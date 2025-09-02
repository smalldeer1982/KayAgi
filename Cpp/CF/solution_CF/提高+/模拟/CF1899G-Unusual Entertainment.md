# Unusual Entertainment

## 题目描述

A tree is a connected graph without cycles.

A permutation is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in any order. For example, $ [5, 1, 3, 2, 4] $ is a permutation, but $ [2, 1, 1] $ is not a permutation (as $ 1 $ appears twice in the array) and $ [1, 3, 2, 5] $ is also not a permutation (as $ n = 4 $ , but $ 5 $ is present in the array).

After a failed shoot in the BrMeast video, Alex fell into depression. Even his birthday did not make him happy. However, after receiving a gift from Timofey, Alex's mood suddenly improved. Now he spent days playing with the gifted constructor. Recently, he came up with an unusual entertainment.

Alex builds a tree from his constructor, consisting of $ n $ vertices numbered from $ 1 $ to $ n $ , with the root at vertex $ 1 $ . Then he writes down each integer from $ 1 $ to $ n $ in some order, obtaining a permutation $ p $ . After that, Alex comes up with $ q $ triples of integers $ l, r, x $ . For each triple, he tries to determine if there is at least one descendant of vertex $ x $ among the vertices $ p_l, p_{l+1}, \ldots, p_r $ .

A vertex $ u $ is a descendant of vertex $ v $ if and only if $ \mathrm{dist}(1, v) + \mathrm{dist}(v, u) = \mathrm{dist}(1, u) $ , where $ \mathrm{dist}(a, b) $ is the distance between vertices $ a $ and $ b $ . In other words, vertex $ v $ must be on the path from the root to vertex $ u $ .

Alex told Zakhar about this entertainment. Now Alex tells his friend $ q $ triples as described above, hoping that Zakhar can check for the presence of a descendant. Zakhar is very sleepy, so he turned to you for help. Help Zakhar answer all of Alex's questions and finally go to sleep.

## 样例 #1

### 输入

```
3
3 5
1 2
2 3
1 2 3
1 2 2
1 2 3
2 3 1
1 2 3
2 3 3
10 10
2 6
2 7
2 4
1 7
2 8
10 6
8 5
9 4
3 4
10 2 5 9 1 7 6 4 3 8
8 9 8
7 8 1
7 10 6
4 8 9
5 5 10
7 10 1
9 9 2
9 10 6
6 6 2
10 10 6
1 1
1
1 1 1```

### 输出

```
YES
NO
YES
NO
YES

NO
YES
YES
YES
NO
YES
YES
NO
NO
NO

YES```

# 题解

## 作者：FFTotoro (赞：11)

本题可以不需要用到那么多高深的数据结构，只需使用**启发式合并**。

先把树上所有点的编号变为该编号在排列中出现时的下标，这样每个询问就变成了查找是否存在编号在 $[l,r]$ 的后代了。

直接使用 `set` 维护一个点的所有后代，至于怎么维护可以用启发式合并。每次找到重儿子直接 `swap` 到父亲上，剩下的用 `merge` 函数暴力合并。然后对于在该结点上的所有询问依次在 `set` 中二分查找判断即可。

时间复杂度是经典的启发式合并复杂度 $O(n\log^2n)$。

放代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
typedef tuple<int,int,int> tpi;
int main(){
  ios::sync_with_stdio(false);
  int t; cin>>t;
  while(t--){
    int n,q; cin>>n>>q;
    vector<pii> e(n-1);
    for(auto &[u,v]:e)cin>>u>>v; // 提前存边
    vector<int> p(n+1);
    for(int i=0;i<n;i++){
      int x; cin>>x; p[x]=i;
    } // 建立映射
    vector<vector<int> > g(n);
    for(auto &[u,v]:e){
      g[p[u]].emplace_back(p[v]);
      g[p[v]].emplace_back(p[u]);
    } // 建树
    vector<vector<tpi> > w(n);
    vector<bool> b(q);
    for(int i=0;i<q;i++){
      int l,r,x; cin>>l>>r>>x;
      w[p[x]].emplace_back(l-1,r-1,i);
    } // 离线所有询问
    vector<set<int> > s(n);
    function<void(int,int)> dfs=[&](int u,int f){
      int h=u; // h 是重儿子
      for(int i:g[u])
        if(i!=f)if(dfs(i,u);s[i].size()>s[h].size())h=i;
      if(h!=u)s[u].swap(s[h]); // 把重儿子的翻上来
      for(int i:g[u])
        if(i!=f&&i!=h)s[u].merge(s[i]); // 暴力合并
      s[u].emplace(u); // 加进它本身
      for(auto [l,r,i]:w[u])
        if(auto p=s[u].lower_bound(l);p!=s[u].end()&&*p<=r)b[i]=true;
        // 使用 lower_bound 进行二分查找
    };
    dfs(p[1],p[1]); // 注意此时的根是 p[1]！
    for(bool i:b)cout<<(i?"Yes\n":"No\n");
  }
  return 0;
}
```

---

## 作者：luqyou (赞：7)

不需要莫队，不需要启发式合并，不需要树剖，时间复杂度可以做到 $O(n \log n)$，还好写。

首先转化一下题意，变为 $[l,r]$ 内是否有某一个点在 $x$ 的子树内。

而我们知道，同一子树内的 $dfn$ 连续，以 $x$ 为根的子树 $dfn$ 范围为 $[dfn_x,dfn_x+sz_x-1]$，其中 $sz_x$ 为 $x$ 的子树大小。

那么问题又变为：查询某一区间内是否有某个范围内的数。

我们将询问拆成 $ans_r - ans_{l-1}$ 离线，按询问位置排序，只需要在加点的同时维护一个树状数组即可。

# code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+10,V=1e5;
int n,m,a[maxn],dfn[maxn],sz[maxn],cnt,c[maxn],res[maxn*2],qcnt;
vector<int> g[maxn];
struct queries{
	int p,l,r,id;
	bool operator <(queries _){
		return p<_.p;
	}
}q[maxn*2];
void dfs(int u,int fa){
	dfn[u]=++cnt,sz[u]=1;
	for(int v:g[u]) if(v!=fa) dfs(v,u),sz[u]+=sz[v];
}
int lb(int x){
	return x&(-x);
}
void update(int x,int k){
	for(;x<=V;x+=lb(x)) c[x]++;
}
int query(int x){
	int res=0;
	for(;x;x-=lb(x)) res+=c[x];
	return res;
}
void solve(){
	cin>>n>>m,cnt=qcnt=0;
	for(int i=1,u,v;i<n;i++) cin>>u>>v,g[u].push_back(v),g[v].push_back(u);
	for(int i=1;i<=n;i++) cin>>a[i],c[i]=0;
	dfs(1,1);
	for(int i=1,l,r,x;i<=m;i++) cin>>l>>r>>x,q[++qcnt]={l-1,dfn[x],dfn[x]+sz[x]-1,qcnt},q[++qcnt]={r,dfn[x],dfn[x]+sz[x]-1,qcnt};
	sort(q+1,q+qcnt+1);
	int z=1;
	while(q[z].p==0) res[q[z].id]=0,z++;
	for(int i=1;i<=n;i++){
		update(dfn[a[i]],1);
		while(q[z].p==i&&z<=qcnt) res[q[z].id]=query(q[z].r)-query(q[z].l-1),z++;
	}
	for(int i=1;i<=m;i++) cout<<(res[i*2]-res[i*2-1]>0?"YES":"NO")<<endl;
	for(int i=1;i<=n;i++) g[i].clear();
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int t=1;
	cin>>t;
	while(t--) solve();
	return 0;
}
```

---

## 作者：Unordered_OIer (赞：5)

UPD：过了

UPD：好像不是 Unintended Solution，但是现存那篇做法跟我一样的讲得有些简略，所以我也写一下吧！

# Description

给定一棵 $n$ 个节点的树，以及一个长度为 $n$ 的排列 $p$，$m$ 组询问，每次询问 $l,r,x$，需要回答在 $p_l \sim p_r$ 中有没有 $x$ 的后代。


# Solution

首先可以明确一件事情，如果 $y$ 在树中是 $x$ 的儿子，那么他们的 dfn（dfs 序）就会满足 $dfn[x] < dfn[y] \leq dfn[x]+sz[x]-1$，其中 $sz[x]$ 为$x$ 的子树大小。

我们让 $q[i] \leftarrow dfn[p[i]]$，询问就变成了是否存在 $l \leq y \leq r$ 使得 $q[y] \in [dfn[x],dfn[x]+sz[x]-1]$。

考虑把 $dfn$ 对应到 $y$ 轴，下标对应到 $x$ 轴，对于 $p[i]$，我们把它想象成一个点 $(i,dfn[p[i]])$，那么就变成了是否在 **左下角 $(l,dfn[x])$，右上角 $(r,dfn[x]+sz[x]-1)$ 的矩阵中有 $p[i]$ 对应的点**。

我们拿样例的第二组数据看一下，$dfn$ 序为 `1 3 8 6 10 4 2 9 7 5`，对应到 $p$ 上 `5 3 10 7 1 2 4 6 8 9`，就能画出图：

![](https://cdn.luogu.com.cn/upload/image_hosting/dlsltsf6.png)

然后看 `7 10 6` 和 `9 10 6`，前者是红色矩形圈出的区域，左下角有一个点，后者是蓝色矩形圈出的区域，没有点。

![](https://cdn.luogu.com.cn/upload/image_hosting/8j7ow98u.png)

所以分别是 YES 和 NO。

将询问离线下来按 $l$ 从小到大排个序，矩形 $(a,b) \rightarrow (c,d)$ 可以用容斥的方法算。然后整个坐标系可以用类似 树状数组维护逆序对 的方法，横坐标扫一遍就能计算出答案了。

$O(n \log n)$

实际上，我们可以发现所有的这 $n$ 个点不会有两个在同一条竖直线上，所以其实不需要完全按照类似二位前缀和那样维护，$Q(r)-Q(l-1)$ 即可。

---

## 作者：CQ_Bob (赞：3)

## 分析

一眼树上启发式合并。

定义 $x_i$ 为节点 $i$ 在序列 $p$ 中的下标。则问题转化为：对于每组 $l,r,k$，询问以 $k$ 为根的子树中是否有一个以上的节点，满足 $l \le x_j \le r$。

使用 set 存以 $i$ 为根的子树中 $x_j$ 的有序排列。则对于每个 $k=i$ 的询问，去合并之后的 set 中二分查找即可。树上启发式合并的话套版子就行了，只是多加了一个更新询问答案的过程而已。

注：模板题可以参照[这道](https://www.luogu.com.cn/problem/CF600E)。但该模板题难度评级显然有问题。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define re register
#define il inline
#define PII pair<int,pair<int,int>>
#define x first
#define y second

const int N=1e5+10;
int n,q;
int ne[N<<1],e[N<<1],h[N],idx;
struct node{
	set<int> st;
	vector<PII> Q;
	il int size(){return st.size();}
}sub[N];int x[N],id[N],cnt;
int ans[N];

il void add(int a,int b){ne[++idx]=h[a],e[idx]=b,h[a]=idx;}
il void dfs(int now,int fa){
	int mson=-1,msiz=0;
	id[now]=++cnt;
	for(re int i=h[now];i;i=ne[i]){
		int j=e[i];if(j==fa) continue;
		dfs(j,now);
		if(sub[id[j]].size()>msiz) msiz=sub[id[j]].size(),mson=j;
	}
	if(mson!=-1) id[now]=id[mson];
	for(re int i=h[now];i;i=ne[i]){
		int j=e[i];if(j==fa||j==mson) continue;
		for(auto s:sub[id[j]].st) sub[id[now]].st.insert(s);
		sub[id[j]].st.clear();
	}
	sub[id[now]].st.insert(x[now]);
	for(auto i:sub[now].Q){
		auto j=sub[id[now]].st.lower_bound(i.y.x);
		ans[i.x]=(j!=sub[id[now]].st.end()&&(*j)<=i.y.y);
	}
	return ;
}

il void solve(){
	cin>>n>>q;
	for(re int i=1;i<=n;++i) h[i]=ans[i]=x[i]=id[i]=0,sub[i].Q.clear(),sub[i].st.clear();
	idx=cnt=0;
	for(re int i=1,a,b;i<n;++i) cin>>a>>b,add(a,b),add(b,a);
	for(re int i=1,s;i<=n;++i) cin>>s,x[s]=i;
	for(re int i=1,l,r,x;i<=q;++i) cin>>l>>r>>x,sub[x].Q.push_back({i,{l,r}});
	dfs(1,0);
	for(re int i=1;i<=q;++i)
		if(ans[i]) cout<<"YES\n";
		else cout<<"NO\n";
	return ;
}

signed main(){
	int t;cin>>t;while(t--)
	solve();
	return 0;
}

```


---

## 作者：AlicX (赞：3)

## Solution 

考虑树上启发式合并：将 $x$ 子树内的点存放在 `set` 中，对于询问 `l r x`，在 $x$ 点中的 `set` 中进行二分查找即可。

以上的做法会 `MLE`，但是我们可以每次更新完 $x$ 点后，清空非重儿子的点，夫节点直接用当前 `set` 即可，于是空间复杂度即为 $O(n)$，时间复杂度为 $O(n\log n)$。

注意多测清空。

```cpp
#include<bits/stdc++.h>
#define ll long long 
#define x first 
#define y second 
#define debug() puts("-----") 
using namespace std; 
typedef pair<int,int> pii; 
const int N=1e5+10; 
int n,m; 
int cnt=0; 
set<int> s;
bool ans[N]; 
int h[N],idx=0;
int in[N],out[N]; 
int mp[N],kis[N]; 
int son[N],siz[N]; 
struct Node{ 
    int to,ne; 
}tr[N<<1]; 
struct Master{
    int l,r,id; 
}; vector<Master> q[N]; 
void add(int u,int v){ 
    tr[idx].to=v,tr[idx].ne=h[u],h[u]=idx++; 
} 
void modify(int u,int k){ 
    for(int i=in[u];i<=out[u];i++){ 
        if(k) s.insert(mp[kis[i]]); 
        else{ 
            auto it=s.lower_bound(mp[kis[i]]); 
            s.erase(it); 
        } 
    } 
} 
void dfs1(int u,int fa){ 
    int Max=0; 
    siz[u]=1; in[u]=++cnt,kis[cnt]=u; 
    for(int i=h[u];i!=-1;i=tr[i].ne){ 
        int to=tr[i].to; 
        if(to==fa) continue; 
        dfs1(to,u); siz[u]+=siz[to]; 
        if(siz[to]>Max) Max=siz[to],son[u]=to;  
    } out[u]=cnt; 
} 
void dfs2(int u,int fa,bool flag){ 
    for(int i=h[u];i!=-1;i=tr[i].ne){
        int to=tr[i].to; 
        if(to==fa||to==son[u]) continue; 
        dfs2(to,u,false); 
    } if(son[u]) dfs2(son[u],u,true); 
    for(int i=h[u];i!=-1;i=tr[i].ne){ 
        int to=tr[i].to; 
        if(to==fa||to==son[u]) continue; 
        modify(to,1); 
    } s.insert(mp[u]); 
    for(int i=0;i<q[u].size();i++){ 
        auto id=s.lower_bound(q[u][i].l); 
        if(*id<=q[u][i].r&&id!=s.end()) ans[q[u][i].id]=true; 
        else ans[q[u][i].id]=false; 
    } if(!flag) modify(u,0);
} 
void work(){ 
    idx=cnt=0; scanf("%d%d",&n,&m); 
    for(int i=1;i<=n;i++) h[i]=-1,mp[i]=son[i]=siz[i]=in[i]=out[i]=0,q[i].clear();    
    for(int i=1;i<n;i++){ 
        int u,v; 
        scanf("%d%d",&u,&v); 
        add(u,v),add(v,u); 
    } s.clear(); dfs1(1,0); 
    for(int i=1,x;i<=n;i++) scanf("%d",&x),mp[x]=i; 
    for(int i=1,l,r,x;i<=m;i++) scanf("%d%d%d",&l,&r,&x),q[x].push_back({l,r,i}),ans[i]=false;  
    dfs2(1,0,false); for(int i=1;i<=m;i++) printf("%s\n",ans[i]?"YES":"NO"); 
}  
signed main(){ 
    int T; scanf("%d",&T); 
    while(T--) work(); return 0; 
} /*
1
10 10
2 6
2 7
2 4
1 7
2 8
10 6
8 5
9 4
3 4
10 2 5 9 1 7 6 4 3 8
8 9 8
7 8 1
7 10 6
4 8 9
5 5 10
7 10 1
9 9 2
9 10 6
6 6 2
10 10 6
*/
```


---

## 作者：DerrickLo (赞：3)

挺典的吧。

首先我们考虑如何判断一个点 $u$ 是不是另一个点 $v$ 的后代。很明显，只需要将从根到 $u$ 的所有点的点权都加 $1$，然后判断 $v$ 点的点权是不是 $1$ 即可。

我们将原题转换成在 $[l,r]$ 间有多少个 $p_i$ 使得 $x$ 是 $p_i$ 的祖先，很明显可以差分一下，也就是算 $[1,r]$ 和 $[1,l-1]$ 间有多少个 $p_i$ 使得 $x$ 是 $p_i$ 的祖先。

那么我们可以在 $l-1$ 处打上减标记，在 $r$ 处打上加标记。然后从 $1$ 到 $n$ 每个点到根节点的路径权值增加 $1$，如果这一个点有减标记则将相应的点的答案减去当前这个点的权值，如果这一个点有加标记则将相应的点的答案加上当前这个点的权值，最后判断一下答案是否大于 $0$ 即可。

可以直接树剖。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,q,u,v,p[200005],top[200005],son[200005],sz[200005],fa[200005],dep[200005],id[200005],cnt,ans[200005],l,r,x[200005];
vector<int> ve[200005],ad[200005],de[200005];
struct tree{
	int l,r,sum,flag;
}tr[800005];
void pushup(int u){
	tr[u].sum=tr[u<<1].sum+tr[u<<1|1].sum;
}
void pushdown(int u){
	if(tr[u].flag){
		tr[u<<1].sum+=tr[u].flag*(tr[u<<1].r-tr[u<<1].l+1),tr[u<<1].flag+=tr[u].flag;
		tr[u<<1|1].sum+=tr[u].flag*(tr[u<<1|1].r-tr[u<<1|1].l+1),tr[u<<1|1].flag+=tr[u].flag;
		tr[u].flag=0;
	}
}
void dfs1(int u,int fat,int de){
	fa[u]=fat,dep[u]=de,sz[u]=1;
	for(int v:ve[u]){
		if(v==fa[u])continue;
		dfs1(v,u,de+1);
		sz[u]+=sz[v];
		if(sz[v]>sz[son[u]])son[u]=v;
	}
}
void dfs2(int u,int tp){
	top[u]=tp,id[u]=++cnt;
	if(!son[u])return;
	dfs2(son[u],tp);
	for(int v:ve[u]){
		if(v==fa[u]||v==son[u])continue;
		dfs2(v,v);
	}
}
void build(int u,int l,int r){
	tr[u]={l,r};
	if(l==r)return;
	int mid=l+r>>1;
	build(u<<1,l,mid),build(u<<1|1,mid+1,r);
	pushup(u);
}
void change(int u,int l,int r,int k){
	if(tr[u].l>=l&&tr[u].r<=r){
		tr[u].sum+=k*(tr[u].r-tr[u].l+1);
		tr[u].flag+=k;
		return;
	}
	pushdown(u);
	int mid=tr[u].l+tr[u].r>>1;
	if(l<=mid)change(u<<1,l,r,k);
	if(r>mid)change(u<<1|1,l,r,k);
	pushup(u); 
}
int query(int u,int l,int r){
	if(tr[u].l>=l&&tr[u].r<=r)return tr[u].sum;
	pushdown(u);
	int mid=tr[u].l+tr[u].r>>1,res=0;
	if(l<=mid)res+=query(u<<1,l,r);
	if(r>mid)res+=query(u<<1|1,l,r);
	return res;
}
void change_path(int u,int v,int k){
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]])swap(u,v);
		change(1,id[top[u]],id[u],k);
		u=fa[top[u]];
	}
	if(dep[u]<dep[v])swap(u,v);
	change(1,id[v],id[u],k);
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0); 
	cin>>t;
	while(t--){
		cin>>n>>q;
		cnt=0;
		for(int i=1;i<=n;i++)ve[i].clear(),ad[i].clear(),de[i].clear(),top[i]=son[i]=sz[i]=fa[i]=dep[i]=id[i]=ans[i]=0;
		for(int i=1;i<=4*n;i++)tr[i]={0,0,0,0};
		for(int i=1;i<n;i++)cin>>u>>v,ve[u].emplace_back(v),ve[v].emplace_back(u);
		dfs1(1,-1,1);
		dfs2(1,1);
		build(1,1,n);
		for(int i=1;i<=n;i++)cin>>p[i];
		for(int i=1;i<=q;i++){
			cin>>l>>r>>x[i];
			ad[r].emplace_back(i),de[l-1].emplace_back(i);
		}
		for(int i=1;i<=n;i++){
			change_path(1,p[i],1);
			for(int v:ad[i])ans[v]+=query(1,id[x[v]],id[x[v]]);
			for(int v:de[i])ans[v]-=query(1,id[x[v]],id[x[v]]);
		}
		for(int i=1;i<=q;i++){
			if(ans[i]>=1)cout<<"YES\n";
			else cout<<"NO\n";
		}
	}
	return 0;
}
```

---

## 作者：CQ_Bob (赞：2)

## 分析

对于区间问题，考虑莫队。

和[这个](https://www.luogu.com.cn/blog/993404/cf1899g-unusual-entertainment-ti-xie)一样转化问题。

把树变成 DFS 序之后，在序列上询问区间就是普通莫队模板了。用 `set` 记录当前区间里存放的有序 $x'$。移动完指针之后的判断是否存在就直接在 `set` 里二分。复杂度虽然大了不止一点，但是 $3$ 秒还是能过的。没有压力。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define re register
#define il inline

const int N=1e5+10;
int n,q,w[N];
int ne[N<<1],e[N<<1],h[N],idx;
int dfsx[N],in[N],out[N],cnt;
struct node{
	int l,r,L,R,id;
}Q[N];int len;
set<int> st;
int ans[N];

il void add(int a,int b){ne[++idx]=h[a],e[idx]=b,h[a]=idx;}
il void dfs(int now,int fa){
	dfsx[++cnt]=now,in[now]=cnt;
	for(re int i=h[now];i;i=ne[i]){
		int j=e[i];if(j==fa) continue;
		dfs(j,now);
	}
	out[now]=cnt;return ;
}

il bool cmp(node a,node b){
	if(a.l/len!=b.l/len) return a.l<b.l;
	if((a.l/len)&1) return a.r<b.r;
	return a.r>b.r;
}
il void add(int x){st.insert(w[x]);}
il void del(int x){st.erase(st.lower_bound(w[x]));}
il bool query(int l,int r){
	auto it=st.lower_bound(l);
	return (it!=st.end()&&(*it)<=r);
}
il void ini(int n){
	st.clear();cnt=idx=len=0;
	for(re int i=1;i<=n;++i) h[i]=0;
} 

il void solve(){
	cin>>n>>q;
	ini(n),len=sqrt(n);
	for(re int i=1,a,b;i<n;++i) cin>>a>>b,add(a,b),add(b,a);
	dfs(1,0);
	for(re int i=1,x;i<=n;++i) cin>>x,w[x]=i;
	for(re int i=1,l,r,x;i<=q;++i) cin>>l>>r>>x,Q[i]={in[x],out[x],l,r,i};
	sort(Q+1,Q+q+1,cmp);
	int l=1,r=0;
	for(re int i=1;i<=q;++i){
		while(l>Q[i].l) add(dfsx[--l]);
		while(r<Q[i].r) add(dfsx[++r]);
		while(l<Q[i].l) del(dfsx[l++]);
		while(r>Q[i].r) del(dfsx[r--]);
		ans[Q[i].id]=query(Q[i].L,Q[i].R); 
	}
	for(re int i=1;i<=q;++i) puts(ans[i]?"YES":"NO");
	return ;
}

signed main(){
	int t;cin>>t;while(t--)
	solve();
	return 0;
}

```


---

## 作者：Kevin911 (赞：0)

不知道为什么大家写得都那么复杂，还是讲讲我的思路吧。

## 思路

首先离线处理是很明显的。其次这里有一个小 trick：如果是算子树中的权值和的问题，只需要用遍历完该子树后的和减去遍历该子树前的和就行了，有一点像差分。而统计权值和的话只要树状数组维护一下就行了，时间复杂度 $O(n\log n)$。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+10;
int n,q;
int a[maxn],c[maxn],ans[maxn];
vector<int> g[maxn],que[maxn];
struct type
{
	int l,r,x;
}qu[maxn];
int lbt(int x)
{
	return x&(-x);
}
void update(int x,int y)
{
	for(int i=x;i<=n;i+=lbt(i)) c[i]+=y;
}
int query(int x)
{
	int res=0;
	for(int i=x;i;i-=lbt(i)) res+=c[i];
	return res;
}
void dfs(int u,int f)
{
	for(int i=0;i<que[u].size();i++)
	{
		int id=que[u][i];
		ans[id]=-(query(qu[id].r)-query(qu[id].l-1));
	}
	update(a[u],1);
	for(int i=0;i<g[u].size();i++)
	{
		int v=g[u][i];
		if(v==f) continue;
		dfs(v,u);
	}
	for(int i=0;i<que[u].size();i++)
	{
		int id=que[u][i];
		ans[id]+=(query(qu[id].r)-query(qu[id].l-1));
	}
}
signed main()
{
	int t;
	cin>>t;
	for(int p=1;p<=t;p++)
	{
		cin>>n>>q;
		for(int i=1;i<=n;i++) c[i]=0,g[i].clear();
		for(int i=1;i<=q;i++) que[i].clear();
		for(int i=1;i<n;i++)
		{
			int u,v;
			cin>>u>>v;
			g[u].push_back(v);
			g[v].push_back(u);
		}
		for(int i=1;i<=n;i++)
		{
			int u;
			cin>>u;
			a[u]=i;
		}
		for(int i=1;i<=q;i++)
		{
			cin>>qu[i].l>>qu[i].r>>qu[i].x;
			que[qu[i].x].push_back(i);
		}
		dfs(1,0);
		for(int i=1;i<=q;i++)
			if(ans[i]) cout<<"YES"<<endl;
			else cout<<"NO"<<endl;
		cout<<endl;
	}
}
```

---

## 作者：farfarqwq (赞：0)

看见题解区全是高深的数据结构和算法，但是这道题只需要一个简单的分块。

考虑对 $p$ 数组进行分块，对于整块预处理出这个块内的所有点的祖先集合，具体遍历块内每一个点暴力往上跳并标记，遇到标记过的点就 break，这样一遍是 $O(n)$ 的，总复杂度 $O(n\sqrt n)$。

询问时先处理整块的答案，如果没有找到就暴力判断散块，这里用到 dfs 序。预处理出每个点的 dfs 序 $dfn_i$ 和子树大小 $sz_i$，点 $x$ 是点 $i$ 的祖先当且仅当 $dfn_i\in[dfn_x,dfn_x+sz_x)$（$i$ 包含在 $x$ 的子树内）。这样就可以 $O(1)$ 判断。

这样就做完了，代码很好写，视 $n,q$ 同阶，时空复杂度都是 $O(n\sqrt n)$，不带 log 哟。

记得多测清空。

核心代码：

```cpp
int a[N];
int cnt, head[N];
struct edge {
    int v, next;
} e[N << 1];
void add(int u, int v) {
    e[++cnt].v = v;
    e[cnt].next = head[u];
    head[u] = cnt;
}
int tot, sz[N], dfn[N], f[N];
void dfs(int p) {
    dfn[p] = ++tot;
    sz[p] = 1;
    for (int i = head[p]; i; i = e[i].next) {
        int v = e[i].v;
        if (v != f[p]) {
            f[v] = p;
            dfs(v);
            sz[p] += sz[v];
        }
    }
}
bool vis[M][N];
int b[N], pe[N];
void solve() {
    int n, q;
    scanf("%d%d", &n, &q);
    cnt = 0;
    tot = 0;
    for (int i = 1; i <= n; i++)
        head[i] = 0;//清空
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        add(u, v);
        add(v, u);
    }
    int len = sqrt(n);
    dfs(1);//dfs预处理出 dfn、sz、father
    b[n + 1] = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &pe[i]);
        b[i] = (i - 1) / len + 1;
        if (b[i] != b[i - 1]) {
            for (int j = 1; j <= n; j++)
                vis[b[i]][j] = 0;//清空
        }
        int p = pe[i];
        while (p && !vis[b[i]][p]) {
            vis[b[i]][p] = 1;
            p = f[p];//暴力跳，直到跳到跳过的点
        }
    }
    while (q--) {
        int l, r, x;
        scanf("%d%d%d", &l, &r, &x);
        bool f = 0;
        if (b[l] == b[r]) {
            for (int i = l; i <= r; i++) {
                if (dfn[x] <= dfn[pe[i]] && dfn[pe[i]] < dfn[x] + sz[x]) {
                    f = 1;
                    break;
                }
            }//l和r在同一块内
        } else {
            for (int i = b[l] + 1; i < b[r]; i++) {
                if (vis[i][x]) {
                    f = 1;
                    break;
                }
            }//整块
            for (int i = l; !f && b[i] == b[l]; i++) {
                if (dfn[x] <= dfn[pe[i]] && dfn[pe[i]] < dfn[x] + sz[x]) {
                    f = 1;
                    break;
                }
            }
            for (int i = r; !f && b[i] == b[r]; i--) {
                if (dfn[x] <= dfn[pe[i]] && dfn[pe[i]] < dfn[x] + sz[x]) {
                    f = 1;
                    break;
                }
            }//散块
        }
        if (f)
            printf("YES\n");
        else
            printf("NO\n");
    }
    printf("\n");
}
int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        solve();
    }
    return 0;
}
```

---

## 作者：Iniaugoty (赞：0)

~~即便是这样简单的题，数据结构学傻的我不想思考也不会思考正解。~~

显然 $v$ 是 $u$ 的后代，当且仅当 $dfn _ u \le dfn _ v \le dfn _ u + siz _ u - 1$，其中 $dfn _ x$ 是 $x$ 的 dfs 序，$siz _ x$ 是 $x$ 的子树大小。

那么建 $n$ 棵权值线段树，第 $i$ 棵存 $p _ 1 \cdots  p _ i$ 的所有结点的 dfs 序，查询时用类似前缀和的方法找 $[l, r]$ 的值域上区间 $[dfn _ x, dfn _ x + siz _ x - 1]$ 中是否有数即可。这 $n$ 棵线段树用主席树维护一下就好了。

实现起来简单粗暴。

时间复杂度 $\mathcal O ((n + q) \log n)$ 显然能过；空间复杂度 $\mathcal O (n \log n)$，$10 ^ 5$ 的范围下不用担心 MLE 的问题。

```cpp
#include <bits/stdc++.h>

#define F(i, a, b) for(int i = (a); i <= (b); ++i)
#define dF(i, a, b) for(int i = (a); i >= (b); --i)

using namespace std;
typedef long long LL;
typedef unsigned long long ull;
const int N = 1e5 + 5;

int _, n, q, p[N];
vector<int> e[N];
void Addedge(int u, int v) {
	e[u].push_back(v);
	e[v].push_back(u);
}

int cnt, dfn[N], siz[N];
void Dfs(int u, int f) {
	dfn[u] = ++cnt;
	siz[u] = 1;
	for (auto v : e[u]) {
		if (v == f) continue;
		Dfs(v, u);
		siz[u] += siz[v];
	}
	return ;
}

int tot, rt[N];
struct node { int ls, rs, siz; } t[N * 18];
void Update(int x, int l, int r, int &u, int v) {
	t[u = ++tot] = t[v];
	++t[u].siz;
	if (l != r) {
		int mid = l + r >> 1;
		if (x <= mid) Update(x, l, mid, t[u].ls, t[v].ls);
		else Update(x, mid + 1, r, t[u].rs, t[v].rs);
	}
	return ;
}
int Query(int L, int R, int l, int r, int u, int v) {
	if (L <= l && r <= R) return t[u].siz - t[v].siz;
	int mid = l + r >> 1, res = 0;
	if (L <= mid) res += Query(L, R, l, mid, t[u].ls, t[v].ls);
	if (R > mid) res += Query(L, R, mid + 1, r, t[u].rs, t[v].rs);
	return res;
}

int main() {
	//freopen(".in", "r", stdin);
	//freopen(".out", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> _;
	while (_--) {
		cin >> n >> q;
		F(i, 1, n - 1) {
			int u, v;
			cin >> u >> v;
			Addedge(u, v);
		}
		Dfs(1, 0);
		F(i, 1, n) cin >> p[i];
		F(i, 1, n) Update(dfn[p[i]], 1, n, rt[i], rt[i - 1]);
		while (q--) {
			int l, r, x;
			cin >> l >> r >> x;
			if (Query(dfn[x], dfn[x] + siz[x] - 1, 1, n, rt[r], rt[l - 1])) cout << "Yes\n";
			else cout << "No\n";
		}
		cout << "\n";
		F(i, 1, n) e[i].clear();
		F(i, 1, tot) t[i].ls = t[i].rs = t[i].siz = 0;
		cnt = tot = 0;
	}
	return 0;
}
```

---

## 作者：Z1qqurat (赞：0)

比较一眼的一个题。

后代？太典了，直接考虑上 dfs 序。相当于问 $p_l \sim p_r$ 中有没有 dfs 序在 $dfn_x \sim dfn_x + siz_x - 1$ 范围内的。变成类似二维数点的问题了，考虑对询问莫队，那么每次只需要在树状数组上单点修改，区间查询就可以了。

然后如果要在线的话可能可以什么主席树或者树套树状物。当然不嫌麻烦的你也可以写什么 cdq 分治。

这也能当 Div3 G？？？感觉是见过的最没有思维难度也最没有代码难度的一场 Div3。

```cpp
#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
using namespace std;
const int N = 2e5 + 5;
int t, n, q, B, dfn[N], tot, siz[N], p[N];
bool ans[N];
vector <int> T[N];
struct Tsukinaga{
    int l, r, x, id;
    bool operator<(Tsukinaga b) {
        if(l / B == b.l / B) {
            if((l / B) & 1) return r < b.r;
            return r > b.r;
        }
        return l < b.l;
    }
} a[N];

void dfs(int u, int ff) {
    siz[u] = 1, dfn[u] = ++tot;
    for (int v : T[u]) {
        if(v == ff) continue;
        dfs(v, u), siz[u] += siz[v];
    }
    return ;
}

namespace BIT{
    int tr[N];
    void init() {
        fill(tr, tr + n + 1, 0); return ;
    }
    void modify(int x, int v) {
        while(x <= n) tr[x] += v, x += x & (-x);
        return ;
    }
    int query(int x) {
        int ret = 0;
        while(x > 0) ret += tr[x], x -= x & (-x);
        return ret;
    }
    int query(int x, int y) {
        return query(y) - query(x - 1);
    }
}

void solve() {
    cin >> n >> q; B = sqrt(n);
    for (int i = 1; i <= n; ++i) T[i].clear();
    BIT::init();
    for (int i = 1, u, v; i < n; ++i) {
        cin >> u >> v;
        T[u].emplace_back(v), T[v].emplace_back(u);
    }
    tot = 0, dfs(1, 0);
    for (int i = 1; i <= n; ++i) cin >> p[i], p[i] = dfn[p[i]];
    for (int i = 1; i <= q; ++i) {
        cin >> a[i].l >> a[i].r >> a[i].x; a[i].id = i;
    }
    sort(a + 1, a + q + 1);
    int l = 1, r = 0;
    for (int i = 1; i <= q; ++i) {
        int x = a[i].l, y = a[i].r, u = a[i].x;
        while(r < y) BIT::modify(p[++r], 1);
        while(l > x) BIT::modify(p[--l], 1);
        while(r > y) BIT::modify(p[r--], -1);
        while(l < x) BIT::modify(p[l++], -1);
        ans[a[i].id] = (BIT::query(dfn[u], min(n, dfn[u] + siz[u] - 1)) > 0);
    }
    for (int i = 1; i <= q; ++i) cout << (ans[i] ? "YES\n" : "NO\n");
    cout << "\n";
    return ;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> t;
    while(t--) solve();
    return 0;
}


---

## 作者：Register_int (赞：0)

直接上原神算法。求出 dfs 序后，求出每个点 $u$ 的子树区间 $[in_u,out_u]$。我们在移动左右端点时，要往集合中插入/删除一个数，然后查询集合中是否有在给定区间中的数。容易想到用树状数组维护前缀和，但是原神在移动左右端点时的复杂度为 $O(\log n)$，导致复杂度为 $O(n\sqrt n\log n)$，还是比较劣。

使用一下原神魔法！我们会移动 $O(n\sqrt n)$ 次左右端点，但是只会查询 $O(n)$ 次。也就是说，我们用一个 $O(1)$ 修改 $O(\sqrt n)$ 查询的算法维护前缀和即可。这个地方可以使用一个分块，时间复杂度降为 $O(n\sqrt n)$。

# AC 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 1e5 + 10;
const int MAXM = 3.2e2 + 10;

vector<int> g[MAXN]; int in[MAXN], out[MAXN], id;

void dfs(int u, int f) {
	in[u] = ++id;
	for (int v : g[u]) if (v != f) dfs(v, u);
	out[u] = id;
}

int len, tot, tl[MAXM], tr[MAXM], bel[MAXN];

int cnt[MAXN], sum[MAXM];

inline 
void init(int n) {
	len = sqrt(n), tot = (n - 1) / len + 1;
	for (int i = 1; i <= tot; i++) tl[i] = tr[i - 1] + 1, tr[i] = i * len; tr[tot] = n;
	for (int i = 1; i <= tot; i++) {
		sum[i] = 0;
		for (int j = tl[i]; j <= tr[i]; j++) bel[j] = i, cnt[j] = 0;
	}
}

inline 
void add(int k, int x) {
	cnt[k] += x, sum[bel[k]] += x;
}

inline 
int query(int l, int r) {
	int p = bel[l], q = bel[r], ans = 0;
	if (p == q) {
		for (int i = l; i <= r; i++) ans += cnt[i];
		return ans;
	}
	for (int i = l; i <= tr[p]; i++) ans += cnt[i];
	for (int i = p + 1; i < q; i++) ans += sum[i];
	for (int i = tl[q]; i <= r; i++) ans += cnt[i];
	return ans;
}

int b, p[MAXN];

struct node {
	int l, r, x, id;
	bool operator < (const node &rhs) const {
		return p[l] == p[rhs.l] ? p[l] & 1 ? r < rhs.r : r > rhs.r : p[l] < p[rhs.l];
	}
} q[MAXN];

int t, n, m, a[MAXN], ans[MAXN];

int l, r;

int main() {
	for (scanf("%d", &t); t--;) {
		scanf("%d%d", &n, &m), init(n), id = 0;
		for (int i = 1; i <= n; i++) g[i].clear();
		for (int i = 1, u, v; i < n; i++) {
			scanf("%d%d", &u, &v);
			g[u].push_back(v), g[v].push_back(u);
		}
		dfs(1, 0);
		for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
		b = max(1., n / sqrt(m)), l = 1, r = 0;
		for (int i = 1; i <= n; i++) p[i] = (i - 1) / b + 1;
		for (int i = 1; i <= m; i++) scanf("%d%d%d", &q[i].l, &q[i].r, &q[i].x), q[i].id = i;
		sort(q + 1, q + m + 1);
		for (int i = 1; i <= m; i++) {
			for (; l > q[i].l; add(in[a[--l]], 1));
			for (; r < q[i].r; add(in[a[++r]], 1));
			for (; l < q[i].l; add(in[a[l++]], -1));
			for (; r > q[i].r; add(in[a[r--]], -1));
			ans[q[i].id] = query(in[q[i].x], out[q[i].x]);
		}
		for (int i = 1; i <= m; i++) puts(ans[i] ? "Yes" : "No");
	}
}
```

---

## 作者：sunkuangzheng (赞：0)

首先我们求出 dfn 序，点 $x$ 是点 $u$ 的后代意味着 $dfn_u \le dfn_x \le dfn_u + siz_u - 1$，问题转化为询问排列 $p$ 的一段区间内，是否有点的 $dfn$ 序在一段区间内。

我们求出每个数字在排列里的位置 $a_i$（$p_i = x$ 则 $a_x = i$），那么询问变成给定 $l,r,x$，判断是否存在点 $y$ 满足：

$$\begin{cases}l \le a_y \le r\\dfn_x \le dfn_y \le dfn_x+siz_x-1\end{cases}$$

这是经典的二维数点问题，树状数组离线处理即可。时间复杂度 $\mathcal O(n \log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 5e5+5;
int T,n,t[N],fa[N],dfn[N],siz[N],tot,re,u,v,ans[N],p[N],x,qu,l,r,ql,qr;vector<int> g[N];
void dfs(int u,int f){
    dfn[u] = ++tot,siz[u] = 1;
    for(int v : g[u]) if(v != f) dfs(v,u),siz[u] += siz[v];
}int main(){
    ios::sync_with_stdio(0),cin.tie(0);
    cin >> T;
    auto upd = [](int x,int p){for(;x <= n;x += x & -x) t[x] += p;};
    auto qry = [](int x){for(re = 0;x;x -= x & -x) re += t[x];return re;};
    while(T --){
        cin >> n >> qu;
        for(int i = 1;i <= n;i ++) g[i].clear(),t[i] = ans[i] = 0;
        for(int i = 1;i < n;i ++) cin >> u >> v,g[u].push_back(v),g[v].push_back(u);
        tot = 0,dfs(1,0);vector<tuple<int,int,int>> q;
        for(int i = 1;i <= n;i ++) cin >> x,p[x] = i;
        for(int i = 1;i <= n;i ++) q.emplace_back(p[i],dfn[i],-1e9);
        for(int i = 1;i <= qu;i ++) cin >> l >> r >> u,ql = dfn[u],qr = dfn[u] + siz[u] - 1,q.emplace_back(r,qr,i),
                            q.emplace_back(l-1,ql-1,i),q.emplace_back(l-1,qr,-i),q.emplace_back(r,ql-1,-i);
        sort(q.begin(),q.end());
        for(auto [x,y,tp] : q)
            if(tp < -qu) upd(y,1); else ans[abs(tp)] += qry(y) * (tp > 0 ? 1 : -1);
        for(int i = 1;i <= qu;i ++) cout << (ans[i] ? "YES\n" : "NO\n");
    }
}

---

## 作者：WaterSun (赞：0)

# 思路

比较典的一个题。

把一棵树的 DFS 序剖下来过后再同一棵子树内的节点编号是连续的。

那么，我们查询 $(l,r,x)$ 时，问题就可以转化为在 $p_{l \sim r}$ 中是否出现过 $lid_x \sim rid_x$ 中的数，其中 $lid_i$ 表示 $i$ 所在子树的节点最小的 DFS 序的编号，$rid_i$ 同理。

然后把询问离线下来做即可。

# Code

```cpp
#include <bits/stdc++.h>
#define re register

using namespace std;

const int N = 2e5 + 10,M = 4e5 + 10;
int n,q;
int ans[2][N];
int idx,h[N],ne[M],e[M],arr[N];
int num,id[N],sz[N];

struct Query{
    int op,l,r,id;
};
vector<Query> Q[N];

inline int read(){
    int r = 0,w = 1;
    char c = getchar();
    while (c < '0' || c > '9'){
        if (c == '-') w = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9'){
        r = (r << 3) + (r << 1) + (c ^ 48);
        c = getchar();
    }
    return r * w;
}

inline void add(int a,int b){
    ne[idx] = h[a];
    e[idx] = b;
    h[a] = idx++;
}

struct BIT{
    int tr[N];

    inline int lowbit(int x){
        return x & -x;
    }

    inline void modify(int x,int k){
        for (re int i = x;i <= n;i += lowbit(i)) tr[i] += k;
    }

    inline int query(int x){
        int res = 0;
        for (re int i = x;i;i -= lowbit(i)) res += tr[i];
        return res;
    }
}T;

inline void init(){
    for (re int i = 1;i <= n;i++){
        Q[i].clear();
        h[i] = -1;
        T.tr[i] = ans[0][i] = ans[1][i] = sz[i] = id[i] = 0;
    }
}

inline void dfs(int u,int fa){
    sz[u] = 1;
    id[u] = ++num;
    for (re int i = h[u];~i;i = ne[i]){
        int j = e[i];
        if (j == fa) continue;
        dfs(j,u);
        sz[u] += sz[j];
   }
}

inline void solve(){
    idx = num = 0;
    n = read();
    q = read();
    init();
    for (re int i = 1;i < n;i++){
        int a,b;
        a = read();
        b = read();
        add(a,b);
        add(b,a);
    }
    dfs(1,0);
    for (re int i = 1;i <= n;i++) arr[i] = read();
    for (re int i = 1;i <= q;i++){
        int l,r,x;
        l = read();
        r = read();
        x = read();
        Q[l - 1].push_back({0,id[x],id[x] + sz[x] - 1,i});
        Q[r].push_back({1,id[x],id[x] + sz[x] - 1,i});
    }
    for (re int i = 1;i <= n;i++){
        T.modify(id[arr[i]],1);
        for (auto p:Q[i]) ans[p.op][p.id] = T.query(p.r) - T.query(p.l - 1);
    }
    for (re int i = 1;i <= q;i++){
        if (ans[1][i] - ans[0][i]) puts("YES");
        else puts("NO");
    }
}

int main(){
    int T;
    T = read();
    while (T--) solve();
    return 0;
}
```

---

## 作者：operator_ (赞：0)

# Unusual Entertainment

[题目传送门](https://www.luogu.com.cn/problem/CF1899G)

## 题解

真的不要太典，，，

考虑点 $u$ 是 $v$ 的后代等价于 $u$ 在子树 $v$ 中，dfs 序直接走起，记 $in_i$ 和 $out_i$ 为点 $i$ 被遍历到与离开时的时间戳，变成判断是否存在 $i$ 使得：

$$in_x\le in_{p_i}\le out_x,l\le i\le r$$

发现这就是二维数点，我们把每个询问离线并差分成两个，然后扫描其中一维并用树状数组统计另一维即可（详见注释）。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int rd() {
	int s=0,m=0;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')m=1;ch=getchar();}
	while( isdigit(ch)) s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
	return m?-s:s;
}
int tt,n,q,p[100005],ans[100005];
int h[100005],cnt;
struct QWQ{int v,nxt;} e[100005*2];
void add(int u,int v) {e[++cnt]={v,h[u]},h[u]=cnt;}
int in[100005],out[100005],tot;
void dfs(int u,int p) {
	in[u]=++tot;
	for(int i=h[u];i;i=e[i].nxt) {
		int v=e[i].v;
		if(v==p) continue;
		dfs(v,u);
	}
	out[u]=tot;
}
struct Query{int l,x,id;} a[200005];
bool cmp(Query a1,Query a2) {return a1.l<a2.l;}
struct Binary_Indexed_Tree {
	int t[100005];
	int lb(int x) {return x&-x;}
	int sum(int x) {int s=0;for(int i=x;i;i-=lb(i)) s+=t[i];return s;}
	int query(int x,int y) {return sum(y)-sum(x-1);}
	void add(int x,int k) {for(int i=x;i<=n;i+=lb(i)) t[i]+=k;}
} t;
signed main() {
	cin>>tt;
	while(tt--) {
		n=rd(),q=rd();
		memset(h,0,sizeof(h));tot=cnt=0;
		memset(ans,0,sizeof(ans));
		memset(t.t,0,sizeof(t.t));
		for(int i=1;i<n;i++) {
			int u=rd(),v=rd();
			add(u,v),add(v,u);
		}
		dfs(1,0);
		for(int i=1;i<=n;i++) 
			p[i]=rd();
		for(int i=1;i<=q;i++) {
			int l=rd(),r=rd(),x=rd();
			a[i*2-1]={l-1,x,-i};
			a[i*2]={r,x,i};//差分
		}
		sort(a+1,a+q*2+1,cmp);
		for(int i=0,j=1;i<=n;i++) {
			if(i) t.add(in[p[i]],1);//加入点(i,in[p[i]])的贡献
			for(;j<=q*2&&a[j].l==i;j++) 
				if(a[j].id>0) ans[a[j].id]+=t.query(in[a[j].x],out[a[j].x]);
				else ans[-a[j].id]-=t.query(in[a[j].x],out[a[j].x]);//统计询问的答案
		}
		for(int i=1;i<=q;i++)
			puts(ans[i]>0?"YES":"NO");
		puts("");
	}
	return 0;
}

```

---

## 作者：ax_by_c (赞：0)

首先可以把 $i$ 在 $p$ 中的位置 $at_i$ 求出来。

那么原来的边 $(u,v)$ 此时就变为了 $(at_u,at_v)$，根变为了 $at_1$，而询问则变为了子树内是否有给定范围的节点。

考虑转化为 dfs 序，转化后就变为了区间内是否有给定范围元素。

此时就好写了，随便找个数据结构维护一下即可，我写的是分块。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
const int SQN=1e3+5;
int n,q;
int u,v;
vector<int>g[N];
int p[N];
int at[N];
int rt;
int dfn[N],Time;
int ls[N],rs[N];
void dfs(int u,int fa)
{
	dfn[++Time]=u;
	ls[u]=rs[u]=Time;
	for(auto v:g[u])
	{
		if(v!=fa)
		{
			dfs(v,u);
			rs[u]=max(rs[u],rs[v]);
		}
	}
}
int bl[SQN],br[SQN],blk,len;
int col[N];
int b[N];
vector<pair<int,int>>uvs;
void slove()
{
	scanf("%d %d",&n,&q);
	for(int i=1;i<=n;i++)
	{
		g[i].clear();
	}
	uvs.clear();
	for(int i=1;i<n;i++)
	{
		scanf("%d %d",&u,&v);
		uvs.push_back({u,v});
	}
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&p[i]);
		at[p[i]]=i;
	}
	for(auto pr:uvs)
	{
		u=pr.first;
		v=pr.second;
		u=at[u];
		v=at[v];
		g[u].push_back(v);
		g[v].push_back(u);
	}
	rt=at[1];
	Time=0;
	dfs(rt,0);
	len=sqrt(n);
	blk=0;
	for(int i=1;br[i-1]!=n;i++)
	{
		blk++;
		bl[i]=br[i-1]+1;
		br[i]=bl[i]+len-1;
		if(br[i]>n)
		{
			br[i]=n;
		}
		for(int j=bl[i];j<=br[i];j++)
		{
			col[j]=i;
		}
	}
	for(int i=1;i<=n;i++)
	{
		b[i]=dfn[i];
	}
	for(int i=1;i<=blk;i++)
	{
		sort(b+bl[i],b+br[i]+1);
	}
	int l,r,u;
	for(int cs=1;cs<=q;cs++)
	{
		scanf("%d %d %d",&l,&r,&u);
		u=at[u];
		int ql,qr;
		ql=ls[u];
		qr=rs[u];
		if(col[qr]-col[ql]<=1)
		{
			bool fd=0;
			for(int i=ql;i<=qr;i++)
			{
				if(l<=dfn[i]&&dfn[i]<=r)
				{
					fd=1;
				}
			}
			if(fd)
			{
				printf("YES\n");
			}
			else
			{
				printf("NO\n");
			}
			continue;
		}
		bool fd=0;
		for(int i=ql;i<=br[col[ql]];i++)
		{
			if(l<=dfn[i]&&dfn[i]<=r)
			{
				fd=1;
			}
		}
		for(int i=bl[col[qr]];i<=qr;i++)
		{
			if(l<=dfn[i]&&dfn[i]<=r)
			{
				fd=1;
			}
		}
		for(int i=col[ql]+1;i<=col[qr]-1;i++)
		{
			int L=bl[i],R=br[i],mid,res=-1;
			while(L<=R)
			{
				mid=L+((R-L)>>1);
				if(b[mid]<l)
				{
					L=mid+1;
				}
				else
				{
					res=mid;
					R=mid-1;
				}
			}
			if(res!=-1)
			{
				if(l<=b[res]&&b[res]<=r)
				{
					fd=1;
				}
			}
		}
		if(fd)
		{
			printf("YES\n");
		}
		else
		{
			printf("NO\n");
		}
	}
}
int main()
{
	int CS;
	scanf("%d",&CS);
	for(int cs=1;cs<=CS;cs++)
	{
		slove();
		putchar('\n');
	}
	return 0;
}
```

---

## 作者：LCat90 (赞：0)

如果 $y$ 是 $x$ 的后代当且仅当 $y$ 在 $x$ 的子树中。

转化成 dfn 问题，即 $\text{dfn} _y \in [ 
\text{dfn}_x,\text{dfn}_x+siz_x-1 ]$。

原问题等价于查询区间 $[l,r]$ 中有无某个数的 dfn 值属于区间 $[ 
\text{dfn}_x,\text{dfn}_x+siz_x-1 ]$。就是主席树板子了。

```cpp
#include <bits/stdc++.h>
#define pb push_back
using namespace std;
const int N = 1e5 + 5;
int n, q, Root[N], cnt = 1, a[N], b[N], dfn[N];
struct node {
	int l, r, ls, rs;
	int sum;
} T[N * 17 * 4];
void pushup(int p) { T[p].sum = T[T[p].ls].sum + T[T[p].rs].sum; }
int build(int l, int r) {
	int rt = ++cnt;
	T[rt].l = l, T[rt].r = r; T[rt].sum = 0;
	if(l == r) return rt;
	int mid = l + r >> 1;
	T[rt].ls = build(l, mid);
	T[rt].rs = build(mid + 1, r);
	return rt;	
}
int New(int p) {
	T[++cnt] = T[p];
	return cnt; 
}
int update(int p, int k, int x) {
	int rt = New(p); 
	if(T[rt].l == k and T[rt].r == k) {
		T[rt].sum += x;
		return cnt;
	}
	int mid = T[rt].l + T[rt].r >> 1;
	if(k <= mid) T[rt].ls = update(T[rt].ls, k, x);
	else T[rt].rs = update(T[rt].rs, k, x);
	pushup(rt);
	return rt;
}
int query(int x1, int x2, int l, int r) {
	if(T[x1].l >= l and T[x1].r <= r) return T[x2].sum - T[x1].sum;
//	cout << x1 << " " << x2 << "\n";
	int mid = T[x1].l + T[x1].r >> 1, ans = 0;
	if(l <= mid) ans += query(T[x1].ls, T[x2].ls, l, r);
	if(r > mid) ans += query(T[x1].rs, T[x2].rs, l, r);
	return ans;
}
int Cnt = 0, siz[N];
vector <int> G[N];
void dfs(int x, int fa) {
	dfn[x] = ++Cnt; siz[x] = 1;
	for(auto to : G[x]) {
		if(to == fa) continue ;
		dfs(to, x); siz[x] += siz[to];
	}
}
void solve() {
	cin >> n >> q; cnt = 1; Cnt = 0;
	for(int i = 1;i <= n; ++i) G[i].clear();
	for(int i = 1, x, y;i < n; ++i) {
		cin >> x >> y;
		G[x].pb(y), G[y].pb(x); 
	}
	dfs(1, 0); Root[0] = build(1, n);
	for(int i = 1, x;i <= n; ++i) {
		cin >> x;
		Root[i] = update(Root[i - 1], dfn[x], 1); //cout << dfn[x] << " ";
	}
	while(q--) {
		int l, r, x; cin >> l >> r >> x;
		int ans = query(Root[l - 1], Root[r], dfn[x], dfn[x] + siz[x] - 1);
		if(ans) puts("Yes");
		else puts("No");
	} puts("");
}
signed main() {
	int T; cin >> T;
	while(T--) solve();	
	return 0;
}
```

---

## 作者：aCssen (赞：0)

### Solution
一个点是 $x$ 的后代，等价于它在 $x$ 的子树里。

那么我们求出树上每一个点的 $dfn$ 表示它被访问到的时间，$siz$ 表示这个点的子树大小，那么对于所有满足 $dfn_{x} \le dfn_p  \le dfn_{x}+siz_{x}-1$ 的所有点 $p$ 都在 $x$ 的子树里。

那么题目里的排列就没用了，我们输入的同时把 $x$ 直接转化为 $dfn_{x}$ 即可。

那么现在问题被转化为：$q$ 组询问，每组询问给出 $l,r,x$，问是否存在一个在 $l,r$ 间的位置，满足序列中该位置的置在 $dfn_{x}$ 和 $dfn_{x}+siz_{x}-1$ 之间，那么是二维数点问题，主席树即可。

时间复杂度 $\mathcal{O}(n+q \log n)$，但是在线，但是 $20$ 倍空间。
### Code
```cpp
#include<iostream>
#include<cstdio>
#include<vector>
using namespace std;
const int maxn=1e5+5;
int root[maxn],siz[maxn],dfn[maxn],head[maxn],ver[maxn<<1],nxt[maxn<<1],tot,cnt,num,n,q;
struct node{int ls,rs,cnt;}t[maxn<<5];
int insert(int now,int x,int l,int r){
	int p=++num;
	t[p]=t[now];
	t[p].cnt++;
	if(l==r) return p;
	int mid=l+r>>1;
	if(x<=mid) t[p].ls=insert(t[now].ls,x,l,mid);
	else t[p].rs=insert(t[now].rs,x,mid+1,r);
	return p;
}
int query(int p,int q,int x,int y,int l,int r){
	if(x<=l&&r<=y) return t[q].cnt-t[p].cnt;
	int mid=l+r>>1,ans=0;
	if(x<=mid) ans+=query(t[p].ls,t[q].ls,x,y,l,mid);
	if(y>mid) ans+=query(t[p].rs,t[q].rs,x,y,mid+1,r);
	return ans;
}
void add_edge(int u,int v){
	ver[++tot]=v;
	nxt[tot]=head[u];
	head[u]=tot;
}
void dfs(int x,int fa){
	siz[x]=1;
	dfn[x]=++cnt;
	for(int i=head[x];i;i=nxt[i]){
		int y=ver[i];
		if(y==fa) continue;
		dfs(y,x);
		siz[x]+=siz[y];
	}
}
void solve(){
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++) head[i]=0;
	tot=cnt=num=0;
	for(int i=1;i<n;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		add_edge(u,v);
		add_edge(v,u);
	}
	dfs(1,0);
	for(int i=1;i<=n;i++){
		int p;
		scanf("%d",&p);
		root[i]=insert(root[i-1],dfn[p],1,n);
	}
	while(q--){
		int l,r,x;
		scanf("%d%d%d",&l,&r,&x);
		int ans=query(root[l-1],root[r],dfn[x],dfn[x]+siz[x]-1,1,n);
		if(ans) printf("Yes\n");
		else printf("No\n");
	}
	printf("\n");
}
int main(){
	int t;
	scanf("%d",&t);
	while(t--) solve();
	return 0;
} 
```

---

