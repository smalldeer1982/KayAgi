# wxhtzdy ORO Tree

## 题目描述

After (finally) qualifying for the IOI 2023, wxhtzdy was very happy, so he decided to do what most competitive programmers do: trying to guess the problems that will be on IOI. During this process, he accidentally made a problem, which he thought was really cool.

You are given a tree (a connected acyclic graph) with $ n $ vertices and $ n-1 $ edges. Vertex $ i $ ( $ 1 \le i \le n $ ) has a value $ a_i $ .

Lets' define $ g(u, v) $ as the [bitwise or](http://tiny.cc/bitwise_or) of the values of all vertices on the shortest path from $ u $ to $ v $ . For example, let's say that we want to calculate $ g(3, 4) $ , on the tree from the first test case in the example. On the path from $ 3 $ to $ 4 $ are vertices $ 3 $ , $ 1 $ , $ 4 $ . Then, $ g(3, 4) = a_3 \ | \ a_1 \ | \ a_4 $ (here, $ | $ represents the [bitwise OR operation](http://tiny.cc/bitwise_or)).

Also, you are given $ q $ queries, and each query looks like this:

You are given $ x $ and $ y $ . Let's consider all vertices $ z $ such that $ z $ is on the shortest path from $ x $ to $ y $ (inclusive).

Lets define the niceness of a vertex $ z $ as the sum of the number of non-zero bits in $ g(x, z) $ and the number of non-zero bits in $ g(y, z) $ . You need to find the maximum niceness among all vertices $ z $ on the shortest path from $ x $ to $ y $ .

Since his brain is really tired after solving an output only problem on SIO (he had to do it to qualify for the IOI), he wants your help with this problem.

## 说明/提示

The image below shows the tree from the second example, first test case.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1878G/f2cfe5691aef70e9d1ac2a32021b32db3f24ab05.png) Tree from the second example, first test caseIn the first query, we have $ x=7 $ , $ y=5 $ . The shortest path from $ 7 $ to $ 5 $ is $ 7-4-2-1-5 $ .

Let's calculate the niceness of vertex $ 7 $ on this path. We have $ g(7,7)=a_7=10=(1010)_2 $ and $ g(5,7)=a_5 \ | \ a_1 \ | \ a_2 \ | \ a_4 \ | \ a_7=10 \ | \ 4 \ | \ 7 \ | \ 4 \ | \ 10=15=(1111)_2 $ , so its niceness is equal to $ 2 + 4 = 6 $ .

Now let's calculate the niceness of vertex $ 4 $ on this path. We have $ g(7,4)=a_7 \ | \ a_4=10 \ | \ 4=14=(1110)_2 $ and $ g(5,4)=a_5 \ | \ a_1 \ | \ a_2 \ | \ a_4=10 \ | \ 4 \ | \ 7 \ | \ 4=15=(1111)_2 $ , so its niceness is equal to $ 3 + 4 = 7 $ .

Now let's calculate the niceness of vertex $ 2 $ on this path. We have $ g(7,2)=a_7 \ | \ a_4 \ | \ a_2=10 \ | \ 4 \ | \ 7=15=(1111)_2 $ and $ g(5,2)=a_5 \ | \ a_1 \ | \ a_2=10 \ | \ 4 \ | \ 7=15=(1111)_2 $ , so its niceness is equal to $ 4 + 4 = 8 $ .

Now let's calculate the niceness of vertex $ 1 $ on this path. We have $ g(7,1)=a_7 \ | \ a_4 \ | \ a_2 \ | \ a_1=10 \ | \ 4 \ | \ 7 \ | \ 4=15=(1111)_2 $ and $ g(5,1)=a_5 \ | \ a_1=10 \ | \ 4=14=(1110)_2 $ , so its niceness is equal to $ 4 + 3 = 7 $ .

Finally, let's calculate the niceness of vertex $ 5 $ on this path. We have $ g(7,5)=a_7 \ | \ a_4 \ | \ a_2 \ | \ a_1 \ | \ a_5=10 \ | \ 4 \ | \ 7 \ | \ 4 \ | \ 10=15=(1111)_2 $ and $ g(5,5)=a_5=10=(1010)_2 $ , so its niceness is equal to $ 4 + 2 = 6 $ .

The maximum niceness on this path is at vertex $ 2 $ , and it is $ 8 $ .

## 样例 #1

### 输入

```
3
4
1 2 3 4
1 3
1 2
1 4
3
1 1
1 3
1 4
3
7 6 3
3 1
2 1
4
1 1
1 2
1 3
2 3
1
4
1
1 1```

### 输出

```
2 4 3 
6 6 6 6 
2```

## 样例 #2

### 输入

```
3
7
4 7 7 4 10 8 10
6 1
3 1
2 1
7 4
1 5
4 2
4
7 5
2 3
4 5
2 5
6
9 5 6 2 4 6
5 1
2 1
1 6
4 3
1 3
4
6 1
1 4
4 3
3 5
7
5 1 3 7 5 1 6
2 1
5 4
2 3
3 4
7 6
6 3
2
4 2
7 7```

### 输出

```
8 6 7 7 
6 6 4 7 
6 4```

## 样例 #3

### 输入

```
1
7
6 8 7 2 5 8 7
2 1
3 2
4 3
4 6
4 5
6 7
4
1 5
6 7
4 5
1 4```

### 输出

```
7 7 5 7```

# 题解

## 作者：WrongAnswer_90 (赞：7)

[CF1878G wxhtzdy ORO Tree](https://www.luogu.com.cn/problem/CF1878G)

![image.png](https://s2.loli.net/2023/10/09/AGbPteRLhOx739N.png)

设 $f(x,y)$ 表示树上 $x$ 到 $y$ 简单路径上的点权或和中 $1$ 的个数。

有一个性质：选取的 $z$ 节点一定满足它比它左边的点（$l$）或者右边的点（$r$）的贡献至少要多一位，即 $f(x,l)<f(x,z)$ 或 $f(y,r)<f(y,z)$，有了这个性质，问题就简单很多了。

即 $d_{i,j}$ 表示第 $i$ 个点的祖先中满足第 $j$ 位为 $1$ 的最深节点的编号，把 $x$ 到 $y$ 的路径看成 $x$ 到 $lca$ 和 $y$ 到 $lca$ 的两段，考虑 $z$ 在第一段路径上，只需要枚举 $d_{x,i}$ 和 $d_{y,i}$ 并检查是否合法（深度大于等于 LCA）然后暴力计算即可，对于 $z$ 在第二段路径上的情况同理。

代码中使用倍增实现求 $LCA$ 和一段路径的或和，复杂度为 $\mathcal O(n\log n \log V)$。

```cpp
int cnt,T,q,maxn,n,v[200001][21],d[200001][31],dep[200001],a[200001],fa[200001][21],head[200001],to[400001],nex[400001];
inline void add(int x,int y){to[++cnt]=y,nex[cnt]=head[x],head[x]=cnt;}
void dfs(int k,int fat)
{
	fa[k][0]=fat,memcpy(d[k],d[fat],sizeof(d[k])),dep[k]=dep[fat]+1,v[k][0]=a[k];
	for(int i=0;i<=30;++i)if(a[k]>>i&1)d[k][i]=k;
	for(int i=1;i<=20;++i)fa[k][i]=fa[fa[k][i-1]][i-1],v[k][i]=v[k][i-1]|v[fa[k][i-1]][i-1];
	for(int i=head[k];i;i=nex[i])if(to[i]!=fat)dfs(to[i],k);
}
inline int LCA(int x,int y)
{
	if(dep[x]>dep[y])swap(x,y);
	for(int i=20;i>=0;--i)if(dep[fa[y][i]]>=dep[x])y=fa[y][i];
	for(int i=20;i>=0;--i)if(fa[y][i]!=fa[x][i])y=fa[y][i],x=fa[x][i];
	return x==y?x:fa[x][0];
}
inline int ask(int x,int fat)
{
	int ans=0;
	for(int i=20;i>=0;--i)if(dep[fa[x][i]]>=dep[fat])ans|=v[x][i],x=fa[x][i];
	return ans|v[fat][0];
}
void mian()
{
	read(T);int x,y,lca,vx,vy;
	while(T--)
	{
		read(n),memset(head,0,sizeof(head)),cnt=0,maxn=0;
		for(int i=1;i<=n;++i)read(a[i]);
		for(int i=1;i<n;++i)read(x,y),add(x,y),add(y,x);
		dfs(1,0),read(q);
		while(q--)
		{
			read(x,y),lca=LCA(x,y),maxn=0,vx=ask(x,lca),vy=ask(y,lca);
			for(int i=0;i<=30;++i)if(d[x][i]&&dep[d[x][i]]>=dep[lca])maxn=max(maxn,__builtin_popcount(vy|ask(d[x][i],lca))+__builtin_popcount(ask(x,d[x][i])));
			for(int i=0;i<=30;++i)if(d[y][i]&&dep[d[y][i]]>=dep[lca])maxn=max(maxn,__builtin_popcount(vx|ask(d[y][i],lca))+__builtin_popcount(ask(y,d[y][i])));
			write(maxn);
		}
		puts("");
	}
}
```

---

## 作者：TKXZ133 (赞：4)

[wxhtzdy ORO Tree](https://www.luogu.com.cn/problem/CF1878G)

### 题目大意

给定一颗 $n$ 个点的树，每个点有权值 $a_i$，定义 $f(x,y)$ 表示从 $x$ 到 $y$ 的路径上的所有点的权值的按位或和，现有 $q$ 个询问，每个询问给出 $x,y$，求 

$$\max_{z\in\text{road}(x,y)}\left(\text{popcount}(f(x,z))+\text{popcount}(f(y,z))\right)$$

其中，$\text{road}(x,y)$ 表示 $x$ 到 $y$ 的路径上的所有点构成的集合，$\text{popcount}(x)$ 表示 $x$ 的二进制表示中 $1$ 的个数。

### 思路分析

赛时胡出来了，但是没有时间写了，赛后花了 40 分钟写完加调完。

做法比官方题解劣，是三个 $\log$ 的，不卡常 $4500ms$。

我们对值域按二进制位逐位考虑：

考虑某一位时 $x,y$ 的链是一条 01 链，我们找到从 $x$ 到 $y$ 链上的第一个 $1$ 的位置 $u$，将 $u$ 到 $y$ 的链加 $1$，再找到从 $y$ 到 $x$ 链上的第一个 $1$ 的位置 $v$，将 $v$ 到 $x$ 的链加 $1$，每一位都做完后查询全局最大值即可，正确性显然。

链加和查询全局最大值可以用树剖套线段树维护。

而找到第一个 $1$ 的位置可以用树剖套二分做，比较麻烦，需要预处理一个树上前缀数组。

时间复杂度为 $O(q\log^2n\log V)$，空间复杂度为 $O(n\log V)$。实现精细可以通过（比如写一个懒标记用于 $O(1)$ 清空线段树）。

这个做法有很高的可扩展性，比如可以做到求最大的 $z$ 的数量。

### 代码

（写了 4.5k，165 行，细节比较多，可以看一下注释）

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;
const int N = 200200, V = 30, M = 32;
#define inf 0x3f3f3f3f
#define mid ((l + r) >> 1)
#define ls (p << 1)
#define rs (p << 1 | 1)

int T, n, q, in1, in2, cnt;
int fa[N], dep[N], dfn[N], rnk[N], top[N], son[N], siz[N];
int pre[N][M], a[N];

// pre[i][j] 表示从 1 到 i 的路径上权值的第 j 位为 1 的点的数量

vector <int> to[N];

void dfs_1(int s, int gr){
    fa[s] = gr; siz[s] = 1; son[s] = 0;
    dep[s] = dep[gr] + 1;
    for (int i = 0; i <= V; i ++)
        pre[s][i] = pre[gr][i] + (a[s] >> i & 1);// 预处理前缀数组
    for (auto v : to[s]) {
        if (v == gr) continue;
        dfs_1(v, s);
        siz[s] += siz[v];
        if (siz[son[s]] < siz[v]) son[s] = v;
    }
}

void dfs_2(int s, int tp){
    top[s] = tp; dfn[s] = ++ cnt; rnk[cnt] = s;
    if (!son[s]) return ;
    dfs_2(son[s], tp);
    for (auto v : to[s])
        if (v != fa[s] && v != son[s]) dfs_2(v, v);
}

int lca(int x, int y){// 树剖求 lca 
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]]) swap(x, y);
        x = fa[top[x]];
    }
    return dep[x] > dep[y] ? y : x;
}

struct STn{
    int tag, max, tag2;
    // tag 是区间加懒标记，max 是最值，tag2 是清空懒标记
};
struct ST{
    STn a[N << 2];
    void add_t(int p, int k){
        a[p].tag += k, a[p].max += k;
    }
    void clear_t(int p){
        a[p].tag2 = 1;
        a[p].tag = a[p].max = 0;
    }
    void push_down(int p){
        if (a[p].tag2) {// 先下放清空
            clear_t(ls); clear_t(rs);
            a[p].tag2 = 0;
        }
        if (a[p].tag) {
            add_t(ls, a[p].tag);
            add_t(rs, a[p].tag);
            a[p].tag = 0;
        }   
    }
    void add(int p, int l, int r, int x, int y, int k){// 区间加
        if (x <= l && r <= y) return add_t(p, k);
        push_down(p);
        if (x <= mid) add(ls, l, mid, x, y, k);
        if (y > mid) add(rs, mid + 1, r, x, y, k);
        a[p].max = max(a[ls].max, a[rs].max);
    }
}tree;

void add_all(int x, int y, int k){// x 到 y 链加
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]]) swap(x, y);
        tree.add(1, 1, n, dfn[top[x]], dfn[x], k);
        x = fa[top[x]];
    }
    tree.add(1, 1, n, min(dfn[x], dfn[y]), max(dfn[x], dfn[y]), k);
}

int up(int x, int c){// 求从 x 到 1 的路径上第一个权值的第 c 位为 1 的点，时间复杂度是单 log 的
    while (top[x]) {
        if (pre[x][c] - pre[fa[top[x]]][c] != 0){// 链内存在 1
            int l = dfn[top[x]], r = dfn[x], ans = dfn[top[x]];// 重链上二分
            while (l <= r) {
                int Mid = (l + r) >> 1;
                if (pre[x][c] - pre[fa[rnk[Mid]]][c] != 0) l = Mid + 1, ans = Mid;
                else r = Mid - 1;
            }
            return rnk[ans];
        }
        x = fa[top[x]];
    }
    return -1;
}

int down(int x, int l, int c){// 求从 l 到 x 的路径上第一个权值的第 c 位 1 的点，l 是 x 的祖先
    vector <pair<int, int>> v;
    while (top[x] != top[l]) {// 从 x 跳到 l
        v.push_back({x, top[x]});
        x = fa[top[x]];
    }
    v.push_back({x, l});
    reverse(v.begin(), v.end());// 将跳的路径记录下来并反向
    for (auto it : v)
        if (pre[it.first][c] - pre[fa[it.second]][c] != 0) {// 存在 1
            int l = dfn[it.second], r = dfn[it.first], ans = dfn[it.second];// 二分位置
            while (l <= r) {
                int Mid = (l + r) >> 1;
                if (pre[rnk[Mid]][c] - pre[fa[it.second]][c] != 0) r = Mid - 1, ans = Mid;
                else l = Mid + 1;
            }
            return rnk[ans];
        }
    return -1;
}

int get(int x, int y, int c){// 分讨求 x 到 y 的路径上第一个权值的第 c 位为 1 的点
    int l = lca(x, y);
    if (pre[x][c] - pre[fa[l]][c] == 0) return down(y, l, c);
    else return up(x, c);
}

int main(){
    scanf("%d", &T);
    while (T --) {
        for (int i = 1; i <= n; i ++) to[i].clear();
        cnt = 0;
        scanf("%d", &n);
        for (int i = 1; i <= n; i ++) 
            scanf("%d", &a[i]);
        for (int i = 1; i < n; i ++) {
            scanf("%d %d", &in1, &in2);
            to[in1].push_back(in2);
            to[in2].push_back(in1);
        }
        dfs_1(1, 0);
        dfs_2(1, 1);
        scanf("%d", &q);
        while (q --) {
            scanf("%d %d", &in1, &in2);
            tree.clear_t(1);
            for (int i = 0; i <= V; i ++) {
                int l = lca(in1, in2);
                if (pre[in1][i] + pre[in2][i] - 2 * pre[fa[l]][i] == 0) continue;// 特判没有 1 的情况
                int u = get(in1, in2, i), v = get(in2, in1, i);
                add_all(u, in2, 1);// 链加
                add_all(in1, v, 1);
            }
            cout << tree.a[1].max << ' ';
        }
        cout << '\n';
    }
    return 0;
}
```

---

## 作者：ckain (赞：4)

考虑从 $x$ 开始顺着链枚举 $z$．可以发现 $g(x, z)$ 至多只有 $30$ 种不同的取值．每种取值都取尽量靠近 $x$ 的位置肯定最优．为了避免讨论，我们假设 $z$ 在 $x$ 到 $lca(x, y)$ 的路径上．

不妨记 $f_{u, i}$ 表示 $u$ 最近的祖先 $anc$ 满足 $a_{anc}$ 二进制的 $i$ 位为 $1$．我们按 $dep_{anc}$ 的顺序遍历 $f_{u, i}$，然后使用 $g(u, f_{u, i})+g(f_{u, i}, v)$ 更新答案．$g(u, f_{u, i})$ 在枚举的过程中可以顺便计算出来．$g(f_{u, i}, v)$ 不妨分成两部分：$g(f_{u, i}, lca(u, v)),g(lca(u, v), v)$ 计算．

但是使用 st table 单组 $O(\log n)$ 求链上或和非常不优雅．不妨活用 $f_{u}$：将 $f_{u}$ 按 $dep$ 排序时候二分出可取的部分即可．这样单组是 $O(\log \log w)$ 的．

总时间复杂度为 $O(n\log w \log \log w)$．

code

```

#include<bits/stdc++.h>
#define pii pair<int, int>
#define fr first
#define sc second
using namespace std;
inline int rd(void){
	int s=0, f=1; char c=getchar();
	while(c<'0' || c>'9') {if(c=='-') f=0; c=getchar();}
	while(c>='0' && c<='9') {s=s*10+c-'0'; c=getchar();}
	return f? s:-s;
}
 
const int N=2e5+5, Mp=30;
 
int n, q, a[N];
vector<int> e[N];
 
 
//pre_work
int anc[N][22], dep[N];
pii fir[N][Mp+1]; int fir_s[N][Mp+1], bit_R[N];
 
inline bool cmp(pii x, pii y){
	return (!x.fr || !y.fr)? x.fr!=0 : dep[x.fr]>dep[y.fr];
}
 
void pre_dfs(int u, int fa){
	dep[u]=dep[fa]+1;
	anc[u][0]=fa;
	for(int i=1; i<=20; i++) anc[u][i]=anc[anc[u][i-1]][i-1];
	bit_R[u]=Mp;
	for(int i=0; i<=Mp; i++){
		fir[u][i]={((a[u]>>i&1)? u:fir[fa][i].fr), i};
		if(!fir[u][i].fr) bit_R[u]=i-1;
	}
	for(int v:e[u]) if(v!=fa) pre_dfs(v, u);
}
//
 
inline int get_lca(int u, int v){
	if(dep[u]<dep[v]) swap(u, v); int dif=dep[u]-dep[v];
	for(int i=0; i<=20; i++) if(dif>>i&1) u=anc[u][i];
	if(u==v) return u;
	for(int i=20; ~i; i--) if(anc[u][i]!=anc[v][i]) u=anc[u][i], v=anc[v][i];
	return anc[u][0];
}
 
inline int get_sor(int u, int dif){
	int L=-1, R=bit_R[u]+1;
	while(R-L>1){
		int mid=(L+R)/2;
		if(dep[u]-dep[fir[u][mid].fr]+1<=dif) L=mid;
		else R=mid;
	}
	return (L==-1)? 0:fir_s[u][L];
}
 
inline int calc(int u, int v, int lc){
	#define pct __builtin_popcount
	int ror=get_sor(v, dep[v]-dep[lc]+1);
	int re=pct(ror);
	for(int i=0, lor=0; i<=bit_R[u] && dep[fir[u][i].fr]>=dep[lc]; i++){
		int x=fir[u][i].fr; lor++;
		int y=get_sor(x, dep[x]-dep[lc]+1);
		re=max(re, lor+pct(y|ror));
	}
	#undef pct
	return re;
}
 
inline void solve(){
	n=rd();
	for(int i=1; i<=n; i++) a[i]=rd();
	for(int i=1, u, v; i<n; i++) u=rd(), v=rd(), e[u].push_back(v), e[v].push_back(u);
	pre_dfs(1, 0);
	for(int u=1; u<=n; u++){
		sort(fir[u], fir[u]+Mp+1, cmp);
		fir_s[u][0]=(1<<fir[u][0].sc); for(int i=1; i<=bit_R[u]; i++) fir_s[u][i]=(fir_s[u][i-1]|(1<<fir[u][i].sc));
	}
	q=rd();
	for(int i=1, u, v, lc; i<=q; i++){
		u=rd(), v=rd();
		lc=get_lca(u, v);
		printf("%d ", max(calc(u, v, lc), calc(v, u, lc)));
	}
	puts("");
	for(int i=1; i<=n; i++) e[i].clear();
}
 
signed main(){
	int T=rd();
	while(T--){
		solve();
	}
	return 0;
}
```

---

## 作者：yangshengyu0719 (赞：2)

# 前言（发牢骚之地，可以跳过）
由于本人太菜，只会思路简单粗暴，代码难调的方法，因此成功调试了足足 $6$ 小时才 A。为纪念这道“史诗级难题”，故写下此篇 TJ。

# 正题
先读题，一眼树剖。发现问题跟位运算有关，所以首先考虑拆位。由于是或运算，因此对于每一个二进制位，只要在$road(x,z)$ 中某一个点的权值在这个位是 $1$,那么对答案的贡献就一定为 $1$。而为了使总贡献最大，我们尽量使 $f(x,z)$ 与 $f(y,z)$ 中在每一个二进制位都包含至少一个 $1$。

### 重点一：大体思路
我们令 $u_i$ 为在 $road(x,y)$ 中离 $x$ 最近的，第 $i$ 个二进制位为 $1$ 的点，同理 $v_i$ 为在 $road(x,y)$ 中离 $y$ 最近的，第 $i$ 个二进制位为 $1$ 的点。则若 $z$ 在 $road(u_i,v_i)$ 中，第 $i$ 位对答案的贡献为 $2$；否则第 $i$ 位对答案的贡献为 $1$。

因此我们在遍历每一位时，令 $road(u,v)$ 的贡献加 $1$,
$road(u_i,v_i)$ 的贡献再多加 $1$。最后再找树中贡献最大的点的贡献是多少即为答案。

### 重点二：$u_i$ 和 $v_i$ 怎么找
首先我们想到的是**线段树**维护每个区间内每一位最左边的为 $1$ 的位置，以及最右边的为 $1$ 的位置，再在爬树时暴力查询每一段的答案。但众所周知，线段树的常数普遍大得抽象，一不小心就容易写挂，然后得到永恒的 TLE。

因此我想到了一个**前缀和**加**二分**的方法，我们只要在爬树时，判断若某段的首尾前缀和不等，就说明这一段有 $1$，那么我们就对这段二分一下，找到最左或最右符合要求的答案即可，这样线段树就只用维护贡献加减及最大值了。语言描述可能不太好懂，各位可以理解一下等会的代码。

# 结尾
最后的最后，我们来总结一下时间复杂度，发现它约为 $O(n\log{a_i}\log^2{n})$ 。然后你一算，天哪，$1e9$ 都超了，还玩个屁。可是你要知道, CF 的评测机一秒 $1e9$ 轻轻松松，再加上亿点点卡常技巧，就能过了。

# 代码
```cpp
#include <bits/stdc++.h>
#define gc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<20,stdin),p1==p2)?EOF:*p1++)
using namespace std;
const int N=2e5+2;
int test,n,m;
int h[N],e[N<<1],nx[N<<1],idx;
int sz[N],fa[N],son[N],dep[N];
int top[N],tid[N],tot,id2[N];
int a[N],val[N],_[31],__[31];
int sum[31][N];//树上前缀和与差分 
char *p1,*p2,buf[1<<20+5];
inline int read(){
	int x=0;char c=gc();
	while(c<'0'||c>'9') c=gc();
	while('0'<=c&&c<='9') x=(x<<3)+(x<<1)+(c^48),c=gc();
	return x;
}
inline void write(int x){
	if(x>9) write(x/10);
	putchar(48+x%10);
}
struct node{int clean,tag,maxn;}T[N<<2],Empty;
inline void AddEdge(int u,int v){e[++idx]=v;nx[idx]=h[u];h[u]=idx;}
inline void dfs1(int u,int deep){
	dep[u]=deep,sz[u]=1;
	for(int i=h[u];i;i=nx[i]){
		int v=e[i];
		if(v^fa[u]){
			fa[v]=u,dfs1(v,deep+1);
			sz[u]+=sz[v];
			son[u]=sz[v]>=sz[son[u]]?v:son[u];
		}
	}
}
inline void dfs2(int u,int t){
	tid[u]=++tot,top[u]=t,val[tot]=a[u],id2[tot]=u;
	for(int i=0;i<30;i++)
		sum[i][tid[u]]=sum[i][tid[fa[u]]]+((a[u]>>i)&1);
	if(son[u]) dfs2(son[u],t);
	for(int i=h[u];i;i=nx[i]){
		int v=e[i];
		if(v^fa[u]&&v^son[u]) dfs2(v,v);
	}
}
inline void pushdown(int k){
	int ls=k<<1,rs=k<<1|1;
	if(T[k].clean){
		T[ls].clean=T[rs].clean=1;
		T[ls].maxn=T[rs].maxn=T[ls].tag=T[rs].tag=0;
		T[k].clean=0;
	}if(T[k].tag){
		int x=T[k].tag;
		T[ls].tag+=x;T[ls].maxn+=x;
		T[rs].tag+=x;T[rs].maxn+=x;
		T[k].tag=0;
	}
}
inline void add(int k,int l,int r,int x,int y,int z){
	if(l>y||r<x) return;
	if(x<=l&&r<=y){T[k].tag+=z;T[k].maxn+=z;return;}
	int mid=(l+r)>>1;
	pushdown(k);
	add(k<<1,l,mid,x,y,z);
	add(k<<1|1,mid+1,r,x,y,z);
	T[k].maxn=max(T[k<<1].maxn,T[k<<1|1].maxn);
}
inline void Add(int u,int v,int x){
	int f1,f2;
	while(top[u]!=top[v]){
		f1=top[u],f2=top[v];
		if(dep[f1]>dep[f2]) add(1,1,n,tid[f1],tid[u],x),u=fa[f1];
		else add(1,1,n,tid[f2],tid[v],x),v=fa[f2];
	}
	if(dep[u]>dep[v]) swap(u,v);
	add(1,1,n,tid[u],tid[v],x);
}
inline int Find_L(int bit,int u,int v){
	int ans=0,f1,f2;
	int *p=sum[bit];
	while(top[u]!=top[v]){
		f1=top[u],f2=top[v];
		if(dep[f1]>dep[f2]){
			if(sum[bit][tid[fa[f1]]]<sum[bit][tid[u]])
				return lower_bound(p+tid[f1],p+tid[u]+1,sum[bit][tid[u]])-p;
			u=fa[f1];
		}else ans=sum[bit][tid[fa[f2]]]<sum[bit][tid[v]]?lower_bound(p+tid[f2],p+tid[v]+1,sum[bit][tid[fa[f2]]]+1)-p:ans,v=fa[f2];
	}
	if(dep[u]>dep[v]) ans=sum[bit][tid[fa[v]]]<sum[bit][tid[u]]?lower_bound(p+tid[v],p+tid[u]+1,sum[bit][tid[u]])-p:ans;
	else ans=sum[bit][tid[fa[u]]]<sum[bit][tid[v]]?lower_bound(p+tid[u],p+tid[v]+1,sum[bit][tid[fa[u]]]+1)-p:ans;
	return ans;
}
inline int Find_R(int bit,int u,int v){
	int ans=0,f1,f2;
	int *p=sum[bit];
	while(top[u]!=top[v]){
		f1=top[u],f2=top[v];
		if(dep[f1]>dep[f2])
			ans=sum[bit][tid[fa[f1]]]<sum[bit][tid[u]]?lower_bound(p+tid[f1],p+tid[u]+1,sum[bit][tid[fa[f1]]]+1)-p:ans,u=fa[f1];
		else{
			if(sum[bit][tid[fa[f2]]]<sum[bit][tid[v]])
				return lower_bound(p+tid[f2],p+tid[v]+1,sum[bit][tid[v]])-p;
			v=fa[f2];
		}
	}
	if(dep[u]>dep[v]) ans=sum[bit][tid[fa[v]]]<sum[bit][tid[u]]?lower_bound(p+tid[v],p+tid[u]+1,sum[bit][tid[fa[v]]]+1)-p:ans;
	else ans=sum[bit][tid[fa[u]]]<sum[bit][tid[v]]?lower_bound(p+tid[u],p+tid[v]+1,sum[bit][tid[v]])-p:ans;
	return ans;
}
int popcount(int x){int res=0;while(x)res++,x-=x&(-x);return res<<1;}
int main(){
	int u,v;test=read();
	while(test--){
		for(int i=1;i<=n;i++) h[i]=son[i]=0;
		for(int i=1;i<=(n<<2);i++) T[i]=Empty;
		tot=idx=0;n=read();
		for(int i=1;i<=n;i++) a[i]=read();
		for(int i=1;i<n;i++) u=read(),v=read(),AddEdge(u,v),AddEdge(v,u);
		dfs1(1,1);dfs2(1,1);
		m=read();
		while(m--){
			u=read(),v=read();
			if(u==v){write(popcount(a[u]));putchar(' ');continue;}//一点点优化，没什么用
			for(int i=0;i<30;i++){
				_[i]=id2[Find_L(i,u,v)];__[i]=id2[Find_R(i,u,v)];
				if(!_[i]||!__[i]) continue;
				Add(u,v,1),Add(_[i],__[i],1);
			}
			write(T[1].maxn);putchar(' ');
			T[1].clean=1;T[1].maxn=T[1].tag=0;//打个标记,TLE->AC
			pushdown(1);
		}
		putchar('\n');
	}
	return 0;
}
```

---

## 作者：winter2020 (赞：2)

给一个好想同时较为好写的写法。

首先我们先把询问两点连线的链展开成一维。

依然考虑二进制拆位，假设当前枚举的数为 $2^j$：

- 先找到这个一维数组最左边和最右边二进制拆位包含 $2^j$ 次方的数，设下标分别为 $l$，$r$。

- 如果不存在这样的数，那么当前位对答案贡献为 $0$，不考虑。

- 如果存在这样的数，那么对答案的贡献至少为 $1$，继续考虑什么时候对答案贡献为 $2$，发现当 $l \leq z \leq r$ 时对答案贡献为 $2$（会在加法两边同时出现）。

- 那么这种情况就相当于对 $[l, r]$ 区间加一（这些位置的 $z$ 方案数额外多 $1$），我们不考虑用树剖等较为复杂做法，先直接将这个区间存起来。

当枚举完成后，我们考虑经过区间加一后的数组，容易发现有一个性质是数组最大值一定出现在前面存储的某个区间的左端点或右端点。

此性质并不难证明，烦请读者自行证明。

接着考虑怎么实现：

对于第一步，可以强行倍增。对于最后的枚举，可以直接枚举所有区间的左端点和右端点，再次枚举区间算出该点的贡献的额外贡献即可（区间一共不超过 $30$ 个，可以暴力枚举）。

最后加上之前说的稳定对答案有 $1$ 的贡献的区间数量即可。

### 参考代码：

```cpp
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

typedef pair<int, int> PII;
const int N = 2e5 + 10, M = N * 2;
int n, q;
vector<int> e[N], a;
bool f[30][N][19];
int depth[N], fa[N][19];
int sum[N][30];

int lca(int a, int b) {
    if (depth[a] < depth[b]) swap(a, b);
    for (int k = 18; k >= 0; k -- )
        if (depth[fa[a][k]] >= depth[b])
            a = fa[a][k];
    if (a == b) return a;
    for (int k = 18; k >= 0; k -- )
        if (fa[a][k] != fa[b][k])
        {
            a = fa[a][k];
            b = fa[b][k];
        }
    return fa[a][0];
}


void dfs(int u, int fat) {
	depth[u] = depth[fat] + 1;
    for (int i = 29; i >= 0; i -- )
        if (a[u] >> i & 1) {
            f[i][u][0] = 1;
            // cout << u << " " << i << endl;
            sum[u][i] = sum[fat][i] + 1;
        }
        else sum[u][i] = sum[fat][i], f[i][u][0] = 0;
    for (int i = 0; i < e[u].size(); i ++ ) {
    	int x = e[u][i];
        if (x == fat) continue;
        fa[x][0] = u;
        dfs(x, u);
    }
}

int main() {
    int T;
    cin >> T;
    while (T -- ) {
        cin >> n;
        a.clear(); a.push_back(0);
        for (int i = 1; i <= n; i ++ ) {
            int x;
            cin >> x;
            a.push_back(x);
            e[i].clear();
        }
        for (int i = 1; i < n; i ++ ) {
            int x, y;
            cin >> x >> y;
            e[x].push_back(y);
            e[y].push_back(x);
        }
        dfs(1, 0);
        for (int j = 1; j < 19; j ++ )
            for (int k = 1; k <= n; k ++ )
                fa[k][j] = fa[fa[k][j - 1]][j - 1];
        for (int i = 29; i >= 0; i -- )
            for (int j = 1; j < 19; j ++ )
                for (int k = 1; k <= n; k ++ )
                    f[i][k][j] = (f[i][k][j - 1] || f[i][fa[k][j - 1]][j - 1]);
       // cout << ":::::: " << f[3][4][2] << " " << fa[4][1] << endl;
        cin >> q;
        while (q -- ) {
            int u, v;
            cin >> u >> v;
            int t = lca(u, v), cnt = 0;
            vector<PII> b;
            for (int i = 29; i >= 0; i -- ) {
                int nowu = u, nowv = v, len1 = 0, len2 = depth[u] + depth[v] - 2 * depth[t];
                for (int j = 18; j >= 0; j -- )
                    if (depth[nowu] - (1 << j) >= depth[t] && !f[i][nowu][j]) {
                    	// cout << nowu << " " << j << " " << fa[nowu][j] << endl;
                        nowu = fa[nowu][j], len1 += (1 << j);
                    }
                for (int j = 18; j >= 0; j -- )
                    if (depth[nowv] - (1 << j) >= depth[t] && !f[i][nowv][j])
                        nowv = fa[nowv][j], len2 -= (1 << j);
                // cout << "::" << i << " " << nowu << " " << nowv << " " << len1 << " " << len2 << endl;
                if (!(a[nowu] >> i & 1) && !(a[nowv] >> i & 1)) continue;
                else if (!(a[nowu] >> i & 1)) {
                    nowu = nowv, len1 += (depth[nowv] - depth[t]);
                    for (int j = 18; j >= 0; j -- )
                    if (depth[nowu] - (1 << j) >= depth[t] && sum[fa[nowu][j]][i] - sum[fa[t][0]][i])
                        nowu = fa[nowu][j], len1 -= (1 << j);
                }
                else if (!(a[nowv] >> i & 1)) {
                    nowv = nowu, len2 = (depth[u] - depth[nowu]);
                    for (int j = 18; j >= 0; j -- )
                    if (depth[nowv] - (1 << j) >= depth[t] && sum[fa[nowv][j]][i] - sum[fa[t][0]][i])
                        nowv = fa[nowv][j], len2 += (1 << j);
                }
                cnt ++;
                
                b.push_back(make_pair(len1, len2));
               // cout << i << " " << len1 << " " << len2 << endl;
            }
            int ans = cnt;
            for (int i = 0; i < b.size(); i ++ ) {
            	PII x = b[i];
                int now = x.first, cot = 0;
                for (int j = 0; j < b.size(); j ++ ) {
                	PII ff = b[j];
                    if (ff.first <= now && ff.second >= now) cot ++;
                }
                ans = max(ans, cnt + cot);
                now = x.second, cot = 0;
                for (int j = 0; j < b.size(); j ++ ) {
                	PII ff = b[j];
                    if (ff.first <= now && ff.second >= now) cot ++;
                }
                ans = max(ans, cnt + cot);
            }
            cout << ans << " ";
        }
        puts("");
    }
    return 0;
}
```

---

## 作者：苏联小渣 (赞：2)

首先我们发现，一条路径上的前缀 or 值不超过 $\log V$ 种，所以我们可以考虑枚举这个值。

设 $x,y$ 的最近公共祖先为 $A$。我们发现 $z$ 的位置有两种情况：$x \to A$ 的路径上和 $y \to A$ 的路径上，而两种本质相同，所以我们只讨论在 $x \to A$ 的路径上的情况。

我们从 $x$ 开始，每次寻找它最近的一个祖先，使得此时的 or 值发生变化。容易发现由于这个祖先是最近的，所以对于 $y$ 而言答案也是最优的。对于查找这个祖先，我们可以记录 $f_{x,i}$ 表示 $x$ 的祖先（包括自己）中第 $i$ 位为 $1$ 且深度最大的那个。每次跳的时候，对于当前还是 $0$ 的位的集合 $\{i\}$，我们找到 $f_{x,i}$ 深度最大的那个就行了。

统计答案的时候，我们需要支持查询 $(x,y)$ 路径上的 or 和的 popcount。我们同样一位一位考虑，用前缀和就行了。

我实现的复杂度是 $O(n \log^2 V)$ 的，比官方题解似乎慢一点，但是可以过。

### Code

```c++
#include <bits/stdc++.h>
using namespace std;
int t, n, q, p, x, y, ans, son, h[200010], a[200010], dep[200010], lst[200010][32], s[200010][32], f[200010][18];
struct node{
	int x, y, next;
}d[400010];
void add(int x, int y){
	d[++p].y = y, d[p].next = h[x], h[x] = p;
}
void dfs(int x, int fa){
	dep[x] = dep[fa] + 1;
	for (int i=0; i<=31; i++){
		if ((a[x] >> i) & 1) lst[x][i] = x, s[x][i] = s[fa][i] + 1;
		else lst[x][i] = lst[fa][i], s[x][i] = s[fa][i];
	}
	for (int i=0; i<17; i++){
		f[x][i+1] = f[f[x][i]][i];
	}
	for (int i=h[x]; i; i=d[i].next){
		int y = d[i].y;
		if (y == fa) continue;
		f[y][0] = x;
		dfs(y, x);
	}
}
int LCA(int x, int y){
	if (dep[x] < dep[y]) swap(x, y);
	for (int i=17; i>=0; i--){
		if (dep[f[x][i]] >= dep[y]) x = f[x][i];
		if (x == y) return x;
	}
	for (int i=17; i>=0; i--){
		if (f[x][i] != f[y][i]){
			x = f[x][i], y = f[y][i];
		}
	}
	son = y;
	return f[x][0];
}
int calc(int x, int y, int lca){
	int ret = 0;
	for (int i=0; i<=31; i++){
		if (s[x][i] + s[y][i] - s[lca][i] - s[f[lca][0]][i]) ret ++;
	}
	return ret;
}
int main(){
	scanf ("%d", &t);
	while (t --){
		scanf ("%d", &n);
		for (int i=1; i<=n; i++){
			scanf ("%d", &a[i]);
			h[i] = p = 0;
		}
		for (int i=1; i<n; i++){
			scanf ("%d%d", &x, &y);
			add(x, y); add(y, x);
		}
		dfs(1, 0);
		scanf ("%d", &q);
		for (int i=1; i<=q; i++){
			scanf ("%d%d", &x, &y);
			son = ans = 0;
			int lca = LCA(x, y);
			int now = x, val = a[x];
			while (1){
				int nxt = 0, mx = 0;
				ans = max(ans, calc(x, now, LCA(x, now)) + calc(now, y, LCA(now, y)));
				for (int j=31; j>=0; j--){
					if (!((val >> j) & 1)){
						if (dep[lst[now][j]] >= dep[lca]){
							if (dep[lst[now][j]] > mx) mx = dep[lst[now][j]], nxt = lst[now][j];
						}
					}
				}
				if (!mx) break;
				val |= a[nxt], now = nxt;
			}
			now = y, val = a[y];
			while (1){
				int nxt = 0, mx = 0;
				ans = max(ans, calc(x, now, LCA(x, now)) + calc(now, y, LCA(now, y)));
				for (int j=31; j>=0; j--){
					if (!((val >> j) & 1)){
						if (dep[lst[now][j]] >= dep[lca]){
							if (dep[lst[now][j]] > mx) mx = dep[lst[now][j]], nxt = lst[now][j];
						}
					}
				}
				if (!mx) break;
				val |= a[nxt], now = nxt;
			}
			printf ("%d ", ans);
		}
		puts ("");
	}
	return 0;
}

```

---

## 作者：Microscopic_WaXeR (赞：2)

[题目链接](https://www.luogu.com.cn/problem/CF1878G)

## 解题思路

我们考虑按二进制位进行统计。

首先我们使用倍增解决 LCA 的问题，在做 dfs 的时候顺便再统计一个 $C_{i,j}$ 表示在 $i$ 这个节点时往上最早的节点 $k$ 使得其满足 $a_k$ 二进制的第 $j$ 位上为1。

然后对于每对询问，我们可以考虑将 $x \rightarrow lca$ 与 $lca \rightarrow y$ 拉成一条链，并在上面建立一棵线段树。然后对于每一个二进制位进行遍历，找到从 $x$ 开始的离其最近的在此时遍历的二进制位上为1的数字，将这个位置一直到 $y$ 区间加一。$y$ 同理。答案即为在遍历完后整棵线段树的区间最大值。

复杂度 $O(n \log V^2)$。

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=200010;
int T;
int n,a[N],q;
int head[N],cnt;
int f[N][35],c[N][35],dep[N];
ll ans;
struct Tree{
	int v,tag[2];
	//tag 0 : plus ; tag 1 cover
}tr[N<<2];
struct Edge{
	int to,nxt;
}e[N<<1];
void add(int u,int v){
	e[++cnt].to=v;
	e[cnt].nxt=head[u];
	head[u]=cnt;
}
void pushup(int node){
	tr[node].v=max(tr[node<<1].v,tr[node<<1|1].v);
}
void build(int l,int r,int node){
	if(l==r){
		tr[node].v=tr[node].tag[0]=0;
		tr[node].tag[1]=-1;
		return;
	}
	int mid=l+r>>1;
	build(l,mid,node<<1);
	build(mid+1,r,node<<1|1);
	pushup(node);
}
void pushdown(int node){
	if(~tr[node].tag[1]){
		tr[node<<1].tag[1]=tr[node].tag[1];
		tr[node<<1|1].tag[1]=tr[node].tag[1];
		tr[node<<1].v=tr[node].tag[1];
		tr[node<<1|1].v=tr[node].tag[1];
		tr[node<<1].tag[0]=tr[node<<1|1].tag[0]=0;
		tr[node].tag[1]=-1;
	}
	tr[node<<1].v+=tr[node].tag[0];tr[node<<1|1].v+=tr[node].tag[0];
	tr[node<<1].tag[0]+=tr[node].tag[0];tr[node<<1|1].tag[0]+=tr[node].tag[0];
	tr[node].tag[0]=0;
}
void Plus(int l,int r,int x,int y,int v,int node){
	if(x<=l && r<=y){
		tr[node].v+=v;
		tr[node].tag[0]+=v;
		return;
	}
	int mid=l+r>>1;
	pushdown(node);
	if(x<=mid) Plus(l,mid,x,y,v,node<<1);
	if(y>mid) Plus(mid+1,r,x,y,v,node<<1|1);
	pushup(node);
}
void Cover(int l,int r,int x,int y,int v,int node){
	if(x<=l && r<=y){
		tr[node].v=v;
		tr[node].tag[0]=0;
		tr[node].tag[1]=v;
		return;
	}
	int mid=l+r>>1;
	pushdown(node);
	if(x<=mid) Cover(l,mid,x,y,v,node<<1);
	if(y>mid) Cover(mid+1,r,x,y,v,node<<1|1);
	pushup(node);
}
void dfs(int x,int fa){
	f[x][0]=fa;
	dep[x]=dep[fa]+1;
	for(int j=0;j<=31;j++){
		if((a[x]>>j)&1) c[x][j]=x;
		else c[x][j]=c[fa][j];
	}
	for(int j=1;j<=31;j++)
		f[x][j]=f[f[x][j-1]][j-1];
	for(int i=head[x];i;i=e[i].nxt){
		int y=e[i].to;
		if(y==fa) continue;
		dfs(y,x);
	}
}
int lca(int x,int y){
	if(dep[x]<dep[y]) swap(x,y);
	for(int j=31;j>=0;j--)
		if(dep[f[x][j]]>=dep[y])
			x=f[x][j];
	if(x==y) return x;
	for(int j=31;j>=0;j--)
		if(f[x][j]!=f[y][j])
			x=f[x][j],y=f[y][j];
	return f[x][0];
}
void work(int x,int y){
	int fa=lca(x,y);
	int len=dep[x]-dep[fa]+dep[y]-dep[fa]+1;
	Cover(1,len,1,len,0,1);
	int lx,ly,rx,ry;
	for(int i=0;i<=31;i++){
		lx=c[x][i];ly=c[y][i];
		if(dep[lx]<dep[fa] && dep[ly]>=dep[fa]){
			ry=y;
			for(int p=31;p>=0;p--)
				if(dep[c[f[ry][p]][i]]>=dep[fa]){
					ry=f[ry][p];
				}
			Plus(1,len,len-(dep[y]-dep[ry]),len,1,1);
		}//如果此时x到lca的路径上没有,就去lca到y的路径上找
		else if(dep[lx]>=dep[fa]){	
			Plus(1,len,1+dep[x]-dep[lx],len,1,1);
		}
		if(dep[ly]<dep[fa] && dep[lx]>=dep[fa]){
			rx=x;
			for(int p=31;p>=0;p--)
				if(dep[c[f[rx][p]][i]]>=dep[fa])
					rx=f[rx][p];
			Plus(1,len,1,1+dep[x]-dep[rx],1,1);
		}//同理
		else if(dep[ly]>=dep[fa]){			
			Plus(1,len,1,len-(dep[y]-dep[ly]),1,1);
		}
	}
	cout<<tr[1].v<<' ';
}
void solve(){
	cin>>n;
	build(1,n,1);
	cnt=0;
	for(int i=1;i<=n;i++){
		cin>>a[i];	
		head[i]=0;dep[i]=0;
	}
	int u,v;
	for(int i=1;i<n;i++){
		cin>>u>>v;
		add(u,v);add(v,u);
	}
	dfs(1,0);
	cin>>q;
	int x,y;
	while(q--){
		cin>>x>>y;
		ans=0;
		work(x,y);
	}
	cout<<endl;
}
int main(){
	cin>>T;
	while(T--)
		solve();
	return 0;
}

```

---

## 作者：Kidding_Ma (赞：1)



树上两点之间或可以使用 $\text{lca}$ 维护。

对于每次询问两点 $u,v$ 先找到 $\text{lca}$，考虑暴力枚举 $z$，这样是 $O(qn)$，此时只考虑枚举从 $u$ 到 $v$ 会导致答案变化的关键点 $z$，关键点一定不超过 $60$ 个，从 $u$ 到 $\text{lca}$ 的关键点不超过 $30$ 个，从 $v$ 到 $\text{lca}$ 的关键点不超过 $30$ 个。

$O(n+q\cdot (\log n+60\log n))$。

C++ Code

```cpp
#include "bits/stdc++.h"

using namespace std;
using i64 = long long;

int popcount(const int &x) {
    return __builtin_popcount(x);
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<vector<int>> g(n);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;

        u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    int lg = __lg(n);
    vector<vector<int>> p(lg + 1, vector<int>(n, -1));
    vector<int> dep(n);
    vector<vector<int>> sum(lg + 1, vector<int>(n));

    function<void(int, int)> dfs = [&](int cur, int pre) {
        for (int i = 0; (2 << i) <= dep[cur]; i++) {
            p[i + 1][cur] = p[i][p[i][cur]];
            sum[i + 1][cur] = sum[i][cur] | sum[i][p[i][cur]];
        }

        for (auto &nex : g[cur]) {
            if (nex != pre) {
                p[0][nex] = cur;
                dep[nex] = dep[cur] + 1;
                sum[0][nex] = a[cur] | a[nex];
                dfs(nex, cur);
            }
        }        
    };

    dfs(0, -1);

    auto lca = [&](int x, int y) {
        if (dep[x] < dep[y]) {
            swap(x, y);
        }
        for (int i = lg; i >= 0; i--) {
            if(dep[x] - dep[y] >= (1 << i)) {
                x = p[i][x];
            }
        }
        if (x == y) {
            return x;
        }
        for (int i = lg; i >= 0; i--) {
            if(p[i][x] != p[i][y]) {
                x = p[i][x];
                y = p[i][y];
            }
        }        
        return p[0][x];
    };

    auto get = [&](int u, int v) {
        int res = a[u];
        for (int i = lg; i >= 0; i--) {
            if (dep[u] - dep[v] >= (1 << i)) {
                res |= sum[i][u];
                u = p[i][u];
            }            
        }
        return res;
    };

    int q;
    cin >> q;
    while (q--) {
        int u, v;
        cin >> u >> v;

        u--, v--;
        int m = lca(u, v);

        int res1 = get(u, m), res2 = get(v, m);
        int ans = popcount(res1) + popcount(res2);

        auto f = [&](int u, int half) {
            int cur = 0;
            for (int z = u; z != -1 && dep[z] > dep[m]; z = p[0][z]) {
                cur |= a[z];
                ans = max(ans, popcount(get(u, z)) + popcount(get(z, m) | half));
                for (int i = lg; i >= 0; --i) {
                    if (dep[z] - dep[m] >= (1 << i)) {
                        if ((cur | sum[i][z]) == cur) {
                            z = p[i][z];
                        }
                    }
                }
            }
        };

        f(u, res2);
        f(v, res1);
        
        cout << ans << " \n"[q == 0];
    }

}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
```

---

## 作者：Gold14526 (赞：0)

$\rm Problem$：[wxhtzdy ORO Tree](https://codeforces.com/problemset/problem/1878/G)

$\rm Difficulty:2300$

**单 $\log$ 在线做法**。

### 做法

我们把一条路径上的点权看作一个序列 $w$。

能够作为关键点的位置 $z$ 应当满足 $w_z$ 要么比 $w_{1\sim z-1}$ 的或和多一位 $1$，要么比 $w_{z+1\sim |w|}$ 的或和多一位 $1$，不难证明这样的位置只有 $O(\log V)$ 个。

我们直接对每个点 $u$ 维护一个 $lst_{h,u}$ 表示 $u$ 最近祖先使得该祖先权值第 $h$ 位为 $1$。

那么能够成为 $z$ 的点一定属于 $lst_{h,x}$ 或 $lst_{h,y}$，那我们直接把这些点全部拿出来算答案。

于是，只要我们能够做到 $O(1)$ 求链或和便可以单 $\log$ 解决此题。

我们考虑平时在序列上 $O(1)$ 求区间或和，这种情况我们用 ST 表维护，设 $len$ 为区间长度，取 $p$ 使得 $2^p\le len<2^{p+1}$，求区间前 $2^p$ 个数的或和以及后 $2^p$ 个数的或和合并即可。

转移到链上，首先把一条链拆成两条直链，其中用 $O(1)$ LCA，接下来只需解决一条直链上的或和，我们同样取 $p$ 使得 $2^p\le dis<2^{p+1}$，用倍增配合长剖 $O(1)$ 求 $k$ 级祖先即可做到 $O(1)$ 查询链或和。

### 代码

```cpp
#include<bits/stdc++.h>
#define cint const int
#define uint unsigned int
#define cuint const unsigned int
#define ll long long
#define cll const long long
#define ull unsigned long long
#define cull const unsigned long long
#define sh short
#define csh const short
#define ush unsigned short
#define cush const unsigned short
using namespace std;
int read()
{
	int x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<1)+(x<<3)+(ch-'0');
		ch=getchar();
	}
	return x;
}
void print(cint x)
{
	if(x<10)
	{
		putchar(x+'0');
		return;
	}
	print(x/10);
	putchar(x%10+'0');
}
void princh(cint x,const char ch)
{
	print(x);
	putchar(ch);
}
int n,q;
int ppc_[1<<16];
void init()
{
	for(int i=1;i<1<<16;++i)
	{
		ppc_[i]=ppc_[i-(i&-i)]+1;
	}
}
inline int ppc(cint x)
{
	return ppc_[x&((1<<16)-1)]+ppc_[x>>16];
}
cint N=2e5,H=29;
int lg[N+1];
int lst[H+1][N+1],w[N+1],fa[18][N+1],wsum[18][N+1];
vector<int>to[N+1],fal[N+1],sonl[N+1],key[N+1];
int tag[N+1];
int mxdep[N+1],mxson[N+1],top[N+1];
inline void add_edge(cint u,cint v)
{
	to[u].push_back(v);
	to[v].push_back(u);
}
int dfn[N+1],dep[N+1];
int idx[N+1];
struct Spare_Table{
	int st[18][N+1];
	inline int cmin(cint x,cint y)
	{
		return (dep[x]<dep[y]?x:y);
	}
	void init()
	{
		for(int i=2;i<=n;++i)lg[i]=lg[i-1]+(i==(i&-i));
		for(int i=1;i<=n;++i)st[0][i]=dfn[i];
		for(int k=1;k<=lg[n];++k)
		{
			for(int i=1;i<=n-(1<<k)+1;++i)
			{
				st[k][i]=cmin(st[k-1][i],st[k-1][i+(1<<k-1)]);
			}
		}
	}
	inline int ask(int l,int r)
	{
		if(l>r)swap(l,r);
		++l;
		cint p=lg[r-l+1];
		return cmin(st[p][l],st[p][r-(1<<p)+1]);
	}
}ST;
inline int lca(cint u,cint v)
{
	if(u==v)return u;
	return fa[0][ST.ask(idx[u],idx[v])];
}
void dfs(cint u,cint father)
{
	dep[u]=dep[father]+1;
	mxdep[u]=dep[u];
	mxson[u]=u;
	fa[0][u]=father;
	dfn[++n]=u;
	idx[u]=n;
	for(int i=0;i<=H;++i)
	{
		if((w[u]>>i&1))lst[i][u]=u;
		else lst[i][u]=lst[i][father];
		if(tag[lst[i][u]]!=u)
		{
			tag[lst[i][u]]=u;
			key[u].push_back(lst[i][u]);
		}
	}
	for(int v:to[u])
	{
		if(v==father)continue;
		dfs(v,u);
		if(mxdep[v]>mxdep[u])
		{
			mxson[u]=v;
			mxdep[u]=mxdep[v];
		}
	}
}
void down(cint u)
{
	if(!top[u])top[u]=u;
	top[mxson[u]]=top[u];
	for(int v:to[u])
	{
		if(v==fa[0][u])continue;
		down(v);
	}
	if(top[u]==u)
	{
		for(int v=u,w=u,i=0;i<=mxdep[u]-dep[u];++i)
		{
			fal[u].push_back(v);
			sonl[u].push_back(w);
			v=fa[0][v];
			w=mxson[w];
		}
	}
}
int find(cint u,cint k)
{
	if(k==0)return u;
	cint p=lg[k],h=(1<<p),v=top[fa[p][u]];
	return (dep[u]-k>dep[v]?sonl[v][dep[u]-k-dep[v]]:fal[v][dep[v]-dep[u]+k]);
}
int get(cint u,cint k)
{
	cint p=lg[k];
	return wsum[p][u]|wsum[p][find(u,k-(1<<p))];
}
int ask(cint u,cint v)
{
	cint c=lca(u,v);
	return get(u,dep[u]-dep[c]+1)|get(v,dep[v]-dep[c]+1);
}
void query()
{
	cint u=read(),v=read();
	cint c=lca(u,v);
	int ans=0;
	for(int p:key[u])
	{
		if(dep[p]>=dep[c])ans=max(ans,ppc(ask(u,p))+ppc(ask(v,p)));
	}
	for(int p:key[v])
	{
		if(dep[p]>=dep[c])ans=max(ans,ppc(ask(u,p))+ppc(ask(v,p)));
	}
	princh(ans,' ');
}
void solve()
{
	n=read();
	for(int i=1;i<=n;++i)
	{
		wsum[0][i]=w[i]=read();
		fal[i].clear();
		sonl[i].clear();
		top[i]=tag[i]=0;
		key[i].clear();
		to[i].clear();
	}
	for(int i=1;i<n;++i)
	{
		add_edge(read(),read());
	}
	n=0;
	dfs(1,0);
	ST.init();
	down(1);
	for(int k=1;k<=lg[n];++k)
	{
		for(int i=1;i<=n;++i)
		{
			fa[k][i]=fa[k-1][fa[k-1][i]];
			wsum[k][i]=wsum[k-1][i]|wsum[k-1][fa[k-1][i]];
		}
	}
	q=read();
	while(q--)query();
}
int main()
{
	init();
	int T=read();
	while(T--)solve();
	return 0;
}

```

---

## 作者：ifffer_2137 (赞：0)

吐了。码量题建议还是似一似。
### 题意
给定一棵 $n$ 个点的树，定义 $f(u,v)$ 表示 $u$，$v$ 路径上所有点的点权按位或结果，有 $q$ 次询问，每次给定 $u$，$v$，求：
$$\max_{x\in path(u,v)}(\text{popcount}(f(u,x)),\text{popcount}(f(v,x)))$$
### 分析
这种题一般拆位。

然后你看一下每一个 bit 的贡献，路径上没出现过的直接扬了，路径上出现过的贡献至少为 $1$，中间切开后如果两边都有贡献就是 $2$。

观察数据范围与时间限制发现正解应该至少两 log。

于是可以上一点不太精细的 ds 了，随便搞搞就可以艹过去。具体地，看一下想要让某个 bit 产生 $2$ 的贡献，切开的点可以选在哪里。可以发现是 $u$ 到 $v$ 路径上，有这个 bit 的，最靠近 $u$ 的点和最靠近 $v$ 的点连成的子路径。不想动脑子，于是直接剖一下吧。然后把路径拆成最多两条从上往下的链，扫一遍上面所有重链，找到第一个以后重链里面 dfn 序连续，直接二分，在之前遍历整棵树的时候顺便给每个 bit 弄个 dfn 序上的前缀和就可以 check 了。

然后你找出了这 $O(\log V)$ 条子路径，不妨设 $u$ 为端点，给整条路径编一下号，就把子路径全部拍成区间了。排一下序暴力扫找出被覆盖最多的那个位置即可，显然可能成为最大值的只有每个区间的起点。

复杂度是 $O(n\log n\log V)$ 的。代码实现比较赤石。
### 代码

```cpp
//From: ifffer_2137
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define inf 0x7fffffff
#define eb emplace_back
#define pii pair<int,int>
#define mkpr make_pair
#define fir first
#define sec second
inline int read(){
	char ch=getchar();int x=0,w=1;
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+ch-48,ch=getchar();return w==1?x:-x;
}
const int maxn=2e5+5;
int _,n,q;
int a[maxn][30];
vector<int> T[maxn];
int fa[maxn],dep[maxn],siz[maxn],hson[maxn];
int dfn[maxn],id[maxn],top[maxn],dfc;
int c[30][maxn];
vector<pii> tmp;
void init(){
	for(int i=1;i<=n;i++){
		T[i].clear();for(int j=0;j<30;j++) a[i][j]=c[j][i]=0;
		fa[i]=dep[i]=siz[i]=hson[i]=dfn[i]=id[i]=top[i]=0;
	}
	dfc=0;
}
void dfs1(int u,int f){
	fa[u]=f,dep[u]=dep[f]+1;
	siz[u]=1;
	for(int v:T[u]){
		if(v==f) continue;
		dfs1(v,u);
		siz[u]+=siz[v];
		if(siz[v]>siz[hson[u]]) hson[u]=v;
	}
}
void dfs2(int u,int t){
	dfn[u]=++dfc;id[dfc]=u;
	for(int i=0;i<30;i++) c[i][dfn[u]]+=a[u][i];
	top[u]=t;
	if(hson[u]) dfs2(hson[u],t);
	for(int v:T[u]){
		if(v==fa[u]||v==hson[u]) continue;
		dfs2(v,v);
	}
}
inline int lca(int u,int v){
	while(top[u]!=top[v]){
		if(dep[top[u]]>dep[top[v]]) u=fa[top[u]];
		else v=fa[top[v]];
	}
	return dep[u]<dep[v]?u:v;
}
inline pii query(int u,int v,int b){
	int vv=v;
	vector<pii> lne;pii res={0,0};
	while(dep[v]>=dep[u]){
		lne.eb(mkpr(max(dfn[u],dfn[top[v]]),dfn[v]));
		v=fa[top[v]];
	}
	sort(lne.begin(),lne.end());
	for(pii x:lne){
		if(c[b][x.sec]-c[b][x.fir-1]){
			int l=x.fir,r=x.sec;
			while(l<=r){
				int m=(l+r)>>1;
				if(c[b][m]-c[b][x.fir-1]) res.fir=dep[id[m]],r=m-1;
				else l=m+1;
			}
			break;
		}
	}
	for(int i=lne.size()-1;i>=0;i--){
		pii x=lne[i];
		if(c[b][x.sec]-c[b][x.fir-1]){
			int l=x.fir,r=x.sec;
			while(l<=r){
				int m=(l+r)>>1;
				if(c[b][x.sec]-c[b][m-1]) res.sec=dep[id[m]],l=m+1;
				else r=m-1;
			}
			break;
		}
	}
	return res;
}
signed main(){
	#ifndef ONLINE_JUDGE
	freopen("data.in","r",stdin);
	freopen("test.out","w",stdout);
	#endif
	cin.tie(0),cout.tie(0);
	_=read();
	while(_--){
		n=read();init();
		for(int i=1;i<=n;i++){
			int x=read();
			for(int j=0;j<30;j++) a[i][j]=((x>>j)&1);
		}
		for(int i=1;i<n;i++){
			int u=read(),v=read();
			T[u].eb(v),T[v].eb(u);
		}
		dfs1(1,0);dfs2(1,1);
		for(int j=0;j<30;j++) for(int i=1;i<=n;i++) c[j][i]+=c[j][i-1];
		q=read();
		while(q--){
			int u=read(),v=read(),ans=0;
			int f=lca(u,v);tmp.clear();
			if(f==u||f==v){
				v=u^v^f,u=f;
				for(int i=0;i<30;i++){
					pii x=query(u,v,i);
					if(!x.fir) continue;
					ans++;
					tmp.eb(mkpr(x.fir-dep[u]+1,x.sec-dep[u]+1));
				}
			}else{
				for(int i=0;i<30;i++){
					pii x=query(f,u,i),y=query(f,v,i);
					if(!x.fir&&!y.fir) continue;
					ans++;
					tmp.eb(mkpr(x.sec?dep[u]-x.sec+1:dep[u]+y.fir-dep[f]*2+1,
					y.sec?dep[u]+y.sec-dep[f]*2+1:dep[u]-x.fir+1));
					pii k=tmp.back();
				}
			}
			sort(tmp.begin(),tmp.end(),[](pii x,pii y){return x.fir!=y.fir?x.fir<y.fir:x.sec>y.sec;});
			int mx=0;
			for(int i=0;i<tmp.size();i++){
				int cnt=1;
				for(int j=0;j<i;j++) if(tmp[j].sec>=tmp[i].fir) cnt++;
				mx=max(mx,cnt);
			}
			cout<<ans+mx<<" ";
		}
		cout<<"\n";
	}
	return 0;
}
```

---

## 作者：vanyou (赞：0)

## 大意

给一棵树，每个点有点权，每次询问在 $x$ 到 $y$ 的路径上找一点 $z$，使得 $x$ 到 $z$ 的路径点权按位或和的二进制 $1$ 的个数和 $y$ 到 $z$ 的路径点权按位或和的二进制 $1$ 的个数的和最大。

## 思路

对于二进制每一位的贡献，可以一位一位的考虑。

其次就是如果点 $z$ 的第 $i$ 位二进制为 $1$ 的话，那么以点 $z$ 为分界两边的路径就都可以得到这一位的贡献。

为了避免枚举整条路径上的每一个点，我们只需要查询 $x$ 和 $y$ 的第一个第 $i$ 位二进制位 $1$ 的祖先就可以找到对于第 $i$ 位二进制必须产生两个贡献的情况的最大值。因为其它二进制位为 $1$ 的情况可以解决答案可能不优的情况，所以只要对每个二进制位为 $1$ 的情况取个最大值就可以了，这样最多枚举 $2 \times \log(\max(a_i)) $ 个点。

对于每次查询的两条路径，要判分界点 $z$ 的深度是否比 $ \operatorname{lca}(x,y) $ 的深度深，否则没有满足情况的点 $z$ ，最近公共祖先可以用倍增优化在 $O(\log(n))$ 的时间里求解，求解路径的按位或和同样可以用倍增处理，对于最后的二进制位 $1$ 的个数，倍增数组的或和可以使用 bitset 储存并用 count 函数得到。

预处理的时间复杂度在 $O(n \log(n) \log(\max(a_i)))$。询问的时间复杂度在 $O(q \log(n) \log(\max(a_i)))$，总时间复杂度就是 $O(n \log(n) \log(\max(a_i)))$。

## Code

```c++
#include<bits/stdc++.h>
using namespace std;
int n,a[200010],q,fa[200010][20],dep[200010],at[200010][35];
bitset<35> s[200010][20];
vector<int> g[200010];

void pre(int u,int f){
	dep[u]=dep[f]+1,fa[u][0]=f;
	s[u][0]=a[u];
	for(int i=1;i<20;i++){
		fa[u][i]=fa[fa[u][i-1]][i-1];
		s[u][i]=s[u][i-1]|s[fa[u][i-1]][i-1];
	}
	for(int i:g[u])
		if(i!=f) pre(i,u);
}

int lca(int x,int y){
	if(dep[x]<dep[y]) swap(x,y);
	for(int i=19;i>=0;i--)
		if(dep[fa[x][i]]>=dep[y]) x=fa[x][i];
	if(x==y) return x;
	for(int i=19;i>=0;i--)
		if(fa[x][i]!=fa[y][i])
			x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}

bitset<35> popcount(int x,int en){
	bitset<35> ans=0;
	for(int i=19;i>=0;i--)
		if(dep[fa[x][i]]>=dep[en]) ans|=s[x][i],x=fa[x][i];
	ans|=s[x][0];
	return ans;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	int t;
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=n;i++) cin>>a[i],g[i].clear();
		for(int i=1,u,v;i<n;i++){
			cin>>u>>v;
			g[u].push_back(v);
			g[v].push_back(u);
		}
		pre(1,0);
		for(int op=0;op<=30;op++){
			for(int i=1;i<=n;i++){
				int x=i;
				for(int j=19;j>=0;j--)
					if(!s[x][j][op]) x=fa[x][j];
				at[i][op]=x;
			}
		}
		cin>>q;
		while(q--){
			int x,y,Lca,ans=0;
			cin>>x>>y;
			Lca=lca(x,y);
			for(int i=0;i<=30;i++){
				if(dep[at[x][i]]>=dep[Lca])
					ans=max(ans,(int)popcount(x,at[x][i]).count()+(int)(popcount(at[x][i],Lca)|popcount(y,Lca)).count());
				if(dep[at[y][i]]>=dep[Lca])
					ans=max(ans,(int)popcount(y,at[y][i]).count()+(int)(popcount(at[y][i],Lca)|popcount(x,Lca)).count());
			}
			cout<<ans<<" ";
		}
		cout<<"\n";
	}
	return 0;
}

```

---

