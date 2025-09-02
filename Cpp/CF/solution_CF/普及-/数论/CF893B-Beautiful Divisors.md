# Beautiful Divisors

## 题目描述

Recently Luba learned about a special kind of numbers that she calls beautiful numbers. The number is called beautiful iff its binary representation consists of $ k+1 $ consecutive ones, and then $ k $ consecutive zeroes.

Some examples of beautiful numbers:

- $ 1_{2} $ ( $ 1_{10} $ );
- $ 110_{2} $ ( $ 6_{10} $ );
- $ 1111000_{2} $ ( $ 120_{10} $ );
- $ 111110000_{2} $ ( $ 496_{10} $ ).

More formally, the number is beautiful iff there exists some positive integer $ k $ such that the number is equal to $ (2^{k}-1)*(2^{k-1}) $ .

Luba has got an integer number $ n $ , and she wants to find its greatest beautiful divisor. Help her to find it!

## 样例 #1

### 输入

```
3
```

### 输出

```
1
```

## 样例 #2

### 输入

```
992
```

### 输出

```
496
```

# 题解

## 作者：Yizhixiaoyun (赞：7)

### [题目传送门](https://www.luogu.com.cn/problem/CF893B)

## 题目分析

此题数据范围较小，因此做题的方法考虑**暴力**，直接枚举所有满足 $(2^k-1)\times(2^{k-1})$ 的数 $s$ ，再判断它是否是 $n$ 的因数。

## 贴上代码

```cpp
#include<iostream>
#include<cmath>
using namespace std;
int n,s,k=1;
int ans;
int main(){
    cin>>n;
    while((pow(2,k)-1)*(pow(2,k-1))<=n){
        s=(pow(2,k)-1)*(pow(2,k-1));
        if(n%s==0) ans=(pow(2,k)-1)*(pow(2,k-1));
        k++; 
    }
    cout<<ans;
}
```


---

## 作者：Miller2019 (赞：6)

实际上不用先做一个程序，打表算出数来。直接把它放在主程序里就行了，时间够。

这是正解：在程序内计算完美数。

```cpp
#include<stdio.h>
#include<math.h>
int n,i,j,s;long long a[16];
int main()
{
	scanf("%d",&n);
	for(i=1;i<16;i++)
	{
		a[i]=(pow(2,i)-1)*pow(2,i-1);//按照题目计算。
	}
	for(i=1;i<=n;i++)
	{
		if(n%i==0)
		{
			for(j=1;j<=15;j++)
			{
				if(i==a[j])
				{
					s=i; //如果是，就赋值成答案。
				}
			}
		}
	}
	printf("%d",s);
	return 0;
}
```
亲测：632ms /  0B

打表， 15 个足够了，可以从后往前试，这样快：

```cpp
#include<stdio.h>
int ans[]={1,6,28,120,496,2016,8128,32640},n,i=7;
int main()
{
	scanf("%d",&n);
	for(;i>-1;i--)
	{
		if(n%ans[i]==0)
		{
			printf("%d",ans[i]);
			return 0;
		}
	}
}
```
亲测：679ms /  0B

也可以用位运算。 1<<n 的意思是 2^n。但是位运算速度特别快。



```
#include<stdio.h>
int n,ans=1,now;
int main()
{
	scanf("%d",&n);
	for(int i=1;(1<<i)<=n;i++)
	{
		now=((1ll<<i)-1)*(1ll<<(i-1));	1ll表示long long类型的 1，不开 ll 可能会爆。
		if(n%now==0) //除尽了
		{
			ans=now;
		}
	}
	printf("%d",ans);
	return 0;
}
```


亲测：587ms /  0B

蒟蒻的第 9 篇题解。

---

## 作者：yzy041616 (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF893B)

## Part.1 题目

让我们找最大的能表示成 $(2^k-1) \times 2^{k-1}$ 的 $n$ 的因数。$\color{white}这么个水题。$

## Part.2 思路

用位运算很好做。因为 $s<<k$ 就是  $s \times 2^k$。

$2^k-1$ 是 $(1<<k)-1$，注意！如果写 $1<<k-1$ 会被算成 $2^{k-1}$，一定要加上括号！**位运算符号优先级比加减乘除还要高！**

$(2^k-1) \times 2^{k-1}$ 就是 $(1<<k)-1<<k-1$ 了。

最后，$k$ 从大到小模拟，看一下数据范围，$1 \le n \le 10^5$，估计 $k$ 最大也到不了 $10$。

## Part.3 代码

```cpp
#include<iostream>
using namespace std;
int main(){
	int n;cin>>n;
	for(int k=10;k;k--){//k最大10
		int s=(1<<k)-1<<k-1;//位运算
		if(n%s==0){
			cout<<s；
			return 0;//求最大的所以有一个就直接退出
		}
	}
}
```

$\color{white}看过我写的题解的人都知道不应该直接拷贝我的代码，因为我把一些分号改成了全角的。$

---

## 作者：_QrSn_ (赞：1)

### 题意
给出 $n(1\leq n\leq10^5)$ ,输出 $n$ 的最大因数 $s$ ,使得 $s$ 能表示为 $(2^k-1)\times(2^{k-1})$

### 方法
先看数据范围 $1\leq n\leq10^5$ ,很小，而在这个范围中，能符合题意的数只有 $8$ 个： $1,6,28,120,496,2016,8128,32640$ ，然后从后面往前找（保证最大），一旦可以被 $n$ 整除，就输出并退出。

### AC Code
```
#include<iostream>
using namespace std;
int a[9]={1,6,28,120,496,2016,8128,32640};
int n;
int main() {
	cin>>n;
	for(int i=8-1;i>=0;i--)//下标从0开始，所以i=8-1
    {
        if(n%a[i]==0)
        {
            cout<<a[i];
            break;
        }
    }
	return 0;
}
```


---

## 作者：_Hero_ (赞：0)

# 分析
数据很小 $1\leq n \leq 10^5$ ,可以考虑暴力或打表。这个范围可以先找出符合条件的数，再用数组打表。这样还减少时间。可以发现，符合的有这几个数字： $1,6,28,120,496,2016,8128,32640$ ，接着就是解决输出最大因数的问题了，可以逆向思维，用 ```for``` 从后往前寻找，符合条件就输出，为了不输出几个答案，输出之后要退出。

# 注意点
- 因为要保证最大，所以要从后往前找。
- 输出后要退出。
- 如果数组下标从 $0$ 开始，要从 $7$ 开始找。

# 代码
```
#include<bits/stdc++.h>
using namespace std;
int a[1000]={1,6,28,120,496,2016,8128,32640},n;
int main() {
   cin>>n;
   for(int i=7;i>=0;i--)//下标是0，i=7开始
   {
      if(n%a[i]==0)//求的是因数
      {
      cout<<a[i];
      return 0;//结束
      }
   }
   return 0;
}
```


---

## 作者：V1mnkE (赞：0)

赞美翻译QwQ。

题意说的很清楚了，因为 $n$ 的范围只有 $10^5$ ，而在这个范围里可以表示成 $(2^k-1)\times (2^{k-1})$ 的只有 $1,6,28,120,496,2016,8128,32640$，可以直接拿一个数组存起来，从大往小枚举。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[8]={1,6,28,120,496,2016,8128,32640},n;
int main(){
	cin>>n;
	for(int i=7;i>-1;i--)if(n%a[i]==0)cout<<a[i],exit(0);
}
```

---

## 作者：lrmlrm_ (赞：0)

# 题意 
  给出 $ n $ ， 求 $ n $ 最大的因数 $ s $ ， 使得 $ s $ 可以表示成 $ ( 2 ^ k - 1 ) \times ( 2 ^ { k - 1 } ) $ 的形式 。 
  
# 思路
  
  这题很简单 ， 因为在 $ 10 ^ 5 $ 中 ， " 完美数 " 只有  
  
  $ 1 , 6 , 2 8 , 1 2 0 , 4 9 6 , 2 0 1 6 , 8 1 2 8 , 3 2 6 4 0 $ 。
  
  
   所以我们只需要从最大的到最小的找哪一个能被 $ n $ 整除 ， 输出即可 。

# 代码

```cpp
#include<bits\stdc++.h>
using namespaoe std;
int a[]={1,6,28,120,496,2016,8128,32640};
int n;
int mian(){
    scanf("%d",&n);
    for(int i=7;i>=0;i--)
        if(n%a[i]==0){
            printf("%d",a[i]);
            break;
        }
    return 0;
}
```

---

## 作者：封禁用户 (赞：0)

#### 题目分析

这题给出了一些完美数的二进制和十进制，那二进制有什么用呢？我们可以找规律。

$6=3*2=(2^2-1)*(2^{2-1})$

这时，$k=2$。

因为 $6$ 的二进制是 $110$ ，所以我们可以发现，完美数的二进制是由 $k$ 个 $1$ 和 $k-1$ 个 $0$ 组成的。

比如：

1. 二进制数 $110$ 是 $2$ 个 $1$ 和 $1$ 个 $0$ 组成的，可以转换为十进制数 $6$。

2. 二进制数 $1111000$ 是 $4$ 个 $1$ 和 $3$ 个 $0$ 组成的，可以转换为十进制数 $120$。

虽然不能直接求出完美数，但是我们可以枚举 $k$，然后把 $k$ 个 $1$ 和 $k-1$ 个 $0$ 放进一个字符串里 ，再转换成十进制，这样就可以得到所有完美数。然后从大到小判断是不是 $n$ 的因数，如果是就输出。

#### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a[100];
string st;
long long zh(string st)
{
	long long x=1,s=0;
	for(int i=st.size()-1; i>=0; i--)
	{
		s+=(st[i]-48)*x;
		x*=2;
	}
	return s;
}
int main()
{
	for(int i=1; i<=10; i++)
	{
		st="";
		for(int j=1; j<=i; j++)st+="1";
		for(int j=1; j<i; j++)st+="0";
		a[i]=zh(st);
	}
	cin>>n;
	for(int i=10; i>=1; i--)
	{
		if(n%a[i]==0)
		{
			cout<<a[i];
			return 0;
		}
	}
    return 0;
}
```


---

## 作者：封禁用户 (赞：0)

# 题意

给定 $n$，求 $n$ 最大的因数 $s$，使 $s$ 能表示成 $(2^k-1)\times(2^{k-1})$ 的形式。

# 思路

这道题的数据范围很小，$n$ 最大才 $10^5$，而在 $10^5$ 里只有 $1$,$6$,$28$,$120$,$496$,$2016$,$8128$,$32640$ 符合条件，从大到小一个个枚举，如果除得尽，直接输出即可。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n;
int main()
{
	cin>>n;
	if(n%32640==0) cout<<32640;
	else if(n%8128==0) cout<<8128;
	else if(n%2016==0) cout<<2016;
	else if(n%496==0) cout<<496;
	else if(n%120==0) cout<<120;
	else if(n%28==0) cout<<28;
	else if(n%6==0) cout<<6;
	else cout<<1;
	return 0;
}
```

---

## 作者：zwy__ (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/CF893B)
### 题意
让你找 $n$ 以内最大的可以表示成 $(2^k-1)\times(2^{k-1})$ 的因数。
### 思路
暴力，直接枚举 $n$ 以内的可以表示成 $(2^k-1)\times(2^{k-1})$ 的数，在判断这个数是不是 $n$ 的因数。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int ma,n,k,s;
int main()
{
    cin>>n;
    k=1;
    while((pow(2,k)-1)*(pow(2,k-1))<=n)
    {
        s=(pow(2,k)-1)*(pow(2,k-1));
        if(n%s==0)
        {
            ma=(pow(2,k)-1)*(pow(2,k-1));
        }
        k++; 
    }
    cout<<ma;
    return 0;
}
```

---

## 作者：ylinxin2010 (赞：0)

## CF893B题解

首先我们确定这题的思路。

思路就是——暴力枚举。

那么就算我们不知道他的个数，我们也能用覆盖的原理(赋值两次只会取决于后面的那次)去除错误答案。

所以我们只要一直枚举，就能求出最后的答案。

那枚举时如何判断呢？

$pow(a,b)$ 可以快速地求出 $a^b$ 的值。

所以我们只要判断是否 $n \equiv 0 \pmod{(2^{k}-1)^2}$ 就可以得出正确答案。

最后输出最小因数即可。

接下来——上代码。
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n, ans=1, a;
	cin>>n;
	while((pow(2,ans)-1)*pow(2,ans-1)<=n)
	{
		if(n%int((pow(2,ans)-1)*pow(2,ans-1))==0)
		{
			a=(pow(2,ans)-1)*pow(2,ans-1);
		}
		ans++;
	}
	cout<<a;
	return 0;
}
```

---

## 作者：Eason_AC (赞：0)

## Content
给定一个数 $n$，求出 $n$ 最大的可以表示成 $(2^k-1)\cdot2^{k-1}$ 形式的因数 $x$。

**数据范围：$1\leqslant n\leqslant 10^5$。**
## Solution
数据范围很小，所以我们先考虑将 $10^5$ 以内的能够表示成 $(2^k-1)\cdot2^{k-1}$ 形式的数全部通过打表生成出来。而且打完以后，我们发现，事实上满足这个条件的数在 $10^5$ 以内只有 $8$ 个：$1,6,28,120,496,2016,8128,32640$。

然后输入完 $n$，就直接从 $n$ 开始往 $1$ 直接枚举，一旦找出了可以表示成 $(2^k-1)\cdot2^{k-1}$ 的因数就直接输出即可。
## Code
```cpp
int num[17], n, cnt, vis[200007];

int main() {
    while(num[cnt] <= 100000) ++cnt, num[cnt] = (1 << (2 * cnt - 1)) - (1 << (cnt - 1));
    F(int, i, 1, cnt) vis[num[i]] = 1; 
	n = Rint;
    R(int, i, n, 1) if(vis[i] && !(n % i)) return write(i), 0;
    return 0;
}
```

---

## 作者：_caiji_ (赞：0)

别的题解都是套公式生成“完美数”的，这里介绍一种递推构造“完美数”的做法。

首先，根据题目描述，“完美数”是指在 $\bold{2}$ **进制**下由连续 $k+1$ 个 $1$ 和连续 $k$ 个 $0$ 组成的数。设 $a_i$ 表示第 $i$ 个完美数，那我们想想，$a_i$ 和 $a_{i+1}$ 之间有什么关系呢？

随便选 $2$ 个完美数，就 $a_4=120$ 和$a_5=496$ 吧。我们把它们的二进制形式写出来：

$$
\begin{cases}
1111000 &(120)\cr
111110000 &(496)\cr
\end{cases}
$$

不难发现，$a_{i+1}$ 的位数比 $a_i$ 的多 $2$ 位。那我们把刚才的 $1111000$ 左移 $2$ 位试试：（左移`<<`，就是在一个数的末尾添上 $n$ 个 $0$）

$$
\begin{cases}
111100000 &(120 << 2)\cr
111110000 &(496)\cr
\end{cases}
$$

这两个数已经很接近了，唯一的区别就是**从右往左数**第 $5$个数字不同。将 $n$ 的第 $k$ 位改为 $1$ 可以使用位运算“或”（或`|`，逐位进行类似逻辑或的运算），即 $n|(1<<(k-1))$，为什么这样写呢？设 $n=20,k=2$，列竖式验证一下。

$$
\begin{aligned}
&20_{10}=10100_2\cr
&1_{10}<<(2_{10}-1_{10})=1_2<<1_{10}=10_2\cr
\end{aligned}
$$
$$
\begin{aligned}
10100&\cr
|\quad 10&\cr
----&\cr
10110&\cr
\end{aligned}
$$
（如果不理解，可以根据算式理解一下）

所以，我们得出以下结论：

$$
a_i=\begin{cases}
1&i=1\cr
a_{i-1}<<2|(1<<(i-1))&i>1\cr
\end{cases}
$$

有了这个结论，我们就可以递推构造“完美数”了，其实不开数组记录也可以。程序如下：
```cpp
#include <cstdio>
using namespace std;
int n,ans;
int main(){
    scanf("%d",&n);
    for(int i=1,j=1;i<=n;j++){
    //i为递推的“完美数”，j为这是第几个“完美数”。
        if(n%i==0&&i>ans) ans=i;
        //由于是递推，只能从小到大，所以需要存最大的答案。
        i=(i<<2)|(1<<j);
        //结论的C++版本，前面一对括号是为了改变优先级，防止出错。
        //之所以j不用-1，是因为例如算a_2时j为1，不需要额外-1。
    }
    printf("%d",ans);
    return 0;
}
```
本题解若有不足之处，请多多指教。

---

## 作者：封禁用户 (赞：0)

先翻译一下

最近，卢芭学到了一种特殊的数字，她称之为美丽的数字。它的二进制表示由k+ 1个连续的1，然后k个连续的0组成，这些是一些美丽数字的例子:

12(110);1102(610);11110002(12010)1111100002(49610)。更正式地说，如果存在某个正整数k，这个数是美丽的，它等于(2k-1) * (2k-1)

Luba有一个整数n，她想找到它最大的美丽的除数。帮她找到它

其实这一题是非常的water的。你先写一个程序求出一些完美数，放心，第十五个完美数就已经有536854528了，建议用longlong，这15个数字是：

0,1,6,28,120,496,2016,8128,32640,130816,523776,2096128,8386560,33550336,134209536,536854528

从第十五开始尝试，如果n%number[i]==0就可以输出了

以下是生成完美数的程序↓↓↓
```
#include<bits/stdc++.h>
using namespace std;
long long p;
int main()
{
	freopen("check.txt","w",stdout);
	for(int i=1;i<=15;i++)
	{
		p=(pow(2,i)-1)*(pow(2,i-1));
		cout<<p<<',';
	}
	return 0;
}

```

以下是正确程序↓↓↓
```
#include <bits/stdc++.h>
using namespace std;
long long check[19]={0,1,6,28,120,496,2016,8128,32640,130816,523776,2096128,8386560,33550336,134209536,536854528};
int n;
int main()
{
	cin>>n;
	for(int i=15;i>=1;i--)
	{
		if(n%check[i]==0)
		{
			cout<<check[i];
			return 0;
		}
	}
}
```

---

