# Power Board

## 题目描述

You have a rectangular board of size $ n\times m $ ( $ n $ rows, $ m $ columns). The $ n $ rows are numbered from $ 1 $ to $ n $ from top to bottom, and the $ m $ columns are numbered from $ 1 $ to $ m $ from left to right.

The cell at the intersection of row $ i $ and column $ j $ contains the number $ i^j $ ( $ i $ raised to the power of $ j $ ). For example, if $ n=3 $ and $ m=3 $ the board is as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1646E/f966495b3fd71da241cb3a79e264d10b59256e95.png)Find the number of distinct integers written on the board.

## 说明/提示

The statement shows the board for the first test case. In this case there are $ 7 $ distinct integers: $ 1 $ , $ 2 $ , $ 3 $ , $ 4 $ , $ 8 $ , $ 9 $ , and $ 27 $ .

In the second test case, the board is as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1646E/36fd681eff28bb5ca921155ad4010ac8be1c65a1.png)There are $ 5 $ distinct numbers: $ 1 $ , $ 2 $ , $ 4 $ , $ 8 $ and $ 16 $ .

In the third test case, the board is as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1646E/a5987da66d8c80ffc8e49f428e2b3197bf00bc43.png)There are $ 6 $ distinct numbers: $ 1 $ , $ 2 $ , $ 3 $ , $ 4 $ , $ 9 $ and $ 16 $ .

## 样例 #1

### 输入

```
3 3```

### 输出

```
7```

## 样例 #2

### 输入

```
2 4```

### 输出

```
5```

## 样例 #3

### 输入

```
4 2```

### 输出

```
6```

# 题解

## 作者：Yuby (赞：7)

[题面](https://www.luogu.com.cn/problem/CF1646E)

#### 题意：

输入两个整数 $n,m$ 保证 $n,m\leq 10^6$。你有一个矩阵 $a$，其中 $a_{ij}=i^j$。求该矩阵中有多少不同的整数。 

点数：2200

标签：素数筛，数论

#### 分析：

对于 $n,m\leq 10^6$ 显然需要 $O(n\log n)$ 左右的复杂度。

我们仔细观察一下这个矩阵。然后发现其中有出现已经出现过的数的行似乎是有规律的。不难发现任何一行的 $k$ 次方中都会出现已经出现过的数。

那么我们得到第一个结论，如果当前的第 $i$ 行可以表示为 $b^x$ 那么这一行是有重复的。

那我们不妨对于一个 $b$ 一次性计算完所有的 $b^x\leq n$ 但其实此时复杂度仍然为暴力的 $O(nm)$，因为你需要考虑每一个使得 $x$ 满足 $b^x\leq n$。考虑怎么优化这个方法。下文均只考虑不存在 $x,y$ 使得 $y^x=b$ 的行 $b$。

这时我们发现这题的一个关键的点。

对于第 $b$ 行，我们不妨设 $f(b)=x$ 表示最大的 $x$ 使得 $b^x\leq n$ 或者说 $f(b)=\left\lfloor\ \log_b n\right\rfloor$。那么对于所有的行 $y$ 使得 $f(y)=f(b)$ 他们对答案的贡献是相同的。而且 $f(b)$ 最多只有 $\log_2 n$ 种，对于每一种 $f(b)$ 进行暴力计算的复杂度为 $O(m)$ 那么复杂度降为了 $O(m\log n)$。

这时需要再处理一个问题：$O(n^m)$ 的空间是不能接受的。

我们结合上面的状态，只考虑 $f(x)$ 的值而不是 $x$ 的值。不难发现对于第 $b$ 行和其他与他一起考虑的行 $b^x$ 我们只去记录他的指数，也就是 $x^j$。正确性由 $b^{xy}=(b^x)^y$ 显然。

然后就做完了。

#### 总复杂度：

时间：$O(m\log n+n)$

空间：$O(m\log n)$

代码如下：

截止题解提交日为洛谷最优解。

```cpp
#include<bits/stdc++.h>//author:Yuby163
#define pc putchar//时间：2.67s 空间：12.41MB 代码长度：1.06KB
using namespace std;//语言：C++20 O2
typedef long long ll;
inline ll read(){ll read_result=0,is_below_0=0;char now_ch=0;while(!isdigit(now_ch)){is_below_0|=now_ch=='-';now_ch=getchar();}while(isdigit(now_ch)){read_result=(read_result<<3)+(read_result<<1)+(now_ch^48);now_ch=getchar();}return is_below_0?-read_result:read_result;}
inline void write(ll x){if(x<0){putchar('-');x=-x;}if(x>9){write(x/10);}putchar(x%10+'0');}
const ll MAXN=1e6+7,MAXM=2e7+1;
ll n,m,dp[27],p[MAXN],cnt;
bitset<MAXM>mp,book;
int main()
{
 	//freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    n=read(),m=read();
    ll maxn=ceil(log2(n*1.0));
    ll res=0;
    for(ll i=1;i<=maxn;i++)
    {
    	for(ll j=1;j<=m;j++)
    	{
    		if(mp[i*j])continue;
    		mp[i*j]=1;
    		res++;
		}
		dp[i]=res;
	}
	for(ll i=2;i<=n;i++)book[i]=1;
    ll ans=1;
    for(ll i=2;i<=n;i++)
    {
    	if(!book[i])continue;
    	for(ll j=i;j<=n;j*=i)book[j]=0;
    	ll num=(log2(n*1.0)/log2(i*1.0));
		ans+=dp[num];
	}
	write(ans);
	return 0;
}
```



---

## 作者：intel_core (赞：6)

注意到第 $d,d^2,d^3,\cdots,d^k(k=\lfloor \log_d n\rfloor )$ 行可以一起考虑。

对所有第 $d,d^2,d^3,\cdots,d^k$ 行的数对 $d$ 取对数，不难发现贡献是 $1\times 1,1\times 2,\cdots,1\times m,\cdots,k\times 1,k\times 2,\cdots,k\times m$ 中不同数的个数。

上述贡献可以轻松 $O(m\log n)$ 轻松求出。

总复杂度 $O(m\log n+n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int NR=1e6+10;
int n,m,ans=1,a[30],vis[NR],now;
bool buc[NR*20]; 
unordered_map<int,int>mp;

signed main(){
	cin>>n>>m;
	for(int i=1;i<=20;i++){
		for(int j=1;j<=m;j++)now+=buc[i*j]^1,buc[i*j]=1;
		a[i]=now;
	}
	for(int i=2;i<=n;i++)
		if(!vis[i]){
			int x=i,cnt=0;
			while(x<=n)cnt++,vis[x]=1,x*=i;
			ans+=a[cnt];
		}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：A_Sunny_Day (赞：5)

# CF1646E Power Board

给一个复杂度与 $m$ 无关的做法。

考虑什么时候数字出现重复。

观察每一行。

发现当存在 $i,j$ 满足 $i,j\le n$ 且 $j=i^k$ 的时候第 $i$ 行和第 $j$ 行会出现重复的。

那么我们分段处理。

我们找到最小的 $i$ 满足不存在 $j$ 使得 $j^k=i$。

那么我们将 $i,i^2,\dots ,i^k$ 这几行的数放在一起处理。

注意到与这几行的包括数是 $i,i^2,\dots,i^m \cup i^2,i^4,\dots,i^{2m}\cup i^3,i^6,\dots i^{3m}\cup\dots$。

发现这些数中如果指数不一样那么数就不一样。所以我们只要把指数拿下来去重就行。

问题就变成：

$1,2,\dots ,m \cup2,4,\dots,2m\cup3,6,\dots,3m\cup\dots$ 

这些数中有多少个不重复的数。

发现是所有 $[1,k\times m]$ 中 $k$ 的倍数的并集。

我们可以大力容斥去做。

复杂度与 $m$ 无关，但是具体是多少我并不会证，输出了下次数大概是 $n\log n$ 级别的。（$10^6$ 跑了 $2\times10^7$ 次）。

~~所以这题的 $m$ 可以被强化到 $1e18$ 哩！~~

代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN = 1e6+5;
int n,m,lg[MAXN];
bool vis[MAXN];
ll gcd(ll x,ll y){return y==0?x:gcd(y,x%y);}
ll lcm(ll x,ll y){return x/gcd(x,y)*y;}
int main()
{
	for(int i=2;i<=1000000;++i) lg[i]=lg[i>>1]+1;
	scanf("%d %d",&n,&m);
	ll Ans=1;
	for(ll i=2;i<=n;++i)
	{
		if(vis[i]) continue;
		int siz=1;
		for(ll j=i*i;j<=n;j=j*i) vis[j]=1,++siz;
		for(int s=1;s<(1<<siz);++s)
		{
			int c=__builtin_popcount(s);
			ll g=lg[(s&(-s))]+1,v=1;
			for(int j=0;j<siz;++j) if((1<<j)&s) v=lcm(v,j+1);
			if(c&1) Ans+=g*m/v;
			else Ans-=g*m/v;
            //注意这里容斥的时候交集一定是在 1到最小的km 之间 
		}
	}
	printf("%lld\n",Ans);
	return 0;
}
```



---

## 作者：Nightingale_OI (赞：4)

## CF1646E Power Board

### 大意

有一个 $ n \times m  $ 的矩阵，第 $ i $ 行第 $ j $ 列上写着 $ i^j $ ，问矩阵中有多少个不同的数。

### 思路

首先，把第一行特殊处理。

我们把 $ i $ 分解为 $ j^k $ ，满足 $ j $ 最小。

发现对于不同的 $ i $ ，当且仅当 $ j $ 向等时该行才可能重。

对于相同的 $ j $ 的 $ k $ 组成的集合发现一定由 $ [1,log_{j}n] $ 中的整数组成。

对于 $ j $ 的可行 $ k $ 组成的集合，不重的数字个数仅与集合大小有关。

发现 $ log_{2}10^{6} < 20 $ ，也就是集合大小不超过 $ 19 $ ，可以逐个处理。

问题变成了对于 $ 1 \leq x \leq 19 $ ，求满足 $ 1 \leq y \leq x $ ， $ 1 \leq z \leq m $ ，不同的 $ y \times z $ 的数量。

开个数组暴力统计即可。

所以先枚举 $ j $ ，将其贡献累加即答案。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define f(i,j,k) for(register int i=j;i<=k;++i)
#define g(i,j,k) for(register int i=j;i>=k;--i)
int n,m,s,l;
long long ans;
int a[1010101];
int v[1010101];
int p[20202020];
int main(){
    cin>>n>>m;
    f(i,1,20){
        f(j,1,m)if(!p[i*j])l+=(p[i*j]=1);
        a[i]=l;
    }
    f(i,2,n)if(!v[i]){
        s=1;l=0;
        while(1ll*s*i<=1ll*n)l+=(v[s*=i]=1);
        ans+=a[l];
    }
    printf("%lld\n",ans+1);
    return 0;
}
```

---

## 作者：szh_AK_all (赞：3)

在决斗中通过了本题。

## 分析

首先可以将 $i^j$ 中的 $i$ 改为 $\prod p_k^{a_k}$ 的形式，其中 $p_k$ 皆为质数。那么 $i^j$ 便可以表示成 $\prod p_k^{a_k\times j}$ 的形式。

接下来考虑可能的与 $i^j$ 相同的数 $u^v$（这里钦定 $u>i$）。将 $u$ 改为 $\prod{q_l}^{b_l}$ 的形式，其中 $q_l$ 皆为质数，那么 $u^v$ 可以表示成 $\prod q_l^{b_l\times v}$ 的形式。因为 $i^j=u^v$，所以 $i,u$ 所包含的质因子是相同的。那么对于相同的 $p_k,q_l$，有 $a_k\times j=b_l\times v$，移项得到 $b_l=a_k\times \frac{j}{v}$。也就是说对于 $i,u$ 包含的相同的质因子，其指数的比例不变，也即 $u=i^{\frac{j}{v}}$。这启示我们与第 $i$ 行的数相同的数只可能出现在第 $i^w$ 行，其中 $w$ 为正整数。

最后就很好办了，令 $|s_i|$ 表示第 $i$ 行的数的集合，也就是 $i^1,i^2\dots i^m$，对于每个 $i$，我们需要求出所有满足 $r=i^k$ 的 $S_r$ 的交集大小，很显然可以用容斥来做。

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int vis[1000005];
int ans = 1, k, n, m;

void dfs(int x, int minn, int now, int sum) {
	if (x == k) {
		if (minn == 1e9)
			return;
		int z = (minn + 1) * m / now;
		if (sum % 2 == 1)
			ans += z;
		else
			ans -= z;
		return;
	}
	dfs(x + 1, min(minn, x), now / __gcd(now, x + 1) * (x + 1), sum + 1);
	dfs(x + 1, minn, now, sum);
}

signed main() {
	cin >> n >> m;
	for (int i = 2; i <= n; i++) {
		if (vis[i])
			continue;
		k = 0;
		for (int j = i; j <= n; j *= i) {
			k++;
			vis[j] = 1;
		}
		dfs(0, 1e9, 1, 0);
	}
	cout << ans;
}
```

---

## 作者：I_am_Accepted (赞：3)

### Preface

「这不是简单的数论题吗？」

「是啊。」

「那为啥这有一个↑↓明明会正解却没写出来……」

### Analysis

第一行单独算，直接判掉不再考虑。

设每行首个为**代表元**。由于 $2^{20}>10^6$，也就是说任意两个代表元 $x,y$ 有 $\log_xy<20$

设 $f(x)$ 为最小的正整数 $y$ 使得 $\log_y x\in\mathbb{N}$。我们称一些代表元为**一族**（元素周期表乱入），当且仅当她们的 $f$ 相同。显然单个族的大小不超过 $20$。

发现**不同族之间不可能有数相同**，我们将每个组分开考虑。

发现**只要族的大小相等，所含不同元素个数必然相同**，我们预处理出不同大小族对答案的贡献即可。

时间 $O(20m)$ 预处理 和 $O(n)$ 计算。

### Code

[Link](https://codeforces.com/contest/1646/submission/149199155)

---

## 作者：CYZZ (赞：3)

# [CF1646E](https://www.luogu.com.cn/problem/CF1646E)
题解区好像有和我一个做法的，不管了直接冲。
## 思路
发现第 $i$ 行可能与第 $i^k$ 行有重复的数。

所以只考虑不能被开根的 $i$（不存在 $k$ 使得 $\sqrt[k]{i} \in \mathbb{Z}$），在计算第 $i$ 行的时候把 $i^k$ 行的答案算完，即所有第 $i^k$ 行的数的并集大小。

注意到第 $i^k$ 行的数为 $\{ i^k,i^{2k},i^{3k},...,i^{mk} \}$。

令 $k=\lfloor \log_{i}{n} \rfloor$，则问题转化为求：

$$|\{ i,i^2,i^3,...,i^m \} \cup \{ i^2,i^4,i^6,...,i^{2m} \} \cup...\cup \{ i^k,i^{2k},i^{3k},...,i^{mk} \} |$$

即：
$$|\{ 1,2,3,...,m\} \cup \{ 2,4,6,...,2m \} \cup ... \cup \{ k,2k,3k,...,mk \}|$$

这不小学数学题吗（每次把编号为 $k$ 的倍数的灯打开），直接容斥即可，注意最后要乘选出的集合的最大值中的最小值（就是乘值域）。

时间复杂度带了两个鬼畜的 $\log_{i}{n}$，所以不会算。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,bk[1000005];
long long ans=1;
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=2;i<=n;i++)
    {
        if(bk[i])
            continue;
        int K=0,cnt=0;
        for(long long j=i;j<=n;j*=i)
        {
            bk[j]=1;
            K++;
        }
        for(int j=1;j<(1<<K);j++)
        {
            int sum=(__builtin_ctz(j)+1)*m,lcm=1;
            //sum 为 "选出的集合的最大值中的最小值"
            for(int k=1;k<=K;k++)
            {
                if((1<<k-1)&j)
                    lcm=k*lcm/__gcd(k,lcm);
            }
            cnt+=(__builtin_popcount(j)&1?1:-1)*(sum/lcm);
        }
        ans+=cnt;
    }
    printf("%lld",ans);
}
```

---

## 作者：Yusani_huh (赞：2)

给一个超级暴力做法。

定义两行是 **冲突** 的，当且仅当这两行在 $m\to\infty$ 时有重复元素。（定义严谨些，因为 $m$ 很小的时候冲突的两行不一定有重复元素）

考虑某一行 $i$，满足整个表中有且仅有另一行与它冲突，即 $\sqrt[3]{n} < i \le \sqrt{n}$ 。把这两行放在一起看，所有元素即为 $i^1,i^2,\cdots i^m,i^2,i^4,\cdots i^{2m}$，我们很容易看出这里面不同元素的个数就是 $m+\left\lceil\frac{m}{2}\right\rceil$（因为后面 $m$ 个元素只有一半是有贡献的）。

但是如果对于更小的 $i$，不太容易在 $O(1)$ 时间内计算所有跟 $i$ 冲突的行，如果同上面的过程你会发现有重复计算的，还可能有漏计算的。

既然三行及以上相互冲突的情况不好算，那我们索性暴力。发现这样的 $i \le \sqrt[3]{n}$，那么直接从 $1$ 枚举到 $\sqrt[3]{n}$，对于每一组互相冲突的行，开一个桶用于计数。然后对于大于 $\sqrt[3]{n}$ 的行，按一开始推的方法计算即可。

时间复杂度 $O(m\sqrt[3]{n}\log n+n)$，因为前面那一坨东西根本跑不满，所以能过。具体细节见代码。

```c++
#include<bits/stdc++.h>
using namespace std;
#define N 1000003
#define LL long long
#define INF 0x3f3f3f3f
LL n,m;
bool vis[N],b[N*32];
int main(){
    scanf("%lld%lld",&n,&m);
    LL res=1;
    int lim=pow(n,1.0/3)+0.5;
    LL i=2;
    for(;i<=lim;++i){  //前lim行直接枚举
        if(vis[i]) continue;
        LL nw=i;
        int cnt=1,ctt=0;
        while(nw<=n){
            vis[nw]=true;
            for(int j=1;j<=m;++j)
                if(!b[cnt*j]) b[cnt*j]=true,ctt++;
            nw*=i,cnt++;
        }
        nw=i,cnt=1;
        while(nw<=n){
            for(int j=1;j<=m;++j)
                b[cnt*j]=false;
            nw*=i,cnt++;
        }
        res+=ctt;
    }
    for(;i<=n;++i){  //后面的行公式计算
        if(vis[i]) continue;
        res+=m;
        if(i*i<=n) vis[i*i]=true,res+=(m+1)/2;
    }
    printf("%lld\n",res);
    return 0;
}
```

---

## 作者：houzhiyuan (赞：2)

先考虑哪些数可能会产生重复。

对于第 $x$ 行，显然只有第 $x^2,x^3...x^k$ 行上的数可能与它有重复。

考虑去计算这个东西，设 $f_k$ 表示对应的答案。

问题转化为 $i\in [1,k],j\in [1,m]$，求 $ij$ 有多少个不同的取值。

由于 $k$ 是 $\log n$ 级别的，可以直接暴力枚举，然后枚举 $x$ 就做完了。

时间复杂度 $O(m\log n+n)$。

---

## 作者：Lemon_zqp (赞：1)

### 锐评
这题感觉完全没有蓝吧……
### 思路
我们先观察矩阵：

$\begin{matrix}
 1 & 1 & 1 ... & 1^m\\
 2 & 4 & 8 ... & 2^m\\
 3 & 9 & 27 ... & 3^m\\
 4 & 16 & 64 ... & 4^m\\
 n & n^2 & n^3... & n^m
\end{matrix}
$

假如我们把底数相同的都提取出来（因为两个数底数不同肯定是不同的数，无论幂次是几都不会相等）：

$\begin{matrix}
 2 & 2^2 & 2^3 ... & 2^m\\
 3 & 3^2 & 3^3 ... & 3^m\\
 4 & 4^2 & 4^3 ... & 4^m
\end{matrix}$

等价于：

$\begin{matrix}
 2 & 2^2 & 2^3 ... & 2^m\\
 2^2 & 2^4 & 2^6 ... & 2^{2m}\\
 2^3 & 2^6 & 2^9 ... & 2^{3m}
\end{matrix}$

#### 预处理

假如我们预处理前几行，有多少个不同的数，我们发现，底数不同时这个预处理的答案是通用的。

#### 如何预处理

你需要预处理出一个数组，$cnt_i$ 表示前 $i$ 个底数相同的行的答案。

#### 如何统计答案
我们可以从小到达遍历每一个底数 $a$：
- 假如 $a$ 没用过，那么统计有多少个以 $a$ 为底的行，设为 $cntt$，（并把这些底数标记为用过，如 $a^2$、$a^3$）那么答案就是这些行的总数对应的预处理出的答案，也就是 $cnt_{cntt}$。
- $a$ 用过，跳过。

### 代码
```
#include<bits/stdc++.h>
#define int long long
using namespace std;

bool used[20000005], vis[20000005];
int cnt[20000005];

long long poww(int a, int b){
	long long ans = 1;
	for(int i = 1; i <= b; i++){
		ans *= a;
	}
	return ans;
} 

signed main(){
	int sum = 0, ans = 1;
	int n, m;
	cin >> n >> m;
	for(int i = 1; i <= 20; i++){//预处理
		for(int j = 1; j <= m; j++){
			if(used[i * j] == false){
				sum++;
				used[i * j] = true;
			}
		}
		cnt[i] = sum;
	}
	for(int i = 2; i <= n; i++){
		int cntt = 0;
		if(vis[i] == false){
			for(int j = 1; poww(i, j) <= n; j++){
				cntt++;
				vis[poww(i, j)] = true;
			}
			ans += cnt[cntt];
		}
	}
	cout << ans;
    return 0;
}

```
[AC记录](https://www.luogu.com.cn/record/138100126)

---

## 作者：QQ82272760 (赞：1)

~~因为我太菜了，所以小题大做了。~~

考虑行 $j$ 会把行 $i$ 部分覆盖（$i<j$），如果存在一个**最小**的 $x$ 使得 $i=x^a,j=x^b$，那么行 $i$ 有且仅有满足 $\dfrac{b}{\gcd(a,b)}k\,(k\in\mathbb N)$ 的位置都会被覆盖。对于第 $i$ 行，$x,a$ 是确定的，所以要先用 $\mathcal O(\log n)$ 找出所有 $b$，再用 $\mathcal O(\log\log n)$ 求出 $d=\dfrac{b}{\gcd(a,b)}$。根据容斥原理，对于**没有**被覆盖位置数，奇数个 $d$ 的贡献是 $-\dfrac{m}{\rm lcm}$，偶数个 $d$ 的贡献是 $\dfrac{m}{\rm lcm}$，可以把所有可能的 $d$ 的集合的总贡献进行预处理，通过 `FWT` 优化高维前缀和，最终复杂度是 $\mathcal O(n\log n\log\log n+n\log n)$。

```cpp
#include<iostream>
#include<cstdio>
#define ll long long
using namespace std;
int c[1<<20],vi[1000005];
int gcd(int x,int y){
	return y?gcd(y,x%y):x;
}
void FWT(int n){
	for(int i=1;i<n;i<<=1){
		for(int j=0;j<n;j+=(i<<1)){
			for(int k=j;k<i+j;k+=1){
				c[k+i]+=c[k];
			}
		}
	}
	return;
}
void init(int n,int m){
	for(int i=0;i<(1<<n);i+=1){
		int now=1,pc=0;
		for(int j=0;j<n;j+=1){
			if(i>>j&1){
				now/=gcd(now,j+1);
				if(now>m/(j+1)){
					pc=-1; break;
				}
				now*=(j+1); pc+=1;
			}
		}
		if(~pc){
			if(pc&1) c[i]=-m/now;
			else c[i]=m/now;
		}
	}
	FWT(1<<20);
	return;
}
int main(){
	int n,m; ll ans=1;
	scanf("%d%d",&n,&m); init(20,m);
	for(int i=2,j;i<=n;i+=1){
		if(vi[i]) continue;
		j=1;
		for(int k=i;k<=n/i;){
			k*=i; vi[k]=1; j+=1;
		}
		for(int k=1;k<=j;k+=1){
			int s=0;
			for(int l=k+1;l<=j;l+=1){
				s|=(1<<(l/gcd(l,k)-1));
			}
			ans+=1ll*c[s];
		}
	}
	printf("%lld\n",ans);
	return 0;
}
```

Thanks~

---

## 作者：Duramente (赞：1)

[传送门](https://codeforces.com/contest/1646/problem/E)  

## 题意  
给一个 $n\times m$ 的矩阵，矩阵的 $(i,j)$ 位置的数为 $i^j$。  
求总共有多少个不同的数。  
$n,m\leq 10^6$  

## Solution  
首先第一行全是 1，最为特殊，特判掉。  
来考虑一下哪些行会造成重复。  当 $i$ 能表示成 $x^k$ 且 $k>1$ 的时候，才会发生重复。  
当前面有 $i'$ 能表示为 $x^{k'}$ 的时候，在 $j\times k=j'\times k'$ 的时候，就会发生重复。  
因此我们预处理哪些数可以表示为次幂数，并求出是多少次幂。其次我们发现 $x$ 是多少并不影响重复的数量，于是都当作 $2$ 来做，用筛法筛一遍即可。  

## Code  
```cpp
#include<bits/stdc++.h>
#define forn(i,a,b)for(int i=(a),_b=(b);i<=_b;i++)
#define fore(i,b,a)for(int i=(b),_a=(a);i>=_a;i--)
#define rep(i,n)for(int i=0,_n=n;i<n;i++)
#define ll long long
#define pii pair<int,int>
#define m_p make_pair
#define pb push_back
#define fi first
#define se second
#define int ll
#define foreach(i,c) for(__typeof(c.begin())i=(c.begin());i!=(c).end();i++)
using namespace std;
const int N=1000010;
int n,m;
int b[N];
int r[33];
bool used[N*25];
signed main(){
   cin.tie(0);
	ios::sync_with_stdio(0);
	forn(i,2,1002){
		if(b[i])continue;
		int cnt=1;
		for(int j=i*i;j<=1000500ll;j*=i){
			b[j]=++cnt;
		}
	}
	cin>>n>>m;
	forn(j,1,m)used[j]=1;
	forn(i,2,20){
		r[i]=m;
		forn(j,1,m){
			if(used[j*i]){
				r[i]--;	
			}
			else{
				used[j*i]=1;
			}
		}
	}
	int ans=1; 
	forn(i,2,n){
		if(!b[i])ans+=m;
		else{
			ans+=r[b[i]];
		}
	}
	cout<<ans<<"\n";
	return 0;
}

---

## 作者：Priestess_SLG (赞：0)

简单题，~~但是没想出来~~

考虑对于每一个不为 $1$ 的数 $i$，若其之前没有访问过，则将所有 $i^k$ 全部标记，并将所有底数为 $i^k$ 的数全部列出。可以将底数全部改为 $i$ 然后同样的修改指数的值。问题变为计算有多少本质不同的二元数对 $(i,j)$ 同时满足下列条件：

+ $1\le i\le k$（$k$ 是最大的正整数满足 $i^k\le n$）
+ $1\le j\le m$

这里定义两个二元数对 $(i,j)$ 和 $(i',j')$ 本质不同当且仅当 $ij\neq i'j'$。即计数有多少个不同的整数 $ij$。因为 $j$ 的上界一直都是定值 $m$，而 $i$ 的上界为 $\log n$ 级别约等于 $20$，所以这个直接随便暴力预处理一下即可。

```cpp
int buc[32];
unsigned char mp[20000100], vis[2000100];
void run() {
    int n = read(), m = read();
    int s = 1, tot = 0;
    for (int i = 1; i <= 20; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (!mp[i * j]) ++tot;
            mp[i * j] = 1;
        }
        buc[i] = tot;
    }
    for (int i = 2; i <= n; ++i) {
        if (!vis[i]) {
            int j = i, pw = 0;
            while (j <= n) {
                ++pw;
                vis[j] = 1;
                j *= i;
            }
            s += buc[pw];
        }
    }
    cout << s << '\n';
}
```

---

## 作者：刘梓轩2010 (赞：0)

题目传送门：[Codeforces](https://codeforces.com/problemset/problem/1646/E)

[Luogu](https://www.luogu.com.cn/problem/CF1646E)

## 题意

给你一个矩阵，第 $i$ 行第 $j$ 列写着 $i^j$，问矩阵中有多少不同的数。

## 思路

首先我们可以发现，出现了多少数与指数密切相关，那么考虑第 $d$ 行，我们令 $d$ 在之前都没有出现过（$d \neq 1$），那么我们可以将第 $d$ 行，第 $d^2$ 行，第 $d^3$ 行一直到最大的小于 $n$ 的第 $d^k$ 行单独提取出来看，我们发现出现的数的数量只取决于指数，而且发现提取出来的矩阵的第 $i$ 行第 $j$ 列的数的指数为 $i \times j$。

综合考虑，我们还发现，这个规律对于任何的底数都成立，于是在统计答案时把当前统计到的行打标记，在下一次遍历到的时候避免重复统计即可。

对于提取出来的矩阵，我们发现最多只有 $\log_{2}{n}$ 行，既然对于每个底数答案不变，那么我们可以预处理出来对于提取出来的前 $i$ 行的答案。

复杂度 $O(n \log n)$。

不理解可以结合代码食用。

## 代码

```cpp
#include <bits/stdc++.h>
#define endl '\n'
#define int long long
#define fi first
#define se second
using namespace std;
const int N=1e6+10;
const int inf=0x3f3f3f3f;
int n,m;
int sum;
bool vis[N],us[N*20];//vis: 这一行有没有被统计过 ; us:这个指数有没有出现过 
int cnt[40];//前i行的答案 
int ans=1;//第一行不用统计,直接是1 
signed main()
{
	cin.tie(0);
	cout.tie(0);
	ios::sync_with_stdio(false);
	cin>>n>>m;
	for(int i=1;i<=20;i++)
	{
	    for(int j=1;j<=m;j++)
        {
            if(!us[i*j]) 
            {
                sum++;   //sum从0开始,统计前i行的答案 
                us[i*j]=1;
            }
        }
        cnt[i]=sum;
    }
    for(int i=2;i<=n;i++)
    {
        if(!vis[i])  //如果这一行没被统计过,那么统计 
        {
            int p=i;
            int cur=0;
            while(p<=n)
            {
                cur++;
                vis[p]=1;
                p*=i;
            }
            ans+=cnt[cur];
        }
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：大眼仔Happy (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1646E)

我们具体分析这个图：

![](data:image/png;base64,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)

若排除掉比较特殊的第 $1$ 行之后，容易发现，当且仅当第 $x^a$ 行和第 $x^b$ 行会有重复数字，如第 $2$ 行和第 $4$ 行就有重复，而第 $2$ 行和第 $6$ 行就没有（原因就是 $6^x$ 还有 $3$ 的约数）

将有相同的数的行写成 $a^x$ 的形式，再看看？

![](data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAASEAAAAlCAYAAAAN+1+5AAAAAXNSR0IArs4c6QAAAARnQU1BAACxjwv8YQUAAAAJcEhZcwAADsMAAA7DAcdvqGQAAAO6SURBVHhe7ZkBigMhDEV7/xv0Xr1Pl5QVQojRMWMS2/8gbNfOt0/FsHQfz+fzjUKhUFn1aUIn83q9/l+dCfxzgX8u5I8mlAz8c4F/LuSPJpQM/HOBfy7kX6IJPR6PT61Q4RDgnwv8c/H6pzchLr+ykOxDgD/8PcA/oAmRGK8VrNzuQ/D6j/Lwtxl9/hVO85fZVpwT9t/Kkv/WJqR98JWFNHkrs/MQ7vCXyDH49/H6cyinZU/bf0n1/efPa1nyL92EGlYGl7jPr/tzKKdlT9t/yTf4h38ndGURDSuz8xA0Vvw5Mn+Sv5Y9wb9lTvOnZ2VJqvu3n5Z/aBO6sgCOlYs8hFX/Ru8QovDsfy9b3Z9ntHxlf+15OVbdX2Y0/7AmdHUBHCsbdQgef6KXP8Wf0Oao7C8zp/lryHlO2n9C8w9pQt4DsPIRh/Dr/hw5V2V/yvWqgf0fs+qv5TT/7U3ojgOw5th9CF7/Ub6yv5aVY9X3n6PNhf23ifDf2oRmJGawMjsPwes/k4d/H6+/RMti//t4/Qn5vOa/vQlpNctMdvchaDWLlqXiVPYnRtnq/oSVx/73kZ/d6ipWlvzDvpjexc5DiAD+ucA/F/JHE0oG/rnAPxfy/zQheoFCoVAZhb+EkoF/LvDPhfzRhJKBfy7wz4X80YSSgX8u8M+F/Es0odV//REVDgH+uVT39/iN+Ab/9CbEF7ey0OxLAH/4W3j9RnyD//YmROK8rjLKRxyC9flXONXfylb3H+W9/qP5ZxjlrLmr+4/mJ/+tTUj7UG2sx0x+5yXw+nMop2Wr+/PnT/OfyXv87/Br1YO/pz1X2X9mfvJHEzLw+nMop2VPu8SS0/zlWOYlbvQyv+If/p3QyiI52iIiWfFvGS1b2Z97t5Kc4M+RY3f7X/Fr9DKn+2to/qFNaGWBHC0feQm8B3SaPz0vM/L3E/afl+RO/xU/opfTxuVYZX+J9hz5hzWh1QU2evmoS7DiLzO9Q4jgDn9CjlX2J3hOm+Mu/1U/opfVxuVYZX9O7xnyD2lCngUSVj7iEqz6U65Xjer+EjkG/3W/Ri9/un/Dep/8tzeh3QvcfQm8/hxtrsr+WlaO/bq/x6/Rm+N0f2I0P/lvbUIzm2gxk995Cbz+Ei1b3V8+L3+v7D+T9/h7/RpWhr+nPVfZf2Z+8t/ehLSaRctScXZfAq2uYuVP85dU9x9lvZdYq1lms9Z7lf2196k45B/2xfQudl6CCOCfC/xzIX80oWTgnwv8cyH/TxOiFygUChVfr/cfTy5winIlsYcAAAAASUVORK5CYII=)

只看指数，是不是就很显然了。而这种情况下，相同的数一定意味着相同的指数，所以我们只需要讨论指数即可。

那么我们需要如何计算这个东西呢？可以发现这玩意最多只有 $\log n\approx 20$ 行，而每行只有 $m$ 个，所以直接暴力就好啦。做完一个之后，要给其他的打上标记防止再被算一次。

视 $n,m$ 同阶，时间复杂度就是 $O(n\log n)$。

------------

你说的对，但是我分别用

```cpp
int t=log(n)/log(i);
```

```cpp
int t=log2(n)/log2(i);
```

而前者 WA 了，但是后者却 AC 了。

所以建议不用：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
#define ll long long
ll inline read()
{
	ll num=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){num=(num<<3)+(num<<1)+(ch^48);ch=getchar();}
	return num*f;
}
int n,m,buc[N*20];bool vis[N];
ll sum[25],ans=1;
int main(){
	n=read();m=read();
	for(int i=1;i<=20;i++)
	{
		sum[i]=sum[i-1];
		for(int j=1;j<=m;j++)buc[j*i]++,sum[i]+=(buc[j*i]==1);
	}
	for(int i=2,t=0;i<=n;i++)
	{
		if(vis[i])continue;
		for(ll j=1ll*i*i;j<=n;j*=i)vis[j]=1,t++;
		ans+=sum[t+1];t=0;
	}
	printf("%lld",ans);
	return 0;
}
```

---

