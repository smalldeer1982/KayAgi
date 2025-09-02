# Moore's Law

## 题目描述

根据摩尔定律，集成电路上可以容纳的晶体管数目每秒可变为原来的 $1.000000011$ 倍，现给定当前晶体管数目 $n$，和经历的秒数 $t$，求 $t$ 秒后集成电路上可以容纳的晶体管数目约是多少。

## 说明/提示

$10^3 \le n \le 10^4$，$0 \le t \le 2 \times 10^9$。

## 样例 #1

### 输入

```
1000 1000000
```

### 输出

```
1011.060722383550382782399454922040
```

# 题解

## 作者：Otue (赞：3)

**不开O2不卡常！！快速幂不用轻松AC!!**

我只是想说，这道题的数据范围不用快速幂，其实有一个函数叫 `pow`，他专门处理幂

比如有个式子叫 $a^b$，那么它可以写成 `pow(a,b)`。

比如有个式子叫 $(a+1)^{(b^2)}$,那么它可以写成 `pow(a+1,pow(b,2))`。
```cpp
#include<bits/stdc++.h>
using namespace std;
double a,b;
int main(){
	cin>>a>>b;
	printf("%.6lf",pow(1.000000011,b)*a);
} 
```
这个代码极限数据秒出，比如输入 $a$ 为 $10000$，$b$ 为 $2000000000$。

由此可见，简单的题用简单的方法，快速幂其实没必要用。

---

## 作者：爬行者小郑 (赞：1)

## 这题其实很水

我乍一看，咦？这不就是快速幂吗？还不用取模。

### 快速幂是什么？
平时，如果我们用pow函数来进行幂运算，是非常慢的，大概是O(n)的效率，其实幂运算完全可以稳定在O(logn)完成，它的原理是这样的：

设原数为n,乘方为k,若k为偶数,那么 $n^k=({n*n})^{k/2}$,奇数的话就再乘上一个n就行了。对于$(n*n)^{k/2}$也可以通过递归来实现这个操作，从而在logn的时间内解决问题。

想更细致地了解快速幂的同学，请跳转[P1226 【模板】快速幂||取余运算](https://www.luogu.com.cn/problem/P1226)

好了上代码
```cpp
#include<iostream>//基本输入输出流（CF的评测机好像printf不用单开cstdio......但是竞赛中最好加上）
using namespace std;
double b;//原有体积，最后乘上就行
int p;//次方数
double pow(double x,int n)
{
	if(n==0)return 1;//x的零次方要返回一个1
	if(n==1)return x;//x的一次方就返回一个0
	if(n%2==0)return pow(x*x,n>>1);//偶数分成两个来运算
	if(n%2==1)return pow(x*x,n>>1)*x;//奇数不要忘记乘上一个多出来的x
    
}
int main()
{
    cin>>b>>p;//输入两个数据
    printf("%.6lf\n",pow(1.000000011,p)*b);//原有体积直接乘上就行
	return 0;//养成好习惯
}

```
谢谢大家

---

## 作者：WinterRain208 (赞：1)

CF630B Moore's Law

题意：

给你一个数，把他乘上1.000000011若干次，求乘完的数。

这题数据比较大，所以循环是不行的，我们考虑把快速幂加到浮点数上去。

因为指数还是整数，所以快速幂的思想还是正确的，只要在板子上把所有整型改成浮点数即可。

保留六位小数的话也很简单，直接printf就行了。

代码：

```cpp
#include<bits/stdc++.h>
using namespace  std;
double db;
int n;
double qpow(double x,int n){
	if(n==0||n==1)return (n==1?x:1);
	return (n%2?pow(x*x,n>>1)*x:pow(x*x,n>>1));
}
int main(){
	cin>>db>>n;
	printf("%.9lf",pow(1.000000011,n)*db);
	return 0;
} 
```


---

## 作者：封禁用户 (赞：0)

一道[摩尔定律](https://baike.baidu.com/item/%E6%91%A9%E5%B0%94%E5%AE%9A%E5%BE%8B/350634?fr=kg_general)题，使用快速幂直接计算出结果。  
题目传送>>[CF630B](https://www.luogu.com.cn/problem/CF630B)  
### 题意简述：  
- 初始集成电路晶体管数量为 $n$，每时刻增加 $1.000000011$ 倍，求 $t$ 时刻后集成电路晶体管数量。  
- $10^3 \le n \le 10^4$，$0 \le t \le 2×10^9$，答案相对误差不应超过 $10^{-6}$。  
  
### 题目分析：  
初始为 $n$，每时刻增加 $1.000000011$ 倍，那么经 $t$ 时刻后自然就为 $n×1.000000011^t$，关键是注意题目数据，用上快速幂（`double` 型），且最终结果按一定小数位数输出即可。  
### Code：  
```cpp
#include <iostream>
#include <iomanip>
using namespace std;
double binaryPow(double a, int b)   //快速幂(a为底数，b为指数)
{
	double ans = 1;
	while (b > 0)
	{
		if (b & 1)
		{
			ans = ans * a;
		}
		a = a * a;
		b >>= 1;
	}
	return ans;
}
int main()
{
	ios::sync_with_stdio(0);   //关同步流，加速cin输入和cout输出
	cin.tie(0), cout.tie(0);   //解除cin与cout的绑定，进一步加快执行效率。
	int n, t;   //定义初始数量，时间
	cin >> n >> t;
	cout << fixed << setprecision(7) << n * binaryPow(1.000000011, t);   //以七位小数输出经时间t后的数量
	return 0;   //结束整个程序
}
```
### 结果（未吸氧）:  
![JieGuo](https://cdn.luogu.com.cn/upload/image_hosting/m2ka7ggf.png)  
企鹅的题解到此结束，祝各位 OIers 进步 ++~

---

