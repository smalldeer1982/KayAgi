# Subarray Cuts

## 题目描述

You are given an array of length $ n $ and a number $ k $ . Let's pick $ k $ non-overlapping non-empty subarrays of the initial array. Let $ s_{i} $ be the sum of the $ i $ -th subarray in order from left to right. Compute the maximum value of the following expression:

 $ |s_{1}-s_{2}|+|s_{2}-s_{3}|+...+|s_{k-1}-s_{k}| $ Here subarray is a contiguous part of an array.

## 说明/提示

Consider the first sample test. The optimal solution is obtained if the first subarray contains the first element only, the second subarray spans the next three elements and the last subarray contains the last element only. The sums of these subarrays are $ 5 $ , $ 9 $ and $ 1 $ , correspondingly.

Consider the second sample test. In the optimal solution, the first subarray consists of the first two elements and the second subarray consists of the third element only. Note that the last element does not belong to any subarray in this solution.

## 样例 #1

### 输入

```
5 3
5 2 4 3 1
```

### 输出

```
12
```

## 样例 #2

### 输入

```
4 2
7 4 3 7
```

### 输出

```
8
```

# 题解

## 作者：shao0320 (赞：6)

#### 题目大意

给出一串数，在其中选出k个不重叠，不相交的子串， 按顺序将子串的和标为$s1,s2,s3…..sk$， 求$|s_1-s_2|+|s_2-s_3|+…+|s_{k-1}-s_k|$的最大值。



分析：



这道题是我们的考试题，同年级的两个巨佬考场上都做出来了，然而我直接放过去了（（（



拿到这个题目的第一反应是$f(i,j,k)$表示前$i$个数分$j$段，最后一段数和是$k$的最优解，但这个做法是基于值域的，不好优化，赛后看了题解恍然大悟。



手造几个样例，可以看出，有些数对于答案是没有贡献的，如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/imcdikkc.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

图中的点和线段代表$s$的大小及趋势，有这样几类点：

$1$、黑色实心点/红色实心点，他们位于极值上，因此对答案有着$2s_x$或$-2s_x$的贡献。

$2$、黄色实心点：位于边界，有着$s_1$和$s_k$的贡献。

$3$、空心点：被加一次，被减一次，对于答案无贡献，无需考虑。



因此$dp$可以这样设计状态：

$f(i,j,0/1/2/3)$表示，前$i$个数，分成$j$组，第$j$组在整个$s$数组的趋势上位于最低/上升期/最高/下降期。

转移时需要特殊考虑$1$、$k$。

代码：

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define N 30005
using namespace std;
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return x*f;
}
int n,k,f[N][205][4],a[N];
/*
0:lowest
1:l->h
2:highest
3:h->l
*/
int main()
{
	n=read();k=read();
	for(int i=1;i<=n;i++)a[i]=read();
	memset(f,-0x3f,sizeof(f));
	for(int i=0;i<=n;i++)
	{
		for(int j=0;j<=3;j++)
		{
			f[i][0][j]=0;
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=k;j++)
		{
			int is_edge=1+(j!=1&&j!=k);
			f[i][j][0]=max(f[i-1][j][0],f[i-1][j-1][3])-is_edge*a[i];
			f[i][j][1]=max(f[i-1][j][1],f[i][j][0]);
			f[i][j][2]=max(f[i-1][j][2],f[i-1][j-1][1])+is_edge*a[i];
			f[i][j][3]=max(f[i-1][j][3],f[i][j][2]);
			if(is_edge==2)
			{
				f[i][j][1]=max(f[i][j][1],f[i-1][j-1][1]);
				f[i][j][3]=max(f[i][j][3],f[i-1][j-1][3]);
			}
		}
	}
	cout<<max(f[n][k][1],f[n][k][3])<<endl;
	return 0;
}
```

by shao0320

---

## 作者：cwfxlh (赞：2)

# [CF513E2](https://www.luogu.com.cn/problem/CF513E2)    

首先发现，我们可以把绝对值拆掉，给每个绝对值内部的式子赋一个 $\pm 1$ 的系数，所以求值最大的赋值方案即可。   

当我们赋完系数后，观察 $s_{1...k}$ 的系数，发现系数存在规律，首先，首尾都是 $\pm 1$，中间有部分的 0 与 $\pm 2$，并且非零数的符号是正负交替出现的。    

于是就可以 dp 了，需要记录的状态就是当前考虑了几个数，分了几段，当前位的权值绝对值，上一个非零数的符号，转移即可。因为首尾的特殊性需要特殊处理，写起来手感纯纯构式。      

代码：    

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,a[500003],dp[30003][203][2][2],ans,pre[500003],p1[500003],p2[500003];
void upd(int v1,int v2,int v3,int v4,int v5){
    dp[v1][v2][v3][v4]=max(dp[v1][v2][v3][v4],v5);
    return;
}
int main(){
    ios::sync_with_stdio(false);
    cin>>n>>k;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=1;i<=n;i++)pre[i]=pre[i-1]+a[i];
    for(int i=1,j1=0,j2=0,mnv=a[1],mxv=a[1];i<=n;i++){
        for(int j=0;j<=k;j++){
            dp[i][j][0][0]=dp[i][j][0][1]=dp[i][j][1][0]=dp[i][j][1][1]=-1000000000;
        }
        if(i==1){
            mnv=min(mnv,pre[i]-pre[j2]);
            mxv=max(mxv,pre[i]-pre[j1]);
            p1[i]=mnv;
            p2[i]=mxv;
            if(pre[i]<pre[j1])j1=i;
            if(pre[i]>pre[j2])j2=i;
            continue;
        }
        upd(i,1,0,0,-mnv);
        upd(i,1,0,1,mxv);
        upd(i,2,0,0,-mnv);
        upd(i,2,0,1,mxv);
        upd(i,2,1,0,mxv-2*a[i]);
        upd(i,2,1,1,-mnv+2*a[i]);
        mnv=min(mnv,pre[i]-pre[j2]);
        mxv=max(mxv,pre[i]-pre[j1]);
        p1[i]=mnv;
        p2[i]=mxv;
        for(int j=1;j<=k;j++){
            upd(i,j,0,0,dp[i-1][j][0][0]);
            upd(i,j,0,0,dp[i-1][j][1][0]);
            upd(i,j,0,1,dp[i-1][j][0][1]);
            upd(i,j,0,1,dp[i-1][j][1][1]);
            upd(i,j,0,0,dp[i-1][j-1][0][0]);
            upd(i,j,0,1,dp[i-1][j-1][0][1]);
            upd(i,j,0,0,dp[i-1][j-1][1][0]);
            upd(i,j,0,1,dp[i-1][j-1][1][1]);
            upd(i,j,1,0,dp[i-1][j-1][0][1]-2*a[i]);
            upd(i,j,1,0,dp[i-1][j][1][0]-2*a[i]);
            upd(i,j,1,0,dp[i-1][j-1][1][1]-2*a[i]);
            upd(i,j,1,1,dp[i-1][j-1][1][0]+2*a[i]);
            upd(i,j,1,1,dp[i-1][j][1][1]+2*a[i]);
            upd(i,j,1,1,dp[i-1][j-1][0][0]+2*a[i]);
        }
        if(pre[i]<pre[j1])j1=i;
        if(pre[i]>pre[j2])j2=i;
    }
    for(int i=n,j1=n,j2=n,mxv=a[n],mnv=a[n];i>1;i--){
        mxv=max(mxv,pre[j1]-pre[i-1]);
        mnv=min(mnv,pre[j2]-pre[i-1]);
        if(k==2){
            ans=max(ans,mxv-p1[i-1]);
            ans=max(ans,p2[i-1]-mnv);
        }
        else{
            ans=max(ans,dp[i-1][k-1][0][0]+mxv);
            ans=max(ans,dp[i-1][k-1][0][1]-mnv);
            ans=max(ans,dp[i-1][k-1][1][0]+mxv);
            ans=max(ans,dp[i-1][k-1][1][1]-mnv);
        }
        if(pre[i-1]>pre[j1])j1=i-1;
        if(pre[i-1]<pre[j2])j2=i-1;
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：XL4453 (赞：2)

### $\text{Difficulty : 2700}$
---
### 解题思路：

朴素的思路是 $f_{i,j,k}$ 表示考虑到第 $i$ 个，上一个转移点在 $j$，转移了 $k$ 次，优化的难点在于需要确定当前转移给予的权值是正还是负。

那不妨就从权值正负入手，将所有的绝对值符号拆开，发现除了第一个和最后一个位置的权值绝对值为 $1$ 外，其它所有位置的权值绝对值都是 $2$ 或者 $0$。

于是就想到用当前的权值作为状态，$f_{i,j,k}$ 表示考虑到第 $i$ 个位置，已经转移了 $j$ 次，状态为 $k$。

具体的状态讨论比较麻烦：

-  $k=0$ 表示当前权值为 $2$，特殊地，当此时是第一个转移点或者到达最后一个转移点的时候，这个地方代表权值为 $1$。

- $k=1$ 表示当前权值为 $-2$，特殊地，当此时是第一个转移点或者到达最后一个转移点的时候，这个地方代表权值为 $-1$。

- $k=2$ 表示接下来的权值为 $0$ 或者不取，往前的最后一个取了的非 $0$ 权值为负。

- $k=3$ 表示接下来的权值为 $0$ 或者不取，往前的最后一个取了的非 $0$ 权值为正。

---
转移细节也非常麻烦，主要在于对于中途，开头和结尾三个地方放弃部分数值的处理。

具体地，将 $j=1$，$j=k$ 和其它情况分开处理。

对于 $j=1$ 时，任意的 $f_{i,j,0}$ 和 $f_{i,j,1}$ 都可以从之前的 $f_{i-1,j,0}$ 和 $f_{i-1,j,1}$ 转移，表示再取一个，也可以放弃之前所有的，直接从当前位置开始重新取。

对于 $j=n$ 和其它情况，$f_{i,j,0}$ 和 $f_{i,j,1}$ 可以在之前的基础上再取一个数，也就是从 $f_{i-1,j,0}$ 和 $f_{i-1,j,1}$ 转移，也可以从开始新的一段，从 $f_{i-1,j-1,2}$ 和 $f_{i-1,j-1,3}$ 转移。

对于 $k=2$ 或 $k=3$ 的情况，除了 $j=1$ 或者 $j=k$ 的时候不能从 $f_{i-1,j-1,2}$ 和 $f_{i-1,j-1,3}$ 转移以外，所有的位置都能够从 $f_{i-1,j-1,2/3}$，表示开启新的一段并选择当前数的权值为 $0$，$f_{i-1,j,2/3}$，表示延续之前的段，以及  $f_{i,j,1/0}$ 表示从当前位置开始新的一段，接下来一段舍弃。对于 $j=1$ 不能用 $f_{i-1,j-1,2}$ 和 $f_{i-1,j-1,3}$ 转移是因为没有这样的位置，而对于 $j=k$ 不能用 $f_{i-1,j-1,2}$ 和 $f_{i-1,j-1,3}$ 是为了最后一段禁止取 $0$，保证只有不取数一个选择，也就使得最终的答案是 $f_{n,k,2/3}$，而不用从后往前找出最大位置。

较为特殊的，由于让权值为 $0$ 和不取带来的贡献都是 $0$，所以在一定存在一种情况使得取 $0$ 的位置连续的结论的保证下可以将不取和取 $0$ 混作一个状态，同时这样也就保证了段与段之间少取部分数的情况被考虑。

---
有一个不影响做法问题也是值得思考的，就是在进行转移的其实并没有进行大小比较，但是最后的结果却没有出现赋予错误的系数情况。

实际上在转移过程中这种错误是有可能出现的。但是可以证明如果出现了这种情况则一定不是一个优解，具体证明的时候局限于刚才给出的方程会比较麻烦，但是可以转向证明一个固定的划分情况赋予权值，得出只有正确划分才能得到最大的权值，然后用所有的划分情况被考虑回归到原命题上。或者简单一点，用 $\text{\_rqy}$ 大佬的话讲就是“显然绝对值改成 $\max$”，但反正我是看不出来哪里显然了。

扯开说一句，顺着这个结论思考就会发现这个 $\text{DP}$ 思路完全做不了最小值。

---
### 代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
#define int long long
const int MAXN=30005;
int n,k,a[MAXN],f[MAXN][205][5],ans;
signed main(){
	scanf("%lld%lld",&n,&k);
	for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
	for(int i=0;i<=n+1;i++)
	for(int j=0;j<=k+1;j++)
	for(int k=0;k<=4;k++)
	f[i][j][k]=-1e13;
	f[0][1][1]=f[0][1][0]=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=min(i,k);j++){
			if(j==1){
				f[i][j][0]=max(f[i-1][j][0],0ll)+a[i];
				f[i][j][1]=max(f[i-1][j][1],0ll)-a[i];
				f[i][j][2]=max(f[i-1][j][2],f[i][j][1]);
				f[i][j][3]=max(f[i-1][j][3],f[i][j][0]);
			}else
			if(j==k){
				f[i][j][0]=max(f[i-1][j][0],f[i-1][j-1][2])+a[i];
				f[i][j][1]=max(f[i-1][j][1],f[i-1][j-1][3])-a[i];
				f[i][j][2]=max(f[i-1][j][2],f[i][j][1]);
				f[i][j][3]=max(f[i-1][j][3],f[i][j][0]);
			}else{
				f[i][j][0]=max(f[i-1][j][0],f[i-1][j-1][2])+2*a[i];
				f[i][j][1]=max(f[i-1][j][1],f[i-1][j-1][3])-2*a[i];
				f[i][j][2]=max(f[i-1][j][2],max(f[i][j][1],f[i-1][j-1][2]));
				f[i][j][3]=max(f[i-1][j][3],max(f[i][j][0],f[i-1][j-1][3]));
			}
		}
	}
	printf("%lld",max(f[n][k][2],f[n][k][3]));
	return 0;
}
```


---

## 作者：L_zaa_L (赞：1)

一般我们做题遇到绝对值都会考虑把他给拆掉，于是考虑将这个给拆掉，拆完后可能会剩下这样的：$s_1-s_2+s_2-s_3-s_3+s_4-s_4+s_5+s_5-s_6\cdots -s_{k-2}+s_{k-1}-s_{k-1}+s_k=s_1-2s_3+2s_5-2s_6+\cdots +s_k$

我们发现除了 $s_1$ 和 $s_k$ 系数可以为 $\pm 1$，其他的系数不是 $\pm 2$ 就是 $0$。而且除去 $0$ 之后，$+$ 与 $+$ 不能连在一起，$-$ 和 $-$ 也不能连在一起，$s_1$ 和 $s_k$ 也要算在条件内。

于是我们可以设 $dp_{i,j,0/1/2,0/1}$ 表示前 $i$ 个数字，划分到了第 $j$ 组，当前组的系数是正的，负的还是 $0$，出去零以后，往前第一个组系数是正的还是负的。

于是可以列出以下的式子，式子比较简单，不再做什么解释：

$$\begin{cases}dp_{i,j,0,0}=\max(dp_{i-1,j,0,0},dp_{i-1,j-1,1,1},dp_{i-1,j-1,2,1})+a_i+[j\not=1\land j\not=k]a_i\\dp_{i,j,1,1}=\max(dp_{i-1,j,1,1},dp_{i-1,j-1,0,0},dp_{i-1,j-1,2,0})-a_i-[j\not=1\land j\not=k]a_i\\dp_{i,j,2,0}=\max({dp_{i-1,j,2,0},dp_{i-1,j-1,2,0},dp_{i-1,j,0,0},dp_{i-1,j-1,0,0}}))&(j\not=1)\\dp_{i,j,2,1}=\max(dp_{i-1,j,2,1},dp_{i-1,j-1,2,1},dp_{i-1,j,1,1},dp_{i-1,j-1,1,1})&(j\not=1)\end{cases}$$

然后发现问题是有些数可以不选，对于在中间的那些不选的数，我们可以直接划分在系数 $0$ 组里面，剩下的就是前面的和后面的，前面的在设初始值就可以解决了，后面在求答案的时候把 $1\sim n$ 的 $dp_{i,k,1,1}$ 和 $dp_{i,k,0,0}$ 求最大值就可以解决。

然后就是绝对值的事，拆完之后一定会是正数，如果是负数就肯定不优，时间复杂度 $O(nk)$。

## Code

```cpp
#include<bits/stdc++.h>
//#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
//#pragma GCC optimize(2)
//#pragma GCC optimize(3)
//#pragma GCC optimize("Ofast,unroll-loops")
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,popcnt,tune=native")
//#include <immintrin.h>
//#include <emmintrin.h>
#define int long long
#define ls(x) ((x)*2)
#define rs(x) ((x)*2+1)
#define Debug(...) fprintf(stderr, __VA_ARGS__)
#define For(i,a,b) for(int i=a,i##end=b;i<=i##end;i++)
#define Rof(i,a,b) for(int i=a,i##end=b;i>=i##end;i--)
#define rep(i,  b) for(int i=1,i##end=b;i<=i##end;i++)
using namespace std;
const int N=1e6+5,base=999983,Mod=998244353;
//char buf[(1<<21)+5],*p1,*p2;
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
inline void chmx(int &x,int y){(x<y)&&(x=y);}
inline void chmn(int &x,int y){(x>y)&&(x=y);}
inline void Add(int &x,int y){(x=x+y+Mod)%=Mod;}
inline int read(){
	int f=0,x=0;
	char ch=getchar();
	while(!isdigit(ch)){f|=(ch=='-');ch=getchar();}
	while(isdigit(ch)){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return f?-x:x;
}
void print(int n){
    if(n<0){
        putchar('-');
        n*=-1;
    }
    if(n>9) print(n/10);
    putchar(n%10+'0');
}
int n,k;
int dp[30005][205][3][2],a[N]; 
signed main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	// ios::sync_with_stdio(false);
	// cin.tie(0); cout.tie(0);
	n=read(),k=read();
	For(i,1,n) a[i]=read();
	For(i,0,n) For(j,0,k) For(t,0,2) For(k,0,1) dp[i][j][t][k]=-1e9;
	For(i,1,n){
		For(j,1,min(i,k)){
			dp[i][j][0][0]=max({dp[i-1][j][0][0],dp[i-1][j-1][1][1],dp[i-1][j-1][2][1]})+a[i]+(j!=1&&j!=k)*a[i];
			dp[i][j][1][1]=max({dp[i-1][j][1][1],dp[i-1][j-1][0][0],dp[i-1][j-1][2][0]})-a[i]-(j!=1&&j!=k)*a[i];
			if(j==1) 
				dp[i][1][0][0]=max(dp[i][1][0][0],a[i]),
				dp[i][1][1][1]=max(dp[i][1][1][1],-a[i]);
			if(j!=1)dp[i][j][2][0]=max({dp[i-1][j][2][0],dp[i-1][j-1][2][0],dp[i-1][j][0][0],dp[i-1][j-1][0][0]});
			if(j!=1)dp[i][j][2][1]=max({dp[i-1][j][2][1],dp[i-1][j-1][2][1],dp[i-1][j][1][1],dp[i-1][j-1][1][1]});
//			printf("%lld %lld\n",i,j);
		}
		
	}
	int ans=0;
	For(i,1,n)ans=max({ans,dp[i][k][1][1],dp[i][k][0][0]});
	printf("%lld\n",ans);
#ifdef LOCAL
    Debug("\nMy Time: %.3lfms\n", (double)clock() / CLOCKS_PER_SEC);
#endif
	return 0;
}

```

---

## 作者：262620zzj (赞：1)

# 核心思路

如果我们画出 $x-s_x$ 折线图，就可以发现 $s_i$ 在 $s$ 中的位置有四种情况，分别是山谷，上坡，山峰，下坡。对应的贡献是 $-2s_i,0,2s_i,0$。较为特殊的是，$s_1,s_k$ 必然作为峰或者谷，但只计算 $1$ 次。用动态规划解决。

## 状态设计

设 $f_{i,j,st},st\in \{0,1,2,3\}$ 表示 最后一段的结尾是 $i$（钦定选 $i$），划分了 $j$ 段，且第 $j$ 段的状态是 $st$，所能获得的最大值。$0\sim 3$ 分别表示上文的四种情况。最终答案就是

$$\max_{i=1}^n f_{i,k,0/2}$$

## 初始状态

$f_{i,0,st}=0$，因为我们知道一段也没有的时候，答案应该为 $0$。而其他状态未知，也不确定能不能转移到，所以设为最劣情况负无穷。

## 转移

- $f_{i,j,0}$，三种情况：
1. 上一段本就是山谷，将 $a_i$ 加入它。
2. 上一段是下坡，新开一段作为山谷。
3. 上一段是山峰，中间没有下坡，直接到山谷。

$$f_{i,j,0}=-2a_i+\max f_{i-1,j,0},f_{i-1,j-1,3},f_{i-1,j-1,2}$$

- $f_{i,j,1}$，三种情况：
1. 上一段本就是上坡，将 $a_i$ 加入它。
2. 上一段是上坡，但是选择新开一段上坡。
3. 上一段是山谷，新开一段上坡。

$$f_{i,j,1}=\max f_{i-1,j,1},f_{i-1,j-1,0},f_{i-1,j-1,1}$$

- $f_{i,j,2}$，与 $f_{i,j,0}$ 类似。

$$f_{i,j,2}=2a_i+\max f_{i-1,j,2},f_{i-1,j-1,1},f_{i-1,j-1,0}$$

- $f_{i,j,3}$，与 $f_{i,j,1}$ 类似。

$$f_{i,j,3}=\max f_{i-1,j,3},f_{i-1,j-1,2},f_{i-1,j-1,3}$$

还有一个点就是注意特判 $j=1,j=k$。第一段和最后一段只能作为山峰山谷，且权值只计算一次。

时间复杂度 $O(nk)$。注意到转移方程中 $f_i$ 只由 $f_{i-1}$ 转移而来，所以可以滚动数组，空间复杂度 $O(k)$。其实 $k$ 这一维还可以滚动 ~~，但是懒得搞了~~。

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
template<typename T>void read(T &x){
	x=0;int f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	x*=f;
}
template<typename T,typename ...Args>
void read(T &x,Args &...rest){read(x);read(rest...);}
int n,k,f[2][205][4],ans=-INT_MAX;
int main(){
	read(n,k);
	memset(f,128,sizeof(f));
	for(int i=0;i<=n;i++)for(int j=0;j<=3;j++)f[i][0][j]=0; 
	for(int s,t,a,i=1;i<=n;i++){
		read(a);
		s=i&1^1,t=i&1;
		for(int j=1;j<=min(i,k);j++){
			if(j==1||j==k){
				f[t][j][0]=max({f[s][j][0],f[s][j-1][3],f[s][j-1][2]})-a;
				f[t][j][2]=max({f[s][j][2],f[s][j-1][1],f[s][j-1][0]})+a;
			}
			else{
				f[t][j][0]=max({f[s][j][0],f[s][j-1][3],f[s][j-1][2]})-2*a;
				f[t][j][1]=max({f[s][j][1],f[s][j-1][0],f[s][j-1][1]});
				f[t][j][2]=max({f[s][j][2],f[s][j-1][1],f[s][j-1][0]})+2*a;
				f[t][j][3]=max({f[s][j][3],f[s][j-1][2],f[s][j-1][3]});
			}
		}
		ans=max({ans,f[t][k][0],f[t][k][2]});
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：luanmenglei (赞：1)

提供一种好想好写且不需要脑子的做法。

遇到式子里有绝对值且要求最大值的题，想都不用想就可以直接拆掉绝对值，因为绝对值一定不会使得值下降，所以说拆掉绝对值不会使得情况变优且一定包括最优解的情况，所以说拆掉绝对值是正确的。

然后我们就可以轻松的列出一个 DP 式子。

记 $f_{i,j,0/1}$ 表示上一段右端点为 $i$，已经选了 $j$ 段，且我们钦定上一段的和 小于/大于 下一段的和。

然后转移就是枚举一下我们这段要选哪个区间，再枚举一下上一段的和下一段与当前段的和的大小情况，就可以转移了。因为段与段之间不一定连续，所以我们可以再做个前缀 $max$ 即 $f_{i,j,k} = \max{(f_{i,j,k},f_{i-1,j,k})}$ 就能通过 E1 了，时间复杂度 $\mathcal{O}(n^2k)$。

[提交记录](https://codeforces.com/contest/513/submission/230956704)

然后考虑怎么优化。

显然 $m$ 是没法去掉的，所以我们考虑优化选当前段的这个过程。

显然当前段的左边界与右边界是贡献是独立的，即我们一定会选值最大的那个左端点，所以就可以考虑拆成前缀和，然后在 DP 的同时处理一个数组 $g_{j,0/1,0/1}$ 表示选了 $j$ 段，与前一段和后一段的大小关系分别为多少，的最大值。

然后转移也是和上面一样的，非常好写，也非常好想。

[提交记录](https://codeforces.com/contest/513/submission/230957801)


时间复杂度 $\mathcal{O}(nk)$。

---

## 作者：chenzida (赞：1)

思路：

首先这题有一个很暴力的思路：

用 $dp[i][j][k]$ 表示前 $i$ 个数中，我们上一个决策点是 $j$，已经分了 $k$ 组的最大价值。然后转移即可，但是这个不是我们要讲的重点。

然后我们发现，每个点只有几种可能的贡献，分别是 $+2,0,-2$ 以及在头和尾的 $+1,-1$，这样我们一共有 $7$ 中状态，但是由于 $+2 ->0-> +2$ 是不允许的，所以我们吧 $0$ 拆成两个，分别是之前 $+2$，或者之前是 $-2$，所以就愉快的结束了。

代码中的第三维表示：

$0:+2$

$1:\text{接+2的0}$

$2:-2$

$3:\text{开头的+1}$

$4:\text{结尾的+1}$

$5:\text{开头的-1}$

$6:\text{结尾的-1}$

$7:\text{接-2的0}$

代码如下：
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int NR=30005;
const int MR=205;
void Min(int& x,int y){x=min(x,y);}
void Max(int& x,int y){x=max(x,y);}
int n,m;
int ans=0;
int a[NR];
int dp[2][MR][10];
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}
	while(ch<='9'&&ch>='0'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return x*f;
}
signed main()
{
//	freopen("1.in","r",stdin);
//	freopen("1.out","w",stdout);
	n=read(),m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	memset(dp,-0x3f,sizeof(dp));
	for(int i=0;i<=n;i++)
	{
		memset(dp[1],-0x3f,sizeof(dp[1]));
		for(int j=0;j<=m;j++)
		{
			//初始
			if(j==0)dp[1][1][3]=a[i+1],dp[1][1][5]=-a[i+1];
			if(j==0)continue;
			//0
			Max(dp[1][j][0],dp[0][j][0]-2*a[i+1]);
			Max(dp[1][j+1][1],dp[0][j][0]);
			Max(dp[1][j+1][2],dp[0][j][0]+2*a[i+1]);
			Max(dp[1][j+1][4],dp[0][j][0]+a[i+1]);
			//1
			Max(dp[1][j][1],dp[0][j][1]);
			Max(dp[1][j+1][1],dp[0][j][1]);
			Max(dp[1][j+1][2],dp[0][j][1]+2*a[i+1]);
			Max(dp[1][j+1][4],dp[0][j][1]+a[i+1]);
			//2
			Max(dp[1][j+1][0],dp[0][j][2]-2*a[i+1]);
			Max(dp[1][j+1][7],dp[0][j][2]);
			Max(dp[1][j][2],dp[0][j][2]+2*a[i+1]);
			Max(dp[1][j+1][6],dp[0][j][2]-a[i+1]);
			//3
			Max(dp[1][j+1][0],dp[0][j][3]-2*a[i+1]);
			Max(dp[1][j+1][7],dp[0][j][3]);
			Max(dp[1][j+1][6],dp[0][j][3]-a[i+1]);
			Max(dp[1][j][3],dp[0][j][3]+a[i+1]);
			//4
			Max(dp[1][j][4],dp[0][j][4]+a[i+1]);
			//5
			Max(dp[1][j+1][4],dp[0][j][5]+a[i+1]);
			Max(dp[1][j+1][1],dp[0][j][5]);
			Max(dp[1][j+1][2],dp[0][j][5]+2*a[i+1]);
			Max(dp[1][j][5],dp[0][j][5]-a[i+1]);
			//6
			Max(dp[1][j][6],dp[0][j][6]-a[i+1]);
			//7
			Max(dp[1][j][7],dp[0][j][7]);
			Max(dp[1][j+1][7],dp[0][j][7]);
			Max(dp[1][j+1][0],dp[0][j][7]-2*a[i+1]);
			Max(dp[1][j+1][6],dp[0][j][7]-a[i+1]);
			//更新答案 
			if(j==m)Max(ans,dp[0][j][4]),Max(ans,dp[0][j][6]);
		}
		memcpy(dp[0],dp[1],sizeof(dp[0]));
	}
	printf("%lld\n",ans);
	return 0;
}


---

## 作者：ty_mxzhn (赞：0)

什么货梯。

考虑把 $|s_i-s_{i+1}|$ 拆成 $\max(s_i-s_{i+1},s_{i+1}-s_{i})$。此时贡献只会算少不会算多。

问题变成每个点可以选择当做折线的峰也可以当做折线的谷，问你贡献最值。

设计 $f_{i,j,0\sim 3}$ 表示当前折线的状态，转移时直接考虑怎么变化状态。

转移考虑延续上个段还是新开一段，对于下降段和上升段直接考虑要不要单出一个点作为一段，对于峰谷段直接考虑延续或者新开并来到上升和下降段，或者跳过上升和下降段直接来到下一个峰谷段。

但是 $1$ 和 $k$ 要特判，细节较多。

[推歌](https://music.163.com/song?id=487379581&uct2=U2FsdGVkX1/14z0OiKhl7NxzY4Qn0Qsc3hrrxMgtqno=)。

---

## 作者：Purslane (赞：0)

# Solution

考虑直接拆绝对值，对于所有 $2^k$ 种拆法，最大值就是原来套了绝对值的结果。

注意到把 $(i,s_i)$ 扔到二维平面上，并且在相邻列之间连边，会形成山形图。每个点根据他在山腰、山顶、山脚对答案的贡献是 $0$、$2s_i$ 和 $-2s_i$。（当然，首尾必定是山顶或山脚，但是贡献只能为 $\pm 1$）

山顶和山腰交替排列，中间用山腰连接。因此可以写出很平凡的 DP 状态：$dp_{i,j,st1,st2}$ 表示考虑了前 $i$ 个数，已经分出了 $j$ 段，目前段的状态是 $st1$（分别表示山腰、山脚和山顶），$st2$ 表示上一个非山腰是山脚还是山顶（最开始你可以认为存在一个山顶，或者存在一个山腰）

有几种可能：

1. 把 $st1$ 改为 $0$，$j$ 不变。表示切换到不选数的状态。
2. 把 $st1$ 改为 $0$，$j$ 加一。表示新增一个山腰。
3. $st1$ 和 $st2$ 不变，$j$ 也不变，表示延续上次的状态。
4. 根据 $st2$，选择山顶或山脚，$j$ 加一。表示选择山顶或山脚。

复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=30000+10,MAXM=200+10;
int n,k,ans,dp[MAXN][MAXM][3][2],a[MAXN];
int mul(int j,int op1) {
	if(j==1||j==k) return op1==1?-1:1;
	if(!op1) return 0;
	return op1==1?-2:2;
}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>k;
	ffor(i,1,n) cin>>a[i];
	memset(dp,-0x3f,sizeof(dp));
	dp[0][0][0][0]=dp[0][0][0][1]=0;
	//op2 是 0 表示 -，是 1 表示 +
	//op1 是 0 表示平地，是 1 表示 -2，是 2 表示 +2 
	ffor(i,1,n) ffor(j,0,k) ffor(op1,0,2) ffor(op2,0,1) {
		if(op1&&op2!=op1-1) continue ;
		if((j==k||j==1)&&!op1) continue ;
		if(j!=k) dp[i][j][0][op1?(op1-1):op2]=max(dp[i][j][0][op1?(op1-1):op2],dp[i-1][j][op1][op2]);
		dp[i][j][op1][op2]=max(dp[i][j][op1][op2],dp[i-1][j][op1][op2]+a[i]*mul(j,op1));
		//新增一个山坡 
		if(j&&j<=k-2) dp[i][j+1][0][op1?(op1-1):op2]=max(dp[i][j+1][0][op1?(op1-1):op2],dp[i-1][j][op1][op2]);
		//新增山顶
		dp[i][j+1][(op2^1)+1][op2^1]=max(dp[i][j+1][(op2^1)+1][op2^1],dp[i-1][j][op1][op2]+a[i]*mul(j+1,(op2^1)+1));
	}
	ffor(i,1,n) ffor(op1,0,2) ffor(op2,0,1) ans=max(ans,dp[i][k][op1][op2]);
	cout<<ans;	
	return 0;
}
```

---

## 作者：Liuxizai (赞：0)

[My Blog](https://liuxizai.ac.cn/archives/solutions-2024-1.html)

由于是要最大化一些绝对值的和，我们可以直接将绝对值去掉，因为错误指定绝对值开出来的符号只会使答案变劣。现在我们的式子变为了 $\pm(s_1-s_2)\pm(s_2-s_3)\pm(s_4-s_5)\dots$，展开后会发现 $s_1$ 和 $s_k$ 的系数为 $\pm 1$，$s_{2\dots k-1}$ 的系数为 $\pm 2$ 或 $0$，并且所有非零系数一定正负交替。

接下来可以基于此进行 dp，记录当前正在选取的段是什么符号即可，注意开头和结尾可以有一段不选，另外不难证明所选的段必然连续，如果两段之间有数不选，将这些数和左边或右边的段合并至少有一种方式是不劣的。于是设 $f_{i,j,0/1,0/1}$ 表示已经考虑了前 $i$ 个数，正在选取第 $j$ 段，上一个系数非零的段的符号是 $+/-$，第 $j$ 段系数是否为 $0$ 时原式的最大值，转移时考虑继续扩展当前段或新开一段即可，注意特殊处理第一段和最后一段的系数。

[Submission #240105698](https://codeforces.com/contest/513/submission/240105698)

**Insights.** 最优化目标和限制一致时可以将限制去掉。

---

