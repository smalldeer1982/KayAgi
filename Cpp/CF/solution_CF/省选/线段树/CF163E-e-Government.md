# e-Government

## 题目描述

The best programmers of Embezzland compete to develop a part of the project called "e-Government" — the system of automated statistic collecting and press analysis.

We know that any of the $ k $ citizens can become a member of the Embezzland government. The citizens' surnames are $ a_{1},a_{2},...,a_{k} $ . All surnames are different. Initially all $ k $ citizens from this list are members of the government. The system should support the following options:

- Include citizen $ a_{i} $ to the government.
- Exclude citizen $ a_{i} $ from the government.
- Given a newspaper article text, calculate how politicized it is. To do this, for every active government member the system counts the number of times his surname occurs in the text as a substring. All occurrences are taken into consideration, including the intersecting ones. The degree of politicization of a text is defined as the sum of these values for all active government members.

Implement this system.

## 样例 #1

### 输入

```
7 3
a
aa
ab
?aaab
-2
?aaab
-3
?aaab
+2
?aabbaa
```

### 输出

```
6
4
3
6
```

# 题解

## 作者：nkwhale (赞：28)

~~先打广告~~：[更好的阅读体验！](https://www.cnblogs.com/whale-at-cola/p/solution-cf163e.html)

### 题意

[题目传送门](https://www.luogu.com.cn/problem/CF163E)

题目要求在一个可修改的字符串集中进行多模匹配，添加和删除的字符串在一开始给出。

### 思路过程

看到多模匹配，首先想到 AC 自动机，但是这道题目会删除原有字符串，所以考虑在 AC 自动机模板的多模匹配上进行修改。

AC 自动机（普通）：建一棵 Trie，在每个字符串结尾节点标记 $end$ 为 $1$，建 fail 树和 Trie 图，建 fail 树时沿树枝边下传 $end$ 节点数，在 Trie 图上跑节点，累加跑到节点的 $end$ 为答案。

那此题要怎么做呢？

不难发现，一个节点的 $end$ 为在它自身结尾的字符串数加上它在 fail 树上的祖先节点结尾的字符串树。

所以，删去一个字符串就是找到它尾部字符所对应的节点，然后将 fail 树中此节点的子树上的每个点（也就是每个以此节点为祖先的节点）的 $end$ 值 $-1$。

换句话说，删除和添加操作就是在一颗树上每次找一个节点，将它子树中所有点的权值加 $1$ 或减 $1$。

同理，询问操作就是在树上询问一个节点的权。

在预处理出这棵树的 dfs 序后，操作就可以了区间修改、单点查询的裸线段树/树状数组维护。

因为~~写得更少~~常数小，我选的树状数组。

### code
```cpp
#include<cstdio>
#include<queue>
using std::queue;
#define re register
#define fr(k) for(re int k=0;k<26;k++)

const int N=1e6+9;
int t,cnt,tot,tr[N][26],fail[N],id[N],xl[N],xr[N],h[N],v[N],ne[N];
char s[N];
bool del[N];

struct BIT{
	int f[N],n;
	inline void add(int p,int q,int k){
		for(;p<=n;p+=(p&-p)) f[p]+=k;
		for(;q<=n;q+=(q&-q)) f[q]-=k;
	}
	inline int ask(int x){int res=0;for(;x;x^=(x&-x)) res+=f[x];return res;}
}bit;

inline void addedge(int x,int y){v[++t]=y,ne[t]=h[x],h[x]=t;}
inline void adds(int k){
	int x=0,i=0,p;
	scanf("%s",s+1);
	while(s[++i]) p=s[i]-'a',x=tr[x][p]?tr[x][p]:(tr[x][p]=++tot);
	id[k]=x;
}
inline void buildfail(){
	int x;queue<int> q;
	fr(k) if(tr[0][k]) addedge(0,tr[0][k]),q.push(tr[0][k]);
	while(!q.empty()){
		x=q.front(),q.pop();
		fr(k)
			if(tr[x][k]) fail[tr[x][k]]=tr[fail[x]][k],addedge(fail[tr[x][k]],tr[x][k]),q.push(tr[x][k]);
			else tr[x][k]=tr[fail[x]][k];
	}
}
void dfs(int x){
	xl[x]=++cnt;
	for(re int i=h[x];i;i=ne[i]) dfs(v[i]);
	xr[x]=cnt+1;	
}
inline int query(){
	int x=0,i=0,ans=0;
	while(s[++i])
		x=tr[x][s[i]-'a'],ans+=bit.ask(xl[x]);
	return ans;
}

int main(){
	int q,n;scanf("%d%d",&q,&n);
	for(re int i=1;i<=n;i++) adds(i);
	buildfail(),dfs(0);bit.n=cnt;
	for(re int i=1;i<=n;i++) bit.add(xl[id[i]],xr[id[i]],1);
	for(re int i=1,x,j;i<=q;i++){
		scanf("%s",s);
		if(s[0]=='?'){printf("%d\n",query());continue;}
		j=0,x=0;
		while(s[++j]) x=(x<<3)+(x<<1)+(s[j]^48);
		if(s[0]=='-'){if(!del[x]) del[x]=1,bit.add(xl[id[x]],xr[id[x]],-1);}
		else {if(del[x])  del[x]=0,bit.add(xl[id[x]],xr[id[x]],1);}
	}
	return 0;
}

```

球点个赞，谢谢！

---

## 作者：Alex_Wei (赞：9)

> ### VII. [CF163E e-Government](https://www.luogu.com.cn/problem/CF163E)
> 
> 选自 [ACAM 乱做](https://www.cnblogs.com/alex-wei/p/ACAM.html) 题 7。

好久没写 ACAM，都快忘掉了。

显然，对于这类字符串匹配问题，我们最好的选择是 ~~SAM~~ ACAM。当然这题应该也可以用广义 SAM 来做，就是把所有询问的字符串和原来的字符串全部拿过来搞一个广义 SAM，修改就类似 ACAM 用 fail 树的 dfs 序 + BIT 维护一下即可。

~~一不小心直接讲完了。~~

首先对字符串集合 $S$ 建出 ACAM $T_S$。考虑用查询的字符串 $t$ 在 $T_S$ 上面跳。根据 ACAM 的实际意义，假设当前通过字符 $t_i$ 跳到了节点 $p$，那么在 fail 树上从 $p$ 到根节点这一整条路径上的所有节点都表示以 $t_i$ 结尾且与 $t_{1\sim i}$ 的后缀匹配的 $S$ 的所有前缀的**全新的一次出现**。对于 $S$ 的每个字符串记录它在 $T_s$ 的末节点，这样就是单点修改 + 链和，可以用树链剖分维护。

但是，因为**链的顶端是根节点**，所以有一个经典的**单点修改 + 链和 转 子树修改 + 单点查询**的经典套路：对于每次单点修改，将其影响扩大至该点的整个子树，那么每次链和查询只需要求链底这一点的值即可。显然，后者可以 dfs 序 + BIT 轻松维护。时间复杂度 $\mathcal{O}(m\log m)$，其中 $m$ 是字典大小。

两个注意点：

- 多次重复添加算一次，删除也是。
- BIT 循环上界不是 $n$ 而是 ACAM 节点个数。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N=1e6+5;

int n,k,buc[N];
int node,ed[N],son[N][26],fa[N];
vector <int> e[N];
void ins(string s,int id){
	int p=0;
	for(char it:s){
		if(!son[p][it-'a'])son[p][it-'a']=++node;
		p=son[p][it-'a'];
	} ed[id]=p;
}
void build(){
	queue <int> q;
	for(int i=0;i<26;i++)if(son[0][i])q.push(son[0][i]);
	while(!q.empty()){
		int t=q.front(); q.pop();
		for(int i=0;i<26;i++)
			if(son[t][i])fa[son[t][i]]=son[fa[t]][i],q.push(son[t][i]);
			else son[t][i]=son[fa[t]][i];
		e[fa[t]].push_back(t);
	}
}

int dnum,dfn[N],sz[N],c[N];
void add(int x,int v){while(x<=node)c[x]+=v,x+=x&-x;}
int query(int x){int s=0; while(x)s+=c[x],x-=x&-x; return s;}
void dfs(int id){
	dfn[id]=dnum++,sz[id]=1;
	for(int it:e[id])dfs(it),sz[id]+=sz[it]; 
}

int main(){
	cin>>n>>k;
	for(int i=1;i<=k;i++){
		string s; cin>>s,ins(s,i);
	}
	build(),dfs(0);
	for(int i=1;i<=k;i++){
		int id=ed[i];
		add(dfn[id],1);
		add(dfn[id]+sz[id],-1);
		buc[i]=1;
	}
	for(int i=1;i<=n;i++){
		char c; cin>>c;
		if(c=='?'){
			string s; cin>>s;
			long long p=0,ans=0;
			for(char it:s){
				p=son[p][it-'a'];
				ans+=query(dfn[p]);
			}
			cout<<ans<<endl;
		}
		else if(c=='-'){
			int id; cin>>id;
			if(!buc[id])continue;
			buc[id]=0;
			id=ed[id];
			add(dfn[id],-1);
			add(dfn[id]+sz[id],1);
		}
		else if(c=='+'){
			int id; cin>>id;
			if(buc[id])continue;
			buc[id]=1;
			id=ed[id];
			add(dfn[id],1);
			add(dfn[id]+sz[id],-1);
		}
	}
	return 0;
}
```

---

## 作者：George1123 (赞：9)

到蒟蒻温暖的博客园里看 $\to$ [$\tt George1123$](https://www.cnblogs.com/Wendigo/p/13381049.html)

---
## 题面

> [CF163E e-Government](https://www.luogu.com.cn/problem/CF163E)

> 给 $n$ 个字符串 $s_i$ 和 $q$ 个询问，刚开始字符串都服役。每次操作将集合中的一个字符串设为退役或服役，或查询与文本串 $S_i$ 的匹配的服役字符串总次数。

> 数据范围：$1\le n,q\le 10^5$，$1\le \sum|s_i|,\sum|S_i|\le 10^6$。

---
## 蒟蒻语

这是个AC自动机的套路题，但是毕竟套路巧妙而且不得不学，所以蒟蒻写一篇题解。

---
## 蒟蒻解

当这题的字符串不退役时，这就是AC自动机的模板。

回忆一下蒟蒻们是怎么做的：先建一棵Trie树，在有字符串终止节点的位置 $tag=1$。然后考虑到包含一个字符串必然包含一个字符串的后缀，建立 $fail$ 链成为AC自动机，$fail$ 链连接节点成为 $parent$ 树，重算一个节点的 $tag$ 为它在 $parent$ 树上到根节点的路径上的节点的 $tag$ 之和。每次匹配的时候，在AC自动机上跑一遍文本串，累计一下 $tag$ 即可。

让一个字符串退役，就相当于将该字符串在Trie树上的终止节点 $p$ 的 $tag=1$ 变成 $tag=0$。建AC自动机重算 $tag$ 的时候，每个在 $parent$ 树上到根节点的路径上包含 $p$ 的节点的 $tag$ 都会减 $1$。**容易发现 $tag$ 减了 $1$ 的节点，正好就是 $parent$ 树上 $p$ 的子树。**

这时候就可以做了，巨佬可以写个树链剖分或LinkCutTree。但是考虑到这题只需要操作子树，不需要操作链，所以可以不写轻重链剖分，求每个节点的 $dfs$ 序及其子树的 $dfs$ 序区间即可。区间修改、单点查询可以用差分加树状数组。

当然这题有很多细节，而且代码很长，估计能写写调调好久……看蒟蒻代码吧。

---
## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

//Start
typedef long long ll;
typedef double db;
#define mp(a,b) make_pair(a,b)
#define x first
#define y second
#define be(a) a.begin()
#define en(a) a.end()
#define sz(a) int((a).size())
#define pb(a) push_back(a)
const int inf=0x3f3f3f3f;
const ll INF=0x3f3f3f3f3f3f3f3f;

//Data
const int N=1e5,M=1e6+1;
int n,at[N];
bool vis[N];

//FenwickTree
int c[M+2];
void add(int x,int v){
	for(int i=x+1;i<M+2;i+=i&-i) c[i]+=v;
}
int sum(int x){
	int res=0;
	for(int i=x+1;i>=1;i-=i&-i) res+=c[i];
	return res;
}

//ACAM
int cnt=1,ch[M][26];
void insert(int x,string&s){
	int p=0;
	for(int i=0;i<sz(s);i++){
		int c=s[i]-'a';
		if(!~ch[p][c]) ch[p][c]=cnt++;
		p=ch[p][c];
	}
	at[x]=p; //记录第x个字符串的终止节点，方便查找dfs序
}
int fa[M],ind,ld[M],rd[M];//[ld,rd)是自动机节点的子树dfs序区间，ld正好是该节点的dfs序
vector<int> e[M];
void Dfs(int p){
	ld[p]=ind++;
	for(int v:e[p]) Dfs(v);
	rd[p]=ind;
}
void build(){
	queue<int> q;
	for(int c=0;c<26;c++)
		if(~ch[0][c]){
			fa[ch[0][c]]=0;
			e[0].pb(ch[0][c]); //加边建parent树
			// cout<<0<<"->"<<ch[0][c]<<'\n';
			q.push(ch[0][c]); 
		} else ch[0][c]=0;
	while(sz(q)){
		int p=q.front(); q.pop();
		for(int c=0;c<26;c++)
			if(~ch[p][c]){
				fa[ch[p][c]]=ch[fa[p]][c];
				e[fa[ch[p][c]]].pb(ch[p][c]); //加边建parent树
				// cout<<fa[ch[p][c]]<<"->"<<ch[p][c]<<'\n';
				q.push(ch[p][c]);
			} else ch[p][c]=ch[fa[p]][c];
	}
	Dfs(0);
}

//Main
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	int T; cin>>T>>n;
	for(int p=0;p<M;p++){
		fa[p]=-1;
		for(int c=0;c<26;c++) ch[p][c]=-1;
	}
	for(int i=0;i<n;i++){
		string s; cin>>s;
		insert(i,s);
	}
	build();
	for(int i=0;i<n;i++) //刚开始字符串都服役
		vis[i]=1,add(ld[at[i]],1),add(rd[at[i]],-1);
	while(T--){
		char c;	cin>>c;
		if(c=='+'){
			int i; cin>>i,--i;
			if(vis[i]) continue;
			vis[i]=1,add(ld[at[i]],1),add(rd[at[i]],-1);
		} else if(c=='-'){
			int i; cin>>i,--i;
			if(!vis[i]) continue;
			vis[i]=0,add(ld[at[i]],-1),add(rd[at[i]],1);
		} else if(c=='?'){
			string s; cin>>s;
			int res=0,p=0;
			for(int i=0;i<sz(s);i++){
				int c=s[i]-'a';
				p=ch[p][c],res+=sum(ld[p]);
			}
			cout<<res<<'\n';
		}
	}
	return 0;
}
```
---
**祝大家学习愉快！**

---

## 作者：Sin_Watt (赞：8)

## 典型例题

### 第一步，写一份足够暴力的代码

比较套路，容易想到可以先建 ACAM，再在 fail 树上单点修改，链查。咱们直接暴力跳 fail。

```cpp
inline void query()
{
	string s;
	rd(s);
	
	int rt = 0, ans = 0;
	
	for (size_t i = 0; i < s.size(); ++ i)
	{
		rt = son[rt][s[i] - 'a'];
		for (int j = rt; j; j = fai[j])
			ans += cnt[j];
	}
	wr(ans, '\n');
}
```

显然 $O(n^2)$。

### 第二步，去掉没用的部分

如果一个位置不是任何模式串的结尾，那它永远也不会对答案有贡献。于是在建完 ACAM 后，咱们可以对 fail 树做点手脚，让它在向上跳的时候跳过没有贡献的节点。

```cpp
// cnt[i] 表示在i处结尾的字符串数
inline void build()
{
	...
	正常建 ACAM
	...
	
	for (int i = 1; i <= idx; ++ i)
	{
		// 这里好像可以用if？
		while (cnt[fai[i]] == 0 && fai[i] != 0)
			fai[i] = fai[fai[i]];
	}
}
```

这样子，fail 树的深度就低了。用如下的模式串才能达到最大深度 $O(\sqrt{n})$。

```
a
aa
aaa
aaaa
...
```

所以总复杂度就变成了 $O(n\sqrt{n})$。但由于本题数据达到了 ${10}^6$，所以还无法通过。

### 第三步，避免重复的计算

在同一次询问中，fail 树上任意一点到根的链和是固定的。那么果断记忆化。为了方便，这里用递归的形式。

```cpp
// 上次更新时的时间
int m_v[N];
// 当前时间
int &m_q = m_v[0];
// 记录的值
long long m_r[N];

// 求从 u 到根的和
int to_rt(int rt)
{
	if (m_v[rt] != m_q)
	{
		m_v[rt] = m_q;
		m_r[rt] = cnt[rt] + to_rt(fai[rt]);
	}
	return m_r[rt];
}

inline void query()
{
	string s;
	rd(s);
	
	-- m_q;
	
	int rt = 0;
	long long ans = 0;
	
	for (size_t i = 0; i < s.size(); ++ i)
	{
		rt = son[rt][s[i] - 'a'];
		ans += to_rt(rt);
	}
	wr(ans, '\n');
}
```

复杂度抽象，咱这个蒟蒻不会分析。期待路过 dalao 为咱解惑。也期待 hack。

### 最后

到现在你就会发现，一些构造的数据卡不到你，那些随机的数据仍然表现优秀，你甚至还可以继续简单的优化。

**最优解**咱就暂时收下了。[提交记录](https://codeforces.com/problemset/submission/163/257676968)。

随堂检测： [CF1437G](https://www.luogu.com.cn/problem/CF1437G)。

能力提升： [CF587F](https://www.luogu.com.cn/problem/CF587F)。

_优化暴力的美妙，在于咱只需略微出手，就能省下你永远也用不完的时间。_

---

## 作者：Hoks (赞：5)

## 前言
最近刚好重新复习~~学习~~了下 ACAM，写了下 [P2414 [NOI2011] 阿狸的打字机](https://www.luogu.com.cn/problem/P2414)。

感觉如果写完上面那题，应该就能独立切下这题了吧。

写完这两题，对于 ACAM 的理解估计会更深刻吧。
## 思路分析
多模匹配次数问题，很自然的想到 ACAM，问题便成了如何处理修改。

类比上面那题，先建出 fail 树，然后考虑下如何处理加入和删除。

先考虑下正常的 ACAM，就是建出 fail 树后把点权下传给子树中每个点，统计时就是在 trie 图上跑累加点权。

那么不难发现，当我们加入/删除一个字符串的时候，就是把他的 fail 的子树点权 $+1/-1$。

子树修改，果断选择~~树链剖分~~树状数组！（树剖魔怔人是这样的。）

因为只有子树修改，所以 dfs 给 dfn 序跑出来后就成了区间修改，单点查，显然树状数组常数小~~代码短~~。

Tips：如果你 `#define int long long` 就会和我一样全 MLE。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1000010,INF=0x3f3f3f3f3f3f3f3f;
int n,m,q,cntt,dfn[N],ed[N],a[N],id[N];char s[N];vector<int>e[N];
struct BIT//binary_indexed_tree
{
    int c[N],n;BIT(){memset(c,0,sizeof c);}
    inline void modify(int x,int v){for(;x<=n;x+=x&-x) c[x]+=v;}
    inline int query(int x){int res=0;for(;x;x-=x&-x) res+=c[x];return res;}
    inline void mdf(int l,int r,int v){modify(l,v),modify(r+1,-v);}
}tt;
inline void add(int u,int v){e[u].emplace_back(v);}
struct ACAM
{
	struct node{int nxt,ed,v[26];}t[N];int tot=0;
	inline void insert(char s[],int n,int j)
	{
		int u=0;
		for(int i=1;i<=n;i++){if(!t[u].v[s[i]-'a']) t[u].v[s[i]-'a']=++tot;u=t[u].v[s[i]-'a'];}
		id[j]=u;
	}
	inline void build()
	{
		queue<int>q;
		for(int i=0;i<26;i++) if(t[0].v[i]) add(0,t[0].v[i]),t[t[0].v[i]].nxt=0,q.push(t[0].v[i]);
		while(!q.empty())
		{
			int u=q.front();q.pop();
			for(int i=0;i<26;i++)
				if(t[u].v[i]) t[t[u].v[i]].nxt=t[t[u].nxt].v[i],add(t[t[u].v[i]].nxt,t[u].v[i]),q.push(t[u].v[i]);
				else t[u].v[i]=t[t[u].nxt].v[i];
		}
	}
	inline int query(char s[],int n)
	{
		int u=0,res=0;
		for(int i=1;i<=n;i++) u=t[u].v[s[i]-'a'],res+=tt.query(dfn[u]);
		return res;
	}
}ac;
namespace Fast_IO
{
    static char buf[1000000],*paa=buf,*pd=buf;
    #define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
    inline int read()
    {
        int x(0),t(1);char fc(getchar());
        while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
        while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
        return x*t;
    }
    inline void print(int x)
    {
        if(x<0) putchar('-'),x=-x;
        if(x>9) print(x/10);
        putchar(x%10+'0');
    }
}
using namespace Fast_IO;
namespace KMP
{
	inline bool chk(char c) { return !(c>='a'&&c<='z'||c=='?'||c=='-'||c=='+'); }
	inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1; }
	inline void rd(char s[],int&n)
	{
		s[++n]=getchar();
		while(chk(s[n])) s[n]=getchar();
		while(ck(s[n])) s[++n]=getchar();
		n--;
	}
}
using namespace KMP;
void dfs(int u){dfn[u]=++cntt;for(auto v:e[u]) dfs(v);ed[u]=cntt;}
signed main()
{
	q=read(),n=read();for(int i=1;i<=n;i++) m=0,rd(s,m),ac.insert(s,m,i);
	ac.build();dfs(0);tt.n=cntt;
	for(int i=1;i<=n;i++) tt.mdf(dfn[id[i]],ed[id[i]],1);
	for(int i=1,x,j;i<=q;i++)
	{
		m=0,rd(s,m);x=0,j=2;
		if(s[1]=='?'){print(ac.query(s,m));puts("");continue;}
		while(j<=m) x=(x<<3)+(x<<1)+(s[j]^48),j++;
		if(s[1]=='-'){if(!a[x]) a[x]=1,tt.mdf(dfn[id[x]],ed[id[x]],-1);}
		else{if(a[x]) a[x]=0,tt.mdf(dfn[id[x]],ed[id[x]],1);}
	}
    return 0;
}
```

---

## 作者：影辰 (赞：4)

这道题看完后就觉得是一道AC自动机的题目

第一步，先把所有匹配串插入一颗AC自动机里面

按照AC自动机的计算方法~~（如果不知道，去看一下AC自动机的题解）~~我们每走到一个节点，就要把ans加上是这个节点代表的字符串的后缀中单词的数量

所以，很自然的可以想到插入这个匹配串就是把这个点的权值加一删除则减一

然后经过思考，发现这样子是不对的

例如字符串aba和ba，你插入ba这个字符串，显然aba处的权值也要加一

如果一个一个节点地跳过去，时间复杂度是O(不能过)

怎么办？

如果我们吧fail指针反过来，建成一颗fail树，那么插入一个字符串就相当于把这棵子树所有节点的权值+1

那么就可以使用线段树或者树状数组在log时间内维护

那么时间复杂度是O(l*logl)

tips:建议手动开O2~~可能是我常数太大了~~

附上代码：

```cpp
#pragma GCC optimize (3)
#include<bits/stdc++.h>
#define now c[o].e[k]
#define go(x) for(int i=head[x];i;i=edge[i].nxt)
using namespace std;
const int sz=1e6+527;
int n,m;
int l,sum,ans;
int T,cnt,o,rt,k,tot;
int last[sz],b[sz],f[sz];
int dfn[sz],r[sz],head[sz];
char s[sz];
struct wxp{
    int e[26],fail;
}c[sz];
struct Edge{
    int v,nxt;
}edge[sz<<1];
void add(int x,int sum){
    while(x<=tot){
        f[x]+=sum;
        x+=x&(-x);
    }
}
int query(int x){
    int ret=0;
    while(x){
        ret+=f[x];
        x-=x&-x;
    }
    return ret;
}
void make_edge(int u,int v){
    edge[++cnt]=(Edge){v,head[u]};
    head[u]=cnt;
}
void insert(char s[],int num){
    l=strlen(s);
    o=rt;
    for(int i=0;i<l;i++){
        k=s[i]-'a';
        if(!now) now=++tot;
        o=now;
    }
    last[num]=o;
}
void build(){
    int j;
    queue<int>q;
    o=rt;
    for(k=0;k<26;k++) 
    if(now){
        make_edge(rt,now);
        c[now].fail=rt;
        q.push(now);
    }else now=rt;
    while(q.empty()==0){
        o=q.front();
        q.pop();
        for(k=0;k<26;k++){
            if(now){
                c[now].fail=c[c[o].fail].e[k]?c[c[o].fail].e[k]:rt;
                make_edge(c[now].fail,now);
                q.push(now);
            }
            else now=c[c[o].fail].e[k]?c[c[o].fail].e[k]:rt;
        }
    }
}
void dfs(int x){
    dfn[x]=++T;
    go(x) dfs(edge[i].v);
    r[x]=T;
}
int main(){
    rt=++tot;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
        scanf("%s",s);
        insert(s,i);
    }
    build();
    dfs(rt);
    for(int i=1;i<=m;i++){
        add(dfn[last[i]],1);
        add(r[last[i]]+1,-1);
        b[i]=1;
    }
    while(n--){
        scanf("%s",s);
        l=strlen(s);
        if(s[0]=='+'){
            sum=0;
            for(int i=1;i<l;i++) sum=sum*10+s[i]-'0';
            if(b[sum]) continue;
            add(dfn[last[sum]],1);
            add(r[last[sum]]+1,-1);
            b[sum]=1;
        }
        else if(s[0]=='-'){
            sum=0;
            for(int i=1;i<l;i++) sum=sum*10+s[i]-'0';
            if(b[sum]==0) continue;
            add(dfn[last[sum]],-1);
            add(r[last[sum]]+1,1);
            b[sum]=0;
        }
        else{
            ans=0;
            o=rt;
            for(int i=1;i<l;i++){
                k=s[i]-'a';
                ans+=query(dfn[o=now]);
            }
            printf("%d\n",ans);
        }
    }
}
```

---

## 作者：BlankAo (赞：3)

$\Large\natural$ **CF163E e-Government \ [原题链接](https://www.luogu.com.cn/problem/CF163E) \ [更好阅读体验](https://www.cnblogs.com/BlankAo/p/14375198.html)**

## 解法

这种题算是比较套路的了，我们看见这种多字符串匹配，会想到**AC自动机**。

如果不会**AC自动机**的可以看看 [我的博客](https://www.cnblogs.com/BlankAo/p/14373027.html) ，希望能给您带来帮助。

那么如果我们对于所有字典树节点连边 $i-fail_i$（根节点没有 $fail$，不连边），那么就得到了一棵 **Fail树**。

那么，如果一号点为根节点，那所有 $fail$ 直接或间接指向 $i$ 号点的节点，都在 $i$ 的子树中。

所以查询字符串 $X$ 在字符串 $Y$ 中出现几次，等价于建出 **Trie** 和 **Fail树** 后，在 **Fail树中** 以 “$X$的结束节点”（设为 $i$） 为根的子树中有多少个 $Y$ 包含的节点。

不理解可以看这解释：比如 $j$ 号点是 $Y$ 所包含的，是 $Y$ 的第 $id$ 个节点，那么代表在 $Y$ 查询时，$j$ 跑 $fail$ 可以跑出 $X$，所以 $X$ 是 $Y$ 中 $1\sim id$ 这个子串的后缀。 

先想想只有询问怎么做：

设询问的字符串为 $T$，则显然有这样一个方法：让 $T$ 在 **Trie** 上跑，经过的点对于的 **Fail树节点**权值加一。设一个字符串在 **Trie** 的结尾节点为 $G$，然后我们查询集合 $S$ 中每个字符串的 $G$ ，对应的 **Fail树节点** ，的子树和（可能有点绕）。最后我们再把那些加一的点再减一，复原原来的树。

然而这样时间显然会炸。

但是，给 $T$ 的路径赋值，然后查询每个 $G$ 的子树权值 **等价于** 给 $G$ 的子树赋值，然后查询 $T$ 的路径权值。

所以我们一开始给每个 $G$ 的子树加一，询问时 $T$ 在 **Trie** 上跑，每跑到一个节点，就加上这个节点对应的 **Fail树** 节点的权值。这个操作的复杂度是 $O(|T|)$ 的。

这样修改操作也迎刃而解，增加字符串 $A$ 就给 $G_A$ 子树加一，删除就减一。

最后一个问题：怎么样给一个节点的子树加减？只需要在树的 **DFS序** 上操作即可。因为一个点的子树在 **DFS序** 上是连续的，所以我们只用**区间加值（给子树加减）、单点询问（ $T$ 在 Trie 跑时查询）**就行了，显然套分块模板即可。

## 代码

```c++
#include<bits/stdc++.h>
#define rep(i,x,y) for(int i=x;i<=y;++i)
#define mar(o) for(int E=fst[o];E;E=e[E].nxt)
#define v e[E].to
#define kwei(x) ((x-1)/B+1)
#define kl(x) ((x-1)*B+1)
#define kr(x) (x*B)
using namespace std;
const int n7=1012345;
struct dino{int to,nxt;}e[n7];
int n,T,B,ecnt,fst[n7],a[n7],blo[n7],cnt=1,tre[n7][26],fail[n7];
int ned[n7],head,tail,que[n7],t,L[n7],R[n7];
char cr[n7];bool exi[n7];

int rd(){
   int shu=0;char ch=getchar();
   while(!isdigit(ch))ch=getchar();
   while(isdigit(ch))shu=(shu<<1)+(shu<<3)+(ch^48),ch=getchar();
   return shu;
}

void edge(int sta,int edn){
	ecnt++;
	e[ecnt]=(dino){edn,fst[sta]};
	fst[sta]=ecnt;
}

void insert(int z){
	int len=strlen(cr+1),now=1;
	rep(i,1,len){
		int ch=cr[i]-'a';
		if(!tre[now][ch]){
			cnt++,tre[now][ch]=cnt;
		}
		now=tre[now][ch];
	}
	ned[z]=now;
}

void Gfail(){
	head=1,tail=1,que[1]=1;
	rep(i,0,25)tre[0][i]=1;
	while(head<=tail){
		int now=que[head];
		rep(i,0,25){
			int edn=tre[ fail[now] ][i];
			if(tre[now][i]){
				fail[ tre[now][i] ]=edn;
				edge(edn,tre[now][i]);
				tail++,que[tail]=tre[now][i];
			}
			else tre[now][i]=edn;
		}
		head++;
	}
}

void dfs(int o){
	t++,L[o]=t;
	mar(o)dfs(v);
	R[o]=t;
}

void updat(int l,int r,int val){
	if( kwei(l)==kwei(r) ){
		rep(i,l,r)a[i]+=val;
		return;
	}
	rep(i,l,kr( kwei(l) ))a[i]+=val;
	rep(i,kl( kwei(r) ),r)a[i]+=val;
	rep(i,kwei(l)+1,kwei(r)-1)blo[i]+=val;
}

int Tquery(int z){
	return a[z]+blo[ kwei(z) ];
}

int query(){
	int len=strlen(cr+1),now=1,tot=0;
	rep(i,1,len){
		now=tre[now][ cr[i]-'a' ];
		tot+=Tquery( L[now] );
	} 
	return tot;
}

int main(){
	T=rd(),n=rd();
	rep(i,1,n)scanf("%s",cr+1),insert(i);
	Gfail(),dfs(1);
	B=sqrt(cnt*2);//事实证明，块长这样设会玄学地更快，直接卡到最优解1st
	rep(i,1,n)exi[ ned[i] ]=1,updat(L[ ned[i] ],R[ ned[i] ],1);
	while(T--){
		char sys=getchar();
		while(sys!='-'&&sys!='+'&&sys!='?')sys=getchar();
		if(sys=='+'){
			int z=ned[ rd() ];
			if(!exi[z])updat(L[z],R[z],1),exi[z]=1;
		}
		if(sys=='-'){
			int z=ned[ rd() ];
			if(exi[z])updat(L[z],R[z],-1),exi[z]=0;
		}
		if(sys=='?'){
			scanf("%s",cr+1);
			printf("%d\n",query());
		}
	}
	return 0;
}
```



---

## 作者：ForgotDream_CHN (赞：3)

[在我的博客园中查看](https://www.cnblogs.com/forgot-dream/p/17674583.html)

> 给定 $k$ 个字符串 $t$，一个字符串集合 $S$ 与 $n$ 次操作，初始时 $S$ 为空。操作有三个类型：
> 
> 1. 将指定编号的字符串加入 $S$ 中；
> 2. 将指定编号的字符串从 $S$ 中删除；
> 3. 给定字符串 $s$，询问 $S$ 中所有字符串在 $s$ 中的匹配次数之和。
> 
> $n, k \le 10^5$，$\sum \left|t\right| \le 10^6$，$\sum \left|s\right| \le 10^6$。

首先看到多模式匹配那肯定是优先想到 AC 自动机的。我们先考虑如果问题是给定一个字符串集合 $S$ 与一个字符串 $s$，问 $S$ 中所有字符串在 $s$ 中的匹配次数之和该怎么做。

很简单对吧，我们对字典树上的每一个节点都赋一个 $val$ 值，表示匹配到当前节点的匹配次数之和。初始化终止节点的 $val$ 为 $1$，其他的为 $0$，然后我们容易发现 $val_i = val_i + val_{nxt_i}$，其中 $nxt$ 表示失配指针，然后询问就很简单了，直接遍历整个 $s$ 并同时维护当前走到了哪个节点，然后累加所经过的 $val$ 即可。

再考虑 AC 自动机中加入或删除字符串的本质：

![这是一个 AC 自动机](https://s1.ax1x.com/2023/09/03/pPDk7b6.png)

上图是由 $\texttt{he}$、$\texttt{hi}$、$\texttt{his}$ 与 $\texttt{she}$ 构建出的 AC 自动机，其中蓝色节点表示终止节点，红色边表示失配指针，节点中的数字代表 $val$ 值。

我们考虑删去 $\texttt{he}$ 这个字符串：

![这是删去 he 的 AC 自动机](https://s1.ax1x.com/2023/09/03/pPDkbVK.png)

虚线代表被删除的部分，绿色代表 $val$ 发生了变化的节点。

没看出来吗？再来一个！我们考虑删去 $\texttt{hi}$ 这个字符串：

![这是删去 hi 的 AC 自动机](https://s1.ax1x.com/2023/09/03/pPDkL5D.png)

我们发现，当删除一个字符串时，不仅会影响到当前字符串终止节点的 $val$ 会减少 $1$，失配指针连向当前字符串终止节点的所有节点的 $val$ 也会减少。加入字符串是同理的。

那么我们此时就有一个 $\mathcal{O}\left(n\sum\left|t\right| + \sum \left|s\right|\right)$ 的做法了。在每次加入或删除字符串时就暴力的找出所有需要修改的节点，询问就直接按上边的方法询问就可以了。

但这显然是不够的，我们需要更优的做法。我们考虑去掉字典树上的边，来观察一下失配指针：

![这是 AC 自动机的失配指针](https://s1.ax1x.com/2023/09/03/pPDkXPe.png)

可以发现，除去初始节点的失配指针由自身转移到自身之外，失配指针天然构成一个树形结构。我们还可以看出，每次字符串修改所影响的节点全部都位于当前字符串终止节点的子树中！

那么现在就好做了。看到子树修改，我们自然会联想到将树用 DFS 序拍平然后转化为序列修改再用线段树等结构维护。但是本题是区间修改单点查询，可以转化为差分序列然后用树状数组来做（而且线段树被卡空间了），那么这样就可以做到时间复杂度 $\mathcal{O}\left(n\log\sum\left|t\right| + \sum \left|s\right|\right)$。

[代码很好写。](https://codeforces.com/contest/163/submission/221423877)

---

## 作者：toolong114514 (赞：2)

# CF163E e-Government 题解
## 题面大意
[传送门。](https://www.luogu.com.cn/problem/CF163E)
## 解题思路
~~比较毒瘤的数据结构拼字符串。~~

忽略添加和删除操作的话，这就是一个裸的 AC 自动机。

不会 AC 自动机的可以先看这道[模板题](https://www.luogu.com.cn/problem/P5357)。

注意到只要求所有模式串匹配的答案，所以从贡献的角度推导。

考虑从 AC 自动机的本质操作分析：

记一个字符串被插入字典树后，在代表它的节点中，最深的那个为关键点。

在匹配的时候，我们通过跳 fail 来查找字典树上能匹配上的点，然后往上跳 fail 计算答案。这个操作相当于从 fail 树上的一个点跳到编号为 $0$ 的根。

在模板题中，这么做会超时。有一种优化思路，是预处理每个节点（包括其本身）**跳 fail 能找到的关键点（即模式串完全匹配成功）数量**，在某个点匹配成功时，直接加上预处理的值。

是否可以通过维护 fail 树上所有节点跳到根节点路径上的关键点数量呢？

事实上完全可以。

当某个模式串被删去后，只“抹去”关键点，让关键点变为普通点。

因为我们的贡献都在 fail 树上**某个节点跳到根节点的路径上**，所以“抹去”关键点只会对**关键点及其子树的节点的贡献产生影响**。只需要批量对子树的每个点贡献减去 $1$ 即可。

增加操作同理。

每次匹配成功，加贡献的时候，现场查询并加入答案。

我们只需要一个数据结构，支持树上的子树修改，单点查询，就能做完这题。

考虑将 fail 树按 dfs 序拍成一个序列，于是转化为区间修改，单点查询。考虑用线段树维护。

~~如果你想搬树剖板子过来我也不好说什么。~~

但是，此题的空间限制很毒瘤，线段树可能过不了，所以把原问题转化为差分数组上的单点修改，区间询问前缀和，用树状数组处理。

总的时间复杂度约为 $O(n\log n)$，可以通过本题。

虽然空间复杂度是 $O(n)$ 的，但是要注意合理分配空间使用！
## 参考代码
```cpp
#include<iostream>
#include<cstring>
#include<queue>
using namespace std;
const int N=1e6+10;
int lowbit(int x){
	return x&(-x);
}
struct sb{
	int to,nxt;
}edge[2*N];
int head[N];
int ntt;
void add(int u,int v){
	edge[++ntt]={v,head[u]};
	head[u]=ntt;
}
bool is_end[N];
int dfn[N],conb[N],in[N],out[N];
int tmr;
void dfs(int x,int last,int ttt){
	if(is_end[x]) ttt++;
	dfn[x]=++tmr;
	in[x]=tmr;
	conb[tmr]=ttt;
	for(int i=head[x];i!=-1;i=edge[i].nxt){
		if(edge[i].to==last) continue;
		dfs(edge[i].to,x,ttt);
	}
	out[x]=tmr;
}
struct node{
	int son[26];
}trie[N];
int cnt;
int fail[N];
char str[N];
int ins(int &pos,int sp,int len){
	int fa=0,now=trie[0].son[str[0]-'a'];
	while(true){
		sp++;
		if(!now) now=++cnt;
		trie[fa].son[str[sp]-'a']=now;
		if(sp==len-1) return now;
		fa=now;
		now=trie[now].son[str[sp+1]-'a'];
	}
}
queue<int> q;
int a[N];
bool exi[N];
int trans[N];
int root;
void upd(int x,int v){
	while(x<=tmr){
		a[x]+=v;
		x+=lowbit(x);
	}
}
int ask(int x){
	int tmp=0;
	while(x>0){
		tmp+=a[x];
		x-=lowbit(x);
	}
	return tmp;
}
void build_fail(){
	while(!q.empty()) q.pop();
	for(int i=0;i<26;i++){
		if(trie[0].son[i]) q.push(trie[0].son[i]);
	}
	while(!q.empty()){
		int now=q.front();
		q.pop();
		for(int i=0;i<26;i++){
			if(!trie[now].son[i]) continue;
			int j=fail[now];
			while(j!=0&&!trie[j].son[i]){
				j=fail[j];
			}
			fail[trie[now].son[i]]=trie[j].son[i];
			q.push(trie[now].son[i]);
		}
	}
	for(int i=1;i<=cnt;i++){
		add(i,fail[i]);
		add(fail[i],i);
	}
	dfs(0,-1,0);
	for(int i=1;i<=tmr;i++){
		upd(i,conb[i]-conb[i-1]);
	}
}
int vst[N]; 
char s[N];
int n,k,ml;
int comp(){
	int tt=0,zyhlqr=0;
	for(int i=0;i<ml;i++){
		while(tt&&!trie[tt].son[s[i]-'a']) tt=fail[tt];
		tt=trie[tt].son[s[i]-'a'];
		zyhlqr+=ask(in[tt]);		
	}
	return zyhlqr;
}
char xh[N];
int main(){
	memset(head,-1,sizeof(head));
	ios::sync_with_stdio(false);
	cin>>n>>k;
	for(int i=1;i<=k;i++){
		cin>>str;
		trans[i]=ins(root,-1,strlen(str));
		is_end[trans[i]]=true;
		exi[i]=true;
	}
	build_fail();
	while(n--){
		cin>>xh;
		int tlen=strlen(xh);
		if(xh[0]=='?'){
			ml=0;
			for(int i=1;i<tlen;i++){
				s[ml++]=xh[i];
			}
			cout<<comp()<<'\n';
		}else if(xh[0]=='+'){
			int num=0;
			for(int i=1;i<tlen;i++){
				num*=10;
				num+=xh[i]-'0';
			}
			if(exi[num]) continue;
			exi[num]=true;
			upd(in[trans[num]],1);
			upd(out[trans[num]]+1,-1);
		}else{
			int num=0;
			for(int i=1;i<tlen;i++){
				num*=10;
				num+=xh[i]-'0';
			}
			if(!exi[num]) continue;
			exi[num]=false;
			upd(in[trans[num]],-1);
			upd(out[trans[num]]+1,1);
		}
	}
	return 0;
} 
```
[本代码可以通过 CF 的评测。](https://www.luogu.com.cn/record/161984903)

Written by [toolong114514](https://www.luogu.com/user/477821) on 2024/6/13.

---

## 作者：_Anchor (赞：2)

# Problem

[CF163E e-Government（AC 自动机+ BIT + dfn 序 + LCA + 序列上差分）](https://www.luogu.com.cn/problem/CF163E)

这么多东西搞在一起其实也没有很难。。

其实我们可以发现，题目就是让我们求每一个串作为某个串的子串出现次数之和。（好像更难理解了。）

看一下样例就知道了。

```cpp
input：
1 3
a
aa
ab
?aaab

output：
6
```

$6=3+2+1$ ，题意就是这个。

# Solution

那对应到 AC 自动机上面去，就是相当于询问一个串的每个前缀对应节点，Fail 树中从这个点到根节点路径上的 $Endpos$ 标记之和。

同时还带修，支持把某个点的 $Endpos$ 标记减一和加一。

暴力做当然是可以的，直接树剖或者 LCT 对着链上和一顿操作即可，但是这样做很麻烦（AC 自动机套个 LCT 就显得很烦了。。虽然码量也不算特别大。）

那么根据树上差分的思想，其实我们可以把原题从：

单点修改，链上查询。

变成：子树区间修改，单点查询。

然后我们再利用序列差分变成：单点修改，子树区间查询。

具体来说就是利用序列差分，先打一下 dfn 序，然后树状数组维护这两个操作即可。

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
template <typename T>
inline void read(T &x){
    x=0;char ch=getchar();bool f=false;
    while(!isdigit(ch)){if(ch=='-'){f=true;}ch=getchar();}
    while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    x=f?-x:x;
    return ;
}
template <typename T>
inline void write(T x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10^48);
    return ;
}
const int N=1e6+5;
#define ll long long
int n,m;
int Q;
char str[N];

int ch[N][26],val[N],fail[N],rev[N],tot,root;
int nex[N],head[N],to[N],idx;
int dep[N],siz[N],son[N],top[N],fa[N],dfn[N],cnt;
int c[N];
bool cmp(const int &x,const int &y){return dfn[x]<dfn[y];}
void Insert(string str,int id){
	int len=str.size(),p=root;
	for(int i=0;i<len;i++){
		int c=str[i]-'a';
		if(!ch[p][c]) ch[p][c]=++tot;
		p=ch[p][c];
	}
	rev[id]=p;
	return ;
}
void Modify(int x,int v){
	if(!x) return ;
	for(;x<=cnt;x+=(x&(-x))) c[x]+=v;
	return ;
}
int Ask(int x){
	int res=0;
	for(;x>0;x-=(x&(-x))) res+=c[x];
	return res;
}
void add(int u,int v){
	nex[++idx]=head[u];
	to[idx]=v;
	fa[v]=u;
	head[u]=idx;
	return ;
}
void dfs1(int x,int f){
	siz[x]=1,dep[x]=dep[f]+1,fa[x]=f;
	for(int i=head[x];i;i=nex[i]){
		int y=to[i];
		dfs1(y,x);
		siz[x]+=siz[y];
		if(siz[y]>siz[son[x]]||!son[x]) son[x]=y;
	}
	return ;
}
void dfs2(int x){
	if(x==son[fa[x]]) top[x]=top[fa[x]];
	else top[x]=x;
	dfn[x]=++cnt;
	if(son[x]) dfs2(son[x]);
	for(int i=head[x];i;i=nex[i]){
		int y=to[i];
		if(y==son[x]) continue;
		dfs2(y);
	}
	return ;
}
void Build(){
	queue<int> q;	
	for(int i=0;i<26;i++) if(ch[root][i]) q.push(ch[root][i]);
	while(!q.empty()){
		int p=q.front();q.pop();
		for(int i=0;i<26;i++){
			if(ch[p][i]) fail[ch[p][i]]=ch[fail[p]][i],q.push(ch[p][i]);
			else ch[p][i]=ch[fail[p]][i];
		}
	}
	return ;
}
int QueryLca(int x,int y){while(top[x]!=top[y]){if(dep[top[x]]<dep[top[y]]){swap(x,y);}x=fa[top[x]];}return dep[x]<dep[y]?x:y;}
void ADD(){
	for(int i=1;i<=tot;i++) add(fail[i],i);
	return ;
}
void Into(int x,int tag){
	Modify(dfn[x],tag),Modify(dfn[x]+siz[x],-tag);
	return ;
}
int Query(char *str){
	int len=strlen(str),p=root,res=0;
	for(int i=0;i<len;i++) p=ch[p][str[i]-'a'],res+=Ask(dfn[p]);
	return res;
}
string S[N];
bool vis[N];
int main(){
	read(Q),read(n);
	for(int i=1;i<=n;i++) cin>>S[i],Insert(S[i],i);
	Build();ADD();
	dfs1(0,0);dfs2(0);
	for(int i=1;i<=n;i++) Into(rev[i],1),vis[i]=true;
    while(Q--){
        char op;int x;op=getchar();
        while(op!='-'&&op!='+'&&op!='?') op=getchar();
        if(op=='-'){
        	read(x);
        	if(!vis[x]) continue;
        	vis[x]=false;
			Into(rev[x],-1);
        }
        else if(op=='+'){
        	read(x);
        	if(vis[x]) continue;
        	vis[x]=true;
			Into(rev[x],1);
        }
        else if(op=='?') scanf("%s",str),printf("%d\n",Query(str));
    }
	return 0;
} 
```

# Ex（延伸）

总的来说，这道题厉害的是那个题意的转化，也就是相当于反其道而行，其实我们这里的变化（尤其是从第一步到第二步），就是一个查询和修改的变换，有时候查询好统计，修改不好改，有时候修改方便，查询却又不利，这个时候我们就要学会变通。

再比如，一道题修改某些东西，我们会先考虑怎么去维护这个修改，但实际上我们也可以考虑每次修改对答案的影响。

所以，我们要做到的就是平衡，想问题要角度多一些。



---

## 作者：crashed (赞：2)

# 题目
&emsp;&emsp;[点这里](https://www.luogu.com.cn/problem/CF163E)看题目。  
# 分析
&emsp;&emsp;首先，我们不需要真的从 AC 自动机中把串删掉。由于我们计算贡献和，我们只需要在 AC 自动机上，把已经删除的串的贡献抹掉就可以了。  
&emsp;&emsp;接着考虑询问。这是一个很基础的问题，一般我们会在 AC 自动机上面处理出每个状态的贡献和，并且将询问的字符串在 AC 自动机上面跑一跑，答案就是经过的状态的贡献和的贡献和。  
&emsp;&emsp;现在贡献是动态的，我们的贡献和也变成了动态的。不过，由于贡献和本质上就是 **fail 树上到根的路径的贡献和** ，因此我们可以对 fail 树进行树链剖分，修改就是单点修改，查询就查询到根的贡献和。这样就可以用 BIT 来维护一下区间和。  
&emsp;&emsp;另一种更简单的方法是，在一个点上改贡献的时候，**有且仅有其子树内的点会被影响**，因此我们用 BIT 维护差分，每次修改就是将子树内的贡献 +1 ，查询就直接查询。这样做就少了一个$\log_2n$。    
&emsp;&emsp;这两种方法体现了两种不同的思想——**统计贡献**和**维护贡献**；两者需要具体问题具体分析再选择使用。  
# 代码
```cpp
#include <cstdio>
#include <iostream>
using namespace std;

#define Tour( c ) for( int c = 0 ; c < 26 ; c ++ )
#define up( x ) ( x += ( x & ( -x ) ) )
#define down( x ) ( x -= ( x & ( -x ) ) )

typedef long long LL;

const int MAXN = 1e5 + 5, MAXL = 1e6 + 5;

template<typename _T>
void read( _T &x )
{
	x = 0;char s = getchar();int f = 1;
	while( s > '9' || s < '0' ){if( s == '-' ) f = -1; s = getchar();}
	while( s >= '0' && s <= '9' ){x = ( x << 3 ) + ( x << 1 ) + ( s - '0' ), s = getchar();}
	x *= f;
}

template<typename _T>
void write( _T x )
{
	if( x < 0 ){ putchar( '-' ); x = ( ~ x ) + 1; }
	if( 9 < x ){ write( x / 10 ); }
	putchar( x % 10 + '0' );
}

struct edge
{
	int to, nxt;
}Graph[MAXL << 1];

LL BIT[MAXL];
int head[MAXL], pos[MAXL], siz[MAXL];
int ch[MAXL][26], fail[MAXL], q[MAXL];
int ed[MAXN];
int N, K, tot, cnt, ID;
char S[MAXL];
bool inside[MAXN];

void update( int x, const int v ) { for( ; x <= ID ; up( x ) ) BIT[x] += v; }
LL getSum( int x ) { LL ret = 0; for( ; x ; down( x ) ) ret += BIT[x]; return ret; }
void update( const int x ) { if( ! inside[x] ) inside[x] = true, update( pos[ed[x]], 1 ), update( pos[ed[x]] + siz[ed[x]], -1 ); }
void remove( const int x ) { if( inside[x] ) inside[x] = false, update( pos[ed[x]], -1 ), update( pos[ed[x]] + siz[ed[x]], 1 ); }

void addEdge( const int from, const int to )
{
	Graph[++ cnt].to = to, Graph[cnt].nxt = head[from];
	head[from] = cnt;
}

void insert( const int rnk )
{
	int p = 0, id;
	for( int i = 1 ; S[i] ; i ++ )
	{
		id = S[i] - 'a';
		if( ! ch[p][id] ) ch[p][id] = ++ tot;
		p = ch[p][id];
	}
	ed[rnk] = p;
}

void init()
{
	int h = 1, t = 0, u, v;
	Tour( i ) if( ch[0][i] ) q[++ t] = ch[0][i];
	while( h <= t )
	{
		u = q[h ++];
		Tour( i )
		{
			if( v = ch[u][i] ) fail[v] = ch[fail[u]][i], q[++ t] = v;
			else ch[u][i] = ch[fail[u]][i];
		}
		addEdge( fail[u], u );
	}
}

void DFS( const int u )
{
	siz[u] = 1, pos[u] = ++ ID;
	for( int i = head[u], v ; i ; i = Graph[i].nxt )
		DFS( v = Graph[i].to ), siz[u] += siz[v];
}

int main()
{
	LL ans; int id, p;
	read( N ), read( K );
	for( int i = 1 ; i <= K ; i ++ ) scanf( "%s", S + 1 ), insert( i );
	init(); 
	DFS( 0 );
	for( int i = 1 ; i <= K ; i ++ ) update( i );
	while( N -- )
	{
		scanf( "%s", S );
		if( S[0] == '?' )
		{
			ans = p = 0;
			for( int i = 1 ; S[i] ; i ++ )
				p = ch[p][S[i] - 'a'],
				ans += getSum( pos[p] );
			write( ans ), putchar( '\n' );
		}
		else if( S[0] == '+' ) sscanf( S + 1, "%d", &id ), update( id );
		else sscanf( S + 1, "%d", &id ), remove( id );
	}
	return 0;
}
```

---

## 作者：asuldb (赞：2)

[题目](https://www.luogu.org/problemnew/show/CF163E)

两个$log$的树状数组套树剖？

我们对于给出的$n$个模式串建立$AC$自动机，之后对于每一个询问串直接丢上去匹配

如果这里是暴力的话，我们直接一路跳$fail$累加作为结束位置还没有被删除的点就好了

我们考虑一个快点的方式，树剖

把$fail$树建出来，直接在上面树剖维护就好了

由于只是单点修改，我们树状数组就好了

尽管是两个$log$，但毕竟树剖和树状数组都是出了名的小常数，还是能跑过$1e6$的

代码

```cpp
#include<cstdio>
#include<queue>
#include<cstring>
#include<iostream>
#include<algorithm>
#define re register
#define lb(x) ((x)&(-x))
#define LL long long
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))
const int maxn=1e6+5;
struct E{int v,nxt;}e[maxn];
int n,m,cnt,__,num;
char S[maxn];
int c[maxn],dfn[maxn],sum[maxn],top[maxn],head[maxn];
int son[maxn][26],fa[maxn],pos[maxn],val[maxn],s[maxn];
inline void add_edge(int x,int y) {
	e[++num].v=y;e[num].nxt=head[x];head[x]=num;
}
inline void ins(int o) {
	scanf("%s",S+1);int len=strlen(S+1);
	int now=0;
	for(re int i=1;i<=len;i++) {
		if(!son[now][S[i]-'a']) son[now][S[i]-'a']=++cnt;
		now=son[now][S[i]-'a'];
	}
	pos[o]=now;
}
void dfs1(int x) {
	int maxx=-1;s[x]=-1,sum[x]=1;
	for(re int i=head[x];i;i=e[i].nxt) {
		dfs1(e[i].v);
		sum[x]+=sum[e[i].v];
		if(sum[e[i].v]>maxx) maxx=sum[e[i].v],s[x]=e[i].v;
	}
}
void dfs2(int x,int topf) {
	top[x]=topf,dfn[x]=++__;
	if(s[x]==-1) return;
	dfs2(s[x],topf);
	for(re int i=head[x];i;i=e[i].nxt)
	if(s[x]!=e[i].v) dfs2(e[i].v,e[i].v); 
}
inline void Build() {
	std::queue<int> q;
	for(re int i=0;i<26;i++) if(son[0][i]) q.push(son[0][i]);
	while(!q.empty()) {
		int k=q.front();q.pop();
		for(re int i=0;i<26;i++)
		if(son[k][i]) fa[son[k][i]]=son[fa[k]][i],q.push(son[k][i]);
			else son[k][i]=son[fa[k]][i];
	}
}
inline void add(int x,int v) {for(re int i=x;i<=cnt;i+=lb(i)) c[i]+=v;}
inline int ask(int x) {
	int now=0;
	for(re int i=x;i;i-=lb(i)) now+=c[i];
	return now;
}
inline int query(int l,int r) {return ask(r)-ask(l-1);}
inline int Query(int x) {
	int tot=0;
	while(top[x]) {
		tot+=query(dfn[top[x]],dfn[x]);
		x=fa[top[x]];
	}
	tot+=query(dfn[0],dfn[x]);
	return tot;
}
int main() {
	scanf("%d%d",&m,&n);
	for(re int i=1;i<=n;i++) ins(i);
	Build();
	for(re int i=1;i<=cnt;i++) add_edge(fa[i],i);
	dfs1(0);dfs2(0,0);cnt++;
	for(re int i=1;i<=n;i++) val[i]=1,add(dfn[pos[i]],1);
	while(m--) {
		scanf("%s",S);int len=strlen(S);
		if(S[0]=='+') {
			int x=0;
			for(re int i=1;i<len;i++) x=(x<<3)+(x<<1)+S[i]-48;
			if(val[x]) continue;
			add(dfn[pos[x]],1);val[x]=1;
		}
		if(S[0]=='-') {
			int x=0;
			for(re int i=1;i<len;i++) x=(x<<3)+(x<<1)+S[i]-48;
			if(!val[x]) continue;
			add(dfn[pos[x]],-1);val[x]=0;
		}
		if(S[0]=='?') {
			int now=0;int ans=0;
			for(re int i=1;i<len;i++) {
				now=son[now][S[i]-'a'];
				ans+=Query(now);
			}
			printf("%d\n",ans);
		}
	}
	return 0;
}
```


---

## 作者：ddwqwq (赞：2)

夜中不能寐，起坐写题解qwq
  
首先看到这是字符串题，还是字符串匹配。于是想到AC自动机。。。然而我觉得它会TLE（？），于是考虑后缀数组。。  

做法：  
1.把所有字符串，包括模板串和查询串，连在一起，中间用奇怪字符隔开（套路qwq）  
2.对于每个模板串，在后缀数组上二分lcp找到可以匹配它的后缀所在的区间（也是套路qwq）  
3.维护一个树状数组，按顺序枚举每一个操作。对于‘+’，把相应模板串对应的可匹配区间加1；对于‘-’，把相应模板串对应的可匹配区间减1；对于‘？’，枚举相应查询串在后缀数组中对应的每一个位置，把它们在树状数组中的值加起来，这就是该询问的答案  
4.没了QwQ  

时间复杂度：O(nlogn)，非常正确qwq

---

## 作者：cflsfzh (赞：1)

很板的一道题，所以看题解的应该是 AC 自动机萌新，所以这里针对萌新稍微讲一下吧。我们如果把它的范围缩小的话，你就会有非常多的方法，对应不同的时间复杂度解这道题，所以我们需要在里面寻找一个适合这道题的解法。发现有很多询问，但是询问串长的总和不超过 $10^6$，所以我们考虑时间复杂度应该是与每次询问的串长挂钩，不应与模式串长挂钩。众所周知，一个模式串终端只会对 fail 树上它的子树产生贡献，我们在询问时时间复杂度不能挂钩到模式串，所以考虑不应拿用匹配串得到的每一个点去扫模式串终端，应将模式串端点的贡献提前加入子树中，这样的话发现时间复杂度非常正确。

于是我们提前在 fail 树上跑 dfs 序，用树状数组维护区间修改和单点查询，对于减操作，让它将子树每个节点 $-1$ 就好了，对于加操作同理，查询时就直接在匹配时加上当前端点的权值就行了。**小心``MLE``**

***Code***


```cpp
#include<bits/stdc++.h>
#define pb push_back
#define pii pair<int,int>
#define fs first
#define sc second
#define il inline
#define re register
#define lowbit(x) (x&-x)
using namespace std;
int read()
{
	re int x=0;
	re int ff=1;
	re char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')
			ff=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=x*10+c-'0';
		c=getchar();
	}
	return x*ff;
}
const int N=1e6+6;
struct ACAM{
	int son[26],fail;
	int & operator [] (int x)
	{
		return son[x];
	}
};
ACAM tree[N];
struct edge{
	int v,next;
};
edge e[N];
int n,m,q,tr[N],l[N],r[N],k,head[N],vis[N],b[N],top,cnt;
char a[N];
void add(int u,int v)
{
	e[++k].v=v;
	e[k].next=head[u];
	head[u]=k;
	return;
}
void get_fail()
{
	queue<int> q;
	for(int i=0;i<26;i++)
		if(tree[0][i])
			q.push(tree[0][i]);
	while(!q.empty()){
		int u=q.front();
		q.pop();
		add(tree[u].fail,u);
		for(int i=0;i<26;i++)
			if(tree[u][i]){
				tree[tree[u][i]].fail=tree[tree[u].fail][i];
				q.push(tree[u][i]);
			}
			else
				tree[u][i]=tree[tree[u].fail][i];
	}
	return;
}
void dfs_dfn(int u)
{
	l[u]=++cnt;
	for(int i=head[u];i;i=e[i].next)
		dfs_dfn(e[i].v);
	r[u]=cnt;
	return;
}
void updata(int x,int z)
{
	for(int i=x;i<=cnt;i+=lowbit(i))
		tr[i]+=z;
	return;
}
int query(int x)
{
	int awa=0;
	for(int i=x;i;i-=lowbit(i))
		awa+=tr[i];
	return awa;
}
signed main()
{
	n=read();
	q=read();
	for(int i=1;i<=q;i++){
		cin>>a+1;
		m=strlen(a+1);
		int u=0;
		for(int j=1;j<=m;j++){
			if(!tree[u][a[j]-'a'])
				tree[u][a[j]-'a']=++top;
			u=tree[u][a[j]-'a'];
		}
		b[i]=u;
		vis[i]=1;
	}
	get_fail();
	dfs_dfn(0);
	for(int i=1;i<=q;i++)
		updata(l[b[i]],1),updata(r[b[i]]+1,-1);
	while(n--){
		char opt;
		cin>>opt;
		if(opt=='-'){
			int x=read();
			if(vis[x]){
				vis[x]=0;
				updata(l[b[x]],-1);
				updata(r[b[x]]+1,1);
			}
		}
		else if(opt=='+'){
			int x=read();
			if(!vis[x]){
				vis[x]=1;
				updata(l[b[x]],1);
				updata(r[b[x]]+1,-1);
			}
		}
		else{
			cin>>a+1;
			m=strlen(a+1);
			int u=0,awa=0;
			for(int i=1;i<=m;i++){
				u=tree[u][a[i]-'a'];
				awa+=query(l[u]);
			}
			printf("%d\n",awa);
		}
	}
	return 0;
}

```

---

## 作者：_Kamisato_Ayaka_ (赞：1)

[更好的阅读体验](https://www.cnblogs.com/Tomori0505/p/18850291)

### Statement 解析

给了字符串集合 $\{S\}$，有 $N$ 次操作，另有与字符串集合 $\{S\}$ 相同的 $\{T\}$，每次给出一种操作：

- 选择编号为 $i$ 的字符串加入 $\{T\}$，已存在于 $\{T\}$ 中不执行。
- 从 $\{T\}$ 中删除编号为 $i$ 的字符串吗，不存在于 $\{T\}$ 中不执行。
- 询问，给定一个字符串 $S'$，求当前集合 $\{T\}$ 中每个串在 $S'$ 中的出现次数之和。

### Solution

看来是比较典的 AC 自动机的题目。

首先我们摸出一个 trick：求子串可以枚举前缀然后考虑这段前缀的后缀。

那么我们对集合 $\{T\}$ 建 AC 自动机，那么当我们从根往下走的时候就是在枚举前缀（因为是 trie 树），然后处理 $fail$ 指针，根据 $fail$ 的含义：指向当前前缀的最长后缀的尾，我们可以通过跳 $fail$ 得到这段前缀的后缀，每个点都有且仅有一个 $fail$ 指针，那么从 $fail_u \to u$ 建边得到的就是一棵外向树（有向且从根指向叶子），原本我们想要的是从 $u$ 跳 $fail_u$ 假设最后跳到 $v$，那么在新建出来的树上 $v$ 在 $u$ 子树内且从 $fail_u$ 到 $u$ 子树内任意结点都是一种可行匹配，那么这就是个子树和问题。

但是这道题带删带修，其实再摸出一个 trick：子树内 dfn 连续，所以可以在 dfn 上子树加一或者减一然后上传区间和，暴力单点查统计，线段树或者树状数组维护都可。

### Code
```cpp
#include <bits/stdc++.h>
//#define int long long
#define son(rt,x) Amt[rt].son[x]
#define fail(rt) Amt[rt].fail
#define lson(rt) (rt << 1)
#define rson(rt) (rt << 1 | 1)
#define len(rt) (Sgt[rt].r - Sgt[rt].l + 1)

using namespace std;
const int MAXN = 1e6 + 10;

int N, K, cnt, ind, idx;
int tail[MAXN], low[MAXN], dfn[MAXN], head[MAXN];
bool tag[MAXN];
string Style, Text;

struct Graphon {
	int to, nxt;
} E[MAXN];

struct AutoMaton {
	int son[26];
	int fail;
} Amt[MAXN];

struct Sgton {
	int l, r, sum, lazy;
} Sgt[MAXN << 2];

inline void Addedge (int u, int v) { E[idx].to = v, E[idx].nxt = head[u], head[u] = idx++; }

inline void InsertString (int ID) {
	int len = Style.length(), now = 0;
	for (int i = 0; i < len; i ++) {
		int chVal = Style[i] - 'a';
		if (!son(now, chVal))
			son(now, chVal) = ++cnt;
		now = son(now, chVal);
	}
	tail[ID] = now;
}

inline void GetFailPointer() {
	queue<int> q;
	for (int i = 0; i < 26; i ++) {
		if (son(0, i)) {
			q.emplace(son(0, i));
			Addedge (0, son(0, i));
		}
	}
	while (!q.empty()) {
		int now = q.front(); q.pop();
		for (int i = 0; i < 26; i ++) {
			if (!son(now, i))
				son(now, i) = son(fail(now), i);
			else {
				fail(son(now, i)) = son(fail(now), i);
				q.emplace (son(now, i));
				Addedge (fail(son(now, i)), son(now, i));
			}
		}
	}
}

void dfs (int from) {
	dfn[from] = ++ind;
	for (int i = head[from]; ~i; i = E[i].nxt) dfs (E[i].to);
	low[from] = ind;
}

void Build (int l, int r, int rt) {
	Sgt[rt].l = l, Sgt[rt].r = r;
	if (l == r) return;
	int mid = (l + r) >> 1;
	Build (l, mid, lson(rt));
	Build (mid + 1, r, rson(rt));
}

inline void pushdown (int rt) {
	if (Sgt[rt].lazy) {
		Sgt[lson(rt)].lazy += Sgt[rt].lazy;
		Sgt[rson(rt)].lazy += Sgt[rt].lazy;
		Sgt[lson(rt)].sum += len(lson(rt)) * Sgt[rt].lazy;
		Sgt[rson(rt)].sum += len(rson(rt)) * Sgt[rt].lazy;
		Sgt[rt].lazy = 0;
	}
}

void Modify (int ql, int qr, int rt, int val) {
	int l = Sgt[rt].l, r = Sgt[rt].r;
	if (ql <= l && qr >= r) {
		Sgt[rt].lazy += val;
		Sgt[rt].sum += len(rt) * val;
		return;
	}
	int mid = (l + r) >> 1;
	pushdown(rt);
	if (ql <= mid)
		Modify (ql, qr, lson(rt), val);
	if (qr > mid)
		Modify (ql, qr, rson(rt), val);
	Sgt[rt].sum = Sgt[lson(rt)].sum + Sgt[rson(rt)].sum;
}

int query (int ql, int qr, int rt) {
	int l = Sgt[rt].l, r = Sgt[rt].r;
	if (ql <= l && qr >= r)
		return Sgt[rt].sum;
	int mid = (l + r) >> 1, res = 0;
	pushdown(rt);
	if (ql <= mid)
		res += query (ql, qr, lson(rt));
	if (qr > mid)
		res += query (ql, qr, rson(rt));
	return res;
}

inline int queryAns (string str) {
	int len = str.length(), now = 0, res = 0;
	for (int i = 1; i < len; i ++) {
		int chVal = str[i] - 'a';
		now = son(now, chVal);
		res += query (dfn[now], dfn[now], 1);
	}
	return res;
}

inline int chgStr (string str) {
	int len = str.length(), res = 0;
	for (int i = 1; i < len; i ++)
		res = res * 10 + str[i] - '0';
	return res;
}

signed main() {
	ios_base::sync_with_stdio (false);
	cin.tie (nullptr), cout.tie (nullptr);
	cin >> N >> K, cnt = ind = idx = 0;
	memset (head, -1, sizeof head);
	for (int i = 1; i <= K; i ++) 
		cin >> Style, InsertString(i);
	GetFailPointer(), dfs(0), Build (1, ind, 1);
	for (int i = 1; i <= K; i ++)
		tag[i] = true, Modify (dfn[tail[i]], low[tail[i]], 1, 1);
	for (int i = 1; i <= N; i ++) {
		cin >> Text;
		if (Text[0] == '+') {
			int strVal = chgStr(Text);
//			cout << strVal << "\n";
			if (!tag[strVal])
				tag[strVal] = true, Modify (dfn[tail[strVal]], low[tail[strVal]], 1, 1);
		} else if (Text[0] == '-') {
			int strVal = chgStr(Text);
//			cout << strVal << "\n";
			if (tag[strVal])
				tag[strVal] = false, Modify (dfn[tail[strVal]], low[tail[strVal]], 1, -1);
		} else {
			cout << queryAns(Text) << "\n";
		}
	}
	return 0;
}
```

---

## 作者：hzoi_Shadow (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF163E)

# 前置知识

[AC 自动机](https://oi-wiki.org//string/ac-automaton/) | [树状数组](https://oi-wiki.org/ds/fenwick/) 

# 解法

一次性将所有模式串加入 AC 自动机，然后处理加入和删除，考虑单次操作对答案的贡献。

因为模式串 $T$ 在文本串 $S$ 中出现的次数之和等价于 $T$ 在 $S$ 的所有前缀中作为后缀出现的次数之和。这就很和 $fail$ 树上跳到根节点的性质相符。

加入/删除分别对应末尾标记 $ed$ 的 $+1/-1$。	

单点修改加一个点到根节点这条链的区间查询可以转化为子树修改加单点查询。

转成 DFS 序后树状数组维护即可。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
#define ull unsigned long long
#define sort stable_sort 
#define endl '\n'
struct node
{
	int nxt,to;
}e[1000010];
int head[1000010],dfn[1000010],out[1000010],del[1000010],tot=0,cnt=0;
char s[1000010];
void add(int u,int v)
{
	cnt++;
	e[cnt].nxt=head[u];
	e[cnt].to=v;
	head[u]=cnt;
}
struct BIT
{
	int c[1000010];
	int lowbit(int x)
	{
		return x&(-x);
	}
	void add(int n,int x,int val)
	{
		for(int i=x;i<=n;i+=lowbit(i))
		{
			c[i]+=val;
		}
	}
	void update(int n,int l,int r,int val)
	{
		add(n,l,val);
		add(n,r+1,-val);
	}
	int getsum(int x)
	{
		int ans=0;
		for(int i=x;i>=1;i-=lowbit(i))
		{
			ans+=c[i];
		}
		return ans;
	}
}B;
struct ACM
{
	int ed[1000010],fail[1000010],rt_sum;
	struct trie
	{
		int ch[27];
	}tree[1000010];
	int val(char x)
	{
		return x-'a'+1;
	}
	void insert(char s[],int len,int id)
	{
		int x=0;
		for(int i=1;i<=len;i++)
		{
			if(tree[x].ch[val(s[i])]==0)
			{
				rt_sum++;
				tree[x].ch[val(s[i])]=rt_sum;
			}
			x=tree[x].ch[val(s[i])];
		}
		ed[id]=x;
	}
	void build()
	{
		queue<int>q;
		for(int i=1;i<=26;i++)
		{
			if(tree[0].ch[i]!=0)
			{
				fail[tree[0].ch[i]]=0;
				add(0,tree[0].ch[i]);
				q.push(tree[0].ch[i]);
			}
		}
		while(q.empty()==0)
		{
			int x=q.front();
			q.pop();
			for(int i=1;i<=26;i++)
			{
				if(tree[x].ch[i]==0)
				{
					tree[x].ch[i]=tree[fail[x]].ch[i];
				}
				else
				{
					fail[tree[x].ch[i]]=tree[fail[x]].ch[i];
					add(fail[tree[x].ch[i]],tree[x].ch[i]);
					q.push(tree[x].ch[i]);
				}
			}
		}	
	}
	int query(char s[],int len)
	{
		int x=0,ans=0;
		for(int i=1;i<=len;i++)
		{
			x=tree[x].ch[val(s[i])];
			ans+=B.getsum(dfn[x]);
		}
		return ans;
	}
}A;
void dfs(int x)
{
	tot++;
	dfn[x]=tot;
	for(int i=head[x];i!=0;i=e[i].nxt)
	{
		dfs(e[i].to);
	}
	out[x]=tot;
}
int main()
{
	int q,n,x,i;
	char pd;
	cin>>q>>n;
	for(i=1;i<=n;i++)
	{
		cin>>(s+1);
		A.insert(s,strlen(s+1),i);
	}
	A.build();
	dfs(0);
	for(i=1;i<=n;i++)
	{
		B.update(tot,dfn[A.ed[i]],out[A.ed[i]],1);
	}
	for(i=1;i<=q;i++)
	{
		cin>>pd;
		if(pd=='?')
		{
			cin>>(s+1);
			cout<<A.query(s,strlen(s+1))<<endl;
		}
		if(pd=='+')
		{
			cin>>x;
			if(del[x]==1)
			{
				del[x]=0;
				B.update(tot,dfn[A.ed[x]],out[A.ed[x]],1);
			}
		}
		if(pd=='-')
		{
			cin>>x;
			if(del[x]==0)
			{
				del[x]=1;
				B.update(tot,dfn[A.ed[x]],out[A.ed[x]],-1);
			}
		}
	}
	return 0;
}
```

---

## 作者：hehelego (赞：1)

也许可以二进制分组?或者对时间分块之类的东西,直接维护$S$中字符串构造的AC自动机,或许搞个sam on trie也行?...没有仔细想...搞个传统做法吧.  

---

考虑AC自动机匹配过程,我们首先把AC自动机这个NFA转化成一个DFA,也就是去掉fail这个状态转移...具体做法很简单,BFS的时候就可以做好了,对于不存在的转移$tr(q,c)$,在$q$处加一个$c$,应当转移到$tr(fail(q),c)$,按照fail树上的深度排序进行转移的话fail(q)的所有转移都已经计算好了,所以可以$O(1)$计算出这个$tr$...具体看程序吧,感觉挺正常的.  

从$qs$(也许程序里面叫root)代表空串的状态开始,文本串下一个字符为$c$则转移到$tr(q,c)$,对于任意$tr(qs,S)=q$的字符串$S$,显然$fail(q),fail(fail(q))\dots fail^k(q),qs$都在$S$中出现了.于是我们构造自动机的时候记录一下根链上出现的接受状态数量,转移后加上这个东西就可以做匹配了.  

大概看一下贡献的形式,一个接受状态对子走到树内的文本串有贡献,而文本串的一个前缀的贡献是根链上所有接受状态数量.(对说得就是一回事...)


---

好了回顾完了,回到本题,考虑文本串$T$匹配过程中到达的状态依次是$(q_0=qs,q_1,q_2\dots q_r)$,$ans=\sum_{i=1}^m([i\in S]\sum_{i=0}^r [q_i\in subtree(tr(qs,T_i)])$
其中$T$是模式串,而$S$是当前有效的模式串.   


我们可以标记所有有效模式串在自动机上对应的状态,匹配文本串,统计到达状态$q$时根链上有效模式串对应状态数量...于是问题转化为树上单点加,根链和,可以HLD+SGT写出美好的$O(nlog^2n)$(我也不知道n在这个题里面是啥233).  

不过这个人物太特殊了,用HLD这种通用工具并不能达到最优,下面我们扯一扯如何优化到$O(nlogn)$

---



答案形式大概是$\sum_u [l_u\leq l_x\leq r_u](dep_x-dep_u+1)$的形式,其中$u$是枚举有效模式串对应状态在fail树上的位置.x是当前模式串前缀走到了自动机上的状态$x$.(画个图就知道了qwq...)  

我们进行拆分,拆成$\sum -dep_u$与$\sum dep_x+1$两部分...我们呢先考虑后面那部分怎么算,可以这么想,$l_u\leq x$,$x\leq r_u$,我们走到$l$的时候加上$u$的贡献,走到$r_u+1$的时候扣掉$u$的贡献即可,于是问题变成了单点加,前缀和,用BIT可以解决它.  

前一部分呢?是一样的呢.btw,这个想法似乎可以用于解决BIT维护区间加,区间和.  


----


整理一下思路,建所有模式串的AC自动机,转化成DFA方便匹配.  
维护当前有效的模式串集合,匹配文本串.  贡献统计在$x\geq l_u$时加上$u$的贡献,$x\gt r_u$时扣掉贡献就可以正确统计,于是贡献计算是单点加,前缀和BIT维护它.得到优秀的1log做法.  



---


```cpp
#include <bits/stdc++.h>
const int N=100000+10;
const int M=1000000+10;
struct T{
	int tr[26],fail;
	T(){ fail=0;
		for(int i=0;i<26;i++) tr[i]=0;
	}
}t[M];
int n,m,cnt,root,at[N],in[N];
int ins(const char *s){
	int p=root,j=0;
	for(int i=0;s[i];i++){ j=s[i]-'a';
		if(t[p].tr[j]==0) t[p].tr[j]=++cnt;
		p=t[p].tr[j];
	}
 	return p;
}
std::vector<int> son[M];
int l[M],r[M],idx,dep[M];
void dfs(int u){
	l[u]=++idx;
	for(int v:son[u]) dfs(v);
	r[u]=idx;
}
typedef long long Int;
Int bit[2][M];
inline int lowbit(int x){ return x&(-x); }
void add(int k,int x,int y){ while(x<=idx){ bit[k][x]+=y; x+=lowbit(x); } }
Int qry(int k,int x){ Int s=0; while(x){ s+=bit[k][x]; x^=lowbit(x); } return s; }
inline void ins(int x){
// 这就是上面说的搞成左端点加入,右端点扣除.
	add(0,l[x],-dep[x]); add(0,r[x]+1,dep[x]);
	add(1,l[x],1); add(1,r[x]+1,-1);
}
inline void del(int x){
	add(0,l[x],dep[x]); add(0,r[x]+1,-dep[x]);
	add(1,l[x],-1); add(1,r[x]+1,1);
}
inline Int get(int x){ return qry(0,l[x])+(dep[x]+1)*qry(1,l[x]); }


int q[M],ql,qr;
void init(){ ql=qr=0;
	for(int i=0;i<26;i++){
		int &v=t[root].tr[i];
		if(v){ t[v].fail=root; q[qr++]=v; }
		else v=root;
	}
	while(ql<qr){
		int u=q[ql++];
		for(int i=0;i<26;i++){
			int &v=t[u].tr[i];
			if(v){
				t[v].fail=t[t[u].fail].tr[i];
				q[qr++]=v;
			}else v=t[t[u].fail].tr[i];
            // 这个else就是把NFA转化成DFA的关键了qwq,
            // 在u处,没有i的转移,会失配走fail,
            // 我们的处理可以这么理解,提前走了fail树找到了可以继续匹配的状态.
		}
	}
	for(int i=1;i<=cnt;i++) son[t[i].fail].push_back(i);
	dfs(root);
	for(int i=1;i<=cnt;i++){ son[i].clear(); son[i].shrink_to_fit(); }
}

char str[M];
int main(){
	scanf("%d%d",&n,&m); root=++cnt;
	for(int i=1;i<=m;i++){
		scanf("%s",str); at[i]=ins(str);
	} init(); idx++;

	for(int i=1;i<=m;i++){ int j=at[i]; in[i]=1; ins(j); }

	Int ans=0; while(n--){
		char op=getchar();
		while(op!='?'&&op!='-'&&op!='+') op=getchar();
		if(op=='?'){
			scanf("%s",str); ans=0;
            // 就暴力匹配...
			for(int i=0,q=root;str[i];i++) ans+=get(q=t[q].tr[str[i]-'a']);
			printf("%.0f\n",double(ans));
		}
		if(op=='+'){
			int id=0; scanf("%d",&id);
			if(in[id]==0){ in[id]=1; ins(at[id]); }
		}
		if(op=='-'){
			int id=0; scanf("%d",&id);
			if(in[id]==1){ in[id]=0; del(at[id]); }
		}
	}
	return 0;
}

```









---

## 作者：Engulf (赞：1)

对所有 $s$ 建出 AC 自动机。对于一个出现的 $s$，在它的终止节点处权值加一，根据 fail 指针的定义，它在 fail 树上的子树都出现了 $s$，所以添加和删除操作就转化为了 fail 树上的子树加。

求答案也是一样，把待求串扔进 AC 自动机，累加每个结点的值，这就是 fail 树上的单点查询。

子树加，单点查询可以用树状数组来维护。

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

const int N = 1e6 + 5;

int tr[N][26], idx, fail[N];

vector<int> g[N];

unordered_map<string, int> ed;

void insert(string s) {
    int p = 0;
    for (auto c: s) {
        if (!tr[p][c - 'a']) tr[p][c - 'a'] = ++idx;
        p = tr[p][c - 'a'];
    }
    ed[s] = p;
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

int dfn[N], siz[N], tim;

void dfs(int u) {
    dfn[u] = ++tim;
    siz[u] = 1;
    for (auto v: g[u])
        dfs(v), siz[u] += siz[v];
}

int bit[N];
void add(int i, int v) {for (; i <= tim; i += i & -i) bit[i] += v;}
int query(int i) {int res = 0; for (; i; i -= i & -i) res += bit[i]; return res;}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int q, n;
    cin >> q >> n;
    vector<string> str(n);
    unordered_map<string, bool> vis;
    for (auto &s: str) {
        cin >> s;
        insert(s);
        vis[s] = 1;
    }
    build();
    dfs(0);
    for (auto s: str) add(dfn[ed[s]], 1), add(dfn[ed[s]] + siz[ed[s]], -1);
    while (q--) {
        char op;
        cin >> op;
        string s;
        cin >> s;
        if (op != '?') {
            stringstream ss;
            ss << s;
            int id;
            ss >> id;
            s = str[id - 1];
        }
        if (op == '+' && !vis[s]) add(dfn[ed[s]], 1), add(dfn[ed[s]] + siz[ed[s]], -1), vis[s] = 1;
        if (op == '-' && vis[s]) add(dfn[ed[s]], -1), add(dfn[ed[s]] + siz[ed[s]], 1), vis[s] = 0;
        if (op == '?') {
            int p = 0;
            ll ans = 0;
            for (auto c: s) p = tr[p][c - 'a'], ans += query(dfn[p]);
            cout << ans << "\n";
        }
    }
    return 0;
}
```

---

## 作者：Mirasycle (赞：0)

很套路的典题。

多模式串考虑建立 ACAM。

考虑如果刻画一个串 $x$（集合中的串）在另一个串 $y$（询问串）中是否出现/出现次数。我们用 $y$ 在自动机上跑匹配，$x$ 在 $y$ 中出现是在 $y$ 中某次到达（匹配过程中经过的节点，该状态为 $y$ 的一个前缀）的状态跳 fail 可以跳到 $x$。也就是 $y$ 中的某个状态在 $x$ 的子树中，如果从最后的匹配来看，该位置也是匹配的末尾点。

于是问题就很简单了，我们反向考虑贡献，对于每个 $x$ 都对其子树 $+1$，这样子我们把 $y$ 一路经过节点的权值累加就是最后的答案了。

考虑从集合中的删减，本质也就是子树的加减动态修改，BIT 维护即可。

时间复杂度 $O(n\log n)$。

---

## 作者：strcmp (赞：0)

ZROI 2024 暑假集训 B 班字符串 T4。

比较基础的 AC 自动机练习题。

不要被它的加入和删除骗到，我们每次只会加入或者删除一个固定集合的字符串，这告诉我们直接对这个集合的字符串建立一个 ACAM。

先不管那个插入和删除。查询 ACAM 中的字符串在给定字符串中出现次数和，是比较经典的问题。具体的对于每个 ACAM 中的字符串的结束结点，它的 fail 子树代表这个字符串前面接了一些奇♀怪的字符，文本串的前缀能进入到它的 fail 子树的话就能存在一个贡献。

因此对于在集合中的字符串，它的 fail 子树整体加一，然后对于文本串，暴力枚举它的前缀，然后查询它前缀代表结点在多少个结点的子树中。

用个树状数组 dfs 序就轻松做到了。

至于那个插入和删除，我们发现插入就让它的 fail 子树整体加一，删除整体减一就做完了。不需要改变 ACAM 的结构。

于是时间复杂度 $\Theta(\sum |s| \log)$，可以通过。

```cpp
// LUOGU_RID: 169793755
#include <bits/stdc++.h>
#define rep(i, a, b) for(int i = a; i <= b; i++)
#define mp make_pair
using namespace std;
typedef long long int ll;
using pii = pair<int, int>;
constexpr int maxn = 1e6 + 10, mod = 1e9 + 7, i3 = 333333336; ll c[maxn];
int t[maxn][26], f[maxn], tot = 0, id[maxn], dfn[maxn], siz[maxn], dct, k; vector<int> g[maxn];
inline void add(int x, int d) { while (x <= dct) c[x] += d, x += x & -x; }
inline ll sum(int x) { ll s = 0; while (x) s += c[x], x -= x & -x; return s; }
inline void ins(char* s, int p) {
	int m = strlen(s + 1), u = 0;
	rep(i, 1, m) {
		if (!t[u][s[i] - 'a']) t[u][s[i] - 'a'] = ++tot;
		u = t[u][s[i] - 'a'];
	}
	id[p] = u;
}
int q[maxn], hd = 1, tl = 0, n, del[maxn]; char s[maxn];
inline void build() {
	rep(i, 0, 25) if (t[0][i]) q[++tl] = t[0][i];
	while (hd <= tl) {
		int u = q[hd++];
		rep(i, 0, 25) {
			int v = t[u][i];
			if (v) f[v] = t[f[u]][i], q[++tl] = v;
			else t[u][i] = t[f[u]][i];
		}
	}
	rep(i, 1, tot) g[f[i]].push_back(i);
}
void dfs(int u) {
	dfn[u] = ++dct; siz[u] = 1;
	for (auto v : g[u]) dfs(v), siz[u] += siz[v];
}
void qry() {
	ll ans = 0; int x = 0, len = strlen(s + 1);
	for (int i = 1; i <= len; i++) x = t[x][s[i] - 'a'], ans += sum(dfn[x]);
	printf("%lld\n", ans);
}
inline void Ad(int l, int r, int x) { add(l, x); add(r + 1, -x); }
int main() {
	scanf("%d%d", &n, &k);
	rep(i, 1, k) scanf("%s", s + 1), ins(s, i); build(); dfs(0);
	rep(i, 1, k) Ad(dfn[id[i]], dfn[id[i]] + siz[id[i]] - 1 , 1);
	for (int i = 1, x; i <= n; i++) {
		scanf("%s", s);
		if (s[0] == '?') qry();
		else {
			int len = strlen(s + 1); int x = 0; 
			for (int j = 1; j <= len; j++) x = x * 10 + s[j] - '0'; x = id[x];
			if (s[0] == '+' && del[x]) del[x] = 0, Ad(dfn[x], dfn[x] + siz[x] - 1, 1);
			else if (s[0] == '-' && !del[x]) del[x] = 1, Ad(dfn[x], dfn[x] + siz[x] - 1, -1);
		}
	}
	return 0;
}
```

---

## 作者：iCostalymh (赞：0)

## 前言

推一下我的[博客](https://www.cnblogs.com/Chronologika/p/17607113.html)先~

一道比较基础的 AC 自动机题（我也是因为这个题才学了 AC 自动机）。这边建议没学过 AC 自动机的先去学一下。我太菜了，没有现成的博客提供给大家（悲）。

校内模拟赛也考到了这个题，不过自己人挺善良的给了不少部分分，我当时还很菜（虽然现在也是），就糊了一个 KMP 骗了 50pts。 不过 CF 上好像卡的挺死的，就不能这么瞎搞了（怕）。

## 简要分析

看到多模式匹配便显然想到了 AC 自动机，这题只不过就是比普通的 AC 自动机板子多了添加和删除操作。观察数据范围可得，我们能增加的复杂度最多不能超过 $\log$ 级别。

我们知道，AC 自动机的所有 fail 边的反向边可构成一棵树（fail 树是一颗外向树），证明也很好理解：因为在所有的 fail 正向边中，所有的点的出度 $\le 1$，所以 fail 反向边就是入度 $\le 1$。

并且对于 fail 树来说，以 $0$ 号节点为根的每一棵子树的字母集大小只有 $1$。如果实在理解不了，就自己多举几个例子手模一下就知道了。

对于添加和删除，我们肯定不能真的添加删除，最先想到的肯定是打标记，对于不会打标记的建议先做一下 [P3796 【模板】AC 自动机（加强版）](https://www.luogu.com.cn/problem/P3796 "P3796 【模板】AC 自动机（加强版）")。

想明白一个问题，当一个字符串出现的时候，那么它的后缀一定出现。那么 fail 树的作用就出现了，想想在建立 fail 数组的时候是从某个字符串的结尾指向其后缀，**那么 fail 树就是从后缀指向某个字符串的结尾**，（我太菜了，需要手模一下才会）发现这东西其实是个区间修改。那么我们设一个数组 $c$，令 $c[i]$ 表示以 $i$ 为后缀的模式串在母串出现的次数，维护的话就先差分一下再用树状数组单点修改即可。正确性显然。

题说完了，就奉上我（自认为）美丽的代码吧~

```cpp
#include <bits/stdc++.h>
using namespace std;

const int maxn(1e6 + 3), maxn2(1e5 + 3);

int n, len, m, opt, a;
char str[maxn];
bool vis[maxn];

namespace AC_AUTOMATON {
    int trie[maxn][26], cnt, ed[maxn], fail[maxn], rnk[maxn2];
    int head[maxn], nxt[maxn], ver[maxn], tot;
    queue<int> q;
    int in[maxn], out[maxn], num;

    class AC_automaton {
    
    public:
        inline void add(int x, int y) {
            ver[++tot] = y, nxt[tot] = head[x], head[x] = tot;
        }

        inline void insert(char* s, int k) {
            int p(0);
            len = strlen(s);
            for (int i = 0; i < len; ++i) {
                if (!trie[p][s[i] - 97]) trie[p][s[i] - 97] = ++cnt;
                p = trie[p][s[i] - 97];
            }
            ++ed[p];
            rnk[k] = p;
        }

        void getFail() {
            fail[0] = 0;
            for (int i = 0; i < 26; ++i) {
                if (trie[0][i]) {
                    q.push(trie[0][i]);
                    fail[trie[0][i]] = 0;
                    add(0, trie[0][i]);
                }
            }

            while (q.size()) {
                int u = q.front(); q.pop();
                for (int i = 0; i < 26; ++i) {
                    if (trie[u][i]) {
                        q.push(trie[u][i]);
                        fail[trie[u][i]] = trie[fail[u]][i];
                        add(fail[trie[u][i]], trie[u][i]);
                    }
                    else trie[u][i] = trie[fail[u]][i];
                }
            }
        }

        void dfs(int x) {
            in[x] = ++num;
            for (int i = head[x]; ~i; i = nxt[i]) {
                dfs(ver[i]);
            }
            out[x] = num;
        }
    } AC;
}

using namespace AC_AUTOMATON;

namespace BINARY_INDEXED_TREE {
    int c[maxn];

    class Binary_Indexed_Tree {
    
    public:
        inline int lowbit(int x) { return x & -x; }

        inline void add(int x, int k) {
            for (; x <= cnt + 1; x += lowbit(x)) { c[x] += k; }
        }

        inline int ask(int x) {
            int res(0);
            for (; x; x -= lowbit(x)) { res += c[x]; }
            return res;
        }

        int query(char* s) {
            int res(0), p(0);
            len = strlen(s);
            for (int i = 1; i < len; ++i) {
                p = trie[p][s[i] - 97];
                res += ask(in[p]);
            }
            return res;
        }
    } BIT;
}

using namespace BINARY_INDEXED_TREE;

int main() {
    memset(head, 0xff, sizeof(head));

    scanf("%d%d", &m, &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%s", str);
        AC.insert(str, i);
    }

    AC.getFail();
    AC.dfs(0);

    for (int i = 1; i <= n; ++i) {
        BIT.add(in[rnk[i]], 1);
        BIT.add(out[rnk[i]] + 1, -1);
    }

    for (int i = 1; i <= m; ++i) {
        scanf("%s", str);
        len = strlen(str);
        a = 0;
        for (int i = 1; i < len; ++i) {
            if (str[0] == '+' || str[0] == '-') a = (a << 1) + (a << 3) + (str[i] & 15); 
        }
        if (str[0] == '?') {
            printf("%d\n", BIT.query(str));
        } else if (str[0] == '+') {
            if (vis[a] == true) {
                vis[a] = false;
                BIT.add(in[rnk[a]], 1);
                BIT.add(out[rnk[a]] + 1, -1);
            }
        } else {
            if (vis[a] == false) {
                vis[a] = true;
                BIT.add(in[rnk[a]], -1);
                BIT.add(out[rnk[a]] + 1, 1);
            }
        }
    }
}
```

---

## 作者：orz_z (赞：0)

好久没写 `AC` 自动机了，来一发套线段树的题解吧。

### 题目大意

给定包含 $k$ 个字符串的集合 $S$，有 $n$ 个操作，操作有三种类型：

* 以 `？` 开头的操作为询问操作，询问当前字符串集S中的每一个字符串匹配询问字符串的次数之和；

* 以 `+` 开头的操作为添加操作，表示将编号为 $i$ 的字符串加入到集合中；

* 以 `-` 开头的操作为删除操作，表示将编号为 $i$ 的字符串从集合中删除。

注意当编号为i的字符串已经在集合中时，允许存在添加编号为 $i$ 的字符串，删除亦然。

### 解题思路

读题，发现题目是要求多模式串匹配数总和。

需要用到一个结论：这个模式串一定会被这个模式串末尾位置在 `fail` 树上的子树代表的字符串匹配到。

由于所有字符串都已经给出，那么先建好 `fail` 树，标记上每个串的结尾。

故添加一个字符串，只需要在这个串的结尾在 `fail` 树上的子树标记都加 $1$，删除则减 $1$。

标记用线段树维护即可。

对于询问，将他放在 `fail` 树上跑，并累加标记即可。

具体请看代码。


### CODE

```cpp
#include <bits/stdc++.h>

using namespace std;

inline int read()
{
    int x = 0, f = 1;
    char c = getchar();
    while (c < '0' || c > '9')
    {
        if (c == '-')
            f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9')
    {
        x = x * 10 + c - '0';
        c = getchar();
    }
    return x * f;
}

int n, m;

char str[1000007];

int cnt, id[100007], tr[1000007][26], fail[1000007];

int tot, head[1000007], to[1000007], nxt[1000007];

int cnt_node, L[1000007], R[1000007];

int del[100007];

void add(int u, int v)
{
    to[++tot] = v;
    nxt[tot] = head[u];
    head[u] = tot;
}

void insert(int x)
{
    scanf("%s", str);
    int len = strlen(str);
    int p = 0;
    for (int i = 0; i < len; ++i)
    {
        int v = str[i] - 'a';
        if (!tr[p][v])
            tr[p][v] = ++cnt;
        p = tr[p][v];
    }
    id[x] = p;
}

void get_fail()
{
    queue<int> q;
    for (int i = 0; i < 26; ++i)
        if (tr[0][i])
        {
            fail[tr[0][i]] = 0;
            q.push(tr[0][i]);
        }
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = 0; i < 26; ++i)
        {
            if (tr[u][i])
            {
                fail[tr[u][i]] = tr[fail[u]][i];
                q.push(tr[u][i]);
            }
            else
            {
                tr[u][i] = tr[fail[u]][i];
            }
        }
    }
    for (int i = 1; i <= cnt; ++i)
        add(fail[i], i);
}

void dfs(int u, int fa)
{
    L[u] = ++cnt_node;
    for (int i = head[u]; i; i = nxt[i])
    {
        int v = to[i];
        if (v == fa)
            continue;
        dfs(v, u);
    }
    R[u] = cnt_node;
}

int t[1000007 << 2], lazy[1000007 << 2];

void push_down(int o, int l, int r)
{
    if (lazy[o])
    {
        int mid = (l + r) >> 1;
        t[o << 1] += (mid - l + 1) * lazy[o];
        t[o << 1 | 1] += (r - mid) * lazy[o];
        lazy[o << 1] += lazy[o];
        lazy[o << 1 | 1] += lazy[o];
        lazy[o] = 0;
    }
}

void update(int o, int l, int r, int L, int R, int k)
{
    if (L <= l && r <= R)
    {
        t[o] += (r - l + 1) * k;
        lazy[o] += k;
        return;
    }
    int mid = (l + r) >> 1;
    push_down(o, l, r);
    if (L <= mid)
        update(o << 1, l, mid, L, R, k);
    if (R > mid)
        update(o << 1 | 1, mid + 1, r, L, R, k);
    t[o] = t[o << 1] + t[o << 1 | 1];
}

int query(int o, int l, int r, int L, int R)
{
    if (L <= l && r <= R)
    {
        return t[o];
    }
    int mid = (l + r) >> 1;
    int res = 0;
    push_down(o, l, r);
    if (L <= mid)
        res += query(o << 1, l, mid, L, R);
    if (R > mid)
        res += query(o << 1 | 1, mid + 1, r, L, R);
    t[o] = t[o << 1] + t[o << 1 | 1];
    return res;
}

int Query()
{
    int x = 0, i = 0, ans = 0;
    for (int i = 1, len = strlen(str); i < len; ++i)
        x = tr[x][str[i] - 'a'], ans += query(1, 1, cnt, 1, L[id[x]]);
    return ans;
}

signed main()
{
    m = read(), n = read();
    for (int i = 1; i <= n; ++i)
        insert(i);
    get_fail();
    dfs(0, -1);
    cnt++;
    for (int i = 1; i <= n; ++i)
        update(1, 1, cnt, L[id[i]], R[id[i]], 1);
    while (m--)
    {
        char opt;
        int x = 0;
        cin >> opt;
        if (opt == '?')
        {
            int ans = 0;
            scanf("%s", str);
            // printf("%s\n", str);
            for (int i = 0, len = strlen(str); i < len; ++i)
            {
                x = tr[x][str[i] - 'a'];
                if (x)
                {
                    ans += query(1, 1, cnt, L[x], L[x]);
                }
            }
            printf("%d\n", ans);
            continue;
        }
        if (opt == '-')
        {
            cin >> x;
            if (!del[x])
                del[x] = 1, update(1, 1, cnt, L[id[x]], R[id[x]], -1);
        }
        else
        {
            cin >> x;
            if (del[x])
                del[x] = 0, update(1, 1, cnt, L[id[x]], R[id[x]], 1);
        }
    }
}
```



---

## 作者：xfrvq (赞：0)

[$\texttt{CF163E e-Government}$](https://www.luogu.com.cn/problem/CF163E)

[$\texttt{Read in my CnBlogs}$](https://www.cnblogs.com/zeno6174/p/solution-cf163e.html)

## 分析

读题，发现题目是要求多模式串匹配数总和。但是还有附加条件：一部分串的贡献是不算进去的。

做一做 [AC 自动机二次加强版](https://www.luogu.com.cn/problem/P5357)，里面也是多模式串匹配，但是由于时限很短，需要用到一个结论：**一个模式串的答案等于这个串末尾的位置用 $\textit{\textbf{fail}}$ 连边后 $\textit{\textbf{p}}$ 的子树 $\textit{\textbf{siz}}$ 和**。

那么我们就有了一个想法：事先 $\texttt{build } fail$，算出子树 $siz$，拿到文本串就直接一位一位遍历计算当前位置的答案。

## 实现

现在的问题：

+ 子树修改
+ 单点查询

考虑计算 $dfn$ 序，把子树表示为一段区间。

+ $l$：搜到这个点时的 $dfn$，
+ $r$：离开这个点时的 $dfn+1$。

那么 $i$ 的子树就应该是左闭右开区间 $[l_i,r_i)$。

那么不难想到套个树状数组处理区间修改单点查询。

注意 $dfn$ 的计算需要用 $fail_i\to i$ 连边就好了。

## Code

```cpp
#include<stdio.h>
#include<string.h>
#include<vector>
#include<queue>

inline int read(){
    register int x = 0;
    register char c = getchar();
    for(;c < '0' || c > '9';c = getchar());
    for(;c >= '0' && c <= '9';c = getchar())
        x = x * 10 + (c ^ '0');
    return x;
}
#define rint register int

const int maxn = 1e5 + 1;
const int maxm = 1e6 + 1;

namespace AC{
	int C[maxm][26],E[maxn],cnt = 0;
	int fail[maxm];
	std::queue<int> q;
	std::vector<int> G[maxm];
	void insert(char *s,rint x){
		rint p = 0,l = strlen(s);
		for(rint i = 0;i < l;++i){
			rint j = s[i] - 'a';
			if(!C[p][j]) C[p][j] = ++cnt;
			p = C[p][j];
		}
		E[x] = p;
	}
	void build(){
		for(rint i = 0;i < 26;++i)
			if(C[0][i]){
				fail[C[0][i]] = 0;
				G[0].push_back(C[0][i]);
				q.push(C[0][i]);
			}
		while(!q.empty()){
			rint u = q.front();
			q.pop();
			for(rint i = 0;i < 26;++i){
				rint &v = C[u][i],f = C[fail[u]][i];
				if(v) fail[v] = f,G[f].push_back(v),q.push(v);
				else v = f;
			}
		}
	} 
	int l[maxm],r[maxm],dfn = 0;
	void dfs(rint u){
		l[u] = dfn++;
		for(rint v : G[u]) dfs(v);
		r[u] = dfn;
	}
}

namespace BIT{
	int T[maxm];
	void add(rint p,rint x){for(++p;p < maxm;p += (p & -p)) T[p] += x;}
	void upd(rint l,rint r,rint x){add(l,x);add(r,-x);}
	int qry(rint p){rint R = 0;for(++p;p;p -= (p & -p)) R += T[p];return R;}
}

using namespace AC;
using namespace BIT;

char s[maxm],t[maxm];
bool inset[maxn];
signed main(){
	int n,m;
	scanf("%d%d",&m,&n);
	for(int i = 1;i <= n;++i){
		scanf("%s",s);
		insert(s,i);
	}
	build();
	dfs(0);
	for(int i = 1;i <= n;++i){
		inset[i] = true;
		upd(l[E[i]],r[E[i]],1);
	}
	while(m--){
		char opt;
		scanf("\n%c",&opt);
		if(opt == '+'){
			rint x;
			scanf("%d",&x);
			if(inset[x]) continue;
			inset[x] = true;
			upd(l[E[x]],r[E[x]],1);
		} else if(opt == '-'){
			rint x;
			scanf("%d",&x);
			if(!inset[x]) continue;
			inset[x] = false;
			upd(l[E[x]],r[E[x]],-1);
		} else {
			scanf("%s",t);
			rint ln = strlen(t),p = 0,ans = 0;
			for(int i = 0;i < ln;++i){
				rint j = t[i] - 'a';
				p = C[p][j];
				ans += qry(l[p]);
			}
			printf("%d\n",ans);
		}
	}
	return 0;
}
```

---

