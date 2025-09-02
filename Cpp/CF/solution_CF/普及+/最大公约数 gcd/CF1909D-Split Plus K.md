# Split Plus K

## 题目描述

[eliteLAQ - Desert Ruins](https://soundcloud.com/lux-gg-198448038/desert-ruins)

⠀



There are $ n $ positive integers $ a_1, a_2, \dots, a_n $ on a blackboard. You are also given a positive integer $ k $ . You can perform the following operation some (possibly $ 0 $ ) times:

- choose a number $ x $ on the blackboard;
- erase one occurrence of $ x $ ;
- write two positive integers $ y $ , $ z $ such that $ y+z = x+k $ on the blackboard.

Is it possible to make all the numbers on the blackboard equal? If yes, what is the minimum number of operations you need?

## 说明/提示

In the first test case, $ k = 1 $ . You can make all the numbers on the blackboard equal to $ 2 $ with the following operations:

- Erase $ x = 4 $ and write $ (y, z) = (2, 3) $ . Note that $ y+z=x+k $ . The blackboard now contains the multiset $ \{3, 2, 3\} $ .
- Erase $ x = 3 $ and write $ (y, z) = (2, 2) $ . Note that $ y+z=x+k $ . The blackboard now contains $ \{2, 2, 2, 3\} $ .
- Erase $ x = 3 $ and write $ (y, z) = (2, 2) $ . Note that $ y+z=x+k $ . The blackboard now contains $ \{2, 2, 2, 2, 2\} $ .

This makes all the numbers equal in $ 3 $ operations. It can be shown that you cannot make all the numbers equal in less than $ 3 $ operations.

In the second test case, $ k = 3 $ . You can make all the numbers on the blackboard equal to $ 7 $ with the following operation:

- Erase $ x = 11 $ and write $ (y, z) = (7, 7) $ . Note that $ y+z=x+k $ . The blackboard now contains $ \{7, 7, 7\} $ .

In the third test case, $ k = 10 $ . You can make all the numbers on the blackboard equal to $ 40 $ with the following operations:

- Erase $ x = 100 $ and write $ (y, z) = (70, 40) $ . Note that $ y+z=x+k $ . The blackboard now contains $ \{70, 40, 40, 100\} $ .
- Erase $ x = 70 $ and write $ (y, z) = (40, 40) $ . Note that $ y+z=x+k $ . The blackboard now contains $ \{40, 40, 40, 40, 100\} $ .
- Erase $ x = 100 $ and write $ (y, z) = (40, 70) $ . Note that $ y+z=x+k $ . The blackboard now contains $ \{40, 40, 40, 40, 40, 70\} $ .
- Erase $ x = 70 $ and write $ (y, z) = (40, 40) $ . Note that $ y+z=x+k $ . The blackboard now contains $ \{40, 40, 40, 40, 40, 40, 40\} $ .

In the fourth and in the fifth test case, you can show that it is impossible to make all the numbers on the blackboard equal.

## 样例 #1

### 输入

```
9
2 1
3 4
2 3
7 11
3 10
100 40 100
2 1
1 2
2 2
1 2
1 327869541
327869541
5 26250314066
439986238782 581370817372 409476934981 287439719777 737637983182
5 616753575719
321037808624 222034505841 214063039282 441536506916 464097941819
5 431813672576
393004301966 405902283416 900951084746 672201172466 518769038906```

### 输出

```
3
1
4
-1
-1
0
3119
28999960732
-1```

# 题解

## 作者：wosile (赞：22)

非常有趣的题。

赛时做法，接近官方 Editorial。

首先我们手模几个样例。容易证明，对于任意一个 $x<k$，拆分得到的 $y+z$ 一定有一个 $<k$。$>k$ 同理。因此如果同时存在 $<k$ 和 $>k$ 的数那么无解，注意 $=k$ 的情况。

这启示我们考虑 $x-k$。

多进行一些直觉上的观察，把脑电波和出题人对一对，然后你会发现 $x+k= y+z$ 相当于把 $x$ 与 $k$ 的差拆成了两份。例如我们有 $x=6,k=3,x-k=3$，此时我们把 $x-k=3$ 拆成 $y-k=1,z-k=2$ 就有 $y=4,z=5$。

如果是数学比较好的人可能可以直接从式子上看出有形式非常好的 $(x-k)=(y-k)+(z-k)$。那么我们一开始把所有数减掉 $k$，就把问题转化成了 $k=0$ 的情况，即每次把一个数拆成两个数的和。

首先已经提到过，只有所有数的符号相同时才有解。

由于最后所有数都要相等，所以每个数拆出的若干个数也要相等，从而一个数必然拆出他的因数。显然拆出来的数越大拆的次数越少，所以我们求所有 $a$ 的 $\gcd$ 即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int n;
ll k;
ll a[200005];
int T;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%lld",&n,&k);
		for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
		sort(a+1,a+n+1);
		if((a[1]<k && a[n]>=k) || (a[1]<=k && a[n]>k)){
			printf("-1\n");
			continue;
		}
		if(a[1]==k && a[n]==k){
			printf("0\n");
			continue;
		}
		for(int i=1;i<=n;i++)a[i]=abs(a[i]-k);
		ll g=0;
		for(int i=1;i<=n;i++)g=__gcd(g,a[i]);
		ll ans=0;
		for(int i=1;i<=n;i++)ans+=a[i]/g-1;
		printf("%lld\n",ans);
	}
	return 0;
	//quod erat demonstrandum
}
```

---

## 作者：Komomo (赞：8)

考虑每个数 $a_i$ 的拆分，令 $a_i$ 拆分了 $t_i$ 次，则必须满足以下条件：

- 对于 $i\in[1,n]$，所有 $\dfrac{a_i+t_ik}{t_i+1}$ 相等。

然后这种整除式分子分母都有未知数，很典的套路就把他提取出来：

- 对于 $i\in[1,n]$，所有 $\dfrac{a_i-k}{t_i+1}+k$ 相等。

思路就很显然了，因为使 $\sum t_i$ 最小，则这个相等的数最大，求出 $\gcd\limits_{i=1}^n\{a_i-k\}$，然后直接带进去求即可，无解情况也很简单：当你算出来这个 $t_i<0$ 就不合法，由于 `__gcd` 的特性，原因显然。

```cpp
void work() {
	int n = read(), k = read(), p = 0, ans = 0;
	for (int i = 1; i <= n; i ++) a[i] = read(), p = __gcd(p, a[i] - k);
 
	if (p == 0) return printf("0\n"), void();
	for (int i = 1; i <= n; i ++) {
		int t = (a[i] - k) / p - 1; ans += t;
		if (t < 0) return printf("-1\n"), void();
	}
    
	printf("%lld\n", ans);
}
```

---

## 作者：youlv (赞：6)

首先考虑有解时如何得出答案，发现每个数的分裂都是独立的。

设一个数 $x$ 分裂成 $t$ 个数，分裂了 $t-1$ 次，并且满足分裂出的数相等，最后得到的数就是：

$$\frac{(t-1)k+x }{t}=k+\frac{x-k}{t}  $$

也就是让序列中每个数的 $\large\frac{x-k}{t}$ 相等就可以满足生成的所有数相等。

对于每一个数，为了分裂数 $t$ 最小，就要最大化 $\large\frac{x-k}{t}$，发现要求的就是每个数的 $(x-k)$ 的 $\mathsf{gcd}$，代入每个数计算分裂次数即可。

---------------------

接下来根据上面的推导，判断是否有解：

- 为了使 $\large\frac{x-k}{t}$ 相等，所有 $(x-k)$ 正负符号一定相同，否则存在两个数无论分裂多少次始终一个大于 $k$，另一个小于 $k$，一定无解。

- 特判 $x=k$ 的情况，假如所有数都满足 $x=k$，也就是一开始所有数都相等，无需操作就已经达到了目标，操作数 $0$。

- 否则如果部分数满足 $x=k$，部分不满足，不满足的部分无论分裂多少次都无法达到 $x=k$ ，此时无解。

$\mathcal{{code } } $
------------------------------------

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

constexpr int N=2e5+5;
int n,a[N],k,ans;
int gcd(int a,int b){
	if(b==0) return a;
	return gcd(b,a%b);
}
void work(){
	n=read();k=read();
	for(int i=1;i<=n;i++) a[i]=read();
	sort(a+1,a+n+1);
	if(a[1]==k&&a[n]==k) {cout<<"0\n";return;}
	if(a[1]==k||a[n]==k) {cout<<"-1\n";return;}
	if((a[1]<k)^(a[n]<k)) {cout<<"-1\n";return;}
	for(int i=1;i<=n;i++) a[i]=abs(k-a[i]); 
	int res=a[1];
	for(int i=2;i<=n;i++) res=gcd(res,a[i]);
	ans=0;
	for(int i=1;i<=n;i++) ans+=a[i]/res-1;
	cout<<ans<<'\n';
}
	
signed main(){
	int t;t=read();
	while(t--){
		work();
	}
}


```


---

## 作者：Troubadour (赞：2)

正难则反，题目要求的将一个数加上 $k$ 然后再拆开的操作感觉很不好办，所以我们考虑这个操作的逆过程，把拆分变成合并，并在其中找出答案。

设最后得到的数为一堆 $b$，设 $a_i$ 可以由 $r_i$ 个 $b$ 合并得到，则有：

$$
a_i=br_i-(r_i-1)k
$$

因为我们要求的是最少的拆分次数，也就是最少的合并次数，也就是 $\sum r_i-n$ 的最小值，对上面式子变形得到：

$$
r_i=\frac{a_i-k}{b-k}
$$

$$
\sum_{i=1}^{n} r_i=\frac{\sum\limits_{i=1}^{n}a_i-nk}{b-k}
$$

那么很显然的，我们要让 $b-k$ 尽量大。注意到 $r_i$ 都是整数，则 $b-k$ 的最大值为所有 $a_i-k$ 的最大公约数，即：

$$
(\sum_{i=1}^{n} r_i)_{\min}=\frac{\sum\limits_{i=1}^{n}a_i-nk}{\gcd\limits_{i=1}^{n}(a_i-k)}
$$

注意到还有一种情况 $a_i-k<0$，那么必然有 $b-k<0$，判断并相应处理即可。如果大于 $0$ 和小于 $0$ 的情况同时出现，则无解。

注意到还有一种情况，就是这个分母为 $0$ 了。这种可能性当且仅当所有的 $a_i$ 都等于 $k$ 时成立。

---

## 作者：EuphoricStar (赞：1)

设最后每个数都相等时为 $t$。那么一次操作变成了合并两个数 $x, y$，再增加 $x + y - k$。于是每个 $a_i$ 可以被表示成 $b_i t - (b_i - 1)k$ 的形式，化简得 $a_i - k = b_i (t - k)$。

因为 $t - k$ 对于每个 $i$ 都相同，又因为我们的目标是最小化 $\sum\limits_{i = 1}^n b_i$，所以 $t - k$ 取 $\gcd\limits_{i = 1}^n (a_i - k)$ 最优。

注意所有 $a_i - k$ 同号才合法，以及特判掉初始 $a_i$ 全部相同的情况后不能出现 $a_i = k$。

[code](https://codeforces.com/contest/1909/submission/238543260)

---

## 作者：zcxnb (赞：1)

考虑转化一下式子。

> $x+k=y+z$ -> $(x-k)=(y-k)+(z-k)$

所以我们就将所有的 $a[i]-k$，然后题目就转化成了抹掉一个数 $x$，替换成 $y,z$，满足 $x=y+z$，求最小把这个序列变成同一个数的最小操作次数。

考虑不管怎么拆分这个序列，这个序列的总和 $sum$ 是不变的，因为最后数列要拆成所有数都相同的形式，我们设这个数为 $k$，显然 $sum=tk$，最终答案即为 $t-n$。

如何求这个 $k$ 呢，考虑对于 $a[i]$ 的拆法，它的拆法是独立的并不受两边数的影响，因为它拆出来的数一定是相等的，所以可以证明 $a[i]=mk$（k是拆出来的数）中 $k$ 是 $a[i]$ 的因数。

我们现在证明了 $k$ 能被 $a[i]$ 拆出来当且仅当 $k$ 是 $a[i]$ 的因数，如何证明这是充要条件？

考虑一种拆法，$k$ 是 $a[i]$ 的因数，固有 $a[i]=mk$，我们先把 $a[i]$ 拆成 $[(m-1)k,k]$，然后再 $[(m-2)k,k,k]$ 依此类推。

所以最终我们就是要找到序列 $a$ 的最大公因数，即可求得答案。

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
int t,n,k;
int a[N];
bool check1(){
	for(int i=2;i<=n;i++){
		if(a[i]!=a[i-1])  return 0;
	}
	return 1;
}
bool check2(){
	if(a[1]==0)  return 1;
	int z=(a[1]>0);
	for(int i=2;i<=n;i++){
		if(a[i]==0)  return 1;
		if((a[i]>0)!=z)  return 1;
	}
	return 0;
}
int gcd(int x,int y){
	if(!y)  return x;
	return gcd(y,x%y);
}
signed main(){
	scanf("%lld",&t);
	while(t--){
		scanf("%lld%lld",&n,&k);
		for(int i=1;i<=n;i++){
			scanf("%lld",&a[i]);
			a[i]-=k;
		}
		if(check1()){
			printf("0\n");
			continue;
		}
		if(check2()){
			printf("-1\n");
			continue;
		}
		int num=0,tot=0;
		tot+=a[1];
		num=a[1];
		for(int i=2;i<=n;i++){
			tot+=a[i];
			num=gcd(num,a[i]);
		}
		printf("%lld\n",tot/num-n);
	}
}
```

---

## 作者：Day_Tao (赞：0)

一个有意思题。

设 $b_i$ 为第 $i$ 个数需要操作的次数。不难发现最终要使得：

$$\forall i\neq j,\frac{a_i+kb_i}{b_i+1}=\frac{a_j+kb_j}{b_j+1}$$

转化一下柿子就是使得：

$$\forall i\neq j,\frac{a_i-k}{b_i+1}+k=\frac{a_j-k}{b_j+1}+k$$

即：

$$\forall i\neq j,\frac{a_i-k}{b_i+1}=\frac{a_j-k}{b_j+1}$$

$\sum\limits_{i=1}^n b_i$ 就是我们要求的答案。要使 $\sum\limits_{i=1}^n b_i$ 最小，就要使 $\sum\limits_{i=1}^n\frac{a_i-k}{b_i+1}$ 最大，又不难发现 $\sum\limits_{i=1}^n\frac{a_i-k}{b_i+1}$ 的最大值其实就是 $\gcd\limits_{i=1}^n (a_i-k)$。这样我们就可以先算出所有 $a_i-k$ 的最大公约数，再求出对应的 $b$。无解当且仅当 $\exists b_i<0$。时间复杂度 $O(n\log n)$。注意 $\gcd$ 为 $0$ 的时候的 corner cases，特判输出 $0$ 即可。

**Code：**

```cpp
inline void solve()
{
	n=read(),k=read(),ans=GCD=0;
	for(int i=1;i<=n;i++)a[i]=read()-k,GCD=__gcd(GCD,a[i]);
	if(GCD==0)return puts("0"),void();
	for(int i=1;i<=n;i++)
		{ans+=a[i]/GCD-1;if(a[i]/GCD-1<0)return puts("-1"),void();}
	printf("%lld\n",ans);
	return ;
}
```

---

## 作者：naroto2022 (赞：0)

# CF1909D 题解

### 题面

[原题传送门](https://www.luogu.com.cn/problem/CF1909D)

### 思路

首先，看懂题后直接先观察式子，盯着盯着感觉有点感觉。

$x+k=y+z$，看这个式子 $x,y,z$ 并没有什么相同的地方，一边有 $k$，一边没 $k$，所以考虑两边同时减 $2k$。

$x+k-2k=y+z-2k$，整理下。

$x-k=(y-k)+(z-k)$，这下看舒服多了，结合下题意，顿时感觉简单多了，这不就是把一个数给分成两个数吗？只要在输入 $a$ 数组的时候将每个数都减去 $k$ 就可以将问题转换了！

但是别急，这还没完，转换完后还是要做题的（以下称的数组 $a$ 均为减 $k$ 后的）。

首先先看无解的情况都有什么条件，容易想到当处理过的数组正负零相间的时候是无解的，证明也非常好证，因为一个正数分解必然至少有一个数为正数，负数必然有一个数是负数，$0$ 要么是两个 $0$，要么一正一负，这样一看怎么分解都无法同一整个数组的正负性，更别说是让这个数组相同。

接下来考虑特殊情况，有两个：

1. $a$ 全是 $0$ 的情况，很简单，在统计正负零的个数时即可判断是否出现这种情况，出现的话就是输出 $0$，因为不需要操作所有的数都一样了。
2. $n=1$ 时，这种情况也一样直接输出 $0$，因为就一个数，必然是整个数组都是相同的。

最后考虑普遍情况：对于一个处理过的数组 $a$，如何用最小的拆分步数让所有数都相同，发现一个数拆分到最后必然是多个相同的数，而这个数必然是原来的数的因数，于是容易想到步数最少的情况下最后整个数组的数都为 $num=\gcd(a_1,a_2,a_3,\cdots,a_n)$，而答案就为 $\begin{aligned}\sum_{i=1}^{n}\frac{a[i]}{num}-1\end{aligned}$。

于是就可以 AC 这道题了~~~

### 代码


```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#define ll long long
using namespace std;
const int MN=200005;
ll T,n,k,ans,num,a[MN],l,z,f;//l统计0的个数，z统计正数的个数，f统计负数的个数，num是计算公约数。 
ll gcd(ll a, ll b){return b?gcd(b,a%b):a;}//计算公约数。 
ll read(){ll x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*f;}
void solve(){
	n=read();k=read();l=z=f=ans=0;/*别忘了初始化。*/for(int i=1; i<=n; i++) a[i]=read()-k,z+=(a[i]>0),f+=(a[i]<0),l+=(a[i]==0);//输入的时候直接统计。 
	if(n==1){printf("0\n");return;}//只有一个数字肯定是都相同的，不用操作。 
	if(!z&&!f&&l){printf("0\n");return;}//只有0的话也是同理，不用操作，均为0。 
	if((z&&f)||(z&&l)||(f&&l)){printf("-1\n");return;}//要是正负0其中至少2个是相间的，必然无解。 
	for(int i=1; i<=n; i++) num=(i==1?a[1]:gcd(num,a[i]));//统计公约数 
	for(int i=1; i<=n; i++) ans+=a[i]/num-1;
	printf("%lld\n",ans);
}
int main(){
	T=read();while(T--) solve();//多测记得换行 
	return 0;
}
```

---

## 作者：User_Authorized (赞：0)

观察到操作对于每一个数的影响是独立的，所以可以分别考虑每一个数。

若一个数 $x$ 共被操作了 $y$ 次，那么最终会得到的值为

$$\dfrac{x + yk}{y + 1}$$

进行一些变换，可以得到

$$k + \dfrac{x - k}{y + 1}$$

那么我们的目标是使得所有数的 $\dfrac{x - k}{y + 1}$ 均相等，不难想到这个值就是所有 $x - k$ 的最大公约数。

可以发现分式的值取最大公约数时合法且 $y$ 最小，若取最大公约数的因子，那么 $y$ 会更大，所以我们只需要取最大公约数即可。

---

