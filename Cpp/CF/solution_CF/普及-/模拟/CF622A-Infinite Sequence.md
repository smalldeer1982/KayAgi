# Infinite Sequence

## 题目描述

Consider the infinite sequence of integers: $ 1,1,2,1,2,3,1,2,3,4,1,2,3,4,5... $ . The sequence is built in the following way: at first the number $ 1 $ is written out, then the numbers from $ 1 $ to $ 2 $ , then the numbers from $ 1 $ to $ 3 $ , then the numbers from $ 1 $ to $ 4 $ and so on. Note that the sequence contains numbers, not digits. For example number $ 10 $ first appears in the sequence in position $ 55 $ (the elements are numerated from one).

Find the number on the $ n $ -th position of the sequence.

## 样例 #1

### 输入

```
3
```

### 输出

```
2
```

## 样例 #2

### 输入

```
5
```

### 输出

```
2
```

## 样例 #3

### 输入

```
10
```

### 输出

```
4
```

## 样例 #4

### 输入

```
55
```

### 输出

```
10
```

## 样例 #5

### 输入

```
56
```

### 输出

```
1
```

# 题解

## 作者：Aw顿顿 (赞：8)

首先一开始想到的是暴力模拟，于是有了这样的一个思路雏形：

- 读入 $n$ 并进入 `while` 循环。

- 每次有一个“光标”，如果达到了光标，就清零，同时光标上移。

- 一直循环 $n$ 次。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,s=1,k=1,cnt;
int main(){
    cin>>n;
    while(s<=k){
        cnt++;
        if(cnt==n){
            break;
        }
        if(s==k){
            s=1;
            k++;
        }
        else s++;
    }
    cout<<s<<endl;
    return 0;
}
```

但是 [TLE](https://www.luogu.com.cn/record/32484396) 了。

于是认真的常数优化了一番，结果，[TLE](https://www.luogu.com.cn/record/32484460)，果然模拟 风 评 被 害 不 可 避。

所以必须考虑**数学**的解法。

首先将这个很容易看出规律的数列：

$$1,1,2,1,2,3,1,2,3,4,1,2,3,4,5$$

在 `oeis.org` 上查询的结果是 [A002260](http://oeis.org/A002260)。

然后结果他给出的通项是：

$$\rm Triangle-T(n,k) = k\ ,\ k=1\cdots n$$

~~似乎就是模拟超时~~


我们来列一个表格看看：

| 序号 | 单调递增序列 |
| -----------: | -----------: |
| $1$ | $1$ |
| $2$ | $1,2$ |
| $3$ | $1,2,3$ |
| $4$ | $1,2,3,4$ |

我们会发现他们是**一一对等**的。

也就是说，$n$ 是左边一列的和，而其对应的内容是右边。

那么这就需要我们判断 $n$ 的所在行。

每次，$n$ 都可以减去不属于他的行，一直减到他刚好为止。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,cnt=1;
int main(){
    cin>>n;
    while(n>0){
        n-=cnt++;
    }
    cout<<(n>0?n:n+cnt-1)<<endl;
    return 0;
}
```

最后要判断是否过小。

评测结果：https://www.luogu.com.cn/record/32484720

那么我们可以写出以下代码



---

## 作者：wuwenjiong (赞：2)

## 题意：
现有一串数列：
```cpp
1 1,2 1,2,3 1,2,3,4 1,2,3,4,5 1,2,3,4,5,6 ...
```
求第 $n$ 个数是什么， $1\le n\le10^{14}$ 。

这串数列的规律很明显，那么我们可以将每一串看作一个组，串中的每个数字都是这个组的组员，不难发现，每组的组员总数就是这一组的序号，且每组的最后一个组员就是这一组的序号。即下表：
| 组 | 组员 |
| :----------- | :----------- |
| $1$ | $1$ |
| $2$ | $1,2$ |
| $3$ | $1,2,3$ |
| $4$ | $1,2,3,4$ |
| $5$ | $1,2,3,4,5$ |
| $...$ | $...$ |
| $n$ | $1,2,3,4,...,n$ |

### 思路：
开一个循环，每次循环， $s$ 加上 $i$ ，然后判断，如果 $s$ 大于或者等于 $n$ ，就跳出循环，否则 $i$ 自增，并进行下次循环。代码实现如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,i,s,x;
int main()
{
	cin>>n;
	for(i=1;;i++)
	{
		s+=i;
		if(s>=n)
			break;
	}
	x=i-(s-n);
	cout<<x;
	return 0;
}
```
谢谢！！！

---

## 作者：封禁用户 (赞：1)

题目传送>>[CF622A](https://www.luogu.com.cn/problem/CF622A)  
### 题意简述:  
- 一串数：   $1,1,2,1,2,3,1,2,3,4,1,2,3,4,5......$，求其第 $n$ 个数。  
- $1\le n \le 10^{14}$。  
  
### 题目分析：  
通过观察，我们可以发现其实这串数是由多组局部自然数串接而成，即：
  
| 组 | 元素 |
| :----------- | :----------- |
| $1$ | $1$ |
| $2$ | $1,2$ |
| $3$ | $1,2,3$ |
| $4$ | $1,2,3,4$ |
| $5$ | $1,2,3,4,5$ |
| $...$ | $...$ |
| $n$ | $1,2,3,...,n$ |
且每组的元素总数即为该组组号，其元素为到该组组号的各自然数。  
此题求总串中第 $n$ 个数，而观察组与元素个数的关系可发现到第 $n$ 组时占总串中数的个数即为组号 $1$ 依次累加组号至组号 $n$，即 $1+2+3+...+n$，据自然数求和公式，即 $\frac{n(n+1)}{2}$。而每组完毕转入新的一组，元素又从 $1$ 开始，所以说要求总串中第 $n$ 个数，我们可以将结果数所在的组之前的所有组的元素总数减去，剩余几，则该组中第几个数（即几）就是要求的结果数。   
#### 注意题目数据范围，需要使用 long long。
### Code:  
```cpp
#include <iostream>
using namespace std;
typedef long long ll;   //类型定义long long为ll，避免频繁使用long long时累手
int main()
{
	ios::sync_with_stdio(0);   //关闭同步流加速cin输入和cout输出
	ll n;   //定义n
	ll i=0,q;   //定义组号、要求数所在组之前所有组中元素总数
	cin>>n;
	while(((i*(i+1))/2)<n)   //前i组所有组中元素个数小于n，求要求数所在组之前共几组
	{
		i++;
	}
	i-=1;   //i自增后跳出循环，现将最后一次自增还原
	q=(i*(i+1))/2;    //利用自然数求和公式求要求数所在组之前所有组中元素总数
	cout<<n-q;   //输出要求数在其所在组中的位置，即总串中第n个数
	return 0;   //结束整个程序
}
```
### 结果（未吸氧）:  
![JieGuo](https://cdn.luogu.com.cn/upload/image_hosting/ji7lpdzj.png)  
企鹅的题解到此结束，祝各位 OIers 进步 ++~

---

## 作者：Insouciant21 (赞：1)

对于数列 $1,1,2,1,2,3,1,2,3,4\ldots$ ，求第 $n$ 项的值。

将数列分节 
$$
\left\{
\begin{aligned}
&1 \cdots 1\\
&1,2 \cdots 2\\
&1,2,3 \cdots 3\\
&1,2,3,4 \cdots 4\\
&\cdots
\end{aligned}
\right.
$$

计算第 $n$ 项的值可先计算前面有多少个完整的节，然后取剩下的部分即为该项值。

前面的部分就是计算这个式子
$$\sum_{i=1}^mi<=n$$

直接设该式等于 $n$ 然后用等差数列求和公式拆开列方程得 $\dfrac{m(m+1)}{2}=n$

求得 $m=\dfrac{-1+\sqrt{1+8n}}{2}$ ，将 $m$ 向下取整就是前面的节数（ $m=\lfloor m\rfloor$ ）

易得答案为 $ans=n-\dfrac{m(m+1)}{2}$

注意如果此时 $ans=0$ ，就是第 $n$ 项为该节的最后一项，使 $ans=m$ 即可。

AC 代码
```
#include <bits/stdc++.h>

using namespace std;

int main() {
    long long n;
    scanf("%lld", &n);
    long long num = (-1 + sqrt(1 + 8 * n)) / 2.0;
    long long res = n - num * (num + 1) / 2;
    if (res == 0)
        res = num;
    printf("%lld", res);
    return 0;
}
```



---

## 作者：☆木辛土申☆ (赞：1)

都用循环的吗，这不是道数学题吗QwQ

先求出n的前面有几组数，然后求出n前一共有几个数，最后用n减去它就行了

```cpp
#include<cstdio>
#include<cmath>

int main(){
	long long n;scanf("%lld",&n);
	long long x=ceil(sqrt(1+8.0*n))/2-1;
    //x是方程x(x+1)/2=n的正根减去1，看不懂的手解一下方程
	printf("%lld\n",n-x*(1+x)/2);
    //求出前面一共有多少个数，用n减去它
	return 0;
}

---

## 作者：QGhappy_Alan (赞：1)

从Zealot大佬的翻译中不难看出这组数据的规律，由于我是用类似数学的方法，和楼下大佬的模拟做法不太一样，所以在此不做解释了。
这里贴下AC代码：
```cpp
#include<iostream>
#include<cstdio>
using namespace  std;
typedef long long ll;
ll n,s,i=1;
int main()
{
    scanf("%lld",&n);
	while(s<n)
	{
		s+=i;i++;
	}
	i--;
	printf("%lld",i-(s%n));
}
```

---

## 作者：LW_h_FP (赞：1)

我看到这题最开始想到的就是模拟，但是数据太大了。

看了一下题目

```
 1 1,2 1,2,3 1,2,3,4 1,2,3,4,5 1,2,3,4,5,6 1,2,3,4,5,6,7
```

再换行一下

```
 1                1个
 1,2              2个
 1,2,3            3个
 1,2,3,4          4个
 1,2,3,4,5        5个    如果n在这行的话就减去前面的，即n-1-2-3-4就是答案了
 1,2,3,4,5,6      6个
 1,2,3,4,5,6,7    7个
```

看了一下要求的数，读入的数就是从最上面的个数一直加到他就是n了，所以求的就是它减去它前面的行的数字就直接得到了

这里用一个while循环从1开始加

```
#include<iostream>
using namespace std;

int main(){
    long long n,cnt=1; cin>>n;
    while(n>=1&&n/cnt>0&&(n%cnt!=0||n/cnt>1))//主要说一下这里，就是如果这行不是它所在的那一行就可以直接减去这个数量
        n-=cnt,cnt++;//减去之后再去到下一行
    cout<<n;
    return 0;
}
```

---

## 作者：skyfly886 (赞：0)

[题目](https://www.luogu.com.cn/problem/CF622A)

对于题目给出的数列“1,1,2,1,2,3,1,2,3,4,1,2,3,4,5...”，我们可以将它拆分为无数个小数列，如下表格：

|  数列| 数列内容 |
|:----------- |-----------|
| $a_1$|$1$  |
| $a_2$|  $1,2$|
| $a_3$| $1,2,3$ |
| $··· $| $···$ |
| $a_i$| $1,2,3,···,i$ |

于是就得到了以下的一段代码。

```cpp
for(long long i=1;ans+i<=n;i++){//这里的i表示数列ai的个数
	ans+=i;
}
```
经此计算后的 ans 表示的就是整个数列中 1~$n$ 中的最靠后的完整的小数列中的最后一个数的位置。所以，$n$-ans 即为答案。

#### 可是，如果 $n$ 等于 ans 呢？

那就说明 $n$ 就在整个数列中 1~$n$ 中的最靠后的完整的小数列中的最后一个数的位置，答案即为 $i$ 。

# Code:
```cpp
#include<bits/stdc++.h>
using namespace std;

int main(){
	long long n,ans=0,z=0;
	scanf("%lld",&n);
	for(long long i=1;ans+i<=n;i++){
		ans+=i;
		z=i;
	}
	if(ans==n){
		printf("%lld",z);
	}
	else{
		printf("%lld",n-ans);
	}
	return 0;
}
```


---

## 作者：伟大的王夫子 (赞：0)

先安利一下[我的博客](https://www.luogu.com.cn/blog/I-AK-IOI/)

设$n$前面有$k$组，则前面$k$组有$\dfrac{k(k+1)}{2}$

所以设$n =  \dfrac{k(k+1)}{2} + m$

$\dfrac{k(k+1)}{2} \le n$

得$k_{\max} = \dfrac{-1 + \sqrt{8n+1}}{2}$

再解出$m$，输出$m$即可

或者$m=0$,$n$刚好是第$k$组最后一个，输出$k$即可

code

```cpp
// luogu-judger-enable-o2
#include <bits/stdc++.h>
using namespace std;
long long n;
int main() {
	cin >> n;
	long long k = ceil((sqrt(8.0 * n + 1))) / 2 - 1;
	long long m = n - k * (k + 1) / 2;
	if (m == 0) printf("%lld", k);
	else printf("%lld", m);
}
```

---

## 作者：Corsair (赞：0)

本人不是怎么会用Markdown，请见谅。

## 大家可以把数据用图表示出来
1. 	1
1. 	1,2
1. 	1,2,3
1. 	1,2,3,4
1. 	1,2,3,4,5
1. 	1,2,3,4,5,6
1. 	1,2,3,4,5,6,7
1. 	1,2,3,4,5,6,7,8  
1. 	1,2,3,4,5,6,7,8,9
1. 	1,2,3,4,5,6,7,8,9,10
1. 	1,2,3,4,5,6,7,8,9,10,11

可以直接模拟数字 1 的位置。

### 千万不要用数组会 MLE 的


下面直接贴代码。


```
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,x=1,y;
// x 上一个数, y 当前的数。 
int main()
{
	cin>>n;
	if(n==1) {cout<<1<<endl; return 0;}
	//特殊判断 
	for(ll i=2;i<=50000000;i++)
	{
   	//for循环内一定要开ll，不然会爆的。
		y=i*(i-1)/2+1;
    //第i个1 的位置。
		if(y>=n)
		{
			if(y==n) {cout<<1<<endl; return 0;}
            // 1的位置，直接输出。
			else {cout<<n-x+1<<endl; return 0;}
            // 注意：一定要+1.
		}
		x=y;
	}
	return 0;
}
```



---

