# Jeff and Rounding

## 题目描述

题意:

你有一个长度为2n的序列,将其中的n个数向下取整,n个数向上取整,求|原序列的和 - 取整后序列的和|的最小值.

## 说明/提示

x:[0,10000]
n:[1,2000]

注意:

None.

感谢@尘染梦 提供的翻译

## 样例 #1

### 输入

```
3
0.000 0.500 0.750 1.000 2.000 3.000
```

### 输出

```
0.250
```

## 样例 #2

### 输入

```
3
4469.000 6526.000 4864.000 9356.383 7490.000 995.896
```

### 输出

```
0.279
```

# 题解

## 作者：Feyn (赞：1)

[link](https://www.luogu.com.cn/problem/CF351A) & [my blog](https://feynn.github.io/)

显然整数部分没什么用，只需要读入小数部分即可。可以把小数部分看成是一个个的三位数，上取整相当于是把数变成一千，下取整相当于是变成零。所以问题大概是这样的：有 $2m$ 个数，和是固定的，希望把其中的 $m$ 个数变成 $1000$，剩下的数变成 $0$，求和的变化量的最小值。

显然上面的描述是不完美的，因为如果一个数原来就是 $0$，那么这个数上取整之后仍然是 $0$，假设这样的数的个数是 $n$，思考一下最后和的上下界：$m$ 个选出来上取整的数中最多有 $n$ 个零，所以和的下界应该是 $\max(m-n,0)\times 1000$；相似地，和的上界应该是 $\min(2m-n,m)\times 1000$。对这个范围中的整千数找和原来的和最接近的即可。

代码非常简单就不放了。

---

## 作者：DiDi123 (赞：1)

# 一、题意
给 $2n$ 个数，将其中 $n$ 个数向上取整，剩下的向下取整，并求和，求取整后的和与原序列的和的差最小是多少。

# 二、分析
这道题看到先想到暴力，但是每个数有两种选择，复杂度直接 $O(2^n)$ 爆炸。

在想想取整的性质，设数 $x=a+b$（$a$ 是 $x$ 的整数部分，$b$ 是 $x$ 的小数部分），易知 $b<1$ 且 $\lfloor x \rfloor =a=x-b$。还可以发现 $\lceil x \rceil=a+1=x+1-b$，那么新序列的和就是 $\sum x-\sum {\{ x \}}+n$（$\{ x \}$ 表述 $x$ 的小数部分）。然后我们会发现这个式子很不对劲，既然已经都确定和了怎么还求最小值呢？

我们再考虑一下向上取整的式子，发现其实这个式子并不是对所有的数都成立，当 $x$ 为整数时，$\lceil x \rceil=x$。但是向下取整的式子是对的，所以我们只需要统计出来有多少个整数，然后枚举有多少个整数是向上取整就好了。

# 三、代码
```cpp
#include <bits/stdc++.h>
using namespace std;
##### #define MAXN 4002
int n,sum;
double a[MAXN],ls,y,minn=1e10,cnt;
// ls代表小数部分之和，cnt代表原序列和，y为一个数的小数部分
int main()
{
	cin>>n;
	for(int i=1;i<=n*2;i++)
		cin>>a[i];
	for(int i=1;i<=n*2;i++)
	{
		y=a[i]-int(a[i]);
		if(!y) sum++;
		else ls+=y;
		cnt+=a[i];
	}
	for(int i=0;i<=min(n,sum);i++)
		minn=min(minn,abs(i-n+ls)); //cnt-(cnt+n-i-ls)=i-n+ls
	cout<<fixed<<setprecision(3)<<minn;
	
}
```


---

## 作者：Hades18 (赞：1)

介绍一种比较妙的解法.

设向下取整的n个数的小数部分和为A,向上取整的为B,其中有k个整数向上取整了,原序列的小数部分和为sum.

则最后所求的```ans=A-(n-k-B)```,(这一步好好想一下).

ans=A-(n-k-B)=A+B-(n-k)=sum-n+k;

此时只有k为变量,暴枚一下就好了...

注意：k的枚举范围为```[max(0,k-n),min(n,k)]```

具体见代码：
```
#include<cmath>
#include<cstdio>
#include<iostream>
inline int read(){
	int x=0,f=0;
	register char ch=getchar();
	for(;ch<48||ch>57;ch=getchar())f|=ch=='-';
	for(;ch>47&&ch<58;ch=getchar())
	x=(x<<1)+(x<<3)+(ch^48);
	return f?~x+1:x;
}
using namespace std;
int main()
{
	int n=read(),num=0;double ans=1e9,sum=0;
	for(int i=0;i<n<<1;++i)
	{
		double t;scanf("%lf",&t);
		int x=t;sum+=t-x;
		if(t==(double)x)++num;
	}
	for(int i=max(0,num-n);i<=min(n,num);++i)
		ans=min(ans,abs(sum-n+i));
	printf("%.3lf",ans);
	return 0;
}
```

---

