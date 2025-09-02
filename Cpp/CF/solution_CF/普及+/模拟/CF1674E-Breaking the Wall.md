# Breaking the Wall

## 题目描述

Monocarp plays "Rage of Empires II: Definitive Edition" — a strategic computer game. Right now he's planning to attack his opponent in the game, but Monocarp's forces cannot enter the opponent's territory since the opponent has built a wall.

The wall consists of $ n $ sections, aligned in a row. The $ i $ -th section initially has durability $ a_i $ . If durability of some section becomes $ 0 $ or less, this section is considered broken.

To attack the opponent, Monocarp needs to break at least two sections of the wall (any two sections: possibly adjacent, possibly not). To do this, he plans to use an onager — a special siege weapon. The onager can be used to shoot any section of the wall; the shot deals $ 2 $ damage to the target section and $ 1 $ damage to adjacent sections. In other words, if the onager shoots at the section $ x $ , then the durability of the section $ x $ decreases by $ 2 $ , and the durability of the sections $ x - 1 $ and $ x + 1 $ (if they exist) decreases by $ 1 $ each.

Monocarp can shoot at any sections any number of times, he can even shoot at broken sections.

Monocarp wants to calculate the minimum number of onager shots needed to break at least two sections. Help him!

## 说明/提示

In the first example, it is possible to break the $ 2 $ -nd and the $ 4 $ -th section in $ 10 $ shots, for example, by shooting the third section $ 10 $ times. After that, the durabilities become $ [20, 0, 10, 0, 20] $ . Another way of doing it is firing $ 5 $ shots at the $ 2 $ -nd section, and another $ 5 $ shots at the $ 4 $ -th section. After that, the durabilities become $ [15, 0, 20, 0, 15] $ .

In the second example, it is enough to shoot the $ 2 $ -nd section once. Then the $ 1 $ -st and the $ 3 $ -rd section will be broken.

In the third example, it is enough to shoot the $ 2 $ -nd section twice (then the durabilities become $ [5, 2, 4, 8, 5, 8] $ ), and then shoot the $ 3 $ -rd section twice (then the durabilities become $ [5, 0, 0, 6, 5, 8] $ ). So, four shots are enough to break the $ 2 $ -nd and the $ 3 $ -rd section.

## 样例 #1

### 输入

```
5
20 10 30 10 20```

### 输出

```
10```

## 样例 #2

### 输入

```
3
1 8 1```

### 输出

```
1```

## 样例 #3

### 输入

```
6
7 6 6 8 5 8```

### 输出

```
4```

## 样例 #4

### 输入

```
6
14 3 8 10 15 4```

### 输出

```
4```

## 样例 #5

### 输入

```
4
1 100 100 1```

### 输出

```
2```

## 样例 #6

### 输入

```
3
40 10 10```

### 输出

```
7```

# 题解

## 作者：ncwzdlsd (赞：3)

分讨。

- $op.1$

最先非正的两个数为序列最小值和次小值。

直接找序列的最小值 $\min_1$ 和次小值 $\min_2$，将 $\min_1$ 和 $\min_2$ 不断减 $2$。总花费为 $\lceil\dfrac{\min_1}{2}\rceil+\lceil\dfrac{\min_2}{2}\rceil$。

- $op.2$

最先非正的两个数为相邻的两个数。

若两个数中的一个不小于另一个数的两倍，那么可以通过不断地对较大数进行操作得到两个非正数。总花费为$\lceil\dfrac{\max(a_i,a_{i+1})}{2}\rceil$。

否则，以这两个数为整体，每次操作可以使两数之和减小 $3$，对两数进行轮流操作，

- $op.3$

最先非正的两个数为序列中距离为 $2$ 的两个数。

无论如何，每次操作只能使这两个数和不断减小 $1$。总花费为 $\lceil\dfrac{a_{i-1}+a_{i+1}}{2}\rceil$。

这里也可以把两个数分开来看计算花费，但是显然没有整体法简洁。

---

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;

const int maxn=2e5+5;
int a[maxn],n,c1,c2,c3,b[maxn];

void op1()
{
    sort(b+1,b+n+1);
    c1=(b[1]+1)/2+(b[2]+1)/2;
}

void op2()
{
    c2=0x3f3f3f;
    for(int i=1;i<n;i++)
    {
        if(a[i+1]>=a[i]*2||a[i]>=a[i+1]*2) c2=min(c2,(max(a[i],a[i+1])+1)/2);
        else c2=min(c2,(a[i]+a[i+1]+2)/3);
    }
}

void op3()
{
    c3=0x3f3f3f;
    for(int i=2;i<n;i++) c3=min(c3,(a[i-1]+a[i+1]+1)/2);
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i],b[i]=a[i];
    op1(),op2(),op3();
    cout<<min(c1,min(c2,c3));
    // cout<<c1<<endl<<c2<<endl<<c3;
    return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：3)

# CF1674E 题解



## 思路分析

考虑两个变成非正整数的位置 $a_i,a_j$，根据 $|i-j|$ 的关系可以分为以下三类。

1. $|i-j|=1$ 时：

此时我们一次操作可以对于 $a_i+a_j$ 产生 $3$ 的贡献，因此此时的答案为 $\left\lfloor\dfrac{a_i+a_j}3\right\rfloor$，不过当 $\max(a_i,a_j)\ge 2\times \min(a_i,a_j)$ 时，不可能每次操作都产生 $3$ 的贡献，而此时答案应该是 $\left\lfloor\dfrac{\max(a_i,a_j)}2\right\rfloor$。

2. $|i-j|=2$ 时：

无论是在 $i,j$ 中间操作还是对着 $i$ 或 $j$ 操作，对 $a_i+a_j$ 的贡献总是 $2$，因此此时的答案为 $\left\lfloor\dfrac{a_i+a_j}2\right\rfloor$。

3. $|i-j|>2$ 时：

一次操作只可能对 $a_i$ 或 $a_j$ 中的一个产生 $1$ 的贡献，此时的答案为 $\left\lfloor\dfrac{a_i}2\right\rfloor+\left\lfloor\dfrac{a_j}2\right\rfloor$。

因此对于这三种情况分别处理后取最小代价即可。

时间复杂度 $\Theta(n)$。

## 代码呈现

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=2e5+1,INF=1e9;
int n,a[MAXN];
inline int cost1() {
	//a[i] and a[i+1]
	int ret=INF;
	for(int i=1;i<n;++i) {
		if(max(a[i],a[i+1])>=2*min(a[i],a[i+1])) ret=min(ret,(max(a[i],a[i+1])+1)/2);
		else ret=min(ret,(a[i]+a[i+1]+2)/3);
	}
	return ret;
}
inline int cost2() {
	//a[i-1] and a[i+1]
	int ret=INF;
	for(int i=2;i<n;++i) {
		ret=min(ret,(a[i-1]+a[i+1]+1)/2);
	}
	return ret;
}
inline int cost3() {
	//a[x] and a[y], |x-y|>2
	int fir=INF,sec=INF;
	for(int i=1;i<=n;++i) {
		if(a[i]<fir) sec=fir,fir=a[i];
		else if(a[i]<sec) sec=a[i];
	}
	return (fir+1)/2+(sec+1)/2;
}
signed main() {
	scanf("%d",&n);
	for(int i=1;i<=n;++i) scanf("%d",&a[i]);
	printf("%d\n",min(min(cost1(),cost2()),cost3()));
	return 0;
} 
```



---

## 作者：CGDGAD (赞：3)

## CF1674E Breaking the Wall

### 算法

首先猜一猜，我们的答案的来源只有可能是这几种情况：

- 第一种，最简单直接，即把数列中最小的两个每次杀掉 2。但肯定不只有这一种，因为杀一个数的时候它相邻的数也会被影响，所以推出来接下来的两种。
- 第二种比较投机取巧，相隔一个数的两个奇数，先通过杀中间的那个数一次转为偶数，然后转为第一种。
- 第三种就是杀掉相邻两个数时，互相凑一凑，答案就是两个数和除以 3 向上取整（攻击一边的时候，自己受到 2 点伤害，对方受到 1 点伤害）。但当一个数 $a$ 大于另一个数 $b$ 的两倍时，此方法只能妥协，答案为 $\lceil \dfrac a 2 \rceil$。

当被杀的两个数距离 $\ge 2$ 的时候，可以做到各杀各的互不干涉，归于第一种。

当被杀的两个数距离等于 $1$ 的时候，适用第一种或第二种（也可以说就是两个数加起来除以 $2$ 向上取整）。

当被杀的两个数相邻，那必然属于第三种。

因此，以上三种得到答案的类型覆盖所有的情况，解法是正确的。

这个题主要是分类讨论的时候要注意一下有没有更优化的方法。

### 实现

```cpp
int n, a[200001];

int upper(int a, int b) {
    if (a % b) return a / b + 1;
    else return a / b;
}

int main() {
    n = read();
    for (int i = 1; i <= n; ++i) {
        a[i] = read();
    }

    int t3 = 1000000;
    for (int i = 1; i <= n - 1; ++i) {
        int res = 0;
        if (a[i] > a[i + 1] * 2) res = (a[i] + 1) / 2;
        else if (a[i + 1] > a[i] * 2) res = (a[i + 1] + 1) / 2;
        else res = upper(a[i] + a[i + 1], 3);
        t3 = std::min(t3, res);
    }

    int t2 = 1000000;
    for (int i = 1; i <= n - 2; ++i)
        if ((a[i] & 1) && (a[i + 2] & 1))
            t2 = std::min(t2, 1 + a[i] / 2 + a[i + 2] / 2);

    std::sort(a + 1, a + n + 1);
    int t1 = (a[1] + 1) / 2 + (a[2] + 1) / 2;

    printf("%d\n", std::min({t1, t2, t3}));
    return 0;
}
```

---

## 作者：lingfunny (赞：1)

## 题解

样例非常多，模拟完之后差不多就知道解法了。

首先最优解只有三种可能。

1. 删掉相邻的数
2. 删掉间隔一格的数
3. 删掉最小的两个但不一定属于上述两种的数

当不属于 1 和 2 的时候，删掉的两个数互相没有影响，所以最优解一定是贪心删除最小的两个。

对于这三种，再暴力分讨。下文说的 $-1$，$-2$，$-3$ 指对 $x+y$ 的改变。

1. 相邻，不妨设 $x<y$。
	1. $\lceil\frac{y}{2}\rceil\ge x$，此时暴力单独删 $y$ 即可，$x$ 会自己消掉。
	2. 否则，会发现对 $y$ 进行操作后，$x$ 和 $y$ 的差值固定 $-1$，并且当 $x$ 和 $y$ 相等后不会出现 $x,y$ 是负数。同时，对 $y$ 操作会总共造成 $-3$ 的贡献，是最优的。那么可以先把 $x,y$ 减到相同，然后交替操作，这样每步操作都是 $-3$ 的。最后会剩下 $1,1$ 或 $1,0$，这时候只能被迫 $-2$ 或 $-1$。可以证明这样的操作方式一定是最优的。可以转化成你有一个数 $x+y$，每次可以 $-1$、$-2$ 或 $-3$，那么如果能一直 $-3$ 最后再 $-1$ 或 $-2$ 一定是最优的。
2. 间隔一，不妨设 $x<y$。
	1. $x,y$ 都为奇数，此时在 $x,y$ 中间那个数操作可以使两者同时 $-1$。接下来两个偶数，可以分别单独操作，每一步都是 $-2$ 的，必定是最优解。因为在间隔一的限制下每一步最多 $-2$。
	2. 不均为奇数，那么对每个数单独减即可。如果一奇一偶会出现最后一步是 $-1$，其他步是 $-2$，可以证明这一定是最优的。因为一步只能 $-1$ 或 $-2$，但 $x+y$ 是奇数，最优解一定是一堆 $-2$ 和一个 $-1$。
3. 暴力改，没有更优，证明同上。

一句话概括解法就是**构造出一种合法的操作方案**，然后证明**这种构造足够优，并且没有更优的**。

~~这凭什么是绿啊~~

~~这凭什么*2000啊~~

## 代码

```cpp
// Problem: E. Breaking the Wall
// From: Codeforces - Codeforces Round #786 (Div. 3)
// URL: https://codeforces.com/problemset/problem/1674/E
// Time: 2022-05-14 17:03
// Author: lingfunny

#include <bits/stdc++.h>
using namespace std;
const int mxn = 2e5+10;

int n, a[mxn], res = 1e9, x, y;

signed main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i) scanf("%d", a+i);
    for(int i = 1; i < n; ++i) {
		x = a[i], y = a[i+1];
        if(x > y) swap(x, y);
        if(x <= (y+1)/2) res = min(res, (y+1)/2);
        else res = min(res, (x+y+2)/3);
    }
    for(int i = 1; i + 2 <= n; ++i) res = min(res, (a[i]+a[i+2]+1)/2);
	auto it = min_element(a+1, a+n+1);
	x = *it; *it = 1e9; it = min_element(a+1, a+n+1);
	y = *it; res = min(res, (x+1)/2+(y+1)/2);
    printf("%d\n", res);
    return 0;
}
```

---

## 作者：I_am_Accepted (赞：1)

### Preface

被 Hack 了，祭。

### Analysis

设最终被摧毁的位置为 $l,r(l<r)$，不妨设 $a_l<a_r$。

若 $r-l\ge 3$，则一次攻击不可能同时削减 $l,r$ 的防御，则答案为 $\lceil\frac{a_l}{2}\rceil+\lceil\frac{a_r}{2}\rceil$。

若 $r-l=2$，则两者都攻击的方案只有打中间，然后双方各 $-1$。此类情况答案为 $a_l+\lceil\frac{a_r-a_l}{2}\rceil$，即先同时 $-1$，再将未清零的消掉。

若 $r-l=1$，则攻击方案有两种：

1. $a_l$ 减 $2$，$a_r$ 减 $1$。

2. $a_l$ 减 $1$，$a_r$ 减 $2$。

所以，若 $2a_l\le a_r$，全部用 (1.) 攻击，答案为 $\lceil\frac{a_r}{2}\rceil$。

否则，我们要先用「一次 (1.) 攻击 一次 (2.) 攻击」的形式使得 $a_r$ 接近 $a_l$ 的两倍，再用 (1.) 攻击。

分类讨论，设 $A=2a_l-a_r$，得到此部分的答案为 $a_r-a_l+\lfloor
\frac{2}{3}A\rfloor+(A\bmod3)$。

然后在每种答案中取最小值即可。

### Code

```cpp
//Said no more counting dollars. We'll be counting stars.
#pragma GCC optimize("Ofast")
//#pragma GCC optimize("unroll-loops")//DONT use rashly,I have suffered
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")//DONT use rashly,I have suffered
#include<bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define fir first
#define sec second
#define mkp make_pair
#define pb emplace_back
#define mem(x,y) memset(x,y,sizeof(x))
#define For(i,j,k) for(int i=j;i<=k;i++)
#define Rof(i,j,k) for(int i=j;i>=k;i--)
#define Fe(x,y) for(int x=head[y];x;x=e[x].nxt)
#define ckmx(a,b) a=max(a,b)
#define ckmn(a,b) a=min(a,b)
#define fin(s) freopen(s,"r",stdin)
#define fout(s) freopen(s,"w",stdout)
#define file(s) fin(s".in");fout(s".out")
#define cerr cerr<<'_'
#define debug cerr<<"Passed line #"<<__LINE__<<endl
template<typename T>T ov(T x){cerr<<"Value: "<<x<<endl;return x;}
#define ll long long
const ll mod=1000000007;
inline ll pw(ll x,ll y){ll r=1;while(y){if(y&1)r=r*x%mod;x=x*x%mod;y>>=1;}return r;}
inline void mad(ll &a,ll b){a=(a+b)%mod;while(a<0)a+=mod;}
inline void mmu(ll &a,ll b){a=a*b%mod;while(a<0)a+=mod;}
#define inv(a) pw(a,mod-2)
#define int long long
#define N 200010
int n,ans,a[N],b[N];
int calc(int x,int y){
	if(x>y) swap(x,y);
	if(2*x<=y) return (y+1)/2;
	int res=y-x;
	x-=res;
	return res+x/3*2+x%3;	
}
int work(int x,int y){
	if(x>y) swap(x,y);
	return (y-x+1)/2+x; 
}
signed main(){IOS;
	cin>>n;
	For(i,1,n) cin>>a[i];
	For(i,1,n) b[i]=(a[i]+1)>>1;
	sort(b+1,b+1+n);
	ans=b[1]+b[2];
	For(i,1,n-1) ckmn(ans,calc(a[i],a[i+1]));
	For(i,1,n-2) ckmn(ans,work(a[i],a[i+2]));
	cout<<ans<<endl;
return 0;}
```

---

## 作者：Deuteron (赞：1)

题意：

现在有一个正整数序列 $a$ , 你可以选择一个位置 $i$ ，进行一次操作：将 $a_i$减去 $2$ ，将 $a_{i-1}$
 （如果存在）减去 $1$ ，将 $a_{i+1}$
 （如果存在）减去 $1$，问至少要多少次操作可以使数列中至少出现两个非正整数。
 
## solution:

可能有以下几种情况：

情况 $1$ ：

选择两个最小的数（不妨设为 $x_1,x_2$ ），答案显然为 $\lceil \dfrac{x_1}{2} \rceil+\lceil \dfrac{x_2}{2} \rceil$ 

情况 $2$ ：

选择两个距离 $=2$ 的数（不妨设为 $a_{i-1},a_{i+1}$）

策略：对 $i$ 进行 $\min(a_{i-1},a_{i+1})$ 次操作 ，此时 $a_{i-1}$ 与 $a_{i+1}$ 中必有一个 $\le 0$ 。

然后对剩下的那个数进行$\lceil \dfrac{\lvert a_{i-1}-a_{i+1} \rvert}{2} \rceil$ 次操作。

这个地方是一个 Hack 的点，~~本蒟蒻惨遭 Hack~~

情况 $3$ ：

选择两个相邻的数。（不妨设为 $a_{i},a_{i+1}$ ）

假设 $a_{i}\le a_{i+1}$ （反过来也一样）

若 $a_{i}>a_{i+1}\times 2$ 则需要对 $a_i$ 操作 $\lceil \dfrac{a_i}{2} \rceil$ 次，显然这时 $a_i\le 0$ ，$a_{i+1} \le 0$ 符合要求。

否则可以轮流操作，答案为$\lceil \dfrac{a_i+a_{i+1}}{3} \rceil$ 。

~~这又是一个大 Hack 点~~

我们只需要取这三种情况中最小的即可。

注意，在此题中 $\lceil \dfrac{x}{2} \rceil=\lfloor \dfrac{x+1}{2} \rfloor$ ，$\lceil \dfrac{x}{3} \rceil=\lfloor \dfrac{x+2}{3} \rfloor$ 。

## code:~~赛时代码，丑陋无比~~

```cpp
#include<iostream>
using namespace std;
const int N=2e5+5;
int n;
int a[N];
int ans=1e9;
int mn=1e9,ml=1e9;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=n;i++){
		if(a[i]<=mn){
			ml=mn;
			mn=a[i];
		}
		else if(a[i]<=ml){
			ml=a[i];
		}
	}//求出最小以及次小值
	ans=(mn+1)/2+(ml+1)/2;//第一种情况
	for(int i=1;i<n;i++){
		if(a[i+1]>=a[i]*2||a[i]>=a[i+1]*2) ans=min(ans,(max(a[i],a[i+1])+1)/2);
		else ans=min(ans,(a[i]+a[i+1]+2)/3);//第三种情况
	}
	for(int i=2;i<n;i++){
		if(a[i-1]>a[i+1]) ans=min(ans,a[i+1]+(a[i-1]-a[i+1]+1)/2);
		else ans=min(ans,a[i-1]+(a[i+1]-a[i-1]+1)/2);//第二种情况
	}
	cout<<ans<<endl;
	return 0;
}
```
求管理员大大通过qwq






---

## 作者：Erica_N_Contina (赞：0)

## 思路

我们枚举那两个非正整数 $a_i,a_j$ 的位置，我们假定 $a_i>a_j$。

- $|i-j|=1$ 时：

此时我们一次操作可以对于 $a_i+a_j$ 产生 $3$ 的贡献，因此此时的答案为 $\left\lceil\dfrac{a_i+a_j}3\right\rceil$，不过当 $a_i\ge 2\times a_j$ 时，不可能每次操作都产生 $3$ 的贡献，而此时答案应该是 $\left\lceil\dfrac{a_i}2\right\rceil
$。我们扫一遍判每个 $(i,i+1)$ 即可。

- $|i-j|=2$ 时：

无论是在 $i,j$ 中间操作还是对着 $i$ 或 $j$ 操作，对 $a_i+a_j$ 的贡献总是 $2$，因此此时的答案为 $\left\lceil\dfrac{a_i+a_j}2\right\rceil$。我们找到 $a$ 中的最小值和次小值即可。或者扫一遍判每个 $(i-1,i+1)$ 即可。

- $|i-j|>2$ 时：

一次操作只可能对 $a_i$ 或 $a_j$ 中的一个产生 $1$ 的贡献，此时的答案为 $\left\lceil\dfrac{a_i}2\right\rceil+\left\lceil\dfrac{a_j}2\right\rceil$。我们在一次扫描中找到最小值和次小值即可。

## 代码

```C++
#include<bits/stdc++.h>
using namespace std;
#define int long long
 
 
#define rd read()
inline int read()
{
	int xx=0,ff=1;
	char c=getchar();
	while(c<'0'||c>'9') {if(c=='-') ff=-1;c=getchar();}
	while(c>='0'&&c<='9') xx=xx*10+(c-'0'),c=getchar();
	return xx*ff;
}
inline void write(int out)
{
	if(out<0) putchar('-'),out=-out;
	if(out>9) write(out/10);
	putchar(out%10+'0');
}
 
 
const int N=2e5+5;
const int M=5e5+5;
const int INF=1e9+5;
const int MOD=1e9+7;
bool f1;
int m,k,n,qzh;
 
int q;
int T,mn=INF,ans=INF;
int ck[N],r;
int a[N],tot,tmp[N];

void solve1(){
	for(int i=1;i<n;i++){
		if(max(a[i],a[i+1])>=2*min(a[i],a[i+1])){
			ans=min(ans,(max(a[i],a[i+1])+1)/2);
		}else{
			ans=min(ans,(a[i]+a[i+1]+2)/3);
		}
	}
}

void solve2(){
	for(int i=2;i<n;i++){
		ans=min(ans,a[i-1]+a[i+1]+1>>1);
	}
}

void solve3(){
	int mx1=INF,mx2=INF;
	for(int i=1;i<=n;i++){
		int t=a[i]+1>>1;
		if(t<mx1)mx2=min(mx1,mx2),mx1=t;
		else if(t<mx2)mx2=t;
	}
	ans=min(ans,mx1+mx2);
}

main(){
	n=rd;
	for(int i=1;i<=n;i++){
		a[i]=rd;
	}
	solve1();
	solve2();
	solve3();

	cout<<ans<<endl;
	
}
```




---

## 作者：xujunlang2011 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1674E)

## 思路

分三类讨论，枚举位置 $l$ 与 $r$。

$\bullet$ 当 $\left|l-r\right|>2$ 时：

这种情况有很多种小情况，但是两个数不相互影响。

所以我们可以充分发扬人类智慧，直接找到最小值和次小值，然后把他们分别干掉。

所以操作次数为 $\left\lceil\dfrac{a_l}{2}\right\rceil+\left\lceil\dfrac{a_r}{2}\right\rceil$。

$\bullet$ 当 $\left|l-r\right|=2$ 时：

我们发现这种情况可以打两个数中间的那个数，也可以分别把两个数打掉。

于是我们再次充分发扬人类智慧，直接对两个数的总和进行操作。

我们发现不管是打中间还是打两边，对总和的总贡献都是 $2$。

所以操作次数为 $\left\lceil\dfrac{a_l+a_r}{2}\right\rceil$。

$\bullet$ 当 $\left|l-r\right|=1$ 时：

我们发现这种情况可以打左边的那个数，也可以打右边的那个数。

于是我们又一次充分发扬人类智慧，还是直接对两个数的总和进行操作。

我们发现不管是打左边还是打右边，对总和的总贡献都是 $3$。

所以操作次数为 $\left\lceil\dfrac{a_l+a_r}{3}\right\rceil$。

但是，如果两个数差的太多，比如 $a_l=10$，$a_r=2$，也就是 $\max(a_l,a_r)>\min(a_l,a_r)\times2$。

这样的话就算一直打大的那个，也无法在小的数打完之前将大的数打完。

这时只能一直对着大的打了，~~充分发扬人类智慧也没用~~。

此时操作次数会增加到 $\left\lceil\dfrac{\max(a_l,a_r)}{2}\right\rceil$。

那么最终答案就是这三种情况的操作次数的最小值了。

## 代码

```
#include<bits/stdc++.h>
using namespace std;
int mins = 999999999; 
int main()
{
    int n, min1 = 999999999, min2 = 999999999;
    cin >> n;
    int a[n + 5];
    for (int i = 1;i <= n;i++)
    {
        cin >> a[i];
        if (a[i] <= min1)
        {
            min2 = min1;
            min1 = a[i];
        }
        else if (a[i] < min2)
        {
            min2 = a[i];
        }
    }
    mins = min(mins, (min1 + 1) / 2 + (min2 + 1) / 2);//abs(l - r) > 2 
    for (int i = 1;i <= n - 2;i++)
    {
        mins = min(mins, (a[i] + a[i + 2] + 1) / 2);
    }//abs(l - r) = 2
    for (int i = 1;i <= n - 1;i++)
    {
        if (max(a[i], a[i + 1]) > min(a[i], a[i + 1]) * 2)
        {
            mins = min(mins, (max(a[i], a[i + 1]) + 1) / 2);
        }//特殊情况 
        else
        {
            mins = min(mins, (a[i] + a[i + 1] + 2) / 3);
        }//普通情况 
    }//abs(l - r) = 1
    cout << mins;
    return 0;
}
```


---

## 作者：UperFicial (赞：0)

破防了，$2000$ 的题调了 2h/oh/hsh，写个题解敲烂警钟。

放一个特别麻烦的分类讨论做法。

[题目传送门](https://www.luogu.com.cn/problem/CF1674E)。

同步发表于我的 [$\text{cnblogs}$](https://www.cnblogs.com/UperFicial/p/16669240.html)。

首先答案 $L$ 具有可二分性，那么问题转化成能否在 $L$ 步之内，使序列出现两个非负整数。

然后有以下若干方法：

1. 找到最小值和次小值，分别不断的减 $2$。

2. 如果最小值和次小值相邻，那么这个显然不是最优的。对于两个相邻的数 $x,y(x<y)$，我们可以先对 $y$ 不断进行操作，直到 $x=y$，然后两个数轮流操作，这样相当于每次减三。考虑最后的 $x,y$ 一定都不大于 $2$，若 $x,y$ 均等于 $0$，那么直接返回操作次数，如果其中一个等于 $1$，那么都可以对另外一个数进行操作，返回操作次数 $+1$；如果 $x,y$ 均等于 $2$，那么需要再额外操作两次。

3. 仍然是对于两个相邻的数 $x,y$，若 $2x<y$，使用 $2$ 操作的话不会使两个数齐平。那么这个单独写一个做法即可，不断对 $y$ 进行操作，直到 $y\le 0$。

4. 对于三个相邻的数 $x,y,z$，若 $\max(x,z)\le L$，说明我们可以一直对 $y$ 操作，使得出现两个非正整数。

之后就是考察超级玛丽的环节，如果寄了建议写一个对拍，这样的话就很好调。

代码：

```cpp
const int MAXN(2e5+10);

int n,a[MAXN];

inline int updiv(int x,int y){return x%y==0?x/y:x/y+1;}
inline int calc(int x,int y)
{
	int now=0;
	if(x>y) Swap(x,y);
	if(x*2<y) return updiv(y,2);
	else
	{
		now=y-x;
		x-=now;
		y=y-now*2;
		if(x%3==0) return x/3*2+now;
		now=now+x/3*2;
		int xx=x-x/3*3;
		int yy=y-y/3*3;
		if(xx==2&&yy==2) now=now+2;
		else now=now+1;
	}
	return now;
}
inline int calc2(int x,int y)
{
	if(x>y) Swap(x,y);
	int t=updiv(y,2);
	if(x>=t) return x;
	return x+updiv((y-x*2),2);
}
inline int calc3(int x,int y)
{
	if(x>y) Swap(x,y);
	--x,--y;
	return updiv(x,2)+updiv(y,2)+1;
}
inline bool check(int lim)
{
	int x(INF),y(INF);
	rep(i,1,n-1) if(calc(a[i],a[i+1])<=lim) return true;
	rep(i,1,n) if(x>=a[i]) y=x,x=a[i];else if(y>=a[i]) y=a[i];
	if(updiv(x,2)+updiv(y,2)<=lim) return true;
	rep(i,2,n-1) if(Max(a[i-1],a[i+1])<=lim) return true;
	rep(i,1,n-1) if(calc2(a[i],a[i+1])<=lim) return true;
	rep(i,1,n-2) if(calc3(a[i],a[i+2])<=lim) return true;
	return false;
}

int main()
{
	n=read();
	int l(1),r(0),res(-1);
	rep(i,1,n) a[i]=read(),r=Max(r,a[i]);
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(check(mid)) r=mid-1,res=mid;
		else l=mid+1;
	}
	printf("%d\n",res);
	return 0;
}
/*
Date : 2022/9/8
Author : UperFicial
Start coding at : 9:27
finish debugging at : 13:54
*/
```

---

## 作者：CmsMartin (赞：0)

## 题目描述

[题目传送门1](https://www.luogu.com.cn/problem/CF1674E)

[题目传送门2](http://codeforces.com/problemset/problem/1674/E)

现在有一个正整数序列 $a$ , 你可以选择一个位置 $i$ ，进行一次操作：将 $a_i$ 减去 $2$ ，将 $a_{i-1}$（如果存在）减去 $1$ ，将 $a_{i+1}$（如果存在）减去 $1$，问至少要多少次操作可以使数列中至少出现两个非正整数。

## 思路

很显然答案有 $3$ 种出现的可能：

+ 相邻两数

+ 相隔为 $1$ 的两数

+ 数列中最小两数

分情况计算即可。

第一种情况：依次枚举相邻两数（记大的数字为 $x$ ， 小的为 $y$）。如果 $x \ge 2y$，那么答案为 $\lceil \frac{x}{2} \rceil$，如果不是，则先在 $x$ 上操作 $x-y$ 次，然后 $x' = x - 2(x-y) , y'=0$，答案为 $\lceil x-y+\frac{x'}{2} \rceil$。

第二种情况：依次相隔为 $1$ 的两数（记大的数字为 $x$ ， 小的为 $y$）。这时有一个贪心策略：当两数都为正数时，在两数中间的数上操作一定最优，因为这样减去的数是 $2$。所以答案为 $y + \lceil \frac{x-y}{2} \rceil$。

第三种情况：我们不需要考虑位置，因为前两种情况包含了。为了好写，先算前两种，然后排序求就可以了。设这两个数为 $x,y$。答案为 $\lceil \frac{x}{2} \rceil + \lceil \frac{y}{2} \rceil$。

最小值即为三种答案取 $\min$。

## 代码

```
#include <bits/stdc++.h>
using namespace std;

int N;
int Num[200010];

int Ans1 = INT_MAX , Ans2 = INT_MAX, Ans3 = INT_MAX;

int Cal1(int i) {
    int x = Num[i] , y = Num[i + 1];
    if(x > y) swap(x , y);
    int res = 0;
    if(y >= x * 2) {
        res = y / 2 + (y % 2 == 1 ? 1 : 0);
        return res;
    }
    res += y - x;
    y -= 2 * res;
    x -= res;
    res += (x / 3) * 2 + x % 3;
    return res;
}

int Cal3(int i) {
    int x = Num[i - 1] , y = Num[i + 1];
    if(x > y) swap(x , y);
    return x + ((y - x) % 2 == 0 ? (y - x) / 2 : (y - x) / 2 + 1);
}

int main() {
    scanf("%d" ,&N);

    for(int i = 1; i <= N; i++) {
        scanf("%d" ,Num + i);
    }
    //答案共有三种可能：相邻两数、相隔一个的两数字、最小两数

    //case 1
    for(int i = 1; i < N; i++) {
        Ans1 = min(Ans1 , Cal1(i));
    }

    //case2
    for(int i = 2; i < N; i++) {
        Ans3 = min(Ans3 , Cal3(i));
    }

    //case 3
    sort(Num + 1 , Num + 1 + N);
    Ans2 = Num[1] / 2 + Num[2] / 2 + (Num[1] % 2 == 1 ? 1 : 0) + (Num[2] % 2 == 1 ? 1 : 0);

    // cout << Ans1 << endl << Ans2 << endl << Ans3 << endl;

    printf("%d\n" ,min(Ans1 , min(Ans2 , Ans3)));
    return 0;
}
```

---

