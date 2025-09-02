# Restoring Three Numbers

## 题目描述

Polycarp has guessed three positive integers $ a $ , $ b $ and $ c $ . He keeps these numbers in secret, but he writes down four numbers on a board in arbitrary order — their pairwise sums (three numbers) and sum of all three numbers (one number). So, there are four numbers on a board in random order: $ a+b $ , $ a+c $ , $ b+c $ and $ a+b+c $ .

You have to guess three numbers $ a $ , $ b $ and $ c $ using given numbers. Print three guessed integers in any order.

Pay attention that some given numbers $ a $ , $ b $ and $ c $ can be equal (it is also possible that $ a=b=c $ ).

## 样例 #1

### 输入

```
3 6 5 4
```

### 输出

```
2 1 3
```

## 样例 #2

### 输入

```
40 40 40 60
```

### 输出

```
20 20 20
```

## 样例 #3

### 输入

```
201 101 101 200
```

### 输出

```
1 100 100
```

# 题解

## 作者：inoichi_lim (赞：2)

这题显然需要先排序，所以先用一个数组储存好。

排完序，我们分析，$x_1=a+b,x_4=a+b+c,x_4-x_1=a+b+c-(a+b)=a+b+c-a-b=(a-a)+(b-b)+c=c$。

其他数同理，就可以得到$a=x_4-x_3,b=x_4-x_2,c-x_4-x_1$了。

----
代码：
```cpp
#include<bits/stdc++.h>
#define ns "-1"
#define fs(i,x,y,z) for(ll i=x;i<=y;i+=z)
#define ft(i,x,y,z) for(ll i=x;i>=y;i+=z)
#define ll long long
using namespace std;
const int N=100001,inf=0x7f7f7f7f;
ll a[5];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>a[1]>>a[2]>>a[3]>>a[4];
	sort(a+1,a+5);
	cout<<a[4]-a[1]<<' '<<a[4]-a[2]<<' '<<a[4]-a[3];//有SPJ，所以乱写也可以AC
	return 0;
}

```

---

## 作者：xsI666 (赞：1)

## 这是一道数论题。
 
我们先整理一下题面告诉我们的信息：

1. $a$、$b$、$c$是三个正整数；

2. 我们会输入4个**乱序**的数字：$x1$、$x2$、$x3$、$x4$；

3.  $x1$ = $a$ + $b$ , $x2$ = $a$ + $c$ , $x3$ = $b$ + $c$ , $x4$ = $a$ + $b$ + $c$。

∵$a$、$b$、$c$均＞$0$.

∴$x4$是这四个数中最大的数。

至于如何求出$a$、$b$、$c$，则可以：

用$x4-x1$得到$c$，用$x4-x2$得到$b$，用$x4-x3$得到$a$，最后按顺序输出这三个数即可。

注意：我们需要开一个数组$x$[]来存储$x1$、$x2$、$x3$、$x4$，因为这样便于我们排序（可以直接调用$c++$库函数$sort$，但要开头文件$algorithm$），而且可以更好地帮助我们寻找到$a$、$b$、$c$。

最终代码：
```cpp
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>//头文件准备

using namespace std;//使用标准名字空间

inline int gi()//快速读入，不解释
{
    int f = 1, x = 0;
    char c = getchar();
    while (c < '0' || c > '9')
    {
        if (c == '-')
            f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9')
    {
        x = x * 10 + c - '0';
        c = getchar();
    }
    return f * x;
}

int a, b, c, x[5];//a、b、c和x数组的意义同分析

inline void init()//分别输入这四个数
{
	x[1] = gi(), x[2] = gi(), x[3] = gi(), x[4] = gi();
}

inline void solve()//将x数组从小到大排序
{
	sort(x + 1, x + 1 + 4);//1和4是指从x[1]到x[4]从小到大排序
}

inline void output()//输出的自函数
{
	printf("%d %d %d\n", x[4] - x[1], x[4] - x[2], x[4] - x[3]);//分别输出a、b、c。
}

int main()//进入干净整洁的主函数
{
	init();//输入
	solve();//排序解决问题
	output();//输出
	return 0;//养成return 0的好习惯
}
```

---

## 作者：ygl666666 (赞：0)

## 题意分析 && 思路
题目说有4个数,x1,x2,x3,x4。分别是a+b,a+c,b+c,a+b+c。其中x4是最大的，所以他一定就是a+b+c了。因为我看样例里面除了x4是最大的外，其他的数都是按输入顺序的，所以我就先找出了最大值，他就是x4，然后再把四个值分别赋值给x1,x2,x3,x4。最后计算a,b,c时。a就等于**a+b+c-(b+c)**，也就是x4-x3；同理b为x4-x2；c就为x4-x1了。所以代码就呼之欲出了。
## Code
```
/**/
#include<bits/stdc++.h>
using namespace std;
int a,b,c,e,f,g,h,x1,x2,x3,x4,maxx;
int main(){
	ios::sync_with_stdio(false);
	cin>>e>>f>>g>>h;//输入开始4个数
	maxx=max(e,max(f,max(g,h)));//找最大值
    	//四个判断分别赋值
	if(maxx==e){
		x4=e,x1=f,x2=g,x3=h; 
	}else if(maxx==f){
		x4=f,x1=e,x2=g,x3=h;
	}else if(maxx==g){
		x4=g,x1=e,x2=f,x3=h;
	}else if(maxx==h){
		x4=h,x1=e,x2=f,x3=g;
	}
	a=x4-x3,b=x4-x2,c=x4-x1;//计算
	cout<<a<<" "<<b<<" "<<c<<endl;//输出
	return 0;//结束
}

```
## The end！


---

## 作者：Eason_AC (赞：0)

## Content
已知有三个正整数 $a,b,c$，现在给出 $a+b,a+c,b+c,a+b+c$（不保证有序）的值，试求出 $a,b,c$。

**数据范围：$2\leqslant a+b,a+c,b+c,a+b+c\leqslant 10^9$。**
## Solution
肯定地，如果是无序的话，那么我们肯定要先对这四个值排序，得到：

$$\begin{cases}x_1=a+b\\x_2=a+c\\x_3=b+c\\x_4=a+b+c\end{cases}$$

那么，运用加减消元，我们就可以得到：

$$\begin{cases}a=x_4-x_3\\b=x_4-x_2\\c=x_4-x_1\end{cases}$$

直接输出这三个值就好了。
## Code
```cpp
int x[7];

int main() {
	_for(i, 1, 4)	getint(x[i]);
	sort(x + 1, x + 5);
	int a = x[4] - x[1], b = x[4] - x[2], c = x[4] - x[3];
	writeint(a), putchar(' '), writeint(b), putchar(' '), writeint(c);
	return 0;
}
```

---

## 作者：FP·荷兰猪 (赞：0)

> 题意：有三个正整数a,b,c,现在给定x1=a+b,x2=a+c,x3=b +c,x4=a+b+c。请求出a,b,c分别是多少。

> 解法：分析公式，易得a=x4-x3,b=x4-x2,c=x4-x1。由于输入是无序的，只要找到x4然后分别输出x4与x3、x2、x1的差即可。由于输入的数均大于0，所以x4就是这四个数中最大的一个。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
	int a[5],i;//这里把x1~x4用数组输入了，方便找最大数
	for (i=1;i<=4;i++)
	{
		cin>>a[i];
	}
	sort(a+1,a+5);//这里直接用sort找最大值了
	int cnt;
	cnt=a[4];
	cout<<cnt-a[1]<<" "<<cnt-a[2]<<" "<<cnt-a[3]<<endl;//分别输出差
	return 0;
}
```

---

## 作者：codemap (赞：0)

这道题其实不需要一大堆判断

只需要用数组排个序就可以了。。。

输出的就是第四个分别减前三个

~~是不是很简单~~

直接上代码
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int main()
{	
    int a[5];
    cin>>a[1]>>a[2]>>a[3]>>a[4];
    sort(a+1,a+5);//排序
    cout<<a[4]-a[1]<<" "<<a[4]-a[2]<<" "<<a[4]-a[3];//输出
    return 0;//完美结束
}
```

---

## 作者：米奇奇米 (赞：0)

## 很简单的一题思维题，就告诉你几个约束条件，求出任意一组解就可以了
### 首先我们来看一下几个约束条件：
### $ x1=a+b $ 
### $ x2=a+c $
### $ x3=b+c $
### $ x4=a+b+c $
### 观察一下这些柿子，发现$  x4=a+b+c  $一定是最大的，所以要求$c$只要$x4-x1$就可以了，很简单！最后在将解出来的$c$代入上柿，就可以得出$a,b$的解了。代码也很短只有13行。
```cpp
#include<bits/stdc++.h>
using namespace std;
int X[5],A,B,C;
int main()
{
	cin>>X[1]>>X[2]>>X[3]>>X[4];
	sort(X+1,X+4+1);//排个序
	C=X[4]-X[1];
	B=X[3]-C;
	A=X[2]-C;
	cout<<A<<" "<<B<<" "<<C<<endl;//按照上面说着做就可以了
	return 0;
}
```


---

## 作者：一扶苏一 (赞：0)

[本场题解博客](https://www.cnblogs.com/yifusuyi/p/10727303.html)

# A

## Description

有三个**正**整数 $a,~b,~c$，现在给定 $x_1~=~a + b,~x_2~=~a + c, x_3~=~b + c, ~x_4~=~a + b + c$，请求出 $a,~b,~c$ 分别是多少。输入数据是乱序的。

## Limitation

$\forall~i~\in~[1,~4],~2~\leq~x_i~\leq~10^9$。

数据保证有解。

## Solution

考虑由于 $x_1~=~a + b,~x_4~=~a + b + c$，所以 $c = a + b + c - (a + b) = x_4 - x_1$

类似的可以得到 $a,~b$ 都可以由三个数字的和减去另外两个数字得到。

考虑由于 $a,~b,~c$ 都是正整数，所以四个数字中最大的显然是三个数字的和，用这个数分别减去前三个数字就是答案了。

## Code

```cpp
ll a[4];

int main() {
  freopen("1.in", "r", stdin);
  for (auto &i : a) qr(i);
  std::sort(a, a + 4);
  qw(a[3] - a[0], ' ', true); qw(a[3] - a[1], ' ' , true); qw(a[3] - a[2], '\n', true);
  return 0;
}
```

---

## 作者：xh39 (赞：0)

a,b,c的顺序其实无所谓

如果a+b=x1,a+c=x2,b+c=x3;

```cpp
b=x1-a,c=x2-a; //把第一个和第二个同时减去a得到。
x1-a+x2-a=x3//代入第三个得到。
x1+x2-2a=x3;
x1+x2-x3=2a;
a=(x1+x2-x3)÷2;
```
最后要注意的是,最大的那个一定是三个数的和。
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int a,b,c,d,x1,x2,x3;
    cin>>a>>b>>c>>d;
    if(a>b&&a>c&&a>d){
        x1=b;
        x2=c;
        x3=d;
    }
    if(b>a&&b>c&&b>d){
        x1=a;
        x2=c;
        x3=d;
    }
    if(c>a&&c>b&&c>d){
        x1=a;
        x2=b;
        x3=d;
    }
    if(d>a&&d>b&&d>c){
        x1=a;
        x2=b;
        x3=c;
    }
    a=(x1+x2-x3)/2;
    b=x1-a;
    c=x2-a;
    cout<<a<<" "<<b<<" "<<c;
    return 0;
}
```

---

