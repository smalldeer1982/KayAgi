# Challenge Pennants

## 题目描述

Because of budget cuts one IT company established new non-financial reward system instead of bonuses.

Two kinds of actions are rewarded: fixing critical bugs and suggesting new interesting features. A man who fixed a critical bug gets "I fixed a critical bug" pennant on his table. A man who suggested a new interesting feature gets "I suggested a new feature" pennant on his table.

Because of the limited budget of the new reward system only $ 5 $ "I fixed a critical bug" pennants and $ 3 $ "I suggested a new feature" pennants were bought.

In order to use these pennants for a long time they were made challenge ones. When a man fixes a new critical bug one of the earlier awarded "I fixed a critical bug" pennants is passed on to his table. When a man suggests a new interesting feature one of the earlier awarded "I suggested a new feature" pennants is passed on to his table.

One man can have several pennants of one type and of course he can have pennants of both types on his table. There are $ n $ tables in the IT company. Find the number of ways to place the pennants on these tables given that each pennant is situated on one of the tables and each table is big enough to contain any number of pennants.

## 样例 #1

### 输入

```
2
```

### 输出

```
24```

# 题解

## 作者：BrokenStar (赞：2)

## 思路
题目中两种旗是没有关系的，根据乘法原理，计算红旗可以摆放的数量与蓝旗可以摆放的数量，再相乘，即可得到答案。

## 细节
- 注意有的桌子可以不摆放

- 题目中 $n$ 的取值较大，所以要用长整型。

## 代码
```cpp
#include<iostream>
using namespace std;
long long C(int a,long long b){
	long long ans;
	ans=1;
	for(int i=1;i<=b;++i){
    	ans=ans*(a+1-i)/i;
   }
	return ans;
}//计算组合数的公式 
using namespace std;
int n;
int main(){
	cin>>n;
	cout<<C(n+4,5)*C(n+2,3)<<endl;
	return 0;
}
```


---

## 作者：封禁用户 (赞：2)

由题目描述可知，放置红旗和放置蓝旗是独立的，因此在 n 张桌子上放置红旗的每种方法与放置蓝旗的每种方法兼容，则问题的答案为放红旗的方法数与放蓝旗的方法数的乘积 。

在不考虑顺序与重复的情况下，记将 k 种物体分配给 n 种物体的方法数为 s，s 的组合数公式如下 。
$$\operatorname{s}=\frac{(k+n-1)!}{k!(n-1)!}$$

因此答案 $\operatorname{ans}=\frac{(n+4)!}{5!(n-1)!}\cdot\frac{(n+2)!}{3!(n-1)!}$。注意到 n 的取值范围较大 , 应防止在计算过程中64位整数类型溢出 。

Code:
```cpp
#include <iostream>
#include <cmath>
using namespace std;
unsigned long long n;
int main() {
	cin>>n;
	cout<<(n+2)*(n+1)/2*n/3*(n+4)*(n+3)/2*(n+2)/3*(n+1)/4*n/5;
    //防止在计算过程中溢出
	return 0;
}
```


---

## 作者：Sammy_prime (赞：1)

[CF630G](https://www.luogu.com.cn/problem/CF630G)

# 思路

本题中说到的红旗和蓝旗任何关系都没有，而需要用到乘法原理用组合数求解。组合公式：

$$C^m_n=\frac{(n+m-1)!}{m!(n-1)!}$$

最后提醒大家，要开 `long long`。

---

## 作者：Amberhart (赞：1)

排列组合里组合的题目。

公式：

$C^m_n=\frac{n!}{m!(n-m)!}$

有公式就好代码了，根据公式套就行了。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll c(ll a,ll b){//算出组合数
	ll s=1;
	for(ll i=1;i<=b;i++){
		s=s*(a+1-i)/i;
	}
	return s;
}
ll n;
int main(){
	cin>>n;	
	cout<<c(n+4,5)*c(n+2,3);//运用乘法原理
	return 0;
}

```
注意：

1. 桌子上可以不放旗子；

2. 函数 $c$ 里的变量 $s$ 要赋初始值为 $1$，不然得出的结果是 $0$；

3. 变量 $n$ 的范围比较大，用 `long long` 类型。

（如果不知道哪里用 `long long` 哪里用 `int` 就都定义成 `long long`，我就是这样的qwq）

---

## 作者：hexuchen (赞：0)

无人区写题解的第四天

[题目传送门](https://www.luogu.com.cn/problem/CF630G)

[更好的阅读体验？](https://www.luogu.com.cn/solution-cf630g)



## 题目意思

求把 $3$ 张蓝旗和 $5$ 张红旗放在 $n$ 张桌子上有多少种方法。


## 思路分析

一道简单的数学题。

这道题要用到组合数公式：

$$C _ {n} ^ {m} = \frac{(n+m-1 )!}{m!(n-1)!}$$

所以正确答案就是

$$C _ {n+4} ^ {5} \times C _ {n+2} ^ {3}$$

**提示：十年 OI 一场空，不开 long long 见祖宗！**

## AC 代码 
 
```cpp
#include <bits/stdc++.h>
#define int unsigned long long
using namespace std;
int n;
int zhsgs(int a,int b); //组合数公式
signed main(){
	cin>>n;
	cout<<zhsgs(n+4,5)*zhsgs(n+2,3)<<endl;
	return 0;
}
int zhsgs(int a,int b){
	int ans=1;
	for(int i=1;i<=b;i++){
		ans=ans*(a+1-i)/i;
	}
	return ans;
}
```

---

## 作者：ICU152_lowa_IS8 (赞：0)

本题目是一道数学题。

解法其它题解已经讲的很清楚了，在此简单复述：

红旗和蓝旗互相不干扰，所以可用乘法原理求解。

用组合数 $C_n^m=\dfrac{n!}{m!(n-m)!}$ 套就可以了。

细节：

1.不开 `long long` 见祖宗。

2.如果你是使用杨辉三角求解的话，循环要到 $n+4$，不然会出现输出为 $0$ 的情况。

代码如下：

```
#include<bits/stdc++.h>
using namespace std;
long long c[1005][1005];
int main(){
	int n;
	cin>>n;
	for(int i=0;i<=505;i++){//选择的是直接预处理完毕
		for(int j=0;j<=i;j++){
			if(i==0||j==0||j==i){
				c[i][j]=1;
			}
			else{
				c[i][j]=c[i-1][j]+c[i-1][j-1];
			}
		}
	}
	cout<<c[n+2][3]*c[n+4][5];
	return 0;
}

```


---

## 作者：WYZ20030051 (赞：0)

## 前言

这道题算是一道入门的组合数学题，难度不大，适合刚学组合数学的同学写。其实主要的几种思路其他题解已经说的比较清楚了，这篇题解除了会对题目进行讲解以外还会再补充一些其他与组合数学入门的内容。

------------

## 正文

这道题的题意很简单：给定 5 面红旗， 3 面蓝旗以及 $n$ 张桌子，要求这 8 面旗必须全部放完，**其中桌子上可以选择不放旗**。求合法的方案数。

这道题读完之后很容易想到用组合数来解决该题，那么具体应该如何解决呢？

分析题意可提取如下几个**关键点**：
1. “当所有的旗分配完后，在某一张桌子上红旗，蓝旗，红旗与红旗，红旗，蓝旗这样类似的不记为不同种”，也就是旗的顺序对这道题并没有影响。
2. 一张桌子上可以放红旗和多张蓝旗。
3. 题中的红旗与蓝旗是互不干扰的。

第一点和第二点暗示了这道题其实就是可重复组合，所以可以使用公 $C_{n+m-1}^{m}$ 来计算答案。第三点暗示了我们可以把蓝旗和红旗分开处理，因为二者是**互不干扰**的，所以我们可以分别计算出红旗对答案的贡献以及蓝旗对答案的贡献，并最后根据乘法原理将二者相乘以得到答案。

对于红旗，桌子有 $n$ 张，红旗有 5 张，可以直接套入公式得到 $C_{n+4}^{5}$。蓝旗同理，套公式得 $C_{n+2}^{3}$。

则最终答案为 $C_{n+4}^{5} \times C_{n+2}^{3}$。

------------

那么现在我们已经知道答案是什么了，接下来要做的就是如何得到答案。

我们现在要做的只有求出组合数 $C$ 即可，因为只要得到了 $C$，那么我们就可以直接得到答案。而求出 $C$ 的方法主要有四种：
1. 暴力模拟出 $C$ 的公式，以得到答案。
2. 预处理出求出 $C$ 需要的相关内容后再求出 $C$。
3. 用递推的方式求出 $C$。
4. 用卢卡斯定理求出 $C$（这种方法适用于 $n$、$m$ 比较大，但模数较小的情况）。

由于本题 n 的范围较小，所以可以三种方法都可以通过本题，其中第二种是最常用的。由于并没有人用递推的方式求出 $C$（又慢又麻烦当然没人用啦），这个做法的时间复杂度是 $O{(n^{2})}$ 的，并不是很常用（由于大多数组合数学的题目都是单次查询且数据范围都较大，所以这种方法并不常用）。不过这个方法相较于其他几种方法，该方法有着码量小，写的时候较方便等优点，并且非常适合数据范围较小，但是是多次查询的题目，这里我说一下用递推的方式求出 $C$。

组合数的递推式是 $C_{n}^{m}=C_{n-1}^{m}+C_{n-1}^{m-1}$，也就是所谓的“杨辉三角”，这个递推式大家在初学组合数的时候应该都知道，并且它很好证明，这里不再赘述。实现用递推式的方法求出 $C$ 的主要途径也有两种，一种是用类似 DP 的方法对其进行状态转移，另一种是用递推的方式去实现。但是呢由于我们已经提前算出答案了，我们发现第二项的值是固定的且非常小，所以我们这里讲一下用第一种方法来实现这道题。求出 $C$ 的方法是：定义一个二维数组 C，其中 $C_{n,m}$ 表示 $C_{n}^{m}$ 的大小，我们根据递推式就可以以 $O{(n^{2})}$ 的时间复杂度预处理出这个数组。

------------
## CODE
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<algorithm>
#include<cassert>
#include<stack>
#include<queue>
#include<vector>
#include<map>
#include<cstdlib>
using namespace std;
#define ll long long
#define ull unsigned long long
#define int ll
int read()
{
	int now=0,nev=1;
	char c=getchar();
	while(c<'0' || c>'9')
	{
		if(c=='-')
			nev=-1;
		c=getchar();
	}
	while(c>='0' && c<='9')
	{
		now=(now<<1)+(now<<3)+(c&15);
		c=getchar();
	}
	return now*nev;
}
const int MAXN=510;
int n;
int C[MAXN][MAXN];
void get_C()
{
	for(int i=0;i<=n+4;i++)//最多用到 n+4，且这题是单次询问，所以 i 只要循环到 n+4 就够了 
	{
		for(int j=0;j<=i && j<=5;j++)//最多用到 5，所以这题 j 只要循环到 5 就够了 
		{
			if(j==0)
				C[i][j]=1;
			else
				C[i][j]=C[i-1][j]+C[i-1][j-1];
		}
	}
}
signed main()
{
	n=read();
	get_C();
	printf("%lld",C[n+4][5]*C[n+2][3]);
	return 0;
}
```


------------

## 结尾

此题很适合刚学组合数的同学入门（为什么我到现在了才知道这道题....），希望这篇题解能对大家有帮助。

---

## 作者：fp0cy1tz6mn4rd_ (赞：0)

### 思路

题目中红旗和蓝旗没有关系，所以可以使用组合数公式。组合数公式如下：
$$C^m_n=\frac{(n+m-1)!}{m!(n-1)!}$$

注意细节，数字较大，需要使用 ```long long```。

### 代码

```cpp
#include<iostream>
using namespace std;
long long C(int a,int b){	//计算组合数
	long long ans=1;
	for(int i=1;i<=b;i++)
    	ans=ans*(a-i+1)/i;
	return ans;
}
int main(){
	int n;
	cin>>n;	
	cout<<C(n+4,5)*C(n+2,3);	//注意桌子上可以不插旗
	return 0;
}
```


---

## 作者：_Execution_ (赞：0)

题目中红旗和蓝旗数量固定且互不相关，于是得到解法。

使用组合数公式：

$C(n,m)= \frac{n!}{m!(n-m)!}$

计算蓝旗和红旗可以摆放的数量，利用乘法原理，乘在一起，就可以得出答案。

需要注意的是有的桌子可以不摆放。

代入题目中的数量可以得到 $ans=C(n+4,5) \times C(n+2,3)$。

注意 $n$ 的范围需要长整型来存答案。
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
long long C(long long n, long long m) {
  long long res = 1;
  for (long long i = 1; i <= m; ++i) {
    res = res * (n - m + i) / i;
  }
  return res;
}
int main() {
  cin >> n;
  cout << C(n + 4, 5) * C(n + 2, 3);
  return 0;
}
```


---

## 作者：OLE_OIer (赞：0)

这是一道比较有思维难度的组合数学题。由于题目中红旗与蓝旗本质上是无关的，所以我们可以利用乘法原理，算出红旗的可能性与蓝旗的可能性，然后相乘。

红旗有 $5$ 面且都相同，桌子有 $n$ 张且都不相同，你想到了什么？对的，就是小学奥数里的“隔板法”，所以我们就可以将桌子看成隔板而用组合数求解。公式是： $C^{5}_{n-1}$ ，同理可以得到蓝旗有 $C^{3}_{n-1}$ 中方法，于是有了代码：

```cpp
#include<bits/stdc++.h>
#define int long long
int c(int a,int b){//计算组合数
	int ans=1;
	for(int i=1;i<=b;++i) ans=ans*(a+1-i)/i;
	return ans;
}
using namespace std;
signed main(){
	int n;
	cin>>n;	
	cout<<c(n-1,5)*c(n-1,3);
	return 0;
}
```

提交后一看，怎么错了呢？原来题目说桌子上**可以不插旗**，所以要把红旗的可能性公式改为 $C^{5}_{n+4}$ ，并把蓝旗的公式改为 $C^{3}_{n+2}$ 。

正确代码如下：

```cpp
#include<bits/stdc++.h>
#define int long long
int c(int a,int b){//计算组合数
	int ans=1;
	for(int i=1;i<=b;++i) ans=ans*(a+1-i)/i;
	return ans;
}
using namespace std;
signed main(){
	int n;
	cin>>n;	
	cout<<c(n+4,5)*c(n+2,3);
	return 0;
}
```

---

## 作者：int32 (赞：0)

小学组合数学题。

容易发现放红旗和蓝旗是独立的，于是分别计数相乘即可。

对于**将 $m$ 个物体分别放在 $n$ 个盘子上，盘子可以有空**这类问题，公式如下：

$$s=\binom{n+m-1}{m}=\dfrac{(n+m-1)!}{m!(n-1)!}$$

将题目数据带入得：

$$ans=\dfrac{(n+2)!(n+4)!}{720[(n-1)!]^2}$$

注意溢出。

---

