# [ABC239F] Construct Highway

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc239/tasks/abc239_f

Atcoder 国には $ 1 $ から $ N $ の番号がついた $ N $ 個の街と $ 1 $ から $ M $ の番号がついた $ M $ 個の高速道路があります。  
 高速道路 $ i $ は街 $ A_i $ と街 $ B_i $ を双方向に結んでいます。

国王の高橋君は、新たに $ N-M-1 $ 本の高速道路を建設し、次の $ 2 $ つの条件をともに満たそうとしています。

- すべての街同士は、高速道路をいくつか通って互いに行き来できる
- 各 $ i=1,\ldots,N $ について、街 $ i $ はちょうど $ D_i $ 本の高速道路と直接つながっている

条件を満たすような建設方法が存在するか判定し、存在するなら $ 1 $ つ出力してください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\times\ 10^5 $
- $ 0\ \leq\ M\ \lt\ N-1 $
- $ 1\ \leq\ D_i\ \leq\ N-1 $
- $ 1\leq\ A_i\ \lt\ B_i\ \leq\ N $
- $ i\neq\ j $ ならば、$ (A_i,\ B_i)\ \neq\ (A_j,B_j) $
- 入力に含まれる値は全て整数である

### Sample Explanation 1

出力例のように、街 $ 6 $ と$ 2 $、街 $ 5 $ と $ 6 $、街 $ 4 $ と $ 5 $ をそれぞれ結ぶ高速道路を建設すると条件を満たすことができます。 この他にも、例えば 街 $ 6 $ と$ 4 $、街 $ 5 $ と $ 6 $、街 $ 2 $ と $ 5 $ を結ぶような高速道路を建設しても条件を満たすことができます。

## 样例 #1

### 输入

```
6 2
1 2 1 2 2 2
2 3
1 4```

### 输出

```
6 2
5 6
4 5```

## 样例 #2

### 输入

```
5 1
1 1 1 1 4
2 3```

### 输出

```
-1```

## 样例 #3

### 输入

```
4 0
3 3 3 3```

### 输出

```
-1```

# 题解

## 作者：rui_er (赞：4)

翻译：给定 $n,m$ 和度数数组 $\{d_i\}$，再给你 $m$ 条边，请构造一棵 $n$ 点的树包含这 $m$ 条边，且第 $i$ 个点的度数为 $d_i$，或者判断无解。

---

显然，若 $\sum d_i\ne 2(n-1)$，则无解。

然后对于输入的每条边，使用并查集维护，再求出在这 $m$ 条边的基础上每个点还需要多少度数（记作 $d_i$，注意下文 $d_i$ 的意义与输入不同）。

如果存在 $d_i < 0$，则无解。

然后考虑每个连通块，维护一个 vector 表示这个连通块中每个点还需要多少度数，若 $u$ 需要 $k$ 的度数就存 $k$ 个 $u$。

将所有连通块分为两类：需要度数 $1$、需要度数 $\ge 2$，下文分别称为“第一类”“第二类”。

第一类连通块显然要优先跟第二类连通块连（不然就不连通了）。我们枚举每个第二类连通块，假设这个连通块还需要 $d$ 的度数，那么拿出 $d-1$ 的度数连第一类连通块，剩下 $1$ 的度数会使得这个连通块被归入第一类中。

如果某一时刻第一类连通块不够了，就无解。如果所有第二类连通块都用完了，此时剩下超过 $2$ 个第一类连通块，就也无解。否则，此时会恰好剩下两个第一类连通块，连起来即可。最后判一下整个图是否连通，不连通还无解。否则输出即可。

这题无解情况挺多的，容易漏情况，写代码之前要想清楚。

```cpp
//By: OIer rui_er
#include <bits/stdc++.h>
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define debug(format...) fprintf(stderr, format)
#define fileIO(s) do{freopen(s".in","r",stdin);freopen(s".out","w",stdout);}while(false)
using namespace std;
typedef long long ll;

mt19937 rnd(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
int randint(int L, int R) {
	uniform_int_distribution<int> dist(L, R);
	return dist(rnd);
}

template<typename T> void chkmin(T& x, T y) {if(x > y) x = y;}
template<typename T> void chkmax(T& x, T y) {if(x < y) x = y;}

const int N = 2e5+5;

int n, m, deg[N];
vector<int> nds[N], nd1;
vector<vector<int>> nd2;
vector<tuple<int, int>> ans;

struct Dsu {
    int fa[N];
    void init(int x) {rep(i, 1, x) fa[i] = i;}
    int find(int x) {return x == fa[x] ? x : fa[x] = find(fa[x]);}
    bool same(int x, int y) {return find(x) == find(y);}
    bool merge(int x, int y) {
        if(same(x, y)) return false;
        x = find(x); y = find(y);
        fa[x] = y;
        return true;
    }
}dsu;

int main() {
	scanf("%d%d", &n, &m);
    rep(i, 1, n) scanf("%d", &deg[i]);
    if(accumulate(deg+1, deg+1+n, 0) != 2 * (n - 1)) return puts("-1")&0;
    dsu.init(n);
    rep(i, 1, m) {
        int u, v;
        scanf("%d%d", &u, &v);
        dsu.merge(u, v);
        --deg[u]; --deg[v];
        if(deg[u] < 0 || deg[v] < 0) return puts("-1")&0;
    }
    rep(i, 1, n) rep(j, 1, deg[i]) nds[dsu.find(i)].push_back(i);
    rep(i, 1, n) {
        if((int)nds[i].size() == 1) nd1.push_back(nds[i][0]);
        if((int)nds[i].size() > 1) nd2.push_back(nds[i]);
    }
    for(auto&& i : nd2) {
        for(int j = 1; j < (int)i.size(); j++) {
            if(nd1.empty()) return puts("-1")&0;
            dsu.merge(i[j], nd1.back());
            ans.emplace_back(i[j], nd1.back());
            nd1.pop_back();
        }
        nd1.push_back(i[0]);
    }
    if((int)nd1.size() > 2) return puts("-1")&0;
    dsu.merge(nd1[0], nd1[1]);
    ans.emplace_back(nd1[0], nd1[1]);
    rep(i, 1, n) if(!dsu.same(i, 1)) return puts("-1")&0;
    for(auto&& [u, v] : ans) printf("%d %d\n", u, v);
	return 0;
}
```

---

## 作者：Mirasycle (赞：1)

首先必须满足 $\sum deg_i=2n-2$，在此基础上不能成环。

先讲述一下无边限制的做法。

思考一个顺序使得连出来的不成环，很容易想到按照“度数序”，即度数大的当度数小的父亲。一开始的想法是按照度数从小往大做，每个点通过成为 $d_i-1$ 个点的父亲来消耗它的度数，最后剩一个度数来连其父亲。不过这是一个粗略的想法，实现不好就是错的，首先观察出任意时刻必然有度数为 $1$ 的点，所以我们上述的做法根本不需要往下连边，只需要每次取度数为 $1$ 的点往上连即可。

思考如果有若干给定边会怎么样，一个点显然不能和已有联通块内 $\ge 2$ 个点连边，所以我们用并查集维护联通块，然后把一个联通块当成一个整体跑上述算法即可。


```cpp
#include<bits/stdc++.h>
#define fi first
#define se second
using namespace std;
typedef long long ll;
const int maxn=2e5+10;
int n,m,d[maxn],vis[maxn]; ll sum=0;
queue<int> q[maxn],q1,q2;
struct DSU{
	int fa[maxn];
	void init(){ for(int i=1;i<=n;i++) fa[i]=i; }
	int find(int u){ return u==fa[u]?u:fa[u]=find(fa[u]); }
	bool merge(int u,int v){
		int f1=find(u),f2=find(v);
		if(f1==f2) return 0;
		fa[f1]=f2; return 1;
	}
}dsu;
int main(){
	cin>>n>>m; dsu.init();
	for(int i=1;i<=n;i++) cin>>d[i],sum+=d[i];
	if(sum!=2*n-2){ cout<<"-1"; return 0; }
	for(int i=1;i<=m;i++){
		int u,v; cin>>u>>v;
		d[u]--; d[v]--;
		if(d[u]<0||d[v]<0||!dsu.merge(u,v)){ cout<<"-1"; return 0; } 
	}
	for(int i=1;i<=n;i++){
		int z=dsu.find(i); if(!vis[z]) vis[z]=1;
		if(d[i]) vis[z]=2;
		while(d[i]--) q[z].push(i);
	}
	for(int i=1;i<=n;i++)
		if(vis[i]==1){ cout<<"-1"; return 0; } 
	for(int i=1;i<=n;i++){
		if(q[i].empty()) continue;
		if(q[i].size()==1) q1.push(q[i].front());
		else q2.push(i);
	}
	while(q1.size()){
		if(q1.size()==2&&q2.empty()){
			cout<<q1.front()<<" "; q1.pop();
			cout<<q1.front()<<endl; return 0;
		}
		int u=q1.front(); q1.pop();
		int v=q2.front(); q2.pop();
		cout<<u<<" "<<q[v].front()<<endl; q[v].pop(); 
		if(q[v].size()==1) q1.push(q[v].front());
		else q2.push(v);
	}
	return 0;
}

```

---

