# [ABC317G] Rearranging

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc317/tasks/abc317_g

$ N $ 行 $ M $ 列のグリッドがあります。上から $ i $ 行目左から $ j $ 列目のマスには整数 $ A_{i,j} $ が書かれています。  
 ここで、グリッドのマスに書かれている計 $ NM $ 個の整数は $ 1,\ldots,N $ をちょうど $ M $ 個ずつ含みます。

あなたは次の手順でマスに書かれた数を入れ替える操作を行います。

- $ i=1,\ldots,N $ の順に次を行う。
  - $ i $ 行目に書かれた数を自由に並び替える。すなわち、$ 1,\ldots,M $ の並び替えである長さ $ M $ の数列 $ P=(P_{1},\ldots,P_{M}) $ を自由に選び、$ A_{i,1},\ldots,A_{i,M} $ を 同時に $ A_{i,P_{1}},\ldots,A_{i,P_{M}} $ に置き換える。
 
あなたの目的は、操作後に全ての列が $ 1,\ldots,N $ を $ 1 $ つずつ含むようにすることです。そのようなことが可能であるか判定し、可能であれば操作後のグリッドの状態を出力してください。

## 说明/提示

### 制約

- $ 1\ \leq\ N,M\ \leq\ 100 $
- $ 1\ \leq\ A_{i,j}\ \leq\ N $
- 入力は全て整数である
- $ NM $ 個の数 $ A_{1,1},\ldots,A_{N,M} $ は $ 1,\ldots,N $ をそれぞれちょうど $ M $ 個ずつ含む
 
### Sample Explanation 1

この他、以下の出力も正解とみなされる。 ``` Yes 1 1 2 3 3 2 ```

## 样例 #1

### 输入

```
3 2
1 1
2 3
2 3```

### 输出

```
Yes
1 1
3 2
2 3```

## 样例 #2

### 输入

```
4 4
1 2 3 4
1 1 1 2
3 2 2 4
4 4 3 3```

### 输出

```
Yes
1 4 3 2
2 1 1 1
4 2 2 3
3 3 4 4```

# 题解

## 作者：EuphoricStar (赞：11)

考虑转化成匹配问题。

对每行建点 $p_i$，每个数建点 $q_i$，$\forall i \in [1, n], j \in [1, m]$，连边 $(p_i, q_{a_{i, j}})$，问题转化成求这个二分图能否恰好被分解成 $m$ 组完美匹配以及方案。

直接给出做法：每次任意找出一组完美匹配，并把边从图中删除，做 $m$ 次。若有一次找不出完美匹配就无解。

为什么是对的呢？

考虑 Hall 定理。二分图有完美匹配的充要条件是，对于左部点集的任意一个子集 $S$，它的邻居集合 $N(S)$（可重集）均满足 $|S| \le |N(S)|$。

Hall 定理是可以推广的，二分图有 $m$ 组完美匹配的充要条件是，对于左部点集的任意一个子集 $S$，它的邻居集合 $N(S)$ 均满足 $m|S| \le |N(S)|$。

如果原图满足这个条件，那么随便删除一组完美匹配后也依然满足。如果原图不满足这个条件，那么它就找不出来 $m$ 组完美匹配。

使用 Dinic 求二分图匹配，复杂度 $O(n^{1.5}m^2)$。

[code](https://atcoder.jp/contests/abc317/submissions/44982376)

---

## 作者：SunnyYuan (赞：6)

借鉴了官方题解思路。

## 思路

首先我们要建立一个二分图。

对于输入的 $a_{i, j}$，我们可以连接 左侧的 $i$ 和 右侧的 $a_{i, j}$。

![](https://cdn.luogu.com.cn/upload/image_hosting/cqtder53.png)

比如样例 $1$：

注意：左边的 $1, 2, 3$ 和 右边的 $1, 2, 3$ 完全不一样，一个是行数，一个是数字。

![](https://cdn.luogu.com.cn/upload/image_hosting/4qzh8f73.png)

1. 那我们现在找出一组二分图的最大匹配，那么就代表对于固定的一列，第 $i$ 行的数字就可以确定了。

   比如上图中橙色的边，它们就是一组二分图的最大匹配，我们可以通过其知道对于一列，可以这么填：

$$
\begin{aligned}
1\\
3\\
2\\
\end{aligned}
$$

2. 我们将已经匹配的边删去，然后再跑下一次的二分图，构建下一列的数字。就这样执行 $m$ 遍，就可以做出答案。

   ![](https://cdn.luogu.com.cn/upload/image_hosting/zqiw3mq9.png)
    
   可以得到最大匹配，然后构建出这一列数字：


$$
\begin{aligned}
1\\
2\\
3\\
\end{aligned}
$$

3. 最后将这么多列数字按任意顺序输出就可以了。

$$
\begin{aligned}
\text{1 1}\\
\text{2 3}\\
\text{3 2}\\
\end{aligned}
$$

## 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 210, M = 40010, INF = 0x3f3f3f3f;

struct edge {
	int to, next, w;
} e[M];

int head[N], idx = 1;

void add(int u, int v, int w) {
	idx++, e[idx].to = v, e[idx].next = head[u], e[idx].w = w, head[u] = idx;
	idx++, e[idx].to = u, e[idx].next = head[v], e[idx].w = 0, head[v] = idx;
}

int S, T;
int n, m;
int q[N], hh, tt;
int d[N];
int ans[N][N];

bool bfs() {
	memset(d, 0, sizeof(d));
	hh = tt = 0;
	q[0] = S;
	d[S] = 1;

	while (hh <= tt) {
		int u = q[hh++];

		for (int i = head[u]; i; i = e[i].next) {
			int to = e[i].to;
			if ((!d[to]) && e[i].w) {
				d[to] = d[u] + 1;
				q[++tt] = to;
			}
		}
	}

	return d[T];
}

int dinic(int u, int limit) {
	if (u == T) return limit;

	int rest = limit;
	for (int i = head[u]; i && rest; i = e[i].next) {
		int to = e[i].to;
		if (d[to] == d[u] + 1 && e[i].w) {
			int k = dinic(to, min(rest, e[i].w));
			if (!k) d[to] = INF;
			rest -= k;
			e[i].w -= k;
			e[i ^ 1].w += k;
		}
	}
	return limit - rest;
}

int maxflow() {
	int ans = 0, flow = 0;
	while (bfs()) while (flow = dinic(S, INF)) ans += flow;
	return ans;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> n >> m;
	S = 0, T = n << 1 | 1;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			int x;
			cin >> x;
			add(i, x + n, 1);
		}
	}
	int tmp = idx;
	for (int i = 1; i <= n; i++) add(S, i, 1), add(i + n, T, 1);

	for (int j = 1; j <= m; j++) {
		if (maxflow() != n) {
			cout << "No\n";
			return 0;
		}
		for (int i = 3; i <= tmp; i += 2) if (e[i].w == 1) {
			int u = e[i].to, v = e[i ^ 1].to;
			ans[u][j] = v - n;
			e[i].w = e[i ^ 1].w = 0;
		}
		for (int i = tmp + 2; i <= idx; i += 2) {
			if (e[i].w == 1) {
				e[i ^ 1].w = 1;
				e[i].w = 0;
			}
		}
	}
	cout << "Yes\n";
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cout << ans[i][j] << ' ';
		}
		cout << '\n';
	}
	return 0;
}
```

---

## 作者：WhisperingWillow (赞：6)

考虑将题目简化。

既然是将每行重排，我们发现可以将每列拆开，单独做贡献。

我们对 $i\leftarrow a_{i,j}$ 连边跑二分图最大匹配。

如果匹配出的数字不等于 $n$，则说明是不可行的。

否则我们将用过的点删去，记录答案。

[$\large\text{AC\ Code}$](https://atcoder.jp/contests/abc317/submissions/46484344)

---

## 作者：LwxAkioi (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc317_g)

## 题意
给出一个 $n\times m$ 的矩阵，重新排每一行的元素，使得每一列的元素是 $1$ 到 $n$ 的排列。
## 题解
由于每一列的数字不能重复，且每一行的元素不能同时出现在一列中，

相当于一行一列只能匹配一个元素，与二分图一个元素只能匹配一个与它处于不同序列的元素的性质是差不多的，

所以可以考虑二分图，将左边的一类元素定为行编号，右边一类定为从一到 $n$ 的每个数字，

这样，每个元素相当于是每一行与此元素所代表的数字连得一条边。

连边时只需枚举每一行上的每一个元素，将这一行的编号与这一个元素所代表的数字连边。

边连完后，二分图可以用匈牙利算法增广路跑出完美匹配，这样每一行恰好能匹配一个数字，然后再将匹配成功的边删除，代表此边已经使用过。

具体代码比较简单，在此不赘述。

---

## 作者：__Louis__ (赞：0)

## 题解：AT_abc317_g [ABC317G] Rearranging 

### 题目大意

给定一个 $n\times m$ 的矩阵，求对每一排都重排以后，能否使得每一列是一个排列。 如果可以，输出一种方案。

保证每一种数字出现 $m$ 次。

### 思路

每一种排列都是一次二分图的匹配，所以其实我们只需要把行看作左节点，把数值看成右节点，做 $m$ 次匹配就可以了。

注意要用 dinic 优化。

### code


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define inf 0x3f3f3f3f3f3f3f
const int maxn=1e5+10;
const int maxv=1e3+10;
int head[maxn],w[maxn],to[maxn],nxt[maxn],cnt=1;
int n,m,s,t;
int ans[maxv][maxv];
void add_edge(int u,int v,int da){
	to[++cnt]=v;
	w[cnt]=da;
	nxt[cnt]=head[u];
	head[u]=cnt;
}

int cur[maxn],dis[maxn];
bool bfs(int begin,int end){
	queue<int> q;
	memset(dis,-1,sizeof(dis));
	dis[begin]=0,cur[begin]=head[begin];
	q.push(begin);
	while(!q.empty()){
		int u=q.front();
		q.pop();
		for(int i=head[u];i;i=nxt[i]){
			int v=to[i];
			if(dis[v]==-1&&w[i]>0){
				dis[v]=dis[u]+1;
				cur[v]=head[v];
				q.push(v);
				if(v==end) return true;
			} 
		}
	}
	return false;
}
int find(int u,int lim,int end){
	if(u==end) return lim;
	int sum=0;
	for(int i=cur[u];i&&sum<lim;i=nxt[i]){
		cur[u]=i;
		int v=to[i];
		if(dis[v]==dis[u]+1&&w[i]>0){
			int flow=find(v,min(w[i],lim-sum),end);
			if(!flow) dis[v]=-1;
			w[i]-=flow,w[i^1]+=flow;
			sum+=flow;
		}
	}
	return sum;
}
int dinic(int begin,int end){
	int ans=0,sum;
	while(bfs(begin,end))
		while(sum=find(begin,inf,end))
			ans+=sum;
	return ans;
}
int g[maxn];
signed main(){
	int n,m;
	scanf("%lld%lld",&n,&m);
	s=2*n+1,t=2*n+2;
	int a;
	for(int i=1;i<=n;i++){
		add_edge(s,i,1);
		add_edge(i,s,0);
		add_edge(i+n,t,1);
		add_edge(t,i+n,0);
		for(int j=1;j<=m;j++){
			scanf("%lld",&a);
			add_edge(i,a+n,1);
			add_edge(a+n,i,0);
		}
	} 
	for(int j=1;j<=m;j++){
		for(int i=head[s];i;i=nxt[i]){
			w[i]=1,w[i^1]=0;
		}
		for(int i=head[t];i;i=nxt[i]){
			w[i^1]=1,w[i]=0;
		}
		int f=dinic(s,t);
		if(f!=n){
			printf("No");
			return 0;
		}
		for(int i=1;i<=n;i++){
			for(int k=head[i];k;k=nxt[k]){
				int v=to[k];
				if(!g[k]&&v>n&&v<=2*n&&w[k]==0){
					g[k]=true;
					ans[i][j]=v-n;
					w[k^1]=0;
				}
			}
		}
	}
	printf("Yes\n");
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			printf("%lld ",ans[i][j]);
		}
		printf("\n");
	}
}
```

---

## 作者：ethan0328 (赞：0)

## 思路

考虑二分图匹配。

对于每个 $a_{i,j}$，把 $i$ 向 $a_{i,j}$ 连边。

一列的答案相当于把行的编号和 $1$ 到 $n$ 的值最大匹配。若最大匹配为 $n$，则这一列可行。

把匹配的边删掉，作 $m$ 遍就求出 $m$ 列的结果。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e2+10;
struct edge
{
    int next,to,mx;
};
int n,m,ind=1,a[N][N],out[N][N],head[N];
edge e[N*N];
int pos[N],now[N];
queue<int> q;
void add(int x,int y,int z)
{
    e[++ind].to=y;e[ind].mx=z;
    e[ind].next=head[x];head[x]=ind;
}
bool bfs(int s,int t)
{
    int x,y;
    for(int i=1;i<=n*2+2;i++)
    {
        pos[i]=-1;
        now[i]=head[i];
    }
    while(!q.empty())
    {
        q.pop();
    }
    pos[s]=1;
    q.push(s);
    while(!q.empty())
    {
        x=q.front();
        q.pop();
        for(int i=head[x];i;i=e[i].next)
        {
            y=e[i].to;
            if(pos[y]!=-1||!e[i].mx)
            {
                continue;
            }
            pos[y]=pos[x]+1;
            q.push(y);
            if(y==t)
            {
                return 1;
            }
        }
    }
    return 0;
}
int dfs(int x,int flow,int t)
{
    if(x==t)
    {
        return flow;
    }
    int rst=flow;
    for(;now[x];now[x]=e[now[x]].next)
    {
        int p=now[x];
        int y=e[p].to;
        if(pos[y]!=pos[x]+1||!e[p].mx)
        {
            continue;
        }
        int v=dfs(y,min(e[p].mx,rst),t);
        if(!v)
        {
            pos[y]=-1;
        }
        e[p].mx-=v;
        e[p^1].mx+=v;
        rst-=v;
        if(!rst)
        {
            break;
        }
    }
    return flow-rst;
}
int dinic(int s,int t)
{
    int ret=0;
    while(bfs(s,t))
    {
        ret+=dfs(s,2e18,t);
    }
    return ret;
}
signed main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			cin>>a[i][j];
			add(i,a[i][j]+n,1);
			add(a[i][j]+n,i,0);
		}
	}
	for(int i=1;i<=n;i++)
	{
		add(n*2+1,i,1);
		add(i,n*2+1,0);
		add(i+n,n*2+2,1);
		add(n*2+2,i+n,0);
	}
	for(int i=1;i<=m;i++)
	{
		if(dinic(n*2+1,n*2+2)<n)
		{
			cout<<"No";
			return 0;
		}
		for(int j=2;j<=n*m*2+1;j+=2)
		{
			if(e[j^1].mx==1)
			{
				e[j^1].mx=0;
				out[e[j^1].to][i]=e[j].to-n;
			}
		}
		for(int j=n*m*2+2;j<=ind;j+=2)
		{
			e[j].mx=1;e[j^1].mx=0;
		}
	}
	cout<<"Yes\n";
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			cout<<out[i][j]<<" ";
		}
		cout<<"\n";
	}
}
```


---

