# Tyler and Strings

## 题目描述

While looking at the kitchen fridge, the little boy Tyler noticed magnets with symbols, that can be aligned into a string $ s $ .

Tyler likes strings, and especially those that are lexicographically smaller than another string, $ t $ . After playing with magnets on the fridge, he is wondering, how many distinct strings can be composed out of letters of string $ s $ by rearranging them, so that the resulting string is lexicographically smaller than the string $ t $ ? Tyler is too young, so he can't answer this question. The alphabet Tyler uses is very large, so for your convenience he has already replaced the same letters in $ s $ and $ t $ to the same integers, keeping that different letters have been replaced to different integers.

We call a string $ x $ lexicographically smaller than a string $ y $ if one of the followings conditions is fulfilled:

- There exists such position of symbol $ m $ that is presented in both strings, so that before $ m $ -th symbol the strings are equal, and the $ m $ -th symbol of string $ x $ is smaller than $ m $ -th symbol of string $ y $ .
- String $ x $ is the prefix of string $ y $ and $ x \neq y $ .

Because the answer can be too large, print it modulo $ 998\,244\,353 $ .

## 说明/提示

In the first example, the strings we are interested in are $ [1\, 2\, 2] $ and $ [2\, 1\, 2] $ . The string $ [2\, 2\, 1] $ is lexicographically larger than the string $ [2\, 1\, 2\, 1] $ , so we don't count it.

In the second example, all strings count except $ [4\, 3\, 2\, 1] $ , so the answer is $ 4! - 1 = 23 $ .

In the third example, only the string $ [1\, 1\, 1\, 2] $ counts.

## 样例 #1

### 输入

```
3 4
1 2 2
2 1 2 1```

### 输出

```
2```

## 样例 #2

### 输入

```
4 4
1 2 3 4
4 3 2 1```

### 输出

```
23```

## 样例 #3

### 输入

```
4 3
1 1 1 2
1 1 2```

### 输出

```
1```

# 题解

## 作者：include_BM (赞：7)

题意：给定两个“字符串” $s,t$，问将 $s$ 中的“字符”重新排列后有多少种字典序小于 $t$。

设 $a_i$ 表示 $s$ 中 $i$ 个数。

考虑现在在第 $i$ 位，且前 $i-1$ 位 $s,t$ 相同，那么对于这一位有两种情况：

1. 放一个 $<t_i$ 的字符，那么第 $i+1$ 到 $n$ 位放任意字符都满足条件，枚举这一位放什么，又因相同字符间无序，方案数为：

$$\dfrac{\sum_{j<t_i}a_j\times(n-i)!}{\prod a_i!}$$

2. 放一个 $=t_i$ 的字符，这种情况的方案数会在 $i+1$ 处被计算，所以将 $a[t_i]\leftarrow a[t_i]-1$，继续判断下一位。

```cpp
const int N=1e6+10,P=998244353;
int n,m,a[N],b[N],sum[N],fac[N],ans,mul=1;
//用树状数组维护 a[i] 的和，mul 为当前所有 a[i] 的阶乘的乘积。

void chg(int x,int k){for(;x<=1e6;x+=x&-x) sum[x]+=k;}
int que(int x){int res=0;for(;x;x-=x&-x)res+=sum[x];return res;}

inline ll ksm(ll a,ll k){
	ll ans=1;
	for(;k;a=(a*a)%P,k>>=1)
		if(k&1) ans=(ans*a)%P;
	return ans;
}

signed main(){
	for(int i=(fac[0]=1);i<N;++i) fac[i]=(fac[i-1]*i)%P;
	n=read(),m=read();
	for(int i=1;i<=n;++i) a[i]=read(),chg(a[i],1);
	for(int i=1;i<=m;++i) b[i]=read();
	for(int i=1;i<=1e6;++i) mul=(mul*fac[que(i)-que(i-1)])%P;
	for(int i=1;i<=n+1;++i){
		if(i>n){
			if(n<m) ans=(ans+1)%P;//说明s与t前n位相同且s比t短，那么s字典序小于t，算一种情况。
			break;
		}
		if(i>m) break;//t比s短，剩下的位置可以放任何数，这种情况已经在 i-1 处被计算，故剩下的位置不用再考虑了。
		ans+=(que(b[i]-1)*fac[n-i])%P*ksm(mul,P-2)%P,ans%=P;
		if(que(b[i])-que(b[i]-1)){
			mul=(mul*ksm(que(b[i])-que(b[i]-1),P-2))%P;//a[b[i]] 变为 a[b[i]]-1，则 a[b[i]]! 变为 a[b[i]]!/a[b[i]]。
			chg(b[i],-1);
		}
		else break;
	}
	printf("%lld",ans);
    return 0;
}
```

---

## 作者：enucai (赞：4)

## Preface

纪念一下蒟蒻第一次在 div2 考场上做出 E，虽然是道万分简单的题。

以下称 $s$ 为 数组 $a$，$t$ 为 数组 $b$。

## Analysis

很套路的题目。考虑要将 $b$ 重排以使 $b$ 的字典序小于 $a$。那么对 $b$ 逐位处理：$b_i<a_i$ **或** $b_i=a_i$ 并继续向后。

接下来的难点在于如何统计这一位选定后后面的排序方法。

对于任意的长度为 $n$ 数组 $s$，若数字 $i$ 出现的次数为 $x_i$，我们知道她的排列方法是 $\frac{n!}{\prod x_i}=\frac{n!}{x_1!\times x_2!\times \dots\times x_i!\times \dots\times x_k!}$。

如果删除一个数 $i$，那么种类数变成了$=\frac{(n-1)!}{x_1!\times x_2!\times \dots\times (x_i-1)!\times \dots\times x_k!}$，正好是原来的 $\frac{x_i}{n}$。

所以，如果这一位要选小于 $b_i$，种类数就是 $\frac{sum}{n}$。其中，$sum$ 表示小于 $b_i$ 的数的个数。用树状数组维护前缀和即可。

具体细节处理详见代码。

**Tip.** 注意取模，考场上没取模吃了一次罚时。

## Code

**Talk is cheap, show me the code.**

[Codeforces Status](https://codeforces.com/contest/1648/submission/149089242)

```cpp
// And in that light, I find deliverance.
#define int long long
int n,m,N,a[200010],b[200010];
int fac[200010],ifac[200010];
int cnt[200010];
bool ok[200010];
int c[200010];
int qry(int x){
	int res=0;
	while(x) res+=c[x],x-=x&(-x);
	return res;
}
void upd(int x,int val){
	while(x<=200000) c[x]+=val,x+=x&(-x);
}
int now;
signed main(){
	read(n,m);N=max(n,m);
	fac[0]=1;
	int ninv=minv(n);
	For(i,1,N) fac[i]=fac[i-1]*i%mod;
	ifac[N]=minv(fac[N]);
	Rof(i,N-1,0) ifac[i]=ifac[i+1]*(i+1)%mod;
	For(i,1,n) read(a[i]);
	For(i,1,m) read(b[i]);
	For(i,1,n) cnt[a[i]]++;
	now=fac[n];
	For(i,1,n) if(!ok[a[i]]){
		now=now*ifac[cnt[a[i]]]%mod;
		upd(a[i],cnt[a[i]]);
		ok[a[i]]=1;
	}
	int ans=0;
	For(i,1,n){
		if(i>m)	break;
		ans+=now*qry(b[i]-1)%mod*ninv%mod;
		ans%=mod;
		int thi=qry(b[i])-qry(b[i]-1);
		if(thi==0) break;
		upd(b[i],-1);
		now=now*thi%mod*minv(qry(200000))%mod;
		if(i==n&&n<m) ans++;
	}
	cout<<ans%mod<<endl;
}
```

---

## 作者：Alarm5854 (赞：3)

## 题意
给定两个字符串 $s,t$，计算 $s$ 有多少种排列方式满足 $s$ 的字典序小于 $t$。两种排列方式 $a,b$ 不同，当且仅当 $a$ 与 $b$ 中至少存在一位不同。
## 解法
首先要根据 $n$ 与 $m$ 的关系分为两类：$n<m$ 与 $n\ge m$，两者的区别在于第一类中 $s$ 可以是 $t$ 的前缀。

然后用类似于数位 `dp` 的方法，对于每一位 $i$，讨论 $s_i<t_i$ 还是 $s_i=t_i$。若 $s_i<t_i$，则 $s_i$ 之后的每一位都可以随便排，贡献为：
$$
\sum_{x<s_i}\prod_{j\le mx}\frac{(n-i)!}{(c_j-[j=x])!}
$$
其中 $mx$ 为 $s$ 和 $t$ 中最大的数。

现在，难点在于维护
$$
\prod_{j\le mx}(c_j-[j=x])!
$$
毕竟上面的东西可以整体除。

考虑将 $(n-i)!$ 提取出来，则式子变为
$$
(n-i)!\times(\sum_{x<s_i}\prod_{j\le mx}\frac{1}{(c_j-[j=x])!})
$$
令 $h_j=\dfrac{1}{c_j!}$，则要求的就是
$$
(n-i)!\times\sum_{x<s_i}(c_x\times\prod_{j\le mx}h_j)
$$
进一步，转化为
$$
(n-i)!\times(\sum_{x<s_i}c_x)
\times(\prod_{j\le mx}h_j)
$$
这样，这个式子就容易维护了，可以用同一个全局变量维护第一项和第三项，而第二项可以用一个树状数组维护，每次累加完这个贡献以后就将 $c_{s_i}$ 减一即可，时间复杂度为 $O(n\log w)$，$w$ 即为上述的 $mx$。

注意一些细节：如果 $t_i$ 已经被用完了，代表不可能取等，直接跳出循环即可。若 $n<m$，则最后一个位置对答案加一时要记得取模！赛时有一车人因此 FST。
```cpp
#include<ctime>
#include<cctype>
#include<cstdio>
#define ll long long
using namespace std;
const int N=2e5+7;
const ll p=998244353;
ll read(){
	char c;
	ll x=0,f=1;
	while(!isdigit(c=getchar()))
		f-=2*(c=='-');
	while(isdigit(c)){
		x=x*10+f*(c^48);
		c=getchar();
	}
	return x;
}
ll n,m,mx,res,tmp,s[N],t[N],cnt[N],fac[N],inv[N];
ll qpow(ll a,ll b=p-2){
	ll res=1;
	while(b){
		if(b&1)
			res=res*a%p;
		a=a*a%p;
		b>>=1;
	}
	return res;
}
ll c[N];
void add(int x,ll k){
	for(;x<=mx;x+=x&-x)
		c[x]+=k;
}
ll ask(int x){
	ll k=0;
	for(;x;x-=x&-x)
		k+=c[x];
	return k;
}
void solve1(){
	for(int i=1;i<=n;++i){
		tmp=tmp*inv[n-i+1]%p;
		tmp=tmp*fac[n-i]%p;//这里是直接替换阶乘
		res=(res+ask(t[i]-1)*tmp)%p;
		if(!cnt[t[i]])//不可能取等
			break;
		if(i==n)//注意，一定要取模！
			res=(res+1)%p;
		tmp=tmp*fac[cnt[t[i]]]%p;
		add(t[i],-1);
		--cnt[t[i]];
		tmp=tmp*inv[cnt[t[i]]]%p;
	}
}
void solve2(){
	for(int i=1;i<=m;++i){
		tmp=tmp*inv[n-i+1]%p;
		tmp=tmp*fac[n-i]%p;
		res=(res+ask(t[i]-1)*tmp)%p;
		if(!cnt[t[i]])
			break;
		tmp=tmp*fac[cnt[t[i]]]%p;
		add(t[i],-1);
		--cnt[t[i]];
		tmp=tmp*inv[cnt[t[i]]]%p;
	}
}
int main(){
	n=read();
	m=read();
	for(int i=1;i<=n;++i){
		s[i]=read();
		if(mx<s[i])
			mx=s[i];
		++cnt[s[i]];
	}
	for(int i=1;i<=m;++i){
		t[i]=read();
		if(mx<t[i])
			mx=t[i];
	}
	fac[0]=1;
	for(int i=1;i<=n;++i)
		fac[i]=fac[i-1]*i%p;
	inv[n]=qpow(fac[n]);
	for(int i=n-1;~i;--i)
		inv[i]=inv[i+1]*(i+1)%p;
	for(int i=1;i<=mx;++i)
		add(i,cnt[i]);
	tmp=fac[n];
	for(int i=1;i<=mx;++i)
		tmp=tmp*inv[cnt[i]]%p;
	if(n<m)
		solve1();
	else
		solve2();
	printf("%lld\n",res);
	return 0;
}
```

---

## 作者：HoshizoraZ (赞：3)

本来赛时写出来了，然后有一两个地方忘取模了……

这里就分享我赛中想的做法吧，可能有些麻烦。

upd：这好像和官方题解的办法差不多……

------------

首先我们先证明一个简单的结论：

设值域为 $1 \sim A$，有 $n$ 个数随机交换位置，令数字 $x$ 出现次数为 $cnt_x$，则产生的不同排列数是

$$\frac{n!}{\prod_{i=1}^A(cnt_i)!}$$

解释一下，对于相同的几个数字 $i$，若把它们当做不同的数，可以有 $(cnt_i)!$ 种排列，但是现在它们相同，所以只有 $1$ 种排列，故答案除以每个 $(cnt_i)!$ 。

------------

两个序列 $a,b$ 比较字典序，满足 $a<b$ 的依据有以下两者之一：

- $a$ 是 $b$ 的一个前缀
- 存在一个位数 $k$，使得 $a,b$ 的前 $k$ 位相同，且 $a$ 的第 $k+1$ 位小于 $b$ 的第 $k+1$ 位。

所以我们可以考虑对每个 $k$ 分别计数。

$k=0$ 的时候，相当于我们要求 $a$ 第 $1$ 位小于 $b$ 的第 $1$ 位，且后面的数位可以**随意排列**。

枚举第一个数 $x$，需要满足 $x<b_1$，而这么枚举带来的方案数等于**原来数字中除掉一个数 $x$，剩余的数随意排列的方案数**。

统计完 $k=0$ 后，我们就统计 $k=1$，以此类推。但是在枚举 $k+1$ 位的时候，相当于前 $k$ 个数和序列 $b$ 中前 $k$ 个数需**完全一样**。因此数方案数的时候，需要去除前面占位的数字。

这样的时间复杂度很高，至少是平方级别的。我们必须优化逐个枚举第 $k+1$ 位的步骤。

首先，当所有数都没有被删除的时候，可以先计算一遍被除的 $(cnt_i)!$ 之积，记为 $T$。

假设数字 $i$ 占了第一位，那么 $cnt_i$ 自身将减去 $1$，因此 $T$ 将变成 $\frac{T}{cnt_i}$。

我们考虑对所有数字 $i$ 都记 $T_i=\frac{T}{cnt_i}$，那么用一个 $i$ 充当第一位的排列数为 $\frac{(n-1)!}{T_i}$。

把问题列成式子，题目要求（这里暂时不考虑特殊情况）

$$
\begin{aligned}
\sum_{k=0}^{n-1}\sum_{i=1}^A[i<b_{k+1}]\frac{(n-k-1)!}{T_i}=\sum_{k=0}^{n-1}(n-k-1)!\sum_{i=1}^{b_{k+1}-1}\frac{1}{T_i} 

\end{aligned}
$$

发现第二个和式**下标连续**，如果我们想快速求出 $\sum\limits_{i=1}^{b_{k+1}-1}\frac{1}{T_i}$，可以使用数据结构存储当前的 $T_i$，之后针对数字删除操作修改它的值即可。

修改是重难点。我们冷静分析一下：

如果当前要删除数字 $i$，那么 $cnt_i$ 自身会减去 $1$。

这时对于 $j \neq i$ 的 $T_j$，里面对数字 $i$ 的重复计数为 $(cnt_i)!$，删除数字后，除的方案数就变成 $(cnt_i-1)!$，相当于除以了 $cnt_i$ 。

**而由于 $T_i$ 内部已经除了一个 $cnt_i$，此时除的方案数从 $(cnt_i-1)!$ 变成 $(cnt_i-2)!$**，相当于自身要除去 $(cnt_i-1)$。

区间乘法、区间除法（乘逆元）、区间求和可以线段树解决，但有点麻烦。发现删除一个 $i$ 的时候，**只有 $T_i$ 修改的内容不一样**，我们可以维护一个变量记录删除后所得的 $(cnt_i-1)$ 之积，对 $T_i$ 在线段树上乘上 $\frac{cnt_i-1}{cnt_i}$ 即可。

------------

最后，就是让我和其余选手都非常难受的细节调试环节了。

- 若 $n<m$，那么枚举到第 $n$ 位时序列 $a$ 可能会成为 $b$ 的前缀，所以第 $n$ 位求和上界的 $b_{k+1}-1$ 应该变成 $b_{k+1}$。
- 如果枚举到某一位时，序列 $a$ 中已经没有可以拿来删的数了，直接退出。
- **取模取干净**。本来前面的题优势在我，因为这个事丢掉一千多分太不值得了。。。

-----------

下面放上代码吧。

```cpp
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
const int INF = 1e9, N = 200010, MOD = 998244353;

int n, m, a[200010], b[200010], ans, prod[200010], inv[200010];
int t[N << 2], buc[N], num, ANS;

int qpow(int a, int b){
	int tt = 1;
	while(b){
		if(b & 1) tt = 1ll * tt * a % MOD;
		a = 1ll * a * a % MOD;
		b >>= 1;
	}
	return tt;
}
inline int Inv(int x){		// 逆元
	return qpow(x, MOD - 2);
}

void build(int i, int l, int r, int x, int v){
	if(l == r){
		t[i] = v;
		return;
	}
	int mid = (l + r) >> 1;
	if(x <= mid) build(i << 1, l, mid, x, v);
	else build(i << 1 | 1, mid + 1, r, x, v);
	t[i] = (t[i << 1] + t[i << 1 | 1]) % MOD;
}
void modify(int i, int l, int r, int x, int v){
	if(l == r){
		t[i] = 1ll * t[i] * v % MOD;
		return;
	}
	int mid = (l + r) >> 1;
	if(x <= mid) modify(i << 1, l, mid, x, v);
	else modify(i << 1 | 1, mid + 1, r, x, v);
	t[i] = (t[i << 1] + t[i << 1 | 1]) % MOD;
}
int query(int i, int l, int r, int x, int y){
	if(l >= x && r <= y) return t[i];
	int mid = (l + r) >> 1, res = 0;
	if(x <= mid) res = (res + query(i << 1, l, mid, x, y)) % MOD;
	if(y > mid) res = (res + query(i << 1 | 1, mid + 1, r, x, y)) % MOD;
	return res;
}


int main(){

	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]), buc[a[i]]++;		// 用桶记录 cnt
	for(int i = 1; i <= m; i++)
		scanf("%d", &b[i]);
	prod[0] = prod[1] = inv[0] = inv[1] = 1;
	for(int i = 2; i < N; i++){
		prod[i] = 1ll * prod[i - 1] * i % MOD;
		inv[i] = 1ll * (MOD - MOD / i) * inv[MOD % i] % MOD;
	}
	int T = 1;
	
	for(int i = 1; i < N; i++)					// 记录应除的方案数
		T = 1ll * prod[buc[i]] * T % MOD;
	
	for(int i = N - 1; i >= 1; i--){
		if(buc[i]){
			T = 1ll * Inv(buc[i]) * T % MOD;	// T_i = T / cnt_i
			build(1, 1, N - 1, i, Inv(T));
			T = 1ll * T * buc[i] % MOD;
		}
	}
	T = 1;					// T 作全局乘法
	for(int i = 1, num; i <= m; i++){
		if(i == n){			// 特判
			if(n < m) ans = (ans + 1ll * query(1, 1, N - 1, 1, b[i]) * prod[n - i] % MOD * T % MOD) % MOD;
			else if(b[i] > 1) ans = (ans + 1ll * query(1, 1, N - 1, 1, b[i] - 1) * prod[n - i] % MOD * T % MOD) % MOD;
			break;
		}
		else if(b[i] > 1) ans = (ans + 1ll * query(1, 1, N - 1, 1, b[i] - 1) * prod[n - i] % MOD * T % MOD) % MOD;
		T = 1ll * T * buc[b[i]] % MOD;
		if(buc[b[i]] >= 1) modify(1, 1, N - 1, b[i], 1ll * (buc[b[i]] - 1) * Inv(buc[b[i]]) % MOD);		// 单独对第 i 个数的位置修改
		if(buc[b[i]] == 0) break;
		buc[b[i]]--;
	}
	printf("%d\n", ans);	
	return 0;
}
```

---

## 作者：jiangtaizhe001 (赞：1)

[可能更好的阅读体验](https://www.cnblogs.com/jiangtaizhe001/p/16216751.html)  
  
[题目传送门](https://codeforces.com/problemset/problem/1648/C)
### 题目大意
给定一个长度为 $n$ 的序列 $a$ 和长度为 $m$ 的序列 $b$。现在你需要将序列 $a$ 进行重排列，求字典序小于 $b$ 的不同种类。对 $998244353$ 取余。  
不同种类的定义为至少存在一位不同。  
$n,m\le 2\times10^5,1\le a_i,b_i\le 2\times 10^5$。  
### 题目解析
不难想到我们可以枚举 $k$，计算 $\forall j\in [1,k-1],a_j=b_j$ 并且 $a_k<b_k$ 的种类。  
显然发现从 $i+2$ 开始就是没有限制的了。  
  
考虑当前有 $n$ 个数字，开个桶，令数字 $i$ 有 $t_i$ 个。  
令总方案数为
$$now=\frac{n!}{\prod t_i!}$$  
这时如果去掉一个数字 $k$，那么这时的方案数量为
$$now'=\frac{(n-1)!}{\prod_{i\not=k}t_i! \times (t_k-1)!}$$  
也就是说
$$now'=now\times\frac{t_k}{n}$$  
然后我们考虑计算 $\forall j\in [1,k-1],a_j=b_j$ 并且 $a_k<b_k$ 的种类。  
这也就是相当于去掉数字 $1,2,\dots,b_k$ 的答案和。  
新增的答案等于
$$\sum_{i=1}^{b_k-1} now \times \frac{t_i}{n}$$  
也就是
$$now\times\frac{\sum\limits_{i-1}^{b_k-1}}{n}$$  

这样开个树状数组维护一下 $t_i$ 的前缀和即可。

注意以上的做法没有考虑到当 $n<m$ 并且存在一种方法使得 $\forall i \in [1,n],a_i=b_i$ 的方法。

核心代码：
```cpp
int n,m,a[maxn],b[maxn],c[maxn],t[maxn];
#define lowbit(x) (x&-x) 
void add(int x,int y){ while(x<=N) c[x]+=y,x+=lowbit(x); return; }
int find(int x){ int sum=0; while(x) sum+=c[x],x-=lowbit(x); return sum; }
ll fpow(ll x,ll y){
	ll res=1,tmp=x%MOD; while(y){ if(y&1) res=res*tmp%MOD; y>>=1; tmp=tmp*tmp%MOD; } return res;
}
ll fact[maxn],inv[maxn],now,ans,tmp;
void init(){
	int i; fact[0]=inv[0]=1; for(i=1;i<=N;i++) fact[i]=fact[i-1]*i%MOD; inv[N]=fpow(fact[N],MOD-2);
	for(i=N-1;i>=1;i--) inv[i]=inv[i+1]*(i+1)%MOD; now=fact[n];
	for(i=1;i<=n;i++) t[a[i]]++; for(i=1;i<=N;i++) add(i,t[i]),now=now*inv[t[i]]%MOD; return;
}
int main(){
	n=read(); m=read(); int i; for(i=1;i<=n;i++) a[i]=read(); for(i=1;i<=m;i++) b[i]=read(); init();
	for(i=1;i<=n;i++){
		if(i>m) break; if(i==n&&n<m&&t[b[i]]) ans++;
		tmp=fpow(n-i+1,MOD-2); ans+=now*tmp%MOD*find(b[i]-1)%MOD; ans%=MOD;
		if(t[b[i]]){ now=now*tmp%MOD*t[b[i]]%MOD; t[b[i]]--; add(b[i],-1); } else break;
	} print(ans%MOD); return 0; 
}
```

---

## 作者：Presentation_Emitter (赞：1)

~~是臭名昭著的 [FST](https://codeforces.com/contest/1649/submission/148593714) 题。~~

前置知识：

- 可重集排列数 $(\sum n_i)! \over \prod (n_i!)$；
- 任意一个支持单点加，查询前缀和的数据结构。

首先考虑 $n \ge m$ 的情况。

设 $cnt_i$ 表示当前状态下没有放的 $i$ 在 $A$ 中的出现次数。

接下来一个个放 $A_i$。对于第 $i$ 位：

- 放任意一个 $\lt B_i$ 的数 $j$，之后任意放，对答案的贡献为 ${(\sum cnt)! \over \prod (cnt!)} \cdot {cnt_j \over \sum cnt}$；
- 放一个 $= B_i$ 的数，之后考虑第 $i+1$ 位。

考虑开一个数据结构维护对于每一个数 $x$，放下这个数且这个数小于当前的 $B_i$ 时对答案的贡献。我们要支持的操作有：

- 全局乘 $1 \over \sum cnt$；
- 单点减；
- 查询前缀和。

全局乘可以使用一个 `tag` 来维护，同时还可以先把 $(-1+\sum cnt)! \over \prod (cnt!)$ 提出来放进 `tag` 中，之后只要维护 $cnt$ 即可。

具体而言，对于第 $i$ 位，所有 $\lt B_i$ 的数的贡献之和为 $\text{tag} \cdot \sum_{j=1}^{B_i-1}cnt_j$，之后 `tag` 乘上 $cnt_{B_i} \over \sum cnt$，最后 $cnt_{B_i}$ 减一。

中途若 $cnt_{B_i}=0$，则结束循环。

对于 $n<m$ 的情况，只需要在 $A_i$ **能放完**的情况下将答案加一即可。

Code:

```cpp
cst ll mx=200001;
ll n,m,r,ans,s[200005],t[200005],cnt[200005],fac[200005],ifc[200005];
struct bit
{
	ll dat[200005];
	il ll qry(ll x){ll res=0;while(x)pls(res,dat[x]),x&=x-1;ret res;}
	il void add(ll x,ll v){while(x&&x<=mx)pls(dat[x],v),x+=x&(-x);}
}b;
int main()
{
	bool flag=0;
	r=n=rd();m=rd();fac[0]=1;if(n<m)flag=1,m=n;
	for(int i=1;i<=n;++i)++cnt[s[i]=rd()];
	for(int j=1;j<=m;++j)t[j]=rd();
	for(int i=1;i<=mx;++i)fac[i]=fac[i-1]*i%HgS;
	ifc[mx]=qpow(fac[mx]);
	for(int i=mx;i>=1;--i)ifc[i-1]=ifc[i]*i%HgS;
	ll tag=fac[n];for(int i=1;i<=mx;++i)tag=tag*ifc[cnt[i]]%HgS;
	for(int i=1;i<=mx;++i)b.add(i,cnt[i]);
	for(int i=1;i<=m;++i)
	{
		(tag*=qpow(r--))%=HgS;
		pls(ans,b.qry(t[i]-1)*tag%HgS);
		if(!cnt[t[i]])break;
		if(i==n&&flag)pls(ans,1);
		(tag*=cnt[t[i]]--)%=HgS;
		b.add(t[i],-1);
	}
	prt(ans);
	ret 0;
}
```

---

## 作者：mango2011 (赞：0)

贡献一发两只树状数组的题解。

对于这个题目，要求一个字符串的字典序比另一个小，那么有两种情形：

1) 存在某个位置 $i(1\le i\le \min(n,m)),s_i<t_i$。

2) 若任意的 $i(1\le i\le \min(n,m)),s_i=t_i$，则 $n<m$ 也是一种情形。

第二种情形是很简单的，留给读者思考（聪慧的作者在这个地方写错了，吃了一发罚时，~~很美味~~）。下面考虑第一种情形：

设重排后的数组是 $s_0$。

我们考虑枚举一个位置 $k$，使得对任意的 $i(1\le i< k),s_{0,i}=t_i,s_{0,k}<t_k$。

但是我们如果还要再枚举 $j=[1,t_i]$ 那么复杂度无法接受，所以先写出式子：

$k$ 对于答案的贡献为 $\displaystyle\sum_{i=1}^{{t_i}-1} \frac{(n-i)!}{cnt_1 !cnt_2!\dots (cnt_k -1)!cnt_{k+1}!cnt_{k+2}!\dots cnt_{2\times10^5}!}$。

其中 $cnt_j$ 表示当前的 $i$ 的数量（$t$ 中每出现一次，我们就让 $cnt_j$ 减去 $1$）。

这个式子很奇怪，我们进行一些修改，记 $M=cnt_1 cnt_2 cnt_3 \dots cnt_{2\times10^5}$。则 $k$ 对答案的贡献为 $\displaystyle\sum_{i=1}^{{t_i}-1}\frac{(n-i)!cnt_i}{M}$，则是我们统一了分子，把分子分母都提出来：

$k$ 的贡献为：$\frac{(n-i)!}{M}\displaystyle\sum_{i=1}^{{t_i}-1}cnt_i$，然后我们开两个树状数组：

第一个维护 $M$，支持单点乘法和区间乘积。

第二个维护 $\displaystyle\sum_{i=1}^{t_i-1}cnt_i$，就相当于单点 $-1$，然后区间求和。

这样子，我们就把这一道题目做完了，时间复杂度 $O(n\log n)$ 空间复杂度 $O(n)$。

由于笔者代码写得过于幽默，所以不予展示。

---

## 作者：Nightingale_OI (赞：0)

## CF1648C Tyler and Strings

### 大意

给定长为 $ n $ 的序列 $ s $ 和长为 $ m $ 的序列 $ t $ ，问将 $ s $ 重新排列后能得到多少个不同的字典序小于 $ t $ 的序列。

### 思路

首先考虑构造一个数组满足值为 $ i $ 的元素恰好有 $ x_i $ 个的方案数（设最大值为 $ s $ ）：

$$ \frac{(\sum_{i = 1}^{n}x_i)!}{\prod x_i!} $$

再考虑让数值为 $ j $ 的数减少一个即 $ x_j - = 1 $ ，答案会变成：

$$ \frac{(\sum_{i = 1}^{n}x_i)!}{\prod x_i!} \times \frac{[(\sum_{i = 1}^{n}x_i) - 1]!}{(\sum_{i = 1}^{n}x_i)!} \times \frac{x_j!}{(x_j - 1)!} $$

注意这里只做假设，式子中 $ x_j $ 是修改前的。

----

再考虑如何统计答案，逐位计算，当前为第 $ i $ 位。

首先，对于 $ 1 \leq j < i $ 要满足 $ s_j = t_j $ ，顺着处理即可。

若这一位取 $ s_i < t_i $ ，就是对于所有小于 $ 1\leq j < t_i $ 用上面推的第二个式子。

即时修改和求和可以使用树状数组维护。

小优化：发现式子中第二个元素恒等于 $ \frac{(n-i)!}{(n-i+1)!} $ （ $ i $ 指求解时的），可以提出来。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define f(i,j,k) for(register int i=j;i<=k;++i)
#define g(i,j,k) for(register int i=j;i>=k;--i)
int n,m,s,l;
const int mo=998244353;
long long ans;
int a[202020];
int b[202020];
int c[202020];
int d[202020];
int jc[202020];
int ny[202020];
int ksm(int x,int p){
    if(!p)return 1;
    int num=ksm(x,p/2);
    num=1ll*num*num%mo;
    if(p&1)num=1ll*num*x%mo;
    return num;
}
void add(int x,int v){
    for(register int i=x;i<=s;i+=-i&i)c[i]=(c[i]+v)%mo;
}
int sum(int x){
    int re=0;
    for(register int i=x;i;i-=-i&i)re=(re+c[i])%mo;
    return re;
}
int main(){
    cin>>n>>m;
    s=2e5;
    f(i,1,n)scanf("%d",&a[i]);
    f(i,1,m)scanf("%d",&b[i]);
    f(i,1,n)++d[a[i]];
    jc[0]=1;
    f(i,1,s)jc[i]=1ll*i*jc[i-1]%mo;
    ny[s]=ksm(jc[s],mo-2);
    g(i,s,1)ny[i-1]=1ll*i*ny[i]%mo;
    l=jc[n];
    f(i,1,s)l=1ll*l*ny[d[i]]%mo;
    f(i,1,s)add(i,d[i]);
    f(i,1,m){
        if(n<i)ans=(ans+1)%mo;
        ans=(ans+1ll*l*sum(b[i]-1)%mo*ksm(n-i+1,mo-2)%mo)%mo;
        if(!d[b[i]])break;
        l=1ll*l*d[b[i]]%mo*ksm(n-i+1,mo-2)%mo;
        add(b[i],-1);
        --d[b[i]];
    }
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：I_am_Accepted (赞：0)

### Analysis

我们先将 $\{s\}$ 中值相同的元素也看作不同来计算答案，最后答案再乘上

$$\left(\prod\limits_{i=1}^kc_i\right)^{-1}$$

即为最终答案，其中 $c_1,\dots,c_k$ 为 $\{s\}$ 每种元素出现的次数（共 $k$ 种）。

我们枚举 $s,t$ 公共前缀长度。同时用树状数组维护 $\{s\}$ 剩下的值。当前对答案的贡献为

$$(之前与 t 完全相同的方案数)\times(当前位比 t 小的方案数)\times(之后位乱放的方案数)$$

注意处理最后 $s,t$ 长度大小的细节。

### Code

[Link](https://codeforces.com/contest/1648/submission/149199297)

---

