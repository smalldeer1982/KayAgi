# Three strings

## 题目描述

You are given three strings $ (s_{1},s_{2},s_{3}) $ . For each integer $ l $ $ (1<=l<=min(|s_{1}|,|s_{2}|,|s_{3}|) $ you need to find how many triples ( $ i_{1},i_{2},i_{3} $ ) exist such that three strings $ s_{k}[i_{k}...\ i_{k}+l-1] $ $ (k=1,2,3) $ are pairwise equal. Print all found numbers modulo $ 1000000007 (10^{9}+7) $ .

See notes if you are not sure about some of the denotions used in the statement.

## 说明/提示

Consider a string $ t=t_{1}t_{2}...\ t_{|t|} $ , where $ t_{i} $ denotes the $ i $ -th character of the string, and $ |t| $ denotes the length of the string.

Then $ t[i...\ j] $ $ (1<=i<=j<=|t|) $ represents the string $ t_{i}t_{i+1}...\ t_{j} $ (substring of $ t $ from position $ i $ to position $ j $ inclusive).

## 样例 #1

### 输入

```
abc
bc
cbc
```

### 输出

```
3 1 
```

## 样例 #2

### 输入

```
abacaba
abac
abcd
```

### 输出

```
11 2 0 0 
```

# 题解

## 作者：Memory_of_winter (赞：3)

[我的博客](https://www.cnblogs.com/Memory-of-winter/p/10164330.html)

**题目大意：**给你三个字符串$A,B,C$，令$L=min(|A|,|B|,|C|)$，对每个$i\in[1,L]$，求出符合$A_{[a,a+i)}=B_{[b,b+i)}=C_{[c,c+i)}$的三元组$(a,b,c)$的个数

**题解：**先建一棵广义$SAM$，求出每个点可以到达的$A,B,C$的字串的个数，然后这个点贡献的值就是三个串分别的个数乘起来，发现一个点会对$[R_{fail_p+1},R_{p}]$的区间产生贡献，可以差分一下维护。

**卡点：**无



**C++ Code：**

```cpp
#include <algorithm>
#include <cstdio>
#include <cstring>
#define maxn 300010
const int mod = 1e9 + 7;
inline void reduce(int &x) {x += x >> 31 & mod;}

int n = 0x3f3f3f3f;
int ans[maxn];
namespace SAM {
#define N (maxn * 3 << 1)
	int R[N], fail[N], nxt[N][26];
	int lst = 1, idx = 1, sz[N][3];

	void append(int ch, int tg) {
		int p = lst, np = lst = ++idx; R[np] = R[p] + 1, sz[np][tg] = 1;
		for (; p && !nxt[p][ch]; p = fail[p]) nxt[p][ch] = np;
		if (!p) fail[np] = 1;
		else {
			int q = nxt[p][ch];
			if (R[p] + 1 == R[q]) fail[np] = q;
			else {
				int nq = ++idx;
				fail[nq] = fail[q], R[nq] = R[p] + 1, fail[q] = fail[np] = nq;
				std::copy(nxt[q], nxt[q] + 26, nxt[nq]);
				for (; p && nxt[p][ch] == q; p = fail[p]) nxt[p][ch] = nq;
			}
		}
	}

	int head[N], cnt;
	struct Edge {
		int to, nxt;
	} e[N];
	inline void addedge(int a, int b) {
		e[++cnt] = (Edge) {b, head[a]}; head[a] = cnt;
	}

	void dfs(int u) {
		for (int i = head[u]; i; i = e[i].nxt) {
			int v = e[i].to;
			dfs(v);
			sz[u][0] += sz[v][0], sz[u][1] += sz[v][1], sz[u][2] += sz[v][2];
		}
	}
	void work() {
		for (int i = 2; i <= idx; i++) addedge(fail[i], i);
		dfs(1);
		for (int i = 2; i <= idx; i++) {
			int tmp = static_cast<long long> (sz[i][0]) * sz[i][1] % mod * sz[i][2] % mod;
			reduce(ans[R[fail[i]] + 1] += tmp - mod), reduce(ans[R[i] + 1] -= tmp);
		}
		for (int i = 2; i <= n; i++) reduce(ans[i] += ans[i - 1] - mod);
	}
#undef N
}

char s[maxn];
int main() {
	for (int i = 0; i < 3; i++) {
		scanf("%s", s); SAM::lst = 1;
		n = std::min(n, static_cast<int> (strlen(s)));
		for (char *ch = s; *ch; ++ch) SAM::append(*ch - 'a', i);
	}
	SAM::work();
	for (int i = 1; i <= n; i++) {
		printf("%d", ans[i]);
		putchar(i == n ? '\n' : ' ');
	}
	return 0;
}

```





---

## 作者：Provicy (赞：1)

$\text{Problem}:$[Three strings](https://codeforces.com/problemset/problem/452/E)

$\text{Solution}:$

仿照 $\text{SA}$ 连接多个串的方式，我们可以把这三个串连成：$A+$`#`$+B+$`?`$+C$ 的形式。那么 $A,B,C$ 中相同的子串在 $\text{SAM}$ 的同一个节点上，将三个串的 $size$ 相乘，贡献给 $[\text{len(link}(x))+1,\text{len}(x)]$ 这个区间即可。利用序列差分可以做到 $O(n)$。

然后发现这是伪广义 $\text{SAM}$ 的一种建法，~~内心感到十分悲伤~~。考虑用普通 $\text{SAM}$ 解决本题。

这题两个串的情况是 [[HAOI2016] 找相同字符](https://www.luogu.com.cn/problem/P3181)，回顾一下用 $\text{SAM}$ 如何解决：对于第一个串建出 $\text{SAM}$，第二个串在 $\text{SAM}$ 上匹配。设当前匹配到的状态是 $x$，最长长度为 $now$，那么第二个串从根节点到 $\text{link}(x)$ 都可以覆盖；而对于状态 $x$，只能覆盖 $[\text{len(link}(x))+1,now]$。考虑把贡献分成两部分计算。在 $x$ 上的贡献可以直接计算，而对于根节点到 $\text{link}(x)$ 的贡献，可以通过前缀和预处理然后直接查询。这样就用普通 $\text{SAM}$ 做到了 $O(n)$ 的复杂度。

现在将两个串的情况推广到三个串（此处感谢 @Point_King 的指导）：我们称覆盖 $[\text{len(link}(x))+1,now]$ 为不完全覆盖，则不完全覆盖的总次数是 $O(n)$ 的。同时，我们可以把完全覆盖看作是 $now=\text{len}(x)$ 的情况，而这里可以用树上差分的方法统计出每个串在每个状态上完全覆盖的次数。设 $f_{now}$ 表示第二个串覆盖 $[\text{len(link}(x))+1,now]$ 的次数，$g_{now}$ 表示第三个串覆盖 $[\text{len(link}(x))+1,now]$ 的次数，那么对于一个状态 $x$，可以用后缀和处理出 $[\text{len(link}(x))+1,\text{len}(x)]$ 长度区间内的答案。此时复杂度为 $O(n^2)$。

发现对于所有状态，$f_{now}$ 和 $g_{now}$ 值不为 $0$ 的位置总数是 $O(n)$ 的，所以不用遍历整段区间，将第二个串和第三个串的 $now$ 排序去重后，只需要遍历总数为 $O(n)$ 的位置即可，而相邻两个位置之间对答案的贡献是相等的。时间复杂度 $O(n\log n)$，可以通过（在 $\text{CF}$ 上跑的和 $O(n)$ 差不多快）。此处也可以用桶排序，这样时间复杂度可以达到 $O(n)$。

当然，这种做法也可以推广到 $n$ 个字符串的情况。

$\text{Update 3.29}:$ 修正了一些笔误。

$\text{Code}:$

广义 $\text{SAM}:$

```cpp
#include <bits/stdc++.h>
#pragma GCC optimize(3)
//#define int long long
#define ri register
#define mk make_pair
#define fi first
#define se second
#define pb push_back
#define eb emplace_back
#define is insert
#define es erase
#define vi vector<int>
#define vpi vector<pair<int,int>>
using namespace std; const int N=600010, Mod=1e9+7;
inline int read()
{
	int s=0, w=1; ri char ch=getchar();
	while(ch<'0'||ch>'9') { if(ch=='-') w=-1; ch=getchar(); }
	while(ch>='0'&&ch<='9') s=(s<<3)+(s<<1)+(ch^48), ch=getchar();
	return s*w;
}
char s[3][N];
int n,m,len[3],g[3][N],Ans[N],tag[3][N],book[N];
int head[N],maxE; struct Edge { int nxt,to; }e[N];
inline void Add(int u,int v) { e[++maxE].nxt=head[u]; head[u]=maxE; e[maxE].to=v; }
struct SAM
{
	int link[N],len[N],ch[N][28];
	int tot,lst;
	inline SAM() { tot=lst=1; link[1]=len[1]=0; memset(ch[1],0,sizeof(ch[1])); }
	inline void Extend(int c)
	{
		int now=++tot;
		int p=lst;
		while(p && !ch[p][c]) ch[p][c]=now, p=link[p];
		len[now]=len[lst]+1;
		if(!p) { lst=now, link[now]=1; return; }
		int q=ch[p][c];
		if(len[q]==len[p]+1) link[now]=q;
		else
		{
			int nq=++tot;
			len[nq]=len[p]+1;
			memcpy(ch[nq],ch[q],sizeof(ch[q]));
			link[nq]=link[q];
			link[q]=link[now]=nq;
			while(p && ch[p][c]==q) ch[p][c]=nq, p=link[p];
		}
		lst=now;
	}
	inline void Renew()
	{
		for(ri int i=1;i<=tot;i++) link[i]=len[i]=0, memset(ch[i],0,sizeof(ch[i]));
		tot=lst=1;
	}
}A;
void DFS(int x)
{
	for(ri int i=head[x];i;i=e[i].nxt)
	{
		int v=e[i].to;
		DFS(v);
		for(ri int j=0;j<3;j++) g[j][x]+=g[j][v];
	}
}
signed main()
{
	for(ri int i=0;i<3;i++) scanf("%s",s[i]+1), len[i]=strlen(s[i]+1);
	m=min(len[0],min(len[1],len[2]));
	for(ri int i=0;i<3;i++)
	{
		for(ri int j=1;j<=len[i];j++) A.Extend(s[i][j]-'a');
		if(i<2) A.Extend(i+26);
	}
	for(ri int i=2;i<=A.tot;i++) Add(A.link[i],i);
	for(ri int i=0;i<3;i++)
	{
		int sta=1;
		for(ri int j=1;j<=len[i];j++)
		{
			int p=s[i][j]-'a';
			sta=A.ch[sta][p];
			g[i][sta]++;
		}
	}
	DFS(1);
	for(ri int i=2;i<=A.tot;i++)
	{
		int L=A.len[A.link[i]]+1, R=A.len[i];
		int w=1ll*g[0][i]*g[1][i]%Mod*g[2][i]%Mod;
		Ans[L]=(Ans[L]+w)%Mod;
		Ans[R+1]=(Ans[R+1]-w+Mod)%Mod;
	}
	for(ri int i=1;i<=m;i++)
	{
		Ans[i]=(Ans[i]+Ans[i-1])%Mod;
		if(Ans[i]<0) Ans[i]+=Mod;
	}
	for(ri int i=1;i<=m;i++) printf("%d ",Ans[i]);
	puts("");
	return 0;
}
```

普通 $\text{SAM}:$

```cpp
#include <bits/stdc++.h>
#pragma GCC optimize(3)
//#define int long long
#define ri register
#define mk make_pair
#define fi first
#define se second
#define pb push_back
#define eb emplace_back
#define is insert
#define es erase
#define vi vector<int>
#define vpi vector<pair<int,int>>
using namespace std; const int N=600010, Mod=1e9+7;
inline int read()
{
	int s=0, w=1; ri char ch=getchar();
	while(ch<'0'||ch>'9') { if(ch=='-') w=-1; ch=getchar(); }
	while(ch>='0'&&ch<='9') s=(s<<3)+(s<<1)+(ch^48), ch=getchar();
	return s*w;
}
char s[3][N];
int n,m,len[3],siz[N],o[3][N],book[N],Ans[N];
vi g[3][N];
struct Node { int w,ti,id; };
vpi h; vector<Node> H;
int head[N],maxE; struct Edge { int nxt,to; }e[N];
inline void Add(int u,int v) { e[++maxE].nxt=head[u]; head[u]=maxE; e[maxE].to=v; }
struct SAM
{
	int link[N],len[N],ch[N][26];
	int tot,lst;
	inline SAM() { tot=lst=1; link[1]=len[1]=0; memset(ch[1],0,sizeof(ch[1])); }
	inline void Extend(int c)
	{
		int now=++tot;
		int p=lst;
		siz[now]=1;
		while(p && !ch[p][c]) ch[p][c]=now, p=link[p];
		len[now]=len[lst]+1;
		if(!p) { lst=now, link[now]=1; return; }
		int q=ch[p][c];
		if(len[q]==len[p]+1) link[now]=q;
		else
		{
			int nq=++tot;
			len[nq]=len[p]+1;
			memcpy(ch[nq],ch[q],sizeof(ch[q]));
			link[nq]=link[q];
			link[q]=link[now]=nq;
			while(p && ch[p][c]==q) ch[p][c]=nq, p=link[p];
		}
		lst=now;
	}
	inline void Renew()
	{
		for(ri int i=1;i<=tot;i++) link[i]=len[i]=0, memset(ch[i],0,sizeof(ch[i]));
		tot=lst=1;
	}
}A;
inline void UpDate(int x,int l,int r,int w1,int w2)
{
	if(l>r) return;
	int w=1ll*siz[x]*w1%Mod*w2%Mod;
	Ans[l]=(Ans[l]+w)%Mod;
	Ans[r+1]=(Ans[r+1]-w+Mod)%Mod;
}
void DFS(int x)
{
	for(ri int i=head[x];i;i=e[i].nxt)
	{
		int v=e[i].to;
		DFS(v);
		siz[x]+=siz[v];
		for(ri int j=1;j<3;j++) o[j][x]+=o[j][v];
	}
	if(x==1) return;
	int tot1,tot2;
	tot1=(int)g[1][x].size()+o[1][x];
	tot2=(int)g[2][x].size()+o[2][x];
	if(!tot1||!tot2) return;
	h.clear(), H.clear();
	for(ri int i=1;i<3;i++)
	for(auto j:g[i][x]) h.eb(mk(j,i));
	sort(h.begin(),h.end());
	pair<int,int> lst={-1,-1};
	int flg1,flg2; flg1=flg2=0;
	for(auto i:h)
	{
		if(i==lst) H.back().ti++;
		else
		{
			H.eb((Node){i.fi,1,i.se});
			if(i.fi==A.len[x])
			{
				if(i.se==1&&!flg1)
				{
					flg1=1;
					H.back().ti+=o[1][x];
				}
				if(i.se==2&&!flg2)
				{
					flg2=1;
					H.back().ti+=o[2][x];
				}
			}
			lst=i;
		}
	}
	if(!flg1) H.eb((Node){A.len[x],o[1][x],1});
	if(!flg2) H.eb((Node){A.len[x],o[2][x],2});
	int pre=A.len[A.link[x]]+1;
	for(auto i:H)
	{
		UpDate(x,pre,i.w,tot1,tot2);
		pre=i.w+1;
		if(i.id==1) tot1-=i.ti;
		else tot2-=i.ti;
	}
}
signed main()
{
	for(ri int i=0;i<3;i++) scanf("%s",s[i]+1), len[i]=strlen(s[i]+1);
	m=min(len[0],min(len[1],len[2]));
	for(ri int i=1;i<=len[0];i++) A.Extend(s[0][i]-'a');
	for(ri int i=2;i<=A.tot;i++) Add(A.link[i],i);
	for(ri int i=1;i<3;i++)
	{
		int sta=1,now=0;
		for(ri int j=1;j<=len[i];j++)
		{
			int p=s[i][j]-'a';
			while(sta && !A.ch[sta][p]) sta=A.link[sta], now=A.len[sta];
			if(!sta) { sta=1; continue; }
			if(A.ch[sta][p]) sta=A.ch[sta][p], now++;
			g[i][sta].eb(now), o[i][A.link[sta]]++;
		}
	}
	DFS(1);
	for(ri int i=1;i<=m;i++)
	{
		Ans[i]=(Ans[i]+Ans[i-1])%Mod;
		if(Ans[i]<0) Ans[i]+=Mod;
	}
	for(ri int i=1;i<=m;i++) printf("%d ",Ans[i]);
	puts("");
	return 0;
}
```



---

## 作者：2018LZY (赞：1)

# 思路:
广义SAM+差分.

显然,相同的串在SAM的相同节点上,那么我们统计一下这个状态在所有串中的出现次数即可.

用差分处理:
对于一个状态$x$,长度为$[l,r]$,贡献为$t$,那么直接$d[l]+=t,d[r+1]-=t$即可.

最后顺序求和输出即可.

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N=6e5+10,mod=1000000007;

char s[N];
struct node {int fa,len,v[26];}tr[N];
int n,mx,len,last=1,tot=1,b[N],c[N],now,f[N][3];

void add(int c) {
	int p=last;
	if(tr[p].v[c]) {
		int q=tr[p].v[c],y;
		if(tr[p].len+1==tr[q].len) last=q;
		else {
			tr[last=y=++tot]=tr[q];
			tr[y].len=tr[p].len+1;
			tr[q].fa=y;
			for(	;p&&tr[p].v[c]==q;p=tr[p].fa) tr[p].v[c]=y;
		}
	}
	else {
		int x=last=++tot; tr[x].len=tr[p].len+1;
		for(	;p&&!tr[p].v[c];p=tr[p].fa) tr[p].v[c]=x;
		if(!p) tr[x].fa=1;
		else {
			int q=tr[p].v[c],y;
			if(tr[p].len+1==tr[q].len) tr[x].fa=q;
			else {
				tr[y=++tot]=tr[q];
				tr[y].len=tr[p].len+1;
				tr[q].fa=tr[x].fa=y;
				for(	;p&&tr[p].v[c]==q;p=tr[p].fa) tr[p].v[c]=y;
			}
		}
	}
	f[last][now]++;
}

void Sort() {
	for(int i=0;i<=mx;i++) c[i]=0;
	for(int i=1;i<=tot;i++)  c[tr[i].len]++;
	for(int i=1;i<=mx;i++) c[i]+=c[i-1];
	for(int i=tot; i;i--)  b[c[tr[i].len]--]=i;
}

void upd(int &x) {x+=x>>31&mod;}

int d[N];

int main() {
	n=N;
	for(now=0;now<3;now++) {
		scanf("%s",s+1);last=1;len=0;
		for(int i=1;s[i];i++) add(s[i]-'a'),len++;
		n=min(n,len);
		mx=max(mx,len);
	}
	Sort();
	for(int i=tot;i>1;i--) {
		int j=b[i],fa=tr[j].fa;
		for(int k=0;k<3;k++) f[fa][k]+=f[j][k];
		int *F=f[j];
		ll t=(ll)F[0]*F[1]*F[2]%mod;
		upd(d[tr[fa].len+1]+=t-mod); 
		upd(d[tr[j].len+1]-=t);
	}
	int ans=0;
	for(int i=1;i<=n;i++) {
		upd(ans+=d[i]-mod);
		printf("%d ",ans);
	}
	puts("");
	return 0;
}


```



---

## 作者：5k_sync_closer (赞：0)

建广义 SAM，考虑统计 $e_{i,0/1/2}$ 表示 $i$ 点在每个串中分别出现多少次，

也就是说，对于 $T$ 串的每个前缀，将其对应节点的 link 树根链上每个点 $u$ 的 $e_{u,T}$ 加上 $1$。

可以将其树上差分为单点加，子树求和，最终可以得到每个 $i$ 点的 $e_{i,0/1/2}$。

考虑每个点的贡献，显然 $i$ 点会使 $(\text{len}(\text{link}(i)),\text{len}(i)]$ 的答案各加上 $e_{i,0}\times e_{i,1}\times e_{i,2}$。

```cpp
#include <queue>
#include <string>
#include <iostream>
#include <algorithm>
#define M 1000000007
using namespace std;
queue<int> q;
int T, n, o, z, e[600050][3], l[600050], f[600050], d[600050], c[600050][26];
long long Q[600050];
string u[600050];
void I(int x)
{
    int u = ++o, p = z;
    l[u] = l[z] + 1;
    while (p != -1 && !c[p][x])
        c[p][x] = u, p = f[p];
    if (p == -1)
        f[u] = 0;
    else
    {
        int q = c[p][x];
        if (l[p] + 1 == l[q])
            f[u] = q;
        else
        {
            int w = ++o;
            l[w] = l[p] + 1;
            f[w] = f[q];
            for (int i = 0; i < 26; ++i)
                c[w][i] = c[q][i];
            while (p != -1 && c[p][x] == q)
                c[p][x] = w, p = f[p];
            f[q] = f[u] = w;
        }
    }
    z = u;
}
int main()
{
    f[0] = -1;
    T = 3;
    for (int i = 0; i < T; ++i)
    {
        cin >> u[i];
        z = 0;
        for (auto j : u[i])
            I(j - 'a');
    }
    for (int i = 0; i < T; ++i)
        for (int j = 0, p = 0; j < u[i].size(); ++j)
            p = c[p][u[i][j] - 'a'], ++e[p][i];
    for (int i = 1; i <= o; ++i)
        ++d[f[i]];
    for (int i = 1; i <= o; ++i)
        if (!d[i])
            q.push(i);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        if (!u)
            continue;
        Q[l[f[u]] + 1] = (Q[l[f[u]] + 1] + 1ll * e[u][0] * e[u][1] % M * e[u][2] % M) % M;
        Q[l[u] + 1] = (Q[l[u] + 1] + M - 1ll * e[u][0] * e[u][1] % M * e[u][2] % M) % M;
        for (int i = 0; i < 3; ++i)
            e[f[u]][i] += e[u][i];
        if (!--d[f[u]])
            q.push(f[u]);
    }
    for (int i = 1; i <= (int)min({u[0].length(), u[1].length(), u[2].length()}); ++i)
        cout << (Q[i] = (Q[i] + Q[i - 1]) % M) << ' ';
    return 0;
}
```


---

## 作者：Mihari (赞：0)

# 题目

[传送门](https://www.luogu.com.cn/problem/CF452E)

# 题解

## 算法一

暴力做，枚举 $A$ 的字串，在 $B,C$ 中暴力找，时间复杂度 $\mathcal O(n^4)$.

## 算法二

同样要在 $A$ 中枚举字串，但是考虑在 $L=1$ 时，对于 $A$ 的每个字符，我们可以在 $B,C$ 中找出相匹配的，随着 $L$ 变大，可能的相同的部分也只可能在之前匹配的字符之后出现，所以我们可以考虑用类似于 `vector` 一类的东西将位置存下来，时间复杂度 $\mathcal O(\tt{TLE})$.

## 算法三(SA)

考虑使用 $\tt SA$ 将字符串匹配转换为 $\tt LCP$ 问题.

首先，处理这种问题的关键是我们得将 $A,B,C$ 首尾相接得到 $S$，中间使用分隔符隔开，接下来我们称其为 $S$ 的 $A,B,C$ 三个部分.

接下来，字符串内部的匹配问题就转化为后缀的 $\tt LCP$ 问题，对于原来 $A,B,C$ 三个串长度为 $L$ 的匹配，现在即为属于三个不同部分的后缀的 $\texttt{LCP} \ge L$ 即可.

但是，对于不同的部分，他们的 $\tt LCP$ 并非是单调的，比如我们有个后缀排序的数组长这样

<div align="center">
    <img src="https://s3.ax1x.com/2020/12/23/r6NfQP.md.jpg">
</div>

对于 $L=4$ 时，可能有这些部分的 $\tt LCP$ 是满足条件的

<div align="center">
    <img src="https://s3.ax1x.com/2020/12/23/r6U3lt.jpg">
</div>

那么 $\tt ans[4]$ 就是各个部分的 $\tt cnt[A] \cdot cnt[B] \cdot cnt[C]$，其中 $\tt cnt[i]$ 表示属于 $i$ 部分的后缀的个数.

但是，随着 $L$ 变大，各个部分有可能会断开，这让我们非常不好处理，既然 $L$ 变大会断开，那么**同样意味着，如果我们倒着处理 $L$，那么随着 $L$ 的变小，会有越来越多的部分连接在一起，这个时候我们只需要维护 `cnt[i]` 即可**，而这个部分可以使用并查集来做，并查集合并的时候，我们也可以维护答案.

关键代码：

```cpp
const int jzm=1000000007;
/** @brief 全局答案*/
int sy=0;
/** @brief 对应长度的答案*/
int ans[maxn+5];
struct node{
    // x 是后缀编号
    int x,v;
    inline int operator <(const node rhs)const{
        return v>rhs.v;
    }
}v[maxn+5+5];
int fa[maxn+5];
int find(const int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
int cock(const int x){
    return 1ll*tot[x][1]*tot[x][2]%jzm*tot[x][3]%jzm;
}
inline void merge(int x,int y){
    // printf("merge:> x == %d, y == %d\n",x,y);
    x=find(x),y=find(y);
    if(x==y)return;
    sy-=cock(x);if(sy<0)sy+=jzm;
    sy-=cock(y);if(sy<0)sy+=jzm;
    fa[x]=y;
    rep(j,1,3)tot[y][j]+=tot[x][j];
    sy+=cock(y);
    if(sy>=jzm)sy-=jzm;
}

inline void solve(){
    rep(i,1,n)v[i]=node{sa[i],heit[i]};
    rep(i,1,n)fa[i]=i;
    sort(v+1,v+n+1);
    // rep(i,1,n)printf("v[%d] : x == %d, v == %d\n",i,v[i].x,v[i].v);
    int now=1;
    fep(i,min_len,1){
        while(now<=n && v[now].v>=i){
            // printf("When i == %d, now == %d\n",i,now);
            int pre=sa[rk[v[now].x]-1];
            merge(pre,v[now].x);
            ++now;
        }
        ans[i]=sy;
    }
    rep(i,1,min_len)printf("%d ",ans[i]);
}
```

## 算法四(SAM)

这个方法再等会可能就可以完善了.

# 一道类似的题

[传送门](https://www.luogu.com.cn/problem/CF873F)

---

## 作者：foreverlasting (赞：0)

[题面](https://www.luogu.org/problemnew/show/CF452E)

广义后缀自动机。

这题感觉超级傻啊，先对三个串建出广义后缀自动机，然后建出后缀树，$dfs$一遍，把每个结点代表的出现过的串的个数记录一下，三个串分别记录一下，那么这个长度的答案就是三个的乘积。然后一个结点代表的长度应该是它的父亲的$len$+1到它的$len$，那么差分一下，就可以做到区间修改了。于是就没了。

code:
```
//2018.11.16 by ljz
#include<bits/stdc++.h>
using namespace std;
#define res register int
#define LL long long
#define inf 0x3f3f3f3f
#define eps 1e-15
inline int read(){
    res s=0;
    bool w=0;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')w=1;ch=getchar();}
    while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=getchar();
    return w?-s:s;
}
inline void _swap(res &x,res &y){
    x^=y^=x^=y;
}
inline int _abs(const res &x){
    return x>0?x:-x;
}
inline int _max(const res &x,const res &y){
    return x>y?x:y;
}
inline int _min(const res &x,const res &y){
    return x<y?x:y;
}
const int N=3e5+10;
const int kcz=1e9+7;
namespace MAIN{
    int sz[N<<1][3];
    struct SAM{
        struct Sam{
            int vis[26],par,len;
        }sam[N<<1];
        int cnt,las,rt;
        SAM() {cnt=las=rt=1;}
        inline void extend(const res &x,const res &id){
            res p=las,np=++cnt;
            las=np,sam[np].len=sam[p].len+1,sz[np][id]++;
            for(;p&&!sam[p].vis[x];p=sam[p].par)sam[p].vis[x]=np;
            if(!p)sam[np].par=rt;
            else {
                res q=sam[p].vis[x];
                if(sam[q].len==sam[p].len+1)sam[np].par=q;
                else {
                    res nq=++cnt;
                    memcpy(sam[nq].vis,sam[q].vis,sizeof(sam[nq].vis));
                    sam[nq].len=sam[p].len+1,sam[nq].par=sam[q].par,sam[q].par=sam[np].par=nq;
                    for(;p&&sam[p].vis[x]==q;p=sam[p].par)sam[p].vis[x]=nq;
                }
            }
        }
    }A;
    char str[N];
    struct E{
        int next,to;
        E() {}
        E(res next,res to):next(next),to(to) {}
    }edge[N<<1];
    int head[N<<1],cnt;
    inline void addedge(const res &u,const res &v){
        edge[++cnt]=E(head[u],v),head[u]=cnt;
    }
    int ans[N];
    inline void add(res &x,const res &y){
        x+=y;
        x>=kcz?x-=kcz:1;
    }
    void dfs(const res &x){
        for(res i=head[x];~i;i=edge[i].next){
            res tox=edge[i].to;
            dfs(tox);
            sz[x][0]+=sz[tox][0],sz[x][1]+=sz[tox][1],sz[x][2]+=sz[tox][2];
        }
        add(ans[A.sam[A.sam[x].par].len+1],1LL*sz[x][0]*sz[x][1]%kcz*sz[x][2]%kcz);
        add(ans[A.sam[x].len+1],kcz-1LL*sz[x][0]*sz[x][1]%kcz*sz[x][2]%kcz);
    }
    int mi=inf;
    inline void MAIN(){
        memset(head,-1,sizeof(head));
        scanf("%s",str+1),A.las=1;
        mi=_min(mi,strlen(str+1));
        for(res i=1,sz=strlen(str+1);i<=sz;i++)A.extend(str[i]-'a',0);
        scanf("%s",str+1),A.las=1;
        mi=_min(mi,strlen(str+1));
        for(res i=1,sz=strlen(str+1);i<=sz;i++)A.extend(str[i]-'a',1);
        scanf("%s",str+1),A.las=1;
        mi=_min(mi,strlen(str+1));
        for(res i=1,sz=strlen(str+1);i<=sz;i++)A.extend(str[i]-'a',2);
        for(res i=2;i<=A.cnt;i++)if(A.sam[i].par)addedge(A.sam[i].par,i);
        dfs(1);
        for(res i=1;i<=mi;i++)add(ans[i],ans[i-1]),printf("%d ",ans[i]);
    }
}
int main(){
    MAIN::MAIN();
    return 0;
}
```

---

