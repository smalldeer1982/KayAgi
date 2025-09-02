# Secrets

## 题目描述

Gerald has been selling state secrets at leisure. All the secrets cost the same: $ n $ marks. The state which secrets Gerald is selling, has no paper money, only coins. But there are coins of all positive integer denominations that are powers of three: 1 mark, 3 marks, 9 marks, 27 marks and so on. There are no coins of other denominations. Of course, Gerald likes it when he gets money without the change. And all buyers respect him and try to give the desired sum without change, if possible. But this does not always happen.

One day an unlucky buyer came. He did not have the desired sum without change. Then he took out all his coins and tried to give Gerald a larger than necessary sum with as few coins as possible. What is the maximum number of coins he could get?

The formal explanation of the previous paragraph: we consider all the possible combinations of coins for which the buyer can not give Gerald the sum of $ n $ marks without change. For each such combination calculate the minimum number of coins that can bring the buyer at least $ n $ marks. Among all combinations choose the maximum of the minimum number of coins. This is the number we want.

## 说明/提示

In the first test case, if a buyer has exactly one coin of at least 3 marks, then, to give Gerald one mark, he will have to give this coin. In this sample, the customer can not have a coin of one mark, as in this case, he will be able to give the money to Gerald without any change.

In the second test case, if the buyer had exactly three coins of 3 marks, then, to give Gerald 4 marks, he will have to give two of these coins. The buyer cannot give three coins as he wants to minimize the number of coins that he gives.

## 样例 #1

### 输入

```
1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
4
```

### 输出

```
2
```

# 题解

## 作者：Sincerin (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/CF333A)

题外话：~~建议评黑，题意极毒。~~

## 题目描述

有一位旅行者去找商人买了一个价值 $n$ 元的东西。在结账时，他突然尴尬地发现自己身上只有硬币了，并且他无法付给商人刚好 $n$ 元钱。旅行者随身带着的硬币的面值都是 $3$ 的整数次幂，这样的硬币面值可以很大，旅行者身上也有非常多，多到自己都数不清呢。

这个商人不喜欢找零，所以旅行者试图用数量尽可能少的硬币给他一笔大于等于 $n$ 的钱，并且额外付出的部分要最小。可是作为旅行者的忠实粉丝，商人好像认出了旅行者，并要求在上述情况下得到尽可能多的硬币用于收藏。

聪明的你可以帮帮他吗？请求出商人最多可以得到的硬币数量。

- $1 \leq n \leq 10^{17} $

## 题目解析

首先分析题目，我们把硬币的面值表示为 $x=3^k \ (k \geq 0)$ 的形式。

旅行者既然**无法付给**商人刚好 $n$ 元，也就是说他选的硬币面值 $x$ 并不能被 $n$ 整除，即 $n \mod x \neq 0$。

综上，我们可以通过枚举 $3$ 的整数次幂来直接枚举每个面值的硬币，直到找出第一个不能被 $n$ 整除的面值 $x$。

此时，我们直接用物品的价值 $n$ 来除以硬币面值 $x$ 得到的并不是最终的硬币数量。因为本身除不尽，$C++$ 会进行强制向下取整。比如当你的钱的面值 $x=3$，你买的东西价格 $n=16$ 时，向下取整得到的结果是 $\lfloor \frac{16}{3} \rfloor = 5$。~~你敢给老板 5 张三块钱试试？~~ 

所以最后结果还要加 $1$。

上述过程也可以使用 `<cmath>` 库里的向上取整函数 `ceil()` 来进行处理。但是要注意使用这个函数的运算必须是**浮点类型数据**的运算，不然就会像[这篇题解](https://bywyr.blog.luogu.org/solution-cf333a)一样错掉。

- 坑点：$10^{17}$ 要开 `long long`！

## AC Code

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
long long n,ans; //一定记得开long long! 
int main() 
{
	scanf("%lld",&n);//输入，使用scanf时别忘了&地址符:) 
	ans=1;//这是硬币面值 
	while(n%ans==0) ans*=3;//每次扩大3倍，相当于指数加1 
	printf("%lld\n",n/ans+1);//除法运算一直是下取整的，所以要加1 
	return 0;//好习惯 
}
```

[AC记录](https://www.luogu.com.cn/record/98199988)

❤ 今天疯狂星期四 ❤

❤ 给我点赞请你吃 ❤

---

## 作者：saixingzhe (赞：2)

## 题意
一个人去买了价值为 $n$ 的东西，那个人只有价值 $3^k$ 的硬币，问商人最多可得到多少硬币。
## 分析
首先，顾客一定是付了 $3^x$ 元，如果 $n\ mod\ 3^x\neq0$，商人一定获得了最多的金币。

我们可以用 `while` 循环枚举，最后输出 $n\div(3^x)+1$ 即可。为什么要 $+1$ 呢？因为题目要求顾客给商人的钱最少，所以要 $+1$。
### 坑点
要开 `long long` 。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long x,ans=1;//不开 long long 见祖宗
int main(){
    cin>>x;
    while(x%ans==0) ans*=3;
    cout<<x/ans+1;
    return 0;
}
```

---

## 作者：zct_sky (赞：2)

### Solution:
-----
因为那位顾客用自己的硬币**无法付给**商人刚好 $n$ 的钱，又因为那位顾客给商人的硬币数量是最少的，所以那位顾客一定是付了 $3^x$ 元，且 $n\bmod 3^x!=0$，那么他付的硬币数量就是 $\left[\dfrac{n}{3^x}\right]+1$。
### Code:
-----
```c++
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll x;
int main(){
    cin>>x;
    ll ans=1;
    while(x%ans==0) ans*=3;
    cout<<x/ans+1;
    return 0;
}
```

---

## 作者：Amm_awa (赞：1)

# CF333A Secrets 题解

题目大意

一个人去买了价值为 $n$ 的东西，那个人只有价值 $3^k$ 的硬币，问商人最多可得到多少硬币。

分析一下，顾客一定是付了 $3^x$ 元,如果 $n \bmod 3^x \neq 0$,那么商人就可以得到最多的硬币。

所以用 ```while``` 枚举顾客付的钱，如果 $n \bmod 3^x \neq 0$ 那么就跳出循环，最后输出要加 1，不然会 WA。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long//十年 OI 一场空，不开 longlong 见祖宗
using namespace std;
signed main()
{
    int n,coins=3;
    cin>>n;
    while(true)//while(!(n%coins))
    {
        if(n%coins)//跳出循环的条件
        {
            printf("%lld",n/coins+1);//输出要加1
            return 0;//完美结束
        }
        coins*=3;
    }
}
```


---

## 作者：RainAir (赞：1)

### 题目大意
就是说一个人去买东西，它的金币的金额都是形如 $3^k(k \geq 0)$。

要求我们找出这样一种方案：使得付出的钱满足 $\geq N$ 的情况下，且付出最少额外价格的方案中花费金币最多的那一个。

显然付钱的时候使用的金币的金额越小就要付出越多的金币。题目同时不让付出的价格 $=N$ 所以我们要找的就是第一个不能整除 $N$ 的数 $x$,答案就是 $ [ \frac{N}{x}] + 1 $。

### 代码
```c++
#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdio>
#include <vector>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define R register
#define LL long long
#define U unsigned
#define FOR(i,a,b) for(R int i = a;i <= b;++i)
#define RFOR(i,a,b) for(R int i = a;i >= b;--i)
#define CLR(i,a) memset(i,a,sizeof(i))
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

int main(){
    LL N,now = 1ll;
    scanf("%I64d",&N);
    while(now){
        now *= 3;
        if(N%now){
            printf("%I64d",N/now + 1);return 0;
        }
    }
    return 0;
}
```

---

## 作者：maomao233 (赞：0)

### 题意
一个人去买了价值为 $n$ 的东西，那个人只有价值 $3^k$ 的硬币，问商人最多可得到多少硬币。$n$ $(1 \leq n \leq 10^{17})$。

### 分析
观察题目中给的数，规律就是它们都是 $3$ 的倍数，且相邻之间都 $\times 3$。所以商人想要收到最多的硬币，顾客一定是付了 $3^x$ 元。也就是说如果 $n \bmod 3^x \neq 0$，那么商人就可以得到最多的硬币。

所以我们就用 `while` 循环来枚举顾客付的钱，如果 $n \bmod 3^x \neq 0$ 满足条件就跳出循环输出答案。或者简洁一点就直接在 `while` 的括号里面写条件就行了。注意此题的数据范围，要开 `long long`。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	long long n; 
    cin>>n;
	long long ans=1;
    while(n%ans==0) 
	{
		ans*=3;
	}
    cout<<n/ans+1<<endl;
    return 0;
}
```


---

## 作者：tbdsh (赞：0)

# 题意
[题目传送门](/problem/cf333a)

[更好的阅读体验](/blog/tianbiandeshenghuo11/solution-cf333a)

给出一个钱数 $n(1\le n\le10^{17})$，用面额 $3^k(k\ge 1)$ 的硬币来支付，同时保证支付硬币尽量少。求商人最多可以获得多少金币。

# 分析
因为支付的数量会尽量少，所以就会要用面额尽量大的硬币来支付，此时支付了 $\left[\dfrac{n}{3^x}\right]$ 个硬币。

但此时因为无法支付完，所以还要再支付一枚硬币。总共支付 $\left[\dfrac{n}{3^x}\right] +1 $ 个硬币。

那么，就枚举 $x$，找到第一个 $n\bmod 3^x ≠ 0$ 的 $x$，输出 $\left\lfloor \dfrac{n}{3^x}\right\rfloor + 1$。

# Code 
```cpp
#include<bits/stdc++.h>

using namespace std;
long long n, cnt = 1;
int main(){
  cin >> n;
  while (n % cnt == 0){
    cnt *= 3;
  }
  cout << n / cnt + 1;
  return 0;
}
```

---

## 作者：InversionShadow (赞：0)

## CF333A Secrets 题解

#### 题外话：

>      话说洛谷 RemoteJudge 还没修好。。。 

### 思路：

阅读题意，发现这个世界的钱可以用 $3^x$ 来表示。题目要求我们给出顾客出的钱大于等于 $n$ 的情况下，超出 $n$ 的部分最小的方案。

用 ```for``` 循环枚举，找出第一个不能整除 $n$ 的数 $a$，输出 **$\lfloor \frac{n}{a}\rfloor\ + 1$** 即可，之所以只加一，是因为题目要求顾客给商人的钱最少，所以不是加二，加三，或加更多。

### 数据范围：

$1\leq n \leq 10^{17}$，本题唯一坑点：要开 ```long long```。

### Code:

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

ll n, x = 1;

int main() {
  cin >> n;
  for (; ; ) {
    x *= 3;
    if (n % x != 0) {
      break;
    }
  }
  cout << n / x + 1 << endl;
  return 0;
}

```

---

## 作者：BYWYR (赞：0)

## $\texttt{Solution}$

想要顾客付的硬币数量最少，我们要最大化每个硬币的价值，也就是说他付的钱一定为 $3^{x_{max}}$ 元。

且 $n$ $\text{mod}$ $3 \neq 0$，那么他付的最少硬币数量就为 $\left\lceil\dfrac{n}{3^{x_{max}}}\right\rceil$ 个。

注意：此处变量要开 $\text{long long}$，因为题目中说 $1 \leq n \leq 10^{17}$。

## $\texttt{Code}$

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,coin=1;//不开 long long 见祖宗
//最初硬币价值应为1，否则初始为0乘起来永远是0
int main(){
	cin>>n;
	while(n%coin==0){
		coin*=3;//最大化每个硬币的价值
	}
	cout<<ceil(n/coin);//硬币的数量
	return 0;
} 
```


---

## 作者：708151_qwq (赞：0)

[题面传送门](https://www.luogu.com.cn/problem/CF333A)

直接 `while` 循环枚举，每次当前钱数乘以 $3$，如果当前钱数不能被 $n$ 整除，输出 $n$ 除以当前钱数。但是因为不能整除，程序会自动向下取整，所以**最后结果要加一**。

直接放代码吧：

```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
	int n, dqqs=1;
	cin >> n;
	while(!(n%dqqs)) dqqs *= 3;//当 n 能整除当前钱数，当前钱数乘以 3
	cout << n/dqqs+1;//注意要加一 
	return 0;
}
```

最后，谢谢大家观看，Copy 可耻哦！

---

## 作者：windowshappy (赞：0)

[CF333A](https://www.luogu.com.cn/problem/CF333A)

题意是一个人只能用 **3** 的倍数的钱买东西问商人最多得到多少钱。读题可以发现硬币都是 **3** 的倍数所以直接进行暴力就行了，每次循环硬币乘 3，注意要开 **long long**。

**AC Code**
```cpp
#include<bits/stdc++.h>

using namesapce std;
  
int main(){
    long long n,now = 1;
    cin>>n;
    while(now){
        now *= 3;
        if(n%now){//当读到不能整除时直接输出
            cout<<n/now+1;//注意要加1
            return 0;
        }
    }
    return 0;//完美结束.
}
```
c++ 中 int 相除默认向下取整所以要加 **1**。

---

## 作者：jxbe6666 (赞：0)

### 题意：
给出客户需要付的钱数，求他最少应该给几个硬币。


------------
### 思路：
我们轻而易举可以发现，硬币的面额都为 3 的倍数。所以只需暴力模拟，用 $\text{while}$ 循环，如果发现钱数不能整除硬币面额，就输出硬币个数 + 1。

### 代码：
```cpp
#include <bits/stdc++.h>
#define I return
#define AK 0
#define IOI ;
#define ll long long
using namespace std;
ll n;
inline ll read()
{ // 快读
    ll number = 0, check = 1;
    char ch = getchar();
    while (ch < 48 || ch > 57)
    {
        check = ch == 45 ? -1 : 1;
        ch = getchar();
    }
    while (ch >= 48 && ch <= 57)
    {
        number = (number << 1) + (number << 3) + (ch ^ 48);
        ch = getchar();
    }
    return number * check;
}
inline void write(ll x)
{ // 快输
    if (x < 0)
    {
        x = ~(x - 1);
        putchar('-');
    }
    if (x > 9)
        write(x / 10);
    putchar(x % 10 + '0');
}
int main()
{
    n = read();
    ll now = 3;
    while (1)
    {
        if (n % now)
        {
            write(n / now + 1);
            I AK IOI
        }
        now *= 3;
    }
    I AK IOI
}

```


---

