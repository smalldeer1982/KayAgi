# Acyclic Organic Compounds

## 题目描述

You are given a tree $ T $ with $ n $ vertices (numbered $ 1 $ through $ n $ ) and a letter in each vertex. The tree is rooted at vertex $ 1 $ .

Let's look at the subtree $ T_{v} $ of some vertex $ v $ . It is possible to read a string along each simple path starting at $ v $ and ending at some vertex in $ T_{v} $ (possibly $ v $ itself). Let's denote the number of distinct strings which can be read this way as ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF601D/a0c9096effba09473c4b51e3186b592318344485.png).

Also, there's a number $ c_{v} $ assigned to each vertex $ v $ . We are interested in vertices with the maximum value of ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF601D/c561564d7b2aed4877e755dc8d366f0ff87cf302.png).

You should compute two statistics: the maximum value of ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF601D/c561564d7b2aed4877e755dc8d366f0ff87cf302.png) and the number of vertices $ v $ with the maximum ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF601D/c561564d7b2aed4877e755dc8d366f0ff87cf302.png).

## 说明/提示

In the first sample, the tree looks like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF601D/9244e4a8ade3af9b76853a18eae8ae654a6d5be1.png)The sets of strings that can be read from individual vertices are:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF601D/b0a25806e20ff995abfb34a167834abd113ae6f1.png)Finally, the values of ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF601D/c561564d7b2aed4877e755dc8d366f0ff87cf302.png) are:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF601D/6c3fc4aa4c72ec4c2646ac39d7110bd6544e120f.png)In the second sample, the values of ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF601D/4c35255ca2e85f9a2c304b6b5d98f8aa96f62b0c.png) are $ (5,4,2,1,1,1) $ . The distinct strings read in $ T_{2} $ are ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF601D/6427dc79a89c97e7e81a3e52fb54938acda3e0b8.png); note that ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF601D/ff39f896bb407bf8e8d94b0a5b47a67e60c595d8.png) can be read down to vertices $ 3 $ or $ 4 $ .

## 样例 #1

### 输入

```
10
1 2 7 20 20 30 40 50 50 50
cacabbcddd
1 2
6 8
7 2
6 2
5 4
5 9
3 10
2 5
2 3
```

### 输出

```
51
3
```

## 样例 #2

### 输入

```
6
0 2 4 1 1 1
raaaba
1 2
2 3
2 4
2 5
3 6
```

### 输出

```
6
2
```

# 题解

## 作者：dead_X (赞：4)

## 前言
来点阴间 vp 时的神奇做法。
## 思路
首先我们可以尝试通过一些方法枚举所有的子串。

直接存所有子串显然不太行，考虑维护 Hash 值。

由于需要支持插入，全体乘 $base$，全体加一个值，线段树合并显然完全不能维护这种集合，那么 dsu-on-tree 呢？

首先 dsu-on-tree 的一些步骤都是暴力插入和暴力删除，于是问题变成了这个东西：

* 集合
* 支持插入
* 支持全体加
* 支持全体乘
* 支持查询不同的数的个数
* 所有操作在模大质数意义下进行

这个就比较好做了，我们在一个操作的时候不改变集合内的数，而让之后所有的插入操作额外乘上一个系数即可，于是此题在 $O(n\log^2n)$ 的时间复杂度内解决。

特别注意的是，由于子串数量会达到 $10^{12}$ 级别，单模是一定会被卡的，请使用双模或多模 hash。

可能略微卡常，这里使用了火车头在 C++17(64) 下通过。
## 代码
```cpp
// Problem: D. Acyclic Organic Compounds
// Contest: Codeforces Round #333 (Div. 1)
// URL: https://codeforces.com/contest/601/problem/D
// Memory Limit: 512 MB
// Time Limit: 3000 ms
// 
// Powered by CP Editor (https://cpeditor.org)
 
//And in that light,I find deliverance.
#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
using namespace std;
#define int long long
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
const int p1=1019260817,p2=998244353,base=131;
int qp1(int x,int y)
{
	int res=1;
	for(int t=x; y; y>>=1,t=t*t%p1) if(y&1) res=res*t%p1;
	return res;
}
int qp2(int x,int y)
{
	int res=1;
	for(int t=x; y; y>>=1,t=t*t%p2) if(y&1) res=res*t%p2;
	return res;
}
#define mp(x,y) make_pair(x,y)
set<pair<int,int>> ss;
char str[300003];
int mx=-1,cnt=0;
int son[300003],sz[300003];
int a[300003];
vector<int> e[300003];
void dfs(int x,int fa)
{
	sz[x]=1;
	for(int y:e[x]) if(y!=fa)
		dfs(y,x),sz[x]+=sz[y],(sz[y]>sz[son[x]])&&(son[x]=y);
	return ;
}
void add(int x,int fa,int qwq,int awa,int qwq_,int awa_,
int k,int b,int k_,int b_,set<pair<int,int>> &s)
{
	qwq=(qwq+awa*str[x])%p1,awa=awa*131%p1;
	qwq_=(qwq_+awa_*str[x])%p2,awa_=awa_*131%p2;
	s.insert(make_pair((qwq+p1-b)*qp1(k,p1-2)%p1,
	(qwq_+p2-b_)*qp2(k_,p2-2)%p2));
	for(int y:e[x]) if(y!=fa) 
		add(y,x,qwq,awa,qwq_,awa_,k,b,k_,b_,s);
	return ;
}
void solve(int x,int fa,int&k,int&b,int&k_,int&b_,set<pair<int,int>> &s)
{
	set<pair<int,int>> st;
	int tk,tb,tk_,tb_;
	for(int y:e[x]) if(y!=fa&&y!=son[x]) 
	tk=tk_=1,tb=tb_=0,solve(y,x,tk,tb,tk_,tb_,st),st.clear();
	if(son[x]) solve(son[x],x,k,b,k_,b_,s);
	//(kx+b)*131+s[x]
	b=(b*131+str[x])%p1,k=k*131%p1;
	b_=(b_*131+str[x])%p2,k_=k_*131%p2;
	s.insert(make_pair((p1+str[x]-b)*qp1(k,p1-2)%p1,
	(p2+str[x]-b_)*qp2(k_,p2-2)%p2));
	for(int y:e[x]) if(y!=fa&&y!=son[x]) 
	add(y,x,str[x],131,str[x],131,k,b,k_,b_,s);
	a[x]+=(int)s.size();
	if(a[x]>mx) mx=a[x],cnt=1;
	else if(a[x]==mx) ++cnt; 
	return ;
}
signed main()
{
	int n=read();
	for(int i=1; i<=n; ++i) a[i]=read();
	scanf("%s",str+1);
	for(int i=1; i<n; ++i)
	{
		int u=read(),v=read();
		e[u].push_back(v);
		e[v].push_back(u);
	}
	set<pair<int,int>> s;
	int K=1,B=0,KK=1,BB=0;
	dfs(1,1),solve(1,1,K,B,KK,BB,s);
	printf("%lld\n%lld\n",mx,cnt);
	return 0;
}
```

---

## 作者：Diaоsi (赞：3)

[Acyclic Organic Compounds](https://www.luogu.com.cn/problem/CF601D)

首先注意到一个事实，如果把若干个字符串插入 Trie 中，则 Trie 的节点数就表示这些字符串的本质不同前缀数（不包括根）。

本题要统计 $x$ 子树内以 $x$ 为起始的本质不同前缀数，可以在 DFS 的时候把 Trie 建出来。由于第一个字符都一样，可以直接把这个节点作为 Trie 的根。建完 Trie 后，Trie 的节点数（包括根）就是 $\text{dif}(x)$。

如果每一次都清空 Trie，时间复杂度为 $\mathcal{O}(n^2)$，考虑树上启发式合并，也就是 DFS 时保留重儿子对应的 Trie，直接用于计算当前子树的答案，而不是重新扫描重儿子。

时间复杂度为 $\mathcal{O}(n\log n)$。

Code:
```cpp
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const int N=300010,M=3000010,INF=0x3f3f3f3f;
inline int max(int x,int y){return x>y?x:y;}
inline int min(int x,int y){return x<y?x:y;}
inline void swap(int &x,int &y){x^=y^=x^=y;}
int n,rt,tot=1,ans,cnt,c[N],sz[N],son[N],tr[N][27];
char s[N];
vector<int> h[N];
void add(int x,int y){
	h[x].push_back(y);
}
void clr(){
	for(int i=1;i<=tot;i++)
		for(int j=1;j<=26;j++)
			tr[i][j]=0;
	rt=tot=1;
}
void dfs1(int x,int fa){
	sz[x]=1;
	int cnt=0;
	for(int y:h[x]){
		if(y==fa)continue;
		dfs1(y,x);
		sz[x]+=sz[y];
		if(sz[y]>cnt){
			cnt=sz[y];
			son[x]=y;
		}
	}
}
void get(int x,int fa,int son,int p){
	for(int y:h[x]){
		if(y==fa||y==son)continue;
		if(!tr[p][s[y]-'a'+1])tr[p][s[y]-'a'+1]=++tot;
		get(y,x,son,tr[p][s[y]-'a'+1]);
	}
}
void dfs2(int x,int fa,int p){
	for(int y:h[x]){
		if(y==fa)continue;
		if(y!=son[x]){
			dfs2(y,x,rt);
			clr();
		}
	}
	if(son[x]){
		dfs2(son[x],x,rt);
		tr[++tot][s[son[x]]-'a'+1]=rt;rt=tot;
		get(x,fa,son[x],rt);
	}
	if(tot+c[x]>ans)ans=tot+c[x],cnt=1;
	else if(tot+c[x]==ans)++cnt;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&c[i]);
	scanf("%s",s+1);
	for(int i=1;i<n;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y),add(y,x);
	}
	dfs1(1,0);
	dfs2(1,0,rt);
	printf("%d\n%d\n",ans,cnt);
	return 0;
}
```

---

## 作者：lzyqwq (赞：3)

**[cnblogs](https://www.cnblogs.com/MnZnOIerLzy/articles/17810260.html)**

**[洛谷](https://www.luogu.com.cn/problem/CF601D) [CF](https://codeforces.com/problemset/problem/601/D)**

> - 给出一棵 $n$ 个点的有根树，每个点上有一个字符 $s_i$ 和权值 $c_i$。
>
> - 定义 $str(u,v)$ 为 $u$ 到 $v$ 路径上所有点上的字符顺次拼接得到的字符串。
>
> - 定义 $\text{dif}(u)$ 为在 $u$ 子树内任选一个点 $v$，可以得到多少种本质不同的 $str(u,v)$。
>
> - 求 $\max\limits_{i=1}^n (\text{dif}(u)+c_u)$，以及多少个点取到最大值。
>
> - $n\le 3\times 10^5$。

首先本质不同的 $str(u,v)$ 等价于本质不同的 $str(v,u)$。考虑树上启发式合并，用 `std::set` 维护每个子树内有多少种本质不同的哈希值。

但是这题又不太一样，因为每个点继承重儿子时，重儿子内的所有 $str(v,u)$ 都要拼上当前点的字符，因此哈希值需要整体乘 / 加。

考虑维护 $mul,add$ 两个标记，表示 `std::set` 里的元素要乘上 $mul$，再加上 $add$ 才能得到真实值。那么我们 `std::set` 里维护的值，就是与标记运算后能得到真实值的数（称为 $base$）。那么有几种真实值，就是有几种 $base$。遍历轻儿子子树插入 $base$ 就可以得到当前子树的 `std::set`。

由于轻儿子子树内的点是不需要与 $tag$ 运算的，因此它们的 $base$ 就是要“撤销”标记，再与标记运算，相当于不变，即真实值。所以还需要求出 $mul$ 的逆元来撤销。


还要注意标记的合并，比如我先乘 $a$ 加 $b$，再乘 $c$ 加 $d$，那么对于一个数 $x$ 而言，它会变成 $c(ax+b)+d=acx+bc+d$，此时 $mul$ 变成 $ac$，$add$ 变成 $bc+d$。

时间复杂度为 $\mathcal{O}(n\log^2 n)$（应该可以用哈希表做到 $\mathcal{O}(n\log n)$），空间复杂度为 $\mathcal{O}(n)$。注意要写双哈希。

**[提交记录（含代码）](https://codeforces.com/contest/601/submission/231402066)**

---

## 作者：Aaronwrq (赞：2)

这道题其实很简单，感觉很多题解都弄复杂了。

题目要求一个点 $v$ 到其子树内的点 $S_v$ 构成的本质不同字符串数量。可以给每个串的前面都加一段从根到 $v$ 父节点的前缀，不影响答案。此时一个点对应了从根到该点的字符串。

直接用哈希维护每个点对应的串，原问题就转变为子树内颜色数，可以通过 dfs 序变为区间颜色数。直接上树状数组维护即可。

时间复杂度：$O(n\log n)$。

```cpp
#include <bits/stdc++.h>
#define MAXN 300010
using namespace std;

int n;
int c[MAXN];
int dfn[MAXN], siz[MAXN], id[MAXN], tot;
char ch[MAXN];
vector<int> ed[MAXN];
long long has[MAXN][2], hk[2] = {103, 19260817}, hm[2] = {1000000007, 998244353};
long long h[MAXN];
map<long long, int> mp;

struct Question{
	int l, r, pos;
}qry[MAXN];

void dfs(const int p, const int from) {
	dfn[p] = ++tot, id[tot] = p, siz[p] = 1;
	has[p][0] = (has[from][0] * hk[0] + ch[p] - 96) % hm[0];
	has[p][1] = (has[from][1] * hk[1] + ch[p] - 96) % hm[1];
	h[dfn[p]] = (has[p][0] << 32) + has[p][1];
	for (int q : ed[p]) if (q != from) {
		dfs(q, p), siz[p] += siz[q];
	}
	qry[p] = Question{dfn[p], dfn[p] + siz[p] - 1, p};
	return;
}

bool operator<(Question a, Question b) {
	return a.r < b.r;
}

int bit[MAXN], ans[MAXN];
int maxans, maxcnt;

void Add(int p, int val) {
	for (; p <= n; p += p & -p) bit[p] += val;
	return;
}

int Query(int p) {
	int ans = 0;
	for (; p; p -= p & -p) ans += bit[p];
	return ans;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> c[i];
	for (int i = 1; i <= n; ++i) {
		char cc; cin >> cc;
		ch[i] = cc;
	}
	for (int i = 1; i < n; ++i) {
		int u, v; cin >> u >> v;
		ed[u].push_back(v);
		ed[v].push_back(u);
	}
	dfs(1, 0);
	sort(qry + 1, qry + n + 1);
	// for (int i = 1; i <= n; ++i) cout << h[i] << " ";
	// cout << "\n";
	for (int i = 1, p = 1; i <= n; ++i) {
		int las = mp[h[i]];
		mp[h[i]] = i;
		Add(i, 1);
		if (las) Add(las, -1);
		while (p <= n && qry[p].r == i) {
			ans[qry[p].pos] = Query(i) - Query(qry[p].l - 1) + c[qry[p].pos];
			++p;
		}
	}
	// for (int i = 1; i <= n; ++i) cout << qry[i].l << " " << qry[i].r << " " << qry[i].pos << " " << ans[qry[i].pos] << "\n";
	for (int i = 1; i <= n; ++i) {
		if (ans[i] > maxans) maxans = ans[i], maxcnt = 0;
		if (ans[i] == maxans) ++maxcnt;
	}
	cout << maxans << "\n" << maxcnt << "\n";
	return 0;
}
```

---

## 作者：幻影星坚强 (赞：2)

我们可以发现一个点它本质不同的子串数为该点所有儿子的不同子串数相加减去他们的公共部分。

而对于公共部分我们可以利用trie合并来处理。

trie合并的过程与线段树合并过程类似，具体看代码

```
#include <iostream>
#include <cstdio>
using namespace std;
int n;long long v[300010];
char s[300010];
struct bian
{
	int from, to;
}eg[300010 << 1];
int front[300010], num;
int trie[300010][30];
long long siz[300010], maxs, zong;
void lian(int x, int y)
{
	eg[++ num].to = y;
	eg[num].from = front[x];
	front[x] = num;
}
long long merge(int x, int y)
{
	long long maretu = 1;//公共部分数（默认有一个重合）
	if(trie[x][s[y] - 'a'] == 0)
	{
		trie[x][s[y] - 'a'] = y;//如果该节点不存在则将其合并
		maretu = 0;//同时也不存在公共部分
	}
	else
	{
		for (int i = 0; i <= 25; ++ i)//对于每个儿子进行该操作
		{
			if(trie[y][i] > 0)
			{
				maretu += merge(trie[x][s[y] - 'a'], trie[y][i]);//公共部分即为儿子的公共部分和
			}
		}
	}
	return maretu;
}
void dfs(int o, int fa)
{
	for (int i = front[o]; i; i = eg[i].from)
	{
		int to = eg[i].to;
		if(to == fa)continue;
		dfs(to, o);
		siz[o] += siz[to];
		siz[o] -= merge(o, to);
	}
	if(siz[o] + v[o] == maxs)
	++ zong;
	if(siz[o] + v[o] > maxs)
	maxs = siz[o] + v[o], zong = 1;
	
}
int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; ++ i)
	{
		siz[i] = 1;
		scanf("%lld", &v[i]);
	}
	scanf("%s", s + 1);
	for (int i = 1; i < n; ++ i)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		lian(x, y);
		lian(y, x);
	}
	dfs(1, 0);
	printf("%lld\n%lld", maxs, zong);
}
```


---

## 作者：1saunoya (赞：2)

这个玩意明显可以启发式合并+trie。

从底下到上面直接合并上去，然后就知道有多少个不同串了（不同结尾。）
（串应该是反的。）

然后就直接更新答案即可？

---

## 作者：lfxxx (赞：1)

考虑对于一个子树维护出子树内点到其的字符串构成的字典树，那么从儿子到父亲就在字典树根上方加一个点，处理子树内有多少个不同的字符串直接字典树合并即可做到线性乘字符集。


```python
#include<bits/stdc++.h>
using namespace std;
//#define int long long
//#define lowbit(x) (x&(-x))
//#define bp push_back
//#define sz size
//#define cl clear
const int maxn =1e6+114;
int son[maxn][26],cnt[maxn];
int rt[maxn];
int n,tot;
int c[maxn],dp[maxn];
char ch[maxn];
vector<int> E[maxn];
int S;//重复 
int ans,ct;
int merge(int a,int b){
	if(a==0||b==0) return a+b;
	S+=cnt[a];
	for(int i=0;i<26;i++) son[a][i]=merge(son[a][i],son[b][i]);
	return a;
}
void dfs(int u,int fa){
	rt[u]=++tot;
	for(int v:E[u]){
		if(v!=fa){
			dfs(v,u);
			S=0;
			tot++;
			son[tot][ch[u]-'a']=rt[v];
			rt[v]=tot;
			rt[u]=merge(rt[u],rt[v]);
			dp[u]=dp[u]+dp[v]-S;
		}
	}
	if(son[rt[u]][ch[u]-'a']==0) son[rt[u]][ch[u]-'a']=++tot;
	if(cnt[son[rt[u]][ch[u]-'a']]==0){
		cnt[son[rt[u]][ch[u]-'a']]=1;
		dp[u]++;
	}
	//cout<<u<<' '<<dp[u]<<'\n';
	if(dp[u]+c[u]>ans){
		ans=dp[u]+c[u];
		ct=1;
	}else if(dp[u]+c[u]==ans) ct++;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>c[i];
	for(int i=1;i<=n;i++) cin>>ch[i];
	for(int i=2;i<=n;i++){
		int u,v;
		cin>>u>>v;
		E[u].push_back(v);
		E[v].push_back(u);
	}
	dfs(1,0);
	cout<<ans<<'\n'<<ct<<'\n';
	return 0;
}
```

---

## 作者：Purslane (赞：1)

# Solution

诶，其实哈希可以做的更简单的。

为了区分两个串完全不一样，我们将 $\texttt a$ 映射为 $1$，$\texttt b$ 映射为 $2$，以此类推，在 $27$ 进制、双模数下判断相等。（如果你把 $\texttt a$ 映射为 $0$，那么 $\texttt {aaa}$ 和 $\texttt {aaaaaa}$ 就没区别了）

对于树上每个点，记录 $c_uc_{fa_u}c_{fa_{fa_u}}\cdots c_1$ 的哈希值 $h_u$。那么 $u$ 到 $v$（$v$ 在 $u$ 的子树内）路径反串的哈希值为 $(h_v-h_{fa_u}) \times 27^{-dep_u}$。

对于每个 $u$，我们要统计其子树内 $v$，所有上式值的种数。发现 $h_u$ 和 $dep_u$ 都是定值，所以只需要数一数 $h_v$ 有多少种。

只需要最朴素的启发式合并即可。复杂度 $O(n \log^2 n)$。用 Dsu On Tree 应该可以做到 $O(n \log n)$（提前离散化）

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=3e5+10,MOD1=1e9+7,MOD2=1e9+9;
int n,c[MAXN],dep[MAXN],cnt[MAXN],pw1[MAXN],pw2[MAXN],pre1[MAXN],pre2[MAXN];
string S;
vector<int> G[MAXN];
set<pair<int,int>> st[MAXN];
void merge(set<pair<int,int>> &x,set<pair<int,int>> &y) {
	if(x.size()<y.size()) swap(x,y);
	for(auto id:y) x.insert(id);
	return y.clear(),void();
}
void dfs(int u,int f) {
	dep[u]=dep[f]+1,pre1[u]=(pre1[f]+(S[u]-'a'+1)*pw1[dep[u]])%MOD1,pre2[u]=(pre2[f]+(S[u]-'a'+1)*pw2[dep[u]])%MOD2;
	st[u].insert({pre1[u],pre2[u]});
	for(auto v:G[u]) if(v!=f) dfs(v,u),merge(st[u],st[v]);	
	cnt[u]=st[u].size();
	return ;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n;ffor(i,1,n) cin>>c[i];cin>>S,S="&"+S;
	pw1[0]=pw2[0]=1,dep[0]=-1;
	ffor(i,1,n) pw1[i]=pw1[i-1]*27%MOD1,pw2[i]=pw2[i-1]*27%MOD2;
	ffor(i,1,n-1) {int u,v;cin>>u>>v,G[u].push_back(v),G[v].push_back(u);}
	dfs(1,0);
	int mx=0,cnts=0;
	ffor(i,1,n) if(c[i]+cnt[i]>mx) mx=c[i]+cnt[i],cnts=1;
	else if(c[i]+cnt[i]==mx) cnts++;
	cout<<mx<<'\n'<<cnts;
	return 0;
}
```

---

## 作者：Nemonade (赞：1)

# 题意

给定一棵有根树。点 $x$ 有权值 $a_x$ 和一个字符 $s_x$。现在定义函数 $\operatorname{dif}(x)$ 为：节点 $x$ 到 $x$ 的子树中任意一个点形成的字符串的种类。求 $\operatorname{dif}(x)+a_x$ 的最大值。

# 思路

看到这种求子树信息形式可以想到数据结构合并。这道题又是字符串相关所以考虑字典树的合并。

如何从 $x$ 的儿子推到 $x$ 呢？首先肯定有一个字符串是单走一个 $s_x$。然后考虑从一个儿子 $y$ 的字典树合并得到 $x$ 的字典树。$y$ 的字典树内每个字符串都是从 $x$ 出发的，所以想要得到 $x$ 的字典树只需要把全部字符串的开头加上一个字符，只需要一个简单的换根操作。

如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/fcdiec6v.png)

# 实现

实现我写的是直接的字典树合并，而不是启发式合并，其实也没有特别难写。

要垃圾回收哦。

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=3e5+5;
int n,ans1,ans2,a[N];char c[N];
vector<int> G[N];
struct Trie{
	int tot,ch[N*2][26],size[N*2];
	int root[N];bool tag[N*2];
	stack<int> reb;
	inline int Node(){
		if(reb.empty()) return ++tot;
		int p=reb.top();reb.pop();
		return p;
	}
	inline void recycle(int p){
		memset(ch[p],0,sizeof ch[p]);
		size[p]=tag[p]=0;
		reb.push(p);return;
	}
	inline void build(int x,char c){
		root[x]=Node();ch[root[x]][c-'a']=Node();
		size[ch[root[x]][c-'a']]=size[root[x]]=1;
		tag[ch[root[x]][c-'a']]=true;
		return;
	}
	inline void add(int x,char c){
		int p=Node();
		ch[p][c-'a']=root[x];
		size[p]=size[root[x]];
		root[x]=p;return;
	}
	inline int merge(int p,int q){
		if(!p||!q) return p+q;
		int np=Node();
		size[np]=tag[np]=(tag[p]|tag[q]);
		for(int i=0;i<26;++i){
			ch[np][i]=merge(ch[p][i],ch[q][i]);
			size[np]+=size[ch[np][i]];
		}
		recycle(p),recycle(q);
		return np;
	}
}trie;
inline void dfs(int x,int f){
	trie.build(x,c[x]);
	for(int y:G[x]){
		if(y==f) continue;
		dfs(y,x);
		trie.add(y,c[x]);
		trie.root[x]=trie.merge(trie.root[x],trie.root[y]);
	}
	int tmp=trie.size[trie.root[x]]+a[x];
	if(tmp==ans1) ++ans2;
	else if(tmp>ans1) ans1=tmp,ans2=1;
	return;
}
signed main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i) scanf("%d",a+i);
	scanf("%s",c+1);
	for(int i=1,x,y;i<n;++i){
		scanf("%d%d",&x,&y);
		G[x].push_back(y);
		G[y].push_back(x);
	}
	dfs(1,0);
	cout<<ans1<<endl<<ans2;
	return 0;
}
```

---

## 作者：qiyue7 (赞：1)

题目中要求的每个点的答案显然为每个点到其子树中所有点所生成的trie的节点数-1+题目给出的weight   

那么我们只需要自底向上进行trie的启发式合并即可。复杂度O(26*n)

AC代码：
```cpp

using namespace std;
const int N = 310010;
struct node
{
	node *nex[26];
	int size;
	node()
	{
		size = 1;
		memset(nex, 0, sizeof(nex));
	}
	void maintain()
	{
		size = 1;
		for (int i = 0; i < 26; ++i)
			if (nex[i] != NULL)
				size += nex[i]->size;
	}
};
node *trie[N];
int weight[N],pre1[N],W2[N];
char w[N];
vector<int> edge[N];
void merge(node *a, node *b)
{
	for (int i = 0; i < 26; ++i)
	{
		if (a->nex[i] && b->nex[i])
			merge(a->nex[i], b->nex[i]);
		else if (!a->nex[i] && b->nex[i])
			a->nex[i] = b->nex[i];
	}
	a->maintain();
}
void dfs(int u,int pre)
{
	queue<int> que;
	for (auto &s : edge[u])
	{
		if (s != pre)
		{
			que.push(s);
			dfs(s, u);
		}
	}
	if (que.empty())
		return;
	while (!que.empty())
	{
		int k;
		k = que.front();
		que.pop();
		if (trie[u]->nex[w[u] - 'a']->nex[w[k] - 'a'] == NULL)
		{
			trie[u]->nex[w[u] - 'a']->nex[w[k] - 'a'] = trie[k]->nex[w[k] - 'a'];
			trie[u]->nex[w[u] - 'a']->maintain();
			trie[u]->maintain();
		}
		else
		{
			merge(trie[u]->nex[w[u] - 'a'], trie[k]);
			trie[u]->nex[w[u] - 'a']->maintain();
			trie[u]->maintain();
		}
	}
	W2[u] = trie[u]->size-1+weight[u];
}
 
 
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int n,u,v;
	string s;
	memset(pre1, 0, sizeof(pre1));
	cin >> n;
	for (int i = 1; i <= n; ++i)
	{
		cin >> weight[i];
		W2[i] = 1+weight[i];
	}
	cin >> s;
	for (int i = 0; i < n; ++i)
		w[i+1] = s[i];
	for (int i = 1; i <= n; ++i)
	{
		trie[i] = new node();
		trie[i]->nex[w[i] - 'a'] = new node();
		trie[i]->maintain();
	}
	for (int i = 1; i < n; ++i)
	{
		cin >> u >> v;
		edge[u].push_back(v);
		edge[v].push_back(u);
	}
	dfs(1, 0);
	long long kkk = 0,cnt=0;
	for (int i = 1; i <= n; ++i)
	{
		if (W2[i] > kkk)
		{
			cnt = 1;
			kkk = W2[i];
		}
		else if (W2[i] == kkk)
			cnt++;
	}
	cout << kkk << endl << cnt << endl;;
	return 0;
}

```


---

## 作者：_slb (赞：0)

## 前言

最近遇到了一道诡异的题，std 的方法是启发式合并 Trie 树，但我写了个更简单（？）的 BFS＋Trie树+LCA 做法。

后来得知是 CF 的题，就上来交一波，结果确实 AC 了。

这做法大概是对的，但是似乎有点慢（还不好写）...

## 题意

有一棵以结点 $1$​ 为根的树，每个结点上都有一个小写字母，对于以每个结点，从该结点出发向其子树中走，路上经过的点能形成一个字符串。求以每个结点为根的子树中能用此方法走出的不同的字符串数量。

CF上原题还有一些奇怪的操作就不说了。

## Solution

显然这道题和 Trie 树有关。

对每个点 $i$​​​ 记录一个 $mus[i]$​​，表示以 $i$​​​​ 为根的子树中有多少个重复的字符串。~~（mus的意思大概是minus，即“减”）~~

考虑 BFS 原树，将遍历到的点插入到 Trie 树中，BFS 时候记录一下 Trie 树上每个点对应的在原树上的点数组 $trie$，如果插入的时候发现这个字符串已经被插入到 Trie 树中，说明有一个重复的字符串，将这个点和 Trie 树上的点对应在原树上点的 LCA 的 $mus$ 数组 $+1$​​​，更新上面的 $trie$ 数组。

最后跑一遍 DFS 统计答案即可。

值得一提的是可以发现如果字符串相同，那么他们在原树上深度必定相同，所以 LCA 的时候不用跳到深度相同了，直接求就行。

至于为什么在 LCA 上打标记，大概是因为打标记的时候要走到两个结点相同的，最早出现有至少两个儿子的字符相同的结点，在这里打标记，才会不重不漏。可以画画图理解。

时间复杂度 $O(n\log n)$，足以通过本题。

## Code

我这代码常数贼大，别人最慢也跑 $30s$，我直接干到 $50s$。

还好这题时限开得也大（

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 300010;
int ch[maxn][28], tot = 1, trie[maxn]; // ch 是 Trie 树
// trie[i] 代表在 Trie 树上编号为 i 的结点对应在原树上的结点编号。
vector<int> e[maxn];
void add(int x, int y) { e[x].push_back(y), e[y].push_back(x); }
string s;
int mus[maxn], siz[maxn], ans[maxn], v[maxn], a[maxn], n;
int f[maxn][32];
struct node // BFS 用结构体
{
    int fa, x, tfa; // fa，x 代表在原树中该结点父亲、该结点编号。
    // tfa 代表在 Trie 树上该结点的父亲
};
void dfs_lca(int x, int fa)
{
    f[x][0] = fa;
    for (int i = 1; i <= 31; i++)
        f[x][i] = f[f[x][i - 1]][i - 1];
    for (int i = 0; i < e[x].size(); i++)
        if (e[x][i] != fa)
            dfs_lca(e[x][i], x);
}
int LCA(int x, int y)
{
    if (x == y)
        return x;
    for (int i = 31; i >= 0; i--)
        if (f[x][i] != f[y][i])
            x = f[x][i], y = f[y][i];
    return f[x][0];
}

void init()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    cin >> s;
    s = " " + s;
    int x, y;
    for (int i = 0; i < n - 1; i++)
        scanf("%d%d", &x, &y), add(x, y);
    dfs_lca(1, 0);
}
void bfs()
{
    queue<node> q;
    q.push((node){0, 1, 1});
    while (!q.empty())
    {
        node now = q.front();
        q.pop();
        //now.P();
        if (v[now.x])
            continue;
        v[now.x] = 1;
        int c = s[now.x] - 'a';
        if (ch[now.tfa][c]) // 如果当前结点对应字符串已经被插入到 Trie 树中
            mus[LCA(now.x, trie[ch[now.tfa][c]])]++, trie[ch[now.tfa][c]] = now.x;
        // 在两点 LCA 上打标记，并将 Trie 树上该点对应原树上结点更新
        else
            ch[now.tfa][c] = ++tot, trie[ch[now.tfa][c]] = now.x;
        // 没被插入就新开个点，并更新 trie 数组
        for (int i = 0; i < e[now.x].size(); i++)
            q.push((node){now.x, e[now.x][i], ch[now.tfa][c]});
    }
}
void dfs(int x, int fa) // DFS 统计答案
{
    siz[x] = 1;
    for (int i = 0; i < e[x].size(); i++)
    {
        if (e[x][i] != fa)
        {
            dfs(e[x][i], x);
            siz[x] += siz[e[x][i]];
            mus[x] += mus[e[x][i]];
        }
    }
    ans[x] = siz[x] - mus[x];
}
void out_put()
{
    int mx = -1, cnt = 0;
    for (int i = 1; i <= n; i++)
    {
        if (mx == ans[i] + a[i])
            cnt++;
        else if (ans[i] + a[i] > mx)
            mx = ans[i] + a[i], cnt = 1;
    }
    cout << mx << endl
         << cnt << endl;
}
void solve()
{
    bfs();
    memset(v, 0, sizeof(v));
    dfs(1, 0);
}
int main()
{
    init();
    solve();
    out_put();
    return 0;
}
```

---

