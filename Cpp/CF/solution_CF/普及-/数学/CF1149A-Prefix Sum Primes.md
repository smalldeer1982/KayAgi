# Prefix Sum Primes

## 题目描述

We're giving away nice huge bags containing number tiles! A bag we want to present to you contains $ n $ tiles. Each of them has a single number written on it — either $ 1 $ or $ 2 $ .

However, there is one condition you must fulfill in order to receive the prize. You will need to put all the tiles from the bag in a sequence, in any order you wish. We will then compute the sums of all prefixes in the sequence, and then count how many of these sums are prime numbers. If you want to keep the prize, you will need to maximize the number of primes you get.

Can you win the prize? Hurry up, the bags are waiting!

## 说明/提示

The first solution produces the prefix sums $ 1, \mathbf{\color{blue}{2}}, \mathbf{\color{blue}{3}}, \mathbf{\color{blue}{5}}, \mathbf{\color{blue}{7}} $ (four primes constructed), while the prefix sums in the second solution are $ 1, \mathbf{\color{blue}{2}}, \mathbf{\color{blue}{3}}, \mathbf{\color{blue}{5}}, 6, \mathbf{\color{blue}{7}}, 8, 10, \mathbf{\color{blue}{11}} $ (five primes). Primes are marked bold and blue. In each of these cases, the number of produced primes is maximum possible.

## 样例 #1

### 输入

```
5
1 2 1 2 1
```

### 输出

```
1 1 1 2 2
```

## 样例 #2

### 输入

```
9
1 1 2 1 1 1 2 1 1
```

### 输出

```
1 1 1 2 1 1 1 2 1
```

# 题解

## 作者：Frozencode (赞：2)

这题并不难想，我们知道$>2$的偶数都不是素数，那么一个很朴素的想法：先放一些$1$和$2$使得前缀和$=3$然后把剩下的$2$全部放进去，再把剩下的$1$全部放进去就行了。这样的话我们就不会错过所有$<=\sum\limits_{i=1}^na_i$的素数，所以答案一定是最优的。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll maxn=500010;
const ll INF=2147483647;
ll n,a[maxn],cnt,b[maxn],tot,icnt;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		if(a[i]==2)cnt++;
	}
	icnt=n-cnt;
	if(icnt>=1)
	{
		if(cnt)
		{
			cnt--;
			icnt--;
			b[++tot]=2;
			b[++tot]=1;
			for(int i=1;i<=cnt;i++)b[++tot]=2;
			for(int i=1;i<=icnt;i++)b[++tot]=1;
		}
		else
		{
			for(int i=1;i<=icnt;i++)b[++tot]=1;
		}
	}
	else
	{
		for(int i=1;i<=cnt;i++)b[++tot]=2;
	}
	for(int i=1;i<=tot;i++)cout<<b[i]<<" ";
	return 0;
}
```


---

## 作者：Biuld (赞：1)

如果我们枚举下素数：
$$2, 3, 5, 7, 11, 13, 17, 19, 23……$$
容易发现，除了 $2$ 以外的素数都是奇数。（这是常识吧）   
我们就可以先手动凑出 $2$ 和 $3$，再输出所有的 $2$， 这样就可以保证我们的前缀和肯定是连续的奇数， 不会放过任何一个素数。最后输出所有的 $1$，这时的前缀和就会是一串连续的整数，自然也不会漏过任意一个素数。这样，我们就肯定可以得到最多的质数。

代码：
```
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;

int n, x;
int a, b;

int main(){
	ios::sync_with_stdio(false);
	
	cin >> n;
	for(int i = 1; i <= n; ++ i){
		cin >> x;
		x == 1 ? a ++ : b ++; //a 为 1 的个数， b 为 2 的个数
	}
	
	if(a >= 1 && b >= 1){ //能凑出 2 和 3
		cout << 2 << ' ' << 1 << ' '; //先凑 2 和 3
		a --; b --;
		
		for(int i = 1; i <= b; ++ i){ //全输出 2
			cout << 2 << ' ';
		}
		for(int i = 1; i <= a; ++ i){ //全输出 1
			cout << 1 << ' ';
		}
		
		return 0;
	}
	// 剩下的情况，就必然是只有 1 或只有 2
	if(a == 0){
		for(int i = 1; i <= b; ++ i){
			cout << 2 << ' ';
		} return 0;
	}
	if(b == 0){
		for(int i = 1; i <= a; ++ i){
			cout << 1 << ' ';
		} return 0;
	}
	
	return 0;
}
```
感谢观看

---

## 作者：exited (赞：1)

题意：

给定一个长度为 $n$ 的只包含 $1,2$ 的序列，将序列重排，使得其前缀和中为素数的数量最多。

### 分析：

素数中除了 $2$，其他的相邻素数之间的差都大于等于 $2$，而且较小的数中，素数密度比较大，所以这么贪心：

1. 如果全部是 $1$ 直接输出即可（全部是 $2$ 也同理）；

2. 输出 $2$ $1$（因为 $1$ 不是素数，$2$ 的下一个素数是 $3$），先把剩下的 $2$ 输完，在输完剩下的 $1$；

**注意，一定是先输出** $2$**，再输出** $1$，因为素数除 $2$ 外都是奇数，而输完 $2$ $1$ 后前缀和为 $3$，先输出 $2$ 不会改变其奇偶性，也能保证不会漏。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,sum,tt,a,tt2;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a;
		if(a==2) tt++;
		else tt2++;
	}
	if(tt){
		cout<<2<<' ';
		tt--;
		if(tt2){
			cout<<1<<' ';
			tt2--;
			for(int i=1;i<=tt;i++)
				cout<<2<<' ';
			for(int i=1;i<=tt2;i++)
				cout<<1<<' ';
		}
		else for(int i=2;i<=n;i++)
			cout<<2<<' ';
	}
	else{
		for(int i=1;i<=n;i++)
			cout<<1<<' ';
	}
	return 0;
}
```


---

## 作者：Rainbow_qwq (赞：1)

[CF1149A Prefix Sum Primes](https://www.luogu.org/problem/CF1149A)

# 思路

简单构造。~~但我还是调了很久~~

开两个桶$c[1],c[2]$存$1$与$2$的个数。  
输出一个数的函数：
```cpp
inline void P(int x){
	printf("%d ",x);
	c[x]--;
}
```

除了$2$以外的所有质数都是奇数。  
于是就有一个想法：先凑出$3$，然后后面不停加$2$，最后全放$1$。

然而有2个问题。

1. 数字总和小于$3$，凑不出。 
解决方案：直接把所有$1$放前面，所有$2$放后面。

```cpp
if(c[1]+c[2]*2<3)//数字总和小于3
{
	while(c[1])P(1);
	while(c[2])P(2);
	return 0;
}
```

2. 全部都是$2$  
更简单，直接输出。

```cpp
if(!c[1]){//没有1，全是2
	while(c[2])P(2);
	return 0;
}
```

剩下情况都能凑出$3$,那就先凑出$3$，然后全部摆$2$,最后全部摆$1$。

```cpp
//凑出3
if(c[2])P(2),P(1);
else P(1),P(1),P(1);
//输出剩下
while(c[2])P(2);
while(c[1])P(1);
return 0;
```

# 完整代码

```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(register int i=(a);i<=(b);++i)
#define Rep(i,a,b) for(register int i=(a);i>=(b);--i)
using namespace std;
inline int read()
{
    char c=getchar();int x=0;bool f=0;
    for(;!isdigit(c);c=getchar())f^=!(c^45);
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
    if(f)x=-x;return x;
}
int n,c[3];
inline void P(int x){
	printf("%d ",x);
	c[x]--;
}
int main()
{
	n=read();
	For(i,1,n){
		int x=read();
		c[x]++;//用桶统计
	}
	if(c[1]+c[2]*2<3)//数字总和小于3
	{
		while(c[1])P(1);
		while(c[2])P(2);
		return 0;
	}
	if(!c[1]){//没有1，全是2
		while(c[2])P(2);
		return 0;
	}
	//凑出3
	if(c[2])P(2),P(1);
	else P(1),P(1),P(1);
	//输出剩下
	while(c[2])P(2);
	while(c[1])P(1);
	return 0;
}
```

---

## 作者：Loser_King (赞：1)

## 真·模拟
### 分析：
仔细观察素数数列：
$$\xRightarrow{+2}2\xRightarrow{+1}3\xRightarrow{+2}5\xRightarrow{+2}7\xRightarrow{+4}11\xRightarrow{+2}13\xRightarrow{+4}17\xRightarrow{+2}19\xRightarrow{+4}23......$$
再观察和组成的数列：
$$+2,+1,+2,+2,+4,+2,+4,+2,+4......$$
这个数列即是我们所要求的答案。

而题目只要求我们用$1,2$，又因为：
$$1+1=2,2+2=4......$$
所以我们可以得到一个比较另类的算法：
```
	if(_2--){
		printf("2 ");
		if(_1--){
			printf("1 ");
			while(_2--)printf("2 ");
			while(_1--)printf("1 ");
		}else while(_2--)printf("2 ");
	}else while(_1--)printf("1 ");
```
其中```_1,_2```表示1,2的个数。
    L8和L7都是特殊情况，L4~6是普通情况。
完整$\texttt{Code:}$
```
#include<ccstdio>
int n,_1,_2;
int main(){
	scanf("%d",&n);
	while(n--){
		int a;scanf("%d",&a);
		a==1?_1++:_2++;
	}
	if(_2--){
		printf("2 ");
		if(_1--){
			printf("1 ");
			while(_2--)printf("2 ");
			while(_1--)printf("1 ");
		}else while(_2--)printf("2 ");
	}else while(_1--)printf("1 ");
}
```
这里的$\texttt{Code}$过不了样例，但是因为此题spj，所以可以AC.


---

