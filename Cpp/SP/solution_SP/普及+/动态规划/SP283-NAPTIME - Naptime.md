# NAPTIME - Naptime

## 题目描述

在某个星球上，一天由 $n$ 小时构成。我们称 $0 \sim 1$ 点为第一个小时，$1 \sim 2$ 点为第二个小时，以此类推。在第 $i$ 个小时睡觉能恢复 $U_i$ 点体力。在这座星球上住着一头牛，它每天要休息 $B$ 个小时，它休息的这 $B$ 个小时可以不连续，可以分成若干段，但是在每一段的第一个小时不能恢复体力，从第二个小时开始才可以恢复体力。
为了身体健康，这头牛希望遵循生物钟，每天采用相同的睡觉计划。另外，因为时间是连续的，每天的第 $n$ 个小时与下一天的第一个小时是相连的，这头牛只需要在 $n$ 个小时内休息 $B$ 个小时就够了。
请你给这头牛安排一个任务计划，使得它每天恢复的体力最多。

## 样例 #1

### 输入

```
1
5 3
2
0
3
1
4```

### 输出

```
6

Input/Output details:
The day is divided into 5 periods, with utilities 2, 0, 3, 1, 4 in that 
order. Goneril must pick 3 periods.

Goneril can get total utility 6 by being in bed during periods 4,
5, and 1, with utilities 0 [getting to sleep], 4, and 2
respectively.```

# 题解

## 作者：Itst (赞：12)

翻译题解~~素质二连~~

 这道题~~很明显~~是一道线性DP

 但是第N小时与下一天第一小时连着的条件真的很不爽！

 如果没有这个条件这道题简直秒解！（状态转移方程就不赘述，下面代码里有）

------------
 当你有以上的想法的时候就表示你离标算又近了一步【滑稽

 不妨先把“第N小时与下一天第一小时连着”的条件去掉，变成一个普通的线性DP。

 而上面的普通线性DP与本题的环形DP本质区别在哪里？
------------
 考虑一下去掉条件的DP，会发现第一天第N小时如果在休息，是无法影响到第二天的第一个小时的，也就是没有计算到第一天第N个小时休息延续到第二天第一个小时的情况

 那我们只需要强行令第N个小时休息并延续到第1个小时使第一个小时获得休息能量并再做一次DP就可以了

 这一次DP里状态转移方程同上，只不过第一个小时算上休息恢复的能量，而结果则只能取第N个小时在休息时的最大能量。

 两个DP综合起来取max就是答案。

 老规矩

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int max(int a , int b){
    return a > b ? a : b;
}
int DP1[3831][3831][2] , DP2[3831][3831][2] , num[3831];
//DP1断环，DP2强制接环
int main(){
    int T , N , K;
 	for(scanf("%d" , &T) ; T ; T--){
 		scanf("%d%d" , &N , &K);
 		for(int i = 1 ; i <= N ; i++)	scanf("%d" , num + i);
 		for(int i = 0 ; i <= N ; i++)
 			for(int j = 0 ; j <= K ; j++)
 				DP1[i][j][0] = DP1[i][j][1] = DP2[i][j][0] = DP2[i][j][1] = -0x3f3f3f3f;
 		DP1[1][1][1] = DP1[1][0][0] = 0;
 		DP2[1][1][1] = num[1];
        for(int i = 2 ; i <= N ; i++)
 			for(int j = 0 ; j <= N && j <= K ; j++){
 				DP1[i][j][0] = max(DP1[i - 1][j][0] , DP1[i - 1][j][1]);
 				DP2[i][j][0] = max(DP2[i - 1][j][0] , DP2[i - 1][j][1]);
                if(j){
                    DP1[i][j][1] = max(DP1[i - 1][j - 1][1] + num[i] , DP1[i - 1][j - 1][0]);
                    DP2[i][j][1] = max(DP2[i - 1][j - 1][1] + num[i] , DP2[i - 1][j - 1][0]);
                }
            }
            //状态转移
        cout << max(max(DP1[N][K][0] , DP1[N][K][1]) , DP2[N][K][1]) << endl;
        //注意DP2（强制接环）中只有第N个小时在休息时的答案才能够计算入内。
    }
    return 0;
}
```

---

## 作者：niiick (赞：11)

首先假设一天的第N小时与后一天的第一个小时**不相连**，
这种情况下DP转移比较好想

$dp[i][j][0/1]$表示

考虑一天的**前i个小时**，**已经休息了j小时**，且**第i个小时是否在休息**

那么有状态转移方程
```
dp[i][j][0]=max(dp[i-1][j][0],dp[i-1][j][1]);
dp[i][j][1]=max(dp[i-1][j-1][0],dp[i-1][j-1][1]+a[i]);
```
初始化为$dp[1][0][0]=dp[1][1][1]=0$，
其余为$-inf$

答案为$max(dp[n][b][0],dp[n][b][1])$

现在再考虑一天的第N小时与后一天的第一个小时**相连**

我们发现上述转移中，
唯一没考虑到的情况只有**第1个小时休息能获得体力**

于是我们可以**初始化**$dp[1][1][1]=U_1$，
**转移方程与上述相同**

那么答案为$dp[n][b][1]$(即**强制最后一小时休息令第一小时能获得体力**)，
和前一次dp的答案比较即可得到最终结果

到此为止在这里已经可以AC，
但是！！！如果我们拿到POJ上提交，
你会发现自己疯狂MLE(POJ丧心病狂的Memory limit只有64M)

于是我们考虑用**滚动数组**优化空间
```
dp[i&1][j][0]=max(dp[(i-1)&1][j][0],dp[(i-1)&1][j][1]);
dp[i&1][j][1]=max(dp[(i-1)&1][j-1][0],dp[(i-1)&1][j-1][1]+a[i]);
```
因为dp[i][][]只与dp[i-1][][]有关，
所以只要**交替使用数组第0维和第1维**，
**只保存上一次更新的dp数组**，
即可大幅优化空间
```
//niiick
#include<iostream>
#include<cmath>
#include<algorithm>
#include<queue>
#include<cstring>
#include<cstdio>
#include<map>
using namespace std;
typedef long long lt;
 
int read()
{
    int x=0,f=1;
    char ss=getchar();
    while(ss<'0'||ss>'9'){if(ss=='-')f=-1;ss=getchar();}
    while(ss>='0'&&ss<='9'){x=x*10+ss-'0';ss=getchar();}
    return x*f;
}

const int maxn=4010;
int t,n,m,ans;
int a[maxn];
int dp1[2][maxn][2],dp2[2][maxn][2];

int main()
{
    t=read();
    while(t--)
    {
    	n=read();m=read();ans=0;
    	for(int i=1;i<=n;++i)a[i]=read();
        
    	memset(dp1,128,sizeof(dp1));
    	dp1[1][0][0]=dp1[1][1][1]=0;
        
    	memset(dp2,128,sizeof(dp2));
    	dp2[1][1][1]=a[1];
        
    	for(int i=2;i<=n;++i)
    	for(int j=0;j<=min(i,m);++j)
    	{
        	dp1[i&1][j][0]=max(dp1[(i-1)&1][j][0],dp1[(i-1)&1][j][1]);
        	if(j>=1)dp1[i&1][j][1]=max(dp1[(i-1)&1][j-1][0],dp1[(i-1)&1][j-1][1]+a[i]);
            
        	dp2[i&1][j][0]=max(dp2[(i-1)&1][j][0],dp2[(i-1)&1][j][1]);
        	if(j>=1)dp2[i&1][j][1]=max(dp2[(i-1)&1][j-1][0],dp2[(i-1)&1][j-1][1]+a[i]);
    	}
    	ans=max(dp2[n&1][m][1],max(dp1[n&1][m][1],dp1[n&1][m][0]));
    	printf("%d\n",ans);
    }
    return 0;
}
```


---

## 作者：cjlak1o1 (赞：5)

[双倍经验好评](https://www.luogu.com.cn/problem/P6064)  
[博客食用效果更佳](https://www.cnblogs.com/windseekerblog/p/16518680.html)

蒟蒻第一次用这样的方式做环上dp，实在是想记录和总结一下。

### 环上dp的做法

1. 我们将环切成一个链之后，倍长该链做dp即可做到从每一位出发，可参考[P1880石子合并](https://www.luogu.com.cn/problem/P1880)。

2. 我们抢先将环切成一条链，然后枚举断点的状态，即为这道[SP283](https://www.luogu.com.cn/problem/SP283)。

### 条件

- $n$ 时间内总共睡 $b$ 小时。

- 每一段睡觉区间第一段时间不参与贡献。

### 思路

这是一个环上dp，由于 $n$ 有点小大，我们采取枚举断点状态的方式。

### 状态转移方程

$dp_{i,j,1/0}$ 表示 $i$ 时刻睡了 $j$ 小时，$1$ 表示睡了。

$$dp_{i,j,0}=\max(dp_{i-1,j,0},dp_{i-1,j,1})$$

没睡则直接延续上一个时刻。

$$dp_{i,j,1}=\max(dp_{i-1,j-1,0},dp_{i-1,j-1,1}+a_i)$$

睡了讨论上一个时刻的情况，上一个时刻没睡则本时刻为第一段时间，不参与贡献。

### 断点讨论

1. $n$ 时刻没睡，那么 $i$ 时刻要么睡，要么为第一段时间。
```cpp
dp[1][0][0]=0,dp[1][1][1]=0;
```
2. $n$ 时刻睡了，那么 $i$ 时刻睡了可参与贡献，由于这是一个环，我们会在后面状态转移的时候到达 $n$ 同样会有 $n$ 时刻睡了的情况，所以不用担心 $n$ 时刻的状态没有记录。
```cpp
dp[1][0][0]=0,dp[1][1][1]=a[1];
```
### code

```cpp
//dp[i][j][0]=max(dp[i-1][j][0],dp[i-1][j][1]);
//dp[i][j][1]=max(dp[i-1][j-1][0],dp[i-1][j-1][1]+a[i]);
//i-1没睡，i睡了也没用
//i时刻，已经睡了j小时，当前睡没睡 
#include<bits/stdc++.h>
//define int long long //不要开longlong，会mle。
using namespace std;
const int N=3840;

template<class T> T read(T &x){
	char c=getchar();bool f=0;x=0;
	while(!isdigit(c)) f|=c=='-',c=getchar();
	while(isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
	return f?-x:x;
} 

int T,n,b,ans=-1;
int a[N];
int dp[N][N][2]; //第一篇题解状转更牛哦，新手学习这个没关系

int main(){
	read(T);
	while(T--){
		read(n),read(b);
		for(int i=1;i<=n;i++) read(a[i]);
		memset(dp,-0x3f,sizeof(dp));//n时刻没睡
		dp[1][0][0]=0;
		dp[1][1][1]=0;
		for(int i=2;i<=n;i++){
			for(int j=0;j<=min(i,b);j++){
				dp[i][j][0]=max(dp[i-1][j][0],dp[i-1][j][1]);//直接顺延
				dp[i][j][1]=max(dp[i-1][j-1][0],dp[i-1][j-1][1]+a[i]); 
			}
		}
		ans=dp[n][b][0];
		memset(dp,-0x3f,sizeof(dp));////n时刻睡了
		dp[1][0][0]=0;
		dp[1][1][1]=a[1];
		for(int i=2;i<=n;i++){
			for(int j=0;j<=min(i,b);j++){
				dp[i][j][0]=max(dp[i-1][j][0],dp[i-1][j][1]);
				dp[i][j][1]=max(dp[i-1][j-1][0],dp[i-1][j-1][1]+a[i]);
			}
		}
		ans=max(ans,dp[n][b][1]);
		printf("%d\n",ans);
	}
	
}
/*
5 3
2
0
3
1
4
*/
/*
6
*/
```

**蒟蒻拙见，请指教**

---

## 作者：Huami360 (赞：4)

[原文](https://www.cnblogs.com/Qihoo360/p/9566842.html)食用效果更佳

[题目链接](https://www.luogu.org/problemnew/show/SP283)

先考虑如果只有一天，那么该怎么做。
设$f[i][j][1]$表示前$i$个小时睡了$j$个小时并且第$j$个小时正在睡觉时的最大体力，$f[i][j][1]$表示前$i$个小时睡了$j$个小时并且第$j$个小时没在睡觉时的最大体力。
则有
$$f[i][j][0]=max(f[i-1][j][0],f[i-1][j][1])$$
$$f[i][j][1]=max(f[[i-1][j-1][0],f[i-1][j-1][1])$$
边界条件:$f[1][0][0]=f[1][1][1]=0$

答案:$max(f[n][b][0],f[n][b][1])$

然后，现在两天是连着的，唯一的区别就是第一个小时可以睡着。

于是，令$f[1][1][1]=U_1$，然后再跑一遍DP，把$ans$和$f[n][b][1]$取最大值就行了。
为什么只与$f[n][b][1]$取最大值呢？
因为这里把$f[1][1][1]$赋值为了$U_1$，那么我们默认就是第一个小时进入了熟睡状态，所以上一天最后一个小时必须开始睡觉才行。

因为SPOJ的空间限制比较大，我就没用滚动数组了。

还有就是楼下说要赋初值负无穷，有点不理解，难道还会出现负数吗？

```cpp
#include <cstdio>
inline int max(int a, int b){
    return a > b ? a : b;
}
inline int min(int a, int b){
    return a < b ? a : b;
}
const int MAXN = 4000;
int f[MAXN][MAXN][3], w[MAXN];
int n, m, T;
int main(){
    scanf("%d", &T);
    while(T--){
      int ans = 0;
      scanf("%d%d", &n, &m);
      for(int i = 1; i <= n; ++i)
         scanf("%d", &w[i]);
      f[1][0][0] = f[1][1][1] = 0;
      for(int i = 2; i <= n; ++i){
         for(int j = 1; j <= min(i, m); ++j){
            f[i][j][0] = max(f[i - 1][j][0], f[i - 1][j][1]);
            if(j != 1) f[i][j][1] = max(f[i - 1][j - 1][0], f[i - 1][j - 1][1] + w[i]);    //第一个小时不加体力
         }
      }
      f[1][1][1] = w[1]; f[1][0][0] = 0;   //边界
      ans = max(f[n][m][1], f[n][m][0]);
      for(int i = 2; i <= n; ++i)
         for(int j = 1; j <= min(i, m); ++j){
            f[i][j][0] = max(f[i - 1][j][0], f[i - 1][j][1]);
            if(j != 1) f[i][j][1] = max(f[i - 1][j - 1][0], f[i - 1][j - 1][1] + w[i]);
         }
      ans = max(ans, f[n][m][1]);     
      printf("%d\n", ans);
    }
    return 0;
}

```

---

## 作者：_djc_ (赞：1)

## 题意理解

首先概括一下题意，去掉新颖有趣 ~~（qi qi guai guai)~~ 的描写大概就是说：给定一个长度为 $n$ 的环形序列，选出 $k$ 个元素，其中对于所有连续的元素，第一个不能算入贡献，求出这个序列的最大贡献。

## 解题思路

我们首先考虑一下如果不是环状的应该怎么做。可以定义这么一种状态，涉及到三个变量：到哪里了，选了多少，这个是否选了，可以用 $f_{i, j,0/1}$ 来表示。

首先时初始化 $f$ 数组为 $-\inf$ ，然后考虑递推初态：因为我们现在考虑的时断环成链，那么第一个小时无论睡不睡都是不可能有贡献的，所以 $f_{1, 1, 1} = 0, f_{1, 0, 0} = 0$ 。

列出状态转移方程：

第一种情况：第 $i$ 个位置不选，那么就从上个位置找选不选两种情况最大的；

$$
f_{i, j, 0} = \max(f_{i - 1, j, 0}, f_{i - 1, j, 1})
$$

第二种情况：选第 $i$ 个位置，它前面的那个位置有选或不选两种情况，如果前面的也选了，那现在的就不是睡觉的第一个小时，贡献可以加上 $a_i$ ，如果没选不加。

$$
f_{i, j, 1} = \max(f_{i - 1, j - 1, 0},f_{i - 1, j - 1, 1} + a_i)
$$

现在我们考虑一下环形怎么做.

可以考虑把一个点切断成一个链，枚举断点可能的情况分别 DP 一遍。

对于本题断点情况就是 $n$ 时刻是否睡：

我们第一遍 dp 时假设 $n$ 时刻没有睡，那么初始化： 

```f[1][1][1] = 0, f[1][0][0] = 0;```

如果 $n$ 时刻睡了，那么一时刻如果睡了的话就能计入贡献： 

```f[1][1][1] = a[1];```

最后取第一遍 dp 的 $f_{n, k, 0}$  和第二遍 dp 的 $f_{n, k, 1}$ 的最大值即可。

看一下数据范围，空间有点吃紧， $f$ 数组的第一维在决策 $i$ 时只会考虑 $i-1$ ，因此用上滚动数组，$30ms$ 过掉省空间也省时间（时间主要是每组数据都要初始化一下）。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define maxn 4000
using namespace std;
inline int read() {
	int x = 0, f = 1; char c = getchar();
	while (c < '0' || c > '9') { if (c == '-') f = -1; c = getchar(); }
	while (c >= '0' && c <= '9') { x = x * 10 + c - '0'; c = getchar(); }
	return x * f;
}
int f1[2][maxn][2], f2[2][maxn][2], a[maxn];//考虑用滚动数组
signed main() {
	int T = read();
	while (T--) {
		int n = read(), k = read();
		for (int i = 1; i <= n; i++) a[i] = read();
		memset(f1, 0xcf, sizeof(f1));//初始化
		memset(f2, 0xcf, sizeof(f2));
         //因为两次dp只有初态不一样，所以我让两个一起 dp
         //初态
		f1[1][1][1] = f1[1][0][0] = 0;
		f2[1][1][1] = a[1], f2[1][0][0] = 0;
		for (int i = 2; i <= n; i++) {
			for (int j = 0; j <= min(i, k); j++) {
				f1[i & 1][j][0] = max(f1[(i - 1) & 1][j][0], f1[(i - 1) & 1][j][1]);
				f2[i & 1][j][0] = max(f2[(i - 1) & 1][j][0], f2[(i - 1) & 1][j][1]);
				if (j > 0) {
					f1[i & 1][j][1] = max(f1[(i - 1) & 1][j - 1][0], 
										  f1[(i - 1) & 1][j - 1][1] + a[i]);
					f2[i & 1][j][1] = max(f2[(i - 1) & 1][j - 1][0], 
										  f2[(i - 1) & 1][j - 1][1] + a[i]);
				}
			}
		}
        //取两种情况最大值
		cout << max(f1[n & 1][k][0], f2[n & 1][k][1]) << endl;
	}
}
```
另：看题解区好多 dalao 的题解都是最后取 $\max$ 的时候加上了 $f1_{n, k, 1}$ 这种情况，窃以为不用，因为 $f1$ 数组的这种情况应该是让最后一个不选的，这样初态的 $f1_{1, 1, 1}$ 才是 $0$ 。

---

## 作者：Z1qqurat (赞：1)

### 思路

Part 1：如何确定这是一道线性 dp 的？

通过数据范围可以确定算法大概是 $n^2$ 的。

而这一段时间的睡觉是否有利用价值完全取决于上一段时间睡没睡，并且有非常明显的方向性。

然后就是一道线性 dp 了。

Part 2：状态的定义。

定义状态 $dp_{i,j}$ 表示前 $i$ 个小时内共睡了 $j$ 个小时的最大效益。

但是如果这样写着写着，会发现一个问题：

这一个小时得到的效益与上一个小时睡没睡直接相关！

于是我们考虑再加一个维度，表示这第 $i$ 个小时睡没睡，$0$ 表示睡了，$1$ 表示没睡。

Part 3：状态转移方程。

```cpp
dp[i][j][0]=max(dp[i-1][j-1][0]+a[i],dp[i-1][j-1][1]);
dp[i][j][1]=max(dp[i-1][j][1],dp[i-1][j][0]); 

```

但是可以发现，我们这么写的话如果 $j$ 为 $0$，第一个转移方程就会数组越界。因为有下标为 $-1$ 的情况。）

所以要改成：

```cpp
if(j>0)dp[i][j][0]=max(dp[i-1][j-1][0]+a[i],dp[i-1][j-1][1]);
dp[i][j][1]=max(dp[i-1][j][1],dp[i-1][j][0]); 

```

Part 4：边界条件。

这题有一个需要特殊处理的点：时间是循环的，第 $1$ 个小时是否有效益值和前一天第 $N$ 个小时睡没睡直接相关。

所以需要分两种情况。

于是我们直接 dp 两次，一次是前一天第 $N$ 个小时睡了，一次是前一天第 $N$ 个小时没睡，状态转移分别是：

```cpp
dp[1][1][0]=a[1],dp[1][0][1]=0;
dp[1][1][0]=dp[1][0][1]=0;

```
注意两次使用数组需要清空。

### 代码

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#define ll long long
#define ri register int
using namespace std;
const int MAXN=3840;
int t,n,b,a[MAXN],dp[MAXN][MAXN][2],ans;

int main() {
    ios::sync_with_stdio(false);
    cin>>t;
    while(t--){
        cin>>n>>b;
        for(ri i=1;i<=n;i++)cin>>a[i];
        memset(dp,0xcf,sizeof(dp));
        dp[1][1][0]=a[1],dp[1][0][1]=0;
        for(int i=2;i<=n;i++){
		    for(int j=0;j<=b;j++){
			    if(j>0)
				    dp[i][j][0]=max(dp[i-1][j-1][0]+a[i],dp[i-1][j-1][1]);
			    dp[i][j][1]=max(dp[i-1][j][1],dp[i-1][j][0]); 
		    }
	    }
        ans=dp[n][b][0];

        memset(dp,0xcf,sizeof(dp));
        dp[1][1][0]=dp[1][0][1]=0;
        for(int i=2;i<=n;i++){
		    for(int j=0;j<=b;j++){
			    if(j>0)
				    dp[i][j][0]=max(dp[i-1][j-1][0]+a[i],dp[i-1][j-1][1]);
			    dp[i][j][1]=max(dp[i-1][j][1],dp[i-1][j][0]); 
		    }
	    }
        ans=max(dp[n][b][1],ans);
        cout<<ans<<"\n";
    }
    return 0;
}

```

---

## 作者：YanLei (赞：1)

[Naptime | SP283](https://www.luogu.com.cn/problem/SP283)

详情见CSDN博客：[【训练题15：线性DP(如何时间复杂度一降再降)】Naptime | SP283](https://blog.csdn.net/weixin_45775438/article/details/109858577)
## 难度
$提高+/省选-$
- 有趣的题目！
- 主要是考察如何转移以及如何降低时间复杂度。

独立写出
## 题意

- 在某个星球上，一天由 $N$ 小时构成。
- 在第 $i$ 个小时睡觉能恢复 $U_i$ 点体力。
- 在这座星球上住着一头牛，它每天要休息 $B$ 个小时，它休息的这 $B$ 个小时可以不连续，可以分成若干段，但是**在每一段的第一个小时不能恢复体力**，从第二个小时开始才可以恢复体力。
- 为了身体健康，这头牛希望遵循生物钟，每天采用相同的睡觉计划。
- 另外，因为时间是连续的，每天的第 $N$ 个小时与下一天的第一个小时是相连的，这头牛只需要在 $N$ 个小时内休息 $B$ 个小时就够了。
- 请你给这头牛安排一个任务计划，使得它每天恢复的体力最多。

## 数据范围
$2\le B < N \le 3830$

$0 \le U_i \le 200000$
## Sample
五天，睡三个小时
$U=2\ 0\ 3\ 1\ 4$
则它睡 $U_4、U_5、U_6$这三个时间段，获得收益为 $1*0+4+2$

## 思路
1.【暴力枚举法（没学过DP）】
- 暴力枚举每个时间段选或者不选，是最最简单的思路。
- 时间复杂度 $\color{cyan}O(2^NN)$
- 继续努力想想嘛。

2.【区间$DP$ / 三维 $DP$ 写法】
- **设 $dp[i][j][k]$表示区间 $i\sim j$选择睡觉 $k$ 个小时的获得最大体力值。**
- 考虑转移还要枚举中间断点，时间复杂度：$\color{cyan}O(N^4)$
- 当状态维度过大，我们会试着降低一个维度看看效果。

3.【线性$DP$ / 二维 $DP$ 单状态，多转移法】
- **设 $dp[i][j]$表示区间 $1\sim i$选择睡觉 $j$ 个小时的获得最大体力值。**
- 转移方程我们可以轻松写出：
- $dp[i+m][j+m]=\max\{dp[i][j]+get[i+1][j]\}$
- 其中 $get[a][b]$ 表示这一段区间的体力值的和，可以使用**前缀和**来优化到 $O(1)$ 获得。
- 我们可以发现，状态数有 $O(N^2)$ ， 每一个状态的转移种数又有 $O(N)$
- 所以时间复杂度为 $\color{cyan}O(N^3)$ （不加前缀和优化的话还要乘以一个 $N$）
- 尽管状态数少了，但是转移的方式还是很多，需要考虑如何转移才可以 $O(1)$ 转移。


4.【线性$DP$ / 二维 $DP$ 多状态，单转移法】
- 设 $dp[i][j][0]$ 表示区间 $1\sim i$选择睡觉 $j$ 个小时，并且当前不睡觉时获得最大体力值
- 设 $dp[i][j][1]$ 表示区间 $1\sim i$选择睡觉 $j$ 个小时，并且刚刚睡觉一个小时时获得最大体力值
- 设 $dp[i][j][2]$ 表示区间 $1\sim i$选择睡觉 $j$ 个小时，并且现在已经睡觉大于一个小时时获得最大体力值

这样，**状态转移方程便可以很好地推出了**。
- $dp[i][j][0]=\max\{dp[i-1][j][0],dp[i-1][j][1],dp[i-1][j][2]\}$
- $dp[i][j][1]=dp[i-1][j-1][0]$
- $dp[i][j][2]=\max\{dp[i-1][j-1][1],dp[i-1][j-1][2]\}+U_i$
- 式子一：当前不睡觉等于前一状态已经睡了 $j$ 小时的最大值。
- 式子二：当前睡第一轮等于前一状态少睡一个小时，并且还没睡觉的值。
- 式子三：当前睡多轮等于前一状态少睡一小时，并且在睡觉的最大值。
- 时间复杂度直接变成 $\color{cyan}O(N^2)$，感觉已经成功了！

**真的成功了吗？**

- 因为一天的时间不一定要从早上开始的一天，也可以是从中午开始到第二天中午的一天。比如样例，答案就是跨过一天的。
- **如果我们枚举从哪一个时间开始作为一天的开始的话，时间复杂度又要再乘上一个 $N$ ，似乎又成了一个瓶颈！**

### 想法一：把一天扩展成两天
- 如果一天是 $U=2\ 0\ 3\ 1\ 4$，我们不试一下把两天拼接起来
- 使之变成 $U=2\ 0\ 3\ 1\ 4\ 2\ 0\ 3\ 1\ 4$
- 然后再去计算最后的答案呢？

结果：
- **这样会导致答案错误**。比如他可能会同时在两天的上午睡觉，但这不符合题目要求。

### 想法二：越单纯越好
- 考虑到：因为第一个小时的睡觉是不回复体力值的。如果要我们贪心的话，肯定是第一个小时会选择尽可能小的值。
- 那我们为何不选出一个小时，这个小时是我们**一定不会选择在这个小时获得休息值的呢？** 然后选择把这个小时放在这天的第一个小时，**当做新的一天的第一个小时。**这样我们选择的结果**就不会跨过新的一天的结尾了**。

这样子就成功了！
## 核心代码
时间复杂度 $O(N^2)$

$Times:70(ms)$
```c
/*
 _            __   __          _          _
| |           \ \ / /         | |        (_)
| |__  _   _   \ V /__ _ _ __ | |     ___ _
| '_ \| | | |   \ // _` | '_ \| |    / _ \ |
| |_) | |_| |   | | (_| | | | | |___|  __/ |
|_.__/ \__, |   \_/\__,_|_| |_\_____/\___|_|
        __/ |
       |___/
*/
const int MAX = 4e3+50;
const int INF = 0x3f3f3f3f;

int aa[MAX];
int bb[MAX];
int dp[MAX][MAX][4];
int main()
{
    int T;scanf("%d",&T);
    while(T--){
        int N,B;
        scanf("%d%d",&N,&B);
        int mn = INF;
        int id = 0;
        for(int i = 1;i <= N;++i){
            scanf("%d",&bb[i]);
            if(bb[i] < mn){
                mn = bb[i];
                id = i;
            }
        }
        for(int i = 1;i <= N;++i){
            aa[i] = bb[(id + i - 1 - 1) % N + 1];
        }
        for(int i = 0;i <= N;++i)
        for(int j = 0;j <= B;++j)
        for(int k = 0;k <= 2;++k)
            dp[i][j][k] = -LINF;

        for(int i = 0;i <= N;++i){
            dp[i][0][0] = 0LL;
        }
        for(int i = 1;i <= N;++i){
            for(int j = 1;j <= min(i,B);++j){
                dp[i][j][0] = max(max(dp[i-1][j][0],dp[i-1][j][1]),dp[i-1][j][2]);
                dp[i][j][1] = dp[i-1][j-1][0];
                dp[i][j][2] = max(dp[i-1][j-1][1],dp[i-1][j-1][2]) + aa[i];
            }
        }
        int ans = 0;
        for(int i = B;i <= N;++i){
            for(int j = 0;j < 3;++j){
                ans = max(ans,dp[i][B][j]);
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}
```

---

## 作者：月雩·薇嫭 (赞：1)

------------


**星影落九天，鱼雁舞千弦。但为君沉吟，落日天涯圆。**

------------
[[题目传送门]](https://www.luogu.com.cn/problem/SP283)

先考虑若不是环的情况

设状态为$dp[i][j][0/1]$：

$dp[i][j][0]$表示前$i$段睡了$j$段且**第**$i$**段没睡**前$i$段的最大效用值

$dp[i][j][1]$表示前$i$段睡了$j$段且**第**$i$**段睡了**前$i$段的最大效用值

那么**状态转移方程**即为：
$$
	dp_{i,j,0}=max(dp_{i-1,j,0},dp_{i-1,j,1})$$
$$
	dp_{i,j,1}=max(dp_{i-1,j-1,0}+0,dp_{i-1,j-1,1}+a_{i})$$
    
$dp_{i,j,0/1}$的初值为-INF

那么**对于环**，只需要强制连接第$n$段与第$1$段

即：将$dp_{1,0,0}$的初值赋为$a_{1}$即可

## Code

```cpp
#include<bits/stdc++.h>
#define FQ(i,a,b) for(register int i=a;i<=b;i++)
#define prf printf
#define scf scanf
#define ll long long
using namespace std;
int INF;
const int N=3835;
int n,m,ans,a[N],F[N][N][2];
ll read()
{
	ll x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int main()
{
	int T=read();
	while(T--)
	{
		INF=-128/2;
		n=read(),m=read();memset(F,INF,sizeof(F));
		for(int i=1;i<=n;i++)a[i]=read();
		for(int i=1;i<=n;i++)F[i][0][0]=0;F[1][1][1]=0;
		for(int i=2;i<=n;i++)
			for(int j=1;j<=m;j++)
			{		
				F[i][j][0]=max(F[i-1][j][0],F[i-1][j][1]);		
				F[i][j][1]=max(F[i-1][j-1][0]+0,F[i-1][j-1][1]+a[i]);		
			}	
		ans=max(F[n][m][1],F[n][m][0]);	
		memset(F,INF,sizeof(F));
		for(int i=1;i<=n;i++)F[i][0][0]=0;F[1][1][1]=a[1];
		for(int i=2;i<=n;i++)
			for(int j=1;j<=m;j++)
			{	
				F[i][j][0]=max(F[i-1][j][0],F[i-1][j][1]);	
				F[i][j][1]=max(F[i-1][j-1][0]+0/*不计i的效用值*/,F[i-1][j-1][1]+a[i]);	
			}
		ans=max(ans,F[n][m][1]);
		printf("%d\n",ans);
	}
	return 0;	
} 
```


---

## 作者：1234567890sjx (赞：0)

首先假设时间不会循环。

那么有 $f_{i,j,0/1}$ 表示当前选取了前 $i$ 个时间，$j$ 个时间睡觉觉，当前时间正在睡觉觉 / 不睡觉觉。

显然有：

$f_{i,j,0}=\max(f_{i-1,j,0},f_{i-1,j,1})$。

$f_{i,j,1}=\max(f_{i-1,j-1,0},f_{i-1,j-1,1}+u_i)$。

初始条件 $f_{1,0,0}=f_{1,1,1}=0$。$f_\texttt{Oth}=-\inf$。

但是这个题目时间是会循环的，也就是有环。

然后在题解区看到了一个[非常喵的解法](https://www.luogu.com.cn/blog/MeowMeowMeow/solution-p6064)。

分类讨论第 $n$ 个时间睡觉觉 / 不睡觉觉。

如果第 $n$ 个时间不睡觉觉那么就是上述的时间不循环的情况。

否则，第 $1$ 个时间就可以获得效用值。

于是初始条件：$f_{1,1,1}=u_1$，其余的不变。

直接做即可。时间复杂度 $O(nm)$。


---

## 作者：JLGxy (赞：0)

由题目不难看出这是一道 dp 题。这题的难点在于将环转换为链，如果我们暴力枚举每一个断点，时间复杂度会变为 $\textrm O(n^3)$，无法通过本题，因此可以只分为两类，即跨天和不跨天的情况。

先考虑不跨天的情况，令 $f_{i,j,k}$ 表示当前是第 $i$ 小时，已经休息了 $j$ 小时，$k$ 表示这个小时是否休息，显然有

$$f_{i,j,0}=\max\{f_{i-1,j,0},f_{i-1,j,1}\}$$
$$f_{i,j,1}=\max\{f_{i-1,j-1,0},f_{i-1,j-1,1}+u_i\}$$

这表示如果某个小时不休息，那么这一小时的贡献为 $0$，如果这个小时休息了，但上个小时没有休息，那么贡献也是 $0$，仅在这个小时和上个小时都休息时，贡献才为 $u_i$。$f$ 的初始值为

$$f_{0,0,0}=0,~f_{i,j,k}=-\infty$$

但是如果休息跨越两天，则要特殊考虑。可以令 $g_{i,j,k}$ 表示昨天第 $b$ 个小时和今天第 $1$ 小时都休息的情况，显然 $g$ 的转移与 $f$ 相同，$g$ 初始值设为

$$g_{1,1,1}=u_1,~g_{i,j,k}=-\infty$$

这是因为，前一天的最后一个小时休息了，那么这一天第一个小时休息一定有贡献，贡献为 $u_1$

答案为 $\max\{f_{n,b,0},f_{n,b,1},g_{n,b,1}\}$，因为 $g$ 表示昨天第 $b$ 个小时和今天第 $1$ 小时都休息，所以 $g_{n,b,0}$ 是无效情况。

因此做两次 dp 既可以涵盖所有情况。考虑到这题空间限制比较小，可以用滚动数组进行优化。

---

## 作者：红黑树 (赞：0)

[可能更好的阅读体验](https://rbtr.ee/luogu-6064-sp-283)

## [题意](https://www.luogu.com.cn/problem/SP283)

给定一个长度为 $n$ 的环，环上第 $i$ 个点有权值 $U_i$。选择其中 $k$ 个点，对于一段连续的选择的点，除第一个点外其余计入答案。求最大的答案。

$1 \leq b < n \leq 3830$

## 题解
我们在 $\left(n, 1\right)$ 间断开环，变成一条链，$f\left(i, j, 0/1\right)$ 表示现在在第 $i$ 个点，已经选择了 $j$ 个点，第 $i$ 个点是否被选择。

转移方程：
$$f\left(i, j, 0\right) = \max\{f\left(i - 1, j, 0\right), f\left(i - 1, j, 1\right)\}$$

$$f\left(i, j, 1\right) = \max\{f\left(i - 1, j - 1, 1\right) + U_i, f\left(i - 1, j - 1, 0\right)\}$$

强制选 $n$ 时，初始值 $f\left(1, 0, 0\right) = 0, f\left(1, 1, 1\right) = U_1$，答案是 $f\left(n, b, 1\right)$

强制不选 $n$ 时，初始值 $f\left(1, 0, 0\right) = f\left(1, 1, 1\right) = 0$，答案是 $f\left(n, b, 0\right)$

时间复杂度 $\mathcal O(n \cdot b)$

## 代码
```cpp
// Please submit with C++14!
#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>
#define ra _Read()

using tp = int;
tp _Read();
using namespace std;
constexpr bool __MTCS__ = 0;
constexpr tp Hat_N = 3833;

namespace __SOL__ {
tp n, b;
array<tp, Hat_N> u;

pair<tp, tp> dp(tp f111) {
  array<array<array<tp, 2>, Hat_N>, Hat_N> f;
  for (auto&& i : f) {
    for (auto&& [j, k] : i) {
      j = k = -(-1u >> 2);
    }
  }
  f[1][0][0] = 0;
  f[1][1][1] = f111;
  for (tp i = 2; i <= n; ++i) {
    f[i][0][0] = f[i - 1][0][0];
    for (tp j = 1; j <= b; ++j) {
      f[i][j][0] = max(f[i - 1][j][0], f[i - 1][j][1]);
      f[i][j][1] = max(f[i - 1][j - 1][1] + u[i], f[i - 1][j - 1][0]);
    }
  }
  return make_pair(f[n][b][0], f[n][b][1]);
}

signed main() {
  pair<tp, tp> temp;
  n = ra;
  b = ra;
  for (tp i = 1; i <= n; ++i) {
    u[i] = ra;
  }
  temp = dp(0);
  printf("%d\n", max({temp.first, temp.second, dp(u[1]).second}));
  return 0;
}
}  // namespace __SOL__

signed main() {
  tp __MTCS__ = ::__MTCS__ ? ra : 1;
  while (__MTCS__--) {
    __SOL__::main();
  }
  return 0;
}

tp _Read() {
  bool __neg(0);
  char __c(getchar());
  tp __val(0);
  for (; __c < 48 || __c > 57; __c = getchar()) {
    __neg = __c == 45;
  }
  for (; __c > 47 && __c < 58; __c = getchar()) {
    __val = __val * 10 + (__c & 15);
  }
  return __neg ? ~__val + 1 : __val;
}
```

---

## 作者：SunsetSamsara (赞：0)

## 前置知识

dp

## 分析

~~一开始我以为在一段可以不连续调了我 15 分钟~~

首先，先找到 dp 状态 $f_{i, j, k}$，$i$ 表示当前在第几个小时，$j$ 表示已经休息了几个小时，$k$ 表示第 $i$ 个小时是不是在休息。

那么怎么转移呢？

1. $f_{i, j, 0}$ 可以是上一小时休息或者不休息，即 $\max\{f_{i - 1, j, 0}, f_{i - 1, j, 1}\}$

2. $f_{i, j, 1}$ 也可以是上一小时休息或不休息，因为每一段第一个小时不计入答案，所以第一个值是 $f_{i - 1, j - 1, 0}$，dp 值即 $\max\{f_{i - 1, j - 1, 0}, f_{i - 1, j - 1, 1} + U_i\}$

初始值就是 $f_{1, 1, 1} = 0,f_{1, 0, 0} = 0$

这里答案取的就是 $f_{N, B, 0}$ 和 $f_{N, B, 1}$ 的最大值。

**但是**，这样少考虑了一种情况，即第 $N$ 个小时和第一个小时连在一起的情况。所以，需要换下初始值再 dp 一遍。

新的初始值显然就是 $f_{1, 1, 1} = U_1$

这里答案取的就是 $f_{N, B, 1}$

最后，取两次答案的最大值即可

## 代码

```cpp
#include <bits/stdc++.h>
#define lld long long
using namespace std;
int T;
int n, m;
int a[4010];
lld ans;
lld f[4010][4010][2];
/*
f[i][j][0] = max(f[i - 1][j][0], f[i - 1][j][1]);
f[i][j][1] = max(f[i - 1][j - 1][0], f[i - 1][j - 1][1] + a[i]);
*/
void solve1() {
	f[1][0][0] = f[1][1][1] = 0;
	for (int i = 2; i <= n; ++ i)
		for (int j = 0; j <= m; ++ j) {
			f[i][j][0] = max(f[i - 1][j][0], f[i - 1][j][1]);
			f[i][j][1] = j ? max(f[i - 1][j - 1][0], f[i - 1][j - 1][1] + a[i]) : f[i][j][1];
		}
	ans = max(f[n][m][0], f[n][m][1]);
}
void solve2() {
	f[1][1][1] = a[1];
	for (int i = 2; i <= n; ++ i)
		for (int j = 0; j <= m; ++ j) {
			f[i][j][0] = max(f[i - 1][j][0], f[i - 1][j][1]);
			f[i][j][1] = j ? max(f[i - 1][j - 1][0], f[i - 1][j - 1][1] + a[i]) : f[i][j][1];
		}
	ans = max(ans, f[n][m][1]);
}
void solve() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++ i)
		scanf("%d", a + i);
	solve1();
	solve2();
	printf("%lld\n", ans);
}
int main() {
	scanf("%d", &T);
	while (T --) solve();
}
```

---

## 作者：gyfydkf (赞：0)

~~为了写这道题，注册了SPOJ好久....~~

[双倍经验](https://www.luogu.com.cn/problem/P6064)

[本题题目传送门](https://www.luogu.com.cn/problem/SP283)

## 题目大意：

从一天的 $n$ 段时间中选取 $b$ 段，每个时间段都有其效用值，第 $n$ 个小时与第 1 个小时相连，问能得到的最大效用值。

## 方法：

读题，这是一个环形结构，一般环形结构处理方式是通过枚举断点使环变成线性结构再来计算，最后通过每一次的结果求出答案。

但此题环形结构对于答案的影响仅有是否选取阶段 $n - 1$，所以可以从这里入手，进行两次计算：选取阶段 $n - 1$ 与不选取此阶段。

由于每个阶段是否选取得到的最大值由上一阶段影响，我们使用 DP 求解。

#### 当不选取阶段 $n - 1$ 时

我们用 $f_{i,j,1}$ 表示前 $i$ 个阶段一共选取了 $j$ 个阶段，并且第 $i$ 个阶段被选取。而由于“**每一段睡眠的第一个时间阶段都是“入睡”阶段，而旦不记入效用值**。”所以只有当前一个阶段被选取，才能加上当前阶段的效应值；若前一个阶段没有被选取，则不能加上当前阶段的效应值；从这两种情况中选出最大值：

$f_{i,j,1}=\max(f_{i-1,j-1,0},f_{i-1,j-1,1}+u_i)$

用 $f_{i,j,1}$ 表示前 $i$ 个阶段一共选取了 $j$ 个阶段，并且第 $i$ 个阶段没有被选取。那就不用顾忌什么，直接从上一阶段是否选取这两种情况中得到最大值即可：

$f_{i,j,0}=\max(f_{i-1,j,0},f_{i-1,j,1})$

由于不选取阶段 $n - 1$,故第一个小时不管有没有休息一定是在入睡状态，不会得到效应值。所以：

初始状态：$f_{1,0,0}=f_{1,1,1}=0$,其余皆设为负无穷。

目标是：$\max(f_{n,b,0},f_{n,b,1})$

#### 当选取阶段 $n - 1$ 时

此时我们应强制选取阶段 $n - 1$ 所以在 $n$ 阶段处于入睡状态，1阶段就睡熟了，所以初始状态和目标状态应修改为：

$f_{1,1,1}=u_1$,其余设为负无穷。

目标是 $f_{n,b,1}$。

## 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,b;
int dp[3905][3905][2],u[3904];//之前存了两个dp数组，会爆空间，一个数组需要反复初始化 
int main(){
	cin>>t;
	while(t--){
		int ans=0;
		cin>>n>>b;
		for(int i=1;i<=n;i++){
			cin>>u[i];
		}//读入 
		memset(dp,128,sizeof(dp)); 
		dp[1][0][0]=0;
		dp[1][1][1]=0;//第一次初始化，不选n-1的情况 
		for(int i=2;i<=n;i++){
			dp[i][0][0]=dp[i-1][0][0];
			for(int j=1;j<=min(i,b);j++){
				dp[i][j][0]=max(dp[i-1][j][1],dp[i-1][j][0]);
			    dp[i][j][1]=max(dp[i-1][j-1][0],dp[i-1][j-1][1]+u[i]);
			}
		}
		ans=max(dp[n][b][0],dp[n][b][1]);
		memset(dp,128,sizeof(dp));
		dp[1][1][1]=u[1];
		dp[1][0][0]=0;//选n-1的情况 
		for(int i=2;i<=n;i++){
			dp[i][0][0]=dp[i-1][0][0];
			for(int j=1;j<=min(i,b);j++){
				dp[i][j][0]=max(dp[i-1][j][1],dp[i-1][j][0]);
				dp[i][j][1]=max(dp[i-1][j-1][0],dp[i-1][j-1][1]+u[i]);
			}
		}
		ans=max(ans,dp[n][b][1]); 
		printf("%d\n",ans);
	}
	return 0;
} 
```



---

## 作者：Azuree (赞：0)

## 分类讨论

例题：[SP283 NAPTIME - Naptime](https://www.luogu.org/problem/SP283)

对于这类问题，我们可以分类讨论首尾的状态，然后分别进行一次DP求得所有可能中的最优解。

#### 状态设计 

$f[i][j][0/1]$表示一天的前$i$小时中睡$j$小时且最后一个小时（第$i$小时）睡/不睡能获得的最大体力

#### 状态转移

$$f[i][j][0]=max(f[i-1][j][0],f[i-1][j][1])$$


$$f[i][j][1]=max(f[i-1][j-1][0],f[i-1][j-1][1]+v[i])$$

其中，再第二个转移中，如果想从$f[i-1][j-1][1]$转移到$f[i][j][1]$，那么必须满足$j>1$，保证第$1$到$i-1$小时中奶牛睡过觉这个状态是合法的。

#### 分类讨论

我们先强制奶牛不从一天的最后一小时睡到第二天的第一个小时并进行一次dp。

更新答案：$ans=max(f[n][b][0],f[n][b][1])$

然后我们强制奶牛从一天的最后一小时睡到第二天的第一个小时并进行一次dp。

初始化：

$f[1][0][0] = -INF$ 

$f[1][1][1] = a[1]$

因为强制从一天的最后一小时睡到第二天的第一个小时，所以把$f[1][1][1]$初始化为$a[1]$，活动第一个小时睡觉时得到的体力，而且不从$f[1][0][0]$转移，所以把它赋成负无限，再转移时，取$max$会把该状态滤掉（也许会把不合法状态赋成$-INF$）。

更新答案：$ans=max(ans,f[n][b][1])$（因为强制从一天的最后一小时睡到第二天的第一个小时，所以此时最后一小时不睡觉的状态是不合法的，不用它去更新答案。）

#### 代码

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<algorithm>
#define ll long long
#define INF 0x7fffffff
#define re register

using namespace std;

int read()
{
    register int x = 0,f = 1;register char ch;
    ch = getchar();
    while(ch > '9' || ch < '0'){if(ch == '-') f = -f;ch = getchar();}
    while(ch <= '9' && ch >= '0'){x = x * 10 + ch - 48;ch = getchar();}
    return x * f;
}

int T,n,b,ans,a[100005],f[4005][4005][2];
 
int main()
{
	T = read();
	while(T--)
	{
		memset(f,0,sizeof(f));
		n = read(); b = read();
		for(re int i = 1; i <= n; i++) a[i] = read();
		for(re int i = 1; i <= n; i++)
			for(re int j = 1; j <= b; j++)
			{
				f[i][j][0] = max(f[i - 1][j][0],f[i - 1][j][1]);
				f[i][j][1] = max(f[i - 1][j - 1][0],(f[i - 1][j - 1][1] + a[i]) * (j > 1));
			}
		ans = max(f[n][b][0],f[n][b][1]);
		memset(f,0,sizeof(f));
		f[1][0][0] = -INF; f[1][1][1] = a[1];
		for(re int i = 2; i <= n; i++)
			for(re int j = 1; j <= b; j++)
			{
				f[i][j][0] = max(f[i - 1][j][0],f[i - 1][j][1]);
				f[i][j][1] = max(f[i - 1][j - 1][0],(f[i - 1][j - 1][1] + a[i]) * (j > 1));
			}
		ans = max(ans,f[n][b][1]);
		printf("%d\n",ans);
	}
    return 0;
}

```



---

## 作者：Object_ (赞：0)

**状态设计：**

- f[小时数（用i&1滚动）][睡觉时长][当前是否在睡觉].

**易错点：**

- 可以使用滚动数组（i&1）.
- 在更新正在睡觉的状态（f[][][1]）前需要保证当前总睡觉时间大于1（起码入睡过）.
- 在更新f[i&1][j][1]时，可以发现如果上个小时没有睡觉现在就不恢复体力，因此只有在从f[(i-1)&1][j-1][1]尝试进行转移时才需要增加u[i]（当前小时的恢复体力量）.

------------
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
const int MAXN=8e3;
int f[2][MAXN][2],u[MAXN];
int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		int n,b;
    	scanf("%d%d",&n,&b);
    	for(int i=1;i<=n;i++){
    	    scanf("%d",&u[i]);
    	}
    	memset(f,0xcf,sizeof(f));
    	f[1&1][0][0]=f[1&1][1][1]=0;
    	for(int i=2;i<=n;i++){
    	    for(int j=0;j<=b;j++){
    	        f[i&1][j][0]=max(f[(i-1)&1][j][0],f[(i-1)&1][j][1]);
    	        if(j>=1)f[i&1][j][1]=max(f[(i-1)&1][j-1][0],f[(i-1)&1][j-1][1]+u[i]);
    	    }
    	}
    	int ans=max(f[n&1][b][0],f[n&1][b][1]);
    	memset(f,0xcf,sizeof(f));
    	f[1&1][1][1]=u[1];
    	for(int i=2;i<=n;i++){
    	    for(int j=0;j<=b;j++){
    	        f[i&1][j][0]=max(f[(i-1)&1][j][0],f[(i-1)&1][j][1]);
    	        if(j>=1)f[i&1][j][1]=max(f[(i-1)&1][j-1][0],f[(i-1)&1][j-1][1]+u[i]);
    	    }
    	}
    	ans=max(ans,f[n&1][b][1]);
    	printf("%d\n",ans);
	}
    return 0;
}
```

---

## 作者：nofind (赞：0)

题意：

一头牛要睡觉，需要一个小时才能睡着，第i小时能恢复体力val[i],它可以从今天睡到明天，问每一轮N小时最多能恢复多少体力。

简单版：

现在给你一个环找刚好b个数，求他们的和，每一段数的第一个数不计入贡献要你使得贡献最大。

解析：

先考虑不是环的时候，我们很容易写出DP方程：f[i][j][0/1]->表示第i小时睡了j小时，现在0->醒着，1->睡着，时的最大贡献。

f[i][j][0]=max(f[i-1][j][0],f[i-1][j][1]);
f[i][j][1]=max(f[i-1][j-1][0],f[i-1][j-1][1]+val[i]);

之后的神奇做法是强制奶牛在第N和第1小时睡觉，方法是f[1][1][1]=0,其它全都负无穷，之后再跑一次DP,将两次的答案比较。

正确性：在第N和第1小时睡不睡觉的两次DP覆盖了整个状态空间。

code：

```
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int maxn=3850;
int n,b,ans;
int val[maxn];
int f[maxn][2];
int main()
{
	scanf("%d%d",&n,&b);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&val[i]);
	}
	memset(f,128,sizeof(f));
	f[0][0]=f[1][1]=0;
	for(int i=2;i<=n;i++)
	{
		for(int j=b;j;j--)
		{
			f[j][0]=max(f[j][0],f[j][1]);
			f[j][1]=max(f[j-1][0],f[j-1][1]+val[i]); 
		}
	}
	ans=max(f[b][0],f[b][1]);
	memset(f,128,sizeof(f));
	f[1][1]=val[1];
	for(int i=2;i<=n;i++)
	{
		for(int j=b;j;j--)
		{
			f[j][0]=max(f[j][0],f[j][1]);
			f[j][1]=max(f[j-1][0],f[j-1][1]+val[i]); 
		}
	}
	ans=max(ans,f[b][1]);	
	printf("%d",ans);
	return 0;
} 
```


---

## 作者：lrqlrq250 (赞：0)

双倍经验：[P6064](https://www.luogu.com.cn/problem/P6064)（这道题没有多测）

## 题意简述

在一个长度为 $n$ 的环上选出若干段使其总长度为 $m$，对于每一段 $i - j$，其贡献为 $sum[j] - sum[i]$，即除了 $u[i]$ 以外的数值和。求贡献的最大值。

## 解题思路

我们可以先尝试不考虑环，那么显然可以设计 $dp[i][j][0/1]$ 表示前 $i$ 个小时中有 $j$ 个小时在睡觉，且第 $i$ 个小时要不要睡觉。

显然如果第 $i$ 个小时不睡觉，则

$$dp[i][j][0] = \max(dp[i - 1][j][0], dp[i - 1][j][1])$$

如果第 $i$ 个小时睡觉了，那么我们考虑前一个小时有没有睡觉：

$$dp[i][j][1] = \max(dp[i - 1][j - 1][0], dp[i - 1][j - 1][1] + u[i])$$

最终的结果就是 $\max(dp[n][m][0], dp[n][m][1])$。

现在我们再来考虑环的问题。通过分析可以发现，有环和没有环，差别只和 $u[1]$ 有关——在没有环的情况下，$u[1]$ 是不可能被加入到贡献中的。

因此我们只需要在正常地进行一次上面那种 DP 后，再进行一次 DP，并强制要求第 $n$ 个时间段用来休息，第 $1$ 个时间段也来休息，使得 $u[1]$ 被加入到贡献中。这时候答案一定为 $dp[n][m][1]$，再与第一次 DP 的结果取较大值即可。

但是如果我们要设计这样一个数组，就相当于一个大小为 $50000000$ 的数组，对于本题 $62.50MB$ 和 P6064 中 $125MB$ 的空间限制都无法通过。但是可以注意到 $dp[i]$ 只和 $dp[i - 1]$ 有关，因此可以滚动数组优化。

总体时间复杂度为 $O(TNB)$。

## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, a[5001], dp[2][5001][2];


int main(){
	int t;
	scanf("%d", &t);
	while (t--){
		scanf("%d%d", &n, &m);
		int minn = 2e9, sum = 0;
		for (int i=1; i<=n; i++) scanf("%d", &a[i]), minn = min(minn, a[i]), sum += a[i];
		if (n == m){printf("%d\n", sum - minn); continue;}
		memset(dp, -0x3f, sizeof(dp));
		dp[1][0][0] = dp[1][1][1] = 0;
		for (int i=2; i<=n; i++) for (int j=0; j<=min(i, m); j++){
			dp[i & 1][j][0] = max(dp[(i - 1) & 1][j][0], dp[(i - 1) & 1][j][1]);
			if (j) dp[i & 1][j][1] = max(dp[(i - 1) & 1][j - 1][0], dp[(i - 1) & 1][j - 1][1] + a[i]);
		}
		int ans = max(dp[n & 1][m][0], dp[n & 1][m][1]);
		memset(dp, -0x3f, sizeof(dp));
		dp[1][1][1] = a[1];
		for (int i=2; i<=n; i++) for (int j=0; j<=min(i, m); j++){
			dp[i & 1][j][0] = max(dp[(i - 1) & 1][j][0], dp[(i - 1) & 1][j][1]);
			if (j) dp[i & 1][j][1] = max(dp[(i - 1) & 1][j - 1][0], dp[(i - 1) & 1][j - 1][1] + a[i]);
		}
		printf("%d\n", max(ans, dp[n & 1][m][1]));
	}
	return 0;
} 

```
PS：我在你谷上最近提交 SPOJ 和 UVA 的题目都会显示 UKE，这份代码在 SPOJ 上提交通过。

---

## 作者：Aiopr_2378 (赞：0)

就是一个在环上的dp。

我们可以考虑把这个环拆一条边，变成链，在链上进行线性dp，这样简单得多。

方便起见，我们把从 $1$ 到 $n$ 的这条链删除，使这张图变成一条链。

我们设 $F[i,j,1]$ 表示前 $i$ 个小时休息了 $j$ 个小时，并且第 $i$ 个小时正在休息，累计恢复体力的最大值。$F[i,j,0]$ 表示前 $i$ 个小时休息了 $j$ 个小时，并且第 $i$ 个小时没有休息，累计恢复体力的最大值。

此时我们需要分类讨论：

- 如果第一个时间段不睡觉或者刚开始睡觉（处于“入睡”状态），也就是常规的dp，不难推出以下结论：

	边界：$F[1,0,0]=0,F[1,1,1]=0$，其余为 `-inf`

   目标：$\max(F[n,b,0],F[n,b,1])$
   
	方程：

$$F[i,j,0]=\max(F[i-1,j,0],F[i-1,j,1])$$

$$F[i,j,1]=\max(F[i-1,j-1,0],F[i-1,j-1,1]+U_i)$$

- 如果第一个时间段在睡觉且不处于“入睡”状态（即睡觉时段和被断开的那个点连在了一起），可以推出以下结论：

	边界：$F[1,1,1]=U_1$ ，其余为 `-inf`

   目标：$F[n,b,1]$
   
	方程：

$$F[i,j,0]=\max(F[i-1,j,0],F[i-1,j,1])$$

$$F[i,j,1]=\max(F[i-1,j-1,0],F[i-1,j-1,1]+U_i)$$

两个结果中最优者就是答案。

讲到这里就可以做 [P6064 [USACO05JAN]Naptime G](https://www.luogu.com.cn/problem/P6064) 这道题了，题意完全相同。

但是本题还需要进行一些空间优化。

由于这个递归只与 $i-1$ 这一行有关，我们不妨进行滚动数组，将上面公式中 $i$ 改成 $i\&1$ 即可。

参考代码：

```cpp
#include<iostream>
#include<cstring>
using namespace std;
#define MAXN 3830
int t,n,b,a[MAXN],f[2][MAXN][2],ans;
int main(){
    cin>>t;
    while(t--){
        cin>>n>>b;
        for(int i=1;i<=n;i++) cin>>a[i];
        memset(f,-0x3f,sizeof(f));
        f[1&1][0][0]=f[1&1][1][1]=0;
        for(int i=2;i<=n;i++){
            for(int j=0;j<=b;j++){
                f[i&1][j][0]=max(f[(i-1)&1][j][0],f[(i-1)&1][j][1]);
                if(j>=1) f[i&1][j][1]=max(f[(i-1)&1][j-1][0],f[(i-1)&1][j-1][1]+a[i]);
            }
        }
        ans=max(f[n&1][b][1],f[n&1][b][0]);
        memset(f,-0x3f,sizeof(f));
        f[1][1][1]=a[1];
        for(int i=2;i<=n;i++){
            for(int j=0;j<=b;j++){
                f[i&1][j][0]=max(f[(i-1)&1][j][0],f[(i-1)&1][j][1]);
                if(j>=1) f[i&1][j][1]=max(f[(i-1)&1][j-1][0],f[(i-1)&1][j-1][1]+a[i]);
            }
        }
        ans=max(ans,f[n&1][b][1]);
        cout<<ans<<endl;
    }
    return 0;
}
```


---

## 作者：zythonc (赞：0)

## 【分析过程】

我们可以用一个三维数组 $f_{i,o,p}$ 来表示状态

其中 $i$ 表示经过了的时间段，$o$ 表示已经睡了 $o$ 个时间段，$p$ 表示这个时间段有没有在睡觉

**那么对于一个时间段有两种决策：睡觉或是不睡觉**

- 没有睡觉，从上个时间段取最大值

- 睡觉，上一段时间又有两种状况：在睡觉或是没有睡觉；在睡觉即可获得效益值 $v_i$

所以我们可以推出转移方程：

$f_{i,o,0}=\max(f_{i-1,o,0},f_{i-1,o,1})$

$f_{i,o,1}=\max(f_{i-1,o-1,0},f_{i-1,o-1,1}+v_i)$

因为此题是一个环形动态规划，所以我们选择**强制断环然后强制连环**进行两次动态规划来消除后效性

断环，意即在时间 $N$ 不睡觉，所以额外初始化为 $f_{1,1,1}=0$

连环，意即在时间 $N$ 和次日时间 $1$ 的时候强制睡觉，所以额外初始化为 $f_{1,1,1}=v_1$，统计答案的时候为 $ans=\max(ans,f_{n,m,1})$

## 【代码实现】

```
#include<iostream>
#include<cstring>
#define N 4000
#define set(f) memset(f,-0x3f,sizeof(f))
#define cl(a) for(int i=1;i<=n;i++) a[i][0][0]=0;
using namespace std;
int n,in[N],T,b,ans,f[N][N][2];
signed main(){
	cin>>T;
	while(T--){ans=0;
	cin>>n>>b;
	for(int i=1;i<=n;i++){
		cin>>in[i];
	}
	set(f);cl(f);
	f[1][1][1]=0;
	for(int i=2;i<=n;i++){
		for(int o=1;o<=i;o++){
			f[i][o][0]=max(f[i-1][o][0],f[i-1][o][1]);
			f[i][o][1]=max(f[i-1][o-1][1]+in[i],f[i-1][o-1][0]);
		}
	}
	ans=max(f[n][b][0],f[n][b][1]);
	set(f);cl(f);
	f[1][1][1]=in[1];
	for(int i=2;i<=n;i++){
		for(int o=1;o<=i;o++){
			f[i][o][0]=max(f[i-1][o][0],f[i-1][o][1]);
			f[i][o][1]=max(f[i-1][o-1][1]+in[i],f[i-1][o-1][0]);
		}
	}
	cout<<max(ans,f[n][b][1])<<"\n";
	}
}
```

---

