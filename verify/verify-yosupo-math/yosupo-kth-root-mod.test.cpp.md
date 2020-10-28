---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: competitive-template.hpp
    title: competitive-template.hpp
  - icon: ':heavy_check_mark:'
    path: inner/inner_math.hpp
    title: inner/inner_math.hpp
  - icon: ':heavy_check_mark:'
    path: misc/rng.hpp
    title: misc/rng.hpp
  - icon: ':heavy_check_mark:'
    path: modint/arbitrary-prime-modint.hpp
    title: modint/arbitrary-prime-modint.hpp
  - icon: ':heavy_check_mark:'
    path: modint/modint-montgomery64.hpp
    title: modint/modint-montgomery64.hpp
  - icon: ':heavy_check_mark:'
    path: modulo/mod-kth-root.hpp
    title: kth root(Tonelli-Shanks algorithm)
  - icon: ':heavy_check_mark:'
    path: prime/fast-factorize.hpp
    title: "\u9AD8\u901F\u7D20\u56E0\u6570\u5206\u89E3(Miller Rabin/Pollard's Rho)"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/kth_root_mod
    links:
    - https://judge.yosupo.jp/problem/kth_root_mod
  bundledCode: "#line 1 \"verify/verify-yosupo-math/yosupo-kth-root-mod.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/kth_root_mod\"\n\n#line 1\
    \ \"competitive-template.hpp\"\n#pragma region kyopro_template\n#define Nyaan_template\n\
    #include <immintrin.h>\n#include <bits/stdc++.h>\n#define pb push_back\n#define\
    \ eb emplace_back\n#define fi first\n#define se second\n#define each(x, v) for\
    \ (auto &x : v)\n#define all(v) (v).begin(), (v).end()\n#define sz(v) ((int)(v).size())\n\
    #define mem(a, val) memset(a, val, sizeof(a))\n#define ini(...)   \\\n  int __VA_ARGS__;\
    \ \\\n  in(__VA_ARGS__)\n#define inl(...)         \\\n  long long __VA_ARGS__;\
    \ \\\n  in(__VA_ARGS__)\n#define ins(...)      \\\n  string __VA_ARGS__; \\\n\
    \  in(__VA_ARGS__)\n#define inc(...)    \\\n  char __VA_ARGS__; \\\n  in(__VA_ARGS__)\n\
    #define in2(s, t)                           \\\n  for (int i = 0; i < (int)s.size();\
    \ i++) { \\\n    in(s[i], t[i]);                         \\\n  }\n#define in3(s,\
    \ t, u)                        \\\n  for (int i = 0; i < (int)s.size(); i++) {\
    \ \\\n    in(s[i], t[i], u[i]);                   \\\n  }\n#define in4(s, t, u,\
    \ v)                     \\\n  for (int i = 0; i < (int)s.size(); i++) { \\\n\
    \    in(s[i], t[i], u[i], v[i]);             \\\n  }\n#define rep(i, N) for (long\
    \ long i = 0; i < (long long)(N); i++)\n#define repr(i, N) for (long long i =\
    \ (long long)(N)-1; i >= 0; i--)\n#define rep1(i, N) for (long long i = 1; i <=\
    \ (long long)(N); i++)\n#define repr1(i, N) for (long long i = (N); (long long)(i)\
    \ > 0; i--)\n#define reg(i, a, b) for (long long i = (a); i < (b); i++)\n#define\
    \ die(...)      \\\n  do {                \\\n    out(__VA_ARGS__); \\\n    return;\
    \           \\\n  } while (0)\nusing namespace std;\nusing ll = long long;\ntemplate\
    \ <class T>\nusing V = vector<T>;\nusing vi = vector<int>;\nusing vl = vector<long\
    \ long>;\nusing vvi = vector<vector<int>>;\nusing vd = V<double>;\nusing vs =\
    \ V<string>;\nusing vvl = vector<vector<long long>>;\nusing P = pair<long long,\
    \ long long>;\nusing vp = vector<P>;\nusing pii = pair<int, int>;\nusing vpi =\
    \ vector<pair<int, int>>;\nconstexpr int inf = 1001001001;\nconstexpr long long\
    \ infLL = (1LL << 61) - 1;\ntemplate <typename T, typename U>\ninline bool amin(T\
    \ &x, U y) {\n  return (y < x) ? (x = y, true) : false;\n}\ntemplate <typename\
    \ T, typename U>\ninline bool amax(T &x, U y) {\n  return (x < y) ? (x = y, true)\
    \ : false;\n}\ntemplate <typename T, typename U>\nostream &operator<<(ostream\
    \ &os, const pair<T, U> &p) {\n  os << p.first << \" \" << p.second;\n  return\
    \ os;\n}\ntemplate <typename T, typename U>\nistream &operator>>(istream &is,\
    \ pair<T, U> &p) {\n  is >> p.first >> p.second;\n  return is;\n}\ntemplate <typename\
    \ T>\nostream &operator<<(ostream &os, const vector<T> &v) {\n  int s = (int)v.size();\n\
    \  for (int i = 0; i < s; i++) os << (i ? \" \" : \"\") << v[i];\n  return os;\n\
    }\ntemplate <typename T>\nistream &operator>>(istream &is, vector<T> &v) {\n \
    \ for (auto &x : v) is >> x;\n  return is;\n}\nvoid in() {}\ntemplate <typename\
    \ T, class... U>\nvoid in(T &t, U &... u) {\n  cin >> t;\n  in(u...);\n}\nvoid\
    \ out() { cout << \"\\n\"; }\ntemplate <typename T, class... U>\nvoid out(const\
    \ T &t, const U &... u) {\n  cout << t;\n  if (sizeof...(u)) cout << \" \";\n\
    \  out(u...);\n}\n\n#ifdef NyaanDebug\n#define trc(...)                   \\\n\
    \  do {                             \\\n    cerr << #__VA_ARGS__ << \" = \"; \\\
    \n    dbg_out(__VA_ARGS__);          \\\n  } while (0)\n#define trca(v, N)   \
    \    \\\n  do {                   \\\n    cerr << #v << \" = \"; \\\n    array_out(v,\
    \ N);     \\\n  } while (0)\n#define trcc(v)                             \\\n\
    \  do {                                      \\\n    cerr << #v << \" = {\"; \
    \                  \\\n    each(x, v) { cerr << \" \" << x << \",\"; } \\\n  \
    \  cerr << \"}\" << endl;                    \\\n  } while (0)\ntemplate <typename\
    \ T>\nvoid _cout(const T &c) {\n  cerr << c;\n}\nvoid _cout(const int &c) {\n\
    \  if (c == 1001001001)\n    cerr << \"inf\";\n  else if (c == -1001001001)\n\
    \    cerr << \"-inf\";\n  else\n    cerr << c;\n}\nvoid _cout(const unsigned int\
    \ &c) {\n  if (c == 1001001001)\n    cerr << \"inf\";\n  else\n    cerr << c;\n\
    }\nvoid _cout(const long long &c) {\n  if (c == 1001001001 || c == (1LL << 61)\
    \ - 1)\n    cerr << \"inf\";\n  else if (c == -1001001001 || c == -((1LL << 61)\
    \ - 1))\n    cerr << \"-inf\";\n  else\n    cerr << c;\n}\nvoid _cout(const unsigned\
    \ long long &c) {\n  if (c == 1001001001 || c == (1LL << 61) - 1)\n    cerr <<\
    \ \"inf\";\n  else\n    cerr << c;\n}\ntemplate <typename T, typename U>\nvoid\
    \ _cout(const pair<T, U> &p) {\n  cerr << \"{ \";\n  _cout(p.fi);\n  cerr << \"\
    , \";\n  _cout(p.se);\n  cerr << \" } \";\n}\ntemplate <typename T>\nvoid _cout(const\
    \ vector<T> &v) {\n  int s = v.size();\n  cerr << \"{ \";\n  for (int i = 0; i\
    \ < s; i++) {\n    cerr << (i ? \", \" : \"\");\n    _cout(v[i]);\n  }\n  cerr\
    \ << \" } \";\n}\ntemplate <typename T>\nvoid _cout(const vector<vector<T>> &v)\
    \ {\n  cerr << \"[ \";\n  for (const auto &x : v) {\n    cerr << endl;\n    _cout(x);\n\
    \    cerr << \", \";\n  }\n  cerr << endl << \" ] \";\n}\nvoid dbg_out() { cerr\
    \ << endl; }\ntemplate <typename T, class... U>\nvoid dbg_out(const T &t, const\
    \ U &... u) {\n  _cout(t);\n  if (sizeof...(u)) cerr << \", \";\n  dbg_out(u...);\n\
    }\ntemplate <typename T>\nvoid array_out(const T &v, int s) {\n  cerr << \"{ \"\
    ;\n  for (int i = 0; i < s; i++) {\n    cerr << (i ? \", \" : \"\");\n    _cout(v[i]);\n\
    \  }\n  cerr << \" } \" << endl;\n}\ntemplate <typename T>\nvoid array_out(const\
    \ T &v, int H, int W) {\n  cerr << \"[ \";\n  for (int i = 0; i < H; i++) {\n\
    \    cerr << (i ? \", \" : \"\");\n    array_out(v[i], W);\n  }\n  cerr << \"\
    \ ] \" << endl;\n}\n#else\n#define trc(...)\n#define trca(...)\n#define trcc(...)\n\
    #endif\n\ninline int popcnt(unsigned long long a) { return __builtin_popcountll(a);\
    \ }\ninline int lsb(unsigned long long a) { return __builtin_ctzll(a); }\ninline\
    \ int msb(unsigned long long a) { return 63 - __builtin_clzll(a); }\ntemplate\
    \ <typename T>\ninline int getbit(T a, int i) {\n  return (a >> i) & 1;\n}\ntemplate\
    \ <typename T>\ninline void setbit(T &a, int i) {\n  a |= (1LL << i);\n}\ntemplate\
    \ <typename T>\ninline void delbit(T &a, int i) {\n  a &= ~(1LL << i);\n}\ntemplate\
    \ <typename T>\nint lb(const vector<T> &v, const T &a) {\n  return lower_bound(begin(v),\
    \ end(v), a) - begin(v);\n}\ntemplate <typename T>\nint ub(const vector<T> &v,\
    \ const T &a) {\n  return upper_bound(begin(v), end(v), a) - begin(v);\n}\ntemplate\
    \ <typename T>\nint btw(T a, T x, T b) {\n  return a <= x && x < b;\n}\ntemplate\
    \ <typename T, typename U>\nT ceil(T a, U b) {\n  return (a + b - 1) / b;\n}\n\
    constexpr long long TEN(int n) {\n  long long ret = 1, x = 10;\n  while (n) {\n\
    \    if (n & 1) ret *= x;\n    x *= x;\n    n >>= 1;\n  }\n  return ret;\n}\n\
    template <typename T>\nvector<T> mkrui(const vector<T> &v) {\n  vector<T> ret(v.size()\
    \ + 1);\n  for (int i = 0; i < int(v.size()); i++) ret[i + 1] = ret[i] + v[i];\n\
    \  return ret;\n};\ntemplate <typename T>\nvector<T> mkuni(const vector<T> &v)\
    \ {\n  vector<T> ret(v);\n  sort(ret.begin(), ret.end());\n  ret.erase(unique(ret.begin(),\
    \ ret.end()), ret.end());\n  return ret;\n}\ntemplate <typename F>\nvector<int>\
    \ mkord(int N, F f) {\n  vector<int> ord(N);\n  iota(begin(ord), end(ord), 0);\n\
    \  sort(begin(ord), end(ord), f);\n  return ord;\n}\ntemplate <typename T = int>\n\
    vector<T> mkiota(int N) {\n  vector<T> ret(N);\n  iota(begin(ret), end(ret), 0);\n\
    \  return ret;\n}\ntemplate <typename T>\nvector<int> mkinv(vector<T> &v) {\n\
    \  vector<int> inv(v.size());\n  for (int i = 0; i < (int)v.size(); i++) inv[v[i]]\
    \ = i;\n  return inv;\n}\n\nstruct IoSetupNya {\n  IoSetupNya() {\n    cin.tie(nullptr);\n\
    \    ios::sync_with_stdio(false);\n    cout << fixed << setprecision(15);\n  \
    \  cerr << fixed << setprecision(7);\n  }\n} iosetupnya;\n\nvoid solve();\nint\
    \ main() { solve(); }\n\n#pragma endregion\n#line 3 \"modulo/mod-kth-root.hpp\"\
    \nusing namespace std;\n\n#line 3 \"inner/inner_math.hpp\"\nusing namespace std;\n\
    \nnamespace inner {\n\nusing i32 = int32_t;\nusing u32 = uint32_t;\nusing i64\
    \ = int64_t;\nusing u64 = uint64_t;\n\ntemplate <typename T>\nT gcd(T a, T b)\
    \ {\n  while (b) swap(a %= b, b);\n  return a;\n}\n\ntemplate <typename T>\nT\
    \ inv(T a, T p) {\n  T b = p, x = 1, y = 0;\n  while (a) {\n    T q = b / a;\n\
    \    swap(a, b %= a);\n    swap(x, y -= q * x);\n  }\n  assert(b == 1);\n  return\
    \ y < 0 ? y + p : y;\n}\n\ntemplate <typename T, typename U>\nT modpow(T a, U\
    \ n, T p) {\n  T ret = 1 % p;\n  for (; n; n >>= 1, a = U(a) * a % p)\n    if\
    \ (n & 1) ret = U(ret) * a % p;\n  return ret;\n}\n\n}  // namespace inner\n#line\
    \ 3 \"modint/arbitrary-prime-modint.hpp\"\nusing namespace std;\n\nstruct ArbitraryLazyMontgomeryModInt\
    \ {\n  using mint = ArbitraryLazyMontgomeryModInt;\n  using i32 = int32_t;\n \
    \ using u32 = uint32_t;\n  using u64 = uint64_t;\n\n  static u32 mod;\n  static\
    \ u32 r;\n  static u32 n2;\n\n  static u32 get_r() {\n    u32 ret = mod;\n   \
    \ for (i32 i = 0; i < 4; ++i) ret *= 2 - mod * ret;\n    return ret;\n  }\n\n\
    \  static void set_mod(u32 m) {\n    assert(m < (1 << 30));\n    assert((m & 1)\
    \ == 1);\n    mod = m;\n    n2 = -u64(m) % m;\n    r = get_r();\n    assert(r\
    \ * mod == 1);\n  }\n\n  u32 a;\n\n  ArbitraryLazyMontgomeryModInt() : a(0) {}\n\
    \  ArbitraryLazyMontgomeryModInt(const int64_t &b)\n      : a(reduce(u64(b % mod\
    \ + mod) * n2)){};\n\n  static u32 reduce(const u64 &b) {\n    return (b + u64(u32(b)\
    \ * u32(-r)) * mod) >> 32;\n  }\n\n  mint &operator+=(const mint &b) {\n    if\
    \ (i32(a += b.a - 2 * mod) < 0) a += 2 * mod;\n    return *this;\n  }\n\n  mint\
    \ &operator-=(const mint &b) {\n    if (i32(a -= b.a) < 0) a += 2 * mod;\n   \
    \ return *this;\n  }\n\n  mint &operator*=(const mint &b) {\n    a = reduce(u64(a)\
    \ * b.a);\n    return *this;\n  }\n\n  mint &operator/=(const mint &b) {\n   \
    \ *this *= b.inverse();\n    return *this;\n  }\n\n  mint operator+(const mint\
    \ &b) const { return mint(*this) += b; }\n  mint operator-(const mint &b) const\
    \ { return mint(*this) -= b; }\n  mint operator*(const mint &b) const { return\
    \ mint(*this) *= b; }\n  mint operator/(const mint &b) const { return mint(*this)\
    \ /= b; }\n  bool operator==(const mint &b) const {\n    return (a >= mod ? a\
    \ - mod : a) == (b.a >= mod ? b.a - mod : b.a);\n  }\n  bool operator!=(const\
    \ mint &b) const {\n    return (a >= mod ? a - mod : a) != (b.a >= mod ? b.a -\
    \ mod : b.a);\n  }\n  mint operator-() const { return mint() - mint(*this); }\n\
    \n  mint pow(u64 n) const {\n    mint ret(1), mul(*this);\n    while (n > 0) {\n\
    \      if (n & 1) ret *= mul;\n      mul *= mul;\n      n >>= 1;\n    }\n    return\
    \ ret;\n  }\n\n  friend ostream &operator<<(ostream &os, const mint &b) {\n  \
    \  return os << b.get();\n  }\n\n  friend istream &operator>>(istream &is, mint\
    \ &b) {\n    int64_t t;\n    is >> t;\n    b = ArbitraryLazyMontgomeryModInt(t);\n\
    \    return (is);\n  }\n\n  mint inverse() const { return pow(mod - 2); }\n\n\
    \  u32 get() const {\n    u32 ret = reduce(a);\n    return ret >= mod ? ret -\
    \ mod : ret;\n  }\n\n  static u32 get_mod() { return mod; }\n};\ntypename ArbitraryLazyMontgomeryModInt::u32\
    \ ArbitraryLazyMontgomeryModInt::mod;\ntypename ArbitraryLazyMontgomeryModInt::u32\
    \ ArbitraryLazyMontgomeryModInt::r;\ntypename ArbitraryLazyMontgomeryModInt::u32\
    \ ArbitraryLazyMontgomeryModInt::n2;\n#line 3 \"modint/modint-montgomery64.hpp\"\
    \nusing namespace std;\n\nstruct montgomery64 {\n  using mint = montgomery64;\n\
    \  using i64 = int64_t;\n  using u64 = uint64_t;\n  using u128 = __uint128_t;\n\
    \n  static u64 mod;\n  static u64 r;\n  static u64 n2;\n\n  static u64 get_r()\
    \ {\n    u64 ret = mod;\n    for (i64 i = 0; i < 5; ++i) ret *= 2 - mod * ret;\n\
    \    return ret;\n  }\n\n  static void set_mod(u64 m) {\n    assert(m < (1LL <<\
    \ 62));\n    assert((m & 1) == 1);\n    mod = m;\n    n2 = -u128(m) % m;\n   \
    \ r = get_r();\n    assert(r * mod == 1);\n  }\n\n  u64 a;\n\n  montgomery64()\
    \ : a(0) {}\n  montgomery64(const int64_t &b) : a(reduce((u128(b) + mod) * n2)){};\n\
    \n  static u64 reduce(const u128 &b) {\n    return (b + u128(u64(b) * u64(-r))\
    \ * mod) >> 64;\n  }\n\n  mint &operator+=(const mint &b) {\n    if (i64(a +=\
    \ b.a - 2 * mod) < 0) a += 2 * mod;\n    return *this;\n  }\n\n  mint &operator-=(const\
    \ mint &b) {\n    if (i64(a -= b.a) < 0) a += 2 * mod;\n    return *this;\n  }\n\
    \n  mint &operator*=(const mint &b) {\n    a = reduce(u128(a) * b.a);\n    return\
    \ *this;\n  }\n\n  mint &operator/=(const mint &b) {\n    *this *= b.inverse();\n\
    \    return *this;\n  }\n\n  mint operator+(const mint &b) const { return mint(*this)\
    \ += b; }\n  mint operator-(const mint &b) const { return mint(*this) -= b; }\n\
    \  mint operator*(const mint &b) const { return mint(*this) *= b; }\n  mint operator/(const\
    \ mint &b) const { return mint(*this) /= b; }\n  bool operator==(const mint &b)\
    \ const {\n    return (a >= mod ? a - mod : a) == (b.a >= mod ? b.a - mod : b.a);\n\
    \  }\n  bool operator!=(const mint &b) const {\n    return (a >= mod ? a - mod\
    \ : a) != (b.a >= mod ? b.a - mod : b.a);\n  }\n  mint operator-() const { return\
    \ mint() - mint(*this); }\n\n  mint pow(u128 n) const {\n    mint ret(1), mul(*this);\n\
    \    while (n > 0) {\n      if (n & 1) ret *= mul;\n      mul *= mul;\n      n\
    \ >>= 1;\n    }\n    return ret;\n  }\n\n  friend ostream &operator<<(ostream\
    \ &os, const mint &b) {\n    return os << b.get();\n  }\n\n  friend istream &operator>>(istream\
    \ &is, mint &b) {\n    int64_t t;\n    is >> t;\n    b = montgomery64(t);\n  \
    \  return (is);\n  }\n\n  mint inverse() const { return pow(mod - 2); }\n\n  u64\
    \ get() const {\n    u64 ret = reduce(a);\n    return ret >= mod ? ret - mod :\
    \ ret;\n  }\n\n  static u64 get_mod() { return mod; }\n};\ntypename montgomery64::u64\
    \ montgomery64::mod, montgomery64::r, montgomery64::n2;\n#line 3 \"prime/fast-factorize.hpp\"\
    \nusing namespace std;\n\n#line 3 \"misc/rng.hpp\"\nusing namespace std;\n\nnamespace\
    \ my_rand {\n\nuint64_t rng() {\n#ifdef NyaanDebug\n  static uint64_t x_ =\n \
    \     chrono::duration_cast<chrono::nanoseconds>(\n          chrono::high_resolution_clock::now().time_since_epoch())\n\
    \          .count();\n#else\n  static uint64_t x_ = 88172645463325252ULL;\n#endif\n\
    \  x_ = x_ ^ (x_ << 7);\n  return x_ = x_ ^ (x_ >> 9);\n}\n\n// [l, r)\nint64_t\
    \ randint(int64_t l, int64_t r) {\n  assert(l < r);\n  return l + rng() % (r -\
    \ l);\n}\n\n//\nvector<int64_t> randset(int64_t l, int64_t r, int64_t n) {\n \
    \ assert(l <= r && n <= r - l);\n  unordered_set<int64_t> s;\n  for (int64_t i\
    \ = n; i; --i) {\n    int64_t m = randint(l, r + 1 - i);\n    if (s.find(m) !=\
    \ s.end()) m = r - i;\n    s.insert(m);\n  }\n  vector<int64_t> ret;\n  for (auto&\
    \ x : s) ret.push_back(x);\n  return ret;\n}\n\n}  // namespace my_rand\n\nusing\
    \ my_rand::randint;\nusing my_rand::randset;\nusing my_rand::rng;\n#line 9 \"\
    prime/fast-factorize.hpp\"\n\nnamespace fast_factorize {\nusing u64 = uint64_t;\n\
    \ntemplate <typename mint>\nbool miller_rabin(u64 n, vector<u64> as) {\n  if (mint::get_mod()\
    \ != n) mint::set_mod(n);\n  u64 d = n - 1;\n  while (~d & 1) d >>= 1;\n  mint\
    \ e{1}, rev{int64_t(n - 1)};\n  for (u64 a : as) {\n    if (n <= a) break;\n \
    \   u64 t = d;\n    mint y = mint(a).pow(t);\n    while (t != n - 1 && y != e\
    \ && y != rev) {\n      y *= y;\n      t *= 2;\n    }\n    if (y != rev && t %\
    \ 2 == 0) return false;\n  }\n  return true;\n}\n\nbool is_prime(u64 n) {\n  if\
    \ (~n & 1) return n == 2;\n  if (n <= 1) return false;\n  if (n < (1LL << 30))\n\
    \    return miller_rabin<ArbitraryLazyMontgomeryModInt>(n, {2, 7, 61});\n  else\n\
    \    return miller_rabin<montgomery64>(\n        n, {2, 325, 9375, 28178, 450775,\
    \ 9780504, 1795265022});\n}\n\ntemplate <typename mint, typename T>\nT pollard_rho(T\
    \ n) {\n  if (~n & 1) return 2;\n  if (is_prime(n)) return n;\n  if (mint::get_mod()\
    \ != n) mint::set_mod(n);\n  mint R, one = 1;\n  auto f = [&](mint x) { return\
    \ x * x + R; };\n  auto rnd = [&]() { return rng() % (n - 2) + 2; };\n  while\
    \ (1) {\n    mint x, y, ys, q = one;\n    R = rnd(), y = rnd();\n    T g = 1;\n\
    \    constexpr int m = 128;\n    for (int r = 1; g == 1; r <<= 1) {\n      x =\
    \ y;\n      for (int i = 0; i < r; ++i) y = f(y);\n      for (int k = 0; g ==\
    \ 1 && k < r; k += m) {\n        ys = y;\n        for (int i = 0; i < m && i <\
    \ r - k; ++i) q *= x - (y = f(y));\n        g = inner::gcd<T>(q.get(), n);\n \
    \     }\n    }\n    if (g == n) do\n        g = inner::gcd<T>((x - (ys = f(ys))).get(),\
    \ n);\n      while (g == 1);\n    if (g != n) return g;\n  }\n  exit(1);\n}\n\n\
    vector<u64> inner_factorize(u64 n) {\n  if (n <= 1) return {};\n  u64 p;\n  if\
    \ (n <= (1LL << 30))\n    p = pollard_rho<ArbitraryLazyMontgomeryModInt, uint32_t>(n);\n\
    \  else\n    p = pollard_rho<montgomery64, uint64_t>(n);\n  if (p == n) return\
    \ {p};\n  auto l = inner_factorize(p);\n  auto r = inner_factorize(n / p);\n \
    \ copy(begin(r), end(r), back_inserter(l));\n  return l;\n}\n\nvector<u64> factorize(u64\
    \ n) {\n  auto ret = inner_factorize(n);\n  sort(begin(ret), end(ret));\n  return\
    \ ret;\n}\n\n}  // namespace fast_factorize\nusing fast_factorize::factorize;\n\
    using fast_factorize::is_prime;\n\n/**\n * @brief \u9AD8\u901F\u7D20\u56E0\u6570\
    \u5206\u89E3(Miller Rabin/Pollard's Rho)\n * @docs docs/prime/fast-factorize.md\n\
    \ */\n#line 9 \"modulo/mod-kth-root.hpp\"\n\nnamespace kth_root_mod {\n\n// fast\
    \ BS-GS\ntemplate <typename T>\nstruct Memo {\n  Memo(const T &g, int s, int period)\n\
    \      : size(1 << __lg(min(s, period))),\n        mask(size - 1),\n        period(period),\n\
    \        vs(size),\n        os(size + 1) {\n    T x(1);\n    for (int i = 0; i\
    \ < size; ++i, x *= g) os[x.get() & mask]++;\n    for (int i = 1; i < size; ++i)\
    \ os[i] += os[i - 1];\n    x = 1;\n    for (int i = 0; i < size; ++i, x *= g)\
    \ vs[--os[x.get() & mask]] = {x, i};\n    gpow = x;\n    os[size] = size;\n  }\n\
    \  int find(T x) const {\n    for (int t = 0; t < period; t += size, x *= gpow)\
    \ {\n      for (int m = (x.get() & mask), i = os[m]; i < os[m + 1]; ++i) {\n \
    \       if (x == vs[i].first) {\n          int ret = vs[i].second - t;\n     \
    \     return ret < 0 ? ret + period : ret;\n        }\n      }\n    }\n    assert(0);\n\
    \  }\n  T gpow;\n  int size, mask, period;\n  vector<pair<T, int> > vs;\n  vector<int>\
    \ os;\n};\n\nusing inner::gcd;\nusing inner::inv;\nusing inner::modpow;\ntemplate\
    \ <typename INT, typename LINT, typename mint>\nmint pe_root(INT c, INT pi, INT\
    \ ei, INT p) {\n  if (mint::get_mod() != decltype(mint::a)(p)) mint::set_mod(p);\n\
    \  INT s = p - 1, t = 0;\n  while (s % pi == 0) s /= pi, ++t;\n  INT pe = 1;\n\
    \  for (INT _ = 0; _ < ei; ++_) pe *= pi;\n\n  INT u = inv(pe - s % pe, pe);\n\
    \  mint mc = c, one = 1;\n  mint z = mc.pow((s * u + 1) / pe);\n  mint zpe = mc.pow(s\
    \ * u);\n  if (zpe == one) return z;\n  assert(t > ei);\n  \n  mint vs;\n  {\n\
    \    INT ptm1 = 1;\n    for (INT _ = 0; _ < t - 1; ++_) ptm1 *= pi;\n    for (mint\
    \ v = 2;; v += one) {\n      vs = v.pow(s);\n      if (vs.pow(ptm1) != one) break;\n\
    \    }\n  }\n\n  mint vspe = vs.pow(pe);\n  INT vs_e = ei;\n  mint base = vspe;\n\
    \  for (INT _ = 0; _ < t - ei - 1; _++) base = base.pow(pi);\n  Memo<mint> memo(base,\
    \ (INT)(sqrt(t - ei) * sqrt(pi)) + 1, pi);\n\n  while (zpe != one) {\n    mint\
    \ tmp = zpe;\n    INT td = 0;\n    while (tmp != 1) ++td, tmp = tmp.pow(pi);\n\
    \    INT e = t - td;\n    while (vs_e != e) {\n      vs = vs.pow(pi);\n      vspe\
    \ = vspe.pow(pi);\n      ++vs_e;\n    }\n\n    // BS-GS ... find (zpe * ( vspe\
    \ ^ n ) ) ^( p_i ^ (td - 1) ) = 1\n    mint base_zpe = zpe.inverse();\n    for\
    \ (INT _ = 0; _ < td - 1; _++) base_zpe = base_zpe.pow(pi);\n    INT bsgs = memo.find(base_zpe);\n\
    \n    z *= vs.pow(bsgs);\n    zpe *= vspe.pow(bsgs);\n  }\n  return z;\n}\n\n\
    template <typename INT, typename LINT, typename mint>\nINT inner_kth_root(INT\
    \ a, INT k, INT p) {\n  a %= p;\n  if (k == 0) return a == 1 ? a : -1;\n  if (a\
    \ <= 1 || k <= 1) return a;\n  assert(p > 2);\n  if (mint::get_mod() != decltype(mint::a)(p))\
    \ mint::set_mod(p);\n  INT g = gcd(p - 1, k);\n  if (modpow<INT, LINT>(a, (p -\
    \ 1) / g, p) != 1) return -1;\n  a = mint(a).pow(inv(k / g, (p - 1) / g)).get();\n\
    \  unordered_map<INT, int> fac;\n  for (auto &f : factorize(g)) fac[f]++;\n  if\
    \ (mint::get_mod() != decltype(mint::a)(p)) mint::set_mod(p);\n  for (auto pp\
    \ : fac)\n    a = pe_root<INT, LINT, mint>(a, pp.first, pp.second, p).get();\n\
    \  return a;\n}\n\nint64_t kth_root(int64_t a, int64_t k, int64_t p) {\n  if (max({a,\
    \ k, p}) < (1LL << 30))\n    return inner_kth_root<int32_t, int64_t, ArbitraryLazyMontgomeryModInt>(a,\
    \ k,\n                                                                       \
    \    p);\n  else\n    return inner_kth_root<int64_t, __int128_t, montgomery64>(a,\
    \ k, p);\n}\n\n}  // namespace kth_root_mod\nusing kth_root_mod::kth_root;\n\n\
    /**\n * @brief kth root(Tonelli-Shanks algorithm)\n * @docs docs/modulo/mod-kth-root.md\n\
    \ */\n#line 5 \"verify/verify-yosupo-math/yosupo-kth-root-mod.test.cpp\"\n\nvoid\
    \ solve() {\n  ini(T);\n  rep(_, T) {\n    inl(K, Y, P);\n    out(kth_root(Y,\
    \ K, P));\n  }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/kth_root_mod\"\n\n#include\
    \ \"../../competitive-template.hpp\"\n#include \"../../modulo/mod-kth-root.hpp\"\
    \n\nvoid solve() {\n  ini(T);\n  rep(_, T) {\n    inl(K, Y, P);\n    out(kth_root(Y,\
    \ K, P));\n  }\n}"
  dependsOn:
  - competitive-template.hpp
  - modulo/mod-kth-root.hpp
  - inner/inner_math.hpp
  - modint/arbitrary-prime-modint.hpp
  - modint/modint-montgomery64.hpp
  - prime/fast-factorize.hpp
  - misc/rng.hpp
  isVerificationFile: true
  path: verify/verify-yosupo-math/yosupo-kth-root-mod.test.cpp
  requiredBy: []
  timestamp: '2020-10-17 00:29:44+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/verify-yosupo-math/yosupo-kth-root-mod.test.cpp
layout: document
redirect_from:
- /verify/verify/verify-yosupo-math/yosupo-kth-root-mod.test.cpp
- /verify/verify/verify-yosupo-math/yosupo-kth-root-mod.test.cpp.html
title: verify/verify-yosupo-math/yosupo-kth-root-mod.test.cpp
---