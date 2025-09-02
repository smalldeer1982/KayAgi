# Symmetree

## 题目描述

Kid was gifted a tree of $ n $ vertices with the root in the vertex $ 1 $ . Since he really like symmetrical objects, Kid wants to find out if this tree is symmetrical.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1800G/d38e017cff0afa58cfae306135ac70824868e32a.png) For example, the trees in the picture above are symmetrical.  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1800G/c7cdf18345f431d81f3f4995e8b80d43eac66d45.png) And the trees in this picture are not symmetrical.Formally, a tree is symmetrical if there exists an order of children such that:

- The subtree of the leftmost child of the root is a mirror image of the subtree of the rightmost child;
- the subtree of the second-left child of the root is a mirror image of the subtree of the second-right child of the root;
- ...
- if the number of children of the root is odd, then the subtree of the middle child should be symmetrical.

## 样例 #1

### 输入

```
6
6
1 5
1 6
1 2
2 3
2 4
7
1 5
1 3
3 6
1 4
4 7
4 2
9
1 2
2 4
2 3
3 5
1 7
7 6
7 8
8 9
10
2 9
9 10
2 3
6 7
4 3
1 2
3 8
2 5
6 5
10
3 2
8 10
9 7
4 2
8 2
2 1
4 5
6 5
5 7
1```

### 输出

```
YES
NO
YES
NO
NO
YES```

# 题解

## 作者：jianhe (赞：4)

树哈希的简单应用。

如果你不知道什么是树哈希，请左转 [P5043 【模板】树同构](https://www.luogu.com.cn/problem/P5043)。本文中代码采取的是[异或哈希](https://oi-wiki.org/graph/tree-hash/#%E6%96%B9%E6%B3%95)。

考虑对于一个结点 $x$。

容易发现，当子结点的异或和为 $0$ 时，说明这棵子树对称。

当子结点的数量为偶数时，子结点的异或和必须为 $0$。

当子结点的数量为奇数时，去掉一个子结点（将其放在中间）后，子结点的异或和必须为 $0$。

用一个数组记录一下每个子树是否能对称，递归调用即可。

### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define pb push_back
const ull mask=rand();
const ll N=2e5+10;
ll T,n,x,y,sz[N];
ull h[N];
vector<ll> e[N];
bool dp[N];
ull Tran(ull x){x^=mask;x^=(x<<13);x^=(x>>7);x^=(x<<17);x^=mask;return x;}
void add(ll x,ll y){e[x].pb(y),e[y].pb(x);}
void dfs(ll x,ll fa){
	ll ct=0;ull s=0;
	h[x]=0;
	for(auto y:e[x]) if(y!=fa) dfs(y,x),ct++,s^=h[y],h[x]+=Tran(h[y]);//树哈希
	if(!(ct&1)) dp[x]=!s;//儿子数量为偶数时，异或和必须为0
	else for(auto y:e[x]) if(y!=fa&&h[y]==s) dp[x]=dp[y]; //当儿子数量为奇数时，去掉一个儿子（将其放在中间）后，异或和必须为0
}
void clr(){for(int i=1;i<=n;i++) e[i].clear(),dp[i]=0;}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n;
		for(int i=1;i<n;i++) cin>>x>>y,add(x,y);
		dfs(1,0);cout<<(dp[1]?"YES\n":"NO\n");clr();
	}
	return 0;
}

```

---

## 作者：thostever (赞：4)

类比哈希，考虑将每种树赋予一个权值，相同的树权值相同，不同的树权值不同。

考虑权值如何计算。我的计算方法是：

$$
a_u=((\sum_{v\in son_u}a_v)+(\prod_{v\in son_u}a_v))\mod 998244353
$$

初始给所有 $a_u$ 赋一个相同的随机值即可。

对于每个节点 $u$ 的子树，我们判断它是否能够对称。对于它的**一种**儿子的子树（权值），如果其出现了奇数次，那么检查这种子树是否可以对称。如果可以，则选一个作为中心点，其它对称摆放，否则 $u$ 无法对称。如果作为中心点的子树种类超过 $1$ 个，那么 $u$ 也无法对称。

最后检查 $1$ 号节点是否可以对称即可。

具体细节可以看代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll mod=998244353;
int n,m;
int head[200010],to[400010],nxt[400010],tot=0;
void add(int x,int y)
{
	to[++tot]=y;
	nxt[tot]=head[x];
	head[x]=tot;
}
ll a[200010];
int b[200010];//表示一个点的子树是否可以对称。b[u]<=1 便是可以，否则不可以。 
struct node{ll a;int b;};
bool cmp(node x,node y){return x.a<y.a;}
ll ra;
void dfs(int u,int f)
{
	a[u]=ra;
	vector<node> t;
	for(int i=head[u];i;i=nxt[i])
	{
		int v=to[i];
		if(v==f) continue;
		dfs(v,u);
		t.push_back(node{a[v],b[v]});
	}
	sort(t.begin(),t.end(),cmp); t.push_back(node{-666ll,-999});
	int lst=0;
	for(int i=0;i<int(t.size())-1;i++)
	{
		if(t[i].a!=t[i+1].a)
		{
			if((i-lst+1)&1)
			{
				if(t[i].b<=1) b[u]++;
				else b[u]=2;
			}
			lst=i+1;
		}
	}
	ll cnt=1;
	for(int i=0;i<int(t.size())-1;i++) a[u]=(a[u]+t[i].a)%mod,cnt=cnt*t[i].a%mod;
	a[u]=(a[u]+cnt)%mod;
}
void solve()
{
	ra=rand();
	scanf("%d",&n);
	for(int i=1;i<=n;i++) head[i]=0; tot=0;
	for(int i=1;i<=n;i++) b[i]=0;
	for(int i=2;i<=n;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y); add(y,x);
	}
	dfs(1,1);
	if(b[1]<=1) printf("YES\n");
	else printf("NO\n");
	return;
}
int main()
{
	srand(time(NULL));
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
/*

*/
```


---

## 作者：shinkuu (赞：1)

duel 题。

考虑如何判定一棵树是否对称。记 $son$ 为儿子数量，容易发现当且仅当：

- $son$ 为偶数时，每一棵子树都能找到另一棵与之匹配，并使得匹配的两棵子树同构。

- $son$ 为奇数时，只有一棵子树找不到匹配的，递归下去判断它是否对称。

于是需要一个树哈希。

然后考虑怎么样判断找到匹配，想到两棵相同的相互消掉，既然我们已经用了 hash，所以可以直接将所有儿子的 hash 值异或起来，判断是否为 $0$，或是否为某个子树的 hash 值，并往这棵子树递归解决即可。

实际代码可以不用递归第二次而是用一次小 dp 解决。时间复杂度 $O(n)$。代码使用非常好写的 xor shift。

code；

```cpp
// Problem: Symmetree
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1800G
// Memory Limit: 250 MB
// Time Limit: 2000 ms
// Written by yinhee.

#include<bits/stdc++.h>
using namespace std;
namespace my_std{
#define mems(x,y) memset(x,y,sizeof x)
#define Mp make_pair
#define eb emplace_back
#define gc getchar
#define pc putchar
#define fi first
#define se second
#define il inline
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define drep(i,a,b) for(int i=(a);i>=(b);i--)
#define go(i,u) for(int i=head[u];i;i=e[i].nxt)
	typedef long long ll;
	typedef unsigned long long ull;
	typedef pair<int,int> pii;
	il int read(){
		int x=0,f=1;char c=gc();
		while(c<'0'||c>'9'){if(c=='-')f=-1;c=gc();}
		while(c>='0'&&c<='9')x=x*10+c-48,c=gc();
		return x*f;
	}
	il void write(int x){
		char buf[23];int len=0;
		if(x<0)pc('-'),x=-x;
		do buf[++len]=x%10,x/=10;while(x);
		while(len)pc(buf[len--]+'0');
	}
}
using namespace my_std;
const int N=2e5+7,M=-1,inf=0x3f3f3f3f,mod=0;
int n,m,dp[N];
ull h[N];
int tot,head[N];
struct node{
	int to,nxt;
}e[N<<1];
il void add(int u,int v){
	e[++tot]={v,head[u]},head[u]=tot;
}
mt19937 rnd(time(0));
ull base=(ull)rnd()*rnd()*rnd()*rnd();
il ull shift(ull x){
	x^=base<<1;
	x^=x<<47;
	x^=x>>31;
	x^=x<<23;
	x^=base<<1;
	return x;
}
void dfs(int u,int f){
	ull sum=0;
	int son=0;
	h[u]=(base<<17),dp[u]=0;
	go(i,u){
		int v=e[i].to;
		if(v==f){
			continue;
		}
		dfs(v,u),son++;
		sum^=h[v];
		h[u]+=shift(h[v]);
	}
	if(son&1){
		go(i,u){
			int v=e[i].to;
			if(v==f){
				continue;
			}
			if(h[v]==sum){
				dp[u]=dp[v];
			}
		}
	}else if(!sum){
		dp[u]=1;
	}
}
void Yorushika(){
	scanf("%d",&n);
	tot=0;
	rep(i,1,n){
		head[i]=0;
	}
	rep(i,1,n-1){
		int u,v;scanf("%d%d",&u,&v);
		add(u,v),add(v,u);
	}
	dfs(1,0);
	puts(dp[1]?"Yes":"No");
}
signed main(){
	int t=1;
		scanf("%d",&t);
	while(t--)
		Yorushika();
}
```

---

## 作者：lfxxx (赞：0)

考虑先对树上每个子树处理出树哈希值。

然后对于一个点不断的取出两个哈希值相同也就是同构的子树删掉，表示将这两个子树作为镜像，直到不可再消。

然后如果没剩下子树就是合法，剩下一个子树就去递归判定这个子树是否合法，否则一定不合法。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
//#define lowbit(x) (x&(-x))
//#define bp push_back
//#define sz size
//#define cl clear
const int maxn = 2e5+114;
const int mod[2] = {1145141,998244353};
mt19937 rd(time(0));
vector<int> E[maxn];
int n;
int C1[2],C2[2];
pair<int,int> Hash(pair<int,int> c){
	return make_pair((c.first*C1[0]%mod[0]+(c.first^C1[0]%mod[0]))%mod[0],(c.second*C1[1]%mod[1]+(c.second^C1[1]%mod[1]))%mod[1]);
}
vector< pair<int,int> > son[maxn];
pair<int,int> dp[maxn];
void dfs(int u,int fa){
	dp[u]=make_pair(114,514);
	for(int v:E[u]){
		if(v!=fa){
			dfs(v,u);
			pair<int,int> s=Hash(dp[v]);
			dp[u]=make_pair((dp[u].first+s.first)%mod[0],(dp[u].second+s.second)%mod[1]);
			son[u].push_back(dp[v]);
		}
	} 
} 
map< pair<int,int> ,int> mp;
bool solve(int u,int fa){
	if(son[u].size()==0) return true;
	mp.clear();
	for(pair<int,int> now:son[u]){
		mp[now]^=1;
	}
	vector< pair<int,int> > vec;
	for(pair<int,int> now:son[u]){
		if(mp[now]==1){
			vec.push_back(now);
			mp[now]^=1;
		}
	}
	if(vec.size()==1){
		for(int v:E[u]){
			if(v!=fa&&dp[v]==vec[0]) return solve(v,u);
		}
	}else if(vec.size()>=2) return false;
	return true;
}
void work(){
	cin>>n;
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		E[u].push_back(v);
		E[v].push_back(u);
	}
	dfs(1,0);
	cout<<(solve(1,0)==true?"YES\n":"NO\n");
	for(int i=1;i<=n;i++) dp[i]=make_pair(0,0),E[i].clear(),son[i].clear();
	return ;
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	C1[0]=rd()%mod[0],C1[1]=rd()%mod[1],C2[0]=rd()%mod[0],C2[1]=rd()%mod[1];
	int t;
	cin>>t;
	while(t--) work();
	return 0;
}
/*
1
6
1 5
1 6
1 2
2 3
2 4
*/
```

---

## 作者：Hoks (赞：0)

## 前言
duel 到的题，被杀了，鉴定为不好好看题面导致的。

摘自 [杂题选做](https://www.luogu.com.cn/training/499842)。
## 思路分析
注意这题题面里的重点：你可以调整**一个点**的儿子顺序。

注意只能是一个点，不然就会和我一样疯狂 WA 3。

接着考虑怎么来处理这个题。

所谓的镜像其实就是指两个子树是同构的。

那么就是判断树的同构，考虑一个类似于树 hash 的东西，考虑赋个臭点的数字然后 hash 防止被卡。

接着就是数数的问题了：
1. 对于有奇数个儿子的点，那么就有一个子树是可以不同的，其他都要相同。
2. 对于偶数个儿子的点，则要全部相同。

这样判断一下他是否要使用交换儿子的那个效果一路向上推即可。
## 代码

```cpp
#include <bits/stdc++.h>
#define ls (lc[p])
#define rs (rc[p])
#define mid ((l+r)>>1)
#define int long long
using namespace std;
const int N=2e5+10,V=1e7,mod=1004535809,INF=0x3f3f3f3f3f3f3f3f;
int n,m,k,t,w,d,a[N],b[N];vector<int>e[N];
namespace Fast_IO
{
    static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
    #define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
    inline int read()
    {
        int x(0),t(1);char fc(getchar());
        while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
        while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
        return x*t;
    }
    inline void flush(){fwrite(out,1,length,stdout);length=0;}
    inline void put(char c){if(length==9999999) flush();out[length++]=c;}
    inline void put(string s){for(char c:s) put(c);}
    inline void print(int x)
    {
        if(x<0) put('-'),x=-x;
        if(x>9) print(x/10);
        put(x%10+'0');
    }
    inline bool chk(char c) { return !(c>='a'&&c<='e'||c>='A'&&c<='Z'||c>='0'&&c<='9'); }
    inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
    inline void rd(char s[],int&n)
    {
        s[++n]=getchar();
        while(chk(s[n])) s[n]=getchar();
        while(ck(s[n])) s[++n]=getchar();
        n--;
    }
}
using namespace Fast_IO;
inline void add(int u,int v){e[u].emplace_back(v),e[v].emplace_back(u);}
inline void dfs(int u,int ff)
{
    a[u]=1145141919810%mod;int res=1;vector<pair<int,int>>c;
    for(auto v:e[u]) if(v!=ff)
        dfs(v,u),c.push_back({a[v],b[v]}),res=res*a[v]%mod,a[u]=(a[u]+a[v])%mod;
    sort(c.begin(),c.end());c.push_back({-114514,-1919810});
    for(int i=0,lst=0;i<c.size()-1;i++)
        if(c[i].first!=c[i+1].first)
        {
            if((i-lst+1)&1)
                if(c[i].second<=1) b[u]++;
                else b[u]=2;
            lst=i+1;
        }a[u]=(a[u]+res)%mod;
}
inline void solve()
{
    w=rand();n=read();for(int i=1;i<=n;i++) e[i].clear(),b[i]=a[i]=0;
    for(int i=1,u,v;i<n;i++) u=read(),v=read(),add(u,v);
    dfs(1,0);put(b[1]<=1?"YES\n":"NO\n");
}
signed main()
{
    srand(time(0));
    int T=read();while(T--) solve();
    genshin:;flush();return 0;
}
```

---

