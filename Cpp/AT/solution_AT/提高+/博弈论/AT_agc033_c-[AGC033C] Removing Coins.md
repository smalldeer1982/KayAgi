# [AGC033C] Removing Coins

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc033/tasks/agc033_c

高橋君と青木君は木を用いてゲームをすることにしました。 ゲームに用いる木は $ N $ 頂点からなり、各頂点には $ 1 $ から $ N $ の番号が割り振られています。 また、$ N-1 $ 本の辺のうち、 $ i $ 本目の辺は頂点 $ a_i $ と頂点 $ b_i $ を結んでいます。

ゲーム開始時、各頂点にはコインが一枚ずつ置いてあります。 高橋君と青木君は高橋君から始めて以下の操作を交互に行い、操作を行えなくなった方が負けになります。

- コインが置いてある頂点を一つ選び、その頂点 $ v $ に置いてあるコインをすべて取り除く。
- その後、木上に残っているコインをすべて、今置いてある頂点に隣接する頂点のうち $ v $ に一番近い頂点に移動させる。

つまり、木上にコインが残っていない状態で手番となった人の負けです。 二人が最適に行動したとき、どちらが勝つか求めてください。

## 说明/提示

### 制約

- $ 1\ ≦\ N\ ≦\ 2\ \times\ 10^5 $
- $ 1\ ≦\ a_i,\ b_i\ ≦\ N $
- $ a_i\ \neq\ b_i $
- 入力で与えられるグラフは木である。

### Sample Explanation 1

ゲームは例えば以下のように進行します。 - 高橋君が頂点 $ 1 $ からコインを取り除く。操作後は、頂点 $ 1 $ に一つ、頂点 $ 2 $ に一つコインがある。 - 青木君が頂点 $ 2 $ からコインを取り除く。操作後は、頂点 $ 2 $ に一つコインがある。 - 高橋君が頂点 $ 2 $ からコインを取り除く。操作後は、木上にコインは残っていない。 - 青木君は木上にコインがない状態で手番となってしまったので、負けとなる。

## 样例 #1

### 输入

```
3
1 2
2 3```

### 输出

```
First```

## 样例 #2

### 输入

```
6
1 2
2 3
2 4
4 6
5 6```

### 输出

```
Second```

## 样例 #3

### 输入

```
7
1 7
7 4
3 4
7 5
6 3
2 1```

### 输出

```
First```

# 题解

## 作者：Time_tears (赞：12)

考虑一次操作的本质，其实就是选择一个 $x$ ，删除除 $x$ 外的所有叶子。

那么现在我们一次操作后会导致直径减 $1$，或者减 $2$，对应不选/选直径端点的情况。

设 $f_i$表示直径为 $i$ 先手必胜还是后手必胜，为 $1$ 则先手必胜。

那么 $f_i=(!f_{i-1})||(!f_{i-2})$ ，边界为 $f_1=1,f_2=0$ 。

所以求出直径 $D$ 后输出 $f_D$ 即可。

```cpp
#include<bits/stdc++.h>
#define N 200005
using namespace std;
int n,f[N],d1[N],d2[N],h[N],cnt,mx;
struct node {int to,next;} e[N<<1];
void Addedge(int x,int y) {
	e[++cnt]=(node) {y,h[x]},h[x]=cnt;
	e[++cnt]=(node) {x,h[y]},h[y]=cnt;
}
inline int read() {
	int s=0,f=0;
	char ch=getchar();
	while(ch<48||ch>57)f|=(ch=='-'),ch=getchar();
	while(ch>47&&ch<58)s=(s<<1)+(s<<3)+(ch^48),ch=getchar();
	return f?-s:s;
}
void Dfs(int x,int fa) {
	for(int i=h[x],y; i; i=e[i].next) {
		if(y=e[i].to,y==fa)continue;
		if(Dfs(y,x),d1[y]+1>d1[x])d2[x]=d1[x],d1[x]=d1[y]+1;
		else if(d1[y]+1>d2[x])d2[x]=d1[y]+1;
	} if(d1[x]+d2[x]+1>mx)mx=d1[x]+d2[x]+1;
}
int main() {
	n=read(),f[1]=1,f[2]=0;for(int i=1; i<n; ++i)Addedge(read(),read());
	for(int i=3; i<=n; ++i)f[i]=(!f[i-1])||(!f[i-2]);Dfs(1,0),puts(f[mx]?"First":"Second");
	return 0;
}
```

---

## 作者：CYZZ (赞：7)

# [Removing Coins](https://www.luogu.com.cn/problem/AT_agc033_c)
## 题意
初始时树上 $n$ 个节点都有硬币。两个人轮流操作，每次操作可以拿走某个节点 $u$ 上的所有硬币（至少一个），其余每个节点上的硬币都往靠近 $u$ 的方向挪 $1$ 个点，谁先拿光谁赢。求先后手谁必胜。
## 思路
首先，一次操作本质上把除 $u$ 外的每个叶子节点向父亲移动了一格。相当于删除了当前除 $u$ 外的每个叶子节点。

我们再考虑删除 $u$ 会对一条两个端点都在叶子的链产生什么影响：

- 如果 $u$ 是链的端点，则这条链会整体向 $u$ 移动一格。链的长度减一。
- 如果 $u$ 不是链的端点，则这条链的两端会向父亲移动一格。链的长度减二。
- 如果这条链只剩 $2$ 个点了，则练的长度减 $1$。

不难看出，直径就是一条满足两端在叶子的链。最终的目标就是要让直径的长度变为 $0$。

于是题目转化为：求出树的直径 $d$，每次操作可以减一或减二，求必胜策略。经典的博弈问题。

- $d \equiv 0 \pmod 3$ 先手取 $1$，然后和后手拼 $3$，最后一定会剩下 $2$ 个点。根据上面的第三条性质，后手取 $1$，先手必胜。
- $d \equiv 1 \pmod 3$ 先手取 $2$，然后和后手拼 $3$。同上一种情况，先手必胜。
- $d \equiv 2 \pmod 3$ 后手与先手拼 $3$，最后剩下 $2$。先手取 $1$，后手必胜。

树的直径两遍 dfs 求出，最后分类讨论即可。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,tot,head[200005],dis[200005],maxx;
struct Edge
{
    int next,to;
}e[400005];
void add_edge(int u,int v)
{
    e[++tot].next=head[u];
    e[tot].to=v;
    head[u]=tot;
}
void dfs(int u,int fa)
{
    if(dis[u]>dis[maxx])
        maxx=u;//更新直径
    for(int i=head[u];i;i=e[i].next)
    {
        int v=e[i].to;
        if(v==fa)
            continue;
        dis[v]=dis[u]+1;
        dfs(v,u);
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<n;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        add_edge(x,y);
        add_edge(y,x);
    }
    dfs(1,0);//第一遍dfs
    memset(dis,0,sizeof dis);
    dfs(maxx,0);//第二遍dfs
    if((dis[maxx]%3+1)==2)//是点数而不是边数，所以要加一！！！
        printf("Second\n");
    else
        printf("First\n");
}
```
希望本篇题解能帮到大家！！！

---

## 作者：sunzh (赞：6)

我们考虑每次操作，若选在非叶子节点，外围一圈的叶子结点的硬币都向内移，若选在当前的叶子节点则除了这个节点以外的叶子结点内移

如果我们把内移转化到直径上，每次操作可以让直径长度$-1$或$-2$

谁先操作使直径长度为0获胜

因为如果选直径上的点，直径外的点一定在直径为0之前消失，我们先不考虑直径外的点

先手必胜的条件是直径长度$\mod 3$不等于$0$

因为只要先手取直径长度$\mod 3$，后手无论怎么取，先手都能取与之不同的使剩余数对3取模不变

反之亦然

只要必胜方坚持取直径上的点，直径外的点无法影响答案

但是若最后剩下2个点，我一次只能消掉1个

所以有以下策略

$len\mod 3 = 0$ ，先手先消1个，然后与对方拼3，最后剩2个，先手必胜

$len\mod 3 = 1$ ，若只有1个，直接消，否则先手先消2个，然后与对方拼3，最后剩2个，先手必胜

$len \mod 3 =2$，后手与先手拼3，最后剩2个，先手先拿，后手必胜

---

## 作者：Jerryfish (赞：4)

[更好的阅读体验](https://www.cnblogs.com/Raining-Hard/p/17464287.html)

看到这个题，是个博弈论，鄙人弱智，没见过树上的，于是想到在数列里的博弈论，又联想到树的特殊形式——链。

于是我们来讨论一下链的情况（对于没有硬币的点，我们就视为它被删掉了）：

![](https://cdn.luogu.com.cn/upload/image_hosting/3w9x1us0.png)

发现若是选择两端的点，顶点数会减一；若是选择中间的点，顶点数会减二。

现在我们站在链的角度来思考在树上选择的情况，一颗树可以看成一条链且在某些顶点上有分支的图。我们再来以这种方式来选点找找规律，发现树上的点删着删着最后总会变成一条链，且这条链是最长链的子链，于是我们把看这棵树的形式转换为其最长链（直径）且在某些顶点上有分支的图：

![](https://cdn.luogu.com.cn/upload/image_hosting/6bz8f950.png)

通过手玩这个例子后发现，我们若是选最长链两端的点，最长链顶点数会减一；若是选择非最长链两端的点，最长链顶点数会减二，其余的分支会因为持续的选点而被删完。

所以发现，在树上的问题被我们转化成了在链上的问题，妙哉！

讨论完了删点的变化情况，我们再来讨论一下必胜条件：若最长链上有 $i-1$ 和 $i-2$ 个点时均必胜，则最长链上有 $i$ 个点时必败，否则必胜，特殊的，若最长链上有 $1$ 个点时必胜，有 $2$ 个点时必败。

打表发现用树的最长链上点的个数 $\bmod 3$，若等于 $2$ 后手胜，否则先手胜。

Code：

```cpp
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 2e5 + 5;

int n, x, y, fir, sec;
int la[N], en[N << 1], ne[N << 1], idx;

void add(int x, int y) {
	en[ ++ idx] = y; 
	ne[idx] = la[x];
	la[x] = idx;
}

void dfs(int u, int f, int step) {
	for (int i = la[u]; i; i = ne[i]) {
		int v = en[i];
		if(v == f) continue;
		if(fir < step) fir = step, sec = v; dfs(v, u, step + 1);
	}
}

int main(){
	ios::sync_with_stdio(0);
	cin >> n;
	for (int i = 1; i < n; ++ i ) cin >> x >> y, add(x, y), add(y, x);
	dfs(1, 0, 1); dfs(sec, 0, 1); 
	if((fir + 1) % 3 == 2) cout << "Second";
	else cout << "First";
	return 0;
}
```

---

## 作者：_sh1kong_ (赞：2)

[In Luogu](https://www.luogu.com.cn/problem/AT_agc033_c)

比较简单的一道思维蓝。

### 思路
对于一条链，移除非端点，节点减少 $2$，移除端点，节点减少 $1$，直到节点为 $0$ 结束，这是显然的。

对于树上的情况，考虑树上的一条最长链，最终需要将最长链变为 $0$ 结束，即直径。

最终只剩两个点时，先手只能减少 $1$，必败。

我们求出树的直径节点数为 $d$，当 $d \bmod 3 = 2$ 时，后手必胜，否则先手必胜。可以由下面几个结论得出：

1. 当 $d \bmod 3 = 0$ 时，先手先减 $1$，后面不断与后手凑 $3$，最后一定会剩下两个，先手获胜。
2. 当 $d \bmod 3 = 1$ 时，先手先减 $2$，后面不断与后手凑 $3$，最后一定会剩下两个，先手获胜。
3. 当 $d \bmod 3 = 2$ 时，先手操作一次就会化为第一种或第二种情况，则后手获胜。

### 实现
求出树的直径后判断长度即可。

code:

```cpp
#include <bits/stdc++.h>

#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
#define int long long
#define re read()

const int N = 5e5 + 7, M = 1e8 + 7, K = 120, inf = 0x3f3f3f3f3f3f3f3fll;

using namespace std;

inline int read()
{
    int num = 0;char c;bool flag = false;
    while((c = getchar()) == ' ' || c == '\n' || c == '\r');
    if(c == '-') flag = true;else num = c - '0';
    while(isdigit(c = getchar())) num = num * 10 + c - '0';
    return (flag ? -1 : 1) * num;
}

int _;

int n;

int dis[N];

int h[N], nx[N], to[N], w[N], edges;

void add(int x, int y)
{
	nx[++ edges] = h[x], to[edges] = y, w[edges] = 1, h[x] = edges;
}

void dfs(int u, int fa)
{
	for (int i = h[u]; i; i = nx[i])
	{
		int j = to[i];
		if (j == fa) continue;
		dis[j] = max(dis[j], dis[u] + w[i]);
		dfs(j, u);
	}  
}

void solve()
{
	n = re;
	for (int i = 1; i < n; i ++ )
	{
		int x, y;
		x = re, y = re;
		add(x, y);
		add(y, x);
	}
	dfs(1, 1);
	int root = 0, res = 0;
	for (int i = 1; i <= n; i ++ )
	{
		if (res < dis[i]) res = dis[i], root = i;
	}
	memset(dis, 0, sizeof dis);
	dfs(root, root);
	res = 0;
	for (int i = 1; i <= n; i ++ ) res = max(res, dis[i]);
	if ((res % 3 + 1) == 2) cout << "Second\n";
	else cout << "First\n";
}

signed main()
{
    IOS;

	_ = 1;
	//_ = re;
	while (_ -- ) solve();
}
```

---

## 作者：Kobe303 (赞：1)

每次操作能让直径减 $1$ 或者减 $2$。

对应选的是否是直径的端点。

发现当直径为 $1$ 时，即只剩下两个点，那么此时操作的人必定会输。

那么先给出结论：如果直径长度减一为 $3$ 的倍数，那么后手必胜，否则先手必胜。

这是一个经典的小学奥数，就是说设先手为 $A$，后手为 $B$。

如果满足后手必胜，那么过程如下：

若 $A$ 让直径长度减 $2$，那么 $B$ 的应对就是让直径长度减 $1$。

反之若 $A$ 让直径长度减 $1$，那么 $B$ 的应对就是让直径长度减 $2$。

最后必定是 $A$ 操作的时候直径为 $1$。

否则过程如下：

若直径长度为 $3$ 的倍数，$A$ 先令直径长度减 $2$，否则令直径长度减 $1$。

这样就转化成了上面的过程。

[Code](https://atcoder.jp/contests/agc033/submissions/31279765)。

---

## 作者：李承轩 (赞：0)

**思路**

可以看出，每次对一个点 $u$ 操作一次，就相当于删除以 $u$ 为根的所有叶节点。

当然我们还是没有什么思路，我们可以想简单一点：在一条链上的情况。

+ 如果 $u$ 是链的端点：以 $u$ 为根节点的叶节点只有一个，所以链的长度减一。

+ 如果 $u$ 不是链的端点：以 $u$ 为根节点的叶节点有两个，所以链的长度减二。

而我们可以看出，在树上找到最长链，即树的直径。根据树的直径性质，如果我们操作直径上的点，旁边的分支也会被删完。

题目已被简化为，一个数 $n$，每次减 $1$ 或 $2$，谁减到 $0$，谁就赢了。~~（小学奥数题）~~ 

$n \equiv 2 \ (mod \ 3)$ 的时候后手有必胜策略，其他时候先手有必胜策略。

特别的，我们树的直径求的是点不是边，所以注意要 $+1$。

**代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int n,maxx,dis[N];
int head[N],to[N*2],nxt[N*2],idx;
void add(int x,int y){to[++idx]=y,nxt[idx]=head[x],head[x]=idx;}
void dfs(int x,int fa)
{
    if(dis[x]>dis[maxx])maxx=x;
    for(int i=head[x];i;i=nxt[i])
    {
        if(to[i]==fa)continue;
        dis[to[i]]=dis[x]+1;
        dfs(to[i],x);
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=1,x,y;i<n;i++)
    {
        scanf("%d%d",&x,&y);
        add(x,y),add(y,x);
    }
    dfs(1,0);
    memset(dis,0,sizeof dis);
    dfs(maxx,0);
    if(dis[maxx]%3+1==2)printf("Second");
    else printf("First");
}
```

---

## 作者：orpg (赞：0)

## [题目传说门](https://www.luogu.com.cn/problem/AT_agc033_c)
### 题目梗概
给定一棵 $n$ 个节点的树，每个节点都有一枚硬币。每次可以选择树上任意一个点 $x$，将 $x$ 上的硬币移除，其他的点就往相邻且离 $x$ 近的点移动。谁无法操作谁输。问先手赢还是后手赢。
### 题目解析
不难发现，其实我们发现把树的直径删掉下一个人就无法操作了。而我们每次可以在树上删一个点，其实相当于在树直径上删 $1$ 或 $2$ 个点。

所以设树的直径 $d$。当 $d$ 除以 $3$ 的余数为 $2$ 时后手必胜，否则先手必胜。
### 上代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+5;
int n,tot;
int head[maxn<<1];
bool vis[maxn];
int d1[maxn],d2[maxn],ans;
struct node{
    int to,nxt;
}ed[maxn<<1];
void add(int u,int v){
    ed[++tot].to=v;
    ed[tot].nxt=head[u];
    head[u]=tot;
}
void dfs(int u){
	vis[u]=true;
	for(int i=head[u];i;i=ed[i].nxt){
		int to=ed[i].to;
		if(vis[to]==true) continue;
		dfs(to);
		if(d1[to]+1>d1[u]){
			d2[u]=d1[u];
			d1[u]=d1[to]+1;
		}
		else if(d1[to]+1>d2[u]){
			d2[u]=d1[to]+1;
		}
	}
	ans=max(ans,d1[u]+d2[u]);
}
main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n;
    for(int u,v,i=1;i<n;i++){
        cin>>u>>v;
        add(u,v);add(v,u);
    }
    dfs(1);
    ans++;//求直径
    if(ans%3==2) cout<<"Second\n";
    else cout<<"First\n";
    return 0;
}
```


---

## 作者：wol_qwq (赞：0)

一道有些思维的题目。

+ 考虑一条链的情况，移动非端点，节点减少 $2$，移除端点，节点减少 $1$，直到节点 $0$ 结束。

+ 对于树上的情况，考虑树上的一条最长链，最终需要将最长链变为 $0$ 结束，即直径。

+ 删除叶子节点，链上节点减少 $1$，删除非叶子节点，链上的节点减少 $2$。

+ 最终只剩两个点的时候，只能减少 $1$，此时先手必败。

+ 设树的直径的节点数为 $d$，如果 $d \bmod 3 = 2$，后手必胜，否则先手必胜。

+ 所以最后我们只需要求出直径然后判断其长度就行了。

推断原理：

1. 当 $d \bmod 3 = 0$ 时，先手先减 $1$，后面与后手凑 $3$，最后一定会剩下两个，先手获胜。

2. 当 $d \bmod 3 = 1$ 同理，先手直接减 $2$，后面与后手凑 $3$，最后一定会剩下两个，先手获胜。

3. 当 $d \bmod 3 = 2$，先手操作一次就会转化为第一种情况或第二种情况，故后手获胜。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+5;
void read(int &xx){
    register char ch=getchar();
    register int ans=0;
    char t=0;
    while(!isdigit(ch))t|=ch=='-',ch=getchar/*_unlocked*/();
    while(isdigit(ch))ans=(ans<<3)+(ans<<1)+(ch^48),ch=getchar/*_unlocked*/();
    xx=t?-ans:ans;
    return ;
}
void write(int x){
    if(x<0){
        putchar('-');
        x*=-1;
    }
    char wr[18];
    int cnt=1;
    if(x==0){
        putchar('0');
        putchar('\n');
        return ;
    }
    while(x){
        wr[cnt++]=x%10+'0';
        x/=10;
    }
    for(cnt--;cnt;cnt--){
        putchar(wr[cnt]);
    }
    putchar('\n');
    return;
}
struct Edge{
	int to,w,nxt;
}e[maxn];
int head[maxn],cnt,dis[maxn],n;
void add(int u,int v,int w){
	e[++cnt].to=v;
	e[cnt].nxt=head[u];
	e[cnt].w=w;
	head[u]=cnt;
}
int bfs(int x) {
    memset(dis,0x3f,sizeof(dis));
    dis[x]=0;
    queue<int>q;
    q.push(x);
    int res=1;
    while(!q.empty()) {
        int x=q.front();
        q.pop();
        for(int i=head[x];i;i=e[i].nxt){
            //write(e[i].to);
            if (dis[e[i].to]!=dis[maxn-1])continue;
            dis[e[i].to]=dis[x]+e[i].w;
            if(dis[e[i].to]>dis[res])res=e[i].to;
            q.push(e[i].to);
        }
    }
    return res;
}
int main(){
	read(n);
	for(int i=1;i<n;i++){
		int x,y;
		read(x);
        read(y);
		add(x,y,1);
		add(y,x,1);
	}
    if((dis[bfs(bfs(1))]+1)%3==2)puts("Second");
    else puts("First");
    return 0;
}

```


---

## 作者：ljlawa (赞：0)

[题目链接](https://www.luogu.com.cn/problem/AT_agc033_c)

首先来理解题意，你可以选一个点然后将其清零，然后所有节点向他的方向跳，这导致他会重新获得点数，大部分节点都会先清零，然后获得跳过来的点数，在树上叶子结点在跳跃之后是获得不了点数的，我们可以定义其消失。但如果你选择的点是叶子节点那么该叶子结点不会消失。

我们先拿一条链举例，如果我选择了链的端点，那么链的另一端就会消失，如果我们选的点在链中间，那么链的两端都会消失。以上操作可以归结为链长减一或减二。

再放到树上，经过很多轮操作之后，大部分节点都会消失，但到最后一定会剩下一条“前最长链的缩影”也就是说这条最长链会支撑我们操作到最后。所以我们可以把这棵树缩小至这个最长链。

我们可以发现，当剩余长度不为三的倍数时，先手才有机会获胜。所以先手会去破坏三的倍数的情况。

当长度模三等于 $0$ 时，先手先减一，然后两人周旋，最后一定会剩下两个，后手只能减一。先手获胜。模三等于 $1$ 同理。

然而长度模三等于 $2$ 时，无论先手怎么取，后手都能让长度保持在三的倍数，先手必败。

所以最后我们只需要求出一条最长链然后判断其长度就行了。

开始写的是树剖维护（然后因为写假T了），后来发现只是两次深搜的事。

## Code：

```cpp
#include <bits/stdc++.h>
 
#define PII pair<int, int>

using namespace std;

const int N = 2e5 + 5;

int n;
int h[N], to[N << 1], ne[N << 1], tot;
int cnt[N], idx;
void add(int u, int v)
{
	to[++ tot] = v;
	ne[tot] = h[u];
	h[u] = tot;
}

PII dfs (int x, int fa)
{
	int ans = 1, id = -1;
	for (int i = h[x]; i; i = ne[i])
		if (to[i] != fa)
		{
			PII y = dfs(to[i], x);
			if (y.first + 1 > ans)
			{
				ans = y.first + 1;
				id = y.second;
			}
		}
	if (ans == 1) id = x;
	return make_pair(ans, id);
}

int main()
{
	cin >> n;
	for (int i = 1; i < n; i ++)
	{
		int u, v;
		cin >> u >> v;
		add (u, v);
		add (v, u);
	}
	int id = dfs (1, 0).second;
	int ans = dfs (id, 0).first;
	if (ans % 3 == 2) cout << "Second";
	else cout << "First";
	return 0;
}
```

---

## 作者：irris (赞：0)

考虑一次操作其实相当于删除除了钦定点以外的叶子，如果这棵树只有一个节点就输了。

我们考虑一个树的结构**其实是困难的**。但是考虑到经过若干次操作后，一些点总会并到另外一些点上，而**那些最后被删掉的点，其实是一条直径**，这启发我们维护树的直径。

具体地，令树的直径上有 $n$ 个节点。一次操作可以让 $n \leftarrow n - 2$（若 $n \gt 2$，选择非直径端点节点）或 $n \leftarrow n - 1$（选择直径端点）。若操作后 $n = 1$ 则对方输，其实就是操作前 $n = 2$ 必败。

这是经典的博弈论问题，下面直接给出结论：

+ $n \bmod 3 = 2$。后手始终保证 $n \bmod 3 = 2$（先手减 $1$，后手减 $2$，反之亦然），那么先手到了 $n = 2$ 时必败。
+ $n \bmod 3 \neq 2$。先手第一步让 $n \bmod 3$ 变为 $2$，先手必胜。

时间复杂度 $\mathcal O(N)$。

---

