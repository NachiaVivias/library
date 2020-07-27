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


# :heavy_check_mark: data-structure/sliding-window-minimum.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#36397fe12f935090ad150c6ce0c258d4">data-structure</a>
* <a href="{{ site.github.repository_url }}/blob/master/data-structure/sliding-window-minimum.hpp">View this file on GitHub</a>
    - Last commit date: 2020-07-28 03:32:31+09:00




## Depends on

* :question: <a href="../competitive-template.hpp.html">competitive-template.hpp</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/verify-aoj-dsl/aoj-dsl-3-d.test.cpp.html">verify-aoj-dsl/aoj-dsl-3-d.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once
#ifndef Nyaan_template
#include "../competitive-template.hpp"
#endif

// return dat | dat[i] := ( answer of range [i - K, i) )
// T : data type
// f : compare function
// K : width of window
template <typename T, typename F>
vector<T> SlideWindowMinimum(vector<T> &v, F f, int K) {
  vector<T> dat;
  int N = v.size();
  dat.resize(N + 1);
  dat[0] = 0;
  deque<int> q;
  for (int i = 0; i < K - 1; i++) {
    while (!q.empty() && (f(v[i], v[q.back()]) == v[i])) q.pop_back();
    q.push_back(i);
    dat[i + 1] = v[q.front()];
  }
  for (int i = K; i < N + 1; i++) {
    T cur = v[i - 1];
    while (!q.empty() && (f(cur, v[q.back()]) == cur)) q.pop_back();
    q.push_back(i - 1);
    dat[i] = v[q.front()];
    if (q.front() == i - K) q.pop_front();
  }
  return dat;
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
onlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: data-structure/sliding-window-minimum.hpp: line 3: unable to process #include in #if / #ifdef / #ifndef other than include guards

```
{% endraw %}

<a href="../../index.html">Back to top page</a>
