# [USACO25FEB] The Best Subsequence G

## 题目描述

Farmer John 有一个长为 $N$ 的位串（$1 \leq N \leq 10^9$），初始时全部为零。

他将首先按顺序对字符串执行 $M$ 次更新（$1 \leq M \leq 2 \cdot 10^5$）。每次更新会翻转从 $l$ 到 $r$ 的每个字符。具体地说，翻转一个字符会将其从 $0$ 变为 $1$，或反之。

然后，他会进行 $Q$ 次查询（$1 \leq Q \leq 2 \cdot 10^5$）。对于每个查询，他要求你输出由从 $l$ 到 $r$ 的子串中的字符组成的长为 $k$ 的字典序最大子序列。如果你的答案是一个位串 $s_1s_2 \dots s_k$，则输出 $\sum_{i=0}^{k-1} 2^i \cdot s_{k-i}$（即将其解释为二进制数时的值）模 $10^9+7$ 的余数。

一个字符串的子序列是可以从中通过删除一些或不删除字符而不改变余下字符的顺序得到的字符串。

我们知道，字符串 $A$ 的字典序大于长度相等的字符串 $B$，当且仅当在第一个 $A_i \neq B_i$ 的位置 $i$ 上（如果存在），我们有 $A_i > B_i$。

## 说明/提示

样例 1 解释：

在执行 $M$ 次操作后，位串为 $10101$。

对于第一个查询，长度为 $5$ 的子序列仅有一个，$10101$，其解释为 $1 \cdot 2^4 + 0 \cdot 2^3 + 1 \cdot 2^2 + 0 \cdot 2^1 + 1 \cdot 2^0 = 21$。

对于第二个查询，长度为 $4$ 的不同的子序列有 $5$ 个：$0101$，$1101$，$1001$，$1011$，$1010$。字典序最大的子序列为 $1101$，其解释为 $1 \cdot 2^3 + 1 \cdot 2^2 + 0 \cdot 2^1 + 1\cdot 2^0 = 13$。

对于第三个查询，字典序最大的序列是 $111$，其解释为 $7$。

样例 3 解释：

确保输出答案对 $10^9+7$ 取模。


- 测试点 $4$：$N \leq 10, Q \leq 1000$。
- 测试点 $5$：$M \leq 10$。
- 测试点 $6\sim 7$：$N, Q \leq 1000$。
- 测试点 $8\sim 12$：$N \leq 2 \cdot 10^5$。
- 测试点 $13\sim 20$：没有额外限制。

## 样例 #1

### 输入

```
5 3 9
1 5
2 4
3 3
1 5 5
1 5 4
1 5 3
1 5 2
1 5 1
2 5 4
2 5 3
2 5 2
2 5 1```

### 输出

```
21
13
7
3
1
5
5
3
1```

## 样例 #2

### 输入

```
9 1 1
7 9
1 8 8
```

### 输出

```
3```

## 样例 #3

### 输入

```
30 1 1
1 30
1 30 30```

### 输出

```
73741816```

# 题解

## 作者：Po7ed (赞：2)

拜谢 @happy_zero 大神提供的单 log 做法。

![](https://cdn.luogu.com.cn/upload/image_hosting/7qirk10b.png)

先将修改差分处理，形成若干连续段。

考虑答案的形态。由于是给定子串的一个长度为 $k$ 的子序列，且要求字典序最大，考虑一个理想的情况，即子串内 $1$ 的个数大于 $k$，那么答案子序列所有元素均为 $1$。

当 $1$ 不够用的时候，从后往前接受 $0$。也就是说，答案的形态是前半段全是 $1$，后半段是给定子串的一个后缀。

考虑如何找到这个后缀。由于子串内 $1$ 的个数 $c_1$ 已经确定，需要的 $0$ 的个数 $n_0$ 也确定，即 $n_0=k-c_1$。而需要的 $0$ 均由后缀提供，所有后缀中 $0$ 的出现次数有单调性，可以二分。

如果直接二分后缀，需要再二分找到其属于哪个连续段，复杂度达到线性对数平方。

这时候我们直接二分后缀所属连续段，然后就可以 $O(1)$ 确定后缀位置。复杂度线性对数。

::::success[代码]
```cpp
#include <bits/stdc++.h>

using std::cin;
typedef long long ll;
constexpr int N=2e5+114,mod=1e9+7;
int n,m,q;
std::map<int,int> c; // 端点
std::vector<int> v,s; // 端点、前缀 0 数量
std::vector<ll> p; // 前缀和
int t;

ll qpow(ll x,ll y)
{
	ll r=1;
	for(;y;x=1ll*x*x%mod,y/=2)if(y&1)r=1ll*r*x%mod;
	return r;
}

int main()
{
	cin.tie(nullptr)->sync_with_stdio(false);
	cin>>n>>m>>q;
	c[1]=c[n+1]=2;
	for(int i=1,l,r;i<=m;i++)
	{
		cin>>l>>r;
		c[l]^=1,c[r+1]^=1;
	}
	t=c[1]&1; // 第一块颜色
	for(auto [x,y]:c)if(y)
	{
		v.push_back(x);
	}
	s.resize(v.size()),p.resize(v.size());
	if(t)s[0]=0,p[0]=(qpow(2,v[1]-v[0])+mod-1)%mod;
	else s[0]=v[1]-v[0],p[0]=0;
	for(int i=1,j=t^1;i<v.size()-1;i++,j^=1) // 计算前缀 0 数量和前缀和
	{
		if(j)
		{
			s[i]=s[i-1];
			p[i]=(1ll*(p[i-1]+1)*qpow(2,v[i+1]-v[i])+mod-1)%mod;
		}
		else
		{
			s[i]=s[i-1]+v[i+1]-v[i];
			p[i]=1ll*p[i-1]*qpow(2,v[i+1]-v[i])%mod;
		}
	}
	// 属于哪块
	auto bel=[](int x){return std::upper_bound(v.begin(),v.end(),x)-v.begin()-1;};
	for(int l,r,k;q--;)
	{
		cin>>l>>r>>k,l--;
		int L=bel(l),R=bel(r);
		int lc1=~L?(t^L&1?l-s[L]:v[L+1]-1-s[L]):0; // l 前缀 1 数量
		int rc1=t^R&1?r-s[R]:v[R+1]-1-s[R]; // r 前缀 1 数量
		int c1=rc1-lc1; // [l,r] 1 数量
		int n0=k-c1; // 需要的 0 的数量
		if(n0<=0) // 不需要 0
		{
			printf("%d\n",(qpow(2,k)+mod-1)%mod);
		}
		else
		{
			int ql=std::max(L,0)-1,qr=R,rc0=r-rc1,mid;
			while(ql+1<qr) // 二分分界点在那一块
			{
				mid=(ql+qr)/2;
				(s[mid]>=rc0-n0?qr:ql)=mid;
			}
			//                                 分界点
			int p0=v[qr+1]-1,t0=n0-(rc0-s[qr]),p1=p0-t0;
			int len=r-p1,l1=k-len;
			printf("%d\n",((1ll*(qpow(2,l1)+mod-1)*qpow(2,len)+ // 前面的 1
							1ll*(R?p[R-1]:0)*qpow(2,r-v[R]+1)+ // r 整块前缀和
							(t^R&1?qpow(2,r-v[R]+1)+mod-1:0) // r 散块前缀和
							-1ll*(qr?p[qr-1]*qpow(2,v[qr]-1-r):0) // 整块前缀和
							-1ll*(t^qr&1?qpow(2,p1-v[qr]+1)+mod-1:0)*qpow(2,p1-r) // r 散块前缀和
			)%mod+mod)%mod);
		}
	}
}
```
::::

以防有人不知道怎么下[数据](https://usaco.org/current/data/prob2_gold_feb25.zip)。

---

## 作者：I_will_AKIOI (赞：2)

### 思路

考虑最大化子序列的字典序。

在区间 $[l,r]$ 中，我们肯定要尽可能在前面多选 $1$。但是当选了一个 $1$ 之后，即使选上后面所有的数都选了，也达不到 $k$ 个，就不合法了。因此考虑二分，找到一个最优决策点，选上这个点前面的所有 $1$，如果数量不够，那么就把这个点之后的选上作为填补。也就是求满足 $cnt_{mid}+r-mid\ge k$ 的最大的 $mid$，其中 $cnt_{mid}$ 表示 $[l,mid]$ 之间 $1$ 的个数。

然后前面区间异或，由于我认为离散化比较困难，所以直接动态开点线段树维护，维护每个区间 $1$ 的个数和二进制数值，后者按照线段树维护哈希的方法进行合并。

时间复杂度 $O(m\log n+q\log^2 n)$，有点紧张，但尚可接受。对于空间复杂度，我们需要区间查询 $q\log^2 n $ 次，每次都要新建节点，导致空间复杂度很高。因此考虑优化。

### 空间复杂度优化

+ 别 `#define int long long`。

+ 观察到是修改之后再查询，因此我们可以对线段树上的叶子节点进行特判，直接返回叶子管辖的区间和查询区间的交集，空间复杂度的问题就解决了，同时还优化了一定的常数。

但是线段树常数过大，过不了，还需优化一下常数。

### 常数优化

+ 快读快写。

+ 计算哈希值的时候，我们需要求 $2^n$。由于底数固定，可以考虑光速幂把求 $2^n$ 从 $O(\log n)$ 优化到 $O(\sqrt{mod})$ 预处理，$O(1)$ 查询。具体地，预处理 $2^0,2^1\dots 2^{\sqrt{mod}}$ 和 $2^{2\sqrt{mod}}$，$2^{3\sqrt{mod}}\dots 2^{mod}$。然后就能快速解决问题了。

常数很大，可能过不了，我用 C++98 交了十几发才过。

```cpp
#include<bits/stdc++.h>
#define Pow(x) ((long long)p2[(x)/block]*p1[(x)%block]%mod)
#define mod 1000000007
#define N 200005
using namespace std;
struct Node{int len,Hash;};
struct Data
{
	int ls,rs,sum,len,Hash;
	bool tag;
}t[N*24];
int n,m,q,len,minn,maxx,cnt=1,block,p1[N],p2[N];
int read()
{
	int x=0;
	char c=getchar();
	while(c<'0'||c>'9') c=getchar();
	while(c>='0'&&c<='9') x=x*10+c-48,c=getchar();
	return x;
}
void write(int x)
{
	if(x>9) write(x/10);
	putchar(x%10+48);
	return;
}
void maketag(int k)
{
	t[k].tag^=1;
	t[k].sum=t[k].len-t[k].sum;
	t[k].Hash=Pow(t[k].len)-1-t[k].Hash;
	return;
}
void pushdown(int k)
{
	if(!t[k].tag) return;
	maketag(t[k].ls);
	maketag(t[k].rs);
	t[k].tag=0;
	return;
}
void update(int k,int l,int r,int ql,int qr)
{
	if(ql<=l&&r<=qr)
	{
		maketag(k);
		return;
	}
	int mid=l+r>>1;
	if(!t[k].ls)
	{
		t[k].ls=++cnt;
		t[t[k].ls].len=mid-l+1;
	}
	if(!t[k].rs)
	{
		t[k].rs=++cnt;
		t[t[k].rs].len=r-mid;
	}
	pushdown(k);
	if(ql<=mid) update(t[k].ls,l,mid,ql,qr);
	if(qr>mid) update(t[k].rs,mid+1,r,ql,qr);
	t[k].sum=t[t[k].ls].sum+t[t[k].rs].sum;
	t[k].Hash=((long long)t[t[k].ls].Hash*Pow(t[t[k].rs].len)+t[t[k].rs].Hash)%mod;
	return;
}
int query1(int k,int l,int r,int ql,int qr)
{ 
	if(ql<=l&&r<=qr) return t[k].sum;
	if(!t[k].ls&&!t[k].rs)
	{
		if(!t[k].sum) return 0;
		minn=max(l,ql);
		maxx=min(r,qr);
		return maxx-minn+1;
	}
	int mid=l+r>>1,res=0;
	pushdown(k);
	if(ql<=mid) res+=query1(t[k].ls,l,mid,ql,qr);
	if(qr>mid) res+=query1(t[k].rs,mid+1,r,ql,qr);
	return res;
}
Node query2(int k,int l,int r,int ql,int qr)
{
	if(ql<=l&&r<=qr) return Node{t[k].len,t[k].Hash};
	if(!t[k].ls&&!t[k].rs)
	{
		Node res;
		minn=max(l,ql);
		maxx=min(r,qr);
		res.len=maxx-minn+1;
		if(!t[k].sum) res.Hash=0;
		else res.Hash=Pow(maxx-minn+1)-1;
		return res;
	}
	int mid=l+r>>1,check=0;
	Node res;
	pushdown(k);
	if(ql<=mid)
	{
		res=query2(t[k].ls,l,mid,ql,qr);
		check=1;
	}
	if(qr>mid)
	{
		Node now=query2(t[k].rs,mid+1,r,ql,qr);
		if(!check) res=now;
		else
		{
			res.Hash=((long long)res.Hash*Pow(now.len)+now.Hash)%mod;
			res.len+=now.len;
		}
	}
	return res;
}
signed main()
{
	n=read(),m=read(),q=read();
	block=sqrt(mod);
	p1[0]=p2[0]=1;
	for(int i=1;i<=block;i++) p1[i]=p1[i-1]*2%mod;
	for(int i=1;i<=block;i++) p2[i]=(long long)p2[i-1]*p1[block]%mod;
	t[1].len=n;
	for(int i=1;i<=m;i++)
	{
		int x,y;
		x=read(),y=read();
		update(1,1,n,x,y);
	}
	for(int i=1;i<=q;i++)
	{
		int x,y,z,res=0;
		x=read(),y=read(),z=read();
		int l=x-1,r=y,mid,sum,tmp;
		while(l<r)
		{
			mid=l+r+1>>1;
			tmp=query1(1,1,n,x,mid);
			if(tmp+(y-mid)>=z) l=mid;
			else r=mid-1;
		}
		if(x>l) sum=0;
		else sum=tmp;
		if(z<=sum) write(Pow(z)-1);
		else
		{
			z-=sum;
			res=Pow(sum)-1;
			Node w=query2(1,1,n,l+1,min(y,l+z));
			res=((long long)res*Pow(w.len)+w.Hash)%mod;
			write((res+mod)%mod);
		}
		putchar('\n');
	}
	return 0;
}
```

---

## 作者：Departure_ (赞：2)

离线操作并排序可得所有极长 $0/1$ 块，容易想到答案由两部分组成：

- 一个前缀中的所有 $1$，设其右端点所属块为 $U$。
- 一个后缀，设其左端点所属块为 $V$。

记 $L,R$ 为 $l,r$ 所属块，记 $s(i,j)$ 为第 $i\sim j$ 个块的 popcnt 之和，不妨略去两种情况：

- $L=R$。
- $s(L,R)\le k$。

则 $U+1=V$。记 $c(i)$ 为第 $i$ 个块是 $0$ 块还是 $1$ 块，先对 $c(L)$ 分讨：

- 若 $c(L)=0$，对答案没有影响。
- 若 $c(L)=1$，显然全选。

记 $a(i)$ 为第 $i$ 个块的左端点。考虑二分出 $U$，显然 $c(U)=1$。接下来对 $V=U+1$ 分讨：

- 若 $V=R$，补上剩下的 $0$ 即可。
- 若 $V\ne R$，显然要在 $V$ 中取若干个 $0$，并取完 $[a(V+1),r]$。

于是，我们需要维护：

- 关于块的前缀 popcnt 之和 $S_i$，则 $s(i,j)=S_j-S_i$。
- 关于块的后缀转化成二进制后的值之和 $W_i$，则第 $i\sim j$ 个块转化成二进制后的值 $w(i,j)=\dfrac{W_i-W_{j+1}}{2^{n-a(j+1)+1}}$。

时间复杂度 $\Theta((m+Q)\log n)$。

```cpp
#include<iostream>
#include<algorithm>
#include<queue>
#include<cassert>
#include<numeric>
#include<array>
#include<bitset>
#include<map>
constexpr static void tomin(auto&x,auto&&y){if(y<x)x=y;}
constexpr static void tomax(auto&x,auto&&y){if(y>x)x=y;}
constexpr static void fin(auto&x){signed c=0,f=0;do if(c==45)f=1;while(c=getchar(),c<48||c>57);x=0;do x=(x<<1)+(x<<3)+(c^48);while(c=getchar(),c>=48&&c<=57);if(f)x=-x;}
constexpr static void fot(auto x){signed d[40],l=-1;if(x<0)x=-x,putchar(45);do d[++l]=(x%10)^48;while(x/=10);do putchar(d[l]);while(~--l);putchar(32);}
using namespace std;
#define long        long long
#define pb          push_back
#define ve          vector
#define fi          first
#define se          second
#define pii         pair<int,int>
#define all(x)      (x).begin(),(x).end()
#ifndef BUG
#define bug(x)      ({})
#define bua(a,l,r)  ({})
#else
#define bug(x)      ({cout<<":"<<__LINE__<<": ";x;cout<<endl;({});})
#define bua(a,l,r)  ({cout<<#a": ";for(signed i##END=(l),j##END=(r);i##END<=j##END;i##END++)cout<<a[i##END]<<' ';cout<<endl;({});})
#endif
#ifdef  FIO
auto FI=freopen("1.in","r",stdin);
auto FO=freopen("1.out","w",stdout);
#endif

constexpr int maxn=4e5+10,mod=1e9+7;
constexpr int fpw(int a,int b,int res=1){
    for(;b;b>>=1,a=1ll*a*a%mod)
        if(b&1)res=1ll*res*a%mod;
    return res;
}

int n,m,Q,cnt;
int a[maxn],c[maxn],s[maxn],w[maxn];

int getpos(int lid,int rid,int y,int& k){
    auto chk=[&](int mid){return s[mid]-s[lid]<=k&&s[mid]-s[lid]+y-a[mid+1]+1>=k;};
    int l=lid+1,r=rid-1,res=lid;
    while(l<=r)if(int mid=(l+r)>>1;chk(mid))res=mid,l=mid+1;else r=mid-1;
    k-=s[res]-s[lid];
    return res;
}

int solve(int x,int y,int k){
    int lid=upper_bound(a+1,a+1+cnt,x)-a-1;
    int rid=upper_bound(a+1,a+1+cnt,y)-a-1;
    if(lid==rid)return c[lid]==0?0:fpw(2,k)-1;
    int tot=s[rid-1]-s[lid]+c[lid]*(a[lid+1]-x)+c[rid]*(y-a[rid]+1);
    if(tot>=k)return fpw(2,k)-1;
    int ans=0;
    if(c[lid]==0)tomin(k,y-a[lid+1]+1);
    else{
        int t=min(a[lid+1]-x,k);
        ans=(fpw(2,t)-1)%mod;
        k-=t;
        if(k==0)return ans;
    } 
    int res=lid+1==rid?lid:getpos(lid,rid,y,k);
    ans=1ll*ans*fpw(2,s[res]-s[lid])%mod;
    ans=(ans+fpw(2,s[res]-s[lid])-1)%mod;
    if(++res==rid){
        ans=1ll*ans*fpw(2,k)%mod;
        if(c[res]==1)ans=(ans+fpw(2,k)-1)%mod;
        return ans;
    }
    int t=k-(y-a[res+1]+1);
    ans=1ll*ans*fpw(2,t+a[rid]-a[res+1])%mod;
    ans=(ans+1ll*(w[res+1]-w[rid]+mod)*fpw(fpw(2,n-a[rid]+1),mod-2))%mod;
    ans=1ll*ans*fpw(2,y-a[rid]+1)%mod;
    if(c[rid]==1)ans=(ans+fpw(2,y-a[rid]+1)-1)%mod;
    return ans;
}

signed main(){
    cin.tie(0)->sync_with_stdio(0);
    // signed cse=1;cin>>cse>>ws;while(cse--)
[&](){
    cin>>n>>m>>Q;map<int,int> mp;
    for(int i=1,l,r;i<=m;i++)cin>>l>>r,mp[l]++,mp[r+1]++;
    for(auto it=mp.begin();it!=mp.end();)
        if(it->se&1)it->se=cnt^=1,it++;
        else it=mp.erase(it);
    if(!mp.count(1))mp[1]=0;
    for(cnt=0;auto [x,st]:mp)cnt++,a[cnt]=x,c[cnt]=st;
    for(int i=1;i<=cnt-1;i++)s[i]=(s[i-1]+c[i]*(a[i+1]-a[i]))%mod;
    for(int i=cnt-1;i>=1;i--)w[i]=(w[i+1]+1ll*c[i]*(fpw(2,a[i+1]-a[i])-1)*fpw(2,n-a[i+1]+1))%mod;
    for(int x,y,k;Q--;)cin>>x>>y>>k,cout<<solve(x,y,k)<<'\n';
}();
}
```

---

## 作者：liruixiong0101 (赞：2)

首先，考虑贪心的选取（下面都只考虑 $l=1,r=n$ 的情况），最优的策略肯定是先选一段 $1$，再选后面的一整段，话句话说，就是有一个 $l$，满足选择 $1$ 到 $l$ 中的所有 $1$ 拼接起来，和 $l+1$ 到 $n$ 的一整段拼接起来。由此我们可以枚举这个 $l$，设 $cnt_i$ 表示 $1,i$ 中 $1$ 的个数，那么需要满足 $cnt_l+n-l=k\Longleftrightarrow l-cnt_l=n-k$。

设 $f_i=i-cnt_i$，注意到 $f_{i-1}\le f_i\le f_{i-1}+1$，所以我们可以二分出这个 $l$ 或者证明其不存在（不存在其实就证明全为 $1$）。

接下来就有两种做法：

第一种，将询问离散化（离线），这样就很好处理区间异或操作，然后二分出这个 $l$，用类似 hash 的方法处理区间的二进制数。  
时间复杂度：$\mathcal{O}(n\log^2 n)$（当然将快速幂改为光速幂可以降为 $\mathcal{O}(n\log n)$），空间复杂度：$\mathcal{O}(n)$。

第二种，直接用动态开点线段树来解决区间异或（在线），可以通过线段树二分二分出 $l$，线段树里再维护区间二进制表示值，这样也可以做。  
时间复杂度：$\mathcal{O}(n\log^2 V)$（不过这样常数可能有点大，不可通过，可以将快速幂改为光速幂，少一只 $\log$），空间复杂度 $\mathcal{O}(n\log V)$。

---

## 作者：Jordan_Pan (赞：1)

## 0

[题目传送门](https://www.luogu.com.cn/problem/P12029)。

题意：对长为 $n$ 的 01 序列先进行 $m$ 次区间反转（0 变 1，1 变 0），再询问 $q$ 次区间长为 $k$ 的字典序最大的子序列，用二进制表示，对 $10^9+7$ 取模。$n\le10^9,m,q\le2\times10^5$。

## 1

字典序最大，一定是能取 1 就取。所以如果区间里 1 的个数不少于 $k$，那么答案一定是 $2^k-1$。

如果没有这么多 1，那么一定是取前面的 1，后面 01 混杂的部分一定是原序列的连续子串。

既然把所有的 1 都取了，那么后面取的 0 的个数就是确定的，考虑线段树二分求出后面的这个连续子串的左边界。

区间反转、区间求 1 的个数、等操作可以用线段树维护，因为 $n$ 很大，考虑离线下来离散化，需要十分注意区间边界信息。

## 2

::::info[code]
```cpp
#include<bits/stdc++.h>
constexpr int rSiz=1<<21;
char rBuf[rSiz],*p1=rBuf,*p2=rBuf;
#define gc() (p1==p2&&(p2=(p1=rBuf)+fread(rBuf,1,rSiz,stdin),p1==p2)?EOF:*p1++)
template<class T>void rd(T&x){
	char ch=gc();
	for(;ch<'0'||ch>'9';ch=gc());
	for(x=0;ch>='0'&&ch<='9';ch=gc())
		x=(x<<1)+(x<<3)+(ch^48);
}
constexpr int _=2e6+5,M=2e5,mod=1e9+7;
int pp[_],wp[_];
void init(){
	pp[0]=wp[0]=1;
	for(int i=1;i<=M;i++)pp[i]=(pp[i-1]<<1)%mod;
	for(int i=1;i<=M;i++)wp[i]=1ll*wp[i-1]*pp[M]%mod;
}
int pw(int x){return 1ll*wp[x/M]*pp[x%M]%mod;}
int n,m,q,V;
int rt,cnt,c[_];
struct query{int l,r,k;}a[_],b[_];
#define mid ((l+r)>>1)
struct node{int len,cnt,val,tag;}t[_<<2];
void Add(int x){
	t[x].cnt=t[x].len-t[x].cnt;
	t[x].tag^=1;
}
void preBld(int x,int l,int r){
	t[x].len=c[r]-c[l-1];
	t[x].cnt=t[x].val=t[x].tag=0;
	if(l==r)return;
	preBld(x<<1,l,mid);
	preBld(x<<1|1,mid+1,r);
}
void Chg(int x,int l,int r,int L,int R){
	if(L<=l&&r<=R)return Add(x),void();
	if(t[x].tag)Add(x<<1),Add(x<<1|1),t[x].tag=0;
	if(L<=mid)Chg(x<<1,l,mid,L,R);
	if(R>mid)Chg(x<<1|1,mid+1,r,L,R);
	t[x].cnt=t[x<<1].cnt+t[x<<1|1].cnt;
}
void Bld(int x,int l,int r){
	if(l==r)return t[x].val=t[x].cnt?pw(t[x].len)-1:0,void();
	if(t[x].tag)Add(x<<1),Add(x<<1|1),t[x].tag=0;
	Bld(x<<1,l,mid);Bld(x<<1|1,mid+1,r);
	t[x].val=(1ll*t[x<<1].val*pw(t[x<<1|1].len)+t[x<<1|1].val)%mod;
}
std::vector<std::pair<int,std::pair<int,int> > >d;
int Qry(int x,int l,int r,int L,int R,bool o){
	if(L<=l&&r<=R){
		if(o)d.push_back({x,{l,r}});
		return t[x].cnt;
	}
	int cnt=0;
	if(L<=mid)cnt=Qry(x<<1,l,mid,L,R,o);
	if(R>mid)cnt+=Qry(x<<1|1,mid+1,r,L,R,o);
	return cnt;
}
int Ask(int x,int l,int r,int v){
	if(l==r)return l;
	if(v<=t[x<<1|1].len-t[x<<1|1].cnt)return Ask(x<<1|1,mid+1,r,v);
	else return Ask(x<<1,l,mid,v-(t[x<<1|1].len-t[x<<1|1].cnt));
}
int Req(int x,int l,int r,int L,int R){
	if(L<=l&&r<=R)return 1ll*t[x].val*pw(c[R]-c[r])%mod;
	int val=0;
	if(L<=mid)val=Req(x<<1,l,mid,L,R);
	if(R>mid)val=(val+Req(x<<1|1,mid+1,r,L,R))%mod;
	return val;
}
int main(){
//	freopen("a.in","r",stdin);
	init();
	rd(n),rd(m),rd(q);
	for(int i=1;i<=m;i++){
		rd(a[i].l),rd(a[i].r),a[i].k=0;
		c[++V]=a[i].l;c[++V]=a[i].l-1;
		c[++V]=a[i].r;c[++V]=a[i].r+1;
	}
	for(int i=1;i<=q;i++){
		rd(b[i].l),rd(b[i].r),rd(b[i].k);
		c[++V]=b[i].l;c[++V]=b[i].l-1;
		c[++V]=b[i].r;c[++V]=b[i].r+1;
	}
	std::sort(c+1,c+V+1);
	V=std::unique(c+1,c+V+1)-c-1;
	preBld(1,1,V);
	for(int i=1;i<=m;i++){
		a[i].l=std::lower_bound(c+1,c+V+1,a[i].l)-c;
		a[i].r=std::lower_bound(c+1,c+V+1,a[i].r)-c;
		Chg(1,1,V,a[i].l,a[i].r);
	}
	Bld(1,1,V);
	for(int i=1;i<=q;i++){
		b[i].l=std::lower_bound(c+1,c+V+1,b[i].l)-c;
		b[i].r=std::lower_bound(c+1,c+V+1,b[i].r)-c;
		d.clear();
		int cnt=Qry(1,1,V,b[i].l,b[i].r,1);
		if(cnt>=b[i].k)printf("%d\n",pw(b[i].k)-1);
		else{
			int pos=0,tmp=cnt;cnt=b[i].k-cnt;
			std::reverse(d.begin(),d.end());
			for(auto pr:d){
				int x=pr.first,l=pr.second.first,r=pr.second.second,tp=cnt;
				cnt-=t[x].len-t[x].cnt;
				if(cnt<=0){pos=Ask(x,l,r,tp);break;}
			}
			cnt=tmp-Qry(1,1,V,pos,b[i].r,0);
			//tmp 个 1，左侧有 cnt 个 1 
			int val=(1ll*(pw(cnt)-1)*pw(b[i].k-cnt)+Req(1,1,V,pos,b[i].r))%mod;
//			printf("%d %d %d %d %d %d %d\n",b[i].l,b[i].r,b[i].k,tmp,cnt,pos,c[pos]);
			printf("%d\n",val);
		}
	}
}
```
::::

---

## 作者：Genius_Star (赞：0)

### 思路：

容易发现，我们肯定是取前面一段前缀的 $1$ 和一整段后缀，我们要找到最小的这个后缀长度使得前面 $1$ 的数量加上这个后缀长度是 $\ge k$ 的，容易发现具有单调性，二分即可。

我们需要支持查找区间异或 $1$，查询区间 $1$ 的数量，查询区间的 $01$ 的哈希值，且是先异或后再询问。

于是可以离散化，然后区间查询的时候二分左右端点，再算上左右端点到离散化端点的贡献即可。

时间复杂度为 $O(N \log^2 N)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>
#define Add(x, y) (x + y >= mod) ? (x + y - mod) : (x + y)
#define lowbit(x) x & (-x)
#define pi pair<ll, ll>
#define pii pair<ll, pair<ll, ll>>
#define iip pair<pair<ll, ll>, ll>
#define ppii pair<pair<ll, ll>, pair<ll, ll>>
#define ls(k) k << 1
#define rs(k) k << 1 | 1
#define fi first
#define se second
#define full(l, r, x) for(auto it = l; it != r; ++it) (*it) = x
#define Full(a) memset(a, 0, sizeof(a))
#define open(s1, s2) freopen(s1, "r", stdin), freopen(s2, "w", stdout);
#define For(i, l, r) for(register int i = l; i <= r; ++i)
#define _For(i, l, r) for(register int i = r; i >= l; --i)
using namespace std;
using namespace __gnu_pbds;
typedef double db;
typedef unsigned long long ull;
typedef long long ll;
bool Begin;
const int N = 5e5 + 10, B = 35000, Mod = 1e9 + 7;
inline ll read(){
    ll x = 0, f = 1;
    char c = getchar();
    while(c < '0' || c > '9'){
        if(c == '-')
          f = -1;
        c = getchar();
    }
    while(c >= '0' && c <= '9'){
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }
    return x * f;
}
inline void write(ll x){
	if(x < 0){
		putchar('-');
		x = -x;
	}
	if(x > 9)
	  write(x / 10);
	putchar(x % 10 + '0');
}
bool End;
struct Period {
    int l, r;
};

Period P[N];
int n, m, q, len, pre[N], prehash[N], spw[B], bpw[B];
set<int> S;
void ins(int x) {
    if (!S.count(x)) {
        S.insert(x);
    } else {
        S.erase(S.find(x));
    }
    return;
}

void pwInit() {
    spw[0] = bpw[0] = 1;
    for (int i = 1; i < B; i ++) {
        spw[i] = (spw[i - 1] << 1);
        spw[i] = spw[i] - ((spw[i] >= Mod) ? Mod : 0);
    }
    int base = spw[B - 1] << 1;
    base = base - ((base >= Mod) ? Mod : 0);
    for (int i = 1; i < B; i ++) {
        bpw[i] = 1ll * bpw[i - 1] * base % Mod;
    }
    return;
}

int pow2(int t) {
    return 1ll * bpw[t / B] * spw[t % B] % Mod;
}

void init() {
    pwInit();
    n = read(), m = read(), q = read();
    for (int i = 0; i < m; i ++) {
        int l = read() - 1, r = read();
        ins(l), ins(r);
    }
    while (!S.empty()) {
        P[len].l = *S.begin();
        S.erase(S.begin());
        P[len].r = *S.begin();
        S.erase(S.begin());
        len ++;
    }
    int last = 0;
    for (int i = 0; i < len; i ++) {
        pre[i + 1] = pre[i] + P[i].r - P[i].l;
        prehash[i + 1] = (1ll * prehash[i] * pow2(P[i].r - last) + pow2(P[i].r - P[i].l) - 1) % Mod;
        last = P[i].r;
    }
    return;
}

int getCnt(int x) {
    int l = 0, r = len, mid;
    while (l < r) {
        mid = (l + r) >> 1;
        if (x >= P[mid].r) {
            l = mid + 1;
        } else {
            r = mid;
        }
    }
    if (l == len || x <= P[l].l) {
        return pre[l];
    }
    return pre[l] + x - P[l].l;
}

int getHash(int x) {
    int l = 0, r = len, mid;
    while (l < r) {
        mid = (l + r) >> 1;
        if (x >= P[mid].r) {
            l = mid + 1;
        } else {
            r = mid;
        }
    }
    if (l == len || x <= P[l].l) {
        return 1ll * prehash[l] * pow2(x - (l ? P[l - 1].r : 0)) % Mod;
    }
    return (1ll * prehash[l] * pow2(x - (l ? P[l - 1].r : 0)) + pow2(x - P[l].l) - 1) % Mod;
}

void calculate() {
    while (q --) {
        int l = read() - 1, r = read(), k = read(), precnt = getCnt(l);
        int ll = 0, rr = k, mid;
        while (ll < rr) {
            mid = (ll + rr) >> 1;
            if (getCnt(r - mid) - precnt + mid >= k) {
                rr = mid;
            } else {
                ll = mid + 1;
            }
        }
        int pre = 1ll * (pow2(k - ll) - 1) * pow2(ll) % Mod;
        int suf = (getHash(r) - 1ll * getHash(r - ll) * pow2(ll) % Mod + Mod) % Mod;
        printf("%d\n", (pre + suf) % Mod);
    }
    return;
}

void solve() {
    init();
    calculate();
    return;
}

int main() {
    solve();
    return 0;
}

```

---

## 作者：wmrqwq (赞：0)

# 题目链接

[P11843 [USACO25FEB] The Best Subsequence G](https://www.luogu.com.cn/problem/P11843)

# 题意简述

有一个长度为 $n$ 的初始全为 $0$ 的数列，现在有 $m$ 次将 $l \sim r$ 区间内的所有数字都取反的操作。

有 $q$ 次询问，每次询问形如 `l r x`，你需要找出 $l \sim r$ 中字典序最大的长度为 $x$ 的子序列。

每次询问只需要输出这个子序列在二进制下拼接而成的数字转为十进制的数字，对 $10^9 + 7$ 取模。

$1 \le n \le 10^9$，$1 \le m \le 2 \times 10^5$，$1 \le q \le 2 \times 10^5$。

# 解题思路

在线做法。

发现这个问题可以转化为初始全为 $1$ 的字符串，询问变为找字典序最小的字符串，那么设这个字典序最小的子序列转化为十进制下的数字为 $ans$，由于你发现两种决策一致，那么答案即为 $2^x - 1 - ans$。

那么我们考虑最小字典序怎么做。

你发现首先由于翻转次数只有 $m$ 次，那么显然将连续段合并后总共只有 $2m$ 个区间，此处离散化即。

那么我们考虑此时怎样查询，发现答案前缀全选 $0$ 总是最优的，那么显然答案的后面选取的是 $l \sim r$ 中的一个后缀，不然如果有更优的前缀肯定可以多选一个 $0$，那么是一定能二分到的，那么我们只需要考虑取二分最后一个能取的前缀 $0$ 的位置即可。

那么考虑如何查询后缀的值，你发现这跟本质一致，那么只需要处理前后两个散块即可，中间的块线段树维护即可。

时间复杂度 $O(q \log n \log m)$。

# 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
//#define map unordered_map
#define re register
#define ll long long
#define cll const ll
#define forl(i,a,b) for(re ll (i)=(a);i<=(b);(i)++)
#define forr(i,a,b) for(re ll (i)=(a);i>=(b);(i)--)
#define forll(i,a,b,c) for(re ll (i)=(a);i<=(b);(i)+=(c))
#define forrr(i,a,b,c) for(re ll (i)=(a);i>=(b);(i)-=(c))
#define pii pair<ll,ll>
#define mid (((l)+(r))>>1)
#define lowbit(x) (x&-x)
#define pb push_back
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
#define endl '\n'
#define QwQ return 0;
#define db long double
#define ull unsigned long long
#define lcm(x,y) (1ll*(x)/__gcd(x,y)*(y))
#define Sum(x,y) (1ll*((x)+(y))*((y)-(x)+1)/2)
#define x first
#define y second
#define maxqueue priority_queue<ll>
#define minqueue priority_queue<ll,vector<ll>,greater<ll>>
#define bug1 cout<<"bug1,AWaDa?\n";
#define bug2 cout<<"bug2,AWaDa!\n";
#define bug3 cout<<"bug3,AKTang?\n";
#define bug4 cout<<"bug4,AKTang!\n";
#define IM (ll)1e9
#define LM (ll)1e18
#define MIM (ll)-1e9
#define MLM (ll)-1e18
#define sort stable_sort
ll pw(ll x,ll y,ll mod){if(y==0)return 1;if(x==0)return 0;ll an=1,tmp=x;while(y){if(y&1)an=(an*tmp)%mod;tmp=(tmp*tmp)%mod;y>>=1;}return an;}
ll pw(ll x){return 1ll<<x;}
template<typename T1,typename T2>bool Max(T1&x,T2 y){if(y>x)return x=y,1;return 0;}template<typename T1,typename T2>bool Min(T1&x,T2 y){if(y<x)return x=y,1;return 0;}ll Ss=chrono::steady_clock::now().time_since_epoch().count();mt19937_64 Apple(Ss);ll rand_lr(ll l,ll r){return Apple()%(r-l+1)+l;}
cll mod=1e9+7,N=300010;ll fac[N],inv[N];void init(){fac[0]=1;forl(i,1,N-5)fac[i]=i*fac[i-1],fac[i]%=mod;inv[N-5]=pw(fac[N-5],mod-2,mod);forr(i,N-5,1)inv[i-1]=inv[i]*i%mod;}ll C(ll n,ll m){if(n<m || m<0)return 0;return (fac[n]%mod)*(inv[n-m]*inv[m]%mod)%mod;}
ll _t_;
ll lg[1000010];
void Init(){
	forl(i,2,1e6+5)
		lg[i]=lg[i>>1]+1;
}
ll n,m,q;
map<ll,ll>mp1,mp2;
vector<ll>G;
struct node{
    ll l,r,tag;
}a[1000010];
ll lst,k,num;
void _clear(){}
/*
10101
*/
ll pre[1000010];
ll _0(ll l,ll r){
    return (a[r].r-a[l].l+1)-(pre[r]-pre[l-1]);
}
ll _1(ll l,ll r){
    return pre[r]-pre[l-1];
}
ll f(ll l,ll r){
    return a[r].r-a[l].l+1;
}
ll l,r,x;
ll pos(ll x)
{
    ll L=1,R=k;
    while(L<R)
    {
        ll Mid=(L+R+1)/2;
        if(x<a[Mid].l)
            R=Mid-1;
        else
            L=Mid;
    }
    return L;
}
ll __0(ll l,ll r)
{
    if(l>r)
        return 0;
    ll id1=pos(l),id2=pos(r);
    if(id1==id2)
    {
        if(a[id1].tag==0)
            return r-l+1;
        return 0;
    }
    ll S=0;
    if(a[id1].tag==0)
        S+=a[id1].r-l+1;
    if(a[id2].tag==0)
        S+=r-a[id2].l+1;
    id1++,id2--;
    if(id1<=id2)
        S+=_0(id1,id2);
   // cout<<"__0("<<l<<','<<r<<")="<<S<<','<<x<<endl;
    return S;
}
struct SegTree{
    struct node{
        ll l,r,len,val;
    }tree[4000010];
    void pushup(ll x)
    {
        tree[x].len=(tree[x*2].len+tree[x*2+1].len);
        tree[x].val=(tree[x*2].val*pw(2,tree[x*2+1].len,mod)%mod+tree[x*2+1].val)%mod;
    }
    void build(ll x,ll l,ll r)
    {
        // cout<<"abc "<<x<<" "<<l<<" "<<r<<endl;
        tree[x]={l,r,0,0};
        if(l==r)
        {
            tree[x].len=a[l].r-a[l].l+1;
            if(a[l].tag)
                tree[x].val=(pw(2,tree[x].len,mod)-1+mod)%mod;
            else
                tree[x].val=0;
            // cout<<x<<' '<<tree[x].val<<' '<<tree[x].len<<endl;
            return ;
        }
        build(x*2,l,mid);
        build(x*2+1,mid+1,r);
        pushup(x);
    }
    // ll query(ll x,ll l,ll r)
    // {
    //     if(l<=tree[x].l && tree[x].r<=r)
    //         return tree[x].val;
    //     ll Mid=(tree[x].l+tree[x].r)/2;
    //     if(r<=Mid)
    //         return query(x*2,l,r);
    //     if(Mid<l)
    //         return query(x*2+1,l,r);
    //     return (query(x*2,l,r)*pw(2,r-tree[x*2+1].l+1,mod)%mod+query(x*2+1,l,r))%mod;
    // }
    ll query(ll x,ll l,ll r)
    {
        if(l<=tree[x].l && tree[x].r<=r)
        {
            // cout<<"cde "<<tree[x].l<<" "<<tree[x].r<<endl;
            // cout<<tree[x].val<<" "<<pw(2,a[r].r-a[tree[x].r].r,mod)<<endl;
            return tree[x].val*pw(2,a[r].r-a[tree[x].r].r,mod)%mod;
        }
        ll Mid=(tree[x].l+tree[x].r)/2;
        if(r<=Mid)
            return query(x*2,l,r)%mod;
        if(Mid<l)
            return query(x*2+1,l,r)%mod;
        return (query(x*2,l,r)+query(x*2+1,l,r))%mod;
    }
}T;
/*
10101
01010

1011

15 - 11 = 4
*/
ll query(ll l,ll r)
{
    ll id1=pos(l),id2=pos(r);
    if(id1==id2)
    {
     //   cout<<"brute:";
        if(a[id1].tag==0)
            return 0;
        return (pw(2,r-l+1,mod)-1+mod)%mod;
    }
    ll num=0;
    if(a[id2].tag)
        num+=pw(2,(r-a[id2].l+1),mod)-1+mod;
    num%=mod;
    // cout<<"awa"<<(pw(2,(r-a[id2].l+1),mod)-1+mod)%mod<<endl;
    if(id1+1<=id2-1)
        num+=T.query(1,id1+1,id2-1)*pw(2,r-a[id2-1].r,mod)%mod;
    num%=mod;
    // cout<<"qwq"<<T.query(1,id1+1,id2-1)<<endl;
    if(a[id1].tag)
        num+=((pw(2,a[id1].r-l+1,mod)-1+mod)%mod*pw(2,r-a[id1].r,mod))%mod;
    // cout<<"OvO"<<((pw(2,a[id1].r-l+1,mod)-1+mod)%mod*pw(2,r-a[id1].r,mod))%mod<<endl;
    return num;
}
/*
01110

3 - 2 = 1

00110110

31 - 16 - 4 - 2 = 9

11011001


*/
void solve()
{
    _clear();
    cin>>n>>m>>q;
    forl(i,1,m)
        cin>>l>>r,
        G.pb(l),
        G.pb(r+1);
    sort(G.begin(),G.end());
    ll L=0,sz=(ll)G.size()-1;
    lst=1;
    num=1;
    forl(i,0,(ll)G.size()-1)
    {
        ll l=num;
        num^=1;
        while(i<sz && G[i]==G[i+1])
            i++,
            num^=1;
        if(num==l)
            continue;
        if(lst<=G[i]-1)
            a[++k]={lst,G[i]-1,l},
            lst=G[i];
    }
    if(lst<=n)
        a[++k]={lst,n,num};
  //  forl(i,1,k)
  //      cout<<a[i].l<<' '<<a[i].r<<' '<<a[i].tag<<endl;
    forl(i,1,k)
        pre[i]=pre[i-1]+a[i].tag*(a[i].r-a[i].l+1);
    T.build(1,1,k);
   // if(n==9)
   //     cout<<pos(7)<<' '<<pos(8)<<endl;
    //cout<<T.query(1,1,5)<<endl;
    forl(_,1,q)
    {
        cin>>l>>r>>x;
        ll id1=pos(l),id2=pos(r);
        if(id1==id2)
        {
       //    cout<<a[id1].tag<<endl;
           // cout<<0<<endl;
            if(a[id1].tag==0)
                cout<<(pw(2,x,mod)-1+mod)%mod<<endl;
            else
                cout<<0<<endl;
            continue;
        }
//        cout<<
        if(__0(l,r)>=x)
        {
           // cout<<0<<endl;
            cout<<(pw(2,x,mod)-1+mod)%mod<<endl;
            continue;
        }
        ll L=l-1,R=r;
        while(L<R)
        {
            ll Mid=(L+R+1)/2;
            if(__0(l,Mid)+(r-Mid)>=x)
                L=Mid;
            else
                R=Mid-1;
        }
//        cout<<"<"<<L<<'>';
        if(L+1<=r)
         //   cout<<"?\n",
            cout/*<<"query("<<L+1<<','<<r<<")="*/<<((((pw(2,x,mod)-1+mod)%mod)-query(L+1,r))%mod+mod)%mod<<endl;
        else
            cout<<0<<endl;
    }
}
int main()
{
	Init();
//    freopen("tst.txt","r",stdin);
//    freopen("sans.txt","w",stdout);
    IOS;
    _t_=1;
  // cin>>_t_;
    while(_t_--)
        solve();
    QwQ;
}
```

---

## 作者：DengStar (赞：0)

> 本题解中原有两段较长的代码，但洛谷博客不支持 html 语法，无法把它们折叠起来，使得阅读体验较差，所以我把它们删除了。如果需要代码，可以 [在博客园中查看](https://www.cnblogs.com/dengstar/p/18738170)。

先思考一下我们的策略是什么。容易想到要贪心地在区间内选取 $\texttt{1}$。如果区间内 $\texttt{1}$ 的个数不少于 $k$，就可以选出全为 $\texttt{1}$ 的子序列。否则，最优策略一定是先选择一堆 $\texttt{1}$，然后选择区间的一段后缀（与前面选择的 $\texttt{1}$ 不相交）。正确性不难证明：比较两个子序列，如果它们前缀的极长 $\texttt{1}$ 连续段长度不同，那么 $\texttt{1}$ 连续段长的字典序大。但如果只选 $\texttt{1}$，最后子序列的长度可能不足 $k$，所以还要补上一段后缀。

询问时，在区间 $[l, r]$ 中找到最后一个 $p$，满足 $[l, p)$ 中 $\texttt{1}$ 的个数加上 $r - p + 1$ 不小于 $k$，那么答案子序列就是若干个 $\texttt{1}$ 拼接上 $[p, r]$。由于 $[l, p)$ 中 $\texttt{1}$ 的个数加 $r - p + 1$ 随着 $p$ 的右移单调不升，所以 $p$ 可以二分。设 $[1, p)$ 中 $\texttt{1}$ 的数量为 $c$，$[p, r]$ 子串的二进制表示为 $x$，则答案为 $(2^{c} - 1)2^{x} + x$。

问题来了：如何维护区间中 $\texttt{1}$ 的个数以及区间的二进制表示这些量呢？我们大致有两种方法：

## 方法I：动态开点线段树

这个方法比较直接，在线段树上维护区间的翻转标记和区间中 $\texttt{1}$ 的个数即可。对于区间的二进制表示，实际上就是维护区间中 $\texttt{1}$ 对应的位置 $i$ 的 $2^{n - i}$ 之和。

但动态开点线段树的空间复杂度为 $O((m + q) \log n)$，时间复杂度为 $O(m \log n + q \log^{2} n)$，二者都需要卡常。

对于空间复杂度的优化，由于所有修改操作都在查询操作之前，所以可以采取这样的策略：查询时，如果线段树上的某个节点的左右子都不存在，则直接返回该节点维护的区间和查询区间的交的信息：

```cpp
Node query(int id, int l, int r, int L, int R) {
    if(!id) return {0, 0};
    if(l == L && r == R) return info[id];
    if(!lson[id] && !rson[id]) {
        // 左右子都不存在，直接返回。
        if(!info[id].cnt) return {0, 0};
        int cnt = R - L + 1; i64 sum = S(L, R);
        return {sum, cnt};
    }
    // 以下省略
}
```

为什么这是对的呢？如果一个节点没有左右子，说明每次修改操作要么完全包含这个节点对应的区间，要么完全不包含。所以这个区间中要么全是 $\texttt{0}$，要么全是 $\texttt{1}$，因此就没有必要继续查询子区间。由于所有修改操作都在查询操作之前，所以这种做法可以有效地减少查询时新建的节点数，从而减少空间占用，同时也减少了时间复杂度中的常数。

现在 MLE 的问题解决了。对于时间的优化，除了快读快输，一个比较有效的方法是使用 $O(\sqrt{p}) - O(1)$ 的光速幂（$p$ 是模数）。一篇题解中说他使用这种方法卡过去了，但我并没有成功，最高分数是 85 分/kk

[提交记录](https://www.luogu.com.cn/record/207368821)

## 方法II：离散化

这是本题的正解。操作完以后整个串可以表示为 $O(m)$ 个极长的 $\texttt{01}$ 连续段，所以把修改操作的端点离散化之后按段维护，就只需要维护 $O(m)$ 个信息。具体而言，按段预处理 $\texttt{1}$ 的数量以及二进制表示的后缀和即可。

实现细节：假设修改的端点排序后的数组为 $num$，我们希望每个字符串中每个 $[num_{i}, num_{i + 1})$ 区间构成一个 $\texttt{01}$ 连续段（可能不是极长的，但不重要）。这里使用的是左闭右开区间，能为实现带来便利。对于修改操作 $(l, r)$，加入到离散化数组中的数应该是 $l$ 和 $r + 1$，也相当于左闭右开区间。如果加入的是 $l$ 和 $r$ 就错了，因为不能保证 $r$ 开头的那一段全为 $\texttt{0}$ 或 $\texttt{1}$，考虑这个例子：$n = 10$ 时翻转 $(3, 7)$，此时字符串分为 $[1, 3)$，$[3, 8)$。$[8, 11)$ 三个连续段，因此加入 $[3, 7)$ 是不正确的。除此之外，为了方便，还可以把 $1$ 和 $n + 1$ 也加入到 $num$ 中。

修改操作可以看作在 $num$ 数组上做异或差分，修改完之后求一次前缀异或和就可以得到每一段是 $\texttt{0}$ 还是 $\texttt{1}$，然后就可以预处理区间 $\texttt{1}$ 的数量和区间二进制表示的后缀和。

查询时二分 $p$ 再查找 $p$ 在哪个连续段中，单次查询的时间复杂度为 $O(\log n \log m)$，此时已经可以通过。（下面这个做法没写，是口胡的）进一步，不难发现 $p$ 一定是一个 $\texttt{0}$ 连续段的开头，所以可以直接二分 $num$ 数组的下标，时间复杂度优化到 $O(\log m)$。

下面是单次询问 $O(\log n \log m)$ 的做法：（见博客园）

[AC 记录](https://www.luogu.com.cn/record/207374572)

---

## 作者：未来姚班zyl (赞：0)

### 题目大意
有一个长度为 $n$ 的 $\text{01}$ 串 $S$ 与 $m$ 次修改，每次修改形如翻转 $S_{[l,r]}$。

在修改结束后，给出 $q$ 次查询 $l,r,k$，询问 $S_{[l,r]}$ 中长度为 $k$ 的字典序最大的子序列的二进制值，对 $10^9+7$ 取模。设 $m,q$ 同阶，要求 $O(m(\log m+\log n))$。
### 题目分析
首先离散化。

考虑一种贪心，从左往右枚举 $i$，如果 $S_i=1$ 则直接选入。否则 $S_i=0$，如果后面的数加上现在的长度不足 $k$ 则不选 $S_i$，反之选择 $S_i$。

容易发现一个前缀的 $0$ 不用选，所以我们可以直接二分找到第一个被选的 $0$，设其为 $S_x$，则 $[l,x-1]$ 中的 $1$ 都被选，$S_{[x,r]}$ 被选。前者快速幂，后者预处理后缀和即可，复杂度线性对数。

```cpp
#include<bits/stdc++.h>
#define ll long long
//#define int ll
#define L x<<1
#define R x<<1|1
#define mid ((l+r)>>1)
#define lc L,l,mid
#define rc R,mid+1,r
#define Root 1,1,ln
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
#define yy puts("Yes"),exit(0)
#define nn puts("No"),exit(0)
#define YY return puts("Yes"),void()
#define	NN return puts("No"),void()
inline int read(){int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57)s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
inline void pf(ll x){if(x<0) putchar('-'),x=-x;if(x>9)pf(x/10);putchar(x%10+48);}
using namespace std;
const int N=1.2e6+5,M=1e6+5,inf=(1LL<<31)-1,mod=1e9+7;
const ll llf=1e18;
inline void add(int &a,int b){((a+=b)>=mod) and (a-=mod);}
inline int Add(int a,int b){return add(a,b),a;}
inline int mul(int a,int b){return 1LL*a*b%mod;}
inline void Mul(int &a,int b){a=mul(a,b);}
inline void red(int &a,int b){add(a,mod-b);}
inline int Red(int a,int b){return red(a,b),a;}
inline int qp(int a,ll b){if(!b)return 1;int c=qp(a,b>>1LL);Mul(c,c);if(b&1)Mul(c,a);return c;}
inline int INV(int x){return qp(x,mod-2);}
int n,m,q,lsh[N],b[N],ln;
struct node{
	int l,r;
}a[N];
struct nod{
	int l,r,k;
}qs[N];
inline void sol(int &x){
	x=lower_bound(b+1,b+ln+1,x)-b;
}
int d[N],tp,sf[N],pr[N][2],Iv[N];
bool pw[N];
inline int get(int l,int r,int ty){
	if(l>r)return 0;
	if(ty<=1)return pr[r][ty]-pr[l-1][ty];
	return mul(Red(sf[l],sf[r+1]),Iv[r+1]);
}
inline int val(int c){
	return Red(qp(2,c),1);
}
inline void Main(){
	n=read(),m=read(),q=read();
	int c=0;
	lsh[++c]=1,lsh[++c]=n;
	repm(i){
		a[i].l=read(),a[i].r=read(),lsh[++c]=a[i].r,lsh[++c]=a[i].l;
		if(a[i].l!=1)lsh[++c]=a[i].l-1;
	}
	rep(i,1,q){
		qs[i].l=lsh[++c]=read(),qs[i].r=lsh[++c]=read(),qs[i].k=read();
		if(qs[i].l!=1)lsh[++c]=qs[i].l-1;
	}
	sort(lsh+1,lsh+c+1);
	rep(i,1,c)if(lsh[i]^lsh[i+1])b[++ln]=lsh[i];
	repm(i)sol(a[i].l),sol(a[i].r),pw[a[i].l]^=1,pw[a[i].r+1]^=1;
	rep(i,1,ln){
		d[i]=b[i]-b[i-1],pw[i]^=pw[i-1];
		pr[i][0]=pr[i-1][0]+d[i];
		pr[i][1]=pr[i-1][1]+d[i]*pw[i];
	}
	Iv[ln+1]=1;
	int tot=0;
	per(i,ln,1){
		if(!pw[i])sf[i]=sf[i+1];
		else sf[i]=Add(mul(val(d[i]),qp(2,tot)),sf[i+1]);
		tot+=d[i],Iv[i]=INV(qp(2,tot));
	}
	rep(o,1,q){
		sol(qs[o].l),sol(qs[o].r),tp=0;
		int Ll=qs[o].l,Rr=qs[o].r,k=qs[o].k;
		if(get(Ll,Rr,1)>=k){
			cout <<val(k)<<'\n';
			continue;
		}
		int l=Ll,r=Rr,ans=Rr,Ans=0;
		while(l<=r){
			int C1=get(Ll,mid,1),Len=get(mid+1,Rr,0);
			if(C1+Len<k)ans=mid,r=mid-1;
			else l=mid+1;
		}
		int C1=get(Ll,ans-1,1),Len=get(ans+1,Rr,0),res=k-C1-Len;
		if(pw[Ans])Ans=Red(qp(2,d[res]),1);
		Ans=Add(mul(Ans,qp(2,Len)),get(ans+1,Rr,2));
		add(Ans,mul(val(C1),qp(2,Len+res)));
		cout <<Ans<<"\n";
	}
}
signed main(){
	int T=1;
	while(T--)Main();
	return 0;
}
```

---

## 作者：aeiouaoeiu (赞：0)

先将 $m$ 次操作离线下来用类似差分的方式处理，得到所有的极长 $0$ 区间与极长 $1$ 区间。

一个明显的贪心方法：先加尽可能多的 $1$，如果没有 $1$ 了，那就从右往左找 $0$ 加，可以证明这是最优的。

考虑答案的最终形态，形成这样一个结构：一个 $1$ 块后缀，数个 $1$ 整块，一个 $0$ 块前缀，由 $0$ 整块与 $1$ 整块构成的一个大块，一个 $0$ 块或 $1$ 块后缀。

首先特判 $l,r$ 在同一个块内的情况。

按块做 $1$ 数量前缀和，处理 $1$ 数量超过 $k$ 的情况。

按块做后缀转为十进制的结果，可以求出任意块之间构成的二进制串的值。

按块做 $0$ 数量后缀和，用二分找到 $0$ 块前缀所在块编号，注意当 $r$ 位于 $0$ 块时有细节。根据这个编号就可以求出由 $0$ 整块与 $1$ 整块构成的大块的值。

把答案拼一起即可，时间复杂度 $\mathcal{O}((m+q)\log n)$。

```cpp
#include<bits/stdc++.h>
#define pb emplace_back
#define mp make_pair 
#define pob pop_back
using namespace std;
typedef long long ll;
const ll maxn=500007,ee=1e18,p=1e9+7;
ll n,m,q,k,L[maxn],val[maxn],c[maxn],s[maxn],c1[maxn],c0[maxn];
ll qpow(ll a,ll b){ll E=1; for(;b;b>>=1,a=a*a%p)if(b&1) E=E*a%p; return E;}
ll ask01(ll l,ll r){
	if(l>r) return 0;
	return (s[l]-s[r+1]+p)%p*qpow(qpow(2,n-L[r+1]+1),p-2)%p;
}
ll ask1(ll l,ll r){return (l>r)?0:(c1[r]-c1[l-1]);}
ll qry(ll l,ll r,ll x){
	ll idl,idr;
	idl=upper_bound(L+1,L+1+k,l)-L-1,idr=upper_bound(L+1,L+1+k,r)-L-1;
	if(idl==idr) return val[idl]*(qpow(2,x)-1+p)%p;

	ll b1=0,b4=0,s1,idz,sufz=c0[k-(idr+1)+1];
	if(val[idl]) b1=L[idl+1]-l;
	if(val[idr]) b4=r-L[idr]+1;
	s1=b1+b4+ask1(idl+1,idr-1);
	if(s1>=x) return (qpow(2,x)-1+p)%p;

	if(val[idr]==0) sufz+=L[idr+1]-r-1;
	idz=lower_bound(c0+1,c0+1+k,x-s1+sufz)-c0; idz=k-idz+1;
	b1=b1+ask1(idl+1,idz-1);

	return ((qpow(2,b1)-1+p)%p*qpow(2,x-b1)%p+ask01(idz+1,idr-1)*qpow(2,r-L[idr]+1)%p+qpow(2,b4)-1+p)%p;
}
int main(void){
    //freopen("data.in","r",stdin); 
    //freopen("data.out","w",stdout);
    ios::sync_with_stdio(0),cin.tie(0);
    cin>>n>>m>>q;
    for(ll i=1,l,r;i<=m;i++) cin>>l>>r,c[2*i-1]=l,c[2*i]=r+1;
    sort(c+1,c+1+2*m); k++;
	for(ll i=1,cnt=1,cv=0;i<=2*m;i++){
		cv^=1;
		if((c[i]!=c[i+1]||i==2*m)&&c[i]<=n&&cv!=val[k]) L[++k]=c[i],val[k]=cv;
	}
	if(k>=2&&L[2]!=1) L[1]=1;

	L[k+1]=n+1;
	for(ll i=k;i>=1;i--){
		c0[i]=c0[i+1],s[i]=s[i+1];
		if(val[i]) s[i]=(s[i+1]+(qpow(2,L[i+1]-L[i])-1+p)%p*qpow(2,n-L[i+1]+1)%p)%p; 
		else c0[i]+=L[i+1]-L[i];
	}
    reverse(c0+1,c0+1+k);
	
	for(ll i=1;i<=k;i++){
		c1[i]=c1[i-1];
		if(val[i]) c1[i]+=L[i+1]-L[i];
	}
	for(ll i=1,l,r,k1;i<=q;i++) cin>>l>>r>>k1,cout<<qry(l,r,k1)<<"\n";
    return 0;
}
```

---

