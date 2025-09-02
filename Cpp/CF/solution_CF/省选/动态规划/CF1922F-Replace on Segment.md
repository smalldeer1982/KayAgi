# Replace on Segment

## 题目描述

You are given an array $ a_1, a_2, \dots, a_n $ , where each element is an integer from $ 1 $ to $ x $ .

You can perform the following operation with it any number of times:

- choose three integers $ l $ , $ r $ and $ k $ such that $ 1 \le l \le r \le n $ , $ 1 \le k \le x $ and each element $ a_i $ such that $ l \le i \le r $ is different from $ k $ . Then, for each $ i \in [l, r] $ , replace $ a_i $ with $ k $ .

In other words, you choose a subsegment of the array and an integer from $ 1 $ to $ x $ which does not appear in that subsegment, and replace every element in the subsegment with that chosen integer.

Your goal is to make all elements in the array equal. What is the minimum number of operations that you have to perform?

## 样例 #1

### 输入

```
3
3 2
1 2 1
6 3
1 2 3 1 2 3
12 3
3 1 3 1 2 1 1 2 3 1 1 3```

### 输出

```
1
2
2```

# 题解

## 作者：王熙文 (赞：17)

感觉大部分（也许是所有）题解都没说到点上，于是我来发一篇。

## 思路

结论：存在一种最优解使得区间之间没有相交且不包含的关系。

证明：考虑将连续相同的数缩成一个点，那么操作一次相当于将这个区间缩成一个点，如果能证明这样操作答案不变，就证明了结论（不会有区间与一个长度为 $1$ 的区间相交且不包含）。考虑归纳证明，根据最优解的次数从小到大归纳。如果之后存在某次操作的区间包含了当前区间的一部分，那么这个的答案相当于将所有都操作了的数列加上一个点（因为根据归纳证明，若数都相同则可以缩成一个）。而加上一个点一定不如不加，所以这样操作不优。

因此操作的区间形成了树形结构，可以使用区间 dp。设 $dp_{i,j,k,0/1}$ 表示将区间 $[l,r]$ 全变成不是/是 $k$ 的数需要的操作次数。首先判断区间是否已经满足了。否则根据当前区间是否操作可以得到转移：

$dp_{i,j,k,0}=\min(\min_{l=i}^{j-1} dp_{i,l,k,0}+dp_{l+1,j,k,0},\min_{l=1}^x dp_{i,j,l,0}+1)$

这个转移方程的意思是，如果当前区间不操作，那么它一定需要分成两半，并分别操作。否则，当前区间会变成一个不为 $k$ 的数 $l$，在此之前，区间需要满足全都不为 $l$，需要的次数为 $dp_{i,j,l,0}$。

$dp_{i,j,k,1}=\min(\min_{l=i}^{j-1} dp_{i,l,k,1}+dp_{l+1,j,k,1},dp_{i,j,k,0}+1)$

这个转移方程和上面的类似，如果当前区间不操作，则它需要分成两半分别操作。否则，当前区间操作的前提是区间所有数都不为 $k$，次数即为 $dp_{i,j,k,0}$。

在第一个转移方程中存在互相转移的情况。但是可以发现只有 dp 值最小的才会更新别人，而它不会被别人更新，所以直接先求出来第一部分的 dp 值，再求出最小值，用它加一更新别人。

这样暴力做的复杂度是 $\mathcal O(n^3x)$ 已经可以通过，不过这个做法还可以优化。

发现对于一个左端点，使用特定次数操作使得满足条件的右端点存在单调性，所以考虑交换下标和值。设 $dp_{i,j,k,0/1}$ 表示左端点为 $i$、操作小于等于 $j$ 次能使区间全变成不是/是 $k$ 的数的最大的右端点。转移和上面类似。这样做的好处是，状态和转移中都有关于答案大小的枚举，而答案大小并不很大。考虑将序列中出现次数最小的数作为最后相等的数，它的出现次数 $\le \dfrac{n}{x}$，那么将它把序列划分的次数${}+1$ 段都操作一次，次数 $\le \dfrac{n}{x}+1$。所以答案的上界就是这个数。复杂度为 $\mathcal O(nx+\dfrac{n^3}{x})$。

## 代码

暴力的代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int a[110];
int dp[110][110][110];
int ans[110][110][110];
int main()
{
	int t; cin>>t; while(t--)
	{
		cin>>n>>m;
		for(int i=1; i<=n; ++i) cin>>a[i];
		for(int len=1; len<=n; ++len)
		{
			for(int i=1; i<=n-len+1; ++i)
			{
				int j=i+len-1;
				for(int k=1; k<=m; ++k)
				{
					bool flag=1;
					for(int l=i; l<=j; ++l)
					{
						if(a[l]==k) { flag=0; break; }
					}
					if(flag) { dp[i][j][k]=0; continue; }
					dp[i][j][k]=1e9;
					for(int l=i; l<j; ++l) dp[i][j][k]=min(dp[i][j][k],dp[i][l][k]+dp[l+1][j][k]);
				}
				for(int k=1; k<=m; ++k)
				{
					bool flag=1;
					for(int l=i; l<=j; ++l)
					{
						if(a[l]!=k) { flag=0; break; }
					}
					if(flag) { ans[i][j][k]=0; continue; }
					ans[i][j][k]=1e9;
					for(int l=i; l<j; ++l) ans[i][j][k]=min(ans[i][j][k],ans[i][l][k]+ans[l+1][j][k]);
				}
				int in=1e9;
				for(int k=1; k<=m; ++k) in=min(in,dp[i][j][k]);
				for(int k=1; k<=m; ++k) dp[i][j][k]=min(dp[i][j][k],in+1),ans[i][j][k]=min(ans[i][j][k],dp[i][j][k]+1);
			}
		}
		int aans=1e9;
		for(int i=1; i<=m; ++i) aans=min(aans,ans[1][n][i]);
		cout<<aans<<'\n';
	}
	return 0;
}
```

优化后的代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int a[110];
int dp[110][110][110];
int ans[110][110][110];
int lst[110][110],llst[110][110];
int main()
{
	int t; cin>>t; while(t--)
	{
		cin>>n>>m;
		for(int i=1; i<=n; ++i) cin>>a[i];
		memset(dp,0,sizeof(dp));
		memset(ans,0,sizeof(ans));
		int lim=n/m+1,aans=1e9;
		for(int i=1; i<=m; ++i) lst[n+1][i]=llst[n+1][i]=n;
		for(int i=n; i>=1; --i)
		{
			for(int j=1; j<=m; ++j)
			{
				if(a[i]==j) lst[i][j]=i-1,llst[i][j]=llst[i+1][j];
				else lst[i][j]=lst[i+1][j],llst[i][j]=i-1;
			}
			for(int j=0; j<=lim; ++j)
			{
				for(int k=1; k<=m; ++k)
				{
					if(j==0) { dp[i][j][k]=lst[i][k],ans[i][j][k]=llst[i][k]; continue; }
					for(int l=0; l<j; ++l)
					{
						if(dp[i][l][k]==n) dp[i][j][k]=n;
						else dp[i][j][k]=max(dp[i][j][k],dp[dp[i][l][k]+1][j-l][k]);
						if(ans[i][l][k]==n) ans[i][j][k]=n;
						else ans[i][j][k]=max(ans[i][j][k],ans[ans[i][l][k]+1][j-l][k]);
					}
				}
				if(j!=0)
				{
					int ax=0;
					for(int k=1; k<=m; ++k) ax=max(ax,dp[i][j-1][k]);
					for(int k=1; k<=m; ++k)
					{
						dp[i][j][k]=max(dp[i][j][k],ax),ans[i][j][k]=max(ans[i][j][k],dp[i][j-1][k]);
						dp[i][j][k]=lst[dp[i][j][k]+1][k];
						ans[i][j][k]=llst[ans[i][j][k]+1][k];
					}
				}
				if(i==1)
				{
					for(int k=1; k<=m; ++k) if(ans[i][j][k]==n) aans=min(aans,j);
				}
			}
		}
		cout<<aans<<'\n';
	}
	return 0;
}
```

---

## 作者：Eraine (赞：17)

编号：CF1922F

tag：区间 DP

比较典的一道题叭。

真的有 $*2500$ 吗？\fn\fn\fn

这里默认 $n,x$ 同阶。

首先设 $f_{l,r,j}$ 为区间 $[l,r]$ 颜色都为 $j$ 的最小操作数。

由于题目的操作是从一个区间内选出没有出现过的颜色，所以还要开一个数组 $g_{l,r,j}$ 表示在区间 $[l,r]$ 中没出现出现过 $j$ 的方案数。

考虑 $f$ 数组转移。第一种是直接从 $g$ 转移到 $f$，即对没出现过 $j$ 的区间 $[l,r]$ 直接耗费 $1$ 全部变成 $j$。即：

$$f_{l,r,j}\gets g_{l,r,j}+1$$

第二种是区间合并，只需枚举中转点 $mid$ 即可实现。即：

$$f_{l,r,j}\gets f_{l,mid,j}+f_{mid+1,r,j}[mid\in[l,r)]$$

考虑 $g$ 数组转移。其实和 $f$ 数组转移大同小异。第一种从 $g$ 转移而来，但不过 $g$ 数组要变成没出现过 $k,(k\neq j)$ 的最小方案数。即：

$$g_{l,r,k}\gets g_{l,r,j}+1[j\neq k]$$

第二种也是找到中转点 $mid$ 合并。即：

$$g_{l,r,j}\gets g_{l,mid,j}+g_{mid+1,r,j}[mid\in[l,r)]$$

状态数 $\Theta(n^3)$，每种状态都有 $4$ 类的 $\Theta(n)$ 转移。

$\Theta(n^4)$。

考场代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=105;
int n,x,a[N],f[N][N][N],g[N][N][N],h[N][N][N];
int solve(){
	memset(f,0x3f,sizeof f);
	memset(g,0x3f,sizeof g);
	memset(h,0x3f,sizeof h);//h 为辅助数组
	scanf("%d%d",&n,&x);
	for(int i=1;i<=n;i++){//单独一个情况特判
		scanf("%d",&a[i]);
		for(int j=1;j<=x;j++){
			if(j!=a[i]){
				g[i][i][j]=0;
				f[i][i][j]=1;
			}
		}
		g[i][i][a[i]]=1;
		f[i][i][a[i]]=0;
	}
	for(int len=2;len<=n;len++){
		for(int l=1;l+len-1<=n;l++){
			int r=l+len-1;
			for(int j=1;j<=x;j++){
				for(register int mid=l;mid<r;++mid){//中转点转移
					f[l][r][j]=min(f[l][r][j],f[l][mid][j]+f[mid+1][r][j]);
					h[l][r][j]=min(h[l][r][j],g[l][mid][j]+g[mid+1][r][j]);//h 为 g 的辅助转移数组
				}
				f[l][r][j]=min(f[l][r][j],h[l][r][j]+1);//f 数组从 g 转移
				for(register int k=1;k<=x;++k){
					if(k==j){
						continue;
					}
					g[l][r][k]=min(g[l][r][k],h[l][r][j]+1);//g 数组从辅助转移数组转移
				}
			}
			for(int j=1;j<=x;j++){
				g[l][r][j]=min(g[l][r][j],h[l][r][j]);//粘贴原来的
			}
		}
	}
	int res=n;
	for(int i=1;i<=x;i++){
		res=min(res,f[1][n][i]);
	}
	return res;
}
int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		printf("%d\n",solve());
	}
	return 0;
}
```
各位看官点个赞再走吧 awa

---

## 作者：cmk666 (赞：12)

来点复杂度更优的做法。

一眼 dp，正常的区间 dp 方式是：记 $dp_{0/1,l,r,c}$ 表示把区间 $[l,r]$ 变成（$0$：$c$，$1$：$\ne c$）的最小操作次数。

考虑交换下标和值，即将 dp 状态变成：记 $dp_{0/1,i,l,c}$ 表示在 $i$ 次操作内，能把左端点为 $l$ 的区间变成（$0$：$c$，$1$：$\ne c$），右端点最远能是多少。

$i=0$ 的初值是简单的，扫一遍就行。

考虑 $dp_0$ 的转移。显然有 $dp_{0,i,l,c}=dp_{1,i-1,l,c}$。同时我们也可以对 $i$ 这一维做背包合并状物，即：$dp_{0,i,l,c}=\max_{0\le j\le i}dp_{0,i-j,dp_{0,j,l,c}+1,c}$。二者取 $\max$ 即为结果。

同理，对于 $dp_1$ 的转移，也有类似的合并：$dp_{1,i,l,c}=\max_{0\le j\le i,c'\ne c}dp_{1,i-j,dp_{0,j,l,c'}+1,c}$。这里不用像 $dp_0$ 一样考虑另外一个转移的原因是已经被这个包含了。$c'\ne c$ 的限制可以直接枚举 $j$ 后记录 $dp_{0,j,l,c'}$ 的前两大解决，是简单的。

我们一直增加 $i$，直到出现 $dp_{0,i,1,c}=n$，那么答案 $ans=i$。

然后你就会发现：状态有三维 $i,l,c$，转移还要枚举 $j$，这不还是四次方的？别急。

首先我们来证明一个简单的引理：$ans\le\left\lfloor\dfrac nx\right\rfloor+1$。考虑所有颜色中出现最少的，显然它的出现次数  $cnt\le\left\lfloor\dfrac nx\right\rfloor$，反证法易得。那么剩下的元素被割成至多 $cnt+1\le\left\lfloor\dfrac nx\right\rfloor+1$ 段，我们把每段变成这种颜色也只要使用 $\left\lfloor\dfrac nx\right\rfloor+1$ 次操作，因此 $ans$ 一定不超过 $\left\lfloor\dfrac nx\right\rfloor+1$。

那么来分析复杂度：$i,j$ 是 $O(ans)$ 的，$l$ 是 $O(n)$ 的，$c$ 是 $O(x)$ 的，总复杂度 $O(ans^2\cdot n\cdot x)=O\left(\dfrac{n^3}x\right)$。

[submission](//codeforces.com/contest/1922/submission/242678239)。变量名可能有点不一样。

---

## 作者：_sunkuangzheng_ (赞：10)

- [Replace on Segment](https://codeforces.com/contest/1922/problem/F) 

考虑 dp。设 $f_{i,j,p}$ 表示把区间 $[i,j]$ 全部推平成 $p$ 的最小代价，好像有简单的区间 dp：$f_{i,j,p} = \min\{f_{i,k,p} + f_{k+1,j,p}\}$，但这是错的。考虑 $[1,4,2,4,3,4](x=5)$，将 $[1,6]$ 推平成 $4$，如果像刚才那样转移答案是 $3$，实际上先将 $[1,6]$ 推平成 $5$，再推平成 $4$ 答案是 $2$。这启示我们设状态 $g_{i,j,p}$ 表示区间 $[i,j]$ 不包含 $p$ 的最小操作次数。$f_{i,j,p}$ 的转移途径是 $g_{l,r,p}+1$，其中 $l=i+[a_i=p],r = j-[a_j=p]$，要加减是因为如果不修改，边界会对 $g$ 多贡献答案。考虑 $g$ 的转移：$g_{i,j,p} = \min\{\min\limits_{p' \ne p}\{f_{i,j,p'}\},\min\limits_{i\le k < j}\{g_{i,k,p}+g_{k+1,j,p}\}\}$，含义是 $g_{i,j,p}$ 既可以通过区间直接推平为其他实现，也可以通过两边分别消除 $p$ 实现（第一种转移不能忽略，因为分开推平可能会忽略跨过分界点的区间，例如 $[2,1,1,2](x=3)$ 这个序列，$g_{1,4,2}$ 的值应该是 $1$，但是只考虑第二种转移会得到 $2$）。第一部分可以通过前后缀 $\min$ 求得。总时间复杂度 $\mathcal O(n^3x)$。[评测记录](https://codeforces.com/contest/1922/submission/242439675)。

---

## 作者：快乐的大童 (赞：3)

看到有区间操作，结合 $n\le 100$ 的数据范围，直接考虑区间 dp。

设 $f_{l,r,x}$ 表示将区间 $[l,r]$ 全部替换成 $x$ 的最小步数。

首先有 $f_{l,r,x}=\max_{p=l}^{r-1}f_{l,p,x}+f_{p+1,r,x}$，但这无法将该状态下的所有的情况都转移到，所以考虑再设一个 $g_{l,r,x}$ 表示将区间 $[l,r]$ 的所有 $x$ 全部消除的最小步数，则存在转移 $f_{l,r,x}= g_{l,r,x}+1$，表示将不存在 $x$ 的区间 $[l,r]$ 通过一次操作全部替换成 $x$。

接下来考虑转移 $g$，显然仍有 $g_{l,r,x}=\max_{p=l}^{r-1}g_{l,p,x}+g_{p+1,r,x}$。类似 $f$ 地，$g$ 也存在转移 $g_{l,r,x}= f_{l,r,k}(k\not=x)$。

但是发现 $f_{l,r,x}\leftarrow g_{l,r,x}\leftarrow f_{l,r,k}(k\not =x)\leftarrow g_{l,r,k}\leftarrow f_{l,r,x}(x\not=k)$，dp 状态之间的转移出现环形关系，无法直接递推。

>**We have to either somehow deal with them, or get rid of them. 我们要么以某种关系处理它们，要么把它们去掉。**——官方题解

我们不能像 [P3232 [HNOI2013] 游走](https://www.luogu.com.cn/problem/P3232) 一样采取第一种办法，所以这里我们采取第二种办法。

考虑裁剪掉一些对答案必然无影响的点，体现在该题中就是：

- 转移 $f$ 时将左右端点上 $a_i=x$ 的连续段删掉。即，将 $l$ 移动到其后第一个 $a_i\not=x$ 的 $i$，将 $r$ 移动到其前第一个 $a_i\not=x$ 的 $i$。
- 转移 $g$ 时将左右端点上 $a_i\not=x$ 的连续段删掉。即，将 $l$ 移动到其后第一个 $a_i=x$ 的 $i$，将 $r$ 移动到其前第一个 $a_i=x$ 的 $i$。

考虑当 $a_l=x$ 时会在转移 $f$ 时被删掉，否则会在转移 $g$ 的时候被删掉。此时转移 $f_{l,r,x}$ 时转移到该状态的 $g_{l',r',x}$ 的 $[l',r']\not=[l,r]$，由此证明了这样不会导致它们之间的转移关系成环。

这种转移式子显然是没法递推的，所以要用记搜。

时间复杂度 $O(n^4)$。

[code](https://codeforces.com/contest/1922/submission/242520237)

---

## 作者：Ether13 (赞：3)

简单区间 $dp$ 。我们发现数据范围很小，$n^3x$ 都可以过。而且每次都是对区间操作，自然而然的想到区间 $dp$ 。

那么我们设 $f_{i,j,k}$ 表示将区间 $[i,j]$  全部涂成 $k$ 的最小花费。

此时我们发现好像不太好转移，因为有一种转移方式为

**若 $i\sim j$ 不含有 $k$ 则可以通过一次操作使其全部转化为 $1$ 。**

于是想到设 $g_{i,j,k}$ 表示将区间 $[i,j]$ 转化为没有 $k$ 的最小花费。

上面两个 $dp$ 都是很好转移的。总转移方程如下：
$$
g_{i,j,k}=\min(\min_{l!=k}g_{i,j,l}+1,\min_{i\le l\le j}g_{i,l,k}+g_{l+1,j,k})\\
f_{i,j,k}=\min(\min_{l!=k}g_{i,j,l}+1,\min_{i\le l\le j}f_{i,l,k}+f_{l+1,j,k})
$$

初始值设为 $INF$ ；对于 区间 $[i,i]$ 将 $a[i]$ 对应的 $g$ 设为 $1$ ，否则设为 $0$ ；同理 $f_{i,i,a[i]}$ 设为 $0$

代码：

```cpp
const int N=110;
int a[N];
int f[N][N][N];//f[i][j][k]表示将i~j替换为k的最小花费
//f:min(g[i][j][l!=k])+1
//f:min(f[i][l][k]+f[l+1][j][k]); 
int g[N][N][N];//g[i][j][k]表示将i~j变得没有k的最小花费  
//g:min(g[i][l][k]+g[l+1][j][k])
//g:min(g[i][j][l!=k])+1
int main(){
	int t=read();
	while(t--){
		int n=read(),x=read();
		rep(i,0,n+1) rep(j,0,n+1) rep(k,0,x+1)
			f[i][j][k]=g[i][j][k]=INF;
		rep(i,1,n){
			rep(j,1,x) g[i][i][j]=0;
		}
		rep(i,1,n) a[i]=read(),f[i][i][a[i]]=0,g[i][i][a[i]]=1;
		rep(len,1,n){
			rep(i,1,n-len+1){
				int j=i+len-1,mn=INF;
				rep(k,1,x){
					rep(l,i,j)
						g[i][j][k]=min(g[i][l][k]+g[l+1][j][k],g[i][j][k]);
					mn=min(g[i][j][k],mn);
				}
				rep(k,1,x) g[i][j][k]=min(g[i][j][k],mn+1);
				rep(k,1,x){
					f[i][j][k]=min(f[i][j][k],mn+1);
					rep(l,i,j){
						f[i][j][k]=min(f[i][l][k]+f[l+1][j][k],f[i][j][k]); 
					}
				}
			}
		}
		int ans=INF;
		rep(i,1,x) ans=min(ans,f[1][n][i]);
		printf("%d\n",ans);
	}
    return 0;
}

```

---

## 作者：HNOIRPplusplus (赞：1)

## 题意

+ 有一个序列，长度为 $n$，值域为 $[1,x]$。
+ 每次选一个 $k (1\le k \le x)$，选出一个不包含 $k$ 的区间，令其元素全部变为 $k$。
+ 问序列中所有元素全部相同的最小操作次数。

## 思路

观察数据范围，注意到 $n$ 和 $x$ 都很小。介于 CodeForces 强大的评测能力，我们很自信的认为 $n$ 和 $x$ 即使四个乘在一起做时间复杂度也不至于有多炸。 

由于涉及区间修改，加上本体数据范围较小，我们采用区间 DP。

---

不难想到令 $dp_{i,j,k}$ 表示区间 $[i,j]$ 全部变成 $k$ 的方案数，因为这是题目直接要求的。但是你会发现这个状态设计根本无法转移，因为转移的条件是某一段不含有 $k$。怎么办呢？  
我们令 $pd_{i,j,k}$ ~~什么瞎起的名字~~ 表示区间 $[i,j]$ 全部没有 $k$ 的方案数。$pd$ 数组应当是很好求的。

仔细观察，我们获得如下转移：

$$pd_{i,j,k} = \min\limits^{j-1}_ {l=i} pd_{i,l,k} + pd_{l+1,j,k}$$

其原理显然，将一个区间划分成两段，每一段都不含有 $k$，那么这一整段也将不含有 $k$。

类似的，我们也有

$$dp_{i,j,k} = \min\limits^{j-1}_ {l=i} dp_{i,l,k} + dp_{l+1,j,k}$$

同时更加容易被忽略的，我们获得另一个转移：

$$pd_{i,j,k} = \min\limits^{x}_ {l=1} pd_{i,j,l}+1$$

其原理一样显然，一个区间中如果没有 $l$ 的话，那么这个区间将可以在一次操作以内全部变成 $l$，这种情况显然这个区间就没有 $k$ 了。

求得 $pd$ 以后，如下是一个简单的式子：

$$dp_{i,j,k} = pd_{i,j,k} + 1$$

其原理更加显然，一个区间内如果没有 $k$ 的话，那么一次操作就可以将其全部变成 $k$。

---

综上，实际上我们的转移都是在 $pd$ 内进行的，$dp$ 数组并没有实际性的参与转移。

$dp$ 和 $pd$ 数组的初始值根据长度为 $1$ 的区间是否为 $k$ 决定，详细可看
代码。

## 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 105, Lim = 1145141919;

int a[N];
int dp[N][N][N], pd[N][N][N];

void solve() {
  memset(pd, 0x7f, sizeof(pd));
  memset(dp, 0x7f, sizeof(dp));
  int n, x;
  cin >> n >> x;
  for(int i = 1; i <= n; i++) {
    cin >> a[i];
    for(int j = 1; j <= x; j++) {
      pd[i][i][j] = (a[i] == j);
      dp[i][i][j] = (a[i] != j);
    }
  }
  for(int ken = 1; ken <= n; ken++) {
    for(int i = 1; i + ken - 1 <= n; i++) {
      int j = i + ken - 1, m = Lim;
      for(int k = 1; k <= x; k++) {
        for(int l = i; l < j; l++) {
          pd[i][j][k] = min(pd[i][j][k], pd[i][l][k] + pd[l + 1][j][k]);
        }
        m = min(m, pd[i][j][k]);
      }
      for(int k = 1; k <= x; k++) {
        pd[i][j][k] = min(pd[i][j][k], m + 1);
      }
      for(int k = 1; k <= x; k++) {
        for(int l = i; l < j; l++) {
          dp[i][j][k] = min(dp[i][j][k], dp[i][l][k] + dp[l + 1][j][k]);
        }
        dp[i][j][k] = min(dp[i][j][k], pd[i][j][k] + 1);
      }
    }
  }
  int ans = Lim;
  for(int k = 1; k <= x; k++) {
    ans = min(ans, dp[1][n][k]);
  }
  cout << ans << '\n';
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  int t;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
```

## 总结

[AC](https://www.luogu.com.cn/record/144552265)

---

## 作者：small_john (赞：1)

## 思路

考虑区间 DP。

设 $f_{i,j,k}$ 表示把区间 $[i,j]$ 变成 $k$ 的最小花费，很明显有转移 $f_{i,j,k} = \displaystyle \min_{l=i}^{j-1}(f_{i,l,k}+f_{l+1,j,k})$。

这就完了？一道紫题？怎么可能！

发现这样转移会算漏，因为可以把区间 $[i,j]$ 变成不含 $k$ 的，再花一步变成全部都是 $k$。

考虑设 $g_{i,j,k}$ 表示把区间 $[i,j]$ 变成不含 $k$ 的最小花费。除了普通的区间 DP，我们还可以把区间 $[i,j]$ 先变成不含 $k'$，再全部变成 $k'$，这样也能达到要求。

所以容易写出转移：$g_{i,j,k}=\displaystyle \min_{l=i}^{j-1}(g_{i,l,k}+g_{l+1,j,k})$，然后记 $mn$ 为 $\displaystyle \min_{k=1}^{x} g_{i,j,k}$，则有 $g_{i,j,k} = \min\{g_{i,j,k},mn+1\}$。

时间复杂度 $O(n^3x)$，看似不能通过，但是区间 DP 会带一个大约 $\frac{1}{4}$ 的常数。实测跑得飞快。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

template<typename T> inline void read(T &x)
{
	x = 0;
	T f = 1;char ch = getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
		{
			f = -1,ch = getchar();
			break;
		}
		ch = getchar();
	}
	while(ch>='0'&&ch<='9')
		x = (x<<3)+(x<<1)+ch-48,ch = getchar();
	x*=f;
}
template<typename T> inline T read()
{
	T x;read(x);return x;
}
template<typename T> void write(T x)
{
    if(x<0) x = -x,putchar('-');
    if(x>9) write(x/10);
    putchar(x%10+48);
}
template<typename T> inline void writen(T x)
{
    write(x);
	putchar(10);
}
const int N = 1e2+5;
int n,m,a[N],f[N][N][N],g[N][N][N];
void solve()
{
    read(n),read(m);
    for(int i = 1;i<=n;i++) 
        for(int j = i;j<=n;j++)
            for(int k = 1;k<=m;k++)
                f[i][j][k] = g[i][j][k] = 2e9;
    for(int i = 1;i<=n;i++)
        for(int j = 1;j<=m;j++)
            g[i][i][j] = 0,f[i][i][j] = 1;
    for(int i = 1;i<=n;i++)
        read(a[i]),f[i][i][a[i]] = 0,g[i][i][a[i]] = 1;
    for(int len = 2;len<=n;len++)
        for(int i = 1,j = len;j<=n;i++,j++)
        {
            int mn = 2e9;
            for(int k = 1;k<=m;k++)
            {
                for(int l = i;l<j;l++)
                    g[i][j][k] = min(g[i][l][k]+g[l+1][j][k],g[i][j][k]);
                mn = min(mn,g[i][j][k]);
            }
            for(int k = 1;k<=m;k++) g[i][j][k] = min(g[i][j][k],mn+1),f[i][j][k] = g[i][j][k]+1;
            for(int k = 1;k<=m;k++)
                for(int l = i;l<j;l++)
                    f[i][j][k] = min(f[i][j][k],f[i][l][k]+f[l+1][j][k]);
        }
    int ans = 2e9;
    for(int i = 1;i<=m;i++)
        ans = min(ans,f[1][n][i]);
    writen(ans);
}
signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
    int T;
    read(T);
    while(T--) solve();
	return 0;
}
```

---

## 作者：Xy_top (赞：1)

一眼秒掉的 DP *2500。

首先观察数据范围，得出应该是区间 DP。

再观察修改的条件（区间内没有数字 $k$），我们就可以得到状态了。

设 $f_{i,j,k}$ 为区间 $[i,j]$ 全部变成 $k$ 的方案数，转移仍然很难，于是再设 $g_{i,j,k}$ 为区间 $[i,j]$ 全部变成不是 $k$ 的方案数，显然有转移：

$g_{i,j,k} = \min {g_{i,l,k}+g_{l+1,j,k}}$，此外 $g_{i,j,k} = \min g_{i,j,l} + 1$，也就是把没有 $l$ 的区间全部变成 $l$ 也能满足。

来看 $f_{i,j,k}$，显然 $f_{i,j,k}$ 可以等于 $g_{i,j,k}+1$，此外还有区间 DP 的转移，不再赘述。

答案就是 $\min f_{1,n,i}$，其中 $1\leq 1\leq n$。

代码：

```cpp
#include <bits/stdc++.h>
#define For(i, a, b) for (int i = (a); i <= (b); i ++)
#define foR(i, a, b) for (int i = (a); i >= (b); i --)
using namespace std;
int n, x;
int a[105];
int f[105][105][105], g[105][105][105];
/*
f[i][j][k]：区间 [i, j] 变为 k 的最小方案数
g[i][j][k]：区间 [i, j] 变为都不是 k 的最小方案数
*/
void solve () {
	For (i, 1, 100) For (j, 1, 100) For (k, 1, 100) f[i][j][k] = g[i][j][k] = 1000000000;
	scanf ("%d%d", &n, &x);
	For (i, 1, n) {
		scanf ("%d", &a[i]);
		For (j, 1, x) {
			g[i][i][j] = (a[i] == j);
			f[i][i][j] = (a[i] != j);
		}
	}
	For (len, 1, n) {
		For (i, 1, n - len + 1) {
			int j = i + len - 1, mi = 1000000000;
			For (l, 1, x) {
				For (k, i, j - 1) g[i][j][l] = min (g[i][j][l], g[i][k][l] + g[k + 1][j][l]);
				mi = min (mi, g[i][j][l]);
			}
			For (l, 1, x) g[i][j][l] = min (g[i][j][l], mi + 1);
			For (l, 1, x) {
				For (k, i, j - 1) f[i][j][l] = min (f[i][j][l], f[i][k][l] + f[k + 1][j][l]);
				f[i][j][l] = min (f[i][j][l], g[i][j][l] + 1);
			}
		}
	}
	int ans = 1000000000;
	For (i, 1, x) ans = min (ans, f[1][n][i]);
	cout << ans;
}
signed main () {
	int _ = 1;
	cin >> _;
	while (_ --) {
		solve ();
		cout << '\n';
	}
	return 0;
}
```


---

## 作者：_lgh_ (赞：0)

**[题目传送门](https://www.luogu.com.cn/problem/CF1922F)**。

区间 dp.

看到 $n,x \le 100$， $\sum x\le 500$ 发现可以 $O(n^3x)$。

很奢侈地设 $f_{i,j,k}$ 指令区间 $[i,j]$ 全部为 $k$ 的代价。

发现这个不包含 $k$ 覆盖的操作很难转移，考虑再设一个 $g_{i,j,k}$  表示令区间 $[i,j]$ 不含 $k$ 的代价。

考虑怎么转移。

发现 $g$ 的转移就是一个区间 dp 板子，发现 $g_{i,j,k}$ 要对所有   $({g_{i,j,o}+1})(1\le o \le x)$ 取 $\min$。

然后对着 $f$ 区间 dp 一下，算上 $g$ 的贡献即可。

需要注意什么时候需要对 $\min(g_{i,j,k})$ 加一，不然可能会 WA on #2。

[code](https://codeforces.com/contest/1922/submission/242878555)

---

