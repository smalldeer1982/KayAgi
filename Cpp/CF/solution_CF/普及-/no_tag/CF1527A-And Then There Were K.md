# And Then There Were K

## 题目描述

给定一个正整数 $n$，请你求出一个最大的正整数 $k$，满足 $n \& (n-1)\&(n-2)\&...\&(k)$ 的值为 0。（这里的 $\&$ 指的是按位与操作，即 ` C++` 语言里的 `&` 运算符）

## 样例 #1

### 输入

```
3
2
5
17```

### 输出

```
1
3
15```

# 题解

## 作者：到底几只鱼呢 (赞：3)

题意简述:给定 $n$ ，求使得下式成立的最小 $k$。

$$
n\  \&\  (n-1) \&\ (n-2)\ \&\ \dots (k)=0
$$

不难发现，当上式有一项满足等于 $0$ 时，其后的计算结果一定为 $0$。

考虑这样一种情况：最高位为 $1$，其它都为 $0$ 的数 $a$，去 $\&$ 一个最高为 $0$，其它都为 $1$ 的数 $b$，显然满足：$a-1=b$，且 $a$ 为 $2$ 的整数次幂。

即找到小于 $n$ 的最大 $2$ 的幂 $-1$即为答案。（可以用 $log2()$ 函数求）

### Code:

```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <queue>
using namespace std;

int T,n;
int main() {
	cin>>T;
	while(T--) {
		cin>>n;
		int tmp=log2(n);
		cout<<(1<<tmp)-1<<"\n";
	}
	return 0;
}
```


---

## 作者：Aw顿顿 (赞：2)

## 题意

给定一个 $n$，求一个最大的 $k$，使得存在：

$$n\ \text{and}\ n-1\ \text{and}\ n-2\ \text{and}\cdots\ \text{and}\ k+1\ \text{and}\ k=0$$

对于 $T$ 组测试数据的每一个 $n$，输出对应的最大的 $k$。

## 解法

乍一看挺麻烦的，但是其实不难处理。

首先，对于这些数，他们的按位和运算结果是 $0$，这意味着这些数每一个位置都至少有一个 $0$，而这恰恰意味着，对于最大的 $k$，我们一定能找到一个数 $x$，使得：

$n$ 最高位的 $1$ 所处的位置，$x$ 也是 $1$。

因为我们知道 $n$ 是这一列中最大的数，而所以比他小的数当中，一定存在一个“最高位”是 $0$ 的数使得 $n$ 最高位按位和的结果为 $0$，所以这个 $x$ 一定存在比他小的数，于是 $x$ 一定在这个数列中。

同时，我们可以发现，$x-1$ 实际上就是最高位为 $0$ 的一个最大数，在这种情况下这个 $x-1$ 就可以作为 $k$。

因为以上的推论，我们只需要找到这个最高位是 $1$ 的 $x$ 就行了，怎么找呢？因为这个数是一个形如 $2^m$ 的数，我们只需要结合 $\log_2$ 函数就可以计算了。

## 代码

注意 $\log_2$ 返回的是浮点数，需用强制类型转换。

```cpp
#include<bits/stdc++.h>
using namespace std;
int T;
int main(){
	cin>>T;
	while(T--){
		int n;cin>>n;
		cout<<(1<<(int)log2(n))-1<<endl;
	}return 0;
}
```

---

## 作者：Exber (赞：2)

## 题意
- #### 给定一个正整数 $n$，求一个最大的正整数 $k$，满足 $n \& (n-1)\&(n-2)\&...\&(k)$ 的值为 0。（这里的 $\&$ 指的是按位与操作，即 `C++` 语言里的 `&` 运算符）
- #### 一共有 $t$ 组数据。对于每一组数据，你需要读入一个正整数 $n$ 并输出对应的 $k$ 的值。

## 做法
数学推导。

如果一些数按位与之后的值为 `0`，那么就表明 `0` 在每一个二进制的数位上都至少出现了一次。例如

```
111
011
101
110
```

这些二进制数按位与之后的值就为 `0`，因为 `0` 在每一位上都至少出现了一次；而

```
111
011
010
110
```
这些二进制数按位与之后的值就不为 `0`，因为 `0` 在从左往右数第三位上没有出现过。

很容易发现，因为题目要求的是连续的自然数按位与之后的值为 `0`，所以只要按位与到 $n$ 的二进制下的最高的为 `1` 的位变为 `0` 就可以了。因为 `0` 肯定早就已经在其它数位出现过了。

例如 $n$ 的二进制为 `1111` 时，就只要按位与到 `0111`。

可以把求 $n$ 的二进制最高的为 `1` 的位所代表的数字写成一个函数，函数名叫 `highbit`。那么只要输出 $highbit(n)-1$ 就行了。 

那 `highbit` 函数怎么实现呢？可以借助 `lowbit` 函数，不断地将 $n$ 减去 $lowbit(n)$，直到减去后 $n$ 为 `0` 为止。此时的 $lowbit(n)$ 即是 $highbit(n)$ 的值。`highbit` 函数的伪代码便是：

```
highbit(x)
{
   re=0
   while(x>0)
   {
       re=lowbit(x)
       x-=re
   }
   return re
}
```

## AC 代码
```cpp
#include <iostream>
#include <cstdio>

using namespace std;

inline int lowbit(int x) // lowbit
{
	return x&-x;
}

inline int highbit(int x) // highbit
{
	int re=0;
	while(x>0) // 重复执行直到 x 为 0 为止 
	{
		re=lowbit(x); // 更新返回值 
		x-=re;        // 更新 x 
	}
	return re;
}

int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
		int n;
		scanf("%d",&n);
		printf("%d\n",highbit(n)-1);
	}
	return 0;
}
```


---

## 作者：LYqwq (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1527A)

# 题目大意

给定一个正整数 $n$，求出一个最大的 $k$，满足 $n\&(n-1)\&(n-2)\&...\&(k)=0$。

# 思路

先来手算一下答案是啥。

以 $n=15$ 为例，$15$ 的二进制为 $1111$。

进行一下操作：

- `1111`&(`1111`-$1$)=`1110`；
- `1110`&(`1111`-$2$)=`1100`；
- `1100`&(`1111`-$3$)=`1100`；
- `1100`&(`1111`-$4$)=`1000`；
- `1000`&(`1111`-$5$)=`1000`；
- `1000`&(`1111`-$6$)=`1000`；
- `1000`&(`1111`-$7$)=`1000`；
- `1000`&(`1111`-$8$)=`0000`；

到 $k=7$ 时圆满结束。

可以推断出，从 $k$ 到 $n$ 的二进制中，第一位永远不是 $0$。等到 $k-1$ 时，才会出现第一位是 $0$ 的情况。那么最终的 $k$ 的二进制位数等于 $n$ 的二进制位数减一，那么 $\lfloor \log_2n \rfloor$ 就是 $k$ 的位数，那么 $2^{\lfloor \log_2n \rfloor}$ 就是最小的 $n$ 的位数的数，它减一就是答案 $k$ 了。

最终答案为：$2^{\lfloor \log_2n \rfloor}-1$，即 `(1<<(int)log2(n))-1`。

# 代码

```cpp
#include <iostream>
#include <cmath>
using namespace std;
int t,n;

int main(){
	cin >> t;
	while(t--){
		cin >> n;
		cout << (1<<(int)log2(n))-1 << endl; // 直接套
	}
	return 0;
}
```

---

## 作者：D2T1 (赞：1)

### 思路：

从 $n$ 到 $2^{\lfloor log_{2}{n}\rfloor}$ 这些数 $\text {and}$ 起来后的二进制必定为 $1000...0$，因为**这些数二进制表示最高位都为 $1$** 且 **$2^{\lfloor log_{2}{n}\rfloor}$ 这个数二进制表示为 $1000...0$**。

所以这些数再 $\text{and}$ 一个 $2^{\lfloor log_{2}{n}\rfloor}-1$ 就为 $0$ 了。

------------

### 例子：

$19 \to 10011$

$2^{\lfloor log_{2}{19}\rfloor}=2^4=16 \to 10000$

$16-1=15 -> 1111$

$10011\&10000\&1111=0$

------------

### 代码：

```cpp
//CF1527A
#include <cstdio>
#include <cmath>

int main(){
	int t,n;
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		printf("%d\n",(1<<(int)(log(n)/log(2)))-1);
		//这里log_2(n)=log(n)/log(2)
		//记得转换为int类型
	}
	return 0;
}
```


---

## 作者：xfrvq (赞：1)

[原题链接](/problem/CF1527A)

[博客食用](/blog/368107/solution-cf1527a)

---

**题目大意**

给定一个 $n$ ，求最大的 $k$ ，使得

$$n\operatorname{and}\space(n-1)\operatorname{and}\space(n-2)\cdots\operatorname{and}k=0$$

其中 $\operatorname{and}$ 表示按位与运算

---

**解法**

[在百度百科了解按位与运算](https://baike.baidu.com/item/%E6%8C%89%E4%BD%8D%E4%B8%8E/9601818)

根据按位与运算的定义，只要在 $n\cdots k$ 中，每一个二进制位都有一个数，它的这个二进制位是 $0$

以 $17$ 为例

$17$ 的二进制形式：$10001$

不难看出，想要让其第一位是 $0$ ，最大的数会是：$01111$ 。

同时，如果想让后面的位都是 $0$ ，最大的数会是：$10000$ ，这个数是大于第一位是 $0$ 的那个二进制数的。

所以答案就应该是一个二进制下总位数与原数相同，且第一位是 $0$，后面都是 $1$ 的数

这个数就等于 $2^{\log n}-1$

----

**[$\color{#52C41A}\texttt{AC Code}$](https://www.luogu.com.cn/record/51096374)**

```cpp
#include<stdio.h>
#include<math.h>
int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		int n;
		scanf("%d",&n);
		printf("%d\n",(1 << int(log2(n))) - 1); 
	}
	return 0;
}

```

---

## 作者：miao5 (赞：0)

**题目大意**

给定 $n$ ，让你求 $k$ ,使得 $n$&$(n-1)$&$(n-2)$&$…$&$k$ 等于 0 。

**大体思路**

根据运算符的性质，可以理解为在 $n$ 的每个二进制位上，从 $n$ 到 $k$ 的每一位上至少有一个是 0 。

之后我们考虑第一位是 0 的情况，这种情况的最大值肯定是 $01111111…$ ，可以和这个相对应的数是 $10000000…$ 。
又因为 $10000000…$ 大于 $01111111…$ ，所以答案就是 $2^{log(n)}-1$ 。

**code:**

```cpp
#include<iostream>
#include<cmath>
using namespace std;
int main(){
	int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		cout<<(1<<int(log2(n)))-1<<endl;
	}
} 
```


---

## 作者：joy2010WonderMaker (赞：0)

本蒟蒻的第十五篇题解。

### 题目分析

首先，分析题目。按位于如果结果为零，那也就意味着它每一位都有一个零。首先你输入的这个数，开头一定有一个二进制1，比如10的二进制是1010，11是1011。那么我们只要找到一个第一位是0的就可以，由于要最大，所以就是比 $n$ 小的2的次幂减1。

### AC Code

```cpp
#include<cstdio>
#include<cmath>
long long mici[32];
int main(){
    mici[0]=1;
    for(int i=1;i<32;i++)mici[i]=pow(2,i);//先将幂次算出来，方便计算
    int t;
    scanf("%d",&t);
    while(t--){
        long long n;
        scanf("%lld",&n);
        for(int i=31;i>=0;i--){//判断小于n的最大2的幂次
            if(mici[i]<=n){
                printf("%lld\n",mici[i]-1);//输出
                break;
            }
        }
    }
    return 0;
}
```


---

## 作者：Sai_t (赞：0)

首先，暴力会TLE。

但是，我们可以找找规律。样例输入输出分别为：

input1:2$\qquad$output1:1

input2:5$\qquad$output2:3

input3:17$\quad\quad\!\!\!$output3:15

我们发现，三个输出都是 $2^n-1$。所以，推测答案就是小于输入的最大的 $2^n-1$。

为什么呢？

首先，可以证明，没有比上述答案还大的可能答案。因为计算到最大的 $2^n$时，二进制最高位依然是1。

其次，计算到最大的 $2^n$时，当前答案的二进制一定是 $(100\dots 00)_{2}$ （因为 $2^n$已经是这个了），而最大的 $2^n-1$是 $(11\dots 11)_{2}$ 所以，计算到此数时，答案一定是0。

AC Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
int main(){
	cin>>t;
	while(t--){
		cin>>n;int w=1;
		while(w<=n)w*=2;w/=2;
		cout<<w-1<<endl;
	}
	return 0;
}
```


---

## 作者：WanderingTrader (赞：0)

upd on 5/21：添加了一些说明。

做一些简单的构造即可。

若要让所有数的与值为0，则对每一位二进制都会存在一个数使得该数中这一位为0。

因此令 $x=\lfloor\log_2n\rfloor$， $f(i,n)$ 为比 $n$ 小且二进制位中第 $i$ 位为0的数中最大的一个。则答案为 $\min\{f(i,n)|0\le i\le x\}$。这样从 $n$ 一直与到答案就能保证为0了。

如果 $n\operatorname{and}2^i=0$，则 $f(i,n)=n$。

否则我们把这一位上的二进制变成0，然后把后面所有的二进制位全部变成1，该数即为 $f(i,n).$

那么如果 $i=x$，则 $f(i,n)=2^x-1$，其他情况下 $f(i,n)$ 的第 $x$ 位二进制必为1，故 $f(i,n)\ge2^x$

于是 $\min\{f(i,n)|0\le i\le x\}=2^x-1$ 即为答案。

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,k;
int main()
{
	scanf("%d",&T);
	for(;T;--T)
	{
		scanf("%d",&n);
		k=log2(n);
		printf("%d\n",(1<<k)-1);
	}
	return 0;
}
```

---

