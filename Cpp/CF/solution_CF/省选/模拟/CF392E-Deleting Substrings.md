# Deleting Substrings

## 题目描述

SmallR likes a game called "Deleting Substrings". In the game you are given a sequence of integers $ w $ , you can modify the sequence and get points. The only type of modification you can perform is (unexpected, right?) deleting substrings. More formally, you can choose several contiguous elements of $ w $ and delete them from the sequence. Let's denote the sequence of chosen elements as $ w_{l},w_{l+1},...,w_{r} $ . They must meet the conditions:

- the equality $ |w_{i}-w_{i+1}|=1 $ must hold for all $ i $ $ (l<=i&lt;r) $ ;
- the inequality $ 2·w_{i}-w_{i+1}-w_{i-1}>=0 $ must hold for all $ i $ $ (l&lt;i&lt;r) $ .

After deleting the chosen substring of $ w $ , you gain $ v_{r-l+1} $ points. You can perform the described operation again and again while proper substrings exist. Also you can end the game at any time. Your task is to calculate the maximum total score you can get in the game.

## 样例 #1

### 输入

```
3
0 0 3
1 2 1
```

### 输出

```
3```

## 样例 #2

### 输入

```
6
1 4 5 6 7 1000
2 1 1 2 2 3
```

### 输出

```
12```

# 题解

## 作者：是个汉子 (赞：6)

### Solution

首先，题的意思是删连续上升的/连续下降的/先上升后的。

然后发现 $n\leq 400$ ，所以可以考虑**区间DP**。

设 $f_{i,j}$ 为删完 $w_i,\cdots, w_j$ 的最大分数， $g_{i,j}$ 为将 $w_i,\cdots,w_j$ 删成以 $w_i$ 开头， $w_j$ 结尾的连续上升的最大分数， $h_{i,j}$ 为将 $w_i,\cdots,w_j$ 删成以 $w_i$ 开头， $w_j$ 结尾的连续下降的最大分数。

可以列出状态转移方程：
$$
g_{i,j}=\max\{[w_{j-1}+1=w_j]g_{i,j-1},\max_{k=i}^{j-2}\{[w_k+1=w_j](g_{i,k}+f_{k+1,j-1})\}\}
$$
意思是可以直接填 $w_j$ ，也可以删除 $w_{k+1},\cdots,w_{j-1}$ ，然后填 $w_j$ 。
$$
h_{i,j}=\max\{[w_{j-1}-1=w_j]h_{i,j-1},\max_{k=i}^{j-2}\{[w_k-1=w_j](h_{i,k}+f_{k+1,j-1})\}\}
$$
和上面那个同理。
$$
f_{i,j}=\max\{[1\leq w_j-w_i+1\leq n](g_{i,j}+v_{w_j-w_i+1}),[1\leq w_i-w_j+1\leq n](h_{i,j}+v_{w_i-w_j+1}),\\\max_{k=i}^{j-1}\{f_{i,k}+f_{k+1,j}\},\max_{k=i+1}^{j-1}\{[1\leq 2w_k-w_i-w_j+1\leq n]g_{i,k}+h_{k,j}+v_{2w_k-w_i-w_j+1}\}\}
$$
最外层 $\max$ 中，第一个是删成连续上升的，第二个是删成连续下降的，第三个是先删 $w_i,\cdots,w_k$ 即 $f_{i,k}$ 再删 $w_k,\cdots,w_j$ 即 $f_{k,j}$ ，第四个是删成先上升再下降的。
$$
dp_i=\max_{j=0}^{j<i}\{dp_{i-1},dp_j+f_{j+1,i}\}
$$
这是最显然的，就不解释了。

注意：要记得把 $f_{i,i}$ 初始化为 $1$ ， $g_{i,i},h_{i,i}$ 初始化为 $0$  

### 代码

```c++
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;
const int N=410,INF=1e9;
int n;
int v[N],w[N],f[N][N],g[N][N],h[N][N],dp[N];

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(!isdigit(ch)){if(ch=='-') f=-1;ch=getchar();}
    while(isdigit(ch)){x=x*10+(ch^48);ch=getchar();}
    return x*f;
}

inline void Max(int &a,int b){
    if(a<b) a=b;
}

int main(){
    n=read();
    for(int i=1;i<=n;i++) v[i]=read();
    for(int i=1;i<=n;i++) w[i]=read();
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            f[i][j]=g[i][j]=h[i][j]=-INF;
    for(int i=n;i>0;i--){
        f[i][i]=v[1];
        g[i][i]=h[i][i]=0;
        for(int j=i+1;j<=n;j++){
            for(int k=i;k<j-1;k++)
                if(w[k]+1==w[j]) Max(g[i][j],g[i][k]+f[k+1][j-1]);
            if(w[j-1]+1==w[j]) Max(g[i][j],g[i][j-1]);
        }
        for(int j=i+1;j<=n;j++){
            for(int k=i;k<j-1;k++)
                if(w[k]-1==w[j]) Max(h[i][j],h[i][k]+f[k+1][j-1]);
            if(w[j-1]-1==w[j]) Max(h[i][j],h[i][j-1]);
        }
        for(int j=i;j<=n;j++){
            if(w[j]-w[i]+1>0&&w[j]-w[i]+1<=n) Max(f[i][j],g[i][j]+v[w[j]-w[i]+1]);
            if(w[i]-w[j]+1>0&&w[i]-w[j]+1<=n) Max(f[i][j],h[i][j]+v[w[i]-w[j]+1]);
            for(int k=i;k<j;k++) Max(f[i][j],f[i][k]+f[k+1][j]);
            for(int k=i+1;k<j;k++)
                if(2*w[k]-w[i]-w[j]+1>0&&2*w[k]-w[i]-w[j]+1<=n)
                    Max(f[i][j],g[i][k]+h[k][j]+v[2*w[k]-w[j]-w[i]+1]);
        }
    }
    for(int i=1;i<=n;i++){
        dp[i]=dp[i-1];
        for(int j=0;j<i;j++) Max(dp[i],dp[j]+f[j+1][i]);
    }
    printf("%d\n",dp[n]);
    return 0;
}
```



---

## 作者：Reywmp (赞：3)

- ## CF392E 【Deleting Substrings】

感谢学长对本题给予指导。

区间 $dp$ 经典题。

-----------

- ### Prelude

大概是一道比较显然的区间 $dp$ 。

观察题目的几个性质。

从那个 $\texttt{inequality}$ 可以看出题目每次删除操作只能删去一个 严格的**峰形/上升/下降** 区间。

从 $\texttt{equality}$ 可以看出一个性质，因为 $|w_i-w_{i+1}|=1$ ，这样的话一个合法区间的间距为 $1$ 。那么考虑这个合法区间（我们假设就是 $[l,r$] ）的长度时，我们有 $|w_r-w_l|+1=r-l+1$ ，这样在计算区间长度的时候会方便做题。为什么呢，很显然，我们要做 $dp$ ，但是这个题是有删除操作的，也就是我们并不可能考虑每次删除后剩下的 $w_i$ 的下标变成了什么，用下标算长度也不再准确，有了这个性质，我们就可以对应长度方便计算贡献。

假如有区间 $i\in[1,7]\rightarrow\{1,2,3,9,8,7,4\}$ 删除区间 $\{9,8,7\}$ 后我们继续删除 $\{1,2,3,4\}$ 时，我们仍然在转移 $[1,7]$ 但是长度不能再用 $v_{7-1+1}$ ，所以可以直接用上升区间右端点减去左端点 $+1$ 同样得到长度。也就是 $v_{4-1+1}=v_4$ 长度也确实为  $4$ ，当然，下降区间反之。

既然都这样了，这个题目就符合区间 $dp$ 的大部分性质了。因为其状态设计，是可以通过合并 $2$ 次删除操作去删除一个大的区间的。

再一看 $n\leq400$，很显然区间 $dp$ 能过。

我们现在只需要考虑 $dp$ 方法和一些细节问题。

------------

- ### Solution

我们考虑 $f_{i,j}$ 为 $[i,j]$ 这个区间的最大贡献。什么贡献呢，显然，如果要合并，我们只能选择操作贡献，也就是**删去整个 $[i,j]$ 区间的最大贡献**。

我们发现很难去判断整个 $[i,j]$ 区间能不能删除或合并，直接扫一遍很显然会徒增复杂度，不可行。

那我们可以分类讨论。

只考虑一个**单调上升/下降**区间，如果不保证当前枚举到的区间是单调的怎么办，没关系，我们可以把它**内部子区间删除直到变成单调的**。这样不会影响我们的结果。这个显然，因为你**只支持删除这样区间**的操作，所以你也只能通过这个操作来删除整个区间，与其说不影响，不如说**只能这样**。

可能比较拗口，但是简单来说就是，删除整个区间，只考虑单调情况的时候，只能一直删除单调区间，顺序无所谓，只需要取最优。

但是这个其实对我们没有帮助，我们也不可能理想地一直删除整个单调区间或者说枚举单调情况，但是这个为我们考虑 **峰形** 区间提供了思路。

我们回到初始状态： $f_{i,j}$ 表示删除 $[i,j]$ 区间可以得到的最大贡献。内部转移很显然是 $f_{i,j}=\max\{f_{i,j},f_{i,k}+f_{k+1,j},(k\in[i,j-1])\}$ 。

对于一个区间 $dp$ 题：我们要明白一个性质，也就是状态端点 $i,j$ 是同一状态下的，那么也就是说在这题他们是在同一个操作内被删除的。也就是说我们只能通过删除让 $[i,j]$ 区间符合条件可以删除，才能合并操作并转换。

我们考虑内部删除操作，对于每个删除操作，必然有一个点是不变的，那就是**波峰**，即使是单调区间也有端点中的最大值。于是我们可以枚举**波峰**。

我们引入 $2$ 个数组 $g,h$ 分别记录让一个区间 $[i,j]$ **变成**单调**上升/下降**的最大收益。这样就可以保证每次操作都是合法的单调区间。至于**峰形**区间，可以考虑合并**一个单调上升和一个单调下降**区间。

这样的话在转移 $f$ 的时候可以保证：

- 加上 $g,h$ 的贡献使得区间变为单调保证每次操作合法。
- 方便合并 $2$ 个单调的区间。
- 自身的贡献不会重复计算，因为计算长度可以通过条件 $|w_i-w_{i+1}|=1$ 。

首先得出 $g,h$ 的转移方程。
$$
g_{i,j}=\max\{g_{i,k}+f_{k+1,j-1}(w_k+1=w_j),g_{i,j-1}(w_{j-1}+1=w_j)\};
$$
$$
h_{i,j}=\max\{h_{i,k}+f_{k+1,j-1}(w_k-1=w_j),h_{i,j-1}(w_{j-1}-1=w_j)\};
$$
很好理解，如果说 $w_k$ 和 $w_j$ 呈上升/下降态，那么就可以通过删除 $f_{k+1,j-1}$ 来使得区间单调。如果连续则不需要删除。可以发现，这个转移方程也是建立在 $f_{i,j}$ 基础上，所以我们需要每次枚举到一个区间都计算，由内到外。初始化 $f_{i,i}=v_1,g_{i,i}=h_{i,i}=0$。

现在可以考虑 $f$ 的转移方程。

考虑直接按照单调上升删除：
$$
f_{i,j}=\max\{g_{i,j}+v_{w_j-w_i+1}\};
$$
考虑单调下降：
$$
f_{i,j}=\max\{h_{i,j}+v_{w_i-w_j+1}\};
$$
这两个很好理解，就是在把 $[i,j]$ 删成单调下降的最大贡献 $+$ 删除保留了 $i,j$ 两个端点最后一次剩下的区间的贡献（这个区间的合法条件其实就是长度不超过 $[i,j]$ 本身，因为你删除不可能删得变长了）。

**现在考虑波峰**：
$$
f_{i,j}=\max\{g_{i,k}+h_{k,j}+v_{2w_k-w_i-w_j+1}\};
$$
与单调情况不同，一个波峰状态至少要有 $3$ 个元素，左端点右端点和波峰。所以首先距离仍然通过 $2w_k-w_i-w_j+1$ 计算，可以自行列几个符合条件的波峰状数列验证。为了保证 $[i,k]$ 上升 $[k,j]$ 下降分别加上 $g_{i,k}$ 和 $h_{k,j}$ 。得到转换。

最后，记得对 $f$ 进行符合区间性质的转换，$f_{i,j}=\max\{f_{i,k}+f_{k+1,j},(k\in[i,j-1])\};$

最后我们还能发现，整个序列可以不删完，这个可以在最后暴力枚举区间考虑是否删除。
$$
ans_i=\max\{ans_{i-1},ans_j+f_{j+1,i},(j\in[0,i-1])\}.
$$
最后答案为 $ans_n$ 。

-------------------------

- ### Code

~~每天一个爆零小技巧~~：数值太大溢出，最小值太小也会溢出。

```cpp
#include<cstdio>
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cmath>
#include<queue>
#include<map>
#include<stack>
//#include<bits/stdc++.h>

#define ll long long
#define ull unsigned long long
#define INL inline
#define Re register

//Tosaka Rin Suki~
using namespace std;

const int N=405;
const int INF=1e9;

INL int read()
{
	 int x=0;int w=1;
	 char ch=getchar();
	 while((ch<'0'||ch>'9')&&ch!='-')ch=getchar();
	 if(ch=='-')w=-1,ch=getchar();
	 while(ch>='0'&&ch<='9')
	 {x=(x<<1)+(x<<3)+ch-48,ch=getchar();}
	 return x*w;
}

INL int mx(int a,int b){return a>b?a:b;}
INL int mn(int a,int b){return a<b?a:b;}

int w[N],v[N];
int f[N][N],g[N][N],h[N][N];
int ans[N];

INL void Debug(int i,int j,int condition)
{
	printf("%d->%d : %d(%d)\n",i,j,f[i][j],condition);
}

int main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	int n;
	n=read();
	for(int i=1;i<=n;i++)v[i]=read();
	for(int i=1;i<=n;i++)w[i]=read();
//	memset(f,128,sizeof(f));
//	memset(g,128,sizeof(g));
//	memset(h,128,sizeof(h));
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)f[i][j]=g[i][j]=h[i][j]=-INF;//初始化
	for(Re int i=n;i>=1;i--)
	{
		f[i][i]=v[1],g[i][i]=h[i][i]=0;
		for(Re int j=i+1;j<=n;j++)
		{
			for(Re int k=i;k<j-1;k++)
			{
				if(w[k]+1==w[j])g[i][j]=mx(g[i][k]+f[k+1][j-1],g[i][j]);
				else if(w[k]-1==w[j])h[i][j]=mx(h[i][k]+f[k+1][j-1],h[i][j]);
			}
			if(w[j-1]+1==w[j])g[i][j]=mx(g[i][j],g[i][j-1]);
			else if(w[j-1]-1==w[j])h[i][j]=mx(h[i][j],h[i][j-1]);
		}//先算 g,h
		for(Re int j=i;j<=n;j++)
		{
			if(w[j]-w[i]>=0&&w[j]-w[i]<=j-i+1)f[i][j]=mx(f[i][j],g[i][j]+v[w[j]-w[i]+1])/*,Debug(i,j,1)*/;
			else if(w[i]-w[j]>=0&&w[i]-w[j]<=j-i+1)f[i][j]=mx(f[i][j],h[i][j]+v[w[i]-w[j]+1])/*,Debug(i,j,2)*/;
			for(Re int k=i;k<j;k++)
			{
				f[i][j]=mx(f[i][k]+f[k+1][j],f[i][j]);
			}
			for(Re int k=i+1;k<j;k++)
			{	
				if(2*w[k]-w[i]-w[j]>=0&&2*w[k]-w[i]-w[j]<n)
				f[i][j]=mx(f[i][j],g[i][k]+h[k][j]+v[2*w[k]-w[i]-w[j]+1])/*,Debug(i,j,3)*/;
			}//波峰转移
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<i;j++)
		{
			ans[i]=mx(ans[j]+f[j+1][i],ans[i]);
		}
		ans[i]=mx(ans[i],ans[i-1]);
	}//暴力判断要删除的区间
	printf("%d\n",ans[n]);
	return 0;
}
```



---

