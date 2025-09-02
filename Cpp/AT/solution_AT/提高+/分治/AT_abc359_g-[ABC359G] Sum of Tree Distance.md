# [ABC359G] Sum of Tree Distance

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc359/tasks/abc359_g

$ N $ 頂点の木が与えられます。 $ i $ 番目の辺は頂点 $ u_i $ と頂点 $ v_i $ を双方向に結んでいます。

また、整数列 $ A=(A_1,\ldots,A_N) $ が与えられます。

ここで $ f(i,j) $ を以下で定義します。

- $ A_i=A_j $ のとき、$ f(i,j) $ は頂点 $ i $ から頂点 $ j $ に移動する場合に通る辺数の最小値とする。$ A_i\neq\ A_j $ のとき $ f(i,j)=0 $ とする。
 
次の式の値を求めてください。

$ \displaystyle\ \sum_{i=1}^{N-1}\sum_{j=i+1}^N\ f(i,j) $

## 说明/提示

### 制約

- $ 2\leq\ N\leq\ 2\times\ 10^5 $
- $ 1\leq\ u_i,v_i\ \leq\ N $
- $ 1\leq\ A_i\leq\ N $
- 入力されるグラフは木
- 入力される数値は全て整数
 
### Sample Explanation 1

$ f(1,4)=2,f(2,3)=2 $ となります。また、それ以外の $ i,j\ (1\leq\ i\ <\ j\leq\ N) $ について $ f(i,j)=0 $ なので、答えは $ 2+2=4 $ です。

## 样例 #1

### 输入

```
4
3 4
4 2
1 2
2 1 1 2```

### 输出

```
4```

## 样例 #2

### 输入

```
8
8 6
3 8
1 4
7 8
4 5
3 4
8 2
1 2 2 2 3 1 1 3```

### 输出

```
19```

# 题解

## 作者：Rosabel (赞：11)

本题解为根号分治做法（与官方题解相同）。其他做法请参考其他题解。

对于每个节点都有颜色的条件，很容易想到根号分治。分两种情况考虑。

设 $sz_i$ 为颜色 $i$ 的出现次数。当 $sz_i\le B$ 时，容易想到枚举每一对两个节点 $u,v$ 均为颜色 $i$ 的二元组 $(u,v)$，算出距离：

$$d(u,v)=dep_u+dep_v-2\times dep_{lca}$$

其中，$lca$ 可以 $\Theta(1)$ 算。将原树用欧拉序展开（令在欧拉序中第一次出现节点 $x$ 的位置为 $in_x$，最后一次出现 $x$ 的位置为 $out_x$），那么在区间 $[\min(in_u,in_v),\max(out_u,out_v)]$ 中必然出现 $lca$，且在区间中 $dep$ 最小值必然为 $dep_{lca}$（欧拉序遍历不会出现访问一棵子树两次的情况，故不会出现 $lca$ 的祖先以及 $lca$ 所在子树以外的节点）。

回到原式子，那么这段区间的 $dep$ 最小值恰为我们唯一要求的信息。问题转换为在欧拉序 $dep$ 序列中查询区间最小值。经典的区间 RMQ 问题，用 $\Theta(n\log n)——\Theta(1)$ 的倍增可求出。时间复杂度 $\Theta(n\log n+nB)$。

$sz_i\gt B$ 时，直接遍历子树利用换根 dp 的思想维护单个信息即可。即维护子树内有多少个颜色为 $i$ 的节点，一条从祖先连向该节点的边的贡献为子树内的节点 $\times$ 子树外的节点（可以用总节点个数 - 子树内个数求出）。时间复杂度为 $\Theta(\frac{n^2}{B})$。

总时间复杂度为 $\Theta(n\log n+nB+\frac{n^2}{B})$。当 $B$ 取 $\sqrt n$ 时有最优复杂度 $\Theta(n\log n+n\sqrt n)$。

[code](https://atcoder.jp/contests/abc359/submissions/54852178)

---

## 作者：yhylivedream (赞：10)

听说有人写根号分治和虚树。

## 分析

拟定 $1$ 为树根， 记 $x$ 子树颜色出现次数数组为 $c_x$。

考虑边对颜色 $col$ 的贡献，贡献即为 $c_{x,col}\times(c_{1,col}-c_{x,col})$ 累加所有颜色贡献即可，合并父子颜色出现次数数组时启发式合并。

颜色出现次数数组可以用 map 实现，顺带提一句 swap 两个 STL 是 $O(1)$ 的，只需交换头迭代器。

## 代码

```cpp
#include <bits/stdc++.h>

using namespace std;
using LL = long long;

const LL kMaxN = 2e5 + 5;

struct V {
  vector<LL> e;
  unordered_map<LL, LL> m;
  LL v, c;
} v[kMaxN];
LL n, ans, c[kMaxN];

void S(LL f, LL x) {
  v[x].m[v[x].c] = 1;
  v[x].v = c[v[x].c] - 1;
  for (LL i : v[x].e) {
    if (i != f) {
      S(x, i);
      if (v[i].m.size() > v[x].m.size()) {
        swap(v[i].m, v[x].m), swap(v[i].v, v[x].v);
      }
      for (auto p : v[i].m) {
        v[x].v -= v[x].m[p.first] * (c[p.first] - v[x].m[p.first]);
        v[x].m[p.first] += p.second;
        v[x].v += v[x].m[p.first] * (c[p.first] - v[x].m[p.first]);
      }
    }
  }
  ans += v[x].v;
}

signed main() {
  cin >> n;
  for (LL i = 1, x, y; i < n; i++) {
    cin >> x >> y, v[x].e.push_back(y), v[y].e.push_back(x);
  }
  for (LL i = 1; i <= n; i++) {
    cin >> v[i].c, c[v[i].c]++;
  }
  S(0, 1), cout << ans;
}
```

---

## 作者：Expert_Dream (赞：9)

这题很多做法，来一个比较好想的**根号分治**，但是比较卡常，~~卡了我 5 个小时~~。顺便讲讲卡常技巧。

首先，我们设有 $m$ 种不同的 $A_i$。每一种相同的 $A_i$ 有  $B_j$ 个。显然得到 $\sum B = n$。

因此，这很根号分治。

也就是说，如果 $B_j \le \sqrt{n}$ 和 $B_j > \sqrt{n}$ 分别处理。使用不同的算法。

如果 $B_j \le \sqrt{n}$，由于较小可以暴力解决。暴力枚举两个点，用倍增 LCA 来计算他们的距离。有大佬说这里可以 $O(1)$ 求 LCA，但我不会。因此这里用到倍增。考虑复杂度。如果都是这一类，那么总的时间复杂度应该是 $O(\dfrac{n}{B_j} \times B_j ^ 2 \times \log n )$。化简得 $O(n \times B_j \times \log n )$，最大也就是 $O(n \times \sqrt{n} \times \log n) $。


对于 $B_j > \sqrt{n}$ 的部分，考虑树形 DP。每一个 $j$ 用一个 $O(n)$ 的树形 DP。具体的，我们设 $g_i$ 代表以 $i$ 的子树内，是这个种类的点的个数。设 $f_i$ 代表以 $i$ 的子树内，所有这个种类的点到 $f_i$ 的距离之和。转移就是，对于每一个点 $u$，它可以到达的点 $v$，则 $g_u = \sum g_v + 1,f_u = \sum f_v + g_v$。对于如何计算贡献？显然对于两个点 $(u,v)$ 的距离应该是 $dis_{u,lca(u,v)} + dis_{v,lca(u,v)}$，$dis$ 即树上两点的距离，我们尝试将 $dis_{u,lca(u,v)}$ 和 $dis_{v,lca(u,v)}$ 两个部分拆开来。这就容易了，增加的贡献就是 $\sum f_v \times (g_u - g_v)$。为什么呢？因为对于 $v$ 子树内的点会与其他在 $u$ 子树的点但又不在 $v$ 子树内的点产生贡献，于是就得到了上面的式子。那么树形 DP 时间复杂度 $O(n)$，由于本部分最多出现 $\sqrt{n}$ 次，所以时间复杂度应该为 $O(n \sqrt{n})$。

所以，本算法的时间复杂度最高是 $O(n \times \sqrt{n} \times \log n) $。

但是由于复杂度很紧张，所以我们卡常。

- 对于 $\sqrt{n}$ 替换成一个常数，对比出来最快的是多少，笔者试出来是 $200$ 相对是比较快的。来到这里，一般来说你的代码会在 TLE $2$ 个点到 $4$ 个点左右。如果没有，建议提高你的效率。

- 但是这还不够，笔者用了很多卡常的方法，例如火车头，inline，FastIO 读入，等等等。但是效果不明显，没什么必要。

- 另一个主要的卡常是合并成一个 DFS。将 $\sqrt{n}$ 个第二种情况所有种类合在一起，跑一个 DFS。减少回溯次数，效率提高许多。记住这很重要，第一次知道，DFS 回溯的代价如此高。大概是递归的劣势吧。但是这样带来的困难就是空间代价大。由于答案必须要记录 long long，所以你需要开一个 $n \sqrt{n}$ 那么大的数组，直接就 MLE 了，你被迫开 int，但是又会 WA。怎么办呢？考虑**时间换空间**。你 $\sqrt{n}$ 次 DFS 不行，时间太慢，$1$ 次 DFS 又不行，空间太大，那你是不是可以控制类似 $3$ DFS，这样就可以省去 $3$ 倍的空间。我这里用的是每一个 DFS 处理 $100$ 个种类。

终于，在简单的思维，复杂度卡常，拿下了这一题。


[link](https://atcoder.jp/contests/abc359/submissions/54866172)。

---

## 作者：WhisperingWillow (赞：5)

新做法。

根据颜色分类。

显然 $f(i,j)=dep_i+dep_j-2\times dep_{\operatorname{LCA}(i,j)}$。

显然统计 $i,j$ 的贡献是简单的。

则统计 $\operatorname{LCA}(i,j)$ 的贡献，则我们让 $1\sim i$ 的所有点都加一，统计所有 $1\sim i$ 的和，注意消除 $(i,i)$ 的贡献，这部分参考 P4211。

显然可以用树链剖分 $\mathcal O(n\log^2n)$ 解决。

---

## 作者：FFTotoro (赞：4)

该题为 [CF1725E](https://www.luogu.com.cn/problem/CF1725E) 弱化版。评价是 G 比 C 简单。

考虑使用虚树，把每种颜色的点抽出来建立虚树，在虚树上跑一遍 `dfs` 直接算贡献即可。具体地，考虑虚树上每一条边的贡献：对于这条边连接的两个子树，分别考虑两个子树内有多少个颜色为当前考察的颜色的点，然后乘上这条边的长度。

**虚树上一条边的长度定义为其连接的两个结点在原树中的距离**，这个可以通过预处理深度以及倍增处理 $\mathrm{lca}$ 来实现。正确性显然。

时限很大所以不怕大常数。

放代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
class virtual_tree{
  private:
    int n,k;
    vector<int> dep,dfn,f,e;
    vector<vector<int> > g,s;
  public:
    virtual_tree(vector<vector<int> > &t){
      n=t.size(),k=__lg(n),f.resize(n);
      dep.resize(n),dfn.resize(n),e.resize(n),g.resize(n);
      s.resize(n,vector<int>(k+1));
      int o=0;
      function<void(int,int)> dfs=[&](int u,int f){
        dfn[u]=o++,s[u][0]=f;
        for(int i=1;i<=k;i++)
          s[u][i]=s[s[u][i-1]][i-1];
        for(int i:t[u])
          if(i!=f)dep[i]=dep[u]+1,dfs(i,u);
      };
      dfs(0,0);
    }
    inline int lca(int u,int v){
      if(dep[u]<dep[v])swap(u,v);
      for(int i=k;~i;i--)
        if(dep[s[u][i]]>=dep[v])u=s[u][i];
      if(u==v)return u;
      for(int i=k;~i;i--)
        if(s[u][i]!=s[v][i])u=s[u][i],v=s[v][i];
      return s[u][0];
    }
    inline int build(vector<int> &c){
      auto v=c;
      sort(v.begin(),v.end(),[&](int x,int y){
        return dfn[x]<dfn[y];
      });
      int n0=v.size();
      for(int i=1;i<n0;i++)
        v.emplace_back(lca(v[i-1],v[i]));
      sort(v.begin(),v.end(),[&](int x,int y){
        return dfn[x]<dfn[y];
      });
      int n=unique(v.begin(),v.end())-v.begin(),s=0;
      for(int i=1;i<n;i++)
        g[lca(v[i-1],v[i])].emplace_back(v[i]);
      // 建立虚树
      for(int i:c)e[i]=1;
      function<void(int)> dfs=[&](int u){
        for(int i:g[u]){
          dfs(i),e[u]+=e[i];
          s+=e[i]*(c.size()-e[i])*(dep[i]-dep[u]);
        } // 跑贡献
      };
      dfs(v[0]);
      for(int i=0;i<n;i++)
        vector<int>().swap(g[v[i]]),e[v[i]]=0;
      // 记得清空
      return s;
    }
};
main(){
  ios::sync_with_stdio(false);
  int n,r=0; cin>>n;
  vector<int> a(n);
  vector<vector<int> > V(n),g(n);
  for(int i=1;i<n;i++){
    int u,v; cin>>u>>v;
    g[--u].emplace_back(--v);
    g[v].emplace_back(u);
  }
  for(int i=0;i<n;i++)
    cin>>a[i],V[--a[i]].emplace_back(i);
  virtual_tree t(g);
  for(int i=0;i<n;i++)
    if(V[i].size()>1)r+=t.build(V[i]);
  cout<<r<<endl;
  return 0;
}
```

---

## 作者：_determination_ (赞：3)

注意到不同颜色之间是没有贡献的，考虑将每个颜色分开考虑。

设 $a_{i,j}$ 为颜色 $i$ 的第 $j$ 个节点，第 $i$ 个颜色有 $len_i$ 个节点，则答案为：

$$
\sum_{c=1}^{n}\sum_{i=1}^{len_c}\sum_{j=i+1}^{len_c}f(a_{c,i},a_{c,j})
$$

把后面一坨拎出来，设两点之间的最近公共祖先为 $l_{i,j}$，$i$ 的深度为 $d_i$。

$$
(n-1)\sum_{i=1}^{n}d_i+\sum_{i=1}^{n}\sum_{j=i+1}^{n}d_{l_{i,j}}
$$

前面可以暴力算，考虑如何优化后面的部分。

以下的部分假定你会 $O(1)$ 求最近公共祖先。

- 暴力枚举

复杂度 $O(n^2)$，但是在每个颜色出现次数都很少的时候非常优秀。

- 深搜处理

对于一个颜色的复杂度为 $O(n)$，但是假如每个点都是一个颜色的时候总复杂度会退化到 $O(n^2)$。

具体的，我们在深搜的时候搜到一个节点 $x$ 我们就尝试统计有多少对节点以 $x$ 为最近公共祖先。

1. $x$ 是路径两端的一个节点。

子树内所有的点和 $x$ 的点对均以 $x$ 为最近公共祖先。

2. 路径的两端均在子树内。

在两个小子树里的点对都以 $x$ 为最近公共祖先，考虑枚举 $x$ 的两个儿子，这样是 $n^2$ 的，但显然可以用类似前缀和的方式做到 $O(n)$。

---

好了，这样我们就得到了两个最劣复杂度都是 $O(n^2)$ 的暴力。但是注意到这两个暴力在两个极端内表现得十分优良。

这代表什么？根号分治！

---

设根号分治的阈值为 $B$，当一个颜色的节点数小于 $B$ 的时候采用暴力法，否则采用深搜法。

复杂度为 $O(\dfrac{n}{B}B^2+\dfrac{n}{B}n)$，当 $B$ 取 $\sqrt{n}$ 时，复杂度平衡，为 $O(n\sqrt{n})$，可以通过。

---

## 作者：incra (赞：3)

### Solution
赛后补的。

考虑用启发式合并，用 map 直接维护每一个子树 $u$ 内每一个颜色 $c$ 的 $cnt_{u,c},s_{u,c}$，分别表示 $u$ 子树内颜色为 $c$ 的点数和点的深度之和。

考虑合并 $u$ 和其子节点 $v$ 对答案的贡献（此时 $v$ 还没有合并到 $u$ 上），那么对于一种颜色 $c$ 增加的答案就是 $cnt_{u,c}\times s_{v,c}+s_{u,c}\times cnt_{v,c}-2\times cnt_{u,c}\times cnt_{v,c}\times dep_{u}$，其中 $dep_u$ 为 $u$ 的深度。

解释一下这个式子：前面两个积算出所有颜色为 $c$ 的点到根节点的距离之和，然后减去多余的部分（这里就是 $u,v$ 的 LCA）。
### Code
```cpp
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <vector>
#include <stack>
#include <queue>
#include <bitset>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <cstring>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <cassert>
#define x first
#define y second
#define pb push_back
#define eb emplace_back
#define pf push_front
#define desktop "C:\\Users\\incra\\Desktop\\"
#define IOS ios :: sync_with_stdio (false),cin.tie (0),cout.tie (0)
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef pair <int,int> PII;
const int dx[] = {1,0,-1,0},dy[] = {0,-1,0,1};
template <typename T1,typename T2> bool tomax (T1 &x,T2 y) {
	if (y > x) return x = y,true;
	return false;
}
template <typename T1,typename T2> bool tomin (T1 &x,T2 y) {
	if (y < x) return x = y,true;
	return false;
}
LL power (LL a,LL b,LL p) {
	LL ans = 1;
	while (b) {
		if (b & 1) ans = ans * a % p;
		a = a * a % p;
		b >>= 1;
	}
	return ans;
}
int fastio = (IOS,0);
#define puts(s) cout << s << endl
const int N = 200010;
int n;
vector <int> g[N];
int c[N];
int dep[N];
map <int,pair <LL,LL> > mp[N];
LL ans;
void DFS1 (int u,int fa) {
	for (int v : g[u]) {
		if (v == fa) continue;
		dep[v] = dep[u] + 1;
		DFS1 (v,u);
	}
}
void merge (int u,int v) {
	if (mp[v].size () > mp[u].size ()) mp[u].swap (mp[v]);
	for (auto [x,y] : mp[v]) ans += y.y * mp[u][x].x + mp[u][x].y * y.x - 2 * mp[u][x].x * y.x * dep[u];
	for (auto [x,y] : mp[v]) mp[u][x].x += y.x,mp[u][x].y += y.y;
}
void DFS2 (int u,int fa) {
	mp[u][c[u]] = {1,dep[u]};
	for (int v : g[u]) {
		if (v == fa) continue;
		DFS2 (v,u);
		merge (u,v);
	}
}
int main () {
	cin >> n;
	for (int i = 1;i <= n - 1;i++) {
		int a,b;
		cin >> a >> b;
		g[a].pb (b),g[b].pb (a);
	}
	for (int i = 1;i <= n;i++) cin >> c[i];
	DFS1 (1,-1),DFS2 (1,-1);
	cout << ans << endl;
	return 0;
}
```

---

## 作者：Heldivis (赞：2)

# ABC359G

称 $A_i$ 为点 $i$ 的“颜色”，$S$ 为某一种颜色点的数量。

由于只有 $A_i = A_j$ 才有贡献，考虑对于每种颜色的点分开计算，则问题转化为：**求某些点两两到达的距离之和**。

有两个办法：

- 对一种颜色的点，暴力枚举两个点，使用 LCA 计算他们之间的距离，时间复杂度 $O(\sum S^2)$。

  ```cpp
  for (int i = 0; i < c[t].size(); i++)
    for (int j = i + 1; j < c[t].size(); j++)
      Lca::Dis(c[t][i], c[t][j]);
  ```

  但是如果所有点颜色相同，时间复杂度变成 $O(N^2)$，不能接受。

  

- 换根 DP，计算每条边两边点的数量，乘积就是这条边的贡献，**每种颜色**时间复杂度 $O(N)$。

  ```cpp
  void Dfs(int x, int fa) {
    if (w[x] == e) siz[x] = 1;
    for (int y : g[x]) {
      if (y == fa) continue;
      Dfs(y, x);
      siz[x] += siz[y];
    }
  }
  void Dp(int x, int fa) {
    if (siz[x] == 0) return;
    for (int y : g[x]) {
      if (y == fa) continue;
      res += 1ll * siz[y] * (siz[1] - siz[y]);
      Dp(y, x);
    }
  }
  ```

  但是如果所有点颜色不同，时间复杂度也是 $O(N^2)$。

发现：**LCA 方法适合点数较少的颜色，DP 适合点数较多的颜色，可以分开计算**。

时间复杂度为 $O(\dfrac NS\times S^2+\dfrac NS\times N)=O(NS+\dfrac {N^2}S)$。

当 $NS = \dfrac{N^2}S$，$S=\sqrt N$ 时，时间复杂度为 $O(N\sqrt N)$，大约是 $10^8$，能过。

提交记录： [*Submission*](https://atcoder.jp/contests/abc359/submissions/54914939)。

---

## 作者：f_hxr_ (赞：1)

第一次切 G，写篇题解纪念一下。~~早知道报 Rated 了。~~

考虑点分治。设我们当前处理的树的根是 $root$，则 $dep_{root}=0$。

对路径进行分类。第一种是其中一个端点为根的路径。第二种是端点不为根但经过根的路径。第三种是在子树内的路径。

最后一种可以用点分治当成子问题递归解决。我们主要解决前两种。

第二种也很好办。我们依次对 $root$ 的每一个子树DFS。我们开两个桶 $sum$ 和 $tot$。其中 $sum_i$ 表示所有颜色为 $i$ 的结点的深度的**和**。$tot_i$ 表示所有颜色为 $i$ 的结点的**数量**。

注意，为了不重不漏，我们要先遍历子树，再用子树里的结点更新 $sum$ 和 $tot$。

假设我们在 DFS 的时候搜到一个点 $u$，它的颜色为 $col$。一方面，由于我们之前前有 $tot_{col}$ 个结点能和它匹配，所以答案要加上 $ tot_{col} \times dep_u$。另一方面，之前所有颜色为 $col$ 的结点也都可以和 $u$ 匹配，所以答案还要再加上 $sum_{col}$。

遍历完之后再用子树内的结点更新 $sum$ 和 $tot$ 即可。当然，你可以先开一个小桶，再把小桶和大桶合并，我就是这样做的。

第一种也很好办。我们提前 $root$ 的颜色记下来。在 DFS 的过程中，每搜到一个点 $u$ 都看一下 $u$ 的颜色与 $root$ 的颜色是否相同，如果相同就把 $u$ 到根的距离，也就是 $dep_u$ 计入答案即可。

注意要随地大小 `long long`。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL; 
const int inf=1e9+7;
const int maxn=2e5+7;
int N,a[maxn];
LL ans;
int head[maxn<<1],nxt[maxn<<1],to[maxn<<1],cnt_edge;
inline void AddEdge(int u,int v){nxt[++cnt_edge]=head[u];to[cnt_edge]=v;head[u]=cnt_edge;}
int cut[maxn],cz[maxn];
long long dep[maxn];
long long tot1[maxn],bug1[maxn],color1[maxn],cnt_color1;//主桶
long long tot2[maxn],bug2[maxn],color2[maxn],cnt_color2;//子桶
int rootcolor; 
void getroot(int u,int fa,int &minsize,int &ret,int ALL){
	cz[u]=1;int maxsize=-1;
	for(int i=head[u];i;i=nxt[i]){
		int v=to[i];if(v==fa||cut[v])continue;
		getroot(v,u,minsize,ret,ALL);cz[u]+=cz[v];
		maxsize=max(maxsize,cz[v]);
	}
	maxsize=max(maxsize,ALL-cz[u]);
	if(maxsize<minsize)minsize=maxsize,ret=u;
}
int getroot(int u,int ALL){int minsize=inf,ret;getroot(u,0,minsize,ret,ALL);return ret;}
void dfs(int u,int fa){
	dep[u]=dep[fa]+1;
	
	if(bug2[a[u]]==0)color2[++cnt_color2]=a[u];
	bug2[a[u]]+=dep[u];
	tot2[a[u]]++;
	
	if(a[u]==rootcolor)ans+=dep[u];
	ans+=1LL*dep[u]*tot1[a[u]]+bug1[a[u]];
	
	for(int i=head[u];i;i=nxt[i]){
		int v=to[i];if(v==fa||cut[v])continue;
		dfs(v,u);
	}
}
void calc(int u){
	dep[u]=0;
	rootcolor=a[u];
	for(int i=head[u];i;i=nxt[i]){
		int v=to[i];if(cut[v])continue;
		dfs(v,u);
		for(int j=1;j<=cnt_color2;j++){
			if(bug1[color2[j]]==0)
				color1[++cnt_color1]=color2[j];
			bug1[color2[j]]+=bug2[color2[j]];
			bug2[color2[j]]=0;
			tot1[color2[j]]+=tot2[color2[j]];
			tot2[color2[j]]=0;
		}
		cnt_color2=0;
	}
	for(int i=1;i<=cnt_color1;i++)
		bug1[color1[i]]=tot1[color1[i]]=0;
	cnt_color1=0;
}
void solve(int u){
	cut[u]=1;calc(u);
	for(int i=head[u];i;i=nxt[i]){
		int v=to[i];if(cut[v])continue;
		solve(getroot(v,cz[v]));
	}
}
int main(){
	scanf("%d",&N);
	for(int i=1,u,v;i<N;i++)scanf("%d %d",&u,&v),AddEdge(u,v),AddEdge(v,u);
	for(int i=1;i<=N;i++)scanf("%d",&a[i]);
	solve(getroot(1,N));
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：kkxacj (赞：1)

#### 思路

看到求树上两点间的距离，考虑点分治。

[P3806 【模板】点分治 1](https://www.luogu.com.cn/problem/P3806)

建议先把模板题打了在来打这道题。

点分治，其思想就是如果要求两点间的距离和，假设以 $i$ 为根，就等价于每个子树内两点间的距离和**经过第 $i$ 个点**的两点间的距离，这里 $a$ 到 $b$ 的距离是 **$a$ 到 $b$ 的简单路径**。

**树的重心**的定义：若树以 $i$ 为根它的最大子树最小，那 $i$ 就是该树的重心。

点分治就是每次以树的重心为根来进行上面提到的计算的，因为树的重心有一个很重要的性质，那就是**以树的重心为根时，所有子树的大小都不超过整棵树大小的一半**，这样递归下去复杂度就可以保证了。

对于本题，由于有颜色，在每次求答案时可以按颜色分成多段，分别算答案。

由于只用算贡献，对于每次以 $i$ 为树 $j$ 的根，直接对于每个点算出到 $i$ 的深度，然后乘上和它不在一个子树内且颜色跟它一样的点的个数就行了。


**code**
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 2e5+10;
int n,m,siz[N],head[N],t[N],c[N],cnt,x,y,z,ma,ma1,dep[N],v[N],sum[N],cnt1,k,ans,cnt2;
struct w1
{
	int z,id,col;
}b[N];
bool cmp(w1 x,w1 y)
{
	if(x.col != y.col) return x.col < y.col;
	return x.z < y.z;
}
struct w 
{
	int nxt,to;
}a[N*2];
inline void add(int x,int y)
{
	a[++cnt].to = y;
	a[cnt].nxt = head[x];
	head[x] = cnt;
}
inline void dfs1(int x,int fa,int xn)
{
	siz[x] = 1; int mi = 0; 
	for(int i = head[x];i;i = a[i].nxt)
		if(a[i].to != fa && !v[a[i].to])
		{
			dfs1(a[i].to,x,xn); siz[x] += siz[a[i].to];
			if(siz[a[i].to] > mi) mi = siz[a[i].to];
		}
	if(xn - siz[x] > mi) mi = xn - siz[x];
	if(!ma1 || mi < ma) ma = mi,ma1 = x;
	return;
}
inline void dfs(int x,int fa,int dep,int id)
{
	b[++cnt1].z = dep; b[cnt1].id = id; b[cnt1].col = c[x];
	for(int i = head[x];i;i = a[i].nxt)
		if(a[i].to != fa && !v[a[i].to])
			dfs(a[i].to,x,dep+1,id); 
	return;
}
inline void solve(int x)
{
	cnt1 = 0;
	b[++cnt1].z = 0;
	b[cnt1].id = x;
	b[cnt1].col = c[x];
	for(int i = head[x];i;i = a[i].nxt)
	{
		if(v[a[i].to]) continue;
		dfs(a[i].to,x,1,a[i].to);	
	}
	sort(b + 1,b + 1 + cnt1,cmp);
	int l = 1;
	for(int i = 2;i <= cnt1;i++)
		if(b[i].col != b[i-1].col) 
		{
			for(int j = l;j < i;j++) t[b[j].id] = 0;
			for(int j = l;j < i;j++) t[b[j].id]++;
			for(int j = l;j < i;j++) 
				ans += (i-l-t[b[j].id]) * b[j].z;
			l = i;
		}
	for(int i = l;i <= cnt1;i++) t[b[i].id] = 0;
	for(int i = l;i <= cnt1;i++) t[b[i].id]++;
	for(int i = l;i <= cnt1;i++) ans += b[i].z*(cnt1-l+1-t[b[i].id]);
}
inline void del(int x) 
{
	v[x] = 1; solve(x); 
	for(int i = head[x];i;i = a[i].nxt)
	{
		if(v[a[i].to]) continue;
		ma = 2e9;
		dfs1(a[i].to,0,siz[a[i].to]);
		del(ma1);
	}
}
signed main()
{
	scanf("%lld",&n); ma = 1e9;
	for(int i = 1;i < n;i++) scanf("%d%d",&x,&y),add(x,y),add(y,x);
	for(int i = 1;i <= n;i++) scanf("%d",&c[i]);
	dfs1(1,0,n);  
	del(ma1);  
	printf("%lld",ans);
    return 0;
}
```

---

## 作者：Sorato_ (赞：0)

# ABC359G Sum of Tree Distance

## 题目大意

给定一棵 $N$ 个节点树，和每个点的权值 $A_i$。求 $\sum\limits_{i=1}^{N-1}\sum\limits_{j=i+1}^Ndis(i,j)\times[A_i=A_j]$。

## Solve

点分治板子啊。

对于分治出的以 $u$ 为根的子树，令 $dep[u]$ 为 $0$。$dep$ 是子树中每个点的深度，也就是到根节点的距离。

用 $sum_i$ 统计所有点权为 $i$ 的点到子树的根的距离之和，再用 $cnt_i$ 统计所有点权为 $i$ 的点的个数，当遍历到点 $v$ 时，让答案加上 $sum_{A_v}+cnt_{A_v}\times dep_v$，也就是加上之前遍历过的点到 $v$ 点的距离和。然后在遍历完这一分支之后修改 $sum$ 和 $cnt$ 数组以实现容斥即可，没啥细节。

## Code

```c++
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int read()
{
	short f=1;
	int x=0;
	char c=getchar();
	while(c<'0'||c>'9')	{if(c=='-')	f=-1;c=getchar();}
	while(c>='0'&&c<='9')	x=(x<<1)+(x<<3)+(c^48),c=getchar();
	return x*f;
}
int n,v[200010],ans;
vector<int>e[200010];
int mn,root,siz[200010];
int dep[200010],sum[200010],now,cnt[200010];
bool vis[200010];
vector<int>a,b;
void get_siz(int u,int fa)
{
	siz[u]=1;
	int mx=0;
	for(auto i:e[u])
		if(i!=fa&&!vis[i])
			get_siz(i,u),
			mx=max(mx,siz[i]),siz[u]+=siz[i];
	mx=max(mx,now-siz[u]);
	if(mx<mn)	mn=mx,root=u;
}
inline int get_rt(int u)/*找重心*/
{
	mn=n;now=siz[u];
	get_siz(u,0);
	return root;
}
void get_dis(int u,int fa)
{
	a.push_back(u);
	for(auto i:e[u])
		if(i!=fa&&!vis[i])
			dep[i]=-~dep[u],
			get_dis(i,u);
}
inline void calc(int u)
{
	dep[u]=1;
	a.clear();
	get_dis(u,0);
	for(auto i:a)
		ans+=sum[v[i]]+dep[i]*cnt[v[i]];
}
void solve(int u)
{
	vis[u]=1;
	cnt[v[u]]=-~cnt[v[u]];/*别忘了算上子树的根*/
	for(auto i:e[u])
		if(!vis[i])
		{
			calc(i);
			for(auto i:a)
				sum[v[i]]+=dep[i],cnt[v[i]]=-~cnt[v[i]],
				b.push_back(i);
		}
	for(auto i:b)	sum[v[i]]-=dep[i],cnt[v[i]]--;
	b.clear();cnt[v[u]]--;
	for(auto i:e[u])
		if(!vis[i])	solve(get_rt(i));
}
signed main()
{
	siz[1]=n=read();
	for(int i=1,a,b;i<n;i=-~i)
		a=read(),b=read(),
		e[a].push_back(b),e[b].push_back(a);
	for(int i=1;i<=n;i=-~i)	v[i]=read();
	solve(get_rt(1));
	return printf("%lld",ans),0;
}
```

（点分治的写法可能有些丑，凑合着看吧。）

---

## 作者：AzusidNya (赞：0)

### abc359_g - Sum of Tree Distance

> 给你一棵有 $N$ 个顶点的树。 $i$ -th 边双向连接顶点 $u _ i$ 和 $v _ i$ 。
>
> 每个点有颜色 $A=(A _ 1,\ldots,A _ N)$ 。
>
> 定义 $f(i,j)$ 如下：
>
> - 如果是 $A _ i = A _ j$ ，那么 $f(i,j)$ 就是从顶点 $i$ 移动到顶点 $j$ 所需的最小边数。如果是 $A _ i \neq A _ j$ ，那么就是 $f(i,j) = 0$ 。
>
> 计算下面表达式的值：
> $$
> \displaystyle \sum _ {i=1}^{N-1}\sum _ {j=i+1}^N f(i,j)
> $$

这是 [P4103  大工程](https://www.luogu.com.cn/problem/P4103)  的严格弱化版。

可以对每种 $A_i$ 分开算，题目转化为了每次给出一个点集，点集大小之和为 $n$，求点集中点两两距离和。

对点集建立虚树，然后在虚树上 dp。

设 $g_u$ 表示以 $u$ 为根的子树内所有当前颜色的点到根的距离和，$siz_u$ 表示 $u$ 子树大小。每次将一个子树 $v$ 和当前子树合并。

对于两个点，如果它们在 $u$ 的两个不同子树内，那么它们的 $\operatorname{lca}$ 为 $u$。

注意到 $g_u$ 和 $g_v$ 维护了一堆链的长度和，$u$ 和 $v$ 为端点的链拼上边 $(u, v)$ 就得到所有经过 $u$ 的路径了。

设 $w$ 为虚树上边 $(u, v)$ 的长度。然后容易写出状态转移方程：
$$
\begin {aligned}
g_u &\leftarrow g_u + g_v + siz_v \cdot w \\
siz_u &\leftarrow siz_u + siz_v \\
ans &\leftarrow ans + (g_u + siz_u \cdot w) \cdot siz_v + g_v \cdot siz_u
\end {aligned}
$$
直接 dp 即可。

设 $C_i$ 表示颜色为 $i$ 的节点数量。对于每种颜色，建虚树的复杂度是排序和求 $\operatorname{lca}$ 的 $O(C_i \log C_i)$，dp 是 $O(C_i)$ 的。而 $\sum C_i = n$。

所以总时间复杂度是 $O(n \log n)$。

如果用基数排序并且用 $O(n) - O(1)$ 的 $\operatorname{lca}$，那么应该是可以优化到 $O(n)$ 的。

```cpp
#include<iostream>
#include<fstream>
#include<algorithm>
#include<vector>
using namespace std;
namespace azus{
	int n;
	int col[400005];
	vector<int> que[400005];
	vector<int> edge[400005];
	int fa[400005], siz[400005], son[400005], dep[400005];
	int dfs1(int u, int ft){
		fa[u] = ft, siz[u] = 1, dep[u] = dep[ft] + 1;
		for(int i = 0, v; i < edge[u].size(); i ++){
			v = edge[u][i];
			if(v == ft) continue;
			dfs1(v, u);
			siz[u] += siz[v];
			if(siz[v] > siz[son[u]]) son[u] = v;
		}
		return 0;
	}
	int dfn[400005], top[400005], rnk[400005], tim;
	int dfs2(int u, int ft, int tp){
		dfn[u] = ++ tim, rnk[tim] = u, top[u] = tp;
		if(son[u] != 0)
			dfs2(son[u], u, tp);
		for(int v : edge[u]){
			if(v == ft || v == son[u]) continue;
			dfs2(v, u, v);
		}
		return 0;
	}
	int getlca(int u, int v){
		if(dep[top[u]] <= dep[top[v]]) swap(u, v);
		if(top[u] == top[v]){
			if(dep[u] > dep[v]) return v;
			return u;
		}
		return getlca(fa[top[u]], v);
	}
	int a[400005], tot, num;
	bool cmp(int u, int v){
		return dfn[u] < dfn[v];
	}
	bool vis[400005];
	vector<int> edg[400005];
	vector<int> vl[400005];
	long long g[400005];
	int sz[400005];
	long long ret;
	int dfs(int u){
		if(vis[u]) sz[u] ++;
		for(int i = 0, v, w; i < edg[u].size(); i ++){
			v = edg[u][i], w = vl[u][i];
			dfs(v);
			ret += 1ll * (g[u] + 1ll * sz[u] * w) * sz[v] + 1ll * g[v] * sz[u];
			g[u] += g[v] + 1ll * sz[v] * w;
			sz[u] += sz[v];
		}
		return 0;
	}
	signed main(){
		cin >> n;
		for(int i = 1, u, v; i < n; i ++)
			cin >> u >> v, edge[u].push_back(v), edge[v].push_back(u);
		for(int i = 1, x; i <= n; i ++)
			cin >> x, que[x].push_back(i);
		dfs1(1, 0), dfs2(1, 0, 1);
		long long ans = 0;
		for(int T = 1; T <= n; T ++){
			tot = que[T].size();
			for(int i = 1; i <= tot; i ++)
				a[i] = que[T][i - 1], vis[a[i]] = 1;
			sort(a + 1, a + tot + 1, cmp);
			num = tot;
			for(int i = 2; i <= num; i ++){
				int lca = getlca(a[i], a[i - 1]);
				if(lca != a[i] && lca != a[i - 1])
					a[++ tot] = lca;
			}
			sort(a + 1, a + tot + 1);
			tot = unique(a + 1, a + tot + 1) - (a + 1);
			sort(a + 1, a + tot + 1, cmp);
			for(int i = 2; i <= tot; i ++){
				int lca = getlca(a[i], a[i - 1]);
				edg[lca].push_back(a[i]);
				vl[lca].push_back(dep[a[i]] - dep[lca]);
			}
			ret = 0;
			dfs(a[1]);
			ans += ret;
			for(int i = 1; i <= tot; i ++)
				vis[a[i]] = 0, edg[a[i]].clear(), vl[a[i]].clear(), g[a[i]] = sz[a[i]] = 0;
		}
		cout << ans;
		return 0;
	}
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	int T = 1;
	while(T --) azus::main();
	return 0;
}
```

---

