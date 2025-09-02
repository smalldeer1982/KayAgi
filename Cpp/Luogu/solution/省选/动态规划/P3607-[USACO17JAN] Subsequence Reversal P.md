# [USACO17JAN] Subsequence Reversal P

## 题目描述

Farmer John 正在将他的 $N$ 头奶牛排成一列拍照（$1 \leq N \leq 50$）。序列中第 $i$ 头奶牛的高度为 $a(i)$，Farmer John 认为如果奶牛队列中存在一个较长的按高度递增的子序列，那么这张照片会更具美感。

回顾一下，子序列是指从奶牛序列中选出的一组元素 $a(i_1), a(i_2), \ldots, a(i_k)$，这些元素位于一系列索引 $i_1 < i_2 < \ldots < i_k$ 处。如果满足 $a(i_1) \leq a(i_2) \leq \ldots \leq a(i_k)$，则称该子序列是递增的。

FJ 希望在他的奶牛排列中存在一个较长的递增子序列。为了确保这一点，他允许自己最初选择任意一个子序列并将其元素反转。

例如，如果我们有以下序列：

```
1 6 2 3 4 3 5 3 4
```

我们可以反转选中的元素：

```
1 6 2 3 4 3 5 3 4
  ^         ^ ^ ^
```

得到：

```
1 4 2 3 4 3 3 5 6
  ^         ^ ^ ^
```

注意被反转的子序列最终仍然使用最初占据的索引，而其他元素保持不变。

请找出在最多反转一个子序列的情况下，可能的最长递增子序列的长度。

## 样例 #1

### 输入

```
9
1
2
3
9
5
6
8
7
4```

### 输出

```
9
```

# 题解

## 作者：苏22 (赞：13)

### 前言
前几天，老师让我们做题，结果，做这道，裂开。

## 正解
这道题是道区间 `dp`，但，难的一批，转移方程想到了就很简单。

首先，我们设一个数组 $dp_{l,r,L,R}$，表示从 `l` 到 `r` 的区间，值域为 `L~R` 的最大价值。

转移方程：我们先看看它不转换序列，最大价值，则为
```cpp
dp[l][r][L][R]=max(dp[l][r][L+1][R],dp[l][r][L][R-1]);//把小值域的价值转换到大值域
dp[l][r][L][R]=max(dp[l][r][L][R],dp[l+1][r][L][R]+(a[l]==L));//向左扩展
dp[l][r][L][R]=max(dp[l][r][L][R],dp[l][r-1][L][R]+(a[r]==R));//向右扩展

```
接下来考虑序列转移后，转移方程怎么弄，既然要转换，也要是最长不下降子序列，则要判断，转换后，是否是最长不下降子序列，则为
```cpp
dp[l][r][L][R]=max(dp[l][r][L][R],dp[l+1][r-1][L][R]+(a[l]==R)+(a[r]==L));//序列翻转后，最大价值 
```

这样的话，再初始化，就行了！！！！

### AC代码

```cpp
#include <algorithm>
#include <cstdio>
using namespace std;
int n, a[51], dp[51][51][51][51];
int main()
{
    scanf("%d",&n);
    for (int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        for (int L=1;L<=a[i];L++)
            for (int R=a[i];R<=50;R++)
                dp[i][i][L][R]=1;//初始化 
    }
    for (int len=2;len<=n;len++)//枚举区间长度 
    {
    	for (int l=1,r=len;r<=n;l++,r++)//枚举起点和终点 
    	{
    		for (int llen=1;llen<=50;llen++)//枚举值域 
    		{
    			for (int L=1,R=llen;R<=50;L++,R++)//枚举值域起点和重点 
                {
                    dp[l][r][L][R]=max(dp[l][r][L+1][R],dp[l][r][L][R-1]);//把小值域的价值转换到大值域
                    dp[l][r][L][R]=max(dp[l][r][L][R],dp[l+1][r][L][R]+(a[l]==L));//向左扩展
                    dp[l][r][L][R]=max(dp[l][r][L][R],dp[l][r-1][L][R]+(a[r]==R));//向右扩展
                    dp[l][r][L][R]=max(dp[l][r][L][R],dp[l+1][r-1][L][R]+(a[l]==R)+(a[r]==L));//序列翻转后，最大价值 
                }
			}
		}
	}
    printf("%d",dp[1][n][1][50]);
    return 0;
}
```

---

## 作者：kczno1 (赞：13)

感觉这题关键就是注意到一个子序列的反转等价于多次交换了两边

之后用dp[l][r][down][up]表示[l,r]值域在[down,up]的最长不降

只用考虑交换不交换即可





    
    
```cpp
//=max:
//dp[l][r][down+1][up] / [down][up-1]
//dp[l+1][r][down][up]+(down==a[l]) / [l][r-1]+(up==a[r])
//dp[l+1][r-1][down][up]+(down==a[r])+(up==a[l])
#include<bits/stdc++.h>
using namespace std;
const int N=52;
int a[N],f[N][N][N][N];
void chmax(int &x,int y)
{
    if(x<y)x=y;
}
int main()
{
    int n,i,l,r,down,up;
    scanf("%d",&n);
    for(i=1;i<=n;++i)
    {scanf("%d",a+i);
     for(down=1;down<=a[i];++down)
     for(up=a[i];up<=50;++up)
      f[i][i][down][up]=1;
    }
    for(int l1=2;l1<=n;++l1)
    for(l=1,r=l1;r<=n;++l,++r)
    for(int l2=1;l2<=50;++l2)
    for(down=1,up=l2;up<=50;++down,++up)
    {
        int ans=max(f[l][r][down+1][up],f[l][r][down][up-1]);
        chmax(ans,f[l+1][r][down][up]+(down==a[l]));
        chmax(ans,f[l][r-1][down][up]+(up==a[r]));
        chmax(ans,f[l+1][r-1][down][up]+(down==a[r])+(up==a[l]));
        f[l][r][down][up]=ans; 
    } 
    printf("%d\n",f[1][n][1][50]);
}
```

---

## 作者：w33z8kqrqk8zzzx33 (赞：10)

看到 LIS 自然想到 dp，但是这里按照普通方法 dp 看的非常难，由于不能预测某个反转对会反转到哪里。但是，如果我们把这些反转交换对匹配一下，会发现：

```
1 6 2 3 4 3 5 3 4
  ^         ^ ^ ^
  |         +-+ |
  +-------------+
```

这个（6，4）对固定为一个反转对之后，后面反转对必须在（6，4）之内，把问题缩小。于是尝试做区间 dp。

来快速判断某个值能否对某个区间贡献，需要保存这个区间所有值域区间的答案。换句话说，对每一个值域区间和位置区间，需要计算这个位置区间内只包含值域区间的元素的 LIS。

$(l,r,L,R)$ 的 dp 怎么转移？

 1. 肯定要包含子值域区间，从 $(l,r,L,R-1)$ 和 $(l,r,L+1,R)$ 转移
 2. 如果想选上 $l$，需要 $a_l=L$，如果 $a_l=L$ 则可以从 $(l+1,r,L,R)+1$ 转移。类似如果 $a_r=R$，则可以从 $(l,r-1,L,R)+1$ 转移
 	- 如果 $a_l \neq L$ 但是还可以被选上，在这里不需要考虑，最终会被转移 1 算
 3. 强行把 $(l,r)$ 当做一个反转对，那么区间缩小到 $(l+1,r-1)$，然后 $a_l$ 和 $a_r$ 也尽量尝试贡献：从 $(l+1,r-1,L,R)+[a_l=R]+[a_r=L]$ 转移

由于转移顺序比较难搞，用记一化搜索即可。

代码：

```cpp

int dp[51][51][51][51];
int a[51];
int dfs(int l, int r, int lb, int ub) {
	if(l > r) return 0;
	if(lb > ub) return 0;
	if(l == r && lb <= a[l] && a[l] <= ub) return 1;
	if(dp[l][r][lb][ub] != -1) return dp[l][r][lb][ub];
	int ans = max(dfs(l+1, r, lb, ub), dfs(l, r-1, lb, ub));
	ans = max(ans, dfs(l, r, lb, ub-1));
	ans = max(ans, dfs(l, r, lb+1, ub));
	if(a[l] == lb) ans = max(ans, dfs(l+1, r, lb, ub) + 1);
	if(a[r] == ub) ans = max(ans, dfs(l, r-1, lb, ub) + 1);
	ans = max(ans, dfs(l+1, r-1, lb, ub) + (a[l] == ub) + (a[r] == lb));
	return dp[l][r][lb][ub] = ans;
}
signed main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    memset(dp, -1, sizeof dp);
	int n; cin >> n;
	rep1(i, n) cin >> a[i];
	cout << dfs(1, n, 1, 50) << endl;
}
```

---

## 作者：Z1qqurat (赞：2)

这是一篇真实的解题报告。

### 思路

Part 1：我是怎么想到这是一道区间 dp 的？

首先这道题符合 dp 的特点，而且这道题可以是从小区间推向大区间，大致可以确定是区间 dp 了；

然后看看数据范围，区间 dp 应该差不多。

Part 2：我是怎么想到这个状态的？

既然是不下降子序列，那我们考虑从小区间到大区间，是否可以让子序列更长取决于和原来的小序列中的极值的大小关系。

于是我们索性开一个四维的数组 $dp_{i,j,L,R}$，表示区间是从 $i$ 到 $j$，而值域是从 $L$ 到 $R$ 的最长不下降子序列长度。

Part 3：怎么算不用反转的情况？

这道题的难点就在可以反转一次。

那如果我把它当作不能反转呢？

那么只需要考虑三种情况：从两端的值域转移，区间往左扩展，区间往右扩展。

状态转移方程就是：

```cpp
dp[i][j][L][R]=max(dp[i][j][L+1][R],dp[i][j][L][R-1]);//从两端的值域转移
dp[i][j][L][R]=max(dp[i][j][L][R],dp[i+1][j][L][R]+(a[i]==L));//区间往左扩展
dp[i][j][L][R]=max(dp[i][j][L][R],dp[i][j-1][L][R]+(a[j]==R));//区间往右扩展
```  

Part 4：那是怎么解决反转问题的呢？

反转，无非就是多次交换两边数的位置。

于是再加一个方程就可以了：

```cpp
dp[i][j][L][R]=max(dp[i][j][L][R],dp[i+1][j-1][L][R]+(a[i]==R)+(a[j]==L));
```

Part 5：边界条件？

这个题主要是要考虑初始值。按照状态的定义来写即可：

```cpp
for(ri l=1;l<=a[i];l++){
	for(ri r=a[i];r<=50;r++){
		dp[i][i][l][r]=1;
	}
}
```

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
const int MAXN=60;
int n,a[MAXN],dp[MAXN][MAXN][MAXN][MAXN];

int main() {
	scanf("%d",&n);
	for(ri i=1;i<=n;i++){
		scanf("%d",&a[i]);
		for(ri l=1;l<=a[i];l++){
			for(ri r=a[i];r<=50;r++){
				dp[i][i][l][r]=1;
			}
		}
	}
	
	for(ri len=2;len<=n;len++){
		for(ri i=1;i+len-1<=n;i++){
			int j=i+len-1;
			for(ri Len=2;Len<=50;Len++){
				for(ri L=1;L+Len-1<=50;L++){
					int R=L+Len-1;
					dp[i][j][L][R]=max(dp[i][j][L+1][R],dp[i][j][L][R-1]);
					dp[i][j][L][R]=max(dp[i][j][L][R],dp[i+1][j][L][R]+(a[i]==L));
					dp[i][j][L][R]=max(dp[i][j][L][R],dp[i][j-1][L][R]+(a[j]==R));
					dp[i][j][L][R]=max(dp[i][j][L][R],dp[i+1][j-1][L][R]+(a[i]==R)+(a[j]==L));
				}
			}
		}
	}
	printf("%d",dp[1][n][1][50]);
	return 0;
}
```

---

## 作者：打程序的咸鱼 (赞：1)

## 前言

希望审核能给我过了这篇题解 。

## 题目

[题目传送门](https://www.luogu.com.cn/problem/P3607)

## 正文

很巧妙的思维题啊 ， 一开始丝毫没有思路 ， 瞟了一眼题解 ， 看到一句话 ： 交换一个序列相当于不相交的交换几个元素 ， 因为这几个元素交换之后就相当于是交换了一个子序列 。

有了这句话的提示 ， 问题就迎刃而解了 ， 关键要做到交换的元素不能相交 ， 其实只需要 DP 的顺序没问题即可 ， 那么显然假设  [L,R] 已经解决了 ， 那么交换的元素就强制只能在 [L,R] 之外 。
下面正式开始 DP ， 定义  $dp_{l,r,i,j}$  表示区间 [l,r] 间 ，  值域在 [i,j] 间的最长上升子序列的长度 ， 那么就转移就是交换和不交换的区别 。

不交换的转移 :

$dp_{l,r,i,j}=\max(dp_{l+1,r,i,j}+(a_{l}==i),dp_{l,r-1,i,j}+(a_{r} == j))$

交换的转移 :

$dp_{l,r,i,j}=\max(dp_{l,r,i,j},dp_{l+1,r-1,i,j}+(a_{l}==j)+(a_{r} == i))$

注意值域是可以向两边扩展的 。
## AC code :

```cpp
#include <bits/stdc++.h>
#define LL long long
using namespace std;
int read() {
	int s = 0, f = 1;
	char a = getchar();
	while(a < '0' || a > '9') {
		if(a == '-') f = -1;
		a = getchar();
	}
	while(a <= '9' && a >= '0') s = s * 10 + a - '0', a = getchar();
	return s * f;
}
LL dp[55][55][55][55],n,m,a[55],p;
int main() {
	n=read();
	for(int i=1; i<=n; i++) {
		a[i]=read();
	}
	for(int i=1;i<=n;i++) {
		for(int j=1;j<=a[i];j++) {
			for(int k=a[i];k<=50;k++) {
				dp[i][i][j][k]=1;
			}
		}
	}
	for(int len=2;len<=n;len++) {
		for(int l=1;l<=n;l++) {
			int r=l+len-1; if(r>n) break;
			for(int i=1;i<=50;i++) {
				for(int j=i;j<=50;j++) {
					dp[l][r][i][j]=max(dp[l][r][i][j],max(dp[l+1][r][i][j]+(a[l]==i),dp[l][r-1][i][j]+(a[r]==j)));
					dp[l][r][i][j]=max(dp[l][r][i][j],dp[l+1][r-1][i][j]+(a[r]==i)+(a[l]==j));
					dp[l][r][i][j+1]=max(dp[l][r][i][j+1],dp[l][r][i][j]);
					dp[l][r][i-1][j]=max(dp[l][r][i-1][j],dp[l][r][i][j]);
				}
			}
			for(int i=1;i<=50;i++) {
				for(int j=i;j>=1;j--) {
					dp[l][r][j-1][i]=max(dp[l][r][j-1][i],dp[l][r][j][i]);
				}
			}
		}
	}
	printf("%lld",dp[1][n][1][50]);
}
```
### 最后希望这篇题解能帮到屏幕前的你 ， 但是不要抄袭哦 ！

---

## 作者：xuantianhao (赞：0)

# [Subsequence Reversal P](https://www.luogu.com.cn/problem/P3607)

思路：

发现，翻转一个子序列，就意味着两两互换子序列里面的东西。

于是我们就可以设 $f[l][r][L][R]$ 表示： $\max[1,l)=L,\min(r,n]=R$ 时的最长长度。

则边界为： $L>R$ 时， $f=-\infty$；否则，如果 $l>r,f=0$。

然后开始转移。

1、不选。

$f[l+1][r][L][R]$ 和 $f[l][r-1][L][R]$。

2、选一个。

$\bullet$ 当 $a_l\geq L$ 时，$f[l+1][r][a_l][R]+1$。

$\bullet$ 当 $a_r\leq R$ 时，$f[l][r-1][L][a_r]+1$。

3、翻转，必须有 $l<r$。

$\bullet$ 当 $a_r\geq L$ 时，$f[l+1][r-1][a_r][R]+1$。

$\bullet$ 当 $a_l\leq R$ 时，$f[l+1][r-1][L][a_l]+1$。

$\bullet$ 当 $a_r\geq L$ 且 $a_l\leq R$ 时，$f[l+1][r-1][a_r][a_l]+2$。

最终答案为 $f[1][n][0][\infty]$，其中 $\infty=50$ 足矣。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int INF=0x80808080;
const int N=60;
int n;
int f[N][N][N][N],a[N];
int solve(int l,int r,int L,int R){
    if(L>R) return INF;
    if(l>r) return 0;
    if(f[l][r][L][R]!=-1) return f[l][r][L][R];
    int &res=f[l][r][L][R];
	res=0;
    res=max(res,solve(l+1,r,L,R));
    res=max(res,solve(l,r-1,L,R));
    if(a[l]>=L) res=max(res,solve(l+1,r,a[l],R)+1);
    if(a[r]>=L&&l!=r) res=max(res,solve(l+1,r-1,a[r],R)+1);
    if(a[r]<=R) res=max(res,solve(l,r-1,L,a[r])+1);
    if(a[l]<=R&&l!=r) res=max(res,solve(l+1,r-1,L,a[l])+1);
    if(a[l]<=R&&a[r]>=L&&l!=r) res=max(res,solve(l+1,r-1,a[r],a[l])+2);
//  printf("(%d,%d):(%d,%d):%d\n",l,r,L,R,res);
    return res;
}
int main(){
    scanf("%d",&n);
	memset(f,-1,sizeof(f));
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    printf("%d\n",solve(1,n,0,50));
    return 0;
}
```

---

## 作者：Coros_Trusds (赞：0)

# 题目大意

给定一个长度为 $n$ 的序列 $\{a_i\}$，可以选择一个子序列将其反转，求能获得的最大不下降子序列。

$1\le n,a_i\le 50$。

# 题目分析

注意到我们翻转一个子序列，相当于交换一些数的顺序，并且这些交换的数是 **互相嵌套的**，换句话说，他们构成的区间的交点不会在顶点处。比如这样：

```plain
----------------
 -----------
  --------
     ---
      -
```

而不会出现：

```plain
-------------
 ----------
   -------------
  --
```

然后很显然，这就是一个区间 $\verb!dp!$。

令 $dp[l,r,i,j]$ 表示区间 $[l,r]$ 的值域在 $[i,j]$ 间的最长不下降子序列的最大长度。

然后枚举区间长度和左端点，如果不交换则有：

$$dp[l,r,i,j]=\max\{dp[l+1,r,i,j]+[a_l=i],dp[l,r-1,i,j]+[a_r=j]\}$$

若交换：

$$d[l,r,i,j]=\max\{dp[l+1,r-1,i,j]+[a_l=j]+[a_r=i]\}$$

然后转移的时候注意一下边界条件。

# 代码

```cpp
// Problem: P3607 [USACO17JAN]Subsequence Reversal P
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P3607
// Memory Limit: 125 MB
// Time Limit: 1000 ms
// Date:2022-06-26 17:09
//
// Powered by CP Editor (https://cpeditor.org)

#include <iostream>
#include <cstdio>
#include <climits>//need "INT_MAX","INT_MIN"
#include <cstring>//need "memset"
#include <numeric>
#include <algorithm>
#include <cmath>
#define int long long
#define enter putchar(10)
#define debug(c,que) std::cerr << #c << " = " << c << que
#define cek(c) puts(c)
#define blow(arr,st,ed,w) for(register int i = (st);i <= (ed); ++ i) std::cout << arr[i] << w;
#define speed_up() std::ios::sync_with_stdio(false),std::cin.tie(0),std::cout.tie(0)
#define mst(a,k) memset(a,k,sizeof(a))
#define stop return(0)
const int mod = 1e9 + 7;
inline int MOD(int x) {
	if (x < 0) x += mod;
	return x % mod;
}
namespace Newstd {
	char buf[1 << 21], *p1 = buf, *p2 = buf;
	inline int getc() {
		return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1 ++;
	}
#ifndef ONLINE_JUDGE
#define getc getchar
#endif
	inline int read() {
		int ret = 0, f = 0;
		char ch = getc();
		while (!isdigit(ch)) {
			if (ch == '-') f = 1;
			ch = getc();
		}
		while (isdigit(ch)) {
			ret = (ret << 3) + (ret << 1) + ch - 48;
			ch = getc();
		}
		return f ? -ret : ret;
	}
	inline double double_read() {
		long long ret = 0, w = 1, aft = 0, dot = 0, num = 0;
		char ch = getc();
		while (!isdigit(ch)) {
			if (ch == '-') w = -1;
			ch = getc();
		}
		while (isdigit(ch) || ch == '.') {
			if (ch == '.') {
				dot = 1;
			} else if (dot == 0) {
				ret = (ret << 3) + (ret << 1) + ch - 48;
			} else {
				aft = (aft << 3) + (aft << 1) + ch - '0';
				num ++;
			}
			ch = getc();
		}
		return (pow(0.1, num) * aft + ret) * w;
	}
	inline void write(int x) {
		if (x < 0) {
			putchar('-');
			x = -x;
		}
		if (x > 9) write(x / 10);
		putchar(x % 10 + '0');
	}
}
using namespace Newstd;

const int N = 55;
int a[N], dp[N][N][N][N];
//dp[r][l][i][j]:区间 [l,r] 的值域在 [i,j] 间的最长不下降子序列的最大长度
int n;
int32_t main(void) {
	n = read();
	for (register int i = 1; i <= n; ++ i) a[i] = read();
	for (register int i = 1; i <= n; ++ i) {
		for (register int j = 1; j <= a[i]; ++ j) {
			for (register int k = a[i]; k <= 50; ++ k) {
				dp[i][i][j][k] = 1;
			}
		}
	}
	for (register int len = 2; len <= n; ++ len) {
		for (register int l = 1; l + len - 1 <= n; ++ l) {
			int r = l + len - 1;
			for (register int i = 1; i <= 50; ++ i) {
				for (register int j = i; j <= 50; ++ j) {
					dp[l][r][i][j] = std::max(dp[l][r][i][j], std::max(dp[l + 1][r][i][j] + (a[l] == i), dp[l][r - 1][i][j] + (a[r] == j)));
					dp[l][r][i][j] = std::max(dp[l][r][i][j], dp[l + 1][r - 1][i][j] + (a[r] == i) + (a[l] == j));
					dp[l][r][i][j + 1] = std::max(dp[l][r][i][j + 1], dp[l][r][i][j]);
					dp[l][r][i - 1][j] = std::max(dp[l][r][i - 1][j], dp[l][r][i][j]);
				}
			}
			for (register int i = 1; i <= 50; ++ i) {
				for (register int j = i;j >= 1; -- j) {
					dp[l][r][j - 1][i] = std::max(dp[l][r][j - 1][i], dp[l][r][j][i]);
				}
			}
		}
	}
	printf("%lld\n", dp[1][n][1][50]);

	return 0;
}
```

---

## 作者：_slb (赞：0)

## Description

给定一个长度为 $n$ 的序列 $\{a_i\}$，可以选择一个子序列将其反转，求能获得的最大不下降子序列。

$n\leq 50$。

## Solution

观察一下反转的性质，实际上就相当于将这个子序列两边对调，且不会有交错和并列，与区间 DP 能很好地搭配——选择反转两个数，他们之间的区间可以接着反转。

那么考虑 $f_{i,j}$ 表示区间 $[i,j]$ 的答案，其中只考虑是否反转 $a_i,a_j$。

考虑如何由小区间得到大区间的解，回忆 LIS 的 $O(n^2)$ 做法，与值有关，那么再加两维状态：$f_{i,j,l,r}$ 表示区间 $[i,j]$，值域 $[l,r]$ 的答案。

那么就可以方便的转移了。

首先，大值域显然可以由小值域得来，即 $f_{i,j,l,r}=\max(f_{i,j,l+1,r},f_{i,j,l,r-1})$。

为表述方便，记 $[\text{bool}]=\begin{cases}1&\text{if bool = TRUE}\\0&\text{if bool = FALSE}\end{cases}$。

当不反转 $a_i,a_j$ 时，$f_{i,j,l,r}=\max(f_{i+1,j,l,r}+[a_i=l],f_{i,j-1,l,r}+[a_j=r])$。

当反转 $a_i,a_j$ 时，$f_{i,j,l,r}=f_{i+1,j-1,l,r}+[a_i=l]+[a_j=r]$。

把上面的方程都取个 $\text{max}$，就得到这个状态的答案了。

初始状态就把区间长度为 $1$ 的合法状态都设成 $1$ 即可。

一开始把不相等的情况也考虑进去了，后来发现是错的：不相等的情况在值域扩张的时候会被考虑到，没必要再进行讨论。（其实把细节稍微改一下也能做）

## Code
```cpp
#include <algorithm>
#include <cstdio>
#include <iostream>

const int maxn = 55;

int a[maxn], b[maxn];
int f[maxn][maxn][maxn][maxn];

int n;

inline void upd_max(int &a, int b) { a = std::max(a, b); }
inline int change(bool x) { return x ? 1 : 0; }

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]), b[i] = a[i];
    
    std::sort(b + 1, b + 1 + n);
    int tot = std::unique(b + 1, b + 1 + n) - b - 1;
    for (int i = 1; i <= n; i++)
        a[i] = std::lower_bound(b + 1, b + 1 + tot, a[i]) - b;
    // 其实没必要离散化。
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= a[i]; j++)
            for (int k = a[i]; k <= tot; k++)
                f[i][i][j][k] = 1;
    // DP的顺序需要考虑一下
    for (int len = 2; len <= n; len++)
    {
        for (int i = 1; i <= n; i++)
        {
            int j = i + len - 1;
            if (j > n)
                continue;
            for (int len2 = 1; len2 <= tot; len2++)
            {
                for (int l = 1; l <= tot; l++)
                {
                    int r = l + len2 - 1;
                    if (r > tot)
                        continue;
                    if (l != tot)
                        upd_max(f[i][j][l][r], f[i][j][l + 1][r]);
                    upd_max(f[i][j][l][r], f[i][j][l][r - 1]);
                    upd_max(f[i][j][l][r], f[i + 1][j][l][r] + change(a[i] == l));
                    upd_max(f[i][j][l][r], f[i][j - 1][l][r] + change(a[j] == r));
                    upd_max(f[i][j][l][r], f[i + 1][j - 1][l][r] + change(a[i] == r) + change(a[j] == l));
                }
            }
        }
    }
    printf("%d\n", f[1][n][1][tot]);
}
```



---

## 作者：raincity (赞：0)

[更好的阅读体验](https://blog.calvincheng1231.org.cn/sols/256.html)

## 分析
很神奇的 DP 题。

这道题比较难的地方在于处理序列反转。

有一个关键的想法：序列反转不好记录，但是可以看做很多次交换数的位置。

也就是说，翻转子序列 $a_{i_1},a_{i_2},\ldots a_{i_k}$ 等价于交换 $a_{i_1}$ 和 $a_{i_k}$，$a_{i_2}$ 和 $a_{i_{k-1}}$ 等等。不需要考虑多了一个的情况，因为这个数根本就不会改变位置，把它从 $i$ 中去掉就好。很可能是一个区间 DP。

需要快速判断一个数能否作贡献，而且值域也只有 50，状态里面可以考虑带值域。

所以，基本上可以设出状态：设 $dp_{l,r,L,R}$ 为原序列中 $l$ 到 $r$ 的区间里，所有值为 $L$ 到 $R$ 的数经过翻转后可以组成的最长 LIS 长度。

考虑如何转移。

首先，$a_l$ 和 $a_r$ 可能不在 $[L,R]$ 中，所以要通过 $dp_{l,r,L+1,R}$ 和 $dp_{l,r,L,R-1}$ 转移。

**update:** 少写了一个“不”字，可能造成了一些困扰。

其次考虑不交换 $a_l$ 和 $a_r$ 位置的情况下，$a_l$ 作的贡献。不被包括在第一种情况的只有 $a_l=L$ 且算入 LIS 的情况。从 $dp_{l+1,r,L,R}+[a_l=L]$ 转移。同理要从 $dp_{l,r-1,L,R}+[a_r=R]$ 转移。

最后考虑交换 $a_l$ 和 $a_r$ 的情况。不被包括在第一种情况的只有 $a_l=R$ 或者 $a_r=L$ 的情况。从 $dp_{l+1,r-1,L,R}+[a_l=R]+[a_r=L]$ 转移。

答案是 $dp_{1,n,1,50}$。

## 解决
```cpp
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

const int N = 55;
int n, a[N], dp[N][N][N][N];

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        for (int L = 1; L <= a[i]; L++)
            for (int R = a[i]; R <= 50; R++)
                dp[i][i][L][R] = 1;
    }
    for (int l1 = 2; l1 <= n; l1++)
        for (int l = 1, r = l1; r <= n; l++, r++)
            for (int l2 = 1; l2 <= 50; l2++)
                for (int L = 1, R = l2; R <= 50; L++, R++)
                {
                    dp[l][r][L][R] = max(dp[l][r][L + 1][R], dp[l][r][L][R - 1]);
                    dp[l][r][L][R] = max(dp[l][r][L][R], dp[l + 1][r][L][R] + (a[l] == L));
                    dp[l][r][L][R] = max(dp[l][r][L][R], dp[l][r - 1][L][R] + (a[r] == R));
                    dp[l][r][L][R] =
                        max(dp[l][r][L][R], dp[l + 1][r - 1][L][R] + (a[l] == R) + (a[r] == L));
                }
    cout << dp[1][n][1][50] << endl;
    return 0;
}
```

---

## 作者：ddd (赞：0)

设 $dp[l][r][k][m]$ 为： 区间 $[l,r]$ 在 $[1,l-1]$ 的最大值为 $k$, $[r+1,n]$ 的最小值为 $m$ 的情况下对答案的贡献，转移见代码。


```cpp
#include <cstdio>

const int MAXN = 55;

inline void chkmax(int &a, int b) {
  if(b > a) a = b;
}

int a[MAXN], dp[MAXN][MAXN][MAXN][MAXN], vis[MAXN][MAXN][MAXN][MAXN];

int solve(int i, int j, int k, int m) {
  if(vis[i][j][k][m]) return dp[i][j][k][m];
  if(k > m) return -1e8;
  if(i > j) return 0;
  if(i == j) {
    if(a[i] >= k && a[j] <= m) return 1;
    return 0;
  }
  int ans = 0;
  //1. 交换 a[i], a[j]
  chkmax(ans, solve(i + 1, j - 1, k, m));
  if(a[j] >= k) chkmax(ans, solve(i + 1, j - 1, a[j], m) + 1);
  if(a[i] <= m) chkmax(ans, solve(i + 1, j - 1, k, a[i]) + 1);
  if(a[j] >= k && a[i] <= m) chkmax(ans, solve(i + 1, j - 1, a[j], a[i]) + 2);
  //2. 不交换
  //(1) [i + 1, j]
  chkmax(ans, solve(i + 1, j, k, m));
  if(a[i] >= k) chkmax(ans, solve(i + 1, j, a[i], m) + 1);
  //(2) [i, j - 1]
  chkmax(ans, solve(i, j - 1, k, m));
  if(a[j] <= m) chkmax(ans, solve(i, j - 1, k, a[j]) + 1);
  return vis[i][j][k][m] = 1, dp[i][j][k][m] = ans;
}
int main() {
  int n; scanf("%d", &n);
  for(int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
  }
  printf("%d\n", solve(1, n, 0, 50));
  return 0;
}
```

---

