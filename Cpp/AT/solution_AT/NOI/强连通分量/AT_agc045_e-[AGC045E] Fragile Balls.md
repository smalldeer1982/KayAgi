# [AGC045E] Fragile Balls

## 题目描述

我们有$n$个盒子和$m$个球(编号都从$1$开始)，目前，球$i$在$A_i$盒子中。

接下来，对于每次操作，你可以执行以下几个操作中的一个：

- 选择一个装有两个或更多球的盒子，从中拿出一个球，把它放入另一个盒子当中
- 由于球都是易碎的，因此，你总共不能移动球$i$超过$C_i$次。

你现在的目标是对于每个$i$，将球$i$放入盒子$B_i$中。请确定这个目标是否可以实现，如果可以，则输出最少需要操作的次数，如果不可以，则输出-1。

## 样例 #1

### 输入

```
3 3
1 2 1
2 1 1
1 3 2```

### 输出

```
3```

## 样例 #2

### 输入

```
2 2
1 2 1
2 1 1```

### 输出

```
-1```

## 样例 #3

### 输入

```
5 5
1 2 1
2 1 1
1 3 2
4 5 1
5 4 1```

### 输出

```
6```

## 样例 #4

### 输入

```
1 1
1 1 1```

### 输出

```
0```

# 题解

## 作者：jun头吉吉 (赞：3)

## 题意

有 $n$ 个盒子 $m$ 个球。每次可以把一个球从一个盒子移到另一个盒子。需要保证球移出后盒子不为空。

第 $i$ 个球需要从 $A_i$ 移动到 $B_i$，最多移动 $C_i$ 次。

求最小移动次数或者报告无解。

$1\le n,m,C_i\le10^5$

## 题解

虽然过了但是还是很晕。

对于一组 $A_i,B_i,C_i$，从 $A_i$ 向 $B_i$ 连一条有向边。

记 $in_i$ 为 $i$ 的入度，也就是最后的球的个数。

记 $out_i$ 为 $i$ 的出度，也就是一开始球的个数。

下面说的连通块指的是将边视作无向边，强连通分量指的是有向边。

一个很很很很显然的结论就是，如果存在 $in_i=0,out_i\ne0$，肯定无解。先判掉。

接下来考虑 $C_i=1$ 的情况，也就是每个球只能动一次，必须一次归位。

**结论：有解当且仅当对于每个连通块 $V$ ，要么 $|V|=1$，要么 $\exist x\in V,out_x>1$。**

首先 $|V|=1$ 时肯定是对的。下面考虑的都满足 $|V|>1$。

必要性是显然的，因为如果所有的 $out_x\le1$，那么动不了，也不可能找别的连通块的求来帮忙，然后就寄了。

充分性的证明，考虑每次可以选一条边把对应的球移到终点，要么这个点已经有归位的球，要么满足 $out_x>1$。

对于一个强连通分量，我们可以选择一个 $out_x>1$ 的 $x$，然后找到一个从 $x$ 开始环，把环上对应的球依次归位，显然每步都是合法的。然后接下来就可以把所有 $x$ 可以到达的边对应的球归位了。

然后我们只要证明所有入度为 $0$ 的强连通分量一定存在一个 $out_x>1$。证明就是如果整个是一个强连通分量那么就已经满足了。否则对于入度为 $0$ 的一个强连通分量，至少有两个点（一个点则 $in=0,out\ne 0$），所以 $out_x\ge 1$，然后这个强连通分量必然有后继会向外连边，所以就出现了一个 $out_x>1$ 的点。

这样我们就证明了，有解就是对于任意 $>1$ 的连通块，存在 $out_x>1$ 的点。

然后答案是容易计算的，就是 $\sum [A_i\ne B_i]$

然后我们考虑 $C_i$ 为任意值的情况，把所有 $A_i,B_i,C_i$ 简单分类：

1. $A_i\ne B_i$：
   1. 在一个不存在 $out_x>1$ 的连通块内
   2. 在一个存在 $out_x>1$ 的连通块内
2. $A_i=B_i$
   1. 在一个不存在 $out_x>1$ 的连通块内，也就是这是一个点上连一个自环
   2. 在一个存在 $out_x>1$ 的连通块内

统计 $need$ 为 $|V|>1$ 且不存在 $out_x>1$ 的连通块的数量。也就是我们要 $need$ 次把别的连通块的点移过来再移回去。

对于 1.1 和 1.2，可以直接用 $t$ 的代价取帮助一个需要帮助的连通块，区别是 1.2 可以直接用，但是 1.1 需要这个连通块被帮助过之后才能使用。使用的次数是 $C_i-1$，用了 $t$ 次代价就是 $t$。

对于 2.2，可以直接去帮助别的连通块，次数是 $C_i-1$，用了 $t$ 次代价是 $t+1$。（如果用 $0$ 次代价就是 $0$）

对于 2.1，需要别人先来帮助它，它才能取帮助别的连通块，所以相当于次数是 $C_i-2$，用了 $t$ 次代价是 $t+2$。（同样如果是 $0$ 那么代价是 $0$）

我们总共的次数是 $need$，那么至少有 $need$ 的代价，然后就可以认为 1.1/2 是免费的 2.2 被用则代价是 $1$，2.1 被用则代价是 $2$，最小化代价和使得可以帮助的 $\ge need$。

这个是可以做的。因为使用的肯定是前 $k$ 大的，就枚举 2.2 用了前 $i$ 大的，看 2.1 最少要用多少个，计算代价即可。

然后还有一个要注意的细节就是如果不存在 1.2，那么我们需要强制用一次 2.2，因为只有这个才能直接移动，1/2.1 都需要别人先帮助它之后才能取帮助别人。

感觉说得很意识流感性理解把吧/yun。

复杂度 $\mathcal O(m\alpha(n)+m\log m)$。可以做到线性但是没有什么必要。

## 代码

```cpp
#include<bits/stdc++.h>
#define mp make_pair
#define mt make_tuple
#define eb emplace_back
#define pb push_back
#define pc putchar
#define chkmx(a,b) (a)=max((a),(b))
#define chkmn(a,b) (a)=min((a),(b))
#define fi first
#define se second
using namespace std;
template<class T>
void read(T&x){x=0;char c=getchar();bool f=0;for(;!isdigit(c);c=getchar())f^=c=='-';for(;isdigit(c);c=getchar())x=x*10+c-'0';if(f)x=-x;}
template<class T,class ...ARK>void read(T&x,ARK&...ark){read(x);read(ark...);}
template<class T>void write(T x){if(x<0)pc('-'),x=-x;if(x>=10)write(x/10);pc(x%10+'0');}
template<class T,class ...ARK>void write(T x,ARK...ark){write(x);pc(' ');write(ark...);}
template<class ...ARK>void writeln(ARK...ark){write(ark...);pc('\n');}
typedef long long ll;
const int mod=998244353;
struct mint{
	int x;mint(int o=0){x=o;}mint&operator+=(mint a){return(x+=a.x)%=mod,*this;}mint&operator-=(mint a){return(x+=mod-a.x)%=mod,*this;}
	mint&operator*=(mint a){return(x=1ll*x*a.x%mod),*this;}mint&operator^=( int b){mint a=*this;x=1;while(b)(b&1)&&(*this*=a,1),a*=a,b>>=1;return*this;}
	mint&operator/=(mint a){return*this*=(a^=mod-2);}friend mint operator+(mint a,mint b){return a+=b;}friend mint operator-(mint a,mint b){return a-=b;}
	friend mint operator*(mint a,mint b){return a*=b;}friend mint operator/(mint a,mint b){return a/=b;}friend mint operator^(mint a, int b){return a^=b;}
	mint operator-(){return 0-*this;}bool operator==(const mint b)const{return x==b.x;}
};
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
int rint(int l,int r){return uniform_int_distribution<int>(l,r)(rnd);}
#define lowbit(x) ((x)&-(x))
#define mid ((l+r)>>1)
#define lc (x<<1)
#define rc (x<<1|1)
const int N=1e5+10;
const int inf=0x3f3f3f3f;
int n,m,a[N],b[N],c[N];
int fa[N],sz[N];
int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}
void merge(int x,int y){fa[find(x)]=find(y);}
int in[N],ot[N];
bool vis[N];
int ans,need,now;
vector<ll>v1,v2;
int get(vector<ll>&v,ll x){
	if(x<=0)return 0;
	if(!v.size()||x>v.back())return inf;
	return lower_bound(v.begin(),v.end(),x)-v.begin()+1;
}
signed main(){
	read(n,m);iota(fa+1,fa+1+n,1);
	for(int i=1;i<=m;i++)read(a[i],b[i],c[i]),ot[a[i]]++,in[b[i]]++,merge(a[i],b[i]),ans+=(a[i]!=b[i]);
	for(int i=1;i<=n;i++)if(ot[i]&&!in[i])return writeln(-1),0;
	for(int i=1;i<=n;i++)sz[find(i)]++,vis[find(i)]|=(ot[i]>1);
	for(int i=1;i<=n;i++)if(i==fa[i]&&sz[i]>1&&!vis[i])need++;
	if(!need)return writeln(ans),0;
	ans+=need;
	bool flag=0;
	for(int i=1;i<=m;i++){
		if(a[i]!=b[i]){
			now+=c[i]-1;
			if(c[i]>1&&vis[find(a[i])])flag=1;
		}else{
			if(vis[find(a[i])])v1.pb(c[i]-1);
			else v2.pb(c[i]-2);
		}
	}
	sort(v1.begin(),v1.end(),greater<ll>());
	sort(v2.begin(),v2.end(),greater<ll>());
	while(v1.size()&&v1.back()<=0)v1.pop_back();
	while(v2.size()&&v2.back()<=0)v2.pop_back();
	if(!flag){
		if(!v1.size())return writeln(-1),0;
		ans++;need-=v1[0];v1.erase(v1.begin());
	}
	need-=now;
	for(int i=1;i<(int)v1.size();i++)v1[i]+=v1[i-1];
	for(int i=1;i<(int)v2.size();i++)v2[i]+=v2[i-1];
	int mn=min(get(v1,need),get(v2,need)*2);
	for(int i=0;i<(int)v1.size();i++)
		chkmn(mn,i+1+2*get(v2,need-v1[i]));
	if(mn>=inf)writeln(-1);
	else writeln(ans+mn);
}
```

---

