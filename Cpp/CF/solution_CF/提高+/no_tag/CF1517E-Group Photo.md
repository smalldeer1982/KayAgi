# Group Photo

## 题目描述

In the 2050 Conference, some people from the competitive programming community meet together and are going to take a photo. The $ n $ people form a line. They are numbered from $ 1 $ to $ n $ from left to right. Each of them either holds a cardboard with the letter 'C' or a cardboard with the letter 'P'.

Let $ C=\{c_1,c_2,\dots,c_m\} $ $ (c_1<c_2<\ldots <c_m) $ be the set of people who hold cardboards of 'C'. Let $ P=\{p_1,p_2,\dots,p_k\} $ $ (p_1<p_2<\ldots <p_k) $ be the set of people who hold cardboards of 'P'. The photo is good if and only if it satisfies the following constraints:

1. $ C\cup P=\{1,2,\dots,n\} $
2. $ C\cap P =\emptyset  $ .
3. $ c_i-c_{i-1}\leq c_{i+1}-c_i(1< i <m) $ .
4. $ p_i-p_{i-1}\geq p_{i+1}-p_i(1< i <k) $ .

Given an array $ a_1,\ldots, a_n $ , please find the number of good photos satisfying the following condition: $ $$$\sum\limits_{x\in C} a_x < \sum\limits_{y\in P} a_y. $ $ </p><p>The answer can be large, so output it modulo  $ 998\\,244\\,353$$$. Two photos are different if and only if there exists at least one person who holds a cardboard of 'C' in one photo but holds a cardboard of 'P' in the other.

## 说明/提示

For the first test case, there are $ 10 $ possible good photos satisfying the condition: PPPPP, CPPPP, PCPPP, CCPPP, PCCPP, PCPCP, PPPPC, CPPPC, PCPPC, PPPCC.

For the second test case, there are $ 7 $ possible good photos satisfying the condition: PPPP, PCPP, PCCP, PPPC, PCPC, PPCC, PCCC.

## 样例 #1

### 输入

```
3
5
2 1 2 1 1
4
9 2 2 2
1
998244353```

### 输出

```
10
7
1```

# 题解

## 作者：w33z8kqrqk8zzzx33 (赞：6)

首先给出一个显然的结论：合法方案基本上全是 `PC...CPC...PCP...PC` 形式。接下来是难点：不重复枚举。

分两类：

 1. `P...PC...C`（regex `P+C+`）
 2. `PC...CPC...PCP...PC`（regex `P?C+(PC)*P+C?`）

注意 2 类的中间 `C...C` 和 `P...P` 必须至少含有一个 `C` 和一个 `P`，否则可能退化为 `PC`，属于第一类。

接下来我们证明如果必须有 `C+` 和 `P+`，这两类 `P?C+(PC)*P+C?` 和 `P+C+` 覆盖所有可行方案。先证明任何不满足该正ce表达式的方案均不合法：

1. 假设中间存在 `PC` 长度大于 1 的混合段 `PCPCPC...PCPCPC`。第一类肯定不会包含这样的方案。接下来证明如果第二类包含当且仅当这个方案合法。
    - 假设左侧有不满足 `P?C+` 形式的部分。这意味着：
        1. 存在 `P` 但是它不在左边，也就是意味着两个 `C` 夹着一个 `P`：
            1. 如果该 `P` 右边仅有一个 `C`，则仍然为 `PC`+`PCPC...PCPC` 形式，并没违规正ce表达式 $\boxed{}$
            2. 否则 `P` 左边有一个 `C`，`P` 右边有两个 `C`，为 `CPCC` 之类的，不满足 `C` 间距递增条件 $\boxed{}$
        2. 存在多个在最左边的 `P`，为 `PP..PCPC` 之类的，不满足 `P` 间距递减条件 $\boxed{}$
        3. 不存在 `C`，变成 `PPCPC` 之类的，也不满足 `P` 间距递减条件 $\boxed{}$
    - 右边同理 $\boxed{}$
2. 假设有恰好一个 `PC`
    - 假设左侧不满足 `P?C+` 形式的部分，这意味着：
        1. 参见上述
        2. 参见上述
        3. 不存在 `C`：
            - 如果右侧有 `P`，变为 `PPC***P**`，不满足 `P` 间距递减要求 $\boxed{}$ (prop A)
            - 如果右侧没有 `P`，变为 `PPCC..CC`，退化为第一类 $\boxed{}$
    - 右侧同理 $\boxed{}$
3. 假设没有 `PC`
    - 假设右边不满足 `P?C+` 形式的部分，这意味着：
        1. 存在 `P` 但是它不在最左边，也就是两个 `C` 夹着一个 `P`：
            1. 如果该 `P` 右边仅有一个 `C`，产生 `PC`，与上述条件矛盾；$\boxed{}$
            2. 则必须为 `PPPPP`，`CPPPP`，`PCPPP` 形式：
                1. `PPPPP`
                    1. 如果右侧有 `P`，参见上述 prop A $\boxed{}$
                    2. 否则形成 `PPCC..CC`，退化为第一类 $\boxed{}$
                2. `CPPPP`
                    1. 如果右侧有 `C`，和 prop A 同理 $\boxed{}$
                    2. `CPP...PP` 并没违规正ce表达式 $\boxed{}$
                3. `PCPPP` 直接违规 `P` 间距递减条件 $\boxed{}$
        2. 左边有一车 `P`，退化为第一类 $\boxed{}$
        3. 不存在 `C`，并没违规正ce表达式 $\boxed{}$

证明任何满足正ce表达式的方案也合法很简单，直接查距离即可。

于是枚举 `(LR)*` 左端点，二分右断电即可。代码：

```cpp
#pragma GCC target("avx2")
#pragma GCC optimize("Ofast")
// writer: w33z8kqrqk8zzzx33
#include <bits/stdc++.h>
using namespace std;

#define iter(i, a, b) for(int i=(a); i<(b); i++)
#define rep(i, a) iter(i, 0, a)
#define rep1(i, a) iter(i, 1, (a)+1)
#define log(a) cerr<<"\033[32m[DEBUG] "<<#a<<'='<<(a)<<" @ line "<<__LINE__<<"\033[0m"<<endl
#define all(a) a.begin(), a.end()
#define fi first
#define se second
#define pb push_back
#define mp make_pair
 
using ll=long long;
using pii=pair<int, int>;
//#define int ll
const int MOD = 1000000007;

int ar[200005];
ll sfx[200015],pfx[200015],sfp[200015];
template<typename T>int flas(T f){
	if(!f(0))return -1;
	int ans=0;
	for(int i=17;i>=0;i--)if(f(ans|(1<<i)))ans|=(1<<i);
	return ans;
}
ll gud(int n){
	rep(i,n){
		sfx[i]=ar[i];
		pfx[i]=ar[i];if(i)pfx[i]+=pfx[i-1];
		if(i!=n-1)sfp[i]=ar[i]-ar[i+1];
	}
	rep(i,10)sfx[n+i]=sfp[n-1+i]=0;
	for(int i=n-1;i>=0;i--){
		sfx[i]+=sfx[i+1];
		sfp[i]+=sfp[i+2];
	}
	ll ans=0;
	for(int i=n;i>=0;i--){
		ll a=-sfx[i];if(i)a+=pfx[i-1];
		ans+=(a>0);
	}
	iter(l,1,n)ans+=flas([&](int i){return (l+2*i<n)&&(-pfx[l-1]+sfp[l]-sfp[l+2*i]+sfx[l+2*i]>0);})+1;
	iter(l,2,n)ans+=flas([&](int i){return (l+2*i<n)&&(-pfx[l-1]+sfp[l]-sfp[l+2*i]+sfx[l+2*i]+2*ar[0]>0);})+1;
	iter(l,1,n)ans+=flas([&](int i){return (l+2*i<n-1)&&(-pfx[l-1]+sfp[l]-sfp[l+2*i]+sfx[l+2*i]-2*ar[n-1]>0);})+1;
	iter(l,2,n)ans+=flas([&](int i){return (l+2*i<n-1)&&(-pfx[l-1]+sfp[l]-sfp[l+2*i]+sfx[l+2*i]+2*ar[0]-2*ar[n-1]>0);})+1;
	return ans%998244353;
}
signed main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t;cin>>t;
	while(t--){
		int n;cin>>n;
		rep(i,n)cin>>ar[i];
		cout<<gud(n)<<endl;
	}
}
```

---

## 作者：MyukiyoMekya (赞：3)

根据 $c_i-c_{i-1}\le c_{i+1}-c_i$ 和 $p_i-p_{i-1}\ge p_{i+1}-p_i$ 不难发现最终的序列一定是这样的：

```plain
(C/P) + CCC...CCCC + PCPCPC...PCPCPC + PPP...PPPP + (C/P)
```

或者是这样的：

```plain
PPP...PPPP + CCC...CCCC
```

大力分类讨论，然后双指针就好了，我这里写了二分，$\mathcal O(n\log n)$。

注意 $n$ 比较小的时候避免麻烦的细节处理可以直接跑指数级暴力。

```cpp
// This code wrote by chtholly_micromaker(MicroMaker)
#include <bits/stdc++.h>
#define reg register
#define int long long
#define mem(x,y) memset(x,y,sizeof x)
#define ln std::puts("")
#define lsp std::putchar(32)
#define pb push_back
const int MaxN=2e5+50;
const int p=998244353;
template <class t> inline void read(t &s){s=0;
reg int f=1;reg char c=getchar();while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
while(isdigit(c))s=(s<<3)+(s<<1)+(c^48),c=getchar();s*=f;return;}
template<class t,class ...A> inline void read(t &x,A &...a){read(x);read(a...);}
template <class t> inline void write(t x){if(x<0)putchar('-'),x=-x;
int buf[21],top=0;while(x)buf[++top]=x%10,x/=10;if(!top)buf[++top]=0;
while(top)putchar(buf[top--]^'0');return;}
inline int lowbit(int x){return x&(-x);}
int a[MaxN],b[MaxN],n,lim,pst,ced,ped;
int tr[2][MaxN];
inline int ask(int *a,int l,int r)
{
	if(l>r)return 0;
	return a[r]-a[l-1];
}
inline int calc(int n,int st)
{
	lim-=st;
	std::memset(tr[0],0,sizeof(int)*(n+5));
	std::memset(tr[1],0,sizeof(int)*(n+5));
	for(int i=1;i<=n;++i)tr[i&1][i]+=b[i];
	for(int i=1;i<=n;++i)tr[0][i]+=tr[0][i-1],tr[1][i]+=tr[1][i-1];
	reg int ans=0,s=0;
	{
		reg int pos=0;
		while(pos+2<=n&&s+b[pos+2]<lim)pos+=2,s+=b[pos];
		if(pos==n&&ced)pos-=2;
		if(!pst)
			ans+=pos/2;
		else if(pos==2&&n<=2&&!ped)
			++ans;
	}
	s=0;
	for(int i=1;i<=n;++i)
	{
		s+=b[i];
		reg int l=i,r=n,mid,res=i-2;
		while(l<=r)
		{
			mid=(l+r)>>1;
			if(s+ask(tr[i&1],i+2,mid)<lim)
				res=mid,l=mid+1;
			else
				r=mid-1;
		}
		if((res+i)&1)--res;
		if(ced&&res==n)res-=2;
		if(res>=i)ans+=(res-i+2)/2;
	}
	if(pst&&ced)
	{
		s=0;
		if(s<lim)++ans;
		reg int ccnt=0;
		for(int i=n;i;--i)
		{
			s+=b[i];
			if(s<lim)++ccnt;
		}
		ans+=ccnt;
	}
	lim+=st;
	if(!(pst&&ced)&&st<lim)++ans;
	return ans;
}
inline void solve()
{
	reg int ans=0;
	for(int m=0;m<(1<<n);++m)
	{
		std::vector<int> C,P;
		for(int i=0;i<n;++i)
			if(m&(1<<i))
				C.pb(i);
			else
				P.pb(i);
		int flg=1;
		for(int i=0;i<(int)C.size()-2;++i)
			if(C[i+1]-C[i]>C[i+2]-C[i+1])
				flg=0;
		for(int i=0;i<(int)P.size()-2;++i)
			if(P[i+1]-P[i]<P[i+2]-P[i+1])
				flg=0;
		reg int s=0;
		for(int i=0;i<n;++i)
			if(m&(1<<i))
				s+=a[i+1];
		if(s>=lim)
			flg=0;
		ans+=flg;
	}
	write(ans),ln;
}
inline void work()
{
	lim=0;
	read(n);
	for(int i=1;i<=n;++i)
		read(a[i]),lim+=a[i];
	lim=(lim+1)/2;
	if(n<=6)
		return solve();
	reg int ans=0;
	for(int i=2;i<n;++i)
		b[i-1]=a[i];
	pst=ped=1,(ans+=calc(n-2,0)%p)%=p,pst=ped=0;
	ped=1,(ans+=calc(n-2,a[1])%p)%=p,ped=0;
	pst=ced=1,(ans+=calc(n-2,a[n])%p)%=p,pst=ced=0;
	ced=1,(ans+=calc(n-2,a[1]+a[n])%p)%=p,ced=0;
	write(ans),ln;
}
signed main(void)
{
	int t;read(t);
	while(t--)
		work();
	return 0;
}
```



---

## 作者：E1_de5truct0r (赞：1)

分类讨论诈骗题。

首先手玩一下，答案不会出现 `P` 和 `C` 相隔超过一个的交错排列情况，因为类似 `PCCCPCCP` 的情况根本就不合法。

所以答案有几种情况：

- `P...PPCC...C`：预处理前后缀和算一下。

- `C...CCPP...P`：同上。

- `C...CPCPCPCPP....P`：我们考虑枚举连续的 `C` 这一段和连续的 `CPCPCP...` 这一段的分界点，则 `CPCP...CP` 和 `P...PPP` 的分界点可以二分求得满足 $sump>sumc$ 的最远位置。这个可以通过预处理下标为奇数或偶数的 $a$ 的前缀和来 $O(1)$ 判断。显然这个是具有单调性的，所以二分出这个位置 $x$ 之后，这个分界点可以在 $i+1$ 到 $x$ 任意取（隔两个可以取一个），加上对应贡献即可。

	不过注意到如果分界点取在 $i+1$，会生成形如 `CC...CCCPP...PP` 的序列，应减去重复贡献。
    
- `PC...CCPCPCPP...PP` 或 `CC....CCPCPCPCPP...PC` 或 `PC...CCPCPCPCP...PC`：同上可以使用二分，调整一下二分时候算的 $sump$ 和 $sumc$ 即可，并且不需要减去重复贡献。

你可能发现了，取模是诈骗的，最终答案是 $n^2$ 级别的。

代码看着有点长，不过其实就是一个二分再复制三遍，稍微改改边界即可。然后为了避免二分上界麻烦的计算，可以把上界设为 $\lfloor\frac{n}{2}\rfloor+3$，如果二分的时候发现 $i+2mid-1>n$ 就 `r--`，这样就行了。

[Code & Submission](https://codeforces.com/contest/1517/submission/229857439)

---

## 作者：7KByte (赞：0)

初步观察可以看出不存在 $\texttt{CCPCC}$ 或 $\texttt{PPCPP}$ 这样的子串。

但是可以存在 $\texttt{PCPCPC}\cdots$ 这样的子串。

我们把 $\texttt{PCPC}\cdots\texttt{PCPC}$ 作为中心，发现左边可以再接一段$\texttt{C}$，右端可以再接一段 $\texttt{P}$。其中左边可以不接$\texttt{C}$，右边可以不接$\texttt{P}$，也可以只存在$\texttt{CCC}\cdots\texttt{PPP}$。我们称这样形式的串为标准串。

如果不以$\texttt{PCPC}\cdots\texttt{PCPC}$ 作为中心，也就是不存在这样的子串，不难发现一定是$\texttt{PPP}\cdots\texttt{CCC}$这样的形式。

但是手盘样例发现过不去。因为我们可以在标准串左边再接一个$\texttt{P}$，右边再接一个$\texttt{C}$。

这样我们可以固定第一个为$\texttt{C/P}$，最后一个为$\texttt{C/P}$。

但是固定首尾后并不是所有的标准串都可以填进去，比如$\texttt{PCP}$是一个标准串，但是加上首尾之后$\texttt{PPCPP}$并不满足条件。

因为我们还有还有一个限制条件，固定第一位为$\texttt{P}$，则第二位一定是$\texttt{C}$，固定最后一位是$C$，则倒数第二位一定是$\texttt{P}$。

然后再统计没有固定的位置有多少满足条件的标准串。

那么如何求出标准串个数呢？

首先 $\sum C< \sum P$ 等价于 $2\times \sum C < \sum a_i$ 。

得到形式 $\sum C \le lim$，其中 $lim$ 是一个常数。

然后我们枚举 $\texttt{PCPC}\cdots$ 和 $\texttt{PP}\cdots$ 的断点，然后发现 $\texttt{CC} \cdots$ 和 $\texttt{PCPC}\cdots $的断点具有单调性，这可以通过二分或双指针解决。

再次强调，形如 $\texttt{P}\cdots\texttt{P}$ 和$\texttt{C}\cdots \texttt{C}$ 和 $\texttt{PC}\cdots\texttt{PC}$
 的串也是标准串。
 
细节特别恶心，可能是我想复杂了？

```cpp
//By SharpnessV
//no copy
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 200005
#define int long long 
using namespace std;
int n,a[N],s[N],u[N];
int g(int l,int r){
	if((l&1)!=(r&1))return u[r]-u[l-1];
	return u[r]-u[max(l-2,0LL)];
}
int calc(int lim,int L,int R){
	int ans=0;
	if(L>R+1)return 0;
	if(lim>=0)ans++;
	rep(i,L,R){
		if(i&1){
			if(g(L,i)<=lim)ans++;
			int l=2,r=i/2,ed=1;
			if(L==2)l=1,ed=0;
			while(l<=r){
				int mid=(l+r)>>1;
				if(u[i]-u[mid*2+1]+s[mid*2+1]-s[L-1]<=lim)ed=mid,l=mid+1;
				else r=mid-1;
			}
			ans+=ed-1+(L!=2);
		}
		else{
			if(g(L,i)<=lim)ans++;
			int l=2,r=i/2,ed=1;
			while(l<=r){
				int mid=(l+r)>>1;
				if(u[i]-u[mid*2]+s[mid*2]-s[L-1]<=lim)ed=mid,l=mid+1;
				else r=mid-1;
			}
			ans+=ed-1;
		}
	}
	return ans;
}
void solve(){
	scanf("%lld",&n);
	rep(i,1,n)scanf("%lld",&a[i]),s[i]=s[i-1]+a[i];
	if(n==1){puts("1");return;}
	if(n==2){printf("%lld\n",(a[1]!=a[2])+1LL);return;}
	u[1]=a[1];rep(i,2,n)u[i]=u[i-2]+a[i];
	int ans=0,lim=(s[n]+1)/2-1;
	rep(i,1,n)ans+=(s[n]-s[i])<=lim;
	ans+=calc(lim-a[2],3,n-1);
	ans+=calc(lim-a[1],2,n-1);
	ans+=calc(lim-a[1]-a[n],2,n-2);
	ans+=calc(lim-a[2]-a[n],3,n-2);
	printf("%lld\n",ans%998244353);
}
signed main(){
	int T;scanf("%lld",&T);
	while(T--)solve();
	return 0;
}
```

---

