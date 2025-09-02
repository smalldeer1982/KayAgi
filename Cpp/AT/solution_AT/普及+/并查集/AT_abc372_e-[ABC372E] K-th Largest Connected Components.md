# [ABC372E] K-th Largest Connected Components

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc372/tasks/abc372_e

$ N $ 頂点 $ 0 $ 辺の無向グラフがあります。頂点には $ 1 $ から $ N $ の番号がつけられています。

$ Q $ 個のクエリが与えられるので、与えられた順に処理してください。各クエリは以下の $ 2 $ 種類のいずれかです。

- タイプ $ 1 $ : `1 u v` の形式で与えられる。頂点 $ u $ と頂点 $ v $ の間に辺を追加する。
- タイプ $ 2 $ : `2 v k` の形式で与えられる。頂点 $ v $ と連結な頂点の中で、$ k $ 番目に頂点番号が大きいものを出力する。ただし、頂点 $ v $ と連結な頂点が $ k $ 個未満のときは `-1` を出力する。

## 说明/提示

### 制約

- $ 1\leq\ N,Q\leq\ 2\times\ 10^5 $
- タイプ $ 1 $ のクエリにおいて、$ 1\leq\ u\lt\ v\leq\ N $
- タイプ $ 2 $ のクエリにおいて、$ 1\leq\ v\leq\ N,\ 1\leq\ k\leq\ 10 $
- 入力は全て整数
 
### Sample Explanation 1

\- $ 1 $ 個目のクエリについて、頂点 $ 1 $ と頂点 $ 2 $ の間に辺が追加されます。 - $ 2 $ 個目のクエリについて、頂点 $ 1 $ と連結な頂点は $ 1,2 $ の $ 2 $ つです。この中で $ 1 $ 番目に大きい $ 2 $ を出力します。 - $ 3 $ 個目のクエリについて、頂点 $ 1 $ と連結な頂点は $ 1,2 $ の $ 2 $ つです。この中で $ 2 $ 番目に大きい $ 1 $ を出力します。 - $ 4 $ 個目のクエリについて、頂点 $ 1 $ と連結な頂点は $ 1,2 $ の $ 2 $ つです。$ 3 $ 個未満なので `-1` を出力します。 - $ 5 $ 個目のクエリについて、頂点 $ 1 $ と頂点 $ 3 $ の間に辺が追加されます。 - $ 6 $ 個目のクエリについて、頂点 $ 2 $ と頂点 $ 3 $ の間に辺が追加されます。 - $ 7 $ 個目のクエリについて、頂点 $ 3 $ と頂点 $ 4 $ の間に辺が追加されます。 - $ 8 $ 個目のクエリについて、頂点 $ 1 $ と連結な頂点は $ 1,2,3,4 $ の $ 4 $ つです。この中で $ 1 $ 番目に大きい $ 4 $ を出力します。 - $ 9 $ 個目のクエリについて、頂点 $ 1 $ と連結な頂点は $ 1,2,3,4 $ の $ 4 $ つです。この中で $ 3 $ 番目に大きい $ 2 $ を出力します。 - $ 10 $ 個目のクエリについて、頂点 $ 1 $ と連結な頂点は $ 1,2,3,4 $ の $ 4 $ つです。$ 5 $ 個未満なので `-1` を出力します。

## 样例 #1

### 输入

```
4 10
1 1 2
2 1 1
2 1 2
2 1 3
1 1 3
1 2 3
1 3 4
2 1 1
2 1 3
2 1 5```

### 输出

```
2
1
-1
4
2
-1```

## 样例 #2

### 输入

```
6 20
1 3 4
1 3 5
2 1 1
2 3 1
1 1 5
2 6 9
2 1 3
2 6 1
1 4 6
2 2 1
2 6 2
2 4 7
1 1 4
2 6 2
2 3 4
1 2 5
2 4 1
1 1 6
2 3 3
2 1 3```

### 输出

```
1
5
-1
3
6
2
5
-1
5
3
6
4
4```

# 题解

## 作者：qzmoot (赞：12)

# 题解：AT_abc372_e [ABC372E] K-th Largest Connected Components
## 题目大意
给你一个操作序列。

1. 连接 $u$ 和 $v$。
2. 查询和 $u$ 连通的下标第 $k$ 大的点（$u$ 自己也算）。
## 分析
通过要查询第 $k$ 大，我便想到直接开 set 来做，然后因为有连边操作，而且查询的是连通的点，因此我们还要加上一个并查集就行了。
```cpp
#include <bits/stdc++.h>
#define si set<int>::iterator
using namespace std;
const int N=2e5+5;
set<int>t[N];
int n,q;
int f[N];
int find(int x)
{
	return x==f[x]?x:f[x]=find(f[x]);
}
int main()
{
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++)
		t[i].insert(i),f[i]=i;
	while(q--)
	{
		int op,u,v;
		scanf("%d%d%d",&op,&u,&v);
		u=find(u);
		if(op==1)
		{
			v=find(v);
			t[u].insert(v);
			t[v].insert(u);
			if(u!=v)
			{
				f[v]=u;
				for(si id=t[v].begin();id!=t[v].end();id++)
					t[u].insert(*id);
			}
		}
		else
		{
			if(v>t[u].size())
				puts("-1");
			else
			{
				si now=t[u].end();
				for(int i=1;i<=v;i++,now--);
				printf("%d\n",*now);
			}
		}
	}
	return 0;
}
```
但是你会发现这个代码 tle 了。因为你在合并的时候，set 并没有达到最优的合并方法，于是你判断一下大小，再合并即可（启发式合并）。

加上这行就行
```cpp
if(t[u].size()<t[v].size())swap(u,v);
```

---

## 作者：hjyowl (赞：5)

### 题目大意

有一个 $n$ 个点的图，最初没有边。

每次有两种操作：

```1 x y```：将 $x$ 和 $y$ 合并。

```2 x k```：询问所有和 $x$ 联通的点当中编号第 $k$ 大的点。

### 前置知识

[文艺平衡树](https://www.luogu.com.cn/problem/P3391)，[并查集](https://www.luogu.com.cn/problem/P3367)。

### 思路

由于直接维护不好弄，容易炸空间也容易超时。

考虑维护 $n$ 个文艺平衡树，然后用并查集来维护那 $n$ 个文艺平衡树的合并。

#### 文艺平衡树的合并

由于文艺平衡树满足平衡，所以可以使用一个递归来合并两个文艺平衡树。

代码大概如下：

```cpp
void merge(int u,int b){
    if (tr[u].s[0]){
        merge(tr[u].s[0],b);
    }
    if (tr[u].s[1]){
        merge(tr[u].s[1],b);
    }
    insert(tr[u].v,tr[u].id,b);
}
```

#### 优化

为了保证合并能更快，每次选取小的来合并，可以让速度变快一点。

### 时间复杂度复杂度

容易计算，时间复杂度 $\Theta(q\log n)$。

### 代码

有点长。

```cpp
#include <bits/stdc++.h>
using namespace std;
const long long N = 2e7 + 10;
long long n,m;
struct owl{
	long long s[2],p,v,id;
	long long cnt,flag;
	void init(long long _v,long long _id,long long _p){
		v = _v;
		p = _p;
		id = _id;
		cnt = 1;
	}
}tr[N];
long long root[N],idx;
long long p[N];
long long find(long long x){
	if (p[x] != x){
		p[x] = find(p[x]);
	}
	return p[x];
}
void pushup(long long u){
	tr[u].cnt = tr[tr[u].s[0]].cnt + tr[tr[u].s[1]].cnt + 1;
}
void rotate(long long x){
	long long y = tr[x].p,z = tr[y].p;
	long long k = tr[y].s[1] == x;
	tr[z].s[tr[z].s[1] == y] = x,tr[x].p = z;
	tr[y].s[k] = tr[x].s[k ^ 1],tr[tr[x].s[k ^ 1]].p = y;
	tr[x].s[k ^ 1] = y,tr[y].p = x;
	pushup(y);
	pushup(x);
}
void splay(long long x,long long k,long long b){
	while (tr[x].p != k){
		long long y = tr[x].p,z = tr[y].p;
		if (z != k){
			if ((tr[y].s[1] == x) ^ (tr[z].s[1] == y)){
				rotate(x);
			}
			else{
				rotate(y);
			}
		}
		rotate(x);
	}
	if (!k){
		root[b] = x;
	}
}
void insert(long long v,long long id,long long b){
	long long u = root[b],p = 0;
	while (u){
		p = u,u = tr[u].s[v > tr[u].v];
	}
	u = ++ idx;
	if (p){
		tr[p].s[v > tr[p].v] = u;
	}
	tr[u].init(v,id,p);
	splay(u,0,b);
}
long long get_k(long long k,long long b){
	long long u = root[b];
	while (u){
		if (tr[tr[u].s[0]].cnt >= k){
			u = tr[u].s[0];
		}
		else if (tr[tr[u].s[0]].cnt + 1 == k){
			return tr[u].id;
		}
		else{
			k -= tr[tr[u].s[0]].cnt + 1;
			u = tr[u].s[1];
		}
	}
	return -1;
}
void merge(long long u,long long b){
	if (tr[u].s[0]){
		merge(tr[u].s[0],b);
	}
	if (tr[u].s[1]){
		merge(tr[u].s[1],b);
	}
	insert(tr[u].v,tr[u].id,b);
}
int main(){
	cin >> n >> m;
	for (long long i = 1; i <= n; i ++ ){
		p[i] = root[i] = i;
		tr[i].init(i,i,0);
	}
	idx = n;
	while (m -- ){
		long long op;
		long long a,b;
		cin >> op >> a >> b;
		if (op == 1){
			long long pa = find(a),pb = find(b);
			if (pa != pb){
				if (tr[root[pa]].cnt > tr[root[pb]].cnt){//优化
					swap(pa,pb);
				}
				merge(root[pa],pb);
				p[pa] = pb;
			}
		}
		else{
			long long pa = find(a);
			if (tr[root[pa]].cnt < b){
				cout << -1 << endl;
			}
			else{
				cout << get_k(tr[root[pa]].cnt - b + 1,pa) << endl;//由于是k小，通过大小-k+1转成k大
			}
		}
	}
	return 0;
}
```

---

## 作者：Ratio_Y (赞：3)

## 思路

维护连通块内序号降序排序，可以用平衡树解决，~~但不想写~~，所以可以把它当成启发式合并的水题来解决。

用 set 容器（不会 set 容器的看[这里](https://www.cnblogs.com/Ratio-Yinyue1007/p/18186604)）和并查集维护，每次将小的连通块合并到大的上，然后跳迭代器到指定元素即可。

会发现只这样操作由于合并的数量越来越大导致程序会 TLE ~~（也可能是我写的常数太大了~~，观察数据范围，发现 $k\le 10$，也就是说每个连通块只用维护前十大的序号就行，于是我们浅删一下就可以顺利 AC 本题。

## 实现

```cpp
#include<bits/stdc++.h>
#define fo(x,y,z) for(register int (x)=(y);(x)<=(z);(x)++)
#define fu(x,y,z) for(register int (x)=(y);(x)>=(z);(x)--)
using namespace std;

const int Ratio=0;
const int N=2e5+5;
int n,q;
int fx[N];
set<int>st[N];
set<int>::iterator it;
namespace Wisadel
{
    int Wfind(int x)
    {
        if(fx[x]==x) return x;
        return fx[x]=Wfind(fx[x]);
    }
    short main()
    {
        scanf("%d%d",&n,&q);
        for(int i(1);i<=n;i++) fx[i]=i,st[i].insert(i);
        for(int i(1);i<=q;i++)
        {
            int op,x,y;scanf("%d%d%d",&op,&x,&y);
            if(op==1)
            {
                int X=Wfind(x),Y=Wfind(y);
                if(st[X].size()>st[Y].size()) swap(X,Y);
                fx[X]=Y,st[Y].insert(st[X].begin(),st[X].end());
                while(st[Y].size()>10) st[Y].erase(st[Y].begin());
            }
            else
            {
                x=Wfind(x);
                if(st[x].size()<y)
                {
                    printf("-1\n");
                    continue;
                }
                it=st[x].begin();
                advance(it,st[x].size()-y);
                printf("%d\n",*it);
            }
        }
        return Ratio;
    }
}
int main(){return Wisadel::main();}
```

[Review record.](https://atcoder.jp/contests/abc372/submissions/57981733)


---

完结撒花~

---

## 作者：Hurraciny (赞：3)

## 数据范围
如果你仔细读了题，你就会发现，询问中的 $k$ 小于等于 $10$，这就意味着我们只需要维护前十大值就行了，其他的根本不需要去管。这个性质让这题变得简单多了。

## 维护

题目要求求出的是连通块中的前 $k$ 大，连通块可以让我们想到并查集，而因为 $k$ 非常小，所以维护第 $k$ 大基本上用什么都可以，这里我用的是 `SET`，每次加边只需要合并一下他们所在的连通块即可。

## 代码


```cpp
#include <iostream>
#include <cstring>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

inline int find(vector<int>&fa, int x){//并查集
	if(x == fa[x])
		return x;
	return fa[x] = find(fa, fa[x]);
}
  inline void add_set(vector<set<int> >&to, int u, int v){//维护前 10 大
	if(to[u].size() < 10)
		to[u].insert(v);
	else{
		if(*(to[u].begin()) < v){
			to[u].erase(to[u].begin());
			to[u].insert(v);
		}
	}
	return;
}
int main(){
	int n, q;
	cin >> n >> q;
	vector<int>fa(n+1);
	for(int i = 1; i <= n; i++)
		fa[i] = i;
	vector<set<int> >to(n+1);
	for(int i = 1; i <= n; i++)
		to[i].insert(i);
	while(q--){
		int op;
		cin >> op;
		if(op == 1){
			int u, v;
			cin >> u >> v;
			u = find(fa, u);
			v = find(fa, v);
			if(u == v)
				continue;
			fa[u] = v;
			for(auto i : to[u])
				add_set(to, v, i);
		}
		else{
			int x, k;
			cin >> x >> k;
			x = find(fa, x);
			auto i = --to[x].end();
			k--;
			int cnt = to[x].size()-1;
			for(; cnt && k; i--, cnt--, k--);
			if(!k)
				cout << *(i) << endl;
			else
				puts("-1");
		}
	}
  return 0;
}
```

---

## 作者：small_lemon_qwq (赞：3)

实际上，对于每个 $op=2$ 的查询，我们只关注 $v$ 所在的联通块的编号前 $10$ 大的节点就好了（因为 $k\le10$），显然要使用并查集，可以对于每个联通块中并查集的根节点开一个 set 存储，但我是直接使用数组，添加边时直接进行合并有序数组就可以了。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,g[200005][15],f[200005],tmp[15];
int get_f(int x){
	if(x==f[x])return x;
	return f[x]=get_f(f[x]);
}
void update(int u,int v){
	int i=1,j=1;
	memcpy(tmp,g[v],sizeof(tmp));
	for(int k=1;k<=10;k++){//只存前10大
		if(g[u][i]>tmp[j]){//我是从大到小存储的
			g[v][k]=g[u][i];
			i++;
		}else{
			g[v][k]=tmp[j];
			j++;
		}
	}
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int q;
	cin>>n>>q;
	memset(g,-1,sizeof(g));
	iota(f+1,f+n+1,1);
	for(int i=1;i<=n;i++){
		g[i][1]=i;
	}//初始化
	while(q--){
		int op,u,k;
		cin>>op>>u>>k;
		if(op==1){
			int fu=get_f(u),fv=get_f(k);
			if(fu!=fv){
				f[fu]=fv;
				update(fu,fv);
			}
		}else{
			u=get_f(u);
			cout<<g[u][k]<<"\n";
		}
	}
	return 0;
}
```

使用 set 的做法可以看[别人的提交记录](https://atcoder.jp/contests/abc372/submissions/57992910)。

---

## 作者：PineappleSummer (赞：3)

[Problem](https://atcoder.jp/contests/abc372/tasks/abc372_e)

开心死了，因为 E 题使我寄完了。

数据范围很有意思，注意到 $k\le 10$，发现对于每次查询可以暴力回答。

点与点之间连边，会出现很多个联通块，每次询问只与该点所在的联通块有关，所以考虑并查集维护。

同时，对每个点维护一个 `set`，表示该点**为祖先**时的联通块中的点集。

对于操作 $1$，暴力合并 `set` 就可以了。将小 `set` 合并到大 `set` 上，即使用启发式合并，有时间复杂度保证。

对于操作 $2$，暴力查找该点所在的联通块的第 $k$ 大点即可。由于 `set` 不支持随机访问，可以从 `set` 最后一直往前跳，时间复杂度 $O(k\log n)$。**注意：如果你是从 `s.rbegin()` 开始往前跳，应该 `it++` 而不是 `it--`。**

总时间复杂度 $O(n\log^2 n)$。

```cpp
int n, q, fa[N];
set <int> G[N];
int find (int k) {
    return fa[k] == k ? k : fa[k] = find (fa[k]);
}
signed main () {
    ios::sync_with_stdio (false);
    cin.tie (0); cout.tie (0);
    
    cin >> n >> q;
    for (int i = 1; i <= n; i++) fa[i] = i, G[i].insert (i);
    while (q--) {
        int opt, u, v;
        cin >> opt >> u >> v;
        if (opt == 1) {
            int fu = find (u), fv = find (v);
            if (fu == fv) continue;
            if (G[fu].size () < G[fv].size ()) swap (fu, fv);
            for (auto i : G[fv]) G[fu].insert (i);
            fa[fv] = fu;
        }
        else {
            int fu = find (u);
            if (G[fu].size () < v) cout << -1 << '\n';
            else {
                auto it = G[fu].end ();
                it --;
                 for (int i = 1; i < v; i++) it --;
                cout << *it << '\n';
            }
        }
    }
    return 0;
}
```

---

## 作者：Redamancy_Lydic (赞：2)

[博客内食用更佳](https://www.cnblogs.com/Lydic/p/18425191)

这道题的 $k\le 10$ 其实没什么用，代码区别仅在于手写平衡树和使用内置容器。

这道题让查询与一个节点相连的所有点的信息，所以不难想到并查集。

又因为让查询第 $k$ 大，所以不难想到平衡树和~~线段树~~启发式合并。

至此思路明显。我们对并查集中的每个节点开一个平衡树，每次合并两个点的时候，比较祖先节点的节点个数并进行启发式合并。查询的时候如果不是手写平衡树就遍历容器，然后遍历到第 $k$ 个的时候就输出即可。

复杂度均摊 $\mathcal{O}(n\log^2 n)$。

[提交记录](https://atcoder.jp/contests/abc372/submissions/57982933)

---

## 作者：doumingze (赞：2)

这题如果你读的时候能注意到 $k \le 10$，你就赢了！

接下来因为 $k \le 10$ 你就可以暴力了。实现两个连通块的合并时，把其中一个连通块中最大的前 $10$ 个值用归并排序的方法合并到另一个连通块中并只取前 $10$ 个值即可。查询的时候，直接找到这个点在哪个块内（找点这一部分可以使用并查集），然后查询相应值即可。时间复杂度 $O(n + q \log n)$。

具体的，看代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

#define wobuxiwang wodedaima
#define beibieren jianqilaihou
#define keyi shiyong
#define zhijie 100000000

const int N = 2e5 + 10;
vector<int> vec[N];
int p[N];
int n, q, op, x, y;
int keyi[zhijie];

int find(int x)
{
	if(p[x] != x) p[x] = find(p[x]);
	return p[x];
}

void merge(int a, int b)
{
	a = find(a), b = find(b); //找到在哪个块内
	if(a == b) return; //没必要再合并
	if(a > b) swap(a, b);
	vector<int> res;
	for(int i = 1, j = 0, k = 0; i <= vec[a].size() + vec[b].size(); i ++) //类似于归并排序，合并两个块内维护的前 10 大值
	{
		if(j == vec[a].size()) res.push_back(vec[b][k ++]);
		else if(k == vec[b].size()) res.push_back(vec[a][j ++]);
		else if(vec[a][j] > vec[b][k]) res.push_back(vec[a][j ++]);
		else res.push_back(vec[b][k ++]);
	}
	vec[a].clear();
	vec[b].clear();
	p[b] = a; //合并两个块
	for(int i = 0; i < res.size() && i < 10; i ++)
		vec[a].push_back(res[i]);
}

int main()
{
	cin >> n >> q;
	for(int i = 1; i <= n; i ++) vec[i].push_back(i), p[i] = i;
	while(q ++)
	{
		scanf("%d%d%d", &op, &x, &y);
		if(op == 1) merge(x, y);
		else
		{
			int t = find(x);
			if(vec[t].size() < y) puts("-2");
			else printf("%d\n", vec[t][y - 1]);
		}
	}
	return 0;
}
```

---

## 作者：ivyjiao (赞：1)

加强版：[P3224 [HNOI2012] 永无乡](https://www.luogu.com.cn/problem/P3224)。

介绍一种时间复杂度正确的 pb_ds 解法。

很明显这两种操作都能用平衡树 + 并查集维护。

但是手写 FHQ or Splay 太麻烦了，还不如打线段树合并呢，怎么办？

这时候就要用到我们亲爱的 pb_ds 中的 rb_tree_tag 了。

[rb_tree_tag 用法](https://oiwiki.org/lang/pb-ds/tree/)。

假设你已经学会了以上操作。

然后先建立一个并查集，并把每个节点 $i$ 加入到 $tr_i$ 里。

代码：

```cpp
for(int i=1;i<=n;i++){
    cin>>a[i];
    f[i]=i;
    tr[i].insert({a[i],i});
}
```

对于操作一（或初始加边），设 $fx=find(x),fy=find(y)$，则我们先把 $f_{fy}=fx$，然后依次把 $tr_y$ 中的所有节点加入到 $tr_x$ 中，并删除 $tr_y$ 中所有元素。

代码：

```cpp
int fx=find(f[x]),fy=find(f[y]);
if(fx==fy) continue;
f[fy]=fx;
while(tr[fy].size()){
    PII it=*tr[fy].find_by_order(0);
    tr[fx].insert(it);
    tr[fy].erase(tr[fy].upper_bound(it));
}
```

对于操作 $2$，设 $fx=find(x)$，若 $tr_x$ 中元素个数 $<y$，那么输出 $-1$，否则我们在 $tr_x$ 中找出排名为 $y$ 的数并输出其下标。

代码：

```cpp
int fx=find(f[x]);
if(tr[fx].size()<y) cout<<-1<<endl;
else cout<<(*tr[fx].find_by_order(y-1)).se<<endl;
```

细心的朋友可能在 oi-wiki 中发现了一个叫做 `join(x)` 的函数，实际上这玩意在实际应用中基本 P 用没有，直接忽略就行。

> `join(x)` 函数需要保证并入树的键的值域与被并入树的键的值域**不相交**（也就是说并入树内所有值必须全部大于 / 小于当前树内的所有值），否则会抛出 `join_error` 异常。
>
>如果要合并两棵值域有交集的树，需要将一棵树的元素一一插入到另一棵树中。
>
> ——oi-wiki

然后我们发现过不了，原因是暴力合并有可能会被卡到 $O(n^2)$，我们需要使用启发式合并进行优化，即每次把元素个数少的树合并到元素个数多的树中，这样时间复杂度是 $O(n)$ 的。

代码：

```cpp
int fx=find(f[x]),fy=find(f[y]);
if(fx==fy) continue;
if(tr[fx].size()<tr[fy].size()) f[fx]=fy,swap(fx,fy);
else f[fy]=fx;
while(tr[fy].size()){
    PII it=*tr[fy].find_by_order(0);
    tr[fx].insert(it);
    tr[fy].erase(tr[fy].upper_bound(it));
}
```

然后我们就过了。

代码：

```cpp
#include<bits/stdc++.h>
#include<bits/extc++.h>
#define PII pair<int,int>
#define fi first
#define se second
using namespace std;
using namespace __gnu_pbds;
const int N=1e5+1;
tree<PII,null_type,less_equal<PII>,rb_tree_tag,tree_order_statistics_node_update>tr[N];
int n,m,q,x,y,a[N],f[N];
char op;
int find(int x){
    if(f[x]==x) return x;
    return f[x]=find(f[x]);
}
int main(){
	cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        f[i]=i;
        tr[i].insert({a[i],i});
    }
    while(m--){
        cin>>x>>y;
        int fx=find(x),fy=find(y);
        if(fx==fy) continue;
        if(tr[fx].size()<tr[fy].size()) f[fx]=fy,swap(fx,fy);
        else f[fy]=fx;
        while(tr[fy].size()){
            PII it=*tr[fy].find_by_order(0);
            tr[fx].insert(it);
            tr[fy].erase(tr[fy].upper_bound(it));
        }
    }
    cin>>q;
	while(q--){
        cin>>op>>x>>y;
        if(op=='Q'){
            int fx=find(f[x]);
            if(tr[fx].size()<y) cout<<-1<<endl;
            else cout<<(*tr[fx].find_by_order(y-1)).se<<endl;
        }
        else{
            int fx=find(f[x]),fy=find(f[y]);
            if(fx==fy) continue;
            if(tr[fx].size()<tr[fy].size()) f[fx]=fy,swap(fx,fy);
            else f[fy]=fx;
            while(tr[fy].size()){
                PII it=*tr[fy].find_by_order(0);
                tr[fx].insert(it);
                tr[fy].erase(tr[fy].upper_bound(it));
            }
        }
	}
}
```

---

## 作者：Redshift_Shine (赞：1)

## 题意

求连通块内第 $k$ 大节点标号，$1\le k\le {\color{red}{10}}$。

## 思路

并查集+`vector` 维护前 $k$ 大标号。

首先给每个节点 $i$ 的连通块中的 `vector` push 一个 $i$。

接下来，在并查集合并函数中，可以使用一个简单的方法直接实现 $O(n+m)$ 有序数列归并，那就是调用 STL `merge` 函数。需要传入两个数组的前闭后开指针以及一个存储结果数组的起始指针。**注意，若使用 `vector` 作为存储结果的数组，需要提前在该数组中申请 $(n+m)$ 个元素的空间，否则 RE**。

查询时直接输出即可。

详情见代码。

## 代码

```c++
#include <algorithm>
#include <cassert>
#include <cstdio>
#include <vector>
using namespace std;
const int N = 2e5 + 10;
int n, m, f[N];
vector<int> vec[N];
inline int find(int x)
{
    return x == f[x] ? x : f[x] = find(f[x]);
}
inline void mrge(int x, int y)
{
    x = find(x), y = find(y);
    if (x == y)
        return;
    if (vec[x].size() < vec[y].size())
        swap(x, y);
    f[y] = x;
    vector<int> tmp(vec[x].size() + vec[y].size());
    merge(vec[x].begin(), vec[x].end(), vec[y].begin(), vec[y].end(), tmp.begin());
    // assert(vec[x].size() and vec[y].size());
    // fprintf(stderr, "%llu\n", tmp.size());
    // printf("%d %d\n", x, y);
    reverse(tmp.begin(), tmp.end());
    tmp.resize(min<int>(tmp.size(), 10));
    reverse(tmp.begin(), tmp.end());
    vec[x] = tmp;
    vec[y].clear();
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        vec[i].emplace_back(i);
        f[i] = i;
    }
    for (int i = 1, x, y, z; i <= m; i++)
    {
        // fprintf(stderr, "%d\n", i);
        scanf("%d%d%d", &x, &y, &z);
        if (x == 1)
        {
            mrge(y, z);
            continue;
        }
        y = find(y);
        if (vec[y].size() < z)
        {
            puts("-1");
            continue;
        }
        // for (auto &j : vec[y])
        //     printf("%d ", j);
        // putchar('\n');
        printf("%d\n", vec[y][vec[y].size() - z]);
    }
}

---

## 作者：Dtw_ (赞：1)

# 题意
每次询问：

- $1 \ u \ v$ 在 $u,v$ 之间连一条边。
- $2 \ u \ k$ 查询 $u$ 所在的联通块中编号第 $k$ 大的值。

# Solution
首先看到维护联通块，容易想到并查集，这样就知道了任意一个点所在的联通块。

查询的时候可以用 `set` 维护出每个联通块内的元素，启发式合并时间复杂度是对的，直接做就好。暴力找第 $k$ 大就好。（其实可以直接找）。

# Code

```cpp
#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

#define fi first
#define se second

#define int long long

#define pii pair<int, int>

#define fst ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

const int INF = 0x3f3f3f3f3f3f3f3f;

const int P = 998244353;

const int N = 2e5 + 10;

int n, q;

set<int, greater<int>> S[N];

int p[N];

int fifa(int x)
{
	if (x == p[x]) return x;
	return p[x] = fifa(p[x]);
}

void join(int x, int y)
{
	x = fifa(x), y = fifa(y);
	if (x != y)
	{
		if (S[x].size() < S[y].size())
		{
			for (auto e : S[x]) S[y].insert(e);
		}
		else
		{
			for (auto e : S[y]) S[x].insert(e);
			swap(S[x], S[y]);
		}
		p[x] = y;
	}
}


set<int>::iterator it;

int query(int u, int k)
{
	u = fifa(u);
	if (S[u].size() < k) return -1;
	for (it = S[u].begin(); it != S[u].end(); it++)
	{
		k--;
		if (k == 0)
		{
			return *it;
		}
	}
	return -1;
}

signed main()
{
	fst
	cin >> n >> q;
	for (int i=1; i<=n; i++) S[i].insert(i), p[i] = i;
	while (q--)
	{
		int op, u, v;
		cin >> op >> u >> v;
		if (op == 1)
		{
			join(u, v);
		}
		else
		{
			cout << query(u, v) << endl;
		}
	}
	return 0;
}



```

---

## 作者：WuMin4 (赞：0)

# 题意

给出 $q$ 个操作。

1. 将 $u$ 和 $v$ 连边。
2. 问 $u$ 所在的连通块中编号第 $k$ 大的点。

# 思路

连通块很容易想到并查集，求第 $k$ 大可以用平衡树（虽然赛时没看到 $k\le 10$），合并时将信息从将小的连通块合并到大的连通块，这样可以减少时间复杂度。\
什么？你不会写平衡树？直接套 pbds 库中的 `tree` 就可以了（具体见代码）。

# 代码

```cpp
#include<bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;//注意使用pbds库时需要加上头文件和命名空间
struct bal_tree{
	tree<int,null_type,less_equal<int>,rb_tree_tag,tree_order_statistics_node_update> t;//使用tree的方式，具体参数可以上网查，不会的直接复制就可以了
	void insert(int x){t.insert(x);}
	void del(int x){t.erase(t.upper_bound(x));}
	int rnk(int x){return t.order_of_key(x)+1;}
	int find_rnk(int x){return *t.find_by_order(x-1);}
	int upper_bound(int x){return *t.upper_bound(x);}
	int lower_bound(int x){return *t.lower_bound(x);}
}t[200005]; 
int n,q,f[200005];
int find(int x){
	if(f[x]!=x) f[x]=find(f[x]);
	return f[x];
}
signed main(){
	cin>>n>>q;
	for(int i=1;i<=n;i++)
		f[i]=i,t[i].insert(i);
	while(q--){
		int op,x,y;
		cin>>op>>x>>y;
		if(op==1){
			int p1=find(x),p2=find(y);
			if(p1!=p2){
				if(t[p1].t.size()>t[p2].t.size())
					swap(p1,p2);
				f[p1]=p2;
				for(int v:t[p1].t)
					t[p2].insert(v);
				t[p1].t.clear();
			}
		}
		else{
			x=find(x);
			if(t[x].t.size()<y)
				cout<<-1<<endl;
			else
				cout<<t[x].find_rnk(t[x].t.size()-y+1)<<endl;//注意是第k大
		}
	}
	return 0;
}
```

---

## 作者：cheng2010 (赞：0)

## K-th Largest Connected Components

### 思路

怎么没人写：

- 线段树合并

呢？

先来说说什么是线段树合并，即把两颗线段树维护的东西给合并起来（废话）。

还是来举个例子吧：

假设现在我们有两棵线段树，每个点维护区间和（每个点上的数字就是区间和）

如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/2wytuopk.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

![](https://cdn.luogu.com.cn/upload/image_hosting/oadbin2t.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

合并即为：

![](https://cdn.luogu.com.cn/upload/image_hosting/nekojbcs.png?x-oss-process=image/resize,m_lfit,h_170,w_225)


再结合并查集，维护联通即可。

### code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+7;
int n,q;
int fa[N];
inline int Find(int x){return fa[x]==x?x:fa[x]=Find(fa[x]);}
int root[N],sum[N<<2],cnt,ls[N<<2],rs[N<<2];
inline void update(int &p,int l,int r,int id)
{
	if(!p) p=++cnt;
	if(l==r)
	{
		sum[p]=1;
		return;
	}
	int mid=l+r>>1;
	if(mid>=id)
		update(ls[p],l,mid,id);
	if(mid<id)
		update(rs[p],mid+1,r,id);
	sum[p]=sum[ls[p]]+sum[rs[p]];
}
inline int query(int p,int l,int r,int k)
{
	if(sum[p]<k) return -1;
	if(l==r) return l;
	int a1=sum[ls[p]];
	int a2=sum[rs[p]];
	int mid=l+r>>1;
	if(a2>=k) return query(rs[p],mid+1,r,k);
	else return query(ls[p],l,mid,k-a2);
}
inline int merge(int x,int y,int l,int r)
{
	if(!x||!y) return x|y;
	if(x==y)
	{
		sum[x]+=sum[y];
		return x;
	}
	int mid=l+r>>1;
	ls[x]=merge(ls[x],ls[y],l,mid);
	rs[x]=merge(rs[x],rs[y],mid+1,r);
	sum[x]=sum[ls[x]]+sum[rs[x]];
	return x;
}
int main()
{
	scanf("%d %d",&n,&q);
	for(int i=1;i<=n;i++) fa[i]=i,update(root[i],1,n,i);
	while(q--)
	{
		int opt,x,y;
		scanf("%d %d %d",&opt,&x,&y);
		if(opt==1)
		{
			int xx=Find(x);
			int yy=Find(y);
			if(xx!=yy)
			{
				fa[yy]=xx;
				root[xx]=merge(root[xx],root[yy],1,n);
			}
		}
		else
		{
			int xx=Find(x);
			printf("%d\n",query(root[xx],1,n,y));
		}
	}
}
```

---

## 作者：Imerance1018 (赞：0)

### Description

[传送门](https://atcoder.jp/contests/abc372/tasks/abc372_e)

### Solution

赛时 15min 写出正解却少一个特判没过，写篇题解纪念一下。

注意到 $k \le 10$。

所以我们可以暴力维护 $$ans_{i,j}$$，表示在与第 $i$ 个节点连通的节点中第 $j$ 大的节点，每次加边操作时合并两个节点，然后取前 10 个即可。

对于连通问题可以用并查集进行处理，总复杂度为 $O(q \log{n})$。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int n,q,fa[N];
int ans[N][20],cnt[N];//当然也可以用 vector，但是我不会排序
int find(int x)
{
	if(fa[x]==x)return x;
	return fa[x]=find(fa[x]);
}
bool cmp(int x,int y){return x>y;}
int main()
{
	cin>>n>>q;
	for(int i=1;i<=n;i++)cnt[i]=1,fa[i]=i,ans[i][1]=i;
	while(q--)
	{
		int opt;
		cin>>opt;
		if(opt==1)
		{
			int u,v;
			cin>>u>>v;
			int fu=find(u),fv=find(v);
			if(fu==fv)continue;//这个特判很重要，我赛时因为这个没调出来
			for(int i=1;i<=cnt[fv];i++)
				ans[fu][i+cnt[fu]]=ans[fv][i];
			sort(ans[fu]+1,ans[fu]+cnt[fu]+cnt[fv]+1,cmp);
			for(int i=11;i<=cnt[fu]+cnt[fv];i++)ans[fu][i]=0;
			cnt[fu]=min(cnt[fu]+cnt[fv],10);//注意取 min
			cnt[fv]=0;
			fa[fv]=fu;
		}
		else
		{
			int v,k;
			cin>>v>>k;
			int fv=find(v);
			if(k>cnt[fv])cout<<-1<<endl;
			else cout<<ans[fv][k]<<endl;
		}
	}
	return 0;
}
``````

---

## 作者：hzxphy (赞：0)

## 思路
对于每个边，我们可以合并序列，而我们访问时访问并查集的根即可。

此时对于合并时，差不多和归并排序的部分一样。

## Cpp Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=2e5;
int fa[MAXN+1],p[MAXN+1][11],tmp[11];
int GetFather(int x){
    return (fa[x]==x?x:(fa[x]=GetFather(fa[x])));
}
void merge(int x,int y){
    x=GetFather(x),y=GetFather(y);
    if(x==y)return;
    fa[x]=y;
    for(int k=1;k<=10;k++)tmp[k]=p[y][k];
    int i=1,j=1;
    for(int k=1;k<=10;k++){
        if(p[x][i]>tmp[j]){
            p[y][k]=p[x][i++];
        }
        else p[y][k]=tmp[j++];
    }
    return;
}
int main(){
    int n,q;cin>>n>>q;
    memset(p,-1,sizeof p);
    for(int i=1;i<=n;i++)fa[i]=i,p[i][1]=i;
    while(q--){
        int op;cin>>op;
        if(op==1){
            int u,v;cin>>u>>v;
            merge(u,v);
        }
        else{
            int u,k;cin>>u>>k;
            cout<<p[GetFather(u)][k]<<'\n';
        }
    }
    return 0;
}
```

---

