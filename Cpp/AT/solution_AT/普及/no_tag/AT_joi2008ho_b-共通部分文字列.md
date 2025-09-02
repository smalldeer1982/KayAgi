# 共通部分文字列

## 题目描述

[problemUrl]: https://atcoder.jp/contests/joi2008ho/tasks/joi2008ho_b



# 题解

## 作者：Elma_ (赞：5)

## Description

[传送门](https://www.luogu.com.cn/problem/AT2418)

给出两行两个字符串，长度不超过4000，求两个字符串最长的相同子串长度（要求连续）。

## Solution
简单dp(递推？)题。

$dp(i,j)$表示以字符串$a$的第$i$个字符和字符串的第$j$个字符为结尾时两个字符串的最长连续相同子串长度。

当字符串$a$的第$i$个字符和字符串的第$j$个字符相等时，容易得出递推式：$dp(i,j)=dp(i-1,j-1)+1$，每一次赋值时更新答案即可。

还要注意一点，字符串的第一个下标为$0$，但是按照递推式这里可能要$-1$，此时数组会越界。所以可以在两个字符串前面加一个空字符，递推时从下标$1$开始就可以了。

## Code

```cpp
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define maxn 4005
using namespace std;

string a, b;
int dp[maxn][maxn], ans;

int main(void)
{
	cin >> a >> b;
	a = " " + a, b = " " + b;//防数组越界
	for (int i = 1;i < a.size();i++)//防数组越界
		for (int j = 1;j < b.size();j++)
			if (a[i] == b[j])
			{
				dp[i][j] = dp[i - 1][j - 1] + 1;//递推
				ans = max(ans, dp[i][j]);//更新答案
			}
	cout << ans << endl;
	return 0;
}
```


---

## 作者：Steven_Gerrard (赞：3)

  题意简单明了，就是字符串相同的最大匹配序列，建议与[P3375](https://www.luogu.com.cn/problem/P3375)一起食用。
  
  本题算一道较为简单的递推题，定义二维数组 $n$ 代表在 $n_{i,\,j}$ 时连续字符串有多少个，当下标为 $i,j$ 时，如果字符串相同，$n_{i,\,j}$ 要在 $n_{i-1,\,j-1}$ 的基础上加 $1$ ，并易得公式 $ans=\max(n_{i-1,\,j-1}+1,ans)$ 将连续的数与 $ans$ 打擂台。但特别注意若循环从 $0$ 开始则会越界（为什么）？ 所以需要在字符串输入后将 $a_{0}$ 和 $b_{0}$ 变为零，且将整个字符串向后挪一位。
#   std
```cpp
#include<iostream>
#include<string>
using namespace std;
int ans,sum;
int n[4001][4001];
int main()
{
	string a,b;
	cin>>a>>b;
	a='0'+a,b='0'+b;//避免越界
	for(int i=1;i<a.size();++i)
	{
		for(int j=1;j<b.size();++j)
		{
			if(a[i]==b[j])//若连续
			{
				ans=max(n[i-1][j-1]+1,ans);//递推公式，打擂台。
				n[i][j]=n[i-1][j-1]+1;
			}
		}
	}
	cout<<ans;
}
```


---

## 作者：TRZ_2007 (赞：3)

# Description  
给你两个字符串，要求你就它们的最长公共子序列（要求连续）。

# Solution  
观察范围得到 $1\le n\le 4000$，所以 $\mathcal{O(n^2)}$  的做法是稳稳的能过的。 但是！空间限制特别的毒瘤，所以我们需要使用 ```unsigned short``` 来卡空间，而数字肯定是存的下的，因为最长就是 $n$，且 $n < 65535$。  

重点到了 $dp$，我们设 $f_{i,j}$ 表示第一个字符串到了 $i$ 的位置，第二个字符串到了 $j$ 的位置，其中 $i,j$ 必须取到。那么我们分类讨论。  
- 1： $a_i \neq b_j$ 时，则当前状态无解，$f_{i,j}=0$ 。  
- 2： $a_i = b_j$ 时，则当前的解为之前 1 位的长度加 1，即： $f_{i,j} = f_{i-1,j-1} + 1$ 。

对所有的 $f_{i,j}$ 取最大值就可以了。

# Code
```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 4002;

unsigned short f[N][N],ans;
string a,b;

int main() {
	cin >> a >> b;
	a = "#" + a; b = "#" + b;
	for(int i = 1;i < a.size();i++) {
		for(int j = 1;j < b.size();j++) {
			if(a[i] == b[j]) f[i][j] = f[i - 1][j - 1] + 1;
			ans = max(ans,f[i][j]);
		}
	}
	cout << ans << "\n";
	return 0;
}
```

---

## 作者：李小泽呵呵哒 (赞：1)

看各位大佬都没有发布题解，那我这个~~躲在角落里颤颤发抖的~~蒟蒻就来发一篇吧。设两个字符串分别为s1、s2，它们的长度分别为len1、len2，可以构造一个长len1、len2的二维矩阵g，用来记录以s1[i]、s2[j]结尾的最长子串长度，然后可以分为三部分：
1. 矩阵赋值：当s1[i]==s2[j]时，g[i][j]=1。
2. 计算子串长度：这里可以用到一种近似于前缀和的思想，当g[i][j]等于1时，就累加上以s1[i-1]、s2[j-1]结尾的最长子串，即g[i][j]+=g[i-1][j-1]。
3. 比较最大值：遍历矩阵，用打擂台的方法求出最大值。

本蒟蒻偷懒了一下，把三个步骤放在一起写了，代码如下：


------------
```cpp
#include<bits/stdc++.h>
using namespace std;
string s1,s2;
int g[4005][4005];//二维矩阵
int main()
{
	cin>>s1>>s2;
	s1='@'+s1;//在字符串前加上一个前置字符
	s2='@'+s2;//方便处理，防止数组越界
	int len1=s1.size()-1;//因为字符串下标从0开始
	int len2=s2.size()-1;//所以要减1
	int maxn=0;
	for(int i=1;i<=len1;i++)
		for(int j=1;j<=len2;j++)
			if(s1[i]==s2[j])
			{
				g[i][j]=1;//1.矩阵赋值
				g[i][j]+=g[i-1][j-1];//2.计算子串长度
				maxn=max(maxn,g[i][j]);//3.统计最大值
			}
	cout<<maxn<<endl;
	return 0;
}
```


---

## 作者：sto_yyrdxh_orz (赞：0)

### 题目大意：
输入 $2$ 个字符串，输出两个字符串最长相同子串的长度。

### 题目分析：
输入后分别加上一个字符，处理越界，然后用双从循环按位比较，相同就加 $1$，输出他们的最大值。

### 具体代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
string a, b;
int dp[4010][4010];
int ans=-1e9;
//要求最大值，初始设为很小的数 
int main(){
    cin>>a>>b;
    //输入 
	a=' '+a;
	b=' '+b;
	//防越界处理 
    int len1=a.size();
	int len2=b.size();
	//长度 
    for(int i=1;i<len1;i++){
		for(int j=1;j<len2;j++){
			//按位比较 
			if(a[i]==b[j]){
				//两个字符串的这一位相等 
				dp[i][j]=dp[i-1][j-1]+1;
				//长度加一 
				ans=max(ans, dp[i][j]);
				//求最大值 
			}
		}
	}
    cout<<ans;
    //输出答案 
    return 0;
}
```

---

## 作者：封禁用户 (赞：0)

这是本蒟蒻的第 $39$ 篇题解，AT2418。

-----

本题为初学动态规划的 OIer 的必做题，形式化来讲，这个模型叫“最长公共子序列”，即 $\text{LCS}$。

首先我们来分析这个问题。如何求最长公共子序列呢？你可能会去建立一个四层循环，去枚举两个字符串的 $i,j$ 位置，然后定义函数去判断是否相等，再去与目前的最大值作比较，最后输出。

可是这个方法效率太低了。我们设 $|a|$ 为字符串 $a$ 的长度，$|b|$ 为 $b$ 的长度，那么时间复杂度就是 $\mathcal{O}(|a|^2|b|^2)$。为什么？你定义了两个 $0 \sim |a|$ 的循环，两个 $0 \sim |b|$ 的循环。乘在一起就是 $|a|^2|b|^2$。

有没有更快捷的方法呢？当然有。你在小奥中学过递推吗？OI 中的**动态规划**思想本质上就是递推。我们可以建立一个二维数组，用来存储字符串 $a$ 的 $1 \sim i$ 和字符串 $b$ 的 $1 \sim j$ 这两个子串的最长公共子序列。

怎么求？很简单。判断这个位置上的 $a_i$ 和 $b_j$，

$f(i,j)=\begin{cases}f(i-1,j-1)&a_i \neq b_j\\f(i-1,j-1)+1&a_i = b_j\end{cases}$

也就是判断这个位置上的两个字符是否相等，相等的话 $f(i,j)$ 显然就是上一个点 $f(i-1,j-1)$ 的长度再加 $1$，因为两个字符串的这个点也是相等的。

再优化一下，我们直接在计算出 $f(i,j)$ 之后用一个变量 $lcs$ 去获得目前的最大值。因为最长公共子序列不可能是负数，所以把 $lcs$ 的初值设为 $0$ 就可以了。

这就是动态规划（$\text{DP}$）的奇妙之处，你无需计算每一个点，根据一个推出来的递推公式就可以由前一个点扩展到这个点，从而降低复杂度，使程序运行得更快。

下面在写代码之前，我想明确两个本题的“坑”：

1. 建议在字符串输入后在最前面加一个空格，因为字符串遍历是从 $0 \sim |k|$ 的，如果不加很有可能出现数组越界。
2. $lcs$，$f$ 变量要设成 `short` 类型，否则会 $\text{MLE}$。

然后就是代码了：

```cpp
#include <bits/stdc++.h>
using namespace std;

string a, b;
short f[4001][4001];
short lcs=0; // short

int main(){
    cin>>a>>b, a=' '+a, b=' '+b; // 防止出现-1等奇葩情况
    int al=a.size(), bl=b.size();
    
    for (int i=1; i<al; i++)
        for (int j=1; j<bl; j++)
            if (a[i]==b[j]) f[i][j]=f[i-1][j-1]+1, lcs=max(lcs, f[i][j]); // dp
                
    cout<<lcs<<endl;
    return 0;
}
```

你看，我们使用动态规划后，时间复杂度就由 $\mathcal{O}(|a|^2|b|^2)$  骤降到 $\mathcal{O}(|a||b|)$ 了。

在最后，希望大家都可以把动规学好，~~其实动规学好在有些年份就能拿到 tg1= 了~~。

谢谢大家。

---

## 作者：scp020 (赞：0)

一道练习最长公共子串的题。

### 题意

给定两个字符串，让你求出两个字符串的最长公共子串。

### 解法

求最长公共子串，所以考虑动态规划，时间复杂度为 $O(nm)$，其中 $n$ 和 $m$ 是两个子序列的长度。

因为动态规划时有可能访问到 $-1$ 这个地址，为防止数组越界，我们要在字符串前加上一个或多个字符防止越界。

坑点：我们不要开 `int` 型变量，会出锅的，要开 `short` 型变量。

### 动态规划转移方程

![](https://cdn.luogu.com.cn/upload/image_hosting/miss9y8l.png)

观察这张图，对于 $\mathit{a}_{i-1,j-1}$ 来说，它的值有两种可能，取决于字符 $x_i$ 和 $y_j$ 这两个字符是否相等。

$\mathit{a}_{i,j}=\begin{cases}0&i=1 \lor j=0\\ \mathit{a}_{i-1,j-1}+1&i,j>0 \land x_i = y_i \\ 0 & i,j>0 \land x_i \ne y_i \end{cases}$

### 代码

```cpp
#include<bits/stdc++.h>
std::string s1,s2;
short f[4010][4010],ans,s1s,s2s;
int main()
{
	std::cin>>s1>>s2,s1="0"+s1,s2="0"+s2,s1s=s1.size(),s2s=s2.size();
	for(int i=1;i<s1s;i++) for(int j=1;j<s2s;j++) if(s1[i]==s2[j]) f[i][j]=f[i-1][j-1]+1;
	for(int i=1;i<s1s;i++) for(int j=1;j<s2s;j++) ans=std::max(ans,f[i][j]);
	std::cout<<ans<<std::endl;
	return 0;
}
```


---

## 作者：MattL (赞：0)

[洛谷链接](https://www.luogu.com.cn/problem/AT2418) & [原题链接](https://www.luogu.com.cn/remoteJudgeRedirect/atcoder/2418)

字符串 & 递推。

---

**题意**

>求两字符串的最长公共子串。（长度均不大于 $4000$）

---

**解题**

这方法有点暴力……

首先，我们设 $f_{i,o}$ 为第一个字符串的第 $i$ 个与第二个字符串的第 $o$ 个结尾的最长公共子串长度。

我们分类讨论：
1. 当两字符不同时，显然无解，即 $f_{i,j}=0$（全局变量默认为 $0$，可以不写这种情况）。
2. 当两字符相同时，答案 $+1$，即 $f_{i,j}=f_{i-1,j-1}+1$。

---

**注意事项**

1. $62.5MB$ 是认真的吗？记住数组一定要开 `short`（`unsigned` 与否不影响）
2. 由于字符串起始为 $0$，而按照我们推的式子会用到下标为 $-1$ 的，所以可以字符串前面加一个字符或用偏移量（当然 `map`也行）。
3. 记录答案最大值的记得初始化是 $0$，负的不行。

---


**代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
string q,p;
short f[4001][4001],ans=0;
int main()
{
	cin>>q>>p;
	for(int i=0;i<q.size();i++)
		for(int o=0;o<p.size();o++)
			if(q[i]==p[o])
				f[i+1][o+1]=f[i][o]+1,ans=max(ans,f[i+1][o+1]);
	cout<<ans<<endl;
	return 0;
}
```

---

