# [USACO13MAR] The Cow Run G/S

## 题目描述

Farmer John has forgotten to repair a hole in the fence on his farm, and his N cows (1 <= N <= 1,000) have escaped and gone on a rampage! Each minute a cow is outside the fence, she causes one dollar worth of damage. FJ must visit each cow to install a halter that will calm the cow and stop the damage.

Fortunately, the cows are positioned at distinct locations along a straight line on a road outside the farm. FJ knows the location P\_i of each cow i (-500,000 <= P\_i <= 500,000, P\_i != 0) relative to the gate (position 0) where FJ starts.

FJ moves at one unit of distance per minute and can install a halter instantly. Please determine the order that FJ should visit the cows so he can minimize the total cost of the damage; you should compute the minimum total damage cost in this case.

农夫约翰的牧场围栏上出现了一个洞，有 $N$（$1\le N\le 1000$）只牛从这个洞逃出了牧场。这些出逃的奶牛很狂躁，他们在外面到处搞破坏，每分钟每头牛都会给约翰带来 $1$ 美元的损失。约翰必须用缰绳套住所有的牛，以停止他们搞破坏。

幸运的是，奶牛们都在牧场外一条笔直的公路上，牧场的大门恰好位于公里的 $0$ 点处。约翰知道每头牛距离牧场大门的距离 $P_i$（$-5\times10^5\le P_i\le5\times 10^5$，$P_i\ne0$）。

约翰从农场大门出发，每分钟移动一个单位距离，每到一头牛所在的地点，约翰就会给它套上缰绳，套缰绳不花时间。按怎样的顺序去给牛套缰绳才能使约翰损失的费用最少？

## 说明/提示

Four cows placed in positions: -2, -12, 3, and 7.


The optimal visit order is -2, 3, 7, -12. FJ arrives at position -2 in 2 minutes for a total of 2 dollars in damage for that cow.

He then travels to position 3 (distance: 5) where the cumulative damage is 2 + 5 = 7 dollars for that cow.

He spends 4 more minutes to get to 7 at a cost of 7 + 4 = 11 dollars for that cow.

Finally, he spends 19 minutes to go to -12 with a cost of 11 + 19 = 30 dollars.

The total damage is 2 + 7 + 11 + 30 = 50 dollars. 



## 样例 #1

### 输入

```
4 
-2 
-12 
3 
7 
```

### 输出

```
50 
```

# 题解

## 作者：ysj1173886760 (赞：24)

简单的区间dp

可以先做关路灯，在做这道题，双倍经验。

dp[i][j][0/1]表示当前已经套完了i到j的牛，然后 第三维表示在左边还是在右边。

那么对于每次处理完区间i~j,我们如何递推出别的状态呢？

我们下一步可以选择去i-1，也就是下一步到dp[i-1][j],


或者选择去j+1,到dp[i][j+1]。

对于每一个当前的状态，fj可能在左边或者右边，也就是dp[i][j][1]或者dp[i][j][0],每一个又有两种转移方案。

两种状态一起处理就好。

我把n个点拆成了n+1个点，找到0点，设为c，令dp[c][c][0]=dp[c][c][1]=0,其他的都为inf， 两重循环转移即可，复杂度O(n^2)

主要是代码比较简洁，无压行30行，所以我想发这个题解。qaq

```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;

const int maxn=1e3+10;

int n;
int pos[maxn],dp[maxn][maxn][2];

int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)cin>>pos[i];				//读入 
	sort(pos+1,pos+1+n);							//排个序 
	int c=lower_bound(pos+1,pos+1+n,0)-pos;			//找到0点 
	memset(dp,0x3f,sizeof(dp));						//初始化极大值 
	for(int i=n;i>=c;i--)pos[i+1]=pos[i];			//把零点以后的向右移一位，注意逆序 ，类比背包滚动数组。 
	pos[c]=0;	
	dp[c][c][0]=dp[c][c][1]=0;						//初始化起点 
	for(int l=2;l<=n+1;l++)							//开始区间dp，枚举区间长度 
		for(int i=1;i+l-1<=n+1;i++)					//枚举左端点 
		{
			int j=i+l-1;							//计算右端点 
			dp[i][j][0]=min(dp[i+1][j][0]+(pos[i+1]-pos[i])*(n-j+i+1),dp[i+1][j][1]+(pos[j]-pos[i])*(n-j+i+1));//n-j+i+1为区间大小，也就是牛的个数. 
			dp[i][j][1]=min(dp[i][j-1][1]+(pos[j]-pos[j-1])*(n-j+i+1),dp[i][j-1][0]+(pos[j]-pos[i])*(n-j+i+1));
		}
	cout<<min(dp[1][n+1][1],dp[1][n+1][0]);			//最终可能在左边或者右边. 
	return 0;
}
```

---

## 作者：喵仔牛奶 (赞：11)

区间 dp。

设 $f_{i,j,0}$ 是捕捉了 $[i,j]$ 的牛站在左端点的最少的已花费，$f_{i,j,1}$ 是捕捉了 $[i,j]$ 的牛站在右端点的最少的已花费。

为什么一定是区间捕牛？因为这片区间是走过了，~~牛不捕白不捕~~。

转移方程如下：

$$f_{i,j,0}=\min\{f_{i+1,j,0}+(d_{i+1}-d_{i})\times(c_{1,n}-c_{i+1,j}),f_{i+1,j,1}+(d_{j}-d_{i})\times(c_{i,n}-c_{i+1,j})$$

$$f_{i,j,1}=\min\{f_{i,j-1,0}+(d_{j}-d_{i})\times(c_{1,n}-c_{i,j-1}),f_{i,j-1,1}+(d_{j}-d_{j-1})\times(c_{i,n}-c_{i,j-1})$$

$c_{i,j}$ 为 $[i,j]$ 的奶牛个数，也就是 $j-i+1$

要排序。不然无序的不能区间 dp。

然而，初始又在哪个端点呢？只要在端点中插入一个位置为 $0$ 的端点，排序后二分即可。

答案是 $\min\{f_{1,n,0},f_{1,n,1}\}$。

代码实现如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 3005;
int f[N][N][2], a[N], d[N], sum[N], n, c;
int main() {
    cin >> n;
    for (int i = 1; i <= n; i ++)
        cin >> d[i];
    d[++ n] = 0, sort(d + 1, d + 1 + n);
    memset(f, 0x3f, sizeof f);
    c = lower_bound(d + 1, d + 1 + n, 0) - d;
    f[c][c][1] = f[c][c][0] = 0;
    for (int k = 2; k <= n; k ++)
        for (int i = 1; i <= n; i ++) {
            int j = i + k - 1;
            f[i][j][0] = min(f[i + 1][j][0] + (d[i + 1] - d[i]) * (i + n - j),
                             f[i + 1][j][1] + (d[j] - d[i]) * (i + n - j));
            f[i][j][1] = min(f[i][j - 1][0] + (d[j] - d[i]) * (i + n - j),
                             f[i][j - 1][1] + (d[j] - d[j - 1]) * (i + n - j));
        }
    cout << min(f[1][n][0], f[1][n][1]) << '\n';
    return 0;
}

```


---

## 作者：qzcbw (赞：4)

## 题面
[题面传送门](https://www.luogu.com.cn/problem/P3080)

---
## 题目分析
#### 分析
这是一道区间dp题。
这道题和[P1220 关路灯](https://www.luogu.com.cn/problem/P1220)特别相似，因为他们的状态转移方程都类似于
$$f[l][r][0]=min( f[ l+1 ][ r ][ 0 ] +改变量 , f[ l+1 ][ r ][ 1 ] +改变量）$$
$$f[l][r][1]=min( f[ l ][ r-1 ][ 0 ] +改变量 , f[ l ][ r-1 ][ 1 ] +改变量）$$
$f[i][j][0]$和$f[i][j][1]$表示当前已经套完了$i$到$j$的牛，然后用第三维表示在左边还是在右边。

我们把$n$个点拆成$n+1$个点，找到$0$点，设为$c$，令$f[c][c][0]=f[c][c][1]=0$,其他的都为$0x3f$。

我们下一步可以选择去$i-1$，也就是下一步到$f[i-1][j]$,或者选择去$j+1$,到$f[i][j+1]$。
对于每一个当前的状态，$a[j]$可能在左边或者右边，也就是$f[i][j][1]$或者$f[i][j][0]$,每一个又有两种转移方案，于是我们可以把两个状态一起两重~~暴力~~进行转移。

其中$$破坏量=距离*未套住的数量$$
#### 复杂度
复杂度为$O(n^2)$。

---
## 代码
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>			//养成好习惯，不用万能头
#define maxn 1039
using namespace std;
int n,f[maxn][maxn][2],a[maxn],c=0;
//inline int max(int x,int y){return x>y?x:y;}
inline int min(int x,int y){return x<y?x:y;}			//养成好习惯，手写min函数
inline int js(int x,int y,int l,int r){return (a[y]-a[x])*(n-r+l);}			//计算破坏量
int main(){
 	memset(f,0x3f,sizeof(f));
	register int i,j;
 	scanf("%d",&n);
 	for(i=1;i<=n;i++)  
		scanf("%d",a+i); 
	n++;	
	a[n]=0;			//把0塞在数组的最末端
	sort(a+1,a+n+1);			//排序
	for(i=1;i<=n;i++)			//找到0点
		if(!a[i]) c=i;
 	f[c][c][0]=f[c][c][1]=0; 
	for(j=c;j<=n;j++)			//区间dp
    	for(i=j-1;i>=1;i--){
    		f[i][j][0]=min(f[i+1][j][0]+js(i,i+1,i,j),f[i+1][j][1]+js(i,j,i,j));//套刚才推出的状态转移方程
    		f[i][j][1]=min(f[i][j-1][0]+js(i,j,i-1,j-1),f[i][j-1][1]+js(j-1,j,i-1,j-1));
		}
    printf("%d",min(f[1][n][0],f[1][n][1]));
    return 0;			//完美撒花
}
```
---


---

## 作者：HS_xh (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/P3080)
 
 区间DP
 
设 $F_{i,j,0}$ 为 $[i,j]$ 的牛左端的区间最小花费， $F_{i,j,1}$ 为 $[i,j]$ 的牛右端的区间最小花费。

接着再找到原点 $O$ ，设为 $b$ 点，将 $F_{b,b,0}$ 和 $F_{b,b,1}$ 设为 $0$，其余为极大值（`0x3f`）。

接来下是动态转移方程:
$$f_{i,j,0}=\min(f_{i+1,j,0}+(in_{i+1}-in_{i})\times(n+i-j),f_{i+1,j,1}+(in_{j}-in_{i})\times(n+i-j))$$

$$f_{i,j,1}=\min(f_{i,j-1,1}+(in_j-in_{j-1})\times(n+i-j),f_{i,j-1,0}+(in_j-in_i)\times(n+i-j))$$

最后取结果要再次求最小值，求左端和右端的最小值即为结果。

详见代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int in[2001],b,n;
int f[2001][2001][2];
int main()
{
	memset(f,0x3f,sizeof(f));
	cin>>n;
	for(int i=1;i<=n;++i)
		cin>>in[i];
	in[++n]=0;//标记原点 
	sort(in+1,in+n+1);
	for(int i=1;i<=n;++i)
		if(in[i]==0) b=i;//找原点 
		f[b][b][0]=f[b][b][1]=0;
	for(int j=b;j<=n;j++)
	   for(int i=j-1;i>=1;i--)
	   {
		  f[i][j][0]=min(f[i+1][j][0]+(in[i+1]-in[i])*(n+i-j),f[i+1][j][1]+(in[j]-in[i])*(n+i-j));
		  f[i][j][1]=min(f[i][j-1][1]+(in[j]-in[j-1])*(n+i-j),f[i][j-1][0]+(in[j]-in[i])*(n+i-j));
	   }
	cout<<min(f[1][n][0],f[1][n][1]);
}
```


---

## 作者：Ryo_Yamada (赞：3)

本题贪心可以获得 71pts 的好成绩。

即每次考虑选择离现在最近的点，计算贡献。这样是 56pts。然而贪心显然有个缺陷：当左右两个最近的点距离相等时，我们无法得知向哪边走是最优的。而在此基础上加上判断开始时向左还是向右可以获得 71pts。

考虑 dp，发现选择的点一定是在将点排序后的一个区间。如果选择的点的区间有多个，中两个区间夹住的中间的点一定被经过了。

将小于 $0$ 的点存入数组 $l$，从大到小排序，大于 $0$ 的点存入数组 $r$，从小到大排序，设 $dp_{i,j,0/1}$ 为一共选择了 $i$ 个点，选择了 $<0$ 的前 $j$ 个点，并且选择的最后一个点是 $<0 / >0$ 的。转移即为

$$dp_{i,j,0} = \min(dp_{i-1,j-1,0} + (n-i+1) \times (l_{j-1} - l_j),\, dp_{i-1,j-1,1}+(n-i+1)\times (r_{i-j}-l_j))$$

$$dp_{i,j,1} = \min(dp_{i-1,j,0} + (n-i+1)\times (r_{i-j}-l_j),\, dp_{i-1,j,1}+(n-i+1)\times (r_{i-j}-r_{i-j-1}))$$

记得判转移边界 $dp_{i,j,0} \rightarrow j>0$，$dp_{i,j,1} \rightarrow i-j>0$。

$\text{Code}$：

```cpp
def(N, int, 1005)

int n;
int lf[N], rh[N];
int t0, t1;
int ps[N];
int dp[N][N][2];

int main() {
	qread(n);
	rep(i, 1, n) qread(ps[i]);
	sort(ps + 1, ps + n + 1);
	int st;
	rep(i, 1, n + 1) if(ps[i] >= 0) {
		st = i - 1;
		break;
	}
	per(i, st, 1) lf[++t0] = ps[i];
	rep(i, st + 1, n) rh[++t1] = ps[i];
	memset(dp, 0x3f, sizeof dp);
	dp[0][0][0] = dp[0][0][1] = 0;
	rep(i, 1, n) rep(j, 0, min(i, t0)) {
		if(i - j > t1) continue;
		
		if(j) dp[i][j][0] = min(dp[i - 1][j - 1][0] + (n - i + 1) * (lf[j - 1] - lf[j]), dp[i - 1][j - 1][1] + (n - i + 1) * (rh[i - j] - lf[j])); 
		if(i - j) dp[i][j][1] = min(dp[i - 1][j][0] + (n - i + 1) * (rh[i - j] - lf[j]), dp[i - 1][j][1] + (n - i + 1) * (rh[i - j] - rh[i - j - 1]));
	}
	cout << min(dp[n][t0][0], dp[n][t0][1]) << endl;
	return 0;
}
```


---

## 作者：回青绝影 (赞：2)

发一篇题解：

首先，[关路灯](https://www.luogu.com.cn/problem/P1220)和这道题很像，只是这道题细节更多一点，与关路灯一样，这是一道区间DP，而且连转移方程都一模一样。

---
因为套牛不需要时间，所以一定是走过去就套了于是：

规定$f[i][j][0/1]$为套完从第$i$头牛到第$j$头牛站在其左/右端点的最少时间花费。

于是得到：

$dp[l][r][0]=min(dp[l+1][r][0]+c1,dp[l+1][r][1]+c2)$

$dp[l][r][1]=min(dp[l][r-1][0]+c3,dp[l][r-1][1]+c4)$

$c=$距离*未套住的数量

代码：
```cpp
#include<bits/stdc++.h>
const int N=1e3+1;
using namespace std;
int n,c=0,a[N],cn[N],f[N][N][2];
int calc(int x,int y,int l,int r){return (a[y]-a[x])*(n-r+l);}
int main(){
    scanf("%d",&n);
    for (int i=1;i<=n;i++) scanf("%d",&a[i]);a[++n]=0;sort(a+1,a+1+n);for (int i=1;i<=n;i++) if (!a[i]) c=i;
    memset(f,0x3f,sizeof(f));f[c][c][0]=f[c][c][1]=0;
    for (int j=c;j<=n;j++)
        for (int i=j-1;i>0;i--){
            f[i][j][0]=min(f[i+1][j][0]+calc(i,i+1,i,j),f[i+1][j][1]+calc(i,j,i,j));
            f[i][j][1]=min(f[i][j-1][0]+calc(i,j,i-1,j-1),f[i][j-1][1]+calc(j-1,j,i-1,j-1));
        }
    printf("%d",min(f[1][n][0],f[1][n][1]));
    return 0;
}
```


---

## 作者：jiangtaizhe001 (赞：2)

[在CSDN上查看](https://blog.csdn.net/jiangtaizhe/article/details/107446755)  
[题目传送门](https://www.luogu.com.cn/problem/P3080)  

附原题：
#### 题目描述
Farmer John has forgotten to repair a hole in the fence on his farm, and his N cows (1 <= N <= 1,000) have escaped and gone on a rampage! Each minute a cow is outside the fence, she causes one dollar worth of damage. FJ must visit each cow to install a halter that will calm the cow and stop the damage.  

Fortunately, the cows are positioned at distinct locations along a straight line on a road outside the farm. FJ knows the location P_i of each cow i (-500,000 <= P_i <= 500,000, P_i != 0) relative to the gate (position 0) where FJ starts.

FJ moves at one unit of distance per minute and can install a halter instantly. Please determine the order that FJ should visit the cows so he can minimize the total cost of the damage; you should compute the minimum total damage cost in this case.

农夫约翰的牧场围栏上出现了一个洞，有N(1 <= N <= 1,000)只牛从这个洞逃出了牧场。这些出逃的奶牛很狂躁，他们在外面到处搞破坏，每分钟每头牛都会给约翰带来1美元的损失。约翰必须用缰绳套住所有的牛，以停止他们搞破坏。

幸运的是，奶牛们都在牧场外一条笔直的公路上，牧场的大门恰好位于公里的0点处。约翰知道每头牛距离牧场大门的距离P_i(-500,000 <= P_i <= 500,000, P_i != 0)

约翰从农场大门出发，每分钟移动一个单位距离，每到一头牛所在的地点，约翰就会给它套上缰绳，套缰绳不花时间。按怎样的顺序去给牛套缰绳才能使约翰损失的费用最少？

#### 输入格式
* Line 1: The number of cows, N.

* Lines 2..N+1: Line i+1 contains the integer P_i.

#### 输出格式
* Line 1: The minimum total cost of the damage.

#### 输入输出样例
###### 输入 #1
```
4 
-2 
-12 
3 
7 
```
###### 输出 #1
```
50
```
#### 说明/提示
Four cows placed in positions: -2, -12, 3, and 7.

The optimal visit order is -2, 3, 7, -12. FJ arrives at position -2 in 2 minutes for a total of 2 dollars in damage for that cow.

He then travels to position 3 (distance: 5) where the cumulative damage is 2 + 5 = 7 dollars for that cow.

He spends 4 more minutes to get to 7 at a cost of 7 + 4 = 11 dollars for that cow.

Finally, he spends 19 minutes to go to -12 with a cost of 11 + 19 = 30 dollars.

The total damage is 2 + 7 + 11 + 30 = 50 dollars.

## 题目解析
先看一眼题目，$N\leq 1000$，$O\left(N^2\right)$ 算法可以过。  
我们可以发现，这道题目可以通过贪心或者搜索的方式来做，~~于是就可以小数据搜索大数据贪心~~。  
$O\left(2^N\right)$搜索肯定不行，~~保证TLE~~，那么我们考虑贪心。  
贪心方案：向近一点的去，但是我们可以证明这是错的，我们构造一组数据如下：  
```
4
-1 2 3 4
```
贪心是沿$-1→2→3→4$的道路走，耗费为$1+4+5+6=16$  
但是存在一条$2→3→4→-1$的道路，耗费为$5+2+3+4=14$
明显贪心是错误的。  

我们发现，这道题貌似可以用贪心，也貌似可以用搜索，并且只要求我们输出答案并且不输出路径，那么这题的正解是什么呢？显然是DP。   
> 如果有一道题，可以用贪心，也可以用搜索，这么这道题目一定是DP。——FLYing

~~FLYing:我没说过~~  
~~我谔谔~~  

DP式解析：
我们采用区间DP，首先想到用区间DP，但是我们发现仅仅靠两个维度是不能完成这道题目的，我们令$f_{i,j,k}$来表示状态，$i,j$表示处理的区域的两个端点，$k$表示当前区间处理完成之后的位置，$k=0$代表在左端，$k=1$代表在右端。
  
**代码版本1.0**  
$f_{i,j,k}$可以通过$f_{i+1,j,k}\ f_{i,j-1,k}$得到
不难推出状态转移式：  
$$f_{i,j,0}=\min\left( f_{i+1,j,0}+|a_{i+1}-a_i|,f_{i+1,j,1}+|a_j-a_i|\right)$$
$$f_{i,j,0}=\min\left( f_{i,j-1,0}+|a_j-a_i|,f_{i,j-1,1}+|a_j-a_{j-1}|\right)$$
```cpp
#include<cstdio>
#include<iostream>
#include<cmath>
#include<algorithm>
using namespace std;
int n,a[1039];
int f[1039][1039][3];
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    sort(a+1,a+n+1);
    f[0][0][0]=f[0][0][1]=0;
    for(int i=n;i>=1;i--)
        for(int j=i;j<=n;j++){
            if(i==j) f[i][j][0]=f[i][j][1]=abs(a[i]);
            else {
                f[i][j][0]=min( f[i+1][j][0]+abs(a[i+1]-a[i]) , f[i+1][j][1]+abs(a[i]-a[j]) );
                f[i][j][1]=min( f[i][j-1][0]+abs(a[j]-a[i])) , f[i][j-1][1]+abs(a[j]-a[j-1]) );
            }
        }
    printf("%d",min(f[1][n][0],f[1][n][1])-1);
    return 0;
}
```
然而，样例都过不去……


**代码版本2.0**  
我们会发现1.0版本的DP式是错误的，因为我们发现，在前进的过程中，不仅仅只有一头奶牛在破坏。  
所以正确的DP式是这样的：  
$$f_{i,j,0}=\min\left( f_{i+1,j,0}+\left(n-j+i\right)\times|a_{i+1}-a_i|,f_{i+1,j,1}+\left(n-j+i\right)\times|a_j-a_i|\right)$$
$$f_{i,j,0}=\min\left( f_{i,j-1,0}+\left(n-j+i\right)\times|a_j-a_i|,f_{i,j-1,1}+\left(n-j+i\right)\times|a_j-a_{j-1}|\right)$$
~~代码就懒得贴了~~  
然而样例还是过不去……  

**代码版本3.0**  
我们发现我们忽略的起点。  
所以我们在进行排序的时候，把句子改成这样：```sort(a+1,a+n+2)```这样就可以把起点$0$算进去了，然后我们要找到起点的位置，当然，由于起点没有奶牛，所以DP式还要改一下：  
$$f_{i,j,0}=\min\left( f_{i+1,j,0}+\left(1+n-j+i\right)\times|a_{i+1}-a_i|,f_{i+1,j,1}+\left(1+n-j+i\right)\times|a_j-a_i|\right)$$  
$$f_{i,j,0}=\min\left( f_{i,j-1,0}+\left(1+n-j+i\right)\times|a_j-a_i|,f_{i,j-1,1}+\left(1+n-j+i\right)\times|a_j-a_{j-1}|\right)$$  
代码如下：  
```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<cmath>
#include<algorithm>
#define min(a,b) ((a)>(b)?(b):(a))
using namespace std;
int n,a[1039],s;
int f[1039][1039][2];
int main(){
	//freopen("1.txt","r",stdin);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	a[n+1]=0;
	sort(a+1,a+n+2);
	for(int i=1;i<=n+1;i++)
	    if(!a[i])
	        s=i;
	f[s][s][0]=f[s][s][1]=0;
	for(int i=n+1;i>=1;i--)
		for(int j=i+1;j<=n+1;j++){
			//if(i==j) f[i][j][0]=f[i][j][1]=abs(a[i]);
			//else {
				f[i][j][0]=min( f[i+1][j][0]+(a[i+1]-a[i])*(n-j+i+1) , f[i+1][j][1]+(a[j]-a[i])*(n-j+i+1) );
				f[i][j][1]=min( f[i][j-1][0]+(a[j]-a[i])*(n-j+i+1) , f[i][j-1][1]+(a[j]-a[j-1])*(n-j+i+1) );
			//}
		}
	printf("%d",min(f[1][n+1][0],f[1][n+1][1]));
	return 0;
}
```  
然而样例还是过不去……  
~~我太难了~~  
  
**代码版本4.0**  
我们发现，在DP式中有一个东西是这样的：$n-i+j+1$这个是奶牛的个数，但是，我们发现，如果$i>s$（$s$为起点），那么我们发现，这个区间是没有意义的，而且这个DP式也是错的，所以我们的```for```循环要改一下：
```cpp
for(int i=s;i>=1;i--)
		for(int j=i+1;j<=n+1;j++)
```  
为了在计算中不要调用到无意义的区间，我们还需要把数组$f$赋值成$\operatorname{INF}$，于是我们加上一句话。```memset(f,0x3f,sizeof(f));```  
然后就可以过样例了，其实也**AC**了。
献上AC代码：
```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<cmath>
#include<algorithm>
#define min(a,b) ((a)>(b)?(b):(a))
using namespace std;
int n,a[1039],s;
int f[1039][1039][2];
int main(){
	//freopen("1.txt","r",stdin);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	a[n+1]=0;
	sort(a+1,a+n+2);
	for(int i=1;i<=n+1;i++)
	    if(!a[i])
	        s=i;
	memset(f, 0x3f, sizeof(f));
	f[s][s][0]=f[s][s][1]=0;
	for(int i=s;i>=1;i--)
		for(int j=i+1;j<=n+1;j++){
			//if(i==j) f[i][j][0]=f[i][j][1]=abs(a[i]);
			//else {
				f[i][j][0]=min( f[i+1][j][0]+(a[i+1]-a[i])*(n-j+i+1) , f[i+1][j][1]+(a[j]-a[i])*(n-j+i+1) );
				f[i][j][1]=min( f[i][j-1][0]+(a[j]-a[i])*(n-j+i+1) , f[i][j-1][1]+(a[j]-a[j-1])*(n-j+i+1) );
			//}
		}
	printf("%d",min(f[1][n+1][0],f[1][n+1][1]));
	return 0;
}
```

---

## 作者：Loser_Syx (赞：1)

显然本题答案不具有最优子结构性质，你根本无法进行贪心的决策，于是只能考虑区间 dp。

发现对于一段连续的区间 $[l,r]$，最后一个捉到的点最优只能是 $l$ 或 $r$，于是就可以定义 dp 状态 $dp_{l,r,0/1}$ 为区间 $[l,r]$ 最后一个点是 $l$ 或 $r$。

那么对于 $dp_{l,r,0}$，转移只能是 $dp_{l+1,r}$ 来的。反之 $dp_{l,r,1}$ 只能是 $dp_{l,r-1}$ 转移而来。

注意抓区间 $[l,r]$ 边界的牛时未抓捕的个数为 $n-len+1$ 个。

注意需要添加原点 $0$ 和排序，不然无法进行 dp。

```cpp
int dp[1010][1010][2], a[1010];
signed main() {
	int n = read();
	for (int i = 1; i <= n; ++i) {
		read(a[i]);
	}
	a[++n] = 0;
	sort(a + 1, a + 1 + n);
	memset(dp, 0x3f, sizeof dp);
	int point_zero = -1;
	for (int i = 1; i <= n; ++i) {
		if (a[i] == 0) point_zero = i;
	}
	dp[point_zero][point_zero][0] = dp[point_zero][point_zero][1] = 0;
	for (int i = 2; i <= n; ++i) {
		for (int l = 1, r = i; r <= n; ++l, ++r) {
			dp[l][r][0] = min(dp[l + 1][r][0] + (a[l + 1] - a[l]) * (n - i + 1), dp[l + 1][r][1] + (a[r] - a[l]) * (n - i + 1));
			dp[l][r][1] = min(dp[l][r - 1][1] + (a[r] - a[r - 1]) * (n - i + 1), dp[l][r - 1][0] + (a[r] - a[l]) * (n - i + 1));
		}
	}
	write(min(dp[1][n][0], dp[1][n][1]), '\n');
	return 0;
}
```

---

## 作者：ImposterAnYu (赞：1)

这道题的 $n$ 最大只有 $1000$，所以我们可以先考虑 $O(n^2)$ 的 `dp`。

首先，我们在读入题目中的 $p_i$ 时，考虑根据 $p_i$ 的正负性将 $p_i$ 分类。如果 $p_i < 0$，则将 $p_i$ 加入 $x$ 数组；如果 $p_i \ge 0$，则将 $p_i$ 加入 $y$ 数组。于是，我们就得到了一个长度为 $s$ 的 $x$ 数组 和一个长度为 $t$ 的 $y$ 数组。

其次，为了方便处理，我们需要将 $x$ 和 $y$ 按照绝对值的大小来分别排序（$x$ 按从大到小排，$y$ 从小到大排）。因为如果不排序，我们就会在按顺序抓奶牛时先抓远的，再抓近的，这会比先抓近的，再抓远的更划不来。

排完序后，我们就可以愉快地 `dp` 啦！

设 $dp_{i,j,0/1}$ 表示 Farmer John 已经抓住了从原点往左数的前 $i$ 头牛和从原点往右数的前 $j$ 头牛，并且现在 Farmer John 正处于原点的左/右边，则可得状态转移方程为：

$$dp_{i,j,0}=\begin{cases}\min(dp_{i - 1,j,0} + (x_{i - 1} - x_i) (n - i - j + 1),dp_{i-1,j,1} + (y_{j} - x_i) (n - i - j + 1))&j>0\\dp_{i - 1,0,0} + (x_{i - 1} - x_i)(n - i + 1)&j=0\end{cases}$$

$$dp_{i,j,1}=\begin{cases}\min(dp_{i,j - 1,0} + (y_j - x_i) (n - i - j + 1),dp_{i,j-1,1} + (y_{j} - y_{j - 1}) (n - i - j + 1))&i>0\\dp_{0,j - 1,0} + (y_{j - 1} - y_j)(n - j + 1)&i=0\end{cases}$$

看到这里，有的巨佬可能就会问了：为什么要将距离乘上那么一大坨呢？很简单，因为每只奶牛每分钟都会给 Farmer John 带来 $1$ 美元的损失，所以每抓住一头奶牛，损失就要增加抓这只奶牛走的距离乘以在这之前还没被抓住的奶牛数。
# code
```c++
#include<bits/stdc++.h>
#define int1 long long
#define p 1005
using namespace std;
int1 n,a,x[p],y[p],dp[p][p][2],s,t,i,j;
int1 read(){
	int1 x = 0,f = 1;
	char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-'){
			f = -1;
		}
		ch = getchar();
	}
	while(isdigit(ch)){
		x = (x << 1) + (x << 3) + (ch & 15);
		ch = getchar();
	}
	return x * f;
}
void print(int1 x){
  	if(x < 0){
    	putchar('-');
    	x = -x;
  	}
  	if(x > 9){
    	print(x / 10);
  	}
  	putchar((x % 10) ^ 48);
  	return ;
}
bool cmp(int1 x,int1 y){
	return x > y;
}
int main(){
	memset(dp,0X79,sizeof(dp));
	n = read(),dp[0][0][0] = dp[0][0][1] = 0;//和上面这一行一样，都是初始化。 
	for(i = 1; i <= n; i++){
		a = read();
		if(a < 0){//将奶牛根据坐标分类。 
			x[++s] = a;
		}else{
			y[++t] = a;
		}
	}
	sort(x + 1,x + s + 1,cmp);
	sort(y + 1,y + t + 1);
	for(i = 1; i <= s; i++){//预处理。 
		dp[i][0][0] = dp[i - 1][0][0] + abs(x[i] - x[i - 1]) * (n - i + 1);
	}
	for(i = 1; i <= t; i++){//预处理。 
		dp[0][i][1] = dp[0][i - 1][1] + abs(y[i] - y[i - 1]) * (n - i + 1);
	}
	for(i = 1; i <= s; i++){
		for(j = 1; j <= t; j++){//正式 dp。 
			dp[i][j][0] = min(dp[i - 1][j][0] + abs(x[i] - x[i - 1]) * (n - i - j + 1),dp[i - 1][j][1] + abs(x[i] - y[j]) * (n - i - j + 1));
			dp[i][j][1] = min(dp[i][j - 1][0] + abs(y[j] - x[i]) * (n - i - j + 1),dp[i][j - 1][1] + abs(y[j] - y[j - 1]) * (n - i - j + 1));
		}
	}
	print(min(dp[s][t][0],dp[s][t][1])); 
	return 0;
}
```

---

## 作者：Celebrate (赞：1)

[我的博客](https://blog.csdn.net/zsyzClb/article/details/84889430)

题解

因为约翰一开始在原点的位置，所以贪心算法肯定过不了

看一下数据，n<=1000，那么这个就是一个很明显的O(N^2)区间dp了

因为是区间 所以要定义一个二维的dp数组

但是发现这样不行，于是在增加一维，判断是在头还是在尾

继承一样很简单

dp[ l ][ r ][ 0 ] = min ( dp[ l+1 ][ r ][ 0 ] +破坏量 , dp[ l+1 ][ r ][ 1 ] +破坏量）

dp[ l ][ r ][ 1 ] = min ( dp[ l ][ r-1 ][ 0 ] +破坏量 , dp[ l ][ r-1 ][ 1 ] +破坏量）

代码

```cpp
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std ;
 
const int N = 1e3 + 20 ;
int n , p[N] ;
int dp[N][N][2] ;
int main() {
	cin >> n ;
	for ( int i = 1 ; i <= n ; i ++ ) cin >> p[i] ;
	sort ( p+1 , p+n+1 ) ;
	memset ( dp , 63 , sizeof(dp) ) ;
	for ( int i = 1 ; i <= n ; i ++ ) dp[i][i][0] = dp[i][i][1] = abs( p[i] ) * n ;
	for ( int k = 2 ; k <= n ; k ++ ) 
		for ( int l = 1 ; l+k-1 <= n ; l ++ ) {
			int r = l+k-1 ;
			dp[l][r][0] = min ( 
				dp[l+1][r][0] + ( n - r + l ) * ( p[l+1] - p[l] ) ,
				dp[l+1][r][1] + ( n - r + l ) * ( p[r] - p[l] ) 
				) ; 
			dp[l][r][1] = min (
				dp[l][r-1][1] + ( n - r + l ) * ( p[r] - p[r-1] ) ,
				dp[l][r-1][0] + ( n - r + l ) * ( p[r] - p[l] ) 
				) ;
		}
	cout << min ( dp[1][n][0] , dp[1][n][1] ) << endl ;
	return 0 ;
}

```

---

## 作者：Yang818 (赞：1)

## [题目传送门](https://www.luogu.com.cn/problem/P3080)

## 解答

![p3080题解](https://cdn.luogu.com.cn/upload/image_hosting/hw2ent2h.png)

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;

int g_a[1010];
int f[1010][1010];
int g_n;

int main(){
	cin>>g_n;
	for(int i=1;i<=g_n;i++){
		cin>>g_a[i];
	}
	sort(g_a+1,g_a+g_n+2);
	int s=0;
	g_n++;
	for(int i=1;i<=g_n;i++){
		if(g_a[i]==0){
			s=i;
			break;
		}
	}
	memset(f,0x3f,sizeof(f));
	f[s][0]=0;
	for(int k=1;k<g_n;k++){
		for(int i=s+1;i<=min(s+k,g_n);i++){
			if(i-k<1){
				continue;
			}
			f[i][k]=min(f[i-1][k-1]+(g_a[i]-g_a[i-1])*(g_n-k),f[i-k][k-1]+(g_a[i]-g_a[i-k])*(g_n-k));
		}
		for(int i=s-1;i>=max(1,s-k);i--){
			if(i+k>g_n){
				continue;
			}
			f[i][k]=min(f[i+1][k-1]+(g_a[i+1]-g_a[i])*(g_n-k),f[i+k][k-1]+(g_a[i+k]-g_a[i])*(g_n-k));//dp转移方程
		}
	}
	cout<<min(f[1][g_n-1],f[g_n][g_n-1]);
	return 0;
} 
```


---

## 作者：zhouenji (赞：1)

诚如楼下所说，简单的区间dp，用dp【i】【j】【0/1】来表示状态

dp【i】【j】【0】表示套完区间i~j的所有牛且当前在i点的最小代价

dp【i】【j】【1】表示套完i~j后在j点的最小代价；

然后就是预处理了

见代码：

```cpp
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
const long long maxn=1000+10;
long long s[maxn],dp[maxn][maxn][2];
long long n,lenl;
int main()
{
    scanf("%lld",&n);
    for(long long i=1;i<=n;i++){
        scanf("%lld",&s[i]);
    }s[n+1]=0;
    sort(s+1,s+n+2);
    for(long long i=1;i<=n+1;i++){
        if(s[i]==0){
            lenl=i-1;break;
        }
    }dp[lenl+1][lenl+1][0]=dp[lenl+1][lenl+1][1]=0;
    for(long long i=lenl;i>=1;i--)dp[i][lenl+1][0]=dp[i+1][lenl+1][0]+(n+1-(lenl+1-i))*(s[i+1]-s[i]),
                                  dp[i][lenl+1][1]=dp[i][lenl+1][0]+(n-(lenl+1-i))*(s[lenl+1]-s[i]);
    for(long long i=lenl+2;i<=n+1;i++)dp[lenl+1][i][1]=dp[lenl+1][i-1][1]+(n+1-(i-lenl-1))*(s[i]-s[i-1]),
                                      dp[lenl+1][i][0]=dp[lenl+1][i][1]+(n-(i-lenl-1))*(s[i]-s[lenl+1]);
    for(long long i=lenl;i>=1;i--){
        for(long long j=lenl+2;j<=n+1;j++){
            dp[i][j][0]=min(dp[i+1][j][0]+(n+1-(j-i))*(s[i+1]-s[i]),dp[i+1][j][1]+(n+1-(j-i))*(s[j]-s[i]));
            dp[i][j][1]=min(dp[i][j-1][1]+(n+1-(j-i))*(s[j]-s[j-1]),dp[i][j-1][0]+(n+1-(j-i))*(s[j]-s[i]));
        }
    }printf("%lld\n",min(dp[1][n+1][0],dp[1][n+1][1]));
}

```

---

## 作者：luaddict (赞：1)

简单的区间DP呵，注意初始化即可。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
int n,s[1003],f[1001][1001][2],ans;
int main()
{
    int i,j,k;
    cin>>n;
    for(i=1;i<=n;i++)
    cin>>s[i];
    s[i]=0;
    n++;
    sort(s+1,s+n+1);
    for(i=1;i<=n;i++)
    if(s[i]>0)
    break;
    if(i==n+1)
    {
        for(i=1;i<=n;i++)
        ans-=s[i];
        cout<<ans<<endl;
        return 0;
    }
    if(i==1)
    {
        for(i=1;i<=n;i++)
        ans+=s[i];
        cout<<ans<<endl;
        return 0;
    }
    k=i-1;
    memset(f,127/3,sizeof(f));
    f[k][k][0]=0;
    f[k][k][1]=0;
    for(i=k+1;i<=n;i++)
    f[k][i][0]=f[k][i-1][0]+(s[i]-s[i-1])*(n-i+k);
    for(i=k-1;i>=1;i--)
    f[i][k][1]=f[i+1][k][1]+(s[i+1]-s[i])*(n-k+i);
    for(i=k-1;i>=1;i--)
    {
        for(j=k+1;j<=n;j++)
        {
            f[i][j][1]=min(f[i+1][j][1]+(s[i+1]-s[i])*(n-j+i),f[i+1][j][0]+(s[j]-s[i])*(n-j+i));
            f[i][j][0]=min(f[i][j-1][1]+(s[j]-s[i])*(n-j+i),f[i][j-1][0]+(s[j]-s[j-1])*(n-j+i));
        }
    }
    cout<<min(f[1][n][1],f[1][n][0])<<endl;
    return 0;
}
```

---

## 作者：Supor__Shoep (赞：0)

这道题和[关路灯](https://www.luogu.com.cn/problem/P1220)的思路其实是差不多的，有着异曲同工之妙。

根据这种来回遍历型的最值求解，以及 $n\leq 1000$ 的范围，不难推测出是一道区间 DP 题目。

区间 DP 的状态一定包含一个区间，所以我们初步定义 $dp_{i,j}$ 表示解决了第 $i$ 到第 $j$ 头牛的最小代价。但是这能够求出正确答案吗？

根据题目，我们知道每头牛每分钟消耗的是正数的代价，而且是要求最小值。那我们就不难想到一个结论，当我们经过一头牛的时候，我们**必须**要给牛套缰绳才能达到最小值。如果不，就会产生更多的代价。这样看上去二维状态貌似是可做的，只需要用 $dp_{i+1,j}$ 和 $dp_{i,j-1}$ 来转移就可以了…………吗？？

我们仔细观察上面的结论，在一个区间遍历当中，为了达到最优解，我们在 $[l,r]$ 遍历完之后停止的点一定是在 $l$ 或者 $r$ 上面。而两个不同的结果也许会使得答案不一样（可以举例得到），所以我们修改 DP 状态为 $dp_{i,j,0/1}$，表示在区间 $[i,j]$ 中，停在左端点（$0$） 或者右端点（$1$）时的最优答案。

那么我们就可以根据 $dp_{i+1,j,0/1}$ 转移到 $dp_{i,j,0}$，根据 $dp_{i,j-1,0/1}$ 转移到 $dp_{i,j,1}$。注意**排序**，而且我们还需要将大门坐标 $0$ **也设为一个点**，进行计算当中。

所以转移方程为：

$$\begin{cases}dp_{i,j,0}=\min\{dp_{i+1,j,0}+(a_{i+1}-a_i)\times (n-len+1),dp_{i+1,j,1}+(a_{j}-a_i)\times (n-len+1)\}\\dp_{i,j,1}=\min\{dp_{i,j-1,0}+(a_j-a_i)\times (n-len+1),dp_{i,j-1,1}+(a_j-a_{j-1})\times (n-len+1)\}\\\end{cases}$$

代码如下：

```cpp
#include<bits/stdc++.h>
#define int long long//没有一次过就是因为long long 
using namespace std;
const int MAXN=1005;
int n,a[MAXN];
int dp[MAXN][MAXN][2];
signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++)	cin>>a[i];
	a[++n]=0;//加入大门这一个点 
	sort(a+1,a+n+1);//排序 
	memset(dp,127,sizeof(dp));//赋最大值 
	int beg;
	for(int i=1;i<=n;i++)//找到大门，作为起始位置 
	{
		if(!a[i])
		{
			beg=i;
			break;
		}
	}
	dp[beg][beg][0]=dp[beg][beg][1]=0;//初始值 
	for(int len=2;len<=n;len++)
	{
		for(int i=1;i<=n-len+1;i++)
		{
			int j=i+len-1;//转移方程 
			dp[i][j][0]=min(dp[i+1][j][0]+(a[i+1]-a[i])*(n-len+1),dp[i+1][j][1]+(a[j]-a[i])*(n-len+1));
			dp[i][j][1]=min(dp[i][j-1][0]+(a[j]-a[i])*(n-len+1),dp[i][j-1][1]+(a[j]-a[j-1])*(n-len+1));
		}
	}
	cout<<min(dp[1][n][0],dp[1][n][1]);//答案是两个结果中的最小的 
	return 0;
}
```

---

## 作者：crh1272336175 (赞：0)

方法：线性DP+费用提前计算

将数据分成正数值和负数值两个数组pos和neg，数组里可以放绝对值，然后分别从小到大排序。

令f[i][j][0/1]表示正值取了i个，负值取了j个，此时在正值0(负值1)时的最少损失。

但代价的计算，需要知道到目前为止的总用时，这需要额外决策最少总用时，比较麻烦。

我们可以利用“费用提前计算”的经典思想解决，不需要求出每头奶牛完成时刻，而是每抓一头奶牛的用时对后面奶牛的影响先累加到答案中。

比如抓第一头奶牛用时3，那么所有奶牛的费用都加3，抓第二头奶牛用时5，(n-1)头奶牛的费用加5，以此类推。

这样f[i][j][0/1]的意义就不是抓i+j头奶牛的最少费用，而是抓i+j头奶牛，对于抓n头奶牛累积的总费用。

AC代码：
```cpp
#include<bits/stdc++.h>
#pragma GCC opitimize(2)
using namespace std;
typedef long long ll;
const int N=1005;
ll n,n1,n2;
ll pos[N],neg[N],f[N][N][2]; 
inline ll read()
{
    ll s=0,f=1; char ch=getchar();
    while(!isdigit(ch)){if(ch=='-') f=-1;ch=getchar();}
    while(isdigit(ch)) s=s*10+(ch^48),ch=getchar();
    return s*f;
}
inline void write(ll x)
{
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
 
int main()
{
    n=read();
    for(ll i=1; i<=n; i++)
    {
        ll x=read();
        if(x>0) pos[++n1]=x;
        else neg[++n2]=-x;
    }
    sort(pos+1,pos+n1+1); 
    sort(neg+1,neg+n2+1);
    memset(f,0x7f,sizeof f);
    f[0][0][0]=f[0][0][1]=0;
    for(ll i=0; i<=n1; i++)
        for(ll j=0; j<=n2; j++)
        {
            ll num=n-i-j+1;
            if(i>=1) f[i][j][0]=min(f[i-1][j][0]+num*(pos[i]-pos[i-1]),f[i-1][j][1]+num*(pos[i]+neg[j]));
            if(j>=1) f[i][j][1]=min(f[i][j-1][0]+num*(pos[i]+neg[j]),f[i][j-1][1]+num*(neg[j]-neg[j-1]));
        }
    ll ans=min(f[n1][n2][0],f[n1][n2][1]);
    write(ans);
    return 0;
}
```


---

