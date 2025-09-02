# Autocompletion

## 题目描述

给定一个 **仅包含小写字母的** 字符串集 $S$，你需要计算打出 $S$ 中的每个字符串需要花费的时间。

打一个字符串的步骤如下：

1. 从一个空串开始；

2. 如果当前的字符串是 $t$，你可以在 $t$ 的末尾拼接任意一个小写字母 $c$，使得此时字符串变为 $t + c$，这个过程耗费 $1$s；

3. 使用 **自动补全功能**，设当前字符串是 $t$，此时所有的 $s \in S$ 且 $t$ 是 $s$ 的前缀将会以 **字典序** 为你展现出来，其中你自动补全到第 $i$ 个串所耗费的时间为 $i$ s。

问打出 $S$ 中的所有字符串 **最短** 需要耗费多长时间。

**需要的注意的是 字符串集 $S$ 的给出方式**

## 样例 #1

### 输入

```
10
0 i
1 q
2 g
0 k
1 e
5 r
4 m
5 h
3 p
3 e
5
8 9 1 10 6```

### 输出

```
2 4 1 3 3```

## 样例 #2

### 输入

```
8
0 a
1 b
2 a
2 b
4 a
4 b
5 c
6 d
5
2 3 4 7 8```

### 输出

```
1 2 2 4 4```

# 题解

## 作者：xtx1092515503 (赞：5)

很明显按照题意建出来的东西是一颗trie。

于是我们就设$f[i]$表示到达字典树上第$i$个点最少步数。

则我们如果设$delta_i$表示$i$节点是树上字典序第$delta_i$小的节点的话，我们就可以得到转移方程：

$$f[i]=\max\begin{cases}f[fa]+1\\f[anc]-delta_{anc}+delta_i\end{cases}$$

上半部可以直接$O(1)$转移，关键是下半部。

我们可以直接将$f[anc]-delta_{anc}$压到一个栈中，如果发现新到达的这个点的$f[x]-delta_x$要小于栈顶的元素，就直接入栈。然后转移时就直接使用栈顶元素即可。当离开一个节点时，弹出它对应的元素（假如那个数还在栈中的话）。

然后我们发现这个$delta$数组实际上都不用建出来，直接用一个值$delta$维护即可。

复杂度$O(n)$。

代码（29行小清新马蜂，你值得拥有）：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,delta,q[1001000];
struct trie{
	int ch[26],f;
	bool fin;
}t[1001000];
stack<pair<int,int> >s;
void dfs(int x){
	if(s.empty()||t[x].f-delta<s.top().second)s.push(make_pair(x,t[x].f-delta));
	delta+=t[x].fin;
	for(int i=0;i<26;i++){
		if(!t[x].ch[i])continue;
		t[t[x].ch[i]].f=t[x].f+1;
		if(!s.empty()&&t[t[x].ch[i]].fin)t[t[x].ch[i]].f=min(t[t[x].ch[i]].f,s.top().second+delta+1);
		dfs(t[x].ch[i]);
	}
	if(!s.empty()&&s.top().first==x)s.pop();
}
char str[2];
int main(){
	scanf("%d",&n);
	for(int i=1,x;i<=n;i++)scanf("%d%s",&x,str),t[x].ch[str[0]-'a']=i;
	scanf("%d",&m);
	for(int i=1,x;i<=m;i++)scanf("%d",&q[i]),t[q[i]].fin=true;
	dfs(0);
	for(int i=1;i<=m;i++)printf("%d ",t[q[i]].f);
	return 0;
} 
```


---

## 作者：Liveddd (赞：3)

巨佬讲课用的题目 qwq。

很明显我们可以先把 Trie 树建出来，直接考虑 DP 。一个子节点 $x$ 在其以 $u$ 为根的子树的字典序排名为 $dfn_x-dfn_u+1$，于是，我们设 $f_x$ 为打出第 $x$ 个串的最小花费，很容易得到下面这个转移：

$f_x=min\{f_{fa}+1,f_u+dfn_x-dfn_u+1\}$，其中 $u$ 为 $x$ 的某个父节点

考虑优化，我们把 $f_u+dfn_x-dfn_u+1$ 拆成只关于 $x$ 的 $dfn_x$ 和只关于 $u$ 的 $f_u-dfn_u+1$ 两部分，我们只需要用一个 $g_x$ 来维护只关于 $u$ 的部分的最小值即可，就可以实现 $O(1)$ 转移，总时间复杂度 $O(n)$。

代码也很清晰明了

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int N=1e6+10;
template <class T>
inline void read(T &x)
{
	x=0;int f=0;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=1;ch=getchar();};
    while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    if(f)x=~x+1;
}
template<class T,class ...T1>
inline void read(T &x,T1 &...x1)
{
    read(x);
    read(x1...);
}

int n,k;
int ch[N][26],a[N],v[N];
int cnt,dfn[N],f[N],g[N];
void dfs(int x)
{
	if(v[x])
		dfn[x]=++cnt;
	for(int i=0;i<26;i++)
		if(ch[x][i])
		{
			dfs(ch[x][i]);
			dfn[x]=min(dfn[x],dfn[ch[x][i]]);//注意对dfn[x]的处理
		}
}
void dp(int x)
{
	for(int i=0;i<26;i++)
	{
		int ver=ch[x][i];
		if(!ver)continue;
		if(v[ver])
			f[ver]=min(f[x]+1,dfn[ver]+g[x]);
		else f[ver]=f[x]+1;
		g[ver]=min(g[x],f[ver]-dfn[ver]+1);
		dp(ver);
	}
}
int main()
{
	
	read(n);
	for(int i=1;i<=n;i++)
	{
		int x;
		char s[10];
		read(x);
		scanf("%s",s);
		ch[x][s[0]-'a']=i;
	}
	read(k);
	for(int i=1;i<=k;i++)
		read(a[i]),v[a[i]]=1;
	memset(dfn,0x3f,sizeof(dfn));
	memset(f,0x3f,sizeof(f));
	memset(g,0x3f,sizeof(g));
	dfs(0);
	f[0]=g[0]=0;
	dp(0);
	for(int i=1;i<=k;i++)
		printf("%d ",f[a[i]]);
	return 0;
}
```

---

## 作者：EuphoricStar (赞：2)

考虑直接在题目给的 Trie 上 dp，设 $f_u$ 为打出 $u$ 结点的串的最小代价。

- 首先我们有 $f_u \gets f_{fa_u} + 1$。
- 我们有 $f_u \gets \min\limits_v f_v + t + 1$，要求 $u$ 是某个串的终止结点，$v$ 是 $u$ 的祖先，$t$ 是字典序大于等于 $v$，小于 $u$ 的串的个数。

发现我们可以把 $f_u$ 扔进一个可删堆里，每个点按字典序遍历对应的子结点，每次经过一棵子树就给这个堆打一个整体加这棵子树大小的 tag。这个可以直接用一个变量维护 tag。

时间复杂度 $O(n \log n)$。

[code](https://codeforces.com/problemset/submission/1312/241224358)

---

## 作者：daniEl_lElE (赞：2)

考虑先建出 trie 树。

在 dfs 过程中，考虑维护两个量：上一步通过打一个字到这里的最小操作数 $dep$，通过自动补全到这里的最小操作数 $minv$。

考虑转移，分成两类。

当该节点为某个串的终点，这个串的答案显然为 $\min(dep,minv)$。

* 对于深度，我们可以跳到这里然后继续往下走，故 $dep'=\min(dep,minv)$。
* 对于自动补全，我们想要到这个子树里的其他位置，就一定会多经过一个这个字符串。如果说我们上一步通过打一个字到这里，然后再去跳，还会出现这个字符串。故 $minv'=\min(dep+2,minv+1)$。

当该节点不为某个串的终点时。

* 对于自动补全，我们可以考虑从这里开始自动补全，故 $minv'=\min(dep+1,minv)$。

总复杂度 $O(n)$。

```cpp
#include <bits/stdc++.h>
#pragma GCC optimize(2,3,"Ofast","inline")
#define int long long
#define double long double
#define mid ((l+r)>>1)
using namespace std;
int n,trie[1000005][26],tag[1000005],endp[1000005],ans[1000005];
void dfs(int now){
	for(int i=0;i<26;i++){
		if(trie[now][i]){
			dfs(trie[now][i]);
			tag[now]+=tag[trie[now][i]];
		}
	}
}
void cal(int now,int dep,int minv){
	if(endp[now]){
		ans[endp[now]]=min(dep,minv);
		int odep=min(dep,minv);
		minv=min(minv+1,dep+2);
		dep=odep;
	}
	else minv=min(dep+1,minv);
	for(int i=0;i<26;i++){
		if(trie[now][i]){
			cal(trie[now][i],dep+1,minv);
			minv+=tag[trie[now][i]];
		}
	}
}
signed main(){
	int n; cin>>n;
	for(int i=1;i<=n;i++){
		int fa; char c;
		cin>>fa>>c;
		trie[fa][c-'a']=i;
	}
	int m; cin>>m;
	for(int i=1;i<=m;i++){
		int p; cin>>p;
		tag[p]=1,endp[p]=i;
	}
	dfs(0);
	cal(0,0,1);
	for(int i=1;i<=m;i++) cout<<ans[i]<<" ";
	return 0;
}

```

---

## 作者：lightup37 (赞：2)

时间复杂度略劣的题解（用 pbds 的 $\mathcal O(1)$ 插入配对堆写 dijkstra 才能过的那种XD）

---

## 题意

给你一颗 trie 树喵。

trie 树上有若干个关键串 $T_1, T_2, \cdots T_k$ 喵。

对于每一个关键串，你要求出从空串 $S$ 开始打出它花费的最小时间喵。

你有两种操作，第一种操作是在 $S$ 后面加一个任意字符喵。花费 $1$ 秒喵。

第二种操作是自动补全喵。可以花费 $i$ 秒，把 $S$ 变为集合 $\{T_i|S\text{ is a prefix of }T_i\}$ 中的字典序第 $i$ 小的串喵。

trie 树大小喵？只有 $10^6$ 哦喵。

## 解法

考虑建图最短路。首先 trie 树上的边要连边权为 $1$ 的边，这样可以处理掉第一种操作。对于第二种操作，每个节点到每个可以自动补全到的节点连边当然是可行的，但是时间复杂度不允许。考虑每个节点利用其儿子的信息：具体来说，我们考虑建立分层图，把第二种操作的转移在上层做，第一种操作的转移在下层做。一个下层节点可以直接花费 $0$ 代价转移到对应的上层节点，一个对应的下层节点是关键串所在点的上层节点可以花费 $1$ 代价转移到对应的下层节点。考虑一个非叶子非关键节点，其走到字典序最小的儿子不需要花费代价，走到字典序第二小的儿子需要花费等同于字典序最小的儿子的子树中的关键串数量的代价（自动补全时，这些串会在字典序第二小的儿子的串的前面，故需要花费额外的时间）。非叶子关键节点只需要让这些转移边的代价都 $+1$ 就好了，具体可以看代码。

使用配对堆优化 dijkstra 求出最短路，总复杂度 $\mathcal O(n\log n + m)$。

```cpp
#pr\
agma optimize("Ofast")

#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/priority_queue.hpp>
#define f(i,x,y) for(int i=x, i##end=y; i<=i##end; ++i)
#define d(i,x,y) for(int i=y, i##end=x; i>=i##end; --i)
#define uf(i,x,y) for(int i=x, i##end=y; i<i##end; ++i)
#define ll long long
#define pir pair<int, int>
#define fir first
#define sec second
#define mp make_pair
#define pb push_back 
char ch;
int rd() {
	int f=1, x=0; ch=getchar();
	while(!isdigit(ch)) { f=((ch=='-')?-1:f); ch=getchar(); }
	while(isdigit(ch)) { x=x*10+ch-'0'; ch=getchar(); }
	return x*f;
}
void rd(int& x) { x=rd(); }
using namespace std;
const int _ = 2e6 + 5;
int tr[_][26], sz[_], n, k, inq[_], dis[_], q[_];
vector< pair<int, int > > edge[_];
void insert(int p, char ch, int id) {
	tr[p][ch - 'a'] = id;
}
void addedge(int u, int v, int w) {
	// cerr << "add : " << u << " -> " << v << " " << w << endl;
	edge[u].pb(mp(v, w));
}
void dfs(int u) {
	if(inq[u]) ++sz[u], addedge(u+n+1, u, 1);
	f(i,'a','z') {
		if(tr[u][i - 'a']) {
			dfs(tr[u][i - 'a']);
			addedge(u+n+1, tr[u][i - 'a']+n+1, sz[u]);
			sz[u] += sz[tr[u][i - 'a']];
		}
	}
}
__gnu_pbds::priority_queue< pir , greater< pir > , __gnu_pbds::pairing_heap_tag > Q;
void dijkstra(int u) {
	memset(dis, 0x3f, sizeof(dis)); dis[u] = 0; Q.push(mp(-dis[u], u));
	while(Q.size()) {
		int u = Q.top().sec; Q.pop();
		// cerr << "at " << u << endl;
		for(auto [v, w] : edge[u]) {
			if(dis[v] > dis[u]+w) {
				Q.push(mp(-dis[v], v));
				dis[v] = dis[u] + w;
			}
		}
	}
}
int main() {
	ios :: sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	rd(n); f(i,1,n) {
		int p = rd(); char c = 0; while(!(c >= 'a' && c <= 'z')) c=getchar();
		// cerr << p << ' ' << ch << endl;
		insert(p, c, i);
		addedge(p, i, 1);
		addedge(i, i+n+1, 0);
	}
	addedge(0, n+1, 0);
	rd(k); f(i,1,k) {
		rd(q[i]); inq[q[i]] = 1;
	}
	dfs(0);
	dijkstra(0);
	f(i,1,k) cout << dis[q[i]] << " \n"[i == k];
	return 0;
}
```

---

## 作者：ax_by_c (赞：0)

八个月前的我都会做（当时比赛没调出来），为啥紫啊/yiw

显然字典树上 DP，设 $f_i$ 为打出根节点到第 $i$ 个节点路径所表示的串所需的最小时间。

一操作转移是显然的。对于二操作，考虑使用一个 DS 在 dfs 的同时维护祖先节点对当前节点的转移。

不难发现这个 DS 需要处理以下操作：

- 加入一个数

- 删除最后一个加入的数

- 整体加上一个数

- 查询最小值

在一个栈上加点东西即可，时间复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace ax_by_c{
const int N=1e6+5;
const int inf=1e9;
void chk(int &x,int y){
    x=(x<y)?(x):(y);
}
struct DS1{
    int stk[N],top,dlt;
    void Init(){
        top=0;
        dlt=0;
        stk[0]=inf;
    }
    void push(int x){
        x-=dlt;
        top++;
        stk[top]=min(stk[top-1],x);
    }
    void pop(){
        top--;
    }
    int getmin(){
        return stk[top]+dlt;
    }
    void add(int val){
        dlt+=val;
    }
}qwq;
int n,pos[N];
int son[N][26],idx;
int k,qs[N];
bitset<N>mk;
int dp[N];
void dfs(int u){
    if(mk[u]){
        qwq.add(1);
        chk(dp[u],qwq.getmin());
        qwq.push(dp[u]+1);
    }
    else qwq.push(dp[u]);
    for(int i=0;i<26;i++){
        if(son[u][i]){
            chk(dp[son[u][i]],dp[u]+1);
            dfs(son[u][i]);
        }
    }
    qwq.pop();
}
void main(){
    scanf("%d",&n);
    for(int i=1,fa;i<=n;i++){
        char c;
        scanf("%d %c",&fa,&c);
        if(!son[pos[fa]][c-'a'])son[pos[fa]][c-'a']=++idx;
        pos[i]=son[pos[fa]][c-'a'];
    }
    scanf("%d",&k);
    for(int i=1;i<=k;i++){
        scanf("%d",&qs[i]);
        qs[i]=pos[qs[i]];
        mk[qs[i]]=1;
    }
    for(int i=1;i<=idx;i++)dp[i]=inf;
    qwq.Init();
    dfs(0);
    for(int i=1;i<=k;i++)printf("%d ",dp[qs[i]]);
}
}
int main(){
    ax_by_c::main();
    return 0;
}
```

---

## 作者：Hoks (赞：0)

## 前言
感觉这题很水？CF 评了 $2600$，但是貌似是挺一眼的。

摘自 [杂题选做](https://www.luogu.com.cn/training/518105)。
## 思路分析
题目给我们是一个字符串后面加一个字母这样的形式，显然就是一颗 trie 嘛。

那么我们直接就把 trie 建出来。

接着考虑怎么求这个值。

不难发现其实只有两种可能性：
1. 直接从父亲拼接一个字母转移。
2. 从一个祖先直接跳过来，代价为 dfn 序比他小且都有这个共同祖先的点个数 $+1$。

因为点有两种，一种是要询问的，一种是不用询问的。

那么对要询问的所有串按照字典序排个序，按顺序标号分别为 $1,2,\dots,k$。

定义一个点的 dfn 序为他子树中所有询问点的最小值。

再定义 $f_u$ 为点 $u$ 的答案，那么就可以得到两种转移方程：
$$f_v=f_u+1,(fa_v=u)$$
$$f_v=f_u+dfn_v-dfn_u+1$$

其中第二个式子中的 $u$ 是 $v$ 的祖先。

观察到 $dfn_v$ 不变，直接提出去单独维护下剩下部分即可。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10,INF=0x3f3f3f3f3f3f3f3f,mod=998244353;
int n,m,tot,cnt,f[N],g[N],dfn[N],a[N],mp[N],t[N][27];char s[N];
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
    inline bool chk(char c) { return !(c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'); }
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
inline void dfs(int u)
{
    if(mp[u]) dfn[u]=++cnt;
    for(int i=0;i<26;i++) if(t[u][i]) dfs(t[u][i]),dfn[u]=min(dfn[u],dfn[t[u][i]]);
}
inline void calc(int u)
{
    for(int i=0;i<26;i++)
    {
        int v=t[u][i];if(!v) continue;
        f[v]=min(f[u]+1,mp[v]?dfn[v]+g[u]:INF);
        g[v]=min(g[u],f[v]-dfn[v]+1);calc(v);
    }
}
inline void solve()
{
    n=read();
    for(int i=1,x,l;i<=n;i++)
    {
        x=read();l=0;rd(s,l);
        t[x][s[1]-'a']=++tot;
    }m=read();for(int i=1;i<=m;i++) mp[a[i]=read()]=1;
    memset(dfn,0x3f,sizeof dfn);dfs(0);memset(f,0x3f,sizeof f);
    memset(g,0x3f,sizeof g);f[0]=g[0]=0;calc(0);
    for(int i=1;i<=m;i++) print(f[a[i]]),put(' ');
}
signed main()
{
    int T=1;while(T--) solve();
    genshin:;flush();return 0;
}
```

---

## 作者：BreakPlus (赞：0)

题目的输入方式启示我们建立出 trie 树，同时其 dfn 序也具备了查询字典序大小的条件。

考虑 trie 树上一个前缀对其子树内的贡献。记录一个前缀 $pre(i)$ 表示 dfn 序中前 $i$ 个字符串有多少个是询问串。此时对于一个点 $u$，其子树内的点 $v$，有转移 $dp(u) - pre(dfn(u)-1) + pre(dfn(v)) \to dp(v)$。

dfs 的时候维护树上当前点到根路径上 $dp(u) - pre(dfn(u)-1)$ 的最小值。注意这条转移需要满足该点对应的串是询问串。另外 $dp(u) + 1 \to dp(son)$ 不必多说。

**可以做到** $\mathcal{O}(n)$。

```cpp
ll n,p[1000005],sz[1000005],son[1000005][26],ans[1000005],dfn[1000005],line[1000005],vis[1000005],ins[1000005],dp[1000005],tim;
char c[1000005]; char str[5];
multiset<ll>Q;
void dfs(ll x){
	dfn[x]=++tim; sz[x]=1; line[tim]=x;
	vis[tim] = vis[tim-1] + (ins[x]>=1);
	for(ll i=0;i<26;i++){
		if(son[x][i]) dfs(son[x][i]), sz[x]+=sz[son[x][i]]; 
	}
}
 
void dfs2(ll x){
	if(x){
		dp[x]=dp[p[x]]+1;
	}
	if(ins[x]){
		if(Q.size()>0) dp[x]=minn(dp[x],(*Q.begin())+vis[dfn[x]]);
		ans[ins[x]]=dp[x];
	}
	ll w = dp[x] - vis[dfn[x]-1]; Q.insert(w);
	for(ll i=0;i<26;i++){
		if(son[x][i]) {
			dfs2(son[x][i]);
		}
	}
	Q.erase(Q.find(w));
}
void solve(){
	n=read();
	for(ll i=1;i<=n;i++){
		p[i]=read(); scanf("%s",str);
		c[i]=str[0]; son[p[i]][c[i]-'a']=i;
	}
	ll k=read();
	for(ll i=1;i<=k;i++) ins[read()]=i;
	dfs(0);
	dfs2(0);
	for(ll i=1;i<=k;i++) printf("%lld ", ans[i]);
}
```

---

## 作者：Clever_Jimmy (赞：0)

首先，我们可以根据题目给的所有字符建一个 Trie。

我们考虑在这个 Trie 上进行 dp。

设 $ans_i$ 表示打出 Trie 上的 $i$ 号结点到根所表示的字符串所需的最少时间。

不难发现，直接接上一个字符的递推式是 $ans_v = \min\limits_{u \in son(v)}\{ans_u + 1\}$

但是我们要考虑“自动补全”的操作。

在 Trie 树上 dp 的时候，我们可以维护一个值，表示最小的通过自动补全用的时间。

递推的时候我们把它传递到下一个结点，但要加上其他儿子带来的在 "List" 里的编号变化。

```cpp
int dfs(int u, int candidates) {
	int rank = 0; // the rank of the word in the list
	if(tar[u]) {
		ans[u] = std::min(ans[u], candidates);
		++rank;
	}
	for(int i = 0; i < vec[u].size(); ++i) {
		int v = vec[u][i].nxt;
		ans[v] = ans[u] + 1;
		// updateing v by using u (append a char)
		rank += dfs(v, std::min(ans[v], candidates) + rank);
	}
	return rank;
}
```

[code](https://codeforces.ml/contest/1312/submission/73346310)

```cpp
#include <bits/stdc++.h>
#define LL long long

const int oo = 0x3f3f3f3f;
const int N = 1e6 + 5;

int n, m, q[N], tar[N], ans[N];

struct NODE {
	char c;
	int nxt;
	bool operator<(const NODE &rhs) const {
		return c < rhs.c;
	}
	NODE(char _c = '\0', int _nxt = -1) {
		c = _c, nxt = _nxt;
	}
};

std::vector <NODE> vec[N];

int dfs(int u, int candidates) {
	int rank = 0; // the rank of the word in the list
	if(tar[u]) {
		ans[u] = std::min(ans[u], candidates);
		++rank;
	}
	for(int i = 0; i < vec[u].size(); ++i) {
		int v = vec[u][i].nxt;
		ans[v] = ans[u] + 1;
		// updateing v by using u (append a char)
		rank += dfs(v, std::min(ans[v], candidates) + rank);
	}
	return rank;
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) {
		int fa; char ch[5];
		scanf("%d %s", &fa, ch);
		vec[fa].push_back(NODE(ch[0], i));
	}
	for(int i = 0; i < n; ++i) std::sort(vec[i].begin(), vec[i].end());
	// sorting is needed for the 'lexicographically' list
	scanf("%d", &m);
	for(int i = 1; i <= m; ++i) {
		scanf("%d", &q[i]);
		tar[ q[i] ] = 1;
		// offline all the queries
	}
	dfs(0, oo);
	for(int i = 1; i <= m; ++i) printf("%d ", ans[ q[i] ]);
	return 0;
}

```

---

