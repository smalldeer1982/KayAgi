# Connect the Dots

## 题目描述

### 题意描述
爱丽丝画了一条直线，并在上面标记了n个点，从1到n进行索引。最初，点之间没有弧，所以它们都是不相交的。之后，Alice执行以下类型的m个操作：

1.   她选了三个整数ai bi和ki
2.   她选择点ai，ai+di,ai+2di......ai+ki*di，并用弧线连接每对点。

在完成所有m操作后，她想知道这些点形成的连接组件的数量。

如果两个点之间通过几个（**可能为零**）弧和其他点存在路径，则称这两个点位于一个连接的组件中。

## 样例 #1

### 输入

```
3
10 2
1 2 4
2 2 4
100 1
19 2 4
100 3
1 2 5
7 2 6
17 2 31```

### 输出

```
2
96
61```

# 题解

## 作者：DrAlfred (赞：10)

摘要：并查集，分组，离线，双指针，排序

[传送门：https://www.luogu.com.cn/problem/CF2020D](https://www.luogu.com.cn/problem/CF2020D)

## 题意

给定一张有 $n$ 个点，一开始没有边的图。Alice 对这张图进行了 $m$ 次操作。每次操作，她会选择三个参数 $a, k, d$，将 $a, a + d, a + 2d, \dots, a + kd$ 这 $k + 1$ 个点两两连边。问经过了 $m$ 次操作之后，这张图一共有几个连通分量。

## 分析思路

首先观察到题目中的 $1 \le d \le 10$，再观察一下 $a, a + d, \dots, a + kd$ 这些点，可以发现他们模 $d$ 的值都是相等的。考虑对操作离线。

我们按照 $d$ 和 $a \bmod d$ 的值对操作进行分类。对于同一类操作，如果某两个操作的点有交集，那么这两个操作**等价于他们合并之后的操作**，因为这两个操作中的任意一个点都可以先走到交集中的某个点，再走到另一个点。于是这两个操作**并集中的所有点**最后都会在同一个连通分量中。

所以，对于每一类操作，我们可以排序后使用双指针进行集合求并，得到若干个极大的操作，然后再使用并查集进行暴力连边。这样可以保证每个点最多只会被暴力操作 $10$ 次。集合求并的复杂度为 $O(m \log m)$，暴力连边时间复杂度 $O(n \times \max d)$，总时间复杂度 $O(m \log m + n \times \max d_i)$，可以通过本题。
 
## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
struct DSU {
    std::vector<int> fa, siz;
    DSU(int n) : fa(n + 1), siz(n + 1, 1) {
        std::iota(fa.begin(), fa.end(), 0);
    }
    inline int find(int x) {
        return fa[x] == x ? x : fa[x] = find(fa[x]);
    }
    inline bool same(int x, int y) {
        return find(x) == find(y);
    }
    // true if x and y were not in the same set, false otherwise.
    inline bool merge(int x, int y) {
        int fx = find(x), fy = find(y);
        if (fx == fy) return false;
        if (siz[fx] < siz[fy]) swap(fx, fy);
        fa[fy] = fx, siz[fx] += siz[fy], siz[fy] = 0;
        return true;
    }
    // x -> y, a.k.a let x be son of y (disable merge by rank).
    inline bool directed_merge(int x, int y) {
        int fx = find(x), fy = find(y);
        if (fx == fy) return false;
        fa[fx] = fy, siz[fy] += siz[fx], siz[fx] = 0;
        return true;
    }
};
int t, n, m, a, k, d;
inline void solve(void) {
    cin >> n >> m;
    vector<pair<int, int>> segs[11][11];
    for (int i = 1; i <= m; i++) {
        cin >> a >> d >> k;
        segs[d][a % d].push_back({a, a + k * d});
    }
    DSU D(n);
    int ans = n;
    for (int i = 1; i <= 10; i++) {
        for (int rem = 0; rem < i; rem++) {
            auto &seg = segs[i][rem];
            const int siz = seg.size();
            sort(seg.begin(), seg.end());
            for (int l = 0, r = 0; l < siz; l = r) {
                int L = seg[l].first, R = seg[l].second;
                while (r < siz && seg[r].first <= R) {
                    R = max(R, seg[r].second), r++;
                }
                for (int j = L; j < R; j += i) {
                    ans -= D.merge(j, j + i);
                }
            }
        }
    }
    cout << ans << '\n';
}
inline void optimizeIO(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
}
int main(int argc, char const *argv[]) {
    optimizeIO(), cin >> t;
    while (t--) solve();
    return 0;
}

```

---

## 作者：aeiouaoeiu (赞：6)

考虑 $d=1$ 怎么做。实际上一次修改就是将一个区间合并到了一起。用并查集跳即可。

考虑只有一种 $d$ 怎么做。实际上就是按编号除以 $d$ 的余数分成了 $d$ 种点。每次修改就将其中一种点的一段连续区间合并，仍然可以使用并查集跳。

考虑本题。直接开 $d$ 种并查集即可。最后可以再用一个并查集，将每个并查集中 $i$ 及其父亲合并，这样就将 $d$ 个并查集合并了。

时间复杂度 $\mathcal{O}(n\log n\cdot D)$，其中 $D=10$，通过记录连通块编号最大点可以使用按秩合并或启发式合并，做到 $\mathcal{O}(n\alpha(n)\cdot D)$。

```cpp
#include<bits/stdc++.h>
#define pb emplace_back
#define pob pop_back
#define mp make_pair
using namespace std;
typedef int ll;
typedef __int128 LL;
const ll maxn=200007,ee=1e18,p=998244353;
struct Dsu{
	ll fa[maxn];
	ll fid(ll x){for(;x^fa[x];x=fa[x]=fa[fa[x]]); return x;}
	void merge(ll x,ll y){
		x=fid(x),y=fid(y); if(x==y) return;
		if(x>y) fa[y]=x;
		else fa[x]=y;
	}
}dsu[11];
ll n,m,ans;
int main(void){
	//freopen("data.in","r",stdin);
	//freopen("data.out","w",stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	ll T=1; cin>>T;
	for(;T--;){
		cin>>n>>m; ans=0;
		for(int i=0;i<=10;i++) iota(dsu[i].fa+1,dsu[i].fa+1+n,1);
		for(int i=1,a,d,k,fr,ed;i<=m;i++){
			cin>>a>>d>>k; if(k==0) continue;
			fr=a,ed=a+d*k;
			for(int j=fr+d;j<=ed;j=dsu[d].fid(j+d)){
				dsu[d].merge(j-d,j);
				if(j+d>ed) break;
				dsu[d].merge(j,j+d);
			}
		}
		for(int j=1;j<=10;j++)for(int i=1;i<=n;i++) dsu[0].merge(dsu[j].fid(i),i);
		for(int i=1;i<=n;i++)if(dsu[0].fid(i)==i) ans++;
		cout<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：__3E24AC7002AD9292__ (赞：5)

太菜了，打 VP 的时候没看到 $d\leq10$，所以以下是 $d\leq n$ 的解法（这个解法改到本题可以爆标）。

看到 $a,a+d,a+2d,\dots,a+kd$ 这类下标的修改，就不难想到对 $d$ 进行根号分治。

具体地，一种直接的暴力是：枚举 $a+id$ 并将他们暴力合并。因为最终求的是连通块数量，所以合并可以使用并查集，这样不需要两两建边，只需并查集合并相邻两个即可。

还有另一种不那么直接暴力是：离线记录每个 $a,d$ 操作时对应的最大 $k$，记录为 $f_{a,d}$，最后统一处理。处理的时候，枚举 $d$，再枚举一个 $a'\in[1,d]$，并对 $a=a',a'+d,a'+2d,\dots,a'+pd$ 统一处理，我们把这些 $a$ 称为一组，标号 $(a',d)$。在处理的时候，按能取的 $a$ 值按从小到大顺序枚举，记录一个 $t$ 存 $f_{a,d}$ 的最大值，用来判连通，若是则合并相邻两个下标即可。

若复杂度不考虑反阿克曼函数，第一种暴力，单次修改复杂度 $\Theta(\frac{n}{d})$；第二种暴力，对单个组处理的复杂度 $\Theta(\frac{n}{d})$。但对于同一个 $d$，其不同的 $a'$ 构成不同的组的并集大小为 $n$，且无交集，所以对单个 $d$ 处理的复杂度是 $\Theta(n)$。

考虑设一个阈值 $V$。不难发现，第一种暴力 $d$ 越大越快；第二种暴力 $d$ 范围越小，需要处理的不同 $d$ 越少，也就越快。所以考虑当 $d>V$ 时，使用第一种暴力，否则使用第二种。这样复杂度为 $\Theta(m\cdot\frac{n}{V}+Vn)$。若假定 $n,m$ 同阶，则最优的 $V$ 应取 $\sqrt n$，这样总复杂度为 $\Theta(n\sqrt n)$。

```cpp
int V=sqrt(n);
for (int i=1;i<=V;i++)
	for (int j=1;j<=n;j++)
		f[i][j]=0;
for (int i=1;i<=n;i++)
	fa[i]=i;
for (int i=1;i<=m;i++){
	int a=read(),b=read(),k=read();
	if (b>V)
		for (int j=1;j<=k;j++)
			merge(a+b*j-b,a+b*j);
	else f[b][a]=max(f[b][a],a+b*k);
}
for (int i=1;i<=V;i++){
	for (int j=1;j<=i;j++){
		int t=0;
		for (int x=j;x<=n;x+=i){
			if (t>=x) merge(x-i,x);
			t=max(t,f[i][x]);
		}
	}
}
int c=0;
for (int i=1;i<=n;i++)
	if (find(i)==i) c++;
printf("%d\n",c);
```

本题的 $d\leq10$，故使用第二种暴力处理十种 $d$ 即可，复杂度 $\Theta(n)$，枚举 $d$ 同时具有 $10$ 倍常数。

---

## 作者：z_yq (赞：2)

# 关于题面
这里不多解释了，主要觉得要评价蓝，绿色还是简单了。
# 做法
想必看完题目之后，对这道题目会有一些感悟，我们会想到，如果每一次询问都暴力去连边肯定超时，观察到 $d_i \le 10$，这个特殊的点，可以想到：我们到了最后最多也只会连接 $10 \times n$ 个边，所以如何进行一个预处理，目的是用很短的时间计算出来每个点都要像前面连着那些边，于是我们先忽略 $k_i$ 的存在，易得一个 $dp_{i,j}$ 表示 $i$ 这个点是否要向 $dp_{i,i+j}$ 连边，同理，当我们加上了 $k_i$ 的限制，我们可以直接把这个值压到 $dp_{i,j}$ 里面，表示还要往后连接多少次 $(i,i+j)$，于是你便做出来了这道题目。
# 写在后面
故意不放代码，很好实现，很好调试，做起来不难，所以不放代码，但是要注意越界。

---

## 作者：Wei_Han (赞：1)

发现 $d_i \leq 10$，从这里入手。

直接暴力并查集合并显然是冗余的，因为很多点会被重复合并。考虑枚举 $d_i$ 的值 $D$，一个 $i$ 只考虑它与 $i-D$ 的关系，发现当前面有 $a_j + k_j \times D \ge i$ 的时候才会使得这两点在同一集合，不考虑 $k_j$ 的限制，只要 $a_j \equiv i \pmod D$，$i$ 和 $a_j$ 就一定在同一集合，加上 $k_j$ 的限制，我们顺序记录模 $D$ 后每个值最右端点的位置，只要当前 $i \bmod D$ 最靠右位置在 $i$ 之后，那么 $i$ 就跟 $i - D$ 有连边，这样就会使得每个点向前连边次数不会超过 $\max d_i$，可以通过。

复杂度 $O(n \times \max d_i)$。

[submission](https://codeforces.com/contest/2020/submission/284183605)

---

