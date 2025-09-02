# Yasya and the Mysterious Tree

## 题目描述

Yasya was walking in the forest and accidentally found a tree with $ n $ vertices. A tree is a connected undirected graph with no cycles.

Next to the tree, the girl found an ancient manuscript with $ m $ queries written on it. The queries can be of two types.

The first type of query is described by the integer $ y $ . The weight of each edge in the tree is replaced by the [bitwise exclusive OR](http://tiny.cc/xor_wiki_eng) of the weight of that edge and the integer $ y $ .

The second type is described by the vertex $ v $ and the integer $ x $ . Yasya chooses a vertex $ u $ ( $ 1 \le u \le n $ , $ u \neq v $ ) and mentally draws a bidirectional edge of weight $ x $ from $ v $ to $ u $ in the tree.

Then Yasya finds a simple cycle in the resulting graph and calculates the [bitwise exclusive OR](http://tiny.cc/xor_wiki_eng) of all the edges in it. She wants to choose a vertex $ u $ such that the calculated value is maximum. This calculated value will be the answer to the query. It can be shown that such a cycle exists and is unique under the given constraints (independent of the choice of $ u $ ). If an edge between $ v $ and $ u $ already existed, a simple cycle is the path $ v \to u \to v $ .

Note that the second type of query is performed mentally, meaning the tree does not change in any way after it.

Help Yasya answer all the queries.

## 样例 #1

### 输入

```
2
3 7
1 2 1
3 1 8
^ 5
? 2 9
^ 1
? 1 10
^ 6
? 3 1
? 2 9
5 6
1 2 777
3 2 2812
4 1 16
5 3 1000000000
^ 4
? 3 123
? 5 1000000000
^ 1000000000
? 1 908070
? 2 1```

### 输出

```
13 15 11 10 
1000000127 2812 999756331 999999756```

## 样例 #2

### 输入

```
3
8 4
8 6 3
6 3 4
2 5 4
7 6 2
7 1 10
4 1 4
5 1 2
^ 4
^ 7
? 7 8
? 4 10
5 6
3 1 4
2 3 9
4 3 6
5 2 10
? 5 7
^ 1
^ 8
? 4 10
? 1 9
? 3 6
4 2
2 1 4
4 3 5
2 3 4
^ 13
? 1 10```

### 输出

```
14 13 
13 8 11 11 
10```

# 题解

## 作者：yx666 (赞：3)

# CF1980G Yasya and the Mysterious Tree 题解

$$\text{Description}$$

一棵有边权的树，存在两种操作：

- `^ x` ：所有边权异或 $x$。

- `? u x`：新建一条从 $u$ 开始，边权为 $x$ 的边，你可以选择不为 $u$ 的任意点 $v$ 作为边的另一端，最大化在环上的边的边权异或和。

注意每个操作 2 没有实际意义上的加边。

对于 $100\%$ 的数据，$2\le n\le2\times10^5,0\le w,x\le 10^9,\sum Q\le 2\times10^5,1\le T\le 10^4$，输入保证是一棵树。

$$\text{Solution}$$

需要用到的知识：

1. 树上 bfs 或 dfs。
2. Trie 树。

首先，将原树转换为有根树，这里不妨让根节点为 $1$。

定义 $dis_i$ 表示第 $i$ 点到根节点的边权异或和，$f_{i,j}$ 表示 $i\to j$ 的边权异或和。

那么对于树上的节点 $u,v$，它们之间的距离就为 $dis_u\operatorname{xor} dis_v$，证明如下（$lca$ 是 $u,v$ 的最近公共祖先，抓住 $a\operatorname{xor}a=0,a\operatorname{xor}0=a$）：

$$\begin{aligned}
f_{u,v}&=f_{u,lca}\operatorname{xor}f_{lca,v}\\
&=(dis_u\operatorname{xor}dis_{lca})\operatorname{xor}
(dis_{lca}\operatorname{xor}dis_v)\\
&=dis_u\operatorname{xor}dis_v\end{aligned}$$

所以我们需要维护所有的 $dis_i$ 即可。

又记每个操作 2 的答案为 $ans$，则 $ans=dis_u\operatorname{xor}dis_v\operatorname{xor}x$。

$dis_u\operatorname{xor}x$ 已知，那我们只需要用 Trie 树的经典例题：[最长异或路径](https://www.luogu.com.cn/problem/P4551) 的思想，找到最大的 $ans$ 即可。

需要注意，$u\ne v$，所以要先删去点 $u$，再进行查询，最后还不要忘了加回点 $u$。

但是，操作 1 十分烦人，非常恶心。

很容易地想到，对于操作 1，可以实现类似线段树的懒标记，而不是每次都傻乎乎地更新。

回头看一下我们如何实现（懒标记 $k$，每个点深度 $h_i$）：

1. 转化为有根树。

2. 预处理 $dis_i$。

3. 对于每个操作 1，将 $k=k\operatorname{xor}x$。

4. 对于每个操作 2，将所有 $s(v)$ 插入一棵 Trie 树，贪心查询，第 $i$ 点的 $dis_i$，会异或上 $h_i$ 个 $k$。

我们~~惊奇地~~发现，第四步还可以进一步优化：

操作 1 只会影响奇数深度的那些点，故我们可以开两个 Trie，分别维护奇数层与偶数层的点的集合。剩下的操作与上述是相同的。

具体的，奇数层每次查询与 $dis_x\operatorname{xor}k\operatorname{xor}x$ 的异或最大值，偶数层每次查询与 $dis_x\operatorname{xor}x$ 的异或最大值，而不用每次去更改 $dis_i$。

时间复杂度 $O((n+q)\log x)$。

$$\text{Code}$$

``` cpp
#include<bits/stdc++.h>
using namespace std;

#define T int
static char buf[1000000],*p1=buf,*p2=buf,obuf[1000000],*p3=obuf;
#define gc() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
#define pc(x) (p3-obuf<1000000)?(*p3++=x):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=x)
#define io_flush fwrite(obuf,p3-obuf,1,stdout)

static inline T read(){T x=0;char ch=gc();bool syn=0;while(ch<'0'||'9'<ch) syn|=ch=='-',ch=gc();while('0'<=ch&&ch<='9') {x=(x<<3)+(x<<1)+(ch-'0');ch=gc();}return syn?-x:x;}
static inline void writesp(T x) {static int sta[28];if(x<0){pc('-');x=-x;}int top = 0;do sta[top++] = x % 10, x /= 10;while (x);while (top) pc(sta[--top] + '0');pc(' ');}
#undef T

static inline int max(int a,int b){return a>b?a:b;}

#define N 200005
#define M 400005

int tot=0,head[N];
struct{
	int to,nxt,val;
}edge[M];

void addEdge(int from,int to,int val){
	edge[++tot].to=to;
	edge[tot].nxt=head[from];
	edge[tot].val=val;
	head[from]=tot;
	return;
}

// 建树 

int dis[N];
bitset<N>h,vis;
static inline void bfs(int rx){		// 预处理 h，dis 
	queue<int>q;
	q.push(rx);
	
	h.reset(),vis.reset();
	h[rx]=1;
	while(q.size()){
		int x=q.front();q.pop();
		if(vis[x]) continue;
		vis[x]=1;
		
		for(int i=head[x];i;i=edge[i].nxt){
			int y=edge[i].to;
			if(!vis[y]){
				h[y]=!h[x];
				dis[y]=dis[x]^edge[i].val;
				q.push(y);
			}
		}
	}return ;
}

class Trie{
private:
	int cnt=0,trie[N<<5][2],tot[N<<5]={0};
public:
	void clear(){			// 清空 
		for(int i=0;i<=cnt;++i)
			trie[i][0]=trie[i][1]=tot[i]=0;
		cnt=0;
	};
	
	void insert(int a,int d){		// 向 a 处插入 d 
		int p=0;
		for(int i=31;i>=0;--i){
			bool x=(a>>i)&1;
			if(!trie[p][x]) trie[p][x]=++cnt;
			p=trie[p][x];
			tot[p]+=d;
		}
		return ;
	}

	int query(int a){			// 查询 a 
		int p=0,ans=0;
		for(int i=31;i>=0;--i){
			bool x=(a>>i)&1;
			if(trie[p][!x]&&tot[trie[p][!x]]>0){		// 注意 tot 里面是 trie[p][!x] 而不是 p 
				p=trie[p][!x];
				ans|=1<<i;
			}else
				p=trie[p][x];
		}
		return ans;
	}
}trie[2];

static inline void solve(){
	int n=read(),q=read();
	for(int i=1;i<n;++i){
		int u=read(),v=read(),w=read();
		addEdge(u,v,w);addEdge(v,u,w);
	}
	bfs(1);
	
	for(int i=1;i<=n;++i)
		trie[h[i]].insert(dis[i],1);
	
	int k=0;
	while(q--){
		char ch=gc();
		while(ch!='^'&&ch!='?') ch=gc();
		if(ch=='^'){
			k^=read();
		}else{
			int u=read(),x=read();
			trie[h[u]].insert(dis[u],-1);
			
			int ans=trie[h[u]].query(dis[u]^x);
			trie[h[u]].insert(dis[u],1);
			
			ans=max(ans,trie[!h[u]].query(dis[u]^x^k));
			writesp(ans);
		}
	}pc('\n');
	
	// 清空 
	fill(head,head+1+n,0);
	tot=0;
	trie[0].clear();trie[1].clear();
	return ;
}

signed main(){
	int t=read();
	while(t--) solve();
	io_flush;
	return 0;
}
```

---

## 作者：yshpdyt (赞：3)

## 题意
一棵有边权的树，存在两种操作：

1. `^ x` ：所有边权异或 `x`。
2. `? v x` ：新建一条一端为 `v` 边权为 `x` 的边，你可以选择不为 `v` 的任意点 `u` 作为边的另一端 ，最大化在环上的边的边权异或和。

操作 $1$ 保留，操作 $2$ 保留。

## Sol
~~疑惑题！~~

先不管修改操作。

把一个环分成三部分，$lca\rightarrow x$，$lca\rightarrow y$，$x\rightarrow y$。

为了方便表示，记 $f_{x,y}$ 表示以 $x,y$ 作为两端的链上边权异或和。

如果多组询问每次给定 $x,y,val$，即在 $x,y$ 间新建边权为 $val$ 的边，统计答案是简单的，考虑类似树上差分的操作，具体来说有：
$$
  \begin{aligned}
    res &= f_{x,y}\oplus val \\
      &= f_{x,lca}\oplus f_{lca,y}\oplus val* \\
      &= f_{x,lca}\oplus f_{lca,root}\oplus f_{root,lca}\oplus f_{lca,y}\oplus val\\
      &= f_{x,root}\oplus f_{root,y}\oplus val\\
      &= f_{x,root}\oplus f_{y,root}\oplus val
  \end{aligned}
$$
所以维护每个点到根节点路径上边权异或和即可求解。

现在 $x$ 变成未知的，仍然考虑上面的式子，只有 $f_{x,root}$ 发生改变，不妨把所有 $f_{x,root}$ 拉出来弄成序列，右边两个定值设为 $d$，问题转化成对于给定的 $d$，选择序列中的一个数，让异或的结果最大，这是很典的套路，用 01trie 可以轻松维护。

具体来说，把所有 $f_{x,root}$ 放入 01trie，对于查询 $y,val$，由于 $x\neq y$，先把 $f_{y,root}$ 踢出字典树，然后直接查询即可。

现在考虑带修改如何做，如果只修改一条边的话会变得很复杂（也许是我太菜了），但是题目要的是全局异或，这就很容易了，可以类似懒标记给全局打 tag 并且标记永久化，设异或值为 $k$。

我们只关心一个点到根节点的异或和，设根节点深度为 $1$，一个点的深度为 $dep_x$，修改后需要异或 $dep_x-1$ 次 $k$，由于异或的性质，相当于偶数深度节点的答案异或，而奇数深度节点不异或，每次修改操作的都是同一批点，所以我们可以记录 $k=\bigoplus\limits_{i=1}^{m}k_i$，表示至今所有修改操作的异或和。

由于深度为奇数的点不需要异或，而偶数的点需要，考虑建两颗 01trie，分别在奇数树和偶数树上以不同的异或值查找。

具体来说，经过修改后当前节点到根节点的路径异或和为 $w=f_{x,root}\oplus\left(k\times[dep_x\equiv0\pmod2]\right)$，在奇数树上查异或 $w\oplus val$ 的最大值，在偶数树上查异或 $w\oplus val\oplus k$ 的最大值。

~~本题充分使用了异或的交换律~~。

时间复杂度 $O(n \log n)$。

##  Code
```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 200005
#define endl "\n" 
#define fi first
#define se second
using namespace std;
const ll mod=1e9+7;
const ll inf=1e18;
const double eps=1e-6;

vector<pair<ll,ll> >v[N];
ll x2[35];
ll n,m;
struct trie{
    ll cnt,tr[N*34][2],rt,num[N*34];
    void ins(ll &p,ll x,ll d){
        if(!p)p=++cnt;
        num[p]++;
        if(d<0)return ;
        if((x>>d)&1)ins(tr[p][1],x,d-1);
        else ins(tr[p][0],x,d-1);
    }
    ll qr(ll p,ll x,ll d){
        if(d<0)return 0;
        ll t=(x>>d)&1;
        if(tr[p][t^1])return x2[d]+qr(tr[p][t^1],x,d-1);
        return qr(tr[p][t],x,d-1);
    }
    void del(ll &p,ll x,ll d){
        num[p]--;
        if(d<0){
            if(num[p]==0)p=0;
            return ;
        }
        if((x>>d)&1)del(tr[p][1],x,d-1);
        else del(tr[p][0],x,d-1);
        if(num[p]==0)p=tr[p][1]=tr[p][0]=0;
    }
}T[2];
ll dep[N],f[N];
void dfs(ll x,ll fa){
    dep[x]=dep[fa]+1;
    T[dep[x]&1].ins(T[dep[x]&1].rt,f[x],33);
    for(auto [y,val]:v[x]){
        if(y==fa)continue;
        f[y]=f[x]^val;
        dfs(y,x);
    }
}
void sol(){
    cin>>n>>m;
    for(int i=1;i<n;i++){
        ll x,y,z;
        cin>>x>>y>>z;
        v[x].push_back({y,z});
        v[y].push_back({x,z});
    }
    dfs(1,0);
    ll k=0;
    for(int i=1;i<=m;i++){
        char c;
        ll x,val;
        cin>>c;
        if(c=='^'){
            cin>>val;
            k^=val;
        }else{
            cin>>x>>val; 
            T[dep[x]&1].del(T[dep[x]&1].rt,f[x],33);
            ll w=((dep[x]&1)?f[x]:(f[x]^k));
            ll p=max(T[0].qr(T[0].rt,w^val^k,33),T[1].qr(T[1].rt,w^val,33));
            cout<<p<<" ";
            T[dep[x]&1].ins(T[dep[x]&1].rt,f[x],33);
        }
    }
    for(int i=1;i<=n;i++){
        v[i].clear();
        T[dep[i]&1].del(T[dep[i]&1].rt,f[i],33);
    }
    T[1].cnt=T[0].cnt=0;
    cout<<endl;
}
int main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    x2[0]=1;
    for(int i=1;i<=33;i++)x2[i]=x2[i-1]*2;
    ll ttt;
    cin>>ttt;
    while(ttt--)sol();
    return 0;
}

```

---

## 作者：lfxxx (赞：0)

一眼题。

静态异或最大环考虑以 $1$ 为根，对于每个点 $u$ 处理出 $dep_u$ 表示根到其路径上所有边异或和，那么给定点 $v$ 和参数 $x$ 后最大异或环异或和就等于询问 $\max_{u \not v}(dep_v \oplus dep_u \oplus x)$。

考虑将所有 $dep_u$ 丢进字典树中，然后带着异或上 $x$ 的条件在字典树上逐位贪心即可，注意判断 $x$ 这位是 $1$ 导致的 $0,1$ 翻转。

考虑全局修改边权，不难发现只有到根距离为奇数的点的 $dep$ 会异或上 $y$，于是对到根距离的奇偶性分类，在两棵字典树中保存，并记录全局异或懒标记，在询问会被懒标记影响到字典树时将影响异或到 $x$ 上即可。

时间复杂度 $O((n+q) \log V)$。

[代码](https://codeforces.com/contest/1980/submission/282491675)

---

