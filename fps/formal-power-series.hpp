#pragma once
#ifndef Nyaan_template
#include "../competitive-template.hpp"
#endif

template <typename mint, bool NTT_friendly = true, bool const_mod = true>
struct FormalPowerSeries : vector<mint> {
  using vector<mint>::vector;
  using FPS = FormalPowerSeries;

  FPS &operator+=(const FPS &r) {
    if (r.size() > this->size()) this->resize(r.size());
    for (int i = 0; i < (int)r.size(); i++) (*this)[i] += r[i];
    return *this;
  }

  FPS &operator+=(const mint &r) {
    if (this->empty()) this->resize(1);
    (*this)[0] += r;
    return *this;
  }

  FPS &operator-=(const FPS &r) {
    if (r.size() > this->size()) this->resize(r.size());
    for (int i = 0; i < (int)r.size(); i++) (*this)[i] -= r[i];
    shrink();
    return *this;
  }

  FPS &operator-=(const mint &r) {
    if (this->empty()) this->resize(1);
    (*this)[0] -= r;
    shrink();
    return *this;
  }

  FPS &operator*=(const FPS &r) {
    if (this->empty() || r.empty()) {
      this->clear();
      return *this;
    }
    if constexpr (NTT_friendly) {
      static NTT<mint> ntt;
      static_assert(ntt.level > 20);
      auto ret = ntt.multiply(*this, r);
      return *this = FPS(ret.begin(), ret.end());
    } else if constexpr (const_mod) {
      auto ret = ArbitraryNTT::multiply<mint::get_mod()>(*this, r);
      return *this = FPS(ret.begin(), ret.end());
    } else {
      auto ret = ArbitraryNTT::multiply(*this, r, mint::get_mod());
      return *this = FPS(ret.begin(), ret.end());
    }
  }

  FPS &operator*=(const mint &v) {
    for (int k = 0; k < (int)this->size(); k++) (*this)[k] *= v;
    return *this;
  }

  FPS &operator/=(const FPS &r) {
    if (this->size() < r.size()) {
      this->clear();
      return *this;
    }
    int n = this->size() - r.size() + 1;
    return *this = ((*this).rev().pre(n) * r.rev().inv(n)).pre(n).rev();
  }

  FPS &operator%=(const FPS &r) { return *this -= *this / r * r; }
  FPS operator+(const FPS &r) const { return FPS(*this) += r; }
  FPS operator+(const mint &v) const { return FPS(*this) += v; }
  FPS operator-(const FPS &r) const { return FPS(*this) -= r; }
  FPS operator-(const mint &v) const { return FPS(*this) -= v; }
  FPS operator*(const FPS &r) const { return FPS(*this) *= r; }
  FPS operator*(const mint &v) const { return FPS(*this) *= v; }
  FPS operator/(const FPS &r) const { return FPS(*this) /= r; }
  FPS operator%(const FPS &r) const { return FPS(*this) %= r; }
  FPS operator-() const {
    FPS ret(this->size());
    for (int i = 0; i < (int)this->size(); i++) ret[i] = -(*this)[i];
    return ret;
  }

  void shrink() {
    while (this->size() && this->back() == mint(0)) this->pop_back();
  }

  FPS rev() const {
    FPS ret(*this);
    reverse(begin(ret), end(ret));
    return ret;
  }

  FPS dot(FPS r) const {
    FPS ret(min(this->size(), r.size()));
    for (int i = 0; i < (int)ret.size(); i++) ret[i] = (*this)[i] * r[i];
    return ret;
  }

  FPS pre(int sz) const {
    return FPS(begin(*this), begin(*this) + min((int)this->size(), sz));
  }

  FPS operator>>(int sz) const {
    if (this->size() <= sz) return {};
    FPS ret(*this);
    ret.erase(ret.begin(), ret.begin() + sz);
    return ret;
  }

  FPS operator<<(int sz) const {
    FPS ret(*this);
    ret.insert(ret.begin(), sz, mint(0));
    return ret;
  }

  FPS diff() const {
    const int n = (int)this->size();
    FPS ret(max(0, n - 1));
    for (int i = 1; i < n; i++) ret[i - 1] = (*this)[i] * mint(i);
    return ret;
  }

  FPS integral() const {
    const int n = (int)this->size();
    FPS ret(n + 1);
    ret[0] = mint(0);
    for (int i = 0; i < n; i++) ret[i + 1] = (*this)[i] / mint(i + 1);
    return ret;
  }

  mint eval(mint x) const {
    mint r = 0, w = 1;
    for (auto &v : *this) r += w * v, w *= x;
    return r;
  }

  FPS inv(int deg = -1) const {
    assert((*this)[0] != mint(0));
    if (deg == -1) deg = (*this).size();
    FPS ret({mint(1) / (*this)[0]});
    for (int i = 1; i < deg; i <<= 1)
      ret = (ret + ret - ret * ret * (*this).pre(i << 1)).pre(i << 1);
    return ret.pre(deg);
  }

  FPS log(int deg = -1) const {
    assert((*this)[0] == mint(1));
    if (deg == -1) deg = (int)this->size();
    return (this->diff() * this->inv()).pre(deg - 1).integral();
  }

  FPS exp(int deg = -1) const {
    assert((*this)[0] == mint(0));
    if (deg == -1) deg = (int)this->size();
    FPS ret({T(1)});
    for (int i = 1; i < deg; i <<= 1) {
      ret = (ret * (pre(i << 1) + mint(1) - ret.log(i << 1))).pre(i << 1);
    }
    return ret.pre(deg);
  }

  FPS pow(int64_t k, int deg = -1) const {
    const int n = (int)this->size();
    if (deg == -1) deg = n;
    for (int i = 0; i < n; i++) {
      if ((*this)[i] != mint(0)) {
        if (i * k > deg) return FPS(deg, mint(0));
        mint rev = mint(1) / (*this)[i];
        FPS ret = (((*this * rev) >> i).log() * k).exp() * ((*this)[i].pow(k));
        ret = (ret << (i * k)).pre(deg);
        if (ret.size() < deg) ret.resize(deg, mint(0));
        return ret;
      }
    }
    return *this;
  }

  // TODO: 作る
  // FPS sqrt(int deg = -1) const {}
};