# Nearest Opposite Parity

## 题目描述

给出一个长度为 $n$ 的序列 $a_1,a_2,\cdots,a_n$，当你在第 $i$ 号位置时，你可以一步跳到 $i-a_i$ 或 $i+a_i$。

对于每一个位置 $i$，你想知道最少需要多少步可以到达一个位置 $j$，使得 $a_j$ 与 $a_i$ 的奇偶性不同。

## 说明/提示

$1 \le n \le 2 \cdot 10^5$，$1 \le a_i \le n$。

## 样例 #1

### 输入

```
10
4 5 7 6 7 5 4 4 6 4
```

### 输出

```
1 1 1 2 -1 1 1 3 1 1 
```

# 题解

## 作者：quanjun (赞：11)

这个问题可以转换成图论模型，然后用广度优先搜索或者最短路算法（Dijkstra或者SPFA算法）进行求解。  
这里因为可能有些同学没有学到最短路算法，并且用最短路算法解决广搜可以解决的问题有一点杀鸡用牛刀的感觉（今年CSP-J复赛第4题可以用广搜做然而我也用了最短路SPFA算法），所以我这里还是讲解广度优先搜索解决这个问题。  
对于一个边权均为 $1$ 的图来说，我们通过广度优先搜索得到的就是最短路。因为此时一开始入队列的都是距起点 $0$ 的点，然后入队列的是距起点 $1$ 的点，然后入队列的是距起点 $2$ 的点，……（大家可以自己画图体会一下，此时的广度优先搜索就是一个层次遍历）

然后我们来看怎么使用广度优先搜索解决这个问题。  

首先对于 $a[i]$ 来说，  
- 如果 $i-a[i] \ge 1$，则从 $i-a[i]$ 向 $i$ 连一条边；
- 如果 $i+a[i] \le n$，则从 $i+a[i]$ 向 $i$ 连一条边。

然后就可以开始我们的搜索了。  
在搜索之前我们需要先开两个数组：
- $odd[i]$ 表示坐标为 $i$ 的点到大最近的一个奇数点所需的最少步数；
- $even[i]$ 表示坐标为 $i$ 的点到大最近的一个偶数点所需的最少步数。

我们先来求 $odd$ 值，  
我们从 $1$ 到 $n$ 遍历 $i$ ，
- 如果 $a[i]$ 是奇数，则设 $odd[i]$ 为 $0$，同时将其加入队列；
- 否则（$a[i]$ 为偶数），设 $odd[i]$ 为无穷大。

接下来每次从队列里面取出一个坐标 $u$，然后遍历所有 $u$ 可以到达的点 $v$ ，如果 $odd[v] > odd[u]+1$ ，则标记 $odd[v] = odd[u]+1$ ，同时将 $v$ 加入队列。  

最终每个点的 $odd$ 值即表示从坐标 $i$ 出发最少需要花费多少步能够到达一个奇数值得点。

然后我们再来求 $even$ 值（其实你们会发现是一样的道理），  
我们从 $1$ 到 $n$ 遍历 $i$ ，
- 如果 $a[i]$ 是偶数，则设 $odd[i]$ 为 $0$，同时将其加入队列；
- 否则（$a[i]$ 为奇数），设 $odd[i]$ 为无穷大。

接下来每次从队列里面取出一个坐标 $u$，然后遍历所有 $u$ 可以到达的点 $v$ ，如果 $odd[v] > odd[u]+1$ ，则标记 $odd[v] = odd[u]+1$ ，同时将 $v$ 加入队列。  

自此，我们就求解完了 $odd$ 和 $even$ 值。  

然后我们从 $1$ 到 $n$ 遍历坐标 $i$，
- 如果 $a[i]$ 是奇数，输出 $even[i]$；
- 如果 $a[i]$ 是偶数，输出 $odd[i]$。

实现代码如下：  
```c++
#include <bits/stdc++.h>
using namespace std;
const int maxn = 200020;
int n, a[maxn], odd[maxn], even[maxn];
vector<int> g[maxn];
queue<int> que;
int main() {
    cin >> n;
    for (int i = 1; i <= n; i ++) cin >> a[i];
    for (int i = 1; i <= n; i ++) {
        if (i-a[i] >= 1) g[ i-a[i] ].push_back(i);
        if (i+a[i] <= n) g[ i+a[i] ].push_back(i);
    }
    // odd
    for (int i = 1; i <= n; i ++) {
        if (a[i]%2) {
            odd[i] = 0;
            que.push(i);
        }
        else odd[i] = -1;
    }
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        int sz = g[u].size();
        for (int i = 0; i < sz; i ++) {
            int v = g[u][i];
            if (odd[v] == -1 || odd[v] > odd[u] + 1) {
                odd[v] = odd[u] + 1;
                que.push(v);
            }
        }
    }
    // even
    for (int i = 1; i <= n; i ++) {
        if (a[i] % 2 == 0) {
            even[i] = 0;
            que.push(i);
        }
        else even[i] = -1;
    }
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        int sz = g[u].size();
        for (int i = 0; i < sz; i ++) {
            int v = g[u][i];
            if (even[v] == -1 || even[v] > even[u] + 1) {
                even[v] = even[u] + 1;
                que.push(v);
            }
        }
    }
    for (int i = 1; i <= n; i ++) {
        if (i > 1) putchar(' ');
        if (a[i] % 2) cout << even[i];
        else cout << odd[i];
    }
    cout << endl;
    return 0;
}
```

---

## 作者：Fan_Tuan (赞：5)

## 题意：

[题意](https://www.luogu.com.cn/problem/CF1272E)

## 思路：

最短路，对于点 $i$，分别向 $i+a_i$ 和 $i-a_i$ 加一条权值为 1 的点。

暴力的话就是对于每个点都跑一遍最短路，偶数点找最短路最小的奇数点，奇数点找最短路最小的偶数点，显然过不去。

考虑建两个超级源点，奇数源点和偶数源点。将所有 $a_i$ 为偶数的点我们向偶数源点连一条权值为 0 的边，从源点**反向**跑一遍最短路，那么每个奇数节点此时的最短路的值一定是到所有偶数节点的最小步数。同理，从奇数节点**反向**跑一遍最短路，每个偶数节点此时最短路的值是到所有奇数节点的最小步数。

## 代码：

```cpp
#include <cstring>
#include <cstdio>
#include <queue>
#include <iostream>
#include <algorithm>
#include <string>
#define int long long
using namespace std;

inline int read() {
    int f = 0, s = 0;
    char ch = getchar();
    while (!isdigit(ch)) f |= ch == '-', ch = getchar();
    while (isdigit(ch)) s = s * 10 + (ch ^ 48), ch = getchar();
    return f ? -s : s;
}

void print (int x) {
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) print (x / 10);
    putchar(x % 10 + '0');
}

const int maxn = 2e6 + 10;
int n, num, head[maxn], dis[maxn], vis[maxn], a[maxn], ans[maxn];

struct node {
    int nex, to, w;
}edge[maxn << 1];

void add(int from, int to, int w) {
    edge[++num].nex = head[from];
    edge[num].to = to;
    edge[num].w = w;
    head[from] = num;
}
 
void spfa(int s) {
    memset(vis, 0, sizeof vis);
    memset(dis, 0x3f, sizeof dis);
    dis[s] = 0;
    vis[s] = 1;
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
        int p = q.front();
        q.pop();
        vis[p] = 0;
        for (int i = head[p]; i; i = edge[i].nex) {
            int to = edge[i].to;
            int w = edge[i].w;
            if (dis[to] > dis[p] + w) {
                dis[to] = dis[p] + w;
                if (vis[to] == 0) {
                    vis[to] = 1;
                    q.push(to);
                }
            }
        }
    }
}

signed main () {
    n = read();
    for (int i = 1; i <= n; i++) a[i] = read();
    for (int i = 1; i <= n; i++) {
        if (i + a[i] <= n) add(i + a[i], i, 1);
        if (i - a[i] >= 1) add(i - a[i], i, 1);
    } 
    for (int i = 1; i <= n; i++)
        if (a[i] & 1) add(n + 1, i, 0);
        else add(n + 2, i, 0);
    spfa(n + 1);
    for (int i = 1; i <= n; i++) if (a[i] % 2 == 0) ans[i] = dis[i];
    spfa(n + 2);
    for (int i = 1; i <= n; i++) if (a[i] & 1) ans[i] = dis[i];
    for (int i = 1; i <= n; i++) print(ans[i] != dis[0] ? ans[i] : -1), putchar(' ');
    return 0;
}
```

---

## 作者：wz20201136 (赞：2)

**BFS大法好！**
### 题解
方便理解，暂时将可以一步满足条件的点成为原点。

明确一点，一个点满足条件当且仅当这个点可以搜到一个原点。于是我们发现每个点的答案为最小的搜到原点的步数+1。显然可以BFS。由于直接搜的复杂度是 $O(n^2)$ 的，我们可以找出所有原点，建返图，这样就可以把时间复杂度将为 $O(n)$。
### 代码
```cpp
#include<bits/stdc++.h>//
using namespace std;
int n,a[200005],book[200005];
vector<int> E[200005];
bool check(int x)
{
	if(x-a[x]>0&&abs(a[x]-a[x-a[x]])%2) return 1;
	if(x+a[x]<=n&&abs(a[x]-a[x+a[x]])%2) return 1;
	return 0;
}
int main()
{
	cin>>n;
	queue<int> q;
	memset(book,-1,sizeof(book));
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)
	{
		if(i-a[i]>0) E[i-a[i]].push_back(i);
		if(i+a[i]<=n) E[i+a[i]].push_back(i);//建返图
	}
	for(int i=1;i<=n;i++)
		if(check(i)) book[i]=1,q.push(i);//原点
	while(q.size())//BFS
	{
		int u=q.front();
		q.pop();
		for(int i=0;i<E[u].size();i++)
		{
			int v=E[u][i];
			if(book[v]!=-1) continue;
			q.push(v);
			book[v]=book[u]+1;
		}
	}
	for(int i=1;i<=n;i++) cout<<book[i]<<' ';
	return 0;
}
```

---

## 作者：yangmuguang (赞：1)

### 题意

给出一个长度为 $n$ 的序列 $a_1,a_2,\cdots,a_n$，当你在第 $i$ 号位置时，你可以一步跳到 $i-a_i$ 或 $i+a_i$。

对于每一个位置 $i$，你想知道最少需要多少步可以到达一个位置 $j$，使得 $a_j$ 与 $a_i$ 的奇偶性不同。

### 思路

这个问题可以转化为：有一个无向图，每个节点有一个值，问对于每一个节点，至少要走多少步到一个值奇偶性不同的节点。

所以，我们可以在在这个图的反图上以所有偶数节点为起点跑一个多源 BFS，得到所有奇数节点离最近的偶数的距离，对偶数节点同理。

时间复杂度：$O(n)$。

### 代码

```
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define faster ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);ios_base::sync_with_stdio(0)
ll n,a[200005];
ll dis[200005];
ll ans[200005];
queue<ll>q;
vector<ll>con[200005];
void bfs()
{
	while (q.size())
	{
		ll x=q.front();q.pop();
		for (ll i=0;i<con[x].size();i++)
		{
			ll v=con[x][i];
			if (dis[x]+1<dis[v])
			{
				dis[v]=dis[x]+1;
				q.push(v);
			}
		}
	}
}
int main()
{
	faster;
	cin>>n;
	for (ll i=1;i<=n;i++)
	{
		cin>>a[i];
		if (i-a[i]>=1)con[i-a[i]].pb(i);
		if (i+a[i]<=n)con[i+a[i]].pb(i);
	}
	memset(ans,-1,sizeof(ans));
	memset(dis,0x3f,sizeof(dis));
	for (ll i=1;i<=n;i++)
	{
		if (a[i]%2==1)
		{
			q.push(i);
			dis[i]=0;
		}
	}
	bfs();
	for (ll i=1;i<=n;i++)
	{
		if (a[i]%2==0)
		{
			ans[i]=dis[i];
		}
	}
	memset(dis,0x3f,sizeof(dis));
	for (ll i=1;i<=n;i++)
	{
		if (a[i]%2==0)
		{
			q.push(i);
			dis[i]=0;
		}
	}
	bfs();
	for (ll i=1;i<=n;i++)
	{
		if (a[i]%2==1)
		{
			ans[i]=dis[i];
		}
	}
	for (ll i=1;i<=n;i++)
	{
		if (ans[i]<=1000000000)cout<<ans[i]<<" ";
		else cout<<"-1 ";
	}
	return 0;
}
```

---

## 作者：live_cxy110122 (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF1272E)

# 思路
- 对于每个下标 $i$ 去求答案，需要跑 $n$ 遍 BFS。
- 每个 $i$ 到达的目标位置要么为奇数位置要么为偶数位置，考虑逆向思维。
- 从所有的奇数位置沿反向边跑 BFS，那么等价于每个位置到奇数位置的最少步数，偶数位置同理。
- 对奇数位置和偶数位置分别跑多起点 BFS 即可。

# 代码

```cpp
#include<bits/stdc++.h>

using namespace std;

const int N = 2e5 + 5;

int dis1[N], dis2[N], a[N];
int n;
struct node{
    int id, step;
};
vector<int> nbr[N];

void bfs(int dis[], int val)
{
	queue<node> q;
	for(int i = 1; i <= n; i++)
    {
        if(a[i] % 2 == val) //多起点BFS，把所有的奇数/偶数入队
        {
            dis[i] = 0;
            q.push({i, 0});
        }
        else
            dis[i] = -1;
    }
	while(!q.empty())
    {
        int cur = q.front().id;
        int step = q.front().step;
        q.pop();
        for(int i = 0; i < nbr[cur].size(); i++)
        {
            int nx = nbr[cur][i];
            if(dis[nx] == -1)
            {
                dis[nx] = step + 1;
                q.push({nx, step + 1});
            }
        }
    }
	return ;
} 

int main()
{
	cin>>n;
    for(int i = 1; i <= n; i++)
    {
        cin>>a[i];
        if(i - a[i] >= 1)
            nbr[i-a[i]].push_back(i);
        if(i + a[i] <= n)
            nbr[i+a[i]].push_back(i);
    }
    bfs(dis1, 1);
    bfs(dis2, 0);
    for(int i = 1; i <= n; i++)
    {
        if(a[i] % 2 == 0)
            cout<<dis1[i]<<' ';
        else
            cout<<dis2[i]<<' ';
    }
	return 0;
}


```

---

## 作者：ATION001 (赞：0)

## 题目描述
有一个长度为 $n$ 的序列，在第 $i$ 号位置你可以跳到 $i-a_i$ 或者 $i+a_i$ 的位置，求到达每一个位置**最少**需要走几步，如果到达不了这个位置，输出 $-1$。
## 思路
相信看到“最少”两个字，童鞋们应该就能发现这是最短路算法了。其实这题用纯 BFS 的话真的不难，关键在于**如何转移**。我们可以预处理所有合法的转移，注意要判断边界。
```cpp
  if(i-a[i]>0){
  v[i-a[i]].push_back(i);
  }
  if(i+a[i]<=n){
    v[i+a[i]].push_back(i);
  }
```
其实这里的预处理是建图。

建完图就可以跑 BFS 了，首先数组初始值要赋值为 $-1$，然后从原点开始向外变量节点，没有遍历过的节点再进行操作。

最后就是代码啦。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int n,a[N],b[N];
queue<int>q;
vector<int>v[N];
bool c(int x)
{
	return ((x-a[x]>0&&abs(a[x]-a[x-a[x]])%2)||(x+a[x]<=n&&abs(a[x]-a[x+a[x]])%2)?1:0);
}
int main(){
	ios::sync_with_stdio(0),cin.tie(0);
	fill(b,b+N,-1);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=n;i++){
		if(i-a[i]>0){
			v[i-a[i]].push_back(i);
		}
		if(i+a[i]<=n){
			v[i+a[i]].push_back(i);
		}
		if(c(i)){
			b[i]=1,q.push(i);
		}
	}
	while(q.size()){
		auto p=q.front();
		q.pop();
		for(auto x:v[p]){
			if(b[x]==-1){
				q.push(x),b[x]=b[p]+1;
			}
		}
	}
	for(int i=1;i<=n;i++){
		cout<<b[i]<<' ';
	}
	return 0;
}
```

---

## 作者：Xdl_rp (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1272E)

solution：
------------
- 类似 `Dijkstra`（也可以用 `SPFA`，但是众所周知 `SPFA` 它死了）。
1. 反向建图：$n$ 个位置分别是 $n$ 个点，如果第 $i$ 个位置能跳到第 $j$ 个位置，就建一条从 $j$ 到 $i$ 的边。
2. 求偶数所在的位置至少跳多少步能到奇数所在的位置：将所有奇数所在的位置放进队列 $Q$ 中，进行 `bfs`。
3. 求奇数所在的位置至少跳多少步能到偶数所在的位置：将所有偶数所在的位置放进队列 $Q$ 中，进行 `bfs`。
4. 挨个输出 `bfs` 后的答案。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
int a[N], ans[N], spj[N], spo[N], n;
queue<int> q;
vector<int> tree[N];
bool visj[N], viso[N];
void bfs(bool flag) {
	if (flag == 1) {//如果是奇数
		while (!q.empty()) {
			int x = q.front();//取出队头
			q.pop();//删除队头
			for (int i = 0; i < tree[x].size(); i++) {//遍历它的所有边
				if (!visj[tree[x][i]]) {//没有访问过
					visj[tree[x][i]] = 1;//标记访问
					q.push(tree[x][i]);//加进队列
					spj[tree[x][i]] = spj[x] + 1;//记录步数
				}
			}
		}//是不是很像Dijkstra？
	}
	else {//如果是偶数
		while (!q.empty()) {//同上
			int x = q.front();
			q.pop();
			for (int i = 0; i < tree[x].size(); i++) {
				if (!viso[tree[x][i]]) {
					viso[tree[x][i]] = 1;
					q.push(tree[x][i]);
					spo[tree[x][i]] = spo[x] + 1;
				}
			}
		}
	}
}
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for (int i = 1; i <= n; i++) {
		if (i - 1 >= a[i]) tree[i - a[i]].push_back(i);
		if (n - i >= a[i]) tree[i + a[i]].push_back(i);
	}//反向建图
	for (int i = 1; i <= n; i++) if (a[i] % 2 == 1) q.push(i), visj[i] = 1;//是奇数就加进队列
	bfs(1);//bfs
	for (int i = 1; i <= n; i++) if (a[i] % 2 == 0) q.push(i), viso[i] = 1;//是偶数
	bfs(0);//同样
	for (int i = 1; i <= n; i++) {
		if (a[i] % 2 == 0) {
			if (visj[i] == 0) printf("-1 ");
			else printf("%d ", spj[i]);
		}//挨个输出
		else {
			if (viso[i] == 0) printf("-1 ");
			else printf("%d ", spo[i]);
		}//挨个输出
	}
	return 0;
}
```


---

