# [USACO22FEB] Sleeping in Class P

## 题目描述

最近终于线下授课了，奶牛 Bessie 十分兴奋！不幸的是，Farmer John 是一个非常无聊的讲师，因此她经常课堂上睡觉。

Farmer John 注意到了 Bessie 上课走神。他要求班上的另一个学生 Elsie 跟踪记录给定课上 Bessie 睡觉的次数。一共有 $N$ 堂课，Elsie 记录下了 Bessie 在第 $i$ 堂课睡了 $a_i$ 次。所有课上 Bessie 一共睡觉的次数最多为 $10^{18}$。

Elsie 认为自己是 Bessie 的竞争对手，所以她想让 FJ 觉得在每堂课上 Bessie 都一直睡了同样多次——让 FJ 觉得这个问题显然完全是 Bessie 的错，而不是 FJ 有时上课很无聊的问题。

Elsie 修改记录只有以下两种方式：把两堂课的记录合起来，或者把一堂课的记录分成两堂课。例如，如果 $a=[1,2,3,4,5]$，那么如果 Elsie 将第二堂和第三堂课的记录合起来，记录就会变为 $[1,5,4,5]$。如果 Elsie 继续选择让第三堂课的记录分为两堂，记录就可能变为 $[1,5,0,4,5],[1,5,1,3,5],[1,5,2,2,5],[1,5,3,1,5]$ 或 $[1,5,4,0,5]$。

给定 $Q$ 个候选的 Bessie 最不喜欢的数字 $q_1,\ldots,q_Q$，对于每个数字，请帮助 Elsie 计算她至少要操作多少次，才能让记录里的所有数字都变成这个数字。

## 说明/提示

**【样例解释】**

Elsie 需要至少 $4$ 次修改才能让记录里的所有数都变成 $3$。

$$
\begin{aligned}
&\ 1\ 2\ 3\ 1\ 1\ 4\\
\rightarrow&\ 3\ 3\ 1\ 1\ 4\\
\rightarrow&\ 3\ 3\ 1\ 5\\
\rightarrow&\ 3\ 3\ 6\\
\rightarrow&\ 3\ 3\ 3\ 3\\
\end{aligned}
$$

Elsie 不可能把记录中的所有数都变成 $5$，因此输出 $-1$。这是正确的。

**【数据范围】**

- 对于第 $2\sim 4$ 组数据，$N,Q\le 5000$。
- 对于第 $5\sim 7$ 组数据，所有 $a_i$ 最多为 $10^9$。
- 对于第 $8\sim 26$ 组数据，无附加限制。

## 样例 #1

### 输入

```
6
1 2 3 1 1 4
7
1
2
3
4
5
6
12```

### 输出

```
6
6
4
5
-1
4
5```

# 题解

## 作者：Alex_Wei (赞：8)

> *[P8193 [USACO22FEB] Sleeping in Class P ](https://www.luogu.com.cn/problem/P8193)*

提供一个不需要 Pollard - rho 的做法。

记 $a$ 的前缀和数组为 $s$，容易发现若 $q \nmid s_n$ 则无解，否则答案为 $\left(\dfrac {s_n} q - 1\right) + (n - 1) - 2\sum\limits_{i = 1} ^ {n - 1} [q\mid  s_i]$。这是因为我们考虑将所有数全部合并再分裂，能够整除 $q$ 的前缀和对应的切割点处不用分裂再合并，可以减少两步。

考虑这样一个朴素的暴力：对每个 $s_n$ 的因数均求一遍答案。时间复杂度 $\mathcal{O}(nd(s_n))$。由于 $s_n$ 可达 $10 ^ {18}$，且 $10 ^ {18}$ 内最大的约数个数级别为 $10 ^ 5$，所以无法接受。

注意到实际上只需求 $2\sum\limits_{i = 1} ^ {n - 1} [q \mid s_i]$。考虑每个 $s_i$ 对 $s_n$ 的每个因数 $d$ 的贡献。显然，$s_i$ 对所有 $\gcd(s_i, s_n)$ 的因数有贡献。设 $D = \gcd(s_i, s_n) = \prod p_i ^ {c_i}$，则任意 $\prod\limits_{0\leq b_i \leq c_i} p_i ^ {b_i}$ 均需要加上 $1$。这是高维前缀和的形式，因此这一部分容易做到 $n\log (s_n) + d(s_n)\omega(s_n)\log d(s_n)$，后面带一个 $\log$ 是因为要把所有因子用 map 映射到一个较小的范围内，否则无法存储结果。哈希表如 gp_hash_table 应该可以去掉这个 $\log$。

问题只剩下分解质因数了。不想写 Pollard - rho 怎么办？考虑只分解到 $10 ^ 6$，即用 $10 ^ 6$ 以内的质因子试除 $s_n$。如果最终结果 $ \leq 10 ^ {12}$，说明剩下的 $s_n$ 是一个质数（否则就被试除掉了），否则说明 $s_n$ 有两个大于 $10 ^ 6$ 的质因子（不一定不同）。对于前者，我们已经成功分解质因数。对于后者，注意到此时 $s_n$ 的因子个数不超过 $4 \times \max\limits_{i \leq 10 ^ 6}d(i)$，于是直接暴力即可。

时间复杂度 $n\max\limits_{i \leq 10 ^ 6} d(i) + n\log (s_n) + d(s_n)\omega(s_n)\log d(s_n)$。代码并不是很可读。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define ll long long
const int N = 2e5 + 5;
ll n, q, a[N], pr[N];
int pw[N], cnt, ppw[N];
map <ll, ll> mp;
int f[N];
int calc(int *pw) {
	int res = 0;
	for(int i = 1; i <= cnt; i++) res += pw[i] * ppw[i];
	return res;
}
ll rev(int x) {
	ll res = 1;
	for(int i = 1; i <= cnt; i++) {
		int d = x / ppw[i] % (pw[i] + 1);
		for(int j = 1; j <= d; j++) res *= pr[i];
	} return res;
}

int fix, cpw[N];
void dfs(int id) {
	if(id > cnt) {
		int cur = calc(cpw);
		f[cur - ppw[fix]] += f[cur];
		return;
	} for(int i = pw[id]; i >= (id == fix); i--) cpw[id] = i, dfs(id + 1);
}
void check() {
	ll tmp = a[n];
	for(int i = 2; i <= 1e6; i++)
		if(tmp % i == 0) {
			pr[++cnt] = i;
			while(tmp % i == 0) pw[cnt]++, tmp /= i;
		}
	if(tmp > 1e12) return;
	if(tmp > 1) pr[++cnt] = tmp, pw[cnt] = 1;
	ppw[cnt] = 1;
	for(int i = cnt - 1; ~i; i--) ppw[i] = ppw[i + 1] * (pw[i + 1] + 1);
	for(int i = 1; i < n; i++) {
		ll tmp = a[i];
		for(int j = 1; j <= cnt; j++) {
			int cur = 0;
			while(tmp % pr[j] == 0) cur++, tmp /= pr[j];
			cpw[j] = min(pw[j], cur);
		} f[calc(cpw)]++;
	}
	for(int i = 1; i <= cnt; i++) fix = i, dfs(1);
	for(int i = 0; i < ppw[0]; i++) mp[rev(i)] = n - 1 + a[n] / rev(i) - 1 - f[i] * 2;
}
int main() {
	cin >> n;
	for(int i = 1; i <= n; i++) cin >> a[i], a[i] += a[i - 1];
	check(), cin >> q;
	for(int i = 1; i <= q; i++) {
		ll x; cin >> x;
		if(a[n] % x) {puts("-1"); continue;}
		if(!mp[x]) {
			ll ans = 0;
			for(int j = 1; j < n; j++) ans += a[j] % x == 0;
			mp[x] = n - 1 + a[n] / x - 1 - ans * 2;
		}
		cout << mp[x] << "\n";
	}
	return 0;
}

/*
stupid mistakes:
	进制转换写错了
	rev : res *= pr[i] -> *= pr[j]
*/ 
```



---

## 作者：analysis (赞：5)

### 观前提示

- 细心读题

- 膜拜 [Alex_Wei](https://www.luogu.com.cn/user/123294)。

## 贪心策略

显然，我们要先找到本题的操作策略。

观看样例解释，你会发现：

- 合并了 $1$、$2$ 变为 $3$。
- 合并出 $6$，拆开成两个 $3$。

即合成出倍数后直接拆。

于是令 $S_n$ 表前 $n$ 个数之和。

$$
ans = \sum_{q | S_r - S_{l-1}}(r - l) + (\frac{S_r - S_{l-1}}{q} - 1)
$$

然后你会发现，$l$、$r$ 是变值，不好做（就算是 $i = 1 \rightarrow n$ 这样的都比他好，$l$、$r$ 根本无法确定），要把它往定值上引导。

哪些是定值？$n$ 与 $S$。

于是我们可以找到一个关于 $n$ 的朴素策略：合并再拆解。

$$
ans = (n-1) + (\frac{S_n}{q} - 1)
$$

于是，我们可以利用类似反悔的思想，我们在出现上述情况时反悔，不把数加入。

这样可以减少两步：加入在拆出。
$$
ans = (n-1) + (\frac{S_n}{q} - 1) - 2\sum_{i=1}^{n-1}[q|S_i]
$$
朴素处理的速度很慢，是 $O(QN)$ 的。而要加速和式计算，就要从贡献的角度入手。

## 优化和式计算

考虑一个 $S$ 有多少贡献。（为什么不考虑 $q$ 应该很明显了吧，考虑它显然也没有优化啊，该算的还是得算）

$S$ 对所有其因数有贡献。

但是 $S \leq 10^{18}$，我们难以对所有 $S$ 对其所有因子给贡献。

但是，我们还有一个隐藏条件：$q | S_n$。（这就是写题时把所有自己能找到的条件写出来的好处）
$$
\because q|S_i,q|S_n
$$
$$
\therefore q | \gcd(S_i,S_n)
$$
也即所有 $S$ 的贡献都在 $S_n$ 的超立方体内，所以只需做一次高维后缀和即可。

## 实现细节

### 质因数分解

- 对于一个数 $n$，其次大质因子不超过 $\sqrt{n}$。

我们试除法分解到 $10^6$，如果剩下的数小于等于 $10^{12}$，则是一个质数，质因数分解完毕。

否则暴力即可。

因为此时 $S_n$ 有至少两个大于 $10^6$ 的质因子（$\frac{10^{18}}{(10^6)^2} \leq 10^6$，它必然已被整除）。

所以它们最多组出 $4$ 个数。

所以 $\sigma_0(S_n) \leq 4 \times \max\{\sigma_{0}(i\leq10^6)\}$。

使用如下代码：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int getd(int x)
{
    int ans = 1;
    for(int i=2;i<=sqrt(x);i++)
    {
        int cur = 0;
        while(x % i == 0)
        {
            cur++;
            x/=i;
        }
        ans *= cur+1;
    }
    return ans;
}
signed main()
{
    int ans = 0;
    for(int i=2;i<=1e6;i++)
    {
        ans = max(ans,getd(i));
    }
    cout<<ans;
}
```

结果为 `192`。

所以需要处理的 $q$ 仅有至多 `768` 个。

所以暴力完全没有问题。

### 数值、点值的互相转化

高维的单位值设为低维的极值加一即可。

```cpp
int fpow(int a,int b)
{
    int r=1;
    while(b)
    {
        if(b&1)r=r*a;
        a=a*a;
        b>>=1;
    }
    return r;
}
//uc表分解质因数后的指数
int ntp(int *uc)//把数字转化为坐标
{
    int r=0;
    for(int i=1;i<=cnt;i++)
    {
        r += uc[i] * w[i];
    }
    return r;
}
int ptn(int x)//反过来
{
    int r = 1;
    for(int i=1;i<=cnt;i++)
    {
        int cnum = x / w[i] % (c[i] + 1);
        r *= fpow(pri[i],cnum);
    }
    return r;
}
```

```cpp
w[cnt]=1;
for(int i=cnt-1;i>=0;i--)
{
    w[i] = w[i+1] * (c[i+1] + 1);
}
```

### 高维前缀和

dfs 状态，然后转移。

```cpp
void presum(int wd,int ch)//高维前缀和,wd:维度,ch：正在转移的维度
{
    if(wd > cnt)
    {
        int x = ntp(p);
        f[x - w[ch]] += f[x];
        return;
    }
    for(int i = c[wd];i>=(wd == ch);i--)
    {
        p[wd] = i;
        presum(wd+1,ch);
    }
}
```

## 完整代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,q,a[200005];
int pri[200005],cnt,c[200005],w[200005];
map<int,int> mp,f;
int fpow(int a,int b)
{
    int r=1;
    while(b)
    {
        if(b&1)r=r*a;
        a=a*a;
        b>>=1;
    }
    return r;
}
int ntp(int *uc)//把数字转化为坐标
{
    int r=0;
    for(int i=1;i<=cnt;i++)
    {
        r += uc[i] * w[i];
    }
    return r;
}
int ptn(int x)//反过来
{
    int r = 1;
    for(int i=1;i<=cnt;i++)
    {
        int cnum = x / w[i] % (c[i] + 1);
        r *= fpow(pri[i],cnum);
    }
    return r;
}
int p[200005];
void presum(int wd,int ch)//高维前缀和
{
    if(wd > cnt)
    {
        int x = ntp(p);
        f[x - w[ch]] += f[x];
        return;
    }
    for(int i = c[wd];i>=(wd == ch);i--)
    {
        p[wd] = i;
        presum(wd+1,ch);
    }
}
void init()
{
    //从这开始质因数分解S_n
    int maxn = a[n];
    for(int i=2;i<=1e6;i++)
    {
        if(maxn % i == 0)
        {
            pri[++cnt] = i;
            while(maxn % i == 0)
            {
                c[cnt]++;
                maxn/=i;
            }
        }
    }
    if(maxn <= 1e12 && maxn > 1)
    {
        pri[++cnt] = maxn;
        c[cnt]++;
    }
    else if(maxn != 1)return;
    //计算维度单位
    w[cnt]=1;
    for(int i=cnt-1;i>=0;i--)
    {
        w[i] = w[i+1] * (c[i+1] + 1);
    }
    //记录点gcd(S_i,S_n)
    for(int i=1;i<n;i++)
    {
        int tmp = a[i];
        for(int j=1;j<=cnt;j++)
        {
            int cur=0;
            while(tmp % pri[j] == 0)
            {
                cur++;
                tmp/=pri[j];
            }
            p[j] = min(cur,c[j]);
        }
        f[ntp(p)]++;
    }
    //逐维高维前缀和
    for(int i=1;i<=cnt;i++)
    {
        presum(1,i);
    }
    //枚举点与记录ans
    for(int i=0;i<w[0];i++)
    {
        mp[ptn(i)] = (n - 1) + (a[n] / ptn(i) - 1) - 2 * f[i];
    }
}
signed main()
{
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i],a[i] += a[i-1];
    init();
    cin>>q;
    while(q--)
    {
        int qq;
        cin>>qq;
        if(a[n] % qq)cout<<-1<<endl;
        else
        {
            if(!mp[qq])
            {
                int r = 0;
                for(int i=1;i<n;i++)
                {
                    if(a[i] % qq == 0)r++;
                }
                mp[qq] = (n-1) + (a[n] / qq - 1) - 2 * r;
            }
            cout<<mp[qq]<<endl;
        }
    }
    return 0;
}
```

---

## 作者：dead_X (赞：5)

## 前言
憨批题。
## 思路
不难发现以下策略是最优的：

* $\sum a_i\bmod p\neq 0$，则必定无解。
* 不然，遍历数组：
* 如果 $a_i<p$，将 $a_i$ 合并到 $a_{i+1}$。
* 如果 $a_i>p$，将 $a_i$ 分裂为 $p$ 和 $a_i-p$。

这种策略中，记 $A_i=\sum\limits_{j=1}^ia_j$，答案即为 $\frac{A_n}{p}+n-2\sum[A_i\bmod p=0]$。

于是相当于要快速求 $\sum[A_i\bmod p=0]$。

因为 $p$ 是 $A_n$ 的因数，所以可以将 $A_i$ 都与 $A_n$ 取 $\gcd$。

现在问题转化成了以下形式：给定 $n$ 个 $S$ 的因数 $A_i$，$T$ 次给定 $S$ 的因数 $p$，求 $A_i$ 中 $p$ 的倍数的数量。

如果我们根据唯一分解定理，因数就可以转化为子集了，我们也只需要对所有数求一遍高维前缀和就可以预处理所有因数的答案。

考虑这个高维前缀和的元素数和维度数，分别为 $d(a)$ 和 $\omega(a)$，因此高维前缀和的时间复杂度为 $O(d(a)\omega(a))$，但是求高维前缀和之前还要做一遍质因数分解，每个数还要求一遍 gcd，因此总时间复杂度为 $O(n\log a+a^\frac{1}{4}+d(a)\omega(a))$。
## 代码
pollard-rho 是贺的。

```cpp
// Problem: Problem 2. Sleeping in Class
// Contest: USACO - USACO 2022 February Contest, Platinum
// URL: http://usaco.org/index.php?page=viewproblem&cpid=1201
// Memory Limit: 256 MB
// Time Limit: 4000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//And in that light,I find deliverance.
#include<bits/stdc++.h>
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("unroll-loops")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
using namespace std;
#define ull unsigned long long
char buf[1<<21],*p1=buf,*p2=buf,obuf[1<<23],*O=obuf;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
inline ull read()
{
	ull s=0;
	char ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9') s*=10,s+=ch^48,ch=getchar();
	return s;
}
void print(ull x) {
    if(x>9) print(x/10);
    *O++=x%10+'0';
}
#define mul(x,y,p) ((__uint128_t)x*y%p)
ull qp(ull x,ull y,ull p){
	ull res=1;
	for(ull now=x; y; y>>=1,now=mul(now,now,p)) (y&1)&&(res=mul(res,now,p));
	return res;
}
bool MR(ull x,ull p){
	for(ull t,k=x-1; !(k&1);)
	{
		k>>=1,t=qp(p,k,x);
		if(t!=1&&t!=x-1) return 0;
		if(t==x-1) return 1;
	}
	return 1;
}
const ull P[10]={2,3,5,7,11,13,19,61,2333,24251};
bool is_prime(ull x){
	if(x<3) return (x==2);
	for(ull i=0; i<10; ++i) 
	{
		if(x==P[i]) return 1;
		if(x%P[i]==0) return 0;
		if(qp(P[i]%x,x-1,x)!=1) return 0;
		if(!MR(x,P[i]%x)) return 0;
	}
	return 1;
}
mt19937 rnd(998244353);
ull qwqabs(ull x){return x>=0?x:-x;}
ull gcd(ull x,ull y){
	if(!x) return y;
	if(!y) return x;
	ull t=__builtin_ctzll(x|y);
	x>>=__builtin_ctzll(x);
	do
	{
		y>>=__builtin_ctzll(y);
		if(x>y) swap(x,y);
		y-=x;
	}while(y);
	return x<<t;
}
ull find(ull n) {
	if((n&1)==0) return 2;
    ull x = rnd()%(n+1);
    ull g = 1;
    ull q = 1;
    ull c=rnd()%(n+1);
    ull xs, y;
    ull m = 128;
    ull l = 1;
    while (g == 1) {
        y = x;
        for (ull i = 1; i < l; i++)
            x = (mul(x,x,n)+c)%n;
        ull k = 0;
        while (k < l && g == 1) {
            xs = x;
            for (ull i = 0; i < m && i < l - k; i++) {
                x = (mul(x,x,n)+c)%n;
                q = mul(q, qwqabs(y - x), n);
            }
            g = gcd(q, n);
            k += m;
        }
        l *= 2;
    }
    ull CNT=1;
    while(g == n) {
        do {
        	++CNT;
            xs = (mul(xs,xs,n)+c)%n;
            g = gcd(qwqabs(xs - y), n);
        } while (g == 1);
        if(CNT>100) return find(n);
    }
    return g;
}
ull ans=0;
unordered_map<ull,ull> mp;
map<ull,ull> dd,val;
void PR(ull x,ull mul=1){
	if(x<=1) return ;
	if(is_prime(x)) 
	{
		dd[x]+=mul;
		return ;
	}
	if(!mp[x]) mp[x]=find(x);
	ull y=x,gg=0;
	while(y%mp[x]==0) y/=mp[x],++gg;
	PR(mp[x],mul*gg),PR(y,mul);
}
ull a[100003];
signed main()
{
	int n=read();
	for(int i=1; i<=n; ++i) a[i]=a[i-1]+read();
	PR(a[n]);
	for(int i=1; i<=n; ++i) ++val[__gcd(a[i],a[n])];
	vector<ull> V;
	V.push_back(1);
	for(auto i:dd)
	{
		vector<ull> tv=V;
		for(ull ii:V)
			for(ull j=1,iii=ii*i.first; j<=i.second; ++j,iii*=i.first)
				tv.push_back(iii);
		V=tv;
	}
	for(auto i:dd) 
	{
		for(auto ii:V) if(ii%i.first)
		{
			ull R=ii;
			for(ull j=1; j<=i.second; ++j)
				R*=i.first;
			ull sum=val[R];
			for(ull j=i.second; j>=1; --j)
				R/=i.first,sum+=val[R],val[R]=sum;
		}
	}
	for(int T=read(); T--;)
	{	
		ull p=read();
		if(a[n]%p) *O++='-',*O++='1',*O++='\n';
		else print(a[n]/p+n-(val[p]<<1)),*O++='\n';
	}
	fwrite(obuf,O-obuf,1,stdout);
	return 0;
}
```

---

## 作者：约瑟夫用脑玩 (赞：1)

套路题，但我确实没做起，因为套路掌握的不够熟练。

如果所有数字都为 $p$，设有 $t$ 个，则有 $p\times t=\sum a_i$，也就是说最后变出的数字是 $S=\sum a_i$ 的因数。

考虑计算最少的次数变成这个数字，首先有个最简单的策略是花费 $n-1$ 次变成 $S$，然后花费 $t-1$ 次分裂成 $p$。

考虑什么时候能少？如果把 $S$ 画成一个长段，初始在 $sum_i=\sum_{j=i}^ia_i$ 的位置分段，最后分段的位置为 $\forall k\in[1,t],kp$。

你按上述策略在分段的位置进行合并与分裂操作，如果你在同一个位置合并且分裂那么你可以直接去掉这两次操作。

显然发现能去掉的位置满足 $\exists k,p|sum_k$，考虑直接计算 $2\sum[sum_i\bmod p=0]$ 即可。

一般人都想到这一步了，然而接下来却是套路。

直接对 $S$ 质因数分解，对于每个数 $sum_i$ 只保留和 $S$ 的公因数，发现询问的就是一个质因子集合上的超集，直接对质因子上高维后缀和即可。

唯一的细节是 $S=1$ 时 Pollard-Rho 可能会挂掉，我乱写的 Pr 都跑的很快，代码就不放了。

---

## 作者：Purslane (赞：0)

# Solution

将问题稍微转化一下。

有 $S=\sum a_i$ 个小球排成一列，在 $S+1$ 个空隙中放了 $n-1$ 个隔板（允许放在相同隔板中。不过这道题没有）。

而最终目标状态是隔板按照等差数列排列。每次操作可以新增一个隔板或者删掉一个隔板，问最小的操作次数。

这显然就是两个隔板集合的对称差的大小。进一步，只需要求出这两个集合的交的大小。

因此问题再次转化为：给定你 $n$ 个整数 $s_1$、$s_2$、$\cdots$、$s_n$，处理 $q$ 次询问，第 $i$ 次询问形如有多少个 $j$ 满足 $q_j \mid s_i$。

这个问题肯定是不好做的。

但是注意到 $q$ 应当是 $S$ 的因子，所以本质上的 $s$ 和 $q$ 都只有 $O(d(S))$ 个（你可以将 $s$ 转化为 $\gcd(s,S)$），也容易使用狄利克雷前缀和刻画它们的整除关系。

那么现在需要分解质因数。当然你可以 Pollard-Rho。

考虑分解出所有 $\le 10^6$ 的质因子。剩余的数如果 $\neq 1$，质因子一定都 $>10^6$，那么最多 $2$ 个。

所以我们可以设 $v = pq$，其中 $p$ 的所有质因子 $\le 10^6$，$q$ 所有质因子都 $> 10^6$。

显然 $p_1q_1 \mid p_2q_2$ 等价于 $p_1 \mid q_1$ 且 $p_2 \mid q_2$（因为 $p$ 和 $q$ 的质因子集合不交），所以可以暴力枚举 $q$ 之间的整除关系，使用狄利克雷前缀和刻画 $p$ 之间的整除关系。

```cpp
#include<bits/stdc++.h>
#define int long long 
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=1e5+10;
int n,ans[MAXN],a[MAXN],q,qr[MAXN],s,mul=1;
vector<int> p;
map<int,vector<pair<int,int>>> mp;
map<int,vector<int>> upd;
void dfs(int dep,int u,vector<int>& d) {
	if(dep==p.size()) return d.push_back(u),void();
	dfs(dep+1,u,d);
	if((mul/u)%p[dep]==0) dfs(dep,u*p[dep],d);
	return ;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n;
	ffor(i,1,n) cin>>a[i],s+=a[i],a[i]+=a[i-1];
	cin>>q;
	ffor(i,1,q) cin>>qr[i],ans[i]=-1;
	ffor(i,1,n-1) a[i]=__gcd(a[i],s);
	int tmp=s;
	ffor(i,2,1000000) if(tmp%i==0) {
		p.push_back(i);
		while(tmp%i==0) mul*=i,tmp/=i;
	}
	ffor(i,1,q) if(s%qr[i]==0) mp[qr[i]/__gcd(qr[i],mul)].push_back({__gcd(qr[i],mul),i});
	ffor(i,1,n-1) upd[a[i]/__gcd(a[i],mul)].push_back(__gcd(a[i],mul));
	vector<int> d;
	dfs(0,1,d);
	sort(d.begin(),d.end());
	reverse(d.begin(),d.end());
	for(auto mzx:mp) {
		int v1=mzx.first;
		auto vc=mzx.second;
		map<int,int> pre;
		for(auto pr:upd) if(pr.first%v1==0) for(auto id:pr.second) pre[id]++;
		for(auto pid:p) for(auto did:d) if(did%pid==0) pre[did/pid]+=pre[did];
		for(auto pr:vc) ans[pr.second]=pre[pr.first];
	}
	ffor(i,1,q) if(ans[i]==-1) cout<<ans[i]<<'\n';
	else cout<<(n-1+s/qr[i]-1-2*ans[i])<<'\n';
	return 0;
}
```

---

