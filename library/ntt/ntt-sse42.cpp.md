---
layout: default
---

<!-- mathjax config similar to math.stackexchange -->
<script type="text/javascript" async
  src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.5/MathJax.js?config=TeX-MML-AM_CHTML">
</script>
<script type="text/x-mathjax-config">
  MathJax.Hub.Config({
    TeX: { equationNumbers: { autoNumber: "AMS" }},
    tex2jax: {
      inlineMath: [ ['$','$'] ],
      processEscapes: true
    },
    "HTML-CSS": { matchFontHeight: false },
    displayAlign: "left",
    displayIndent: "2em"
  });
</script>

<script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
<script src="https://cdn.jsdelivr.net/npm/jquery-balloon-js@1.1.2/jquery.balloon.min.js" integrity="sha256-ZEYs9VrgAeNuPvs15E39OsyOJaIkXEEt10fzxJ20+2I=" crossorigin="anonymous"></script>
<script type="text/javascript" src="../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../assets/css/copy-button.css" />


# :heavy_check_mark: ntt/ntt-sse42.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#ccb3669c87b2d028539237c4554e3c0f">ntt</a>
* <a href="{{ site.github.repository_url }}/blob/master/ntt/ntt-sse42.cpp">View this file on GitHub</a>
    - Last commit date: 2020-07-26 06:55:28+09:00




## Depends on

* :heavy_check_mark: <a href="../competitive-template.cpp.html">competitive-template.cpp</a>
* :heavy_check_mark: <a href="../modint/simd-montgomery.cpp.html">modint/simd-montgomery.cpp</a>


## Required by

* :heavy_check_mark: <a href="arbitrary-ntt.cpp.html">ntt/arbitrary-ntt.cpp</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/verify-yosupo-ntt/yosupo-convolution-arbitraryntt-arbitrarymodint.test.cpp.html">verify-yosupo-ntt/yosupo-convolution-arbitraryntt-arbitrarymodint.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/verify-yosupo-ntt/yosupo-convolution-arbitraryntt-arbitraryprimemodint.test.cpp.html">verify-yosupo-ntt/yosupo-convolution-arbitraryntt-arbitraryprimemodint.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/verify-yosupo-ntt/yosupo-convolution-arbitraryntt.test.cpp.html">verify-yosupo-ntt/yosupo-convolution-arbitraryntt.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/verify-yosupo-ntt/yosupo-convolution-ntt-sse42.test.cpp.html">verify-yosupo-ntt/yosupo-convolution-ntt-sse42.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once
#ifndef Nyaan_template
#include "../competitive-template.cpp"
#endif

#include "../modint/simd-montgomery.cpp"

constexpr int SZ = 1 << 19;
uint32_t buf1_[SZ * 2] __attribute__((aligned(64)));
uint32_t buf2_[SZ * 2] __attribute__((aligned(64)));

template <typename mint>
struct NTT {
  static constexpr uint32_t get_pr() {
    uint32_t mod = mint::get_mod();
    using u64 = uint64_t;
    u64 ds[32] = {};
    int idx = 0;
    u64 m = mod - 1;
    for (u64 i = 2; i * i <= m; ++i) {
      if (m % i == 0) {
        ds[idx++] = i;
        while (m % i == 0) m /= i;
      }
    }
    if (m != 1) ds[idx++] = m;

    uint32_t pr = 2;
    while (1) {
      int flg = 1;
      for (int i = 0; i < idx; ++i) {
        u64 a = pr, b = (mod - 1) / ds[i], r = 1;
        while (b) {
          if (b & 1) r = r * a % mod;
          a = a * a % mod;
          b >>= 1;
        }
        if (r == 1) {
          flg = 0;
          break;
        }
      }
      if (flg == 1) break;
      ++pr;
    }
    return pr;
  };

  static constexpr uint32_t mod = mint::get_mod();
  static constexpr uint32_t pr = get_pr();
  static constexpr int level = __builtin_ctzll(mod - 1);
  mint dw[level], dy[level];
  mint *buf1, *buf2;

  NTT() {
    setwy(level);
    buf1 = reinterpret_cast<mint *>(::buf1_);
    buf2 = reinterpret_cast<mint *>(::buf2_);
  }

  constexpr void setwy(int k) {
    mint w[level], y[level];
    w[k - 1] = mint(pr).pow((mod - 1) / (1 << k));
    y[k - 1] = w[k - 1].inverse();
    for (int i = k - 2; i > 0; --i)
      w[i] = w[i + 1] * w[i + 1], y[i] = y[i + 1] * y[i + 1];
    dw[1] = w[1], dy[1] = y[1], dw[2] = w[2], dy[2] = y[2];
    for (int i = 3; i < k; ++i) {
      dw[i] = dw[i - 1] * y[i - 2] * w[i];
      dy[i] = dy[i - 1] * w[i - 2] * y[i];
    }
  }

  __attribute__((target("sse4.2"))) void ntt(mint *a, int n) {
    int k = n ? __builtin_ctz(n) : 0;
    if (k == 0) return;
    if (k == 1) {
      mint a1 = a[1];
      a[1] = a[0] - a[1];
      a[0] = a[0] + a1;
      return;
    }
    if (k & 1) {
      int v = 1 << (k - 1);
      for (int j = 0; j < v; ++j) {
        mint ajv = a[j + v];
        a[j + v] = a[j] - ajv;
        a[j] += ajv;
      }
    }
    int u = 1 << (2 + (k & 1));
    int v = 1 << (k - 2 - (k & 1));
    mint one = mint(1);
    mint imag = dw[1];
    const __m128i m0 = _mm_set1_epi32(0);
    const __m128i m1 = _mm_set1_epi32(mod);
    const __m128i m2 = _mm_set1_epi32(mod + mod);
    const __m128i r = _mm_set1_epi32(mint::r);
    const __m128i Imag = _mm_set1_epi32(imag.a);
    while (v) {
      if (v == 1) {
        mint ww = one, xx = one, wx = one;
        for (int jh = 0; jh < u;) {
          ww = xx * xx, wx = ww * xx;
          mint t0 = a[jh + 0], t1 = a[jh + 1] * xx;
          mint t2 = a[jh + 2] * ww, t3 = a[jh + 3] * wx;
          mint t0p2 = t0 + t2, t1p3 = t1 + t3;
          mint t0m2 = t0 - t2, t1m3 = (t1 - t3) * imag;
          a[jh + 0] = t0p2 + t1p3, a[jh + 1] = t0p2 - t1p3;
          a[jh + 2] = t0m2 + t1m3, a[jh + 3] = t0m2 - t1m3;
          xx *= dw[__builtin_ctz((jh += 4))];
        }
      } else {
        mint ww = one, xx = one, wx = one;
        for (int jh = 0; jh < u;) {
          if (jh == 0) {
            int j0 = 0;
            int j1 = v;
            int j2 = j1 + v;
            int j3 = j2 + v;
            int je = v;
            for (; j0 < je; j0 += 4, j1 += 4, j2 += 4, j3 += 4) {
              __m128i T0 = _mm_loadu_si128((__m128i *)(a + j0));
              __m128i T1 = _mm_loadu_si128((__m128i *)(a + j1));
              __m128i T2 = _mm_loadu_si128((__m128i *)(a + j2));
              __m128i T3 = _mm_loadu_si128((__m128i *)(a + j3));
              __m128i T0P2 = montgomery_add_128(T0, T2, m2, m0);
              __m128i T1P3 = montgomery_add_128(T1, T3, m2, m0);
              __m128i T0M2 = montgomery_sub_128(T0, T2, m2, m0);
              __m128i T1M3 =
                  montgomery_mul_128(montgomery_sub_128(T1, T3, m2, m0), Imag, r, m1);
              _mm_storeu_si128((__m128i *)(a + j0),
                               montgomery_add_128(T0P2, T1P3, m2, m0));
              _mm_storeu_si128((__m128i *)(a + j1),
                               montgomery_sub_128(T0P2, T1P3, m2, m0));
              _mm_storeu_si128((__m128i *)(a + j2),
                               montgomery_add_128(T0M2, T1M3, m2, m0));
              _mm_storeu_si128((__m128i *)(a + j3),
                               montgomery_sub_128(T0M2, T1M3, m2, m0));
            }
          } else {
            ww = xx * xx, wx = ww * xx;
            __m128i WW = _mm_set1_epi32(ww.a);
            __m128i WX = _mm_set1_epi32(wx.a);
            __m128i XX = _mm_set1_epi32(xx.a);
            int j0 = jh * v;
            int j1 = j0 + v;
            int j2 = j1 + v;
            int j3 = j2 + v;
            int je = j1;
            for (; j0 < je; j0 += 4, j1 += 4, j2 += 4, j3 += 4) {
              __m128i T0 = _mm_loadu_si128((__m128i *)(a + j0));
              __m128i T1 = _mm_loadu_si128((__m128i *)(a + j1));
              __m128i T2 = _mm_loadu_si128((__m128i *)(a + j2));
              __m128i T3 = _mm_loadu_si128((__m128i *)(a + j3));
              T1 = montgomery_mul_128(T1, XX, r, m1);
              T2 = montgomery_mul_128(T2, WW, r, m1);
              T3 = montgomery_mul_128(T3, WX, r, m1);
              __m128i T0P2 = montgomery_add_128(T0, T2, m2, m0);
              __m128i T1P3 = montgomery_add_128(T1, T3, m2, m0);
              __m128i T0M2 = montgomery_sub_128(T0, T2, m2, m0);
              __m128i T1M3 =
                  montgomery_mul_128(montgomery_sub_128(T1, T3, m2, m0), Imag, r, m1);
              _mm_storeu_si128((__m128i *)(a + j0),
                               montgomery_add_128(T0P2, T1P3, m2, m0));
              _mm_storeu_si128((__m128i *)(a + j1),
                               montgomery_sub_128(T0P2, T1P3, m2, m0));
              _mm_storeu_si128((__m128i *)(a + j2),
                               montgomery_add_128(T0M2, T1M3, m2, m0));
              _mm_storeu_si128((__m128i *)(a + j3),
                               montgomery_sub_128(T0M2, T1M3, m2, m0));
            }
          }
          xx *= dw[__builtin_ctz((jh += 4))];
        }
      }
      u <<= 2;
      v >>= 2;
    }
  }

  __attribute__((target("sse4.2"))) void intt(mint *a, int n,
                                              int normalize = true) {
    int k = n ? __builtin_ctz(n) : 0;
    if (k == 0) return;
    if (k == 1) {
      mint a1 = a[1];
      a[1] = a[0] - a[1];
      a[0] = a[0] + a1;
      return;
    }
    int u = 1 << (k - 2);
    int v = 1;
    mint one = mint(1);
    mint imag = dy[1];
    const __m128i m0 = _mm_set1_epi32(0);
    const __m128i m1 = _mm_set1_epi32(mod);
    const __m128i m2 = _mm_set1_epi32(mod + mod);
    const __m128i r = _mm_set1_epi32(mint::r);
    const __m128i Imag = _mm_set1_epi32(imag.a);
    while (u) {
      if (v == 1) {
        mint ww = one, xx = one, yy = one;
        u <<= 2;
        for (int jh = 0; jh < u;) {
          ww = xx * xx, yy = xx * imag;
          mint t0 = a[jh + 0], t1 = a[jh + 1];
          mint t2 = a[jh + 2], t3 = a[jh + 3];
          mint t0p1 = t0 + t1, t2p3 = t2 + t3;
          mint t0m1 = (t0 - t1) * xx, t2m3 = (t2 - t3) * yy;
          a[jh + 0] = t0p1 + t2p3, a[jh + 2] = (t0p1 - t2p3) * ww;
          a[jh + 1] = t0m1 + t2m3, a[jh + 3] = (t0m1 - t2m3) * ww;
          xx *= dy[__builtin_ctz(jh += 4)];
        }
      } else {
        mint ww = one, xx = one, yy = one;
        u <<= 2;
        for (int jh = 0; jh < u;) {
          if (jh == 0) {
            int j0 = 0;
            int j1 = v;
            int j2 = v + v;
            int j3 = j2 + v;
            for (; j0 < v; j0 += 4, j1 += 4, j2 += 4, j3 += 4) {
              __m128i T0 = _mm_loadu_si128((__m128i *)(a + j0));
              __m128i T1 = _mm_loadu_si128((__m128i *)(a + j1));
              __m128i T2 = _mm_loadu_si128((__m128i *)(a + j2));
              __m128i T3 = _mm_loadu_si128((__m128i *)(a + j3));
              __m128i T0P1 = montgomery_add_128(T0, T1, m2, m0);
              __m128i T2P3 = montgomery_add_128(T2, T3, m2, m0);
              __m128i T0M1 = montgomery_sub_128(T0, T1, m2, m0);
              __m128i T2M3 =
                  montgomery_mul_128(montgomery_sub_128(T2, T3, m2, m0), Imag, r, m1);
              _mm_storeu_si128((__m128i *)(a + j0),
                               montgomery_add_128(T0P1, T2P3, m2, m0));
              _mm_storeu_si128((__m128i *)(a + j2),
                               montgomery_sub_128(T0P1, T2P3, m2, m0));
              _mm_storeu_si128((__m128i *)(a + j1),
                               montgomery_add_128(T0M1, T2M3, m2, m0));
              _mm_storeu_si128((__m128i *)(a + j3),
                               montgomery_sub_128(T0M1, T2M3, m2, m0));
            }
          } else {
            ww = xx * xx, yy = xx * imag;
            __m128i WW = _mm_set1_epi32(ww.a);
            __m128i XX = _mm_set1_epi32(xx.a);
            __m128i YY = _mm_set1_epi32(yy.a);
            int j0 = jh * v;
            int j1 = j0 + v;
            int j2 = j1 + v;
            int j3 = j2 + v;
            int je = j1;
            for (; j0 < je; j0 += 4, j1 += 4, j2 += 4, j3 += 4) {
              __m128i T0 = _mm_loadu_si128((__m128i *)(a + j0));
              __m128i T1 = _mm_loadu_si128((__m128i *)(a + j1));
              __m128i T2 = _mm_loadu_si128((__m128i *)(a + j2));
              __m128i T3 = _mm_loadu_si128((__m128i *)(a + j3));
              __m128i T0P1 = montgomery_add_128(T0, T1, m2, m0);
              __m128i T2P3 = montgomery_add_128(T2, T3, m2, m0);
              __m128i T0M1 =
                  montgomery_mul_128(montgomery_sub_128(T0, T1, m2, m0), XX, r, m1);
              __m128i T2M3 =
                  montgomery_mul_128(montgomery_sub_128(T2, T3, m2, m0), YY, r, m1);
              _mm_storeu_si128((__m128i *)(a + j0),
                               montgomery_add_128(T0P1, T2P3, m2, m0));
              _mm_storeu_si128(
                  (__m128i *)(a + j2),
                  montgomery_mul_128(montgomery_sub_128(T0P1, T2P3, m2, m0), WW, r,
                                 m1));
              _mm_storeu_si128((__m128i *)(a + j1),
                               montgomery_add_128(T0M1, T2M3, m2, m0));
              _mm_storeu_si128(
                  (__m128i *)(a + j3),
                  montgomery_mul_128(montgomery_sub_128(T0M1, T2M3, m2, m0), WW, r,
                                 m1));
            }
          }
          xx *= dy[__builtin_ctz(jh += 4)];
        }
      }
      u >>= 4;
      v <<= 2;
    }
    if (k & 1) {
      u = 1 << (k - 1);
      for (int j = 0; j < u; ++j) {
        mint ajv = a[j] - a[j + u];
        a[j] += a[j + u];
        a[j + u] = ajv;
      }
    }
    if (normalize) {
      mint invn = one / mint(n);
      for (int i = 0; i < n; i++) a[i] *= invn;
    }
  }

  constexpr vector<mint> multiply(const vector<mint> &a,
                                  const vector<mint> &b) {
    int l = a.size() + b.size() - 1;
    if (min<int>(a.size(), b.size()) <= 40) {
      vector<mint> s(l);
      for (int i = 0; i < (int)a.size(); ++i)
        for (int j = 0; j < (int)b.size(); ++j) s[i + j] += a[i] * b[j];
      return s;
    }
    int M = 4;
    while (M < l) M <<= 1;
    for (int i = 0; i < (int)a.size(); ++i) buf1[i].a = a[i].a;
    for (int i = (int)a.size(); i < M; ++i) buf1[i].a = 0;
    for (int i = 0; i < (int)b.size(); ++i) buf2[i].a = b[i].a;
    for (int i = (int)b.size(); i < M; ++i) buf2[i].a = 0;
    ntt(buf1, M);
    ntt(buf2, M);
    for (int i = 0; i < M; ++i)
      buf1[i].a = mint::reduce(uint64_t(buf1[i].a) * buf2[i].a);
    intt(buf1, M, false);
    vector<mint> s(l);
    mint invm = mint(M).inverse();
    for (int i = 0; i < l; ++i) s[i] = buf1[i] * invm;
    return s;
  }
};
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
Traceback (most recent call last):
  File "/opt/hostedtoolcache/Python/3.8.3/x64/lib/python3.8/site-packages/onlinejudge_verify/docs.py", line 349, in write_contents
    bundled_code = language.bundle(self.file_class.file_path, basedir=pathlib.Path.cwd())
  File "/opt/hostedtoolcache/Python/3.8.3/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus.py", line 185, in bundle
    bundler.update(path)
  File "/opt/hostedtoolcache/Python/3.8.3/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py", line 306, in update
    raise BundleErrorAt(path, i + 1, "unable to process #include in #if / #ifdef / #ifndef other than include guards")
onlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: ntt/ntt-sse42.cpp: line 3: unable to process #include in #if / #ifdef / #ifndef other than include guards

```
{% endraw %}

<a href="../../index.html">Back to top page</a>
