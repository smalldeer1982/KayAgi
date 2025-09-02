# [ARC156B] Mex on Blackboard

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc156/tasks/arc156_b

有限個の非負整数からなる多重集合 $ S $ にたいして、$ \mathrm{mex}(S) $ を、$ S $ に含まれない最小の非負整数と定義します。例えば、$ \mathrm{mex}(\lbrace\ 0,0,\ 1,3\rbrace\ )\ =\ 2,\ \mathrm{mex}(\lbrace\ 1\ \rbrace)\ =\ 0,\ \mathrm{mex}(\lbrace\ \rbrace)\ =\ 0 $ です。

黒板に $ N $ 個の非負整数が書かれており、$ i $ 番目の非負整数は $ A_i $ です。

あなたは、以下の操作をちょうど $ K $ 回行います。

- 黒板に書かれている非負整数を $ 0 $ 個以上選ぶ。選んだ非負整数からなる多重集合を $ S $ として、$ \mathrm{mex}(S) $ を黒板に $ 1 $ 個書き込む。
 
最終的に黒板に書かれている非負整数の多重集合としてありうるものの個数を $ 998244353 $ で割ったあまりを求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N,K\ \leq\ 2\times\ 10^5 $
- $ 0\leq\ A_i\leq\ 2\times\ 10^5 $
- 入力される数値は全て整数
 
### Sample Explanation 1

操作後に得られる多重集合は、以下の $ 3 $ 通りです。 - $ \lbrace\ 0,0,1,3\ \rbrace $ - $ \lbrace\ 0,1,1,3\rbrace $ - $ \lbrace\ 0,1,2,3\ \rbrace $ 例えば、$ \lbrace\ 0,1,1,3\rbrace $ は黒板に書かれている $ 0 $ を選び、$ S=\lbrace\ 0\rbrace $ として操作をすることで得られます。

### Sample Explanation 2

操作後に得られる多重集合は、以下の $ 2 $ 通りです。 - $ \lbrace\ 0,0,0\ \rbrace $ - $ \lbrace\ 0,0,1\rbrace $ 操作で選ぶ整数は $ 0 $ 個でも良いことに注意してください。

## 样例 #1

### 输入

```
3 1
0 1 3```

### 输出

```
3```

## 样例 #2

### 输入

```
2 1
0 0```

### 输出

```
2```

## 样例 #3

### 输入

```
5 10
3 1 4 1 5```

### 输出

```
7109```

# 题解

## 作者：heaksicn (赞：3)

## 1 题意
有一个可重集合 $S$ 中有 $n$ 个数，对这个集合进行恰好 $k$ 次操作。

每次操作选出 $S$ 的任意一个子集 $S'$，将 $mex(S')$ 放入 $S$ 中。

问操作后的 $S$ 有多少种可能出现的情况。

## 2 思路

考虑每一次对 $S$ 操作可能会加入什么数。

若 $\operatorname{mex}(S)=x$，则 $S$ 中一定包含 $0$ 到 $x-1$ 的所有数字。

那么 将 $S$ 中的所有的 $i(0\leq i\leq x-1)$ 取出形成 $S'$，则此时 $\operatorname{mex}(S')=i$。

所以，每次操作可以加入 $0$ 到 $\operatorname{mex}(S)$ 中的任意一个数。

为了防止重复，我们将操作分为取 $\operatorname{mex}$ 和不取两个阶段。

在进行 $i$ 次取 $\operatorname{mex}$ 操作后，假设当前的 $\operatorname{mex}(S)=x$

那么在后面的 $k-i$ 次操作中，每一次操作都可以增加 $0$ 到 $x-1$ 的任何一个数。

这时就转化成了一个插板法经典 trick，方案数一共是 $C_{x+k-i-1}^{k-i-1}$。

暴力枚举 $i$ 求和即可。

时间复杂度 $O(k)$。

## 3 code

```
//Man always remember love because of romance only!
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod=998244353;
inline int read(){
    int X=0,w=0; char ch=0;
    while(!isdigit(ch)) {w|=ch=='-';ch=getchar();}
    while(isdigit(ch)) X=(X<<3)+(X<<1)+(ch^48),ch=getchar();
    return w?-X:X;
}
inline void write(int x){
	if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
int a[200001];
int mp[1000001];
int qpow(int x,int y){
	int res=1;
	while(y){
		if(y&1) res=res*x%mod;
		x=x*x%mod;
		y>>=1;
	}
	return res;
}
int fac[500001],inv[500001];
int C(int n,int m){
	return fac[n]*inv[m]%mod*inv[n-m]%mod;
}
int g[200001];
signed main(){
	int n=read(),k=read();
	for(int i=1;i<=n;i++) a[i]=read(),mp[a[i]]++;
	fac[0]=inv[0]=1;
	for(int i=1;i<=5e5;i++){
		fac[i]=fac[i-1]*i%mod;
		inv[i]=qpow(fac[i],mod-2)%mod;
	}
	int now=0;
	while(mp[now]) now++;
	for(int i=1;i<=k;i++){
		g[i]=now;
		mp[now]=1;
		while(mp[now]) now++;
	}
//	for(int i=1;i<=k;i++) cout<<g[i]<<" ";
//	puts(""); 
	int ans=0;
	for(int i=1;i<=k;i++){
		ans=(ans+C(g[i]+k-i,k-i+1))%mod; 
	}
	ans++;
	write(ans);
	return 0;
}

```

---

## 作者：suzhikz (赞：2)

首先我们计算是最后的结果的个数，我们并不关心取的顺序，所以我们先取没有的，在取有的。这样方便不重不漏的计算。

发现如果这样的话，取已经有的数的方案数可以拿排列组合直接算，所以我们考虑直接枚举取几个没有的。

然后贡献统一在下一个没有的数前计算。

详细说下怎么算答案。假设要新增 $us$ 个不同的元素，然后新增完之后可以在 $i$ 个数内随便取，所以答案就是在 $i$ 个数内，每种数可以无限取，取 $k-us$ 次，那么他的贡献就是 $\binom{i+k-us-1}{k-us}$。

复杂度 $O(n\log_2n)$

```cpp
#include<bits/stdc++.h>//Are dreams merely lost wings in the concrete jungle？
#define il inline
#define reg register
#define ll long long
#define popcount __builtin_popcount
using namespace std;
//#define int __int128
inline void read(int &n){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}n=x*f;}
inline void read(ll &n){ll x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}n=x*f;}
const int N=4e5+5,mod=998244353;
int n,k;
int cnt[N];
ll ans;
ll qpow(ll x,int y){
	ll re=1;
	while(y){
		if(y&1)re=re*x%mod;
		x=x*x%mod;y>>=1;
	}
	return re;
}
ll jie[N],inv[N];
void init(){
	jie[0]=1;
	for(int i=1;i<N;i++)jie[i]=jie[i-1]*i%mod;
	inv[N-1]=qpow(jie[N-1],mod-2);
	for(int i=N-2;i>=0;i--)inv[i]=inv[i+1]*(i+1)%mod; 
}
ll C(int x,int y){
	return jie[x]*inv[y]%mod*inv[x-y]%mod;
}
int main(){
	init();
	read(n);read(k);
	for(int u,i=1;i<=n;i++){
		read(u);cnt[u]++;
	}
	int us=0;
	for(int i=0;i<N;i++){
		if(cnt[i]==0){
			if(i!=0){
				ans=ans+C(i+k-us-1,k-us);ans%=mod;
			}
			us++;
			if(us>k)break;
		}
	}
	cout<<ans;
	return 0;
}


```

---

## 作者：Otue (赞：2)

### 题目大意
给定 $N$ 个元素的数组 $A$，每次操作你可以从数组中选出任意个元素，然后向数组中加入这些元素的  $mex$ 。

问 $K$ 次操作后，可以得到多少种不同的数组。
### 思路
假如你能向数组中加入 $x$ 且 $x$ 是你写的最大整数，那么数组中 $0\sim x-1$ 绝对都出现过一次。 因为如果 $x-1$ 不存在的话加入的数会变成 $x-1$ 。第一次写入 $x$ 后，之后就可以加入 $0$ 到 $x$ 之间的任何整数。

观察到值域不大，考虑枚举最大整数 $x$。设你需要 $cnt$ 次才能写下 $x$ 这个数，那么你写下 $x$ 这个数后就还剩 $K-cnt$ 次操作机会，问题转化成使用 $K-cnt$ 次操作，每次操作写下 $0\sim x$ 任意一个数，问最后有多少个多重集合。

这不就等价于 $n$ 个小朋友分 $m$ 个苹果吗？（在这里 $n=x+1$，$m=K-cnt$）。当然不保证 $n$ 个小朋友每个都要分至少一个苹果。排列组合经典问题，$n$ 个小朋友分 $m$ 个苹果 $ \ = \ $ $n+m$ 个小朋友分 $m$ 个苹果且每个小朋友至少一个。

则答案为 ${(}^{\ \ \ m-1}_{n+m-1})$，在这里答案就为 ${(}^{ \ \ \  \  \ \  \ x}_{K-cnt+x})$。

参考代码：[code](https://pastebin.ubuntu.com/p/Hk2YPqNcNM/)
### 代码
```c++
#include <bits/stdc++.h>
using namespace std;

#define int long long
const int N = 1e6 + 5, mod = 998244353;
int T, n, k, a[N], vis[N], p[N], res;
char s[N];

int qpow(int a, int k, int p) {
    int res = 1;
    while (k) {
        if (k & 1) res = res * a % p;
        a = a * a % p;
        k >>= 1;
    }
    return res;
}

int C(int a, int b) {
    return p[a] * qpow(p[b], mod - 2, mod) % mod * qpow(p[a - b], mod - 2, mod) % mod;
}

signed main() {
    cin >> n >> k;

    for (int i = 1; i <= n; i++) cin >> a[i], vis[a[i]]++;
    p[0] = 1;
    for (int i = 1; i <= N - 5; i++) p[i] = p[i - 1] * i % mod;
    int cnt = 0;
    for (int i = 0; i <= N - 5; i++) {
        if (vis[i] == 0) cnt++;
        if (vis[i + 1]) continue;
        if (cnt > k) break;
        res = (res + C(k - cnt + i, i)) % mod;
    }
    cout << res << endl;
}
```

---

## 作者：I_like_magic (赞：1)

这道题其实不难。

我们先把原先 $A$ 集合去重。

然后，我们观察最终集合 $A$ 的情况。

先定义 $m$ 表示后来加入的数中最大的值，$cnt_i$ 表示最终集合 $A$ 中的数字 $i$ 的数量。

我们发现，最终集合需要满足对于任意的整数 $x\in[0, m]$，$cnt_x \ge 1$。因为如果存在整数 $x\in[0, m]$，$cnt_x = 0$，那么无论如何，加入集合 $A$ 的数都不可能超过 $x$，要超过 $x$ 需要先把 $x$ 填好。

因此，我们可以枚举 $m$ 的值。

对于当前的 $m$，我们统计出原先 $A$ 集合中小于等于 $m$ 的数字个数，然后再加上 $K$，即为最终 $A$ 集合 $\sum\limits_{i = 0}^{m}cnt_i$ 的值。

我们可以发现，只要满足 3 段前说明的条件，那么最终的 $A$ 一定是合法的，我们已经对 $A$ 集合去重了，那么每一个 $x\in[0, m]$ 可以取到的最小值就是 $1$。我们使用插板法计算可能的结果数。

设 $W = \sum\limits_{i = 0}^{m}cnt_i$，那么一共有 $W - 1$ 个空，需要插 $m$ 个板子。对于当前 $m$，答案就是 $\tbinom{W - 1}{m}$。

需要注意的是，如果对于某个 $m$，原集合 $A$ 中存在 $m + 1$，那么 $cnt_{m + 1} = 1$，$m$ 的贡献已经在 $m + 1$ 中统计过了。所以不需要统计这个 $m$。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long // 开 long long 是为了防止取模前爆 int
using namespace std;
const int N = 400005, P = 998244353; // 数据范围及模数
int n, k; // 原集合 A 的元素数量及操作个数
bool f[N]; // 标记某数是否存在于原集合
int sum = 0;  // 当前枚举到的 m 对应的 W 值 
int ans = 0;  // 答案
int frac[N];  // 阶乘数组
int ksm(int a, int n) { // 快速幂
    if(n == 0) return 1;
    if(n == 1) return a % P; 
    int d = ksm(a, n / 2);
    d = d * d % P;
    if(n & 1) d = d * a % P;
    return d;
}
int inv(int a) {  // 逆元
    return ksm(a, P - 2); // 不会的可以去看 OI wiki 乘法逆元
}
int C(int n, int m) { // 组合数
    return frac[n] * inv(frac[n - m]) % P * inv(frac[m]) % P; // 计算组合数
}
signed main() {
    cin >> n >> k;
    frac[0] = 1;
    for(int i = 1; i <= n + k; i ++) frac[i] = frac[i - 1] * i % P;
    for(int i = 1; i <= n; i ++) {
        int a;
        cin >> a;
        f[a] = 1; // 标记 a 存在于原集合 A
    }
    sum = k;
    for(int i = 0; ; i ++) {
        if(f[i]) sum ++;  // 修改当前的 M 值
        if(sum < i) break; // 无法满足条件
        if(f[i + 1]) continue;  // 无需统计
        ans += C(sum - 1, i); // 将贡献加入答案
        ans %= P; // 对 P 取模
    }
    printf("%d\n", ans); // 输出答案
    return 0;
}
```

---

## 作者：lsj2009 (赞：1)

## Solution

考虑去枚举最终序列的 $\text{mex}$。我们可以边填边计算，设若当前枚举得 $\text{mex}$ 为 $k$，同时我们可以继续再填 $m$ 个，那么接下来我们任意一次操作可以造出一个在 $[0,k)$ 范围内的整数，因为此时我们已经拥有 $[0,k)$ 内的所有整数，如果要造出 $x$，我们直接取 $S=[0,k)\cap\mathbb{N}-\{x\}$；而且我们只能造出这个范围内的数，因为如果要造出更大的数，则我们需要一个 $k$ 以及更大的数，这与 $\text{mex}=k$ 相矛盾。

那么我们就把这个问题转换为：

> 给定两个整数 $k,m$ 和一个初始为空的可重集 $S$，进行 $m$ 次操作，每次选择一个整数 $x\in[0,k)$，然后令 $S\gets S+\{x\}$，求最终集合 $S$ 的可能个数。

然后这是一个著名问题，答案为 $C_{k+m-1}^m$，证明如下：

设在 $S$ 中有 $x_i$ 个 $i$，则答案为 $x_0+x_1+\cdots+x_{k-1}=m$ 的自然数解个数，令 $y_i\gets x_i+1$，则 $y_0+y_1+\cdots+y_{k-1}=m+k$ 的正整数解个数，将其想象为 $m+k$ 个球，然后一共有 $m+k-1$ 个空隙，我们要将其分为 $k$ 个部分，则得答案为 $C_{k+m-1}^{k-1}=C_{k+m-1}^m$ 个。

然后就做完了。

## Code

正解：<https://atcoder.jp/contests/arc156/submissions/38985426>。

---

## 作者：linyihdfj (赞：0)

[更优秀的阅读体验](https://www.cnblogs.com/linyihdfj/p/17150125.html)
# B.Mex on Blackboard
## 题目分析：
我们其实可以考虑从小到大依次决定每一个数选择多少，也就是考虑完了前 $i$ 个数选的情况再考虑 $i+1$ 这个数，这样显然是没影响的。

这个其实就启发我们直接枚举选择的最大的数是多少，假设为 $i$ 且为了使得序列存在 $[1,i]$ 还剩余 $k$ 次操作，那么答案其实就是：
$$
\binom{k+i}{i}
$$
但是会出现一个问题，假设我们现在选择的数为 $x$ 但是序列中原本就存在 $x+1$，这样就会算重最大为 $x$ 的情况。但是这个也不用容斥，出现这种情况直接跳过 $x$ 就好了。 
## 代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MX = 1e6+5;
const int MOD = 998244353;
int cnt[MX*2],a[MX],fac[MX*2+5],inv[MX*2+5];
int mod(int x){
	return x % MOD;
}
int power(int a,int b){
	int res = 1;
	while(b){
		if(b & 1)	res = mod(res * a);
		a = mod(a * a);
		b >>= 1;
	}
	return res;
}
int binom(int n,int m){
	return mod(fac[n] * mod(inv[n - m] * inv[m]));
}
signed main(){
	int n,k;scanf("%lld%lld",&n,&k);
	for(int i=1; i<=n; i++)	scanf("%lld",&a[i]),cnt[a[i]]++;
	fac[0] = 1;
	for(int i=1; i<=MX*2; i++)	fac[i] = mod(fac[i-1] * i);
	inv[MX*2] = power(fac[MX*2],MOD-2);
	for(int i=MX*2-1; i>=0; i--)	inv[i] = mod(inv[i+1] * (i+1));
	int ans = 0;
	for(int i=0; i<=MX; i++){
		if(!cnt[i])	k--;
		if(k <= 0){
			ans++;
			break;
		}
		while(cnt[i+1])	i++;
		ans = mod(ans + binom(k+i,i));
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

