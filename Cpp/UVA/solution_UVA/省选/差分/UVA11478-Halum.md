# Halum

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=26&page=show_problem&problem=2473

[PDF](https://uva.onlinejudge.org/external/114/p11478.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11478/fe7bd946fb4e049b4a2acc693bd285a050d606f4.png)

## 样例 #1

### 输入

```
2 1
1 2 10
2 1
1 2 -10
3 3
1 2 4
2 3 2
3 1 5
4 5
2 3 4
4 2 5
3 4 2
3 1 0
1 2 -1```

### 输出

```
Infinite
Infinite
3
1```

# 题解

## 作者：Dfkuaid (赞：6)

> [题目链接](https://www.luogu.com.cn/problem/UVA11478)

## #0.0 题目翻译

给定一张带权有向图，定义操作 $\texttt{Halum(}x,d\texttt{)}$ 为将所有以 $x$ 为终点的边的权值减少 $d$，将所有以 $x$ 为起点的边的权值增加 $d$，问通过若干次这样的操作，可得到的最小边权的最大值是多少。

## #1.0 简单思路



不难发现，多次作用于同一个点的 $\texttt{Halum}$ 操作不受顺序影响，即先 $\texttt{Halum(}x,d_1\texttt{)}$ 再 $\texttt{Halum(}x,d_2\texttt{)}$ 和先 $\texttt{Halum(}x,d_2\texttt{)}$ 再 $\texttt{Halum(}x,d_1\texttt{)}$ 这两种操作顺序对结果没有影响，所以不妨设 $S_x$ 表示所有在 $x$ 上的操作的 $d$ 值之和。

看到**最小值最大**立刻想到二分答案，那么题目转化为给定 $t$，问是否存在操作使得对任意的边 $(x,y)$ 满足 

$$
w(x,y)-S_y+S_x\geq t
$$

即

$$
S_y-S_x\leq w(x,y)-t
$$

发现上式符合差分约束系统的式子，那么建一条 $x\to y$ 的边，权值为 $w(x,y)-t$ ，再新建一个 $0$ 号节点，向所有点连一条权值为 $0$ 的边，也就是将 $S$ 限制在负数，判断这张新图有没有负环即可。

但是，直接采用队列优化的 $\texttt{Bellman-Ford}$ 算法（$\texttt{SPFA}$）会 $\texttt{TLE}$，而我们只需要知道当前差分约束系统有没有解，所以可以采用 $\texttt{DFS}$ 实现对负环的判断，相对要更快。

**一点细节：**

- 二分答案时，假设当前中点为 $x$，若产生的差分约束系统中存在负环，说明 $x$ 太大了！且不是合法答案，应当执行 $r=x-1$，如果不存在负环，说明 $x$ 是合法答案，应当令 $l=x$（这里用 $l$ 记录答案），循环的终止条件为 $l=r$；
- 在求中点时应当是 $mid=\dfrac{l + r + 1}{2}$，$+1$ 的原因是不能整除的情况尽量往大里选，防止像 $l=12,r=13$，$l$ 合法，$r$ 不合法，但永远达不到 $l=r$ 的情况出现。

## #2.0 代码实现

``` cpp
#define mset(l, x) memset(l, x, sizeof(l))

const int N = 100010;
const int INF = 0x3fffffff;

struct Edge {
    int u, v, w;
    int nxt;
};
Edge e[N], ne[N];

int n, m, cnt, ncnt, head[N], nhead[N];
int inq[N], q[N], frt, tal, tot[N];
ll d[N];

inline void add(const int &u, const int &v, const int &w) {
    e[cnt].u = u, e[cnt].v = v, e[cnt].w = w;
    e[cnt].nxt = head[u], head[u] = cnt ++;
}

bool check_ring(int x) {
    inq[x] = true;
    for (int i = head[x]; i; i = e[i].nxt)
      if (d[e[i].v] > d[x] + e[i].w) {
          d[e[i].v] = d[x] + e[i].w;
          if (inq[e[i].v] || check_ring(e[i].v))
            return true;
          /*如果 x 找到一个当前在队列里的点 y ，
          也就意味着 y 本身可以更新 x 的最短路，
          而 x 又可以更新 y 的最短路，那么一定是产生了负环！*/
      }
    inq[x] = false;
    return false;
}

bool check(ll x) {
    mset(d, 0x3f); mset(inq, 0);
    d[0] = 0, inq[0] = 1;
    /*注意到本身边权只是减去 x，不必重新建图，直接修改边权即可*/
    for (int i = 1; i <= m; i ++) e[i].w -= x;
    bool res = check_ring(0);
    /*记得要把边权改回来*/
    for (int i = 1; i <= m; i ++) e[i].w += x;
    return res;
}

int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        cnt = 1; mset(head, 0);
        for (int i = 1; i <= m; i ++) {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            add(u, v, w);
        }
        for (int i = 1; i <= n; i ++) add(0, i, 0);
        int l = 0, r = 1e9, ans = 0;
        while (l < r) { //二分答案，注意边界
            int mid = (l + r + 1) >> 1;
            if (check(mid)) r = mid - 1;
            else l = mid;
        }
        if (l == 0) printf("No Solution\n");
        else if (l >= 1e7) printf("Infinite\n");
        else printf("%d\n", l);
    }
    return 0;
}
```

## End

希望能给您带来帮助。

---

## 作者：无言独上机房 (赞：6)

看到求最小值最大，很容易联想到二分答案。

考虑二分答案后检验，因为对每一个点只能做一次有效操作（假设第一次加+d1，第二次+d2,可以简化成+（d1+d2））。因此考虑对每一个点的操作值重新建图。

设从i到j有一条初始权值为v的边，当前要验证的最小值为mid，每个点的操作值为x[i]；很容易得到：v+x[i]-x[j]>=mid;
继而化简为x[j]-x[i]>=v-mid;

符合差分约束的模型。

于是从i到j建一条权值为v-mid的边，之后判负环即可。

下附AC代码
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	int to;
	int v;
	node(int a,int b)
	{
		to=a;
		v=b;
	}
};
vector<node>v[605];
int n,m,a[2705],b[2705],c[2705],d[605],vis[605],inque[605],flag;
void dfs(int x)
{
	if(flag) return;
	vis[x]=true;
	inque[x]=true;
	for(int i=0;i<v[x].size();i++)
	   {
	   		int y=v[x][i].to;
	   		if(d[y]>d[x]+v[x][i].v)
	   		{
	   			d[y]=d[x]+v[x][i].v;
	   			if(inque[y])
	   			{
	   				flag=1;
	   				return;
				}
				else {
					dfs(y);
				}
			}
	   }
	inque[x]=false;
}
bool check(int x)
{
	flag=0;
	memset(vis,0,sizeof(vis));
	memset(inque,0,sizeof(inque));
	for(int i=1;i<=n;i++)
	   	v[i].clear();
	for(int i=1;i<=m;i++)
	   v[a[i]].push_back(node(b[i],c[i]-x));
	memset(d,0x3f3f3f3f,sizeof(d));
	for(int i=1;i<=n;i++)
	   {
	   	if(vis[i]) continue;
	   	d[i]=0;
	   	dfs(i);
	   }
	if(flag) return false;
	else return true;
}

int main()
{
	while(cin>>n>>m)
	{
		for(int i=1;i<=m;i++)
		 	{
			 cin>>a[i]>>b[i]>>c[i];
			}
		int l=0,r=1e9;	
		while(l<r)
		{
			int mid=(l+r+1)/2;
			if(check(mid)) l=mid;
			else r=mid-1;
		}
		if(l==0) cout<<"No Solution"<<endl;
		else if(l>=500000) cout<<"Infinite"<<endl;
		else cout<<l<<endl;
	}
	
	
	
}
```

---

## 作者：Ray662 (赞：0)

### 题目大意

一个 $n$ 点 $m$ 边的有向图，操作 $\text{Halum(v, d)}$ 表示将终点为 $v$ 的所有边的权值减少 $d$，将起点为 $v$ 的所有边的边权加上 $d$。若干次操作，你要最大化边权最小的边的边权。

$n \le 500, m \le 2700, w_{u \to v} \le 1000$。

* * *

### 思路

“最大化最小”，很容易想到二分答案。

我们设当前最小的边权为 $x$，那么当前所有边的权值都 $\ge x$。

考虑对于同一个点 $u$ 的所有 $\text{Halum}(u, d)$ 的操作，每个操作的先后顺序对于答案没有影响，所以我们可以考虑将同一个点的所有 $\text{Halum}$ 操作合并为一个大操作。我们不妨设所有 $\text{Halum(u, d)}$ 的 $d$ 之和为 $D_u$。

再考虑 $\text{Halum}$ 操作的具体内容。影响一条边 $(u \to v)$ 权值的因素只有三个：

* 其本身的初始权值 $w_{u \to v}$
  
* 起点 $u$ 的操作 $D_u$
  
* 终点 $v$ 的操作 $D_v$
  

我们发现，$D_u$ 会给最终边 $(u \to v)$ 的权值 $g_{u \to v}$ 贡献 $D_u$，$D_v$ 会贡献 $- D_v$，所以最终 $g_{u \to v} = w_{u \to v} + D_u - D_v$。

上面提到，每个边权要 $\ge x$，所以可以列出不等式：

$$
w_{u \to v} + D_u - D_v \ge x
$$

整理得到：

$$
D_v - D_u \le w_{u \to v} - x
$$

看到这里想到了什么？[差分约束](https://oi-wiki.org/graph/diff-constraints/)！

于是我们每次 `check(mid)` 时就把每条边的边权减去 $x$。如果没有负环（即每个式子能同时成立），代表当前 $x$ 合法，标记答案为当前 $x$，然后继续往大的判断，即 `ans = mid, l = mid + 1`，否则 `r = mid - 1`。最后记得根据 $ans$ 的值判断输出即可。

时间复杂度大约 $O(T(m + n)\log n)$，$T$ 是数据组数。

综上，一个 dfs 判断负环（spfa 能卡到 $O(nm)$，有可能过不去） + 二分答案，还要记得多组数据清零。

代码很简单了，这里放一个 dfs 判断负环。

```cpp
bool dfs(int u) {  // true - 无负环，false - 有负环 
	vis[u] = 1;
	for (int i = head[u]; i; i = e[i].nxt)  if (D[e[i].to] > D[u] + e[i].w) {
		D[e[i].to] = D[u] + e[i].w;
		if (vis[e[i].to] || (! dfs(e[i].to)))  return false;  // 下一个点已访问或者有负环 
	}
	vis[u] = 0;
	return true;
}
```

---

