# Sultan Rage

## 题目描述

有一个数列 $\{a_n\}$ 满足对 $n > m$ 均有 $a_n=\sum\limits_{j=1}^m a_{n-j}$，并且 $a_1,a_2,\cdots,a_m$ 是输入中给出的正整数。

$q$ 次询问，每一次给出一个正整数 $x$，问有多少个不可重正整数集 $S$ 满足 $\sum\limits_{s\in S}a_s=x$。答案对质数 $998244353$ 取模。

本题有多组数据。

## 说明/提示

对于所有数据，$T=5$，$2 \le m \le 100$，$1 \le q,a_i \le 100$，$1 \le x \le 10^{18}$。
$$
\def\arraystretch{1.5}
\begin{array}{c|c|c|c|c|c}\hline 
\textbf{测试点编号}&\bm{m\le}&\bm{q \le }&\bm{a_i \le }& \bm{x \le}&\bm{\textbf{特殊性质}}\cr\hline 
\textsf1\sim \sf2 & 8&8  & 8 & 100\cr\hline 
\sf3\sim 5 & 15& &15&10^3 \cr\hline 
\textsf6 & & & & 1 &\cr\hline 
\sf7\sim 11 & & 1& & & \textsf{A}\cr\hline
\sf12\sim 16 & 2& & &\cr\hline
\sf17\sim 20 & &\cr\hline
\end{array}
$$

$\textsf A$：$m=10$，且 $x$ 在所有可能的 $x$ 中随机生成。

## 样例 #1

### 输入

```
2
2 5
1 1
3 5 7 9 11
3 5
1 2 5
4 7 10 18 22```

### 输出

```
3
3
3
5
5
0
1
1
1
1```

# 题解

## 作者：Pengzt (赞：8)

[P8565](https://www.luogu.com.cn/problem/P8565)

发现数列 $a$ 增长的特别快，项数最多时是 $a_1 = a_2 = 1, m = 2$，也就是斐波那契数列，这样也只需要不到 $100$ 项就可以超过 $10^{18}$。

发现值域上点的分布越来越稀疏且点极少，可以考虑搜索，函数 ```dfs(val, cur)``` 表示凑出 $x$ 还需要 $val$，现在在考虑 $cur$。

但光是搜索肯定不能过这道题，考虑优化。

先记忆化掉重复的操作，可以用一个 map 来存储，然后可以进行可行性剪枝，如果以后再怎么凑都不行，直接剪枝，可以用前缀和优化一下。

但是这样只有 30 分。

可以改变一下搜索的顺序，因为先考虑小元素的话，会有较多的无用的搜索，且小元素较灵活，更容易凑到 $x$，故可以从大到小的考虑。这样就可以过了。

注意：判断能否返回时是 ```mp[cur].conut(val)```，而不是 ```mp[cur][val]```，否则会超时。因为如果这样判断的话，会直接额外开一个节点，对每一层都是如此，但第一次搜索时会额外开 $2^{dep - 1}$ 个节点，会使后面的搜索查询越来越慢（尽管迟早也要开，等于这样使常数变大了不少）。

时空可过。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
ll read() {
	ll ret = 0, sgn = 0;
	char ch = getchar();
	while (!isdigit(ch)) sgn |= ch == '-', ch = getchar();
	while (isdigit(ch)) ret = ret * 10 + ch - '0', ch = getchar();
	return sgn ? -ret : ret;
}
const int N = 180, mod = 998244353;
const ll INF = 1e18;
int n, q;
ll a[N], sum[N];
map<ll, int> mp[N];

int dfs(ll x, int cur) {
	if (x < 0 || x > sum[cur]) return 0;
	if (!cur) return (x == 0);
	if (mp[cur].count(x)) return mp[cur][x];
	return mp[cur][x] = (dfs(x - a[cur], cur - 1) + dfs(x, cur - 1)) % mod;
}

int main() {
	int T = read();
	while (T--) {
		n = read(), q = read();
		for (int i = 1; i <= n; i++) a[i] = read();
		int m = n;
		while (a[m] <= INF) {
			a[++m] = 0;
			for (int i = 1; i <= n; i++) a[m] += a[m - i];
		}
		n = m - 1;
		for (int i = 1; i <= n; i++) {
			sum[i] = sum[i - 1] + a[i];
			mp[i].clear();
		}
		while (q--) {
			ll x = read();
			printf("%d\n", dfs(x, n));
		}
	}
	return 0;
}
```

---

## 作者：JohnVictor (赞：5)

#### Solution 1（纯暴力）

直接当做一般的背包问题做（也就是令 $dp_{i,j}$ 表示前 $i$ 个数和为 $j$ 的方案数），时间复杂度 $O(kw^2)$，其中 $k$ 为不超过 $w$ 的 $a_i$ 个数，$w$ 为询问中 $x$ 的最大值。期望通过测试点 $1 \sim 5$。

#### Solution 2（数位 dp+推导）

 一般的这种范围的背包问题是不可做的，对于这个问题我们需要一些观察。

之后我们记 $1 \le i \le m$ 的 $a_i$ 是小的，其它是大的。

测试点 $6 \sim 8$ 中答案不超过 $1$，我们只用判断是否能取到就行。

对于小的 $a_i$，也就是 $1 \le i \le m$，我们能背包出它们能取到什么数。

只用考虑大的 $a_i$ 表示出一个数的方案数。

我们考虑将每一种方案对应成一个 $0-1$ 数组，第 $i$ 位是 $1$ 当且仅当 $a_i$ 被选择。这里 $i \ge m+1$。

注意到我们可以对方案进行这样的操作而不改变最后的和：对于连续 $m$ 个 $1$，如果之后一位是 $0$，那么可以把这些 $1$ 都变成 $0$ 并且把之后的 $0$ 变成 $1$。

我们不断进行这样的操作，它肯定会停止（我们考虑直接看成二进制数在变大，但是很后面的位显然不能是 $1$）。

停止的时候不会有连续的 $m$ 个 $1$，否则取其中最前的一组还可以继续操作。我们称这样操作到不能再操作的表示为最简表示。

现在，我们有如下结论：**最简表示是唯一的**。

考虑反证法。如果有两种不同的最简表示，去掉相同的位之后还是最简表示。那么我们可以假设这两个表示没有相同的位。不妨假设第一个表示有某个 $a_n$，而第二个表示用的都是更小的数。

注意到第二个表示在 $a_{n-1},a_{n-2},\cdots a_{n-m}$ 中必定有一个不选；$a_{n-m-1},\cdots,a_{n-2m}$ 中也是如此。这样它的和最多是 $a_{n-1}+\cdots+a_{n-m+1}+a_{n-m-1}+\cdots +a_{n-2m+1}+\cdots<a_n$。最后的小于号对 $n$ 归纳，将左边的前 $m-1$ 项移到右边并且利用通项公式，那么就变成了 $n-m$ 的情况。

当然证明上述结论的过程显然也表明了直接从上往下的贪心（从最大的 $a_i$ 开始，如果当前 $x$ 大于现在考虑的 $a_i$ 就将 $x$ 减去 $a_i$，然后再考虑下一个，一直这样下去）确实能求出唯一的最小表示。

最后计数方案数：对于每一种最小表示，考虑变回普通表示的话，只能是 $(11\cdots 1011 \cdots 10\cdots 11\cdots 0)\to (00\cdots 01)$，其中左边那个第一段是 $m$ 个 $1$，后面的段是 $m-1$ 个 $1$。

注意这样退回去的过程中不同的 $1$ 最终变回的部分和原来的 $1$ 顺序相同，并且可能到达的范围也很好求出。现在令 $dp_{i,0/1}$ 为到第 $i$ 位，前面一个最简表示中的 $1$ 要不要变回到这一位的方案数即可。（其中 $i$ 的取值范围是最简表示的 $1$ 的位置）

时间复杂度：背包的复杂度为 $O(m\max a_i)$，之后数位 dp 的复杂度为 $O(\log x)$，总复杂度 $O(mq \max a_i\log x)$。

bonus：仔细思考一下几个细节，例如为什么从上往下直接贪心并不能通过测试点 $6-8$，但是在什么样的 $a_i$ 下这个贪心算法又是正确的；更具体地，想清楚为什么我们只考虑大的 $a_i$ 就可以贪心，而带上小的 $a_i$ 又不行。 

#### Solution 3(爆搜)

直接开始爆搜，用 `Search(x,y)` 表示用前 $y$ 个数凑出 $x$ 的方案数，具体的式子和直接背包类似。我们将所有搜到的状态记忆化，这样就不弱于直接背包。如果想要通过，我们需要两个优化：如果当前的 $x$ 大于剩下的所有剩下的数之和，那么答案显然是 $0$；对于较小的 $x$ 用背包预处理答案，搜索到这些 $x$ 时直接返回。

可以证明以上爆搜的复杂度是正确的。实际上，可以发现上述表示中如果最大的是第 $t$ 位的话，那么 $t,t-1$ 位至少选一位，否则会被剪枝掉。这样两次搜索就能让 $y$ 减小 $1$。更加合适的想法是 Proof by AC 或者注意到最大的两个必须选一个，从而想到状态数应该不多。期望通过所有测试点。

如果忽略了一些细节或者没有想到什么优化也有很大概率通过测试点 $7\sim 11$。

---

## 作者：12345678hzx (赞：4)

## 前置知识
**$1.$ [深度优先搜索](https://baike.baidu.com/item/%E6%B7%B1%E5%BA%A6%E4%BC%98%E5%85%88%E6%90%9C%E7%B4%A2/5224976?fr=aladdin)**

**$2.$ [前缀和](https://blog.csdn.net/qq_45914558/article/details/107385862)**
## **30**分做法
直接暴力或当成背包问题做。

因为题目保证 $x \le 10^{18}$，所以比 $10^{18}$ 大的数是没有用的，所以我们在预处理数列时只要处理比 $10^{18}$ 小的数就好了，而题目描述中增长最慢的数列就是斐波那契数列了，但是斐波那契数列增长得非常快，所以不用担心空间炸了。
## **100**分做法
**还是爆搜。**

我们尝试给爆搜加上剪枝。

首先，我们写一个前缀和，假设已经选到第 $k$ 个数，那么如果将第 $k+1$ 到第 $n$ 个数全部选了但还是比 $x$ 小，立即返回。接着我们从大到小搜，因为最大的数 $a$ 和第二大的数 $b$ 中一定得选一个，否则无解。最后用 ```map``` 进行记忆化搜索，如果这个状态已经被搜过了，就直接用以前记录的答案。这样它的时间复杂度就不亚于背包。
## 代码
```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<set>
#include<queue>
#include<stack>
#include<vector>
#include<ctime>
#include<map>
#include<set>
#include<bitset>
#include<list>
#include<iomanip>

using namespace std;

const int mod=998244353;
long long a[157],sum[157];
map<long long,int>mp[157];
inline long long dfs(long long n,int m) {
    if(n<0||n>sum[m]) return 0;//可行性剪枝。 
    if(m==0) return n==0? 1:0;//判断是否是可行解。 
    if(mp[m].count(n)) return mp[m][n];//记忆化搜索。 
    return mp[m][n]=(dfs(n,m-1)+dfs(n-a[m],m-1))%mod;
}
int main() {
    int t;
    cin>>t;
    for(int i=1;i<=t;i++) {
        int m,q,k;
        cin>>m>>q;
        k=m;
        for(int j=1;j<=m;j++) cin>>a[j];
        while(a[k]<=1e18) { 
            a[++k]=0;
            for(int j=1;j<=m;j++) a[k]+=a[k-j];
        }
        for(int j=1;j<=k;j++) {
            sum[j]=sum[j-1]+a[j];//前缀和优化。 
            mp[j].clear();
        }
        for(int j=1;j<=q;j++) {
            long long x;
            cin>>x;
            cout<<dfs(x,k)<<"\n";
        }
    }
    return 0;
}
```

---

## 作者：COsm0s (赞：2)

类似于 [P4133 [BJOI2012]最多的方案](https://www.luogu.com.cn/problem/P4133)。

## 思路

记忆化搜索。

题目中提到 $x \leq 10^{18}$，则本题可用 long long 解决。

对于数列 $\lbrace {a_{cnt}} \rbrace$，这是一个变化过的斐波那契数列。而我们知道，斐波那契的增长是极快的，$86$ 项就可以超过 $10^{18}$。因此，我们可以暴力求出此数列中小于 $10^{18}$ 的部分。

设 $f_{i,j}$ 为用前 $i$ 项组成 $j$ 的方案数。当前项有选和不选两种情况，即 $f_{i-1,j}$ 和 $f_{i-1,j-a_i}$。那么转移方程就出来了：$f_{i,j}=f_{i-1,j}+f_{i-1,j-a_i}$。

注意剪枝：如果当前搜索到 $i$ 的比剩下的 $a_j$ 的和（即前缀和 $b_j$）还要大，那就直接返回。

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define rint register int
inline int read() {
	int x = 0, m = 1;
	char ch = getchar();
	while(!isdigit(ch)) {
		if(ch == '-') m = -1;
		ch = getchar();
	}
	while(isdigit(ch)) {
		x = x * 10 + ch - 48;
		ch = getchar();
	}
	return x * m;
}
inline void write(int x) {
	if(x < 0) {
		putchar('-');
		write(-x);
		return;
	}
	if(x >= 10) write(x / 10);
	putchar(x % 10 + '0');
}
const int N = 3e2 + 10, MOD = 998244353;
unordered_map<int, int> f[N];//unordered_map 复杂度约为 O(1) 
int a[N], b[N];
inline int dfs(int n, int m) {
	if (n < 0 || n > b[m]) return 0;//剪枝 
	if (m == 0 || n == 0)
		if(n == 0) return 1;
			else return 0;
	if (f[m].count(n)) return f[m][n];
	f[m][n] = (dfs(n, m - 1) + dfs(n - a[m], m - 1)) % MOD;
	return f[m][n];
}
//记搜 
signed main() {
	int T = read();
	while(T --) {
		int n = read(), m = read();
		for(rint i = 1; i <= n; i ++) a[i] = read();
		int cnt = n;
		while(1) {
			++ cnt;
			for(rint i = 1; i <= n; i ++) a[cnt] += a[cnt - i];
			if(a[cnt] > 1e18 || a[cnt] < 0) break;
		}//计算数列，当数列大于10^18时结束，注意有可能因爆long long而返回负值 
		for(rint i = 1; i <= cnt; i ++) b[i] = b[i - 1] + a[i];//前缀和 
		while(m --) write(dfs(read(), cnt)), puts("");
		//以下是清空操作 
		memset(a, 0, sizeof a);
		for(rint i = 1; i <= cnt; i ++) f[i].clear();
	}
	
	return 0;
}
```


---

## 作者：wangruibo20 (赞：1)

我们可以观察到，当原数列为斐波那契数列时增长速度最慢，而斐波那契数列第 $88$ 项就已经超过 $10^{18}$ 了（$\approx1.1\times 10^{18}$），所以一眼就能看出可以用暴搜。

码完暴搜过后交上去一看，“TLE 30pts”狠狠地拍在我脸上。

当然，纯粹的暴搜是肯定过不了这道题的（~~谁家出题人会这么良心~~），我们需要思考怎么去剪枝。

第一个肯定是从大的往小依次枚举（应该不会有人想不到吧）；

除开第一个第二眼（第一眼给暴搜了）就能看出来的应该是当 $n>\sum\limits_{i=1}^{m-1}a_i$ 时一定要选 $a_m$，在这里 $n$ 表示现在还未分掉的数字，$m$ 表示现枚举到 $a$ 序列的第 $m$ 项。

现在再去交，你会发现变成了 TLE 55pts。剩下的 35pts 该怎么拿呢？

记忆化。

是的，就是加个记忆化。

我们可以看出加上剪枝的暴搜还是会搜索到很多重复情况，所以加个记忆化就能顺利通过这道题了。

Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll t,n,m,q,f[305],s[305],i,c,mod=998244353;
map<ll,ll>x[305];
inline ll dfs(ll n,ll m){
	if(n==0)return 1;
	if(m==0)return 0;
	if(x[m].count(n))return x[m][n];
	if(n>s[m-1])return x[m][n]=dfs(n-f[m],m-1);
	return x[m][n]=((n>=f[m]?dfs(n-f[m],m-1):0)+dfs(n,m-1))%mod;
}int main(){
	scanf("%lld",&t);
	while(t--){
		c=0;
		s[0]=0;
		scanf("%lld%lld",&m,&q);
		for(i=1;i<=m;i++)scanf("%lld",&f[i]),s[i]=s[i-1]+f[i];
		for(;f[i-1]<=1e18&&f[i-1]>0;i++){
			f[i]=0;
			for(ll j=1;j<=m;j++)f[i]+=f[i-j];
			s[i]=s[i-1]+f[i];
		}while(q--){
			scanf("%lld",&n);
			printf("%lld\n",dfs(n,i-1));
		}for(ll j=i-1;j;j--)x[j].clear();
	}return 0;
}
```



---

## 作者：Butterfly_qwq (赞：1)

[博客食用效果更佳](https://www.luogu.com.cn/blog/663638/solution-p8565)

[题目传送门](https://www.luogu.com.cn/problem/P8565)

注意到 $1\le x\le 10^{18}$，而数列 $a$ 增长速度肯定大于斐波拉契数列，而斐波拉契数列第 $86$ 项，已经超过 $10^{18}$ 了。所以可以求出所有 $a_i<10^{18}$ 的 $a_i$ 的值。

那么就可以使用记忆化搜索，为了不 MLE，使用了 unordered_map。

设 $dp_{i,j}$ 为用前 $i$ 个数字组成 $j$ 的方案数，那么易得动态转移方程：$dp_{i,j}=dp_{i-1,j}+dp_{i-1,j-a_i}$。

Code:

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[305],s[305];
unordered_map<int,int>h[305];
int dfs(int x,int n)
{
	if(x<0||x>s[n])return 0;
	if(x==0)return 1;
	else if(n==0)return 0;
	if(h[n].count(x))return h[n][x];
	h[n][x]=(dfs(x,n-1)+dfs(x-a[n],n-1))%998244353;
	return h[n][x]=(dfs(x,n-1)+dfs(x-a[n],n-1))%998244353;
}
signed main()
{
   int t;
   cin>>t;
   while(t--)
   {
   	int m,q;
   	cin>>m>>q;
   	for(int i=1;i<=m;i++)cin>>a[i];
   	int n=m;
   	while(1)
   	{
   		n++;
   		for(int i=1;i<=m;i++)a[n]+=a[n-i];
   		if(a[n]>1e18||a[n]<0)break;
		}
		for(int i=1;i<=n;i++)s[i]=s[i-1]+a[i];
		int x;
		while(q--)
		{
			cin>>x;
			cout<<dfs(x,n)<<'\n';
		}
		memset(a,0,sizeof(a));
		for(int i=1;i<=n;i++)h[i].clear();
	}
}
```

时间：不吸氧和吸氧都是 370ms 左右。

---

## 作者：喵仔牛奶 (赞：1)

## $\mathcal{P}reface$

这是一篇近似暴力的题解。学习正解勿入。

## $\mathcal{S}olution$

题目说说 $x\leq10^{18}$，说明有用的 $\{a_n\}$ 不会爆 `long long`。然后这个里面增长最慢的就是斐波那契数列，斐波那契数列增长有多快大家应该知道吧？那直接暴力把 $n$ 和 $\{a_n\}$ 处理出来，处理到爆 `long long` 为止就可以了。

然后就是一个背包问题，使用 `unordered_map` 记忆化搜索即可。

令 $f_{i,j}$ 为前 $i$ 个数组成 $j$ 的方案数。

$$f_{i,j}=(f_{i-1,j}+f_{i-1,j-a_i})\bmod998244353$$

不过这样不剪枝肯定还是 T 飞，我们可以把前缀和预处理出来，然后逆向搜索，如果当前搜索到的比剩下的和还要大，那就直接剪枝掉。

时间复杂度？应该是玄学，但是类似 $\mathcal{O}(Tq\log x)$。

## $\mathcal{C}ode$

记忆化搜索，[277ms](https://www.luogu.com.cn/record/88404468)。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1005, mod = 998244353;
unordered_map<ll, ll> f[N]; // 记忆化
ll a[N], sum[N], T, Q, n, cnt, x;
ll dfs(ll n, int m) {
	if (n < 0 || n > sum[m]) return 0; // 剪枝
	if (!m || !n) return !n ? 1 : 0;
	if (f[m].count(n)) return f[m][n];
	return f[m][n] = (dfs(n, m - 1) + dfs(n - a[m], m - 1)) % mod;
}
int main() {
	cin >> T;
	while (T --) {
		memset(a, 0, sizeof a);
		cin >> n >> Q;
		for (int i = 1; i <= n; i ++)
			cin >> a[i], sum[i] = sum[i - 1] + a[i];
		for (cnt = n + 1; ; cnt ++) {
			for (int i = 1; i <= n; i ++)
				a[cnt] += a[cnt - i];
			sum[cnt] = sum[cnt - 1] + a[cnt];
			if (sum[cnt] < 0) break; // 爆 long long 说明够了
		}
		cnt --; // 当前 cnt 是爆 long long 的，记得减 1
		while (Q --)
			cin >> x, cout << dfs(x, cnt) << '\n';
		for (int i = 1; i <= cnt; i ++) // 记得清空
		    f[i].clear(); 
	}
	return 0;
}
```


---

## 作者：rq_kyz (赞：0)

# P8565 Sultan Rage 题解

### 传送门

[P8565 Sultan Rage](https://www.luogu.com.cn/problem/P8565)

---

### 题意

有一个数列，满足每一项为前 $m$ 项之和，并给出第 $1$ 到 $m$ 项，问一个数字表示为数列中的一些数之和的方案数。

---

### 分析

因为 $m\ge2$，所以数列最小的情况会退化成一个斐波那契数列，但尽管是斐波那契数列，增长速度也是指数级别的，所以其实最终的数列只有三百个左右，再大就会超过 $10^{18}$。

所以本题我们完全可以使用 DFS，但如果使用不加任何剪枝的 DFS 会喜提 TLE 30 分，所以剪枝是必不可少的，~~毕竟不会有这么好心的出题人的~~。

首先可以想到的是，我们倒着 DFS，使它的减小速度更快，并用**前缀和**来优化时间，如果当前可以使用的只有数列的前 $n$ 项，并且数字为 $x$，我们可以判断：如果 $x>\sum_{i=1}^{n-1}a_i$，则说明当前在组成 $x$ 的数字中必有 $a_n$，那么就可以减少一半的时间。

但光是这样还是不够，那么应该如何优化呢？注意到，数列 $a_i$ 的递推式为 $a_i=\sum_{j=i-m}^{i-1}$，说明选一个 $a_i$ 和选择 $a_{i-m}$ 到 $a_{i-1}$ 的所有数字减小的部分是一样的。换句话说，在 DFS 的过程中会出现大量的重复，所以我们可以使用**记忆化**防止重算。这里注意到，$x$ 的值域很大，但真正使用的并不多，所以可以使用 map 进行存储。

那么，本题结束，~~撒花~~！

---

### 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll p=998244353;
ll a[301],b[301];
map<ll,ll> m[301];
ll dfs(ll n,ll x){
	if(!x)
		return 1;
	if(!n)
		return 0;
	if(m[n].count(x))
		return m[n][x];
	if(x>=a[n])
		m[n][x]+=dfs(n-1,x-a[n]);
	if(x<=b[n-1])
		m[n][x]+=dfs(n-1,x);
	m[n][x]=m[n][x]<p?m[n][x]:m[n][x]-p;
	return m[n][x];
}
int main(){
	ll T;
	scanf("%lld",&T);
	while(T--){
		ll n,q;
		scanf("%lld%lld",&n,&q);
		a[n+1]=0;
		for(ll i=1;i<=n;i++){
			scanf("%lld",&a[i]);
			b[i]=b[i-1]+a[i];
			if(a[n+1]+a[i]<=1e18)
				a[n+1]+=a[i];
		}
		if(a[n+1]<=1e18){
			b[n+1]=b[n]+a[n+1];
			for(ll i=n+2;1;i++){
				if(a[i-1]*2>1e18+a[i-n-1]){
					n=i-1;
					break;
				}
				a[i]=a[i-1]*2-a[i-n-1];
				b[i]=b[i-1]+a[i];
			}
		}
		for(ll i=1;i<=n;i++)
			m[i].clear();
		while(q--){
			ll x;
			scanf("%lld",&x);
			printf("%lld\n",dfs(n,x));
		}
	}
	return 0;
}
```

---

### 其他

[双倍经验](https://www.luogu.com.cn/problem/P4133)

---

## 作者：MornStar (赞：0)

# Sultan Rage
[题面](https://www.luogu.com.cn/problem/P8565)
```
第一眼：紫题，再见。

第二眼：爆搜。
```
总体思想跟 [P4133 [BJOI2012]最多的方案](https://www.luogu.com.cn/problem/P4133)差不多。

求值，前缀和，记忆化搜索（但是这次不开 long long 见了祖宗）。

其中记忆化可以使用 map 实现

详细解释放在代码里：
```cpp
#include<bits/stdc++.h>
#define mod 998244353
#define inf 1e18
using namespace std;
long long read(){
	long long r=0,f=1;
	char c;
	c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9')r=(r<<1)+(r<<3)+c-'0',c=getchar();
	return r*f;
}
long long a[180],sum[180];//再多long long也装不下。
map<pair<long long,int>,long long>mi;。
long long dfs(long long x,long long y){
	if (x<0||x>sum[y]) return 0;
	if(!y)	return !x;
	pair<long long,int> p=make_pair(x,y);
	if(mi.count(p))	return mi[p];
	return mi[p]=(dfs(x-a[y],y-1)+dfs(x,y-1))%mod;
}
int main(){
	long long t=read();
	while(t--){
		long long m=read(),q=read();
		for(int i=1;i<=m;i++){
			a[i]=0,a[i]=read();
			sum[i]=0,sum[i]=sum[i-1]+a[i];
		}
		long long k=m;
		while(a[k]<=inf){
			a[++k]=0;
			a[k]=sum[k-1]-sum[k-m-1];//小优化，使用前缀和计算数组下一个数。
			sum[k]=sum[k-1]+a[k];//前缀和
		}
      		mi.clear();//每组数据清空记忆。
		while(q--){
			long long que=read();
			cout<<dfs(que,k)<<endl;
		}
	}
}
```
[提交记录](https://www.luogu.com.cn/record/103488741)


---

## 作者：出言不逊王子 (赞：0)

好题，并且让人难以想象的是，这是暴力。

考虑最劣的情况，就是 $m=100$ 且前 $100$ 个数都是 $1$。

在这种情况下，数列也只需要一百多位就会被撑到 $10^{18}$。

那么我们考虑 $f_{i,j}$ 表示当前选到了前 $j$ 项且和为 $i$ 的方案数。

不难发现，若 $i=0$ 则 $f_{i,j}=1$，就是都不选。

否则 $f_{i,j}=f_{i,j-1}+f_{i-a_j,j-1}$，分别代表选和不选的方案数。

代码写起来也非常简单。

但是你要注意一个剪枝：若 $i$ 大于 $\sum_{k=1}^ja_k$，则这个 $i$ 就太大了，对于的方案数就是 $0$。

因为状态收敛很快，所以实际上并不能跑到次方级别，基本上就是一条线加几根枝条这样的。

因为斐波那契数列收敛的太快了，基本上就是 $f_{i-1}=\frac {f_i}2$ 这个级别的，所以他实际上可能很多时候刚下来就会发现又超过前缀和了。

代码：

```
#include<bits/stdc++.h>	
#define fs(i,x,y,z) for(int i=x;i<=y;i+=z)
#define ft(i,x,y,z) for(int i=x;i>=y;i+=z)
#define int long long
#define ull unsigned long long
#define db double
#define ms(a,b) memset(a,b,sizeof(a))
#define sz(a) sizeof(a)
using namespace std;
const int rw[]={-1,0,1,0,-1,1,-1,1},cl[]={0,1,0,-1,-1,1,1,-1};
const int N=100001,inf=998244353ll;
inline int read(){
	int date=0,w=1;char c=0;
	while(c<'0'||c>'9'){if(c=='-')w=-1;c=getchar();}
	while(c>='0'&&c<='9'){date=date*10+c-'0';c=getchar();}
	return date*w;
}
map<pair<int,int>,int> mp;
int m,q,n;
int a[N],pre[N];
inline int dfs(int cur,int nums){//当前和为C，考虑到了第N个 
	if(cur<0||nums<0||cur>pre[nums]) return 0;
	if(cur==0||nums==0) return bool(cur==0);
	pair<int,int> now={cur,nums}; 
	if(mp.count(now)) return mp[now];
	return mp[now]=(dfs(cur,nums-1)+dfs(cur-a[nums],nums-1))%inf;
} 
void mian(){
	m=read(),q=read(),n=m;fs(i,1,m,1) a[i]=read();
	while(a[n]<=1e18){
		a[++n]=0;
		fs(j,1,m,1) a[n]+=a[n-j];
	}
	//fs(i,1,n,1) printf("%lld ",a[i]);puts("");
	mp.clear();
	fs(i,1,n,1) pre[i]=pre[i-1]+a[i];//,mp[i].clear();//前缀和
	//fs(i,1,n,1) printf("%lld ",pre[i]);printf("!%lld\n",n);
	while(q--){
		int x=read();
		printf("%lld\n",dfs(x,n));//和为x，当前抽到n项 
	} 
}
signed main(){
	int t=read();while(t--) mian();
	return 0;
}
```

---

## 作者：olegekei (赞：0)

题目中给定的每个询问 $x \le 10^{18}$，而数列 $\{a_{\text{cnt}}\}$ 是一个改版的斐波那契数列，可以考虑先求出在 long long 范围内的完整的 $\{a_{\text{cnt}}\}$ 序列，然后进行记忆化搜索。

## 搜索：

```search(x,y)``` 表示当前已经枚举到下标 $y$，当前数还剩下 $x$，枚举 $a_y$ 选或不选。

如果 $x=0$ 则搜到了一种方案。

## 剪枝：

光是记忆化搜索肯定是会超时的，我们需要一些剪枝来提高效率。

处理数列的前缀和，如果当前取到第 $j$ 个数，而剩下的 $pre_{j-1}$ 已经小于剩余的值 $x$，则当前的 $a_j$ 一定要取，才能保证后边的 $j-1$ 能够取到方案。

而如果 $x < a_j$，则 $a_j$ 一定不能取。

最后小型背包预处理 $dp_i$ 记录前 $n$ 个数（即最开始给定的数列 $\{a_n\}$）能够组成 $i$ 的方案数，当搜到的位置 $j=n$ 时直接返回 $dp_x$ 即可。

实测效率很高，[88ms](https://www.luogu.com.cn/record/91125839)。

## 代码：

```cpp
#include<map>
#include<iostream>
#define int unsigned long long
using namespace std;
int n,m,cnt;
int a[200];
int pre[200];
int dp[10001];
map<int,int>p[200];
const int mod=998244353;
int search(int x,int j){
	if(j==n)return dp[x]%mod;
	if(!x)return 1;
	if(x<a[j])return search(x,j-1);
	if(x>pre[j-1])return search(x-a[j],j-1)%mod;
	if(p[j].count(x))return p[j][x];
	return p[j][x]=(search(x-a[j],j-1)+search(x,j-1))%mod;
}
main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  int t;
  cin>>t;
  dp[0]=1;
  while(t--){
      cin>>n>>m;
      for(int i=1;i<=n;i++){cin>>a[i];}
      for(int i=1;i<=n;i++){pre[i]=pre[i-1]+a[i];}
      for(int i=1;i<=pre[n];i++)dp[i]=0;
      for(int i=1;i<=n;i++){
          for(int j=pre[i];j>=a[i];j--){
              dp[j]=(dp[j]+dp[j-a[i]])%mod;
          }
      }
      cnt=n;
      while(pre[cnt]-pre[cnt-n]<=1e18){
          a[cnt+1]=pre[cnt]-pre[cnt-n];cnt++;pre[cnt]=pre[cnt-1]+a[cnt];
      }
      for(int i=1;i<=cnt;i++)p[i].clear();
      for(int i=1,x;i<=m;i++){
          cin>>x;
          cout<<search(x,cnt)%mod<<'\n';
      }
  }
return 0;
}
```

---

