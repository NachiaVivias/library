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


# :heavy_check_mark: modint/simd-montgomery.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#fb97f878c938d7517d3d9f7de68146e9">modint</a>
* <a href="{{ site.github.repository_url }}/blob/master/modint/simd-montgomery.cpp">View this file on GitHub</a>
    - Last commit date: 2020-07-24 20:19:03+09:00




## Depends on

* :heavy_check_mark: <a href="../competitive-template.cpp.html">competitive-template.cpp</a>


## Required by

* :heavy_check_mark: <a href="../ntt/arbitrary-ntt.cpp.html">ntt/arbitrary-ntt.cpp</a>
* :heavy_check_mark: <a href="../ntt/ntt-sse42.cpp.html">ntt/ntt-sse42.cpp</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/verify/yosupo-convolution-arbitraryntt-arbitrarymodint.test.cpp.html">verify/yosupo-convolution-arbitraryntt-arbitrarymodint.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/verify/yosupo-convolution-arbitraryntt-arbitraryprimemodint.test.cpp.html">verify/yosupo-convolution-arbitraryntt-arbitraryprimemodint.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/verify/yosupo-convolution-arbitraryntt.test.cpp.html">verify/yosupo-convolution-arbitraryntt.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/verify/yosupo-convolution-ntt-sse42.test.cpp.html">verify/yosupo-convolution-ntt-sse42.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once
#ifndef Nyaan_template
#include "../competitive-template.cpp"
#endif

constexpr int SZ = 1 << 19;
#include <immintrin.h>
using u32 = uint32_t;
using u64 = uint64_t;

__attribute__((target("sse4.2"))) __attribute__((always_inline)) __m128i
my_mullo_epu32(const __m128i &a, const __m128i &b) {
  return _mm_mullo_epi32(a, b);
}

__attribute__((target("sse4.2"))) __attribute__((always_inline)) __m128i
my_mulhi_epu32(const __m128i &a, const __m128i &b) {
  __m128i a13 = _mm_shuffle_epi32(a, 0xF5);
  __m128i b13 = _mm_shuffle_epi32(b, 0xF5);
  __m128i prod02 = _mm_mul_epu32(a, b);
  __m128i prod13 = _mm_mul_epu32(a13, b13);
  __m128i prod = _mm_unpackhi_epi64(_mm_unpacklo_epi32(prod02, prod13),
                                    _mm_unpackhi_epi32(prod02, prod13));
  return prod;
}

__attribute__((target("sse4.2"))) __m128i montgomery_mul(const __m128i &a,
                                                         const __m128i &b,
                                                         const __m128i &r,
                                                         const __m128i &m1) {
  return _mm_sub_epi32(
      _mm_add_epi32(my_mulhi_epu32(a, b), m1),
      my_mulhi_epu32(my_mullo_epu32(my_mullo_epu32(a, b), r), m1));
}

__attribute__((target("sse4.2"))) __m128i montgomery_add(const __m128i &a,
                                                         const __m128i &b,
                                                         const __m128i &m2,
                                                         const __m128i &m0) {
  __m128i ret = _mm_sub_epi32(_mm_add_epi32(a, b), m2);
  return _mm_add_epi32(_mm_and_si128(_mm_cmpgt_epi32(m0, ret), m2), ret);
}

__attribute__((target("sse4.2"))) __m128i montgomery_sub(const __m128i &a,
                                                         const __m128i &b,
                                                         const __m128i &m2,
                                                         const __m128i &m0) {
  __m128i ret = _mm_sub_epi32(a, b);
  return _mm_add_epi32(_mm_and_si128(_mm_cmpgt_epi32(m0, ret), m2), ret);
}

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
onlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: modint/simd-montgomery.cpp: line 3: unable to process #include in #if / #ifdef / #ifndef other than include guards

```
{% endraw %}

<a href="../../index.html">Back to top page</a>
