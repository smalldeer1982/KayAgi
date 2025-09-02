# Increase Sequence

## 题目描述

**题目大意**：

给定一个序列，可以对若干对区间$[l,r]$中的数+$1$，且保证任意两个区间的左右端点不重合（即$l_1$!=$l_2$且$r_1$!=$r_2$）。

最终要求序列中所有元素值都等于$h$，请输出总方案数对$1e9$+$7$取模后的结果。


------------

## 说明/提示

$1$≤$n,h$≤$2000$

$0$≤$a_i$≤$2000$

## 样例 #1

### 输入

```
3 2
1 1 1
```

### 输出

```
4
```

## 样例 #2

### 输入

```
5 1
1 1 1 1 1
```

### 输出

```
1
```

## 样例 #3

### 输入

```
4 3
3 2 1 1
```

### 输出

```
0
```

# 题解

## 作者：LittleMoMol (赞：6)

## 前言

看了题解才会的……决定自己详细写一篇保证自己学明白了！

[良好的专注力练习体验](https://www.cnblogs.com/LittleMoMol-kawayi/p/LuoGu_solution_CF466D.html)

## 思路

题目给我印象最深的一句话是：**任意**两个区间的左右端点不重合。感觉这个要求挺苛刻的，你会发现 $a$ 数组的第 $1$ 项和最后一项最多和 $h$ 相差 $1$

这个不难理解，因为想要让第一项 $+1$，你的左端点必须是 $1$，那么以后的所有操作的左端点都不能是 $1$ 了，自然只能操作一次，最后一项同理。

所以决定因素在于 $a_i$ 和 $h$ 相差多少，那么我们把 $a_i$ 的意义变一下，如果原序列为 $a_i$，那么新的 $a_i$ 表示 $h - a_i$（接下来的所有 $a_i$ 表示的均为最新意义）

分析每次操作，改变的是一个区间且加的值是固定的，如果暴力修改复杂度不可承受，考虑有没有一种 $O(1)$ 的修改方式？差分！

令 $d_i=a_i-a_{i-1}$，那么每次区间为 $[l,r]$ 的操作，等价于 $d_l-1,d_{r+1}+1$，由于端点不能重复，所以每个 $d_i$ 至多会被**减**一次，那么无解情况就出来了：若存在 $|d_i|>1$，必然无解！（请注意，现在的操作为区间减，因为 $a$ 数组的意义已经变了）

最终合法的状态为：$d$ 数组全为 $0$，而可能的 $d_i$ 的值也就 $3$ 种：$1,-1,0$，逐个分析即可。

- 若 $d_i$ 为 $1$，说明必须要有一个操作的左端点为 $i$，也就是说**左端点数量要加一**。
- 若 $d_i$ 为 $-1$，说明必须要有一个操作的右端点为 $i$，那么这个右端点可以和之前的任何一个左端点匹配，完毕后**左端点数量要减一**，因为**一个端点不能同时做两次左端点**。
- 若 $d_i$ 为 $0$，该怎么办？在此之前，我想先明确一下题意，题意指：一个端点不能作多次左端点，也不能作多次右端点，但是可以**作一次左端点再作一次右端点**。所以对于 $0$ 的情况，要么先让它作右端点，和之前的任意一个左端点匹配，然后再作左端点，来保证 $0-1+1=0$；要么干脆就不动它，即不对其进行操作。请注意：这里**不需要改变左端点数量**，因为在第一种情况中既作右端点又作左端点就抵消了，第二种情况下无事发生……

## Code

```cpp
#include <iostream>

using namespace std;

typedef long long LL;
const int N = 2010;
const LL mod = 1e9 + 7;

int n, h, num;
int a[N], diff[N];
LL ans = 1;

int main()
{
	cin >> n >> h;
	for (int i = 1; i <= n; i ++ )
	{
		cin >> a[i];
		a[i] = h - a[i];
	}
	for (int i = 1; i <= n + 1; i ++ )
	{
		diff[i] = a[i] - a[i - 1];
		if (abs(diff[i]) > 1) return cout << 0 << endl, 0;
	}
	for (int i = 1; i <= n; i ++ )
	{
		if (diff[i] == 1) num ++ ;
		if (diff[i] == 0) ans = ans * (num + 1) % mod;
		if (diff[i] == -1) ans = ans * num % mod, num -- ;
	}
	cout << ans << endl;
	return 0;
}
```

## 后记
花了好长时间才理解，完结撒花！

---

## 作者：仗剑_天涯 (赞：5)

一道思维题QAQ

由于最终目的是将每个数变成h，所以我们可以将所有数减去h，最后让他们都变成0就好惹。

左右端点不许重合，所以一个点不可能既是左端点又是右端点。

1.相邻两个数相差超过1，放弃治疗，不可能有方案。

2.后一个数比前一个数大1，只能新开一个区间。

3.前一个数比后一个数大1，只能结束一个区间。

4.相邻两个数相等，可以结束一个区间后在开一个区间，或者不进行操作。

代码:
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,h,t,x,ans=1,a[2010],s[2010];
int main()
{
	cin>>n>>h;
	for(int i=1;i<=n;i++) 
	{
		scanf("%lld",&x);
		a[i]=h-x;
	}
	for(int i=1;i<=n+1;i++)
	{
		s[i]=a[i]-a[i-1];
	}
	for(int i=1;i<=n+1;i++)
	{
		if(s[i]==1)//2
		{
			t++;
		}
		else 
		{
			if(s[i]==0)//4
			{
				if(t!=0) 
				{
					ans=(ans*(t+1))%1000000007;
				}
			}
			else 
			{
				if(s[i]==-1)//3
				{
					ans=(ans*t)%1000000007;
					t--;
				}
				else//1
				{
					cout<<0;
					return 0;
				}
			}
		}
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：ETHANK (赞：3)

[传送门](https://www.luogu.com.cn/problem/CF466D)

思维题。

首先可以设 $a'_i=h-a_i$ 为每个数离 $h$ 差的操作次数，而我们想通过若干次左右端点不重合的区间 $-1$ 来使 $a'_i=0$ 。考虑区间 $-1$ 所带来的影响，设这段区间为 $[l,r]$ ，实质上为将差分数组 $d$ 中的 $d_l$ 减一，$d_{r+1}$ 加一。而最终所有元素值相等则等价于将差分数组转为全 $0$ ，故下面只考虑差分数组上的操作。

再看左右端点不重合的条件，这说明了一个值和原来相比，只有 $+1,-1$ 或不变三种。所以如果差分数组中某个值的绝对值大于 $1$ ，显然无解。最后做区间端点匹配即可，具体地：

- 差分值为 $1$ 则放进左端点中
- 为 $0$ 可以不操作，或者同时为左右端点
- 为 $-1$ 则是右端点，与前面有的任意左端点匹配。

时间复杂度： $O(n)$

```cpp
#include <bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define ll long long
using namespace std;
inline ll read(){
    ll x=0,f=1;char ch=getchar();
    while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}
    while (isdigit(ch)){x=x*10+ch-48;ch=getchar();}
    return x*f;
}
const int N=1e5+5,mod=1e9+7;
int n,h,a[N],d[N],num;
ll ans=1;
int main(){
    n=read(),h=read();
    rep(i,1,n)a[i]=h-read();
    rep(i,1,n+1){
        d[i]=a[i]-a[i-1];
        if(abs(d[i])>1)return puts("0"),0;
    }
    rep(i,1,n+1){
        if(d[i]==1)++num;
        if(d[i]==0){
            ans=ans*(num+1)%mod;
        }
        if(d[i]==-1){
            ans=ans*num%mod;--num;
        }
    }
    printf("%lld\n",ans);
    return 0;
}
```



---

## 作者：gcx12012 (赞：2)

### 前言
没有看出来贪心，但是用 dp 秒了。
### Solution
我们可以设 $b_i = h-a_i$，表示每个点 $i$ 需要加法的次数，显然当某个 $b_i < 0$ 时绝对无解。

然后根据题意得出，关于点内放置区间端点的状态，有且仅有四个：
- 没有放置任何端点；

- 放置了一个 $l$ 端点；

- 放置了一个 $r$ 端点；

- 同时放置了一个 $l$ 端点和一个 $r$ 端点。

由此我们可以 dp，设 $f_{i,j,0/1}$ 为处理了前 $i$ 个位置，还有 $j$ 个 $l$ 端点未匹配，在第 $i$ 个点的位置是否同时放置了一个 $l$ 端点和一个 $r$ 端点，初始化 $f_{0,0,0}=1$。

我们先考虑前两类情况，对于当前未匹配的若干个 $l$，显然在之后匹配 $r$ 时这个区间一定跨过当前点，因此贡献是有效的。

对于第三类情况，一个 $r$ 是可以任意匹配前面若干个未匹配的 $l$ 的，这对前面的合法性没有影响。

最后一类情况也是同理的，只是需要一个特殊状态去记录。

由此可以得出四个对应情况的 dp 转移方程：
$$
f_{i+1,j,0} \gets f_{i,j,0}+f_{i,j,1}
$$
$$
f_{i+1,j+1,0} \gets f_{i,j,0}+f_{i,j,1}
$$
$$
f_{i+1,j-1,0} \gets (f_{i,j,0}+f_{i,j,1})\times j
$$
$$
f_{i+1,j,1} \gets (f_{i,j,0}+f_{i,j,1}) \times (j+1)
$$
记得根据 $b_i$ 去判定转移的合法性。

最后的答案就是 $f_{n,0,0}+f_{n,0,1}$，整个算法的时间复杂度为 $O(n^2)$，可以通过。
### Code

```cpp
#include<bits/stdc++.h>
#include<cmath>
#define ll long long
#define lll __int128
#define ull unsigned long long
#define N 2010
#define For(i,a,b) for(ll i=a;i<=b;++i)
#define Rof(i,a,b) for(ll i=a;i>=b;--i)
#define ls x<<1
#define rs x<<1|1
#define lson ls,l,mid
#define rson rs,mid+1,r 
#define pb push_back
#define mk make_pair
#define pque priority_queue
#define pii pair<int,int>

using namespace std;
bool st;
const ll mod=1e9+7;
ll a[N],f[N][N][2];
int n,m;
bool ed;

ll read(){
	ll x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}


int main()
{
    //fprintf(stderr,"%d",(&ed-&st)/1024/1024);
	//freopen("C.in","r",stdin);
    //freopen("C.out","w",stdout);
    n=read(),m=read();
    int is=1;
    For(i,1,n) a[i]=m-read(),is&=(a[i]>=0);
    if(!is){
    	printf("0");
    	return 0;
	}
	f[0][0][0]=1;
	For(i,0,n-1){
		For(j,0,i){
			if(j==a[i+1]) f[i+1][j][0]=(f[i+1][j][0]+f[i][j][0]+f[i][j][1])%mod;//add nothing
			if(j+1==a[i+1]) f[i+1][j+1][0]=(f[i+1][j+1][0]+f[i][j][0]+f[i][j][1])%mod;//add l
			if(j==a[i+1]) f[i+1][j-1][0]=(f[i+1][j-1][0]+(f[i][j][0]+f[i][j][1])*j%mod)%mod;//add r
			if(j==a[i+1]-1) f[i+1][j][1]=(f[i+1][j][1]+(f[i][j][0]+f[i][j][1])*(j+1))%mod;// add l and r
		}
	}
	cout<<(f[n][0][0]+f[n][0][1])%mod;
	return 0;
}
/*

*/
```

---

## 作者：Laoshan_PLUS (赞：2)

### 题意

给定一个序列 $a$，可以对若干对区间 $[l,r]$ 中的数 $+1$，且保证**任意两个区间的左右端点不重合**（即 $l_1\ne l_2$ 且 $r_1\ne r_2$）。

最终要求序列中所有元素值都等于 $h$，请输出总方案数对 $10^9+7$ 取模后的结果。

### 解析

这种题的类型屡见不鲜，将 $a$ 的所有元素减去 $h$，于是目标变成让所有元素变成 $0$。（下文的 $a$ 序列均指修改后的）

但我们注意到题干中被加粗的这句话。这就说明位于区间边界的元素 **只能被加一次**。例如 $a$ 序列为 $[0,-1,-3,-3]$ 就是显然不可能的一种情况，两个 $-3$ 都位于区间边界，不可能一次加到 $-1$，所以遇到这种情况直接输出 $0$。我们于是求 $a$ 序列的差分数组 $d$，令 $d_i=a_i-a_{i-1}$，每次对区间 $[l,r]$ 的操作相当于 $d_l-1,d_{r+1}+1$，目标变为使 $d$ 数组变为全 $0$。令 $\textit{num}$ 表示已统计的左端点数量，则对于每个 $d_i$：

- $\lvert d_i\rvert>1$，此时直接输出 $0$，如上文所述；
- $d_i=1$，也就是说 $a_i$ 比 $a_{i-1}$ 大 $1$，此时 $d_i$ 一定是左端点，计入 $\textit{num}$；
- $d_i=0$，也就是说 $a_i=a_{i-1}$，此时 $d_i$ 可以不操作，也可以结束一个区间再开一个区间（即同时为左右端点），答案乘上 $(\textit{num}+1)$；
- $d_i=-1$，也就是说 $a_i$ 比 $a_{i-1}$ 小 $1$，此时 $d_i$ 一定是右端点，答案乘上 $\textit{num}$，随后 $\textit{num}-1$（一个区间结束，也就是可用的左端点数 $-1$）。

另外勿忘每次计算对 $10^9+7$ 取模，**勿忘开 long long**。

### 实现

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
constexpr int MOD = 1e9 + 7;
int n, h, a[2005], d[2005];
ll ans = 1, num;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(nullptr);
	cin >> n >> h;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		a[i] = h - a[i];
	}
	for (int i = 1; i <= n + 1; i++) {
		d[i] = a[i] - a[i - 1];
		switch (d[i]) {
		case 1:
			num++;
			break;
		case 0:
			ans = ans * (num + 1) % MOD;
			break;
		case -1:
			ans = ans * (num--) % MOD;
			break;
		default:
			cout << 0 << '\n';
			return 0;
		}
	}
	cout << ans << '\n';
	
	return 0;
}
```

---

## 作者：Lotus_Land (赞：0)

用差分数组把区间修改转化为单点修改。把区间 $[l,r]$ 加 $1$ 等价于在差分数组 $c$ 上 $c_{l}\leftarrow c_{l}+1,c_{r+1}\leftarrow c_{r+1}-1$。

通过单点加 $1$ 或减 $1$ 的操作将原数组的差分数组变成目标数组的差分数组 $h,0,0,\dots,0$。因为规定 $l$ 和 $r$ 不能重复，所以每个数只有 $4$ 种操作方式：$+1$，$-1$，$+1$ 且 $-1$，什么也不做。但还要考虑到左右端点匹配的问题。对于每个 $-1$ 操作，前面必须有至少一个 $+1$ 操作来和它匹配。最后匹配完剩下的 $+1$ 操作个数只能是 $0$ 或 $1$ 个，因为如果 $+1$ 没有匹配的话就意味着存在 $r=n$ 的情况，而这种情况最多出现一次。

设 $dp_{i,j}$ 为处理到第 $i$ 个数，还有 $j$ 个 $+1$ 操作未匹配的方案数。答案为 $dp_{n,0}+dp_{n,1}$。初始，若 $c_1=h$，则 $dp_{1,0}=1$；若 $c_1+1=h$，则 $dp_{1,1}=1$。

若 $c_{i+1}=0$，$dp_{i+1,j}\leftarrow dp_{i,j}\times(j+1)$，即上文所说的操作 3 和 4 两种情况。

若 $c_{i+1}=-1$，$dp_{i+1,j+1}\leftarrow dp_{i,j}$。

若 $c_{i+1}=1$ 且 $j\not=0$，$dp_{i+1,j-1}\leftarrow dp_{i,j}\times j$。

```
#include<bits/stdc++.h>
#define LL long long
#define ull unsigned long long
#define mkpr make_pair
#define lc(p) ((p)*2)
#define rc(p) ((p)*2+1)
#define fir first
#define sec second
using namespace std;
inline LL read() {
    LL x=0;
    bool t=0;
    char ch=getchar();
    while(ch<'0'||ch>'9')t|=(ch=='-'),ch=getchar();
    while(ch>='0'&&ch<='9')x=x*10+(ch^48),ch=getchar();
    return t?-x:x;
}
const int mod=1000000007;
const int N=2005;
int n,h,a[N];
LL dp[N][N];
int main() {
	cin>>n>>h;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=n;i>=1;i--){
		a[i]-=a[i-1];
	}
	if(a[1]==h)dp[1][0]=1;
	else if(a[1]+1==h)dp[1][1]=1;
	for(int i=1;i<n;i++){
		for(int j=0;j<=i;j++){
			if(a[i+1]==0)dp[i+1][j]=dp[i][j]*(j+1)%mod;
			else if(a[i+1]==-1)dp[i+1][j+1]=dp[i][j];
			else if(a[i+1]==1&&j)dp[i+1][j-1]=dp[i][j]*j%mod;
		}
	}
	cout<<(dp[n][1]+dp[n][0])%mod<<endl;
    return 0;
}
```

---

## 作者：封禁用户 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF466D)

### 题目大意

有一个长度为 $n$ 的序列，每次可以给一个区间 $[l,r]$ 都加 $1$，对于任意两次操作，都有 $l_1 \not= l_2$ 且 $r_1 \not= r_2$。要使所有的权值都为 $h$，求方案数。

### 解题思路
很显然两个相邻的位置权值差不能超过 $1$，否则肯定会出现两个左边界或右边界。

首先，我们枚举位置 $i$。如果 $a_i>a_{i-1}$，则一定作为左边界，显然该位置只有这一种情况，同时要记录下遇到了多少个左边界。

如果 $a_i<a_{i-1}$，则一定作为右边界，方案数乘以目前碰到的左边界数，左边界数要减一。

如果 $a_i=a_{i-1}$ 并且 $a_{i-1}$ 没有被作为右边界，则可以在所有的操作中任选一个断开，将 $a_{i-1}$ 作为右边界，$a_i$ 作为左边界，方案数乘以 $h-a_i$。

最重要的是要认识到一个右边界可以和不同的左边界进行匹配，因为这个 WA 了很长时间。

---

## 作者：masonpop (赞：0)

很有意思的思维题。

首先肯定让 $a_i\to h-a_i$，操作就变成了区间减法。然后区间操作不难想到差分。设 $b_i=a_i-a_{i-1}$，则对 $[l,r]$ 的一次操作相当于让 $b_l$ 减一，$b_{r+1}$ 加一。

我们发现，由于题目中 $l,r$ 分别不重合的条件，每个位置至多被加一次，减一次。因此若要 $b_i$ 全部变为 $0$，必须有 $|b_i|\le 1$。

然后对于每个位置讨论：

① $b_i=0$。此时它可以不做任何事情，也可以与之前的左端点匹配，然后自己再成为新的左端点。

② $b_i=1$。显然自己就是左端点。

③ $b_i=-1$。此时可以与之前任意一个左端点匹配。

维护当前可用左端点个数即可，$O(n)$。

---

## 作者：cloud2764scallop_eve (赞：0)

## 题意
给定一个序列 $a$，每次操作可以将区间 $[l, r]$ 中的所有元素加一，要求最后使所有元素等于 $h$。

要求：  
1. 任意两个区间的左右端点互不重合（$l1 \neq l2$ 且 $r1 \neq r2$）；
2. 对 $10^9 + 7$ 取模。

## 思路
首先，可以考虑预处理出一个新的序列，表示出原数列中每个数与 $h$ 的差，这样可以节约一定的时间复杂度。这里约定 $c_i = a_i - a_{i - 1}$，将问题转换为了如何使序列 $c$ 全部归零。

现在考虑 $c_i$ 可能的几种情况：  
- $c_i > 1$：无解。由于每个区间最多选一次，如果 $c_i > 1$，这意味着 $i$ 处需要大于一次被选择，不符合题意。
- $c_i = 1$：此时一定有一个起始点 $l$ 在 $i$ 处。这里我们维护一个 $cnt$，表示 $l$ 的个数。那么在此时，$cnt$ 加一。
- $c_i = -1$：此时需要在 $i$ 处在设置一个 $r$，所以需要和前面的某个 $l$ 匹配，故将答案乘以 $cnt$，再将 $cnt$ 减一。
- $c_i = 0$：这时考虑几种情况：  
 1. $i$ 处其实什么都没有；  
 2. $i$ 处同时作为一个 $l$ 和一个 $r$。那么就需要对当前位置的 $l$ 进行匹配，将答案乘上 $cnt + 1$。
 
## 代码
友情提示：一定要开 `long long`。
```cpp
#include <bits/stdc++.h>
#define int long  long
using namespace std;
const int mod = 1e9 + 7, N = 2005;
int a[N], b[N];
int n, h, cnt = 0, ans = 1;
signed main() {
	while (~scanf("%lld%lld", &n, &h)) {
		memset(a, 0, sizeof(a));
		memset(b, 0, sizeof(b));
		for (int i = 1; i <= n; i++) {
			scanf("%lld", &a[i]);
			a[i] = h - a[i];
		}
		for (int i = 1; i <= n + 1; i++)
			b[i] = a[i] - a[i - 1];
		for (int i = 1; i <= n + 1; i++) {
			if (b[i] == 1) cnt++;
			else if (b[i] == 0) {
				ans =  ans * (cnt + 1) % mod;
			} else if (b[i] == -1) {
				ans = ans * cnt % mod;
				cnt--;
			} else {
				printf("0\n");
				return 0;
			}
		}
		printf("%lld\n", ans);
	}
	return 0;
}
```

---

