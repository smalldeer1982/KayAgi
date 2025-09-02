# Subtree

## 题目描述

[problemUrl]: https://atcoder.jp/contests/dp/tasks/dp_v

$ N $ 頂点の木があります。 頂点には $ 1,\ 2,\ \ldots,\ N $ と番号が振られています。 各 $ i $ ($ 1\ \leq\ i\ \leq\ N\ -\ 1 $) について、$ i $ 番目の辺は頂点 $ x_i $ と $ y_i $ を結んでいます。

太郎君は、各頂点を白または黒で塗ることにしました。 このとき、どの黒い頂点からどの黒い頂点へも、黒い頂点のみを辿って到達できるようにします。

正整数 $ M $ が与えられます。 各 $ v $ ($ 1\ \leq\ v\ \leq\ N $) について、次の質問に答えてください。

- 頂点 $ v $ が黒であるような頂点の色の組合せは何通りか？ $ M $ で割った余りを求めよ。

## 说明/提示

### 制約

- 入力はすべて整数である。
- $ 1\ \leq\ N\ \leq\ 10^5 $
- $ 2\ \leq\ M\ \leq\ 10^9 $
- $ 1\ \leq\ x_i,\ y_i\ \leq\ N $
- 与えられるグラフは木である。

### Sample Explanation 1

頂点の色の組合せは次図の $ 7 $ 通りです。 このうち、頂点 $ 1 $ が黒であるようなものは $ 3 $ 通り、頂点 $ 2 $ が黒であるようなものは $ 4 $ 通り、頂点 $ 3 $ が黒であるようなものは $ 3 $ 通りです。 !\[\](https://img.atcoder.jp/dp/subtree\_0\_muffet.png)

### Sample Explanation 4

答えを $ M $ で割った余りを出力することを忘れずに。

## 样例 #1

### 输入

```
3 100
1 2
2 3```

### 输出

```
3
4
3```

## 样例 #2

### 输入

```
4 100
1 2
1 3
1 4```

### 输出

```
8
5
5
5```

## 样例 #3

### 输入

```
1 100```

### 输出

```
1```

## 样例 #4

### 输入

```
10 2
8 5
10 8
6 5
1 5
4 8
2 10
3 6
9 2
1 7```

### 输出

```
0
0
1
1
1
0
1
0
1
1```

# 题解

## 作者：zhlzt (赞：30)

### 换根 DP 做法
这题要用换根 DP 解决，换根 DP 也是一种的树形 DP。

由于题目中说的是无根树，我们将其转化为一个以 $1$ 为根的有根树来处理。

设把 $u$ 染成黑色时，在以 $u$ 为根的子树中，染成黑色的节点与 $u$ 构成一个连通块的方案数为 $dp1_{u}$；在以 $u$ 为根的子树外，染成黑色的节点与 $u$ 构成一个连通块的方案数为 $dp2_{u}$。那么最终答案就是 $dp1_{u}\times dp2_{u}$。

显然，$dp1_{u}$ 的转移方程为：

$$dp1_{u}=\prod_{v\in \text{son}(u)} dp1_{v}+1$$

其中，$\text{son}(u)$ 表示 $u$ 的所有儿子的集合，$dp1_{v}+1$ 表示将节点 $v$ 染成黑色和白色的方案数总和。

$dp2_{u}$ 的转移方程较为难想，要让 $u$ 与外界连通，只有一个中转点，那就是 $u$ 的父亲 $fa$，$fa$ 既连向了 $u$ 的兄弟，又连向了 $u$ 的祖父、曾祖父、叔叔、堂兄弟等，于是知 $dp2_{u}$ 的状态转移方程为：

$$dp2_{u}=\left(dp2_{fa}\times\prod_{v\in\text{brother}(u)} dp1_{v}+1 \right)+1$$

其中，$\text{brother(u)}$ 表示 $u$ 的所有兄弟的集合，$dp1_{v}+1$ 表示将节点 $v$ 染成黑色和白色的方案数总和。整个式子表示将节点 $fa$ 染成黑色和白色的方案数总和（即是否让 $u$ 与外界连通）。

很明显，求 $n$ 次 $\prod dp1_{v}+1~(v\in \text{brother}(u))$ 的复杂度最坏是 $O(n^2)$ 的，TLE，需要优化。由于要取余，且模数不保证为质数，所以优化是不能用除法，或费马小定理的。

考虑预处理前缀积，后缀积，设 $pre_{u}$ 表示在 $u$ 左边的兄弟的 $dp1_{v}+1$ 值的积，设 $suf_{u}$ 表示在 $u$ 右边的兄弟的 $dp1_{v}+1$ 值的积，那么 $\prod dp1_{v}+1~(v\in \text{brother}(u))$ 就可以转化为 $pre_{u}\times suf_{u}$ 了。

### 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+10;
int dp1[maxn],dp2[maxn],n,mod;
int pre[maxn],suf[maxn];
vector<int>edge[maxn];
void dfs1(int u,int fa){ 
	dp1[u]=1; 
    vector<int>son;
	for(int v:edge[u]){
		if(v==fa) continue;
		dfs1(v,u); 
        dp1[u]=1LL*dp1[u]*(dp1[v]+1)%mod;
		son.push_back(v); 
		// 将子节点加入集合，方便之后操作
	}
	int tmp=1;
	for(int i=0;i<son.size();i++){
		pre[son[i]]=tmp;
		tmp=1LL*tmp*(dp1[son[i]]+1)%mod;
	}
	// 预处理前缀积
    tmp=1;
	for(int i=son.size()-1;i>=0;i--){
		suf[son[i]]=tmp;
		tmp=1LL*tmp*(dp1[son[i]]+1)%mod;
	} 
	// 预处理后缀积
}
void dfs2(int u,int fa){
	if(fa==-1) dp2[u]=1; // 特判根节点
	else dp2[u]=(1LL*dp2[fa]*(1LL*pre[u]*suf[u]%mod)%mod+1)%mod;
	for(int v:edge[u]){
		if(v!=fa) dfs2(v,u);
	}
}
int main(){
	scanf("%d%d",&n,&mod);
  	int u,v;
	for(int i=1;i<n;i++){
		scanf("%d%d",&u,&v);
		edge[u].push_back(v); 
		edge[v].push_back(u);
	} 
	dfs1(1,-1); dfs2(1,-1);
	for(int i=1;i<=n;i++){
        printf("%d\n",1LL*dp1[i]*dp2[i]%mod);
    }
	return 0;
}
```

---

## 作者：TKXZ133 (赞：13)

[Subtree](https://www.luogu.com.cn/problem/AT_dp_v)

### 题目大意

给定一颗树，你可以选出一些节点，你需要对于每个点求出在强制选这个点的情况下所有选择的点联通的方案数，对给定模数取模。

### 思路分析

对于这种求树上每一个点方案数的题目，首先考虑换根 DP。

强制钦定树根为 $1$，设 $f_i$ 表示在 $i$ 的子树中选点，$i$ 强制选，所有选择的点联通的方案数，$g_i$ 表示在 $i$ 的子树外选点，$i$ 强制选，所有选择的点联通的方案数，那么显然点 $s$ 的答案就是 $f_s\times g_s$。

- 考虑计算 $f$：

对于叶节点 $s$，显然 $f_s=1$，对于非叶节点，容易得出状态转移方程：

$$f_{u}=\prod_{v\in \text{son}_{u}}(f_v+1)$$

解释一下，$f_v+1$ 就是 $u$ 的一个子节点的子树染色的方案数，而 $u$ 的子树的染色方案数就是所有 $f_v+1$ 的乘积。

- 考虑计算 $g$：

对于根节点 $1$，显然 $g_1=1$，对于非根节点，不难得出状态转移方程：

$$g_v=g_{u}\times\frac{f_{u}}{f_v+1},u=\text{fa}_{v}$$

解释一下，从 $g_u$ 转移到 $g_v$，新增的节点就是 $u$ 的子树去掉 $v$ 的子树中的点后的所有点，而这些点染色的方案数就是 $\frac{f_{u}}{f_{v}+1}$，也可以理解为在 $f_u$ 中去掉所有由 $v$ 产生的贡献。

但是直接求肯定是没法求的，模数不一定是质数，不一定存在逆元，但是我们发现我们可以将除法改为乘法，也即：

$$g_{v}=g_{u}\times\prod_{p\not =v,p\in \text{son}_u} (f_p+1)$$

而这个可以通过预处理每个节点的子节点权值的前缀积和后缀积实现。

故我们只需要通过两遍 dfs 就可以在 $O(n)$ 的时间空间内解决问题。

### 代码

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;
const int N=200200;
#define int long long 

int n,mod,in1,in2,idx=1;
int to[N],nxt[N],head[N];
int f[N],g[N];

vector<int> pre[N],suf[N];

void add(int u,int v){
    idx++;to[idx]=v;nxt[idx]=head[u];head[u]=idx;
}

void dfs_1(int s,int fa){
    f[s]=1;
    for(int i=head[s];i;i=nxt[i]){
        int v=to[i];
        if(v==fa) continue;
        dfs_1(v,s);
        f[s]=f[s]*(f[v]+1)%mod;
        pre[s].push_back(f[v]+1);
        suf[s].push_back(f[v]+1);
    }
    for(int i=1;i<pre[s].size();i++) 
        pre[s][i]=pre[s][i]*pre[s][i-1]%mod;//前缀积
    for(int i=suf[s].size()-2;i>=0;i--) 
        suf[s][i]=suf[s][i]*suf[s][i+1]%mod;//后缀积
}

void dfs_2(int s,int fa){
    int num=0,x=pre[s].size();
    for(int i=head[s];i;i=nxt[i]){
        int v=to[i];
        if(v==fa) continue;
        num++;
        if(x==1) g[v]=g[s]+1; //一些特判，可能不需要
        else if(num==1) g[v]=g[s]*suf[s][num]%mod+1;
        else if(num==x) g[v]=g[s]*pre[s][num-2]%mod+1;
        else g[v]=g[s]*(pre[s][num-2]*suf[s][num]%mod)%mod+1;
        dfs_2(v,s);
    }
}

signed main(){
    scanf("%lld%lld",&n,&mod);
    for(int i=1;i<n;i++){
        scanf("%lld%lld",&in1,&in2);
        add(in1,in2);add(in2,in1);
    }    
    dfs_1(1,0);
    g[1]=1;
    dfs_2(1,0);
    for(int i=1;i<=n;i++)
        cout<<(f[i]*g[i]%mod)<<'\n';
    return 0;
}
```

---

## 作者：FelFa_1414666 (赞：13)

这是**树形 dp** 中的**换根 dp**。

[atcoder 题目传送门 ](https://atcoder.jp/contests/dp/tasks/dp_u) & [洛谷题目传送门](https://www.luogu.com.cn/problem/AT4543) 

[更好的阅读体验](https://www.luogu.com.cn/blog/xesssb10108899/solution-at4543)

---

## Description

有一个 $n$ 个节点的树，对一些节点染色，使得所有被染色的节点是一个连通块。求对于 $1,2,...,n$ 每个节点，该节点被染色的方案个数。所有答案对 $M$ 取模。

- $1\le n\le 10^5$

- $2\le M\le 10^9$

---

## Solution

换根 dp，我们需要考虑两个 dp 状态：

- $dp1_u$ 表示考虑以 $u$ 为根节点的子树，染色节点 $u$ 被染色的方案数。

- $dp2_u$ 表示考虑以 $u$ 为根节点的子树外的节点和 $u$，节点 $u$ 被染色的方案数。

转移：

对于换根 dp ，我们要用两次 dfs 转移 dp 值。

第一次 dfs 选取节点 0 为根，在这棵有根树上转移 $dp1$ 的值。

$$dp1_u=\prod (dp1_v+1)$$

![](https://cdn.luogu.com.cn/upload/image_hosting/ta6ax2ls.png)

~~人类高质量画图大赏。~~

其中 $v$ 是 $u$ 的儿子。表示对于每个子树的根，他每个子树的染色方案是独立的，并且每个子树可以不染色。这颗子树的染色方案就是**他所有子树染色方案 +1 的积**。

第二次 dfs 处理 $dp2$ 的值，可以通过dp1递推

$$dp2_u=dp2_p\times\prod (dp1_v+1)+1$$

![](https://cdn.luogu.com.cn/upload/image_hosting/cxduykhn.png)

其中 $p$ 是 $u$ 的父亲，$v$ 是 $u$ 的兄弟。表示对于每个子树外的节点，可以分为**兄弟子树中的节点**和**父亲以上的节点**两类，用父亲以上的节点的 $dp2$ 值乘上**兄弟节点子树的可能数 +1 的积**。最后总的答案 +1 表示**只有 $u$ 节点被染色**的可能。

每个节点 $u$ 的答案就是 $dp1_u\times dp2_u$。

### 关于取模&优化：

第二次 dfs 转移如果暴力枚举每个兄弟节点，时间复杂度会达到 $O(n^2)$。

我们可以将 $\prod (dp1_v+1)$ 转化为 $\dfrac{dp1_p}{dp1_u+1}$。

但是由于**模数 $M$ 不一定是质数**，所以这里的除法运算不能用逆元去做。

冷静分析后发现，我们可以对每个父亲节点，按顺序维护他所有儿子 $u$ 的 $dp1_u+1$ 这个值的**前缀积**和**后缀积**。这样就能 $O(1)$ 地求出 $\prod dp1_v+1$。

- 时间复杂度：$O(n)$

- 空间复杂度：$O(n)$

---

## Code

```c++
#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define pii pair<int,int>
#define mp make_pair
#define F first
#define S second
using namespace std;
int n;
ll MOD,dp1[100005],dp2[100005];
vector<int> G[100005];//邻接表
vector<ll> pro1[100005],pro2[100005];//子节点的前缀积，后缀积
void dfs1(int u,int p)
{
	pro1[u].resize((int)G[u].size(),1);
	pro2[u].resize((int)G[u].size(),1);
	if ((int)G[u].size()==1&&G[u][0]==p)
	{
		dp1[u]=1;
		return;
	}
	dp1[u]=1ll;
	for(int i=0;i<G[u].size();i++)
		if (G[u][i]!=p)//枚举儿子转移
		{
			dfs1(G[u][i],u);
			dp1[u]=dp1[u]*(dp1[G[u][i]]+1)%MOD;
		}
	for(int i=1;i<G[u].size();i++)
	{//处理前缀积
		pro1[u][i]=pro1[u][i-1];
		if (G[u][i-1]!=p)
			pro1[u][i]=pro1[u][i]*(dp1[G[u][i-1]]+1)%MOD;
	}
	for(int i=(int)G[u].size()-2;i>=0;i--)
	{//处理后缀积
		pro2[u][i]=pro2[u][i+1];
		if (G[u][i+1]!=p)
			pro2[u][i]=pro2[u][i]*(dp1[G[u][i+1]]+1)%MOD;
	}
}
void dfs2(int u,int p,int id)
{//id表示当前u节点在p节点儿子中的序号是多少，用来处理前后缀积
	if (p==-1)
		dp2[u]=1;
	else
	{	
		dp2[u]=dp2[p]*pro1[p][id]%MOD*pro2[p][id]%MOD+1;//转移
		if (dp2[u]>=MOD) dp2[u]-=MOD;
	}
	for(int i=0;i<G[u].size();i++)
		if (G[u][i]!=p)
			dfs2(G[u][i],u,i);
	return;
}
int main()
{
	ios::sync_with_stdio(false),cin.tie(nullptr);
	cin>>n>>MOD;
	for(int i=0;i<n-1;i++)
	{//读入，邻接表存边
		int u,v;
		cin>>u>>v;
		G[u-1].pb(v-1);
		G[v-1].pb(u-1);
	}
	dfs1(0,-1);//两次dfs转移
	dfs2(0,-1,-1);
	for(int i=0;i<n;i++)
		cout<<dp1[i]*dp2[i]%MOD<<endl;//输出每个节点的答案
	return 0;
}
```

---

## Summary

所谓换根 dp ，一定是第一次 dfs 转移选定一个节点做为根，求一些每个子树的信息；第二次 dfs 转移，用之前每个子树的信息，来求一些子树外的具有普适意义的信息。

这样的算法能在 $O(n)$ 的时间里很好的求出每一个节点作为根时的答案。这样也就达到了“换根”的目的。

希望题解对你有帮助！

---

## 作者：NBest (赞：6)

[AT_dp_v Subtree](https://www.luogu.com.cn/problem/AT_dp_v)

# 思路
考虑树形 dp，假设根左右子树的连通块已经算出来了，我们用 $f[x]$ 表示强制将 $x$ 染色，$x$ 子树的连通块方案数。

那么我们可得：
$f[u]=\prod\limits _{v=u_{son}} (f[v]+1)$

$+1$ 是因为还要算上这个子树不取的情况。

但是考虑到根的答案处理出来后，其他节点的答案还没有处理出来。由于 $n\leq10^5$，我们显然不能对每个节点设根做一遍 dfs，所以考虑换根 dp。

由于在换根之后根节点除了这个子树以外的部分都算这个点的子树，转移方法同上，那我们思考后又可得:

$f'[v]=f[v]\times(f[u]\div(f[v]+1)+1)$

但是我们又要对答案取模，这使得式子应该为：

$f'[v]=f[v]\times(f[u]\div(f[v]+1)+1)\bmod m$

而 $m$ 不一定为质数，这意味着我们不能通过求逆元的方式来解决这个除法。

那怎么办呢？

显然不能再算一遍，那我们只能想一个 $\log n$ 以下的方法处理。

考虑同时做前缀乘和后缀乘，计算对子树的贡献只需要将前缀乘和后缀乘相乘即可，虽然多了几个 $O(n)$，但是总复杂度不变。空间上，因为子树根的个数为 $O(n)$，所以空间复杂度也为 $O(n)$。

注意细节处理即可。

## $Code:$
```cpp
int n,mod,cnt;//cnt维护前缀乘起点。
ll dp[100005],pre[400005],sub[400005];//pre表示前缀乘数组，sub表示后缀乘数组，开4倍是为了放每个区间之间的2个间距
basic_string<int> f[100005];
void dfs1(int x,int fa){//处理根节点答案。
    dp[x]=1;
    for(int y:f[x]){
        if(y==fa)continue;
        dfs1(y,x);
        dp[x]=(dp[x]*(dp[y]+1))%mod;//套公式即可
    }
}
void dfs(int x,int fa,ll las){
    dp[x]=dp[x]*(las+1)%mod;
    int st=++cnt,en,o=0;//st表示开始位置，en表示结束位置（为什么要直接在数组上做？因为方便，而且数组快，内存有保证）
    cnt=cnt+f[x].size()+1;//这里直接加f[x].size()，不需要减一，因为父节点也要算进子节点的前缀后缀答案中（换根后作为一棵子树）
    pre[st-1]=1,sub[cnt-1]=1;//处理数组前后值。
    en=cnt-2;//cnt比en大2是为了放st-1和en+1。
    for(int i=0;i<f[x].size();i++){//前缀乘
        int y=f[x][i];
        if(y==fa)pre[st+o]=pre[st+o-1]*(las+1)%mod;//父亲加进来
        else pre[st+o]=pre[st+o-1]*(dp[y]+1)%mod;
        o++;
    }
    o=0;
    for(int i=f[x].size()-1;~i;--i){//后缀乘
        int y=f[x][i];
        if(y==fa)sub[en-o]=sub[en-o+1]*(las+1)%mod;
        else sub[en-o]=sub[en-o+1]*(dp[y]+1)%mod;
        o++;
    }
    for(int i=0;i<f[x].size();i++){
        int y=f[x][i];
        if(y==fa)continue;
        dfs(y,x,(pre[st+i-1]*sub[st+i+1])%mod);//递归
    }
}
int main(){
    n=read(),mod=read();
    for(int i=1;i<n;i++){
        int u=read(),v=read();
        f[u]+=v,f[v]+=u;
    }
    dfs1(1,0);
    dfs(1,0,0);
    for(int i=1;i<=n;i++){
        printf("%lld\n",dp[i]%mod);
    }
}
```

---

## 作者：jnzg (赞：2)

[AT_dp_v Subtree](https://www.luogu.com.cn/problem/AT_dp_v)

# 题目大意

给出结点数为 $n$ 的树，求以每个结点为根，对包含根的联通块计数。

# 思路

显然是换根 dp。

首先考虑一个根节点的情况，设 $f_u$ 表示以 $u$ 为根节点的子树，强制选 $u$ 的方案数，于是有：

$$

f_u=\prod\limits_{v\in son_u}(f_v+1)
$$

考虑换根，设 $ans_u$ 表示以 $u$ 为整棵树的根，强制选 $u$ 的方案数。于是有：

$$
ans_u=\frac{ans_{fa_u}}{f_u+1}\times f_u
$$

然而要对 $m$ 取模，但 $m$ 不一定是质数，所以没法做除法。

考虑暴力相乘，设 $g_u$ 为除去 $u$ 的子树，以 $u$ 为根节点，强制选 $u$ 的方案数，得到：

$$
g_u=g_{fa_u}\prod_{v\in fa_u \operatorname{and}v\ne u}(f_v+1)
$$

于是问题变成如何求 $\prod_{v\in fa_u \operatorname{and}v\ne u}(f_v+1)$。

想不到前缀后缀积怎么办？

不难想到分治，设 $fa_u$ 的儿子区间 $[l,r]$ 表示第 $l$ 到第 $r$ 个儿子，设区间中点 $mid$。

先将区间 $[mid+1,r]$ 的 $f_v+1$ 乘起来，记到 $mul$ 中，然后递归区间 $[l,mid]$，再把 $mul$ 还原，将区间 $[l,mid]$ 的 $f_v+1$ 乘起来，递归区间 $[mid+1,r]$。

当 $l=r$ 时 $mul$ 即为 $\prod_{v\in fa_u \operatorname{and}v\ne u}(f_v+1)$，于是就得到了 $g_u$。

最终答案即为 $f_u\times g_u$。

空间虽然小了点，但时间复杂度为 $O(n\log n)$。

Code：
```cpp
#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define lp(i, j, n) for(int i = j; i <= n; ++i)
#define dlp(i, n, j) for(int i = n; i >= j; --i)
#define mst(n, v) memset(n, v, sizeof(n))
#define mcy(n, v) memcpy(n, v, sizeof(v))
#define INF 1e18
#define MAX4 0x3f3f3f3f
#define MAX8 0x3f3f3f3f3f3f3f3f
#define pii pair<int, int>
#define pll pair<ll, ll>
#define co(x) cerr << (x) << ' '
#define cod(x) cerr << (x) << endl
#define fi first
#define se second
#define eps 1e-8
#define lc(x) ((x) << 1)
#define rc(x) ((x) << 1 ^ 1)
#define pb(x) emplace_back(x)

using namespace std;

const int N = 100010;

int n, m;
int f[N], g[N];

struct edge { int v, nxt; } E[N << 1];
int en, hd[N];

void add(int u, int v) { E[++en] = { v, hd[u] }, hd[u] = en; }

void dfs1(int u, int fa) {
    f[u] = 1;
    for(int i = hd[u]; i; i = E[i].nxt) {
        int v = E[i].v;
        if(v == fa) continue;
        dfs1(v, u), f[u] = 1ll * f[u] * (f[v] + 1) % m;
    }
}

int son[N], tot;
ll mul;
void solve(int l, int r) {
    if(l == r) return g[son[l]] = (mul + 1) % m, void();
    ll t = mul; int mid = l + r >> 1;
    lp(i, mid + 1, r) mul = mul * (f[son[i]] + 1) % m;
    solve(l, mid);
    mul = t; lp(i, l, mid) mul = mul * (f[son[i]] + 1) % m;
    solve(mid + 1, r);
}

void dfs2(int u, int fa) {
    tot = 0, mul = g[u];
    for(int i = hd[u]; i; i = E[i].nxt) {
        if(E[i].v != fa) son[++tot] = E[i].v;
    }
    if(tot >= 1) solve(1, tot);
    for(int i = hd[u]; i; i = E[i].nxt) {
        if(E[i].v != fa) dfs2(E[i].v, u);
    }
}

signed main() {
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
#ifndef READ
    ios::sync_with_stdio(false);
    cin.tie(0);
#endif
    cin >> n >> m;
    int u, v;
    lp(i, 1, n - 1) cin >> u >> v, add(u, v), add(v, u);
    dfs1(1, 0), g[1] = 1, dfs2(1, 0);
    lp(i, 1, n) cout << 1ll * f[i] * g[i] % m << endl;
    return 0;
}
```


---

## 作者：novax (赞：2)

[题面](https://www.luogu.com.cn/problem/AT4543)。

### 题意

对于每一个节点，求强制把该节点染成黑色的情况下，所有的黑色节点组成一个联通块的染色方案数。

### 思路

对于每个点都要求答案，每次 $O(n)$ 求解显然不现实，于是考虑**换根dp**。

先考虑只有一次询问怎么做：设 $F_i$ 表示 $i$ 点被染成黑色，其子树中只含有一个黑色连通块的方案数。则有转移：$F_i = \prod_{j \in son_i} (F_{j}+1)$。因为对于当前点的子树 $j$，既可以是子树的根染成黑色的方案，也可以整棵子树都为白色，而每棵子树之间是乘法原理。$F_{root}$ 即为答案。

然后是换根。当前根 $p$ 不是最初的根时，答案则变为两部分：在第一次 dp 过程中 $p$ 的子树的贡献和在原树中当前点的父亲构成的“子树”的答案。设在第一次 dp 的树上 ${fa}_p$ 子树之外所有点的方案和为 $F_f$，则其父亲方向的“子树”的贡献为 $F'=(F_f +1) \times \prod F_{brother_p}$，其中 ${brother}_p$ 是在第一次 dp 的树中所有与 $p$ 有相同父亲节点的节点。而当前点为根的最终答案则为 $(F'+1) \times F_{p}$。

本题需要对答案取模。因此求 $\prod F_{brother_p}$ 不能用 $\frac{F_{fa_p}}{F_p}$ 的方法来求，因为模数**可能不是质数**。因此可以换一种巧妙的思路，在第一次 dp 时维护 $p$ 点兄弟节点的答案前缀积和后缀积，这样用前缀积和后缀积相乘就实现了求得兄弟节点答案乘积的效果。前缀积后缀积可以用递归方式方便的维护。

### 代码

```cpp
#include <cstdio>
#include <vector>
const int Nx=100010;
int N,Mod;
struct edge{int to,nex;};
edge a[2*Nx];
int head[Nx],cnt;
void add(int u,int v)
{
	a[++cnt].to=v;
	a[cnt].nex=head[u];
	head[u]=cnt;
}
long long F[Nx],ANS[Nx],qx[Nx],hx[Nx];
//F以当前点为根的子树中 当前点被染成黑色且只有一个黑色联通块的方案数 qx/hx对于每个节点的前缀/后缀积
long long mul(int i,int fa,long long val)//在链上递归记录前缀/后缀积
{
	if(i==0)
		return 1;
	qx[a[i].to]=val;
	if(a[i].to==fa)
		return hx[a[i].to]=mul(a[i].nex,fa,val);
	hx[a[i].to]=mul(a[i].nex,fa,(val*(F[a[i].to]+1))%Mod);
	return (hx[a[i].to]*(F[a[i].to]+1))%Mod;
}
void dfs_dp(int p,int fa)//第一次dp
{
	int i;
	F[p]=1;
	for(i=head[p];i;i=a[i].nex)
	{
		if(a[i].to==fa)
			continue;
		dfs_dp(a[i].to,p);
		F[p]=F[p]*(F[a[i].to]+1)%Mod;
	}
	mul(head[p],fa,1);
}
void dfs_huangen(int p,int fa,long long ff)//换根
{
	int i;
	if(p!=1)
	{
		ff=((ff+1)*((qx[p]*hx[p])%Mod))%Mod;
		ANS[p]=F[p]*(ff+1)%Mod;
	}
	for(i=head[p];i;i=a[i].nex)
	{
		if(a[i].to==fa)
			continue;
		dfs_huangen(a[i].to,p,ff);
	}
}
int main()
{
	scanf("%d%d",&N,&Mod);
	int i,j,k;
	for(i=1;i<N;i++)
	{
		scanf("%d%d",&j,&k);
		add(j,k);add(k,j);
	}
	dfs_dp(1,1);
	ANS[1]=F[1];
	dfs_huangen(1,1,0);
	for(i=1;i<=N;i++)
		printf("%lld\n",ANS[i]);
}
```


---

## 作者：_Vix_ (赞：1)

[原题链接](https://www.luogu.com.cn/problem/AT_dp_v)

---

## 分析

换根 DP。我们根据子树内外的贡献分别设计状态。

$f_u$：$u$ 被染成黑色，$u$ 及其子树的贡献。

$g_u$：$u$ 子树外的贡献。

$u$ 的答案就是 $f_u \times g_u$。

考虑转移：

$$f_u = \prod_{v \in son(u)} (f_v + 1)$$

$$g_v = g_u \times \prod_{v' \in son(u), \ v' \ne v} (f_{v'} + 1)+1$$

$+1$ 是上一节点可以不用为黑色多出来的贡献，自己画个图就很好理解了。现在我们就得到了 $O(n^2)$ 的 DP。

发现瓶颈在于 $g$ 的转移，是 $O(n)$ 的，这里使用前缀积和后缀积优化就是 $O(1)$ 的了。至此 $O(n)$ 就解决了这个题。

## Code
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 1e5 + 10;
int h[N], e[N << 1], ne[N << 1], idx;
int f[N], g[N], son[N], ans[N];
int n, mod;
vector<int> val[N], pre[N], suc[N];

void add(int u, int v) {
	e[idx] = v, ne[idx] = h[u], h[u] = idx++;
}

void dfs1(int u, int fa) {
	int tmp = 1;
	val[u].push_back(1);
	for (int i = h[u]; ~i; i = ne[i]) {
		int v = e[i];
		if (v == fa) continue;
		dfs1(v, u);
		son[u]++;
		val[u].push_back(f[v] + 1);
		tmp = (ll)tmp * (f[v] + 1) % mod;
	}
	f[u] = tmp;
}

void dfs2(int u, int fa) {
	if (u == 1) g[u] = 1;
	ans[u] = (ll)f[u] * g[u] % mod;
	pre[u].resize(son[u] + 2);
	suc[u].resize(son[u] + 2);
	pre[u][0] = suc[u][son[u] + 1] = 1;
	for (int i = 1; i <= son[u]; i++) pre[u][i] = (ll)pre[u][i - 1] * val[u][i] % mod;
	for (int i = son[u]; i >= 1; i--) suc[u][i] = (ll)suc[u][i + 1] * val[u][i] % mod;
	int m = 0;
	for (int i = h[u]; ~i; i = ne[i]) {
		int v = e[i];
		if (v == fa) continue;
		m++;
		g[v] = (ll)g[u] * pre[u][m - 1] % mod * suc[u][m + 1] % mod;
		g[v] = (g[v] + 1) % mod;
		dfs2(v, u);
	}
}

int main() {
	memset(h, -1, sizeof h);
	cin >> n >> mod;
	for (int i = 1, u, v; i < n; i++) {
		cin >> u >> v;
		add(u, v), add(v, u);
	}
	dfs1(1, 0);
	dfs2(1, 0);
	for (int i = 1; i <= n; i++) cout << ans[i] << endl;
	return 0;
}
```

---

## 作者：Endt (赞：1)

# Subtree-题解

### 题意

给定一棵 $N$ 个节点的树，现在需要将每一个节点染成黑色或白色。

对于每一个节点 $i$，求强制把第 $i$ 节点染成黑色的情况下，所有的黑色节点组成一个联通块的染色方案数，答案对 $M$ 取模。

### 分析

树上求方案数，而且要求每一个顶点对应的方案数，~~还是在 AT 的 DP 列表里的~~，考虑进行换根DP。

### 求解

第一步，先求出以第 $i$ 个点为根的子树中，根节点是黑色的黑连通块数量，就是一个普通的树上 DP，状态从子节点转移，结果储存在 $dp_i$ 里。

```cpp
void DP(int x,int fa){
    for(int i:s[x]){
        if(i!=fa){
            DP(i,x);
            dp[x]=dp[x]*(dp[i]+1)%m;//子树全白也是一种情况
        }
    }
}
```

第二步，求出第 $i$ 个节点通过它的父亲节点，与此节点的兄弟节点们及其子孙节点和此节点的祖先节点们，所能构成的黑连通块的总数，结果存在 $pd_i$ 里。这里有换根的思想。首先它的父亲肯定是黑的，这时把它的父亲节点视作根节点，把它自己及其子树删去，和第一步同样的方法求解。

```cpp
void PD(int x,int fa){
    Int t=pd[x];
    for(int i:s[x])//它的祖先们转移过来的
        if(i!=fa)
            pd[i]=pd[i]*t%m;
    t=1;
    for(int i:s[x])//它左侧的兄弟们转移过来的
        if(i!=fa)
            pd[i]=pd[i]*t%m,t=t*(dp[i]+1)%m;
    t=1;
    std::reverse(s[x].begin(),s[x].end());
    for(int i:s[x])//它右侧的兄弟们转移过来的
        if(i!=fa)
            pd[i]=pd[i]*t%m,t=t*(dp[i]+1)%m;
    for(int i:s[x])if(i!=fa){
        ++pd[i];
        PD(i,x);
    }
}
```

显而易见的，步骤一和步骤二中的答案互不相干，可以让节点上方随意排布，节点下方随意排布。根据乘法原理，答案即为 $dp_i\cdot pd_i$。

### 代码

```cpp
#include<bits/stdc++.h>

#define  Int  long long int
#define  Tem  template
#define  Pub  public

using std::min;using std::max;

int n;Int m;

std::vector<int> s[100005];
Int dp[100005],pd[100005];

void DP(int x,int fa){
    for(int i:s[x]){
        if(i!=fa){
            DP(i,x);
            dp[x]=dp[x]*(dp[i]+1)%m;
        }
    }
}
void PD(int x,int fa){
    Int t=pd[x];
    for(int i:s[x])
        if(i!=fa)
            pd[i]=pd[i]*t%m;
    t=1;
    for(int i:s[x])
        if(i!=fa)
            pd[i]=pd[i]*t%m,t=t*(dp[i]+1)%m;
    t=1;
    std::reverse(s[x].begin(),s[x].end());
    for(int i:s[x])
        if(i!=fa)
            pd[i]=pd[i]*t%m,t=t*(dp[i]+1)%m;
    for(int i:s[x])if(i!=fa){
        ++pd[i];
        PD(i,x);
    }
}

int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)dp[i]=pd[i]=1;
    for(int i=1,x,y;i<n;++i){
        scanf("%d%d",&x,&y);
        s[x].push_back(y);
        s[y].push_back(x);
    }
    DP(1,0);PD(1,0);
    for(int i=1;i<=n;++i){
        printf("%lld\n",dp[i]*pd[i]%m);
    }
    return 0;
}
```

---

## 作者：whhsteven (赞：1)

## 题目链接

洛谷：[AT4543](https://www.luogu.com.cn/problem/AT4543)

AT：[AT4543/DP_V](https://atcoder.jp/contests/dp/tasks/dp_v)

---

## 题意简述

给定一棵树，用黑白两色染色。

对于每一个点，求强制给该点染上黑色时，整棵树上的黑点构成一个连通块的染色方案数。

答案取模，模数输入给出。

---

## 题解

题目要求我们求出对每一个点强制染黑的情形的答案，故考虑采用换根 DP。

先计算钦定 $1$ 号点为根并染黑的方案数。

设 $f_u$ 表示将 $u$ 号点染黑，且其子树内黑点构成连通块的方案数。易见，对于其每一个子节点 $v$，都有染黑和不染黑两种选择：染黑则方案数为 $f_v$；不染黑则 $v$ 的整棵子树都只能为白，方案数为 $1$。故

$$f_u = \prod_{v \in \mathrm{son}_u} (f_v + 1)$$

当 $u$ 为叶子时，显然 $f_u = 1$，与初始化要求相同。

现在考虑换根。不难理解，换根时消去 $u$ 对 $\mathrm{fa}_u$ 的贡献，再将 $\mathrm{fa}_u$ 的贡献乘到 $u$ 上。

- 消去 $u$ 对 $\mathrm{fa}_u$ 的贡献：

  $$f^\prime_{\mathrm{fa}_u} = \frac{f_{\mathrm{fa}_u}}{f_u + 1}$$

- 将 $\mathrm{fa}_u$ 的贡献乘到 $u$ 上：

  $$f^\prime_u = f_u \times (f^\prime_{\mathrm{fa}_u} + 1)$$

不过出现了一个小问题：模数不保证是质数，所以不能用直接乘逆元的方式来消去贡献。

这里，对于每一个点 $u$，处理出 $(f_{v \in \mathrm{son}_u} + 1)$ 的前缀积和后缀积，即可解决求出消去一个子树贡献后的答案的问题。

---

## 代码

```cpp
#include<bits/stdc++.h>
#define eb emplace_back

using namespace std;

namespace acah
{
	using ll = long long;
	
	constexpr int maxn = 1e5 + 7;
	
	int N, p;
	vector<int> T[maxn], sn[maxn];
	ll f[maxn], ans[maxn];
	vector<ll> pf[maxn], sf[maxn];
	
	void dp(int u, int fa)
	{
		f[u] = 1;
		
		for(int v : T[u]) {
			if(v == fa) continue;
			sn[u].eb(v);
			dp(v, u);
			(f[u] *= (f[v] + 1)) %= p;
		}
		
		pf[u].eb(1); // pf[u][0] = 1
		for(int i = 0, bd = sn[u].size(); i < bd; i++)
			pf[u].eb(pf[u][i] * (f[sn[u][i]] + 1) % p);
		
		sf[u].eb(1);
		for(int i = sn[u].size() - 1, c = 0; i >= 0; i--, c++)
			sf[u].eb(sf[u][c] * (f[sn[u][i]] + 1) % p);
		reverse(sf[u].begin(), sf[u].end());
	}
	
	void solve(int u, ll fv)
	{
		ans[u] = f[u] * (fv + 1) % p;
		
		for(int i = 0, bd = sn[u].size(); i < bd; i++) {
			int v = sn[u][i];
			ll l = pf[u][i], r = sf[u][i + 1];
			solve(v, l * r % p * (fv + 1) % p);
		}
	}
	
	int work()
	{
		scanf("%d%d", &N, &p);
		for(int i = 1, u, v; i < N; i++) {
			scanf("%d%d", &u, &v);
			T[u].eb(v), T[v].eb(u);
		}
		
		dp(1, 0), solve(1, 0);
		
		for(int i = 1; i <= N; i++)
			printf("%lld\n", ans[i]);
		
		return 0;
	}
}

int main() {return acah::work();}
```

这里，因为要使用儿子的编号，所以用基于范围的 `for` 循环并不如枚举下标简便。

---

## 作者：MortisM (赞：1)

题意：有一棵 $n$ 个节点的数，你要给它黑白染色，但是限定染黑的节点必须连在一起（即形成一个连通块），对于每一个 $i=1...n$，问如果强制将 $i$ 节点染黑的染色方案数。（注意：模数不保证为质数）

数据范围：$n\leq 10^5$。

$O(N)$ 的 DP 且要对于每个 $i$ 都求的要么就是一次全算出来，要么是换根 DP。

你需要分两类，即 $u$ 子树里（不含 $u$）和除了 $u$ 的子树（含 $u$）。

对这两类分别使用 $f(u),g(u)$ 来表示强制 $u$ 染色的代价。

首先考虑 $f(u)$ 的转移，这是简单的：

$$
f(u)=\prod_{v\in son(u)}(f(v)+1)
$$

这个式子就表示每个子树都可以染或不染，染就 $f(v)$ 种，不染就 1 种。

但是 $g(u)$ 的转移就需要从 $f(u)$ 进行倒推了：

$$
g(u)=g(p)\cdot\prod_{v\in son(p)}(f(v)+1)+1
$$

这个转移分成 2 类：

+ 父亲及祖先（$g(p)$）
+ 兄弟的子树（$\prod_{v\in son(p)}(f(v)+1)$）

剩下的 $1$ 就是啥都不染的代价。

这样就可以得到一个 $O(N^2)$ 的做法了。

**一些优化:**

考虑到复杂度瓶颈为枚举兄弟节点，容易想到一个优化就是 $\prod_{v\in son(p)}(f(v)+1)=\frac{f(p)}{f(u)+1}$，但是不能直接用乘法逆元搞。

仔细想想维护前缀和后缀积就行，这样时间复杂度 $O(N)$。

**[代码](https://atcoder.jp/contests/dp/submissions/33886306)**

---

## 作者：Z1qqurat (赞：0)

* 当作是换根 dp 模板题。首先转化一下，相当于求每个点所在的连通块个数。

* 树上问题，速速考虑扔到子树上考虑，首先定义 $f_u$ 表示以 $u$ 为根的子树中包含 $u$ 的连通块有多少个（显然这是包含单点 $u$ 的），然后考虑经典状态 $g_u$ 表示包含 $u$ 的 $u$ 为根的子树之外的连通块个数。

* 那么转化为了经典换根 dp 问题，$f_u$ 的转移很简单，考虑枚举儿子 $v$，那么我要么选择 $v$ 子树内包含 $u$  的一个连通块，方案数是 $f_u$，要么不选 $u$ 子树内任何点，方案数为 $1$，所以有：

$$
f_u = \prod\limits_{v \in son_u} (f_v + 1)
$$

* 接下来考虑怎么维护 $g_u$，注意 $g_u$ 也算上了单点 $u$。如果 $u$ 要被一个不在子树内的连通块覆盖，那么肯定需要选 $fa_u$（除去只选单点 $u$ 的情况），那么 $fa_u$ 怎么选？一部分是我 $fa_u$ 还是往外跳，$g_{fa_u}$；另一部分就是选择 $u$ 的兄弟 $v$ 的子树，也就是将 $f_v + 1$ 连乘。但是你想，我怎么快速地得到这个连乘？如果我一开始就把所有的 $fa_u$ 都乘起来，每次都除掉 $f_u + 1$，但是模数 $P$ 不是质数，这不行！**考虑一个换根 dp 常见技巧，适用于需要取极值/连乘等所有情况**：将 $fa_u$ 的所有儿子拿出来，然后做一个前缀/后缀积，那么如果是 $i$ 号儿子，就可以用 $pre_{i - 1} \times suf_{i + 1}$ 得到它所有兄弟贡献的连乘了。所以说：

$$
g_u = \prod\limits_{v \in brother_u} (f_v + 1) \times g_{fa} + 1
$$

（最后那个 $1$ 是只选了单点 $u$ 的情况！）

* 那么真正的答案怎么计算？$f_u \times g_u$。

* 接下来是一些代码实现的坑！是我自己错过好几次的呜啊！
  * 换根 dp 求前缀/后缀积的时候一定要把 $u$ 的儿子单独拿出来！要不然你想一想，我们建的是双向边，那么 $u$ 的邻接表中有 $u$ 的儿子还有 $u$ 的父亲，我们自然不会用 $u$ 去更新 $fa_u$，循环到 $fa_u$ 的时候肯定会跳过它，那么就会导致邻接表中儿子不是一段连续的区间，就会挂掉。
  * 如果你暂时存 $u$ 的儿子的是一个全局的变量，那么一定记得再最后整体地 ```dfs2(v, u)``` 千万不能用 $son_i$ 来得到 $v$，因为你前面将 $u$ 的其他儿子转移的时候会在函数中修改了 $son$ 的值！所以一定要用原邻接表来遍历 $v$！
  
奉上我自己写的代码！

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <queue>
#include <vector>
#define ll long long
#define pii pair<int, int>
#define mr make_pair
using namespace std;
const int N = 1e5 + 5;
int n, son[N];
ll P, f[N], g[N], pre[N], suf[N];
vector <int> G[N];

void dfs1(int u, int fa) {
	f[u] = 1;
	for (int i = 0; i < G[u].size(); ++i) {
		int v = G[u][i];
		if (v == fa)
			continue;
		dfs1(v, u);
		f[u] = f[u] * (f[v] + 1) % P;
	}
	return ;
}

void dfs2(int u, int fa) {
	if (G[u].size() == 1 && G[u][0] == fa)
		return ;
	int num = 0;
	for (int i = 0; i < G[u].size(); ++i) {
		int v = G[u][i];
		if (v == fa)
			continue;
		son[++num] = v;
	}
	pre[0] = suf[num + 1] = 1;
	for (int i = 1; i <= num; ++i) {
		int v = son[i];
		pre[i] = pre[i - 1] * (f[v] + 1) % P;
	}
	for (int i = num; i >= 1; --i) {
		int v = son[i];
		suf[i] = suf[i + 1] * (f[v] + 1) % P;
	}
	for (int i = 1; i <= num; ++i) {
		int v = son[i];
		g[v] = (pre[i - 1] * suf[i + 1] % P * g[u] % P + 1) % P;
	}
	for (int i = 0; i < G[u].size(); ++i) {
		int v = G[u][i];
		if (v == fa)
			continue;
		dfs2(v, u);
	}
	return ;
}

int main() {
	scanf("%d %lld", &n, &P);
	for (int i = 1; i < n; ++i) {
		int u, v;
		scanf("%d %d", &u, &v);
		G[u].push_back(v), G[v].push_back(u);
	}
	dfs1(1, -1);
	g[1] = 1;
	dfs2(1, -1);
	for (int i = 1; i <= n; ++i) {
		// cout << f[i] << ' ' << g[i] << "\n";
		ll ans = f[i] * g[i] % P;
		printf("%lld\n", ans);
	}
	return 0;
}
```

---

## 作者：liaiyang (赞：0)

很明显的换根 dp。

我们设 $dp1_x$ 表示将 $x$ 染成黑色时，子树内所有黑色节点构成一个连通块的方案数，$dp2_x$ 表示将 $x$ 染成黑色时，子树外所有黑色节点构成一个连通块的方案数。

转移方程为
$$dp1_x=\prod\limits_{i\in son_x}dp1_i+1$$
$$dp2_x=(dp2_{fa}\times\prod\limits_{i\in brother_x}dp1_i+1)+1$$

由于模数可能不是质数，我们预处理前后缀积。

时间复杂度 $O(n)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define min(a,b) (a<b?a:b) 
#define P pair<int,int>
#define x first
#define y second
#define modd(x) (((x)%mod+mod)%mod) 
#define rd read()
#define lowbit(x) ((x)&(-x))
mt19937 rnd(time(0));
inline int read(int u=0, char c=getchar(), bool f=false){
    for (;!isdigit(c);c=getchar()) f|=c=='-';
    for (;isdigit(c);c=getchar()) u=(u<<1)+(u<<3)+c-'0';
    return f?-u:u;
}
inline void wt(int x){
    if(x<0) x=-x,putchar('-');
    if(x>9) wt(x/10);
    putchar(x%10+48);
}
inline void wt(int x,char k){wt(x),putchar(k);}
const int inf=~0U>>1,linf=~0ULL>>1; 
const int N=1e5+10;
int n,mod,f1[N],f2[N],sum1[N],sum2[N],num;
vector<int>e[N];
void dfs(int x,int fa){
    f1[x]=1;
    for(int i:e[x]){
        if(i==fa) continue;
        dfs(i,x);
        sum1[i]=f1[x];
        f1[x]=f1[x]*(f1[i]+1)%mod;
    }
    num=1;
    for(int i=e[x].size()-1;i>=0;i--){
        if(e[x][i]==fa) continue;
        sum2[e[x][i]]=num;
        num=num*(f1[e[x][i]]+1)%mod;
    }
}
void dfs2(int x,int fa){
    f2[x]=(f2[fa]*sum1[x]%mod*sum2[x]%mod+1)%mod;
    for(int i:e[x]) if(i!=fa) dfs2(i,x);
}
main(){
    n=rd,mod=rd;
    for(int i=1;i<n;i++){
        int x=rd,y=rd;
        e[x].push_back(y);
        e[y].push_back(x);
    }f2[1]=1;
    dfs(1,0);
    dfs2(1,0);
    for(int i=1;i<=n;i++) wt(f1[i]*f2[i]%mod,'\n');
    return 0;
}
```

---

## 作者：OIer_ACMer (赞：0)

~~本子的题不好做呀。~~

------------
注意：本题由于涉及到的知识比较简单，笔者不会将证明以及原理讲得太过细节，望各位悉知！

------------
## 警钟敲烂：
这道题在做的时候**一定不能将树上搜索的部分写错**~~不然就会像我一样改三十分钟才过~~。

------------
## 大致思路：
我们首先看到题目要求**在一个点涂上黑色且计算在此基础之上有多少种涂色方法是的所有黑色的点形成一个连通块**。这种换点求结果的操作很显然要用树上 DP 中的**换根 DP** 来做。

我们首先先来考虑一下怎么用树形 DP 设计状态，我们设 $dp[x]$ 表示强制将节点 $x$ 染色，有多少种将黑色的点炼成连通块的方案。**根据乘法原理可知，想要知道父亲节点有多少种方案，就需要把子节点的答案加上 $1$ 相乘就可以得到**，至于加 $1$ 的原因是因为我们**要考虑到这棵子树不选的情况**则我们很显然可以得到方程：

$dp[x] =\prod {dp[y]+1}~(y\in \text{son}~u)$。

但是考虑到根的答案处理出来后，其他节点的答案还没有处理出来。由于 $n \le 10^5$，**我们显然不能对每个节点设根做一遍 dfs，所以考虑换根 dp**。由于在换根之后根节点除了这个子树以外的部分都算这个点的子树，转移方法同上，那我们思考后又可得:

$dp1[y] = dp[y] \times (dp[x] \div (dp[y] + 1) + 1)$。

然而，我们不能忘记，这道题要取模！！！所以我们稍微改一改公式：

$dp1[y] = dp[y] \times (dp[x] \div (dp[y] + 1) + 1) \bmod m$。

我们知道，**计算方案不能出现小数点这种奇葩情况，所以我们可以考虑用逆元来解决这个问题**。但是，各位别着急走，我们**并不知道 $m$ 是否为素数**，这意味着我们的计划泡汤了。显然不能再算一遍，那我们只能想一个 $\log(n)$ 以下的方法处理。

想一想，我们能用什么方法解决时间复杂度大的问题呢？除了吸氧大法，我唯一知道的就只有**将一个个数据变成前缀**或者**一些别的 DP 专属的优化方法**（例如四边形优化，滚动数组之类的），但是本蒟蒻只会做前缀乘吃累的操作，所以我们考虑**同时做前缀乘和后缀乘**（这个乘法就是一开始的第一个方程），计算对子树的贡献**只需要将前缀乘和后缀乘相乘即可**（这时小学数学，我就不多说了），虽然多了几个 $O(n)$，但是总复杂度不变。空间上，因为子树根的个数为 $O(n)$，所以空间复杂度也为 $O(n)$。

解决这些问题后，我们就可以愉快的码代码了！

------------
## 代码如下：

```c++
#include <bits/stdc++.h>
using namespace std;
#define int long long
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
int n, mod, cnt;
int dp[100005], pre[400005], sub[400005];
basic_string<int> f[100005];
void dfs1(int x, int fa)
{
    dp[x] = 1;
    for (int y : f[x])
    {
        if (y == fa)
        {
            continue;
        }
        dfs1(y, x);
        dp[x] = (dp[x] * (dp[y] + 1)) % mod;
    }
}
void dfs(int x, int fa, int las)
{
    dp[x] = dp[x] * (las + 1) % mod;
    int st = ++cnt, en, o = 0;
    cnt = cnt + f[x].size() + 1;
    pre[st - 1] = 1, sub[cnt - 1] = 1;
    en = cnt - 2;
    for (int i = 0; i < f[x].size(); i++)
    {
        int y = f[x][i];
        if (y == fa)
        {
            pre[st + o] = pre[st + o - 1] * (las + 1) % mod;
        }
        else
        {
            pre[st + o] = pre[st + o - 1] * (dp[y] + 1) % mod;
        }
        o++;
    }
    o = 0;
    for (int i = f[x].size() - 1; ~i; i--)
    {
        int y = f[x][i];
        if (y == fa)
        {
            sub[en - o] = sub[en - o + 1] * (las + 1) % mod;
        }
        else
        {
            sub[en - o] = sub[en - o + 1] * (dp[y] + 1) % mod;
        }
        o++;
    }
    for (int i = 0; i < f[x].size(); i++)
    {
        int y = f[x][i];
        if (y == fa)
        {
            continue;
        }
        dfs(y, x, (pre[st + i - 1] * sub[st + i + 1]) % mod); 
    }
}
signed main()
{
    n = read();
    mod = read();
    // cout << "n=" << n << ' ' << "mod=" << mod << endl; 
    for (int i = 1; i < n; i++)
    {
        int u = read(), v = read();
        f[u] += v;
        f[v] += u;
    }
    dfs1(1, 0);
    dfs(1, 0, 0);
    for (int i = 1; i <= n; i++)
    {
        cout << dp[i] % mod << endl;
    }
    return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/122427367)

---

