# [USACO25FEB] Vocabulary Quiz S

## 题目描述

Bessie 正在帮助 Elsie 准备她即将到来的词汇测验。要测验的单词将从 $M$ 个不同单词的词库中抽取，其中词库里没有一个单词是另一个单词的前缀。

当词库非空时，Bessie 将从词库中选择一个单词，将其从词库中移除，并从左到右逐个字符地读给 Elsie。Elsie 的任务是在她能够唯一确定该单词时告诉 Bessie，此后 Bessie 将停止朗读。

Bessie 已经决定按顺序 $w_1,w_2,\dots,w_M$ 朗读单词。如果 Elsie 尽可能快地回答，Bessie 将朗读每个单词的多少个字符？

这些单词以一种压缩格式给出。我们将首先定义 $N+1$（$1\le N\le 10^6$）个不同的单词，然后词库将由其中所有不作为另一个单词前缀的单词组成。这些单词定义如下：

- 初始时，第 $0$ 个单词为空字符串。
- 然后对于每一个 $1\le i\le N$，第 $i$ 个单词将等于第 $p_i$ 个单词在末尾加上一个额外的字符（$0\le p_i<i$）。字符的选择使得所有 $N+1$ 个单词各不相同。

## 说明/提示

样例 1 解释：

有 $6$ 个单词编号为 $0 \dots 5$。单词 $5$ 是唯一一个不是另一个单词的前缀的单词，因此它是词库中唯一的单词。一般地说，一旦库中仅剩下一个单词，Elsie 就不再需要任何字符以确定它。

样例 2 解释：

词库由单词 $2$，$3$ 和 $4$ 组成。

Elsie 需要两个字符来确定单词 $4$，因为单词 $3$ 和 $4$ 的第一个字符相同。

一旦 Bessie 朗读了单词 $3$ 的第一个字符，Elsie 就有了足够的字符来唯一确定它，因为单词 $4$ 已经被朗读。

- 测试点 $4\sim 5$：所有单词的长度均不超过 $20$。
- 测试点 $6\sim 10$：词库中所有单词的长度之和不超过 $10^7$。
- 测试点 $11\sim 18$：没有额外限制。

## 样例 #1

### 输入

```
5
0 1 2 3 4
5```

### 输出

```
0```

## 样例 #2

### 输入

```
4
0 0 1 1
4
3
2```

### 输出

```
2
1
0```

## 样例 #3

### 输入

```
4
0 0 1 1
2
3
4```

### 输出

```
1
2
0```

# 题解

## 作者：XGTD (赞：6)

# 题解：P11840 [USACO25FEB] Vocabulary Quiz S

~~不是，现在银组都简单成这样了？看看去年二月银组，难度可是直逼铂金呀。~~

[视频题解](https://www.bilibili.com/video/BV1n1P5eVEJo/?spm_id_from=333.1387.homepage.video_card.click&vd_source=e30c5bf3cf935b96ec8bab557be3afbd)。

介绍一种时间复杂度 $O(n)$，非常简单直白，码量小，且不需要 st 表，lca 的方法。

## Problem Statement

[P11840](https://www.luogu.com.cn/problem/P11840)。

## Solution

虽然题目感觉有些绕，但是很快就能发现其实这 $n - 1$ 个点构成的就是一颗以节点 0 为根的树，每个节点的父节点就是 $p_i$，而那 $m$ 个 "不作为另一个单词前缀的单词" 就是所有的叶子节点。

现在我们先不考虑读的顺序，就是假设目前还没有任何单词因为被读过而删除掉了。

我们发现对于一个叶节点 $i$，想要知道它的具体身份至少需要读到的字符数就是 $i$ 深度最深的，有超过一个儿子的祖先节点的深度。为什么呢？设这个节点是 $j$, 发现如果我们不把 $j$ 读完，我们并不知道这个单词到底是 $i$，还是 $j$ 的另一个儿子下的某一个叶子，因此至少需要把 $j$ 读完，且还要再多读一个字符。同时读 $dep_j + 1$ 也一定足够确定 $i$ 了（$dep_j$ 为 $j$ 节点的深度），因为我们知道从 $j$ 到 $i$ 没有任何其他节点有超过一个儿子了，因此 $j$ 下面唯一的叶节点就是 $i$。

现在发现删除节点也很简单了，直接将此节点的父亲出度减一就行了。如果发现一个节点的出度已经为零了（儿子被删完了）说明他下面没有叶节点了，就把它也删除就行了。

代码十分简洁好写。

## Code

赛时代码。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n, m, p[1000005], dep[1000005];
int cnt[1000005];
vector<int> e[1000005];
void pdfs(int x){
	dep[x] = dep[p[x]] + 1;
	if(!cnt[x])m++;
	for(auto i: e[x]){
		pdfs(i);
	}
}
int rdfs(int x){
	if(cnt[x]){
		//this point has other sons
		return dep[x] + 1;
	}
	if(x == 0){
		//last one
		return 0;
	}
	cnt[p[x]]--;//erase this node
	return rdfs(p[x]);
}
signed main(){
	cin>>n;
	for(int i = 1; i <= n; i++){
		cin>>p[i];
		cnt[p[i]]++;
		e[p[i]].push_back(i);
	}
	p[0] = 0;
	dep[0] = -1;
	//so when we do dep[i] = dep[p[i]] + 1 we have dep[0] = 0
	pdfs(0);
	//pre process depth and m
	for(int i = 1; i <= m; i++){
		int now;
		cin>>now;
		cout<<rdfs(now)<<endl;
		//reverse dfs
	}
	return 0;
}
```

## After thoughts

对于银组来说真的太简单了，顺着想一步一步非常直白就出来了，考场上花了大概 10 分钟。

---

## 作者：封禁用户 (赞：5)

[题目传送门](https://www.luogu.com.cn/problem/P11840)

赛时 AC 了 T2T3，就差 T1 没调出来（恼。

首先根据输入的 $p$ 计算每个单词的深度即长度，然后找出不是其他单词前缀的单词，就是由这些单词构成了词库。然后逆向处理，对于每个单词，从这个单词开始向上遍历前缀，找到第一个已经出现过的前缀记录深度，如果没找到就说明这个单词的前缀都没出现过，那么需要朗读的字符数为前一个单词需要朗读的字符数对应的前缀深度加 $1$。最后将数组反转，正向输出答案即可。

注意输入，因为没仔细读题卡了我很久。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;

int p[N], dep[N], lst[N], wsl[N], ans[N];
bool vis[N];

int main() {
  ios::sync_with_stdio(false);
  ios_base::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);

  int n;
  cin >> n;
  for (int i = 1; i <= n; i++)
    cin >> p[i];
  dep[0] = 0;
  for (int i = 1; i <= n; i++)
    dep[i] = dep[p[i]] + 1;
  fill(vis, vis + n + 1, true);
  for (int i = 1; i <= n; i++)
    vis[p[i]] = false;
  int m = 0;
  for (int i = 0; i <= n; i++)
    if (vis[i]) m++;
  for (int i = 0; i < m; i++)
    cin >> wsl[i];
  reverse(wsl, wsl + m);
  fill(lst, lst + n + 1, -1);
  for (int i = 0; i < m; i++) {
    int w = wsl[i], cur = w, md = 0;
    while (true) {
      if (lst[cur] != -1) {
        md = dep[cur];
        break;
      } if (cur == 0) break;
      cur = p[cur];
    } if (cur == 0 && lst[0] != -1) md = dep[0];
    ans[i] = (i == 0) ? 0 : (md + 1);
    cur = w;
    while (true) {
      if (lst[cur] == -1) {
        lst[cur] = i;
        if (cur == 0) break;
        cur = p[cur];
      } else break;
    }
  } reverse(ans, ans + m);
  for (int i = 0; i < m; i++)
    cout << ans[i] << "\n";
  return 0;
}
```

---

## 作者：沃若 (赞：4)

这道题的确第一眼会让人想到 Trie、Huffman、树剖之类的。但它只是银组 T2，显然不会是正解。

给出一个个人觉得很优美的在线**并查集**做法，甚至可以支持加点。

通过分析，我们发现要确定到某个叶子，说明从当前点到该叶子，一路上的节点都没有分叉（子节点数目小于等于 $1$）。**当前点的深度即为答案。**

这一点许多题解都已说明，但大部分人选择使用较复杂的数据结构来支持维护和查询。实际上，只需要对于每个子节点数目小于等于 $1$ 的点，将其在并查集中连向父亲。查询时找到在并查集中的根，输出其深度即可。对于删除叶子，沿到根的路径维护子节点数目即可（每个减一），直到遇到根节点或子节点数目大于 $1$ 的节点时停止，复杂度是均摊的。

时间复杂度：$O(n \log n)$ 或 $O(n + \alpha)$，取决于并查集写法。

空间复杂度：$O(n)$。

代码（C++17）：

```cpp
#include <bits/stdc++.h>

using namespace std;

int n;
int p[1000005];
int d[1000005];
int c[1000005];
int nxt[1000005];
int dsu[1000005];

int root(int x) {
	while (dsu[x] != x)
		x = dsu[x] = dsu[dsu[x]];
	return x;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> p[i], d[i] = d[p[i]] + 1, c[p[i]]++, nxt[p[i]] ^= i, dsu[i] = i;
	for (int i = 0; i < n; i++)
		if (c[i] == 1)
			dsu[nxt[i]] = i;
	for (int x; cin >> x; ) {
		cout << d[root(x)] << '\n';
		while (x != 0 && c[x] == 0)
			nxt[p[x]] ^= x, c[x = p[x]]--;
		if (c[x] == 1)
			dsu[nxt[x]] = x;
	}
	return 0;
}
```

---

## 作者：SunsetVoice (赞：3)

本题最大难点：读懂题意。

原问题等价于：

> 有一颗以 $0$ 为根的树，定义其叶子数为 $m$，每次询问从该叶子不断回溯至回溯到的第一个子节点数 $\ge 1$ ，输出其深度并删掉该叶子到该节点的所有点。

如果直接暴力向上跳维护当前每一个节点的子树节点数一条链就卡满了。这个时候硬维护相当于路径区间修改要写树剖~~所以题解区真有人写啊~~很麻烦，我们考虑让每条边只访问一次，直接抛弃子树节点数处理子节点数。只有当这个节点修改后子节点数 $\le 1$ 才向上回溯，这就保证了时间复杂度的正确性。

笑点解析：写完一二剩三分钟来不及写暴力差 $33$ 分金遗憾离场。


```cpp
#include<bits/stdc++.h>
#define int long long
#define endl "\n"
using namespace std;
int n,m = 0,f[1000001] = {0},dep[1000001] = {0},val[1000001] = {0};
vector<int>e[1000001];
void dfs(int x,int fa){
	f[x] = fa;
	int s = 0;
	for(int v:e[x]){
		if(fa==v)continue;
		dep[v] = dep[x]+1;
		dfs(v,x);
		s++;
	}
	val[x] = s;
	if(val[x]==0)val[x] = 1;
	if(s==0)m++;
	return;
}
int dans = 0;
void cl(int x){
	if(x==-1){
		return;
	}
	val[x]--;
	if(val[x]==0){
		dans = dep[x];
		cl(f[x]);
	}
	return;
}
signed main(){
	cin>>n;
	for(int i = 1;i<=n;i++){
		int hjx;
		cin>>hjx;
		e[hjx].push_back(i);
		e[i].push_back(hjx);
	}
	dfs(0,-1);
	for(int i = 1;i<=m;i++){
		int pl;
		cin>>pl;
		dans = dep[pl];
		cl(pl);
		cout<<dans<<endl;
	}
	return 0;
}

```

---

## 作者：Phoenix_2010 (赞：2)

赛时做法，$O(n\log^2n)$
# 题目大意
这个压缩形式看着比较抽象，但是手玩一下你就会发现它给你的就是一颗字典树，每个节点就代表一个单词（因为单词互不相同）。$p_i$ 就是 $i$ 的父亲。然后词库中（不作为另一个单词前缀）的词就是所有叶子结点。
# 主要思路
先把这棵树建出来，然后考虑什么时候可以确定一个单词。如果一个节点子树中只有一个词没读，那显然是可以直接确定的。

设节点 $i$ 的子树中有 $w_i$ 个词还没读过。

初始时，$w$ 就是子树中叶节点的数量，然后每读完一个词就把包含这个叶子的节点的 $w$ 都减一，也就是把这个节点到根路径上的所有点的 $w$ 都减一。

所以在读每个单词时，找到根到叶子的路径上深度最浅的 $w=1$ 的节点，这就是读单词时第一个可以确定单词的点，输出其深度即可（这里根节点深度是 $0$）。

不懂的话就画几颗树然后手玩几次就知道了。

接下来就是无脑套数据结构。对于修改操作，可以树剖+线段树维护；对于查询操作，我用的是倍增（应该有更好的方法，但考场上懒得想了），具体可以参考代码。

# 代码

```cpp
#include<bits/stdc++.h>
#define mid (l+r>>1)
using namespace std;
const int N=1e6+5;
struct{int val,tag;}t[4*N];
int T,n,f[N][21],dep[N],sz[N],hson[N],dfn[N],top[N],w[N],tmp[N];vector<int> a[N];long long ans;
//树剖和线段树板子
inline void dfs1(int u,int fa){sz[u]=1;for(auto v:a[u]) if(v!=fa) f[v][0]=u,dep[v]=dep[u]+1,dfs1(v,u),sz[u]+=sz[v],sz[hson[u]]<sz[v]&&(hson[u]=v);}
inline void dfs2(int u,int t)
{
    dfn[u]=++T;top[u]=t;
    if(!hson[u]){w[u]=1;return;}//没有重子节点证明这是叶子
    dfs2(hson[u],t);w[u]+=w[hson[u]];
    for(auto v:a[u]) if(v!=f[u][0]&&v!=hson[u]) dfs2(v,v),w[u]+=w[v];
}
inline void pushdown(int p){if(t[p].tag) t[p<<1].tag+=t[p].tag,t[p<<1|1].tag+=t[p].tag,t[p].tag=0;}
inline void build(int p,int l,int r)
{
    if(l==r){t[p].val=w[l];return;}
    build(p<<1,l,mid);build(p<<1|1,mid+1,r);
}
inline void modify(int p,int l,int r,int ql,int qr,int x)
{
    if(l==ql&&r==qr){t[p].tag+=x;return;}
    pushdown(p);
    if(qr<=mid) modify(p<<1,l,mid,ql,qr,x);
    else if(ql>mid) modify(p<<1|1,mid+1,r,ql,qr,x);
    else modify(p<<1,l,mid,ql,mid,x),modify(p<<1|1,mid+1,r,mid+1,qr,x);
}
inline int query(int p,int l,int r,int qi)
{
    if(l==r) return t[p].val+t[p].tag;
    pushdown(p);
    if(qi<=mid) return query(p<<1,l,mid,qi);
    else return query(p<<1|1,mid+1,r,qi);
}
inline void upd(int x)
{
    while(top[x]!=1)
    {
        modify(1,1,n,dfn[top[x]],dfn[x],-1);
        x=f[top[x]][0];
    }
    modify(1,1,n,1,dfn[x],-1);
}
int main()
{
    ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    f[1][0]=1;
    cin>>n;
    for(int i=1,x;i<=n;i++) cin>>x,a[x+1].push_back(i+1);n++;//注意节点从0开始编号
    dfs1(1,0);dfs2(1,1);memcpy(tmp,w,sizeof(tmp));for(int i=1;i<=n;i++) w[dfn[i]]=tmp[i];//记得重新编号
    for(int j=1;j<=20;j++) for(int i=1;i<=n;i++) f[i][j]=f[f[i][j-1]][j-1];
    build(1,1,n);
    int x;
    while(cin>>x)
    {
        x++;
        int tmp=x;
        for(int j=20;j>=0;j--) if(query(1,1,n,dfn[f[x][j]])==1) x=f[x][j];//与lca写法基本相同，会跳到第一个w!=1的点下方，也就是最浅的w==1的点
        cout<<dep[x]<<"\n";
        upd(tmp);
    }
    return 0;
}
```

~~码风不好，不喜勿喷~~

---

## 作者：littlebug (赞：2)

B<<<<<A。

第一次场切对我来说比较复杂的 ds，体会到 ds 的可爱了。但是据说我们不能只在场切 ds 的时候说 ds 可爱。

## Solution

用的树剖 + 线段树做的，可能麻烦了，不过这个思路比较好想。

读懂题意之后就一眼了，但是读懂题意是本题中最困难的部分。

实际上就是给一颗树，点 $i$ 的父亲是 $p_i$，$m$ 就是这颗树的叶子节点个数，$w_i$ 就是叶子结点。当然也可以从 trie 的角度理解。

然后每次操作一个叶子节点，求一下这个叶子节点的**最近的**、**有 $>1$ 个儿子的**祖先，其深度 $+1$ 即为答案，然后再把这个叶子节点直到连向它那个祖先的这条链删掉。

所以要动态维护每个叶子节点的满足上面条件的最大深度，想到可以树剖套线段树做。线段树维护的是区间内对于有 $>1$ 个儿子的节点的深度最大值，支持区间查询和单点修改，就是线段树板子了，其中把有 $\le 1$ 个儿子的节点的深度设为 $- \infin$ 即可。剩下的就是树剖板子了，点 $u$ 依次往上跳重链即可。

---

## Code

为了方便，我代码里根节点是 $1$ 而不是题目中要求的 $0$，其余节点编号以此类推。

```cpp
int n,a[MAXN],m,w[MAXN];
vector <int> p[MAXN];

int dep[MAXN],fa[MAXN],siz[MAXN],son[MAXN];
int top[MAXN],id[MAXN],cnt=0;
int d[MAXN],c[MAXN];

il void dfs1(int u,int ufa)
{
	dep[u]=(ufa==0 ? 0ll : dep[ufa]+1),fa[u]=ufa,siz[u]=1;
	int mx=0;
	for(auto i:p[u])
	{
		if(i==ufa) continue;
		dfs1(i,u);
		siz[u]+=siz[i];
		if(siz[i]>mx) mx=siz[i],son[u]=i;
	}
}

il void dfs2(int u,int utop)
{
	id[u]=++cnt;
	top[u]=utop;
	if(p[u].size()==1 && p[u][0]==fa[u]) return;
	dfs2(son[u],utop);
	for(auto i:p[u])
	{
		if(i==fa[u]) continue;
		if(i!=son[u]) dfs2(i,i);
	}
}

il void init()
{
	dfs1(1,0),dfs2(1,1);
}

struct node{int mx,id;};

class __segment_tree
{
#define lc v[pos<<1]
#define rc v[pos<<1|1]
#define lcp pos<<1
#define rcp pos<<1|1
	
private:
	
	int *a;
	node v[MAXN<<2];
	int k,lt,rt;
	
	il void pushup(int pos)
	{
		lc.mx>rc.mx ? v[pos]=lc : v[pos]=rc;
	}
	
	il void build(int l,int r,int pos)
	{
		if(l==r) return v[pos]={a[l],l},void();
		int mid=l+r>>1;
		build(l,mid,lcp),build(mid+1,r,rcp);
		pushup(pos);
	}
	
	il void update(int l,int r,int pos)
	{
		if(l>=lt && r<=rt) return v[pos].mx=k,void();
		int mid=l+r>>1;
		mid>=lt && (update(l,mid,lcp),1);
		mid+1<=rt && (update(mid+1,r,rcp),1);
		pushup(pos);
	}
	
	il node query(int l,int r,int pos)
	{
		if(l>=lt && r<=rt) return v[pos];
		int mid=l+r>>1; node now,res={-inf,-1};
		mid>=lt && (now=query(l,mid,lcp),now.mx>res.mx && (res=now,1));
		mid+1<=rt && (now=query(mid+1,r,rcp),now.mx>res.mx && (res=now,1));
		return res;
	}
	
public:
	il void bui() {build(1,n,1);}
	il void bui(int *aa) {a=aa,build(1,n,1);}
	il void upd(int l,int _k) {k=_k,lt=l,rt=l; update(1,n,1);}
	il node q(int l,int r) {l>r && (swap(l,r),1); lt=l,rt=r; return query(1,n,1);}
	
#undef lc
#undef rc
#undef lcp
#undef rcp
} tr;

il int opt(int u)
{
	node now;
	while(top[u]!=0)
	{
		now=tr.q(id[top[u]],id[u]);
		if(now.mx>=0)
		{
			--c[now.id];
			if(c[now.id]==1) tr.upd(now.id,-inf);
			return now.mx+1;
		}
		
		u=fa[top[u]];
	}
	
	return 0;
}

signed main()
{
	cin>>n; rep(i,2,n+1) cin>>a[i],++a[i],p[a[i]].pb(i),p[i].pb(a[i]);
	++n;
	while(cin>>w[++m]) ++w[m];
	--m;
	
	if(m==1) return cout<<0,0;
	
	init();
	rep(i,1,n) d[id[i]]=((p[i].size()==1 || (p[i].size()==2 && i!=1)) ? -inf : dep[i]),c[id[i]]=p[i].size()-(i!=1);
	tr.bui(d);
	
	rep(i,1,m-1) write(opt(w[i]),'\n');
	write(0ll);
	
	return 0;
}
```

---

华风夏韵，洛水天依！

---

## 作者：Colinxu2020 (赞：2)

注意到单词具体是什么是不重要的，又因为 $p_i \lt i$，有 $n+1$ 个词，$n$ 个前缀关系，考虑建树，给 $p_i$ 到 $i$ 连一条边，显然测验表就是这个树的所有叶子节点，定义一个点是 solo 的，当且仅当这个点的子树中有且仅有一个叶子，考察对于每个叶子节点你需要给多少个字符，显然对于祖先中所有 solo 的点都不需要询问（因为不需要问他们就能确定），所以答案就是深度减去祖先中 solo 点的数量。

考虑如何处理祖先中 solo 点的数量，显然，若一个点本身不是 solo 的，则其所有祖先都不是 solo 的，因为他们的子树区间严格比当前点大，所以只需要不断跳父亲，直到跳到一个非 solo 的点，再考虑排列的性质，也就是问完一个单词 Bessie 就可以确定这个单词绝不会再出现了，所以在树上删去这个叶子，考察删去这个叶子对祖先点的变化，为了方便维护给每个点计算一个子树中的叶子数量，显然删去后上面找出的 solo 点都没用了，但也可以不管他们，因为不会再被引用，找到深度最浅的 solo 点的父亲，给他的儿子计数 $-1$ 即可。

讨论一下复杂度，因为每个点最多被子树中的一个点当作一次 solo 点，而一旦遇到非 solo 点我们就立即跳出了，所以总和复杂度为 $O(n)$。

```cpp
#include<iostream>
#include<vector>
using namespace std;

const int maxn=1e6+10;
int n,fa[maxn],wi[maxn],leafcnt,leaf[maxn],dep[maxn],sz[maxn];
vector<int> grp[maxn];

void dfs(int cur, int pa){
    bool flag=false; dep[cur]=dep[pa]+1;
    for(auto x:grp[cur])dfs(x,cur),flag=true;
    if(!flag)leafcnt++,leaf[cur]=true;
    sz[cur]=grp[cur].size();
}
bool issolo(int x){
    return sz[x]<=1;
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++)cin>>fa[i],grp[fa[i]].push_back(i);
    dfs(0,0);
    for(int id=1;id<=leafcnt;id++){
        int x; cin>>x;
        int cur=fa[x],len=0;
        while(cur&&issolo(cur))cur=fa[cur],len++;
        if(issolo(0)&&!cur)len++;
        sz[cur]--;
        cout<<dep[x]-len-1<<endl;
    }
    
}
```

---

## 作者：Chenyichen0420 (赞：2)

## 思路分析

正难则反，显然加点要比删点容易很多。

我们将这些点倒着加进去，让这个点一直向上找，并标记当前点，直到找到一个点，使其父节点已经被标记过。答案就是这个点的深度。

特别的，我们认为 $0$ 点的深度为 $0$，一定要特殊处理第一次的询问。

为什么正确呢？只有没查询过的，也就是没删的才会对他造成影响。而第一次确定就是他最后一次不走上被标记的部分。那些部分就是已经有其他的单词在上面的。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n, a[1000005], d[1000005], p, ans;
bool vis[1000005]; stack<int> av, va;
inline int dfs(int p) {
	vis[p] = 1; if (!p) return ans = d[p] = 0;
	if (vis[a[p]]) return ans = d[p] = d[a[p]] + 1;
	dfs(a[p]); return d[p] = d[a[p]] + 1;
}
int main() {
	ios::sync_with_stdio(0); cin >> n; vis[0] = 1;
	for (int i = 1; i <= n; ++i) cin >> a[i];
	while (cin >> p) av.emplace(p);
	dfs(av.top()); av.pop(); va.emplace(0);
	while (av.size())
		dfs(av.top()), av.pop(),
		va.emplace(ans);
	while (va.size())
		cout << va.top() << endl, va.pop();
}
```

---

## 作者：xukehg (赞：1)

神秘做法。

显然可以建出一棵字典树，问题转变为，依次询问每一个标记点 $i$，求最深度最小的 $v$ 满足 $v$ 是 $i$ 的父亲且满足 $v$ 子树内有且仅有一个标记点。操作后会撤销这个点的标记。

考虑让一个点往上跳的过程，若若干个点跳到了一起，只有出现时间最晚的点才能往上跳，其余的点答案就确定了。因此每个结点最多只能留一个往上跳的点。模拟即可。

[记录。](https://www.luogu.com.cn/record/205888543)

---

## 作者：MoonCake2011 (赞：1)

可爱的简单题。

题意就是给你一棵以 $0$ 为根的树。

然后这棵树有 $m$ 个叶子节点，最开始除了叶子节点其它权值是 $0$，叶子最初节点权值为 $1$。

每次操作会先查询对于一个权值为 $1$ 的叶子节点，寻找最浅的一个节点使得它的子树权值总和为 $1$，并且那个叶子节点必须在那个节点的子树内。

最后将那个叶子节点权值改为 $0$。

题意理清楚了，就直接做完了呀。

发现对于一个子树，它的 dfs 序编号是连续的一个区间。

又发现查询答案以深度有单调性，于是可以尝试倍增 LCA 加树状数组维护。

时间复杂度 $O(n\log^2 n)$。

主要是树状数组跑的飞快加上倍增常数不大再加上这是两秒，就过了。

蛮可爱的一道板子题呢。

听机房大佬 chenyichen0420 说，可以倒序处理线性做，这里太菜了不会就不讲了。

---

## 作者：hinin (赞：0)

[更好的阅读体验，包括银组前二](https://www.cnblogs.com/hinin/articles/18731858)。

# T2：Vocabulary Quiz

### 题意

概括一下（精炼过头了）：

在一棵树上，每一个节点（除了 0 号节点）都有自己的父亲。从 0 开始遍历，至少向下遍历到哪一个点此时这个点的才能确定唯一的我们所需要的叶子节点。输出这个点的深度。

### 思路

DFS 和 LCA 中的部分思想。

DFS 求取对构建好的树进行深度优先搜索，主要目的是计算每个节点的深度 `d` 和以该节点为根的子树中叶子节点的数量 `l`。

读取需要识别的单词顺序。对于每个单词，我们从其父节点开始处理。如果该父节点的子树中还有其他未识别的叶子节点，那么需要读取到该父节点的下一层，即输出 $d_x + 1$；如果该父节点的子树中只剩下当前要识别的叶子节点，我们需要向上回溯，更新其父节点的 $l$ 值，直到找到一个父节点，其 $l$ 值不为 $0$，然后输出该父节点的深度 $d_x$。

### 代码

``` cpp
// By Hinin（Neko233）
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast", "-funroll-all-loops")
#define ll long long
#define pii pair<int, int>

#define y1 kairiki
#define x first
#define y second

#define repeat(x, a, b) for(int x = a; x <= b; x ++)
#define rpless(x, a, b) for(int x = a; x >= b; x --)
#define repeatl(x, a, b) for(int x = a; x < b; x ++)
#define rplessr(x, a, b) for(int x = a; x > b; x --)

using namespace std;

const int N = 1e6 + 1; 
vector<int> g[N]; 
int n, x, d[N], l[N], bl[N], fa[N]; 

void dfs(int x) 
{
	if(g[x].size() == 0) {
		l[x] = 1; 
		return ; 
	}
	
	for(int i : g[x]) {
		d[i] = d[x] + 1; 
		
		dfs(i); 
		l[x] += l[i]; 
	}
	
	return ; 
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> n; 
	repeat(i, 1, n) {
		cin >> x; 
		
		fa[i] = x; 
		g[x].emplace_back(i); 
	}
	
	dfs(0); 
	
	repeat(i, 0, n) { bl[i] = l[i]; }
	
	while(cin >> x) {
		x = fa[x]; 
		
		if(-- l[x]) { cout << d[x] + 1 << endl;  }
		else {
			while(x && (l[fa[x]] -= bl[x]) == 0)
			{ x = fa[x]; }
			
			cout << d[x] << endl;
		}
	}
	
	return 0;
}
```

- 时间复杂度：$O(N + M * N)$。
- 空间复杂度：主要用于存储树的邻接表和节点信息，空间复杂度为 $O(N)$。

注意：不要忘了关掉我的加速，否则会 CE。

---

## 作者：iced_tea543 (赞：0)

## 引言：
我们来看看 2 月银组的第二题。我在这里提供一个比较直接的思路。

本题题目令人费解。不过读懂之后会发现就是道非常普通的考树的题目。

## 题解：
最朴素的想法就是，我们可以直接dfs初始化统计每一个结点的子节点里面叶子结点的数量，记作 $val$ 数组，然后每一次从叶子结点往上遍历到根结点，每次只要碰到第一个 $val$ 值大于1的说明其有多个叶子结点，也就是有歧义，那么直接输出这个结点的深度加 $1$ 即可，顺便把沿途的结点的 $val$ 值减一。

但是这样效率太低，每次都要遍历到根节点，有太多重复。观察发现，在找到第一个分叉点时，完全没有必要继续向上查找，因为上面的结点压根不关心你这个结点的具体的值是多少——只要你这条分叉还有值，对于上面的结点来说，你们两共同连接的那条主干就必定是有歧义的，最起码必须从主干遍历到它自己的那条路上，才能找到唯一独特的单词前缀，否则在主干上就无法和你那条路还存在的单词区分开。

所以我们一旦碰到我们需要的第一个 $val$ 大于 $1$ 的结点，就可以不继续往上遍历，而是在这个点的“账本”加上 $1$，表示我下面以及删掉了多少个点并带上我自己这个刚删掉的点，告诉后面那个还没有遍历到这个点的结点，往上遍历的时候记得把这个结点的“欠账”带上。

这样，对于每一个结点，把从下往上把沿途的每个结点的欠账全部带上，加上这个点本来就有的欠账，用这个结点的 $val$ 减去，就是这个点下面目前实际的还存在没被删掉的叶子结点数。

理论上的复杂度——因为每个结点只过了一遍——应该是 $O(n)$。

## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int fa[(int)1e6 + 5], val[(int)1e6 + 5], acc[(int)1e6 + 5], dep[(int)1e6 + 5];
vector<int> chd[(int)1e6 + 5];

int dfs(int n, int depth) {
	dep[n] = depth;
	if (chd[n].empty())
		return val[n] = 1;
	for (auto i : chd[n])
		val[n] += dfs(i, depth + 1);
	return val[n];
}

void rdfs(int n, int account) {
	if (fa[n] == -1 and val[n] - acc[n] - account == 1)
		cout << 0;
	else if (val[n] - acc[n] - account > 1 or fa[n] == -1)
		acc[n] += account + 1, cout << dep[n] + 1 << endl;
	else
		rdfs(fa[n], account + acc[n]);
}

int main() {
	int n;
	cin >> n;
	fa[0] = -1;
	for (int i = 1; i <= n; i++)
		cin >> fa[i], chd[fa[i]].push_back(i);
	dfs(0, 0);
	int w;
	while (cin >> w) {
		rdfs(w, 0);
	}
}
```

---

## 作者：ThisIsLu (赞：0)

简单题。

首先显然的是我们不用管单词具体是什么，因为两两都不互为前缀，这使得如果我们对于所有整数 $1 \le i \le n$ 在 $i$ 和 $p_i$ 之间建一条边，这实际上便是这些单词的字典树。

然后考虑依次朗读每个单词，发现这本质上是在算最近的祖先使得该祖先的子树内有两个还未被朗读的单词。

朗读一个单词还要删除它，所以我们需要一种数据结构维护。

一个简单的做法是倍增维护出 $2^k$ 级祖先然后用树状数组维护删除。

code:

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
const int N=1e6;
int fa[N+5][20],sz[N+5],dfn[N+5],tot;
int c[N+5],dep[N+5];
int lowbit(int x){return x&(-x);}
void update(int x,int k){
    while(x<=n){
        c[x]+=k;
        x+=lowbit(x);
    }
}
int query(int x){
    int res=0;
    while(x){
        res+=c[x];
        x-=lowbit(x);
    }
    return res;
}
int query(int l,int r){
    return query(r)-query(l-1);
}
vector<int> sons[N+5];
void dfs(int u){
    dep[u]=dep[fa[u][0]]+1;
    dfn[u]=++tot;
    sz[u]=1;
    for(int i=1;i<20;i++){
        fa[u][i]=fa[fa[u][i-1]][i-1];
    }
    if(sons[u].empty()){
        update(dfn[u],1);
        m++;
    }
    for(int v:sons[u]){
        dfs(v);
        sz[u]+=sz[v];
    }
}
signed main(){
    cin>>n;
    n++;
    for(int i=2;i<=n;i++){
        cin>>fa[i][0];
        fa[i][0]++;
        sons[fa[i][0]].emplace_back(i);
    }
    dfs(1);
    for(int oi=1;oi<=m;oi++){
        int ci;
        cin>>ci;
        ci++;
        update(dfn[ci],-1);
        for(int i=19;i>=0;i--){
            if(fa[ci][i]&&query(dfn[fa[ci][i]],dfn[fa[ci][i]]+sz[fa[ci][i]]-1)<=0){
                ci=fa[ci][i];
            }
        }
        cout<<dep[ci]-1<<"\n";
    }
    return 0;
}
```

---

## 作者：ZLCT (赞：0)

# [USACO25FEB] Vocabulary Quiz S
## 题意转化
我们注意到题目的意思可以转化为给了一个有根树，设叶子结点点权为 $1$，其余节点点权为 $0$，设 $val_u$ 表示 $u$ 子树点权和。每次相当于求根到一个叶子的路径上最浅节点 $v$ 满足 $val_v=1$。
## solution
我们看一下大致需要维护的信息，只有链修改和链查询，那么我们就可以用 LCT 去维护。\
具体地，我们维护 $val_u$ 表示子树点权和；$minn_u$ 表示当前 splay 树中点 $u$ 及子树最小的 $val$；$siz_u$ 表示当前 splay 树中点 $u$ 及子树的节点个数（为了求深度用）。\
其中维护就和正常 LCT 一样维护。并且由于我们每去掉一个单词只对一条链的 $val$ 产生影响，所以我们甚至不需要维护虚儿子的任何信息。\
那如何找到答案呢？\
我们考虑把根到当前叶子的路径 split 出来，并注意以原根为 makeroot 的根。\
这样我们问题就变成了在这棵二叉搜索树上找到中序遍历最小的点 $u$ 满足 $\forall v\le u,val_v=1$。注意这里的 $\le$ 定义为中序遍历的顺序的比较。\
那么这就是一个平衡树二分的裸题了。\
我们每次判断如果左儿子的 $minn=1$，就跳到左儿子，否则如果当前节点的 $val=1$ 答案就是当前节点，否则跳到右儿子。
## code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e6+666;
const int inf=1e18+7;
int n,pa[N];
struct node{
    int son[2],fa;
    bool tag;
    int tag2;
    int minn,siz,val;
}tr[N];
bool notroot(int x){
    return tr[tr[x].fa].son[0]==x||tr[tr[x].fa].son[1]==x;
}
void pushup(int x){
    if(!x)return;
    tr[x].siz=tr[tr[x].son[0]].siz+tr[tr[x].son[1]].siz+1;
    tr[x].minn=min({tr[tr[x].son[0]].minn,tr[tr[x].son[1]].minn,tr[x].val});
}
void pushdown(int x){
    if(tr[x].tag){
        swap(tr[x].son[0],tr[x].son[1]);
        tr[tr[x].son[0]].tag^=1;
        tr[tr[x].son[1]].tag^=1;
        tr[x].tag=0;
    }
    if(tr[x].tag2!=0){
        tr[tr[x].son[0]].tag2+=tr[x].tag2;
        tr[tr[x].son[1]].tag2+=tr[x].tag2;
        tr[tr[x].son[0]].minn+=tr[x].tag2;
        tr[tr[x].son[1]].minn+=tr[x].tag2;
        tr[tr[x].son[0]].val+=tr[x].tag2;
        tr[tr[x].son[1]].val+=tr[x].tag2;
        tr[x].tag2=0;
    }
}
void pushall(int x){
    if(notroot(x))pushall(tr[x].fa);
    pushdown(x);
}
void rotate(int x){
    int y=tr[x].fa,z=tr[y].fa;
    int k=tr[y].son[1]==x;
    if(notroot(y)){
        tr[z].son[tr[z].son[1]==y]=x;
    }
    tr[x].fa=z;
    tr[y].son[k]=tr[x].son[k^1];
    tr[tr[x].son[k^1]].fa=y;
    tr[x].son[k^1]=y;
    tr[y].fa=x;
    pushup(y);
    pushup(x);
}
void splay(int x){
    pushall(x);
    while(notroot(x)){
        int y=tr[x].fa,z=tr[y].fa;
        if(notroot(y))rotate((tr[z].son[1]==y)^(tr[y].son[1]==x)?x:y);
        rotate(x);
    }
}
void access(int x){
    for(int y=0;x;x=tr[x].fa){
        splay(x);
        tr[x].son[1]=y;
        pushup(x);
        y=x;
    }
}
void makeroot(int x){
    access(x);
    splay(x);
    tr[x].tag^=1;
}
void split(int x,int y){
    makeroot(x);
    access(y);
    splay(y);
}
void dfs(int x){
    if(tr[x].son[0])dfs(tr[x].son[0]);
    cout<<x<<" ";
    if(tr[x].son[1])dfs(tr[x].son[1]);
}
int deg[N],m;
void GET(int p){
    split(n+1,p);
    int x=p,sz=-1;
    while(1){
        pushdown(x);
        if(tr[tr[x].son[0]].minn==1){
            x=tr[x].son[0];
        }else if(tr[x].val==1){
//            cout<<x<<":";
            cout<<tr[tr[x].son[0]].siz+1+sz<<"\n";
            break;
        }else{
            sz+=tr[tr[x].son[0]].siz+1;
            x=tr[x].son[1];
        }
    }
    tr[p].tag2--;tr[p].val--;tr[p].minn--;
}
void solve(){
    cin>>n;
    for(int i=1;i<=n;++i){
        cin>>pa[i];if(pa[i]==0)pa[i]=n+1;
        deg[pa[i]]++;
    }
    queue<int>q;
    for(int i=1;i<=n;++i){
        if(!deg[i]){tr[i].val=1;q.push(i);m++;}
    }
    while(!q.empty()){
        int u=q.front();q.pop();
        if(u==n+1)continue;
        tr[pa[u]].val+=tr[u].val;deg[pa[u]]--;
        if(!deg[pa[u]])q.push(pa[u]);
    }
    for(int i=1;i<=n;++i){
        tr[i].fa=pa[i];pushup(i);
    }
    pushup(n+1);
    for(int i=1;i<=m;++i){
        int x;cin>>x;
        GET(x);
    }
    return;
}
signed main(){
    tr[0].minn=inf;
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int T=1;
    while(T--)solve();
    return 0;
}
```

---

