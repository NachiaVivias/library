---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    _deprecated_at_docs: docs/math/prime-counting.md
    document_title: "\u7D20\u6570\u30AB\u30A6\u30F3\u30C8( $\\mathrm{O}(\\frac{N^{\\\
      frac{3}{4}}}{\\log N})$\u30FB\u9AD8\u901F\u5316\u7248)"
    links: []
  bundledCode: "#line 1 \"math/prime-counting-faster.hpp\"\n#include <bits/stdc++.h>\n\
    using namespace std;\n\nnamespace PrimeCounting {\nusing i64 = long long;\nstatic\
    \ inline i64 my_div(i64 n, i64 p) { return double(n) / p; };\n\n__attribute__((target(\"\
    avx2\"), optimize(\"O3\", \"unroll-loops\"))) i64\nprime_counting(i64 N) {\n \
    \ i64 N2 = sqrt(N);\n  i64 NdN2 = my_div(N, N2);\n\n  vector<i64> hl(NdN2);\n\
    \  for (int i = 1; i < NdN2; i++) hl[i] = my_div(N, i) - 1;\n\n  vector<int> hs(N2\
    \ + 1);\n  iota(begin(hs), end(hs), -1);\n\n  for (int x = 2, pi = 0; x <= N2;\
    \ ++x) {\n    if (hs[x] == hs[x - 1]) continue;\n    i64 x2 = i64(x) * x;\n  \
    \  i64 imax = min<i64>(NdN2, my_div(N, x2) + 1);\n    i64 ix = x;\n    for (i64\
    \ i = 1; i < imax; ++i) {\n      hl[i] -= (ix < NdN2 ? hl[ix] : hs[my_div(N, ix)])\
    \ - pi;\n      ix += x;\n    }\n    for (int n = N2; n >= x2; n--) {\n      hs[n]\
    \ -= hs[my_div(n, x)] - pi;\n    }\n    ++pi;\n  }\n  return hl[1];\n}\n\n}  //\
    \ namespace PrimeCounting\n\n/**\n * @brief \u7D20\u6570\u30AB\u30A6\u30F3\u30C8\
    ( $\\mathrm{O}(\\frac{N^{\\frac{3}{4}}}{\\log N})$\u30FB\u9AD8\u901F\u5316\u7248\
    )\n * @docs docs/math/prime-counting.md\n */\n"
  code: "#include <bits/stdc++.h>\nusing namespace std;\n\nnamespace PrimeCounting\
    \ {\nusing i64 = long long;\nstatic inline i64 my_div(i64 n, i64 p) { return double(n)\
    \ / p; };\n\n__attribute__((target(\"avx2\"), optimize(\"O3\", \"unroll-loops\"\
    ))) i64\nprime_counting(i64 N) {\n  i64 N2 = sqrt(N);\n  i64 NdN2 = my_div(N,\
    \ N2);\n\n  vector<i64> hl(NdN2);\n  for (int i = 1; i < NdN2; i++) hl[i] = my_div(N,\
    \ i) - 1;\n\n  vector<int> hs(N2 + 1);\n  iota(begin(hs), end(hs), -1);\n\n  for\
    \ (int x = 2, pi = 0; x <= N2; ++x) {\n    if (hs[x] == hs[x - 1]) continue;\n\
    \    i64 x2 = i64(x) * x;\n    i64 imax = min<i64>(NdN2, my_div(N, x2) + 1);\n\
    \    i64 ix = x;\n    for (i64 i = 1; i < imax; ++i) {\n      hl[i] -= (ix < NdN2\
    \ ? hl[ix] : hs[my_div(N, ix)]) - pi;\n      ix += x;\n    }\n    for (int n =\
    \ N2; n >= x2; n--) {\n      hs[n] -= hs[my_div(n, x)] - pi;\n    }\n    ++pi;\n\
    \  }\n  return hl[1];\n}\n\n}  // namespace PrimeCounting\n\n/**\n * @brief \u7D20\
    \u6570\u30AB\u30A6\u30F3\u30C8( $\\mathrm{O}(\\frac{N^{\\frac{3}{4}}}{\\log N})$\u30FB\
    \u9AD8\u901F\u5316\u7248)\n * @docs docs/math/prime-counting.md\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: math/prime-counting-faster.hpp
  requiredBy: []
  timestamp: '2020-09-24 23:29:46+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: math/prime-counting-faster.hpp
layout: document
redirect_from:
- /library/math/prime-counting-faster.hpp
- /library/math/prime-counting-faster.hpp.html
title: "\u7D20\u6570\u30AB\u30A6\u30F3\u30C8( $\\mathrm{O}(\\frac{N^{\\frac{3}{4}}}{\\\
  log N})$\u30FB\u9AD8\u901F\u5316\u7248)"
---
## 素数の個数$\pi(N)$の高速計算

$\pi(N)$を$\mathrm{O}\left(\frac{N^{\frac{3}{4}}}{\log N}\right)$で計算するライブラリ。

#### 概要

まず初めに、$f(x,n):=$($n$以下の自然数のうち$x$以下の素数を因数に持たない数の個数)とおく。

この時、

$$\pi(N) = f(\lfloor\sqrt{N}\rfloor,N) + \pi(\lfloor\sqrt{N}\rfloor) - 1$$

であるため、$f(\lfloor\sqrt{N}\rfloor,N)$を高速に求めれば$\pi(N)$が求まる。また、

$$f(x,n) = \begin{cases} f(x-1,n) & \mathrm{if}\ x\ \mathrm{is}\ \mathrm{not}\  \mathrm{prime} \newline f(x-1,n)-f(x-1,\lfloor\frac{n}{x}\rfloor) & \mathrm{otherwise} \end{cases}$$

となるが、ここで$\lfloor\frac{N}{ij}\rfloor=\lfloor\lfloor\frac{N}{i}\rfloor/j\rfloor$に着目すると、$f(\lfloor\sqrt{N}\rfloor,N)$は$f(x,n),1 \leq x \leq \sqrt{N},n = \lfloor\frac{N}{K}\rfloor$($K$は自然数)の線形和で表されるとわかる。

よって、$f(0,n)=n$を初期値として$x\leq \sqrt{N},n =\lfloor\frac{N}{K}\rfloor$を範囲とする、$x$が素数の時に更新するin-placeな動的計画法で$f(\lfloor\sqrt{N}\rfloor,N)$を求められる。計算量は
- $\sqrt{N}$以下の素数の個数 $\ldots$ 素数定理より$\mathrm{O}\left(\frac{\sqrt{N}}{\log N}\right)$
- DPテーブルの長さ $\ldots$ $\lfloor\frac{N}{K}\rfloor$の取りうる値の個数なので$\mathrm{O}(\sqrt{N})$

なので$\mathrm{O}\left(\frac{N}{\log N}\right)$となる。

さらに高速化する。$g(x,n) :=f(x,n) + \pi(\min(n,x))$とおくと、$g(x,n)$は$n$以下の数に$x$以下の素数でふるいを掛けた時に残ったもの($1$を含む)となる。ここから

$$g(\lfloor\sqrt{N}\rfloor,N) = \pi(N) - 1$$

であり、また$f(x,n)$の式に代入すると

$$g(x,n) = \begin{cases} g(x-1,n) & \mathrm{if}\ x\ \mathrm{is}\ \mathrm{not}\  \mathrm{prime}\ \cup\ n < x^2 \newline g(x-1,n)-g(x-1,\lfloor\frac{n}{x}\rfloor) + \pi(x) & \mathrm{otherwise} \end{cases}$$

を示せる。

$h(x,n) = g(x,n)-1$とおいて整理すると、

$$\pi(N) = h(\lfloor\sqrt{N}\rfloor,N)$$

$$h(0,n) = n - 1$$

$$h(x,n) = \begin{cases} h(x-1,n) & \mathrm{if}\ x\ \mathrm{is}\ \mathrm{not}\  \mathrm{prime}\ \cup\ n < x^2 \newline h(x-1,n)-h(x-1,\lfloor\frac{n}{x}\rfloor) + h(x-1,x-1) & \mathrm{otherwise} \end{cases}$$

となり、簡素な動的計画法が実行できる。計算量は$h(x,n)$の更新回数を数えればよく、

- $2 \leq x \leq N^{\frac{1}{4}}$のとき $\ldots$ 素数は$\mathrm{O}\left(\frac{N^{\frac{1}{4}}}{\log N}\right)$個あってDPテーブルの長さは$\mathrm{O}(\sqrt{N})$なので合計$\mathrm{O}\left(\frac{N^{\frac{3}{4}}}{\log N}\right)$回
- $N^{\frac{1}{4}} \leq x \leq \sqrt{N}$のとき 各$x$についてそれぞれ$\ldots$ $x^2< n < N$を満たす部分を更新する。更新する個数は$\sqrt{N} < x^2$より$\mathrm{O}\left(\frac{N}{x^2}\right)$個なので、合計$\mathrm{O}\left(\frac{1}{\log N}\int_{N^{\frac{1}{4}}}^{\sqrt{N}} \frac{N}{x^2}dx\right)=\mathrm{O}\left(\frac{N^{\frac{3}{4}}}{\log N}\right)回$

以上より全体の計算量は$\mathrm{O}\left(\frac{N^{\frac{3}{4}}}{\log N}\right)$となる。

#### 補足

区間を3つに区切ってFenwick Treeを使用することで更なる計算量の改善が可能である。(ただし実装はかなり煩雑になる。)

[$\mathrm{O}(N^\frac{2}{3})$での実装](https://nyaannyaan.github.io/library/library/math/prime-counting-o2d3.hpp.html)

なお、高速化をしたい場合は整数同士の除算をdouble型同士の除算で計算するのが最も高速化への寄与が大きい。なぜなら、64bit整数同士の除算は最悪ケースで80クロックと低速なのに対してdouble型同士は11クロックとはるかに高速であり、また$N=10^{12}$程度の大きさ同士の切り捨て除算ならばdouble型で計算しても誤差が発生しないことが規格で保証されているためである。実際にLibrary Checkerの提出で比較すると、除算を変えるだけで686ms→180msとおよそ4倍もの高速化となっている。

[定数倍高速化したバージョン](https://nyaannyaan.github.io/library/math/prime-counting-faster.hpp)　[提出(104ms)](https://judge.yosupo.jp/submission/19375)　他の人の提出を見ると異常高速化している人が何人も居て、魔境か？という気持ちに…