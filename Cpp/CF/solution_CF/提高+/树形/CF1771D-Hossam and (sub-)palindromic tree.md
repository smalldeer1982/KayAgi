# Hossam and (sub-)palindromic tree

## 题目描述

Hossam has an unweighted tree $ G $ with letters in vertices.

Hossam defines $ s(v, \, u) $ as a string that is obtained by writing down all the letters on the unique simple path from the vertex $ v $ to the vertex $ u $ in the tree $ G $ .

A string $ a $ is a subsequence of a string $ s $ if $ a $ can be obtained from $ s $ by deletion of several (possibly, zero) letters. For example, "dores", "cf", and "for" are subsequences of "codeforces", while "decor" and "fork" are not.

A palindrome is a string that reads the same from left to right and from right to left. For example, "abacaba" is a palindrome, but "abac" is not.

Hossam defines a sub-palindrome of a string $ s $ as a subsequence of $ s $ , that is a palindrome. For example, "k", "abba" and "abhba" are sub-palindromes of the string "abhbka", but "abka" and "cat" are not.

Hossam defines a maximal sub-palindrome of a string $ s $ as a sub-palindrome of $ s $ , which has the maximal length among all sub-palindromes of $ s $ . For example, "abhbka" has only one maximal sub-palindrome — "abhba". But it may also be that the string has several maximum sub-palindromes: the string "abcd" has $ 4 $ maximum sub-palindromes.

Help Hossam find the length of the longest maximal sub-palindrome among all $ s(v, \, u) $ in the tree $ G $ .

Note that the sub-palindrome is a subsequence, not a substring.

## 说明/提示

In the first example the maximal subpalindromes are "aaa" with letters in vertices $ 1, \, 3, \, 5 $ , or "aca" with letters in vertices $ 1, \, 4, \, 5 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1771D/2a7d49fbfdc47b629dbea5a5d05163d26e820257.png) The tree from the first example.In the second example there is only one maximal palindrome "bacab" with letters in vertices $ 4, \, 2, \, 1, \, 5, \, 9 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1771D/1a3ef86962248c5a486bd8acba156707a2fa8aec.png) The tree from the second example.

## 样例 #1

### 输入

```
2
5
abaca
1 2
1 3
3 4
4 5
9
caabadedb
1 2
2 3
2 4
1 5
5 6
5 7
5 8
8 9```

### 输出

```
3
5```

# 题解

## 作者：include_BM (赞：11)

先考虑序列上的情况，设 $f(l,r)$ 表示 $s_{l\dots r}$ 的最长回文子序列长度，考虑 $l,r$ 位置上的字符，可得到转移方程：

$$f(l,r)=\max\{f(l+1,r),f(l,r-1),f(l+1,r-1)+2[s_l=s_r]\}$$

将这个东西转移到树上，即设 $f(x,y)$ 表示 $x,y$ 路径构成的最长回文子序列长度，$fa(x,y)$ 表示以 $x$ 为根时 $y$ 的父亲，可得转移方程：

$$f(x,y)=\max\{f(fa(y,x),y),f(x,fa(x,y)),f(fa(y,x),fa(x,y))+2[s_x=s_y]\}$$

最终答案即为 $\max_{x,y}f(x,y)$，可以写记忆化搜索，可能需要注意一些细节。

```cpp
const int N=2e3+10;
int n,mx[N][N],ans,fa[N][N]; char s[N]; vector<int> E[N];

void dfs(int x,int fa,int root){
    ::fa[root][x]=fa;
    for(auto y:E[x]) if(y!=fa) dfs(y,x,root);
}

int calc(int x,int y){
    if(x==y) return 1;
    if(x==fa[1][y]||y==fa[1][x]) return 1+(s[x]==s[y]); // 特判相邻的点。
    if(mx[x][y]) return mx[x][y];
    return mx[x][y]=max({calc(x,fa[x][y]),calc(y,fa[y][x]),calc(fa[x][y],fa[y][x])+(s[x]==s[y]?2:0)});
}

signed main(){
    for(int T=read();T;--T){
        n=read(),scanf("%s",s+1),ans=0;
        for(int i=1;i<=n;++i) for(int j=1;j<=n;++j) mx[i][j]=0;
        for(int i=1;i<=n;++i) E[i].clear();
        for(int u,v,i=1;i<n;++i){
            u=read(),v=read();
            E[u].emplace_back(v),E[v].emplace_back(u);
        }
        for(int i=1;i<=n;++i) dfs(i,0,i);
        for(int i=1;i<=n;++i) for(int j=1;j<=n;++j) ans=max(ans,calc(i,j));
        printf("%d\n",ans);
    }
    return 0;
}
```

---

## 作者：StayAlone (赞：5)

$f_{l, r}$ 表示点 $l$ 到点 $r$ 的路径上的答案。为了方便转移，记 $pa_{r, x}$ 表示以 $r$ 为根时，$x$ 的父亲；$d_{r, x}$ 表示以 $r$ 为根时，$x$ 的深度。

考虑记搜。

显然有 $f_{l, r} = \max\{f_{pa_{y, x}, y}, f_{x, pa_{x, y}},f_{pa_{y, x}, pa_{x, y}} + 2\times[s_x = s_y]\}$。

边界：
- $f_{x,y} = 1(d_{x, y}=1)$
- $f_{x,y} = 1 + [s_x=s_y](d_{x, y}=2)$

状态数 $n^2$，转移 $\Theta(1)$。

[AC code record](https://www.luogu.com.cn/record/97901434)

```cpp
int n, pa[2010][2010], f[2010][2010], d[2010][2010]; vector <int> lnk[2010];
char s[2010];

il void add(const int &x, const int &y) {
	lnk[x].eb(y); lnk[y].eb(x);
}

il void dfs(int rt, int x, int p) {
	pa[rt][x] = p; d[rt][x] = d[rt][p] + 1;
	for (auto v : lnk[x]) if (v ^ p) dfs(rt, v, x);
}

il int dp(int x, int y) {
	if (~f[x][y]) return f[x][y];
	if (d[x][y] == 1) return f[x][y] = 1;
	if (d[x][y] == 2) return f[x][y] = (s[x] == s[y]) + 1;
	return f[x][y] = max({dp(pa[y][x], y), dp(x, pa[x][y]), dp(pa[y][x], pa[x][y]) + 2 * (s[x] == s[y])});
}

int main() {
	for (int T = read(); T--; ) {
		read(n); scanf("%s", s + 1);
		rep1(i, 2, n) add(read(), read());
		rep1(i, 1, n) rep1(j, 1, n) f[i][j] = -1;
		rep1(i, 1, n) dfs(i, i, 0);
		int ans = 0;
		rep1(i, 1, n) rep1(j, 1, n) ans = max(ans, dp(i, j));
		printf("%d\n", ans);
		rep1(i, 1, n) lnk[i].clear();
		rep1(i, 1, n) rep1(j, 1, n) pa[i][j] = f[i][j] = 0;
	}
	rout;
}
```


---

## 作者：Polaris_Australis_ (赞：3)

考虑放在序列上做：设 $dp_{l,r}$ 表示 $[l,r]$ 这个区间的最长回文子序列。

$$
dp_{i,r}=\max(dp_{l+1,r},dp_{l,r-1},dp_{l+1,r-1}+2\times[s_l==s_r])
$$

放到树上，直接按照路径长度从小到大枚举点对转移，预处理或倍增找到路径上的相邻点，转移和序列上一样。

代码：

```cpp
#include<bits/stdc++.h>
#define pb push_back
#define mk make_pair
using namespace std;
namespace Std{
void gi(int &x){
	x=0;
	int y=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')y=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=(x<<1)+(x<<3)+(c&15);
		c=getchar();
	}
	x*=y;
}
int T,n,f[2010][2010],dep[2010],fa[2010][12];
vector<int>e[2010];
vector<pair<int,int> >vec[2010];
char s[2010];
void dfs(int x){
	for(auto i:e[x]){
		if(i==fa[x][0])continue;
		fa[i][0]=x;
		dep[i]=dep[x]+1;
		dfs(i);
	}
}
int lca(int x,int y){
	if(dep[x]<dep[y])swap(x,y);
	for(int i(11);~i;--i){
		if(dep[fa[x][i]]<dep[y])continue;
		x=fa[x][i];
	}
	if(x==y)return x;
	for(int i(11);~i;--i){
		if(fa[x][i]==fa[y][i])continue;
		x=fa[x][i],y=fa[y][i];
	}
	x=fa[x][0];
	return x;
}
int jp(int x,int y){
	for(int i(11);~i;--i){
		if(dep[fa[x][i]]<y)continue;
		x=fa[x][i];
	}
	return x;
}
void solve(){
	gi(n);
	dep[1]=1;
	scanf("%s",s+1);
	int u,v;
	for(int i(1);i<n;++i){
		gi(u);
		gi(v);
		e[u].pb(v);
		e[v].pb(u);
	}
	dfs(1);
	for(int i(1);i<=11;++i){
		for(int j(1);j<=n;++j)fa[j][i]=fa[fa[j][i-1]][i-1];
	}
	int ans(1);
	for(int i(1);i<=n;++i){
		f[i][i]=1;
		for(int j(i+1);j<=n;++j){
			int lc=lca(i,j);
			int ds=dep[i]+dep[j]-dep[lc]*2;
			if(ds==1){f[i][j]=1+(s[i]==s[j]);ans=max(ans,f[i][j]);}
			else vec[ds].pb(mk(i,j));
		}
	}
	for(int i(2);i<n;++i){
		for(auto j:vec[i]){
			int u=j.first,v=j.second;
			int lc=lca(u,v);
			if(dep[u]<dep[v])swap(u,v);
			int lj,rj;
			if(v==lc){
				lj=fa[u][0],rj=jp(u,dep[v]+1);
			}else{
				lj=fa[u][0],rj=fa[v][0];
			}
			f[min(u,v)][max(u,v)]=max(max(f[min(u,rj)][max(u,rj)],f[min(v,lj)][max(v,lj)]),f[min(lj,rj)][max(lj,rj)]+2*(s[u]==s[v]));
			ans=max(ans,f[min(u,v)][max(u,v)]);
		}
		vec[i].clear();
	}
	printf("%d\n",ans);
	for(int i(1);i<=n;++i)e[i].clear();
}
void main(){
	gi(T);
	while(T--)solve();
}
}  // namespace Std
#undef int
int main(){
	Std::main();
	return 0;
}
```


---

## 作者：MSqwq (赞：3)

典典可爱题，挺喜欢的。  


------------
题意：  
给出一棵树，每个点是一个字符，求树上最长回文子序列（LPS）的长度。  


------------
题解：  
首先你得知道，正常的最长回文子序列咋算，再搬到树上。  
其实本质就是个区间 dp，设 $dp_{i,j}$ 表示 $i$ 到 $j$ 的最长回文子序列。  
那么当 $a_i=a_j$ 的时候，相当于加长了两个，可以转移 $dp_{i,j}=dp_{i+1,j-1}+2$ ，反之就是 $dp_{i,j}=max(dp_{i+1,j},dp_{i,j-1})$，更具体的初始 $dp_{i,i}=1$。  
那么怎么搬到树上呢。  
我们不妨设 $i$ 和 $j$ 就是树上的某两个节点，接下来我们就是要找 $i+1$ 和 $j-1$ 了，随便画颗树模拟一下，你就发现，这不就是 $i$ 的父亲节点嘛。那么转移就是在 $(x,fa[y])$，$(fa[x],y)$，$(fa[x],fa[y])$ 转移啦。  
记忆化一下就好了可以 $n^2$  
当然特殊的我们需要特判一下他们的 $lca$ 在是他们的其中一个，比如我随便画了一个图啊（  
![](https://3wt.img.zlkj.icu/2022/12-12/3728183af3b149e1885ae3605f6828083wcn351256.jpeg)  
如果我们更新到 $i = 2$ $j = 4$ 了嗷。这个时候再 $fa[i]$ 就到 $5$ 了，但实际跟 $5$ 没有半毛钱关系。所以要特殊处理一下，可以倍增找到还差一个点就到 $i$ 的那个点，然后和前面一样的更新就好了。  
最后注意一下多测清空吧，其他的就没了。   
最后代码：  
```
#include<cstdio>
#include<cstring>
#include<stdlib.h>
#include<algorithm>
#include<iostream>
#include<vector>
#include<set>
#include<string>
#include<map>
#include<queue>
#include<stack>
#include<math.h>
#define ll long long
using namespace std;
const int mod=1e9+7;
const int INF=0x3f3f3f3f;

inline int read()
{
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0',c=getchar();}
	return x*f;
}
const int N=5e3+10;
struct qwq{
	int to,ne;
}e[N];
int elast[N],num;
void add(int from,int to)
{
	e[++num]={to,elast[from]};
	elast[from]=num;
}
int lg[N],dep[N],f[N][30];

void dfs(int x,int fa)
{
	f[x][0]=fa,dep[x]=dep[fa]+1;
	for(int i=1;i<=lg[dep[x]];i++)
		f[x][i]=f[f[x][i-1]][i-1];
	
	for(int i=elast[x];i;i=e[i].ne)
	{
		int to=e[i].to;
		if(to!=fa)dfs(to,x);
	}
}
int LCA(int x,int y)
{
	if(dep[x]<dep[y])swap(x,y);
	while(dep[x]>dep[y])
		x=f[x][lg[dep[x]-dep[y]]-1];
	if(x==y)return x;
	for(int i=lg[dep[x]];i>=0;i--)
		if(f[x][i]!=f[y][i])x=f[x][i],y=f[y][i];
	return f[x][0];
}

int n;
int ans;
char a[N];
int dp[N][N];

int DP(int x,int y)
{
	if(dep[x]<dep[y])swap(x,y);
	if(dp[x][y]!=-1)return dp[x][y];
	
	int lca=LCA(x,y),res=0;
	int delt=0;
	if(a[x]==a[y])delt=2;

	if(lca==y)
	{
		int now=x;
		for(int i=11;i>=0;i--)
			if(dep[f[now][i]]>dep[y])now=f[now][i];
	
		res=max(DP(x,now),max(DP(f[x][0],y),DP(f[x][0],now)+delt));
		
		dp[x][y]=dp[y][x]=res;
		return res;
	}

	res=max(DP(x,f[y][0]),max(DP(f[x][0],y),DP(f[x][0],f[y][0])+delt));
	
	dp[x][y]=dp[y][x]=res;
	return res;
}
void solve()
{
	num=0;
	memset(elast,0,sizeof(elast));
	memset(dep,0,sizeof(dep));
	memset(f,0,sizeof(f));
	
	n=read();
	cin>>a+1;
	for(int i=1;i<n;i++)
	{
		int x=read(),y=read();
		add(x,y),add(y,x);
	}
	
	
	dfs(1,0);

	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)dp[i][j]=-1;
		
	for(int i=1;i<=n;i++)dp[i][i]=1;
	for(int i=2;i<=n;i++)
	{
		if(a[i]==a[f[i][0]])dp[i][f[i][0]]=dp[f[i][0]][i]=2;
		else dp[i][f[i][0]]=dp[f[i][0]][i]=1;
	}
	ans=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)ans=max(ans,DP(i,j));
	
	printf("%d\n",ans);
}
int main()
{
	for(int i=1;i<N;i++)
		lg[i]=lg[i-1]+(1<<lg[i-1]==i);
	int T=read();
	while(T--)solve();
	return 0;
}

```


---

## 作者：Cxny (赞：2)

题意：给定一棵 $n$ 个节点的树，每个结点上有一个小写字母。定义 $s(i,j)$ 表示将 $i\to j$ 路径上结点的字符顺次相接形成的字符串，求所有 $s(i,j)$ 的最长回文**子序列**长度的最大值。

先考虑链上的情况。令 $dp(i,j)$ 表示 $i$ 到 $j$ 最长回文子序列长度，则显然有转移
$$
dp(i,j)=\max\{dp(i+1,j),dp(i,j-1),dp(i+1,j-1)+2[s_i=s_j]\}
$$
直接放到树上，就是 $O(n^2)$ 状态、$O(1)$ 转移。记搜即可。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define pb push_back
const int maxn = 2e3 + 10;
int n, dp[maxn][maxn], rt, f[maxn], fa[15][maxn], dep[maxn];
char s[maxn];
vector<int> edge[maxn];
int solve(int x, int y, int lca){
    if(dp[x][y]) return dp[x][y];
    if(lca == x || lca == y){
        if(dep[x] < dep[y]) swap(x, y);
        if(dp[x][y]) return dp[x][y];
        int det = dep[x] - dep[y] - 1, qwq = x;
        if(!det) dp[x][y] = 1 + (s[x] == s[y]);
        else{
            for(int i = 0; i < 12; i++) if(det & (1 << i)) qwq = fa[i][qwq];
            dp[x][y] = max({solve(x, qwq, qwq), solve(f[x], y, y), solve(f[x], qwq, qwq) + 2 * (s[x] == s[y])});
        }
        // printf("%d %d - %d\n", x, y, dp[x][y]);
        return dp[x][y];
    }
    if(y != lca) dp[x][y] = max(dp[x][y], solve(x, f[y], lca));
    if(x != lca) dp[x][y] = max(dp[x][y], solve(f[x], y, lca));
    if(x != lca && y != lca) dp[x][y] = max(solve(f[x], f[y], lca) + 2 * (s[x] == s[y]), dp[x][y]);
    // printf("%d %d - %d\n", x, y, dp[x][y]);
    return dp[x][y];
}
void dfs(int u){
    fa[0][u] = f[u], dep[u] = dep[f[u]] + 1;
    for(int i = 1; i < 12; i++) fa[i][u] = fa[i - 1][fa[i - 1][u]];
    for(int v : edge[u]) if(v != f[u]) f[v] = u, dfs(v);
}
int LCA(int x, int y){
    if(dep[x] < dep[y]) swap(x, y);
    int det = dep[x] - dep[y];
    for(int i = 11; i >= 0; i--) if(det & (1 << i)) x = fa[i][x];
    if(x == y) return x;
    for(int i = 11; i >= 0; i--) if(fa[i][x] != fa[i][y]) x = fa[i][x], y = fa[i][y];
    return f[x];
}
void wsyakioi(){
    scanf("%d%s", &n, s + 1);
    for(int i = 1; i <= n; i++){
        edge[i].clear();
        for(int j = 1; j <= n; j++) dp[i][j] = 0;
        dp[i][i] = 1;
    }
    for(int i = 1, x, y; i < n; i++){
        scanf("%d%d", &x, &y);
        edge[x].pb(y), edge[y].pb(x);
    }
    if(n == 2) return puts(s[1] == s[2] ? "2" : "1"), void();
    for(int i = 1; i <= n; i++) if(edge[i].size()) rt = i;
    f[rt] = 0, dfs(rt); int ans = 1;
    for(int i = 1; i <= n; i++) for(int j = i + 1; j <= n; j++) ans = max(ans, solve(i, j, LCA(i, j)));
    printf("%d\n", ans);
}
int main(){
    int T; scanf("%d", &T);
    while(T--) wsyakioi();
    return 0;
}
```

---

## 作者：紊莫 (赞：1)

树上区间 DP 板子题。

先考虑序列上这个问题怎么做，记 $f_{i,j}$ 为 $[i,j]$ 内的最长回文子序列长度，那么显然有转移（下文方括号表示艾弗森括号）：  

$$f_{i,j} = \max(f_{i+1,j},f_{i,j-1},f_{i+1,j-1}+2\times [S_i=S_j])$$

考虑在树上，一条路径就是一个序列，有 $n^2$ 条路径，直接枚举时间复杂度是 $O(n^4)$ 的，不足以通过本题，考虑在枚举的同时记忆化，因为某些小区间可能被反复使用，此时不必重复计算。

代码实现可以记录一个 $to_{u,v}$ 表示 $u$ 向 $v$ 走一步到达的节点，这个可以 $O(n^2)$ 求出。

[示例代码。](https://codeforces.com/contest/1771/submission/244643766)

---

## 作者：OIer_ACMer (赞：1)

~~这是一棵有理想的树。~~

------------
## 警钟敲烂：
这道题在做的时候一定要建树同时，还要记住一句话：**多测不清空，爆零两行泪**。

------------
## 大致思路：
这道题是一道经典的 LCA 和 区间 DP 缝合题（说实话为啥这种变态难度的题还被评为绿题），但是，由于两者“犬牙交错”太深，导致我在这道题上卡了很久，接下来，我来讲一下这道题得做法。

由于这道题问到了两个点之间的路径，又是在**树上跑**，所以我们很自然而然的想到了**用 LCA 预处理所有点之间的路径**（至于具体操作是啥我就不细讲，因为太基础了）。

接着，我们就来考虑下这道题的重点：区间 DP。我们先设计状态：设 $dp[i][j]$ 表示从第 $i$ 个字符到第 $j$ 个字符路径上的最长回文子序列。若 $\operatorname{lca}(i, j)$ 既不是 $i$ 也不是 $j$，就意味着**这辆点都不在最近公共祖先上**。这时候比较简单，和线性 DP 下的一样，（具体证明笔者在这里不多赘述）：

1. 如果 $s[i]$ 和 $s[j]$ 一样，则说明**形成回文子序列**，则要将这两个字符加入到答案中（因为**要组成回文至少要两个字符**）：$dp[i][j] = d[fa[i]][fa[j]] + 2$。否则**就直接将原来的情况转移下来**：$dp[i][j] = d[fa[i]][fa[j]]$。

2. 同时，我们**还不忘比较哪家父亲的结果更大**，并将更大的那一家记录到子树中去：$dp[i][j] = \max(\max(dp[fa[i]][j], dp[i][fa[j]]), dp[i][j])$。

若 $\operatorname{lca}(i, j)$ 等于 $i$ 或者 $j$ 中的某一个，那么需要先倍增找到 $\operatorname{lca}(i, j)$ 下的那个点，然后更新过程就和刚才一样了。最后注意 dp 状态要用**记忆化搜索的方式更新**，直接遍历 dp 数组更新**不具有后效性，符合 dp 性质**。

------------
## 代码如下：

```c++
#include <bits/stdc++.h>
using namespace std;
inline int read()
{
    register int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
        {
            f = -1;
        }
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
char s[2005];
vector<int> edge[2005];
int dp[2005][2005], fa[2005][25], dep[2005], n;
void dfs(int now, int pre)
{
    dep[now] = dep[pre] + 1;
    fa[now][0] = pre;
    for (int i = 1; i <= 20; i++)
    {
        fa[now][i] = fa[fa[now][i - 1]][i - 1];
    }
    for (int i = 0; i < edge[now].size(); i++)
    {
        if (edge[now][i] != pre)
        {
            dfs(edge[now][i], now);
        }
    }
}
int lca(int x, int y)
{
    if (dep[x] < dep[y])
    {
        swap(x, y);
    }
    for (int i = 20; i >= 0; i--)
    {
        if (dep[fa[x][i]] >= dep[y])
        {
            x = fa[x][i];
        }
    }
    if (x == y)
    {
        return x;
    }
    for (int i = 20; i >= 0; i--)
    {
        if (fa[x][i] != fa[y][i])
        {
            x = fa[x][i], y = fa[y][i];
        }
    }
    return fa[x][0];
}
int dpdfs(int x, int y)
{
    if (x > y)
    {
        swap(x, y);
    }
    if (dp[x][y])
    {
        return dp[x][y];
    }
    int ans = 0;
    int LCA = lca(x, y);
    if (LCA != x && LCA != y)
    {
        ans = dpdfs(fa[x][0], fa[y][0]) + (s[x] == s[y]) * 2;
        ans = max(max(dpdfs(fa[x][0], y), dpdfs(x, fa[y][0])), ans);
    }
    else
    {
        if (LCA == x)
        {
            int now = y;
            for (int i = 20; i >= 0; i--)
            {
                if (dep[fa[now][i]] > dep[LCA])
                {
                    now = fa[now][i];
                }
            }
            ans = dpdfs(fa[y][0], now) + (s[x] == s[y]) * 2;
            ans = max(max(dpdfs(fa[y][0], x), dpdfs(y, now)), ans);
        }
        else
        {
            swap(x, y);
            int now = y;
            for (int i = 20; i >= 0; i--)
            {
                if (dep[fa[now][i]] > dep[LCA])
                {
                    now = fa[now][i];
                }
            }
            ans = dpdfs(fa[y][0], now) + (s[x] == s[y]) * 2;
            ans = max(max(dpdfs(fa[y][0], x), dpdfs(y, now)), ans);
            swap(x, y);
        }
    }
    return dp[x][y] = ans;
}
int main()
{
    int T;
    T = read();
    while (T--)
    {
        n = read();
        scanf("%s", s + 1);
        for (int i = 1; i <= n; i++)
        {
            edge[i].clear();
        }
        for (int i = 1; i < n; i++)
        {
            int u, v;
            u = read();
            v = read();
            edge[u].push_back(v);
            edge[v].push_back(u);
        }
        for (int i = 0; i <= n; i++)
        {
            for (int j = 0; j <= n; j++)
            {
                if (i == j)
                {
                    dp[i][j] = 1;
                }
                else
                {
                    dp[i][j] = 0;
                }
            }
        }
        dfs(1, 0);
        for (int i = 1; i <= n; i++)
        {
            int x = i, y = fa[x][0];
            if (x > y)
            {
                swap(x, y);
            }
            dp[x][y] = (s[x] == s[y]) ? 2 : 1;
        }
        int ans = 1;
        for (int i = 1; i <= n; i++)
        {
            for (int j = i + 1; j <= n; j++)
            {
                dp[i][j] = dpdfs(i, j);
                ans = max(dp[i][j], ans);
            }
        }
        cout << ans << endl;
    }
    return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/122304281)

---

## 作者：王江睿 (赞：1)

提交理由：题解区暂无 bitset 题解，循环 dp 题解．

标准 _链上_ 回文子序列 _串_ 相同原理．    
转移方程为：    
$dp_{i,j}=\max\begin{cases}dp_{i+1,j}\\dp_{i,j-1}\\dp_{i+1,j-1}+2&&{S_{i}=S_{j}}\end{cases}$
    
状态定义：两点确定的区间（$i, j$）内回文子序列的最长长度。    
初始化：单点（起终点相同）序列必回文，记为 $1$．

对「坐标」的补充说明：

![](https://cdn.luogu.com.cn/upload/image_hosting/o9jjvp0b.png)

每一个点作为根的时候，唯一的目的是求出使自己到每一个点的最长回文子序列长度。这就够了。于是把：`for (i = 1; i <= N; ++i)` 修改为 `for (i = e[j]._Find_first(); i <= N; i = e[j]._Find_next(i))`。

有了这个剪枝，可以 Accepted。


附完整代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
basic_string<unsigned> E[2016];
bitset<2016> e[2016];
unsigned G[2016], f[2016], dp[2016][2016];
string V;
void dfs(unsigned fr, unsigned ps)
{
    for (const auto& to : E[ps])
        if (fr != to)
            dfs(ps, to);
    f[ps] = ps, G[ps] = fr;
    return;
}
int main()
{
    unsigned i, j, k, r, s, t, N, anw;
    cin >> t;
    for (i = 1; i < 2016; ++i)
        dp[i][i] = 1, e[i].set();
    do {
        cin >> N >> V;
        V = " " + V;
        for (i = 1; i < N; ++i) {
            cin >> r >> s;
            E[r].push_back(s);
            E[s].push_back(r);
        }
        for (j = 1; j <= N; ++j) {
            dfs(0, j);
            for (k = 1; k <= N; ++k)
                for (i = e[j]._Find_first(); i <= N; i = e[j]._Find_next(i)) {
                    if (!e[i][G[f[i]]] || !G[f[i]] || !G[i])
                        f[i] = G[f[i]];
                    else
                        dp[f[i]][i] = dp[i][f[i] = G[f[i]]] = max({ dp[i][f[i]], dp[G[i]][G[f[i]]],
                            (i == f[i] ? 0 : dp[G[i]][f[i]]) + 2 * (V[i] == V[G[f[i]]]) }),
                        e[f[i]][i] = e[i][f[i]] = 0;
                }
        }
        for (i = 1, anw = 0; i <= N; ++i) {
            anw = max(anw, *max_element(dp[i] + 1, dp[i] + N + 1));
            E[i].clear(); e[i].set();
        }
        cout << anw << '\n';
    } while (--t);
    return 0;
}
```
[可能辨识度更佳的缩进](https://www.luogu.com.cn/paste/0jk17f2z)  
[Codeforces 链接](https://codeforces.com/contest/1771/submission/192572034)


---

## 作者：Fan_sheng (赞：1)

分享一下我的睿智做法，感觉蛮有意思的。

首先容易知道，只需要找出两个端点都是叶子的所有路径，对每条这样的路径都 dp 一遍，取最大值即可。

具体实现是枚举每个叶子，以它为根 dfs 一遍，每找到另一个叶子的时候就 dp 一次。

尝试写了下，T 在了 #16。

vp 的时候降智了，不知道这玩意儿能记忆化，然后加了个玄学优化：

按我们这样的实现方式，假设有根 $a$，叶子 $b,c$，已经算了 $a\rightarrow b$ 的答案，下一个要算 $a\rightarrow c$ 的答案。容易发现字符串的前半部分（即 $a\rightarrow lca(b,c)$）完全没有变化，并且其内部的 dp 值已经在之前算过了，就不用重算了。

于是……过了？？

Code

对了，注意特判 $n=1$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,ans,dp[2003][2003],L;//L表示lca(b,c)在序列中的位置 
char s[2003],a[2003];
vector<int>edge[2003];
inline int max(int a,int b){return a>b?a:b;}
void dfs(int id,int from,int depth){
	a[depth]=s[id];
	if(edge[id].size()==1){
		for(int i=L+1;i<=depth;i++)dp[i][i]=1;
		for(int len=2;len<=depth;len++)
		for(int l=max(1,L-len+2);l+len-1<=depth;l++){//这里l的初值就是我所说的优化 
			int r=l+len-1;
			dp[l][r]=max(dp[l][r-1],dp[l+1][r]);
			if(a[l]==a[r])dp[l][r]=max(dp[l][r],dp[l+1][r-1]+2);
		}ans=max(ans,dp[1][depth]);
	}
	for(int v:edge[id])if(v!=from)dfs(v,id,depth+1),L=depth;//更新lca(b,c) 
}
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d%s",&n,s+1),ans=0;
		for(int i=1;i<=n;i++)edge[i].clear();
		for(int i=1,u,v;i<n;i++){
			scanf("%d%d",&u,&v);
			edge[u].emplace_back(v);
			edge[v].emplace_back(u);
		}
		for(int i=1;i<=n;i++)if(edge[i].size()==1)dfs(i,L=0,1);
		printf("%d\n",n==1?1:ans);
	}return 0;
}
```

我没有细想它复杂度是不是对的，如果有大佬看到了可以评论啊 QAQ

---

## 作者：Leeb (赞：0)

### 题意简述

有 $n$ 个字符构成一棵树，求树上的最长回文子序列。

### 解题思路

先考虑怎么求一个字符串的最长回文子序列，就是一个区间动规，$dp_{i,j}=\max({dp_{i,j-1},dp_{i+1,j},dp_{i+1,j-1}+((s[i]==s[j])\times 2)})$。

现在把这个状态搞到树上来，设 $dp_{i,j}$ 表示从第 $i$ 个字符到第 $j$ 个字符路径上的最长回文子序列，若 $\operatorname{lca}(i,j)$ 既不是 $i$ 也不是 $j$，这个时候比较简单，和线性下的一样，$dp_{i,j}=\max({dp_{i,fa_j},dp_{fa_i,j},dp_{fa_i,fa_j}+((s[i]==s[j])\times 2)})$，若 $\operatorname{lca}(i,j)$ 等于 $i$ 和 $j$ 中的某一个，那么我们需要先倍增找到 $\operatorname{lca}$ 下的那个点，然后更新过程就和刚刚一样了。

### 参考代码

```cpp
// -- More and More vegetales, what should I do?
// -- AFO! AFO YYDS!
// Code Author : Leeb
// #include <bits/stdc++.h>
#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define N 2005
#define M 25
#define inf 0x3f3f3f3f
#define endl '\n'
#define elif else if
// #define int long long 
#define ll long long
#define mem(a, x) memset(a, x, sizeof(a))
using namespace std;
vector<int> G[N];
int n, m, dep[N], ffa[N][M], dp[N][N]; char s[N];
inline int in() {
    int a = 0; bool f = 0; char ch = getchar();
    while (ch < '0' || ch > '9')
        {if (ch == '-') f = 1; ch = getchar();}
    while (ch >= '0' && ch <= '9')
        a = (a << 1) + (a << 3) + (ch ^ 48), ch = getchar();
    if (f) return ~a + 1;   
    return a;
}
inline void print(int x) {
    if (x < 0) putchar('-'), x = ~x + 1;
    if (x > 9) print(x / 10);
    putchar(x % 10 + '0');
}
inline void out(int x, char ch) {
    print(x);
    putchar(ch);
}
inline void init() {
    n = in();
    scanf("%s", s + 1);
    for (int i = 1; i <= n; ++i) G[i].clear();
    for (int i = 1; i < n; ++i) {
        int u = in(), v = in();
        G[u].push_back(v);
        G[v].push_back(u);
    }
    for (int i = 0; i <= n; ++i)
        for (int j = 0; j <= n; ++j)
            if (i == j) dp[i][j] = 1;
            else dp[i][j] = 0;
}
inline void dfs(int u, int fa) {
    dep[u] = dep[fa] + 1;
    ffa[u][0] = fa;
    for (int i = 1; i <= 20; ++i) 
        ffa[u][i] = ffa[ffa[u][i - 1]][i - 1];
    for (int i = 0; i < G[u].size(); ++i) {
        int v = G[u][i];
        if (v == fa) continue;
        dfs(v, u);
    }
}
inline void swap(int &a, int &b) {
    a ^= b ^= a ^= b;
}
inline int LCA(int x, int y) {
    if (dep[x] < dep[y]) swap(x, y);
    for (int i = 20; i >= 0; --i)
        if (dep[ffa[x][i]] >= dep[y]) x = ffa[x][i];
    if (x == y) return x;
    for (int i = 20; i >= 0; --i)
        if (ffa[x][i] != ffa[y][i])
            x = ffa[x][i], y = ffa[y][i];
    return ffa[x][0];
}
inline int dfs_(int x, int y) {
    if (x > y) swap(x, y);
    if (dp[x][y]) return dp[x][y];
    int ans = 0, lca = LCA(x, y);
    if (lca != x && lca != y) {
        ans = dfs_(ffa[x][0], ffa[y][0]) + ((s[x] == s[y]) << 1);
        ans = max({ans, dfs_(ffa[x][0], y), dfs_(x, ffa[y][0])});
    }
    else
        if (lca == x) {
            int u = y;
            for (int i = 20; i >= 0; --i) 
                if (dep[ffa[u][i]] > dep[lca]) u = ffa[u][i];
            ans = dfs_(ffa[y][0], u) + ((s[x] == s[y]) << 1);
            ans = max({ans, dfs_(ffa[y][0], x), dfs_(y, u)});
        }
        else {
            swap(x, y); int u = y;
            for (int i = 20; i >= 0; --i)
                if (dep[ffa[u][i]] > dep[lca]) u = ffa[u][i];
            ans = dfs_(ffa[y][0], u) + ((s[x] == s[y]) << 1);
            ans = max({ans, dfs_(ffa[y][0], x), dfs_(y, u)});
            swap(x, y);
        }
    return dp[x][y] = ans;
}
inline void work() {
    dfs(1, 0);
    for (int i = 1; i <= n; ++i) {
        int x = i, y = ffa[x][0];
        if (x > y) swap(x, y);
        if (s[x] == s[y]) dp[x][y] = 2;
        else dp[x][y] = 1;
    }
    int ans = 1;
    for (int i = 1; i <= n; ++i)    
        for (int j = i + 1; j <= n; ++j) {
            dp[i][j] = dfs_(i, j);
            ans = max(dp[i][j], ans);
        }
    out(ans, '\n');
}
signed main() {
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    int t = in();
    while (t--) {
        init();
        work();
    }
    return 0;
}
```



---

## 作者：__3E24AC7002AD9292__ (赞：0)

挺好的树上区间 DP 题，没做过这种板子，所以我 VP 的时候没做出来。

首先考虑对于一个序列的做法。

对于一个区间 $[l,r]$，可以分几种讨论：

- 舍去 $s_l,s_r$ 的其中一个，不加贡献。
- 同时舍去 $s_l,s_r$，此时如果 $s_l=s_r$，答案加 $2$，显然是有贡献的，而且对 $[l+1,r-1]$ 答案不影响。

那么设 $dp_{l,r}$ 为 $[l,r]$ 的答案，那么 $dp_{l,r}=\max(dp_{l+1,r},dp_{l,r-1},dp_{l+1,r-1}+2[s_l=s_r])$。

然后是树上的做法。

类似地，考虑一个路径 $x\leftrightarrow y$，还是这些情况：

- 舍去 $s_x,s_y$ 的其中一个，不加贡献。
- 同时舍去 $s_x,s_y$，此时如果 $s_x=s_y$，答案加 $2$。

舍去的时候需要让 $x$ 或 $y$ 跳到父亲上，显然在某个点跳到 $lca(x,y)$ 上再跳父亲就错了。所以为了方便，跳 $x$ 的时候让 $x$ 跳到以 $y$ 为根时 $x$ 的父亲，我们记其为 $fa(y,x)$，那么 $y$ 同理，这个预处理一下即可。

那么设 $dp_{x,y}$ 为 $x\leftrightarrow y$ 的答案，那么 $dp_{x,y}=\max(dp_{fa(y,x),y},dp_{x,fa(x,y)},dp_{fa(y,x),fa(x,y)}+2[s_x=s_y])$。

---

