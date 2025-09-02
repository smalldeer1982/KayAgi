# [IOI 2009] Regions

## 题目背景

## 滥用本题评测将被封号

IOI2009 D2T3

原题时间限制 8s，为节约评测资源，时间限制改为 4s。

## 题目描述

联合国区域发展委员会（The United Nations Regional Development Agency, UNRDA）有一个良好的组织结构。它任用了 $N$ 名委员，每名委员都属于几个地区中的一个。委员们按照其资历被编号为 $1$ 到 $N$ ，$1$ 号委员是主席，资历最高。委员所属地区被编号为 $1$ 到 $R$。除了主席之外所有委员都有一个直接导师。任何直接导师的资历都比他所指导的委员的资历要高。

我们称委员 $A$ 是委员 $B$ 的导师当且仅当 $A$ 是 $B$ 的直接导师或者 $A$ 是 $B$ 的直接导师的导师。显然，主席是所有其他委员的导师，没有任何两名委员互为导师。

现在，为了调查大量对 UNRDA 偏向某些地区的不平衡的组织结构的指控，UNRDA 想要建立一个计算机系统：在给定委员之间的直接导师关系的情况下，该系统可以回答下述形式的问题：给定两个地区 $r_1$ 和 $r_2$，要求系统回答委员会中有多少对委员 $e_1$ 和 $e_2$，满足 $e_1$ 属于 $r_1$，而 $e_2$ 属于 $r_2$，并且 $e_1$ 是 $e_2$ 的导师。每次询问都有两个参数 $r_1$ 和 $r_2$，结果是一个整数：满足上述条件的 $(e_1, e_2)$ 二元组的数量。

**任务**：编写一个程序，给定每个委员的地区和直接导师，**在线** 回答上述询问。

**强制在线将以交互的格式进行**。

## 说明/提示

### 数据范围与约定

- 对于 $30\%$ 的数据，$N\leq 500$。
- 对于 $55\%$ 的数据，没有地区包含超过 $500$ 个委员。
- 同时满足上述两个条件的数据有 $15\%$，至少满足上述一个条件的数据有 $70\%$。
- 对于 $100\%$ 的数据，$1 \le N, Q \le 2 \times 10^5$，$1 \le H_k, r_1, r_2 \le R \le 2.5 \times 10^4$，$1 \le S_k < k$。

## 样例 #1

### 输入

```
6 3 4
1
1 2
1 3
2 3
2 3
5 1
1 2

1 3

2 3

3 1```

### 输出

```








1 [刷新缓冲区]

3 [刷新缓冲区]

2 [刷新缓冲区]

1 [刷新缓冲区]
```

# 题解

## 作者：UnyieldingTrilobite (赞：14)

[lnk](https://www.luogu.com.cn/problem/P5901)。

大家好啊这里是一个在线的 $O(n^{1.5})$ 的做法（假设 $n,q,r$ 同阶）。

地区不好听，换个名字叫颜色好了。导师关系显然构成树形结构。

首先这种题一眼起手根分，把出现次数大于等于根号的颜色标记为“重颜色”，小于的标记为“轻颜色”。那么我们把询问 $(u,v)$（对应原题里的 $(r1,r2)$）分为三类处理。

1. $v$ 为“重颜色”

注意到此时所有可能的询问一共 $O(n^{1.5})$ 种，可以预处理。我们可以对于每个点，把它子树内的“重颜色”分布贡献到它对应的颜色上去（这个分布可以按儿子向父亲转移，一遍 dfs 能搜完）。但这样的话我们注意到我们的空间需要开两个 $O(n^{1.5})$ 的数组。更优的做法是在 $dfs$ 的时候维护一个“重颜色”分布的计数器，进入一个点的时候更新计数器（**离开不更新**），然后每个点子树内部的颜色分布就可以通过进入子树前和离开子树后的两波计数器作差求出。然后我们可以跳过先把贡献挂在每个点上再转给颜色这一步，可以直接给颜色更新贡献，不懂的可以看代码。

2. $v$ 为“轻颜色”且 $u$ 为“重颜色”。

注意到此时所有可能的询问还是一共 $O(n^{1.5})$ 种，依旧可以预处理。注意到实际上有两种算贡献的方法：孩子把贡献给祖先，或者祖先从孩子处获得贡献。很显然，谁的颜色分布简单，就该由谁去主动操作贡献（不然很难精准定位贡献）。所以在第一种情况下是祖先从孩子处获取，那这回就是孩子把贡献给祖先了。我们同样维护一个“重颜色”分布的计数器，进入一个点的时候更新之，离开一个点的时候同样更新之。这样的话，我们遍历到一个点的时候，实际上计数器里存下的是它祖先们的“重颜色”分布。那我们把这个点的贡献给祖先，只需要枚举每一种“重颜色”然后根据它在祖先中的出现次数加贡献就好了。

3. $u,v$ 均为“轻颜色”

这个时候我们发现两边都只有根号量级的点了。我们可以直接把这些点拉出来，然后观察如何给这个“子树内”另一个刻画。不难想到 dfs 序，那么我们设第一个序列是 $a_1,a_2,\cdots,a_x$，第二个是 $b_1,b_2,\cdots,b_n$，dfs 序列 为 $dfn$，一个点子树内的最大 dfs 序为 $ed$，那要统计的其实是这么一个东西：

$$\sum_{i=1}^x\sum_{j=1}^y[dfn_{a_i}\le dfn_{b_j}\le ed_{a_i}]$$

我们发现那个双不等号很难处理，于是我们考虑把它拆开，然后柿子变成了：

$$\sum_{i=1}^x\sum_{j=1}^y[dfn_{b_j}\le ed_{a_i}]-\sum_{i=1}^x\sum_{j=1}^y[dfn_{b_j}\le dfn_{a_i}-1]$$

我们发现前后两个柿子没啥形式上的区别而且都是一个类似于归并求逆序对（或者顺序对？）的形式，那显然是扫描线扫一扫就可以算的。而且我们甚至不需要为这个排序付出额外的代价——在 dfs 的过程中刻画这个序列的话，它应当天然是有序的（不过要看怎么刻画，也有可能天然倒序，反正就一个翻转序列的事）。

综上，我们这题就做完了。可能讲的有点意识流，放代码吧，没有精细实现，就图一个好写。跑挺慢的。不认识且结对出现且和带 nxt 的数组在一起的数组可以全部归为前向星（一共三个：存图，$dfn$，$ed$。基本上存法各有千秋，建议结合代码理解。注意前向星对边的编号没有要求，所以非常放飞自我，方便就完事了，希望不要有读者被误导。）

最后再说一个代码小细节吧，本来这题打算开 `long long` 的（因为虽然题目有那个保证但其实没查到的地方还是可能溢出，第三类情况依赖作差也很容易溢出），但考虑到不大美观，于是就使用了一个常用 trick：把 `unsigned` 当 `long long` 用，输出没问题且过程没 UB 就好了（

```cpp
#include <bits/stdc++.h>
#define getchar()                                                              \
  (p1 == p2 && (p2 = (p1 = buf) + (cin.read(buf, 1 << 23).gcount()), p1 == p2) \
       ? EOF                                                                   \
       : *p1++)
using namespace std;
typedef unsigned ll;
char buf[1 << 23], *p1 = buf, *p2 = buf, obuf[1 << 22], *O = obuf;
int rd() {
  char ch;
  while (!isdigit(ch = getchar()))
    ;
  int x = ch & 15;
  while (isdigit(ch = getchar())) x = x * 10 + (ch & 15);
  return x;
}
void prtln(ll x) {
  char s[15];
  int tot = 0;
  if (!x)
    *O++ = '0';
  else {
    while (x) s[++tot] = x % 10 | '0', x /= 10;
    while (tot) *O++ = s[tot--];
  }
  *O++ = '\n';
}
constexpr int N = 2e5 + 9, R = 2.5e4 + 9, Q = 2e5 + 9, B = 459;
int n, r, q;
int id[R], bel[N], ctot, cnt[R], tmp[B];
int hd[N], nxt[N], etot;
int dhd[R], dnxt[N];
int ehd[R], eto[N], enxt[N];
int tmpx[B], tmpy[B], totx, toty;
ll htl[B][R], occ[B], lth[R][B];
void dfs(int x) {
  int c = bel[x];
  dnxt[++etot] = dhd[c], dhd[c] = etot;
  for (int i = 1; i <= ctot; ++i) lth[c][i] -= occ[i];
  if (int i = id[c]) ++occ[i], ++tmp[i];
  for (int i = 1; i <= ctot; ++i) htl[i][c] += tmp[i];
  for (int y = hd[x]; y; y = nxt[y]) dfs(y);
  for (int i = 1; i <= ctot; ++i) lth[c][i] += occ[i];
  enxt[x] = ehd[c], ehd[c] = x, eto[x] = etot;
  if (int i = id[c]) --tmp[i];
}
ll calcxy() {
  ll ans = 0;
  for (int i = 0, j = 0; j < toty; ++j) {
    while (i < totx && tmpx[i] <= tmpy[j]) ++i;
    ans += i;
  }
  return ans;
}
ll calcans(int u, int v) {
  if (id[v])
    return lth[u][id[v]];
  else if (id[u])
    return htl[id[u]][v];
  totx = 0, toty = 0;
  for (int i = dhd[v]; i; i = dnxt[i]) tmpx[totx++] = i;
  reverse(tmpx, tmpx + totx);
  for (int i = ehd[u]; i; i = enxt[i]) tmpy[toty++] = eto[i];
  reverse(tmpy, tmpy + toty);
  ll ans = calcxy();
  toty = 0;
  for (int i = dhd[u]; i; i = dnxt[i]) tmpy[toty++] = i - 1;
  reverse(tmpy, tmpy + toty);
  return ans - calcxy();
}
int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  n = rd(), r = rd(), q = rd();
  ++cnt[bel[1] = rd()];
  for (int i = 2, s; i <= n; ++i) {
    nxt[i] = hd[s = rd()], hd[s] = i;
    ++cnt[bel[i] = rd()];
  }
  for (int i = 1; i <= r; ++i)
    if (cnt[i] >= B) id[i] = ++ctot;
  dfs(1);
  while (q--) {
    int u = rd(), v = rd();
    prtln(calcans(u, v));
  }
  return cout.write(obuf, O - obuf).flush(), 0;
}
```

---

## 作者：Alex_Wei (赞：10)

> [P5901 [IOI2009] Regions](https://www.luogu.com.cn/problem/P5901)

同时涉及两个集合的问题，如果没有特殊性质，基本上不能 $\mathrm{polylog}$：每个集合的大小为 $\sqrt n$，询问每两个集合之间的答案，至少也得 $\mathcal{O}(n\sqrt n)$。

考虑根号分治，称大小大于 $\sqrt n$ 的集合为大集合，其它集合为小集合。

当 $r_1$ 为大集合时，考虑预处理所有这样的询问的答案。对每个大集合 $r_1$，集合 $r_2$ 的答案为 $\sum_{i\in r_2} c_i$，其中 $c_i$ 表示集合 $r_1$ 中 $i$ 的祖先的数量，时间复杂度 $\mathcal{O}(n)$。因为有不超过 $\sqrt n$ 个大集合，所以总复杂度 $\mathcal{O}(n\sqrt n)$。

当 $r_2$ 为大集合时，同样的，预处理所有这样的询问的答案，只需要将 $c_i$ 的定义改为集合 $r_2$ 中 $i$ 的子节点的数量。

当 $r_1, r_2$ 均为小集合时，总共只会涉及到 $\mathcal{O}(\sqrt n)$ 个点。$r_1$ 的每个点对应一个时间戳区间，$r_2$ 的每个点对应一个时间戳，每个时间戳落在每个时间戳区间都会产生 $1$ 的贡献。相当于先进行若干次区间加 $1$，再进行若干次单点查询。 对坐标区间扫描线，遇到左端点就将当前区间数 $+1$，遇到右端点就将当前区间数 $-1$。预处理排序即可做到单次 $\mathcal{O}(\sqrt n)$。

总时间复杂度 $\mathcal{O}((n + q)\sqrt n)$，空间复杂度 $\mathcal{O}(n + R\sqrt n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

bool Mbe;
constexpr int N = 2e5 + 5;
constexpr int R = 2.5e4 + 5;
constexpr int B = 450;

int n, r, q, h[N], rlab[N];
int c1[B][R], c2[B][R];
int dn, fa[N], sz[N], dfn[N];
vector<int> e[N], buc[N], eve[N];
void dfs(int id) {
  dfn[id] = ++dn, sz[id] = 1;
  for(int it : e[id]) dfs(it), sz[id] += sz[it];
}

bool Med;
int main() {
  fprintf(stderr, "%.3lf MB\n", (&Mbe - &Med) / 1048576.0);
  #ifdef ALEX_WEI
    FILE* IN = freopen("1.in", "r", stdin); 
    FILE* OUT = freopen("1.out", "w", stdout);
  #endif
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> n >> r >> q;
  for(int i = 1; i <= n; i++) {
    if(i > 1) cin >> fa[i], e[fa[i]].push_back(i);
    cin >> h[i], buc[h[i]].push_back(i);
  }
  dfs(1);
  for(int i = 1, c = 0; i <= r; i++)
    if(buc[i].size() >= B) {
      static int d[N];
      memset(d, 0, sizeof(d)), rlab[i] = ++c;
      for(int it : buc[i]) d[dfn[it]]++;
      for(int j = 1; j <= n; j++) d[j] += d[j - 1];
      for(int j = 1; j <= n; j++) {
        if(h[j] == i) continue;
        int l = dfn[j], r = l + sz[j] - 1;
        c1[c][h[j]] += d[r] - d[l - 1];
      }
      memset(d, 0, sizeof(d));
      for(int it : buc[i]) {
        int l = dfn[it], r = l + sz[it] - 1;
        d[l]++, d[r + 1]--;
      }
      for(int j = 1; j <= n; j++) d[j] += d[j - 1];
      for(int j = 1; j <= n; j++) {
        if(h[j] == i) continue;
        c2[c][h[j]] += d[dfn[j]];
      }
    }
    else {
      for(int it : buc[i]) {
        eve[i].push_back(dfn[it]);
        eve[i].push_back(-(dfn[it] + sz[it]));
      }
      sort(eve[i].begin(), eve[i].end(), [&](int x, int y) {
        return abs(x) < abs(y);
      });
      sort(buc[i].begin(), buc[i].end(), [&](int x, int y) {
        return dfn[x] < dfn[y];
      });
    }
  for(int i = 1; i <= q; i++) {
    int r1, r2;
    cin >> r1 >> r2;
    if(rlab[r2]) cout << c1[rlab[r2]][r1] << endl;
    else if(rlab[r1]) cout << c2[rlab[r1]][r2] << endl;
    else {
      int ans = 0, cur = 0, pt = 0;
      for(int it : buc[r2]) {
        while(pt < eve[r1].size()) {
          int v = eve[r1][pt];
          if(abs(v) > dfn[it]) break;
          cur += v / abs(v), pt++;
        }
        ans += cur;
      }
      cout << ans << endl;
    }
  }
  cerr << 1e3 * clock() / CLOCKS_PER_SEC << " ms\n";
  return 0;
}
```

---

## 作者：WrongAnswer_90 (赞：5)

[P5901 [IOI2009] Regions](https://www.luogu.com.cn/problem/P5901)

[更好的阅读体验](https://www.cnblogs.com/WrongAnswer90-home/p/17789893.html)

根号分治，过掉不难，但是想 $\mathcal O(n\sqrt n)$ 还是有一些思维含量的。

经过思考，发现 polylog 十分困难，考虑根号的算法。

首先有一种暴力：预处理两两颜色间的答案，$\mathcal O(1)$ 查询。首先枚举颜色数，然后每种颜色 $\mathcal O(n)$ 扫一遍，这样预处理的复杂度是 $\mathcal O(n\times \text{处理的颜色数})$。直接硬预处理显然过不去，所以可以考虑对出现次数较多的颜色预处理。设块长为 $B$，出现次数大于 $B$ 的颜色称为大块，否则为小块。

对于大块与大块，大块与小块，小块与大块之间的答案还是想上面一样预处理，预处理复杂度是 $\mathcal O(n\times \dfrac{n}{B})$。

对于小块，内部点数是 $\mathcal O(B)$ 级别的，树上的祖先后代问题用 dfn 序转化为区间问题：

$\sum_{i\in col_x}\sum_{j\in col_y}[in_i\leq dfn_j\leq out_i]$

直接做有 $in,out$ 两个限制，但是一个 $dfn$ 不可能即 $>out_i$ 有 $<in_i$，所以可以容斥一下，用总的点对数减去不合法的点对数，问题变为

$\sum_{i\in col_x}\sum_{j\in col_y}[dfn_j<in_i]$

可以树状数组做到 $B\log n$，但是更优秀的做法是预处理排序好的 $in$ 和 $dfn$，用类似归并排序求逆序对的思路双指针解决，对于 $>out_i$ 的部分也是同理。

总复杂度 $\mathcal O(n\times \dfrac{n}{B}+nB)$，$B$ 取 $\sqrt n$ 时复杂度为 $\mathcal O(n\sqrt n)$。

```cpp
	int n,m,q,cnt,B=360,tot,dfn[200001],nfd[200001],pos[200001],sum[200001],a[200001],head[200001],to[200001],nex[200001],siz[25001],ans1[160][25001],ans2[160][25001];
	inline void add(int x,int y){to[++cnt]=y,nex[cnt]=head[x],head[x]=cnt;}
	vector<int> larg,ve[25001],ve2[25001];
	void dfs(int k){dfn[k]=++tot;for(int i=head[k];i;i=nex[i])dfs(to[i]);nfd[k]=tot;}
	void dfs1(int k){for(int i=head[k];i;i=nex[i])dfs1(to[i]),sum[k]+=sum[to[i]];}
	void dfs2(int k){for(int i=head[k];i;i=nex[i])sum[to[i]]+=sum[k],dfs2(to[i]);}
	inline bool cmp(int x,int y){return dfn[x]<dfn[y];}
	inline bool cmp2(int x,int y){return nfd[x]<nfd[y];}
	inline void mian()
	{
		cin>>n>>m>>q>>a[1],++siz[a[1]],ve[a[1]].eb(1);int x,y;
		for(int i=2;i<=n;++i)cin>>x>>a[i],++siz[a[i]],ve[a[i]].eb(i),add(x,i);
		for(int i=1;i<=m;++i)if(siz[i]>B)pos[i]=larg.size(),larg.eb(i);
		dfs(1);
		for(int i=1;i<=m;++i)ve[i].eb(0),ve2[i]=ve[i],sort(ve2[i].begin(),ve2[i].end(),cmp2),sort(ve[i].begin(),ve[i].end(),cmp);
		for(int i=0;i<larg.size();++i)
		{
			for(auto j:ve[larg[i]])++sum[j];
			dfs1(1);
			for(int j=1;j<=n;++j)ans1[i][a[j]]+=sum[j];
			memset(sum,0,sizeof(sum));
			for(auto j:ve[larg[i]])++sum[j];
			dfs2(1);
			for(int j=1;j<=n;++j)ans2[i][a[j]]+=sum[j];
			memset(sum,0,sizeof(sum));
		}
		while(q--)
		{
			cin>>x>>y;
			if(pos[x])cout<<ans2[pos[x]][y]<<endl;
			else if(pos[y])cout<<ans1[pos[y]][x]<<endl;
			else
			{
				int ans=siz[x]*siz[y];
				for(int i=1,j=1;i<=siz[x]&&j<=siz[y];++j)
				{
					while(i<=siz[x]&&dfn[ve[x][i]]<=dfn[ve[y][j]])++i;
					ans-=siz[x]-i+1;
				}
				for(int i=siz[x],j=siz[y];i>0&&j>0;--j)
				{
					while(i>0&&nfd[ve2[x][i]]>=dfn[ve[y][j]])--i;
					ans-=i;
				}
				cout<<ans<<endl;
			}
			fflush(stdout);
		}
	}
```

---

## 作者：Fan_sheng (赞：5)

每种颜色包含的点数与总颜色数相互制约，很显然是根号分治。

这里提供两种做法。

## 离线

算法一：进行一次 dfs，同时维护根到当前点的路径上每种颜色的个数。设当前点颜色为 $col$，如果 $r_2=col$ 的询问次数少于 $\sqrt q$，考虑枚举每一个这样的询问并计入贡献。复杂度 $\mathbb O(n\sqrt q)$。

算法二：如果 $r_2=col$ 的询问次数大于 $\sqrt q$，那么这样的 $col$ 不超过 $\sqrt q$ 个。考虑枚举每个这样的 $col$，分别用一次 dfs 统计出每个点的子树内有多少个 $col$。复杂度 $\mathbb O(n\sqrt q)$。

两种算法综合即可回答所有询问。总复杂度 $\mathbb O(n\sqrt q)$。

Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,T,r,q,app[200005],color[200005],ans[200005];
vector<int>edge[200005];
pair<int,int>Q[200005];
namespace task1{
	int cnt[25005];
	vector<int>hang[25005];
	void dfs1(int id){
		cnt[color[id]]++;
		for(int v:hang[color[id]])ans[v]+=cnt[Q[v].first];
		for(int v:edge[id])dfs1(v);
		cnt[color[id]]--;
	}
}
namespace task2{
	int cnt[25005],timer;
	vector<int>hang[25005];
	void dfs2(int id,int targ){
		int lst=timer;
		for(int v:edge[id])dfs2(v,targ);
		if(color[id]==targ)timer++;
		cnt[color[id]]+=timer-lst;
	}
}
int main(){
	scanf("%d%d%d%d",&n,&r,&q,&color[1]);
	T=ceil(sqrt(q));
	for(int i=2,tmp;i<=n;i++){
		scanf("%d",&tmp);
		edge[tmp].emplace_back(i);
		scanf("%d",&color[i]);
	}
	for(int i=1;i<=q;i++){
		scanf("%d%d",&Q[i].first,&Q[i].second);
		app[Q[i].second]++;
	}
	for(int i=1;i<=q;i++){
		if(app[Q[i].second]<=T)
		task1::hang[Q[i].second].emplace_back(i);
		else task2::hang[Q[i].second].emplace_back(i);
	}task1::dfs1(1);
	for(int i=1;i<=r;i++)if(app[i]>T){
		task2::dfs2(1,i);
		for(int v:task2::hang[i])ans[v]+=task2::cnt[Q[v].first];
		memset(task2::cnt,0,sizeof(task2::cnt));
	}
	for(int i=1;i<=q;i++)printf("%d\n",ans[i]);return 0;
}
```


## 在线

为方便，以下称包含点数大于 $\sqrt n$ 的颜色为“重颜色”，反之为“轻颜色”。

算法一（$r_2$ 为重颜色）：可以用类似离线算法二的方法解决，因为这样的 $r_2$ 不超过 $\sqrt n$ 个。复杂度 $\mathbb O(n\sqrt n)$。

算法二（$r_1$ 为重颜色，$r_2$ 为轻颜色）：$r_1$ 是 $r_2$ 的祖先相当于 $r_2$ 在 $r_1$ 的 dfs 序子树区间中。也就是说要解决这个问题：给出 $r_1$ 的所有子树区间和 $r_2$ 的所有点，计算每个点被多少个区间包含，再求和。可以枚举所有重颜色 $r_1$，用差分的方式插入其所有子树区间，再前缀和一下即可。复杂度 $\mathbb O(n\sqrt n)$。

算法三（$r_1,r_2$ 都是轻颜色）：本次询问总共涉及到的点数为 $\mathbb O(\sqrt n)$ 级别，直接建出虚树然后暴力统计即可。复杂度 $\mathbb O(n\sqrt n)$。

总复杂度 $\mathbb O(n\sqrt n)$。

算法三的常数非常大，可以用以下方式优化：

- 对关键点排序不要直接 sort。可以对每种颜色的点预先排序一次，询问的时候对 $r_1,r_2$ 的点归并排序，去掉 $\log$。

- 建虚树的时候，已经确定父亲的点的子树不会再发生变化。因此可以对每个点维护一个 $cnt$，表示当前其子树内 $r_2$ 的数量。与儿子 $v$ 连边时，更新自己的 $cnt$，同时 $v$ 的子树已经完全确定，如果 $v$ 的颜色为 $r_1$，将 $cnt[v]$ 加入答案。这样甚至根本不需要建边，效果显著。

Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int lim=160;
int n,r,q,T,color[200005],mp[25003],flag;
vector<int>edge[200005],b[25003];
namespace LCA{
	int depth[200005],dfn[200005],sz[200005],lg[400005],st[400005][20],timer,in[200005];
	void DFS(int id,int from){
		depth[id]=depth[from]+(sz[id]=1);
		st[in[id]=++timer][0]=id;
		dfn[id]=++dfn[0];
		for(int v:edge[id])
		DFS(v,id),sz[st[++timer][0]=id]+=sz[v];
	}
	inline void ST(){
		lg[0]=-1;
		for(int i=1;i<=timer;i++)lg[i]=lg[i>>1]+1;
		for(int len=1;len<=lg[timer];len++)
		for(int i=1;i+(1<<len)-1<=timer;i++){
			int a=st[i][len-1],b=st[i+(1<<(len-1))][len-1];
			st[i][len]=(depth[a]<depth[b]?a:b);
		}
	}
	inline int lca(int u,int v){
		u=in[u],v=in[v];
		if(u>v)swap(u,v);
		int len=lg[v-u+1],a=st[u][len],b=st[v-(1<<len)+1][len];
		return (depth[a]<depth[b]?a:b);
	}
}using namespace LCA;
namespace task1{
	int ans[lim+3][25003],cnt[lim+3],lst[lim+3];
	void dfs(int id){
		for(int i=1;i<=flag;i++)ans[i][color[id]]-=cnt[i];
		for(int v:edge[id])dfs(v);
		cnt[mp[color[id]]]++;
		for(int i=1;i<=flag;i++)ans[i][color[id]]+=cnt[i]-lst[i];
	}
}
namespace task2{
	int sum[200005],ans[lim+3][25005];
	inline void init(){
		for(int i=1;i<=r;i++)if(mp[i]){
			memset(sum,0,sizeof(sum));
			for(int v:b[i])sum[dfn[v]]++,sum[dfn[v]+sz[v]]--;
			for(int j=1;j<=n;j++)sum[j]+=sum[j-1];
			for(int j=1;j<=n;j++)ans[mp[i]][color[j]]+=sum[dfn[j]];
		}
	}
}
namespace task3{
	int targ[200005],k,stk[200005],top,ans,cnt[200005];
	inline void build(int r1,int r2){
		auto add=[&](int u,int v){
			cnt[u]+=cnt[v];
			if(color[v]==r1)ans+=cnt[v];
		};
		auto clear=[&](int id){cnt[id]=(color[id]==r2);};
		k=ans=0;
		for(int v:b[r1])targ[++k]=v;
		for(int v:b[r2])targ[++k]=v;
		inplace_merge(targ+1,targ+b[r1].size()+1,targ+k+1,[&](int a,int b){return dfn[a]<dfn[b];});
		clear(stk[top=1]=1);
		for(int i=1;i<=k;i++){
			if(targ[i]==1)continue;
			int L=lca(stk[top],targ[i]);
			if(L!=stk[top]){
				while(dfn[stk[top-1]]>dfn[L])
				add(stk[top-1],stk[top]),top--;
				if(stk[top-1]!=L)
				clear(L),add(L,stk[top]),stk[top]=L;
				else add(L,stk[top--]);
			}clear(stk[++top]=targ[i]);
		}
		while(top>1)add(stk[top-1],stk[top]),top--;
		add(0,1),printf("%d\n",ans);
	}
}
int main(){
	scanf("%d%d%d%d",&n,&r,&q,&color[1]);
	T=ceil(sqrt(n));
	for(int i=2,tmp;i<=n;i++){
		scanf("%d",&tmp);
		edge[tmp].emplace_back(i);
		scanf("%d",&color[i]);
	}DFS(1,0),ST();
	for(int i=1;i<=n;i++)b[color[i]].emplace_back(i);
	for(int i=1;i<=r;i++)
	sort(b[i].begin(),b[i].end(),[&](int a,int b){return dfn[a]<dfn[b];});
	for(int i=1;i<=r;i++)if(b[i].size()>T)mp[i]=++flag;
	task1::dfs(1),task2::init();
	while(q--){
		int r1,r2;
		scanf("%d%d",&r1,&r2);
		if(mp[r2])printf("%d\n",task1::ans[mp[r2]][r1]);
		else if(mp[r1])printf("%d\n",task2::ans[mp[r1]][r2]);
		else task3::build(r1,r2);
	}return 0;
}
```


---

## 作者：lytqwq (赞：5)

来一篇在线 $O(n\sqrt{n\log n})$ 的题解。

设满足 $r_1$ 属性的点有 $A$ 个，满足 $r_2$ 属性的点有 $B$ 个。

所有以 $A$ 中的每个点为祖先的点在 dfs 序中都对应一段区间，那么我们就是求每个 $B$ 中的点被多少个区间包含了。

设一个阈值 $C$，然后分 $A,B$ 的大小讨论：

1. $B\ge C\land A< C$ 时 ，枚举 $A$，在 $B$ 属性的 vector 里二分，时间复杂度 $O(A\log B)$。

1. $A\ge C\land B< C$ 时 ，枚举 $B$，在 dfs 的过程中维护当前点到根的链上各个属性的出现次数，实际上是个欧拉序的样子（见代码），也一样可以在 vector里二分，时间复杂度 $O(B\log A)$。

1. $A< C \land B< C$ 时，和2.一样做，不过二分换成双指针就完了，时间复杂度 $O(A+B)$。

1. $A\ge C \land B\ge C$ 时，和3.一样做，注意到不同的 $A,B$ 出现次数不多，记忆化一下，时间复杂度最高 $O(nC)$。

$C$ 在取 $\sqrt{n\log n}$ 时，时间复杂度有最小： $O(n\sqrt{n\log n})$ 。

代码如下：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define PI pair<int,int>
#define fi first
#define se second
#define mp make_pair
#define ui unsigned int
using namespace std;
const int N=200010,R=25010;
int id[N],a[N],n,m,q;
vector<int> to[N];
struct d{
	vector<int> id;
	vector<PI> ranges;
	int dep;
}qwq[R];
int dfs_num,dfn[N];
void dfs(int u){
	dfn[u]=++dfs_num;
	qwq[a[u]].dep++;
	qwq[a[u]].id.push_back(dfs_num-1);
	qwq[a[u]].ranges.push_back(mp(dfs_num,qwq[a[u]].dep));
	for(auto i:to[u])dfs(i);
	qwq[a[u]].dep--;
	qwq[a[u]].ranges.push_back(mp(dfs_num,qwq[a[u]].dep));
}
ll query1(d x,d y){
	ll sum=0;
	for(auto i:y.id){
		vector<PI>::iterator it=lower_bound(x.ranges.begin(),x.ranges.end(),mp(i,n+1));
		if(it==x.ranges.begin())continue;
		it--;
		sum+=(*it).se;
	}
	return sum;
}
ll query2(d x,d y){
	ll sum=0;
	for(ui i=0;i+1<x.ranges.size();i++){
		int pos1=x.ranges[i].fi,pos2=x.ranges[i+1].fi,dep=x.ranges[i].se;
		vector<int>::iterator q1=lower_bound(y.id.begin(),y.id.end(),pos1);
		vector<int>::iterator q2=lower_bound(y.id.begin(),y.id.end(),pos2);
		sum+=dep*1ll*(q2-q1);
	}
	return sum;
}
ll query3(d x,d y){
	ll sum=0;
	vector<int>::iterator it=y.id.begin();
	if(x.ranges.empty())return 0;
	while(it!=y.id.end()&&(*it)<(*x.ranges.begin()).fi)it++;
	for(ui i=0;i+1<x.ranges.size()&&it!=y.id.end();i++){
		int pos=x.ranges[i+1].fi,dep=x.ranges[i].se;
		while(it!=y.id.end()&&(*it)<pos)it++,sum+=dep;
	}
	return sum;
}
map<PI,ll> ans;
int main(){
	scanf("%d%d%d",&n,&m,&q);
	int K=sqrt(n*log2(n)*2);
	scanf("%d",&a[1]);
	int fa;
	for(int i=2;i<=n;i++){
		scanf("%d%d",&fa,&a[i]);
		to[fa].push_back(i);
	}
	dfs(1);
	for(int i=1;i<=q;i++){
		int r1,r2;
		scanf("%d%d",&r1,&r2);
		if(ans[mp(r1,r2)]){
			
		}
		else if(qwq[r1].id.size()>=K&&qwq[r2].id.size()<K){
			ans[mp(r1,r2)]=query1(qwq[r1],qwq[r2])+1;
		}
		else if(qwq[r1].id.size()<K&&qwq[r2].id.size()>=K){
			ans[mp(r1,r2)]=query2(qwq[r1],qwq[r2])+1;
		}
		else{
			ans[mp(r1,r2)]=query3(qwq[r1],qwq[r2])+1;
		}
		printf("%lld\n",ans[mp(r1,r2)]-1);
	}
	return 0;
}
```



---

## 作者：TKXZ133 (赞：2)

[Regions](https://www.luogu.com.cn/problem/P5901)

这里提供一种时间复杂度不那么优秀但十分好写也好理解的做法。

### 题目大意

给定一颗 $n$ 个节点的树，每个节点拥有一个颜色，进行若干次询问，每次询问给出两种颜色 $A,B$，求所有颜色为 $A$ 的节点的子树中颜色为 $B$ 的节点的个数的和。

### 思路分析

考虑根号分治。按颜色的节点数进行分类，节点数 $>\sqrt n$ 的称为**重颜色**，节点数 $\le \sqrt n$ 的称为**轻颜色**。

对询问进行分类讨论：

- $A,B$ 均为轻颜色：

考虑到两者的节点数都不会很多，可以暴力标记每一个颜色为 $B$ 的点，并枚举所有颜色为 $A$ 的点，求出其子树中的标记数并累加入答案。这一过程可以用树状数组实现。（单点加，区间查询）单次实现的时间复杂度为 $O(\sqrt n\log n)$。

- $A$ 为重颜色，$B$ 为轻颜色：

设 $f_{i,j}$ 表示**点 $i$ 到根的路径中**颜色为**重颜色** $j$ 的节点的数量，那么答案显然为：

$$\sum\limits_{i\in \text{col}_B}f_{i,A}$$

其中，$\text{col}_X$ 表示所有颜色为 $X$ 的点所构成的集合。

考虑计算 $f$：

枚举每一个重颜色 $K$，遍历 $\text{col}_K$，将其中的每一个点的子树中的所有点的权值加 $1$，再遍历每一个颜色不为 $K$ 的点，其权值就是其对应的 $f$。这一过程可以用差分实现。（区间加，单点查询）时间复杂度为 $O(n\sqrt n)$。

- $B$ 为重颜色，$A$ 为轻颜色：

设 $g_{i,j}$ 表示**点 $i$ 的子树中**颜色为**重颜色** $j$ 的节点的数量，那么答案显然为：

$$\sum_{i\in \text{col}_A}g_{i,B}$$

$g$ 的计算与 $f$ 正好相反:

枚举每一个重颜色 $K$，遍历 $\text{col}_K$，将其中的每一个点的权值单点加 $1$。再遍历每一个颜色不为 $K$ 的点，其子树中的权值和即为其对应的 $g$，这一过程可以用前缀和实现。（单点加，区间查询）时间复杂度为 $O(n\sqrt n)$。

- $A,B$ 均为重颜色：

容易发现，这种情况是上述两种情况的交集，上述两种情况的答案计算方式均适用于此情况。

### 实现细节

在实现中，为了优化空间复杂度，可以省去 $f$ 和 $g$ 直接累加答案。具体的说，设 $\text{ans1}_{i,j}$ 表示所有颜色为 $i$ 的点的子树中颜色为重颜色 $j$ 的节点的数量的和，$\text{ans2}_{i,j}$ 表示所有颜色为 $i$ 的点到根的路径中颜色为重颜色 $j$ 的节点的数量的和。（也就是第三，二种情况对应的答案）这样可以将空间复杂度由 $O(n\sqrt n)$ 优化到 $O(R\sqrt n)$。

差分和前缀和可以直接在 dfs 序上进行，不需要放到树上。

总时间复杂度为 $O(q\sqrt n\log n+n\sqrt n)$，瓶颈在于树状数组，卡常后可以通过。

空间复杂度为 $O(R\sqrt n+n)$，完全可过。

### 代码

（不保证在任意时间提交此代码均可通过）

```
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;
const int N=200100,M=450,R=25500;

int idx=1,n,m,q,B,cnt,in1,in2,cur,ans;
int w[N],to[N],nxt[N],head[N];
int c[N],dfn[N],siz[N],big[N],d[N];
int ans1[M][R],ans2[M][R];

vector<int> col[N];

int read(){//卡常用的快读快写
    int x=0;char ch=getchar();
    while(ch>'9'||ch<'0') ch=getchar();
    while(ch>='0'&&ch<='9') x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
	return x;
}

void write(int x){
    int k=x/10;if(k) write(k);
    putchar(x-(k<<3)-(k<<1)+'0');
}

void add(int u,int v){
	idx++;to[idx]=v;nxt[idx]=head[u];head[u]=idx;
}

void dfs_1(int s){
	dfn[s]=++cnt;siz[s]=1;
	for(int i=head[s];i;i=nxt[i])
		dfs_1(to[i]),siz[s]+=siz[to[i]];
}

struct BIT{
	int a[N];
	#define lowbit(x) ((x)&(-(x)))
	void add(int x,int v){
		for(;x<N;x+=lowbit(x)) a[x]+=v;
	}
	int query(int x){
		if(!x) return 0;
		int ans=0;
		for(;x;x-=lowbit(x)) ans+=a[x];
		return ans; 
	}
}tree;

int main(){
	n=read();m=read();q=read();
	B=sqrt(n);
	w[1]=read();
	col[w[1]].push_back(1);
	for(int i=2;i<=n;i++){
		in1=read();w[i]=read();
		add(in1,i);
		col[w[i]].push_back(i);
	}
	dfs_1(1);
	for(int i=1;i<=m;i++){
		if(col[i].size()<=B) continue;
		big[i]=++cur;//对每一种重颜色重标号
		for(int j=1;j<=n;j++) d[j]=0;
		for(auto it:col[i]) d[dfn[it]]++;//单点加
		for(int j=1;j<=n;j++) d[j]+=d[j-1];//前缀和
		for(int j=1;j<=n;j++){
			if(w[j]==i) continue;
			ans1[cur][w[j]]+=d[dfn[j]+siz[j]-1]-d[dfn[j]-1];//直接累加答案
		}
		for(int j=1;j<=n;j++) d[j]=0;
		for(auto it:col[i]){
			d[dfn[it]]++;//差分
			d[dfn[it]+siz[it]]--;//这里其实是 dfn[it]+siz[it]-1+1
		}
		for(int j=1;j<=n;j++) d[j]+=d[j-1];//对差分序列做前缀和得到原序列
		for(int j=1;j<=n;j++){
			if(w[j]==i) continue;
			ans2[cur][w[j]]+=d[dfn[j]];
		}
	}
	while(q--){
		in1=read();in2=read();ans=0;
		if(big[in2]){write(ans1[big[in2]][in1]);cout<<'\n'<<flush;continue;}
		if(big[in1]){write(ans2[big[in1]][in2]);cout<<'\n'<<flush;continue;}
		for(auto it:col[in2]) tree.add(dfn[it],1);//暴力加
		for(auto it:col[in1]) 
			ans+=tree.query(dfn[it]+siz[it]-1)-tree.query(dfn[it]-1);
		write(ans);cout<<'\n'<<flush;
		for(auto it:col[in2]) tree.add(dfn[it],-1);//记得清空
	}
	return 0;
}
```

---

## 作者：strcmp (赞：1)

省流：在本题时限改成 4s 后被卡成 95pts 的大常数做法。

教练给的根号分治题单里的题，也是第一篇写了题解的 IOI 题。

**题目大意：** 给定一棵 $n$ 个结点以 $1$ 为根的树，点带权。$q$ 次询问，每次给定两数 $r_1$ 和 $r_2$。你需要计算祖先点权是 $r_1$ 且后代点权是 $r_2$ 的祖孙对数量。

------------

### Solution

记 $|c|$ 表示点权为 $c$ 的结点数，$w_i$ 为结点 $i$ 的点权。

考虑暴力要怎么做，显然我们可以对每次询问建立虚树，每个点权为 $r_1$ 的点会产生贡献，且贡献为其子树中点权为 $r_2$ 的点的数量，直接 dp 即可。

但显然我们只需要多次询问两个结点多的点权，就能把这个做法卡爆。

考虑用一个近似于 $\sqrt{n}$ 的数 $S$ 对复杂度平衡。

- $|r_1| \le S \wedge |r_2| \le S$，此时我们直接跑上面的暴力，每次询问复杂度是 $\Theta(S)$。

- $|r_1| \le S \wedge |r_2| > S$。

显然 $|c| > S$ 的颜色 $c$ 的个数不会有超过 $\frac{n}{S}$ 个。

于是对每个点 $i$ 预处理 $s_{i,u}$ 表示结点 $i$ 中有多少个颜色 $u$，其中 $u$ 满足 $|u| > S$。预处理时间复杂度为 $\Theta(\frac{n^2}{S})$。单次询问计算 $\sum_{w_i = r_1}s_{i,r_2}$，时间复杂度为 $\Theta(S)$。

- $|r_1| > S \wedge |r_2| \le S$。

与前一个做法同理，预处理 $g_{i,u}$ 表示结点 $i$ 到根结点的路径上有多少个颜色 $u$，其中 $u$ 满足 $|u| > S$。预处理可以做树上前缀和，时间复杂度为 $\Theta(\frac{n^2}{S})$。单次询问计算 $\sum_{w_i = r_2} g_{i,r_1}$，时间复杂度为 $\Theta(S)$。

- $|r_1| > S \wedge |r_2| > S$。

枚举每个 $|c| > S$ 的颜色对 $u,\,v$，直接建立虚树计算答案。

时间复杂度上，考虑对于每个颜色对 $u,\,v$，对时间复杂度的贡献为 $|u| + |v|$ 级别的，枚举 $u$，最坏情况下 $u$ 对时间复杂度的贡献是 $\frac{|u| \times n}{S}+ n$ 级别的。对所有 $u$ 求和，是 $\frac{n^2}{S}$ 级别的。

总时间复杂度为 $\Theta(nS + \frac{n^2}{S})$，根据均值不等式，在 $S$ 取 $\sqrt{n}$ 时时间复杂度最优，为 $\Theta(n \sqrt{n})$。（默认 $n,q$ 同阶）

------------

实现上，建立虚树的复杂度要求是 $\Theta(n)$ 级别的，考虑建立虚树时有什么地方导致时间复杂度乘上了一个 $\log$。

很显然是排序 dfs 序和求 LCA 的部分。排序上，可以先将每个点权包含的点按 dfs 序排序，求虚树时直接归并即可。求 LCA 可以用 ST 表直接预处理。

由于更改了时限，本题略（hen）卡常，这里放一个 95pts 的代码（在原题 8s 下可以通过）。

```cpp
#include <bits/stdc++.h>
#define re register
using namespace std;
typedef long long int int128;
const int maxn = 2e5 + 10;
const int N = maxn << 1;
const int S = 600;//////
inline int read() {
    int x = 0; char ch = getchar();
    while (!isdigit(ch)) ch = getchar();
    while (isdigit(ch)) x = (x << 3) + (x << 1) + ch - '0', ch = getchar();
    return x;
}
struct edge {
	int to, nxt;
}node[N]; int head[maxn], cnt = 0, n, r, q;
inline void add(int u, int v) {
	node[cnt].nxt = head[u];
	node[cnt].to = v;
	head[u] = cnt++;
}
int dep[maxn], lg[N] = { -1, 0 }, st[20][N], dfn[maxn], a[N], t = 0;
namespace LCA {
	void getdfn(int u, int f) {
		dfn[u] = ++t, a[t] = u, dep[u] = dep[f] + 1;
		for (int i = head[u]; ~i; i = node[i].nxt) {
			int v = node[i].to;
			if (v == f) continue;
			getdfn(v, u);
			a[++t] = u;
		}
	}
	void buildst() {
		for (int i = 1; i <= t; i++) st[0][i] = a[i], lg[i] = lg[i >> 1] + 1;
		for (int j = 1; j <= 19; j++) {
			for (int i = 1; i + (1 << j) <= t; i++) {
				int p1 = st[j - 1][i], p2 = st[j - 1][i + (1 << j - 1)];
				st[j][i] = dep[p1] < dep[p2] ? p1 : p2;
			}
		}
	}
	inline int lca(int u, int v) {
		u = dfn[u], v = dfn[v];
		if (u > v) swap(u, v);
		int g = lg[v - u + 1];
		int p1 = st[g][u], p2 = st[g][v - (1 << g) + 1];
		return dep[p1] < dep[p2] ? p1 : p2;
	}
}
vector<int>c[maxn]; int w[maxn], id[maxn];
using LCA::lca;
namespace vtree {
	int s[maxn], dp[maxn];
	int key[maxn], ks = 0;
	void build(int col) {
		int top = 0; s[++top] = 1;
		dp[1] = (w[1] == col);
		for (re int i = 1; i <= ks; i++) {
			int u = key[i];
			if (u == 1) continue;
			int l = lca(s[top], u);
			if (l != s[top]) {
				while (dfn[l] < dfn[s[top - 1]]) dp[s[top - 1]] += dp[s[top]], --top;
				if (dfn[l] > dfn[s[top - 1]]) dp[l] = (w[l] == col), dp[l] += dp[s[top]], s[top] = l;
				else dp[l] += dp[s[top]], --top;
			}
			dp[u] = (w[u] == col);
			s[++top] = u;
		}
		for (re int i = top - 1; i >= 1; i--) dp[s[i]] += dp[s[i + 1]];
		ks = top = 0;
	}
}
using vtree::key;
using vtree::ks;
using vtree::dp;
int s[505][maxn], g[505][maxn], bh[maxn];
void work(int u, int f, int uc, int now) {
	int bc = id[uc];
	if (w[u] == uc) s[bc][u] = 1, ++now; g[bc][u] = now;
	for (int i = head[u]; ~i; i = node[i].nxt) {
		int v = node[i].to;
		if (v == f) continue;
		work(v, u, uc, now);
		s[bc][u] += s[bc][v];
	}
}
inline int cmp(int x, int y) { return dfn[x] < dfn[y]; }
inline int cmp2(int x, int y) { return dfn[x] <= dfn[y]; }
int ANS[505][505];
inline void solve(int x, int y, int& sum) {
	int p1 = 0, p2 = 0;
	while (c[x][p1] || c[y][p2]) {
		while (cmp2(c[x][p1], c[y][p2]) && c[x][p1] != 0) key[++ks] = c[x][p1], ++p1;
		while (cmp2(c[y][p2], c[x][p1]) && c[y][p2] != 0) key[++ks] = c[y][p2], ++p2;
		if (c[x][p1] == 0) while (c[y][p2] != 0) key[++ks] = c[y][p2], ++p2;
		if (c[y][p2] == 0) while (c[x][p1] != 0) key[++ks] = c[x][p1], ++p1;
	}
	vtree::build(y);
	for (int k = 0; k < c[x].size(); k++) sum += dp[c[x][k]], dp[c[x][k]] = 0;
}
int main() {
	memset(head, -1, sizeof(head));
	n = read(), r = read(), q = read(), w[1] = read();
	c[w[1]].push_back(1);
	for (int i = 2; i <= n; i++) {
		int x;
		x = read(); w[i] = read();
		add(i, x); add(x, i);
		c[w[i]].push_back(i);
	}
	dfn[0] = 1e9; int len = 0;
	LCA::getdfn(1, 0); LCA::buildst();
	for (int i = 1; i <= r; i++) sort(c[i].begin(), c[i].end(), cmp), c[i].push_back(0);
	for (int i = 1; i <= r; i++) if (c[i].size() > S) id[i] = ++len, bh[id[i]] = i, work(1, 0, i, 0);
	for (int i = 1; i <= len; i++) {
		for (int j = 1; j <= len; j++) {
			if (i == j) continue;
			//颜色 bh[i] 的所有结点，颜色 bh[j] 的所有结点
			int p1 = 0, p2 = 0, x = bh[i], y = bh[j];
			solve(x, y, ANS[i][j]);
		}
	}
	while (q--) {
		int x, y, ans = 0;
		x = read(); y = read();
		//计算颜色为 x，颜色为 y，祖先是 x，后代是 y
		if (c[x].size() <= 30 && c[y].size() <= 30) {
		    for (int i = 0; i < c[x].size() - 1; i++) {
		        for (int j = 0; j < c[y].size() - 1; j++) {
		            if (lca(c[x][i], c[y][j]) == c[x][i]) ++ans;
		        }
		    }
		    printf("%d\n", ans);
		}
		else if (c[x].size() <= S && c[y].size() <= S) {
			solve(x, y, ans);
			printf("%d\n", ans);
		}
		else if (c[x].size() <= S) {
			int iy = id[y];
			for (re int i = 0; i < c[x].size() - 1; i++) ans += s[iy][c[x][i]];
			printf("%d\n", ans);
		}
		else if (c[y].size() <= S) {
			int ix = id[x];
			for (re int i = 0; i < c[y].size() - 1; i++) ans += g[ix][c[y][i]];
			printf("%d\n", ans);
		}
		else printf("%d\n", ANS[id[x]][id[y]]);
		fflush(stdout);
	}
	return 0;
}
```


---

## 作者：Purslane (赞：0)

# Solution

直接考虑根号分治。

如果其中某个地区的人数超过了 $\sqrt n$ 就可以预处理。这样的地区的数量不超过 $\sqrt n$ 个。暴力计算他们做先辈和做后辈的答案。（用一个树上前缀和即可）

否则，这两个地区的总人数之和也不会超过 $2 \sqrt n$。考虑在每个祖先除计算答案，它想让对方的 DFS 序的值应当是在一个区间中。那么我们可以先预处理出每个地区的 DFS 序以及它对其他人要求（差分一下）排序后的结果。然后扫描线一下就可以了。

总复杂度为 $O(n \sqrt n)$（认为 $nq$ 同阶。）

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=2e5+10,MAXK=400+10,MAXM=2.5e4+10;
int n,q,r,rt,tot,sze[MAXN],dfn[MAXN],pre[MAXN],esid[MAXN],bl=500;
vector<int> G[MAXN],pos[MAXM],dfn_st[MAXM];
vector<pair<int,int>> qr[MAXM];
ll ans1[MAXK][MAXM],ans2[MAXK][MAXM];
void dfs(int u) {
	dfn[u]=++tot,sze[u]=1;
	for(auto v:G[u]) dfs(v),sze[u]+=sze[v];
	return ;	
}
void add_pre1(int u) {
	for(auto v:G[u]) pre[v]+=pre[u],add_pre1(v);
	return ;
}
void add_pre2(int u) {
	for(auto v:G[u]) add_pre2(v),pre[u]+=pre[v];
	return ;	
}
void solve(int bl,int tot) { //1 bl 做祖先 
	ffor(i,1,n) pre[i]=0;
	for(auto id:pos[bl]) pre[id]=1;
	add_pre1(1);
	ffor(i,1,r) for(auto id:pos[i]) ans1[tot][i]+=pre[id];	
	ffor(i,1,n) pre[i]=0;
	for(auto id:pos[bl]) pre[id]=1;
	add_pre2(1);
	ffor(i,1,r) for(auto id:pos[i]) ans2[tot][i]+=pre[id];	
	return ;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>r>>q>>rt,pos[rt].push_back(1);
	ffor(i,2,n) {int bl,fa; cin>>fa>>bl,G[fa].push_back(i),pos[bl].push_back(i);}
	dfs(1),tot=0;
	ffor(i,1,r) for(auto id:pos[i]) dfn_st[i].push_back(dfn[id]),qr[i].push_back({dfn[id],1}),qr[i].push_back({dfn[id]+sze[id],-1});
	ffor(i,1,r) sort(dfn_st[i].begin(),dfn_st[i].end()),sort(qr[i].begin(),qr[i].end());
	ffor(i,1,r) if(pos[i].size()>bl) esid[i]=++tot,solve(i,tot);
	ffor(i,1,q) {
		int r1,r2;
		cin>>r1>>r2;
		if(pos[r1].size()>bl) cout<<ans1[esid[r1]][r2]<<endl;
		else if(pos[r2].size()>bl) cout<<ans2[esid[r2]][r1]<<endl;
		else {
			ll ans=0; int cnt=pos[r2].size(),tpos=0;
			for(auto pr:qr[r1]) {
				int id=pr.first,op=pr.second;
				while(tpos<dfn_st[r2].size()&&dfn_st[r2][tpos]<id) tpos++,cnt--;	
				ans+=op*cnt;
			}
			cout<<ans<<endl;
		}
	}
	return 0;
}

```

---

## 作者：Hanx16Kira (赞：0)

# [IOI2009] Regions

[Luogu P5901](https://www.luogu.com.cn/problem/P5901)

## Solution

先尝试去想暴力，很容易想到两种不同的暴力做法：

- 分别枚举两个颜色中的所有点，利用 Dfs 序判定一个点是否在另一个点的子树内。
- 将一个颜色内的所有点先加入到一个数据结构内，然后枚举另一个颜色的所有点，查看有多少点在当前子树。

第一种做法时间最劣是 $\mathcal O(n^2)$ 的，第二种做法空间最劣是 $\mathcal O(n^2)$ 的。考虑综合一下这两种做法。使用根号分治，按照颜色的点数进行根号分治。将点数在阈值之上的称为重颜色，否则称为轻颜色。分类讨论一下：

- 重颜色作为祖先节点：不妨预处理所有重颜色作为祖先节点的情况的答案，容易做到 $\mathcal O(n\sqrt {n\log n})$ 时间预处理，$\mathcal O(R\sqrt n)$ 空间。
- 轻颜色作为祖先节点：枚举轻颜色内的所有点，然后对于每个颜色开一个 `vector` 按照 Dfs 序将所有点排序就可以直接二分找到所有满足条件的子节点，时间可以做到 $\mathcal O(n\sqrt{n\log n})$。

总时间复杂度 $\mathcal O(n\sqrt {n\log n})$，空间复杂度 $\mathcal O(R\sqrt n)$。

```cpp
#include <bits/stdc++.h>
#define All(x) x.begin(), x.end()
using namespace std;
constexpr int _N = 2e5 + 5, _B = 450 + 5, _R = 2.5e4 + 5;
int N, R, Q, Lim;
vector<int> e[_N];
int f[_B][_R], dfn[_N], cnt[_N], ord, id[_N], siz[_N], di[_N], d[_N];
vector<int> vec[_N], vdfn[_N];
void Dfs(int x) {
    dfn[x] = ++ord, siz[x] = 1;
    for (int v: e[x]) Dfs(v), siz[x] += siz[v];
}
signed main() {
    cin >> N >> R >> Q;
    Lim = sqrt(N * log2(N) * 2);
    for (int i = 1; i <= N; ++i) {
        if (i != 1) {
            int fa; cin >> fa;
            e[fa].push_back(i);
        }
        int col; cin >> col;
        vec[col].push_back(i);
        ++cnt[col];
    }
    iota(id + 1, id + R + 1, 1);
    sort(id + 1, id + R + 1, [&](const int &i, const int &j) {
        return cnt[i] > cnt[j];
    });
    Dfs(1);
    for (int i = 1; i <= R; ++i) {
        di[id[i]] = i;
        for (int x: vec[i]) vdfn[i].push_back(dfn[x]);
        sort(All(vdfn[i]));
    }
    for (int i = 1; i <= R; ++i) {
        if (cnt[id[i]] < Lim) break;
        for (int i = 1; i <= N + 1; ++i) d[i] = 0;
        for (int x: vec[id[i]]) ++d[dfn[x]], --d[dfn[x] + siz[x]];
        partial_sum(d, d + N + 1, d);
        for (int j = 1; j <= R; ++j) for (int x: vec[j])
            f[i][j] += d[dfn[x]];
    }
    while (Q--) {
        int r1, r2; cin >> r1 >> r2;
        if (cnt[r1] < Lim) {
            int res = 0;
            for (int x: vec[r1])
                res += upper_bound(All(vdfn[r2]), dfn[x] + siz[x] - 1) -
                       lower_bound(All(vdfn[r2]), dfn[x]);
            cout << res << endl;
        } else cout << f[di[r1]][r2] << endl;
    }
}
```

---

## 作者：__ycx2010__ (赞：0)

### 简化题意

给你一棵树，每个点有一个颜色，$Q$ 次询问，每次询问给出 $r_1$ 和 $r_2$,求祖孙节点 $(x,y)$ 满足 $x$ 的颜色为 $r_1$ 且 $y$ 的颜色为 $r_2$ 的祖孙节点的对数。

### 思路

运用根号分支，设树上某个颜色出现了大于 $\sqrt{n}$ 次，则称之为重颜色，否则称之为轻颜色。

对于每一轮询问 $(r_1,r_2)$：

- 若 $r_2$ 为重颜色，那么 $r_2$ 最多有 $\sqrt{n}$ 种可能，所以可能的询问 $(r_1,r_2)$ 的种数最多为 $n\sqrt{n}$ 个，对于整棵树进行预处理，将树转成 $dfn$ 序的形式，对于一个点，若其为重颜色，则在主席树中在对应颜色位置加一。那么对于每一个点，可以用它子树的 $dfn$ 序下标求出子树中每一个重颜色的个数，于是就可以预处理出所有 $(r_1,r_2)$ 的答案，时间复杂度 $O(n\sqrt{n}\log{\sqrt{n}})$（为了避免 MLE 所以使用了主席树）。

- 否则若 $r_1$ 为重颜色，同理也只有 $n\sqrt{n}$ 种可能，于是要求的是每一个节点的祖宗节点中，每个重颜色出现的次数，在遍历树的时候可以顺便处理，时间复杂度 $O(n)$。

- 否则 $r_1$ 和 $r_2$ 均为轻颜色，将所有颜色为 $r_2$ 的节点在 $dfn$ 序下加入树状数组，再对于每一个 $r_1$ 节点，在树状数组中求即可，时间复杂度 $O(q \sqrt{n}\log n)$。

综上所述，我们现在有了一个时间复杂度 $O(n\sqrt{n}\log n)$，空间复杂度 $O(R\sqrt{n})$ 的算法，由于空间卡的紧，所以将块长稍调大。


### 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 200010, M = 300, K = 25010;
int n, r, q, L;
int h[N], e[N], ne[N], idx;
int c[N], cnt[K], g[K], le[N], ri[N], w[N], tmp, tot;
int s2[M], rt[N];
ll ans[K][M], ans2[M][K];
vector<int> gg[K];

struct Tree {
	int tr[N];
	void add(int x, int k) {
		for (int i = x; i <= n; i += i & -i) tr[i] += k;
	} int query(int x) {
		int res = 0;
		for (int i = x; i; i -= i & -i) res += tr[i];
		return res;
	} int qry(int lll, int rr) {return query(rr) - query(lll - 1);}
} T;

struct sgt {
    int tt;
    struct Node {
        int l, r, s;
    } tr[N * 10];
    void modify(int &u, int l, int r, int p, int k) {
        tr[++ tt] = tr[u], tr[tt].s += k, u = tt;
        if (l == r) return;
        int mid = l + r >> 1;
        if (p <= mid) modify(tr[u].l, l, mid, p, k);
        else modify(tr[u].r, mid + 1, r, p, k);
    } int query(int u, int l, int r, int p) {
        if (!u) return 0;
        if (l == r) return tr[u].s;
        int mid = l + r >> 1;
        if (p <= mid) return query(tr[u].l, l, mid, p);
        return query(tr[u].r, mid + 1, r, p);
    }
} T2;

void add_edge(int a, int b) {
	e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}

void dfs(int u, int fa) {
	for (int i = 1; i <= tmp; i ++ ) ans2[i][c[u]] += s2[i];
	le[u] = ++ tot, w[tot] = u;
	if (cnt[c[u]] > L) s2[g[c[u]]] ++ ;
	for (int i = h[u]; ~i; i = ne[i]) {
		int ver = e[i];
		if (ver == fa) continue;
		dfs(ver, u);
	}
	if (cnt[c[u]] > L) s2[g[c[u]]] -- ;
	ri[u] = tot;
}

int main() {
	scanf("%d%d%d%d", &n, &r, &q, &c[1]);
	T2.tt = n;
	L = max((int)sqrt(n), 650);
	memset(h, -1, sizeof h);
	for (int i = 2; i <= n; i ++ ) {
		int p;
		scanf("%d%d", &p, &c[i]);
		add_edge(p, i);
		cnt[c[i]] ++ ;
	}
	for (int i = 1; i <= n; i ++ ) gg[c[i]].push_back(i);
	for (int i = 1; i <= r; i ++ ) if (cnt[i] > L) g[i] = ++ tmp;
	dfs(1, 0);
	for (int i = 1; i <= n; i ++ ) {
	    rt[i] = i;
	    T2.tr[rt[i]] = T2.tr[rt[i - 1]];
	    if (cnt[c[w[i]]] > L) T2.modify(rt[i], 1, tmp, g[c[w[i]]], 1);
	}
	for (int i = 1; i <= n; i ++ )
	    for (int j = 1; j <= tmp; j ++ )
	        ans[c[i]][j] += T2.query(rt[ri[i]], 1, tmp, j) - T2.query(rt[le[i] - 1], 1, tmp, j);
	while (q -- ) {
		int r1, r2;
		scanf("%d%d", &r1, &r2);
		if (cnt[r2] > L) printf("%lld\n", ans[r1][g[r2]]);
		else if (cnt[r1] > L) printf("%lld\n", ans2[g[r1]][r2]);
		else {
			ll res = 0;
			for (int k : gg[r2]) T.add(le[k], 1);
			for (int k : gg[r1]) res += T.qry(le[k] + 1, ri[k]);
			for (int k : gg[r2]) T.add(le[k], -1);
			printf("%lld\n", res);
		}
		fflush(stdout);
	}
	return 0;
}
```


---

## 作者：Usada_Pekora (赞：0)

题意：给定一棵树，每个点有颜色，$q$ 次询问问满足 $u$ 的颜色是 $r_1$，$v$ 的颜色是 $r_2$，且 $u$ 是 $v$ 的祖先的点对 $(u,v)$ 有多少对。

看到颜色出现次数总数是 $n$ 考虑根号分治。

对于出现次数超过 $B$ 的只有 $O(\frac{n}{B})$ 种，我们可以暴力预处理它们的答案，要处理 $x$ 作为某一参数的答案是简单的：对于每种颜色，要处理 $r_1=x$ 时的答案，是问它们的祖先里有多少个 $x$，这个可以作根到它的前缀和，一次 DFS 解决；若要处理 $r_2=x$ 的询问，则是问子树里有多少个 $x$，这个也可以一次 DFS，复杂度 $O(\frac{n^2}{B})$。

对于出现次数不超过 $B$ 的颜色，我们直接暴力做就好了，由于 $r_1,r_2$ 的次数都不超过 $B$，其实是 $B$ 个询问 $B$ 个点的一维数点，注意每次询问重新排序是 $O(qB\log B)$ 的，事实上可以提前排好序，这样就可以 $O(qB)$。

由于 $O(n)=O(q)$，我们取 $B=\sqrt n$ 可以做到 $O(n\sqrt n)$ 的复杂度。

```cpp
#include <bits/stdc++.h>
#define pb emplace_back
#define mkp make_pair
using namespace std;
typedef long long ll;
typedef long double lf;
const int N = 2e5 + 5, B = 449, inf = 0x3f3f3f3f;
template<typename T> inline bool chkmax(T &x, const T &y) {
	return (x < y) && (x = y, true);
}
template<typename T> inline bool chkmin(T &x, const T &y) {
	return (y < x) && (x = y, true);
}
int n, m, q, c[N], idx, dfn[N], rdfn[N], siz[N], hvy[N], sum;
int ans1[B][25005], ans2[B][25005];
vector<int> col[N], g[N];
vector<pair<int, int>> qr[N];
inline void dfs(int u, int rt) {
	static int ord = 0;
	dfn[u] = ++ord;
	for (int v : g[u])
		if (v != rt)
			dfs(v, u);
	rdfn[u] = ord;
}
inline void dfs1(int u, int rt, int cl) {
	ans1[idx][c[u]] += sum;
	sum += (c[u] == cl);
	for (int v : g[u])
		if (v != rt)
			dfs1(v, u, cl);
	sum -= (c[u] == cl);
}
inline void dfs2(int u, int rt, int cl) {
	siz[u] = 0;
	for (int v : g[u]) {
		if (v != rt) {
			dfs2(v, u, cl);
			siz[u] += siz[v];
		}
	}
	ans2[idx][c[u]] += siz[u];
	siz[u] += (c[u] == cl);
}
signed main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cin >> n >> m >> q;
	for (int i = 1, fa; i <= n; i++) {
		if (i > 1) {
			cin >> fa;
			g[fa].pb(i);
		}
		cin >> c[i], col[c[i]].pb(i);
	}
	dfs(1, 0);
	for (int i = 1; i <= m; i++) {
		if (col[i].size() > B) {
			hvy[i] = ++idx;
			dfs1(1, 0, i), dfs2(1, 0, i);
		} else {
			for (int j : col[i])
				qr[i].pb(dfn[j] - 1, -1), qr[i].pb(rdfn[j], 1);
			sort(qr[i].begin(), qr[i].end()), sort(col[i].begin(), col[i].end(), [&](int i, int j) -> bool { return dfn[i] < dfn[j]; });
		}
	}
	while (q--) {
		int r1, r2;
		cin >> r1 >> r2;
		if (hvy[r1])
			cout << ans1[hvy[r1]][r2] << endl;
		else if (hvy[r2])
			cout << ans2[hvy[r2]][r1] << endl;
		else {
			int res = 0, i = -1;
			for (auto [x, op] : qr[r1]) {
				while (i + 1 < col[r2].size() && dfn[col[r2][i + 1]] <= x)
					i++;
				res += op * (i + 1);
			}
			cout << res << endl;
		}
	}
	return 0;
}
```

---

## 作者：RedLycoris (赞：0)

题目意思很清楚不用说。

看到每个点都有颜色，然后询问和颜色的种类有关，时限开了很【】的 8s，就可以往根号分治方面想了。

按照常理，我们钦定一个 $B$，所有颜色为 $i$ 的点的集合为 $col_i$。

如果 $|col_x| \le B$ 且 $|col_y|<B$，则他们都是小块，可以直接建立出虚树暴力跑，单次询问时间复杂度 $O(\sqrt{n})$。

如果 $|col_x| > B$ 且 $|col_y| \le B$，那么我们可以进行预处理。对于所有的大块（设其颜色为 $c$），我们处理处其 $up$ 数组，$up_i$ 表示在第 $i$ 个节点到根结点的路上，有多少个颜色为 $c$ 的节点，然后在询问的时候直接计算 $\sum\limits_{v \in col_y}up_v$ 即可。预处理时间复杂度 $O(n\sqrt{n})$，单次询问时间复杂度 $O(\sqrt{n})$。

同理，如果 $|col_x| \le B$ 且 $|col_y| > B$，那么我们可以预处理 $dw_i$ 表示第 $i$ 个节点的子树中有多少个节点的颜色为 $c$，询问时计算 $\sum\limits_{v \in col_x}dw_v$。时间复杂度同上。

最后，如果 $|col_x| > B$ 且 $|col_y| > B$，那么和小块对小块一样，可以预处理，对于所有可能的大块对建出虚树算一遍答案，询问时直接调用即可。时间复杂度 $O(n\sqrt{n})$。

---

上述全部为口胡，如果实现不精细的话，时间复杂度会写成 $O(n\sqrt{nlogn})$ 且常数巨大，导致你可能只有 60pts 的好成绩。

---

1. 普通的倍增LCA的询问是 $O(logn)$ 的，我们要用 ST 表做到 $O(nlogn)$ 预处理，$O(1)$ 求 LCA。

2. 在建立虚树的时候，有一步要对所有点按照 dfs 序排序。如果不想写基数排序怎么办？可以在询问前先对每个 $col_i$ 中的元素先按照字典序排序，在询问的时候用类似归并排序的方法 merge 两个有序的 $col_x$ 和 $col_y$，就可以把这个 $logn$ 砍掉了。

---

现在的时间复杂度已经降到了正好的 $O(n\sqrt{n})$，但是巨大的常数仍让你在 94pts 和 97pts 之间徘徊。

为了减小常数：

1. 加入快读快输

2. 小对小和大对大中暴力统计答案的dfs看起来很累赘，那么短。如果我们能够想办法把这一步放入建立虚树的过程中，那么就可以避免存虚树的边，从而大幅减小常数（感谢 [w23c3c3](https://www.luogu.com.cn/user/109942) 的指导）

然后这样就能过了。

---

Talk is cheap, show me the code.

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define mp make_pair
#define reg register
const int maxn=10005;        //很好的快读板子
char buffer[maxn],*S,*T;
inline char Get_Char(){
    if(S==T){
        T=(S=buffer)+fread(buffer,1,maxn,stdin);
        if(S==T)return EOF;
    }
    return *S++;
}
inline int read(){
    reg char c;
    reg int re=0,f=0;
    for(c=Get_Char();c<'0' or c>'9';c=Get_Char())if(c=='-')f=1;
    for(;c>='0' and c<='9';)re=(re<<1)+(re<<3)+(c-'0'),c=Get_Char();
    if(f)return -re;
    return re;
}
inline void read(int&x){
    reg char c;
    reg int re=0,f=0;
    for(c=Get_Char();c<'0' or c>'9';c=Get_Char())if(c=='-')f=1;
    for(;c>='0' and c<='9';)re=(re<<1)+(re<<3)+(c-'0'),c=Get_Char();
    if(f)x=-re;
    else x=re;
}
inline void read(ll&x){
    reg char c;
    reg ll re=0,f=0;
    for(c=Get_Char();c<'0' or c>'9';c=Get_Char())if(c=='-')f=1;
    for(;c>='0' and c<='9';)re=(re<<1)+(re<<3)+(c-'0'),c=Get_Char();
    if(f)x=-re;
    else x=re;
}
inline void print(int x){
	if(x<10){
		putchar(x+'0');
		return;
	}
	print(x/10);
	putchar(x%10+'0');
}
const int mxn=2e5+5;
vector<int>g[mxn];
int n,R,q,r[mxn];
int dep[mxn*2];
int ord[mxn*2],cco,cord[mxn*2];
int mi[mxn*2][22];
int lg[mxn*2],co;
int st[mxn*2],ed[mxn*2];
inline void dfs(int x,int par=0,int deep=1){
	cord[++cco]=x;
	st[x]=cco;ed[x]=cco;
	dep[x]=deep;ord[x]=++co;
	for(int y:g[x]){
		if(par==y)continue;
		dfs(y,x,deep+1);
		cord[++cco]=x;
		ed[x]=cco;
	}
}
inline void init(){     //预处理ST表
	lg[1]=0;
	for(int i=2;i<mxn*2;++i)lg[i]=lg[i>>1]+1;
	for(int i=1;i<=cco;++i)mi[i][0]=cord[i];
	for(int k=1;k<22;++k){
		for(int i=1;i<=cco-(1<<k)+1;++i){
			int x=mi[i][k-1],y=mi[i+(1<<(k-1))][k-1];
			if(dep[x]<dep[y])mi[i][k]=x;
			else mi[i][k]=y;
		}
	}
}
inline int lca(int x,int y){
	int fx=st[x],fy=ed[y];
	if(fx>fy)swap(fx,fy);
	int ax=mi[fx][lg[fy-fx]],ay=mi[fy-(1<<lg[fy-fx])+1][lg[fy-fx]];
	if(dep[ax]<dep[ay])return ax;
	else return ay;
} 
inline bool cmp(int x,int y){return ord[x]<ord[y];}
int sta[mxn],top=0;
int sz[mxn];
int up[404][mxn],dw[404][mxn];
inline vector<int>mer(vector<int>x,vector<int>y){  //类似归并的操作
	vector<int>rt;rt.clear();
	int i=0,j=0;
	for(;i<x.size() and j<y.size();)
		if(cmp(x[i],y[j]))rt.push_back(x[i]),++i;
		else rt.push_back(y[j]),++j;
	for(;i<x.size();++i)rt.push_back(x[i]);
	for(;j<y.size();++j)rt.push_back(y[j]);
	return rt;
}
inline void gen(vector<int>v,int y){  //建立虚树
	top=0;
	sta[++top]=1;
	sz[1]=r[1]==y;
	for(int i:v){
		if(i!=1){
			int l=lca(sta[top],i);
			if(l!=sta[top]){
				for(;ord[l]<ord[sta[top-1]];)sz[sta[top-1]]+=sz[sta[top]],--top;
				if(ord[l]>ord[sta[top-1]]){
					sz[l]=r[l]==y;
					sz[l]+=sz[sta[top]];
					sta[top]=l;
				}else sz[l]+=sz[sta[top]],top--;
			}
			sz[i]=r[i]==y;
			sta[++top]=i;	
		}
	}
	for(int i=top-1;i>=1;--i)sz[sta[i]]+=sz[sta[i+1]];
}
vector<int>col[mxn];
vector<int>hea;
int ans[404][404];
int id[mxn];
//inline void getans(int x,int fa,int cl){//on ng[]    //原来的暴力统计小对小和大对大的答案
//	if(r[x]==cl)sz[x]=1;
//	else sz[x]=0;
//	for(int y:ng[x])if(y!=fa)getans(y,x,cl),sz[x]+=sz[y];
//}
inline void prep(int x,int fa,int cl,int flg=0){   //预处理小对大和大对小的up和dw数组
	if(r[x]==hea[cl])dw[cl][x]=1,++flg;
	up[cl][x]=flg;
	for(int y:g[x])if(y!=fa){
		prep(y,x,cl,flg);
		dw[cl][x]+=dw[cl][y];
	}
}
inline void solve(){
	memset(id,-1,sizeof(id));
	read(n),read(R),read(q);
	read(r[1]);col[r[1]].push_back(1);
	for(int i=2;i<=n;++i){
		int x;read(x),read(r[i]);
		g[x].push_back(i);
		g[i].push_back(x);
		col[r[i]].push_back(i);
	}
	dfs(1);
	init();
	int bound=500;
	for(int i=1;i<=R;++i)if(col[i].size()>=bound)hea.push_back(i);  //这里我的B定为了500
	for(int i=0;i<hea.size();++i)id[hea[i]]=i;
	for(int i=1;i<=n;++i)sort(col[i].begin(),col[i].end(),cmp);
	for(int i=0;i<hea.size();++i)for(int j=0;j<hea.size();++j)if(i!=j){
		gen(mer(col[hea[i]],col[hea[j]]),hea[j]);
//		getans(1,0,hea[j]);
		ll res=0;
		for(int f:col[hea[i]])res+=sz[f];
		ans[i][j]=res;
	}
	for(int i=0;i<hea.size();++i)prep(1,0,i);
	for(;q--;){
		int x,y;read(x),read(y);
		if(~id[x] and ~id[y])print(ans[id[x]][id[y]]),putchar('\n');
		else if(~id[x] and id[y]==-1){
			ll res=0;
			for(int i:col[y])res+=up[id[x]][i];
			print(res),putchar('\n');
		}else if(id[x]==-1 and ~id[y]){
			ll res=0;
			for(int i:col[x])res+=dw[id[y]][i];
			print(res),putchar('\n');
		}else{
			gen(mer(col[x],col[y]),y);
//			getans(1,0,y);
			ll res=0;
			for(int f:col[x])res+=sz[f];
			print(res),putchar('\n');
		}
	}
}
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int T=1;
	//cin>>T;
	for(;T--;)solve();
	return 0;
}
```

---

