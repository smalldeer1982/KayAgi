# [ARC174D] Digit vs Square Root

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc174/tasks/arc174_d

$ T $ 個のテストケースについて、以下の問題に答えてください。

整数 $ N $ が与えられるので、以下の条件を全て満たす整数 $ x $ の個数を求めてください。

- $ 1\ \le\ x\ \le\ N $
- $ y\ =\ \lfloor\ \sqrt{x}\ \rfloor $ とする。このとき、 $ x,y $ 双方を (先頭に $ 0 $ を含まずに) 十進法で書き下した場合、 $ y $ が $ x $ の接頭辞になる。

## 说明/提示

### 制約

- $ T $ は $ 1\ \le\ T\ \le\ 10^5 $ を満たす整数
- $ N $ は $ 1\ \le\ N\ \le\ 10^{18} $ を満たす整数
 
### Sample Explanation 1

この入力には、 $ 2 $ 個のテストケースが含まれます。 - $ 1 $ つ目のテストケースについて、 $ x=1 $ は $ y\ =\ \lfloor\ \sqrt{1}\ \rfloor\ =\ 1 $ となり問題文中の条件を満たします。 - $ 2 $ つ目のテストケースについて、例えば $ x=100 $ は $ y\ =\ \lfloor\ \sqrt{100}\ \rfloor\ =\ 10 $ となり問題文中の条件を満たします。

## 样例 #1

### 输入

```
2
1
174```

### 输出

```
1
22```

# 题解

## 作者：wosile (赞：6)

怎么会有这么蠢的 ARC D。

赛时做法：打表看哪些数符合条件，发现对于 $k\in \mathbb{N}$，满足以下两个之一的 $x\in \mathbb{N}$ 符合条件：

- $x=100^k-2\times10^k$（$k=3$ 时形如 $\lfloor\sqrt{998000}\rfloor=998$）

- $x\in[100^k-10^k,100^k+10^k)$（$k=3$ 时形如 $\lfloor\sqrt{999000}\rfloor=999$ 和 $\lfloor\sqrt{1000999}\rfloor=1000$）

枚举 $k$（代码中是 $b=10^k$），直接计算区间交即可，时间复杂度 $O(T\log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int T;
typedef long long ll;
int main(){
	scanf("%d",&T);
	while(T--){
		ll n;
		scanf("%lld",&n);
		ll ans=1;
		for(ll b=10;b<=1000000000;b*=10){
			ll B=b*b;
			if(n>=B-b-b)ans++;
			if(n>=B-b)ans+=min(B+b-1,n)-B+b+1;
		}
		printf("%lld\n",ans);
	}
	return 0;
	//quod erat demonstrandum
}
```

看起来很玄学，其实可以感性理解一下。首先题目中的性质比较稀有，大部分数都不满足这个条件，只有接近 $100^k$ 的数才会满足。开头是 $10^k$ 的对应 $[100^k,100^k+10^k)$，开头是 $10^k-1$ 的对应 $[100^k-10^k,100^k)$，开头是 $10^k-2$ 的对应 $100^k-2\times10^k$ 一个。

---

## 作者：incra (赞：1)

### Solution
赛时把 D 当 T1，喜提 D 题首 A。

看完题目，马上想到打暴力代码看答案的规律，然后就发现如下规律（暴力代码都会写吧）：

1. $\underset{k-1}{\underbrace{{999\dots9}}}8\underset{k}{\underbrace{{000\dots0}}}$。
2. $\underset{k}{\underbrace{{999\dots9}}}\underset{k}{\underbrace{{000\dots0}}}\sim1\underset{k}{\underbrace{{000\dots0}}}\underset{k}{\underbrace{{999\dots9}}}$。

然后对于这些区间（第一个就是单独一个点），求和 $[1,n]$ 的区间交的长度和。

附：两个区间 $[l1,r1]$ 和 $[l2,r2]$ 的区间交为 $[\max\{l1,l2\},min\{r1,r2\}]$，如果区间左端点大于右端点那么区间交为空。

### Code
[Link](https://atcoder.jp/contests/arc174/submissions/51385766)。

---

## 作者：Link_Cut_Y (赞：1)

讲一下赛时做法。

首先看起来没什么思路。不妨打表，观察那些数满足条件。按照题解规范，应该把打表的代码放上来一下：

```cpp
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cmath>
#define rep(i, a, b) for (int i = (a); i <= (b); i ++ )
#define rop(i, a, b) for (int i = (a); i < (b); i ++ )
#define dep(i, a, b) for (int i = (a); i >= (b); i -- )
#define dop(i, a, b) for (int i = (a); i > (b); i -- )

using namespace std;

int stk[110], top, ans;
int bin[100000], T, n;
bool check(int n) {
	int s = (int)sqrt(n);
	top = 0; while (n) stk[ ++ top] = n % 10, n /= 10;
	int ss = 0; while (top) {
		ss = ss * 10 + stk[top -- ];
		if (ss >= s) break;
	} if (ss == s) return 1; return 0;
}
signed main() {
	rep(i, 1, 10010)
		if (check(i)) cout << i << ' ' << (int)sqrt(i) << endl;
	rep(i, 1, 99999) if (bin[i]) cout << i << ' ' << bin[i] << endl;
}
```

把所有合法的数打印下来，不难发现，只有下面这样的数是满足条件的：

- $\texttt{999...8000...0}$，即一串 $9$，一个 $8$，后面跟上相同位数的 $0$。如 $998000$。

- $\texttt{999...9???...?}$，即一串 $9$，后面跟上等位数的任意数。如 $999837$。

- $\texttt{1000...0???...?}$，即 $1$ 后面跟上一串 $0$，后面再跟上等位数的任意数。例如 $1000873$。

这样问题就变得简单。直接枚举 $\sqrt{n}$ 的位数，进行暴力判断即可。复杂度 $O(1)$。有比较多的 corner case，建议配合代码食用。[submission](https://atcoder.jp/contests/arc174/submissions/51396441)。

---

## 作者：_JF_ (赞：0)

[[ARC174D] Digit vs Square Root ](https://www.luogu.com.cn/problem/AT_arc174_d)


~~我也是打表老哥。~~

最先想出来的肯定是对每个 $\sqrt x$ 考虑，考察它影响到的区间，然后去算贡献。

然后发现过不了。感性观察到，可能造成的贡献的数不会太多，因为约束条件较强。

所以考虑打表观察，然后发现：

- $1$ 可以造成贡献。
- 对于 $n$ 是 $10$ 的倍数，观察到 $n-2$，$n-1$，$n$ 分别能造成贡献。假设 $n-2$ 数位为 $x$。

具体地：

- 对于 $n-2$，$(n-2)\times 10^x$ 能造成贡献。
- 对于 $n-1$，$[(n-1)\times 10^x,(n-1)\times 10^x+n-1]$ 能造成贡献。
- 对于 $n$，$[n\times 10^x,n\times 10^x+n-1]$ 能造成贡献。

然后就做完了。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long 
signed main(){
	int t,n;
	cin>>t;
	while(t--){
		int ans=1;
		__int128 pre=8,pre1=9,pre2=10,now=10;
		cin>>n;
		while(1){
			int dus=pre*now;
			if(n>=dus)	ans++;
			else break;
			dus=pre1*now;
			if(n>=dus){
				if(n>=dus+pre1)	ans+=(pre1+1);
				else	{ans+=(n-dus+1); break;}
			}
			else	break;
			dus=pre2*now;
			if(n>=dus){
				if(n>=dus+pre1)	ans+=pre2;
				else{	ans+=n-dus+1; break;}
			}
			pre=pre+9*now,pre1+=9*now,pre2*=10,now*=10;
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：Iniaugoty (赞：0)

### [ARC174D Digit vs Square Root](/problem/solution/AT_arc174_d)

~~神题~~ 神金题。

打表。

```cpp
F(i, 1, 1e6) {
  int j = sqrt(i);
  for (int k = 1; k <= i; k *= 10)
    if (i / k == j)
      { cout << i << " " << j << "\n"; break; }
}
```

然后你会发现这些数满足条件：

- $x = 10 ^ {2k} - 2 \times 10 ^ {k}$，$\lfloor \sqrt x \rfloor = 10 ^ k - 2$。

- $x \in [10 ^ {2k} - 10 ^ k, 10 ^ {2k} - 1]$，$\lfloor \sqrt x \rfloor = 10 ^ k - 1$。

- $x \in [10 ^ {2k}, 10 ^ {2k} + 10 ^ k - 1]$，$\lfloor \sqrt x \rfloor = 10 ^ k$。

然后随便做做就行了。时间复杂度 $O(\log V)$。

[code](https://atcoder.jp/contests/arc174/submissions/57824872)。

---

## 作者：WhileTrueRP (赞：0)

### ARC174B

对于此类题目，没有思路不妨先去打表，若打表发现了规律，就直接用规律，否则，可以尝试分段打表的方式骗分。

打表程序不难实现：

```cpp
#include<bits/stdc++.h>
using namespace std;
bool f(int x){
	int t = sqrt(x);
	while(x){
		if(x == t){
			return true;
		}
		x /= 10;
	}
	return false;
}
int main(){
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		if(f(i)){
			printf("%d ",i);
		}
	}
}
```

将打表的结果整理一下发现 $[1,2000000]$ 符合条件的区间为 $\{1\}\cup\{80\}\cup[90,109]\cup\{9800\}\cup[9900,10099]\cup\{998000\}\cup[999000,1000999]$。

不难发现规律一共为两种情况，即 $[10^{2k}-10^k,10^{2k}+10^k-1]$ 和 $\{10^{2k}-2\times10^{k}\}$。

枚举其中的 $k$，求解即可。

[完整代码](https://atcoder.jp/contests/arc174/submissions/55653327)

---

## 作者：Elysian_Realme (赞：0)

# AT_arc174_d

## 解题思路

~~一眼数位 dp。~~

数位显然做不了（在这卡了十几分钟）。

没有思路不妨先打个表：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
signed main(){
	for(int i=1;i<=1e18;i++){
		int a=sqrt(i),t=i;
		while(t>a)t/=10;
		if(t==a)cout<<i<<"\n";
	}
	return 0;
}
```

输出太长就不贴了。

我们发现它很有规律，（除了最开始那个 `1`）我们可以把他们分成很多组：

每组开头的数是 $i$ 个 `9`，接下来是一个 `8`，然后后面有 $i-1$ 个 `0`。

中间是从  $i+1$ 个 `9`，后面有 $i-1$ 个 `0` 这个数，到一个 `1` 加 $i+1$ 个 `0` 再加 $i$ 个 `9` 这个数。

这样，我们就可以用一个很丑的代码过掉这题，枚举 $i$ 并把每一种情况都分类讨论。

```cpp
// LUOGU_RID: 154945777
// Problem: D - Digit vs Square Root
// Contest: AtCoder - AtCoder Regular Contest 174
// URL: https://atcoder.jp/contests/arc174/tasks/arc174_d
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// 
// By：lmq
// AC Time：2024-04-08 19:43:24

#include <bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int t,n,sum;
signed main(){
	cin>>t;
	while(t--){
		cin>>n;
		sum=1;
		for(int i=1;i<=9;i++){
			int dl=0,s=0,e=1;
			for(int j=1;j<i;j++)
				dl*=10,dl+=9;
			dl*=10,dl+=8;
			dl*=pow(10,i);
			s=dl+1*pow(10,i);
			e=pow(10,i);
			for(int j=1;j<=i;j++)
				e*=10,e+=9;
			if(n<dl){
				cout<<sum<<endl;
				break;
			}else if(n>=dl&&n<s){
				cout<<sum+1<<endl;
				break;
			}else if(n>=s&&n<=e){
				cout<<sum+1+n-s+1<<endl;
				break;
			}
			sum+=1+e-s+1;
		}
	}
	return 0;
}
```

---

## 作者：Sorato_ (赞：0)

# ARC174D Digit vs Square Root

## 题目大意

给定 $N$，求有多少个正整数 $x(1\leq x\leq N)$ 满足：在十进制表示下，$\lfloor x\rfloor$ 是 $x$ 的前缀。

## Solve

很难直接手推性质，考虑用如下程序打表：

```c++
#include<bits/stdc++.h>
#pragma GCC optimize(1,2,3,"Ofast","inline")
using namespace std;
#define int long long
inline bool check(int x,int y)
{
	stack<int>a,b;
	while(x)
		a.push(x%10),x/=10;
	while(y)
		b.push(y%10),y/=10;
	while(!a.empty())
	{
		if(a.top()!=b.top())	return 0;
		a.pop();b.pop();
	}
	return 1;
}
signed main()
{
	int res=0,j,lst;
	for(int i=1;i<=1000000;i=-~i)
	{
		j=i;lst=res;
		while(check(sqrt(j*1.0),j))	j=-~j,res=-~res;
		if(j>i)	printf("%lld~%lld: %lld~%lld\n",i,j-1,-~lst,res);
		i=j;
	}
	return 0;
}
```

得到：

```
1~1: 1~1
80~80: 2~2
90~109: 3~22
9800~9800: 23~23
9900~10099: 24~223
998000~998000: 224~224
999000~1000999: 225~2224
```

我们不难可以发现这样的性质：

**区间 $\large[10^i-10^{\frac i 2},10^i+10^{\frac i 2}-1]$（即 $\large1,90\sim109,9900\sim10099$）中的所有数 以及 $\large10^i-2\times 10^{\frac i 2}$（即 $\large80,9800,998000$）满足条件（$\large i$ 均为偶数）**。

仔细想一下，确实很对。

对于区间 $[10^i-10^{\frac i 2},10^i+10^{\frac i 2}-1](i\mod 2=0)$，我们将他拆成 $[10^i-10^{\frac i 2},10^i-1]$ 和 $[10^i,10^i+10^{\frac i 2}-1]$ 来考虑：

- 对于 $[10^i-10^{\frac i 2},10^i-1]$，即 $9900\sim9999,999000\sim999999$，显然他们开根向下取整都是 $10^{\frac i 2}-1$，即 $99,999$，而且它们的前 $\frac i 2$ 位也是 $10^{\frac i 2}-1$。并且这些数的数位都是偶数，对于每个 $i$ 有 $10^{\frac i2}$ 个。

- 对于 $[10^i,10^i+10^{\frac i 2}-1]$，即 $10000\sim10099,1000000\sim1000999$，它们开根向下取整都是 $10^{\frac i 2}$，即 $100,1000$，而它们的前 $\frac i 2$ 位也是 $10^{\frac i 2}$。并且这些数的数位都是奇数，，对于每个 $i$ 有 $10^{\frac i2}$ 个。

对于 $10^i-2\times 10^{\frac i 2}$，即 $80,9800,998000$：

- $(10^{\frac i 2}-1)^2=10^i-2\times 10^{\lfloor\frac i 2\rfloor}+1$，所以 $\lfloor\sqrt{10^i-2\times 10^{\frac i 2}}\rfloor=10^{\frac i 2}-2$，即 $\lfloor\sqrt{80}\rfloor=8,\lfloor\sqrt{9800}\rfloor=98,\lfloor\sqrt{998000}\rfloor=998$，显然 $10^{\frac i 2}-2$ 是 $10^i-2\times 10^{\frac i 2}$ 的前缀，而不是 $10^i-2\times 10^{\frac i 2}-x$ 的前缀。这些数的数位都是偶数，，对于每个 $i$ 有 $1$ 个。

所以思路就很显然了：

- 首先处理出 $1\sim 10^i-1$ 之间的所有符合条件的数的个数 $sum_i$。

- 对于每次询问，判断出 $N$ 的位数 $m$，无论 $m$ 是奇数还是偶数，答案 $ans$ 都可以先加上 $sum_{i-1}$。
- 若 $m$ 是偶数：如果 $m\geq 10^m-2\times 10^{\frac m 2}$，令 $ans$ 加上 $1$；如果 $N\geq 10^m-10^{\frac m 2}$，令 $ans$ 加上 $N-(10^m-2\times 10^{\frac m 2})+1$。
- 若 $m$ 是奇数：令 $ans$ 加上 $\min(N,10^{m-1}+10^{\lfloor\frac m 2\rfloor}-1)-10^{m-1}$。

## Code

```c++
#include<bits/stdc++.h>
#pragma GCC optimize(1,2,3,"Ofast","inline")
using namespace std;
#define int long long
inline int read()
{
	short f=1;
	int x=0;
	char c=getchar();
	while(c<'0'||c>'9')	{if(c=='-')	f=-1;c=getchar();}
	while(c>='0'&&c<='9')	x=(x<<1)+(x<<3)+(c^48),c=getchar();
	return x*f;
}
inline int Get(int x)
{
	int res=0;
	while(x)
		res=-~res,x/=10;
	return res;
}
int t,n,sum[20],mi[20]={1},ans;
signed main()
{
	for(int i=1;i<=18;i=-~i)
	{
		mi[i]=mi[i-1]*10;
		sum[i]=sum[i-1]+mi[i/2];
		if(i%2==0)	sum[i]=-~sum[i];
	}
//	cout<<sum[3];
	t=read();
	while(t--)
	{
		n=read();
		int res=Get(n);
//		cout<<res<<endl;
		ans=sum[res-1];
		if(res%2==0)
		{
//			puts("into Case 1");
			if(n>=mi[res]-2*mi[res/2])	ans=-~ans;
			if(n>=mi[res]-mi[res/2])	ans+=n-(mi[res]-mi[res/2])+1;
		}
		else	ans+=min(n,mi[res-1]+mi[res/2]-1)-mi[res-1]+1;
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：Starrykiller (赞：0)

Update on 3.21：补充了证明。

Update on 3.22：被打回，微调了格式。

找规律题。打个表，会发现：

- $1$ 满足条件。

- 对于 $k\ge 1$，$10^{2k}-2\cdot 10^{2k-1}$，$10^{2k}-10^k$，$10^{2k}-10^k+1\sim 10^{2k}+10^k-1$ 满足条件。

证明：$1$，$10^{2k}$ 满足条件是平凡的。

- 关于形如 $10^{2k}-2\cdot 10^k$ 的数。

由于 $10^{2k}-2\cdot 10^k\lt 10^{2k}-2\cdot 10^k+1=(10^k-1)^2$，所以 $\lfloor\sqrt {10^{2k}-2\cdot 10^k}\rfloor=10^k-2\lt 10^k-1$。$10^k-2$ 的形式显然满足是 $10^{2k}-2\cdot 10^k$ 的前缀。

- 关于形如 $10^{2k}-10^{k}\sim 10^{2k}-1$ 的数。

由上面的结论知道，$(10^k-1)^2\lt 10^{2k}-10^k\lt 10^{2k}-1\lt 10^{2k}$，所以在这个区间内的数开平方向下取整一定是 $10^{k}-1$。

而，$10^{2k}-10^k\sim 10^{2k}-10^k+1$ 的前面必然有 $k$ 个 $9$，即是 $\overline{\underbrace{99\cdots9}_{k \text{ 个}}\underbrace{????}_{{k \text{ 个}}}}$ 的形式，满足 $10^k-1=\overline{\underbrace{99\cdots 99}_{k \text{ 个}}}$ 是其前缀。

- 关于形如 $10^{2k}+1\sim 10^{2k}+10^k-1$ 的数。

显然 $10^{2k}\lt 10^{2k}+1\lt 10^{2k}+10^k-1\lt (10^k+1)^2$。所以在这个区间内的数开平方向下取整一定是 $10^{k}$。

类似地做出讨论可以发现满足条件。

于是直接枚举 $k$ 就可以了，时间复杂度 $\Theta(T\log n)$。

[My Submission](https://atcoder.jp/contests/arc174/submissions/51395982).

---

