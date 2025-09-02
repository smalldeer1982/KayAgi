# Random Teams

## 题目描述

 $ n $ participants of the competition were split into $ m $ teams in some manner so that each team has at least one participant. After the competition each pair of participants from the same team became friends.

Your task is to write a program that will find the minimum and the maximum number of pairs of friends that could have formed by the end of the competition.

## 说明/提示

In the first sample all the participants get into one team, so there will be exactly ten pairs of friends.

In the second sample at any possible arrangement one team will always have two participants and the other team will always have one participant. Thus, the number of pairs of friends will always be equal to one.

In the third sample minimum number of newly formed friendships can be achieved if participants were split on teams consisting of $ 2 $ people, maximum number can be achieved if participants were split on teams of $ 1 $ , $ 1 $ and $ 4 $ people.

## 样例 #1

### 输入

```
5 1
```

### 输出

```
10 10
```

## 样例 #2

### 输入

```
3 2
```

### 输出

```
1 1
```

## 样例 #3

### 输入

```
6 3
```

### 输出

```
3 6
```

# 题解

## 作者：云浅知处 (赞：7)

本题考数学，难度不高。

[更好的阅读体验？](https://www.luogu.com.cn/blog/wwwluogucn/solution-cf478b)
***
首先，如果一个组中有$x$人，那么这个组中朋友的组数就是$\text{C}^2_x=\dfrac{x(x-1)}{2}$。

假设一共分为$k$组，共有$n$人，每一组中的人数分别为$a_1,a_2,a_3,\dots,a_{k-1},a_k$，则朋友的组数为：

$$\quad\dfrac{a_1(a_1-1)}{2}+\dfrac{a_2(a_2-1)}{2}+\dfrac{a_3(a_3-1)}{2}+\cdots+\dfrac{a_{k-1}(a_{k-1}-1)}{2}+\dfrac{a_k(a_k-1)}{2}$$

$=\dfrac{a_1(a_1-1)+a_2(a_2-1)+a_3(a_3-1)+\cdots+a_{k-1}(a_{k-1}-1)+a_k(a_k-1)}{2}$

$=\dfrac{a_1^2+a_2^2+a_3^2+\cdots+a_{k-1}^2+a_k^2-a_1-a_2-a_3-\cdots-a_{k-1}-a_k}{2}$

$=\dfrac{a_1^2+a_2^2+a_3^2+\cdots+a_{k-1}^2+a_k^2-(a_1+a_2+a_3+\cdots+a_{k-1}+a_k)}{2}$

又，由题意知：$a_1+a_2+a_3+\cdots+a_{k-1}+a_k=n$，为定值。

所以问题转化为求$a_1^2+a_2^2+a_3^2+\cdots+a_{k-1}^2+a_k^2$的最大值与最小值。
***
先看最小值。

由柯西不等式得：

$$(a_1^2+a_2^2+a_3^2+\cdots+a_{k-1}^2+a_k^2)(\begin{matrix}\underbrace{1^2+1^2+1^2+\cdots+1^2+1^2}\\\text{k个}1^2\end{matrix})\geqslant(a_1+a_2+a_3+\cdots+a_{k-1}+a_k)^2$$

（不明白柯西不等式的同学可以自己[百度](https://baike.baidu.com/item/柯西不等式)，这里由于篇幅的原因就不赘述了。）

即

$$k(a_1^2+a_2^2+a_3^2+\cdots+a_{k-1}^2+a_k^2)\geqslant n^2$$

移项，得

$$(a_1^2+a_2^2+a_3^2+\cdots+a_{k-1}^2+a_k^2)\geqslant \dfrac{n^2}{k}$$

故$a_1^2+a_2^2+a_3^2+\cdots+a_{k-1}^2+a_k^2$的最小值为$\dfrac{n^2}{k}$。

此时原式的值为$\dfrac{\frac{n^2}{k}-n}{2}=\dfrac{n^2-kn}{2k}=\dfrac{n(n-k)}{2k}$

故朋友的组数最小为$\left\lceil\dfrac{n(n-k)}{2k}\right\rceil$（向上取整是因为人数必须是正整数）。
***
再看最大值。

实际上，如果把这个问题当作一个纯粹的数学问题来研究，最大值应该是无穷大。不过在这里，由于人数只能是正整数，所以还是可以有最大值的，只不过比较不好叙述。

现在我们一起来考虑一个事情：函数$f(x)=x^2$的增长速度。

学过导数的同学应该知道，函数$f(x)=x^2$的导数应该是$2x$，也就是说，$x$越大，此函数增长的就越快。

如果没学过导数，没关系，跟我来！

“增长速度”这个名词，现阶段我们可以理解为$f(x+1)-f(x)$的值，也就是$x$每增大$1$，$f(x)$的函数值所增大的值。

照这样理解，函数$f(x)=x^2$的增长速度应该是：

$\quad(x+1)^2-x^2$

$=(x+1-x)(x+1+x)\qquad\qquad$    （平方差公式）

$=2x+1$

因此，如果$x$是一个很大的值，那么$f(x+1)$比$f(x)$多的值也会很大；反之，如果$x$是一个比较小的值，那么$f(x+1)$比$f(x)$多的值也会很小。

所以，$x$越大，此函数增长的就越快。

那这个结论和这道题有什么关系呢？**关系大了！**

我们现在要求出对于$a_i\in \mathbb{N}^+$，且$a_1+a_2+a_3+\cdots+a_{k-1}+a_k=n$，为定值的时候$a_1^2+a_2^2+a_3^2+\cdots+a_{k-1}^2+a_k^2$的最大值。

由之前的结论，我们知道，对于每一个$a_i^2$，都有$a_i$越大，$a_i^2$增长的越快。

那么，我们完全可以**使其中的一个数尽可能的大，其余的数尽可能地小啊！**（比如其余的数都是$1$）

这样，我们就可以构造出最大值了。

证明如下：

假设此时$a_1=a_2=a_3=\cdots=a_{k-2}=a_{k-1}=$（一个很小的值），$a_k=$（一个很大的值）

如果我们给$a_1,a_2,\dots,a_{k-1}$中的任意一个数加上$x$，则由于$a_1+a_2+a_3+\cdots+a_{k-1}+a_k=n$，为定值，那么$a_k$必须减去$x$。

假设给$a_1,a_2,\dots,a_{k-1}$中的任意一个数加上$x$将会导致$a_1^2+a_2^2+a_3^2+\cdots+a_{k-1}^2+a_k^2$增加$p$。

将$a_k$减去$x$导致$a_1^2+a_2^2+a_3^2+\cdots+a_{k-1}^2+a_k^2$减少$q$。

那么，由之前的结论，我们知道：**$p$一定小于$q$！**

这是因为$a_1,a_2,\dots,a_{k-1}$中的任意一个数都远远小于$a_k$，所以加上$x$后增长的值一定小于$a_k$减去$x$之后减少的值。

所以代数式$a_1^2+a_2^2+a_3^2+\cdots+a_{k-1}^2+a_k^2$增加了$p$又减少了$q$，减少的比增加的多，显然此时$a_1^2+a_2^2+a_3^2+\cdots+a_{k-1}^2+a_k^2$变小了。

所以说仅有当$a_1=a_2=a_3=\cdots=a_{k-2}=a_{k-1}=$（一个很小的值），$a_k=$（一个很大的值）的时候，原式有最大值。

在本题中就是$a_1=a_2=a_3=\cdots=a_{k-2}=a_{k-1}=1$，$a_k=n-k+1$的时候，原式有最大值。

此时原式的值为：

$\quad\dfrac{a_1^2+a_2^2+a_3^2+\cdots+a_{k-1}^2+a_k^2-(a_1+a_2+a_3+\cdots+a_{k-1}+a_k)}{2}$

$=\dfrac{\begin{matrix}\underbrace{1^2+1^2+1^2+\cdots+1^2+1^2}\\\text{k-1个}1^2\end{matrix}+(n-k+1)^2-n}{2}$

$=\dfrac{k-1-n+(n-k+1)^2}{2}$

$=\dfrac{(n-k+1)^2-(n-k+1)}{2}$

$=\dfrac{(n-k+1)(n-k)}{2}$

（特别地，这里不需要取整，原因是$n-k+1$和$n-k$中必定有一个偶数。）
***
需要注意的是，我们需要特判$n<k$的情况。
***
至于代码，就不贴了，在明白了以上知识以后，写出一篇AC代码是很容易的啦～～

$\text{The end}$

---

## 作者：_Katyusha (赞：1)

#### 结论

把人全部集中到一个队朋友对数最大，均分朋友对数最小。

#### 证明

数学归纳法。考虑只有两个队，一个队人数为 $a$，另一个队人数为 $b$，则此时朋友对数为 $\frac{a\times (a-1)}{2}+\frac{b\times(b-1)}{2}$，把人数集中为一个队，则一个队为 $a+b-1$ 人，另一个队为 $1$ 人。此时朋友对数为 $\frac{(a+b)\times(a+b-1)}{2}$。展开：
$\frac{a^2+b^2+2ab-a-b}{2}$，拆分开来的对数为 $\frac{a^2+b^2-a-b}{2}$。显然有：

$$\frac{a^2+b^2+2ab-a-b}{2}>\frac{a^2+b^2-a-b}{2}$$

所以全部集中到一个队最优，均分人数最少。

#### 思路

有了结论就很简单了。最大值就是给其他 $m-1$ 个队一个人，剩下的队 $n-m+1$ 个人，答案就是 $\frac{(n-m+1)\times (n-m)}{2}$ 即为最大值。

最小值可以均分。先给每个队 $\left\lfloor{\frac{n}{m}}\right\rfloor
$ 人，则总朋友对数为 $\frac{m\times(\left\lfloor{\frac{n}{m}}\right\rfloor
-1)\times \left\lfloor{\frac{n}{m}}\right\rfloor}{2}
$，然后给 $n\bmod m$ 个队中各加一个人，增加的朋友对数为 $(n\bmod m)\times \left\lfloor{\frac{n}{m}}\right\rfloor$，所以最小值为 $ \frac{m\times(\left\lfloor{\frac{n}{m}}\right\rfloor
-1)\times \left\lfloor{\frac{n}{m}}\right\rfloor}{2}+(n\bmod m)\times \left\lfloor{\frac{n}{m}}\right\rfloor $。

#### 代码

```cpp
#include <bits/stdc++.h>
#define int long long 
#define MAXN 200000

using namespace std;

const int mod = 1e9 + 7;


signed main() {
	int n, m;
	cin >> n >> m;
	cout << m * (n / m) * (n / m - 1) / 2 + (n / m) * (n % m) << ' ';
	cout << (n - m + 1) * (n - m) / 2;
	return 0;	
}
```

---

## 作者：wzhcsl (赞：1)

首先，如果有一个组里有n个人，那么这一组里的朋友对数为$n*(n-1)/2$，我们考虑怎样划分可以得到最小值和最大值。

我们先来看最小值。

有点类似于找次品一类问题的思想，让每一组人数尽可能平均，可以得到最小值。

然后再来看最大值。

手推几组数据可以发现，当某一组人数越多时答案会越大。所以我们可以把前$m-1$组的人数都设为$1$，最后一组的人数设为$n-m+1$，这样可以得到最大值。

```cpp
#include <iostream>
using namespace std;
long long n, m, ans1, ans2;//注意要开long long 
long long calc(long long x) {//计算朋友对数 
	return x * (x - 1) / 2;
}
int main() {
	cin >> n >> m;
	if (n < m) {//特判 
		cout << 0 << " " << 0 << endl;
		return 0;
	}
	long long k = n % m;
	ans1 += k * calc(n / m + 1) + (m - k) * calc(n / m);//计算最小值 
	ans2 = calc(n - m + 1);//计算最大值 
	cout << ans1 << " " << ans2 << endl;
	return 0;
}
```


---

## 作者：Meatherm (赞：1)

如果要求最大，那么我们可以把前 $m-1$ 组的人数设为 $1$ ，而把第 $m$ 组的人数设为 $n-m+1$。

如果要求最小，那么我们可以把人数平均分——注意可能 $m \nmid n$ ，这个时候要处理余数。

怎么处理余数才能使人数尽可能平均呢？

令前 $n \mod m$ 组的人数为 $\left \lfloor n/m \right \rfloor+1$，剩下的组人数为 $\left \lfloor n/m \right \rfloor$。


```
# include <bits/stdc++.h>
# define rr register
# define int long long//注意要使用64位整数
int n,m;
inline int sum(int x){//计算 (1+2+...+x)
	return (1+x)*x/2;	
}
signed main(void){
	scanf("%I64d%I64d",&n,&m);
	printf("%I64d %I64d",n%m*sum(n/m)+(m-n%m)*sum(n/m-1),sum(n-m));//注意：一个x人组的朋友对数为 \sigma_{1}^{x-1}
	return 0;
}
```

---

## 作者：LouYiYang1 (赞：0)

我们先来看最小值。

有点类似于找次品一类问题的思想，让每一组人数尽可能平均，可以得到最小值。

然后再来看最大值。

手推几组数据可以发现，当某一组人数越多时答案会越大。所以我们可以把前 $m-1$ 组的人数都设为 $l$ ，最后一组的人数设为 $n-m+1$ ，这样可以得到最大值。


## AC Code

```cpp
#include <bits/stdc++.h>
using namespace std;
long long n, m;
long long f(long long x) {
	return x * (x - 1) / 2;
}
int main() {
	cin >> n >> m;
	if (n < m) {
		cout << 0 << " " << 0 << endl;
		return 0;
	}
	long long k = n % m;
	cout << k * f(n / m + 1) + (m - k) * f(n / m) << " " << f(n - m + 1) << endl;
	return 0;
}
```

---

## 作者：fish_gugu (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/CF478B)


---
## 思路

这一题无非就是一道组合排列的数学题。



#### 最大朋友对数：
为了使朋友对数最大，我们应该尽量让一组的人数远大于其他组。最优策略是将 $n − m + 1$ 个人放入一个组，其余 $m − 1$ 组各放一个人。
这样，最大的朋友对数为 $C^2_{n - m + 1} + (m − 1)×C^2_1$（但 $C^2_1=0$，因为一个人不能和自己成为朋友）。


#### 最小朋友对数：
为了使朋友对数最小，我们应该尽量让各组的人数接近，即尽量平均分配。


- 假设 $n$ 可以被 $m$ 整除，则每组有 $\frac{n}{m}$ 人，总朋友对数为 $m \times C^2_{\frac{n}{m}}$。

  

- 如果 $n$ 不能被 $m$ 整除，则前 $n \bmod m$ 组每组有 $\left\lfloor{\frac{n}{m}}\right\rfloor + 1$ 人，其余组每组有 $\left\lfloor{\frac{n}{m}}\right\rfloor$ 人。

  

## 代码


```cpp
#include <bits/stdc++.h>  
using namespace std;  
   
long long comb(long long n) 
{  
    return n * (n - 1) / 2;  
}  
   
void minMaxFriends(long long n,long long m,long long& minF,long long& maxF) 
{  

    // 计算最小情况  
    long long perGroup = n / m;  
    long long extra = n % m;  
    minF = 0;  
    for(long long i = 0;i < m;i++) 
	{  
        if (i < extra) minF += comb(perGroup + 1);   
		else minF += comb(perGroup);   
    }  
    
    // 计算最大情况  
    maxF = comb(n - m + 1);  
}  
  
int main() 
{  
    long long n,m;  
    cin >> n >> m;  
	long long min,max;  
    minMaxFriends(n,m,min,max);  
    cout << min << " " << max; 
	return 0;  
}
```

---

## 作者：IGA_Indigo (赞：0)

## 题目大意
就是像题目所说的那样分组找朋友，求出最小朋友对数和最大朋友对数。
## 大体思路
纯数学题啊这，我们来分析一下：

众所周知有几对这种的公式是 $n\times (n-1)\div 2$。

若想要对数尽量少，那每一组的人尽量少，那就是说每一组人尽量平均分，先平均，剩下的余数每组一个，那就有 $n\div m$ 人和 $n\div m+1$ 两种队伍了，所以：

$minn=m\times(n\div m)\times(n\div m-1)\div 2+(n\div m)\times(n\bmod m)$。

若想要对数尽量多，那尽量都放一组，那就是先都放一个人，然后把所有人塞一个组里，所以：

$maxx=(n-m+1)\times(n-m)\div 2$。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std; 

int main(){
	long long n,m;
	cin>>n>>m;
	long long minn=m*(n/m)*(n/m-1)/2+(n/m)*(n%m);
	long long maxx=(n-m+1)*(n-m)/2;
	cout<<minn<<" "<<maxx;
	return 0;
}
```

---

## 作者：zhujiangyuan (赞：0)

[CF478B Random Teams](https://www.luogu.com.cn/problem/CF478B)

结论题，难度不高。

首先根据经验以及观察样例可以猜到：
- 要使答案最小，需要尽可能平均分配。
- 要使答案最大，需要 $m-1$ 个组每组 $1$ 个人，$1$ 个组 $n-m+1$ 个人。

那么这个结论是否正确呢？

考虑只有两个组，一个组 $a$ 人，一个组 $b$ 人，令 $a>b\ge2$。则现在的朋友数量为 $\dfrac{a(a-1)+b(b-1)}{2}$。

如果从第一个组中抽一个人给第二个组，则朋友数量变为 
$$\dfrac{(a-1)(a-2)+b(b+1)}{2}=\dfrac{a^2-3a+2+b^2+b}{2}=\dfrac{a(a-1)+b(b-1)-2a+b+2}{2}$$

又因为要求 $a>b\ge2$，所以 $-2a+b+2<0$，所以平均分配人答案最小，把人集中到一个组答案最大。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
typedef long long LL;
const int N = 1e6 + 10;
int n, m, ans1, ans2;
signed main () {
	ios::sync_with_stdio (false);
	cin.tie (0); cout.tie (0);
	
	cin >> n >> m;
	int x = n / m;
	if (n % m) ans1 += (n % m) * (x + 1) * x / 2;
	ans1 += (m - n % m) * x * (x - 1) / 2;
	int p = n - (m - 1);
	ans2 = p * (p - 1) / 2;
	cout << ans1 << ' ' << ans2;
	return 0;
}
```

---

## 作者：LiJinLin_AFO (赞：0)

# CF478B 题解
这是一道数学题。

首先来看最小值。最小值，意味着我们要将这些选手尽量平分。

然后看最大值。和最小值相对，前 $n-1$ 组越少越好，其他全在最后，就是最大值。

具体细节见代码。

```cpp
#include <stdio.h>
long long n, m, ans1=0, ans2=0;
long long ex1(long long x) {
	return x * (x - 1) >> 1;
}//朋友有多少对
int main() {
	scanf("%lld%lld",&n,&m);
	if (n < m) {//没有答案，输出0 0
		printf("0 0");
		return 0;
	}
	long long k = n % m;
	ans1 += k * ex1(n / m + 1) + (m - k) * ex1(n / m);//最小值 
	ans2 = ex1(n - m + 1);//最大值 
	printf("%lld %lld",ans1,ans2);
	return 0;
}
```


---

## 作者：_Kouki_ (赞：0)

### 题目思路：
#### 最小可能：    
**尽量让每组人数相对平均**。      
平均人数为 $ n \div m $ ，但是要注意**不是整除**的时候要让剩下的数给每组分配。     
假设剩下  $ x $  人，将组数 $1∼x$ 每位 $+1$。  

#### 最大可能：
这就相对比较简单了！   
**尽量让所有人都在一组**。  
让第一组有 $ n-m+1 $ 人，剩下的 $ m-1 $ 组，每组 1    人。     

### 题目要点：
**一定要开** long  long 。

### 题目代码：

```cpp
#include<bits/stdc++.h>//万能头
using namespace std;
typedef long long ll;
ll n,m;//人数和组数
int main()
{
    scanf("%lld%lld",&n,&m);//输入
    /*
     * 最小可能
    */
    ll tmp=n/m;//每组尽量平均
    ll ele=n-tmp*m;//还剩下多少！
    printf("%lld ",tmp*(tmp-1)/2*(m-ele)+(tmp+1)*tmp/2*ele);//平均的和非平均的
    /*
     * 最大可能
    */
    printf("%lld\n",(n-m+1)*(n-m)/2);//尽量分在一组内！
    // cin>>n;
    return 0;
}
```

---

