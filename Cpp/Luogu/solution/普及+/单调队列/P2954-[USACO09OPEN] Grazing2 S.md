# [USACO09OPEN] Grazing2 S

## 题目描述

Farmer John has N (2 <= N <= 1,500) prize milk cows conveniently numbered 1..N. His newly-painted barn has S (N <= S <= 1,000,000) stalls (conveniently numbered 1..S) in a single long line; each stall is a unit distance from its neighboring stall(s).

The cows have made their way to the stalls for a rest; cow i is in stall P\_i. Antisocial as they are, the cows get grumpy if they are situated in stalls very close to each other, so Farmer John wants to move the cows to be as spread out as possible.

FJ wants to make sure that the N - 1 distances between adjacent cows are as large as possible, and he would also like them to be similar to each other (i.e., close to equi-distant spacing).

In particular, FJ would like all distances between adjacent cows to be at most 1 different from (S - 1) / (N - 1), where integer division is used. Moreover, he would like as many of these distances as possible to be exactly equal to (S - 1) / (N - 1) [integer

division]. Thus, with four cows and eight stalls, one can place the cows at positions 1, 3, 5, 8 or 1, 3, 6, 8 but not at 1, 2, 4, 7 or 1, 2, 4, 8.

Help FJ spread the cows as efficiently as possible by calculating and reporting the minimum total distance that the cows have to move in order to achieve proper spacing. Ignore the distance it takes for a cow to enter or exit a stall.

约翰有N(2≤N≤1500)头奶牛，S(N≤S≤1,000,000)个一字排开的牛棚．相邻牛棚间的距离恰好为1．

奶牛们已经回棚休息，第i只奶牛现在待在牛棚Pi．如果两只奶牛离得太近，会让奶牛们变得很暴躁．所以约翰想给一些奶牛换一个棚，让她们之间的距离变得尽量大，并且尽管接近．令d=Trunc((s-1)/(n-1))

所以约翰希望最终的奶牛的状态是：两只相邻奶牛间的距离与d之差不超过1，而且让尽量多的间距等于d．因此，对于4只奶牛8个棚的情况，1，3，5，8或1，3，6，8这样的安置情况是允许的，而1，2，4，7或1，2，4，8这样的情况是不允许的．    帮助约翰移动奶牛，让所有奶牛的移动距离之和最小，同时让最终的安置情况符合约翰心意．


## 说明/提示

1   2   3   4   5   6   7   8   9  10

Cow Locs     | A | B | C | . | . | . | . | D | E | . | 

Cows move from stall 2 to 3, 3 to 5, and 9 to 10. The total distance moved is 1 + 2 + 1 = 4. The final positions of the cows are in stalls 1, 3, 5, 8, and 10.

1   2   3   4   5   6   7   8   9  10

Init Stall     | A | B | C | . | . | . | . | D | E | . | 
Final Stall    | A | . | B | . | C | . | . | D | . | E | 
Distance moved | 0 | . | 1 | . | 2 | . | . | 0 | . | 1 | 

## 样例 #1

### 输入

```
5 10 
2 
8 
1 
3 
9 
```

### 输出

```
4 
```

# 题解

## 作者：Rainbow_qwq (赞：12)

[[USACO09OPEN]移动牛棚Grazing2](https://www.luogu.org/problem/P2954)
# 思路

$dp$

先对牛排一遍序。  
手推一下数据，发现对于每一头牛，它的距前一头牛的距离都是$d$或$d+1$。

有$n-1$个间隔，设有$c_1$个间隔为$n$,$c_2$个间隔为$n+1$，可列方程：

$\begin{cases} \mathrm{c_1+c_2=n-1} \\ \mathrm{c_1\times d+c_2\times (d+1)=s}\end{cases}$

解得$\mathrm{c_2=s-(n-1)\times d}$

然后设计$dp$状态，设$\mathrm{f[i][j]}$表示前$i$头牛，$j$个间隔为$n+1$的最小值。

答案即为$\mathrm{f[n][c_2]}$。

接下来是状态转移方程：对于这一个间隔，可以选$n$，也可以选$n+1$。

如果选了$j$个区间长度$n+1$,就有$i-j-1$个区间长度$n$。那这个点的“坐标”就是$\mathrm{(i-j-1)\times n+j\times(n+1)}$,简化可得$\mathrm{d\times (i-1)+j}$  
与第$i$头牛的距离就是$\mathrm{abs(a[i]-(d\times (i-1)+j))}$。

转移方程：
$\mathrm{f[i][j]=min(f[i-1][j],f[i-1][j-1])+abs(a[i]-(d\times (i-1)+j))}$

边界条件：第1头牛调整到1位置，$\mathrm{f[1][1]=a[1]-1}$

时间复杂度：2重循环，$O(n*s)$

代码：
```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(register int i=(a);i<=(b);++i)
#define Rep(i,a,b) for(register int i=(a);i>=(b);--i)
using namespace std;
inline int read()
{
    char c=getchar();int x=0;bool f=0;
    for(;!isdigit(c);c=getchar())f^=!(c^45);
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
    if(f)x=-x;return x;
}
int n,s,d,c2,f[1509][1509];
int a[1509];
int main()
{
    memset(f,63,sizeof f);
    n=read(),s=read(),d=int((s-1)/(n-1));c2=s-(n-1)*d;
    //预处理出s,c2的值
    For(i,1,n)a[i]=read();
    sort(a+1,a+n+1);//排一遍序
    f[1][1]=a[1]-1;//边界条件
    For(i,2,n)//dp
        For(j,1,min(c2,i))
            f[i][j]=min(f[i-1][j],f[i-1][j-1])+abs(a[i]-(d*(i-1)+j));
    cout<<f[n][c2];
    return 0;
}
```

---

## 作者：巨型方块 (赞：4)

题目要求间距最大，那么我们显然1好节点就一定在1的位置，n号节点就一定在最后

然后我们观察这个式子

d=(m-1)/(n-1)

不难发现最优情况下两个点的间距只可能是d或者d+1

而且d+1的个数就是m-1-d\*(n-1)个

所以f[i][j]表示前i个点有j个是d+1

注意第一个点就不做dp了，直接放到1 的位子

显然这个i点的位置就是d\*(i-1)+j

那么我们f[i][j]=min(f[i-1][j],f[i-1][j-1])+a[i]到其位置的距离

答案f[n][（m-1）-d\*(n-1)]

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e3+5;
int a[N],f[N][N],n,m,d;
int main()
{
    scanf("%d%d",&n,&m);m--;
    d=m/(n-1);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]),a[i]--;
    sort(a+1,a+n+1);
    memset(f,63,sizeof f);
    f[1][0]=a[1];
    for(int i=2;i<=n;i++)
        for(int j=0;j<=min(i-1,m-d*(n-1));j++)
            f[i][j]=min(f[i-1][j],f[i-1][j-1])+abs(a[i]-((i-1)*d+j));
    printf("%d",f[n][m-d*(n-1)]);            
}

```

---

## 作者：Elegy_of_Green_Kite (赞：4)

最近在刷单调队列的题目的时候做到了这道题目，看了一些大佬的题解才明白这道题的 DP 思路的，写篇题解纪念一下（并且给像我一样的萌新解释一下楼上大佬的一些结论如何推得）。

[原题链接](https://www.luogu.com.cn/problem/P2954)

### 题目大意

每头奶牛有一个初始位置 $Pi$，将奶牛们重新排列，使得每两头奶牛距离与 $d=(s-1)/(n-1)$ 之差不大于 $1$。

### 解题思路

首先，$d$ 是一个确定的值。那么每两头奶牛的距离只能是 $n-1$，$n$，$n+1$ 中的一个。

既然要让尽可能多的奶牛间距为 $n$，那么可以用一个 $n-1$ 和一个 $n+1$ 换成两个 $n$。根据 $d$ 的定义可以知道 $d-1$ 的数量一定小于 $n+1$ 的数量。

因此，所有奶牛之间距离只能是 $n$ 或者是 $n+1$。

因为要让所有奶牛之间距离尽可能大，所以 $1$ 号牛棚与 $n$ 号牛棚一定都有奶牛。换句话说，这若干个 $d$ 和若干个 $d+1$ 的和总为给定的值 $s-1$。

那么 $n-1$ 的数量就是 $s-1-d*(n-1)$，其余的就是 $n$ 的数量（不解释）。

现在，我们已经知道了所有奶牛之间的间距的所有情况。可以想到 DP 的思路。

令 $f_{i,j}$ 表示前 $i$ 个间距中有 $j$ 个是 $n+1$，$i-j$ 个是 $n$，$f_{i,j}=\min(f_{i-1,j},f_{i-1,j-1})  +$ 当前点到现在的位置的距离。

转移方程的意思很好理解，即要么当前的间距是 $n$（相当于 $j$ 的数量不变），要么当前间距是 $n+1$（相当于 $j$ 的数量加了 $1$）。

初始定义：第一头奶牛一定在第一位，移动其他奶牛需要更多代价，$f_{1,0}=a_{1}-1$。

另外，不要忘记初始排序。

### 代码

```cpp
#include<stdio.h>
#include<algorithm>
#include<string.h>
#include<iostream>
using namespace std;
const int N=2e3+5;
int a[N],f[N][N],n,s,d;
int main()
{
    memset(f,63,sizeof f); //初始化 
    scanf("%d %d",&n,&s);
    for(int i=1;i<=n;i++)  scanf("%d",&a[i]);
    sort(a+1,a+n+1);
    d=(s-1)/(n-1),f[1][0]=a[1]-1;
    for(int i=2;i<=n;i++)
        for(int j=0;j<=min(i-1,s-1-d*(n-1));j++)
        //注意一下j的取值不可能大于目前间距总数的数量 
            f[i][j]=min(f[i-1][j],f[i-1][j-1])+abs(a[i]-1-((i-1)*d+j));
    printf("%d",f[n][s-1-d*(n-1)]);
return 0;          
}
```


---

## 作者：shadowice1984 (赞：3)

这题主要是审题坑爹。。。

加个滚动数组优化

一开始扫反了Wa了一下。。。

我们发现对于每一头牛，它的距前一头牛的距离都是d或d+1

发现直接枚举长度会t（1e9）

那么我们发现，每一头牛的坐标，都是在i\*d~i\*d+i

之间，(因为每次挪牛最多引起1的误差)

所以设dp[j]为总误差为j的放置最小花费

然后滚动更新，这样可以省一维数组

还有就是记得排序，和题目中含混不清的表示

(题目中的距离从一开始，方便计算统一平移1)

上代码~

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int abso(int x){return (x>=0)?x:-x;}
int dis[1510];
int dp[1510];
int n;int m;int d;
int main()
{
    scanf("%d%d",&n,&m);
    d=(m-1)/(n-1);
    for(int i=0;i<n;i++)
    {
        scanf("%d",&dis[i]);dis[i]-=1;
    }
    for(int i=0;i<n;i++)//手动memset
    {
        dp[i]=0x3f3f3f3f;
    }
    sort(dis,dis+n);//排序啥的就不用说了吧
    dp[0]=abso(dis[0]-0);
    for(int i=1;i<n;i++)//更新
    {
        for(int j=min(i,m-(n-1)*d);j>=1;j--)//由于是滚动数组一定要倒着扫，不然会翻车
        {
            dp[j]=min(dp[j],dp[j-1])+abso(dis[i]-i*d-j);    
    }dp[0]+=abso(dis[i]-i*d);
    }
    printf("%d",dp[m-(n-1)*d-1]);//由于整体平移1，所以记得-1
    return 0;//拜拜程序
}

```

---

## 作者：wei2013 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P2954)
## 思路：
一道 dp 题。

状态定义：$dp_{i,j}$ 表示前 $i$ 个牛棚，有 $j$ 个与上一个的距离是 $d+1$。如何得来？根据题目，奶牛位置对于上一只的距离可能是 $d-1$，$d$，$d+1$。其中 $d-1$ 和 $d+1$ 不可以同时存在，而 $d+1+d-1=2d$，所以可以消掉一种情况，我这边呢是选择保留 $d+1$。

初始化：显而易见，只有第一头牛移到位置 $1$，才有可能合法。

状态转移：
$$dp_{i,j}=\min(dp_{i-1,j},dp_{i-1,j-1}+\left | ((d(i-1)+j)-a_{i}) \right |) $$

从此时区间长度是 $d+1$ 还是 $d$，然后加上这只奶牛需要移动的距离即可。

答案得出：设 $y$ 是 $d+1$ 情况的最多区间数，可以通过解方程得出 $y=m-(n-1)d$，所以答案就是 $dp_{n,y}$。
## code：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n,m,a[1505],dp[1505][1505];
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	sort(a+1,a+n+1);
	memset(dp,0x3f,sizeof(dp));
	int d=(m-1)/(n-1),y=m-(n-1)*d;
	dp[1][1]=a[1]-1;
	for(int i=2;i<=n;i++){
		for(int j=1;j<=min(y,i);j++){
			dp[i][j]=min(dp[i-1][j],dp[i-1][j-1])+abs((d*(i-1)+j)-a[i]);
		}
	}
	cout<<dp[n][y];
	return 0;
} 
```

---

## 作者：staygone (赞：1)

## 思路

让距离最大，奶牛 $1$ 一定在 $1$ 号牛棚，奶牛 $n$ 一定在 $s$ 号牛棚，考虑 dp 做法。

总距离为 $s - 1$ ，要使长度为 $d$ 的段数尽量多，那么剩下的一定就是 $d + 1$ 的段数，也就是 $s - (n - 1) \times d$ 。

我们让 $f_{i,j}$ 表示前 i 个牛棚合理且前面长为 $d + 1$ 的段数为 $j$ 的答案，然后第 i 个牛棚的位置其实就是 $(i - 1) \times d + j$ 。

因为第 $i - 1$ 个牛棚只可能是相隔 $d$ 或 $d - 1$ ，所以有 $f_{i,j} = \min (f_{i-1,j}, f_{i-1,j-1}) + \lvert a_i - (i - 1) \times d - j \rvert$ 。

## CODE

```cpp
#include <bits/stdc++.h>
#define sf scanf
#define pf printf
using namespace std;
int a[10005], f[2005][2005];
int n, s;
int main () {
	memset (f, 0x3f3f3f3f, sizeof f);
	sf ("%d %d", &n, &s);
    int d, m;
    d = (s - 1) / (n - 1);
	m = s - (n - 1) * d;
    for (int i = 1; i <= n; i ++) {
    	sf ("%d", &a[i]);
	}
    sort (a + 1, a + n + 1);
    f[1][1] = a[1] - 1;
    for (int i = 2; i <= n; i ++) {
    	for (int j = 1; j <= m && j <= i; j ++) {
        	f[i][j] = min (f[i - 1][j], f[i - 1][j - 1]) + abs (a[i] - d * (i - 1) - j);
		}
	}
    pf ("%d", f[n][m]);
    return 0;
}
```
## 问题

我发现，在此做法下，若不是数据有点水，会RE。

我就继续想，有什么可以简化空间吗？

## 优化

可以用滚动数组，有一维只用开二维。	但是我实现了半天，这方面果然还是要加强一下。

## CODE(plus)

```cpp
#include <bits/stdc++.h>
#define sf scanf
#define pf printf
using namespace std;
int a[10005], f[2][1005];
int n, s;
int main () {
	memset (f, 0x3f, sizeof f);
	sf ("%d %d", &n, &s);
    int d, m;
    d = (s - 1) / (n - 1);
	m = s - (n - 1) * d;
    for (int i = 1; i <= n; i ++) {
    	sf ("%d", &a[i]);
	}
    sort (a + 1, a + n + 1);
    f[1][1] = a[1] - 1;
    for (int i = 2; i <= n; i ++) {
    	int k = i % 2;
    	for (int j = 1; j <= m && j <= i; j ++) {
        	f[k][j] = min (f[(!k)][j], f[(!k)][j - 1]) + abs (a[i] - d * (i - 1) - j);
		}
	}
    pf ("%d", f[n % 2][m]);
    return 0;
}
```
感谢阅读

---

## 作者：125125A (赞：0)

# 前言
随机跳题跳过来的，当我看见 $619$ 提交但是只有 $111$ 通过的时候，我还以为是什么世纪级难题。
# 正文
[题目传送门](https://www.luogu.com.cn/problem/P2954)
## 题目大意
每头奶牛有一个初始位置 $P_{i}$，将奶牛们重新排列，使得每两头奶牛距离与 $d=(s−1) \div (n−1)$ 之差不大于 $1$。
## 思路
1.  让距离最大，奶牛 $1$ 一定在 $1$ 号牛棚，奶牛 $n$ 一定在 $s$ 号牛棚，考虑 dp 做法。

2.  总距离为 $s−1$ ，要使长度为 $d$ 的段数尽量多，那么剩下的一定就是 $d+1$ 的段数，也就是 $s−(n−1)\times d$。

3.  我们让 $f_{i,j}$ 表示前 $i$ 个牛棚合理且前面长为 $d+1$ 的段数为 $j$ 的答案，然后第 $i$ 个牛棚的位置其实就是 $(i−1)\times d+j$。

4.  因为第 $i−1$ 个牛棚只可能是相隔 $d$ 或 $d−1$，所以有 $f_{i,j}=\min(f_{i-1,j},f_{i-1,j-1})+\left | a_{i}-(i-1)\times d-j \right | $。

## Code:

```
#include <bits/stdc++.h>
using namespace std;

int arr[10005], f[2005][2005];
int n, s;

int main () {
	
	memset (f, 0x3f3f3f3f, sizeof f);
	
	cin >> n >> s;
	
	int d, m;
	d = (s - 1) / (n - 1);
	m = s - (n - 1) * d;
	
	for (int i = 1; i <= n; i ++) {
		cin >> arr[i];
	}
	
	sort (arr + 1, arr + n + 1);
	f[1][1] = arr[1] - 1;
	
	for (int i = 2; i <= n; i ++) {
		for (int j = 1; j <= m && j <= i; j ++) {
			f[i][j] = min (f[i - 1][j], f[i - 1][j - 1]) + abs (arr[i] - d * (i - 1) - j);
		}
	}
	
	cout << f[n][m];
	
	return 0;
}
```

~~码风猎奇，勿喷。~~

---

## 作者：封禁用户 (赞：0)

应用算法：dp 大法好！

题目大意：每头奶牛有一个初始位置 $P_i$，重排奶牛们，使得每两头奶牛距离与 $d=\dfrac{s-1}{n-1}$ 的差 $\le1$。

思路：不难发现最优情况下两个点的间距只可能是 $d$ 或者 $d+1$。而且 $d+1$ 的个数就是 $m-1-d\times(n-1)$ 个,所以 $f_{i,j}$ 表示前 $i$ 个点有 $j$ 个是 $d+1$。遂易状态转移：
$$dp_{i,j}=\min(dp_{i-1,j},dp_{i-1,j-1}+\left | d(i-1)+j-a_i\right |)$$

此时问题便迎刃而解了。

---

