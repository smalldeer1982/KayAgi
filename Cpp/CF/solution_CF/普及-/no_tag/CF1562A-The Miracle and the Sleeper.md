# The Miracle and the Sleeper

## 题目描述

You are given two integers $ l $ and $ r $ , $ l\le r $ . Find the largest possible value of $ a \bmod b $ over all pairs $ (a, b) $ of integers for which $ r\ge a \ge b \ge l $ .

As a reminder, $ a \bmod b $ is a remainder we get when dividing $ a $ by $ b $ . For example, $ 26 \bmod 8 = 2 $ .

## 说明/提示

In the first test case, the only allowed pair is $ (a, b) = (1, 1) $ , for which $ a \bmod b = 1 \bmod 1 = 0 $ .

In the second test case, the optimal choice is pair $ (a, b) = (1000000000, 999999999) $ , for which $ a \bmod b = 1 $ .

## 样例 #1

### 输入

```
4
1 1
999999999 1000000000
8 26
1 999999999```

### 输出

```
0
1
12
499999999```

# 题解

## 作者：Dry_ice (赞：8)

> 个人估计橙题左右。

昨晚打了 $5$ 分钟cf，切了这道**数学题**。

## 题目简述（我的翻译）
$t$ 组数据。每组数据给定正整数 $l$ 和 $r$，在该范围内任取 $2$ 个整数 $a$ 和 $b$（满足 $l\leq a\leq b\leq r$），求 $b\mod a$ 的最大值。

## 思路
在 $l$ 到 $r$ 的范围内取二数相模的最大值，根据数据范围 $1\leq l\leq r\leq 10^9$，显然我们得考虑数学方法。暴力枚举的部分分（虽然在cf上拿不到）在这里就不讲了。

要使模数最大，当然 $b=r$，因为对于任何 $b<r$ 的最优解，其解必定小于 $b=r$ 的最优解。

接下来我们只用考虑 $a$ 就行，想一想显然 $a$ 取到 $b$ 的一半时模数最大，但是这里的**一半**要细分一下。

### 结论
对于 $b=r$ 为偶数，$a=\frac{b}{2}+1$ 时模数最大；对于 $b=r$ 为奇数，$a=\frac{b+1}{2}=\lfloor \frac{b}{2} \rfloor+1$ 时模数最大。

### 证明
可以想到，当 $b=r$ 为偶数时，若取 $a\leq \frac{b}{2}$，则 $\lfloor \frac{b}{a} \rfloor$ 一定不小于 $2$，这点非常显然，因为 $a\leq \frac{b}{2}$，所以有 $2a\leq b$，进而得到 $\lfloor \frac{b}{a} \rfloor\leq2$；当 $b$ 为奇数时，只需把原数减一即可也就是 $b=r-1$。那么可以发现使模数最大，必须 $a>\frac{b}{2}$。

当 $a>\frac{b}{2}$ 时，可以得到 $\lfloor \frac{b}{a} \rfloor =1$，此时模数即答案就是 $b-a$，那么要使解最大，由于 $b=r$（或 $r-1$）为定值，所以只要使 $a$ 最小即可，因为 $a>\frac{b}{2}$ 且为整数，所以 $a$ 最小取到 $\lfloor \frac{b}{2} \rfloor+1$ 就行。

为了优化常数，我们选择用 ```>>1``` 替代 ```/2```。

## CODE
```cpp
#include <stdio.h>
int a, b;
int main(void) {
    int t; for (scanf("%d", &t); t--; ) {
        scanf("%d %d", &a, &b); //读入
        if (a > (b >> 1)) printf("%d\n", b % a);
        else printf("%d\n", b % ((b >> 1) + 1));
        //代码直接用结论
    }
    return 0;
}
```

走过路过，~~必定赞过~~（owo

---

## 作者：little_cindy (赞：2)

[CSDN同步题解](https://blog.csdn.net/little_cindy_/article/details/119948817)
## 题意简述
给定 $t(1 \le t \le 10^4)$ 组 $l,r(1 \le l,r \le 10^9)$。请求出 $a \mod b(l \le a,b \le r)$ 的最大值。
## 思路
我们考虑每一次处理：

如题目所说，我们要求模数最大，一定是 $b-1$。所以 $a=r$ 时，$b$ 也能更大。

简单思考一下就可以发现：当 $b=\frac{a}{2}+1$时，答案可以取到最大值 $\frac{a}{2} -1$。

但是，题目里有个条件：$l \le b$，所以最小只能到 $l$。假如 $l>\frac{a}{2}+1$，那么 $b$ 只能取 $l$。所以 $a=r,b=\max{\begin{cases}l\\\frac{a}{2}+1\end{cases}}$。

没什么好说的了，上代码。

## code
```cpp
#include <bits/stdc++.h>
using namespace std;
int t, l, r;

int main() {
	cin >> t;
	while (t--) {
		cin >> l >> r;
		cout << r % max(r / 2 + 1, l) << '\n';
	}
	return 0;
}
```

---

## 作者：EnofTaiPeople (赞：2)

一道很好的入门题，考察知识点如下：

1. 最基础的数论（取模运算）；
2. 贪心算法。

AC 时间：5 分钟。

取模运算大家都了解，现在告诉大家如何贪心做。

引理一：对任意正整数 $n,m$，$m \le n$ 都有 $n \bmod m \le n-n/2-1$。

采用反证法：假设 引理不成立，则 $m\le (n-(n-n/2+1))=n/2-1\le n\bmod m$，不成立。故引理一成立。

于是，要求最大的取模值，应当先令 $a=r$，$b=l$。然后，若 $b<a/2+1$ 就让 $b=a/2+1$。

这是因为，若 $a/2+1\le b$,则 $a\bmod b=r-l$，没有更大值了；反之，由引理一可知，当 $n=a/2+1$ 时， $a\bmod b$ 取最大值为 $a-a/2+1$，很容易知道对任意 $a$ 以下的正整数 $c$，都有 $c-c/2+1\le a-a/2+1$故贪心策略成立。

AC 代码如下：
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
inline int read(){
	int an=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')f=-f;c=getchar();
	}while(c>='0'&&c<='9'){
		an=an*10+c-'0';c=getchar();
	}return an*f;
}
int ans[10005],i,T,l,r;
int main(){
	T=read();
	for(i=1;i<=T;++i){
		l=read();r=read();
		ans[i]=r%max(l,r/2+1);	
	}for(i=1;i<=T;++i)
		printf("%d\n",ans[i]);
	return 0;
}
```

---

## 作者：wssdl (赞：1)

**~~昨晚历经艰辛坎坷过了这道题，写篇题解纪念一下。~~**

# 题目大意

输入两个数分别为 $l$ 和 $r$ 让你从 $l$ 到 $r$ 的区间中选出两个数，分别为 $a$ 和 $b$ ，并且 $r\ge a\ge b\ge l$ 输出 $a\bmod b$ 的最大值。

# 解题思路

由于这一题的数据范围是： $1\le l\le r \le 10^9$ 所以我们直接暴力枚举 $a$ 和 $b$ 肯定会 $T$ 飞，所以我们想 $O(1)$ 的实现方法。

我们可以把这道题分成四种情况：

-  $l=r$ 时，这个区间只有一个数，无法选出两个数，所以直接输出 $0$ 。

我们知道在 $l$ 足够小的情况下，假设 $l=1$ ， $a$ 与 $b$ 最大的余数肯定是让除数 $b$ 尽可能大，同时 $a$ 也要尽可能大，所以 $a$ 就肯定是 $r$ ，为了使 $b$ 尽可能大， $a$ 要除以一个数，使 $b$ 与它的余数尽可能大，所以那个数必然是 $2$ 。

那我们就可以令 $tmp$ 为 $a\div 2$ 也就是 $r\div 2$ 的结果，然后我们分开判断。

-  $l<tmp$ 时，举个例子， $l=10,r=30,tmp=15$ 那么 $l$ 到 $r$ 之间最大的连个余数便是 $r$ 与 $r\div 2-1$，因为 $30$ 为偶数，如果 $b$ 直接等于 $30\div 2$ 是不行的，因为 $30$ 可以整除 $2$ 所以我们这里要用一个三目运算符输出，判断如果 $r$ 是奇数，可以直接输出 $tmp$ ，否则 $b$ 必须要 $+1$ 因为 $r$ 是偶数，换句话说，输出的是 $tmp-1$ 。

```cpp
 if (l < tmp) {
  cout << (r % 2 ? tmp : tmp - 1) << endl;
 } 
```

- $l=tmp$ 时，举个例子， $l=10,r=20,tmp=10$ 这时， $r$ 是偶数， $r$ 肯定可以整除 $l$ 所以为了让余数变大， $b$ 要等于 $l+1$ ，这样输出就是 $r-(l+1)$ 换个例子， $l=10,r=21,tmp=10$ ， $r$ 为奇数，那么为了要使 $l=tmp$ ，肯定 $l\times 2+1=r$ ，如果我们给 $l$ 加个 $1$ 那余数同时会减个 $1$ ，不会出现 $r$ 能整除 $l+1$ 的情况，所以 $r$ 为奇数时也输出 $r-(l+1)$ 。

```cpp
　else if (l == tmp) {
　　cout << r - (l + 1) << endl;
　}
```

- 否则的话为了让余数最大，肯定是 $a=r,b=l$ 是余数最大，因为 $l>tmp$ 所以 $r$ 无法整除 $l$ ，这时直接输出 $r-l$ 即可。

```cpp
　else {
　　cout << r - l << endl;
　}
```

# 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll t, l, r, tmp;
int main() {
  cin >> t;
  while (t--) {
    cin >> l >> r;
    if (l == r) {
      cout << 0 << endl;
      continue;
    }
    tmp = r / 2;
    if (l < tmp) {
      cout << (r % 2 ? tmp : tmp - 1) << endl;
    } else if (l == tmp) {
      cout << r - (l + 1) << endl;
    } else {
      cout << r - l << endl;
    }
  }
  return 0;
}
```

**祝愿洛谷越办越好 QWQ 。**

---

## 作者：Forever1507 (赞：1)

题目大概就是让你在一个给定区间里选两个数 $a,b$ 使 $a \bmod b$ 最大。

我们假设模数为 $s$，那么模数选定的同时答案最大值也确定了，即 $s-1$，那么，我们显然需要使 $s$ 接近被模数的二分之一，显然被模数为 $r$ 时最优，模数即为 $\frac{r}{2}+1$，此时答案为 $\frac{r}{2}-1$，显然是所有答案中最大的。

还有一个细节，就是模数不能小于 $l$，所以还要与 $l$ 取一个 $\max$。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,a,b; 
int main(){
	cin>>t;
	while(t--){
		cin>>a>>b;
		int ans=b/2+1;
		ans=max(ans,a);
		cout<<b%ans<<'\n';
	}
	return 0;
}
```


---

## 作者：jinxdtaiy (赞：0)

### 题意简述

- 给定一段区间，在区间内取两个数，使得两数取模运算得到的结果最大，其中，被除数必须大于除数。

### 题目分析

- 作为这场比赛的签到题，蒟蒻认为还是有那么一点点难度的。对于区间 $[l,r]$，很明显，当 $l \times 2$ 比 $r$ 大的时候，直接选择 $r \equiv l$ 即可。其它情况我们的答案应该为 $（r+1）/ 2$，这在其它题解中已经给出了详细证明，这里就不多赘述了。

### 代码

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,l,r;
inline int solve(int l,int r)
{
	if((l<<1)>r) return r%l;
	else return (r+1)/2;
}
signed main()
{
	cin>>t;
	while(t--)
	cin>>l>>r,cout<<solve(l,r)<<endl;
	return 0;
}
```

---

## 作者：hewo (赞：0)

#### 题目分析

假设确定了 $b$ ， 对于任意 $a<b$ ，我们可以分类讨论下：

1. $a<=\left \lfloor \frac{b}{2} \right \rfloor+1$

那么 $max(b \bmod a)=\left \lfloor \frac{b-1}{2} \right \rfloor$ ， 此时 $a=\left \lfloor \frac{b}{2} \right \rfloor+1$

换到 $(l,r)$ 的区间来想，$b$ 自然就是 $r$ ,只要 $l<=\left \lfloor \frac{r}{2} \right \rfloor+1$ , $ans=\left \lfloor \frac{b-1}{2} \right \rfloor$.

2. $a>\left \lfloor \frac{b}{2} \right \rfloor+1$

显然 $a$ 比 $b$ 的一半大了，自然 $max(b \bmod a)=b-a$

拓展到 $(l,r)$ 的区间来想， $b=r,a=l$ ， $b-a$ 才能足够大。

所以 $ans=r-l$

#### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

#define inf 0x7fffffff
#define LL long long
const int MX=5*30000+10;

inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}
    while (isdigit(ch)){x=x*10+ch-48;ch=getchar();}
    return x*f;
}

inline int solve(int l,int r)
{
	if(l<=(r/2+1)) return (r-1)/2;
	return r-l;
}

int main(int argc, char const *argv[])
{
	int T;
	T=read();
	while(T--)
	{
		int l,r;
		l=read(),r=read();
		printf("%d\n",solve(l,r));
	}	
	return 0;
}
```


---

## 作者：BotDand (赞：0)

# $\text{Problems}$

给出 $l$ 和 $r$，求一个数对 $(a,b)$，满足 $l \le b \le a \le r$，且满足 $a \mod b$ 的值最大，求这个最大值。

# $\text{Answer}$

不难发现对于一个数对 $(a,b)$，当 $b$ 为 $\left \lfloor \frac{a}{2} \right \rfloor +1$ 时 $a \mod b$ 最大。

如果此时的 $b \notin \left[l,r\right]$，则最大值为 $r-l$，证明显然。

综合可得答案为 $r-\max(\left \lfloor \frac{a}{2} \right \rfloor +1,l)$。

# $\text{Code}$

```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int l,r;
inline int read()
{
    int s=0,w=1;
    char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-')w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
    return s*w;
}
inline void write(int x)
{
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
inline void print(int x)
{
    write(x);
    putchar('\n');
}
inline void work()
{
    l=read();r=read();
    print(r-max(r/2+1,l));
}
int main()
{
    t=read();
    while(t--) work();
    return 0;
}
```


---

## 作者：luyiyang0830 (赞：0)

## 题目大意
------------
给定两个数 $l$ 和 $r$，需要找出两个数 $a$ 和 $b$，满足 $r\ge a\ge b\ge l$，且 $a\bmod b$ 的值最大，输出这个最大值。

## 思路
------------
首先因为 $a\bmod b$ 的值最大，所以 $a$ 尽可能大，最大为 $r$。又有一个性质：在所有比 $r$ 小的正整数中，与 $r$ 取模得到的值最大的数是 $\lfloor\frac{r}{2}\rfloor+1$，因此可以分两种情况考虑，当 $l\le \lfloor\frac{r}{2}\rfloor+1$ 时，则答案为 $r$ $\bmod$ $(\lfloor\frac{r}{2}\rfloor+1)=\lfloor\frac{r-1}{2}\rfloor$；当 $l>\lfloor\frac{r}{2}\rfloor+1$ 时，则答案为 $r$ $\bmod$ $l=r-l$。因此可以在 $O(1)$ 的时间复杂度内解决该题。

这里给一下上面用到的性质的证明：

设 $y=kx+b$（$k\ge 1,b<k$）。

$$\because k\ge 1,b<k$$
$$\therefore y=kx+b>b+b=2b$$
$$\therefore b<\frac{y}{2}$$
所以 $b$ 取最大值 $\lceil\frac{y}{2}\rceil-1$ 时，$x=\lfloor\frac{y}{2}\rfloor+1$，即与 $y$ 取模得到的值最大的数是 $\lfloor\frac{y}{2}\rfloor+1$。

## 代码
------------
```cpp
//上面已经讲过，就不放注释了
#include<bits/stdc++.h>
using namespace std;
int t,l,r;
int main(){
    cin>>t;
    while(t--){
        cin>>l>>r;
        if(r<l*2) cout<<r-l<<endl;
        else cout<<(r-1)/2<<endl;
    }
    return 0;
}
```

---

## 作者：LRL65 (赞：0)

### 题意：

给定两数 $l,r$ ，求两数 $a,b$ ，使得 $l\leq b \leq a \leq r$ ，且 $a\% b$ 最大。



------------
### 思路：

$a\% b $ 最大为 $b-1$ ，因为 $b\leq a$，此时 $a$ 最小为 $b+(b-1)=2b-1$ 。又因为 $a\leq r$ ，所以 $2b-1\leq r$ ，所以 $b\leq \frac{r+1}{2}$。

- 如果 $l>\frac{r+1}{2}$ ，那么 $a$ 取 $r$，$b$ 取 $l$。

- 否则，当 $r$ 为偶数时 $a=r-1$ ，为奇数时 $a=r$。**注意，要特判一下 $l=r$ 的情况。**


------------

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,l,r;
int main() {
    cin>>t;
    while(t--) {
        cin>>l>>r;
        int x=(r+1)/2;
        if(l==r)cout<<0<<endl;
        else cout<<max(r%max(x,l),(r-1)%max(x,l))<<endl;//懒得判奇偶，偷个懒qwq
    }
}
```


---

## 作者：int32 (赞：0)

## $\verb!Solution!$

考虑分类讨论。

答案最大的情况必定是在 $a=r,b=\lfloor\dfrac{r}2\rfloor+1$ 的时候取到。（商为 $1$，余数为 $\lfloor\dfrac{r-1}2\rfloor$）

当 $l>\lfloor\dfrac{r}2\rfloor+1$ 时，$ans=r\mod l=r-l$。

当 $l\leq\lfloor\dfrac{r}2\rfloor+1$ 时，$ans=\lfloor\dfrac{r-1}2\rfloor$。

## $\verb!Code!$

```cpp
#include<bits/stdc++.h>
using namespace std;
int T;
int l, r;
signed main(){
	cin>>T;
	while(T--){
		cin>>l>>r;
		if(r<l*2) cout<<r-l<<'\n';
		else cout<<(r-1)/2<<'\n';
	}
	return 0;
}
```

---

## 作者：reailikezhu (赞：0)

简单分类讨论。

首先考虑 $r$ 与 $2l$ 的关系。

如果 $r<2l$，那么输出 ${r}\ mod\ {l}$。

否则判断 $r$ 的奇偶性。

如果为偶，得数是 $r/2-1$。

正确性：若要使其更大，必然要有 $r/2+1$，超出了界限，故得数是 $r/2-1$。

如果为奇，得数是 $r/2$。

正确性：因为此处 $(r/2+1,2(r/2)+1)$ 没有越界。

代码：
```cpp
#include<stdio.h>

int t;
int l,r;

int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&l,&r);
		if(r>=2*l){
			if(r%2==0) printf("%d\n",r/2-1);
			else printf("%d\n",r/2);
		}
		else printf("%d\n",r%l);
	}
	return 0;
} 
```

---

## 作者：HerikoDeltana (赞：0)

## CF1562A The Miracle and the Sleeper

简单的签到题。

### 题意简述

给出区间 $[l,r]$，求满足 $l \le b \le a \le r$ 且使得 $a \bmod b$ 最大的 $a$ 和 $b$。

### 思路简述

我们考虑如何让 $a \bmod b$ 最大。

显然当 $a \le b$ 时，我们若想让 $a \bmod b$ 最大，就需要 $(a-b) \bmod b$ 最大。

那么我们要使 $a$ 最大，于是使 $a=r$。当 $r$ 为奇数时，$b=\left\lfloor\dfrac{r}{2}\right\rfloor$；当 $r$ 为偶数的时，$b=\dfrac{r}{2}-1$。

### Code

```cpp
#include <iostream>
#include <stdio.h>
#include <cmath>
#include <algorithm>
#include <cstring>
#define Heriko return
#define Deltana 0
#define Romanno 1
#define S signed
#define LL long long
#define R register
#define I inline
#define CI const int
#define mst(a, b) memset(a, b, sizeof(a))
#define ON std::ios::sync_with_stdio(false);cin.tie(0)
using namespace std;

template<typename J>
I void fr(J &x)
{
    static short f(1);
    char c=getchar();
    x=0;
    while(c<'0' or c>'9')
    {
        if(c=='-') f=-1;
        c=getchar();
    }
    while (c>='0' and c<='9') 
    {
        x=(x<<3)+(x<<1)+(c^=48);
        c=getchar();
    }
    x*=f;
}

template<typename J>
I void fw(J x,bool k)
{
    x<0?x=-x,putchar('-'):1;
    static short stak[35],top(0);
    do
    {
        stak[top++]=x%10;
        x/=10;
    }
    while(x);
    while(top) putchar(stak[--top]+'0');
    k?puts(""):putchar(' ');
}

int t;

S main()
{
    fr(t);
    while(t--)
    {
        LL l,r;
        fr(l),fr(r);
        if(l>(r>>1)) {fw(r%l,1);continue;}
        if(r&1) fw(r>>1,1);
        else fw((r>>1)-1,1);
    }
    Heriko Deltana;
}
```

---

## 作者：miserExist (赞：0)

### 题意
求两个数在 $l$ 到 $r$ 的区间中，大的数被小的数取模后余数的最大值是多少。

### 思路
遵循以上规则，一个数 $a$ 被 $(\dfrac{a}{2} + 1)$ 取模后剩余的数最大，此时的模运算相当于减法运算，$+1$ 是为了保证只被除一次，同时答案要对 $l$ 取最大值。

也就是答案为：
$$
 r - \max(l, \dfrac{r}{2} + 1)
$$

### 代码
```cpp
    #include<bits/stdc++.h>
    using namespace std;
    #define int long long
    signed main()
    {
     
        int t;
        cin >> t;
        while(t --)
        {
            int l,r;
            cin >> l >> r;
            
            cout << r - max(l, r / 2 + 1) << "\n";
        }
     
     
     
        return 0;
    }
```

---

## 作者：Chouquet (赞：0)

既然 $a \mod b$ 最大，那么 $a$ 越大越好，所以 $a$ 最大取 $r$。对于 $a \mod b$（$a > b$），有一个性质：

$$a \mod b < \frac{a}{2}$$

证明：

设 $a = kb + c$（$c$ 为余数，$b$ 为除数）。

$$\because k \ge 1, b > c$$

$$\therefore a > c + c$$

$$\therefore c < \frac{a}{2}$$

由于 $c$ 是整数，当 $c$ 取最大值 $\lceil \frac{a}{2} \rceil - 1$ 时，$b = \lfloor \frac{a}{2} \rfloor + 1$。如果 $l < b$，那么答案显然为 $\lceil \frac{a}{2} \rceil - 1$；否则答案一定是 $r \mod l$，因为模数越大越好。

代码：

```cpp
#include <cstdio>
int t, l, r;
int main() {
	scanf("%d", &t);
	while (t--) {
		scanf("%d%d", &l, &r);
		if (l == r)//这个判断可要可不要
			puts("0");
		else if (l < (r >> 1) + 1)//l<b的的情况
			printf("%d\n", (r - 1 >> 1));
		else//l>=b的情况
			printf("%d\n", r % l);
	}
	return 0;
}
```

---

