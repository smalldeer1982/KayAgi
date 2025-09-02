# [ARC165D] Substring Comparison

## 题目描述

对于整数列 $X=(X_1,X_2,\dots,X_n)$，用 $X[L,R]$ 表示整数列 $(X_L,X_{L+1},\dots,X_{R})$。

给定整数 $N,M$ 和 $M$ 组整数 $(A_i,B_i,C_i,D_i)$。

请判断是否存在一个长度为 $N$ 的整数列 $X$，使得对于所有 $i=1,2,\dots,M$，都满足以下条件：

- $X[A_i,B_i]$ 在字典序上小于 $X[C_i,D_i]$。

数列的字典序定义如下：设数列 $S=(S_1,S_2,\ldots,S_{|S|})$，$T=(T_1,T_2,\ldots,T_{|T|})$，若满足以下 1. 或 2. 中的任意一个，则称 $S$ 在字典序上小于 $T$。其中 $|S|,|T|$ 分别表示 $S,T$ 的长度。

1. $|S|<|T|$ 且 $(S_1,S_2,\ldots,S_{|S|})=(T_1,T_2,\ldots,T_{|S|})$。
2. 存在整数 $1\leq i\leq \min\lbrace |S|,|T| \rbrace$，使得以下两点都成立：
   - $(S_1,S_2,\ldots,S_{i-1})=(T_1,T_2,\ldots,T_{i-1})$
   - $S_i$ 小于 $T_i$（作为数值比较）。

## 说明/提示

### 数据范围

- $2\leq N\leq 2000$
- $1\leq M\leq 2000$
- $1\leq A_i\leq B_i\leq N$
- $1\leq C_i\leq D_i\leq N$
- 输入的所有值均为整数

### 样例解释 1

例如 $X=(1,1,2,1)$ 就满足所有条件。

### 样例解释 2

不存在满足条件的整数列 $X$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4 2
1 3 3 4
4 4 1 2```

### 输出

```
Yes```

## 样例 #2

### 输入

```
3 2
1 2 2 3
2 2 1 1```

### 输出

```
No```

## 样例 #3

### 输入

```
15 20
2 5 6 14
11 14 10 10
13 15 6 10
8 10 3 8
7 8 1 9
2 8 14 15
14 14 5 12
6 10 9 9
1 4 10 14
5 14 6 7
8 10 5 8
8 10 11 15
4 8 4 11
7 9 1 4
8 10 3 3
11 13 8 14
6 13 4 15
4 7 6 11
2 5 1 2
8 14 6 8```

### 输出

```
No```

# 题解

## 作者：樱雪喵 (赞：13)

## Description

构造一个长度为 $n$ 的整数序列 $X$，使其满足 $m$ 条限制。第 $i$ 条限制形如 $(A_i,B_i,C_i,D_i)$，表示要求 $X$ 的子段 $[A_i,B_i]$ 字典序小于 $[C_i,D_i]$。问是否存在满足条件的序列 $X$。

$n,m\le 2000$。

## Solution

对于 $A_i=C_i$ 的询问，可以直接比较 $B_i$ 和 $D_i$ 的大小，$B_i>D_i$ 则无解，否则这个限制一定满足，可以忽略。因此，我们假设所有询问满足 $A_i\neq C_i$。

我们希望每组限制的两个区间在尽量靠前的位置上就开始不一样，因为这样后面的位就都没有大小限制。看到判断若干点之间的大小关系能否满足，考虑建图。

对每组限制连边 $A_i\to C_i$，表示对于 $X$ 有限制 $X_{A_i}\le X_{C_i}$。那么连出的这个图分两种情况：

- 图里没有环，则直接按拓扑序给 $X$ 的每个位置赋值即可，答案为 `Yes`。
- 图里有环，需要做进一步考虑。

对于在同一个强连通分量内的点，要满足图连边的大小关系，它们的 $X$ 值必须都相等。因此可以对这个图跑 tarjan 求出强连通分量，并重新依次考虑题目给出的每个限制：

- 如果 $A_i$ 和 $C_i$ 不在一个强连通分量，那么它们所在位置的 $X$ 值不相等，这个字典序的条件已经满足了；
- 否则，代表 $X_{A_i}$ 和 $X_{C_i}$ 一定是相等的，需要限制它们下一位的大小关系。我们令 $A_i\gets A_i+1,C_i\gets C_i+1$，并在缩点后的图上重新建图，重复以上步骤。
- 如果一直重复到 $A_i=B_i$ 或 $C_i=D_i$ 它们都只能相等，判断哪个区间还剩下一段，如果是前面的区间剩一段就无解。否则这个限制已经满足。

如果重复完了上述步骤，中途没有被判无解，就是有解。

每次重复该过程都会让当前未满足限制的 $A_i\gets A_i+1$，至多重复 $n$ 次。每次跑一个 tarjan，复杂度 $O(n+m)$。总复杂度 $O(n^2+nm)$。

代码为了好写用并查集维护了哪些点值相等，但这不是复杂度瓶颈。

```cpp
const int N=2005;
int n,m,fa[N];
int find(int x) {return fa[x]==x?x:fa[x]=find(fa[x]);}
il void merge(int x,int y) {if(find(x)!=find(y)) fa[find(x)]=find(y);}
struct edge{int nxt,to;}e[N<<1];
int head[N],cnt;
il void add(int u,int v) {e[++cnt]={head[u],v};head[u]=cnt;}
int dfn[N],low[N],in[N],tot;
stack<int> Q;
bool flag;
void tarjan(int u)
{
    dfn[u]=low[u]=++tot,in[u]=1; Q.push(u);
    for(int i=head[u];i;i=e[i].nxt)
    {
        int v=e[i].to;
        if(!dfn[v]) tarjan(v),low[u]=min(low[u],low[v]);
        else if(in[v]) low[u]=min(low[u],dfn[v]);
    }
    if(dfn[u]==low[u])
    {
        while(!Q.empty())
        {
            int t=Q.top(); if(t!=u) flag=1;
            merge(t,u),in[t]=0,Q.pop();
            if(t==u) break;
        }
    }
}
il void clear() 
{
    memset(head,0,sizeof(head)),cnt=0;
    memset(dfn,0,sizeof(dfn)),memset(low,0,sizeof(low)),tot=0;    
}
struct node{int a,b,c,d;} q[N];
int main()
{
    n=read(),m=read();
    for(int i=1;i<=m;i++) q[i]={read(),read(),read(),read()};
    for(int i=1;i<=n;i++) fa[i]=i;
    for(int w=1;w<=n;w++)
    {
        clear();
        for(int i=1;i<=m;i++)
        {
            while(find(q[i].a)==find(q[i].c)&&q[i].a<=q[i].b&&q[i].c<=q[i].d)
                q[i].a++,q[i].c++;
            if(q[i].c>q[i].d) {printf("No\n");return 0;}
            if(q[i].a<=q[i].b) add(find(q[i].a),find(q[i].c));
        }
        flag=0;
        for(int i=1;i<=n;i++) if(!dfn[i]) tarjan(i);
        if(!flag) break;
    }
    printf("Yes\n");
    return 0;
}
```

---

## 作者：翼德天尊 (赞：5)

其实没必要一上来就把约束形式化描述的，不妨先只考虑每一条约束中最简洁最弱的那个，即 $a_i<c_i$。

将二元偏序关系连边，如果不出现环则直接出解，否则每个强连通分量位置上的值一定相同，而这些相同会打破一些偏序关系，强制使得一些 $a_i=c_i$。此时我们可以将被打破的约束中的 $a_i,c_i$ 不断后移，直到两者不在同一连通分量为止，此时若 $c_i>d_i$，则一定无解，否则若 $a_i>b_i$，我们之后就可以不再管这条约束。若 $a_i,c_i$ 依旧小于 $b_i,d_i$，我们可以在图上建立若干新边表示这些新的偏序关系，一直做下去直到不再产生新的强连通分量为止。

由于至多会跑 $n$ 次 tarjan，且对于每个偏序关系至多移动 $n$ 次，所以时间复杂度为 $O(n(n+m))$。

本题启发我们对于带有继承关系的【或】约束，不妨先从最弱的约束下手，根据是否合法依次增强约束。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2005;
int n,m,dfn[N],low[N],cnt,bl[N],st[N],stot,tim,rbl[N],rcnt;
bool vis[N],ban[N];
struct node{
    int a,b,c,d;
}p[N];
struct Edge{
    int to[N*N],next[N*N],head[N],tot;
    void adde(int u,int v){
        to[++tot]=v,next[tot]=head[u],head[u]=tot;
    }
    void clear(){
        memset(head,0,sizeof(head));
        tot=0;
    }
}S;
ll read(){
    ll w=0,f=1;
    char c=getchar();
    while (c>'9'||c<'0'){
        if (c=='-') f=-1;
        c=getchar();
    }
    while (c>='0'&&c<='9'){
        w=(w<<3)+(w<<1)+(c^48);
        c=getchar();
    }
    return w*f;
}
void tarjan(int u){
    dfn[u]=low[u]=++tim;
    st[++stot]=u,vis[u]=1;
    for (int i=S.head[u];i;i=S.next[i]){
        int v=S.to[i];
        if (!dfn[v]){
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }else if (vis[v]) low[u]=min(low[u],dfn[v]);
    }
    if (dfn[u]==low[u]){
        int in;
        ++cnt;
        while (in=st[stot--]){
            vis[in]=0,bl[in]=cnt;
            if (in==u) break;
        }
    }
}
void no(){
    puts("No");
    exit(0);
}
int main(){
#ifndef ONLINE_JUDGE
    freopen("in.in","r",stdin);
    // freopen("out.out","w",stdout);
#endif
    rcnt=n=read(),m=read();
    for (int i=1;i<=n;i++) rbl[i]=i;
    for (int i=1;i<=m;i++){
        p[i].a=read(),p[i].b=read(),p[i].c=read(),p[i].d=read();
    }
    for (int i=1;i<=m;i++)
        if (!ban[i]) S.adde(p[i].a,p[i].c);
    for (int i=1;i<=n;i++)
        if (!dfn[i]) tarjan(i);  
    while (rcnt>1&&cnt<rcnt){
        for (int i=1;i<=m;i++){
            if (ban[i]) continue;
            if (bl[p[i].a]==bl[p[i].c]){
                while (p[i].a<=p[i].b&&p[i].c<=p[i].d&&bl[p[i].a]==bl[p[i].c]) ++p[i].a,++p[i].c;
                if (p[i].a<=p[i].b&&p[i].c<=p[i].d) S.adde(p[i].a,p[i].c);
            }
            if (p[i].c>p[i].d) no();
            else if (p[i].a>p[i].b) ban[i]=1;
        }
        rcnt=cnt,cnt=tim=stot=0;
        memset(dfn,0,sizeof(dfn));
        memset(low,0,sizeof(low));
        for (int i=1;i<=n;i++)
            if (!dfn[i]) tarjan(i);    
        // cout<<rcnt<<" "<<cnt<<"\n";      
    }
    puts("Yes");
    return 0;
}
```

---

## 作者：another_world (赞：2)

### 题目链接：[ARC 165-D](https://atcoder.jp/contests/arc165/tasks/arc165_d)


------------
### 题解思路：
1. 考虑每条约束条件中**最直接，最简洁的**要求满足  $A_i < C_i$

2. **依据约束条件连边**，若不存在环，则一定存在解，否则每个强联通分量中的点位置上的值一定相同，即要求一些约束条件 $A_i = C_i$ 

3. 通过 (2) 的**进一步约束**，再根据 (1) 不断向后寻找新的约束限制 $A_i < C_i$，即 **$A_i$ 与 $C_i$ 不断向 $B_i$ 和 $D_i$ 后移**，直至两者不在同一强联通分量为止 

4.  不断重复 (2) 的约束限制，(3) 的后移，若 $B_i > D_i$ ，则一定无解，反之若 $A_i> C_i$，则该约束条件可以成立  

- **总结：** 对于带有继承关系的【**或**】约束，不妨先从最直接的约束下手，根据是否合法依次增强约束


------------
### Code：
```cpp
#include<bits/stdc++.h>
using namespace std; 
const int N=2010;
int n,m,a[N],b[N],c[N],d[N],fa[N];
int dfn[N],low[N],num;
int ta[N],ins[N],top,cnt;
vector<int> scc[N];
struct EDGE {
	int v,lt;
}E[N];
int head[N],tot;
void add(int u,int v) {
	E[++tot].v=v;
	E[tot].lt=head[u];
	head[u]=tot;
}
int get(int x) {
	if(x==fa[x]) return x;
	return fa[x]=get(fa[x]);
}
void tarjan(int x) {
	dfn[x]=low[x]=++num;
	ta[++top]=x,ins[x]=1;
	for(int i=head[x]; i; i=E[i].lt) {
		int y=E[i].v;
		if(!dfn[y]) {
			tarjan(y);
			low[x]=min(low[x],low[y]);
		}
		else if(ins[y]) low[x]=min(low[x],dfn[y]);
	}
	if(dfn[x]==low[x]) {
		cnt++; int y;
		do {
			y=ta[top--]; ins[y]=0;
			scc[cnt].push_back(y);
		} while(x!=y);
	}
} 
void init() {
	for(int i=1; i<=n; i++) {
		head[i]=dfn[i]=low[i]=ins[i]=0;
		scc[i].clear();
	}
	tot=num=top=cnt=0; 
} 
int main() {
    scanf("%d%d",&n,&m);
    for(int i=1; i<=n; i++) fa[i]=i; 
    for(int i=1; i<=m; i++) {
    	scanf("%d%d%d%d",&a[i],&b[i],&c[i],&d[i]); 
	}
	while(1) {
	    init();
		for(int i=1; i<=m; i++) {
			while(a[i]<=b[i] && c[i]<=d[i] && get(a[i])==get(c[i])) { // 通过并查集来维护序列 A 每个位置的值是否要求相同 
				a[i]++;
				c[i]++;
			}
			if(c[i]>d[i]) {
				printf("No");
				return 0;
			}
			if(a[i]<=b[i] && c[i]<=d[i]) add(get(a[i]),get(c[i]));
		}
	    for(int i=1; i<=n; i++) 
	        if(!dfn[i]) {
	        	tarjan(i);
			} 
		if(cnt==n) {
			printf("Yes");
			return 0;
		}
		for(int i=1; i<=cnt; i++) {
			int x=get(scc[i][0]);
			for(int j=1; j<scc[i].size(); j++) {
				fa[get(scc[i][j])]=x;
			}
		}
	} 
	return 0;  
}
```


---

## 作者：E_fang (赞：1)

# arc165_d Substring Comparison

## 简要题意

给定整数 $n,m$，以及 $m$ 个四元组 $(a_i,b_i,c_i,d_i)$。

判断是否存在一个长度为 $n$ 的正整数序列 $x$，满足 $\forall i\in [1,m]$，$x_{a_i}\sim x_{b_i}$ 组成的序列的字典序**严格小于** $x_{c_i}\sim x_{d_i}$ 组成的序列。

$n,m\le 2\times 10^3$。

## 题解

知识点：图论，强连通分量。

启发：

- 处理多元互相制约的问题考虑建出限制图。

$n,m\le 2\times 10^3$，说明做法大概在 $O(n^2)$ 左右。

初始时，建出一个图，将所有 $a_i$ 向 $c_i$ 连一条有向边，表示 $x_{a_i}<x_{c_i}$。

如果当前图中不存在大小 $\ge 2$ 的强连通分量，那说明是满足条件的，直接输出 `Yes`，判断这个东西可以用 `tarjan` 算法。

否则说明存在环，为了解决这个矛盾，只好令该强连通分量里的点代表的 $x_i$ 都相等，随即找到对应的 $a_i$ 和 $c_i$，既然这一位必须得相等了，那就让 $a_i+1$ 和 $c_i+1$ 不相等，于是令 $a_i\leftarrow a_i+1,c_i\leftarrow c_i+1$，然后再重新建图判断。

需要注意的是，如果某次 $a_i,c_i$ 自增 $1$ 后使得 $c_i>d_i$，说明 $b_i-a_i+1\ge d_i-c_i+1$，即前者区间长度大于等于后者，且他们在后者那段有效前缀得满足完全相等，此时不可能使得前者字典序**严格**小于后者，故此时输出 `No`。

综上来看，本题不仅可以以两个区间为载体作出限制，更能直接钦定两个子序列作出限制，但显然前者更具有迷惑性。

最坏情况下时间复杂度为 $O(n(n+m))$，跑了 $n$ 次 `tarjan`。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define rep(i,l,r) for(int i=(l);i<=(r);++i)
#define per(i,l,r) for(int i=(r);i>=(l);--i)
#define pr pair<int,int>
#define fi first
#define se second
#define pb push_back
#define all(x) (x).begin(),(x).end()
#define sz(x) (x).size()
#define bg(x) (x).begin()
#define ed(x) (x).end()

#define N 2025
// #define int long long

int n,m,a[N],b[N],c[N],d[N],cnt;
int st[N],tp,fa[N],dfn[N],low[N];
bitset<N>in;
vector<int>e[N];
bool ex;

inline int ask(int k){
    if(fa[k]==k){
        return k;
    }
    return fa[k]=ask(fa[k]);
}

inline bool mg(int x,int y){
    int fx=ask(x),fy=ask(y);

    if(fx==fy){
        return 0;
    }

    fa[fx]=fy;

    return 1;
}

inline void clr(){
    tp=cnt=0;

    rep(i,1,n){
        e[i].clear();
        dfn[i]=low[i]=0;
        in[i]=0;
    }
}

inline void tarjan(int k){
    low[k]=dfn[k]=++cnt;
    st[++tp]=k;
    in[k]=1;
    
    for(int x:e[k]){
        if(!dfn[x]){
            tarjan(x);
            low[k]=min(low[k],low[x]);
        }
        else if(in[x]){
            low[k]=min(low[k],dfn[x]);
        }
    }

    if(low[k]!=dfn[k]){
        return;
    }

    if(st[tp]!=k){
        ex=1;
    }

    while(st[tp]!=k){
        in[st[tp]]=0;
        mg(k,st[tp]);

        tp--;
    }

    in[k]=0;
    tp--;
}

signed main(){
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);

    cin>>n>>m;

    rep(i,1,m){
        cin>>a[i]>>b[i]>>c[i]>>d[i];
    }

    rep(i,1,n){
        fa[i]=i;
    }

    rep(i,1,n){
        clr();

        rep(j,1,m){
            while(a[j]<=b[j]&&c[j]<=d[j]&&ask(a[j])==ask(c[j])){
                a[j]++;
                c[j]++;
            }

            if(c[j]>d[j]){
                cout<<"No";
                return 0;
            }

            if(a[j]<=b[j]){
                e[ask(a[j])].pb(ask(c[j]));
            }
        }

        ex=0;

        rep(j,1,n){
            if(!dfn[j]){
                tarjan(j);
            }
        }

        if(!ex){
            break;
        }
    }

    cout<<"Yes";

    return 0;
}
```

---

## 作者：_YangZJ_ (赞：1)

将限制建图，对于限制 $(a_i,b_i,c_i,d_i)$，我们连边 $a_i\rightarrow c_i$。容易发现如果此时图是一张拓扑图，那么直接按照拓扑序当做元素的值就是一组满足条件的解。

否则如果存在环的话，那么环上的点的权值都应该相等，不然就没有办法满足条件。

对环上的一条边 $(a_i,c_i)$ 来说，限制仍然没有被满足，应该继续考虑其下一位，加入一条新的边 $(a_i+1,c_i+1)$。

如果新加入的边 $c_i+1>d_i$ 那么就无解（意味着 $\text{lcp(}a_i,c_i)>d_i-c_i$，并且后面那个串长度更短），否则如果 $a_i+1>b_i$ 那这条边的限制就被满足了（前面那个串长度更短），不需要被加入。

重复以上过程，直到原图中不存在环，每条边被至多加入 $O(n)$ 次，每次的边数都是 $O(n)$ 的，用并查集维护哪些点权相等。复杂度 $O(n^2)$。

code

```cpp
#include<bits/stdc++.h>
using namespace std;

#define vc vector
#define pb emplace_back

const int N = 5e5+5, P = 1e9+7;

int n, m, fl, usd[N], st[N], fa[N];
int topf, idx, cnt, TIME, stk[N], dfn[N], low[N], ins[N], id[N];
vc<int> G[N];
struct edge { int a, b, c, d; }e[N];

inline int get(int x) { return x == fa[x] ? x : fa[x] = get(fa[x]); }

inline void tarjan(int x) {
	dfn[x] = low[x] = ++idx; stk[++topf] = x; ins[x] = 1; cnt = 0;
	for(auto y:G[x]) 
		if(!dfn[y]) tarjan(y), low[x] = min(low[x], low[y]);
		else if(ins[y]) low[x] = min(low[x], dfn[y]);
	if(dfn[x] == low[x]) {
		int z; ++cnt;
		do { z = stk[topf--]; fa[get(z)] = get(x); ins[z] = 0; id[z] = ++cnt; }while(x != z); 
	}
}

inline void doit() {
	topf = idx = 0;
	for(int i = 1; i <= n; i++) dfn[i] = id[i] = 0, G[i].clear();
	for(int i = 1; i <= m; i++) if(usd[i]) G[get(e[i].a + st[i])].pb(get(e[i].c + st[i]));
	for(int i = 1; i <= n; i++) if(get(i) == i && !dfn[i]) tarjan(i);
	for(int i = 1; i <= m; i++) if(usd[i]) {
		int x = e[i].a + st[i], y = e[i].c + st[i];
		while(x <= e[i].b && y <= e[i].d && get(x) == get(y)) 
			++st[i], ++x, ++y;
		if(y > e[i].d) return fl = 1, void();
		if(x > e[i].b) usd[i] = 0;
	}
}

signed main() {
	cin >> n >> m;
	for(int i = 1; i <= n; i++) fa[i] = i;
	for(int i = 1, a, b, c, d; i <= m; i++) {
		cin >> a >> b >> c >> d;
		e[i] = edge{a, b, c, d}; usd[i] = 1; st[i] = 0;
	}
	for(int i = 1; i <= n && !fl; i++) doit();
	puts(fl ? "No" : "Yes");
	return 0;
}
```



---

## 作者：int_dx (赞：0)

好题。

# 题意

[题目传送门](https://www.luogu.com.cn/problem/AT_arc165_d)

**题目大意：**

问是否存在长度为 $n$ 的序列构造，使得其满足 $m$ 个限制，第 $i$ 个限制要求该序列在字典序上 $[a_i,b_i]$ 的子段严格小于 $[c_i,d_i]$ 的子段。

# 思路

先思考最简单的，对于一个限制，如果 $a_i=c_i$，显然只需要比较 $b_i$ 和 $d_i$ 即可知道这个限制一定或不可能满足。因此以下先假设 $a_i\not =c_i$。

对于这种多元互相制约的题一个很经典的 trick 就是建出限制图，然后缩点出 DAG 再操作。

如果一个序列小于另一个序列，那么这两个序列一定有一段前缀（可以为空）相同，并在此之后立即出现两个元素的不相等。对于此题，我们想要尽可能满足条件，那么就要求这个不相等元素的位置尽可能靠前，这样后面的相应元素就不需要满足任何大小关系从而方便为其它限制服务。

设构造的序列为 $p$。那么，考虑对每个限制连一条 $a_i\to c_i$ 的边，表示初始时就要求 $p_{a_i}<p_{c_i}$。全部建完之后如果不存在 SCC 就必然有解了，构造方法就是将 $p$ 直接按分层顺序升序即可。

如果存在 SCC 呢？说明我们的一些要求形成了闭环，这显然是不行的。也就是说，想要满足条件必须使得这些点对应的 $p_i$ 值相等。但是对于第 $i$ 条限制原本的要求是严格小于，所以应该放宽条件，允许第一个数相等，只需要 $p_{a_i+1}<p_{c_i+1}$ 即可。

处理完毕我们发现，现在的情况相当于原本情况的一个子问题，所以直接按原有方法处理即可。什么时候是边界呢？类似开头所说的，如果一个限制的 $a_i$ 已经处理到了底，也就是 $b_i$，那么只需要看 $[c_i,d_i]$ 是否还有东西即可。如果有的话就可以自然满足，否则就是无解。

考虑到每次处理只需要 $a_i$ 和 $c_i$ 各加 $1$，最多处理 $n$ 次，每次跑 Tarjan 复杂度 $\mathcal{O(n+m)}$，总复杂度 $\mathcal{O(n(n+m))}$。

剩下就是细节了。处理 SCC 可以用并查集。详见代码。

# 代码

```cpp
#include<bits/stdc++.h>
// #define int long long
using namespace std;
typedef long long ll;
const int MAXN=2005,mod=998244353,inf=0x3f3f3f3f;
int n,m;
#define toi (e[i].to)
// #define roi (e[i^1].to)
#define fore(now,i) for(int i=head[now];i;i=e[i].next)
int cnt=0,head[MAXN];
struct EDGE{
    int to,next;
}e[MAXN];
inline void addedge(int u,int v){
    e[++cnt].to=v;
    e[cnt].next=head[u];
    head[u]=cnt;
}
int f[MAXN],dfn[MAXN],low[MAXN],dfncnt;
bool ins[MAXN],scc;
stack<int> st;
void init(){
    cnt=dfncnt=scc=0;
    memset(head,0,sizeof(head));
    memset(dfn,0,sizeof(dfn));
    memset(low,0,sizeof(low));
}
int findf(int x){
    return f[x]==x?x:f[x]=findf(f[x]);
}
inline void merge(int x,int y){
    if(findf(x)!=findf(y))
        f[f[x]]=f[y];
}
void dfs(int now){
    dfn[now]=low[now]=++dfncnt;
    ins[now]=1;
    st.push(now);
    fore(now,i){
        if(!dfn[toi]){
            dfs(toi);
            low[now]=min(low[now],low[toi]);
        }else if(ins[toi])
            low[now]=min(low[now],dfn[toi]);
    }
    if(low[now]==dfn[now]){
        for(int t;!st.empty();st.pop()){
            ins[t=st.top()]=0;
            merge(now,st.top());
            if(t!=now)
                scc=1;
            else
                break;
        }
        st.pop();
    }
}
int a[MAXN],b[MAXN],c[MAXN],d[MAXN];
signed main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin>>n>>m;
    for(int i=1;i<=n;i++)
        f[i]=i;
    for(int i=1;i<=m;i++)
        cin>>a[i]>>b[i]>>c[i]>>d[i];
    for(int i=1;i<=n;i++){
        init();
        for(int i=1;i<=m;i++){
            while(a[i]<=b[i]&&c[i]<=d[i]&&findf(a[i])==findf(c[i]))
                ++a[i],++c[i];
            if(c[i]>d[i]){
                cout<<"No";
                return 0;
            }
            if(a[i]<=b[i])
                addedge(findf(a[i]),findf(c[i]));
        }
        for(int i=1;i<=n;i++)
            if(!dfn[i])
                dfs(i);
        if(!scc)
            break;
    }
    cout<<"Yes";
    return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：0)

[Problem Link](https://www.luogu.com.cn/problem/AT_arc165_d)

**题目大意**

> 判断是否存在一个长度为 $n$ 的字符串 $S$，满足 $m$ 个限制 $(a,b,c,d)$，要求 $S[a,b]$ 字典序小于 $S[c,d]$。
>
> 数据范围：$n,m\le 2000$。

**思路分析**

从一些必要条件开始，对每个限制显然有 $S_a\le S_c$，那么考虑建出拓扑关系图，连边 $a\to c$。

在这张拓扑图上，如果有环，那么说明环上元素必须相等，因此可以把每个强联通分量都缩点。

注意到缩点后相当于确定若干 $S_a=S_c$，那么 $S[a,b]<S[c,d]$ 的必要条件就是 $S[a+1,b]<S[c+1,d]$，即找到最小的 $i$ 使得未钦定 $S_{a+i}=S_{c+i}$，连边 $a+i\to c+i$ 即可，容易发现这也是必要的。

如果某个时刻 $S[c,d]$ 已经变成 $S[a,b]$ 前缀说明无解，否则图中已经无环说明有解。

每次 Tarjan 缩点至少合并两个位置，因此合并至多进行 $n+1$ 轮。

时间复杂度 $\mathcal O(n(n+m))$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=2005;
int n,m,a[MAXN],b[MAXN],c[MAXN],d[MAXN],dsu[MAXN];
int find(int x) { return dsu[x]^x?dsu[x]=find(dsu[x]):x; }
vector <int> G[MAXN];
int dfn[MAXN],low[MAXN],dcnt,stk[MAXN],tp;
bool ins[MAXN],ok;
void tarjan(int u) {
	dfn[u]=low[u]=++dcnt,ins[stk[++tp]=u]=true;
	for(int v:G[u]) {
		if(!dfn[v]) tarjan(v),low[u]=min(low[u],low[v]);
		else if(ins[v]) low[u]=min(low[u],dfn[v]);
	}
	if(low[u]==dfn[u]) {
		ok&=stk[tp]==u;
		while(ins[u]) dsu[find(u)]=find(stk[tp]),ins[stk[tp--]]=false;
	}
}
signed main() {
	scanf("%d%d",&n,&m),iota(dsu+1,dsu+n+1,1);
	for(int i=1;i<=m;++i) scanf("%d%d%d%d",&a[i],&b[i],&c[i],&d[i]);
	while(true) {
		for(int i=1;i<=n;++i) G[i].clear(),dfn[i]=low[i]=0;
		for(int i=1;i<=m;++i) {
			while(a[i]<=b[i]&&c[i]<=d[i]&&find(a[i])==find(c[i])) ++a[i],++c[i];
			if(c[i]>d[i]) return puts("No"),0;
			if(a[i]<=b[i]) G[find(a[i])].push_back(find(c[i]));
		}
		ok=true,dcnt=0;
		for(int i=1;i<=n;++i) if(!dfn[i]) tarjan(i);
		if(ok) break;
	}
	puts("Yes");
	return 0;
}
```

---

## 作者：bluewindde (赞：0)

考虑将字典序的小于关系建图。

即对一个限制 $(A, B, C, D)$，假设前 $k$ 个位置已经相等，则连有向边 $A + k \rightarrow C + k$，表示 $A + k$ 处的值小于等于 $C + k$ 处的值。

如果 $A + k > B$，则这个限制已经被满足；如果 $C + k > D$，则 $[C, D]$ 是 $[A, B]$ 的一个前缀，无解。

这样建出来的图中如果有环，则说明环上所有位置的值相同；反之，没有环说明已经满足条件。

可以使用 Tarjan 找环，每次用并查集缩环为点，并继续迭代。

因为每次如果继续迭代，则点数至少减少 $1$，所以至多迭代 $n$ 次。时间复杂度 $O(n(n + m))$。

需要特判两个限制起点相同（即 $A = C$）的情况，此时只需比较两个子串的长度。

```cpp
#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

int n, m;
int a[2005], b[2005], c[2005], d[2005];
vector<int> vec[2005];

int f[2005];
int siz[2005];
static inline int find(int x) { return f[x] == x ? x : f[x] = find(f[x]); }
static inline void merge(int u, int v) {
    int uu = find(u), vv = find(v);
    if (uu == vv)
        return;
    if (siz[uu] < siz[vv])
        swap(uu, vv);
    f[vv] = uu;
    siz[uu] += siz[vv];
}

int dfn[2005], low[2005], dfn_clock;
int sta[2005], tail;
bool insta[2005];
int rt[2005], scc_cnt;
static inline void tarjan(int u) {
    dfn[u] = low[u] = ++dfn_clock;
    sta[++tail] = u;
    insta[u] = true;
    for (auto v : vec[u]) {
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (insta[v])
            low[u] = min(low[u], dfn[v]);
    }
    if (dfn[u] == low[u]) {
        ++scc_cnt;
        while (sta[tail] != u) {
            rt[sta[tail]] = u;
            insta[sta[tail]] = false;
            --tail;
        }
        rt[u] = u;
        insta[u] = false;
        --tail;
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        f[i] = i;
        siz[i] = 1;
    }
    for (int i = 1; i <= m; ++i) {
        cin >> a[i] >> b[i] >> c[i] >> d[i];
        if (a[i] == c[i]) { // 特判起点相同
            if (b[i] >= d[i]) {
                cout << "No" << endl;
                return 0;
            }
            --m;
            --i;
        }
    }
    int las = n;
    while (true) {
        dfn_clock = scc_cnt = 0;
        memset(dfn, 0, sizeof dfn);
        for (int i = 1; i <= n; ++i)
            vec[i].clear();
        for (int i = 1; i <= m; ++i) {
            while (a[i] <= b[i] && c[i] <= d[i] &&
                   find(a[i]) == find(c[i])) { // 匹配掉相等的位置
                ++a[i];
                ++c[i];
            }
            if (c[i] > d[i]) {
                cout << "No" << endl;
                return 0;
            }
            if (a[i] <= b[i])
                vec[find(a[i])].push_back(find(c[i]));
        }
        for (int i = 1; i <= n; ++i)
            if (f[i] == i && !dfn[i])
                tarjan(i);
        if (scc_cnt == las) { // 没有环，注意这里 scc_cnt 与 las 而不是 n 比较
            cout << "Yes" << endl;
            return 0;
        }
        for (int u = 1; u <= n; ++u)
            merge(u, rt[u]);
        las = scc_cnt;
    }
    return 0;
}
```

---

## 作者：Erine (赞：0)

看到字典序直接无脑考虑贪心。

首先贪高位。对于每条限制 $(A_i,B_i,C_i,D_i)$，我们先考虑让 $P_{A_i}<P_{c_i}$。显然建图，让 $A_i$ 向 $C_i$ 连一条有向边。在这张图中，每个点表示 $P$ 的一个位置，一条边表示一个从小到大的偏序关系。

这个时候如果这张图是 DAG 那么显然这个偏序关系是完全可以成立的，直接输出 `Yes` 即可；否则如果有一个环，或者说一个强连通分量，则说明这里面的所有点表示的位置上的数都相等。

那么这个强联通分量里面的边就得退而求其次，去考虑下一位，即 $A_i+1$ 向 $C_i+1$ 连边；同时我们要保证前面的相等关系仍成立。我们用并查集维护相等关系即可。这样依次推下去，不存在 $P$ 的条件为：设当前偏移为 $o$，则若到了某一位有 $C_i+o>D_i$ 则无解。原因是前面都满足相等，而到了这一位上无法再有小于的关系。

```cpp
#include <bits/stdc++.h>
#define int long long
#define fs first
#define sc second

using namespace std;
using pii = pair<int, int>;

const int maxn = 2e3 + 10;

struct limit {
	pii x, y;
	int o;
	limit() = default;
};

int n, m;
limit w[maxn];
vector<int> g[maxn];
vector<int> now;
int dfn[maxn], low[maxn], idx;
int col[maxn], cnt;
int vis[maxn];
stack<int> st;
int fa[maxn];

int find(int x) {
	return x == fa[x] ? x : fa[x] = find(fa[x]);
}

void merge(int u, int v) {
	u = find(u), v = find(v);
	if (u != v) fa[u] = v;
}

void init() {
	for (int i = 1; i <= n; i++) dfn[i] = low[i] = col[i] = vis[i] = 0;
	cnt = idx = 0;
	while (!st.empty()) st.pop();
}

void tarjan(int u) {
	dfn[u] = low[u] = ++idx;
	st.push(u), vis[u] = true;
	for (int v : g[u]) {
		if (!dfn[v]) {
			tarjan(v);
			low[u] = min(low[u], low[v]);
		} else if (vis[v]) {
			low[u] = min(low[u], dfn[v]);
		}
	}
	if (low[u] == dfn[u]) {
		int cur;
		++cnt;
		do {
			cur = st.top();
			vis[cur] = 0;
			col[cur] = cnt;
			st.pop();
		} while (cur != u);
	}
}

int lst[maxn];

signed main() {
	cin >> n >> m;
	for (int i = 1; i <= m; i++) cin >> w[i].x.fs >> w[i].x.sc >> w[i].y.fs >> w[i].y.sc;
	for (int i = 1; i <= n; i++) fa[i] = i;
	bool ans = 1;
	while (true) {
		for (int i = 1; i <= n; i++) g[i].clear();
		bool fl = 1;
		for (int i = 1; i <= m; i++) {
			while (w[i].x.fs + w[i].o <= w[i].x.sc && w[i].y.fs + w[i].o <= w[i].y.sc && find(w[i].x.fs + w[i].o) == find(w[i].y.fs + w[i].o)) w[i].o++;
			if (w[i].y.fs + w[i].o > w[i].y.sc) fl = 0, i = m;
			else if (w[i].x.fs + w[i].o > w[i].x.sc) continue;
			else g[find(w[i].x.fs + w[i].o)].push_back(find(w[i].y.fs + w[i].o));
		}
		if (!fl) {
			ans = 0;
			break;
		}
		init();
		for (int i = 1; i <= n; i++) if (find(i) == i && !dfn[i]) tarjan(i);
		for (int i = 1; i <= n; i++) lst[i] = 0;
		fl = 1;
		for (int i = 1; i <= n; i++) {
			if (find(i) != i) continue;
			if (!lst[col[i]]) lst[col[i]] = i;
			else merge(i, lst[col[i]]), fl = 0;
		}
		if (fl) break;
	}
	puts(ans ? "Yes" : "No");
	return 0;
}
/*
6 5
1 3 5 6
5 6 3 5
6 6 3 6
5 6 2 4
5 5 1 6
*/

```

---

## 作者：orz_z (赞：0)



考虑字典序的性质。

我们维护当前的 $a_i,c_i$ 表示判断 $a_i$ 是否 $<c_i$，连边。

`tarjan` 判环，如果是一个环，说明环上所有点都相等。

注意，我们连边是对两个点的环进行连边。

对于一个限制，如果当前的 $a_i,c_i$ 都在环上，即前缀都相等，那么 $a_i,c_i$ 都往下跳一位，说明我们判断下一位的关系。

最后跑完某个区间判断有无解即可。

如果 `tarjan` 时没有新的环合并，那么结束。

---

