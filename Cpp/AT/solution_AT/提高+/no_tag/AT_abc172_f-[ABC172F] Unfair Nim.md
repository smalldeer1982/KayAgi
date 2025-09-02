# [ABC172F] Unfair Nim

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc172/tasks/abc172_f

石の山が $ N $ 個あり、$ i $ 番目の山には $ A_i $ 個の石があります。

これを使って青木君と高橋君が次のようなゲームをしようとしています。

- 青木君から交互に、次の操作を繰り返す
  - 操作：石の山を $ 1 $ つ選び、そこから $ 1 $ 個以上の石を取り除く
- 先に操作ができなくなった方の負け

このゲームは、両者が最適に行動する場合、ゲーム開始時の各山の石の個数のみによって、先手必勝か後手必勝かが決まります。

そこで高橋君は、ゲームを始める前に、 $ 1 $ 番目の山から $ 0 $ 個以上 $ A_1 $ 個未満の石を $ 2 $ 番目の山に移すことで、後手の高橋君が必勝となるようにしようとしています。

そのようなことが可能なら移動する石の個数の最小値を、不可能ならかわりに `-1` を出力してください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 300 $
- $ 1\ \leq\ A_i\ \leq\ 10^{12} $

### Sample Explanation 1

石の移動をしなかった場合、青木君が最初に $ 1 $ 番目の山から $ 2 $ 個の石を取り除くと、高橋君はその後どのように行動しても負けてしまいます。 ゲームを始める前に $ 1 $ 番目の山から $ 1 $ 個の石を移動して、石の個数を $ 4,4 $ とした場合、適切な行動を取ることで、高橋君は必ず勝つことができます。

### Sample Explanation 2

$ 2 $ 番目の山から $ 1 $ 番目の山へ石を移すことはできません。

### Sample Explanation 3

$ 1 $ 番目の山のすべての石を移すことはできません。

### Sample Explanation 5

オーバーフローに注意してください。

## 样例 #1

### 输入

```
2
5 3```

### 输出

```
1```

## 样例 #2

### 输入

```
2
3 5```

### 输出

```
-1```

## 样例 #3

### 输入

```
3
1 1 2```

### 输出

```
-1```

## 样例 #4

### 输入

```
8
10 9 8 7 6 5 4 3```

### 输出

```
3```

## 样例 #5

### 输入

```
3
4294967297 8589934593 12884901890```

### 输出

```
1```

# 题解

## 作者：Fan_sheng (赞：9)

写一个简单一点的贪心做法。

前面的转化都很显然了，不会的可以参考其他题解。

现在相当于要解决这个问题：求最大的 $A$，使得

$$
\left\{
\begin{aligned}
A+B&=a_1+a_2\\
A\ \text{xor}\ B&=\text{xor}_{i=3}^na_i\\
0<A&\le a_1
\end{aligned}
\right.
$$

考虑贪心：初始令 $A,B$ 等于 $0$。从最高位开始，$A\ \text{xor}\ B$ 的第 $i$ 位为 $1$，如果 $A+2^i\le a_1$，令 $A+=2^i$，否则 $B+=2^i$。

这里有一个严重漏洞，就是 $A\ \text{xor}\ B$ 的第 $i$ 位为 $0$，应该怎么填？无论是选择都填 $1$ 还是都填 $0$，你无法保证 $A+B=a_1+a_2$。

那么我们考虑结论：

$$
A\ \text{xor}\ B=A+B-2(A\ \text{and}\ B)
$$

因为当 $A,B$ 某一位都为 $1$，异或会消成 $0$，而其他情况相当于普通加法。

我们可以直接算出 $A\ \text{and}\ B$ 的值，这样就确定了哪些位置都填 $1$，可以直接套用之前的贪心解决。

算出最大的 $A$ 后，再倒回来判断所有无解情况即可。

Code

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int n;
ll a[303];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
	ll targ=0;
	for(int i=3;i<=n;i++)targ^=a[i];
	ll C=(a[1]+a[2]-targ)/2,A=C,B=C;
	for(int i=42;i>=0;i--)if((targ>>i)&1){
		if(A+(1ll<<i)<=a[1])A+=(1ll<<i);
		else B+=(1ll<<i);
	}
	if(A>a[1]||B<a[2]||(A^B)!=targ||!A||A+B!=a[1]+a[2])puts("-1"),exit(0);
	printf("%lld",a[1]-A);return 0;
}
```


---

## 作者：2018ljw (赞：1)

非常有趣的小构造。

首先根据 nim 规则可知，后手必胜当且仅当每堆石子数异或和为 $0$。

由于只有前两堆会变，我们直接预处理出后 $n-2$ 堆石子异或和，记为 $p$。

关注到前两堆无论怎么倒腾石子总和是不变的，记为 $q=a_1+a_2$。

那么我们的任务相当于构造一组 $(x,y)$，满足：

$$
\begin{cases}x\;\operatorname{bitxor}\;y=p\\x+y=q\\1\le x\le a_1\end{cases}
$$

在此基础上，我们需要最大化 $x$。

首先处理最麻烦的：异或。令 $x=p$，$y=0$。

将 $x$，$y$ 拆成二进制，对每一位考虑：

1. 若第 $i$ 位构成为 $(1,0)$，我们可以将其变成 $(0,1)$，和不变。
2. 若第 $i$ 位构成为 $(0,0)$，我们可以将其变成 $(1,1)$，和加上 $2^{i+1}$。

那么就很明显了。若 $p>q$ 直接无解，否则记 $\Delta_1=q-p$，若 $\Delta_1$ 二进制第 $i$ 位为 $1$，那么把 $x,y$ 的 $i-1$ 位都变成 $1$。如果这一位不存在，或者 $x$ 这一位已经是 $1$，那么无解。

至此，我们的 $(x,y)$ 已经满足前两个条件了。不难发现，我们构造的 $x$ 是此时所有满足条件一二的点对中，最大的一个。那么如果 $x\le a_1$，直接输出即可。

否则记 $\Delta_2=x-a_1$，这时候我们就要利用第一条性质了。

记录所有的 $(1,0)$ 位，对第 $i$ 位操作的话 $x$ 会减少 $2^i$，我们的目标，就是从这些 $2^i$ 中选出一些数，使其和 $\ge \Delta_2$ 且最小。

大冤种可以考虑转成二进制后二分跑数位 dp，我们考虑更优的解法。

关注到二进制每一位要么是 $0$ 要么是 $1$，从高往低考虑每一位：

1. 可填 $0/1$，$\Delta_2$ 对应位为 $1$；或可填 $0$，对应位为 $0$：这一位没得选，直接填上。
2. 可填 $0/1$，$\Delta_2$ 对应位为 $0$：存在一种可行方案，即这一位填 $1$，后面全填 $0$。
3. 可填 $0$，$\Delta_2$ 对应位为 $1$：不管怎么填都只会小于后者，不再考虑后面。

换而言之，我们要找到一个位置，使得这个位置满足条件 $2$，并且前面位置填的数和 $\Delta_2$ 完全一致。

为了最小化，这个位置自然越小越好，枚举即可。

如此，我们就构造出了解。需要注意若最后的 $x\le 0$ 或找不到合法位置，依旧无解。

```cpp
#include<cstdio>
bool p[41];
int main(){
	int n,i;
	long long xr=0,sm=0,a1;
	scanf("%d",&n);
	for(i=1;i<=n;i++){
		long long x;
		scanf("%lld",&x);
		if(i<=2)sm+=x;
		else xr^=x;
		if(i==1)a1=x;
	}
	if(xr>sm)return printf("-1"),0;
	long long dlt=sm-xr,x=xr,y=0;
	for(i=0;i<=40;i++){
		if(!(dlt&(1ll<<i)))continue;
		if(!i||(x&(1ll<<i-1)))return printf("-1"),0;
		y|=1ll<<i-1;
	}
	x|=y;
	if(x<=a1)return printf("%lld",a1-x),0;
	for(i=0;i<=40;i++){
		if(!(x&(1ll<<i)))continue;
		if(y&(1ll<<i))continue;
		p[i]=1;
	}
	dlt=x-a1;
	long long res=-1,sum=0;
	for(i=40;i>=0;i--){
		bool p1=p[i],p2=dlt&(1ll<<i);
		if(!p1&&p2)break;
		else if(!p1&&!p2)continue;
		else if(!p2)res=sum+(1ll<<i);
		else sum+=1ll<<i;
	}
	x-=res;
	if(x<=0||x>a1)printf("-1");
	else printf("%lld",a1-x);
}
```

---

## 作者：CarroT5656 (赞：0)

**题目大意**

有 $n$ 堆石子。两个人轮流在任意一堆石子中取任意多个。	

让你从第 $1$ 堆石子中取出一些，放到第 $2$ 堆，使得后手必胜。

最小化这个答案。

**解法分析**

一个经典的博弈问题，当 $\bigoplus a_i=0$ 时，后手必胜。

即让你找到一个 $(x,y)$，满足：

* $x+y=a_1+a_2$

* $0< x\le a_1$

* $x\oplus y= \bigoplus_{i=3}^n a_i$

在此基础上，要让 $x$ 尽可能大。

显然 $\bigoplus_{i=3}^n a_i$ 的值是可以提前算出来的。

考虑到异或实际上就是不进位的二进制加法，那么有 $x\oplus y=x+y-2(x\ \text{and}\ y)$。

然后观察上面的式子，$x\oplus y$ 和 $x+y$ 都是已知的，那么就可以知道 $x\ \text{and}\ y$ 的值。

由异或和按位与的性质可以知道，$x\ \text{and}\ y$ 中为 $1$ 的位，$x$ 和 $y$ 的那一位都为 $1$；$x \oplus y$ 为 $1$ 的位，$x$ 和 $y$ 中恰好一个那一位为 $1$。

你同时还要满足 $x$ 尽可能大且 $x\le a_1$。所以就在 $x\le a_1$ 的情况下，尽可能地选择较高的位，并将那一位变为 $1$。

时间复杂度 $O(n+\log w)$。

**Code**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define N 305
#define db double
#define pb push_back
#define F first
#define S second
typedef pair<ll,ll> pll;
void Max(ll &x,ll y){if(y>x) x=y;}
void Min(ll &x,ll y){if(y<x) x=y;}
ll n,a[N],p,q,r,ans1,ans2;
int main(){
	scanf("%lld",&n);
	for(ll i=1;i<=n;i++) scanf("%lld",&a[i]);
	for(ll i=3;i<=n;i++) p^=a[i];
	q=a[1]+a[2];
	r=(q-p)/2;
	ans1=ans2=r;
	for(ll i=42;i>=0;i--){
		if((p>>i)&1ll){
			if(ans1+(1ll<<i)<=a[1]) ans1+=(1ll<<i);
			else ans2+=(1ll<<i);
		}
	}
	if(ans1+ans2==q&&(ans1^ans2)==p&&ans1>0&&ans1<=a[1]&&ans2>=a[2]) printf("%lld\n",a[1]-ans1);
	else printf("-1\n");
	return 0;
}
```

---

