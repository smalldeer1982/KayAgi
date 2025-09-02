# Coin Rows

## 题目描述

Alice and Bob are playing a game on a matrix, consisting of $ 2 $ rows and $ m $ columns. The cell in the $ i $ -th row in the $ j $ -th column contains $ a_{i, j} $ coins in it.

Initially, both Alice and Bob are standing in a cell $ (1, 1) $ . They are going to perform a sequence of moves to reach a cell $ (2, m) $ .

The possible moves are:

- Move right — from some cell $ (x, y) $ to $ (x, y + 1) $ ;
- Move down — from some cell $ (x, y) $ to $ (x + 1, y) $ .

First, Alice makes all her moves until she reaches $ (2, m) $ . She collects the coins in all cells she visit (including the starting cell).

When Alice finishes, Bob starts his journey. He also performs the moves to reach $ (2, m) $ and collects the coins in all cells that he visited, but Alice didn't.

The score of the game is the total number of coins Bob collects.

Alice wants to minimize the score. Bob wants to maximize the score. What will the score of the game be if both players play optimally?

## 说明/提示

The paths for the testcases are shown on the following pictures. Alice's path is depicted in red and Bob's path is depicted in blue.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1555C/252b3575ef3aca0ba0371198bcb73812484716e5.png)

## 样例 #1

### 输入

```
3
3
1 3 7
3 5 1
3
1 3 9
3 5 1
1
4
7```

### 输出

```
7
8
0```

# 题解

## 作者：wind_seeker (赞：19)

作为直到最后才勉强通过的蒟蒻，在这里发篇题解记录一下我的想法。

~~悲伤了，卡点过水题~~

[原题链接](https://www.luogu.com.cn/problem/CF1555C)

## 题意解释

题目的意思，大概是这样的：

有一个 $2$ &times; $m$ 的矩阵。

Alice 和 Bob 都在矩阵上的 $(1,1)$ 处。 Alice 先出发，每到一个房间就会将这个房间所有的 coins 全部都拿走，她很**聪明**（~~她总是很聪明~~），会用最**聪明**的走法，使得在她拿走她经过路径上的所有    coins 之后，让 Bob 接下来走的时候拿的最大的 coins 总和最小。而
 Bob 也非常的**聪明**（~~他也总是很聪明~~）,会在 Alice 走后,选取一条路径可以使得他在剩下的 coins 拿走最大的总和。

注意：**每一次他们都只能往右和往下走一步**。

输出在他们两个人都很聪明的情况下 Bob 最后的得分。

## 关键点

曾经有一位巨佬说过，做题，需要找到题目的关键点。

所以我们先来看一下，这道题目中的一线关键点：

- **Alice 和 Bob 都很聪明 ~~(这是重点，着重关注)~~**
- **每一次他们都只能往右和往下走一步**
- **一个 $2$ &times; $m$ 的矩阵**
 
第一个关键点给我们带来的是，**答案一定是最优解** ~~（fake几句）~~ 。  
第二个关键点给我们的信息是**一旦 Alice 和 Bob 下去以后，就不能上来了
。**
第三个关键点提示我们，~~**这其实是一道水题**~~。

## 画图找解法
接下来我们采用画图的方式，找到答案.  
**绿色是 Alice 走的路径**。

![](https://cdn.luogu.com.cn/upload/image_hosting/fpi6uldr.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/o6ul7vd8.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/8fuy1zx8.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/heqbx4xm.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/pa2dom0h.png)

**感谢[@QueenSi](https://www.luogu.com.cn/user/431697)的画图助力**

我相信大家已经从图中发现了， Alice **从哪个位置下去**就决定了她所走的路径，也就决定了 Bob 能得到的 coins 最大的总和。

由于 Bob 与 Alice 的路径限制条件一样，且矩阵高为 $2$，所以我们就会发现图中**红色部分**和**蓝色部分**就是出现 **Bob 能得到 coins  最大的总和的唯一的两个区域。**

那么一切就都已经出来了，接下来，附上代码，完事！
## CODE
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=1e5+1e3;
int T,m;
int a[maxn],b[maxn],ans[maxn],sum1,sum2,answer;
inline int read()
{
	int res=0,f=1;char c;
	for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
	for(;isdigit(c);c=getchar()) res=(res<<1)+(res<<3)+(c^48);
	return res*f;
}
signed main()
{
	T=read();
	while(T--)
	{
		memset(ans,0,sizeof ans); //初始化ans值 
		answer=0x3f3f3f3f,sum1=0,sum2=0;//将ans赋值为0x3f3f3f3f，方便后面取min
		//sum1记录在i位置下去时上方红色部分总和
		//sum2记录在i位置下去时下方蓝色部分总和 
		m=read();
		for(int i=1;i<=m;i++) a[i]=read(),sum1+=a[i];//提前处理好第一排总和 
		for(int i=1;i<=m;i++)
		{
			b[i]=read();
			sum1-=a[i];//由上面图可知，红色部分从i+1开始 
			ans[i]=max(sum1,sum2);//取蓝色部分和红色部分中的大值（Bob的聪明） 
			answer=min(ans[i],answer);//取所有蓝色部分和红色部分中的大值中的最小值（Alice的聪明） 
			sum2+=b[i];// 由上面图可知，蓝色部分到i-1结束 
		}
		printf("%lld\n",answer);//最后输出answer,完事 
	}
	return 0;
}


```
**蒟蒻拙见，大佬勿喷**



---

## 作者：Gokix (赞：5)

[CF1555C](https://www.luogu.com.cn/problem/CF1555C)

注意到不管 Alice 怎么走，她走完后棋盘上只会剩下第一行的一个后缀和第二行的一个前缀：

![](https://cdn.luogu.com.cn/upload/image_hosting/1b2wh7jy.png)


又注意到 Bob 只可能取得这两部分的其中之一。而所有的数又都是正的，所以最优一定是把某一部分全部取得。

于是做法显然了：预处理第一行后缀和 $suf$、第二行前缀和 $pre$。枚举 Alice 的拐点 $i$，最终答案 $ans=\min\limits_{i=1}^{m}\{\max(suf_{i+1},pre_{i-1})\}$。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;

long long t,n,a[100010],b[100010],pre[100010],suf[100010],ans;

int main(){
    long long i,j,u,v;
    cin>>t;
    while(t--){
        cin>>n;
        for(i=0;i<=n+1;i++){pre[i]=suf[i]=0;}
        for(i=1;i<=n;i++) cin>>a[i];
        for(i=1;i<=n;i++) cin>>b[i],pre[i]=pre[i-1]+b[i];
        for(i=n;i>=1;i--) suf[i]=suf[i+1]+a[i];
        if(n==1){
            cout<<0<<endl;
            continue;
        }
        ans=1000000000000;
        for(i=1;i<=n;i++){
            ans=min(ans,max(pre[i-1],suf[i+1]));
        }
        cout<<ans<<endl;
    }
    return 0;
}
```


---

## 作者：QZY2008 (赞：4)

### 题目大意:
Bob 和 Alice 在玩游戏，游戏在一个 $ 2 \times N $ 的矩阵中进行。

规则:

1.只能往下和右走。

2.Alice 先走。

3.Alice 想让 Bob 走得分最少。

4.求 Bob 的最高得分。

### 思路:
对于 $ 2 \times N $ 的矩阵，可以考虑做前缀，后缀和优化。

很显然,对于第 $ i $ 列，可以求 $ i-1 $ 前缀和和 $ i+1 $ 后缀和中最大值。

我们求的答案即为 $ 1-n $ 列中上述最小值。

### 温馨提示 ~~(废话)~~

对于每组数据，不要 memset 清空，不然容易被 Hack 。

详见代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int num[3][N];
int q_sum[N];//前缀和数组
int h_sum[N];//后缀和数组
int n;
int t;
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for (int i=1;i<=2;i++)
			for (int j=1;j<=n;j++)
				scanf("%d",&num[i][j]);
		q_sum[0]=0;//直接清第一个
		h_sum[n+1]=0;//直接清最后一个
		for (int i=n;i>=1;i--)
			h_sum[i]=h_sum[i+1]+num[1][i];
		for (int i=1;i<=n;i++)
			q_sum[i]=q_sum[i-1]+num[2][i];
		int tmp=2147483647; 
		for (int i=1;i<=n;i++)
			tmp=min(tmp,max(q_sum[i-1],h_sum[i+1]));
		printf("%d\n",tmp);
	}
   return 0;//完结撒花
} 
```

---

## 作者：江户川·萝卜 (赞：1)

首先容易发现两人走的路径一定是向右、向下、向右。

那么当 `Alice` 走过之后（下图红色路线）留给 `Bob` 的只有黄色的区域。

![](https://cdn.luogu.com.cn/upload/image_hosting/amiymhab.png)

所以 `Bob` 每次的最优情况要么就是一开始就向下走，取下面的黄色部分；或是走到底再往下走，取上面的黄色部分，也即取两部分各自总和的最大值。

由于 `Alice` 想要最小值，那么就扫一遍，取两部分各自总和的最大值的最小值即可。

用前缀和维护。

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int sum[2][100005];
int main(){
	int t;
	cin>>t;
	while(t--){
		int m;
		scanf("%d",&m);
		sum[1][0]=sum[0][0]=0;
		for(int i=1;i<=m;i++){
			int val;scanf("%d",&val);
			sum[0][i]=sum[0][i-1]+val;
		}
		for(int i=1;i<=m;i++){
			int val;scanf("%d",&val);
			sum[1][i]=sum[1][i-1]+val;
		}
		int ans=1e9;
		for(int i=1;i<=m;i++){
			ans=min(ans,max(sum[1][i-1],sum[0][m]-sum[0][i]));
		}
		printf("%d\n",ans);
	}
	return 0;
} 
``

---

## 作者：iMya_nlgau (赞：1)

由于格子只有两行，且只能向右和向下走，所以走的方案一定存在一个拐点 $i$，在 $1$ 到 $i$ 列走第一行，下到第二行，再走第二行的 $i$ 到 $m$ 列。

由于 $a_{i,j}\geq 1$，所以无论 Alice 怎么走，Bob 要想最大化分数，只能走 $(1,1)\to (2,1)\to (2,m)$ 或 $(1,1)\to (1,m)\to (2,m)$ 两种路线（可以看看样例的图）。

我们分别预处理两行的前缀和，枚举 Alice 的路线，计算答案即可。

#### 代码

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
inline int read(){int x=0,f=0;char c=getchar();while(c<'0'||c>'9')f|=c=='-',c=getchar();while(c>='0'&&c<='9')x=x*10+c-'0',c=getchar();return f?-x:x;}
int a[100010],b[100010],c[100010],d[100010];
signed main(){
	   int T=read();
	   while(T--){
			int n=read();
			for(int i=1;i<=n;i++) a[i]=read(),c[i]=c[i-1]+a[i];
			for(int i=1;i<=n;i++) b[i]=read(),d[i]=d[i-1]+b[i];
			int ans=1000000000;
			for(int i=1;i<=n;i++)
				ans=min(ans,max(c[n]-c[i],d[i-1]));
			 printf("%d\n",ans);
	   }
	return 0;
}


```

---

## 作者：Microperson (赞：1)

[题目](https://www.luogu.com.cn/problem/CF1555C)
## 题目大意：
给定一个 $2$ 行，$m$ 列的矩阵，有两个人从 $(1,1)$ 走到 $(2,m)$，他们有先后顺序，每一个人走过之后都会拿走该位置上的硬币，第一个人想让第二个人拿到的少，第二个人想得到的多，求第二个人最多能得到多少。
## 腐朽的思路：
因为只有两行并且只能向下或向右走，我们只需要处理每一行的前缀和，枚举第一个人走过的路径的方案，处理出对于每一种方案的最多能取到多少硬币，同时处理出最小值就可以了。
## 新鲜出炉的code：
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
using namespace std;

int t,m,sum[3][100010],a[3][100010],ans,flag,anss=2147483647;
//数组一定要开够呀，我在这死了好长时间
int main(){
//	freopen("aa.in","r",stdin);
	scanf("%d",&t);
	while(t--){
		ans=0,anss=1e9+10;
		memset(sum,0,sizeof(sum));
		scanf("%d",&m);
		for(int i=1;i<=2;i++){
			for(int j=1;j<=m;j++){
				scanf("%d",&a[i][j]);
				sum[i][j]=sum[i][j-1]+a[i][j];
			}
		}
		if(m==1){
			cout<<0<<endl;
			continue;
		}
		for(int i=1;i<=m;i++){
				anss=min(anss,max(sum[1][m]-sum[1][i],sum[2][i-1]));				
		}
		printf("%d\n",anss);
	}
	return 0;
} 
```


---

## 作者：NXYorz (赞：1)

[题目链接](https://www.luogu.com.cn/problem/CF1555C)

----
### 题目大意
有一个 $2$ 行 $m$ 列的矩阵。每一个格子有金币。两个小朋友玩捡金币的游戏。第一个小朋友想让第二个小朋友获得的金币近可能少，第二个小朋友在第一个小朋友捡完金币后，想在此基础上获得的金币尽可能的多。问第二个小朋友在第一个小朋友的阻挠下，最多可以获得多少金币。

每一个小朋友只能向右或者向下走。

---------
### 分析

DP? ~~省省吧你。~~

注意第一个小朋友并不是尽可能多捡金币，而是使第二个小朋友的金币尽可能少。

发现只有矩阵只有两行，而且每一个小朋友只能向右或者向下走。 也就是说第一个小朋友只能捡第一行的一个前缀 **以及** 第二行的一个后缀。第二个小朋友只能捡第一行后缀 **或者** 第二行前缀。

于是我们枚举列，使第一行后缀与第二行前缀的最大值尽可能小即可。

---------
### $\texttt{Code}$
```cpp
#include<cstdio>
#include<cstring>

using namespace std;

const int N = 1e5 + 10;

int m; 
int sum[3][N] , a[3][N];

inline int max(int x , int y)
{return x > y ? x : y;}

inline int min(int x , int y)
{return x > y ? y : x;}

void work()
{
    
    memset(sum , 0 , sizeof(sum));
    scanf("%d",&m);
    for(int i = 1; i <= 2; i++)
        for(int j = 1; j <= m; j++)
            scanf("%d",&a[i][j]) , sum[i][j] = sum[i][j - 1] + a[i][j];
    
    int ans = 1e9 + 10;
    for(int i = 1; i <= m; i++)
        ans = min(ans , max(sum[1][m] - sum[1][i] , sum[2][i - 1]));
    
    printf("%d\n",ans); return;
}

int main()
{
  //  freopen("aa.in","r",stdin);
    int t; scanf("%d",&t);
    while(t--)
        work();
}
```

---

## 作者：_Clown_ (赞：0)

# C.Coin Rows
$\mathtt{Difficulty}$=$\mathtt{1300}$

看懂题目之后，我们来观察样例。

我们提出一个猜想：Bob 只能先一直往右，再一直往下或是先一直往下，再一直往右。

然后我们考虑分别用前缀和维护一下，不然会 $\texttt{TLE}$。

维护完之后，暴力枚举 Alice 的路线即可。

然后就不难写出代码了。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int N;
int Dp1[100001],Dp2[100001];
signed main(void)
{
    register int Case;cin>>Case;while(Case--)
    {
        register int i;cin>>N;
        for(i=1;i<=N;i++)Dp1[i]=Dp2[i]=0;
        for(i=1;i<=N;i++){register int X;cin>>X;Dp1[i]=Dp1[i-1]+X;}
        for(i=1;i<=N;i++){register int X;cin>>X;Dp2[i]=Dp2[i-1]+X;}
        register int Ans;
        Ans=min(Dp1[N]-Dp1[1],Dp2[N-1]);
        for(i=2;i<N;i++)Ans=min(Ans,max(Dp1[N]-Dp1[i],Dp2[i-1]));
        if(N==1)Ans=0;
        cout<<Ans<<endl;
    }
    return 0;
}
```

---

## 作者：happy_dengziyue (赞：0)

### 1 思路

设这个矩阵为 $a_{[1,2],[1,m]}$。

可以发现，`Alice` 在走的时候，只有一个点是她往下走的点。设这一列是 $i$。

为了获得最多的金币，`Bob` 只有 $2$ 种选择：

$$(1,1)\to(2,1)\to(2,m)$$

和

$$(1,1)\to(1,m)\to(2,m)$$

实际上，他能拿到金币的区间也只是：

$$(2,1)\to(2,i-1)$$

和：

$$(1,i+1)\to(1,m)$$

那么，设二维数组 $s$。其中：

$$s[1][i]=\sum_{j=1}^ia[1][j]$$

$$s[2][i]=\sum_{j=1}^ia[2][j]$$

那么，这 $2$ 个拿到金币的区间的金币数就是：

$$s[2][i-1]$$

和

$$s[1][m]-s[1][i]$$

枚举每一个 $i$，则答案为：

$$ans=\operatorname{min}(\operatorname{max}(s[2][i-1],s[1][m]-s[1][i]))\ (1\le i\le m)$$

然后输出就行了。

### 2 代码与记录

```cpp
#include<cstdio>
using namespace std;
int t;
#define max_m 100000
int m;
int a[3][max_m+2];
int s[3][max_m+2];
int ans;
int ma(int a,int b){
	return a>b?a:b;
}
int mi(int a,int b){
	return a<b?a:b;
}
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1555C_1.in","r",stdin);
	freopen("CF1555C_1.out","w",stdout);
	#endif
	scanf("%d",&t);
	for(int ca=1;ca<=t;++ca){
		scanf("%d",&m);
		for(int i=1;i<=m;++i){
			scanf("%d",a[1]+i);
		}
		for(int i=1;i<=m;++i){
			scanf("%d",a[2]+i);
		}
		for(int i=1;i<=m;++i){
			s[1][i]=s[1][i-1]+a[1][i];
		}
		for(int i=1;i<=m;++i){
			s[2][i]=s[2][i-1]+a[2][i];
		}
		ans=s[1][m]-a[1][1];
		for(int i=2;i<=m;++i){
			ans=mi(ans,ma(s[1][m]-s[1][i],s[2][i-1]));
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/54627725)

By **dengziyue**

---

## 作者：超级玛丽王子 (赞：0)

第一需要知道的是，Alice 实际上只有 $m$ 种选择，即 $\text{down}$ 操作进行时所在的列。通过数据范围中的 $\sum m\le 10^5$ 可知可以通过 $O(m)$ 枚举得到答案。

考虑设拐点为 $k$。注意到 Alice 走过的路径上的点都会变为 $0$，那么 Alice 走完后序列实际上被分割为了两部分，即 $a_{2,[1,k-1]}$ 和 $a_{1,[k+1,m]}$。Bob 要做的就是从这两段里面选一段，形式化的说，就是求

$$\text{ans}=\max\{\sum_{i=1}^{k-1}a_{2,i},\sum_{i=k+1}^ma_{1,i}\}$$

~~其实 Bob 几乎啥选择权也没有~~

于是维护两行的前缀和即可 $O(m)$ 得到答案。

核心代码：

```cpp
const int maxn=1e5+50;
int a[2][maxn],pre[2][maxn],mn=0x3f3f3f3f;
int m;
cin>>m;
for(int i=1;i<=m;++i) {
	cin>>a[0][i];
    pre[0][i]=pre[0][i-1]+a[0][i];
}
for(int i=1;i<=m;++i) {
	cin>>a[1][i];
    pre[1][i]=pre[1][i-1]+a[1][i];
}
for(int k=1;k<=m;++i) { //枚举拐点
    mn=min(mn,max(pre[0][k-1],pre[1][m]-pre[1][k]));
}
cout<<mn<<endl;
```

---

## 作者：A_zjzj (赞：0)

[更好的阅读体验](https://blog.csdn.net/A_zjzj/article/details/119281389)

## 题目大意
有一个 $2\times m$ 的矩阵，每次从 $(1,1)$ 号点，往下或往右走到 $(2,m)$。Alice 先出发，把经过的点上的权值清空，然后 Bob 再出发，把经过的点上的权值加起来作为答案。Alice 希望最小化答案，Bob 希望最大化答案，求最后的答案。

## 思路
首先，从 $(1,1)$ 走到 $(2,m)$ 的路径条数也不过就 $m$ 条，考虑枚举 Alice 走的路径（枚举从哪一列往下走），然后注意到 $a_{i,j}\ge1$，所以 Bob 一定是选得越多越好，那么 Bob 要么到了 $(1,m)$ 再往下走，要么在 $(1,1)$ 就往下走，这样答案最大。

这样就可以发现，Bob 最后拿到分数的点要么是第一行的一段后缀，要么是第二行的一段前缀，所以预处理第一行的后缀和以及第二行的前缀和，枚举 Alice 走的路径，计算答案就可以了。

每次注意把后缀和以及前缀和的数组清空，不然会影响之后的答案。

## 代码
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
void read(){}
template<typename _Tp,typename... _Tps>
void read(_Tp &x,_Tps &...Ar){
	x=0;char c=getchar();bool flag=0;
	while(c<'0'||c>'9')flag|=(c=='-'),c=getchar();
	while(c>='0'&&c<='9')x=(x<<3)+(x<<1)+(c^48),c=getchar();
	if(flag)x=-x;
	read(Ar...);
}
const int N=1e5+10;
int n,a[3][N],suf[N],pre[N];
int get(){
	int i,j,ans=0x3f3f3f3f;
	for(read(n),i=1;i<=2;i++)for(j=1;j<=n;j++)read(a[i][j]);
	for(pre[1]=a[2][1],i=2;i<=n;i++)pre[i]=pre[i-1]+a[2][i];//前缀和
	for(suf[n]=a[1][n],i=n-1;i>=1;i--)suf[i]=suf[i+1]+a[1][i];//后缀和
	for(i=1;i<=n;i++)ans=min(ans,max(suf[i+1],pre[i-1]));//计算答案
	for(i=1;i<=n;i++)suf[i]=pre[i]=0;
	return printf("%d\n",ans),0;
}
int main(){
	int T;read(T);while(T--)get();
	return 0;
}
```
## 谢谢--zhengjun

---

## 作者：AmamiyaYuuko (赞：0)

题目相当于最小化 Bob 的收益。由于 $a_{i, j} > 0$，那么当 Alice 走完以后，Bob 走的路径只有两条：$(1, 1) \rightarrow (2, 1) \rightarrow (2, m)$ 或 $(1, 1) \rightarrow (1, m) \rightarrow (2, m)$。

注意到 Alice 只能选择一个点将她的行数从 $1$ 变为 $2$，于是枚举这个点 $p$，同时预处理两行的前缀和便于更新答案。

在这个点确定以后，由于上面的性质，Bob 的收益为 $\sum \limits_{i = p + 1}^{n}a_{1, i}$ 或 $\sum \limits_{i = 1}^{p}a_{2, i}$。只需要让这两者的最大值最小即可。

代码：

```cpp
while (T--) {
    for (int i = 1; i <= m + 1; ++i)    f[i] = g[i] = 0;
    read(m);
    min = 1e18;
    for (int i = 1; i <= 2; ++i) {
        for (int j = 1; j <= m; ++j) {
            read(a[i][j]);
        }
    }
    for (int i = m; i >= 1; --i)    f[i] = f[i + 1] + a[1][i], g[i] = g[i + 1] + a[2][i];
    for (int i = 1; i <= m; ++i) {
        LL s1 = f[i + 1], s2 = g[1] - g[i];
        LL s = std::max(s1, s2);
        min = std::min(s, min);
    }
    printf("%lld\n", min);
}
```

---

## 作者：冰糖鸽子 (赞：0)

~~第一眼以为博弈论，吓死了~~

我们模拟几次 Alice 的行走，或者简单想一下就会发现，Alice 的轨迹是上下两段只有端点重合的线段（但是你不能让上面那段的左端点和下面那段的右端点重合）。

而 Alice 走完之后，矩阵中有数的地方只剩下了两块（也可能是一块），第一块在第一行，从第 $i$ 个数到第 $n$ 个数，$i$ 可以取 $[2,n+1]$；第二块在第二行，从第 $1$ 个数到第 $i-2$ 个数，两段中的 $i$ 相同。

具体的可以看样例解释第一幅图，就是一个 $i=3$ 的情况。

这时，Bob 只有两种选择，即选两块中的一块，因为他如果选择拿第二块，或者说拿第二块中的某些数，就会早早往下，这时候他就回不去第一行了。如果拿第一块也拿不到第二块，道理差不多。

所以咱们可以枚举 $i$ ，取两块中的 $\max$（因为这个时候是 Bob在选），然后再对这 $n$ 个 $\max$ 取 $\min$（因为这个时候是 Alice 在选）。

代码：

```cpp

// Problem: C. Coin Rows
// Contest: Codeforces - Educational Codeforces Round 112 (Rated for Div. 2)
// URL: https://codeforces.ml/contest/1555/problem/C
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
using namespace std;
#define int long long
#define M 100005
const int inf=1e15;
int n,m,k,a[M],T,suma[M],ans,sumb[M];
signed main()
{
	cin>>T;
	while(T--)
	{
		cin>>n,suma[n+1]=0,ans=inf;
		for(int i=1;i<=n;i++) cin>>a[i];
		for(int i=n;i>=1;i--) suma[i]=suma[i+1]+a[i];
		for(int i=1;i<=n;i++) cin>>a[i],sumb[i]=sumb[i-1]+a[i];
		for(int i=0;i<n;i++) ans=min(ans,max(sumb[i],suma[i+2]));
		cout<<ans<<endl;
	}
	return 0;
}
```

---

