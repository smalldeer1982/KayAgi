# Max History

## 题目描述

You are given an array $ a $ of length $ n $ . We define $ f_{a} $ the following way:

- Initially $ f_{a}=0 $ , $ M=1 $ ;
- for every $ 2<=i<=n $ if $ a_{M}<a_{i} $ then we set $ f_{a}=f_{a}+a_{M} $ and then set $ M=i $ .

Calculate the sum of $ f_{a} $ over all $ n! $ permutations of the array $ a $ modulo $ 10^{9}+7 $ .

Note: two elements are considered different if their indices differ, so for every array $ a $ there are exactly $ n! $ permutations.

## 说明/提示

For the second example all the permutations are:

- $ p=[1,2,3] $ : $ f_{a} $ is equal to $ 1 $ ;
- $ p=[1,3,2] $ : $ f_{a} $ is equal to $ 1 $ ;
- $ p=[2,1,3] $ : $ f_{a} $ is equal to $ 1 $ ;
- $ p=[2,3,1] $ : $ f_{a} $ is equal to $ 1 $ ;
- $ p=[3,1,2] $ : $ f_{a} $ is equal to $ 0 $ ;
- $ p=[3,2,1] $ : $ f_{a} $ is equal to $ 0 $ .

Where $ p $ is the array of the indices of initial array $ a $ . The sum of $ f_{a} $ is equal to $ 4 $ .

## 样例 #1

### 输入

```
2
1 3
```

### 输出

```
1```

## 样例 #2

### 输入

```
3
1 1 2
```

### 输出

```
4```

# 题解

## 作者：Skadi_H (赞：4)

[可移步至洛谷博客获得不知道会不会更好的阅读体验](https://www.luogu.com.cn/blog/Skadi-H1314/cf938e-max-history-ti-xie)
# upd
2023.11.16：有一个式子写错了，现已更正，烦请审核老师再次审核，感谢！

2023.11.22：已针对题解反馈的问题进行改正，并特地对**科学计数法**进行仔细检查，感谢审核老师的再次审核！
# 背景
前几天某场模拟赛遇到的一道题，刚好好久没看组合了，复习一下。
# 题意
初始时，$f(a)=0$，$m=0$。

对于一个 $n$ 的排列 $p$ 。

对于 $i\le 2\le n$ （$i$从小到大枚举），如果 $a_{p_i}>a_m$ ，则: $f(a)\gets f(a)+a_m,m=p_i$ 。

对 $n!$ 种可能的排列的 $\sum f(a)$（对$10^9+7$取模）。

$ 1\le n \le 10^6$。
# solution
应该算是非常详细的。

首先，由于总共 $n!$ 种排列的 $f(a)$ 难以分每次逐个统计，于是想到**对每一个以 $a_i$ 为终值的排列对答案的贡献分开计算**并且求和。

而注意到，当 $a_m<a_i$ 时，$m=i$，由此可以得知：

如果将历史上出现的每一个 $a_m$ 的值组成一个序列，则这个序列是**单调递增**的。

故 **$a_m$ 由 $0$ 变为终值的过程中，只与那些比 $a_m$ 小的数有关**。

考虑先进行**排序**（时限3s），通过一次扫描**对每个 $a_i$ 得到比其值小的数字个数 $pre_i$**。

下面就到式子了：（步骤非常详细）

假设对于 $a_i$ ,共有 $x$ 个数比其小。

因为只有**在 $a_i$ 前的比起小的数会对结果有影响**，故考虑**枚举 $a_i$ 前比其小的数字个数**。

假设当前 $a_i$ 前面有 $i$ 个比它小的数，共 $\binom{x}{i}$ 种方案。

这 $i$ 个数随便排列，共 $i!$ 种方案。

剩下除这 $i$ 个数与当前枚举的 $a_i$ 以外的数共 $n-i-1$ 个随意排列方案数：$(n-i-1)!$ 。

所以数 $a_i$ 对答案的贡献**次数**为：

$$\sum_{i=0}^{x} \binom{x}{i} ·i!·(n-i-1)!$$

下面的过程是**简化**这个式子：

拆组合数：

$$=\sum_{i=0}^{x} \frac{x!}{i!·(x-i)!}·i!·(n-i-1)!$$

抵消：

$$=\sum_{i=0}^{x} \frac{x!}{(x-i)!}·(n-i-1)!$$

将 $x!$ 提到前面：

$$=x!·\sum_{i=0}^{x} \frac{(n-i-1)!}{(x-i)!}$$

由组合数：$\binom{n}{m}= \frac{n!}{m!(n-m)!}$ 添项：

$$=x!·\sum_{i=0}^{x} \frac{(n-i-1)!}{(x-i)!(n-x-1)!}·(n-x-1)!$$

将 $(n-x-1)!$ 提到前面：

$$=x!·(n-x-1)!·\sum_{i=0}^{x} \frac{(n-i-1)!}{(x-i)!(n-x-1)!}$$

合成组合数：

$$=x!·(n-x-1)!·\sum_{i=0}^{x} \binom{n-1-i}{x-i}$$

由于 $i$ 与 $x-i$ 值域均为 $0 \sim x$，且$(i)+(x-i)=x$（这不是废话吗）。

所以 $i$ 与 $x-i$ 可相互替换（相当于求和的循环倒着枚举）：

（这里可能不用这么麻烦，但是太久没推式子了。）

$$=x!·(n-x-1)!·\sum_{i=0}^{x} \binom{n-1-x+i}{i}$$

$$=x!·(n-x-1)!·\sum_{i=0}^{x} \binom{n-x+i-1}{i}$$

又因为：$\sum_{i=0}^{k}\binom{n+i-1}{i}=\binom{n+k}{k}$

$$=x!·(n-x-1)!·\binom{n}{x}$$

拆组合数：

$$=x!·(n-x-1)!·\frac{n!}{x!(n-x)!}$$

抵消：

$$=n!·\frac{(n-x-1)!}{(n-x)!}$$

$$=\frac{n!}{n-x}$$

而**因为最终值 $a_m$ 不会被计算**在答案当中，显然排序后所有**值为 $a_n$ 的数不应该被统计**在答案当中。

则答案就为：

$$\sum_{i=1}^{n}\frac{n!}{n-pre_i}·a_i·[a_i \neq a_n]$$

# 代码
下方提供代码参考：
```cpp
#include <bits\stdc++.h>
using namespace std;
const int mod=1000000007;
long long n,facn=1,ans;
long long a[1000005],p[1000005],pre[1000005];
long long ksm(long long a,long long b)
{
	long long res=1;
	while(b)
	{
		if(b&1)
			res=res*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return res;
}
long long inv(long long x)
{
	if(x==0)
		return 0;
	return ksm(x,mod-2);
}
int mian(){
	std::ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		facn=facn*i%mod;
	}
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++)
	{
		if(a[i]==a[i-1])
		{
			p[i]=p[i-1];
			pre[i]=pre[i-1];
		}	
		else
		{
			p[i]=i-1;
			pre[i]=a[i-1];
		}
	}
	for(int i=1;i<=n;i++)
	{
		if(a[i]==a[n])
			break;
		ans=(ans+facn*(inv(n-p[i]))%mod*a[i])%mod;
	}
	cout<<ans;
	return 0;
}
//Skadi_H
//CF938E
```
# 后记
审核老师辛苦了！

---

## 作者：wosile (赞：3)

这题题解有必要这么长吗....？

首先，就像其他题解提到的一样，我们考虑每个数 $x=a_i$ 会在最终的答案中被统计多少次。对于一个 $a$ 的排列 $b$，$b_i$ 会被统计到答案里当且仅当 $b_i$ 不是最大值并且 $\forall 1\le j< i,b_j<b_i$。

也就是说，我们对于每一个非最大值的 $x$，要数满足 $x$ 比前面所有数都大的排列个数。

于是其他题解就开始枚举 $x$ 出现的位置然后直接推组合式子，其实没有这个必要。

注意到，“$x$ 前面所有数都 $<x$”等价于“所有 $\ge x$ 的数都在 $x$ 后面”，也就是“$x$ 在所有 $\ge x$ 的数中**排在第一个**”。

记 $g(x)=\sum\limits_{i=1}^n[a_i\ge x]$，即 $\ge x$ 的数的个数。显然（如果这个不显然，考虑忽略掉所有 $<x$ 的数）如果随机选一个排列，$x$ 排在所有 $\ge x$ 的数中的第一个的概率就是 $\frac{1}{g(x)}$。那么，一共就有 $\frac{n!}{g(x)}$ 个排列符合条件。

计算每一个 $x$ 的出现次数，乘上值，加起来就行。   

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
const int mod=1000000007;
int a[1000005];
int ft[1000005],ift[1000005];
typedef long long ll;
ll qp(ll x,int y){
	ll ans=1;
	while(y){
		if(y&1)ans=ans*x%mod;
		x=x*x%mod;
		y>>=1; 
	}
	return ans;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	sort(a+1,a+n+1);
	ft[0]=1;
	for(int i=1;i<=n;i++)ft[i]=1LL*ft[i-1]*i%mod;
	ift[n]=qp(ft[n],mod-2);
	for(int i=n;i>=1;i--)ift[i-1]=1LL*ift[i]*i%mod; 
	int cnt=0,ans=0;
	for(int i=1;i<=n;i++){
		++cnt;
		if(a[i]<a[i+1] && i<n){
			ans=(ans+1LL*ft[n]*ft[n-i+cnt-1]%mod*ift[n-i+cnt]%mod*a[i]%mod*cnt)%mod;
			cnt=0;
		}
	}
	printf("%d",ans);
	return 0;
	//quod erat demonstrandum
}
```

---

## 作者：AxDea (赞：3)

### 如果公式崩了，请在博客查看！！！

由于每一个数组元素的大小不同，只能分开计数。

对于每个 $a_i$，若有 $k$ 个严格比它小的数，这个数字被记录的次数就是：

$$
\begin{aligned}
 &\sum_i {k \choose i} i! (n - i - 1)!\\
=&\sum_i \dfrac{k! i! (n - i - 1)!}{i! (k - i)!}\\
=&(n - 1) !\times\sum_i \dfrac{\dfrac{k!}{(k - i)! i!}}{\dfrac{(n - 1)!}{(n - i - 1)! i!}}\\
=&(n - 1) ! \times \sum_i \dfrac{{k\choose i}}{{n - 1\choose i}}
\end{aligned}
$$

右边这个组合数的商十分难搞，但是两个组合数的下指标是相同的，考虑一个恒等式：

$$
{r\choose m} {m\choose k} = {r - k\choose m - k} {r \choose k}
$$

转换一下：

$$
\dfrac{m\choose k}{r\choose k} = \dfrac{r - k\choose m - k}{r\choose m}
$$

把这个结论带入原式右边的部分：

$$
\begin{aligned}
 &\sum_{i \le k - 1} \dfrac{{k\choose i}}{{n - 1\choose i}}\\
=&\sum_{i \le k - 1} \dfrac{{n - i - 1\choose k - i}}{{n - 1\choose k}}
\end{aligned}
$$

发现分式下面这个东西已经与 $i$ 无关了，直接提出和式：

$$
\begin{aligned}
 &\sum_{i \le k} {n - i - 1\choose k - i} \\
=&\sum_{i \le k} {n - k + i - 1\choose i} \\
=&{n\choose k}
\end{aligned}
$$

最后一步是由另一个恒等式：

$$
\sum_{k\le n} {r + k \choose k} = {r + n + 1\choose n}
$$

得出来的。

把最后组合出的式子写出来：

$$
\begin{aligned}
 &(n - 1) ! \times \dfrac{{n\choose k}}{{n - 1\choose k}}\\
=&\dfrac{n!}{n - k}
\end{aligned}
$$

最后一步只是拆了一个阶乘。

代码也比较简短了。


---

## 作者：Chthologist7507 (赞：2)

对于每一个 $a_i$，若有 $k$ 个比他小的数，那么他记录的次数即：

$$\begin{aligned}
&\sum_{i=0}^{k-1}\binom{i}{k-1}\times i!\times(n-i-1)!\\
=&\sum_{i=0}^{k-1}\dfrac{(k-1)!}{(k-i-1)!}\times(n-i-1)!\\
=&(k-1)!\sum_{i=0}^{k-1}\dfrac{n-1-i}{k-1-i}(n-k)!\\
=&(k-1)!(n-k)!\binom{n}{k-1}\\
=&\dfrac{n!}{n-k}
\end{aligned}$$

求和，做完了

[code](https://codeforces.com/contest/938/submission/166679157)

---

## 作者：daniEl_lElE (赞：2)

## 思路

考虑对于每个 $a_i$ 计算贡献。当且仅当 $a_i$ 以前的所有 $a_j$ 均严格小于 $a_i$ 才能使 $a_i$ 计算到总和中（$a_i$ 若最大则不可能被计算到总和中）。考虑 $a_j<a_i$ 的 $j$ 有 $k$ 个，容易写出对于 $i$：

$$
\begin{aligned}
\sum_{i=0}^k C_{k}^ii!(n-i-1)! \\
=\sum_{i=0}^k\frac{k!i!(n-i-1)!}{i!(k-i)!} \\
=\sum_{i=0}^k\frac{k!(n-i-1)!}{(k-i)!} \\
=k!\sum_{i=0}^k\frac{(n-i-1)!}{(k-i)!} \\
=k!(n-k-1)!\sum_{i=0}^k\frac{(n-i-1)!}{(k-i)!(n-k-1)!} \\
=k!(n-k-1)!\sum_{i=0}^kC_{n-i-1}^{k-i}\\
k!(n-k-1)!C_{n}^k \\
k!(n-k-1)!\frac{n!}{k!(n-k)!} \\
\frac{n!(n-k-1)!}{(n-k)!} \\
\frac{n!}{n-k} \\
\end{aligned}
$$

然后求和即可。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
int qp(int a,int b){
	int ans=1;
	while(b){
		if(b&1) ans=(ans*a)%mod;
		a=(a*a)%mod;
		b>>=1;
	}
	return ans;
}
signed main(){
	int n;
	cin>>n;
	int a[n+1];
	for(int i=1;i<=n;i++) cin>>a[i];
	sort(a+1,a+n+1);
	int fac[n+1];
	fac[0]=1;
	for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod;
	int ans=0;
	for(int i=1;i<n&&a[i]!=a[n];){
		int k=i-1,now=a[i];
		while(a[i]==now&&i<n&&a[i]!=a[n]){
			ans=(ans+(fac[n]*qp(n-k,mod-2)%mod)*a[i]%mod)%mod;
			i++;
		}
	} 
	cout<<ans;
	return 0;
}
```

---

## 作者：strcmp (赞：1)

因为是枚举全排列，我们显然可以先对 $a$ 序列排序。

注意到一个数能够被计入贡献，当且仅当这个数前面的所有数都比它小，且它自身不是最大数。

证明可以考虑钦定最后一个比 $a_i$ 大的数 $x$，递归下去，要么访问到 $x$，此时必然不会访问到 $i$，要么 $x$ 没被访问到，必然是前面访问到了一个比 $x$ 更大的数，进而 $i$ 也不可能被访问到。后一种情况可以特判。

因此考虑每个 $a_i$ 在什么时候产生贡献，显然在 $i$ 前面所有数都比 $a_i$ 小的时候产生贡献。

于是不妨钦定 $a_i$ 在 $x$ 位置且必然产生贡献，此时选择 $x - 1$ 个数，在所有比 $a_i$ 小的数（假设有 $d$ 个，通过排序可以 $\Theta(1)$ 得知）中取。总共是 $\binom{d}{x - 1}$ 种方案，可以任意排列，是 $(x - 1)!$ 种方案，$x$ 之后的位置可以任意排列，总共是 $(n - x)!$ 种方案。

于是我们就是要搞这个式子：

$$
\sum_{i=1}^{d + 1} \binom{d}{i - 1} \times (i - 1)! \times (n - i + 1)!
$$

不妨令 $i \leftarrow i - 1$。

$$
\sum_{i=0}^{d} \binom{d}{i} \times i! \times (n - i - 1)!
$$

显然拆组合数式子。

$$
\begin{aligned}
& \sum_{i=0}^{d} \frac{d!}{(d - i)!i!} i! \times (n - i - 1)! \\
& = d!\left(\sum_{i=0}^{d} \frac{(n - i - 1)!}{(d - i)!}\right)\\
& = d!(n - d - 1)!\left(\sum_{i=0}^{d} \frac{(n - i - 1)!}{(d - i)!(n - d - 1)!}\right)\\
& = d!(n - d - 1)!\left(\sum_{i=0}^{d} \binom{n - i - 1}{d - i}\right)\\
& = d!(n - d - 1)!\binom{n}{d}\\
& = \frac{n!}{n - d}\\
\end{aligned} 
$$

对所有的 $a_i$ 求这个式子的和即可。

时间复杂度 $\Theta(n \log n)$，瓶颈在求逆元和二分排序，但是前者可以线性求逆元，后者可以基数排序和双指针来做到线性。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
const int maxn = 1e6 + 10;
constexpr ll inf = 11451491981052013LL;
constexpr int mod = 1e9 + 7;
inline ll ksm(ll a, ll b) {
	ll ls = 1;
	while (b) {
		if (b & 1) ls = ls * a % mod;
		a = a * a % mod; b >>= 1;
	}
	return ls;
}
int n; ll a[maxn], fac[maxn], mx = 0;
int main() {
	scanf("%d", &n); fac[0] = 1;
	for (int i = 1; i <= n; i++) scanf("%lld", &a[i]), fac[i] = fac[i - 1] * i % mod;
	sort(a + 1, a + n + 1); ll ans = 0;
	for (int i = 1, l = 0; i <= n; i++) {
		if (a[i] == a[n]) break;
		while (a[l + 1] < a[i]) ++l;
		ans = (ans + fac[n] * ksm(n - l, mod - 2) % mod * a[i] % mod) % mod;
	}
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：Purslane (赞：1)

# Solution

好久没推组合式子了，感觉已经变成了弱智。

显然一个数能被算入贡献当且仅当它前面所有数都严格比他小（当然如果这个数是最大值不能被算入贡献）。

假设一共有 $m$ 个数比他小，方案为

$$\begin{aligned}
\sum_{i=0}^m A_m^i(n-i-1)! &= \sum_{i=0}^m \frac{m!(n-i-1)!}{(m-i)!}\\
&=m!\sum_{i=0}^m \frac{(n-i-1)!}{(m-i)!(n-m-1)!}(n-m-1)! \\
&=m!(n-m-1)! \sum_{i=0}^m C_{n-i-1}^{n-m-1} \\
&=m!(n-m-1)!C_{n}^{n-m} \\
&=\frac{m!(n-m-1)!n!}{(n-m)!m!} \\
&=\frac{n!}{n-m}
\end{aligned}
$$

求出比每个数小的数的个数。但是最大数要删掉。

代码：[code](https://codeforces.com/contest/893/submission/211907397)。

---

## 作者：wwlw (赞：1)

[Link](https://www.luogu.com.cn/problem/CF938E)
--------------

### Solution

考虑每个元素的贡献。该元素对答案有贡献当且仅当前面没有比该元素大的数，且后面存在比该元素大的数。容易想到先将序列排序。

假设所有元素都不同，当前是第 $i$ 个，枚举该元素前面的数的个数，然后计数

$$\sum_{k=0}^{i-1} k!(n-k-1)!\binom{i-1}{k}$$

然后就会发现 $k!(n-k-1)!$ 是个常数列，记为 $f_k$。然后就会发现上面的式子是 $f$ 和 $1$ 的 egf 的二项卷积。NTT 一下就做完了。（但是模数是 $10^9+7$，这种方法并不可取）

还是太年轻了。

由于 $f_k$ 这个东西很特殊，所以应该先考虑化简。注意到有

$$k!(n-k-1)!=\frac{k!(n-k-1)!(n-1)!}{(n-1)!}=(n-1)!\binom{n-1}{k}^{-1}$$

所以就化成

$$(n-1)! \sum_{i=0}^{i-1} \binom{i-1}{k}\Big/\binom{n-1}{k}$$

然后你就会发现这个和《具体数学》5.2 第一个例题长得差不多，大概就是考虑运用三项恒等式后再上指标求和。

最后便是

$$(i-1)!(n-i)!\binom{n}{i-1}$$

然后再看有重复元素的。容易发现必须是第一个该值的元素才会造成贡献，所以只需要把所有同值元素按照第一个遇到的该种元素处理即可。

```cpp
#include<stdio.h>
#include<algorithm>
using namespace std;

inline int read(){
    int x=0,flag=1; char c=getchar();
    while(c<'0'||c>'9'){if(c=='-') flag=0;c=getchar();}
    while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+c-48;c=getchar();}
    return flag? x:-x;
}

typedef long long ll;

const int N=1e6+7;
const int Mod=1e9+7;

int qpow(ll x,int y=Mod-2){
    ll ret=1;
    while(y){
        if(y&1) ret=ret*x%Mod;
        x=x*x%Mod,y>>=1; 
    }
    return ret;
} 

ll fac[N],a[N],inv[N];

ll C(int x,int y){return x<y? 0:fac[x]*inv[y]%Mod*inv[x-y]%Mod;}

int main(){
    int n=read(); fac[0]=1;
    for(int i=1;i<=n;i++)
        a[i]=read(),fac[i]=fac[i-1]*i%Mod;
    inv[n]=qpow(fac[n]);
    for(int i=n-1;~i;i--)
        inv[i]=inv[i+1]*(i+1)%Mod;
    sort(a+1,a+1+n); int mx=a[n];
    ll ans=0,q=0;
    for(int i=1;i<=n;i++){
        if(a[i]==mx) break;
        if(a[i]!=a[i-1]) q=fac[i-1]*fac[n-i]%Mod*C(n,i-1)%Mod;
        ans=(ans+a[i]*q%Mod)%Mod;
    }
    printf("%lld",ans);
}
```

---

## 作者：caidzh (赞：1)

$f$函数事实上是在维护一个能取就取的上升子序列

考虑计算$a_i$对答案的贡献

注意到$a_i$被选入上升子序列并且对答案有贡献，需要满足：前面没有$\ge a_i$的数，后面存在一个数比$a_i$大

事实上对于不是原序列中最大数的$a_i$，只需要满足上面的第一个条件即可

设$\ge a_i$的数有$y$个，$a_i$的贡献次数可以表示为：

$$\sum_{i=1}^{n-y}\dbinom{n-i}{y}y!(n-y-1)!$$

然后做一点简单的变换可以去掉求和，得到一个可以直接计算的式子：

$$y!(n-y-1)!\dbinom{n}{y+1}$$
```cpp
const int maxn=1000010,mod=1e9+7;
int n,a[maxn],tmp[maxn],cnt,fac[maxn],facinv[maxn],inv[maxn],suf[maxn];
int C(int n,int m){
	return 1ll*fac[n]*facinv[m]%mod*facinv[n-m]%mod;
}
int main(){
	n=read();
	for(int i=1;i<=n;i++)tmp[i]=a[i]=read();
	sort(tmp+1,tmp+n+1);cnt=unique(tmp+1,tmp+n+1)-tmp-1;
	for(int i=1;i<=n;i++)a[i]=lower_bound(tmp+1,tmp+cnt+1,a[i])-tmp;
	for(int i=1;i<=n;i++)suf[a[i]]++;
	for(int i=cnt-1;i>=1;i--)suf[i]+=suf[i+1];
	for(int i=1;i<=cnt;i++)suf[i]--;
	fac[1]=fac[0]=inv[1]=facinv[1]=facinv[0]=1;
	for(int i=2;i<=n;i++){
		fac[i]=1ll*fac[i-1]*i%mod;
		inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;
		facinv[i]=1ll*facinv[i-1]*inv[i]%mod;
	}int ans=0;
	for(int i=1;i<=n;i++){
		if(a[i]==cnt)continue;int y=suf[a[i]];
		ans=(ans+1ll*tmp[a[i]]*fac[y]%mod*fac[n-y-1]%mod*C(n,y+1)%mod)%mod;
	}cout<<ans;return 0;
}
```


---

## 作者：ifffer_2137 (赞：0)

### 题意
给一个长度为 $n$ 的序列 $a_i$，求其 $n!$ 种全排列的前缀 $\max$ 之和（除去全局最大值）的和，对 $10^9+7$ 取模。
### 分析
这种题一般算贡献。

看当前这个数 $x$，想让它成为前缀 $\max$，只需要它前面的数都小于 $x$，其它随便排。

于是我们从小往大扫，维护一个小于当前数的数的个数 $s$。然后枚一下当前这个数填的位置，产生贡献的方案数有：
$$\sum_{i=0}^{s}\dbinom{s}{i}i!(n-i-1)!$$
接下来是推柿子。
$$\begin{aligned}
&\sum_{i=0}^{s}\frac{s!}{i!(s-i)!}i!(n-i-1)!\\
=&s!\sum_{i=0}^{s}\frac{(n-i-1)!}{(s-i)!}\\
=&s!\sum_{i=0}^{s}\frac{(n-i-1)!}{(s-i)!(n-s-1)!}(n-s-1)!\\
=&s!(n-s-1)!\sum_{i=0}^{s}
\dbinom{n-i-1}{n-s-1}\\
=&s!(n-s-1)!\sum_{i=0}^{n-1}
\dbinom{i}{n-s-1}\\
=&s!(n-s-1)!\dbinom{n}{n-s}\\
\end{aligned}
$$
总的来说是构造了一个下标固定的二项式系数求和，最后一步用了朱世杰恒等式。

然后这里还可以继续推一下变成 $\dfrac{n!}{n-s}$，比较平凡就不多赘述了。好处是可以不用预处理组合数。

懒人笔者艹了个快速幂逆元，时间 $O(n\log V)$。
### 代码

```cpp
//From: ifffer_2137
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define inf 0x7fffffff
#define eb emplace_back
#define pii pair<int,int>
#define mkpr make_pair
#define fir first
#define sec second
inline int read(){
	char ch=getchar();int x=0,w=1;
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+ch-48,ch=getchar();return w==1?x:-x;
}
const int maxn=1e6+5;
const int mod=1e9+7;
int pw(int a,int x){
	int s=1;
	while(x){
		if(x&1) s=s*a%mod;
		a=a*a%mod;x>>=1;
	}
	return s;
}
int n,fac,mx,ans;
map<int,int> cnt;
signed main(){
	#ifndef ONLINE_JUDGE
	freopen("data.in","r",stdin);
	freopen("test.out","w",stdout);
	#endif
	cin.tie(0),cout.tie(0);
	n=read();fac=1;
	for(int i=1;i<=n;i++) fac=fac*i%mod;
	for(int i=1;i<=n;i++){
		int a=read();
		mx=max(mx,a);
		cnt[a]++;
	}
	int s=0;
	for(auto it:cnt){
		ans=(ans+it.fir*fac%mod*pw(n-s,mod-2)%mod*it.sec%mod)%mod;
		s+=it.sec;
	}
	ans=(ans-fac*mx%mod+mod)%mod;
	cout<<ans<<'\n';
	return 0;
}
```

---

## 作者：jpwang (赞：0)

这个f(a)实际上就是在维护单调栈，一个数字被算当且仅当前面的都不比它大。记mn表示小于a[i]的数量，那么答案就是$$\binom{n}{n-mn}\cdot mn!\cdot (n-mn-1)!$$
注意最大的数字我们无论如何都算不到，减去即可
# Code
---
```cpp
#include <stdio.h>
#include <string.h>
#include <algorithm>
#define rep(i,st,ed) for (int i=st;i<=ed;++i)
#define drp(i,st,ed) for (int i=st;i>=ed;--i)

typedef long long LL;
const int MOD=1000000007;
const int N=1000005;

LL a[N],fac[N],ny[N];

LL ksm(LL x,LL dep) {
	LL res=1;
	for (;dep;dep>>=1) {
		(dep&1)?(res=res*x%MOD):0;
		x=x*x%MOD;
	}
	return res;
}

LL C(int n,int m) {
	if (m==0||n==m) return 1;
	return fac[n]*ny[m]%MOD*ny[n-m]%MOD;
}

int main(void) {
	freopen("data.in","r",stdin);
	freopen("myp.out","w",stdout);
	fac[0]=1; rep(i,1,N-1) fac[i]=fac[i-1]*i%MOD;
	ny[N-1]=ksm(fac[N-1],MOD-2);
	drp(i,N-2,0) ny[i]=ny[i+1]*(i+1)%MOD;
	int n; scanf("%d",&n);
	rep(i,1,n) scanf("%lld",&a[i]);
	std:: sort(a+1,a+n+1);
	LL ans=0; fac[0]=1;
	for (int i=1,j;i<=n;) {
		j=i;
		while (a[j+1]==a[j]) j++;
		if (j==n) break;
		ans=(ans+fac[n-i]*(LL)(j-i+1)%MOD*a[i]%MOD*fac[i-1]%MOD*C(n,n-i+1)%MOD)%MOD;
		i=j+1;
	}
	printf("%lld\n", ans);
	return 0;
}
```

---

