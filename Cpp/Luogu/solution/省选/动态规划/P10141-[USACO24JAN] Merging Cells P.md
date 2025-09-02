# [USACO24JAN] Merging Cells P

## 题目背景

**注意：本题的内存限制为 512MB，通常限制的两倍。**

## 题目描述

Bessie 正在玩一个著名的在线游戏，游戏中有许多不同编号和大小的细胞。细胞会被其他细胞吞噬，直到只剩下一个胜利者。

有 $N$（$2\le N\le 5000$）个细胞从左到右排成一行，编号为 $1\ldots N$，初始大小为 $s_1,s_2,\ldots,s_N$（$1\le s_i\le 10^5$）。当存在多个细胞时，均匀地随机选择一对相邻细胞，并根据以下规则合并为一个新的细胞：

如果编号为 $a$ 且当前大小为 $c_a$ 的细胞与编号为 $b$ 且当前大小为 $c_b$ 的细胞合并，则合并成的细胞的大小为 $c_a+c_b$，且编号等于较大细胞的编号，并列时则为编号较大的细胞的编号。形式化地说，合并成的细胞的编号为 $\begin{cases}a & c_a>c_b\\b & c_a<c_b\\ \max(a,b) & c_a=c_b \end{cases}$。

对于 $1\ldots N$ 范围内的每个编号 $i$，最终的细胞具有编号 $i$ 的概率可以以 $\frac{a_i}{b_i}$ 的形式表示，其中 $b_i\not \equiv 0 \pmod {10^9+7}$。输出 $a_ib_i^{-1}\pmod {10^9+7}$。 

## 说明/提示

### 样例解释 1

存在两种可能性，其中 $(a,b)\to c$ 表示编号为 $a$ 和 $b$ 的细胞合并成了一个编号为 $c$ 的新的细胞。

$(1, 2) \to 2, (2, 3) \to 2$  
$(2, 3) \to 3, (1, 3) \to 3$

所以有各 $\frac{1}{2}$ 的概率最终的细胞具有编号 $2$ 或 $3$。


### 样例解释 2

六种可能性如下：

$(1, 2) \to 1, (1, 3) \to 1, (1, 4) \to 1$  
$(1, 2) \to 1, (3, 4) \to 4, (1, 4) \to 1$  
$(2, 3) \to 3, (1, 3) \to 1, (1, 4) \to 1$  
$(2, 3) \to 3, (3, 4) \to 3, (1, 3) \to 3$  
$(3, 4) \to 4, (2, 4) \to 4, (1, 4) \to 4$  
$(3, 4) \to 4, (1, 2) \to 1, (1, 4) \to 1$

所以有 $\frac{2}{3}$ 的概率最终的细胞具有编号 $1$，各 $\frac{1}{6}$ 的概率最终的细胞具有编号 $3$ 或 $4$。

### 测试点性质

- 测试点 3：$N\le 8$。
- 测试点 $4-8$：$N\le 100$。
- 测试点 $9-14$：$N\le 500$。
- 测试点 $15-22$：没有额外限制。

## 样例 #1

### 输入

```
3
1 1 1```

### 输出

```
0
500000004
500000004```

## 样例 #2

### 输入

```
4
3 1 1 1```

### 输出

```
666666672
0
166666668
166666668```

# 题解

## 作者：Lonely_NewYear (赞：7)

# P10141 题解

## 题目大意

有 $n$ 个细胞排成一排，第 $i$ 个细胞大小为 $c_i$，重复 $n-1$ 次，第 $i$ 次从当前的 $n-i+1$ 个细胞中随机选出相邻的两个，并让大的吞噬小的（大小相同右吞左），被吞噬的细胞消失并将大小累加到留下的细胞上。求每个细胞活到最后的概率，对 $1e9+7$ 取模，$n\le5000$。

## 题目分析

对于每个细胞单独考虑，设当前考虑的细胞为 $i$，容易得到 $dp_{l,r}$ 表示 $l,r$ 区间最后活下来的是 $i$ 的概率，转移需要枚举最后一次吞噬。单个细胞复杂度 $O(n^3)$，总复杂度 $O(n^4)$，很难优化到 $O(n^2)$。

上面的做法转移的顺序是合并从小区间到大区间的顺序，正难即反，可以发现如果枚举最后一次合并，则最后留下的细胞必定来自总和较大的区间。也就是说，倒着做把合并变成分裂，每次会确定最后留下的细胞来自左侧的区间还是右侧，并将另一部分舍去不必再考虑。设 $dp_{l,r}$ 表示区间 $1,n$ 经过若干次分裂留下了区间 $l,r$ 的概率。转移时枚举 $l\le k<r$ 表示分裂出 $l,k$ 和 $k+1,r$，若 $sum_{l\sim k}>sum_{k+1\sim r}$，则将 $dp_{l,k}$ 加上 $\frac{dp_{l,r}}{r-l}$，否则让 $dp_{k+1,r}$ 加上后者。直接实现复杂度 $O(n^3)$。

继续优化，考虑所有能转移到 $dp_{l,r}$ 的区间要不然左端点是 $l$ 要不然右端点是 $r$。两部分类似，下面只讨论前者。那么如果右端点是 $k$，则要求 $sum_{l,r}>sum_{r+1,k}$，容易发现可取的 $k$ 是以 $r+1$ 为左端点的一段区间。这段区间的右端点通过对每一个 $l$ 做双指针是好求的（区间 dp 时通过枚举区间长度从大到小，枚举到的左端点为 $l$ 的区间右端点必然是递减的，随着 $r$ 递减双指针找到最大的 $k$ 即可），则 $dp_{l,r}$ 会加上 $\sum_{i=r+1}^k\frac{dp_{l,i}}{i-l}$，对每一个 $l$ 维护 $\frac{dp_{l,r}}{r-l}$ 后缀和即可。复杂度 $O(n^2)$。

## 代码

```
#include<bits/stdc++.h>
using namespace std;
const int MAXN=5010,mod=1e9+7;
int inv(int a){
	int b=mod-2,r=1;
	while(b){
		if(b&1)r=1ll*r*a%mod;
		a=1ll*a*a%mod;
		b>>=1;
	}
	return r;
}
void add(int &i,int j){
	i=(i+j>=mod?i+j-mod:i+j);
}
int n;
int s[MAXN],v[MAXN];
int d[MAXN][MAXN],f[MAXN][MAXN],g[MAXN][MAXN],p[MAXN],q[MAXN];
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>s[i];
		s[i]+=s[i-1];
		v[i]=inv(i);
	}
	d[1][n]=f[1][n]=g[1][n]=v[n-1];
	for(int i=1;i<=n;i++)p[i]=n,q[i]=1;
	for(int h=n-1;h>=1;h--){
		for(int i=1,j=h;j<=n;i++,j++){
			while(s[j]-s[i-1]<=s[p[i]]-s[j])p[i]--;
			add(d[i][j],f[i][j+1]);
			add(d[i][j],mod-f[i][p[i]+1]);
			while(s[j]-s[i-1]<s[i-1]-s[q[i]-1])q[i]++;
			add(d[i][j],g[i-1][j]);
			add(d[i][j],mod-g[q[i]-1][j]);
			if(h>1){
				d[i][j]=1ll*d[i][j]*v[j-i]%mod;
				f[i][j]=f[i][j+1];
				add(f[i][j],d[i][j]);
				g[i][j]=g[i-1][j];
				add(g[i][j],d[i][j]);
			}
		}
	}
	for(int i=1;i<=n;i++)cout<<d[i][i]<<'\n';
	return 0;
}
```

谢谢观看！

---

## 作者：Perta (赞：6)

设 $f_{l,r}$ 表示区间 $[l,r]$ 内的编号为最终细胞编号的概率。

有转移：
$$
f_{l,r}=\sum_{1\leq i<l\ \land \ S(i,l-1)\leq S(l,r)}{\frac{f_{i,r}}{r-i}}+\sum_{r<i\leq n\ \land \ S(r+1,i)<S(l,r)}{\frac{f_{l,i}}{i-l}}
$$
其中 $S_{l,r}=\sum_{i=l}^ra_i$，边界条件 $f_{1,n}=1$。

朴素转移是 $O(n^3)$ 的，考虑优化。

注意到当 $l$ 固定时，$S(l,r)$ 随 $r$ 的减小而减小。设 $g_{l,r}$ 表示满足 $1\leq i<l\ \land \ S(i,l-1)\leq S(l,r)$ 的最小的 $i$，有 $g_{l,r}\geq g_{l,r+1}$；另一边同理。利用单调性继承上一次转移的指针即可做到 $O(n^2)$。

第 $i$ 个答案为 $f_{i,i}$。

[Code](https://www.luogu.com.cn/paste/eyy5m183)

---

## 作者：Purslane (赞：5)

# Solution

这题简单。

首先观察到如果 $[l,r]$ 这段区间的细胞能合并成一个细胞，那么这个细胞的大小是固定的。进一步发现，这个细胞合并的最后一步由 $[l,pos]$ 到 $[pos+1,r]$ 这两段完成的。容易发现，最后一步这个 $pos$ 是在 $[l,r)$ 中等概率选取的。（证明的话对区间长度使用数学归纳法易得）

所以你可以看做这样一个过程：现在有个活生生的大细胞，大小为 $\sum_{i=l}^r a_i$，代表区间为 $[l,r]$。最开始 $l=1$，$r=n$。每次等概率选择一个 $pos \in [l,r)$，把区间分裂为 $[l,pos]$ 和 $[pos+1,r]$，并且选择其中更为优秀者。最后观察每个长度为 $1$ 的细胞。

很容易设 $dp_{l,r}$ 为分裂出 $[l,r]$ 的概率（准确来说是分裂途中经过这个点的概率）。枚举这个区间往左拓展多少或者往右拓展多少，用前缀和优化即可。

代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=5000+10,MOD=1e9+7;
int n,a[MAXN],dp[MAXN][MAXN],pre[MAXN][MAXN],suf[MAXN][MAXN],inv[MAXN];
ll qpow(ll bs,int p) {
	ll res=1;
	while(p) {
		if(p&1) res=res*bs%MOD;
		bs=bs*bs%MOD,p>>=1;
	}
	return res;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n; ffor(i,1,n) cin>>a[i],a[i]+=a[i-1],inv[i]=qpow(i,MOD-2);
	dp[1][n]=1,suf[1][n]=pre[n][1]=inv[n-1];
	roff(len,n-1,1) for(int l=1,r=len;r<=n;l++,r++) {
		//向右扩展到 pos，有 a_pos-a_r < a_r - a_{l-1} => a_pos <= 2 a_r - a_{l-1} - 1
		int pos=upper_bound(a,a+n+1,a[r]+a[r]-a[l-1]-1)-a-1;
		dp[l][r]=(dp[l][r]+suf[l][r+1]-suf[l][pos+1])%MOD;
		//向左扩展到 pos，有 a_r-a_{l-1} >= a_{l-1}-a{pos-1} => a_{pos-1}>=2a_{l-1}-a_r
		pos=lower_bound(a,a+n+1,a[l-1]+a[l-1]-a[r])-a+1;
		dp[l][r]=((dp[l][r]+pre[r][l-1])%MOD-pre[r][pos-1])%MOD;
		
		int v=1ll*dp[l][r]*inv[len-1]%MOD;
		suf[l][r]=(suf[l][r+1]+v)%MOD,pre[r][l]=(pre[r][l-1]+v)%MOD;
	}
	ffor(i,1,n) cout<<(dp[i][i]%MOD+MOD)%MOD<<'\n';
	return 0;
}
```

---

## 作者：Claire0918 (赞：1)

记 $sum_{l, r} = \sum_{i = l}^{r} s_i$。

题目的操作是合并，不难想到区间 DP。先枚举要求答案的细胞 $x$，设 $f_{l, r}$ 表示 $[l, r]$ 中细胞合并完成后编号为 $x$ 的概率。转移需要枚举分点，时间复杂度 $\mathcal{O}(n^3)$，还需要枚举 $x$，整体时间复杂度 $\mathcal{O}(n^4)$。并且转移几乎没有优化空间。

枚举 $x$ 非常不好，我们考虑将 $x$ 通过状态表示出来。具体地，我们改设 $f_{l, r}$ 表示最终剩余的细胞编号在 $[l, r]$ 的概率。那么 $x$ 的答案即可以被表示为 $f_{x, x}$。

首先有初始化 $f_{1, n} = 1$。转移时考虑枚举一个 $k \in [l, r)$，表示 $[l, r]$ 是由 $[l, k]$ 和 $[k + 1, r]$ 合并而来。如果 $sum_{l, k} > sum_{k + 1, r}$，那么 $[l, r]$ 将保留 $[l, k]$ 的答案，即 $\dfrac{f_{l, r}}{r - l} \to f_{l, k}$；否则 $[l, r]$ 将保留 $[k + 1, r]$ 的答案，即 $\dfrac{f_{l, r}}{r - l} \to f_{k + 1, r}$。我们得到了 $\mathcal{O}(n^3)$ 的刷表法转移。

考虑将刷表法转化为填表法。进行一定的移项和换元，不难得到
$$
f_{l, r} = \sum_{k = r + 1}^{n} [sum_{l, r} > sum_{r + 1, k}] \times \frac{f_{l, k}}{k - l} + \sum_{k = 1}^{l - 1} [sum_{l, r} \geq sum_{k, l - 1}] \times \frac{f_{k, r}}{r - k}
$$

对于确定的 $(l, r)$，能满足 $sum_{l, r} > sum_{r + 1, k}$ 的 $k$ 显然是一段区间，能满足 $sum_{l, r} \geq sum_{k, l - 1}$ 的 $k$ 也是一段区间。维护 $\dfrac{f_{l, k}}{k - l}$ 的后缀和和 $\dfrac{f_{k, r}}{r - k}$ 的前缀和，二分 $k$ 的上（下）界即可做到 $\mathcal{O}(n^2\log n)$ 转移。

我们又注意到对于一个确定的 $l$，随着 $r$ 减小，满足 $sum_{l, r} > sum_{r + 1, k}$ 的 $k$ 的上界减小；对于一个确定的 $r$，随着 $l$ 增加，满足 $sum_{l, r} \geq sum_{k, l - 1}$ 的 $k$ 的下界增加。考虑使用双指针，对于一个确定的 $l$ 和一个确定的 $r$ 维护一个指针，即可做到 $\mathcal{O}(n^2)$ 转移。

Code：
```cpp
#include<bits/stdc++.h>
#define mem(a, v) memset(a, v, sizeof(a));

using namespace std;

const int maxn = 5000 + 10, mod = 1e9 + 7;

int n;
int a[maxn], sum[maxn][maxn], f[maxn][maxn], pre[maxn][maxn], suf[maxn][maxn], p[maxn], q[maxn], inv[maxn];

inline long long ksm(long long a, long long b){
    long long res = 1;
    while (b){
        if (b & 1){
            res = res * a % mod;
        }
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

template<typename Tp_x, typename Tp_y>
inline int mod_add(Tp_x x, Tp_y y){
    x += y;
    return x >= mod ? x -= mod : x;
}

int main(){
    scanf("%d", &n);
    for (int i = 1; i <= n; i++){
        scanf("%d", &a[i]);
        for (int j = 1; j <= i; j++){
            sum[j][i] = sum[j][i - 1] + a[i];
        }
        inv[i] = ksm(i, mod - 2);
    }
    fill(p + 1, p + n + 1, n), fill(q + 1, q + n + 1, 1);
    f[1][n] = 1, pre[1][n] = suf[1][n] = inv[n - 1];
    for (int len = n - 1; len; len--){
        for (int l = 1; l + len - 1 <= n; l++){
            const int r = l + len - 1;
            while (p[l] >= r + 1 && sum[l][r] <= sum[r + 1][p[l]]){
                p[l]--;
            }
            f[l][r] = mod_add(suf[l][r + 1], mod - suf[l][p[l] + 1]);
            while (q[r] <= l - 1 && sum[l][r] < sum[q[r]][l - 1]){
                q[r]++;
            }
            f[l][r] = mod_add(f[l][r], mod_add(pre[l - 1][r], mod - pre[q[r] - 1][r]));
            pre[l][r] = mod_add(pre[l - 1][r], (long long)f[l][r] * inv[r - l] % mod);
            suf[l][r] = mod_add(suf[l][r + 1], (long long)f[l][r] * inv[r - l] % mod);
        }
    }
    for (int i = 1; i <= n; i++){
        printf("%d\n", f[i][i]);
    }

return 0;
}
```

---

## 作者：zdd0342 (赞：1)

## [[USACO24JAN] Merging Cells P](https://www.luogu.com.cn/problem/P10141)

定义 $S(l,r)=\sum_{i=l}^{r}a_i$。

证明：区间 $[l,r]$ 合并后的细胞只有一个状态。

> 细胞大小是 $\sum_{i=l}^{r}a_i$ 为定值。
>
> 具体的编号不重要，因为之后只会和 $[1,l-1]$ 和 $[r+1,n]$ 的编号比较，$[l,r]$ 中每一个数的结果都是一样的。

这样就很区间 `dp`。

### 第一

对于每一个位置 $x$ 考虑。

定义 $dp_{l,r}$ 表示 $[l,r]$ 合并后编号为 $x$ 的概率。若 $x\notin [l,r],dp_{l,r}=0$。

$dp_{x,x}=1$。

转移：
$$
dp_{l,r}=\sum_{k=l}^{r-1}\frac{1}{r-l}([S(l,k)>S(k+1,r)]dp_{l,k}+[S(l,k)\le S(k+1,r)]dp_{k+1,r})
$$
复杂度单次 $O(n^3)$，总共 $O(n^4)$。

可以通过双指针或者二分枚举 $k$ 做到 $O(n^3)$ 或者 $O(n^3\log n)$。

好像没有优化空间了。

### 第二

从上往下考虑，定义 $dp_{l,r}$ 表示最后编号 $res\in[l,r]$ 的概率。

$dp_{1,n}=1$。

转移：
$$
\left\{\begin{matrix} 
  dp_{l,k}\leftarrow dp_{l,r}\times \frac{1}{r-l} &S(l,k)>S(k+1,r)\\  
  dp_{k+1,r}\leftarrow dp_{l,r}\times \frac{1}{r-l} &S(l,k)\le S(k+1,r)\\  
\end{matrix}\right. 
$$
改写成填表：
$$
dp_{l,r}=\left\{\begin{matrix} 
  \sum_{R=r+1}^{n}dp_{l,R}\times \frac{1}{R-l}&S(l,r)>S(r+1,R)\\
  \sum_{L=1}^{l-1}dp_{L,r}\times \frac{1}{r-L}&S(L,l-1)\le S(l,r)\\
\end{matrix}\right.
$$
发现 $L$ 和 $R$ 的可取区间都是一个区间，可以直接二分端点。

然后记录：
$$
lft_{i,j}=\sum_{r=j}^{n}dp_{i,r}\times\frac{1}{r-i}\\
rgt_{i,j}=\sum_{l=1}^{i}dp_{l,j}\times\frac{1}{j-l}\\
$$
就可以转移了。

---

## 作者：_Ch1F4N_ (赞：0)

首先考虑概率转计数，考虑用类似区间 dp 的方式拆解问题，具体地，如果你把区间 $[l,r]$ 拆为 $[l,k]$ 与 $[k+1,r]$，那么方案数贡献就是区间 $[l,k]$ 与 $[k+1,r]$ 的贡献再乘上合并两个区间内的操作序列的方案，也就是 ${r-l-1} \choose {k-l}$。

直接合并区间，计算每个数作为一个区间最后剩下的数的概率的做法复杂度太高了。

考虑转置整个过程，不难发现当你把区间 $[l,r]$ 拆为 $[l,k]$ 与 $[k+1,r]$ 后，区间 $[l,r]$ 最后剩下的数到底是从哪个区间转移而来是确定的，所以设计状态 $dp_{l,r}$ 表示最后剩下的数由区间 $[l,r]$ 转移而来，区间 $[l,r]$ 内的合并方式还未确定的前提下的方案数。

注意到 $dp_{l,r}$ 转移到 $dp_{l,k}$ 的系数为 ${{r-l-1} \choose {k-l} }\times (r-k-1)!$，化简后发现就是 $\frac{(r-l-1)!}{(k-l)!}$，不妨先认为转移系数是 $(r-l-1)!$ 等考虑到区间 $[l,k]$ 时再让 $dp_{l,k} \gets dp_{l,k} \times \frac{1}{(k-l)!}$，对于 $dp_{l,r}$ 转移到 $dp_{k+1,r}$ 的情形可以类似地处理，又注意到 $[l,r]$ 究竟是转移到 $[l,k]$ 还是 $[k+1,r]$ 只与 $k$ 和某一个分界点的大小关系有关，所以贡献到的区间形如一个端点固定，另一个端点在一个区间内，因此可以用差分优化贡献过程，将差分数组贡献到 dp 数组的顺序恰好与 dp 的转移顺序一致，因此可以一同完成，求出分界点我写的是直接二分，时间复杂度 $O(n^2 \log n)$，常数很小所以过了。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod = 1e9+7;
const int maxn = 5e3+114;
int qpow(int a,int b){
    if(b==0) return 1;
    if(b==1) return a;
    int res=qpow(a,b>>1);
    res=1ll*res*res%mod;
    if(b&1) res=1ll*res*a%mod;
    return res;
}
int dp[maxn][maxn],fac[maxn],inv[maxn];
int C(int n,int m){
    return 1ll*fac[n]*inv[m]%mod*inv[n-m]%mod;
}
int addl[maxn][maxn];//l=i,r<=j 的加法
int addr[maxn][maxn];//l>=i,r=j 的加法
int n,pre[maxn];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n;
    fac[0]=inv[0]=1;
    for(int i=1;i<=n;i++) fac[i]=1ll*fac[i-1]*i%mod,inv[i]=qpow(fac[i],mod-2);
    for(int i=1;i<=n;i++) cin>>pre[i],pre[i]+=pre[i-1];
    dp[1][n]=fac[n-1];
    for(int len=n;len>1;len--){
        for(int l=1;l+len-1<=n;l++){
            int r=l+len-1;
            dp[l][r]=(1ll*dp[l][r]+1ll*addl[l][r])%mod;
            addl[l][r-1]=(1ll*addl[l][r-1]+1ll*addl[l][r])%mod;
            dp[l][r]=(1ll*dp[l][r]+1ll*addr[l][r])%mod;
            addr[l+1][r]=(1ll*addr[l+1][r]+1ll*addr[l][r])%mod;
            dp[l][r]=1ll*dp[l][r]*inv[r-l]%mod;
            int k=l-1;
            if(pre[l]-pre[l-1]<=pre[r]-pre[l]){
                int lt=l,rt=r;
                while(lt+1<rt){
                    int mid=(lt+rt)>>1;
                    if(pre[mid]-pre[l-1]<=pre[r]-pre[mid]) lt=mid;
                    else rt=mid;
                }
                k=lt;                
            }
            //[l,K] [K+1,r]
            //l<=K<=k 时划分到右区间
            if(k>=l){
                //K+1 \in [l+1,k+1]
                addr[l+1][r]=(1ll*addr[l+1][r]+1ll*dp[l][r]*fac[r-l-1]%mod)%mod;
                addr[k+2][r]=(1ll*addr[k+2][r]+mod-1ll*dp[l][r]*fac[r-l-1]%mod)%mod;
            }
            //k+1<=K<=r-1 时划分到右区间
            if(k+1<=r-1){
                //K \in [k+1,r]
                addl[l][r-1]=(1ll*addl[l][r-1]+1ll*dp[l][r]*fac[r-l-1]%mod)%mod;
                addl[l][k]=(1ll*addl[l][k]+mod-1ll*dp[l][r]*fac[r-l-1]%mod)%mod;
            }
        }
    }
    for(int i=1;i<=n;i++) dp[i][i]=(1ll*dp[i][i]+1ll*addl[i][i]+1ll*addr[i][i])%mod;
    for(int i=1;i<=n;i++) cout<<1ll*dp[i][i]*inv[n-1]%mod<<"\n";
    return 0;
}
```

---

## 作者：HYXLE (赞：0)

## [P10141 [USACO24JAN] Merging Cells P]([P10141 [USACO24JAN\] Merging Cells P - 洛谷 (luogu.com.cn)](https://www.luogu.com.cn/problem/P10141))

正难则反，考虑倒着考虑。

记 $sum_i$ 表示 $\sum_{j=1}^ia_i$。

设 $f_{l,r}$ 表示对于最后的细胞，其编号在 $l,r$ 的概率。

考虑对于一段区间的细胞，枚举 $1$ 个断点 $k$ ，表示上一步是从这里合并的。

不难发现，$f_{l,k}$ 能被 $f_{l,r}$ 转移到当且仅当 $sum_k -sum_l-1 > sum_r-sum_k$，$f_{k,r}$ 能被 $f_l,r$ 转移到当且仅当 $sum_r-sum_{k-1} \ge sum_{k-1} -sum_{l-1}$。

考虑改写一下这个式子，则有
$$
f_{l,r}=\sum_{k=r+1}^n \frac{f_{l,k}}{k-l}[sum_r-sum_{l-1} > sum_k-sum_r] + \sum_{k=1}^{l-1}\frac{f_{k,r}}{r-k}[sum_{l-1}-sum_k>sum_r-sum{l-1}]
$$
直接暴力做复杂度是 $O(n^3)$ 的，考虑优化。

不难发现，前后两种贡献方式的 $k$ 均为一段连续的区间，所以维护一个前缀和和一个后缀和即可。

时间复杂度为 $O(n^2)$。

### code

```cpp
#include<bits/stdc++.h>
#define ll long long
#define R register
using namespace std;
const int N=5005,mod=1e9+7;
inline ll qmul(ll a,ll b){
	ll ans=1;
	while(b){
		if(b&1)ans=ans*a%mod;
		a=(a*a)%mod;b>>=1;
	}
	return ans;
}
int n,a[N],f[N][N],suf[N][N],pre[N][N],inv[N];
int main(){
	ios::sync_with_stdio(0);cin.tie(0),cout.tie(0);
	cin>>n;for(R int i=1;i<=n;++i)cin>>a[i],a[i]+=a[i-1];
	for(R int i=1;i<=n;++i)inv[i]=qmul(i,mod-2);
	f[1][n]=1;suf[1][n]=pre[n][1]=inv[n-1];
	for(R int len=n-1;len>=1;--len){
		for(R int l=1,r=len;r<=n;++l,++r){
			int pos=upper_bound(a,a+n+1,2*a[r]-a[l-1]-1)-a-1;
			f[l][r]=(1ll*f[l][r]+suf[l][r+1]-suf[l][pos+1]+mod)%mod;
			pos=lower_bound(a,a+n+1,2*a[l-1]-a[r])-a+1;
			f[l][r]=(1ll*f[l][r]+pre[r][l-1]-pre[r][pos-1]+mod)%mod;
			int tmp=1ll*f[l][r]*inv[r-l]%mod;
			suf[l][r]=(suf[l][r+1]+tmp)%mod,pre[r][l]=(pre[r][l-1]+tmp)%mod;
		}
	}
	for(R int i=1;i<=n;++i)cout<<f[i][i]<<'\n';
	return 0;
}
```

---

## 作者：happybob (赞：0)

对于每个 $i$，考虑将整个合并过程分阶段，将所有包含 $i$ 的合并视为关键点，将整个合并过程分段。每个关键点，$i$ 目前对应了一段区间 $[l,r]$。每次扩展到 $[l,r']$ 或 $[l',r]$。

据此，设计区间 DP。$f_{l,r}$ 表示目前关键点区间为 $[l,r]$，之后的概率。每次从 $[l,r']$ 与 $[l',r]$ 转移。直接转移是 $O(n^3)$ 的，通过维护一些转移过程的前缀和即可做到 $O(n^2 \log n)$ 或 $O(n^2)$。

---

