# Pizza, Pizza, Pizza!!!

## 题目描述

Katie, Kuro and Shiro are best friends. They have known each other since kindergarten. That's why they often share everything with each other and work together on some very hard problems.

Today is Shiro's birthday. She really loves pizza so she wants to invite her friends to the pizza restaurant near her house to celebrate her birthday, including her best friends Katie and Kuro.

She has ordered a very big round pizza, in order to serve her many friends. Exactly $ n $ of Shiro's friends are here. That's why she has to divide the pizza into $ n + 1 $ slices (Shiro also needs to eat). She wants the slices to be exactly the same size and shape. If not, some of her friends will get mad and go home early, and the party will be over.

Shiro is now hungry. She wants to cut the pizza with minimum of straight cuts. A cut is a straight segment, it might have ends inside or outside the pizza. But she is too lazy to pick up the calculator.

As usual, she will ask Katie and Kuro for help. But they haven't come yet. Could you help Shiro with this problem?

## 说明/提示

To cut the round pizza into quarters one has to make two cuts through the center with angle $ 90^{\circ} $ between them.

To cut the round pizza into five equal parts one has to make five cuts.

## 样例 #1

### 输入

```
3
```

### 输出

```
2```

## 样例 #2

### 输入

```
4
```

### 输出

```
5```

# 题解

## 作者：sh7adow_ (赞：4)

**~~我第一次发``CF``题解，好紧张啊！~~**

看到大家都介绍得很清楚，我就不详细展开了。

这道题很明显是一道挖坑题，所以我们得来分析。

他只输入一个数【代表客人人数】，但是：

``TA``自己也要吃啊！

所以，我们得到以下公式：
 
 $ \  \ \ \ \ \ \ \ \ \ \ $ $\mathtt{Total People}$ $=a+1$。
 
 用``Python``来表达是这样：
 ```python
a=input() # 这是定义变量a
b=int(a)+1  # Python简化，直接可以输入+计算
```
我们首先要进行``特判``：

如果没有客人呢？

那么``TA``自己就吃整个！~~【太懒了，连切都不想切，还挖坑】~~

特判要放在首位！【我自己都是这样】

特判要放在首位！【我自己都是这样】

特判要放在首位！【我自己都是这样】

重要的事情说三遍！

用``Python``来表达是这样：
 ```python
if b==1 :   # 注意：Python 的 if 不用括号，但要 冒号
    print("0")  # 输出是print 不是 printf
```

最后的判定就是：

奇数输出原数，偶数输出除以 $2$ 的数。

用``Python``来表达是这样：
 ```python
elif b%2==0 : # else if 简写成elif
    print(b//2) 
elif b%2!=0 : # 是  ！=  不是    =！
    print(b)
```

好了，接下来是完整代码：
```python
a=input()
b=int(a)+1
if b==1 :
    print("0")
elif b%2==0 :
    print(b//2)
elif b%2!=0 : 
    print(b)
```
注：所有的判定指的是除数 $b$，而不是 $a$ 。

最后，两个字：

过&&赞！

---

## 作者：小咪137902 (赞：2)

一道找规律的水题
==

如果n+1是奇数,答案为n+1；

如果n+1是偶数,答案为(n+1)/2。

不过······
--

特判第一位！
===

特判n+1=1的情况。

代码如下：
==

```c
#include<bits/stdc++.h>//万能头文件
using namespace std;//未命名空间
long long n;//10的18次方，也就是1000000000000000000。要开long long
int main()
{
    /*找规律*/
	cin>>n;//输入
	n++;//先加一
	if(n==1)//特判
		cout<<0<<endl;
	else if(n%2==0)
		cout<<n/2;
	else
		cout<<n;
	return 0;
} 
```


---

## 作者：封禁用户 (赞：2)

这一题我要仔细的为大家分析一遍（而不是像前面那两位同学直接说结论）

因为要分成n+1分，所以n输入后要加一
```
n++;
```
继续。我们阿里分析一下怎么得到切几刀。

首先，形状要一样，也就是说，每一块都得有一个圆弧（毕竟不可能每个都没有圆弧），然后嘛，他就一定是个扇形。他的半径*2就是大圆的直径。

![](https://cdn.luogu.com.cn/upload/pic/49748.png)

然后，就分类讨论

先看偶的↓↓↓
![](https://cdn.luogu.com.cn/upload/pic/49749.png)

再看奇的↓↓↓
![](https://cdn.luogu.com.cn/upload/pic/49750.png)

不过当输入的n==0时，you know~~

说了这么久，代码来了↓↓↓
```
#include <bits/stdc++.h>
using namespace std;
long long n;
int main()
{
	cin>>n;//输入 
	n++;
	if(n==1)//特判！ 
	cout<<0;
	else if(n%2==0)//偶数 
	cout<<n/2;
	else//奇数 
	cout<<n;
	return 0;
}
```
注意，int 存不下~~~

---

## 作者：海绵宝贝 (赞：2)

水！大水题！

当n+1是偶数除以2输出，

当n+1是奇数直接输出，

代码：


```cpp

	#include<bits/stdc++.h>//万能
    long long n;//保险起见开long long
	int main(){
	scanf("%lld",&n);
	if((n+1)%2==0||n==0)
    {
    	printf("%lld\n",(n+1)/2);
     	}
     		else
   	  	{
     	    printf("%lld\n",n+1);
     	}
    	return 0;
	}	//我...没什么好讲的...吧？
```
	

---

## 作者：Eason_AC (赞：1)

## Content
小 S 想把一块披萨切成大小、形状都相同的 $(n+1)$ 块（$n$ 块分给 TA 的 $n$ 个朋友，还有一块留给自己），试问最小需要切多少块。

**数据范围：$0\leqslant n\leqslant 10^{18}$。**
## Solution
首先这道题目坑的一点就是 $n$ 可能等于 $0$，这时候不需要再切了，答案是 $0$。

然后看 $n\neq 0$ 的情况。

首先是 $2\mid (n+1)$ 的情况，那么我们可以发现有两次可以当一次切，可以求得需要切的次数为 $\dfrac{n+1}{2}$。然后是 $2\nmid (n+1)$，那么没法再将多次当一次切了，那么需要且的次数就是 $(n+1)$。
## Code
```cpp
ll n, ans;

int main() {
	getll(n);
	writell(ans = (!n ? 0 : (((n + 1) % 2) ? n + 1 : (n + 1) / 2)));
	return 0;
}
```

---

## 作者：紫金依旧 (赞：1)

其实很简单,只需要找规律就行了

如果n+1是奇数,则答案为n+1

如果n+1是偶数,则答案为(n+1)/2

# 但是

需要特判n+1为1的情况

上代码:

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n;
int main()
{
	cin>>n;
	n++;
	if(n==1)
		cout<<0<<endl;
	else if(n%2==0)
		printf("%d\n",n/2);
	else
		printf("%d\n",n);	
	return 0;
} 
```
# 求通过,求赞

---

## 作者：末置lzy (赞：1)

# **CF979A**题解

#### 题外话

###### 这个题目可见作者对pizza的热爱

### 正题

**分析**

###### 这个题就是典型的小学数学问题，找规律

当你要n（偶数块）时，会发现其实就是需要切n/2刀

当你要n（奇数块）时，会发现其实就是要n块切n刀

所以我第一次的代码是这样的

```
#include<bits/stdc++.h>//霸气万能头
using namespace std;
int main()
{
    long long n;
    cin>>n;
    n+=1;
    if(n%2==0) cout<<n/2;
    else cout<<n;
    return 0;
}
```
然后它WA了，我才意识到他一个人竟然可以吃一整块pizza

所以...

## AC CODE

```
#include<bits/stdc++.h>//霸气万能头
using namespace std;
int main()
{
    long long n;
    cin>>n;
    n+=1;
    if(n==1) cout<<0;
    else if(n%2==0) cout<<n/2;
    else cout<<n;
    return 0;
}
```
好啦，结束了

~~蒟蒻真的想出篇题解，求审核大大通过啊~~

---

## 作者：zqwzqwzqw (赞：0)

[$\color{black}CF979\!A$](https://www.luogu.com.cn/problem/CF979A) **题解**

### 注意

$n$是客人数，而不是总人数，所以，**总人数**和**蛋糕切块数**都是$n\!+\!1$。

### 算法

以样例数据为例。

1. $n\!=\!3$，那么总块数为$4$，每一块的圆心角度为$\dfrac{360}{4}=90$，可以用过圆心的两刀切成$4$份，故输出$2$。

2. $n\!=\!4$，那么总块数为$5$，每一块的圆心角度为$\dfrac{360}{5}=72$，只能用不过圆心的$5$刀切成$5$份，故输出$5$。

3. 当$n\!=\!0$时，总块数为$1$，不需要切，输出$0$。

**推广下来**，$n$为$1$，输出$0$；$n$为非$1$奇数，输出$\dfrac{n+1}{2}$；$n$为偶数，输出$n\!+\!1$;

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n;
int main(){
	cin>>n;
	n++;
	if(n==1)
		cout<<0;
	else if(n%2==0)
		cout<<n/2;
	else cout<<n;
	return 0;
}
```

---

## 作者：bigju (赞：0)

#### 题目大意

有个人要请朋友吃饭，一共有 $n$ 位客人。现在主人订了一个比萨，现在她要把这个披萨分成 $n+1$ 份（她自己也要吃）,只能在平面上切，问要切几刀。

#### 大体思路

显然披萨是一个圆，而圆是一个轴对称图形，也就是说我们一刀切下去，如果是沿着直径切的话会把这个圆分成相等的两部分。那么当 $n+1$ 为偶数的时候，我们只需要切 $\frac{(n+1)}{2}$刀就可以完成任务。但是，如果 $n+1$ 是个奇数，这个时候就没法一刀切两个了，只能按照半径切了，那么就得老老实实 $n+1$ 刀了。但是这么做，你会发现你错在了第 $29$ 个点上，为什么？因为当一个客人都没有的时候，主人就不需要切了，直接输出 $0$，而按照刚才的做法我们会输出 $1$。

代码：

```cpp
#include<cstdio>
#include<iostream>
#define ll long long
using namespace std;
long long n;
int main()
{
    cin>>n;
    if(n==0) return cout<<0,0;
    n+=1;
    if(n%2==0) return cout<<n/2,0;
    if(n%2==1) return cout<<n,0;
}

```


---

## 作者：梁丘封冽 (赞：0)

思路非常简单，如果$n + 1$是偶数的话，就输出$(n + 1) \div 2$，否则直接把$n + 1$输出了就行。

但是如果$n$是0的话，你就会发现根本不用切，所以需要特判。

这里我用了一点位运算优化(虽然其实没什么用对吧)

AC代码如下

```cpp
#include<bits/stdc++.h>

using namespace std;

int main(void) {
	unsigned long long n;
	cin >> n;
	if(!n || ++n & 1) {
		cout << n << endl;
	}
	else {
		cout << (n >> 1) << endl;
	}
	return 0;
}
```


---

## 作者：Frozencode (赞：0)

找出规律即可

n+1为奇数时直接输出n+1

n+1为偶数时输出(n+1)/2即可

**注意特判1的情形**
------------

~~我是不会告诉你我因为这个被hack了~~


------------


```c
#include<bits/stdc++.h>
using namespace std;
long long n,sum;
int main()
{
    cin>>n;
    sum=n+1;
    if(sum==1)
    {
    	cout<<"0"<<endl;
    	return 0;
	}
	else{
    if(sum%2==0)cout<<sum/2;
    else cout<<sum;
	return 0;
}
}
```

---

