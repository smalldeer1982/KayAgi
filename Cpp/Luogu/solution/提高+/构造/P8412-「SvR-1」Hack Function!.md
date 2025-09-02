# 「SvR-1」Hack Function!

## 题目背景

**Problem Number:** $\textit{63}$

小 C 坐在 J-PSC2077 的赛场（题目可于下方「**题目附件**」处下载）上，他早已年逾七旬，但作为 Z 队选手还是成功参赛。

## 题目描述

此时的 J-PSC 终于改成了 CF 赛制，小 C 迅速地 AK 了 Day 1，他发现 T2 function 比较好 Hack，题目的人话翻译如下：

> 对于一个数 $A$，定义函数 $f(A)$ 如下：
> 
> 1. 先把 $A$ 变成 $k$ 进制数 $B$。
> 2. 将 $A$ 替换为 $B$ 各位之和。
> 3. 返回执行第 1 步，直到 $B$ 是一位数为止。
> 4. 记 $x$ 表示 $A$ 此时的值（十进制）。
> 此时 $f(A) = x$，$f(A)$ 称作 $A$ 关于 $k$ 的**位和函数**。
>
> 给定 $k, l, r, p$，求出 $\sum_{i = l}^r f(i^i) \bmod p$ 的值。
>
> **特别地，当 $\sum_{i = l}^r f(i^i) = p$ 时，输出 $\texttt{perfect}$。**

小 C 迅速秒了该题，当他翻看别人的代码时，发现他们用的全是暴力枚举。（因为机子跑得飞快）

好不容易看到一个人，他的代码里竟然没有一个  $\texttt{perfect}$！但由于数据过弱，竟然让他 pp 了。

小 C 突然脑子一热，忘记了怎么构造 Hack 数据，所以他通过 Luogu 6.0 求助于你。

小 C 会告诉你 $k, p$ 的值，你需要构造一组 $l, r$，**使答案输出为 $\texttt{perfect}$**。

**若无法构造，输出两个 $\texttt{-1}$。**

## 说明/提示

#### 样例 1 说明

- 对于数据 $1$，在 $k = 10$ 下，有 $f(2^2) = f(4) = 4$，$f(3^3) = f(27) = 9$，显然 $l = 2, r = 3$ 时原题应该输出 $\texttt{perfect}$。
- 对于数据 $2$，在 $k = 10$ 下，发现不可能满足要求。
- 对于数据 $3$，在 $k = 2$ 下，显然有 $f(1^1) = 1$，但该样例仅用于理解，根据数据规模与约定，我们保证 $k \geq 10$。

#### 数据规模与约定

$$
\newcommand{\arraystretch}{1.5}
\begin{array}{c|c|c|c}\hline\hline
\textbf{Subtask} & \textbf{说明} & \textbf{时限} & \textbf{分值} \\\hline
\textsf{1} & \text{无解} & 1\text{ s} & 3 \\\hline
\textsf{2} & \text{有解且\textbf{\textsf{存在}}一组解使 }1\le l\le r\le 10^5 & 1\text{ s} & 16 \\\hline
\textsf{3} & 1\le p\le 10^7 & 1\text{ s} & 34 \\\hline
\textsf{4} & \text{无特殊限制} & 1.5\text{ s} & 47 \\\hline\hline
\end{array}
$$

对于 $100\%$ 的数据，$10 \leq k \leq 10^3$，$1 \leq p \leq 10^8$，$1 \leq T \leq 10$。

保证时限在 std 用时的 $4$ 倍以上。

#### 评测说明

**本题开启 Special Judge 和捆绑测试。**

你需要保证 $l = r = -1$ 或 $1 \leq l \leq r \leq 10^{18}$ 且 $r - l \leq 10^{15}$，否则 SPJ 会将你的答案判为 $0$ 分。

## 样例 #1

### 输入

```
3
10 13
10 3
2 1```

### 输出

```
2 3
-1 -1
1 1```

# 题解

## 作者：CSP_Sept (赞：15)

Official Editorial.

## 题意

定义函数 $f_k(x)$，给定 $k,p$，构造 $l,r$ 使得

$$
\sum\limits_{i=l}^rf_k(i^i)=p
$$

## 解法

### Subtask 1

直接输出 $\texttt{-1}$ 即可。

### Subtask 2

直接暴力枚举并用 map 维护即可。时间复杂度为 $O(T N \log N)$。

### Subtask 3

首先，我们需要知道 $f$ 函数满足 $f(A) = (A - 1) \bmod (k - 1) + 1$。

证明：令 $A$ 在 $k$ 进制下各位分别为 $a_0, a_1, \cdots, a_m$，$f'(x) = \displaystyle\sum_{i = 0}^m a_i$，则 $f'(A)$ 表示 $A$ 在 $k$ 进制下每一位的和，且 $d(A)$ 即为不断地令 $A \leftarrow f'(A)$ 直到 $A < k$。

因为 $k^i \equiv 1 \pmod{k - 1}$，所以 $A = \displaystyle\sum_{i = 0}^m k^i a_i \equiv f'(A) \pmod{k - 1}$。证毕。

注意到 $f(A)$ 在这里不能为 $0$，于是当 $k - 1 \mid A$，令 $f(A) = k$ 即可。

接下来根据构造出的 $l, r$ 分类讨论。

1. $1\le l\le r\le\varphi(k-1)$\
直接暴力处理 $f(i^i)$ 的前缀和并将其存入 map，枚举计算即可。时间复杂度为 $O(k \log k)$。
2. $1\le l\le\varphi(k-1)<r$\
将其分为两部分处理。
   - $l\le i\le\varphi(k-1)$：同上。
   - $\varphi(k-1)<r$：考虑扩展欧拉定理，发现此时 $f(i^i)$ 存在循环节，循环节起点为 $\varphi(k-1) + 1$，循环节长度为 $\operatorname{lcm}(k-1,\varphi(k-1))$。考虑预处理出**整个循环节中前缀和 $\leq p$ 的部分**并枚举循环次数以及在 map 中查询。时间复杂度为 $O(\log k(k^2 + \frac{p}{k}))$。
3. $\varphi(k-1)<l\le r$\
考虑钦定 $l$ 位于第一个循环节中（反正都要循环）。\
接下来先特判 $l,r$ 均位于第一个循环节的情况，然后再枚举 $r$ 位于第几个循环节。设一个循环节内 $f(i^i)$ 的和为 $sum$，考虑到 $l \sim r$ 之间（不包括 $l,r$ 所在循环节）的循环节数 $cnt$ 一定满足 $cnt\cdot sum\le p\le sum\cdot(cnt+2)$，直接枚举至多三个循环节即可。时间复杂度为 $O(k^2 \log k)$。

综上，时间复杂度为 $O(T \log k(k^2 + \frac pk))$。

### Subtask 4

加上哈希即可。

时间复杂度为 $O(T(k^2 \log k + \frac pk))$。

## 代码

向 CSP_Sept 或洛谷氪金即可获得。

---

## 作者：lgvc (赞：11)

首先，
 $$ f(i)=\left\{
\begin{aligned}
i \bmod {K-1},((K-1) \nmid i) \\
{K-1},({(K-1)}\mid i) \\
\end{aligned}
\right.
$$
 然后考虑 $i^i \bmod {K-1}$ 的周期。
 
 前 $\varphi_{K-1}$ 个 $i$ 没有周期，然后后面有长度为 $\text{lcm}(K-1,\varphi_{K-1})$ 的周期。
 
 于是抛弃前 $\varphi_{K-1}$ 个，算出一个周期的和。
 
 把一种方案的完整连续周期去除，剩下的拼在一起，一定是一个周期复制两遍的一个连续子序列。
 
遍历一个周期复制两遍，开一个 $\text{umap}$ 记录每一个前缀和的出现位置即可。

可能需要卡卡常数。

---

## 作者：Leasier (赞：6)

### Subtask $1$
直接输出 $-1$ 即可。
### Subtask $2$
直接暴力枚举并用 map 维护即可。时间复杂度为 $O(TN \log N)$。
### Subtask $3$
前置芝士：[扩展欧拉定理（exEuler）](https://oi-wiki.org/math/number-theory/fermat/#_5)

首先，我们需要知道 $f$ 函数满足 $f(A) = (A - 1) \bmod (k - 1) + 1$。

证明：令 $A$ 在 $k$ 进制下各位分别为 $a_0, a_1, \cdots, a_m$，$f'(x) = \displaystyle\sum_{i = 0}^m a_i$，则 $f'(A)$ 表示 $A$ 在 $k$ 进制下每一位的和，且 $d(A)$ 即为不断地令 $A \leftarrow f'(A)$ 直到 $A < k$。

因为 $k^i \equiv 1 \pmod{k - 1}$，所以 $A = \displaystyle\sum_{i = 0}^m k^i a_i \equiv f'(A) \pmod{k - 1}$。证毕。

注意到 $f(A)$ 在这里不能为 $0$，于是当 $k - 1 \mid A$，令 $f(A) = k$ 即可。

接下来根据构造出的 $l, r$ 分类讨论。

1. $1 \leq l \leq r \leq \varphi(k - 1)$

直接暴力处理 $f(i^i)$ 的前缀和并将其存入 map，枚举计算即可。时间复杂度为 $O(k \log k)$。

2. $1 \leq l \leq \varphi(k - 1) < r$

将其分为两部分处理。

- $l \leq i \leq \varphi(k - 1)$

同上。

- $\varphi(k - 1) < r$

考虑扩展欧拉定理，发现此时 $f(i^i)$ 存在循环节，循环节起点为 $\varphi(k - 1) + 1$，循环节长度为 $\operatorname{lcm}(k - 1, \varphi(k - 1))$。

考虑预处理出**整个循环节中前缀和 $\leq p$ 的部分**并枚举循环次数以及在 map 中查询。时间复杂度为 $O(\log k(k^2 + \frac{p}{k}))$。

3. $\varphi(k - 1) < l \leq r$

考虑钦定 $l$ 位于第一个循环节中（反正都要循环）。

接下来先特判 $l, r$ 均位于第一个循环节的情况，然后再枚举 $r$ 位于第几个循环节。设一个循环节内 $f(i^i)$ 的和为 $sum$，考虑到 $l \sim r$ 之间（不包括 $l, r$ 所在循环节）的循环节数 $cnt$ 一定满足 $cnt \times sum \leq p \leq sum \times (cnt + 2)$，直接枚举至多三个循环节即可。时间复杂度为 $O(k^2 \log k)$。

综上，时间复杂度为 $O(T \log k(k^2 + \frac{p}{k}))$。
### Subtask $4$
前置芝士：[哈希（Hash）](https://oi-wiki.org/ds/hash/)

其实本来是没有这个 Subtask 的。加上哈希是因为 Subtask $2$ 的做法可以在预处理循环但不进行上述讨论的情况下冲过 Subtask $3$。

时间复杂度为 $O(T(k^2 \log k + \frac{p}{k}))$。

代码：
```cpp
#include <stdio.h>

typedef long long ll;

const int N = 993012 + 7, mod = 1e6 + 7;

typedef struct {
	int cnt = 0;
	int head[mod];
	int nxt[N];
	int val[N];
	ll key[N];
	
	inline void clear(){
		for (register int i = 0; i < mod; i++){
			head[i] = 0;
		}
		for (register int i = 1; i <= cnt; i++){
			nxt[i] = val[i] = key[i] = 0;
		}
		cnt = 0;
	}
	
	inline int find(ll cur_key){
		ll pos = cur_key % mod;
		if (head[pos] == 0){
			cnt++;
			head[pos] = cnt;
			key[cnt] = cur_key;
			return cnt;
		}
		int pre = 0, cur = head[pos];
		while (cur != 0 && key[cur] != cur_key){
			pre = cur;
			cur = nxt[cur];
		}
		if (cur == 0){
			nxt[pre] = cur = ++cnt;
			key[cur] = cur_key;
		}
		return cur;
	}
	
	inline void assign(ll cur_key, int k){
		val[find(cur_key)] = k;
	}
	
	inline bool count(ll cur_key){
		for (register int i = head[cur_key % mod]; i != 0; i = nxt[i]){
			if (key[i] == cur_key) return true;
		}
		return false;
	}
	
	inline int query(ll cur_key){
		for (register int i = head[cur_key % mod]; i != 0; i = nxt[i]){
			if (key[i] == cur_key) return val[i];
		}
		return 0;
	}
} Hash;

const int M = 1e3 + 7;
Hash mp1, mp2;
int prime[M], phi[M];
ll sum1[M], sum2[N];
bool p[M];

inline void init(){
	int cnt = 0;
	p[0] = p[1] = true;
	phi[1] = 1;
	for (register int i = 2; i < M; i++){
		if (!p[i]){
			prime[++cnt] = i;
			phi[i] = i - 1;
		}
		for (register int j = 1; j <= cnt && i * prime[j] < M; j++){
			int t = i * prime[j];
			p[t] = true;
			if (i % prime[j] == 0){
				phi[t] = phi[i] * prime[j];
				break;
			}
			phi[t] = phi[i] * (prime[j] - 1);
		}
	}
}

inline ll quick_pow(ll x, ll p, ll mod){
	ll ans = 1;
	while (p){
		if (p & 1) ans = ans * x % mod;
		x = x * x % mod;
		p >>= 1;
	}
	return ans;
}

int gcd(int a, int b){
	return b == 0 ? a : gcd(b, a % b);
}

inline int lcm(int a, int b){
	return a * b / gcd(a, b);
}

inline ll max(ll a, ll b){
	return a > b ? a : b;
}

int main(){
	int t;
	scanf("%d", &t);
	init();
	for (register int i = 1; i <= t; i++){
		int k, p, kd, n, ansl = -1, ansr = -1;
		scanf("%d %d", &k, &p);
		kd = k - 1;
		n = phi[kd];
		mp1.clear();
		mp1.assign(0, 0);
		for (register int j = 1; j <= n; j++){
			sum1[j] = sum1[j - 1] + ((quick_pow(j, j, kd) - 1) % kd + kd) % kd + 1;
			if (sum1[j] >= p && mp1.count(sum1[j] - p)){
				ansl = mp1.query(sum1[j] - p) + 1;
				ansr = j;
				break;
			}
			mp1.assign(sum1[j], j);
		}
		if (ansl == -1 && ansr == -1){
			int m = lcm(kd, n);
			mp2.clear();
			mp2.assign(0, 0);
			for (register int j = 1; j <= m; j++){
				sum2[j] = sum2[j - 1] + ((quick_pow(j + n, j % n + n, kd) - 1) % kd + kd) % kd + 1;
				if (sum2[j] >= p && mp2.count(sum2[j] - p)){
					ansl = mp2.query(sum2[j] - p) + n + 1;
					ansr = j + n;
					break;
				}
				mp2.assign(sum2[j], j);
			}
			if (ansl == -1 && ansr == -1){
				for (register int j = 0; j * sum2[m] <= p; j++){
					ll t = j * sum2[m];
					for (register int x = n; x >= 1 && t + (sum1[n] - sum1[x - 1]) <= p; x--){
						if (mp2.count(p - (j * sum2[m] + (sum1[n] - sum1[x - 1])))){
							ansl = x;
							ansr = n + j * m + mp2.query(p - (t + (sum1[n] - sum1[x - 1])));
							break;
						}
					}
					if (ansl != -1 && ansr != -1) break;
				}
				if (ansl == -1 && ansr == -1){
					for (register int j = max((p - 1) / sum2[m] - 1, 0); j * sum2[m] <= p; j++){
						ll t = j * sum2[m];
						for (register int x = m; x >= 1 && t + (sum2[m] - sum2[x - 1]) <= p; x--){
							if (mp2.count(p - (t + (sum2[m] - sum2[x - 1])))){
								ansl = n + x;
								ansr = n + m * (j + 1) + mp2.query(p - (t + (sum2[m] - sum2[x - 1])));
								break;
							}
						}
						if (ansl != -1 && ansr != -1) break;
					}
				}
			}
		}
		printf("%d %d\n", ansl, ansr);
	}
	return 0;
}
```

---

## 作者：yizhiming (赞：4)

提供一个不需要 map/umap 的做法，代码和思路均来自我的教练。

## 题目大意

给定 $k,p$，要求构造一组 $l,r$，使得 $\sum\limits_{i=l}^r f(i^i) = p$，其中 $f(x)$ 表示把 $x$ 这个数写成 $k$ 进制后，对每一项求和，得到的新数接着做这个操作，直到 $k$ 进制下得到的数只有一位，此时停下来，得到的值就是 $f(x)$，$T$ 组数据。

要求 $1\leq l\leq r\leq 10^{18}$，$r-l\leq 10^{15}$，或者 $l=r=-1$，表示无解。

$10\leq k \leq 10^3$，$1\leq p\leq 10^8$，$1\leq T \leq 10$。

## 题目分析

首先结论是 $f(x) = x \bmod (k-1)$，特别的，为 $0$ 视作 $k$，证明别的题解说了不再赘述。

为了方便，下述视作 $k$ 已经减 $1$。

首先假设我们可以确定 $l,r$ 的范围很小，比如不超过 $10^5$，那么可以暴力算出来每个位置的点值，现在我们得到了一个恒正序列，问是否存在一个区间使得和为 $s$，若存在找到任意一个，否则报告无解。

这其实是很经典的东西，别的题解在这里使用了 map/umap，但实际上可以双指针，显然右端点往右移的过程中，权值单调增，直到增到某个时刻 $>s$ 了，再动左端点即可，直到右端点跑完整个区间结束。

那么考虑如何限定 $l,r$ 的范围，我们观察 $f$ 的式子，你会发现 $i^i$ 这个东西模意义下，分子有循环节 $k$，分母根据扩展欧拉定理也有循环节。

当然因为扩欧前半段不循环，所以我们要跑至少 $\varphi(k)+k\varphi(k)$，之后的部分就每 $k\varphi(k)$ 循环一次了。

容易发现这个东西的量级也就 $10^6$，我们可以暴力用双指针扫。然后考虑循环的部分怎么办，我们可以根据现在和答案的差值，来让右端点跑若干个整周期，直到再加就超过去了。

然后我们在此刻再跑一个周期的双指针就做完了。

但是，你发现这东西交上去挂了一个点，我找了半天的原因，在和其他题解对拍的加持下发现，你最后一部分的双指针要跑两个周期，原因是你这个时候左端点一定不会跑满一个整周期了，但是右端点可以，因为右端点扩的过程中，左端点移动删贡献可能调整到一个合适的位置，其实就相当于在右端点跑整周期之前，让左端点稍微往前走了几步。

容易发现这个东西只需要跑两个整周期就能解决，因为你左端点最多会删掉一个周期，而你右端点会往右走当且仅当你左端点移动了删掉的贡献让右端点走，因为你最多删一个整周期，所以右端点最多在原本移动的基础上再加一个周期，总计不超过两个周期。

跑不满，复杂度 $O(Tk\varphi(k))$。

## code

这实际上是拿教练没调完的代码调出来的，当前最优解代码才是我教练的。

```cpp
#include <cstdio>
#include <iostream>
using namespace std;
const int N=1010;
typedef long long ll;
int k,p,t,phi,l,lcm,sum,rmax,bei;
ll r;
bool ok;
int f[N*N+N],s[N*N+N];
int read(){
	char ch;
	int w=0,f=1;
	ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')f=-f;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		w=w*10+ch-'0';
		ch=getchar();
	}
	return w*f;
}
int get_phi(int k){
	int ans=1;
	for(int i=2;i*i<=k;i++){
		if(k%i==0){
			ans*=i-1;
			k/=i;
			while(k%i==0){
				ans*=i;
				k/=i;
			}
		}
	}
	if(k>1)ans*=k-1;
	return ans;
}
int gcd(int a,int b){
	return b?gcd(b,a%b):a;
}
int power(int a,int b){
	int ans=1;
	while(b){
		if(b&1)ans=(ll)ans*a%k;
		a=(ll)a*a%k;
		b>>=1;
	}
	return ans;
}
int getf(int x){
	if(x<=phi)return power(x%k,x);
	else return power(x%k,x%phi+phi);
}
int main(){
//	freopen("data.txt","r",stdin);
//	freopen("me.txt","w",stdout);
	t=read();
	while(t--){
		k=read();p=read();
		k--;sum=0;ok=0;
		phi=get_phi(k);
		lcm=k*phi/gcd(k,phi);
		l=1;
		rmax=phi+lcm;
		for(r=1;r<=rmax;r++){
			f[r]=getf(r);
			f[r]=(f[r]+k-1)%k+1;
//			printf("f[%d]=%d\t",r,f[r]);
			s[r]=s[r-1]+f[r];
			sum+=f[r];
			while(sum>p){
				sum-=f[l];
				l++;
			}
			if(sum==p){
				ok=1;break;
			}
		}
//		cout<<"LR:"<<l<<' '<<r<<'\n';
		if(!ok){
			r--;//如果跑到这个地方，上面循环完全跑完，r是rmax+1,需回调一个数 
			int xhs=s[rmax]-s[phi];
			bei=(p-sum)/xhs;
			sum+=bei*xhs;
			r+=bei*lcm;
//			cout<<"R:"<<r<<" "<<sum<<" "<<xhs<<" "<<lcm<<" "<<phi<<"\n";
			if(sum==p){
				ok = 1;
				break;
			}
			for(int i=1;i<=2*lcm;i++){
				sum+=f[phi+(i>lcm?i-lcm:i)];
				r++;
//				if(r==1273433){
//					cout<<"L:"<<l<<"\n";
//				}
				while(sum>p){
					sum-=f[l];
					l++;
				}
				if(l>rmax)break;
				if(sum==p){
					ok=1;break;
				}
			}
		}
		
		if(ok){
			cout<<l<<" "<<r<<"\n";
		}else{
			printf("-1 -1\n");
		}
	}
	return 0;
}
```

---

## 作者：kevinzheng0426 (赞：2)

首先 $f(x)=(x-1) \bmod (k-1) + 1$ 是个经典结论，然后问题就变成求一对 $l,r$ 满足 $\sum_{i=l}^r g(i)=p$，令 $n=k-1$，

$$
g(i)=
\begin{cases}
n&,i^i \bmod n=0\\
i^i \bmod n&,{\rm otherwise}\\
\end{cases}
$$

使用扩展欧拉定理，有：

$$
i^i=
\begin{cases}
(i \bmod n) ^ i &,i<\varphi(n)\\
(i \bmod n)^{i \bmod \varphi(n)+\varphi(n)}&,{\rm otherwise}\\

\end{cases}
$$

然后可以发现 $g(i)$ 在 $i\ge \varphi(n)$ 时有循环节，循环节长度 $len = {\rm lcm}(n,\varphi(n))$。

接下来只用分两种情况：

1. $r<\varphi(n)$

枚举所有 $l,r$ 即可，用前缀和求区间和。

此部分复杂度 $O(\varphi(n)^2)=O(k^2)$。

2. $r\ge \varphi(n)$

也先前缀和一下 $S(x)=\sum_{i=1}^x g(i)$。
则 $l,r$ 需满足 $S_r-S_{l-1}=p$。$S_{l-1}$ 显然可以不包含循环节，则 $l<\varphi(n)+len$，而 $S_r$ 可能包含循环节，那么用 $S_r+x\times sum\ ,r<\varphi(n)+len\ ,x\ge 0$ 可以表示所有情况（真实的右界为 $r+x\times len$），其中 $sum$ 为循环节内的和，$sum=S(\varphi(n)+len-1)-S(\varphi(n)-1)$。

问题再次转化：
$$
S_r+x\times sum-S_{l-1}=p\ ,x\ge 0
$$
同余分类：
$$
S_r\equiv p+S_{l-1}{\pmod {sum}}\ ,S_r\le p+S_{l-1}
$$
由于 $S$ 本身单调，就可以用归并排序思想解决 $S_r\le p+S_{l-1}$ 的条件。再用 unordered_map 解决 $S_r\equiv p+S_{l-1}$ 的条件，map 里记录 $r$ 和 $S_r$ 以求答案。

此部分复杂度 $O(\varphi(n)+len)=O(k^2)$。

求 $g(x)$ 用快速幂，单次复杂度 $O(\log k)$。

总复杂度 $O(T(k^2 \log k))$。

代码：
```cpp
#include<cstdio>
#include<algorithm>
#include<unordered_map>
#include<map>
#define long long long
using namespace std;
const int N=1e3+10;
int n,m,phi,al,ar,F[N*N+N];
long per[N*N+N];
int gcd(int a,int b){
	return b?gcd(b,a%b):a;
}
int qpow(int x,int i){
	int res=1;
	for(;i;i>>=1,x=x*x%n)
		if(i&1)res=res*x%n;
	return res;
}
inline int f(int i){
	if(i>=phi)i=qpow(i%n,i%phi+phi);
	else i=qpow(i%n,i);
	return i?i:n;
}
unordered_map<int,int> mp;
int main(){
	int tt;
	scanf("%d",&tt);
	while(tt--){
		scanf("%d%d",&n,&m);n--;
		bool ok=0;phi=1;
		for(int x=n,i=2;i<=x;i++)
			if(x%i==0){
				phi*=i-1;x/=i;
				while(x%i==0){phi*=i;x/=i;}
			}
		for(int i=1;i<phi;i++){
			per[i]=0;F[i]=f(i);
			for(int j=1;j<=i;j++)per[j]+=F[i];
			for(int j=1;j<=i;j++)
				if(per[j]==m){
					printf("%d %d\n",j,i);
					ok=1;break;
				}
			if(ok)break;
		}
		if(ok)continue;
		int k=phi*n/gcd(phi,n),tot=0;
		long S=0,sL=0,sR=0,mL=0,mR=0;
		for(int i=0;i<k;i++)S+=F[phi+i]=f(phi+i);
		for(int i=1;i<=phi;i++)sR+=F[i];
		mR=sR%S;sL=m;mL=sL%S;
		for(int r=phi,l=1;l<phi+k;){
			if(r<phi+k&&sR<=sL){
				per[r]=sR;mp[mR]=r;
				sR+=F[++r];
				if((mR+=F[r])>=S)mR-=S;
			}else{
				if(mp.find(mL)!=mp.end()){
					al=l;ar=mp[mL];
					ar+=(sL-per[ar])/S*k;
					ok=1;break;
				}
				if((mL+=F[l])>=S)mL-=S;
				sL+=F[l++];
			}
		}
		if(ok)printf("%d %d\n",al,ar);
		else printf("-1 -1\n");
		mp.clear();
	}
	return 0;
}
```


---

