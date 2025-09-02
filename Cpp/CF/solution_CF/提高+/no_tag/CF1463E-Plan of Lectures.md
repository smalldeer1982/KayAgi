# Plan of Lectures

## 题目描述

Ivan is a programming teacher. During the academic year, he plans to give $ n $ lectures on $ n $ different topics. Each topic should be used in exactly one lecture. Ivan wants to choose which topic will he explain during the $ 1 $ -st, $ 2 $ -nd, ..., $ n $ -th lecture — formally, he wants to choose some permutation of integers from $ 1 $ to $ n $ (let's call this permutation $ q $ ). $ q_i $ is the index of the topic Ivan will explain during the $ i $ -th lecture.

For each topic (except exactly one), there exists a prerequisite topic (for the topic $ i $ , the prerequisite topic is $ p_i $ ). Ivan cannot give a lecture on a topic before giving a lecture on its prerequisite topic. There exists at least one valid ordering of topics according to these prerequisite constraints.

Ordering the topics correctly can help students understand the lectures better. Ivan has $ k $ special pairs of topics $ (x_i, y_i) $ such that he knows that the students will understand the $ y_i $ -th topic better if the lecture on it is conducted right after the lecture on the $ x_i $ -th topic. Ivan wants to satisfy the constraints on every such pair, that is, for every $ i \in [1, k] $ , there should exist some $ j \in [1, n - 1] $ such that $ q_j = x_i $ and $ q_{j + 1} = y_i $ .

Now Ivan wants to know if there exists an ordering of topics that satisfies all these constraints, and if at least one exists, find any of them.

## 样例 #1

### 输入

```
5 2
2 3 0 5 3
1 5
5 4```

### 输出

```
3 2 1 5 4```

## 样例 #2

### 输入

```
5 2
2 3 0 5 3
1 5
5 1```

### 输出

```
0```

## 样例 #3

### 输入

```
5 1
2 3 0 5 3
4 5```

### 输出

```
0```

## 样例 #4

### 输入

```
5 4
2 3 0 5 3
2 1
3 5
5 2
1 4```

### 输出

```
3 5 2 1 4```

# 题解

## 作者：OMG_wc (赞：10)

用并查集把每个相邻的部分缩点，同时找出缩点部分的起点，并且在缩点过程中也能用并查集判断是否存在循环。

然后按原拓扑关系树建立新图，在上面跑拓扑排序，得到一组答案。

如果几个分隔的部分出现矛盾在新图会形成环，而连续的一段出现矛盾还需要继续检查和原拓扑关系树是否相符合，也就是再模拟一遍。

参考代码如下：

```c++
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int INF = 0x3f3f3f3f;
const LL mod = 1e9 + 7;
const int N = 300005;

int p[N];
int find(int x) {
    return p[x] == x ? x : p[x] = find(p[x]);
}
int a[N], b[N], c[N], in[N], ans[N];
vector<int> G[N], H[N];
bool vis[N];
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    int root;
    for (int i = 1; i <= n; i++) {
        int fa;
        scanf("%d", &fa);
        p[i] = i;
        if (fa == 0)
            root = i;
        else
            H[fa].push_back(i);
    }
    while (m--) {
        int x, y;
        scanf("%d%d", &x, &y);
        a[x] = y;
        b[y] = x;
        x = find(x), y = find(y);
        if (x == y) return puts("0"), 0;  //出现循环
        p[x] = y;
    }
    for (int i = 1; i <= n; i++) {
        if (b[i] == 0) c[find(i)] = i;  // 起点
        for (auto v : H[i]) {
            if (find(i) != find(v)) {
                G[find(i)].push_back(find(v));
                in[find(v)]++;
            }
        }
    }
    queue<int> q;
    q.push(find(root));
    int ct = 0;
    while (q.size()) {
        int u = q.front();
        q.pop();
        int t = c[u];
        while (t) {
            ans[++ct] = t;
            t = a[t];
        }
        for (auto v : G[u]) {
            in[v]--;
            if (in[v] == 0) {
                q.push(v);
            }
        }
    }
    if (ct != n) return puts("0"), 0;
    vis[root] = 1;
    for (int i = 1; i <= n; i++) {
        if (vis[ans[i]] == 0) return puts("0"), 0;
        for (auto v : H[ans[i]]) vis[v] = 1;
    }
    for (int i = 1; i <= n; i++) printf("%d%c", ans[i], " \n"[i == n]);
    return 0;
}
```



---

## 作者：紊莫 (赞：1)

如果要有解，那么这 $k$ 个关系一定组成了若干条链，否则无解，不妨把这些链缩成一个个代表点，可以使用并查集解决。

将原图中的关系变成一个关键点构成的 DAG，如果无法构成，宣布无解，之后进行拓扑排序，得到一个答案。

但是还没完，需要验证答案，假设存在点 $u$ 和点 $v$在同一条链中，$u$ 在 $v$ 前面，但是 $v$ 却是 $u$ 的祖先，那么是不行的，我们不妨采用如下方法模拟“解锁”的过程。  

```cpp
lock[root]=1;
for(int i:ans){
	if(!lock[i])
		cout<<0,exit(0);
	for(auto j:G[i])
		lock[j]=1;
}
```

这一步假如放到前面去做很难判断祖先关系，不如在最后验证一次答案比较简单。

总结：这题思维量不太大，但是情况比较多，稍有漏判就会出错。

[示例代码。](https://www.luogu.com.cn/paste/xzt4llpu)


---

## 作者：立柱已选162534 (赞：1)

## 思路

这道题给出的限制分两种：

1. 一个数 $p_i$ 在另一个数 $i$ 前面

1. 一个数 $x$ 在另一个数 $y$ 前一个位置

看到先后顺序，想到处理大小关系的拓扑排序，同时两个数相邻为明显的并查集，于是就可以使用并查集合并相邻的点，然后拓扑排序做了。

## 实现

### 合并相邻的点

只使用并查集无法找到输出需要的先后顺序，于是我选择用一个链表维护一个连通块，具体来说对每个点 $i$ 维护向后的一个指针 $nex_i$，合并 $x,y$ 时只需将 $x,y$ 所在集合合并，然后把 $nex_i$ 指向$y$ 即可。

代码中有一个技巧，即把 $y$ 所在集合合并到 $x$ 所在集合中，从而保证在并查集中能使 $f_x=x$ 的 $x$ 均为一个连通块的开头。

**无解：** 此时若 $x$ 与$y$ 在同一集合中（左边那张图中的情况），则说明无解，由于题目中保证所有 $x$ 与所有 $y$ 分别不相等，所以不会出现右边那张图中的情况。

![](https://cdn.luogu.com.cn/upload/image_hosting/az7ugo49.png)
![](https://cdn.luogu.com.cn/upload/image_hosting/0u8a67w1.png)

### 缩点连边

使用每个连通块的开头作为当前连通块的代表进行缩点，对每对 $i$ 与 $p_i$ 所在的缩点考虑连边，分两种情况讨论：

1. 若 $i$ 与 $p_i$ 在同一连通块中，不需要连边，预处理一下连通块内的先后顺序，直接比较判断 $i$ 是否在 $p_i$ 后面，如果不是输出无解即可。

2. 若 $i$ 与 $p_i$ 不在同一连通块中，从 $i$ 所在的连通块向 $p_i$ 所在的连通块连边即可。

### 拓扑排序

没啥好说的，直接将缩点拓扑排序，如果出现环直接输出无解即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=300005;
int n,k,a[N],x,y;
int nex[N];
int f[N],cnt;
int find(int x){//一种神奇的低常数路径压缩
	while(f[x]!=x)x=f[x]=f[f[x]];
	return x;
}
int to[N],ne[N],h[N],nowed;
int in[N],ord[N],b[N];
int now;
void add(int x,int y){
	to[++nowed]=y,ne[nowed]=h[x],h[x]=nowed;
}
bool topsort();
bool topsort(){//拓扑排序
	queue<int> x;
	int cnt1=0;
	for(int i=1;i<=cnt;++i)
		if(!in[b[i]])x.push(b[i]);
	while(!x.empty()){
		now=x.front();x.pop();
		ord[++cnt1]=now;//存下拓扑序
		for(int i=h[now];i;i=ne[i])
			if(!(--in[to[i]]))x.push(to[i]);
	}
	return cnt1==cnt;
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>k;
	for(int i=1;i<=n;++i){
		cin>>a[i];
		f[i]=i;
	}
	for(int i=1;i<=k;++i){
		cin>>x>>y;
		if(find(x)==find(y)){//判断是否出现环
			cout<<0;
			return 0;
		}
		nex[x]=y;//维护链表
		f[find(y)]=find(x);//合并，注意此时从后往前连，方便输出时找到第一个数
	}
	for(int i=1;i<=n;++i)//处理连通块内顺序
	if(f[i]==i){
		b[++cnt]=i;
		now=i;
		while(nex[now]){
			ord[nex[now]]=ord[now]+1;//暂时借用ord数组存下连通块内的信息
			now=nex[now];
		}
	}
	for(int i=1;i<=n;++i)//给缩点连边
	if(a[i]){
		x=find(i),y=find(a[i]);
		if(x!=y){//分类，不在同一连通块使用拓扑排序判断
			add(y,x);
			++in[x];//维护入度
		}
		else if(ord[a[i]]>ord[i]){//在同一连通块直接使用块内顺序判断
			cout<<0;
			return 0;
		}
	}
	if(!topsort()){
		cout<<0;
		return 0;
	}
	for(int i=1;i<=cnt;++i){//输出
		now=ord[i];//拓扑序为第一关键字
		while(now){
			cout<<now<<" ";//块内顺序为第二关键字
			now=nex[now];
		}
	}
	return 0;
}
```

---

## 作者：lfxxx (赞：0)

假若没有第二个限制？

直接 $a_i \to i$ 建图跑拓扑排序即可。

有第二个限制咋做？

考虑相邻这个限制特别强，于是按照第二个限制对图缩点，再跑拓扑排序即可，注意特判一下被缩起来的点之间的连边。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 3e5+114;
int nxt[maxn],dep[maxn],fa[maxn];
int lst[maxn];
vector<int> E[maxn];
int In[maxn];
int a[maxn];
int n,k;
int ans[maxn];
int tot;
queue<int> q;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n>>k;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=k;i++){
        int x,y;
        cin>>x>>y;
        nxt[x]=y;
        lst[y]=x;
    }
    int cnt=0;
    for(int i=1;i<=n;i++){
        if(lst[i]==0){
            dep[i]=1;
            int v=i;
            fa[i]=i;
            cnt++;
            while(nxt[v]!=0){
                dep[nxt[v]]=dep[v]+1;
                v=nxt[v];
                cnt++;
                fa[v]=i;
            }
        }
    }
    if(cnt<n){
        cout<<0<<'\n';
        return 0;
    }
    for(int i=1;i<=n;i++){
        if(a[i]==i){
            cout<<0<<'\n';
            return 0;
        }
        if(a[i]!=0){
            //a[i]->i
            int u=a[i],v=i;
            if(fa[u]==fa[v]){
                if(dep[u]>dep[v]){
                    cout<<0<<'\n';
                    return 0;
                }
            }else{
                E[fa[u]].push_back(fa[v]);
                In[fa[v]]++;
            }
        }
    }
    for(int i=1;i<=n;i++){
        if(fa[i]==i){
            if(In[i]==0){
                q.push(i);
            }
        }
    }
    while(q.size()>0){
        int u=q.front();
        q.pop();
        int v=u;
        while(v!=0){
            ans[++tot]=v;
            v=nxt[v];
        }
        for(int to:E[u]){
            In[to]--;
            if(In[to]==0) q.push(to);
        }
    }
    if(q.size()>0||tot<n){
        cout<<0<<'\n';
        return 0;
    }
    for(int i=1;i<=tot;i++) cout<<ans[i]<<' ';
    return 0;
}

```

---

## 作者：KazamaRuri (赞：0)

## 题意

要求你构造一个 $1\sim n$ 的排列，要满足：
+ $a_i$ 出现在 $i$ 之前，如果 $a_i=0$ 代表这个数没有限制。仅对条件一保证一定有解。
+ 有 $k$ 个特殊对 $(i,j)$，要求满足 $i$ 在排列中一定在 $j$ 的左一位。询问是否存在这样的排列。

保证恰好存在一个 $i$ 使得 $a_i = 0$。

## 分析

发现多个特殊对拼在一起能构成一段确定的连续子序列，如果把特殊对看作边的关系，那么连续子序列就是一个连通块，直接拿并查集维护连通块并且缩点就好了，然后就会有第一种无解情况，并查集合并到了同一个集合内的元素，显然无解，因为不可能一个位置上放两个数。而对于第一个条件，是拓扑排序的基础应用，直接连 $belong_{a_i} \rightarrow belong_{i}$ 的边（$belong_{i}$ 表示缩完点后 $i$ 对应那个点，人话就是并查集的链头），当然这样会有自环，我们可以先忽略掉这样的边。最后判断有没有有环就是无解，有解按拓扑序输出每个点对应的子序列。写完这两段就会发现样例都过不了，这是因为没有考虑两个条件之间的限制，也就是被忽略掉的自环边，有可能会出现第一个条件 $x$ 在 $y$ 前面，然后第二个条件里 $x$ 在连续子序列里在 $y$ 后面出现。一种解决办法是给每个连通块内的点按下标顺序重编号一下，连边时遇到自环边特判一下编号顺序对不对再忽略这条边，然后就只有这三种无解情况了，线性做法就能过了。

## 代码

没有刻意压行。

遍历连通块我用的是链表来维护了一下，即代码中的 $nxt$ 数组。

```cpp
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;
using ll =long long;
const int N=3e5+5;
int n,m,a[N],f[N],nxt[N],tot,cnt,head[N],d[N],rk[N],st[N],top;
struct Edge{ int to,next; }e[N<<1]; queue<int>q;
void add(int u,int v){ e[++cnt]={v,head[u]},head[u]=cnt,d[v]++; }
int find(int x){ return x==f[x]?x:f[x]=find(f[x]); }
void uni(int x,int y){ if(find(x)==find(y)) putchar(48),exit(0); f[f[y]]=f[x]; }
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",a+i),f[i]=i;
	for(int i=1,u,v;i<=m;i++)
		scanf("%d%d",&u,&v),
		uni(u,v),nxt[u]=v;
	for(int i=1;i<=n;i++){
		if(i==find(i)){
			int id=0; add(0,i),tot++;
			for(int j=i;j;j=nxt[j])
				rk[j]=++id;
		}
		if(a[i])
			if(find(a[i])^find(i)) add(f[a[i]],f[i]);
			else if(rk[a[i]]>rk[i]) putchar(48),exit(0);
	} q.push(0);
	for(int u;q.size();q.pop()){
		st[++top]=u=q.front();
		for(int i=head[u];i;i=e[i].next){
			int v=e[i].to; if(!--d[v]) q.push(v);
		}
	}
	if(tot+1^top) putchar(48),exit(0);
	for(int i=1;i<=top;i++)
		for(int j=st[i];j;j=nxt[j])
			printf("%d ",j);
	return 0;
}
```

---

## 作者：naroanah (赞：0)

注意到 $k$ 个特殊约束相当于把两个数捆绑在一起，判断矛盾使用带权并查集维护。打包好之后相当于进行了一个缩点，按照 $a$ 的限制建图，最后跑拓扑排序即可。

三种无解的情况 ：

- 维护 $k$ 个约束时出现矛盾，
- 建图时和已有约束矛盾，
- 拓扑排序时有环。

```cpp
#include<bits/stdc++.h>
#define rep(i, l, r) for(int i = (l); i <= (r); i++)
#define req(i, r, l) for(int i = (r); i >= (l); i--)
#define pii pair<int, int>
#define fi first
#define se second
#define all(x) begin(x), end(x)
using namespace std;
constexpr int N = 3e5 + 10, inf = 0x3f3f3f3f, INF = 0x7f7f7f7f; constexpr double eps = 1e-9;
int n, k; 
int a[N], in[N];
struct node {
    int id, f, dep, siz; //dep 表示权值，dep越大，说明它在当前节点内应该越靠前
}b[N];
pii tmp[N];
int find(int x) {
    if(b[x].f == x) return x;
    int p = b[x].f;
    b[x].f = find(b[x].f);
    b[x].dep += b[p].dep;
    return b[x].f;
}
bool mer(int x, int y) {
    int xx = find(x), yy = find(y);
    if(xx != yy) b[xx].f = yy, b[xx].dep = b[yy].siz, b[yy].siz += b[xx].siz;
    xx = find(x), yy = find(y);
    if(b[x].dep - b[y].dep != 1) return 0; //合并后权值差不为 1 说明出现矛盾，不满足相邻
    return 1;  
}
vector<int> ans, p[N], e[N];
void add(int u, int v) {e[u].emplace_back(v);}
void solve() {
    cin >> n >> k; 
    rep(i, 1, n) b[i].f = i, b[i].dep = 0, b[i].id = i, b[i].siz = 1;
    rep(i, 1, n) cin >> a[i]; 
    rep(i, 1, k) {
        int x, y; cin >> x >> y;
        if(!mer(x, y)) {cout << "0\n"; return;}
    }
    rep(i, 1, n) {
        if(!a[i]) continue;
        if(find(a[i]) == find(i)) {
            if(b[a[i]].dep <= b[i].dep) {cout << "0\n"; return;} // a[i] 已经排在 i 后面，说明无解
            continue;
        }
        add(find(a[i]), find(i)), in[find(i)]++;
    }

    rep(i, 1, n) tmp[i].fi = b[i].dep, tmp[i].se = i;
    sort(tmp + 1, tmp + n + 1, greater<pii>());
    rep(i, 1, n) p[find(tmp[i].se)].push_back(tmp[i].se);
    // 维护缩点后每个点内的排列顺序

    queue<int> q;
    rep(i, 1, n) {
        if(!in[i] && find(i) == i) {
            q.push(i);
        } 
    } 
    while(q.size()) {
        int x = q.front(); q.pop();
        if(p[x].size()) ans.push_back(x);
        for(int ed : e[x]) {
            if(!--in[ed]) q.push(ed);
        }
    }
    rep(i, 1, n) if(in[i]) {cout << "0\n"; return;} //成环无解
    for(int i : ans) for(int j : p[i]) cout << j << " ";
}
signed main() {
    ios :: sync_with_stdio(0); cin.tie(0); cout.tie(0);
    solve();
    return 0;
}
```


---

## 作者：Tx_Lcy (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1463E)

## 思路

简单构造，不过我的思路比较奇特。

考虑先把 $a_i \rightarrow i$ 的边建出来，然后考虑特殊对 $(u,v)$ 怎么建边。

显然 $u$ 在 $v$ 的前面是题目有解的必要条件，那么我们建 $u \rightarrow v$ 的边，如果此时存在环，必然无解。

我们称 $(x,y)$ 为特殊边仅当 $(x,y)$ 是特殊对。

若存在一条边 $(u,v)$，则我们称 $u$ 是 $v$ 的入点。

对于点 $v$ 的所有入边，若存在 $>1$ 条边 $(u,v)$ 是特殊边，无解。若存在一条边 $(u,v)$ 是特殊边，那么 $u$ 必定是 $v$ 的入点中在答案数组中最后一个出现的，我们把另外的入点向 $u$ 连一条边。

若此时出现了环，显然无解。

接下来考虑构造解。

我们把特殊边拉出来，剖分成一条条链，把一条链缩成一个点，然后再跑一遍拓扑排序即可，每次拓扑到一个点就把这个点代表的链输出，容易证明这个构造方法是正确的。

时间复杂度 $\mathcal O(n+k)$。

## 代码

```cpp
//A tree without skin will surely die.
//A man without face will be alive
#include<bits/stdc++.h>
using namespace std;
int const N=3e5+10;
int a[N],c[N],d[N],pp[N],co[N],rd[N],vis[N],ce[N];
vector<int>b[N],r[N],s[N],p[N];
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int n,m;cin>>n>>m;
    for (int i=1;i<=n;++i){
        cin>>a[i];
        b[a[i]].push_back(i);
        r[i].push_back(a[i]);
    }
    while (m--){
        int u,v;cin>>u>>v;
        if (c[u] || d[v]) return cout<<"0\n",0;
        c[u]=v,d[v]=u;
        b[u].push_back(v);
        r[v].push_back(u);
    }
    for (int i=1;i<=n;++i){
        if (!d[i]) continue;
        for (auto j:r[i])
            if (j^d[i])
                b[j].push_back(d[i]);
    }
    for (int i=1;i<=n;++i)
        for (auto j:b[i]) ++rd[j];
    int sum=0;queue<int>q;
    for (int i=1;i<=n;++i)
        if (!rd[i]) q.push(i),ce[i]=1;
    vector<int>vec;
    while (!q.empty()){
        int x=q.front();q.pop();
        ++sum;
        for (auto v:b[x])
            if (!--rd[v]) ce[v]=max(ce[v],ce[x]+1),q.push(v);
    }
    if (sum!=n) return cout<<"0\n",0;
    for (int i=1;i<=n;++i) s[ce[i]].push_back(i);
    int idx=0;
    for (int i=1;i<=n;++i)
        for (auto j:s[i]){
            if (vis[j]) continue;
            int k=j;co[k]=++idx,pp[idx]=k,vis[k]=1;
            while (c[k]) k=c[k],co[k]=idx,vis[k]=1;
        }
    memset(rd,0,sizeof(rd));
    for (int i=1;i<=n;++i)
        for (auto j:b[i])
            if (co[i]^co[j])
                p[co[i]].push_back(co[j]),++rd[co[j]];
    for (int i=1;i<=idx;++i) if (!rd[i]) q.push(i);
    while (!q.empty()){
        int x=q.front();q.pop();
        int i=pp[x];
        cout<<i<<' ';
        while (c[i]) i=c[i],cout<<i<<' ';
        for (auto v:p[x])
            if (!--rd[v]) q.push(v);
    }
    cout<<'\n';
    return 0;
}
```

---

