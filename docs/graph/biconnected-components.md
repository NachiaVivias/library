## Biconnected Components

### 概要

無向グラフを biconnected components に分解し、各成分を辺集合で表現する。

- **関節点**とは、頂点であって、その頂点とそれに隣接する辺を除くと連結成分が非連結になるものである。
- 無向グラフが **biconnected** であるとは、連結で、関節点を持たないことである。
- **biconnected component** とは、 biconnected な部分グラフで極大なものである。

自己ループでない各辺について、それを含む二重連結成分は一意である。

### 使い方

実体は構造体テンプレート`BiConnectedComponents`である。

#### 継承

`LowLink<G>`を継承する。これによる機能の使い方は Lowlink のドキュメントを参照すること。

#### メンバ関数

- `BiConnectedComponents<G>(const G &_g)`: 

  コンストラクタ。型`G`は`UnweightedGraph`または`vector<vector<I>>` (`I`は整数型)で、引数`_g`は無向グラフの隣接リストである。
  
  実行すると、メンバ変数に出力が格納される。
  
  計算量$\mathrm{O}(N+M)$ ($N$は頂点数、$M$は辺数)

#### メンバ変数

- `vector<vector<pair<int, int> > > bc`:

  `bc[i]`は、ある biconnected component に含まれる辺の集合。各辺は両端の頂点の番号($0$-indexed)で表される。多重辺は$1$つにまとめられる。

### 注意点

- グラフが連結でない場合、すべての連結成分を処理し、答えをまとめて出力する。
- 自己ループによって関節点の集合は変化せず、自己ループは例外的にどの biconnected component にも含まれない。
- 再帰関数でDFSをするので、スタックサイズが小さすぎると利用できない。
