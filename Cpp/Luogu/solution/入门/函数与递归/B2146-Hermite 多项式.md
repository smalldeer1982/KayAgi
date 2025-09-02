# Hermite 多项式

## 题目描述

求 Hermite 多项式的值。

$$
h_n(x)=\left\{
\begin{aligned}
1&，&n=0\\
2x&，&n=1\\
2xh_{n-1}(x)-2(n-1)h_{n-2}(x)&，& n>1
\end{aligned}
\right.
$$



对给定的 $x$ 和正整数 $n$，求多项式的值。

## 说明/提示

$(n \le 8，x \le 8)$

## 样例 #1

### 输入

```
1 2```

### 输出

```
4```

# 题解

## 作者：MatrixGroup (赞：68)

根据 [cppreference.com](https://zh.cppreference.com/w/cpp/numeric/special_functions/hermite)，C++ 17 及以上在 `cmath` 库里提供了 `std::hermite` 函数求 Hermite 多项式的值。

使用该函数求值即可。

```cpp
#include<cstdio>
#include<cmath>
int n,x;
int main()
{
    scanf("%d%d",&n,&x);
    printf("%.0f\n",std::hermite(n,x));
    return 0;
}
```

---

## 作者：Starw (赞：15)

这道题一本通里是说用递归解，那我们就用递归解吧。

这道题比较良心，把**边界**和**如何调用下一层递归**都给你了，如下图：

![边界和如何调用下一层递归](https://cdn.luogu.com.cn/upload/image_hosting/qsdnnmu0.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

这样我们就可以很轻松地打出递归函数了：

```cpp
int h(int n){
	if(n==0) return 1;//边界1
	else if(n==1) return 2*x;//边界2
	else return 2*x*h(n-1)-2*(n-1)*h(n-2);//调用下一层递归
}
```
毕竟这是道红题，主函数也好打极了：

```cpp
int main(){
	int n;
	scanf("%d%d",&n,&x);
	printf("%d",h(n));//调用递归函数并输出
	return 0;
}
```
### 完整代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int x;//这里要把x定为全局变量
int h(int n){//递归函数
	if(n==0) return 1;
	else if(n==1) return 2*x;
	else return 2*x*h(n-1)-2*(n-1)*h(n-2);
}
int main(){
	int n;
	scanf("%d%d",&n,&x);
	printf("%d",h(n));
	return 0;//好习惯
}
```
---

这里也可以用递推，递推式的得来还是那张图。

### 递推代码：
```cpp
#include<bits/stdc++.h>
int h[10];
using namespace std;
int main(){
	int n,x;//这里x就可以不定为全局变量了
	scanf("%d%d",&n,&x);
	h[0]=1,h[1]=2*x;//初始化
	for(int i=2;i<=n;i++)
		h[i]=2*x*h[i-1]-2*(i-1)*h[i-2];//递推式
	printf("%d",h[n]);
	return 0;//好习惯
}
```


---

## 作者：Daidly (赞：5)

发现 Hermite 多项式在 $n>1$ 时需要递归，考虑递归函数求解。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x;
int h(int i,int j){
	if(i==0)return 1;
	else if(i==1)return 2*j;
	return 2*j*h(i-1,j)-2*(i-1)*h(i-2,j);
}
int main(){
	cin>>n>>x;
	cout<<h(n,x);
    return 0;
}
```
发现函数中并不需要 $j$ 作为变量，删去即可。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x;
int h(int i){
	if(i==0)return 1;
	else if(i==1)return 2*x;
	return 2*x*h(i-1)-2*(i-1)*h(i-2);
}
int main(){
	cin>>n>>x;
	cout<<h(n);
    return 0;
}
```

---

## 作者：墨忧 (赞：4)

## 思路
一道入门级别的递归题，根据题目给出的公式写出相应的递归函数求解即可
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int Hermite(int n,int x)//递归求解 
{
    if(n==0) return 1;
    if(n==1) return 2*x;
    else return 2*x*Hermite(n-1,x)-2*(n-1)*Hermite(n-2,x); 
}
int n,x;
int main()
{
    cin>>n>>x;
    cout<<Hermite(n,x);
    return 0;
} 
```


---

## 作者：__Cartesian__Tree__ (赞：3)

题目的意思就是编写一个递归函数，条件按照题目里的来。

首先，这个函数应该有两个形参。如果 $n = 0$，那么函数返回1，如果 $n = 1$，函数返回 $2 * x$，其余情况返回题目中的那个式子。

由于数据范围比较小，所以不会 TLE。

AC Code:
```cpp
#include <bits/stdc++.h>
using namespace std;
int h(int n, int x){//递归函数
    if (n == 0) return 1;
    if (n == 1) return 2 * x;//不用加 else
    return 2 * x * h(n - 1, x) - 2 * (n - 1) * h(n - 2, x); //按照题目的递归公式
}
int main(){
    int n, x;
    scanf("%d%d", &n, &x);
    printf("%d\n", h(n, x));
    return 0;
}
```


---

