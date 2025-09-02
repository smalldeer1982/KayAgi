# Four Vertices

## 题目描述

You are given an undirected weighted graph, consisting of $ n $ vertices and $ m $ edges.

Some queries happen with this graph:

- Delete an existing edge from the graph.
- Add a non-existing edge to the graph.

At the beginning and after each query, you should find four different vertices $ a $ , $ b $ , $ c $ , $ d $ such that there exists a path between $ a $ and $ b $ , there exists a path between $ c $ and $ d $ , and the sum of lengths of two shortest paths from $ a $ to $ b $ and from $ c $ to $ d $ is minimal. The answer to the query is the sum of the lengths of these two shortest paths. The length of the path is equal to the sum of weights of edges in this path.

## 说明/提示

Before the queries you can choose vertices $ (a, b) = (3, 2) $ and $ (c, d) = (1, 4) $ . The sum of lengths of two shortest paths is $ 3 + 1 = 4 $ .

After the first query you can choose vertices $ (a, b) = (2, 5) $ and $ (c, d) = (1, 4) $ . The sum of lengths of two shortest paths is $ 2 + 1 = 3 $ .

After the second query you can choose vertices $ (a, b) = (3, 4) $ and $ (c, d) = (2, 5) $ . The sum of lengths of two shortest paths is $ 1 + 2 = 3 $ .

After the third query, you can choose vertices $ (a, b) = (2, 6) $ and $ (c, d) = (4, 5) $ . The sum of lengths of two shortest paths is $ 4 + 3 = 7 $ .

After the last query you can choose vertices $ (a, b) = (1, 6) $ and $ (c, d) = (2, 5) $ . The sum of lengths of two shortest paths is $ 3 + 2 = 5 $ .

## 样例 #1

### 输入

```
6 6
1 3 6
4 3 1
1 4 1
2 6 4
2 4 2
5 4 3
4
1 2 5 2
0 1 4
0 3 4
1 6 1 3```

### 输出

```
4
3
3
7
5```

# 题解

## 作者：dottle (赞：7)

我们称选取一条边指选取这条边的两个端点，设最小边端点为 $X$、$Y$，选取的方案应当只有以下三种：

1. 选取 $(X,Y)$，然后再选取另一条边（端点不能是 $X$ 或 $Y$）。
2. 以 $X$、$Y$ 为端点分别选取两条边。
3. 对于一个结点 $V$ 与和它有边相连的 $A,B,C$，选取 $(V,A)$，$(B,C)$。

可以证明，这样可以涵盖所有情况，我们现在考虑对这三者分别计算。

首先考虑第三种，这种是最简单的：我们按顺序维护每一个点的所有边，然后算出前三小的边的和即可。每当我们加入或删除一条边时，便更新这个答案。

然后考虑第一、二种，有一个性质：如果一条边在其任意一个端点的排名大于 $3$，则这条边不会出现在任何选取方案中。因为此时总可以找到一条边权比它小的边，其另一端没有被使用过。

有了这个性质就很好办了，我们考虑按维护集合 $A$ 和 $E_i$。 $A$ 中储存了所有可能成为答案的边，$E_i$ 中储存了以 $i$ 为端点的所有边。

计算第一种情况时，我们取出 $A$ 中最小的边，然后从小到大依次枚举其他边，若与最小边无公共端点，更新答案并退出。因为上述性质，这一步中我们至多会枚举到第 $4$ 条边。 

计算第二种情况是，我们在 $E_X,E_Y$ 中分别枚举前 $3$ 条边，若无公共端点就更新答案。

弄清楚了如何统计答案，我们现在考虑如何维护 $A$ 和 $E$。

每当加入一条边 $(u,v)$ 时，首先向 $E_u$ 和 $E_v$ 中插入此边，然后把 $E_u$，$E_v$ 中排名第四的边从 $A$ 中删除，再把 $E_u$，$E_v$ 中排名第三的边加入 $A$ 中。

删除时，首先将其从 $A$ 中删除，然后把 $E_u$，$E_v$ 中排名第三的边加入 $A$ 中，再从 $E_u$ 和 $E_v$ 中删除此边。

注意到我们上述过程有些随意，可能会删掉集合中不存在的边，或加入集合中已经存在的边。在加入和删除的时候稍微判断一下就可以了。

具体实现中，我们需要维护一个数据结构，支持按排名查询、插入和删除。使用 `__gnu_pbds::tree` 即可。

```cpp
#define TREE tree<node,null_type,less<node>,rb_tree_tag,tree_order_statistics_node_update>
struct node{
	int fr,to,w;
	bool operator <(const node b)const{
		return w!=b.w?w<b.w:fr!=b.fr?fr<b.fr:to<b.to;
	}
	bool operator ==(const node b)const{
		return w==b.w&&fr==b.fr&&to==b.to;
	}
	bool operator ^(node b){
		return fr!=b.fr&&fr!=b.to&&to!=b.to&&to!=b.fr;
	}// a^b = a 与 b 没有公共端点
}e[N];
TREE E[N],A,E3;//E3 数组其实是个 int 类型的，维护了每个节点的第三种情况的值
map<int,int> ln[N];
 
node gt(TREE&a,int k){
	return *a.find_by_order(k);
}
 
void add(TREE&a,node b){
	a.insert(b);// pbds 的树会自动去重
}
void del(TREE&a,node b){
	TREE::iterator nw=a.lower_bound(b);
	if(nw!=a.end()&&*nw==b)//如果要删的节点不存在，就不删
		a.erase(nw);
}
int id(TREE&a,node b){
	return a.order_of_key(b);
}
void ck3(int k){
	if(fl[k])del(E3,(node){0,0,fl[k]});fl[k]=0;
	if(E[k].size()>=3)fl[k]=gt(E[k],0).w+gt(E[k],1).w+gt(E[k],2).w;
	if(fl[k])add(E3,(node){0,0,fl[k]});
}
void tryadd(node nw){//若此边在两边排名都小于 3， 才可以加入
	if(id(E[nw.fr],nw)<=3&&id(E[nw.to],nw)<=3)
		add(A,nw);
}
void trydel(int k){// 删除 E[k] 的第四名
	if(E[k].size()>=4)del(A,gt(E[k],3));
}
 
void add(int fr,int to,int w){
	if(fr>to)swap(fr,to);
	node nw=(node){fr,to,w};
	add(E[fr],nw);
	add(E[to],nw);
	tryadd(nw);
	trydel(fr),trydel(to);
	ck3(fr),ck3(to);
	ln[fr][to]=w;
}

void del(int fr,int to){
	if(fr>to)swap(fr,to);
	int w=ln[fr][to];ln[fr][to]=0;
	del(E[fr],(node){fr,to,w});
	del(E[to],(node){fr,to,w});
	if(E[fr].size()>=3)tryadd(gt(E[fr],2));
	if(E[to].size()>=3)tryadd(gt(E[to],2));
	del(A,(node){fr,to,w});
	ck3(fr),ck3(to);
}
int calc(){
	int ans=1e17+7;
	if(E3.size())ans=min(ans,gt(E3,0).w);
	for(int i=1;i<A.size()&&i<10;i++)
		if(gt(A,0)^gt(A,i)){
			ans=min(ans,gt(A,0).w+gt(A,i).w);
			break;
		}//第一种
	node nw=gt(A,0);
	for(int i=0,P=E[nw.fr].size();i<min(P,4ll);i++)
		for(int j=0,Q=E[nw.to].size();j<min(Q,4ll);j++)
			if(gt(E[nw.fr],i)^gt(E[nw.to],j))
				ans=min(ans,gt(E[nw.fr],i).w+gt(E[nw.to],j).w);//第二种
	return ans;
}
```

稍微补充一下为什么这样算可以涵盖所有情况：对于所有选择两条边的方案，若某条边与最小边没有公共端点，则可以把另一条边换成最小边，即第一种情况；若两条边与最小边都有公共端点，即第二种情况；若选择三条边，则只能是第三种情况，否则可以缩短一条路径，答案不会更劣。大于三条边的方案显然劣。以上。

---

## 作者：happybob (赞：0)

看着就是怎么分讨一下。

大多数情况下你肯定希望选两条最小的边，但是这样的边可能有公共端点。

考虑记边权最小的边的端点为 $(u,v)$，考虑两种选择方式：

1. 不存在选择的某个点对为 $(u,v)$，此时可以发现如果这是最优解，则必然选取的两个点对为 $(u,a)$ 和 $(v,b)$。

   则要么是 $(u,a)$ 和 $(v,b)$ 均为边，要么形如 $(u,a)$ 是边但 $(v,b)$ 不是，此时必然可以调整使得答案不劣。所以只有可能 $(u,a)$ 和 $(v,b)$ 都是边。

2. 存在选择的某个点对为 $(u,v)$。此时要么选择另一条边 $(u',v')$ 使得顶点没有重复，要么形如选择 $u$ 的两个邻居 $(a,b)$。

于是只需要考虑三种情况，分别是选择 $(u,v)$ 和另一条边，选择 $(u,a)$ 和 $(v,b)$ 两条边，或者选择 $(a,b)$ 和 $(u,v)$ 且 $a,b$ 是 $u$ 或 $v$ 的邻居。

后两种比较容易，第三种直接维护，第二种注意到只需要对于每个点存前三小条边即可，对于第一个来说，考虑选择的另一条边必然是在两端排名都不超过三的，于是直接维护即可。

---

## 作者：紊莫 (赞：0)

线段树分治做法，需要卡常。

---

首先答案来自两种情况：

1. 两条无公共端点的边。
2. 一个点延伸出去的三条边（观察样例可以发现）。

那么对于第二种情况，可以直接计算，而对于第一种情况，这里采用线段树分治的方法计算。

每次加入边 $(u, v, w)$ 的时候，查询的是不包括 $u,v$ 的边中的最小边权。

这里使用**动态开点权值线段树**维护每个点连出去的边权，额外维护所有边的信息，查询就是所有边的信息，减去 $u$ 连着的边，再减去 $v$ 连着的边，做一次线段树上二分即可。

所有答案可以用 multiset 维护，时间复杂度 $O(n\log^2n)$。

朴素的实现会 TLE，下面分享一些卡常方法：

1. 线段树采用非递归式写法，这里是单点修改，所以没必要写 zkw 线段树。
2. 离散化后再上线段树。
3. 已经求解过的信息存储下来，减小常数。

[参考代码。](https://codeforces.com/problemset/submission/1566/304796984)

跑的还是很慢的话可以加上火车头，实测会快一些，上面的代码是不加火车头的版本，惊险通过（1999ms）。

---

## 作者：sunkuangzheng (赞：0)

最优方案不可能包含四条及以上的边，一个四条边的方案一定可以通过调整端点删去一条边。

如果我们选择了三条边，则一定是一个点的三条出边，否则可以被两条边替代。这种情况容易维护：对每个点维护前三小出边，再全局开一个 set 维护每个点的前三小边的和。

剩余情况都是两条边。直观的想法是找到最小和次小边 $(a,b),(c,d)$。如果 $a,b,c,d$ 互不相同则直接结束，否则设 $d = a$，两条边分别为 $(a,b),(a,c)$。

- **重要观察**：$(a,b),(a,c),(b,c)$ 中至少有一条边被选择。
- **Proof**：假设我们已经选择了一条边 $(u,v)$。如果 $(u,v) \ne (b,c)$，则 $(a,b),(a,c)$ 两条边至少有一条可以选。由于它们是最小的两条边，故一定会选。

现在问题变成，维护边集 $\{(u,v,w)\}$，每次查询给出 $(a,b)$，找到一对 $(u,v,w)$ 满足 $a,b,u,v$ 互不相同且 $w$ 最小。

将所有边挂在较小端点 $u$ 上，设询问的 $a < b$。将左端点拆分成三段区间 $[1,a),(a,b),(b,n]$，每个区间内查一个 $w$ 的右端点 $v$ 满足 $v \ne a,v \ne b$。线段树每个节点维护 $w$ 前三小的 $v$ 即可。

时间复杂度 $\mathcal O(n \log n)$，常数非常非常大。实现时请注意常数，注意常数，注意常数，不是所有单 $\log$ 都能轻松过 $10^5$。

```cpp
/**
 *    author: sunkuangzheng
 *    created: 15.10.2024 08:00:36
**/
#include<bits/stdc++.h>
#ifdef DEBUG_LOCAL
#include <mydebug/debug.h>
#endif
using ll = long long;
const int N = 1e5+5;
using namespace std;
int T,n,q,m,u,v,w,op;  map<pair<int,int>,int> mp; 
set<tuple<int,int,int>> s,ss[N],st[N];
multiset<ll> tp;
struct info{int x,y; bool operator <(const info&a)const{return x < a.x;}};
struct S{info a,b,c;}t[N*4];
inline info es(){return {(int)2e9,0};}
inline S e(){return S{es(),es(),es()};}
inline S mg(S a,S b){
    info c[6] = {a.a,a.b,a.c,b.a,b.b,b.c};//别用 vector，会 TLE。
    sort(c,c + 6);
    S t = e(); t.a = c[0];
    for(int i = 1;i < 5;i ++) if(c[i].y != c[0].y){
        t.b = c[i]; break;
    }for(int i = 1;i < 5;i ++) if(c[i].y != c[0].y && c[i].y != t.b.y){
        t.c = c[i]; break;
    }return t;
}inline void upd(int s,int l,int r,int x,S k){
    if(l == r) return t[s] = k,void();
    int mid = (l + r) / 2;
    if(x <= mid) upd(s*2,l,mid,x,k);
    else upd(s*2+1,mid+1,r,x,k);
    t[s] = mg(t[s*2],t[s*2+1]);
}inline S qry(int s,int l,int r,int ql,int qr){
    if(ql > qr) return e();
    if(ql <= l && r <= qr) return t[s];
    int mid = (l + r) / 2; S as = e();
    if(ql <= mid) as = mg(as,qry(s*2,l,mid,ql,qr));
    if(qr > mid) as = mg(as,qry(s*2+1,mid+1,r,ql,qr));
    return as;
}inline void upd(int u){
    S t = e(); auto it = ss[u].begin();
    if(it != ss[u].end()){
        auto [x,y,z] = *it ++;
        t.a = {x,z};
    }if(it != ss[u].end()){
        auto [x,y,z] = *it ++;
        t.b = {x,z};
    }if(it != ss[u].end()){
        auto [x,y,z] = *it ++;
        t.c = {x,z};
    }upd(1,1,n,u,t);
}inline void ins(int u,int v,int w){
    if(u > v) swap(u,v); mp[{u,v}] = w;
    if(st[u].size() >= 3){
        auto it = st[u].begin(); ll t = 0; 
        t += get<0>(*it ++),t += get<0>(*it ++),t += get<0>(*it ++);
        tp.erase(tp.find(t));
    }if(st[v].size() >= 3){
        auto it = st[v].begin(); ll t = 0; 
        t += get<0>(*it ++),t += get<0>(*it ++),t += get<0>(*it ++);
        tp.erase(tp.find(t));
    }
    s.emplace(w,u,v),ss[u].emplace(w,u,v),upd(u);
    st[u].emplace(w,u,v),st[v].emplace(w,u,v);
    if(st[u].size() >= 3){
        auto it = st[u].begin(); ll t = 0; 
        t += get<0>(*it ++),t += get<0>(*it ++),t += get<0>(*it ++);
        tp.insert(t);
    }if(st[v].size() >= 3){
        auto it = st[v].begin(); ll t = 0; 
        t += get<0>(*it ++),t += get<0>(*it ++),t += get<0>(*it ++);
        tp.insert(t);
    }
}inline void del(int u,int v){
    if(u > v) swap(u,v);
    if(st[u].size() >= 3){
        auto it = st[u].begin(); ll t = 0; 
        t += get<0>(*it ++),t += get<0>(*it ++),t += get<0>(*it ++);
        tp.erase(tp.find(t));
    }if(st[v].size() >= 3){
        auto it = st[v].begin(); ll t = 0; 
        t += get<0>(*it ++),t += get<0>(*it ++),t += get<0>(*it ++);
        tp.erase(tp.find(t));
    }
    int w = mp[{u,v}];
    s.erase({w,u,v}),ss[u].erase({w,u,v}),st[u].erase({w,u,v}),st[v].erase({w,u,v}),upd(u);
    if(st[u].size() >= 3){
        auto it = st[u].begin(); ll t = 0; 
        t += get<0>(*it ++),t += get<0>(*it ++),t += get<0>(*it ++);
        tp.insert(t);
    }if(st[v].size() >= 3){
        auto it = st[v].begin(); ll t = 0; 
        t += get<0>(*it ++),t += get<0>(*it ++),t += get<0>(*it ++);
        tp.insert(t);
    }
}inline ll qry(int u,int v){
    int ans = 2e9; if(u > v) swap(u,v);
    auto x = qry(1,1,n,1,u - 1);
    if(x.a.y != u && x.a.y != v) ans = min(ans,x.a.x);
    if(x.b.y != u && x.b.y != v) ans = min(ans,x.b.x);
    if(x.c.y != u && x.c.y != v) ans = min(ans,x.c.x);
    x = qry(1,1,n,u + 1,v - 1);
    if(x.a.y != v) ans = min(ans,x.a.x);
    if(x.b.y != v) ans = min(ans,x.b.x);
    if(x.c.y != v) ans = min(ans,x.c.x);
    x = qry(1,1,n,v + 1,n),ans = min(ans,x.a.x);
    return ans;
}inline ll qry(){
    assert(s.size() >= 4); auto it = s.begin();
    auto [w,u,v] = *it ++; auto [W,U,V] = *it;
    if(u != U && u != V && v != U && v != V) return w + W;
    if(u == U || u == V); else swap(u,v);
    if(U == u); else swap(U,V);
    ll ans = min(qry(u,v) + w,qry(U,V) + W);
    if(mp.count(minmax(v,V))) ans = min(ans,qry(v,V) + mp[minmax(v,V)]);
    if(tp.size()) ans = min(ans,*tp.begin());
    return ans;
}int main(){
    ios::sync_with_stdio(0),cin.tie(0);
    cin >> n >> m;
    for(int i = 1;i <= 4 * n;i ++) t[i] = e();
    for(int i = 1;i <= m;i ++) cin >> u >> v >> w,ins(u,v,w);
    cout << qry() << "\n";
    for(cin >> q;q --;){
        if(cin >> op >> u >> v,op == 1) cin >> w,ins(u,v,w);
        else del(u,v);
        cout << qry() << "\n";
    }
}
```

---

