# [LSOT-1] Crosspain

## 题目背景

![](https://cdn.luogu.com.cn/upload/image_hosting/xcjot9ob.png)

## 题目描述

令 $S_0=\varnothing$，维护一个数据结构，要求支持以下操作：
- `1 hoc s`，令 $S_i=S_{hoc}\cup\{s\}$，其中 $s$ 是字符串（保证操作前 $s\notin S_{hoc}$） .
- `2 hoc s`，令 $S_i=S_{hoc}$，并查询 $S_i$ 中的所有字符串在给出的字符串 $s$ 中出现的次数之和 .

## 说明/提示

### 样例解释

第三行中，询问版本 $0$ 中的串在 `abc` 中出现几次，因为版本 $0$ 为空，所以出现 $0$ 次 .

第五行中，询问版本 $3$ 中的串在 `defg` 中出现几次，因为版本 $3$ 有字符串 `def`，所以出现 $1$ 次 .

第六行中，询问版本 $1$ 中的串在 `abcd` 中出现几次，因为版本 $1$ 有字符串 `abc`，所以出现 $1$ 次 .

### 数据范围及约定

**「本题采用捆绑测试」**

- $\texttt{Subtask 1(10 pts)：} \displaystyle \sum|s_i|\le 1000$；
- $\texttt{Subtask 2(20 pts)：}$所有添加的字符串长度相同；
- $\texttt{Subtask 3(20 pts)：}$所有添加的字符串只包含一种字符；
- $\texttt{Subtask 4(20 pts)：}q\le 10^3$；
- $\texttt{Subtask 5(30 pts)：}$无特殊限制。

对于全部数据，$1\le q\le  5\times10^5$，$\displaystyle 1\le \sum_i|s_i|\le 10^6$ . 所有字符串仅含小写字母 .

## 样例 #1

### 输入

```
5
1 0 abc
2 0 abc
1 2 def
2 3 defg
2 1 abcd```

### 输出

```
0
1
1```

# 题解

## 作者：enucai (赞：9)

## Preface


**做法0**：我不会数据结构！

**期望得分**：100。

真的想骂骂这个数据啊。

## Analysis

乱搞选手，复杂度不正确，可惜出题人没有卡。

**算法**：字符串 hash。

首先想用一个容器记录一下每次询问后的字符串集。每个字符串记录其长度与 hash 值。

对于操作 1，直接计算字符串 $s$ 的 hash 值，并将其加入容器。

对于操作 2，则直接遍历容器中的元素，并枚举 $s$ 的起始位置，用字符串 hash 的前缀和快速算出这一个子串的 hash 值。若相等，则答案 $+1$。

注意容器的选择，应用 multiset 而不是 set。但是直接用 set 会 MLE，因此选择在使用 set 的同时记录一下这种串的个数即可。

最坏时间复杂度 $O(q^2)$，莫名其妙就过了。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define For(i,j,k) for(int i=(j);i<=(k);i++)
#define Rof(i,j,k) for(int i=(j);i>=(k);i--)
#define mkp make_pair
#define fi first
#define se second
#define IOS ios::sync_with_stdio(false),cin.tie(0)
#define ull unsigned long long
#define int long long
const ull B=13331;
set<pair<pair<ull,int>,int>> S[500010];
ull sum[1000010],mi[1000010];
int q;
char s[1000010];
signed main(){IOS;
	mi[0]=1;
	For(i,1,1000000) mi[i]=mi[i-1]*B;
	cin>>q; S[0].clear();
	For(_,1,q){
		int op,__; cin>>op>>__>>(s+1);
		int m=strlen(s+1);
		S[_]=S[__];
		if(op==1){
			ull now=0ull;
			For(i,1,m) now=now*B+(ull)(s[i]-'a');
			auto tmp=S[_].lower_bound(mkp(mkp(now,m),0));
			if(tmp->fi==mkp(now,m)){
				int cnt=tmp->se;
				S[_].erase(tmp),S[_].emplace(mkp(now,m),cnt+1);
			}else{
				S[_].emplace(mkp(now,m),1);
			}
		}else{
			sum[0]=0ull;
			For(i,1,m) sum[i]=sum[i-1]*B+(ull)(s[i]-'a');
			int res=0;
			for(auto[hl,cnt]:S[_]){
				For(i,1,m-hl.se+1) if(sum[i+hl.se-1]-sum[i-1]*mi[hl.se]==hl.fi) res+=cnt;
			}
			cout<<res<<"\n";
		}
	}
}
```

---

## 作者：Little09 (赞：5)

发现要支持可持久化。

众所周知，没有强制在线的可持久化等于没有可持久化。所以我们考虑离线，询问形成了一个树形结构，我们只要遍历这棵树，支持加入字符串、删除字符串、查询即可。

然后你会发现直接把 AC 自动机建出来就好了。具体地，先把所有要加入的串插到 trie 里去然后建 ACAM，每次加入、删除字符串等价于单点加、减；查询的时候在 ACAM 上走，每次到一个节点把它在 fail 树上到根的权值加一下。

这样你可以树剖。当然，它显然可以转化为子树加、减，单点查值。这样求一下 dfn，用树状数组就行了。

我这样写空间有点卡，找了一下似乎是 vector 开销比较大。

```cpp
// Author: Little09
// Problem: P8451 [LSOT-1] Crosspain
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P8451
// Memory Limit: 192 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
using namespace std;
#define lowbit(x) (x&(-x))
const int N=1e6+5,M=5e5+5;
int q;
char a[N];
int fa[M],b[M],ans[M];
vector<char>s[M];
vector<int>t[M];
namespace AC
{
	int tr[N][26],tot=0;
	int fail[N];
	vector<int>g[N];
	void insert(int id)
	{
		int u=0;
		for (char i:s[id])
		{
			if (!tr[u][i-'a']) tr[u][i-'a']=++tot;
			u=tr[u][i-'a'];
		}
	}
	queue<int>q;
	int dfn[N],cnt,siz[N];
	void dfs(int x)
	{
		dfn[x]=++cnt,siz[x]=1;
		for (int i:g[x])
		{
			dfs(i);
			siz[x]+=siz[i];
		}
	}
	int tree[N];
	inline void add(int x,int k)
	{
		for (;x<=cnt;x+=lowbit(x)) tree[x]+=k;
	}
	inline void update(int id,int k)
	{
		int u=0;
		for (char i:s[id]) u=tr[u][i-'a'];
		add(dfn[u],k);
		add(dfn[u]+siz[u],-k);
	}
	inline int ask(int id)
	{
		int u=0,ans=0;
		for (char i:s[id]) 
		{
			u=tr[u][i-'a'];
			int x=dfn[u];
			for (;x;x-=lowbit(x)) ans+=tree[x];
		}
		return ans;
	}
	void build()
	{
		for (int i=0;i<26;i++)
		{
			if (tr[0][i]) q.push(tr[0][i]);
		}
		while (!q.empty())
		{
			int u=q.front();
			q.pop();
			for (int i=0;i<26;i++)
			{
				if (tr[u][i])
				{
					fail[tr[u][i]]=tr[fail[u]][i];
					q.push(tr[u][i]);
				}
				else tr[u][i]=tr[fail[u]][i];
			}
		}
		for (int i=1;i<=tot;i++) g[fail[i]].push_back(i);
		dfs(0);
	}
}
inline int read()
{
    int F=1,ANS=0;
	char C=getchar();
    while (C<'0'||C>'9')
	{
		if (C=='-') F=-1;
		C=getchar();
	}
    while (C>='0'&&C<='9')
	{
		ANS=ANS*10+C-'0';
		C=getchar();
	}
    return F*ANS;
}

void dfs(int x)
{
	if (b[x]==1) AC::update(x,1);
	if (b[x]==2) ans[x]=AC::ask(x);
	for (int i:t[x]) dfs(i);
	if (b[x]==1) AC::update(x,-1);
}

int main()
{
	q=read();
	for (int i=1;i<=q;i++)
	{
		b[i]=read(),fa[i]=read();
		t[fa[i]].push_back(i);
		scanf("%s",a);
		int l=strlen(a);
		for (int j=0;j<l;j++) s[i].push_back(a[j]);
		if (b[i]==1) AC::insert(i);
	}
	AC::build();
	dfs(0);
	for (int i=1;i<=q;i++)
	{
		if (b[i]==2) printf("%d\n",ans[i]);
	}
	return 0;
}

```


---

## 作者：NY2025 (赞：3)

## $\text{Task}$

题目链接：[[LSOT-1] Crosspain](https://www.luogu.com.cn/problem/P8451)。

实现数据结构：

1. 维护一个带有版本回退与新增元素操作的字符串集合。
2. 查询某版本字符串集合中的元素在给定字符串中出现的总次数。

## $\text{Solution}$

题目的询问明显是 AC 自动机上查询，但发现有版本回退操作，可持久化 AC 自动机是不现实的。但是考虑到没有强制在线，可以通过**操作树**将回退操作转换为撤销操作。

此时只需要在对操作树进行深度优先搜索时加入或删除字符串即可。

因此先将所有操作 1 对应的字符串插入 ACAM，每次加入/删除字符串显然就是在该字符串对应的 fail 树节点位置进行单点加减操作，每次查询时在 AC 自动机上走到一个节点时，将 fail 祖先链上的所有点权求和加入答案。

单点加链查询，可以等价转换为子树加单点查询，因此树状数组维护即可。

## $\text{Code}$

```c++
#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e6+5;
constexpr int M = 5e5+5;
#define lowbit(x) ((x)&(-x))

struct Aho_Corasick {
	struct Trie {
		int son[26];
		void init() {
			memset(son, 0, sizeof son);
		}
	} trie[N];
	int fail[N], tot;
	queue<int> q;
	vector<int> e[N];
	
	int insert(string& s) {
		int u = 0, len = s.size();
		for (int i = 0; i < len; i++) {
			int& son = trie[u].son[s[i]-'a'];
			if (!son) trie[son = ++tot].init();
			u = son;
		}
		return u;
	}
	
	int dfn[N], out[N], timer;
	void dfs(int u) {
		dfn[u] = ++timer;
		for (auto v : e[u]) dfs(v);
		out[u] = timer;
	}
	
	void build() {
		for (int i = 0; i < 26; i++) {
			if (trie[0].son[i]) q.push(trie[0].son[i]);
		}
		while (!q.empty()) {
			int u = q.front();
			q.pop();
			for (int i = 0; i < 26; i++) {
				if (trie[u].son[i]) {
					fail[trie[u].son[i]] = trie[fail[u]].son[i];
					q.push(trie[u].son[i]);
				} else {
					trie[u].son[i] = trie[fail[u]].son[i];
				}
			}
		}
		for (int i = 1; i <= tot; i++) {
			e[fail[i]].emplace_back(i);
		}
		dfs(0);
	}
	
	int tree[N];
	void update(int x, int v) {
		while (x <= timer) {
			tree[x] += v;
			x += lowbit(x);
		}
	}
	int query(int x) {
		int rst = 0;
		while (x) {
			rst += tree[x];
			x -= lowbit(x);
		}
		return rst;
	}
	
	int getans(string& s) {
		int u = 0, rst = 0, len = s.size();
		for (int i = 0; i < len; i++) {
			u = trie[u].son[s[i]-'a'];
			rst += query(dfn[u]);
		}
		return rst;
	}
	
} acam;

int n, opt[M], rst[M], pos[M];
string s[M];
vector<int> e[M];

void dfs(int u) {
	if (opt[u] == 1) {
		acam.update(acam.dfn[pos[u]], 1);
		acam.update(acam.out[pos[u]]+1, -1);
	}
	if (opt[u] == 2) {
		rst[u] = acam.getans(s[u]);
	}
	for (auto v : e[u]) dfs(v);
	if (opt[u] == 1) {
		acam.update(acam.dfn[pos[u]], -1);
		acam.update(acam.out[pos[u]]+1, 1);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin >> n;
	for (int i = 1, x; i <= n; i++) {
		cin >> opt[i] >> x >> s[i];
		e[x].emplace_back(i);
		if (opt[i] == 1) {
			pos[i] = acam.insert(s[i]);
		}
	}
	acam.build();
	dfs(0);
	for (int i = 1; i <= n; i++) {
		if (opt[i] == 2) printf("%d\n", rst[i]);
	}
	
	return 0;
} 
```

---

## 作者：Hoks (赞：2)

## 前言
比较好玩的题了，只不过有个点有点烦。

广告：[串串博客](https://www.luogu.com.cn/article/dv6dig1o)。
## 思路分析
不难发现题面是想让我们实现可持久化 ACAM。

但是就他这个数据范围，正常的 ACAM 空间都要炸飞了，更别说可持久化。

不难发现题面里没写**强制在线**，而知周所众的是：
> **没有强制在线的可持久化不是可持久化。**

考虑离线怎么做。

首先肯定是要对所有串建出 ACAM，求出 fail 树。

但是题目这个操作是挂在另一个操作下的，貌似不太好做？

这不就是树形结构了吗。

考虑对操作造出一颗树，那么题意就变成了如何维护加字符串，删字符串，查询出现次数。

~~其实如果只有这一部分的话是可以在线做的。~~

考虑加字符串即为 fail 树上的子树加，删与其对应即为加负数，查询即为单点查询权值。

然后就愉快的做完了？

**当心空间问题！**

尤其是喜欢用 `string` 的，注意不要采用 `s=" "+s` 这种语句。

因为其内部实现为复制一遍再加，会导致内存爆炸。

换 `vector<char>` 就过了。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e6+10,INF=0x3f3f3f3f3f3f3f3f,mod=1e9+7;
int n,m,cnt,a[N/2],fa[N/2],len[N/2],dfn[N],ed[N],ans[N/2];char t[N];
vector<int>e[N],g[N/2];vector<char>s[N/2];
struct ACAM
{
	int t[N][26],nxt[N];int tot=0;int c[N],n;
	inline void mdf(int x,int v){for(;x<=n;x+=x&-x) c[x]+=v;}
    inline int query(int x){int res=0;for(;x;x-=x&-x) res+=c[x];return res;}
    inline void mdf(int l,int r,int v){mdf(l,v),mdf(r+1,-v);}
	inline void insert(char s[],int n)
	{
		int u=0;
		for(int i=1;i<=n;i++){if(!t[u][s[i]-'a']) t[u][s[i]-'a']=++tot;u=t[u][s[i]-'a'];}
	}
	inline void dfs(int u){dfn[u]=++cnt;for(auto v:e[u]) dfs(v);ed[u]=cnt;}
	inline void modify(int x,int v)
	{
		int u=0;
		for(int i=1;i<=len[x];i++) u=t[u][s[x][i]-'a'];
		mdf(dfn[u],v);mdf(ed[u]+1,-v);
	}
	inline int ask(int x)
	{
		int u=0,ans=0;
		for(int i=1;i<=len[x];i++) u=t[u][s[x][i]-'a'],ans+=query(dfn[u]);
		return ans;
	}
	inline void build()
	{
		queue<int>q;
		for(int i=0;i<26;i++) if(t[0][i]) nxt[t[0][i]]=0,q.push(t[0][i]);
		while(!q.empty())
		{
			int u=q.front();q.pop();e[nxt[u]].emplace_back(u);
			for(int i=0;i<26;i++)
				if(t[u][i]) nxt[t[u][i]]=t[nxt[u]][i],q.push(t[u][i]);
				else t[u][i]=t[nxt[u]][i];
		}dfs(0);n=cnt;
	}
}ac;
namespace Fast_IO
{
    inline int read()
    {
        int x(0),t(1);char fc(getchar());
        while(!isdigit(fc)&&fc!=-1){if(fc=='-') t=-1;fc=getchar();}
        while(isdigit(fc)&&fc!=-1) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
        if(fc==-1) exit(0);return x*t;
    }
    inline void print(int x)
    {
        if(x<0) putchar('-'),x=-x;
        if(x>9) print(x/10);
        putchar(x%10+'0');
    }
    inline bool chk(char c) { return !(c>='a'&&c<='z'); }
    inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1; }
    inline void rd(char s[],int&n)
    {
        s[++n]=getchar();
        while(chk(s[n])) s[n]=getchar();
        while(ck(s[n])) s[++n]=getchar();
        n--;
    }
}
using namespace Fast_IO;
void dfs(int u)
{
	if(a[u]==1) ac.modify(u,1);
	if(a[u]==2) ans[u]=ac.ask(u);
	for(auto v:g[u]) dfs(v);
	if(a[u]==1) ac.modify(u,-1);
}
signed main()
{
	n=read();
	for(int i=1;i<=n;i++)
	{
		a[i]=read(),fa[i]=read();g[fa[i]].emplace_back(i);
		rd(t,len[i]);s[i].emplace_back(' ');for(int j=1;j<=len[i];j++) s[i].emplace_back(t[j]);
		if(a[i]==1) ac.insert(t,len[i]);
	}ac.build();dfs(0);for(int i=1;i<=n;i++) if(a[i]==2) print(ans[i]),puts("");
	return 0;
}
```

---

## 作者：Reunite (赞：2)

简单题。

## 一
---

再怎么绕也离不开多模匹配的中心。稍微考虑一下，发现这个字符串集的生成方式是一个树的形态，考虑建出这个操作树。

操作树的边权为空或者是一个字符串，对应的分别为操作 $2$ 的直接继承和操作 $1$ 的加入一个字符串。操作树上的点也显然地分为没有询问的点和有询问的点了。

那么现在题目就转化为，对于操作树上所有的询问点，查询以其到根的链上所有的边权为模式串，在给定文本串中的出现次数和。正确性是显然的，因为这只是直观化和熟悉化了题意。

按照套路建出 ACAM、fail 树，顺便记录模式串的结尾节点。因为我们都有操作树了，且询问的是从根到当前节点的信息，那直接树上遍历一遍就好了。统计出现次数和是套路的，把匹配转化为 fail 树上的链数点，再转化为子树加，单点求和，不再赘述。

具体地，我们 dfs 这棵树，若该节点是需要从父节点加入一个字符串，那么我们就用树状数组加入新的字符串的贡献。若该节点需要询问，那直接把文本串在 ACAM 上跑一遍，顺便记录贡献即可。离开该节点时再把该节点的贡献撤销即可。

## 二
---

总时间复杂度是 $O(|S||\sum|+(n+q)\log_2|S|)$。

代码十分好写，可以一发过的。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

int n,tot,tm;
char c[500005];
int ed[500005];
int op[500005];
int sz[1000005];
int dfn[1000005];
int ans[500005];
int fail[1000005];
int son[1000005][26];
vector <char> g[500005];
vector <int> e[500005];
vector <int> gg[500005];

inline int insert(){
	int len=strlen(c+1),u=0;
	for(int i=1;i<=len;i++){
		if(!son[u][c[i]-'a']) son[u][c[i]-'a']=++tot;
		u=son[u][c[i]-'a'];
	}
	return u;
}

inline void build(){
	queue <int> q;
	for(int i=0;i<26;i++)
		if(son[0][i]) q.push(son[0][i]);
	while(!q.empty()){
		int u=q.front();
		q.pop();
		for(int i=0;i<26;i++){
			int v=son[u][i];
			if(!v) son[u][i]=son[fail[u]][i];
			else fail[v]=son[fail[u]][i],q.push(v);
		}
	}
	for(int i=1;i<=tot;i++) e[fail[i]].emplace_back(i);

	return ;
}

int t[1000005];
inline void add(int x,int k){while(x<=tm) t[x]+=k,x+=x&-x;return ;}
inline int ask(int x){int s=0;while(x) s+=t[x],x^=x&-x;return s;}

inline void init(int u){dfn[u]=++tm,sz[u]=1;for(int v:e[u]) init(v),sz[u]+=sz[v];}

inline int get(int id){
	int u=0,s=0;
	for(char c:g[id]) u=son[u][c-'a'],s+=ask(dfn[u]);
	return s;
}

inline void dfs(int u){
	if(op[u]==1) add(dfn[ed[u]],1),add(dfn[ed[u]]+sz[ed[u]],-1);
	else ans[u]=get(u);
	for(int v:gg[u]) dfs(v);
	if(op[u]==1) add(dfn[ed[u]],-1),add(dfn[ed[u]]+sz[ed[u]],1);
}

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		int x;
		scanf("%d%d%s",&op[i],&x,c+1);
		gg[x].emplace_back(i);
		if(op[i]==1) ed[i]=insert();
		else{
			int len=strlen(c+1);
			g[i].resize(len);
			for(int j=1;j<=len;j++) g[i][j-1]=c[j];
		}
	}
	build();
	init(0);
	dfs(0);
	for(int i=1;i<=n;i++) 
		if(op[i]==2) printf("%d\n",ans[i]);

	return 0;
}
```

---

## 作者：Defoliation (赞：2)

## 提供一个思路很简单的非正解做法

考虑到每一个 $S_i$ 都是由 $S_{hoc}$ 转移而来，如果真地将每一个字符串集合进行赋值，既浪费空间，又浪费时间。

于是想到对于每一个 $S_i$，使它指向被转移量 $S_{hoc}$，并且对于操作一，将 $s$ 存在一个数组 $extra$ 中。
这样在查询字符串出现次数时就可以沿着指向边进行查询。

字符串查询用 KMP 就行，用 STL 库里的函数是会 TLE 的。


KMP 不太理解的童鞋可以戳 [这里](https://blog.csdn.net/v_JULY_v/article/details/7041827?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522166649446816800182718472%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=166649446816800182718472&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~top_positive~default-1-7041827-null-null.142^v59^pc_new_rank,201^v3^add_ask&utm_term=kmp&spm=1018.2226.3001.4187)
和 [这里](https://www.bilibili.com/video/BV16X4y137qw/?spm_id_from=333.337.search-card.all.click)。

## **Code :**
```cpp
#include<bits/stdc++.h>
#define maxn 500500
#define re register
#define il inline
using namespace std;
int q,opt,m,ans,kmp[maxn],fa[maxn];
string s,extra[maxn];
//KMP算法
//其中 a 是文本串，b 是模式串 
il int KMP(const string& a,const string& b){
	int la=a.size(),lb=b.size(),i=0,j=-1,sum=0;
	if(la<lb) return 0;
	//kmp数组：最长相等前后缀 
	kmp[i]=-1;
	while(i<lb){
		if(j==-1||b[i]==b[j]) kmp[++i]=++j;
		else j=kmp[j];
	}
	j=i=0;
	while(i<la){
		if(j==-1||b[j]==a[i]) ++i,++j;
		else j=kmp[j];
		if(j==lb){
			sum++;
			j=kmp[j-1];
			i--;
		}
	}
	return sum;
}
signed main(){
	ios::sync_with_stdio(false);
	cin>>q;
	for(int i=1;i<=q;i++){
		cin>>opt>>m>>s;
		//建指向边，并存储 s 字符串 
		if(opt==1){
			fa[i]=m;
			extra[i]=s;
		}
		if(opt==2){
			ans=0;
			fa[i]=m;
			int pos=i;
			//不断沿着指向边向上查询 
			while(fa[pos]!=pos){
				pos=fa[pos];
				if(extra[pos]=="") continue;
				ans+=KMP(s,extra[pos]);
			}
			cout<<ans<<'\n';
		}
	}
	return 0;
}
```



------------
KMP 爆踩 AC 自动机。

但蒟蒻因为 KMP 写炸了，导致现在才 AC。



------------
 QWQ


---

## 作者：Fzrcy (赞：1)

在做这道题前先考虑弱化版：

>有一个字符串集合 $S$，$q$ 次询问，每次询问给出一个字符串 $s$ 并求出 $S$ 中所有字符串在给出的字符串 $s$ 中出现的次数之和 。
>
>solution：首先对字符串集合 $S$ 建立 AC 自动机，设 $f_i$ 表示集合 $S$ 中有多少个字符串是 $i$ 代表的字符串的后缀，然后将字符串 $s$ 放在自动机上跑，每到一个节点 $u$，答案累加 $f_u$ 即可。

回到本题，将操作离线，并沿用弱化版的思路，对操作一出现的字符串建立自动机，然后对 $S_i$ 之间的关系建图，并在图中遍历。

询问和弱化版相同，自动机要动态维护 $f_i$ 的值，支持动态加入或删除一个字符串，考虑 $f_i$ 的本质是在 $fail$ 树中节点 $u$ 有多少个祖先是终止节点，用 dfs 序拍扁，线段树维护即可。

```cpp
// qwq
#include <bits/stdc++.h>
using namespace std;
namespace Work{
    constexpr int N=1e6+7;
    struct SegTree{
        int s[N<<2];
        void ins(int k,int l,int r,int x,int y,int v){
            if(l>=x&&r<=y){s[k]+=v;return;} int mid=l+r>>1;
            if(x<=mid)ins(k<<1,l,mid,x,y,v);
            if(y>mid) ins(k<<1|1,mid+1,r,x,y,v);
        }
        int q(int k,int l,int r,int x){
            if(l==r)return s[k];int mid=l+r>>1;
            if(x<=mid)return q(k<<1,l,mid,x)+s[k];
            return q(k<<1|1,mid+1,r,x)+s[k];
        }
    }Tr;
    int ch[N][26],fail[N],cnt=1;
    int d1[N],d2[N],dft;
    vector<int>e[N];
    int ins(char *s){
        int u=1,len=strlen(s+1);
        for(int i=1,c;i<=len;i++,u=ch[u][c])
            !ch[u][c=s[i]-'a']&&(ch[u][c]=++cnt);
        return u;
    }
    void build(){
        for(int i=0;i<26;i++)ch[0][i]=1;
        queue<int> q; q.push(1);
        while(!q.empty()){
            int u=q.front();q.pop();
            e[fail[u]].push_back(u);
            for(int i=0;i<26;i++)
                if(!ch[u][i])ch[u][i]=ch[fail[u]][i];
                else fail[ch[u][i]]=ch[fail[u]][i],q.push(ch[u][i]);
        }
    }
    void dfs1(int u){d1[u]=++dft;for(int v:e[u])dfs1(v);d2[u]=dft;}
    char s[N],r[N*3],*rp[N];
    int qt[N];
    long long ans[N];
    vector<pair<int,int>>edge[N];
    int n,qc;
    void dp(int u){
        if(qt[u]){
            int x=qt[u],len=strlen(rp[x]),now=1;
            long long num=0;
            for(int i=0;i<len;i++){
                now=ch[now][rp[x][i]-'a'];
                num+=Tr.q(1,1,dft,d1[now]);
            }
            ans[x]=num;
        }
        for(auto i:edge[u]){
            int str=i.second;
            if(str)Tr.ins(1,1,dft,d1[str],d2[str],1);
            dp(i.first);
            if(str)Tr.ins(1,1,dft,d1[str],d2[str],-1);
        }
    }
    int Main(){
        int cur=0;
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            int op;scanf("%d",&op);
            if(op==1){
                int pid;scanf("%d %s",&pid,s+1);
                edge[pid].push_back({i,ins(s)});
            }
            else{
                rp[++qc]=r+cur+1;int id;
                scanf("%d %s",&id,rp[qc]);
                edge[id].push_back({i,0});
                qt[i]=qc,cur+=strlen(rp[qc])+2;
            }
        }
        build(),dfs1(1),dp(0);
        for(int i=1;i<=qc;i++)
            printf("%lld\n",ans[i]);
        return 0;
    }
}
int main(){
    Work::Main();
    return 0;
}
```

---

## 作者：lfxxx (赞：1)

显然，题面明摆着让你写一个可持久化 AC 自动机。

但是从空间来说这是不可能的。

想起做 **不强制在线** 的可持久化数据结构的一种方法，建立“时光树”，具体来说，假若版本 $x$ 由版本 $y$ 更改而来，建边 $x \to y$。最后在建出的树上遍历并回答询问。

到此我们只需要一个可以支持加入和撤销的 AC 自动机即可。

考虑维护失配树，具体来说，一个字符串出现的次数等于其所有前缀节点在失配树上的祖先中终止节点数量之和，这是一个点修链查，将其转变为子树修单点查，用树状数组维护即可。

```cpp
#include<bits/stdc++.h>
#define lowbit(x) (x&(-x))
using namespace std;
const int maxn = 1e6+5;
class AC_automaton{
public:
    int son[maxn][26],fail[maxn],rt,tot,dfncnt;
    vector<int> edge[maxn];//fail 树 
    vector<int> fa[maxn];//原树上的祖先 
    int L[maxn],R[maxn],len,now;
    void insert(string &s,int pos){
        len=s.size(),now=rt;
        for(int i=0;i<len;i++){
            if(son[now][s[i]-'a']==0) son[now][s[i]-'a']=++tot;
            now=son[now][s[i]-'a'];
            fa[pos].push_back(now);
        }
    }
    void build(){
        queue<int> q;
        for(int i=0;i<26;i++) if(son[rt][i]) fail[son[rt][i]]=rt,q.push(son[rt][i]);
        while(q.size()>0){
            int u=q.front();
            q.pop();
            for(int i=0;i<26;i++){
                if(son[u][i]){
                    fail[son[u][i]]=son[fail[u]][i];
                    q.push(son[u][i]);
                }
                else son[u][i]=son[fail[u]][i];
            }
        }
        for(int i=1;i<=tot;i++){
        	edge[fail[i]].push_back(i);	
		}
    }
    inline void dfs(int u){
    	L[u]=++dfncnt;
		for(int v:edge[u]){
			if(!L[v]) dfs(v);
		} 
        R[u]=dfncnt;
	}//处理子树信息 
}AC;
int tr[maxn];
inline void add(int x,int v){
    while(x<=AC.dfncnt) tr[x]+=v,x+=lowbit(x);
}
inline int pre(int x){
    int res=0;
    while(x>0) res+=tr[x],x-=lowbit(x);
    return res; 
}
int answer[maxn>>1];
struct Edge{
    int v,nxt;
}e[maxn];
int head[maxn>>1],cnt;
void add_edge(int u,int v){
    e[++cnt].v=v;
    e[cnt].nxt=head[u];
    head[u]=cnt;
}
vector<int> Query[maxn>>1];
bitset< 500005 > opt;
inline void dfs(int u){
    for(int now:Query[u]){
        for(int u:AC.fa[now]){
            answer[now]+=pre(AC.L[u]);
        }
    }
    Query[u].clear();
    for(int i=head[u];i;i=e[i].nxt){
        int now=e[i].v;
        if(opt[now]==1){
            add(AC.L[AC.fa[now].back()],1);
            add(AC.R[AC.fa[now].back()]+1,-1);
        }
        dfs(now);
        if(opt[now]==1){
            add(AC.L[AC.fa[now].back()],-1);
            add(AC.R[AC.fa[now].back()]+1,1);
        }
    }
}
inline int found(int u){
    return tr[u]==u?u:tr[u]=found(tr[u]);
}
int q;
int main(){
    cin>>q;
    for(int i=1;i<=q;i++){
        tr[i]=i;
        int lst,op;
        string s;
        cin>>op>>lst>>s;
        opt[i]=(op==1?1:0);
        lst=found(lst);
        AC.insert(s,i);
        if(opt[i]==1) add_edge(lst,i);
        else Query[lst].push_back(i),tr[i]=lst;
    }
    for(int i=0;i<=q;i++) tr[i]=0;
    AC.build();
    AC.dfs(AC.rt);
    dfs(0);
    for(int i=1;i<=q;i++) if(opt[i]==0) cout<<answer[i]<<'\n';
    return 0;
}
```


---

## 作者：未来姚班zyl (赞：1)

## 题目大意

你需要维护一个集合，满足两个操作：从过去的版本中加入一个字符串，或是查询过去的版本中的集合内的字符串在当前字符串中出现的总次数。

## 题目分析

众所周知，可持久化加上不强制在线等于啥也没有。

所以，我们可以直接按照编号建立操作树，在操作树上进行 dfs。题目变成了支持加入或者删除一个字符串和多模匹配，也就变成了 AC 自动机的板子题。即进行 fail 树上单点加和单点到根路径的查询，树链剖分即可。当然也可以差分转成子树加和单点查询。维护 dfs 序并使用树状数组即可，复杂度均为线性对数。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define L xd[x].l
#define R xd[x].r
#define mid (l+r>>1LL)
#define lc L,l,mid
#define rc R,mid+1,r
#define Root 1,1,n
#define OK l>=Ll&&r<=Rr
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define pb push_back
#define ull unsigned ll
#define e(x) for(int i=h[x],y=to[i];i;i=nxt[i],y=to[i])
#define E(x) for(auto y:p[x])
#define Pi pair<int,int>
#define ui unsigned ll
inline int read(){int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57) s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
inline void pf(ll x){if(x<0) putchar('-'),x=-x;if(x>9)pf(x/10);putchar(x%10+48);}
const int N =5e5+5,M=1e6+5,inf=(1LL<<31)-1;
const ll llf=1e18,mod=1e8+7,bas=131;
const ui base=13331;
using namespace std;
int n=read(),cnt,Id[N];
struct node{
	int son[26],fail,end;
}trie[M];
struct nod{
	int opt;
	string s;
}q[N]; 
vector<int>p[N]; 
inline void insert(string s,int id){
	int len=s.length(),now=0;
	rep(i,0,len-1){
		int k=s[i]-'a';
		if(!trie[now].son[k])trie[now].son[k]=++cnt;
		now=trie[now].son[k];
	}
	Id[id]=now;
}
int dfn[M],h[M],to[M],nxt[M],tot,Time,siz[M];
ll out[N];
inline void add(int a,int b){
	to[++tot]=b,nxt[tot]=h[a],h[a]=tot;
}
inline void dfs(int x){
	dfn[x]=++Time,siz[x]=1;
	e(x)dfs(y),siz[x]+=siz[y];
}
int t[M];
inline void ad(int x,int k){
	while(x<=Time)t[x]+=k,x+=x&-x;
}
inline ll query(int x){
	ll ans=0;
	while(x)ans+=t[x],x-=x&-x; 
	return ans;
}
inline void build(){
	queue<int>q;
	rep(i,0,25)if(trie[0].son[i])q.push(trie[0].son[i]);
	while(!q.empty()){
		int x=q.front();q.pop();
		rep(i,0,25)if(trie[x].son[i])q.push(trie[x].son[i]),trie[trie[x].son[i]].fail=trie[trie[x].fail].son[i];
		else trie[x].son[i]=trie[trie[x].fail].son[i];
	}
	rep(i,1,cnt)add(trie[i].fail,i);
	dfs(0);
}
inline ll solve(string s){
	int len=s.length(),now=0;
	ll ans=0;
	rep(i,0,len-1){
		int k=s[i]-'a';
		now=trie[now].son[k];
		ans+=query(dfn[now]);
	}
	return ans;
}
inline void Dfs(int x){
	if(q[x].opt==1)ad(dfn[Id[x]],1),ad(dfn[Id[x]]+siz[Id[x]],-1);
	else if(x)out[x]=solve(q[x].s);
	E(x)Dfs(y);
	if(q[x].opt==1)ad(dfn[Id[x]],-1),ad(dfn[Id[x]]+siz[Id[x]],1);
}
int main(){
	rep(i,1,n)q[i].opt=read(),p[read()].pb(i),cin >>q[i].s;
	rep(i,1,n)if(q[i].opt==1)insert(q[i].s,i);
	build(),Dfs(0);
	rep(i,1,n)if(q[i].opt==2)pf(out[i]),putchar('\n');
	return 0;
}
```


---

