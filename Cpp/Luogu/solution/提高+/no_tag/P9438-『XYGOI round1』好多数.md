# 『XYGOI round1』好多数

## 题目背景

小 X 在和小 L 一起玩。他们走到了公园，发现了一棵长得很奇怪的参天大树。这棵树，按照 OIer 们的习惯，它有一个明显特征，那就是**严重右偏**。

## 题目描述

小 X 想到了另外一个东西，也是严重右偏的。

首先，他写下一个数字 $n$。  

接着，对于所有 $n$ 的因数 $x\notin\{1,n\}$，让 $x$ 从小到大的成为 $n$ 的儿子节点。 

递归的建这棵树，这棵树就建成了。小 X 把这棵树称为一个“$n$ 号数学树”。小 X 想知道，给定 $q$ 个正整数 $x$，它在 $n$ 号数学树出现了几次。  

因为 $n$ 很大，他只能告诉你 $n$ 的质因数分解。  

答案对 $998244353$ 取模。

## 说明/提示

样例解释：前两组数据均为 $24$ 号数学树。这棵树绘制以后如下：
![](https://cdn.luogu.com.cn/upload/image_hosting/ejrhdnv3.png)   

其中，$2$ 出现了 $8$ 次，$3$ 出现了 $4$ 次，$5,7$ 则没有出现过。  

对于第三组数据，你需要注意 $343$ 在 $343$ 号数学树的树根出现了一次，$1$ 不会在数学树中出现。  

| Subtask | $n$ | $q$ | 保证 $n$ 是质数的幂 | 分值 |
|:-:|:-:|:-:|:-:|:-:|
|0|$\le 10^3$|$\le 20$|Yes|10|
|1|$\le 10^6$|$\le 20$|No|10|
|2|$\sum b_i\le5000$|$\le 20$|Yes|40|
|3|$\sum b_i\le5000$|$\le 20$|No|40| 

对于 $100\%$ 的数据，$1\le b_i \le 5000$，$\sum b_i\le5000$，$2\le a_i\le 10^9$，$1\le x\le 10^{18}$。

## 样例 #1

### 输入

```
2 3 3 1 0 0
1
2```

### 输出

```
8```

## 样例 #2

### 输入

```
2 3 3 1 0 0
3
3 5 7```

### 输出

```
4 0 0```

## 样例 #3

### 输入

```
7 3 0 0
3
49 1 343```

### 输出

```
1 0 1```

# 题解

## 作者：lw21144 (赞：8)

## P9438『XYGOI round1』好多数

[题目传送门](https://www.luogu.com.cn/problem/P9438)，[博客](https://www.luogu.com.cn/blog/lzq-lw21144/solution-p9438)阅读更佳。

这是一道组合数学的好题，赛时调炸了，有点可惜，来补篇题解。

### Subtask 1, 2

对 $n$ 分解质因数后直接暴力搜索，记录 $1$ 到 $10^6$ 中每个数在树中出现了几次，直接输出即可。

### Subtask 3

本 Subtask 中保证 $n$ 是质数 $p$ 的 $k$ 次幂，以 $p=2,k=5,n=p^k=32$ 为例建立下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/jnf54f2o.png?x-oss-process=image/resize,m_lfit,h_1700,w_2250)

~~画的不是很好~~

观察此图，我们发现：

- 以 $2=2^1$ 为根的子树中仅有根节点 $2=2^1$。

- 以 $4=2^2$ 为根的子树中，除根节点外还有一个以 $2=2^1$ 为根的子树。

- 以 $8=2^3$ 为根的子树中，除根节点外还有两个分别以 $2=2^0,4=2^1$ 为根的子树。

据此，我们可以推断，以 $2^j$ 为根的子树，除根节点外相当于把 $2^i(0<i<j)$ 的子树复制了一遍，如上图。

接下来推广到一般，把 $2$ 换成任意质数 $p$，考虑出现次数。

对于 $p^i$，它将在 $p^i$ 的子树中出现在根节点，在 $p^{i+1}$ 的子树中出现在 $p^i$ 的子树中的 $1$ 次，在 $p^{i+2}$ 的子树中出现在 $p^i$ 的子树和 $p^{i+1}$ 的子树中，共 $2$ 次。

以此类推，因为 $p^k$ 最大符合条件的因数为 $p^{k-1}$，所以可得 $p^i$ 在整棵树中出现次数 $s$ 为：

$$s = 1+2^{(i+1)-i-1}+2^{(i+2)-i-1}+2^{(i+3)-i-1}+\cdots+2^{(k-1)-i-1}$$

即：

$$s=1+2^0+2^1+2^2+\cdots+2^{k-i-2}=1+\sum\limits_{j=0}^{k-i-2}2^j=2^{k-i-1}$$

所以只需特判每个问题中的 $x$ 是否为 $n$ 的因数，再直接代入计算即可。

### Subtask 4

终于来到正解了。先看题目中给出的这张图：

![](https://cdn.luogu.com.cn/upload/image_hosting/ejrhdnv3.png)

我们发现：$24=2^3\times3^1$，分解质因数后仅有 $1$ 个 $3$，但是 $3$ 在图中却出现了 $4$ 次。

观察根节点到每个 $3$ 节点的路径：

- $24-3$；
- $24-6-3$；
- $24-12-3$；
- $24-12-6-3$；

可以发现，$24$ 到 $3$ 的路径中是这样的：

- $24-(÷8)-3$；
- $24-(÷4)-6-(÷2)-3$；
- $24-(÷2)-12-(÷4)-3$；
- $24-(÷2)-12-(÷2)-6-(÷2)-3$；

这相当于分多次除去两数的商 $8$，而除去的次数是可以随意的。

考虑 dp，设 $n$ 分解质因数后，总共有 $t$ 个质因数。

对于 $n=\prod\limits_{i=1}^{t}{a_i^{b_i}}$ 和读入的 $x=\prod\limits_{i=1}^{t}{a_i^{h_i}}$，它们的商为相同底数的幂相减的结果，即 $\prod\limits_{i=1}^{t}{a_i^{b_i-h_i}}$。

设 $f_i$ 表示花费 $i$ 次除掉这个商，也就相当于总共有 $sum=\sum\limits_{j=1}^{t}{b_j-h_j}$ 个数，将这些数分成 $i$ 段除去。

根据隔板法，可得状态转移方程式：

$$f_i=\prod\limits_{j=1}^{t}C_{b_j-h_j+i-1}^{i-1}$$

但是这样就会出现问题，还是上图的那个例子。

手模一下样例，当 $n=24=2^3\times 3^1,x=3=2^0\times 3^1$ 时，易得 $t=2;\ a_1=2,b_1=3,h_1=0;\ a_2=3,b_2=1,h_2=1$。

令 $i=2$，则根据上式可算出：$f_2=C_{3-0+2-1}^{2-1}\times C_{1-1+2-1}^{2-1}=C_4^1\times C_1^1=4\times 1=4$。

但是，由图中可以看出，两步变成 $3$ 的仅有 $24-6-3$ 和 $24-12-3$ 的 $2$ 种方案，与计算出的 $4$ 种方案不符。

进一步分析可以发现，多出的 $2$ 种方案分别是是 $24-24-3$ 和 $24-3-3$，相当于有一步是除以 $1$ 的无用步。

因此在状态转移方程式中，需要减去所有包含无用步的情况。

设在 $i$ 状态时（即分成 $i$ 段时）有 $j$ 步的无用步，那么：

- 这 $j$ 步的**选择方式**有 $C_i^j$ 种；
- 这 $j$ 步**放在各个因数位置**中的方式有 $f_j$ 种；

因此，根据乘法原理得无用步数为 $C_i^j\times f_j$ 种，最终的状态转移方程式：

$$f_i=\prod\limits_{j=1}^{t}C_{b_j-h_j+i-1}^{i-1}-\sum\limits_{j=1}^{i-1}{C_i^j\times f_j}$$

显然，最终答案 $ans$ 为分任意次除去两数的商的方案数之和，即：

$$ans=\sum\limits_{i=1}^{sum}{f_i}$$

时间复杂度 $O(q\times t^2)$，由于 $\sum{b_i}\leq 5000$，所以除掉次数的总上限不会超过 $5000$，在 $2$ 秒的时限下可以通过此题。

### 一些注意事项

- 组合数计算时求乘法逆元，要注意 $0$ 的逆元情况。

- 求 $f_i$ 时要做乘法，记得要全部初始化为 $1$。

- 注意 $q$ 个询问是独立的，要记得清空数组。

~~别问我为什么知道这些~~

### AC code

本代码包含了每个 subtask 的解法，供大家参考。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int mod=998244353;
int n,q,xx,yy,a[1000010],b[1000010],jc[1000010],ppow[1000010],p[1000010];

inline void Fre_open(){
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
}

namespace Fast_Read_And_Print{
	inline int read(){ //快读快写 
		int cnt=1,h=0; char ch=getchar();
		while(ch<'0'||ch>'9') cnt=(ch=='-')?-1:1,ch=getchar();
		while(ch>='0'&&ch<='9') h=h*10+(ch^48),ch=getchar();
		return h*cnt;
	}
	inline void print(int x){
		if(x<0) putchar('-'),x=-x;
		x>9?print(x/10),putchar((x%10)^48):putchar((x%10)^48);
	}
}
using namespace Fast_Read_And_Print;

namespace Bao_Li{ //暴力解法 
	inline void dfs(int x){
		p[x]++; //标记一次因数 
		for(int i=2;i<=sqrt(x);i++){
			if(x%i==0&&i*i==x) dfs(x/i);
			else if(x%i==0) dfs(i),dfs(x/i);
		}
		return;
	}
	inline void Solve_1(int sum){
		dfs(sum); //暴力搜索出现次数 
		while(q--){ //直接输出预处理的个数 
			xx=read(),print(p[xx]),putchar(32);
		}
	}
}

inline int quick_pow(int x,int y){
	if(y<0) return 1; int s=1;
	while(y){ //快速幂板子 
		if(y&1) s=(s*x)%mod;
		x=(x*x)%mod,y>>=1;
	}
	return s%mod;
}

namespace Sub_3{ // n 是质数的幂 
	inline void Solve_2(){
		while(q--){
			int x=read(),y=0,flag=0;
			if(x==1){ //题目说不会出现 1，直接特判 
				print(0),putchar(32); continue;
			}
			while(x>1){
				if(x%a[1]!=0&&x!=1){
					flag=1; break; //不存在这个因数 
				}
				x/=a[1],y++;
			}
			if(flag==1){
				print(0),putchar(32); continue;
			}
			int sum=quick_pow(2,b[1]-y-1);
			print(sum),putchar(32);
		}
	}
}

namespace Sub_4{ //正解 
	inline void init(){
		//预处理每个数的阶乘以及其逆元 
		jc[0]=1,ppow[0]=1; // 0 比较特殊，单独拿出来 
		for(int i=1;i<=1000005;i++){
			jc[i]=(jc[i-1]*i)%mod,ppow[i]=quick_pow(jc[i],mod-2);
		}
	}
	inline int C(int n,int m){
		if(n<m) return 0; //组合数计算，注意逆元 
		else return (((jc[n]*ppow[m])%mod)*ppow[n-m])%mod;
	}
	int h[1000010],f[1000010];
	inline void Solve_3(){
		init(); // printf("114514\n");
		while(q--){
			int cnt=read();
			memset(h,0,sizeof(h));
			memset(f,0,sizeof(f));
			if(cnt==1){ //题目说不会出现 1，直接特判 
				print(0),putchar(32); continue;
			}
			for(int i=1;i<=n;i++){
				while(cnt%a[i]==0&&h[i]<=b[i]) cnt/=a[i],h[i]++;
				// 对 cnt 分解质因数，cnt=(a[1]^h[1])*(a[2]^h[2])*...*(a[n]^h[n]) 
			}
			int flag=0,sum=0,anss=0;
			for(int i=1;i<=n;i++){
				if(b[i]!=h[i]) flag=1; sum+=b[i]-h[i];
			} 
			if(cnt>1){
				print(0),putchar(32); continue; // cnt 不能被 n 整除 
			}
			if(flag==0){ 
				print(1),putchar(32); continue;
				//每个幂都相等，此时 cnt 就是 n 本身，仅在根节点出现一次 
			}
			// dp
			for(int i=1;i<=sum;i++){
				f[i]=1; //因为要做乘法，所以初始化为 1 
				for(int j=1;j<=n;j++){
					f[i]=(f[i]*C(b[j]-h[j]+i-1,i-1))%mod;
					// printf("%lld %lld %lld\n",b[j]-h[j]+i-1,i-1,C(b[j]-h[j]+i-1,i-1));
				}
				// printf("\n");
				for(int j=1;j<i;j++){
					f[i]=(f[i]-((C(i,j)*f[j])%mod)+mod)%mod;
					// printf("%lld %lld %lld\n",i,j,C(i,j));
				}
				anss=(anss+f[i])%mod; //统计答案 
				// printf("%lld %lld\n",f[i],anss);
			}
			print(anss),putchar(32);
		}
	} 
}

signed main(){
	// Fre_open();
	while(1){ //读入 
		xx=read(),yy=read();
		if(xx==0&&yy==0) break;
		a[++n]=xx,b[n]=yy; 
	}
	int sum=1,flag=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=b[i];j++){
			sum*=a[i]; if(sum>1000000) flag=1,j=114514; //这里相当于 break 
		}
		if(flag) break;
	}
	q=read(); //读入询问次数 
	if(flag==0) Bao_Li::Solve_1(sum); //subtask 1,2 
	else if(flag==1&&n==1) Sub_3::Solve_2(); //subtask 3 
	else Sub_4::Solve_3(); //subtask 4 
    return 0;
} 
```

这是[通过记录](https://www.luogu.com.cn/record/113866024)，最大耗时点  $866$ 毫秒。

~~求管理给过审吧~~

---

update 2024.10.24

修改了部分错误，优化了一些语句表达。

---

## 作者：Piggy343288 (赞：4)

对于一次询问，相当于在考虑整数 $\frac{n}{x}$ 变为 $1$ 的方案数。进一步的，这相当于给定一个数列 $c_0\cdots c_k$，每一次可以减小任意位的任意值，但不能空选，问方案数，这里“空选”指的是不选任何一个数。  

先考虑允许空选的时候应该怎么做，令 $f(x)$ 代表正好走了 $x$ 步变为 $0$ 的方案数，允许空选。这个很简单，针对每一位都插板容斥，答案 $f(x)=\prod_{i=1}^k\limits\binom{c_i+x-1}{x-1}$。  

而我们进一步考虑 $g(x)$ 为正好走了 $x$ 步变为 $0$ 的方案数，不允许空选。这个也只需要针对 $f$ 进行容斥，枚举空选步数，大力推式子得出 $g(x)=\sum_{i=0}(-1)^{x-i}\binom{x}{i}f(i)$。  

容易发现，$Ans=\sum g(i)$。

$f$ 暴力，$g$ NTT 卷一下就行。不会 NTT 的小朋友们就平方复杂度的推出结果，此题一样可以通过。

---

## 作者：PosVII (赞：4)

**前言**

------------

运气好，拿到了场上首切。可惜教练不准打比赛，将我制裁了，于是比赛下分。

被波特和审核各拿下一次，有点搞的。

如果你格式真要求这么严的话我只能流汗黄豆了。

**思路**

------------

题面中说这是一颗树，有点难求答案，考虑转化答案。

发现连边一定是大连小，符合有向无环图的定义，于是可以不用拆点，把图变成一个 DAG，发现答案就是从 $n$ 到 $x$ 的路径数量。

然后设 $n = p_{1}^{q_{1}} \times p_{2}^{q_{2}} \times ... \times p_{k}^{q_{k}} (q_{i} > 0)$ 那么我们可以将 $x$ 分解为 $x = p_{1}^{b_{1}} \times p_{2}^{b_{2}} \times ... \times p_{k}^{b_{k}} (b_{i} \geq 0)$。

考虑无解情况：

1. 如果 $x$ 有了不属于 $p$ 数组的质因子的话显然是无解的，因为 $n$ 没有路径能走到它。
1. 如果存在 $b_{i} > q_{i}$，无解，因为 $n$ 也没有路径能走到它。

判断完无解后，考虑如何求解。设 $sum = (b_{1} - q_{1}) + (b_{2} - q_{2}) + ... + (b_{k} - q_{k})$，那么从 $n$ 到 $x$ 最多走 $sum$ 步，因为 $n$ 每次至少要除掉一个质因子，最少可以只走 $1$ 步。

考虑枚举步数。然后考虑 $n$ 只有一种质因子的情况。很显然，这是一个非常简单的盒子放球问题（视每一步为一个盒子，则问题是球相同，盒不同，不能空盒，可以用隔板法解决）。但是，如果是多个质因子呢？如果是这样的话，问题就变成了可以空盒，然后把对于每个质因子的分配方案数乘起来就行了。

但是，如果多个质因子在同一个地方都是空盒呢？这下难办了，我们需要去掉不合法方案。在处理走 $i$ 步的解 $f_{i}$ 时，我们已经将 $[1,i-1]$ 这一区间内的解求出来了，那么不合法的解可以通过在之前合法的解中插入一些原地踏步的步数就可以容斥去重了。

给出一个式子：

$f_{i} = \prod \limits^{k}_{j=1} C^{i - 1}_{q_{j} - b_{j} + i - 1} - \sum^{i-1}_{k=1} f_k \times C^{k}_{i}$

按上面的式子求就好了。注意特判 $n = x$ 和 $x = 1$ 的情况！

**code**

------------

```
#include<bits/stdc++.h>
using namespace std;
#define int long long
template<typename G> inline void read(G &x) {x=0;G f=1;char ch=getchar();while((ch<'0'||ch>'9')&&ch!='-') ch=getchar();if(ch=='-') f=-1,ch=getchar();while(ch>='0'&&ch<='9') {x=x*10+(ch^48);ch=getchar();}x*=f;}
const int MAXN=1e5+5,p=998244353;
int qpow(int x,int y) {
	int res=1;
	while(y) {
		if(y&1) res=res*x%p;
		x=x*x%p,y>>=1;
	}return res;
}
int a[MAXN],b[MAXN],fac[MAXN],inv[MAXN],cnt;
int C(int x,int y) {
	return fac[x]*inv[y]%p*inv[x-y]%p;
}
int q,x,tot[MAXN],f[MAXN];
signed main() {
	fac[0]=1;
	for(int i=1;i<MAXN;++i) fac[i]=fac[i-1]*i%p;
	inv[MAXN-1]=qpow(fac[MAXN-1],p-2);
	for(int i=MAXN-2;i>=0;--i) inv[i]=inv[i+1]*(i+1)%p;
	while(1) {
		++cnt;
		read(a[cnt]),read(b[cnt]);
		if(a[cnt]==0&&b[cnt]==0) break;
	}
	read(q);
	while(q--) {
		read(x);
		if(x==1) {
			printf("0 ");
			continue;
		}
		bool fl=0;
		int sum=0;
		for(int i=1;i<cnt;++i) {
			tot[i]=0;
			while(x%a[i]==0) x/=a[i],++tot[i];
			sum+=(b[i]-tot[i]);
			if(tot[i]>b[i]) {
				fl=1;
				break;
			}
		}
		if(x!=1) fl=1;
		if(fl) printf("0 ");
		else {
			if(!sum) {
				printf("1 ");
				continue;
			}
			int ans=0;
			for(int i=1;i<=sum;++i) {
				f[i]=1;
				for(int j=1;j<cnt;++j) {
					f[i]=f[i]*C(b[j]-tot[j]+i-1,i-1)%p;
				}
				for(int j=1;j<i;++j) f[i]=(f[i]-f[j]*C(i,j)%p+p)%p;
				ans=(ans+f[i])%p;
			}printf("%lld ",ans);
		}
	}
	return 0;
}
```



---

## 作者：Register_int (赞：3)

对 $x$ 进行质因数分解。如果 $x$ 不是 $n$ 的因子，直接判断无解。

设 $x=\prod c_i^{d_i}$。由于我们每次往下走一格都是除掉一个因数，所以，求 $x$ 出现的次数就是求算出 $x$ 的方案数。更近一步地，每一个质因子各需要除去 $t_i=b_i-d_i$ 个，每一步可以除掉至少一个质因子。

枚举步数 $i$，则每一个质因子都需要用最多 $i$ 除完。我们可以直接对 $t_i$ 进行分段，一段内的都在同一部内消掉。特别的，每一个质因子在一步内都可以选择不除，所以允许出现空段。答案为 $dp_i=\prod_j\dbinom{t_j+i-1}{i-1}$。

但这样会出现一个问题：所有数都不除，相当于这一步被空过了。这会导致算重很多情况。不过，我们可以钦定这 $i$ 步内恰好有 $j$ 步被空过，这样，恰好 $i$ 步的方案数就为 $dp_i\rightarrow dp_i-\sum^{i-1}_j\dbinom ijdp_j$，总方案数为 $\sum_idp_i$，时间复杂度 $O(\left(\sum b_i\right)^2)$。

# AC 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 1e6 + 10;
const int MAXM = 5e3 + 10;
const int mod = 998244353;

inline 
ll qpow(ll b, ll p) {
	ll res = 1;
	for (; p; p >>= 1, b = b * b % mod) if (p & 1) res = res * b % mod;
	return res;
}

int q, a[MAXN], b[MAXN], t[MAXN];

ll fac[MAXN], ifac[MAXN], x;

inline 
void init(int n) {
	*fac = 1;
	for (int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % mod;
	ifac[n] = qpow(fac[n], mod - 2);
	for (int i = n; i; i--) ifac[i - 1] = ifac[i] * i % mod;
}

inline 
ll c(int n, int m) {
	return fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}

ll dp[MAXN], ans; int n, m;

int main() {
	for (init(1e6); scanf("%d%d", &a[n + 1], &b[n + 1]), a[n + 1] && b[n + 1]; n++);
	for (scanf("%d", &q); q--;) {
		scanf("%lld", &x), m = 0;
		if (x == 1) { printf("0 "); continue; }
		for (int i = 1; i <= n; i++) t[i] = b[i];
		for (int i = 1; i <= n; i++) for (; x % a[i] == 0 && t[i]; t[i]--, x /= a[i]);
		if (x > 1) { printf("0 "); continue; }
		for (int i = 1; i <= n; i++) m += t[i];
		if (!m) { printf("1 "); continue; } ans = 0;
		for (int i = 1; i <= m; i++) {
			dp[i] = 1;
			for (int j = 1; j <= n; j++) dp[i] = dp[i] * c(t[j] + i - 1, i - 1) % mod;
			for (int j = 1; j < i; j++) dp[i] = (dp[i] - c(i, j) * dp[j] % mod + mod) % mod;
			ans = (ans + dp[i]) % mod;
		}
		printf("%lld ", ans);
	}
}
```

---

## 作者：zzx0102 (赞：2)

部分分做法摘自 [如何在 Div2 月赛中获得佳寄](https://www.luogu.com.cn/blog/Stitch0711/how-to-get-great-score-in-div2)，有兴趣的和我一样菜的蒟蒻可以看看。

暴力：直接枚举 $1-n$ 所有数的约数，然后枚举。

不知道为啥 $\mathcal{O(n\sqrt n)}$ 过了 $10^6$，~~也正如《OI 之梦》里所讲的：”$n^2$ 过百万，写个暴力踩标算“。~~

特殊性质：

令 $n=p^k$。

然后如果输入的数不是 $p$ 的整数幂，就没有方案。

如果输入的 $x=p^q$，且 $q>k$ 或 $q=0$，也没有方案。

否则，令 $x=p^q,0<p<k$，则答案为 $dp_{k-p}$。

$dp$ 的转移方程为 $dp_i=\sum\limits_{j=0}^{i-1}dp_j$。

$dp_0=1$。

因为 $p^x$ 到所有 $\forall 0<y<x,p^y$ 均有连边。

不要忘记取模。

赛时 $60$ 分代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1000010, p = 998244353; int n, a[N], b[N]; ll dp[N];
vector<int> e[N]; int cnt[N];
void init(int n) {
	for(int i = 1; i <= n; i++) {
		for(int j = 2; j * j <= i; j++) if(i % j == 0) {
			e[i].push_back(j);
			if(j * j != i) e[i].push_back(i / j);
		}
	}
}
void dfs(int x) {
	if(x == 1) return ;
	cnt[x]++;
	for(int v: e[x]) dfs(v);
}
signed main() {
	int x, y;
	while(cin >> x >> y) {if(!x) break; a[++n] = x, b[n] = y;}
	for(int i = 1; i <= b[1]; i++) dp[0] = 0;
	dp[0] = 1;
	for(int i = 1; i <= b[1]; i++) {
		for(int j = 0; j < i; j++) dp[i] = (dp[i] + dp[j]) % p;
	}
	if(n == 1) {
		int q, c = 0; cin >> q;
		while(q--) {
			ll x; cin >> x; ll y = x; int flag = 1; c = 0;
			if(x == 1) {cout << 0 << ' '; continue;}
			while(x > 1) {
				c++; if(c > b[1]) {flag = 0; break;}
				if(x % a[1]) {flag = 0; break;}
				x /= a[1];
			}
			if(!flag) cout << 0 << ' ';
			else {
				
				cout << dp[b[1] - c] << ' ';
			}
		}
	}
	else {
		ll m = 1; for(int i = 1; i <= n; i++) m *= pow(a[i], b[i]); init(m);
		dfs(m); int q; cin >> q;
		while(q--) {
			ll x; cin >> x;
			if(x > m) {cout << 0 << ' '; continue;}
			cout << cnt[x] << ' ';
		}
	}
	return 0;
}
```

~~怎么比正解还长~~

其实特殊性质已经很接近正解了。

假设 $n=\prod p_i^{t_i}$，输入的 $x=\prod a_i^{b_i}$，$a_i,p_i$ 是质数。

每一个因子需要除去 $d_i=t_i-b_i$ 次。

假设每个因子都在 $i$ 步之内除尽。那么对 $d_i$ 进行分段。

得出转移方程：

$$dp_i=\prod\limits_{j}C_{i-1}^{d_j+i-1}$$

但是所有数都不除，相当于这一步被空过了。

令前 $i$ 步内恰好空了 $j$ 步，则每次将 $dp_i$ 变为

$$dp_i-\sum\limits_{j=1}^{i-1}C_j^i\times dp_j$$

即可避免重复。

注意特判一些特殊情况。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 1000010, p = 998244353;
int inv[N], jc[N], Jc[N], dp[N], a[N], b[N], cnt[N], n, m;
void init(int n, int p) {
	inv[1] = 1, jc[0] = 1, Jc[0] = 1;
	for(int i = 2; i <= n; i++) inv[i] = 1LL * (p - p / i) * inv[p % i] % p;
	for(int i = 1; i <= n; i++) jc[i] = 1LL * jc[i - 1] * inv[i] % p, Jc[i] = 1LL * Jc[i - 1] * i % p;
}
int C(int n, int m) {return Jc[n] * jc[m] % p * jc[n - m] % p;}
signed main() {
	init(1e6, p); int P, q;
	while(cin >> P >> q, P || q) a[++n] = P, b[n] = q; cin >> q;
	while(q--) {
		int x; cin >> x; m = 0;
		if(x == 1) {cout << "0 "; continue;}
		for(int i = 1; i <= n; i++) cnt[i] = b[i];
		for(int i = 1; i <= n; i++) for(; x % a[i] == 0 && cnt[i]; cnt[i]--, x /= a[i]);
		if(x > 1) {cout << "0 "; continue;} int ans = 0;
		for(int i = 1; i <= n; i++) m += cnt[i];
		if(!m) {cout << "1 "; continue;}
		for(int i = 1; i <= m; i++) {
			dp[i] = 1;
			for(int j = 1; j <= n; j++) dp[i] = dp[i] * C(cnt[j] + i - 1, i - 1) % p;
			for(int j = 1; j < i; j++) dp[i] = (dp[i] - C(i, j) * dp[j] % p + p) % p;
			ans = (ans + dp[i]) % p;
		}
		cout << ans << ' ';
	}
    return 0;
}
```

---

## 作者：樱雪喵 (赞：1)

## Description

定义“$n$ 号数学树”为一棵根节点权值为 $n$ 的树，其中对于任意权值为 $x$ 的节点，它的儿子为除 $1$ 和 $x$ 外所有 $x$ 的约数。   
多次询问权值为 $x$ 的节点数。  

设 $n=\prod a_i^{b_i}$，$\sum b_i\le 5000,a_i \le 10^9,x\le 10^{18},q\le 20$。

## Solution

把 $x$ 质因数分解为 $\prod a_i^{c_i}$。

考虑这棵树在质因数分解后，每个点 $x$ 的父亲是 $x$ 的倍数，也就是说父亲的 $c_i$ 序列是 $x$ 的 $c_i$ 序列挑选其中几位并把他们的值变大得到的。那么向上不断跳父亲的过程即为，每次选择一些 $c_i$ 把它们变大，不能什么都不选，直到所有 $c_i=b_i$。  
考虑枚举 $x$ 的深度，设深度为 $i$ 的 $x$ 有 $f_i$ 个。  
对于每个质因数分别考虑，设 $g_{i,j}$ 表示变化了至多 $i$ 次，值增加了 $j$ 的方案数。这里单独对于一个质因数是可以不变的，因为全局至少有一个质因数变大，乘积就是变大的。  

那么这个东西其实就是，把 $j$ 个数分 $i$ 组，可以有的组为空。插板，得 $g_{i,j}=\binom{j+i-1}{i-1}$。

> 其实如果你不知道这个结论，也可以 dp，状态转移方程是 $g_{i,j}=\sum_{k=0}^j g_{i-1,k}$。前缀和优化一下也是 $O(n^2)$。

设 $h_{i}=\prod g_{i,b_i-c_i}$，那么 $f_i$ 即为 $h_i$ 去掉空选的情况，即 $f_i=h_i- \sum\limits_{j=1}^i \binom{i}{j}f_{i-j}$。  
答案即为 $\sum f_i$，时间复杂度 $O(n^2 q)$。


---

