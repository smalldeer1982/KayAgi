# Tree Compass

## 题目描述

You are given a tree with $ n $ vertices numbered $ 1, 2, \ldots, n $ . Initially, all vertices are colored white.

You can perform the following two-step operation:

1. Choose a vertex $ v $ ( $ 1 \leq v \leq n $ ) and a distance $ d $ ( $ 0 \leq d \leq n-1 $ ).
2. For all vertices $ u $ ( $ 1 \leq u \leq n $ ) such that $ \text{dist}^\dagger(u,v)=d $ , color $ u $ black.

Construct a sequence of operations to color all the nodes in the tree black using the minimum possible number of operations. It can be proven that it is always possible to do so using at most $ n $ operations.

 $ ^\dagger $ $ \text{dist}(x, y) $ denotes the number of edges on the (unique) simple path between vertices $ x $ and $ y $ on the tree.

## 说明/提示

In the first test case, there is only one possible operation, and performing it gives us a valid answer.

In the second test case, the first operation colors vertex $ 2 $ black, and the second operation colors vertex $ 1 $ black. It can be shown that it is impossible to color both vertices black in one operation, so the minimum number of operations needed is $ 2 $ . Another possible solution is to use the $ 2 $ operations: $ (u, r) = (1, 0) $ and $ (u, r) = (2, 0) $ .

In the third test case, the first operation colors vertices $ 2 $ , $ 3 $ and $ 4 $ black, and the second operation colors vertex $ 1 $ black. Again, it can be shown that it is impossible to color all vertices black in $ 1 $ operation, so the minimum number of operations needed is $ 2 $ .

In the fourth test case, the first operation colors vertices $ 4 $ , $ 1 $ and $ 7 $ black, the second operation colors vertices $ 2 $ , $ 5 $ and $ 6 $ black while the third operation colors vertices $ 3 $ and $ 7 $ black. Notice that it is allowed to color vertex $ 7 $ black twice.

Thus, each node was marked at least once, with node $ 7 $ marked twice. It can be shown that it is impossible to color all vertices black in fewer than $ 3 $ moves.

## 样例 #1

### 输入

```
4
1
2
1 2
4
1 2
1 3
1 4
7
2 7
3 2
6 4
5 7
1 6
6 7```

### 输出

```
1
1 0
2
1 1
2 1
2
1 1
2 1
3
6 1
7 1
2 1```

# 题解

## 作者：wosile (赞：4)

首先我们大胆猜测存在某种操作次数最少构造方案使得所有操作 $(v,d)$ 都满足 $v=v_0$。

如果真的存在这样的 $v_0$，需要的操作次数就是 $1+\max\limits_{i=1}^n\text{dist}(i,v_0)$。我们取直径的中点（之一）即可满足所有点的距离最大值最小。

于是你开心的交了一发并 `Wrong Answer on Pretest 2`。

想一下这个结论哪里有问题。

显然，我们考虑直径这一条路径，一次操作最多只能把两个在直径上的点涂黑，而在直径点数 $m$ 是奇数的时候，理论最少操作次数和我们的实际操作次数都是 $\frac{m+1}2$，看起来没什么问题。

进一步地，我们可以证明一次操作在直径上涂黑的两个点 $u_1,u_2$ 一定满足 $\text{dist}(u_1,u_2)$ 是偶数。~~读者自证不难。~~ 

如果把直径上的点黑白间隔染色，那么每次操作涂黑的点一定是同色的。对于 $m$ 是偶数的情况，会有 $\frac{m}2$ 个黑点和 $\frac{m}2$ 个白点。

在 $m\equiv2\pmod 4$ 的时候，黑点和白点各有奇数个，也就是至少需要 $\frac{m}{2}+1$ 次操作，此时我们也达到了理论最少操作次数。

最后剩下 $m\equiv0\pmod 4$ 的情况，容易发现我们的做法在这种情况下挂掉了，比如我们有一个长度为 $4$ 的链：

```
4
1 2
2 3
3 4
```

我们取中点 $2$，需要三次操作。但是实际上只需要两次操作：

```
2
2 1
3 1
```

就可以了。

我们对于这种情况稍微修改一下构造，对于直径的两个中点，对所有的 $d=2k-1< \frac{m}{2}$ 操作一次，就可以在涂黑整棵树的同时达到最少操作次数 $\frac{m}{2}$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int Tc;
int n;
vector<int>T[2005];
int dis[2005],from[2005];
void dfs(int x,int fa){
	from[x]=fa;
	for(int v:T[x])if(v!=fa){
		dis[v]=dis[x]+1;
		dfs(v,x);
	}
}
int main(){
	scanf("%d",&Tc);
	dis[0]=-1;
	while(Tc--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++)T[i].clear();
		for(int i=1;i<n;i++){
			int u,v;
			scanf("%d%d",&u,&v);
			T[u].push_back(v);
			T[v].push_back(u);
		}
		dis[1]=0;
		dfs(1,0);
		int mx=0;
		for(int i=1;i<=n;i++)if(dis[i]>dis[mx])mx=i;
		dis[mx]=0;
		dfs(mx,0);
		int st=mx;
		mx=0;
		for(int i=1;i<=n;i++)if(dis[i]>dis[mx])mx=i;
		int tmp=dis[mx]/2;
		int len=(dis[mx]+1)/2;
		if(dis[mx]%4==3){
			// m%4==0 的特殊情况。 
			printf("%d\n",(dis[mx]+1)/2);
			while(tmp--)mx=from[mx];
			for(int i=1;i<=len;i+=2)printf("%d %d\n",mx,i);
			mx=from[mx];
			for(int i=1;i<=len;i+=2)printf("%d %d\n",mx,i);
		}
		else{
			while(tmp--)mx=from[mx];
			printf("%d\n",len+1);
			for(int i=0;i<=len;i++)printf("%d %d\n",mx,i);
		}
	}
	return 0;
	//quod erat demonstrandum
}

```

---

## 作者：EuphoricStar (赞：2)

发现对于一条链，一次操作最多能染黑这条链上的 $2$ 个点。

所以我们把直径拎出来，设直径长度为 $d$。

考虑一条长度为 $d$ 的链至少要多少次能全染黑。

- 若 $d$ 为奇数，显然从直径中点 $u$ 开始做 $(u, 0), (u, 1), \ldots, (u, \frac{d - 1}{2})$ 即可。这样操作次数已经顶到下界了，而且发现由直径的性质，这样能把整棵树都全部染黑。
- 若 $d$ 为偶数，发现 $d = 2$ 和 $d = 4$ 时都需要 $2$ 次。考虑若 $d \bmod 4 = 0$，可以找到直径的中心边 $(x, y)$，依次做 $(x, 1), (y, 1), (x, 3), (y, 3), \ldots, (x, \frac{d}{2} - 1), (y, \frac{d}{2} - 1)$ 即可，只需 $\frac{d}{2}$ 次操作。若 $d \bmod 4 = 2$，只能做 $(x, 0), (x, 1), \ldots, (x, \frac{d}{2})$，需要 $\frac{d}{2} + 1$ 次操作。

找直径即可。时间复杂度 $O(n)$，开 $2 \times 10^3$ 是因为 checker 要 $O(n^2)$。

[code](https://codeforces.com/problemset/submission/1943/251868497)

---

## 作者：MaxBlazeResFire (赞：2)

考虑一个比较 trivial 的思路：找到直径中点，以这个点为根操作树的深度次。我们发现长度为 $4$ 的链就可以 hack 掉这个做法。

然后我们发现假设我们对这棵树进行黑白染色，那么我们可以得到两个完全独立的问题（一次操作只有可能染一种颜色的点）。考虑分别求出黑点和白点点集的直径中点（黑点点集的直径中点可能是一个白点，白点点集的直径中点可能是一个黑点），然后以直径中点为根，操作深度次即可，容易证明这是一个下界。

复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long
#define MAXN 400005

int n,col[MAXN];
vector<int> E[MAXN];

int dep1[MAXN],dep2[MAXN],fa1[MAXN],fa2[MAXN];
int vis[MAXN];

vector< pair<int,int> > Ans;

void dfs( int x , int fa ){ for( int v : E[x] ) if( v != fa ) col[v] = col[x] ^ 1,dfs( v , x ); }

void buildblack( int x , int fa , int rt ){
	for( int v : E[x] ){
		if( v == fa ) continue;
		if( col[v] ) dep1[v] = dep1[rt] + 1,fa1[v] = rt;
		buildblack( v , x , col[x] ? x : rt );
	}
}

void buildwhite( int x , int fa , int rt ){
	for( int v : E[x] ){
		if( v == fa ) continue;
		if( !col[v] ) dep2[v] = dep2[rt] + 1,fa2[v] = rt;
		buildwhite( v , x , !col[x] ? x : rt );
	}
}

inline void solve(){
	scanf("%lld",&n);
	if( n == 1 ){ printf("1\n1 0\n"); return; }
	for( int i = 1 ; i < n ; i ++ ){
		int u,v; scanf("%lld%lld",&u,&v);
		E[u].emplace_back( v ),E[v].emplace_back( u );
	} col[1] = 1,dfs( 1 , 0 );
	int S1 = 0,T1 = 0,S2 = 0,T2 = 0;
	for( int i = 1 ; i <= n ; i ++ ){
		if( col[i] ){
			for( int i = 1 ; i <= n ; i ++ ) dep1[i] = fa1[i] = 0;
			dep1[i] = 1,buildblack( i , 0 , i );
			for( int i = 1 ; i <= n ; i ++ ) if( col[i] && dep1[i] > dep1[S1] ) S1 = i;
			for( int i = 1 ; i <= n ; i ++ ) dep1[i] = fa1[i] = 0;
			dep1[S1] = 1,buildblack( S1 , 0 , S1 );
			for( int i = 1 ; i <= n ; i ++ ) if( col[i] && dep1[i] > dep1[T1] ) T1 = i;
			break;
		}
	}
	for( int i = 1 ; i <= n ; i ++ ){
		if( !col[i] ){
			for( int i = 1 ; i <= n ; i ++ ) dep2[i] = fa2[i] = 0;
			dep2[i] = 1,buildwhite( i , 0 , i );
			for( int i = 1 ; i <= n ; i ++ ) if( !col[i] && dep2[i] > dep2[S2] ) S2 = i;
			for( int i = 1 ; i <= n ; i ++ ) dep2[i] = fa2[i] = 0;
			dep2[S2] = 1,buildwhite( S2 , 0 , S2 );
			for( int i = 1 ; i <= n ; i ++ ) if( !col[i] && dep2[i] > dep2[T2] ) T2 = i;
			break;
		}
	}
	int len1 = dep1[T1],len2 = dep2[T2];
	int l1 = T1,r1 = 0,l2 = T2,r2 = 0;
	for( int i = 1 ; i <= ( len1 - 1 ) / 2 ; i ++ ) l1 = fa1[l1]; r1 = fa1[l1];
	for( int i = 1 ; i <= ( len2 - 1 ) / 2 ; i ++ ) l2 = fa2[l2]; r2 = fa2[l2];
	int aim1 = 0,aim2 = 0;
	for( int i = 1 ; i <= n ; i ++ ) vis[i] = 0;
	for( int v : E[l1] ) vis[v] = 1;
	for( int v : E[r1] ) if( vis[v] ){ aim1 = v; break; }
	if( !aim1 ) for( int v : E[l1] ){ aim1 = v; break; }
	for( int i = 1 ; i <= n ; i ++ ) vis[i] = 0;
	for( int v : E[l2] ) vis[v] = 1;
	for( int v : E[r2] ) if( vis[v] ){ aim2 = v; break; }
	if( !aim2 ) for( int v : E[l2] ){ aim2 = v; break; }
	Ans.clear();
	for( int i = 1 ; i <= ( len1 + 1 ) / 2 ; i ++ ) Ans.emplace_back( make_pair( aim1 , i * 2 - 1 ) );
	for( int i = 1 ; i <= ( len2 + 1 ) / 2 ; i ++ ) Ans.emplace_back( make_pair( aim2 , i * 2 - 1 ) );
	printf("%lld\n",(int)Ans.size());
	for( pair<int,int> ele : Ans ) printf("%lld %lld\n",ele.first,ele.second);
	for( int i = 1 ; i <= n ; i ++ ) col[i] = dep1[i] = dep2[i] = fa1[i] = fa2[i] = vis[i] = 0;
	for( int i = 1 ; i <= n ; i ++ ) E[i].clear();
}

signed main(){
	int testcase; scanf("%lld",&testcase);
	while( testcase -- ) solve();
	return 0;
}
```

---

## 作者：xlh_01 (赞：1)

[洛谷题目](https://www.luogu.com.cn/problem/CF1943C)
[CF题目](https://codeforces.com/problemset/problem/1943/C)

---

### 题意

给出一棵 $n$ 个点的树，初始时所有的点都是白色的，每次你可以选择一个点 $x$ 和一个非负整数半径 $r$，将树上所有与 $x$ 距离为 $r$ 的点染成黑色，求把所有点染成黑色的最少操作次数，并给出一组方案。

范围：$1 \le n \le 2 \times 10^{3} $。

---

### Solution

首先大胆猜测 $x$ 可能为树的中心。

证明：设树的直径长度为 $l$。对于一条直径上的点，每次至多染两个点。

- 若 $l$ 为奇数，取中心操作，则对直径的操作次数显然为 $\lceil \frac{l}{2} \rceil$，达到最小。
- 若 $l$ 为偶数，重复对两个中心操作。继续分类讨论，发现 $l \bmod 4 = 0$ 时操作次数为 $\frac{l}{2}$，$l \bmod 4 = 2$ 时操作次数为 $\frac{l}{2}+1$，也达到最小。

由此可以证明对于直径树的中心操作的次数最少，再根据直径为树中最长的链可得树的中心即为操作的点 $x$。由此得证。

时间复杂度：$O(n)$。


---


### Code


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e3+5;
struct node{int to,next;}edge[N<<1];
int n,head[N],cnt,len,ans,res[N],dis[N],num;bool vis[N];
inline void add(const int u,const int v){//加边
    edge[++cnt].next=head[u];
    edge[cnt].to=v;
    head[u]=cnt;
}
namespace rw{//快读快写
    inline int read(){
        int tot=0,t=1;char ch=getchar();
        while(ch<'0'||ch>'9'){if(ch=='-') t=-1;ch=getchar();}
        while(ch>='0'&&ch<='9'){tot=tot*10+ch-'0';ch=getchar();}
        return tot*t;
    }
    inline void write(int x){
        if(x<0) putchar('-'),x=-x;
        static int sta[35];int top=0;
        do{sta[top++]=x%10,x/=10;}while(x);
        while(top) putchar(sta[--top]+'0');
    }
    inline void print(const int x,const char ch){return (write(x),putchar(ch)),void(0);}
}using namespace rw;
inline void dfs(const int u,const int dep){
    if(vis[u]) return;vis[u]=1;
    if(dep>len) ans=u,len=dep;//len即为直径的长度
    for(int i=head[u];i;i=edge[i].next){
        int v=edge[i].to;
        dfs(v,dep+1);
    }
}
inline void dfs2(const int u,const int dep){
    if(dis[u]) return;dis[u]=dep;
    for(int i=head[u];i;i=edge[i].next){
        int v=edge[i].to;
        dfs2(v,dep+1);
    }
}
inline void dfs3(const int u){
    res[++num]=u;//记录答案
    for(int i=head[u];i;i=edge[i].next){
        int v=edge[i].to;
        if(dis[v]==dis[u]-1) return dfs3(v),void(0);
    }
}
inline void outit(){//输出答案
    if(len%4==0){
        print(len>>1,'\n');
        for(int i=1;i<<1<=len;i+=2) cout<<res[len>>1]<<" "<<i<<'\n'<<res[(len>>1)+1]<<" "<<i<<'\n';
    }
    else if(len%4==2){
        print((len>>1)+1,'\n');
        for(int i=1;i<<1<=len;i+=2) cout<<res[len>>1]<<" "<<i<<'\n'<<res[(len>>1)+1]<<" "<<i<<'\n';
    }
    else{
        print((len>>1)+1,'\n');
        for(int i=0;i<<1<len;i++) cout<<res[(len>>1)+1]<<" "<<i<<'\n';
    }
}
//初始化
inline void init(){for(int i=1;i<=n;i++) head[i]=0,dis[i]=0;cnt=0;num=0;}
inline void init2(){for(int i=1;i<=n;++i) vis[i]=0;len=0;}
inline void solve(){
    n=read();init();
    for(int i=1;i<n;i++){
        int u=read(),v=read();
        add(u,v),add(v,u);
    }
    init2();dfs(1,1);init2();
    int s=ans;dfs(s,1);//找出直径
	int t=ans;dfs2(t,1);
	dfs3(s);outit();
}
signed main(){
    int T=read();
    while(T--) solve();
    return 0;
}
```

---

## 作者：honglan0301 (赞：1)

## 分析

注意到，对任意一条链来说，每次操作至多标记其中的两个点。于是记直径点数为 $len$，操作次数有平凡下界 $\lceil \frac{len}{2}\rceil$。接下来分讨构造：

- $len\equiv 1 \pmod 2$ 时：

	取出直径中点 $u$，进行操作 $(u,0),(u,1),\dots,(u,\frac{len-1}{2})$ 即可达到理论最优（$\lceil \frac{len}{2}\rceil$ 次）。

- $len\equiv 0\pmod 2$ 时：

	此时直径中点在边上，取出该边 $(u,v)$，然后继续分讨。

	1. 若 $len\equiv 0\pmod 4$，则进行操作 $(u,1),(v,1),(u,3),(v,3)\dots,(u,\frac{len-2}{2}),(v,\frac{len-2}{2})$ 即可达到理论最优（$\lceil \frac{len}{2}\rceil$ 次）。

	2. 否则 $len\equiv 2\pmod 4$，此时可以证明无法构造出 $\frac{len}{2}$ 次操作的方案（见下文），那么操作 $(u,0),(u,1),\dots,(u,\frac{len}{2})$ 即最优（$\lceil \frac{len}{2}\rceil+1$ 次）。
    
   		*证明：记直径一端点为 $p$。显然两个点 $x,y$ 可以在同一次操作中被标记需要满足 $\text{dis}(p,x)+\text{dis}(p,y)\equiv \text{dis}(x,y)\equiv 0\pmod 2$，而 $\sum \text{dis}(p,i)\equiv 1\pmod 2$。故不能把直径上的点两两配对使得每对点都能在一次操作中被标记，即没有 $\frac{len}{2}$ 次操作的方案。
    
## 代码

[赛时代码](https://codeforces.com/contest/1943/submission/251734840)。

---

## 作者：Priestess_SLG (赞：0)

首先考虑一条长度为 $n$ 的链上的情况。

对于 $2\nmid n$ 的情况：链上存在编号为 $\frac{n+1}2$ 的中点，直接以这个点为中心，向两边扩展长度染色即可，需要耗费 $\frac {n+1}2$ 次操作。

对于 $2\mid n$ 的情况：此时链上没有中点，因此需要继续分类讨论：

+ 若 $4\nmid n$ ，则最优解只能是找到“中边”连接的两个编号分别为 $\frac n2$ 和 $\frac n2+1$ 的点，然后以其中任意一个点为中心向左右两侧扩展，需要花费 $\frac n2+1$ 次操作。
+ 若 $4\mid n$ ，则找到“中边”连接的两个编号分别为 $\frac n2$ 和 $\frac n2+1$ 的点，然后以这两个点为中心，分别向序列两边扩展奇数长度的结点，需要花费 $\frac n2$ 次操作。将序列奇偶染色可以证明必然能够用这个方法染色所有序列上的点。

然后考虑将其扩展到树上。考虑下面一个结论：

+ 对于树 $T$ 的任意一条直径 $u\leftrightarrow v$ ，树上任意一点 $i$ 都不存在距离比 $i$ 到 $u$ 或者 $i$ 到 $v$ 更远的结点。

因此只需要在树上任意找出一条直径，然后对直径做上述对链的染色操作即可解决问题，时间复杂度为 $O(n)$ 。

```cpp
#pragma GCC optimize(3, "Ofast", "inline")
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2010;
vector<int> adj[N];
int dis[N], depth[N], parent[N];
void dfs(int u, int fa) {
    depth[u] = depth[fa] + 1;
    parent[u] = fa;
    for (int &v : adj[u])
        if (v != fa) {
            dfs(v, u);
            depth[u] = depth[fa] + 1;
        }
}
signed main() {
    cin.tie(0)->sync_with_stdio(false);
    cout << fixed << setprecision(15);
    cerr << fixed << setprecision(5);
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        if (n == 1) cout << "1\n1 0\n";
        else {
            for (int i = 1; i <= n; ++i) adj[i].clear();
            for (int i = 1; i < n; ++i) {
                int x, y;
                cin >> x >> y;
                adj[x].emplace_back(y);
                adj[y].emplace_back(x);
            }
            for (int i = 1; i <= n; ++i) dis[i] = 1e18;
            dis[1] = 0;
            queue<int> q;
            q.emplace(1);
            while (q.size()) {
                int t = q.front();
                q.pop();
                for (int &g : adj[t]) {
                    if (dis[g] > dis[t] + 1) {
                        dis[g] = dis[t] + 1;
                        q.emplace(g);
                    }
                }
            }
            int id = 1;
            for (int i = 2; i <= n; ++i)
                if (dis[id] < dis[i]) id = i;
            for (int i = 1; i <= n; ++i) dis[i] = 1e18;
            dis[id] = 0;
            q.emplace(id);
            while (q.size()) {
                int t = q.front();
                q.pop();
                for (int &g : adj[t]) {
                    if (dis[g] > dis[t] + 1) {
                        dis[g] = dis[t] + 1;
                        q.emplace(g);
                    }
                }
            }
            int id2 = 1;
            for (int i = 2; i <= n; ++i)
                if (dis[id2] < dis[i]) id2 = i;
            // diameter: id <--> id2
            dfs(1, 0);
            vector<int> jmp1, jmp2, lnk;
            while (depth[id] > depth[id2]) {
                jmp1.emplace_back(id);
                id = parent[id];
            }
            while (depth[id] < depth[id2]) {
                jmp2.emplace_back(id2);
                id2 = parent[id2];
            }
            while (id != id2) {
                jmp1.emplace_back(id);
                jmp2.emplace_back(id2);
                id = parent[id];
                id2 = parent[id2];
            }
            for (int &i : jmp1) lnk.emplace_back(i);
            lnk.emplace_back(id);
            reverse(jmp2.begin(), jmp2.end());
            for (int &i : jmp2) lnk.emplace_back(i);
            if (lnk.size() & 1) {
                vector<pair<int, int>> op;
                int mid = lnk.size() / 2;
                for (int i = 0; i <= mid; ++i) op.emplace_back(lnk[mid], i);
                cout << op.size() << '\n';
                for (auto &[i, j] : op) cout << i << ' ' << j << '\n';
            } else {
                if (lnk.size() & 3) {
                    vector<pair<int, int>> op;
                    int mid = lnk.size() / 2;
                    for (int i = 0; i <= mid; ++i) op.emplace_back(lnk[mid], i);
                    cout << op.size() << '\n';
                    for (auto &[i, j] : op) cout << i << ' ' << j << '\n';
                } else {
                    vector<pair<int, int>> op;
                    int m1 = lnk.size() / 2 - 1, m2 = lnk.size() / 2;
                    for (int i = 0; i < m2 / 2; ++i) {
                        op.emplace_back(lnk[m1], i << 1 | 1);
                        op.emplace_back(lnk[m2], i << 1 | 1);
                    }
                    cout << op.size() << '\n';
                    for (auto &[i, j] : op) cout << i << ' ' << j << '\n';
                }
            }
        }
    }
    return 0;
}
```

---

## 作者：Genius_Star (赞：0)

### 思路：

[或许更好的阅读体验。](https://www.cnblogs.com/rgw2010/p/18357900)

考虑往直径方向想，设直径的长度为 $d$。

首先可以注意到一个性质：

- 每次操作最多只会覆盖住直径的 $2$ 个点，那么答案的下界即为 $\lceil \frac{d}{2} \rceil$。

分类讨论一下。

若 $d$ 为奇数，则存在唯一的一个直径中心 $u$：

- 那么答案为 $(u,0),(u,1),\cdots,(u,\lceil \frac{d-1}{2} \rceil)$。

- 最优次数是 $\lceil \frac{d}{2} \rceil$ 次。

若 $d$ 为偶数，则存在两个直径中心 $u,v$：

- 若 $d \bmod 4 = 0$ 时：

  - 那么答案为 $(u,1),(v,1),(u,3),(v,3),\cdots,(u,\frac{d}{2}-1),(v,\frac{d}{2}-1)$。

  - 最优次数是 $\frac{d}{2}$。

  - 这样是两者是完全错开的。

- 若 $d \bmod 4 = 2$ 时：

  - 那么答案为 $(u,0),(u,1),\cdots,(u,\frac{2}{d})$。

  - 最优次数是 $\frac{d}{2}+1$。

> 这里证明一下为什么当 $d \bmod 4 = 0$ 时不能取到答案的下界。
> 
> 注意到若 $x,y$ 能被同时取到当且仅当 $\operatorname{dis}(x,y)$ 为偶数。
> 
> 设 $L$ 为直径的一个端点，那么 $\operatorname{dis}(L,x)+\operatorname{dis}(L,y)$ 的奇偶性等价于 $2 \times (奇数或偶数)+偶数=偶数$。
> 
> 因为 $d \bmod 4 = 2$，所以 $\sum \operatorname{dis}(L,i) = \frac{d \times (d-1)}{2} \bmod 4 = 1$，则这个和式一定不是偶数，故无法达到下界。

时间复杂度为 $O(TN)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
#define Add(x,y) (x+y>=mod)?(x+y-mod):(x+y)
#define lowbit(x) x&(-x)
#define pi pair<ll,ll>
#define pii pair<ll,pair<ll,ll>>
#define iip pair<pair<ll,ll>,ll>
#define ppii pair<pair<ll,ll>,pair<ll,ll>>
#define fi first
#define se second
#define full(l,r,x) for(auto it=l;it!=r;it++) (*it)=x
#define Full(a) memset(a,0,sizeof(a))
#define open(s1,s2) freopen(s1,"r",stdin),freopen(s2,"w",stdout);
using namespace std;
typedef double db;
typedef unsigned long long ull;
typedef long long ll;
bool Begin;
const ll N=2e3+10;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
ll T,n,x,y,id,sum,cnt;
ll a[N],d[N],fa[N];
vector<ll> E[N];
void add(ll u,ll v){
    E[u].push_back(v);
    E[v].push_back(u);
}
void dfs(ll u,ll f){
    for(auto v:E[u]){
        if(v==f)
          continue;
        fa[v]=u;
        d[v]=d[u]+1;
        dfs(v,u);
    }
}
void solve(){
    cnt=0;
    n=read();
    for(int u,v,i=1;i<n;i++){
        u=read(),v=read();
        add(u,v);
    }
    fa[1]=d[1]=sum=0;
    dfs(1,1);
    for(int i=1;i<=n;i++){
        if(d[i]>=sum){
            sum=d[i];
            id=i;
        }
    }
    //cerr<<id<<'\n';
    fa[id]=d[id]=sum=0;
    dfs(id,id);
    for(int i=1;i<=n;i++){
        if(d[i]>=sum){
            sum=d[i];
            id=i;
        }
      //  cerr<<d[i]<<' ';
    }
   // cerr<<'\n';
    while(id){
        a[++cnt]=id;
        id=fa[id];
    }
    if(cnt&1ll){
        x=a[(cnt+1)>>1ll];
        write((cnt+1)>>1ll);
        putchar('\n');
        for(int i=0;i<((cnt+1)>>1ll);i++){
            write(x);
            putchar(' ');
            write(i);
            putchar('\n');
        }
    }
    else{
        x=a[cnt>>1ll],y=a[(cnt>>1ll)+1];
        if(cnt&3ll){
            write((cnt>>1ll)+1);
            putchar('\n');
            for(int i=0;i<=(cnt>>1ll);i++){
                write(x);
                putchar(' ');
                write(i);
                putchar('\n');
            }
        }
        else{
            write(cnt>>1ll);
            putchar('\n');
            for(int i=1;i<(cnt>>1ll);i+=2){
                write(x);
                putchar(' ');
                write(i);
                putchar('\n');
                write(y);
                putchar(' ');
                write(i);
                putchar('\n');
            }
        }
    }
    for(int i=1;i<=n;i++)
      E[i].clear();
}
bool End;
int main(){
    T=read();
    while(T--)
      solve();
	cerr<<'\n'<<abs(&Begin-&End)/1048576<<"MB";
	return 0;
}
```

---

## 作者：Halberd_Cease (赞：0)

首先有结论：每次操作最多改变树直径上最多两个点的颜色，并且这两个点距离为偶数。

那么直径点数是奇数的时候就很好求了，找到直径的中点，然后做 $\left \lceil \frac{n}{2}  \right \rceil $ 次操作（距离为 $0,1,2,\dots$），把所有点都染上色。

偶数的情况还要分类讨论：

- $4 \nmid n$：
	
    手动模拟一下，你会发现你无法在 $\frac n2$ 次操作后点亮直径上的所有的点。简单理解，将其顶点以任意形式两两配对后，你会发现其距离和是奇数，显然不可能恰好染色完。
    
    所以这种情况可以和 $n$ 为奇数一起处理，$\frac{n}{2}  +1 $ 次操作在直径任意一个中点上，即可染色完。
    
- $4 \mid n$：
	
    考虑这样一张图：
    
    ![](https://cdn.luogu.com.cn/upload/image_hosting/t02snju4.png)
    中点为 $4$ 和 $5$，分别点亮其距离为 $1,3$ 的点，你会发现所有的点都不重不漏的被点亮了。
    
    那么 $n$ 为 $4$ 的倍数的情况就是找到直径的两个中点，然后分别点亮距离为 $1,3,5,\dots$ 的点。
    
因此这道题的方法就是找直径，中点，然后根据直径长度分类讨论。

[submission](https://codeforces.com/contest/1943/submission/252374098)

---

## 作者：Alex_Wei (赞：0)

### [CF1943C Tree Compass](https://www.luogu.com.cn/problem/CF1943C)

对于树上的任意一条链，一次操作最多覆盖链上的两个点，这启发往直径的方向思考。

对于直径 $(u, v)$，设点数为 $d$，则答案有下界 $\lceil\frac d 2\rceil$。设 $c = \lfloor \frac d 2\rfloor$。

- 若 $d$ 为奇数，则操作次数不小于 $d = c + 1$。对直径中点 $m$ 和所有 $0\leq i\leq c$ 操作 $(m, i)$ 即可，因为所有点和 $m$ 的距离不超过 $c$，否则可以得到更长的直径。
- 若 $d$ 为偶数，先考虑一条链的情况。通过手玩 $d$ 较小时的情形，发现当 $d\bmod 4 = 2$ 时无法达到下界 $c$。思考其背后的本质。由 “一次操作覆盖两个距离为偶数的点”，考虑若将链黑白染色，则一次操作只能覆盖颜色相同的两点，于是 $d\bmod 4 = 2$ 的情况至少需要 $c + 1$ 次操作。
  - 若 $d\bmod 4 = 0$，设直径中点落在 $(m_1, m_2)$ 上，构造 $(m_1, i)$ 和 $(m_2, i)$，其中 $1\leq i \leq c$ 且 $i$ 为奇数。因为 $\min(\mathrm{dis}(x, m_1), \mathrm{dis}(x, m_2)) \leq c - 1$ 且两个 $\mathrm{dis}$ 至少一个为奇数，所以方案合法。
  - 若 $d\bmod 4 = 2$，设直径中点落在 $(m_1, m_2)$ 上，构造 $(m_1, i)$ 和 $(m_2, c - 1)$，其中 $0\leq i < c$。因为如果距离 $m_1$ 为 $c$ 则距离 $m_2$ 一定为 $c - 1$（否则距离 $m_2$ 为 $c + 1$，得到更长的直径），所以方案合法。

时间复杂度 $\mathcal{O}(n)$。[代码](https://codeforces.com/contest/1943/submission/251731321)。

---

