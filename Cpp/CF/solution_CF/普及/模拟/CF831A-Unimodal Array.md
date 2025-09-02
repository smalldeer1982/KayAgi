# Unimodal Array

## 题目描述

一个整数数组是单峰的，如果：

一开始它是严格增加的；

之后是恒定不变的；

再后是严格减少的；

第一块（增加）和最后一块（减少）可能不存在。允许这两块都不存在。

例如，下面这三个数组是单峰的：

$[5,7,11,11,2,1] , [4,4,2] , [7]$ 

但是，下面这三个不是单峰的：

$[5,5,6,6,1] , [1,2,1,2] , [4,5,5,6]$ 

写一个程序来判断一个数组是否是单峰的。

## 说明/提示

第一个样例中的数组是单峰的，因为它是在开始的时候严格递增（从位置$1$ 到位置$2$ ，含端点），中间恒定不变（从位置$2$ 到位置$4$ ，含端点）并在最后严格递减（从位置$4$ 到位置$6$ ，含端点）。

by @Khassar

## 样例 #1

### 输入

```
6
1 5 5 5 4 2
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
5
10 20 30 20 10
```

### 输出

```
YES
```

## 样例 #3

### 输入

```
4
1 2 1 2
```

### 输出

```
NO
```

## 样例 #4

### 输入

```
7
3 3 3 3 3 3 3
```

### 输出

```
YES
```

# 题解

## 作者：Rainbow_qwq (赞：3)

[原题链接](https://www.luogu.org/problemnew/show/CF831A)

思路：
```cpp
找到中间恒定不变那段的左端和右端。
如样例#1：
1 5 5 5 4 2
此时左端为2，右端为4。
(2-4这段是不变的)
接下来，
从左端向左检查，从右端向右检查，
如果两段都是递减，就符合。
```
那怎么找左端呢？

数组中最左&最大的就是左端。

右端的话，从左端向右找就行了。

参考代码：
```cpp
inline int read(){//快读
	char c=getchar();int x=0,f=1;
	while(!isdigit(c)){if(c=='-')f=-f;c=getchar();}
	while(isdigit(c))x=(x<<1)+(x<<3)+(c^48),c=getchar();
	return f*x;
}
int n,lpos,rpos,a[110];
//lpos为左端，rpos为右端

int main()
{
    n=read();
    for(int i=1;i<=n;i++){
    	a[i]=read();
    	if(a[i]>a[lpos])lpos=i;//找最大值，就是左端
	}
	rpos=lpos;
	while(a[rpos+1]==a[lpos]&&rpos<=n)rpos++;//找右端
}
```
接下来是检查是否符合。
```cpp
	for(int i=lpos-1;i>=1;i--)//从左端向左检查
		if(a[i]>=a[i+1])return puts("NO")&0;//不符合递增，结束
	for(int i=rpos+1;i<=n;i++)//从右端向右检查
		if(a[i]>=a[i-1])return puts("NO")&0;//不符合递减，结束
    return puts("YES")&0;//符合
```
完整代码：
```cpp
//不要复制代码
#include<cstdio>
#include<cctype>
using namespace std;
inline int read(){
	char c=getchar();int x=0,f=1;
	while(!isdigit(c)){if(c=='-')f=-f;c=getchar();}
	while(isdigit(c))x=(x<<1)+(x<<3)+(c^48),c=getchar();
	return f*x;
}
int n,lpos,rpos,a[110];
int main()
{
    n=read();
    for(int i=1;i<=n;i++){
    	a[i]=read();
    	if(a[i]>a[lpos])lpos=i;
	}
	rpos=lpos;
	while(a[rpos+1]==a[lpos])rpos++;
	
	for(int i=lpos-1;i>=1;i--)
		if(a[i]>=a[i+1])return puts("NO")&0;
	for(int i=rpos+1;i<=n;i++)
		if(a[i]>=a[i-1])return puts("NO")&0;
    return puts("YES")&0;
}
```

---

## 作者：zhangyuhan (赞：2)

我来给大家介绍一下用一遍循环$AC$的写法（因为我看别的题解都是用三个循环过的）。

首先，定义两个$bool$变量$flag1$和$flag2$。其中$flag1$记录循环变量是否处于数列“峰顶”（就是数列相等的一段），如果是记为$true$，$flag2$记录循环变量是否处于数列“下坡”（就是数列减少的一段）。

接着令数列为$a$，再令$i$从$2$开始遍历，一直到$n$，期间做三个$if$判断：

$1.$如果$a[i]=a[i-1]$，则将$flag1=true$

$2.$如果$a[i]<a[i-1]$，则将$flag2=true$，但注意，此时已处于下坡，要记得$flag1=false$

$3.$如果**出现非法情况**，就输出$NO$，并$return$ $0$。

那么让我们来思考什么是非法情况，无碍乎就两种：

$1.$处于峰顶时出现减少增加或减少情况

$2.$处于下坡阶段时出现增加或相等情况

**为什么不判断上坡时出现违法情况？**

举个栗子：对于$[1,2,3,2,4,3,2]$这个数列来说，您可能一眼会看出在第$4$个数时出现了违法状况，看似是增加时出现了问题，其实我们用那两种判断法则来判断一下：

首先，在第四个位置的时候，$flag2=true$，而在第五个位置的时候，出现了增加情况，显然不符合判定法则$2$，也会输出$NO$。

因此我们得知：**只要前面的两种判定法则就可以判定所有的违法情况**

那我们来讨论前面的两种判定法则如何用代码实现：

对于第$1$种，对应的代码应该是

```cpp
flag1==true&&a[i]!=a[i-1]
```

对于第$2$种，对应的代码应该是

```cpp
flag2==true&&a[i]>=a[i-1]
```

所以，整道题的$AC$ $Code$就呼之欲出了：

```cpp
#include<iostream>
using namespace std;

int n,a[110];

bool flag1,flag2;

int main(){
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    for(int i=2;i<=n;i++){
        if(a[i]==a[i-1])
            flag1=true;
        if(a[i]<a[i-1]){
            flag2=true;
            flag1=false;
        }
        if((flag2==true&&a[i]>=a[i-1])||(flag1==true&&a[i]!=a[i-1])){
            cout<<"NO\n";
            return 0;
        }
    }
    cout<<"YES\n";
    return 0;//完结撒花！
}
```

---

## 作者：Iron_Heart (赞：1)

## 思路

模拟。

定义 `state` 为当前数组的状态。$1$ 表示递减，$0$ 表示不变，$-1$ 表示递增。

之后遍历数组，如果数组状态转变，则更新 `state`。

如果数组当前状态和 `state` 冲突（例如 $a_i == a_{i-1}$ 但 `state` 为 $1$），则数组不是单峰的，输出 `NO`。

如果没有冲突，则数组是单峰的，输出 `YES`。

## 代码

```cpp
#include <cstdio>
int n, a[105], state = -1;
bool flag = 1;

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
    }
    for (int i = 1; i < n; ++i) {
        if (a[i] == a[i - 1]) {
            if (state == -1) {
                state = 0;
            } else if (state == 1) {
                flag = 0;
                break;
            }
        } else if (a[i] < a[i - 1]) {
            if (state == 0 || state == -1) {
                state = 1;
            }
        } else if (a[i] > a[i - 1]) {
            if (state == 0 || state == 1) {
                flag = 0;
                break;
            }
        }
    }
    if (flag) {
        puts("YES");
    } else {
        puts("NO");
    }
    return 0;
}
```


---

## 作者：李至擎 (赞：0)

[点我看题](https://www.luogu.com.cn/problem/CF831A)

思路：显然是模拟题，没什么好说的。

方法：

- $1.$ 输入时储存前后大小关系（后面比前面小为负数，相等为 $0$ ，后面比前面大为正数）；

- $2.$ 从 $2$ （注意 $!$ ）到 $n$ 循环判断是否合法，如不合法，输出 $NO$ ，结束程序；

- $3.$ 如果一直是合法的，输出 $YES$ 。

细节：
- 第二步是"从 $2$ 到 $n$ 循环判断"，而不是"从 $1$ 到 $n$ 循环判断"。因为 $a[0]$ 初始为 $0$ ，而 $a[1]$ 一定是大于它的，而后面又会小于它，会出错，所以不能这么写。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[105],c[105];//n、a如题意，c为前后之差（用于判断）
int main()
{
	cin>>n;//输入
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		c[i]=a[i]-a[i-1];//计算前后之差
	}
	for(int i=2;i<=n;i++)//这里是从2到n循环 
	{
		if(c[i]>0)//后面比前面大 
		{
			if(c[i-1]<0||c[i-1]==0)//如果前面是相等或下降 
			{
				cout<<"NO";//不可能 
				return 0;//结束程序 
			}
		}
		else if(c[i]==0)//后面与前面相等 
		{
			if(c[i-1]<0)//如果前面是下降  
			{
				cout<<"NO";//不可能
				return 0;//结束程序 
			}
		}
	}	
	cout<<"YES";//一直是合法的 
	return 0;//结束程序 
}
//6
//1 5 5 5 4 2

//5
//10 20 30 20 10

//4
//1 2 1 2
```

---

## 作者：封禁用户 (赞：0)

这一题的思路是：首先输入，在相等或下降时break；在下降时break；再检查之后是否一直下降
代码如下↓↓↓
```
#include <bits/stdc++.h>
using namespace std;
int j,number[1000],n;
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    cin>>number[i];
    j=n;
    for(int i=1;i<n;i++)
    {
        if(number[i]>=number[i+1])//这两个数字成下降趋势 ||相等 
        {
            j=i;
            break;
        }
    }
    for(int i=j;i<=n;i++)
    {
        if(number[i]!=number[i+1])
        {
            j=i;
            break;
        }
    } 
    for(int i=j;i<=n;i++)//从第j个数开始应该保持下降
    {
        if(number[i]<=number[i+1])
        {
            cout<<"NO";
            return 0;
        }
    } 
    cout<<"YES";
    return 0;
}
```

---

