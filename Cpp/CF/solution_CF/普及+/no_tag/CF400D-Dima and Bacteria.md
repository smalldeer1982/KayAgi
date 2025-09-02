# Dima and Bacteria

## 题目描述

Dima took up the biology of bacteria, as a result of his experiments, he invented $ k $ types of bacteria. Overall, there are $ n $ bacteria at his laboratory right now, and the number of bacteria of type $ i $ equals $ c_{i} $ . For convenience, we will assume that all the bacteria are numbered from $ 1 $ to $ n $ . The bacteria of type $ c_{i} $ are numbered from ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF400D/982a571b1865821e9e229719b32d90deaece954a.png) to ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF400D/cadef4f1e0deb44673d0bf224d83a90828e59d96.png).

With the help of special equipment Dima can move energy from some bacteria into some other one. Of course, the use of such equipment is not free. Dima knows $ m $ ways to move energy from some bacteria to another one. The way with number $ i $ can be described with integers $ u_{i} $ , $ v_{i} $ and $ x_{i} $ mean that this way allows moving energy from bacteria with number $ u_{i} $ to bacteria with number $ v_{i} $ or vice versa for $ x_{i} $ dollars.

Dima's Chef (Inna) calls the type-distribution correct if there is a way (may be non-direct) to move energy from any bacteria of the particular type to any other bacteria of the same type (between any two bacteria of the same type) for zero cost.

As for correct type-distribution the cost of moving the energy depends only on the types of bacteria help Inna to determine is the type-distribution correct? If it is, print the matrix $ d $ with size $ k×k $ . Cell $ d[i][j] $ of this matrix must be equal to the minimal possible cost of energy-moving from bacteria with type $ i $ to bacteria with type $ j $ .

## 样例 #1

### 输入

```
4 4 2
1 3
2 3 0
3 4 0
2 4 1
2 1 2
```

### 输出

```
Yes
0 2
2 0
```

## 样例 #2

### 输入

```
3 1 2
2 1
1 2 0
```

### 输出

```
Yes
0 -1
-1 0
```

## 样例 #3

### 输入

```
3 2 2
2 1
1 2 0
2 3 1
```

### 输出

```
Yes
0 1
1 0
```

## 样例 #4

### 输入

```
3 0 2
1 2
```

### 输出

```
No
```

# 题解

## 作者：foryou_ (赞：5)

对于第一问，用并查集将所有边权为 $0$ 的边的端点合并，

然后对于每个 type 看里面是否所有的点都在一个集合中即可。

时间复杂度 $O(n \log n)$（默认使用路径压缩并查集）。

对于第二问，将 type 看作点，

对于每两个 type 取它们中两个点的最小边权连边，

然后跑 floyd 即可，时间复杂度 $O(k^3)$。

---

## 作者：wangboyue (赞：5)

# CF400D Dima and Bacteria 题解
## 思路
本题分为两步。  
1. 判断同一个种类中细菌是否可以以 $0$ 为代价互相连通。可以使用并查集。
2. 如果同一个种类中细菌是否可以以为 $0$ 代价互相连通，那么就需要求出 $d_{i,j}$ 的值。可以使用 Floyd。

详见代码。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int n,m,k,c[N],u[N],v[N],w[N],fa[N],dp[505][505],id[N];
int find(int x){
	if(fa[x]==x){
		return x;
	}
	return fa[x]=find(fa[x]);
}
void add(int x,int y){
	x=find(x);
	y=find(y);
	if(x!=y){
		fa[x]=y;
	}
	return;
}
void floyd(){
	for(int l=1;l<=k;l++){  //避免与k重名
		for(int i=1;i<=k;i++){
			for(int j=1;j<=k;j++){
				dp[i][j]=min(dp[i][j],dp[i][l]+dp[l][j]);
			}
		}
	}
	return;
}
int main(){
	cin>>n>>m>>k;
	memset(dp,0x3f,sizeof(dp));
	for(int i=1;i<=n;i++){
		fa[i]=i;
	}
	for(int i=1;i<=k;i++){
		dp[i][i]=0;
	}
	for(int i=1;i<=k;i++){
		cin>>c[i];
	}
	for(int i=1;i<=m;i++){
		cin>>u[i]>>v[i]>>w[i];
		if(w[i]==0){
			add(u[i],v[i]); //边权为0时将u和v合并
		}
	}
	int cnt=0;
	for(int i=1;i<=k;i++){
		for(int j=cnt+1;j<=cnt+c[i];j++){
			id[j]=i;    //id[i]表示细菌i所在的类型编号
			if(find(j)!=find(cnt+1)){
				cout<<"No";
				return 0;
			}
		}
		cnt+=c[i];
	}
	cout<<"Yes"<<endl;
	for(int i=1;i<=m;i++){
		int x=id[u[i]],y=id[v[i]];
		dp[x][y]=dp[y][x]=min(dp[x][y],w[i]);
	}
	floyd();
	for(int i=1;i<=k;i++){
		for(int j=1;j<=k;j++){
			if(dp[i][j]==0x3f3f3f3f){
				cout<<-1;
			}
			else{
				cout<<dp[i][j];
			}
			cout<<" ";
		}
		cout<<endl;
	}
	return 0;
}

```

---

## 作者：pzc2004 (赞：3)

[题目传送门](https://www.luogu.org/problem/CF400D)

直接用并查集把边权为0的两个点合并起来，然后看看同一个type的点是否在同一个集合中，最后在每个type之间建边，跑一遍Floyd即可。

代码：
``` cpp
#include<bits/stdc++.h>
inline int read(){int x=0;char c=getchar();while(c<'0' || c>'9')c=getchar();while(c>='0' && c<='9')x=(x<<3)+(x<<1)+(c^'0'),c=getchar();return x;}
int n,m,k,c[501],fa[100001],id[100001],dis[501][501],cnt;
struct sb{int a,b,c;}e[100001];
inline int find(const int &x){return fa[x]==x?x:fa[x]=find(fa[x]);}//并查集
inline bool cmp(const sb &a,const sb &b){return a.c<b.c;}
signed main()
{
	n=read(),m=read(),k=read();
	for(register int i=1;i<=n;i++)fa[i]=i;//并查集初始化
	for(register int i=1;i<=k;i++)c[i]=read();
	for(register int i=1;i<=m;i++)e[i].a=read(),e[i].b=read(),e[i].c=read();
	std::sort(e+1,e+m+1,cmp);
	for(register int i=1;i<=m;i++)
	{
		if(e[i].c>0)break;
		fa[find(e[i].a)]=find(e[i].b);//合并
	}
	for(register int i=1;i<=k;i++)
	{
		int x=find(cnt+1);
		id[cnt+1]=i;
		for(register int j=cnt+2;j<=cnt+c[i];j++){id[j]=i;if(find(j)!=x){printf("No");return 0;}}//判断是否在一个集合中
		cnt+=c[i];
	}
	for(register int i=1;i<=k;i++)for(register int j=1;j<=k;j++)if(i!=j)dis[i][j]=1000000000;//Floyd初始化
	for(register int i=1;i<=m;i++)dis[id[e[i].b]][id[e[i].a]]=dis[id[e[i].a]][id[e[i].b]]=std::min(dis[id[e[i].a]][id[e[i].b]],e[i].c);//建边
	for(register int l=1;l<=k;l++)for(register int i=1;i<=k;i++)for(register int j=1;j<=k;j++)dis[i][j]=std::min(dis[i][j],dis[i][l]+dis[l][j]);//Floyd
	printf("Yes\n");
	for(register int i=1;i<=k;i++){for(register int j=1;j<=k;j++)printf("%d ",dis[i][j]==1000000000?-1:dis[i][j]);printf("\n");}
}
```
![](https://www.luogu.org/images/congratulation.png)

---

## 作者：Stars_visitor_tyw (赞：2)

## CF400D Dima and Bacteria 题解
### 分析
算法：Floyd+并查集

比较直观的一道题。

做题步骤：

1. 并查集初始化，把所有点的父亲都设为这个点本身。

2. 读入数据。

3. 用结构体存储每条边。

4. 扫一遍每条边，若边权为 $0$，则将这条边的两个端点合并。

5. 记录每个点所在的集合并判断种类相同的点是否连通，若不连通输出 `No` 并结束程序。

6. 若程序没有结束，输出 `Yes` 并换行。

7. Floyd 初始化，将 $dp$ 数组赋值为极大值，并将 $dp[i][i]$ 设为 $0$。

8. 将每条边的边权与两个端点所在集合之前记录过的连通的边权取 $\min$。

9. 跑最短路。

10. 若两个集合的最短路不是极大值，证明可以到达，输出 $dp[i][j]$，否则输出 $-1$。

### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+5;
int n, m, k, a[N], fa[N], dp[505][505], type[N];
struct node
{
    int x, y, v;
}e[N];
int find(int x)//并查集寻找祖先
{
    if(fa[x]==x)
    {
        return x;
    }
    return fa[x]=find(fa[x]);
}
void unionn(int x, int y)//并查集合并两个点
{
    x=find(x), y=find(y);
    if(x!=y)
    {
        fa[x]=y;
    }
}
void init()//并查集初始化
{
    for(int i=1;i<=100000;i++)
    {
        fa[i]=i;
    }
}
void Floyd()//跑最短路
{
    for(int tmp=1;tmp<=k;tmp++)
    {
        for(int i=1;i<=k;i++)
        {
            for(int j=1;j<=k;j++)
            {
                dp[i][j]=min(dp[i][j],dp[i][tmp]+dp[tmp][j]);
            }
        }
    }
}
void output()//输出
{
    for(int i=1;i<=k;i++)
    {
        for(int j=1;j<=k;j++)
        {
            if(dp[i][j]==1000000000)
            {
                cout<<"-1 ";
            }
            else
            {
                cout<<dp[i][j]<<" ";
            }
        }
        cout<<"\n";
    }
}
void get_type()//检查是否连通并记录每个点所在集合
{
    int tmp=0;
    for(int i=1;i<=k;i++)
	{
		type[tmp+1]=i;
		for(int j=tmp+2;j<=tmp+a[i];j++)
		{
		    type[j]=i;
		    if(find(j)!=find(tmp+1))
		    {
		        cout<<"No";
		        exit(0);
		    }
		}
		tmp+=a[i];
	}
}
void input()//输入
{
    cin>>n>>m>>k;
    for(int i=1;i<=k;i++)
    {
        cin>>a[i];
    }
    for(int i=1;i<=m;i++)
    {
        cin>>e[i].x>>e[i].y>>e[i].v;
    }
}
void init_dp()//Floyd 初始化
{
    for(int i=1;i<=k;i++)
    {
        for(int j=1;j<=k;j++)
        {
            dp[i][j]=1e9;
        }
        dp[i][i]=0;
    }
}
signed main()
{
    init();
    input();
    for(int i=1;i<=m;i++)//合并边权为0的两个端点
    {
        if(e[i].v==0)
        {
            unionn(e[i].x,e[i].y);
        }
    }
    get_type();
    cout<<"Yes\n";
    init_dp();
    for(int i=1;i<=m;i++)//处理已连边集合最短路
    {
        int x=type[e[i].x], y=type[e[i].y];
        dp[x][y]=dp[y][x]=min(dp[x][y],e[i].v);
    }
    Floyd();
    output();
    exit(0);
}

---

## 作者：YNH_QAQ (赞：1)

[传送门](https://www.luogu.com.cn/problem/CF400D)。

算法：最短路（Floyd）+[并查集](https://www.luogu.com.cn/blog/1105650/bing-zha-ji)。

## 题目大意

1. 一个 $n$ 个点、$m$ 条边的带权值无向图。
2. 现在一共有 $k$ 种属性，每个点都有属性 $c_i$。

目标：如果同一颜色的节点可以以 $0$ 的代价连通，就求出不同颜色节点连通的最小代价。
## 思路
1. 合并边权为 $0$ 的端点。
2. 维护每个点所在的集合，判断种类相同的点是否连通，即 $k$ 个连通块。
3. 将每条边的边权与两个端点所在集合之前记录过的连通的边权取最小值，跑最短路。
4. 两个连通块的路径不是初始化时的极大值，可以到达，输出。

时间复杂度：$O(n \log n)$。
## 核心代码
```cpp
int num=0;
    for(int i=1;i<=k;i++){
		type[num+1]=i;
		for(int j=num+2;j<=num+b[i];j++){
		    type[j]=i;
		    if(find(j)!=find(num+1)){
		        cout<<"No";
		        return 0;
		    }
		}
		num+=b[i];
	}
    cout<<"Yes"<<endl;
    memset(dp,0x3f,sizeof(dp));
    for(int i=1;i<=k;i++) dp[i][i]=0;
    for(int i=1;i<=m;i++){
        int d=type[a[i].x];
		int c=type[a[i].y];
        dp[d][c]=dp[c][d]=min(dp[d][c],a[i].v);
    }
    for(int l=1;l<=k;l++){
        for(int i=1;i<=k;i++){
            for(int j=1;j<=k;j++){
                dp[i][j]=min(dp[i][j],dp[i][l]+dp[l][j]);
            }
        }
    }
    for(int i=1;i<=k;i++){
        for(int j=1;j<=k;j++)
            if(dp[i][j]==0x3f3f3f3f) cout<<"-1 ";
            else cout<<dp[i][j]<<" ";
        cout<<endl;
    }
```

---

## 作者：Weekoder (赞：1)

# CF400D Dima and Bacteria 题解

## 题目大意

有一个有 $n$ 个点，$m$ 条边的无向图，每条边都有边权，每个点 $i$ 都有一种颜色 $c_i$，一共有 $k$ 种颜色。

目标：

1. 判断同一种颜色的结点是否可以以 $0$ 的代价连通。

1. 若上面的条件成立，再求出不同颜色之间的结点连通的最小代价。

## 思路：

floyd + 并查集。

## 分析：

1. 可以将所有边权为 $0$ 的端点直接用**并查集**合并，后面就只需要判断同一种颜色的结点是否都在一个集合里。

合并代码：

```cpp
void merge(int x, int y) {
	int t1 = findf(x), t2 = findf(y);
	if (t1 != t2)
		f[t2] = t1;
}
```

2. 需要一个 $type$ 数组，$type_i$ 代表结点 $i$ 的颜色。在处理 $type$ 时，可以顺便判断是否在一个集合里，如果不在，直接输出 $\texttt{No}$。

```cpp
int tmp = 0;
	for (int i = 1; i <= k; i++) {
		type[tmp + 1] = i;
		for (int j = tmp + 2; j <= tmp + c[i]; j++) {
			type[j] = i;
			if (findf(tmp + 1) != findf(j)) {
				cout << "No";
				return 0;
			}
		}
		tmp += c[i];
	}
```

3. 把合并后的集合**看作一个点**，可以发现输出是一个邻接矩阵，所以考虑跑一遍 floyd，输出即可。

floyd 函数：

```cpp
void floyd() {
	for (int l = 1; l <= k; l++)
		for (int i = 1; i <= k; i++)
			for (int j = 1; j <= k; j++)
				if (dp[i][l] != INF && dp[l][j] != INF)
					dp[i][j] = min(dp[i][j], dp[i][l] + dp[l][j]);
}
```

输出：

```cpp
for (int i = 1; i <= k; i++)
		for (int j = 1; j <= k; j++)
			cout << (dp[i][j] == INF ? -1 : dp[i][j]) << (j == k ? "\n" : " ");
```
注意，在理论上不用把集合看作一个点，可以直接跑 floyd，但是原题的 $n$ 很大，但 $k$ 比较小，所以把集合看作点是必须的。

完整代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5, K = 505, INF = 0x3f3f3f3f;
int n, m, k, c[K], f[N + 1], dp[K][K], type[N];
struct Edge {
	int u, v, w;
}e[N];
void floydinit() {
	memset(dp, 0x3f, sizeof dp);
	for (int i = 1; i <= k; i++) dp[i][i] = 0;
}
void floyd() {
	for (int l = 1; l <= k; l++)
		for (int i = 1; i <= k; i++)
			for (int j = 1; j <= k; j++)
				if (dp[i][l] != INF && dp[l][j] != INF)
					dp[i][j] = min(dp[i][j], dp[i][l] + dp[l][j]);
}
void fa_init() {
	for (int i = 1; i <= N; i++)
		f[i] = i;
}
int findf(int i) {
	if (f[i] == i)
		return i;
	return f[i] = findf(f[i]);
}
void merge(int x, int y) {
	int t1 = findf(x), t2 = findf(y);
	if (t1 != t2)
		f[t2] = t1;
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin >> n >> m >> k;
	fa_init();
	floydinit();
	for (int i = 1; i <= k; i++) cin >> c[i];
	for (int i = 1; i <= m; i++) {
		cin >> e[i].u >> e[i].v >> e[i].w;
		if (!e[i].w) merge(e[i].u, e[i].v);
	}
	int tmp = 0;
	for (int i = 1; i <= k; i++) {
		type[tmp + 1] = i;
		for (int j = tmp + 2; j <= tmp + c[i]; j++) {
			type[j] = i;
			if (findf(tmp + 1) != findf(j)) {
				cout << "No";
				return 0;
			}
		}
		tmp += c[i];
	}
	cout << "Yes\n";
	for (int i = 1; i <= m; i++) {
		int x = type[e[i].u], y = type[e[i].v];
		dp[x][y] = dp[y][x] = min(dp[x][y], e[i].w);
	}	
	floyd();
	for (int i = 1; i <= k; i++)
		for (int j = 1; j <= k; j++)
			cout << (dp[i][j] == INF ? -1 : dp[i][j]) << (j == k ? "\n" : " ");
	return 0;
}
```

---

## 作者：huangmingyi (赞：1)

首先我翻译一下([来源](https://gonoi.com.cn/problem/CF400D))：  
Dima 研究了细菌的生物学，他发明了 $k$ 种细菌。目前实验室中有 $n$ 个细菌，其中第 $i$ 种细菌的数量为 $c_i$。为了方便，我们将所有细菌从 $1$ 到 $n$ 编号，第 $i$ 种细菌从 $i$ 到 $i + ci - 1$ 编号。Dima 可以利用特殊的设备将能量从某些细菌转移至其他细菌，但这并非免费。Dima 知道 $m$ 种从一个菌落向另一个菌落转移能量的方式。第 $i$ 种转移能量的方式可以用整数 $u_i$、$v_i$ 和 xi 描述，表示该方式允许以 $x_i$ 美元的价格从编号为 $u_i$ 的细菌向编号为 $v_i$ 的细菌转移能量，或相反地。对于任意特定种类的细菌，如果存在一种（可非直接的）移动方式，其可以使此类细菌的任何细菌将能量传递至同类细菌中的任何其他细菌并且不需要费用，则称类型分布正确。对于类型分布不正确的情况，能量转移的成本将取决于哪些类型的细菌，帮助 Inna 确定类型分布是否正确。如果是，则按以下方式输出矩阵 $d$，其大小为 $k \times k$。该矩阵的第 $d_{i,j}$ 个单元格必须等于从第 $i$ 种细菌转移能量至第 $j$ 种细菌时的最小成本。
注意：这里假设移能的成本在不同的方法间始终不变。

### 分析
1. 由于 $n$ 达到了 $10^5$，因此不能对个数跑 floyd，但是种类 $k$ 只有 $5 \times 10^2$，所以转化为对细菌种类做 floyd。
2. 对于边权为 $0$ 的两种细菌，用并查集合并。
3. 维护 $pos_i$ 表示第 $i$ 个细菌所属的并查集。
4. 跑 floyd 之前检查每种细菌是否在同一个连通块上面。
5. 把所有的连通块视为新的点，对于原来的 $m$ 条边 $u_i$ 指向 $v_i$，边权为 $x_i$，新的边。

```
dp[id[u[i]]][id[v[i]]]=dp[id[v[i]]][id[u[i]]]=min(dp[id[v[i]]][id[u[i]]],x[i]);
```

6. 对新图跑 floyd。

```
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int n,m,k,b[N],fa[N],dp[505][505],type[N];
struct node{
    int x,y,v;
}a[N];
int find(int x){
	if(fa[x]==x){
		return x;
	}
	return fa[x]=find(fa[x]);
}
void un(int x,int y){
	x=find(x);
	y=find(y);
	if(x!=y){
		fa[x]=y;
	}
	return ;
}
signed main(){
    for(int i=1;i<=N;i++){
        fa[i]=i;
    }
    cin>>n>>m>>k;
    for(int i=1;i<=k;i++){
        cin>>b[i];
    }
    for(int i=1;i<=m;i++){
        cin>>a[i].x>>a[i].y>>a[i].v;
    }
    for(int i=1;i<=m;i++){
        if(a[i].v==0){
            un(a[i].x,a[i].y);
        }
    }
    int num=0;
    for(int i=1;i<=k;i++){
		type[num+1]=i;
		for(int j=num+2;j<=num+b[i];j++){
		    type[j]=i;
		    if(find(j)!=find(num+1)){
		        cout<<"No";
		        return 0;
		    }
		}
		num+=b[i];
	}
    cout<<"Yes"<<endl;
    memset(dp,0x3f,sizeof(dp));
    for(int i=1;i<=k;i++){
        dp[i][i]=0;
    }
    for(int i=1;i<=m;i++){
        int d=type[a[i].x];
		int c=type[a[i].y];
        dp[d][c]=dp[c][d]=min(dp[d][c],a[i].v);
    }
    for(int l=1;l<=k;l++){
        for(int i=1;i<=k;i++){
            for(int j=1;j<=k;j++){
                dp[i][j]=min(dp[i][j],dp[i][l]+dp[l][j]);
            }
        }
    }
    for(int i=1;i<=k;i++){
        for(int j=1;j<=k;j++){
            if(dp[i][j]==0x3f3f3f3f){
                cout<<"-1";
            }else{
                cout<<dp[i][j];
            }
            cout<<" ";
        }
        cout<<endl;
    }
    return 0;
}
```

---

## 作者：CRTL_xzh2009 (赞：0)

先并查集。

第一步验证同种细菌间能力转移是否代价为 $0$，可以使用单源最短路 $K$ 次，但最快的算法应该是并查集，只要边权是 $0$ 的就并，同时可以记录不同种类细菌间转移的最小代价。

然后多源最短路。

再用 Floyd 算法求不同种类间的多源最短路。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,k,fa[200005],num[200005],belong[200005],d[505][505],p;
inline long long read()
{
	long long x=0,f=1;
	char ch=getchar();
	while(ch<'0'||'9'<ch)
	{
	    if (ch=='-') f=-f; 
		ch=getchar();
	}
	while('0'<=ch&&ch<='9')
	{
	    x=x*10+ch-'0',ch=getchar();
	}
	return x*f;
}
inline long long find(long long x)
{
    if(x==fa[x])  
	    return fa[x];
    return fa[x]=find(fa[x]);
}
inline void merge(long long x,long long y)
{
	if((x=find(x))==(y=find(y)))
	    return;
	fa[y]=x;
}
inline bool pd()
{
    p=1;
    for(int i=1;i<=k;++i)
	{
        int x=find(p);
        for(int j=1;j<=num[i];++j)
            if(find(p++)!=x) 
			    return false;
    }  
    return true;
}
inline void floyd()
{
    for(int p=1;p<=k;++p)
        for(int i=1;i<=k;++i)
            for(int j=1;j<=k;++j)
                d[i][j]=min(d[i][j],d[i][p]+d[p][j]);
}
int main()
{
	memset(d,INT_MAX,sizeof d);
    n=read(),m=read(),k=read();
    for(int i=1;i<=k;++i)
            for(int j=1;j<=k;++j)
			{
                if(i==j) 
				    d[i][j]=d[j][i]=0;
                else 
				    d[i][j]=d[j][i]=INT_MAX;
            }    
    for(int i=1;i<=n;++i) fa[i]=i;
    p=1;
    for(int i=1;i<=k;++i)
	{
        num[i]=read();
        for(int j=1;j<=num[i];j++) 
		    belong[p++]=i;
    }
    while(m--){
        int u=read(),v=read(),w=read();
        if(!w) merge(u,v);
        register int uu=belong[u],vv=belong[v];   
        d[uu][vv]=d[vv][uu]=min(d[uu][vv],(long long)w);
    }
    if(!pd()){
        puts("No");
        return 0;
    }
    else
	{
        puts("Yes");
        floyd();
        for(int i=1;i<=k;++i)
		{
            for(int j=1;j<=k;++j)
			{
                if(i==j) d[i][j]=0;
                if(d[i][j]==INT_MAX) 
				    d[i][j]=-1;  
            if(j<k) 
			    printf("%lld ",d[i][j]); 
            else 
			    printf("%lld",d[i][j]);
        }
        puts("");
    	}
    }
    return 0;
}
```


---

## 作者：Allanljx (赞：0)

## 思路
首先将颜色相同的点缩成一个点，并判断是否能以 $0$ 的代价相连通（将被一条边权为 $0$ 的边连接的两个点加入一个集合中，然后判断颜色相同的点是否在同一个集合中）。然后将新的图建边（一定要取最小值，~~我就被这个卡了很久~~ ）。最后跑一遍弗洛伊德求最短路。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,k,d;
int c[505];
vector<pair<int,int> > t[100005];//存初始的图
int book[100005];
int b[100005];//颜色
int u[100005],v[100005],w[100005];
int t1[505][505];//floyd
signed main()
{
	cin>>n>>m>>k;
	for(int i=1;i<=k;i++) cin>>c[i];
	int la=1;
	for(int i=1;i<=k;i++)
	{
		for(int j=la;j<la+c[i];j++) b[j]=i;
		la=la+c[i];//上一种颜色的结尾的下标
	}
	for(int i=1;i<=m;i++)
	{
		cin>>u[i]>>v[i]>>w[i];
		t[u[i]].push_back(make_pair(v[i],w[i]));
		t[v[i]].push_back(make_pair(u[i],w[i]));//建图
		if(w[i]==0)//将相同颜色的点缩成一个点
		{
			if(book[u[i]])
			{
				book[v[i]]=book[u[i]];
			}
			else if(book[v[i]])
			{
				book[u[i]]=book[v[i]];
			}
			else book[u[i]]=++d,book[v[i]]=d;
		}
	}
	memset(t1,0x3f,sizeof(t1));
	int sum=0;
	for(int i=1;i<=k;i++)
	{
		int f=0;
		for(int j=sum+2;j<=sum+c[i];j++)
		{
			if(book[j]!=book[j-1]||book[j]==0)//判断同一种颜色的点能否以0的代价联通
			{
				f=1;
				break;
			}
		}
		if(f) return puts("No"),0;
		sum+=c[i];
	}
	for(int i=1;i<=m;i++)
	{
		t1[b[u[i]]][b[v[i]]]=t1[b[v[i]]][b[u[i]]]=min(w[i],t1[b[v[i]]][b[u[i]]]);//建缩点后的新图
	}
	for(int i=1;i<=k;i++) t1[i][i]=0;
	cout<<"Yes\n";
	for(int k1=1;k1<=k;k1++)//跑floyd
	{
		for(int i=1;i<=k;i++)
		{
			for(int j=1;j<=k;j++)
			{
				t1[i][j]=min(t1[i][j],t1[i][k1]+t1[k1][j]);
			}
		}
	}
	for(int i=1;i<=k;i++)
	{
		for(int j=1;j<=k;j++)
		{
			if(t1[i][j]!=t1[0][0]) cout<<t1[i][j]<<' ';
			else cout<<-1<<' ';//不能到达
		}
		cout<<endl;
	}
}
```


---

## 作者：liyichun001 (赞：0)

[题目传送门](https://www.luogu.org/problem/CF400D)
## 思路：
先对每个集合的点进行编号，然后用并查集判断是否满足同个集合任意两点距离为 0，如果满足，就用 Floyd 求传递闭包算出任意两个集合的点移动所需花费
```cpp
#include<bits/stdc++.h>
#define INF 0x3f3f3f3f
#define N 100001
#define LL long long
using namespace std;
LL n,m,k;
LL G[1001][1001];
LL father[N];
LL Set[N],num[N];
LL Find(LL x){
    if(x!=father[x])
        father[x]=Find(father[x]);
    return father[x];
}
void Union(LL x,LL y){
    x=Find(x);
    y=Find(y);
    if(x!=y)
        father[y]=x;
}
bool judge(){
    LL cnt=1;
    for(LL i=1;i<=k;i++){
        LL x=Find(cnt);
        for(LL j=1;j<=Set[i];j++)
            if(Find(cnt++)!=x)
                return false;
    }
    return true;
}
void floyd(){
    for(LL p=1;p<=k;p++)
        for(LL i=1;i<=k;i++)
            for(LL j=1;j<=k;j++)
                G[i][j]=min(G[i][j],G[i][p]+G[p][j]);
}
int main(){
    while(scanf("%lld%lld%lld",&n,&m,&k)!=EOF){
        memset(G,INF,sizeof(G));
        for(LL i=1;i<=k;i++){
            for(LL j=1;j<=k;j++){
                if(i==j){
                    G[i][j]=0;
                    G[j][i]=0;
                }
                else{
                    G[i][j]=INF;
                    G[j][i]=INF;
                }
            }
        }
        for(LL i=1;i<=n;i++) father[i]=i;
        LL cnt=1;
        for(LL i=1;i<=k;i++){
            scanf("%lld",&Set[i]);
            for(LL j=1;j<=Set[i];j++)//对集合进行分组
                num[cnt++]=i;
        }
        while(m--){
            LL x,y,w;
            scanf("%lld%lld%lld",&x,&y,&w);
            if(!w)
                Union(x,y);
            LL u=num[x],v=num[y];
            G[u][v]=min(G[u][v],w);
            G[v][u]=min(G[u][v],w);
        }
        if(!judge()){
            printf("No\n");
        }
        else{
            printf("Yes\n");
            floyd();
            for(LL i=1;i<=k;i++){//枚举集合
                for(LL j=1;j<=k;j++){
                    if(i==j)
                        G[i][j]=0;
                    if(G[i][j]==INF)//不能到达
                        G[i][j]=-1;
                    if(j<k)
                        printf("%lld ",G[i][j]);
                    else
                        printf("%lld",G[i][j]);
                }
                 printf("\n");
            }
        }
    }
    return 0;
}

---

