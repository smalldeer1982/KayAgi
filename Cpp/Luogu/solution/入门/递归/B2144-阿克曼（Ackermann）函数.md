# 阿克曼（Ackermann）函数

## 题目描述

阿克曼（Ackermann）函数 $A(m,n)$ 中，$m, n$ 定义域是非负整数（$m \le 3$，$n \le 10$），函数值定义为：

$\mathit{A}(m,n)=n+1$；（$m=0$ 时）。

$\mathit{A}(m,n)=\mathit{A}(m-1,1)$；（$m>0$、$n=0$ 时）。

$\mathit{A}(m,n)=\mathit{A}(m-1,\mathit{A}(m,n-1))$；（$m,n>0$ 时）。

## 样例 #1

### 输入

```
2 3```

### 输出

```
9```

# 题解

## 作者：vegetable_king (赞：27)

在[博客](https://yjh965.github.io/post/ackmann-han-shu-ti-jie/)食用更佳。

本蒟蒻的第 $4$ 篇题解！

# 前置芝士（递归）
> 递归作为一种算法在程序设计语言中广泛应用，
基本含义是指函数、过程、子程序在运行过程序中直接或间接调用自身而产生的重入现象。——360百科

推荐一个讲递归比较清楚的[博客](https://www.cnblogs.com/Pushy/p/8455862.html)

我并不认为递归像最上面说的那样麻烦，我认为递归就只是递归边界和函数调用的是罢了。

举个栗子：
```cpp
int fib(int x){
	if (x < 3) return 1; // 递归边界
	return fib(x - 1) + fib(x - 2); // 函数递归调用
```
上面的函数，是求斐波那契数列第 $x$ 项的代码。

通过这个栗子，我们可以看出，递归边界是为了在特定情况下，防止函数再递归调用下去。上面，如果没有递归边界，这个函数就会继续调用，产生 $fib(0)$，$fib(-1)$ 等等奇怪的情况。而这一个递归边界，就是在函数无法再递归下去的时候（如果 $x<3$，$x-1$ 和 $x-2$ 其中一定会至少有一项 $<1$，也就是不合法）终止递归，返回斐波那契数列的第一项或第二项——$1$。

递归调用函数则是核心，每一个答案都是从其他的答案推导过来的。

如果我们往这个函数里传入一个参数 $5$，这个函数会发生像这样的事情：

$fib(5)$

$=fib(4)+fib(3)$

$=(fib(3)+fib(2))+(fib(2)+fib(1))$

$=((fib(2)+fib(1))+1)+(1+1)$

$=((1+1)+1)+2$

$=5$

每一项都是由前两项推导而成，这就是递归的一种简单的使用方法。

# 思路
这道题已经给你了所有的递归边界和递归调用方法，你只要把它转换成代码的形式，你就成功了！

# 代码
```cpp
#include <bits/stdc++.h>
 
using namespace std;
 
int a, b;
int ack(int a, int b){
    if (a == 0) return b + 1;
    if (b == 0) return ack(a - 1, 1); // 递归边界
    return ack(a - 1, ack(a, b - 1)); // 函数递归调用
}
int main(){
    cin >> a >> b;
    cout << ack(a, b);
}
```

---

## 作者：WanderingTrader (赞：9)

从对函数的定义可以看出，这个函数的计算需要使用递归。直接按照定义来写即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m;
int a(int m,int n) // akm(m,n)
{
    if(m==0) return n+1;
    if(m>0&&n==0) return a(m-1,1);
    if(m>0&&n>0) return a(m-1,a(m,n-1));
}
int main() 
{
   scanf("%d%d",&m,&n);
   cout<<a(m,n);
   return 0;
}
```
通过一些测试数据可以看出，阿克曼的函数增长的非常快，因此它的反函数，即反阿克曼函数增长的非常慢。使用路径压缩的并查集单次操作均摊时间复杂度为 $O(\log n)$，加上按秩合并后降低即为反阿克曼函数，可以近似成一个常数。
>对于 $\forall n\le2^{2^{10^{19729}}}$，都有 $a(n)<5$   ——《进阶指南》

$$\texttt{The End.}$$

---

## 作者：daiarineko (赞：8)

## 题意简述

要求计算阿克曼函数的值。

$akm(m,n)=n+1~~(m=0)$

$akm(m,n)=akm(m-1,1)~~(m>0,n=0)$

$akm(m,n)=akm(m-1,akm(m,n-1))~~(m,n>0)$

## 解法1

使用纯递归。

递归参数：$m,n$

结束条件：$m=0$

```cpp
#include<bits/stdc++.h>
using namespace std;
long long akm(long long m,long long n){
    if(m==0)return (n+1);
    if(n==0)return akm(m-1,1);
    return akm(m-1,akm(m,n-1));
}
int main(){
    long long m,n;
    cin>>m>>n;
    cout<<akm(m,n)<<endl;
}
```

## 解法2

使用记忆化搜索。

这种方法记录已经得到的子问题结果，以此减少重复调用。

```cpp
#include<bits/stdc++.h>
using namespace std;
const long long mod=2147483648LL;
long long ans[10][100000];
bool hasans[10][100000];
long long akm(long long m,long long n);
long long _akm(long long m,long long n){
    if(m==0)return (n+1)%mod;
    if(n==0)return akm(m-1,1)%mod;
    return akm(m-1,akm(m,n-1))%mod;
}
long long akm(long long m,long long n){
    if(!hasans[m][n]){
        hasans[m][n]=1;
        ans[m][n]=_akm(m,n);
    }
    return ans[m][n];
}
int main(){
    long long m,n;
    cin>>m>>n;
    cout<<akm(m,n)<<endl;
}
```

经测试，同一组数据，解法1使用 `500ms`，解法2使用 `200ms`。

这两种方法可以通过此题，但数据更大就无法计算了，需要递推等不依赖栈的算法。

---

## 作者：ZhaiOverflow (赞：4)

## 分析

**本题所需知识：函数的递归。**

函数递归，即函数自身调用自身。在本题中，只需按题意写出函数，直接模拟即可。

代码：
```
#include<bits/stdc++.h>
using namespace std;

int acm(int m, int n) {
    if(m == 0) return n + 1;
    if(n == 0 && m > 0) return acm(m - 1, 1);
    if(m > 0 && n > 0) return acm(m - 1, acm(m, n - 1));
}

int main() {
    int a, b;
    cin >> a >> b;
    cout << acm(a, b);
    
    return 0;
}
``

---

## 作者：Kobe_Bryant824 (赞：3)

简单的递归，代码如下：
```cpp
#include <iostream>
#include <cstdio>
using namespace std;
int m, n;
int akm(int m, int n) {
    if(m==0) return n+1;	//递归边界1：m=0时，由题可知
    if(n==0 && m>0) return akm(m-1, 1);	//递归边界2：由题可知
    return akm(m-1, akm(m, n-1)); 	//其他情况，照常递归
}
int main() {
    scanf("%d%d", &m, &n);	//输入
    printf("%d", akm(m, n));	//调用akm函数并输出
    return 0;
}
```


---

## 作者：baiABC (赞：2)

只要依据题意模拟即可。

C++ 支持递归，于是直接可以给出代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int akm(int m, int n)
{
    if(m == 0) return n+1;
    // 能运行到这里说明 m != 0, 又 m >= 0，所以这里 m > 0
    if(n == 0) return akm(m-1, 1);
    // 这里一定有 m > 0, n > 0.
    return akm(m-1, akm(m, n-1));
}
int main()
{
    int a, b;
    cin >> a >> b;
    cout << akm(a, b) << endl;
    return 0;
}
```
这可以看做是一道递归的模板题。

---

