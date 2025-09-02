# Boboniu and Jianghu

## 题目描述

Since Boboniu finished building his Jianghu, he has been doing Kungfu on these mountains every day.

Boboniu designs a map for his $ n $ mountains. He uses $ n-1 $ roads to connect all $ n $ mountains. Every pair of mountains is connected via roads.

For the $ i $ -th mountain, Boboniu estimated the tiredness of doing Kungfu on the top of it as $ t_i $ . He also estimated the height of each mountain as $ h_i $ .

A path is a sequence of mountains $ M $ such that for each $ i $ ( $ 1 \le i <       |M| $ ), there exists a road between $ M_i $ and $ M_{i+1} $ . Boboniu would regard the path as a challenge if for each $ i $ ( $ 1\le i<|M| $ ), $ h_{M_i}\le h_{M_{i+1}} $ .

Boboniu wants to divide all $ n-1 $ roads into several challenges. Note that each road must appear in exactly one challenge, but a mountain may appear in several challenges.

Boboniu wants to minimize the total tiredness to do all the challenges. The tiredness of a challenge $ M $ is the sum of tiredness of all mountains in it, i.e. $ \sum_{i=1}^{|M|}t_{M_i} $ .

He asked you to find the minimum total tiredness. As a reward for your work, you'll become a guardian in his Jianghu.

## 说明/提示

For the first example:

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1394D/6d7c9860b48141348a65d76336aec032250a8094.png)In the picture, the lighter a point is, the higher the mountain it represents. One of the best divisions is:

- Challenge $ 1 $ : $ 3 \to 1 \to 2 $
- Challenge $ 2 $ : $ 5 \to 2 \to 4 $

The total tiredness of Boboniu is $ (30 + 40 + 10) + (20 + 10 +       50) = 160 $ . It can be shown that this is the minimum total tiredness.

## 样例 #1

### 输入

```
5
40 10 30 50 20
2 3 2 3 1
1 2
1 3
2 4
2 5```

### 输出

```
160```

## 样例 #2

### 输入

```
5
1000000 1 1 1 1
1000000 1 1 1 1
1 2
1 3
1 4
1 5```

### 输出

```
4000004```

## 样例 #3

### 输入

```
10
510916 760492 684704 32545 484888 933975 116895 77095 127679 989957
402815 705067 705067 705067 623759 103335 749243 138306 138306 844737
1 2
3 2
4 3
1 5
6 4
6 7
8 7
8 9
9 10```

### 输出

```
6390572```

# 题解

## 作者：Soulist (赞：15)


给定 $n$ 个节点的树，每个点有点权 $v_i$，有高度 $h_i$

将原树的所有边划分成若干条链，使得每条链的高度递增，最小化所有链的点权和。

$h_i,w_i\in[1,10^6],n\le 2\times 10^5$

### Solution

对于边 $u,v$ 假设 $h_u\ne h_v$，那么这条边的方向确定。

一个点对答案的贡献是经过他的链数，设 $a$ 为指向它的边的数量，$b$ 为指出去的边的数量，那么不难发现其贡献为 $w_i\times \max\{a,b\}$

问题等价于你需要给高度相等的链确定方向最小化贡献和。

设 $f_{u,0/1}$ 分别表示以 $u$ 为根的子树，$u$ 到父亲的边强制为连入/连出情况下的贡献和。

更具体的，问题变成给定 $m$ 个二元组 $(f_{v,0},f_{v,1})$ 给每个二元组选择一个权值，然后设 $a,b$ 分别为 $0/1$ 的数量，$k=\max(a,b)$ 贡献为权值和加上 $k\times w_i$（当然部分是固定的，但是处理起来也很简单）

可以先假设所有元素选 $0$，然后依次枚举 $1$ 的数量，不难发现我们肯定优先选 $f_{v,1}-f_{v,0}$ 尽可能小的元素。

然后即时更新一下贡献，特判一下 $1$ 号节点，这个题就做完了。

复杂度是 $\mathcal O(\sum \deg(i) \log)$ 大约是 $\mathcal O(n\log n)$

感觉评分偏高了...

$Code:$

```cpp
#include<bits/stdc++.h>
using namespace std ;
#define Next( i, x ) for( register int i = head[x]; i; i = e[i].next )
#define rep( i, s, t ) for( register int i = (s); i <= (t); ++ i )
#define drep( i, s, t ) for( register int i = (t); i >= (s); -- i )
#define re register
#define int long long
#define pb push_back
int gi() {
	char cc = getchar() ; int cn = 0, flus = 1 ;
	while( cc < '0' || cc > '9' ) {  if( cc == '-' ) flus = - flus ; cc = getchar() ; }
	while( cc >= '0' && cc <= '9' )  cn = cn * 10 + cc - '0', cc = getchar() ;
	return cn * flus ;
}
const int N = 2e5 + 5 ; 
const int inf = 1e15 + 7 ;
int n, cnt, w[N], h[N], head[N], f[N][2] ; 
struct E {
	int to, next ; 
} e[N << 1] ;
void add(int x, int y) {
	e[++ cnt] = (E){y, head[x]}, head[x] = cnt,
	e[++ cnt] = (E){x, head[y]}, head[y] = cnt ; 
}
vector<int> st[N] ; 
void Dfs(int x, int fa) {
	int sum = 0, a = 0, b = 0 ; 
	Next( i, x ) {
		int v = e[i].to ; if( v == fa ) continue ; 
		Dfs(v, x) ; 
		if( h[v] == h[x] ) st[x].pb(f[v][1] - f[v][0]), sum += f[v][0], ++ a ; 
		else if( h[v] > h[x] ) ++ b, sum += f[v][1] ;
		else ++ a, sum += f[v][0] ; 
	}
	sort(st[x].begin(), st[x].end()) ;
	for(re int i = 0; i <= st[x].size(); ++ i) {
		f[x][0] = min( f[x][0], sum + max(a, b + (x != 1)) * w[x] ) ;
		f[x][1] = min( f[x][1], sum + max(a + (x != 1), b) * w[x] ) ; 
		-- a, ++ b ;
		if( i < st[x].size() ) sum += st[x][i] ; 
	}
}
signed main()
{
	n = gi() ; int x, y ; 
	rep( i, 1, n ) w[i] = gi() ; 
	rep( i, 1, n ) h[i] = gi() ; 
	rep( i, 2, n ) x = gi(), y = gi(), add(x, y) ; 
	memset( f, 63, sizeof(f) ) ;
	Dfs(1, 1) ; 
	cout << min(f[1][0], f[1][1]) << endl ; 
	return 0 ;
}
```


---

## 作者：Lucky_Glass (赞：6)

\> Link:推荐在我的[个人博客](https://4rds5h.coding-pages.com/2020/20Sep14thArt2/)上阅读~

## 解析

所谓单调递增或单调递减，其实只用看成一条**有向**的链，$a_i$ 大的点指向 $a_i$ 小的点即可。

若 $a_u\neq a_v$ ，则边 $(u,v)$ 的方向是固定的。不妨假设所有边的方向都固定了，设点 $u$ 的入度为 $p_u$、出度为 $q_u$，则在最优的情况下 $u$ 会在 $\max\{p_u,q_u\}$ 条有向链中产生一次贡献（即尽可能将入边与出边匹配）。

但是如果 $a_u=a_v$，则需要确定 $(u,v)$ 的方向。注意到对于一个点，**重要的只有其入度和出度**，因此考虑树形DP。

$f_{u,0}$ 表示 $u$ 到其父节点的边是从 $u$ 连“出”，$f_{u,1}$ 表示连“入”到 $u$。

接下来就是比较套路的DP方法。在 $u$ 点转移时，设其子节点 $v_1,v_2,\dots,v_k$ 的边需要定向，则先全部定向为从 $u$ 指向 $v_i$；再考虑改变一条边的方向，使得DP值的变化最小，即取 $f_{v,0}-f_{v,1}$ 最小的 $v$ 改变方向，计算答案。

对 $v_1,v_2,\dots,v_k$ 按 $f_{v,0}-f_{v,1}$ 从小到大排序，依次改变边的方向，维护此时的 $p_u,q_u$，从而求出 $u$ 的DP值。

总复杂度 $O(n\log n)$，即每个点排序的复杂度。

## 源代码
```cpp
/*Lucky_Glass*/
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

typedef long long ll;
const int N=2e5+10;
const ll INF=(1ll<<60);
#define ci const int &

int n;
int hgt[N],val[N];
ll f[N][2],tmp[N],ans;

struct GRAPH{
	int head[N],to[N<<1],nxt[N<<1],ncnt;
	void AddEdge(ci u,ci v){
		int p=++ncnt,q=++ncnt;
		to[p]=v,nxt[p]=head[u],head[u]=p;
		to[q]=u,nxt[q]=head[v],head[v]=q;
	}
	inline int operator [](ci u){return head[u];}
}Gr;

inline int Read(){
	register int r=0,c=getchar();
	while(c<'0' || '9'<c) c=getchar();
	while('0'<=c && c<='9') r=(r<<1)+(r<<3)+(c^'0'),c=getchar();
	return r;
}
//0:up ; 1:down
void DP(ci u,ci fa){
	ll sum=0;
	f[u][0]=f[u][1]=INF;
	int in=0,out=0;
	for(int it=Gr[u];it;it=Gr.nxt[it]){
		int v=Gr.to[it];
		if(v==fa) continue;
		DP(v,u);
		if(hgt[v]<hgt[u]) sum+=f[v][0],in++;
		if(hgt[v]>hgt[u]) sum+=f[v][1],out++;
	}
	int ntmp=0;
	for(int it=Gr[u];it;it=Gr.nxt[it]){
		int v=Gr.to[it];
		if(v==fa || hgt[v]!=hgt[u]) continue;
		sum+=f[v][1];
		tmp[++ntmp]=f[v][0]-f[v][1];
		out++;
	}
	sort(tmp+1,tmp+1+ntmp);
	for(int i=0;i<=ntmp;i++,in++,out--,sum+=tmp[i]){
		if(u==1)
			ans=min(ans,sum+1ll*max(in,out)*val[u]);
		else{
			f[u][0]=min(f[u][0],sum+1ll*max(in,out+1)*val[u]);
			f[u][1]=min(f[u][1],sum+1ll*max(in+1,out)*val[u]);
		}
	}
}
int main(){
	n=Read();
	for(int i=1;i<=n;i++) val[i]=Read();
	for(int i=1;i<=n;i++) hgt[i]=Read();
	for(int i=1;i<n;i++) Gr.AddEdge(Read(),Read());
	ans=INF;
	DP(1,0);
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：233zhang (赞：5)

# 题意:



有一颗 $n$ 个节点的树 $(1\leq n\leq 2\times 10^5)$，第 $i$ 个点有参数 $a_{i},b_{i}$。 $(1 \leq a_{i},b_{i} \leq 10^6)$。

现在要求把这棵树剖分成若干条链（链包括端点），使每条边恰好出现在一条链中，且要求链上的点的 $b_{i}$ **单调不降或单调不增**。一条链的权值定义为链上所有点的 $a_{i}$ 之和。

求在所有剖分方案中，链的总权值最小为多少？



# 算法：



树形dp



# 思路：



对于一条链的**单调不降或单调不增**，本质上就是规定了一条链的方向，我们可以规定链的方向始终为 $b_{i}$  大的点指向 $b_{i}$ 小的点。

我们很容易想到，对于一个点 $u$，与它相连的 $v$ 点，若 $b_{u} \ne b_{v}$，其方向是固定的，只有当 $b_{u} = b_{v}$ 时，方向需要自己确定，由于我们目前对于这个问题，并不知道如何选择最优，于是我们将它暂放一旁。

也就是说，我们现在假设任意点和与其相连的点，它们的边的方向都已经确定，我们如何计算贡献？

对于一个点，它对答案的贡献就是经过它的链数。设 $x$ 为指向它的边的数量， $y$ 为它指出去的边的数量，即 $x$ 为它的入度， $y$ 为它的出度。我们不难发现，一个入边可以和一个出边搭配成一条链，也就是说，一个入边加上一个出边可以对答案产生 $a_{i}$ 的贡献。我们在将入边和出边一一搭配后，可能还会剩余一些入边或出边（两者只能剩下其中一种），这些边同样也会对答案产生相同的贡献。

因此，我们可以知道，该点的贡献为 $a_{i} \times \max(x,y)$。

我们令 $dp_{u,0/1}$ 表示以 $u$ 为根节点的子树， $u$ 与父节点的边为入边/出边。在统计以 $u$ 为根节点的这一子树时，由于我们不会遍历回它的父亲节点，也就是说，对于 $u$ 与父节点这一条边时，对于 $u$ 节点，它的入边或者出边是少统计了一位的。但是树的根节点，因为其没有父节点，它的入边和出边是正确的。若我们令根节点始终为 $1$，我们就可以得到以下递推式。

$$dp_{u,0} = \sum dp_{v,0/1} + \max(x,y+(u \ne 1)) \times a_{u}$$

$$dp_{u,1} = \sum dp_{v,0/1} + \max(x+(u \ne 1),y) \times a_{u}$$

（当 $b_{u} > b_{v}$ 时，取 $dp_{v,0}$；当 $b_{u} < b_{v}$ 时，取 $dp_{v,1}$）。

接下来我们考虑 $b_{u} = b_{v}$ 的情况，我们可以先令这样的情况全为入边，但这样肯定不能保证其为最优解，我们要将其中一些边转换为出边，我们可以枚举转换数量。那么，当转换数量固定时，我们怎么样转换才是最优的呢？

我们不难想到，当转换数量固定时，该点本身对于总贡献是固定的，也就是说，它的优劣完全取决于它的子节点。而显而易见的是， $dp_{v,1} - dp_{v,0}$ 越小的点，必然是更优的方案。因此我们可以记录 $dp_{v,1} - dp_{v,0}$ 并排序，根据排序顺序遍历转换数量求出最优解，因此代码如下：

```
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N=2e5+5;
const int inf=0x3f3f3f;
const int mod=1e9+7;

vector<int>son[N];
vector<int>q[N];
int x,y,n;
ll t[N],w[N],dp[N][2];

void dfs(int u,int fa) {
    ll sum=0,a=0,b=0;
    for (auto v:son[u]) {
        if (v==fa) continue;
        dfs(v,u);
        if (w[v]==w[u]) {sum+=dp[v][0];q[u].push_back(dp[v][1]-dp[v][0]);a++;}
        else if (w[v]>w[u]) sum+=dp[v][1],b++;
        else sum+=dp[v][0],a++;
        //cout<<v<<" "<<u<<" "<<dp[v][0]<<" "<<dp[v][1]<<" "<<sum<<" "<<a<<" "<<b<<"\n";
    }
    //cout<<u<<" "<<sum<<"\n";
    sort(q[u].begin(),q[u].end());
    dp[u][0]=sum+max(a,b+(u!=1))*t[u];
    dp[u][1]=sum+max(a+(u!=1),b)*t[u];
    //cout<<"test"<<u<<":"<<a<<" "<<b<<" "<<sum<<" "<<dp[u][0]<<" "<<dp[u][1]<<"\n";
    for (auto i:q[u]) {
        --a,++b,sum+=i;
        dp[u][0]=min(dp[u][0],sum+max(a,b+(u!=1))*t[u]);
        dp[u][1]=min(dp[u][1],sum+max(a+(u!=1),b)*t[u]);
        //cout<<"test"<<u<<":"<<a<<" "<<b<<" "<<sum<<" "<<dp[u][0]<<" "<<dp[u][1]<<"\n";
    }
    //cout<<u<<" "<<dp[u][0]<<" "<<dp[u][1]<<"\n";
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin>>n;
    for (int i=1;i<=n;i++) cin>>t[i];
    for (int i=1;i<=n;i++) cin>>w[i];
    for (int i=1;i<n;i++) {
        cin>>x>>y;
        son[x].push_back(y);son[y].push_back(x);
    }
    dfs(1,1);
    cout<<min(dp[1][0],dp[1][1])<<"\n";

    return 0;
}
```

---

## 作者：Locix_Elaina_Celome (赞：2)

[更差（？）的阅读体验](https://www.luogu.com.cn/blog/XXR-Elaina/solution-cf1394d)

# [CF1394D Boboniu and Jianghu](https://www.luogu.com.cn/problem/CF1394D) 题解

## 题意
> 给出一棵树，每个数有两个点权 $(c,h)$，现在要将整棵树分为若干个链。链之间没有相同的边（可以有相同的点），链上的点要满足 $h$ 单调不增/不降。一条链的权值定义为链上所有点的 $c$ 之和，问整棵树最小总权值是多少。
>
> $1\le n\le 2\times 10^5 \qquad 1\le c,h\le 10^6$

## 题解

首先因为链不分方向，所以可以钦定所有都是单调不降的。所以可以把边按左右端点的 $h$ 定向，这里钦定由 $h$ 小的指向 $h$ 大的。

首先我们发现，如果有一条链在点 $u$ 结束，另一条在点 $u$ 出发，这样一定是不优的，因为一定可以把两条链合并减少一次 $u$ 的贡献。

根据这个可以得出这样的结论：设点 $u$ 的入度为 $a$，出度为 $b$，那么其贡献就是 $\max(a,b)\times c_u$。

然后就发现一个问题：有的边其两端的 $h$ 相等无法定向。

然后就用某科学的树形 dp 来解决这个问题。设 $dp_{u,0/1}$ 表示指定 $u$ 这个点与父亲 $fa$ 的连边由 $fa$ 连向 $u$/由 $u$ 连向 $fa$ 的情况下 $u$ 这个子树的最小贡献。

那么对于一个结点 $u$，先把与自身 $h$ 不同的儿子权值加上，再考虑与自身 $h$ 相同的儿子。我们先设它们全都取 $dp_1$，然后把这些儿子按照 $dp_0-dp_1$ 排序，逐个贪心调整，在过程中取最小值。

注意特判根节点。

## 代码

```cpp
using namespace std;
#include<bits/stdc++.h>
//#include<cstdio>
//#include<cstring>
//#include<string>
//#include<iostream>
//#include<utility>
//#include<algorithm>
#define MAX(x,y) (x<y?y:x)
#define MIN(x,y) (x<y?x:y)
#define ABS(x) (x<0?-x:x)
#define lb(x) ((x)&(-(x)))
#define N 400005
#define LL long long
#define LD long double
#define int LL
//#define double LD
#define P 1000000007
#ifdef _WIN32
#define getchar _getchar_nolock
#define putchar _putchar_nolock
#elif _WINDOWS_
#define getchar _getchar_nolock
#define putchar _putchar_nolock
#else
#define getchar getchar_unlocked
#define putchar putchar_unlocked
#endif
constexpr double EPS=(1e-9);
#ifdef int
constexpr int INF=1211081101201201140;
#else
constexpr int INF=1145141919;
#endif
template<typename T>T Max(T x,T y){return MAX(x,y);}
template<typename T>T Min(T x,T y){return MIN(x,y);}
template<typename T>T Abs(T x){return ABS(x);}
template<typename T>void Swap(T&x,T&y){x^=y^=x^=y;}
template<typename T>T Gcd(T x,T y){while(y^=x^=y^=x%=y);return x;}
template<typename T>
T qp(T a,T b){T sum=1;
while(b){if(b&1)sum=(sum*a)%P;a=(a*a)%P;b>>=1;}return sum;}
template<typename T>
void read(T&x){
x=0;char c=getchar();/*T fl=1;*/
while(c<'0'||c>'9'){/*if(c == '-')fl=-1;*/c=getchar();}
while('/'<c&&c<':'){x=(x<<3)+(x<<1)+c-'0';c=getchar();}/*x*=fl;*/}
template<typename T>
void write(T x){if(x<0){x=-x;putchar('-');}
if(x>9){write(x/10);}putchar(x%10|48);}
int n;
int a[N],b[N];
int c[N],h[N]; 
int t[N],las[N],fir[N],num=1;
void add(int u,int v){
t[++num]=v;las[num]=fir[u];fir[u]=num;
t[++num]=u;las[num]=fir[v];fir[v]=num;}
int dp[N][2];
struct st{
	int f,id;
	bool operator < (const st& oth) const{return oth.f<f;}
};
void dfs(int u,int fa){
	priority_queue<st> q;
	int sm=0;
	int f0=0,f1=0;
	int ai=a[u],bi=b[u];
	for(int i=fir[u];i;i=las[i]){
		if(t[i]==fa)continue;
		dfs(t[i],u);
		if(h[u]<h[t[i]])dp[u][0]+=dp[t[i]][0],dp[u][1]+=dp[t[i]][0];
		else if(h[t[i]]<h[u])dp[u][0]+=dp[t[i]][1],dp[u][1]+=dp[t[i]][1];
		else sm+=dp[t[i]][1],q.push({dp[t[i]][0]-dp[t[i]][1],t[i]}),bi++;
	}
	if(u==1||h[u]!=h[fa]){
		f0=f1=sm+Max(ai,bi)*c[u];
		while(q.size()){
			int v=q.top().id;
			q.pop();
			bi--;
			ai++;
			sm+=dp[v][0]-dp[v][1];
			f0=f1=Min(f1,sm+Max(ai,bi)*c[u]);
		}
		dp[u][0]+=f0,dp[u][1]+=f1;
	}
	else{
		f0=sm+Max(ai,bi+1)*c[u],f1=sm+Max(ai+1,bi)*c[u];
		while(q.size()){
			int v=q.top().id;
			q.pop();
			bi--;
			ai++;
			sm+=dp[v][0]-dp[v][1];
			f0=Min(f0,sm+Max(ai,bi+1)*c[u]),f1=Min(f1,sm+Max(ai+1,bi)*c[u]);
		}
		dp[u][0]+=f0,dp[u][1]+=f1;
	}
}
#undef int
int main(){
#define int LL
	read(n);
	for(int i=1;i<=n;i++)read(c[i]);
	for(int i=1;i<=n;i++)read(h[i]);
	for(int i=1;i<n;i++){
		int u,v;
		read(u);
		read(v);
		if(h[u]<h[v])a[u]++,b[v]++;
		if(h[v]<h[u])a[v]++,b[u]++;
		add(u,v);
	}
	dfs(1,0);
	write(dp[1][0]);
	return 0;
#undef int
}
```

---

## 作者：_fairytale_ (赞：2)

## 前言

补题的时候看见了这道题，想我在 ZR 的朋友们了，NOIP 之后他们几乎全都退役了。我常常想 OIer 的夏天是不会随着暑假结束而结束的，但现实告诉我，也只是晚两个月而已。前两天我这里下了一场大雪，也许这正像金华的那场大雨一样。然后题解应该不是写很长小作文的地方，那就，感谢你们为我的 OI 生涯带来的色彩，谢谢你们，再见，祝好。

本文的变量名使用原题面的名称，即 luogu 题面中的 $a,b$ 分别对应本文的 $t,h$。

## 正文

借用了这位大佬题解的思路 [@duyi](https://www.luogu.com.cn/user/100674) 。

注意到单调不增的链相当于反方向的单调不减的链，因此不妨直接钦定剖分出的链单调不减。因此对于一条连接两个 $h$ 不同的点的边，它的方向已经确定了，一定是由 $h$ 小的点指向 $h$ 大的点，比较难搞的只有连接两个 $h$ 相同的点的边。

然后是题目里的这个剖分可以看成，初始方案是每条边单独划分进一个集合，然后我们逐渐把链拼接起来，每把两条有共同端点 $u$ 的链拼接起来，总权值就减少 $t_u$，因此此时我们的任务变成使减少的总权值最大。

树上的最优化问题，我们考虑树形 DP。

具体地，设 $f[u][0]$ 表示只考虑 $u$ 子树中的点，且 $u$ 到 $fa[u]$ 的边为 $u\to fa[u]$，总权值减小的最大值，同样地，$f[u][1]$ 表示连边为 $fa[u]\to u$，总权值减小的最大值。

然后 $u$ 的儿子 $v$ 有三类：$h_v<h_u,h_v<h_u,h_v=h_u$。

其中前两种是好处理的，这里以第一种举例子。只需要将 $f[u][0/1]\gets f[u][0/1]+f[v][0]$。

对于第三种儿子，我们直接通过暴力枚举来定向，令 $i$ 个儿子变成第一种，剩下的变成第二种。**这样就只剩下两种儿子了。**

那么问题就是，我怎么判断该拿哪 $i$ 个儿子变成第一种呢？这是一个经典的贪心模型，我们先让所有儿子取 $f[v][1]$，然后把所有儿子按照 $f[v][0]-f[v][1]$ 排序，取前 $i$ 大的即可。理解的话就是先让所有儿子变成第二种，然后取 $i$ 个儿子改为第一种。

在枚举 $i$ 的过程中，我们顺便将第一种儿子和第二种两两匹配。注意到更新 $f[u][0]$ 时还可以用第一种儿子与 $u\to fa$ 这条边匹配，$f[u][1]$ 同理。

代码使用了更加简洁的实现，同时附赠了一组样例。

```cpp
#include<bits/stdc++.h>
#define re register
#define il inline
#define ll long long
#define rep(x,qwq,qaq) for(re int (x)=(qwq);(x)<=(qaq);++(x))
using namespace std;
#define maxn 200010
il void ckmax(ll &x,ll y) {
	x=(x>y?x:y);
}
int n,m;
int t[maxn],h[maxn];
vector<int>g[maxn];
ll f[maxn][2];
void dfs(int u,int fa) {
	int yi=0,er=0;
	ll sum=0,sum_3=0;
	vector<ll>vec;
	for(int v:g[u]) {
		if(v==fa)continue;
		dfs(v,u);
		if(h[v]<h[u]) {
			++yi;
			sum+=f[v][0];
		} else if(h[v]>h[u]) {
			++er;
			sum+=f[v][1];
		} else {
			sum_3+=f[v][1];
			vec.emplace_back(f[v][0]-f[v][1]);
		}
	}
	sort(vec.begin(),vec.end(),greater<ll>());//greater是降序 
	int sz=vec.size();
	ll cut=0,nyi=yi,ner=er+sz;
	cut=min(nyi,ner);
	ckmax(f[u][0],sum+1ll*cut*t[u]+sum_3+(nyi>ner&&u!=1)*t[u]);
	ckmax(f[u][1],sum+1ll*cut*t[u]+sum_3+(ner>nyi&&u!=1)*t[u]);
	for(int i=0; i<sz; ++i) {
		nyi=yi+i+1,ner=er+(sz-i-1);
		cut=min(nyi,ner);
		sum_3+=vec[i];
		ckmax(f[u][0],sum+1ll*cut*t[u]+sum_3+(nyi>ner&&u!=1)*t[u]);
		ckmax(f[u][1],sum+1ll*cut*t[u]+sum_3+(ner>nyi&&u!=1)*t[u]);
	}
}
ll ans;
int u,v;
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n;
	rep(i,1,n)cin>>t[i];
	rep(i,1,n)cin>>h[i];
	rep(i,2,n) {
		cin>>u>>v;
		ans+=t[u]+t[v];
		g[u].emplace_back(v);
		g[v].emplace_back(u);
	}
	dfs(1,0);
	cout<<ans-f[1][0];
	return 0;
}
/*
in:
6
1 5 0 3 4 4 
4 4 2 4 3 4 
1 2
4 3
6 4
6 5
1 6
out:
21
*/
```

---

## 作者：LJ07 (赞：2)

简单题。

套路地想到树上 dp，容易想到设计状态 $f(i,0/1)$ 表示如果当前从 $i$ 点延伸出去的链 $b$ 值为递增或递减的形态时 $\sum a$ 的最小和值为多少。

转移是容易的，也就是有一些链在根节点两两合并（必须满足一条递增一条递减），或者选择不合并，并且在不合并的链中挑选一条延伸上去。

那么就考虑枚举合并的链的对数，贪心调整（用堆或者 sort 均可），然后转移。

```cpp
const int N(2e5);
int n,a[N+5],b[N+5];
long long dp[N+5][2],ans;
vector<int> G[N+5];
void dfs(int u,int fa=0)
{
  dp[u][0]=dp[u][1]=1e18;
  long long sum(0),cnt0(0),cnt1(0),SZ(0);
  priority_queue<long long,vector<long long>,greater<long long> > q0,q1;
  for (int v:G[u]) if (v!=fa) 
  {
    dfs(v,u),++SZ;
    if (b[v]<b[u]) ++cnt0,sum+=dp[v][0];
    else if (b[v]>b[u]) ++cnt1,sum+=dp[v][1];
    else
    {
      if (dp[v][0]<dp[v][1]) q0.push(dp[v][1]-dp[v][0]),sum+=dp[v][0];
      else q1.push(dp[v][0]-dp[v][1]),sum+=dp[v][1];
    }
  }
  const int R(min(SZ-max(cnt0,cnt1),SZ>>1));U(i,min(cnt0,cnt1),R) 
  {
    while (cnt0+q0.size()<i) assert(q1.size()),sum+=q1.top(),q0.push(-q1.top()),q1.pop();
    while (cnt1+q1.size()<i) assert(q0.size()),sum+=q0.top(),q1.push(-q0.top()),q0.pop();
    const int SZ0(q0.size()+cnt0),SZ1(q1.size()+cnt1),c(SZ-i);
    if (SZ0>i) cn(dp[u][0],sum+1ll*a[u]*c);
    else 
    {
      cn(dp[u][0],sum+1ll*a[u]*(c+(u!=1)));
      if (SZ1>i&&SZ1>cnt1) cn(dp[u][0],sum+q1.top()+1ll*a[u]*c);
    }
    if (SZ1>i) cn(dp[u][1],sum+1ll*a[u]*c);
    else 
    {
      cn(dp[u][1],sum+1ll*a[u]*(c+(u!=1)));
      if (SZ0>i&&SZ0>cnt0) cn(dp[u][1],sum+q0.top()+1ll*a[u]*c);
    }
  }
}
int main()
{
  rd(n);
  U(i,1,n) rd(a[i]);
  U(i,1,n) rd(b[i]);
  U(i,2,n) {int u,v;rd(u,v),G[u].push_back(v),G[v].push_back(u);}
  dfs(1),printf("%lld\n",min(dp[1][0],dp[1][1]));
  return 0;
}
```

---

## 作者：duyi (赞：2)

[求求您了求求您了进来看看更好的阅读体验吧](https://www.cnblogs.com/dysyn1314/p/13753566.html)

## 题目大意

[题目链接](https://codeforces.com/contest/1394/problem/D)

波波牛每天都在山上练习功夫。

波波牛设计了一张 $n$ 座山的地图。他用 $n-1$ 条边将山相连，保证整张图联通，也就是说，这张图形成了一个**树**的结构。

对于第 $i$ 座山，波波牛评估了在这座山上练功夫的**疲惫值** $t_i$。同时，他还计算出了每座山的**高度** $h_i$。

我们定义一条**路径**，是一个山的序列 $M$，满足 $\forall 1\leq i < |M|$，$M_i$ 和 $M_{i+1}$ 之间都有边相连。波波牛认为一条路径是一个**挑战**，当且仅当 $\forall 1\leq i < |M|:h_{M_i}\leq h_{M_{i + 1}}$。

波波牛会将所有 $n-1$ 条边划分成若干个挑战，使得每条边都恰好出现在一个挑战里。

我们定义一个挑战的**疲惫值**为该挑战里所有节点的疲惫值之和，即：$\sum_{i=1}^{|M|}h_{M_i}$。

请你划分这些挑战，使得所有挑战的疲惫值最小。你只需要输出这个最小的疲惫值。

数据范围：$1\leq n\leq 2\cdot 10^5$。

## 本题题解

考虑 $h$ 单调这个要求。我们可以理解为**给边定向**，使得同一条路径上的边方向相同（也就是从某个端点可以依次按方向经过所有边到达另一个端点）。不妨约定，对于树上的边 $(x,y)$，如果方向是 $x\rightarrow y$，则 $h_x\leq h_y$。也就是说，当 $h_x\neq h_y$ 时，边的方向是已经确定的。我们要做的是给所有 $h_x=h_y$ 的边定一个方向。

定好方向后，如何计算答案？首先，一种一定合法的方案是，每条边单独作为一条路径。此时的代价和是 $\sum_{i = 1} ^ {n} \text{deg}(i)\times t_i$，其中 $\text{deg}(i)$ 表示树上节点 $i$ 的度数。但这显然不一定是最优方案。我们来做一些调整使它变得更优。选取一个节点 $u$，一条以 $u$ 为终点的路径和一条以 $u$ 为起点的路径拼接起来，则总代价会减少 $t_u$。我们希望通过拼接一些路径，使得**总代价的“减少值”最大**。

综上所述，我们的工作有两个：

1. 给边定向。
2. 将定向好的边拼接。

这两个工作可以通过一次树形 DP 同时完成。

先任意钦定一个根节点。设 $dp[u][0]$ 表示节点 $u$ 和父亲 $fa$ 之间的边方向是 $u\rightarrow fa$，只考虑 $u$ 子树内的节点，它们最多能使总代价减少多少；$dp[u][1]$ 表示方向是 $fa\rightarrow 1$ 时，最多减少多少。特别地，对于根节点而言，它没有父亲，所以 $dp[\text{root}][0] = dp[\text{root}][1]$。值得注意的是，DP 时计算的并不是答案，$\sum_{i = 1} ^ {n} \text{deg}(i)\times t_i-dp[\text{root}][0]$ 才是答案。所以我们要使 DP 值尽可能**大**。

转移，考虑 $u$ 的儿子 $v$。可以分成三类：

1. $h_v<h_u$
2. $h_v>h_u$
3. $h_v = h_u$

设三类儿子的数量分别为 $c_1,c_2,c_3$。为了方便讨论，不妨假设 $c_1\leq c_2$（$c_1>c_2$ 时做法类似）。

对于前两类，方向是确定的，它们的 DP 值（第 1 类 $dp[v][0]$，第 2 类 $dp[v][1]$）可以直接加到 $dp[u]$ 里。并且可以先将它们尽可能多地两两配对，每成功匹配一对就使 $dp[u]$ 增大 $t_u$。于是我们会匹配掉 $c_1$ 对，并且剩下 $c_2-c_1$ 个落单的第 2 类儿子。

接下来，问题的关键是第 3 类儿子如何定向。考虑有 $i$ 个第 3 类儿子方向定为 $v\rightarrow u$，其他 $c_3-i$ 个定为 $u\rightarrow v$。那么具体选哪 $i$ 个呢？发现两种方向对 $dp[u]$ 的贡献分别为 $dp[v][0]$ 和 $dp[v][1]$，所以我们可以将第三类儿子按 $dp[v][0]-dp[v][1]$ 的值从大到小排序。然后取前 $i$ 大的。你可以把这个策略理解为：先假设全取 $dp[v][1]$，然后贪心挑 $i$ 个换成 $dp[v][0]$。

定向后，这些儿子要进行匹配。匹配有两种：和落单的第 2 类儿子匹配，或者两种方向的第 3 类儿子内部匹配。枚举了 $i$，很容易 $O(1)$ 计算出匹配的数量。

最后总结一下，$dp[u]$ 的值来自两个部分，分别是 $dp[v]$，以及 $t_u\times\text{新增的匹配数}$。对前两类儿子来说，$dp[v]$ 的贡献是确定的，对第 3 类儿子，我们枚举有 $i$ 个 $dp[v][0]$，然后贪心取 $dp[v][0] - dp[v][1]$ 前 $i$ 大的即可。新增的匹配数，又可以分为四个部分：(1) 前两类儿子，尽可能多匹配；(2) 前两类儿子匹配完多出来的部分，和第 3 类儿子匹配；(3) 第 3 类儿子内部匹配；(4) 如果最后多 $1$ 条边，可能可以和 $(u,fa)$ 匹配（视 $(u,fa)$ 的方向而定）。

时间复杂度 $O(n\log n)$，其中 $\log n$ 来自排序。

## 参考代码

```cpp
// problem: CF1394D
#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mk make_pair
#define lob lower_bound
#define upb upper_bound
#define fi first
#define se second
#define SZ(x) ((int)(x).size())

typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;

template<typename T> inline void ckmax(T& x, T y) { x = (y > x ? y : x); }
template<typename T> inline void ckmin(T& x, T y) { x = (y < x ? y : x); }

const int MAXN = 2e5;

int n, tired[MAXN + 5], hight[MAXN + 5];
ll dp[MAXN + 5][2];
vector<int> G[MAXN + 5];
vector<pair<ll, int> > eq[MAXN + 5];

void dfs(int u, int fa) {
	ll sum_le = 0, sum_gr = 0;
	int cnt_le = 0, cnt_gr = 0;
	for(int i = 0; i < SZ(G[u]); ++i) {
		int v = G[u][i];
		if(v == fa) continue;
		dfs(v, u);
		if(hight[v] < hight[u]) {
			cnt_le++;
			sum_le += dp[v][0];
		}
		else if(hight[v] > hight[u]) {
			cnt_gr++;
			sum_gr += dp[v][1];
		}
		else {
			eq[u].pb(mk(dp[v][0] - dp[v][1], v));
		}
	}
	
	if(cnt_le <= cnt_gr) {
		ll sum = sum_le + sum_gr + (ll)cnt_le * tired[u];
		int rest = cnt_gr - cnt_le;
		sort(eq[u].begin(), eq[u].end());
		reverse(eq[u].begin(), eq[u].end()); // 从大到小
		ll eqcur = 0;
		for(int i = 0; i < SZ(eq[u]); ++i) eqcur += dp[eq[u][i].se][1];
		ckmax(dp[u][0], sum + eqcur);
		ckmax(dp[u][1], sum + eqcur + (u != 1 && rest + SZ(eq[u]) > 0) * tired[u]);
		for(int i = 1; i <= SZ(eq[u]); ++i) {
			// eq 里选几个 0
			eqcur += eq[u][i - 1].fi;
			int mat = 0, have_0 = 0, have_1 = 0;
			if(i <= rest) {
				mat = i;
				have_1 = (i < rest || i < SZ(eq[u]));
			} else {
				mat = rest + min(i - rest, SZ(eq[u]) - i);
				have_0 = (i - rest > SZ(eq[u]) - i);
				have_1 = (i - rest < SZ(eq[u]) - i); 
			}
			if(u == 1) have_0 = have_1 = 0;
			ckmax(dp[u][0], sum + eqcur + (ll)(mat + have_0) * tired[u]);
			ckmax(dp[u][1], sum + eqcur + (ll)(mat + have_1) * tired[u]);
		}
	} else {
		ll sum = sum_le + sum_gr + (ll)cnt_gr * tired[u];
		int rest = cnt_le - cnt_gr;
		sort(eq[u].begin(), eq[u].end());
		ll eqcur = 0;
		for(int i = 0; i < SZ(eq[u]); ++i) eqcur += dp[eq[u][i].se][0];
		ckmax(dp[u][0], sum + eqcur + (u != 1 && rest + SZ(eq[u]) > 0) * tired[u]);
		ckmax(dp[u][1], sum + eqcur);
		for(int i = 1; i <= SZ(eq[u]); ++i) {
			// eq 里选几个 1
			eqcur -= eq[u][i - 1].fi;
			int mat = 0, have_0 = 0, have_1 = 0;
			if(i <= rest) {
				mat = i;
				have_0 = (i < rest || i < SZ(eq[u]));
			} else {
				mat = rest + min(i - rest, SZ(eq[u]) - i);
				have_0 = (i - rest < SZ(eq[u]) - i);
				have_1 = (i - rest > SZ(eq[u]) - i);
			}
			if(u == 1) have_0 = have_1 = 0;
			ckmax(dp[u][0], sum + eqcur + (ll)(mat + have_0) * tired[u]);
			ckmax(dp[u][1], sum + eqcur + (ll)(mat + have_1) * tired[u]);
		}
	}
}
int main() {
	cin >> n;
	for(int i = 1; i <= n; ++i)
		cin >> tired[i];
	for(int i = 1; i <= n; ++i)
		cin >> hight[i];
	for(int i = 1; i < n; ++i) {
		int u, v; cin >> u >> v;
		G[u].pb(v); G[v].pb(u);
	}
	dfs(1, 0);
	ll ans = 0;
	for(int i = 1; i <= n; ++i)
		ans += (ll)tired[i] * SZ(G[i]);
	// cerr << ans << endl;
	assert(dp[1][0] == dp[1][1]);
	ans -= dp[1][0];
	cout << ans << endl;
	// int i, j; while(1) { cin >> i >> j; cout << dp[i][j] << endl; }
	return 0;
}
```


---

## 作者：tommymio (赞：2)

一道 $\text{ao}$ 的思维题。

注意到英文题目中的 $\texttt{Challenge}$ 其实就是一条 **单调递增/递减** 的路径。为了方便，任取一个根，规定向根的方向的 **单调递增路径** 为向上的路径，向根的方向的 **单调递减路径** 为向下的路径。形式化的描述，就是 $\forall x\to fa_x,h_x\leq h_{fa_x}$ 是向上的路径，$\forall x\to fa_x,h_x \geq h_{fa_x}$ 是向下的路径。

那么问题就转化成：用一些有方向的路径 $\text{Path}(x \to y)$ 覆盖 $n-1$ 条边的最小花费。

我们对两类边 $(x,y)$ 分别讨论：

- 对于 $h_x\neq h_y$，根据上述定义，这样的边的方向都已确定。
- 对于 $h_x=h_y$，方向不确定，需要具体考虑。

我们考虑这题的弱化版：确保 $h_i$ 互不相同，那么就不存在 $h_x=h_y$ 的情况，即每条边方向都已确定。

我们可以想到，对于一些边可以将其合并成一条路径，减少花费。更形式化的表达，对于 $\text{Path}(x\to y),\text{Path}(y\to z)$，我们可以将它们合并成一条路径，从而减少 $t_y$ 的花费。自然我们想要这个减少量最大。

对于点 $x$，记 $y\to x$ 的路径为 $x$ 的入边，$x\to y$ 的边为 $x$ 的出边。记入边的数量为 $in_x$，出边的数量为 $out_x$，$x$ 的度为 $deg_x$。

初始时，我们令每条边 $(x,y)$ 就是一条路径 $x\to y$，易得出此时的花费为 $ans=\sum_x t_x\times deg_x$。接着我们考虑合并，根据上述分析，合并路径 $y_1\to x,x\to y_2$ 减少的花费为 $t_x$。对于点 $x$，总减少量就为 $\min(in_x,out_x)\times t_x$，对于整棵树的减少量则为 $\sum_{x=1}^n \min(in_x,out_x)\times t_x$。对于这个弱化问题，显然当 $in_x,out_x$ 趋近相同时有最优解。

现在我们回到原题。如果将 $h_x\neq h_y$ 的这些边都删掉，那么就构成了一个森林，森林中每棵树上所有点的 $h_x$ 都相同，也就是说方向完全不确定。尝试用 $\text{DP}$ 确定每条边的方向。

设 $f_x$ 为 $(x,fa_x)$ 的边方向为 $x\to fa_x$，以 $x$ 为根的子树的最大减少量，$g_x$ 为 $(x,fa_x)$ 的边方向为 $fa_x\to x$，以 $x$ 为根的子树的最大减少量。以 $f_x$ 为例，先考虑 $x$ 的子节点 $y$ 对 $x$ 产生的贡献。设 $x$ 有 $|son_x|$ 个子节点，枚举其中 $i$ 条边 $(x,y)$ 的方向为 $x\to y$，显然有 $\max_{i=0}^{|son_x|}\min(out_x+i+1,in_x+|son_x|-i)\times t_x$。

但是还需要考虑 $f_y,g_y$ 在 $i$ 条边方向确定时对 $x$ 的贡献。$i$ 条边 $(x,y)$ 的方向确定为 $x\to y$，就意味着 $f_y,g_y$ 对 $x$ 的贡献为 $\sum_{y\in S} f_y+\sum_{y\notin S} g_y(|S|=|son_x|-i)$，即取 $|son_x|-i$ 个 $f_y$ ，$i$ 个 $g_y$。可以发现这部分贡献其实是可以独立计算的，那么我们可以令这部分贡献最大。

于是需要解决这么一个问题：求$\sum_{y\in S} f_y+\sum_{y\notin S} g_y(|S|=|son_x|-i)$ 的最大值。将柿子稍加变形可得 $\sum_{y}f_y+\sum_{y\notin S} g_y-f_y$，对 $g_y-f_y$ 从大到小排序依次取前 $i$ 大即可。

以 $f_x$ 为例，根据上述贡献，状态转移方程为：
$$
f_x=\max_{i=0}^{|son_x|}\{\min(out_x+i+1,in_x+|son_x|-i)\times t_x+(\sum_{y\in S} f_y+\sum_{y\notin S} g_y(|S|=|son_x|-i))\}
$$

至于为什么 $f$ 取 $|son_x|-i$ 个而不是 $i$ 个，因为 $x\to fa_x$ 是一条 $x$ 的出边，所以要取一条出边 $x\to y$ ，而在 $y$ 的意义下就是 $y\to fa_y$，即 $g_y$。

该问题得以解决，时间复杂度为 $O(n \log n)$。

**Show the Code**
```cpp
inline void dfs(int x,int fa=0) {
    vis[x]=1;
    int num=0; ll cur=0;
    for(register int i=h[x];i;i=ver[i]) {
        int y=to[i];
        if(y==fa) continue;
        dfs(y,x);
    }
    for(register int i=h[x];i;i=ver[i]) {
        int y=to[i];
        if(y==fa) continue;
        tmp[++num]=g[y]-f[y];
        cur+=f[y];
    }
    std::sort(tmp+1,tmp+1+num,cmp);
    for(register int i=0;i<=num;++i) {
        cur+=tmp[i];
        if(fa) {
            f[x]=max(f[x],min(out[x]+i+1,in[x]+num-i)*(ll)t[x]+cur);
            g[x]=max(g[x],min(out[x]+i,in[x]+num-i+1)*(ll)t[x]+cur);
        }
        else f[x]=max(f[x],min(out[x]+i,in[x]+num-i)*(ll)t[x]+cur);
	}
}
int main() {
    int n=read();
    ll ans=0;
    for(register int i=1;i<=n;++i) t[i]=read();
    for(register int i=1;i<=n;++i) a[i]=read();
    for(register int i=1;i<n;++i) {
        int x=read(),y=read();
        ans+=t[x]+t[y];
        if(a[x]==a[y]) {add(x,y);add(y,x);}
        else {if(a[x]>a[y]) swap(x,y); ++in[x];++out[y];}
    }
    for(register int i=1;i<=n;++i) {
        if(!vis[i]) {dfs(i);ans-=f[i];}
    }
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：elbissoPtImaerD (赞：1)

先将连接不同 $b$ 的边定向。

我们只需考虑 $b_u=b_v$ 的 $(u,v)$ 定向即可。

$a_u$ 的贡献系数是 $\max (in_u,out_u)$。

树形 dp，$f_{u,0/1}$ 表示 $u$ 子树，$u$ 的父边连接的方向。

每次在节点 $u$ 尝试合并 $O(d_u)$ 个链，这个可以贪心做到总复杂度 $O(n\log n)$。

[$\color{green}{\checkmark}$](https://codeforces.com/contest/1394/submission/246775250)

---

## 作者：Eon_Sky (赞：1)

#### [$\color{blueviolet}\text{CF 杂题集（点我）}$](https://www.cnblogs.com/Eon-Sky/p/17763683.html)

#### [$\color{red}\text{博客内食用效果更佳（点我）}$](https://www.luogu.com.cn/blog/Eon/solution-cf1394d)

## 主体思路：树形 DP

## 复杂度：$O(n \log n)$

## 完整思路

首先转化题意，相当于对于每个边选定其方向，然后合并合法路径减小总代价。

考虑没有 $b_i = b_j \quad (i \not= j)$ 情况，也就是说相邻点对的大小关系是固定的。此时对于任意边 $(u, v) \quad (b_u < b_v)$，都钦定方向 $u \to v$ 是最优的。（或者都钦定为 $v \to u$，这两种方式等价，此题解中采用 $u \to v$。）此时一个点 $u$ 贡献的代价 $val_u$ 为 $\max \{ d0_i, d1_i \} \times a_u$，其中 $d0_u, d1_u$ 分别表示其入度和出度。总代价即所有点代价之和。

重新考虑原问题，我们设 $f_{i, 0/1}$ 表示节点 $i$ 子树内，在 $(i, fa_i)$ 这条边被钦定为向上/向下的最小代价。假设现在正在处理节点 $u$，对于 $b_v \not= b_u$ 的子节点 $u$ 的贡献是固定的，我们只需要考虑 $b_v = b_u$ 的贡献。我们先钦定这些边都是向上的，即 $v \to u$，接下来的问题就是从这些子节点中挑一些将其钦定为 $u \to v$，使得总代价最小。调整一个点对于 $a_u$ 的数量贡献是固定的，于是我们贪心地优先调整 $f_{u, 1} - f_{u, v}$ 较小的点。

考虑记录所有的 $b_u = b_v$ 的 $v$，将其按照 $f_{u, 1} - f_{u, v}$ 从小到大排序，每次调整贡献并尝试更新。

特别地，考虑 $f_{u, 0}$ 使 $u$ 的出度加一，$f_{u, 1}$ 使 $u$ 的入度加一，这考虑的是边 $(u, fa_u)$ 被钦定的方向，如果 $b_u \not= b_v$，那么 $0/1$ 状态中只有一个会被使用。

设 $T_u$ 表示 $u$ 的子树，$T0_u$ 表示被钦定为 $v \to u$ 的点 $v$ 的集合，$T1_u$ 表示被钦定为 $u \to v$ 的点 $v$ 的集合（向上/向下连边的两个子节点集合），于是有以下形式化的转移：

$$f_{u, 0} = \min \left\{ \sum \limits_{v \in T0_u} f_{v, 0} + \sum \limits_{v \in T1_u} f_{v, 1} + \max \left\{|T0_u|, |T1_u| + \left[u \not= 1\right] \right\}\times a_u \right\}$$

$$f_{u, 1} = \min \left\{ \sum \limits_{v \in T0_u} f_{v, 0} + \sum \limits_{v \in T1_u} f_{v, 1} + \max \left\{|T0_u| + \left[u \not= 1\right], |T1_u|\right\}\times a_u \right\}$$

以上式子中的 $\left[u \not= 1\right]$ 表示以 $1$ 为根进行 DP 时，其没有父节点，也就不存在与父节点连边的那个度数。

## 代码实现需要注意的地方：

- DP 数组需要开 **long long**。

## 参考代码：

```cpp
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef unsigned long long ULL;
typedef unsigned int UIT;
typedef double DB;
typedef pair<int, int> PII;

#define fi first
#define se second
//--------------------//
const int N = 2e5 + 5, M = 4e5 + 5;

int n, a[N], b[N];

struct Edge {
    int to, nex;
} edge[M];
int tot, head[N];

void add(int from, int to) {
    edge[++tot] = {to, head[from]};
    head[from] = tot;
}

LL f[N][2];

bool cmp(int x, int y) {
    return f[x][1] - f[x][0] < f[y][1] - f[y][0];
}

int tcnt, tem[N];

void DFS(int now, int fa) {
    for (int to, i = head[now]; i; i = edge[i].nex) {
        to = edge[i].to;
        if (to != fa)
            DFS(to, now);
    }
    int cnt0 = 0, cnt1 = 0; LL sum = 0; tcnt = 0;
    for (int to, i = head[now]; i; i = edge[i].nex) {
        to = edge[i].to;
        if (to == fa)
            continue;
        if (b[to] < b[now])
            cnt0++, sum += f[to][0];
        else if (b[to] > b[now])
            cnt1++, sum += f[to][1];
        else
            cnt0++, sum += f[to][0], tem[++tcnt] = to; // 存特殊节点
    }
    sort(tem + 1, tem + tcnt + 1, cmp); // 按照代价从小到大排序
    f[now][0] = sum + 1LL * max(cnt0, cnt1 + (fa != 0)) * a[now];
    f[now][1] = sum + 1LL * max(cnt0 + (fa != 0), cnt1) * a[now];
    for (int to, i = 1; i <= tcnt; i++) {
        to = tem[i], sum += f[to][1] - f[to][0], cnt0--, cnt1++;
        f[now][0] = min(f[now][0], sum + 1LL * max(cnt0, cnt1 + (fa != 0)) * a[now]);
        f[now][1] = min(f[now][1], sum + 1LL * max(cnt0 + (fa != 0), cnt1) * a[now]);
    }
}
//--------------------//
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    for (int i = 1; i <= n; i++)
        scanf("%d", &b[i]);
    for (int u, v, i = 1; i < n; i++)
        scanf("%d%d", &u, &v), add(u, v), add(v, u);
    DFS(1, 0);
    printf("%lld", f[1][0]);
    // f[1][0] 一定与 f[1][1] 相等，输出哪一个都行
    return 0;
}
```

---

## 作者：intel_core (赞：0)

考虑树上贪心。注意到每个点只往上传一条链，所以设 $f_{u,0/1}$ 表示考虑完 $u$ 的子树内，$u$ 往上传的这条链是单增/单减的最小代价。

如果当前有 $x_1$ 条单增，$x_2$ 条单减的链需要配对，显然 $u$ 需要额外产生 $|x_1-x_2|w_u$ 的贡献，在这里整条链都相等的情况必须钦定一个单调关系。

我们可以枚举单增链的条数 $k$，$k$ 从小到大计算贡献。$k=0$ 时就是 $\sum_{v\in son_u}f_{v,1}$，$k$ 每次 $+1$ 我们就取 $f_{v,0}-f_{v,1}$ 第 $k$ 小的加到贡献里即可。

复杂度瓶颈在排序，注意到每个点只会被排一次序，因此复杂度 $O(n\log n)$。

---

