# Cost Equilibrium

## 题目描述

An array is called beautiful if all the elements in the array are equal.

You can transform an array using the following steps any number of times:

1. Choose two indices $ i $ and $ j $ ( $ 1 \leq i,j \leq n $ ), and an integer $ x $ ( $ 1 \leq x \leq a_i $ ). Let $ i $ be the source index and $ j $ be the sink index.
2. Decrease the $ i $ -th element by $ x $ , and increase the $ j $ -th element by $ x $ . The resulting values at $ i $ -th and $ j $ -th index are $ a_i-x $ and $ a_j+x $ respectively.
3. The cost of this operation is $ x \cdot |j-i|  $ .
4. Now the $ i $ -th index can no longer be the sink and the $ j $ -th index can no longer be the source.

 The total cost of a transformation is the sum of all the costs in step $ 3 $ .For example, array $ [0, 2, 3, 3] $ can be transformed into a beautiful array $ [2, 2, 2, 2] $ with total cost $ 1 \cdot |1-3| + 1 \cdot |1-4| = 5 $ .

An array is called balanced, if it can be transformed into a beautiful array, and the cost of such transformation is uniquely defined. In other words, the minimum cost of transformation into a beautiful array equals the maximum cost.

You are given an array $ a_1, a_2, \ldots, a_n $ of length $ n $ , consisting of non-negative integers. Your task is to find the number of balanced arrays which are permutations of the given array. Two arrays are considered different, if elements at some position differ. Since the answer can be large, output it modulo $ 10^9 + 7 $ .

## 说明/提示

In the first example, $ [1, 2, 3] $ is a valid permutation as we can consider the index with value $ 3 $ as the source and index with value $ 1 $ as the sink. Thus, after conversion we get a beautiful array $ [2, 2, 2] $ , and the total cost would be $ 2 $ . We can show that this is the only transformation of this array that leads to a beautiful array. Similarly, we can check for other permutations too.

In the second example, $ [0, 0, 4, 4] $ and $ [4, 4, 0, 0] $ are balanced permutations.

In the third example, all permutations are balanced.

## 样例 #1

### 输入

```
3
1 2 3```

### 输出

```
6```

## 样例 #2

### 输入

```
4
0 4 0 4```

### 输出

```
2```

## 样例 #3

### 输入

```
5
0 11 12 13 14```

### 输出

```
120```

# 题解

## 作者：Limit (赞：6)

# 题目大意

给出一个序列 $a$，求这个序列存在多少种排列是 balanced。

在开始时对序列中的每个元素规定其为源点还是汇点，接下来的操作中，每次可以选择 $i,j$，要满足 $i$ 是源点，$j$ 是汇点，可以选择一个任意正整数 $x$，使元素 $i$ 的权值减 $x$，元素 $j$ 的权值加 $x$，需要花费 $|i-j|x$ 的代价。

如果对于任意的可以把序列存在至少一种规定源点汇点的方案使得对于把权值全部变为相同的任意的操作方案的代价是相同的，那么就称这个序列为 balanced。

# 分析

如果平均数不是整数显然答案为 $0$。

然后把序列分成三部分：

1. 权值小于平均数的 $b_1,b_2,\dots b_p$
2. 权值等于平均数的 $\overline{a},\overline{a},\dots$
3. 权值大于平均数的 $c_1,c_2,\dots c_q$

其中等于平均数的那些数是的权值是不能改变权值的，所以不需要考虑它们是源点还是汇点。

经过简单的考虑可以得到 $b$ 中只能做汇点，$c$ 中只能做源点。

当 $|b|=1$ 或 $|c|=1$ 时可以发现不论怎么排都是满足条件的，所以可以直接用多重集的排列数计算。

下面只考虑 $1<|b|$ 且 $1<|c|$ 的情况。

如果存在某个源点前后都存在汇点可以发现必然存在方案使得代价不同，所以源点必须全部放在汇点前（或汇点后）。可以枚举最后的一个源点放置的位置 $o$，那么这个位置的贡献为
$$
(\sum_{i=1}^{k}\frac{(o-1)!}{\prod_{j=1}^{k}(s_j-[i=j])!(o-1-\sum_{j=1}^ks_j)!})(\frac{(n-o)!}{\prod_{i=1}^lt_i!(n-o-\sum_{i=1}^lt_i)!})
$$
其中 $b$ 中存在 $k$ 种不同的数，第 $i$ 种数出现了 $s_i$ 次；$c$ 中存在 $l$ 种不同的数，第 $i$ 种数出现了 $t_i$ 次。

其中
$$
\sum_{i=1}^{k}\frac{1}{\prod_{j=1}^{k}(s_j-[i=j])!}
$$
和
$$
\frac{1}{\prod_{i=1}^lt_i!}
$$
可以 $\mathcal{O}(n)$ 预处理，$\mathcal{O}(1)$ 计算每个 $o$ 的贡献，把这些贡献加起来即可。

因为这样计算的是汇点在源点前的方案，所以最终答案需要乘二。

综上可以做到 $\mathcal{O}(n\log n)$ 计算最终结果，复杂度瓶颈仅在于 `sort`。

# 代码

```cpp
inline int Pow(int a,int b,const int mod)
{
	a%=mod;
	if(!a)
	{
		return 0;
	}
	register int result(1);
	for(;b;a=1ll*a*a%mod,b>>=1)
	{
		if(b&1)
		{
			result=1ll*result*a%mod;
		}
	}
	return result;
}
#define POW(a,b) Pow(a,b,MOD)
#define INV(x) Pow(x,MOD-2,MOD)
const int MAXN=1e5+5;
const int MOD=1e9+7;
int n;
int arr[MAXN];
int fac[MAXN];
int inv[MAXN];
inline LL C(const int n,const int m)
{
	if(n<m)
	{
		return 0;
	}
	return 1ll*fac[n]*inv[m]%MOD*inv[n-m]%MOD;
}
int num1[MAXN];
int num2[MAXN];
int main()
{
	Read(n);
	fac[0]=1;
	REP(i,1,n)
	{
		fac[i]=1ll*fac[i-1]*i%MOD;
	}
	inv[n]=INV(fac[n]);
	DOW(i,n-1,0)
	{
		inv[i]=inv[i+1]*(i+1ll)%MOD;
	}
	LL sum(0);
	REP(i,1,n)
	{
		Read(arr[i]);
		sum+=arr[i];
	}
	if(sum%n)
	{
		Writeln(0);
		return 0;
	}
	int ba=sum/n;
	sort(arr+1,arr+1+n);
	int cnt1(0),cnt2(0),cnt3(0),s(0),s2(0);
	arr[0]=arr[n+1]=-1;
	REP(i,1,n)
	{
		if(ba<=arr[i])
		{
			if(arr[i]==ba)
			{
				cnt3=i;
			}
			break;
		}
		++s;
		if(arr[i]^arr[i-1])
		{
			num1[++cnt1]=1;
		}
		else
		{
			++num1[cnt1];
		}
	}
	DOW(i,n,1)
	{
		if(arr[i]<=ba)
		{
			if(arr[i]==ba)
			{
				cnt3=i-cnt3+1;
			}
			break;
		}
		++s2;
		if(arr[i]^arr[i+1])
		{
			num2[++cnt2]=1;
		}
		else
		{
			++num2[cnt2];
		}
	}
	if(!cnt1)
	{
		Writeln(1);
		return 0;
	}
	if(s==1||s2==1)
	{
		int answer(1ll*fac[n]*inv[cnt3]%MOD);
		REP(i,1,cnt1)
		{
			answer=1ll*answer*inv[num1[i]]%MOD;
		}
		REP(i,1,cnt2)
		{
			answer=1ll*answer*inv[num2[i]]%MOD;
		}
		Writeln(answer);
		return 0;
	}
	int q(0),p(1),p2(1);
	REP(i,1,cnt1)
	{
		p=1ll*p*inv[num1[i]]%MOD;
	}
	REP(i,1,cnt2)
	{
		p2=1ll*p2*inv[num2[i]]%MOD;
	}
	REP(i,1,cnt1)
	{
		q=(q+1ll*p*fac[num1[i]]%MOD*inv[num1[i]-1])%MOD;
	}
	int answer(0);
	REP(i,s,n)
	{
		if(n<i+s2)
		{
			break;
		}
		LL add(1ll*fac[i-1]*inv[i-s]%MOD*q%MOD*fac[n-i]%MOD*inv[n-i-s2]%MOD*p2%MOD);
		answer=(answer+add)%MOD;
	}
	Writeln(answer*2ll%MOD);
	return 0;
}
```



---

## 作者：Tx_Lcy (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/CF1513E)

## 思路

简单题，来一个简单点的思路。

题目规定了每个点只能减少或增加，所以等于人为地把点分成了三种。

我们定义 $i$ 为黑点当且仅当 $a_i$ 大于平均数，同理，灰点为等于，白点为小于。三种点的个数分别为 $cnt_2,cnt_1,cnt_0$。

不难发现灰点对答案没有任何影响，我们最后乘上 $\binom{n}{cnt_1}$ 即可。

首先特判 $cnt_2 \le 1$ 与 $cnt_0 \le 1$ 的情况，这两种情况下所有方案都是合法的。

我们发现之所以有方案不合法，是因为这个 $|i-j|$，如果没有绝对值，那么不管怎么排列，代价一定是相同的。

所以我们需要人为地去掉绝对值，具体说来，就是直接把所有黑点都放在左边，所有白点都放在右边或所有白点都放在左边，所有黑点都放在右边。

这样我们就可以对白点和黑点内的排列方案分别计数，然后乘起来，然后乘 $2$，然后乘上 $\binom{n}{cnt_1}$ 即可。

对白点和黑点内的方案的计数是一个简单的数学问题，相信大家都会。

## 代码

```cpp
//A tree without skin will surely die.
//A man without face is invincible.
#include<bits/stdc++.h>
using namespace std;
#define int long long
int const mod=1e9+7;
int const N=1e5+10;
int fac[N],a[N];map<int,int>nsm,num0,num2;
inline int qpow(int a,int b,int t=1){for(;b;b>>=1,a=a*a%mod)if(b&1)t=t*a%mod;return t;}
inline int C(int n,int m){return fac[n]*qpow(fac[m],mod-2)%mod*qpow(fac[n-m],mod-2)%mod;}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int n;cin>>n;
	fac[0]=1;
	for (int i=1;i<=n;++i) fac[i]=fac[i-1]*i%mod;
	int sum=0,cnt0=0,cnt1=0,cnt2=0;
	for (int i=1;i<=n;++i) cin>>a[i],sum+=a[i];
	if (sum%n) return cout<<"0\n",0;
	sum/=n;
	for (int i=1;i<=n;++i)
		cnt0+=(a[i]<sum),
		cnt1+=(a[i]==sum),
		cnt2+=(a[i]>sum);
	int num=fac[n];
	for (int i=1;i<=n;++i) ++nsm[a[i]];
	for (int i=1;i<=n;++i) num*=qpow(fac[nsm[a[i]]],mod-2),num%=mod,nsm[a[i]]=0;
	if (cnt0<=1 || cnt2<=1) return cout<<num<<'\n',0;
	int ans=0,res=fac[cnt0];
	for (int i=1;i<=n;++i) if (a[i]<sum) ++num0[a[i]];
	for (int i=1;i<=n;++i) if (a[i]<sum) res*=qpow(fac[num0[a[i]]],mod-2),res%=mod,num0[a[i]]=0;
	ans=res;res=fac[cnt2];
	for (int i=1;i<=n;++i) if (a[i]>sum) ++num2[a[i]];
	for (int i=1;i<=n;++i) if (a[i]>sum) res*=qpow(fac[num2[a[i]]],mod-2),res%=mod,num2[a[i]]=0;
	ans*=res,ans%=mod;
	ans*=2,ans%=mod;
	ans*=C(n,cnt1);ans%=mod;
	cout<<ans<<'\n';
	return 0;
}
```

---

## 作者：7KByte (赞：2)

简单分析一下，一个点不能同时作为源点和汇点，所以值一定是经过一次转移到应该到的位置。

所以我们可以看作相邻点之间的移动，相邻点之间的移动可以还原成一个合法的原操作序列。

先求出序列的平均数 $\overline{x}$ ，则将 $a_i<0/=0/>0$ 作为三种不同的位置类型。

第一种只能为汇点，第三种只能为源点，第二种只能为重力点。

观察一下如果只有一个汇点或者源点，则所有方案数都是满足条件的。

答案就是可重集合的排列。

否则，源点必须在一起，汇点也必须在一起，否则一定有 $1313$ 或 $1331$ 这种情况。可以走重复的边使得答案不优。

所以这种情况答案分两种，第一种是一类点在左边，第二种是二类点在左边。

三类点只用占位置即可，贡献为$\dbinom{n}{s_3}$ 。

再乘上一类点和二类点的可重集合排列数。

时间复杂度$\rm O(N\log P)$ 。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 100005
#define P 1000000007
#define int long long 
using namespace std;
int n,a[N],sum,fac[N],p[N],q[N];
int Pow(int x,int y){int now=1;for(;y;y>>=1,x=1LL*x*x%P)if(y&1)now=1LL*now*x%P;return now;}
int C(int x,int y){return 1LL*fac[x]*Pow(fac[y],P-2)%P*Pow(fac[x-y],P-2)%P;}
signed main(){
	scanf("%lld",&n);
	rep(i,1,n)scanf("%lld",&a[i]),sum+=a[i];
	if(sum%n){puts("0");return 0;}
	int L=0,R=0;sum/=n;
	rep(i,1,n)if(a[i]>sum)p[++L]=a[i];else if(a[i]<sum)q[++R]=a[i];
	fac[0]=1;rep(i,1,n)fac[i]=1LL*fac[i-1]*i%P;
	sort(p+1,p+L+1);
	sort(q+1,q+R+1);
	if(L<=1||R<=1){
		int ans=C(n,n-L-R)*fac[L+R];
		if(L){
			int pre=1;
			rep(i,2,L)if(p[i]!=p[i-1])ans=1LL*ans*Pow(fac[i-pre],P-2)%P,pre=i;
			ans=1LL*ans*Pow(fac[L-pre+1],P-2)%P;
		}
		if(R){
			int pre=1;
			rep(i,2,R)if(q[i]!=q[i-1])ans=1LL*ans*Pow(fac[i-pre],P-2)%P,pre=i;
			ans=1LL*ans*Pow(fac[R-pre+1],P-2)%P;
		}
		printf("%lld\n",ans);
	}
	else{
		int ans=1LL*C(n,n-L-R)*fac[L]%P*fac[R]%P*2%P;
		int pre=1;
		rep(i,2,L)if(p[i]!=p[i-1])ans=1LL*ans*Pow(fac[i-pre],P-2)%P,pre=i;
		ans=1LL*ans*Pow(fac[L-pre+1],P-2)%P;
		pre=1;
		rep(i,2,R)if(q[i]!=q[i-1])ans=1LL*ans*Pow(fac[i-pre],P-2)%P,pre=i;
		ans=1LL*ans*Pow(fac[R-pre+1],P-2)%P;
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：1)

# CF1513E 题解



## 思路分析

记 $c_x$ 表示 $x$ 在 $a_1\sim a_n$ 中出现的次数，$w$ 为 $a_1\sim a_n$ 中的最大值。

首先求出 $a_1\sim a_n$ 的平均值，记为 $\bar a$，若 $\bar a\notin \mathbb Z$ 则无解。

考虑将每个 $a_i$ 当成 $i$ 拥有的流量，对于每个 $a_i$ 比较其与 $\bar a$ 的大小关系有如下三种情况：

- $a_i>\bar a$，每次操作一定是流出流量，共有 $a_i-\bar a$ 的流量要流出，将点 $i$ 放入源点点集 $\mathbf S$。
- $a_i=\bar a$，即 $a_i$ 已经饱和，不需要进行任何操作，将点 $i$ 放入自由点点集 $\mathbf F$。
- $a_i<\bar a$，每次操作一定是流入流量，共有 $\bar a-a_i$ 的流量要流入，将点 $i$ 放入汇点点集 $\mathbf T$。

若 $|\mathbf S|=0$ 或 $|\mathbf T|=0$，此时 $|\mathbf F|=n$，总共只有 $1$ 中可能的排列。

对于每次操作，看成从某个源点 $S_i$ 向某个汇点 $T_j$ 流了 $1$ 的流量，代价为 $|S_i-T_j|$，并复制这样的流 $x$ 次。

考虑对于给定的 $\{a_i\}$，判断其是否满足题目限制，对于一种合法的方案，如果存在两个流 $S_{i_1}\to T_{j_1},S_{i_2}\to T_{j_2}$ 满足 $S_{i_1}<T_{j_1}<S_{i_2}<T_{j_2}$ 或 $S_{i_1}>T_{j_1}>S_{i_2}>T_{j_2}$，那么交换两个流的终点变成流 $S_{i_1}\to T_{j_2},S_{i_2}\to T_{j_1}$ 时总花费改变。

所以根据上面的分析，当 $|\mathbf S|\ge 2$ 且 $|\mathbf T|\ge 2$ 时，在任意合法的 $\{b_i\}$ 中，所有的源点在都在所有的汇点的左侧或右侧。

而 $|\mathbf S|=1$ 或 $|\mathbf T|=1$ 时，任意排列 $\{a_i\}$ 均可，此时答案为 $\binom{n}{c_0,c_1,c_2,\cdots,c_w}$。

当 $|\mathbf S|\ge 2$ 且 $|\mathbf T|\ge 2$ 时，我们先选择 $\mathbf F$ 中点的位置，然后确定 $\mathbf S$ 和 $\mathbf T$ 内部点集的排列数，最后确定是 $\mathbf S$ 在 $\mathbf T$ 左边还是右边，答案为：
$$
\binom{n}{|\mathbf F|}\times \binom{|\mathbf S|}{c_0,c_1,c_2,\cdots,c_{\bar a-1}}\times \binom{|\mathbf T|}{c_{\bar a+1},c_{\bar a+2},\cdots,c_{w}}\times 2
$$
因此处理出 ${c_i}$ 和阶乘以及阶乘逆元即可计算。

时间复杂度 $\Theta(n\log n)$。

## 代码呈现

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=1e5+1,MOD=1e9+7;
inline int ksm(int a,int b=MOD-2,int m=MOD) {
	int ret=1;
	while(b) {
		if(b&1) ret=ret*a%MOD;
		a=a*a%MOD;
		b=b>>1;
 	}
 	return ret;
}
int a[MAXN],fac[MAXN],inv[MAXN];
map <int,int> cnt;
inline int binom(int n,int m) {
	return fac[n]*inv[m]%MOD*inv[n-m]%MOD;
}
signed main() {
	int n,sum=0;
	scanf("%lld",&n);
	fac[0]=inv[0]=1;
	for(int i=1;i<=n;++i) fac[i]=fac[i-1]*i%MOD,inv[i]=ksm(fac[i]);
	for(int i=1;i<=n;++i) {
		scanf("%lld",&a[i]);
		sum+=a[i];
	}
	if(sum%n!=0) {
		puts("0");
		return 0;
	}
	int avr=sum/n,S=0,T=0;
	for(int i=1;i<=n;++i) {
		++cnt[a[i]];
		if(a[i]>avr) ++S;
		if(a[i]<avr) ++T;
	}
	if(S==0&&T==0) {
		puts("1");
		return 0;
	}
	if(S==1||T==1) {
		int ans=fac[n];
		for(auto p:cnt) ans=ans*inv[p.second]%MOD;
		printf("%lld\n",ans);
		return 0;
	}
	int s=fac[S],t=fac[T];
	for(auto p:cnt) {
		int x=p.first,tot=p.second;
		if(x>avr) s=s*inv[tot]%MOD;
		if(x<avr) t=t*inv[tot]%MOD;
	}
	printf("%lld\n",2*s*t%MOD*binom(n,S+T)%MOD);
	return 0;
}
```



---

## 作者：yinianxingkong (赞：0)

水一篇简洁的题解，复杂度期望 $O(n)$，期望指的是用了 $\text{Hash}$ 表。

首先容易想到所有数都得往平均数靠，若平均数不是整数显然无解。

我们称比平均数小的数是左括号，比平均数大的数是有括号。

一般情况下，若左右括号有交叉，交叉部分显然有不计和计两次两种贡献，所以一定不行。所以一定是左括号一堆，右括号一堆，其余数在其中任意插入。统计同一种括号时可以同一个数一起处理，就是无序序列归并，方案数 $\binom{len_1+len_2}{len_1}$。注意最后左右括号可以切换，所以要两倍。

特殊地，只要单个左右端点时无论如何都不会更劣，这种特判即可。

其余细节不难处理。

[代码。](https://mirror.codeforces.com/problemset/submission/1513/296815271)

---

