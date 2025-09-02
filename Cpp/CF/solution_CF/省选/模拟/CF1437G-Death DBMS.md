# Death DBMS

## 题目描述

## 题目背景

（下面有简化描述，不想看长背景就直接去下面）

(与题意无关)简单来说，“死亡笔记”是一个能把名字被写在笔记上的人杀死的笔记。

用这个笔记杀人很容易，但没法用它记录你计划杀死但尚未杀死的人（写上人名就直接杀了）。所以你决定开发一个“死亡数据管理系统”-一个能方便地提供潜在受害者信息的系统。下面为你描述这个系统。

一个受害者由两个信息描述：仅由小写英文字母组成的姓名（不保证唯一）和受怀疑程度。

最开始，系统的使用者输入n个受害者的姓名，他们的受怀疑程度最初都为0。

然后使用者会进行两种操作：

- 1 i x 将第i个受害者的受怀疑程度改为x
- 2 q 给出一个字符串q，询问所有姓名是q的子串的受害者的受怀疑程度的最大值

**注意**，这个系统不负责杀人，因此在整个过程中受害者都是固定的

## 简化描述

给出$n,m$，然后给出n个字符串，每个字符串都有一个权值，最初权值都为0

然后有m个操作，操作有两种类型

- 1 i x 将第i个字符串的权值修改为x

- 2 q 给出一个字符串q，求所有**是q的子串**的字符串的**权值的最大值**

## 说明/提示

$1\le n,m\le 3\times10^5$

$\sum length(s_i)\le3\times 10^5$，即输入的受害者姓名串s的长度和不超过$3\times10^5$

操作1中$1\le i\le n \space,\space 0\le x \le 10^9$

操作2中$\sum length(q)\le3\times 10^5$，即询问串长度和不超过$3\times 10^5$

## 样例 #1

### 输入

```
5 8
kurou
takuo
takeshi
naomi
shingo
2 nakiraomi
2 abanaomicaba
1 3 943
2 takuotakeshishingo
1 5 135832
2 shingotakeshi
1 5 0
2 shingotakeshi```

### 输出

```
-1
0
943
135832
943```

## 样例 #2

### 输入

```
6 15
a
ab
ba
b
a
ba
2 aa
1 4 4
2 bbb
1 2 1
1 2 18
2 b
2 c
1 6 10
2 aba
2 abbbba
1 2 12
2 bbaaab
1 1 11
1 5 5
2 baa```

### 输出

```
0
4
4
-1
18
18
12
11```

# 题解

## 作者：Alex_Wei (赞：19)

Upd on 2022.4.8：重写题解，补充了线性对数的做法。

Upd on 2022.9.3：修改一处笔误。

> *XIV. [CF1437G Death DBMS](https://www.luogu.com.cn/problem/CF1437G)
>
> [AC 自动机](https://www.cnblogs.com/alex-wei/p/Common_String_Theory_Theory_automaton_related.html)。

刻画子串结构最方便的工具就是后缀字符串结构。考虑对 $s_i$ 建出 ACAM。

我们知道，若 $i$ 是 $j$ 的祖先，则 $i$ 对应的字符串 $t_i$ 是 $t_j$ 的 border。并且，若将字符串 $q$ 放在 $s_i$ 的 ACAM 上面跑，那么跑到的每个位置就依次是 $q$ 的对应前缀的最长的与某个单词的前缀匹配的后缀。

因此，判断 $s_i$ 是否是 $q$ 的子串，只需要判断将 $q$ 按字符加入自动机后依次得到的状态 $Q_j(1\leq j\leq |q|)$ 经过了 $s_i$ 在 fail 树上的子树。或者说，为了求出答案，我们只需查询每个 $Q_j$ 在 fail 树上到根的路径上所有表示某个单词 $s_i$ 的节点的对应单词的权值的最大值。树剖 + 线段树维护。

注意，由于字符串可能相等，所以一个节点可能表示了多个单词。对于这种情况，用 multiset 维护该节点表示单词的权值最大值即可。

如果不想写树剖，也可以直接转子树添加权值 + 单点查询，这部分用 dfs 序拍平转化成区间加入 / 删除一个数，单点查询被加入的所有数的最大值。线段树 + multiset 维护即可（注意，子树操作弱于区间操作，因为前者可归约到后者，但后者不可归约至前者）。[代码](https://codeforces.com/contest/1437/submission/152990355)。

上面两种方法都是线性对数平方的。接下来介绍线性对数的魔法。

在线是没啥前途的，考虑离线把问题搞简单一点。离线有一个好处，那就是我们知道了每个节点对应权值被修改的时刻。从而得到对于每个节点 $i$，存在若干时刻的连续段 $[l_j, r_j, v_j]$ 使得在 $l_j\sim r_j$ 时刻，$i$ **对应的单词** 的权值为 $v_j$。如果一个节点没有表示单词，它对答案显然不会有任何贡献。这样一来，一次询问 $q$ 就转化为所有 $Q_j$ 到根的路径上所有单词节点 $i$ 的 $v_k$ 的最大值，其中查询时刻 $t\in [l_k, r_k]$。

子树限制和区间限制的不同点在于，前者拍平转化为后者时，区间满足非常好的性质：对于任意两个区间，**只有包含或相离** 的关系，不会相交。尽管经过离线后，所有矩形加数在所有单点查询之前，但仍然难以做到单 $\log$（甚至不可能）。

这里有一个非常精彩且适用范围非常广的技巧，那就是 **通过 dfs 解除子树限制**。具体来说，我们按照 dfs 的顺序考虑每个单词节点 $i$ 的连续段 $[l_j, r_j, v_j]$ 的贡献，在进入一个节点时，将贡献加上，离开时撤销。这样一来子树限制就没了，只剩下时间限制 $[l_j, r_j]$。这是容易考虑的，用线段树维护时间轴上的区间 checkmax 和单点查询。撤销是容易的，记录进入该节点时所有 $[l_j, r_j, v_j]$ 对线段树的修改即可。

换种角度考虑，对于一般的矩形加数单点查询最值，我们通过对一维扫描线转化为区间加 / 删数以及单点查最值。删数是很不好处理的，我们不得不使用 multiset。但若扫描线的那一维 $D_1$（dfs 序维度）的区间只有包含或相离的关系，那么在 $D_1$ 的某个区间 $[L, R]$ 的右端点（$[L, R]$ 是 dfn 区间）处删除另一维 $D_2$（时间维度）上一段区间的数时，所有在 $D_1$ 上包含于 $[L, R]$ 的区间的影响已经没有了，相当于我们此时面对着刚好加入当前要被删除的一段区间的数的局面，这意味着我们只需要撤销操作而非删除。可以想象成括号序列进栈（加入贡献）出栈（撤销影响）。

总结一下，树上问题可以通过离线 dfs 去掉形如 “包含在某个节点的子树内” 的限制，并将其转化为在端点处撤销，而撤销是 trivial 的。但是序列问题通过扫描线去掉 “包含在某个区间内” 的限制后，只能在端点处删除，对于 **不可减的信息** 而言复杂度更劣（但对于可减信息并没有太大差别）。换言之，对于子树限制，拍平到序列上后限制区间两两不交，这是非常棒的性质。个人认为这种技巧有很大的应用空间，读者需认真体会。

时间复杂度 $\mathcal{O}(n|\Sigma| + q\log n)$，[代码](https://codeforces.com/contest/1437/submission/152996143)。

---

## 作者：zhoukangyang (赞：7)

[来蒟蒻的博客园里来看/kel](https://www.cnblogs.com/zkyJuruo/p/13891633.html)

这题感觉不是很难，但是既然放在 $\texttt{EDU}$ 的 $\texttt{G}$ 题，那么还是写写题解吧。
## $\texttt{Solution}$
首先看到 "子串"，那么想到 $\texttt{ACAM}$ 和 $\texttt{SAM}$。本篇题解就使用 $\texttt{ACAM}$。

然后我们先对于最开始给定的 $n$ 个串建立一个 $\texttt{ACAM}$。

然后考虑对于每一个串在 $\texttt{ACAM}$ 上对应的位置赋上这个串的值。 

查询其实就是在 $\texttt{fail}$ 树上查询一些节点到根的最大值。

这个其实就是要求在 $\texttt{fail}$ 树上单点修改，求链上最大值。这个东西树剖很好维护。

然后注意以下一个细节：一个串可能出现多次。这个 $\texttt{multiset}$ 维护一下最大值就好了

## $\texttt{Code}$
```cpp
#include<bits/stdc++.h>
using namespace std;
#define L(i, j, k) for(int i = (j), i##E = (k); i <= i##E; i++) 
#define R(i, j, k) for(int i = (j), i##E = (k); i >= i##E; i--) 
#define ll long long 
#define db double
#define mp make_pair 
const int N = 3e5 + 7;
const int M = N * 4;
const int inf = 1e9;
int n, m, endid[N], VAL[N];
int ch[N][26], fa[N], tot = 1;
multiset<int> st[N];
int insert(char *s, int n) {
    int now = 1;
    L(i, 0, n - 1) {
        if(!ch[now][s[i] - 'a']) ch[now][s[i] - 'a'] = ++tot;
        now = ch[now][s[i] - 'a'];
    }
    return now;
}
void bfs() {
    queue<int> q;
    L(i, 0, 25) if(ch[1][i]) fa[ch[1][i]] = 1, q.push(ch[1][i]); else ch[1][i] = 1;
    while(!q.empty()) {
        int u = q.front();
        q.pop();
        L(i, 0, 25) {
            int v = ch[u][i];
            if(!v) ch[u][i] = ch[fa[u]][i];
            else fa[v] = ch[fa[u]][i], q.push(v);
        }
    }
}
int head[N], edge_id;
struct node { int to, next; } e[N << 1];
void add_edge(int u, int v) {
    ++edge_id, e[edge_id].next = head[u], e[edge_id].to = v, head[u] = edge_id;
}
int siz[N], maxto[N], dep[N], uid[N], idtot, heavy[N];
void dfs1(int x) {
    siz[x] = 1;
    for(int i = head[x]; i; i = e[i].next) {
        int v = e[i].to;
        fa[v] = x, dep[v] = dep[x] + 1, dfs1(v), siz[x] += siz[v];
        if(siz[v] > siz[heavy[x]]) heavy[x] = v;
    }
}
void dfs2(int x) {
    uid[x] = ++idtot;
    if(heavy[x]) maxto[heavy[x]] = maxto[x], dfs2(heavy[x]);
    for(int i = head[x]; i; i = e[i].next) {
        int v = e[i].to;
        if(v == heavy[x]) continue;
        maxto[v] = v, dfs2(v);
    }
}
int maxn[M];
void build(int x, int l, int r) { 
    maxn[x] = -1; 
    if(l == r) return; 
    int mid = (l + r) / 2;
    build(x << 1, l, mid), build(x << 1 | 1, mid + 1, r);
}
void add(int id, int L, int R, int wz, int val) {
    // if(id == 1) cout << wz << " is : " << val << endl;
    if(L == R) return maxn[id] = val, void();
    int mid = (L + R) / 2;
    if(wz <= mid) add(id << 1, L, mid, wz, val);
    else add(id << 1 | 1, mid + 1, R, wz, val);
    maxn[id] = max(maxn[id << 1], maxn[id << 1 | 1]);
}
int query(int id, int L, int R, int l, int r) {
    if(l <= L && R <= r) return maxn[id];
    int mid = (L + R) / 2, res = -1;
    if(l <= mid) res = max(res, query(id << 1, L, mid, l, r));
    if(r > mid) res = max(res, query(id << 1 | 1, mid + 1, R, l, r));
    // if(id == 1) cout << l << " to " << r << "'s max = " << res << endl;
    return res;
}
int get(int x) {
    int res = -1;
    while(x) res = max(res, query(1, 1, tot, uid[maxto[x]], uid[x])), x = fa[maxto[x]];
    return res;
}
char s[N];
int main() {
    scanf("%d%d", &n, &m);
    L(i, 1, n) scanf("%s", s), endid[i] = insert(s, strlen(s));
    bfs();
    L(i, 2, tot) add_edge(fa[i], i);
    dfs1(1), maxto[1] = 1, dfs2(1);
    build(1, 1, tot);
    L(i, 1, n) add(1, 1, tot, uid[endid[i]], 0), st[endid[i]].insert(0);
    while(m--) {
        int opt, x, val;
        scanf("%d", &opt);
        if(opt == 1) {
            scanf("%d%d", &x, &val);
            int now = endid[x];
            st[now].erase(st[now].lower_bound(VAL[x]));
            st[now].insert(val), VAL[x] = val;
            add(1, 1, tot, uid[now], *st[now].rbegin());
        }
        else {
            int maxn = -1, now = 1;
            scanf("%s", s);
            L(i, 0, strlen(s) - 1) now = ch[now][s[i] - 'a'], maxn = max(maxn, get(now)); 
            printf("%d\n", maxn);
        }
    }
	return 0;
}
```

---

## 作者：Drind (赞：4)

### 题目解析

给定若干个串，每个串有一个权值，初始是 $0$，维护两种操作，一个是修改某个串的权值，一个是给定一个查询串，求所有他的子串的权值最大值。

首先看到很多个串的问题，我们直接建出 ac 自动机，然后有一个经典套路就是一个串的前缀在 fail 树上到根的这段路径就是他的所有子串。

所以我们对于每个前缀在 fail 树上进行一次链查找，然后对于修改操作，就是一个单点修改，这些操作我们可以用树剖维护，总复杂度 $O(\sum |q|\log^2\sum|s|)$。

注意串可重，所以对于每个结束点都需要一个 multiset 或者可删堆来维护，我代码里写的 multiset。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e5+1000;
inline int _abs(int x){if(x>0) return x;return -x;}

struct node{
	int to,nxt;
}edge[N*2]; int head[N],res;
void add(int u,int v){
	edge[++res].to=v;
	edge[res].nxt=head[u];
	head[u]=res;
}

int tr[N][26];
int fail[N],fa[N];
int lst[N],cnt;
multiset<int>val[N];
int pval[N];

void insert(string s,int x){
	int u=0;
	for(int i=0;i<s.size();i++){
		int v=s[i]-'a';
		if(!tr[u][v]) tr[u][v]=++cnt,fa[tr[u][v]]=u;
		u=tr[u][v];
	}
	lst[x]=u;
}

void build(){
	queue<int>q;
	for(int i=0;i<26;i++){
		if(tr[0][i]) q.push(tr[0][i]);
	}
	
	while(!q.empty()){
		int u=q.front(); q.pop();
		for(int i=0;i<26;i++){
			if(tr[u][i]){
				fail[tr[u][i]]=tr[fail[u]][i];
				q.push(tr[u][i]);
			}
			else tr[u][i]=tr[fail[u]][i];
		}
	}
	
	for(int i=1;i<=cnt;i++) add(fail[i],i);
}

int _fa[N],siz[N],son[N],dep[N];
int top[N],dfn[N],id[N],res_;
void dfs1(int u,int f){
	siz[u]=1; _fa[u]=f;
	dep[u]=dep[f]+1;
	
	for(int i=head[u];i;i=edge[i].nxt){
		int v=edge[i].to; if(v==f) continue;
		dfs1(v,u); siz[u]+=siz[v];
		if(!son[u]||siz[son[u]]<siz[v]) son[u]=v;
	}
}

void dfs2(int u,int tp){
	id[u]=++res_; dfn[res_]=u; top[u]=tp;
	if(!son[u]) return; dfs2(son[u],tp);
	for(int i=head[u];i;i=edge[i].nxt){
		int v=edge[i].to; if(v==_fa[u]||v==son[u]) continue;
		dfs2(v,v);
	}
}

struct segtree{
	struct node{
		int l,r;
		int mx;
	}tree[N*4];
	
	void pushup(int x){
		tree[x].mx=max(tree[x*2].mx,tree[x*2+1].mx);
	}
	
	void build(int x,int l,int r){
		tree[x].l=l; tree[x].r=r;
		if(l==r){
			tree[x].mx=-1;
			return;
		}
		int mid=(l+r)>>1;
		build(x*2,l,mid); build(x*2+1,mid+1,r);
		pushup(x);
	}
	
	void modify(int x,int pos,int val){
		if(tree[x].l==tree[x].r&&tree[x].l==pos){
			tree[x].mx=val; return;
		}
		if(pos<tree[x].l||tree[x].r<pos) return;
		modify(x*2,pos,val); modify(x*2+1,pos,val);
		pushup(x);
	}
	
	int query(int x,int l,int r){
		if(l<=tree[x].l&&tree[x].r<=r) return tree[x].mx;
		if(tree[x].l>r||tree[x].r<l) return -1;
		return max(query(x*2,l,r),query(x*2+1,l,r));
	}
}seg;

int linkquery(int u,int v){
	int ans=-1;
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]]) swap(u,v);
		ans=max(ans,seg.query(1,id[top[u]],id[u]));
		
		u=_fa[top[u]];
	}
	if(dep[u]>dep[v]) swap(u,v);
	ans=max(ans,seg.query(1,id[u],id[v]));
	
	return ans;
}

void fake_main(){
	
	
	int n,m; cin>>n>>m;
	for(int i=1;i<=n;i++){
		string s; cin>>s;
		insert(s,i);
	}
	
	build(); seg.build(1,1,300010);
	
	
	
	dfs1(0,0); dfs2(0,0);
	
	for(int i=1;i<=n;i++){//注意线段树初始值应该是 -1，然后给每个结束点附上 0 的权值，才能保证不包含任何串答案就是 -1。
		seg.modify(1,id[lst[i]],0);
		pval[i]=0; val[lst[i]].insert(0);
		
	}
	

	
	for(int i=1;i<=m;i++){
		int op; cin>>op;
		
		if(op==1){
			int x,y; cin>>x>>y;
			val[lst[x]].erase(val[lst[x]].find(pval[x]));
			pval[x]=y; val[lst[x]].insert(pval[x]);//用multiset维护这个结束点的最大值，并且插入树里
			seg.modify(1,id[lst[x]],*prev(val[lst[x]].end()));
		}else{
			string s; cin>>s;
			int u=0,ans=-1;
			for(int j=0;j<s.size();j++){
				int v=s[j]-'a';
				u=tr[u][v];
				ans=max(ans,linkquery(0,u));//对于每个前缀算他到根的最大值
			}
			
			cout<<ans<<"\n";
		}
	}
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	int t; t=1;
	while(t--) fake_main();
}

```

---

## 作者：万弘 (赞：4)

CF质量确实越来越差，已经开始出板子题了。

先考虑没有名字重复的情况。先建那些人名字的广义SAM，并记录每个名字对应的终止节点。设一个终止节点的点权为那个人的suspicion value，非终止节点为-1.

考虑询问一个串$S$，在SAM上跑匹配找到$S$的每个前缀的对应节点，这个前缀的贡献就是这个点到根的路径上的最大点权。

单点修改，询问到根的最大点权，LCT直接上就好了。

对于有名字重复的情况，让每个点维护一个`std::multiset`或线段树就行。

复杂度$\mathcal O(L\log L)$

```cpp
/**********/
#define MAXN 600011
struct SAM
{
    int t[MAXN][26],pre[MAXN],len[MAXN];
    int last,tot;
    SAM(){last=tot=1;}
    void extend(int w)
    {
        if(t[last][w])
        {
            int nxt=t[last][w];
            if(len[nxt]==len[last]+1)last=nxt;
            else
            {
                int tmp=++tot;
                len[tmp]=len[last]+1,memcpy(t[tmp],t[nxt],sizeof t[nxt]);
                pre[tmp]=pre[nxt],pre[nxt]=tmp;
                while(last&&t[last][w]==nxt)t[last][w]=tmp,last=pre[last];
                last=tmp;
            }
            return;
        }
        int pos=last,cur=++tot;
        len[cur]=len[pos]+1,last=cur;
        while(pos&&!t[pos][w])t[pos][w]=cur,pos=pre[pos];
        if(!pos){pre[cur]=1;return;}
        int nxt=t[pos][w];
        if(len[nxt]==len[pos]+1)pre[cur]=nxt;
        else
        {
            int tmp=++tot;
            len[tmp]=len[pos]+1,memcpy(t[tmp],t[nxt],sizeof t[nxt]);
            pre[tmp]=pre[nxt],pre[cur]=pre[nxt]=tmp;
            while(pos&&t[pos][w]==nxt)t[pos][w]=tmp,pos=pre[pos];
        }
    }
}sam;
struct LCT
{
    int fa[MAXN],son[MAXN][2],f[MAXN];
    std::multiset<int>val[MAXN];
    void init(){f[0]=-1; for(int i=1;i<=sam.tot;++i)fa[i]=sam.pre[i],f[i]=-1;}
    bool not_root(int x){return son[fa[x]][0]==x||son[fa[x]][1]==x;}
    void pushup(int x){f[x]=max(*val[x].rbegin(),max(f[son[x][0]],f[son[x][1]]));}
    void rotate(int x)
    {
        int y=fa[x],z=fa[y],k=(son[y][1]==x);
        if(not_root(y))son[z][son[z][1]==y]=x;
        fa[x]=z;
        son[y][k]=son[x][!k],fa[son[x][!k]]=y;
        son[x][!k]=y,fa[y]=x;
        pushup(y);
    }
    void splay(int x)
    {
        while(not_root(x))
        {
            int y=fa[x];
            if(not_root(y))rotate((son[y][1]==x)==(son[fa[y]][1]==y)?y:x);
            rotate(x);
        }
        pushup(x);
    }
    void access(int x)
    {
        for(int y=0;x;y=x,x=fa[x])
            splay(x),son[x][1]=y;
    }
    int Query(int x){access(x),splay(x);return f[x];}
    void add(int x,int k){access(x),splay(x);val[x].insert(k),pushup(x);}
    void modify(int x,int pre,int k){access(x),splay(x),val[x].erase(val[x].find(pre)),val[x].insert(k);pushup(x);}
}lct;
char s[MAXN];
int ed[MAXN],a[MAXN];
int main()
{
    int n=read(),m=read();
    for(int x=1;x<=n;++x)
    {
        scanf("%s",s+1);
        int l=strlen(s+1);
        sam.last=1;
        for(int j=1;j<=l;++j)sam.extend(s[j]-'a');
        ed[x]=sam.last;
    }
    lct.init();
    for(int i=1;i<=n;++i)lct.val[ed[i]].insert(0);
    for(int i=1;i<=sam.tot;++i)
        if(lct.val[i].empty())lct.val[i].insert(-1);
    while(m--)
    {
        int op=read();
        if(op==1)
        {
            int x=read(),k=read();lct.modify(ed[x],a[x],k),a[x]=k;
        }
        else
        {
            scanf("%s",s+1);
            int l=strlen(s+1),u=1,nowlen=0,res=-1;
            for(int i=1;i<=l;++i)
            {
                while(u&&!sam.t[u][s[i]-'a'])u=sam.pre[u],nowlen=sam.len[u];
                if(!u)u=1,nowlen=0;
                else u=sam.t[u][s[i]-'a'],++nowlen;
                if(nowlen!=sam.len[u])umax(res,lct.Query(sam.pre[u]));
                else umax(res,lct.Query(u));
            }
            printf("%d\n",res);
        }
    }
    return 0;
}
```



---

## 作者：lfxxx (赞：3)

单 $\log$ 跑不过 $\log^2$ 真是逆天。

考虑把所有的询问串与模板串放在一起建广义后缀自动机，然后记录下所有终止节点，每次查询字串就在自动机上跑，看跑到的每一个点在 parent 树上的祖先是否是终止节点并计算贡献，转换一下变成单点修改链查最大值，考虑全局平衡二叉树维护即可，每个点上还要开一个可重集维护不同的串的权值。

复杂度 $O((n+q) \log n)$。

```cpp
#include<bits/stdc++.h>
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,popcnt,tune=native")
using namespace std;
const int maxn = 1e6+2e5+114;
struct SAM{
    int len,fa;
    int son[26];
}nd[maxn]; 
int tot,lst;
int ending[maxn];
void ins(char c,int pos){
    if(nd[lst].son[c-'a']!=0){
        int q=nd[lst].son[c-'a'],v=lst;
        if(nd[q].len==nd[v].len+1){
            lst=q;
            ending[pos]=q;
            return ;    
        }
        int nq=++tot;
        lst=nq;
        ending[pos]=nq;
        nd[nq]=nd[q];
        nd[nq].len=nd[v].len+1;
        nd[q].fa=nq;
        while(v!=0&&nd[v].son[c-'a']==q) nd[v].son[c-'a']=nq,v=nd[v].fa;
        return ;
    }
    int u=++tot,v=lst;
    nd[u].len=nd[lst].len+1;
    lst=u;
    ending[pos]=u;
    //cout<<pos<<' '<<ending[pos]<<' '<<u<<' '<<nd[u].fa<<'\n';
    while(v!=0&&nd[v].son[c-'a']==0) nd[v].son[c-'a']=u,v=nd[v].fa;
    if(v==0){
        nd[u].fa=1;
        return ;
    }else{
        int q=nd[v].son[c-'a'];
        if(nd[v].len+1==nd[q].len){
            nd[u].fa=q;
            return ;
        }else{
            int nq=++tot;
            nd[nq]=nd[q];
            nd[nq].len=nd[v].len+1;
            nd[u].fa=nq;
            nd[q].fa=nq;
            while(v!=0&&nd[v].son[c-'a']==q) nd[v].son[c-'a']=nq,v=nd[v].fa;
            return ;
        }
    }
}
void insert(string s,int pos){
    lst=1;
    for(char x:s) ins(x,pos);
}
vector<int> edge[maxn];
int son[maxn],sz[maxn],dfn[maxn],dfncnt,top[maxn];
int v_fa[maxn],ls[maxn],rs[maxn],pre[maxn],rt[maxn],Node[maxn],tail[maxn];
int tr[maxn],mx[maxn];
void dfs1(int u){
    sz[u]=1;
    for(int v:edge[u]){
        dfs1(v);
        sz[u]+=sz[v];
        if(sz[v]>sz[son[u]]) son[u]=v;
    }
}
void dfs2(int u,int tp){
    tail[tp]=u;
    top[u]=tp;
    dfn[u]=++dfncnt;
    Node[dfncnt]=u;
    if(son[u]!=0){
        dfs2(son[u],tp);
    }
    for(int v:edge[u]){
        if(v!=son[u]) dfs2(v,v);
    }
}
int build(int l,int r){//dfn 序在区间 [lt,rt] 中的点所在重链建树
    if(l>r) return 0;
    int root=Node[lower_bound(pre+l,pre+r+1,(pre[r]+pre[l-1])>>1)-pre];
    ls[root]=build(l,dfn[root]-1);
    rs[root]=build(dfn[root]+1,r);
    tr[root]=-1;
    mx[root]=max(tr[root],max(mx[ls[root]],mx[rs[root]]));
    v_fa[ls[root]]=v_fa[rs[root]]=root;
    return root;
}
multiset<int> S[maxn];
void change(int u){
    tr[u]=(*S[u].rbegin());
    mx[u]=max(tr[u],max(mx[ls[u]],mx[rs[u]]));
    while(u!=0){
        u=v_fa[u];
        mx[u]=max(tr[u],max(mx[ls[u]],mx[rs[u]]));
    }
    return ;
}
int query(int x,int u){
    if(x==0) return -1;
    if(dfn[x]>dfn[u]) return query(ls[x],u);
    else if(dfn[x]==dfn[u]) return max(mx[ls[x]],tr[x]);
    else return max(max(tr[x],mx[ls[x]]),query(rs[x],u));
}
int ask(int u){
    int res=-1;
    while(u!=0){
        res=max(res,query(rt[top[u]],u));
        //cout<<top[u]<<' '<<u<<' '<<query(rt[top[u]],u)<<'\n';
        u=nd[top[u]].fa;        
    }
    return res;
}
void init(){
    dfs1(1);
    dfs2(1,1);
    for(int i=1;i<=tot;i++) pre[i]=pre[i-1]+sz[Node[i]]-sz[son[Node[i]]];
    for(int i=1;i<=tot;i++){
        if(top[i]==i){
            rt[i]=build(dfn[top[i]],dfn[tail[i]]);
        }
    }
    return ;
}
int val[maxn];
void opt1(int i,int x){
    //cout<<"Change"<<ending[i]<<' '<<x<<'\n';
    //cout<<ending[i]<<' '<<val[i]<<'\n';
    S[ending[i]].erase(S[ending[i]].find(val[i]));
    val[i]=x;
    S[ending[i]].insert(val[i]);
    change(ending[i]);
    return ;
}
int opt2(string s){
    int res=-1;
    int u=1;
    for(char x:s){
        u=nd[u].son[x-'a'];
        //cout<<"ASK"<<u<<'\n';
        res=max(res,ask(u));
    }
    return res;
}
struct opt{
    int op,i,x;
    string s;
}q[maxn];
int n,m;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    memset(tr,-1,sizeof(tr));
    memset(mx,-1,sizeof(mx));
    ++tot;
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        string s;
        cin>>s;
        insert(s,i);
        val[i]=-1;
    }
    for(int i=1;i<=m;i++){
        cin>>q[i].op;
        if(q[i].op==1) cin>>q[i].i>>q[i].x;
        else cin>>q[i].s,insert(q[i].s,i+n);
    }
    for(int i=2;i<=tot;i++) edge[nd[i].fa].push_back(i);
    for(int i=1;i<=n;i++) S[ending[i]].insert(-1);
    init();
    for(int i=1;i<=n;i++) opt1(i,0);      
    for(int i=1;i<=m;i++){
        if(q[i].op==1) opt1(q[i].i,q[i].x);
        else cout<<opt2(q[i].s)<<'\n';
    }
    return 0;
}
```


---

## 作者：wrzSama (赞：3)

## 题目大意

给出 $n$ 个字符串和 $m$ 个操作，每个字符串都有一个权值，其初始值为 $0$。这 $m$ 个操作分为 $2$ 种：
- 1 x k：将第 $x$ 个字符串的权值修改为 $k$。

- 2 q：给出一个字符串 $q$，求所有是 $q$ 的子串的字符串的权值的最大值。

## 思路

我们对这 $n$ 个字符串建立一个 AC 自动机，按 fail 指针建一颗 fail 树，定义每个节点权值是其所有祖先（包括它本身）的字符串的权值的最大值。那么，对于操作 $2$，每次在字典树上遍历字符串 $q$，求出其遍历到的所有节点的权值的最大值就是答案。下面，我们考虑如何维护每个节点的权值。我们可以将 fail 树按 dfs 序压成 $1$ 维并对其建立一颗线段树，用 multiset 维护每个区间的所有节点的权值的最大值。每改变一个节点的权值，就令线段树上以该节点为根的子树的区间中所有 multiset 删除修改前的权值并加入修改后的值，注意不要把 multiset 中的值向下传递。查询一个节点的权值，就求出所有包含这个节点的区间的 multiset 中的最大值即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
	int read_result=0,is_below_0=0;
	char now_ch=0;
	while(!isdigit(now_ch))
	{
		is_below_0|=now_ch=='-';
		now_ch=getchar();
	}
	while(isdigit(now_ch))
	{
		read_result=(read_result<<3)+(read_result<<1)+(now_ch^48);
		now_ch=getchar();
	}
	return is_below_0?-read_result:read_result;
}
inline void write(int x)
{
	if(x<0)
	{
		putchar('-');
		x=-x;
	}
	if(x>9) write(x/10);
	putchar(x%10+'0');
}
int n,m,tr[300005][26],tot,fail[300005],id[300005],dfn[300005],cnt,sz[300005],lst[300005];
multiset<int>t[1200005];
vector<int>s[300005];
inline void insert(string s,int num)
{
	int o=0;
	for(int i=0;i<s.size();++i)
	{
		if(!tr[o][s[i]-'a']) tr[o][s[i]-'a']=++tot;
		o=tr[o][s[i]-'a'];
	}
	id[num]=o;
}
inline void build()
{
	queue<int>q;
	for(int i=0;i<26;++i) if(tr[0][i]) q.push(tr[0][i]);
	while(q.size())
	{
		int u=q.front();
		q.pop();
		s[fail[u]].push_back(u);
		for(int i=0;i<26;++i)
		{
			if(tr[u][i])
			{
				fail[tr[u][i]]=tr[fail[u]][i];
				q.push(tr[u][i]);
			}
			else tr[u][i]=tr[fail[u]][i];
		}
	}
}
inline void dfs(int u)
{
	sz[u]=1;
	dfn[u]=++cnt;
	for(int i=0;i<s[u].size();++i)
	{
		int v=s[u][i];
		dfs(v);
		sz[u]+=sz[v];
	}
}
inline void update(int o,int l,int r,int x,int y,int k1,int k2)
{
	if(x<=l&&r<=y)
	{
		t[o].insert(k1);
		if(k2>=0) t[o].erase(t[o].find(k2));
		return;
	}
	int mid=(l+r)>>1;
	if(x<=mid) update(o<<1,l,mid,x,y,k1,k2);
	if(y>mid) update(o<<1|1,mid+1,r,x,y,k1,k2);
}
inline int query(int o,int l,int r,int x)
{
	if(l==r)
	{
		if(t[o].empty()) return -1;
		return *--t[o].end();
	}
	int mid=(l+r)>>1,res=-1;
	if(t[o].size()) res=*--t[o].end();
	if(x<=mid) return max(res,query(o<<1,l,mid,x));
	return max(res,query(o<<1|1,mid+1,r,x));
}
inline int getmax(string s)
{
	int o=0,res=-1;
	for(int i=0;i<s.size();++i)
	{
		o=tr[o][s[i]-'a'];
		res=max(res,query(1,1,cnt,dfn[o]));
	}
	return res;
}
int main()
{
	n=read();
	m=read();
	for(int i=1;i<=n;++i)
	{
		string s;
		cin>>s;
		insert(s,i);
	}
	build();
	dfs(0);
	for(int i=1;i<=n;++i) update(1,1,cnt,dfn[id[i]],dfn[id[i]]+sz[id[i]]-1,0,-1);
	for(int i=1;i<=m;++i)
	{
		int op=read();
		if(op==1)
		{
			int i=read(),x=read();
			update(1,1,cnt,dfn[id[i]],dfn[id[i]]+sz[id[i]]-1,x,lst[i]);
			lst[i]=x;
		}
		else
		{
			string s;
			cin>>s;
			write(getmax(s));
			puts("");
		}
	}
	return 0;
}
```


---

## 作者：GIFBMP (赞：3)

### 正题

首先，根据一个结论，一个串所包含的子串的集合等于它在 AC 自动机上经过的所有点到根的路径所代表的串的并集。（可以自行画图理解）

因此，我们可以建立 fail 树，那么操作 $1$ 相当于树上单点修改。

对于操作 $2$，我们将询问的串放入 AC 自动机中匹配，对于每个经过的节点求它到 $0$ 号节点的路径上的最大值，最后对于这些最大值再取最大即可。

特别地，如果经过的点当中没有包含任何文本串，答案为 $-1$。而这可以在求 fail 时顺便求出，这里就不展开讲了。

但这题有一个值得注意的地方，那就是可能有多个重复的文本串，在修改的时候，单点修改的权值要取这些文本串权值的最大值。

因此，我们可以把结束节点在同一个点上的文本串看做一个区间，把所有区间压缩到一个线段树里，只要维护单点加，区间最大值即可。

综上所述，用树链剖分+线段树维护即可。

如果对于上述内容不理解，可以结合代码理解。

时间复杂度：$\Theta(q\log n+q\log^2\sum|S|)$，虽然不是很优秀，但可以通过本题。

Code:

```cpp
#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
#include <vector>
#define lc(o) (o << 1) 
#define rc(o) (o << 1 | 1)
using namespace std ;
const int MAXN = 3e5 + 10 ;
int n , q , trie[MAXN][30] , fail[MAXN] , tot , vis[MAXN] , vv[MAXN] ;
int dep[MAXN] , sz[MAXN] , h[MAXN] , f[MAXN] , fir[MAXN] , tt ; 
int tp[MAXN] , id[MAXN] , cnt ;
char s[MAXN] ;
struct edge {
	int to , nxt ;
} e[MAXN] ;
struct sgt {
	int mx ;
	sgt () {mx = 0 ;}
} t[MAXN << 2] , t2[MAXN << 2] ;
int idd[MAXN] , ccnt , lp[MAXN] , rp[MAXN] ;
void add (int u , int v) {
	e[++tt].to = v ;
	e[tt].nxt = fir[u] ;
	fir[u] = tt ; 
}
vector <int> G[MAXN] ;
void insert (int x) {
	int len = strlen (s + 1) , nw = 0 ;
	for (int i = 1 ; i <= len ; i++) {
		int p = s[i] - 'a' ;
		if (!trie[nw][p]) trie[nw][p] = ++tot ;
		nw = trie[nw][p] ;
	}
	vis[x] = nw ;
	vv[nw] = 1 ;
	G[nw].push_back (x) ; 
}
void work () {
	fail[0] = 0 ;
	queue <int> q ;
	for (int i = 0 ; i < 26 ; i++)
		if (trie[0][i]) {
			q.push (trie[0][i]) ;
			fail[trie[0][i]] = 0 ;
		}
	while (!q.empty ()) {
		int x = q.front () ;
		//printf ("%d %d\n" , x , fail[x]) ;
		q.pop () ; add (fail[x] , x) ;
		for (int i = 0 ; i < 26 ; i++)	{
			if (trie[x][i]) {
				fail[trie[x][i]] = trie[fail[x]][i] ;
				vv[trie[x][i]] |= vv[trie[fail[x]][i]] ;
				q.push (trie[x][i]) ;
			}
			else trie[x][i] = trie[fail[x]][i] ;
		}
	}
}
void dfs (int x , int fa) {
	dep[x] = dep[fa] + 1 ; sz[x] = 1 ; f[x] = fa ;
	int tmp = -1 ;
	for (int i = fir[x] ; i ; i = e[i].nxt) {
		int v = e[i].to ; dfs (v , x) ;
		sz[x] += sz[v] ;
		if (sz[v] > tmp)
			tmp = sz[v] , h[x] = v ; 
	}
}
void dfs2 (int x , int fa) {
	tp[x] = fa ; id[x] = ++cnt ;
	if (h[x] != -1) dfs2 (h[x] , fa) ;
	for (int i = fir[x] ; i ; i = e[i].nxt) {
		int v = e[i].to ;
		if (v != h[x]) dfs2 (v , v) ;
	}
}
int lca (int x , int y) {
	while (tp[x] != tp[y]) {
		if (dep[tp[x]] < dep[tp[y]]) swap (x , y) ;
		x = f[tp[x]] ;
	}
	return dep[x] < dep[y] ? x : y ;
}
void push_up (int o) {
	t[o].mx = max (t[lc(o)].mx , t[rc(o)].mx) ;
}
void upd (int o , int l , int r , int x , int k) {
	if (l == r) {
		t[o].mx = k ;
		return ;
	}
	int mid = l + r >> 1 ;
	if (x <= mid) upd (lc(o) , l , mid , x , k) ;
	else upd (rc(o) , mid + 1 , r , x , k) ;
	push_up (o) ;
}
int query (int o , int l , int r , int x , int y) {
	if (x <= l && r <= y) return t[o].mx ;
	int mid = l + r >> 1 ;
	if (y <= mid) return query (lc(o) , l , mid , x , y) ;
	if (mid < x) return query (rc(o) , mid + 1 , r , x , y) ;
	return max (query (lc(o) , l , mid , x , y) , query (rc(o) , mid + 1 , r , x , y)) ;
}
int qmx (int x , int y) {
	int ret = 0 ;
	while (tp[x] != tp[y]) {
		if (dep[tp[x]] < dep[tp[y]]) swap (x , y) ;
		ret = max (ret , query (1 , 1 , cnt , id[tp[x]] , id[x])) ;
		x = f[tp[x]] ;
	}
	if (dep[x] > dep[y]) swap (x , y) ;
	ret = max (ret , query (1 , 1 , cnt , id[x] , id[y])) ;
	return ret ;
}
void u2 (int o , int l , int r , int x , int k) {
	if (l == r) {
		t2[o].mx = k ;
		return ;
	}
	int mid = l + r >> 1 ;
	if (x <= mid) u2 (lc(o) , l , mid , x , k) ;
	else u2 (rc(o) , mid + 1 , r , x , k) ;
	t2[o].mx = max (t2[lc(o)].mx , t2[rc(o)].mx) ; 
}
int q2 (int o , int l , int r , int x , int y) {
	if (x <= l && r <= y) return t2[o].mx ;
	int mid = l + r >> 1 ;
	if (y <= mid) return q2 (lc(o) , l , mid , x , y) ;
	if (mid < x) return q2 (rc(o) , mid + 1 , r , x , y) ;
	return max (q2 (lc(o) , l , mid , x , y) , q2 (rc(o) , mid + 1 , r , x , y)) ;
}
int main () {
	scanf ("%d %d" , &n , &q) ;
	for (int i = 1 ; i <= n ; i++)
		scanf ("%s" , s + 1) , insert (i) ;
	for (int i = 0 ; i <= tot ; i++) {
		lp[i] = ccnt + 1 ; 
		for (int j = 0 ; j < G[i].size () ; j++)
			idd[G[i][j]] = ++ccnt ;
		rp[i] = ccnt ;
	}
	work () ; 
	memset (h , -1 , sizeof (h)) ;
	dfs (0 , 0) ; dfs2 (0 , 0) ;
	while (q--) {
		int opt , x , y ;
		scanf ("%d" , &opt) ;
		if (opt == 1) {
			scanf ("%d %d" , &x , &y) ;
			u2 (1 , 1 , n , idd[x] , y) ;
			int tmp = q2 (1 , 1 , n , lp[vis[x]] , rp[vis[x]]) ;
			upd (1 , 1 , cnt , id[vis[x]] , tmp) ; 
		}
		else {
			scanf ("%s" , s + 1) ;
			int nw = 0 , ls = strlen (s + 1) , ret = -1 ;
			bool flag = 0 ;
			for (int i = 1 ; i <= ls ; i++) {
				int p = s[i] - 'a' ;
				nw = trie[nw][p] ;
				//printf ("%d\n" , nw) ;
				if (vv[nw]) flag = 1 ;
				ret = max (ret , qmx (nw , 0)) ;
				//printf ("%d\n" , ret) ;
			}
			printf ("%d\n" , flag ? ret : -1) ;
		}
//		for (int i = 0 ; i <= tot ; i++)
//			printf ("%d " , query (1 , 1 , cnt , id[i] , id[i])) ;
//		printf ("\n") ;
	}
	return 0 ;
}
```

---

## 作者：xyf007 (赞：2)

给出 $n$ 个字符串 $s_i$，每个字符串都有一个权值，最初权值都为 $0$。$q$ 次操作，操作有两种类型：
- 将第 $i$ 个字符串的权值修改为 $x$。
- 给出一个字符串 $t_i$，求所有是 $t_i$ 的子串的字符串的权值最大值，如果不存在则为 $-1$。

$1\le n,m\le3\times10^5$，$\sum|s_i|,\sum|t_i|\le3\times10^5$。

---
~~大家好我很喜欢暴力所以我用根号做法通过了此题。~~  
设 $S=\sum|s_i|$，$T=\sum|t_i|$。一个暴力的想法是枚举 $t_i$ 的所有子串，判断是否出现，可以在 Trie 树上查询。Trie 树的结束结点用 `std::multiset` 记录权值，修改是 $O(m\log n)$ 的不成问题，这样单次查询是 $O(|t_i|^2)$ 的，于是考虑根号分治。设阈值为 $B$，当 $|t_i|\le B$ 时暴力，根据不等式可以知道最坏情况 $O(BT)$；当 $|t_i|>B$ 时，这样的情况最多只会出现 $\dfrac{T}{B}$ 次，考虑枚举 $s$ 判断是否是 $t_i$ 的子串。要求判断子串的复杂度与 $|t_i|$ 无关，可以想到对 $t_i$ 建立 SAM，单次复杂度就是 $O(S+|t_i|)$。总时间复杂度 $O\left(BT+S\times\dfrac{T}{B}\right)$，取 $B=\sqrt{S}$，则为 $O(T\sqrt{S})$。

实践比大多数 log 做法快。
```cpp
#include <cmath>
#include <cstring>
#include <iostream>
#include <set>
#include <string>
template <typename T>
void checkmax(T &x, T y) {
  if (x < y) x = y;
}
template <typename T>
void checkmin(T &x, T y) {
  if (x > y) x = y;
}
int n, q, a[300001], ch[300001][26], tot, ed[300001], id[300001], cnt;
std::string s[300001], t;
std::multiset<int, std::greater<int>> st[300001];
bool vis[300001];
void Insert(const std::string s, int x) {
  int now = 0;
  for (const auto &c : s) {
    if (!ch[now][c - 'a']) ch[now][c - 'a'] = ++tot;
    now = ch[now][c - 'a'];
  }
  vis[ed[x] = now] = true;
  if (!id[now]) id[now] = ++cnt;
  st[id[now]].emplace(0);
}
class SuffixAutomaton {
 private:
  struct Node {
    int len, link, nxt[26];
  } t_[600001];
  int sz_, last_;

 public:
  SuffixAutomaton() { t_[0].link = -1; }
  void Clear() {
    for (int i = 0; i <= sz_; i++)
      t_[i].len = t_[i].link = 0, std::memset(t_[i].nxt, 0, sizeof(t_[i].nxt));
    sz_ = last_ = 0, t_[0].link = -1;
  }
  void Expand(char c) {
    int cur = ++sz_, p = last_;
    t_[cur].len = t_[last_].len + 1;
    while (p != -1 && !t_[p].nxt[c - 'a'])
      t_[p].nxt[c - 'a'] = cur, p = t_[p].link;
    if (p == -1) {
      t_[cur].link = 0;
    } else {
      int q = t_[p].nxt[c - 'a'];
      if (t_[q].len == t_[p].len + 1) {
        t_[cur].link = q;
      } else {
        int nq = ++sz_;
        t_[nq].len = t_[p].len + 1, t_[nq].link = t_[q].link;
        std::memcpy(t_[nq].nxt, t_[q].nxt, sizeof(t_[q].nxt));
        while (p != -1 && t_[p].nxt[c - 'a'] == q)
          t_[p].nxt[c - 'a'] = nq, p = t_[p].link;
        t_[cur].link = t_[q].link = nq;
      }
    }
    last_ = cur;
  }
  bool Find(const std::string &s) {
    int now = 0;
    for (const auto &c : s) {
      if (!t_[now].nxt[c - 'a']) return false;
      now = t_[now].nxt[c - 'a'];
    }
    return true;
  }
  ~SuffixAutomaton() {}
} sam;
int main(int argc, char const *argv[]) {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);
  std::cin >> n >> q;
  std::size_t B = 0;
  for (int i = 1; i <= n; i++) std::cin >> s[i], B += s[i].size();
  for (int i = 1; i <= n; i++) Insert(s[i], i);
  B = std::sqrt(B);
  while (q--) {
    int op;
    std::cin >> op;
    if (op == 1) {
      int x, y;
      std::cin >> x >> y;
      st[id[ed[x]]].erase(st[id[ed[x]]].find(a[x]));
      st[id[ed[x]]].emplace(a[x] = y);
    } else {
      std::cin >> t;
      int ans = -1;
      if (t.size() <= B) {
        for (std::size_t i = 0; i < t.size(); i++) {
          int now = 0;
          for (std::size_t j = i; j < t.size(); j++) {
            if (!ch[now][t[j] - 'a']) break;
            now = ch[now][t[j] - 'a'];
            if (vis[now]) checkmax(ans, *st[id[now]].begin());
          }
        }
      } else {
        sam.Clear();
        for (const auto &c : t) sam.Expand(c);
        for (int i = 1; i <= n; i++)
          if (sam.Find(s[i])) checkmax(ans, *st[id[ed[i]]].begin());
      }
      std::cout << ans << '\n';
    }
  }
  return 0;
}
```

---

## 作者：Engulf (赞：1)

对所有 $s$ 建出 AC 自动机。每次询问把 $t$ 扔进去匹配，每个节点在 fail 树上的祖先都是这个节点所代表字符串的字串，取个最大值即可，这个可以用树剖维护。

注意到有重复的字符串，所以每个叶子节点需开一个 `multiset` 维护。

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;

#ifdef ONLINE_JUDGE
#define debug(...) 0
#else
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#endif

const int N = 3e5 + 5;

int tr[N][26], fail[N], idx;

int ed[N];

vector<int> g[N];

void insert(string s, int id) {
    int p = 0;
    for (auto c: s) {
        if (!tr[p][c - 'a']) tr[p][c - 'a'] = ++idx;
        p = tr[p][c - 'a'];
    }
    ed[id] = p;
}

void build() {
    queue<int> q;
    for (int i = 0; i < 26; i++) if (tr[0][i]) q.push(tr[0][i]);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        g[fail[u]].emplace_back(u);
        for (int i = 0; i < 26; i++)
            if (tr[u][i]) {
                fail[tr[u][i]] = tr[fail[u]][i];
                q.push(tr[u][i]);
            } else
                tr[u][i] = tr[fail[u]][i];
    }
}

int son[N], fa[N], dep[N], siz[N];
int top[N], dfn[N], tim;

void dfs1(int u, int f) {
    dep[u] = dep[f] + 1;
    fa[u] = f;
    siz[u] = 1;
    for (auto v: g[u]) {
        if (v == f) continue;
        dfs1(v, u);
        siz[u] += siz[v];
        if (!son[u] || siz[v] > siz[son[u]])
            son[u] = v;
    }
}

void dfs2(int u, int tp) {
    top[u] = tp;
    dfn[u] = ++tim;
    if (son[u]) dfs2(son[u], tp);
    for (auto v: g[u])
        if (!dfn[v])
            dfs2(v, v);
}

int maxn[N << 2];
multiset<int> leaf[N << 2];

void build(int p, int l, int r) {
    if (l == r) {maxn[p] = -1, leaf[p].insert(-1); return;}
    int mid = l + r >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
    maxn[p] = max(maxn[p << 1], maxn[p << 1 | 1]);
}

void insert(int p, int l, int r, int x, int v) {
    if (l == r) {leaf[p].insert(v); maxn[p] = *--leaf[p].end(); return;}
    int mid = l + r >> 1;
    x <= mid ? insert(p << 1, l, mid, x, v) : insert(p << 1 | 1, mid + 1, r, x, v);
    maxn[p] = max(maxn[p << 1], maxn[p << 1 | 1]);
}

void remove(int p, int l, int r, int x, int v) {
    if (l == r) {leaf[p].erase(leaf[p].lower_bound(v)); return;}
    int mid = l + r >> 1;
    x <= mid ? remove(p << 1, l, mid, x, v) : remove(p << 1 | 1, mid + 1, r, x, v);
    maxn[p] = max(maxn[p << 1], maxn[p << 1 | 1]);
}

int query(int p, int l, int r, int L, int R) {
    if (l > R || r < L) return -1;
    if (L <= l && r <= R) return maxn[p];
    int mid = l + r >> 1;
    return max(query(p << 1, l, mid, L, R), query(p << 1 | 1, mid + 1, r, L, R));
}

int query(int x, int y) {
    int res = -1;
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]]) swap(x, y);
        res = max(res, query(1, 1, tim, dfn[top[x]], dfn[x]));
        x = fa[top[x]];
    }
    if (dep[x] > dep[y]) swap(x, y);
    res = max(res, query(1, 1, tim, dfn[x], dfn[y]));
    return res;
}

int val[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        insert(s, i);
    }
    build();
    dfs1(0, 0), dfs2(0, 0);
    build(1, 1, tim);
    for (int i = 1; i <= n; i++) insert(1, 1, tim, dfn[ed[i]], 0);
    while (m--) {
        int op;
        cin >> op;
        if (op == 1) {
            int x, v;
            cin >> x >> v;
            remove(1, 1, tim, dfn[ed[x]], val[x]);
            insert(1, 1, tim, dfn[ed[x]], v);
            val[x] = v;
        } else {
            string s;
            cin >> s;
            int p = 0, res = -1;
            for (auto c: s) {
                p = tr[p][c - 'a'];
                res = max(res, query(0, p));
            }
            cout << res << "\n";
        }
    }
    return 0;
}
```

---

## 作者：ywy_c_asm (赞：1)

来一个后缀数组的做法。

离线，把所有的模板串和询问串使用特殊字符连接起来搞个大串，然后求出其后缀数组。对于每个模板串，考虑其在后缀数组中的位置$rk[i]$，显然，以它为前缀的所有大串的后缀（后缀的前缀就是子串）是其在后缀数组上的一个邻域区间$[rk[i]-a,rk[i]+b]$，可以通过后缀的LCP，二分出这个区间，然后使用线段树套堆去这个区间内整体将其的权值push进去，也可以更新权值。

对于每个询问串，枚举它对应的所有后缀，然后去线段树上查询这个位置的最大值即可，此时线段树的这个位置对应的堆里面存的就是所有以这个位置为起点的模板子串的值。

那么我们只需要写后缀排序+ST表+线段树套堆即可。注意拼凑大串的时候要开4倍空间。

时间$O(n\log^2n)$，空间$O(n\log n)$。

（顺带一提……2019年的十二省联考的D1T2和此题较为相似，我当时在考场上写的是和此题几乎一模一样的做法，~~但是它写挂了……~~）

上代码~

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define N 400010
using namespace std;
namespace ywy{
	inline int get(){
		int n=0;char c;while((c=getchar())||23333)if(c>='0'&&c<='9')break;
		n=c-'0';while((c=getchar())||23333){
			if(c>='0'&&c<='9')n=n*10+c-'0';else return(n);
		}
	}char s[N];unsigned char bv[N*3];int st[N*3][21],gch='z'+1;
	inline int sget(){
		int n=1;char c;while((c=getchar())||2333)if(c>='a'&&c<='z')break;
		s[n]=c;n++;while((c=getchar())||23333){
			if(c>='a'&&c<='z')s[n]=c,n++;else return(n-1);
		}
	}int str[N*3],sa[N*3],rk[N*3],h[N*3],height[N*3],trk[N*3],tsa[N*3],lst[N*3],lstcnt[N*3];
	typedef struct _h{
		priority_queue<int> me,del;
		inline void wh(){while(!me.empty()&&!del.empty()&&me.top()==del.top())me.pop(),del.pop();}
		void push(int x){me.push(x);}
		void erase(int x){del.push(x);}
		int top(){wh();if(me.empty())return(-1);return(me.top());}
	}heap;heap que[N*6];int lef[N*6],rgh[N*6],gn=1;
	int build(int l,int r){
		int me=gn;gn++;if(l==r)return(me);int mid=(l+r)>>1;
		lef[me]=build(l,mid);rgh[me]=build(mid+1,r);return(me);	
	}int pt,x,y;
	void push(int rl,int rr,int l,int r,int tree){
		if(rl==l&&rr==r){
			if(y!=-1)que[tree].erase(y);
			que[tree].push(x);return;
		}int mid=(l+r)>>1;if(rl>mid)push(rl,rr,mid+1,r,rgh[tree]);else{
			if(rr<=mid)push(rl,rr,l,mid,lef[tree]);else{
				push(rl,mid,l,mid,lef[tree]);push(mid+1,rr,mid+1,r,rgh[tree]);	
			}
		}
	}
	int query(int l,int r,int tree){
		if(l==r)return(que[tree].top());int mid=(l+r)>>1;
		if(pt<=mid)return(max(que[tree].top(),query(l,mid,lef[tree])));
		return(max(que[tree].top(),query(mid+1,r,rgh[tree])));
	}int lg[N*3],sums[N*3],tmp[N*3];
	inline int getrk(int a,int b){
		if(lst[a]==b){lstcnt[a]++;return(tmp[a]);}
		tmp[a]-=lstcnt[a];lst[a]=b;lstcnt[a]=1;return(tmp[a]);
	}
	void SA(int n){
		for(register int i=1;i<=n;i++)sums[str[i]]++;
		for(register int i=1;i<=gch;i++)sums[i]+=sums[i-1],tmp[i]=sums[i];
		for(register int i=1;i<=n;i++)sa[sums[str[i]]]=i,sums[str[i]]--,rk[i]=tmp[str[i]];
		for(register int b=1;b<n;b<<=1){
			for(register int i=1;i<=n;i++)bv[i]=sums[i]=lstcnt[i]=0,lst[i]=-1;
			for(register int i=1;i<=n;i++)sums[rk[i]]++;int bswitch=1;
			for(register int i=1;i<=n;i++)sums[i]+=sums[i-1],tmp[i]=sums[i];
			for(register int i=n;i>=1;i--){
				if(sa[i]<=b)continue;tsa[sums[rk[sa[i]-b]]]=sa[i]-b;sums[rk[sa[i]-b]]--;
				trk[sa[i]-b]=getrk(rk[sa[i]-b],rk[sa[i]]);	
			}for(register int i=n;i>n-b;i--){
				tsa[sums[rk[i]]]=i;sums[rk[i]]--;trk[i]=getrk(rk[i],0);
			}for(register int i=1;i<=n;i++){
				sa[i]=tsa[i];if(bv[rk[i]=trk[i]])bswitch=0;bv[rk[i]]=1;
			}if(bswitch)break;
		}
	}
	void Height(int n){
		if(sa[1]!=1){
			while(sa[rk[1]-1]+h[1]<=n&&str[sa[rk[1]-1]+h[1]]==str[h[1]+1])h[1]++;
		}for(register int i=2;i<=n;i++){
			if(rk[i]==1)continue;int lst=sa[rk[i]-1];h[i]=max(0,h[i-1]-1);
			while(max(lst,i)+h[i]<=n&&str[lst+h[i]]==str[i+h[i]])h[i]++;	
		}for(register int i=1;i<=n;i++)height[rk[i]]=h[i];
	}
	inline int qmin(int l,int r){
		int g=lg[r-l+1];return(min(st[l][g],st[r-(1<<g)+1][g]));	
	}int dl[N],dr[N],pos[N],len[N],val[N],qry[N][3];
	void print(int x){
		if(x<10)putchar(x+'0');else print(x/10),putchar(x%10+'0');	
	}
	void ywymain(){
		int n=get(),m=get();int ptr=1;for(register int i=1;i<=n;i++){
			int ln=sget();pos[i]=ptr;len[i]=ln;
			for(register int j=1;j<=ln;j++)str[ptr]=s[j],ptr++;str[ptr]=gch;gch++;ptr++;
		}for(register int i=1;i<=m;i++){
			int op=get();if(op==1){
				qry[i][0]=1;qry[i][1]=get();qry[i][2]=get();
			}else{
				int ln=sget();qry[i][0]=2;qry[i][1]=ptr;qry[i][2]=ln;
				for(register int j=1;j<=ln;j++)str[ptr]=s[j],ptr++;str[ptr]=gch;gch++;ptr++;
			}
		}ptr--;SA(ptr);Height(ptr);lg[0]=-1;for(register int i=1;i<=ptr;i++){
			lg[i]=lg[i-1];if(i==(i&-i))lg[i]++;st[i][0]=height[i];
		}
		for(register int i=1;i<=lg[ptr];i++){
			for(register int j=1;j+(1<<i)-1<=ptr;j++){
				st[j][i]=min(st[j][i-1],st[j+(1<<(i-1))][i-1]);
			}
		}int rt=build(1,ptr);for(register int i=1;i<=n;i++){
			int me=rk[pos[i]],ans=me,l=1,r=me-1;while(l<=r){
				int mid=(l+r)>>1;if(qmin(mid+1,me)>=len[i])ans=mid,r=mid-1;else l=mid+1; 
			}dl[i]=ans;ans=me;l=me+1;r=ptr;while(l<=r){
				int mid=(l+r)>>1;if(qmin(me+1,mid)>=len[i])ans=mid,l=mid+1;else r=mid-1;	
			}dr[i]=ans;x=0;y=-1;push(dl[i],dr[i],1,ptr,rt);
		}for(register int i=1;i<=m;i++){
			if(qry[i][0]==1){
				int me=qry[i][1];y=val[me];val[me]=x=qry[i][2];push(dl[me],dr[me],1,ptr,rt);
			}else{
				int me=qry[i][1],mx=-1;for(register int j=1;j<=qry[i][2];j++){
					pt=rk[me+j-1];mx=max(mx,query(1,ptr,rt));
				}if(mx==-1){
					putchar('-');putchar('1');	
				}else print(mx);putchar('\n');
			}
		}
	}
}
int main(){
	ywy::ywymain();return(0);	
}
```

---

## 作者：a2956331800 (赞：0)

## UPD
我成功在CF上hack了我自己的代码，现在更新了修改过可以通过的代码并强调一下这个叉点

在使用AC自动机进行匹配时，之前的代码使用了**每匹配到一个点，就从它沿fail走到根统计答案**的方法（同时不允许一次匹配中一个点被访问**大于一次**，这避免了被aaaa...aaa卡掉）

但这种方法依然能被卡，具体操作是，模式串（受害人姓名）为一个**高度无序**（确保trie上有接近模式串长度的节点）的长串(具体实现是用a-z的排列连起来)和它**所有的后缀**，询问串就是这个长串。-----这样整个fail树在一次询问中都会被访问，也就是说我们用一个长度为$\sqrt{\sum s_i}$的询问串产生了$\sum s_i$的运算量，则总复杂度就是$\sqrt{\sum s_i}\times\sum q_i$，TLE了

- 解决方案

基于fail树建一棵**只含对答案有效节点，也就是有某个$s_i$在这个点结尾的节点**，保持祖先-后代关系不变 

在统计答案时，只访问这棵树，这意味着一次访问复杂度$\le n$，看起来很大但如果要维持上面那个hack数据的性质，n到100多$\sum s_i$就到极限了，实际耗时并不高。

结果就是我调整了半天数值还是完全卡不掉

希望有人给个卡不掉的证明或者再次卡掉的方法？


------------


题目大意：一开始给出n个字符串**（可能相同）**，每个字符串都有一个权值，最初**都是0**

有两种操作：

**1：**将第i个字符串的权值修改为x

**2：**给出一个字符串s，求n个字符串中**是s的子串的串**的权值的最大值

先观察操作2，要求一组已知串在一个给定串中是否出现，可以通过AC自动机完成，将初始给出的n个字符串建成AC自动机，然后把串s在自动机上跑即可找到所有子串

对于**求权值的最大值**，在每个AC自动机节点上建一个multiset（因为权值会有相同的）用于保存这个点对应串的权值即可

对于操作1：在建AC自动机插入串时，记录一下每个串在哪结尾（这就是保存权值的位置），然后修改时找对对应的multiset先删除原权值再插入新权值即可

**注意multiset在删除时使用s.erase(x)会把所有x都删掉，(test 90好像就是叉这个的)所以要使用s.erase(s.find(x))**

代码
```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<queue>
#include<set>
using namespace std;

int n,m,i,val[300005];

struct node
{
	multiset<int> val;
    int p,v;
    node *chd[26],*fail,*anc;
    node()
    {
        memset(chd,0ll,sizeof(chd));
        fail=anc=0ll;p=v=0;
        val.clear();
    }
};
node *root;
node *place[300005];
void resetAC()
{
    root=new node();
}
char s[300005];
void insert()
{
    node *now=root;
    int l=0,len=strlen(s);
    while(l<len)
    {
        if(now->chd[s[l]-'a']==NULL)
          now->chd[s[l]-'a']=new node();
        now=now->chd[s[l]-'a'];
        l++;
    }
    now->p++;
    place[i]=now;now->val.insert(0);
}
queue<node*> qAC;
void buildAC()
{
    node *now,*q;
    int i;
    for(i=0;i<26;i++)
	  if(root->chd[i]!=NULL)
		root->chd[i]->fail=root,qAC.push(root->chd[i]);
    while(!qAC.empty())
    {
        now=qAC.front();qAC.pop();
        for(i=0;i<26;i++)
          if(now->chd[i]!=NULL)
          {
          	q=now->fail;
          	while(q!=NULL&&q->chd[i]==NULL)
          	  q=q->fail;
          	if(q==NULL)
          	  now->chd[i]->fail=root;
          	else now->chd[i]->fail=q->chd[i],now->chd[i]->anc=(q->chd[i]->val.empty()?q->chd[i]->anc:q->chd[i]);
          	qAC.push(now->chd[i]);
          }
    }
}
int AC()
{
    node *now=root,*p;
    int ans=-1,len=strlen(s);
    for(int l=0;l<len;l++)
    {
        while(now!=root&&now->chd[s[l]-'a']==NULL)
           now=now->fail;
		now=(now->chd[s[l]-'a']==NULL?root:now->chd[s[l]-'a']);
		p=now;
		while(p!=NULL&&p->v!=i)
		{
			if(!p->val.empty())
			{
				auto x=p->val.end();--x;
				ans=max(ans,*x);
			}
			p->v=i;
			p=p->anc;
		}
    }
    return ans;
}

char c;int flag;
void read(int &x)
{
    x=0;c=getchar();flag=1;
    while(c<'0'||c>'9')
      flag=(c=='-'?-1:flag),c=getchar();
    while(c>='0'&&c<='9')
      x=x*10+c-'0',c=getchar();
    x*=flag;
}

int opt; 


int main()
{
    resetAC();
    read(n);read(m);
    for(i=1;i<=n;i++)
	{
		scanf("%s",s);
	    insert();
	}
	buildAC();
	for(i=1;i<=m;i++)
	{
		read(opt);
		if(opt==1)
		{
			int x,vl;
			read(x);read(vl);
			place[x]->val.erase(place[x]->val.find(val[x]));
			val[x]=vl;
			place[x]->val.insert(val[x]);
		}
		if(opt==2)
		{
			scanf("%s",s);
			cout<<AC()<<endl;
		}
	}
    return 0;
}
```


---

## 作者：lory1608 (赞：0)

## CF1437G Death DBMS

一道比较模板的字符串题。

~~本来在考场上15minutes码完，但考试结束后两分钟才调完，没分了。~~

### 题意简述

给出$n,m$，然后给出$n$个字符串，每个字符串都有一个权值，最初权值都为0

然后有$m$个操作，操作有两种类型：

- $\texttt{1 i x}$ 将第i个字符串的权值修改为$x$。
- $\texttt{2 q}$ 给出一个字符串$q$，求所有**是q的子串**的字符串的**权值的最大值**。

$\sum |S_i|\leq 3\times 10^5,\sum |q|\leq 3\times 10^5$。

### 题解

很显然我们可以对$n$个模板串建立广义后缀自动机，然后对于每次询问，只用在$SAM$上匹配，每走一步查询一次当前点到跟的最小值。

显然这都可以用重链剖分+线段树维护，修改只用在线段树上修改即可。

复杂度$O(n\log^2 n)$。

**Hint：这道题有很多细节，需要好好想一下。**

**Hint1：对于一些SAM上相同的串，我们需要找到他最上面的位置，同时将相同的串的权值标记在最上面的位置的multiset中。**

**Hint2：对于到达一个SAM上的点$u$，若当前长度$=now[u]$，我们才从$u$查询，否则从$fa_u$查询。**

**Hint3：在multiset中删值的时候只能删迭代器。**

晚上交的直接删的值，还过了，早上一起来赶紧把自己给hack了。

### hack数据

hack by me

- $\texttt{hack.in}$

```plain
6 15
a
a
a
a
a
a
2 aaaa
1 4 5
2 aaa
1 2 5
1 6 5
2 a
2 aa
1 5 5
2 aa
2 a
1 4 1
2 aaa
1 5 1
1 6 2
2 a
```

- $\texttt{hack.out}$

```plain
0
5
5
5
5
5
5
5
```

这就是CF上的test90，~~顺带叉掉了8个人~~。

### 参考代码

```cpp
#pragma GCC optimize(4)
#include<bits/stdc++.h>
#define FOR(i,a,b) for(int i=a;i<=b;++i)
#define REP(u) for(int i=p[u];i!=-1;i=e[i].nxt)
#define ll long long
#define pb push_back
#define PII pair<int,int>
#define gc getchar()//(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
using namespace std;
char buf[100000],*p1,*p2;
inline int gi()
{
	int x=0,f=1;
	char ch=gc;
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=gc;}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=gc;}
	return (f==1)?x:-x;
}
inline int max(int a,int b){return a<b?b:a;}
inline int min(int a,int b){return a<b?a:b;}
const int maxn=6e5+5;
int fa[maxn],len[maxn],tot=1,last=1,sz,p[maxn],son[maxn][26],pos[maxn],dfn[maxn],siz[maxn],tp[maxn],so[maxn],rel[maxn],val[maxn];
char s[maxn];
struct edge
{
	int v,nxt;
	edge(int vv=0,int nn=0){v=vv,nxt=nn;}
}e[maxn<<1];
inline void add(int u,int v)
{
	e[++sz]=edge(v,p[u]);
	p[u]=sz;
}
struct SAM
{
	inline void insert(int c)
	{
		int np=++tot,p=last;
		len[np]=len[p]+1,last=np;
		while(!son[p][c]&&p)son[p][c]=np,p=fa[p];
		if(!p)fa[np]=1;
		else
		{
			int q=son[p][c];
			if(len[q]==len[p]+1)fa[np]=q;
			else
			{
				int nq=++tot;
				len[nq]=len[p]+1;
				fa[nq]=fa[q];
				fa[q]=fa[np]=nq;
				memcpy(son[nq],son[q],sizeof(son[q]));
				while(p&&son[p][c]==q)son[p][c]=nq,p=fa[p];
			}
		}
	}
}sam;
int n,q;
inline void dfs(int u)
{
	if(len[u]==len[fa[u]]&&u!=1)rel[u]=rel[fa[u]];
	else rel[u]=u;
	siz[u]=1;
	REP(u)
	{
		int v=e[i].v;
		if(v==fa[u])continue;
		dfs(v);
		siz[u]+=siz[v];
		if(siz[v]>siz[so[u]])so[u]=v;
	}
}
inline void dfs2(int u,int topf)
{
	dfn[u]=++tot;
	tp[u]=topf;
	if(so[u])dfs2(so[u],topf);
	REP(u)
	{
		int v=e[i].v;
		if(v==fa[u]||v==so[u])continue;
		dfs2(v,v);
	}
}
struct segmentree
{
	#define ls u<<1
	#define rs u<<1|1
	static const int maxn=3e6+5;
	int maxv[maxn];
	inline void pushup(int u){maxv[u]=max(maxv[ls],maxv[rs]);}
	inline void update(int u,int l,int r,int x,int v)
	{
		if(l==r){return maxv[u]=v,void();}
		int mid=(l+r)>>1;
		if(x<=mid)update(ls,l,mid,x,v);
		else update(rs,mid+1,r,x,v);
		pushup(u);
	}
	inline int query(int u,int l,int r,int x,int y)
	{
		if(x<=l&&y>=r)return maxv[u];
		int ret=-1e9;
		int mid=(l+r)>>1;
		if(x<=mid)ret=query(ls,l,mid,x,y);
		if(y>mid)ret=max(ret,query(rs,mid+1,r,x,y));
		return ret;
	}
}tree;
inline int Query(int u)
{
	int ret=-1e9;
	while(u)
	{
		ret=max(ret,tree.query(1,1,n,dfn[tp[u]],dfn[u]));
		u=fa[tp[u]];
	}
	return ret;
}
multiset<int>ss[maxn];
int main()
{
	memset(p,-1,sizeof(p));
	n=gi(),q=gi();
	FOR(i,1,n)
	{
		last=1;
		scanf("%s",s+1);
		int len=strlen(s+1);
		FOR(j,1,len)sam.insert(s[j]-'a');
		pos[i]=last;
	}
	FOR(i,2,tot)add(fa[i],i);
	int xx=n;
	n=tot;
	tot=0;
	dfs(1);
	dfs2(1,1);
	FOR(i,2,tot)if(i!=rel[i])ss[rel[i]].insert(0);
	FOR(i,1,tot)tree.update(1,1,tot,i,-1e9);
	FOR(i,1,xx)tree.update(1,1,tot,dfn[rel[pos[i]]],0);
	while(q--)
	{
		int typ=gi();
		if(typ==2)
		{
			scanf("%s",s+1);
			int len1=strlen(s+1);
			int now=1,nowlen=0;
			int ans=-1;
			FOR(i,1,len1)
			{
				while(!son[now][s[i]-'a']&&now)now=fa[now],nowlen=len[now];
				if(now==0){now=1;nowlen=0;continue;}
				nowlen++;
				if(son[now][s[i]-'a'])now=son[now][s[i]-'a'];
				if(nowlen==len[now])ans=max(ans,Query(now));///fa[now]
				else ans=max(ans,Query(fa[now]));
			}
			printf("%d\n",ans);
		}
		else
		{
			int id=gi(),x=gi();
			if(pos[id]!=rel[pos[id]])
			{
				auto it=ss[rel[pos[id]]].find(val[pos[id]]);
				ss[rel[pos[id]]].erase(it);
				ss[rel[pos[id]]].insert(val[pos[id]]=x);
			}
			else val[pos[id]]=x;
			if(ss[rel[pos[id]]].size())
			{
				auto it=ss[rel[pos[id]]].end();
				it--;
				x=max(x,*it);
			}
			tree.update(1,1,n,dfn[rel[pos[id]]],max(x,val[rel[pos[id]]]));
		}
	}
	return 0;
}
```

**希望本篇题解能给你带来收获。**



---

