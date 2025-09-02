# [ABC168D] .. (Double Dots)

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc168/tasks/abc168_d

あるところに、洞窟があります。

洞窟には $ N $ 個の部屋と $ M $ 本の通路があり、部屋には $ 1 $ から $ N $ の、通路には $ 1 $ から $ M $ の番号がついています。通路 $ i $ は部屋 $ A_i $ と部屋 $ B_i $ を双方向につないでいます。どの $ 2 $ 部屋間も、通路をいくつか通って行き来できます。部屋 $ 1 $ は洞窟の入り口がある特別な部屋です。

洞窟の中は薄暗いので、部屋 $ 1 $ 以外の各部屋に $ 1 $ つずつ道しるべを設けることにしました。各部屋の道しるべは、その部屋と通路で直接つながっている部屋の $ 1 $ つを指すように置きます。

洞窟の中は危険なので、部屋 $ 1 $ 以外のどの部屋についても以下の条件を満たすことが目標です。

- その部屋から出発し、「いまいる部屋にある道しるべを見て、それが指す部屋に移動する」ことを繰り返すと、部屋 $ 1 $ に最小の移動回数でたどり着く。

目標を達成できる道しるべの配置が存在するか判定し、存在するならばそのような配置を $ 1 $ つ出力してください。

## 说明/提示

### 制約

- 入力はすべて整数
- $ 2\ \leq\ N\ \leq\ 10^5 $
- $ 1\ \leq\ M\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ A_i,\ B_i\ \leq\ N\ (1\ \leq\ i\ \leq\ M) $
- $ A_i\ \neq\ B_i\ (1\ \leq\ i\ \leq\ M) $
- どの $ 2 $ 部屋間も、通路をいくつか通って行き来できる

### Sample Explanation 1

出力例のように道しるべを置いたとき、 - 部屋 $ 2 $ から出発した場合 $ (2)\ \to\ 1 $ と $ 1 $ 回移動することになり、これが最小です。 - 部屋 $ 3 $ から出発した場合 $ (3)\ \to\ 2\ \to\ 1 $ と $ 2 $ 回移動することになり、これが最小です。 - 部屋 $ 4 $ から出発した場合 $ (4)\ \to\ 2\ \to\ 1 $ と $ 2 $ 回移動することになり、これが最小です。 したがって、出力例のように道しるべを置けば目標を達成できます。

### Sample Explanation 2

答えが複数あり得る場合、どれを出力してもかまいません。

## 样例 #1

### 输入

```
4 4
1 2
2 3
3 4
4 2```

### 输出

```
Yes
1
2
2```

## 样例 #2

### 输入

```
6 9
3 4
6 1
2 4
5 3
4 6
1 5
6 2
4 5
5 6```

### 输出

```
Yes
6
5
5
1
1```

# 题解

## 作者：small_john (赞：4)

## 前言

抢一波沙发。

## 思路

方法：BFS。

由于要让每个点离 $1$ 号洞穴最近，所以用 BFS 求最短。

设一个队列 $q$，其中有一个数 $1$。每次 BFS，搜队首直接连通的点，并把每个没标记过的路标指向指向队首，并入队。重复这个步骤直到 $q$ 为空。

BFS 完后，如果还有没标记过的，就输出 `No`，否则按格式输出即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5+5;
int n,m,x,y,ans[N];
vector<int> v[N];
void bfs()
{
	queue<int> q;
	q.push(1);
	while(!q.empty())
	{
		int x = q.front();q.pop();
		for(int i = 0;i<v[x].size();i++)
			if(!ans[v[x][i]])
				ans[v[x][i]] = x,q.push(v[x][i]);
	} 
}
bool ok()
{
	for(int i = 2;i<=n;i++)
		if(!ans[i])
			return 0;
	return 1;
} 
signed main()
{
	cin>>n>>m;
	for(int i = 1;i<=m;i++)
		cin>>x>>y,v[x].push_back(y),v[y].push_back(x);
	bfs();
	if(ok())
	{
		puts("Yes");
		for(int i = 2;i<=n;i++)
			cout<<ans[i]<<'\n';
	}
	else puts("No");
	return 0;
}
```

---

## 作者：kkxacj (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc168_d)

#### 题目大意

给出一个 $N$ 个点 $M$ 条边的无向图，求出除 $1$ 外每个点到 $1$ 的最短路径。

#### 思路

题目已经告诉你了，求最短路，我们可以用 bfs 求最短路，根据 bfs 的性质，第一次被遍历到的点它到 $1$ 的距离一定是最短的，如第一个样例：

![](https://cdn.luogu.com.cn/upload/image_hosting/9egs2lpl.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

由 $1$ 遍历到 $2$，$2$ 遍历 $3$ 和 $4$，由于 $3$ 和 $4$ 已经被标记过，所以无法继续更新。

code
```
#include<bits/stdc++.h>
using namespace std;
int n,m,x,y,kk[100010],b[1000010],he,t = 1,v[100010];
vector<int>a[100010];
void bfs()
{
	while(t <= he)
	{
		for(int i = 0;i < a[b[t]].size();i++)
		{
			if(!v[a[b[t]][i]])//没被遍历过 
			{
				v[a[b[t]][i]] = b[t];//标记 
				b[++he] = a[b[t]][i];
			}
		}
		t++;
	} 
}
int main()
{
	cin >> n >> m;
	while(m--)
	{
		cin >> x >> y;
		a[x].push_back(y);
		a[y].push_back(x);
	
	}
	b[++he] = 1;
	v[1] = 114514;
	bfs();
	for(int i = 2;i <= n;i++)
	{
		if(!v[i]) //如果没被便利到，说明不可以 
		{
			cout << "No";
			return 0;
		}
	}
	cout << "Yes" << endl;
	for(int i = 2;i <= n;i++) cout << v[i] << endl;
	return 0;
}

```


---

## 作者：Mu_leaf (赞：3)

## [题意]
给定一个 $n$ 个点，$m$ 条边的图，每条边的边权是 $1$ ，求除了 $1$ 号点外所有点到 $1$ 号点的最短路径的上第二个到达的点。

例如样例：
![](https://cdn.luogu.com.cn/upload/image_hosting/gwmfvqqx.png)

点 $3$ 到 $1$ 的最短路为 $3 \to 2 \to 1$,那么第二个到达的点便是 $2$。

允许多解。

## [思路]
bfs 模板题。

题目意思很明确了。既然边权是 $1$ 且 $m \leq 2\times10^5$ 那么跑一遍 bfs 即可。不过我们不能从第 $i$ 个点出发到达点 $1$。这样不仅不容易记录答案，而且会超时。

我们可以考虑逆向思维，那就是从点 $1$ 出发从一个点遍历到与它相邻的点时，那么与**它相邻的点的答案就是当前点**，把当前点记录下来即可。

需要注意的是：

- 输出 ```No``` 的时候，是在 $n$ 个点中有一个与点 $1$ 不连通。
 

# Code:
```cpp
#include <bits/stdc++.h>
#define Yes printf("Yes\n");
#define End printf("No\n");return 0;
using namespace std;
const int N=1e5+5;
vector<int> V[N];
int n,m;
int ans[N];
queue<int> q;
void bfs(int x){
	q.push(x);
	while(!q.empty()){
		int u=q.front();
		q.pop();
		for(int i=0;i<V[u].size();i++){
			int v=V[u][i];
			if(!ans[v]){
				ans[v]=u;
				q.push(v);
			}
		}
	}
}
int main(){
	cin >> n >> m;
	for(int i=1,u,v;i<=m;i++){
		cin >> u >> v;
		V[u].push_back(v);
		V[v].push_back(u); 
	}
//	memset(ans,-1,sizeof(ans));
	bfs(1); 
	for(int i=2;i<=n;i++){
		if(!ans[i]){End}
	}
	Yes
	for(int i=2;i<=n;i++){
		printf("%d\n",ans[i]);
	}
	return 0;
}
```



---

## 作者：_AyachiNene (赞：1)

# 思路：
由于每条边没有权值，可以把边权视为 $1$，所以可以直接用 bfs，每个点第一次搜到时就是它的最短路，在统计一下路径就行了。
# Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node
{
	int nxt,to;
}e[114514*4];
int head[114514],cnt,vis[114514];
void add(int u,int v)
{
	e[++cnt].to=v;
	e[cnt].nxt=head[u];
	head[u]=cnt;
}
int n,m,ans[114514];
queue<int>q;
void bfs(int s)
{
	q.push(s);
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		for(int i=head[u];i;i=e[i].nxt)
		{
			int v=e[i].to;
			if(!ans[v])
			{
				ans[v]=u;
				q.push(v);
			}
		}
	}
}
int main()
{	
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		int u,v;
		cin>>u>>v;
		add(u,v);
		add(v,u);
	}
	bfs(1);
	for(int i=1;i<=n;i++)
		if(!ans[i])
		{
			cout<<"No";
			return 0;
		}
	cout<<"Yes"<<endl;
	for(int i=2;i<=n;i++)
		cout<<ans[i]<<endl;
}
```


---

## 作者：YuTianQwQ (赞：1)

# 题目解析

这段代码的目标是在给定的图中找到从顶点 1 到所有其他顶点的路径。我们使用广度优先搜索（BFS）来找到这些路径。

## 解题思路

1. **读取输入**：首先，我们读取输入的顶点数 $n$ 和边数 $m$，然后读取每一条边的两个顶点 $u$ 和 $v$。

    ```cpp
    cin >> n >> m;
    for(int i = 0; i < m; i++)
    {
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    ```

2. **广度优先搜索**：从顶点 1 开始，执行广度优先搜索。

    ```cpp
    q.push(1);
    p[1] = 1;
    while(!q.empty())
    {
        u = q.front();
        q.pop();
        for(int i : g[u])
            if(!p[i])
                q.push(i), p[i] = u;
    }
    ```

3. **输出结果**：输出 "Yes"，然后输出从顶点 1 到所有其他顶点的路径。

	`puts("Yes");`
    
	`for(int i = 0; i < n - 1; i++) cout << p[i + 2] << endl;`

总的来说，我们使用广度优先搜索，从顶点 1 开始找到到所有其他顶点的路径。

# 完整代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int mx = 1e5+5;
int n, m, v, u, p[mx];
vector<int> g[mx];
queue<int> q;
int main()
{
    cin >> n >> m;
    for(int i = 0; i < m; i++) cin >> u >> v, g[u].push_back(v), g[v].push_back(u);
    q.push(1);
    p[1] = 1;
    while(!q.empty())
    {
        u = q.front();
        q.pop();
        for(int i : g[u])
            if(!p[i])
                q.push(i), p[i] = u;
    }
    puts("Yes");
    for(int i = 0; i < n - 1; i++) cout << p[i + 2] << endl;
}
```

---

