# Lucky Numbers

## 题目描述

The numbers of all offices in the new building of the Tax Office of IT City will have lucky numbers.

Lucky number is a number that consists of digits $ 7 $ and $ 8 $ only. Find the maximum number of offices in the new building of the Tax Office given that a door-plate can hold a number not longer than $ n $ digits.

## 样例 #1

### 输入

```
2
```

### 输出

```
6```

# 题解

## 作者：一只书虫仔 (赞：7)

#### Description

> [CF630C Lucky Number](https://www.luogu.com.cn/problem/CF630C)  
> 给定 $n$，假设 $S(i)$ 为 $i$ 位数中只由 $7$ 和 $8$ 组成的数的个数，求
> $$\sum\limits_{i=1}^nS(i)$$

#### Solution 1

让我们一步步来分析 $S(i)$ 吧。

- $i=1$，那么只有 $7$ 和 $8$，$S(1)=2$。
- $i=2$，那么只有 $77$，$78$，$87$ 和 $88$，$S(2)=4$。
- $i=3$，那么只有 $777$，$778$，$787$，$788$，$877$，$878$，$887$，$888$，$S(3)=8$。
- ……
- $i=k$，每一位都有两种可能性（为 $7$ 或者 $8$），那么一共就有 $2^k$ 个可能。

所以最后求 

$$\sum\limits_{i=1}^n S(i)$$

就转变为 

$$\sum\limits_{i=1}^n 2^i$$

那么我们用一个 for 循环套上快速幂即可。

#### Code 1

```cpp
#include <bits/stdc++.h>

using namespace std;

long long binpow (long long b, long long p) {
	long long res = 1;
	while (p > 0) {
		if (p & 1)
			res = res * b;
		b = b * b;
		p >>= 1;
	}
	return res;
}


int main () {
	long long n;
	scanf("%lld", &n);
	long long ans = 0;
	for (int i = 1; i <= n; i++)
		ans += binpow(2, i);
	printf("%lld", ans);
	return 0;
}
```

预测得分：$100$ 分。

[AC Record](https://www.luogu.com.cn/record/36461073)

但是我们可以省掉那个 for 循环。

#### Solution 2

再次观察式子

$$\sum\limits_{i=1}^n 2^i$$

这时可以用上我们小学奥数的知识，这个式子就可以变为

$$2^{n+1}-2$$

这时候我们就可以省掉 for 循环力！

#### Code 2

```cpp
#include <bits/stdc++.h>

using namespace std;

long long binpow (long long b, long long p) {
	long long res = 1;
	while (p > 0) {
		if (p & 1)
			res = res * b;
		b = b * b;
		p >>= 1;
	}
	return res;
}

int main () {
	long long n;
	scanf("%lld", &n);
	printf("%lld", binpow(2, n + 1) - 2);
	return 0;
}
```

预测得分：$100$ 分。

[AC Record](https://www.luogu.com.cn/record/36460467)

By Shuchong       
2020.8.6

---

## 作者：逃课小姐MS (赞：5)

实际上是一只水题

递推的思想很明显啊

想着一个数里面只可以有 $7$ 和 $8$，根据乘法原理：

一位数的情况：$7$ 和 $8$.

那两位数的情况就是在一位数的情况前面添上一个$7$ 或者是 $8$，那就是$2*2=4$种情况.

后面的三位数四位数一直到n位数同理 就把他们加起来就可以了qwq

view code
```
#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll ans[100];
ll n;
int main(){
    ans[1]=2;
    cin>>n;
    for(int i=2;i<=55;++i) ans[i]=pow(2,i)+ans[i-1];
    cout<<ans[n]<<endl;
    return 0;
}
```

然后 我们来一波优化：
```
#include<bits/stdc++.h>
using namespace std;
int main(){
    long long n;
    cin>>n;
    cout<<pow(2,n+1)-2<<endl;
    return 0;
}
```
然后就壮烈牺牲了 因为pow对付不了ll类型的数

所以说 我们的最终优化版本如下qwq（也没有优化多少

```
#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll n,ans=2,sum=0;
int main(){
    cin>>n;
    for(int i=2;i<=n;i++) sum+=ans,ans=ans*2;
    sum+=ans;
    cout<<sum<<endl;
    return 0;
}
```

---

## 作者：Aw顿顿 (赞：2)

[博客更多有趣的知识，欢迎前来观看qwq](https://www.luogu.com.cn/blog/AlanWalkerWilson/)

这道题我们可以利用乘法原理：

乘法原理：

https://baike.baidu.com/item/%E4%B9%98%E6%B3%95%E5%8E%9F%E7%90%86/7538447?fr=aladdin

摘出来/修改最经典的一句：

> 完成一件事需要 $n$ 个步骤，第一步有 $m_1$ 种不同的方法，第二步有 $m_2$ 种不同的方法，第 $i$ 步有 $m_i$ 种不同的方法。

> 那么完成这件事共有 $m_1\times m_2\times\cdots\times m_n$ 种不同的方法。 

- 每一位都可以有两种选择 $7$ 或者 $8$。

- 每一位都有 $2$ 中情况。

那么每一位的数字都影响着接下来这一位的数字，所以，他们要相乘。

那么，每一步都有 $2$ 中，$n$ 步就有 $n$ 个 $a$ 相乘。

那我们很容易就能得知其**每一步的**总方案数是 $2^n$ 种。

然后我们推及整个数列：

$$S=2+2^2+2^3+\cdots+2^n$$

$$2S=2^2+2^3+2^4+\cdots+2^{n+1}$$

$$2S-S=2^{n+1}-2$$

这就是经典的**等比数列求和**。



我们此处还需要知道一个知识：快速幂。

> 顾名思义，快速幂就是快速算底数的 $n$ 次幂。其时间复杂度为 $\operatorname{O(logn)}$ ， 与朴素的 $\operatorname{O(n)}$ 相比效率有了极大的提高。

其代码为：
```
long long quickpow(long long a,long long b){
    long long s=1;
    while(b){
        if(b&1)s=(s*a)%mod;
        a=(a*a)%mod;
        b>>=1;
    }
    return s%mod;
}
```
当中的核心思想就是：

$$a^n=a^{n\div2}\times a^{n\div2}$$

这样，本来 $n$ 次循环乘法就被优化为 $log_2\ n$ 次循环。

其中我们需要了解 `b&1` 相当于 `b%2`。

通常的快速幂是要取模的，但是这个快速幂不需要。

所以代码就是：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n;
long long qp(long long a,long long b){
    long long s=1;
    while(b){
        if(b&1)s=(s*a);
        a=(a*a);
        b>>=1;
    }
    return s;
}
int main(){
    cin>>n;
    cout<<qp(2,n+1)-2<<endl;
    return 0;
}
```

为了证明此代码可以AC，提交记录：https://www.luogu.com.cn/record/32371648

谢谢大家的观看，希望对大家有用qwq。

---

## 作者：BotDand (赞：1)

# Problems
给定数字位数，即这个数的位数要**小于或者等于它**，且这个数字**只能由7和8**组成，问有多少种情况。
# Answer
因为只能由7和8组成，所以每位就有两种情况：**7或8**。

所以$x$位就有$2^{x+1}$种情况。

又因为题目中给出了这个数的位数要**小于或者等于它**，则答案就是$2^2+2^3+...+2^{n-1}+2^n$。
# Code
```cpp
var
  n,x,s:int64;//定义大一点
  i:longint;
begin
  readln(n);
  x:=2;//初始值
  for i:=1 to n-1 do//乘到n
    begin
      s:=s+x;//加上当前的值
      x:=x*2;//乘以2，为下一个做准备
    end;
  writeln(s);//输出s
end.
```

---

## 作者：wshl (赞：0)

题解：~~这题真难！！！~~
- 一个数里面只可以有$7$和$8$，且位数不能超过$n$，问有多少种情况。
- 明显位数是$n$的总个数是$2*2^{n-1}$，总数把所有的加上即可。

```
#include<iostream>
#include<algorithm>
using namespace std;
int n;
long long pow(int x)
{
    if(x==0)return 1;
    else return 2*pow(x-1);
}
int main()
{
    cin>>n;
    cout<<pow(n+1)-2;
    return 0;
}
```

---

## 作者：xiaohuang (赞：0)

[更好的阅读体验](https://xiaohuang888.github.io/2019/12/11/%E3%80%8CCF630C%E3%80%8DLucky%20Numbers/)

### Solution

题目要我们构造$1 \sim n$位由$7, 8$的数的个数。我们先来找一找规律：

位数为$1$时：有$7, 8$，共$2 \times 2 ^ 0 = 2$种；

位数为$2$时：有$77, 78, 87, 88$，共$2 \times 2 ^ 1 = 4$种；

位数为$3$时：有$777, 778, 787, 788, 877, 878, 887, 888$共$2 \times 2 ^ 2 = 8$种；

$\cdots \cdots$

所以，位数是$n$的总个数是$2 \times 2 ^ {n - 1}$；

那么位数为$1 \sim n$的总个数为

$$\begin{aligned} \sum^{n}_{i = 1}{2 \times 2 ^ {i - 1}} & = 2 \times \sum^{n}_{i = 1}{2 ^ {i - 1}} \\ & = 2 \times (2 ^ {n} - 2) \\ & = 2 ^ {n + 1} - 2\end{aligned}$$

于是就解决了。

### Code

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<cmath>

using namespace std;

typedef long long LL;
LL n;
inline LL power(LL x, LL y) {//求x的y次方
    LL ret = 1;
    for (LL i = 1; i <= y; i++)
        ret *= x;
    return ret;
}
int main() {
    scanf("%lld", &n);
    printf("%lld\n", power(2, n + 1) - 2);//推出来的公式
    return 0;
}
```

---

## 作者：wangjinbo (赞：0)

# 这个水题……
普及组t1难度
废话不多说先举报一波恶意评分
~~~~
##### 下面是正式部分
思路：n位数可能性为pow（2，n）
所以全部加起来是pow(2,n+1)-2
因为pow到不了long long所以自己写函数
~~~~
# 代码：
```cpp
#include<iostream>
using namespace std;
long long pow（int x）
{
    if(x==0) return 1;
    else return 2*pow(x-1);//递归
}
int main()
{
	int n;
	cin>>n;
	cout<<pow(n+1)-2;
    while(1);
	return 0;
}
```
代码有彩蛋抄袭请当心


---

## 作者：CZQ_King (赞：0)

题意：
```
长度在小于等于n只包含7或8的字符串的个数是多少
```

------------
做法：

当长度为$x$的字符串，有$2^x$种方法。

证明：第一位放$7$或$8$有两种，第二位也是可以放$7$或$8$，也是两种$\dots$以此类推到第$x$位，那么方法数就是$x$个$2$相乘，即$2^x$。

然后我们只需要列举出从$1$到$n$的方法总和就可以了：

$$ans=2^1+2^2+\dots+2^n$$

等比数列，直接套公式：

$$a^0+a^1+a^2+\dots+a^n=\frac{a^{n+1}-1}{a-1}$$

那么$ans=2^{n+1}-2$。

正好$py$自带次方运算（``a**b``代表$a^b$），而且根本不用担心高精度，代码还能超短，岂不美哉！

------------
$Python3$代码：
```python
print(2**int(input())*2-2) # 等价于2**(int(input())+1)-2，只是这样代码会短一点
```

~~但是看着我那927ms的速度，我就笑了~~

---

## 作者：DPair (赞：0)

### 弱弱的说一句，为什么想做CF紫题碰到的都是水题啊！

## 【题意】
这个翻译有些不太清楚，我这么说吧。

题目会给你一个位数，问你有多少个位数小于等于给定位数，且只含$7$和$8$的数。

## 【做法】
这不是很简单吗！！！

先假设一个数有$n$位。

每一位有$7$和$8$两种可能。

因此总共是$2^n$种可能。

然后我们要求$\sum_{i=1}^{n}{2^i}$，设$S=\sum_{i=1}^{n}{2^i}$


然后我们知道$2S=\sum_{i=2}^{n+1}{2^i}$

所以$2S-S=\sum_{i=2}^{n+1}{2^i}-\sum_{i=1}^{n}{2^i}=2^{n+1}-2$

然后快速幂搞一下就好了（不知道为什么楼下没有写快速幂。。。）

## 【代码】
```cpp
#include <bits/stdc++.h>
using namespace std;
#define LL long long

LL ksm(LL x, LL y)
{
    LL ret = 1, tmp = y;
    while(tmp > 0)
    {
        if(tmp & 1) ret = (ret * x);
        x = (x * x);
        tmp >>= 1;
    }
    return ret;
}
LL n;
int main()
{
    cin >> n;
    cout << ksm(2, n + 1) - 2;
}
```

`p.s.水的一批`

---

