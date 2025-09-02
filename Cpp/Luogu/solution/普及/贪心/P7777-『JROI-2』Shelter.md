# 『JROI-2』Shelter

## 题目背景

And it's a long way forward        
So trust in me       
I'll give them shelter like you've done for me       
And I know, I'm not alone         
You'll be watching over us       
Until ...        

一个小女孩斜躺在一个驾驶舱的椅子上，长发从肩膀上飘落到地上。     
她的嘴角绽放出微笑，身旁的显示屏写着 “返回 第三行星”。       
她怀里的泰迪熊身上写着她的名字，Rin。

—— [Shelter](https://www.bilibili.com/video/BV1ys41147Gv)

---



## 题目描述

Rin 和爸爸还在地球上时，他们经常玩一个石子游戏。

爸爸摆出了 $n$ 堆石子，这 $n$ 堆石子编号为 $1$ 到 $n$。

游戏规则是这样的，每次 Rin 可以抓取石子，有两种抓取方式：

- 选择一个数 $i$，把第 $i$ 堆石子抓取走，代价为 $i \times p$。
- 选择两个数 $i,j$，把第 $i$ 堆和第 $j$ 堆石子抓走，代价为 $|i-j| \times q$。

其中 $p,q$ 为爸爸提前定好的常数。

Rin 想知道，抓取完所有石子至少需要多少代价。

还剩 1919810114514 秒第三行星的灾难就要降临了，爸爸还需要 1919810114513.7 秒的时间把 Rin 安放到驾驶舱里，并启动机器让 Rin 进入 “Shelter” 里，因此，你只有 0.3 秒的时间帮助 Rin 算出这个结果哦！

## 说明/提示

#### 样例 1 解释

第一组数据：

1. 利用第一个操作，拿走第 $1$ 堆石子，代价为 $1 \times 2=2$。
2. 利用第二个操作，拿走第 $2,3$ 堆石子，代价为 $|2-3| \times 3=3$。
3. 利用第二个操作，拿走第 $4,5$ 堆石子，代价为 $|4-5| \times 3=3$。

最小代价为 $2+3+3=8$。

第二组数据：

1. 利用第一个操作，拿走第 $1$ 堆石子，代价为 $1 \times 1=1$。
2. 利用第一个操作，拿走第 $2$ 堆石子，代价为 $2 \times 1=2$。
3. 利用第二个操作，拿走第 $3,4$ 堆石子，代价为 $|3-4| \times 5=5$。

最小代价为 $1+2+5=8$。

#### 数据规模与约定

**本题采用捆绑测试。**

- Subtask 1（1 pts）：$p,q =0$。
- Subtask 2（1 pts）：$n=1$。
- Subtask 3（30 pts）：$T \le 5 \times 10^4$，$n \le 5 \times 10^5$。
- Subtask 4（33 pts）：$T \le 10^6$，$n \le 5 \times 10^5$。
- Subtask 5（35 pts）：无特殊限制。

对于 $100\%$ 的数据，$1 \le n \le 10^9$，$0 \le p,q \le 100$，$1 \le T \le 10^6$。

附件中的 Extra Example 满足 $T=10^4$，可供调试使用。


-----
Source：[JROI-2 Summer Fun Round](https://www.luogu.com.cn/contest/30241) - T1

Idea&Sol：[一只书虫仔](/user/114914)

Std&Data：[Tony2](/user/171288)

Retest：[Cocoly1990](/user/183026)

## 样例 #1

### 输入

```
2
5 2 3
4 1 5```

### 输出

```
8
8```

# 题解

## 作者：CSP_Sept (赞：10)

题号 7777 留念（

### Description

给定 $n$，要求把 $1\sim n$ 取完，有两种取法：

1. 单独取 $i$，代价 $i\times p$。
2. 一起取 $i,j$，代价 $|i-j|\times q$。

求最小代价。

### Solution

首先观察到两个显然的性质：

- 开始使用方法 2 后，一直使用方法 2 是最优的。
- 使用方法 2 时，保证 $|i-j|=1$ 是最优的。

我们考虑何时开始使用方法 2。

对于 $i,i+1$，有两种代价：$(2i+1)\times p$ 和 $q$。

于是，当 $(2i+1)\times p\ge q$ **且 $n-i-1$ 为偶数**时，我们就开始使用方法 2。

$n-i-1$ 为偶数是保证开始使用方法 2 后可以一直使用方法 2（剩余数字数量为偶数）。

### Code

```cpp
#include <cstdio>
#include <cmath>

#define ll long long
using namespace std;
ll p, q, n;
void sol(){
    scanf("%lld%lld%lld", &n, &p, &q);
    if(p == 0){
    	puts("0");
    	return;
	}
	if(n == 1){
		printf("%lld\n", p);
		return;
	}
	ll x = q / p;
	x = (x - 1) / 2;
	ll res = n - x;
	ll ans = 0;
	if(res % 2) x++, res--;
	ans = x * p;
	ans += (x - 1) * x * p / 2;
	ans += (res / 2) * q;
	printf("%lld\n", ans);
}
int main(){
	//freopen("tmp.in", "r", stdin);
	//freopen("tmp.out", "w", stdout);
	int t;
	scanf("%d", &t);
	while(t--) sol();
	return 0;
}
```

---

## 作者：ricky0916 (赞：6)

~~被编号吸引过来的~~

[题目链接](https://www.luogu.com.cn/problem/P7777)

我们定义选择一个数的操作为操作一，选择两个数的操作为操作二。

首先设我们会用 $2d$ 个操作二，那么我们要用 $n-2d$ 个操作一。

设操作二中用到的数为 $1\le b_1\le b_2\le ......\le b_{2d}\le n$，且用法为 $(b_{c_1},b_{c_2}),(b_{c_3},b_{c_4}),......(b_{c_{2d-1}},b_{c_{2d}})$，其中 $c_i\in [1,2d]$ 且两两不同。

那么可以证明以下结论：当 $ c_i=i $ 时答案最小。

为了方便证明，可设 $c_{2i-1}<c_{2i}$，对操作没有影响。

证明：假设有一个 $ c'_i $ 里有 $ c'_{2i-1}>c'_{2j-1} $（其中 $i<j$ ）

若有 $ c'_{2i}>c'_{2j} $，那么将 $ (c'_{2i-1},c'_{2i}) $ 与 $ (c'_{2j-1},c'_{2j}) $ 交换，代价不变

若有 $ c'_{2i}<c'_{2j} $，那么将 $ c'_{2i-1} $ 与 $ c'_{2j-1} $交换，代价变小

其他情况类似，命题得证。

然后我们又可以证明当 $ c_i=n-2d+i $ 时代价更小，~~结论显然就不证了。~~

于是我们就需要找到正确的 $ d $，使得代价最小。

容易列出以下两条不等式

$1.d\times q+p\times \sum_{i=1}^{n-2d}i\le (d+1)\times q+p\times \sum_{i=1}^{n-2d-2}i $

$2.d\times q+p\times \sum_{i=1}^{n-2d}i\le (d-1)\times q+p\times \sum_{i=1}^{n-2d+2}i$

两式可解得如下结果
$$
\dfrac{2np-p-q}{4p}\le d\le \dfrac{2np+3p-q}{4p}
$$

有 $ d $ 小于零或大于$ \lfloor \frac{n}{2}\rfloor $的话，特判即可。

还要注意特判 $p=0$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x=0;
	bool f=0;
	char ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9'){
		x=(x<<3)+(x<<1)+ch-'0';
		ch=getchar();
	}
	return x;
}
void write(long long x){
	if(x/10) write(x/10);
	putchar(x%10+'0');
}
void we(long long x){
	write(x);
	putchar('\n');
}
int n,p,q,t;
int main(){
	t=read();
	while(t--){
		n=read();
		p=read();
		q=read();
		if(p==0){
			we(0);
			continue;
		}
		int d,lf=(1ll*(2*n-1)*p-q)/(4*p),rf=(1ll*(2*n+3)*p-q)/(4*p);
		if(rf<=0) d=0;
		else if(lf>=n/2) d=n/2;
		else d=rf;
		we(1ll*d*q+1ll*(n-2*d)*(n-2*d+1)/2*p);
	}
	return 0;
}
```


---

## 作者：Cocoly1990 (赞：2)

来迟了的官方题解，书虫没交我就补一发

[Link](https://www.luogu.com.cn/paste/owibe01o)

本来二分是错误的要卡掉的，但是实在是不好卡，也不想卡，所以最后是没卡的。

std $\mathcal{O}\left(T\right)$

---

## 作者：int_R (赞：2)

题目链接：[P7777 『JROI-2』Shelter](https://www.luogu.com.cn/problem/P7777)

省流：**二分求单谷函数的谷值**。

### 前记

蒟蒻的第二篇题解。

一般的二分和 $O(1)$ 算法其他人都已经说的很明白了，这里提供一种新的思路——不用特判，个人认为好理解，好写的二分。

### 读题

首先我们仔细的研究一下这两个规则。

- 选择一个数 $i$，把第 $i$ 堆石子抓取走，代价为 $i \times p$。
- 选择两个数 $i,j$，把第 $i$ 堆和第 $j$ 堆石子抓走，代价为 $|i-j| \times q$。

我们发现，如果我们使用第二条规则，则一定是选取**相邻的两个**最优；同时还发现，我们一定是在前面一部分使用规则一，后面的使用规则二，因为你**编号越小，使用规则一所花费的代价就越少**，如果你编号大的都使用了规则二，则编号小的也一定要使用规则二。

于是乎，我们设 后 $2x$ 个使用规则二，则 前 $n-2x$ 个，使用规则一。

设花费总和为 $ans$ 则：

$$ans=\min\limits_{x=0}^{\lfloor n/2 \rfloor} ( \sum\limits_{i=1}^{n-2x} ip + xq)$$

合并同类项即：

$$ans=\min\limits_{x=0}^{\lfloor n/2 \rfloor} ( p\sum\limits_{i=1}^{n-2x} i + xq)$$

利用**等差数列**整理得：

$$ans=\min\limits_{x=0}^{\lfloor n/2 \rfloor} (\frac{(n-2x+1)(n-2x)}{2}p + xq)$$

我们这时可以感性理解一下，前一部分使用规则一，后一部分使用规则二，存在一个点到达最小值，那么 $ans=\frac{(n-2x+1)(n-2x)}{2}p + xq$，不就是个**单谷函数**么？

所以问题就转化成了求如下单谷函数的谷值。

$$\boxed{f(x)=\frac{(n-2x+1)(n-2x)}{2}p + xq\ (0\leq x\leq \lfloor \frac{n}{2} \rfloor)}$$

```cpp
inline int f(int i){return (n-2*i+1)*(n-2*i)/2*p+i*q;}//f(x)
```


### 二分

额，一般求单峰/谷函数我们最常用的是三分法，但对于这道题来说，反正我是没有用三分法写过去，原因可能是因为本人太弱了，一些毒瘤的问题我没有想到；同时 $O(T (2\log_3 n))$ 的时间复杂度（这里带上 2 的常数是为了体现出三分法要比二分慢一些）需要些卡常，不如使用二分（但二分也需要稍微卡一卡）。

在这道题中，是完完全全可以用二分求解单谷函数的谷值的，甚至于没有那些~~乱七八糟~~的特判，我们设一个点为 $x$ ，如果 $f(x-1)<f(x)$ ，则谷值点一定 $<x$ ，同理，如果 $f(x+1)<f(x)$ ，则谷值点一定 $>x$ ，如果 $f(x)\leq f(x-1)$ 且 $f(x)\leq f(x+1)$ ，则 $x$ 为**谷值点**，$f(x)$ 为**谷值**。同时我们还要考虑不能出界，这个直接看代码吧。

```cpp
while(l<r)
{
	mid=(l+r)>>1;
	if(mid-1>=0&&f(mid-1)<f(mid)) r=mid-1;//如果x可以更小，并且谷值点<x
	else if(mid+1<=n/2&&f(mid+1)<f(mid)) l=mid+1;//如果x可以更大，并且谷值点>x
	else l=r=mid;//若不行，则x为谷值点，直接将l和r设成 mid，下一步就直接跳出了
}
printf("%lld\n",f(l));
```

### AC Code

代码挺短的，最后一个点基本可以稳定在 220ms 左右

```cpp
#include<cstdio>
#define int long long
using namespace std;
int T,n,p,q;
inline int read()//快读是必要的
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
inline int f(int i){return (n-2*i+1)*(n-2*i)/2*p+i*q;}//f(x)
main()
{
	T=read();
	while(T--)
	{
 		n=read(),p=read(),q=read();
		int l=0,r=n/2,mid;//注意边界
		while(l<r)
		{
			mid=(l+r)>>1;
			if(mid-1>=0&&f(mid-1)<f(mid)) r=mid-1;//如果x可以更小，并且谷值点<x
			else if(mid+1<=n/2&&f(mid+1)<f(mid)) l=mid+1;//如果x可以更大，并且谷值点>x
			else l=r=mid;//若不行，则x为谷值点，直接将l和r设成 mid，下一步就直接跳出了
		}
		printf("%lld\n",f(l));
	}
	return 0;
}
```

### END

---

## 作者：斜揽残箫 (赞：2)


## Solution

首先，对于第二种抓取方式，贪心的想，肯定是每次取相邻的两堆石子代价是最小的，并且如果每次取相邻的两堆石子，代价是 $|i - j| \times q = q$，所以不管取哪里的，只要是相邻的，代价是不变的。

对于第一种抓取方式，明显代价会随着编号 $i$ 的增加而增加，所以和第二种抓取方式相结合，一定会有一个 $i$ 使得第 $i$ 堆石子用第一种方法，第 $i + 1$ 堆用第二种方法。

对于如何找出这个 $i$，因为第一种抓取方式代价随着 $i$ 的增加而增加，所以如果要使用第一种方式，肯定是从编号小的开始，这样满足单调性，我们只需要二分一下在哪个位置满足 $(2 \times i + 1) \times p > q$ 即可。(因为第二种是拿两个，所以要判断两次第一种抓取和一次第二种抓取哪个代价高)

还有就是二分之后，设 $i$ 为我们二分出来使用第一种方式抓取的最后一堆石子，后面用第二种抓取的分 $(n - i)$ 的奇偶性讨论一下 ： 

+ 如果是奇数，$Ans = Ans + (((n - i) - 1) / 2) \times q + p \times (i + 1)$
+ 否则，$Ans = Ans + ((n - i) / 2) \times q$

细节有点多，还是乐多赛，快把我给整吐了，时间复杂度 $O(T \log n)$。

## Code 

```
#include <cstdio>
#include <cmath>
#include <iostream>
#include <cstring>
#include <algorithm>
#define int long long
using namespace std;
int Ans,n,A,B;
inline int read()
{
	int s = 0, f = 0;char ch = getchar();
	while (!isdigit(ch)) f |= ch == '-', ch = getchar();
	while (isdigit(ch)) s = s * 10 + (ch ^ 48), ch = getchar();
	return f ? -s : s;
}
inline bool check(int num)
{
  if((2 * num + 1) * A > B) return false;//判断
  else return true;
}
signed main()
{
  int T = read();
  while(T --) {
    Ans = 0;
    n = read(),A = read(),B = read();
    if(check(n)) Ans = (((1 + n) * n) / 2) * A;//两种特殊情况
    else if(!check(1)){
      if(n & 1) Ans = ((n - 1) / 2) * B + A;
      else Ans = (n / 2) * B;//奇偶性讨论
    }
    else {
      int L = 1,R = n,Num = 1;
      while(L <= R) {
        int mid = (L + R) >> 1;
        if(check(mid)) L = mid + 1,Num = mid;
        else R = mid - 1;
      } //二分找出分界点
//      while(!check(Num)) Num --;
//      while(check(Num)) Num ++;
//      Num --;//大概是因为怕二分挂掉 (雾
      Ans += (((1 + Num) * Num) / 2) * A;
      if((n - Num) & 1) Ans += (((n - Num) - 1) / 2) * B + A * (Num + 1);
      else Ans += ((n - Num) / 2) * B;//奇偶性讨论
    }
    cout << Ans;puts("");
  }
  return 0;
}
```

---

## 作者：Daidly (赞：1)

发现规则 $2$ 比规则 $1$ 好，因为可以相邻两个配对，要找到什么时候开始用规则 $2$。

考虑以 $i$ 为分界点，大于 $i$ 的都用规则 $2$，小于等于 $i$ 的都用规则 $1$。

可以发现：$p(2i+1)=q$，所以 $i=\frac{\frac{q}{p}-1}{2}$，先把这一部分用等差数列求和公式算出来。

接着考虑剩下的：当剩下数数量为奇数，必然有一个不能用规则 $2$，那就取最小的将其使用规则 $1$，剩下的用规则 $2$。

坑：

- RE 的话要特判 $p=0$ 的情况，分子不能为 $0$：`if(!p){puts("0");continue;}`

- 特判 $n=1$ 的情况：`if(n==1){print(p),puts("");continue;}`

- 开 `long long`

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int read(){
    int x=0,f=1;
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
inline void print(int x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)print(x/10);
	putchar(x%10^48);
}
int t,n,p,q,ans,i;
signed main(){
	t=read();
	while(t--){
		ans=0;
		n=read(),p=read(),q=read();
		if(!p){puts("0");continue;}
		if(n==1){print(p),puts("");continue;}
		i=(q/p-1)/2;
		ans+=(1+i)*(i)/2*p;
		if((n-i)&1)ans+=(i+1)*p+(n-i-1)/2*q;
		else ans+=(n-i)/2*q;
		print(ans),puts("");
	}
	return 0;
}
```

---

## 作者：In3aNiT1 (赞：1)

### Key to P7777

其实做这道题不必太紧张，无论是通过时间限制与数据范围还是自己灵感都可以察觉出最好用 $O(1)$ 的做法。这也意味着，除了外层的 $t$ 层循环，里面没有平时各种 _~~花里胡哨的~~_ 算法。

话不多说，上图。

![石子](https://cdn.luogu.com.cn/upload/image_hosting/3p1z151b.png)

初步判断，我们可以发现，存在一条分割线，使线右侧的点数量为**双数**（左右侧点数可以为 零）；其中分割线左侧每个点的**编号乘** $p$ 再相加，右侧从最后一个点开始，每两点组成一对。左侧所得数，再加上右侧的**对数**乘以 **$q$** 就是答案中的一种情况。

这也是最优石子选取方法中的**固定格式**。手推很简单，可用反证法。

那么，我们就开始推导公式吧！

排除分割线在两边的极端情况，我们先看普遍的情况。

我们先选取石子堆中的**相邻**两堆，编号设为 $x - 1,x$ 两个。需要注意的是，根据题意，编号比 $x$ 大的石子堆数需要是**双数**。

我们暂且把这两堆石子看成一对。那么，这对石子堆现在面临着两个命运 :
- 分开取，即代价分开乘以 $p$，再相加。
- 一起取，即代价为 $q$。

那么，我们得到了一个**不等式** :

$(2x - 1) × p < q$

当满足此不等式时，第 $x$ 堆石子可以被分到分割线左侧。解得 :

$x < (q + p) / (p + p)$

问题来了 :

若是满足此式的最大 $x$ 让分割线右侧的堆数为单数呢？

解决方案为 :

比较。将 $x + 1$ 与 $x - 1$ 的两种情况所计算出的代价作比较，选取较小的数。


------------
关于特殊且必要的判断 :

- 若不等式解得 $x$ 最大值大于等于数量 $n$，那就直接输出 $n$ 乘以 $p$。
- $p = 0$ 时，不必解不等式，直接输出 $0$。
- 右侧点数为奇数时，若 $x + 1$ 大于 $n$，则直接输出 $x - 1$ 情况下的答案。
- 两分的特判，干脆单独写出来。


------------
~白给环节~

[AC code⭐](https://www.luogu.com.cn/record/55124392)
```c
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
#define int long long
inline int read()
{
	int x=0, f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		x=x*10+ch-48;
		ch=getchar();
	}
	return x*f;
}//快读

int n, p, q, ans, k, y, tmp;
signed main()
{
	int t=read();
	for(int i=1; i<=t; i++) {
		n=read(), p=read(), q=read();
		ans=0;
		if(p)
			y=n-(q+p)/(p+p);//q的个数
//		cout<<y<<endl;
		if(p==0) printf("0\n");
		else if(n==1) {
			printf("%lld\n", p);
		}
		else if(y<0) {
			printf("%lld\n", n*p);
		}
		else if(y%2==0) {
//			cout<<y<<endl;
			for(int i=1; i<=n-y; i++) ans+=i;
			y=q*y/2+p*ans;
//			cout<<ans<<" 000"<<endl;
			printf("%lld\n", y);
		}
		else {
//			cout<<y;
			y--;
			for(int i=1; i<=n-y; i++) ans+=i;
//			cout<<ans<<endl;
			ans=q*y/2+p*ans;
//			cout<<ans<<endl;
			y++;
			y++;
			tmp=y;
			k=0;
			for(int i=1; i<=n-y; i++) k+=i;
//			cout<<k*p<<endl;
			y=q*y/2+p*k;
			if(tmp<=n) printf("%lld\n", min(y, ans));
			else printf("%lld\n", ans);
		}
	}
	return 0;
}

```
最后祝各位同学都 Rp++!

---

## 作者：luckydrawbox (赞：1)

这里提供一个 $O(T\log N)$ 的二分做法。

为了使代价最小，对于第一种抓取方式，我们尽量取较小的数；对于第二种抓取方式，我们尽量取**相邻**的数。

于是，我们要找到一个数 $k$，使 $1\sim k-1$ 的数用第一种抓法，$k\sim n$ 用第二种抓法，且代价最小。这具有单调性，于是考虑二分。

首先是边界，$r$ 自然是 $n$，但因为第二种抓法的个数是偶数，所以要保证 $l$ 和 $n$ 奇偶性相同，因此 $l$ 必须为 $n\ \text{and}\ 1$。

接下来就考虑一个 $mid$ 是属于哪一种了。

- 如果 $mid$ 和 $n$ 奇偶性相同，那么与 $mid$ 相邻的数就为 $mid-1$。

- 如果 $mid$ 和 $n$ 奇偶性不同，那么与 $mid$ 相邻的数就为 $mid+1$。

以上规律可以通过打表发现，总结一下就有了通项判定式 $((mid+mid-1+2\times((n\ \text{and}\ 1)-(mid\ \text{and}\ 1))\neq\ 0)\times p<q$。

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int t;
ll n,p,q,ans,l,r,mid;
ll read()
{
	ll x=0,f=1;char ch=getchar();
	while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}
	while (isdigit(ch)){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
void write(ll X){
	if(X<0) {putchar('-'); X=~(X-1);}
	int s[21],top=0;
	while(X) {s[++top]=X%10; X/=10;}
	if(!top) s[++top]=0;
	while(top) putchar(s[top--]+'0');
}
int main()
{
    t=read();
    while(t--)
    {
    	n=read();
    	p=read();
    	q=read();
    	l=n&1,r=n;
    	while(l<r)
    	{
    		mid=(l+r+1)>>1;
    		if((mid*2-1+2*((n&1)-(mid&1)!=0))*p<q)
    			l=mid;
    		else
    			r=mid-1;
		}
		write(l*(l+1)/2*p+(n-l)/2*q);
		putchar('\n');
	}
	return 0;
}
```

当然，细心 ~~ctj~~ 的你一定会发现，**这个代码其实并不能通过本题**，原因是本题原来时限为 2s，无优化可以轻松过。

但[出题人](https://www.luogu.com.cn/user/114914)为了只让 $O(T)$ 的算法过，把时限改成了 500ms，不过这个算法加上快读也能过。

但[出题人](https://www.luogu.com.cn/user/114914)仍不死心，把时限调成了 300ms，不过道高一尺，魔高一丈，不过再加上快写等优化仍等稳过，[开 O2 后](https://www.luogu.com.cn/record/55083091)吊打[出题人](https://www.luogu.com.cn/user/114914)。

![](https://cdn.luogu.com.cn/upload/image_hosting/4xt4zxiy.png)

相关[帖子](https://www.luogu.com.cn/discuss/show/336831?page=3)。

---

## 作者：Erica_N_Contina (赞：0)

# 『JROI-2』Shelter


## 思路

首先明确这 $n$ 堆石子编号为 $1$ 到 $n$ 连续分布。如果选择方式 $1$，则代价分别为 $1\times p,2\times p,3\times p,...,n\times p$，且 $p>0$。如果选择方式 $2$，我们肯定每次选择连续两个数，那么每次取走 $i,i+1$ 的代价为 $ q$，平均下来每个的代价为 $p\div 2$。

既然方式 $1$ 的代价是递增的，那么当我们从 $1\sim n$ 扫描时，当我们第一次碰到 $i$ 石子选用方式 $1$ 的代价大于方式 $2$ 的代价时，我们就开始使用方式 $2$ 而不再使用方式 $1$。

当然，由于方式 $2$ 是成对消除的，所以只有当前剩余偶数个石子时才能判定是否要转向方式 $2$。

```C++
signed main(){
	cin>>T;
	while(T--){
		ans=0;
		cin>>n>>p>>q;
		int i=1;
		if(n%2)ans+=p,i++;
		for(;i<=n;i++){
			if((i+1+i)*p<q)ans+=p;
			else {
				ans+=q*(n-i+1)/2;break;
			}
		}
		cout<<ans<<endl;
	}
	
	return 0;
}
```


但我们发现，本题时间限制为 300ms，还有多组数据，那么我们肯定要优化掉 `for` 循环。

我们考虑什么时候开始用方式 $2$。

当我们消除 $i,i+1$ 时，方式 $1$ 代价为 $(2\times i+1)\times p$，方式 $2$ 的代价为 $q$，那么当 $ (2\times i+1)\times p≥q$ 时，我们开始用方式 $2$。但是我们要保证 $n-i+1$ 为偶数。

$(2\times i+1)\times p=q$

$2\times i=q\div p-1$

$i=\frac{q\div p-1}{2}$


```C++
    int i=(q/p-1)/2;
    if((n-i)%2)i++;
    ans+=i*p;
    ans+=(1+i-1)*(i-1)/2*p;
    ans+=(n-i)/2*q;
    printf("%lld\n",ans);
```


我们计算出 $i$ 后，$[1,i]$ 使用方式 $1$，$[i+1,n]$ 使用方式 $2 $。如果 $n-(i+1)+1$ 为奇数，则 $i$ 加上 $1$。

## 注意

- 本题卡时长，请不要使用 `cin` 。

- 本题请开 `long long`。

- 注意计算 $i$ 时分母为 $0$ 的情况！以及特判 $n=1$ 的情况。

```C++
    if(p==0){
        puts("0");
        continue;
    }
    if(n==1){
        printf("%d\n", p);
        continue;
    }
```




---

