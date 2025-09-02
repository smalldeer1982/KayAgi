# Arithmetic Array

## 题目描述

An array $ b $ of length $ k $ is called good if its arithmetic mean is equal to $ 1 $ . More formally, if $ $$$\frac{b_1 + \cdots + b_k}{k}=1. $ $ </p><p>Note that the value  $ \\frac{b\_1+\\cdots+b\_k}{k} $  is not rounded up or down. For example, the array  $ \[1,1,1,2\] $  has an arithmetic mean of  $ 1.25 $ , which is not equal to  $ 1 $ .</p><p>You are given an integer array  $ a $  of length  $ n$$$. In an operation, you can append a non-negative integer to the end of the array. What's the minimum number of operations required to make the array good?

We have a proof that it is always possible with finitely many operations.

## 说明/提示

In the first test case, we don't need to add any element because the arithmetic mean of the array is already $ 1 $ , so the answer is $ 0 $ .

In the second test case, the arithmetic mean is not $ 1 $ initially so we need to add at least one more number. If we add $ 0 $ then the arithmetic mean of the whole array becomes $ 1 $ , so the answer is $ 1 $ .

In the third test case, the minimum number of elements that need to be added is $ 16 $ since only non-negative integers can be added.

In the fourth test case, we can add a single integer $ 4 $ . The arithmetic mean becomes $ \frac{-2+4}{2} $ which is equal to $ 1 $ .

## 样例 #1

### 输入

```
4
3
1 1 1
2
1 2
4
8 4 6 2
1
-2```

### 输出

```
0
1
16
1```

# 题解

## 作者：BurningEnderDragon (赞：12)

[题目链接：CF1537A Arithmetic Array](https://www.luogu.com.cn/problem/CF1537A)

## 题意解释

给定一个有 $n$ 个整数的序列 $b$，你可以向这个序列的末端添加若干个**非负整数**，求最少添加多少个非负整数可以使这个序列的算术平均数为 $1$。

## 结论

一个有 $n$ 个整数的序列 $b$ 的算术平均数为 $1$ 的充分必要条件是：序列 $b$ 中所有整数的和为 $n$，即 $\sum\limits_{i=1}^{n}{b_{i}} = n$。

对于每一个长度为 $n$ 的原始序列 $b$，令 $sum$ 表示 $b$ 中所有整数的和。显然：

- 若 $sum < n$，则添加 $1$ 个整数 $n-sum+1$，此时序列长度和序列总和均为 $n+1$，故答案为 $1$；
- 若 $sum \ge n$，则添加 $sum-n$ 个整数 $0$，此时序列长度和序列总和均为 $sum$，故答案为 $sum-n$。

## 代码

```cpp
#include <cstdio>
int t,n,a[50],sum;
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		sum=0;
		for(int i=0;i<=n-1;++i)
		{
			scanf("%d",&a[i]);
			sum+=a[i];
		}
		if(sum<n)
		{
			puts("1");
		}
		else
		{
			printf("%d\n",sum-n);
		}
	}
	return 0;
}
```



---

## 作者：Shunpower (赞：2)

## 题目大意

**有 $t$ 组数据**，每组数据是一个长度为 $n$ 的数列，现在要你求出需要往数列中加入多少个**非负整数**才能使得数列的平均数为 $1$。

## 解决思路

### 考虑各种情况

- 如果平均数大于 $1$，我们就要把平均数降下来，那肯定不能往里面加正数，只能往数列里加 $0$ 。
- 如果平均数等于 $1$，那么不需要加数。
- 如果平均数小于 $1$，那就加一个正数即可。

### 求出平均数大于 $1$ 时的加数量

首先，我们知道一堆数的平均数大于 $1$，其实就是这堆数的和大于数的个数。

如果这些数的和为 $sum$，个数为$n$，假设要加 $x$ 个 $0$，很容易进行如下变换：

$$
\begin{aligned}

sum+x\times 0&=n+x
\\sum&=n+x
\\x&=sum-n

\end{aligned}
$$

所以需要加 $sum-n$ 个 $0$。

## 代码实现

```
#include <bits/stdc++.h>
using namespace std;
int t,n,sum,tool;
int main(){
	cin>>t; 
	while(t--){//多组数据
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>tool;
			sum+=tool;//求和器
		}
		if(sum>n){
			cout<<sum-n<<endl;//平均数大于1，输出和与个数的差
		}
		else if(sum==n){
			cout<<"0"<<endl;//平均数等于1，直接输出0
		}
		else{
			cout<<"1"<<endl;//平均是小于1，直接加一个大正数即可
		}
		sum=0;//记得清空
	}
	return 0;
}
```

[AC记录](https://www.luogu.com.cn/record/51920454)

---

## 作者：sunzz3183 (赞：1)

# CF1537A Arithmetic Array

## 题意 

  给你一个长度为 $n$ 的序列，你要在序列的末端添加几个非负整数 $(a≥0)$ ，是这个序列的平均值为1。
  
## 分析
 我们定义一个变量 $sum$ ,统计序列的和，那么，值这个序列的平均值就是为 $sum/n$ 。
  
  序列的平均值为1，也就是 $sum/n=1$ ，即 $sum=n$ 。
  
  那么，有三种情况：
  
  1、 $sum>n$ ，此时，添加一个正整数 $n-sum+1$ ，使 $sum=n+1$；
  
  2、 $sum=n$ ，此时，不做处理；
  
  3、 $sum<n$ ，此时，添加 $sum-n$ 个 $0$ ,使 $sum=n$。
  
## 代码

```
#include<iostream>
#include<cstdio>
using namespace std;
int t,n,a;
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		int sum=0;
		for(int i=1;i<=n;i++){
			cin>>a;
			sum+=a;
		}
		if(sum<n)//第一种情况
			cout<<"1\n";
		if(sum==n)//第二种情况
			cout<<"0\n";
		if(sum>n)//第三种情况
			cout<<sum-n<<"\n";
	}
	return 0;
}
```



---

## 作者：张语诚ZYC (赞：1)

## 题目翻译

~~又是一道没翻译的题目呢！~~（百度翻译传送门：[LINK](http://fanyi.baidu.com/transpage?query=https%3A%2F%2Fwww.luogu.com.cn%2Fproblem%2FCF1537A&source=url&ie=utf8&from=auto&to=zh&render=1)）

对于每一组数据，给定一个数组，长度是 $n$ ，求至少加上多少个非负整数可以使目前数组的平均值为 $1$。

## 思路分析

用 $n$ 表示数组长度，$n$ 也是长度为 $n$ 的且平均值为 $1$ 的数组中所有元素和。
用 $sum$ 表示数组中所有数的和。

- 首先，读题可知，当 $sum=n$ 时，意味着数组中所有数的和等于长度为 $n$ 的且平均值为 $1$ 的数组中所有元素和，满足题意，不用任何操作，所以不用添加，即至少添加 $0$ 个数。
- 当 $sum<n$ 时，平均数也一定小于 $1$，加一个数就可以了（反正差多少就加多少）。

- 当 $sum>n$ 时，平均数大于 $1$ ，只能通过加 $0$ 让平均数降为 $1$，如果加 $n$ 个 $0$。得到 $\frac{n}{sum+x}=1$，得到 $x=sum-n$，即添加 $sum-n$ 个 $0$。

## $\texttt{AC Code}$

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1e3+10;
inline int read_int(){
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-'){
			w=-1;
		} 
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		s=s*10+ch-'0';
		ch=getchar();
	}
	return s*w;
}
int main(){
	int t=read_int();
	for(int ti=0;ti<t;ti+=1){
		int n=read_int();
		int sum=0;
		for(int i=0;i<n;i+=1){
			sum+=read_int();
		}
		if(sum==n){
			puts("0");
		}else if(sum<n){
			puts("1");
		}else{
			printf("%d \n",sum-n);
		}
	}
	return 0;
}
```


---

## 作者：ʕ•ﻌ•ʔ (赞：1)

### 传送门：[CF1537A  Arithmetic Array](https://www.luogu.com.cn/problem/CF1537A)。

### CF 题面：[Arithmetic Array](https://codeforces.com/contest/1537/problem/A)。

### 题目大意：
共有 $t$ 组测试数据，对于每一组数据，输入一个正整数 $n$ 表示将要给定的数列的长度，接下来 $n$ 个整数表示给定数列 $a$。 

我们定义：如果一个数列的**所有数的和除以该序列的长度**得到的商为一（也就是**数的和等于序列长度**），那么这个数列称为“好的数列”。

我们要进行的操作是向这个数列中添加一些**非负整数**，使这个数列变成好的数列。（如果本身就是好的数列那显然不需要添加）求最少添加的数的数量。

### 题目分析：

对于一开始没有头绪的题可以先分析分析样例。

样例一：

$3$

$1\ 1\  1$

显然，这个数列一开始就是一个“好的数列”。所以输出 0。

样例二：

$2$

$1\  2$

所有数的和为 $3$，数列长度为 $2$，显然需要我们添加一些**非负整数**。注意，对于这个样例，初始的**数的和**比**数列长度**要大。既然我们要添数.那显然**数列长度是不断变长的**，如果我们想尽量**少添数**，那要尽量使数的和变化小一些，数列长度变化大一些。而每增加一个数,数列长度都会变大 $1$，只有添加的数为  $0$ 时数的和才没有变化。那么答案就是数的和与数列长度的差（增加许多 $0$）。

再看一组样例：

$1$

$-2$

数的和为 $-2$ ,数列长度为 $1$,那么是不是只要添加**一个**足够大的数，就一定能满足要求了呢？答案是显然的。

分析到这一步，我们便讨论出了所有可能的情况，答案也就自然而然的出现了。

## AC CODE：

```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
int main(){
	int t,n,sum,a[60];
	cin>>t;
	while(t--){
		sum=0; //多组数据，别忘了赋初始值 
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			sum+=a[i]; //计算初始的数列和 
		}
		if(sum==n){ //一开始就是好的数列 
			cout<<"0"<<endl;
			continue;
		}
		if(sum<n){ //对应最后一组样例 
			cout<<"1"<<endl;
			continue ;
		}
		cout<<sum-n<<endl; 	//对应样例二 
	}
	return 0;
} 
```




---

## 作者：翼德天尊 (赞：0)

由于是【平均值】，不难想到开始先将初始数列的和算出。

下面开始分类讨论。

若和等于 $n$（$1\times n$），则输出 $0$ 即可。

若和大于 $n$，由于我们只能选择非负整数将该数组的平均值拉为 $1$，所以我们只能选择 $0$。

由于一次只能添加一个 $0$，将数组的总和下拉 $1$，所以我们添加 $sum-n$ 个 $0$ 即可，答案为 $sum-n$。（$sum$ 为该数组原来的 元素和）

若和小于 $n$，那么我们只需要添加一个大小为 $sum-n+1$ 的数就好了！答案为 $1$。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 105
int t;
int read(){
	int w=0,f=1;
	char c=getchar();
	while (c>'9'||c<'0'){
		if (c=='-') f=-1;
		c=getchar();
	}
	while (c>='0'&&c<='9'){
		w=(w<<3)+(w<<1)+(c^48);
		c=getchar();
	}
	return w*f;
}

int main(){
	t=read();
	while (t--){
		int n=read(),ans=0;
		for (int i=1;i<=n;i++) ans+=read()-1;
		if (ans<0) puts("1");
		else printf("%d\n",ans); 
	}
	return 0;
}
```


---

## 作者：Terraria (赞：0)

不难发现，若要使一个长度为 $k$ 的数列的平均值为 $1$，那么这个数列中的各个数字之和应当等于 $k$。

现在题目中给出了 $n,a_i(1 \leq i \leq n)$，我们记 $s=\sum_{i=1}^na_i$，对 $s$ 进行分类讨论：

对于 $s<n$ 的情况，我们可以加上一个数 $n-s+1$，这个时候数列中有 $n+1$ 个数，每个数之和为 $s+n-s+1=n+1$，因此平均值为 $1$，满足题目要求，故输出 $1$。

对于 $s=n$ 的情况，直接输出 $0$ 即可。

对于 $s>n$ 的情况，我们可以给数列添加 $s-n$ 个 $0$，这个时候数列长度为 $n+s-n=s$，各个数字之和为 $s$，因此平均值为 $1$，满足题目要求，故输出 $s-n$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int T;
int main(){
	cin>>T;
	while(T--){
		int n,a[100009],s=0;
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			s+=a[i];
		}
		if(s>=n) cout<<s-n<<endl;
		else cout<<1<<endl;
	}
}
```


---

## 作者：StayAlone (赞：0)

### 题意

给定一个长度为 $n$ 的只包含整数的序列，请你在这个序列中增加一些非负数，使得所有数的平均数为 $1$。请你输出最少需要增加几个数。  

### 思路

此题是一道比较简单的通过构造得出结论的题目。  

我们先算出这个序列中所有元素的和 $sum$，接下来判断：

- 如果 $sum = n$，说明无需增加任何数，输出 $0$；
- 如果 $sum < n$，一定有方案可以只加一个数达到要求，输出 $1$；
- 如果 $sum > n$，就只需要尽量多的放 $0$ 进入序列，只需要加 $sum - n$ 个 $0$ 即可，输出 $sum - n$。  

[AC code记录](https://www.luogu.com.cn/record/51906841)

```cpp
#include <bits/stdc++.h>
#define fr(i, l, r) for (int i = l; i <= r; ++i)
using namespace std;
int t, n, a[55];

int main()
{
	scanf("%d", &t);
	while (t--)
	{
		scanf("%d", &n);
		int sum = 0, cnt = 0;
		fr(i, 1, n) scanf("%d", a + i), sum += a[i];
		if (sum == n) puts("0");
		else if (sum > n) printf("%d\n", sum - n);
		else puts("1");
	}
	return 0;
}
```

---

## 作者：int32 (赞：0)

### 前言

看到咕值又掉了，来水篇题解……

### 题意简述

[题目传送门](/problem/CF1537A)

给定一个数组 $a_{1\cdots n}$，问至少添加多少个非负整数使得整个数列元素的平均值是 $1$。

### 思路分析

为了书写简洁，设 $s=\sum_{i=1}^n a_i$，$v$ 是加上的数的个数。

- $\dfrac{s}{n}=1$，不需要加数。

- $\dfrac{s}{n}<1$，加一个数（即 $(n-s+1)$ ）。

- $\dfrac{s}{n}>1$，此时不能加正数，只能加 $0$。（想想为什么）

#### 讨论当 $s>n$ 时应该加几个 $0$

设要加 $z$ 个 $0$，则

$$\dfrac{s}{n+z}=1$$
$$s=n+z$$
$$z=n-s$$

所以只用加 $(n-s)$ 个 $0$。

### 代码展示

```cpp
namespace code{
	typedef long long ll;
	const int inf=0x3f3f3f3f3f;
	const int _=1e5+10;
	const int mod=998244353;
	const int modu=1e9+7;
   	const double eps=1e-7;
   	ll t, n, s, a, v;
	void find_ans(){
		cin>>t;
		while(t--){
			s=n=v=a=0;
			cin>>n;
			fr(i,1,n,1){
				cin>>a;
				s+=a;
			}
			if(s==n) v=0;//Case 1
			else if(s<n) v=1;//Case 2
			else v=s-n;//Case 3
			cout<<v<<'\n';
		}
	}
};
```

求赞求互关求评论！

---

## 作者：FjswYuzu (赞：0)

原问题题意是，在一个长度为 $n$ 的数列后加入 $k$ 个非负整数使得整个数列的平均数为 $1$ 的最小的 $k$。

那么考虑分类讨论。令 $sum = \sum a_i$，那么：

- 如果 $sum>n$，最优的方法是往后加入若干个 $0$。易得这个 $0$ 的个数，即 $k$，为 $sum-n$；   
- 如果 $sum=n$，不加即可，答案为 $0$；   
- 如果 $sum<n$，加入一个数即可，答案为 $1$。

代码由上述思路综合。

---

## 作者：Cripple_Abyss (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF1537A)

## Description 

- 给定一个有 $n$ 个整数的数列 。

- 求至少加上多少个非负整数（即自然数）才能使目前数列的平均值为 1 。

- 目前数列包括加上去的数。

## Solution

- 一个明显的结论题，需要分三种情况讨论：

- 用 $s$ 表示原数列的总和 , $ans$ 表示至少加上多少个数。

- 若 $s = n$ , 易得 $ans = 0$ 。 

- 若 $s < n$ , 易得 $ans = 1$ (加的数为 $n+1-s$ )。

- 若 $s > n$ , 易得 $ans = s - n$ (至少加 ($s-n$) 个 0 ) 。

## Code 
```cpp
#include <cstdio>
typedef long long ll;
inline void in(ll &x) {
	x=0;
	ll f=1;
	char ch=getchar();
	while (ch<'0'||ch>'9') {
		if (ch=='-') f=-1;
		ch=getchar();
	}
	while (ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	x*=f;
}
inline void out(ll x) {
	if (x<0) putchar('-'),x=-x;
	if (x>9) out(x/10);
	putchar(x%10+'0');
}
ll n,T,a[55],s;
int main() {
	in(T);
	while (T--) {
		in(n);
		s=0;
		for (ll i=1; i<=n; ++i) in(a[i]),s+=a[i];
		if (s==n) puts("0");
		else if (s<n) puts("1");
		else out(s-n),putchar('\n');
	}
	return 0;
}
```

---

## 作者：所有人袛旳 (赞：0)

题意是想让你加一些非零整数使得这一串数的平均数为 $1$ ，也就是和等于个数。分类讨论即可。

设数组的和为 $s$ ，个数为 $n$ 
- $s=n$ 时 , 只需要输出 $0$ 即可。
- $s<n$ 时，此时可以直接加一个足够大的非零整数使得平均数为 $1$ ,所以输出 $1$ 。
- $s>n$ 时，则需要你加若干个零使得它们相等，则需要加 $s-n$ 个 $0$ 。所以输出 $s-n$ 。

## code
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,s,a,i;
int main(){
	cin>>T;
	while(T--){
		cin>>n;
		for(i=0;i<n;i++){
			cin>>a;
			s+=a;
		}
		if(s==n){
			cout<<0<<endl;
		}else if(s>n){
			cout<<s-n<<endl;
		}else{
			cout<<1<<endl;
		}
		s=0;
	}
	return 0;
}
```


---

