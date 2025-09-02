# [ARC174E] Existence Counting

## 题目描述

给定整数 $N,K$。现在考虑所有满足以下条件的长度为 $K$ 的数列 $a=(a_1,a_2,\dots,a_K)$：

- $a_i$ 是满足 $1 \le a_i \le N$ 的整数；
- $a$ 的所有元素互不相同。

将所有可能的数列 $a$ 按照字典序排列，得到一个“数列的集合” $s$。

现在给定集合 $s$ 中的一个数列 $P$，对于每个整数 $t=1,2,\dots,N$，请回答以下问题：

- 满足下列所有条件的数列 $b$ 的个数，模 $998244353$ 后的结果是多少？
  - 数列 $b$ 存在于集合 $s$ 中；
  - 数列 $b$ 中包含整数 $t$；
  - 数列 $b$ 的字典序不大于数列 $P$。

关于数列的字典序：数列 $A=(A_1,\ldots,A_{|A|})$ 的字典序**严格小于**数列 $B=(B_1,\ldots,B_{|B|})$，当且仅当满足以下两条之一：
1. $|A| < |B|$ 且 $(A_1,\ldots,A_{|A|}) = (B_1,\ldots,B_{|A|})$；
2. 存在整数 $1 \leq i \leq \min\{|A|,|B|\}$，使得
   - $(A_1,\ldots,A_{i-1}) = (B_1,\ldots,B_{i-1})$；
   - $A_i < B_i$。

## 说明/提示

### 限制条件

- 输入均为整数。
- $1 \le K \le N \le 3 \times 10^5$。
- $P$ 满足题目中的条件。

### 样例解释 1

在本样例中，$N=4,K=2$。此时，集合 $s=((1,2),(1,3),(1,4),(2,1),(2,3),(2,4),(3,1),(3,2),(3,4),(4,1),(4,2),(4,3))$。在集合 $s$ 中，且字典序不大于 $(3,2)$ 的数列中：

- 包含 $1$ 的有 $(1,2),(1,3),(1,4),(2,1),(3,1)$ 共 $5$ 个；
- 包含 $2$ 的有 $(1,2),(2,1),(2,3),(2,4),(3,2)$ 共 $5$ 个；
- 包含 $3$ 的有 $(1,3),(2,3),(3,1),(3,2)$ 共 $4$ 个；
- 包含 $4$ 的有 $(1,4),(2,4)$ 共 $2$ 个。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4 2
3 2```

### 输出

```
5
5
4
2```

## 样例 #2

### 输入

```
18 13
5 13 11 2 18 1 10 15 17 4 12 7 3```

### 输出

```
925879409
905921009
665544804
665544719
783035803
349952762
349952758
349952757
349952757
349921178
212092637
710350150
378895603
129113201
129111892
129098081
129096772
110181652```

# 题解

## 作者：wosile (赞：10)

一个很考验基本功，或者说只考验了基本功的普通题。

首先不考虑必须出现某个数 $t$ 的限制，只计算 $P$ 之前有多少个序列。

和计算排列的时候一样，我们从前往后枚举每个位置 $i$，通过树状数组计算这个位置上能填多少个比现在填的数 $P_i$ 小的数，再乘上后面的填法数。前者可以用树状数组维护前面已经出现的数（因为已经出现过的比 $P_i$ 小的数当然不能在这边选哦），后者就是 $A_{n-i}^{k-i}=\frac{(n-i)!}{(n-k)!}$。（怀念一下小学奥数记号）。

也就是说，$P$ 之前有 $\sum\limits_{i=1}^k\frac{(n-i)!}{(n-k)!}(P_i-1-\sum\limits_{j=1}^i[P_j<P_i])$ 个序列。其中 $[]$ 是 [Iverson 括号](https://baike.baidu.com/item/%E8%89%BE%E4%BD%9B%E6%A3%AE%E6%8B%AC%E5%8F%B7/22361197)。可以用树状数组在 $O(n\log n)$ 的时间内求出。

那么，固定某个数 $t$ 必须出现的序列有多少个呢？

我们发现这不好算，于是反过来考虑 $t$ 不出现的序列有多少个。

这个问题实际上就相当于在序列的值域 $[1,n]$ 中直接去掉了 $t$ 这个数，那不妨直接把值域当成 $[1,n-1]$，然后把所有 $P_i>t$ 减掉 $1$。这样，在 $[1,n-1]$ 中，修改过的 $P$ 之前出现的序列，就和不含 $t$ 的序列一一对应。用上面的式子计数即可。

但是这里有 $n$ 个询问，所以我们从小到大处理每个询问，一开始每个 $P_i$ 都有 $P_i>t$，所以都要减掉 $1$。处理询问的时候每次碰到有 $P_i=t$ 就把 $1$ 加回来就行。体现在答案上就是减去 $\frac{(n-i)!}{(n-k)!}$（这里的 $n$ 代表值域，其实是 $n-1$）。

计算不符合条件的序列数量的时候存在 $P_i=t$ 的情况需要特殊考虑。由于这个 $P_i$ 实际上在值域中并不存在，而是一个比 $[1,t-1]$ 大比 $[t+1,n]$ 小的神秘数，所以 $i$ 后面的所有数都不会造成贡献（因为不存在啊），需要用另一个树状数组维护每个位置 $i$ 造成的贡献然后减掉后面不会造成贡献的一段。另外我们统计的是 $P$ **之前**的序列有多少个含 $t$，所求的范围是包含 $P$ 本身的，所以此时还需要给答案额外 $+1$。

时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k;
int p[300005];
const int mod=998244353;
int ft[300005],invf[300005];
int qp(int x,int y){
	int ans=1;
	while(y){
		if(y&1)ans=1LL*ans*x%mod;
		x=1LL*x*x%mod;
		y>>=1;
	}
	return ans;
}
int f(int x,int y){
	assert(x>=0 && x-y>=0);
	return 1LL*ft[x]*invf[x-y]%mod;
}
int c[300005];
void add(int x){
	assert(x>0);
	for(;x<=n;x+=(x&-x))c[x]++;
}
int query(int x){
	int ans=0;
	assert(x>=0);
	for(;x;x-=(x&-x))ans+=c[x];
	return ans;
}
int q[300005];
int d[300005];
void dadd(int x,int val){
	assert(x>=0);
	for(;x<=k;x+=(x&-x))d[x]=(d[x]+val)%mod;
}
int dquery(int x){
	int ans=0;
	assert(x>=0);
	for(;x;x-=(x&-x))ans=(ans+d[x])%mod;
	return ans;
}
int main(){
	scanf("%d%d",&n,&k);
	ft[0]=1;
	for(int i=1;i<=n;i++)ft[i]=1LL*ft[i-1]*i%mod;
	invf[n]=qp(ft[n],mod-2);
	for(int i=n;i>=1;i--)invf[i-1]=1LL*invf[i]*i%mod;
	for(int i=1;i<=k;i++)scanf("%d",&p[i]);
	for(int i=1;i<=k;i++)q[p[i]]=i;
	int tot=0;
	for(int i=1;i<=k;i++){
		tot=(tot+1LL*(p[i]-1-query(p[i]-1))*f(n-i,k-i))%mod;
		add(p[i]); 
	}
	if(n==k){
		for(int i=1;i<=n;i++)printf("%d\n",tot+1);
		return 0;
	}
	int sub=0;
	for(int i=1;i<=n;i++)c[i]=0;
	for(int i=1;i<=k;i++){
		sub=(sub+1LL*(p[i]-2-query(p[i]-1))*f(n-1-i,k-i))%mod;
		dadd(i,1LL*(p[i]-2-query(p[i]-1))*f(n-1-i,k-i)%mod); 
		add(p[i]);
	} 
	for(int i=1;i<=n;i++){
		// if(q[i]) 成立就说明 p[j]=i 存在。 
		if(q[i])sub=(sub+f(n-1-q[i],k-q[i]))%mod;// p[i] 加上 1 
		int ans=(tot-sub+mod)%mod;
		if(q[i])ans=(ans+dquery(k)-dquery(q[i])+1)%mod;// q[i] 之后不造成贡献 
		if(q[i])dadd(q[i],f(n-1-q[i],k-q[i]));// 维护每个位置的贡献 
		printf("%d\n",(ans+mod)%mod);
	}
	return 0;
	//quod erat demonstrandum
}

```

---

## 作者：Autream (赞：8)

难以置信我考试竟能场切紫题。

### 题意简述

给定整数 $n,k$ 和一个长度为 $k$ 的数组 $A$ 满足以下条件：

- $A_i$ 是一个整数，且 $1 \leq A_i \leq n$。
- $A$ 中的所有元素都是不同的。

对于每个整数 $t=1,2,\dots,n$，求满足下列所有条件的数组 $B$ 的个数，模 $998244353$。
- $B$ 满足 $A$ 的满足的所有条件。
- $B$ 包含整数 $t$。
- $B$ 的字典序小于等于序列 $A$。

---

### 题目分析

显然，满足条件的 $B$ 数组的个数为：**总的能排列的个数 - 不含 $t$ 的排列的个数 - 字典序大于 $A$ 的排列的个数 + 既不含 $t$ 字典序又大于 $A$ 的排列的个数**。

为避免歧义，以下的既带上标又带下标的 $A$ 表示数学中的排列。

其中总的能排列的个数为 $A_n ^k$，不含 $t$ 的排列的个数为 $A_{n-1} ^k$。

重点在于后两项。

#### 如何求字典序大于 $A$ 的排列的个数

考虑什么情况下 $B$ 的字典序**开始**大于 $A$。显然当 $B$ 的某一位比 $A$ 的这一位大时，且这一位前面的与 $A$ 都相同，$B$ **开始**比 $A$ 大。

于是我们可以考虑枚举这个位置 $i$。

对于第 $i$ 位，我们要使这一位比 $A_i$ 大，可以选取的值有 $n-A_i$ 种，由于要保证不重复，实际还需要减去 $i$ 之前已经出现在值域区间 $[A_i+1,n]$ 中的数字个数 $S(A_i+1,n)$，可以使用树状数组实现。

对于 $i$ 后面的，我们还剩 $n-i$ 个数字和 $k-i$ 个位置可以随便填。

排列数为：$\sum \limits ^k _{i=1} [n-A_i-S(A_i+1,n)] \times A_{n-i} ^{k-i}$，这是不变的。

#### 如何求既不含 $t$ 字典序又大于 $A$ 的排列的个数

同上，考虑枚举 $B$ 开始比 $A$ 大的位置 $i$。

对于第 $i$ 位，我们不仅要使这一位比 $A_i$ 大，还要保证不能取到 $t$，可以选取的值有 $n-A_i-[t>A_i]$ 种。

对于 $i$ 后面的，我们还剩 $n-i-1$ 个数字和 $k-i$ 个位置可以随便填。

排列数为：$\sum \limits ^k _{i=1} [n-A_i-S(A_i+1,n)-[t>A_i]] \times A_{n-i-1} ^{k-i}$，答案根据 $t$ 的变大单调递减。

总方案数为：

$$
A_n ^k - A_{n-1} ^k - \sum \limits ^k _{i=1} [n-A_i-S(A_i+1,n)] \times A_{n-i} ^{k-i} + \sum \limits ^k _{i=1} [n-A_i-S(A_i+1,n)-[t>A_i]] \times A_{n-i-1} ^{k-i}
$$

根据以上式子容易得出以下代码（部分），时间复杂度平方级：

```cpp
signed main() {
	n=read(),k=read();
	pre(n+5);
	arrin(a,k);
	rep(i,1,k) lmt=std::max(lmt,a[i]);
	ans=(A(k,n)-A(k,n-1)+MOD)%MOD;
	rep(i,1,k) {
		bit.update(a[i],1); //标记已经出现过
		ans=(ans-(n-a[i]-bit.query(a[i]+1,n))*A(k-i,n-i)%MOD+MOD)%MOD;
		s[i]=bit.query(a[i]+1,n); //优化一个log，避免以后重复计算
	}
	rep(t,1,n) {
		sum=0;
		rep(i,1,k) {
			sum=(sum+(n-a[i]-s[i]-(t>a[i]?1:0))*A(k-i,n-i-1)%MOD)%MOD;
			if(a[i]==t) break; //如果遇到了t等于A中的某个值A[i]，那么在填到第i+1位时，前面必然会出现t，后面不计入贡献
		}
		std::cout<<(ans+sum)%MOD<<"\n";
	}
    return 0;
}
```

### 优化

Tips：主要根据代码写的内容来优化，感性理解即可。

上面的代码显然不够优秀，我们看到 $sum$ 被重复统计了很多次，我们来思考只用计算一次的方法。

考虑先求出 $t=1$ 时的 $sum$，因为此时的 $t$ 无法影响到任何使 $B$ 大于 $A$ 的选择。

在遍历 $t$ 时，如果遇到 $t$ 大于了 $A$ 中的某个值 $A_i$，那么这个数的贡献将会减少 $A_{n-i-1} ^{k-i}$；如果遇到了 $t$ 等于 $A$ 中的某个值 $A_i$，那么在填到第 $i+1$ 位时，前面必然会出现 $t$，贡献减少 $[i+1,n]$ 中所有数的贡献。

由于从小到大枚举 $t$，我们可以把 $A$ 排序以确保遇到的是第一个小于 $t$ 的。

使用树状数组单点修改区间查询即可（没错又是它）。

时间复杂度线性对数。

---

### AC Code

丑陋的赛时代码

```cpp
#include<bits/stdc++.h>
#define arrout(a,n) rep(i,1,n)std::cout<<a[i]<<" "
#define arrin(a,n) rep(i,1,n)a[i]=read()
#define rep(i,x,n) for(int i=x;i<=n;i++)
#define dep(i,x,n) for(int i=x;i>=n;i--)
#define erg(i,x) for(int i=head[x];i;i=e[i].nex)
#define dbg(x) std::cout<<#x<<":"<<x<<" "
#define mem(a,x) memset(a,x,sizeof a)
#define all(x) x.begin(),x.end()
#define arrall(a,n) a+1,a+1+n
#define PII std::pair<int,int>
#define m_p std::make_pair
#define u_b upper_bound
#define l_b lower_bound
#define p_b push_back
#define CD const double
#define CI const int
#define int long long
#define il inline
#define ss second
#define ff first
#define itn int
int read() {
    char ch=getchar();
    int r=0,w=1;
    while(ch<'0'||ch>'9') w=ch=='-'?-1:w,ch=getchar();
    while(ch>='0'&&ch<='9') r=r*10+ch-'0',ch=getchar();
    return r*w;
}
CI N=3e5+5,MOD=998244353;
int n,k,ans,lmt,sum,a[N],s[N],b[N],vis[N],fac[N],inv[N];
struct Binary_Indexed_Tree { //普通的树状数组
	int c[N];
	int lowbit(int x) {return x&(-x);}
	void update(int x,int v) {for(int i=x;i<=n;i+=lowbit(i)) c[i]=(c[i]+v)%MOD;}
	int query(int l,int r) {
		int ans=0;
		for(int i=l-1;i;i-=lowbit(i)) ans=(ans-c[i]+MOD)%MOD;
		for(int i=r;i;i-=lowbit(i)) ans=(ans+c[i])%MOD;
		return ans;
	}
}bit;
int qpow(int a,int b) {
	int ans=1;
	while (b) {
		if (b&1) ans=ans*a%MOD;
		a=a*a%MOD;
		b>>=1;
	}
	return ans;
}
void pre(int n) { //预处理阶乘逆元
	fac[0]=inv[0]=1;
	rep(i,1,n) fac[i]=fac[i-1]*i%MOD;
	inv[n]=qpow(fac[n],MOD-2);
	dep(i,n-1,1) inv[i]=inv[i+1]*(i+1)%MOD;
}
int C(int m,int n) {return fac[n]*inv[m]%MOD*inv[n-m]%MOD;}
int A(int m,int n) {return fac[n]*inv[n-m]%MOD;}
signed main() {
	freopen("sequence.in","r",stdin);
	freopen("sequence.out","w",stdout);
	n=read(),k=read();
	pre(n+5);
	arrin(a,k);
	ans=(A(k,n)-A(k,n-1)+MOD)%MOD;
	rep(i,1,k) {
		bit.update(a[i],1); //标记a[i]出现过
		ans=(ans-(n-a[i]-bit.query(a[i]+1,n))*A(k-i,n-i)%MOD+MOD)%MOD;
		s[i]=bit.query(a[i]+1,n); //优化一个log，避免以后重复计算
	}
	mem(bit.c,0); //重复利用，节省空间
	sum=0; //sum表示既不含t字典序又大于A的排列的个数
	rep(i,1,k) {
		bit.update(i,(n-a[i]-s[i])*A(k-i,n-i-1)%MOD); //将每个数的贡献储存起来
		sum=(sum+(n-a[i]-s[i])*A(k-i,n-i-1)%MOD)%MOD; //初始的和
	}
	rep(i,1,k) vis[a[i]]=i; //标记a[i]的值原本所在的下标，顺便标记a[i]是否存在
	std::sort(arrall(a,k)); //排序以确保遇到的是第一个比t小的
	int idx=1;
	rep(t,1,n) {
		int x=0;
		while(idx<=k&&t>a[idx]) sum=(sum-A(k-vis[a[idx]],n-vis[a[idx]]-1)+MOD)%MOD,bit.update(vis[a[idx]],-A(k-vis[a[idx]],n-vis[a[idx]]-1)),idx++;
		/*
		这里马蜂有点难看
		如果能找到t比a[idx]大的情况
		sum=(sum-A(k-vis[a[idx]],n-vis[a[idx]]-1)+MOD)%MOD 表示减去这个数的一种情况的贡献
		bit.update(vis[a[idx]],-A(k-vis[a[idx]],n-vis[a[idx]]-1)) 表示在树状数组中同步这个更改
		idx++ 表示继续寻找下一个
		*/
		if(vis[t]) { //如果t在A中出现过
			x=bit.query(vis[t]+1,k); //[原本t在a中的下标+1,k]之间所有数的贡献
			sum=(sum-x+MOD)%MOD;
		}
		std::cout<<(ans+sum+MOD)%MOD<<"\n";
		sum=(sum+x+MOD)%MOD; //下一个t就不等于a[i]辣
	}
    return 0;
}
```
[附作者的调试过程，一步一步来可能比较容易看懂。](https://www.luogu.com.cn/paste/0sjm2b4b)

---

## 作者：大眼仔Happy (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/AT_arc174_e)

字典序的限制立刻就想到了类似数位 dp 的东西。

就是钦定前 $i - 1$ 位相同，然后枚举第 $i$ 位比 $P_i$ 小，后面就可以随便填了。

首先剩下还有 $n - i$ 个数，然后还有 $k - i$ 个位置要填。

如果对 $x$ 有贡献，那么 $x$ 必填一个位置，然后其他 $n - i - 1$ 个数填 $k - i - 1$ 个位置。那么就是 $\dbinom{n - i - 1}{k - i - 1}(k - i)!$。然后对于已经确定的前缀的数字，贡献次数为 $\dbinom{n - i}{k - i}(k - i)!$。

确定前缀的时间复杂度是 $O(nk)$ 的，然后统计贡献又要一个 $O(n)$，总时间复杂度 $O(n ^ 2k)$。

---

其实你会发现我们不关系第 $i$ 个数具体是什么，只关心有多少种合法的取值，假设有 $x$ 种。

那么对于前面的 $i - 1$ 个数的贡献就是 $x\dbinom{n - i}{k - i}(k - i)!$。

对于第 $i$ 个位置那合法的 $x$ 种方案中，每个数的贡献都是确定的。

答案为 $\dbinom{n - i}{k - i}(k - i)! + (x - 1)\dbinom{n - i - 1}{k - i - 1}(k - i)!$。

其他非法的数的方案数则为 $x\dbinom{n - i - 1}{k - i - 1}(k - i)!$。

这样时间复杂度就是 $O(nk)$ 的了，但是还不够。

---

我们发现每次计算贡献的时候都对每个数枚举了一遍，这是时间复杂度的瓶颈。

想一下可不可以用个数据结构维护。

首先 $x$ 可以用树状数组维护计算。

对于第一项，因为是确定的数，可以差分解决。

对于后面两个，合法的值在值域上是 $P_i$ 的前缀，非法的则是 $P_i$ 的后缀。

所以维护区间修改，当一个数被确定之后，那么这个数在前面作为未确定的值，也即第二第三项的贡献，就要被取出来，因为这个数后面不会再有第二第三项的贡献。所以同时要单点查询，树状数组维护之。

时间复杂度 $O(k\log n)$。

> 嗯其实是我想不到用什么来表示排列。
>
> 所以用了 $\dbinom{n}{m}m!$ 这种方法。

应该是挺考基础的一个计数题了，但是我没看题解竟然拿下了，说明加训有成果啊。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 3e5 + 5;
#define ll long long
const ll mod = 998244353; 
int inline read() {
	int num = 0, f = 1;
	char ch = getchar();
	while(ch < '0' || ch > '9') {
		if(ch == '-') f = -1;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9') {
		num = (num << 3) + (num << 1) + (ch ^ 48);
		ch = getchar();
	}
	return num * f;
}
int n, k, a[N], c[N], s[N];
void binc(int &x, const int &y) { x += y; if(x >= mod) x -= mod; }
void bdec(int &x, const int &y) { x -= y; if(x < 0) x += mod; }
int inc(const int &x, const int &y) { int res = x + y; if(res >= mod) res -= mod; return res; }
int dec(const int &x, const int &y) { int res = x - y; if(res < 0) res += mod; return res; }
void upd(int *t, int x, int v) { while(x <= n) binc(t[x], v), x += x & -x; }
int ask(int *t, int x) { int res = 0; while(x) binc(res, t[x]), x -= x & -x; return res; }
ll fac[N], ifac[N];
int ans[N], sum[N], vis[N];
ll qp(ll a, ll b) {
	ll res = 1; 
	while(b) {
		if(b & 1) res = res * a % mod; 
		a = a * a % mod, b >>= 1; 
	}
	return res; 
}
ll nCr(ll n, ll r) { return r < 0 || n < r ? 0ll : fac[n] * ifac[r] % mod * ifac[n - r] % mod; }
ll nAr(ll n, ll r) { return r < 0 || n < r ? 0ll : fac[n] * ifac[n - r] % mod; }
int main() {
#ifdef file
	freopen("ARC174E.in", "r", stdin);
	freopen("ARC174E.out", "w", stdout);
#endif
	n = read(), k = read(), fac[0] = 1;
	for(int i = 1; i <= n; ++i) fac[i] = fac[i - 1] * i % mod; 
	ifac[n] = qp(fac[n], mod - 2);
	for(int i = n; i; i--) ifac[i - 1] = ifac[i] * i % mod; 
	for(int i = 1; i <= k; ++i) a[i] = read();
	for(int i = 1; i <= k; ++i) {
		int x = a[i] - 1 - ask(c, a[i] - 1);
		if(x > 0) {
			ll res1 = x * nAr(n - i, k - i) % mod; 
			assert(0 <= res1 && res1 < mod);
			binc(sum[1], res1), bdec(sum[i], res1);
			
			ll res2 = (nAr(n - i, k - i) + 1ll * (x - 1) * (k - i) % mod * nAr(n - i - 1, k - i - 1)) % mod; 
			assert(0 <= res2 && res2 < mod);
			upd(s, 1, res2), upd(s, a[i], dec(0, res2));
			
			ll res3 = 1ll * x * (k - i) % mod * nAr(n - i - 1, k - i - 1) % mod; 
			assert(0 <= res3 && res3 < mod);
			upd(s, a[i], res3);
		}
		upd(c, a[i], 1), binc(ans[a[i]], ask(s, a[i])), vis[a[i]] = 1;
	}
	for(int i = 1; i <= n; ++i) {
		if(vis[i]) binc(ans[i], 1);
		else binc(ans[i], ask(s, i));
	}
	for(int i = 1; i <= k; ++i) binc(sum[i], sum[i - 1]), binc(ans[a[i]], sum[i]);
	for(int i = 1; i <= n; ++i) printf("%d\n", ans[i]);
	return 0;
}
```

---

## 作者：docxjun (赞：4)

发现没有人写容斥所以来把训练记录贴上来。

题面变量有点反人性，设值域为 $m$，数列长度为 $n$。

考虑容斥。对于一个 $t$ 的方案数是：

所有 满足 $B$ 字典序小于等于 $A$ 的方案数 减去 不出现 $t$ 且 $B$ 字典序小于等于 $A$ 的方案数。

先想字典序小怎么做，设 $pre_i$ 是前 $i$ 个数的答案，即 $B_{1, i}$ 的字典序小于等于 $A_{1, i}$。

则当前 $i-1$ 个数满足字典序小于时，第 $i$ 个数可以任意放没填过的数，已经填完了 $[1, i - 1]$ 所以没填过的数有 $m-(i-1)$ 种。

即 $pre[i] = pre[i] + (pre[i - 1] - 1) \times (m - (i - 1))$。

前 $i-1$ 个数刚好和 $A$ 中相等时，第 $i$ 个数需要小于等于 $A_i$。而此时已经填过的不能再填，可以用树状数组维护当前还能填几个数。

具体：树状数组中一开始将 $[1, m]$ 全赋为 $1$，代表这些数还每填，做完 $i$ 就 $add(a[i], -1)$。

当前小于等于 $A_i$ 的未填过的数的数量就是 $query(a[i])$。

综上：$pre[i] = (pre[i - 1] - 1) \times (m - (i - 1)) + query(a[i])$。

容易发现 $pre$ 数组可以压成一个数。

然后暴力时枚举 $t$，统计不出现 $t$ 的方案数。大体和上面相等。

首先树状数组中一开始要把 $t$ 排掉。

然后考虑，当 $A_{1, i - 1}$ 中出现过 $t$，此时的 $pre[i - 1]$ 就代表了字典序小于 $A$ 的方案数，而不是小于等于。

因为等于 $A$ 会出现 $t$，不满足钦定条件。

所以出现过 $t$ 时，$pre[i] = pre[i - 1] \times (m - (i - 1) - 1)$，这里多减一个 $1$ 是把 $t$ 减掉。

未出现过 $t$ 时与之前相同，也要多减一个 $1$。

这个暴力的复杂度是 $O(nm \log m)$。

考虑这个暴力怎么优化。

把每个 $pre$ 弄成一个数，放进线段树中。

对于未在 $A$ 中出现过的每个 $t$，只需要的操作是 $pre = (pre - 1) \times (m - (i - 1)) + query(a[i])$。

加号前面是全体减和全体乘。

注意到：$query(a[i])$ 的值最多只有两种。

对于每一个 $t$，$query(a[i])$ 的变化只是因为树状数组中一开始将 $t$ 除去了。

如果不除去的话：

对于$\forall t \leq A_i$，它加上的是原本的 $query(a[i]) - 1$。

对于$\forall t > A_i$，它加上的是原本的 $query(a[i])$。

于是将每次树状数组中删去 $t$ 的操作变成：

线段树中区间 $[1, a[i]]$ 加 $query(a[i]) - 1$，区间 $[a[i] + 1, m]$ 加 $query(a[i])$。

这样就成功用线段树优化掉了一个 $n$，复杂度变成 $O(n \log m)$，通过此题。

区间乘其实有点难写，考场只剩半个小时自认为是写不完，去打暴力了。

实际订正的时候写错了好几次，有几个地方比较模糊，被回旋镖了。

对于思维不佳的选手，线段树的基础操作应当**非常熟练**，需要反省。

代码：
```C++
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define x first
#define y second
typedef pair<int, int> PP;
typedef double db;
const int N = 6e5 + 5;
const int mod = 998244353;
int n, m, a[N], jc[N], pre[N], tr1[N], ans[N];
struct node {
	int l, r, sum, mul, ad;
}tr[N << 2];
int ksm(int a, int b) {
	int ret = 1;
	while(b) {
		if(b & 1) ret *= a, ret %= mod;
		a *= a, a %= mod;
		b >>= 1;
	}
	return ret % mod;
}
void add(int i, int x) {
	for(; i <= m; i += (i & -i)) tr1[i] += x, tr1[i] %= mod;
} 
int query(int i) {
	int ret = 0;
	for(; i; i -= (i & -i)) ret += tr1[i], ret %= mod;
	return ret;
}
void Base() {for(int i = 1; i <= m; i ++) add(i, 1);}
void clear() {for(int i = 0; i <= m; i ++) tr1[i] = 0;}
void pushup(int p) {
	tr[p].sum = tr[p << 1].sum + tr[p << 1 | 1].sum;
	tr[p].sum %= mod;
}
void pushdown(int p) {
	int k = tr[p].mul; tr[p].mul = 1;
	tr[p << 1].mul *= k, tr[p << 1 | 1].mul *= k, tr[p << 1].mul %= mod, tr[p << 1 | 1].mul %= mod;
	tr[p << 1].ad *= k, tr[p << 1 | 1].ad *= k, tr[p << 1].ad %= mod, tr[p << 1 | 1].ad %= mod;
	tr[p << 1].sum *= k, tr[p << 1 | 1].sum *= k, tr[p << 1].sum %= mod, tr[p << 1 | 1].sum %= mod;
	k = tr[p].ad, tr[p].ad = 0;
	tr[p << 1].sum += k * (tr[p << 1].r - tr[p << 1].l + 1) % mod, tr[p << 1].sum %= mod;
	tr[p << 1 | 1].sum += k * (tr[p << 1 | 1].r - tr[p << 1 | 1].l + 1) % mod, tr[p << 1 | 1].sum %= mod;
	tr[p << 1].ad += k, tr[p << 1 | 1].ad += k, tr[p << 1].ad %= mod, tr[p << 1 | 1].ad %= mod;
}
void build(int l, int r, int p) {
	tr[p].l = l, tr[p].r = r, tr[p].mul = 1, tr[p].ad = 0;
	if(l == r) {
		tr[p].sum = a[1] % mod;
		return;
	}
	int mid = (l + r) >> 1;
	build(l, mid, p << 1), build(mid + 1, r, p << 1 | 1);
	pushup(p);
}
void Add(int p, int l, int r, int x) {
	if(tr[p].l >= l && tr[p].r <= r) {
		tr[p].ad += x, tr[p].ad %= mod;
		tr[p].sum += x * (tr[p].r - tr[p].l + 1), tr[p].sum %= mod;
		pushdown(p);
		return;
	}
	pushdown(p);
	int mid = (tr[p].l + tr[p].r) >> 1;
	if(l <= mid) Add(p << 1, l, r, x);
	if(r > mid) Add(p << 1 | 1, l, r, x);
	pushup(p);
}
void Mul(int p, int l, int r, int x) {
	if(tr[p].l >= l && tr[p].r <= r) {
		tr[p].mul *= x, tr[p].ad *= x; 
		tr[p].mul %= mod, tr[p].ad %= mod; 
		tr[p].sum *= x, tr[p].sum %= mod;
		pushdown(p);
		return;
	}
	pushdown(p);
	int mid = (tr[p].l + tr[p].r) >> 1;
	if(l <= mid) Mul(p << 1, l, r, x);
	if(r > mid) Mul(p << 1 | 1, l, r, x);
	pushup(p);
}
int Query(int p, int i) {
	if(tr[p].l == tr[p].r) {
		return tr[p].sum;
	}	
	pushdown(p);
	int mid = (tr[p].l + tr[p].r) >> 1;
	if(i <= mid) return Query(p << 1, i);
	else return Query(p << 1 | 1, i);
}
signed main() {
	cin >> m >> n, jc[0] = 1;
	for(int i = 1; i <= n; i ++) scanf("%lld", &a[i]);
	for(int i = 1; i <= m; i ++) jc[i] = i * jc[i - 1], jc[i] %= mod;
	int all = a[1]; Base(), add(a[1], -1);
	for(int i = 2; i <= n; i ++) {
		all = (all - 1) * (m - (i - 1)) % mod + query(a[i]);
		all %= mod;
		add(a[i], -1);
	}
	clear();
	build(1, m, 1);
	Add(1, 1, a[1], -1);
	Base(), add(a[1], -1);
	for(int i = 2; i <= n; i ++) {
		ans[a[i - 1]] = all - Query(1, a[i - 1]) * jc[m - i] % mod * ksm(jc[m - n - 1], mod - 2) % mod;
		ans[a[i - 1]] = (ans[a[i - 1]] + mod) % mod;
		Add(1, 1, m, -1);
		Mul(1, 1, m, m - i);
		Add(1, 1, a[i], query(a[i]) - 1);
		if(a[i] < m) Add(1, a[i] + 1, m, query(a[i]));
		add(a[i], -1);
	}
	ans[a[n]] = all - Query(1, a[n]), ans[a[n]] %= mod;
	ans[a[n]] = (ans[a[n]] + mod) % mod;
	for(int i = 1; i <= m; i ++) {
		if(!ans[i]) {
			ans[i] = all - Query(1, i);
			ans[i] = (ans[i] + mod) % mod;
			ans[i] %= mod;
		}
		cout << ans[i] << endl;
	}
	return 0;
}

```

---

## 作者：NATO (赞：4)

一道不错的计数题，赛时没看，赛后自己推了会儿也就会了。

### 思路浅析：

由于题目中要求好序列的所有整数两两不同，那么统计 $x$ 的出现次数即是统计包含 $x$ 的好序列的个数。

考虑先去满足字典序小于等于给定序列这一条件。

对于等于的情况，给给定序列中出现的数答案 $+1$ 即可。

对于小于的情况，我们容易想到枚举与给定序列不相同的第一个位置，显然，只要在该位置放了一个小于对应给定序列位置的数，后面无论怎么放都是合法的，且这样必然是完备的（毕竟一个字典序小于给定序列的序列必然是和给定序列有一个长度 $\ge 0$ 的公共前缀，再在某一个位置小于给定序列的），那么讨论一下当枚举到位置 $i$ 时对每个数答案的贡献：

以下设当前计算贡献的数是 $j$，在位置 $i$ 前没有在给定序列出现且 $<p_i$ 的数的数量为 $s$。

1. 若 $j$ 已经在给定序列的位置 $i$ 之前出现过了。

   考虑到我们只要在 $i$ 放上一个小于对应给定序列位置的数，后面怎么放都必然会计入 $j$ 的答案中，只要不重即可，故可得贡献如下：
   
   $$s(n-i)^{\underline {k-i}}$$
   
   意义即为当前位置必须放一个 $<p_i$ 的数，有 $s$ 种放法，后面 $k-i$ 个位置分别有 $n-i,n-i-1,\dots,n-k+1$ 种放法。
   
2. 若 $j$ 没有在给定序列的位置 $i$ 之前出现且 $<p_i$。

	那么考虑如果没有在位置 $i$ 上放 $j$，而放其它数的贡献如下：
    
    $$(s-1)(k-i)(n-i-1)^{\underline{k-i-1}}$$
    
   意义即为当前位置上可以放的数有 $s-1$ 个数，钦定在后面 $k-i$ 个位置中的某一个放上一个 $j$，剩余 $k-i-1$ 个位置上分别就有 $n-i-1,n-i-2,\dots,n-k+1$ 种放法。 
   
   考虑在位置 $i$ 上放 $j$ 的贡献：
   
   $$(n-i)^{\underline {k-i}}$$
   
   意义即为后面 $k-i$ 个位置分别有 $n-i,n-i-1,\dots,n-k+1$ 种放法（$i$ 这个位置已经放上了 $j$，故不用考虑）。
   
   将上述两个柿子加起来即为对 $j$ 的贡献。
   
3. 若 $j$ 没有在给定序列的位置 $i$ 之前出现且 $\ge p_i$。

	显然 $j$ 只能在 $i$ 后的 $k-i$ 个位置上放，可以轻松地写出贡献柿子如下：
    
   $$s(k-i)(n-i)^{\underline {k-i}}$$
    
   意义即为位置 $i$ 有 $s$ 种放 $<p_i$ 的放法，钦定在后面 $k-i$ 个位置中的某一个放上一个 $j$，剩余 $k-i-1$ 个位置上分别就有 $n-i-1,n-i-2,\dots,n-k+1$ 种放法。
   
至此，我们分类讨论完了位置 $i$ 对于不同类型 $j$ 的贡献，枚举 $i,j$ 即可算出答案。容易发现在预处理下降幂后时间复杂度是 $O(nk)$ 的（外层枚举 $i$，内层枚举 $j$），会得到 [TLE](https://atcoder.jp/contests/arc174/submissions/51467464) 的好成绩。

考虑优化。

$s$ 可以通过一个值域上的单修区查的树状数组轻松算出。

核心问题在于搞掉 $i,j$ 中的一个，然而由于贡献会随着 $i$ 的变化而变化，因此考虑搞掉 $j$。

注意到当 $i$ 固定时对于相同类型的 $j$ 贡献都是相同的。

容易想到后面讨论的两种类型的数可以使用一个线段树或树状数组区间加维护，这是简单的，但是第一种类型的数似乎并不是连续的，而且还要避免区间加的时候加上后面讨论的两种类型的数加上的值，该怎么办呢？

考虑在枚举到 $i'$ 及之前，$i'$ 都是视作后面两种类型算的，而之后都是第一种类型，那么处理完 $i'$ 之后，存下当前线段树或树状数组上 $p_{i'}$ 的值，即为 $i'$ 被视作后面两种类型时的贡献，维护一个第一种类型贡献的后缀和，给 $p_{i'}$ 加上 $i'+1$ 的后缀和即可记上作为第一种类型的贡献。

至此，我们在 $O(n\log n)$ 的时间内解决了本题。

总结一下，虽然本题比较繁琐，但是只要找对了对象，根据对象类型一个一个列出贡献并考虑优化，事实上并不是一道很难的计数题。

#### 参考代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define MOD 998244353
using namespace std;
ll n,k;
ll p[300005],sum[300005],f[300005],inv[300005],where[300005];
ll trx[300005],sfx[300005];
ll lowbit(ll x)
{
	return x&(-x);
}
void upd(ll id,ll val)
{
	for(ll i=id;i<=n;i+=lowbit(i))trx[i]+=val;
}
ll qy(ll id)
{
	ll res=0;
	for(ll i=id;i;i-=lowbit(i))res+=trx[i];
	return res;
}
ll qpow(ll a,ll b)
{
	ll res=1;
	while(b)
	{
		if(b&1)res=res*a%MOD;
		a=a*a%MOD;b>>=1;
	}
	return res;
}
ll tr[1200005];
#define ls(id) id*2
#define rs(id) id*2+1
void update(ll id,ll l,ll r,ll ml,ll mr,ll add)
{
	if(ml>mr)return;
	if(ml<=l&&r<=mr)
	{
		tr[id]=(tr[id]+add)%MOD;return;
	}
	ll mid=l+r>>1;
	if(ml<=mid)update(ls(id),l,mid,ml,mr,add);
	if(mr>mid)update(rs(id),1+mid,r,ml,mr,add);
}
ll query(ll id,ll l,ll r,ll ml)
{
	if(l==r)return tr[id];
	ll mid=l+r>>1;
	if(ml<=mid)return (tr[id]+query(ls(id),l,mid,ml))%MOD;
	return (tr[id]+query(rs(id),1+mid,r,ml))%MOD;
}
ll h=0;
int main()
{
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>k;
	f[0]=1;
	for(ll i=1;i<=n;++i)f[i]=f[i-1]*i%MOD;
	inv[n]=qpow(f[n],MOD-2);
	for(ll i=n-1;i>=0;--i)inv[i]=inv[i+1]*(i+1)%MOD;
	for(ll i=1;i<=k;++i)cin>>p[i],++sum[p[i]],where[p[i]]=i;
	for(ll i=1;i<=k;++i)
	{
		ll sy=p[i]-1-qy(p[i]-1);
		if(sy)
		{
		sfx[i]=sy*f[n-i]%MOD*inv[n-k]%MOD;
		h=(h+sy*f[n-i]%MOD*inv[n-k])%MOD;
		update(1,1,n,1,p[i]-1,((sy-1)*f[n-i-1]%MOD*(k-i)%MOD+f[n-i])%MOD*inv[n-k]%MOD);
		update(1,1,n,p[i],n,sy*f[n-i-1]%MOD*(k-i)%MOD*inv[n-k]%MOD);
		}
		sum[p[i]]=(sum[p[i]]+query(1,1,n,p[i]))%MOD;
		upd(p[i],1);
	}
	for(ll i=k-1;i;--i)sfx[i]=(sfx[i+1]+sfx[i])%MOD;
	for(ll i=1;i<=n;++i)
		if(where[i])
		cout<<(sum[i]+sfx[where[i]+1])%MOD<<'\n';
		else
		cout<<query(1,1,n,i)<<'\n';
}
```

---

## 作者：封禁用户 (赞：3)

考场上有这道题，但是脑瘫只打了 $\mathcal{O}(n k)$ 算法，同校大佬只提一句，让我恍然大悟，遂记之。

## 思路

这个排列计数很基础，要求 $b$ 的字典序小于等于 $a$ 的字典序。考虑比较字典序的过程，有一个枚举前缀 LCP 的想法，稍微简单分讨一下即可。

具体的，考虑当前枚举到 $i$，必须填 $t$，有 $\forall j, j \in [1, i), a_j = b_j$，此时有三种情况。

1. 若 $t$ 出现在前缀中，那么后面怎么填都不会影响，再考虑到每个位置是不同的，所以当前的方案数为 $A_{n - i} ^ {k - i}$。
2. 若 $t \ge a_i$，即当前位置不能填 $t$（需要填其他的，而且不能等于 $a_i$，因为包含在了前缀相等的情况中）所以预留一个位置填 $i$ 其他位置随便填，所以方案有 $(a_i - 1 - cnt_i) \times (k - i - 1) \times A_{n - i - 1} ^ {k - i - 1}$，$cnt_i$ 表示前缀中小于 $a_i$ 的数。
3. 若 $t < a_i$，即当前位置能填 $t$（ps：因为统计了前缀相等的情况，所以此处不需要取等），当前方案有 $A_{n - i} ^ {k - i}$，还有 $i$ 不止可以填在 $i$ 位置，所以还需要加上 $\textcolor{red}{(a_i - cnt_i - 2)} \times (k - i - 1) \times A_{n - i - 1} ^ {k - i - 1}$，注意前面已经算过 $t$ 填在 $i$ 的情况了，所以红色部分要减二。

此时就能 $\mathcal{O}(nk)$ 解决了。

注意到情况二和情况一的贡献不同，所以需要分开维护。这个只需要开一个支持单点修改，区间查询的数据结构，在第 $i$ 个位置记录它的贡献，情况改变时进行修改即可。

至于情况一，因为此时它的贡献已经与 $t$ 没关系了，所以维护后缀和，在查询时加上前半部分的贡献即可实现。

然后就能 $\mathcal{O}(n \log n)$ 求解了。

[$\texttt{Code}$](https://atcoder.jp/contests/arc174/submissions/56741732)

---

## 作者：Phartial (赞：2)

首先考虑字典序小于等于 $P$ 的序列个数 $G(P)$，枚举首个不同处，有

$$
G(P)=1+\sum_{i=1}^K{N-i\choose K-i}(K-i)!(P_i-\sum_{j=1}^i[P_j\le P_i])
$$

不难 $\mathcal{O}(K\log N)$ 计算。

然后考虑做个容斥，把存在 $t$ 容斥成不存在 $t$，设字典序小于等于 $P$ 且不存在 $t$ 的序列个数为 $G(P,t)$，有

$$
G(P,t)=[\nexists i(P_i=t)]+\sum_{i=1}^K[\nexists 1\le j<i(P_j=t)]{N-i-1\choose K-i}(K-i)!(P_i-\sum_{j=1}^i[P_j\le P_i]-[t<P_i])
$$

则 $t=i$ 时的答案即为 $G(P)-G(P,i)$。

根据 $t$ 在 $P$ 里的出现情况分类讨论：

### $t$ 不在 $P$ 中出现

有

$$
\begin{aligned}
  G(P,t)
  &=1+\sum_{i=1}^K{N-i-1\choose K-i}(K-i)!(P_i-\sum_{j=1}^i[P_j\le P_i]-[t<P_i])\\
  &=1+\sum_{i=1}^K{N-i-1\choose K-i}(K-i)!(P_i-\sum_{j=1}^i[P_j\le P_i])-\sum_{i=1}^K{N-i-1\choose K-i}(K-i)![t<P_i]\\
\end{aligned}
$$

前一项可以简单预处理，后一项可以考虑从大到小枚举 $t$，每次可能使 $\le 1$ 个 $[t<P_i]$ 变成 $1$，扫描线即可。

### $t$ 在 $P$ 中出现

设 $t=P_q$，有

$$
\begin{aligned}
  G(P,t)
  &=\sum_{i=1}^q{N-i-1\choose K-i}(K-i)!(P_i-\sum_{j=1}^i[P_j\le P_i]-[t<P_i])\\
  &=\sum_{i=1}^q{N-i-1\choose K-i}(K-i)!(P_i-\sum_{j=1}^i[P_j\le P_i])-\sum_{i=1}^q{N-i-1\choose K-i}(K-i)![t<P_i]\\
\end{aligned}
$$

同样，前一项可以简单预处理，对于后一项，考虑从小到大枚举 $q$，每次在 $P_q$ 的位置插入一个 $\displaystyle{N-q-1\choose K-q}(K-q)!$，查询就是把 $>P_q$ 的数上的值加起来，可以使用线段树维护。

总时间复杂度 $\mathcal{O}(K\log N)$。

```cpp
#include <numeric>
#include <iostream>
#include <atcoder/all>

using namespace std;
using LL = atcoder::modint998244353;

const int kN = 3e5 + 1;

int n, k, p[kN], d[kN];
LL fc[kN], ifc[kN], g, rg[kN], vp[kN], ans[kN];

LL A(int n, int m) { return fc[n] * ifc[n - m]; }
LL Pu(LL x, LL y) { return x + y; }
LL E() { return 0; }

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n >> k;
  for (int i = 1; i <= k; ++i) {
    cin >> p[i];
  }
  fc[0] = 1;
  for (int i = 1; i <= n; ++i) {
    fc[i] = fc[i - 1] * i;
  }
  ifc[n] = fc[n].inv();
  for (int i = n; i >= 1; --i) {
    ifc[i - 1] = ifc[i] * i;
  }
  atcoder::fenwick_tree<int> t(n + 1);
  g = 1;
  for (int i = 1; i <= k; ++i) {
    t.add(p[i], 1);
    g += A(n - i, k - i) * (p[i] - t.sum(1, p[i] + 1));
  }
  if (n == k) {
    for (int i = 1; i <= n; ++i) {
      cout << g.val() << '\n';
    }
    return 0;
  }
  t = decltype(t)(n + 1);
  for (int i = 1; i <= k; ++i) {
    vp[i] = A(n - i - 1, k - i);
  }
  LL _rg = 0;
  for (int i = 1; i <= k; ++i) {
    t.add(p[i], 1);
    _rg += vp[i] * (p[i] - t.sum(1, p[i] + 1));
    rg[i] = _rg;
  }
  iota(d + 1, d + k + 1, 1);
  sort(d + 1, d + k + 1, [](int i, int j) { return p[i] < p[j]; });
  _rg = 0;
  for (int t = n, i = k; t >= 1; --t) {
    if (t == p[d[i]]) {
      _rg += vp[d[i]], --i;
    } else {
      ans[t] = 1 + rg[k] - _rg;
    }
  }
  atcoder::segtree<LL, Pu, E> gt(n + 1);
  for (int i = 1; i <= k; ++i) {
    gt.set(p[i], vp[i]);
    ans[p[i]] = rg[i] - gt.prod(p[i] + 1, n + 1);
  }
  for (int i = 1; i <= n; ++i) {
    cout << (g - ans[i]).val() << '\n';
  }
  return 0;
}
```

---

## 作者：cosf (赞：1)

考虑一下一个字典序小于 $P$ 的性质：一定从某一位之前和 $P$ 一样，一位比 $P$ 小，后面随便。

那么，我们考虑如下模型：有 $n$ 个数，填入长度为 $k$ 的模型，其中第一位只能填其中 $x$ 个数之一。则，这 $x$ 个数被填入的次数是 $(x-2)(k-1)A_{n - 2}^{k - 2} + A_{n - 1}^{k - 1}$，剩下的 $n-x$ 个数被填入的次数是 $(x - 1)(k - 1)A_{n - 2}^{k - 2}$。填法数是 $xA_{n - 1}^{k - 1}$。我们记其中一个数（$i$）出现的次数为 $F_i(n, k, x)$，填法数是 $G(n, k, x)$。这里的 $A_{n}^m = \frac{n!}{(n-m)!}$。

回到原题，对于 $1$ 到 $n$ 中的每个数 $i$，它的次数应该是 $\Big(\sum_{j=1}^{p_{j - 1} \not=i}F_{i}(n - j + 1, k - j + 1, p_j - 1 - u_{p_j - 1})\Big) + \Big(\sum_{l=j + 1, p_j = i}^nG(n - l + 1, k - l + 1, p_l - 1 - u_{p_l - 1})\Big)$。这里的 $u_m$ 表示 $1$ 到 $m$ 中 出现在 $p_1$ 到 $p_{j - 1}$ 的数的个数。

前面一半是它作为后面随便填的数的次数，后面是它作为前面定好位置的填的次数。

注意考虑边界情况，如 $p_j - 1 - u_{p_j - 1} = 0$ 以及最后 $p$ 也算进答案等等。

可以发现，$F_i$ 可以用线段树维护（只需支持区间加和单点查），$G$ 用一个 `int` 存即可，$u$ 用树状数组动态维护。时间复杂度 $O(n\log n)$。

```cpp
#include <iostream>
using namespace std;

#define MAXN 300005
#define MOD 998244353ll
#define lowbit(x) ((x) & -(x))

using ll = long long;

ll pow(ll b, ll p, ll m)
{
    ll r = 1;
    while (p)
    {
        if (p & 1)
        {
            r = r * b % m;
        }
        b = b * b % m;
        p >>= 1;
    }
    return r;
}

int n, k;

int p[MAXN];

ll s[MAXN << 2];

void pushdown(int p)
{
    if (s[p])
    {
        s[p << 1] = (s[p << 1] + s[p]) % MOD;
        s[p << 1 | 1] = (s[p << 1 | 1] + s[p]) % MOD;
        s[p] = 0;
    }
}

void add(int p, int l, int r, int ql, int qr, ll v)
{
    if (ql <= l && r <= qr)
    {
        s[p] = (s[p] + v) % MOD;
        return;
    }
    pushdown(p);
    int mid = (l + r) >> 1;
    if (mid >= ql)
    {
        add(p << 1, l, mid, ql, qr, v);
    }
    if (mid < qr)
    {
        add(p << 1 | 1, mid + 1, r, ql, qr, v);
    }
}

ll query(int p, int l, int r, int q)
{
    if (l == r)
    {
        return s[p];
    }
    pushdown(p);
    int mid = (l + r) >> 1;
    if (mid >= q)
    {
        return query(p << 1, l, mid, q);
    }
    return query(p << 1 | 1, mid + 1, r, q);
}

int t[MAXN];

void addt(int p)
{
    while (p <= n)
    {
        t[p]++;
        p += lowbit(p);
    }
}

int queryt(int p)
{
    int res = 0;
    while (p)
    {
        res += t[p];
        p -= lowbit(p);
    }
    return res;
}

ll res[MAXN];

bool upd[MAXN];

ll cur = 0;

ll fac[MAXN], inf[MAXN];

ll A(ll n, ll m)
{
    return fac[n] * inf[n - m] % MOD;
}

int main()
{
    cin >> n >> k;
    for (int i = 1; i <= k; i++)
    {
        cin >> p[i];
    }
    fac[0] = inf[0] = 1;
    for (int i = 1; i <= n; i++)
    {
        fac[i] = fac[i - 1] * i % MOD;
        inf[i] = pow(fac[i], MOD - 2, MOD);
    }
    for (int i = 1; i <= k; i++)
    {
        if (i < k)
        {
            ll l = p[i] - 1 - queryt(p[i] - 1), r = n - i, m = k - i;
            if (l > 0)
            {
                add(1, 1, n, p[i], n, l * m % MOD * A(r - 1, m - 1) % MOD);
                add(1, 1, n, 1, p[i] - 1, ((l - 1) * m % MOD * A(r - 1, m - 1) % MOD + A(r, m)) % MOD);
            }
            cur = (cur + l * A(r, m) % MOD) % MOD;
            res[p[i]] = (MOD - cur + query(1, 1, n, p[i])) % MOD;
            upd[p[i]] = true;
            addt(p[i]);
        }
        else
        {
            int l = p[i] - queryt(p[i]);
            add(1, 1, n, 1, p[i], 1);
            cur = (cur + l) % MOD;
            res[p[i]] = (MOD - cur + query(1, 1, n, p[i])) % MOD;
            upd[p[i]] = true;
        }
    }
    for (int i = 1; i <= n; i++)
    {
        if (upd[i])
        {
            cout << (res[i] + cur) % MOD << endl;
        }
        else
        {
            cout << query(1, 1, n, i) << endl;
        }
    }
    return 0;
}

```

---

## 作者：huangrenheluogu (赞：1)

不难的计数，但是没有用到容斥。

备注：现在使用 $\dbinom{n}{m}$ 表示 $C_{n}^m$，为了和 $A_{n}^m$ 对应，本题解仍然采用后面的写法。

显然，考虑对小于 $P$ 的计数，最后加一下就好了。

如果是小于 $P$ 的序列，就可以枚举哪里开始不同，这是容易的。我们要做的，就是对第 $i$ 位开始不同的序列统计答案。

考虑前面已经有了 $i-1$ 个数，记 $P_1,\cdots,P_{i-1}$ 没有出现的小于 $P_i$ 的数的个数为 $cnt$，显然第 $i$ 为只有 $cnt$ 种方案。剩下的可以随便排，就是 $A_{m-i}^{n-i}$ 种方案。我们可以得到总共的方案总数，在这些方案中，$P_1,\cdots,P_{i-1}$ 都出现了一遍，这个计数可以放到序列上，结束序列扫描之后再说。可以后缀和 $O(n)$ 解决，但是其他地方带了 $\log$，我写法上这里也带了 $\log$。

显然，在这个位置，前面没有出现的数可以分成两个集合，$S$ 集合和 $L$ 集合。$S$ 集合表示前面没有出现的数比 $P_i$ 小的，就是可以放在第 $i$ 为的，$L$ 表示比 $P_i$ 大的，不能放在这一位的。显然，这两个集合在这个位置的每个数字出现次数是相同的。

为了表述方便，记 $cal$ 表示第 $i$ 位选定之后的一个数 $x$ 必须在 $i+1$ 到 $k$ 位中的方案。显然是选择其他的数，然后排列即可，$cal=C_{n-i-1}^{k-i-1}\cdot (n-i)!$。

考虑 $S$ 集合每一个数字出现的次数。如果放在第 $i$ 位，后面是随便选的，就是 $A_{n-i}^{k-i}$ 种。如果不放在第 $i$ 位，那么第 $i$ 位剩余 $|S|-1$ 种可能，$i+1\sim n$ 位就是前面计算过的 $cal$。

考虑 $T$ 集合的方案数，类似的可以得到 $|S|\cdot cal$。

因为修改的对象是不在 $i$ 前面的数，可以先存到树状数组里，然后枚举到一个数统计一下答案。如果不在 $P$ 里的数可以最后统计。

这里就只用 $3$ 个树状数组就好了。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 3e5 + 5, mod = 998244353;
int n, m, a[N], ans[N], fac[N], ifac[N], tem, tmp1, tmp2, cnt, tmp;
bool vis[N];
inline int pls(int x, int y){
    x += y;
    if(x >= mod) x -= mod;
    return x;
}
struct BIT{
    int c[N];
    inline int lowbit(int x){
        return x & -x;
    }
    inline void add(int x, int val){
        while(x <= m){
            c[x] = pls(c[x], val);
            x += lowbit(x);
        }
    }
    inline int get(int x){
        int res = 0;
        while(x){
            res = pls(res, c[x]);
            x -= lowbit(x);
        }
        return res;
    }
    inline int query(int x, int y){
        return pls(get(y), mod - get(x - 1));
    }
    inline void modify(int l, int r, int val){
        add(l, val);
        add(r + 1, mod - val);
    }
}T, T1, T2;
inline int ksm(int x, int y){
    int res = 1;
    while(y){
        if(y & 1) res = 1ll * res * x % mod;
        x = 1ll * x * x % mod, y >>= 1;
    }
    return res;
}
inline void init(){
    fac[0] = 1;
    for(int i = 1; i <= m; i++) fac[i] = 1ll * fac[i - 1] * i % mod;
    ifac[m] = ksm(fac[m], mod - 2);
    for(int i = m - 1; ~i; i--) ifac[i] = 1ll * ifac[i + 1] * (i + 1) % mod;
}
inline int A(int x, int y){
    assert(x >= y);
    if(x <= 0) return 0;
    return 1ll * fac[x] * ifac[x - y] % mod;
}
inline int C(int x, int y){
    if(x < 0 || y < 0) return 0;
    assert(x >= y);
    return 1ll * fac[x] * ifac[y] % mod * ifac[x - y] % mod;
}
signed main(){
    // freopen("data.in", "r", stdin);
    // freopen("code.out", "w", stdout);
    scanf("%d%d", &m, &n);
    init();
    for(int i = 1; i <= n; i++){
        scanf("%d", &a[i]);
        ans[a[i]] = 1;
    }
    for(int i = 1; i <= m; i++) T.add(i, 1);
    for(int i = 1; i <= n; i++){
        cnt = T.query(1, a[i] - 1);
        if(cnt == 0){
            ans[a[i]] = pls(ans[a[i]], T2.get(a[i]));
            vis[a[i]] = 1;
            T.add(a[i], -1);
            continue ;
        }
        tem = 1ll * cnt * A(m - i, n - i) % mod;
        tmp = 1ll * C(m - i - 1, n - i - 1) * A(n - i, n - i) % mod;
        tmp2 = 1ll * tmp * cnt % mod;
        tmp1 = pls(1ll * tmp * (cnt - 1) % mod, A(m - i, n - i));
        T1.modify(1, i - 1, tem);
        T2.modify(1, a[i] - 1, tmp1);
        T2.modify(a[i], m, tmp2);
        ans[a[i]] = pls(ans[a[i]], T2.get(a[i]));
        vis[a[i]] = 1;
        T.add(a[i], -1);
        // printf("i = %d, cnt = %d, tem = %d, tmp = %d, tmp1 = %d, tmp2 = %d\n", i, cnt, tem, tmp, tmp1, tmp2);
    }
    for(int i = 1; i <= m; i++){
        if(vis[i]) continue ;
        ans[i] = pls(ans[i], T2.get(i));
    }
    for(int i = 1; i <= n; i++){
        ans[a[i]] = pls(ans[a[i]], T1.get(i));
    }
    for(int i = 1; i <= m; i++){
        printf("%d\n", ans[i]);
    }
    return 0;
}
```

---

## 作者：123456xwd (赞：1)

考虑枚举一下 $t$，然后枚举一下 $i$ 是第一个 $b_i<a_i$ 的地方，称其为关键点（前面 $i-1$ 个数就确定了）考虑计数。

若 $t$ 在 $i$ 前面出现了，方案为 $(a_i-1-p_i)\tbinom{n-i}{k-i}(k-i)!$，其中 $p_i$ 表示 $i$ 前面比 $a_i$ 小的数的个数。

否则，则先计算 $t$ 填写在 $i$ 后面的方案：$(a_i-1-p_i-[t<a_i])\tbinom{n-i-1}{k-i-1}(k-i)!$，并且若 $t$ 可以填在第 $i$ 个位置，则有 $\tbinom{n-i}{k-i}(k-i)!$。

考虑如何优化，瓶颈在这个枚举 $t$ 上，先考虑 $t=a_i$ 的情况。

我们发现，对于关键点在 $i$ 之后的情况，其实就是一段后缀，可以直接预处理出来。

考虑前面的，设当前关键点为 $a_j(j\le i)$，若 $t<a_j$，则其的贡献为 $(k-j)!\tbinom{n-j}{k-j}+(a_j-2-p_j)\tbinom{n-j-1}{k-j-1}(k-j)!$，也就是说对于 $t\in[1,a_j)$，他的贡献就是这些。

反之则为 $(a_j-1-p_j)\tbinom{n-j-1}{k-j-1}(k-j)!$，用一个树状数组即可维护。

最后我们更新一下 $t=a_j$ 的答案即可。

对于不在 $a$ 内的 $t$，我们最后统计一下答案即可。

不要忘了相等的情况。

```c++
#include<bits/stdc++.h>
#define int long long
#define p_b push_back
#define m_p make_pair
#define pii pair<int,int>
#define fi first
#define se second
#define ls k<<1
#define rs k<<1|1
#define mid ((l+r)>>1)
#define gcd __gcd
#define lowbit(x) (x&(-x))
using namespace std;
int rd(){
	int x=0,f=1; char ch=getchar();
	for(;ch<'0'||ch>'9';ch=getchar())if (ch=='-') f=-1;
	for(;ch>='0'&&ch<='9';ch=getchar())x=(x<<1)+(x<<3)+(ch^48);
	return x*f;
}
const int N=3e5+5,INF=0x3f3f3f3f3f3f3f3f,mod=998244353;
int jc[N+5],jc_inv[N+5];	
int ksm(int a,int b){
	int ans=1;
	while(b){
		if(b&1) ans=ans*a%mod;
		a=a*a%mod;b>>=1;
	}
	return ans;
}
void init(){
	jc[0]=1;
	for(int i=1;i<=N;i++) jc[i]=jc[i-1]*i%mod;
	jc_inv[N]=ksm(jc[N],mod-2);
	for(int i=N;i>=1;i--) jc_inv[i-1]=jc_inv[i]*i%mod;
}
int C(int n,int m){
	if(m>n) return 0;
	return jc[n]*jc_inv[m]%mod*jc_inv[n-m]%mod;
}

int n,k;
int a[N];
void add(int &x,int y){
	x+=y;
	if(x>mod) x-=mod;
}
struct BIT{
	int c[N];
	void update(int x,int y){
		while(x<=n) add(c[x],y),x+=lowbit(x);
	}
	int query(int x){
		int ans=0;
		while(x) add(ans,c[x]),x-=lowbit(x);
		return ans;
	}
	void clean(){
		for(int i=1;i<=n;i++)c[i]=0;
	}
}T;
int p[N],sum[N],ans[N];
bool vis[N];
signed main(){
	init();
	n=rd(),k=rd();
	for(int i=1;i<=k;i++) a[i]=rd();
	for(int i=1;i<=k;i++){
		p[i]=T.query(a[i]-1);
		T.update(a[i],1);
		vis[a[i]]=1;
	}
	T.clean();
	for(int i=1;i<=k;i++){
		sum[i]=(a[i]-1-p[i])*C(n-i,k-i)%mod*jc[k-i]%mod;
		int tmp=jc[k-i]*C(n-i,k-i)%mod+(a[i]-2-p[i])*C(n-i-1,k-i-1)%mod*jc[k-i]%mod;
		tmp%=mod;
		T.update(1,tmp),T.update(a[i],mod-tmp);
		tmp=(a[i]-1-p[i])*C(n-i-1,k-i-1)%mod*jc[k-i]%mod;
		T.update(a[i],tmp);
		ans[a[i]]=T.query(a[i]);
	}
	for(int i=k;i>=0;i--) add(sum[i],sum[i+1]);
	for(int i=1;i<=k;i++) add(ans[a[i]],(sum[i+1]+1)%mod); 
	for(int i=1;i<=n;i++) if(!vis[i]) ans[i]=T.query(i);
	for(int i=1;i<=n;i++) printf("%lld\n",(ans[i]%mod+mod)%mod);
	return 0;
}
```

---

## 作者：gcx114514 (赞：0)

首先考虑对于一个元素 $x$ 统计答案：所有序列减不包含 $x$ 的序列减字典序大于 $P$ 的序列加字典序大于 $P$ 且不包含 $x$ 的序列。

对于前两项的和是：$A_{n}^k-A_{n-1}^k$。

第三项考虑枚举从那个数开始大于 $P$ 的，答案为：$\sum\limits_{i=1}^k (n-p_i-sum(a_i+1,n))\times A_{n-i}^{k-i}$。

其中 $sum(l,r)$ 表示枚举到当前位置时 $p$ 在 $[l,r]$ 中的个数。

问题在于求第四项，对于一个特定的 $x$，其方案数为（令 $pos_x$ 表示 $x$ 在序列 $P$ 中的出现位置，若未出现则为 $k+1$）：
$$
\sum_{i=1}^{pos_x-1}(n-p_i-sum(p_i+1,n)-[x>p_i])\times A_{n-i-1}^{k-i}
$$
这个可以用 BIT 维护，先跑一边找出所有答案，因为后面的 $[x>p_i]$ 将序列划分成两部分，两个区间加即可。

时间复杂度 $O(n\log n)$。

[Code](https://atcoder.jp/contests/arc174/submissions/66223703)

---

## 作者：鲤鱼江 (赞：0)

基本功题，比较简单。

先想到 $O(nk)$ 暴力是逐位确定，每次枚举填什么，然后是一个后缀加状物。

具体地，我们构造一个排列 $d_{1\dots n}$，使得 $d_{1\dots k}=P$，因为 $P$ 是好的所以一定可以构造。

现在我们做类似数位 DP 的方式，从前到后确定每一位，假设现在确定到了第 $i$ 位：

若当前填的数 $j<P_i$：

则此时字典序的限制已经消失了，那么 $d_{i+1\dots n}$ 的数除了 $j$ 之外都可以填在后面，也就相当于后缀除了 $j$ 之外加 $(k-i)A_{n-i-1}^{k-i-1}$，令 $j$ 的出现次数加 $A_{n-i}^{k-i}$。

若当前填的数 $j=P_i$：

则只让 $j$ 加一下后 $k-i$ 位字典序小于等于 $P$ 的方案数，这个明显可以树状数组 DP 一下求出来，然后继续向后计算。

明显是 $O(nk)$ 的，考虑如何优化，发现第二种情况本来就不是瓶颈，问题在于第一种情况。

可以变成后缀加 $(k-i)A_{n-i-1}^{k-i-1}$，到时候给 $j$ 加上 $A_{n-i}^{k-i}-(k-i)A_{n-i-1}^{k-i-1}$。

分两部分统计：

1. 对于排列 $d$ 的后缀加，这个可以做到 $O(n\log n)$，因为要求出有多少数可以填。
2. 给在 $d$ 中出现在 $d_i$ 之后且值小于 $P_i$ 的地方加，这个是一个二维偏序，一样是 $O(n\log n)$ 的。

总时间 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>

using namespace std;

const int N=3e5+10;
const int mod=998244353;
struct modint {
    int val;
    static int norm(const int& x) { return x < 0 ? x + mod : x; }
    static constexpr int get_mod() { return mod; }
    modint inv() const {
        int a = val, b = mod, u = 1, v = 0, t;
        while (b > 0) t = a / b, swap(a -= t * b, b), swap(u -= t * v, v);
        return modint(u);
    }
    modint() : val(0) {}
    modint(const int& m) : val(norm(m)) {}
    modint(const long long& m) : val(norm(m % mod)) {}
    modint operator-() const { return modint(norm(-val)); }
    modint& operator+=(const modint& o) { return val = (1ll * val + o.val) % mod, *this; }
    modint& operator-=(const modint& o) { return val = norm(1ll * val - o.val), *this; }
    modint& operator*=(const modint& o) { return val = static_cast<int>(1ll * val * o.val % mod), *this; }
    modint operator-(const modint& o) const { return modint(*this) -= o; }
    modint operator+(const modint& o) const { return modint(*this) += o; }
    modint operator*(const modint& o) const { return modint(*this) *= o; }
	friend std::ostream& operator<<(std::ostream& os, const modint a) { return os << a.val; }
}res[N],sum[N],dp[N];

template < typename T >
struct TreeArray{
	int len;vector < T > tr;
	inline void init(int _n){len=_n;tr.resize(len+10);}
	inline int lowbit(const int &x){return x&(-x);}
	inline void add(int i,const T &x){++i;if(!len) cout<<"ERROR\n";for(;i<=len;i+=lowbit(i)) tr[i]+=x;}
	inline T ask(int i){T res=0;++i;if(!len) cout<<"ERROR\n";for(;i;i-=lowbit(i)) res+=tr[i];return res;}
};
template < int Max >
struct Choose{
	modint frac[Max+10],inv[Max+10];
	Choose(){
		frac[0]=inv[0]=1;for(int i=1;i<=Max;++i) frac[i]=frac[i-1]*i;
		inv[Max]=frac[Max].inv();for(int i=Max-1;i;--i) inv[i]=inv[i+1]*(i+1);
	}
	modint operator ()(const int x,const int y){return x<y||y<0?0:frac[x]*inv[x-y];}
};
TreeArray < modint > t;//第二贡献 
TreeArray < int > s;//还有多少个数没有出现过 
Choose < N > P;
int n,k,len,p[N],d[N],fg[N];

int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>k;for(int i=1;i<=k;++i) cin>>p[i],fg[d[i]=p[i]]=1;
	len=k;for(int i=1;i<=n;++i) if(!fg[i]) d[++len]=i;
	s.init(n+10);t.init(n+10);dp[k+1]=1;
	for(int i=1;i<=k;++i) s.add(p[i],1);
	for(int i=k;i;--i){
		dp[i]=P(n-i,k-i)*(p[i]-s.ask(p[i]))+dp[i+1];
		s.add(p[i],-1);
	}
//	for(int i=1;i<=k;++i) cout<<dp[i]<<' ';
//	cout<<endl;
	for(int i=1;i<=n;++i){
		//后缀加
		sum[i]+=P(n-i-1,k-i-1)*(k-i)*(d[i]-1-s.ask(d[i]-1));
		res[d[i]]+=t.ask(n)-t.ask(d[i]);
		res[d[i]]+=dp[i+1];
		s.add(p[i],1);t.add(d[i],P(n-i,k-i)-P(n-i-1,k-i-1)*(k-i));
	}
	for(int i=1;i<=n;++i) res[d[i]]+=(sum[i]+=sum[i-1]);
	for(int i=1;i<=n;++i) cout<<res[i]<<'\n';
	return 0;
}
```

---

## 作者：WaterM (赞：0)

记限制序列为 $a$，排列数为 $A_n^m$。

对于字典序的限制，我们一位一位填，考虑第一次与 $a$ 出现不同的是哪一位。

具体地，我们从 $1$ 到 $k$ 枚举 $i$，要填的数 $v$ 只有两种可能：
1. $v = a_i$。
2. $v < a_i$ 且 $v$ 未在 $a_1, a_2, \cdots ,a_{i-1}$ 中出现过。

对于 case 1，我们记 $suf_i$ 表示前 $i-1$ 位与 $a_i$ 填得一样，第 $i$ 位开始不做限制（只要互不相同），填出的序列字典序小于等于 $a$ 的方案数。  
记 $num_i$ 为前 $i$ 位，小于 $a_i$ 但之前未选的数的个数，树状数组轻松处理。  
若第 $i$ 位填得一样，那么贡献为 $ suf_{i+1}$。若第 $i$ 位填得小，那么后面随便填，贡献为 $num_i \times A_{n-i}^{k-i}$。故 $suf_i = suf_{i+1} + num_i \times A_{n-i}^{k-i}$。

那么 case 1 的情况即是：$ans_{a_i} \gets ans_{a_i} + suf_{i+1}$，其他数的贡献不用算。


再看 case 2。这时因为已经有当前填的数 $v<a_i$ 了，故后面随便填。既然随便填，就要把所有数的贡献全部算算。  
对于当前一个未选的数 $x$：
- 若 $x < a_i$，分为第 $i$ 位填 $x$ 和第 $i$ 位不填 $x$ 两种情况。  
第 $i$ 位填 $x$，就是第 $i$ 位定死，后面随便填；否则，第 $i$ 位填除了 $x$，有 $num_i - 1$ 种选择，后面随便填。至于 $k-i$ 因子，是枚举 $x$ 放哪。  
有 $ans_x \gets ans_x + 1 \times A_{n-i}^{k-i} + (num_i - 1) \times (k-i) \times A_{n-i-1}^{k-i-1}$。
- 若 $x \ge a_i$，那第 $i$ 位有 $num_i$ 种选择，后面随便填。  
有 $ans_x \gets ans_x + num_i \times (k-i) \times A_{n-i-1}^{k-i-1}$。

问题来了，如何快速处理这一串更新呢？  
注意到他们实际上都是区间加，用树状数组区间修改，最后单点查询。  
那如何将已选的数刨掉贡献呢？
我们增加一个【锁定】操作，在每次 case 1 的时候就会有一个数已选，在这时候将 $ans$ 确定下来，之后不接受树状数组的单点查询，也就刨掉了之后的贡献操作。
最后，将没有【锁定】的数的答案设为树状数组单点查询的结果即可。

时间复杂度 $O(k \log n)$。

[submission.](https://atcoder.jp/contests/arc174/submissions/63370790)

---

## 作者：happybob (赞：0)

题意：

给出 $N,K$ 和序列 $P_{1\dots k}$。

称一个序列是好的，当且仅当满足以下所有条件：

+ 长度为 $K$。

+ 所有整数范围为 $[1,N]$。

+ 所有整数两两不同。

保证 $P$ 是好的。

对于每个数 $x\in [1,K]$，求字典序 $\le P$ 的所有好序列中 $x$ 的出现次数，答案对 $998244353$ 取模。

$1\le K\le N\le 3\times 10^5$。

解法：

很简单的题。

考虑枚举序列和 $P$ 的 LCP，然后考虑下贡献可以发现每部分都只需要简单地维护树状数组就能求出。具体来说，考虑前缀每个数的答案都会增加某个值，如果某个数 $x$ 出现在后面，对 $x \geq P_{i+1}$ 和 $x< P_{i+1}$ 分类讨论即可。

总复杂度 $O(n \log n)$。

[Submission Link.](https://atcoder.jp/contests/arc174/submissions/60689769)

---

## 作者：spire001 (赞：0)

## ARC174E 题解

第一次自己独立切掉 Atcoder *2300，写篇题解纪念一下！！！

假定你已经读懂了题目意思，下面直接提供本题解法。

### 解题思路

题目要求的限制很简单，只有字符串的字典序的偏序关系。

这让人联想到数位 DP，数位 DP 的思路是固定前缀，通过比较最高的前缀大小来表示出所有数字。

本题可以使用类似的思路。

考虑字符串 $S\le T$，除去最简单的 $S=T$，则必然存在一对相等的前缀 $S'=T'$。
则我们可以通过考虑枚举每一个 $i$ 满足 $\{s_1, s_2, s_3, \dots, s_{i - 1}\} = \{t_1, t_2, t_3, \dots, t_{i - 1}\}$ 的情况来不重不漏的计数。

下面计算对于每个 $i$，可能的序列对答案的贡献。

对于一个 $x\in \{u|u\neq p_j,j<i\}$，有以下两种情况。

若满足 $x < p_i$ 那么你可以在 $i$ 处放置 $x$，剩下的地方放任自流，亦可以放在 $i$ 位置后的 $k - i$ 个位置中，然后再挑选一个 $y < p_i$ 放在 $i$ 位置，剩下依旧放任自流。
若满足 $x \ge p_i$ 那么考虑剩下的数中选择一个数 $y<p_i$，放在 $i$ 位置，$x$ 放在后 $k - i$ 个位置，剩下的放任自流。

我恰好写了一个暴力可以参考。
注意部分排列组合数是排列数而不是组合数。

```cpp
vector<int> cur(k);
for (int i = 1; i <= k; i++)
{
  LL wnow = 0;
  LL w1 = P(n - i, k - i);
  int tot = 0;
  for (int j = 1; j < p[i]; j++)
    tot += !box[j];
  LL w2 = (k - i) * P(n - i - 1, k - i - 1) % mod;
  for (int j = 1; j <= n; j++)
  {
    if (box[j])
      continue;
    LL& res = ans[j];
    if (j < p[i])
      ad(res, w1 + w2 * (tot - 1));
    else 
      ad(res, w2 * tot);
  }
  box[p[i]] = 1;
  for (auto th : cur)
    ad(ans[th], P(n - i, k - i) * tot);
  cur.emplace_back(p[i]);
}
```

考虑优化。

首先注意到对已经钦定的点的答案增加成后缀关系，只要快速求出值小于 $p_i$ 的未被钦定的数量配合前缀和即可。

单点加，求前缀个数，树状数组足够用了。

对于剩下的点的贡献，可以看做每次操作打一个标记，打标记后的数不再对答案贡献，否则依与 $p_i$ 的大小关系对答案贡献。

可这么做显然麻烦了。

只需在加入 $p_i$ 这个点的时候查询，求出其答案，后面不再维护这个值即可。

操作是区间加，单点查询，借助差分树状数组足够用了。

最后发现题目限制条件的偏序关系是不大于而非小于，故需考虑 $\{p\}$ 对答案的贡献，这道题就做完了。

### 完整代码
```cpp
#include <algorithm>
#include <cassert>
#include <cstring>
#include <iostream>
#include <numeric>
#include <vector>
#define lowbit(x) (x & -(x))


using namespace std;

typedef long long LL;
constexpr int mod = 998244353;
template <typename Tp1, typename Tp2>
inline void cmax(Tp1& A, const Tp2& B)
{
  if (A < B)
    A = B;
  return;
}
template <typename Tp1, typename Tp2>
inline void cmin(Tp1& A, const Tp2& B)
{
  if (A > B)
    A = B;
  return;
}
template <typename Tp1, typename Tp2, int mod = ::mod>
inline void ad(Tp1& A, const Tp2& B)
{
  A = (A + B) % mod;
  return;
}
template <typename Tp1, typename Tp2, int mod = ::mod>
inline void sb(Tp1& A, const Tp2& B)
{
  A = (A + mod - B) % mod;
  return;
}

constexpr int N = 300010;
int n, k;
int p[N];
LL ans[N], jc[N], jcinv[N];

inline LL quick_pow(LL base, LL ind)
{
  LL res = 1;
  base %= mod;
  for (; ind; ind >>= 1)
  {
    if (ind & 1ll)
    {
      res = res * base % mod;
    }
    base = base * base % mod;
  }
  return res;
}
inline LL _div(LL x, LL y)
{
  return x * quick_pow(y, mod - 2) % mod;
}
inline LL C(const int x, const int y)
{
  return x < y ? 0 : jc[x] * jcinv[y] % mod * jcinv[x - y] % mod;
}
inline LL P(const int x, const int y)
{
  if (x < 0 || y < 0) return 0;
  return x < y ? 0 : jc[x] * jcinv[x - y] % mod;
}

void pre() // 预处理阶乘
{
  jc[0] = jcinv[0] = 1;
  for (int i = 1; i != N; i++)
    jc[i] = jc[i - 1] * i % mod;
  jcinv[N - 1] = quick_pow(jc[N - 1], mod - 2);
  for (int i = N - 2; i >= 1; i--)
    jcinv[i] = jcinv[i + 1] * (i + 1) % mod;
  return;
}

bool box[N];
LL stm[N], sum[N];

LL c[N];
int as[N];

inline void add(const int x, const int val) { for (int i = x; i <= n; i += lowbit(i)) c[i] += val; return; }
inline LL ask(const int x) { LL res = 0; for (int i = x; i; i &= i - 1) res += c[i]; return res; }

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  pre();

  cin >> n >> k;

  for (int i = 1; i <= k; i++)
    cin >> p[i];
  for (int i = 1; i <= n; i++)
    add(i, 1); 

  vector<int> cur(k);

  for (int i = 1; i <= k; i++)
  {
    int tot = ask(p[i] - 1); // 查询小于 p[i] 的数的个数
    as[i] = tot;
    stm[i] = (stm[i - 1] + P(n - i, k - i) * tot) % mod; // 前缀和
    add(p[i], -1);
  }
  for (int i = 1; i <= k; i++)
    ans[p[i]] = stm[k] - stm[i]; // 对答案的贡献是后缀

  memset(c, 0, sizeof c); // 清空树状数组

  for (int i = 1; i <= k; i++)
  {
    LL w1 = P(n - i, k - i); // x < p[i] 特有的贡献
    int tot = as[i];
    LL w2 = (LL)(k - i) * P(n - i - 1, k - i - 1) % mod;
    LL A = (w1 + w2 * (tot - 1)) % mod;
    LL B = w2 * tot % mod;
    add(1, A); // 差分，区间加
    add(p[i], (B + mod - A) % mod);
    ad(ans[p[i]], ask(p[i])); // 贡献答案，可看做删除这个点
    box[p[i]] = 1;
  }

  for (int i = 1; i <= k; i++) // { p } 对答案的贡献
    ans[p[i]]++;
  
  for (int i = 1; i <= n; i++)
    if (!box[i]) // 剩下的点没有标记，在最后查询即可
      ans[i] = ask(i) % mod;

  for (int i = 1; i <= n; i++)
    cout << ans[i] << '\n';
  
  return 0;
}
```

---

## 作者：_Yonder_ (赞：0)

这题可能对巨佬们来说很简单，但对我这种计数蒟蒻来说却有着一定的价值。

先考虑一个 $x$ 怎么做。

对于一定要包含 $x$ 这个条件，在排列问题中一般是比较难算的，反过来求不包含的话就相当于考虑这个数不存在，这是好算的。那么答案为：总的排列数 - 不含 $x$ 的排列数 - 字典序大于 $P$ 的排列数 + 不含 $x$ 且字典序大于 $P$ 的排列数。

前两个显然为 $A^k_n-A^k_{n-1}$，重点考虑后两个。

以下内容中，令 $Q(i,x)$ 表示 ${\footnotesize\displaystyle\sum^n_{i=1}}[P_i\ge x]$。

字典序大于 $P$ 的排列数：我们考虑枚举每一位，计算从这一位开始大于 $P$ 的字典序的序列个数，为 ${\footnotesize\displaystyle\sum^k_{i=1}}(n-P_i-Q(i,P_i+1))\times A^{k-i}_{n-i}$。

不含 $x$ 且字典序大于 $P$ 的排列数：假设 $x$ 不存在即可，贡献为 ${\footnotesize\displaystyle\sum^k_{i=1}}(n-P_i-Q(i,P_i+1)-[x>P_i])\times A^{k-i}_{n-i-1}$。观察这个式子可以发现，除了 $x>P_i$ 比较难搞，其他的都很简单。我们考虑从 $1\sim n$ 枚举 $x$，当某个 $x>P_i$ 成立时，找到 $i$ 并修改即可。
# Code

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=3e5+5,mod=998244353;
struct BIT{
	ll tr[N];
	inline void clear(){memset(tr,0,sizeof(tr));}
	inline int ask(int x,ll ans=0){while(x) ans+=tr[x],x-=x&-x;return ans%mod;}
	inline void add(int x,int d){while(x<N) tr[x]+=d,x+=x&-x;}
}T;
int n,k,p[N],fac[N],inv[N],ans,val[N],sum,ind[N];
inline int quickpow(int a,int b,int ans=1){while(b){if(b&1) ans=1ll*ans*a%mod;b>>=1;a=1ll*a*a%mod;}return ans;}
inline int A(int m,int n){return 1ll*fac[n]*inv[n-m]%mod;}
inline void upd(int i){if(i) T.add(i,mod-A(n-i,k-i-1));}
int main(){
	std::ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>k>>n;fac[0]=inv[0]=1;
	for(int i=1;i<=k;i++) fac[i]=1ll*fac[i-1]*i%mod;
	inv[k]=quickpow(fac[k],mod-2);
	for(int i=k-1;i;i--) inv[i]=1ll*inv[i+1]*(i+1)%mod;
	for(int i=1;i<=n;i++) cin>>p[i],ind[p[i]]=i;
	ans=(A(n,k)-A(n,k-1)+mod)%mod;
	for(int i=1;i<=n;i++) val[i]=k-p[i]-i+1+T.ask(p[i]),T.add(p[i],1);
	for(int i=1;i<=n;i++) ans=(ans-1ll*val[i]*A(n-i,k-i)%mod+mod)%mod;
	T.clear();
	for(int i=1;i<=n;i++) T.add(i,1ll*val[i]*A(n-i,k-i-1)%mod);
	for(int i=1;i<=k;i++){
		upd(ind[i-1]);
		cout<<(ans+T.ask(ind[i]?ind[i]:n))%mod<<endl;
	}
	return 0;
}
```

---

## 作者：WrongAnswer_90 (赞：0)

# [My Blogs](https://www.cnblogs.com/WrongAnswer90/p/18384272)

### [[ARC174E] Existence Counting](https://www.luogu.com.cn/problem/AT_arc174_e)

比较机械的处理方式。和 NOID2T2 是一个性质，只不过简单多了。

枚举生成序列和 $P$ 的第一个不同位置 $i$，则第 $i$ 个位置能填的数的个数 $g_i$ 是 $<a_i$ 并且之前没有出现过的数，$g_i$ 可以简单用树状数组求出。

然后考虑如何统计答案。对于 LCP 中所有数的贡献：首先有了 $g_i$，设 $ans_i$ 表示第 $i$ 个位置开始字典序小于 $P$ 的序列的方案数，则 $ans_i=g_i(m-i)^{\underline{n-i}}$。

然后对于一个 $j$，他作为前缀，则所有 $i>j$ 的 $ans_i$ 都对它有贡献。求出 $ans$ 之后做一遍后缀和统计这部分的答案。

在 $i$ 后面出现的答案。直接的想法是分为第 $i$ 个位置和后面 $n-i$ 个位置两种情况分别统计。第一种情况是对所有 $<p_i$ 并且在前面没有出现过的数字有贡献，对偶一下，对于一个 $p_i$，会对他造成贡献的是 $j<i$ 并且 $p_j>p_i$ 的数，这样可以用树状数组维护单点加，后缀和。

但是第二种情况，在 $j<p_i$ 时，贡献是 $(g_i-1)(m-i-1)^{\underline{n-i-1}}$，但是 $j\geq p_i$ 时贡献是 $g_i(m-i-1)^{\underline{n-i-1}}$。可以看成全局没有出现过的 $+g_i(m-i-1)^{\underline{n-i-1}}$，然后 $j<p_i$ 的减去 $(m-i-1)^{\underline{n-i-1}}$，减去的这部分可以和上面第一种情况共用一个树状数组维护后缀和即可。总复杂度 $\mathcal O(n\log n)$。

```cpp
int n,m,a[300010],f[300010],fr[300010],inv[300010],ans[300010];
inline int C(int n,int m){return m<0||m>n?0:Cmul(fr[n],inv[m],inv[n-m]);}
struct BIT
{
	int t[300010];
	inline void add(int x,int y=1){for(;x<=m;x+=x&-x)Madd(t[x],y);}
	inline int ask(int x){int s=0;for(;x;x-=x&-x)Madd(s,t[x]);return s;}
}T1,T2;
bool vis[300010];
inline void mian()
{
	read(m,n),f[n+1]=fr[0]=inv[0]=1;int lst,tmp=0;
	for(int i=1;i<=m;++i)fr[i]=Cmul(fr[i-1],i);
	inv[m]=power(fr[m],MOD-2);
	for(int i=m-1;i>0;--i)inv[i]=Cmul(inv[i+1],i+1);
	for(int i=1;i<=n;++i)read(a[i]);
	for(int i=1;i<=n;++i)
	{
		T1.add(a[i]),lst=a[i]-1-T1.ask(a[i]-1),f[i]=Cmul(lst,C(m-i,n-i),fr[n-i]);
		Madd(tmp,Cmul(lst,C(m-i-1,n-i-1),fr[n-i]));
		T2.add(m-a[i]+2,Cdel(Cmul(C(m-i,n-i),fr[n-i]),Cmul(C(m-i-1,n-i-1),fr[n-i])));
		Madd(ans[a[i]],T2.ask(m-a[i]+1),tmp);
		vis[a[i]]=1;
	}
	for(int i=1;i<=m;++i)if(!vis[i])Madd(ans[i],T2.ask(m-i+1),tmp);
	for(int i=n;i>=1;--i)Madd(f[i],f[i+1]),Madd(ans[a[i]],f[i+1]);
	for(int i=1;i<=m;++i)write(ans[i],'\n');
}
```

---

## 作者：Wu_Qi_Tengteng (赞：0)

没有 $t$ 限制的很好想。

相当于是枚举第一个不同的是哪一个，就是 $\sum_{i=1}^k\frac{(n-i)!}{(n-k)!}(A_i-1-\sum_{j=1}^i[A_j<A_i])$。

注意了注意了，后面 $\sum_{j=1}^i[A_j<A_i]$ 可以用树状数组优化掉。

有了 $t$ 咋算？不好算，可行的方法是直接通过一些分类讨论搞，但是这个东西的时间复杂度是 $\mathcal{O}(n^2)$，且不好优化。(其实有人搞出来了)。

直接反过来考虑不包含 $t$ 的合法序列有多少个。那么能选则的数 ```n--```，后面的式子 $A_i-1-\sum_{j=1}^i[A_j<A_i]$ 当 $A_i>t$ 时多 $-1$。

前面部分 $\frac{(n-i)!}{(n-k)!}$ 不管 $t$ 怎么变，都是一样的；而后面部分，只有当 $t$ 变大的时候大于他的数才会变少。

所以我们从小到大枚举 $t$，每次加上小于等于他的但是大于上一个数的数。由于我们是 $1$\~$n$ 枚举，其实只有当 $i$ 这个数出现在原序列中才会减少。

注意，当 $t$ 出现在 $A$ 中的时候，那么在 $A_i=t$ 之后的位置贡献的方案都是不合法的。所以我们会多减，就要加上这些方案。并且我们还要 $+1$，因为总共还算一个。

值得注意的是，我们每个位置的贡献是一直在变化的，因为不断有数变成小于的。所以我们需要一个支持单点修改和区间查询的数据结构，显然树状数组。时间复杂度 $\mathcal{O}(n\log n)$。
```c++
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define R register 
const int N=3e5+10;
const int mod=998244353;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f*=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return x*f;
}
inline int ksm(int a,int b){
	int ans=1;
	while(b){
		if(b&1)ans=ans*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return ans;
} 
int fac[N],inv[N];
inline void pre(){
	fac[0]=1;
	for(int i=1;i<=N-10;i++)fac[i]=fac[i-1]*i%mod;
	inv[N-10]=ksm(fac[N-10],mod-2);
	for(int i=N-11;i>=0;i--)inv[i]=inv[i+1]*(i+1)%mod;
}
inline int A(int n,int m){
	if(m>n)return 0;
	if(n<0||m<0)return 0;
	return fac[n]*inv[n-m]%mod;	
}
int n,k; 
int a[N],q[N];
int c[N],d[N];
inline int lowbit(int x){
	return x&(-x); 
}
inline void add(int x){
	for(R int i=x;i<=n;i+=lowbit(i))c[i]++;
}
inline int sum(int x){
	int ans=0;
	for(R int i=x;i>0;i-=lowbit(i))ans+=c[i];
	return ans;
}
inline void dadd(int x,int y){
	for(R int i=x;i<=n;i+=lowbit(i))d[i]=(d[i]+y)%mod;
}
inline int dsum(int x){
	int ans=0;
	for(R int i=x;i>0;i-=lowbit(i))ans=(ans+d[i])%mod;
	return ans;
}
signed main(){
	pre(); 
	n=read();k=read();
	for(R int i=1;i<=k;i++){
		a[i]=read();
		q[a[i]]=i;
	}
	int tot=0,sub=0;
	for(R int i=1;i<=k;i++){
		int cnt=sum(a[i]-1);
		tot=(tot+A(n-i,k-i)*(a[i]-1-cnt)%mod)%mod;
		sub=(sub+A(n-i-1,k-i)*(a[i]-2-cnt)%mod)%mod;
		dadd(i,A(n-i-1,k-i)*(a[i]-2-cnt)%mod);
		add(a[i]);
	}
	for(R int i=1;i<=n;i++){
		 if(q[i])sub=(sub+A(n-q[i]-1,k-q[i]))%mod;
		 int ans=(tot-sub+mod)%mod;
		 if(q[i])ans=(ans+dsum(k)-dsum(q[i])+mod+1)%mod;
		 if(q[i])dadd(q[i],A(n-q[i]-1,k-q[i]));
		 printf("%lld\n",(ans+mod)%mod);
	} 
	return 0;
}
```

---

