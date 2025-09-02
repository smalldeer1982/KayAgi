# GCD Problem

## 题目描述

Given a positive integer $ n $ . Find three distinct positive integers $ a $ , $ b $ , $ c $ such that $ a + b + c = n $ and $ \operatorname{gcd}(a, b) = c $ , where $ \operatorname{gcd}(x, y) $ denotes the [greatest common divisor (GCD)](https://en.wikipedia.org/wiki/Greatest_common_divisor) of integers $ x $ and $ y $ .

## 说明/提示

In the first test case, $ 6 + 9 + 3 = 18 $ and $ \operatorname{gcd}(6, 9) = 3 $ .

In the second test case, $ 21 + 39 + 3 = 63 $ and $ \operatorname{gcd}(21, 39) = 3 $ .

In the third test case, $ 29 + 43 + 1 = 73 $ and $ \operatorname{gcd}(29, 43) = 1 $ .

## 样例 #1

### 输入

```
6
18
63
73
91
438
122690412```

### 输出

```
6 9 3
21 39 3
29 43 1
49 35 7
146 219 73
28622 122661788 2```

# 题解

## 作者：正负君 (赞：15)

#### 2023/01/15 将“公倍数”修改成了“公因数”

# CF1617B GCD Problem 题解

# 题意 

给出 $n$，求出一组合法的 $a,b,c$，满足以下要求： 
$$\left\{
\begin{array}{l}
a\neq b\\
a\neq c\\
b\neq c\\
a+b+c=n\\
\gcd(a,b)=c\\
\end{array}
\right.
$$ 

# 分析 

显然，$\gcd(a,b)=c$，将 $c$ 替换成 $\gcd(a,b)$，那么 $a+b+\gcd(a,b)=n$。 

至少有一组解。很显然，$c=1$ 时更好构造。 

因为如果 $c=1$，则 $\gcd(a,b)=1$。因为 $a$ 和 $b$ 只有一个公因数，是 $1$，所以 $a\perp b$（$a\perp b$ 代表 $a$ 与 $b$ 互质）。也就是 $a+b+1=n$。

然后就好办了。众所周知，一个数与它减去 $1$ 互质（$a\perp a-1$）   

- 如果 $n$ 是偶数，那么 $a=n\div2,b=a-1$。 
- 否则，我们就再分情况考虑：  
> - 如果 $n-1$ 为 $4$ 的倍数时，需要满足 $a\perp b$，那么 $a=(n-1)\div2-1,b=a+2$；  
> - 否则，那么 $a=(n-1)\div2-2,b=a+4$

# 代码  

接下来放出~~你们最喜欢的完整~~代码：  

```cpp
#include<iostream>
using namespace std;
int t,a,b,c,n;
int main()
{
  cin>>t;
  for(int i=1; i<=t; i++)//共有 t 次。
  {
    cin>>n;
    c=1;                //无论如何，我们选择的结果 c 总是 1。
    if(n%2==0)          //第一种情况：
    {
      a=n/2-1;
      b=n/2;
    }
    else if((n-1)%4==0) //第二种情况：
    {
      a=(n-1)/2-1;
      b=(n-1)/2+1;
    }
    else                //第三种情况：
    {
      a=(n-1)/2-2;
      b=(n-1)/2+2;
    }
    cout<<a<<' '<<b<<' '<<c<<endl;
  }                     //输出。
  return 0;             //完美地结束啦！
}
```

看完我的题解了，不妨点个赞吧！

---

## 作者：Kris_hukr (赞：4)

### 题意

给定 $n$, 求出一组 $(a,b,c)$ 使 $a+b+c=n$ 且 $\gcd(a,b)=c$。

### 分析

不妨钦定 $c$ 为 $1$，这样只要保证 $a + b = n-1$ 且 $a \perp b$ 即可。

当 $n$ 为偶数时，由于**相邻两个自然数必定互质**，所以有一组答案为 $\left(\dfrac{n}{2}-1,\dfrac{n}{2},1 \right)$。

当 $n$ 为奇数时，我们令 $d = \dfrac{n - 1}{2}$，为了保证 $a + b = n - 1$ ，答案应该为 $(d - k, d + k, 1)$ 的形式。

由于**相邻两个奇数必定互质**，

当 $d$ 为偶数时， $k$ 应取 $1$，即有一组答案为 $\left(\dfrac{n - 1}{2} - 1, \dfrac{n - 1}{2} + 1, 1 \right)$；

当 $d$ 为奇数时， 又由于 $a,b,c$ 互不相同 ，$k$ 应取 $2$，即有一组答案为 $\left(\dfrac{n - 1}{2} - 2, \dfrac{n - 1}{2} + 2, 1 \right)$。

~~当然，由于此题数据范围不算很大，你也可以选择直接暴力枚举。~~

### 代码

仅给出部分实现。

```cpp
int n = read<int>();
if (n & 1) {
    int h = (n - 1) / 2;
    if (h & 1) {
        printf("%d %d 1\n", h - 2, h + 2);
    } else {
        printf("%d %d 1\n", h - 1, h + 1);
    }
} else {
    printf("%d %d 1\n", n / 2 - 1, n / 2);
}
```



---

## 作者：MCRS_lizi (赞：3)

咕值不够了，好不容易找到一道可以写题解的题目，那么还是开整吧。

# 题目大意
输入 $n$ ，输出任意一组符合 $a+b+gcd(a,b)=n$ 的 $a,b,gcd(a,b)$ 。

其中 $gcd(a,b)$ 表示 $a$ 与 $b$ 的最大公因数
# 题目分析
这道题一开始会让人感觉无从下手，但又只要找到任意一组解即可，各位试想一下自己上学时遇到无从下手的数学题，但又只要你给出任意符合题目情况的解该怎么办？凑呗！

但凑也是要看情况的，所以这道题需要简单的分类讨论。

既然是分类讨论，依据什么来分？不妨先试试简单的奇偶性吧。

众所周知，两个相差 $1$ 的正整数一定互质，也就是最大公因数为 $1$ 。

也就是说， $x$ 与 $x-1$ 一定互质。

所以可以得出，当 $n$ 为偶数时：

$a=n/2$ ，$b=n/2-1$ 就可以满足条件。

那么 $n$ 为奇数时怎么解决呢？

奇数不好解决就变成偶数嘛。

所以，我们可以对 $n+1$ 进行处理。

但如果继续进行下去，我们会发现 $n+1$ 没办法直接处理。

没办法，继续分类， $2$ 的倍数分过了，那就分 $4$ 的倍数。

当 $n+1$ 为 $4$ 的倍数时， $(n-1)/2$ 一定是奇数，由此可得：

$a=(n-1)/2-2$ , $b=(n-1)/2+2$ 。(可以证明 $a$ 与 $b$ 一定互质)

如果 $n+1$ 不是 $4$ 的倍数：

$a=(n+1)/2-2$ ， $b=(n+1)/2$ 即可。

然后你会惊奇的发现， $gcd(a,b)=1$ 就可以满足全部条件，吓得我去看了上面的题解才知道 $gcd(a,b)=1$ 真的可以全部满足。

#  _**Code**_ 
```c
#include<bits/stdc++.h>
using namespace std;
int t,n;
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>n;
		if(n%2==0)
		{
			cout<<n/2-1<<" "<<n/2<<" "<<1<<endl;
		}
		else if((n+1)%4==0)
		{
			cout<<(n-1)/2-2<<" "<<(n-1)/2+2<<" "<<1<<endl;
		}
		else
		{
			cout<<(n+1)/2-2<<" "<<(n+1)/2<<" "<<1<<endl;
		}
	}
	return 0;
}
```


---

## 作者：OoXiao_QioO (赞：2)

# 前言

这是一个不太懂数学的小屑生写的文章，如果您想看更具有说服力的文章，请移步到别的题解，这个题解是用“充满智慧的暴力枚举大法”来通过解题的。

# 题目描述

给定一个正整数 $n$，请找出一组**互不相同**的正整数 $a,b,c$，使得：

- $a+b+c = n$。
- $\gcd(a,b) = c$。

其中 $\gcd(x,y)$ 表示 $x$ 和 $y$ 的最大公因数。

# 思路

一道很简单的构造题，很容易想到当 $c = 1$ 的时候解法最多。为什么呢？$c = 1$ 说明 $a$ 和 $b$ 一定是正整数；当 $c = 2$ 的时候，$a$ 和 $b$ 一定是偶数；当 $c = 3$ 的时候，$a$ 和 $b$ 一定是 $3$ 的倍数。此时我们发现，如果 $c$ 越大，那么满足条件的 $a$ 和 $b$ 就越难找，我们只需要让 $c$ 最小即可，所以 $c = 1$ 的时候解法最多。

那么我们只需枚举 $a$ 和 $b$ 就可以了。怎么个枚举法呢？可以先让 $a = 2$，再从 $n-3$ 挨个枚举 $b$，满足条件就输出。 当写出代码时，发现有一个弊端，万一 $n$ 是奇数而且也是 $3$ 的倍数，例如 ```63``` 呢？程序竟然会输出 ```2 0 1```！出现了 $0$ 就肯定出错，所以需要优化。我们可以让 $a$ 也加入到枚举的行列里，每次枚举，让 $b-1$，同时也让 $a+1$，双管齐下，肯定能找到正确的答案。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	//定义变量
	 
	int n,t,a,b,c;
	
	//输入
	 
	cin>>t;
	
	//处理
	 
	while(t--)
	{
		cin>>n;
		//假设让c = 1,a = 2,b = n-3,原因前文已经解释。 
		c = 1;
		a = 2;
		b = n-3;
		
		//暴力枚举大法，如果不满足条件就一直枚举，反正题目说了有解 
		while(!(__gcd(a,b)==1&&a+b+c==n))//不满足条件 
			a++,b--;//继续枚举 

		//找到答案了，输出 
		printf("%d %d %d\n",a,b,c);
	}
	return 0;
}
```


---

## 作者：Coros_Trusds (赞：1)

[更好的阅读体验](https://www.cnblogs.com/Coros-Trusds/p/15773327.html)

最开始以为是计数问题，卡了好久（

话说这道题出成计数不失为一道好题~~主要是我不会~~。

----
一个很显然的思路。

# 题目大意

给定一个正整数 $n$，请找出一组**互不相同**的正整数 $a,b,c$，使得：

- $a+b+c=n$。
- $\gcd(a,b)=c$。

其中 $\gcd(x,y)$ 表示 $x$ 和 $y$ 的最大公因数。

# 题目分析

令 $c=1$，有 $\gcd(a,b)=1$，即 $a,b$ 互质。

分类讨论一波咯：

+ $n$ 为偶数时，$\dfrac{n}{2}$ 为整数，所以有 $a=\dfrac{n}{2}-1,b=\dfrac{n}{2}$。

+ $n$ 为奇数时：

> + 若 $n-1$ 为 $4$ 的倍数时，需要满足 $\gcd(a,b)=1$，有 $a=\dfrac{n-1}{2}-1,b=\dfrac{n-1}{2}+1$。
>
> + 若 $n-1$ 非 $4$ 的倍数时，有 $a=\dfrac{n-1}{2}-2,b=\dfrac{n-1}{2}+2$。

----
然后这道题就做完了。

# 代码

$\frak{Main~Code:}$

```cpp
inline void solve()
{
	n=read();
	
	if(n%2==0)
	{
		a=n/2-1,b=n/2,c=1;
	}
	
	else
	{
		if((n-1)%4==0)
		{
			a=(n-1)/2-1,b=(n-1)/2+1,c=1;
		}
		
		else
		{
			a=(n-1)/2-2,b=(n-1)/2+2,c=1;
		}
	}
	
	printf("%d %d %d\n",a,b,c);
}
```

---

## 作者：Eason_AC (赞：0)

## Content
给定一个正整数 $n$，请找出一组**互不相同**的正整数 $a,b,c$，使得：

- $a+b+c=n$。
- $\gcd(a,b)=c$。

**数据范围：$t$ 组数据，$1\leqslant t\leqslant 10^5$，$10\leqslant n\leqslant 10^9$。**
## Solution
我们不妨钦定 $c=1$，即 $a,b$ 互质，然后上一波分类讨论：

- $2\mid n$，此时即可构造出 $a=\frac n2-1$，$b=\frac n2$，$c=1$ 的一组解。
- $2\nmid n$，那么我们减去一个 $1$ 之后发现，要使 $a,b$ 均为奇数，则仍有不同种情况，于是继续分类讨论：
    - $4\mid (n-1)$，此时即可构造出 $a=\frac{n-1}2-1$，$b=\frac{n-1}2+1$，$c=1$ 的一组解。
    - $4\nmid (n-1)$，此时即可构造出 $a=\frac{n-1}2-2$，$b=\frac{n-1}2+2$，$c=1$ 的一组解。

然后你就做完了。代码根据上面这个很容易写，就不放了。

---

## 作者：WangBng (赞：0)

此题如果枚举的话情况太多，不妨设 $c=1$ 。

再分类讨论：

- $2\mid n$ ，那么 $a+b=n-1$ ， 根据相邻数互质的原理，易知 $a=\frac{n}{2}-1,b=\frac{n}{2}$ 。

- $2\nmid n$

	- $n\equiv1\pmod{4}$ ，我们发现 $\frac{n-1}{2}-1,\frac{n-1}{2}+1$ 都为奇数且互质，直接输出它们即可。
    
   - $n\equiv3\pmod{4}$ ，不难发现 $\frac{n-1}{2}-2,\frac{n-1}{2}+2$ 都为偶数且互质，输出它们即可。
   
Code：

```cpp
#include<iostream>
using namespace std;
int main(){
	int t,n;
	cin>>t;
	while(t--){
		cin>>n;
		if((n&3)==3){
			cout<<((n-1)>>1)-2<<" "<<((n-1)>>1)+2<<" "<<1<<endl;
		}
		else if(n&1){
			cout<<((n-1)>>1)-1<<" "<<((n-1)>>1)+1<<" "<<1<<endl;
		}
		else{
			cout<<((n-1)>>1)<<" "<<n-1-((n-1)>>1)<<" "<<1<<endl;
		}
	}
	return 0;
}
```

[完结撒花](https://vjudge.net/solution/36567458)

---

## 作者：liangbowen (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1617B)

[$\color{red}{see}\space \color{green}{in}\space \color{blue}{my}\space \color{purple}{blog}$](https://www.luogu.com.cn/blog/liangbowen/solution-CF1617B)

小学生又双叒叕来写题解啦！

其他题解的代码都是 $O(1)$ 的，对于小学生来说，这也太难分类讨论了。

我们可以用**短除模型**解决。

设 $c \times q_1 = a$，$c \times q_2 = b$ 并且 $q_1$ 与 $q_2$ 互质。

$$a + b + c = n$$

$$c \times q_1 + c \times q_2 + c = n$$

$$c \times (q_1 + q_2 + 1) = n$$

我们只需要枚举 $c$，如果 $c \mid n$ 就停下来，看看 $q_1$ 与 $q_2$ 能否构造。

此时，$q_1 + q_2 = \dfrac{n}{c} - 1$。

我们再枚举 $q_1$ 与 $q_2$，如果 $\gcd(q_1, q_2) = 1$，说明：

$$\begin{cases}a = q_1 \times c\\b = q_2 \times c\\c = c\end{cases}$$

是其中一个解。

注意！还有一个坑点，就是 $a \ne b \ne c$。

所以，$q_1$ 与 $q_2$ 不能等于 $1$ 哦。

到这就算完了。

如果你担心算法跑得不够快，可以往程序里输入 $n = 10^9$ 看看会不会超时就行了。

## 完整代码：

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
int gcd(int x, int y)
{
	if (y == 0) return x;
	return gcd(y, x%y);
}
void solve()
{
	int n;
	scanf("%d", &n);
	for (int c = 1; c <= n; c++)
		if (n % c == 0)
		{
			int sum = n / c - 1;  //指 q1+q2 的结果。
			for (int q1 = 2; q1 <= n-2; q1++)  //q1 不能等于 1 所以界线有改变。
			{
				int q2 = sum - q1;
				if (gcd(q1, q2) == 1)
				{
					printf("%d %d %d\n", q1*c, q2*c, c);
					return;
				}
			}
		}
}
int main()
{
	int T;
	scanf("%d", &T);
	while (T--) solve();
	return 0;
}
```

---

## 作者：heaksicn (赞：0)

## 1 题意
给定一个 $n$，求一组 $a,b,c$，满足 $a+b+c=n$ 且 $\gcd(a,b)=c$。

多组数据。
## 2 思路
假定 $c=1$ 。

如果 $n$ 为奇数，那么 $a=n/2,b=n/2+1$ 即可。

如果 $n$ 为偶数，那么 $a=n/2-1,b=n/2+1$ 即可。  
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
int gcd(int a,int b){//求gcd
	if(b==0) return a;
	return gcd(b,a%b);
}
int T;
int main(){
	cin>>T;
	int n;
	while(T--){
		n=read();
		n--;
		int c=1,a,b;
		if(n%2){//n为奇数
			a=n/2,b=n/2+1;
		}else{//n为偶数
			for(a=n/2-1;a>1;a--){
				b=n-a;
				if(gcd(a,b)==1) break;
			}
		}
		cout<<a<<" "<<b<<" "<<c<<endl;
	}
	return 0;
}
```


---

## 作者：Tx_Lcy (赞：0)

###  Part 0 背景
昨天晚上打 CF 的时候先做了这题，因为 T1 的题目老长，百度翻译卡死了(.......)。
### Part 1 解法
显然，这道题目有一个思路：

因为$\gcd(a,b)=c$，所以可以设 $\ a=x \times c$,  
设$\ b=y \times c\ $，那么可得

$a+b+c=n$

$x \times c+y \times c + 1 \times c=n$

$(x+y+1) \times c=n$

所以，我们只要找到 n 的两个约数，一个是 x+y+1 ，一个便是 c ，但是要注意：

$x+y+1≥6\ $ 因为 $\ x≥1,y≥1\ $ 并且它们都不相等。

$\gcd(x,y)=1\ $ 因为事实上 $\gcd(a,b)=\gcd(x,y)\times c\ $ ，而$\gcd(a,b)=c$

所以$\gcd(x,y)=1$
### Part 2 AC代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int gcd(int a,int b){return a%b==0?b:gcd(b,a%b);}//最大公约数模板
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;cin>>n;
	while (n--){
		int t;cin>>t;//输入
		for (int i=1;i*i<=t;i++)//找约数
		    if (t%i==0){
		    	int k=t/i;
		    	if (k<=5) continue;
				k--;
				int l=2;//判断开始
				for (int l=2;l<=t;l++){
					if (gcd(l,k-l)==1){
						cout<<l*i<<' '<<(k-l)*i<<' '<<i<<'\n';
						break;//找到一个就退出了
					}
				}
				break; 
			}	 
	}
	return 0;
}
```


---

