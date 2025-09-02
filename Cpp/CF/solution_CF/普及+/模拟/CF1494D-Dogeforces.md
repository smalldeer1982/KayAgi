# Dogeforces

## 题目描述

The Dogeforces company has $ k $ employees. Each employee, except for lower-level employees, has at least $ 2 $ subordinates. Lower-level employees have no subordinates. Each employee, except for the head of the company, has exactly one direct supervisor. The head of the company is a direct or indirect supervisor of all employees. It is known that in Dogeforces, each supervisor receives a salary strictly more than all his subordinates.

The full structure of the company is a secret, but you know the number of lower-level employees and for each pair of lower-level employees, the salary of their common supervisor is known (if there are several such supervisors, then the supervisor with the minimum salary). You have to restore the structure of the company.

## 说明/提示

One of the possible structures in the first example: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1494D/b4b5e03fae4e04d10365f74dfd3682f3acad7010.png)

## 样例 #1

### 输入

```
3
2 5 7
5 1 7
7 7 4```

### 输出

```
5
2 1 4 7 5 
4
1 5
2 5
5 4
3 4```

# 题解

## 作者：kouylan (赞：7)

给你一个树，祖先的权值严格大于当前点，给你所有两个叶节点的 LCA 的权值，请我们构造出这样一棵树。

首先，根节点的权值肯定是最大的，那么我们就可以任取一个叶节点 $i$，取 $\max\{a[i][j]\}$，就是根节点的权值。

求出根节点后，所有的叶节点就可以被分为两类。

1. $a[i][j]=\max\{a[i][j]\}$，就说明他们的 LCA 是根节点，也就是他们分属在不同的子树中（此处的子树指的都是以树根的子节点为根的子树）。

2. $a[i][j]\neq \max\{a[i][j]\}$，说明他们的 LCA 不是根，也就是分属在同一棵子树中。

当然，第一种情况对我们已经没有用了，因为已经求出了根节点。所以有用的就是第二种情况。

我们把一棵子树抽出来看，如果我们知道了在这棵子树中的所有叶节点，那不就可以递归求出这个子树的根了吗？而求出的根恰好是愿树根的子节点。

所以说，思路就十分明了了，我们只需要写一个函数，可以做到给出所有叶节点，求出树根。然后找出分属同一棵子树的叶节点，抽取出来递归操作。

下面是 AC 代码。
```cpp
/*
Codeforces 1494D
*/
#include <bits/stdc++.h>
using namespace std;

#define int long long

int m,n,a[1005][1005];
int c[1005],fa[1005];

int getroot(vector<int> leaf)
{
	if(leaf.size()==1)
	{
		c[leaf[0]] = a[leaf[0]][leaf[0]];
		return leaf[0];
	}
	int mx=0;
	for(int i=1;i<leaf.size();i++)
		mx = max(mx,a[leaf[0]][leaf[i]]);
	int root=(++m);
	c[root] = mx;
	int del[1005];
	for(int i=0;i<=leaf.size();i++)
		del[i] = 0;
	vector<int> son;
	for(int i=0;i<leaf.size();i++)
		if(!del[i])
		{
			son.clear();
			for(int j=i;j<leaf.size();j++)
				if(a[leaf[i]][leaf[j]]!=mx)
				{
//					cout<<leaf[j]<<' ';
					son.push_back(leaf[j]);
					del[j] = 1;
				}
//			cout<<endl;
			fa[getroot(son)] = root;
		}
	return root;
}

signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			cin>>a[i][j];
	m = n;
	vector<int> leaf;
	for(int i=1;i<=n;i++)
		leaf.push_back(i);
	int root=getroot(leaf);
	cout<<m<<endl;
	for(int i=1;i<=m;i++)
		cout<<c[i]<<' ';
	cout<<endl<<root<<endl;
	for(int i=1;i<=m;i++)
		if(i!=root)
			cout<<i<<' '<<fa[i]<<endl;
	
	return 0;
}
```

祝大家 AC 愉快！

---

## 作者：fade_away (赞：4)

很久之前场上过的题，偶然发现大家的做法和我都不太一样，于是来水一发题解。

我们发现这棵树上每个点都比它父亲小，这是啥？这是不是类似于$kruskal$重构树啊！

于是我们对这个完全图建一个$kruskal$重构树，然后因为可能存在父子权值相同，于是我们把权值相同的连通块缩成一个点，这样就可以满足题目的限制。

于是就得到了一个$O(n^2\log n)$的优秀做法，目前排在CF Rank2，被Rank1的$O(n^3)$做法暴锤了$QAQ$。

## Code
```cpp
vector<PR> Ans;
vector<int> e[MAXN];
struct Vnode{ int x, u, v; } V[MAXN];
int id[MAXN], c[MAXN], C[MAXN], f[MAXN], n, ID, num;
int find(int x) { return f[x] == x ? f[x] : f[x] = find(f[x]); }
void dfs(int x, int father) {
	if (x <= n) return;
	if (c[x] != c[father]) id[x] = ++ ID, C[ID] = c[x];
	else id[x] = id[father];
	for (auto v : e[x]) {
		if (v == father) continue;
		dfs(v, x);
	}
	for (auto v : e[x]) {
		if (v == father) continue;
		if (id[v] != id[x]) Ans.PB(MP(id[v], id[x]));
	}
}
signed main() {
	n = read();
	int edgenum = 0;
	for (int i = 1; i <= n ; ++ i)
		for (int j = 1; j <= n ; ++ j) {
			if (i == j) { c[i] = C[i] = read(); continue; }
			int x = read();
			if (i < j) V[++ edgenum] = (Vnode){x, i, j};
		}
	sort(V + 1, V + edgenum + 1, [&](Vnode a, Vnode b){ return a.x < b.x; });
	num = ID = n;
	for (int i = 1; i <= n ; ++ i) id[i] = i, f[i] = i;
	for (int i = 1; i <= edgenum ; ++ i) {
		int x = find(V[i].u), y = find(V[i].v);
		if (x == y) continue;
		c[++ num] = V[i].x, f[x] = f[y] = f[num] = num;
		e[num].PB(x), e[num].PB(y);
	} 
	dfs(num, 0);
	printf("%d\n", ID);
	for (int i = 1; i <= ID ; ++ i) printf("%d ", C[i]); puts("");
	printf("%d\n", id[num]);
	for (auto v : Ans) printf("%d %d\n", v.fi, v.se);
	return 0;
}
```


---

## 作者：lgswdn_SA (赞：2)

首先可以得到根节点权值 $\max lca_{u,v}$。

假设我们得到了一个节点作为子树根节点 $u$ 和其所有子树内叶节点，那么对于两个叶节点 $s_i,s_j$，如果他们的 $lca\neq u$，则这两个点处在一个子树中。所以我们递归处理这一些处在同一个子树中的叶子节点。

由于最多分成 $O(n)$ 个子树，然后每一个节点要 $O(n^2)$ 枚举叶节点，所以总复杂度 $O(n^3)$。

代码：https://codeforces.com/contest/1494/submission/110974588

---

## 作者：DaiRuiChen007 (赞：1)

# CF1494D 题解



## 思路分析

看到父亲的权值大于儿子的权值，首先想到 Kruskal 重构树。

显然两个点 LCA 处的权值就是合并这两个点所在连通块时的那条边的边权，因此我们把所有 $a_{i,j}$ 当成一条连接 $i,j$，边权为 $a_{i,j}$ 的边求出 Kruskal 重构树即为所求的答案。

但是这题略有不同，这题要求父亲的权值严格大于儿子的权值，因此我们要进行一定的分类讨论，假设当前我们需要新建一条边，连接 $u,v$ 权值为 $w$，记 $val_i$ 表示节点 $i$ 的权值，根据 Kruskal 生成树的算法流程我们知道 $val_u\le w,val_v\le w$，根据两个不等号是否取等分成如下四类情况：

- $val_u<w,val_v<w$：

  最基本的情况，用 Kruskal 重构树原本的处理方案，新建一个节点 $x$，$val_x=w$，设 $u,v$ 为 $w$ 的儿子即可。

- $val_u=w,val_v<w$：

  此时假如我们新建 $x$，那么 $val_x=w=val_u$ 不满足题目限制，发现直接把 $v$ 设为 $u$ 的儿子即可。

- $val_u<w,val_v=w$：

  同上一种情况，设 $u$ 为 $v$ 的儿子。

- $val_u=w,val_v=w$：

  非常有趣的情况，我们应该要把 $u,v$ 合并成一个节点，因此我们想象成把 $v$ 删掉，把所有 $v$ 的儿子变成 $u$ 的儿子，并查集上直接设 $v$ 这一块的祖先为 $u$，并不需要对于每个节点修改，只要保证后面查询这一块的祖先查不到 $v$ 即可，最后输出节点编号的时候需要做一次离散化。


时间复杂度 $\Theta(n^2\log n)$。

## 代码呈现

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1001;
struct node {
	int u,v,w;
	inline friend bool operator <(const node &A,const node &B) {
		return A.w<B.w;
	}
};
vector <node> edges;
vector <int> G[MAXN];
int w[MAXN][MAXN],id[MAXN],val[MAXN],dsu[MAXN];
bool del[MAXN];
inline int find(int x) {
	if(dsu[x]==x) return x;
	return dsu[x]=find(dsu[x]);
}
signed main() {
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;++i) dsu[i]=i;
	for(int i=1;i<=n;++i) {
		for(int j=1;j<=n;++j) {
			scanf("%d",&w[i][j]);
			if(i<j) edges.push_back((node){i,j,w[i][j]});
			if(i==j) val[i]=w[i][i];
		}
	}
	sort(edges.begin(),edges.end());
	int siz=n;
	for(auto e:edges) {
		int x=find(e.u),y=find(e.v);
		if(x==y) continue;
		if(val[x]==e.w&&val[y]==e.w) {
			del[y]=true,dsu[y]=x;
			for(int i:G[y]) G[x].push_back(i);
			G[y].clear();
		} else if(val[x]==e.w) {
			dsu[y]=x;
			G[x].push_back(y);
		} else if(val[y]==e.w) {
			dsu[x]=y;
			G[y].push_back(x);
		} else {
			dsu[x]=dsu[y]=++siz;
			dsu[siz]=siz,val[siz]=e.w;
			G[siz].push_back(x),G[siz].push_back(y);
		}
	}
	int idcnt=0;
	for(int i=1;i<=siz;++i) if(!del[i]) id[i]=++idcnt;
	printf("%d\n",idcnt);
	for(int i=1;i<=siz;++i) if(!del[i]) printf("%d ",val[i]); puts("");
	printf("%d\n",idcnt);
	for(int i=1;i<=siz;++i) {
		if(del[i]) continue;
		for(int j:G[i]) printf("%d %d\n",id[j],id[i]);
	}
	return 0;
}
```



---

## 作者：Rui_R (赞：1)

题意：有一棵树，满足每个非叶子结点至少有两个儿子。每个点有权值，满足父亲的权值严格大于儿子的权值。

已知这棵树有 $n$ 个叶子，并给出这 $n$  个叶子两两之间 $\text{lca}$ 的权值。

求出这棵树的结点数，根，形态，以及每个点的权值。

$2 \le n \le 500$

[原题](https://www.luogu.com.cn/problem/CF1494D)

对于一棵树，其上两个叶子的 $\text{lca}$ 为根等价于这两个叶子分别属于根不同儿子的子树；两个叶子的 $\text{lca}$ 不为根等价于这两个叶子属于根同一个儿子的子树。

根至少有两个儿子。

那么，对于任意一个叶子 $i$，一定会有另一个叶子 $j$ 满足 $\text{lca}(i,j)=\text{root}$，并且我们知道 $\text{root}$
的权值一定最大。

所以只要随便选一个叶子，把它跟其它所有叶子 $\text{lca}$ 的权值取 $\max$ 就可以得到根的权值。

同时，对于每个叶子，所有跟它 $\text{lca}$ 不为根的一定在同一个子树中，而对于每棵子树我们可以递归处理。

具体来说就是整一个函数，其参数为一棵树所有叶子的编号，其返回值为这棵树的根的编号。

通过上述方法可以确定当前树的根的权值，那么给其分配一个编号。

枚举叶子，如果其已经属于之前的某个子树就 ``continue`` ，否则选出与它在根的同一个儿子的子树里的所有叶子（包括其本身）塞到一起递归，将返回的子树的根的父亲标为当前树的根。

递归时如果当前的树只有一个结点，直接返回这个叶子。

单次复杂度是 $O(n^2)$ 的，由于每次递归的子树中不会包括根，只会调用最多 $Size$ 次，其中 $Size$ 为这棵树的结点数量。

每个非叶子结点至少有两个儿子，那么 $Size$ 是 $2n$ 级别的。

下面给出一个简单的证明：

令 $d_i$ 表示第 $i$ 个结点儿子的数量。对于那 $n$ 个叶子， $d=0$；剩下的 $Size-n$ 个结点， $d\ge 2$ 。

$$
Size = 1+\sum d_i \ge 1+2(Size-n) \to Size \le 2n-1
$$

这样复杂度是 $O(n^3)$ 。

代码：

```cpp
#pragma GCC optimize(2)

#include <cstdio>
#include <vector>

const int maxn = 1e3 + 5 ;

template<typename T>
inline T max(const T &a,const T &b){
	return a>b?a:b;
}

int n,a[maxn][maxn],ncnt;int c[maxn],fa[maxn];

int Epk(std::vector<int> &v){
	if(v.size() == 1) return c[v[0]]=a[v[0]][v[0]],v[0] ;
	int Maxx = 0;
	for(int i=1;i<(int)v.size();i++) Maxx = max(Maxx,a[v[0]][v[i]]);
	int rt = ++ncnt;c[rt] = Maxx;
	std::vector<int> del;del.resize(v.size());
	std::vector<int> go ;
	for(int i=0;i<(int)v.size();i++){
		if(del[i]) continue ;
		go.clear();
		for(int j=i;j<(int)v.size();j++){
			if(a[v[i]][v[j]]!=Maxx){
				go.push_back(v[j]);
				del[j] = true;
			}
		}
		fa[Epk(go)] = rt;
	}
	return rt ;
}

std::vector<int> basic;

int main(){
	scanf("%d",&n);
	for(int i = 1;i <= n;i++){
		for(int j=1;j<=n;j++)
			scanf("%d",&a[i][j]);
	}
	ncnt = n;
	for(int i=1;i<=n;i++) basic.push_back(i);
	int rt = Epk(basic);
	printf("%d\n",ncnt);
	for(int i=1;i<=ncnt;i++) printf("%d ",c[i]);
	printf("\n");
	printf("%d\n",rt);
	for(int i=1;i<=ncnt;i++){
		if(i == rt) continue ;
		printf("%d %d\n",i,fa[i]);
	}
	return 0 ;
}

```




---

## 作者：Valhalla_Is_Calling (赞：0)

### $\operatorname{Description.}$
给出一个树的 $n$ 个叶子节点的权值（一共就 $n$ 个叶子节点），以及每个叶子节点的最近公共祖先的权值，你需要构造出一个合法的树，满足所有父节点的权值都大于子节点。

### $\operatorname{Solution.}$

感谢 @芦苇林 提供的原始思路。

显然，为了满足题目需求，我们需要把权值大的点往上放才行，于是我们对于所有的不重复的 $lca$ 进行排序，之后放到一个单调队列里边，记录一下每个点当前所在树的根，之后每次选出两个权值最小的，新建一个节点并合并即可。

### $\operatorname{Code.}$

```cpp
#include <bits/stdc++.h>

using namespace std;

priority_queue<pair<int, pair<int, int> > > pq;

int read () {
    int x = 0, f = 1;
    char c = getchar();
    while (c < '0' || c > '9') {
        if (c == '-') f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9') {
        x = (x << 1 ) + (x << 3) + (c ^ 48);
        c = getchar();
    }
    return x * f;
}

int main() {
    int n = read();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int x = read();
            pq.push({-x, {i, j}});
        }
    }
    vector<vector<int>> v;
    v.resize(n);
    vector<int> fa(n, -1);
    vector<int> ans(n);
    int k = n;
    while(!pq.empty()) {
        pair<int, pair<int, int> > t = pq.top();

        pq.pop();

        int x = t.second.first;
        int y = t.second.second;
        int val = -t.first;
        if (x == y) {
            ans[x] = val;
            continue;
        }

        while (x != y && (fa[x] != -1 && fa[y] != -1)) {
            x = fa[x];
            y = fa[y];
        }

        while(fa[x] != -1) x = fa[x];
        while(fa[y] != -1) y = fa[y];

        if (x == y) continue;

        if (ans[x] == val) {
            v[x].push_back(y);
            fa[y] = x;
            continue;
        }
        if (ans[y] == val) {
            v[y].push_back(x);
            fa[x] = y;
            continue;
        }

        fa.resize(k + 1), ans.resize(k + 1), v.resize(k + 1);
        v[k].push_back(x), v[k].push_back(y);
        fa[x] = k,  fa[y] = k;
        fa[k] = -1;
        ans[k] = val;
        k++;
    }

    cout << k ;
    puts("");
    for (int i = 0; i < k; i++) {
        if (fa[i] != -1) {
            if (ans[i] >= ans[fa[i]]) continue;
        }
        cout << ans[i] << " ";
    }
    puts("");
    cout << k << "\n";
    for (int i = 0; i < k; i++) {
        for (auto g : v[i]) {
            cout << g + 1 << " " << i + 1 << "\n";
        }
    }
    return 0;
}

```


---

