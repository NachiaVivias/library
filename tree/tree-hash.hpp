#pragma once

#include "../inner/inner-hash.hpp"

template <typename G>
struct TreeHash {
  using Hash = inner::Hash<3>;

  const G& g;
  int n;
  vector<Hash> hash;
  vector<int> depth;

  static vector<Hash>& xs() {
    static vector<Hash> _xs;
    return _xs;
  }

  TreeHash(const G& _g, int root = 0) : g(_g), n(g.size()) {
    hash.resize(n);
    depth.resize(n, 0);
    while ((int)xs().size() <= n) xs().push_back(Hash::get_basis());
    dfs(root, -1);
  }

 private:
  int dfs(int c, int p) {
    int dep = 0;
    for (auto& d : g[c]) {
      if (d != p) dep = max(dep, dfs(d, c) + 1);
    }
    Hash x = xs()[dep], h = Hash::set(1);
    for (auto& d : g[c]) {
      if (d != p) h = h * (x + hash[d]);
    }
    hash[c] = h;
    return depth[c] = dep;
  }
};

/**
 * @brief 根付き木のハッシュ
 */
