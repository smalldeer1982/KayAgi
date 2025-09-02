# [NEERC 2016] Binary Code

## 题目描述

给定 `n` 个01串，每个字符串至多有一位是未知的，可以填 `0` 或 `1` ，求是否存在一种方案，使得任意一个字符串不是其它任意一个字符串的前缀

## 样例 #1

### 输入

```
4
00?
0?00
?1
1?0
```

### 输出

```
YES
000
0100
11
100
```

## 样例 #2

### 输入

```
3
0100
01?0
01?0
```

### 输出

```
NO
```

# 题解

## 作者：oisdoaiu (赞：20)

注意到每个串只有一个 ? (只有 $2$ 种状态)，所求的是构造方案，所以考虑使用 2-SAT。

于是进一步想到如果 $x_0,y_0$ 一个是另一个的前缀，就 $x_0\to y_1,y_0\to x_1$。

那么容易想到暴力 $n^2$ 建图，下一步显然就是减少边数。

考虑使用 trie，那么对于一个状态 $x_0$ ，设 trie 上对应点为 $cur$，则：

- $x_0$ 连向 $cur$ 的祖先节点的另一个状态(比如说 $cur$ 的祖先中有一个 $y_1$，则连向 $y_0$ )

可以复制一遍 trie，trie 树上儿子连父亲，然后 $x_0\to fa(cur),cur\to x_1$ (这样可以避免连自己)，增加 $m$ 个点($m$ 为 trie 的节点个数)， $m+2n$ 条边。
```cpp
inline void build1(){
    for(register int i=1; i<=trie_cnt; i++) if(fa(i)) Add_Edge(i+node_cnt,fa(i)+node_cnt);
    for(register int i=1, x; i<=n; i++){
        x = loc[0][i]; if(x) Add_Edge(x+node_cnt,Y(i)); if(fa(x)) Add_Edge(N(i),fa(x)+node_cnt);
        x = loc[1][i]; if(x) Add_Edge(x+node_cnt,N(i)); if(fa(x)) Add_Edge(Y(i),fa(x)+node_cnt);
    }
    node_cnt += trie_cnt;
}
```

- $x_0$ 连向 $cur$ 的儿子节点的另一个状态(同上)

还是复制一遍 trie，父亲连儿子，然后 $x_0\to cur, fa(cur)\to x_1$ ，增加 $m$ 个点， $m+2n$ 条边。
```cpp
inline void build2(){
    for(register int i=1; i<=trie_cnt; i++) if(fa(i)) Add_Edge(fa(i)+node_cnt,i+node_cnt);
    for(register int i=1, x; i<=n; i++){
        x = loc[0][i]; if(x) Add_Edge(N(i),x+node_cnt); if(fa(x)) Add_Edge(fa(x)+node_cnt,Y(i));
        x = loc[1][i]; if(x) Add_Edge(Y(i),x+node_cnt); if(fa(x)) Add_Edge(fa(x)+node_cnt,N(i));
    }
    node_cnt += trie_cnt;
}
```

- $x_0$ 连向 $cur$ 对应的其他状态的另一个状态

设点 $cur$ 对应的状态为 $a_1,a_2\cdots$，那么我们要做的就是把 $a_i$ 和 $a_j'$ ( $a_j$ 的对应状态)两两连边，这是一个经典的前缀优化建图模型，增加 $2n$ 个点， $12n$ 条边。
![](https://cdn.luogu.com.cn/upload/image_hosting/cpstf7c5.png)
```cpp
inline void build3(){
    static int tmp[MAXN], num;
    for(register int i=1; i<=trie_cnt; i++){
        num = vec[i].size();
        if(num>=2){
            for(register int j=1; j<=num; j++)
                tmp[j] = vec[i][j-1],
                Add_Edge(tmp[j],j+node_cnt),
                Add_Edge(j+num+node_cnt,tmp[j]^1);
            for(register int j=1; j<num; j++)
                Add_Edge(j+node_cnt,j+1+node_cnt),
                Add_Edge(j+node_cnt,tmp[j+1]^1),
                Add_Edge(tmp[j+1],j+num+node_cnt),
                Add_Edge(j+1+num+node_cnt,j+num+node_cnt);
            node_cnt += num*2;
        }
    }
}
```

然后走一般 2-SAT 流程就行了，输出方案看哪个状态的 $belong$ 小，就选哪个状态。

**一点小细节**

仔细看题，*最多一个"?"*，意思是会有没有 ? 的字符串(样例2)，这种情况可以假设任意一位为 ? ，然后强制这一位选 $0/1$ 。(即 $x_0\to x_1$ 或者 $x_1\to x_0$ )

[完整代码](https://www.luogu.com.cn/paste/m08w0rpy)


---

## 作者：KaisuoShutong (赞：16)

前情提要：本题解代码长度不超过 $\mathtt{2kb}$，不压行不毒瘤，是一篇优秀的小清新题解。

部分思路来自 @Saliеri，大家快来膜她！

## 题意
略。

## 题解
因为只需要前缀匹配，同时又是 $01$ 串，显然可以 trie 扯上关系。  
又注意到 $?$ 最多有一个，显然可以和 2-sat 扯上关系。

考虑如何建图。

注意到，如果选择将某串置为 trie 树上 $x$ 所对应的节点，则 $x$ 在 trie 树上的子树和祖先都不能选。

那么产生了一个 naive 的想法：对于 trie 上的边 $(pa,x)$，连边 $pa\rightarrow x$、$x\rightarrow pa$；同时，对于字符串 $S$ 及其 trie 上对应节点 $x$，连边 $S\rightarrow x$，$x\rightarrow opp(S)$。  
有问题？不用慌，这个肯定有问题，我们一个一个来解决。

首先会发现在一张图上连上行下行的结果就是：  
![](https://cdn.luogu.com.cn/upload/image_hosting/il9ox3pv.png)  
那么考虑限制其只能上/下，容易想到拆成两张图，分别连。

然后你就会发现：  
![](https://cdn.luogu.com.cn/upload/image_hosting/6r505n9p.png)  
其中 $x$，$y$ 分别是 trie 树上 $S$ 和 $S$ 的反面 $S'$ 对应的节点。

咋办？不连不就完事了！  
让 $S\rightarrow pa(x)/son(x)$ 即可解决。

你接着发现不对，如果有多个 $S$ 对应的是一个 $x$，咋办呢？  
独立于 trie 之外，单独拎出来搞？暴力会被卡到 $O(n^2)$，所以再整一前后缀优化建图？

太麻烦。想想，**你的暴力真的会被卡到 $O(n^2)$ 吗**？如果一个串出现超过 $3$ 次，这个图真的还能有解吗？  
显然不能！所以一个字符串最多出现两次。

除了这个，还能怎么卡？只能将某字符串的所有位置依次换上 $?$，这样数据大小为长度的平方的唉？总长度又保证了在 $5\times 10^5$ 以内，那不就说明我时间复杂度为平方的建图也在 $5\times 10^5$ 范围？

[怒号光明.jpg](https://cdn.luogu.com.cn/upload/image_hosting/8ri3s40m.png)

有了这个，直接暴力建图就得了。  
还要加上个 hash 判一下相同字符串，不过你直接 `map<string,int>` 这题也没卡。

完结撒愤怒，点个赞吧。  
放个上面承诺的 $\mathtt{2kb}$ 代码。

```cpp
//月亮照耀青窗，窗里窗外皆有青色的光。
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
const int maxn = 3e6+10;
#define opp(x) (x>n?x-n:x+n)
vector<int>g[maxn];int qa,n,tot,dfn[maxn],low[maxn],dfx,B[maxn],iss[maxn],q[maxn],scc;
void ADD(int x,int y) {g[x].push_back(y);}
void tar(int x) {
	dfn[x]=low[x]=++dfx,iss[x]=1,q[++q[0]]=x;
	for(auto y:g[x])
		if(!dfn[y]) tar(y),low[x]=min(low[x],low[y]);
		else if(iss[y]) low[x]=min(low[x],dfn[y]);
	if(dfn[x]==low[x]) for(++scc;B[q[q[0]]]=scc,iss[q[q[0]]]=0,q[q[0]--]^x;);
}
char SCC() {for(int i=1;i<=tot;i++) if(!dfn[i]) tar(i);for(int i=1;i<=n;i++) if(B[i]==B[n+i]) return 0;return 1;}
void CLS() {for(int i=1;i<=tot;i++) dfn[i]=low[i]=0;dfx=scc=0;}
int rt,ch[maxn][2],N[maxn];
vector<int>ve[maxn];
void ins(char*S,int nm) {
	int x=rt;
	for(int i=0;S[i];i++) x=(ch[x][S[i]^48]?ch[x][S[i]^48]:ch[x][S[i]^48]=++tot);
	ve[x].push_back(nm);
}
void byd(int x,int pa) {
	if(!x) return;N[x]=++tot;
	if(pa) ADD(x,pa),ADD(N[pa],N[x]);
	for(auto y:ve[x]) ADD(y,pa),ADD(x,opp(y)),ADD(N[x],opp(y));
	for(auto y:ve[pa]) ADD(y,N[x]);
	for(auto y:ve[x])
		for(auto z:ve[x]) if(y^z) ADD(y,opp(z));
	byd(ch[x][0],x),byd(ch[x][1],x);
}
char S[maxn];string s[maxn];
unordered_map<ull,int>mp;
ull has(char*S) {ull r=0;for(int i=0;S[i];i++) r=r*137+S[i];return r;}
signed main() {
	scanf("%d",&n),rt=tot=(n<<1|1);
	for(int i=1;i<=n;i++) {
		scanf("%s",S),s[i]=S;if(++mp[has(S)]==3) return cout<<"NO\n",0;
		for(int j=0;;j++)
			if(!S[j]) {ins(S,i),ins(S,n+i);break;}
			else if(S[j]=='?') {S[j]='0',ins(S,i),S[j]='1',ins(S,n+i);break;}
	}byd(rt,0);
	if(SCC()) {
		cout<<"YES\n";
		for(int i=1;i<=n;i++)
			for(int j=0;;j++)
				if(!s[i][j]) {cout<<s[i]<<'\n';break;}
				else if(s[i][j]=='?') {s[i][j]='0'+(B[i]>B[n+i]);cout<<s[i]<<'\n';break;}
	} else cout<<"NO\n";
	return 0;
}
```

---

## 作者：Alex_Wei (赞：15)

### *[P6965 [NEERC2016] Binary Code](https://www.luogu.com.cn/problem/P6965)

一个字符串至多含有一个问号，所以状态至多有两种，考虑 2-SAT，设 $x_i$ 表示第 $i$ 个字符串的问号填 $0$，$\lnot x_i$ 表示第 $i$ 个字符串的问号填 $1$。现在我们有 $2n$ 个字符串和 $2n$ 个文字，它们之间一一对应。

容易发现，若字符串 $s$ 是 $t$ 的前缀，则若 $s$ 对应文字为真，则 $t$ 对应文字为假；若 $t$ 对应文字为真，则 $s$ 对应文字为假。这说明若 $s$ 则非 $t$，若 $t$ 则非 $s$。

刻画前缀关系的结构是字典树。对于若 $s$ 则非 $t$ 的限制，我们需要从 $s$ 向它的子树内所有字符串的 **否定** 连边。对于若 $t$ 则非 $s$ 的限制，我们需要从 $t$ 向它的祖先对应的所有字符串的 **否定** 连边。因此，建出根向字典树和叶向字典树。在两棵字典树上，每个字符串对应的状态向它对应文字的否定连边。为防止出现 $s$ 和 $t$ 对应同一字符串的情况，在叶向字典树上，$s$ 对应文字只能向它对应状态的两个儿子连边，否则 $s$ 会向 $s$ 的否定连边，导致必然无解。同理，在根向字典树上，$s$ 对应文字向它对应节点的父亲（而非它本身）连边。

我们还要处理 $s = t$ 但对应不同字符串的情况。容易发现，将相等的字符串排成一行，每个字符串会向所有除了它本身的其它字符串的 **否定** 连边，可以通过前缀后缀优化建图做到。

综上，点数和边数关于 $n$ 和字典树大小 $m$ 线性。点数不超过 $4n + 2m$，而 $m \leq 2n$，所以边数不超过 $8n$。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define TIME 1e3 * clock() / CLOCKS_PER_SEC
using ll = long long;
using pii = pair<int, int>;
bool Mbe;
constexpr int N = 3e6 + 5;
int n, node, trie, son[N][2], fa[N], ed[N], pos[N], qm[N];
vector<int> e[N], buc[N], pref[N], suff[N];
string s[N];
void insert(int id, string s) {
  int p = n * 2;
  for(char it : s) {
    if(!son[p][it - '0']) {
      e[p].push_back(trie), e[trie ^ 1].push_back(p ^ 1);
      fa[son[p][it - '0'] = trie] = p, trie += 2;
    }
    p = son[p][it - '0'];
  }
  ed[id] = p, pos[id] = buc[p].size();
  buc[p].push_back(id ^ 1);
  e[p].push_back(id ^ 1), e[p ^ 1].push_back(id ^ 1);
}
int dfn[N], dn, low[N], vis[N], col[N], cn, stc[N], top;
void tarjan(int id) {
  dfn[id] = low[id] = ++dn, stc[++top] = id, vis[id] = 1;
  for(int it : e[id]) {
    if(!dfn[it]) tarjan(it), low[id] = min(low[id], low[it]);
    else if(vis[it]) low[id] = min(low[id], dfn[it]);
  }
  if(low[id] == dfn[id]) {
    col[id] = ++cn;
    while(stc[top] != id) col[stc[top]] = cn, vis[stc[top--]] = 0;
    vis[stc[top--]] = 0;
  }
}
bool Med;
int main() {
  fprintf(stderr, "%.3lf MB\n", (&Mbe - &Med) / 1048576.0);
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> n, trie = n * 2 + 2;
  for(int i = 0; i < n; i++) {
    cin >> s[i], qm[i] = s[i].find('?');
    if(qm[i] == -1) insert(i * 2, s[i]), insert(i * 2 + 1, s[i]);
    else s[i][qm[i]] = '0', insert(i * 2, s[i]), s[i][qm[i]] = '1', insert(i * 2 + 1, s[i]);
  }
  node = trie;
  for(int i = n * 2; i < trie; i += 2) {
    if(buc[i].empty()) continue;
    int sz = buc[i].size();
    pref[i].resize(sz), suff[i].resize(sz);
    for(int p = 0; p < sz; p++) {
      if(p) e[node].push_back(node - 1);
      e[node].push_back(buc[i][p]);
      pref[i][p] = node++;
    }
    for(int p = sz - 1; ~p; p--) {
      if(p + 1 < sz) e[node].push_back(node - 1);
      e[node].push_back(buc[i][p]);
      suff[i][p] = node++;
    }
  }
  for(int i = 0; i < n * 2; i++) {
    int p = ed[i];
    if(son[p][0]) e[i].push_back(son[p][0]);
    if(son[p][1]) e[i].push_back(son[p][1]);
    e[i].push_back(fa[p] ^ 1);
    int q = pos[i];
    if(q) e[i].push_back(pref[p][q - 1]);
    if(q + 1 < buc[p].size()) e[i].push_back(suff[p][q + 1]);
  }
  for(int i = 0; i < node; i++) if(!dfn[i]) tarjan(i);
  for(int i = 0; i < n; i++) {
    if(col[i * 2] == col[i * 2 + 1]) puts("NO"), exit(0);
    if(qm[i] != -1) s[i][qm[i]] = col[i * 2] < col[i * 2 + 1] ? '0' : '1';
  }
  cout << "YES\n";
  for(int i = 0; i < n; i++) cout << s[i] << "\n";
  cerr << TIME << " ms\n";
  return 0;
}
```

---

## 作者：panyf (赞：9)

注意到关键性质：每个串至多包含一个问号。因此每个串至多只有两种状态，可以用 bool 变量表示。

于是想到 2-SAT。但是两两枚举点对建图会超时。

注意到串的总长不超过 $5\times10^5$，可以对每个串的所有前缀建一个新点。建点的过程可以用 hash 或字典树实现。

选了一个串就不能选它的前缀，因此要向它的所有前缀连边。用前缀优化建图的套路可以将边数优化到线性。

然而这样建图不能处理相同串的情况，还要在相同串之间连边，同样可以前缀优化建图。

时间复杂度 $O(n+\sum|S|)$，代码实现细节较多。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ul unsigned long long
const ul P=1ll<<60|7;
const int A=5e5+7,B=3e6+7,N=6e6+7,M=1e7+7;
#define Y(x) ((x)*2)
#define N(x) ((x)*2+1)
int t,o,m,he[N],to[M],ne[M],lo[N],id,bl[N],ct,st[N],tp,p[A],a[A],pr[N],v[B];
string s[A];
unordered_map<ul,int>mp;
void add(int x,int y){ne[++t]=he[x],to[t]=y,he[x]=t;}
void ins(int x,int y){add(x,y),add(y^1,x^1);}
void tar(int x){//Tarjan 求强连通分量
	int p=++id,i=he[x],j;
	for(lo[st[++tp]=x]=p;i;i=ne[i])if(!lo[j=to[i]])tar(j),lo[x]=min(lo[x],lo[j]);else if(!bl[j])lo[x]=min(lo[x],lo[j]);
	if(lo[x]==p)for(++ct;bl[st[tp]]=ct,st[tp--]!=x;);
}
void g1(ul u,int k){//向前缀连边
	if(!mp[u]){
		int p=++m;
		if(mp[u]=++m,pr[Y(m)]=p,ins(Y(m),Y(p)),k)ins(Y(pr[Y(k)]),Y(p)),ins(Y(m),N(pr[Y(k)]));
	}
}
void g2(int k,int a){//相同串连边
	ins(a,Y(pr[a]=++m)),ins(a,Y(k));
	if(v[k])ins(Y(v[k]),Y(m)),ins(a,N(v[k]));
	v[k]=m;
}
int main(){
	int n,i,j,k,l;
	ul u;
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0),cin>>n;
	for(i=1;i<=n;++i){
		if(cin>>s[i],p[i]=s[i].find('?'),a[i]=++m,l=s[i].size(),~p[i])s[i][p[i]]='0';
		for(u=j=k=0;j<l;k=mp[u],++j)g1(u=(u*7+s[i][j])%P,k);
		if(g2(k,Y(a[i])),~p[i]){
			for(u=j=k=0,s[i][p[i]]='1';j<l;k=mp[u],++j)g1(u=(u*7+s[i][j])%P,k);
			g2(k,N(a[i]));
		}else add(N(a[i]),Y(a[i]));
	}
	for(i=0;i<N;++i)if(!lo[i])tar(i);
	for(i=1;i<=m;++i)if(bl[Y(i)]==bl[N(i)])return cout<<"NO\n",0;
	for(i=1,cout<<"YES\n";i<=n;cout<<s[i++]<<'\n')if(~p[i]&&bl[Y(a[i])]<bl[N(a[i])])s[i][p[i]]='0';
	return 0;
}
```


---

## 作者：Starlight237 (赞：6)

> (**2021集训队作业 P6965 【[NEERC2016]Binary Code】**)给定 $n$ 个总长度不超过 $5\times10^5$ 的二进制串，每个串中最多有一个位置不确定（标记为 $\texttt{?}$），求一种替换问号的方案使得这些串中没有任何一个是另一个的前缀，或输出无解。

对于第一次接触相关套路的人来说细节较多，~~我两三个小时才完全捋清楚。~~

记 $(i,t)$ 表示串 $s_i$ 的问号填了 $t(t\in\{0,1\})$ 后形成的串，将不超过 $2n$ 个串 $(i,t)$ 插入 Trie，题目所求即等价于在其中选择 $n$ 个点（对每个 $s_i$，从 $(i,0),(i,1)$ 中恰好选择一个点），使得它们互不为祖先关系。

考虑 2-SAT，$u\rightarrow v$ 表示若选了 $u$ 则必然选 $v$。若 $v$ 是 $u$ 的祖先，则应当有路径 $u \leadsto \neg v$。如果暴力直接连边显然会 `MLE+TLE`，可以考虑将 $u$ 连接到 Trie 上对应的点，再把 $v$ 在 Trie 上的定点连接到 $\neg v$。对于 Trie 上的点，由儿子连向父节点。

但是注意到这样连边有个问题，会出现 $(i,t)\rightarrow u\rightarrow(i,\neg t)$ 的连边，这是矛盾的。

我们考虑一个替代方案：若 Trie 中一个点上有 $m$ 个串，则把这个结点拆成 $m$ 个小结点，首先从大结点到所有小结点连一条边。设 $(i,t)$ 对应的小结点为 $u$，则对于其他 $m-1$ 个小结点 $v\not=u$，连接 $(i,t)\rightarrow v$。然后正常连所有小结点到 $(i,\neg t)$ 的边。易见此时就不存在 $(i,t)\leadsto(i,\neg t)$ 的路径了，矛盾被解决了。然后所有小结点全部连向大结点的父亲大结点。

然而这样边数极多，依然会 `MLE+TLE`。考虑前后缀优化建边（这里采用前缀的写法），设 $m$ 个小结点分别为 $v_1,v_2,...,v_m$，我们首先连所有边 $v_{i+1}\rightarrow v_i$，那么从某个 $s$ 连接到 $v_i$ 就等价于同时连接 $v_1,...,v_i$，类似地，从 $v_i,...,v_m$ 同时连接到 $s$ 就等价于从 $v_i$ 连接到 $s$。

然后就可以来优化上面的建边过程了。设 $(i,t)$ 对应结点 $v_j$（改用 j 是为了防止名称歧义），则目的是从 $(i,t)$ 连向所有 $v_k(k\not=j)$。注意到 $u\rightarrow\neg v$ 和 $v\rightarrow \neg u$ 中只要有一个就足够表达互斥关系，我们约定从编号较小的大节点对应的串连向编号较小的小节点，也就是从 $(i,t)$ 连向 $v_1,...,v_{j-1}$。因此转化为从 $(i,t)$ 连向 $v_{j-1}$（前缀优化建边），类似地，对于另一个方向，我们约定从编号较大的小节点连向编号较小的小节点对应的串（的取反），也就是从 $v_j,...,v_m$ 连向 $(i,\neg t)$，前缀优化建边之后转变为从 $v_j$ 连向 $(i,\neg t)$。

对于没有问号的情况，随便钦定一个问号，假设问号处原来是 $t$，连接 $(i,\neg t)\rightarrow(i,t)$ 即可。这样就只能选 $t$ 了。

小技巧：由抽屉原理稍加分析可以得出，字符串数量超过 $10^5$ 时可以直接输出无解。

```cpp
#define P(x) (((x) << 1) - 1) // 原命题
#define Q(x) ((x) << 1) // 反命题
#define neg(x) ((((x) - 1) ^ 1) + 1)
const int N = 1e6 + 10;
int n, lst[N], zero[N], one[N];
char s[N];
vector<int> vec[N];
struct Trie {
	int tot, ch[N][2], c[N], fa[N];
	char outp[N], *tt;
	Trie() : tot(1) {}
	inline int insert(const char *s) {
		int ptr = 1, len = strlen(s);
		for (int i = 0, t; i < len; ++i) {
			t = s[i] - 48 & 1;
			if (ch[ptr][t]) ptr = ch[ptr][t];
			else ++tot, fa[tot] = ptr, c[tot] = t, ptr = ch[ptr][t] = tot;
		}
		return ptr;
	}
	inline void print(int ptr) {
		tt = outp;
		while (ptr != 1) *tt++ = c[ptr] + 48, ptr = fa[ptr];
		do putchar(*--tt); while (tt != outp);
		putchar('\n');
	}
} tr;
namespace SAT {
	const int M = N << 2;
	vector<int> eg[M];
	inline void addedge(int u, int v) {eg[u].push_back(v), eg[neg(v)].push_back(neg(u));}
	int tot, dfn[M], low[M], bl[M], mch[M], tmp[M], res[M], tim, cnt;
	bool ins[M];
	stack<int> S;
	void tarjan(int x) {
		dfn[x] = low[x] = ++tim, ins[x] = true, S.push(x);
		for (int v : eg[x])
			if (!dfn[v]) tarjan(v), low[x] = min(low[x], low[v]);
			else if (ins[v]) low[x] = min(low[x], dfn[v]);
		if (dfn[x] == low[x]) {
			int y; ++cnt;
			do y = S.top(), ins[y] = false, bl[y] = cnt, S.pop(); while (y != x);
		}
	}
	inline bool solve() {
		for (int i = 1; i <= tot; ++i)
			if (!dfn[i]) tarjan(i);
		for (int i = 1, u, v; i <= tot; i += 2) {
			if (bl[i] == bl[i + 1]) return false;
			mch[i] = i + 1, mch[i + 1] = i;
		}
		for (int i = 1; i <= tot; ++i)
			res[i] = bl[i] < bl[mch[i]] ? 1 : -1;
		return true;
	}
}
int main() {
	ios :: sync_with_stdio(0), cin.tie(0);
	cin >> n;
	if (n > 100000) return puts("NO"), 0;
	for (int i = 1; i <= n; ++i) {
		cin >> s; int len = strlen(s);
		int pos = find(s, s + len, '?') - s;
		if (pos != len) s[pos] = 48, zero[i] = tr.insert(s), s[pos] = 49, one[i] = tr.insert(s);
		else zero[i] = tr.insert(s), SAT :: addedge(Q(i), P(i));
		vec[zero[i]].push_back(P(i));
		if (one[i]) vec[one[i]].push_back(Q(i));
	}
	int num = n + tr.tot;
	for (int i = 2; i <= tr.tot; ++i) {
		lst[i] = tr.fa[i] + n;
		for (int j = 0, k = vec[i].size(); j < k; ++j) {
			SAT :: addedge(vec[i][j], P(lst[i]));
			SAT :: addedge(P(num + j + 1), neg(vec[i][j]));
			SAT :: addedge(P(num + j + 1), P(lst[i]));
			lst[i] = num + j + 1;
		}
		num += vec[i].size();
	}
	for (int i = 2; i <= tr.tot; ++i)
		SAT :: addedge(P(i + n), P(lst[i]));
	SAT :: tot = num << 1;
	if (!SAT :: solve()) return puts("NO"), 0;
	puts("YES");
	for (int i = 1; i <= n; ++i)
		tr.print(SAT :: res[P(i)] == 1 ? zero[i] : one[i]);
	return 0;
}
```

---

## 作者：Leasier (赞：4)

前置芝士：[2-SAT](https://oi-wiki.org/graph/2-sat/)、[Trie 树](https://oi-wiki.org/string/trie/)

看到一个字符串中至多一个 `?`，容易想到 2-SAT。对于那些没有 `?` 的字符串，我们钦定一个位置有 `?` 并强制选择其本来的字符。

看到字符串的前缀，容易想到 Trie 树。一个字符串 $a$ 是另一个字符串 $b$ 的前缀，当且仅当 $a$ 最后一个字符所在节点是 $b$ 最后一个字符所在节点的祖先。

于是我们似乎口胡出来了：将一个字符串拆成两个点，分别代表 `?` 处填 `0` 和 `1` 时所得的字符串。

接下来就是实现方面的问题了。

1. 如何实现对于一个节点，选了以它结尾的字符串就不能选以它的祖先结尾的字符串？

树上前缀优化建图即可。

2. 如何实现对于一个节点，以它结尾的字符串至多只能选一个？

前后缀优化建图即可。

3. 如何实现对于一个节点，选了以它结尾的字符串就不能选以它子树中（除了它本身）的节点结尾的字符串？

对于每一个 Trie 树上的节点，新建一个点表示不能选它子树中的节点结尾的字符串即可。

综上，时间复杂度为 $O(n + \sum |S|)$。~~其实常数还蛮大的（~~

代码：
```cpp
#include <iostream>
#include <stack>
#include <vector>
#include <cstdio>
#include <cstring>

using namespace std;

typedef struct {
	int other;
	int son[7];
} Node;

typedef struct {
	int nxt;
	int end;
} Edge;

int dot_id = 1, cnt = 0;
int blank[500007], fa[2000007], id[500007][7], head[5000007], pos[2000007], subtree[2000007], pre[2000007], dfn[5000007], low[5000007], belong[5000007];
char s[500007];
bool mark[2000007], vis1[5000007], vis2[5000007];
Node tree[2000007];
Edge edge[9000007];
stack<int> stk;
vector<int> v1[2000007], v2[2000007], v3[2000007];
vector<string> v4;

inline void add_edge(int start, int end){
	cnt++;
	edge[cnt].nxt = head[start];
	head[start] = cnt;
	edge[cnt].end = end;
}

inline int insert(char s[]){
	int len = strlen(&s[1]), pos = 1;
	for (register int i = 1; i <= len; i++){
		int ch = s[i] - '0';
		if (tree[pos].son[ch] == 0){
			dot_id++;
			tree[pos].son[ch] = dot_id;
			fa[dot_id] = pos;
		}
		pos = tree[pos].son[ch];
	}
	dot_id++;
	fa[dot_id] = pos;
	mark[dot_id] = true;
	v1[pos].push_back(dot_id);
	return dot_id;
}

void tarjan(int u, int &id, int &scc_cnt){
	dfn[u] = low[u] = ++id;
	vis1[u] = vis2[u] = true;
	stk.push(u);
	for (register int i = head[u]; i != 0; i = edge[i].nxt){
		int x = edge[i].end;
		if (!vis1[x]){
			tarjan(x, id, scc_cnt);
			low[u] = min(low[u], low[x]);
		} else if (vis2[x]){
			low[u] = min(low[u], dfn[x]);
		}
	}
	if (dfn[u] == low[u]){
		int cur;
		scc_cnt++;
		do {
			cur = stk.top();
			stk.pop();
			vis2[cur] = false;
			belong[cur] = scc_cnt;
		} while (cur != u);
	}
}

int main(){
	int n, dfn_id = 0, scc_cnt = 0, t;
	scanf("%d", &n);
	for (register int i = 1; i <= n; i++){
		int len;
		scanf("%s", &s[1]);
		len = strlen(&s[1]);
		blank[i] = -1;
		v4.push_back((string)&s[1]);
		for (register int j = 1; j <= len; j++){
			if (s[j] == '?'){
				blank[i] = j;
				break;
			}
		}
		if (blank[i] == -1){
			id[i][0] = insert(s);
			s[1] = s[1] == '0' ? '1' : '0';
			id[i][1] = insert(s);
			add_edge(id[i][1], id[i][0]);
		} else {
			s[blank[i]] = '0';
			id[i][0] = insert(s);
			s[blank[i]] = '1';
			id[i][1] = insert(s);
		}
		tree[id[i][0]].other = id[i][1];
		tree[id[i][1]].other = id[i][0];
	}
	t = dot_id;
	for (register int i = 1; i <= t; i++){
		if (mark[i]){
			if (tree[fa[i]].other == 0) tree[fa[i]].other = ++dot_id;
			add_edge(tree[fa[i]].other, tree[i].other);
		}
	}
	for (register int i = t; i >= 1; i--){
		if (!mark[i]){
			subtree[i] = ++dot_id;
			if (tree[i].other != 0) add_edge(subtree[i], tree[i].other);
			if (tree[i].son[0] != 0) add_edge(subtree[i], subtree[tree[i].son[0]]);
			if (tree[i].son[1] != 1) add_edge(subtree[i], subtree[tree[i].son[1]]);
		}
	}
	for (register int i = 1; i <= t; i++){
		if (!mark[i]){
			int size = v1[i].size(), cur_id = ++dot_id;
			v2[i].resize(size);
			v3[i].resize(size);
			for (register int j = 0; j < size; j++){
				pos[v1[i][j]] = j;
				v2[i][j] = ++dot_id;
				v3[i][j] = ++dot_id;
				if (tree[i].son[0] != 0) add_edge(v1[i][j], subtree[tree[i].son[0]]);
				if (tree[i].son[1] != 0) add_edge(v1[i][j], subtree[tree[i].son[1]]);
			}
			for (register int j = 0; j < size; j++){
				add_edge(v2[i][j], tree[v1[i][j]].other);
				add_edge(v3[i][j], tree[v1[i][j]].other);
				if (j > 0) add_edge(v2[i][j], v2[i][j - 1]);
				if (j + 1 < size) add_edge(v3[i][j], v3[i][j + 1]);
			}
		}
	}
	for (register int i = 1; i <= t; i++){
		if (!mark[i]){
			pre[i] = ++dot_id;
			if (tree[i].other != 0) add_edge(pre[i], tree[i].other);
			if (fa[i] != 0) add_edge(pre[i], pre[fa[i]]);
		} else {
			if (pos[i] > 0) add_edge(i, v2[fa[i]][pos[i] - 1]);
			if (pos[i] + 1 < v1[fa[i]].size()) add_edge(i, v3[fa[i]][pos[i] + 1]);
			if (fa[fa[i]] != 0) add_edge(i, pre[fa[fa[i]]]);
		}
	}
	for (register int i = 1; i <= dot_id; i++){
		if (!vis1[i]) tarjan(i, dfn_id, scc_cnt);
	}
	for (register int i = 1; i <= n; i++){
		if (belong[id[i][0]] == belong[id[i][1]]){
			printf("NO");
			return 0;
		}
	}
	printf("YES\n");
	for (register int i = 1; i <= n; i++){
		int i_d = i - 1;
		if (blank[i] != -1){
			if (belong[id[i][0]] < belong[id[i][1]]){
				v4[i_d][blank[i] - 1] = '0';
			} else {
				v4[i_d][blank[i] - 1] = '1';
			}
		}
		printf("%s\n", v4[i_d].c_str());
	}
	return 0;
}
```

---

## 作者：Saliеri (赞：3)

注意到，每一个串最多中有一个问号，那么至多只会有两种选择。而前缀的限制则会对选择进行限制，于是考虑 **2-SAT**。

为了方便地处理前缀关系，我们将所有可能出现的字符串建成 Trie，那么选择一个字符串后所有的限制就是不能选结尾在其结尾结点的**子树内或祖先上**的字符串。

直接暴力建图复杂度边数可能达到 $O(n^2)$，考虑优化建图。

我们考虑前缀优化建图的思想——通过**成前缀关系的辅助中转点**来指向所有需要指的点。

可以发现，这个思想可以很容易的扩展到树上。

我们建立两颗与 Trie 树形态完全一致的辅助树，第一颗树边向上指，第二颗树边向下指。

对于这两颗辅助树的每一个节点，都指向所有结尾在 这个节点对应的原 Trie 节点 的字符串的反面。（0 指 1，1 指 0）

最后将每一个字符串连向两颗辅助树上与这个字符串的结尾节点对应的点即可。

容易看出这样的边数是线性的。

但是，我们忽略了一点，正面对应的辅助树上的点会指向反面，反面对应的点也会指向正面——无论如何都会有环的存在而导致 `No`。

解决方案是，在最后一步中，每一个字符串连向：第一颗辅助树上的父亲、第二颗辅助树上的儿子。这样我们就规避了上文的情况。

但是，这样也会出现问题：如果一个 Trie 树节点是多个字符串的结尾，这些串内部是有限制关系的，然而这样建图没有考虑。

没考虑补上就是了。接下来有两种想法：

较为无脑的是：因为每个节点上是形如 **一组节点至多选一个** 的限制，这很符合经典**前缀优化建图**的形式，于是我们对于每一个节点内部再做一遍前缀优化建图即可。

另一种想法是：一个节点上的字符串数真的可能到达 $O(n)$ 吗？其实是不会的。于是我们考虑每个节点内部**暴力建图**。 

我们首先特判掉 $> 2$ 个字符串（指可能包含 '?' 的初始字符串）完全相等的情况，直接输出 `No` 即可。

对于长度 $> \sqrt {|S|}$ 的串，不会超过 $\sqrt{|S|}$ 个，暴力总复杂度线性。

对于长度 $\le \sqrt{|S|}$ 的串：

我们可以发现：能到达同一个结尾节点的串的形式必然是——在某一个基础串上**替换一位为 '?'**，或不替换。

于是，到达一个节点的字符串的数量级不会超过字符串的长度，也就是 $\sqrt{|S|}$，于是暴力建图依旧是线性的。

于是我们直接暴力建图是对的！

___

代码：

长度 `2.09k` ，供参考。

```cpp
#include <bits/stdc++.h>
#define pb push_back
using namespace std;
const int maxn = 5e5+5,maxs = 1e6+5,N = 3e6+5;
int n,qmpos[maxn],edp[maxn<<1];
string s[maxn];
std :: map<string,int> oc;
int fa[maxs],ch[maxs][2],nods = 1;
std :: vector<int> strs[maxs];
void ins(string &s,int id){
	int now = 1;
	for(char c:s)(ch[now][c-'0']?0:fa[ch[now][c-'0']=++nods]=now),now = ch[now][c-'0'];
	edp[id] = now,strs[now].push_back(id);
}
std :: vector <int> G[N];
int tot,cpyid[maxs][2];
int Bu(int u){
	int id = ++tot;for(int v:strs[u])G[id].pb(v>n?v-n:v+n);
	if(ch[u][0])G[Bu(ch[u][0])].pb(id);if(ch[u][1])G[Bu(ch[u][1])].pb(id);
	return cpyid[u][0] = id;
}
int Bd(int u){
	int id = ++tot;for(int v:strs[u])G[id].pb(v>n?v-n:v+n);
	if(ch[u][0])G[id].pb(Bd(ch[u][0]));if(ch[u][1])G[id].pb(Bd(ch[u][1]));
	return cpyid[u][1] = id;
}
void Link(int u){
	int up = edp[u];
	if(fa[up])G[u].pb(cpyid[fa[up]][0]);
	if(ch[up][0])G[u].pb(cpyid[ch[up][0]][1]);
	if(ch[up][1])G[u].pb(cpyid[ch[up][1]][1]);
}
int dfn[N],low[N],st[N],vis[N],b[N],tim,cnt,top;
void Tarjan(int u){
	dfn[u] = low[u] = ++tim,st[++top] = u,vis[u] = 1;
	for(int v:G[u]){
		if(!dfn[v])Tarjan(v),low[u] = min(low[u],low[v]);
		else if(vis[v])low[u] = min(low[u],dfn[v]);
	}
	if(low[u] == dfn[u]){
		int now;++cnt;
		do{now = st[top--],vis[now] = 0,b[now] = cnt;}while(now^u);
	}
}
int main(){
	ios::sync_with_stdio(0);cin >> n;
	for(int i=1,p,tv;i<=n;++i){
		cin >> s[i];p = s[i].find('?');
		if(((tv = ++oc[s[i]]) > 1 && p == -1)|| tv > 2)return (cout<<"NO\n"),0;
		if(~p)qmpos[i] = p;
		else (s[i][0]=='1'?G[i].pb(i+n):G[i+n].pb(i)),p = qmpos[i] = 0;
		s[i][p] = '0',ins(s[i],i),s[i][p] = '1',ins(s[i],i+n);
	}
	for(int u=1;u<=nods;++u)
		for(int i:strs[u])
			for(int j:strs[u])
				if(i != j)G[i].push_back((j>n?j-n:j+n));
	tot = 2*n,Bu(1),Bd(1);
	for(int i=1;i<=2*n;++i)Link(i);
	for(int i=1;i<=tot;++i)if(!dfn[i])Tarjan(i);
	for(int i=1;i<=n;++i)if(b[i] == b[i+n])return (cout<<"NO\n"),0;
	cout << "YES\n";
	for(int i=1;i<=n;++i)
		s[i][qmpos[i]] = (b[i]>b[i+n])+'0',cout << s[i] << '\n';
	return 0;
}
```




---

## 作者：比利♂海灵顿 (赞：3)

# P6965 NERRC2016 Binary Code

传送门: [P6965](https://www.luogu.com.cn/problem/P6965) + [LOJ6036](https://loj.ac/p/6036)

树链剖分优化建图，复杂度 $O(n\log^2n)$，[开了 `-O2` 跑得真不慢](https://www.luogu.com.cn/record/58780653)。

## 题意

有 $n$ 个二进制串，每个串最多有一位是 `?`。

你要给 `?` 填上 `0/1`，使得不存在 $i$，$j$ 使 $s_i$ 是 $s_j$ 的前缀。

洛谷上要输出方案，而 LOJ 只需要判断可行性，相当于弱化版，所以这里只放 P6965 的做法。

## 做法 

将每个字符串 `?` 取 `0` 和 `1` 的情况都存到 Trie 里。

我们发现，如果选了一个节点，那么它子树上的节点都不能选，它到根的路径上的节点也不能选，所以我们要往这些点的对应点上连边。

我们知道有线段树优化建边，当线段树从序列上放到 Trie 上，就需要树链剖分了，(显然我没有想到可以只连父子)

树链剖分建边是 $O(n\log^2n)$，对于常数极大的线性算法，这个算法增加的 $\log^2n$ 的复杂度没有明显地比别的算法慢，只是不开 `-O2` 会超时，但是开了 `-O2` 便跑到了最优解第一页的前半部分。

建边之后跑 2-SAT 即可。

## 代码实现

我觉得这份代码最妙的地方莫过于在递归过程中计算线段树区间长度，然后用 `vector` 存图，实现了线段树和有向图的无缝衔接，这虽然对数组来说是很正常的事，但是对于指针来说，少定义两个结构体 (存边和存线段树) 确实大大减少了代码难度。

```cpp
unsigned m, n, n2;
unsigned A, B, C, D, t;
unsigned Tmp(0);
unsigned DFSCnt(1), STop(0), SCC(0);
char TmpI[500005], UnSur[500005], Cr(0), Flg(0);
vector<char> Ans[500005];
struct Trie;
struct Node {
  vector<Node*> To;
  Trie* Tr;
  unsigned Bel, Low, DFSr;
  char InS;
}N[2000005], * List[2000005], * CntN, * Frm, * Root;
struct Trie {
  Trie* Son[2], * Top, * Fa;
  unsigned RL, RR, Size, Cnt;
  char Heavy;
  inline void PreDFS() {
    unsigned Mx(0);
    if (Son[0]) Son[0]->Fa = this, Son[0]->PreDFS(), Heavy = 0, Mx = Son[0]->Size;
    if (Son[1]) {
      Son[1]->Fa = this, Son[1]->PreDFS();
      if (Son[1]->Size > Mx) Heavy = 1;
    }
  }
  inline void DFS() {
    RL = DFSCnt, RR = RL + Cnt - 1, DFSCnt += Cnt;
    if (!Son[Heavy]) return;
    Son[Heavy]->Top = Top, Son[Heavy]->DFS();
    Trie* Cur(Son[Heavy ^ 1]);
    if (Cur) Cur->Top = Cur, Cur->DFS();
  }
}T[1000005], * CntT(T), * Lst1, * Lst2;
inline void Link(Node* x, unsigned L, unsigned R) {
  if ((A <= L) && (R <= B)) { Frm->To.emplace_back(x);return; }
  unsigned Mid((L + R) >> 1);
  if (A <= Mid) Link(x->To[0], L, Mid);
  if (B > Mid) Link(x->To[1], Mid + 1, R);
}
inline Node* Build(unsigned L, unsigned R) {
  if (L == R) { return N + ((List[L] - N) ^ 1); }
  unsigned Mid((L + R) >> 1);
  Node* Cur(++CntN);
  Cur->To.emplace_back(Build(L, Mid));
  Cur->To.emplace_back(Build(Mid + 1, R));
  return Cur;
}
inline void Tarjan(Node* x) {
  x->DFSr = x->Low = ++DFSCnt, List[++STop] = x, x->InS = 1;
  for (auto Cur : x->To) {
    if (Cur->DFSr) { if (Cur->InS) x->Low = min(x->Low, Cur->Low); }
    else Tarjan(Cur), x->Low = min(x->Low, Cur->Low);
  }
  if (x->DFSr == x->Low) {
    ++SCC;
    do List[STop]->Bel = SCC, List[STop]->InS = 0;
    while (List[STop--] != x);
  }
}
signed main() {
  CntN = N + (n2 = ((n = RD()) << 1)) - 1;
  for (unsigned i(0), j(1); i < n; ++i) {
    scanf("%s", TmpI + 1), Lst1 = Lst2 = T, j = 1;
    while (TmpI[j] >= '0') {
      ++(Lst1->Size), ++(Lst2->Size);
      Ans[i].push_back(TmpI[j]);
      if (TmpI[j] == '?') {
        UnSur[i] = 1;
        if (!(Lst1->Son[0])) Lst1->Son[0] = ++CntT;
        if (!(Lst2->Son[1])) Lst2->Son[1] = ++CntT;
        Lst1 = Lst1->Son[0];
        Lst2 = Lst2->Son[1];
      }
      else {
        Cr = TmpI[j] - '0';
        if (!(Lst1->Son[Cr])) Lst1->Son[Cr] = ++CntT;
        if (!(Lst2->Son[Cr])) Lst2->Son[Cr] = ++CntT;
        Lst1 = Lst1->Son[Cr];
        Lst2 = Lst2->Son[Cr];
      }
      ++j;
    }
    ++(Lst1->Cnt), ++(Lst1->Size), N[i << 1].Tr = Lst1;
    ++(Lst2->Cnt), ++(Lst2->Size), N[(i << 1) ^ 1].Tr = Lst2;
  }
  T->PreDFS(), T->Top = T, T->DFS();
  for (unsigned i(0); i < n2; ++i) List[(N[i].Tr)->RL + (--((N[i].Tr)->Cnt))] = N + i;
  for (unsigned i(1); i <= n2; ++i) List[i]->DFSr = i;
  Root = Build(1, n2);
  for (Frm = N + n2 - 1; Frm >= N; --Frm) {
    Trie* Cur(Frm->Tr);
    A = Frm->DFSr + 1, B = Cur->RL + Cur->Size - 1;
    if (A <= B) Link(Root, 1, n2);
    A = Cur->Top->RL, B = Frm->DFSr - 1;
    if (A <= B) Link(Root, 1, n2);
    Cur = Cur->Top->Fa;
    while (Cur) {
      A = Cur->Top->RL, B = Cur->RR;
      if (A <= B) Link(Root, 1, n2);
      Cur = Cur->Top->Fa;
    }
  }
  for (unsigned i(1); i <= n2; ++i) List[i]->DFSr = 0;
  DFSCnt = 0, Tarjan(Root);
  for (unsigned i(0); i < n; ++i)
    if (N[i << 1].Bel == N[(i << 1) ^ 1].Bel) { Flg = 1;break; }
    else UnSur[i] = (N[i << 1].Bel > N[(i << 1) ^ 1].Bel ? 1 : 0);
  if (Flg) { printf("NO\n"); return 0; }
  printf("YES\n");
  for (unsigned i(0); i < n; ++i) {
    for (auto j : Ans[i]) {
      if (j == '?') putchar(UnSur[i] + '0');
      else putchar(j);
    }
    putchar('\n');
  }
  return Wild_Donkey;
}
```


---

## 作者：SoyTony (赞：2)

先建出 Trie 树，若一个串有 `?` 则将两种可能都插入。

设 $p_{i,0/1},u_{i,0/1}$ 分别表示第 $i$ 个串填 $0$ 或 $1$ 这一事件以及在 Trie 树上结束的位置，暴力做法是如果 $u_{i,x}$ 和 $u_{j,y}$ 在 Trie 树上有祖先关系，那么 $p_{i,x}\to p_{j,\lnot y},p_{j,y}\to p_{i,\lnot x}$ 连边，跑 2-SAT。

先考虑 $u_{i,x}\neq u_{j,y}$ 的情况，即二者有祖先关系但不重合，连边可以视作 $p_{j,y}$ 向一个前缀所有 $p_{i,\lnot x}$ 连边，一个前缀 $p_{i,x}$ 向所有 $p_{j,\lnot y}$ 连边。

考虑前缀优化，分别建出内向树和外向树，在内向树中，$u_{i,x}\to p_{i,\lnot x}$，这样连 $p_{j,y}\to fa_{u_{j,y}}$ 就是第一种连边；在外向树中，$p_{i,x}\to u_{i,x}$，这样连 $fa_{u_{j,y}}\to p_{j,\lnot y}$ 就是第二种连边。

$u_{i,x}=u_{j,y}$ 的情况就是在一个节点内部连边，看做序列，连边就是与自己以外的相反状态相连，这也是一个前后缀优化。

需要特殊考虑不含 `?` 的情况，若两个不含 `?` 的串有前后缀关系直接不合法，若一个不含 `?` 的串与一个含 `?` 的可能结果有前后缀关系就连 $p_{i,x}\to p_{i,\lnot x}$。

注意 Trie 树的节点数可能大于 $5\times 10^5$。

点数和边数巨大，但是可以通过。

---

## 作者：SDNetFriend (赞：2)

## P6965 [NEERC2016]Binary Code 题解

### 题意不再赘述啦

[P6965 [NEERC2016]Binary Code](https://www.luogu.com.cn/problem/P6965)

### 知识点

2-SAT , Tarjan , 前缀优化建图 , 字典树 , Hash

### 分析

首先，我们问题可以转化一下，因为每个串至多有一个“？”,所以相当于是在每个串的问号为 $0$ 或 $1$ 的情况里面挑一种，并且因为要保证“任意一个字符串不是其它任意一个字符串的前缀”，即有一些冲突条件，这就是一个经典的 2-SAT 问题。

那怎么能把这个冲突描述出来呢？我们知道字典树又名“前缀树”，也就是讲，两个串如果在字典树上的终点是“祖先-后代”关系那么这对就不可以同时选。

所以我们考虑把每个带问号的串拆成两个塞进字典树里面，然后建边跑 2-SAT ，但有个大问题，即边的数量可能达到 $O(n^2)$，所以现在我们主要的任务是解决边数太大的问题。

#### 方案 1

**我觉得边不会很多！**

实际上确实不是很多。

假设拆出来的串没有相同的，那么每个点边的数量就最多是自己的长度，而题目给了限制 $\sum len\leq 5\times 10^5$，这样不会有什么问题。

现在问题就在于可能出现一坨串全都塞进了一个点里面，这就导致一个点前面可能有 $n$ 个需要连的串，这该怎么办？

考虑，假设出现了 $3$ 个连问号都一样的串，那么最后肯定是无解的。这有什么用呢？

假设字典树上一个点代表长度为 $len$ ，那么因为连问号都相同的串不超过 $2$ 个，所以 $len$ 个位置，最多可以放下 $2\times len$ 个带问号的，还能放下一个不带问号的，也就是说，每个点最多有 $2\times len +1$ 个串。

并且，因为有总长度的限制，所以每个点的串数上界应该是 $\frac{\sum len}{len}$，两个平衡一下能得出每个点串数最多是 $\sqrt {\sum len}$ 这个水平，也就是自己点连自己不会很多。

那连其它的怎么办？我尝试用程序构造了一下，让长度为 $1,2,3,...$ 的节点分别塞进去 $3,5,7,...$ 个串，然后算了算，上界不到 $10^8$，并且几乎跑不满。

而且我们可以一个节点建一个副节点与其中所有串连边。类似操作优化优化，实际上不优化常数优秀点也可以跑过去。

只要搞搞哈希判下完全相同的串是否超过两个即可。

#### 方案 2

代码即是此种方案的代码。

我们发现每次建边，每个点都向自己的前缀，以及自己“被前缀”的节点建了边，这其实就是字典树根向和叶向的前缀。

那我们对每一个串都开几个辅助节点，专门用来进行前缀建边的辅助，这样问题就能得到解决。

这里细节比较多，在这里简单分析下。

我用 $p_{i,0/1}$ 分别表示 $i$ 号串（拆完之后的编号）前缀和被前缀的辅助节点，然后用 $ep_{i,0/1}$ 表示 $i$ 这个字典树节点最后一个前缀和被前缀的辅助节点的编号方便各点之间连接。用 $x_{0/1}$ 表示同一个问号串衍生出来的串。

同时我们随手声明一个 $md$ 表示两个叶子节点到父节点的被前缀辅助节点的辅助节点（这个程序里并没有保存下来）。以及上一个串的对应节点用 $lst$ 表示。

- $x_0\to ep_{fa_x,0}$

- $p_{x_0,0}\to p_{lst,0}$

- $p_{x_0,0},x_1$

- $md\to ep_{lc,1}$ , $md\to ep_{rc,1}$

- $x_0\to p_{lst,1}/md$

- $p_{x_0,1}\to p_{lst,1}/md$

- $p_{x_0,1}\to x_1$

剩下真的细节不少，大概就这样。

**代码中各变量含义与文中略有不同**

### 贴代码

```cpp
#include <bits/stdc++.h>
#define lint long long
#define rint register int
using namespace std;
inline int read(){
	char c;int f=1,res=0;
	while(c=getchar(),!isdigit(c))if(c=='-')f*=-1;
	while(isdigit(c))res=res*10+c-'0',c=getchar();
	return res*f;
}
const lint N=2e6+5,M=2e7+5;
int hed[M],nxt[M<<1],ver[M<<1],cnt=1;
inline void inst(int u,int v){
	if(!u||!v)return;
	ver[++cnt]=v;
	nxt[cnt]=hed[u];
	hed[u]=cnt;
}
int n,np,a[2][N],p[N][2];
string s[N],_s[N][2];//_s为存答案的数组 
int tot=1,ch[N][2],ep[N][2]={0};
vector<int> id[N];
//p为记录前缀和的点标号
//ep为记录对应Trie树节点前缀和的结束编号 
//id存储当前点是哪些标号点的终点
inline void inst(int _id,int *arr,int len){
	int x=1;
	for(rint i=1;i<=len;++i){
		int c=arr[i];
		if(!ch[x][c])
			ch[x][c]=++tot;
		x=ch[x][c];
	}
	id[x].push_back(_id);
}
//前缀优化建图 0搞前缀 1搞被前缀 
void build(int x,int fa){
	//先建出前缀图
	int lst=ep[fa][0];
	for(rint i=0;i<id[x].size();++i){
		int y=id[x][i];
		p[y][0]=++np;
		inst(y,lst);//连y的前缀 
		inst(p[y][0],lst);//前缀连前缀 
		inst(p[y][0],y^1);//前缀连y的相对 
		lst=p[y][0];
	}ep[x][0]=lst;
	//再建被前缀图 
	int lc=ch[x][0],rc=ch[x][1];lst=++np;
	if(lc)build(lc,x),inst(lst,ep[lc][1]);
	if(rc)build(rc,x),inst(lst,ep[rc][1]);
	//用一个被前缀节点连左右儿子被前缀终点
	for(rint i=id[x].size()-1;i>=0;--i){
		int y=id[x][i];
		p[y][1]=++np;
		inst(y,lst);
		inst(p[y][1],lst);
		inst(p[y][1],y^1);
		lst=p[y][1];
	}ep[x][1]=lst;
}
int st[M],tp=0,scc[M],ns=0,dfn[M],low[M],t=0;
bool vis[M];
inline void Tarjan(int u,int fa){
	dfn[u]=low[u]=++t;
	st[++tp]=u;
	for(rint e=hed[u];e;e=nxt[e]){
		int v=ver[e];
		if(v==fa)continue;
		if(!dfn[v]){
			Tarjan(v,u);
			low[u]=min(low[u],low[v]);
		}else if(!vis[v])
			low[u]=min(low[u],dfn[v]);
	}
	if(low[u]==dfn[u]){
		++ns;
		while(tp&&st[tp+1]!=u){
			scc[st[tp]]=ns;
			vis[st[tp]]=true;
			--tp;
		}
	}
}
int main(){
	n=read();np=n<<1|1;
	for(rint i=1;i<=n;++i){
		cin>>s[i];bool flg=false;
		_s[i][0]=_s[i][1]=s[i];
		for(rint j=0;j<s[i].size();++j)
			if(s[i][j]=='?'){
				a[0][j+1]=0;_s[i][0][j]='0';
				a[1][j+1]=1;_s[i][1][j]='1';
				flg=true;
			}else{
				a[0][j+1]=s[i][j]-'0';
				a[1][j+1]=s[i][j]-'0';
			}
		inst(i<<1,a[0],s[i].size());
		inst(i<<1|1,a[1],s[i].size());
		if(!flg)inst(i<<1,i<<1|1);
		//特判两种情况相同的
		//强制选后者 
	}
	build(1,0);
	for(rint i=1;i<=np;++i)
		if(!dfn[i])Tarjan(i,0);
	for(rint i=1;i<=n;++i){
		if(scc[i<<1]==scc[i<<1|1]){
			printf("NO");
			return 0;
		}
	}
	cout<<"YES"<<endl;
	for(rint i=1;i<=n;++i)
		if(scc[i<<1]<scc[i<<1|1])
			cout<<_s[i][0]<<endl;
		else
			cout<<_s[i][1]<<endl;
	return 0;
}
```


---

## 作者：wangyυsυm (赞：1)

这道题目是一道图论题。

我们可以用字典树 Trie 来解决这道题。

我们考虑直接在 Trie 上优化建图。

我们考虑如何处理子树。

我的方法是这样的：对于子树，可以通过新建点连向儿子的子树点，来代表这棵子树的入边 $or$ 出边。

这样只要建立选了 $i$ 就不能选 $i$ 子树中元素的条件。

剩下就只需要注意细节即可。

细节比较繁琐，需要细心处理。

代码鬼畜，细节繁多，无法突出重点，就不放了。

---

## 作者：hzoi_liuchang (赞：0)

## 分析
对于每一个字符串，我们把它拆成两个状态，

一个代表问号处填 $0$ 的方案，一个代表问号处填 $1$ 的方案，

对于每一个字符串，枚举其它会与它产生冲突的字符串，向其反状态连边，

然后跑一个 $2-sat$ 就行了。

这样建图的复杂度是 $n^2$ 的。

上述做法问题在于边数太多，因此我们考虑先枚举问号，然后把所有可能串建成一棵 $Trie$，

在 $Trie$ 树上，我们只需要由当前的节点向其反状态的所有祖先和儿子连边。

具体的做法是多开两条链来辅助我们进行连边优化，

就是图中右面的节点两边的边，

链上反映的就是 $Trie$ 上的父子关系，

在两条链上又都有多个节点，和我们需要连边的节点连在一起，

那么我们连边时就可以这样连，

![](https://img2020.cnblogs.com/blog/1996139/202101/1996139-20210126073849837-1164800721.png)

最终建出来的图就是这个样子的。

![](https://img2020.cnblogs.com/blog/1996139/202101/1996139-20210126073850601-97778415.png)

(图是嫖[ljh巨佬](https://www.cnblogs.com/li-jia-hao/p/13773651.html)的)

还有一个问题就是 $Trie$ 树上一个节点可能包含多个不同的字符串，

我们需要强行规定一个父子关系。
## 代码
``` cpp
#include<cstdio>
#include<algorithm>
#include<vector>
#include<cstring>
#define rg register
const int maxn=4e6+5;
int n,len[maxn],h[maxn],tot=1,cnt=1,tr[maxn][2];
struct asd{
	int to,nxt;
}b[maxn];
void ad(rg int aa,rg int bb){
	if(aa==0 || bb==0) return;
	b[tot].to=bb;
	b[tot].nxt=h[aa];
	h[aa]=tot++;
}
int dfn[maxn],dfnc,low[maxn],shuyu[maxn],scc,sta[maxn],tp,wz[maxn];
void tar(rg int now){
	sta[++tp]=now;
	dfn[now]=low[now]=++dfnc;
	for(rg int i=h[now];i!=-1;i=b[i].nxt){
		rg int u=b[i].to;
		if(!dfn[u]){
			tar(u);
			low[now]=std::min(low[now],low[u]);
		} else if(!shuyu[u]){
			low[now]=std::min(low[now],dfn[u]);
		}
	}
	if(dfn[now]==low[now]){
		scc++;
		while(1){
			rg int y=sta[tp--];
			shuyu[y]=scc;
			if(y==now) break;
		}
	}
}
char s[maxn];
std::vector<char> g[maxn];
std::vector<int> Node[maxn];
int fa[maxn];
void insert(rg int id,rg int op){
	rg int now=1;
	for(rg int i=0;i<len[id];i++){
		rg int p=g[id][i]-'0';
		if(!tr[now][p]){
			tr[now][p]=++cnt;
			fa[cnt]=now;
		}
		now=tr[now][p];
	}
	Node[now].push_back(id+n*op);
}
int getup(rg int id){
	if(id>n) return id+4*n;
	else return id+3*n;
}
int getdown(rg int id){
	if(id>n) return id+3*n;
	else return id+2*n;
}
void solvezx(rg int id){
	rg int tmp1=id;
	if(id>n) id-=n;
	else id+=n;
	rg int tmp2=getup(id);
	for(rg int i=h[tmp2];i!=-1;i=b[i].nxt) if(b[i].to!=id) ad(tmp1,b[i].to);
}
void solvech(rg int id){
	rg int tmp1=id;
	if(id>n) id-=n;
	else id+=n;
	rg int tmp2=getdown(id);
	for(rg int i=h[tmp2];i!=-1;i=b[i].nxt) if(b[i].to!=id) ad(tmp1,b[i].to);
}
void build(rg int da,rg int fa){
	rg int mmax=Node[da].size(),now;
	for(rg int i=0;i<mmax;i++){
		now=Node[da][i];
		ad(getdown(now),now),ad(getup(now),now);
		if(fa) ad(getup(now),getup(fa)),ad(getdown(fa),getdown(now));
		fa=now;
	}
	if(tr[da][0]) build(tr[da][0],fa);
	if(tr[da][1]) build(tr[da][1],fa);
}
int main(){
	memset(h,-1,sizeof(h));
	memset(wz,-1,sizeof(wz));
	scanf("%d",&n);
	for(rg int i=1;i<=n;i++){
		scanf("%s",s+1);
		len[i]=strlen(s+1);
		for(rg int j=1;j<=len[i];j++){
			g[i].push_back(s[j]);
			if(s[j]=='?') wz[i]=j;
		}
	}
	for(rg int i=1;i<=n;i++){
		if(wz[i]==-1){
			insert(i,0),insert(i,1);
		} else {
			g[i][wz[i]-1]='0',insert(i,0);
			g[i][wz[i]-1]='1',insert(i,1);
		}
	}
	build(1,0);
	for(rg int i=1;i<=2*n;i++) solvezx(i),solvech(i);
	for(rg int i=1;i<=6*n;i++) if(!shuyu[i]) tar(i);
	for(rg int i=1;i<=n;i++){
		if(shuyu[i]==shuyu[i+n]){
			printf("NO\n");
			return 0;
		}
	}
	printf("YES\n");
	for(rg int i=1;i<=n;i++){
		if(wz[i]!=-1 && shuyu[i]>shuyu[i+n]) g[i][wz[i]-1]='0';
		for(rg int j=0;j<g[i].size();j++) printf("%c",g[i][j]);
		printf("\n");
	}
	return 0;
}
```

---

