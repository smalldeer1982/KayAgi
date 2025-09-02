# Weird Subtraction Process

## 题目描述

两个数 $a$ 和 $b$ 要对它们做以下操作:

1. 如果 $a=0$ 或 $b=0$ ，结束程序。否则执行第 $2$ 步。

2. 如果 $a\geq2b$ ，把 $a$ 变为 $a-2b$ ，并返回第 $1$ 步。否则执行第 $3$ 步。

3. 如果 $b\geq 2 a$ ，把 $b$ 变为 $b-2a$，并返回第 $1$ 步。否则结束程序。

你需要将 $a,b$ 持续进行操作直到结束程序，输出结束程序时的 $a,b$。

## 样例 #1

### 输入

```
12 5
```

### 输出

```
0 1
```

## 样例 #2

### 输入

```
31 12
```

### 输出

```
7 12
```

# 题解

## 作者：zhang_kevin (赞：9)

[题目传送门](https://www.luogu.com.cn/problem/CF946B)

# $1$. 题意简述

两个数 $a$ 和 $b$ 要对它们做以下操作:

1. 如果 $a=0$ 或 $b=0$ ，结束程序。否则执行第 $2$ 步。

2. 如果 $a\geq2b$ ，把 $a$ 变为 $a-2b$ ，并返回第 $1$ 步。否则执行第 $3$ 步。

3. 如果 $b\geq2a$ ，把 $b$ 变为 $b-2a$，并返回第 $1$ 步。否则结束程序。

你需要将 $a,b$ 持续进行操作直到结束程序，输出结束程序时的 $a,b$。

# $2$. 本题高复杂度解法

观察题意简述，这道题直接模拟即可。

详细内容已经放到代码的注释里面。

```cpp
#include<iostream>
using namespace std;
typedef long long ll;
int main(){
	ll a, b;
	cin >> a >> b;
	while(true){                     //循环 
		if((a==0)||(b==0)){          //步骤 1 
			break;                   //结束循环 
		}else if(a>=2*b){            //步骤 2
			a = a - 2 * b;           //改变 a 的值
			continue;                //回到步骤 1
		}else if(b>=2*a){            //步骤 3 
			b = b - 2 * a;           //改变 b 的值 
		}else{                       //否则 
			break;                   //结束循环 
		}
	}
	cout << a << " " << b << endl;
	return 0;
}
```

然后获得了 [TLE](https://codeforces.com/contest/946/submission/167924217) ，因此我们要对代码进行优化。

# $3$. 本题低复杂度解法

可以看到本题高复杂度解法一直在进行 `a = a - 2 * b;` 以及 `b = b - 2 * a;`。不难发现，这就是 `a %= 2 * b` 与 `b %= 2 * a` 。

因此我们把这两句代码替换一下就好了。

最终的 [AC](https://codeforces.com/contest/946/submission/167924849) 代码：

```cpp
#include<iostream>
using namespace std;
typedef long long ll;
int main(){
	ll a, b;
	cin >> a >> b;
	while(true){                     //循环 
		if((a==0)||(b==0)){          //步骤 1 
			break;                   //结束循环 
		}else if(a>=2*b){            //步骤 2
			a %= 2 * b;              //改变 a 的值
			continue;                //回到步骤 1
		}else if(b>=2*a){            //步骤 3 
			b %= 2 * a;              //改变 b 的值 
		}else{                       //否则 
			break;                   //结束循环 
		}
	}
	cout << a << " " << b << endl;
	return 0;
}
```


---

## 作者：LiAuPb (赞：5)


[题目传送门](https://www.luogu.com.cn/problem/CF946B)

1.题目大意
两个数 $a$ 和 $b$ 要对它们做以下操作：

（1）如果 $a=0$ 或 $b=0$，结束程序。否则执行第 2 步。

（2）如果 $a≥2b$，把 $a$ 变为 $a-2b$，并返回第 1 步。否则执行第 3 步。

（3） 如果 $b≥2a$，把 $b$ 变为 $b-2a$，并返回第 1 步。否则结束程序。

你需要将 $a$，$b$ 持续进行操作直到结束程序，输出结束程序时的 $a$，$b$。

2.坑

看完后我们很自然的想到了模拟，一波代码下去……

但是有个坑! $1 <= a, b <= 10^{18}$ 所以要开 long long。 然后心满意足地交了：

```c
#include<bits/stdc++.h>
using namespace std;
long long a, b; 
int main()
{
    cin >> a >> b;
    while(1)
    {
        if(a == 0 || b == 0)break;
        else if(a >= 2 * b)a -= 2 * b;
        else if(b >= 2 * a)b -= 2 * a;
        else break;
    }
    cout << a << " " << b;
    return 0;
} 
```

得了TLE。

因为还有第二个坑
如果$a = 1, b = 10^{18}$，那么要执行 $5 * 10^{17}$ 次，肯定超时。 我们想一下，直到减到条件不满足，不就是取模吗？ 最后的AC代码：

3.AC代码

```c
#include<bits/stdc++.h>
using namespace std;
long long a, b; 
int main()
{
    cin >> a >> b;
    while(1)    //一直执行直到break 
    {
        //是否break
        if(a == 0 || b == 0)break;  //10、12、14、16行判断
        //是否改变a值
        else if(a >= 2 * b)a %= 2 * b;
        //是否改变b值
        else if(b >= 2 * a)b %= 2 * a;
         //都不成立就break
        else break;
    }
    cout << a << " " << b;  //输出，完结撒花
    return 0;
} 
```

这是本蒟蒻写的第一篇题解。

---

## 作者：LucasXu80 (赞：5)

Python题解一篇！

先看思路。相信所有人都能想到按题意直接模拟，直到需要退出程序就退出。但是，直接这样做会[TLE](https://www.luogu.com.cn/record/34326149)。

为什么？试想一组极端数据$a=1,b=10^{18}$。

稍微想想就知道它很慢，要做$5×10^{17}$次减法。那怎么办？

用**取模**。

你可能会问：为什么可以取模？

我们再构造一组数据：$a=1,b=5$。

最后答案的过程：$b=5-(1×2)-(1×2)=1$。此时应该退出循环。

我们来看这个过程：咦，这不就是将$5$不断$-2$，直到其不能再减（$<2$）吗？

换句话说，不就是$5$**对**$2$**取模**吗？

这样可以减少很多的步骤，省不少的时间。

好了，这样我们就把思路搞定了。看看代码吧！

```python
import sys
a,b=map(int,input().split()) #输入两个数
while 1: #无限循环
    if a==0 or b==0: #第一种情况
        print(a,end=' ')
        print(b)
        sys.exit() #别忘了结束程序
    if a>=2*b: a%=2*b #第二种情况
    elif b>=2*a: b%=2*a #第三种情况
    else: #无法再操作
        print(a,end=' ')
        print(b)
        sys.exit() #结束程序
```


------------

### 彩蛋（水，勿纠错）

用减法做到底有多慢？

为了得出这个结论，我在Dev C++里面试了试，采用数据是$a=10^{18},b=1$。

一开始我直接输进去算，然后等了五分钟没动静。

然后我就把$a$的值改成$10^{12}$，心想这次应该会快很多吧。但是还是没动静。。。

最后我改成了$a=10^{10}$。这次输出答案$0$用了$27$秒。

我们知道，这$27$秒做了至少$5×10^9$次运算。那么如果拿原数据进行计算，就要做$5×10^{17}$次运算，是前者的$10^8$倍。

那么时间就是$27×10^8$秒$=750000$小时$=31250$天，约合$85$年……

哈哈，还好我没有硬等……

当然这个结论可能并不准确，大家别太在意哈哈。


------------

好了，这篇题解就到此为止了。希望大家喜欢，求赞！

---

## 作者：Hughpig (赞：2)

由于 $a,b\le 10^{18}$，我们需要开 `long long`。并且如果使用模拟的话最多会有 $5\times 10^{17}$ 次操作，必然会 $\text{TLE}$。

我们考虑优化。

第一个操作是退出，无法优化。这里考虑操作 $2$ 和操作 $3$。

拿操作 $2$ 举例。

如果操作完后，$a$ 仍然大于等于 $2\times b$ ，将会继续执行此操作，直到 $a<2\times b$ 为止，即无法进行操作了。

这样做，等同于求 $a$ 除以 $2\times b$ 的余数。即 $a\bmod (2\times b)$。

同理，操作 $3$ 可以优化为 $b\bmod (2\times a)$。

代码：

```cpp
#include<bits/stdc++.h>//头文件
using namespace std;

int main()
{
	long long a,b;//变量，注意 long long
	cin>>a>>b;
	while(1)
	{
		if((!a)|(!b))break;//操作 1，即结束操作
		else if(a>=2*b)a%=(2*b);//操作 2，使用取模优化
		else if(b>=2*a)b%=(2*a);//操作 3，同操作 2
		else break;
	}
	cout<<a<<' '<<b;
}
```

---

## 作者：小睿睿 (赞：1)

其实这道题也是比较简单的。

先翻译一下题目：

1. 第 $1$ 步，如果 $a=0$ 或者 $b=0$ ，结束过程。否则，跳到第 $2$ 步。

2. 第 $2$ 步，如果 $a>=2\times b$，则把 $a$ 变成 $a-2\times b$，跳到第 $1$ 步。否则，跳到第 $3$ 步。

3. 第 $3$ 步，如果 $b>=2\times a$ ，则把$b$ 变成 $b-2\times a$，跳到第 $1$ 步。否则，结束过程。

于是这道题我们很轻松的想到模拟。

但是这道题有几个坑。

1. 数据范围是 $1<=n,m<=10^{18}$ ， $int$类型装不下，所以我们必须开 $long$ $long$ 。

2. 我们发现，第 $2$ 步和第 $3$ 步中如果用减法会非常慢，为什么呢？ 

	试想一组极端数据：$a=10^{18},b=1$，那么此时如果一直做减法，则会做 $5\times 10^{17}$次减法，此时肯定会超时。
    
    那我们怎么办呢？还是用上面那组数据，我们发现，我们一直在用 $a$ 去减 $2\times b$ ，直到 $a$ 小于$2\times b$为止，其实就是 $a$ 除以 $2\times b$的余数，不就是取模的运算吗？
    
    所以在减法的过程就直接可以用取模来做就行了，节省了不少时间。
    
于是我们就可以上代码了：

```cpp
#include<bits/stdc++.h>//万能头文件 
using namespace std;
int main()
{
	long long a,b;//注意定义long long 
	cin>>a>>b;
	while(1)//循环 
	{
		if(a==0||b==0) break;//第一步 
		if(a>=2*b) a%=(2*b);//满足第二步的条件 
		if(a==0||b==0) break;//跳到第一步 
		if(b>=2*a) b%=(2*a);//满足第三步的条件 
		if(!(a>=2*b&&b>=2*a)) break;//判断结束条件 
	} 
	cout<<a<<" "<<b;
	return 0;
}
```
完结散花！

---

## 作者：_D06 (赞：1)

方法：按题目模拟，不过在-的时候变成%（不然会TLE）
注意：1 要开long long
      2 无法继续做下去就要退出了
c++ 代码：
```cpp
#include<bits/stdc++.h>
using namespace std; 
int main()
{
	long long a,b;//注意变量类型 
	cin>>a>>b;
	bool f=false;
	while(1)
	{
	if(a==0||b==0)
	{
		break;
	}
	
	f=false;
	if(a>=2*b)
	{
		a%=(2*b);
		f=true;
	}
	
	if(a==0)
	{
		break;
	} 
	
	if(b>=2*a)
	{
		b%=(2*a);
		f=true;
	} 
	
    if(f==false)
    {
    	break;//无法继续更新则退出 
	}
	} 
	cout<<a<<' '<<b<<endl;
	return 0;
}

```

---

## 作者：Eason_AC (赞：1)

## Content
有两个数 $a,b$，执行如下操作：

1. 如果 $a,b$ 中有一个数是 $0$，结束操作，否则跳到操作 $2$。
2. 如果 $a\geqslant 2b$，那么 $a\leftarrow a-2b$，并跳回操作 $1$，否则跳到操作 $3$。
3. 如果 $b\geqslant 2a$，那么 $b\leftarrow b-2a$，并跳回操作 $1$，否则结束操作。

求出操作结束后的 $a,b$。

**数据范围：$1\leqslant a,b\leqslant 10^{18}$。**
## Solution
那么我们发现，如果 $a=10^{18},b=1$ 的极限数据下，直接模拟肯定会时间爆炸的，那么怎么办？我们发现，如果满足要求，那么一个数会一直减一直减，知道这个数不满足要求为止，那么不就是取模操作吗？那么上面的 $2,3$ 操作换成 $a\leftarrow a\mod 2b,b\leftarrow b\mod 2a$，不就可以节省很多时间吗？

剩下的就只是判断的问题了。
## Code
```cpp
long long a, b;

void ans(ll a, ll b) {
	if(!a || !b) {
		writell(a), putchar(' '), writell(b);
		return;
	}
	if(a >= 2 * b)	ans(a % (2 * b), b);
	else if(b >= 2 * a) 	ans(a, b % (2 * a));
	else {
		writell(a), putchar(' '), writell(b);
		return;
	}
}

int main() {
	getll(a), getll(b);
	ans(a, b);
	return 0;
}
```

---

## 作者：zhouzihe (赞：0)

## 1 观察题目
观察题目，不难发现这是一道模拟题，只要模拟出这三种操作就行了。  

但是我们还要注意一下数据范围是 $1 \leq a,b \leq 10^{18}$，我们可以假设 $a=10^{18}$，$b=1$，不难算出需要运行 $5 \times 10^{17}$ 次，铁定超时。  

所以我们可以在模拟时，当 $a \geq 2b$ 时，可以直接 $a$ $\bmod$ $2b$，同理，当 $b \geq 2a$ 时，可以直接 $b$ $\bmod$ $2a$。
## 2 code
```cpp
#include<bits/stdc++.h>
using namespace std;
long long int a,b;
int main(){
	cin>>a>>b;
	while(a!=0&&b!=0){
		if(a>=2*b){
			a%=(2*b);
		}
		else if(b>=2*a){
			b%=(2*a);
		}
		else{
			break;
		}
	}
	cout<<a<<" "<<b;
	return 0;
}
```


---

## 作者：lmndiscyhyzdxss (赞：0)

## 题目大意
两个数 $ a $ 和 $ b $ 要对它们做以下操作：

如果 $ a=0 $ 或 $ b=0 $，结束程序，否则执行第 $ 2 $ 步。

如果 $ a\geq2b $，把 $ a $ 变为 $ a-2b $，并返回第 $ 1 $ 步。否则执行第 $ 3 $ 步。

如果 $ b\geq2a $，把 $ b $ 变为 $ b-2a $，并返回第 $ 1 $ 步。否则结束程序。

你需要将 $ a $, $b $ 持续进行操作直到结束程序，输出结束程序时的，$ a $，$ b $。
## 题目分析
首先想到的就是直接模拟。
```cpp
#include<bits/stdc++.h>
using namespace std;
long long a,b;
int main(){
	cin>>a>>b;
	while(a!=0||b!=0)
	{
		else if(a>=2*b){a=a-2*b;continue;}
		else if(b>=2*a)b=b-2*a;
		else break;
	}
	cout<<a<<" "<<b<<endl;
	return 0;
}
```
但是，$ 1\leq a,b\leq 10^{18} $，时间复杂度太高了，$ O\left(a/2b\right) $

其实，这及其类似辗转相除法求最大公因数 $ \gcd(a,2b) $，如果 $ a $ 很大而 $ b $ 很小的话，此时会减很多次，直接用求余即可。
```cpp
#include<bits/stdc++.h>
using namespace std;
long long a,b;
int main(){
	cin>>a>>b;
	while(a!=0&&b!=0)
	{
	    if(a>=2*b)a%=2*b;
		else if(b>=2*a)b%=2*a;
		else break;
	}
	cout<<a<<" "<<b<<endl;
	return 0;
}
```

---

## 作者：diqiuyi (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF946B)

**题意**

给定 $2$ 个正整数 $a$ 和 $b$，然后对它们进行如下操作：

$1.$ 若 $a=0||b=0$，则结束运行，否则执行操作 $2$。

$2.$ 若 $a \ge 2b$，则 $a \gets a-2b$，并返回操作 $1$，否则执行操作 $3$。

$3.$ 若 $b \ge 2a$，则 $b \gets b-2a$，并返回操作 $1$，否则退出。

操作完后输出 $a$ 和 $b$ 的值。

**思路**

果断暴力啊，直接模拟就可以了。

**MAIN CODE**
```cpp
void dg(int a,int b){
	if(!a||!b){
		printf("%lld %lld\n",a,b);
		exit(0);
	}
	if(a>=(b<<1)) 
		dg(a-(b<<1),b);
	else if(b>=(a<<1))
		dg(a,b-(a<<1));
	else{
		printf("%lld %lld\n",a,b);
		exit(0);
	}
}
```

然后就 TLE 了，因为时间复杂度最坏有 $O(a)$。

$\therefore$ 要优化。

仔细观察操作 $2$，发现 $b$ 肯定不会突然变成 $0$，也就是说，如果 $a$ 比 $2b$ 大，不用按部就班地一直减，直接取模，然后返回第 $1$ 步就可以了。操作 $3$ 同理。这个时候时间复杂度是 $O(\log{a})$ 左右。~~鬼知道这个复杂度怎么算。~~

代码就不上了，主要是 $\because$ 把上面的代码的减操作改成模操作就行了。

---

