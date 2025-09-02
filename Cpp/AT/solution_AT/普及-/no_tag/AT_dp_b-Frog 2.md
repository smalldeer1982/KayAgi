# Frog 2

## 题目描述

[problemUrl]: https://atcoder.jp/contests/dp/tasks/dp_b

$ N $ 個の足場があります。 足場には $ 1,\ 2,\ \ldots,\ N $ と番号が振られています。 各 $ i $ ($ 1\ \leq\ i\ \leq\ N $) について、足場 $ i $ の高さは $ h_i $ です。

最初、足場 $ 1 $ にカエルがいます。 カエルは次の行動を何回か繰り返し、足場 $ N $ まで辿り着こうとしています。

- 足場 $ i $ にいるとき、足場 $ i\ +\ 1,\ i\ +\ 2,\ \ldots,\ i\ +\ K $ のどれかへジャンプする。 このとき、ジャンプ先の足場を $ j $ とすると、コスト $ |h_i\ -\ h_j| $ を支払う。

カエルが足場 $ N $ に辿り着くまでに支払うコストの総和の最小値を求めてください。

## 说明/提示

### 制約

- 入力はすべて整数である。
- $ 2\ \leq\ N\ \leq\ 10^5 $
- $ 1\ \leq\ K\ \leq\ 100 $
- $ 1\ \leq\ h_i\ \leq\ 10^4 $

### Sample Explanation 1

足場 $ 1 $ → $ 2 $ → $ 5 $ と移動すると、コストの総和は $ |10\ -\ 30|\ +\ |30\ -\ 20|\ =\ 30 $ となります。

### Sample Explanation 2

足場 $ 1 $ → $ 2 $ → $ 3 $ と移動すると、コストの総和は $ |10\ -\ 20|\ +\ |20\ -\ 10|\ =\ 20 $ となります。

### Sample Explanation 3

足場 $ 1 $ → $ 2 $ と移動すると、コストの総和は $ |10\ -\ 10|\ =\ 0 $ となります。

### Sample Explanation 4

足場 $ 1 $ → $ 4 $ → $ 8 $ → $ 10 $ と移動すると、コストの総和は $ |40\ -\ 70|\ +\ |70\ -\ 70|\ +\ |70\ -\ 60|\ =\ 40 $ となります。

## 样例 #1

### 输入

```
5 3
10 30 40 50 20```

### 输出

```
30```

## 样例 #2

### 输入

```
3 1
10 20 10```

### 输出

```
20```

## 样例 #3

### 输入

```
2 100
10 10```

### 输出

```
0```

## 样例 #4

### 输入

```
10 4
40 10 20 70 80 10 20 70 80 60```

### 输出

```
40```

# 题解

## 作者：GZY007 (赞：7)

## 线性DP简单题
- 令 $dp[i]$为当青蛙跳到石头i时使用的力气的最小值。
- 初始状态为 $dp[1]=0$,即去到第一块石头时花费为0。
- 动态转移方程：$dp[i+k]=min(dp[i+k],dp[i]+|h[i+k]-h[i]|$。
- 由于有k种跳的方法，用循环即可。

------------

其他细节见代码，代码如下：
```cpp
#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;
int dp[200010],h[200010],m,k;
int main(){
	cin>>m>>k;
	memset(dp,2147483647,sizeof(dp));//初始化数组 
	for(int i=1;i<=m;i++) 
	{
		cin>>h[i];
	}
	dp[1]=0;//设置初始情况 
		for(int j=1;j<=m-1;j++)//向前递推 
		{
				for(int x=1;x<=k;x++)//枚举青蛙向前跳的情况 
				{
					dp[j+x]=min(dp[j+x],dp[j]+abs(h[j]-h[j+x]));//更新答案 
				}
		}
	cout<<dp[m]; 
return 0;
}
```


---

## 作者：Doqin07 (赞：6)

### 简单题
##### 建议可以先做[简化版](https://www.luogu.com.cn/problem/AT4522)


------------
- ##### 设$dp[i]$表示跳到第$i$块石头时所用体力的最小值
- ##### 则$dp[1]=0$，第$1$块石头第$1$块石头代价为0
- 1. ##### $dp[i]=min(dp[i],dp[j]+|h[i]-h[j]|) $
	2. ##### $i-k \le j<i$
    3. ##### 由于第$i$个石头可能从前$k$个石头任意一个跳过来，所以枚举每一种情况取$min$即可
- ##### 别忘记初始化$dp$数组

```c
memset(dp,0x3f,sizeof(dp));
```



- ##### $O(nk)$递推即可

-----
### 核心Code
```c
dp[1]=0;
for(int i=2;i<=n;++i)
	for(int j=max(1,i-k);j<i;++j)
		dp[i]=min(dp[i],dp[j]+abs(h[i]-h[j]));
```



---

## 作者：Ryo_Yamada (赞：2)

此题翻译本人也已提交，麻烦管理审核一下，谢谢。

此题是一道$dp$题。整体思路是用$dp[i]$表示跳到第$i$块石头需要的最小体力值。不难得出，状态转移方程$dp[i] = min(dp[i], dp[i - j] + abs(h[i] - h[i - j])$.其中$1 \leq j \leq K, 1 \leq j \leq K$。时间复杂度$O(NK)$。

还有两点需要注意的：

- $dp$数组要初始化成`INF`，用`0x3f`。
- 当$i < K$时j循环不能循环$N$次。~~废话~~

上代码：

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#define min(a, b) a < b ? a : b
using namespace std;
int f[100000];
int dp[100000];
int abs(int a) {
    return a < 0 ? -a : a;
}//自己写了abs和min函数.
int main() {
	int n, k;
	cin >> n >> k;
	memset(dp, 0x3f, sizeof(dp));
	for(int i=0; i<n; i++) {
		scanf("%d", &f[i]);
	}
	dp[0] = 0;//dp[0]值应为0.
	for(int i=1; i<k; i++) {
		for(int j=i; j>=0; j--) {
			dp[i] = min(dp[i], dp[i - j] + abs(f[i] - f[i - j]));
		}
	}//如果i < k
	for(int i=k; i<n; i++) {
		for(int j=1; j<=k; j++) {
			dp[i] = min(dp[i], dp[i - j] + abs(f[i] - f[i - j]));
		}
	}//剩下的情况，
   //状态转移方程一出，dp就很好写。
	cout << dp[n - 1] << endl;//输出
    return 0;
}
```


---

## 作者：Gloaming (赞：1)

## 分析

我们读完这道题之后，可以发现它让我们求一个最小值，我们就可以想到一个算法：动态规划。

动态规划最重要的就是定义状态和转移状态，我们根据问什么设什么的方法，就想到定义$dp_i$为调到$i$的最小代价。

思考一下，我们的$dp_i$是怎么来的呢？它是由所有前面能到达的石头在加上代价而得到的。

那么就有转移方程：$dp_i=\max{dp_j+|h_i-h_j|}(j+k\geq i)$

于是代码就出来了。

## 代码
```c++
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100000 + 10;
int n, k, h[MAXN], dp[MAXN];
int main()
{
	cin >> n >> k;
	for(int i = 1; i <= n; i ++)
		cin >> h[i];
	memset(dp, 0x3f, sizeof dp);
	dp[1] = 0;
	for(int i = 2; i <= n; i ++)
		for(int j = max(1, i - k); j < i; j ++)
			dp[i] = min(dp[i], dp[j] + abs(h[i] - h[j]));
	cout << dp[n];
	return 0;
}
```

---

## 作者：出言不逊王子 (赞：1)

简单题。

我们假设状态`f[i]`为从树桩$i$跳到树桩$n$所需要的的最短距离。

正面思考较难，不如反着想：从第$n$根树桩开始跳，一直跳到第$1$根为止。

显然`f[n]`是$0$。

假设$k=2$。

根据题意，第$i$根树桩可以跳到第$i+1$或第$i+2$根树桩上，那么反过来，第$i$根树桩只能从第$i+1$和第$i+2$根树桩跳过来。

那么就不难列出转移方程了：

$$f_i=\begin{cases}0&n\\|h_n-h_{n-1}|&n-1\\\min(f_{i+2}+|h_i-h_{i+2}|,f_{i+1}+|h_i-h_{i+1}|)&\text{其他情况}\end{cases}$$

那么$k$等于任意正整数的情况和上边一样，但是要注意不能跳出范围，即$i+j\le n$（$i$和$j$的定义见代码。）

其他细节见代码。

代码：

```cpp
     #include<bits/stdc++.h>
    using namespace std;
    const int N=500001,inf=1e9+7;
    #define fs(i,x,y,z) for(int i=x;i<=y;i+=z)
    #define ft(i,x,y,z) for(int i=x;i>=y;i+=z)
    #define dis(i,j) abs(a[i]-a[j])
    int a[N],f[N];
    int main(){
    	int n,k;cin>>n>>k;
    	fs(i,1,n,1) cin>>a[i];
    	f[n]=0;
    	f[n-1]=dis(n-1,n);
    	ft(i,n-2,1,-1){
    		f[i]=inf;
    		fs(j,1,k,1) if(i+j<=n) f[i]=min(f[i+j]+dis(i+j,i),f[i]);
    	}
    	cout<<f[1];
    	return 0;
    }

```

最后宣传[博客](zeta.connectakioi.cf)，欢迎注册~

---

## 作者：小豆子范德萨 (赞：0)

- 解题思路
本题直接dp做吧，别想这dfs或者记忆化搜索了，因为有k的存在，搜索细节不好写。

这一题类似p1192台阶问题、都是每一步可以走k步以内，但是区别是前者求方案数，这题是求最小花费

dp数组：dp[i]表示从起点到i的最小花费

dp边界：

- dp[1] = 0
- dp[2] = abs(a[2]-a[1])

状态转移方程

```
dp[i] = min(dp[i-1]+abs(a[i] - a[i-1]),dp[i-2]+abs(a[i] - a[i-2]）......dp[i-k]+abs(a[i] - a[i-k]))
```
 不可能写这么长的状态转移方程，故需要用个循环处理，这是本题的难点、具体看代码吧
 
 ```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5+10;
int a[maxn];
int dp[maxn];		//dp[i]:从起点到i的最小费用 

int main() {
	int n,k;cin>>n>>k;
	for(int i = 1;i <= n;i++) cin>>a[i];
	dp[1] = 0;
	dp[2] = abs(a[2] - a[1]);
	for(int i = 3;i <= n;i++) {
		dp[i] = 1e9;		//需要将dp[i]定义为一个很大的值，类似于求Min,要设置为很大的一个数 
		for(int j = 1;j <= k;j++) {		//枚举从前面的状态到当前状态可能跳的步数 
			if(i - j >= 1) {		//i-j=1时数组访问刚好不越界 
				dp[i] = min(dp[i],dp[i-j] + abs(a[i] - a[i-j]));
			} else 
				break;
		}
	}
	cout<<dp[n];
	return 0;
}
```

	

---

## 作者：chenxia25 (赞：0)

>### [洛谷题目页面传送门](https://www.luogu.com.cn/problem/AT4523) & [AtCoder题目页面传送门](https://atcoder.jp/contests/dp/tasks/dp_b)

>有$n$个石头，第$i$个石头高度为$a_i$。青蛙初始站在石头$1$上。当青蛙在石头$i$上时，它可以跳到石头$j=i+1$、石头$j=i+2$、……、石头$j=i+m$（如果存在的话），花费的代价为$|a_j-a_i|$。求青蛙跳到石头$n$的最小代价。

>$n\in\left[2,10^5\right],m\in[1,100]$。

设$dp_i$表示跳到石头$i$的最小代价。边界是$dp_1=0$，目标是$dp_n$，状态转移方程是$dp_i=\min\limits_{j=\max(1,i-m)}^{i-1}\{dp_j+|a_i-a_j|\}$（尝试从石头$\max(1,i-m)$、石头$\max(1,i-m)+1$、……、石头$i-1$跳过来）。时间复杂度$\mathrm O(nm)$。

下面是AC代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int inf=0x3f3f3f3f;
const int N=100000;
int n,m;
int a[N+1];
int dp[N+1];
int main(){
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=2;i<=n;i++){
		dp[i]=inf;
		for(int j=max(1,i-m);j<i;j++)
			dp[i]=min(dp[i],dp[j]+abs(a[i]-a[j]));//转移 
	}
	cout<<dp[n];//目标 
	return 0;
}
```


---

