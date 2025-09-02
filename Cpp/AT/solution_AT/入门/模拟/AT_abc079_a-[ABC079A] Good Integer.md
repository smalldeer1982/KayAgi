# [ABC079A] Good Integer

## 题目描述

像 $1118$ 这样，$4$ 位整数中有 $3$ 个或以上相同的数字连续排列的数，被称为**好整数**。

给定一个 $4$ 位整数 $N$，请判断 $N$ 是否为**好整数**。

## 说明/提示

## 限制条件

- $1000 \leq N \leq 9999$
- 输入为整数

## 样例解释 1

因为 $1$ 连续出现了 $3$ 次，所以是**好整数**。

## 样例解释 2

所有数字都相同的情况也属于**好整数**。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
1118```

### 输出

```
Yes```

## 样例 #2

### 输入

```
7777```

### 输出

```
Yes```

## 样例 #3

### 输入

```
1234```

### 输出

```
No```

# 题解

## 作者：Warriors_Cat (赞：1)

## 题解 AT3674 【[ABC079A] Good Integer】

~~为什么题解区里面都是用字符串的啊……难道用整数不好吗……~~

首先，输入一个四位数 $n$ 后，我们将它一位一位拆解，最后判断有没有相邻三个数相同就可以了QWQ。

这道题较为简单，所以就直接放代码吧QAQ。

### $Code:$

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>//四大常用头文件
using namespace std;
int n, a, b, c, d;
int main(){
	scanf("%d", &n);
	a = n / 1000;
	b = n / 100 % 10;
	c = n / 10 % 10;
	d = n % 10;//一位一位拆解
	if((a == b && b == c) || (b == c && c == d)) puts("Yes");//因为 AT 的题要换行，所以用 puts
	else puts("No");
	return 0;//完结撒花-v-
} 
```
## End

---

## 作者：不到前10不改名 (赞：1)

at水题一道（不知数据为何只有四位数，我差点想成几千位的那种）
```
#include<stdio.h>
int main()
{
    int n[5],i;
    for(i=1;i<=4;i++)
    scanf("%1d",&n[i]);//%1d就是为了输入方便（害得我用while浪费了一次~）
    if(n[1]==n[2]&&n[2]==n[3])
    {printf("Yes\n");
    return 0;}//只有这两种情况，1=2=3,2=3=4；
    if(n[2]==n[3]&&n[3]==n[4])
    {printf("Yes\n");
    return 0;}
    printf("No\n");//都不是就输出No（记住大写）
    return 0;
}
```
//纯粹是C语言，没有什么好解释的了

---

## 作者：mwhxiaopy (赞：0)

# 这道题是一道打表题

不知为何没有使用模的

所以本蒟蒻使用模来解决

正文：

Good数字分三类

i:$xxxx$(此时模$1111=0$)

ii:$xxxy$（此时模$1110$时小于$10$）

iii:$yxxx$(此时模$1000$再模$111$时$=0$)

这三种都是Good数字，输出$Yes$;剩下的都不是,输出$No$。

所以只要打表就行了。

代码：

```
#include<iostream>
using namespace std;
int main(){
int a,b,c;
cin>>a;
b=a%1000;
c=a%1110;
if(a%1111==0)cout<<"Yes";
else if(b%111==0||c<=9)cout<<"Yes";
else cout<<"No";
}
```
希望大佬们多多提出意见。

---

## 作者：RioBlu (赞：0)

判断一个4位数是否连续3位以上都一样的话只要判断：

### 第1位是否和第2，3位相同

### 第2位是否和第3，4位相同

#### 其中一个或以上成立输出"Yes" 否则输出"No"


```
#include<bits/stdc++.h>
using namespace std;
string n;
int u[20];
int main()
{
	cin>>n;
    for(int s=2;s<n.size();s++)
    {
    	if(n[s]==n[s-1]&&n[s]==n[s-2])
    	{
    		cout<<"Yes"<<endl;
    		return 0;
		}
	}
	cout<<"No"<<endl;
	return 0;
}
```

---

