# [WFOI - 02] I wanna a feasitor（化验器）

## 题目背景

> 比赛时在做什么？有没有空？可以来开 longlong 吗？

kid 一脸疑惑地看着 Elgo87，Elgo87 说，通关就告诉你 ...

## 题目描述

kid 发现了一个函数 $f(x)$，它表示**除 $x$ 本身之外，$x$ 的最大约数**（$x$ 为大于 $1$ 正整数）。

下面是一些例子：

- $f(8)=4$，因为 $8$ 的约数有 $1,2,4,8$，除 $8$ 本身之外显然最大的约数为 $4$，所以 $f(8)=4$；
- $f(15)=5$，因为 $15$ 的约数有 $1,3,5,15$，除 $15$ 本身之外显然最大的约数为 $5$，所以 $f(15)=5$；

kid 还发现了两个数 $L,R$，你需要帮他求对于 $L\sim R$ 中的每一个数 $x$，$f(x)$ 的**最大值**，作为通关密码。

注意，$L\sim R$ 包括 $L$ 和 $R$。

你只需要告诉他答案，剩下的操作就交给 Elgo87 吧！

## 说明/提示

**【样例解释】**

在 $12\sim17$，也就是 $12,13,14,15,16,17$ 这几个数中，除这些数本身之外的最大因数分别是 $6,1,7,5,8,1$，故最大值为 $8$。

**【数据范围】**

**本题采用 $\tt Subtask$ 捆绑测试。** 即你需要通过一个 $\tt Subtask$ 中的所有测试点才能得到这部分的分数。

- $\texttt{Subtask \#0 (10pts)}$：$2\le L< R\le 100$；
- $\texttt{Subtask \#1 (30pts)}$：$2\le L< R\le10^4$；
- $\texttt{Subtask \#2 (30pts)}$：$2\le L < R\le 10^9$，$R-L\le 10^6$；
- $\texttt{Subtask \#3 (30pts)}$：$2\le L < R \le 10^{18}$。



## 样例 #1

### 输入

```
12 17```

### 输出

```
8```

# 题解

## 作者：Grisses (赞：66)

[题面](https://www.luogu.com.cn/problem/P8219)

### 结论：

答案为 $\dfrac{R}{2}$ 下取整。

### 证明：

- 若 $R$ 为偶数：

则毫无疑问答案直接为 $\dfrac{R}{2}$。

- 若 $R$ 为奇数：

最大因数最大能取 $\dfrac{R}{3}$。

而此时 $R-1$ 为偶，则有因数 $\dfrac{R-1}{2}$。

即需证：
$$\dfrac{R-1}{2}\geq\dfrac{R}{3}$$
即：
$$3R-3\geq 2R$$
即：
$$R\geq 3$$
因为 $2\le L<R\le 10^{18}$，所以 $R\geq 3$。

得证。

代码：
```cpp
  #include<bits/stdc++.h>
  using namespace std;
  long long l,r;//要开long long
  int main(){
      cin>>l>>r;
      cout<<r/2;
      return 0;
  }
```

---

## 作者：Ginger_he (赞：6)

本文同步更新于[博客园](https://www.cnblogs.com/Gingerhe/p/16027696.html)
# 题目描述
$f(x)$ 表示除 $x$ 本身之外，$x$ 的最大约数。给定 $L,R$，求 $\max\limits_{i=L}^R\{f(i)\}$。
# 题解
先感性理解，要让 $x$ 尽量大，并且让它除 $1$ 以外的最小约数尽量小，不难想到答案为 $[L,R]$ 中最大偶数的一半。  
若 $R$ 为偶数，显然。若 $R$ 为奇数，即证 $\dfrac{R-1}{2}\geqslant\dfrac{R}{3}$，等价于 $R\geqslant3$，刚好符合题目的数据范围，证毕。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll l,r;
int main()
{
	scanf("%lld%lld",&l,&r);
	printf("%lld\n",r>>1);
	return 0;
}
```

---

## 作者：wimg6_ (赞：6)

# P8219 题解

### 40 pts

暴力枚举。

首先从 $L$ 枚举到 $R$。

然后慢慢算最大约数。

### 100 pts

就是正解了。

通过观察，我们发现一些连续自然数中，最大因数一定是偶数的因数。

首先，我们知道，偶数一定能被 $2$ 整除。接着，我们设 $R \% 3=0$ 且 $R \%2 \neq0$。

故他们的最大约数分别为 $(R-1)\div 2$ 与 $R\div 3$。

假设 $(R-1)\div 2< R\div3$，

则 $3\times (R-1) < 2\times R$。

故 $3R-3 < 2R$。

即 $R< 3$。

我们再来翻一下测试数据：

由于 $2\leq L < R$

不合题意，证毕。

设 $R \%2=0$ 且 $(R-1) \% 3=0$，

假设 $R \div 2 \leq (R-1) \div 3$。

故 $3\times R\leq2\times R-2$。

即 $R\leq -2$。

负数？舍去！

又因为其余情况比以上情况劣，故得到如下结论

在 $L \sim R$ 区间内，最后一个与 $2$ 取模等于零的数，其 $f(x)$ 在此区间内的所有 $f(x)$ 中最大。

代码如下：

```
#include<bits/stdc++.h>
using namespace std;
long long s,l,r;
int main()
{
	scanf("%lld%lld",&l,&r);
	if(r%2==0) return !printf("%lld",r/2);
	else return !printf("%lld",(r-1)/2);
}
```


---

## 作者：苏联小渣 (赞：4)

怎样可以使区间里某个数除自己本身最大的约数最大呢？首先，我们希望那个数足够大，最好在 $R$ 附近；其次，约数要足够大，而偶数恰好能实现这一点。两者相结合，答案就明确了：取 $R$ 或 $R-1$（哪个是偶数就取哪个），然后把它除以 $2$ 即可。

可能会有一点疑惑：假如 $R$ 是奇数，那答案会不会由 $R$ 产生？如果这样，那最大的约数就是 $\frac{R}{p}$（$p \ge 3$），可以发现在给定数据范围内它必定会 $\le \frac{R-1}{2}$，然后就可以写出代码：

```cpp
#include <stdio.h>

long long l, r;
int main(){
	scanf ("%lld%lld", &l, &r);
	for (long long i=r; i>=l; i--){
		if (i % 2 == 0){
			printf ("%lld\n", i / 2);
			return 0;
		}
	}
	return 0;
}
```

C 语言比较好卡常，但还是卡不过 Pascal。

---

## 作者：Elgo87 (赞：4)

出题人题解，汲取了上次的经验，很良心的签到题，赛时被将近 $2000$ 人吊打，一血用时 $\text{51s}$。

$L\sim R$ 中对于每个数 $x$，可以从小到大看 $x\div f(x)$，$f(x)$ 最大时显然 $x$ 是个偶数，因为 $f(x)\not=x\div1$ 那就只能 $f(x)=x\div2$ 了。

然后从这些偶数里边取最大即可。

注意到出题人的良心数据范围 $L<R$，所以 $L\sim R$ 中一定有偶数，所以不需要添加任何特判。

参考代码 $1$：

```cpp
# include <bits/stdc++.h>
using namespace std;

int main() {
	long long a, b;
    cin >> a >> b;
    if (b % 2 == 0) cout << b / 2 ;
    else cout << (b - 1) / 2;
    return 0;
}
```

参考代码 $2$：

```cpp
#include<iostream>
main(){long long a,b;std::cin>>a>>b;std::cout<<b/2;}
```

---

## 作者：Engulf (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/P8219)

[更好的阅读体验](https://www.luogu.com.cn/blog/t-m-j-y-h-0-9/solution-p8219)

想要 $x\in[L,R]\ f(x)$ 最大，我们考虑贪心，不妨找 $x$ **最小**的非 $1$ 因数，显然可能最小的因数就是 $2$，这样 $x$ 和 $2$ 配对的因数 $\dfrac{x}{2}$ 就会是 $x$ 的最大因数。

显然 $x$ 越大，$\dfrac{x}{2}$ 就会越大，这样的话，我们找出离 $R$ 最近的偶数 $x$，答案就是 $\dfrac{x}{2}$。

---

## 作者：FFTotoro (赞：3)

分析题目后我们可以发现，一个数的最大因数会等于这个数除以除 $1$ 外的最小因数。

所以，一个数的最小因数（除 $1$ 外）越小，它的最大因数就越大；因数最小只可能是 $2$。

综上所述，如果 $r$ 是偶数，那么这个区间内的最大的 $f(x)$ 就是 $\frac{r}{2}$；否则最大值为 $\frac{r-1}{2}$。即答案为 $\left\lfloor\frac{r}{2}\right\rfloor$。

放代码：

```cpp
#include<iostream>
using namespace std;
int main(){
  long long l,r; cin>>l>>r;
  cout<<(r>>1)<<endl;
  return 0;
}
```

---

## 作者：cff_0102 (赞：2)

## P8219 [WFOI - 02] I wanna a feasitor（化验器） 题解

[原题](https://www.luogu.com.cn/problem/P8219)

### 题意：

输出 $L$ 和 $R$ 之间的数的最大真因子。

### 题解：

~~学过数学的都知道~~，一个数的最大真因子就是这个数除以它的最小质因数。最大真因子要越大，最小质因数也就要越小。最小的质数是 $2$，所以一定要选 $2$ 的倍数。

其次，这个数本身也要越大，所以要很接近 $R$。

所以，这个含有最大真因子的数就是小于等于 $R$ 的最大偶数，这个最大真因子也就是 $\lfloor\frac{R}{2}\rfloor$ 了。

题目里面提到了 $L<R$，不用特判 $L=R$ 的情况。

### 代码：

实际上没什么好放的，不过我还是放一下吧。

`Python`：

```python
a=input().split(" ")
b=int(a[1])#l没有用，因为要最大
print(b//2)
```

`C++`：

```cpp
int l,r;
cin>>l>>r//l没有用，因为要最大;
cout<<r/2;
```

~~其它语言的自己编~~。

希望管理能过，自己检索了一下空格应该没有问题。

---

## 作者：封禁用户 (赞：2)

#### 结论

答案为 $ r / 2 $ 

#### 证明

若 $ r $ 为偶数

则毫无疑问答案直接为 $ r / 2 $

若 $ r $ 为奇数

最大因数最大能取 $ r / 3 $

而此时 $ r - 1 $ 为偶

又因为 $ ( r - 1 ) / 2 \geq r / 3 $

则此时答案为 $ ( r - 1 ) / 2 $

因为 $ r $ 为奇数，所以答案还是为 $ r / 2 $

#### 代码

```
#include<bits/stdc++.h>
using namespace std;
int main(){
    long long l,r;//要开long long
    cin>>l>>r;
    cout<<r/2;
    return 0;
}

---

## 作者：charleshe (赞：1)

推式子题。

如果要让 $f(x)$ 最大，肯定优先选择除以二。

如果这个数不是二的倍数怎么办？很简单，让这个数减一成为二的倍数就行了。

考虑最不利情况，当 $l$，$r$ 取到最小值，即 $2$ 和 $3$ 时，此时 $f(x)$ 最大（当然也只能）为 $1$。容易发现，$1=(3-1) {\div} 2$，满足我们刚才推的式子。

因此答案即为 $\left \lfloor \dfrac{r}{2}  \right \rfloor$。

注意：

- 看清数据范围，此题要用长整型。

这些思考好了，代码就好写了。

```cpp
#include <iostream>
using namespace std;
int main(){
	long long r;
	cin>>r>>r;
	cout<<r/2;
	return 0;
}
```


---

## 作者：TheSky233 (赞：1)

# Description

定义 $f(x)$ 为除 $x$ 外，$x$ 的最大约数，求 $\max\limits_{L\leq i \leq R}f(i)$。

# Solution

首先，有结论 $f(x)=\dfrac{x}{k}$，其中 $k$ 是 $x$ 的不为 $1$ 的最小因数。

粗略证明一下：因为 $x$ 可被分解为两个因数的乘积，所以当 $k$ 最小时，$f(x)$ 最大。

------------


分情况讨论：

1. 当前的 $i$ 是偶数，则 $i$ 中必定有 $2$ 这个因数，而与之对应的最大因数则是 $\dfrac{i}{2}$。

2. 当前的 $i$ 是奇数，则它的最大因数必定小于 $\lfloor \dfrac{i}{2} \rfloor$，因为它的最小不为 $1$ 因数大于 $2$。

数据范围里有 $L < R$，即 $[L,R]$ 中必有一个偶数，所以只要输出其中最大偶数即可。

最后，注意题面：

> 比赛时在做什么？有没有空？可以来开 ```long long``` 吗？


本题即可 AC。

## Code
```cpp
#include <cstdio>
using namespace std;

long long l,r;

int main(){
	scanf("%lld%lld",&l,&r);
	if(r&1) printf("%lld",(r-1)>>1);//位运算卡常
	else printf("%lld",r>>1);
	return 0;
}

```

---

## 作者：duchengjun (赞：1)

# 题意

求 L 到 R 中 $f(x)$ 的最大值。

# 分析

我们从样例解释着手。

**【样例解释】**

在 $12\sim17$，也就是 $12,13,14,15,16,17$ 这几个数中，除这些数本身之外的最大因数分别是 $6,1,7,5,8,1$，故最大值为 $8$。

在样例解释中我们可以轻松地得出：

若 $x \bmod 2=1$,则 $f(x-1)<f(x)<f(x+1)$。

∵$(x+1) \bmod 2=0$

∴$f(x+1)=\frac{x+1}{2}$

则此题就是求最大的小于 R 的 2 的倍数的最大公约数，相当于求这个数的 $\frac{1}{2}$。

# Code

```cpp
#include<bits/stdc++.h>
#define int long long
#define For(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	return x*f;
}
int l,r;
signed main(){
	l=read(),r=read();
	if(r&1)printf("%lld",((r-1)>>1));
	else printf("%lld",(r>>1));
	return 0;
}

```


---

## 作者：3a51_ (赞：1)

不难发现答案一定是距离 $r$ 最近的且 $\le r$ 的数除以 $2$。下面给出证明：

首先假设最大的满足要求的数为 $k$，答案为 $\frac{k}{2}$。

如果存在一个数 $p>\frac{k}{2}$，那么 $x \times p>k+1$（此处 $x$ 为不是 $1$ 的正整数。）

所以此时 $x \times p$ 的最大质因数 $p$ 虽然大于 $k$，但是 $x \times p$ 已经超过了 $k+1$ 也就是 $r$（$k$ 可以是 $r$ 或 $r-1$），所以不满足。

证毕。

最后附上代码：

```cpp
/*
work by:Tothetime_tolife
time:1s
space:128MB
*/
#include<bits/stdc++.h>
#define int long long
#define Tothetime_tolife using
#define AK namespace
#define IOI std
Tothetime_tolife AK IOI;
int l,r;
signed main()
{
	//;;;;;
	cin>>l>>r;
	if(l==r && r%2==1) cout<<l;
	if(r%2==0) cout<<r/2;
	else cout<<(r-1)/2;
	return 0;
}
//QwQ

```


---

## 作者：Cure_Wing (赞：1)

### 题意
求 $\max\{f(x)\}(l\le x\le r)$。
### 解法
根据定义可得，要使 $x$ 的最大约数最大，就得使 $x$ 的最小非 1 约数最小，则这个数一定是 2，得到 $x$ 是偶数。又根据数据范围 $l<r$，可以得出这个区间内至少有 $2$ 个数，所以这里至少有一个偶数。最后得出结论：$\max\{f(x)\}(l\le x\le r)$ 应为 $[l,r]$ 中的最大偶数 $\div2$ 的结果。
### 代码
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,m;//不开long long见祖宗
int main(){
	scanf("%lld%lld",&n,&m);
	return !printf("%lld\n",m>>1);//当m是奇数时，由于long long类型会自动下取整，所以此时m>>1等同于m-1>>1
}
```
~~说白了和L有关系吗......~~

---

## 作者：Nygglatho (赞：1)

有一条性质，即如果 $x$ 是 $N$ 的因数，则 $\dfrac{N}{x}$ 也是 $N$ 的因数，我们可以从这条性质入手。

如果 $R$ 为偶数，那么 $R$ 除 $1$ 以外的最小因数为 $2$，除 $R$ 以外的最大因数为 $\dfrac{R}{2}$，其他的数字既比 $R$ 小，除 $1$ 以外的最小因数又大于等于 $2$，那么除该数字以外的最大因数就小于 $R$ 了，所以若 $R$ 为偶数，则答案为 $\dfrac{R}{2}$。

如果 $R$ 为奇数，则答案为 $\dfrac{R - 1}{2}$。

我们只需要证明 $\dfrac{R}{3} \le \dfrac{R - 1}{2}$ 即可。因为若 $3$ 是 $R$ 除 $1$ 以外的最小因数，那么 $R$ 的最大因数即为 $\dfrac{R}{3}$，若 $3$ 不是 $R$ 除 $1$ 以外的最小因数，那么由于 $2$ 不是 $R$ 的最小因数，最小因数（设为 $x$）必定大于 $3$，那么 $\dfrac{R}{x} < \dfrac{R}{3}$，一旦 $\dfrac{R}{3} \le \dfrac{R - 1}{2}$，那么 $\dfrac{R}{x}$ 也小于 $\dfrac{R - 1}{2}$ 了。

证明：

既然 $\dfrac{R}{3} \le \dfrac{R - 1}{2}$，将不等式两边同时乘以 $6$，可得：
$$2R \le 3R - 3$$
$$(3 - 1)R \le 3R - 3$$
$$3R - R \le 3R - 3$$
$$ -R \le -3$$

由于 $L \ge 2$，且 $R > L$，所以 $R \ge 3$。那么当 $R = 3$ 时，左边明显等于右边，成立；当 $R > 3$ 时，$-R < -3$ 明显也成立，所以答案为 $\dfrac{R - 1}{2}$。

Code:
```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
	long long l, r;
	cin >> l >> r;
	if (r & 1) cout << (r - 1ll) / 2ll;
	else cout << r / 2ll;
}
```

---

## 作者：ARGV (赞：1)

这一题，首先我们要考虑对于正整数 $a$ ，它不包含自己的最大因数是什么：

* 很容易想到，如果 $a$ 是偶数，那么答案就是 $\frac{a}{2}$ 。

* 如果 $a$ 是奇数，那么就把 $a-1$ ，这样  $a$ 就是偶数了 ，$\frac{a-1}{2}$ 满足这一题的要求。

于是就有了代码：
```cpp
#include <iostream>
using namespace std;

int main(){
    long long a,b;
    cin>>a>>b;
    cout<<b/2;
    return 0;
}
```
换种语言就得到了比赛期间的最短代码~~弱到不比成绩比这个qaq~~

Ruby：
```
a,b=gets.split.map(&:to_i)
puts b/2
```


---

## 作者：lsj2009 (赞：1)

## 题目大意
函数 $f(x)$ 代表 $x$ 的第二大约数。求
$\max\limits_{L\le x\le R}\{f(x)\}$
。
## 思路
如果 $x$ 是偶数的话，那么 $f(x)$ 无疑是 $\frac{x}{2}$。如果 $x$ 是奇数，那么 $f(x)$ 最大是 $\frac{x}{3}$，当然 $3$ 可能无法整除 $x$，那么这时 $f(x)$ 便是 $\frac{x}{\min\limits_{5\le k\le\infty}\{k\mid x\bmod k=0 \}}$ 了。

我们可以设计一个算法：

当 $R$ 为偶数时直接输出 $\frac{R}{2}$ 即可。

那么当 $R$ 为奇数呢？由于题目要求 $L<R$，所以 $R-1\ge L$，也就是对于 $[L,R)$ 这个区间里的最大的 $f(x)$ 是 $\frac{R-1}{2}=\frac{R}{2}-\frac{1}{2}$，而 $f(R)$ 最大是 $\frac{R}{3}$，而 $\frac{R-1}{2}\ge \frac{R}{3}$，所以当 $R$ 为奇数时，答案是 $\frac{R-1}{2}$。

值得一提的是，当 $R$ 为奇数时，$\frac{R-1}{2}=\lfloor\frac{R}{2}\rfloor$，而 ``int`` 自动向下取整。

所以直接输出 $\frac{R}{2}$ 即可。

---

## 作者：Lorkji (赞：1)

 - ### 题目要求
这题要求 $L$ 到 $R$ 之间的最大因子。


------------
 - ### 解法
因为最大因子 $=$ 本身 $/$ 最小因子。所以答案的形式一定是 $r / p $，是某个 $l - r$ 中数的因子，向下取整。而最小的素数是 $2$，所以答案就是 $r / 2$ 向下取整。   
 
 题目也提示了，一定要开 longlong 。不然后面的数据点会WA掉。
 另外要判断奇偶，这道题就好啦。
 

------------
 - ### Code
```c
#include <bits/stdc++.h>
using namespace std;
int main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	long long l,r;
	cin>>l>>r;
	if(r%2==0){
		cout<<r/2;
	}
	else{
		cout<<(r-1)/2;
	}
	return 0;
}
```

---

## 作者：hmzclimc (赞：0)

## 题意
原题传送门:

[Luogu P8219](https://www.luogu.com.cn/problem/P8219)

有一个函数 $f(x)$ ，它表示除 $x$ 本身之外， $x$ 的最大约数（ $x$ 为大于 $1$ 的正整数）。

给你两个数 $L$ ，$R$  ，求对于 $L\sim R$ 中的每一个数 $x$ ，$f(x)$  的最大值。

## 思路

首先， $x$ 为偶数时，它的除它自己以外的最大因数就是 $x/2$ ， 所以 $x/2$ 就是答案 。

那如果 $x$ 为奇数，它的除它自己以外的最大因数最大也就是 $x/3$ ，这是不如  $(x-1)/2$ 大的， 所以 $(x-1)/2$ 就是答案 。

因此我们只需要输出 $R-1$ 即可。
## 代码
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<string>
#include<iomanip>
using namespace std;
long long ans;
int main(){
    ios::sync_with_stdio(false);
    long long l,r;
    cin>>l>>r;
    cout<<r/2; // 代码没什么需要解释的吧
    return 0;
}
```

---

谢谢观看，本人是菜鸡，如发现有问题，请指出，谢谢。

---

## 作者：Lvyuze (赞：0)

我们都知道，一个数最大的约数是 $\frac{n}{2}$，此题就是让我们在这个区间内寻找最大的偶数，输出他的最大约数，即 $\frac{n}{2}$。

如果 $R$ 是偶数，答案就是 $\frac{R}{2}$；$R$ 如果是奇数，最大的偶数就是 $R-1$ ，答案就是 $\frac{R-1}{2}$，其实输出 $\frac{R}{2}$ 也没有关系，因为会给你向下舍入。

很简单了，上代码！

```cpp
#include<iostream>
using namespace std;
long long l,r;    //一定开 long long
int main()
{
    cin>>l>>r;
    cout<<r/2<<endl;
    /*
    也可以这样：
    if(r%2==0) cout<<r/2<<endl;
    else cout<<(r-1)/2<<endl;
    */
    return 0;
}
```


---

## 作者：hank0402 (赞：0)

### 题目大意：

定义 $f(x)$ 表示 $x$ 的不包含本身的最大约数，求 $i$ 在 $[L,R]$ 范围内最大的 $f(i)$.

### 题解：

因为下面 $L,R$ 的范围是 $10^{18}$. 所以我们要考虑 $O(1)$ 的解法。

进行分析，最大的 $f$ 肯定是由一个大的数除以一个小的数得到的，并且小的数不能是 $1$.

直接猜结论，因为 $2$ 是大于 $1$ 的正整数中最小的一个，并且考虑奇数和偶数的性质，在连续两个自然数中，一定一奇一偶，所以考虑这个范围内最大的两个数 $R$ 和 $R-1$，如果 $R$ 是偶数，那么 $f(R)=\frac{R}{2}$ 一定是最大的，反之，如果 $R$ 是奇数，那么 $R-1$ 一定是偶数，那么 $f(R-1)=\frac{R-1}{2}$ 一定是最大的，所以，当 $R$ 是偶数时，$\frac{R}{2}$ 就是答案，当 $R$ 是奇数时，$\frac{R-1}{2}$ 就是答案。

### 简易证明：

先证明第一个结论：当 $R$ 是偶数时，$\frac{R}{2}$ 就是答案。

因为 $R$ 是偶数，所以 $R-1$ 不可能是 $2$ 的倍数，那么若 $R-1$ 是 $3$ 的倍数，那么，$\frac{R-1}{3}<\frac{R-1}{2}<\frac{R}{2}$，并且 $\frac{R}{2}>\frac{X}{2}\ \ \ (X<R)$，综上，可得 $\frac{R}{2}>\frac{X}{a}\ \ \ (X<R\  \text{and}\ a\geq 2)$.  满足题目要求。

证明第二个结论：当 $R$ 是奇数时，$\frac{R-1}{2}$ 就是答案。

因为 $R$ 是奇数，所以 $R$ 不可能是 $2$ 的倍数，那么若 $R$ 是 $3$ 的倍数，那么，$\frac{R}{3}<\frac{R-1}{2}<\frac{R}{2}$，并且 $\frac{R-1}{2}>\frac{X}{2}\ \ \ (X<R-1)$，综上，可得 $\frac{R-1}{2}>\frac{X}{a}\ \ \ (X<R\  \text{and}\ a\geq 2)$ 且 $\frac{R}{3}<\frac{R-1}{2}$. 满足题目要求。

### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define debug(a, n)\
	printf(#a ":");\
	for(int i = 1; i <= n; ++i) cout << a[i] << ' ';\
	cout << '\n';
typedef long long ll;
ll l, r; 
int main() {
	scanf("%lld %lld", &l, &r);
	if(r % 2 == 0) printf("%lld", r / 2);
	else printf("%lld", (r - 1) / 2);
	return 0;
}

```

---

## 作者：哈士奇憨憨 (赞：0)

## 题意
求 $L∼R$ 中每个数 $x$，$f(x)$ 的最大值。其中 $f(x)$ 为除 $x$ 本身之外，$x$ 的最大约数。
## 思路
一个偶数 $x$，除 $x$ 本身之外，$x$ 的最大约数是 $\dfrac{x}{2}$，一个奇数 $x$，除 $x$ 本身之外，$x$ 的最大约数 $\le\dfrac{x}{3}$，所以，我们找到 $L∼R$里最大的偶数即可。
## CODE
```cpp
#include<bits/stdc++.h>
using namespace std;
long long l, r;
int main(){
    cin >> l >> r;
    r % 2 == 0 ? cout << r / 2 : cout << (r - 1) / 2;
    return 0;
}
```

---

## 作者：__a__ (赞：0)

# P8219 题解

## 思路

这道题是**数论**题。

我们首先要知道，如果两个数 $a$，$b$ 相乘的积为 $c$，那么 $a$ 和 $b$ 一定是 $c$ 的因数。

那么，我们要找一个数除了本身的**最大因数**，首先找到除了 $1$ 的**最小因数**。

怎样找到一个数的最小因数呢？我们先看**偶数**。偶数一定能被 $2$ 整除，$2$ 就是偶数除 $1$ 以外的最小因数。

我们要找 $L\sim R$ 中的**最大因数**，如果区间内有偶数，那么最大因数一定是 $\text{最大偶数}\div 2$。

那么**如果区间内没有偶数**怎么办？

注意看题目数据范围：

> $L<R$

也就是说，$L \sim R$ **至少有两个数**，再简化一下：$L \sim R$ **至少有一个偶数**！

那么，我们就不需要考虑“区间没有偶数”的情况了。

## 完整代码

```cpp
#include<cstdio>
int main()
{
	long long l,r;//别忘了开long long
    scanf("%lld%lld",&l,&r);
    printf("%lld",r/2);
	return 0;
}
```

---

## 作者：artofproblemsolving (赞：0)

题目分析：

拿到这道题的第一反应就是：从 $l$ 到 $r$ 一个个枚举 $x$，然后计算 $f(x)$，最后求出最小值。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
long long l,r,maxn;
long long f(long long x){
	for(long long i=2;i<=ceil(sqrt(x));i++)
		if(x%i==0) return x/i;
	return 1;
}
int main(){
	cin>>l>>r;
	for(long long i=l;i<=r;i++) maxn=max(f(i),maxn);
	cout<<maxn<<endl;
	return 0;
}
```
40分，超时了。

看一下数据范围：$2≤L<R≤10^{18}$，很明显过不去，怎么办呢？

我们来继续分析：

首先，对于 $x$，$f(x)$ 可能的最大值是多少呢？

很明显是 $\lfloor \frac{x}{2} \rfloor$。并且，当n为偶数时，$f(x)=\frac{x}{2}$。

那么，当 $r$ 为偶数时，直接取 $f(r)$ 即可。因为比 $r$ 小的数，其函数值不可能大于 $\frac{r}{2}$。

同理，当 $r$ 为奇数时，直接取 $f(r-1)$ 即可，也就是 $\frac{r-1}{2}$，可以表示为 $\lfloor \frac{r}{2} \rfloor$。
 
代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
long long l,r;
int main(){
	cin>>l>>r;
	cout<<r/2<<endl;
	return 0;
}
```


---

## 作者：ChenLingHan (赞：0)

题目中提到的是**最大约数**，一开始也把我给蒙住了，最大约数该怎么枚举？

如何解决这个问题呢，我们就开始思考最大约数是怎么产生的。

最大约数是怎么产生的呢？是因为**最小约数**而产生的啊！

有没有恍然大悟的感觉？

对于不同的数，它们的最大约数都不尽相同，但是它们的最小约数却有极大的概率是相同的（例如所有偶数的最小约数都是 $2$）！

**对于每一个有相同最小约数的数，这个数越大，那么这个数的最大约数也越大。**

举个例子：$2,4,6,8,10$ 最小约数都是 $2$，其中最大的数是 $10$ ，那么 $10$ 在这组数中的最大约数就最大！

现在我们将上述内容转换为代码就可以了：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	long long l,r;
	cin>>l>>r;
	for(long long k=2;;k++){
		for(long long i=r;i>=l;i--){
			if(i%k==0){ cout<<i/k; return 0; }
		}	
	}
} 
```
由于隔一个数就会出现偶数，所以本算法的时间复杂度是很可观的。

**注：本文所指的最大约数和最小约数均不包含本身和 $1$。**

---

## 作者：Galois_Field_1048576 (赞：0)

【题意描述】  
定义函数 $f(x) = \max\{d : (d \mid x) \wedge(d\ne x)\}$，求 $\max\limits_{i=l}^{r} f(i)$，保证 $l<r$。  


### Solution.

先说结论，$\text{ans} = \lfloor\frac r 2\rfloor$。  
证明：  
1. 显然，$\exists x \in [l,r] \cap \mathbb N (l<r), 2 | x$。  
2. 根据定义，若 $2 \mid x$ 则 $f(x) = \frac x 2$。  
3. 且根据定义，若 $2 \nmid x$ 则 $f(x) \lt \lfloor\frac x 2\rfloor$。
4. 根据 2., 3., $\max\limits_{i=l}^{r} f(i) = f(x) = \frac x 2$，其中 $x = \max\limits_{i\in[l,r] \wedge 2 \mid i} i$。  
  4.1. 反证法，若存在一个 $y \in [l,r]$ 使得 $f(y) \gt f(x)$：  
     - 若 $y < x$，则必然 $f(y) \le \lfloor\frac x 2\rfloor$（2., 3.），又因为 $f(x) = \frac x 2$，故 $f(y) \le f(x)$，矛盾。  
     - 若 $y \ge x + 2$，则 $2 \mid x + 2$ 且 $x + 2 \gt x$，与 $x = \max\limits_{i\in[l,r] \wedge 2 \mid i} i$ 矛盾。  
     - 若 $y = x$，显然 $f(y) = f(x)$，不成立。  
     - 若 $y = x + 1$，根据3.，$\lfloor\frac y2\rfloor = \frac x2$，故 $f(y) \lt f(x)$，矛盾。  


$\mathcal {Q.E.D.}$  

Code：
```cpp
#include<cstdio>
inline long long read(){
    long long x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return x*f;
}
int main()
{
    long long l = read(), r = read();
    printf("%lld", r/2);
}
```

时间复杂度 $\Theta(1)$。

---

## 作者：Tx_Lcy (赞：0)

## 题目分析
这道题目应该算是一道月赛中的送分题，题目让我们求区间 $L$ 到 $R$ 间的数的最大约数（除自己以外）。很显然，我们知道一个整数的最大约数是它自己，**若它是一个偶数，那么它的除本身以外的最大约数就是它自己除以二。**

那么我们就有一个很显然的思路。对于区间 $L∼R$，因为 $L$ 与 $R$ 不相等，所以此区间一定会有一个偶数。**若 $R$ 是偶数，则答案就是 $R$ 除本身以外的最大约数，即为 $\frac{R}{2}$，若 $R$ 是奇数，显然 $R-1$ 比 $R$ 更优，所以答案就是 $\frac{R-1}{2}$**

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	long long l,r;cin>>l>>r;
	cout<<r/2;
	return 0;
}
```


---

## 作者：_k_e_v_i_n_ (赞：0)

# 题目大意

给你 $L$ 和 $R$，让你求 $L$ 到 $R$ 之间 $f(x)$ 的最大值（$f(x)$ 题目说了是什么）。

# 思路

如果要求 $L$ 到 $R$ 之间 $f(x)$ 的最大值，这个数必须要大，但又不能是奇数（~~这就很烦了~~）。比如说，$f(4)$ 和 $f(6)$ 比较的话，$f(4)=2$，因为 $8$ 的约数有 $1,2, 4$，除 $4$ 本身之外显然最大的约数为 $2$，所以 $f(4)=2$；$f(6)=3$，因为 $6$ 的约数有 $1,2,3,6$，除 $6$ 本身之外显然最大的约数为 $3$，所以 $f(6)=3$。但是 $f(15)=5$,$f(14)=7$，$x$ 为偶数却大一些。

从上可以发现，$f(x)=x {\div} 2$,且 $x$ 是偶数。

既然 $x$ 要大，还要是偶数，$L$ 到 $R$ 之间最大的数显然是 $R$ ，如果 $R$ 是偶数，之间输出 $R {\div} 2$，否则输出 $(R-1) {\div} 2$。

# 附上 AC 代码

```
#include<bits/stdc++.h>
using namespace std;
long long l,r;	//记得开 long long，题目背景就有提示 
int main(){
	cin>>l>>r;
	if(r%2==0){	//如果 R 是偶数 
		cout<<r/2;
	}else{	//如果 R 是奇数 
		cout<<(r-1)/2;
	}
	return 0;
}

```


---

## 作者：sh7adow_ (赞：0)

## 简要题意
~~这题看似很难，其实这题只是披上了虚假的面纱。~~

给定 $a$ 和 $b$ ，让你求 $a\sim b$ 之间某个数的最大因数。
## 分析
众所周知，当 $b$ 越大时，它的最大因数也随之变大。所以我们要求最大的那个数的最大因数。**（即 $b$ 要尽量大）**

因为 $2$ 是**最小的共同因数**，所以当所有的数除以 $2$ 后，留下的因数最大：

e.g. （当共同因数为 $2$ 时）

- $8=2\times4$  最大因数为 $4$ 。
- $16=2\times8$ 最大因数为 $8$ 。
- $32=2\times16$ 最大因数为 $16$ 。

证明： $\dfrac{n}{2}\ge\dfrac{n+1}{3}(n\ge2)$ 即可。

> 在本题的求助贴中已有巨佬给出证明：偶数的最大因数是 $\dfrac{x}{2}$，而奇数的最大因数是 $\dfrac{x}{a},a\ne 1$ 且为奇数，表示奇数 $x$ 最小非1因数，题目保证 $l < r$ ，所以范围内一定有偶数，而 $\dfrac{x}{2}> \dfrac{x + 1}{a_{x+1}},\dfrac{x}{2} >\dfrac{x-1}{a_{x-1}}$ ，所以答案是 $\dfrac{r}{2}$ （r偶数） 或 $\dfrac{r-1}{2}$ ( $r$ 奇数)，即$r>>1$ 。

所以，我们不妨将所给的**偶数（假设）** $b$ 中删去一个因数 $2$ （即把符合要求的数除以  $2$ ），那么所剩下来的的因数就是我们要求的最大因数。但是， $b$ **不一定全是偶数**，所以当 $b$ 不是偶数时，把  $b$ 变为 $b-1$ 即可，还是相同操作。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    long long a,b;
    cin>>a>>b;
    if(b%2==0) cout<<b/2;//b为偶数
    else cout<<(b-1)/2;//b为奇数
    return 0;
}
```

完结撒花！

---

## 作者：Jorisy (赞：0)

这一题，我们可以换种思路。

首先，一个整数越大，那它的除本身外最大因子也**大多数**会越来越大。

同时，我们可以反过来——找该数的最小因子 $t$，然后输出 $i \div t$ 即可。

赛时 AC Code：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

int main()
{
	ll l,r,t=2;//不开 long long 见祖宗
	cin>>l>>r;
	do
	{
		for(ll i=r;i>=l;i--)//倒序
		{
			if(i%t==0)//找最小因子
			{
				cout<<i/t;//反过来输出最大因子
				return 0;
			}
		}
	}
	while(t++);//找不到 t 就加一
}
```
当然，事实上，只要用最大的偶数 $\div 2$（即 $r \div 2$）。

---

## 作者：Galex (赞：0)

## 题意
求 $l$ 到 $r$ 中所有数中除自己外的最大约数的最大值。

## 思路
经过思考，很明显发现最大值一定是其中最大的 $2$ 的倍数的最大约数。例如样例，答案就为 $f(16) = 8$。因此，只需特判一下 $r$ 是不是 $2$ 的倍数即可。若是就输出 $\frac{r}{2}$，否则输出 $\frac{r-1}{2}$ （因为若 $r$ 不是 $2$ 的倍数则 $r - 1$ 一定是 $2$ 的倍数）。

**记得开 `long long` ！！！**

## $Code$ 

```cpp
#include <cstdio>

long long read(){//快读
	long long s = 0, f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9'){
		if (ch == '-')
			f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
		s = (s << 1) + (s << 3) + (ch ^ 48), ch = getchar();
	return s * f;
}


int main(){
	long long l = read(), r = read();
	if (r % 2 == 0)//判断r是不是2的倍数
		printf("%lld", r / 2);//输出r/2
	else
		printf("%lld", (r - 1) / 2);//否则输出(r-1)/2
	return 0;
} 
```


---

## 作者：DengDuck (赞：0)

对于一个数字 $x$ ,除自身的最大因数一定是 $\frac x 2$ 

当然，前提是 $x$ 为偶数，否则无法整除

同时， $\frac x 2$ 满足单调性， $x$ 增大只可能让 $\frac x 2$ 增大

所以答案应该是最大偶数除二，简单理解成 $\lfloor \frac x 2 \rfloor$

```cpp
#include<bits/stdc++.h>
using namespace std;
long long s,t;
int main(){
    cin>>s>>t;
    cout<<t/2;
}
```

---

## 作者：Firstly (赞：0)

这是一道数学思维题。

## **题目思路：**

$f(x)$ 表示除 $x$ 本身之外的最大约数，这个约数可以看做是 $x$ 除以它的另一个约数。要想让 $f(x)$ 最大，就要让另一约数最小。

很容易发现，当 $x$ 为偶数时，它的最小约数就是 $2$，所以它的最大约数就是 $\frac{x}{2}$。当 $x$ 为奇数时，我们应当枚举求出。

但是题目中的数据范围告诉我们，$L<R$，所以在这个范围中，一定有一个偶数。不难证明，$2$ 以上的任一奇数 $x$，$f(x)<f(x-1)$。

所以我们分类讨论即可：当 $R$ 为偶数，输出 $\frac{R}{2}$，否则输出 $\frac{R-1}{2}$。但由于语言特性，直接输出整数类型的 $\frac{R}{2} $ 即可。

## **Code：**

```cpp
#include<cstdio>
int main(){
    long long l,r;
    scanf("%lld%lld",&l,&r);
    printf("%lld",r/2);
    return 0;
}
```


---

## 作者：sgl654321 (赞：0)

### 题意描述
- 定义用 $f(x)$ 表示 $x$ 最大的非本身的因数。
- 给定两个数 $L$ 和 $R$，求出对于 $[L,R]$ 中每一个数 $x$，$f(x)$ 的最大值。

### 解题思路
**40 分做法**：

遍历 $[L,R]$ 中的每一个数 $x$，分别求出 $f(x)$，最后输出最大值。不展示代码。

**满分做法**：

看数据规模，$L$ 和 $R$ 都到了 $10^{18}$ 级别，毫无疑问是 $O(1)$ 做法。

思考： $[L,R]$ 中，肯定至少有一个数是偶数。一个偶数 $x$ 的最大非本身因数，即 $f(x)$，就是 $\dfrac{x}{2}$。

若 $R$ 为偶数，则一定输出 $\dfrac{R}{2}$。

若 $R$ 为奇数，则 $R$ 最大可能的非本身的因数是 $\dfrac{R}{3}$，又因为当 $R \ge 3$ 时，都有 $\dfrac{R-1}{2}\ge \dfrac{R}{3}$。题目中已经给定 $2 \le L<R$，说明 $R\ge 3$。所以，应该输出 $\dfrac{R-1}{2}$。

综合上述，可以得到：
- 若 $R$ 为偶数，则输出 $\dfrac{R}{2}$。

- 若 $R$ 为奇数，则输出 $\dfrac{R-1}{2}$。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long l,r;
int main(){
	cin>>l>>r;
	if(r%2==1)cout<<(r-1)/2<<endl;
	else cout<<r/2<<endl;
	return 0;
}
```

不开 long long 见祖宗。

---

## 作者：HappyCode (赞：0)

### 思路
#### 40 分
枚举 $L$ 到 $R$ 之间的每个 $f(x)$ 的值，用“打擂台法”求出最大值。  
注：“打擂台法”指如果当前值大于最大值，那么当前值就是最大值。详细解释请参考《深入浅出程序设计竞赛 - 基础篇》语言入门部分。
#### 100 分
当 $x$ 是偶数时， $f(x)$ 为 $x \div 2$。那 $x$ 是奇数时呢？答案是：不管它！$x$ 是奇数时，$f(x)$ 至少为 $x \div 3$，比 $x$ 是偶数时大。因此答案是 $\lfloor x \div 2 \rfloor$，C++ 中整数除法有自动向下取整的功能，因此只需输出 $R \div 2$ 即可。

### 提醒
比赛时在做什么？有没有空？可以来 **开 long long** 吗？

### 代码
```cpp
#include<iostream>
using namespace std;
long long l,r; //开 long long
int main(){
    cin>>l>>r;
    cout<<r/2<<endl;
    return 0;
}
```

---

