# 高洁（Purity）

## 题目背景

简洁、准确而永恒的美丽 —— 高洁。
****
「高洁之光」拉姆，身为精灵王的他可以完美使用《阿梅斯草纸书》的力量。

## 题目描述

拉姆使用「暴风箭雨」一次射出了 $n$ 支箭，其中第 $i$ 支箭的原始攻击力是 $i$。不过，这些箭会经过一些强化。

对于常数 $d$，设原始攻击力为 $i$ 的箭，其**能级**为 $v(i)$：

- 若不存在正整数 $k$ 使得 $i^k$ 是 $d$ 的整数倍，则 $v(i)=0$；  
- 否则 $v(i)$ 为**最小的**、使得 $i^k$ 是 $d$ 的整数倍的正整数 $k$。

那么这支箭强化后的攻击力为 $i^{v(i)+1}$。

拉姆想知道所有箭在**强化后**的攻击力之和，由于答案可能很大，你只需要求出答案对 $998244353$ 取模的结果。（即求出答案除以 $998244353$ 的余数）

## 说明/提示

【样例解释】   
对于第一组数据，$d=12$。其中 $v(6)=2$，因为 $12$ 能整除 $6^2$，而不整除 $6^1$，同样也能得到 $v(12)=1$。
可以发现 $n=15$ 以内的其它数能级都为 $0$，故答案为：

$$\left(\sum_{i=1}^{15}i\right)-6-12+6^3+12^2=462$$

对于第二组数据，可以证明 $n$ 以内只有 $v(210)=3$ 非零，由此可以算出答案为 $1944889990$，对 $998244353$ 取模后为 $946645637$。

【数据范围】  
**本题采用捆绑测试。**

Subtask 1（15 pts）：$1 \le n,d \le 10^4$；  
Subtask 2（15 pts）：$d$ 为质数；  
Subtask 3（20 pts）：$d$ 为质数的正整数幂；  
Subtask 4（20 pts）：不存在大于 $1$ 的整数 $x$，使得 $x^4$ 整除 $d$；  
Subtask 5（30 pts）：无特殊限制。

对于全部数据，$1\le T \le 1000$，$1\le n < 2^{63}$，$1\le d \le 10^8$。

【提示】  
此题的时间限制较为宽松，即使你的代码在某些细节上没有优化，也可以正常通过此题。

## 样例 #1

### 输入

```
5
15 12
400 2520
5000000 68256
10000000 65536
10000000000 3628800```

### 输出

```
462
946645637
231125775
290821843
602104955```

# 题解

## 作者：NaCly_Fish (赞：31)

我们考虑有哪些数的能级**至多**为 $k$ —— 即满足 $d \mid i^k$。可以将 $d$ 进行质因数分解：

$$d=\prod_{j=1}^m p_j^{t_j}$$
然后考虑到 $d \mid i^k$ 等价于 $i^k$ 的所有质因子的幂次都不小于 $d$ 对应质因子的幂次。即 $i$ 含有质因子 $p_j$ 的数量至少为 $\lceil t_j/k \rceil$。现在可以设
$$f_k(d)=\prod_{j=1}^rp_j^{\lceil t_j/k\rceil}$$
这样就得到了结果：$d \mid i^k \Leftrightarrow f_k(d) \mid i$。然后就能得到能级为 $k \ (k > 1)$ 的所有数的答案之和：
$$\sum_{i=1}^ni^{k+1}[f_k(d) \mid i][f_{k-1}(d)\nmid i]$$
$$=f_k(d)^{k+1}\sum_{i=1}^{\lfloor n/f_k(d)\rfloor}i^{k+1}[\left(f_{k-1}(d)/f_k(d)\right) \nmid i]$$
而对于 $k=1$ 的情况，条件就只是 $d \mid i$，答案也很简单：
$$\sum_{i=1}^ni^2 [d \mid i]=d^2 \sum_{i=1}^{\lfloor n/d \rfloor}i^2$$

设 $q_k=f_{k-1}(d)/f_k(d)$，上面这个问题可以转化为（$m=\lfloor n/f_k(d) \rfloor$）：
$$\sum_{i=1}^mi^{k+1}(1-[q_k \mid i])=\sum_{i=1}^mi^{k+1}-q_k^{k+1}\sum_{i=1}^{\lfloor m/q_k \rfloor}i^{k+1}$$
整个问题就变成了简单的自然数 $k$ 次幂和：

$$S_k(n)=\sum_{i=1}^ni^k$$
这个东西有很多种算法，比如有：
$$S_k(n)=\sum_{i=0}^{n-1}(i+1)^k=\sum_{j=0}^k\binom kj (S_j(n)-n^j+0^j)$$
就可以简单地递推计算。

注意到 $k$ 不小于 $d$ 的质因子的最大幂次（即 $\max\{ t_1,\cdots,t_r \}$）时 $f_k(d)$ 全部都相同，这样就得到了能级的上限。可以发现 $k$ 很小（不超过 $27$），使用 $\Theta(k^2)$ 的递推法计算也可以通过。

最后还需要求出能级为 $0$ 的所有数之和，这样好办。它就是

$$\sum_{i=1}^n i [\text{ord}(d) \nmid i]$$
其中 $\text{ord}(d)$ 表示 $d$ 所有不同质因子的乘积，可以直接使用之前的操作方法处理。
****

---

## 作者：Naszt (赞：7)

[> Problem Link <](https://www.luogu.com.cn/problem/P10322)  

这篇题解看起来很长，其实只是把步骤写的较为详细罢了，希望能够耐心看完。  

## 题意

能级：
$$
v(i)=
\begin{cases}
0 & d\nmid i^k\\
\text{最小的} \ k \ {使得} & d\mid i^k
\end{cases}
$$

所有箭在强化后的攻击力之和：  
$$ans=\sum_{i=1}^n i^{v(i)+1}$$

## 思路分析

### step1 换求和顺序

设 $f(k)$ 为所有能级为 $k$ 的箭的攻击力之和：
$$f(k)=\sum_{i=1}^n i^{k+1}[k=v(i)]$$

质因数分解 $d=\prod_{i=1}^{r} p_i^{t_i}$，记 $t_{max}$ 为最大的 $t_i$，有：  
$$ans=\sum_{i=1}^n i^{v(i)+1}=\sum_{k=1}^{t_{max}} f(k)$$

### step2 化简 $f(k)$
设 $d_k=\prod_{i=1}^{r} p_i^{\left\lceil\frac{t_i}{k}\right\rceil}$。  
那么有（充要条件）：$d\mid i^k\Leftrightarrow d_k\mid i$。  
所以有（充要条件）：$(v(i)=k)\Leftrightarrow (d_{k-1}\nmid i)\wedge(d_{k}\mid i)$。 

化简 $f(k)$：  

$$
f(k)=\sum_{i=1}^n i^{k+1}[k=v(i)]=
\begin{cases}
\sum_{i=1}^n i[d_{t_{max}}\nmid i] & k=0\\
\sum_{i=1}^n i^2[d_1\mid i] & k=1\\
\sum_{i=1}^n i^{k+1}[d_{k-1}\nmid i][d_{k}\mid i] & k>1
\end{cases}
$$

分别消去逻辑判断：

- 当 $k=0$ 时： 

$$
\begin{aligned}
\sum_{i=1}^n i[d_{t_{max}}\nmid i]
=&\sum_{i=1}^n i[1-d_{t_{max}}\mid i]\\
=&\sum_{i=1}^n i-\sum_{i=1}^n i[d_{t_{max}}\mid i]\\
=&\sum_{i=1}^n i-d_{t_{max}}\sum_{i=1}^{\left\lfloor\frac{n}{d_{t_{max}}}\right\rfloor} i\\
\end{aligned}
$$

- 当 $k=1$ 时：  

$$
\begin{aligned}
\sum_{i=1}^n i^2[d_1\mid i]
=&\sum_{i=1}^{\left\lfloor\frac{n}{d_1}\right\rfloor} (id_1)^2\\
=&d_1^2\sum_{i=1}^{\left\lfloor\frac{n}{d_1}\right\rfloor} i^2
\end{aligned}
$$

- 当 $k>1$ 时：  

$$
\begin{aligned}
\sum_{i=1}^n i^{k+1}[d_{k-1}\nmid i][d_{k}\mid i]
=&\sum_{i=1}^{\left\lfloor\frac{n}{d_k}\right\rfloor} (id_k)^{k+1}[d_{k-1}\nmid id_k]  \hspace{1cm} \color{#999999}<\text{换}\ i\to id_k>\\
=&d_k^{k+1}\sum_{i=1}^{\left\lfloor\frac{n}{d_k}\right\rfloor} i^{k+1}[1-\frac{d_{k-1}}{d_k}\mid i]\\
=&d_k^{k+1}\left(\sum_{i=1}^{\left\lfloor\frac{n}{d_k}\right\rfloor} i^{k+1}-\sum_{i=1}^{\left\lfloor\frac{n}{d_k}\right\rfloor} i^{k+1}[\frac{d_{k-1}}{d_k}\mid i]\right)\\
=&d_k^{k+1}\left(\sum_{i=1}^{\left\lfloor\frac{n}{d_k}\right\rfloor} i^{k+1}-\sum_{i=1}^{\left\lfloor\frac{\left\lfloor\frac{n}{d_k}\right\rfloor}{\frac{d_{k-1}}{d_k}}\right\rfloor} \left(i\frac{d_{k-1}}{d_k}\right)^{k+1}\right) \color{#999999}<\text{换}\ i\to i\frac{d_{k-1}}{d_k}>\\
=&d_k^{k+1}\sum_{i=1}^{\left\lfloor\frac{n}{d_k}\right\rfloor} i^{k+1}-d_{k-1}^{k+1}\sum_{i=1}^{\left\lfloor\frac{\left\lfloor\frac{n}{d_k}\right\rfloor}{\frac{d_{k-1}}{d_k}}\right\rfloor} i^{k+1}
\end{aligned}
$$

## 工程细节  


记 $sum(n,k)=\sum_{i=1}^ni^k$。  
这里等幂和可以 $\Theta(k\log k)$ 或 $\Theta(k^2)$ 计算。  
此时：

$$
f(k)=
\begin{cases}
sum(n,1)-d_{t_{max}}sum(\left\lfloor\frac{n}{d_{t_{max}}}\right\rfloor,1) & k=0\\
d_1^2sum(\left\lfloor\frac{n}{d_1}\right\rfloor,2) & k=1\\
d_k^{k+1}sum(\left\lfloor\frac{n}{d_k}\right\rfloor,k+1)-d_{k-1}^{k+1}sum(\left\lfloor\frac{\left\lfloor\frac{n}{d_k}\right\rfloor}{\frac{d_{k-1}}{d_k}}\right\rfloor,k+1)& k>1
\end{cases}
$$

当 $d=1$ 时注意特判为 $sum(n,2)$。

## 代码实现

```cpp
#include <bits/stdc++.h>
#define P 998244353ll
int64_t B[30]={1,499122176,166374059,0,565671800,0,308980395,0,565671800,0,892369952,0,247549973,0,166374060,0,624392049,0,203902097,0,293422811,0,947614962,0,247463393,0,167799576,0,56462502,0};
int64_t F[30]={1,1,2,6,24,120,720,5040,40320,362880,3628800,39916800,479001600,237554682,331032489,972509923,586493473,986189864,781263551,868586527,401576539,447152495,853155713,655938692,768863313,254940118,638976950,282223649,914551701,567646151};
int64_t T,n,d,D[30],t_max;
int64_t fpow(int64_t a,int64_t n) {
  int64_t ans=1;for(a%=P;n;n>>=1,(a*=a)%=P)if(n&1)(ans*=a)%=P;return ans;
}
int64_t sum(int64_t n,int64_t k){
  int64_t ans=0,i=k,ni=n=(n+1)%P;
  for(;i!=-1;--i,(ni*=n)%=P)ans+=(F[k+1]*fpow(F[i],P-2)%P*fpow(F[k+1-i],P-2)%P*B[i]%P*ni%P);
  return (ans%P*fpow(k+1,P-2)+P*P)%P;
}
int64_t f(int64_t k){
  if(k==0)return (sum(n,1)-D[t_max]*sum(n/D[t_max],1)%P+P)%P;
  if(k==1)return (D[1]*D[1]%P*sum(n/D[1],2))%P;
  return (fpow(D[k],k+1)*sum(n/D[k],k+1)%P-fpow(D[k-1],k+1)*sum(n/D[k]/(D[k-1]/D[k]),k+1)%P+P)%P;
}
int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0), std::cout.tie(0);
  std::cin>>T;
  while(T--){
    std::cin>>n>>d;
    if(d==1){std::cout<<sum(n,2)<<"\n";continue;}//特判
    std::map<int64_t,int64_t> p;//质因数分解
    for(int64_t i=2;i*i<=d;++i)while(!(d%i))++p[i],d/=i;
    if (d!=1)p[d]=1;
    t_max=0;for(auto[p_i,t_i]:p)t_max=std::max(t_max,t_i);
    for(int64_t i=1;i<=t_max;i++){//求D_i
      D[i]=1;for(auto[p_i,t_i]:p)D[i]*=fpow(p_i,int64_t(t_i/(i*1.0)+0.99));
    }
    //代入公式计算
    int64_t ans=0;for(int64_t k=0;k<=t_max;++k)ans+=f(k);
    std::cout<<ans%P<<"\n";
  }
  return 0;
}
```

---

## 作者：s4CRIF1CbUbbL3AtIAly (赞：3)

## 题意

给出 $n$ 和 $d$，记 $v_i$ 表示 $d|i^k$ 的最小的 $k$（如果不存在则为 $0$），求 $\sum\limits_{i=1}^ni^{v_i+1}$。

$d\le 10^8,n<2^{63}$。

## 做法

首先考虑那些非 $0$ 的 $v_i$，也就是说将 $d$ 质因数分解为 $p_1^{a_1}p_2^{a_2}\dots p_x^{a_x}$ 之后，将那些 $i$ 分解成 $p_1^{b_1}p_2^{b_2}\dots p_x^{b_x}$，就要有 $b_jv_i\ge a_j$，而因为 $a_j$ 和 $b_j$ 都不超过 $63$，所以 $v_i$ 最多也只有 $63$。

于是考虑枚举 $v_i=k$，求此时所有的 $i^{k+1}$ 之和。

也就是 $\sum\limits_{i=1}^n[d|i^k][d\nmid i^{k-1}]i^{k+1}$。

这个显然可以先算出 $d|i^k$ 的，再减去 $d|i^{k-1}$ 的。于是我们先考虑前者。

继续考虑上面的质因数分解，这个时候就有 $b_jk\ge a_j$，即 $b_j\ge \lceil\dfrac{a_j}k\rceil$。

每一部分的指数都至少要为某一个值，等价于这个数是 $q=p_1^{a_1/k}p_2^{a_2/k}\dots p_x^{a_x/k}$ 的倍数。

那现在我们要求的就是 $\sum\limits_{i=1}^{\lceil\frac nq\rceil}(qi)^{k+1}=q^{k+1}\sum\limits_{i=1}^{\lceil\frac nq\rceil}i^{k+1}$。

这是一个自然数幂求和的形式，可以参考 [CF622F](https://www.luogu.com.cn/problem/CF622F)。也有一些 $O(k^2)$ 的递推，但是我的代码似乎常数比较大，只有 $O(k)$ 的能过去。

最后还剩下一些 $v_i=0$ 的 $i$ 之和，这个可以先求出 $\sum\limits_{i=1}^n i$，再减掉所有 $v_i>0$ 的和。后者的计算方法跟前面类似，只不过 $q$ 那里的 $k$ 要取到 $63$，而求和式子里的 $k$ 要为 $0$。

## 代码

```cpp
ll n,d,qian[65],hou[65],fc[65];
vector<pli>p;
ll S(ll n,int k){// 计算 1^k+2^k+...+n^k
	if(!n)return 0;
	vector<pair<ll,ll>>tmp;
	ll s=0;
	for(int i=1;i<=k+2;i++)tmp.push_back({i,(s+=qpow(i,k))%=mod});
	if(n<=k+2)return tmp[n-1].se;
	ll ans=0;
	qian[0]=hou[k+3]=1;
	for(int i=1;i<=k+2;i++)qian[i]=(n-i)%mod*qian[i-1]%mod;
	for(int i=k+2;i;i--)hou[i]=(n-i)%mod*hou[i+1]%mod;
	for(int i=1;i<=k+2;i++){
		ans=(ans+(tmp[i-1].se*(qian[i-1]*hou[i+1]%mod)%mod)*
		((((k+2-i)&1?mod-1:1ll)*fc[i-1]%mod)*fc[k+2-i]%mod)%mod)%mod;
	}
	return ans;
}
inline ll calc(ll q,int k){return qpow(q,k+1)*S(n/q,k+1)%mod;}
ll gq(int k){// 求 q
	ll q=1;
	for(auto i:p)q=q*qpow(i.fi,(i.se-1)/k+1)%mod;
	return q;
}

void __INIT__(){ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
fc[0]=1;// 预处理
for(int i=1;i<=62;i++)fc[i]=qpow(i,mod-2)*fc[i-1]%mod;
}
void __SOLVE__(int _case){
	cin>>n>>d;
	p.clear();
	for(ll i=2;i*i<=d;i++)if(d%i==0){
		int cnt=0;
		while(d%i==0)d/=i,++cnt;
		p.push_back({i,cnt});
	}
	if(d>1)p.push_back({d,1});// 质因数分解
	ll ans=0;
	for(int k=1;k<=60;k++){
		ans+=calc(gq(k),k);
		if(k>1)ans+=mod-calc(gq(k-1),k);
		ans%=mod;
	}
	ans=(ans+n%mod*((n+1)%mod)%mod*(mod+1>>1)%mod+mod-calc(gq(60),0))%mod;// v_i=0
	cout<<ans<<"\n";
}
```

---

## 作者：sbno333 (赞：2)

这个题难度比较高，赛时没调出来。

由于数据很大，一定要开 `__int128`。

当然，全开 `__int128` 有可能 RE，因此我们开的时候要慎重。

我们先考虑一个简单的问题。

给定 $a,b$，求出最小正整数 $k$，使得 $b|a^k$。

此时我们可以质因数分解 $a,b$，计算每个质因数次数的比，取最大值向上取整即可。

于是质因数分解 $b$ 变成了必要的一步。

显然如果 $d|i^k$，则一定有 $d|i^{k+x}$，$x$ 为任意自然数。

我们可以假设所有 $v(i)=0$，算出答案。

然后枚举 $v(i)$。

每次枚举到 $e$ 时，我们假设所有 $v(i)\le e$ 的 $v(i)$ 为 $e$，由于 $d|i^{k+x}$，因此枚举到后面的情况一定被前面的包含。

那么枚举时计算贡献要先减去这些数原来的贡献，即上次枚举得到的贡献，然后加上当前的贡献。

我们枚举到 $v(o)$ 时，满足条件的数计算是好维护的，即设 $d=\prod\limits_{i=1}^{inn}a_i^{p_i}$，其中 $a_i$ 均为质数，$p_i$ 为正整数。

即所有正整数 $l$，使得 $\prod\limits_{i=1}^{inn}a_i^{\lceil\cfrac{p_i}{v(o)}\rceil}|l$，$l\le n$。

下文为了方便，记 $s=\prod\limits_{i=1}^{inn}a_i^{\lceil\cfrac{p_i}{v(o)}\rceil}|l$。

即设正整数 $y$ 满足 $y\le\cfrac{n}{s}$，所有 $s\times y$ 都满足条件。

此时贡献为 $\sum\limits_{i=1}^{\lfloor\cfrac{n}{s}\rfloor}(is)^{v(i)+1}$。

简单推出原式为 $s^{v(i)+1}\times\sum\limits_{i=1}^{\lfloor\cfrac{n}{s}\rfloor}i^{v(i)+1}$。

对于 $\sum\limits_{i=1}^{\lfloor\cfrac{n}{s}\rfloor}i^{v(i)+1}$，这一看就是个板子，可以通过 bdfs 得出，具体可以看[这里](https://www.luogu.com.cn/problem/CF622F)。

于是代码出炉啦！
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const __int128 mod=998244353;
__int128 a[109],p[109],pp[109];
__int128 inn;
__int128 ksm(__int128 a,__int128 b){
	int ans=1;
	while(b){
		if(b&1) ans=ans*a%mod;
		b>>=1,a=a*a%mod;
	}
	return ans;
}
__int128 _sum(int n,int k){//计算 1^k+2^k+3^k...+n^k
	if(n==0){
		return 0;
	}
	int pri[109]={},mi[109]={},cnt=0;
	bool P[109]={};
	int f[109]={},g[109]={};
	__int128 fac[109]={},inv[109]={},ans=0;
	mi[1]=1;
	for(__int128 i=2;i<=k+2;++i){
		if(!P[i]) mi[i]=ksm(i,k),pri[++cnt]=i;
		for(__int128 j=1;j<=cnt&&i*pri[j]<=k+2;++j){
			P[i*pri[j]]=1;
			mi[i*pri[j]]=mi[i]*mi[pri[j]]%mod;
			if(i%pri[j]==0) break;
		}
	}
	for(__int128 i=1;i<=k+2;++i) mi[i]=(mi[i]+mi[i-1]>mod?mi[i]+mi[i-1]-mod:mi[i]+mi[i-1]);
	f[0]=g[0]=1;
	if(n<=k+2) return mi[n]; 
	f[0]=g[k+3]=fac[0]=inv[0]=1;
	for(__int128 i=1;i<=k+2;++i) f[i]=f[i-1]*(n-i)%mod;
	for(__int128 i=k+2;i>=1;--i) g[i]=g[i+1]*(n-i)%mod;
	for(__int128 i=1;i<=k+2;++i) fac[i]=fac[i-1]*i%mod;
	inv[k+2]=ksm(fac[k+2],mod-2);
	for(__int128 i=k+1;i>=1;--i) inv[i]=inv[i+1]*(i+1)%mod;
	for(__int128 i=1;i<=k+2;++i){
		__int128 a=f[i-1]*g[i+1]%mod;
		__int128 b=inv[i-1]*((k-i)&1?(mod-inv[k+2-i]):inv[k+2-i])%mod;
		ans=(ans+mi[i]*a%mod*b%mod)%mod;
	}
	return ans;
}
void _main(){
	long long a1,a2;
	cin>>a1>>a2;
	__int128 n,d;
	n=a1,d=a2;
	if(d==1){//d=1 并不寻常，因此特判
	    cout<<(long long)_sum(n,2)<<endl;
	    return;
	}
	while(inn>0){//多测清空
		a[inn]=p[inn]=0;
		inn--;
	}
	__int128 ma;
	ma=0;
	for(__int128 i=2;i*i<=d;i++){//质因数分解
		if(d%i==0){
			a[++inn]=i;
			while(d%i==0){
				d/=i;
				p[inn]++;
			}
			if(p[inn]>ma)//计算最大值方便循环，因为 v(i) 最大显然为 ma
			ma=p[inn];
		}
		
	}
	if(d>1){
		a[++inn]=d;
		p[inn]=1;
		if(p[inn]>ma)
			ma=p[inn];
	}
	__int128 ans;
	ans=0;
	ans=(n+1)%mod*n%mod*ksm(2,mod-2)%mod;//v(i) 均为 0 时的答案
	__int128 z=0;
	//cout<<(long long)mi<<endl;
	for(__int128 i=ma;i>=1;i--){//枚举 v(i)
		__int128 an,a1;
		an=1;
		for(__int128 j=1;j<=inn;j++){//计算 an=s
			pp[j]=(p[j]+i-1)/i;
			an*=ksm(a[j],pp[j]);
		}
		a1=n/an;
		ans+=_sum(a1,i+1)%mod*ksm(an,i+1)%mod;//计算当前的贡献
		ans+=100*mod;
		ans-=_sum(a1,z+1)%mod*ksm(an,z+1)%mod;//去除之前的多余贡献
		ans%=mod;
		z=i;
	}
	ans%=mod;
	cout<<(long long)ans<<endl;
}
signed main(){
	long long t;
	cin>>t;
	while(t--){
		_main();
	} 
	return 0;
}
```

---

## 作者：diqiuyi (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/P10322)。

提供一个很捞的做法。

显然 $v(i)$ 只和 $\gcd(i,d)$ 有关。不妨枚举 $d$ 的因数，考虑它的倍数对答案的贡献。

所以答案为 $\begin{aligned}\sum_{i\mid d}\sum_{j=1}^{n/i} (ij)^{v(i)}[\gcd(j,d/i)==1]\end{aligned}$。

整理一下可得答案为：

$\begin{aligned}\sum_{i\mid d}i^{v(i)+1}\sum_{j=1}^{n/i}j^{v(i)+1}[\gcd(j,d/i)==1] &=\sum_{i \mid d}i^{v(i)+1}\sum_{j=1}^{n/i}j^{v(i)+1}\sum_{p \mid i,j}\mu(p) \\&=\sum_{i \mid d}i^{v(i)+1}\sum_{p \mid \frac{d}{i}}\mu(p)\sum_{j=1}^{n/i/p} j^{v(i)+1}\end{aligned}$

显然 $v(i)$ 为 $d$ 的所有质因子在 $d$ 中出现次数与在 $i$ 中出现次数的商的最大值，这个可以在枚举 $i$ 时顺便计算。后面的那个 $\sum_{i=1}^n i^k$ 可以用[这题](https://www.luogu.com.cn/problem/CF622F)的方法求。然后直接暴力做就可以，复杂度应该是 $O(T(\sqrt{d}+\log^3 d))$，总之是可以过的。

**CODE**
```cpp
#include <bits/stdc++.h>
#define ull unsigned long long
#define ll long long
#define uint unsigned int
#define pii pair<int,int>
using namespace std;
inline ll read(){
	ll x=0;bool f=1;char c=getchar();
	while(c>'9'||c<'0'){if(c=='-')f=0;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return f?x:-x;
}
const int mod=998244353;
int d,t,p[50],aph[50],cnt,p1,k[50],ans,res2,fac[50],fac2[50],caf[50],kkk[50]/*,mu[maxn+5],prime[9000000]*/;
ll n;
//bitset<maxn+5> vis;
int Pow(int x,int y){
	int res=1;
	for(;y;y>>=1,x=1ll*x*x%mod)
		if(y&1)
			res=1ll*res*x%mod;
	return res; 
}
int getpow(ll n,int k){
	n%=mod;
	int y=0,fm=0,res=0;
	fac2[k+3]=1;
	for(int i=k+2;i;i--) fac2[i]=1ll*fac2[i+1]*(n-i)%mod;
	caf[0]=1;
	for(int i=1;i<=k+2;i++) caf[i]=1ll*caf[i-1]*(n-i)%mod;
	for(int i=1;i<=k+2;i++){
		y+=Pow(i,k),fm=1ll*fac[i-1]*fac[k-i+2]%mod;
		if(y>=mod) y-=mod;
		if(k-i&1) fm=-fm;
		res=(res+1ll*y*fac2[i+1]%mod*caf[i-1]%mod*Pow(fm,mod-2)%mod)%mod;
	}
	return (res+mod)%mod;
}//这里直接把我 cf622f 的代码搬过来了，所以很丑
inline void solve(int x){
	memset(aph,0,sizeof(aph));
	for(int i=2;i*i<=x;i++)
		if(!(x%i)){
			p[++cnt]=i;
			while(!(x%i)) x/=i,aph[cnt]++;
		}
	if(x>1) p[++cnt]=x,aph[cnt]=1;
}
void dfs2(int x,int lmt){
	if(x>cnt){
		int p2=1,mu=1;
		for(int i=1;i<=cnt;i++){
			if(kkk[i]>1) mu=0;
			else if(kkk[i]==1) mu=-mu;
			for(int j=1;j<=kkk[i];j++)
				p2*=p[i];
		}//mu 不能线性筛，只能直接算
		if(!mu) return ;
		res2=(res2+1ll*mu*Pow(p2,lmt)*getpow(n/p1/p2,lmt)%mod)%mod;
		return ;
	}
	for(int i=0;i<=aph[x]-k[x];i++)
		kkk[x]=i,dfs2(x+1,lmt);
}
void solv(int d,int p1,int lmt){
	if(d==1) lmt=1;
	lmt++;
	int res=Pow(p1,lmt);
	res2=0;
	dfs2(1,lmt);
	ans=(ans+1ll*res*res2%mod)%mod;
} 
void dfs(int x){
	if(x>cnt){
		p1=1;
		int nd=0;
		bool flg=1;
		for(int i=1;i<=cnt;i++){
			flg&=(k[i]>0);
			for(int j=1;j<=k[i];j++)
				p1*=p[i];
			if(k[i]) nd=max(nd,(aph[i]+k[i]-1)/k[i]); 
		}
		solv(d,p1,flg?nd:0);
		return ;
	}
	for(int i=0;i<=aph[x];i++)
		k[x]=i,dfs(x+1);
}//实际上是上文的 i
void print(int x){
	if(x>9) print(x/10);
	putchar(x%10|48);
}
signed main(){
    fac[0]=1;
	for(int i=1;i<=30;i++) fac[i]=1ll*fac[i-1]*i%mod;
	t=read();
	while(t--){
		n=read(),d=read(),cnt=ans=0;
		solve(d);
		dfs(1);
		print((ans%mod+mod)%mod),putchar(10);
	}
    return 0;
}
```

---

## 作者：Purslane (赞：1)

# Solution

一道平凡的题目。

考虑把所有数按照 $v(i)$ 分类。

注意到 $v(i) \le t$ 的数都是 $k$ 的倍数，其中 $k$ 是满足 $k \mid d$ 且 $d \mid k^t$ 的最小的  $k$。

所以我们计算

$$
\sum_{v(i) \le t} i^{t+1}
$$

本质在计算

$$
k^{t+1} \sum_{i=1}^{\lfloor \frac{n}{k} \rfloor} i^{t+1}
$$

这是拉格朗日插值的典中典用途。

不过考虑你可能多算了一些，所以这时候还要减去

$$
k^{t+2} \sum_{i=1}^{\lfloor \frac{n}{k} \rfloor} i^{t+2}
$$

注意特判 $d=1$。

```cpp
#include<bits/stdc++.h>
#define int long long 
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=100+10,MOD=998244353;
int T,n,d,D,mx;
int qpow(int base,int p) {
	int ans=1;
	while(p) {
		if(p&1) ans=ans*base%MOD;
		base=base*base%MOD,p>>=1;	
	}
	return ans;
}
int sum_of_pow(int n,int k) {
	n%=MOD; int ans=0,pre=0;
	ffor(i,1,k+2) {
		pre=(pre+qpow(i,k))%MOD;
		int u=pre,d=1;
		ffor(j,1,k+2) if(i!=j) u=u*(n-j)%MOD,d=d*(i-j)%MOD;
		ans=(ans+u*qpow(d,MOD-2))%MOD;
	}
	return (ans%MOD+MOD)%MOD;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--) {
		cin>>n>>d,mx=0,D=d;
		if(d==1) {cout<<sum_of_pow(n,2)<<'\n';continue ;}
		vector<pair<int,int>> frac;
		ffor(i,2,D/i) if(D%i==0) {
			int cnt=0;
			while(D%i==0) cnt++,D/=i;
			frac.push_back({i,cnt});
			mx=max(mx,cnt);
		}
		if(D!=1) frac.push_back({D,1}),mx=max(mx,1ll);
		int tans=sum_of_pow(n,1);
		roff(i,mx,1) {
			int mul=1; for(auto pr:frac) mul*=qpow(pr.first,pr.second/i+!!(pr.second%i));
			tans=(tans+qpow(mul,i+1)*sum_of_pow(n/mul,i+1))%MOD;
			if(i!=mx) tans=(tans-qpow(mul,i+2)*sum_of_pow(n/mul,i+2))%MOD;
			else tans=(tans-mul*sum_of_pow(n/mul,1))%MOD;
		}
		cout<<(tans%MOD+MOD)%MOD<<'\n';
	}
	return 0;
}
```

---

## 作者：Kreado (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P10322)。

## 思路

容易得到我们要求的是

$$\sum_{i=1}^n\sum_{k\ge 0} i^{k+1 }[d\mid i^k\land d\nmid i^{k-1}]$$

对于 $d$ 的质因数分解 $d=\displaystyle \prod_{i=1}^q p_i^{\beta_i}$，令 $f_k(d)=\displaystyle \prod_{i=1}^k p_i^{\lceil \beta_i/k \rceil}$。

若 $d\mid i^k$，那么一定有 $f_k(d)\mid i$，这是充分必要的，原式便转换成了

$$\sum_{i=1}^n \sum_{k\ge 0} i^{k+1}[f_k(d)\mid i\land f_{k-1}(d)\nmid i]$$

改变上指标得到

$$\sum_{k\ge 0}f_k(d)^{k+1}\sum_{i=1}^{n/f_k(d)}i^{k+1}\biggl[\frac{f_{k-1}(d)}{f_k(d)}\not\biggl\lvert  i\biggl]$$

令 $g_k(d)=\dfrac{f_{k-1}(d)}{f_k(d)}$（容易发现这是整数），对原式进行容斥得到

$$\sum_{k\ge 1}f_k(d)^{k+1}\left(\sum_{i=1}^{n/f_k(d)}i^{k+1}-g_k(d)^{k+1}\sum_{i=1}^{n/f_k(d)g_k(d)}i^{k+1}\right)$$
注意当 $k=1$ 时 $k-1$ 为 $0$，我们要特殊处理这一部分，这是平凡的，这一部分贡献是

$$d^2\sum_{i=1}^{n/d}i^2$$

特别的，当 $k=0$ 时，记 $r=f_{\inf}(d)$，这一部分的贡献是

$$\sum_{i=1}^n i-r\sum_{i=1}^{n/r}i$$

由于 $k$ 是 $\mathcal{O}(\log n)$ 级别的，后面算自然数的 $k$ 次方和可以做到 $\mathcal O (k)$，因此总时间复杂度就是 $\mathcal O(T(\sqrt d+\log^2n))$。

自然数 $k$ 次方和可以看 [CF622F](https://www.luogu.com.cn/problem/CF622F)，其实就是差分得到其为 $k+1$ 次多项式后进行一遍拉格朗日插值法。

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int Maxn=1e5+7,N=1e5;
const int Mod=998244353;
int T,d;
ll n;
vector<pair<int,int> >divs;
bitset<Maxn>isp;
vector<int>prm;

inline int ksm(ll a,int b,int mod){
    ll z=1;
    while(b){
        if(b&1) z=1ll*a*z%mod;
        a=1ll*a*a%mod;
        b>>=1;
    }
    return z;
}
inline int f(int k){
    int nd=1;
    for(auto [p,b]:divs) for(int j=1;j<=(b/k+(b%k!=0));j++) nd=nd*p;
    return nd;
}
inline int g(int k){
    return f(k-1)/f(k);
}
ll Smk[Maxn];
ll pre[Maxn],suf[Maxn];
ll fac[Maxn],Inv[Maxn];
inline ll upd(ll x){
    return (x%Mod+Mod)%Mod;
}
inline ll solvek(ll m,int k){
    for(int i=1;i<=k+2;i++) Smk[i]=(Smk[i-1]+ksm(i,k,Mod))%Mod;
    if(m<=k+2) return Smk[m];
    pre[0]=suf[k+3]=1;
    ll mm=m%Mod;
    for(int i=1;i<=k+2;i++) pre[i]=pre[i-1]*upd(mm-i)%Mod;
    for(int i=k+2;i;i--) suf[i]=suf[i+1]*upd(mm-i)%Mod;
    ll ret=0;
    for(int i=1;i<=k+2;i++){
        ll res=Smk[i]*Inv[i-1]%Mod*Inv[k+2-i]%Mod;
        if((k+2-i)&1) res=(Mod-res);
        res=res*pre[i-1]%Mod*suf[i+1]%Mod;
        ret=(ret+res)%Mod;
    }
    return ret;
}


int main(){
    scanf("%d",&T);
    for(int i=2;i<=N;i++)
        for(int j=i+i;j<=N;j+=i)
            isp.set(j);
    for(int i=2;i<=N;i++) if(!isp.test(i)) prm.emplace_back(i);
    fac[0]=1;
    for(int i=1;i<=N;i++) fac[i]=fac[i-1]*i%Mod;
    Inv[N]=ksm(fac[N],Mod-2,Mod);
    for(int i=N-1;~i;i--) Inv[i]=Inv[i+1]*(i+1)%Mod;

    while(T--){
        scanf("%lld%d",&n,&d);
        divs.resize(0);
        int nd=d,pd=1;
        for(auto p:prm){
            if(!(nd%p)){
                int cnt=0;
                pd*=p;
                while(!(nd%p)) nd/=p,cnt++;
                divs.emplace_back(p,cnt);
            }
        }
        if(nd!=1) divs.emplace_back(nd,1),pd*=p;

        ll ans=1ll*solvek(n/d,2)*d%Mod*d%Mod;
        ans=(ans+upd(solvek(n,1)-1ll*solvek(n/pd,1)*pd%Mod))%Mod;
        for(int k=2;k<=63;k++){
            ll now1=f(k),now2=g(k);
            ll z=upd(solvek(n/now1,k+1)-ksm(now2,k+1,Mod)*solvek(n/now1/now2,k+1)%Mod)%Mod;
            ans=(ans+z*ksm(now1,k+1,Mod)%Mod)%Mod;
        }
        printf("%lld\n",upd(ans));
    }
    return 0;
}
/*
100
9982443530 17
*/
```

---

