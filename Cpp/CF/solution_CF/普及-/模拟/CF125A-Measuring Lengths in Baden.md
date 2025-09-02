# Measuring Lengths in Baden

## 题目描述

Lengths are measures in Baden in inches and feet. To a length from centimeters it is enough to know that an inch equals three centimeters in Baden and one foot contains 12 inches.

You are given a length equal to $ n $ centimeters. Your task is to convert it to feet and inches so that the number of feet was maximum. The result should be an integer rounded to the closest value containing an integral number of inches.

Note that when you round up, 1 cm rounds up to 0 inches and 2 cm round up to 1 inch.

## 样例 #1

### 输入

```
42
```

### 输出

```
1 2
```

## 样例 #2

### 输入

```
5
```

### 输出

```
0 2
```

# 题解

## 作者：Alex_Wei (赞：5)

先将读进来的厘米数 $+1$（起到四舍五入的效果），再 $/3$ 转化为英寸即可

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,c;//n是厘米，c是英尺
int main()
{
	cin>>n,c=(n+1)/3;
	cout<<c/12<<" "<<c%12;
	return 0; 
}
```

---

## 作者：封禁用户 (赞：3)

此题根据题意模拟即可。  
题目传送>>[CF125A](https://www.luogu.com.cn/problem/CF125A)  
### 题意简述：  
一英寸等于 $3$ 厘米，一英尺等于 $12$ 英寸，给一个长度为 $n$ 厘米的物品，将其长度转换为以英尺和英寸为单位且为整数，四舍五入时 $1$ 厘米舍入到 $0$ 英寸，$2$ 厘米舍入到 $1$ 英寸。  
### 题目分析：  
首先把厘米数除于 $3$ 转化为英寸数，但是需要注意四舍五入取近似值，得到英寸数后除于 $12$ 即可得到英尺数，对 $12$ 取模即可得到化英尺后剩余的英寸数。  
### 问题解决：  
主要涉及到四舍五入取近似值，我们可以自己手写一个函数来进行操作。  
cmath 库中有 floor( ), ceil( ) 两个函数 :  
- floor( )会取不大于自变量的最大整数，即 floor($1.1$) 和 floor($1.9$) 的结果都为 $1$，floor($-1.1$) 和 floor($-1.9$) 的结果都为 $-2$；  
- ceil( )会取不小于自变量的最小整数，即 ceil($1.1$) 和 ceil($1.9$) 的结果都为 $2$，ceil($-1.1$) 和 ceil($-1.9$) 的结果都为 $-1$。  
  
 因此我们可以利用其特性自己手写一个四舍五入取近似值函数如下：  
```cpp
int round_double(double number)
{
    return (number > 0.0) ? floor(number + 0.5) : ceil(number - 0.5);
}
```

### Code  ：  
```cpp
#include<iostream>
#include<cmath>   //floor()和ceil()均含于其库 
using namespace std;
int round_double(double number)   //定义函数四舍五入取近似值 
{
    return (number > 0.0) ? floor(number + 0.5) : ceil(number - 0.5);
}
int main()
{
	ios::sync_with_stdio(0);   //关同步流，加速cin输入和cout输出
	int n;   //定义厘米数 
	cin >> n;	    
	cout << round_double(n/3.0)/ 12 << " " << round_double(n/3.0) % 12;    //输出以英尺和英寸为单位的长度
	return 0;   //结束整个程序 
}
```
### 评测结果（未吸氧）：  
![JieGuo](https://cdn.luogu.com.cn/upload/image_hosting/tjeci6km.png)  
企鹅的题解到此结束，希望各位 OIers 进步 ++~

---

## 作者：Ybocean_s (赞：2)

题意：有一个长度为 $n$ 厘米的物品，任务是将厘米改成以英尺和英寸为单位的长度。

------------
思路：题目中给出一英寸等于三厘米，一英尺等于十二英寸，并且在计算过程中需要考虑四舍五入，为了简便，在数中加一，就可以起到文中要求的四舍五入效果。

先把所有厘米数都转化成英寸，然后优先考虑英尺，剩下的按照英寸输出。

代码：
```cpp
#include<iostream>
using namespace std;
int main()
{
	int n,a;//题中要求变量和计算待定变量。
	cin>>n;
	a=(n+1)/3;//如思路加一，然后求出英寸数。
	cout<<a/12<<" "<<a%12;//先考虑英尺剩下按照英寸输出。
	return 0;//结束。
}
```
撒花。

---

## 作者：CSP_Sept (赞：1)

# 前置知识
1. **编写函数**
2. **四舍五入的判断**

# $Solution:$
## 1. 编写函数
```cpp
函数返回值类型 函数名(参数类型1 参数名1,参数类型2 参数名2,...,参数类型n 参数名n){
   函数体
   return;//void类型,无返回值
   return x;//返回x
}
```
## 2. 四舍五入的实现
### 2.1 手写
先看几组式子$($ 以下用 $[x]$ 表示 $x$ 四舍五入后的结果 $)$ ：

**注：$\text{int}(n)$ 代表对 $n$ 向下取整。**

$\begin{cases}[2.4]=2\;,\;\text{int}(2.4+0.5)=2\\ [2.5]=3\;,\;\text{int}(2.5+2.5)=3\\ [2020]=2020\;,\;\text{int}(2020+0.5)=2020\\ [-2020.03]=-2020\;,\;\text{int}(-2020.03+0.5)=-2020\end{cases}$

可以看出对于任意一个 $x$，都有 $[x]=\text{int}(x+5)$ 。

于是可以轻松写出代码：
```cpp
int To_round(int n,int r){//对n/r四舍五入
    return int(n*1.0/r+0.5);//强制类型转换
}
```
### 2.2 C++11自带函数
在C++11中，`round` 函数支持四舍五入，函数原型：
```cpp
double round(double x)//返回x(double类型)四舍五入后的结果(结果也是double类型) 
```
但建议大家还是手写比较好，因为大多数竞赛**不支持** C++11，一些旧版本的编译器也**不支持**这个函数。
## 3.怎么写这道题
先转换成英寸 $(\text{inch})$，再转化成英尺 $(\text{foot})$，也就是说，把英寸当成一个转换的桥梁。

**注意：厘米$\to$英寸 要四舍五入，但 英寸$\to$英尺 不用四舍五入！**
# $Code:$
#### 完全按照 $Solution$ 而写
```cpp
#include <cstdio>
using namespace std;
int To_round(int n,int r){
	return int(n*1.0/r+0.5);
}
int main(){
	int inch,foot,n;
	scanf("%d",&n);
	inch=To_round(n,3);
	foot=inch/12;
	inch-=foot*12;
	printf("%d %d",foot,inch);
	return 0;
}
```
# $End$
题解编号 $20200303(2020$年 $3$ 月第 $3$ 篇题解$)$,总第 $14$ 篇。

---

## 作者：信守天下 (赞：0)

## 直接按题目要求模拟就可以了
关键点在四舍五入

先转换成英寸
~~~cpp
n / 3.0 
~~~
再利用floor进行四舍五入

~~~cpp
floor(n / 3.0 + 0.5)
~~~

这里分享一下，任何小数+0.5后向下取整就能达到四舍五入的效果

英尺就是除12的整数部分，剩下的就是英寸
~~~cpp
int(floor(n / 3.0 + 0.5)) / 12
~~~

英寸就可以用模12来获得，因为每一个12英寸都会变成英尺
~~~cpp
int(floor(n / 3.0 + 0.5)) % 12
~~~
我们为了代码通俗易懂，可以用一个变量存四舍五入的结果
# $code1$
 
~~~cpp
#include <iostream>
#include <cmath>
int m;
int main() {
  cin >> n;
  m = floor(n / 3.0 + 0.5);
  cout << m / 12 << " " << m % 12;
}
~~~
## 再提供一种很妙的写法
 因为所有数模1都会得0，所以可以这么写，不会RE
 
因为没有使用c++的特性和函数，所以可以不要
~~~cpp
using namespace std;
~~~
加上这行也没事，只是单纯压行

因为$floor$的返回值是个浮点数，而题目要求整数

所以要用$int$进行强制类型转换

上面的代码是因为$m$是$int$类型，在赋值时就转换了类型
# $code2$
~~~cpp
#include <cstdio>//c语言就可以改成stdio.h
#include <cmath>//同上，可改math.h
int n;
int main() {
  return (scanf("%d" , &n) , printf("%d %d" , int(floor(n / 3.0 + 0.5)) / 12 , int(floor(n / 3.0 + 0.5)) % 12 )) % 1;
}
~~~
 主函数只有一行

---

## 作者：Zhoumy (赞：0)

按照题意把要四舍五入得当一类，不要的当另一类，进行判断。
```
#include<bits/stdc++.h>
using namespace std;
long long n;
int main(){
	cin>>n;
	if(n%3==2)cout<<(n/3+1)/12<<" "<<(n/3+1)%12;
	else cout<<n/3/12<<" "<<n/3%12;
	return 0;
}
```

---

## 作者：Trollz (赞：0)

这道题真的不难，不知道怎么被评为普及-的。。

讲正题。它这个题意呢，就是把厘米数转成英尺与英寸，很容易就有了思路：先把厘米转换成英寸，再由英寸转换为英尺。我们就有了一个伪代码：
```cpp
#include <iostream>
#include <cmath>
using namespace std;
double cm;
int main(){
	int yingchi;
	cin>>cm;
	yingchi=/*convert*/(cm/3); 
	cout<<yingchi/12<<" "<<yingchi%12;
	return 0;
}  
```
注意打了注释的那里。如果那个地方直接替换成int，**肯定是不可行的**，因为，题意说了要**四舍五入**。也很容易办，我们写个四舍五入的函数就可以了。具体见代码：
```cpp
#include <iostream>
#include <cmath>
using namespace std;
double cm;
int convert(double a){
	if(cm/3-int(cm/3)>0.5){//取小数部分，大于0.5就向上取整
		return ceil(cm/3);
	}else{//否则向下取整
		return floor(cm/3);
	}
}
int main(){
	int yingchi;
	cin>>cm;
	yingchi=convert(cm/3);//一定要在计算英寸的这里就要四舍五入，不然结果会有误差！ 
	cout<<yingchi/12<<" "<<yingchi%12;
	return 0;
}  
```

---

## 作者：Eason_AC (赞：0)

## Content
在巴登，一英寸等于 $3$ 厘米，一英尺等于 $12$ 英寸。

现在有一个 $n$ 厘米的物体，求在巴登，它是几英尺又几英寸。

**数据范围：$1\leqslant n\leqslant 10000$。**
## Solution
现将厘米数换算成总共的英寸数（注意四舍五入），然后换算成几英尺又几英寸的形式就好。具体来说，英尺可以直接用总英寸数除以 $12$ 向下取整，余数即为剩下的英寸数。
## Code
```cpp
#include <cstdio>
#include <cmath>
using namespace std;

int n;

int main() {
	scanf("%d", &n);
	int inch = floor(n / 3.0 + 0.5);
	printf("%d %d", inch / 12, inch % 12);
}
```

---

## 作者：Dimly_dust (赞：0)

### 题意翻译
在巴登，一英寸等于 3 厘米，一英尺等于 12 英寸

你有一个物品，长度为 n 厘米。任务是将厘米改成以英尺和英寸为单位的长度。

结果是一个整数，如果是一个小数那么答案要四舍五入
请注意，取近似值时，1 厘米舍入到 0 英寸，2 厘米舍入到 1 英寸。

输入：一个非负整数 n

输出：两个整数，分别是保留整数部分的英尺数和英寸数，中间用空格隔开



------------
这是一道有关于长度的题目，规则是：先添加再判断。
1. 添加：
```cpp
	double s,n=0,m=0;
	cin>>s;
	
	m=(s*1.0/3)*10;
```
2. 判断：
```cpp
if(int(m)%10>=5)m+=10;//小数位是否大于五
```
3. 进位：
```cpp
	m=int(m)/10;
	n=int(m)%12;
	m=m/12;
```
4. 输出
```cpp
cout<<int(m)<<" "<<int(n);
```
好了，完工！

整体代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100001];
int main()
{
	double s,n=0,m=0;
	cin>>s;
	
	m=(s*1.0/3)*10;
	if(int(m)%10>=5)m+=10;
	m=int(m)/10;
	n=int(m)%12;
	m=m/12;
	cout<<int(m)<<" "<<int(n);
	return 0;
}

```


---

