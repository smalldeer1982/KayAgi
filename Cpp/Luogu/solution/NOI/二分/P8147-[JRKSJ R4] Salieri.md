# [JRKSJ R4] Salieri

## 题目背景

![a358071f95cad1c8ccd29cc83a3e6709c83d518e.jpg](https://s2.loli.net/2021/12/24/Oi251TnFP7SflQp.jpg)  

~~【记得到番里面去把“萨列里谱不出莫扎特的曲子”这句话找到】~~ 最终还是没能找到，哪位看过《命运石之门0》的兄弟能帮我找找？

## 题目描述

Salieri 发现了 $n$ 种制作音乐的模式，他将第 $i$ 种模式表示为一个字符串 $s_i$，这种模式所带来的初始优美度为 $v_i$。  
Salieri 现在想制作 $m$ 首乐曲，每次他的灵感可以被表示成一个字符串 $S$。设 $cnt_i$ 为 $s_i$ 在 $S$ 中的出现次数，则采用 $i$ 模式制作的乐曲最终的优美度 $w_i=cnt_i\times v_i$。  
Salieri 当然希望制作出来的乐曲最终优美度越大越好，但是他发现此灵感下前 $k-1$ 优美的乐曲已经被 Mozart 制作过了，他只能制作第 $k$ 优美的乐曲。请你求出这个最终优美度。  

形式化题意：给出 $n$ 个字符串 $s_i$，每个字符串有一个权值 $v_i$。$m$ 次询问每次给出一个字符串 $S$ 和一个常数 $k$。设 $cnt_i$ 为 $s_i$ 在 $S$ 中的出现次数，求 $cnt_i\times v_i$ 第 $k$ 大的值。

## 说明/提示

设 $L$ 为 $s$ 长度总和。

| $\text{Subtask}$|$n,m\le$|$L\le$|特殊性质| 分值 |
|:-:|:-:|:-:|:-:| :-: |
|$1$|$10^3$|$5\times10^3$|无| $10$ |
|$2$|$10^3$|$10^5$|无| $20$ |
|$3$|$10^5$|$5\times10^5$|$k=1$| $10$ |
|$4$|$3\times10^4$|$2\times10^5$|$k\le5$| $20$ |
|$5$|$3\times10^4$|$2\times10^5$|无|  $20$ | 
|$6$|$10^5$|$5\times10^5$|无|  $20$ |

对于 $100\%$ 的数据，$1\le n,m\le10^5$，$L\le5\times10^5$。

无论何时 $\sum |S|$ 与 $L$ 同阶，$s$ 和 $S$ 中只会出现 $\texttt a,\texttt b,\texttt c,\texttt d$ 四种字符，$v_i\le10^3$，$k\le n$。


![QQ截图20220128131353.png](https://s2.loli.net/2022/01/28/MJchEuxsF1QI46V.png)

## 样例 #1

### 输入

```
4 2
ab 2
a 2
ba 2
b 1
bbaba 2
aab 1```

### 输出

```
4
4```

## 样例 #2

### 输入

```
15 4
ba 18
cbc 74
aac 54
ba 77
a 66
c 96
cdb 47
dc 45
cb 62
db 88
dda 93
db 34
b 81
acd 100
da 80
bcaacbbdcbabcda 4
bccac 3
abdbaca 5
cbdaaaacaaca 3```

### 输出

```
124
66
77
108```

# 题解

## 作者：abruce (赞：17)

题外话：我吹爆命运石之门！！1  
这道题目主要考察了选手对于某些算法的熟悉度以及 AC 自动机的概念。这个题其实不是很难，但赛时只有和本题目名一样的那位巨佬写了正解（其它的是神秘做法），原因可能是没想到虚树一辈子都想不出来（毕竟这个 trick 我从未见过）。  
数据有点水……但是肯定会加强的（但似乎卡不掉？）。  

### 30~50pts  
建完 AC 自动机后暴力得到 $cnt$，然后暴力求出第 $k$ 大。（因为数据水，所以你最高甚至可以得到 60pts）  
### 60pts  
先看 $k=1$，$k\le5$ 是类似的（这是一个口胡算法）。  
我们可以建出 AC 自动机，然后把询问串在 AC 上跑，得到一堆节点，设这个可重集合为 $T$。考虑 $cnt_i$ 的意义是有多少个 $T$ 中节点在 $s_i$ 在 trie 树上的尾节点的子树中。  
我们可以直接对于每个 $T$ 中节点进行到根加操作（用树剖+线段树），然后暴力求维护前 $k$ 大的值。最后直接看线段树根节点。  

## 100pts  
保留 60pts 中 $cnt_i$ 的意义，我们换一种方式去查询第 $k$ 大。  
首先我们可以二分答案，问题转化为求 $cnt_i\ge k$ 的有多少个。  
我们发现，对于 $T$ 中的每个点，我们可以不用直接进行到根加操作。因为 $|T|=|S|,\sum |S|\le5\times10^5$，所以我们可以把 $T$ 中的点建成一棵虚树。  
接下来，你会发现，对于虚树上的 $u$ 到 $fa_u$，这一段的 $cnt$ 的值是一样的，问题转化为求这一段上面 $w_i\ge \lceil\dfrac{mid}{cnt}\rceil$ 有多少个。一段直上直下的链求上面的值大于等于一个参数有多少个，我们可以用一棵主席树维护。时间复杂度 $O(\sum|T|\log L\log ans)$。  

```cpp
#include<bits/stdc++.h>
#define lc(x) t[x].c[0]
#define rc(x) t[x].c[1]
using namespace std;
inline int reads(char s[]) {
	int x=0;
	char ch=getchar();
	while(ch<'0'||ch>'z')ch=getchar();
	while(ch>='0'&&ch<='z')s[x++]=ch,ch=getchar();
	s[x]='\0';
	return x;
}
inline int read() {
	int x=0;
	char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9')x=x*10+c-'0',c=getchar();
	return x;
}
typedef long long ll;
const int maxn=5e5+5;
struct tree {
	int c[2],siz;
} t[maxn*30];
int tr[maxn][4],fail[maxn],siz[maxn],rt[maxn],v[maxn],n,m,tot=1,cnt,f[maxn][19],d[maxn],zc[maxn],book[maxn],st[maxn],top,p[maxn],pos,lg2[maxn];
char s[maxn];
queue<int> q;
vector<int> e[maxn],w[maxn],bj[maxn];
typedef vector<int>::iterator iter;
bool cmp(int x,int y) {
	return p[x]<p[y];
}
void insert(int u) {
	int len=strlen(s),rt=1;
	for(register int i=0; i<len; i++) {
		int y=s[i]-'a';
		if(!tr[rt][y])tr[rt][y]=++tot;
		rt=tr[rt][y];
	}
	bj[rt].push_back(u);
}
void getfail() {
	for(register int i=0; i<4; i++)tr[0][i]=1;
	q.push(1);
	while(!q.empty()) {
		int u=q.front(),f=fail[u];
		q.pop();
		for(register int i=0; i<4; i++) {
			int j=tr[u][i];
			if(!j) {
				tr[u][i]=tr[f][i];
				continue;
			}
			fail[j]=tr[f][i];
			q.push(j);
		}
	}
}
void add(int &id,int o,int l,int r,int v) {
	id=++cnt,t[id]=t[o],t[id].siz++;
	if(l==r)return;
	int mid=l+r>>1;
	v<=mid?add(lc(id),lc(o),l,mid,v):add(rc(id),rc(o),mid+1,r,v);
}
int ask(int id,int o,int l,int r,int v) {
	if(!id)return 0;
	if(l>=v)return t[id].siz-t[o].siz;
	int mid=l+r>>1,sum=ask(rc(id),rc(o),mid+1,r,v);
	if(v<=mid)sum+=ask(lc(id),lc(o),l,mid,v);
	return sum;
}
void dfs(int u,int fa) {
	rt[u]=rt[fa];
	for(register iter it=bj[u].begin(); it!=bj[u].end(); it++)add(rt[u],rt[u],1,1000,v[*it]);
	d[u]=d[fa]+1,f[u][0]=fa,p[u]=++pos;
	for(register int i=1; i<=lg2[d[u]]; i++)f[u][i]=f[f[u][i-1]][i-1];
	for(iter it=e[u].begin(); it!=e[u].end(); it++)dfs(*it,u);
}
int lca(int x,int y) {
	if(d[x]<d[y])swap(x,y);
	while(d[x]>d[y])x=f[x][lg2[d[x]-d[y]]-1];
	if(x==y)return x;
	for(register int i=lg2[d[x]]-1; i>=0; i--)
		if(f[x][i]!=f[y][i])x=f[x][i],y=f[y][i];
	return f[x][0];
}
int check(int u,int fa,int mid) {
	int sum=0;
	siz[u]=book[u];
	for(register iter it=w[u].begin(); it!=w[u].end(); it++)sum+=check(*it,u,mid),siz[u]+=siz[*it];
	if(u!=1)sum+=(mid-1)/siz[u]+1>1000?0:ask(rt[u],rt[fa],1,1000,(mid-1)/siz[u]+1);//小细节，这里的剪枝可以大大优化常数
	return sum;
}
void clear(int u) {
	for(register iter it=w[u].begin(); it!=w[u].end(); it++)clear(*it);
	siz[u]=book[u]=0,w[u].clear();
}
int main() {
	int k,sl1=0,sl2=0;
	n=read(),m=read();
	for(register int i=1; i<=n; i++)reads(s),sl1+=strlen(s),v[i]=read(),insert(i);
	getfail();
	for(register int i=2; i<=tot; i++)e[fail[i]].push_back(i);
	for(register int i=1; i<=tot; i++)lg2[i]=lg2[i-1]+((1<<lg2[i-1])==i);
	dfs(1,0);//建 AC 自动机，fail 树
	while(m--) {
		reads(s),sl2+=strlen(s),k=read();
		int u=1,len=strlen(s);
		for(register int i=0; i<len; i++)u=tr[u][s[i]-'a'],zc[i+1]=u,book[u]++;//得到 T 的所有节点
		sort(zc+1,zc+len+1,cmp),len=unique(zc+1,zc+len+1)-zc-1;
		st[top=1]=zc[1];
		for(register int i=2; i<=len; i++) {
			int la=lca(st[top],zc[i]);
			while(top) {
				if(d[la]>=d[st[top-1]]) {
					if(la!=st[top])w[la].push_back(st[top]),la!=st[top-1]?st[top]=la:top--;
					break;
				}
				w[st[top-1]].push_back(st[top]),top--;
			}
			st[++top]=zc[i];
		}
		while(--top)w[st[top]].push_back(st[top+1]);//建出虚树
		int l=1,r=1e9,ans=0;
		while(l<=r) {
			int mid=l+r>>1;
			if(check(st[1],1,mid)>=k)l=mid+1,ans=mid;
			else r=mid-1;
		}//二分答案
		printf("%d\n",ans);
		clear(st[1]);
	}
}
```

---

## 作者：251Sec (赞：4)

因为我在模拟赛秒杀这题 $\log^2$ 做法之后认定这个复杂度一定过不了 $5 \times 10^5$ 并狂暴写了个乱搞而且跑的飞快，所以这是一篇乱搞题解。

不难得到暴力做法：对于所有 $s_i$ 建 ACAM，每次询问就是把若干 Fail 树上的到根路径上所有点的出现次数 $x_i$ 加 $1$，然后求第 $k$ 大的 $x_iv_i$。这个可以直接二分解决。

考虑精细实现这个暴力，我们直接暴力求出所有这些点到根的路径并，这显然是一个连通块，所以我们只遍历该连通块上的点。我们发现在 $|S|> \sqrt L$ 的时候这样的单次询问代价不超过 $L$，询问次数不超过 $\sqrt L$，在 $|S| \le \sqrt L$ 的时候这样的代价不超过 $|S|\sqrt L$（因为它们在 Fail 树上的深度都不超过 $\sqrt L$），于是它的复杂度算上二分是 $O(L\sqrt L  \times \text{polylog})$ 的。按理说它完全过不了，但是我卡了半天都没把这个东西卡满，所以我交了，然后它跑的飞快。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n, m;
char s[500005];
int nxt[500005][26], prt[500005], tcn = 1;
vector<int> w[500005];
vector<int> eN[500005];
void Ins(char *s, int n, int v) {
	int p = 1;
	for (int i = 1; i <= n; i++) {
		int &q = nxt[p][s[i] - 'a'];
		if (!q) q = ++tcn;
		p = q;
	}
	w[p].push_back(v);
}
void Build() {
	queue<int> q;
	for (int i = 0; i < 26; i++) nxt[0][i] = 1;
	q.push(1);
	while (!q.empty()) {
		int u = q.front(); q.pop();
		for (int i = 0; i < 26; i++) {
			if (nxt[u][i]) {
				prt[nxt[u][i]] = nxt[prt[u]][i];
				q.push(nxt[u][i]);
			}
			else nxt[u][i] = nxt[prt[u]][i];
		}
	}
}
int x[500005], vis[500005], vC;
void DFS(int u) {
	for (int v : eN[u]) DFS(v), x[u] += x[v];
}
int sum;
void Check(int u, int t) {
	sum += w[u].end() - lower_bound(w[u].begin(), w[u].end(), (t + x[u] - 1) / x[u]);
	for (int v : eN[u]) Check(v, t);
}
void Clear(int u) {
	x[u] = 0;
	for (int v : eN[u]) Clear(v);
	eN[u].clear();
}
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1, v; i <= n; i++) {
		scanf("%s%d", s + 1, &v);
		Ins(s, strlen(s + 1), v);
	}
	Build();
	for (int i = 1; i <= tcn; i++) if (w[i].size()) sort(w[i].begin(), w[i].end());
	while (m--) {
		vC++;
		int k, len;
		scanf("%s%d", s + 1, &k);
		len = strlen(s + 1);
		int p = 1;
		for (int i = 1; i <= len; i++) {
			p = nxt[p][s[i] - 'a'];
			x[p]++;
			int t = p;
			while (t && vis[t] != vC) {
				if (prt[t]) eN[prt[t]].push_back(t);
				vis[t] = vC, t = prt[t];
			}
		}
		int l = 0, r = 1000 * len, res = 0;
		DFS(1);
		while (l <= r) {
			int mid = l + r >> 1;
			sum = 0, Check(1, mid);
			if (sum >= k) res = mid, l = mid + 1;
			else r = mid - 1;
		}
		printf("%d\n", res);
		Clear(1);
	}
	return 0;
}
```

---

## 作者：qiuzx (赞：4)

## 题意

有 $n$ 个字符串 $s_i$，串有权值 $v_i$。$m$ 次询问 $S,k$，记 $cnt_i$ 表示 $s_i$ 在 $S$ 中的出现次数，则求 $cnt_i\times v_i$ 的第 $k$ 大值。$n,m\le 10^5,\sum |S|,\sum |s_i|\le 5\times 10^5$。

## 思路

所有串在 $S$ 中的出现次数可以通过 AC 自动机解决。具体地，建出失配树之后在字典图上遍历 $S$，标记所有点，则 $cnt_i$ 就等于 $s_i$ 对应节点的子树中被标记的点个数。考虑如何处理多组询问。对于一组询问，建出所有被标记的点的虚树，那么在虚树上两个点之间的部分拥有着相同的 $cnt_i$，然后虚树的根在原树的祖先这部分也需要单独拉出来考虑，其它部分的 $cnt_i$ 全部都是 $0$，所以无需考虑。这样会得到 $O(|S|)$ 条祖孙链，需要查询所有链上的 $cnt_i\times v_i$ 的第 $k$ 大值。考虑二分答案，则需要计算一条链上所有的 $v_i\ge x$ 的个数，使用主席树维护即可。这样做的复杂度是 $O(L\log ans\log v)$。

事实上每次都二分然后查询太浪费了，考虑一种类似线段树二分的方式，例如 [UOJ52](https://uoj.ac/problem/52) 的实现方法。对于每条链维护其当前所在的点的编号，以及其当前可能作为答案的 $l,r$，和对应乘上的系数 $v$。然后开始二分，将每个区间分成两半，可以在主席树上查得后面一半总共的多少个。这样如果这个个数至少是 $k$，取出 $mid_i\times v_i$ 最小的区间 $i$，则说明 $i$ 的前半部分一定不可能作为答案。否则找到 $mid_i\times v_i$ 最大的区间 $i$，则说明 $i$ 的后半部分一定被包含在了最大的 $k$ 个中，将这部分贡献扣掉。然后分别下传即可。当最终 $l=r$ 的时候，若后半部分在答案中会陷入死循环，此时特别处理一下，将 $l$ 当作右半部分即可。使用 set 维护所有区间 $mid\times v$ 的值，可以做到 $O(L\log L\log v)$，如果使用亚 $\log$ 数据结构代替 set，可以做到更优的复杂度。

[代码](https://www.luogu.com.cn/paste/h3mwf5ps)

---

## 作者：Sakura_xyz (赞：2)

## P8147 Salieri 题解

### 题意
给出 $n$ 个字符串 $s_i$，每个字符串有一个权值 $v_i$。$m$ 次询问每次给出一个字符串 $S$ 和一个常数 $k$。设 $cnt_i$ 为 $s_i$ 在 $S$ 中的出现次数，求 $cnt_i\times v_i$ 第 $k$ 大的值。

### 题解

一道比较显然的 AC 自动机题。

首先，答案显然具有单调性，我们可以二分答案，把询问第 $k$ 大的值转化为询问是否有至少 $k$ 个数比当前答案 $x$ 大。

然后考虑 $cnt$ 的意义，我们发现，在 AC 自动机上匹配一遍字符串 $S$ ，将 $S$ 的每个位置所扫到的节点记录下来，记 AC 自动机上的第 $i$ 号节点被扫过的次数为 $times_i$ ，则对于节点 $i$ 而言，其 fail 树的子树内所有节点的 $times$ 之和就是节点 $i$ 所代表的字符串在 $S$ 中出现的次数 $cnt$ 。

观察到，我们对于每次询问而言，对 $cnt$ 有影响的节点只有 $S$ 所扫过的节点，只有这些节点在这次询问中对 $cnt$ 而言是有贡献的，因此我们找到这些点，对 fail 树建一棵虚树，便可以统计出对于每个节点的 $cnt$ 。

接着考虑如何统计答案，对于虚树上的两个直接连边的节点，其在原树上的路径上每个点的出现 $cnt$ 一定都与两点中深度较深的节点相同，即对于虚树上搜索到的每一个点，其与父节点连边所表示的一段区间的 $cnt$ 均与其相同，那么也就等价于要查询的是树上的一段深度递增的路径上所对应的 $v$ 中，大于等于 $\lceil \frac{x}{cnt} \rceil$ 的数的个数。

因此直接把每个节点的 $v$ 处理出来后在 fail 树上建一棵主席树维护一下就行了。

### AC 代码
```cpp
#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>
#include<algorithm>
#include<cstring>
#define MAXN 500005

using namespace std;

int n,m,ch[MAXN][4],trie_cnt=0,fail[MAXN],head[MAXN],edge_cnt=0;

int rt[MAXN],nodecnt=0,dfn[MAXN],dfncnt=0,h[MAXN],cnt=0,vistag[MAXN];

int fa[MAXN],dep[MAXN],siz[MAXN],top[MAXN],son[MAXN],stk[MAXN],tp=0;

int sz[MAXN],sz2[MAXN];

char str[MAXN];

vector <int> v[MAXN],edge[MAXN];

struct E{
	int to,nxt;
}e[MAXN];

struct seg{
	int lc,rc,val;
}tree[MAXN*20];

bool cmp(int x,int y) { return dfn[x]<dfn[y]; }

void Add_Edge(int x,int y){
	e[++edge_cnt].to=y;
	e[edge_cnt].nxt=head[x];
	head[x]=edge_cnt;
}

int modify(int p,int l,int r,int pos){
	int tmp=++nodecnt;
	tree[tmp]=tree[p];
	tree[tmp].val++;
	if(l==r) return tmp;
	int mid=l+r>>1;
	if(pos<=mid) tree[tmp].lc=modify(tree[p].lc,l,mid,pos);
	else tree[tmp].rc=modify(tree[p].rc,mid+1,r,pos);
	return tmp;
}

int query(int rt1,int rt2,int l,int r,int ql,int qr){
	if(l>=ql&&r<=qr) return tree[rt2].val-tree[rt1].val;
	int mid=l+r>>1,ret=0;
	if(mid>=ql) ret+=query(tree[rt1].lc,tree[rt2].lc,l,mid,ql,qr);
	if(mid<qr) ret+=query(tree[rt1].rc,tree[rt2].rc,mid+1,r,ql,qr);
	return ret;
}

void insert(char * s,int val){
	int now=0,len=strlen(s);
	for(int i=0;i<len;i++){
		if(!ch[now][s[i]-'a']) ch[now][s[i]-'a']=++trie_cnt;
		now=ch[now][s[i]-'a'];
	}
	v[now].push_back(val);
}

void getfail(){
	queue <int> q;
	for(int i=0;i<4;i++) if(ch[0][i]) q.push(ch[0][i]);
	int fro;
	while(!q.empty()){
		fro=q.front();
		q.pop();
		for(int i=0;i<4;i++){
			if(ch[fro][i]){
				fail[ch[fro][i]]=ch[fail[fro]][i];
				q.push(ch[fro][i]);
			}
			else ch[fro][i]=ch[fail[fro]][i];
		}
	}
	for(int i=1;i<=trie_cnt;i++) edge[fail[i]].push_back(i);
}

void dfs_fail(int x){
	rt[x]=rt[fail[x]]; dfn[x]=++dfncnt;
	for(int i : v[x]) rt[x]=modify(rt[x],1,1000,i);
	for(int i : edge[x]) dfs_fail(i);
}

void dfs1(int x,int f,int d){
	fa[x]=f; dep[x]=d; siz[x]=1;
	for(int i : edge[x]){
		dfs1(i,x,d+1);
		siz[x]+=siz[i];
		if(siz[i]>siz[son[x]]) son[x]=i;
	}
}

void dfs2(int x,int tp){
	top[x]=tp;
	if(son[x]) dfs2(son[x],tp);
	for(int i : edge[x]) if(i^son[x]) dfs2(i,i);
}

int Lca(int x,int y){
	while(top[x]!=top[y]){
		if(dep[top[x]]>dep[top[y]]) x=fa[top[x]];
		else y=fa[top[y]];
	}
	return dep[x]>dep[y]?y:x;
}

int dfs(int x,int f,int val){
	int ret=0;
	sz2[x]=sz[x];
	for(int i=head[x];i;i=e[i].nxt){
		ret+=dfs(e[i].to,x,val);
		sz2[x]+=sz2[e[i].to];
	}
	if(x){
		int tmp=(val-1)/sz2[x]+1;
		if(tmp<=1000) ret+=query(rt[f],rt[x],1,1000,tmp,1000);
	}
	return ret;
}

bool check(int x,int k) { return dfs(0,0,x)>=k; }

int main(){
	cin >> n >> m;
	int val,k,l,r,len,mid,ans,vistot=0;
	while(n--){
		cin >> str >> val;
		insert(str,val);
	}
	getfail();
	dfs_fail(0);
	dfs1(0,0,1);
	dfs2(0,0);
	while(m--){
		++vistot;
		cin >> str >> k;
		edge_cnt=0;
		cnt=0;
		len=strlen(str);
		for(int now=0,i=0;i<len;i++){
			now=ch[now][str[i]-'a'];
			h[++cnt]=now;
			if(vistag[now]==vistot) sz[now]++;
			else sz[now]=1,vistag[now]=vistot;
		}
		sort(h+1,h+cnt+1,cmp);
		stk[tp=1]=0; head[0]=0;
		for(int i=1;i<=cnt;i++){
			if(h[i]==0) continue;
			if(i!=1&&h[i]==h[i-1]) continue;
			l=Lca(stk[tp],h[i]);
			if(l!=stk[tp]){
				while(dfn[l]<dfn[stk[tp-1]]){
					Add_Edge(stk[tp-1],stk[tp]);
					tp--;
				}
				if(dfn[l]>dfn[stk[tp-1]]){
					head[l]=0;
					if(vistag[l]!=vistot) sz[l]=0;
					Add_Edge(l,stk[tp]);
					stk[tp]=l;
				}
				else Add_Edge(l,stk[tp]),tp--;
			}
			head[h[i]]=0; stk[++tp]=h[i];
		}
		for(int i=1;i<tp;i++) Add_Edge(stk[i],stk[i+1]);
		if(!check(1,k)){
			cout << 0 << '\n';
			continue;
		}
		l=1,r=1e9,ans=114514;
		while(l<=r){
			mid=l+r>>1;
			if(check(mid,k)) ans=mid,l=mid+1;
			else r=mid-1;
		}
		cout << ans << '\n';
	}
	return 0;
}
```

---

## 作者：zzxLLL (赞：2)


不是很难的套路乱炖题。

---

要求出现次数，故先建出所有 $s_i$ 的 ACAM，将每个字符串权值挂到其在字典树的终止节点上。

先考虑暴力怎么做。直接将询问的 $S$ 放到 Trie 图上跑，将求 $v_i$ 转化成 fail 树的子树和，然后就能求得每个 $s_i$ 的 $cnt_i\times v_i$。这样时间复杂度是 $O(\sum|S|(n+L))$ 的。

观察 $cnt_i$，发现对于一次询问，不同的 $cnt_i$ 只有 $O(|S|)$ 种。具体地，设 $S$ 在 Trie 图上匹配经过的节点集合为 $T$，建出 fail 树上点集 $T$ 的虚树。那么对于 $u\in T$ 及其虚树上父亲 $fa_u$，fail 树路径 $(u,fa_u)$ 中的所有节点除了 $fa_u$ 以外，所有点的子树和（即 $cnt_i$）都是相同的。

这样就把 fail 树剖成了 $O(|S|)$ 祖孙链，每条链的 $cnt_i$ 相同。二分第 $k$ 大的值 $x$，然后就是祖孙链上查询 $cnt_i\times v_i\ge x$ 即 $v_i\ge\left\lceil\frac{x}{cnt_i}\right\rceil$ 的 $v_i$ 个数。因为事先将权值挂在了节点上，所以直接树上主席树即可。

时间复杂度 $O(L\log V+\sum(|S|\log|S|+|S|\log|S|\log|V|))$。

```cpp
#include <bits/stdc++.h>
const int M = 1e5 + 10, L = 5e5 + 10;
const int LIM = 1000;

int _lg2[L];
inline void calc() {
    _lg2[0] = -1;
    for (int i = 1; i < L; i++) _lg2[i] = _lg2[i >> 1] + 1;
}

char str[L];
int n, m, val[M], qwq[L];

std::vector<int> vec[L];
int ch[L][26], fail[L], lst[L], tot = 1;
inline int Insert(char* str) {
    int len = strlen(str), cur = 1;
    for (int i = 0; i < len; i++) {
        int x = str[i] - 'a';
        if (!ch[cur][x]) ch[cur][x] = ++tot;
        cur = ch[cur][x];
    }
    lst[cur]++;
    return cur;
}

std::vector<int> g[L];
inline void Build() {
    std::queue<int> q;
    for (int i = 0; i < 26; i++) ch[0][i] = 1;
    q.push(1);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int i = 0; i < 26; i++) {
            if (!ch[u][i])
                ch[u][i] = ch[fail[u]][i];
            else
                fail[ch[u][i]] = ch[fail[u]][i], q.push(ch[u][i]);
        }
    }
    for (int i = 2; i <= tot; i++) g[fail[i]].push_back(i);
}

const int Sz = L * 30;
int lc[Sz], rc[Sz], sum[Sz], rt[L], cntnode = 0;
inline void Pushup(int k) {
    sum[k] = sum[lc[k]] + sum[rc[k]];
}
inline void Add(int& k, int p, int l, int r, int x, int v) {
    k = ++cntnode;
    lc[k] = lc[p], rc[k] = rc[p], sum[k] = sum[p] + v;
    if (l == r) return;
    int mid = (l + r) >> 1;
    if (x <= mid) Add(lc[k], lc[p], l, mid, x, v);
    else Add(rc[k], rc[p], mid + 1, r, x, v);
}
inline int Ask(int k, int l, int r, int L, int R) {
    if (L > R || !k) return 0;
    if (L <= l && r <= R) return sum[k];
    int mid = (l + r) >> 1;
    if (R <= mid) return Ask(lc[k], l, mid, L, R);
    if (L > mid)  return Ask(rc[k], mid + 1, r, L, R);
    return Ask(lc[k], l, mid, L, R) + Ask(rc[k], mid + 1, r, L, R);
}

int dfn[L], st[L][20], idx;
#define Min(u, v) (dfn[u] < dfn[v] ? u : v)
inline void Build_ST() {
    for (int k = 1; (1 << k) <= tot; k++)
        for (int i = 1; i + (1 << k) - 1 <= tot; i++)
            st[i][k] = Min(st[i][k - 1], st[i + (1 << (k - 1))][k - 1]);
}
inline int LCA(int u, int v) {
    if (u == v) return u;
    if ((u = dfn[u]) > (v = dfn[v])) std::swap(u, v);
    int k = _lg2[v - u++];
    return Min(st[u][k], st[v - (1 << k) + 1][k]);
}
inline void dfs(int u, int f) {
    rt[u] = rt[f];
    for (int v : vec[u]) Add(rt[u], rt[u], 0, LIM, v, 1);
    st[dfn[u] = ++idx][0] = f;
    for (int v : g[u]) dfs(v, u);
}

int dp[L], fa[L];
std::vector<int> t[L], A, B;
inline bool cmp(int A, int B) {
    return dfn[A] < dfn[B];
}
inline void VirtualTree() {
    std::sort(A.begin(), A.end(), cmp), B.push_back(A.front());
    for (int i = 1; i < (int)(A.size()); i++)
        B.push_back(LCA(A[i - 1], A[i])), B.push_back(A[i]);
    std::sort(B.begin(), B.end(), cmp);
    B.erase(std::unique(B.begin(), B.end()), B.end());
    for (int x : B) t[x].clear();
    for (int i = 1; i < (int)(B.size()); i++)
        t[LCA(B[i - 1], B[i])].push_back(B[i]);
}
inline void Dfs(int u, int f) {
    fa[u] = f;
    for (int v : t[u]) Dfs(v, u), dp[u] += dp[v];
}
inline int calc(int lim) {
    int ret = 0;
    for (int x : B) {
        if (!fa[x]) continue;
        if (lim % dp[x] == 0)
            ret += Ask(rt[x], 0, LIM, lim / dp[x], LIM) - Ask(rt[fa[x]], 0, LIM, lim / dp[x], LIM);
        else
            ret += Ask(rt[x], 0, LIM, lim / dp[x] + 1, LIM) - Ask(rt[fa[x]], 0, LIM, lim / dp[x] + 1, LIM);
    }
    return ret;
}

int tmp[L];
inline void Solve(char* str, int k) {
    A.clear(), B.clear();
    int len = strlen(str), cur = 1;
    A.push_back(cur);
    for (int i = 0; i < len; i++)
        A.push_back(cur = ch[cur][str[i] - 'a']), tmp[cur]++;

    VirtualTree();
    for (int x : B) dp[x] = tmp[x], tmp[x] = 0;
    Dfs(1, 0);

    int L = 1, R = 500000000, res = 0;
    while (L <= R) {
        int mid = (L + R) >> 1;
        if (calc(mid) >= k) res = mid, L = mid + 1;
        else R = mid - 1;
    }
    printf("%d\n", res);
}

int main() {
    calc();
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf(" %s", str), scanf("%d", &val[i]);
        vec[Insert(str)].push_back(val[i]);
    }
    Build(), dfs(1, 0), Build_ST();

    for (int i = 1, k; i <= m; i++) {
        scanf(" %s", str), scanf("%d", &k);
        Solve(str, k);
    }
    return 0;
}
```

---

## 作者：Seauy (赞：2)

Steins Gate 太神了，无论是游戏还是番大家都值得去康康啊！qwq

【嗯是我，“萨列里谱不出莫扎特的曲子”怎么也找不到了，看来“机关”已经开始介入了……我会注意的，EL PSY CONGROO】

## 题目大意

- $n$ 个模式串带权，$m$ 次查询问模式串在文本串中出现次数乘以权的 $K$ 大值。

- $n,m\leq 10^5$，模式串文本串各长度之和不超过 $5\times 10^5$，权不超过 $10^3$。

# 一、思路

多模式串匹配立马想到 AC自动机，建出 Fail 树后，每次匹配让文本串沿着 Trie 树走，一个模式串的出现次数就是 Fail 树上子树内被遍历过的结点个数。

每次查询文本串都在 Fail 树上打出散点，自然地想到使用虚树，这样虚树一条边上的所有模式串出现次数就都相等了，为虚树子树内标记之和（文本串每走到一个点就做 $+1$ 标记）。

但是发现把所有链的值域分布全并起来不太现实，每条链的出现次数也都不一样，不能直接用数据结构维护值域分布找 $K$ 大值。但是我们发现判断一个数字的排名是方便的，也就是说设要判断的数为 $d$，某条链深度较大的那个结点子树内标记之和为 $S$，那么这条链上比我大的数字的权值 $v$ 满足

$$ v>\lceil \frac{d}{S} \rceil $$

于是我们就二分这个 $d$，满足最终优美度 $\geq d+1$ 的模式串个数少于 $K$ 个，最小的这个 $d$ 就是答案了。

最后的问题就是如何维护一条 子孙-祖先 的链上排名查询，显然可以 Fail 树上主席树，这样总复杂度就是 $O(n\log v+L(\log^2 v + \log L))$ 的。

~~喂喂喂出题人，$L$ 有 5e5 结果 std 2log 真的好吗~~

发现 $L$ 其实比 $n$ 大挺多的，于是考虑平衡预处理和查询的复杂度，拥有这个神奇功效也只有分块了。也就是说把可持久化线段树改成可持久化分块，这样一次 子孙-祖先 链上大于给定值的个数就能 $O(1)$ 查询了。

如此如此，复杂度 $O(n\sqrt v + L(\log v + \log L))$，由于出题人贴心地把值域设超小，根号跟log差得几乎不多。

但是我常数写疵了，并没有达到想象中碾压 2log 的效果。

# 二、代码

```cpp
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

inline int Read()
{
	int ret;char c;
	while(1) {c=getchar();if('0'<=c && c<='9') {ret=c-'0';break;}}
	while(1) {c=getchar();if('0'<=c && c<='9') ret=ret*10+c-'0';else break;}
	return ret;
}

const int MAXN=1e5,MAXL=5e5,MAXV=1e3,SQRV=32;

int n,m;string s;
int Trie[MAXL+5][4],tot;
vector<int> V[MAXL+5];
int Q[MAXL+5],Head,Tail,Fail[MAXL+5];

void New(int now,int t)
{
	if(Trie[now][t]) return;
	Trie[now][t]=++tot;
}

void Insert(int now,int depth)
{
	if(depth==s.length()) {V[now].push_back(Read());return;}
	int d=s[depth]-'a';
	New(now,d),Insert(Trie[now][d],depth+1);
}

void BuildAC()
{
	Head=1,Tail=0;
	for(int i=0;i<4;i++) if(Trie[0][i]) Q[++Tail]=Trie[0][i];
	for(int now,rear;Head<=Tail;)
	{
		now=Q[Head++];
		for(int i=0;i<4;i++)
		{
			rear=Trie[now][i];
			if(rear)
			{
				Fail[rear]=Trie[Fail[now]][i];
				Q[++Tail]=rear;
			}
			else Trie[now][i]=Trie[Fail[now]][i];
		}
	}
}

void Match() {Tail=0;for(int now=0,i=0;i<s.length();i++) now=Trie[now][s[i]-'a'],Q[++Tail]=now;}

vector<int> ft[MAXL+5];//失配树
int Block[MAXN+5][SQRV+1],root[MAXN+5][SQRV+1],LT[MAXN+5][SQRV+1],lst;
int loc[MAXL+5];
//可持久化分块 
int Skip[MAXL+5],DFN[MAXL+5],dep[MAXL+5],dnum;
int Mson[MAXL+5],Size[MAXL+5];

void Plus(int x,int v)//在版本 x 上 [1,v] +1
{
	int hb=((v-1)>>5)+1,lb=((v-1)&31)+1;
	++lst;
	for(int i=1;i<=32;i++) Block[lst][i]=Block[root[x][hb]][i]+LT[x][hb];
	for(int i=1;i<=32;i++)
		if(i!=hb) root[lst][i]=root[x][i],LT[lst][i]=LT[x][i];
		else root[lst][i]=lst;
	for(int i=1;i<=lb;i++) ++Block[lst][i];
	for(int i=1;i<hb;i++) ++LT[lst][i];
}

int Ask(int x,int v)//版本 x 上 >=v 的数的个数
{
	int hb=((v-1)>>5)+1,lb=((v-1)&31)+1;
	if(v>1000) return 0;
	return Block[root[x][hb]][lb]+LT[x][hb];
}

void Build(int now)
{
	DFN[now]=++dnum;
	dep[now]=dep[Fail[now]]+1;
	loc[now]=loc[Fail[now]];
	for(int i=0;i<V[now].size();i++) Plus(loc[now],V[now][i]),loc[now]=lst;
	Size[now]=1;
	for(int i=0,rear;i<ft[now].size();i++)
	{
		rear=ft[now][i];
		Build(rear);
		Size[now]+=Size[rear];
		if(Size[rear]>Size[Mson[now]]) Mson[now]=rear;
	}
}

void TCP(int now,int Top)
{
	Skip[now]=Top;
	if(Mson[now]) TCP(Mson[now],Top);
	for(int i=0,rear;i<ft[now].size();i++)
	{
		rear=ft[now][i];
		if(rear==Mson[now]) continue;
		TCP(rear,rear);
	}
}

int LCA(int a,int b)
{
	while(Skip[a]!=Skip[b])
		if(dep[Skip[a]]>dep[Skip[b]]) a=Fail[Skip[a]];
		else b=Fail[Skip[b]];
	if(dep[a]<dep[b]) return a;
	return b;
}

bool cmp(int a,int b) {return DFN[a]<DFN[b];}

vector<int> vt[MAXL+5];
int S[MAXL+5],tp;
void CleanVT(int now)
{
	Size[now]=0;
	for(int i=0;i<vt[now].size();i++) CleanVT(vt[now][i]);
	vt[now].clear();
}
void Link(int x)
{
	if(x==S[tp]) return;
	if(tp<2) {S[++tp]=x;return;}
	int lca=LCA(x,S[tp]);
	if(x==S[tp]) {S[++tp]=x;return;}
	while(tp>1 && dep[lca]<=dep[S[tp-1]]) vt[S[tp-1]].push_back(S[tp]),--tp;
	if(lca!=S[tp]) vt[lca].push_back(S[tp]),S[tp]=lca;
	S[++tp]=x;
}
void BuildVT()
{
	Match();
	sort(Q+1,Q+Tail+1,cmp);
	tp=0;
	if(Q[1]) S[++tp]=0;
	for(int i=1;i<=Tail;i++) Link(Q[i]);
	for(;tp>1;--tp) vt[S[tp-1]].push_back(S[tp]);
	for(int i=1;i<=Tail;i++) ++Size[Q[i]];
}
int ALL;
void CalMsg(int now,int fa)
{
	ALL+=Ask(loc[now],1)-Ask(loc[fa],1);
	for(int i=0;i<vt[now].size();i++) CalMsg(vt[now][i],now),Size[now]+=Size[vt[now][i]];
}

int GetRank(int now,int fa,int x)
{
	int ret=0;//v*Size[now]>=x+1
	if(now)
	{
		int bd=x/Size[now]+1;
		ret+=Ask(loc[now],bd)-Ask(loc[fa],bd);
	}
	for(int i=0;i<vt[now].size();i++) ret+=GetRank(vt[now][i],now,x);
	return ret;
}

int Query(int rnk)
{
	ALL=0,CalMsg(0,0);
	if(rnk>ALL) return 0; 
	int L=1,R=5e8;//找第 rnk 大的 
	for(int mid;L<=R;)
	{
		mid=(L+R)>>1;
		//找>=mid+1 个数最小的 <rnk 的数
		if(GetRank(0,0,mid)<rnk) R=mid-1;
		else L=mid+1;
	}
	return L;
}

int main()
{
	//freopen("test.txt","r",stdin); 
	n=Read(),m=Read();
	for(int i=1;i<=n;i++) cin>>s,Insert(0,0);
	BuildAC();
	for(int i=1;i<=tot;i++) ft[Fail[i]].push_back(i);
	Build(0),TCP(0,0);
	for(int i=0;i<=tot;i++) Size[i]=0;
	for(int K;m--;)
	{
		cin>>s,K=Read();
		BuildVT(); 
		printf("%d\n",Query(K));
		CleanVT(0);
	}
	return 0;
}
```


---

## 作者：OldDriverTree (赞：1)

# Solution

首先对所有 $s$ 建出 $\text{AC}$ 自动机，对于查询，我们先把这个串在 $\text{AC}$ 自动机上走一遍，对于经过的每个点，都会对 $\text{fail}$ 树上这个点到根的路径的 $cnt$ 都会产生 $1$ 的贡献，最后我们要查询的就是 $cnt\times w$ 的第 $k$ 大值，考虑如何维护这个东西。这个 $cnt$ 我们其实不需要用数据结构来维护，可以直接把虚树建出来，然后在虚树上差分一下就行了，此时我们可以注意到对于虚树上的一条 $x$ 到 $y$ 的边，原树上 $x$ 到 $y$ 的路径上（不包括 $x$）的所有点的 $cnt$ 都是相同的。

我们可以先通过二分答案将 $\text{kth}$ 问题转化为 $\text{nlt}$ 问题，我们对于虚树上的每条边都单独处理一下，由于此时 $cnt$ 和 $mid$ 都是固定的，那么我们只需要查询原树这条链上点权大于等于 $\lceil\dfrac{mid}{cnt}\rceil$ 的个数，这个东西用主席树维护一下就行了，时间复杂度 $O(L\log ans\log v)$。

# Code
```c++
//when you use vector or deque,pay attention to the size of it.
//by OldDirverTree
#include<bits/stdc++.h>
//#include<atcoder/all>
#define P pair<int,int>
#define int long long
#define mid (l+r>>1)
using namespace std;
//using namespace atcoder;
const int N=5e5+2,M=1000;
struct node { int son[4],fail; }T[N];
struct Node { int ls,rs,cnt; }ODT[N*10];
int n,m,cnt,tot,dep[N],dfn[N],st[N][19];
vector<int> g[N],w[N],pos,a;
int qwq,ans,root[N],val[N];

void insert(string s,int v)
{
	int rt=0;
	for (char c:s) {
		int &p=T[rt].son[c-'a'];
		if (!p) p=++tot; rt=p;
	}
	w[rt].push_back(v);
}
void build()
{
	queue<int> q; for (int i=0;i<4;i++)
	if (T[0].son[i]) q.push(T[0].son[i]);
	while (!q.empty() ) {
		int u=q.front(); q.pop();
		g[T[u].fail].push_back(u); for (int i=0;i<4;i++)
		if (T[u].son[i]) T[T[u].son[i] ].fail=T[T[u].fail].son[i],
		q.push(T[u].son[i]); else T[u].son[i]=T[T[u].fail].son[i];
	}
}
void update(int &rt,int p,int l,int r,int x) {
	rt=++cnt,ODT[rt]=ODT[p],ODT[rt].cnt++; if (l==r) return;
	if (x<=mid) update(ODT[rt].ls,ODT[p].ls,l,mid,x);
	else update(ODT[rt].rs,ODT[p].rs,mid+1,r,x);
}
int query(int rt,int l,int r,int x) {
	if (!rt) return 0; if (x<=l) return ODT[rt].cnt;
	if (x<=mid) return query(ODT[rt].ls,l,mid,x)+query(ODT[rt].rs,mid+1,r,x);
	else return query(ODT[rt].rs,mid+1,r,x);
}
void dfs(int u,int fa) {
	dep[u]=dep[fa]+1,root[u]=root[fa],st[dfn[u]=++tot][0]=fa;
	for (int x:w[u]) update(root[u],root[u],1,M,x); for (int v:g[u]) dfs(v,u);
}
int LCA(int x,int y) {
	if (x==y) return x; x=dfn[x],y=dfn[y];
	if (x>y) swap(x,y); int k=__lg(y-x);
	x=st[x+1][k],y=st[y-(1<<k)+1][k];
	return dep[x]<dep[y]?x:y;
}
void calc(int u) {
	for (int v:g[u])
	calc(v),val[u]+=val[v];
}
void solve(int u)
{
	for (int v:g[u]) {
		solve(v); int w=(qwq+val[v]-1)/val[v]; if (w<=M)
		ans+=query(root[v],1,M,w)-query(root[u],1,M,w);
	}
}
main()
{
	cin.tie(0),cin>>n>>m;
	while (n--) {
		string s; int w;
		cin>>s>>w,insert(s,w);
	}
	build(),tot=0,dfs(0,0);
	for (int i=0;i<tot;i++) g[i].clear();
	for (int j=1;(1<<j)<=tot;j++)
		for (int i=1,x,y;i+(1<<j)-1<=tot;i++)
			x=st[i][j-1],y=st[i+(1<<j-1)][j-1],
			st[i][j]=dep[x]<dep[y]?x:y;
	
	while (m--)
	{
		string s; int k,rt=0; cin>>s>>k;
		pos.push_back(0),a.push_back(0);
		for (char c:s) {
			rt=T[rt].son[c-'a'],val[rt]++;
			pos.push_back(rt),a.push_back(rt);
		}
		sort(pos.begin(),pos.end(),[&](int x,int y){ return dfn[x]<dfn[y]; });
		for (int i=1;i<pos.size();i++) a.push_back(LCA(pos[i-1],pos[i]) );
		sort(a.begin(),a.end(),[&](int x,int y){ return dfn[x]<dfn[y]; });
		a.erase(unique(a.begin(),a.end() ),a.end() );
		for (int i=1;i<a.size();i++) g[LCA(a[i-1],a[i])].push_back(a[i]);
		calc(0); int l=1,r=5e8; while (l<=r) qwq=mid,ans=0,solve(0),ans>=k?l=mid+1:r=mid-1;
		printf("%lld\n",r); for (int x:a) val[x]=0,g[x].clear(); a.clear(),pos.clear();
	}
	return 0;
}
```

---

## 作者：wxzzzz (赞：0)

### 思路

将 $s$ 经过 AC 自动机上的点以及 $t_0$ 建虚树，于是所有在 $s$ 中出现过的串的点都在虚树上。考虑二分答案，在虚树上统计 $cnt_i\times w_i\ge mid$ 的点数。

注意到虚树上一条边 $(x,y)$ 上所有点的 $cnt$ 都是 $y$ 的子树大小 $b_y$，因此只需统计原树这条路径上 $w_i\ge\lceil\frac{mid}{b_y}\rceil$ 的 $i$ 的数量，直接用主席树维护，复杂度总共 $O(n\log^2n)$。

### 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
#define ull unsigned ll
#define pll pair<ll,ll>
#define fs first
#define sc second
#define all(v) v.begin(),v.end()
#define pb push_back
#define ppb pop_back
#define getc getchar
#define putc putchar
#define N 500005
using namespace std;
const ll nv = 1e3;
vector<ll> e[N];
inline void add(ll x, ll y) {
    e[x].pb(y);
}
struct ACAM {
    ll idt, ft[N], t[N][26];
    inline ll insert(string s) {
        ll p = 0;
        for (auto j : s) {
            ll c = j - 'a';
            if (!t[p][c])
                t[p][c] = ++idt;
            p = t[p][c];
        }
        return p;
    }
    inline void build() {
        queue<ll> q;
        for (ll i = 0; i < 26; i++)
            if (t[0][i])
                q.push(t[0][i]);
        while (q.size()) {
            ll x = q.front();
            q.pop();
            for (ll i = 0; i < 26; i++) {
                ll &y = t[x][i];
                if (y) {
                    ft[y] = t[ft[x]][i];
                    q.push(y);
                } else
                    y = t[ft[x]][i];
            }
        }
        for (ll i = 1; i <= idt; i++)
            add(ft[i], i);
    }
    inline void print() {
        cerr << "edge:\n";
        for (ll i = 0; i <= idt; i++)
            for (ll j = 0; j < 26; j++)
                if (t[i][j])
                    cerr << i << ' ' << t[i][j] << ' ' << char(j + 'a') << '\n';
        cerr << "\nlink:\n";
        for (ll i = 1; i <= idt; i++)
            cerr << ft[i] << ' ' << i << '\n';
    }
} acam;
struct SGT {
    ll idt, rt[N];
    struct node {
        ll ls, rs, sum;
    } t[N * 20];
    inline void pushup(ll p) {
        t[p].sum = t[t[p].ls].sum + t[t[p].rs].sum;
    }
    inline void change(ll p, ll &q, ll l, ll r, ll x, ll k) {
        q = ++idt, t[q] = t[p];
        if (l == r) {
            t[q].sum += k;
            return;
        }
        ll mid = l + r >> 1;
        if (x <= mid)
            change(t[p].ls, t[q].ls, l, mid, x, k);
        else
            change(t[p].rs, t[q].rs, mid + 1, r, x, k);
        pushup(q);
    }
    inline ll query(ll p, ll q, ll l, ll r, ll ql, ll qr) {
        if (ql > qr)
            return 0;
        if (l >= ql && r <= qr)
            return t[q].sum - t[p].sum;
        ll mid = l + r >> 1, ret = 0;
        if (ql <= mid)
            ret += query(t[p].ls, t[q].ls, l, mid, ql, qr);
        if (mid < qr)
            ret += query(t[p].rs, t[q].rs, mid + 1, r, ql, qr);
        return ret;
    }
} sgt;
ll n, m, ts, b[N], d[N], sz[N], son[N], top[N], dfn[N];
vector<ll> w[N], e1[N];
inline void add1(ll x, ll y) {
    e1[x].pb(y);
}
inline void dfs1(ll x) {
    sz[x] = 1;
    for (auto y : e[x]) {
        d[y] = d[x] + 1;
        sgt.rt[y] = sgt.rt[x];
        for (auto i : w[y])
            sgt.change(sgt.rt[y], sgt.rt[y], 1, nv, i, 1);
        dfs1(y), sz[x] += sz[y];
        if (!son[x] || sz[y] > sz[son[x]])
            son[x] = y;
    }
}
inline void dfs2(ll x, ll tp) {
    top[x] = tp, dfn[x] = ++ts;
    if (son[x])
        dfs2(son[x], tp);
    for (auto y : e[x])
        if (y != son[x])
            dfs2(y, y);
}
inline ll LCA(ll x, ll y) {
    while (top[x] != top[y]) {
        if (d[top[x]] < d[top[y]])
            swap(x, y);
        x = acam.ft[top[x]];
    }
    return d[x] < d[y] ? x : y;
}
inline void uniq(vector<ll> &v) {
    ll lim = unique(all(v)) - v.begin();
    while (v.size() > lim)
        v.ppb();
}
inline void dfs3(ll x) {
    for (auto y : e1[x])
        dfs3(y), b[x] += b[y];
}
vector<pll> lk;
inline bool check(ll mid, ll k) {
    ll sum = 0;
    for (auto i : lk) {
        ll x = i.fs, y = i.sc;
        sum += sgt.query(sgt.rt[x], sgt.rt[y], 1, nv, (mid - 1) / b[y] + 1, nv);
    }
    return sum >= k;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    for (ll i = 1; i <= n; i++) {
        string s;
        cin >> s;
        ll x;
        cin >> x;
        w[acam.insert(s)].pb(x);
    }
    acam.build();
    d[0] = 1, dfs1(0), dfs2(0, 0);
    while (m--) {
        string s;
        ll k, p = 0;
        cin >> s >> k;
        vector<ll> tp;
        tp.pb(0);
        for (auto i : s) {
            ll c = i - 'a';
            p = acam.t[p][c];
            tp.pb(p), b[p]++;
        }
        sort(all(tp), [&](ll x, ll y) {
            return dfn[x] < dfn[y];
        });
        uniq(tp);
        ll sz = tp.size();
        for (ll i = 1; i < sz; i++)
            tp.pb(LCA(tp[i - 1], tp[i]));
        sort(all(tp), [&](ll x, ll y) {
            return dfn[x] < dfn[y];
        });
        uniq(tp);
        lk.clear();
        for (ll i = 1; i < tp.size(); i++) {
            ll lca = LCA(tp[i - 1], tp[i]);
            add1(lca, tp[i]);
            lk.pb({lca, tp[i]});
        }
        dfs3(tp[0]);
        ll l = 1, r = 1e8, mid, ans = 0;
        while (l <= r) {
            mid = l + r >> 1;
            if (check(mid, k))
                ans = mid, l = mid + 1;
            else
                r = mid - 1;
        }
        cout << ans << '\n';
        for (auto i : tp)
            b[i] = 0, e1[i].clear();
    }
    return 0;
```

---

## 作者：Luciylove (赞：0)

# Preface

几年前的题看下来确实是简单了。

#  Solution 

哥太过套路了导致这个题。

我们称 $s_i$ 为小串，$S$ 为大串。

考虑建出关于 $s_i$ 的 ACAM 的 fail 树。 

我们考虑将 $S$ 和 ACAM 进行匹配得到 $|S|$ 个节点，我们对其建出虚树方便我们计算答案。

注意到 kth 问题的常见解法是二分答案，所以我们先二分答案 $T$。

我们利用虚树上面的节点 $x$ 计算答案。每次我们只考虑 $fa_x \to x$ 这一段祖先-后代链上的字符串 $s_i$ 的答案，注意到我们当前节点会对这些节点的 $v_i$ 产生 $\times sz_x$ 的贡献，所以只需要查询 $v_i \geq \lceil \frac{T}{cnt_x}\rceil$, 如果要精细地实现，这等价于入栈序上在线二维数点，使用主席树即可。

复杂度大概是 $O(\sum |S| \log V \log ans )$。

代码如下：


```cpp
#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = l; i <= r; i ++)
#define per(i, r, l) for (int i = r; i >= l; i --)

using namespace std;

typedef long long ll;
const int _ = 5e5 + 5, V = 1e3;
int read() {
    int x = 0, f = 1;
    char ch = getchar();

    while (ch < '0' || ch > '9') {
        if (ch == '-')
            f = -1;

        ch = getchar();
    }

    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - 48;
        ch = getchar();
    }

    return x * f;
}


int n, q, dfc;
int cnt = 1, ch[_][26], fail[_];
int dfn[_], pa[_][20], sz[_], dep[_];
int val[_];

vector <int> e[_], mark[_];

void insert(string T, int id) {
    int x = 1;
    rep(i, 0, T.size() - 1) {
        int idx = T[i] - 'a';

        if (!ch[x][idx])
            ch[x][idx] = ++ cnt;

        x = ch[x][idx];
    }
    mark[x].push_back(id);
}
void BFS() {
    queue <int> q;
    rep(i, 0, 25) ch[0][i] = 1;
    q.push(1);

    while (! q.empty()) {
        int u = q.front();
        q.pop();
        rep(i, 0, 25) {
            if (ch[u][i])
                q.push(ch[u][i]), fail[ch[u][i]] = ch[fail[u]][i];
            else
                ch[u][i] = ch[fail[u]][i];
        }
        e[fail[u]].push_back(u);
    }
}

int tot, rt[_], t[_ * 15], lc[_ * 15], rc[_ * 15];
void insert(int &x, int y, int l, int r, int p, int v) {
    x = ++ tot;
    t[x] = t[y] + v, lc[x] = lc[y], rc[x] = rc[y];

    if (l == r)
        return ;

    int mid = (l + r) >> 1;
    p <= mid ? insert(lc[x], lc[y], l, mid, p, v) : insert(rc[x], rc[y], mid + 1, r, p, v);
}
int query(int x, int y, int l, int r, int ql, int qr) {
    if (ql > qr)
        return 0;

    if (ql <= l && r <= qr)
        return t[x] - t[y];

    int mid = (l + r) >> 1, ret = 0;

    if (ql <= mid)
        ret = query(lc[x], lc[y], l, mid, ql, qr);

    if (qr > mid)
        ret += query(rc[x], rc[y], mid + 1, r, ql, qr);

    return ret;
}
void dfs(int x) {
    dfn[x] = ++ dfc,
             pa[x][0] = fail[x], dep[x] = dep[fail[x]] + 1;

    if (mark[x].size()) {
        rt[x] = rt[fail[x]];

        for (int y : mark[x]) {
            insert(rt[x], rt[x], 1, V, val[y], 1);
        }
    } else
        rt[x] = rt[fail[x]];

    rep(i, 1, 19) pa[x][i] = pa[pa[x][i - 1]][i - 1];

    for (int y : e[x])
        dfs(y);
}

int stp, st[_];
vector <int> G[_], Node;
bool cmp(int x, int y) {
    return dfn[x] < dfn[y];
}
int LCA(int x, int y) {
    if (dep[x] < dep[y])
        swap(x, y);

    int d = dep[x] - dep[y];
    rep(i, 0, 19)

    if (d & (1 << i))
        x = pa[x][i];

    if (x == y)
        return x;

    per(i, 19, 0)

    if (pa[x][i] != pa[y][i])
        x = pa[x][i], y = pa[y][i];

    return pa[x][0];
}
void ins(int x) {
    if (stp == 1) {
        st[++ stp] = x;
        return;
    }

    int ance = LCA(x, st[stp]);

    while (stp > 1 && dep[ance] < dep[st[stp - 1]])
        G[st[stp - 1]].push_back(st[stp]), stp --;

    if (dep[ance] < dep[st[stp]])
        G[ance].push_back(st[stp --]);

    if (!stp || st[stp] != ance)
        st[++ stp] = ance;

    st[++ stp] = x;
}
void buildVT() {
    st[stp = 1] = 1;


    set <int> s(Node.begin(), Node.end());
    Node.assign(s.begin(), s.end());
    sort(Node.begin(), Node.end(), cmp);

    for (int j = 0; j < Node.size(); j ++)
        ins(Node[j]);

    while (stp)
        G[st[stp - 1]].push_back(st[stp]), stp --;

    Node.clear();
}
void getsz(int x) {
    for (int y : G[x])
        getsz(y), sz[x] += sz[y];
}
int check(int x, int fa, int v) {
    int cnt = 0;

    for (int y : G[x])
        cnt += check(y, x, v);

    int ra = v / sz[x];

    if (ra * sz[x] < v)
        ra ++;

    int T = query(rt[x], rt[fa], 1, V, ra, V);
    cnt += query(rt[x], rt[fa], 1, V, ra, V);
    return cnt;
}
void clr(int x) {
    sz[x] = 0;

    for (int y : G[x])
        clr(y);

    G[x].clear();
}

int main() {
    n = read(), q = read();
    rep(i, 1, n) {
        string S;
        cin >> S, insert(S, i);
        val[i] = read();
    }
    BFS();
    dfs(1);

    while (q --) {
        string S;
        cin >> S;
        int x = 1, k = read();
        rep(i, 0, S.size() - 1)
        x = ch[x][S[i] - 'a'], Node.push_back(x), sz[x] ++;
        buildVT();
        getsz(1);
        int l = 1, r = 1000 * 500000, ret = 0;

        while (l <= r) {
            int mid = (l + r) >> 1;

            if (check(1, 0, mid) >= k)
                l = mid + 1,
                ret = mid;
            else
                r = mid - 1;
        }

        printf("%d\n", ret);
        clr(1);
    }

    return 0;
}
```

---

## 作者：happybob (赞：0)

题意：给定 $n$ 个字符串 $s_i$，每个字符串有权值 $v_i$。$q$ 次询问，每次给定一个字符串 $S$ 和一个数 $k$。定义 $cnt_i$ 为 $s_i$ 在 $S$ 中出现次数。求 $cnt_i \times v_i$ 的第 $k$ 大的值。

范围：$n, m \leq 10^5$，$\sum \left| s_i \right|, \sum \left| S_i \right| \leq 5 \times 10^5$，$k \leq n$。字符集只有 $\{\texttt{a,b,c,d}\}$。时限 $2$ 秒。

解法：

建出 AC 自动机的 $fail$ 树后，就等价于若干个点，支持到根路径每个点 $cnt$ 加 $1$。修改后求 $cnt_i \times v_i$ 的第 $k$ 大。不存在字符串末尾的点视为 $k=0$ 即可。

直接做不支持多组询问。不太对。考虑二分。就变成了询问有多少个点 $cnt_i \times v_i > x$。但是还是不太好做。

多次询问，每次给若干个点。这不是虚树吗？虚树上每条边上的点的 $cnt$ 值都相同，等于这条边下面那个点子树和。于是这些边上要满足 $v_i > \dfrac{x}{sz_v}$。就变成了询问链上点权大于某数个数的点数。直接主席树维护即可。由于 $k$ 个点建虚树只有 $O(k)$ 条边，总复杂度 $2\log$。

关于虚树：

把树视为有根树。

建立虚树需要有一个关键点集合 $S$，通常要把根加入 $S$，设为 $S=\{s_1,s_2,\cdots,s_k\}$。虚树只包含所有关键点和任意一个关键点子集的 LCA。连边方式按照祖先关系。

先说怎么求虚树点集。

$\text{Lemma 1.}$ 任意点集 $S$ 的 LCA 为其中 DFS 序最小的和最大的两个点的 LCA。

$\text{Proof.}$ 记 DFS 序列最小和最大两点分别为 $u$ 和 $v$。容易知道点集 $S$ 的 LCA 必然是 $u,v$ 的 LCA 的祖先。我们只需要证明点集 $S$ 中任意一个点都在 $u,v$ 的 LCA 子树内。显然假如有一个不在子树内，那 DFS 序最小和最大的必然不是 $u,v$。证毕。

于是我们只需要求出任意两点 LCA 加入虚树点集即可。然而这个复杂度还是 $O(k^2 \log n)$ 的，不能接受。

$\text{Lemma 2.}$ 将点集按 DFS 序排序，取相邻两个点的 LCA 加入虚树集合即可。

$\text{Proof.}$ 本质等价于证明对于任意 $i < j$，$s_i$ 和 $s_j$ 的 LCA 都被加入过虚树。

归纳证明，当 $j - i =1$ 时，显然。考虑 $j-i>1$。我们知道 $s_i$ 与 $s_{j-1}$ 的 LCA 必然被加入过。如果 $s_j$ 不在这两个点 LCA 子树内，那么考虑 $s_{j-1}$ 和 $s_j$ 的 LCA 即为 $s_i$ 和 $s_j$ 的 LCA。否则 $s_i$ 和 $s_j$ 的 LCA 在之前就加入过了。

证毕。

然后我们就做到了在 $O(k \log n)$ 的复杂度内求出虚树点集。然后将虚树内点按 DFS 序排序，相邻两点的 LCA 连向第二个点即可。

容易发现每条边上的点对应的 $cnt$ 都是一样的。

代码：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <queue>
#include <vector>
using namespace std;

using ll = long long;

const int N = 5e5 + 5;

int n, m;
string s[N];
ll v[N];
int pos[N];
vector<int> G[N];

class ACAM
{
public:
	int son[N][4];
	int fail[N];
	int idx;
	int flag[N];
	int ins(string s)
	{
		int u = 1;
		for (auto& j : s)
		{
			int nj = j - 'a';
			if (!son[u][nj]) son[u][nj] = ++idx;
			u = son[u][nj];
		}
		flag[u]++;
		return u;
	}
	void getfail()
	{
		queue<int> q;
		fail[1] = 1;
		for (int i = 0; i < 4; i++)
		{
			fail[son[1][i]] = 1;
			if (son[1][i]) q.push(son[1][i]);
		}
		while (q.size())
		{
			int u = q.front();
			q.pop();
			for (int i = 0; i < 4; i++)
			{
				if (!son[u][i]) son[u][i] = son[fail[u]][i];
				else
				{
					fail[son[u][i]] = son[fail[u]][i];
					q.push(son[u][i]);
				}
			}
		}
		for (int i = 1; i <= idx; i++) if (!fail[i]) fail[i] = 1;
		for (int i = 2; i <= idx; i++)
		{
			G[fail[i]].emplace_back(i);
		}
	}
}ac;

vector<int> total;
int rt[N];
vector<int> nv[N];

class Chairman_tree
{
public:
	int idx;
	struct Node
	{
		int lson, rson;
		ll sum;
	}tr[N * 21];
	void pushup(int u)
	{
		tr[u].sum = tr[tr[u].lson].sum + tr[tr[u].rson].sum;
	}
	int update(int p, int l, int r, int x)
	{
		int u = ++idx;
		tr[u] = tr[p];
		if (l == r)
		{
			tr[u].sum++;
			return u;
		}
		int mid = l + r >> 1;
		if (x <= mid) tr[u].lson = update(tr[p].lson, l, mid, x);
		else tr[u].rson = update(tr[p].rson, mid + 1, r, x);
		pushup(u);
		return u;
	}
	ll qry(int derricklo, int lt, int lt2, int nl, int nr, int l, int r)
	{
		if (l > r) return 0;
		if (nl >= l && nr <= r) return tr[lt].sum + tr[lt2].sum - tr[derricklo].sum;
		int mid = nl + nr >> 1;
		ll res = 0;
		if (l <= mid) res = qry(tr[derricklo].lson, tr[lt].lson, tr[lt2].lson, nl, mid, l, r);
		if (r > mid) res += qry(tr[derricklo].rson, tr[lt].rson, tr[lt2].rson, mid + 1, nr, l, r);
		return res;
	}
}sgt;

int lt[N], dl;
int faf[N][21];
int dep[N];

void dfs(int u, int fa, int d)
{
	dep[u] = d;
	lt[u] = ++dl;
	if (nv[u].size())
	{
		rt[u] = sgt.update(rt[fa], 0, N, nv[u][0]);
		for (int i = 1; i < nv[u].size(); i++) rt[u] = sgt.update(rt[u], 0, N, nv[u][i]);
	}
	else
	{
		rt[u] = rt[fa];
	}
	for (auto& j : G[u]) dfs(j, u, d + 1);
}

class TreeCut
{
public:
	int top[N], sz[N], fa[N], son[N], dep[N];
	void dfs1(int u, int f)
	{
		fa[u] = f;
		sz[u] = 1;
		dep[u] = dep[f] + 1;
		for (auto& j : G[u])
		{
			if (j != f)
			{
				dfs1(j, u);
				sz[u] += sz[j];
				if (sz[son[u]] < sz[j]) son[u] = j;
			}
		}
	}
	void dfs2(int u, int f)
	{
		top[u] = f;
		if (!son[u]) return;
		dfs2(son[u], f);
		for (auto& j : G[u])
		{
			if (j != fa[u] && j != son[u]) dfs2(j, j);
		}
	}
	inline int LCA(int u, int v)
	{
		while (top[u] ^ top[v])
		{
			if (dep[top[u]] < dep[top[v]]) swap(u, v);
			u = fa[top[u]];
		}
		return (dep[u] < dep[v] ? u : v);
	}
}tc;

inline bool cmp(int x, int y)
{
	return lt[x] < lt[y];
}

vector<int> NG[N];
int flag[N];
int sz[N];
int cnt;

void vtdfs(int u)
{
	sz[u] = flag[u];
	for (auto& j : NG[u])
	{
		vtdfs(j);
		sz[u] += sz[j];
	}
}

ll nk;

void calcans(int u, int fa)
{
	for (auto& j : NG[u])
	{
		calcans(j, u);
		// val[i] * sz[j] > nk
		// val[i] > nk / sz[j]
		if (sz[j] && nk / sz[j] + 1 < N)
		{
			ll nval = nk / sz[j] + 1;
			//cnt -= (1ll * nv[j] * sz[j] > nk);
			cnt += sgt.qry(rt[u], 0, rt[j], 0, N, nval, N);
		}
	}
}

int check(ll k)
{
	nk = k;
	cnt = 0;
	vtdfs(1);
	calcans(1, 0);
	return cnt;
}

int main()
{
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n >> m;
	ac.idx = 1;
	for (int i = 1; i <= n; i++)
	{
		cin >> s[i] >> v[i];
		pos[i] = ac.ins(s[i]);
		nv[pos[i]].emplace_back(v[i]);
	}
	ac.getfail();
	dfs(1, 0, 1);
	tc.dfs1(1, 0);
	tc.dfs2(1, 1);
	while (m--)
	{
		string s;
		int k;
		cin >> s >> k;
		total.clear();
		int u = 1;
		for (auto& j : s)
		{
			u = ac.son[u][j - 'a'];
			total.emplace_back(u);
			flag[u]++;
		}
		sort(total.begin(), total.end(), cmp);
		// solve
		vector<int> vec;
		for (int i = 0; i + 1 < total.size(); i++)
		{
			vec.emplace_back(total[i]);
			vec.emplace_back(tc.LCA(total[i], total[i + 1]));
		}
		vec.emplace_back(total.back());
		vec.emplace_back(1);
		sort(vec.begin(), vec.end(), cmp);
		vec.erase(unique(vec.begin(), vec.end()), vec.end());
		for (int i = 0; i + 1 < vec.size(); i++)
		{
			NG[tc.LCA(vec[i], vec[i + 1])].emplace_back(vec[i + 1]);
		}
		ll l = 0ll, r = (ll)8e8, ans = 0ll;
		while (l <= r)
		{
			ll mid = l + r >> 1ll;
			if (check(mid) < k) r = mid - 1, ans = mid;
			else l = mid + 1;
		}
		for (auto& j : total) flag[j] = 0;
		for (auto& j : vec) NG[j].clear(), sz[j] = 0;
		cout << ans << "\n";
	}
	return 0;
}
```

---

## 作者：Reunite (赞：0)

好题。

## 一
---

多模匹配，套路地考虑 ACAM，建出 fail 树，把每个串的权值挂在结尾处对应的点上。在 ACAM 上跑文本串，记经过的点序列编号为 $c_{i}$，由 ACAM 性质可得，一个模式串被匹配的次数，等于所有 $c_i$ 在 fail 树上到根的链覆盖次数。想必这是大家都知道的。

直接算是有些困难的，正难则反，考虑直接二分答案，接下来考虑如何判断是否合法即可。假如现在只有一次询问。

比较简单的思路是，我们在 fail 树上打标记，然后每次二分后，求一遍子树的标记和，那么若子树标记数乘上结尾处权值大于二分的 $midans$，则计数器加一，二分判断条件是如果计数器大于 $k$，则显然限制还不够紧，可以上调，反之亦然。

接下来考虑如果询问次数很多为什么就寄了，因为每次都得扫一遍整个 fail 树，复杂度上天。但是发现 $\sum|s|$ 是较小的，也就是说，整个 fail 树上会有大块大块的拥有相同子树标记数的点，而变化的点也只有 $\sum|s|$ 这么多，标记为零的点也不可能在对应点的到根的链上。

这不是很虚树么，想到虚树就简单了。具体地，对于每一个文本串在 ACAM 上跑一遍，把所有节点在 fail 树上建立一棵虚树。外层二分答案，先扫一遍虚树，算出虚树上每一条父子边的标记数，然后就可以根据二分出来的答案计算出至少需要的权值 $x$，问题转化为快速求出一条原树上祖孙链中权值大于等于某个值的标记数量（这个标记是指模式串挂在结尾处的权值）。

然后你发现这玩意是静态的，所以直接上可持久化线段树就好了，每个点从父节点继承一下，然后把自己的贡献加上。询问也是非常朴素的。

## 二
---
于是这题就解决了，复杂度主要是 $O(|S|\log_2|V|\log_2|S|)$。稍微注意一下常数吧，不过我最大的点也只跑了 $150$ms，应该不是很卡常。

话说回来这题其实是可以做到动态修改的串的权值的，只需要把静态的可持久化线段树换成 KDT 做动态三维数点即可，不过复杂度会变成 $O(|S|^{\frac{5}{3}}\log_2|S|)$，当然应该有更好的实现，不过我比较容易想出来的就是这个了。

之前觉得直接暴力算每一条父子边的贡献不是很优美，因为我觉得没有用到点被覆盖的次数与深度之间的单调关系，觉得会有更好的复杂度，不过后来我问了 1kri，他说这个性质并不能很好的利用，那看来这题也只能这样了。

代码细节较多，一定要想清楚了再写，一定要注意经常调试，一定要注意一些 $0$ 相关的问题。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

int n,q,tot=1,tm,cnt;
vector <int> h[500005];
vector <int> g[500005];

int rt[500005];
int lc[4000005];
int rc[4000005];
int t[4000005];

inline int clone(int u){
	cnt++;
	t[cnt]=t[u];
	lc[cnt]=lc[u];
	rc[cnt]=rc[u];
	return cnt;
}

inline int updata(int u,int l,int r,int k){
	u=clone(u);
	if(l==r){
		t[u]++;
		return u;
	}
	int mid=(l+r)>>1;
	if(k<=mid) lc[u]=updata(lc[u],l,mid,k);
	else rc[u]=updata(rc[u],mid+1,r,k);
	t[u]=t[lc[u]]+t[rc[u]];
	return u;
}

inline int query(int u,int v,int l,int r,int L,int R){
	if(L>R) return 0;
	if(L<=l&&r<=R) return t[u]-t[v];
	int mid=(l+r)>>1,s=0;
	if(L<=mid) s+=query(lc[u],lc[v],l,mid,L,R);
	if(R>mid) s+=query(rc[u],rc[v],mid+1,r,L,R);
	return s;
}

int v[100005];
char c[500005];
int fail[500005];
int son[500005][4];

inline void insert(int x){
	int len=strlen(c+1),u=1;
	for(int i=1;i<=len;i++){
		if(!son[u][c[i]-'a']) son[u][c[i]-'a']=++tot;
		u=son[u][c[i]-'a'];
	}
	h[u].emplace_back(x);
	return ;
}

inline void build(){
	queue <int> q;
	for(int i=0;i<4;i++)
		if(son[1][i]){
			int v=son[1][i];
			fail[v]=1;
			q.push(v);
			rt[v]=rt[1];
			for(int o:h[v]) rt[v]=updata(rt[v],1,1000,o);
		}
		else son[1][i]=1;
	while(!q.empty()){
		int u=q.front();
		q.pop();
		for(int i=0;i<4;i++){
			int v=son[u][i];
			if(!v) son[u][i]=son[fail[u]][i];
			else{
				fail[v]=son[fail[u]][i];
				q.push(v);
				rt[v]=rt[fail[v]];
				for(int o:h[v]) rt[v]=updata(rt[v],1,1000,o);
			}
		}
	}
	for(int i=1;i<=tot;i++) g[fail[i]].emplace_back(i);
	return ;
}

int dep[500005];
int sz[500005];
int mson[500005];
int top[500005];
int dfn[500005];

inline void dfsfind(int u){
	sz[u]=1;
	dep[u]=dep[fail[u]]+1;
	for(int v:g[u]){
		dfsfind(v);
		sz[u]+=sz[v];
		if(sz[mson[u]]<sz[v]) mson[u]=v;
	}
	return ;
}

inline void dfstime(int u,int tp){
	top[u]=tp;
	dfn[u]=++tm;
	if(mson[u]) dfstime(mson[u],tp);
	for(int v:g[u])
		if(v!=mson[u]) dfstime(v,v);
	return ;
}

inline int LCA(int u,int v){
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]]) swap(u,v);
		u=fail[top[u]];
	}
	return dep[u]<dep[v]?u:v;
}

int m;
int a[1000005];
int fa[500005];
int ct[500005];

inline void buildtree(){
	a[++m]=1;
	sort(a+1,a+1+m,[](int a,int b){return dfn[a]<dfn[b];});
	int mm=m;
	for(int i=2;i<=mm;i++) a[++m]=LCA(a[i-1],a[i]);
	mm=m;
	sort(a+1,a+1+m,[](int a,int b){return dfn[a]<dfn[b];});
	m=0;
	for(int i=1;i<=mm;i++) if(a[i]!=a[i-1]) a[++m]=a[i];
	for(int i=2;i<=m;i++) fa[a[i]]=LCA(a[i-1],a[i]);
	for(int i=m;i>=1;i--) ct[fa[a[i]]]+=ct[a[i]];

	return ;
}

inline bool check(int x,int k){
	int s=0;
	for(int i=2;i<=m;i++){
		int u=a[i],cnt=ct[u];
		if(!cnt) continue;
		int xx=(x+cnt-1)/cnt;
		s+=query(rt[u],rt[fa[u]],1,1000,xx,1000);
	}
	return s>=k;
}

int main(){
	// freopen("qwq.in","r",stdin);
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++){
		scanf("%s%d",c+1,&v[i]);
		insert(v[i]);
	}
	build();
	dfsfind(1);
	dfstime(1,1);
	while(q--){
		int k,u=1,len;
		scanf("%s%d",c+1,&k);
		m=len=strlen(c+1);
		for(int i=1;i<=len;i++){
			u=son[u][c[i]-'a'];
			a[i]=u,ct[u]++;
		}
		buildtree();
		int l=0,r=5e8,mid,ans=0;
		while(l<=r){
			mid=(l+r)>>1;
			if(check(mid,k)) ans=mid,l=mid+1;
			else r=mid-1;
		}
		printf("%d\n",ans);
		for(int i=1;i<=m;i++) fa[a[i]]=ct[a[i]]=0;
	}

	return 0;
}
```

---

