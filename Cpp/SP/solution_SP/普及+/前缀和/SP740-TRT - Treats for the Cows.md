# TRT - Treats for the Cows

## 题目描述

FJ经常给产奶量高的奶牛发特殊津贴，于是很快奶牛们拥有了大笔不知该怎么花的钱．为此，约翰购置了N(1≤N≤2000)份美味的零食来卖给奶牛们．每天FJ售出一份零食．当然FJ希望这些零食全部售出后能得到最大的收益．这些零食有以下这些有趣的特性：

•零食按照1．．N编号，它们被排成一列放在一个很长的盒子里．盒子的两端都有开口，FJ每天可以从盒子的任一端取出最外面的一个．

•与美酒与好吃的奶酪相似，这些零食储存得越久就越好吃．当然，这样FJ就可以把它们卖出更高的价钱．

•每份零食的初始价值不一定相同．FJ进货时，第i份零食的初始价值为Vi(1≤Vi≤1000)(Vi指的是从盒子顶端往下的第i份零食的初始价值)．

•第i份零食如果在被买进后的第a天出售，则它的售价是vi×a．

FJ告诉了你所有零食的初始价值，并希望你能帮他计算一下，在这些零食全被卖出后，他最多能得到多少钱．

## 样例 #1

### 输入

```
5
1
3
1
5
2```

### 输出

```
43```

# 题解

## 作者：yf最qhhh (赞：3)

**区间DP**

$f[i][j]$ 表示 $i-j$ 号零食能获得的最大价值

每次有两个答案，从左边取和从右边取。取大的那个赋给 $f[i][j]$ 

所以 $f[i][j]=$ 左/右边零食的价值 $+$ 当前能取到的最大价值

但这样还不够，因为假设我们取最左边，取最左边是第一天，所以取$i+1-j$ 时都要推迟一天，那么要加上 $i+1...j$ 能获得的钱数

我们拿一个 $Sum$ 数组来记录就行了。

最终的答案为 $f[1][n]$。

所以代码如下：
```cpp
#include<cstdio>
#include<algorithm>
#define ll long long
#define rll register long long
ll f[2005][2005],Sum[2005];
int main(){
    rll n,i,j;
    scanf("%lld",&n);
    for(i=1;i<=n;i++){
    scanf("%lld",&f[i][i]);
        Sum[i]=Sum[i-1]+f[i][i];//Sum数组记录
    }
    for(j=1;j<=n;j++){
        for(int i=1;i+j<=n;i++){
    	    f[i][i+j]=std::max(f[i][i]+f[i+1][i+j]+(Sum[i+j]-Sum[i]),f[i+j][i+j]+f[i][i+j-1]+(Sum[i+j-1]-Sum[i-1]));//状态转移方程
        }
    }
    return printf("%lld",f[1][n]),0;
}
```


---

## 作者：小铭同学lym (赞：3)

## 0 前言
当我第一次做这道题的时候，学校刚好在比赛。当时也没想这么多，打了个贪心。结果得了27.3分。后来想起来该这道题，一开始还不会做......看了区间dp的题解还不懂，只好看记忆化搜索的题解，才 AC......

所以，想写个题解，做个纪念。
## 1 题目
[题目传送门](https://www.luogu.com.cn/problem/SP740)
## 2 做法
1. 区间 dp （请看其他题解）。
2. 记忆化搜索。
3. 其他各种玄学（请看其他题解）。

## 3 具体做法
我们可以先设一个数组$f_{x,y}$，来表示：从 $x$ 号零食到 $y$ 号零食的最大价值。那么，最后就可以直接输出$f_{1,n}$来求出答案。

我们要求$x$一定要比 $y$ 大，所以我们可以把 $x$，$y$ 代替为 $l$，$r$。

在这道题中，当前无非就有两个状态：要么从左边取，要么从右边取。所以哪边大，就取哪边。

现在我们差不多已经构建完了 $\textit{dfs}$ 函数。再来思考一下细节：先设一个参数 $x$ ，表示第几天，接着就是 $l$ 和 $r$。取左边的最大值，是 $l+1$ 到 $r$ 的最大值$+x\times a_l$。所以，代码是```dfs(x+1,l+1,r)+x*a[l]```。

同理，取右边的最大值是 $l$ 到 $r-1$ 的最大值$+x\times a_r$。代码是```dfs(x+1,l,r-1)+x*a[r]```。

这样我们就可以把整个$\textit{dfs}$函数给写出来了：
```cpp
int dfs(int x,int l,int r)
{
	if(l>r)
		return 0;
	if(f[l][r]>0)
		return f[l][r];
	return f[l][r]=max(dfs(x+1,l+1,r)+x*a[l],dfs(x+1,l,r-1)+x*a[r]);
}
```
输入完后，只用写$dfs_{1,1,n}$，然后输出$f_{1,n}$即可。
## 4 AC代码
```cpp
#include<cstdio>
using namespace std;
int n,f[2002][2002],a[2002];
int max(int x,int y)
{
	if(x>y)
		return x;
	return y;
}
int dfs(int x,int l,int r)
{
	if(l>r)
		return 0;
	if(f[l][r]>0)
		return f[l][r];
	return f[l][r]=max(dfs(x+1,l+1,r)+x*a[l],dfs(x+1,l,r-1)+x*a[r]);
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	dfs(1,1,n);
	printf("%d",f[1][n]);
	return 0;
} 
```
如有错误，请dalao指出。

---

## 作者：ahwhQZY (赞：3)

## SP740 (Treats for the Cows)

题面传送门:https://www.luogu.com.cn/problem/SP740

### 题目大意：
	
  给你一个序列，每次可以从头或尾取一个数，分值为$i$(取得第$i$次)*$a_{i}$，求最大分值。
    
### 解题思路：

我们用$dp_{i,j}$表示区间$[{i,j]}$号零食能获得的最大价值。

状态转移：$dp_{i,j}$=左/右边零食的价值+当前能取到的最大价值。

似乎不够，对了，应该假设我们取最左边，取最左边是第一
天，所以取$i+1-j$时都要推迟一天，那么要加上$i+1...j$能获得的钱数。

得出状态转移方程：$dp[i][i+j]=\max(dp[i][i]+dp[i+1][i+j]+(sum[i+j]-sum[i]),dp[i+j][i+j]+dp[i][i+j-1]+(sum[i+j-1]-sum[i-1]));$

其余注释见代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;//用long long 好一点 
ll n,dp[2001][2001],num[2001],sum[2001]={0};
int main(){
    scanf("%lld",&n);
    for(ll i=1;i<=n;i++){
        scanf("%lld",&dp[i][i]);
        sum[i]=sum[i-1]+dp[i][i];//前缀和预处理
    }
    for(ll j=1;j<=n;j++) 
        for(ll i=1;i+j<=n;i++)//再枚举i 
            dp[i][i+j]=max(dp[i][i]+dp[i+1][i+j]+(sum[i+j]-sum[i]),dp[i+j][i+j]+dp[i][i+j-1]+(sum[i+j-1]-sum[i-1]));
            //状态转移+前缀和 
    printf("%lld",dp[1][n]);//输出dp[1][n]
    //结束啦 
}
```

---

## 作者：EarthGiao (赞：2)

## 【思路】
区间DP    
### 【题目大意】  
每次都从左端点或者右端点选择一个零食     
获得的价值是这个零食的价值乘以是第几个选择的     

### 【核心思路】 
可以设置一个状态f(i,j)     
表示选取了i个零食，在左边选取了j个     
这个状态可以由前面选取了i - 1个零食    
在左边选取j个零食或者在左边选取了j-1个零食   
意思就是：    
之前选取了i-1个零食   
现在选取的第i个零食    
分别在左边选的还是在右边选的情况转移过来   

### 【DP方程式】
$$f[i][j] = max(f[i - 1][j] + a[n - i + 1 + j] * i,f[i - 1][j - 1] + a[j] * i)$$     

## 【完整代码】
```cpp
#include<iostream>
#include<cstdio>

using namespace std;
const int Max = 2005;
int a[Max];
int f[Max][Max];

int main()
{
	int n;
	cin >> n;
	for(register int i = 1;i <= n;++ i)
		cin >> a[i];
	for(register int i = 1;i <= n;++ i)
		for(register int j = 0;j <= i;++ j)
			f[i][j] = max(f[i - 1][j] + a[n - i + 1 + j] * i,f[i - 1][j - 1] + a[j] * i);
	int M = 0;
	for(register int i = 0;i <= n;++ i)
		M = max(M,f[n][i]);
	cout << M << endl;
	return 0; 
}
```

---

## 作者：ez_lcw (赞：2)

# 神奇的dp

这是一道很典型的区间dp题。

具体思路如下：

**我们用$dp[i][j]$来表示从第i份零食到第j份零食所能获得的最大钱数。**

**那么不难想到，假设我们现在要求$dp[i][j]$，那么我们就考虑第一天从最左边开始取，还是从最右边开始取。若从最左边开始取，则获得的钱数为**

**$money[i]$（最左边零食的价值）+**

**$dp[i+1][j]$（除去最左边外能取得的最大值）+**

**$sum[i+1][j]$（因为取最左边的是第一天，所以取$i+1$~$j$时都要推迟一天，那么获得的总价值就要加上从$i+1$加到$j$的一天能获得的钱数）**

那么状态转移方程就显而易见了：

$$dp[i][i+len]=max(dp[i][i]+dp[i+1][i+len]+(sum[i+len]-sum[i]),dp[i+len][i+len]+dp[i][i+len-1]+(sum[i+len-1]-sum[i-1]));$$

其中，$sum$是用前缀和实现的。

具体代码如下：
```cpp
#include<cstdio>
#include<iostream>

#define N 2001

using namespace std;

int n,sum[N],dp[N][N];

int main()
{
	scanf("%d",&n);
	for(int i=1; i<=n; i++)
	{
		scanf("%d",&dp[i][i]);//dp[i][i]就是这个位置的零食
		sum[i]=sum[i-1]+dp[i][i];//前缀和
	}
	for(int len=1; len<=n; len++)
	{
		for(int i=1; i+len<=n; i++)
		{
			dp[i][i+len]=max(dp[i][i]+dp[i+1][i+len]+(sum[i+len]-sum[i]),dp[i+len][i+len]+dp[i][i+len-1]+(sum[i+len-1]-sum[i-1]));//状态转移方程
		}
	}
	printf("%d\n",dp[1][n]);//输出从1到n能获取的最多的钱数
	return 0;
}
```

---

## 作者：kevin1616 (赞：1)

### 审题
有 $N$ 个数，第 $i$ 个数为 $V_i$。它们被排成一列，每次可以从盒子左端或右端取走一个。第 $i$ 个数如果是第 $a$ 个被取走，则它的价值是 $V_i\times a$。问这个序列的最大价值。
***
### 方法
【贪心】每次选择左右端里最便宜的零食。虽然这种方法看似可行，但是有一些特例不行。举个例子：

```
6
3 3 3 1 1 4
```

根据贪心策略，应该依次拿第 1、2、3、4、5、6、7、8、9 个。此时根据贪心的总共钱数是 $3\times1+3\times2+3\times3+1\times4+1\times5+4\times6=51$。但是最优解为 $4\times1+1\times2+1\times3+3\times4+3\times5+3\times6=54$。所以我们可以看到，每个物品的选取不止影响当前，同时影响着后面的选取。所以贪心不可行。

【区间动态规划】区间动态规划比较适合选取头和尾的题型，时间复杂度为 $O(n^2)$，此题数据又比较小，所以可以使用区间动态规划。

***
### 思路
由于删除不便于实现，我们可以把操作反过来，变成每次加入一个数。这里的 `dp[i][j]` 代表在 $i\sim j$ 这个区间里的最大价值。所以每次枚举区间长度，然后再枚举起点，即可知道终点。在此每个区间里的最大价值有两种转移的可能，其中 $len$ 表示当前区间长度：

1. 在 $(i+1)\sim j$ 这个区间里的最大价值加上 $v_i\times(n - len + 1)$。
2. 在 $i\sim (j-1)$ 这个区间里的最大价值加上 $v_j\times(n - len + 1)$。

最后输出从 $1$ 到 $n$ 这个区间里的最大价值。
***
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int v[2005];
int dp[2005][2005];
int main(){
    cin >> n;
    for(int i = 1;i <= n;i++) cin >> v[i];
    for(int len = 1;len <= n;len++){ //区间长度
        for(int i = 1;i <= n - len + 1;i++){ //起点
            int j = i + len - 1; //终点
            dp[i][j] = max(dp[i + 1][j] + v[i] * (n - len + 1),dp[i][j - 1] + v[j] * (n - len + 1)); //转移方程
        }
    }
    cout << dp[1][n]; //输出
    return 0;
}
```
不抄题解，从我做起！

---

## 作者：zqh123b (赞：0)

[luogu 传送门](https://www.luogu.com.cn/problem/SP740)  
[SPOJ 传送门](https://www.luogu.com.cn/remoteJudgeRedirect/spoj/740)  

----

### 【题目描述】  
现有 $n$ 个物品，每天物品的价值会加上 $v_i$。每天都要出售一个物品，可以从两端拿取，求最大收益。

----

### 【题目解法】
明显的**区间 DP**，用 $dp[i][j]$ 表示从 $i$ 至 $j$ 号的最大收益。  

#### 【初始化】  
对于 $dp[i][i]$ 的最大收益即 $v[i]$，就此初始化 $dp$ 数组即可。  

#### 【前置】  
本题需要一个前缀和，标准的那种。  

#### 【动态转移方程】  
每次可以取左边的，也可以取右边的。  
因此 $dp[i][j] =$ 左或右边的最大收益 $+$ 当前的最大收益。  
到这里，应该都发现了，前缀和就是用来算当前的最大收益的。  
最终的转移方程：
```cpp
dp[l][r]=max(dp[l+1][r],dp[l][r-1])+sum[r]-sum[l-1];
```


#### 【答案】  
就是 $dp[1][n]$。

----

### 【完整代码】
```
#include<bits/stdc++.h>
using namespace std;
int n,a[2010],sum[2010],f[2010][2010];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++)sum[i]=sum[i-1]+a[i];
	for(int i=1;i<=n;i++)f[i][i]=a[i];
	for(int len=2;len<=n;len++){
		for(int l=1;l+len-1<=n;l++){
			int r=l+len-1;
			f[l][r]=max(f[l+1][r],f[l][r-1])+sum[r]-sum[l-1];
		}
	}
	cout<<f[1][n];
    return 0;
}
```

这道题其实一点也不难。  

小小的吐槽一句，这题不是个黄题？！

---

## 作者：Supor__Shoep (赞：0)

我做完后翻了一些题解，很少有人不用前缀和写 DP，所以我就来写一下这篇不用前缀和的题解吧。

首先为什么是区间 DP 呢？非常明显，因为他是从左右端点取的，但是很容易判断不是队列，加上刚好 $O(n^2)$ 可以过的数据，那么肯定就是一个中规中矩的区间 DP 了。

通过对数据的分析，我们肯定不会枚举中间点，所以我们是从区间 $[i,j]$ 的两端 $i$ 和 $j$ 取的数。设 $dp_{i,j}$ 表示选 $[1,n]$ 时选到区间 $[i,j]$，接着选完 $[i,j]$ 的答案（**注意状态**）。那么 $dp_{i,j}$ 就是从 $dp_{i+1,j}$ 或者 $dp_{i,j-1}$ 再选一个数转换的。考虑到是先选了 $[1,i-1]$ 和 $[j+1,n]$，所以如果要加上一个数，就需要乘上 $n-len+1$，其中 $len$ 表示区间 $[i,j]$ 的长度（即 $j-i+1$）。

那么我们就可以列出方程了：

$$dp_{i,j}=\max(dp_{i+1,j}+v_i\times (n-len+1),dp_{i,j-1}+v_j\times (n-len+1))$$

简单的输出答案为 $dp_{1,n}$。

最后注意一个地方——**初始化**，根据状态可知，$dp_{i,i}$ 是选的最后一个数，所以初始为 $dp_{i,i}=v_i\times n$。

代码就不给了，请给位读者自行完成这道题！！

---

## 作者：5G信号塔报装 (赞：0)

## 思路

思维过程简单的区间 DP 入门题。

**简化版题意**：给定一个双端队列，每次取出一个数，第 $k$ 次取出的数所得到的值就是这个数与 $k$ 的乘积。使 $n$ 个值的和最大。

我们考虑 DP，用 $\text{dp}_{i,j}$ 表示从 $i$ 到 $j$ 所得到的最大值。

对于一个 DP 节点，它只能从两个方向转移：从 $i+1,j$ 或 $i,j-1$。

很显然，我们可以这样转移：

$$\text{dp}_{st.ed} = max(\text{dp}_{st+1,ed} + (n-i+1) \times a_{st}, \text{dp}_{st,ed-1} + (n-i+1) \times a_{ed})$$

## 代码

```cpp
# include <bits/stdc++.h>
using namespace std;

int n;
int a[2005];
int dp[2005][2005];

signed main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
	}
	for (int i = 1; i <= n; i++) {
		// dp 初值初始化
		dp[i][i] = a[i] * n;
	}
	for (int i = 2; i <= n; i++) {
		// 枚举区间长度
		for (int j = 1; j <= n-i+1; j++) {
			int st = j;
			int ed = i + j - 1;
			dp[st][ed] = max(dp[st+1][ed] + (n-i+1)*a[st], dp[st][ed-1] + (n-i+1)*a[ed]);
		//	printf("[debug] i=%d,j=%d,st=%d,ed=%d\n", i, j, st, ed);
		} 
	}
	printf("%d\n", dp[1][n]);
	return 0;
} 
```

---

## 作者：William_Fangs (赞：0)

# dp问题
我们设定一个数组 f[i][j]表示取出i个物品中有j个从头部取出。  
则一定有i-j个物品从尾部取出。  
于是就得到了转移方程 f[i][j]=max(f[i-1][j]+a[n-(i-j)+1] _X_ (i)f[i-1][j-1]+a[j]*(i))  
再从f[n][0]到f[n][n]中求出最大值即可

  
    
放代码  
```cpp
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
const int N=2005;
int n;
int a[N];
int f[N][N];//F[I][J]表示取出i个物品中有j个是从头部拿起的； 
int dfs(int i,int j)
{
	if(j>i||j<0)
		return 0;
	if(f[i][j]!=0)
		return f[i][j];
	f[i][j]=max(dfs(i-1,j)+a[n-(i-j)+1]*(i),dfs(i-1,j-1)+a[j]*(i));
	return f[i][j];
 } 
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
	}
	int maxn=-1;
	for(int j=0;j<=n;j++)
	{
		maxn=max(dfs(n,j),maxn);
	}
	printf("%d\n",maxn);
	return 0;
 } 
 ```
 


---

## 作者：asasas (赞：0)

既然没有记忆化搜索的题解，那我就来写一篇吧。

众所周知，所有的DP题都能拿记搜写，这题也不例外。

DFS函数有三个参数：$step$(第几天）,$l$(左边的零食)，$r$(右边的零食)。记搜数组$qwq_{i,j}$表示第$i$个零食到第$j$个零食的最大价值（很像dp）。

每次搜索是从左边取零食还是从右边取零食，将其中的较大值赋给$qwq_{i,j}$并返回，最后输出$qwq_{1,n}$即可。

将其套到记搜板子上即可。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int qwq[2005][2005],a[2005];
int dfs(int step,int l,int r){//三个参数
	if (r<l) return 0;//边界条件
	if (qwq[l][r]!=0) return qwq[l][r];//有值就返回
	qwq[l] [r]=max(dfs(step+1,l+1,r)+step*a[l],dfs(step+1,l,r-1)+step*a[r]);//判断从左边取价值大还是右边取价值大
	return qwq[l][r];
} 
int main(){
    int n;
    cin >> n;
    for (int i=1;i<=n;i++) cin >> a[i];
    dfs(1,1,n);//初始值
    cout << qwq[1][n];//最终答案为第1个零食到第n个零食的最大价值
    return 0;
}
```


---

