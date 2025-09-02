# [ABC067D] Fennec VS. Snuke

## 题目描述

$Fennec$ 和 $Snuke$ 正在玩棋盘游戏。

在这个游戏中，有 $n$ 个格子和 $n-1$ 条道路， 编号为 $a_i$ 和 $b_i$ 的格子通过第 $i$ 条边相连。这些格子和边组成了一棵树。

第 $1$ 个格子是黑色，第 $n$ 个格子是白色，其他格子没有颜色。先手 $Fennec$ 和后手 $Snuke$ 交替给格子涂色，两人依次执行以下操作：

   $Fennec$：将一个与黑色格子相邻且未被涂色的格子涂成黑色。
   
   $Snuke$：将一个与白色格子相邻且未被涂色的格子涂成白色。

如果当前行动的玩家无法涂色，他将输掉游戏。请你写一个程序，判断当 $Fennec$ 和 $Snuke$ 都采取最佳策略时，谁能获胜。

## 样例 #1

### 输入

```
7
3 6
1 2
3 1
7 4
5 7
1 4```

### 输出

```
Fennec```

## 样例 #2

### 输入

```
4
1 4
4 2
2 3```

### 输出

```
Snuke```

# 题解

## 作者：tanghg (赞：7)

这道题目是一道经典搜索题。

如果想赢，那么也就要用最短的次数去堵对方。假设这棵树是这样的。
![](https://cdn.luogu.com.cn/upload/image_hosting/5j36k464.png)

从黑棋从最左边开始，白棋从最右边，可以看出来，想要赢的最优策略是抢占中间。

那么怎么判断中间呢？

我们可以定义两个数组，起名为 dis0 和 dis1，分别代表黑棋和白棋的“距离”。也就是每一个点到 $1$ 或 $n$ 之间有几个边。

每一个点的“距离”也就是其父节点加 $1$，之后只要分别以黑棋和白棋遍历一下树即可。

之后，看图就可以不难发现，距离为 $1$ 到 $n$ 的就是中间的结点。之后，如果 $dis0_i\leq dis1_i$，这个点也就是黑棋的了，之所以等于也是黑棋的，是因为黑棋有先手优势。之后，统计会被黑棋占领和被白棋占领的总数量，看中间的就可以了。然后统计，拥有数量更多中间棋子的一方获胜。

代码如下：

```cpp
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;
ll n;
vector<ll>a[1000000];
ll dis[8][1000000];
void dfs(ll u,ll f,ll id){
    dis[id][u]=dis[id][f]+1;
    for(int i:a[u]){
        if(i==f){
            continue;//在遍历的时候可能会碰到父节点，不能算重
        }
        dfs(i,u,id);
    }
}
ll u,v;
int main(){
    cin>>n;
    for (int i = 0; i <n-1 ; ++i) {
        cin>>u>>v;
        a[u].push_back(v);
        a[v].push_back(u);
    }
    dfs(1,0,0);//黑棋
    dfs(n,0,1);//白棋
    ll ans0=0,ans1=0;
    for (int i = 1; i <=n ; ++i) {
        if(dis[0][i]<=dis[1][i]){
            ans0++;
        }else{
            ans1++;
        }
    }
    if(ans0>ans1){
        cout<<"Fennec";
    }else{
        cout<<"Snuke";
    }
    return 0;
}
```

---

## 作者：_hxh (赞：2)

### 分析

首先易知胜利条件“如果当前行动的玩家无法涂色，他将输掉游戏”等价于“什么颜色的格子数更多谁就赢下游戏”。

先看样例 1：

![](https://cdn.luogu.com.cn/upload/image_hosting/j1tezlv5.png)

换一种方式画就是：

![](https://cdn.luogu.com.cn/upload/image_hosting/acm0d2f1.png)

最优的决策一定是先沿着 $1$ 到 $7$ 这一条“主干道”涂色，涂不了了再将这条“主干道”上下的“岔路”涂色。通俗点的解释就是先涂“主干道”抢占“岔路”，因为只要控制了这个“岔路口”，这条“岔路”中的所有点都归他了。

读者：![](https://cdn.luogu.com.cn/upload/image_hosting/42805n2z.png)

额，好吧。具体来讲就是如果想赢，就要尽快堵住对方。因为这是一个树，所以 $1$ 到 $n$ 只有一条路可走，如果是黑方就要先从 $1$ 往 $n$ 涂，如果是白方就要先从 $n$ 往 $1$ 涂，相遇以后再涂其它分支就行。

但是这样模拟太麻烦了，有没有更简单的方法呢？

有的！我们可以定义两个数组，分别记录每个点到点 $1$ 和到点 $n$ 的距离。这个距离就是上一个节点的距离值加 $1$。这个操作简单遍历一下即可。

设一个节点 $x(1 \le x \le n)$ 到节点 $1$ 的距离记为 $dis\_black_x$，到节点 $n$ 的距离记为 $dis\_white_x$，那么对于这个节点 $x$，若 $dis\_black_x \le dis\_white_x$，那么这个节点就是黑色的，反之为白色。由于黑色先手，所以当 $dis\_black_x = dis\_white_x$ 时这个点是黑色的。这个判断在 $1$ 到 $n$ 这条路上时很好理解，为什么在岔路上也成立呢？因为如果某种颜色先到达这个在岔路上的点，那么它也一定先到达对应的“岔路口”，所以这个节点就是这种颜色的了。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
int n,u,v,w[N],b[N],ans_white,ans_black;
vector<int> vec[N];
void white(int u,int v)
{
	w[u] = w[v] + 1;
	for (auto i : vec[u])
		if (i != v)
			white(i,u);
}
void black(int u,int v)
{
	b[u] = b[v] + 1;
	for (auto i : vec[u])
		if (i != v)
			black(i,u);
}
int main()
{
	cin >> n;
	for (int i = 1;i < n;i++)
	{
		cin >> u >> v;
		vec[u].push_back(v);
		vec[v].push_back(u);
	}
	white(n,0);
	black(1,0);
	for (int i = 1;i <= n;i++)
	{
		if (b[i] <= w[i])
			ans_black++;
		else
			ans_white++;
	}
	if (ans_black > ans_white)
		cout << "Fennec" << endl;
	else
		cout << "Snuke" << endl;
	return 0;
}
```

---

## 作者：Juanzhang (赞：1)

**思路：**

- $bfs$

因为题目要求最优解，两人都会尽量缩小对方能走的范围，所以两个人肯定都会尽量往对方区域走

显然，距离两人初始点近的会被两人染色，于是只需处理出两人初始点距每一点的路径长度，最后统计。

但是，可以发现，我们只需统计哪个人先到那个点，于是，$bfs+$**染色**

**代码**

染色

``` cpp
#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 10;
int n, l, r, q[maxn], vis[maxn];

vector <int> e[maxn];

int main() {
	scanf("%d", &n);
	for (int i = 1, u, v; i < n; i++) {
		scanf("%d %d", &u, &v);
		e[u].push_back(v), e[v].push_back(u);
	}
	l = 1, r = 0;
	vis[1] = 1;
	vis[n] = 2;
	q[++r] = 1;
	q[++r] = n;
	for (; l <= r; ) {
		int u = q[l++];
		for (int v : e[u]) {
			if (!vis[v]) {
				vis[v] = vis[u];
				q[++r] = v;
			}
		}
	}
	int sum1 = 0, sum2 = 0;
	for (int i = 1; i <= n; i++) {
		if (vis[i] == 1) {
			sum1++;
		} else {
			sum2++;
		}
	}
	puts(sum1 > sum2 ? "Fennec" : "Snuke");
	return 0;
}
```

距离统计

``` cpp
#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 10;
const int INF = 0x7fffffff;
int n, l, r, q[maxn], dis[2][maxn];

vector <int> e[maxn];

int main() {
	scanf("%d", &n);
	for (int i = 1, u, v; i < n; i++) {
		scanf("%d %d", &u, &v);
		e[u].push_back(v), e[v].push_back(u);
	}
	for (int i = 1; i <= n; i++) {
		dis[0][i] = dis[1][i] = INF;
	}
	dis[0][1] = 0;
	l = 1, r = 0;
	q[++r] = 1;
	for (; l <= r; ) {
		int u = q[l++];
		for (int v : e[u]) {
			if (dis[0][v] > dis[0][u] + 1) {
				dis[0][v] = dis[0][u] + 1;
				q[++r] = v;
			}
		}
	}
	dis[1][n] = 0;
	l = 1, r = 0;
	q[++r] = n;
	for (; l <= r; ) {
		int u = q[l++];
		for (int v : e[u]) {
			if (dis[1][v] > dis[1][u] + 1) {
				dis[1][v] = dis[1][u] + 1;
				q[++r] = v;
			}
		}
	}
	int sum1 = 0, sum2 = 0;
	for (int i = 1; i <= n; i++) {
		if (dis[0][i] > dis[1][i]) {
			sum2++;
		} else {
			sum1++;
		}
	}
	puts(sum1 > sum2 ? "Fennec" : "Snuke");
	return 0;
}
```

---

## 作者：EAT_NH4HCO3 (赞：1)

~~抢沙发~~

### 这道题实际上还是比较简单的
### 主要要考虑清楚几个问题

 1. 我们为了保证最优策略，要尽量让两个人去堵住对方的路
 2. 当然在遍历的过程中，依然要考虑到所有邻居节点，以防遗漏出现偏差 
 


------------

代码菌如下
```
#include<iostream>
#include<queue>
#include<vector>

using namespace std;

const int MAXN=100000+10;
vector<int> edge[MAXN];//用邻接表来实现树的存储
int n,cnt[3];//cnt用来记录颜色数量
int tree[MAXN];//tree数组储存每个节点的颜色，1是指black，2指white

void bfs()
{
	queue<int> q;
	q.push(1),q.push(n);//Fennec先，Snuke后，所以先后入队
	while(!q.empty())
	{
		int temp=q.front();
		q.pop();
		cnt[tree[temp]]++;//注意位置！！（咳咳）
		for(int i=0;i<edge[temp].size();++i)//枚举所有节点
		{
			int v=edge[temp][i];
			//cnt[tree[temp]]++;  不要在意细节（^_^）
			if(tree[v])continue;
			else tree[v]=tree[temp];//判断是否涂过色
			q.push(v);
		}
	}
}

int main()
{
	ios::sync_with_stdio(false);
    memset(tree,0,sizeof(tree));
	cin>>n;
	for(int i=1;i<n;++i)
	{
		int x,y;
		cin>>x>>y;
		edge[x].push_back(y);
		edge[y].push_back(x);//邻接表建树
	}
	tree[1]=1,tree[n]=2;
	bfs();
	if(cnt[2]>=cnt[1])//因为Fennec先手，所以如果最终结果相同，很明显是Snuke赢了
		cout<<"Snuke"<<endl;
	else
		cout<<"Fennec"<<endl;
	return 0;
}
```

---

## 作者：封禁用户 (赞：1)

这是一道经典的博弈题。每个人的最优策略都应该是向对面的地方走，两个人相遇时，比出去对面的子节点，谁多谁就赢。

先求出路径，然后模拟即可。

记得关注我的博客哦：https://www.luogu.org/blog/Noi2017/

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=100005;
int n,a,b,dep,p,q;
int vis[N],path[N];
vector<int>e[N];
int dfs1(int now,int deep)
{
	vis[now]=1;
	if(now==n)
	{
		dep=deep;
		return 1;
	}
	for(int i=0;i<e[now].size();i++)
	{
		if(vis[e[now][i]])
			continue;
		path[deep]=e[now][i];
		if(dfs1(e[now][i],deep+1))
			return 1;
	}
	return 0;
}
int dfs2(int now)
{
	vis[now]=1;
	int sum=1;
	for(int i=0;i<e[now].size();i++)
		if(!vis[e[now][i]])
			sum+=dfs2(e[now][i]);
	return sum;
}
int main()

{
	scanf("%d",&n);
	for(int i=1;i<n;i++)
	{
		scanf("%d%d",&a,&b);
		e[a].push_back(b);
		e[b].push_back(a);
	}
	path[0]=1;
	dfs1(1,1);
	//1:(0)---(dep/2),(dep/2+1)---(dep-1)  2:(0)---(dep/2-1),(dep/2)---(dep-1)
 	memset(vis,0,sizeof(vis));
 	p=dfs2(1);
	if(dep%2)
	{
		memset(vis,0,sizeof(vis));
		for(int i=0;i<=dep/2;i++)
			vis[path[i]]=1;
		q=dfs2(path[dep/2+1]);
		if(p-q>q)
			printf("Fennec\n");
		else
			printf("Snuke\n");
	}
	else
	{
		memset(vis,0,sizeof(vis));
		for(int i=0;i<=dep/2-1;i++)
			vis[path[i]]=1;
		q=dfs2(path[dep/2]);
		if(p-q>q)
			printf("Fennec\n");
		else
			printf("Snuke\n");
	}
	return 0;
}

```

---

## 作者：_AyachiNene (赞：1)

# 思路：
这种和博弈有关的题，我们可以自己试着玩一下。然后就很好发现，只要先手的人把后手堵住，然后看堵住的那个点的子树和除去这个点的子树的大小，多的就能赢。因为子树越大能拿的次数就越多。

**注意：如果为一条链要根据奇偶性进行特判。**
# Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node
{
   	int to,nxt;
}e[114514*2];
int head[114514*2],cnt;
void add(int x,int y)
{
   	e[++cnt].to=y;
   	e[cnt].nxt=head[x];
   	head[x]=cnt;
}
int n;
int s[114514],f[114514],cnt1,ans[114514];  //s表示子树大小，f表示每个点的父亲节点 
void dfs(int u,int fa)
{
   	s[u]=1;
   	for(int i=head[u];i;i=e[i].nxt)
   	{
   		int v=e[i].to;
   		if(v!=fa)       //不能往会搜 
   		{
   			f[v]=u;
   			dfs(v,u);
   			s[u]+=s[v];         //回溯之后算子树大小 
   		}
   	}
}
int lca()
{
   	int x=n;
   	while(x!=1)
   	{
   		ans[++cnt1]=x;    
   		x=f[x];
   	} 
   	ans[++cnt1]=1;
   	return ans[cnt1/2];
}
int main()
{
    cin>>n;
   	for(int i=1;i<n;i++)	//建树 
   	{
   		int a,b;
   		cin>>a>>b;
   		add(a,b);
   		add(b,a);
   	}
   	dfs(1,0);     //预处理每个点的子树大小和每个点的父亲 
   	int k=lca();  //算会在哪一个点被堵住 
   	if(s[1]-s[k]>s[k])           //子树大的就赢 
   		cout<<"Fennec";
  	else if(s[1]==n&&s[n]==1&&cnt1%2)       //特判，为链的长度为奇数就是 Fennec赢，否则 Snuke赢 
  		cout<<"Fennec";
   	else
   		cout<<"Snuke";
   	return 0; 
}
```


---

## 作者：hh弟中弟 (赞：0)

相当于两个人在扩展自己的颜色，由于树上路径唯一，所以两个人不可能到达对方某个节点之后的颜色，相当于那个节点封锁了道路。已经封锁的地方可以最后再填，所以每个人都想让自己封锁的地方更大，所以他们需要尽可能的填 $1$ 到 $n$ 路径上的颜色，设后手在这条道路填的最后一个位置为 $x$，如果 $size_x\ge n-size_x$，后手必胜，否则先手必胜。\
[record](https://atcoder.jp/contests/abc067/submissions/61663429)

---

## 作者：long_long__int (赞：0)

# 题目解法

由于题目里给的是一棵树，所以可以把点 $1$ 当做根，由树的性质可知，从点 $1$ 到点 $n$ 的不经过重复结点的路径有且仅有一条。所以点 $1$ 要先尽可能的去堵点 $n$ 的路，点 $n$ 也一样。所以样例一的形式会如下图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/q4g9rezb.png)

解释：由于点 $7$ 不通过点 $1$ 无法到达点 $2,3,6$，所以点 $1$ 不需要提前去染点 $2,3,6$，要去把中间的点尽可能多地染，而点 $1$ 不通过点 $7$ 无法到达点 $5$，所以点 $7$ 也是一样。

接下来：

![](https://cdn.luogu.com.cn/upload/image_hosting/05735i9b.png)

解释：由于黑方先走，所以点 $4$ 被点 $1$ 占领了。

最后：

![](https://cdn.luogu.com.cn/upload/image_hosting/jggvoakr.png)

很明显，黑方胜利。

所以，如果一个点到点 $1$ 的距离小于等于到点 $n$ 的距离，那么这个点会被点 $1$ 染黑，否则被点 $n$ 染白。

所以解法就是 BFS 一遍，计算每个店距离点 $1$ 和点 $n$ 的距离，然后统计一下答案即可。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int to1[100800],to2[100500];
int n;
vector<int>e[100500];
struct node{
	int u,step;
};
queue<node>q;
int main(){
	memset(to1,0x3f,sizeof to1);
	memset(to2,0x3f,sizeof to2);
	cin>>n;
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	while(!q.empty()) q.pop();
	q.push({1,0});to1[1]=0;
	while(!q.empty()){
		int u=q.front().u,step=q.front().step;
		q.pop();
		for(auto v:e[u]){
			if(to1[v]==0x3f3f3f3f){
				to1[v]=step+1;
				q.push({v,step+1});
			}
		}
	}
	while(!q.empty()) q.pop();
	q.push({n,0});to2[n]=0;
	while(!q.empty()){
		int u=q.front().u,step=q.front().step;
		q.pop();
		for(auto v:e[u]){
			if(to2[v]==0x3f3f3f3f){
				to2[v]=step+1;
				q.push({v,step+1});
			}
		}
	}
	int ans1=0,ans2=0;
	for(int i=1;i<=n;i++){
		if(to2[i]<to1[i]) ans2++;
		else ans1++;
	}
	printf("%s",(ans2>=ans1)?"Snuke":"Fennec");
	return 0;
}
```

---

## 作者：aike_6yoshi9 (赞：0)

思路很明确，要占的多，就需要占据主干道，因为把主干道上的点占领了，那个点的分支就不会收到威胁了，相当于提前占领了，所以先把主干道尽量多占领，然后再慢慢把主干道上的分支占领了。  
而主干道就是 Fennec 和 Snuke 之间的路径（也就是第 $1$ 个黑色格子和第 $n$ 个白色格子间的路径），由于原图是一棵树，所以路径是唯一的，把主干道上的点当作根然后它的子节点个数就是占领的个数。  
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 1 << 18;

int n;
vector<int> e[MAXN];
int cnt[MAXN];
vector<int> vct;
int frst;

void dfs(int v, int pr) {
    cnt[v] = 1;
    vct.push_back(v);

    if (v == n - 1) {
        frst = vct[((int)vct.size() + 1) / 2];
    }
    for (int to : e[v]) {
        if (to == pr) continue;
        dfs(to, v);
        cnt[v] += cnt[to];
    }
    vct.pop_back();
}

int main() {
#ifdef HOME
    assert(freopen("in", "r", stdin));
#endif


    while (scanf("%d", &n) == 1) {
        for (int i = 0; i < n; i++) {
            e[i].clear();
        }
        for (int i = 0; i < n - 1; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            --u; --v;
            e[u].push_back(v);
            e[v].push_back(u);
        }
        frst = -1;
        dfs(0, 0);
        bool win = cnt[frst] * 2 < n;
        string ans = win ? "Fennec" : "Snuke";
        cout << ans << endl;
    }


#ifdef HOME
    cerr << "time: " << clock() * 1.0 / CLOCKS_PER_SEC << endl;
#endif
    return 0;
}
```
代码取自 izban。

---

## 作者：TLEWA (赞：0)

## 思路

一道博弈论题，并不难。

我们把这个 $n$ 个格子和 $n-1$ 个道路抽象成树，然后我们发现先将对方无法到达的点染色没有意义（不会增加自己所能染色的范围），我们应该贪心地将对方所能走的点缩小，向对面的地方走（至少能对染色范围产生 1 点贡献），由于是一棵树，所以向对面走其实就是走 $1$ 号点和 $n$ 号点那条确定的路径，先走到的就得到这个点。我们通过 BFS 来染色，最后判断谁的控制区域更多即可（如果控制区域相同，那么根据树的奇偶性来判断先手还是后手先不能下）。

## AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

int n;

vector<int> vec[100005];

queue<pair<int,int> > que;

int ans[2],m[100005];

int main() {
	cin >> n;
	
	int u,v;
	for(int i=1;i!=n;++i) {
		cin >> u >> v;
		vec[u].push_back(v);
		vec[v].push_back(u);
	}
	
	que.push(make_pair(0,1));
	que.push(make_pair(1,n));
	
	//BFS 染色 
	while(!que.empty()) {
		auto u=que.front().second,op=que.front().first;
		que.pop();
		if(m[u]) continue;
		
		m[u]=1;
		ans[op]++;
		
		for(auto v:vec[u]) {
			que.push(make_pair(op,v));
		}
	}
	
	if(ans[0]>ans[1]) cout << "Fennec";
	else if(ans[0]<ans[1]) cout << "Snuke";
	else if(n%2) cout << "Fennec";
	else cout << "Snuke";
	return 0;
}

```


---

## 作者：watcher_YBH (赞：0)

# 思路：
要使 Fennec 胜利，那么 Fennec 所可走的点的数量一定大于或等于 Snuke 可走的点的数量，那么 Snuke 所可走的点的数量一定大于 Fennec 可走的点的数量。

我们可以用 dfs 求出每个点到 $1,n$ 的距离，比较每个点离谁的距离近，那么这个点就是谁的。
# 代码：
```
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int homo = 114514;
int n,z;
int ans,ans1;
int vis[114][homo];
vector<int> tu[homo];
void dfs_1(int son,int fa){//求出离1的距离
	vis[0][son] = vis[0][fa]+1;
	for(int i = 0; i<tu[son].size(); i++)
		if(tu[son][i] != fa) dfs_1(tu[son][i],son);
}
void dfs_n(int son,int fa){//求出离n的距离
	vis[1][son] = vis[1][fa]+1;
	for(int i = 0; i<tu[son].size(); i++)
		if(tu[son][i] != fa) dfs_n(tu[son][i],son);
}
int main(){
	cin>>n;
	for(int i = 1; i<n; i++){
		int x,y;
		cin>>x>>y;
		tu[x].push_back(y);
		tu[y].push_back(x);
	}
	tu[1].push_back(0);
	tu[n].push_back(0);
	dfs_1(1,0);   dfs_n(n,0);
	for(int i = 2; i<n; i++){//比较长短，离谁近这个点就是谁的
		if(vis[1][i] < vis[0][i]) ans++;
		else ans1++;
	}
	if(ans1 <= ans) cout<<"Snuke";
	else cout<<"Fennec";
	return 0;
}
```



---

## 作者：zhengzonghaoak (赞：0)

思路：两个人肯定要往中心位置走。中心位置一定在点 n 与点 1 所确定的链上。我们考虑先建树，同时记录下父亲。之后跑出双方最后走到的位置，计算出双方可以涂的点数即可。改了一周了，现在放上代码。注释里讲的比较详细了。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int N=1e5+100; 
long long Next[N*2],Head[N*2],edge[N*2],tot;//邻接表来存树 
void add(long long x,long long y){//邻接表模板 
	edge[++tot]=y;
	Next[tot]=Head[x],Head[x]=tot;
} 
long long n,x,y;//n是点数，x,y,是每次输入的两个相邻点 
long long f[N];//f数组记录每个点的父亲 
long long a,b,c;//a记录1与n所确定的链上1的儿子，b记录链上除去1与n点的个数，c记录snuke最终在链上走到了哪 
long long cnt;//记录某个点下方有多少个点 
void build(long long now,long long fa){//建树 
	for(int i=Head[now];i;i=Next[i]){
		if(edge[i]==fa) continue;//特判是否往回走 
		f[edge[i]]=now;//存父亲 
		build(edge[i],now);//递归 
	}
}
void findamount(long long now,long long fa){//算出一个点下方有多少点（不算这个点） 
	for(int i=Head[now];i;i=Next[i]){
		if(edge[i]==fa) continue;
		cnt++;//计数器加一 
		findamount(edge[i],now);
	}
}
long long findbeforefather(long long x){//找到1与n所确定的链上1的儿子
	while(f[x]!=1){
		x=f[x];
	} 
	return x;
} 
long long pre_huafen(){//算出链上除去1与n点的个数 
	long long ans=0;
	long long x=n;//从最下方开始 
	while(x!=1){//避免x==1的情况发生（虽然没有） 
		if(f[x]!=1){//到1结束 
			x=f[x];
			ans++;
		}
		else break;
	}
	return ans;
}
long long huafen(long long amount){//从n开始向上走amount步，记录位置 
	long long x=n;
	for(int i=1;i<=amount;i++){
		x=f[x];
	}
	return x;
}
int main(){
	cin>>n;
	for(int i=1;i<n;i++){
		cin>>x>>y;
		add(x,y);//存双向边 
		add(y,x);
	}
	build(1,-1);//建树 
	a=findbeforefather(n);//找出点a 
	b=pre_huafen();//找出个数 
	c=huafen(b/2);//因为snuke是后手，所以肯定是跳b/2步 
	findamount(c,f[c]);//计算出snuke可以涂的点数 
	if(cnt<n-cnt-2) cout<<"Fennec\n";//多减了2是因为1与n已经有颜色 
	else cout<<"Snuke\n";
	return 0;//完结撒花！！！ 
}
```

码字不易，望管理员通过！！！

---

## 作者：灵光一闪 (赞：0)

这个题窝给了两种做法（一个本人一个dalao的）

这道题显而易见就是要占领尽可能多的地盘，因为这个是树，没有环，所以思路就是先行理出一条1->n的路，然后分割地盘，比谁的地盘大

代码:
```
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<cstdio>

#include<vector>
using namespace std;
bool flag=false;
vector<int> v[233333];
vector<int> way;
bool vis[233333];
bool visited[233333];
int n;
int m;
int l,r;
bool dfs_find_way(int a){
	vis[a]=true;
	way.push_back(a);
	if(a==n){
		return true;
	}
	for(int i=0;i<v[a].size();i++){
		if(!vis[v[a][i]]){
			if(dfs_find_way(v[a][i])){
				return true;//true说明走到了
			}
		}
	}
	way.pop_back();
	return false;//false说明没走到
}
int dfs_get_ans(int a,int num=0){//结点累计
	visited[a]=true;
	for(int i=0;i<v[a].size();i++){
		if(!visited[v[a][i]]){
			num=dfs_get_ans(v[a][i],num+1);
		}
	}
	return num;
}
int main(){
	cin>>n;
	m=n-1;
	for(int i=0;i<m;i++){
		int x,y;
		cin>>x>>y;
		v[x].push_back(y);
		v[y].push_back(x);
	}
	dfs_find_way(1);
///*
	for(int i=0;i<way.size();i++){
		visited[way[i]]=true;
//	cout<<way[i]<<" ";
	}
//*/
//puts("1");
	for(int i=0;i<(way.size()+1)/2;i++){
		l+=dfs_get_ans(way[i],0);
	}
	for(int i=(way.size()+1)/2;i<way.size();i++){
		r+=dfs_get_ans(way[i],0);
	}
	if(l>r){
		puts("Fennec");
		return 0;
	}
	else if(l<r){
		puts("Snuke");
		return 0;
	}
	else{
		if(way.size()%2==0){
			puts("Snuke");
			return 0;
		}
		else{
			puts("Fennec");
			return 0;
		}
	}
	return 0;
}
```

然鹅还有一种基本上所有人都没认识到的一个问题：其实只要判断这个点离谁近谁就拿得到（相等就是F拿到了）
```
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<cstdio>

#include<vector>
using namespace std;
int n;
vector<int> g[233333];
int dist[2][233333],id;
void dfs(int idx,int par=-1){//树上dfs
	if(par!=-1){
		dist[id][idx]=dist[id][par]+1;
	}
	for(int i=0;i<g[idx].size();i++){
		if(g[idx][i]!=par){
			dfs(g[idx][i],idx);
		}
	}
	return;
}
int main(){
	cin>>n;
	for(int i=0;i<n-1;i++){
		int x,y;
		cin>>x>>y;
		x--;
		y--;
		g[x].push_back(y);
		g[y].push_back(x);
	}
	id=0;
	dfs(0);//F距离每个点的距离
	id=1;
	dfs(n-1);//S距离每个点的距离
	int res=0;
	for(int i=0;i<n;i++){
		if(dist[0][i]<=dist[1][i]){//显而易见，比离谁进
			res++;
		}
	}
	if(res>=n/2+1){//F赢了
		puts("Fennec");
	}
	else{//不然就是S赢了
		puts("Snuke");
	}
	return 0;
}
```

The End.

---

