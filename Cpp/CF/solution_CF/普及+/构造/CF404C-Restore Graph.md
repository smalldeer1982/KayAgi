# Restore Graph

## 题目描述

Valera had an undirected connected graph without self-loops and multiple edges consisting of $ n $ vertices. The graph had an interesting property: there were at most $ k $ edges adjacent to each of its vertices. For convenience, we will assume that the graph vertices were indexed by integers from 1 to $ n $ .

One day Valera counted the shortest distances from one of the graph vertices to all other ones and wrote them out in array $ d $ . Thus, element $ d[i] $ of the array shows the shortest distance from the vertex Valera chose to vertex number $ i $ .

Then something irreparable terrible happened. Valera lost the initial graph. However, he still has the array $ d $ . Help him restore the lost graph.

## 样例 #1

### 输入

```
3 2
0 1 1
```

### 输出

```
3
1 2
1 3
3 2
```

## 样例 #2

### 输入

```
4 2
2 0 1 3
```

### 输出

```
3
1 3
1 4
2 3
```

## 样例 #3

### 输入

```
3 1
0 0 0
```

### 输出

```
-1
```

# 题解

## 作者：DinnerHunt (赞：4)

根据最短路的性质，边权为1的情况下，到点距离为$a_i$的点近能由到点距离为$a_i-1$链接而来    
我们可以从到点距离为0的点依次递增连边     

因为每个点最多有$k$度  
除起始点外，每个点$a_i$ 由 $a_i-1$ 链接而来，所以每个点仅能连$k-1$个点，如果 $size[a_{i-1}]*(k-1) < size[a_i] $ 那么无解

还有起始点有且仅有一个

```cpp
#include <cstdio>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxd = 1e5+10;
int n,k,s,arr[maxd],flag,mx;
queue<int> que[maxd];
int main()
{
    // freopen("a.in","r",stdin);
    // freopen("k.out","w",stdout);
    scanf("%d %d",&n,&k);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&s);
        arr[s]++;
        que[s].push(i);
        mx = max(s,mx);
    }
    if(arr[0]!=1) flag=1;
    if(k < arr[1]) flag=1;
    for(int i=2;i<=mx;i++)
        if((long long)arr[i-1]*(k-1)<arr[i]) flag=1;
    if(flag)printf("-1");
    else
    {
        printf("%d\n",n-1);
        for(int i=0;i<mx;i++)
        {
            while(arr[i+1])
            {
                int x = que[i].front();que[i].pop();
                for(int j=1;arr[i+1]&&j<=k-1+(i==0);j++)
                {
                    int y = que[i+1].front();que[i+1].pop();
                    que[i+1].push(y); arr[i+1]--;
                    printf("%d %d\n",x,y);
                }
            }
        }
    }

    return 0;
}
```


---

## 作者：Blancа (赞：3)

## 思路

这道题从最短路的角度去考虑可能不是很好想，可以考虑从构造的角度，只要确定了起点，那么图的框架就可以顺利成章的构造出来。

最短路可以不考虑，考虑最短路只会使答案复杂化，建出一颗树，路径唯一，就不需要考虑最短路了;其次，有每个点的度数不可以大于k，所以没必要连的边就尽量不连。

考虑度数，除了距离为 0 的节点的边都是连的儿子节点，其他节点在添加父节点时一定有一条边连向了父节点，即只能添加 $k-1$ 个儿子，而距离为 0 的点就可以连$k$个儿子。

首先通过判断距离为x和距离为$x+1$的点的个数关系，即（距离为$x$的点的个数 $\times (k - 1)$  > 距离为$x+1$的点的个数），距离为 0 的点特殊处理一下，同时判断一下，有可能不存在距离为 0 的点或者存在多个距离为 0 的点都是不合法的，建边就从距离为 $x$ 的点连向距离为 $x+1$ 的点就可以。

代码实现 ~~(操作有点累赘)~~
```c++
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
using namespace std;
const int maxn = 1e6 + 50;
inline int read () {
	int x = 0, f = 1; char ch = getchar();
	for (;!isdigit(ch); ch = getchar()) if (ch == '-') f = -1;
	for (; isdigit(ch); ch = getchar()) x = x * 10 + ch - '0';
	return x * f;
}
int n, k;
struct Node {
	int d, id;
} node[maxn];
int cnt[maxn];
vector <int> vec[maxn];
struct Ans {
	int from, to;
} ans[maxn];
bool cmp (Node A, Node B) { return A.d < B.d;}
int Max;
signed main () {
	n = read(), k = read();
	for (int i = 1; i <= n; i++) {
		node[i].d = read();
		node[i].id = i;
		Max = max (node[i].d, Max);
	}
	int cnt = 0;
	sort (node + 1, node + 1 + n, cmp);
	for (int i = 1; i <= n; i++) {
		if (node[i].d == 0) {
			if (cnt != 0) {
				return puts("-1"), 0;
			}
			cnt++;
		}
		vec[node[i].d].push_back(node[i].id);
	}
	for (int i = 1; i < Max; i++) {
		if ((long long)vec[i].size() * (k - 1) < vec[i + 1].size()) return puts("-1"), 0;//记得开long long，不然会爆
	}
	if (cnt == 0) return puts("-1"), 0;
	if (k < vec[1].size()) return puts("-1"), 0;
	int oper = 0, js = 0;
	for (int i = 1; i <= n; i++) {
		if (node[i].d == 0) {
			continue;
		}
		if (node[i].d - node[i - 1].d == 0) {
			if (js == k) {
				js = 1, ++oper;
				ans[i].from = vec[node[i].d - 1][oper], ans[i].to = node[i].id;
			} else if (js == k - 1 && node[i].d != 1) {
				js = 1, ++oper;
				ans[i].from = vec[node[i].d - 1][oper], ans[i].to = node[i].id;
			} else if (js == k - 1 && node[i].d == 1) {
				js ++;
				ans[i].from = vec[node[i].d - 1][oper], ans[i].to = node[i].id;
			}else {
				js++;
				ans[i].from = vec[node[i].d - 1][oper], ans[i].to = node[i].id;
			}
		} else if (node[i].d - node[i - 1].d == 1) {
			oper = 0, js = 1;
			ans[i].from = vec[node[i].d - 1][oper], ans[i].to = node[i].id;
		}
	}
	printf ("%d\n", n - 1);
	for (int i = 2; i <= n; i++) {
		printf ("%d %d\n", ans[i].from, ans[i].to);
	}
	return 0;
}


```

---

## 作者：Umbrella_Leaf (赞：2)

> 构造一个 $n$ 个点的图，一个顶点的度不大于 $k$，并满足从某一点到 $i$ 的最短路不超过 $d_i$。
> 
> 无解输出 $\texttt{-1}$。

发现最短路比较难处理，因此假设我们建出了这个图的最短路树。

显然不在最短路上的边就没用了（因为不会更新答案）。

那么其实我们就是要构造以那个最短路为 $0$ 的点为根的一棵树，要求每个节点的深度为 $d_i$ 且任意一个节点的度数不大于 $k$。

考虑树上一个节点（除了根节点）的度一定是 $1+它的子节点数$。

度数不大于 $k$ ，那就是说子节点的个数不超过 $k-1$。

对于根节点，它的子节点数（即深度为 $1$ 的节点数）不超过 $k$ 个。

深度为 $i+1$ 的点不超过深度为 $i$ 的点的 $k-1$ 倍，这里 $i\ge 1$。

这就是一个很显然的贪心了。

可以开 $n$ 个 `vector` 来存储深度为 $i$ 的节点。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
vector<int> v[100005];
int d[100005],fa[100005];
int n,k;
int root,num;
int main(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++){
		scanf("%d",&d[i]);
		if(d[i]==0){//记录根节点
			root=i;
			num++;
		}
		v[d[i]].push_back(i);//用vector存储
	}
	if(num!=1){//有多个根
		puts("-1");
		return 0;
	}
	if(n==1){//特判
		puts("0");
		return 0;
	}
	if(v[1].size()>k){//特判深度为1的点个数
		puts("-1");
		return 0;
	}
	for(int i=0;i<v[1].size();i++)fa[v[1][i]]=root;
	for(int i=2;i<n;i++){
		if(v[i].size()>(long long)(k-1)*(v[i-1].size())){//这里容易爆int
			puts("-1");
			return 0;
		}
		for(int j=0;j<v[i].size();j++)fa[v[i][j]]=v[i-1][j/(k-1)];//设置fa数组
	}//用fa数组记录一个节点的父亲，方便输出。
	printf("%d\n",n-1);
	for(int i=1;i<=n;i++)if(i!=root)printf("%d %d\n",i,fa[i]);
	return 0;
}
```

---

## 作者：KID2695 (赞：0)

先考虑一下这里的 $d_i$ 的性质，因为边权都是 $1$，所以 $d_u=1+\min\limits_{v\in son_u}{d_v}$。因此 $d_i$ 排序后一定是从 $0$ 开始的一些连续的数字。

接着不考虑无解，发现如果某个 $d_i$ 为 $0$，那么 $i$，就是最开始被选中的那个点。由此可以得到有解的一个条件是 $d_i$ 为 $0$ 的点只有一个。

最后考虑连边，仿照前面的式子，假设 $d_i=x$，$d_j=x-1$，那么 $i$ 向 $j$ 连边。所以假设满足 $d_i=x$ 的 $i$ 的数量为 $A$，满足 $d_j=x-1$ 的数量为 $B$，那么 $A$ 一定不能大于 $q\times B$，其中 $q$ 是 $k-1$，特别的，当 $i=1$ 的时候，$q$ 为 $k$。

这个题就结束了，直接用上面三个条件判断是否有解，然后连边就好了。

~~核心代码加注释貌似没有必要~~

```cpp
#define wj {puts("-1");return 0;}

int d[N];
int D[N];
int n,k;
vector<int> e[N];
int que[N],had,tal; 
int rt;
int tot;
pair<int,int> edge[N];
int main(){
	n=iread();
	k=iread();
	FOR(i,1,n){
		d[i]=iread();
		e[d[i]].push_back(i);//统计数量，便于计算
		if(!d[i]) rt=i;
	}
	if(e[0].size()!=1) wj
	if(e[1].size()>e[0].size()*1ll*k) wj
	int qwe=k-1;
	FOR(i,2,n){
		if(e[i].size()>e[i-1].size()*1ll*qwe) wj
	}
  //判断完是否无解，开始连边
	que[had=tal=1]=rt;
	FOR(i,1,n){
		if(e[i].empty()) break;
		while(d[que[had]]!=i-1) ++had;//保证差1
		for(auto it:e[i]){
			edge[++tot]=make_pair(it,que[had]);
			++D[que[had]];
			++D[it];
			while(D[que[had]]==k) ++had;//保证度数符合要求
			que[++tal]=it;
		}
	}
	printf("%d\n",tot);
	FOR(i,1,tot){
		printf("%d %d\n",edge[i].first,edge[i].second);
	}
	return 0;
}

```

对于时间复杂度的话，可以当作线性，别看代码这么多循环，但是进行的操作数量是很少的。

---

## 作者：TheSky233 (赞：0)

## Description

给定 $n$ 个点和顶点的度 $k$ 以及每个点到点 $i$ 的最短路长度 $dis_i$，打印这个图。

## Solution

若直接从图的角度考虑，则情况太多太乱，放弃。

还记得树的某个性质吗？每两点之间只有唯一的一条路径！恰好符合题目中给定的条件。假设有且只有一个距离为 $0$ 的点，就把这个点称当做整个树中的根节点，那么 $dis_i$ 就相当于树中这个点的深度。

对于根节点，它的入度为 $0$，最多就可以有 $k$ 个孩子节点；对于其他层的节点，因为它有一个父亲节点，所以它只能有 $k-1$ 个孩子节点。

### 对于无解情况

- 如果没有 $dis$ 为 $0$ 的节点，无解。
- 如果 $dis$ 为 $0$ 的节点个数超过 $1$，无解。
- 如果根节点的孩子节点数量超过 $k$，无解（上文已说明）。
- 如果非根节点的孩子节点数量超过 $k-1$，无解（上文已说明）。

## Code
```cpp
#include<cstdio>
#include<vector>
#include<cstdlib>
using namespace std;

const int N=1e5+5;

int n,k,MaxDep;
int dis[N];
vector<int> v[N];
vector<pair<int,int> > ans;

void Exit(int num){
	printf("%d\n",num);
	exit(0);
}

int main(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++){
		scanf("%d",&dis[i]);
		v[dis[i]].push_back(i);
		MaxDep=max(dis[i],MaxDep);
	}
	if(v[0].size()!=1 || v[0].size()*k<v[1].size()) Exit(-1);
	if(n==1) Exit(0);
	for(int i=0;i<v[1].size();i++) ans.push_back(make_pair(v[0][0],v[1][i]));
	for(int i=2;i<=MaxDep;i++){
		if(v[i].size()==0) Exit(-1);
		if((v[i-1].size()*(long long)(k-1)<v[i].size() && i!=1)) Exit(-1);
		for(int j=0;j<v[i].size();j++)
			ans.push_back(make_pair(v[i-1][j/(k-1)],v[i][j]));
	}
	printf("%d\n",ans.size());
	for(int i=0;i<ans.size();i++)
		printf("%d %d\n",ans[i].first,ans[i].second);
	return 0;
}
```

---

