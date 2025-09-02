# ビルの飾り付け (Building)

## 题目描述

### 题目简述

给定一个长为 $n$ 的数列 $a$，求其最长上升子序列的长度。

## 说明/提示

对于全部测试点，数据保证 $1\le n\le 1000$，$1\le a_i\le 10000$。

# 题解

## 作者：sea_bird (赞：5)

# 本题是一道经典的动规题。
[题目传送门](https://www.luogu.com.cn/problem/AT_joisc2007_buildi)。

那么什么是动规呢？~~动规就是动态规划~~。
动态规划是一种分阶段求解决策问题的思想，有点类似于分治算法，将数据拆分成子问题处理后，再将子问题的解组合起来得到原问题的解。动态规划的各子问题的选取依赖于当前所面临的状态，而又影响之后的进程。

那么这题为什么不能用贪心呢？我来举个例子。

```
7 1 2 9 3 4 5 6
```

用贪心来写会输出 $3$，用动态规划来写则会输出 $6$。

换句话讲就是贪心求的是局部最优解，而动态规划求的是全局最优解。

## 代码。
让我们来看一下题目：求一个数列最长上升子序列的长度，也就是说明我们要找的数列应满足升序~~废话~~。

根据动态规划的原理，从后往前遍历（这样可以省去一些判断和比较）。

从倒数第二项往前处理，比较是否大于前一个数。

在 $i+1$，$i+2$，……，$n$ 中找出比 $ans[i][3]$ 大的最长长度 $x$。

当 $x>0$，则 $ans[i][2]=x+1$。

我来画个表格来帮各位理解一下。

|$1$|$2$|$3$|$4$|$5$|$6$|$7$|$8$|$9$|
|-----------:|-----------:|-----------:|-----------:|-----------:|-----------:|-----------:|-----------:|-----------:|
|$3$|$7$|$5$|$9$|$8$|$10$|$10$|$11$|$9$|
|$5$|$4$|$4$|$3$|$3$|$2$|$2$|$1$|$1$|

从倒数第二列开始（也就是第 $8$ 列）。

第 8 列是 $11$ 后面没有更大的了，所以最多有 $1$ 个。

第 7 列是 $10$ 后面 $11$ 更大，所以最多有 $2$ 个。

第 6 列是 $10$ 后面 $11$ 更大，所以最多有 $2$ 个。

第 5 列是 $8$ 后面 $10$ 和 $11$ 更大，所以最多有 $3$ 个。

第 4 列是 $9$ 后面 $10$ 和 $11$ 更大，所以最多有 $3$ 个。

第 3 列是 $5$ 后面 $9$（或 $8$）$10$，$11$ 更大，所以最多有 $4$ 个。

第 2 列是 $7$ 后面 $9$（或 $8$）$10$，$11$ 更大，所以最多有 $4$ 个。

第 1 列是 $3$ 后面 $7$（或 $5$）$9$（或 $8$）$10$，$11$ 更大，所以最多有 $5$ 个。

而答案就是 $5$。

```cpp
#include<bits/stdc++.h>//万能头
using namespace std;
int ans[10005][1005];
int main()
{
	int n,i,j,x,y;
	cin>>n;
	for(i=1;i<=n;i++){//输入序列
		cin>>ans[i][1];
		ans[i][2]=1;//初始化
	}
	
	for(i=n-1;i>=1;i--){//求最长上升子序列
		x=0;
		for(j=i+1;j<=n;j++){
			if((ans[j][1]>ans[i][1])&&(ans[j][2]>x)){//注意是大于号
				x=ans[j][2];
			}
			if(x>0){
				ans[i][2]=x+1;
				
			}
		}
	}
	for(i=1;i<=n;i++){//求最长上升子序列的起始位置
		if(ans[i][2]>ans[y][2]){
			y=i;
		}
	}
	cout<<ans[y][2]<<endl;//输出
	return 0;//好习惯
}
```

[AC](https://www.luogu.com.cn/record/151899940)。

~~本人也是蒟蒻，概念模糊的地方翻了书看了百科~~。

---

## 作者：Stars_visitor_tyw (赞：4)

## AT_joisc2007_buildi ビルの飾り付け (Building) 题解
### 分析
动规板子题。

状态：$dp_i$ 表示以 $i$ 结尾的最长上升子序列。

答案：由于以 $n$ 结尾的最长上升子序列不一定是答案，所以对 $dp_i$ 取最大值。

状态转移方程：枚举 $i$，在每一次枚举时找出所有可能的上一个转移过来的点，当一个下标小于 $i$ 且值也小于 $a_i$ 的数出现时，$dp_i=\max(dp_i,dp_j+1)$。

初始状态：由于每个元素自己可以算作一个上升子序列，所以初始时 $dp_i = 1$。

注意：AT 的题要换行。

### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n, a[500005], dp[500005], ans=-1;
signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		dp[i]=1;
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<i;j++)
		{
			if(a[j]<a[i])
			{
				dp[i]=max(dp[i],dp[j]+1);
			}
		}
		ans=max(dp[i],ans);
	}
	cout<<ans<<"\n";
}
```

---

## 作者：xuchuhan (赞：4)

## 思路

设 $dp_i$ 表示以 $a_i$ 结尾的最长上升子序列的长度。显然 $dp_i$ 的初始值为 $1$，即最长上升子序列中只有它自己。

那么易得转移方程：对于所有的 $j$ 使得 $j<i$ 且 $a_j<a_i$，有 $dp_i=\max(dp_i,dp_j+1)$，即 $a_i$ 可以接在以 $a_j$ 结尾的最长上升子序列后。

最后答案即为 $\max_{i=1}^n dp_i$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e3+5;
int n,ans;
int a[N],dp[N];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		dp[i]=1;
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<i;j++)
			if(a[i]>a[j])
				dp[i]=max(dp[i],dp[j]+1);
	for(int i=1;i<=n;i++)
		ans=max(ans,dp[i]);
	cout<<ans<<"\n";
	return 0;
} 
```

---

## 作者：Pink_Cut_Tree (赞：2)

# AT_joisc2007_buildi ビルの飾り付け (Building) 题解

最长上升子序列模板题。

### 解析

我们钦定 $f_i$ 为以 $a_1,a_2,\ldots,a_i$ 的最长上升子序列的长度。

对于 $\forall 1\leq i<j\leq n$，若 $a_j>a_i$，则 $f_j=\text{max}(f_j,f_i+1)$，形式化地，我们有：

$f_k=\left\{\begin{matrix}
 f_i+1 & a_k>a_i\\
 f_i &\text{otherwise} 
\end{matrix}\right.$（此处 $1\leq i<k\leq n$）。

所以我们不难写出代码。

### 代码

```cpp
#include<iostream>
using namespace std;
const int N=1024; 
int n,num[N],f[N],ans;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>num[i];
		f[i]=1;
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=i-1;j++){
			if(num[j]<num[i]){
				f[i]=max(f[i],f[j]+1);
			}
		}
	}
	for(int i=1;i<=n;i++){
		ans=max(ans,f[i]);
	}
	cout<<ans<<"\n";
return 0;
}
```

### 题外话

1. 本题为远古 AT 题，最后请输出换行，不然会喜提 $0$ 分。

1. 站上同样有原题：[B3637 最长上升子序列](https://www.luogu.com.cn/problem/B3637)，大家可以参考练习。

---

## 作者：Ice_rnfmabj (赞：1)

一眼盯真，鉴定为动规板子！

状态转移方程：```f[i]=max(f[i],f[j]+1);```

原因？首先要知道代码中的 $f[i]$ 表示 $a_1$ 到 $a_i$ 中的最长上升子序列的长度。

然后如果循环找到了一个在当前这个数之前的，比它还小的数，那么就更新 $f[i]$ 的值。怎么个更法？你找到了这个 比 $a[i]$ 小的 $a[j]$，那么从 $a_1$ 到 $a_j$ 的最长上升子序列的长度就是 $f[j]$，你只需要把它再加一，得到的就是 $f[i]$。不过别忘了，这个可能比原本的 $f[i]$ 要小，那么需要取大的一个。

```
#include<bits/stdc++.h>
using namespace std;
int a[5001],f[5001],n,ans;
int main(){
	cin>>n;//输入 n。
	for(int i=1;i<=n;i++){
		cin>>a[i];//输入 n 个数。
		f[i]=1;//将 f 数组初始化为 1（因为自己本身也是一个长度为 1 的上升子序列）。
	}
	for(int i=2;i<=n;i++){
		for(int j=1;j<=i-1;j++){
			if(a[j]<a[i]) f[i]=max(f[i],f[j]+1);//动态转移方程，如果当前的 a[j] 比 a[i] 要小，说明是上升的，那么 f[i] 数组就要更新它的值。
		}
	}
	for(int i=1;i<=n;i++) ans=max(ans,f[i]);//max 出最大值。
	cout<<ans<<"\n";//别忘了换行！
    return 0;
}
```

---

## 作者：Karl_Aldrich (赞：1)

### 模版题
~~但是记得输出换行。~~

假设 $f_i$ 表示以 $a_i$ 为结尾的最长上升子序列，则显然有 $f_i=\max\{f_1,f_2,\ldots,f_{i-1}\}+1$。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin>>n;
    vector<int>a(n+1);
    for(int i=1;i<=n;i++)cin>>a[i];
    vector<int>dp(n+1);
    int ans=0;
    for(int i=1;i<=n;i++){
        dp[i]=1;
        for(int j=1;j<i;j++)
            if(a[i]>a[j])dp[i]=max(dp[i],dp[j]+1);
        ans=max(dp[i],ans);
    }
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：ZnHF (赞：1)

[题目链接](https://www.luogu.com.cn/problem/AT_joisc2007_buildi)。

# 题意简述

给定一个长度为 $n$ 的序列，求其最长上升子序列的长度。

# 题目分析

本题可以使用动态规划解决。

定义 $f_i$ 表示以 $a_i$ 结尾的最长上升子序列的长度。对于每一个小于 $i$ 的 $j$，如果 $a_i > a_j$，那么 $a_i$ 就可以接在 $a_j$ 后面构成一个长度为 $f_{j}+1$ 的上升子序列。

状态转移方程为：$f_{i}= \underset{0 \le j < i,a_{i} < a_{j}}{\max}\{f_{j}+1\}$。

目标为：$\underset{1 \le i \le n}{\max}\{f_{i}\}$。

# 代码
```cpp
#include<bits/stdc++.h>
#define endl '\n'
#define int long long
using namespace std;
int n,a[1005],f[1005],ans;
signed main(){
	std::ios::sync_with_stdio(false);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	f[1]=1;
	for(int i=1;i<=n;i++){
		for(int j=0;j<i;j++){
			if(a[i]>a[j]) f[i]=max(f[j]+1,f[i]);
		}
	}
	for(int i=1;i<=n;i++) ans=max(ans,f[i]);
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：Kle1N (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_joisc2007_buildi)

---
算法：动态规划。

设 $dp_i$ 表示以 $a_i$ 为结尾的最长上升子序列的长度，那么扫描 $1$ 到 $i-1$ 的所有 $a_j$，若 $a_j<a_i$，则说明 $a_i$ 可以接在以 $a_j$ 为结尾的最长上升子序列后面，那么对 $dp_i$ 和 $dp_j+1$ 取 $\max$ 扔进 $dp_i$ 里即可。

状态转移方程：$dp_i=\underset{1\le j<i,a_j<a_i}{\max} \left\{ dp_j+1 \right\}$；

初始状态：$\underset{1\le i\le n}{dp_i}=1$；

最终答案：$\underset{1\le i\le n}{max\left\{dp_i\right\}}$

最后输出答案别忘了换行。

具体见代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,a[1001],dp[1001],ans;
int main(){
	ios::sync_with_stdio(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		dp[i]=1;
	}
	for(int i=2;i<=n;i++){
		for(int j=1;j<i;j++){
			if(a[j]<a[i]){
				dp[i]=max(dp[i],dp[j]+1);
			}
		}
	}
	for(int i=1;i<=n;i++){
		ans=max(ans,dp[i]);
	}
	cout<<ans<<"\n";
	return 0;
}
```

---

## 作者：封禁用户 (赞：1)

本题是 LIS 的模版题。

我们可以设 $dp_{i}$ 表示以第 $i$ 个数为结尾的最长上升子序列的长度，不难得出转移方程为 $dp_{i}=\max(dp_{j}+1)\quad (j<i)$。

答案为 $\max(dp_{i})\quad (1\le i\le n)$，因为以第 $n$ 个数结尾的 LIS 不一定是最长的。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=10005;
int a[N],dp[N];
int main(){
	int n,ans=-1;
	cin>>n;
	for(int i=1;i<=n;++i){
		cin>>a[i];
		dp[i]=1;
	}for(int i=1;i<=n;++i){
		for(int j=1;j<i;++j){
			if(a[j]<a[i]) dp[i]=max(dp[i],dp[j]+1);
		}
	}for(int i=1;i<=n;++i) ans=max(ans,dp[i]);
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：__CrossBow_EXE__ (赞：0)

# 前言

这么好的 LIS 模板题居然没人发题解？

这题看旁边大佬都用 $dp$，那我也写一发。

我对此题的评判如下：

- 建议升橙

# 分析

做 dp 题一共分三步：

1. 找 $dp_i$ 的含义；
2. 写出状态转移方程；
3. 写出代码。

那么，我们就一步一步地解决掉这道模板题吧！

## 第一步：找含义

由于我们要求最长上升子序列，所以我们可以将 $dp_i$ 定义为从 $dp_1$ 到 $dp_i$ 找到的**最长上升子序列的个数**。

## 第二步：写出状态转移方程

首先，我们要初始化 $dp_i = 1$。

接着，我们要判断能够继承最大状态，也就是 $a_i>a_j$。

最后，如果上面的判断成立，说明 $a_i$ 可以延续我们以 $a_j$ 作为结尾的上升子序列，所以我们就可以写出状态转移方程：$dp_i = \max(dp_i,dp_j+1)$。

## 第三步：写出代码

代码如下：

```cpp
/*
LIS 板子题
Step 1：找dp含义
Step 2：写状态转移方程
Step 3：写出代码 
*/ 

#include<iostream>
using namespace std;
int a[1005],dp[1005];//建两个数组，a里是输入的数据，dp是每一个数的状态，见下 
//dp[i]：从开头到i找到的最长上升子序列的个数 
int n; 
int main(){
	//输入 
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		dp[i]=1;//这个数本身也是一个LIS 
	}
	for(int i=2;i<=n;i++){
		for(int j=1;j<i;j++){
			if(a[i]>a[j]){//继承最大状态 
				dp[i]=max(dp[i],dp[j]+1);//状态转移方程 
			}
		}
	}
	int maxn=-0x3f3f3f3f;
	for(int i=1;i<=n;i++) maxn=max(maxn,dp[i]);//打擂台找最大值
	cout<<maxn<<endl; 
	return 0;
} 
```

![](https://i.postimg.cc/pX1p2hgd/image.png)

最后，**不要忘记换行**！

---

## 作者：lihongqian__int128 (赞：0)

# AT_joisc2007_buildi ビルの飾り付け (Building)题解
一道最长上升子序列的模板题。

## 解题思路：
每次将 $a_i$ 插到答案数组中大于等于 $a_i$ 的位置上，若答案数组的所有数都小于 $a_i$，则将 $a_i$ 加到答案数组的末尾。答案数组的长度即为答案。

### 介绍 STL 函数 lower_bound：

```lower_bound(a + 1 , a + n + 1 , val);``` 会返回 $a_1$ 到 $a_n$ 中第一个大于等于 val 的数的内存位置，若都小于 val，则返回 $a_{n + 1}$ 的内存位置。想得到下标就减去 a 数组的首地址即可。

时间复杂度为 $O(\log n)$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std ;
int n , k , a[1005] , lis[1005] , len ;
int main()
{
	ios::sync_with_stdio(0) ;
	cin.tie(0) ;
	cout.tie(0) ;
	cin >> n ;
	for(int i = 1 ; i <= n ; i++)
	{
		cin >> a[i] ;
	}
	for(int i = 1 ; i <= n ; i++)
	{
		int pos = lower_bound(lis + 1 , lis + len + 1 , a[i]) - lis ;
		lis[pos] = a[i] ;
		len = max(len , pos) ;
	}
	cout << len << '\n' ;
	return 0 ;
}
```
总时间复杂度为 $O(n \log n)$。

---

## 作者：frotms (赞：0)

# AT_joisc2007_buildi 题解
这是一道最长上升子序列的板子题。 

考虑使用 $dp$ 来解决这道题。 

首先，设定一个状态为：  
$dp_i$ 为以 $a_i$ 为结尾的最长上升子序列。

那么状态转移方程就为：  
$dp_i=\max(dp_i,dp_j+1);$

因为是最长**上升**子序列，所以要加个判断。

初始状态：因为每个点自身就是一个子序列，所以将 $dp_i$ 设为 $1$。

答案：在所有 $dp_i$ 中取最大值。　　

# code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e3+5;
long long n,a[N],dp[N],sum=-1e9;
signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		dp[i]=1;
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=i+1;j<=n;j++)
		{
			if(a[i]<a[j])//确保是上升的子序列
				dp[j]=max(dp[j],dp[i]+1);
		}
		sum=max(sum,dp[i]);
	}
	cout<<sum<<"\n";//at的题目需要换行
	return 0;
}
```

---

## 作者：GoodLuckCat (赞：0)

这题......~~其实我也不太会......~~

但是我们可以直接模拟。

可以在输入第 $i$ 个数时判断以第 $i$ 个数结尾的 LIS（最长上升子序列）的长度是多少。然后最后取前面算出来的最大值即可。

取最大值也可以边输入边算，因为算后面的结果时不会改变前面的结果。

代码如下：

```cpp
#include<iostream>
using namespace std;
int a[1001],b[1001];
int main()
{
    int n,m=-1;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        b[i]=1;
        for(int j=1;j<i;j++)if(a[j]<a[i]&&b[j]+1>b[i])b[i]=b[j]+1;
        if(b[i]>m)m=b[i];
    }
    cout<<m<<endl;
    return 0;
}
```

AC 记录：[record 151613968](https://www.luogu.com.cn/record/151613968)。

但是小心爆零。

~~我竟然有一次忘记输出了~~

另外 **AT 题目要加换行**。

---

## 作者：maomao233 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_joisc2007_buildi)  
[AT 传送门](https://atcoder.jp/contests/joisc2007/tasks/joisc2007_buildi)

本题为最长上升子序列（LIS）的板子题。双倍经验 [B3637 最长上升子序列](https://www.luogu.com.cn/problem/B3637)。

我们直接解释样例：

```
9
3 7 5 9 8 10 10 11 9
```

（在下文中，我们令代码框内第二行的序列名为 $a$，第三行的序列名为 $f$。）

首先，初始时单个数的最长上升子序列就是它本身，所以其最长上升子序列的长度为 $1$：

```
9
3 7 5 9 8 10 10 11 9
1 1 1 1 1  1  1  1 1
```

然后我们依次判断 $a_i(2\le i\le n)$。

- 当 $i=2$ 时：  
可以看到 $\color{red}7>3\ (f_1)$，所以序列 $a_1a_2$ 的最长上升子序列的长度为 $\max\{f_2,f_1+1\}=f_1+1=2$：

  ```
  9
  3 7 5 9 8 10 10 11 9
  1 2 1 1 1  1  1  1 1
  ```

- 当 $i=3$ 时：  
可以看到 $\color{red}5>3\ (f_1)$，$\color{blue}5<7\ (f_2)$，所以序列 $a_1a_2a_3$ 的最长上升子序列的长度为 $\max\{f_3,f_1+1\}=f_1+1=2$：

  ```
  9
  3 7 5 9 8 10 10 11 9
  1 2 2 1 1  1  1  1 1
  ```

- 当 $i=4$ 时：  
可以看到 $\color{red}9>3\ (f_1)$，$\color{red}9>7\ (f_2)$，$\color{red}9>5\ (f_3)$，所以序列 $a_1a_2a_3a_4$ 的最长上升子序列的长度为 $\max\{f_4,\max\{f_1,f_2,f_3\}+1\}=f_2+1=f_3+1=3$：

  ```
  9
  3 7 5 9 8 10 10 11 9
  1 2 2 3 1  1  1  1 1
  ```

- 当 $i=5$ 时：  
可以看到 $\color{red}8>3\ (f_1)$，$\color{red}8>7\ (f_2)$，$\color{red}8>5\ (f_3)$，$\color{blue}8<9\ (f_4)$，所以序列 $a_1a_2a_3a_4a_5$ 的最长上升子序列的长度为 $\max\{f_5,\max\{f_1,f_2,f_3\}+1\}=f_2+1=f_3+1=3$：

  ```
  9
  3 7 5 9 8 10 10 11 9
  1 2 2 3 3  1  1  1 1
  ```

- 当 $i=6,7,8,9$ 时：  
$\cdots\ \cdots$

最后长这个样子：

```
9
3 7 5 9 8 10 10 11 9
1 2 2 3 3  4  4  5 4
```

可以看到以 $11$ 结尾的一些序列（例如 $[3,7,8,10,11]$），最长上升子序列的长度为 $5$，答案是最大的。也就是说我们答案取 $\max\{f_1,f_2,\cdots,f_9\}=5$ 即可。

最后按照此思路模拟即可，时间复杂度 $\mathcal{O}(n^2)$，且 $1\le n\le1000$，可以通过。于是我们便完成了本题。

有代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int ll
template<typename T>inline void rd(T &x){x=0;char c=getchar();bool f=0;while(!isdigit(c)){if(c=='-'){f=1;}c=getchar();}while(isdigit(c)){x=(x<<3)+(x<<1)+(c^'0');c=getchar();}if(f){x=~(x-1);}}
template<typename T,typename...Args>inline void rd(T &x,Args&...args){rd(x);rd(args...);}
inline void wt(int x){if(x<0){putchar('-'),x=-x;}if(x>9){wt(x/10);}putchar(x%10+'0');}
#define pc(x) putchar(x)
#define wtl(x) wt(x),pc('\n')
#define kg pc(' ')
#define hh pc('\n')
#define lb(x) x&-x
#define itn int
inline string its(int x){stringstream ss;string s;ss<<x;ss>>s;return s;}
inline int sti(string s){stringstream ss;int x;ss<<s;ss>>x;return x;}
inline string jia(string a1,string b1){int a[10010],b[10010],c[10010];int lena=a1.size(),lenb=b1.size();for(int i=0;i<lena;i++){a[i]=a1[lena-1-i]-'0';}for(int i=0;i<lenb;i++){b[i]=b1[lenb-1-i]-'0';}int lenc=max(lena,lenb),t=0;for(int i=0;i<lenc;i++){c[i]=a[i]+b[i]+t;if(c[i]>=10){t=1,c[i]%=10;}else{t=0;}}if(t==1){lenc++;c[lenc-1]=1;}string s;for(int i=lenc-1;i>=0;i--){s+=c[i]+'0';}return s;}
inline string jian(string a1,string b1){if(a1.size()<b1.size()||a1.size()==b1.size()&&a1<b1){pc('-'),swap(a1,b1);}int a[10010],b[10010],c[10010];int lena=a1.size(),lenb=b1.size();for(int i=0;i<lena;i++){a[i]=a1[lena-1-i]-'0';}for(int i=0;i<lenb;i++){b[i]=b1[lenb-1-i]-'0';}int lenc=lena;for(int i=0;i<lenc;i++){if(a[i]<b[i]){a[i+1]--,a[i]+=10;}c[i]=a[i]-b[i];}while(lenc>=1&&c[lenc-1]==0){lenc--;}string s;for(int i=lenc-1;i>=0;i--){s+=c[i]+'0';}return s;}
inline int qpow(int a,int b,int p){int sum=1;while(b){if(b&1){sum=(sum*a)%p;}b>>=1;a=(a*a)%p;}return sum;}
inline int qp(int a,int b){int sum=1;while(b){if(b&1){sum*=a;}b>>=1;a*=a;}return sum;}
int a[1010],f[1010];
signed main()
{
	int n;
	rd(n);
	for(int i=1;i<=n;i++)
	{
		rd(a[i]),f[i]=1;
	}
	for(int i=2;i<=n;i++)
	{
		for(int j=1;j<i;j++)
		{
			if(a[i]>a[j])
			{
				f[i]=max(f[i],f[j]+1);
			}
		}
	}
	int ans=0;
	for(int i=1;i<=n;i++)
	{
		ans=max(ans,f[i]);
	}
	wtl(ans);
	return 0;
}
```

---

