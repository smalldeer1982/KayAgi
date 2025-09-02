# Perfect Permutation

## 题目描述

现有一个$1$~$n$的排列$p_1,p_2,...,p_n$。

$Nickolas$喜欢排列，他认为有一种排列是完美的。用$p_i$表示排列中的第$i$个元素，则完美的排列符合如下性质：

1. $p_{p_i}=i$

2. $p_i≠i$

现在给出$n$的值，请求出这个完美的排列。


现有一个$1$~$n$的排列$p_1,p_2,...,p_n$。

$Nickolas$喜欢排列，他认为有一种排列是完美的。用$p_i$表示排列中的第$i$个元素，则完美的排列符合如下性质：

1. $p_{p_i}=i$

2. $p_i≠i$

现在给出$n$的值，请求出这个完美的排列。

## 样例 #1

### 输入

```
1
```

### 输出

```
-1
```

## 样例 #2

### 输入

```
2
```

### 输出

```
2 1 
```

## 样例 #3

### 输入

```
4
```

### 输出

```
2 1 4 3 
```

# 题解

## 作者：Mars_Dingdang (赞：4)

这道题是一道典型的奇偶分析加构造的题目。只要分析出构造的方法就迎刃而解了。
## 题目大意

现有一个 $1\sim n$ 的排列 $p_1,p_2,\ldots,p_n$。

$\text{Nickolas}$ 喜欢排列，他认为有一种排列是完美的。用 $p_i$ 表示排列中的第 $i$ 个元素，则完美的排列符合如下性质：
1. $p_{p_i}=i$   
2. $p_i≠i$

现在给出 $n$ 的值，请求出这个完美的排列。如果排列不存在，输出 $-1$。
## 大体思路
这道题是一道构造的题目，首先来分析 $n=1$ 的情况：显然此时 $i=1$，因此满足 $p_{p_i}=i$，则 $p_1=1$，矛盾。

接下来看 $n=2$ 的情况：此时 $i∈[1,2]$，由题意得 $p_1≠1$，$p_2≠2$，且 $p_{p_2}=2$，$p_{p_1}=1$。因此 $p_{p_2}=p_1$，$p_{p_1}=p_2$。也就是说，$p_2=1,p_1=2$。

由此可以推导到全部的情况：$∀i,j∈[1,n]$，满足 $p_i=j, p_j=i$，此时 $p_{p_i}=p_j≠i,p_{p_j}=p_i≠j$，当且仅当 $i≠j$ 成立。因此要使每一组 $i,j$ 都不相等，条件为 $n$ 是偶数，即$n≡0\pmod 2$。

构造方法为：

1. 令 $i=1,j=n$，也就是说 $p_1=n,p_n=1$，然后 $i+1,j-1$，这样构造出来的就是 $1\sim n$ 的倒序排列。

2. 令 $i=1,j=2$，$p_1=2,p_2=1$，然后 $i+2,j+2$，相当于每次交换$1\sim n$的有序排列中的元素 $(p_1,p_2),(p_3,p_4)\ldots (p_n-1,p_n)$，构造出形如 $2,1,4,3\dots (n-2),(n-3),n,(n-1)$ 的数列。

## 完整代码
第一种构造法的代码：
```cpp
#include<bits/stdc++.h>//头文件
using namespace std;
int main(){
   int n;
	cin>>n;//输入
	if(n%2==1)//一切的先决条件为n为偶数，
    //因此n为奇数直接输出-1
		cout<<-1;
	else{
      for(int i=n;i>=1;i--) 
         cout<<i<<" ";//倒序输出1~n
    }
	return 0;//完美
}
```

第二种构造法：
```cpp
#include<bits/stdc++.h>//头文件
using namespace std;
int main(){
   int n;
	cin>>n;//输入
	if(n%2==1)
		cout<<-1;//同上
        //n为奇数直接输出-1
	else{
      for(int i=1;i<=n;i+=2) //注意每次+2
          cout<<i+1<<" "<<i<<" ";
          //相当于交换相邻两数并输出。
    }
	return 0;//完美
}
```


---

## 作者：BurningEnderDragon (赞：2)

[题目链接：CF233A Perfect Permutation](https://www.luogu.com.cn/problem/CF233A)

## 题意

你需要求出一个 $1 \sim n$ 的排列 $p_1,p_2,\ldots,p_n$，使得其满足以下两个性质：

1. $p_{p_i}=i$
2. $p_i \not= i$

## 思路

首先，若要使 $p_{p_i}$ 存在，**则 $p_i$ 必须是 $1$ 到 $n$ 之间的整数**，即 $\forall i \in \left[ 1,n \right]$，有 $p_i \in \left[ 1,n \right]$。

设 $p_i=x$，则上述的第一条性质可以转化为：$p_x=i$。

而第二条性质限制了 $p_i \not= i$，显然，只要排列中的**元素及其下标两两对应**，这个排列即满足两条性质。

而为了做到两两对应，**排列的元素个数 $n$ 必须为偶数**。

可以发现，当 $n$ 为偶数时，满足要求的排列有很多种，以下给出两种简单且可行的解法。

## 解法 1

第一种解法为：**相邻的两个元素两两对应**。

即对于每个奇数 $i$，$p_i=i+1$；对于每个偶数 $i$，$p_i=i-1$。

例如当 $n=4$ 时，排列为：$2,1,4,3$；

当 $n=10$ 时，排列为：$2,1,4,3,6,5,8,7,10,9$。

**解法 1 的主函数代码如下：**

```cpp
int n;
cin>>n;
if(n&1)  //当 n 为奇数时，无解 
{
    cout<<-1<<endl;
}
else  //当 n 为偶数时，使相邻的两个元素及其下标两两对应 
{
    for(int i=1;i<=n;i+=2)
    {
        cout<<i+1<<" "<<i<<" ";
    }
    cout<<endl;
}
return 0;
```

## 解法 2

第二种解法为：**排列为 $1 \sim n$ 的倒序**。

即 $\forall i \in \left[ 1,n \right]$，$p_i=n-i+1$。

例如当 $n=4$ 时，排列为：$4,3,2,1$；

当 $n=10$ 时，排列为：$10,9,8,7,6,5,4,3,2,1$。

**解法 2 的主函数代码如下：**

```cpp
int n;
cin>>n;
if(n&1)  //当 n 为奇数时，无解 
{
    cout<<-1<<endl;
}
else  //当 n 为偶数时，倒序输出 1 ~ n 
{
    for(int i=n;i>=1;--i)
    {
    	cout<<i<<" ";
	}
    cout<<endl;
}
```

---

## 作者：agicy (赞：2)

# 题意

## 题目描述

现有一个$1$ ~ $n$的排列$p_1,p_2,...,p_n$。

$Nickolas$喜欢排列，他认为有一种排列是完美的。用$p_i$表示排列中的第$i$个元素，则完美的排列符合如下性质：

1. $p_{p_i}=i$

2. $p_i≠i$

现在给出$n$的值，请求出这个完美的排列。

## 输入输出格式

### 输入格式：

仅一行，一个整数$n(1≤n≤100)$。

### 输出格式：

如果排列不存在，输出$-1$，否则输出完美排列，数字之间用空格隔开。

---

# 思路

先设排列中有只两个数$p_1,p_2$，则根据题意可得，

$p_{p_1}=1,p_{p_2}=2$

若出现另外两个数$p_i,p_{i+1}$，我们只需要让它们两个符合$p_{p_i}=i,p_{p_j}=j$即可。

又因为$p_i≠i,p_j≠j$。

所以$p_i=j,p_j=i$。

观察上面的式子，我们发现，上面好像是**一组对称式**。

所以，当$n$为偶数时，我们只要让$p_1=n,p_2=n-1,...,p_{n-1}=2,p_n=1$即可，答案为$n$~$1$。

至于$n$为奇数的情况，因为排列中每两个元素都互成一对，所以排列的长度不可能为奇数，无解，输出$-1$。

# 代码

代码如下。

```cpp
#include<stdio.h>//头文件

int n;

int main(void){
	scanf("%d",&n);//读入
	if(n&1)//如果n为奇数，无解
		puts("-1");
	else
		while(n)
			printf("%d ",n--);//倒序输出n~1
	return 0;//结束
}
```

## [我的测评记录](https://www.luogu.org/record/show?rid=9235669)

---

## 作者：fls233666 (赞：1)

考虑题目给的两个限制条件：

- $p_i \ne i$
- $p_{p_i} = i$

我们设 $p_i=j$ 则有

- $p_i = j$
- $p_{p_i} = p_j = i$

于是我们发现，题目中的限制是成对的！

那么首先得出无解的条件： **$n$ 为奇数时，必有一个位置存在 $p_i= i$ ，所以无解。**

其次，在 $n$ 为偶数时，对任意两个位置两两配对构造即可。

一种简单的构造思路是：把上式中的 $j$ 换为 $i+1$ 然后直接对于连续的两个位置构造。可以发现，样例就采用了此构造方法。

按照上述思路，得到如下代码：

```cpp
#include<iostream>
#include<cstdio>
#define ll long long
#define rgt register int
using namespace std;

const int mxn = 111;

int num[mxn];

int main(){
	int n;
	scanf("%d",&n);
    
	if(n%2){   //n为奇数，无解
		printf("-1");
		return 0;
	}
    //否则开始构造
	for(rgt i=1;i<=n;i+=2)
		num[i]=i+1,num[i+1]=i;
        
	for(rgt i=1;i<=n;i++)   //输出构造结果
		printf("%d ",num[i]);
	return 0;
}

```


---

## 作者：_Clown_ (赞：1)

# 概述
|题号|难度|$AC$时间及记录|
| :----: | :----: | :----: |
|$\texttt{CF233A}$|$\texttt{CF难度:800}$|[$\texttt{On 2020/12/18}$](https://www.luogu.com.cn/record/43870510)|
# 解析
-----
题目大意是：

有一种排列是完美的。用$p_i$表示排列中的第$i$个元素，则完美的排列符合如下性质：

1. $p_{p_i}=i$
2. $p_i≠i$

求这个排列
-----
~~我不会向其他人一样严谨地证明~~

我来讲一讲我是怎么做的吧

首先我想到的是$p_i=i$，但是题目把它限制了

那么我想到的就是几个数组成一个轮回

那干脆就两个数吧，好像也只能是两个数呢

然后互相指向即可，那不就可以是$1~n$的倒序么？
# 代码
~~马蜂鬼畜，不要介意~~
```cpp
#include<bits/stdc++.h>
#define BetterIO ios::sync_with_stdio(false)
#define Fr(i,A,B,X) for(i=A;i<=B;i+=X)
#define Reg register
#define Ll long long
#define Iln inline
#define Str string
#define Chr char
#define Vod void
#define In int
using namespace std;
In main(Vod)
{
	BetterIO;
	Reg In N;
	cin>>N;
	if(N%2==1)
	{
		cout<<-1<<endl;
		return 0;
	}
	Reg In i;
	for(i=N;i>=1;i--)
	{
		cout<<i<<' ';
	}
	cout<<endl;
	return 0;
}
```

---

## 作者：C171501 (赞：1)

题目样例中，有一些重要的信息：

输入

`4`

输出

`2 1 4 3 `

可以看出，输出的每一个奇数位 $i$ 与其紧邻的后一个偶数位 $i+1$ 有:

 - $p_i=i+1$
 - $p_{i+1}=i$

如果输入是奇数，就必然存在一个数位上的数找不到可以与之配对的另一个数，不成立，输出 $-1$。

如果是偶数，则从第一位循环，每次 `i+=2`，输出 $i+1$ 与 $i$ 。

如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n;
	cin>>n;
	if(n%2!=0) cout<<"-1";
	else
	{
		for(int i=1;i<=n;i+=2)//每次循环i+=2到达下一个奇数数位
		{
			cout<<i+1<<" "<<i<<' ';
		}
	}
	return 0;
}
```


---

## 作者：LucasXu80 (赞：1)

看到题解区没有用Python的，本人来一篇吧。

其实这么简单的题，Python比C++还是要好很多了，免去打头文件什么的。

思路什么的各位大佬已经讲的很清楚了：

偶数的话，**倒序输出**即可，这样可以首末两两配对，满足题目条件。

而奇数无法两两配对，第一个条件不可能成立。

上代码！

```python
a=int(input()) #输入这个数，别忘了int()转化为整形
if a%2==1: #是奇数，无法两两配对
    print(-1) #输出-1
else: #是偶数
    for i in range(a,0,-1): #别忘了第二个数是0，不是1
        print(i,end=' ') #输出i及空格
```
这份代码长度98B，C++代码都要超过100B了。

虽然有点慢，但这题~~这么水~~不卡时间，自己写代码的时候节省点时间，不亦乐乎？

本人的第一篇Python题解，求过求赞~

---

## 作者：inoichi_lim (赞：0)

不难发现：
- 当$n=2$时有$p_1=2.p_2=1$。
- 若有另外两个数$i$和$j$，那么我们只需要让$p_{p_i}=i$和$p_{p_j}=j$即可。
- 但是$p_i\ne i,p_j\ne j$。
- 所以我们设$p_i=j,p_j=i$。
- 显然这里必须**有一对数才可以构成排列**，所以如果$n$是奇数，直接`-1`即可。
- 接下来，就看你怎么构造了。
- 我这里选择用尾到头，即$n,n-1,n-2,...,1$。

那么剩下的就是代码了：
```cpp
#include<bits/stdc++.h>
#define ns "-1"
#define fs(i,x,y,z) for(ll i=x;i<=y;i+=z)
#define ft(i,x,y,z) for(ll i=x;i>=y;i+=z)
#define ll long long
#define ull unsigned long long
#define db double
#define ms(a,b) memset(a,b,sizeof(a))
#define sz(a) sizeof(a)
using namespace std;
const int rw[]={-1,0,1,0,-1,1,-1,1},cl[]={0,1,0,-1,-1,1,1,-1};
const int N=100001,inf=0x7f7f7f7f;
const int daynum[]={114514,31,28,31,30,31,30,31,31,30,31,30,31};
const db E=2.718281828459,pi=acos(-1.0),eps=0.0000000001;
int n;
int main(){
    cin>>n;
    if(n&1) cout<<-1;
    else{
        ft(i,n,1,-1) cout<<i<<' ';
    }
    return 0;
}#include<bits/stdc++.h>
#define ns "-1"
#define fs(i,x,y,z) for(ll i=x;i<=y;i+=z)
#define ft(i,x,y,z) for(ll i=x;i>=y;i+=z)
#define ll long long
#define ull unsigned long long
#define db double
#define ms(a,b) memset(a,b,sizeof(a))
#define sz(a) sizeof(a)
using namespace std;
const int rw[]={-1,0,1,0,-1,1,-1,1},cl[]={0,1,0,-1,-1,1,1,-1};
const int N=100001,inf=0x7f7f7f7f;
const int daynum[]={114514,31,28,31,30,31,30,31,31,30,31,30,31};
const db E=2.718281828459,pi=acos(-1.0),eps=0.0000000001;
int n;
int main(){
    cin>>n;
    if(n&1) cout<<-1;
    else{
        ft(i,n,1,-1) cout<<i<<' ';
    }
    return 0;
}
```

---

