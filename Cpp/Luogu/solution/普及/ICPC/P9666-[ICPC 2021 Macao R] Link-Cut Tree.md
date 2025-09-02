# [ICPC 2021 Macao R] Link-Cut Tree

## 题目描述

宝宝刚刚学会使用一种称为“链接切割树”的数据结构来寻找图中的环，并决定尝试一下。宝宝得到一个有 $n$ 个顶点和 $m$ 条边的无向图，其中第 $i$ 条边的长度为 $2^i$。她需要找到一个长度最小的简单环。

一个简单环是原始图的一个子图，包含 $k$ ($3 \le k \le n$) 个顶点 $a_1, a_2, \cdots, a_k$ 和 $k$ 条边，使得对于所有 $1 \le i \le k$，在子图中存在一条边连接顶点 $a_i$ 和 $a_{(i \mod k) + 1}$。简单环的长度是环中边的总长度。

## 说明/提示

第一个样例测试用例如下。边旁边的整数是它们的索引（括号外）和长度（括号内）。长度最小的简单环由边 $2$、$4$、$5$ 和 $6$ 组成，其长度为 $2^2 + 2^4 + 2^5 + 2^6 = 116$。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
2
6 8
1 2
2 3
5 6
3 4
2 5
5 4
5 1
4 2
4 2
1 2
4 3```

### 输出

```
2 4 5 6
-1```

# 题解

## 作者：Nightsky_Stars (赞：9)

# 题目大意

给一个 $n$ 个点 $m$ 条边的无向图，按照输入顺序，第 $i$ 条边的权值 $2^i$，找出一个长度 $s \ge 3$ 的**简单环**，使权值最小，并按升序输出构成这个简单环的边的的编号。若无解则输出 $-1$。

# 思路

考虑贪心，从小到大枚举每条边的边权。

由于 $\sum_{i=1}^n2^i \le 2^{n+1}$，所以贪心成立。

使用 Kruskal 算法，一边输入一遍处理，用并查集维护，若并查集查到属于同一联通块时，就说明出现了环，此时用 dfs 找到这个环输出。

# CODE:
```
#include<bits/stdc++.h>
using namespace std;
int m,n,T,fa[2500010];
struct edge{
	int u,v;
}g[100010];
vector<int> s;
vector<edge> e[100010];
inline int find(int x){//并查集
	if(x!=fa[x]){
		fa[x]=find(fa[x]);
	}
	return fa[x];
}
inline void join(int x,int y){
	int fx=fa[x],fy=fa[y];
	if(fx!=fy) fa[fx]=fy;
	else return ;
}
inline int read(){
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
inline void write(){//升序输出
	sort(s.begin(),s.end());
	for(int i=0;i<s.size();i++){
		cout<<s[i]<<" ";
	}
	cout<<"\n";
	return ;
}
inline void init(){
	s.clear();
	for(int i=1;i<=m;i++){
        g[i].u=g[i].v=0;
    }
	for(int i=1;i<=n;i++){
		fa[i]=i;
		e[i].clear();
	}
}
inline bool dfs(int x,int now,int f){//dfs求环
	if(now==x) return 1;
	for(auto to:e[now]){// 遍历 now 的所有边
		if(to.u==f) continue;
		s.push_back(to.v);
		if(dfs(x,to.u,now)) return 1;
		s.pop_back();
	}
	return 0;
}
inline void kruskal(){
	for(int i=1;i<=m;i++){
		if(find(g[i].u)==find(g[i].v)){//如果查询并查集在同一联通块内
			if(dfs(g[i].v,g[i].u,g[i].u)){
				s.push_back(i);
				write();
				break;
			}
			continue;
		}
		e[g[i].u].push_back((edge){g[i].v,i});
		e[g[i].v].push_back((edge){g[i].u,i});
		join(find(g[i].u),find(g[i].v));//合并
		if(i==m) cout<<"-1\n";
	}
}
int main(){
	T=read();
	while(T--){
		n=read();
		m=read();
		init();//多组测试数据，记得清空
		for(int i=1;i<=m;i++){
			g[i].u=read();
			g[i].v=read();
		}
		kruskal();
	}
	return 0;
}
```


---

## 作者：推翻暴政 (赞：8)

# P9666 [ICPC2021 Macao R] Link-Cut Tree 题解

[题目链接](https://www.luogu.com.cn/problem/P9666)

## 题目大意

$t$ 组数据，每组数据给出一张无向图的点的数量 $n$，边的数量 $m$，按照输入顺序的第 $i$ 条边的边权为 $2^i$ ，要求找到一个边数大于等于 $3$ 的简单环，使得边权最小化，按照升序输出构成这个简单环的边的序号，若无解输出 $-1$。

## 思路

考虑贪心，类比 kruskal 求最小生成树的思路，每次加入边权最小的边，判断是否能构成环即可。由于  $\sum\limits_{i=1} ^n 2^i = 2^{n+1}-1$ 可以得出贪心策略正确，即即使选了 $1 \sim n$ 的所有边都优于选第 $n+1$ 条边。

在代码实现上我们仍然考虑类比 kruskal 算法，按输入顺序即边权升序依次加入边，用并查集维护，若并查集查到属于同一联通块时就说明加入当前这条边会形成一个简单环，此时用 dfs 找到这个环即可。

时间复杂度在找环处为 $O(m \alpha(n))$，在输出时由于使用 sort 排序所以为 $O(n \log n)$，整体时间复杂度为 $O(n \log n)$。

**注意：并查集初始化，多测清空，升序输出。**

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=100005;
int t,n,m,fa[MAXN];
struct edge{//选边前的图
    int x,y;
} e[MAXN];
vector<int> v;//存最终答案
vector<edge> ed[MAXN];//选边后的图
inline int get(int x){//并查集查询操作
    if(fa[x]==x)  return x;
    return fa[x]=get(fa[x]);
}
inline bool solve(int rt,int now,int fath){//dfs 找环
    if(now==rt)  return 1;
    for(edge E:ed[now]){
        int to=E.x,val=E.y;
        if(to==fath)  continue;
        v.push_back(val);
        if(solve(rt,to,now))  return 1;
        v.pop_back();
    }
    return 0;
}
inline void write(){//升序输出
    sort(v.begin(),v.end());
    for(int i:v){
        printf("%d ",i);
    }
    puts("");
    return;
}
int main(){
    scanf("%d",&t);
    while(t--){
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++){//注意多测清空和并查集初始化
            ed[i].clear();
            fa[i]=i;
        }
        for(int i=1;i<=m;i++){
            scanf("%d%d",&e[i].x,&e[i].y);
        }
        for(int i=1;i<=m;i++){//选边过程
            int x=get(e[i].x),y=get(e[i].y);
            if(x==y){//如果查询并查集在同一联通块内
                if(solve(e[i].y,e[i].x,e[i].x)){
                    v.push_back(i);
                    write();
                    break;
                }
                continue;
            }
            ed[e[i].x].push_back((edge){e[i].y,i});//建新图便于 dfs
            ed[e[i].y].push_back((edge){e[i].x,i});
            fa[x]=y;//合并并查集
            if(i==m)  puts("-1");
        }
        v.clear();//注意多测清空
        for(int i=1;i<=m;i++){
            e[i].x=e[i].y=0;
        }
    }
    return 0;
}
```

感谢您的阅读，点个赞再走吧~



---

## 作者：SunnyYuan (赞：5)

本题解力求使用简单易懂的文字阐述道理。

## 思路

首先，我们可以推导出 $2^1 + 2^2 + 2^3 + \cdots + 2^i = 2^{i + 1} - 1 < 2^{i + 1}$，说明我们就是选择了第 $i + 1$ 条边前面的所有 $i$ 条边，也不会去选第 $i + 1$ 条边这一条边。

所以，我们要尽量往小的选，从小到大枚举边，只要什么时候形成了环，就退出。

我使用的是并查集判断环，然后题目要求输出环上的所有边，我用了 dfs 来找环。

是不是很简单呢？

## 代码

代码注释写的很详细，大家应该能看懂。

```cpp
/*******************************
| Author:  SunnyYuan
| Problem: P9666 [ICPC2021 Macao R] Link-Cut Tree
| Contest: Luogu
| URL:     https://www.luogu.com.cn/problem/P9666
| When:    2023-09-28 21:55:19
| 
| Memory:  256 MB
| Time:    2000 ms
*******************************/

#include <bits/stdc++.h>

using namespace std;
using PII = pair<int, int>;             // first : 点， second : 边的索引

const int N = 100010;

void solve() {
    int n, m;
    cin >> n >> m;

    vector<int> fa(n);
    vector<vector<PII> > e(n);          // 并查集
    vector<int> path;                   // 记录路径

    iota(fa.begin(), fa.end(), 0);      // 为 fa 赋值为 0 1 2 ... n - 1

    auto find = [&](auto f, int x) -> int {// 找并查集的根
        if (x == fa[x]) return x;
        return fa[x] = f(f, fa[x]);
    };

    auto dfs = [&](auto f, int u, int fa, int des) -> bool {// 找环
        if (u == des) return true;      // 形成环，返回 true
        for (auto to : e[u]) {          // 遍历 u 的所有边
            if (to.first == fa) continue;// 不能走回去
            path.push_back(to.second);  // 记录边的索引
            if (f(f, to.first, u, des)) return true;// 找到答案，不用继续搜索
            path.pop_back();            // 复原
        }
        return false;                   // 没找到 qwq
    };

    bool ok = false;                    // 是否已经找到答案
    for (int i = 1, u, v; i <= m; i++) {
        cin >> u >> v;
        if (ok) continue;               // 已经找到，但是也要让 cin 跑完
        u--, v--;
        e[u].push_back({v, i});         // 建图
        e[v].push_back({u, i});
        int fx = find(find, u), fy = find(find, v);// 并查集操作
        if (fx == fy) {                 // 同根，找到环
            path.push_back(i);          // 当前这条边也不能丢哦
            dfs(dfs, u, v, v);          // 找环
            ok = true;                  // 标记已经成功了
        }
        fa[fx] = fy;                    // 合并
    }
    if (ok) {
        sort(path.begin(), path.end());         // 按照题目要求从小到大输出
        for (int i = 0; i < path.size(); i++) cout << path[i] << " \n"[i == path.size() - 1];
    }
    else cout << "-1\n";                // 没找到 qwq
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;                              // T 组数据
    cin >> T;
    while (T--) solve();
    return 0;
}
```

---

## 作者：Lian_zy (赞：3)

# 0 题目传送门 & 前置芝士
## · 题目传送门
[题目传送门](https://www.luogu.com.cn/problem/P9666)

## · 前置芝士
首先，你要会一些图论和最小生成树。

如果你不会生成树，[板子见](https://www.luogu.com.cn/problem/P3366)！

# 1 题目翻译
给定一张 $n$ 个点 $m$ 条边的无向图，第 $i$ 个被输入的边边权为 $2^i$。现在让你找出一个环（如果环的长度为 $k$，则 $k \geqslant 3$ ），使得环上的总边权最小，并按升序输出每条边在输入顺序中的编号若不存在这样的简单环，输出 $-1$。

注意本题有**多组数据**！ 

# 2 题目分析
本题使用 贪心 解决。

观察题面，我们可以发现本题类似最小生成树，不过题目要求的是最小生成环（自己瞎取的名字）。

由于 $\sum\limits_{i=1}^{n} 2^i \le 2^{n + 1}$，即选择第 $n + 1$ 不如选择 $1 - n$ 的所有边，所以贪心成立。

一边输入一边处理，当输入边时 $(x_i, y_i)$  发现 $x$ 点与 $y$ 点联通，则说明出现了环，此时需要 dfs 找到环输出。

## · DFS 代码

``` cpp
bool dfs(int rt, int now, int f) {  
	if (now == rt) return true;
	for (auto v : G[now]) {
		if (v.x == f) continue;
		answer.push_back(v.y);
		if (dfs(rt, v.x, now)) return true;
		answer.pop_back();
	}
	return false;
}
```

如果所有边加入以后依然没满足条件，则直接输出 `-1`。

注意：即便已经知道了答案也不能 `break`，这样的话会影响后面的输入、

# 3 代码时间
~~莫抄袭，没了 AC 记录，空悲切。~~

``` cpp
#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxn = 1e5 + 10;
struct node {
	int x, y;
} a[maxn];
vector<int> answer;
vector<node> G[maxn];
int T, n, m, u, v, x, y, fa[maxn];
int findRt(int x) {
	if (fa[x] == x) return x;
	return fa[x] = findRt(fa[x]);
}
bool dfs(int rt, int now, int f) { //dfs求环，顺便把节点编号弄进 answer里。 
	if (now == rt) return true;
	for (auto v : G[now]) {
		if (v.x == f) continue;
		answer.push_back(v.y);
		if (dfs(rt, v.x, now)) return true;
		answer.pop_back();
	}
	return false;
}
void write() {
    sort(answer.begin(), answer.end());
    for (int i : answer) printf("%d ", i);
    putchar(10);
    return;
}
int main() {
	scanf("%d", &T);
	while (T--) {
		fa[0] = 0; 
		answer.clear(); //多组测试数据，记得清空，我就是被这个坑了一次
		scanf("%d %d", &n, &m);
		for (int i = 1; i <= n; i++) {
			fa[i] = i;
			G[i].clear();
		}
		for (int i = 1; i <= m; i++) {
			scanf("%d %d", &a[i].x, &a[i].y);
			if (fa[0]) continue; //用fa[0]当标记，fa[0]=1时已经有解，跳过了 
			x = findRt(a[i].x);
			y = findRt(a[i].y);
			if (x == y) {
				if (dfs(a[i].y, a[i].x, a[i].x)) {
					answer.push_back(i); //注意第 i 条边也要选 
					write();
					fa[0] = 1; //标记 
				}
				continue;
			}
			G[a[i].x].push_back(node{a[i].y, i});
			G[a[i].y].push_back(node{a[i].x, i});
			fa[x] = y;
			if (i == m) puts("-1");//无解情况考虑 
		} 
	}
	return 0;
}
```

---

## 作者：HFanGDoDM (赞：2)

## 前置知识

图论基础、[Kruskal 算法求最小生成树](https://www.luogu.com.cn/problem/P3366)

# 题意简述

给定一张 $n$ 个点 $m$ 条边的无向图，边有边权，其中在输入顺序中的第 $i$ 条边 $(u_i,v_i)$ 的边权为 $2^i$。试在该图上找出一个长度 $k\geqslant 3$ 的 **简单环**，要求 **最小化** 环的总边权，并按升序输出每条边在输入顺序中的编号。若不存在这样的简单环，输出 $-1$。

**数据范围**

**有多组测试数据**。对于每组测试数据，$3\leqslant n\leqslant 10^5$，$1\leqslant m \leqslant 10^5$，$1\leqslant u_i,v_i\leqslant n$，不存在自环或重边。对于所有测试数据，$\sum n,\sum m\leqslant 10^6$。

# 解题思路

我们考虑贪心思路，**从小到大枚举每条边的边权**。

我们假设有一张图，其等于原图去掉所有的边，仅保留原图的所有结点。当我们枚举到原图上的一条边时，我们将它加入新图，并判断此时该图中是否存在一个长度 $k\geqslant 3$ 的简单环。若不存在，则继续加入边；若存在，则这个简单环就是原图中总边权最小的一个环。

若原图中的所有边都加入新图，而新图中仍不存在环，则无解。

**正确性证明**

对于无解的情况，此时新图与原图完全相同，新图中不存在环证明 **原图中不存在环**，则也不存在长度 $k\geqslant 3$ 的环，必然无解。

对于有解的情况：

当我们第一次找到环时，在加入这条边之前，**新图中不存在环**。

对于在其之后加入的边，若加入这条边之后，能够形成新的环，则该环必然包含这条边。

设第一次找到的环长度为 $k$，其边的编号分别为 $a_1,a_2,a_3,...,a_k$；在其之后加入的一条新边的编号为 $x$，加入这条新边后产生的新环长度为 $l$，其边的编号分别为 $b_1,b_2,b_3,...,b_l$。设编号为 $i$ 的边的边权为 $w_i$，则 $w_i=2^i$。**容易发现，$a_1,a_2,a_3,...,a_k$ 互不相同**。

设第一次找到的环与之后产生的新环的边权总和分别为 $C_1,C_2$，则

$$C_1=\displaystyle{\sum_{i=1}^kw_{a_i}}=\displaystyle{\sum_{i=1}^k2^{a_i}}$$

$$C_2=\displaystyle{\sum_{i=1}^lw_{b_i}}=\displaystyle{\sum_{i=1}^l2^{b_i}}$$

根据上述定义，我们可以推出：

$$\forall i\in\{1,2,3,...,k\},a_i\lt x\implies\forall i\in\{1,2,3,...,k\}, 2^{a_i}\lt 2^x$$

$$\implies \displaystyle{\sum_{i=1}^k2^{a_i}}\lt 2^x$$

且

$$\exists j\in \{1,2,3,...,l\},b_j=x$$

因此

$$C_1=\displaystyle{\sum_{i=1}^k2^{a_i}}\lt 2^x=2^{b_j}\lt2^{b_j}+\displaystyle{\sum_{i=1,i\not=j}^l2^{b_i}}=\displaystyle{\sum_{i=1}^l2^{b_i}}=C_2$$

**即证**

$$C_1\lt C_2$$

因此我们的贪心策略是正确的。

**具体实现**

容易发现，上述的贪心过程与 **使用 Kruskal 算法求最小生成树** 的过程高度相似。

我们模拟这一算法的过程，当我们加入一条边 $(u_i,v_i)$ 时，若 $u_i$ 与 $v_i$ 已经连通，说明我们已找到符合题意的环。此时，在当前的新图上的 $u_i$ 所在的树中，通过从点 $u_i$ 开始 DFS，预处理这棵树上每个点的父亲及每个点与其父亲连边的编号，然后直接从点 $v_i$ 开始往上跳到点 $u_i$ ，最后加上当前枚举的这条边即可。

若所有边加入完之后都不存在上述情况，则输出 `-1`。

由于要求升序输出，最后需要对答案数组 $\operatorname{sort}$ 一遍。

**注意多测的清零有关问题。**

**时间复杂度分析**

使用 Kruskal 算法，借助并查集求最小生成树，枚举边的过程复杂度为 $O(m\alpha(n))$；DFS 一遍，寻找 $u_i$ 与 $v_i$ 的简单路径的复杂度为 $O(n)$；对答案数组排序，复杂度为 $O(n\log n)$ 或 $O(n+m)$（因具体实现而异）。其中 $\alpha(n)$ 为并查集复杂度。

总时间复杂度为 $O(\sum (n+m\alpha(n)))$ 或 $O(\sum (n\log n))$。

**参考核心代码**

```cpp
int hd[N],pr[N<<1],e[N<<1],w[N<<1],scnt,fa[N],wfa[N],dep[N];//这里wfa[i]记录的是结点i到它的父亲的那条边的编号
vector<int>ans;
......
void DFS(int u,int fath){
	fa[u]=fath;
	dep[u]=dep[fath]+1;
	for(int s=hd[u];s;s=pr[s]){
		int v=e[s];
		if(v==fath)
			continue;
		wfa[v]=w[s];
		DFS(v,u);
	}
}
void Find(int x,int y){
	if(dep[x]<dep[y])
		swap(x,y);
	while(dep[x]>dep[y]){
		ans.push_back(wfa[x]);
		x=fa[x];
	}
	if(x==y)
		return;
	while(x!=y){
		ans.push_back(wfa[x]),ans.push_back(wfa[y]);
		x=fa[x],y=fa[y];
	}
}
......
	bool flg=false;
	for(i=1;i<=m;i++){
		int u=R(),v=R();
		if(!dsu.Union(u,v)){//并查集中发现u和v已经在同一集合内，则返回false
			DFS(u,0);
			Find(u,v);//找到u和v之间的简单路径，并将路径上各边的编号存入答案数组
			ans.push_back(i);//不要忘了新加入的这条边
			Output();
			flg=true;
			break;
		}
		AddSide(u,v,i),AddSide(v,u,i);
	}
	if(!flg){
		puts("-1");
		return;
	}
```

---

## 作者：dlzlj_2010 (赞：1)

因为 $\sum\limits_{i=1}^{n-1}2^i<2^n$，所以即使选上第 $n$ 条边前面所有边的权值也小于第 $n$ 条边的权值，考虑贪心，从小到大枚举每一条边的边权，有环就立即搜索出环然后输出。
## code:
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
const int N=1e5+5,M=2e5+5;
int fa[N];//并查集
struct node{
	int v,id;//边的指向节点和边的编号
};
vector<int>ans;//结果
vector<node> e[N];//邻接表
int n,m;
int T;
void init(){//多测不清空，爆零两行泪
	ans.clear();
	for(int i=1;i<=n;i++){
		fa[i]=i,e[i].clear();
	}
}
int find(int x){
	if(fa[x]==x)return x;
	return fa[x]=find(fa[x]);
}
void unionn(int u,int v){
	u=find(u),v=find(v);
	if(u!=v)fa[u]=v;
}
bool dfs(int bg,int u,int f){//搜索环
	//bg:环的起点;u:当前结点;f:当前结点的前驱结点
	for(auto [v,i]:e[u]){//枚举出边
		if(v==f)continue;
		if(v==bg){//回到起点，说明搜出了整个环
			ans.push_back(i);
			return 1;
		}
		ans.push_back(i);//加入当前边
		if(dfs(bg,v,u))return 1;//如果后面搜出了环就直接返回
		ans.pop_back();//否则就说明该边不在环中
	}
	return 0;
}
signed main(){
	cin>>T;
	while(T--){
		cin>>n>>m;
		init();
		bool f=0;//是否有环
		for(int i=1;i<=m;i++){
			int u,v;
			cin>>u>>v;
			if(f)continue;//如果已经找到环就不做处理
			e[u].push_back({v,i});
			e[v].push_back({u,i});
			if(find(u)!=find(v)){//不在同一连通块内，说明还没有环
				unionn(u,v);
			}
			else{
				f=1;
				dfs(u,u,-1);//搜索找环
				sort(ans.begin(),ans.end());//要求升序输出
			}
		}
		if(f)
			for(auto i:ans)cout<<i<<" ";
		else cout<<-1;
		puts("");
	}
    return 0;
}
```

---

## 作者：zjj2024 (赞：0)

### 思路

由于边的权值均是 $2$ 的正整数次方，所以，相当于让环中权值最大的边权值最小。

可以在遍历每一条边时用并查集维护图中是否有环，只需要判断两端是否在同一个连通块即可。

考虑在没有环时将已经遍历的边建成一棵树，等到有一条边让树变得有环时，将其中一个点固定为树根，则两个点之间的路径和正在判断的这条边就是答案。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=100005;
struct T
{
	int ne,to,v;
}e[2*N];
int fa[N],he[N],idx,n,m,x[N],y[N];
int c[N],top,up[N],upv[N];//c表示答案的每一条边
//up表示每一个点的父亲，upv表示每个点到其父亲节点的权值（只计算指数）
void add(int x,int y,int z)//使用链式前项星建树
{
	e[++idx].ne=he[x];
	e[idx].to=y;
	e[idx].v=z;
	he[x]=idx;
}
int find(int x)//并查集
{
	if(x==fa[x])return x;
	return fa[x]=find(fa[x]);
}
void dfs(int u,int father,int v)//得到当前树上的每个节点的up和upv
{
	up[u]=father;
	upv[u]=v;
	for(int i=he[u];i;i=e[i].ne)
	{
		int y=e[i].to;
		if(y==father)continue;
		dfs(y,u,e[i].v);
	}
}
void run()
{
	for(int i=1;i<=m;i++)
	{
		int xx=find(x[i]),yy=find(y[i]);
		if(xx==yy)
		{
			dfs(x[i],0,0);//x[i]一定在当前树中，以x[i]或y[i]为根可以省去一些步骤
			top=0;
			c[++top]=i;
			int s=y[i];
			while(s!=x[i])//的到x[i]到y[i]之间的每一条边
			{
				c[++top]=upv[s];
				s=up[s];
			}
			sort(c+1,c+top+1);//按从小到大的顺序
			for(int i=1;i<=top;i++)
				cout<<c[i]<<' ';
			cout<<'\n';
			return;
		}
		fa[xx]=yy;
		add(x[i],y[i],i);//建树
		add(y[i],x[i],i);
	}
	cout<<"-1\n";
	return;
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int T;
	cin>>T;
	while(T--)
	{
		cin>>n>>m;
		for(int i=1;i<=m;i++)
			cin>>x[i]>>y[i];
		for(int i=1;i<=n;i++)fa[i]=i;//并查集初始化
		run();
		memset(he,0,sizeof(he));//多测清空
		idx=0;
	}
	return 0;
}
```

---

## 作者：wizard（偷开O2 (赞：0)

一道挺好的最小生成树的题目。

### 题意

求出一个有 $n$ 个点，$m$ 条边，第 $i$ 条边的权值为 $2^i$ 的无向图的最小环。

### 分析

这本质上其实不是一道纯的生成树，我们只是利用克鲁斯卡尔思想不断地往当前图中加最小边，最后判断能不能形成环。

我们利用深搜求环的思想是：从出发点开始搜，遍历出发点的所有出边，搜到最后可以回到原点的就是环。

```cpp
bool dfs(int x,int now,int fath){//出发点，当前点，当前点的父节点
	for(auto to:g[now]){
		if(to.x==fath){
			continue;
		}
		ans.push_back(to.y);//试探处理
		if(dfs(x,to.x,now)){
			return 1;
		}
		ans.pop_back();//撤
	}
    if(now==x){
		return 1;
	}
	return 0;
}
```

遍历所有边，如果构成该边的两节点在一个联通分量中，就可以直接开始判环了。

因为我们是顺序遍历，且边权大小是随着边的编号递增的，所以先遇到的环一定是最小环，就没有再对后面的图进行遍历的必要了。

遍历到最后没找到环，直接输出 $-1$ 即可。

最后注意题目要求，构成环的节点编号要顺序输出。

注意多测清空！！

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=1e6+10;
struct node{
	int x,y;
}e[maxn];
/*bool cmp(node a,node b){
	return a.z<b.z;
}*/
int n,m;
int fa[maxn],cnt,ans;
int find(int x){
	while(x!=fa[x]){
		x=fa[x]=fa[fa[x]];
	}
	return x;
}
vector <int> s;
vector <node> g[maxn];
bool dfs(int x,int now,int fath){//出发点，当前点，当前点的父节点
	for(auto to:g[now]){
		if(to.x==fath){
			continue;
		}
		s.push_back(to.y);
		if(dfs(x,to.x,now)){
			return 1;
		}
		s.pop_back();
	}
    if(now==x){
		return 1;
	}
	return 0;
}
void kruskal(){
	for(int i=1;i<=m;i++){
		int now=find(e[i].x);
		int to=find(e[i].y);
		if(to==now){
			if(dfs(e[i].y,e[i].x,e[i].x)){
				s.push_back(i);
				sort(s.begin(),s.end());
				for(int i=0;i<(int)s.size();i++){
					cout << s[i] << " ";
				}
				cout << endl;
				break;
			}
			continue;
		}
		g[e[i].x].push_back((node){e[i].y,i});
		g[e[i].y].push_back((node){e[i].x,i});
		fa[now]=to;
		if(i==m){
			cout << -1 << endl;
		}
	}
}
int dex;
signed main(){
	int T;
	cin >> T;
	while(T--){
		cin >> n >> m;
		s.clear();
		for(int i=1;i<=m;i++){
			e[i].x=e[i].y=0;
		}
		for(int i=1;i<=n;i++){
			fa[i]=i;
			g[i].clear();
		}
		for(int i=1;i<=m;i++){
			cin >> e[i].x >> e[i].y;
		}
		kruskal();
	}
	return 0;
}

```

---

## 作者：Flaw_Owl (赞：0)

# P9666 [ICPC2021 Macao R] Link-Cut Tree 题解

题目连接：[P9666 [ICPC2021 Macao R] Link-Cut Tree](https://www.luogu.com.cn/problem/P9666)

## 题目分析

注意到题目说第 $i$ 条边的权值为 $2^i$，并且题目要求找到一个权值最小的环。这是一个非常经典的**贪心**，一般以二进制的形式出现。它的关键在于：

$$ \sum_{i=1}^{n-1} 2^i < 2^n $$

因此，要找到这个权值最小的环，就尽量让它以较小的边组成。我们只要依次在图中加入这些边，并判断它是否能形成环即可。在这里，类似于**最小生成树**算法中的 **kruskal** 算法。

按照这个思路分析：在加入的过程中，为了判断其是否**成环**，可以用**并查集**实现；判断成环后所形成的环，可以用 **DFS** 实现。

## 参考代码

```cpp
#include <iostream>
#include <cctype>
#include <vector>
#include <algorithm>

using namespace std;

int read()
{
    int x = 0, f = 1;
    char ch = 0;
    while (!isdigit(ch))
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (isdigit(ch))
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

const int maxN = 1e5 + 5;

struct edge
{
    int from, to;
} g[maxN];

int T;
int n, m;
int x, y;

int fa[maxN];
vector<int> ans;
vector<edge> G[maxN];

void init()
{
    ans.clear();
    for (int i = 1; i <= m; i++)
        g[i].from = g[i].to = 0;
    for (int i = 1; i <= n; i++)
    {
        fa[i] = i;
        G[i].clear();
    }
}

int find_set(int x)
{
    return fa[x] == x ? fa[x] : fa[x] = find_set(fa[x]);
}

void merge_set(int x, int y)
{
    x = find_set(x), y = find_set(y);
    if (x != y)
        fa[x] = y;
}

bool DFS(int root, int now, int pre)
{
    if (now == root)
        return true;
    for (auto to : G[now])
    {
        if (to.from == pre)
            continue;
        ans.push_back(to.to);
        if (DFS(root, to.from, now))
            return true;
        ans.pop_back();
    }
    return false;
}

void write()
{
    sort(ans.begin(), ans.end());
    for (int i : ans)
        printf("%d ", i);
    printf("\n");
    return;
}

void kruskal()
{
    for (int i = 1; i <= m; i++)
    {
        x = find_set(g[i].from);
        y = find_set(g[i].to);
        if (x == y)
        {
            if (DFS(g[i].from, g[i].to, g[i].to))
            {
                ans.push_back(i);
                write();
                break;
            }
            continue;
        }
        G[g[i].from].push_back((edge){g[i].to, i});
        G[g[i].to].push_back((edge){g[i].from, i});
        merge_set(x, y);
        if (i == m)
            printf("-1\n");
    }
}

int main()
{
    T = read();
    while (T--)
    {
        n = read(), m = read();
        init();
        for (int i = 1; i <= m; i++)
            g[i].from = read(), g[i].to = read();
        kruskal();
    }
    return 0;
}
```

---

## 作者：Frozen_Ladybug (赞：0)

第一眼看到这道题没什么想法，后来发现可以用并查集来做。

### 题目大意

给定一个包含 $n$ 个点，$m$ 条变的图，图不一定联通；第 $i$ 条边的长度是 $2^i$。数据范围是 $10^6$，不会超出 ```int``` 范围。

我们要求长度最短的环的长度和它包含的边的编号。如果找不到环，输出 ```-1```。

### 思路

因为第 $i$ 条边的长度是 $2^i$，而

$$\displaystyle\sum^n_{i=1}2^i+1=2^{n+1}$$

所以前 $i-1$ 条边的长度加起来也比第 $i$ 条边短，所以我们尽量用前面的边来构成环。

那么如何判断是否存在环呢？我们从第一条一条地往图中加边，同时用并查集记录已经连在一起的点。

![](https://cdn.luogu.com.cn/upload/image_hosting/iqasguki.png)

一旦我们加入一条边时，发现它连接的两个点已经在一个并查集中了，那就说明把这条边加进去时，就存在了一条环。

这样就能找到第一次形成环时的那条边。用拓扑排序找到它即可。

### 代码

```c
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+5;
int T,n,m,head[maxn],cnt,fa[maxn],st,vis[maxn],cnt2,d[maxn],ans[maxn];
struct Edge{//记录每一条边
    int from,to,dis;//起点，终点和长度
    bool operator<(const Edge x)const{
        return dis<x.dis;
    }//重载运算符，方便sort
}e[maxn<<1],e2[maxn<<1];//两种边，第一种记录正常的边，第二种记录并查集中建立的边
struct Now{//记录当前点
    int val,point;//价值和编号
}now[maxn];
void add(int u,int v,int w){
    e[++cnt].from=u;
    e[cnt].to=v;
    e[cnt].dis=w;
}//建图用的边
void add2(int u,int v,int w){
    e2[++cnt2].from=head[u];
    e2[cnt2].to=v;
    e2[cnt2].dis=w;
    head[u]=cnt2;
}//并查集中的边
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}//找祖先
void bfs(){//广搜，找最优解
    queue<int> q;
    for(int i=1;i<=n;++i)
        if(d[i]==1) q.push(i);//没被访问，推入队列
    while(!q.empty()){//队列非空，即没有全访问
        int x=q.front();
        q.pop();
        for(int i=head[x];i;i=e2[i].from){
            d[e2[i].to]--;
            ans[e2[i].dis]=1;
            if(d[y]==1) q.push(y);
        }//按照相邻顺序检查访问
    }
}
int main(){
    scanf("%d",&T);
    while(T--){
        memset(head,0,sizeof(head));
        memset(vis,0,sizeof(vis));
        memset(ans,0,sizeof(ans));
        memset(d, 0, sizeof(d));
        cnt=cnt2=0;//清空
        scanf("%d%d",&n,&m);
        for(int i=1;i<=m;++i) {
            int x,y; 
            scanf("%d%d",&x,&y);
            add(x,y,i);//x和y这两个点之间有一条边，长度为i(2^i)
        }
        for(int i=1;i<=n;++i) fa[i]=i;//自己的祖先设为自己
        sort(e+1,e+1+m);//边从短到长排序
        bool f=0;
        for(int i=1;i<=m;++i) {
            int x=e[i].from,y=e[i].to,fx=find(x),fy=find(y);
            if(fx==fy){//x和y的祖先相同
                st=i;
                for(int j=1;j<=i;++j){
                    add2(e[j].from,e[j].to,e[j].dis);
                    add2(e[j].to,e[j].from,e[j].dis);
                    d[e[j].from]++;
                    d[e[j].to]++;
                }//在并查集中建边
                bfs();
                f=1;//能访问到，不需要继续查
                break;
            }
            fa[fx]=fy;//最后将fx的父节点设为fy
        }
        if(f){//如果能访问
            for(int i=1;i<=st;++i)
                if(!ans[i]){printf("%d",i++);break;}
            for(int i=1;i<=st;++i)
                if(!ans[i]) printf(" %d",i);
            printf("\n");//没有被访问的就是答案
        }
        else printf("-1\n");//没有答案，输出-1
    }
    return 0;
}
```

---

