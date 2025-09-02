# 阿里巴巴 Alibaba

## 题目描述

## 题面描述
在**一条直线**的同一个方向上有  $n$ 件珠宝，已知每件珠宝的位置，并且第  $i$ 件珠宝在  $t_i$ 时刻就毁灭，问能否将所有的珠宝收集起来？搜集不耗时，移动需要耗时。

# 题解

## 作者：vines (赞：5)

题目大意：在一条直线上有n（n<=10000）个点有宝藏，每个点的坐标都是整数，每个宝藏在某个时间到之后都会消失，可以在任何一个点出发，移动一个单位需要一个单位的时间，问最少需要多少时间拿完所有宝藏，如果不能拿完所有的输出No solution。输入按照坐标递增顺序。



a[i]表示第i个宝藏的位置，b[i]表示消失的时间。

首先注意到对于任意区间(i,j)，拿完所有宝藏之后必然在i或j两者之一。所以用d[i][j][0]表示拿完第i个到第j个之间的所有宝藏，且最后位于i，用d[i][j][1]表示拿完第i个到第j个之间的所有宝藏且最后位于j。

程序用滚动数组优化内存消耗，递推是按照区间的宽度递增的顺序，所以也是按照这样滚动的。



状态转移方程：

d[i][j][0]=min { d[i+1][j][0]+a[i+1]-a[i],d[i+1][j][1]+a[i+j]-a[i]}

d[i][j][1]=min { d[i][j-1][0]+a[i+j]-a[i],d[i][j-1][1]+a[i+j]-a[i+j-1]}

在程序中还需要判断递推过程中是否能在消失前到达，不能到达则置为INF。



```cpp
#include<stdio.h>  
#include<stdlib.h>  
int a[10010];  
int b[10010];  
int d[2][10010][2];  
int main(void)  
{  
    int i,j,n,cur,min;  
    while(scanf("%d",&n)==1)  
    {  
        for(i=1;i<=n;i++)  
        {  
            scanf("%d%d",&a[i],&b[i]);  
        }  
        cur=0;  
        for(j=1;j<=n;j++)  
        {  
            d[0][j][0]=d[0][j][1]=(b[j]>0)?0:(1<<30);  
        }  
        for(i=1;i<n;i++)  
        {  
            cur^=1;  
            for(j=1;j<=n-i;j++)  
            {  
                d[cur][j][0]=d[cur^1][j+1][0]+a[j+1]-a[j]>d[cur^1][j+1][1]+a[j+i]-a[j]?d[cur^1][j+1][1]+a[j+i]-a[j]:d[cur^1][j+1][0]+a[j+1]-a[j];  
                d[cur][j][1]=d[cur^1][j][0]+a[j+i]-a[j]>d[cur^1][j][1]+a[j+i]-a[j+i-1]?d[cur^1][j][1]+a[j+i]-a[j+i-1]:d[cur^1][j][0]+a[j+i]-a[j];  
                d[cur][j][0]=d[cur][j][0]<b[j]?d[cur][j][0]:(1<<30);  
                d[cur][j][1]=d[cur][j][1]<b[j+i]?d[cur][j][1]:(1<<30);  
            }  
        }  
        min=d[cur][1][0]>d[cur][1][1]?d[cur][1][1]:d[cur][1][0];  
        if(min==(1<<30))  
        {  
            printf("No solution\n");  
        }  
        else  
        {  
            printf("%d\n",min);  
        }  
    }  
    return 0;  
}  

```

---

## 作者：蒟酱 (赞：3)

简单题意：数轴上有 $n$ 个点，已知每个点的坐标 $a_i$ 和毁灭时间 $t_i$ 。开始时可以选择任意一点空降，每刻可以选择向左或者向右移动 $1$ 的单位长度，求出经过所有点的最短时间，如果不可能输出 `No solution` 。  

首先因为经过点不会浪费时间，而且题目说 $a_i$ 是有序的，所以可以通过区间 $[a_j,a_i,x]$ 表示经过此区间 $[a_j,a_i]$ ，并且当前位置是 $x$ 的所有点消耗的最短时间。  

考虑区间DP。然而因为压根不知道 $a_i$ 的大小所以无法存下这个巨型状态，考虑优化。因为经过区间时保证每个点都被访问，贪心一下得出目前位置要么在区间最左端要么在最右段。那就以 $f_{j,i,0}$ 表示经过区间 $[j,i]$ 并且目前在点 $a_j$ 的最短时间，以 $f_{j,i,1}$ 表示经过区间 $[j,i]$ 并且目前在点 $i$ 的最短时间。  

接下来考虑状态转移，也就是动规方程：

每个区间都是由 $2$ 个小区间合并起来的，以下用 $j$ 来表示区间左端，用 $i$ 来表示区间右端。  

以 $f_{j,i,0}$ 举例子，每次要么从 $f_{j+1,i,0}$ 向左移动过 $1$ 个点，移动距离是 $a_{j+1}-a_j$ ；要么从 $f_{j+1,i,1}$ 走过 $i-j$ 个点，移动距离是 $a_i-a_j$。向右转移同理。还要在每次转移结束后还要判断，如果当前时间大于等于被刚刚经过的点的摧毁时间，标记为极大值。  

接下来是初始状态，因为可以从任意一点空降落地瞬间经过任意单点，所以 $f_{i,i,0}=f_{i,i,1}=0$ 。最终答案是 $f_{1,n,0}$ 和 $f_{1,n,1}$ 的较小值。如果还是出现了极大值就表示无解。  

两重循环，每次是 $10^4$ 总共是 $10^8$ 卡卡常数就完全不会超时。对代码有较大要求看不惯 $10^4$ 二维数组的可以写滚动数组，但是这题没必要。另外记得 UVA 是多组数据。  

这里建议每个人按照自己区间 DP 中枚举左端和右端的方式写，因为方式实在是太太太多了，每次写不一样的就很容易出错。  

~~最重要的代码~~

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<cmath>
using std::cin;using std::cout;
template<typename any>inline any max(any x,any y){return x>y?x:y;}
template<typename any>inline any min(any x,any y){return x<y?x:y;}
template<typename any>inline any abs(any x){return x>0?x:-x;}
struct treasure{int a,t;}a[10007];
int f[10007][10007][2];
signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);cout.tie(nullptr);
	int i,j,k;
	int n,m,T;

	while(cin>>n)
	{
		for(i=1;i<=n;i++)f[i][i][0]=f[i][i][1]=0;
		for(i=1;i<=n;i++)cin>>a[i].a>>a[i].t;
		for(i=2;i<=n;i++)for(j=i-1;j;j--)
		{
			f[j][i][0]=min(f[j+1][i][0]+a[j+1].a-a[j].a,f[j+1][i][1]+a[i].a-a[j].a);
			if(f[j][i][0]>=a[j].t)f[j][i][0]=0x3f3f3f3f;
			f[j][i][1]=min(f[j][i-1][1]+a[i].a-a[i-1].a,f[j][i-1][0]+a[i].a-a[j].a);
			if(f[j][i][1]>=a[i].t)f[j][i][1]=0x3f3f3f3f;
		}
		int ans=min(f[1][n][0],f[1][n][1]);
		if(ans==0x3f3f3f3f)cout<<"No solution\n";
		else cout<<ans<<'\n';
	}

	return 0;
}
```

---

## 作者：Sata_moto (赞：2)


[ $\color {#6495ED} \mathcal{MyBlog}$](https://xjx885.coding-pages.com/)

---

### 前言：

本题题解比较少诶...

我交一发好了...

---

### 题目大意：

给定一条线段，其上有n个珠宝，每个珠宝到线段最左端距离为定值$d_i$，珠宝在$t_i$时刻会消失，可以从任意地点开始收集珠宝，每单位时间可以移动一个单位的距离，问收集所有珠宝的最少时间是多少？

---

### 题目分析:

这题难点主要在于状态表示...

当然，首先你得看出来这题是道DP...

观察数据规模，$n<=10000$

这意味着，我们的DP数组顶多开n^2....

首先，我们思考最暴力的方法：状压DP...

令$f[k][i]$表示现在在k点的位置，已经走过了二进制状压后为i的点...

显然不行，复杂度高达$2^{10000}$

我们考虑优化i这一维：

思考可知，假如我们通过了点i，我们自然会顺手拿起其上的珠宝...

而我们从起始点开始，经过的路径一定是连续的线段...

这意味着，我们所拿走的点一定是连续的...

换句话说，我们可以把状态改为$f[k][i][j]$表示我们在k点，经过了$i-j$中所有点，所花费的最少时间...

然而复杂度任然高达$O(n^3)$...

继续考虑优化...

i,j两维似乎没办法优化了，我们似乎可以优化k...

我们已经理解：走过的点一定是一个连续区间...

那么我们最后会落在哪呢？

我们不可能落到区间中的任意一点...只有可能落在区间两极...

为什么？

很明显...从第一步开始，我们每到达一个未经过的点，本质就是对 经过的点 这个区间的左右拓展...

比如说我经过了$i$~$j$这个区间的所有点，下一步我无非就是要么走到$i-1$点，拓展区间左端，要么走到$r+1$点，拓展区间右端...

如果说走到$i-2$的点呢？ 其实就是先走到$i-1$ ,再走到$i-1 -1$的点...

因此，我们可以把原状态优化为f[i][j][0/1]，表示走过了$i$~$j$的区间，正处在区间左/右端点...

转移便是分别向左向右走一步...

至于初态，因为我们的初始节点是随意的，所以说$f[i][i][0/1]=0$

剩下的细节见代码就好0.0...

本题与[洛谷P1220 关路灯](https://www.luogu.org/problem/P1220)很是相像，推荐过去做一做...

---

### 代码：

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 10010;

int n;
int dis[N], die[N];

int f[N][N][2];
//经过了l,r的区间，站在l/r点时的最小时间

int main()
{
	while(scanf("%d", &n) != EOF)
	{
		for(int k = 1; k <= n; k++)
			scanf("%d %d", &dis[k], &die[k]);

		//初始化
		memset(f, 0x3f, sizeof(f));
		for(int k = 1; k <= n; k++)
			f[k][k][0] = f[k][k][1] = 0;
		
		for(int len = 2; len <= n; len++)
			for(int l = 1; l + len - 1 <= n; l++)
			{
				int r = l + len - 1;

				f[l][r][0] = min(f[l + 1][r][0] + dis[l + 1] - dis[l] , f[l + 1][r][1] + dis[r] - dis[l]);
				if(f[l][r][0] >= die[l]) f[l][r][0] = 0x3f3f3f3f;

				f[l][r][1] = min(f[l][r - 1][1] + dis[r] - dis[r - 1] , f[l][r - 1][0] + dis[r] - dis[l]);
				if(f[l][r][1] >= die[r]) f[l][r][1] = 0x3f3f3f3f;
			}

		int answ = min(f[1][n][0], f[1][n][1]);

		if(answ == 0x3f3f3f3f)
			printf("No solution\n");
		else
			printf("%d\n", answ);
	}

	return 0;
}
```


---

### 结语：


如果本题解有BUG...

那么...那么...那么...

（随意了）还请私信作者....


---

## END

---

## 作者：forever516 (赞：0)

# 题意
在一条直线的同一个方向上有
$n$
件珠宝，已知每件珠宝的位置，并且第
$i$
件珠宝在 
$t_i$
时刻就毁灭，问能否将所有的珠宝收集起来？

### 注意：搜集不耗时，移动需要耗时！

# 解法
对于任意区间
$(i,j)$
中，拿完所有宝藏之后绝对会在
$i$
或
$j$。

因此，我们定义一个
$dp$
数组
$f_{i,j,0}$
表示拿完第
$i$
个到第
$j$
个之间的所有宝藏，且最后位于
$i$
这个位置。

有了上面的定义，我们当然能想到第二个
$dp$
式子。

用
$f_{i,j,1}$
表示拿完第
$i$
个到第
$j$
个之间的所有宝藏且最后位于
$j$。

其实，总结一下，数组最后一位的
$0,1$
代表取
$i$
或取
$j$。

由推导可知状态转移方程：

$f_{i,j,0}=\min(f_{i+1,j,0}+a_{i+1}-a_i,f_{i+1,j,1}+a_{i+j}-a_i)$

$f_{i,j,1}=\min(f_{i,j-1,0}+a_{i+j}-a_i,f_{i,j-1,1}+a_{i+j}-a_{i+j-1})$

代码见下：


```cpp
#include<iostream>
#include<cstring>
#include<string>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstdlib>
#include<bits/stdc++.h>
#define ll long long
#define N 1010
#define M 0x3f
using namespace std;
using std::cin;
using std::cout;
template<typename any>inline any abs(any x){return x>0?x:-x;}
int a[N],b[N],f[N][N][2],i,j,n;
void init() {
	for(i=1; i<=n; i++)f[i][i][0]=f[i][i][1]=0;
}
void input() {
//	ios::sync_with_stdio(0);
//	cin.tie(0);
//	cout.tie(0);
//	这题不能用解绑！ 
	cin>>n;
	for(i=1; i<=n; i++)cin>>a[i]>>b[i];
	init();
}
void write(int num) {
	int a[10],cnt=0;
	while(num>0) {
		a[cnt++]=num%10;
		num/=10;
	}
	for(int i=cnt-1; i>=0; i--)cout<<a[i];
	cout<<"\n"; 
}
int main() {
	input();
	for(i=2; i<=n; i++) {
		for(j=i-1; j; j--) {
			f[j][i][0]=min(f[j+1][i][0]+a[j+1]-a[j],f[j+1][i][1]+a[i]-a[j]);
			if(f[j][i][0]>=b[j])f[j][i][0]=M;
			f[j][i][1]=min(f[j][i-1][1]+a[i]-a[i-1],f[j][i-1][0]+a[i]-a[j]);
			if(f[j][i][1]>=b[i])f[j][i][1]=M;
		}
	}
	int ans=min(f[1][n][0],f[1][n][1]);
	if(ans==M)cout<<"No solution\n";
	else write(ans);
	if(n)main();
	return 0;
}
```

---

## 作者：wanyiheng (赞：0)

[题目链接](https://www.luogu.com.cn/problem/UVA1632)

### 题目大意：
在一条直线上有 $n(n\le10000)$ 个点有宝藏，每个点的坐标都是整数，每个宝藏在某个时间到之后都会消失，从左往右第i个宝藏的坐标为 $a_i$，消失的时间是 $t_i$。阿里巴巴可以在任何一个点出发，移动一个单位需要一个单位的时间，问最少需要多少时间拿完所有宝藏，如果不能拿完所有的输出 No solution。

##### 阶段：每次讨论一个连续的区间,以区间的长度为讨论的阶段。

#### 状态：

- $dp[i][j][2]$ 表示搜集完第 $i$ 个宝藏到第 $j$ 个宝藏最小时间。即处理区间 $[i,j]$ 所需最小时间。
- $dp[i][j][0]$ 表示结束时，阿里巴巴停在了区间左端(坐标    $a_i$ 处)。
- $dp[i][j][1]$ 表示结束时，阿里巴巴停在了区间右端(坐标 $a_j$处)。

#### 决策： 
当前收集哪一个宝藏。

#### 方程：

$$
\textstyle dp[i][j][0]=\min(dp[i+1][j][0]+a[i+1]-a[i],dp[i+1][j][1]+a[j]-a[i])
$$

$$
\textstyle dp[i][j][1]=\min(dp[i][j-1][0]+a[j]-a[i],dp[i][j-1][1]+a[j]-a[j-1])
$$

#### 边界条件:

$1 \le i \le n,i \le j \le n$

在程序中还需要判断递推过程中是否能在消失前到达，不能到达则置为 INF。

根据方程，我们需要一个很大的状态数组 $dp[10000][10000][2]$，$dp$ 数组占用了约 800m 的空间，显然不行！怎么优化空间？

可以考虑用滚动数组来压缩空间！

#### 方程：

$$
\textstyle dp[i][j][0]=min(dp[i \oplus 1][j][0]+a[i+1]-a[i],dp[i \oplus 1][j][1]+a[j]-a[i])
$$

$$
\textstyle dp[i][j][1]=min(dp[i][j-1][0]+a[j]-a[i],dp[i][j-1][1]+a[j]-a[j-1])
$$

现在，我们只需要一个状态数组 $dp[2][10000][2]$。

#### 实际处理时状态：

$dp[i][x][2]$ 表示搜集完第 $i$ 个宝藏开始连续 $x$ 个宝藏所需最小时间。上面所述的 $j=i+x-1$；

## **code：**

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N=10010;

int n;
int a[N],t[N];
int dp[N][N][2];

int main()
{
	while(scanf("%d", &n)!=EOF)
	{
		for(int i=1;i<=n;i++)
			scanf("%d %d", &a[i], &t[i]);
		memset(dp,1e9,sizeof dp);
		for(int i=1;i<=n;i++)
			dp[i][i][0]=dp[i][i][1]=0;
		for(int i=2;i<=n;i++){
			for(int j=1;j+i-1<=n;j++)
			{
				dp[i][j][0]=min(dp[i][j][0],min(dp[i^1][j][0]+a[i+1]-a[i],dp[i^1][j][1]+a[j]-a[i]));
				dp[i][j][1]=min(dp[i][j][0],min(dp[i][j-1][0]+a[j]-a[i],dp[i][j-1][1]+a[j]-a[j-1]));
			}
		}
		int ans=min(dp[1][n][0],dp[1][n][1]);
		if(ans==0x3f3f3f3f)puts("No solution");
		else printf("%d\n", ans);
	}

	return 0;
}
```

---

