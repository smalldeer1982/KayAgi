# [AGC058B] Adjacent Chmax

## 题目描述

## 题目翻译


给你一个 $1 \sim n$ 的排列 $P$ ,你可以进行若干次如下操作，也可以不进行操作。

- 每次选择一个整数 $i$ ($1\ \leq\ i\ \leq\ N-1$) ，使 $v=\max(P_i,P_{i+1})$ ，然后将 $P_i$ 和 $P_{i+1}$ 改为 $v$ 。

求问最后可能得到多少种不同的结果，答案对 $ 998244353 $ 取模。

## 说明/提示

- $ 2\ \leq\ N\ \leq\ 5000 $
- $ (P_1,P_2,\cdots,P_N) $ 为 $ (1,2,\cdots,N) $ 的排列
- 输入均为整数

### 样例解释 1

操作后 $P$ 可能为 $(1,3,2),(3,3,2),(1,3,3),(3,3,3)$ 这 $4$ 种结果。

## 样例 #1

### 输入

```
3
1 3 2```

### 输出

```
4```

## 样例 #2

### 输入

```
4
2 1 3 4```

### 输出

```
11```

## 样例 #3

### 输入

```
10
4 9 6 3 8 10 1 2 7 5```

### 输出

```
855```

# 题解

## 作者：zac2010 (赞：22)

我么采用区间染色思维去做这题（把 $P_i$ 看做一种颜色）。

钦定最终序列为 $P'$，以及 $l_i,r_i$ 分别为位置 $i$ 左右离 $i$ 最近的 $j$（满足 $P_j>P_i$）。

尝试思考每个颜色最后会覆盖到哪些位置。会发现 $[l_i,r_i]$ 其实就是 $i$ 能覆盖到的极大闭区间（区间内可以随意覆盖）。

这样的性质能比较方便我们去 $\text{DP}$。设 $f_{i,j}$ 表示考虑了原序列的前 $i$ 个位置的颜色，这 $i$ 种颜色已经覆盖了位置区间 $[1,j]$ 的方案数。

转移有两种：
1. $f_{i,j}\leftarrow f_{i-1,j}$。
2. $f_{i,j}\leftarrow f_{i,j-1}[l_i\leq j\leq r_i]$。

最终答案为 $f_{N,N}$。

时间复杂度 $O(N^2)$。

```cpp
#include <bits/stdc++.h>
#define FL(i, a, b) for(int i = (a); i <= (b); i++)
#define FR(i, a, b) for(int i = (a); i >= (b); i--)
using namespace std;
typedef long long ll;
const int N = 5010;
const ll p = 998244353;
int n, a[N]; ll f[N];
int main(){
    scanf("%d", &n), f[0] = 1;
    FL(i, 1, n) scanf("%d", &a[i]);
    FL(i, 1, n){
        int l = i, r = i;
        while(l > 1 && a[l - 1] < a[i]) l--;
        while(r < n && a[r + 1] < a[i]) r++;
        FL(j, l, r) (f[j] += f[j - 1]) %= p;
    }
    printf("%lld\n", f[n]);
    return 0;
}
```


---

## 作者：Super_Cube (赞：8)

# Solution

称操作一段区间为染色。定义 $dp_{i,j}$ 表示对 $1\sim i$ 染色后，$1\sim j$ 的颜色已定的方案数。

对于第 $i$ 个数，如果不能定下自己的颜色就是 $dp_{i-1,j}$，否则找到一个极大区间 $[l,r]$ 使得 $a_{l\sim r}\le a_i$，那么对于 $l\sim r$ 所有数都可以被 $i$ 确定，即为 $dp_{i,j-1}$。所以转移为 $dp_{i,j}=dp_{i-1,j}+[l_i\le j\le r_i]dp_{i,j-1}$。

答案为 $dp_{n,n}$，时间复杂度 $O(n^2)$。

# Code

注意到每次转移只与当前行与上一行相关，打了滚动。

```cpp
#include<bits/stdc++.h>
const int mod=998244353;
int dp[5005];
int a[5005];
int n;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;scanf("%d",&a[i++]));
	a[0]=a[n+1]=n+1;
	dp[0]=1;
	for(int i=1,l,r;i<=n;++i){
		for(l=i;a[l-1]<=a[i];--l);
		for(r=i;a[r+1]<=a[i];++r);
		for(int j=l;j<=r;++j)
			if((dp[j]+=dp[j-1])>=mod)dp[j]-=mod;
	}
	printf("%d",dp[n]);
	return 0;
}
```

---

## 作者：wf715 (赞：8)

写篇讲得比较清楚的题解。

我们和大部分的题解一样，定义 $f_{i, j}$ 表示只使用前 $i$ 个位置的颜色，覆盖了 $[1, j]$ 内的位置的方案数，$l_i$、$r_i$ 分别表示 $P_i$ 所能扩展到的最左、最右的边界。初始设 $f_{0, 0} = 1$。

考虑 dp 到第 $i$ 个位置：

显然 $P_i$ 不可能影响到小于 $l_i$ 与大于 $r_i$ 的位置，于是可以直接使 $f_{i, j} = f_{i - 1, j} (j \in [0, l_i) \cup (r_i, n])$。

对于 $j = l_i$，若不染，则方案数为原来的 $f_{i - 1, j}$；若染，则方案数为 $f_{i - 1, j - 1}$（因为前面无法染到，所以 $f_{i - 1, j - 1}$ 和 $f_{i, j - 1}$ 是一样的）。于是 $f_{i, j} = f_{i - 1, j - 1} + f_{i - 1, j} = f_{i, j - 1} + f_{i - 1, j}$。

对于 $l_i < j \leq i$：

- 若染，则前面的位置可染可不染，方案数为 $f_{i, j - 1}$；

- 若不染，则前面的位置必须不染，此时前 $j$ 个位置均没有 $P_i$，故方案数为 $f_{i - 1, j}$（如果前面的位置染而这个位置不染，意味着这个位置被后面的某个更大的颜色又染过去了，根据定义，那个位置不可能小于 $i$，于是只能大于 $i$，那么只需在 dp 到那个位置的时候再考虑即可）。

于是 $f_{i, j} = f_{i, j - 1} + f_{i - 1, j}$。

对于 $i < j \leq r_i$：

我们需要理解的事实是，$f_{i - 1, j}$ 所表示的方案数中，$j$ 的位置上必须是前 $i - 1$ 个位置的颜色，并且这个颜色只可能大于 $P_i$，这是显然的，不然无法扩展到 $j$ 位置。也就是说，$f_{i, j}$ 在转移时不能考虑 $P_j$，也即不能考虑 $j$ 位置本身的颜色。

- 若染，则前面的位置可染可不染（前面的位置不染相当于被 $i$ 之前的更大的颜色覆盖了），方案数为 $f_{i, j - 1}$；

- 若不染，此时 $j$ 位置上的颜色只能是 $i$ 位置之前的更大的颜色，前面所有的位置必须不染（因为如果染了，就意味着 $i$ 之前更大的颜色无法扩展过来，那么为了让 $j$ 位置上有颜色，只能让 $j$ 染上 $P_i$，矛盾），故方案数为 $f_{i - 1, j}$。

于是 $f_{i, j} = f_{i, j - 1} + f_{i - 1, j}$。

于是对于 $j \in [l_i, r_i]$，$f_{i, j} = f_{i - 1, j} + f_{i, j - 1}$，显然可以滚动数组优化。

希望这是一篇讲得清晰的题解。

---

## 作者：lottle1212__ (赞：5)

# Solution to [AT_agc058_b](https://www.luogu.com.cn/problem/AT_agc058_b)

观察一个 $P_i$，它可以去影响相邻的位置，或被相邻的位置影响，这个取决于哪一个位置上的数更大。那么可以考虑一个较大的 $P_i$，则它可以影响一个很大的范围，直到遇到比它更大的位置，则这些位置就可以构成一个区间，记为 $[l_i, r_i]$。我们把它看成一个染色的问题，每一个 $P_i$ 就是一种颜色。

从左往右去考虑每一种颜色，设计状态 $f_{i, j}$ 表示考虑用前 $i$ 个位置上的颜色，去填充前 $j$ 个位置的方案数。

$$f_{i, j}=\sum_{k=l_i-1}^{j} f_{i-1, k}$$

即用颜色 $i$ 去填充 $[k+1, j]$，$[1, k]$ 用前 $i-1$ 种颜色填充 $O(n^3)$。

用前缀和优化一下即可 $O(n^2)$。

[Code](https://atcoder.jp/contests/agc058/submissions/56449519)

---

## 作者：DengDuck (赞：4)

我们可以理解为一个染色问题。

首先求一个颜色的染色区间，因为数据很小，你既可以写单调队列，也可以写暴力。

然后，我们设 $f_i$ 表示前 $i$ 项染色有几种方案。

初始状态 $f_0=1$。

接下来我们从 $1$ 到 $n$ 逐次考虑每种颜色对答案的贡献。

显然新的颜色编号为 $x$ 会使它的染色区间 $[L,R]$ 的 $f_i(L\leq i\leq R)$ 增大。

那么对于第 $L$ 项，它可以染成一个新的颜色，前面不变，因此方案数为 $f_L=f_L+f_{L-1}$。

对于第 $i(L<i\leq x)$ 项，有三种可能：前面染我也染，前面不染我染，前面不染我不染,贡献是 $f_{i-1}$，加上即可。


对于第 $i(x< i\leq R)$ 项，有三种可能：前面染我也染，前面不染我不染，前面染我不染,贡献是 $f_{i-1}$，加上即可。

因此思路很清楚了，每次找到 $x$ 和对应的 $[L,R]$，然后更新区间内的 $f_i\gets f_i+f_{i-1}$。

```cpp
#include<bits/stdc++.h>
#define LL long long
#define val first
#define num second
using namespace std;
stack<pair<LL,LL> >s;
const LL N=5005; 
const LL mod=998244353;
LL n,a[N],l[N],r[N],f[N]; 
int main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
		while(!s.empty()&&s.top().val<a[i])
		{
			r[s.top().num]=i-1;
			s.pop();
		}
		if(s.size())l[i]=s.top().num+1;
		else l[i]=1;
		s.push({a[i],i});
	}
	while(!s.empty())
	{
		r[s.top().num]=n;
		s.pop(); 
	} 
	f[0]=1;
	for(int i=1;i<=n;i++)
	{
		for(int j=l[i];j<=r[i];j++)
		{
			f[j]=(f[j]+f[j-1])%mod;
		}
	}
	printf("%lld",f[n]);
}
```

---

## 作者：良心WA题人 (赞：3)

可以发现题目的操作实际上是每种颜色可以覆盖掉所有数都小于它的一段。那么可以预处理每种颜色可以覆盖哪里到哪里。记为 $[l_i,r_i]$

首先能发现一个右侧的颜色是不会跨过一个前面的颜色去覆盖的。

现在我们从左到右去用颜色 $a_i$ 覆盖一些段，可以发现若颜色覆盖的段 $[l,r]$ 并不包含 $i$（下假设 $i>r$），则 $[r+1,k]$ 所覆盖的颜色 $a_j$ 必然大于 $a_i$。因为原本满足 $j>i>r$，那么能够覆盖到 $r+1$ 则必然能覆盖 $i$，则 $a_j>a_i$。所以一定可以完成覆盖。

定义 $f_{i,j}$ 表示前 $i$ 个数，第 $i$ 个位置使用颜色 $a_j$ 来覆盖。若 $i<l_i$ 或 $i>r_i$ 则 $f_{i,j}=0$，否则 $f_{i,j}=\sum_{k=1}^j f_{i-1,j}$。

显然可以前缀和优化。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int NN=5004,P=998244353;
int a[NN],l[NN],r[NN],f[NN][NN],s[NN][NN];
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	f[0][0]=1;
	for(int i=1;i<=n;i++)
	{
		l[i]=i;
		while(l[i]>1&&a[l[i]-1]<=a[i])
			l[i]--;
		r[i]=i;
		while(r[i]<n&&a[r[i]+1]<=a[i])
			r[i]++;
	}
	for(int j=1;j<=n;j++)
		s[0][j]=1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		{
			if(i>=l[j]&&i<=r[j])
				f[i][j]=s[i-1][j];
			s[i][j]=(s[i][j-1]+f[i][j])%P;
		}
	printf("%d",s[n][n]);
	return 0;
}
```

---

## 作者：daniEl_lElE (赞：3)

## 思路

考虑 $dp_{i,j}$，表示看到第 $i$ 个数，看到这个数为止已经覆盖了 $1\sim j$ 的区间的方案数。

转移时先计算左右第一个大于 $a_i$ 的数，记为 $l_i,r_i$，对区间做前缀和并添加即可。原因就是这个数比区间内所有数都大，一定有操作可以让其他数变成他。

据说有 $O(n\log n)$ 解，应该是通过线段树维护这个区间算个前缀和的操作，不过这题 $O(n^2)$ 即可。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int mod=998244353;
int dp[5005][5005];
signed main(){
	dp[0][0]=1;
	int n;
	cin>>n;
	int p[n+1];
	p[0]=0;
	for(int i=1;i<=n;i++) cin>>p[i];
	for(int i=1;i<=n;i++){
		int l=i,r=i,sum=0;
		while(l>=0&&p[i]>=p[l]) l--; l++;
		while(r<=n&&p[i]>=p[r]) r++; r--;
		for(int j=0;j<=n;j++) dp[i][j]=dp[i-1][j];
		if(l) sum=dp[i-1][l-1];
		for(int j=l;j<=r;j++) dp[i][j]=(dp[i][j]+sum)%mod,sum=(sum+dp[i-1][j])%mod;
	}
	cout<<dp[n][n];
	return 0;
}
```

---

## 作者：yueyan_WZF (赞：2)

首先，我们看题，我们可以在题目中得知:

>每次选择一个整数 $i(1 \le i \le N−1)$ 使 $v=\max(p_i,p_{i+1})$，然后将 $P_i$ 和 $P_{i+1}$ 改为 $v$。

我们可以考虑染色问题，让一个数进行扩张（也就是把其他数覆盖成自己），直到两边的数都大于自己才停止。

这样我们就求出了每个数的最大扩张范围，最后用 DP 求出方案数就行了。

DP 的状态转移方程：

$$ f_i = f_i + f_{i-1}$$

（$f_i$ 表示第 $i$ 项的方案数）

### AC code：


```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=998244353;
int n;
int p[5003];
int f[5003];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&p[i]);
	}
	f[0]=1;
	for(int i=1;i<=n;i++){
		int l=i-1,r=i+1;
		while(l>=1&&p[l]<p[i]){
			l--;
		} 
		while(r<=n&&p[r]<p[i]){
			r++;

		}
		for(int j=l+1;j<r;j++){
			f[j]+=f[j-1];
			f[j]%=mod; 
		}
	}
	cout<<f[n];
}
```

---

## 作者：CarroT5656 (赞：1)

**题目大意**

给定你一个 $1\sim n$ 的排列 $P$，你可以做以下操作若干次：

* 选定一个 $i(1\le i<n)$，并将 $P_i$ 和 $P_{i+1}$ 替换成 $\max{(P_i,P_{i+1})}$。

问你有多少种合法的最终序列，对 $998244353$ 取模。

**解法分析**

显然一个数在向外扩张的时候，不可能跨过比它大的数。

所以你可以记录一个 $l_i$ 和一个 $r_i$，分别表示 $P_i$ 左边和右边第一个比它大的数。

考虑 dp。

令 $dp_{i,j}$ 表示考虑到 $P$ 中的第 $i$ 位，最终序列的第 $j$ 位时的方案数。

* 如果 $P_i$ 在最终序列没有出现，可以贡献到 $dp_{i+1,j}$。

* 如果 $P_i$ 在最终序列出现了，可以贡献到 $dp_{i+1,k}(j+1\le k<r_{i+1})$。

答案就是 $dp_{n,n}$。

时间复杂度 $O(n^3)$，会 T。考虑优化。

你发现第二种情况实际上是在一个区间加上一个相同的数，用差分优化即可。

时间复杂度 $O(n^2)$，可以通过。

**Code**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define mod 998244353
#define N 5005
ll n,a[N],l[N],r[N],dp[N][N],s[N][N];
int main(){
	scanf("%lld",&n);
	for(ll i=1;i<=n;i++) scanf("%lld",&a[i]);
	a[0]=a[n+1]=LLONG_MAX;
	for(ll i=1;i<=n;i++){
		for(ll j=i-1;j>=0;j--) if(a[j]>a[i]){l[i]=j;break;}
		for(ll j=i+1;j<=n+1;j++) if(a[j]>a[i]){r[i]=j;break;}
	}
	dp[0][0]=1;
	for(ll i=0;i<n;i++){
		for(ll j=0;j<=n;j++){
			(dp[i+1][j]+=dp[i][j])%=mod;
			(dp[i+1][j+1]+=mod-dp[i][j])%=mod;
			if(l[i+1]<=j&&j+1<r[i+1]){
				(dp[i+1][j+1]+=dp[i][j])%=mod;
				(dp[i+1][r[i+1]]+=mod-dp[i][j])%=mod;
			}
		}
		for(ll j=0;j<n;j++) (dp[i+1][j+1]+=dp[i+1][j])%=mod;
	}
	printf("%lld\n",dp[n][n]);
	return 0;
}
```

---

## 作者：IceKylin (赞：1)

# AT_agc058_b  Adjacent Chmax 题解
### [原题链接（in luogu）](https://www.luogu.com.cn/problem/AT_agc058_b)
### [原题链接（in AtCoder）](https://atcoder.jp/contests/agc058/tasks/agc058_b)
### [更好的阅读体验？](https://www.luogu.com.cn/blog/std-IK/atagc058b-ti-xie)

这是一道比较简单的 **区间 DP** 题。

我们设闭区间 $[l_i,r_i]$ 的最大值为 $f(l_i,r_i)$。

考虑 $P_i$ 所能覆盖到的极大闭区间 $[l_i,r_i]$，显然有 $(f(l_i,r_i)=P_i)\wedge(P_{l_i-1}>P_i)\wedge(P_{r_i+1}>P_i)$。

又因为求的是方案总数，并且区间具有可累加处理的性质，所以不难想到 **前缀和**。

那么解法就呼之欲出了：

1. 设 $dp_i$ 表示 $P_1\sim P_i$ 对答案的贡献之和，$dp_0$ 初值为 $1$（即不操作）。 

2. 暴力寻找 $P_i$ 所能覆盖到的极大闭区间 $[l_i,r_i]$（如果用数据结构维护可以做到 $O(\log n)$，但没有必要）。

3. 对该区间做一次前缀和的累加，即 $dp_{i}\gets (dp_i+dp_{i-1})\quad(i=l_i,l_i+1,\cdots,r_i-1,r_i)$

4. 答案即为 $dp_n$。

**时间复杂度**：

1. 暴力找区间法：$O(n^2)$。

2. 数据结构维护法：$O(n\log n)$。

P.S. 本题数据范围需要开 **long long**，取模可以用加减代替（~~卡常~~）。

## AC 代码

```cpp
//By IceKylin
#include<bits/stdc++.h>
#define ll long long
#define mod (ll)(998244353)
#define maxn 5050
#define ios ios::sync_with_stdio(false) 
using namespace std;
ll n,a[maxn],dp[maxn];
void add(ll &x,ll y){
	x+=y;
	if(x>=mod)x-=mod;
}
int main(){
	ios;
	cin>>n;
	for(int i=1;i<=n;++i)cin>>a[i];
	dp[0]=1;
	for(int i=1;i<=n;++i){
		int l=i,r=i;
		while(l>1&&a[l-1]<a[i])--l;
		while(r<n&&a[r+1]<a[i])++r;
		for(int j=l;j<=r;++j)add(dp[j],dp[j-1]);
	}
	cout<<dp[n];
	return 0;
}

```

---

## 作者：ZXXS (赞：1)

### 做法
此题一维 dp。

具体步骤如下：

1. 先查找每一个值左右能影响的最大边界，确定区间。

查找的原因是因为一个数只可能被覆盖或影响到 $l_i$,$r_i$，即计算每一个值左右第一个大于它本身的数，记为 $l_i$,$r_i$。

2.  $f_i$ 存储每一个值的区间中每一个数的区间 $f_j$ 的值，即求这一段的 DP 的和，依次赋上值求前缀和（取模），即为 DP。

第二步即为 dp 的做法，求到每一个数的方案数：从 $l_i$ 到 $r_i$的每一项 dp 的值都加上前一项 dp 后的值，即 dp 公式为 `f[j]+=f[j-1]`,最后一项 $f_n$ 就是最终的答案。

### 代码实现
```cpp
#include<bits/stdc++.h>
#define debug(x) cerr<<#x<<"="<<(x)<<endl;
using namespace std;
inline void write(int x)//快写
{
	if(x<0)
	{
		putchar('-');
		x=-x;
	}
	if(x>9)
		write(x/10);
	putchar(x%10+'0');
}
inline int read()//快读
{
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9')
	{
		if(c=='-')
			f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		x=x*10+c-'0';
		c=getchar();
	}
    return x*f;
}
int n,a[5005],f[5005];//f[i]存dp的值
int main()
{
	n=read();
	for(int i=1;i<=n;++i)
	{
		a[i]=read();
	}
	f[0]=1;//dp初值
	for(int i=1;i<=n;++i)
	{
		int l=i,r=i;
		while(l>1&&a[l-1]<a[i])//查找左边能影响的最大边界
			--l;
		while(r<n&&a[r+1]<a[i])//查找右边能影响的最大边界
			++r;
		for(int j=l;j<=r;++j)//DP，依次赋上值即为DP的值
		{
			f[j]+=f[j-1];
			f[j]%=998244353;
		}
	}
	write(f[n]);
    return 0;
}


```


---

## 作者：aCssen (赞：0)

### Solution

把操作视为染色。那么一个数能染到的区间是 $[L_i,R_i]$，其中 $L_i,R_i$ 分别表示左边和右边最后一个不超过 $p_i$ 的位置。

从 $p_1 \sim p_n$ 依次加入颜色，每个时刻能染到的位置都是一段前缀，因为能染到的任意一个位置都是由目前考虑的这些颜色中的某一个扩展出去的连续区间。所以设 $f_{i,j}$ 表示用了 $p _{1 \sim i}$，染色了 $[1,j]$ 的方案数，初始时 $f_{0,0}=1$。

对于 $f_{i,j}$，我们如果不染色，那么它的颜色就必须是之前染的，所以 $f_{i,j}=f_{i-1,j}$。如果染色，需要满足 $L_i \le j \le R_i$，考虑这部分的转移：对于 $j \le i$ 的部分，我们要让 $j$ 染成 $p_i$，染的是 $[j,i]$ 这一段，对左边没有限制，所以方案数是 $f_{i,j-1}$。对于 $j>i$ 的部分，我们要求 $[i,j]$ 必须进行染色，这样才能染成 $p_i$。考虑 $f_{i-1,j}$ 给 $j$ 染上的颜色一定比 $p_i$ 大，不然无法跨过 $i$ 这个位置，因此 $f_{i,j-1}$ 存储的方案有两部分，第一种为 $j-1$ 染成 $p_i$ 的方案，第二部分是将 $j-1$ 染成某个比 $p_i$ 大的颜色的方案。我们只需要先染 $[j,i]$ 再染之前的方案就能做到 $j$ 的颜色为 $p_i$，所以 $j>i$ 部分的方案也是 $f_{i,j-1}$。这是足够的，因为如果染了 $j$ 那么 $[i,j]$ 中的颜色不可能比 $p_i$ 小。

更好理解的方式是枚举 $p_i$ 染的范围，即 $f_{i,j}=\sum_{k=L_i-1}^j f_{i-1,k}$，然后前缀和优化，直接做在 $f$ 上。
### Code
```cpp
#include<algorithm>
#include<iostream>
#include<cstdio>
#define file(x) freopen(x".in","r",stdin);freopen(x".out","w",stdout);
using namespace std;
typedef long long ll;
namespace FastIO{
	template<typename T=int> T read(){
		T x=0;int f=1;char c=getchar();
		while(!isdigit(c)){if(c=='-') f=~f+1;c=getchar();}
		while(isdigit(c)){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
		return x*f;
	}
	template<typename T> void write(T x){
		if(x<0){putchar('-');x=-x;}
		if(x>9) write(x/10);
		putchar(x%10+'0');
	}
	template<typename T> void Write(T x,char c='\n'){write(x);putchar(c);}
}
using namespace FastIO;
const int MOD=998244353;
const int maxn=5005;
int f[maxn][maxn],a[maxn];
int main(){
	int n=read();
	for(int i=1;i<=n;i++) a[i]=read();
	f[0][0]=1;a[0]=a[n+1]=n+1;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=n;j++) f[i][j]=f[i-1][j];
		int L=i,R=i;
		while(a[L]<=a[i]) L--;
		while(a[R]<=a[i]) R++;
		for(int j=L+1;j<R;j++) f[i][j]=(f[i][j]+f[i][j-1])%MOD;
	}
	write(f[n][n]);
	return 0;
}
```

---

## 作者：GY程袁浩 (赞：0)

在文中，为方便介绍，我们称一次操作为“染色”，而在操作过程中更新了一个元素的值，我们称那个元素“被染色”，一个元素 $x$ 与另一个元素 $y$ 操作，使另一个元素更新值，称“用 $x$ 来染色”。

首先发现如果用 $a_{i}$ 来染色，最左染到左边第一个比他大的数的右边，最右染到右边第一个比他大的数的左边。

所以我们定义 $[l_{i},r_{i}]$ 表示用一个元素最左、最右能染到的位置，这就是那个元素的影响范围。

考虑 DP，设状态为 $f_{i,j}$ 表示目前考虑到第 $i$ 个元素，用这 $i$ 个元素染色到了 $j$，显然初始状态 $f_{0,0}$ 为 $1$。

讨论方案数哪里来：

考虑讨论 $j(l_{i} \le j \le r_{i})$ 的染色情况，如果 $j$ 不染色，那么说明原来就有，从 $f_{i-1,j}$ 转移而来，如果染色，那么从 $f_{i,j-1}$ 转移而来，即又往右染了一个元素。

不在上述区间的方案数就直接继承 $f_{i-1,j}$ 的方案数。



```cpp
//很有趣的一道题目，代码不长思维很精妙 
#include <bits/stdc++.h>
#define int long long
#define upp(a,x,y) for(int a=x;a<=y;a++)
#define dww(a,x,y) for(int a=x;a>=y;a--)
using namespace std;
const int N=5010,X=998244353;
int f[N][N],a[N],n;
signed main() {
	cin>>n;upp(i,1,n) cin>>a[i],f[0][0]=1;
	upp(i,1,n) {
		int l=i,r=i;
		while(l-1>=1&&a[l-1]<=a[i]) l--;
		while(r+1<=n&&a[r+1]<=a[i]) r++;
		upp(j,0,n) f[i][j]=f[i-1][j];
		upp(j,l,r) f[i][j]=(f[i][j]+f[i][j-1])%X;
	}
	cout<<f[n][n]<<endl;
	return 0;
} 
```

---

## 作者：youdu666 (赞：0)

思路跟第一篇题解一样，但是感觉第一篇没讲得很清楚（反正我没看懂），我再来嘴一嘴。

考虑把区间内每一个位置从前往后地执行 $f_i=f_i+f_{i-1}$ 的本质其实是 $f_i=f_i+\sum_{j=l-1}^{j \leq i-1}{f_j}$。算式中的 $f_i$ 就是不修改当前位的方案，后面一个相当于就是当前的位置开始往前填写 $a_i$ 一直填到第 $j$ 位的贡献，加起来就是他们的贡献和。这一点第一篇题解里没有说得特别清楚（当然，不排除我的理解与作者不同）。

于是就可以把每个点处理出左右最远能到达（即数值都比它小）的位置，然后暴力做区间连加就行了。

代码不贴了。

---

## 作者：yukimianyan (赞：0)

## problem
一个长为 $n$ 的排列 $P$，每次可以选择一个 $i$，令 $v=\max(P_i,P_{i+1})$，使 $P_i=P_{i+1}=v$，求若干次操作后有多少种不同的序列。$1\leq n\leq 5000$。

## solution
显然地，对于一个 $P_i$，它要么被完全覆盖，要么会占领一段区间 $[l_i,r_i]$。显然这些 $[l_i,r_i]$ 要连续，它占领的这一段区间是由这个最大值扩散出去的，所以不能扩散到比它大的值。令它能扩散的区域是 $[L_i,R_i]$（这部分暴力），显然 $L_i\leq l_i\leq r_i\leq R_i$（这里注意 $i$ 号点最终不一定会被它自己覆盖）。于是 DP，设 $f_{i,j}$ 表示当 $r_i=j$ 时的方案数，枚举 $l_i$ 在哪里，从 $f_{i-1,l_i-1}$ 转移就可以了。

## code
```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
const int P=998244353;
int n,a[5010];
LL f[5010][5010];
int main(){
//	#ifdef LOCAL
//	 	freopen("input.in","r",stdin);
//	#endif
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	a[0]=a[n+1]=1e9;
	f[0][0]=1;
	for(int i=1;i<=n;i++){
		int l=i,r=i;
		while(l>=1&&a[l-1]<=a[i]) l--;
		while(r<=n&&a[r+1]<=a[i]) r++;
		memcpy(f[i],f[i-1],sizeof f[i]);
		LL sum=f[i][l-1]; 
		for(int j=l;j<=r;j++){
			f[i][j]=(f[i][j]+sum)%P;
			sum=(sum+f[i-1][j])%P;
		}
	}
	printf("%lld\n",f[n][n]);
	return 0;
}

```

[一些关于这个题的思考](https://www.luogu.com.cn/paste/lugtus1n)


---

