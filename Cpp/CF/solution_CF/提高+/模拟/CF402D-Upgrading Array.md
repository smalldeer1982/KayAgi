# Upgrading Array

## 题目描述

给一个有n个数 a[1],a[2],…,a[n] 的数列打分，你认为 b[1],b[2]…,b[m] 是不好的质数。定义这个序列的分值为各个数的分值之和，设 x 的分值为 f(x)，f(x)=f(x/p)+k （p 为 x 的最小质因子；若 p 为不好的质数， k 取 −1 ，否则 k 取 +1 ； f(1)=0 ）。
你想让序列的分值更大，可以反复进行一项操作：$a[1],a[2],a[3],...,a[i](i<=n)$ 的每个数除以它们的最大公约数。请问你能让序列的得分最大为多少。

## 样例 #1

### 输入

```
5 2
4 20 34 10 10
2 5
```

### 输出

```
-2
```

## 样例 #2

### 输入

```
4 5
2 4 8 16
3 5 7 11 17
```

### 输出

```
10
```

# 题解

## 作者：CarroT1212 (赞：6)

### 题目大意

给定一个长度为 $n$ 的序列 $a$ 和长度为 $m$ 的仅含质数的序列 $b$。$b$ 中的数被称为坏质数。规定 $f(1)=0,f(x)=f(x/p)+k$，其中 $p$ 为 $x$ 的最小质因数，若 $p$ 在 $b$ 中出现过，则 $k=-1$，否则 $k=1$。你可以进行若干次操作：选定一个 $i\,(1 \le i \le n)$，使 $a_1,a_2,\cdots,a_i$ 都除以它们的最大公因数。问操作后 $f(a_1)+f(a_2)+\cdots+f(a_n)$ 最大是多少。（$1 \le n,m \le 5000$，$1 \le a_i\le 10^9$，$2 \le b_i \le 10^9$）

------------

### 解法分析

这题主要就是题意比较抽象，其实仔细看一下过程就会发现 $f(x)$ 就是 $x$ 的所有质因数中好质数和坏质数的个数之差。

所以我们进行操作的目的就是通过除以前 $i$ 个数的 $\gcd$ 把 $a_i$ 的坏质因数灭掉一些，同时注意不要灭掉太多的好质因数。

首先摆一些显然的结论：$g_i \mid g_j\,(i>j)$；操作一定是从后往前进行的，因为如果从前往后的话，$\gcd$ 一次操作之后就会变成 $1$，后面的直接玩完。

考虑从后往前枚举 $i$，判断是否要对 $a_{1\sim i}$ 进行操作。猜个贪心：设目前的操作状态下 $\gcd\{a_1,a_2,\cdots,a_i\}=g_i$，则如果 $f(g_i)<0$，就说明除以一次 $g_i$ 可以灭掉的坏质因数的个数是比好质因数多的，这时啥都不管直接把 $a_{1\sim i}$ 都除以 $g_i$（同时 $g_{1\sim i-1}$ 也会除以 $g_i$）。稍微想一想，这个贪心是对的，确实可以得到最优答案。因为我们把所有能增加答案的操作都执行了一遍。而且可以发现，找到一个使答案增加的操作就直接执行是比跳过其中的某几个操作更优的，如果我们留着一个可以使答案增加的操作不做，去做前面的操作，因为这题操作的效果可以叠加，则前面的操作得到的效果和若干个后面的操作被执行导致影响前面位置的效果基本可以看作是相同的，而这些后面的操作中，很可能会混入几个使答案减小的操作，不优，不如直接把那些使答案增加的操作都先做了。

到这里写完交上去又会出现另一个严重的问题：它 T 了。确实，$O(N\sqrt{10^9})$ 的复杂度本来就相当危险，再带点 STL 的 $\log$，复杂度嗖的一下直接起飞，$1\text{s}$ 时限不炸才怪，打上两个优化才能过：开个 map 记忆化一下 $f(x)$ 的结果；分解质因数的时候如果 $x$ 已经等于 $1$ 了就直接跳出。

------------

### 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
#define ld long double
#define pb push_back
#define pii pair<int,int>
#define pll pair<ll,ll>
#define vo void()
using namespace std;
const int N=5007,M=4e4+7;
int n,m,a[N],b[N],gcd[N],ans;
vector<int> prm;
map<int,int> mp,rem;
void ola() {
	vector<int> vis(M);
	for (int i=2;i<M;i++) {
		if (!vis[i]) prm.pb(i);
		for (int j:prm) { if (i*j>M) break; vis[i*j]=1; if (i%j==0) break; }
	}
}
int f(int x) {
	if (rem.count(x)) return rem[x];
	int ret=0,y=x;
	for (int i:prm) {
		int cnt=0;
		while (y%i==0) y/=i,cnt++;
		ret+=cnt*(mp[i]?-1:1);
		if (y==1) break;
	}
	if (y>1) ret+=(mp[y]?-1:1);
	return rem[x]=ret;
}
int main() {
	ola();
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++)
		scanf("%d",&a[i]),gcd[i]=__gcd(gcd[i-1],a[i]);
	for (int i=1;i<=m;i++) scanf("%d",&b[i]),mp[b[i]]=1;
	for (int i=1;i<=n;i++) ans+=f(a[i]);
	for (int i=n,cnt=1,tmp;i;i--)
		if ((tmp=f(gcd[i]/cnt))<0) ans-=tmp*i,cnt=gcd[i];
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：54Teddy (赞：3)

题意:

给一个数组，和一个bad prime集合，可以无数次地让1到i这些所有数字除以他们的gcd，然后要求$\sum_{i=1}^{n}f(a[i])$的最大值，其中

$f(x) = f(\frac{x}{p}) + 1$, `p`为`x`的最小质数，且`p`不为坏质数

$f(x) = f(\frac{x}{p}) - 1$, `p`为`x`的最小质数，且`p`为坏质数

思路:~~赤裸裸~~的贪心题

从后往前更新，能减小就减小。

$gcd[i]$:前缀最大公因数

用set来保存坏质数，map来保存答案

总体来说：贪心+记忆化搜索

ps:本代码luogu会TLE，但亲测原oj上能过(~~第一次MLE了~~)

```cpp
#include <map>
#include <set>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define inf 0x3fffffff
#define maxn 5005
#define rep(i,a,b) for (int i = a; i <= b; i++)
#define ped(i,a,b) for (int i = a; i >= b; i--)
#define pb push_back
using namespace std;
int n, m, ans = 0;
int p, q, t, bad;
int a[maxn], g[maxn] = {0};
map <int, int> res;
set <int> prime;
inline int read () {
	char ch = getchar();
	int t = 0, f = 1;
	while (ch < '0' || ch > '9') {
		if (ch == '-') f = -1;
		ch = getchar();
	}
	while ('0' <= ch && ch <= '9') t = t * 10 + ch - '0', ch = getchar();
	return t * f;
}
int getbad (int k) { return k * (-2) + 1; }
int f (int x) {
	if (x <= 1) return 0;
	if (prime.count(x)) return -1;
	if (res[x]) return res[x];
	q = x, t = 0;
	for (int i = 2; i * i <= q; i++) {
		bad = getbad(prime.count(i));
		while (x % i == 0) x /= i, t += bad;
	}
	if (x != 1) bad = getbad(prime.count(x)), t += bad;
	return (res[q] = t);
}
int main () {
	n = read(), m = read();
	rep (i, 1, n) a[i] = read();
	rep (i, 1, m) prime.insert(read());
	rep (i, 1, n) g[i] = __gcd(g[i-1], a[i]);
	rep (i, 1, n) ans += f(a[i]);
	ped (i, n, 1) {
		p = f(g[i]);
		if (p < 0) {
			ans -= p * i;
			rep (j, 1, i) g[j] /= g[i];
		}
	}
	printf ("%d\n", ans);
	return 0;
} 
```

---

## 作者：az__eg (赞：2)

感谢 @[fairyland](https://www.luogu.com.cn/user/251992) 指正错误。

**题意**：

给你一个长度为 $n$ 的序列 $a$，再给你一个只包含素数且长度为 $m$ 的 $b$，每次对于 $1 \leq i \leq n$ 可以将 $a_1$ 到 $a_i$ 除以他们的最大公约数，并定义一个函数 $f$，$f(x)$ 表示 $x$ 的质因数不是 $b$ 的元素的数量减去是 $b$ 的元素的数量，求怎样改变才能使 $\sum\limits^{n}_{i=1}{f(a_i)}$ 最小。

**解法**：

对于 $a_1$ 到 $a_i$，如果我们已经将 $a_1$ 到 $a_{i-1}$ 除以了他们的最大公约数，那么显然 $a_1$ 到 $a_i$ 的最大公约数一定是 $1$。所以我们应当先判断是否除以 $a_1$ 到 $a_i$ 的最大公约数，再考虑是否除以 $a_1$ 到 $a_{i-1}$ 的最大公约数，所以我们的 $i$ 从 $n$ 到 $1$ 遍历，每次算出当前的 $f(\gcd{(a_1,a_2,...,a_i)})$，如果小于 $0$，说明除以他们的最大公约数后，$\sum\limits^{n}_{i=1}{f(a_i)}$ 会增长，所以我们可以除。总时间复杂度 $O(n^2 \log n)$。

**代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int a[5001];
int b[5001];
unordered_map<int,bool> mp;
bool check(int x);
void work(int dq);
signed main()
{
	int i,j;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
	}
	for(i=1;i<=m;i++)
	{
		scanf("%d",&b[i]);
		mp[b[i]] = true;
	}
	for(i=n;i>=1;i--)
	{
		work(i);//判断是否可以执行并执行操作
	}
	int ans = 0;
	for(i=1;i<=n;i++)
	{
		for(j=2;j*j<=a[i];j++)
		{
			if(a[i]%j==0)
			{
				while(a[i]%j==0)
				{
					a[i]/=j;
					if(mp.find(j)!=mp.end())
					{
						ans--;
					}
					else
					{
						ans++;
					}
				}
			}
			
		}
		if(a[i]>1)
		{
			if(mp.find(a[i])!=mp.end())
			{
				ans--;
			}
			else
			{
				ans++;
			}
		}
	}
	printf("%d",ans);//求出最后答案
	return 0;
}
void work(int dq)
{
	int gys = a[1];//公约数
	int i,j;
	for(i=2;i<=dq;i++)
	{
		gys = __gcd(gys,a[i]);
	}
	int zc = gys;
	int cnt1 = 0;
	int cnt2 = 0;
	for(i=2;i*i<=gys;i++)
	{
		if(gys%i==0)
		{
			while(gys%i==0)
			{
				if(mp.find(i)!=mp.end())
				{
					cnt1++;
				}
				else
				{
					cnt2++;
				}
				gys /= i;
			}
		}
	}
	if(gys>1)
	{
		if(mp.find(gys)!=mp.end())
		{
			cnt1++;
		}
		else
		{
			cnt2++;
		}
	}
	if(cnt1>=cnt2)
	{
		for(i=1;i<=dq;i++)
		{
			a[i]/=zc;
		}
	}
}
```


---

## 作者：kma_093 (赞：2)

## 题目链接：
[CF402D](https://www.luogu.org/problem/CF402D)

---

## 题目分析：

首先考虑一下怎么求每个数的分数。把每个数分解到最后会发现它的坏质因子对它分数的贡献是$-1$，好质因子对它分数的贡献是$1$，那么最后的分数就是好质因数-坏质因数

然后想一想怎么操作。我们的最优答案是把所有能除掉的负数分数的$gcd$全部除掉，一个很显然的贪心是从后往前操作，因为前面操作了之后后面的$gcd$就恒为$1$，操作不下去了

另一个$point$是操作是显然正确的，因为后面的操作会除掉前面操作原本的$gcd$的一部分，而剩下的一部分应该被除掉的会在之后的贪心中被除去

举个例子

假设区间$[1, 5]$需要被除掉的$gcd$是$12$，区间$[1, 9]$需要被除掉的$gcd$是$4$，那么在$9$号位上除去$4$后再在$5$号位上除去$3$即可

处理一下前缀$gcd$，从后向前贪心，并记录当前已经除去了多少，每次进行操作之前要先除去这个量。（另：素数只需筛到$sqrt(1e9)$即可，后面的可以暴力判断），对于每一位，质因数分解一下当前位置上的前缀$gcd$并计算它的分数，如果$<0$就除掉它

用$bitset$记录坏质数


## 代码：

```cpp
#include<bits/stdc++.h>
#define N (100000 + 5)
using namespace std;
int n, m, prime[N], tot, ans, g[N];
bool vis[N];
bitset <1000000005> S;inline int read() {
	int cnt = 0, f = 1; char c = getchar();
	while (!isdigit(c)) {if (c == '-') f = -f; c = getchar();}
	while (isdigit(c)) {cnt = (cnt << 3) + (cnt << 1) + (c ^ 48); c = getchar();}
	return cnt * f;
}
int a[N], b[N];
int gcd(int a, int b) {return b ? gcd(b, a % b) : a;}
void init() {
	for (register int i = 2; i <= N - 5; ++i) {
		if (!vis[i]) vis[i] = 1, prime[++tot] = i;
		for (register int j = 1; j <= tot && prime[j] * i <= N - 5; ++j) {
			vis[i * prime[j]] = 1;
			if (i % prime[j] == 0) break;
		}
	}
}

int divide(int x) {
	int ans = 0;
	for (register int i = 1; i <= tot && prime[i] * prime[i] <= x; ++i) {
		while (x % prime[i] == 0) ans += S[prime[i]] ? -1 : 1, x /= prime[i];
	}
	if (x > 1) ans += S[x] ? -1 : 1;
	return ans;
}
int main() {
	n = read(), m = read();
	for (register int i = 1; i <= n; ++i) a[i] = read();
	for (register int i = 1; i <= m; ++i) S[read()] = 1;
	init();
	for (register int i = 1; i <= n; ++i) ans += divide(a[i]);
	for (register int i = 1; i <= n; ++i) g[i] = gcd(g[i - 1], a[i]);
	int div = 1;
	for (register int i = n; i >= 1; --i) {
		g[i] /= div;
		int x = divide(g[i]);
		if (x < 0) ans += i * (-x), div *= g[i];
	}
	printf("%d\n", ans);
	return 0;
}
```

最后推销一下自己的$blog$：[$kma's\ blog$](https://www.cnblogs.com/kma093/)

---

## 作者：shroud777 (赞：2)

**题目描述：**

给出一个长度为 $n$ 的序列 $a_1,a_2,...,a_n$ 和 $m$ 个被认为不好的质数

定于 $f(x)$ 为 $x$ 的分值，并且满足 $f(x)=f(\frac x p)+k$（$p$ 为 $x$ 的最小质因子，当 $p$ 为不好的质数是，$k=-1$，否则 $k=1$，$f(1)=0$）

定义序列的分值为 $\sum_i f(a_i)$，现在可以进行若干次如下操作，使得序列的分值最大：

对于每一次操作可以选择一个下标 $i$，使得 $a_1,a_2,...,a_i$ 每个数都除以 $\gcd(a_1,a_2,...,a_i)$

求操作后可能达到的最大序列分值

$1 \leq n \leq m \leq 5000$

$1 \leq a_i \leq 10^9$ 

保证 $m$ 个给出的都是质数并且按照升序给出

**solution:**

唯一的两篇好像都是贪心做法，我来贡献一发DP

根据唯一分解定理 $x=p_1^{c_1} \cdot p_2^{c_2} ... p_k^{c_k}$， $f(x)=f(\frac x p)+k$ 就是分解质因子的过程，所以 $f(x)=\sum_i p_i \cdot (-1)^{[c_i==bad prime]}$

显然 $1-i$ 的 $gcd$ 随着 $i$ 增大而单调递减。并且对于任意 $i$，满足所有  $j(j<i)$ 满足 $\gcd(a_1,a_2,...a_i)$  的质因子是 $\gcd(a_1,a_2,..a_j)$  子集

考虑在 $1-i$ 上操作的贡献，对于每个 $i$，只有第一次进行操作才会产生贡献 $i *-f(\gcd(a_1,a_2,..,a_i))$，所有 $1-i$ 的数已经互质了，无法继续产生贡献。并且操作下标大于 $i$ 的操作显然也受到这 $n$ 个互质的数的影响而不会产生任何贡献。因此从前往后操作的意义相当于只进行了第一次操作。

考虑从后往前操作，根据上述gcd单调子集性质，可以发现每次操作时，当前位置剩余的 最小公共质因子集合是当前下标 $i$ 的 $\gcd(a_1,a_2,...,a_i)$ 的质因子集合减去上一次操作位置 $j$ 的 $\gcd(a_1,a_2,...,a_j)$ 的质因子集合。这样不太好统计，我们可以从前往后看这个过程（这里依旧是从后往前操作，只是换个角度看这个问题），发现前面的操作不会影响当前的质因子（因为集合单调减小），只会影响贡献数量，设上一次操作下标为 $j$，当前下标为 $i$，则贡献为 $(i-j) *-f(\gcd(a_1,a_2,..,a_i))$

我们依旧是按照从前往后的角度看从后往前操作的过程，设 $dp_i$ 代表操作完前 $i$ 个数的**增加的最大分值**，$g=-f(\gcd(a_1,a_2,..,a_i))$，显然转移方程为 $dp_i=max \{ dp_j+g*(i-j) \}(0 \leq j < i)$，答案就是 $\sum_i f(a_i)+dp_n$

这题数据范围高达 $1e9$，质因数分解前最好筛一下质数。。。一开始直接暴力分解质因数T飞了


**code:**

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn=5005;
const int N=1e5+10;

int n,m;
ll a[maxn],b[maxn];
ll f[maxn],ans=0;
int vis[N],p[N],tot=0;


unordered_map<int,bool> pri;


int solve(ll x){
    int ans=0;
    for(int i=1;p[i]*p[i]<=x;i++){
        if(x%p[i]==0){
            int cnt=0;
            while(x%p[i]==0) x/=p[i],cnt++;
            if(pri[p[i]]) ans-=cnt;
            else ans+=cnt; 
        }
    }
    if(x!=1){
        if(pri[x]) ans--;
        else ans++;
    }
    return ans;
}

void sieve(int n){
    for(int i=2;i<=n;i++){
        if(!vis[i]) vis[i]=i,p[++tot]=i;
        for(int j=1;j<=tot;j++){
            if(p[j]>vis[i]||p[j]>n/i) break;
            vis[p[j]*i]=p[j];
        }
    }
}

int main(){
    sieve(1e5);
    scanf("%d %d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
    ll x;
    for(int i=1;i<=m;i++){
        scanf("%lld",&x);
        pri[x]=1;
    }
    for(int i=1;i<=n;i++) ans+=solve(a[i]);
    ll res,gcd,temp;
    ll mx=0;
    for(int i=1;i<=n;i++){
        if(i==1) gcd=a[1];
        else gcd=__gcd(gcd,a[i]);
        int tot=-solve(gcd);
        f[i]=i*tot;
        for(int j=0;j<i;j++){
            f[i]=max(f[i],f[j]+(i-j)*tot);
        }
        mx=max(f[i],mx);
    }
    printf("%lld\n",ans+mx);
    return 0;
}
```



---

## 作者：Shadows_of_Twilight (赞：1)

## 前言

VP 时场切了这题，写个题解留念。

## 题意

给定一个长度为 $n$ 的序列 $a$。

定义 $f(x) = f(\frac{x}{p}) + k$。其中 $p$ 是 $x$ 的最小质因数，如果 $p$ 在坏质数集合内则 $k = -1$，否则 $k = 1$。总共有 $m$ 个坏质数。

你可以对序列 $a$ 进行操作，每次操作你选择一个 $r(1 \le r \le n)$，使得对于每个 $1 \le i \le r$ 的 $a_i$ 除以 $\gcd(a_1,a_2,a_3...,a_r)(1\le i \le r)$。

现在要使 $\sum_{i = 1} ^ n f(a_i)$ 最大。

## 思路

显然 $f(x)$ 为 $x$ 分解质因数中的每个质因数产生的价值。那么我们可以在 $\mathcal{O}(\sqrt{x})$ 的时间复杂度内求出 $f(x)$ 了。

考虑预处理出序列 $a$ 的前缀最大公约数 $s$，先算出不做任何操作的答案，然后我们贪心的从后往前操作，如果对当前位置操作会使答案更优，那么执行此操作，并修改答案。对当前位置操作后对答案的影响是 $f(s_i)$ 显然这样贪心下去是有正确性的。

判断质因数是不是坏质数的时候用 `unordered_map` 就可以了。

时间复杂度 $\mathcal{O}(n\times\sqrt{X})$。($X$ 即为最大的数)

## 注意事项

十年 OI 一场空，`define int long long` 见祖宗。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
long long ans, res, n, m, a[5005], s[5005], b[5005];
unordered_map<int, int>mp;
inline int f(int x)//计算价值
{
    long long tmp = 0;
    for (int j = 2; j * j <= x; j++)
    {
        if (x % j == 0)
        {
            int k = 0;
            if (mp[j])
                k = -1;
            else
                k = 1;
            while (x % j == 0)
            {
                x /= j;
                tmp += k;
            }
        }
    }
    if (x > 1)
        tmp += (mp[x] ? -1 : 1);
    return tmp;
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        s[i] = __gcd(s[i - 1], a[i]);//预处理
    }
    for (int i = 1; i <= m; i++)
    {
        cin >> b[i];
        mp[b[i]] = 1;
    }
    res = 0;
    for (int i = 1; i <= n; i++)
    {
        res = res + f(a[i]);//计算不做操作的价值
    }
    ans = res;
    res = 1;
    for (int i = n; i >= 1; i--)
    {
        s[i] /= res;//修改当前值
        if (ans - f(s[i]) * i >= ans)//判断是否操作
        {
            ans -= f(s[i]) * i;
            res *= s[i];
        }
    }
    cout << ans << '\n';
    return 0;
}
```

---

## 作者：wmrqwq (赞：1)

# 题目链接

[CF402D Upgrading Array (luogu)](https://www.luogu.com.cn/problem/CF402D)

[CF402D Upgrading Array (codeforces)](https://codeforces.com/contest/402/problem/D)

# 解题思路

首先你会发现你一旦在第 $i$ 个位置上做了一次操作后，那么你之后所有在第 $j(i \le j)$ 个位置做的操作都是无效的，因为此时该序列前 $i$ 个数的的公因数为 $1$。

因此有个很显然的结论就是**操作从后往前做是最优的**。

然后我们只做对答案有贡献的操作，有贡献指的是做了这个操作后的答案大于等于原本不做这个操作的的答案或者说是这个操作区间的最大公因数的价值小于 $0$。

于是根据以上方式进行操作即可，时间复杂度 $O(n \sqrt V )$，其中 $V$ 代表值域。

不过**需要注意**的是，本题**比较卡常**，记得在各个地方加上记忆化以加快程序效率。

# 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define map unordered_map
#define re register
#define ll long long
#define forl(i,a,b) for(re ll i=a;i<=b;i++)
#define forr(i,a,b) for(re ll i=a;i>=b;i--)
#define forll(i,a,b,c) for(re ll i=a;i<=b;i+=c)
#define forrr(i,a,b,c) for(re ll i=a;i>=b;i-=c)
#define lc(x) x<<1
#define rc(x) x<<1|1
#define mid ((l+r)>>1)
#define cin(x) scanf("%lld",&x)
#define cout(x) printf("%lld",x)
#define lowbit(x) (x&-x)
#define pb push_back
#define pf push_front
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
#define endl '\n'
#define QwQ return 0;
#define db long double
#define ull unsigned long long
#define lcm(x,y) x/__gcd(x,y)*y
#define Sum(x,y) 1ll*(x+y)*(y-x+1)/2
#define aty cout<<"Yes\n";
#define atn cout<<"No\n";
#define cfy cout<<"YES\n";
#define cfn cout<<"NO\n";
#define xxy cout<<"yes\n";
#define xxn cout<<"no\n";
#define printcf(x) x?cout<<"YES\n":cout<<"NO\n";
#define printat(x) x?cout<<"Yes\n":cout<<"No\n";
#define printxx(x) x?cout<<"yes\n":cout<<"no\n";
#define maxqueue priority_queue<ll>
#define minqueue priority_queue<ll,vector<ll>,greater<ll>>
ll t;
ll n,m,ans=-1e18;
map<ll,ll>mp,mp2;
ll a[100010],b[100010],lst[100010];
ll lst2;
ll gcd[100010];
map<ll,ll>mp3;
bool pdzs(ll a)
{
	if(mp3[a])
		return mp3[a]-1;
    if(a==1)
        return 0;
    if(a==2)
        return 1;
    for(ll i=2;i<=sqrt(a);i++)
        if(a%i==0)
        {
			mp3[a]=1;
		    return 0;
   		}
   	mp3[a]=2;
    return 1;
}
bool pd[1000010];
long long A[2000010],K;
void work(ll n)
{
	for(ll i=2;i<=n;i++)
	{
		if(pd[i]==0)
			A[++K]=i;
		for(ll j=1;j<=K && i*A[j]<=n;j++)
		{
			pd[i*A[j]]=1;
			if(i%A[j]==0)
				break;
		}
	}
}
ll f(ll x)
{
	ll num=x;
	if(mp2[num])
		return mp2[num];
	ll an=0;
	if(pdzs(num))
		return mp[num]==0?1:-1;
	forl(i,1,K)
		if(x%A[i]==0)
		{
			ll pd=mp[A[i]]==0?1:-1;
			while(x%A[i]==0)
				x/=A[i],an+=pd;
			if(x==1)
				return mp2[num]=an;
		}
	if(pdzs(x))
		return mp2[num]=an+(mp[x]==0?1:-1);
	return mp2[num]=an;
}
void solve()
{
	lst2=1;
	cin>>n>>m;
	forl(i,1,n)
		cin>>a[i],lst[i]=a[i];
	gcd[1]=a[1];
	forl(i,2,n)
		gcd[i]=__gcd(gcd[i-1],a[i]);
	forl(i,1,m)
		cin>>b[i],mp[b[i]]=1;
	ll sum=0;
	forl(i,1,n)
		sum+=f(a[i]);
//	cout<<sum<<endl;
	forr(i,n,1)
		if(f(gcd[i]/lst2)<0)
			sum+=f(gcd[i]/lst2)*-1*i,lst2=gcd[i];
	cout<<max(ans,sum)<<endl;
}
int main()
{
	work(40000);
	IOS;
	t=1;
 //	cin>>t;
	while(t--)
		solve();
	QwQ;
}
```

---

## 作者：wujingfey (赞：1)

Updata at 2023.10.11：终于不 UKE 了，已 AC.

![](https://cdn.luogu.com.cn/upload/image_hosting/2pq544bz.png)

------------


模拟赛的 T1，手搓了俩小时终于搓出来了 awa，当发现是一道蓝题时真的倍感自豪。

原题传送门：[CF402D](https://www.luogu.com.cn/problem/CF402D)
# 题目大意
给定一个长度为 $n$ 的序列 $a$，同时给出 $m$ 个质数，我们称之为坏质数，其余所有质数为好质数。定义 $f_1=0$，设 $p$ 为 $a_i$ 的最小质因数，若 $p$ 是好质数，则 $f_{a_i}=f_{a_i/p}+1$，否则 $f_{a_i}=f_{a_i/p}-1$。同时给定操作：将 $a_1,a_2,a_3\dots a_i(i\le n)$ 同时除以 $\gcd(a_1,a_2,a_3\dots a_i)$。求若干次操作后能得到的 $\sum_{i=1}^n a_i$ 的最大值。

$1\le n,m\le 5005$，所有数为不超过 $10^9$ 的正整数。
# 题目分析
首先我们要搞懂这个 $f$ 函数是啥意思。

因为 $f_{a_i}=f_{a_i/p}+k$（$k$ 根据 $p$ 取成 $1$ 或 $-1$），一直递归下去的话可以发现：$f_{a_i}=f_{a_i/{\prod p_j}}+\sum k_j$，$p_j$ 是 $a_i$ 的所有质因数，$k_j$ 是 $p_j$ 中好质数和坏质数的差。

我们可以从头到尾 for 一遍预处理出前缀 $pre_i=\gcd(a_1,a_2\dots a_i)$。考虑这个操作的意义：每次操作相当于从 $a_1,a_2\dots a_i$ 中剔除所有的 $pre_i$ 的因数。这些因数可能产生 $1$ 的贡献或者 $-1$ 的贡献。

那么就有一种贪心：我们从后往前枚举删除每一个 $pre_i$ 产生的贡献记为 $c$，若 $c$ 为正数说明这次操作肯定对我们有利的——对答案产生了正贡献，那么这些质因数我们不删白不删，现在不删后面有可能还删不掉了，会有亏损这些贡献的可能。**换句话说，能删的地方我们一定要删，因为后面就算能有等效的删法也不会更有利，没有等效删法则会亏。满足了贪心的条件。**（逻辑请读者认真梳理一下）

难点就基本解决了，考虑实现：

1. 先预处理出 $pre_i$。
2. 从后往前对 $pre_i$ 进行质因数分解，然后统计一下删除 $pre_i$ 对答案的贡献 $c$，如果 $c\le 0$ 就不删，否则删除。如果删除了直接 for 一遍更新 $a_i$ 和 $pre_i$ 即可。
3. 最后从前往后跑一遍，根据题意的 $f$ 把 $ans$ 算出来就行啦。

复杂度分析：这个复杂度比较玄学，本蒟蒻也不是很清楚。和同学讨论了一下，主要复杂度集中在步骤二。步骤二中，每个数受到的操作次数等于自己的质因数个数，且要进行一次质因数分解。质因数个数不会超过 $\log_2{a_i}=30$，质因数的复杂度是 $\sqrt{a_i}$，因此总复杂度大约是 $O(n(\log_2{a_i}+\sqrt{a_i}))$，考虑到修改操作使得序列不可能每个数都跑 $\sqrt{a_i}$，实际复杂度比这个应该还要小点——至少通过此题足以。
# AC代码如下
(马蜂可能有点丑？见谅 awa）
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int res=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		res=(res<<3)+(res<<1)+c-'0';
		c=getchar();
	}
	return res*f;
}
int gcd(int a,int b){//辗转相除法求 gcd
	if(b==0) return a;
	else return gcd(b,a%b);
}
const int N=5005;
int a[N],b[N],pre[N];
int n,m,ans;
int minn(int x){
	int res=0;
	for(int i=1;i<=m;i++)
		if(x%b[i]==0) res++;
	return res;
}
int get(int x){
	for(int i=2;i*i<=x;i++){
		if(x%i==0) return i;
	}
	return x;
}
int work(int x){//就是题目上的 f
	if(x==1) return 0; 
	int k=get(x);//最小质因数 
	int a1=lower_bound(b+1,b+1+m,k)-b;
	if(b[a1]==k) return work(x/k)-1;//坏质数倍数 
	else return work(x/k)+1;//好质数倍数 
}
int main(){
	n=read(),m=read();
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=1;i<=m;i++) b[i]=read();
	for(int i=1;i<=n;i++) pre[i]=gcd(pre[i-1],a[i]);//预处理前缀 gcd
	for(int i=n;i>=1;i--){
		int x=pre[i],c=0;//c:删除的贡献
		while(x>1){
			int f=x;//最小的因子
			for(int j=2;j*j<=x;j++){//暴力枚举最小的因子
				if(x%j==0){//找到最小的因数
					f=j;x/=j;break;
				}
			}
			if(f==x) x=1;//本身是质数 
			int a1=lower_bound(b+1,b+1+m,f)-b;//查找是不是坏质数
			if(b[a1]==f){//坏因子 
				for(int j=1;j<=i;j++)
					if(a[j]%f==0) c++;//坏质因子 
			}else{//好因子 
				for(int j=1;j<=i;j++)
					if(a[j]%f==0) c--;//好质因子 
			}
		}
		if(c<0) continue;
		for(int j=1;j<=i;j++){//暴力更新 a[j] 和 pre[j]
			a[j]/=pre[i];
			pre[j]/=pre[i];
		}
	}
	for(int i=1;i<=n;i++){//统计答案
		if(a[i]==1) continue;
		ans+=work(a[i]);
	}
	cout<<ans;
	return 0;
}
```
## 后记
这份代码自己的号上死活 UKE，喊同学帮忙把自己考试的代码交了上去，已 AC。其实题解写了下来感觉到不了蓝，主要难点就在分析 $f$ 的作用以及贪心。可能因人而异罢（逃）。

审核大大辛苦了，求通过，真找不到格式哪里有问题了 T^T。


---

## 作者：VIOLET__FOREVER (赞：1)

题目[传送门](https://www.luogu.com.cn/problem/CF402D)

## 题目分析

### 简化题意
对每个数进行质因数分解，如果质因数在题目中给出为坏质数答案就 $-1$，不然答案就 $+1$ 算所有数计算出的答案的总和的最小值。

### 做法
我们求出每个数的前缀 $\gcd$ 然后预处理出 $10^6$ 以内的质数，后处理的时候从后向前枚举，判断当前数的前缀 $\gcd$ 进行题目中的计算得到的数是正数还是负数，如果是正数就保留，不然就全部除以这个数这里利用一个 $used$ 记录要除以的数，类似线段树中的懒标记，处理每个数就按照质因数分解，利用预处理出的质数集去遍历，判断能否被整除，时间复杂度是线性的。

## $code$
```cpp
#include<bits/stdc++.h>
#define int long long

const int N=5005;
const int M=1000006;

using namespace std;

inline int read(){
    int t=1,x=0;
    char ch=getchar();
    for(;!isdigit(ch);ch=getchar()) if(ch=='-') t=-1;
    for(;isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+(ch^48);
    return t*x;
}//快读

int n,m;
int a[N],num[N];
int pre[M],pr;
bool pd[M];
unordered_map<int,int> be;//要用map不然数字会超过范围，会RE
int ans;
int gcd[N];//前缀数组

void init(){
    int x=1e6;
	for(int i=2;i<=x;i++){
		if(!pd[i]) pre[++pr]=i;
		for(int j=1;pre[j]*i<=x&&j<=pr;j++){
			pd[pre[j]*i]=1;
			if(i%pre[j]==0) break;
		}
	}
}//预处理出所有的质数


int dfs(int x){
    int res=0;
    for(int i=1;pre[i]*pre[i]<=x;i++){
        int cnt=0;
		while(x%pre[i]==0) x/=pre[i],cnt++;
		res+=cnt*(be[pre[i]]?-1:1);
		if (x==1) break;
    }
    if(x>1) res+=(be[x]?-1:1);
	return res;
}//每个数的质因数分解

signed main(){
    init();
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        a[i]=read();
    }
    gcd[1]=a[1];//对于第一个数的前缀数组要进行特判
    for(int i=2;i<=n;i++){
        gcd[i]=__gcd(gcd[i-1],a[i]);//__gcd是内置函数，比较好用
    }
    for(int i=1;i<=m;i++){
        num[i]=read();
        be[num[i]]=1;//给b数组的每一个数打上标记
    }
    for(int i=1;i<=n;i++)ans+=dfs(a[i]);
    int used=1;//used用来记录上一个要除去的数
    for(int i=n;i;i--) {
        if(gcd[i]/used==1)continue;//特判，小优化，也可以去掉
		int p=dfs(gcd[i]/used);
		if(p<0){
			ans-=p*i;
			used=gcd[i];
		}
	}
    cout<<ans;
    return 0;
}

```
## 后记

$long long$ 要看准时机开，不要开可以不开。

---

## 作者：kimi0705 (赞：0)

简单题。从操作的内容入手。设操作的数列为 $r_i$，那么显然 $r_i$ 是单调递减的。

证明：当存在 $i, j,i<j$ 使得 $r_i \le r_j$。那么对于前 $i$ 次操作 $[1,r_i]$ 的 $\gcd$ 在操作完之后为 $1$，之后再操作 $r_j$，由于 $\gcd_{i=1}^{r_i}=1,r_i<r_j$，得 $\gcd_{i=1}^{r_j}=1$。证毕。 

所以从 $n\to1$ 枚举 $i$，观察对于 $i$ 的更改是否有好处，贪心的去思考，具体的维护前缀 $\gcd$，看 $f(\gcd_i)$ 是否大于 $1$。

code:
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, x, ans, res = 1;
set <int> bad;
int arr[5005], Gcd[5005];
bool vis[40005];
vector <int> p;
void init() {
	for (int i = 2; i <= 40000; i++) {
		if (vis[i]) continue;
		p.push_back(i);
		for (int j = i * i; j <= 40000; j += i) vis[j] = true;
	}
}
int f(int x) {
	int ans = 0;
	for (int i = 0; i < p.size(); i++) {
		if (x <= 40000 && vis[x] == 0) break;
		int deta = (bad.find(p[i]) == bad.end() ? 1 : -1);
		while (x % p[i] == 0) ans += deta, x /= p[i];
	}
	if (x != 1) {
		ans += (bad.find(x) == bad.end() ? 1 : -1);
	}
	return ans;
}

int g(int x) {
	int ans = 0;
	for (int i : p) {
		if (x <= 40000 && vis[x] == 0) break;
		int deta = (bad.find(i) != bad.end() ? 1 : -1);
		while (x % i == 0) ans += deta, x /= i;
	}
	if (x != 1) {
		ans += (bad.find(x) != bad.end() ? 1 : -1);
	}
	return ans;
}
int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	init();
	cin >> n >> m;
	for (int i = 1; i <= n; i++) cin >> arr[i];
	while (m--) cin >> x, bad.insert(x);
	for (int i = 1; i <= n; i++) ans += f(arr[i]);
	for (int i = 1; i <= n; i++) Gcd[i] = __gcd(Gcd[i - 1], arr[i]);
	for (int i = n; i >= 1; i--) {
		int now = Gcd[i] / res, G = g(now);
		if (G > 0) ans += G * i, res *= now;
	}
	cout << ans << '\n';
}
```

---

## 作者：Fantasy_Segment_Tree (赞：0)

首先思考这个f函数究竟是什么？其实就是分解质因数后好素数的个数减去坏素数的个数的值。

所以如果我们把一个前缀除以最大公因数会更优，一定是最大公因数分解质因数后坏质数比好质数个数多。这样除掉的坏质数的个数比好质数多，所以加上的f函数值比减去的多，可以使答案更优。

于是先筛出 $1$ 至 $\sqrt{10^9}$ 之内的质数，然后把所有前缀的最大公因数求出，接着从后往前（为什么要从后往前？因为后面把一个前缀整体除掉后前面还可以继续除，但是前面除掉后后面最大公因数会变成 $1$，会使答案变劣）取出当前前缀的最大公因数，如果最大公因数分解质因数后坏质数个数比好质数多，那么就把这个前缀除以最大公因数，同时前面的最大公因数也要除。

最后计算f函数的总和即可。

代码如下。

```
#include <iostream>
#include <map>
#include <cmath>
using namespace std;

int n, m, a[5005], gc[5005], zs[50005], cnt, prime[50005];

map <int, int> mp;

int gcd(int x, int y) {
	if(y == 0) return x;
	else return gcd(y, x % y);
}

int main() {
	for(int i = 2; i <= 50000; i++) {
		if(!prime[i]) {
			zs[++cnt] = i;
		}
		for(int j = 1; j <= cnt && i * zs[j] <= 50000; j++) {
			prime[i * zs[j]] = 1;
		}
	}
	cin >> n >> m;
	for(int i = 1; i <= n; i++) cin >> a[i];
	for(int i = 1; i <= n; i++) {
		gc[i] = gcd(gc[i - 1], a[i]);
	}
	for(int j = 1; j <= m; j++) {
		int x;
		cin >> x;
		mp[x] = 1;
	}
	
	for(int i = n; i >= 1; i--) {
		int tmp = gc[i], cnt1 = 0, cnt2 = 0;
		for(int j = 1; j <= cnt; j++) {
			if(zs[j] > sqrt(gc[i])) break;
			if(tmp == 1) break;
			while(tmp % zs[j] == 0) {
				tmp /= zs[j];
				if(mp[zs[j]]) cnt1++;
				else cnt2++;
			}
		}
		if(tmp != 1) {
			if(mp[tmp]) cnt1++;
			else cnt2++;
		}
		if(cnt1 > cnt2) {
			for(int j = 1; j <= i; j++) a[j] /= gc[i];
			for(int j = 1; j <= i; j++) {
				gc[j] /= gc[i];
			}
		}
	}
	int ans = 0;
	for(int i = 1; i <= n; i++) {
		int tmp = a[i], cnt1 = 0, cnt2 = 0;
		for(int j = 1; j <= cnt; j++) {
			if(zs[j] > sqrt(a[i])) break;
			if(tmp == 1) break;
			while(tmp % zs[j] == 0) {
				tmp /= zs[j];
				if(mp[zs[j]]) cnt1++;
				else cnt2++;
			}
		}
		if(tmp != 1) {
			if(mp[tmp]) cnt1++;
			else cnt2++;
		}
		ans += cnt2 - cnt1;
	}
	cout << ans;
}
```

虽然时间复杂度看着是 $O(n\sqrt{10^9})$ 的，但是实际上 $1$ 至 $50000$ 的质数都只有 $5000$ 多个，所以不会超时。

---

## 作者：WANG_YIN (赞：0)

# CF402D Upgrading Array

## 题意

给定一个长度为 $n$ 的序列 $a$，在给定一个长度为 $m$ 的质数序列 $b$，我们称这些数为坏素数。同时你可以对任意的 $i(1\le i\le n)$进行若干次的操作，使 $a_1,a_2,\cdots,a_i$，同时除以 $\gcd(a_1,a_2,\cdots,a_i)$，求  $\displaystyle\sum\limits^n_{i=1}f(i)$。

已知：
$$
f(x)=
\begin{cases}
	1 & x=1 \\
	f(\frac{x}{p})-1 &x\not=1 \land p \in b\\
	f(\frac{x}{p})+1 &x\not=1 \land p \notin b
\end{cases}
$$

其中 $p$ 为 $x$ 的最小质因数。



## 分析

很容易发现对于一个数 $x$，求 $f(x)$ 的过程就是将 $x$ 质因数分解后，统计其中坏质数与好质数的数量之差。

很显然我们可以 $O(n\sqrt A)$ 的求出在没有进行任何操作时的答案。

现在考虑每一次操作会对答案造成什么影响。

我们设 $g_i=\gcd(a_1,a_2,\cdots,a_i)$，可以发现：对于 $i>j$，满足 $g_i\le g_j$ 且 $g_i\mid g_j$。

所以我们从后往前进行操作一定是更优的。

考虑为什么这样是更优的：

因为我们在从后向前找时，我们能尽可能多的处理到所有的 $a_i$，而从前往后找的话，因为我们在前面某处使所有的 $a_i$ 除去了一个 $\gcd$，可能会使后面的某些地方无法进行操作。

我们可以 $O(n)$ 预处理出 $g_i$，同时 $O(n\sqrt{g_i})$ 的处理出 $f(g_i)$ 。

这样就有一个很显然的贪心策略：我们从后向前找，对于一个 $g_i$ 如果它的 $f(g_i)<0$，那我们将其除去一定是更优的。在除去 $g_i$ 后，对于 $g_1,\cdots,g_i$ 都要除去 $g_i$ ，我们可以打一个 `tag` 记录已经除掉的值，在查找到这一位时再处理标记即可。

总的时间复杂度为 $O(n\sqrt A)$。



## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 5005
#define ll long long

int n,m;
ll ans;
int a[N],b[N];
int g[N],t[N];
unordered_map<int,int>vis;

inline int gcd(int a,int b){
	return !b?a:gcd(b,a%b);
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;++i){
		cin>>a[i];
	}
	for(int i=1;i<=m;++i){
		int x;
		cin>>x;
		vis[x]=1;
	}
	g[1]=a[1];
	for(int i=2;i<=n;++i){
		g[i]=gcd(g[i-1],a[i]);
	}
	for(int i=1;i<=n;++i){
		int x=g[i];
		for(int j=2;j*j<=g[i];++j){
			if(x%j) continue;
			int cnt=0;
			while(!(x%j)){
				x/=j;
				++cnt;
			}
			if(vis.find(j)!=vis.end()) t[i]-=cnt;
			else t[i]+=cnt;
			if(x==1) break;
		}
		if(x!=1){
			if(vis.find(x)!=vis.end()) --t[i];
			else ++t[i];
		}
	}
	int tag_g=1,tag_t=0;
	for(int i=n;i>=1;--i){
		if(t[i]<tag_t&&g[i]>tag_g){
			ans-=1ll*(t[i]-tag_t)*i;
			tag_g=g[i];
			tag_t=t[i];
		}
	}
	for(int i=1;i<=n;++i){
		int x=a[i];
		for(int j=2;j*j<=a[i];++j){
			if(x%j) continue;
			int cnt=0;
			while(!(x%j)){
				x/=j;
				++cnt;
			}
			if(vis.find(j)!=vis.end()) ans-=cnt;
			else ans+=cnt;
			if(x==1) break;
		}
		if(x!=1){
			if(vis.find(x)!=vis.end()) --ans;
			else ++ans;
		}
	}
	cout<<ans<<"\n";
	
	return 0;
} 
```





---

## 作者：z_yq (赞：0)

### 题目意思
定义一个数的得分是其质因数中好的质数的个数减去坏的质数的个数，其中坏的质数已经给出，其余的都是好的质数。

定义一个数列的的得分为其中所有数的得分之和，现在有一种操作，可以将前 $i$ 个数均除以 $\gcd(a_1,a_2,\ldots,a_{i-1},a_i)$ 现在可以进行任意次数操作，求数列得分的最大值。

### 思路
其实这道题目就是一个模拟，我们可以求出我们原来数列的得分，然后看怎么样操作可以让分数变高：当我们选择一个 $i$，并进行操作的时候我们令他们的最大公约数为 $p$，则若 $p$ 的得分比 $0$ 小，则显而易见，我们除以的数就是有很多差的质数的，所以我们可以就可以除这个数，则我们的得分增加 $i$ 倍的 $p$ 的得分，而我们遍历，看我们什么时候可以做操作就可以了。

### Code
```cpp
#include<bits/stdc++.h>
#define ll int
using namespace std;
const ll N=5009;
ll n,a[N],m,b[N],gcd_[N];
map<ll,bool>mp;
inline ll gx(ll x)
{
	ll cnt=0;
	for(int i=2;i*i<=x;i++)
		while(x%i==0)
			if(mp[i]==0)
				cnt++,x/=i;
			else cnt--,x/=i;
	if(x!=1)
	{
		if(mp[x])
			cnt--;
		else cnt++;
	}
	return cnt;
}
inline ll read()
{
	ll x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0' && ch<='9')
		x=x*10+ch-'0',ch=getchar();
	return x*f;
}
int main()
{
	n=read();m=read();
	for(int i=1;i<=n;i++)
		a[i]=read();
	for(int i=1;i<=m;i++)
		b[i]=read(),mp[b[i]]=1;
	ll ans=0,gd=0;
	for(int i=1;i<=n;i++)
	{
		if(!gd) gd=a[i];
		else gd=__gcd(gd,a[i]);
		ans+=gx(a[i]);
		gcd_[i]=gd;
	}
	gd=1;
	for(int i=n;i>=1;i--)
	{
		ll tmp=gx(gcd_[i]/gd);
		if(tmp<0)
			gd=gcd_[i],
			ans-=tmp*i;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：NBest (赞：0)

不难想到我们要先记录一下每一位的前缀 $\gcd$，我们发现我们选择一位的前缀 $\gcd$ 除掉以后，前缀 $\gcd$ 会变为 $1$ 并且会导致这位之后的 $\gcd$ 全部为  $1$。所以每一位只能选择一次，并且我们从后往前扫肯定比从前往后扫要更优。

我们先把原序列原答案算出来，然后判断每一次除当前位的 $\gcd$ 是否对答案有正贡献，贪心选择。这样为什么对呢？考虑我们第 $i$ 位的贡献为正，但是我们不选，到 $i-1$ 的时候，贡献可能变大，那显然我们后面除了对前面也没有影响，前面依然可以除剩下的，但是如果变小，说明前面不用除要让后面除。所以我们贪心从后往前选择是更优的。

如果我们直接贪心选了以后把前面的 $\gcd$ 都除掉，发现复杂度是 $O(n^2\sqrt{a})$ 的，这样肯定不行。注意到我们 $\gcd$ 是单调不增的，所以我们从后往前是单调不减的，记录一下即可做到 $O(n\sqrt{a})$，然而用线性筛跑了之后是远远跑不满的。
## $Code$
```cpp
int n,m,tot,prime[100005];
bool vis[100005];
ll ans,a[5002],b[5002];
unordered_set<ll>pd;
void init(){
    for(int i=2;i<=100000;i++){
        if(!vis[i])prime[++tot]=i;
        for(int j=1;j<=tot&&prime[j]*i<=100000;j++){
            vis[prime[j]*i]=1;
            if(i%prime[j]==0)break;
        }
    }
}
ll cal(ll x){
    ll res=0;
    for(int i=1;prime[i]*prime[i]<=x;i++){
        if(x%prime[i])continue;
        ll cnt=0;
        while(x%prime[i]==0)x/=prime[i],cnt++;
        if(pd.find(prime[i])!=pd.end())res-=cnt;
        else res+=cnt;
    }
    if(x>1){
        if(pd.find(x)!=pd.end())res--;
        else res++;
    }
    return res;
}
int main(){
    n=read(),m=read();
    init();
    for(int i=1;i<=n;i++){
        a[i]=read();
        if(i==1)b[i]=a[i];
        else b[i]=__gcd(b[i-1],a[i]);
    }
    for(int i=1;i<=m;i++)pd.insert(read());
    for(int i=1;i<=n;i++)ans+=cal(a[i]);
    for(ll i=n,used=1,o;i;--i)
        if((b[i]/used>1)&&(o=cal(b[i]/used))<0)ans-=o*i,used=b[i];
    cout<<ans;
    return 0;
}
```

---

