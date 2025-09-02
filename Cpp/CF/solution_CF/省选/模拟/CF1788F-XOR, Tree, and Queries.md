# XOR, Tree, and Queries

## 题目描述

You are given a tree of $ n $ vertices. The vertices are numbered from $ 1 $ to $ n $ .

You will need to assign a weight to each edge. Let the weight of the $ i $ -th edge be $ a_i $ ( $ 1 \leq i \leq n-1 $ ). The weight of each edge should be an integer between $ 0 $ and $ 2^{30}-1 $ , inclusive.

You are given $ q $ conditions. Each condition consists of three integers $ u $ , $ v $ , and $ x $ . This means that the [bitwise XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR) of all edges on the shortest path from $ u $ to $ v $ should be $ x $ .

Find out if there exist $ a_1, a_2, \ldots, a_{n-1} $ that satisfy the given conditions. If yes, print a solution such that $ a_1 \oplus a_2 \oplus \ldots \oplus a_{n-1} $ is the smallest. Here, $ \oplus $ denotes the bitwise XOR operation.

If there are multiple solutions such that $ a_1 \oplus a_2 \oplus \ldots \oplus a_{n-1} $ is the smallest, print any.

## 说明/提示

For the first example, there does not exist a set of edge weights that satisfies the given conditions.

For the second example, the two given conditions are $ a_1 \oplus a_2 \oplus a_3=2 $ and $ a_4 \oplus a_5=7 $ . There can be multiple solutions, for example, $ (a_1, a_2, a_3, a_4, a_5)=(1, 2, 1, 4, 3) $ .

For the third example, the two given conditions are $ a_1 \oplus a_2 \oplus a_3=3 $ and $ a_1 \oplus a_4 \oplus a_5=5 $ . There are multiple solutions that satisfy the given conditions.

 $ (a_1, a_2, a_3, a_4, a_5)=(1, 1, 3, 4, 0) $ satisfies the given conditions, but the bitwise XOR of all edge weights is $ 7 $ , which does not have the smallest $ a_1 \oplus a_2 \oplus \ldots \oplus a_{n-1} $ , so it cannot be the answer.

## 样例 #1

### 输入

```
4 4
1 2
2 3
3 4
1 4 3
2 4 2
1 3 1
2 3 1```

### 输出

```
No```

## 样例 #2

### 输入

```
6 2
1 2
2 3
3 4
2 5
5 6
1 4 2
2 6 7```

### 输出

```
Yes
4 2 4 1 6```

## 样例 #3

### 输入

```
6 2
1 2
2 3
3 4
2 5
5 6
1 4 3
1 6 5```

### 输出

```
Yes
6 1 4 3 0```

# 题解

## 作者：洛浔 (赞：12)

## 题意

给定一颗 $n$ 个节点的树，给定树的形态。

有 $m$ 条限制，每条限制形如 $(u,v,w)$，表示从 $u$ 到 $v$ 的路径上的边权异或和为 $w$。

你需要填入树边的边权，在满足条件的基础上让所有树边的异或和最小，并输出你构造的边权。若无解输出 `NO`。

## 题解

### 转化题意

令 $f_x$ 表示 $x$ 到根的异或和，那么 $(u,v,w)$ 的限制就可以转化成 $f_u \oplus f_v = w$，这一步我们把边权转化成了点权。将点权转化成边权的操作是对于树边 $(u,v,w)$，$w = f_u \oplus f_v$ （注意这不是对限制操作的逆向转化）。之后只需要考虑点权。

将这些限制转化成图，对于 $(u,v,w)$ 的限制，我们将其转化成一条由 $u$ 到 $v$ 边权为 $w$ 的无向边。最终这些限制将成为一些联通块。

### 判断是否有解

遍历每个连通块，并对它的赋值，因为之后要进行最小化调整，所以现在的赋值随意。考虑什么情况是无解的：当两次对他的赋值矛盾的时候无解。所以我们可以 dfs 遍历每个连通块，对其赋值和进行有解判断。并在这个过程中处理目前的结果 $ans$。

### 最小化调整

每个联通块的内部结构是确定的，我们能调整的只有对每个连通块第一个点的赋值。而且只要我们能在所有联通块中有一个的修改是能直接影响答案的，由于异或的性质，最后的答案为 $0$。

考虑一个连通块怎么能影响答案。将每个点转化成边权后，每个点权的计算次数是他在原图上的度数次。也就是说，当这个点在原图上度数为奇数时，修改这个点会影响答案一次。当在这个连通块里有奇数个这样的点，就会影响答案奇数次，才能影响答案。

操作是将这个连通块内所有的点的赋值都异或上 $ans$，最终答案为 $0$。

如果不能进行这个调整那么最后的答案就是 $ans$。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
template<class T>void read(T &x){
    x=0;int f=0;char ch=getchar();
    while(ch<'0'||ch>'9')  {f|=(ch=='-');ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    x=f?-x:x;return;
}
#define int long long
const int N=3e5+5;
int n,m;
struct node{int u,v;}inp[N];
bool vis[N];
int hd[N],tot;
struct edge{int to,nxt,val;}a[N<<1];
void add(int u,int v,int w){
    a[++tot]=(edge){v,hd[u],w};
    hd[u]=tot;
}
int val[N],deg[N];
vector<int> point,chg;
void dfs(int u){
	vis[u]=1;
    point.push_back(u);
    for(int i=hd[u];i;i=a[i].nxt){
        int to=a[i].to;
        if(vis[to]){
            if(val[to]^val[u]^a[i].val){
                puts("NO");
                exit(0);
            }
            continue;
        }
        val[to]=val[u]^a[i].val;
        dfs(to);
    }
}
main(){
    read(n),read(m);
    for(int i=1;i<n;i++){
    	 read(inp[i].u),read(inp[i].v);
    	 deg[inp[i].u]++,deg[inp[i].v]++;
    }
    for(int i=1;i<=m;i++){
        int u,v,w;
        read(u),read(v),read(w);
        add(u,v,w),add(v,u,w);
    }
    int ans=0;;
    for(int i=1;i<=n;i++){
        if(!vis[i]){
            point.clear();
            dfs(i);
            int fg=0;
            for(int j:point) fg^=(deg[j]&1);
            if(fg&&(!chg.size()))for(int j:point) chg.push_back(j);
            for(int j:point) if(deg[j]&1)ans^=val[j];
        }
    }
    if(chg.size())for(int i:chg)val[i]^=ans;
    puts("Yes");
    for(int i=1;i<n;i++) printf("%d ",val[inp[i].u]^val[inp[i].v]);
    return 0;
}
```


---

## 作者：Feyn (赞：7)

套路地令 $s_x$ 表示点 $x$ 到根路径上的异或和，于是形如点 $x$ 到 $y$ 的异或和必须是 $v$ 的性质可以转化成 $s_x\oplus s_y=v$ 的形式。然后根据异或的性质，如果知道了 $a\oplus b,b\oplus c$ 的值，那么 $a\oplus c$ 的值是确定的。所以前面的限制会把 $s$ 分成一些连通块，可以抽离连通块中的一棵生成树求出点值之间的异或值，然后用那些非树边去检查，如果有哪个非树边不满足那么整道题就无解了。至此就可以构造方案了。

但是如何让所有树边的异或和最小呢，考虑如何用 $s$ 去表示边的异或和。一条连接 $x,y$（并且 $x$ 是 $y$ 的父亲）的边的边权是 $s_x\oplus s_y$，于是发现异或到最后，那些拥有偶数个孩子的点对应的 $s$ 会留在柿子里，剩下的就不见了，我们称这些点是关键点。

考虑如何高效地降低异或和。对于每个连通块分别考虑，显然如果改变了一个点的 $s$，那么连通块内所有点的 $s$ 都会改变，所以遍历一下统计连通块内关键点的数量，如果是偶数，那么不会改变最后的答案，忽略；否则贪心地尝试给每个 $s$ 异或上当前构造出来的异或和，这样可以直接把边权异或和清零，显然最优。

要特殊处理，因为 $s_{root}$ 只能是 $0$。输出方案很简单。

```cpp
#include<bits/stdc++.h>
//#define feyn
using namespace std;
const int N=300010;
inline void read(int &wh){
    wh=0;int f=1;char w=getchar();
    while(w<'0'||w>'9'){if(w=='-')f=-1;w=getchar();}
    while(w<='9'&&w>='0'){wh=wh*10+w-'0';w=getchar();}
    wh*=f;return;
}

int m,n,sum[N],ans[N];
bool matter[N];

namespace pre{
	struct edge{
		int t,v,nxt;
	}e[N<<1];
	int head[N],esum;
	inline void add(int fr,int to,int val){
		e[++esum]=(edge){to,val,head[fr]};head[fr]=esum;
	}
	void dfs(int wh,int fa){
		int nowNum=0;
		for(int i=head[wh],th;i;i=e[i].nxt){
			if((th=e[i].t)==fa)continue;
			dfs(th,wh);++nowNum;
		}
		if((nowNum&1)==0&&wh!=1)matter[wh]=true;
	}
	void find(int wh,int fa){
		for(int i=head[wh],th;i;i=e[i].nxt){
			if((th=e[i].t)==fa)continue;
			ans[e[i].v]=sum[th]^sum[wh];
			find(th,wh);
		}
	}
}
namespace suf{
	struct edge{
		int t,v,nxt;
	}e[N<<1];
	int head[N],esum,du[N];
	inline void add(int fr,int to,int val){
		++du[fr],++du[to];
		e[++esum]=(edge){to,val,head[fr]};head[fr]=esum;
	}
	bool vis[N];
	void dfs(int wh){
		vis[wh]=true;
		for(int i=head[wh],th;i;i=e[i].nxt){
			if(vis[th=e[i].t]){
				if((sum[wh]^sum[th])!=e[i].v){
					puts("No");exit(0);
				}
				continue;
			}
			sum[th]=sum[wh]^e[i].v;
			dfs(th);
		}
	}
	bool ched[N];int chNum;
	void change(int wh){
		ched[wh]=true;chNum+=matter[wh];
		for(int i=head[wh],th;i;i=e[i].nxt){
			if(ched[th=e[i].t])continue;
			sum[th]=e[i].v^sum[wh];change(th);
		}
	}
	void main(){
		for(int i=1;i<=m;i++){
			if(vis[i]==false)dfs(i);
		}
		int all=0;
		for(int i=1;i<=m;i++){
			if(matter[i])all^=sum[i];
		}
		change(1); 
		for(int i=2;i<=m;i++){
			if(ched[i])continue;
			sum[i]^=all;chNum=0;
			change(i);
			if(chNum&1)break;
		}
	}
}

signed main(){
	
	#ifdef feyn
	freopen("in.txt","r",stdin);
	#endif
	
	read(m);read(n);int s1,s2,s3;
	for(int i=1;i<m;i++){
		read(s1);read(s2);
		pre::add(s1,s2,i);pre::add(s2,s1,i);
	}
	for(int i=1;i<=n;i++){
		read(s1);read(s2);read(s3);
		suf::add(s1,s2,s3);suf::add(s2,s1,s3);
	}
	pre::dfs(1,0);
	suf::main();puts("Yes");
	pre::find(1,0);
	for(int i=1;i<m;i++)printf("%d ",ans[i]);
	
	return 0;
}
```

---

## 作者：N2MENT (赞：3)

[CF1788F](https://www.luogu.com.cn/problem/CF1788F)
有点意思的题目。

***

### 题意

设 $f(u,v)$ 表示从 $u$ 到 $v$ 的路径权值异或和。给定一个 $n$ 个点的树，$q$ 个关系，每个关系包含三个参数 $u$，$v$ 和 $w$，要求构造树的边权，使得 $\forall i,f(u_i,v_i)=w$。无解输出 NO，有解则输出 YES 以及使得所有边的异或和最小的方案。

***

### 解法

设 $g(u)$ 表示从 $1$ 到 $u$ 的路径权值异或和。$f(u,v) = g(u) \oplus g(v)$ 即 $g(u) \oplus g(v) = w$，那么我们先不考虑边权，只考虑给每个点的 $g(u)$ 赋值。由于异或值只和单独一位上的值有关，考虑每一位拆开处理。

首先保证方案合法。  
新建一个 $n$ 个点的无向图 $G$，对于每个关系，在 $u$ 和 $v$ 之间连一条权值为 $w$ 的边，假设此时处理到第 $i$ 位，如果 $w$ 的第 $i$ 位为 $0$ 说明 $u$ 和 $v$ 的第 $i$ 位必须相等，否则不相等。每次对所有连通块按照边权的第 $i$ 位黑白染色，矛盾直接判定为无解。

然后考虑使得代价最小。  
树上一条边的边权等于 $g(u) \oplus g(v)$，边权转点权，有偶数度的点没有贡献，只考虑奇数度点的贡献。  
依然是拆开每一位处理，随后对于一个连通块求贡献，设连通块里染了黑色的有贡献的点有 $c_1$ 个，白色有 $c_0$ 个，如果 $c_0$ 和 $c_1$ 奇偶性相同，那么这个位上这个连通块的贡献是固定的，否则可以 $01$ 翻转改变连通块的贡献。  
由于每一位都是独立的，代价的每一位能取 $0$ 就取 $0$，如果是 $1$ 就尝试改变一个连通块的贡献使它变成 $0$。

然后呢，做完力！复杂度 $\Theta(n\log_2w)$，$2.5 \times 10^5$ 刚好跑得过。


code

```
#include <bits/stdc++.h>
using namespace std;
const int maxn = 2.5e5 + 10;
struct Edge {
    int v, w;
    Edge() {}
    Edge(int v, int w) : v(v), w(w) {}
};
vector<Edge> G[maxn];
vector<int> gp[maxn];
vector<int> p[maxn];
int wb[32][maxn];
bool flip[32][maxn];
int col[maxn];
bool deg[maxn];
int sum[maxn];
int colcnt;
int n, q;
void div(int u) {
    gp[colcnt].emplace_back(u);
    col[u] = colcnt;
    for (auto e : G[u]) {
        int v = e.v;
        if (col[v])
            continue;
        div(v);
    }
}
int o;
int z;
void dfs(int u) {
    for (auto e : G[u]) {
        int v = e.v, w = e.w;
        bool opt = bool(w & o);
        if (wb[z][v] == -1) {
            wb[z][v] = wb[z][u] ^ opt;
            dfs(v);
        } else if (wb[z][v] != (wb[z][u] ^ opt)) {
            printf("no");
            exit(0);
        }
    }
}
int u[maxn], v[maxn];
int main() {
    memset(wb, -1, sizeof(wb));
    scanf("%d%d", &n, &q);
    for (int i = 1; i < n; i++) {
        scanf("%d%d", u + i, v + i);
        deg[u[i]] ^= 1;
        deg[v[i]] ^= 1;
    }
    for (int i = 1; i <= q; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        G[u].emplace_back(v, w);
        G[v].emplace_back(u, w);
    }
    for (int i = 1; i <= n; i++) {
        if (!col[i]) {
            colcnt++;
            div(i);
        }
    }//拆分连通块
    for (int i = 1; i <= n; i++) {
        if (deg[i])
            p[col[i]].emplace_back(i);
    }//找有贡献的点
    for (z = 0, o = 1; z <= 30; z++, o <<= 1) {
        for (int i = 1; i <= colcnt; i++) {
            wb[z][gp[i].front()] = 0;
            dfs(gp[i].front());
        }
    }//黑白染色
    printf("yes\n");
    for (z = 0, o = 1; z <= 30; z++, o <<= 1) {
        int tot = 0;
        for (int i = 1; i <= colcnt; i++) {
            if (p[i].empty())//处理连通块的贡献
                continue;
            int x = 0;
            for (int j : p[i]) {
                if (wb[z][j])
                    x ^= 1;
            }
            tot ^= x;
        }
        if (tot) {//如果是1就尝试改回0
            for (int i = 1; i <= colcnt; i++) {
                if (p[i].empty())
                    continue;
                int cnt0 = 0, cnt1 = 0;
                int x = 0;
                for (int j : p[i]) {
                    if (wb[z][j] == 0)
                        cnt0++;
                    else
                        cnt1++, x ^= 1;
                }
                if ((cnt0 & 1) != (cnt1 & 1)) {
                    tot ^= 1;
                    flip[z][i] = 1;
                    break;
                }
            }
        }
    }
    for (int i = 1; i <= n; i++) {//根据每一位的信息推出g(u)
        for (z = 0, o = 1; z <= 30; z++, o <<= 1) {
            if (wb[z][i] ^ flip[z][col[i]])
                sum[i] |= o;
        }
    }
    for (int i = 1; i < n; i++) {//输出答案
        printf("%d ", sum[u[i]] ^ sum[v[i]]);
    }
}
```

---

## 作者：Zhao_daodao (赞：1)

# [CF1788F] XOR, Tree, and Queries

## Description

给你一棵 $n$ 个节点的树，你需要给每一条边赋值 $a_i$，满足 $a_i\in [0,2^{30})$。

有 $q$ 条限制，而每一个限制形如 $(u,v,w)$，表示**从 $u$ 到 $v$ 的边权异或和为 $w$**。

问你能否构造出一组 $a_i$ 的合法解，如果有，需要最小化 $a$ 的异或和，输出任意一解都可。

## Solution

发现两点之间的异或和，套路转换一下。

不妨假设根为 1。设 $dep_i$ 表示从根到 $i$ 的异或和。

每一条限制就是 $dep_u\oplus dep_v=w$。

建立一个新图，将每一个限制的 $(u,v)$ 之间连双向边，边权为 $w$。

这个新图中的每一个连通块，都只有一个变量。确定这个变量，整个连通块中的点的 $dep$ 都被确定下来。

假设新图中的一个连通块第一次遍历到的点是 $i$。

就是说，这个连通块中，$dep_i$ 是变量，其他的 $dep_u$ 都能表示成 $dep_i\oplus x$ 的形式。

如果在连通块中，**一个点本身有权值，但是现在被赋了一个不一样的权值**，那么就无解了。

不然就是有解。

---

那如何最小化呢？

设每一个新点所在的连通块中的根是 $rt_i$，这个点向连通块的根的距离是 $dis_i$。

那么这个点的权值可以表示成 $dep_{rt_i}\oplus dis_i$。

首先一个观察：每一条从 $u$ 连向 $v$ 的边的权值就是 $dep_u\oplus dep_v$。

所以最后的答案就是 $(dep_{u_1}\oplus dep_{v_1})\oplus (dep_{u_2}\oplus dep_{v_2})\oplus \cdots\oplus (dep_{u_{n-1}}\oplus dep_{v_{n-1}})$。

**直接能够表示成若干个连通块的根的权值异或和，再异或上一个常数 $x$。**

如果最后化简出来有一个 $dep_i$，那么答案就是 0。

不然就是 $x$。

所以我们钦定一个连通块的根的权值 $dep_i=x$，其他连通块的根的权值**全部都是 0**。

这样一定能够取到最小值。

构造的话根据每一条 $u$ 向 $v$ 的边为 $dep_u\oplus dep_v$ 即可。

## Code

```cpp
#include<bits/stdc++.h>
#define int long long
#define Pair pair<int,int>
using namespace std;
const int MAXN=2.5e5+5;
int n,q;
int u_[MAXN],v_[MAXN];
int head[MAXN],tot;
struct node{int nxt,to;}e[MAXN<<1];
inline void add(int u,int v){
    e[++tot]=node{head[u],v};
    head[u]=tot;
}
vector<Pair>G[MAXN];
int root[MAXN],dis[MAXN];//根 到根的距离
inline void dfs(int u,int rt){
    root[u]=rt;
    for(auto [v,w]:G[u]){
        if(!root[v]){
            dis[v]=dis[u]^w;
            dfs(v,rt);
        }
        else{
            if(dis[v]!=(dis[u]^w)){
                cout<<"No\n";
                exit(0);
            }
        }
    }
}
int ans[MAXN];
int cnt[MAXN],ano;
inline void add(int x){
    cnt[root[x]]^=1;
    ano^=dis[x];
}
signed main(){
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(false);
    cin>>n>>q;
    for(int i=1;i<n;i++){
        cin>>u_[i]>>v_[i];
        add(u_[i],v_[i]);
        add(v_[i],u_[i]);
    }
    for(int i=1,u,v,w;i<=q;i++){
        cin>>u>>v>>w;
        G[u].push_back(Pair(v,w));
        G[v].push_back(Pair(u,w));
    }
    for(int i=1;i<=n;i++)if(!root[i]){
        root[i]=i;dfs(i,i);
    }
    cout<<"Yes\n";
    for(int i=1;i<n;i++){
        add(u_[i]),add(v_[i]);
    }
    memset(ans,0,sizeof ans);
    for(int i=1;i<=n;i++)if(cnt[i]){
        ans[i]=ano;ano=0;
    }
    for(int i=1;i<=n;i++){
        ans[i]=ans[root[i]]^dis[i];
    }
    for(int i=1;i<n;i++)cout<<(ans[u_[i]]^ans[v_[i]])<<" ";
}
```

---

## 作者：lfxxx (赞：1)

首先每一位都是独立的，按位考虑。

不妨令 $1$ 为根。

假若只有 $0,1$，我们考虑将两点间路径的异或值转变为两点到根路径的异或值的异或，所以设 $a_i$ 表示点 $i$ 到根路径上的异或值，那么限制可以被描述为 $a_u \oplus a_v = 0/1$，那么直接拆点后连边即可判断是否有解（无解当且仅当 $a_u = 0$ 与 $a_u = 1$ 处于一个连通块中），最优化答案考虑先构造一组解，然后假若不优再看是否有可以翻转后改变改变权值的连通块即可，注意 $a_1$ 必须为 $0$。

总时间复杂度 $O(n \log V)$，常数可能比较大，下面放出卡常后通过的代码。

[代码](https://codeforces.com/contest/1788/submission/284281900)

---

## 作者：0xyz (赞：0)

我们先预处理出使得 $a_1\oplus a_2\oplus …\oplus a_{n-1}=s_{i_1}\oplus s_{i_2}\oplus …\oplus s_{i_k}$ 的 $i_1,i_2,…i_k$。

每一位是独立的，我们只要考虑这一位 $i$ 有解还是无解，有解时能不能取到 $0$ 即可，分开考虑。首先，令 $s_x\in\{0,1\}$ 表示从 $x$ 到 $1$ 的边权异或和。对于任何一个 $u,v,x$，我们都有 $s_u\oplus s_v=x$，就在 $u,v$ 之间连上一条权为 $x$ 的边。然后，对于每个连通块分开看。在处理一个连通块时，任取一个点 $x$，讨论 $s_x$ 的取值，那么这个连通块所有的 $x$ 都确定了，它对 $ans_i$ 的贡献也就确定了。如果 $2$ 种赋值方案都不可行，就无解。整个问题有解当且仅当所有连通块都有解，并且如果有一个连通块对 $ans_i$ 可以贡献 $0,1$，那么无论其它连通块贡献几它都可以保证 $ans_i=0$；否则，每个连通块贡献唯一，直接计算 $ans_i$ 即可。

时间复杂度 $O(n\log v)$。

```cpp
#pragma GCC optimize(2)
#include<bits/stdc++.h>
using namespace std;
const int _=5e5+5,o=(1<<30)-1;
int f[_],t[_],h[_],nxt[_],pt[_],q[_],w[_],u[_],a[_],s[_],l,r,b,d,n,m,nm;
bitset<_>c,v,p,g;
vector<pair<int,int> >e[_];
void dfs(int x,int fa){
	f[x]=fa;
	for(pair<int,int> y:e[x])
		if(y.first!=fa)a[y.second]=y.first,dfs(y.first,x);
}
inline int gen(int x,bool y){
	bool rs=0,fl=0;
	c[x]=y;v[x]=1;q[l=r=1]=x;pt[nm=1]=x;
	while(l<=r){
		int x=q[l++];
		if(p[x])rs^=c[x];
		for(int i=h[x];i;i=nxt[i])
			if(!v[t[i]])c[t[i]]=c[x]^g[i],v[t[i]]=1,pt[++nm]=q[++r]=t[i];
			else fl|=c[t[i]]^c[x]^g[i];
	}
	if(fl)return -1;
	return rs;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(int i=1,x,y;i<n;i++){
		cin>>x>>y;
		e[x].push_back({y,i});
		e[y].push_back({x,i});
	}
	dfs(1,0);
	for(int i=2;i<=n;i++)p.flip(f[i]),p.flip(i);
	p[1]=0;
	for(int i=1,x,y;i<=m;i++){
		cin>>x>>y>>w[i];
		nxt[i+i-1]=h[x];h[x]=i+i-1;t[i+i-1]=y;
		nxt[i+i]=h[y];h[y]=i+i;t[i+i]=x;
	}
	for(int i=0;i<30;i++){
		b=d=0;v.reset();
		bool fl=0;
		for(int j=1;j<=m;j++)g[j+j-1]=g[j+j]=(w[j]>>i)&1;
		for(int j=1;j<=n;j++)
			if(!v[j]){
				int g0=gen(j,0),g1=-1;
				if(j>1){
					for(int k=1;k<=nm;k++)v[pt[k]]=0;
					g1=gen(j,1);
				}
				if(g0==-1&&g1==-1)cout<<"No\n",exit(0);
				else if(g0==0&&g1==1&&!fl)u[j]=3,fl=1;
				else if(g0==1&&g1==0&&!fl)u[j]=4,fl=1;
				else if(g0!=-1)d^=g0,u[j]=1;
				else d^=g1,u[j]=2;
			}
		v.reset();
		for(int j=1;j<=n;j++)
			if(!v[j]){
				if(u[j]==1)gen(j,0);
				else if(u[j]==2)gen(j,1);
			}
		for(int j=1;j<=n;j++)
			if(!v[j]){
				if(u[j]==3)gen(j,d);
				else if(u[j]==4)gen(j,d^1);
			}
		for(int j=1;j<=n;j++)s[j]|=c[j]<<i;
	}
	cout<<"Yes\n";
	for(int i=1;i<n;i++)cout<<(s[a[i]]^s[f[a[i]]])<<' ';
	return 0;
}
```

---

## 作者：tribool4_in (赞：0)

首先对于路径的边权异或和，考虑 $f_i$ 表示 $i$ 到根节点的路径异或和，于是一条路径 $u-v$ 的权值变成了 $f_u\oplus f_v$。接下来只需要考虑 $f_i$。

考虑如何判断合法。对于一条限制 $(u,v,w)$ 等价于 $f_u\oplus f_v=w$，想到在新图上连边，边权为 $w$，于是形成了若干个连通块互相独立。对于每个连通块的某个环，显然要满足其上的边权异或和为 $0$，这个容易通过 dfs 判断，只需判断 dfs 树上的返祖边是否合法即可。

考虑如何最小化答案。容易发现一条边 $(u,v)$ 的权值也为 $f_u\oplus f_v$，因此一个点的 $f_u$ 能对答案产生贡献当且仅当其度数为奇数，称其为贡献点。对于每个连通块选出一个度数为奇数的贡献点 $r$ 作为“根”，则对于该连通块内的每个点 $f_u=f_r\oplus d_{r,u}$，其中 $d_{r,u}$ 为定值。因此若一个连通块内的贡献点个数为奇数则 $f_r$ 会对答案产生一次贡献，否则贡献为定值。

于是构造方法已经很显然了。设所有连通块内的贡献定值（即 $d$ 的异或和）为 $k$，若存在一个连通块有奇数个贡献点，则只需令其 $f_r=k$，其余连通块 $f_r=0$，于是答案为 $0$。否则答案为定值 $k$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2.5e5 + 10;
int n, m, x[N], y[N], deg[N], vis[N], xors[N], ans[N];
int oddc[N], rt[N], Rt;
vector<pair<int, int>> G[N];
vector<int> cc[N];
void dfs(int u, int id) {
    vis[u] = id, cc[id].push_back(u);
    for (auto [v, w] : G[u]) {
        if (vis[v]) {
            if (xors[v] != (xors[u] ^ w)) {
                cout << "No\n";
                exit(0);
            }
            continue;
        }
        xors[v] = xors[u] ^ w;
        dfs(v, id);
    }
}
bool vis2[N];
void dfs2(int u) {
    vis2[u] = 1;
    for (auto [v, w] : G[u]) {
        if (vis2[v]) continue;
        ans[v] = ans[u] ^ w;
        dfs2(v);
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i < n; i++) cin >> x[i] >> y[i], ++deg[x[i]], ++deg[y[i]];
    for (int i = 1, u, v, w; i <= m; i++) {
        cin >> u >> v >> w;
        G[u].emplace_back(v, w), G[v].emplace_back(u, w);
    }
    int ccnt = 0, kv = 0, cnt2 = 0;
    for (int i = 1; i <= n; i++)
        if (!vis[i]) dfs(i, ++ccnt);
    for (int i = 1; i <= ccnt; i++) {
        for (auto u : cc[i]) oddc[i] += (deg[u] & 1), rt[i] = ((deg[u] & 1) ? u : rt[i]);
        if (oddc[i] & 1) Rt = rt[i];
        if (!rt[i]) rt[i] = cc[i][0];
        for (auto u : cc[i])
            if (deg[u] & 1) kv ^= (xors[rt[i]] ^ xors[u]);
        cnt2 += (oddc[i] & 1);
    }
    for (int i = 1; i <= ccnt; i++) {
        if (Rt == rt[i]) ans[rt[i]] = kv, dfs2(rt[i]);
        else dfs2(rt[i]);
    }
    cout << "Yes\n";
    for (int i = 1; i < n; i++) cout << (ans[x[i]] ^ ans[y[i]]) << " \n"[i == n - 1];
    return 0;
}
```

---

## 作者：simonG (赞：0)

这个题也就是把区间和的限制搬到树上。设 $s_u$ 表示 $u$ 到根的异或和。不妨用带权并查集，$u\to v$ 路径权值给定为 $w$ 的话，那么 $s_u\otimes s_v=w$。然后我们可以通过带权并查集维护出若干连通块，同时可以判断无解的情况。

我们现在要求的是 $a_i$ 异或的和，如何用 $s_u$ 表示出来呢？设 $i=(u,v)$，那么 $a_i=s_u\otimes s_v$，所以只有奇度数点的 $s$ 是有贡献的。

那么如何填数值呢？由于每一位都独立，拆位去填，设一个连通块中该位是 $0$ 的有 $c_0$ 个，$1$ 有 $c_1$ 个。如果根填 $0$，那么值是 $c_1$。若填 $1$，那么值是 $c_0$。后续调整即可。具体地，默认填 $0$，之后把无论怎么填都是 $1$ 的用可以填出 $0,1$ 的去抵消。

复杂度 $O(n\log nV)$，其中 $V$ 是值域。
 

```cpp
#include<algorithm>
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<map>
using namespace std;
const int N=2.5e5+10;
int n,m,fa[N],dis[N],cnt,z[N],c[N][2],ans[N],res[N],ret[N];
bool op[N];
vector<int> e[N],s[N];
map<pair<int,int>,int> mp;
int getf(int x) {
	if(fa[x]==x) return x;
	int t=getf(fa[x]);
	dis[x]^=dis[fa[x]];
	return fa[x]=t;
}
void dfs(int u,int fa) {
	for(int v:e[u]) if(v!=fa) {
		int i=mp[{u,v}];
		ret[i]=ans[u]^ans[v];
		dfs(v,u);
	}
}
int main() {
	scanf("%d%d",&n,&m);
	for(int i=1,x,y; i<n; i++) {
		scanf("%d%d",&x,&y);
		e[x].push_back(y); e[y].push_back(x);
		mp[{x,y}]=mp[{y,x}]=i;
	}
	for(int i=1; i<=n; i++) fa[i]=i,dis[i]=0;
	for(int i=1; i<=m; i++) {
		int x,y,z; scanf("%d%d%d",&x,&y,&z);
		int fx=getf(x),fy=getf(y);
		if(fx==fy) {
			if(dis[x]^dis[y]^z) return printf("NO\n"),0;
		} else fa[fx]=y,dis[fx]=dis[x]^z;
	}
	for(int i=1; i<=n; i++) op[i]=e[i].size()&1;
	for(int i=1; i<=n; i++) s[getf(i)].push_back(i);
	for(int i=1; i<=n; i++) if(s[i].size()) z[++cnt]=i;
	for(int t=0; t<=30; t++) {
		for(int j=1; j<=cnt; j++) {
			int i=z[j];
			c[j][0]=c[j][1]=0;
			for(int u:s[i]) if(op[u])
				c[j][(dis[u]>>t)&1]^=1;
			res[j]=0;
			swap(c[j][0],c[j][1]);
		}
		int t1=0,t2=0;
		for(int j=1; j<=cnt; j++) {
			if(c[j][0]==0&&c[j][1]==1) t1=j;
			if(c[j][0]==1&&c[j][1]==0) t1=j,res[j]=1;
			if(c[j][0]&&c[j][1]) t2=t2?0:j;
		}
		if(t2&&t1) res[t1]^=1;
		for(int j=1; j<=cnt; j++) {
			int i=z[j];
			for(int u:s[i]) ans[u]|=(((dis[u]>>t)&1)^res[j])<<t;
		}
	}
	dfs(1,1);
	printf("YES\n");
	for(int i=1; i<n; i++) printf("%d ",ret[i]);
	printf("\n");
	return 0;
}
```

---

## 作者：SegTree (赞：0)

### 题意

$n$ 个结点的树，边有权，有 $q$ 条限制 $(x,y,w)$ 表示 $x$ 到 $y$ 这条链上的边权异或值为 $w$。

请构造边权，并最小化所有边权异或最小值。若无解输出 `No`。

### 题解
首先将“链上边权异或值”转化成用 $s_u$ 表示根到 $u$ 的路径异或值。

问题等价于：$q$ 条限制，每条形如 $s_x\oplus s_y=w$。

想到按位考虑，每次问题就等价于 $01$ 序列满足 $a_x\oplus a_y=w(w\in[0,1])$ 的问题。这个问题直接染色即可。

下面考虑怎么最小化边权异或值。

所有边权异或值等于 $s_i\oplus s_{fa_i}$ 的异或值。观察这个式子，发现对答案造成贡献当且仅当它有偶数个儿子，并且必须满足 $s_{rt}=0$。

于是，每次染完后记录 $c_1$ 和 $c_2$ 表示这一组染完对答案有贡献且染色为 $0$ 和 $1$ 的点数。你可以让它不变或者把颜色为 $0$ 的集和颜色为 $1$ 的集进行交换。

因为要尽可能最小化，所以需要让颜色为 $1$ 的点数和尽量为偶数。

分讨一下：

+ $c_1$ 和 $c_2$ 具有相同的奇偶性，那么你交换集显然没有意义。/该组中有根不能交换。

+ $c_1$ 和 $c_2$ 具有不同的奇偶性。

对于第二种情况，我们把上面的东西求出来已经染过的颜色为 $1$ 且对答案有贡献的点数。

+ 如果是偶数，若 $c_1$ 为偶数不变，否则交换。

+ 如果是奇数找出任意一组同组被染掉的点若 $c_1$ 为奇数不变否则交换（把上面的反过来），剩下就可以按照偶数情况搞了。

[Record](https://codeforces.com/contest/1788/submission/231555500)。

---

