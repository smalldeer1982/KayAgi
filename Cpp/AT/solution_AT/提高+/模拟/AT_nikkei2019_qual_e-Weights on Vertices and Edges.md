# Weights on Vertices and Edges

## 题目描述

[problemUrl]: https://atcoder.jp/contests/nikkei2019-qual/tasks/nikkei2019_qual_e

$ N $ 頂点 $ M $ 辺の連結な無向グラフがあります。 頂点には $ 1 $ から $ N $ までの番号が、辺には $ 1 $ から $ M $ までの番号がついています。 また、各頂点、各辺にはそれぞれ重みが定められています。 頂点 $ i $ の重みは $ X_i $ です。 辺 $ i $ は頂点 $ A_i $ と $ B_i $ を結ぶ辺で、その重みは $ Y_i $ です。

グラフから辺を $ 0 $ 本以上削除して、次の条件が満たされるようにしたいです。

- 削除されていない任意の辺について、その辺を含む連結成分の頂点の重みの総和が、その辺の重み以上である。

最小で何本の辺を消す必要があるかを求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 10^5 $
- $ N-1\ \leq\ M\ \leq\ 10^5 $
- $ 1\ \leq\ X_i\ \leq\ 10^9 $
- $ 1\ \leq\ A_i\ <\ B_i\ \leq\ N $
- $ 1\ \leq\ Y_i\ \leq\ 10^9 $
- $ (A_i,B_i)\ \neq\ (A_j,B_j) $ ($ i\ \neq\ j $)
- 与えられるグラフは連結である。
- 入力される値はすべて整数である。

### Sample Explanation 1

辺 $ 3,4 $ を削除したとします。 このとき、辺 $ 1 $ を含む連結成分は、頂点 $ 1,2,3 $ からなる連結成分であり、頂点の重みの総和は $ 2+3+5=10 $ です。 辺 $ 1 $ の重みは $ 7 $ なので、辺 $ 1 $ については条件を満たしています。 また同様に、辺 $ 2 $ についても条件を満たしています。 よって、辺を $ 2 $ 本削除することで条件を満たすグラフが得られます。 辺を $ 1 $ 本以下削除することによって条件を満たすことはできないので、答えは $ 2 $ になります。

## 样例 #1

### 输入

```
4 4
2 3 5 7
1 2 7
1 3 9
2 3 12
3 4 18```

### 输出

```
2```

## 样例 #2

### 输入

```
6 10
4 4 1 1 1 7
3 5 19
2 5 20
4 5 8
1 6 16
2 3 9
3 6 16
3 4 1
2 6 20
2 4 19
1 2 9```

### 输出

```
4```

## 样例 #3

### 输入

```
10 9
81 16 73 7 2 61 86 38 90 28
6 8 725
3 10 12
1 4 558
4 9 615
5 6 942
8 9 918
2 7 720
4 7 292
7 10 414```

### 输出

```
8```

# 题解

## 作者：普通的名字 (赞：0)

考虑一个显然的做法。如果当前图中最大的边权大于其所在的连通块点权和，那么这条边就必须删去，重复以上操作，直到不存在这样的边为止。

但是删边操作是不好做的（指 LCT），所以考虑反过来按边权从小到大加边，目的是让加入的边最多。使用并查集维护连通块，同时维护连通块内边权大于点权和的边集 $s$（由于后面点权和可能会变大，那么他们就会加入答案）。

当处理到边 $(u,v,w)$，都将其加入并查集，并且维护 $s$。如果 $w$ 不大于点权和，说明 $s$ 中的边权都不大于点权和（由于 $w$ 的单调性），自然它们就可以加入答案。记得开 `long long`。

时间复杂度 $O(m\log m)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+1;
int n,m,fa[N],num[N],cnt;
long long sum[N];
struct node{int u,v,w;}e[N];
int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>sum[i],fa[i]=i;
    for(int i=1,u,v,w;i<=m;i++){
        cin>>u>>v>>w;
        e[i]={u,v,w};
    }
    sort(e+1,e+1+m,[](node a,node b){return a.w<b.w;});
    for(int i=1;i<=m;i++){
        int x=find(e[i].u),y=find(e[i].v);
        if(x!=y){
            fa[x]=y;
            sum[y]+=sum[x];
            num[y]+=num[x];
        }
        num[y]++;
        if(e[i].w<=sum[y]){
            cnt+=num[y];
            num[y]=0;
        }
    }
    cout<<m-cnt;
}
```

---

## 作者：Otue (赞：0)

我们将边从小到大加，看最多能加多少条边，用总边数减就得到了最少删去的边数。

如果加入一条边 $(u,v,w)$，$u,v$ 所处的连通块不同，就相当于将这两个连通块合并。维护合并后的连通块点的权值总和。若点权和大于等于 $w$，则意味这个连通块里所有的边都满足条件（从小到大加边）。

但可能这次加边会导致之前的有些边变得条件成立，那么再维护一个数组表示这个连通块中有多少条边想加没有加进去。对此进行统计即可。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define PII pair<int, int>
#define _for(i, a, b) for (int i = (a); i <= (b); i++)
#define _pfor(i, a, b) for (int i = (a); i >= (b); i--)
#define int long long
const int N = 3e5 + 5;

int n, m, p[N], sum[N], cnt[N], res;

struct edge {
	int u, v, w;
}ed[N];

int find(int x) {
	if (p[x] != x) p[x] = find(p[x]);
	return p[x];
}

bool cmp(edge x, edge y) {
	return x.w < y.w;
}

signed main() {
	cin >> n >> m;
	_for(i, 1, n) cin >> sum[i], p[i] = i;
	_for(i, 1, m) cin >> ed[i].u >> ed[i].v >> ed[i].w;
	sort(ed + 1, ed + m + 1, cmp);
	_for(i, 1, m) {
		int fx = find(ed[i].u), fy = find(ed[i].v);
		if (fx != fy) {
			p[fx] = fy;
			sum[fy] += sum[fx];
			cnt[fy] += cnt[fx];
			cnt[fx] = 0;
		}
		cnt[fy]++;
		if (sum[fy] >= ed[i].w) {
			res += cnt[fy];
			cnt[fy] = 0; // 这个连通块所有边都满足条件，cnt 清空
		}
	}
	cout << m - res << endl;
}
```

---

## 作者：qzhwlzy (赞：0)

### 题目大意

有一张 $n$ 个点 $m$ 条边的无向图，节点 $i$ 有点权 $x_i$，边 $i$ 连接点 $a_i$ 和 $b_i$ 且有边权 $y_i$。

现在要删除若干条边，使得剩下的图满足：对于没有被移除的边，其所在联通块中的点的点权和不小于该边的边权。

求需要移除的最小边数。

### 思路

正着考虑删边不好做，考虑按边权从小到大往图中加边，求出最多能加多少边。因为加边只会使联通块的点权和变大，所以原来加进去的边一定不会变得不符合条件。用并查集维护即可。

但是可能有原来加不进去的边变得能加进去了。对于这样的边，我们可以先把联通块连起来，但是这条边不计入答案。当且仅当等到加入某条边后使得这条边满足条件了，那么之前未计入答案的边就可以计入了。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#define maxn 100005
#define ll long long
using namespace std;
int n,m,fa[maxn],num[maxn],ans; ll sum[maxn];
struct edge{int from,to; ll val; bool operator<(const edge &xx)const{return val<xx.val;}}a[maxn];
int getfa(int xx){if(fa[xx]==xx) return xx; return fa[xx]=getfa(fa[xx]);}
int main(){
    scanf("%d%d",&n,&m); for(int i=1;i<=n;i++){scanf("%lld",&sum[i]); fa[i]=i;}
    for(int i=1;i<=m;i++) scanf("%d%d%lld",&a[i].from,&a[i].to,&a[i].val); sort(a+1,a+1+m);
    for(int i=1;i<=m;i++){
        int r1=getfa(a[i].from),r2=getfa(a[i].to); if(r1!=r2){fa[r2]=r1; sum[r1]+=sum[r2]; num[r1]+=num[r2];}
        num[r1]++; if(sum[r1]>=a[i].val){ans+=num[r1]; num[r1]=0;}
    } printf("%d",m-ans);
    return 0;
}

```

---

