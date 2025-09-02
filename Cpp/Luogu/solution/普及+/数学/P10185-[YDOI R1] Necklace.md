# [YDOI R1] Necklace

## 题目背景

hdkk 正在做项链。

## 题目描述

hdkk 有 $n$ 种颜色的珠子，每种珠子有 $a_i$ 颗，他可以选出任意颗珠子串成一串项链。

每种珠子有一个漂亮值 $v_i$，hdkk 认为项链有一个美丽度，若第 $i$ 种珠子在项链中有 $cnt$ 颗并且 $cnt\ge1$，则这串项链的美丽度会加上 $(v_i)^{cnt}$。



现在他想知道，所有不同的项链的美丽度总和是多少，请你求出答案，并对 $10^9+7$ 取模。

定义两串项链是不同的，当且仅当存在一颗珠子，它在一串项链中出现，在另一串中没有出现。

注意：每颗珠子都是互不相同的，即使颜色一样。

## 说明/提示

### 样例解释 #1

颜色 $1$：$\left\{1\right\}$，颜色 $2$：$\left\{2,3\right\}$。

共有 $7$ 种不同的项链：$\left \{1 \right \},\left \{2\right \},\left \{3\right \},\left \{1,2 \right \},\left \{1,3 \right \},\left \{2,3 \right \},\left \{1,2,3 \right \}$，美丽度总和为 $2+3+3+(2+3)+(2+3)+3^2+(2+3^2)=38$。


**本题采用捆绑测试。**

|子任务编号|$n\le$|$a_i\le$|分值|
|:--:|:--:|:--:|:--:|
|$1$|$4$|$5$|$15$|
|$2$|$10^3$|$10^3$|$25$|
|$3$|$2\times10^5$|$10^9$|$60$|

对于所有数据，保证 $1\le n\le2\times10^5$，$1\le a_i\le10^9$，$1\le v_i\le10^9$。

## 样例 #1

### 输入

```
2
1 2
2 3 ```

### 输出

```
38```

## 样例 #2

### 输入

```
2
18 2
9 1```

### 输出

```
786624```

# 题解

## 作者：sLMxf (赞：15)

[或许更好的阅读体验](https://www.cnblogs.com/SLMXF/articles/18035442)/[题目传送门](https://www.luogu.com.cn/problem/P10185)

## 前置芝士
1. 二项式定理：$(a+b)^n=\sum \limits_{i=0}^{n}C^i_n\times a^i\times b^{n-i}$
2. 快速幂

## Meaning
有 $n$ 种珠子，每种有 $a_i$ 颗，且美丽值为 $v_i$。任意两颗珠子不同（同种类也算不同）。每种珠子有一个漂亮值 $v_i$。项链有一个美丽度，若第 $i$ 种珠子在项链中有 $cnt$ 颗并且 $cnt\ge1$，则这串项链的美丽度会加上 $(v_i)^{cnt}$。求所有不同的项链的美丽度总和是多少。
## Solution
以下记 $S=\sum\limits^n_{i=1} a_i$，且以下式子默认对 $10^9+7$ 取模。
### subtask 1
留给搜索。

每一颗珠子枚举是否选择，即有 $2^S$ 种项链。枚举一下就行。

时间复杂度 $O(2^S)$。
### subtask 2
开始推式子。

对于第 $i$ 种珠子，剩下 $S-a_i$ 颗珠子，有 $2^{S-a_i}$ 种取法。而在这 $i$ 颗珠子中，取 $x$ 颗，美丽值增加 ${(v_i)}^x$。取 $x$ 颗珠子的方案数为 $C^x_{a_i}$。所以答案为：
$$
\begin{aligned}\sum \limits _{i=1}^n\sum\limits_{x=1}^{a_i}(2^{S-a_i}\times C^x_{a_i}\times {v_i}^x)
&=\sum \limits _{i=1}^n[2^{S-a_i}\times \sum\limits_{x=1}^{a_i}(C^x_{a_i}\times {v_i}^x)]
\end{aligned}$$

时间复杂度 $O(S\log S)$。其中 $\log S$ 是快速幂的时间复杂度。
### subtask 3
显然，subtask 2 的时间复杂度会 T 飞。

外面一层明显无法化简，此时回头看一眼二项式定理：
$$(a+b)^n=\sum \limits_{i=0}^{n}C^i_n\times a^i\times b^{n-i}$$
再看看里面那一坨式子：
$$\sum\limits_{x=1}^{a_i}(C^x_{a_i}\times {v_i}^x)$$
稍微变下形：
$$\sum\limits_{x=1}^{a_i}(C^x_{a_i}\times {v_i}^x\times 1^{a_i-x})$$
~~这两个好像！~~

所以答案可以变为 $\sum \limits _{i=1}^n[2^{S-a_i}\times (v_i+1)^{a_i}]$？

由于原式中是从 $1$ 开始遍历的，所以还需要减去 $C_{a_i}^0\times {v_i}^0\times 1^{a_i}=1$。

故答案为 $\sum \limits _{i=1}^n\{2^{S-a_i}\times [(v_i+1)^{a_i}-1]\}$

时间复杂度 $O(n\log S)$。
## code
**杜绝复制！**
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[2000003],v[2000003];
int qpow(int a,int n,int mod)
{
    int re=1;
    while(n)
    {
        if(n&1)
            re=(re*a)% mod;
        n>>=1;
        a=(a*a)%mod;
    }
    return re%mod;
}
signed main()
{
	int n,ans=0,s=0;
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i],s+=a[i];
	for(int i=1;i<=n;i++) cin>>v[i];
	for(int i=1;i<=n;i++)
	{
		int cnt=0;
		cnt=qpow(v[i]+1,a[i],1000000007)-1;
		ans+=cnt*qpow(2,s-a[i],1000000007),ans%=1000000007;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：hdkk (赞：4)

## subtask 1：

暴搜每颗珠子选或不选即可，这里不再赘述。

## subtask 2：

因为是求和，我们可以单独考虑贡献，考虑有多少方案使第 $i$ 种珠子出现 $j$ 颗。

从 $a_i$ 颗珠子选 $j$ 颗应有 $C^j_{a_i}$ 种方案，其他种类的珠子则有选或不选两种选择，设 $sum$ 为所有珠子数量，则方案数应为：

$$2^{sum-a_i}\times C^j_{a_i}$$

造成贡献为：

$$2^{sum-a_i}\times C^j_{a_i} (v_i)^j$$

由于 $n$ 和 $a_i$ 都不大，我们可以预处理组合数后枚举 $i$ 和 $j$ 得到总贡献，代码如下。

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int c[1005][1005],n,a[10005],sum=0,ans=0,v[10005];
const int md=1e9+7;
int qpow(int a,int b)
{
	int res=1;
	while(b)
	{
		if(b&1)
			res=(res*a)%md;
		a=a*a%md;
		b>>=1;
	}
	return res;
}
signed main()
{
	c[1][0]=c[1][1]=1;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		sum+=a[i];
	}
	for(int i=1;i<=n;i++)
		cin>>v[i];
	for(int i=2;i<=1000;i++)
	{
		c[i][0]=1;
		for(int j=1;j<=i;j++)
			c[i][j]=(c[i-1][j-1]+c[i-1][j])%md;
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=a[i];j++)
			ans=(ans+qpow(2,sum-a[i])*c[a[i]][j]%md*qpow(v[i],j)%md)%md;
	}
	cout<<ans;
}

```

## subtask 3：

我们发现其实并不需要枚举 $j$，只需得到第 $i$ 种珠子所有方案总贡献，再乘上其他珠子方案数即可，式子为：

$$2^{sum-a_i}\times (\sum_{j=1}^{a_i}C_{a_i}^j (v_i)^j)$$

后面部分很像二项式定理展开式，发现：

$$(v_i+1)^{a_i}=\sum_{j=0}^{a_i}C_{a_i}^j(v_i)^j$$

只需减去 $1$ 即可得到，于是式子变成：

$$2^{sum-a_i}\times ((v_i+1)^{a_i}-1)$$

前后两部分都可以用快速幂计算，代码如下：

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a[200005],v[200005],sum=0,ans=0;
const int md=1e9+7;
int qpow(int a,int b)
{
	int res=1;
	while(b)
	{
		if(b&1)
			res=res*a%md;
		a=a*a%md;
		b>>=1;
	}
	return res;
}
signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		sum+=a[i];
	}
	for(int i=1;i<=n;i++)
		cin>>v[i];
	for(int i=1;i<=n;i++)
	{
		ans=(ans+qpow(2,sum-a[i])*(qpow(v[i]+1,a[i])-1+md)%md)%md;
	}
	cout<<ans;
}

```

---

## 作者：IceKylin (赞：3)

### P10185 [YDOI R1] Necklace 题解

简单算贡献题。

下记 $\displaystyle s=\sum_{i=1}^n{a_i}$。

由于每种珠子间互不影响，所以考虑分开计算每种珠子的贡献。

钦定选 $k$ 颗第 $i$ 种珠子，贡献为 $2^{s-a_i}\displaystyle v^k{a_i\choose k}$。所以总贡献可以写成：

$$\text{ans}=\displaystyle\sum_{i=1}^{n}2^{s-a_i}\sum_{k=1}^{a_i}v^k{a_i\choose k}$$

然后引入二项式定理（可能和标准形式有所不同）：

$$\displaystyle(x+1)^k=\sum_{i=0}^k x^i{k\choose i}$$

发现原式右边很像二项式定理的样子，只是求和的下标从 $1$ 而非 $0$ 开始。所以得到：


$$\text{ans}=\displaystyle\sum_{i=1}^{n}2^{s-a_i}\left[\left(v+1\right)^{a_i}-1\right]$$

直接算就好了。

---

## 作者：WhitD (赞：2)

注：本文记 $m=\sum_{i=1}^na_i$ 表示珠子总数。

前置知识：二项式定理
$$(a+b)^n=(\sum_{i=0}^nC_n^i\times a^{n-i}\times b^i)$$
## 思路
暴力思路比较显然，$O(2^n)$ 爆搜即可。

因为我们是对所有项链的美丽度总和进行求和，只要分别求出每种珠子在所有项链中的美丽度总和再 $O(n)$ 求和即可。

考虑从第 $i$ 种珠子（共 $a_i$ 个）中选 $j$ 个组成的项链：因为珠子互不相同，因此第 $i$ 种珠子中选 $j$ 个的选法共有 $C_{a_i}^j$ 种，每种选法可以提供 $(v_i)^j$ 的美丽度。所以只选这种珠子的美丽度之和为： 
$$\sum_{j=1}^{a_i}C_{a_i}^j\times(v_i)^j$$

不难发现这个式子和二项式定理很相似，只不过它是从 $j=1$ 开始枚举的，只需将原式稍加变形（乘上 $1$）再加上 $j=0$ 的结果（显然就是 $C_{a_i}^0\times1^{a_i}\times(v_i)^0=1$）即可化简：
$$(v_i+1)^{a_i}=\sum_{j=0}^{a_i}C_{a_i}^j\times1^{a_i-j}\times(v_i)^j=(\sum_{j=1}^{a_i}C_{a_i}^j\times(v_i)^j)+1$$
$$\sum_{j=1}^{a_i}C_{a_i}^j\times(v_i)^j=(v_i+1)^{a_i}-1$$

一串项链最多有 $m$ 个珠子，因为我们只计算第 $i$ 种珠子的美丽度之和，所以计算时只需考虑一串珠子的个数而不是种类，其他的 $(m-a_i)$ 个珠子只有选或不选两种情况，总方案数就是 $2^{m-a_i}$。

综上，第 $i$ 种珠子的美丽度总和为：
$$2^{m-a_i}\times((v_i+1)^{a_i}-1)$$

结合快速幂即可快速求解。

---

## 作者：Link_Cut_Y (赞：1)

稍微分析一下就可以得到答案。

不妨设 $f_i$ 表示考虑完了前 $i$ 中颜色，得到项链的美丽度之和。

则对于第 $i + 1$ 中颜色，每一种选珠子的方式，设其选出了 $c$ 个珠子，都可以与前面的某个方案配对，$f_{i + 1}$ 产生贡献。

设前面的方案数为 $s$，则选出某 $c$ 个珠子，产生的贡献就是 $c \times s + f_i$。

故设选择前 $i$ 种珠子的方案为 $s_1$，选择第 $i + 1$ 种珠子的方案为 $s_2$，选择第 $i + 1$ 种珠子的价值和为 $V$，有转移：

$$f_{i +1} \leftarrow f_i \times s_2 +V \times s_1$$

$s_1, s_2$ 的获得是平凡的。接下来考虑 $V$ 如何求解。

不妨再设 $g_j$ 表示，第 $i + 1$ 种珠子中，已经考虑完了前 $j$ 个，得到的珠子价值和是多少。

若选择第 $j + 1$ 颗珠子，则有转移 $g_{j + 1} \leftarrow g_j \times v$。

若不选择第 $j + 1$ 颗珠子，则有转移 $g_{j +1} \leftarrow g_j$

最后不要忘记，如果只选择 $j + 1$ 这一个珠子，还有转移 $g_{j +1} \leftarrow v$。

因此总转移为：

$$g_{j +1} = (v + 1)g_j + v$$

发现这个转移可以使用矩阵快速幂优化，故求解一个珠子的价值，其复杂度为 $O(\log a)$。总复杂度即为 $O(n \log a)$。

这里给出核心代码，矩阵乘法以及输入输出的实现需要读者自行完成。

```cpp
int n, a[N], v[N], s[N], f[N];
int calc(int v, int n) {
	Matrix t; t[0][0] = v + 1; t[1][0] = t[1][1] = 1;
	Matrix B; B[0][1] = v; t = t ^ n; B = B * t;
	return B[0][0];
}
signed main() {
	// input
	rep(i, 1, n) s[i] = s[i - 1] + a[i];
	rep(i, 1, n) {
		f[i] = f[i - 1] * qpow(2, a[i]) % mod; 
		(f[i] += qpow(2, s[i - 1]) * calc(v[i], a[i])) %= mod;
	}
	write('\n', f[n]); return 0;
}
```

---

## 作者：Ginger_he (赞：1)

对于每种颜色分开考虑，权值和为

$$\sum_{j=1}^{a_i}\binom{a_i}{j}\times v_i^{j}=(v_i+1)^{a_i}-1$$

方案数为

$$2^{s-a_i}$$

其中 $s=\sum\limits_{i=1}^na_i$

把所有颜色的权值和和方案数乘起来然后相加即可。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define N 200005
const int p=1e9+7;
inline int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x*f;
}
int n,x,a[N],s,ans;
inline int quickpow(int a,int b)
{
	int res=1;
	while(b)
	{
		if(b&1) res=1ll*res*a%p;
		b>>=1;
		a=1ll*a*a%p;
	}
	return res;
}
int main()
{
	n=read();
	for(int i=1;i<=n;i++) a[i]=read(),s=(s+a[i])%(p-1);
	for(int i=1;i<=n;i++)
	{
		x=read();
		ans=(ans+1ll*quickpow(2,(s-a[i]+p-1)%(p-1))*(quickpow(x+1,a[i])-1+p)%p)%p;
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：sbno333 (赞：0)

这道题要注意是横着输入~~别问我怎么知道的~~。

我们考虑每种珠子的贡献。

设只有自己的贡献的和为 $x_j$。

总方案数为 $2^{\sum a_i}$，包括空，即使对答案没有贡献。

去掉当前 $a_j$，总共 $2^{(\sum a_i)-a_j}x_j$ 的贡献。

```cpp
int ans;
ans=0;
for(int i=1;i<=n;i++){
	ans+=x[i]%mod*ksm(2,s-a[i])%mod;//s 为 a[i] 的和
	ans%=mod;
}
cout<<(long long)ans;
```
上面的代码仅供理解，并非本人真实代码的一部分。

接着我们需要计算 $x_i$。

假设选取 $j$ 个珠子，则有 $\binom{a_i}{j}$ 种方案。

总共的答案为 $\binom{a_i}{j}\times{v_i}^j$。

当然，没有珠子不贡献答案，因此最终第 $i$ 种的贡献为 $\sum\limits_{j=0}^{a_i}\binom{a_i}{j}\times{v_i}^j-1$，为什么不能 $j$ 从 $1$ 开始然后不减去 $1$ 呢？因为从 $0$ 开始性质多一些，继续往下看。

此时我们能拿到 $40$ 分，我们只能从组合数求和入手优化。

这是凭借我们~~灵敏的直觉~~的经验，次数逐渐加大，这就是二项式定理！

二项式定理 $\sum\limits_{i=0}^{n}\binom{n}{i}\times{x}^i{y}^{n-i}=(x+y)^n$。

证明~~学过动态规划的都知道数学归纳法能自己证明~~可以 bdfs。

我们设二项式定理中的 $n=a_i,i=j,x=v_i,y=1$。

则得到原式等于 $(v_i+1)^n-1$。

快速幂计算即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int __int128
const int mod=1e9+7;
int ksm(int a,int b){
	int ans;
	ans=1;
	while(b){
		if(b&1){
			ans*=a;
			ans%=mod;
		}
		a*=a;
		a%=mod;
		b>>=1;
	}
	return ans;
}
long long a[1000009];
long long b[1000009];
signed main(){
	long long n;
	cin>>n;
	int s;
	s=0;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		s+=a[i];
	}
	for(int i=1;i<=n;i++){
		cin>>b[i];
	}
	int ans;
	ans=0;
	for(int i=1;i<=n;i++){
		ans+=(ksm(b[i]+1,a[i])+mod-1)%mod*ksm(2,s-a[i])%mod;
		ans%=mod;
	}
	cout<<(long long)ans;
	return 0;
}
```

---

## 作者：Jerry_heng (赞：0)

（一）

考虑对每一种颜色单独求解。

对于一次第 $k$ 种的“循环”，美丽度会加上 

$$\sum_{i=1}^{a_k}C_{n}^{i}\times v_k^{i}=(v_k+1)^{a_k}-1$$ 


相信大家都学过二项式定理。

“循环”次数取决于其他珠子是否出现，即 $2^{\sum_{i=1}^{a_i}-a_k}$。

再将两式相乘就愉快 AC 了。


（二）

警钟敲烂：注意输入格式。

我调了 $1$ 天。

（三）

AC 代码。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a[200010],v[200010],ans,pw[200010];
const int md=1e9+7;
int pow(int x,int y){
	int ss=1;
	while(y){
		if(y&1)ss=ss*x%md;
		x=x*x%md;
		y>>=1;
	}
	return ss;
}
signed main(){
	scanf("%lld",&n);
	int s=0;
	for(int i=1;i<=n;i++)scanf("%lld",&a[i]),s+=a[i];
	for(int i=1;i<=n;i++)scanf("%lld",&v[i]);
//	pw[0]=1;
//	for(int i=1;i<=s;i++)pw[i]=pw[i-1]*i%md;
//	for(int i=0;i<=a[1];i++)
//		for(int j=0;j<=a[2];j++){
//			if(i==0&&j==0)continue;
//			else if(j==0)ans=(ans+pow(v[1],i)*C(a[1],i)%md)%md;
//			else if(i==0)ans=(ans+pow(v[2],j)*C(a[2],j)%md)%md;
//			else ans=(ans+((pow(v[1],i)+pow(v[2],j))%md*C(a[1],i)%md*C(a[2],j)%md))%md;
//		}
//	printf("%lld\n",ans);
//	return 0;
	for(int i=1;i<=n;i++){
		ans=(ans+pow(2ll,s-a[i])*((pow(v[i]+1ll,a[i])-1ll+md)%md)%md)%md;
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：elbissoPtImaerD (赞：0)

枚举选择的类型以及个数算贡献，则答案为：$\large \sum\limits_{i=1}^n 2^{\sum\limits_{j\neq i}a_j} \sum\limits_{j=1}^{a_i} v_i ^j \binom {a_i} j$。

后面那个求和显然是二项式定理的形式：$\sum\limits_{j=1}^{a_i} v_i ^j \binom {a_i} j = (v_j+1)^{a_i} - 1$。

枚举 $i$，快速幂计算即可。

[$\color{green}{\checkmark}$](https://www.luogu.com.cn/record/148396426)

---

## 作者：xishanmeigao (赞：0)

（[题目传送门](https://www.luogu.com.cn/problem/P10185)）

对每种珠子考虑它的贡献。显然珠子的顺序是无用的，重要的是个数。设第 $i$ 种珠子选了 $j$ 颗。先不管其它珠子。因为同种颜色的珠子也有区别，所以它的贡献就是 $\dbinom{a_i}{j}\times (v_i)^j$。总贡献就是

$$\sum\limits_{j=1}^{a_i}\dbinom{a_i}{j}\times (v_i)^j$$

由二项式定理知它等于

$$(v_i+1)^{a_i}-1$$

现在再考虑其它珠子，考虑第 $i$ 种珠子的贡献时其它珠子可以乱选，所以记 $sum=\sum a_i$，上述式子还要乘上 $2^{sum-a_i}$。所以答案即

$$\sum\limits_{i=1}^n{2^{sum-a_i}\times ((v_i+1)^{a_i}-1)}$$

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int N=2e5+10,MOD=1e9+7;

int n,a[N],v[N],ans,sum;

int ksm(int x,int y)
{
	int res=1;
	while(y)
	{
		if(y&1)
			res=1LL*res*x%MOD;
		x=1LL*x*x%MOD;
		y>>=1;
	}
	return res;
}

signed main()
{
	scanf("%lld",&n);
	for(int i=1; i<=n; i++)
		scanf("%lld",&a[i]),sum+=a[i];
	for(int i=1; i<=n; i++)
		scanf("%lld",&v[i]);
	for(int i=1; i<=n; i++)
	{
		int res=ksm(v[i]+1,a[i]);
		res--;
		if(res<0)
			res+=MOD;
		(ans+=1LL*res*ksm(2,sum-a[i])%MOD)%=MOD;
	}

	printf("%lld\n",ans);
	
	return 0;
}
```



---

## 作者：modfish_ (赞：0)

## 思路
考虑对于每种珠子分别计算其贡献。

例如，对第 $i$ 种珠子：

选 $1$ 颗，有 $\binom{a_i}{1}$ 种选法，贡献为 $v_i^1$。

选 $2$ 颗，有 $\binom{a_i}{2}$ 种选法，贡献为 $v_i^2$。

……

选 $a_i$ 颗，有 $\binom{a_i}{a_i}$ 种选法，贡献为 $v_i^{a_i}$。

全部累加：

$$\binom{a_i}{1}v_i^1+\binom{a_i}{2}v_i^2+\dots+\binom{a_i}{a_i}v_i^{a_i}$$

由二项式定理，上式等于：

$$(v_i+1)^{a_i}-1$$

再考虑每一种贡献在总贡献中出现的次数：就是除第 $i$ 种珠子外其余珠子的选法总数。

设柱子一共有 $sum$ 颗，则除第 $i$ 种外有 $sum-a_i$ 颗，由乘法原理得选法总数为 $2^{sum-a_i}$。

所以所有贡献之和为：

$$\sum_{i=1}^n2^{sum-a_i}((v_i+1)^{a_i}-1)$$

用快速幂简单算算，时间复杂度 $O(n\log n)$。

## 代码
```cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int maxn = 2e5 + 5, mod = 1e9 + 7;

ll a[maxn], v[maxn];

ll qpow(ll a, ll x){
	ll ans = 1;
	while(x){
		if(x & 1) ans = (ans * a) % mod;
		a = (a * a) % mod;
		x >>= 1;
	}
	return ans;
}

int main(){
	int n;
	scanf("%d", &n);
	ll sum = 0;
	for(int i = 1; i <= n; i ++){
		scanf("%lld", &a[i]);
		sum += a[i];
	}
	for(int i = 1; i <= n; i ++){
		scanf("%lld", &v[i]);
	}
	ll ans = 0;
	for(int i = 1; i <= n; i ++){
		ans = (ans + ((((qpow(v[i] + 1, a[i]) - 1 + mod) % mod) * qpow(2ll, sum - a[i])) % mod)) % mod;
	}
	printf("%lld", ans);
	return 0;
}
```


---

