# Frog 1

## 题目描述

[problemUrl]: https://atcoder.jp/contests/dp/tasks/dp_a

$ N $ 個の足場があります。 足場には $ 1,\ 2,\ \ldots,\ N $ と番号が振られています。 各 $ i $ ($ 1\ \leq\ i\ \leq\ N $) について、足場 $ i $ の高さは $ h_i $ です。

最初、足場 $ 1 $ にカエルがいます。 カエルは次の行動を何回か繰り返し、足場 $ N $ まで辿り着こうとしています。

- 足場 $ i $ にいるとき、足場 $ i\ +\ 1 $ または $ i\ +\ 2 $ へジャンプする。 このとき、ジャンプ先の足場を $ j $ とすると、コスト $ |h_i\ -\ h_j| $ を支払う。

カエルが足場 $ N $ に辿り着くまでに支払うコストの総和の最小値を求めてください。

## 说明/提示

### 制約

- 入力はすべて整数である。
- $ 2\ \leq\ N\ \leq\ 10^5 $
- $ 1\ \leq\ h_i\ \leq\ 10^4 $

### Sample Explanation 1

足場 $ 1 $ → $ 2 $ → $ 4 $ と移動すると、コストの総和は $ |10\ -\ 30|\ +\ |30\ -\ 20|\ =\ 30 $ となります。

### Sample Explanation 2

足場 $ 1 $ → $ 2 $ と移動すると、コストの総和は $ |10\ -\ 10|\ =\ 0 $ となります。

### Sample Explanation 3

足場 $ 1 $ → $ 3 $ → $ 5 $ → $ 6 $ と移動すると、コストの総和は $ |30\ -\ 60|\ +\ |60\ -\ 60|\ +\ |60\ -\ 50|\ =\ 40 $ となります。

## 样例 #1

### 输入

```
4
10 30 40 20```

### 输出

```
30```

## 样例 #2

### 输入

```
2
10 10```

### 输出

```
0```

## 样例 #3

### 输入

```
6
30 10 60 10 60 50```

### 输出

```
40```

# 题解

## 作者：乐乐乐还在乐 (赞：15)

# AT4522 题解

**[题目传送门](https://www.luogu.com.cn/problem/AT4522)**

### 题目大意

一只青蛙要从 $1$ 号石头跳到 $n$ 号石头上。

每次跳跃需消耗一些费用。

求青蛙跳到 $n$ 号石头需要的最小总费用。

### 分析题目
这道题~~明显就~~是一道动态规划。

康康数据范围：$2 \le N \le 10^5$, $O(n)$ 能过。



### 前置工作

我们先定义一个函数 $cost(i,j)$,用来计算从第 $i$ 块石头跳到第 $j$ 块石头的花费。

由题意，$cost(i,j)=|a_i-a_j|$。

### 思考算法

dp 三件套：状态、状态转移方程、初始状态。

**状态：**

用 $dp_i$ 表示跳到第i块石头所需的最小费用。

**状态转移方程：**

$dp_i=min\Big(dp_i+cost(i,i-1),dp_i+cost(i,i-2)\Big)$

即:跳到第 $i$ 块石头所需的最小费用 = 前两块的最小费用 + 跳过来的消耗。

**初始状态：**

跳到第一块石头无需消耗(~~跳都不用跳~~)，

跳到第二块石头需消耗 $cost(1,2)$。

即 $dp(1)=0,dp(2)=cost(1,2)$。

~~接着就可以愉快地dp啦。~~

```cpp
for(int i=3;i<=n;i++)
	dp[i]=min(dp[i-1]+cost(i,i-1),dp[i-2]+cost(i,i-2));
```

$\upuparrows\upuparrows$ ~~主要程序~~ $\upuparrows\upuparrows$

## 附上AC代码


```cpp
#include<bits/stdc++.h>

using namespace std;

const int MAXN=1e5+5;

int n;
int h[MAXN]={0};
int dp[MAXN]={0};//dp[i]表示跳到第i块石头所需的最小费用

int cost(int i,int j){//cost函数表示从第i块石头跳到第j块石头的花费
	return abs(h[i]-h[j]);
}

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&h[i]);
	
	dp[2]=cost(1,2);//初始化，2号石头只能从前一块（1号）石头跳来
	//注：不用初始化dp[1]（它本来就是0）
	
	for(int i=3;i<=n;i++)
		dp[i]=min(dp[i-1]+cost(i,i-1),dp[i-2]+cost(i,i-2));
	
	printf("%d",dp[n]);
	return 0;
}

```

---

## 作者：lsw1 (赞：1)

这题数据范围 $N\le10^5$ ,只有 $O(N)$ 的算法才能通过，很明显要用DP。

状态： $f_i$ 表示青蛙到达第 $i$ 块石头需要的最小总费用；

转移方程：第 $i$ 块石头只能由第 $i-1$ 或 $i-2$ 块石头转移过来，所以：
$$f_i=\min(|h_{i}-h_{i-1}|+f_{i-1},|h_i-h_{i-2}|+f_{i-2})$$
时间复杂度 $O(N)$ 。

最后注意一下边界条件就可以通过此题了。

代码：
```cpp
#include <iostream>
#include <cmath>
using namespace std;
const int MAXN = 1e5;
const int INF = 2147483647;
int a[MAXN + 5],f[MAXN + 5];
int main()
{
	int n;
	cin >> n;
	for(int i = 1;i <= n;i++)
	{
		cin >> a[i];
	}
	for(int i = 1;i <= n;i++)
	{
		f[i] = INF;
	}
	f[1] = 0;//初始值，注意要设成无穷大
	for(int i = 2;i <= n;i++)//转移
	{
		f[i] = min(f[i],f[i - 1] + abs(a[i] - a[i - 1]));
		if(i > 2)//注意要判断一下
		{
			f[i] = min(f[i],dp[i - 2] + abs(a[i] - a[i - 2]));
		}
	}
	cout << f[n];
	return 0;
}
```

---

## 作者：SqrtSecond (赞：1)

一道非常经典的dp题。

我们先用$dp_i$表示跳到第$i$块石头上所用的最小费用

所以如果青蛙是从第$i-2$块石头跳过来的那么$dp_i=dp_{i-2}+|h_i-h_{i-2}|$

从第$i-1$块石头跳过来的那么$dp_i=dp_{i-1}+|h_i-h_{i-2}|$

因为是最小费用

所以我们对上两种情况去最小值

得到状态转移方程：

### $dp_i=\min{(dp_{i-2}+|h_i-h_{i-2}|,dp_{i-1}+|h_i-h_{i-2})}$

再线性递推就好啦！

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,h[1000100],dp[1000100];
int main()
{
	cin>>n;
	for(int i=1;i<=n;++i)cin>>h[i];
	dp[2]=abs(h[2]-h[1]);//别忘了初始化 
	for(int i=3;i<=n;++i)
	dp[i]=min(dp[i-2]+abs(h[i]-h[i-2]),dp[i-1]+abs(h[i]-h[i-1]));//状态转移 
	cout<<dp[n];
	return 0;//养成好习惯 
}
```


---

## 作者：きりと (赞：1)

**[题目传送门](https://www.luogu.com.cn/problem/AT4522)**

### 题目大意

见题面

### 解题思路

拿到题，首先考虑$DFS$，然后一看数据范围$2≤N≤10^5$显然会TLE

只好考虑$DP$：

- #### 状态：

  $f[i]$表示跳到第$i$块石头所需要的最小总费用

- #### 转移：

  由于$f[i]$可以由$f[i-1]$或$f[i-2]$跳到，两者**跳到$f[i]$**的费用分别为$abs(h[i]-h[i-1])$和$abs(h[i]-h[i-2])$，很容易就能推出状态转移方程：
$f[i]=min(f[i-1]+abs(h[i]-h[i-1]),f[i-2]+abs(h[i]-h[i-2]))$

- #### 初始：

  $f[1]=0,f[2]=abs(h[2]-h[1])$，因为原来青蛙就在$1$号石头，不需要费用，而$2$号石头只能由$1$号石头跳过来，所$f[2]$就是$abs(h[2]-h[1])$

- #### 答案：

  $f[n]$

- #### 时间复杂度：

  $O(n)$

### 算法优化：

我们发现，对于每一个$f[i]$，它的值只与$f[i-1],f[i-2]$有关，那么我们可以用滚动数组优化空间，这里我选择把滚动数组改成三个数——$s1,s2,s3$

$PS$：~~步步深入，精益求精，这应该也是一个$OIer$应有的品质吧~~

### 代码实现：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int h[N];
int main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>h[i];
	}
	int s1=0,s2=abs(h[2]-h[1]),s3;  //初始化
	if(n==1)
	{
		cout<<0<<endl;
		return 0;
	}
	if(n==2)
	{
		cout<<s2<<endl;
		return 0;
	} //特判n是否≤2
	for(int i=3;i<=n;i++)
	{
		s3=min(s2+abs(h[i]-h[i-1]),s1+abs(h[i]-h[i-2]));   //转移
		s1=s2;    //更新s1,s2的值
		s2=s3;
	}
	cout<<s3<<endl;
	return 0;
}
```



---

## 作者：Doqin07 (赞：1)

### 这题不难
#### 翻译题目里有，很清晰，这里就不写了
- #### 设$dp[i]$表示跳到第$i$块石头时所用体力的最小值
- #### 	则$dp[1]=0$，第$1$块石头第$1$块石头代价为0
- #### $dp[2]=|h2-h1|$, 从第$1$块石头到第$2$块耗费代价为$h2-h1$
- #### 则$dp[i]$（$i>=3$) 只用考虑是从上一个石头调过来亦是从上两个石头跳过来，两个所花费的代价取$min$即可,
- #### 上一个石头跳过来为$dp[i-1]+abs(h[i]-h[i-1])$，每次加上新的花费即可
- #### 上两个石头同上，把下标改变即可$dp[i-2]+abs(h[i]-h[i-2])$

### 核心Code
```c
dp[1]=0;
dp[2]=abs(h[2]-h[1]);
for(int i=3;i<=n;++i)
	dp[i]=min(dp[i-1]+abs(h[i]-h[i-1]),dp[i-2]+abs(h[i]-h[i-2]));
```



------------
### 求过QwQ

---

## 作者：出言不逊王子 (赞：1)

简单题。

我们假设状态`f[i]`为从树桩$i$跳到树桩$n$所需要的的最短距离。

正面思考较难，不如反着想：从第$n$根树桩开始跳，一直跳到第$1$根为止。

显然`f[n]`是$0$。

根据题意，第$i$根树桩可以跳到第$i+1$或第$i+2$根树桩上，那么反过来，第$i$根树桩只能从第$i+1$和第$i+2$根树桩跳过来。

那么就不难列出转移方程了：

$$f_i=\begin{cases}0&n\\|h_n-h_{n-1}|&n-1\\\min(f_{i+2}+|h_i-h_{i+2}|,f_{i+1}+|h_i-h_{i+1}|)&\text{其他情况}\end{cases}$$

其他细节见代码。

代码：

```cpp
    #include<bits/stdc++.h>
    using namespace std;
    const int N=100001;
    #define fs(i,x,y,z) for(int i=x;i<=y;i+=z)
    #define ft(i,x,y,z) for(int i=x;i>=y;i+=z)
    #define dis(i,j) abs(a[i]-a[j])
    int a[N],f[N];
    int main(){
    	int n;cin>>n;
    	fs(i,1,n,1) cin>>a[i];
    	f[n]=0;
    	f[n-1]=dis(n-1,n);
    	ft(i,n-2,1,-1){
    		f[i]=min(f[i+2]+dis(i+2,i),f[i+1]+dis(i+1,i));
    	}
    	cout<<f[1];
    	return 0;
    }
```

最后宣传[博客](zeta.connectakioi.cf)，欢迎注册~

---

## 作者：小豆子范德萨 (赞：1)

- 解题思路

1）题目看起来比较直白，直接dfs来一发吧

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5+10;
int a[maxn];
int ans = 1e9+10;
int n;

void dfs(int step,int sum) {	//step下一步要跳的位置 
	if(step == n) {		//到了最后一块石头
		ans = min(ans,sum);
		return;
	}
	if(sum > ans) return;
	dfs(step+1,sum+abs(a[step]-a[step+1]));	//挑一部 
	dfs(step+2,sum+abs(a[step]-a[step+2]));	//跳两步
}

int main() {
	cin>>n;
	for(int i =1;i<= n;i++) cin>>a[i];
	dfs(1,0);
	cout<<ans;
	return 0;
} 

```
暴力搜索超时了，试试递推的DP写法吧！

2)递推（动态规划）

dp数组：dp[i]代表从起点到i位置的花费

dp边界： 
- dp[1] = 0、（起点就在1位置）
- dp[2] = abs(a[2]-a[1])

状态转移方程：
设dp[i]为i从3到n的某个石头位置，那么要求得dp[i]我们可以将问题转移到dp[i-1]和dp[i-2]两种情况上来（因为可以从i-1跨一步，i-2位置跨2步过来i位置）、所以状态转移方程:
	
    dp[i] += min(dp[i-1] + abs(a[i] - a[i-1]),dp[i-2] + abs(a[i] - a[i-2]))、

最后输出dp[n]就是答案了

- 代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5+10;
int a[maxn];
int dp[maxn];		//dp[i]:从起点到i的最小费用 

int main() {
	int n;cin>>n;
	for(int i = 1;i <= n;i++) cin>>a[i];
	dp[1] = 0;
	dp[2] = abs(a[2] - a[1]);
	for(int i = 3;i <= n;i++) {	
		dp[i] += min(dp[i-1] + abs(a[i] - a[i-1]),dp[i-2] + abs(a[i] - a[i-2]));
	}
	cout<<dp[n];
	return 0;
}
```




---

## 作者：chenxia25 (赞：1)

>### [洛谷题目页面传送门](https://www.luogu.com.cn/problem/AT4522) & [AtCoder题目页面传送门](https://atcoder.jp/contests/dp/tasks/dp_a)

>有$n$个石头，第$i$个石头高度为$a_i$。青蛙初始站在石头$1$上。当青蛙在石头$i$上时，它可以跳到石头$j=i+1$或石头$j=i+2$（如果存在的话），花费的代价为$|a_j-a_i|$。求青蛙跳到石头$n$的最小代价。

>$n\in\left[2,10^5\right]$。

设$dp_i$表示跳到石头$i$的最小代价。边界是$dp_1=0$，目标是$dp_n$，状态转移方程是$dp_i=\min\begin{cases}dp_{i-1}+|a_i-a_{i-1}|\\dp_{i-2}+|a_i-a_{i-2}|&i\geq3\end{cases}$（尝试从石头$i-1$或石头$i-2$跳过来）。时间复杂度$\mathrm O(n)$。

下面是AC代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=100000;
int n;; 
int a[N+1];
int dp[N+1];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	dp[2]=abs(a[2]-a[1]);//转移 
	for(int i=3;i<=n;i++)dp[i]=min(dp[i-1]+abs(a[i]-a[i-1]),dp[i-2]+abs(a[i]-a[i-2]));//转移 
	cout<<dp[n];//目标 
	return 0;
}
```

---

## 作者：信守天下 (赞：0)

## [洛谷传送门](https://www.luogu.com.cn/problem/AT4522)
## [AT 传送门](https://atcoder.jp/contests/dp/tasks/dp_a)
## 思路
从每一个石头 $i$ 可以转移到石头 $i + 1$ 或石头 $i + 2$。

需要求出转移到石头 $N$ 最小代价，显然使用动态规划。

可以将状态设计为当前在的石头 $i$，最优化属性为到石头 $i$ 的最小代价。

令 $dp[i]$ 表示到石头 $i$ 的最小代价，可以转移到 $dp[i + 1]$ 和 $dp[i + 2]$。

则状态转移方程为：
$$dp[i] = \min(dp[i - 1] + \left\vert h[i] - h[i - 1]\right\vert, dp[i - 2] + \left\vert h[i] - h[i - 2]\right\vert)$$
直接求解即可。
## code
~~~cpp
#include <cmath>
#include <iostream>
using namespace std;
const int kMaxN = 1e5 + 1;
int dp[kMaxN];
int h[kMaxN];
int n;
int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> h[i];
  }
  dp[2] = abs(h[1] - h[2]);
  //dp[2]只能从dp[1]转移过来，所以dp[2] = abs(h[1] - h[2])。
  //预处理dp[1]和dp[2]，就不需要在dp时特判越界了，直接从3开始求解。
  for (int i = 3; i <= n; i++) {
    dp[i] = min(dp[i - 1] + abs(h[i] - h[i - 1]), dp[i - 2] + abs(h[i] - h[i - 2]));
  }
  cout << dp[n];
  return 0;
}
~~~

---

## 作者：Zirnc (赞：0)

[ChungZH's blog](https://chungzh.cn) · [ChungZH's portfolio](https://chungzh.cc)

这是一道简单的线性动态规划 dp 题。

第 $i$ 个石头只能从第 $i-1$ 个石头或者第 $i-2$ 个石头跳过去。

设 $dp_i$ 为青蛙到第 $i$ 块石头的最小代价，那么 $dp_i = min(dp_{i-2} + abs(h_i - h_{i - 2}), dp_{i-1} + abs(h_i - h_{i-1}))$。

注意：$dp_1 = 0, dp_2 = |h_2-h_1|$。

核心代码：

```cpp
  dp[1] = 0;
  dp[2] = abs(h[2] - h[1]);
  for (int i = 3; i <= n; i++) {
    dp[i] =
        min(dp[i - 2] + abs(h[i] - h[i - 2]), dp[i - 1] + abs(h[i] - h[i - 1]));
  }
```

---

