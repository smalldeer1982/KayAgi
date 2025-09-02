# [ABC083C] Multiple Gift

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc083/tasks/arc088_a

高橋君は、日頃の感謝を込めて、お母さんに数列をプレゼントすることにしました。 お母さんにプレゼントする数列 $ A $ は、以下の条件を満たす必要があります。

- $ A $ は $ X $ 以上 $ Y $ 以下の整数からなる
- すべての $ 1\leq\ i\ \leq\ |A|-1 $ に対し、$ A_{i+1} $ は $ A_i $ の倍数であり、かつ $ A_{i+1} $ は $ A_i $ より真に大きい

高橋君がお母さんにプレゼントできる数列の長さの最大値を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ X\ \leq\ Y\ \leq\ 10^{18} $
- 入力は全て整数である

### Sample Explanation 1

数列 $ 3,6,18 $ が条件を満たします。

## 样例 #1

### 输入

```
3 20```

### 输出

```
3```

## 样例 #2

### 输入

```
25 100```

### 输出

```
3```

## 样例 #3

### 输入

```
314159265 358979323846264338```

### 输出

```
31```

# 题解

## 作者：UnyieldingTrilobite (赞：3)

Update:修了一点排版，重新审核

分析：

首先，这题如果要长度最大，**那么首项必然尽量小，即为x**。

由于首项是x故每一项都是**x的倍数**，可以同除以x。

现在就是要求 $1,2,\ldots,[\frac{y}{x}]$ 中能有多少项。

接着暴力膜你每一项就行了······

上代码，Python3：
```
x,y=input().split();
k,w=int(y)//int(x),0
while 2**w<=k:w=w+1
print(w)
```

Over，对于不想搞事的同志，到这里已经没了。

**接着来一种高能玩玩······**

~~自然语言编程~~

更详细的可以戳[这里](https://www.luogu.com.cn/blog/2007100723874wxz/define)。

然后就是“自然语言”代码······

```cpp
I have some long integers called x,y;
Let us begin;
Use the way of input(x,y);
I have some long integers called k(y divided by x),w(0),p(1);
While the value of p is less than the value of k plus 1 do{
    Let the value of w be the value of w plus 1;
    Let the value of p be the value of p times 2;
}
Print out w;
Print out '\n';
That is all;
Thank you so much;
```

~~英语作文既视感。~~

代码前加上[这些](https://www.luogu.com.cn/paste/yd432osb)，语言选C++14就好了（滑稽。

真·Over.

祝大家切题愉快！

---

## 作者：不到前10不改名 (赞：2)

//一看就知道，这题很水，先上一个暴力吧！
```
#include<stdio.h>
int lgx;
long long x,y;
int main()
{
    scanf("%lld%lld",&x,&y);
    long long i=x;
    while(i<=y) //暴力枚举模拟，没什么好说的
    {lgx++;
    i*=2;}
    printf("%d\n",lgx);///回车是必须的~QAQ
}
```
//正解
因为这个序列后一个数是前一个数的两倍，设序列a长度为n
则有y/x=n;
具体代码实现
```
#include<stdio.h>
int main()
{
    long long x,y,srx,sum=0;
    scanf("%lld%lld",&x,&y);
    srx=((long long)(y/x));
    while(srx>=1)
    {srx/=2;
    sum++;}
    printf("%d\n",sum);
    return 0;
}
```

---

## 作者：Kiel (赞：1)

小学解方程，~~尽管我提交了3次~~。

解：
 
 
 x*$n^2$=y
    
 y/x=$n^2$
    
所以只要求n的个数就行！

第一次TLE错了6个点，因为 ans!=1,但是应该是 ans>=1;后来就对了。

```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
    long long x,y,ans,sum=0;
    cin>>x>>y;
    ans=((long long)(y/x));
    while(ans>=1)ans/=2,sum++;
    cout<<sum<<endl;
    return 0;
}

```


---

## 作者：CZQ_King (赞：0)

### $WA$了几次发现选的语言是$C++$。。。（其实应该是$C++14$）

------------
这是一道很简单的题，从题意中我们可以看出：
### $x\ast2^{ans}=y$
### $\quad\ \ 2^{ans}=\frac{y}{x}$
### $\quad\ \ \ ans=\log_2(\frac{y}{x})$
因为包括$x$和$y$，所以变成了$ans=\lfloor\log_2(\frac{y}{x})\rfloor+1$

------------
代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long x,y;
int main(){
    cin>>x>>y;
    cout<<floor(log2((long double)(y/x)))+1<<endl;//按照公式算
    return 0;
}
```

---

## 作者：Chthology (赞：0)

题意较简单，就不翻译了~~(懒~~


---
###解：

######~~水题~~

从X开始每次乘2，ans++，直到大于Y为止

```cpp
#include<bits/stdc++.h>
using namespace std;

int ans;
long long x,y;

int main(){
    cin>>x>>y;
    long long i=x;
    while(i<=y) ++ans,i*=2;
    cout<<ans;
}
```
######蒟蒻题解，dalao轻喷


---

## 作者：I_will (赞：0)

这道题的思路是这样的：

* 输入x和y。
* 用a保存y÷x。
* 从1开始，不停×2，直到2的次方数大于a。
* 输出最后的次方数+1。

这就是程序：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long x,y,h,no;
int g;
int main()
{
	cin>>x>>y;
	h=y/x;
	no=1;
	while(no<=h)
	{
		g++;
		no*=2;
	}
	cout<<g<<endl;
	return 0;
}
```


---

