# 题目信息

# Polo the Penguin and Houses

## 题目描述

Little penguin Polo loves his home village. The village has $ n $ houses, indexed by integers from 1 to $ n $ . Each house has a plaque containing an integer, the $ i $ -th house has a plaque containing integer $ p_{i} $ ( $ 1<=p_{i}<=n $ ).

Little penguin Polo loves walking around this village. The walk looks like that. First he stands by a house number $ x $ . Then he goes to the house whose number is written on the plaque of house $ x $ (that is, to house $ p_{x} $ ), then he goes to the house whose number is written on the plaque of house $ p_{x} $ (that is, to house $ p_{px} $ ), and so on.

We know that:

1. When the penguin starts walking from any house indexed from 1 to $ k $ , inclusive, he can walk to house number 1.
2. When the penguin starts walking from any house indexed from $ k+1 $ to $ n $ , inclusive, he definitely cannot walk to house number 1.
3. When the penguin starts walking from house number 1, he can get back to house number 1 after some non-zero number of walks from a house to a house.

You need to find the number of ways you may write the numbers on the houses' plaques so as to fulfill the three above described conditions. Print the remainder after dividing this number by $ 1000000007 $ $ (10^{9}+7) $ .

## 样例 #1

### 输入

```
5 2
```

### 输出

```
54
```

## 样例 #2

### 输入

```
7 4
```

### 输出

```
1728
```

# AI分析结果

### 题目内容
# 企鹅波罗和房子

## 题目描述
小企鹅波罗热爱他的家乡村庄。村庄里有$n$座房子，由整数$1$到$n$编号。每座房子都有一块牌子，上面写着一个整数，第$i$座房子的牌子上写着整数$p_{i}$（$1\leq p_{i}\leq n$）。

小企鹅波罗喜欢在这个村庄里散步。散步的方式如下。首先，他站在编号为$x$的房子旁。然后，他走到牌子上所写编号的房子（即走到房子$p_{x}$），接着，他再走到房子$p_{x}$牌子上所写编号的房子（即走到房子$p_{p_{x}}$），依此类推。

我们知道：
1. 当企鹅从编号$1$到$k$（包括$1$和$k$）的任意一座房子出发时，他都能走到编号为$1$的房子。
2. 当企鹅从编号$k + 1$到$n$（包括$k + 1$和$n$）的任意一座房子出发时，他肯定无法走到编号为$1$的房子。
3. 当企鹅从编号为$1$的房子出发时，经过若干次从一座房子走到另一座房子的移动后，他能回到编号为$1$的房子。

你需要找出满足上述三个条件的在房子牌子上写数字的方法数量。输出该数量除以$1000000007$（$10^{9}+7$）的余数。

## 样例 #1
### 输入
```
5 2
```
### 输出
```
54
```

## 样例 #2
### 输入
```
7 4
```
### 输出
```
1728
```

### 算法分类
数学

### 综合分析与结论
这些题解思路基本一致，均是将问题分为两部分来考虑：一部分是$1$到$k$号房子的方案数，另一部分是$k + 1$到$n$号房子的方案数，最后根据乘法原理将两部分方案数相乘得到总方案数。对于$1$到$k$号房子，通过手动模拟小数据找规律得出方案数为$k^{k - 1}$；对于$k + 1$到$n$号房子，由于这些房子不能指向$1$，所以每个房子都有$n - k$种选择，方案数为$(n - k)^{n - k}$ 。考虑到数据较大，都采用快速幂来优化计算。各题解的差异主要体现在代码实现风格和对思路的表述清晰度上。

### 所选的题解
- **作者：ztxtjz（5星）**
  - **关键亮点**：思路表述清晰，先明确题意，再通过分类讨论，手动模拟小数据详细地推导出两部分的方案数，代码简洁明了，注释详细。
  - **重点代码**：
```cpp
#include <cstdio>
#define ll long long
ll n,k,mod=1e9+7;
inline ll fpow(ll x,ll n)
{
    ll ret=1;
    for(;n;n>>=1,x=x*x%mod) if(n&1) ret=ret*x%mod;
    return ret;
}
int main()
{
	scanf("%lld%lld",&n,&k);
	printf("%lld",(fpow(k,k-1)*fpow(n-k,n-k))%mod);
	return 0;
}
```
  - **核心实现思想**：`fpow`函数实现快速幂运算，主函数中通过调用`fpow`函数分别计算两部分的方案数并相乘取模得到结果。
- **作者：mxjz666（4星）**
  - **关键亮点**：简洁地阐述了两部分的方案数及乘法原理，代码简短，使用`bits/stdc++.h`头文件，代码实现较为紧凑。
  - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod=1e9+7;
int ksm(int a,int b){
	int c=1;
	for(;b;b>>=1){
		if(b&1){
			c=c*a%mod;
		}
		a=a*a%mod;
	}
	return c;
}
signed main(){
	int n,k;
	scanf("%lld%lld",&n,&k);
	printf("%lld",ksm(k,k-1)*ksm(n-k,n-k)%mod);
	return 0;
}
```
  - **核心实现思想**：`ksm`函数实现快速幂，主函数利用`ksm`函数计算两部分方案数乘积取模。
- **作者：orpg（4星）**
  - **关键亮点**：清晰地给出题目梗概和题意分析，代码中使用`ios::sync_with_stdio(0);`等优化输入输出，逻辑清晰。
  - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll n,k,mod=1e9+7;
ll ksm(ll a,ll b){
	ll ans=1;
	while(b){
		if(b&1) ans=ans*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return ans%mod;
}//快速幂
main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
	cin>>n>>k;
    ll ans=ksm(k,k-1)*ksm(n-k,n-k)%mod;
	cout<<ans<<'\n';
	return 0;
}
```
  - **核心实现思想**：`ksm`函数实现快速幂运算，主函数通过`ksm`函数计算两部分方案数乘积取模输出。

### 最优关键思路或技巧
- **分类讨论与找规律**：将问题按房子编号范围分为两部分，通过手动模拟小数据找出每部分方案数的规律，进而得到整体方案数。
- **快速幂优化**：由于$n$可能很大，使用快速幂算法优化幂运算，降低时间复杂度。

### 拓展
此类题目属于组合数学范畴，通常通过分析题目条件，将问题分解为多个独立部分，分别计算各部分方案数，再依据乘法原理得到总方案数。类似题目一般围绕不同的限制条件下的排列组合问题展开，解题关键在于对条件的准确理解和方案数的合理推导。

### 推荐题目
- [P1313 计算系数](https://www.luogu.com.cn/problem/P1313)：涉及二项式定理相关的系数计算，考查组合数学知识。
- [P2181 对角线](https://www.luogu.com.cn/problem/P2181)：通过找规律和数学推导来计算多边形对角线相关问题，与本题找规律的思路类似。
- [P3807 【模板】卢卡斯定理](https://www.luogu.com.cn/problem/P3807)：考查卢卡斯定理在组合数取模问题中的应用，属于组合数学中较进阶的内容，与本题利用数学原理解决问题的思路相符。 

---
处理用时：64.25秒