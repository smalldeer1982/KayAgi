# [ABC304F] Shift Table

## 题目描述

高桥君和青木君将在接下来的 $N$ 天里做兼职。  
高桥君的排班表由字符串 $S$ 给出，$S$ 的第 $i$ 个字符为 `#` 时表示第 $i$ 天上班，为 `.` 时表示第 $i$ 天不上班。  
基于此，青木君按照如下方式制作了自己的排班表：

- 首先，取 $N$ 的一个正因数 $M$，但 $M \neq N$。
- 接着，决定第 $1$ 天到第 $M$ 天的出勤情况。
- 最后，依次对 $i = 1, 2, \ldots, N - M$，令第 $M + i$ 天的出勤情况与第 $i$ 天相同。

需要注意的是，即使 $M$ 的取值不同，最终得到的排班表也可能相同。

请计算，在 $N$ 天中，每一天高桥君和青木君至少有一人上班的情况下，青木君的排班表可能有多少种，结果对 $998244353$ 取模。

## 说明/提示

## 限制条件

- $N$ 是 $2$ 到 $10^5$ 之间的整数。
- $S$ 是长度为 $N$ 的、仅由 `#` 和 `.` 组成的字符串。

## 样例解释 1

高桥君在第 $1, 2, 4, 6$ 天上班。用字符串 $T$ 表示青木君的排班表，$T$ 的第 $i$ 个字符为 `#` 时表示第 $i$ 天上班，为 `.` 时表示第 $i$ 天不上班。可能的 $T$ 有 `######`、`#.#.#.`、`.##.##` 共 $3$ 种。第 $1$ 种排班表可以通过 $M = 1$ 或 $2$ 或 $3$ 实现，第 $2$ 种排班表可以通过 $M = 2$ 实现，第 $3$ 种排班表可以通过 $M = 3$ 实现。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
6
##.#.#```

### 输出

```
3```

## 样例 #2

### 输入

```
7
...####```

### 输出

```
1```

## 样例 #3

### 输入

```
12
####.####.##```

### 输出

```
19```

# 题解

## 作者：Neil_Qian (赞：14)

# [ABC304F] Shift Table 题解

## 题目描述

给出长度为 $2\le n\le 10^5$ 仅由 `#` 和 `.` 的字符串 $s$，对于任意的 $m|n(0<m<n)$，你可以决定字符串 $t$ 的前 $m$ 个位置是 `#` 还是 `.`，对于第 $i>m$ 个位置，字符与第 $i-m$ 个位置相同。要求对于位置 $1\le i\le n$ 字符串 $s$ 和 $t$ 必须有一个是 `#`。**注意不同的 $m$ 可能有相同的方案**。问 $t$ 的方案数对 $998244353$ 取模的结果。

## 解决方案

首先，我们可以枚举 $m$，可以 $O(\sqrt n)$，做到。我们不能枚举每一种 $t$，显然会超时。很容易发现，**其实 $t_i(i>m)$ 它的取值取决于 $t_{(i-1)\bmod m+1}$**。

- 如果 $s_i$ 是 `.`，那么 $t_i$ 必须是 `#`，也就是 $t_{(i-1)\bmod m+1}$ 必须是 `#`。
- 如果 $s_i$ 是 `#`，那么对 $t_i$ 没有要求。

所以我们可以得到对于 $t_i(1\le i\le m)$ 是否有限制。如果无限制则可以随便选，有限制已经固定。**设有 $w$ 个位置无限制，则有 $2^w$ 中选择。所有 $m$ 计算答案然后累加即可。**

但是有一个问题，如果不同的 $m$ 有相同的 $t$ 怎么办？如果 $m$ 的因数可以，那么 $m$ 也可以，因为是一个周期，实际 $t$ 相同。比如：

```
m=3:##.
m=6:##.##.
```

枚举 $m$ 的因数可以接受。

用 $res_i$ 记录 $m=i$ 时的答案，统计自身的，减去重复的，即可得到答案，注意取模即可。时间复杂度 $O(n\times \sqrt n)$，可以通过，注意 $O(\sqrt n)$ 枚举因数需要对所有因数从小到大排序后处理。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;typedef long long ll;
const ll MOD=998244353,N=1e5+2;vector<ll> v;
ll n,i,cnt,ans,p2[N],res[N],now;string str;bool p[N];
inline void solve(int m){
	memset(p,0,sizeof(p)),now=cnt=0;
	for(ll i=1;i<=n;i++)if(str[i]=='.')p[(i-1)%m+1]=1;//哪些已经确定
	for(ll i=1;i<=m;i++)cnt+=p[i];
	for(ll i=1;i*i<=m;i++)if(m%i==0){//重复的
		((now-=res[i])+=MOD)%=MOD;
		if(i*i!=m)((now-=res[m/i])+=MOD)%=MOD;
	}
	(now+=p2[m-cnt])%=MOD,res[m]=now,(ans+=now)%=MOD;//这次的
}
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0),//读入+预处理
	cin>>n>>str,p2[0]=1,str=" "+str;
	for(i=1;i<=n;i++)p2[i]=(p2[i-1]*2)%MOD;
	for(i=1;i*i<=n;i++)if(n%i==0){//枚举因数
		v.push_back(i);
		if(i*i!=n&&i!=1)v.push_back(n/i);
	}
	sort(v.begin(),v.end());
	for(ll i:v)solve(i);
	return printf("%lld\n",ans),0;//输出
}
```

---

## 作者：Sunflower_ac (赞：8)

# 【题解】[ABC304F] Shift Table

## 题目链接

[[ABC304F] Shift Table
](https://www.luogu.com.cn/problem/AT_abc304_f)

## 题意概述

Takahashi 和 Aoki 将在接下来的 $N$ 天里兼职工作。 

Takahashi 这 $n$ 天的出勤情况由字符串 $S$ 表示，其中 $S$ 的第 $i$ 个字符是 `#` 则表示他在第 $i$ 天工作，第 $i$ 个字符是 `.` 表示他在第 $i$ 天休息。

Aoki 的出勤情况如下：

- 首先选择一个 $N$ 的正因数 $M$，其中 $M\ne N$；
- 接下来安排 $1$ 到 $M$ 天的出勤情况；
- 最后安排 $M+1$ 到 $N$ 天的出勤情况，使得对于任意 $i(1\le i \le M)$，第 $kM+i$ 天的出勤情况与第 $i$ 天一致。

**注意：不同的 $M$ 可能会形成相同的出勤情况安排。**

求 Aoki 可能的出勤情况安排数量，使得 Takahashi 和 Aoki 至少在每一天都有一人工作。

答案对 $998244353$ 取模。

## 数据范围

- $1\le N \le 10^5$

## 题目分析

首先我们发现，$10^5$ 范围内的数的因子数不超过 $128$ 个。

那么很容易想到去枚举因子 ，考虑 $N$ 的每个因子的贡献。

对于每个因子 $M$，我们可以将 $N$ 天平均分为 $\dfrac{N}{M}$ 份，根据题目要求， 每一份的出勤安排相同。

由于必须保证两人至少在每一天都有一人工作，所以若第 $i$ 天 Takahashi 休息，则 Aoki 在这一天必须出勤。同时，如果确定了第 $i$ 天 Aoki 出勤，那么第 $kM+i$ 天 Aoki 也必须出勤。换句话说，若第 $i$ 天出勤，那么所有使得 $j\bmod M=i \bmod M$ 的第 $j$ 天也必须出勤。

基于此，我们可以定义一个 $vis$ 数组，其中 $vis_i$ 表示每一份的第 $i$ 天是否必须出勤。枚举从 $1$ 到 $N$ 的每一天，若 $S_i$ 为 `.`，则将 $vis_{i\bmod M}$ 设为 $1$。

那么对于 $vis_i=0$ 的 $i$，既可以出勤又可以休息，也就是说第 $i$ 天有两种情况。对于 $vis_i=1$ 的 $i$，必须出勤，只有一种情况。

所以对于每个因子 $M$，如果 $vis_i=0$ 的 $i$ 的个数为 $t$，符合题意的方案数就是 $2^t$。

观察样例可以发现，对于所有的 $M$，答案并非是简单的所有 $M$ 的方案数相加，因为不同的 $M$ 可能会形成相同的出勤情况安排。

我们考虑什么样的 $M$ 可以形成相同的出勤安排。容易发现，对于因子 $M_i$ 和 $M_j$，若 $M_i$ 是 $M_j$ 的倍数，则 $M_i$ 的方案数完全包含 $M_j$ 的方案数。那么为了避免重复计数，我们应该将 $M_i$ 的方案数减去 $M_j$ 的方案数计入总答案。

所以我们可以对于每一个因子 $M$ 的方案数，减去所有 $N$ 的因子中同时也是 $M$ 的因子的方案数，即为 $M$ 单独对答案的贡献。

最后，所有的因子贡献之和即为答案。

时间复杂度 $O(128N)$。

## 代码实现

```cpp
//F
//The Way to The Terminal Station…
#include<cstdio>
#include<iostream>
#include<vector>
#include<set>
#define int long long
using namespace std;
const int maxn=1e5+10;
const int mod=998244353;
set<int>p,q;
int vis[maxn],sum[maxn];//vis[i] 表示的是每一份的第 i 天是否必须出勤，sum[i] 表示的是因子 i 的贡献。

inline int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}

signed main()
{
	int n=read();
	string s;
	cin>>s;
	s='%'+s;
	//预处理出 n 的所有因子
	for(int i=1;i<n;i++)
	{
		if(n%i==0)p.insert(i);
	}
	//枚举所有的因子，考虑每个因子的贡献。
	int ans=0;
	for(int v:p)
	{
		for(int i=1;i<=v;i++)vis[i]=0;
		for(int i=1;i<=n;i++)
		{
			int t=i%v;
			if(t==0)t=v;
			if(s[i]=='.')vis[t]=1;
		}
		sum[v]=1;
		for(int i=1;i<=v;i++)
		{
			if(!vis[i])(sum[v]*=2)%=mod;
		}
        //容斥，计算每个因子单独的贡献。
		for(int vv:p)
		{
			if(vv==v)break;
			if(v%vv==0)sum[v]=(sum[v]-sum[vv]+mod)%mod;
		}
		(ans+=sum[v])%=mod;
	}
	cout<<ans<<'\n';
	return 0;
}
```











---

## 作者：NOBenRen (赞：8)

# [题目传送门](https://www.luogu.com.cn/problem/AT_abc304_f)

# 题目大意

高桥和青木将在接下来的 $N$ 天兼职工作。

高桥的轮班时间表由字符串 $S$ 给出，其中，如果他在 $i$ 天工作，则 $S$ 的第 $i$ 个字符为 `#`，如果他在 $i$ 天缺勤，则为 `.`。

基于此，Aoki 创建了他的轮班时间表，如下所示。

- 首先，取 $N$ 的正除数 $M$，该除数不等于 $N$。
- 接下来，确定前 $M$ 天的出勤率。
- 最后，按照此顺序，对于 $i = 1, 2, \ldots, N - M$，确定第 $(M + i)$ 天的出勤率，使其与第 $i$ 天的出勤率相匹配。

请注意，不同的 $M$ 值可能会导致相同的最终轮班安排。

找出青木可能的轮班安排数量，使得 高桥和青木中至少有一人在 $N$ 天的每一天工作，模数为 $998244353$。

# 思路

很明显如果高桥第 $i$ 天没工作，那么青木第 $i$ 天就只有一种情况（必须工作）；而如果高桥第 $i$ 天工作了，那么青木第 $i$ 天就有两种情况（工作或者不工作），所以我们只需要遍历找 $m$，如果有高桥没工作的，答案乘以 $2$。

但是这样我们又会发现一个问题：当遍历的循环节为倍数关系时（如：$2, 4, 8,\ldots$）那么就会有重复计算部分，这种我们就需要用一个数组记录重复部分，在必要时候减去重复部分，然后就 OK 啦！

# 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll N=200005,m=998244353;
ll n,ans,v[N],c,f;/*c用来存储计算过程中可能的组合数 f用来判断某天是否需要工作 通过数组v[i]来防止重复计算*/
string s;
int main(){
	cin>>n>>s,s=" "+s;/*使s下标从1开始*/
	for(int i=1;i<n;i++){/*遍历找m*/
		if(n%i==0){/*找到符合条件m*/
			c=1;
			for(int j=1;j<=i;j++){/*以i为循环节遍历每天是否需要值班*/
				f=0;
				for(int k=j;k<=n;k+=i)if(s[k]=='.'){f=1;break;}/*如果高桥这天没值班青木这天必须值班*/
				if(f==0)c=(c*2)%m;/*方案数X2(01值班或不值)*/
			}
			ans=(ans+c-v[i]+m)%m;/*计算答案,-v[i]去重 +m防止ans<0*/
			for(int j=i+i;j<=n;j+=i)v[j]=(v[j]+c-v[i]+m)%m;/*去重数组i的倍数值刷新 +m同上*/
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：elbissoPtImaerD (赞：6)

莫反做法。

设 $f(x)$ 表示合法方案最小周期为 $x$ 的方案数，$g(x)$ 表示存在周期为 $x$ 的方案数。  
有 $\sum\limits_{d|n}f(d) = g(n)$，莫反一下是 $\sum\limits_{d|n}\mu(\frac nd)g(d) = f(n)$

$g(x)$ 是好算的，逐个考虑前 $i$ 个的贡献是 $1$ 还是 $2$ 相乘即可。

答案是：
$$
\begin{aligned}
\sum\limits_{d|n,d<n}f(d)
&= \sum\limits_{d|n,d<n}\sum\limits_{a|d}\mu(\frac da)g(a) \\ 
&= \sum\limits_{a|n,a<n}g(d)\sum\limits_{a|b,b|n,b<n}\mu(\frac ba) \\ 
&= \sum\limits_{a|n,a<n}g(d)\sum\limits_{b|\frac na,b<\frac na}\mu(b) \\ 
&= \sum\limits_{a|n,a<n}g(d)([\frac na = 1] - \mu(\frac na))
\end{aligned}
$$

枚举 $n$ 的因数，$O(n)$ 扫一遍算 $g$ 即可。

复杂度 $O(d(n)n)$。

[$\color{green}{\checkmark}$](https://atcoder.jp/contests/abc304/submissions/50949323)

---

## 作者：rzh01014 (赞：5)

# [abc304_f](https://www.luogu.com.cn/problem/AT_abc304_f)
### 题目描述
高桥和青木将在接下来的 $N$ 天内兼职工作。   
高桥的班次安排由字符串 $S$ 给出，其中如果 $S_i$ 是 `#` 表示他在第 $i$ 天工作，而 `.` 表示他在第 $i$ 天缺勤。
基于此，青木创建了他的班次安排，如下所示。

- 首先，选择一个 N 的正约数 $M$ 且 $M$ 不等于 $N$。
- 接下来，决定前 $M$ 天的出勤情况。
- 最后，按照 $i=1,2,…,N−M$ 的顺序，决定第 $(M+i)$ 天的出勤情况，使其与第 $i$ 天的出勤情况相匹配。
### 做法
不难发现，我们可以直接枚举 $N$ 的因子 $i$，进行暴力的模拟看前 $i$ 个的位置中哪些位置是必须为`#`，剩下的位置可以填`#`或`.`，令其数量为 $x$，则当前的方案数为 $2^x$。   
接下来考虑重复的情况，若 $j$ 是 $i$ 的因子，则计算 $i$ 时，$j$ 的方案必会被计算进去。若长度为 $j$ 的方案合法，则数个 $j$ 的方案拼接起来也合法。因此只需要减去 $j$ 的方案即可。    
时间复杂度 $O(kn)$，其中 $k$ 为 $n$ 的因子数。事实证明 $10^5$ 范围内最大的 $k$ 为 $127$。
### code
```
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+5,mod=998244353;
int n,dp[N];
bool ans[N];
char a[N];
inline int ksm(int x,int y){
	int ret=1;
	while(y){
		if(y&1) ret=(ret*x)%mod;
		x=x*x%mod;
		y>>=1;
	}
	return ret;
}
signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	int anss=0;
	for(int i=1;i<n;i++){
		if(n%i!=0) continue;
		for(int j=1;j<=n;j++) ans[j]=0;
		for(int j=1;j<=n;j++) if(a[j]=='.') ans[(j%i==0?i:j%i)]=1;
		int sum=0;
		for(int j=1;j<=i;j++) if(!ans[j]) sum++;
		dp[i]=ksm(2,sum);
		for(int j=1;j<=sqrt(i)&&j<i;j++){
			if(i%j==0) dp[i]=(dp[i]-dp[j]+mod)%mod;
			if(i%j==0&&j!=1&&j*j!=i) dp[i]=(dp[i]-dp[i/j]+mod)%mod;
		}
		anss=(anss+dp[i])%mod;
	}
	cout<<anss;
	return 0;
}
```

---

## 作者：Composite_Function (赞：5)

# 题目大意

有 $n$ 天，给出一个长度为 $n$ 的字符串 $s$，表示小 A 的工作表，若为 $\texttt{\#}$ 则表示工作，反之为 $\texttt{.}$ 则表示休息。

接下来，小 B 要决定他的工作表，对于一个 $m$ 满足 $m|n$，决定他的前 $m$ 天的工作表，然后让第 $i+m$ 天的工作情况和第 $i$ 天一样，并且要求 $n$ 天中每一天都有人工作，问共有多少种。

# 解决方案

枚举 $m$ 并算出前 $m$ 天的工作表，$\texttt{\#}$ 则表示工作，$\texttt{.}$ 表示可以工作，方案数就是 $2^\texttt{.的个数}$。

然后 DFS 算容斥就行了。

# AC代码

```
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int mod = 998244353;
int n, a[1000], cnt;
string s;
int qpow(int Base, int Pow, int Mod)
{
	int Ans = 1;
	while (Pow) {
		if (Pow % 2 == 1) Ans = Ans * Base % Mod;
		Base = Base * Base % Mod, Pow /= 2;
	}
	return Ans;
}
int dfs(string s)
{
	int ans = 0;
	for (int i = 1; i <= cnt; ++i) {
		if (s.length() % a[i] != 0 || a[i] == s.length()) continue;
		string t = "";
		int x = 0;
		for (int j = 0; j < a[i]; ++j) t += '.';
		for (int j = 0; j < s.length(); ++j)
			if (s[j] == '#') t[j % a[i]] = '#';
		for (int j = 0; j < t.length(); ++j)
			if (t[j] == '.') ++x;
		ans = ((ans + qpow(2, x, mod) - dfs(t)) % mod + mod) % mod;
	}
	return ans;
}
int solve(string s)
{
	int ans = 0;
	for (int i = 1; i <= cnt; ++i) {
		if (s.length() % a[i] != 0 || a[i] == s.length()) continue;
		string t = "";
		int x = 0;
		for (int j = 0; j < a[i]; ++j) t += '.';
		for (int j = 0; j < s.length(); ++j)
			if (s[j] == '.') t[j % a[i]] = '#';
		for (int j = 0; j < t.length(); ++j)
			if (t[j] == '.') ++x;
		ans = ((ans + qpow(2, x, mod) - dfs(t)) % mod + mod) % mod;
	}
	return ans;
}
signed main()
{
	cin >> n >> s;
	for (int i = 1; i < n; ++i)
		if (n % i == 0) a[++cnt] = i;
	cout << solve(s) << endl;
	return 0;
}
```

吐槽：AT 又不算分，好不容易做了六题

---

