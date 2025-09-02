# 题目信息

# Plus Minus Permutation

## 题目描述

You are given $ 3 $ integers — $ n $ , $ x $ , $ y $ . Let's call the score of a permutation $ ^\dagger $ $ p_1, \ldots, p_n $ the following value:

 $ $$$(p_{1 \cdot x} + p_{2 \cdot x} + \ldots + p_{\lfloor \frac{n}{x} \rfloor \cdot x}) - (p_{1 \cdot y} + p_{2 \cdot y} + \ldots + p_{\lfloor \frac{n}{y} \rfloor \cdot y}) $ $ </span></p><p>In other words, the <span class="tex-font-style-it">score</span> of a permutation is the sum of  $ p\_i $  for all indices  $ i $  divisible by  $ x $ , minus the sum of  $ p\_i $  for all indices  $ i $  divisible by  $ y $ .</p><p>You need to find the maximum possible <span class="tex-font-style-it">score</span> among all permutations of length  $ n $ .</p><p>For example, if  $ n = 7 $ ,  $ x = 2 $ ,  $ y = 3 $ , the maximum <span class="tex-font-style-it">score</span> is achieved by the permutation  $ \[2,\\color{red}{\\underline{\\color{black}{6}}},\\color{blue}{\\underline{\\color{black}{1}}},\\color{red}{\\underline{\\color{black}{7}}},5,\\color{blue}{\\underline{\\color{red}{\\underline{\\color{black}{4}}}}},3\] $  and is equal to  $ (6 + 7 + 4) - (1 + 4) = 17 - 5 = 12 $ .</p><p> $ ^\\dagger $  A permutation of length  $ n $  is an array consisting of  $ n $  distinct integers from  $ 1 $  to  $ n $  in any order. For example,  $ \[2,3,1,5,4\] $  is a permutation, but  $ \[1,2,2\] $  is not a permutation (the number  $ 2 $  appears twice in the array) and  $ \[1,3,4\] $  is also not a permutation ( $ n=3 $ , but the array contains  $ 4$$$).

## 说明/提示

The first test case is explained in the problem statement above.

In the second test case, one of the optimal permutations will be $ [12,11,\color{blue}{\underline{\color{black}{2}}},4,8,\color{blue}{\underline{\color{red}{\underline{\color{black}{9}}}}},10,6,\color{blue}{\underline{\color{black}{1}}},5,3,\color{blue}{\underline{\color{red}{\underline{\color{black}{7}}}}}] $ . The score of this permutation is $ (9 + 7) - (2 + 9 + 1 + 7) = -3 $ . It can be shown that a score greater than $ -3 $ can not be achieved. Note that the answer to the problem can be negative.

In the third test case, the score of the permutation will be $ (p_1 + p_2 + \ldots + p_9) - p_9 $ . One of the optimal permutations for this case is $ [9, 8, 7, 6, 5, 4, 3, 2, 1] $ , and its score is $ 44 $ . It can be shown that a score greater than $ 44 $ can not be achieved.

In the fourth test case, $ x = y $ , so the score of any permutation will be $ 0 $ .

## 样例 #1

### 输入

```
8
7 2 3
12 6 3
9 1 9
2 2 2
100 20 50
24 4 6
1000000000 5575 25450
4 4 1```

### 输出

```
12
-3
44
0
393
87
179179179436104
-6```

# AI分析结果

### 题目内容重写
#### 题目描述
给定三个整数 $n$、$x$、$y$。定义一个排列 $p_1, p_2, \ldots, p_n$ 的分数为：
$$(p_{1 \cdot x} + p_{2 \cdot x} + \ldots + p_{\lfloor \frac{n}{x} \rfloor \cdot x}) - (p_{1 \cdot y} + p_{2 \cdot y} + \ldots + p_{\lfloor \frac{n}{y} \rfloor \cdot y})$$
换句话说，排列的分数是所有下标能被 $x$ 整除的 $p_i$ 之和，减去所有下标能被 $y$ 整除的 $p_i$ 之和。你需要找到所有长度为 $n$ 的排列中可能的最大分数。

#### 说明/提示
第一个测试用例在题目描述中已经解释。

在第二个测试用例中，一个最优排列是 $[12,11,\color{blue}{\underline{\color{black}{2}}},4,8,\color{blue}{\underline{\color{red}{\underline{\color{black}{9}}}}},10,6,\color{blue}{\underline{\color{black}{1}}},5,3,\color{blue}{\underline{\color{red}{\underline{\color{black}{7}}}}}]$。该排列的分数是 $(9 + 7) - (2 + 9 + 1 + 7) = -3$。可以证明无法得到比 $-3$ 更大的分数。注意，问题的答案可以是负数。

在第三个测试用例中，排列的分数是 $(p_1 + p_2 + \ldots + p_9) - p_9$。一个最优排列是 $[9, 8, 7, 6, 5, 4, 3, 2, 1]$，其分数为 $44$。可以证明无法得到比 $44$ 更大的分数。

在第四个测试用例中，$x = y$，因此任何排列的分数都是 $0$。

#### 样例 #1
##### 输入
```
8
7 2 3
12 6 3
9 1 9
2 2 2
100 20 50
24 4 6
1000000000 5575 25450
4 4 1
```
##### 输出
```
12
-3
44
0
393
87
179179179436104
-6
```

### 算法分类
贪心、数学

### 题解分析与结论
所有题解的核心思路都是通过贪心策略，将最大的数分配给被 $x$ 整除的位置，将最小的数分配给被 $y$ 整除的位置，并排除同时被 $x$ 和 $y$ 整除的位置（因为这些位置的贡献会相互抵消）。通过计算这些位置的数量，并使用等差数列求和公式，可以快速得到最大分数。

### 评分较高的题解
#### 题解1：hjqhs (4星)
**关键亮点**：简洁明了地使用了贪心策略和等差数列求和公式，代码简洁高效。
**核心代码**：
```cpp
int lcm(int x,int y){return x/__gcd(x,y)*y;}
int sum(int st,int ed,int num){return (st+ed)*num/2;}
void solve(){
  cin>>n>>x>>y;
  int cx=n/x,cy=n/y,cz=n/lcm(x,y);
  cx-=cz,cy-=cz;
  cout<<sum(n-cx+1,n,cx)-sum(1,cy,cy)<<'\n';
}
```
**核心思想**：计算被 $x$ 和 $y$ 整除的位置数量，并使用等差数列求和公式计算最大分数。

#### 题解2：an_ancient_ghoul (4星)
**关键亮点**：详细解释了贪心策略，并提供了清晰的代码实现。
**核心代码**：
```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
int t,a,b,c,n,ca,cb,cc;
int gcd(int x,int y)
{
	if(x<y)swap(x,y);
	if(x%y)return gcd(y,x%y);
	return y;
}
signed main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>t;
	while(t--)
	{
		cin>>n>>a>>b;
		c=a*b/gcd(a,b);
		ca=n/a,cb=n/b,cc=n/c;
		ca-=cc,cb-=cc;
		cout<<(n+n-ca+1)*ca/2-(1+cb)*cb/2<<endl;
	}
	return 0;
} 
```
**核心思想**：通过计算被 $x$ 和 $y$ 整除的位置数量，并使用等差数列求和公式计算最大分数。

#### 题解3：Larryyu (4星)
**关键亮点**：详细解释了贪心策略，并提供了清晰的代码实现。
**核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
long long get(long long x){
	return (x+1)*x/2;
}
int gcd(int x,int y){
	if(x==0) return y;
	if(x>y) swap(x,y);
	return gcd(y%x,x);
}
void  solve(){
	long long n,x,y;
	cin>>n>>x>>y;
	long long cnt1=n/x,cnt2=n/y,cnt3=n/(x*y/gcd(x,y));
	cnt1-=cnt3,cnt2-=cnt3;
	long long sum1=get(n)-get(n-cnt1),sum2=get(cnt2);
	cout<<sum1-sum2<<endl;
}
int main(){
	cin>>t;
	while(t--){
		solve();
	}
	return 0;
}
```
**核心思想**：通过计算被 $x$ 和 $y$ 整除的位置数量，并使用等差数列求和公式计算最大分数。

### 最优关键思路
1. **贪心策略**：将最大的数分配给被 $x$ 整除的位置，将最小的数分配给被 $y$ 整除的位置。
2. **排除重复贡献**：排除同时被 $x$ 和 $y$ 整除的位置，因为这些位置的贡献会相互抵消。
3. **等差数列求和**：使用等差数列求和公式快速计算最大分数。

### 可拓展之处
类似的问题可以通过贪心策略和数学公式来优化计算，特别是在处理排列和组合问题时，贪心策略往往能提供高效的解决方案。

### 推荐题目
1. [P1045 最大子段和](https://www.luogu.com.cn/problem/P1045)
2. [P1068 最大公约数和最小公倍数问题](https://www.luogu.com.cn/problem/P1068)
3. [P1072 最大公约数](https://www.luogu.com.cn/problem/P1072)

### 个人心得总结
在解决这类问题时，贪心策略和数学公式的结合往往能提供高效的解决方案。通过合理分配数值，并排除重复贡献，可以快速得到最优解。

---
处理用时：39.17秒