# GCD vs LCM

## 题目描述

本题有多测。  
给定一个正整数 $n$，求一组正整数 $a$, $b$, $c$, $d$，使得 $a+b+c+d=n$，并且 $\gcd(a,b) = \operatorname{lcm}(c,d)$。本题有 SPJ，求出任意一组即可。

## 说明/提示

$4\le n\le 10^9$  
$1\le t\le 10^4$

## 样例 #1

### 输入

```
5
4
7
8
9
10```

### 输出

```
1 1 1 1
2 2 2 1
2 2 2 2
2 4 2 1
3 5 1 1```

# 题解

## 作者：Dream_weavers (赞：6)

## 题意

给出 $n$，找出正整数 $a,b,c,d$ 且满足以下条件：

- $a+b+c+d=n$

- $\gcd(a,b)=\text{lcm}(c,d)$

$\gcd$ 指求两数的**最大公约数**，$\text{lcm}$ 指求两数的**最小公倍数**，找出一组解即可。

## 思路

这里借鉴一下@lsj2009 的思路，有一些不同。[ta已经同意借鉴了](https://www.luogu.com.cn/paste/8os9tyl8)。

设 $\gcd(a,b)=\text{lcm}(c,d)=1$，这样会更容易找出四个数的值。

当 $\text{lcm}(c,d)=1$，则 $c=1,d=1$。

当 $\gcd(a,b)=1$，让两数互质即可。设 $a=1$，那一共出现了三个 $1$，则 $b=n-3$。其实让 $a$ 和 $b$ 相邻也可以，但要特判一下奇偶性。

## 代码

python版

```python
t=int(input())
for i in range(t):
    n=int(input())
    print("1 "+str(n-3)+" 1 1")

```

------------

c++版

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n; 
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		printf("1 %d 1 1\n",n-3);
	}
    return 0;
}

```

---

## 作者：xzyg (赞：3)

## 题意简述

给定一正整数 $ n $，试求出正整数 $ a,b,c,d $ 的值，其中 $ a + b + c + d =n,\gcd(a,b) = \operatorname{lcm}(c,d) $。

## Sol:

对于任意正整数 $n$，有如下性质：

性质 1：$ \gcd(1,n) = 1 $。

性质 2：$ \operatorname{lcm}(1,n) = n $

令第二个约束等式两边都等于 1，即 $ \gcd(a,b) = \operatorname{lcm}(c,d) = 1 $。

根据上面的性质，~~不难~~推出有一组解为 $a = 1,b = n-3,c = 1,d = 1$。

（$a = n-3,b = 1,c = 1,d = 1$ 也可以）

对于每组数据输出即可。

### 代码

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath> 
#define ll long long

using namespace std;

int main(){
	ll t;
	cin >> t;
	for(ll i = 1; i <= t; i++){
		ll n;
		cin >> n;
		cout << 1 << " " << n-3 << " " << 1 << " " << 1 << endl;
	}
	return 0;
}
```


---

## 作者：Shimotsuki (赞：3)

[传送门 to 洛谷](https://www.luogu.com.cn/problem/CF1665A)

[传送门 to CF](https://codeforces.com/contest/1665/problem/A)

题意：给定数 $n$，求四个数 $a$，$b$，$c$，$d$，使得 $a+b+c+d=n$，并且 $\gcd(a,b)= \operatorname{lcm}(c,d)$。输出任意合法的一组解。

思路：考虑让两边都为 $1$，则 $a$ 与 $b$ 要互质，$c$ 与 $d$ 要都为 $1$。为了让 $a$ 和 $b$ 互质，可以令 $b$ 为 $1$。这样即可解决问题。

$Code$
```cpp
#include<cstdio>

using namespace std;

int main(){
	int t,n;
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		int a=n-3;
		printf("%d 1 1 1\n",a);
	}
	return 0;
} 
```


---

## 作者：CmsMartin (赞：1)

## 题目描述

[题目传送门](http://codeforces.com/problemset/problem/1665/A)

## 思路

智障题。。。考场瞬切。

显然可以构造 $a = 1 , b = n-3 , c = 1 , d = 1$。

此时 $\gcd(a,b) = \operatorname{lcm}(c,d) = 1$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int T , N;

int main() {
    scanf("%d" ,&T);
    while(T--) {
        scanf("%d" ,&N);
        printf("%d %d %d %d\n" ,1 , N - 3 , 1 , 1);
    }
    return 0;
}
```

---

## 作者：miao5 (赞：1)

**题意：**

给定一个正整数 $n$，求出 $4$ 个正整数 $a,b,c,d$ 满足 $a+b+c+d=n$ 并且 $\gcd(a,b)=\text{lcm}(c,d)$。

$t$ 组数据。

**思路:**


首先考虑 $\gcd$ 和 $\text{lcm}$ 的性质：任意一个数和 $1$ 的 $\gcd$ 都是 $1$，一个数和另一个与它相等的数的 $\text{lcm}$ 等于这个数本身。

于是可以轻易的得到一个结论：$\gcd(n-3,1)=1,\text{lcm}(1,1)=1$，所以 $\gcd(n-3,1)=\text{lcm}(1,1)$，而 $n-3+1+1+1=n$，所以直接输出 $n-3,1,1,1$ 即可。

```cpp
#include<iostream>
using namespace std;
int main(){
	int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		cout<<n-3<<' '<<1<<' '<<1<<' '<<1<<endl;
	}
}
```

---

## 作者：zhicheng (赞：1)

### 分析

先拿到这个题，没有什么思路，不妨从特殊情况入手。而最特殊的情况就是 $ \operatorname{lcm}(c,d) =1$，即 $c=d=1$ 的时候。

发现这时 $ \gcd(a,b) $ 也应等于 $1$，表明 $a$、$b$ 互质。而最特殊的情况即为 $a=1$ 或 $b=1$ 时。

然后，就没有然后了。。。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,a;
	scanf("%d",&n);
	while(n--){
		scanf("%d",&a);
		printf("1 %d 1 1\n",a-3); //a,c,d 均为1，那么 b 就是 a-3。
	}
}
```

---

## 作者：Polaris_Australis_ (赞：1)

[传送门](https://www.luogu.com.cn/problem/CF1665A)

## 题意
多组数据，每组给定一个数 $n$ ，输出一组数 $a,b,c,d$ ，使得 $gcd(a,b)=lcm(c,d)$ 。
## 解法
这是一道构造题（如果不构造可能真的不是很简单），只需要让 $a=n-3\texttt{ },\texttt{ }b=c=d=1$ 即可，这样 $gcd(a,b)=lcm(c,d)=1$ 。
## 代码
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
namespace Std
{
    template<typename tp>
    void read(tp &x)
    {
        x=0;
        tp nev=1;
        char c=getchar();
        while(c<'0'||c>'9')
        {
            if(c=='-')nev=-1;
            c=getchar();
        }
        while(c>='0'&&c<='9')
        {
            x=(x<<1)+(x<<3)+(c&15);
            c=getchar();
        }
        x*=nev;
    }
    template<typename tp>
    void write(tp x)
    {
        if(x<0)
        {
            putchar('-');
            write(-x);
            return;
        }
        if(x/10)write(x/10);
        putchar((x%10)|48);
    }
    int n,t;
    int main()
    {
        read(t);
        while(t--)
        {
            read(n);
            printf("%d 1 1 1\n",n-3);
        }
        return 0;
    }
}
int main()
{
    return Std::main();
}
```


---

## 作者：EtHereal_Algorithm (赞：1)

## CF1665A GCD vs LCM
给出一个清奇构造。

### 0.题意
对于一个方程组

$\begin{cases}a+b+c+d=n\\\gcd(a,b)=\text{lcm}(c,d)\end{cases}$

其中 $n$ 已经给定。输出任意解。
### 1.思路
我的思路很奇怪，可能是被样例误导到了。

* 对于 $n\bmod2=1$，答案为 $(a,b,c,d)=(n-5,2,2,1)$ 总是正确的。

原因很简单，$n-5$ 常为偶数，那么 $\gcd(a,b)=2=\text{lcm}(1,2)$

* 对于 $n\bmod4=2$，答案为 $(a,b,c,d)=(\dfrac{n-2}{2}-1,\dfrac{n-2}{2}+1,1,1)$

原因更简单，对于两个相邻的奇数他们一定互质。

* 对于 $4|n$，答案为 $(a,b,c,d)=(n-6,2,2,2)$

显然，$\gcd(n-6,2)=2=\text{lcm}(2,2)$。

* 特别的，对于 $4$ 我们的答案是 $1,1,1,1$（我特判了）

* 对于 $5$ 我们的答案是 $2,1,1,1$（我特判了）。

不知道这个思路您们喜不喜欢，但是确实容易从样例中得到。这也是 `CF` 构造题中会用到的简单技巧。（？）
### 2.代码
```cpp
#include <bits/stdc++.h>

//standard

#define up(i,l,r) for(int i=(l);i<=(r);i++)
#define down(i,r,l) for(int i=(r);i>=(l);i--)
typedef long long ll;
using namespace std;

//quick in / out

#define int ll
inline int readl(){
    int f = 1, x = 0;
	char ch;
    do{ch = getchar();if(ch == '-')f = -1;}while(ch < '0' || ch > '9');
    do{x = x * 10 + ch - '0';ch = getchar();}while(ch >= '0' && ch <= '9');
    return f * x;
}
void printl(int x){
	if(x > 9) printl(x / 10);
	putchar(x % 10 + '0');
}
#undef int
inline int read(){
    int f = 1, x = 0;
	char ch;
    do{ch = getchar();if(ch == '-')f = -1;}while(ch < '0' || ch > '9');
    do{x = x * 10 + ch - '0';ch = getchar();}while(ch >= '0' && ch <= '9');
    return f * x;
}
void print(int x){
	if(x > 9) print(x / 10);
	putchar(x % 10 + '0');
}

//main function

int main() {
	int T = read();
	while(T--)
	{
		int n = read();
		if(n == 4) {puts("1 1 1 1"); continue;}
		if(n == 5) {puts("2 1 1 1"); continue;}
		if(n % 4 == 2)
		{
			printf("%d %d %d %d\n", (n - 2) / 2 - 1, (n - 2) / 2 + 1, 1, 1);
			continue;
  		}
  		if(n % 2 == 1)
  		{
		  	printf("%d %d %d %d\n", 2, (n - 5), 2, 1);
		  	continue;
		}
		if(n % 4 == 0)
		{
			printf("%d %d %d %d\n", 2, (n - 6), 2, 2);
			continue;
		}
	}
	return 0;
}
```

---

## 作者：0xFF (赞：1)

#### 题目大意


------------
给定一个整数 $n$，求出满足条件的四个数 $a,b,c,d$ 满足 $a+b+c+d=n$ 同时 $\gcd(a, b) = \operatorname{lcm}(c, d)$。输出 $a,b,c,d$。

#### 思路分析


------------
首先考虑当 $n$ 是 $4$ 的倍数是，直接令 $a,b,,c,d$ 都等于 $\frac{n}{4}$ 即可。

如果 $n$ 是一个奇数，考虑构造 $\gcd(a, b) = \operatorname{lcm}(c, d) = 1$，只需要令 $c=d=1$ 同时令 $a=\left \lfloor \frac{n-2}{2} \right \rfloor,b=\left \lceil \frac{n-2}{2}  \right \rceil $ 即课满足题设。

另外的情况就是 $n$ 能整除 $2$ 却不能整除 $4$。同样考虑构造 $\gcd(a, b) = \operatorname{lcm}(c, d) = 1$，还是令 $c=d=1$，因为相邻的两个奇数最大公因数必然是 $1$，所以构造 $a=\frac{n-2}{2}-1,b=\frac{n-2}{2}+1$ 即可满足题设。

#### 代码实现


------------
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<cstdlib>

using namespace std;
const int N = 10010;

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    for(;!isdigit(ch);ch=getchar()) if(ch=='-') f=-1;
    for(; isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+ch-'0';
    return x*f;
}

int main(){
	int T = read();
	while(T--){
		int n = read();
		if(n % 2 == 1){
			printf("%d %d 1 1\n",(n-2)/2,(n-2)/2+1);
		}
		else{
			if(n % 4 != 0){
				printf("%d %d 1 1\n",(n-2)/2-1,(n-2)/2+1);
			}
			else{
				int ans = n/4;
				printf("%d %d %d %d\n",ans,ans,ans,ans);
			}
		}		
	}

	return 0;
}
```


---

## 作者：panyanppyy (赞：1)

CF 简单的构造题，难度在 $\color{orange}\texttt{普及-}$ 到 $\color{red}\texttt{入门}$ 左右。
## Problem
输入一个 $n\le10^9$ 求出一个四元组 $a,b,c,d$ 满足：
1. $a+b+c+d=n$
2. $\gcd(a,b)=\operatorname{lcm}(c,d)$

## Solution

可以想到一种简单的构造方法，使 $\gcd(a,b)=\operatorname{lcm}(c,d)=1$。

* 使 $\gcd(a,b)=1$，$a,b$ 互质即可。

	**赛时做法**：如果 $a+b$ 为奇，输出 $2,a+b-2$ 奇数显然和 $2$ 互质；否则输出 $1,a+b-1$。

   **更简单的做法**：再仔细思考一下，当 $a+b$ 为奇时，$1,a+b-1$ 还是互质的，就不用分类谈论了。
* 使 $\operatorname{lcm}(c,d)=1\longrightarrow c=d=1$ 即可。

所以最终答案就是 $n-3,1,1,1$。

Code
```cpp
#include<bits/stdc++.h>
#define ll long long
#define ri register
using namespace std;
int T,n;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
//		if(n&1)printf("%d 2 1 1\n",n-4);赛时脑血栓做法
/*		else*/printf("%d 1 1 1\n",n-3);
	}
	return 0;
}
```

---

## 作者：tZEROちゃん (赞：1)

> 给你一个正整数 $n$，试找出 $4$ 个正整数 $a, b, c, d$，使得：
>
> - $a+b+c+d = n$
> - $\gcd(a,b) = \operatorname{lcm}(c,d)$
>
> 若有多个答案，输出任意一个。

考虑让 $\gcd(a,b)$ 和 $\operatorname{lcm}(c,d)$ 都等于 $1$，此时 $c, d$ 显然都为 $1$，而我们要让两个正整数的 $\gcd = 1$，那么至少有一个是 $1$，另一个取任意值，所以我们可以让 $a = n - 3, b = 1$，于是就做完了。

**Pascal**
```pascal
var i, n, t: longint;
begin
  read(t);
  for i := 1 to t do
  begin
    read(n);
    writeln(n - 3, ' ', 1, ' ', 1, ' ', 1);
  end;
end.
```

**C++**
```cpp
#include<bits/stdc++.h>
using namespace std;

void solve() {
  int n;
  cin >> n;
  printf("%d %d %d %d", n - 3, 1, 1, 1);
  putchar('\n');
}

int main(){
  int _; cin >> _; while (_--) {
    solve();
  }
  return 0;
}
```

---

## 作者：力巴尔 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1665A)

### 题目大意：

$t$ 组数据，每组数据给出一个正整数 $n$，你需要输出四个正整数 $a$，$b$，$c$，$d$，使 $a + b + c + d = n$ 且$gcd(a, b) = lcm(c, d)$，输出任意一种情况即可。

### 思路：

这道题只需要输出一种情况，而且题目中说 $n$ 至少为 $4$，所以我们可以让 $b = c = d = 1$，$a = n - 3$，这样 $gcd(a, b)$ 和 $lcm(c, d)$ 就都等于 $1$，且 $a + b + c + d = n$，所以直接输出这四个数即可。

### 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int t;
    cin>>t;
    while (t--)
    {
        int n;
        cin>>n;
        printf("%d 1 1 1\n", n - 3);
    }
}
```


---

## 作者：Catium (赞：1)

# CF1665A GCD vs LCM

算是一道数论题吧，赛时就写了这个就睡觉了(

## 题目描述：

给定正整数 $n$ ，让你求出四个正整数 $a,b,c,d$ ，使得  $a+b+c+d=n$，并且 $\gcd(a,b) = \operatorname{lcm}(c,d)$ 。

输出任意一组解即可

有个结论，最小公倍数 $\operatorname{lcm}(i,j) =\gcd(i,j)*i*j$  。

## Solution

观察数据范围，发现 $n$ 和测试组数 $t$ 都是巨大的，并且任意一组解均可。

首先我们考虑朴素方法，暴力的去找这四个数字，那么我们枚举 $a,b,c,d$ 就行了(

不难发现我们可以省去一个 $d$ 的枚举，因为显然 $d=n-a-b-c$ 

这种枚举复杂度是 $n^3$ 的(大概),至于`gcd`的实现我们可以直接用`<algorithm>`里面的`__gcd(int i,int j)`，这个内部实现就是[辗转相除法](https://baike.baidu.com/item/%E6%AC%A7%E5%87%A0%E9%87%8C%E5%BE%97%E7%AE%97%E6%B3%95/1647675?fromtitle=%E8%BE%97%E8%BD%AC%E7%9B%B8%E9%99%A4&fromid=10667326&fr=aladdin)。

```c++
for(int a = 1;a < n;a++){
    for(int b = 1;b + a < n;b++){
        for(int c = 1;c + b + a < n;c++){
            int d = n - a - b - c;
            if(gcd(a,b) == lcm(c,d)){
                cout<<a<<" "<<b<<" "<<c<<" "<<d<<endl;
                goto end;
                //有解立刻跳出
            }
        }
    }
}
end:{};
```

即使加上各种优化，这种暴力枚举也肯定会被 $10^9$ 的数据干爆

那么，**正难则反**，我们看到这个巨大数据范围，自然会想有没有什么 $O(1)$ 算法或者结论。

经过一些思考，我们发现**两个数的最大公约数和最小公倍数都不好确定，除非其中有一个数是固定的**。

那我们就固定一个数呗，反正只要保证四个数和为 $n$ 就行啦。

然后我们再想，一个数固定了之后还是不好确定 $gcd$ 和 $lcm$ 的，但是可以有特殊情况：

> $\gcd(1,i) = 1,i \in N*$

这个非常牛逼的数，**1 可以把 $gcd$ 确定下来**。

但是这还不够，我们还需要让 $\gcd(a,b)=\operatorname{lcm}(c,d)$ 成立。

我们既然已经确定了 $\gcd(a,b) = 1$ ，那我们直接**强制 $\operatorname{lcm}(c,d) = 1$ 不就完了**(

于是我们考虑 $\operatorname{lcm}(1,i) = i , i \in N*$ ，从而发现 $\operatorname{lcm}(1,1) = 1$ （废话）

那么结论就得出来啦，我们只需要使 $a =n-3 ,b=1,c=1,d=1$ 即可，一定是一组满足条件的解。

容易发现，$n<4$ 时无解，但是题目保证有解所以就不管啦。

代码难度入门，就不放了（逃

---

## 作者：Failure_Terminator (赞：1)

## Problem

给定一个整数 $n$，求整数组 $(a,b,c,d)$，满足 $a+b+c+d=n$，且 $\gcd(a, b)$ = $\operatorname{lcm}(c, d)$。

这里的 $gcd$ 指的是[最大公约数](https://baike.so.com/doc/5399827-5637381.html)，而 $lcm$ 指的是[最小公倍数](https://baike.so.com/doc/5390805-5627461.html)。

结果可能有多种，输出任意一种即可。

## Solution

实际上此题只要使 $\gcd(a, b)$ = $\operatorname{lcm}(c, d)$ = $1$。

办法很简单。

因为对于任意正整数 $n$， $\gcd(n, 1)$ = $1$，因此可以使 $b$，$c$，$d$ 都为 $1$，$a$ 为 $n-3$，这在 $n$ $\ge$ $4$ 时都满足要求。

核心代码（1行）

	printf("%d 1 1 1\n",n-3);
    
完整 AC 代码放在剪贴板里。

[AC Code](https://www.luogu.com.cn/paste/laruqx0e)

### By **haimo**

---

## 作者：hmzclimc (赞：0)

## 题意
原题传送门:

[Luogu](https://www.luogu.com.cn/problem/CF1665A)

[Codeforces](http://codeforces.com/problemset/problem/1665/A)

给定一个正整数 $n$，求一组正整数 $a$,$b$,$c$,$d$，使得 $a+b+c+d=n$，并且 $ \gcd(a,b) = \operatorname{lcm}(c,d)$。
## 思路
这道题有一个神奇的做法：

题目不是要求 $ \gcd(a,b) = \operatorname{lcm}(c,d)$ 吗，那我们就让他们都等于 $1$。

众所周知，任何正整数都是 $1$ 的倍数，因此 $1$ 与任何正整数的最大公因数是 $1$。

同时，$1$ 和任何正整数的最小公倍数就是这个数。

那么我们就让 $a=n-3,b=1,c=1,d=1$，这样就能完美满足条件了。
## 代码
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<string>
#include<iomanip>
using namespace std;
int t;
int main(){
    ios::sync_with_stdio(false);
    cin>>t;
    while(t-->0){
        int n;
        cin>>n; // 代码内容非常简单因此没什么可说的了
        cout<<n-3<<" "<<1<<" "<<1<<" "<<1<<'\n';
    }
    return 0;
}
```

---

谢谢观看，本人是菜鸡，如发现有问题，请指出，谢谢。

---

## 作者：FiraCode (赞：0)

[【题目链接】](https://www.luogu.com.cn/problem/CF1665A)
## 题意：
给你 $t$ 个整数，让我们求四个数 $a,b,c,d$，并且 $a + b + c + d = n$ 并且 $\gcd(a , b)$ $= \operatorname{lcm(c , d)}$。

## 题解思路：
我们先输出一个 $n - 3$，然后再输 $3$ 个 $1$，即可，因为 $n - 3 + 1 + 1 + 1 = n - 3 + 3 = n$。

在来看后面的满足，后面要求 $\gcd (a , b) = \lcm (c , d)$，那么由于任何一个数都是 $1$ 的倍数，所以 $\gcd(a , b)$ 一定等于 $1$。

而两个 $1$ 的最小公倍数就是 $1$，$1 = 1$ 所以这种方法可行。

## AC Code:
```
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
int T;
int main() {
	cin >> T;
	while (T --) {
		int n;
		cin >> n;
		cout << n - 3 << ' ';//先输出一个n-1
		for (int i = 1; i <= 3; ++ i)
			cout << 1 << ' ';//再输出3个1
		cout << endl;
	}
	return 0;
}
```

---

## 作者：_xxy_ (赞：0)

一道简单的构造题

当我们看到构造任意一组 $ a,b,c,d $ 使 $ a+b+c+d=n $ 且 $ n \ge 4 $ 时，马上可以想到构造 $ 1,1,1,n-3 $ ，要满足 $ gcd(a,b)=lcm(c,d) $ ，只需调换顺序输出 $ n-3,1,1,1 $ 即可。

```cpp
#include<iostream>
using namespace std;
int main(){
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        cout<<n-3<<" "<<"1 "<<"1 "<<"1 "<<endl;
    }
    return 0;
}
```

---

## 作者：happy_dengziyue (赞：0)

### 1 思路

我们可以发现，如果让 $\operatorname{gcd}(a,b)=\operatorname{lcm}(c,d)=1$，那么会好处理地多。

我们可以发现，当且仅当 $c=d=1$ 时，$\operatorname{lcm}(c,d)=1$。同时，当 $a$ 和 $b$ 中存在一个为 $1$，那么 $\operatorname{gcd}(a,b)=1$。

那么我们就可以得出结论：输出 $n-3,1,1,1$ 必定满足要求。

### 2 代码与记录

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
int t;
int n;
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1665A_1.in","r",stdin);
	freopen("CF1665A_1.out","w",stdout);
	#endif
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		printf("%d %d %d %d\n",n-3,1,1,1);
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/73510226)

By **dengziyue**

---

## 作者：落花月朦胧 (赞：0)

## 题意

给出一个数 $n$, 求一组解 $a, b, c, d$, 使 $\gcd(a, b) = lcm(c, d)$。

## 解

可以想到让 $a$ 是 $b$ 的因数， $c$ 为 $d$ 的倍数，只需要让 $a =c$ 就可以解决。

不妨设 $d$ 是 1， $c$ 只有为 1 是才可以满足条件， 相同的，再设 $a$ 是 1， $b$ 无论取那个数都可以满足条件。 又因为和为 $n$， 所以最后的答案就是 $1, n - 3, 1, 1$。

```cpp
#include <bits/stdc++.h>

using i64 = long long;

void solve() {
	int n;
	std::cin >> n;
	std::cout << 1 << " " << (n - 3) << " " << 1 << " " << 1 << "\n";
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	
	int T;
	std::cin >> T;
	while (T--) {
		solve();
	}

	return 0;
}


```

---

## 作者：ForeverCC (赞：0)

我们可以找一个普遍的情况。

因为 $gcd(x,1)=1$，$lcm(1,1)=1$。

所以只要使 $gcd(a,b)=lcm(c,d)$ 等于 $1$ 即可。

其中 $a,b,c,d$ 分别为 $n-3,1,1,1$。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,t;
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		printf("%d %d %d %d\n",n-3,1,1,1);
	}
    return 0;
}
```


---

## 作者：rai1gun (赞：0)

### 1.题目大意

给定你 $n$，让你找到 $a,b,c,d$ 四个数，使得 $\text{gcd(a,b) = 1}$ 且 $\text{lcm(c,d)=1}$。

### 2.题目思路

我们先从最小公倍数下手，由于 $\text{lcm(a,b)}= \dfrac{a \times b}{\text{gcd(a,b)}} $，所以 $a\times b = \text{gcd(a,b)}=1$ 肯定有解。

现在我们再看 $\text{gcd(a,b)}$ 。由于我们刚才所需的条件，所以 $\text{gcd(a,b)=1}$。我们知道对于 $k$，$k \in \mathbb{Z},\text{gcd(1,k)=1}$。所以我们只需要将 $a$ 设为 $1$，$b$ 设为 $n-3$ 即可。

### 3.题目代码

```cpp
#include<bits/stdc++.h>
// 快读部分省略
using namespace Fast_Io;
int t,n;
int main(){
	read(t);
	while(t--){
		read(n);
		print(1,' ');
		print(n-3,' ');
		print(1,' ');
		print(1,'\n');
	}
	return 0;
}

```

---

## 作者：Tx_Lcy (赞：0)

## 题目描述
[题目传送门](https://www.luogu.com.cn/problem/CF1665A)

题目大意为构造四个数，使得前两个数的最大公约数等于后两个数的最小公倍数。
## 题目思路
很显然，我们知道当 $c=d=1$ 时 $\operatorname{lcm}(c,d)=1$。而当 $a=1$ 且 $b \ge 1$ 时 $\gcd(a,b)=1$。那么此时我们就构造出了这四个数，分别为 $a=1,b=n-3,c=1,d=1$。
## 题目代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	int t;cin>>t;
	while (t--){
		int n;cin>>n;
		cout<<1<<' '<<n-3<<' '<<1<<' '<<1<<'\n';
	}
	return 0;
}
```


---

## 作者：Altwilio (赞：0)

$ 1.$ 题意

给定一个正整数 $n$，求一组正整数 $a, b, c, d$ 使得 $a+b+c+d=n$，并且 $a,b$ 的最大公因数等于 $c,d$ 的最小公倍数。

$ 2.$ 思路

推推式子，发现（手写勿喷）

![](https://cdn.luogu.com.cn/upload/image_hosting/pz2xcp18.png)

发现直接输出 $n-3, 1, 1, 1$ 即可。

$ 3.$ 代码

非常简略！
```cpp
#include<iostream>
using namespace std;
signed main(){
    int t; cin >> t;
    while(t --){
        int n; std::cin >> n;
        cout << n - 3 << " 1 1 1"<< endl;
    }
    return 0;
}
```


---

## 作者：Crab_time (赞：0)

# 题目大意

有 $t$ 组数据，每组数据给你一个正整数 $n$ ，让你输出任意一组正整数 $a$ ， $b$ ， $c$ ， $d$ ，使得满足 $\gcd(a,b) = \operatorname{lcm}(c,d)$ 并且 $a + b + c + d = n$

# 解法

首先特判 $n$ 是否为 $4$ 的倍数，若成立则令 $a$ ， $b$ ， $c$ ， $d$ 均为 $\frac{n}{4}$ 。

证明：

根据最大公约数和最小公倍数的性质： 若 $a = b$ ， 则 $\gcd(a,b) = a$ ， $\operatorname{lcm}(a,b) = a$ 。

$\therefore$ $\gcd(a,b) = \operatorname{lcm}(c,d) = \frac{n}{4}$ 并且 $a + b + c + d = n$ 。

不成立则开始枚举 $a$ ， $b$ ， $c$ 。 $d$ 可以通过 $n - a - b - c$ 得到，不用进行 $4$ 重循环。 $a$ 从 $\frac{n}{2}$ 开始枚举到 $1$ ， $b$ 从 $n - a$ 开始枚举到 $1$ ， $c$ 从 $n - a - b$ 开始枚举到 $1$ 。并且枚举 $b$ 时若 $n - a - b < 2$ 进入下一个循环，枚举 $c$ 时若 $n - a - b - c < 1$ 进入下一个循环。

对于上述操作的解释： 因为这道题目的要求是存在解即可输出。所以 $a$ 从 $\frac{n}{2}$ 开始枚举可以保证 $b + c + d$ 一定大于等于 $\frac{n}{2}$ ，同时减少了时间复杂度。 $b$ 与 $c$ 的枚举方式同样减少了时间复杂度。对于 枚举 $b$ 时的特判是因为若 $n - a - b < 2$ 则 $d$ 不成立，枚举 $c$ 时的特判是因为若 $n - a - b - c < 1$ 则 $d$ 不成立。

在枚举出 $a$ ， $b$ ， $c$ ， $d$ 后若满足 $\gcd(a,b) = \operatorname{lcm}(c,d)$ 则输出答案并进入下一组数据。

# 代码

```cpp
#include<iostream>
using namespace std;

int n,a,b,c,d,t;
bool flag = false;

int gcd(int x,int y)
{
    return y==0?x:gcd(y,x%y);
}

int lcm(int x,int y){
    return x * y / gcd(x,y);
}

int main()
{
    cin >> t;
    while(t--){
        cin >> n;
        if(n%4==0){
            a = n/4;
            b = a;
            c = b;
            d = c;
            cout << a << " " << b << " " << c << " " << d << endl;
            continue;
        }
        flag = false;
        for(a = n/2;a>=1;a--){
            for(b = n - a;b>=1;b--){
                if(a+b>n-2){
                    continue;
                }
                for(c = n - a - b;c>=1;c--){
                    if(n-a-b-c<1){
                        continue;
                    }
                    d = n - a - b - c;
                    if(gcd(a,b)==lcm(c,d)){
                        cout << a << " " << b << " " << c << " " << d << endl;
                        flag = true;
                        break;
                    }
                }
                if(flag){
                    break;
                }
            }
            if(flag){
                break;
            }
        }
    }
    return 0;
}
```

---

## 作者：POYE (赞：0)

能发现一个非常明显的性质，即 $gcd(m,1)=1$，$lcm(1,1)=1$，所以最简单的既满足 $gcd(a,b)=lcm(c,d)$ 且满足 $a+b+c+d=n$ 的四元组 $(a,b,c,d)$ 即为 $(n-3,1,1,1)$，直接输出即可。

## AC Code
```cpp
#include<cstdio>
using namespace std;
int main()
{
	int T;
	scanf("%d",&T);
	for(int o=1;o<=T;o++)
	{
		int n;
		scanf("%d",&n);
		printf("%d 1 1 1\n",n-3);
	}

	return 0;
}
```


---

## 作者：int4 (赞：0)

大家好，这是小菜鸡 int4 写的第一篇题解。如有不足望大家多多包涵。qwq

---

先讲讲我做这道题目的思路吧。

首先，我一看到题目中的 $a+b+c+d=n$ 和 $\gcd(a,b)=\operatorname{lcm}(c,d)$ 这两个条件，马上就想到了在 $n\bmod 4=0$ 时，$a=b=c=d=\dfrac{n}{4}$ 显然是一组满足要求的解。然后我就想着能否按照 $n\bmod 4$ 的余数来进行分类讨论。一看样例中：

- $n=7$，对应的是 $n\bmod 4=3$ 的情况，样例给出的构造方案是 $a=b=c=2$，$d=1$。
- $n=8$，对应的是 $n\bmod 4=0$ 的情况，样例给出的构造方案是 $a=b=c=d=2$。
- $n=9$，对应的是 $n\bmod 4=1$ 的情况，样例给出的构造方案是 $a=c=2$，$b=4$，$d=1$。
- $n=10$，对应的是 $n\bmod 4=2$ 的情况，样例给出的构造方案是 $a=b=3$，$c=5$，$d=1$。

根据进一步思考，我发现：

- $n\bmod 4=1$ 时，构造 $a=\dfrac {n-1}{4}$，$b=\dfrac{n-1}{2}$，$c=\dfrac {n-1}{4}$，$d=1$。此时，$\gcd(a,b)=\dfrac{n-1}{4}$，$\operatorname{lcm}(c,d)=\dfrac{n-1}{4}$，满足题目条件。
- $n\bmod 4=2$ 时，构造 $a=\dfrac {n-2}{2}-1$，$b=\dfrac{n-2}{2}+1$，$c=d=1$。此时，由于 $a,b$ 为相差 $2$ 的奇数，因此 $\gcd(a,b)=1$，而又因为 $\operatorname{lcm}(c,d)=1$，所以满足题目条件。
- $n\bmod 4=3$ 时，构造 $a=c=2$，$b=n-5$，$d=1$。此时，由于 $n-5$ 必然为偶数，因此 $\gcd(a,b)=2$，而又因为 $\operatorname{lcm}(c,d)=2$，所以满足题目条件。

正当我把题目写完交上去后，我突然发现，我被样例带偏了。事实上根本并不需要按照 $n\bmod 4$ 分类讨论。我们只需要构造出 $a=n-3,b=c=d=1$，此时就可以满足 $\gcd(a,b)=\operatorname{lcm}(c,d)$ 的条件了，因为显然这两边的值都是 $1$。

看来，以后做题还是不能过度依赖样例啊。QAQ

---

代码……既然你思路都懂了，这道题目就只有简单的输入输出的问题吧？所以就不贴啦。qwq

---

## 作者：heaksicn (赞：0)

## 1 题意
给定 $n$，求 $4$ 个数 $a,b,c,d$，满足 $a+b+c+d=n$ 且 $\gcd(a,b)=lcm(c,d)$。

多组数据。

## 2 思路
对于 $\gcd$ 和 $lcm$，有两个性质：

1. $\gcd(1,x)=1$

2. $lcm(1,1)=1$

那么此时，$\gcd(1,x)=lcm(1,1)$。

令 $b=c=d=1,a=n-3$ 即可。

时间复杂度 $O(T)$。

## 3 code
```
#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int X=0,w=0; char ch=0;
    while(!isdigit(ch)) {w|=ch=='-';ch=getchar();}
    while(isdigit(ch)) X=(X<<3)+(X<<1)+(ch^48),ch=getchar();
    return w?-X:X;
}
inline void write(int x){
	if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
int T,n; 
int main(){
	T=read();
	while(T--){
		n=read();
		cout<<n-3<<" 1 1 1"<<endl;
	}
	return 0;
}

```


---

## 作者：金霸王电池 (赞：0)

题目翻译：

$a+b+c+d=n$,$gcd(a,b)=lcm(c,d)$。求出一组满足条件的正整数解。

注意到只需输出一组解，考虑特殊解。观察发现，$a=n-3,b=1,c=1,d=1$ 时满足条件。那么只需输出这组解即可。

AC 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
signed main(){
	cin>>t;
	while(t--){
		cin>>n;
		cout<<n-3<<" 1 1 1"<<endl;
	}
	return 0;
} 
```


---

## 作者：IYSY2009I (赞：0)

[本人的翻译](https://www.luogu.com.cn/paste/bt1petc5)

首先我们要知道，对于任一个正整数 $x$,$\gcd(x,1)=1$，所以我们对于任意 $\ge 4$ 的正整数 $n$,都可以构造出 $a=n-3,b=1,c=1,d=1$，使得 $\gcd(a,b)=\gcd(n-3,1)=\operatorname{lcm}(c,d)=\operatorname{lcm}(1,1)=1$ 且 $a+b+c+d=n-3+1+1+1=n$,所以输出 `n-3 1 1 1` 即可。

代码：
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=(x<<1)+(x<<3)+c-'0';
		c=getchar();
	}
	return x*f;
}
void cf(){
	int n=read();
	printf("%d 1 1 1\n",n-3);
	return;
}
int main(){
	int t=read();
	for(int i=1;i<=t;i++)
		cf();
	return 0;
}
```


---

## 作者：封禁用户 (赞：0)

#### 思路

看到题首先想到枚举，但是看了看数据范围好像并不可枚举的样子。
只能构造了。
首先就想到了将最大公约数与最小公倍数构造为1，然后就想出了一种构造：$ a = n - 3 $ ， $ b = 1 $ ， $ c = 1 $ ， $ d = 1 $

然后发现对了。

#### 代码

```
#include <bits/stdc++.h>
using namespace std;
int t , n;
int main()
{
	cin >> t;
	while(t--)
	{
		cin >> n;
		cout << n << ' ' << 1 << ' ' << 1 << ' ' << 1 << endl;
	}
	return 0;
}


---

## 作者：lsj2009 (赞：0)

## 题目大意
给定一个正整数 $n$。

找到 $4$ 个正整数 $a,b,c,d$ 使得 $a+b+c+d=n$ 且 $\gcd(a,b) = \operatorname{lcm}(c,d)$。

如有多组解，输出任意一组即可。
## 思路
看见 $\texttt{Special Judge}$，直接构造即可。

既然要让 $\gcd$ 与 $\operatorname{lcm}$ 相同，那么我们的第一反应就是固定他们的值，而 $1$ 就是一个很好的选择。

令 $\operatorname{lcm}(c,d)=1$，则有解且仅有唯一解 $c$ 与 $d$ 均为 $1$。

令 $\gcd(a,b)=1$，则只需令 $a$ 或 $b$ 其一者为 $1$ 即可。

而又要令 $a+b+c+d=n$，那么根据上述，我们不妨让 $b=c=d=1,a=n-3$ 即可。

---

## 作者：奥斯卡小冰人 (赞：0)

题意比较简单，这里直接说思路。

我们考虑 $\gcd(a,b) = \operatorname{lcm}(c,d) = 1$，那么 $c = d = 1$，$a$ 和 $b$ 中有一个是 $1$。 再结合 $a + b + c + d = n$，可以轻松的把四个值都打出来 $a = n - 3,b = c = d = 1$。

Code:
```cpp
#include <bits/stdc++.h>
using namespace std;

#define gc getchar
#define qwq 0

typedef long long ll;
typedef unsigned long long ull;

const int N = 2e5 + 10;

int read()
{
    int a = qwq,b = qwq;char c = gc();
    while(c < '0'||c > '9') b ^= (c == '-'),c = gc();
    while(c >= '0'&&c <= '9') a = a * 10 + c - 48,c = gc();
    return b ? -a : a;
}

int main()
{
    int T = read();
    while(T--)
    {
        int n = read();
        printf("%d 1 1 1\n",n - 3);
    }
    return qwq;
}
```

---

## 作者：瀛洲仙子 (赞：0)

### 思路分析
此题绝对的贪心。    
我们都知道，$x$ 作为任意值，必有$gcd(1,x)=1$ 和 $lcm(1,1)=1$。所以代码如下。
```cpp
#include <bits/stdc++.h>
using namespace std;
int main () {
    int t;cin >> t;
    while(t--)
    {
        int n;cin >> n;
        printf("%d 1 1 1\n",n-3);
    }
}
```
这题有 $SPJ$，这样就能 AC。

---

## 作者：Deuteron (赞：0)

### 题意简述：
给定一个数字 $n$ ，你需要找出一组 $(a,b,c,d)$ 使得 $\gcd(a,b)=\operatorname{lcm}(c,d)$ ， $a+b+c+d=n$。

$4\le n \le10^9$
### solution:

显然对于任意的 $k$， $\gcd(k,1)=1$ 

所以 $\gcd(n-3,1)=1$ 。

又有 $\operatorname{lcm}(1, 1)=1$

故 $a=n-3,b=1,c=1,d=1$ 即为所求。

### code:

```cpp
#include<iostream>
using namespace std;
int n;
int main(){
	int t;
	cin>>t;
	while(t--){
		cin>>n;
		cout<<n-3<<" "<<1<<" "<<1<<" "<<1<<endl;
	}
	return 0;
}
```


---

