# Game with Powers

## 题目描述

Vasya 和 Petya 写下了 $1\sim n$ 的所有整数来玩“乘方”游戏（$n$ 可以很大，但是，Vasya 和 Petya 并不被此事实迷惑）。

玩家轮流选择数（Vasya 先选）。如果这一轮 $x$ 被选择，以后将不能选择 $x$ 或其所有正整数幂（也就是 $x^2,x^3,\dots$）。例如，如果 $9$ 在第一轮被选择，玩家以后将不能选择 $9$ 或 $81$，但是仍然可以选择 $3$ 或 $27$。如果一个玩家不能再选数了，他就输了。

如果 Vasya 和 Petya 两个人都以最佳方案玩，那么谁会赢？

## 说明/提示

在样例 $1$ 中，Vasya 将选 $1$，然后立即胜利。

在样例 $2$ 中，不管 Vasya 第一轮选什么数，Petya 可以选剩余的数然后胜利。

## 样例 #1

### 输入

```
1
```

### 输出

```
Vasya
```

## 样例 #2

### 输入

```
2
```

### 输出

```
Petya
```

## 样例 #3

### 输入

```
8
```

### 输出

```
Petya
```

# 题解

## 作者：liangzihao (赞：5)

我们可以把一些能用同样底数的幂次分组，即分成$c,c^2,c^3....$，为了让分开的集合相互独立，$c$不能表示成其他数（除了$c^1$）的幂形式。既然已经同底数了，所以可以理解为每次可以取一个数$i\in[1,k]$，当选了$i$时，$i*j$不能选，$k$为满足$c^k<=n$的最大整数，问谁能赢的问题。

因为$n≤1e9$，所以$2^{30}>1e9$ ，所以$k<30$ 。对于每一个组，都相当于一个$NIM$游戏，可以用$sg$函数求解，再把所有组的$sg$异或起来。我们可以打表打出大小为$[1,30]$的组的$sg$值。

打表代码如下：

```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#include <map>

using namespace std;

map <int,int> h;

int a[35],n,g;

int dfs(int x)
{
	if ((x==0) || (h[x])) return h[x];
	bool b[35];
	for (int i=0;i<=n;i++) b[i]=0;
	for (int i=1;i<=n;i++)
	{
		int sub=x;
		if ((x&(1<<(i-1)))!=0)
		{
			for (int j=i;j<=n;j+=i) sub&=g-(1<<(j-1));
			b[dfs(sub)]=1;
		}
	}
	int c=0;
	for (int i=0;i<=n;i++)
	{
		if (!b[i])
		{
			c=i;
			break;
		}
	}
	h[x]=c;
	return c;
}

int main()
{
	for (int i=1;i<=30;i++)
	{	
		n=i;
		g=(1<<n)-1;		
		for (int j=1;j<=i;j++) a[j]=1;
	    printf("%d\n",dfs(g));
	}
}
```

因为大于$\sqrt{n}$的数的$k$值都是$1$，所以我们可以暴力前$\sqrt{n}$个数的$sg$异或和。但是要排除掉那些可以写成其他数幂次（除$c^1$）的数，然后统计一下$[\sqrt{n}+1,n]$有多少个这样的数，那么这个范围内剩下的数的$sg$值都等于$sg[1]$。因为是异或，只要判断剩下的数的个数的奇偶性即可。

代码：
```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#define LL long long

const LL sg[31]={0,1,2,1,4,3,2,1,5,6,2,1,8,7,5,9,8,7,3,4,7,4,2,1,10,9,3,6,11,12,14};
const int maxn=1e5+7;

using namespace std;

LL n;
LL ans,v[maxn],t;

int main()
{
	scanf("%lld",&n);
	LL p=trunc(sqrt(n));
	ans=sg[1];	
	for (LL i=2;i<=p;i++)
	{
		if (v[i]) continue;
		LL c=i,k=1;
		while (c*i<=n)
		{
			c*=i;
			if (c<=p) v[c]=1;
			    else t++;
			k++;
		}		
		ans^=sg[k];
	}	
	if ((n-p-t)%2==1) ans^=sg[1];
    if (ans==0) printf("Petya");
           else printf("Vasya");
}
```

---

## 作者：xiezheyuan (赞：0)

## 简要题意

Alice 和 Bob 在玩游戏，有一个集合 $S$，初始时 $S=\{1,2,\cdots,n\}$，Alice 先手，轮流进行下面的操作：

* 选择一个 $x\in S$，对于所有的正整数 $k$，若 $x^k\in S$，则从 $S$ 中删除 $x^k$。

无法操作的判负。假设每个人都绝顶聪明，输出谁最终会取胜。

$1\leq n\leq 10^9$。

## 思路

首先假设我们将 $S$ 划分为若干个等价类，每个等价类形如 $\{x,x^2,x^3,\cdots,x^{\lfloor\log_{x}n\rfloor}\}$，其中代表元 $x$ 满足：

* 取 $x$ 的质因子分解 $\prod_{i=1}^{\Omega(x)} {p_i}^{e_i}$，满足 $\gcd(e_1,e_2,\cdots,e_{\Omega(x)})=1$。

不难发现这些等价类恰好构成 $S$ 的一个划分（所有元素在且仅在一个等价类中）。并且在博弈的过程中等价类之间不会产生影响。

参考 SG 定理，我们可以将这个游戏划分为若干个子游戏，每个子游戏都在等价类中进行。

这些子游戏都可以表示成有一个集合 $S$，初始时为 $S=\{1,2,\cdots,m\}$，每次可以选定一个 $x\in S$，然后对于所有的正整数 $k$，若 $xk\in S$，则从 $S$ 中删除 $xk$。无法操作的判负。

这个东西似乎 SG 函数没有那么显然。不过考虑到每个等价类大小最多只有 $O(\log n)$，可以打一个表（暴力~~或者从题解贺一个~~）。

然后考虑如何求答案，下面给出一个引理：大小不小于 $2$ 的等价类的所有元素总数最多只有 $O(\sqrt{n}\log n)$ 个。

证明也很简单，大小不小于 $2$ 的等价类的代表元上界为 $\sqrt{n}$，而每一个等价类的大小上界为 $\log_2 n$。

于是我们可以暴力枚举每一个大小不小于 $2$ 的等价类的代表元去求这些等价类的大小，然后将这些等价类的 SG 函数异或起来。

最后考虑大小为 $1$ 的等价类。这些等价类的 SG 函数都是 $1$，只有奇数个 $1$ 才会产生 $1$ 的影响。

时间复杂度 $O({\sqrt{n}\log n})$。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

int sg[31]={0,1,2,1,4,3,2,1,5,6,2,1,8,7,5,9,8,7,3,4,7,4,2,1,10,9,3,6,11,12,14};
int n, val;
map<int,bool> vis;

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin >> n;
    int all = 0;
    for(int i=2;i*i<=n;i++){
        if(vis[i]) continue;
        int cnt = 0;
        for(int j=i;j<=n;j*=i){
            all++; cnt++;
            vis[j] = 1;
        }
        val ^= sg[cnt];
    } 
    val ^= ((n - all) & 1);
    cout << (val ? "Vasya" : "Petya") << '\n';
    return 0;
}

// Written by xiezheyuan
```

---

## 作者：wangyibo201026 (赞：0)

## solution

首先注意到这是一道博弈论，所以我们思考用 SG 函数解决这个题。

其实我们发现如果存在 $z = y^p$，$y = x^q$，那么 $z = x^{p 
\times q}$，就意味着相当于我选 $y$ 和选取 $x$ 的一个子问题没有任何区别。

所以相当于我们只需要处理 $x$ 满足 $x$ 不是任何数的正整数幂就好了，这样每个 $x$ 都是一个单独的子问题，我们只需要将其 SG 函数值异或起来便好。

那么我们现在思考，对于一个单独的游戏 $x$，SG 函数值应该如何求出，相当于我有一堆石子，每次可以取出最上面的一整段，我们发现具有相同石子数的 SG 函数值明显是一样的，于是我们可以利用打表程序求出石子个数在 $1 
\sim 30$ 个的 SG 函数（指数不会超过 $30$ 的），然后直接异或起来便好。

然后怎么处理 $x$，很像埃氏筛一样筛一下就出来了，然后不难发现如果 $x > 
\sqrt n$ 那么指数最多就是 $1$，也就是说我们只要枚举到 $\sqrt n$ 就好了。

## code

code：

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define fir first
#define sec second
#define mkp make_pair 
#define pb push_back
#define lep( i, l, r ) for ( int i = ( l ); i <= ( r ); ++ i )
#define rep( i, r, l ) for ( int i = ( r ); i >= ( l ); -- i )

typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
typedef pair < int, int > pii;

char _c; bool _f; template < class type > inline void read ( type &x ) {
	_f = 0, x = 0;
	while ( _c = getchar (), !isdigit ( _c ) ) if ( _c == '-' ) _f = 1;
	while ( isdigit ( _c ) ) x = x * 10 + _c - '0', _c = getchar (); if ( _f ) { x = -x; }
}

template < class type > inline void chkmin ( type &x, type y ) { x = ( x <= y ? x : y ); }
template < class type > inline void chkmax ( type &x, type y ) { x = ( x >= y ? x : y ); }

const int sg[] = { 0, 1, 2, 1, 4, 3, 2, 1, 5, 6, 2, 1, 8, 7, 5, 9, 8, 7, 3, 4, 7, 4, 2, 1, 10, 9, 3, 6, 11, 12, 14 };

int n, ans;
map < int, int > mp;
vector < int > g;

void Solve () {
	cin >> n;
	int b = sqrt ( n ), res = n - b;
	ans ^= sg[1];
	for ( int i = 2; i <= b; i ++ ) {
		if ( !mp[i] ) {
			int cnt = 0;
			for ( int j = i; j <= n; j *= i ) {
				cnt ++;
				if ( !mp[j] ) {
					mp[j] = 1;
					if ( j > b ) {
						res --;
					}
				}
			}
			ans ^= sg[cnt];
		}
	}
	if ( res & 1 ) {
		ans ^= sg[1];
	}
	if ( !ans ) {
		cout << "Petya";
	}
	else {
		cout << "Vasya";
	}
}

signed main () {
#ifdef judge
	freopen ( "Code.in", "r", stdin );
	freopen ( "Code.out", "w", stdout );
	freopen ( "Code.err", "w", stderr );
#endif
	Solve ();
	return 0;
}
```

---

## 作者：lfxxx (赞：0)

考虑找到最小的不能被表示为其他数幂次的数 $x$，那么原问题被若干个 $x$ 分解为若干个不交的子游戏。

子游戏通过 $x^d$ 可以拆解为有 $1 \sim d$ 共 $d$ 个数，每次可以取走一个数以及其所有倍数，不能取的人输，注意到 $d \leq 30$，于是可以在本地先把关于 $d$ 的 SG 函数打表打出来，然后求解答案因为对于 $x > \sqrt n$ 的情况 $d$ 均为 $1$，所以对于 $x \leq \sqrt n$ 的情况特殊计算一下即可，时间复杂度 $O(\sqrt n \log n)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
//#define lowbit(x) (x&(-x))
//#define bp push_back
//#define sz size
//#define cl clear
int dp[31]={0,1,2,1,4,3,2,1,5,6,2,1,8,7,5,9,8,7,3,4,7,4,2,1,10,9,3,6,11,12,14};
/*
1 1
2 2
3 1
4 4
5 3
6 2
7 1
8 5
9 6
10 2
11 1
12 8
13 7
14 5
15 9
16 8
17 7
18 3
19 4
20 7
21 4
22 2
23 1
24 10
25 9
26 3
27 6
28 11
29 12
30 14*/
int n;
map<int,int> vis;
const int warma = 4e4;
int Nim,cnt;
signed main(){
	cin>>n;
	cnt=n;
	for(int i=2;i<=warma;i++){
		if(vis[i]==1) continue;
		int u=i;
		int t=0;
		while(u<=n){
			vis[u]=1;
			cnt--;
			t++;
			u*=i;
		}
		Nim^=dp[t];
	}
	Nim^=(cnt%2==0?0:dp[1]);
	cout<<(Nim!=0?"Vasya\n":"Petya\n");
}
```

---

## 作者：Inui_Sana (赞：0)

Daily problem.

先把有正整数幂关系的数都放在一个组中，容易发现，此时不同组之间相互独立，于是可以分每组算出 SG 值，最后用 SG 定理算整个游戏的 SG 值。

考虑每个子游戏 SG 值怎么算，发现等价于这样一个游戏：

> 给你 $[1,m]$ 内的所有整数，两个玩家依次选则一个还未删掉的 $x$，删掉 $x,2x,3x,\cdots$（如果还没被删），无法操作的人输，问谁获胜。

注意到 $m\le 29$。直接考虑爆搜打表：

```cpp
int n,m,sg[30];
map<int,int> dp;
int dfs(int u){
	if(!u){
		return 0;
	}
	if(dp.count(u)){
		return dp[u];
	}
	set<int> st;
	rep(i,0,28){
		if(!(u>>i&1)){
			continue;
		}
		int v=u;
		for(int j=i;j<=28;j+=i+1){
			v&=((1<<29)-1)^(1<<j);
		}
		st.emplace(dfs(v));
	}
	int ret=0;
	rep(i,0,30){
		if(!st.count(i)){
			ret=i;
			break;
		}
	}
	return dp[u]=ret;
}
void Yorushika(){
	read(n,m);
}
signed main(){
	rep(i,1,29){
		sg[i]=dfs((1<<i)-1);
		printf("%d,",sg[i]);
	}
	int t=0;
	//read(t);
	while(t--){
		Yorushika();
	}
}
```

打出来是 $1,2,1,4,3,2,1,5,6,2,1,8,7,5,9,8,7,3,4,7,4,2,1,10,9,3,6,11,12$。

但是发现 $n$ 仍然比较大，考虑只枚举到 $\sqrt n$，处理 $m\ge 2$ 的情况，然后记录有多少 $m=1$ 的，再算上这种情况的 SG 值即可。

code：

```cpp
int n,m;
const int sg[30]={0,1,2,1,4,3,2,1,5,6,2,1,8,7,5,9,8,7,3,4,7,4,2,1,10,9,3,6,11,12};
map<int,bool> vis;
void Yorushika(){
	read(n),m=n;
	int ans=0;
	for(int i=2;i*i<=n;i++){
		if(vis[i]){
			continue;
		}
		int cnt=0;
		for(ll j=i;j<=n;j*=i){
			if(!vis[j]){
				vis[j]=1;
				m--,cnt++;
			}
		}
		ans^=sg[cnt];
	}
	ans^=m&1;
	puts(ans?"Vasya":"Petya");
}
signed main(){
	int t=1;
	//read(t);
	while(t--){
		Yorushika();
	}
}
```

---

