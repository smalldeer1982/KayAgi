# Representative Sampling

## 题目描述

The Smart Beaver from ABBYY has a long history of cooperating with the "Institute of Cytology and Genetics". Recently, the Institute staff challenged the Beaver with a new problem. The problem is as follows.

There is a collection of $ n $ proteins (not necessarily distinct). Each protein is a string consisting of lowercase Latin letters. The problem that the scientists offered to the Beaver is to select a subcollection of size $ k $ from the initial collection of proteins so that the representativity of the selected subset of proteins is maximum possible.

The Smart Beaver from ABBYY did some research and came to the conclusion that the representativity of a collection of proteins can be evaluated by a single number, which is simply calculated. Let's suppose we have a collection $ {a_{1},...,a_{k}} $ consisting of $ k $ strings describing proteins. The representativity of this collection is the following value:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF178F3/c7b3873e6751582bb5e2ad2c1deb58138ab9c543.png)where $ f(x,y) $ is the length of the longest common prefix of strings $ x $ and $ y $ ; for example, $ f( $ "abc", "abd" $ )=2 $ , and $ f( $ "ab", "bcd" $ )=0 $ .

Thus, the representativity of collection of proteins $ { $ "abc", "abd", "abe" $ } $ equals $ 6 $ , and the representativity of collection $ { $ "aaa", "ba", "ba" $ } $ equals $ 2 $ .

Having discovered that, the Smart Beaver from ABBYY asked the Cup contestants to write a program that selects, from the given collection of proteins, a subcollection of size $ k $ which has the largest possible value of representativity. Help him to solve this problem!

## 样例 #1

### 输入

```
3 2
aba
bzd
abq
```

### 输出

```
2
```

## 样例 #2

### 输入

```
4 3
eee
rrr
ttt
qqq
```

### 输出

```
0
```

## 样例 #3

### 输入

```
4 3
aaa
abba
abbc
abbd
```

### 输出

```
9
```

# 题解

## 作者：_ctz (赞：5)

[$My\ blog$](https://ctz45562.github.io/2019/11/06/Codeforces178F3-Representative-Sampling/)

[传送门](https://www.luogu.org/problem/CF178F3)

翻译+一血+首篇题解+三倍经验美滋滋。

造个$trie$树，考虑一个朴素的$trie$树$DP$：

设$f(i,j)$为点$i$的子树内选了$j$个结束节点的最大答案，$s(i)$为点$i$子树内结束节点的个数。

为了不让贡献重复计算只考虑$i$到其父亲的边的贡献。

转移是个树形背包：

$f(i,j)=\max\limits_{x\in son(i),k\le \min\{j,s(x)\}}\{f(x,k)+f(i,j-k)\}+\dfrac{j\times(j-1)}{2}(j\le s(i))$

复杂度最高有$O(n|a_i|k)$。

我们发现有些没有分支和结束节点的链是多余的。

具体地说，只有结束节点和它们两两之间的$lca$有用，直接造虚树。

但是这里不用真的写虚树板子，我们只需$dfs$一遍把根节点、拥有至少$2$个儿子的节点和结束节点保留下来就行了。

记$dep(i)$为点$i$在原$trie$树上的深度。虚树上的方程要稍加改动：

$f(i,j)=\max\limits_{x\in son(i),k\le \min\{j,s(x)\}}\{f(x,k)+f(i,j-k)\}+\dfrac{j\times(j-1)}{2}\times(dep(i)-dep(fa_i))(j\le s(i))$

复杂度是$O(nk)$的。

代码：

``` cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>

#define maxn 1000005
#define inf 0x3f3f3f3f

using namespace std;

inline int read(){
	int x=0,y=0;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')y=1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return y?-x:x;
}
#define son(x,y) son[x][y]
int en[maxn],son[maxn][26],siz[maxn],deep[maxn],s[4005],f[4005][2005],h[4005],c[2005],num,k,cnt=1,all;
char a[505];
struct edge{int pre,to;}e[maxn];
inline void add(int from,int to){e[++num]=(edge){h[from],to},h[from]=num;}
void insert(){
	int len=strlen(a+1),node=1;
	for(register int i=1;i<=len;++i){
		if(!son(node,a[i]-'a'))son(node,a[i]-'a')=++cnt,++siz[node];
		node=son(node,a[i]-'a');
	}
	++en[node];
}
void dfs(int node=1,int dep=0,int last=0){
	if(node==1||siz[node]>1||en[node])deep[++all]=dep,add(last,all),last=all,s[all]=en[node];
	for(register int i=0;i<26;++i)if(son(node,i))dfs(son(node,i),dep+1,last);
}
void dp(int node=1,int fa=0){
	f[node][0]=0;
	for(register int i=h[node],x;i;i=e[i].pre){
		dp(x=e[i].to,node),s[node]+=s[x];
		for(register int j=min(s[node],k);j;--j)
			for(register int k=min(s[x],j);k;--k)
				f[node][j]=max(f[node][j],f[x][k]+f[node][j-k]);
	}
	for(register int i=1;i<=s[node];++i)f[node][i]+=c[i]*(deep[node]-deep[fa]);
}
int main(){
	int n=read();
	k=read();
	for(register int i=1;i<=n;++i)scanf("%s",a+1),insert();
	for(register int i=1;i<=k;++i)c[i]=i*(i-1)>>1;
	dfs(),dp();
	printf("%d\n",f[1][k]);
}
```



---

## 作者：极寒神冰 (赞：5)

因为要求 LCP，所以考虑建一棵字典树。在字典树中，两个串的 LCP 为它们的 LCA 的深度。

而对于那些对应了一整个字符串的节点（不一定是叶节点），我们称它们是重要的。

然后考虑树形 $dp$。

记 $dp_{i,j}$ 表示以 $i$ 为根的子树中，选取了 $j$ 个重要节点，两两串之间 LCA 的深度之和的最大值。其中根结点的深度为 $0$。

边界 $dp_{i,1}=0$，答案为 $dp_{1,k}$。

记 $i$ 的子节点为 $v_1,v_2,\cdots$，$f_{v_j,l}$ 表示以 $i$ 为根的子树中，只考虑子树 $v_1,v_2,\cdots,v_k$，选取 $l$ 个重要节点时深度之和最大值，转移：

$$
f_{v_j,l}=\max\left(f_{v_{j-1},l-p}+dp_{v_j,p}+\binom p 2\right)
$$

这样子最坏复杂度是 $\mathcal O(n^2|S|)$。

但是可以发现，因为任意两个串只会在它们的 LCA 处更新 dp 值。

因此可以把这棵树压缩一下变成带权树，只保留可能是 LCA 的节点。

可以证明这样的节点数是 $\mathcal O(n)$ 的，时间复杂度 $\mathcal O(n^2)$.

```cpp
#include<bits/stdc++.h>
#define R(i,a,b) for(int i=(a),i##E=(b);i<=i##E;i++)
#define L(i,a,b) for(int i=(b),i##E=(a);i>=i##E;i--)
using namespace std;
int n,m;
int dis[1011111],siz[1011111];
int val[1011111],cnt=1;
int tr[1011111][26];
int dp[6888][2222],f[6888][2222];
int id[1011111],tim;
inline int ckmax(int &x,const int y)
{
	return x<y?x=y,1:0;
}
inline int calc(int x)
{
	return (x*(x-1))>>1;
}
inline void ins(const string &s)
{
	int t=1,tt;
	R(i,0,(int)s.size()-1)
	{
		tt=s[i]-'a';
		if(!tr[t][tt]) tr[t][tt]=++cnt;
		t=tr[t][tt];
	}
	++val[t];
}
void dfs(int u)
{
	//cout<<"u: "<<u<<endl;
	id[u]=++tim;
	siz[u]=val[u];
	int v;
	R(i,0,25) if(v=tr[u][i]) dfs(v),siz[u]+=siz[v];
	int lst=0;
	R(i,0,25) if(v=tr[u][i])
	{
		L(j,1,min(siz[u],m)) R(k,0,min(siz[v],j))
		{
			//cout<<"i: "<<i<<" j: "<<j<<" k: "<<k<<endl;
 			ckmax(f[id[v]][j],f[id[lst]][j-k]+dp[id[v]][k]+calc(k)*(dis[v]+1));
		}
		lst=v;
	}
	memcpy(dp[id[u]],f[id[lst]],sizeof(dp[id[u]]));
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin>>n>>m;
	string s;
	R(i,1,n)
	{
		cin>>s;
		ins(s);
	}
	L(i,2,cnt) 
	{
		if(!val[i])
		{
			int ok=1,t=0;
			R(j,0,25) if(tr[i][j])
			{
				if(t) 
				{
					ok=0;
					break;
				}
				t=tr[i][j];
			}
			if(ok&&!val[t]) dis[i]=dis[t]+1,memcpy(tr[i],tr[t],26<<2);
		}
	}	

	dfs(1);
	cout<<dp[1][m]<<endl;
}
```

---

## 作者：沉石鱼惊旋 (赞：4)

# 题目翻译

给定 $n(n\leq 2000)$ 个串，选定 $k$ 个串，求出最大两两 LCP。

# 题目思路

首先把给定串按字典序排序，保证相邻 LCP 最大。

考虑 dp，$f_{l,r,x}$ 表示选择 $[l,r]$ 中有 $x$ 个串的最大两两 LCP。

类似分治，转移的时候枚举相邻 LCP 最小的点 $m$，一定是在 $m$ 断开最优。转移枚举左右段分选几个串，加上串的个数乘上 $\operatorname{lcp}(s_m,s_{m+1})$。这个 $\operatorname{lcp}$ 需要预处理。

时间复杂度 $\mathcal O(n^2)$。

# 完整代码

```cpp
#include <bits/stdc++.h>
using namespace std;
template <typename T>
void chkmx(T &x, T y) { x = max(x, y); }
typedef vector<int> vi;
int n, k;
int lcp[2020];
string s[2020];
vi solve(int l, int r)
{
    if (l == r)
        return vi(2, 0);
    int m = min_element(lcp + l, lcp + r) - lcp;
    vi L = solve(l, m);
    vi R = solve(m + 1, r);
    vi f(r - l + 2, 0);
    for (int l = 0; l < L.size(); l++)
        for (int r = 0; r < R.size(); r++)
            chkmx(f[l + r], L[l] + R[r] + lcp[m] * l * r);
    return f;
}
int main()
{
    cin >> n >> k;
    for (int i = 1; i <= n; i++)
        cin >> s[i];
    sort(s + 1, s + n + 1);
    for (int i = 1; i <= n; i++)
    {
        int len = 0;
        while (len < min(s[i].size(), s[i + 1].size()) && s[i][len] == s[i + 1][len])
            len++;
        lcp[i] = len;
    }
    cout << solve(1, n)[k] << endl;
    return 0;
}
```

---

## 作者：forest114514 (赞：4)

### CF178F3 Representative Sampling

不知道为什么要用 trie 树捏。

首先类比 SA 求 LCP，把一车串按字典序排序，对 $a$ 排序后计 $height_{i}=LCP(a_{i},a_{i-1})$，这样两两的 LCP 变成了区间 $height$ 的最小值。

考虑对这个 $height$ 建笛卡尔树，做一个树上背包即可，可以在每个节点计算两个子树之间点对的贡献。设  $f_{u,x}$ 为子树 $u$ 内选 $x$ 个点的最大两两 LCP 和，则 $f_{u,x}=\max\limits_{l+r=x}f_{ls_u,l}+f_{rs_u,r}+height_{u}\times l\times r$，叶节点的初值就是 $f_{u,0/1}=0$。

排序使用哈希实现的话，时间复杂度 $O(n|a_{i}|+n\log n\log |a_{i}|+nk)$，但是这里暴力排序+暴力求 LCP $O(n|a_{i}|\log n)$ 都能过吧。

放个代码：

```cpp
const int N=2005;
int n,k,f[N][N],height[N],ct;
string s[N];
int LCP(int x,int y){
	int l=min(s[x].size(),s[y].size());
	rep(i,0,l-1) if(s[x][i]!=s[y][i]) return i;
	return l;
}
int st[N],top,ls[N],rs[N],siz[N];
void dfs(int u,int l,int r){
	if(l==r) return;
	dfs(ls[u],l,u-1);
	dfs(rs[u],u,r);
	rep(i,0,min(k,r-l+1))
		rep(j,0,min(u-l,i))  f[u][i]=max(f[u][i],f[ls[u]][j]+f[rs[u]][i-j]+height[u]*j*(i-j));
}
signed main(){
	read(n,k);
	rep(i,1,n)  cin>>s[i];
	sort(s+1,s+1+n);
	rep(i,2,n) height[i]=LCP(i,i-1);
	rep(i,2,n){
		while(top&&height[i]<height[st[top]]) ls[i]=st[top--];
		if(top) rs[st[top]]=i;
		st[++top]=i;
	}
	dfs(st[1],1,n);
	write(f[st[1]][k],'\n');
	return 0;
}
```

---

## 作者：Angraecum (赞：2)

实在是啥都不想干了，遂来补篇题解。这篇题解是暴力 dp 草过去的，只能说数据可能比较水。

------------

求两两串间最大 LCP 长度之和，考虑先建出 trie 树。画出 trie 树后可以发现，两串的 LCP 长度就是两串结尾节点的 LCA 的深度。

考虑朴素的树上背包：设 $dp[i][j]$ 表示在 $i$ 子树内选 $j$ 个节点，也就是选 $j$ 个串的最大 LCP 之和。转移：$dp[u][i]=\max(dp[u][i],\sum\limits_j dp[u][j]+dp[v][i-j]+i\times(i-j)\times dept[u])$。

但是因为 trie 的节点很多，所以直接用 dp 数组是存不下的。因为笔者菜，所以这里提供一种不需要任何其他算法的优化方案：我们发现做背包的时候发现 dp 过程中用到的点很少，所以考虑开一个 $id$ 数组用于映射 dp 时要用到的点的编号。具体维护可以开一个栈，先把所有编号扔进去，有新的点时就把栈顶编号拿出来，用完了再退回去。这样空间的问题就解决了，具体实现可以参考代码。

这样子时间复杂度是 $O(n^2|a_i|)$ 的，最高要算 $2e9$ 次，但是 $2s$ 过了，很离谱，而且最大点刚好跑了 $2s$，大抵是数据水了。和 NATO 一起喜提最劣解，确实挺不错的。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll int
const ll N=1145140,M=1919810,mod=1e9+7;
ll n,k,siz[N],f[N],ans;
string st;
ll t[N][26],tot;
ll dp[1145][2005];
void build(string s){
	ll rt=0;
	++siz[rt];
	for(int i=0;i<s.size();++i){
		ll nex=s[i]-'a';
		if(!t[rt][nex]) t[rt][nex]=++tot;
		rt=t[rt][nex];
		++siz[rt];
	}
	++f[rt];
}
stack <ll> s;
ll id[N],cnt;
void dfs(ll u,ll dept){
	ll si=0;
	id[u]=s.top(),s.pop();
	for(int i=0;i<26;++i)
		if(t[u][i]){
			dfs(t[u][i],dept+1);
			si+=siz[t[u][i]];
			for(int j=si;j>=0;--j)
				for(int k=min(j,siz[t[u][i]]);k>=0;--k)
					dp[id[u]][j]=max(dp[id[u]][j],dp[id[u]][j-k]+dp[id[t[u][i]]][k]+(j-k)*k*dept);
			for(int j=siz[t[u][i]];j>=0;--j) dp[id[t[u][i]]][j]=0;
			s.push(id[t[u][i]]);
		}
	si+=f[u];
	for(int i=si;i>=0;--i)
		for(int j=min(i,f[u]);j>=0;--j)
			dp[id[u]][i]=max(dp[id[u]][i],dp[id[u]][i-j]+(i-j)*j*dept+j*(j-1)/2*dept);
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin>>n>>k;
	for(int i=1;i<=n;++i) cin>>st,build(st);
	for(int i=1;i<=614;++i) s.push(i);
	dfs(0,0);
	cout<<dp[id[0]][k];
	return 0;
}//你说得对，但是因为我菜，所以我也选择O(n^2|a|)
```

---

## 作者：wosile (赞：2)

题意略。Duel 到这道题写了 45 分钟被暴打了。

让求 LCP，就建一棵 Trie 好了。

既然要选 $k$ 个字符串求最大值，很明显我们应该在 Trie 上跑树上背包。对于 Trie 的一条边而言，如果我们选择的字符串中有 $x$ 个在 Trie 上经过了这条边，那么这条边就会产生 $\frac{x(x-1)}{2}$ 的贡献。

直接背包的时间复杂度似乎是 $O(k\sum|a_i|)$ 的，但借用虚树的思想，只有一个孩子的节点我们可以很简单的处理它的答案。从而实际需要计算的节点只有 $O(n)$ 个，时间复杂度是 $O(kn)$。代码里使用了 `tag[i]` 记录虚点 $i$ 到当前位置的深度，在需要用到 $i$ 点的 dp 值的时候用 `tag[i]` 更新 dp 值即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
string s[2005];
int n,K;
int tr[1000005][30],buc[1000005],tot=0;
int f[4005][2005],sz[4005],tag[4005],id[1000005];
void upd(int v){
	for(int i=0;i<=sz[v];i++)f[v][i]+=tag[v]*(i-1)*i/2;
	tag[v]=0;
}
int main(){
	cin>>n>>K;
	for(int i=0;i<n;i++)cin>>s[i];
	for(int i=0;i<n;i++){
		int cur=0;
		for(int j=0;j<(int)s[i].size();j++){
			if(tr[cur][s[i][j]-'a']==0)tr[cur][s[i][j]-'a']=++tot;
			cur=tr[cur][s[i][j]-'a'];
		}
		buc[cur]++;
	}
	int qwq=0;
	for(int i=tot;i>=0;i--){
		int cnt=0,son=0;
		for(int j=0;j<26;j++)if(tr[i][j]){
			++cnt,++tag[id[tr[i][j]]];
			son=tr[i][j];
		}
		if(cnt==0)id[i]=++qwq;
		else if(cnt==1)id[i]=id[son];
		else{
			id[i]=++qwq;
			for(int j=0;j<26;j++)if(tr[i][j]){
				int v=id[tr[i][j]];
				upd(v);
				for(int k=sz[qwq];k>=0;k--)for(int l=0;l<=sz[v];l++)f[qwq][k+l]=max(f[qwq][k+l],f[qwq][k]+f[v][l]);
				sz[qwq]+=sz[v];
			}
		}
		if(buc[i]>0){
			upd(id[i]);
			for(int j=sz[id[i]];j<sz[id[i]]+buc[i];j++)f[id[i]][j+1]=max(f[id[i]][j+1],f[id[i]][j]);
			sz[id[i]]+=buc[i];
		}
	}
	for(int i=0;i<=n;i++)f[qwq][i]+=tag[qwq]*i*(i-1)/2;
	printf("%d",f[qwq][K]);
	return 0;
}
```

---

## 作者：Purslane (赞：1)

# Solution

考虑直接在 Trie 树上进行树上背包，差不多可以获得 $O(k \sum|len|+n^2)$ 的做法。过不了。

然后你发现瓶颈是前者。那么建出虚树，就可以做到 $O(n^2)$ 了。

代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=4000+10,MAXM=1e6+10;
int n,k,tot,al,dep[MAXM],id[MAXM],cnt[MAXM],tr[MAXM][27],flg[MAXM],sze[MAXM];
ll dp[MAXN][MAXN];
vector<int> T[MAXN];
void insert(string S) {
	int u=0;
	for(auto ch:S) {
		if(tr[u][ch-'a']==0) tr[u][ch-'a']=++tot,dep[tot]=dep[u]+1;
		u=tr[u][ch-'a'];
	}
	return cnt[u]++,void();	
}
void build(int u,int f) {
	if(f!=-1&&flg[u]) T[id[f]].push_back(u);
	if(flg[u]) f=u,id[u]=++al;
	ffor(i,0,25) {
		int v=tr[u][i];
		if(v) build(v,f);
	}
	return ;
}
ll f[MAXM];
void dfs(int u) {
	memset(dp[id[u]],-0x3f,sizeof(dp[id[u]]));
	ffor(i,0,cnt[u]) dp[id[u]][i]=i*(i-1)/2*dep[u];
	sze[u]=cnt[u];
	for(auto v:T[id[u]]) {
		dfs(v);
		ffor(i,0,sze[u]+sze[v]) f[i]=-0x3f3f3f3f3f3f3f3f;
		ffor(i,0,sze[v]) ffor(j,0,sze[u]) f[i+j]=max(f[i+j],dp[id[v]][i]+dp[id[u]][j]+i*j*dep[u]);
		ffor(i,0,sze[u]+sze[v]) dp[id[u]][i]=f[i];
		sze[u]+=sze[v];
	}
	return ;
}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>k;
	ffor(i,1,n) {string S;cin>>S;insert(S);}
	flg[0]=1;
	ffor(i,0,tot) {
		if(cnt[i]) flg[i]=1;
		else {
			int cnt=0;
			ffor(j,0,25) if(tr[i][j]) cnt++;
			if(cnt>=2) flg[i]=1;
		}
	}
	build(0,-1);
	dfs(0);
	cout<<dp[id[0]][k];
	return 0;	
}
```

---

## 作者：ningago (赞：1)

求两两整个串的 LCP，考虑建立 Trie 树。显然两串的 LCP 长度即为两结尾节点的 LCA 深度。

使用树上背包算法，记 $dp(k,i)$ 表示 $k$ 子树内选了 $k$ 个的最大和。

令 $a_k$ 表示 $k$ 节点是多少个串的结尾节点。则初始状态为：

$$\forall 0\leq i\leq a_k,dp(k,\dfrac{i\cdot (i-1)}{2}\cdot dep_{k})=1$$

考虑合并父亲 $k$ 与儿子 $nx$ 的过程，即：

$$dp(k,i+j)\leftarrow dp(k,i)+dp(nx,j)+i\cdot j\cdot dep_{k}$$

复杂度为 $O(n|s_i|m)$。

注意到树上背包只会在结尾节点的 LCA 处产生贡献，而 Trie 树上插入一个串只会开辟至多一条新链，即产生 $O(1)$ 个可能的 LCA。

故可将 $a_k=0$ 且 $|son_k|=1$ 的节点删去。保留下的节点数为 $O(n)$。

复杂度 $O(nm)$。

https://www.luogu.com.cn/paste/nxhobtsp

---

## 作者：Priestess_SLG (赞：0)

一道很恶心的题。

[![pEEXXTS.png](https://s21.ax1x.com/2025/01/26/pEEXXTS.png)](https://imgse.com/i/pEEXXTS)

（不过至少算是独立切了对吧）

### F1

Data Range: $n\le 20,|s|\le 500$。

和 F2，F3 的关系不大。考虑设 $f_{i}$ 表示选择了 $i$ 集合内的字符串，这些字符串两两 lcp 的值最大是多少。那么显然有转移：

$$f_{i\text{ with }j}\leftarrow f_i+\sum\limits_{k\text{ in }i}\text{lcp}(s_k,s_j)$$

暴力预处理出后面的字符串两两 lcp，时间复杂度为 $O(2^nn^2)$，极限卡常后应该可以过。代码没写。

### F2

Data Range: $n\le 100,|s|\le 500$。

看上去必须用时间复杂度在多项式级别的做法来搞了。考虑对所有字符串建一棵 Trie 树，那么假设一条边在 $k$ 个叶子结点到根节点的简单路径上，那么这条边对答案产生了 $\dfrac{k(k-1)}{2}$ 的贡献。

于是考虑在 Trie 上搞一个树上背包。设 $f_{i,j}$ 表示 $i$ 为根的子树内，最少选择多少个结点。那么显然有下面的转移：

+ 对于一个结点 $p$，若 $p$ 是某一个串的结尾。那么若 $p$ 点处有 $x$ 个字符串结尾，则 $f_{p,i}=0$ 当且仅当 $0\le i\le x$。为了方便处理可以在 $p$ 后面连一个虚点并在这个虚点上处理 dp 信息。
+ 对于一个非叶子结点 $p$，根据上面的处理方式不需要处理某一个串结尾的情况。于是设 $S$ 集合为 $p$ 所有儿子结点组成的点集，那么依次对每个 $x\in S$，设 $siz_x$ 表示 $x$ 的子树内有多少个字符串的结尾（这个部分可以一遍 dfs 求出），则枚举 $x$ 之前选择了多少个串，在 $x$ 的子树中选择了多少个串，合并信息即可。为了避免重复计算答案，这个地方可以开两个数组 $f,g$，用 $g$ 来合并，最后再将信息 copy 回 $f$ 中。

显然答案就是 $f_{1,m}$。此时可以通过 F2。

```cpp
#pragma GCC optimize(3, "Ofast", "inline")
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 110, M = N * 510;
using ull = unsigned long long;
int a[N];
int n, m;
struct Node {
    signed child[26], cnt;
    Node() {
        memset(child, 0, sizeof child);
        cnt = 0;
    }
} tree[M];
int idx = 1;
void ins(string s) {
    int p = 1;
    for (auto &i : s) {
        int j = i - 'a';
        if (!tree[p].child[j]) tree[p].child[j] = ++idx;
        p = tree[p].child[j];
    }
    ++tree[p].cnt;
}
vector<int> adj[M];
int f[M][110], g[110];
signed siz[M];
int vis[M];
// f[i][j]: i 子树内选择 j 个结点，贡献最大是多少
void dfs(int u, int fa) {
    siz[u] = vis[u];
    for (int &v : adj[u])
        if (v != fa) dfs(v, u), siz[u] += siz[v];
}
int pidx;
void dfs2(int u, int fa) {
    int now = vis[u], son = 0;
    for (int j = 0; j <= vis[u]; ++j) f[u][j] = 0;
    for (int &v : adj[u])
        if (v != fa) {
            ++son;
            dfs2(v, u);
            now += siz[v];
            for (int bk = 0; bk <= min(m, now - siz[v]); ++bk) {
                for (int nw = 1; nw <= min(m, (int)siz[v]) && bk + nw <= m; ++nw) {
                    int val = nw * (nw - 1) / 2 + f[v][nw];
                    if (v <= pidx)
                        g[bk + nw] = max({g[bk + nw], f[u][bk + nw], f[u][bk] + val});
                    else
                        g[bk + nw] = max({g[bk + nw], f[u][bk + nw], f[u][bk]});
                }
            }
            for (int i = 0; i <= m; ++i) f[u][i] = max(f[u][i], g[i]);
            for (int i = 0; i <= m; ++i) g[i] = -1e18;
        }
}
signed main() {
    cin.tie(0)->sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        string s;
        cin >> s;
        ins(s);
    }
    pidx = idx;
    for (int i = 1; i <= idx; ++i) {
        for (int j = 0; j < 26; ++j)
            if (tree[i].child[j]) {
                int k = tree[i].child[j];
                adj[i].emplace_back(k);
                adj[k].emplace_back(i);
            }
        if (tree[i].cnt) {
            int key = ++idx;
            vis[key] = tree[i].cnt;
            adj[i].emplace_back(key);
            adj[key].emplace_back(i);
        }
    }
    memset(f, -0x3f, sizeof f);
    memset(g, -0x3f, sizeof g);
    dfs(1, 0);
    dfs2(1, 0);
    cout << f[1][m] << '\n';
    return 0;
}
```

### F3

考虑到 Trie 树中结点的数量是 $O(n\times |s_i|)$ 级别的，而在 F3 中 $n$ 可以取到 $2000$，$|s_i|$ 可以取到 $500$，乘起来是 $10^6$ 个结点。而 dp 的时候又需要枚举到 $m$ 个选中的串，时间复杂度为 $O(nm|s_i|)$ 过不去。考虑优化。可以发现 Trie 树中大部分结点都不是串的结尾，而且只有一个儿子结点合并信息。显然每一次计算它的信息很浪费，因此考虑用虚树的思想，建立一个新的树，在这个新树中将每一条链合并为一条边，此时需要对每一条边记录边权表示这条边其实是由多少条边合并而成的。此时结点的数目大大减少，只需要对点、边的编号离散化减少 dp 的信息量即可。

需要计算信息的上界并卡一下空间。

```cpp
#pragma GCC optimize(3, "Ofast", "inline")
#include <bits/stdc++.h>
#define int long long
using namespace std;
bool beginmem;
const int N = 2004, M = N * 502;
using ull = unsigned long long;
int a[N];
int n, m;
struct Node {
    signed child[27], cnt;
    Node() {
        memset(child, 0, sizeof child);
        cnt = 0;
    }
} tree[M];
int idx = 1;
void ins(string s) {
    int p = 1;
    for (auto &i : s) {
        int j = i - 'a';
        if (!tree[p].child[j]) tree[p].child[j] = ++idx;
        p = tree[p].child[j];
    }
    ++tree[p].cnt;
}
vector<pair<int, int>> adj[N * 5];
signed f[16190][2010], g[2010];
signed siz[M], vis[M];
// f[i][j]: i 子树内选择 j 个结点，贡献最大是多少
void dfs(int u, int fa) {
    siz[u] = vis[u];
    for (auto &[v, w] : adj[u])
        if (v != fa) dfs(v, u), siz[u] += siz[v];
}
int pidx;
void dfs2(int u, int fa) {
    int now = vis[u], son = 0;
    for (int j = 0; j <= vis[u]; ++j) f[u][j] = 0;
    for (auto &[v, w] : adj[u])
        if (v != fa) {
            ++son;
            dfs2(v, u);
            now += siz[v];
            for (int bk = 0; bk <= min(m, now - siz[v]); ++bk) {
                for (int nw = 1; nw <= min(m, (int)siz[v]) && bk + nw <= m; ++nw) {
                    int val = nw * (nw - 1) / 2 * w + f[v][nw];
                    if (v <= pidx)
                        g[bk + nw] = max({g[bk + nw], f[u][bk + nw], f[u][bk] + (signed)val});
                    else
                        g[bk + nw] = max({g[bk + nw], f[u][bk + nw], f[u][bk]});
                }
            }
            for (int i = 0; i <= m; ++i) f[u][i] = max(f[u][i], g[i]);
            for (int i = 0; i <= m; ++i) g[i] = -1e18;
        }
}
signed to[M + N * 5];
void dfs3(int u, int len, int last) {
    int ch_cnt = 0;
    for (int i = 0; i < 26; ++i)
        if (tree[u].child[i]) ++ch_cnt;
    if (ch_cnt > 1 || u == 1 || tree[u].child[26] || tree[u].cnt) {
        if (u != last) adj[to[last]].emplace_back(to[u], len - 1);
        for (int i = 0; i < 26; ++i)
            if (tree[u].child[i]) {
                adj[to[u]].emplace_back(to[tree[u].child[i]], 1);
                dfs3(tree[u].child[i], 1, tree[u].child[i]);
            }
    } else if (ch_cnt == 1) {
        for (int i = 0; i < 26; ++i)
            if (tree[u].child[i])
                dfs3(tree[u].child[i], len + 1, last);
    } else {
        if (u != last) adj[to[last]].emplace_back(to[u], len - 1);
    }
}
vector<signed> useful;
void dfs4(int u, int len, int last) {
    int ch_cnt = 0;
    for (int i = 0; i < 26; ++i)
        if (tree[u].child[i]) ++ch_cnt;
    if (ch_cnt > 1 || u == 1 || tree[u].cnt) {
        if (u != last) {
            if (last) useful.emplace_back(last);
            useful.emplace_back(u);
        }
        for (int i = 0; i < 26; ++i)
            if (tree[u].child[i]) {
                useful.emplace_back(u);
                useful.emplace_back(tree[u].child[i]);
                dfs4(tree[u].child[i], 1, tree[u].child[i]);
            }
    } else if (ch_cnt == 1) {
        for (int i = 0; i < 26; ++i)
            if (tree[u].child[i])
                dfs4(tree[u].child[i], len + 1, last);
    } else {
        if (u != last) {
            if (last) useful.emplace_back(last);
            useful.emplace_back(u);
        }
    }
}
bool endmem;
signed main() {
    cin.tie(0)->sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        string s;
        cin >> s;
        ins(s);
    }
    dfs4(1, 1, 0);
    for (int i = 1; i <= idx; ++i)
        if (tree[i].cnt) useful.emplace_back(i);
    sort(useful.begin(), useful.end());
    useful.erase(unique(useful.begin(), useful.end()), useful.end());
    int index = 0;
    for (signed &i : useful) to[i] = ++index;
    pidx = index;
    for (int i = 1; i <= idx; ++i) {
        if (tree[i].cnt) {
            int key = ++index;
            vis[key] = tree[i].cnt;
            adj[to[i]].emplace_back(key, 1ll);
            assert(key);
            tree[i].child[26] = 1;
        }
    }
    dfs3(1, 1, 0);
    memset(f, -0x3f, sizeof f);
    memset(g, -0x3f, sizeof g);
    dfs(1, 0);
    dfs2(1, 0);
    cout << f[1][m] << '\n';
    cerr << "Memory used " << (&beginmem - &endmem) / 1048576. << '\n';
    return 0;
}
```

---

## 作者：lfxxx (赞：0)

简单题，这里给一种不依赖字典序特性的解法，考虑设计状态 $dp_{u,i}$ 表示考虑以点 $u$ 为根的子树，这个子树中选了 $i$ 个字符串的贡献。

显然转移是一个背包形式的 $\max +$ 卷积，由于 dp 第二维最大是子树单词节点数量，所以用上界优化后是 $O(n^2)$ 的，转移方程是简单的：$dp_{u,i} \gets \sum_{j} dp_{u,j} + dp_{v,i-j} + i \times (i-j) \times dep_u$。

不过你发现一个很不好的东西，你的空间是 $O(n^2 |S_i|)$ 的，直接爆了。

考虑重剖优化空间，具体来说只给需要正在处理的节点分配 dp 数组编号，在执行对点 $u$ 的 dp 时，进行以下步骤：

1. 找出重儿子 $hson$。

2. 对重儿子进行 dp，并在其结束后将数组合并到 $u$ 上，继承重儿子的 dp 数组编号。

3. 对轻儿子进行 dp。合并后回收轻儿子 dp 数组编号。因为在这之后不会再用到。

4. 结束时如果点 $u$ 是一个单词节点则分配一个编号。

不难发现这样做在进行对点 $u$ 的 dp 时存在的 dp 数组是被点 $u$ 到根的路径上所有切换轻重链的节点的父亲（在重链上）所占用，根据重剖的结论，这样的点至多有 $\log n$ 个，因此这么做空间就被优化到了 $O(n \log n + n \log |S_i|)$ 而时间还是 $O(n |S_i| + n^2)$ 的。

```cpp
#include<bits/stdc++.h>
using namespace std;
const long long inf = 1e18+114;
const int maxn = 1e6+114;
const int maxlg = 25;
int cnt[maxn],sz[maxn],dep[maxn];
long long dp[maxlg][2014];
int pos[maxn],node[maxn];
int n,rt,tot,K;
int C;
int son[maxn][26];
void ins(string s){
    int u=rt;
    for(char c:s){
        sz[u]++;
        if(son[u][c-'a']==0) son[u][c-'a']=++tot;
        u=son[u][c-'a'];
    }
    cnt[u]++;
    sz[u]++;
    return ;
}
void dfs(int u){
    int hson=0;
    for(int i=0;i<26;i++) if(sz[son[u][i]]>sz[hson]) hson=son[u][i];
    if(hson!=0){
        dep[hson]=dep[u]+1;
        dfs(hson);
        pos[u]=pos[hson];
        node[pos[u]]=u;
    }
    for(int i=0;i<26;i++){
        if(son[u][i]==hson) continue;
        if(son[u][i]==0) continue;
        dep[son[u][i]]=dep[u]+1;
        int lst=C;
        dfs(son[u][i]);
        for(int j=sz[u]-sz[son[u][i]];j>=0;j--)
            for(int k=sz[son[u][i]];k>=0;k--) dp[pos[u]][j+k]=max(dp[pos[u]][j+k],dp[pos[u]][j]+dp[pos[son[u][i]]][k]+1ll*j*k*dep[u]);
        //轻儿子使用完就全部回收
        for(int j=lst+1;j<=C;j++){
            for(int k=1;k<=sz[node[j]];k++) dp[j][k]=-inf;
            dp[j][0]=0;
        }
        C=lst;
    }
    if(pos[u]==0&&cnt[u]>0) pos[u]=++C,node[C]=u;
    for(int i=sz[u]-cnt[u];i>=0;i--){
        for(int j=cnt[u];j>=0;j--) dp[pos[u]][i+j]=max(dp[pos[u]][i+j],dp[pos[u]][i]+1ll*j*(j-1)/2*dep[u]+1ll*i*j*dep[u]);
    }
}
int main(){
    cin>>n>>K;
    rt=++tot;
    for(int i=1;i<=n;i++){
        string s;
        cin>>s;
        ins(s);
    }
    dfs(rt);
    cout<<dp[pos[rt]][K]<<'\n';
    return 0;
}
```

---

## 作者：TernaryTree (赞：0)

先考虑简单做法。即在 trie 树上给定的 $n$ 个结点（可重）中选出 $k$ 个是的两两 $\operatorname{lca}$ 的深度之和最大。使用树上背包 dp 解决。令 $f_{u, i,j}$ 表示 $u$ 为根的前 $i$ 个子树内选了 $j$ 个关键点的答案。则

$$f_{u,i,j}=\max_{t=0}^{\min(siz_v,k)}f_{u,i-1,j-t}+f_{v,t}+(j-t)\cdot t\cdot dep_u$$

因为前面 $i-1$ 个子树内的 $j-t$ 个点与当前子树的 $t$ 个点两两配对的 $\operatorname{lca}$ 都是 $u$，所以会对答案有 $(j-t)\cdot t\cdot dep_u$ 的贡献。

最后还要考虑 $u$ 可选，并且 $u$ 选了自己的情况。此时假设 $u$ 选了 $t$ 个点，则 $u$ 子树内除了自己一共选了 $j-t$ 个点。$j-t$ 个点的贡献是刚刚不考虑选 $u$ 的结果，$t$ 个点两两会产生 $dep_u$ 的贡献，即 $\dfrac12t(t-1)\cdot dep_u$，而 $j-t$ 个点与 $t$ 个点之间两两也会产生共 $(j-t)\cdot t\cdot dep_u$ 的贡献。再对自己背包一次即可。

然后把第二维滚动数组滚掉，注意顺序问题。

[这份代码](https://www.luogu.com.cn/paste/swqbo7gn)可以通过此题简单版 [F2](https://www.luogu.com.cn/problem/CF178F2)。

思考如何优化。注意到对于刚才的做法，点数是 $\Theta(n|S|)$ 的，而 trie 上却有很多点是没用的。它们只有一个儿子，会完整地继承儿子的 dp 数组。这些点是没用的。而哪些点是有用的呢，是可能成为两个关键点的 $\operatorname{lca}$ 的点或自己就是关键点的点。这里用到虚树的思想，可以证明有用的点是 $\Theta(n)$ 的。

先把所有关键点钦定出来，接着对这些关键点建虚树，在虚树上做一样的 dp 就行了。

[有点繁琐的代码。](https://www.luogu.com.cn/paste/a8r99anl)

---

