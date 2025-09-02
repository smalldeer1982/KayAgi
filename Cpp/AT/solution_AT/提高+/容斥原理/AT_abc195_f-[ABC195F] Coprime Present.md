# [ABC195F] Coprime Present

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc195/tasks/abc195_f

あなたは $ A $ 以上 $ B $ 以下の整数が書かれたカードを各 $ 1 $ 枚、合計 $ B-A+1 $ 枚持っています。 この中から何枚かを選んで ($ 0 $ 枚でもよい) ペットのすぬけ君にプレゼントしようと考えています。

すぬけ君は、プレゼントされたカードたちについて、どの相異なる $ 2 $ 枚に書かれた数も互いに素であるときに喜び、そうでないとき悲しみます。

すぬけ君が喜ぶようなカードの組合せは何通りありますか？

## 说明/提示

### 制約

- $ 1\ \leq\ A\ \leq\ B\ \leq\ 10^{18} $
- $ B-A\ \leq\ 72 $
- 入力は全て整数

### Sample Explanation 1

あなたは $ 2,3,4 $ が書かれたカードを $ 1 $ 枚ずつ持っています。すぬけ君が喜ぶようなカードの組合せは - $ \{\} $ - $ \{2\} $ - $ \{3\} $ - $ \{4\} $ - $ \{2,3\} $ - $ \{3,4\} $ の $ 6 $ 通りです。

### Sample Explanation 2

すぬけ君が喜ぶようなカードの組合せは - $ \{\} $ - $ \{1\} $ の $ 2 $ 通りです。

## 样例 #1

### 输入

```
2 4```

### 输出

```
6```

## 样例 #2

### 输入

```
1 1```

### 输出

```
2```

## 样例 #3

### 输入

```
123456789000 123456789050```

### 输出

```
2125824```

# 题解

## 作者：NASFsky (赞：9)

对于一个满足题意的集合，集合中每一个元素的质因数肯定不会是该集合中其它元素的质因数，这是显然的。  
注意到不同寻常的数据范围：$B-A\leqslant 72$，那么可以提前预处理出 $[1,72]$ 中所有的质数，只有 $20$ 个，可以进行状态压缩。  
定义状态 $i$，若其第 $j$ 位为 $1$ 则代表其含有第 $j$ 个质数因子。$f[i]$ 则表示集合中质数因子状态为 $i$ 时的方案数。   
初始化为 $f[0]=1$，因为 $\varnothing$ 也为一种可能情况。  
更多的详细内容见代码。
```cpp
#include<bits/stdc++.h>
#define N 2000200
#define ll long long//别忘了开long long 
using namespace std;
ll f[N],ans;//f[i]表示质数拥有情况为i的方案数 
ll pr[22]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71};
ll l,r;
int main()
{
	scanf("%lld%lld",&l,&r);
	f[0]=1;//初始化 
	for(ll i=l;i<=r;i++)
	{
		ll t=0;//t表示i的质因数拥有情况 
		for(ll j=0;j<=19;j++)if(!(i%pr[j]))t|=(1<<j);
		for(ll j=0;j<(1<<20);j++)if(!(j&t))f[j|t]+=f[j];
		//如果j&t=0，则j和t没有相同的质因数，那么f[j|t]的方案数要加上f[j]的方案数 
	}
	for(ll i=0;i<(1<<20);i++)ans+=f[i];
	printf("%lld\n",ans);
}
```


---

## 作者：Swirl (赞：4)

> 状压 dp。

因为 $b - a \le 72$，则从集合 $\left [ a, b \right ]$ 中任取两个数 $x$ 和 $y$ 且 $x \lt y$，其公共质因子一定在 $72$ 以内。

证明如下：

假设存在一对 $(x, y)$ 使得 $x \lt y$ 且存在一个公共质因子 $p \gt 72$。

因为 $p$ 是公共质因子，所以 $\frac{x}{p}$ 和 $\frac{y}{p}$ 一定是正整数。

因为 $x \lt y$，所以 $1 \le \frac{x}{p} \lt \frac{y}{p}$。

则 $y - x \ge p \ge 72$，矛盾，该假设不成立。

那么可以预处理出所有 $72$ 以内的质数，一共 $20$ 个，可以做状压 dp。

我们定义一个数的所有「小质因数」为所有 $72$ 以内的质因数。

我们可以用集合内所有选择的数的所有小质因数所构成的集合来代表原集合。

定义 $f_i$ 为选择的所有数的小质因数集合为 $i$ 时的情况数。

如果存在一个 $x \in \left [ a, b \right ]$ 并且 $x$ 的所有小质因数都没有在 $i$ 出现过，则 $f_i$ 可以通过其转移。

$$
f_{i \cup j} \gets f_{i \cup j} + f_i
$$

其中 $j$ 表示 $x$ 的所有小质因数集。

因为空集也算入答案，所以 $f_{\varnothing} \gets 1$。

---

```cpp
namespace zqh {
const int R = 20, N = (1 << R) + 5;

int a, b;
int dp[N];
int p[R + 5] = {2,  3,  5,  7,  11, 13, 17, 19, 23, 29,
                31, 37, 41, 43, 47, 53, 59, 61, 67, 71};

void init() {
    cin >> a >> b;
}

void solve() {
    dp[0] = 1;
    for (int i = a; i <= b; i++) {
        int I = 0;
        for (int j = 0; j < R; j++) {
            if (i % p[j] == 0) {
                I |= (1 << j);
            }
        }
        for (int j = 0; j < (1 << R); j++) {
            if ((j & I) == 0) {
                dp[j | I] += dp[j];
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < (1 << R); i++) {
        ans += dp[i];
    }
    cout << ans;
}

void main() {
    init();
    solve();
}
}  // namespace zqh
```

---

## 作者：wth2026 (赞：2)

# 题目大意
你有 $B-A+1$ 张卡片，分别写着从 $A$ 到 $B$ 的每个整数。你要把其中一些（也可能一个也没有）给你的宠物 Snuke。

如果卡片上写的数字都是互质的，Snuke 会很高兴；否则，他会很难过。

有多少组卡片会让 Snuke 开心？
# 题目思路
这道题狠狠的教训了那些不看完数据范围就开始想的人。

本题的解题思路在于数据范围中的一个重点：
>$B-A\leq72$

而在信息竞赛的大多数题目中，互质要么与质数有关，要么表示互不相等。在此题中，互质与质数有关。我们可以发现，在区间 $[A,B]$ 中，两个数所同时包含的质因数绝对不会超过 $72$（~~这个因该不用解释吧~~），而 $72$ 以内的质数只有区区 $20$ 个，分别是：

$2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71$

所以使用状压解决问题。

定义 $f_i$ 表示集合 $i$ 的方案数一共有多少种。转移的时候，每一次遍历区间内所有的数，看是否满足当前状态。可以得到 $O(B-A)$ 的转移。总状态数为 $2^{20}$，所以时间复杂度为 $O((B-A)\times2^{20})$。
# [AC Code](https://atcoder.jp/contests/abc195/submissions/57637326)
```cpp
// LUOGU_RID: 176575721
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>

#define endl '\n'
#define int long long
#define inf 0x3f3f3f3f
#define lnf 0x3f3f3f3f3f3f3f

#pragma GCC optimize (1)
#pragma GCC optimize (2)
#pragma GCC optimize (3)
#pragma GCC optimize (4)
#pragma GCC optimize (5)
#pragma GCC optimize ("Os")
#pragma GCC optimize ("Ofast")

const bool Debug = false;

//#define Debug true

using namespace std;

const int N = 1 << 20;

int A, B;
int f[N];
vector <int> _Prm = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71};
int _, _Ans;

signed main () {
	ios :: sync_with_stdio (Debug);
	cin.tie (0);
	cout.tie (0);
	f[0] = 1;
	
	cin >> A >> B;
	
	for (register int i = A; i <= B; ++ i) {
		_ = 0;
		
		for (register int j = 0; j < _Prm.size (); ++ j) {
			if (i % _Prm[j]) {
				continue ;
			}
			
			_ |= (1 << j);
		}
		
		for (register int j = 0; N - j; ++ j) {
			if (j & _) {
				continue ;
			}
			
			f[j | _] += f[j];
		}
	}
	
	for (register int i = 0; N - i; ++ i) {
		_Ans += f[i];
	}
	
	cout << _Ans << endl;
}

```

---

## 作者：skyskyCCC (赞：1)

## 前言。
比较远古的题了，本题存在弱化版在评论区可以找到。

简要题意：请求出在 $\left[A,B\right]$ 内的数字中，两两互质的集合的个数。一个比较考查基本数论的状压动态规划题。
## 分析。
设两个数 $x$ 和 $y$ 为 $\left[A,B\right]$ 中的数，并且 $x>y$ 存在。当 $x$ 与 $y$ 不互质时，我们设 $\gcd(x,y)=k$ 则必定存在 $x$ 与 $y$ 都是 $k$ 的倍数。那么我们不妨将 $x$ 和 $y$ 表示成乘积的形式。立即有 $x=b_1\times k$ 和 $y=b_2\times k$ 的形式，那么 $x$ 和 $y$ 之间的差值为 $x-y=k\times\left(b_1-b_2\right)$ 的结果。根据等式的基本性质即可得到：
$$k=\frac{x-y}{b_1-b_2}$$
那么由于 $x>y$ 存在，由于 $b_1=\frac{x}{k}$ 和 $b_2=\frac{y}{k}$ 之间的存在关系，则必定存在 $b_1>b_2$ 而且均为整数，所以 $b_1-b_2\geq1$ 成立。那么代入原式则有 $k\leq x-y$。

那么我们就可以得知，当 $x$ 和 $y$ 不互质时，一定存在 $\gcd(x,y)\leq x-y$。那么我们猛然发现题目中有一个 $B-A\leq 72$ 的条件，我们正好可以和其结合起来，则有 $x-y\leq A-B \leq 72$ 存在，所以相互之间的公因数的取值范围就在 $\left[1,72\right]$ 之间。那么我们直接暴力枚举即可，直接判断是否互质，具体来说，就是去判断 $x$ 和 $y$ 是否除了 $1$ 以外，还是否同时拥有在 $\left[1,72\right]$ 中间的公因数即可。

直接枚举这个区间，可以得到一共有 $20$ 个质因子。那么现在的算法就很显然了，令 $dp_{i,j}$ 表示在前 $i$ 个数中，质因子集合为 $j$ 的方案数，然后将 $\left[A,B\right]$ 中的每一个数都用一个 $20$ 位的二进制数表示出来，因为要互质，所以我们要保证每种质因子只出现一次，扫一遍统计即可，采用状压动态规划，通过状态压缩来表示每个数含有的质数的情况。

此时我们可以进一步优化，因为前面的 $i$ 和 $j$ 可以合并，所以用 $dp_i$ 来表示 $i$ 对应的集合的方案数即可。此时需要注意空集也是一种可能的情况。

代码如下，仅供参考：
```
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;
long long a,b;
long long ans,sum,tot_pr,pri[25],vis[80],dp[100000005];
int main(){
	//初始化一下，统计那20个质因子。 
    for(int i=2;i<=72;i++){
        if(!vis[i]){
            pri[++tot_pr]=i;
        }
        for(int j=1;j<=tot_pr&&pri[j]*i<=72;j++){
            vis[i*pri[j]]=1;
            //标记一下。 
            if(i%pri[j]==0){
                break;
            }
        }
    }
    dp[0]=1;//空集的情况要统计进去。 
    cin>>a>>b;
    for(long long i=a;i<=b;i++){
        sum=0;
        for(long long j=1;j<=tot_pr;j++){
            if(i%pri[j]==0){
                sum|=(1<<(j-1));
            }
            //分解i拥有的质因子。 
        }
        for(long long j=0;j<(1<<tot_pr);j++){
            if(!(sum&j)){
                dp[sum|j]+=dp[j];
            }
			//判断是否互质。 
        }
    }
    for(int i=0;i<(1<<tot_pr);i++){
        ans+=dp[i];
    }
    cout<<ans<<"\n";
    return 0;
}
```
## 后记。
大家如有疑问，可以在评论区提出，我会尽力解答的。

---

## 作者：Crazyouth (赞：0)

## 分析

不难发现任何大于 $72$ 的质数都不会在 $[a,b]$ 中出现两次（出现指存在一个数是它的倍数），而小于 $72$ 的质数只有 $20$ 个，可以自然想到状压。我们可以预处理出每个数被前 $20$ 个质数中的哪些整除，在转移的时候就可以 $O(1)$ 使用。令 $dp_{i,S}$ 表示区间 $[a,a+i-1]$ 内选出的数的因数（前 $20$ 个质数）组成状态 $S$ 的方案数，对于状态 $dp_{i,S}$，如果满足 $S\cap sta_{i+1}=\varnothing$（$sta$ 数组是前文预处理出的因数），那么可以转移到 $dp_{i+1,S\cup sta_{i+1}}$。另外 $dp_{i,S}$ 也可以正常转移到 $dp_{i+1,S}$（也就是不选第 $i+1$ 个数）。初值 $dp_{0,0}=1$（因为空集也算）。时间复杂度 $O((b-a+1)\times 2^P)$，$P$ 指不大于 $b-a+1$ 的质数个数，这里是 $20$。

## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int sta[80],dp[80][1<<21],pri[30]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71};
signed main()
{
	int a,b;
	cin>>a>>b;
	for(int i=a;i<=b;i++) for(int j=0;j<20;j++) if(i%pri[j]==0) sta[i-a+1]|=(1<<j);
	dp[0][0]=1;
	for(int i=1;i<=b-a+1;i++)
	{
		for(int s=0;s<(1<<20);s++)
		{
			if(!(s&sta[i])) dp[i][s|sta[i]]+=dp[i-1][s];
			dp[i][s]+=dp[i-1][s];
		}
	}
	int ans=0;
	for(int s=0;s<(1<<20);s++) ans+=dp[b-a+1][s];
	cout<<ans;
}

---

## 作者：Shxt_Plus (赞：0)

## ~~诈骗题~~

发现题解区都是状压，发一篇爆搜（优化后甚至跑到最优解）。

看到这题第一思路是容斥，但是直觉告诉我们这题的答案一定不会太大（打表可得最大不超过 $5 \times 10^8$），所以可以考虑用爆搜解决。

对于每个数，用 $f_{i,j}$ 来表示选了 $i$ 这个数还能不能选 $j$，然后直接暴搜，用 bitset 来优化常数，这样就能得到我们的第一代爆搜。

但是我们拿极限数据一跑，发现居然要用 30s，显然无法接受，考虑优化。

我们发现 bitset 的常数实在太大，考虑用 `__int128` 代替，我们发现优化到了 8s，但是还是无法通过。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long l,r;
int n;
__int128 p[105];
long long a[105];
int pc[(1<<19)+5];
int ans=0;
int cnt,cnt1,o;
inline void dfs(int i,__int128 vis)
{
	if(i>=cnt)
	{
		ans++;
		return ;
	}
	dfs(i+1,vis);
	if(vis&((__int128)1<<i))dfs(i+1,vis&p[i]);
}
int ans1=1;
int main()
{
	cin>>l>>r;
	n=r-l+1;
	for(long long i=l;i<=r;i++)
	{
		a[cnt++]=i;
	}
	for(int i=0;i<cnt;i++)
	{
		p[i]|=((__int128)1<<i);
		for(int j=0;j<cnt;j++)
		{
			p[i]|=((__int128)1<<j)*(__gcd(a[i],a[j])==1);
		}
	}
	dfs(0,((__int128)1<<cnt)-1);
	cout<<ans<<"\n";
	return 0;
}
```


我们发现，对于所有偶数，显然选了一个就无法再选其他的数了，所以我们将奇数和偶数分开，然后分开统计奇数里还能选哪些数，偶数里还能选哪些数，显然，当我们选完奇数时，还能在能选的偶数中随意选一个，那么答案就加上 $\text{popcount}(vis1)+1$（加上不选的情况，$vis1$ 表示偶数中还能选哪些数）。

这样我们就能直接跑到 76ms 的好成绩。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long l,r;
int n;
long long p[105];
long long p1[105];
long long b[105],a[105];
int pc[(1<<19)+5];
int ans=0;
int cnt,cnt1,o;
inline void dfs(int i,long long vis,long long vis1)
{
	if(i>=cnt)
	{
		ans+=pc[vis1&o]+pc[vis1>>19]+1;
		return ;
	}
	dfs(i+1,vis,vis1);
	if(vis&(1ll<<i))dfs(i+1,vis&p[i],vis1&p1[i]);
}
int main()
{
	cin>>l>>r;
	n=r-l+1;
	for(long long i=l;i<=r;i++)
	{
		if(i%2!=0)a[cnt++]=i;
		else b[cnt1++]=i;
	}
	for(int i=0;i<cnt;i++)
	{
		for(int j=0;j<cnt;j++)
		{
			p[i]|=(1ll<<j)*(__gcd(a[i],a[j])==1);
		}
	}
	for(int i=0;i<cnt;i++)
	{
		for(int j=0;j<cnt1;j++)
		{
			p1[i]|=(1ll<<j)*(__gcd(a[i],b[j])==1);
		}
	}
	pc[0]=0;
	o=(1<<19)-1;
	for(int i=1;i<(1<<19);i++)
	{
		pc[i]=pc[i-(i&-i)]+1;
	}
	dfs(0,(1ll<<63)-1,(1ll<<cnt1)-1);
	cout<<ans;
	return 0;
}
```

但是我们看着最优解的 21ms，难道爆搜真的比不上状压吗。

不，我们考虑到对于那些与所有数都互质的数是独立的，选不选对其他数都没有影响，所以我们直接将这个数去掉，在最后再算上贡献。

这样我们就以 1ms 的成绩通过了这道题。

[提交记录](https://atcoder.jp/contests/abc195/submissions/54476076)

---

## 作者：PCCP (赞：0)

## 思路

比较明显的暴力是搜索，每次丢入一个数前判断和之前的数是否互质。

但是我们发现题目给定我们 $ r-l\le 72 $，非常的小，也表明这 $ 72 $ 个数两两之间最大的最大质公因数是 $ 71 $。几个数互质，那他们的就不能有相同的质因数，小于等于 $ 71 $ 的质数只有 $ 20 $ 个，这启示我们可以使用状压表示质因数分解优化暴力。

更进一步的，可以直接想到状压 DP 了，第一层枚举当前选的数，第二层枚举质因数状态。某一位为 $ 1 $，就表示这一位代表的质数已经存在，不能再出现。

设 $ n=r-l $，时间复杂度：$ O(2^{20}n) $。

## 代码

```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<vector>
#include<cmath>
#include<queue>
#include<stack>
#include<list>
#include<set>
using namespace std;
const int N=1e7+10;
const int MOD=1e9+7;
long long l,r,ans,f[N];
int prime[N],cnt,sit[N];
bool st[N];
inline long long read(){
    char c(getchar());
    long long x(0);
    while(!isdigit(c))c=getchar();
    while(isdigit(c))x=(x<<3)+(x<<1)+(c^48),c=getchar();
    return x;
}
void write(long long a){
    if(a>9)write(a/10);
    putchar(a%10+48);
}
void ycl(int lim){
	for(int i=2;i<=lim;i++){
		if(st[i]==0)
			prime[++cnt]=i;
		for(int j=1;prime[j]*i<=lim;++j){
			st[i*prime[j]]=true;
			if(i%prime[j]==0)
				break;
		}
	}
}
int main(){
	l=read(),r=read();
	ycl(72);
	f[0]=1;
	for(int i=0;i<=r-l;i++){
		for(int j=1;j<=cnt;j++){
			if((1ll*i+l)%prime[j]==0){
				sit[i]|=((1<<j)>>1);
			}
		}
		for(int j=0;j<=(1<<20);j++){
			if(j&sit[i]){
				continue;
			}
			f[j|sit[i]]=(f[j|sit[i]]+f[j])%MOD;
		}
	}
	for(int i=0;i<=(1<<20);i++){
		if(f[i]){
			ans=(ans+f[i])%MOD;
		}
	}
	printf("%lld\n",ans);
}
```

---

## 作者：loser_seele (赞：0)

部分内容参考自官方题解。

观察到 $ B-A $ 很小，启发我们可以用一些巧妙的办法。

首先如果 $ n > m $ 且在区间 $ [A,B] $ 内，则 $ \gcd(n,m)=\gcd(n-m,m) \leq n-m \leq B-A $，这个是显然的。

那么如果 $ n,m $ 不互质，一定存在一个公质因子在 $ [2,B-A] $ 以内。

于是符合条件的集合一定对于一个 $ [2,B-A] $ 内的质数，满足集合内最多有一个整数整除它。由于 $ B-A \leq 72 $，而 $ 72 $ 以内的质数只有 $ 20 $ 个，所以可以暴力状压转移即可。

时间复杂度 $ \mathcal{O}(Kn) $，其中 $ K \leq 2^{20} $ 为状压的复杂度，可以通过。

代码：

```cpp
#import <bits/stdc++.h>
#define int long long
using namespace std;
const int N=3000010;
int l,r,w,ans,f[N],b[N],prime[N];
bool vis[N];
int tot=0;
void pre(int n)
{
for(int i=2;i<n;i++)
{
    if(!vis[i])
    prime[tot++]=i;
    for(int j=0;j<tot;++j)
    {
    if(i*prime[j]>n)
    break;
    vis[i*prime[j]]=1;
    if(i%prime[j]==0)
    break;
    }
}
}
signed main()
{
    cin>>l>>r;
    pre(r-l+1);
    f[0]=1;
    for(int i=l;i<=r;i++)
    {
    	int s=0;
    	for(int j=0;j<tot;j++)
    	s|=(i%prime[j]==0)<<j;
    	for(int j=0;j<(1<<tot);j++)
    	f[s|j]+=s&j?0:f[j];
    }
    for(int i=0;i<(1<<tot);i++)
    ans+=f[i];
    cout<<ans<<"\n";
}
```


---

## 作者：nxd_oxm (赞：0)

一道比较一眼的状压。

注意到 $B-A \le 72$。显然，对于一个合法集合 $S$，其中 $\forall x \in S$ 的质因数都不被其他的集合中的元素所含有。而在 $A \sim B$ 范围内若存在两个数拥有相同的质因数 $q$，显然 $q \le 72$，也就是说我们只需要记录集合中是否存在这 $20$ 个质数即可。$72$ 中的质数只有 $20$ 个，显然可对其进行状压。

定义 $f_i$ 表示当前集合所拥有的质因数集合为 $i$ 的方案数，其中二进制下 $i$ 的第 $j$ 位表示当前集合所拥有的质因数集合中是否有第 $j+1$ 个质数。转移 $\mathcal{O}(B-A)$，时间复杂度 $\mathcal{O}(2^{20} \times (B-A))$。

## AC code
```cpp
#include<bits/stdc++.h>
using namespace std;
long long l,r,ans=0,mb[110],ln[110],dp[1100000];
bitset<110> vis,vv;
inline void gs(){
	cin>>l>>r;
	int cnt=0;
	for(long long i=2;i<=r-l;++i){
		if(vis[i])continue;
		for(long long j=2;j*i<=r-l;j++){vis[i*j]=1;}
		for(long long j=l/i;i*j<=r;j++){if(i*j>=l)ln[i*j-l]|=(1ll<<cnt);}
		cnt++;
	}
	dp[0]=1;
	for(long long i=l;i<=r;++i){
		for(long long j=0;j<(1ll<<cnt);++j){
			if(!(j&ln[i-l])){
				dp[j|ln[i-l]]+=dp[j];
			}
		}
	}
	for(long long j=0;j<(1ll<<cnt);++j){ans+=dp[j];}
	cout<<ans<<endl;
}
signed main(){ios::sync_with_stdio(0);cin.tie(0),cout.tie();gs();return 0;}
```

---

