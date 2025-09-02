# 「dWoi R1」Sweet Fruit Chocolate

## 题目背景

[事情来源 ……](https://www.bilibili.com/video/BV19Z4y1K7dH)

我们的东条妈妈在残害了梦野之后，还想继续她的事业，残害可怜的最原。她发现最原很喜欢吃甜甜的巧克力，另外还有一种东西叫做西西弗水果，他富含营养但没那么好吃，因此，她想把这些巧克力淋在西西弗水果上。

## 题目描述

东条把想淋的巧克力做成了一个巧克力喷泉树。巧克力喷泉树是一棵 $n$ 个节点的树。每个节点都有一个西西弗水果。对于每一个节点 $u$，你有两种选择：你可以在节点 $u$ 放置 $a_u$ 个水果，也可以一个水果都不放。然后，东条会在根节点往下淋巧克力汁。节点 $u$ 给最原带来的营养值是 $u$ 及其子树中所放置的西西弗水果的数量。东条想要知道，对于所有 $2^n$ 个放水果方案，最原所获得的营养值之和的总和是多少。答案对 $998244353$ 取余。

树的根节点为 $1$。

## 说明/提示

#### 样例 1 解释

用 $S$ 表示选中状态

- $S=000$ 贡献 $0$
- $S=001$ 贡献 $1$
- $S=010$ 贡献 $2$
- $S=011$ 贡献 $3$
- $S=100$ 贡献 $6$
- $S=101$ 贡献 $7$
- $S=110$ 贡献 $8$
- $S=111$ 贡献 $9$

#### 数据规模与约定

对于 $20\%$ 的数据，满足 $n\le 20$。

对于另外 $30\%$ 的数据，满足 $u=v-1$。

对于 $100\%$ 的数据，满足 $2\le n\le 10^6$，$1 \le a_i \le 10^9$。

## 样例 #1

### 输入

```
3
1 1 2
1 2
2 3```

### 输出

```
36```

# 题解

## 作者：推翻暴政 (赞：10)

一道不算水的黄题。

首先，对于每个点放置的水果我们可以做出以下的处理：

因为每个点放置的水果 **仅会影响** 它的所有祖先节点，所以我们可以考虑记录 $i$ 节点的祖先数量大小 $Size_i$（即它与它的所有祖先），注意要包含它自己。

现在的问题是，每个点会做出贡献多少次？显然是 $2^{n-1}$ 次，我的推导过程如下：

注意到样例一解释：

> 用 $S$ 表示选中状态：
>
> - $S=000$ 贡献 $0$
> - $S=001$ 贡献 $1$
> - $S=010$ 贡献 $2$
> - $S=011$ 贡献 $3$
> - $S=100$ 贡献 $6$
> - $S=101$ 贡献 $7$
> - $S=110$ 贡献 $8$
> - $S=111$ 贡献 $9$

我们考虑同样的想法，$[0,2^n)$ 中，二进制表示下每一位 $1$ 会出现 $2^{n-1}$ 次，就可以得到这个结论了。

故答案公式如下：

$$Ans=2^{n-1}\times\large\sum\limits_{i=1}^n Size_i$$

线性求出 $2^{n-1}$，使用 dfs 求出祖先数量 $Size_i$ 大小最后统计答案即可，时间复杂度 $O(n)$。

代码如下：

```c++
#include<bits/stdc++.h>
using namespace std;
//模数和2的逆元 需要用到2的逆元是因为我的2^(n-1)是用(2^n)/2求得的 非常不聪明
const long long mod=998244353,inv=499122177;
const int MAXN=1000005;
int n,a[MAXN],head[MAXN],tot;
long long siz[MAXN],base,ans;
struct edge{
	int v,nex;
} e[MAXN<<1];
//链式前向星建边
inline void add_edge(int u,int v){
	e[++tot].v=v;
	e[tot].nex=head[u];
	head[u]=tot;
}
//深搜求出祖先数量大小
inline void dfs(int x,int fa){
	siz[x]=siz[fa]+1;
	for(int i=head[x];i;i=e[i].nex){
		int y=e[i].v;
		if(y==fa)  continue;
		dfs(y,x);
	}
}
//处理2^(n-1)
inline void pre(){
	base=1;
	for(int i=1;i<=n;i++)  base=(base*2)%mod;
	base=(base*inv)%mod;
}
int main(){
	scanf("%d",&n);
	pre();
	for(int i=1;i<=n;i++)  scanf("%d",&a[i]);
	for(int i=1;i<n;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		add_edge(x,y);
		add_edge(y,x);
	}
	dfs(1,1);
   	//统计答案 注意三个数一起相乘可能会爆long long 所以我们拆成两两相乘
	for(int i=1;i<=n;i++){
		siz[i]=(siz[i]*a[i])%mod;
		ans+=base*siz[i]%mod;
		ans%=mod;
	}
	printf("%lld",ans);
	return 0;
}
```

感谢你的阅读，点个赞再走吧~

---

## 作者：Broken_Heart (赞：5)

[P7159 「dWoi R1」Sweet Fruit Chocolate](https://www.luogu.com.cn/problem/P7159)

### 分析
显然每个点都有选或不选两种状态，那么一共就有 $2^n$ 种方案，那么显然暴力是过不去的，于是我们不妨想想对每个点去单独统计其贡献。

### 思路
对于每个点 $u$，我们发现只有 $2^{n-1}$ 种方案 $a_u$ 会对答案有贡献，其余每种方案与 $u$ 无关，$u$ 对答案有贡献的 $2^{n-1}$ 种方案中，$a_u$ 会在每次统计它和它祖先时被计算到，即每种选 $u$ 的方案中 $u$ 会贡献的值为  $dep_u\times a_u$，那么答案为 $2^{n-1}\times \sum^n_{i=1} dep_i \times a_i$。

### 实现
先处理出 $2^{n-1}$ 的值，再 dfs 遍历求出每个点深度 $dep_i$，最后遍历 $1$ 到 $n$ 算出每个点贡献即可，记得每次取模，总复杂度 $O(n)$。

### 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1000005;
const int mod=998244353;
int n,ans,p,dep[N],val[N];
vector<int>a[N];
void dfs(int u,int f){
	dep[u]=dep[f]+1;
	for(auto v:a[u]){
		if(v==f) continue;
		dfs(v,u);
	}
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>n;
	p=1;
	for(int i=1;i<=n;i++) cin>>val[i];
	for(int i=1,u,v;i<n;i++){
		cin>>u>>v;
		a[u].push_back(v);
		a[v].push_back(u);
		p=p*2%mod;
	}
	dfs(1,0);
	for(int i=1;i<=n;i++){
		ans=(ans+1ll*val[i]*dep[i]%mod)%mod;
	}
	ans=1ll*ans*p%mod;
	cout<<ans;
	return 0;
}

```


---

## 作者：一只书虫仔 (赞：5)

![](https://cdn.luogu.com.cn/upload/image_hosting/zxxf3qro.png)

$$\color{Gold}\sf dWoi\ Round\ 1\ C\ Sweet\ Fruit\ Chocolate$$

written by lgswdn

首先一个比较重要的转化，就是每个节点对答案做出的影响是独立的，所以我们可以分开算每个节点对答案的贡献。首先，如果在节点 $u$ 上放上了水果，那么受到影响的将会是 $u$ 及其祖先们，只有它们中的每个节点会增加 $a_u$ 的收益，所以假设 $u$ 及其祖先们一共有 $p_u$个，我们可以发现这个节点如果放了水果，那么将会带来 $p_u\times a_u$ 的收益。在所有 $2^n$ 种情况中，有 $2^{n-1}$ 种情况是节点 $u$ 放水果的。所以 $u$ 对答案的贡献是 $2^{n-1}a_up_u$。所以我们最终的答案为

$$
ans=2^{n-1} \sum_{u=1}^{n} a_up_u
$$

代码如下

```cpp
#include<bits/stdc++.h>
#define int long long
#define rep(i,a,b) for(register int i=(a);i<=(b);i++)
#define per(i,a,b) for(register int i=(a);i>=(b);i--)
using namespace std;
const int N=1e6+9,mod=998244353;

inline int read() {
    register int x=0, f=1; register char c=getchar();
    while(c<'0'||c>'9') {if(c=='-') f=-1; c=getchar();}
    while(c>='0'&&c<='9') {x=(x<<3)+(x<<1)+c-48,c=getchar();}
    return x*f;
}

struct edge {int to,nxt;} e[N*2]; int hd[N],tot;
void add(int u,int v) {e[++tot]=(edge){v,hd[u]};hd[u]=tot;}

int n,a[N],p[N],ans;
void dfs(int u,int fa) {
	p[u]=p[fa]+1;
	ans=(ans+p[u]*a[u]%mod);
	for(int i=hd[u],v;i;i=e[i].nxt) {
		if((v=e[i].to)==fa) continue;
		dfs(v,u);
	}
}

signed main() {
	n=read();
	rep(i,1,n) a[i]=read();
	rep(i,1,n-1) {
		int u=read(), v=read();
		add(u,v), add(v,u);
	}
	dfs(1,0);
	rep(i,1,n-1) ans=(ans*2)%mod;
	printf("%lld\n",ans);
	return 0;
} 
```

---

## 作者：狛枝风斗 (赞：2)

#### Description

> 给定一棵 $n$ 个节点的树，第 $i$ 个节点的点权可以选择为 $0$，也可以选择为 $a_i$。每个节点的价值为自身加上子树的点权和。求对于所有的 $2^n$ 种放置方式，得到的价值和总和是多少。

#### Solution

有点像 P7223 的树上形式。

如果第 $i$ 个节点被选择了，那么他的点权 $a_i$ 就会被计算在内。能被他影响的只有所有子树中有节点 $i$ 的，即他的祖先。假设第 $i$ 个节点的祖先有 $cur_i$ 个，那么对于每个祖先节点的价值都会算上 $a_i$，也就是可以提取公因数一下，对总答案的贡献 $k_i=cur_i \times a_i$。

最后算 $k_i$ 的和，但是注意，每次有一半的情况是让这个节点的点权计算在内的，所以答案应该是：

$$\sum\limits_{i=1}^n(2^{n-1} \times k_i)=2^{n-1}\times \sum\limits_{i=1}^nk_i$$

---

## 作者：qwqszxc45rtnhy678ikj (赞：1)

P7159 是可能第一眼看不出来结论的题（雾？

我们先看一个全部选择的方案。如果全部选择的话，它就会被它所有的祖先结点和它本身所计入价值，那么我们设 $p_i$ 为 $i$ 结点所有的祖先结点的数量（这里包括自己），那么答案为所有 $p_ia_i$ 的和。

接着，如果所有方案放进来的话，一个结点会被选择 $2$ 的 $n-1$ 次方次，直接把刚才的结论乘以这么多次就是了。

AC 记录代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
inline long long read(){
	long long x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
    	if(ch=='-')f=-1;
    	ch=getchar();
	}
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return x*f;
}
long long tmp=2,k,s=1,a[1000010];
int n,t1,t2,dep[1000010],mod=998244353,ans;
vector<int>d[1000010];
void dfs(long long now,long long fa){//dfs求深度（这里是dep(i)）
	dep[now]=dep[fa]+1;
	for(int i=0;i<d[now].size();i++)
		if(d[now][i]!=fa)
			dfs(d[now][i],now);
}
int main(){
	n=read();
	k=n-1;
	while(k){//计算2的n-1次方
		if(k&1)s=s*tmp%mod;
		tmp=tmp*tmp%mod;
		k>>=1;
	}
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<n;i++){//建图
		t1=read(),t2=read();
		d[t1].push_back(t2);
		d[t2].push_back(t1);
	}
	dfs(1,0);
	for(int i=1;i<=n;i++)//最后把所有相加
		ans=(ans+dep[i]*a[i]%998244353*s%998244353)%998244353;
	cout<<ans;
	return 0;
}
```


---

## 作者：Liyuanhao123456 (赞：0)

### 题意

每一个节点 $u$ 都可以带来一个营养值，即以 $u$ 为根的子树中水果的数量。

每一种放置方案的答案即为此种方案中每个节点的答案之和。

每个节点可以选择放或不放，题目要求求出所有 $2^n$ 种水果放置方案所获营养值之和。

### 分析

考虑在一个节点放置水果对此种放置方案的贡献：若在节点 $u$ 放置水果，$u$ 及 $u$ 的所有祖先的营养值都会加上 $a_u$，总共产生 $dep_i$ 次贡献。

那么什么时候一个节点会产生贡献呢？当然是选择在这个节点放置水果的时候！不难发现，对于一个确定节点，在总共 $2^n$ 种情况中有一半是选择在这个位置放置水果，另一半是不放，所以一个节点对总答案的贡献为 $2^{n-1} \times a_u \times dep_i$。

到这里，我们就可以在 $O(n)$ 时间内解决这道题了：只需求出每个点的 $dep$，再枚举所有点统计答案即可。

### Lyy's ugly Code

```cpp
#include<iostream>
#define LL long long
using namespace std;
const int maxn=1000005;
const int mod=998244353;
int n,a[maxn];
LL ans,mul=1;
struct edge{
	int to,nxt;
};
int head[maxn],totr=1;
edge T[maxn<<1];
inline void add_edge(int u,int v) {
	T[++totr].nxt=head[u];
	T[totr].to=v;
	head[u]=totr;
}
int dep[maxn];
inline void dfs(int u,int fa) {
	dep[u]=dep[fa]+1;
	for(int i=head[u];i;i=T[i].nxt) {
		int v=T[i].to;
		if(v==fa)continue;
		dfs(v,u);		
	}
}
int main() {
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]),mul=i>1?(mul*2)%mod:mul;
	//顺便求 2^(n-1) 
	for(int i=1;i<n;i++) {
		int u,v;
		scanf("%d%d",&u,&v);
		add_edge(u,v);add_edge(v,u);
	}
	dfs(1,0);
	//求dep 
	for(int i=1;i<=n;i++) {
		LL tmp=((mul*dep[i])%mod)*a[i]%mod;
		ans+=tmp;
		ans%=mod;
	}
	//统计答案，记得取模 
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：Legitimity (赞：0)

根据题目描述，并且数据范围显然需要 $\Theta(N)$ 复杂度的算法，那么我们可以大胆的猜想一下结论。

因为最后求的是所有方案营养值之和，不要求具体每个方案，我们可以把这些方案放在一起看。稍微观察一下不难发现，当一个节点 $x$ 被选中时，它自己需要算一遍营养值，它的父亲也需要算一遍营养值，它父亲的父亲……依次类推，节点 $x$ 的所有祖先都要算一遍它的营养值。所以当节点 $x$ 被选中时，根节点的营养值要加上 $a_x \times depth_x$。

那么一个节点在所有方案中被选的次数是多少？（小学生都会发现）所有方案中节点 $x$ 选中和被选中的方案各有一半，所以一共会被选中 $2^{n-1}$ 次。通过上面的分析，所有方案的营养值之和就是 $2^{n-1} \times \sum_{i=1}^{n}a_i \times depth_i$

那么思路就出来了：先把树爆搜一遍，得到每个节点 $depth$，计算出$\sum_{i=1}^{n}a_i \times depth_i$，再乘上 $2^{n-1}$ 就行了。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define rg register
#define ll long long
#define mod 998244353*1LL
inline ll read(){
	rg ll ret=0,f=0;
	char ch=getchar();
    while(!isdigit(ch)){
		if(ch=='-') f=1;
		ch=getchar();
	}
    while(isdigit(ch)){
		ret=ret*10+ch-48;
		ch=getchar();
	}
    return f?-ret:ret;
}
struct node{
	int nex,to;
}e[2000005];
ll n,a[1000005],u,v,head[1000005],cnt;
ll dep[1000005],ans;
inline void add(int u,int v){
	e[++cnt].nex=head[u];
	e[cnt].to=v;
	head[u]=cnt;
}
inline void dfs(int x,int fa){ //初始化得到深度 
	dep[x]=dep[fa]+1;
	for(rg int i=head[x];i;i=e[i].nex){
		if(e[i].to!=fa){
			dfs(e[i].to,x);
		}
	}
}
int main(){
    n=read();
    for(rg int i=1;i<=n;++i){
    	a[i]=read(); a[i]%=mod;
    } 
    for(rg int i=1;i<n;++i){
    	u=read(); v=read();
    	add(u,v); add(v,u);
    }
    dfs(1,0);
    for(rg int i=1;i<=n;++i){
    	ans+=a[i]*dep[i]%mod;
    	ans%=mod; 
    }//计算单次的营养值之和 
    ll p=n-1,base=2,tmp=1;
    while(p){
    	if(p&1){
    		tmp*=base; tmp%=mod;
    	}
    	base*=base; base%=mod;
    	p>>=1;
    }//计算 2^(n-1) 
    printf("%lld",tmp*ans%mod); 
    return 0;
}
```


---

## 作者：Demoe (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/P7159)

~~验题人题解~~

## 题意

- 给定一棵树，对于每个节点的权值可以为 $0$ 或 $a_i$，每个节点的贡献为其自身与子树权值和。

- 对于 $2^n$ 种权值选择方案，求贡献和，对 $998244353$ 取模。

## Sol

~~别提 提就是验题时看错题了~~

~~好像也算不上树形dp~~

考虑每个节点的贡献。

显然对于每个选中它的局面，它的贡献是 $dep_i\times a_i$。

而选中它的局面有 $2^{n-1}$ 个。

故答案为 $2^{n-1}\sum\limits_{i=1}^ndep_i\times a_i$。

其中 $dep_i$ 提一下根即可。

```cpp
// wish to get better qwq

#include<bits/stdc++.h>
#define re register int
#define pb push_back

using namespace std;
typedef long long ll;

template <typename T> void rd(T &x){
	int fl=1;x=0;char c=getchar();
	for(;!isdigit(c);c=getchar()) if(c=='-') fl=-fl;
	for(;isdigit(c);c=getchar()) x=(x<<3)+(x<<1)+c-'0';
	x*=fl;
}
void wr(int x){
	if(x<0) x=-x,putchar('-');
	if(x<10) putchar(x+'0');
	if(x>9) wr(x/10),putchar(x%10+'0');
}

// ---------- IO ---------- //

const ll N=1e6+5,mod=998244353;
ll n,a[N],ans,dep[N],vst[N];
vector<ll> e[N];

ll pw(ll x,ll y){
	ll sum=1;
	while(y){
		if(y&1) sum=(sum*x)%mod;
		x=(x*x)%mod;y>>=1;
	}
	return sum;
}

inline void lift(ll x,ll fa){
	dep[x]=dep[fa]+1;ans=(ans+a[x]*dep[x]%mod)%mod;
	for(re i=0;i<e[x].size();i++)
		if(e[x][i]!=fa) lift(e[x][i],x);
}

// ----------  ---------- //

int main(){
//	freopen("C.in","r",stdin);
//	freopen("C.out","w",stdout);
	rd(n);
	for(re i=1;i<=n;i++) rd(a[i]),a[i]%=mod;
	int u,v;
	for(re i=1;i<n;i++){
		rd(u);rd(v);
		e[u].pb(v);e[v].pb(u);
	}
	lift(1,0);
	wr((ans*pw(2,n-1))%mod);puts("");
	return 0;
}

// ---------- Main ---------- //
```

---

