# [EC Final 2021] Beautiful String

## 题目描述

庞教授最近获得了一本精灵语言的字典，其中包含许多表示他们单词的字符串。他认为字符串 $s$ 的一个划分是美丽的，如果满足以下两个条件：

- $s = s_1 + s_2 + s_3 + s_4 + s_5 + s_6$，其中 $s_i (1\leq i\leq 6)$ 是非空子字符串。这里 $a + b$ 表示字符串 $a$ 和 $b$ 的连接。
- $s_1 = s_2 = s_5, s_3 = s_6$。

例如，你可以将字符串 "114514" 划分为 6 部分："114514" = "1" + "1" + "4" + "5" + "1" + "4"。第一、第二、第五部分相同，第三和第六部分相同。因此，将 $s=$"114514" 划分为 $s_1=$"1"，$s_2=$"1"，$s_3=$"4"，$s_4=$"5"，$s_5=$"1"，和 $s_6=$"4" 是美丽的。

因此，字符串 $s$ 的美丽定义为 $s$ 的美丽划分的数量。

给定一个字符串 $t$，请帮助庞教授计算 $t$ 的所有子串的美丽之和。

## 说明/提示

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
2
114514
0000000```

### 输出

```
1
3```

# 题解

## 作者：meyi (赞：3)

2023/11/30 upd: 感谢 [zyc212303](https://www.luogu.com.cn/user/556366) 指出一处 typo。

貌似写了个常数比较小的做法，目前洛谷最优解 rk1 390ms，比 rk2 825ms 快了一倍。

首先由 $s_2=s_5, s_3=s_6$ 可知 $s_2+s_3=s_5+s_6$，不妨将它们合并起来看，那么题意就转化为了：定义字符串 $t$ 是美丽的当且仅当将可以 $t$ 视作 $t_1+t_2+t_3+t_4$，满足 $t_1,t_2,t_3,t_4$ 均非空，且 $t_1$ 为 $t_2$ 的真前缀，$t_2=t_4$，给定字符串 $s$，求其有多少子串是美丽的。

考虑 $O(n^2)$ 求 $\text{lcp}$ 的过程，若 $i$ 和 $j$ 的 $\text{lcp}$ 为 $k$，那么可以将 $t_2$ 视作 $s_{i..i+l-1}$，将 $t_4$ 视作 $s_{j,j+l-1}$，$(1\le l\le k)$，由于 $t_3$ 的存在，因此还需要满足 $l< j-i$。故我们可以预处理 $sum_{i,l}$ 表示以 $i$ 开头长度为 $>l$ 的选择 $t_2$ 和 $t_4$ 的方案数，那么每个 $j$ 给 $sum_i$ 的贡献是一个等差数列的形式，使用两个前缀和数组处理即可。最后注意到这里的 $t_2$ 是唯一确定的，因此不会重复计数。

然后考虑 $t_1$ 怎么枚举，仍然是在求 $\text{lcp}$ 的过程中，设 $i$ 和 $j$ 的 $\text{lcp}$ 为 $k$，若 $i+k\ge j$，则说明 $s_{i,j-1}$ 可以成为 $t_1$，答案只需累加 $sum_{j,j-i}$ 即可。

时间复杂度 $O(n^2)$。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
//#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops")
#define ALL(v) v.begin(),v.end()
#define For(i,_) for(int i=0,i##end=_;i<i##end;++i) // [0,_)
#define FOR(i,_,__) for(int i=_,i##end=__;i<i##end;++i) // [_,__)
#define Rep(i,_) for(int i=(_)-1;i>=0;--i) // [0,_)
#define REP(i,_,__) for(int i=(__)-1,i##end=_;i>=i##end;--i) // [_,__)
typedef long long ll;
typedef unsigned long long ull;
#define V vector
#define pb push_back
#define pf push_front
#define qb pop_back
#define qf pop_front
#define eb emplace_back
typedef pair<int,int> pii;
typedef pair<ll,int> pli;
#define fi first
#define se second
const int dir[4][2]={{-1,0},{0,1},{1,0},{0,-1}},inf=0x3f3f3f3f,mod=1e9+7;
const ll infl=0x3f3f3f3f3f3f3f3fll;
template<class T>inline bool ckmin(T &x,const T &y){return x>y?x=y,1:0;}
template<class T>inline bool ckmax(T &x,const T &y){return x<y?x=y,1:0;}
int init=[](){return cin.tie(nullptr)->sync_with_stdio(false),0;}();
int main(){
	int t_case=1;
	cin>>t_case;
	while(t_case--){
		string s;
		cin>>s;
		ll ans=0;
		int n=s.size();
		V<int>lcp(n);
		V<V<int>>sum(n);
		Rep(i,n){
			sum[i].resize(n-i-1>>1);
			V<int>sum2(sum.size());
			FOR(j,i+1,n){
				if(s[i]==s[j]){
					lcp[j]=(j+1<n?lcp[j+1]:0)+1;
					if(i+lcp[j]>=j&&j-i<sum[j].size())ans+=sum[j][j-i];
					if(sum[i].size()){
						int ed=min(j-i-1,lcp[j]);
						sum[i][0]+=ed,--sum2[0];
						if(ed<sum[i].size())++sum2[ed];
					}
				}
				else lcp[j]=0;
			}
			FOR(j,1,sum[i].size())sum[i][j]+=sum[i][j-1]+sum2[j-1],sum2[j]+=sum2[j-1];
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：WZwangchongming (赞：1)

题意：定义 $a+b$ 表示将字符串 $b$ 接在字符串 $a$ 后。

有 $T$ 组询问，每次给定一个字符串 $S$，找出其所有子串 $s$ 满足其可以表示为 $$s=s_1+s_2+s_3+s_4+s_5+s_6$$ 的形式，其中 $$s_1=s_2=s_5,s_3=s_6$$。

数据范围：$$ |S| \le 5 \times 10^3，\sum|S| \le 3\times 10^4$$。

## solution

~~我不会告诉你部分分怎么写的，我也不会告诉你我eps暴力怎么炸的。~~


令 $n$ 表示字符串 $S$ 的长度，则我们希望我们能得到一个单次 $O(n^2)$ 的做法。


题目给定子串模式为 AABCAB，你肯定要找一个枚举点作为突破。而这题的突破点就在于：里面出现了两次 AB。你枚举前一个 AB，为了满足要求，这个 AB 前面的部分要求是这个 AB 的一个前缀，后面只需要隔了至少一个不等于 A 且不等于 B 的间隔，然后再有一个完全一样的东西拼起来即可。

所以做法已经呼之欲出了：枚举 AB 作为整体，如果能检查其前面有多少个其前缀，后面有多少个完全一样的 AB ，那么把这两个值乘法原理乘起来，就是当前枚举的 AB 产生的贡献。

形式化地讲：令 $$t=s_2+s_3$$，在固定了 $t$ 的位置后，就只需要知道 $t$ 的前面有多少个子串和 $t$ 的前缀相同，在 $t$ 的后面还有多少个和 $t$ 完全相同的子串，这两个值乘起来就是 $t$ 产生的贡献。

设 $f_{i,j}$ 表示 $$t=S[i,...,i+j-1]$$ 时，在第 $i+j$ 个位置后面还有多少个与 $t$ 相同的子串。设 $g_{i,j}$ 表示 $$t=S[i,...,i+j-1]$$ 时，在 $t$ 之前有多少个子串是 $t$ 的前缀，那么答案就是 $\sum f_{i,j}\times g_{i,j}$。

至于如何求出 $f,g$：枚举两个位置 $i,j$，并求出 $S[i,...,n]$ 和 $S[j,...,n]$ 的最长公共前缀 $lcp$，然后令 $$f_{i,lcp}=f_{i,lcp}+1$$，最后再给 $f$ 数组的第二维求一个后缀和，即可得到定义中的 $f$ 数组。$g$ 数组则更为方便，只需要判断 $S[i,...,n]$ 和 $S[i-j,...,n]$ 的最长公共前缀是否大于等于 $j$ 即可。

那如何 $O(1)$ 地求出最长公共前缀呢？递推即可。倒序枚举，如果 $S_i=S_j$，则 $$lcp_{i,j}=lcp_{i+1,j+1}+1$$，否则 $lcp_{i,j}=0$。
当然，你也可以后缀数组搞一下。

最后统计时注意 $s_i(i\in{1,2,3,4,5,6})$ 都不能为空。做完了。


---


### Main Code：

```cpp
void mian() {
	cin >> S;
	n = S.length(); S = ' ' + S;
	for(int i = n; i; i--)
		for(int j = i; j <= n; j++)
			if(S[i] == S[j])
				lcp[i][j] = lcp[i + 1][j + 1] + 1;
	for(int i = 2; i <= n; i++)
		for(int j = i + 3; j < n; j++) {
			int k = min(j - i - 1, lcp[i][j]);
			if(k >= 2) f[i][k]++;
		}
	for(int i = 2; i <= n; i++)
		for(int j = n - 1; j > 1; j--) f[i][j] += f[i][j + 1];
	for(int i = 2; i <= n; i++)
		for(int j = 1; j <= min(i - 1, n - i + 1); j++) 
			if(lcp[i - j][i] >= j) g[i][j]++;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++) g[i][j] += g[i][j - 1];
	long long ans = 0;
	for(int i = 2; i <= n; i++)
		for(int j = 2; j <= n; j++) ans += 1ll * f[i][j] * g[i][j - 1];
	cout << ans << '\n';
	memset(f, 0, sizeof(f));
	memset(g, 0, sizeof(g));
	memset(lcp, 0, sizeof(lcp));
}
```
当然，其实我还口胡了一个哈希。

对于找在子串 $t$ 后还有多少与 $t$ 完全相同的子串，如果将后面的所有串都放入哈希表，那么肯定是跑不动的。所以我们将后面所有串按长度分类放入哈希表。因为当你子串 $t$ 的长度知道后，哈希表中的那个串长度也定了，也就可以快速地找后面的完全相同的 $t$ 了。

而对于在子串 $t$ 前寻找一个前缀，只需要枚举前缀前的一个端点，将这个端点到 $t$ 左端点的串和 $t$ 用哈希判一下，再用一个类似后缀和的东西拼上去。

说不太清楚，应该是对的。

---

## 作者：_jimmywang_ (赞：1)

假设原串是 $s$，下文 $s_{[l,r]}$ 表示 $s$ 中 $[l,r]$ 这个字串。

因为可以平方，我们先处理出 $\text{LCP}_{x,y}$ 表示以 $x$ 开头的后缀和以 $y$ 开头的后缀的最长公共前缀。这可以用 $\text{LCP}_{x,y}=[s_x=s_y](\text{LCP}_{x+1,y+1}+1)$ 求出。

然后我们发现 $\texttt{114514}$ 中那些 $\texttt{4}$ 比较难搞，于是我们枚举两个 $\texttt{14}$ 开头的位置 $i$ 和 $j(i<j)$，那么 $\texttt{14}$ 的最长可以是多长呢？因为中间夹了一个 $\texttt{5}$，所以 $\text{maxlen}=\min(j-i-1,\text{LCP}_{i,j})$。

然后我们枚举 $\texttt{14}$ 的长度 $l_1$ 和 $\texttt{1}$ 的长度 $l_2$，$l_2$ 的上界是 $l_1-1$，因为 $\texttt{4}$ 非空。于是贡献为：

$$\sum_{l_1=1}^{\text{maxlen}}\sum_{l_2=1}^{l_1-1}[s_{[i-l_2,i-1]}=s_{[i,i+l_2-1]}]$$

如果我们记 $c_{i,j}=[s_{[i-j,i-1]}=s_{[i,i+j-1]}]$，这可以枚举 $i,j$ 并用 $\text{LCP}$ 判断；那么上面的贡献就是 $c_i$ 的一个二阶前缀和。可以在求出 $c_{i,j}$ 时顺带处理。

于是做完了。复杂度 $O(Tn^2)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define f(i,a,b) for(ll i=a;i<=b;i++)
#define wt int tt=d;while(tt--)
#define py puts("Yes")
#define pn puts("No")
#define fe(i,e) for(int i=0;i<e.size();i++)
#define vi vector<ll>
inline ll rd() {
	ll x=0,f=1;
	char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c))x=x*10+c-'0',c=getchar();
	return x*f;
}
namespace binom{
	const ll Lim=300010,mod=998244353;
	ll jc[Lim],inv[Lim],inc[Lim];
	void pre(){
		jc[0]=jc[1]=inc[0]=inc[1]=inv[0]=inv[1]=1;
		f(i,2,Lim-1)jc[i]=jc[i-1]*i%mod,inv[i]=(mod-mod/i)*inv[mod%i]%mod,
		inc[i]=inc[i-1]*inv[i]%mod;
	}ll C(ll n,ll m){if(n<0||m<0||n<m)return 0;return jc[n]*inc[m]%mod*inc[n-m]%mod;}
}
// using namespace binom;
ll dx[4]={0,1,0,-1};
ll dy[4]={1,0,-1,0};
#define d rd()
#define pb push_back
const ll N=300010;
struct edge{ll v,w,nx;}e[N<<1];
ll hd[N],cnt;
void add(ll u,ll v,ll w){e[++cnt]=(edge){v,w,hd[u]};hd[u]=cnt;}
ll qp(ll a,ll b,ll p){
	ll ans=1;while(b){
		if(b&1)ans=ans*a%p;
		a=a*a%p;b>>=1;
	}return ans;
}ll n,m;
char s[5050];
ll dp[5050][5050];
ll c[5050][5050];
int main(){
	wt{
        scanf("%s",s+1);n=strlen(s+1);
        f(i,0,n+1)f(j,0,n+1)dp[i][j]=c[i][j]=0;
        for(int i=n;i>=1;i--)for(int j=n;j>=1;j--){
            if(s[i]==s[j])dp[i][j]=dp[i+1][j+1]+1;
        }
        f(i,1,n){
            f(j,1,i-1)if(dp[i][j]>=(i-j))c[i][i-j]++;
            f(j,1,n)c[i][j]+=c[i][j-1];
            f(j,1,n)c[i][j]+=c[i][j-1];
        }
        ll res=0;
        f(i,2,n)f(j,i+3,n)if(dp[i][j]>=2){
            ll mx=min(j-i-1,dp[i][j])-1;
            res+=c[i][mx];
        }cout<<res<<endl;
    }
	return 0;
}
```

---

## 作者：Sampson_YW (赞：0)

由 $s_2=s_5$，$s_3=s_6$ 可知 $s_2+s_3=s_5+s_6$。设 $S=s_2+s_3$，那么一个划分就形如 $s_1+S+s_4+S$，且 $s_1$ 是 $S$ 的真前缀。

考虑枚举 $S+s_4+S$ 这样的串。设枚举的子串为 $T=s[l,r]$，那么 $S$ 是 $T$ 的一个 border，且 $|S| <\lceil\frac{|T|}{2}\rceil$。发现 $T$ 的满足要求的最长的 border $K$ 以及 $K$ 的所有 border 都可以是 $S+s_4+S$ 中的 $S$。

$K$ 可以通过一次 KMP 求出。那么只要对于 $K=s[l,p]$ 以及它的所有 border，计算出：选一个前缀 $s_2$，使得 $s_1=s_2$ 的方案数。考虑对 $K$ 计算方案。

如果一个前缀 $s[l,q](q<p)$ 可以成为 $s_2$，那么要满足 $s[2l-1-q,l-1]=s[l,q]$，也就是 $\text{LCP}(s[2l-1-q,l-1],s[l,q])\ge q-l+1$。

那么 $O(n^2)$ 预处理出所有后缀的 LCP，就可以对任意 $s[l,q]$ 在 $O(1)$ 的时间内判断了。对于 $K=s[l,p]$ 的方案数，只需要做个前缀和就能求出。

那么对于 $K$ 和它所有 border 的方案数，跑一遍 KMP 后进行 DP 即可。

有点乱，整理一下就是：

先枚举 $s_2+s_3+s_4+s_5+s_6$，那么 $s_2+s_3$ 是这个串的 border 且长度小于串长的一半。再对 $s_2+s_3$ 求出分割出 $s_2$ 的方案数，答案累加上这个方案数。

代码中求 $K$ 用了 border 的一点性质：如果字符串 $S$ 存在一个 border $T$ 满足 $2|T|>|S|$，那么 $S$ 有长度为 $2|T|-|S|$ 的循环节。每次 $T$ 跳 fail 的长度会减少 $2|T|-|S|$，直到跳到一个长度 $\leq \frac{|S|}{2}$ 的 border。

[code](https://www.luogu.com.cn/paste/sge0jua9)

---

