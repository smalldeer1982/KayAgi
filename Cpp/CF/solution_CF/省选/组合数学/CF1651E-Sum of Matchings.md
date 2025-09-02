# Sum of Matchings

## 题目描述

Let's denote the size of the maximum matching in a graph $ G $ as $ \mathit{MM}(G) $ .

You are given a bipartite graph. The vertices of the first part are numbered from $ 1 $ to $ n $ , the vertices of the second part are numbered from $ n+1 $ to $ 2n $ . Each vertex's degree is $ 2 $ .

For a tuple of four integers $ (l, r, L, R) $ , where $ 1 \le l \le r \le n $ and $ n+1 \le L \le R \le 2n $ , let's define $ G'(l, r, L, R) $ as the graph which consists of all vertices of the given graph that are included in the segment $ [l, r] $ or in the segment $ [L, R] $ , and all edges of the given graph such that each of their endpoints belongs to one of these segments. In other words, to obtain $ G'(l, r, L, R) $ from the original graph, you have to remove all vertices $ i $ such that $ i \notin [l, r] $ and $ i \notin [L, R] $ , and all edges incident to these vertices.

Calculate the sum of $ \mathit{MM}(G(l, r, L, R)) $ over all tuples of integers $ (l, r, L, R) $ having $ 1 \le l \le r \le n $ and $ n+1 \le L \le R \le 2n $ .

## 样例 #1

### 输入

```
5
4 6
4 9
2 6
3 9
1 8
5 10
2 7
3 7
1 10
5 8```

### 输出

```
314```

# 题解

## 作者：lingfunny (赞：4)

## Solution

计算匹配的点数显然比计算匹配的边数更为简单。

考虑计算每个子图 $G'(l,r,L,R)$ 中匹配的点数的和，除以 $2$ 即为答案。

对于本题，计算没匹配的点数显然比计算匹配的点数简单。

对于一张子图 $G'(l,r,L,R)$，根据每个点度数小于等于 $2$ 的条件，可以得出子图一定是由若干个偶数环和若干条路径组成的。

其中，未匹配的点一定只在奇数路径上，且每条路上只有一个无法匹配。

问题就在于如何计算每个子图 $G'(l,r,L,R)$ 的奇数路径条数总和。

考虑枚举一个奇数路径并判断它会在几张子图中出现。

奇数路径显然可以由唯一一个二元组 $(u, k)$ 确定。其中 $u$ 是这个路径的中点， $2k+1$ 是这条路径的长度。

于是考虑枚举 $(u,k)$ 并进行判断。

当一个路径 $(u,k)$ 合法，需要满足两个条件：

1. 到 $u$ 距离小于等于 $k$ 的节点编号都要在区间 $[l, r]$ 或 $[L,R]$ 内；
2. 到 $u$ 距离为 $k+1$ 的节点不能在 $[l,r]$ 或 $[L,R]$ 内。

维护节点编号在区间 $[l,r]$ 内和 $[L,R]$ 内的最小值和最大值，得到这些信息后显然可以 $\mathcal O(1)$ 求解方案数。

所以可以得到一个清晰的流程：

1. 找到原图上的一个偶数环，记环长为 $s$；
2. 对于环上每个点 $u$，对 $k$ 从 $0$ 到 $\frac{s}{2}$ 枚举，计算答案。

初始时总点数应该是子图数量乘上 $2n$（假设每个点在每张子图都被匹配；对于实际上根本就不在子图中的点，最后扣掉它不被选中的方案数时就包含了这个可能）。

总时间复杂度 $\mathcal O(n^2)$。

## Code

```cpp
// Problem: E. Sum of Matchings
// From: Codeforces - Educational Codeforces Round 124 (Rated for Div. 2)
// URL: https://codeforces.com/contest/1651/problem/E
// Time: 2022-03-14 18:02
// Author: lingfunny

#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int mxn = 3005;

int n, m, vis[mxn], circle[mxn], len;
LL tot;
vector <int> G[mxn];
inline void upd(int v, int& i, int& x) { i = min(i, v); x = max(x, v); }
inline LL S(int x) { if(x<=0) return 0; return (LL)x*(x+1)>>1; }
inline LL calc(int lr, int rl, vector <int> blks) {
	// blk: 不能选的点
	if(lr > rl) {
		int mn = *min_element(blks.begin(), blks.end()),
		mx = *max_element(blks.begin(), blks.end());
		if(mn > n) mn -= n, mx -= n;
		return S(mn-1) + S(n-mx) + S(mx-mn-1);
	}
	int ll = 1, rr = n;
	for(int c: blks) {
		if(c > n) c -= n;
		if(lr <= c && c <= rl) return 0;
		else if(c < lr) ll = max(ll, c+1);
		else if(c > rl) rr = min(rr, c-1);
	}
	return (LL)(lr-ll+1) * (rr-rl+1);
}
void dfs(int u) { circle[++len] = vis[u] = u; for(int v: G[u]) if(!vis[v]) dfs(v); }
inline int Q(int pos) {
	if(pos > len) pos -= len;
	if(pos < 1) pos += len;
	return circle[pos];
}
void solve() {
	int K = len >> 1;
	for(int i = 1, u; u = circle[i], i <= len; ++i) {
		int minl = n, maxl = 0, minr = n, maxr = 0;
		if(u <= n) maxl = minl = u; else minr = maxr = u - n;
		for(int k = 1, l, r; k <= K; ++k) {		// k 实指 k+1
			l = i + k, r = i - k;
			vector <int> blks = {Q(l), Q(r)};
			LL res;
			if(blks[0] > n) res = calc(minl, maxl, {}) * calc(minr, maxr, blks);
			else res = calc(minl, maxl, blks) * calc(minr, maxr, {});
			tot += res;
			for(int v: blks) if(v > n) minr = min(minr, v-n), maxr = max(maxr, v-n);
			else minl = min(minl, v), maxl = max(maxl, v);
		}
	}
}

signed main() {
	scanf("%d", &n); m = n << 1;
	for(int i = 1, u, v; i <= m; ++i) {
		scanf("%d%d", &u, &v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	for(int u = 1; u <= n; ++u) if(!vis[u]) { len = 0; dfs(u); solve(); }
	for(int u = 1; u <= n; ++u) tot += S(n) * (S(u-1) + S(n-u)) << 1;		// 根本不选 u；这边只枚举了 1~n，所以乘 2
	LL res = S(n)*S(n)*(n<<1);
	printf("%lld\n", (res-tot)>>1);
	return 0;
}
```



---

## 作者：Sol1 (赞：3)

很不错的一个题。

首先考虑我们从两侧各截出一个区间之后得到的图是什么样子。忽略掉二分图，原来的图是一堆不相交的环。然后截出来之后自然就是一堆不相交的环和被拦腰截断的环（也就是链）。

然后我们考虑匹配。既然原来是个二分图，那么截出来还是环的环肯定长度都是偶数，匹配数量就是一侧的点数。关键在于链。经过一些观察容易发现匹配数是 链上的点数除以 $2$ 下取整。

那么整个图的匹配数就是 点数 减去 有奇数个点的链的个数 除以 $2$。

现在我们用这个来计算贡献。前半部分，即所有截出来的子图的点数的和是好算的，考虑后半部分。这里我们注意到整个图只有 $3000$ 个点，因此我们可以直接把所有有奇数个点的链全都 DFS 枚举出来，然后考虑有多少个区间对使得这个区间对截出的子图包含这个链，且这个链在子图中是一个独立的连通块。限制就是要包含这个链上所有的点，且不包含与这条链直接相连的点。这个直接维护出链上两侧分别的 max/min 然后分类讨论一手就可以算了。

那么这样这题就做完了，复杂度 $O(n^2)$。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 3005;
struct Edge {
	int to, nxt;
	Edge() {
		nxt = -1;
	}
};
int n, hd[N], pnt;
Edge e[N << 1];
long long ans;

inline void AddEdge(int u, int v) {
	e[++pnt].to = v;
	e[pnt].nxt = hd[u];
	hd[u] = pnt;
}

inline void Read() {
	cin >> n;
	for (int i = 1;i <= 2 * n;i++) {
		int u, v; cin >> u >> v;
		AddEdge(u, v);
		AddEdge(v, u);
	}
}

inline long long Totcnt(int n) {
	return 1ll * n * (n + 1) / 2;
}

inline void Dfs1(int u, int fa, int dep, int lmn, int lmx, int rmn, int rmx, int le1) {
	if (u <= n) {
		for (int i = hd[u];~i;i = e[i].nxt) {
			if (e[i].to != fa) Dfs1(e[i].to, u, dep + 1, lmn, lmx, min(rmn, e[i].to), max(rmx, e[i].to), le1);
		}
	} else {
		for (int i = hd[u];~i;i = e[i].nxt) {
			if (e[i].to != fa) {
				int le2 = e[i].to;
				int ncl = min(le1, le2), ncr = max(le1, le2);
				long long curans = ans;
				long long rfc = 1ll * (rmn - n) * (2 * n - rmx + 1);
				if (dep == 1) ans -= (Totcnt(ncr - ncl - 1) + Totcnt(n - ncr) + Totcnt(ncl - 1)) * rfc;
				else {
					if (ncl > lmx) ans -= 1ll * lmn * max(ncl - lmx, 0) * rfc;
					else if (ncr < lmn) ans -= 1ll * max(lmn - ncr, 0) * (n - lmx + 1) * rfc;
					else ans -= 1ll * max(lmn - ncl, 0) * max(ncr - lmx, 0) * rfc;
				}
				if (e[i].to != le1) Dfs1(e[i].to, u, dep + 1, min(lmn, e[i].to), max(lmx, e[i].to), rmn, rmx, le1);
			}
		}
	}
}

inline void Dfs2(int u, int fa, int dep, int lmn, int lmx, int rmn, int rmx, int le1) {
	if (u > n) {
		for (int i = hd[u];~i;i = e[i].nxt) {
			if (e[i].to != fa) Dfs2(e[i].to, u, dep + 1, lmn, lmx, min(rmn, e[i].to), max(rmx, e[i].to), le1);
		}
	} else {
		for (int i = hd[u];~i;i = e[i].nxt) {
			if (e[i].to != fa) {
				int le2 = e[i].to;
				int ncl = min(le1, le2), ncr = max(le1, le2);
				long long rfc = 1ll * rmn * (n - rmx + 1);
				if (dep == 1) ans -= (Totcnt(ncr - ncl - 1) + Totcnt(2 * n - ncr) + Totcnt(ncl - n - 1)) * rfc;
				else {
					if (ncl > lmx) ans -= 1ll * (lmn - n) * max(ncl - lmx, 0) * rfc;
					else if (ncr < lmn) ans -= 1ll * max(lmn - ncr, 0) * (2 * n - lmx + 1) * rfc;
					else ans -= 1ll * max(lmn - ncl, 0) * max(ncr - lmx, 0) * rfc;
				}
				if (e[i].to != le1) Dfs2(e[i].to, u, dep + 1, min(lmn, e[i].to), max(lmx, e[i].to), rmn, rmx, le1);
			}
		}
	}
}

inline void Solve() {
	for (int i = 1;i <= n;i++) {
		for (int j = hd[i];~j;j = e[j].nxt) Dfs2(i, e[j].to, 1, 0x3f3f3f3f, 0xf3f3f3f3, i, i, e[j].to);
	}
	for (int i = n + 1;i <= 2 * n;i++) {
		for (int j = hd[i];~j;j = e[j].nxt) Dfs1(i, e[j].to, 1, 0x3f3f3f3f, 0xf3f3f3f3, i, i, e[j].to);
	}
	ans /= 2;
	for (int i = 1;i <= n;i++) {
		for (int j = i;j <= n;j++) ans += 1ll * n * (n + 1) * (j - i + 1);
	}
	cout << ans / 2 << endl;
}

int main() {
	memset(hd, -1, sizeof(hd));
	Read();
	Solve();
	return 0;
}
```

~~代码刚好 100 行！~~

---

## 作者：Renshey (赞：3)

记 $g(l,r,L,R)=MM(G(l,r,L,R))$，设 $f(l,r)=\sum_{n+1\le L\le R\le 2n} g(l,r,L,R)$。

考虑对于 $\forall 1\le l \le r\le n$，计算 $f(l,r)$ 的和。

考虑增量法。注意到 $g(l,r,L,R)-g(l,r-1,L,R)\in\{0,1\}$，因此可以考虑由 $f(l,r-1)$ 得到 $f(l,r)$。

对于 $g(l,r,L,R)-g(l,r-1,L,R)=1$ 的情况，首先 $r$ 一定要被匹配到，否则答案不会增大。题目中每个点的度数为 $2$ 保证了图由若干个偶环构成，且每个偶环由 $[1,n]$ 与 $[n+1,2n]$ 中的数交替构成。因此直接考虑 $r$ 所在的环，记 $r$ 所在的环按环上的顺序分别为 $a_1,a_2,\dots,a_{2m}$，且 $a_1=r$。

假设 $g(l,r-1,L,R)$ 中前若干个连续的匹配为 $(a_2,a_3),(a_4,a_5),\dots,(a_{2k},a_{2k+1})$，则 $a_1$ 与 $a_2$ 匹配后能改变最大匹配当且仅当 $a_{2k+2}\in [L,R]$，同时由于 $a_{2k+2}$ 不能与 $a_{2k+3}$ 匹配，则 $a_{2k+3}\notin [l,r]$。那么这样的 $k$ 对于确定的 $l,r$ 来说是唯一的，所以通过限制 $a_2,a_4,\dots,a_{2k+2}\in [L,R]$，则符合要求的 $[L,R]$ 的对数可以直接计算得出。对于 $a_1$ 与 $a_{2m}$ 匹配的情况是类似的。将两种方案合并在一起，即可计算出满足 $g(l,r,L,R)-g(l,r-1,L,R)=1$ 的 $(L,R)$ 的对数。对于 $a_1,a_3,\dots,a_{2m-1}$ 全部在 $[l,r]$ 内的情况可以单独讨论。

枚举 $l,r$ 后直接暴力找到 $r$ 所在环上的分界点，即可做到效率 $O(n^3)$，由于 $(l,r)$ 的对数有限，且环上分界点对于 $(l,r)$ 不同的情况也互不相同，因此实际计算的次数远低于 $n^3$，在极限数据下也能通过。如果采用倍增/数据结构优化找到分界点与求最值的过程可以做到 $O(n^2\log n)$。

代码：
```cpp
#include<bits/stdc++.h>
int n,tot,id[3010],id0[3010],id1[3010],cir[3010][6010];
int cnt[3010],min[3010][2],max[3010][2];
std::vector<int> e[3010]; long long ans[3010][3010],Ans;
inline void dfs ( int u )
{
	id[u]=tot; cir[tot][++cnt[tot]]=u;
	if ( !id[e[u][0]] ) dfs(e[u][0]);
	if ( !id[e[u][1]] ) dfs(e[u][1]);
}
signed main()
{
	scanf("%d",&n);
	for ( int i=1,u,v;i<=2*n;i++ ) scanf("%d%d",&u,&v),e[u].push_back(v),e[v].push_back(u);
	for ( int i=1;i<=n;i++ ) if ( !id[i] )
	{
		++tot; dfs(i); min[tot][0]=max[tot][0]=cir[tot][1]; min[tot][1]=max[tot][1]=cir[tot][2];
		for ( int j=3;j<=cnt[tot];j+=2 ) min[tot][0]=std::min(min[tot][0],cir[tot][j]),max[tot][0]=std::max(max[tot][0],cir[tot][j]);
		for ( int j=4;j<=cnt[tot];j+=2 ) min[tot][1]=std::min(min[tot][1],cir[tot][j]),max[tot][1]=std::max(max[tot][1],cir[tot][j]);
		min[tot][1]-=n; max[tot][1]-=n;
		for ( int j=1;j<=cnt[tot];j++ ) cir[tot][j+cnt[tot]]=cir[tot][j],id0[cir[tot][j]]=j,id1[cir[tot][j]]=j+cnt[tot];
	}
	for ( int l=1;l<=n;l++ )
	{
		for ( int r=l;r<=n;r++ )
		{
			int i=id[r];
			if ( l<=min[i][0] and max[i][0]<=r ) ans[l][r]=ans[l][r-1]+min[i][1]*(n-max[i][1]+1);
			else
			{
				int endpos1=0,endpos2=0;
				int l1=n+1,r1=0,l2=n+1,r2=0;
				for ( int p=id0[r];;p+=2 ) if ( cir[i][p]<l or cir[i][p]>r ) { endpos1=p; break; }
				for ( int p=id1[r];;p-=2 ) if ( cir[i][p]<l or cir[i][p]>r ) { endpos2=p; break; }
				for ( int p=id0[r]+1;p<endpos1;p+=2 ) l1=std::min(l1,cir[i][p]-n),r1=std::max(r1,cir[i][p]-n);
				for ( int p=id1[r]-1;p>endpos2;p-=2 ) l2=std::min(l2,cir[i][p]-n),r2=std::max(r2,cir[i][p]-n);
				ans[l][r]=ans[l][r-1]+l1*(n-r1+1)+l2*(n-r2+1)-std::min(l1,l2)*(n-std::max(r1,r2)+1);
			}
		}
		for ( int r=l;r<=n;r++ ) Ans+=ans[l][r];
	}
	return !printf("%lld\n",Ans);
```
}

---

## 作者：daniEl_lElE (赞：1)

题目条件等价于原图由若干个环组成。

考虑计算对于一个环（视作循环排列） $x_1,x_2,\dots,x_{2t}$，包含了 $x_i,x_{i+1},\dots,x_j$ 且不包含 $x_{i-1}$ 和 $x_{j+1}$ 的方案数，不难发现其对最大匹配的贡献为 $\lfloor\frac{j-i+1}{2}\rfloor$（若 $j<i$ 那么就是 $\lfloor\frac{2t-(j-i+1)}{2}\rfloor$）。

容易计算出选择 $x_i,x_{i+1},\dots,x_j$ 时上面一排与下面一排点至少要到左边右边哪个位置。使用 $x_{i-1}$ 和 $x_{j+1}$ 的条件判断至多到左边右边哪个位置。

特判整个环都包含的情况。

总复杂度 $O(n^2)$。

```cpp
#include <bits/stdc++.h>
#define int long long
#define double long double
#define lowbit(i) (i&(-i))
using namespace std;
int vis[3005];
vector<int> vc[3005];
int nxt[3005],lst[3005],ans;
signed main(){
	int n; cin>>n;
	for(int i=1;i<=2*n;i++){
		int u,v; cin>>u>>v;
		vc[u].push_back(v);
		vc[v].push_back(u);
	}
	for(int i=1;i<=2*n;i++){
		if(!vis[i]){
			int now=i,ok;
			vector<int> tmp;
			do{
				ok=0;
				vis[now]=1;
				tmp.push_back(now);
				for(auto v:vc[now]){
					if(!vis[v]){
						ok=1;
						now=v;
					}
				}
			}while(ok);
			for(int j=0;j<tmp.size();j++) nxt[tmp[j]]=tmp[(j+1)%tmp.size()];
			for(int j=0;j<tmp.size();j++) lst[tmp[j]]=tmp[(j+tmp.size()-1)%tmp.size()];
//			for(auto v:tmp) cout<<v<<" "; cout<<"\n";
			for(int j=0;j<tmp.size();j++){
				int now=tmp[j],minl=n+1,maxl=0,minr=n+1,maxr=0,o=now;
				if(now<=n) minl=min(minl,now),maxl=max(maxl,now);
				else minr=min(minr,now-n),maxr=max(maxr,now-n);
				for(int k=2;k<tmp.size();k++){
					now=nxt[now];
					if(now<=n) minl=min(minl,now),maxl=max(maxl,now);
					else minr=min(minr,now-n),maxr=max(maxr,now-n);
//					cout<<minl<<" "<<maxl<<" "<<minr<<" "<<maxr<<" "<<now<<"\n";
					int posx1,posy1;
					int posx2,posy2;
					if(lst[o]<=n) posx1=1,posy1=lst[o];
					else posx1=2,posy1=lst[o]-n;
					if(nxt[now]<=n) posx2=1,posy2=nxt[now];
					else posx2=2,posy2=nxt[now]-n;
					int lsiz1=minl,rsiz1=n-maxl+1,lsiz2=minr,rsiz2=n-maxr+1;
//					cout<<lsiz1<<" "<<rsiz1<<" "<<lsiz2<<" "<<rsiz2<<"\n";
					{
						if(posx1==1){
							if(minl<=posy1&&posy1<=maxl) continue;
							if(posy1<minl) lsiz1=min(lsiz1,minl-posy1);
							if(posy1>maxl) rsiz1=min(rsiz1,posy1-maxl);
						}
						else{
							if(minr<=posy1&&posy1<=maxr) continue;
							if(posy1<minr) lsiz2=min(lsiz2,minr-posy1);
							if(posy1>maxr) rsiz2=min(rsiz2,posy1-maxr);
						}
					}
					{
						if(posx2==1){
							if(minl<=posy2&&posy2<=maxl) continue;
							if(posy2<minl) lsiz1=min(lsiz1,minl-posy2);
							if(posy2>maxl) rsiz1=min(rsiz1,posy2-maxl);
						}
						else{
							if(minr<=posy2&&posy2<=maxr) continue;
							if(posy2<minr) lsiz2=min(lsiz2,minr-posy2);
							if(posy2>maxr) rsiz2=min(rsiz2,posy2-maxr);
						}
					}
//					cout<<lsiz1<<" "<<rsiz1<<" "<<lsiz2<<" "<<rsiz2<<" ";
//					cout<<lsiz1*rsiz1*lsiz2*rsiz2*(k/2)<<"\n";
					ans+=lsiz1*rsiz1*lsiz2*rsiz2*(k/2); 
//					cout<<ans<<"\n";
				}
				if(j==0){
					now=nxt[now];
					if(now<=n) minl=min(minl,now),maxl=max(maxl,now);
					else minr=min(minr,now-n),maxr=max(maxr,now-n);
					int lsiz1=minl,rsiz1=n-maxl+1,lsiz2=minr,rsiz2=n-maxr+1;
					ans+=lsiz1*rsiz1*lsiz2*rsiz2*(tmp.size()/2);
				}
			}
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：zhanghengrui (赞：1)

显然原图可以分成若干个点数为偶数的环。

先来考虑怎么算原图的任意一个子图的最大匹配：显然这个子图一定可以分成若干个长度为偶数的环和若干条链，对最大匹配的贡献都是长度除以 $2$（下取整）。

所以可以枚举原图的每一条链和每一个环，计算其在多少个子图中会有直接贡献（不被包含在其他环或链中），乘上自身贡献加到答案里。计算的时候，可以分别记录环 / 链上 $[1, n]$ 和 $[n+1, 2n]$ 两部分的最大和最小值，得出 $l, r, L, R$ 的上下界；对于链还要处理与两个端点相连且不在链上的两个点，要求子图不能包含这两个点。实现细节见代码。

时间复杂度 $O(n^2)$。

---

```cpp
#ifdef ONLINE_JUDGE
#define NDEBUG
#endif

#include <cassert>

#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

bool inRange(int l, int r, int x) {
  assert(l <= r);
  return x >= l && x <= r;
}

// 从 [l0, r0] 中选（下同）
// 包含 [l, r]
long countRanges(int l, int r, int l0, int r0) {
  assert(l >= l0 && r <= r0 && l <= r);
  return (l - l0 + 1L) * (r0 - r + 1);
}

// 包含 [l, r]，不包含 x
long countRanges(int l, int r, int l0, int r0, int x) {
  assert(l >= l0 && r <= r0 && l <= r);
  if (!inRange(l0, l, x) && !inRange(r, r0, x))
    return (l - l0 + 1L) * (r0 - r + 1);
  return inRange(l0, l, x) ? (l - x) * (r0 - r + 1L) : (l - l0 + 1L) * (x - r);
}

// 包含 [l, r]，不包含 x, y
long countRanges(int l, int r, int l0, int r0, int x, int y) {
  assert(l >= l0 && r <= r0 && l <= r);
  if (!inRange(l0, l, x) && !inRange(r, r0, x))
    return countRanges(l, r, l0, r0, y);
  if (!inRange(l0, l, y) && !inRange(r, r0, y))
    return countRanges(l, r, l0, r0, x);
  if (inRange(l0, l, x) && inRange(l0, l, y))
    return countRanges(l, r, l0, r0, std::max(x, y));
  if (inRange(r, r0, x) && inRange(r, r0, y))
    return countRanges(l, r, l0, r0, std::min(x, y));
  if (inRange(r, r0, x))
    std::swap(x, y);
  assert(inRange(l0, l, x) && inRange(r, r0, y));
  return static_cast<long>(l - x) * (y - r);
}

// 对于一个环，计算本身及环上的所有链的贡献
long long calc(const std::vector<int> &nodes, int n) {
  const int m = nodes.size();
  assert(m % 2 == 0);
  long long sum = 0;
  for (int i = 0; i < m; ++i) {
    int s[4]{n - 1, 0, 2 * n - 1, n};
    for (int j = i, cnt = 1; (j + 1) % m != i; j = (j + 1) % m, ++cnt) {
      if (nodes[j] < n) {
        if (nodes[j] < s[0])
          s[0] = nodes[j];
        if (nodes[j] > s[1])
          s[1] = nodes[j];
      } else {
        if (nodes[j] < s[2])
          s[2] = nodes[j];
        if (nodes[j] > s[3])
          s[3] = nodes[j];
      }
      if (cnt == 1)
        continue;
      const int u = nodes[(i + m - 1) % m], v = nodes[(j + 1) % m];
      if (inRange(s[0], s[1], u) || inRange(s[2], s[3], u) ||
          inRange(s[0], s[1], v) || inRange(s[2], s[3], v))
        continue;
      const auto c0 = cnt / 2LL;
      const auto c1 = countRanges(s[0], s[1], 0, n - 1, u, v),
                 c2 = countRanges(s[2], s[3], n, n * 2 - 1, u, v);
      sum += c0 * c1 * c2;
    }
  }
  int s[4]{n - 1, 0, 2 * n - 1, n};
  for (int i = 0; i < m; ++i) {
    if (nodes[i] < n) {
      if (nodes[i] < s[0])
        s[0] = nodes[i];
      if (nodes[i] > s[1])
        s[1] = nodes[i];
    } else {
      if (nodes[i] < s[2])
        s[2] = nodes[i];
      if (nodes[i] > s[3])
        s[3] = nodes[i];
    }
  }
  return sum + m / 2LL * countRanges(s[0], s[1], 0, n - 1) *
                   countRanges(s[2], s[3], n, n * 2 - 1);
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n;
  std::cin >> n;
  std::vector<std::vector<int>> edges(n * 2);
  for (int i = 0; i < n * 2; ++i) {
    int x, y;
    std::cin >> x >> y;
    --x;
    --y;
    edges[x].push_back(y);
    edges[y].push_back(x);
  }
  std::vector<bool> vis(n * 2, false);
  long long answer = 0;
  for (int i = 0; i < n * 2; ++i) {
    if (vis[i])
      continue;
    std::vector<int> v{i, edges[i][0]};
    while (v.back() != i) {
      vis[v.back()] = true;
      v.push_back(edges[v.back()][*(v.end() - 2) == edges[v.back()][0]]);
    }
    v.pop_back();
    answer += calc(v, n);
  }
  std::cout << answer << '\n';
  return 0;
}
```

---

## 作者：piggy123 (赞：0)

考虑 Hall 定理推论，最大匹配为 $|V_L|-\max\limits_{S\subset V_L}(|S|-|\cup_{u\in S}N(S)|)$，其中 $N(u)$ 表示 $u$ 的邻域。对于这题来说，我们可以把所有 $|V_L|$ 先累计上去，所以我们只需要计算 $\max\limits_{S\subset V_L}(|S|-|\cup_{u\in S}N(S)|)$ 的和。

容易发现题目中的条件等价于图仅包含偶环，那么删除某些点之后就剩下若干条链和环。容易发现环的贡献为 $0$（归纳证明），偶数长度链的贡献为 $0$（归纳证明），奇数长度链的贡献为 $1$（隔一个选一个，归纳可证明上界为 $1$）。

所以我们只需要计算所有奇数长度链的贡献，我们搜出所有奇数长度链，则会有若干 $[l,r],[L,R]$ 包含或不包含某些数的限制，分类讨论即可做到 $\Theta(n^2)$。

代码非常多细节，如果你想写这道题我建议你换一道题。

```cpp
#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
using namespace std;
vector<ll> vct[3005];
ll to2[3005],ans,n,vis[3005];

void dfs(ll pos,ll len,ll lb1,ll rb1,ll lb2,ll rb2,ll st,ll st2) {
	vis[pos]=1;
	ll tt=0;
	for(ll i:vct[pos]) {
		if (!vis[i]) {
			if (i>n)tt=i-n;
			else tt=i;
			if (i<=n) {
				dfs(i,len+1,min(lb1,i),max(rb1,i),lb2,rb2,st,st2);
			}
			else
				dfs(i,len+1,lb1,rb1,min(lb2,i-n),max(i-n,rb2),st,st2);
		}
	}
	if (len&1) {
		if (!tt)tt=st2;
		if(len==1)return;
		if (max(tt,st2)<lb2) {
			ans-=lb1*max(0ll,n-rb1+1)*(lb2-max(tt,st2))*(n-rb2+1);
		} else if (min(tt,st2)>rb2) {
			ans-=lb1*max(0ll,n-rb1+1)*(min(tt,st2)-rb2)*lb2;
		} else if (min(tt,st2)<lb2&&max(tt,st2)>rb2) {
			ans-=lb1*max(0ll,n-rb1+1)*(max(tt,st2)-rb2)*(lb2-min(tt,st2));
		}
	}
}

int main() {
	cin >> n;
	for (ll i=1; i<=2*n; i++) {
		ll u,v;
		cin >> u >> v;
		vct[u].push_back(v);
		vct[v].push_back(u);
		if (u>v)swap(u,v);
		to2[v]^=u;
	}

	for (ll i=1; i<=n; i++) {
		ll p1=vct[i][0],p2=vct[i][1];
		for (ll j=1; j<=2*n; j++)vis[j]=0;
		vis[p1]=1;
		dfs(i,1,i,i,n,1,i,p1-n);
		vis[p1]=0;
		for (ll j=1; j<=2*n; j++)vis[j]=0;
		vis[p2]=1;
		dfs(i,1,i,i,n,1,i,p2-n);
		vis[p2]=0;
	}
	ans/=2;
	for (ll i=1; i<=n; i++) {
		ll p1=vct[i][0],p2=vct[i][1];
		if (p1>p2)swap(p1,p2);
		p1-=n,p2-=n;
		ans-=i*(n-i+1)*(p1*(p1-1)/2+(p2-p1)*(p2-p1-1)/2+(n-p2)*(n-p2+1)/2);
	}
	for (ll i=1; i<=n; i++)ans+=i*(n-i+1)*(n*(n+1)/2);
	cout<< ans;
	return 0;
}

```


---

## 作者：wcyQwQ (赞：0)

感觉大家的数数方式都和我不一样。

每个点度数为 $2$，说明整个图是由若干个偶环组成的，我们考虑从其中取两个区间，剩下来的图显然是若干个环和若干条链，所以我们对每个环和链统计贡献即可。

首先是环，我们记一个环长为 $len$ 上左部点编号最大值，最小值为 $lmax$，$lmin$，右部点编号最大值，最小值为 $rmax$，$rmin$，显而易见，这个环对答案的贡献为 $lmin(n - lmax + 1)rmin(n - rmax + 1)\dfrac{len}{2}$。

其次是链，我们枚举所有的链，共 $O(n^2)$ 条，然后同上记下链上的这四个信息，但是这条链对答案能造成贡献，还要考虑这条链左右两侧的点会不会被选中，再记录一下链外两点的信息即可。

时间复杂度 $O(n^2)$。[Code](https://codeforces.com/contest/1651/submission/214613612)



---

