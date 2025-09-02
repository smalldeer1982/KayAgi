# [ARC110D] Binomial Coefficient is Fun

## 题目描述

我们有一个包含 $N$ 个非负整数的序列 $A$。

对于所有长度为 $N$ 且和不超过 $M$ 的非负整数序列 $B$，求 $\prod_{i = 1}^N {B_i \choose A_i}$ 之和， 对 $(10^9 + 7)$ 取模。

## 说明/提示

- $1 \le N \le 2000$
- $1 \le M \le 10^9$
- $0 \le A_i \le 2000$

## 样例 #1

### 输入

```
3 5
1 2 1```

### 输出

```
8```

## 样例 #2

### 输入

```
10 998244353
31 41 59 26 53 58 97 93 23 84```

### 输出

```
642612171```

# 题解

## 作者：violin_wyl (赞：12)

~~组合意义天地灭，代数推导保平安！~~

首先 $M\gets M-\sum A_i$

即求 $\sum_{i=0}^m[x^i]\prod_{j=1}^N\frac{1}{(1-x)^{A_j+1}}$

$$[x^k]\prod_{j=1}^N\frac{1}{(1-x)^{A_j+1}}=[x^k]\frac 1{(1-x)^{\sum A_i + N}}=\binom{\sum A_i + N-1+k}{\sum A_i + N-1}$$

上指标求一下就是：

$$\binom{\sum A_i+N+M}{\sum A_i +N}=\frac{(\sum A_i+N+M)^{\underline{\sum A_i +N}}}{(\sum A_i +N)!}$$

$\mathcal O(n^2) $ 计算即可。

---

## 作者：Mikazuki_Munechika (赞：8)

考虑组合数的意义，我们把原问题等价为：

有 $n$ 组球，每组有 $a_i$ 个黑球，现在要插入若干个白球，白球的数量不超过：

$m - \sum a_i$ 的总方案数。

利用插板法，所求即为：

$\sum_{i=0}^{i\leq m-sum(a)} \binom{n-1+sum(a)+i}{i}=\binom{n+m}{m-sum(a)}=\binom{n+m}{n+sum(a)}$

由于 $n+sum(a)$ 比较小，计算时可以选择用 $n+m$ 的 $n+sum(a)$ 次下降幂除以  $n+sum(a)$ 的阶乘进行计算。

---

## 作者：SoyTony (赞：5)



考虑 $\binom{i}{j}$ 的生成函数 $F_j(x)=\sum_{i\ge 0} \binom{i}{j}x^i$，可以推导：

$$
\begin{aligned}
F_j(x)
&=\sum_{i\ge 0} \dbinom{i}{j}x^i\\
&=\sum_{i\ge 0} \left(\dbinom{i-1}{j-1}+\dbinom{i-1}{j}\right)x^i\\
&=\sum_{i\ge 0} \dbinom{i-1}{j-1}x^i+\sum_{i\ge 0} \dbinom{i-1}{j}x^i\\
&=xF_{j-1}(x)+xF_j(x)
\end{aligned}
$$

因此有 $F_j(x)=\frac{x}{1-x}F_{j-1}(x)$，而 $F_0(x)=\frac{1}{1-x}$，所以 $F_j(x)=\frac{x^j}{(1-x)^{j+1}}$。

设 $s=\sum_{i=1}^n a_i$，答案是求：

$$
\begin{aligned}
\sum_{j=s}^m [x^j]\prod_{i=1}^n F_{a_i}(x)
&=\sum_{j=s}[x^j]F_s(x)\\
&=\sum_{j=s}^m [x^j] \dfrac{x^s}{(1-x)^{s+n}}\\
&=\sum_{j=s}^m [x^{j-s}] \left(\dfrac{1}{1-x}\right)^{s+n}
\end{aligned}
$$

有一经典结论：

$$
\begin{aligned}
[x^i]\left(\dfrac{1}{1-x}\right)^j
&=[x^i](1-x)^{-j}\\
&=(-1)^i\dbinom{-j}{i}\\
&=(-1)^i\dfrac{(-j)^{\underline{i}}}{i!}\\
&=(-1)^i\dfrac{(-1)^ij^{\overline{i}}}{i!}\\
&=\dfrac{(i+j-1)^{\underline{i}}}{i!}\\
&=\dbinom{i+j-1}{i}
\end{aligned}
$$

因此答案就是：

$$\sum_{j=s}^m \dbinom{j+n-1}{s+n-1}=\dbinom{m+n}{s+n}$$

--- 

题解给出组合意义做法。

考虑把 $m$ 个求划分成 $n+1$ 段，第 $i$ 段为 $b_i$，再在第 $i$ 段选 $a_i$ 个球的方案数，把段与段之间看作球，即为在 $m+n$ 个球中，先选 $a_1$ 个球，再选一个球，再选 $a_2$ 个球，再选一个球……

结果为 $m+n$ 个球中选 $s+n$ 个，即 $\binom{m+n}{s+n}$。
 
提交记录：[Submission - AtCoder](https://atcoder.jp/contests/arc110/submissions/45283769)

---

## 作者：Math_rad_round (赞：4)

对于计数题，我们可以选择组合意义。

我们可以发现，每一项的 $\tbinom{b_i}{a_i}$ 转化为 $\tbinom{a_i+d_i}{a_i}$，也就是向 $a_i$ 个球中插入 $d_i$ 个球的方案数。

因此我们构造一个序列：

挡板，$a_1$ 个黑球，挡板，$a_2$ 个黑球，挡板.....，$a_n$ 个黑球

我们可以发现，现在在这个序列中插入 $m-\sum a_i$ 个球的方案数，等价于原问题所求！

因为最终在第 $i$ 个挡板后的球总数恰好对应一个原先合法的序列 $b_i$，权值正好等于放到这种状态的方案数 $\prod_{i=1}^n \tbinom{b_i}{a_i}$。

所以答案即为$\tbinom{m+n}{\sum a+n}$，暴力求即可，复杂度为 $O({\sum a+n})$。

 _[代码](https://www.luogu.com.cn/paste/rk0y8y3b)_ 


---

## 作者：小明小红 (赞：2)

# AT_arc110_d题解

赛时贺了一篇题解被要求讲题公开处刑，特此写篇题解加深理解。

首先，考虑将多个式子**简化**成**一个式子**，要求 $\binom{b_i}{a_i}$,由于 $b_i \ge a_i$,我们可以将他化为 $\binom{a_i+c}{a_i}$，其中 $c$ 为任意**非负整数**。

根据这个**高贵的性质**，我们可以将原题目变为以下问题。
![](https://cdn.luogu.com.cn/upload/image_hosting/009py12e.png)
就这样，放石子就变成了如下图示。
![](https://cdn.luogu.com.cn/upload/image_hosting/p0yjovzx.png)
最终，我们的问题就变成了在如上的所有共 $m+n$ 个元素中选出 $m-\sum a$ 个蓝石子，即 $\binom{m+n}{m-\sum a}$，由于 $m$ 过大**不能循环**，我们可以**变为** $\binom{m+n}{n+\sum a}$，直接求就可以了。

附上[代码](https://atcoder.jp/contests/arc110/submissions/57016334)。

---

## 作者：TLEWA (赞：1)

考虑从组合数意义的角度思考这个问题。

题目要求我们求 $\prod_{i = 1}^N {B_i \choose A_i}$，$B_i$ 的数值分配似乎很难处理，我们考虑使用**隔板法**，将所有 $A_i$ 串联起来，用隔板分隔。原问题转化为：在 $\sum A_i$ 个球和 $n-1$ 个隔板中插入至多 $m-\sum A_i$ 个球，计算总方案数。

“至多”的限制貌似还是不太好处理，考虑在最右侧增加一个隔板，删除在这个隔板右边插入的球，相当于满足了条件。答案即为 $m+n \choose {\sum A_i +n}$，计算即可。

## AC 代码


```cpp
#include<bits/stdc++.h>
#define int long long

using namespace std;

const int N=2005,mod=1000000007;

int n,m;
int arr[N],cnt;

int qmod(int n,int k) {
	if(k==0) return bool(n);
	if(k==1) return n;
	if(k&1) return n*qmod(n*n%mod,k/2)%mod;
	else return qmod(n*n%mod,k/2);
}

signed main() {
	cin >> n >> m;
	for(int i=1;i<=n;++i) {cin >> arr[i];cnt+=arr[i];}
	
	int ans=1;
	for(int i=m+n-cnt-n+1;i<=m+n;++i) ans=(ans*i)%mod;
	
	for(int i=1;i<=cnt+n;++i) ans=(ans*qmod(i,mod-2))%mod;
	
	cout << ans;
	return 0;
}

```

---

## 作者：chenwenmo (赞：1)

### 思路
如果$B_{i}<A_{i}$，那么$(_{A_{i}}^{B_{i}})=0$，不会产生贡献，所以只讨论$B_{i}\ge A_{i}$的情况。

$(_{A_{i}}^{B_{i}})$的组合意义是在$B_{i}$个数中选$A_{i}$个，那么$\prod_{i=1}^{N} (_{A_{i}}^{B_{i}})$就是每个$B_{i}$都选$A_{i}$个数的方案数，并且$\sum B_{i} \le M$。  

其中$B_{i}$一直在变化，不容易理解，不妨转换一下，在每个$A_{i}$中间加入一个隔板，然后在最后面再加一个板：  
$A_{i}\ 板\ A_{i + 1}\ 板\ A_{i + 2}\ ...\ 板$  
问题就转换成了：在$(\sum A_{i} + N + 1)$个空中插入$(M-\sum A_{i})$个元素，也就是将$(M-\sum A_{i})$个元素分成$(\sum A_{i} + N + 1)$组，组内可空，于是这就是普通插板法公式了：  
$C^{(\sum A_{i} + N)}_{M-\sum A_{i}+(\sum A_{i} + N)}=C^{\sum A_{i} + N}_{M+N}$
### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e3 + 10, inf = 2e9;
const ll mod = 1e9 + 7;

ll n, m, a[N], suma;

ll read(){
	ll x = 0, f = 1;
	char ch = getchar();
	while(ch < '0' || ch > '9') {if(ch == '-') f = -f; ch = getchar();}
	while(ch >= '0' && ch <= '9') {x = (x << 3) + (x << 1) + (ch ^ 48); ch = getchar();}
	return x * f;
}

ll fPow(ll a, ll b){
	ll ans = 1;
	for(; b; b >>= 1){
		if(b & 1) ans = ans * a % mod;
		a = a * a % mod; 
	}
	return ans;
}

ll C(ll n, ll m){
	if(n < m) return 0;
	ll f1, f2, up = 1, down = 1;
	if(m > n - m){
		f1 = m + 1;
		f2 = 1;
	}else{
		f1 = n - m + 1;
		f2 = 1; 
	}
	for(; f1 <= n; f1++, f2++){
		up = up * f1 % mod;
		down = down * fPow(f2, mod - 2) % mod;
	}
	return up * down % mod;
}

int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	n = read(), m = read();
	for(int i = 1; i <= n; i++) a[i] = read(), suma += a[i];
	cout << C(m + n, suma + n);
//	fclose(stdin);
//	fclose(stdout);
	return 0;
}

```

---

## 作者：Starrykiller (赞：1)

提供一种不太一样的组合意义？

约定：本题中，采用常用的笛卡尔坐标系。

去掉显然会没有贡献的 $B$ 序列，我们可以把问题转化为：

> 给定 $n,m'$ 和长度为 $n$ 的序列 $A$，对于所有长度为 $n$ 且和不超过 $m'$ 的非负整数序列 $B$，求 $\displaystyle \prod_{i=1}^n {A_i+B_i\choose A_i}$ 之和。

这里，$m'=m-\sum a_i$。

考虑组合意义。不难发现对于一个单独的组合数，就是从 $(0,0)$ 走到 $(B_i,A_i)$ 的（只能往右上方走的）方案数。然后你会发现可以把后一个移动的起点平移到前一个移动的终点。

然后你会发现对于任意 $\sum B_i$ 相同的序列，最后走到的位置都是相同的。所有 $\sum B_i$ 相等的序列的贡献就是 $(0,0)$ 走到 $\left(\sum B_i,\sum{A_i}+n-1\right)$ 的方案数。注意，这里加上了 $(n-1)$。


举个例子。例如 ${1+2\choose 1}$ 就是从 $(0,0)$ 走到 $(1,2)$ 的方案数，共 $3$ 个（证明：从 $(x+y)$ 步中选出 $x$ 步往右走）。


![](https://cdn.luogu.com.cn/upload/image_hosting/v577gebl.png)

那么，序列 $A=\{2,1\}$，$B=\{1,1\}$ 就是从 $(0,0)$ 经过 $(1,2),(1,3)$ 到达 $(2,4)$ 的方案数。（如下图左 1）

![](https://cdn.luogu.com.cn/upload/image_hosting/zl9jfc3v.png)

如果把所有和为 $2$ 的合法的 $B$ 序列列出来，把对应的图画出来，你会发现所有方案恰好不重不漏地覆盖了所有从 $(0,0)$ 到 $(\sum B_i,\sum A_i+n-1)$ 的方案。

枚举 $\sum B_i$，答案就是 $\displaystyle \sum_{i=0}^{m-\sum a_i} {\sum A_i+n-1+i\choose \sum {A_i+n-1}}$，化简得到 $\displaystyle {n+m\choose \sum {A_i}+n}$，直接 $\Theta(nV)$ 做即可。

---

## 作者：New_hope (赞：0)

## [[D] Binomial Coefficient is Fun](https://www.luogu.com.cn/problem/AT_arc110_d)

计数题又不会。

马上学习初等生成函数大杀器！！！

一样的，${B_i\choose A_i} \rightarrow {A_i + x_i\choose A_i}$，那么有 $x_i \ge 0$，且 $(\sum_{i}^n x_i) \le m - (\sum_{i}^n a_i)$。记 $m' = m - (\sum_{i}^n a_i)$。

考虑枚举上界，将不等关系转化为等号关系。

同时设计生成函数，设 $f_i(x) = \sum_{p \ge 0} {a_i + p\choose p} x^p$ （这步是为了构造出一个关于 $x_i$ 的指数，从而限制住和），根据生成函数乘积的意义，那么有答案式如下：

$$
ans = \sum_{i=0}^{m'} [x^i]\prod_{j=1}^n f_j(x)
$$

根据 $f_i(x)$ 的封闭形式，有 $f_i(x) = \frac{1}{(1 - x)^{a_i + 1}}$。

又根据幂数相乘，指数相加的定理，有：

$$
ans = \sum_{i=0}^{m'} [x^i] \frac{1}{(1 - x)^{\sum a + n}}
$$

再把封闭形式弄回展开形式，再用一步组合恒等式，有：

$$
ans = \sum_{i=0}^{m'} {{\sum a + n + i - 1}\choose {\sum a + n - 1}} = {{m' + \sum a + n}\choose {\sum a + n}} = {{m + n}\choose{\sum a + n}}
$$

终于推完了。

---

## 作者：封禁用户 (赞：0)

# 正文
## 审题 + 思路1
仔细读题，我们会发现这道题是一个不折不扣的数学题。

题意也比较好理解，在此就不浪费大家的时间讲解题目含义了。

这道题所运用的方法叫做**隔板法**，~~是一种小学奥数的技巧~~。

思考：该如何隔板？

经过一分钟的思考，我们可以发现题目所求的值并不是求乘积，而是求和。根据隔板法，我们知道白球的数量就是 $m-\sum a_i$ 的数量。

题目所求的数量就是组合数 $\binom{m+n}{s+n}$ 的数量。

在这里我借鉴了一下楼下的思路，时间复杂度是 $O(\sum a_i+n)$。

至此，您做出了这道题目。

## 思路2
分析题目中所给的表达式，当 $B$ 确定时，表达式的含义为：从 $B_1$ 中选 $A_1$ 个数，同时从 $B_2$ 中选 $A_2$ 个数，同时从 $B_3$ 个数中选 $A_3$ 个数，…，同时从 $B_n$个数中选 $A_n$ 个数，总共有多少种方法。得到一个子问题。

子问题解决：记 $sum_A$ 和 $sum_B$ 分别为此时$A$ 和 $B$ 的元素和。可以先从 $sum_B$ 个元素中选出 $sum_A$ 个元素，但这并没有达到分组的效果。假设这些数都是小球，现在加上木棒以分组。从 $sum_B + n$ 个元素中选出 $sum_A + n$ 个元素，设第 $1$ 个到第 $A_1$ 个元素为小球，第 $A_1 + 1$ 个元素为木棒；第 $A_1 + 1 + 1$ 个到第 $A_1 + 1 + A_2$ 个元素为小球，第 $A_1 + 1 + A_2 + 1$ 个元素为木棒，以此类推。加上木棒的目的是在选取小球的过程中进行分组，默认每一组后的第一个元素为木棒。

其实对上面的子问题选取 $n-1$ 个木棒即可，但选取最后一个木棒的目的是为了第二个子问题：构造所有的 $B$ 数列。前 $n-1$ 个木棒是将每一组进行区分，那么第 $n$ 个木棒的目的就是为了将 $B$ 中的所有数与 $B$ 之外的数进行区分，也就是 $m-sum_B$。

综上可以这样理解：最后一根木棒决定了 $sum_B$ 的大小，前 $n-1$ 个木棒则是对 $B$ 进行分组，而至于 $A$ 的选取已经在分组时完成了。

## 代码(思路2)
```cpp
#include <bits/stdc++.h>
#define fir first
#define sec second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
typedef pair<P,int> Q;
const int inf1=1e9+9;
const ll inf2=1e16+9;
const ll mod=1e9+7;
const int maxn=2e5+9;
const ll maxx=1e12+9;
const int DEG=20;
ll n,m,ar[maxn];
ll q_pow(ll x,ll t) {
    ll res=1;
    while(t) {
        if(t&1) res=res*x%mod;
        x=x*x%mod; t>>=1;
    }
    return res;
}
ll inv(ll a) {
    return q_pow(a,mod-2);
}
ll c(ll n,ll r) {
    if(r>n) return 0;
    if(n-r<r) r=n-r;
    ll a=1,b=1;
    for(int i=1;i<=r;i++) {
        a=a*(n-i+1)%mod;
        b=b*i%mod;
    }
    return a*inv(b)%mod;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=0;i<n;i++) scanf("%d",&ar[i]);
    ll sum=0;
    for(int i=0;i<n;i++) sum+=ar[i];
    printf("%lld\n",c(n+m,sum+n));
}
```
以上是这道题的代码，仅供参考。

---

