# Infinite Sequence (Hard Version)

## 题目描述

这是该问题的困难版本。不同版本的区别在于此版本中 $l \leq r$。仅当您解决了该问题的所有版本时才能进行 hack。

给定一个正整数 $n$ 和一个无限二进制序列 $a$ 的前 $n$ 项，该序列定义如下：

- 对于 $m > n$，$a_m = a_1 \oplus a_2 \oplus \ldots \oplus a_{\lfloor \frac{m}{2} \rfloor}$ $^{\text{∗}}$。

你的任务是计算给定区间 $[l, r]$ 内元素的和：$a_l + a_{l + 1} + \ldots + a_r$。

$^{\text{∗}}$ $\oplus$ 表示[按位异或操作](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)。

## 说明/提示

在第一个测试用例中，序列 $a$ 为：

$$[\underline{\color{red}{1}}, 1, 1, 0, 0, 1, 1, 1, 1, 1, \ldots]$$ 

其中 $l = 1$，$r = 1$。区间 $[1, 1]$ 的元素和为 $a_1 = 1$。

在第二个测试用例中，序列 $a$ 为：

$$ [\text{\color{red}{1}}, \text{\color{red}{0}}, \underline{1}, 1, 1, 0, 0, 1, 1, 0, \ldots] $$

其中 $l = 3$，$r = 10$。区间 $[3, 10]$ 的元素和为

$$ a_3 + a_4 + \ldots + a_{10} = 1 + 1 + 1 + 0 + 0 + 1 + 1 + 0 = 5. $$

翻译由 DeepSeek R1 完成


## 样例 #1

### 输入

```
9
1 1 1
1
2 3 10
1 0
3 5 25
1 1 1
1 234 567
0
5 1111 10000000000
1 0 1 0 1
1 1000000000000000000 1000000000000000000
1
10 41 87
0 1 1 1 1 1 1 1 0 0
12 65 69
1 0 0 0 0 1 0 1 0 1 1 0
13 46 54
0 1 0 1 1 1 1 1 1 0 1 1 1```

### 输出

```
1
5
14
0
6666665925
0
32
3
2```

# 题解

## 作者：未来姚班zyl (赞：6)

先差分转为前缀和。

### D1

由于向下取整对相邻两个数 $2x$ 与 $2x+1$ 是相同的，所以对于 $2x>n$，有 $a_{2x}=a_{2x+1}$。

把 $n$ 补为奇数，设前 $n$ 个 $a_i$ 的异或和为 $P$。我们发现，从 $n$ 之后，$a$ 的组成变为两个两个相同的数顺次相接，它们会在异或和中两两抵消，最终最多剩一个多余的，所以：

对于 $a_m$，设 $d=\lfloor\frac{m}{2}\rfloor$，则：

- $d\le n$，预处理原数组的前缀异或和即可。
- $d>n$，则如果 $d$ 是奇数，$n$ 后面的数在异或和中两两抵消，$a_m=P$；否则在抵消后剩下 $a_d$，$a_m=P\oplus a_d$。

递归即可做到 $O(n+\log V)$。

### D2

差分转前缀和是习惯。

在 D1 的基础上，我们先把前 $2n+1$ 个位置补齐，并处理对应的前缀和与前缀异或和。因为对于大于 $2n+1$ 的位置 $m$，$\lfloor\frac{m}{2}\rfloor>n$，其形式将更加统一。

经过简单的草稿发现，从 $a_{2n+2}$ 开始，数组的形式如下：

$$P\oplus{a_{n+1}},P\oplus {a_{n+1}},P,P,P\oplus{a_{n+3}},P\oplus {a_{n+3}},P,P,\dots$$

即按照 $\bmod 4$ 分组，每组前两个是 $P\oplus a_{x}$，后两个是 $P$，而 $x$ 从第一组开始依次加二。

将 $r$ 调整到一组的末尾，求的就是这些组的前缀和。

于是我们可以将 $a_{2n+1}$ 之前的前缀和预处理，$a_{2n+2}\sim r$ 递归到 $a_{n+1}\sim a_{\lfloor\frac{r}{2}\rfloor-1}$ 中偶数位置的和。

偶数位置前缀和，对于 $i\le 2n+1$，可以预处理前缀和，对于 $i>2n+1$，相当于把两两相等的位置合并，本质求法相同。

总复杂度 $O(n+\log^2 V)$。


```cpp
#include<bits/stdc++.h>
#define ll long long
#define int ll
#define L x<<1
#define R x<<1|1
#define mid ((l+r)>>1)
#define lc L,l,mid
#define rc R,mid+1,r
#define Root 1,1,n
#define OK Ll<=l&&r<=Rr
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define repn(x) rep(x,1,n)
#define repm(x) rep(x,1,m)
#define pb push_back
#define e(x) for(int i=h[x],y=to[i];i;i=nxt[i],y=to[i])
#define E(x) for(auto y:p[x])
#define Pi pair<int,int>
#define ui unsigned ll
inline int read(){int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57)s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
inline void pf(int x){if(x<0) putchar('-'),x=-x;if(x>9)pf(x/10);putchar(x%10+48);}
using namespace std;
const int N=5e5+5,M=1e6+5,inf=(1LL<<30)-1,mod=998244353;
const ll llf=1e18;
inline void add(int &a,int b){((a+=b)>=mod) and (a-=mod);}
inline int Add(int a,int b){return add(a,b),a;}
inline int mul(int a,int b){return 1LL*a*b%mod;}
inline void Mul(int &a,int b){a=mul(a,b);}
inline void red(int &a,int b){add(a,mod-b);}
inline int Red(int a,int b){return red(a,b),a;}
inline int qp(int a,ll b){if(!b)return 1;int c=qp(a,b>>1LL);Mul(c,c);if(b&1)Mul(c,a);return c;}
inline int INV(int x){return qp(x,mod-2);}
int n,l,r,a[N],xr[N],pr[N],P,pe[N];
inline int Get(int x){
	if(x<=n*2+1)return a[x];
	if(x/2<=n*2+1)return xr[x/2];
	if(x/2%2==1)return P;
	return P^Get(x/2);
}
inline int calc(int r){
	if(r<=n*2+1)return pe[r]-pe[n-1];
	int ans=pe[n*2]-pe[n-1];
	while(r%4!=2)r+=2,ans-=Get(r);
	if(P)ans+=(r-n*2)/2,ans-=calc(r/2-1);
	else ans+=calc(r/2-1);
	return ans;
}
inline int Calc(int r){
	if(r<=n*2+1)return pr[r];
	int ans=pr[n*2+1];
	while(r%4!=3)r++,ans-=Get(r);
	int ps=n*2+5,Ct=(r-ps)/4+1;
	if(P)ans+=(r-(n*2+1)),ans-=calc(r/2-1)*2;
	else ans+=calc(r/2-1)*2;
	return ans;
}
inline void Main(){
	n=read(),l=read(),r=read();
	repn(i)a[i]=read(),xr[i]=xr[i-1]^a[i],pr[i]=pr[i-1]+a[i];
	if(n%2==0)n++,a[n]=xr[n/2],pr[n]=pr[n-1]+a[n],xr[n]=xr[n-1]^a[n];
	P=xr[n];
	rep(i,n+1,n*2+1)a[i]=xr[i/2],xr[i]=xr[i-1]^a[i],pr[i]=pr[i-1]+a[i];
	for(int i=2;i<=n*2+1;i+=2)pe[i]=pe[i-2]+a[i];
	cout <<Calc(r)-Calc(l-1)<<'\n';
}
signed main(){
	int T=read();
	while(T--)Main();
	return 0;
}

```

---

## 作者：Grammar_hbw (赞：4)

提供一个不需要讨论边界的做法。

注意到有**结论**：$\forall x > n, 2|x , a_x = a_{x+1}$。（这是因为此时 $\lfloor \dfrac x 2 \rfloor = \lfloor \dfrac {x+1} 2 \rfloor$。）

先将区间 $[l,r]$ 的和转化为 $[1,r]$ 的和减去 $[1,l-1]$ 的和。记求和右端点为 $r$ 。

不妨设 $n \equiv 1 \pmod 2, m = 2n+1$。预处理 $m$ 以内的前缀和、前缀异或和。（如果 $n$ 不是奇数就先补一位。）记 $v=\bigoplus_{i=1}^{n} a_i$。

那么 $m$ 以内的可以直接算；由**结论**和 $a_x$ 的定义可以得到，$m$ 之后的 $a$ 值依次是 $v \oplus a_{n+1},v \oplus a_{n+1},v,v,v \oplus a_{n+3}, \cdots$。你现在可能想直接去算奇数位 $a_n$ 的和，但是这不仅需要处理边界，还需要一些奇怪的东西……

别慌，我们有**结论**！那么 $m$ 之后的 $a$ 值也可以依次是 $v \oplus a_{n+1}, v \oplus a_{n+2}, v, v, v \oplus a_{n+3}, \cdots$ 。那个 $v$ 的异或好说，异或可以直接变成减。根据一些简单的周期分析可以推出来，你只需要求出 $[n+1,n+2 \lfloor \dfrac {r-m-1}4 \rfloor + \min ((r-m-1) \bmod 4 +1,2)]$ 的和，显然可以递归，并注意到每一次端点都会减半，所以我们得到了复杂度 $O(\sum n + T \log V)$ 的做法。

话不多说，现在是 Code Time ~

```
#include <bits/stdc++.h>
using namespace std;
const int N=200007;
typedef long long li;
int a[N*2],x[N*2],s[N*2],n,m; //因为要用到 m=2*n+1 的数，而且因为要补奇数所以 n 最大为 200001，数组开小见祖宗。
li calc(li r){
	if(r<=m) return s[r];
	li ans=calc(n+2ll*((r-m-1)/4)+min((r-m-1)%4+1,2ll))-s[n]; //注意下取整和乘法同级，是从左往右算的。在这里 WA 了一次样例。
	if(x[n]) ans=r-m-ans; //当前 n 个数异或和为 1 时，用区间长度减 ans 才是 [m+1,r] 的和。
	return ans+s[m];
}
int main(){
	cin.tie(0)->sync_with_stdio(0);
	int t;
	cin>>t;
	while(t-->0){
		li l,r; //十年 OI 一场空，不开 long long 见祖宗。
		cin>>n>>l>>r;
		for(int i=1;i<=n;i++) cin>>a[i],x[i]=x[i-1]^a[i],s[i]=s[i-1]+a[i];
		if(!(n&1)) n++,a[n]=x[n/2],x[n]=x[n-1]^a[n],s[n]=s[n-1]+a[n];
		m=2*n+1; //一定要先把 n 补充成奇数之后再考虑 m ！
		for(int i=n+1;i<=m;i++) a[i]=x[i/2],x[i]=x[i-1]^a[i],s[i]=s[i-1]+a[i];
		cout<<calc(r)-calc(l-1)<<'\n'; 
	}
}
```

---

## 作者：reinforest (赞：3)

### 前置结论：

我们用 $\bigoplus$ 表示按位异或运算。

1. 如果 $x=y$，那么 $x \oplus y = 0$。

这个是异或的基本性质，不用证明。

2. 如果 $x$ 是偶数且 $x>n$，那么 $a_x=a_{x+1}$。

因为 $x$ 是偶数，所以 $\lfloor \frac{x}{2} \rfloor = \lfloor \frac{x+1}{2} \rfloor$，因此 $\bigoplus_{i=1}^{\lfloor \frac{x}{2} \rfloor } a_i = \bigoplus_{i=1}^{\lfloor \frac{x+1}{2} \rfloor } a_i$，根据定义可得 $a_x=a_{x+1}$。

3. 在 $n$ 是奇数的前提下，如果 $i$ 是偶数，那么 $\bigoplus_{j=n+1}^{i} a_j = a_i$，反之如果 $i$ 是奇数，那么 $\bigoplus_{j=n+1}^{i} a_j = 0$。

因为 $n$ 是奇数，所以 $a_{n+2k+1}$ 与 $a_{n+2k+2}$（$k$ 是自然数）一定相等（性质2），然后消去（性质1）。如果 $i$ 是偶数，那么最后只会剩下 $a_i$ 没被消去，即原式成立。反之，所有的数都会被消去。



---

### 题解

题目需要求 $ \sum_{i=l}^{r} a_i$ 的值。

我们考虑把区间 $[l,r]$ 拆成 $[1,r]$ 与 $[1,l-1]$ 的差。

所以我们可以把问题转化成 $ \sum_{i=1}^{r} a_i$ 的值。

为了迎合性质3，我们需要首先把 $n$ 补成一个奇数。

现在我们把式子推一下。

$$\begin{aligned}
  \sum_{i=1}^{r} a_i
  &= \sum_{i=1}^{2n+1} a_i + \sum_{i=2n+2}^{r} a_i
  \\&= \sum_{i=1}^{2n+1} a_i + \sum_{i=2n+2}^{r}
\bigoplus_{j=1}^{\lfloor \frac{i}{2} \rfloor}a_j
  \\&= \sum_{i=1}^{2n+1} a_i +\sum_{i=n+1}^{\lfloor \frac{r}{2} \rfloor}
\bigoplus_{j=1}^{i}a_j + \sum_{i=n+1}^{\lfloor \frac{r-1}{2} \rfloor}\bigoplus_{j=1}^{i}a_j
\end{aligned}$$

因为第一项可以预处理，第二项和第三项形式上差不多，所以现在我们把问题转化成计算 $ \sum_{i=n+1}^{k}\bigoplus_{j=1}^{i}a_j $ 的值。

我们继续推式子。

$$\begin{aligned}
  \sum_{i=n+1}^{k}\bigoplus_{j=1}^{i}a_j 
  &= \sum_{i=n+1}^{k}\left(\bigoplus_{j=1}^{n}a_j\right)\bigoplus \left( \bigoplus_{j=n+1}^{i}a_j \right)
  \\&= \sum_{i=n+1}^{k}\left(\bigoplus_{j=1}^{n}a_j\right)\bigoplus \left( \bigoplus_{j=n+1}^{i}a_j \right)
  \\&=  \sum_{i=n+1,2|i}^{k}\left(\bigoplus_{j=1}^{n}a_j\right)\bigoplus a_i + \sum_{i=n+1,2|(i+1)}^{k}\left(\bigoplus_{j=1}^{n}a_j\right)
\end{aligned}$$

因为 $n$ 是奇数，所以 $[n+1,k]$ 中有 $\lfloor \frac{k-n}{2} \rfloor$ 个奇数，我们令 $s=\bigoplus_{j=1}^{n}a_j$，则有以下的式子（这是第一种式子）。

$$\begin{aligned}
  \sum_{i=n+1}^{k}\bigoplus_{j=1}^{i}a_j 
  &= \left(\sum_{i=n+1,2|i}^{k} s \oplus a_i \right)+ \lfloor \frac{k-n}{2} \rfloor \times s
  \\&= 
  \left(\sum_{i=\lfloor \frac{n+1}{2} \rfloor}^{\lfloor \frac{k}{2} \rfloor} s \oplus a_{2i} \right)+ \lfloor \frac{k-n}{2} \rfloor \times s
  \\&=    \left(\sum_{i=\lfloor \frac{n+1}{2} \rfloor}^{n} s \oplus a_{2i} \right) + \left(\sum_{i=n+1}^{\lfloor \frac{k}{2} \rfloor} s \oplus a_{2i} \right)+\lfloor \frac{k-n}{2} \rfloor \times s
    \\&=    \left(\sum_{i=\lfloor \frac{n+1}{2} \rfloor}^{n} s \oplus \left(\bigoplus_{j=1}^{i}a_j \right)\right) + \left(\sum_{i=n+1}^{\lfloor \frac{k}{2} \rfloor} s \oplus \left(\bigoplus_{j=1}^{i}a_j \right)\right)+\lfloor \frac{k-n}{2} \rfloor \times s
\end{aligned}$$

发现第一项在求出 $s$ 的情况下可以 $O(n)$ 求或者预处理，第三项可以 $O(1)$ 求，第二项的形式与我们要求的 $\sum_{i=n+1}^{k}\bigoplus_{j=1}^{i}a_j $ 很像，只是多异或了一个 $s=\bigoplus_{j=1}^{n}a_j$。

我们推一下 $\sum_{i=n+1}^{k}\left(\bigoplus_{j=1}^{n}a_j\right) \bigoplus \left(\bigoplus_{j=1}^{i}a_j\right)$，可得以下的式子（这是第二种式子）。

$$\begin{aligned}
\sum_{i=n+1}^{k}\left(\bigoplus_{j=1}^{n}a_j\right) \bigoplus \left(\bigoplus_{j=1}^{i}a_j\right)
  &= \sum_{i=n+1}^{k}\left(\bigoplus_{j=n+1}^{i}a_j\right)
  \\&= \sum_{i=n+1,2|i}^{k}a_i
  \\&=  \sum_{i=\lfloor \frac{n+1}{2} \rfloor}^{\lfloor \frac{k}{2} \rfloor}  a_{2i}
  \\&= \sum_{i=\lfloor \frac{n+1}{2} \rfloor}^{n}  a_{2i} + \sum_{i=n+1}^{\lfloor \frac{k}{2} \rfloor}  a_{2i}
  \\&= \sum_{i=\lfloor \frac{n+1}{2} \rfloor}^{n}  \bigoplus_{j=1}^{i}a_j + \sum_{i=n+1}^{\lfloor \frac{k}{2} \rfloor}  \bigoplus_{j=1}^{i}a_j
\end{aligned}$$

第一项还是可以 $O(n)$ 求或者预处理，第二项就是我们需要求的 $\sum_{i=n+1}^{k}\bigoplus_{j=1}^{i}a_j $ 的形式！

因为每次都可以把上界从 $k$ 变成 $\lfloor \frac{k}{2} \rfloor$，所以可以递归处理，不会超时。

我们发现，以上两种式子在递归过程中是交替的，我们在递归的过程中可以记录需要执行哪一个式子的结论。

至此我们可以把这道题做完了，但是需要注意一下细节。

刚开始，我们需要先将 $a$ 序列补成奇数，然后计算到 $a_{2n+1}$，还需要计算 $a$ 序列的前缀异或和数组 $X$。这样我们也可以顺便求出来 $s=\bigoplus_{j=1}^{n}a_j$。

在求的时候，我们对于 $i>n$，有 $a_i=X_{\lfloor \frac{i}{2} \rfloor}$。

还有就是，如果刚开始的时候 $k \leq 2n+1$，或者递归的时候 $k \leq 2n$，我们就可以暴力计算了。

其余见代码吧，总时间复杂度 $O(Tn\log n)$，可以通过预处理优化到 $O(T \log n)$，但是没必要。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll n,m,l,r,T,arr[500005],xsum[500005];
ll get_ans(ll k,bool is){
	//is:false:第一种式子,true:第二种式子 
	ll ret=0;
	if(k<=2*n){
		//暴力计算即可 
		for(int i=n+1;i<=k;i++){
			if(is)ret+=(xsum[n]^xsum[i]);
			else ret+=xsum[i];
		}
		return ret;
	}
	//这个循环计算的是第一项 
	for(int i=((n+1)/2);i<=n;i++){
		if(is)ret+=xsum[i];
		else ret+=(xsum[n]^xsum[i]);		
	}
	if(is){
		//第一项+第二项 
		return ret+(get_ans(k/2,!is));
	}else{
		//第一项+第二项+第三项 
		return ret+(get_ans(k/2,!is))+((k-n)/2)*(xsum[n]);
	}
}
ll init(ll k){
	ll ret=0;
	if(k<=2*n+1){
		for(int i=1;i<=k;i++){
			ret+=arr[i];
		}
		return ret;
	}
	//这个循环计算的是第一项 
	for(int i=1;i<=2*n+1;i++){
		ret+=arr[i];
	}
	return ret+get_ans(k/2,0)+get_ans((k-1)/2,0);
	//第一项+第二项+第三项 
}
int main(){
	scanf("%lld",&T);
	while(T--){
		scanf("%lld%lld%lld",&n,&l,&r);
		for(int i=1;i<=n;i++){
			scanf("%lld",&arr[i]);
			xsum[i]=xsum[i-1]^arr[i];
		}
		for(int i=n+1;i<=2*n+3;i++){
		//如果先计算，后补奇数的话，需要至少计算到 a_{2n+3} 
			arr[i]=xsum[i/2];
			xsum[i]=xsum[i-1]^arr[i];
		}
		if(n%2==0)n++;//把n补成奇数		 
		printf("%lld\n",init(r)-init(l-1));		
	}
	return 0;
}
```

---

## 作者：tyr_04 (赞：1)

[传送门](https://www.luogu.com.cn/problem/CF2071D2)

调了三天，不知道我在干啥。

### 题意

给定 $n,l,r,a_{1} \sim a_{n}$，其中 $a_i$ 为 $0$ 或 $1$，对于 $n$ 以后的位置 $j$，满足 $a_j = a_1 \oplus a_2  \ldots  a_{\lfloor \frac{j}{2} \rfloor}$，求 $\displaystyle\sum_{i = l}^{r} a_i$。

### 思路

从 Easy Version 出发，注意到 $n$ 以后的位置 $2x$ 和 $2x + 1$ 是相同的（$x$ 为正整数），因此把 $n$ 补为奇数，方便处理。

因此，对于 $a_{2x}$ 和 $a_{2x + 1}$，$a_{2x} \oplus a_{2x + 1} = 0$，不会对当前位置的值造成影响。也就是说当 $m$ 为偶数时，$a_1 \oplus a_2  \ldots  a_n \oplus a_{n + 1}  \ldots a_{m} = a_1 \oplus a_2  \ldots  a_n \oplus a_{m}$；当 $m$ 为奇数时，$a_1 \oplus a_2  \ldots  a_n \oplus a_{n + 1} \ldots a_{m} = a_1 \oplus a_2  \ldots  a_n$。

考虑递归，容易想到将要求的位置 $x$ 变为 $x_1 = \lfloor \frac{x}{2} \rfloor$ 后，若 $x_1$ 为偶数，继续判断 $x_2 = \lfloor \frac{x_1}{2} \rfloor$，当 $x_i$ 为奇数时返回 $a_1 \oplus a_2 \ldots a_n$，否则 $x_i \le n$ 时返回 $a_1 \oplus a_2 \ldots a_{x_i}$，求出了 $a_{u}$ 再异或 $a_1 \oplus a_2 \ldots a_{n}$ 就可以求出 $a_{2u}$（$u$ 为偶数）。

将求单点的思想推广到区间，假设要求区间为 $a_{i_0} + a_{i_0 + 1} \ldots a_{j_0}$，接着根据第一步所有位置除以 $2$ 向下取整，**必须满足 $i$ 为偶数，$j$ 为奇数**，由于 $\lfloor \frac{2x}{2} \rfloor = \lfloor \frac{2x + 1}{2} \rfloor = x$，设 $i_1 = \frac{i_0}{2},i_2 = \lfloor \frac{i_1 + 1}{2} \rfloor \ldots$ 与 $j_1 = \frac{j_0 - 1}{2},j_2 = \lfloor \frac{j_1}{2} \rfloor \ldots$，原式为 $2 \times (a_{i_1} + a_{i_1 + 1} \ldots a_{j_1})$。根据求单点的方法，可知 $a_{i_{k - 1}} + a_{{i_{k-1} + 1}} \ldots a_{j_{k - 1}} = (a_1 \oplus a_2 \ldots a_n) \times (a_{i_k} + a_{i_k + 1} \ldots a_{j_k}) + (k + 1) \mod 2 \times \frac{j_k - i_k + 1}{2} \times (a_1 \oplus a_2 \ldots a_{n})$（$k \ge 2$，有一半位置为奇数，另一半要除以 $2$，$i_k,j_k$ 相当于第 $k$ 轮后区间的起点和终点。由于 $k + 1$ 轮变换前都要保证 $i_k$ 为偶数，$j_k$ 为奇数，不满足时要单独求 $a_{i_k}$ 或 $a_{j_k}$ 并加入最终答案，如果 $i_k \le n$，则单独处理 $i_k \sim n$ 这个区间，并把 $i_k$ 变为 $n + 1$，当 $i_k > j_k$ 时全部停止），接下来根据 $k$ 的奇偶性分讨再预处理前缀和 $O(1)$ 求出 $a_{i_k} \oplus a_{i_k + 1} \ldots a_{n}$ 就可以啦（$i_k \le n$），如果还不太懂可以看看代码。

预处理 $O(n)$，最多变换 $\log(r)$ 次，最劣时每次都进行特殊处理（即单独求 $a_{i_k},a_{j_k}$ 或 $a_{i_k} \sim a_n$），耗时 $\log(r)$，总时间复杂度 $O(n + \log^2(r))$

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,l,r,ans,gs,a[200005],sum[200005],h[3][200005];
int ask(int x)
{
	int u,cs=0;
	x/=2;
	while(1)
	{
		if(x<=n)
		{
			u=sum[x];
			break;
		}
		else if(x%2==1)
		{
			u=sum[n];
			break;
		}
		x/=2;
		cs++;
	}
	u^=((cs%2)*sum[n]);
	return u;
}
int ts_ask(int x)
{
	int u,cs=0;
	while(1)
	{
		if(x<=n)
		{
			u=sum[x];
			break;
		}
		else if(x%2==1)
		{
			u=sum[n];
			break;
		}
		x/=2;
		cs++;
	}
	u^=((cs%2)*sum[n]);
	return u;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--)
	{
		cin>>n>>l>>r;
		ans=0;
		gs=0;
		sum[0]=0;
		h[0][0]=0;
		h[1][0]=0;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
			sum[i]=sum[i-1]^a[i];
			h[0][i]=h[0][i-1]+sum[i];
			if(i>=l&&i<=r)
			{
				ans+=a[i];
			}
		}
		if(n%2==0)
		{
			n++;
			a[n]=sum[n/2];
			sum[n]=sum[n-1]^a[n];
			h[0][n]=h[0][n-1]+sum[n];
			if(n>=l&&n<=r)
			{
				ans+=a[n];
			}
		}
		for(int i=1;i<=n;i++)
		{
			h[1][i]=h[1][i-1]+(sum[i]^sum[n]);
		}
		if(r<=n)
		{
			cout<<ans<<'\n';
			continue;
		}
		l=max(l,n+1);
		if(r%2==0)
		{
			ans+=ask(r);
			r--;
			if(r<l)
			{
				cout<<ans<<'\n';
				continue;
			}
		}
		if(l%2==1)
		{
			ans+=ask(l);
			l++;
			if(r<l)
			{
				cout<<ans<<'\n';
				continue;
			}
		}
		l/=2;
		r/=2;
		while(r>n)
		{
			if(r%2==0)
			{
				ans+=2*((gs%2*sum[n])^ts_ask(r));
				r--;
				if(r<l)
				{
					break;
				}
			}
			if(l<=n)
			{
				ans+=2*(h[gs%2][n]-h[gs%2][l-1]);
				l=n+1;
			}
			if(l%2==1)
			{
				ans+=2*((gs+1)%2)*sum[n];
				l++;
				if(r<l)
				{
					break;
				}
			}
			ans+=(r-l+1)*((gs+1)%2)*sum[n];
			l/=2;
			r/=2;
			gs++;
		}
		if(l<=r)
		{
			ans+=2*(h[gs%2][r]-h[gs%2][l-1]);
		}
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：yingkeqian9217 (赞：1)

简单题。

注意到对于 $2k>n$，满足 $a_{2k}=a_{2k+1}$，于是考虑异或前缀和，有 $pre_{2k+1}=\bigoplus_{i=1}^{2k+1} a_i= x$，其中 $x$ 可以通过任意计算一项得到。特别的，若 $n$ 为奇数，则 $a_n=x$。

而对于偶数 $pre_{2k}=pre_{2k-1}\oplus pre_k(2k>n)$，第一项为奇数，即为 $x$，第二项每次减半，可以递归计算，于是有复杂度 $O(\log V)$ 求异或前缀和（异或差分可得单项），其中 $V$ 为值域。

但是原题要求的是原序列和，考虑通过 $a_i=pre_{\lfloor\frac{i}{2}\rfloor}(i>n)$ 转化，由于 $a_{2k}=a_{2k+1}$，所以直接算然后乘 $2$ 即可，边界直接通过上述算法暴力补齐算。

考虑异或前缀和的区间求和，首先去除与初始序列有交（包含）的部分，可以通过前缀和快速得到，然后对于奇数项，都恒等于 $x$，直接计算即可。

接下来要求 $\sum_{k=l'}^{r'} pre_{2k}=\sum_{k=l'}^{r'} pre_{k}\oplus x$，当 $x=0$ 时即为 $\sum_{k=l'}^{r'} pre_{k}$；否则为 $r-l+1-\sum_{k=l'}^{r'} pre_{k}$，递归计算即可。

时间复杂度 $O(n+\log V)$。

```cpp
#include<bits/stdc++.h>
#define maxn 2010005
#define int long long
using namespace std;

int n,l,r,sum,a[maxn],pre[maxn];//pre 为原序列加法前缀和 
int query(int pos){//求异或前缀和 
	int cur=0;
	while(pos){
		if(pos<=n) return a[pos]^cur;
		if(pos&1) return sum^cur;
		cur^=sum;
		pos>>=1;
	}
	return 0;
}
int query(int l,int r){//求区间异或前缀和的和 
	int res=0;
	if(r<=n) return pre[r]-pre[l-1];
	if(l<=n) res+=pre[n]-pre[l-1],l=n+1;
	int tmp=(r+1)/2-l/2;
	res+=tmp*sum;
	if(sum) return res+r-l+1-tmp-query(l+1>>1,r>>1);
	return res+query(l+1>>1,r>>1);
}
inline void solve(){
	int res=0;
	scanf("%lld%lld%lld",&n,&l,&r);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
	if(r<=n){
		for(int i=l;i<=r;i++) res+=a[i];
		printf("%lld\n",res);
		return;
	}
	if(l<=n){
		for(int i=l;i<=n;i++) res+=a[i];
		l=n+1;
	}
	for(int i=1;i<=n;i++) pre[i]=pre[i-1]+(a[i]^=a[i-1]);
	if(n&1) sum=a[n];
	else sum=(a[n>>1]^a[n]);//sum 即为上面的 x 
	if(l&1) res+=(query(l)^query(l-1)),l++;
	if(r%2==0) res-=(query(r+1)^query(r)),r++;
	l>>=1,r>>=1;
	printf("%lld\n",(query(l,r)<<1)+res);
}
signed main(){
	signed T=1;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
```

---

## 作者：Yao_yx (赞：0)

这里的 $N$ 为题目中的 $n$。

首先注意到 $a_{2k}=a_{2k+1}$，所以对于easy version可以直接递归，大部分相邻两项均为0，只需特判小于等于 $N$ 的情况以及当前数的奇偶性即可。时间复杂度 $O(T\log N)$。

```cpp
int query(int x){
    if(x <= n) return a[x]; int y = x / 2;
    return (y <= n ? sum[y] : sum[n] ^ (y & 1 ? 0 : query(y)));
}
```

考虑hard version。不妨设 $N$ 为奇数，若为偶数就再添加一项即可。记 $S=\oplus_{i=1}^{N}a_i$，若 $N\leq 2k$，则：

$$\begin{aligned}

a_{4k}+a_{4k+1}&=\oplus_{i=1}^{2k}a_i\\
&=(\oplus_{i=1}^{N}a_i)\oplus(a_{N+1}\oplus a_{N+2})\oplus\dots\oplus(a_{2k-2}\oplus a_{2k-1})\oplus a_{2k}\\
&=S\oplus a_{2k}\\\\

a_{4k+2}+a_{4k+3}&=\oplus_{i=1}^{2k+1}a_i\\
&=(\oplus_{i=1}^{N}a_i)\oplus(a_{N+1}\oplus a_{N+2})\oplus\dots\oplus(a_{2k}\oplus a_{2k+1})\\
&=S\\

\end{aligned}$$

其中 $S$ 可以直接预处理，考虑处理 $S\oplus a_{2k}$：

$$\begin{aligned}
S\oplus a_{2k}&=S\oplus(\oplus_{i=1}^{N}a_i)\oplus(\oplus_{i=N+1}^{2k}a_i)=\oplus_{i=N+1}^{2k}a_i\\
&=\begin{cases}
0,&\text{$2\nmid k$}\\
a_k,&\text{$2\mid k$}
\end{cases}
\end{aligned}$$

将 $k$ 的奇偶性再拆开，其中 $N\leq2k$：

$$\begin{aligned}
\oplus_{i=8k}^{8k+7}a_i&=2(S\oplus a_{4k})+2S+2(S\oplus a_{4k+2})+2S\\
&=4S+2(S\oplus a_{2\times(2k)})+2(S\oplus a_{2\times(2k+1)})\\
&=4S+2a_{2k}\\
&=4S+a_{2k}+a_{2k+1}
\end{aligned}$$

所以对于每连续的8个数，可以缩短为2个数的子问题。所以仍是直接递归，最多递归 $log_4N$ 次，若不在不在一个完整的长度为8的区间内暴力计算即可，显然每次递归最多计算14次。故总时间复杂度 $O(T\log^2N)$。注意边界条件。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int MAXN = 8e5 + 10;
int n, l, r, a[MAXN], sum[MAXN], s[MAXN];

int query(int x){
    if(x <= n) return a[x]; int y = x / 2;
    return (y <= n ? sum[y] : sum[n] ^ (y & 1 ? 0 : query(y)));
}
int query(int l, int r){
	int res = 0;
	if(l > r) return 0;
	if(r <= n * 4) return s[r] - s[l - 1];
	if(l <= n * 4) return s[n * 4] - s[l - 1] + query(n * 4 + 1, r);
	if(r - l <= 6){ for(int i = l; i <= r; ++i) res += query(i); return res; }
	int L = l, R = r;
	if(l % 8 != 0 || r % 8 != 7){
		int x = l; while(x % 8 != 0) res += query(x++);
		int y = r; while(y % 8 != 7) res += query(y--);
		l = x, r = y;
	}
	int x = res + (r - l + 1) / 2 * sum[n] + query(l / 4, r / 4);
	return x;
}

void solve(){
    cin >> n >> l >> r;
    for(int i = 1; i <= n; ++i) cin >> a[i], sum[i] = sum[i - 1] ^ a[i];
    if(!(n & 1)){
        int s = 0; for(int i = 1; i <= (n + 1) / 2; ++i) s ^= a[i];
        a[++n] = s; sum[n] = sum[n - 1] ^ s;
    }
	for(int i = n + 1; i <= n * 4; ++i) sum[i] = sum[i - 1] ^ (a[i] = query(i));
	for(int i = 1; i <= n * 4; ++i) s[i] = s[i - 1] + a[i];
	cout << query(l, r) << '\n';
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    int T; cin >> T; while(T--) solve();

    return 0;
}
```

---

