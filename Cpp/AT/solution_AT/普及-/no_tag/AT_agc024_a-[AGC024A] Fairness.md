# [AGC024A] Fairness

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc024/tasks/agc024_a

高橋君、中橋君、低橋君は、それぞれ整数 $ A,B,C $ を持っています。 以下の操作を $ K $ 回行った後、高橋君の持っている整数から中橋君の持っている整数を引いた値を求めてください。

- $ 3 $ 人は同時に、他の $ 2 $ 人の持っている整数の和を求める。その後、自分の持っている整数を求めた整数で置き換える。

ただし、答えの絶対値が $ 10^{18} $ を超える場合は、代わりに `Unfair` と出力してください。

## 说明/提示

### 制約

- $ 1\ \leq\ A,B,C\ \leq\ 10^9 $
- $ 0\ \leq\ K\ \leq\ 10^{18} $
- 入力はすべて整数である

### Sample Explanation 1

$ 1 $ 回の操作後、高橋君、中橋君、低橋君の持っている整数はそれぞれ $ (5,4,3) $ となります。$ 5-4=1 $ を出力します。

## 样例 #1

### 输入

```
1 2 3 1```

### 输出

```
1```

## 样例 #2

### 输入

```
2 3 2 0```

### 输出

```
-1```

## 样例 #3

### 输入

```
1000000000 1000000000 1000000000 1000000000000000000```

### 输出

```
0```

# 题解

## 作者：billzd (赞：2)

由题目易得$A_i-B_i=B_{i-1}-A_{i-1}=-(A_{i-1}-B_{i-1})$

所以这是公比为 $-1$ 的等比数列，首项为 $A_{1}-B_1$ 。

代码如下:
___
```c
#include<stdio.h>
long long a,b,c,k;
int main(){
	scanf("%lld%lld%lld%lld",&a,&b,&c,&k);
	printf("%lld\n",(a-b)*((k&1)?-1:1));
	return 0;
}
```

---

## 作者：DreamsChaser (赞：2)

我们有：

$\begin{cases}A_i=B_{i-1}+C_{i-1}\\B_i=A_{i-1}+C_{i-1}\\C_i=A_{i-1}+B_{i-1}\end{cases}$

$\therefore \begin{cases}A_i=2\times A_{i-2}+B_{i-2}+C_{i-1}\\B_i=A_{i-2}+2\times B_{i-2}+C_{i-1}\end{cases}$

那么有 $A_i-B_i=A_{i-2}-B_{i-2}$

即：我们设 $A_0+B_0+C_0=x,A_1+B_1+C_1=y$

就有：

$$ans=\begin{cases}A_0+B_0&k\equiv 0\pmod2\\A_1+B_1&k\equiv 1\pmod 2\end{cases}$$

问题得解。

---

## 作者：phigy (赞：1)


已知：

$A_i=B_{i-1}+C_{i-1}$ ，

$B_i=C_{i-1}+A_{i-1}$ ，

$C_i=A_{i-1}+B_{i-1}$ ，

求 $A_k-B_k$ 。

三种方法 。

### 法1

$A_k-B_k=(B_{k-1}+C_{k-1})-(C_{k-1}+A_{k-1})$

 $ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ =B_{k-1}-A_{k-1}$
 
 $ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ =(-1)^k(A_{0}-B_{0})$
 
 ```cpp
#include <iostream>

using namespace std;

int a,b,c,k;


int main() 
{
    int i,j,k;
    cin>>a>>b>>c>>k;
    cout<<(-(k%2*2-1))*(a-b);
	return 0;
}

```

### 法2
 
令$S_k=A_k+B_k+C_k=2(A_{k-1}+B_{k-1}+C_{k-1})=2^k(A_0+B_0+C_0)$ 
 
$A_k=B_{k-1}+C_{k-1}$

$ \ \ \ \ \ \ =A_{k-2}+S_{k-2}$

$ \ \ \ \ \ \ =A_{k-2}+2^{k-2}(A_0+B_0+C_0)$

若$2|k$

$A_k=\sum_{i=1}^{\frac{k}{2}-1}4^i(A_0+B_0+C_0)+A_0$

$B_k=\sum_{i=1}^{\frac{k}{2}-1}4^i(A_0+B_0+C_0)+B_0$

$C_k=\sum_{i=1}^{\frac{k}{2}-1}4^i(A_0+B_0+C_0)+C_0$

若$2|k+1$

$A_k=2\sum_{i=1}^{\frac{k}{2}-1.5}4^i(A_0+B_0+C_0)+B_0+C_0$

$B_k=2\sum_{i=1}^{\frac{k}{2}-1.5}4^i(A_0+B_0+C_0)+A_0+C_0$

$C_k=2\sum_{i=1}^{\frac{k}{2}-1.5}4^i(A_0+B_0+C_0)+A_0+B_0$

此时若是还没有发现 $A_k-B_k$ 能够消掉那么可以用一些等比数列求和公式加快速幂。

### 法3

考虑暴力方法。

$\begin{pmatrix}
A_i\\B_i\\C_i 
\end{pmatrix}\begin{pmatrix}
0&1&1\\1&0&1\\1&1&0 
\end{pmatrix}=\begin{pmatrix}
A_{i+1}\\B_{i+1}\\C_{i+1} 
\end{pmatrix}$

所以

$\begin{pmatrix}
A_{k}\\B_{k}\\C_{k} 
\end{pmatrix}=\begin{pmatrix}
A_0\\B_0\\C_0 
\end{pmatrix}\begin{pmatrix}
0&1&1\\1&0&1\\1&1&0 
\end{pmatrix}^k$

用矩阵快速幂求之 。

---

## 作者：Otue (赞：1)

其实就是个大水题，干扰条件挺多。

只要求 $A_k-B_k$ 的值，所以 $C_i$ 这个东西毛用没有。

根据题目条件可得：

$A_i-B_i=B_{i-1}-A_{i-1}$（两式相减可得）

$=-(A_{i-1}-B_{i-1})$

所以 $\lbrace A_k-B_k\rbrace$ 是首项为 $A_0-B_0$，公差为 $-1$ 的等比数列。

易得：$A_k-B_k=(-1)^k\times(A_0-B_0)$。
 
但是这道题不用输出 `Unfair` ，因为 $A_k-B_k$ 的绝对值最多 $10^9$。

代码:
```c++
#include<bits/stdc++.h>
using namespace std;
long long a,b,c,k;//跟题目中的含义一样
int check(int i){//计算(-1)^k的值
	if(i%2==0) return 1;
	return -1;
}
int main(){
	cin>>a>>b>>c>>k;
	cout<<(a-b)*check(k)<<endl;
}
```

---

## 作者：MattL (赞：0)

答案求 $A_k-B_k$ ，所以我们只需要关注 $A_i-B_i$ 即可。
# **突破口：**
由题目的$A_i=B_{i-1}+C_{i-1}$和$B_i=A_{i-1}+C_{i-1}$可以发现，$C_{i-1}$是可以抵消的，所以可以这样推导：

$$\begin{aligned} A_i-B_i & = (B_ {i-1}+C_{i-1})-(A_{i-1}+C_{i-1})\\& =B_{i-1}+C_{i-1}-A_{i-1}-C_{i-1}\\&=B_{i-1}-A_{i-1}\\& =-1\times(A_{i-1}-B_{i-1})\end{aligned}$$

所以可以由递推公式转化成通项公式：

$$\begin{aligned}A_k-B_k&=-1\times(A_{k-1}-B_{k-1})\\
 &=(-1)^2\times(A_{k-2}-B_{k-2})\\
 &=(-1)^3\times(A_{k-3}-B_{k-3})\\
 &=(-1)^4\times(A_{k-4}-B_{k-4})\\
 &=\ \ \vdots\\
 &=(-1)^k\times(A_0-B_0)\end{aligned}$$
 
 
 
**众所周知，$(-1)^k$的值取决于$k$的奇偶性。若$k$为奇数，值为$-1$；但$k$为偶数时，值为$-1$。所以最终可以打出核心代码：**
 ```cpp
write(((k&1)?(-1):(1))*(A0-B0));
```
这里介绍一下三目运算符：
```cpp
逻辑语句?为真时执行的语句：为假时执行的语句
```
## 重点：
**由于题目说$1\le A_0,B_0,C_0 \le 10^9$，答案又是$\pm( A_0-B_0)$，范围在$10^9+10^9=2\times10^9$，又因为$2\times10^9<10^{18}$，所以不可能输出```Unfair```**


```cpp
#include <bits/stdc++.h>
#define raed read
using namespace std;
typedef long long ll;
inline ll read(){
   ll s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
void write(long long out){
	if(out<0){putchar('-');out=abs(out);}
	if(out>9)write(out/10);
	printf("%d",out%10);
}
int A0,B0,C0,k;
int main()//超短主函数
{
	A0=read();
	B0=read();
	C0=read();
	k=raed();
	write(((k&1)?(-1):(1))*(A0-B0));//k&1是k%2的位运算写法，会快一点
	puts("");//AT题千万不要忘这句
	return 0;
}

```

---

## 作者：atarashiTLE (赞：0)

### 写在前面
不开`long long`见祖宗！

---
### 思路
$\because A_i-B_i=(B_{i-1}+C_{i-1})-(A_{i-1}+C_{i-1})$

$\ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ =B_{i-1}-A_{i-1}$

$\ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ =(-1)\times (A_{i-1}-B_{i-1})$

又$\because 1\leq A_0,B_0\leq 10^9$

$\therefore |A_0-B_0|\leq 10^{18}$，不需特判`Unfair`。

---          
### 正解

由上，$A_i-B_i=(-1)^i\times (A_0-B_0)$

由此可以得出核心代码：
`ans=(-(k % 2 * 2 - 1)) * (a_0 - b_0)`。

太短，完整代码就不贴了。

---

## 作者：火车司机 (赞：0)

## 简要分析

先推一波式子

$$
\begin{aligned}

A_i-B_i&=(B_{i-1}+C_{i-1})-(A_{i-1}+C_{i-1}) \\

&=B_{i-1}-A_{i-1} \\

&=(-1) \times (A_{i-1}-B_{i-1})

\end{aligned}
$$

所以我们可以得到下面这个式子

$$
A_k-B_k=(-1)^k \times (A_0-B_0)
$$

因为 $1 \leq A_0,B_0,C_0 \leq 10^9$，即 $|A_0-B_0| \leq 10^{18}$，所以根本不需要判断 "Unfair" 的情况

## 完整代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define ri register int
using namespace std;
int a, b, c, k;
template <typename T>
inline void read(T &x)
{
	register T f = 0, c = getchar();
	for (; c < 48 || 57 < c; c = getchar())
		if (c == '-')
			f = 1;
	for (x = 0; 48 <= c && c <= 57; c = getchar())
		x = (x << 3) + (x << 1) + (c & 15);
	if (f)
		x = ~(--x);
}
template <typename T>
inline void print(T x)
{
	if (x < 0)
		putchar('-'), x = ~(--x);
	if (x > 9)
		print(x / 10);
	putchar(x % 10 | 48);
}
signed main()
{
	read(a), read(b), read(c), read(k), print((k & 1 ? -1 : 1) * (a - b));
	return 0;
}
```


---

