#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../template/template.hpp"
//
#include "../../misc/timer.hpp"
#include "../../modulo/strassen.hpp"

using namespace FastMatProd;

void time_test() {
  int N = 1024;
  int P = N, M = N;
  mt19937 rng(58);
  vvm s(N, vm(P)), t(P, vm(M));
  for (int i = 0; i < N; i++)
    for (int j = 0; j < P; j++) s[i][j] = rng() % 998244353;
  for (int i = 0; i < P; i++)
    for (int j = 0; j < M; j++) t[i][j] = rng() % 998244353;
  vvm u, u2, u3;
  Timer timer;

  int loop = 5;
  timer.reset();
  for (int i = 0; i < loop; i++) u = FastMatProd::strassen(s, t);
  cerr << "strassen " << (timer.elapsed() / loop) << endl;

  timer.reset();
  u2 = FastMatProd::naive_mul(s, t);
  cerr << "naive " << timer.elapsed() << endl;

  timer.reset();
  for (int i = 0; i < loop; i++) u3 = FastMatProd::block_dec(s, t);
  cerr << "block dec " << (timer.elapsed() / loop) << endl;

  assert(u == u2);
  assert(u == u3);
}

void debug_test(int max = 500, int loop = 20) {
  int N, P, M;
  mt19937 rng(58);
  while (loop--) {
    N = rng() % max + 1;
    M = rng() % max + 1;
    P = rng() % max + 1;
    vvm s(N, vm(P)), t(P, vm(M));
    for (int i = 0; i < N; i++)
      for (int j = 0; j < P; j++) s[i][j] = rng() % 998244353;
    for (int i = 0; i < P; i++)
      for (int j = 0; j < M; j++) t[i][j] = rng() % 998244353;
    auto u = strassen(s, t);
    auto u2 = naive_mul(s, t);
    auto u3 = block_dec(s, t);
    if (u != u2) {
      cerr << "ng u1 " << N << " " << P << " " << M << endl;
      exit(1);
    } else if (u != u3) {
      cerr << "ng u1 " << N << " " << P << " " << M << endl;
      exit(1);
    } else {
      cerr << "ok " << N << " " << P << " " << M << endl;
    }
  }
  cerr << "all ok" << endl;
}

void Nyaan::solve() {
  // time_test();
  debug_test();
  debug_test(32, 1000);

  int a, b;
  cin >> a >> b;
  cerr << a + b << endl;
}