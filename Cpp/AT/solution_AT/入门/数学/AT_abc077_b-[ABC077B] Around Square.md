# [ABC077B] Around Square

## 题目描述

请你求出不超过 $N$ 的所有平方数中最大的一个。这里，平方数指的是可以表示为某个整数的 $2$ 次方的整数。

## 说明/提示

## 限制条件

- $1 \leq N \leq 10^9$
- $N$ 是整数

## 样例解释 1

$10$ 不是平方数，而 $9 = 3 \times 3$ 是平方数，所以输出 $9$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
10```

### 输出

```
9```

## 样例 #2

### 输入

```
81```

### 输出

```
81```

## 样例 #3

### 输入

```
271828182```

### 输出

```
271821169```

# 题解

## 作者：agicy (赞：2)

# 题意

找到一个最大小于等于$N$的完全平方数

# 思路

经过数学分析可得，$ans=\left\lfloor\sqrt{n}\right\rfloor^2$。

# 代码

代码如下。

```cpp
#include<stdio.h>
#include<math.h>//头文件

double n;//用double防止精度损失

int main(void){
	scanf("%lf",&n);//读入
	printf("%.0lf\n",pow(floor(sqrt(n)),2.0));//输出，记得换行
	return 0;//结束
}
```

---

## 作者：mwhxiaopy (赞：1)

这里我写一个比较暴力的题解（全篇只有一个变量）

这道题我使用了int的向下取整特性，
通过sqrt函数来开方，此时原数会向下取整。

开方函数代码形如``` sqrt(a)```。

所以我的思路是：将输入的数开方后向下取整，然后再平方，最后得到小于它的最大平方数。

源代码：
```
#include<iostream>
using namespace std;
int main(){
    int a;
    cin>>a;
    a=sqrt(a);//开方+取整
    a*=a;//重新平方
    cout<<a;
}
```
求过！(^_^)

---

## 作者：CZQ_King (赞：1)

做法：从后面枚举循环，碰到的第一个完全平方数，就是最大的，这时，直接输出即可。


------------

```cpp
#include<bits/stdc++.h>//头文件
using namespace std;
int a;//要输入的数
double b;
int main(){
    cin>>a;//输入
    for(int i=a;i>=0;i--){
        b=sqrt(i);//把b设置成i的平方根
        if(int(sqrt(i))==b){//判断是否为完全平方数
            cout<<i<<endl;//是的话就输出
            return 0;//蓝后结束
        }
    }
    return 0;//这个好像没什么用
}
```

---

## 作者：ShineEternal (赞：1)

# 可以发现，如果n就是完全平方数：那么他的平方根一定是个整数。

同理，n以下的数如果是完全平方数，根一定也是整数。

可以先sqrt(1.0*n);注意这时要强制转化；

因为这个数不一定是整数，要把他归到最近的整数上

进一显然不行，会超过n，可得去尾floor(),



------------


```
#include<cstdio>
#include<cmath>//后面数学函数要用
using namespace std;
int main()
{
	int n;
	scanf("%d",&n);//没那么麻烦，int型读入足够。
	int x=floor(sqrt(1.0*n));//即分割线上所述的转化
	printf("%d\n",x*x);//别忘了x是平方根，还要平方
	return 0;
}
```

---

