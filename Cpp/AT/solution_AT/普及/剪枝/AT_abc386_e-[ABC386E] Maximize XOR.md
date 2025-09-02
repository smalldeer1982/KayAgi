# [ABC386E] Maximize XOR

## 题目描述

给定一个长度为 $N$ 的非负整数序列 $A$ 和一个整数 $K$。保证二项式系数 $\dbinom{N}{K} \leq 10^6$。

从序列 $A$ 中选择 $K$ 个不同的元素，求出这些元素的异或和的最大值。

简单来说，就是求 $\underset{1 \leq i_1 < i_2 < \ldots < i_K \leq N}{\max} A_{i_1} \oplus A_{i_2} \oplus \ldots \oplus A_{i_K}$。

在这里，异或运算（XOR）是这样定义的：对于两个非负整数 $A$ 和 $B$，其结果 $A \oplus B$ 是一个二进制数，对于每个 $2^k \ (k \geq 0)$ 位，如果 $A$ 和 $B$ 在这一位中恰好只有一个是 $1$，则结果在这一位是 $1$，否则为 $0$。

举个例子：$3 \oplus 5 = 6$，在二进制下：$011 \oplus 101 = 110$。通常来说，$k$ 个整数 $p_1, \dots, p_k$ 的异或值可以表示为 $(\cdots ((p_1 \oplus p_2) \oplus p_3) \oplus \cdots \oplus p_k)$，并且顺序不会影响结果。

## 说明/提示

- $1 \leq K \leq N \leq 2 \times 10^5$
- $0 \leq A_i < 2^{60}$
- $\dbinom{N}{K} \leq 10^6$
- 所有输入均为整数

### 示例解释 1

从 $(3, 2, 6, 4)$ 中选出任意两个不同的数，有以下六种组合方式：
- 选择 $(3, 2)$：异或值为 $3 \oplus 2 = 1$。
- 选择 $(3, 6)$：异或值为 $3 \oplus 6 = 5$。
- 选择 $(3, 4)$：异或值为 $3 \oplus 4 = 7$。
- 选择 $(2, 6)$：异或值为 $2 \oplus 6 = 4$。
- 选择 $(2, 4)$：异或值为 $2 \oplus 4 = 6$。
- 选择 $(6, 4)$：异或值为 $6 \oplus 4 = 2$。

因此，最大异或值为 $7$。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
4 2
3 2 6 4```

### 输出

```
7```

## 样例 #2

### 输入

```
10 4
1516 1184 1361 2014 1013 1361 1624 1127 1117 1759```

### 输出

```
2024```

# 题解

## 作者：yy0707 (赞：8)

### 题目大意:

给你一个长为 $n$ 的序列 $a$，让你求选 $k$ 个数时的最大异或和。

首先我们可以暴力 DFS，但很明显它会超时。  
我们可以想到，选 $k$ 个数就相当于不选 $n-k$ 个数。  
所以我们可以判断当 $n-k<k$ 时，就改为不选 $n-k$ 个数。  
然后它就过了，时间复杂度 $O(C_n^k)$。

### Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,ans,sum,a[200001],k;
void dfs(int p,int st,int xsum){
	if(st==k)return ans=max(ans,xsum),void();
	for(int i=p+1;i<=n;i++)dfs(i,st+1,xsum^a[i]);
}signed main(){
	cin>>n>>k;k=n-k;
	for(int i=1;i<=n;i++)cin>>a[i],sum^=a[i];
	if(k>n-k)k=n-k,sum=0;
	dfs(0,0,sum);cout<<ans;
}
```

---

## 作者：Walrus (赞：3)

## 题意

给定一个长度为 $n$ 的序列，选出 $k$ 个数，使得其异或值最大化。

---

考虑突破口在哪里，发现题目中有个系数 $\dbinom{n}{k}$ 不超过 $10^6$，想告诉我们什么？考虑组合数的计算法即：
$$\dbinom{n}{k}=\dfrac{n!}{k!\times(n-k)!}$$

变形一下可得：
$$\dbinom{n}{k}=\dfrac{\prod_{i=n-k+1}^n i}{k!}$$

再考虑爆搜的时间复杂度是 $O(n^k)$，即暴力枚举选哪 $k$ 个数。

发现有：
- 当 $k=2$ 时，$n$ 一定小于 $450$，此时 $n^k=202500$。
- 当 $k=3$ 时，$n$ 一定小于 $86$，此时 $n^k=636056$。
- 当 $k=4$ 时，$n$ 一定小于 $41$，此时 $n^k=2825761$。
- 当 $k=5$ 时，$n$ 一定小于 $29$，此时 $n^k=20511149$。
- 当 $k=6$ 时，$n$ 一定小于 $23$，此时 $n^k=148035889$。

后续不作列举，**但实际上在 dfs 的时候一定是跑不满 $n^k$ 的，因为有些情况已经选到 $k$ 个了会提前终止而不会搜满当前 $n$ 层。加上 AT 的超级机子是可过的。**

## 优化

发现在上述列举中 $n^k$ 可以达到 $10^8$ 的级别且 $n^k$ 在增加，如果 $k=7$ 或更大会不会到 $10^{10}$ 的级别甚至更高？当然是有可能的，但是这些情况的 $n$ 肯定就大不到哪去了。我们考虑优化：

- 若 $k\leq \dfrac{n}{2}$，如上述列举最多到 $10^8$，直接搜即可。
- 反之，我们考虑全部选上再反悔，则将原来的 $k$ 变为 $n-k$，由于异或操作有个性质形如 $a \oplus b \oplus b=a$，在 dfs 时，再选一些数**相当于丢掉不选**，故此做法是可行的。

[code](https://atcoder.jp/contests/abc386/submissions/61220515)

跑的还是蛮快的，最大点只有 23 ms。

---

## 作者：Yuexingfei_qwq (赞：2)

深搜，但是赛时没看。
## 思路  
很明显是一道有关组合数的题。  
先处理出后缀异或和数组 $s$ ，然后开始深搜。  
建立**全局变量** $ans$，将 $ans$ 赋值为**无穷小**（因为要求最大值）用于计算答案。

深搜部分有以下参数：  
`inline void dfs(int x, int y, int t)`  
其中 $x$ 表示现在搜到的位置， $y$ 表示现在还没有用到的数的数量， $t$ 表示目前的异或和。  
 
首先，当 $y = 0$ 时，表示所有数都用完了，直接更新 $ans$ 为 $ans$ 和 $t$ 的较大值，然后结束递归。  
其次，当 $x + y - 1 = n$ 时，表示剩下的 $y$ 个数均在目前的位置 $x$ 的后面，将 $ans$ 更新为 $ans$ 和 $t \oplus s_{x}$ 的较大值，然后结束递归。  
否则分别递归 $a_{x}$ 这个数选或不选的情况。  

最后输出答案 $ans$ 即可。  
## AC CODE

```cpp
#include <bits/stdc++.h>
#define el "\n"
#define sp " "
#define fi first
#define se second
#define inf 1e18
#define r0 return 0
#define int long long
#define F(i, a, b, c) for (int i = a; i <= b; i += c)
#define debug printf ("bug is in here\n")
#define TheEnd continue
#define base(s) s = sp + s
#define lcm(a, b) a * b / __gcd(a, b)
#define setp(x) fixed << setprecision(x)

using namespace std;

typedef long long ll;
typedef string str;
using ull = unsigned ll;

int n, k;
int a[210000], s[210000];
int ans = -inf;

inline void dfs(int x, int y, int t) {
	if (y == 0) {
		ans = std::max(ans, t);
		return;
	}
	if (x + y - 1 == n) {
		ans = std::max(ans, t ^ s[x]);
		return;
	}
	dfs(x + 1, y - 1, t ^ a[x]);
	dfs(x + 1, y, t);
}

signed main(void) {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);
	memset(s, 0, sizeof(s));//注意要初始化
	cin >> n >> k;
	F(i, 1, n, 1) {
		cin >> a[i];
	}
	for (int i = n; i; i--) {
		s[i] = s[i + 1] ^ a[i];
	}
	dfs(1, k, 0);
	cout << ans << el;
	r0;
}
```

[AC记录](https://atcoder.jp/contests/abc386/submissions/61282542)

---
完结~~不~~散花。

---

## 作者：tanghg (赞：1)

由于那个组合数的性质，发现应该是直接深搜就可以的。可是发现超时了。发现如果 $k$ 很大那么还是不好处理。但是发现搜 $k$ 个数和搜 $n-k$ 个数是一样的，只不过第二种得到的值要用 $n$ 个数的总异或值再异或一次。然后又因为 $C_n^k=C_n^{n-k}$ 所以时间复杂度就是 $O(C_n^k)$。

```cpp
// Problem: E -  Maximize XOR
// Contest: AtCoder - AtCoder Beginner Contest 386
// URL: https://atcoder.jp/contests/abc386/tasks/abc386_e
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MAXN=2e5+5;
ll n,k,a[MAXN];
ll ans,ma;

ll Val=0;
void dfs(ll x,ll num,ll val){
    if(num>k||x>n+1){
        return;
    }
    if(num==n-k){
        ans=max(ans,Val^val);
        return;
    }
    if(num==k){
        ans=max(ans,val);
        return;
    }
    dfs(x+1,num+1,val^a[x]);
    dfs(x+1,num,val);
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n>>k;
	for(int i=1;i<=n;++i){
	    cin>>a[i];
	    ma=max(ma,a[i]);
	    Val^=a[i];
	}
	dfs(1,0,0);
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：sjh0626 (赞：1)

## 题意概括
给你一个长度为 $N$ 的非负整数序列 $A$ 和一个整数 $K$。保证二项式系数 $\dbinom{N}{K}$ 最多为 $10^6$。

从 $A$ 中选择 $K$ 个不同的元素，求所选 $K$ 个元素的异或最大可能值。

即求出 $\underset{1\leq i_1\lt i_2\lt \ldots\lt i_K\leq N}{\max} A_{i_1}\oplus A_{i_2}\oplus \ldots \oplus A_{i_K}$。


一般来说，$K$ 个整数 $p_1, \dots, p_k$ 的异或值定义为 $(\cdots((p_1 \oplus p_2) \oplus p_3) \oplus \cdots \oplus p_k)$。可以证明它与  $p_1, \dots, p_k$ 的阶数无关。
## 思路分析
这题我们采用暴力搜索与剪枝。

我们首先要进行暴力搜索，即选择和不选择，即 $O(2^n)$。

但是 $N \le 2 \times 10^5$，所以肯定超时。

我们要想到一个事情，假如你搜索到 $i$ 这个下标的时候，选择了 $m$ 个数，包括自己刚好还剩 $K-m$ 个数，那就不用搜索了，后面的肯定必须选，我们可以用后缀异或和优化，这就可以把时间复杂度优化到 $O(\dbinom{N}{K})$，因为我们是在 $N$ 个数里面选 $K$ 个数。

因为 $\dbinom{N}{K}$ 最多为 $10^6$，所以我们可以通过此题。
## 代码解析
```cpp
#include<bits/stdc++.h>
#define sjh0626s return
#define code 0
#define ll long long
using namespace std;
class FastIO{
	public:
	inline ll read(){
		ll x=0,f=1;char ch=getchar();
		while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
		while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
		return x*f;
	}
	FastIO &operator>>(ll &x){
		x=read();
		return *this;
	}
};
FastIO qin;
ll n,k,a[300010],s[300010],ans;
void dfs(ll now,ll rest,ll sum){
	if(rest==0){ //搜完了 
		ans=max(ans,sum);
		return ;
	}
	if(now+rest-1==n){ //包括自己剩下 k 个数 
		ans=max(ans,sum^s[now]); //直接比较 
		return;
	}
	dfs(now+1,rest,sum); //选择 
	dfs(now+1,rest-1,sum^a[now]); //不选择 
}
int main(){
	qin>>n>>k;
	for(int i=1;i<=n;i++){
		qin>>a[i];
	}
	for(int i=n;i>=1;i--)s[i]=s[i+1]^a[i];
	dfs(1,k,0);
	cout<<ans; 
	sjh0626s code;
}
```

---

## 作者：dg114514 (赞：1)

为了方便，将剩余可选数量记作 $k$，当前准备选的数的下标记为 $id$，$A$ 长度记为 $n$。\
看到 $ \dbinom{N}{K}\leq\ 10^6 $，一眼搜索。\
打好普通搜索会 TLE 二~四个点，需要加剪枝。\
剪枝比较好想。~~（蒟蒻赛后七分钟才想出来）~~ 就是如果后面的数必须全选，（即 $k+id=n+1$）直接将之前选的数的异或和异或上 $A_{id}\ \oplus\ A_{id+1} \oplus \cdots \oplus A_n$，然后将此时的异或和 `max` 一下就可以了。其中 $A_{id}\ \oplus\ A_{id+1} \oplus \cdots \oplus A_n$ 可以用后缀和计算。一交，神奇的 AC 了。\
代码很简单，不放了。

---

## 作者：OIer_Tan (赞：1)

这下这辈子有了，暴搜题不过。

## 题意

给你一个长度为 $N$ 的非负整数序列 $A$ 和一个整数 $K$。保证 $\dbinom{N}{K}$ 最多为 $10^6$。

从 $A$ 中选择 $K$ 个不同的元素，求所选元素 $K$ 的 XOR 的最大可能值。

即求出 $\underset{1\leq i_1\lt i_2\lt \ldots\lt i_K\leq N}{\max} A_{i_1}\oplus A_{i_2}\oplus \ldots \oplus A_{i_K}$。

## 思路

赛时很魔怔，想到暴搜了。

然而最坏复杂度是 $O(N^K)$ 的，显然过不了。

容易想到分讨，将 $N\le25$ 的部分用状压跑出来。

然而还是会有很多情况，比如 $N$ 很大然而 $K$ 接近 $N$ 的情况。赛后想到可以将这部分变为先算出整体然后再搜不取的那部分。

我们考虑优化状压部分：

- 由于是选 $K$ 个，所以当最高位不足 $K$ 位时直接跳过；
- 找到一个可以选的时候，直接减去 $\frac{\operatorname{lowbit}}{2}$，这样相当于直接把最后一位改过去。

发现搜索部分还可以优化，我们考虑再记一个下标，表示剩下的值只能从这后面取，再剪枝一下。

这样就可以卡过去了。

当然状压的阈值要卡一卡，经测试对 $N\le23$ 的部分使用状压可以跑的很快。

## 代码

仅供参考。

```cpp
#include <bits/stdc++.h>

#ifndef CRT
#define endl '\n'
#endif

using namespace std ;

typedef long long ll ;
typedef unsigned long long ull ;
typedef long double ld ;

const ll N = 2e5 + 5 ;

ll n , k , a [N] ;

ll ans = 0 , all = 0 ;

bool flag [N] ;

ll lst [N] ;

void dfs1 ( ll now , ll cnt , ll sum )
{
	if ( cnt == k )
	{
		ans = max ( ans , sum ) ;
		return ;
	}
	if ( now == n )
	{
		return ;
	}
	if ( k - cnt > n - now )
	{
		return ;
	}
	if ( k - cnt == n - now )
	{
		ans = max ( ans , sum ^ lst [now + 1] ) ;
		return ;
	}
	for ( ll i = now + 1 ; i <= n ; i ++ )
	{
		if ( ! flag [i] )
		{
			flag [i] = 1 ;
			dfs1 ( i , cnt + 1 , sum ^ a [i] ) ;
			flag [i] = 0 ;
		}
	}
	return ;
}

void dfs2 ( ll now , ll cnt , ll sum )
{
	if ( cnt == k )
	{
		ans = max ( ans , sum ^ all ) ;
		return ;
	}
	if ( now == n )
	{
		return ;
	}
	if ( k - cnt > n - now )
	{
		return ;
	}
	if ( k - cnt == n - now )
	{
		ans = max ( ans , sum ^ lst [now + 1] ^ all ) ;
		return ;
	}
	for ( ll i = now + 1 ; i <= n ; i ++ )
	{
		if ( ! flag [i] )
		{
			flag [i] = 1 ;
			dfs2 ( i , cnt + 1 , sum ^ a [i] ) ;
			flag [i] = 0 ;
		}
	}
	return ;
}

ll lowbit ( ll x )
{
	return x & -x ;
}

int main ()
{
#if not defined ( CRCC ) and not defined ( ONLINE_JUDGE )
	freopen ( ".in" , "r" , stdin ) ;
	freopen ( ".out" , "w" , stdout ) ;
#endif
	ios::sync_with_stdio ( 0 ) ;
	cin.tie ( 0 ) ;
	cout.tie ( 0 ) ;
	cin >> n >> k ;
	for ( ll i = 1 ; i <= n ; i ++ )
	{
		cin >> a [i] ;
	}
	// k = min ( k , n - k ) ;
	if ( n <= 20 )
	{
		ll ans = 0 ;
		for ( ll i = ( 1ll << n + 1 ) - 1 ; i ; i -- )
		{
			if ( __builtin_popcount ( i ) != k )
			{
				continue ;
			}
			if ( 64 - __builtin_clz ( i ) < k )
			{
				break ;
			}
			// ll tmp = 0 ;
			// for ( ll j = 1 ; j <= n ; j ++ )
			// {
			// 	if ( i & ( 1 << ( j - 1 ) ) )
			// 	{
			// 		tmp ^= a [j] ;
			// 	}
			// }
			// ans = max ( ans , tmp ) ;
			while ( ( i ? __builtin_ctz ( i ) : 0 ) )
			{
				ll tmp = 0 ;
				for ( ll j = 1 ; j <= n ; j ++ )
				{
					if ( i & ( 1 << ( j ) ) )
					{
						tmp ^= a [j] ;
					}
				}
				ans = max ( ans , tmp ) ;
				// cout << ( bitset <64> ( i ) ) << " " << tmp << endl ;
				i -= lowbit ( i ) / 2 ;
			}
			// cout << bitset <20> ( i ) << endl ;
			
		}
		cout << ans << endl ;
	}
	else
	{
		for ( ll i = n ; i ; i -- )
		{
			lst [i] = lst [i + 1] ^ a [i] ;
		}
		if ( k <= n - k )
		{
			dfs1 ( 0 , 0 , 0 ) ;
		}
		else
		{
			all = lst [1] ;
			k = n - k ;
			dfs2 ( 0 , 0 , 0 ) ;
		}
		cout << ans << endl ;
	}
	return 0 ;
}

```

---

## 作者：_anll_ (赞：1)

告诉我为什么要在 E 放可爱剪枝。
## 思路
观察数据，你发现 $\dbinom {N}{K}\le 10^6$ ，方案数这么少，感觉暗示搜索。

你打了一发交上去 T 了，但只有 $10$ 个点，于是考虑剪枝。发现有一种无用状态是哪怕最后都选完也只选了 $x$ 个点，但 $x<k$。遇到这种情况可以直接结束。

你这样写了一发上去又 T 了，发现当 $x=k$ 时，因为 $n$ 最大可以到 $2\times 10^5$ 的，这样很不妙，考虑能否在这种情况下 $O(1)$ 求出答案直接返回。显然，只需要在开始深搜前预处理一下后缀异或和即可。

你又交上去，发现完美通过，但只剩十分钟，而 F 更是无法战胜。于是你放弃了挣扎并打开了 qq，开始水群。

## 代码
```cpp
#include<iostream>
#define int long long
using namespace std;
const int N=2e5+5;
int n,k,num[N],hzh[N],ans;
void dfs(int x,int c,int a){
	if(!c){ans=max(ans,a);return;}
	if(x>n||c+x-1>n) return;
	if(c+x-1==n)
		return void(ans=max(ans,a^hzh[x]));
	dfs(x+1,c-1,a^num[x]);
	dfs(x+1,c,a);
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>num[i];
	for(int i=n;i>=1;i--) hzh[i]=(hzh[i+1]^num[i]);
	dfs(1,k,0);cout<<ans;
	return 0;
}
```

---

## 作者：TainityAnle (赞：0)

### 题意

给定一个长度为 $n$ 的序列，选出其中的 $k$ 个数，使得这些数异或和最大。

### 思路

容易写出以下暴力：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,a[200005],c[200005],ans=0;
void dfs(int x,int k,int res) {
	if(x==m+1) {
        ans=max(ans,res);
        return ;
    }
	for(int i=k+1; i<=n; i++) dfs(x+1,i,res^c[i]);
}
signed main() {
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>c[i];
	dfs(1,0,0);
	cout<<ans;
	return 0;
}
```

这个暴力就是枚举所有组合，对所有答案取最大值。但不幸的是，这个做法的时间复杂度并不是我们所希望的 $O\left(\dbinom{N}{k}\right)$，而是会将 $\dbinom{N}{1}$ 到 $\dbinom{N}{k}$ 的所有情况都枚举一遍，所以 $k$ 比较大时会 T 飞。

然后我想到正难则反，于是考虑先记一下整个序列的异或和，再枚举删哪个，这样的时间复杂度是 $\displaystyle\sum_{i=0}^{n-k}\dbinom{N}{i}$。不过这样 $k$ 小的时候反而会变慢。

于是，我们很自然地发现当 $k$ 小时用前面的暴力，当 $k$ 大时用第二种反着来的方式。这样会变快。当满足 $\dbinom{N}{k}\le10^6$ 这个条件时，要么 $k$ 很小，要么 $k$ 很大，不会出现在中间的情况。所以这样写可以过。

### AC Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,a[200005],c[200005],ans=0,cnt=0,xorsum=0;
void dfs(int x,int k,int res) {
	cnt++;
	if(x==m+1) {
		ans=max(ans,res);
		return ;
	}
	for(int i=k+1; i<=n; i++) dfs(x+1,i,res^c[i]);
}
void dfs1(int x,int k,int res) {
	cnt++;
	if(x==n-m+1) {
		ans=max(ans,res);
		return ;
	}
	for(int i=k+1; i<=n; i++) dfs1(x+1,i,res^c[i]);
}
signed main() {
	cin>>n>>m;
	for(int i=1; i<=n; i++) cin>>c[i],xorsum^=c[i];
	if(m<=n-m) dfs(1,0,0);
	else dfs1(1,0,xorsum);
	cout<<ans;
	return 0;
}
```

---

## 作者：wflhx2011 (赞：0)

有点诈骗的一道题。

首先，看见这个题，第一反应是一个 dfs，直接求出所有的可能解，即下面的代码：


```cpp
void dfs(long long cnt,long long c,long long u)
{
    if(cnt==0) 
    {
    	res=max(res,c); 
		return ;
	}
    for(long long i=u+1;i<=n;i++)
    {
        if(vis[i]==0)
        {
            vis[i]=1;
            dfs(cnt-1,c^a[i],i);
            vis[i]=0;
        }
    }
}
```
其中 $cnt$ 表示还能选多少个数，如果选了 $k$ 个记录结果。$c$ 就表示当前的异或和。

之后分别枚举每个数选的情况，为了避免重复可以用 $vis$ 数组，或者记录上一次选的数的位置 $u$，之后从下一个位置开始枚举。

但这样会超时，分析发现这样大概会进行 $\sum_{i=0}^{k}C_n^i$ 次递归，因为你不能保证每次一定选 $k$ 个数，选 $0$ 个到 $k-1$ 个都有可能。

题目中虽然保证 $C_n^k \le 10^6$，当 $k>\frac{n}{2}$ 时，上面的式子 $C_n^i$ 会在 $i=\frac{n}{2}$ 时取到最大值，且这个值有可能远大于 $C_n^k$。

那有没有办法优化呢？ 因为 $C_n^k=C_n^{n-k}$，即从 $n$ 个中选 $k$ 个等价于从 $n$ 个中不选 $n-k$。

所以，如果 $k>\frac{n}{2}$，就让 $k$ 变成 $n-k$，也就是变为选择不选的 $n-k$ 个数，最后的结果就是所有数的异或和，异或上不选的数的异或和。（原理是 $x\oplus x=0$ 并且 $x \oplus 0=x$）

递归次数就降低为 $\sum_{i=0}^{n-k}C_n^i$，可以算出这个最大也就是 $10^6$ 级别的。

这样，既能求出正确结果，又把时间复杂度降低，完美！

代码只需按照暴力的代码改一改，就不放了。

---

## 作者：201012280925LSY (赞：0)

## 题意
给定一个长度为 $N$ 的数组，要求你从里面选出 $K$ 个数，使它们的异或和最大，输出这个异或和。
## 思路
注意到约束中有一个条件：
$$
\dbinom{N}{K} \le 10^6
$$
这个条件的意思是指保证从 $N$ 个数里面选 $K$ 个（方案不重复）的方案数小于等于 $10^6$。

所以思路就十分显然了。直接暴力搜索即可，同时要保证自己的搜索避免大量重复，即可通过此题。

具体见代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,k,a[200010],answer,b[200010],m; 
bool flag[200010];
long long sum[200010];
void DFS(long long step,long long x,long long ans)//从 N 个数里面选 K 个。
{
	if(step==x-1)//说明剩下的都得选。
	{
		answer=max(answer,ans^sum[step]);
		return;
	}
	if(step==0)//K 个数都选完了。 
	{
		answer=max(answer,ans);
		return;
	}
	for(int i=x-1;i>=step;i--)DFS(step-1,i,ans^a[i]);//从后往前找。
	return;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>k;
	for(int i=1;i<=n;i++)cin>>a[i],sum[i]=sum[i-1]^a[i];//处理出异或前缀和。
	DFS(k,n+1,0);
	cout<<answer;
	return 0;
}

```

---

## 作者：wht_1218 (赞：0)

搜索剪枝。

怎么搜索我就不说了。

剪枝 $1$：当前已经选择了 $K$ 个数：直接跳到 `dfs(N+1...)`。

剪枝 $2$：设当前准备选第 $x$ 个数，$1\sim x-1$ 已经选过 $cnt$ 个数，则 $1\sim x-1$ 有 $x-cnt$ 个数没选。若 $x\sim N$ 选完后刚好选了 $K$ 个，即 $N-(x-cnt-1)=K$ 时，直接跳到 `dfs(N+1...)`，这里要使当前答案再异或 $A_{x}\oplus A_{x+1}\oplus ...A_N$，其中 $\oplus$ 为异或。异或和可以预处理。

理论来说这样就可以过了。


```cpp
#ifndef _CPP_FILE
#define _CPP_FILE
#include<bits/stdc++.h>
#define int long long 
#pragma GCC optimize("Ofast")
using namespace std;
const int N=1e6+7;
#define il inline
#define re register
#define rei register int
#define max(x,y) (x>y?x:y)
#define min(x,y) (x<y?x:y)
//#define abs(x) (x>0?x:-x)
inline int abs(auto x){
	return x>0?x:-x;
}
#define imx INT_MAX
#define imn INT_MIN
#define lmx LLONG_MAX
#define lmn LLONG_MIN
#define nmx (N)
#define nmn (-N)
#define umap unordered_map
#define pii pair<int,int>
#define mset multiset

/**/
int n,m,S;
long long a[N],p1[N],p2[N],ans=0;
inline void dfs(register int x,register long long ansn,register int cnt){
	if(cnt>m||cnt+n-x+1<m)return;
	if(x>n){
		cnt==m?ans=max(ans,ansn):0;
		return;
	}
	if(n-x+cnt+1==m)return dfs(n+1,ansn^p2[x],m);
	cnt==m?dfs(n+1,ansn,cnt):(cnt>0?dfs(x+1,ansn^a[x],cnt+1):dfs(x+1,a[x],cnt+1));
	cnt!=m?dfs(x+1,ansn,cnt):void();
	return;
} 
main() {
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(register int i=1;i<=n;++i)cin>>a[i];
	p1[0]=0;
	p1[1]=a[1];
	p2[n]=a[n];
	p2[n+1]=0;
	for(int i=2;i<=n;++i)p1[i]=p1[i-1]^a[i];
	for(int i=n-1;i;--i)p2[i]=p2[i+1]^a[i];
	dfs(1,0,0);
	cout<<ans;
	return 0; 
}
#endif
```

赛时为了 E 磕了 1h 且放了 D，然后 E 有两个点超时。。。

---

