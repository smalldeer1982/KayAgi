# Hyperregular Bracket Strings

## 题目描述

给定一个数 $n$ 和 $k$ 个区间 $\left[l_i,r_i\right]\subseteq [1,n]$。

我们定义，对于一个长度为 $n$ 的，仅由 ```(``` 和 ```)``` 组成的合法括号序列，如果它的每一个区间 $\left[l_i,r_i\right]$ 内的子串都是合法括号序列，那么这个括号序列是**好的**。

求**好的**括号序列的数量，答案对 $998244353$ 取模。

## 说明/提示

以样例的第四组数据为例，答案代表的 $4$ 个好的括号序列分别是：

```
 ((())(()))
 ((())()())
 ()()((()))
 ()()(()())
```

而 ```)(())(())(``` 不是答案之一，因为它不是一个合法的括号序列（最左端与最右端的括号未配对）

```(())((()))``` 也不是答案之一，因为它的 $[3,4]$ 表示的子串 ```))``` 不是一个合法的括号序列

```((()(())))``` 也不是答案之一，因为它的 $[6,9]$ 表示的子串 ```()))``` 不是一个合法的括号序列

## 样例 #1

### 输入

```
7
6 0
5 0
8 1
1 3
10 2
3 4
6 9
1000 3
100 701
200 801
300 901
28 5
1 12
3 20
11 14
4 9
18 19
4 3
1 4
1 4
1 4```

### 输出

```
5
0
0
4
839415253
140
2```

# 题解

## 作者：hfjh (赞：10)

# CF1830C Hyperregular Bracket Strings
## 题意

给定 $k$ 个区间，求有多少种长度为 $n$ 的**合法括号序列**，满足每个区间也是**合法括号序列**。

## 题解
考虑两个相交的区间，可以分成三个区间，三个区间都满足是合法括号序列。

> 黑色是原本的，黄色是现在的。

![](https://cdn.luogu.com.cn/upload/image_hosting/ta6dmgly.png)

考虑两个相包含的区间，被包含的区间是一部分，剩余部分是一部分。

> 红色部分要满足合法，黄色部分拼起来也要满足合法。

![](https://cdn.luogu.com.cn/upload/image_hosting/pd6cvgbb.png)

我们有一堆相交，相包含的区间交替出现，如果你要真的分割区间会是一个~~我不会的~~分讨。

我们考虑给每一个区间赋权值，相交部分的权值就异或起来。

在上面两种情况中权值异或后权值每一部分都不相同。

我们想要的是每一种区间的长度然后求卡特兰数，也就是每一种区间也就是每一个异或值对应的个数。

> 区间赋异或权值可以考虑差分序列，两端点赋了之后再前缀异或和得到原序列。

## 代码
```cpp
#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long  
using namespace std;
const int N = 3e5 + 10, mod = 998244353;
int T, n, k, l, r;
ull p[N], v;
ll pr[N], ip[N], ans = 1;
mt19937_64 myrand(20070924);
map<ull, int>t;
ll mpow(ll x, ll k){
	ll ans = 1;
	while(k){
		if(k & 1) ans = ans * x % mod;
		x = x * x % mod;
		k >>= 1;
	}
	return ans;
}

void pre(int n){
	pr[0] = ip[0] = 1;
	for(int i = 1; i <= n; ++i) pr[i] = pr[i - 1] * i % mod;
	ip[n] = mpow(pr[n], mod - 2);
	for(int i = n - 1; i >= 1; --i) ip[i] = ip[i + 1] * (i + 1) % mod;
} 
ll C(int x, int y){ return pr[x] * ip[y] % mod * ip[x - y] % mod;}
ll Can(int n){
	if(n & 1) return 0;
	return (C(n, n / 2) - C(n, n / 2 - 1) + mod) % mod;
}
void input(){
	cin>> n >> k;
	for(int i = 1; i <= k; ++i){
		cin >> l >> r;
		v = myrand();
		p[l] ^= v, p[r + 1] ^= v;
	}
}
void op(){
	for(int i = 1; i <= n; ++i){
		p[i] ^= p[i - 1];
		++t[p[i]];
	}
	for(auto it : t) ans = ans * Can(it.second) % mod;
}
void qk(){
	ans = 1;
	for(int i = 1; i <= n + 1; ++i) p[i] = 0;
	t.clear();
} 
int main(){
	pre(3e5);
	cin>>T;
	while(T--){
		input();
		op();		
		cout<<ans<<'\n';
		qk();
	}
} 

```


---

## 作者：Alex_Wei (赞：9)

### [CF1830C Hyperregular Bracket Strings](https://www.luogu.com.cn/problem/CF1830C)

将 $l$ 减去 $1$，设 $s$ 表示括号序列前缀和，那么一条限制要求：

- $s_l = s_r$。
- $\forall i\in [l, r], s_i \geq s_r$。

线段树优化建图。对于每个强连通分量，每相邻两个位置之间都是合法括号序列。按 $s$ 从大到小的顺序处理，每次算出区间内已经被处理的位置数量（可以用 set 维护），可知需要多长的合法括号序列，将答案乘以对应卡特兰数即可。

时间复杂度 $\mathcal{O}(n + k\log n)$。[代码](https://codeforces.com/contest/1830/submission/207644804)。

我们发现一个非常厉害的性质：设 $S_i$ 表示 $i$ 被哪些区间覆盖了，对于 $S_i$ 相同的下标形成的等价类，每个等价类内部为合法括号序列，且条件充要。证明即讨论两区间相交时不包含或包含两种情况。

XOR-哈希即可做到除排序外 $\mathcal{O}(n + k)$。

---

## 作者：xkcdjerry (赞：6)

复健之后第一次场切的 E，写篇题解纪念一下。

首先考虑无限制的情况：若 $n$ 为奇数显然答案为 $0$，否则一定各有 $k=\dfrac{n}2$ 个左右括号，设 $f_{2i}$ 为有左右括号各 $i$ 个的方案数，则 $f_{2i}$ 为第 $i$ 个卡特兰数，即 $f_i=\dfrac{C(2i,i)}{i+1}$。（证明略）

接下来思考若存在恰好一个区间 $[l,r]$ 如何处理，这个区间内部显然可以同理上文得到答案为 $f_{r-l+1}$，而显然在 $[l,r]$ 内部的括号序列由于一定恰好匹配，所以对外部无影响，即对于任何一个 $[l,r]$ 的填法，其他地方的填法都和长度为 $n-(r-l+1)$ 的填法一一对应。

因此得出一个重要结论：

若一个长度为 $L$ 的区间有若干个长度分别为 $l_1,l_2,...,l_x$ 的子区间，且子区间填法分别为 $g_1,g_2,...,g_x$，那么这个区间的填法就为 $f_{L-\sum l_i} \prod g_i$。

那么重叠区间怎么办？

假设存在区间 $[a,b],[c,d]$，满足 $a \leqslant c \leqslant b \leqslant d$，那么在区间 $[c,b]$ 内：

* 每个右括号一定匹配一个左括号，否则 $[c,d]$ 一定不合法。
* 每个左括号一定匹配一个右括号，否则 $[a,b]$ 一定不合法。

综上，$[c,b]$ 内的左右括号一一对应，即 $[c,d]$ 合法，那么 $[a,c-1],[b+1,d]$ 内的括号一定也合法。

反之，显然 $[a,c-1],[c,b],[b+1,d]$ 内的括号若均合法，则 $[a,b],[c,d]$ 内的括号也一定均合法。

因此，若若干区间重叠，从每个端点处切开即可，完了之后一定会是要么并列要么包含的**有根树**形式，根据上面的式子 dfs 推即可。

~~然后我就卡死了大半个小时。~~

这里的难点就在于给出一车线段，如何判断一个线段不和**任何一个**其他线段相交，如果相交就拆开，如果没有就确定覆盖它的最短的线段是什么。（显然该线段唯一）

---

我们可以转换思路：  
给出一堆线段覆盖，找出最少的线段使得每个线段左右端点的覆盖情况相同。  

为什么可以这样呢？

首先我们证明充分性，即如果两个相邻的位置覆盖情况不同他们一定在原切分后处于不同的线段。  
显然如果相邻的位置不同，一定是左侧的是某个线段的右端点或右侧是某个线段的左端点，那么要么是线段包含要么线段相交，无论什么情况都将会被切分为不同的线段。

接下来我们证明必要性，即如果两个相邻的位置覆盖情况相同他们一定在原切分后处于相同的线段。  
这个结论显然。

---

我们接下来要做的时期就是如何对于若干线段迅速判断两个点覆盖情况是否相同。

做过 PKUSC2022 D2T2 的人应该很熟悉的一个 trick：我们对于每个初始线段随机赋一个权值，然后每次加入线段对它覆盖的所有点异或上这个权值，当随机的权值值域为 $10^{18}$ 的时候，以*高概率*（北大讲课人棒读音），两个点异或值相同等价于覆盖法相同。

那么我们记录每个权值出现的左端点和右端点就可以处理划分问题，那包含呢？

一个常见的错误方法就是检测左右端点再超出一点（$l-1,r+1$）属于的区间就是他的父亲。但是这样在三个区间相邻的时候就会彻底失效。（两个区间相邻就不太对劲了但是三个就彻底炸了）

解决方法是按把个端点按位置升序，长度降序排列，显然这样每个区间的父亲左端点一定在自己的前面出现，右端点一定在自己的后面出现。这样维护一个目前区间的串，遇到左端点设置父亲并压入，遇到右端点弹出即可。

---

复杂度分析：

* 预处理卡特兰数 $O(n)$ 时空，前缀和 $O(n)$ 时空；
* 维护每个权值的左右端点因为需要 `map` 所以 $O(n)$ 空间 $O(n \log n)$ 时间；
* 排序端点 $O(n)$ 空间 $O(n \log n)$ 时间；
* 维护栈处理父亲 $O(n)$ 时空；
* dfs 计算答案 $O(n)$ 时空。

最终复杂度：时间 $O(n \log n)$，空间 $O(n)$。

---

正确性分析：

这个代码正确当且仅当所有分割出来的线段的权值互不相同。  
由于最初仅存在 $n$ 个线段 $2n$ 个端点，所以最终线段数目不超过 $2n-1$，若权值范围为 $V$，则正确概率为：
$$
\prod_{i=0}^{6 \times 10^5} \dfrac{V-i}{V}=0.9999998200002852
$$

假设有 $100$ 个 test case，每个 test case $T=100$，则正确概率为 $0.9982016217136003$ （$0.17\%$ 的错误率），非常的高概率。

---

代码：

```c++
#include <cstdio>
#include <map>
#include <ctime>
#include <vector>
#include <random>
#include <algorithm>

#define ll long long
#define N 2000010
#define P 998244353
using std::vector;

vector<int> son[N];
int n,m;
ll b[N];
struct seg
{
    int l,r,fa;
    //这里用在阴间排序，l为左端点r为长度fa为自己
    bool operator<(seg b) const
    {return l==b.l?r>b.r:l<b.l;}
}s[N],srt[N*2];
std::mt19937_64 rng(time(0));
ll fmul[N],inv[N],finv[N],bruh[N];
ll dfs(int x)
{
    ll ans=1; int len=s[x].r-s[x].l+1;
    for(auto i:son[x]) ans=ans*dfs(i)%P,len-=s[i].r-s[i].l+1;
    ll rtn=len&1?0:ans*bruh[len/2]%P;
    return rtn;
}
void once()
{
    scanf("%d%d",&n,&m);
    //预处理卡特兰数+特判n为奇数情况
    fmul[0]=1; for(int i=1;i<=n*2;i++) fmul[i]=fmul[i-1]*i%P;
    inv[1]=1; for(int i=2;i<=n*2;i++) inv[i]=(P-P/i)*inv[P%i]%P;
    finv[0]=1; for(int i=1;i<=n*2;i++) finv[i]=finv[i-1]*inv[i]%P;
    bruh[0]=1;
    for(int i=1;i<=n;i++) bruh[i]=fmul[i*2]*finv[i]%P*finv[i]%P*inv[i+1]%P;
    if(!m){printf("%lld\n",n&1?0:bruh[n/2]); return;}
    //读入+维护异或
    for(int i=1;i<=n;i++) b[i]=0;
    for(int i=0,l,r;i<m;i++)
    {
        scanf("%d%d",&l,&r);
        ll v=rng();
        b[l]^=v,
        b[r+1]^=v;
    }
    for(int i=1;i<=n;i++) b[i]^=b[i-1];
    //现在相同的b值代表着相同的线段，维护左右端点就能恢复出线段
    //LFT[i]:权值为i的线段的左端点
    //M[i]:权值为i的线段的编号
    std::map<ll,int> LFT,M; int cur=0;
    for(int i=1;i<=n;i++) if(!LFT.count(b[i])) LFT[b[i]]=i;
    M[0]=0;
    for(int i=n;i>=1;i--) if(LFT[b[i]])
        cur++,s[cur]={LFT[b[i]],i,-1},LFT[b[i]]=0;
    int p=0;
    for(int i=1;i<=cur;i++)
    {
        srt[p++]={s[i].l,s[i].r-s[i].l+1,i};
        srt[p++]={s[i].r,-(s[i].r-s[i].l+1),-i};
    }
    std::sort(srt,srt+p);
    static int stk[N];
    int top=0;
    //构造栈处理父亲
    stk[top++]=0;
    for(int i=0;i<p;i++)
    {
        if(srt[i].fa>0)
        {
            s[srt[i].fa].fa=stk[top-1];
            stk[top++]=srt[i].fa;
        }
        else --top;
    }
    //用fa构造树
    for(int i=0;i<=cur;i++) son[i].clear();
    for(int i=1;i<=cur;i++) son[s[i].fa].push_back(i);
    s[0]={1,n,-1};
    printf("%lld\n",dfs(0));
}
int main()
{
    int t; scanf("%d",&t);
    while(t--) once();
}
```


UPD 2023-8-13: 修正卡特兰数公式

---

## 作者：Gmt丶FFF (赞：3)

本题解的方法可能是最简单的？（但是有点人类智慧）

一道非常不错的题，并且难度也没有想象中那么大。

首先假设没有限制，那么答案即为卡特兰数第 $n\div2 $ 位，设 $m=\frac{n}{2}$，那么答案即为 $\frac{\binom{n}{m}}{m+1}$。

如果不知道上述结论那么建议先去学习（或复习一下）卡特兰数的意义。

接下来设 $C(x)$ 代表卡特兰数第 $x$ 位。 

那么假设有一个区间的限制，那么我们实际上就是将序列拆成了中间和两边，那么答案即为 $C(\frac{r-l+1}{2})\times C(\frac{n-(r-l+1)}{2})$。

一个区间限制的情况实际上就是一个区间包含另一个区间的情况（总区间包含一个限制区间）。

那么对于两个区间 $[l_1,r_1],[l_2,r_2]$ 相交，我们其实可以拆成不相交的三个区间，即为 $[l_1,l_2-1],[l_2,r_1],[r_1+1,r_2]$。

所以我们可以智慧的想象一下，就能发现，我们实际上可以从左往右扫描，并维护一个栈记录下标，遇到一个区间的右端点时，我们将栈回退直到栈中没有这个区间这个点。

至于回退栈的过程中，哪一些点分为一组作为贡献，这个操作我们可以再智慧的想象一下，发现我们将所有区间进行区间加操作后，在栈中连续值相同的下标为一组。

证明其实是显然的，因为假设有两个点值不同却在一组，那么在这两个点之间一定有一个左端点阻拦，那么就肯定不在一组了，如果有两个点值相同却不在一组，那么这两个点之间一定有一个右端点与左端点，并且左边那个点一定会被右端点弹出，那么就不存在这种情况，所以是正确的。

所以我们整理一下可得本题步骤。

一、先对于每个区间做一遍对这个区间的所有数 $+1$，这个可以用差分处理。

二、从左往右扫描，维护一个记录下标的栈。

三、遇到一个区间的右端点时，弹栈，直到栈中没有点在这个区间内。

四、弹出栈的点对其值进行分组，在栈中连续且值相同的下标分为一组，若这个组内的数为 $x$，那么贡献即为 $C(\frac{x}{2})$，所有贡献相乘可得到最终答案。

如果在途中发现一个区间为奇数，答案就赋为 $0$。

要我说，这个方法简单，是挺简单的，但并不是很好想到，因为因果关系不大强，硬说这个思路来源的话，那就是先画区间包含和相交的情况，然后对于这两种情况，找到其共同点，如果能想出用栈维护了，那么再找弹出栈的所有点的联系，可以模拟几个样例发现与包含这个下标的区间数有关，然后就解决了。

时间复杂度：$O(n)$。


```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<set>
#include<algorithm>
#define int long long
using namespace std;
const int N=2e6+5;
const int mod=998244353;
int quick_pow(int x,int y)
{
	int num=x,sum=1;
	while(y)
	{
		if(y&1)sum*=num,sum%=mod;
		num*=num;
		num%=mod;
		y>>=1;
	}
	return sum;
}
int n,k,frac[N],inv[N],a[N],st[N],cnt,f[N];
vector<int>b[N];
inline int C(int x,int y)
{
	return frac[x]*inv[y]%mod*inv[x-y]%mod;
}
struct node
{
	int l,r;
}t[N];
signed main()
{
	int T=1;
	scanf("%lld",&T);
	frac[0]=1;
	for(int i=1;i<=N-5;i++)frac[i]=frac[i-1]*i%mod;
	inv[N-5]=quick_pow(frac[N-5],mod-2);
	for(int i=N-6;i>=0;i--)inv[i]=inv[i+1]*(i+1)%mod;
	while(T--)
	{
		n=0;
		scanf("%lld%lld",&n,&k);
		for(int i=1;i<=n+1;i++)a[i]=0,b[i].clear();
		for(int i=1;i<=k;i++)scanf("%lld%lld",&t[i].l,&t[i].r),a[t[i].l]++,b[t[i].r+1].push_back(t[i].l);
		int sum=0,res=1;
		cnt=0;
		bool flag=1;
		for(int i=1;i<=n+1;i++)
		{
			int num1=a[i],num2=b[i].size();
			for(int j=0;j<num2;j++)
			{
				int tot=0,las=-1;
				while(st[cnt]>=b[i][j])
				{
					if(f[st[cnt]]!=las)
					{
						if(tot&1)flag=0;
						else tot/=2,res*=C(tot*2,tot)*frac[tot]%mod*inv[tot+1]%mod,res%=mod;
						tot=0;
					}
					las=f[st[cnt]];
					tot++;
					cnt--;
				}
				if(tot&1)flag=0;
				else tot/=2,res*=C(tot*2,tot)*frac[tot]%mod*inv[tot+1]%mod,res%=mod;
//				cout<<i<<" "<<tot<<" "<<res<<" "<<st[cnt]<<" "<<b[i][j]<<" ????\n";				
			}
			if(i>n)break;
			sum+=num1-num2;
			f[i]=sum;
			st[++cnt]=i;
//			cout<<i<<" "<<sum<<endl;
		}
		int tot=cnt;
		if(tot&1)flag=0;
		else tot/=2,res*=C(tot*2,tot)*frac[tot]%mod*inv[tot+1]%mod,res%=mod;
//		cout<<tot<<" "<<res<<" ????\n";
		if(!flag)res=0;
		printf("%lld\n",res);
	}
	return 0;
}
/*
1
28 5
1 12
3 20
11 14
4 9
18 19
*/
```


---

## 作者：BreakPlus (赞：2)

+ 对于一个长度为 $2n$ 的无限制括号串，其是合法匹配的种类数为 Catalan 数，${2n \choose n}-{2n \choose n-1}$。

+ 对于两个相交的限制，我们可以让相交部分独立，形成三个不相交的限制。

+ 但是对于包含关系，若 $A \subset B$，那么这个限制只能拆分成两个限制，还出现了非连续区间的限制。

+ 进一步发现，两个元素如果受到给出限制的编号的集合相同，就可以放在一起考虑。

+ 但是怎么记录并 check 这个编号集合？拆事件 + XOR Hash 即可。

```cpp
ll f[600005];
void init(){
	for(ll i=1;i<=300000;i++){
		f[2*i] = (comb.C(2*i, i) - comb.C(2*i, i-1) + mod) % mod;
	}
}
mt19937_64 rnd(19260817);
ll w[300005];
ll n,k,l[300005],r[300005],d[300005];
ll tmp[300005], cnt;
vector<ll>E[300005];
map<pair<ll,ll>,ll>M;
void solve(){
	cnt = 0; M.clear();
	n=read(), k=read();
	for(ll i=0;i<=n+1;i++) E[i].clear();
	for(ll i=1;i<=k;i++) w[i]=rnd();
	for(ll i=1;i<=k;i++){
		l[i]=read(), r[i]=read(); 
		E[l[i]].emplace_back(i); E[r[i]+1].emplace_back(-i);
	}
	ll now=0, cnt=0, ans=1, res=n;
	for(ll i=1;i<=n;i++){
		for(auto t: E[i]){
			if(t>0) now^=w[t], cnt++;
			else now^=w[-t], cnt--;
		}
		M[mkp(now,cnt)]++;
	}
	for(auto P: M){
		ans=ans*f[P.se]%mod;
	}
	printf("%lld\n",ans);
}
```

---

## 作者：Otue (赞：1)

前置知识：长度为 $2\times n$ 的括号序列的种数是卡特兰数第 $n$ 项。记**卡特兰数第 $n$ 项为 $C_n$**，为了下文方便这里给出 $C_1=1$，$C_2=2$。

考虑区间包含的情况。

要求两个区间 $[l_1,r_1]$ 和 $[l_2,r_2]$ 合法，满足 $l_1 \le l_2 \le r_2 \le r_1$。

只需这两个区间合法：

- $[l_2,r_2]$
- $[l_1,l_2-1] \cup [r_2+1,r_1]$

---

考虑区间相交的情况。

要求两个区间 $[l_1,r_1]$ 和 $[l_2,r_2]$ 合法，满足 $l_1 \lt l_2 \le r_1 \lt r_2$。

只需这三个区间合法：

- $[l_1,l_2-1]$
- $[l_2,r_1]$
- $[r_1+1,r_2]$

---

那么我们可以得出结论：设 $S_i$ 表示 $i$ 位置被哪些线段覆盖。**所有 $S_i(1\leq i \leq n)$ 相同的可以单独计算贡献**，最后所有方案相乘就是答案。


![](https://cdn.luogu.com.cn/upload/image_hosting/cguqtzss.png)

如上图，给出样例的第四组数据的简要分析。

会发现 $S_1=S_2=S_5=S_{10}$，即第 $1,2,5,10$ 的位置（$4$ 个）被编号 $1$ 的线段覆盖。

$S_3=S_4$，即第 $3,4$ （$2$ 个）的位置被编号为 $1,2$ 的线段覆盖。

$S_6=S_7=S_8=S_9$，即第 $6,7,8,9$ （$4$ 个）被编号为 $1,3$ 的线段覆盖。那么最终答案就是 $C_{\frac{4}{2}}\times C_{\frac{2}{2}}\times C_{\frac{4}{2}}=8$。


可以用 xor hashing 实现上述算法。

## 代码
```c++
#include <bits/stdc++.h>
using namespace std;

#define int long long
const int N = 3e5 + 5, mod = 998244353;

int t, n, k, a[N], fac[N], invfac[N], cat[N];
map<int, int> vis;

int qpow(int a, int k, int p) {
	int res = 1;
	while (k) {
		if (k & 1) res = res * a % p;
		a = a * a % p;
		k >>= 1;
	}
	return res;
}

int C(int n, int m) {
	if (n < m) return 0;
	return fac[n] * invfac[m] % mod * invfac[n - m] % mod;
}

signed main() {
	mt19937 rnd(time(0));
	cin >> t;
	fac[0] = invfac[0] = 1;
	for (int i = 1; i <= N - 5; i++) {
		fac[i] = fac[i - 1] * i % mod;
		invfac[i] = qpow(fac[i], mod - 2, mod);
	}
	for (int i = 1; i <= N - 5; i++) cat[i] = C(2 * i, i) * qpow(i + 1, mod - 2, mod) % mod;
	while (t--) {
		vis.clear();
		cin >> n >> k;
		for (int i = 1; i <= n; i++) {
			a[i] = 0;
		}
		for (int i = 1; i <= k; i++) {
			int l, r;
			cin >> l >> r;
			int t = rnd();
			a[l] ^= t, a[r + 1] ^= t; 
		}
		int t = rnd();
		a[1] ^= t, a[n + 1] ^= t; 
		for (int i = 1; i <= n; i++) {
			a[i] = a[i] ^ a[i - 1];
			vis[a[i]]++;
		}
		int ans = 1;
		for (auto i = vis.begin(); i != vis.end(); i++) {
			int cnt = i -> second;
			if (cnt % 2 == 1) ans = 0;
			else ans = ans * cat[cnt / 2] % mod;
		}
		cout << ans << endl;
	}
}
```

---

## 作者：Purslane (赞：1)

# Solution

最开始我的思想非常类似 CF 中的 hint：考虑如果两条不相等的相交括号串 $[l_1,r_1]$ 与 $[l_2,r_2]$（如果 $l_1 \neq l_2$，那么 $l_1 < l_2$；否则 $r_1 > r_2$），可以根据它们的两种基本相对关系——错开和包含来讨论出一些性质。

当 $[l_1,r_1]$ 包含 $[l_2,r_2]$ 的时候，根据括号串匹配的基本结论：一个匹配串不断匹配相邻的匹配的括号，这样操作下去始终还是匹配的括号串。因此我们得到：$[l_1,l_2-1] \cup [r_2+1,r_1]$ 是一个匹配括号串。

当 $[l_1,r_1]$ 和 $[l_2,r_2]$ 错开的时候，我们即将证明：$[l_1,l_2-1]$，$[l_2,r_1]$，$[r_1+1,r_2]$ 都是匹配串。假设把括号串转化为 $\pm 1$ 的序列，其前缀和为 $s_i$，则 $s_{l_1-1} = s_{r_1} \ge s_{l_2-1} \ge s_{l_1-1}$（这是括号串匹配的性质），于是得到了 $s_{l_1-1} = s_{r_1} = s_{l_2-1} = s_{r_2}$。于是得到了 $\forall l_1-1 \le i \le r_2$ 都有 $s_i \ge s_{l_1-1}$。综上所述，容易知道这三个串都满足匹配括号字符串的充要条件。

那么有一个很 Trival 的思路就是每次不断把相的串给裂开，这样你最后会形成一个树形结构（只有互相包含）。不过我个人在实现的时候几乎要抓狂了。

下面是官方 Solution 给的一个神秘的做法。我们发现，最后我们所要求的的极短的（也就是不能再拆开）的括号串，它们被覆盖的线段的集合是相同的，而且不同的线段的集合对应不同的括号串。

所以确定了所有位置的覆盖集合之后就可以用卡特兰数计算即可。

而这种覆盖就可以使用异或哈希来解决了。

> 为什么异或哈希在这里是对的？考虑事实上只有 $O(n)$ 中不同的自己覆盖。然而在 $2^{64}$ 位下随机 $t$ 个数的异或和为 $0$ 的概率为 $\dfrac{1}{2^{64}}$ （你分开考虑每一位）。所以出现问题的概率是很小的。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=6e5+10,MOD=998244353;
mt19937 myrand(time(NULL));
int T,n,k,mx=600000,frac[MAXN],inv[MAXN],pre[MAXN];
int qpow(int base,int p) {
	int ans=1;
	while(p) {
		if(p&1) ans=ans*base%MOD;
		base=base*base%MOD,p>>=1;
	}
	return ans;
}
int C(int u,int d) {return frac[d]*inv[u]%MOD*inv[d-u]%MOD;}
int Catalan(int n) {return (C(n,n+n)-C(n-1,n+n))%MOD;}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	frac[0]=1; ffor(i,1,mx) frac[i]=frac[i-1]*i%MOD;
	inv[mx]=qpow(frac[mx],MOD-2);
	roff(i,mx-1,0) inv[i]=inv[i+1]*(i+1)%MOD;
	cin>>T;
	while(T--) {
		cin>>n>>k;
		ffor(i,1,n) pre[i]=0;
		ffor(i,1,k) {
			int l,r;
			cin>>l>>r;
			int RAND=1ll*(myrand()%INT_MAX)*(myrand()%INT_MAX);
			pre[l]^=RAND,pre[r+1]^=RAND;
		}
		ffor(i,1,n) pre[i]^=pre[i-1];
		map<int,int> mp;
		ffor(i,1,n) mp[pre[i]]++;
		int ans=1;
		for(auto pr:mp) {
			if(pr.second&1) ans=0;
			else ans=ans*Catalan(pr.second/2)%MOD;	
		}
		cout<<(ans%MOD+MOD)%MOD<<'\n';
	}
	return 0;
}
```

PS：写这篇题解的时候有很多集训队选手在台下唱歌。很好的歌，使我的大脑旋转。

---

## 作者：pldzy (赞：1)


括号序列。

## Solution

显然括号序列的方案数可以使用卡特兰数 $O(n)$ 预处理。

考虑区间交的情况。那么我们可以把这两个相交的区间拆分成三份，首一份、重叠的一份、尾一份。

然后中间重叠的这一份一定是一个完整的括号序列，其方案数是可以直接求出来的。

经过简单推论，首一份与尾一份合起来（即不考虑中间重叠的一份）是一个完整的括号序列，其方案数亦可直接求出。

同时，易证这两个完整的括号序列是互不干扰的。

区间不相干的时候方案当然独立，直接方案数相乘即可。区间包含的时候和区间相交的情况同理。

所以，假设覆盖点 $i$ 的区间的集合为 $S_i$，易知所有 $S_i$ 相同的数实际上是构成一个完整的括号序列的。

所以最终的答案就是所有 $S_i$ 对应的括号序列方案数相乘取模即可。

维护这个 $S_i$ 相同的点，我们使用一个类似哈希的小技巧。它满足溢出之后依旧满足哈希性质。注意取 `rand()` 的时候要平方，因为 $n$ 比较大。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long
typedef long long ll;
typedef double db;
#define rep(i, a, b) for(int i = a; i <= b; ++i)
#define per(i, a, b) for(int i = a; i >= b; --i)
#define pii pair<int, int>
#define fr first
#define se second
#define pb push_back
const int maxn = 1e6 + 5, mod = 998244353;
int n, m, a[maxn], b[maxn], f[maxn];
int ans = 1;
map<int, int> cnt;

//mt19937 rnd(time(0)); 

inline int rd(){
	int x = 1, s = 0; char ch = getchar();
	while(ch < '0' or ch > '9'){
		if(ch == '-') x = -1; ch = getchar();
	}while(ch >= '0' and ch <= '9') s = s * 10 + ch - '0', ch = getchar();
	return x * s;
}
inline int pw(int x, int p){
	int res = 1; 
	while(p){
		if(p & 1) res = res * x % mod;
		p /= 2, x = x * x % mod;
	} return res;
}
inline void slv(){
	ans = 1; cnt.clear();
	n = rd(), m = rd();
	rep(i, 1, n) a[i] = b[i] = 0;
	rep(i, 1, m){
		int l = rd(), r = rd();
		int v1 = rand() * rand(), v2 = rand() * rand();
		a[l] += v1, a[r + 1] -= v1;
		b[l] ^= v2, b[r + 1] ^= v2;
	} a[1] += 1, b[1] ^= 1;
	rep(i, 1, n) a[i] += a[i - 1], b[i] ^= b[i - 1];
	rep(i, 1, n) cnt[a[i] * b[i]] += 1;
	rep(i, 1, n) if(cnt[a[i] * b[i]]){
		if(cnt[a[i] * b[i]] & 1) return printf("0\n"), void();
		ans = (ans * f[cnt[a[i] * b[i]] / 2]) % mod;
		cnt[a[i] * b[i]] = 0;
	}
	printf("%lld\n", (ans % mod + mod) % mod);
}

signed main(){
	srand(time(0)); 
	int _ =  maxn - 5;
	f[0] = f[1] = 1; 
	for(int i = 2; i <= _; ++i) f[i] = f[i - 1] * (4 * i - 2) % mod * pw(i + 1, mod - 2) % mod;
	
	int T; scanf("%lld", &T);
	while(T--) slv();
	return 0;
}
 
```


------------

Thanks for reading.

---

## 作者：EuphoricStar (赞：1)

每一步思路都非常自然的题。

考虑先从一些简单的 case 入手。

### 1. $k = 0$

设 $g_i$ 为长度为 $i$ 的合法括号串数。显然 $\forall i \nmid 2, g_i = 0$。对于偶数的 $i$，这是一个经典问题，$g_i$ 就是第 $\frac{i}{2}$ 项卡特兰数，因此 $g_i = \binom{i}{\frac{i}{2}} - \binom{i}{\frac{i}{2} - 1}$。

### 2. 区间互不相交

考虑把这些区间删去，那么剩下的括号也要构成合法括号串。设 $len_i$ 为第 $i$ 个区间的长度，$r$ 为区间长度总和，答案即为 $g_{n - r} \times \prod\limits_{i=1}^k g_{len_i}$。

### 3. 区间两两不交或包含

考虑建树，每个区间向**包含它且最短的区间**连边，那么会构成一片森林。设 $f_u$ 为第 $u$ 个区间**内部**的方案数，$r_u$ 为 $\sum\limits_{v \in son_v} len_v$，那么由互不相交的 case 我们得到 $f_u = g_{len_u - r_u}\prod\limits_{v \in son_u} f_v$。

### 4. 区间可能相交并且不包含

举个例子，如果 $[3, 6]$ 和 $[5, 8]$ 都是合法括号串，画出折线图，可以发现相当于 $[3, 4], [5, 6], [7, 8]$ 都是合法括号串。也就是我们要把相交的部分分裂出来。考虑异或哈希，每个区间赋一个随机权值，把区间里的每一个数都异或上这个权值，最后把每个权值**第一次出现的位置**和**最后一次出现的位置**拎出来作为新的区间。显然它们只会两两不交或包含了。

复杂度是线性对数。

[code](https://codeforces.com/contest/1830/submission/207643493)

---

## 作者：Hanx16Kira (赞：0)

# Hyperregular Bracket Strings

[Luogu CF1830C](https://www.luogu.com.cn/problem/CF1830C)

## Solution

先考虑所有区间两两不交的情况。发现如果保证所有区间内的括号序列合法，那么对于所有不在区间内的位置组成的括号序列也会是合法的。比如 `()(()(()))` 中 $[4,5]$ 是合法的，那么 $[1,3]\cup[6,10]$ 也是合法的。那么每个区间和剩余部分都是相互独立的。一个长度为 $2m$ 的括号序列个数为卡特兰数 $\displaystyle\binom{2m}{m}-\binom{2m}{m-1}$。那么最后答案就是所有区间的括号序列个数的乘积。

但是此处区间可能存在交。只考虑两个相交的区间看有什么性质。发现两个区间 $[l,r],[a,b](r\ge a,l\le a)$，可以看作是三个不交的区间 $[l,a),[a,r),[r,b]$ 的组合。这样就把所有区间全部拆成不交的了。如果直接枚举相交的区间显然不行，考虑给每个区间随机一个权值 $v$，然后将这个区间内的所有位置都异或上 $v$，最后如果两个位置权值相同那么覆盖这两个位置的区间集合也是相同的。因此统计每个权值出现的次数然后用卡特兰数乘起来即可。

区间异或使用差分，时间复杂度 $\mathcal O(n+k)$。

```cpp
mint fac[_N], ifac[_N];
void init(int n) {
    fac[0] = 1; For(i, 1, n) fac[i] = fac[i-1] * i;
    ifac[n] = 1 / fac[n]; Rof(i, n, 1) ifac[i-1] = ifac[i] * i;
}
mint binom(int x, int y) {
    return x < y || y < 0 ? 0 : fac[x] * ifac[y] * ifac[x-y];
}
mint cat(int n) {
    if (n & 1) return 0;
    return binom(n, n / 2) - binom(n, n / 2 - 1);
}
mt19937_64 rnd(9);
signed main() {
    cin.tie(0)->sync_with_stdio(0);
    int T; cin >> T;
    init(3e5);
    while (T--) {
        int N, M; cin >> N >> M;
        vector<u64> val(N + 2, 0);
        For(i, 1, M) {
            int l, r; cin >> l >> r;
            u64 v = rnd();
            val[l] ^= v, val[r+1] ^= v;
        }
        unordered_map<u64, int> mp;
        For(i, 1, N) val[i] ^= val[i-1], ++mp[val[i]];
        mint ans = 1;
        for (auto& pr: mp) ans *= cat(pr.second);
        cout << ans << '\n';
    }
}
```

---

## 作者：orz_z (赞：0)



考虑包含与相交的区间。

对于相交的两区间 $[l1,r1],[l2,r2]$，则只需区间 $[l1,l2],[l2,r1],[r1,r2]$ 都合法即可。

对于相互包含的两区间 $[l1,r1],[l2,r2]$（前区间包含后区间），则只需区间 $[l2,r2],[l1,l2]\cup [r2,r1]$ 都合法即可。

考虑判断所有条件都满足后，区间的拆分情况。

发现对于相交的，即将 $[l2,r1]$ 从两区间里拆分出来。

对于相互包含的，即将 $[l2,r2]$ 从两区间里拆分出来。

于是考虑哈希判断。

对于条件 $[l,r]$，对 $[l,r]$ 进行哈希将其分离出来即可。

对于最后的每个单独区间，我们只需要知道它的长度，开个桶统计即可。

长度为 $2n$ 的合法括号序列方案数为卡特兰数第 $n$ 项。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
typedef pair<int, int> pii;
typedef vector<int> vi;
#define F(i, a, b) for(int i = a; i <= (b); ++i)
#define F2(i, a, b) for(int i = a; i < (b); ++i)
#define dF(i, a, b) for(int i = a; i >= (b); --i)
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define Debug debug("Passing [%s] in LINS %d\n", __FUNCTION__, __LINE__)
#define pb push_back
#define fi first
#define se second
#define Mry debug("%.3lf MB\n", (&Mbe - &Med) / 1048576.0)
#define Try cerr << 1e3 * clock() / CLOCKS_PER_SEC << " ms\n";
typedef long long ll;
//namespace Fread {const int SIZE = 1 << 17; char buf[SIZE], *S, *T; inline char getchar() {if (S == T) {T = (S = buf) + fread(buf, 1, SIZE, stdin); if (S == T) return '\n';} return *S++;}}
//namespace Fwrite {const int SIZE = 1 << 17; char buf[SIZE], *S = buf, *T = buf + SIZE; inline void flush() {fwrite(buf, 1, S - buf, stdout), S = buf;} inline void putchar(char c) {*S++ = c;if (S == T) flush();} struct NTR {~NTR() {flush();}} ztr;}
//#ifdef ONLINE_JUDGE
//#define getchar Fread::getchar
//#define putchar Fwrite::putchar
//#endif
inline int ri() {
	int x = 0;
	bool t = 0;
	char c = getchar();
	while (c < '0' || c > '9') t |= c == '-', c = getchar();
	while (c >= '0' && c <= '9') x = (x << 3) + (x << 1) + (c ^ 48), c = getchar();
	return t ? -x : x;
}
inline void wi(int x) {
	if (x < 0) {
		putchar('-'), x = -x;
	}
	if (x > 9) wi(x / 10);
	putchar(x % 10 + 48);
}
inline void wi(int x, char s) {
	wi(x), putchar(s);
}
bool Mbe;
const int mod = 998244353;
const int mod2 = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll infll = 0x3f3f3f3f3f3f3f3f;
const int _ = 3e5 + 5;

int n, m, l[_], r[_], a[_], b[_], f[_];
map<pii, int> mp;
int qpow(int x, int y) {
	int r = 1;
	while(y) {
		if(y & 1) r = 1ll * r * x % mod;
		x = 1ll * x * x % mod, y >>= 1;
	} return r;
}
void solve() {
	mt19937 g(time(0) + rand());
	n = ri(), m = ri();
	F(i, 0, n + 2) a[i] = b[i] = 0; mp.clear();
	F(i, 1, m) l[i] = ri(), r[i] = ri();
	l[++m] = 1, r[m] = n;
	F(i, 1, m) {
		if((r[i] - l[i] + 1) & 1) {
			puts("0"); return;
		}		
		int x = g() % mod;
		a[l[i]] = (a[l[i]] + x) % mod, a[r[i] + 1] = (a[r[i] + 1] + mod - x) % mod;
		x = g() % mod2;
		b[l[i]] = (b[l[i]] + x) % mod2, b[r[i] + 1] = (b[r[i] + 1] + mod2 - x) % mod2;
	}
	F(i, 1, n) {
		a[i] = (a[i] + a[i - 1]) % mod;
		b[i] = (b[i] + b[i - 1]) % mod2;
		mp[make_pair(a[i], b[i])]++;
//		cout << a[i] << ' ';
	}
//	cout << '\n';
//	cout << f[2] << "@@\n";
	int ans = 1;
	for(auto v : mp) {
//		cout << v.se <<"!!\n";
		if(v.se & 1) {
			puts("0"); return;
		}
		ans = 1ll * ans * f[v.se / 2] % mod;
	} wi(ans, '\n');
}
bool Med;
signed main() {
	srand(time(0));
//	Mry;
	f[0] = f[1] = 1;
	F(i, 2, 300002) f[i] = 1ll * f[i - 1] * (4 * i - 2) % mod * qpow(i + 1, mod - 2) % mod;
	int T = ri();
	while(T--) solve();
//	Try;
}
```



---

