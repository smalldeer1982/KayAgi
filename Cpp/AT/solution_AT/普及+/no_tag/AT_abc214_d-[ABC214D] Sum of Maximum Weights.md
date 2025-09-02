# [ABC214D] Sum of Maximum Weights

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc214/tasks/abc214_d

$ N $ 頂点の木があり、頂点は $ 1,\ 2,\ \dots,\ N $ と番号付けられています。  
 $ i\ \,\ (1\ \leq\ i\ \leq\ N\ -\ 1) $ 番目の辺は頂点 $ u_i $ と頂点 $ v_i $ を結び、重みは $ w_i $ です。

異なる頂点 $ u,\ v $ に対し、頂点 $ u $ から頂点 $ v $ までの最短パスに含まれる辺の重みの最大値を $ f(u,\ v) $ とおきます。

$ \displaystyle\ \sum_{i\ =\ 1}^{N\ -\ 1}\ \sum_{j\ =\ i\ +\ 1}^N\ f(i,\ j) $ を求めてください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 10^5 $
- $ 1\ \leq\ u_i,\ v_i\ \leq\ N $
- $ 1\ \leq\ w_i\ \leq\ 10^7 $
- 与えられるグラフは木である。
- 入力は全て整数である。

### Sample Explanation 1

$ f(1,\ 2)\ =\ 10,\ f(2,\ 3)\ =\ 20,\ f(1,\ 3)\ =\ 20 $ であるので、これらの和である $ 50 $ を出力します。

## 样例 #1

### 输入

```
3
1 2 10
2 3 20```

### 输出

```
50```

## 样例 #2

### 输入

```
5
1 2 1
2 3 2
4 2 5
3 5 14```

### 输出

```
76```

# 题解

## 作者：loser_seele (赞：6)

考虑题目中的 $ f(i,j)=x $ 的条件。

显然，如果 $ f(i,j)=x $，那么加入所有 $ \leq x $ 的边时 $ i,j $ 一定还没连通。于是考虑把边按照边权排序后从小到大加入图中，对于一条边 $ (a,b,c) $，如果 $ a,b $ 处于不同的集合，那么说明这条边对两边的集合都造成了贡献。设 $ a,b $ 所在的连通块大小为 $ sz_a,sz_b $，在答案上累加 $ sz_a \times sz_b \times c $ 即可，然后将 $ a,b $ 所在的集合合并。如果 $ a,b $ 在同一个集合则说明 $ c $ 一定不是集合里的点路径上的最大权路径，可以直接忽略。合并集合过程用并查集实现。

时间复杂度 $ \mathcal{O}(n\log{n}) $，来自边权排序的复杂度，可以通过。

代码：

```cpp
#import <bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn=1e5+10;
int fa[maxn],sz[maxn];
int find(int x)
{
    return fa[x]==x?x:fa[x]=find(fa[x]);
}
struct st
{
    int a,b,c;
};
bool cmp(st a,st b)
{
return a.c<b.c;
}
int main() 
{
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)
    fa[i]=i,sz[i]=1;
    vector<st>vec(n - 1);
    for(int i=0;i<n-1;i++)
    cin>>vec[i].a>>vec[i].b>>vec[i].c;
    sort(vec.begin(),vec.end(),cmp);
    ll ans=0;
    for(int i=0;i<n-1;i++)
    {
        int a=find(vec[i].a);
        int b=find(vec[i].b);        
        if(a!=b)
        {
            ans+=1LL*vec[i].c*sz[a]*sz[b];
            sz[b]+=sz[a];
            sz[a]=0;
            fa[a]=b;
        }
    }
    cout<<ans;
}
```


---

## 作者：EityDawn (赞：3)

# 思路
并查集很经典的应用。

对边权升序排序后，每加入一条边，边权记为 $w$，考虑图是树，所以必然会联通两个联通块。

而对于两个联通块内，我们使一个联通块联通的边，没有比当前边更大的边，因为边权已经升序排序了。

那么这两个联通块，一个联通块内的点到另一个联通块的点的路径上的最大边的边权就是 $w$。

有多少对 $f(i,j)$ 呢？设两个联通块的大小分别为 $size_{u}$ 和 $size_{v}$，共有 $size_{u}\times size_{v}$ 个点对。

拿并查集维护相当简单。
 
 求最大值会了，那[这题](https://www.luogu.com.cn/problem/CF915F)你也一定会了。
 
 时间复杂度 $O(n \log{n})$。
 
 # code：
 ```cpp
 #include<iostream>
#include<cstring>
#include<algorithm>
#define int long long
using namespace std;
const int N=1e6+10;
struct node{
	int x,y,w;
} k[N];
#define x(i) k[i].x
#define y(i) k[i].y
#define w(i) k[i].w
int w[N],fa[N],siz[N];
inline int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
int n;
bool cmp(node a,node b){return a.w<b.w;}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<n;i++) cin>>x(i)>>y(i)>>w(i);
	for(int i=1;i<=n;i++) fa[i]=i,siz[i]=1;
	sort(k+1,k+n,cmp1);
	int ans=0;
	for(int i=1;i<n;i++)
	{
		int fx=find(x(i)),fy=find(y(i));
		ans+=w(i)*siz[fx]*siz[fy];
		fa[fy]=fx;siz[fx]+=siz[fy];
	}
	cout<<ans;
	return 0;
}
 ```

---

## 作者：toolong114514 (赞：1)

# AT_abc214_d [ABC214D] Sum of Maximum Weights 题解
## 题面大意
[传送门。](https://www.luogu.com.cn/problem/AT_abc214_d)
## 解题思路
是教练给过的题 [CF915F](https://www.luogu.com.cn/problem/CF915F) 的弱化版。

考虑从小到大对边权排序。

注意到下列事实：
1. 按排好的顺序往图里加边的时候，每次**会且仅会**合并两个连通块。
2. 只有树上简单路径的两个端点分别属于这两个连通块，这条边才能产生一个贡献。

证明：
1. 假如这个事实不成立，那么图里面一定会产生环，与给定的图是一棵树矛盾。所以该事实成立。

2. 容易发现，此前形成的连通块内，所有边权都小于等于当前这条边的边权，如果有来自其它连通块的贡献，那么它一定不会由比当前大的边连成。但是边权小于等于当前边的的边已经连完，所以这种情况不存在。即事实成立。

用带权并查集维护连通块，以及它内部的点数，用[乘法原理](https://baike.baidu.com/item/%E4%B9%98%E6%B3%95%E5%8E%9F%E7%90%86/7538447?fr=ge_ala)计算出贡献，加起来即可。

时间复杂度约为 $O(n\log n)$，可以通过本题。
## 参考代码
```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
using namespace std;
#define int long long
const int N=1e5+10;
struct node{
	int fr,to,val;
}edge[N];
bool cmp(node pre,node nxt){
	return pre.val<nxt.val;
}
int fa[N],cnt[N];
int find(int x){
	if(fa[x]==x) return x;
	else return fa[x]=find(fa[x]);
}
void connect(int x,int y){
	cnt[find(y)]+=cnt[find(x)];
	fa[find(x)]=find(y);
}
int n,ans;
signed main(){
	ios::sync_with_stdio(false);
	cin>>n;
	for(int i=1;i<=n;i++){
		fa[i]=i;
		cnt[i]=1;
	}
	for(int i=1;i<n;i++){
		cin>>edge[i].fr>>edge[i].to>>edge[i].val;
	}
	sort(edge+1,edge+n,cmp);
	for(int i=1;i<n;i++){
		ans+=cnt[find(edge[i].fr)]*cnt[find(edge[i].to)]*edge[i].val;
		connect(edge[i].fr,edge[i].to);
	}
	cout<<ans;
	return 0;
}
```
[本代码可以通过 AT 的评测。](https://www.luogu.com.cn/record/163326707)

Written by [toolong114514](www.luogu.com/user/477821) on 2024/6/29.

---

## 作者：_EternalRegrets_ (赞：1)

题目是要求给定树上每两点之间最短路的最大权值边的和。

如果两个点不在同一个连通块内，添加这条边会增加 $q_u \times q_v \times w$。

其中 $q_i$ 是 $i$ 所在的连通块大小。

使用并查集维护连通块即可。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

struct node{
    int u;
    int v;
    int w;
};

node a[100005];
int q[100005];
int f[100005];

int findf(int x){
	if(f[x]==x){
		return f[x];
	}
	else{
		f[x]=findf(f[x]);
	}

	return f[x];
}

bool cmp(node x,node y){
    return x.w<y.w;
}

signed main(){
	int n; cin>>n;

	for(int i=1;i<=n;i++){
        f[i]=i;
        q[i]=1;
	}

	for(int i=1;i<n;i++){
        int u; cin>>u;
        int v; cin>>v;
        int w; cin>>w;

        a[i]=(node){u,v,w};
	}

	sort(a+1,a+n,cmp);

	int ans; ans=0;
	for(int i=1;i<=n-1;i++){
        int x; x=findf(a[i].u);
        int y; y=findf(a[i].v);

        ans+=q[x]*q[y]*a[i].w;

        if(x!=y){
            f[y]=x;
            q[x]+=q[y];
        }
	}

	cout<<ans;
	return 0;
}

```

---

## 作者：__Chx__ (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc214_d)

## 题目大意
给出一个有 $N-1$ 条边的树，求树上每两点之间最短路的最大权值边的和。

## 思路
我们可以让边权从小到大排序，依次添加边以满足权值严格不降。考虑用并查集维护树，并运用乘法原理算出每个边权的贡献，即为权值乘上链接两树的大小之积。

时间复杂度为 $O(N\ log\ N)$，时间复杂度瓶颈在于排序。

具体细节可参考代码

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e5+5;
struct node{
	int x,y,w;
}a[N];//结构体方便权值排序 
int n,cnt[N],fa[N],ans;
int f(int x){//并查集 
	if(fa[x]==x) return x;
	return fa[x]=f(fa[x]); 
}
bool cmp(node a1,node a2){return a1.w<a2.w;}//排序函数 
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++) fa[i]=i,cnt[i]=1;//初始化 
	for(int i=1;i<n;i++) cin>>a[i].x>>a[i].y>>a[i].w;//输入 
	sort(a+1,a+n,cmp); //排序 
	for(int i=1;i<=n;i++){
		int xf=f(a[i].x),yf=f(a[i].y);//找父亲 
		if(xf==yf) continue;
		ans+=cnt[xf]*cnt[yf]*a[i].w;//乘法原理计算贡献 
		fa[xf]=yf;
		cnt[yf]+=cnt[xf];
	}
	cout<<ans;
	return 0;//完结 
}
```



---

## 作者：Genius_Star (赞：0)

### 思路：

考虑将边权从小到大排序，依次加边，明显一条边的贡献为 $sz_u \times siz_v \times w$。

因为此时所有的边的权值都比当前边小，故两子树任意点对的路径上的边权最大值都只能是 $w$。

故直接使用并查集维护上述过程即可。

时间复杂度为 $O(N \log N)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
#define Add(x,y) (x+y>=mod)?(x+y-mod):(x+y)
#define lowbit(x) x&(-x)
#define full(l,r,x) for(auto it=l;it!=r;it++) (*it)=x
#define Full(a) memset(a,0,sizeof(a))
#define open(s1,s2) freopen(s1,"r",stdin),freopen(s2,"w",stdout);
using namespace std;
typedef double db;
typedef long long ll;
const ll N=1e5+10;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
struct Edge{
	ll u,v,w;
	bool operator<(const Edge&rhs)const{
		return w<rhs.w;
	}
}a[N];
ll n,ans;
ll fa[N],siz[N];
ll Find(ll x){
	if(x!=fa[x])
	  return fa[x]=Find(fa[x]);
	return fa[x];
}
int main(){
	n=read();
	for(int i=1;i<=n;i++)
	  fa[i]=i,siz[i]=1;
	for(int i=1;i<n;i++)
	  a[i]={read(),read(),read()};
	sort(a+1,a+n);
	for(int u,v,i=1;i<=n;i++){
		u=Find(a[i].u),v=Find(a[i].v);
		ans+=siz[u]*siz[v]*a[i].w;
		fa[u]=v;
		siz[v]+=siz[u];
	} 
	write(ans);
	return 0;
}
```

---

## 作者：XYQ_102 (赞：0)

## 思路
如何计算一个边的贡献：把其他权值大于该边的都删掉。将两点两边的连通数量相乘（就像一座桥，桥的一边的点一定要到桥另一边的各个点，所以是相乘）再乘以边权即得到该边队答案的贡献。我们可以从小到大加边，这样达到每次加入的边都是连通图中最大的，这个边就是“桥”。统计连通数量用并查集。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 200005;
int f[N];
long long cnt[N];
int Find(int x)
{
    return x==f[x]?x:f[x]=Find(f[x]);
}
struct edge
{
    int a,b;
    long long c;
    bool operator<(const edge j)
    {
        return c<j.c;
    }
}e[N];
int main()
{
    int n;
    cin>>n;
    for(int i=1;i<n;i++)
        cin>>e[i].a>>e[i].b>>e[i].c;
    sort(e+1,e+n);
    for(int i=1;i<=n;i++)
    {
        f[i]=i;
        cnt[i]=1;
    }
    long long ans=0;
    for(int i=1;i<n;i++)
    {
        int fa=Find(e[i].a);
        int fb=Find(e[i].b);
        ans+=cnt[fa]*cnt[fb]*e[i].c;
        f[fa]=fb;
        cnt[fb]+=cnt[fa];
    }
    printf("%lld\n",ans);
}
```

---

## 作者：CQ_Bob (赞：0)

## 分析

对于边 $u \to v$，其能够产生贡献的数量一定为 $x$ 到 $u$ 不经过 $u \to v$ 且权值最大值小于 $w$ 的数量与 $y$ 到 $v$ 不经过 $u \to v$ 且权值最大值小于 $w$ 的数量的乘积。

考虑并查集。将边按 $w$ 升序排序。对于 $u,v$ 两个点所在集合的任意点，我们就能保证它们到 $u$ 或者 $v$ 的任意一个边权都不大于 $w$。所以在两个集合中的点经过 $u\to v$ 所产生的贡献为 $siz_{S_u} \times siz_{S_v} \times w$。

复杂度 $O(n \log n)$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define re register
#define il inline
#define pii pair<int,int>
#define x first
#define y second
#define gc getchar()
#define rd read()
#define debug() puts("------------")

namespace yzqwq{
	il int read(){
		int x=0,f=1;char ch=gc;
		while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=gc;}
		while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=gc;
		return x*f;
	}
	il int qmi(int a,int b,int p){
		int ans=1;
		while(b){
			if(b&1) ans=ans*a%p;
			a=a*a%p,b>>=1;
		}
		return ans;
	}
	il auto max(auto a,auto b){return (a>b?a:b);}
	il auto min(auto a,auto b){return (a<b?a:b);}
	il int gcd(int a,int b){
		if(!b) return a;
		return gcd(b,a%b);
	}
	il int lcm(int a,int b){
		return a/gcd(a,b)*b;
	}
	il void exgcd(int a,int b,int &x,int &y){
		if(!b) return x=1,y=0,void(0);
		exgcd(b,a%b,x,y);
		int t=x;
		x=y,y=t-a/b*x;
		return ;
	}
	mt19937 rnd(time(0));
}
using namespace yzqwq;

const int N=1e5+10;
struct edge{
	int u,v,w;
}e[N];
int n,fa[N],siz[N];
int ans;

il bool cmp(edge a,edge b){
	return a.w<b.w;
}
il int find(int x){
	return (fa[x]==x?x:fa[x]=find(fa[x]));
}

il void solve(){
	n=rd;
	for(re int i=1;i<=n;++i) fa[i]=i,siz[i]=1;
	for(re int i=1;i<n;++i) e[i]={rd,rd,rd};
	sort(e+1,e+n,cmp);
	for(re int i=1;i<n;++i){
		int x=find(e[i].u),y=find(e[i].v);
		ans+=e[i].w*siz[x]*siz[y];
		fa[x]=y,siz[y]+=siz[x],siz[x]=0;
	}
	printf("%lld\n",ans);
	return ;
}

signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	int t=1;while(t--)
	solve();
	return 0;
}

```

---

## 作者：Symbolize (赞：0)

# $\tt{Solution}$
不要想得太复杂，我们先想想最终答案会是怎么样的形式，于是我们能得到一下式子。

$$ans=\sum\limits_{i=1}^{n-1} a_i \times w_i$$

这个式子中的 $a$ 数组是未知的，换句话来讲，如果我们求出了 $a$ 数组，那么我们就做完了，考虑如何求。

先从最大的边来看，不难会发现最大的边的贡献数就是去掉这条边后，其两个端点所在的子树的节点个数相乘。就此我们发现一条边的贡献只会受到比它边权小的边的影响，所以将边全部存下来，按边权从小到大排序，然后每次加边就行了，有可能在某一时刻所有节点并不联通，所以需要使用并查集维护。

```cpp
#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define x first
#define y second
#define rep1(i,l,r) for(int i=l;i<=r;i++)
#define rep2(i,l,r) for(int i=l;i>=r;i--)
const int N=1e5+10;
using namespace std;
int n,fa[N],len[N],ans;
struct node
{
	int a;
	int b;
	int c;
};
vector<node> v;
inline int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return f*x;
}
bool cmp(node a,node b){return a.c<b.c;}
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
signed main()
{
	n=read();
	rep1(i,1,n) fa[i]=i,len[i]=1;
	rep1(i,0,n-2)
	{
		int a=read();
		int b=read();
		int c=read();
		v.push_back({a,b,c});
	}
	sort(v.begin(),v.end(),cmp);
	rep1(i,0,n-2)
	{
		int a=find(v[i].a);
		int b=find(v[i].b);
		if(a==b) continue;
		ans+=v[i].c*len[a]*len[b];
		len[b]+=len[a];
		len[a]=0;
		fa[a]=b;
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：鱼跃于渊 (赞：0)

## 题意：  
给定一棵有 $n$ 个节点的树，有边权，求树上每两点间路径上最大权值边的和。  
## 做法：  
显然对于一条边来说，它能对答案产生贡献的情况只有两点间没有其它权值更大的边。这启发我们按边权值从小到大处理每条边。  
具体做法是使用并查集维护连通块及块内节点数。设则对于一条边 $(u,v,w)$，其产生的贡献为 $w \times size_{fa_u} \times size_{fa_v}$。正确性显而易见。  
## 代码：  
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e5+5;
struct edge{
	int u,v,w;
}e[N];
bool operator <(const edge &x,const edge &y){
	return x.w<y.w;
}
int n,ans,fa[N],siz[N];
int find(int x){
	return x==fa[x]?x:fa[x]=find(fa[x]);
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		fa[i]=i;
		siz[i]=1;
	}
	for(int i=1;i<n;i++){
		cin>>e[i].u>>e[i].v>>e[i].w;
		if(e[i].u<e[i].v) swap(e[i].u,e[i].v);
	}
	sort(e+1,e+n);
	for(int i=1,u,v;i<n;i++){
		u=find(e[i].u);
		v=find(e[i].v);
		ans+=siz[u]*siz[v]*e[i].w;
		siz[u]+=siz[v];
		fa[v]=u;
	}
	cout<<ans<<'\n';
	return 0;
}
```  
[AC 记录](https://atcoder.jp/contests/abc214/submissions/44888371)。

---

## 作者：徐晨轩✅ (赞：0)

## 题意简述

* 给定一棵树。

* 求
$$\sum_{i=1}^{n-1} \sum_{j=i+1}^n f(i,j)$$
其中 $f(i,j)$ 表示 $i$ 到 $j$ 最短路径上的最大边权。

## 解法

我们先假设树中没有边，只有节点，然后进行连边统计贡献。

具体地：

* 将权值从小到大排序。排序是为了更好的统计贡献。

* 遍历边，对于每条边 $(u, v, w)$：

   - 将其连通（使用并查集）。
   
   - 计算贡献：这条边的贡献就是它连起来之前 $\operatorname{size}(u) \times \operatorname{size}(v) \times w$ 的值。（因为排过序，所以连通 $u$ 和 $v$ 的最大值就是这条边）

PS：注意开 `long long`。

## Code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

class dsu {
    // the implemention of DSU
    // include find, merge, size
    // you can also use atcoder::dsu instead of this
};

struct node {
    int u, v, w;
    bool operator < (node x) const {
        return w < x.w;
    }
} e[100005];

int n, ans;

dsu d(100005);

signed main() {
    cin >> n;
    for (int i = 1, u, v, w; i < n; i++)
        cin >> u >> v >> w, e[i] = {u, v, w};
    sort(e + 1, e + n); // 对边权排序
    for (int i = 1; i < n; i++) {
        ans += e[i].w * d.size(e[i].u) * d.size(e[i].v); // 计算贡献
        d.merge(e[i].u, e[i].v); // 合并
    }
    cout << ans << endl;
    return 0;
}
```

---

## 作者：_zzzzzzy_ (赞：0)

## 思路
我们可以暴力枚举每一条边做出的贡献，但这样的复杂度是 $O(n^2)$。

那么我们考虑怎么递推的找出来答案，我们可以把边从小到大枚举保证了没有后效性，每加入一条边都会将两颗树连接起来，根据乘法原理可以得出贡献为两颗树的大小之积乘上边的权重，这个东西可以用并查集来维护。

最后我们的复杂度是 $O(n\log n)$。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=1000050;
int sz[maxn],f[maxn];
int F(int x){return x==f[x]?x:f[x]=F(f[x]);}
void U(int u,int v){
	u=F(u),v=F(v);
	if(u!=v){
		f[v]=u;
		sz[u]+=sz[v];
	}
}
struct node{
	int u,v,w;
}e[maxn];
signed main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)f[i]=i,sz[i]=1;
	for(int i=1;i<n;i++){
		cin>>e[i].u>>e[i].v>>e[i].w;
	}
	sort(e+1,e+n,[&](node a,node b){
		return a.w<b.w;
	});
	int ans=0;
	for(int i=1;i<n;i++){
		ans+=sz[F(e[i].u)]*sz[F(e[i].v)]*e[i].w;
		U(e[i].u,e[i].v);
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：迟暮天复明 (赞：0)

[没说更好的阅读体验](https://www.cnblogs.com/1358id/p/15143827.html)

首先不考虑数据范围的话，可以轻松写出一个 $O(n^2)$ 的树形DP。

但是这个题过不去。所以考虑换一个算法。我去统计每一个数出现了几次。

那么显然这个边前后大于此边边权的边向外连出去的点和这条边没有关系了，那对当前边出现次数有影响的点，只可能是被边权小于当前边所连接的点。那么我们立马想到把边排序，很快啊！然后并查集查询。没什么细节。

这个题做完以后可以考虑用类似的思路做一下 CF915F。

---

