# Axis Walking

## 题目描述

Iahub wants to meet his girlfriend Iahubina. They both live in $ Ox $ axis (the horizontal axis). Iahub lives at point 0 and Iahubina at point $ d $ .

Iahub has $ n $ positive integers $ a_{1} $ , $ a_{2} $ , ..., $ a_{n} $ . The sum of those numbers is $ d $ . Suppose $ p_{1} $ , $ p_{2} $ , ..., $ p_{n} $ is a permutation of $ {1,2,...,n} $ . Then, let $ b_{1}=a_{p1} $ , $ b_{2}=a_{p2} $ and so on. The array b is called a "route". There are $ n! $ different routes, one for each permutation $ p $ .

Iahub's travel schedule is: he walks $ b_{1} $ steps on $ Ox $ axis, then he makes a break in point $ b_{1} $ . Then, he walks $ b_{2} $ more steps on $ Ox $ axis and makes a break in point $ b_{1}+b_{2} $ . Similarly, at $ j $ -th $ (1<=j<=n) $ time he walks $ b_{j} $ more steps on $ Ox $ axis and makes a break in point $ b_{1}+b_{2}+...+b_{j} $ .

Iahub is very superstitious and has $ k $ integers which give him bad luck. He calls a route "good" if he never makes a break in a point corresponding to one of those $ k $ numbers. For his own curiosity, answer how many good routes he can make, modulo $ 1000000007 $ ( $ 10^{9}+7 $ ).

## 说明/提示

In the first case consider six possible orderings:

- \[2, 3, 5\]. Iahub will stop at position 2, 5 and 10. Among them, 5 is bad luck for him.
- \[2, 5, 3\]. Iahub will stop at position 2, 7 and 10. Among them, 7 is bad luck for him.
- \[3, 2, 5\]. He will stop at the unlucky 5.
- \[3, 5, 2\]. This is a valid ordering.
- \[5, 2, 3\]. He got unlucky twice (5 and 7).
- \[5, 3, 2\]. Iahub would reject, as it sends him to position 5.

In the second case, note that it is possible that two different ways have the identical set of stopping. In fact, all six possible ways have the same stops: \[2, 4, 6\], so there's no bad luck for Iahub.

## 样例 #1

### 输入

```
3
2 3 5
2
5 7
```

### 输出

```
1
```

## 样例 #2

### 输入

```
3
2 2 2
2
1 3
```

### 输出

```
6
```

# 题解

## 作者：Alex_Wei (赞：6)

> [CF327E Axis Walking](https://www.luogu.com.cn/problem/CF327E)

[双倍经验](https://www.luogu.com.cn/problem/P2396)。

设 $f_S$ 表示集合 $S$ 的答案，若 $g_S = \sum_{i\in S} a_i$ 不合法，则 $f_S = 0$，否则 $f_S = \sum_{i\in S} f_{S\backslash i}$。

直接做的时间复杂度为 $\mathcal{O}(2 ^ n n)$，开 O2 可以通过。我们枚举 $i$ 的时候通过 $\mathrm{lowbit}(S)$ 做到不枚举无用转移，有 $\frac 1 2$ 的常数。

优化：

- 若 $k = 0$，则答案为 $n!$。
- 若 $k = 1$，则答案为 $n! - \sum_{g(S) = x} |S|! (n - |S|)!$。

- 当 $g_S < \min(x, y)$ 时，$f_S = |S|!$。可以将 $x, y$ 同时变成 $\sum a_i - x, \sum a_i - y$ 使 $\min(x, y)$ 变大。
- 当使得 $g(S) = x$ 和 $g(T) = \sum a_i - y$ 的 $S$ 和 $T$ 的数量之积不大时，可以枚举 $S, T$ 算出同时经过 $x, y$ 的路径数，再套入 $k = 1$ 的容斥。

[代码](https://codeforces.com/contest/327/submission/176821874)，不开 O2 获得了双倍经验最优解（749ms），开 O2 又获得了双倍经验最优解（476ms）。

**怎么没有人写 $\boldsymbol {3 ^ {n / 2}}$ 的做法啊？**

设 $A(S)$ 表示集合 $S$ 的 $a_i$ 之和。

考虑 $k = 1$，我们发现相当于求 $n! - \sum\limits_{A(S) = x} |S|! (n - |S|)!$。子集和等于某个值，考虑 MITM，将 $a$ 分成两部分 $L, R$，求出 $f_{i, j}$ 表示 $R$ 的子集 $R_1$ 的数量，使得 $|R_1| = i$ 且 $A(R_1) = j$。枚举 $L$ 子集 $L_1$ 和 $i = |R_1|$，则答案减去 $f_{i, x - A(L_1)} (i + |L_1|)!(n - i - |L_1|)!$。

$k = 2$ 同理，运用容斥原理将答案转化为 $n!$ 减去经过 $x$ 的方案数，减去经过 $y$ 的方案数，再加上同时经过 $x$ 和 $y$ 的方案数。对于后者 $\sum\limits_{A(S_1) = x} \sum\limits_{A(S_2) = y - x\land S_1 \cap S_2 = \varnothing} |S_1|! |S_2|! (n - |S_1| - |S_2|)!$。类似地，枚举 $R$ 的子集 $R_1$ 和 $R\backslash R_1$ 的子集 $R_2$，求出 $f_{i, j, l, m}$ 表示 $|R_1| = i$，$|R_2| = j$，$A(R_1) = l$ 且 $A(R_2) = m$ 的方案数。枚举 $L$ 子集 $L_1$ 和 $L\backslash L_1$ 的子集 $L_2$，则答案加上 $f_{i, j, x - A(L_1), y - x - A(L_2)} (|L_1| + i)! (|L_2| + j)! (n - i - j - |L_1| - |L_2|)!$。

使用哈希表维护 $k = 1$ 的 $j$ 一维和 $k = 2$ 的 $l, m$ 两维，时间复杂度 $\mathcal{O}(3 ^ {n / 2} n ^ 2)$。注意 `unodered_map` 会 TLE，用 `gp_hash_table`。[代码](https://codeforces.com/contest/327/submission/176961722)。洛谷上不开 O2 会 TLE，开 O2 获得了双倍经验最优解（383ms）。

---

## 作者：Mobius127 (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/CF327E)

---
>>题目大意

> 给出一堆数，让你对其进行排序，求有多少种方案满足任意前缀和不会出现给定的数字。
---

看到这么小的数据范围果断状压。

令 $f_S$ 为选择状态为 $S$ 的方案数，易知最终答案为 $f_{2^n-1}$ 。

考虑 $f_S$ 珂以由哪些前继状态 $f_T$ 转移而来，因为每次只能选一个，所以 $S$ 与 $T$ 应该满足：$S \oplus  T = 2^p | S>T$，异或相当与把除了选择的数之外的的去掉，然后只剩一个数就必然是 $2^p$ 了。

直接一个个枚举 $T$ 肯定是会爆的，我们可以拿一个东西记录最后一个位是什么，然后将一个原值等于 $S$ 的寄存器异或掉她，然后拿这个寄存器的最后一位去异或 $S$ 即可枚举到所有可能的 $T$。

上面的一个过程都离不开一个操作：取最后一位，想必学过树状数组的同学都能回忆起来它是 $\text{lowbit(x)}$。

我们再把状态转移方程列出：

$$f_S=\sum_{T \oplus S = 2^p}^{(0,S)} f_T$$

这是没有限制的情况。

那如果有限制呢？

很简单，只要 $S$ 所表示的选择状态和被限制赋值为 0 即可。

这个和珂以直接每次 $O(\log n)$ 暴力求，也可以类似于 $f$ 一样求。

### Code

```cpp
#include <stdio.h>
#include <algorithm>
#include <string.h>
#define N 100005
#define lowbit(x) (x&(-x))
using namespace std;
typedef long long ll;
const int INF=0x3f3f3f3f;
const int mo=1e9+7;
inline int read(){
	char ch=getchar();int x=0, f=1;
	while(ch<'0'||ch>'9'){if(ch=='-') f=-1; ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
	return x*f;
}
int n, k, notin[3], R;
int a[1<<24], f[1<<24];
signed main(){
	n=read(), R=1<<n;
	for(int i=1; i<R; i<<=1) a[i]=read();
	k=read();for(int i=1; i<=k; i++) notin[i]=read();
	f[0]=1;
	for(int S=1; S<R; S++){
		a[S]=a[S^lowbit(S)]+a[lowbit(S)];
		if(a[S]==notin[1]||a[S]==notin[2]) continue;
		for(int T=S; T; T^=lowbit(T)) f[S]=(f[S]+f[S^lowbit(T)])%mo;
	}
	printf("%d", f[R-1]);
	return 0;
}

```


---

## 作者：quarmer (赞：1)

[题目](https://www.luogu.com.cn/problem/CF327E)。

比较板子的状压 dp。

读完题容易设出状态 $f_{i}$ 表示此时已选数的状态，$i$ 的二进制位 $0/1$ 分别对应这一个数不选或选。

因为已选数的和不得等于给定数，我们新开一个数组记录每个选数的状态的数总和。

对于每一个 $i$，找到 $i$ 中所有二进制位为 $1$ 的位，设此位为第 $j$ 位，让这一位的数作为最后一个被选的数，则易得方程 $f_{i}=f_{i} + f_{i \otimes 2^j}$。其中 $\otimes$ 表示异或运算。

然后会发现直接照着方程打可能会 T（写得好有的不会）。

考虑优化，dp 中枚举状态是必须的，无法优化，优化点只能在找出每一个 $1$ 上。

对于此，**我们可以用 lowbit 运算来快速找到此二进制数所有的 $1$，从而卡常 AC 本题。**

```cpp
#include <algorithm>
#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <stack>
#include <queue>
#include <vector>
#include <list>
#include <map>
#include <ctime>
//#define int long long
//#define int __int128
//#define int long long
//#define int long double
//#define Int int
#define mr make_pair
#define ff first
#define ss second
#define lb(x) (x & (-x))
using namespace std ;
int a[26] ;
int b[3] ;
int f[1 << 24 | 1] ;  
int sum[1 << 24 | 1] ;
const int mod = 1e9 + 7 ;
int n, m ; 
bool check(int x) {
	return (x != b[1] && x != b[2]) ;
}
int read(){
	char ch ;int s = 0 ;int w = 1;
	while((ch = getchar()) >'9' || ch < '0' )if(ch == '-')w = -1 ;
	while(ch >= '0' && ch <= '9')s = (s << 1) + (s << 3) + (ch ^ 48) , ch = getchar() ;
	return s * w ;
}
signed main() {
    cin >> n ;
    for(int i = 1 ; i <= n ; i++) a[i] = read() ;
    cin >> m ;
    memset(b, -1, sizeof(b)) ;
    for(int i = 1 ; i <= m ; i++) b[i] = read() ;
    f[0] = 1 ;
    for(int i = 0 ; i < n ; i++) sum[1 << i] = a[i + 1] ;
    int maxn = 1 << n ;
    for(int i = 1 ; i < maxn ; i++) sum[i] = sum[lb(i)] + sum[i - lb(i)] ;
    for(int i = 0 ; i < maxn ; i++) {
    	if(!check(sum[i])) continue ;
		int k = i ;
    	while(k) { 
    		f[i] += f[i ^ lb(k)] ;
    		if(f[i] >= mod) f[i] -= mod ;
    		k -= lb(k) ; //用lowbit快速找出每一位的1 
		}
	}	
    cout << f[(1 << n) - 1]  ;
	return 0 ;
}
```

[双倍经验 P2396](https://www.luogu.com.cn/problem/P2396)。

---

## 作者：__Hacheylight__ (赞：1)

给一个序列，可以任意重排，但是前缀和不能出现给定数字中的数，问有几种排列方式

n<=24，这样的数量级不是搜索就是状压。明显这道题目是状压。

dp[i]表示选的状态为i的方案数

这题主要练习通过lowbit优化的dp



```cpp
#include <bits/stdc++.h>
using namespace std ;
const int p = 1e9+7;
const int M = (1<<25) ;
int lowbit(int x){return x&-x;}
int sum[M],a[25],no[3],dp[M] ;
int n,k ;
int main(){
	scanf("%d",&n) ;
	for (int i=0;i<n;i++){
		scanf("%d",&a[i]) ;
		sum[1<<i]=a[i] ;
	}
	scanf("%d",&k) ;
	for (int i=0;i<k;i++) scanf("%d",&no[i]) ;
	dp[0]=1 ;
	for (int i=1;i<(1<<n);i++){
		sum[i]=sum[i&~lowbit(i)]+sum[lowbit(i)] ;
		if (sum[i]==no[0] || sum[i]==no[1]) continue ;
		for (int j=i;j!=0;j-=lowbit(j))
			dp[i]=(dp[i]+dp[i&~lowbit(j)])%p ;
			
		
	}
	printf("%d\n",dp[(1<<n)-1]) ;
}
```

---

## 作者：可爱即是正义 (赞：1)

###  谨以此篇题解来纪念的我可怜的状压水平.....

## 题目大意：给一个序列，可以任意重排，但是前缀和不能出现给定数字中的数，问有几种排列方式

注意到N很小...~~K更小~~所以应该是可以状压~~因为暴力全排列过不去~~
一般全排列只能到n==11，由于状压加上lowbit可以跑得很快...因为我太弱跑的仍然很慢

所以说用一个sum数组记录所选的数得前缀和，所选的数在sum的下标中体现

下标的每一个二进制位代表一个数选还是不选。

具体求可以直接枚举，二进制暴力的上界是n==15，而本题n到了24，所以考虑优化

考虑枚举到在当前这位之前，可能有很多位0

所以很自然的想到lowbit


------------

lowbit的意义：~~你大概翻译一下也能猜出来，~~就是求一个二进制数从右向左数第一个1的位权

#### 举个栗子：28的二进制表示为 11100
所以lowbit(28)为8

具体求法不再赘述



------------
回到本题，有了lowbit这个东西便能提高程序效率

先上我的擦边代码，具体用法在代码里注释出来
```cpp
#include<cstdio>
#define lowbit(x) (x&(-x))

using namespace std;

const int M=(1<<24)+10;
const int mod=1e9+7;

typedef long long ll;

int a[M];
int o[M];
ll f[M];
ll sum[M];

int main()
{
	int n;
	scanf("%d",&n);
	for(int i=0;i<n;++i)
	{
		scanf("%d",&a[i]);
		sum[1<<i]=a[i];//每一位代表一个a[i] 
	}
	int k;scanf("%d",&k);
	for(int i=1;i<=k;++i)scanf("%d",&o[i]);
	f[0]=1;
	int lim=1<<n;//最多有n位，所以最大的下标不会超过(2^n)-1
	lim--;
	for(int i=1;i<=lim;++i)
	{
		sum[i]=sum[i&~lowbit(i)]+sum[lowbit(i)]; 
		if(sum[i]==o[1]||sum[i]==o[2])continue;//k只有2，特判即可 
		for(int j=i;j;j-=lowbit(j))//快速访问每一个为1的位
		{
			f[i]+=f[i&~lowbit(j)];
			if(f[i]>mod)f[i]-=mod;//玄学，long long的取模非常慢  --Scαpe
		}
	}
	return !printf("%lld\n",f[lim]);//皮一手 
}
```

这里补充一下~这个逻辑运算符，它的作用是把一个二进制数每一位取反
即每一位的0变成1,1变成0

所以i&~lowbit(i)的意义为去掉一个二进制数的lowbit后的值

--end

原文借鉴了[呐](https://blog.csdn.net/Tc_To_Top/article/details/47162427)中的思想，加上我自己本人的一些见解组合而成，不喜勿喷

---

## 作者：小木虫 (赞：0)

### Preface  
这道题的卡常作为一道 dp 来说过于丧心病狂...
### Problem  
给你一个长度为 $n(1\leq n\leq 24)$ 的正整数序列 $S$，再有 $k(0\leq k\leq 2)$ 个正整数。

求有多少种 $S$ 的排列方式使得其前缀和不会成为那 $k$ 个数里的任意一个。
答案对 $10^9+7$ 取模。  
### Solution  
一眼状压，很显然我们要压的是已经被用过的 $S$ 元素，这是 $O(2^n)$ 复杂度的，接下来易得转移方程：  
$dp_i=\sum_{(j\oplus i)= i+j}^{j\leq i-1}dp_j$  
但是！我们回头一看却发现这道题的数据范围不同于通常的状压，$n \leq 24$ 在状压中其实算一个很大的数据了。上述的转移方程的理论复杂度是 $O(2^n n)$ 的，经过简单计算即可发现，总的计算量为：$2 \times 2^{24} \times 24=805306368$。  

这个复杂度且没有 O2 优化的情况下超时几乎是必然。但是这个复杂度也并非完全无法挽回，我们在按位枚举状态的时候使用了 $O(n)$ 的复杂度，但实际上并不需要，我们可以通过求 lowbit 来快速找出一个大数的每一位 1。  

这时候复杂度瓶颈来到了前面的预处理，即找出加和为 $k$ 个数之一的状态数。这里的计算是和状态中 1 的所在位置有关的，不能直接 lowbit 处理，但是我们可以在前面算好每一个 2 的幂次所代表的位数，然后就可以使用 lowbit 了。  

code：  
```cpp
#include <bits/stdc++.h>
using namespace std;
const int mod=1e9+7;
int n,k;int s[30];
bool vis[(1<<24)];int b[30];
int dp[(1<<24)];int id[(1<<24)];
inline int popdata(int x){
	int res=0;
	while(x!=0){
		int now=x&-x;
		res+=s[id[now]];
		x-=now;
	}return res;
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n;int base=1;
	for(int i=0;i<=n;i++){
		id[base]=i+1;base*=2;
	}
	for(int i=1;i<=n;i++)
		cin>>s[i];
	cin>>k;
	for(int i=1;i<=k;i++)cin>>b[i];
	for(int i=0;i<=(1<<n)-1;i++){
		for(int j=1;j<=k;j++)
			if(popdata(i)==b[j])vis[i]=1;
	}dp[0]=1;
	for(int i=0;i<=(1<<n)-1;i++){
		if(vis[i]){dp[i]=0;continue;}
		int l=((1<<n)-1)^i;
		while(l!=0){
			int now=l&-l;
			dp[i^now]+=dp[i];dp[i^now]%=mod;
			l-=now;
		}
	}cout<<dp[(1<<n)-1];
}
```


---

## 作者：AIskeleton (赞：0)

状压好题。

### 题意

> 给你一个长度为 $n$ 的正整数序列 $S$，再有 $k$ 个正整数。
求有多少种 $S$ 的排列方式使得其前缀和不会成为那 $k$ 个数里的任意一个。答案对 $1e9+7$ 取模。
$0 \le k \le 2,1 \le n \le 24$。

### 题解

因为 $n \le 24$，明显是状压。

假设 $f_i$ 表示在状态为 $i$ 的情况下的组合方法数，则答案为 $f_{2^n-1}$。

定义一个数组 $a$，其中 $a_i$ 存储在情况 $i$ 下的元素之和，很容易理解。

对于一个新的 $a_i$，$a_i = a_{lowbit(i)} + a_{i \, \operatorname{xor} \, lowbit(i)}$。

考虑如何转移。

对于 $f_i$ 可以由 $f_j$ 转移而来，其中 $j$ 是 $i$ 去掉一个元素得来的。

那么状态转移方程就是 $f_i = \sum f_j$，在循环内枚举每一位的情况即可。

### 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
#define lb(x) (x&(-x))
using namespace std;const ll N=24,mod=1e9+7;
int a[1<<N],f[1<<N],n,k,b[N],lim;
int main(){
    cin>>n;lim=(1<<n)-1;for(int i=1;i<=lim;i<<=1)cin>>a[i];
    cin>>k;for(int i=1;i<=k;i++)cin>>b[i];f[0]=1;
    for(int i=0;i<=lim;i++){
	a[i]=a[i^lb(i)]+a[lb(i)];
	if(a[i]!=b[1]&&a[i]!=b[2])
	    for(int j=i;j;j^=lb(j))
                f[i]=(f[i^lb(j)]+f[i])%mod;
    }cout<<f[lim];return 0;
}
```

---

## 作者：Mihari (赞：0)

# 题目

[传送门](https://www.luogu.com.cn/problem/CF327E)

# 题解

一道很水的状压题...

设 $f[s]$ 为数字出现情况为 $s$ 时的方案数，显然如果 $\exist k[i],sum[s]=k[i]$ 那么 $f[s]=0$，其中 $sum[s]$ 为选择数字情况为 $s$ 时的数字和，而转移也很好写了：
$$
f[s]=\sum f[s']
$$
其中 $s'$ 为 $s$ 少出现了一个数字的状态。

有一个边界条件 —— $f[0]=1$，其他的没什么好说的了......

但是洛谷推荐有一道[模型一样的题](https://www.luogu.com.cn/problem/P2396)，需要对题目有很深了解并且合理转化，推荐去做一做。

推荐题唯一 $ex$ 的就是它卡常...

# 代码

```cpp
https://www.cnblogs.com/Arextre/p/13460640.html
```



---

## 作者：SpXace (赞：0)

状压dp题，sum[i]为状态为i时的前缀和，dp[i]为到i为止方案数

每次新的状态（sum[i]） = 仅有末尾1的状态 + 去掉末尾1的状态，而二者都在先前求过了，可以O（1）的求出sum[i] 的值

而dp[i] 则要枚举每种情况，用lowbit取1而非枚举每一位来加速，将每种情况累加即可


```
#include<iostream>
#include<cstdio>
using namespace std;
inline int Read()
{
	int s = 0,w = 1;
	char ch = getchar();
	while(ch < '0' || ch > '9'){
		if(ch == '-') w = -1;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9')
		s = (s << 3)+(s << 1) + ch - '0',ch = getchar();
	return w * s;
}
int Mod = 1e9 + 7; 
int N,K,No[2],a[(1<<24)+1];
long long sum[(1<<24)+1],dp[(1<<24)+1];
int lowbit(int Q){
	return Q&(-Q);
}
int main()
{
	N = Read();
	for(int i = 0; i < N; ++i)
	{
		a[i] = Read();
		sum[1<<i] = a[i];
	}
	K = Read();
	for(int i = 0; i < K; ++i)  //个数 <= 2 
 		No[i] = Read();
 	dp[0] = 1;  
	 for(int i = 1; i < (1 << N); ++i)
	 {
	 	sum[i] = sum[i-lowbit(i)] + sum[lowbit(i)];
	 	if(sum[i] == No[0] || sum[i] == No[1])
	 		continue;
	 	for(int j = i; j; j -= lowbit(j))
	 	{
	 		dp[i] += dp[i&~lowbit(j)];
	 		if(dp[i] > Mod) dp[i] -= Mod;
	 	}
	 } 
	 cout << dp[(1<<N)-1];
	return 0;
}
```

---

## 作者：羽儇 (赞：0)

$\color{Red}\text{状压DP(位运算) + 压行}$


------------


 $\text{题目}$：
 
 
给你一个长度为n(1<=n<=24)的正整数序列S，

再有k(0<=k<=2)个正整数。

求有多少种S的排列方式使得其前缀和不会成为那k个数里的任意一个。 

答案对1e9+7取模


------------


$Solution$

既然这些数珂以任意自由排列

那我们可以把它当做**选取一些数**得到和

珂以通过二进制来表示对每个数的选取情况

1 表示已选取，0 表示未选取


------------


详见代码中注释

```cpp
#include <cstdio>
const int mod = 1e9 + 7 ;
const int Z = 24;
int N,M,a[1 << Z],M_1,M_2,f[1 << Z] ;
int main()
{
    scanf("%d",&N); 
    for(int i = 0 ;i < N ; i ++)
    scanf("%d",&a[1<<i]);
    scanf("%d",&M);
    (((M > 0)&&scanf("%d",&M_1))&&((M > 1)&&scanf("%d",&M_2)));//毒瘤の输入珂还行？QAQ
    f[0] = 1;
    for(int i = 1 ;i <= (1 << N ) - 1 ; i ++)//枚举所有种情况
    {
        int j = i & -i;//最后一位为1的
        a[i] = a[i^j] + a[j];//相加得前缀和
        //如 i = 1110,j = 10,i^j = 1100
        //a[1110] = a[1100] + a[0010]
        //a[1100]与a[0010]总是在a[1110]前被计算出，珂以算出前缀和
        if(a[i] == M_1 || a[i] == M_2)continue;//如果恰好前缀和为M_1与M_2,则跳过，不进行计算方案数
        for(int k = i ; k ;k ^= j,j = k & -k )f[i] = (f[i] + f[i^j])%mod;
        //让我来剖析下
        //for()内部是枚举去掉每一位的情况
        //例如f[1110] = f[1100] + f[1000] + f[0]
    
    }
    printf("%d",f[(1 << N ) -1]);
    return 0;
}
```
22行短$AC Code$$\text{呈上}$

~~码风珂还行？~~

```cpp
#include <cstdio>
const int mod = 1e9 + 7 ;
const int Z = 24;
int N,M,a[1 << Z],M_1,M_2,f[1 << Z] ;
int main()
{
    scanf("%d",&N); 
    for(int i = 0 ;i < N ; i ++)
    scanf("%d",&a[1<<i]);
    scanf("%d",&M);
    f[0] = 1;
    (((M > 0)&&scanf("%d",&M_1))&&((M > 1)&&scanf("%d",&M_2)));
    for(int i = 1 ;i <= (1 << N ) - 1 ; i ++)
    {
        int j = i & -i;
        a[i] = a[i^j] + a[j];
        if(a[i] == M_1 || a[i] == M_2)continue;
        for(int k = i ; k ;k ^= j,j = k & -k )f[i] = (f[i] + f[i^j])%mod;
    }
    printf("%d",f[(1 << N ) -1]);
    return 0;
}
```



---

