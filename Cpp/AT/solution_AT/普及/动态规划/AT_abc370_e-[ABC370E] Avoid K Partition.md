# [ABC370E] Avoid K Partition

## 题目描述

给出长度为 $N$ 的序列 $A=(A_1,A_2,\dots,A_N)$ 以及一个整数 $K$。

存在 $2^{N-1}$ 种方法将 $A$ 分成若干个连续子区间。有多少划分方法满足没有任何一个划分出的子区间元素和为 $K$？请输出这个值模 $998244353$ 的结果。

这里，“将 $A$ 分成若干个连续子区间”的含义如下：

- 随意选择一个整数 $k\space 1\le k\le N$ 作为序列长度，并且随意选择一个满足条件 $1=i_1<i_2<\dots<i_k<i_{k+1}=N+1$ 的整数序列 $(i_1,i_2,\dots,i_k,i_{k+1})$。
- 对于每个满足 $1\le n\le k$ 的整数 $n$，第 $n$ 个被划分出来的子区间是由提取序列 $A$ 中的第 $i_n$ 到第 $(i_{n+1}-1)$ 个元素得到的。

举个例子，以下是序列 $A=(1,2,3,4,5)$ 的若干可行划分方案：

- $(1,2,3),(4),(5)$
- $(1,2),(3,4,5)$
- $(1,2,3,4,5)$

## 说明/提示

- $1 \leq N \leq 2 \times 10^5$
- $-10^{15} \leq K \leq 10^{15}$
- $-10^9 \leq A_i \leq 10^9$
- 全部输入为整数

#### 对样例 1 的解释

以下是符合题目要求的 $2$ 种划分方案。

- $(1),(2,3)$
- $(1,2,3)$

Author: [Redshift_Shine](/user/475403)

## 样例 #1

### 输入

```
3 3
1 2 3```

### 输出

```
2```

## 样例 #2

### 输入

```
5 0
0 0 0 0 0```

### 输出

```
0```

## 样例 #3

### 输入

```
10 5
-5 -1 -7 6 -6 -2 -5 10 2 -10```

### 输出

```
428```

# 题解

## 作者：沉石鱼惊旋 (赞：9)

# 题目翻译

给定长度为 $n$ 的序列 $a$，求有多少种划分方式（不可划分出空段）使得 $a$ 可以被分成若干个段，每段之和都 $\neq k$。

对于划分的具体定义：选定 $1=i_1\lt i_2\lt  \dots\lt i_k\lt i_{k+1}=n+1$。分成 $[i_p,i_{p+1})$ 共 $k$ 个小段。显然你一共有 $2^{n-1}$ 种划分方案。

答案对 $998244353$ 取模。

$1 \leq n \leq 2 \times 10^5$，$-10^{15} \leq k \leq 10^{15}$，$-10^9 \leq A_i \leq 10^9$。

# 题目思路

设 $f_{i}$ 表示第 $i$ 个位置作为结尾的合法方案数。

$f_i$ 可以从 $f_j(j\lt i)$ 转移过来。绝大多数 $f_j$ 都可以顺利转移。考虑那些不能顺利转移的。

不能顺利转移说明存在 $s_i-s_j=k$ 的情况。$s_i$ 表示前缀和。

那么我们找到那些满足 $s_j=s_i-k$ 的位置，排除掉即可。

这样做仍然不好做，考虑改变状态设计，我们状态可以不和 $i$ 有关，直接和 $s_i$ 有关。

$g_{s_i}$ 表示前缀和为 $s_i$ 的方案数。

那么 $f_i\gets (\sum g) - g_{s_i-k}$。也就是全集扣除 $g_{s_i-k}$。更新了 $f$ 之后更新这一位相关的 $g$，也就是 $g_{s_i}\gets g_{s_i}+f_i$。

那么我们直接维护全局的 $g_{s_i}$ 的总数记为 $tot$。这个 $tot$ 的更新是 $\mathcal O(1)$ 的。每次根据 $tot$ 和 $g_{s_i-k}$ 算出这里的 $f_i$。

由于前缀和范围很大所以可以使用 `std::map` 等 STL 容器映射。

# 部分代码

[AT submission 57560977](https://atcoder.jp/contests/abc370/submissions/57560977)

忽略了 mod_int 的实现。

```cpp
using Z = mod_int<998244353>;
map<ll, Z> mp;
ll sum;
Z tot;
int n;
ll k;
int main()
{
    cin >> n >> k;
    mp[0] = 1;
    tot = 1;
    for (int i = 1; i <= n; i++)
    {
        ll x;
        cin >> x;
        sum += x;
        Z add = tot - (mp.count(sum - k) ? mp[sum - k] : 0);
        mp[sum] += add;
        tot += add;
        if (i == n)
            return cout << add << endl, 0;
    }
    return 0;
}
```

---

## 作者：_determination_ (赞：6)

好的如你所见，这道题你一眼秒了一个简单 dp：

$$
f_x=\sum_{i=1}^{x}[\sum_{j=i}^{x}a_j \neq k]f_{i-1}
$$
其中 $f_0=1$，答案为 $f_n$。$f_x$ 的含义是将前 $x$ 个数分段的合法方案数。

考虑优化。你注意到除了那个判断其他都很好搞，考虑怎么判断。对于每个 $\sum_{j=i}^{x}$ 我们动态维护。问题等价于给你一堆二元组，要求你实现以下操作：

1. 将所有二元组的第一项增加 $x$。
2. 加入一个二元组 $(x,y)$。
3. 查询集合中第一项为 $k$ 的二元组的第二项的和。

好的如果你是一个聪明的读者，你应该已经秒了一个打 tag 做法，但是如果你像我一样学数据结构学傻了你就会得到一个平衡树做法。

```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
using namespace std;
const int mod=998244353,inf=0x3f3f3f3f3f3f3f3f;
mt19937 rnd(time(0));
struct node{
	int ls,rs,suma,f,sumf,siz,tag,key;
}t[200010];
int root,tot;
int new_node(int f)
{
	tot++;
	t[tot].ls=t[tot].rs=0;
	t[tot].suma=t[tot].tag=0;
	t[tot].f=t[tot].sumf=f;
	t[tot].siz=1;
	t[tot].key=rnd();
	return tot;
}
void pu(int x)
{
	t[x].siz=t[t[x].ls].siz+t[t[x].rs].siz+1;
	t[x].sumf=t[t[x].ls].sumf+t[t[x].rs].sumf+t[x].f;
}
void pd(int x)
{
	if(t[x].tag==0)return;
	int tag=t[x].tag;
	t[x].tag=0;
	t[t[x].ls].suma+=tag;
	t[t[x].rs].suma+=tag;
	t[t[x].ls].tag+=tag;
	t[t[x].rs].tag+=tag;
}
void split_suma(int x,int v,int &l,int &r)
{
	if(!x)return l=r=0,void();
	pd(x);
	if(t[x].suma<=v)
	{
		l=x;
		split_suma(t[x].rs,v,t[x].rs,r);
	}else{
		r=x;
		split_suma(t[x].ls,v,l,t[x].ls);
	}
	pu(x);
}
int merge(int l,int r)
{
	if(!l||!r)return l+r;
	if(t[l].key<t[r].key)
	{
		pd(l);
		t[l].rs=merge(t[l].rs,r);
		pu(l);
		return l;
	}else{
		pd(r);
		t[r].ls=merge(l,t[r].ls);
		pu(r);
		return r;
	}
}
int f[200010],a[200010];
int n,k;
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin >> n >>k;
	for ( int i = 1 ; i <= n ; i++ )cin >> a[i];
//	f[0]=1;
//	for ( int i = 1 ; i <= n ; i++ )
//	{
//		int sum=0;
//		for ( int j = i ; j >= 1 ; j-- )
//		{
//			sum+=a[j];
//			if(sum!=k)f[i]+=f[j-1];
//		}
//	}
//	cout << f[n];
	root=new_node(1);
	for ( int i = 1 ; i <= n ; i++ )
	{
		t[root].tag+=a[i];
		t[root].suma+=a[i];
		int L,R,M;
		split_suma(root,k,L,R);
		split_suma(L,k-1,L,M);
		f[i]=t[L].sumf+t[R].sumf; 
		f[i]%=mod;
		root=merge(merge(L,M),R);
		split_suma(root,0,L,R);
		root=merge(merge(L,new_node(f[i])),R);
	}
	cout << f[n];
	return 0;
}
```

---

## 作者：osfly (赞：5)

### something interesting

赛时在 D 卡了好久，dsu 没调出来开了 E 然后一眼了。

早知道就早点开 E 了。

/fn

### 正文

考虑 dp。

设 $dp_i$ 为考虑前 $i$ 个数且前 $i$ 个数划分出来后每个子段和都小于 $k$ 的方案数。

这个很好转移：$dp_n=\sum\limits^n_{i=1}dp_{j-1}\times[\sum\limits^n_{j=i}a_j\not=k]$

其中，当命题 $a$ 为真 $[a]=1$，否则 $[a]=0$。

发现中括号里的可以用前缀和快速判断，但是直接转移是 $O(n^2)$ 的，考虑优化。

注意到转移的条件仅与前缀和有关，我们可以用 `unordered_map` 来记录每一个前缀和对应的 $dp$ 值的和是多少。

具体的，令 $mp$ 为一个 `unordered_map`，$mp_x$ 记录的是到目前为止前缀和为 $x$ 的 $dp$ 值的和。

那么求和部分可以改写为：$dp_n=(\sum\limits^n_{i=1}dp_i)-mp_{pre_i}$

这样就可以 $O(n)$ 转移了。

注意边界问题和初始化。

代码很短。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define ll long long

const int N=1e6+10;
const ll mod=998244353;

int n;
ll k,a[N],pre[N];

ll dp[N],sum;

unordered_map<ll,ll> mp;

int main()
{
	scanf("%d%lld",&n,&k);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]),pre[i]=pre[i-1]+a[i];
	dp[0]=sum=mp[0]=1;
	for(int i=1;i<=n;i++)
		dp[i]=(((sum-mp[pre[i]-k])%mod)+mod)%mod,sum=(sum+dp[i])%mod,mp[pre[i]]+=dp[i];
	printf("%lld",dp[n]);
	return 0;
}
```

---

## 作者：LaDeX (赞：5)

题意简述：

> 给定数列 $\{a_n\}$，请问有多少种方法可以将该数列划分为若干个段且每段之和都不等于 $K$。

DP 题，定义状态 $f_i$ 表示第 $i$ 个及以前的数已经划分完且第 $i$ 个数为最后一段结尾的方案数。并且初始化 $f_0=1$。

考虑暴力 DP，记 $S(n)$ 表示第 $1$ 个数到第 $n$ 个数之和，有：

$$f_i=\sum_{j=1}^i f_{j-1}[S(i)-S(j-1)\neq K].$$

变换一下，容斥原理减去其补集可得：

$$
\begin{aligned}
f_i&=\sum_{j=1}^i f_{j-1} - \sum_{j=1}^i f_{j-1}[S(i)-S(j-1)=K]\\
&=\sum_{j=0}^{i-1} f_{j-1} - \sum_{j=0}^{i-1} f_{j}[S(j)=S(i)-K].
\end{aligned}
$$

显然状态转移方程中前一项可以在 DP 枚举的同时求出，后者可以记录一个数组 $P$，$P_i$ 表示处理到当前位置时，所有已经处理过的 $j$ 中 $S_j=i$ 的 $f_j$ 之和。则有：

$$f_i=\sum_{j=0}^{i-1} f_{j-1} - P_{S_i-K}.$$

每次处理完一个数更新一下 $P$ 数组即可。

由于数极大，使用 `map` 记录 $P$ 数组。

DP 方程时间复杂度 $O(n)$，STL 的时间复杂度 $O(\log n)$，总时间复杂度为 $O(n\log n)$。

---

## 作者：StayAlone (赞：2)

## 题意

给定一个长度为 $n$ 的序列 $a$，要将其分成若干个连续子段。一个方案是合法的，当且仅当不存在一个子段的和为 $k$。求合法方案数。

## 思路

考虑 dp。

设 $f_i$ 表示序列前 $i$ 项的合法分割方案数，$sum_i=\sum\limits_{j=1}^i a_j$。

有初值 $f_0=1$。

很容易写出方程：$f_i=\sum\limits_{sum_i-sum_{j} \ne k} f_j$，直接做是 $\mathcal O(n^2)$ 的。发现 $j$ 的合法性只与其 $sum_{j}$ 有关，那么就能用 map 优化。

具体的，用整体减去不合法的地方。实时维护 $s = \sum\limits_{j=0}^{i-1} f_j$，$cnt_v = \sum\limits_{j \in[0, i) \land sum_j=v}$，则 $f_i=s-cnt_{sum_i - k}$。

时间复杂度 $\mathcal O(n\log n)$。

```cpp
int n, a[MAXN]; ll k, sum, f[MAXN];
const int mod = 998244353;
map <ll, ll> cnt;

int main() {
	read(n, k); rer(i, 1, n, a);
	ll s = cnt[0] = f[0] = 1;
	rep1(i, 1, n) {
		(f[i] = s - cnt[(sum += a[i]) - k] + mod) %= mod;
		(cnt[sum] += f[i]) %= mod; (s += f[i]) %= mod;
	} printf("%lld", f[n]);
	return 0;
}
```

---

## 作者：DWBbobo (赞：2)

### 思路

可以非常快地想到一个 $\mathrm{O} (n ^ 2)$ 的朴素 DP 做法。

$f[i]$ 表示在 $i$ 点分割时的总可行方案数。

设
$$
S_i = \sum_{j=1}^{i} A_j
$$

状态转移方程：

$$
f[i] = \sum_{1 \leq j \lt i} \left(0\text{ if }S_i - S_{j - 1} = K \text{ else } f[j - 1] \right)
$$

$\mathrm{O} (n ^ 2)$ 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

int n;
long long k;
long long a[200011],s[200011],f[200011];

int main() {
	scanf("%d",&n);
	scanf("%lld",&k);
	for(int i=1;i<=n;i++)
		scanf("%lld",&a[i]);
	for(int i=1;i<=n;i++)
		s[i] = s[i - 1] + a[i];
	f[0] = 1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=i;j++)
			if (s[i] - s[j - 1] != k)
				f[i] = (f[i] + f[j - 1]) % 998244353;
	printf("%lld",f[n]);
    return 0;
}
```
但是这么写会 TLE 。

稍加思考，可以上面的式子可以简化为：

$$
f[i] = \sum_{1 \leq j \lt i, S_{j - 1} \neq S_{i} - K} f[j - 1]
$$

只要统计 $$ \sum_{j=0}^{i - 1} f[j] $$ 的值，再减去 $S_{j - 1} = S_i - K$ 时 $ f[j - 1] $的总和，就是$f[i]$ 的值！

查询 $S_{j - 1} = S_i - K$ 时 $ f[j - 1] $的总和 可以用 STL 提供的 map 来维护。

优化后的时间复杂度约为 $\mathrm{O}(n \log n)$。

### CODE


```cpp
#include <bits/stdc++.h>
using namespace std;

int n;
long long k,sum;
map <long long,long long> m;
long long a[200011],s[200011],f[200011];

int main() {
	scanf("%d",&n);
	scanf("%lld",&k);
	for(int i=1;i<=n;i++)
		scanf("%lld",&a[i]);
	for(int i=1;i<=n;i++)
		s[i] = s[i - 1] + a[i];
    m[0] = 1;
    sum = 1;
	for(int i=1;i<=n;i++) {
        f[i] = (f[i] + sum - m[s[i] - k]) % 998244353;
        m[s[i]] += f[i];
        sum += f[i];
    }
	printf("%lld",f[n]);
    return 0;
}
```

---

## 作者：zzhbpyy (赞：1)

### [E - Avoid K Partition](https://atcoder.jp/contests/abc370/tasks/abc370_e)

## 分析

考虑动态规划。$dp_i$ 表示前 $i$ 个数分成几个和不为 $k$ 的子段的方案数，$m_x$ 表示当前所有前缀和为 $x$ 的前缀的分割方案数之和，$s$ 表示前缀和数组。容易得到转移方程：

$$dp_i=-m_{s_i-k}+\sum_{j=1}^{i-1}dp_j$$

其中后一项可以边转移边维护，前一项用 `unordered_map` 储存，复杂度 $O(N)$。

## Code

```c++
#include<bits/stdc++.h>
#define int long long
#define mod 998244353
using namespace std;
int n,k,a[200005],s[200005],ss[200005];
unordered_map<int,int>m;
signed main(){
	ios::sync_with_stdio(0),cin.tie(nullptr);
	cin>>n>>k;int lst=0;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		s[i]=s[i-1]+a[i];
		ss[i]=lst+(s[i]!=k);
		(ss[i]-=m[s[i]-k])%=mod;
		(m[s[i]]+=ss[i])%=mod;//ss就是dp数组
		(lst+=ss[i])%=mod;
	}
	cout<<(ss[n]%mod+mod)%mod;
}
```

---

## 作者：a_sad_soul (赞：1)

## E.Avoid K Partition

简述题意：将一个数列分成若干个连续段，使得每段的和都不等于 $K$，求方案数，注意对 $998244353$ 取模。

设 $f_i$ 为以第 $i$ 个数为结尾分成子段的合法方案数，容易得到方程：

$$\large f_i=[a_i \ne K]+\sum\limits_{j=1}^{i-1}{[sum_i-sum_{j-1}\ne K]\times f_j}$$

这里 $sum_i$ 为数列 $a$ 的前缀和。

对 $sum_i-sum_{j-1}\ne K$ 移项得到 $sum_{j-1}\ne sum_i-K$

那么可以开一个哈希表存 $sum_i$ 的方案数然后记录前缀方案数最后减掉不符合答案的方案即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
const long long MOD = 998244353;
unordered_map<long long ,long long >vis;
long long n,k,sum;
long long g[500005],f[500005];
int main(){
	cin>>n>>k;
	f[0]=1;vis[0]=1;sum=1;
	for(int i=1;i<=n;++i){
		scanf("%lld",&g[i]);
		g[i]=g[i-1]+g[i];
	}
	for(int i=1;i<=n;++i){
		f[i]=(sum-vis[g[i]-k]+MOD+f[i])%MOD;
		vis[g[i]]=(vis[g[i]]+f[i])%MOD;
		sum=(sum+f[i])%MOD;
	}
	cout<<f[n]<<endl;
	return 0;
}
```

---

## 作者：zjc5 (赞：0)

[题目链接](https://www.luogu.com.cn/problem/AT_abc370_e)

**思路：**

设 $f_i$ 表示前 $i$ 个数的答案。若不考虑不合法情况，显然 $f_i=\sum\limits_{j=1}^{i-1}f_j+1$。

但是如果出现 $s_i-k=s_j$（$s$ 表示前缀和），则 $f_i$ 不能从 $f_j$ 转移过来。

所以 $f_i$ 是否转移与 $s_i$ 有关。可以用 map 储存每个 $s$ 对应的 $f_i$ 的和，转移时减去。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=200010;
int n,k,a[N],s,s2,f[N],mod=998244353;
map<int,int>mp;
signed main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		s+=a[i];
		f[i]=((s!=k)+s2-mp[s-k]+mod)%mod;
		s2=(s2+f[i])%mod;
		mp[s]=(mp[s]+f[i])%mod;
	}
	cout<<f[n];
	return 0;
} 
```

---

## 作者：yinpeichu2021 (赞：0)

[题目链接](https://www.luogu.com.cn/problem/AT_abc370_e)

### 题意

给出一个长为 $N$ 的序列 $a$，求将其分成多个连续子序列且没有任何一个子序列中数的和为 $K$ 的方案数。对 $998244353$ 取模。

### 思路

考虑 dp，令 $s_i$ 表示前 $i$ 个数的和，$f_i$ 表示将前 $i$ 个数合法划分（即满足题目条件）的方案数，则有转移 $f_i=\sum_{s_i-s_j\ne k}f_j$（$0\le j<i$ 的条件将不再重复）。

可以发现 $s_i-s_j\ne k$ 的条件不好看，故可以令 $g=\sum\limits_{j=0}^i f_j$，则有 $f_i=g-\sum_{s_i-s_j=k}f_j$，条件可转化为 $s_j=s_i-k$，故可以用 map 存下每个 $s_i$ 值对应的 $f_i$ 的和。

### Code

```cpp
#include<bits/stdc++.h>
#define eps 1e-6
#define MOD 998244353
#define inf 0x3f3f3f3f
#define INF 0x3f3f3f3f3f3f3f3f
using namespace std;
typedef long long LL;
typedef pair<int,int> pii;
// #define fi first
// #define se second
#define MAXN 200005
int n,a[MAXN];
LL k,s[MAXN],sum,f[MAXN];
map<LL,LL>mp;
signed main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++)cin>>a[i],s[i]=s[i-1]+a[i];
	mp[0]=1,sum=1;
	for(int i=1;i<=n;i++){
		f[i]=(sum-mp[s[i]-k]+MOD)%MOD;
		mp[s[i]]=(mp[s[i]]+f[i])%MOD;
		sum+=f[i];
	}
	cout<<f[n];
	
	return 0;
}
```

---

