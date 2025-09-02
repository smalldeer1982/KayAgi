# [CCC 2020] Escape Room

## 题目背景

本题译自 [Canadian Computing Competition](https://cemc.uwaterloo.ca/resources/past-contests?contest_category=29) [2020 Senior](https://cemc.uwaterloo.ca/sites/default/files/documents/2020/2020CCCSrProblemSet.html) T2/[2020 Junior](https://cemc.uwaterloo.ca/sites/default/files/documents/2020/2020CCCJrProblemSet.html) T5 Escape Room。

## 题目描述

你需要判断是否可以从一个房间逃脱。房间是一个 $m$ 行 $n$ 列的矩阵，每个位置包含一个正整数。我们用 $(x,y)$ 表示第 $x$ 行，第 $y$ 列的单元格。

当你从 $(1,1)$ 开始，并成功走到 $(m,n)$ 时，你便成功逃脱了。如果你在一个包含值 $num$ 的单元格中，那么若你可以跳到 $(x,y)$，当前仅当 $x \times y=num$。例如，如果你在一个包含 $6$ 的单元格中，你可以跳到单元格 $(2,3)$。

## 说明/提示

#### 【样例解释】
从 $(1,1)$ 开始，其包含的值为 $3$，从这里可以跳到单元格 $(1,3)$。

这个单元格包含 $8$，因此从这里可以跳到单元格 $(2,4)$。

这个单元格包含 $12$，因此从这里可以跳到单元格 $(3,4)$。
#### 【数据范围】
**本题采用捆绑测试**。

由于原题 Subtask 分值，本题满分 105 分。
| Subtask | 特殊性质 | 分值 |
| :----------: | :----------: | :----------: |
| 1 | $m=n=2$ | 7 |
| 2 | $m=1$ | 14 |
| 3 | 所有单元格中的整数是唯一的 | 28 |
| 4 | $1\le m,n \le200$ | 28 |
| 5 | 无 | 28 |

## 样例 #1

### 输入

```
3
4
3 10 8 14
1 11 12 12
6 2 3 9```

### 输出

```
yes```

# 题解

## 作者：KukCair (赞：4)

搜索。

对于每个位置 $(i, j)$，让 $i \times j$ 向 $num_{i, j}$ 连一条边，所以起点为 $1$，终点为 $n \times m$。

然后 bfs/dfs 即可。

$n$ 和 $m$ 别搞反了，不然喜获 $77$ pts。

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;      
int m, n;
bool f[1000005];
vector<int> vc[1000005];
void bfs(){
	queue<int> q;
	q.push(1);
	f[1] = 1;
	while(q.size()){
		int fr = q.front();
		q.pop();
		for(int i = 0; i < vc[fr].size(); i++){
			int v = vc[fr][i];
			if(f[v]) continue;
			f[v] = 1;
			q.push(v);
		}
	}
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> m >> n;
	for(int i = 1; i <= m; i++){
		for(int j = 1; j <= n; j++){
			int num;
			cin >> num;
			vc[i * j].push_back(num);
		}
	}
	bfs();
	if(f[n * m]) cout << "yes";
	else cout << "no";
	return 0;
}
```

---

## 作者：John2014 (赞：2)

# P11580 [CCC2020] Escape Room 题解

## 思路

搜索，暴力代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[1010][1010];
struct point{
	int x,y;
};
queue<point> q;
int used[1010][1010];
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>a[i][j]; //输入数据 
		}
	}
	point s;
	s.x=1,s.y=1;
	q.push(s); //起点入队
	used[s.x][s.y]=1; //标记起点 
	while(!q.empty()){
		point u=q.front(); //取出队首 
		point v;
		q.pop();
		for(int i=1;i<=a[u.x][u.y];i++){
			if(a[u.x][u.y]%i==0){ //如果这个格子的num可以被i整除 
				v.x=i,v.y=a[u.x][u.y]/i; //跳转的位置 
				if(v.x<1||v.y<1||v.x>n||v.y>m){ //越界 
					continue;
				}
				if(used[v.x][v.y]){ //已经走过 
					continue;
				}
				q.push(v); //将新的点入队 
				used[v.x][v.y]=1; //标记used 
				if(v.x==n&&v.y==m){
					cout<<"yes";
					return 0;
				}
			}
		}
	}
	cout<<"no";
	return 0;
}
```

经过分析，我们发现速度慢在枚举因数这里。于是我们可以在输入时先预处理出每个 $num$ 可以跳到的位置。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[1010][1010];
struct point{
	int x,y;
};
queue<point> q;
vector<point> t[1000010]; //预处理数组 
int used[1010][1010];
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>a[i][j]; //输入数据 
			point x;
			x.x=i,x.y=j;
			t[i*j].push_back(x);
		}
	}
	point s;
	s.x=1,s.y=1;
	q.push(s); //起点入队
	used[s.x][s.y]=1; //标记起点 
	while(!q.empty()){
		point u=q.front(); //取出队首
		q.pop();
		for(point v:t[a[u.x][u.y]]){
			if(used[v.x][v.y]){ //已经走过 
				continue;
			}
			q.push(v); //将新的点入队 
			used[v.x][v.y]=1; //标记used 
			if(v.x==n&&v.y==m){
				cout<<"yes";
				return 0;
			}
		}
	}
	cout<<"no";
	return 0;
}
```

---

## 作者：zhoujunchen (赞：2)

建议评黄或橙。

做题思路
--

一道搜索。

考虑到 $n\times m\le10^6$，我们可以根据矩阵建边，对于坐标 $(i,j)$，连一条从 $i\times j$ 到 $a_{i,j}$ 的边，然后 BFS/DFS 看 $(n,m)$ 走没走过。

code:


```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	int x,y,num;
};
vector<node> g[1000005];
int n,m,st,a[1005][1005],vis[1005][1005];
void bfs(int sx,int sy){
	queue<node> q;
	q.push({sx,sy,a[sx][sy]});
	vis[sx][sy]=1;
	while(q.size()){
		node top=q.front();
		q.pop();
		for(auto [x,y,num]:g[top.num])if(!vis[x][y])vis[x][y]=1,q.push({x,y,num});
	}
}
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		    cin>>a[i][j],g[i*j].push_back({i,j,a[i][j]});
	bfs(1,1);
	cout<<(vis[n][m]?"yes":"no");
	return 0;
}
```

---

## 作者：jojo222 (赞：2)

先用 vector 记录那些点能跳到积为 $num$ 的位置，再从 $(n,m)$ 开始反着跑一遍 bfs，最后输出 $(1,1)$ 是否被标记。

代码极短：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m;
bool vis[1001][1001];
vector<pair<int, int>> nxt[1000001];
queue<pair<int, int>> q; 
int main()
{
	cin >> n >> m;
	for(int i = 1, x; i <= n; i++)
		for(int j = 1; j <= m; j++)
		{
			scanf("%d", &x);
			nxt[x].push_back({i, j});
		}
	vis[n][m] = true, q.push({n, m});
	while(!q.empty())
	{
		auto x = q.front();
		q.pop();
		for(auto y : nxt[x.first * x.second])
		{
			if(vis[y.first][y.second]) continue;
			vis[y.first][y.second] = true;
			q.push(y);
		}
	}
	if(vis[1][1]) cout << "yes";
	else cout << "no";
	return 0;
}
```

---

## 作者：signed_long_long (赞：1)

# 题目解法

## 做法一

直接暴力 BFS，枚举 $num_{i,j}$ 的所有因数，加入优化后时间复杂度 $O(n^3)$，TLE，$77$ 分。

[代码](https://www.luogu.com.cn/paste/ka3ww3a7)。

## 做法二

用 vector 存 $num$ 为 $i$ 的格子能走到的所有格子，再 BFS，时间复杂度 $O(n^2)$，可以通过。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
struct node{
	int x,y,num;
};
queue<node>q;
vector<node>e[1005000];//num为i的格子能走到哪里 
bool vis[1005][1005];
int main(){
	int start;
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			int x;
			cin>>x;
			if(i==1 and j==1) start=x;
			e[i*j].push_back({i,j,x});
		}
	}
	q.push({1,1,start});
	vis[1][1]=true;
	while(q.size()){
		int x=q.front().x,y=q.front().y,num=q.front().num;
		q.pop();
		if(x==n and y==m) return printf("yes"),0;
		for(auto v:e[num]){
			if(!vis[v.x][v.y]){
				vis[v.x][v.y]=true;
				q.push(v);
			}
		}
	}
	printf("no");
	return 0;
}
```

---

## 作者：collegiate (赞：0)

哦，太棒了！又是一道可以写题解的题！

回到正题，看到数据不大，就考虑用**广度优先搜索**嘛，当然深度优先搜索也可以。

其实正着想虽然可以做但是不好想，所以我们**倒着想**。

我们先看**结束条件**，注意到这句话：想要到 $(x,y)$ 的格子，当且仅当 $x \times y = num$ 才行，而这里的 $num$ 是输入进去的。

我们可以从中想出，广搜的结束条件不就是当 $xx \times yy = 1$ 吗？因为要到 $(1,1)$，那么 $1 \times 1$ 就是 $1$ 了。

接着是存图，根据跳格子的规则，我们就这样子存图：


```cpp
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			cin>>val;
			G[val].push_back(mk(i,j));
		}
```

为什么呢？非常简单滴！

因为当前的格子下一次必定跳到 $i \times j$ 这个区域，所以用邻接表存的是 $i \times j$ 了。

最后注意下 $n$ 和 $m$ 别搞反了即可：


```cpp
#include<bits/stdc++.h>
#define ll long long
#define pll pair<ll,ll>
#define mk make_pair
using namespace std;
const int N=1e5+5;
vector<pll> G[N];
ll vis[N];
ll n,m,val;
queue<pll> q;
bool bfs(ll xx,ll yy){
	q.push({xx,yy});
	while(!q.empty()){
		val=q.front().first * q.front().second;
		q.pop();
		if(val==1) return 1;//到了
		if(vis[val]) continue;//如果被标记了就continue
		vis[val]=1;
		for(auto y:G[val]) q.push(y);
	}
	return 0;
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			cin>>val;
			G[val].push_back(mk(i,j));//特殊存图
		}
	if(bfs(n,m)) cout<<"yes";
	else cout<<"no";
	return 0;
}
```

---

## 作者：lzx111218 (赞：0)

# P11580 [CCC2020] Escape Room
[题目传送门](https://www.luogu.com.cn/problem/P11580)
## 思路
使用 BFS 遍历矩阵，从 $(1,1)$ 开始，检查每个格子能跳跃到的位置，直到到达 $(m,n)$ 或遍历完所有可达位置。记录访问状态避免重复访问即可。

**热知识：** constexpr 比 const 快。

并且，手写队列会更快。


```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
constexpr int N = 1000005; 
constexpr int Q = 1000005; 
int m, n;
bool f[N];
vector<int> g[N];
int q[Q]; 
int h, t; 
inline void e(int val) {
    q[t] = val;
    t = (t + 1) % Q;
}
inline int d() {
    int val = q[h];
    h = (h + 1) % Q;
    return val;
}
inline void bfs() {
    e(1);
    f[1] = true;
    while (h != t) {
        int fr = d();
        for (int i = 0; i < g[fr].size(); i++) {
            int v = g[fr][i];
            if (f[v]) continue;
            f[v] = true;
            e(v);
        }
    }
}
signed main() {
    scanf("%lld%lld", &m, &n);
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            int num;
            scanf("%lld", &num);
            g[i * j].push_back(num);
        }
    }
    bfs();
    if (f[m * n]) printf("yes");
    else printf("no");
    return 0;
}

```

---

## 作者：ZSYhaouuan (赞：0)

首先，建议评黄或橙。

其次。看到这道题，一个很明显的迷宫问题，数据也不算很大，广搜就行了。

然后在仔细看。发现这道题和每个点的具体的坐标没有关系，只看格子上的乘积，来决定位置。我们只需要维护数字的乘积就行了。

具体表现为：


```cpp
vector<ll> G[1000005];//记录乘积为i的点到乘积为G[i]的格子去
```

因为一个乘积可能去到很多地方，所以采用邻接表的方式存储。

然后在输入时渐变即可，根据定义很容易写出来，具体为：

```cpp
G[i * j].push_back(t);//t为输入的值
```

广搜都是模板，此处不再赘述。最后看看代码：


```cpp
//迷宫
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n, m; //长和宽
vector<ll> G[1000005];//记录乘积为i的点到乘积为G[i]的格子去
bool flag[1000005];
bool bfs(ll t) {//bfs模板
	queue<ll> q;
	q.push(t);
	while (q.size()) {
		ll times = q.front();
		q.pop();
		if (times == n * m) return 1;
		flag[times] = 1;
		for (auto y : G[times]) {
			if (!flag[y]) {
				q.push(y);
			}
		}
	}
	return 0;
}
int main() {
	cin >> m >> n;//注意：不要输反了！
	for (ll i = 1; i <= m; i++) {//注意：不要写反了！
		for (ll j = 1; j <= n; j++) {//注意：不要写反了！
			ll t;
			cin >> t;
			G[i * j].push_back(t);//建边
		}
	}
	if (bfs(1))cout << "yes";
	else cout << "no";
	return 0;
}
```

---

## 作者：huhangqi (赞：0)

发现直接从起点开始不好处理，可以考虑从终点倒过来处理。

假设目前在位置 $(x,y)$ 那么下一次一定是选择值为 $x\times y$ 的区域。

那么我们开按照当前区域的值存下这个区域的位置，使用广搜处理，记录每一个值是否加入过队列，防止重复。

时间复杂度为 $O(n^2)$，可以通过。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int m,n;
bool vis[1000005];
vector<pair<int,int>> e[1000005];
bool bfs(int sx,int sy){
	queue<pair<int,int>> q;
	q.push({sx,sy});
	while(!q.empty()){
		pair<int,int> u=q.front();
		q.pop();
		int tmp=u.first*u.second;
		if(tmp==1)return true;
		if(vis[tmp])continue;
		vis[tmp]=1;
		for(auto i:e[tmp])q.push(i);
	}
	return false;
}
signed main(){
	cin>>m>>n;
	for(int i=1;i<=m;i++){
		for(int j=1,x;j<=n;j++){
			cin>>x;
			e[x].push_back({i,j});
		}
	}
	if(bfs(m,n))cout<<"yes";
	else cout<<"no";
	return 0;
}
``````

---

