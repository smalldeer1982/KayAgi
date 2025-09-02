# Petya and Inequiations

## 题目描述

对于给出的整数 $n, x, y,$ 找出一个正整数数组 $a$ ，满足：

$\begin{cases}a_1^2+a_2^2+...+a_n^2\geq x\\a_1+a_2+...+a_n\leq y\end{cases}$

## 说明/提示

对于 $100 \%$ 的数据：

$1\leq n\leq 10^5$

$1\leq x\leq 10^{12}$

$1\leq y\leq 10^6$

## 样例 #1

### 输入

```
5 15 15
```

### 输出

```
4
4
1
1
2
```

## 样例 #2

### 输入

```
2 3 2
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
1 99 11
```

### 输出

```
11
```

# 题解

## 作者：vanueber (赞：2)

[CF原题传送门](https://codeforces.com/contest/111/problem/A)

# 题目大意

找到一个数组 $a$ ，满足：

- $ a_{1}^{2}+a_{2}^{2}+...+a_{n}^{2}\ge x $
- $ a_{1}+a_{2}+...+a_{n}\le y $

# 题目分析

核心：求出 $a_{1}$ 的最大值。

因为 $a_{i}>0$，$a_{i}^{2}>0$，且 $a_{i}$ 为正整数，所以 $a_{i}\geq 1$，不妨令 $a_{1}$ 之外的数都为 $1$，根据 $ a_{1}+a_{2}+...+a_{n}\le y $ 可以得到 $a_{1}$ 的最大值，我们将其代入 $ a_{1}^{2}+a_{2}^{2}+...+a_{n}^{2} \ge x $ 计算，如果不满足，因为 $a_{1}$ 之外的数都为 $1$，$a_{1}$ 已经取到了最大值，剩下的情况更加不可能满足，输出 $-1$，满足则直接输出答案即可。具体实现见代码部分。

# 代码

```cpp
#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;

long long n,x,y;

int main()
{
	cin>>n>>x>>y;
	long long maxx=y-(n-1); //求出a[1]最大值 
	if(y>=n)
	{
		if(n-1+maxx*maxx>=x)
		{
			cout<<maxx<<endl;
			for(int i=1;i<n;i++)
			{
				cout<<1<<endl;
			}
			return 0;
		}
		else
		{
			cout<<"-1";
			return 0;
		}
	}
	else //y<n一定不满足 
	{
		cout<<"-1";
	}
	return 0;
} 

```

[AC记录](https://codeforces.com/problemset/submission/224/218662251)

---

## 作者：Eason_AC (赞：2)

## Content
请找出一个由 $n$ 个正整数组成的数列 $\{a_1,a_2,\dots,a_n\}$，满足以下两种条件：

- $\sum\limits_{i=1}^na_i^2\geqslant x$。
- $\sum\limits_{i=1}^na_i\leqslant y$。

**数据范围：$1\leqslant n\leqslant 10^5$，$1\leqslant x\leqslant 10^{12}$，$1\leqslant y\leqslant 10^6$。**
## Solution
我们不妨设 $f(x)=x^2(x>0)$，然后画出这个函数的图像之后不难看出 $f(x)$ 是增函数，且随着 $x$ 的增长，其值越来越大。因此我们考虑这样的一个贪心：将前 $n-1$ 个数全部赋值为 $1$，最后一个数赋值为 $y-(n-1)=y-n+1$。然后再计算 $1^2\cdot(n-1)+(y-n+1)^2$ 是否 $\geqslant x$，是的话直接输出方案，否则输出 $-1$。

另外这题还要注意一个特判：因为题目中并没有保证 $y\geqslant n$，而要求的数列又要求全是正整数。所以如果 $y<n$，那么也无法得到合法的方案，输出 $-1$。
## Code
```cpp
ll ans[100007], xx;

int main() {
	int n = Rint; ll x = Rll; int y = Rint;
	if(y < n) return puts("-1"), 0;
	F(i, 2, n) ans[i] = 1;
	ans[1] = y - n + 1;
	F(i, 1, n) xx += 1ll * ans[i] * ans[i];
	if(xx < x) return puts("-1"), 0;
	F(i, 1, n) write(ans[i]), puts("");
	return 0;
}
```

---

## 作者：追风少年σχ (赞：2)

### 难得做一次第一篇，当然要详细一点啦

##### 一.问题描述与转化
原题题意:给定正整数n,x,y,若已知$\sum\limits_{i=1}^n a_i \leq y$,令S=$\sum\limits_{i=1}^n a_i^2$,求出$ S_{max} $以及此时的{$ a_1,a_2,···,a_n$},将$S_{max}$与x进行比较。而显然在$\sum\limits_{i=1}^n a_i=y$时,S才可能取最大(~~想想为什么？~~)。所以在做的时候保证$\sum\limits_{i=1}^n a_i=y$(其中$a_i\in N_+$).

##### 二.分析
1.问题：什么时候S取最大值？

2.猜想与假设：

n=2,y=4时,
$$\because 3^2+1^2>2^2+2^2 $$
$$\therefore S_{max}=10$$

n=3,y=8时
$$\because 6^2+1^2+1^2>5^2+2^2+1^2>4^2+3^2+1^2···$$
$$\therefore S_{max}=38$$

n=4,y=7时，有$S_{max}=4^2+1^2+1^2+1^2=19$

n=5,y=10时，有$S_{max}=6^2+1^2+1^2+1^2+1^2=40$

你发现了什么？？？
貌似$S_{max}=(n-1)*1^2+(y-n+1)^2$！

3.结论:
   $$S_{max}=(n-1)*1^2+(y-n+1)^2$$
（请读者自证,欢迎巨佬们提供证明补全题解）

##### 三.代码实现
贴上AC代码
```cpp
#include<cstdio>
#include<iostream>
using namespace std;
long long n,x,y,Maxnum,S_max;//清晰易懂的变量名
void print(){//输出
    for(int i=1;i<n;i++)
        printf("1\n");
    cout<<Maxnum;
}
int main(){
    cin>>n>>x>>y;
    Maxnum=y-n+1;
    S_max=Maxnum*Maxnum+n-1;//求出Smax
    if(S_max<x||n>y)cout<<"-1";//n>y是最后一个点的特判，因为a[i]都是正整数，所以必须n<=y
    else print();
    return 0;
}
```
简单的O(n)算法

~~蒟蒻妹子的题解求通过~~


---

## 作者：hyjdouSHEN (赞：1)

[原题传送门](https://www.luogu.com.cn/problem/CF111A)

## 题目分析

引理 $(a+b-1)^{2}+1 \geq a^{2}+b^{2}$

引理证明：先将左式拆开，得 $a^{2}+b^{2}+2ab-2a-2b+2$，移项可得 $2ab-2a-2b+2 \geq 0$，又因为 $a$ 与 $b$ 均为正整数，所以 $ab+1>2a$ 且 $ab+1>2b$，引理证毕。

根据引理，我们可以看出在数列中选择 $a+b+1$ 与 $1$ 比选择 $a$ 与 $b$ 一定不会更差，能选 $a+b+1$ 与 $1$ 我们就不会选 $a$ 与 $b$，所以为了使数列更大概率满足题意，最优数列就是选 $n-1$ 个 $1$ 与 $1$ 个 $y-n-1$，算出平方和若仍不大于 $x$，则没有满足题意的数列了，因为此数列是最优；若满足题意，就直接输出。

温馨提示：需特判 $y < n$，因为任意 $a_{i}$ 为正整数，所以这种情况是无解的，应输出 $-1$。

## 代码部分

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	long long n,x,y;
	cin>>n>>x>>y;
	if(y<n){
		cout<<-1;
		return 0;
	}
	y=y-n+1;
	x=x-n+1;
	if(y*y>=x){
		for(int i=1;i<=n-1;i++){
			cout<<1<<endl;
		}
		cout<<y;
	}
	else cout<<-1;
	return 0;
}
```

希望这篇题解对你有帮助~

[AC记录](https://www.luogu.com.cn/record/120717435)

---

## 作者：lovely_fcukh (赞：1)

## 题目大意
给定三个数 $n,x,y$，找到一个长度为 $n$ 的数组 $a_1$ 到 $a_n$ 要求满足： 
* $\sum\limits_{i=1}^na_i^2\leqslant y $
* $\sum\limits_{i=1}^na_i\geqslant x $

## 思路
我们可以发现如果将一个 $a$ 拆分成 $b$ 和 $c$，$b^2+c^2 \leq a^2$，所以我们可以将数组的前 $n-1$ 个数全部赋值为 1，最后一个数赋值为满足第一点的最大值 $(y-n+1)^2+n-1$ 如果这个数组满足第二点，那么就可以输出这个数组，否则输出 -1。

## AC代码
```
#include<bits/stdc++.h>
using namespace std;
int n,x,y,s;
int main(){
	cin>>n>>x>>y;
	s=pow((y-n+1),2)+n-1;
	if(s>=x&&y>=n){
		for(int i=1;i<n;i++)cout<<"1\n";
		cout<<y-n+1;
	}
	else cout<<-1;
	return 0;
}
```

---

## 作者：MrJC_Pandingding (赞：1)

# [题目传送门](https://www.luogu.com.cn/problem/CF111A)
# 解题思路
先满足第二个条件。这里我们采用极端思想，令 $\sum_{i=1}^{n}a_i=y$。如果等于 $y$ 时无法满足，则小于 $y$ 时更无法满足。此时 $n$ 个数的和已经确定，$(\sum_{i=1}^{n}a_i)^2=y^2$ 也已经确定，我们要构造一种最大的 $\sum_{i=1}^{n}a_i^2$，如果它还是比 $x$ 小，则无解，否则有解。而 $\sum_{i=1}^{n}a_i^2=(\sum_{i=1}^{n}a_i)^2-2\times\sum_{i=1}^{n}(\sum_{j=1}^{i-1}a_i\times a_j+\sum_{j=i+1}^{n}a_i\times a_j)$，所以我们要让 $\sum_{i=1}^{n}(\sum_{j=1}^{i-1}a_i\times a_j+\sum_{j=i+1}^{n}a_i\times a_j)$ 最小。

考虑一种贪心，令 $a_1\sim a_{n-1}$ 都是 $1$，则 $a_n=y-(n-1)=y-n+1$。此时，$\sum_{i=1}^{n}a_i^2=n-1+(y-n+1)^2$。如果这个值比 $x$ 小，则输出 `-1`，否则把我们构造的极端的数列输出。

注意，序列的每一项都必须是正整数，当 $y<n$ 时无法做到，所以要加特判，$y<n$ 时也无解。

最后，$1\le x\le10^6$，所以要开 `long long`。

此算法的时间复杂度为 $O(1)$，绝对不会超时。不明白为什么题解区其他大佬要先存入数组再求平方和。
# 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
int i,n,y;
long long x;
int main()
{
	scanf("%d%lld%d",&n,&x,&y);
	if(y<n||n-1+(y-n+1ll)*(y-n+1)<=x-1)
		puts("-1");
	else
	{
		for(i=1;i<=n-1;++i)
			puts("1");
		printf("%d",y-n+1);
	}
	return 0;
}
```

---

## 作者：Rookie_t (赞：0)

首先我们确定在哪些情况下本题无解。

这是一道构造题。 

首先，如果 $y<n$，无法表示，肯定无解。

如果这条不满足，还有两种情况。

 
如果有解，我们可以输出一串 $1$ 还有一个可能的最大值。 
 
然后，我们就应该确定这个最大值了。

因为有 $y-1$ 个 $1$，所以我们可以得到最大值就是 $n-y+1$。

然后带入二式，如果不满足，直接输出 $-1$。

如果满足条件，直接输出解。


```cpp

#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,x,y;
signed main(){
	cin>>n>>x>>y;
	int maxn = y-n+1; 
	if(y >= n){
		if(n-1+maxn*maxn >= x){
			cout<<maxn<<endl;
			for(int i = 1;i<n;i++){
				cout<<1<<endl;
			}
			return 0;
		}
		else{
			cout<<"-1";
			return 0;
		}
	}
	else{
		cout<<"-1";
	}
	return 0;
} 
```



---

## 作者：LiJinLin_AFO (赞：0)

# CF111A 题解

看到本题，我们第一眼会不知所措，再看一眼会发现这是一道贪心题。正常且聪明的人类会有一个猜想：有这样的一个数列，由 $n-1$ 个 $1$ 和 $1$ 个 $y-n-1$ 组成，如果这个数列满足 $\displaystyle  a_1^2+a_2^2+\cdots+a_n^2\ge x$ 的话，那么这个数列就是最优解。不过，如何证明？接下来，我们走进数学的世界。

首先，我们来证明：当 $a,b$ 为正整数时，$(a+b-1)^2+1^2\ge a^2+b^2$。

会证明的跳过，不会的来看：

左边：$((a+b)-1)^2 = (a+b)^2-2\times(a+b)+1^2=a^2+b^2+2ab-2a-2b-2$。

可列出式子：$2ab-2a-2b+2=2 \times(a-1)\times(b-1)\ge0$。

命题得证。

所以，我们间接地推理出，我们猜想的命题是正确的。具体的细节见代码。

```cpp
#include<stdio.h>
int main()
{
	long long n,x,y;
	scanf("%lld%lld%lld",&n,&x,&y);
	if(y<n){
		printf("-1");
		return 0;
	}//当n大于y时，不可能存在解法
	y=y-n+1;
	x=x-n+1;//数列中的最后一个数
	if(y*y>=x){
		for(int i=1;i<n;i++){
			printf("1\n");
		}
		printf("%d",y);
	}//当满足题目条件时，打印结果
	else printf("-1");//否则输出-1
	return 0;
}
```


---

## 作者：yuheng_wang080904 (赞：0)

## 题意

对于给出的整数 $n,x,y$，找出一个正整数数组 $a$ ，满足：$\sum_{i=1}^na_i^2\ge x$ 且 $\sum_{i=1}^{n}\le y$。

## 思路

令 $m=\sum_{i=1}^na_i^2$，易得当 $\sum_{i=1}^{n}=y$ 时，$m$ 才会取得最大值，接下来我们证明 $m_{max}=(n-1)\times1^2+(y-n+1)^2$。

当我们确定了 $n-2$ 个数之后，设剩下的两个数和为 $sum$，我们将两种方法进行对比，$1^2+(sum-1)^2$ 和 $i^2+(sum-i)^2(i\in N^+)$，作差法比较大小，$(1^2+(sum-1)^2)-(i^2+(sum-i)^2)=(sum+sum-1-i)(i-1)-(i+1)(i-1)=2sum(i-1)$，可见要使其值最大，则应当分为 $1^2+(sum-1)^2$。推广后则可得 $m_{max}=(n-1)\times1^2+(y-n+1)^2$，证毕。

## 代码
接下来放上我的代码，十分简短。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll n,x,y,maxi;
int main(){
	cin>>n>>x>>y;
	maxi=(y-n+1)*(y-n+1)+n-1;
	if(maxi<x||n>y)cout<<-1<<endl;
	else{
	    cout<<y-n+1<<endl;
	    for(ll i=1;i<n;i++)cout<<1<<endl;
	}
	return 0;
}
```


---

