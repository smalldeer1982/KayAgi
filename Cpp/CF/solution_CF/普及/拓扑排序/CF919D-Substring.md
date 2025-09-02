# Substring

## 题目描述

You are given a graph with $ n $ nodes and $ m $ directed edges. One lowercase letter is assigned to each node. We define a path's value as the number of the most frequently occurring letter. For example, if letters on a path are "abaca", then the value of that path is $ 3 $ . Your task is find a path whose value is the largest.

## 说明/提示

In the first sample, the path with largest value is $ 1→3→4→5 $ . The value is $ 3 $ because the letter 'a' appears $ 3 $ times.

## 样例 #1

### 输入

```
5 4
abaca
1 2
1 3
3 4
4 5
```

### 输出

```
3
```

## 样例 #2

### 输入

```
6 6
xzyabc
1 2
3 1
2 3
5 4
4 3
6 4
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
10 14
xzyzyzyzqx
1 2
2 4
3 5
4 5
2 6
6 8
6 5
2 10
3 9
10 9
4 6
1 10
2 8
3 7
```

### 输出

```
4
```

# 题解

## 作者：Merron (赞：10)

## CF919D——拓扑排序

[题目传送门](https://www.luogu.com.cn/problem/CF919D)

### 前置知识

1. 拓扑排序
2. 简单DP

### 正文

通过标签我们可以知道这是拓扑排序。

P.S.:这上面一句显然是废话

但是乍看题目，感觉没想到是拓扑排序。

但是，请看这句

> Output a single line with a single integer denoting the largest value. If the value can be arbitrarily large, output -1 instead.

来，谷歌生草一下。

> Translate:输出单行和一个整数，该整数表示最大值。如果该值可以任意大，则输出-1。

~~好像没生草诶~~

有没有注意到“任意大”？这意味着什么？

**环！**

-------

看这种在**有向图**图上找权值（“权值”详见题目中定义）的题，总会想起**DP**。

Q: Why? What's the reason?

A: 因为DAG（有环可以Topo排除，具体措施详见后文）有向，所以满足DP。

设
$$
dp[i][j] \text{表示走到第i步时，字母j的最大出现次数}
$$
Q: 嗯？j不是字母吗？

A: 我们可以预处理。

For example:

对于小写字母a，将其映射为1。

So,

```
a -> 1

b -> 2

...

n -> n - a + 1
```

继续推转移方程。

我们设目前走到了x，而x通向y，我们枚举j。

此处要分为两种情况。

1. 当y的字母等于j时

   `dp[y][j] = max(dp[y][j], dp[x][j] + 1) `

2. 不等于时

   `dp[y][j] = max(dp[y][j], dp[x][j]) //因为不等于，所以不加一`

此过程进行于拓扑排序时，下面是代码片段：

```cpp
	while(!Q.empty())
	{
		int x = Q.front();
		Q.pop();
		in[x] = -1; //delete this edge 
		sum ++;// count
		for(int i = 0; i < E[x].size(); i ++)
		{
			int y = E[x][i];
			for(int j = 1; j <= 26; j ++)
			{
				if(val[y] == j)
					dp[y][j] = max(dp[y][j], dp[x][j] + 1);
				else
					dp[y][j] = max(dp[y][j], dp[x][j]);
			}
			in[y] --;
			if(!in[y])
				Q.push(y);
		}
	}
/*
解释一下：
in：入度
sum：统计入队数量
val[x]：x代表的字母
*/
```

让我们回到先前的问题：

> Q: Why? What's the reason?
>
> A: 因为DAG（ __有环可以Topo排除，具体措施详见后文__）有向，所以满足DP。

我们统计入队的数量，如果sum小于n，则有环，即权值任意大。

举个例子：

![](https://cdn.luogu.com.cn/upload/image_hosting/8ipsg4ik.png)

图画得不好，请见谅。

当点1进入队列后，删掉点1，此时sum=1

但当1删掉后，没有入度为0的点了，退出。

此时sum < n (n = 4)。

好了，没什么说的了，下面是代码。

---

Code:

```cpp
#include <bits/stdc++.h>
using namespace std;

const int maxn = 3e5 + 10;

int n, m;
int val[maxn];
int in[maxn];
int dp[maxn][30];
int sum;
int ans;
vector<int> E[maxn];//save the edges
queue<int> Q;

int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i ++)
	{
		char c;
		cin >> c;
		val[i] = c - 'a' + 1;
		dp[i][val[i]] ++;//init
	}

	for(int i = 1; i <= m; i ++)
	{
		int x, y;
		scanf("%d%d", &x, &y);//notice "x to y"
		E[x].push_back(y);
		in[y] ++;
	}

	for(int i = 1; i <= n; i ++)
		if(!in[i])Q.push(i);
	//Topo sort
	while(!Q.empty())
	{
		int x = Q.front();
		Q.pop();
		in[x] = -1; //delete this edge 
		sum ++;// count
		for(int i = 0; i < E[x].size(); i ++)
		{
			int y = E[x][i];
			for(int j = 1; j <= 26; j ++)
			{
				if(val[y] == j)
					dp[y][j] = max(dp[y][j], dp[x][j] + 1);
				else
					dp[y][j] = max(dp[y][j], dp[x][j]);
			}//solve
			in[y] --;
			if(!in[y])
				Q.push(y);
		}
	}

	if(sum < n)
		return printf("-1"), 0;

	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= 26; j ++)
			ans = max(dp[i][j], ans);//find the biggest
	printf("%d\n", ans);
	return 0;
}
```



### 写在最后

本题解、代码写于`Linux Ubuntu`下，就出现了一个玄学问题

```cpp
	for(int i = 1; i <= n; i ++)
	{
		char c;
		cin >> c;//如将这里改为c = getchar(), 本地运行RE
		val[i] = c - 'a' + 1;
		dp[i][val[i]] ++;//init
	}
```

求大佬指教！

The end.

---

## 作者：Binary_Lee (赞：7)

## [题面传送门](https://www.luogu.com.cn/problem/CF919D)

### 解决思路：

DP 与拓扑结合。$f_{i,j}$ 表示到 $i$ 位置 $j$ 的最大次数。

将 $a \sim z$ 转成数字 $0\sim 25$ ，方便存储。

考虑转移。这一部分其他题解讲的很详细了，也很好理解。对于二十六个字母（$j$）：

- 若是当前节点，则 $f_{tmp,j}=\max(f_{tmp,j},f_{k,j}+1)$

- 否则 $f_{tmp,j}=\max(f_{tmp,j},f_{k,j})$

其中 $tmp$ 为当前搜到的节点，$k$ 为其父节点。

然后考虑如何判环。例如以下情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/nnur6eks.png)

红框中显然是环。

模拟其处理过程。第一次删掉了入度为 $0$ 的 $1$ 号节点：

![](https://cdn.luogu.com.cn/upload/image_hosting/o6v6dfum.png)

然后会发现，这时没有入度为 $0$ 的节点可以找了，队列为空，结束 BFS。

而对于没有环的情况，所有点都是会被遍历到的。

所以，用 $cnt$ 记录遍历过点的数量，若最后 $cnt<n$，则说明有环。

细节讲好了，程序中就不再注释了。

### Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,b[300005],in[300005],f[300005][26];
int ans,cnt,x,y;
string s;
vector<int> a[300005];
queue<int> q;
int main(){
	scanf("%d%d",&n,&m);
	cin>>s;
	for(int i=1;i<=n;i++) b[i]=s[i-1]-'a',f[i][b[i]]++;
	for(int i=1;i<=m;i++){
		scanf("%d%d",&x,&y);
		in[y]++;
		a[x].push_back(y);
	}
	for(int i=1;i<=n;i++) if(!in[i]) q.push(i);
	while(q.size()){
		int k=q.front();
		q.pop();
		cnt++;
		for(int i=0;i<a[k].size();i++){
			int tmp=a[k][i];
			for(int j=0;j<26;j++){
				if(b[tmp]==j) f[tmp][j]=max(f[tmp][j],f[k][j]+1);
				else f[tmp][j]=max(f[tmp][j],f[k][j]);
			}
			in[tmp]--;
			if(!in[tmp]) q.push(tmp);
		}
	}
	if(cnt<n) printf("-1");
	else{
		for(int i=1;i<=n;i++){
			for(int j=0;j<26;j++) ans=max(ans,f[i][j]);
		}
		printf("%d",ans);
	}
	return 0;
}
```

---

## 作者：Mistybranch (赞：3)

[传送门](https://www.luogu.com.cn/problem/CF919D)

题目大概意思是：给出一个 $n$ 个点 $m$ 条边的有向图，每个点有一个小写字母权值，而一条路径的权值是这条路径出现字母的最多次数，问所有路径中最大的权值。如果结果为无限大，则输出 $-1$。

这道题的主要思路就是**判断环**接着**进行 DP**。下面就将两个步骤分开讲：

- 判断环

	- 其实这道题判断环的方法很多，比如**拓扑排序**，因为拓扑排序后顺便可以把 DP 顺序处理出来，具体实现其他题解说的已经很清楚了。
    - 我们也可以把图**遍历**一遍，在访问 $u$ 的子节点 $v$ 的过程中，保持 $vis_u$ 为 $-1$，如果从 $v$ 开始遍历能遍历到 $u$ 即 $vis_u$ 为 $-1$ 时，说明有环。如果遍历完了 $u$ 的所有子节点都没有遍历到 $u$，说明 $u$ 及 $v$ 都没有环，可以设为 $1$，下次遍历到就不用遍历了。

```cpp
void CheckRing(int u) {
	int v;
	
    vis[u] = -1;
    
    for (int i = 0; i < e[u].size(); i++) {
    	v = e[u][i];
    	
    	if (!vis[v]) {
    		CheckRing(v);
		}
		
		else if (vis[v] == -1) {
			printf("-1\n");
			exit(0); 
		}
	}
	
    vis[u] = 1;
}
```

- DP

	- 我们设 ```f[i][26]``` 为以 $i$ 为起点的路径，每种字母出现最多的次数，接着我们就可以从 $u$ 开始，先 DP 完 $u$ 的所有子节点 $v$，接着我们就可以考虑列状态转移方程。
    - 我们设当前要求 ```f[u][i]```，那么：
    	- 在不断更新的过程中，```f[v][i]``` 记录的是从 $v$ 出发的路径中第 $i$ 个字母出现的最多次数，也就相当于保留了第 $i$ 个字母出现最多的路径。
        - 将每个子节点 $v$ 比较，选择含第 $i$ 个字母最多的路径，那么最后保存的一定是含第 $i$ 个字母最多的路径。
        - 最后如果第 $i$ 个字母为节点权值的话别忘了加一。
    - 所以状态转移方程为：
    
$$f[u][i] =
\begin{cases}
max(f[v][i]) & i+\texttt{a} \neq lett_u\\
max(f[v][i]) + 1 & i+\texttt{a} = lett_u
\end{cases}$$

```cpp
void Search (int u) {
	int v;
	
    vis[u] = true;
    
    for (int i = 0; i < e[u].size(); i++) {
        v = e[u][i];
        
        if (!vis[v]) {
        	Search(v);
		}
    }
    
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < e[u].size(); j++) {
        	f[u][i] = max(f[u][i], f[e[u][j]][i]);
		}
    }
    
    f[u][lett[u] - 'a']++;
}
```
完整代码：

```cpp


#include <bits/stdc++.h>

using namespace std;

int n, m, ans;
bool st[300009];
int f[300009][29];
char lett[300009];
vector<int> e[300009];
int vis[300009];

void Search (int u) {
	int v;
	
    vis[u] = true;
    
    for (int i = 0; i < e[u].size(); i++) {
        v = e[u][i];
        
        if (!vis[v]) {
        	Search(v);
		}
    }
    
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < e[u].size(); j++) {
        	f[u][i] = max(f[u][i], f[e[u][j]][i]);
		}
    }
    
    f[u][lett[u] - 'a']++;
}

void CheckRing(int u) {
	int v;
	
    vis[u] = -1;
    
    for (int i = 0; i < e[u].size(); i++) {
    	v = e[u][i];
    	
    	if (!vis[v]) {
    		CheckRing(v);
		}
		
		else if (vis[v] == -1) {
			printf("-1\n");
			exit(0); 
		}
	}
	
    vis[u] = 1;
}

int main () {
	int u, v;
	
    scanf("%d %d", &n, &m);
    
    for (int i = 1; i <= n; i++) {
    	while (true) {
    		scanf("%c", &lett[i]);
    		
    		if ('a' <= lett[i] && 'z' >= lett[i]) {
    			break;
			}
		}
	}
	
    memset(st, true, sizeof(st));
    
    for (int i = 1; i <= m; ++i) {
        scanf("%d %d", &u, &v);
        e[u].push_back(v);
        st[v] = false;
    }

    memset(vis, 0, sizeof(vis));
    
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
        	CheckRing(i);
		}
    }

    memset(vis, 0, sizeof(vis));
    
    for (int i = 1; i <= n; i++) {
        if (st[i]) {
        	Search(i);
		}
    }
    
    for (int i = 1; i <= n; i++) {
    	if (st[i]) {
    		for (int j = 0; j < 26; j++) {
    			ans = max(ans, f[i][j]);
			}
		}
	}
	
    printf("%d\n", ans);
}
```


---

## 作者：Isshiki·Iroha (赞：2)

## 题解

[传送门](https://www.luogu.com.cn/problem/CF919D)

[点我获得更好的阅读体验](https://www.luogu.com.cn/blog/yousa22/solution-cf919d)

闲话：这题其实~~比较水~~，但是因为我的智障操作硬生生的 WA 了 $7$ 发。

本题解主要讲 Dp，不懂拓扑自行学习。

### 回归正题

这题暴力搜索会 TLE，~~不要问我怎么知道的。~~

看到这种求最大值的题目，有没有想到什么？

**DP**

我们先来确定一下 Dp 的状态，用 $dp[i][j]$ 表示从任意一个点走到 $i$ 时字母 $j$ 的数量的**最大值**。

方程：我们不难发现：点 $i$ 只能是被他的父亲更新，所以方程为:

$dp[v][i]=\begin{cases}\max(dp[u][i]+1,dp[v][i])&i = word[v]\\\max(dp[u][i],dp[v][i])&i\neq word[v]\end{cases}<u,v> \in G_E,i \in [1,26]$

$word[v]$ 表示 $v$ 代表的字母，如果相同，自然要加一。

但是如果你不按照从父亲到儿子的方向去 Dp，就会造成先更新儿子再更新父亲的错误顺序，所以这时候拓扑排序就排上用场了。

```cpp
	#define ll long long
	#define reg register
	#define ri reg int
	inline void Topo() {
	queue<int>q;
	for(ri i(1); i<=n; ++i) {
		if(In[i]==0)q.push(i);
		//找入度为 0 的点入队 
	}
	while(!q.empty()) {
		ri u=q.front();
		q.pop();
		++cnt;
		//计数，如果入队次数小于 n 说明有环 
		for(ri i(head[u]); i; i=kano[i].nxt) {
			ri v=kano[i].v;
			--In[v];
			//删边，这里用减少度数来表示 
			for(ri j(1); j<=26; ++j) {
				if(j==s[v]) {//如果此时字母一样，在原来的基础上加 1 
					dp[v][j]=max(dp[v][j],dp[u][j]+1);
				} else {//否则不改动 
					dp[v][j]=max(dp[v][j],dp[u][j]);
				}
			}
			//如果入队为 0，说明他的爸爸已经被拓展完了，可以拓展了 
			if(In[v]==0)q.push(v);
		}
	}
}
```

再讲一下为什么可以这样判环，因为在环上的所有的点入度肯定会大于 $0$，他们都不会被更新，所以此时入队次数一定小于 $n$。

最后，上一下代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define reg register
#define ri reg int
using namespace std;
const int maxn=3e5+10;
int n,m;
int dp[maxn][27],In[maxn],cnt;
int head[maxn],tot,ans=0;
int s[maxn];
char t;
struct node {
	int v,nxt;
} kano[maxn<<2];
//我写的时候脑抽把 [maxn<<2] 写成 [maxn>>2] 结果一直 WA 
inline void add_kano(ri u,ri v) {
	++tot;
	kano[tot].nxt=head[u];
	kano[tot].v=v;
	head[u]=tot;
}
//存图 
inline void Topo() {
	queue<int>q;
	for(ri i(1); i<=n; ++i) {
		if(In[i]==0)q.push(i);
		//找入度为 0 的点入队 
	}
	while(!q.empty()) {
		ri u=q.front();
		q.pop();
		++cnt;
		//计数，如果入队次数小于 n 说明有环 
		for(ri i(head[u]); i; i=kano[i].nxt) {
			ri v=kano[i].v;
			--In[v];
			//删边，这里用减少度数来表示 
			for(ri j(1); j<=26; ++j) {
				//Tips 我 dp 的时候里面的循环是 i,竟然不报错，还过了样例
				//一定要细心，不要像我这样 
				if(j==s[v]) {//如果此时字母一样，在原来的基础上加 1 
					dp[v][j]=max(dp[v][j],dp[u][j]+1);
				} else {//否则不改动 
					dp[v][j]=max(dp[v][j],dp[u][j]);
				}
			}
			//如果入队为 0，说明他的爸爸已经被拓展完了，可以拓展了 
			if(In[v]==0)q.push(v);
		}
	}
}
int main() {
	ios::sync_with_stdio(false);
	cin>>n>>m;
	for(ri i(1); i<=n; ++i) {
		cin>>t;
		s[i]=t-'a'+1;
		++dp[i][s[i]];
		//初始 dp 值 
	}
	for(ri i(1),u,v; i<=m; ++i) {
		cin>>u>>v;
		if(u==v)cout<<-1,exit(0);
		//判断自环 
		add_kano(u,v);
		++In[v];
	}
	Topo();
	if(cnt<n)cout<<-1,exit(0);
	//判断负环 
	for(ri i(1); i<=n; ++i) {
		for(ri j(1); j<=26; ++j) {
			ans=max(ans,dp[i][j]);
			//暴力找 max 
		}
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：__Deng_Rui_Song__ (赞：1)

# preface
~~为啥教练把它放在分治题单里啊~~
# problem
[题目传送门](/problem/CF919D)
# solution
观察题目中的一句话：

```If the value can be arbitrarily large, output -1 instead.```

什么鬼？地铺喜磕翻译一下：

```如果该值可以无限大，则输出-1。```

Q1：什么情况才会无限大呢？

A1：环啊！

Q2：什么能找环呢？

A2：**拓扑排序**啊！

Q3：没有环怎么办？

A3：dp 啊！

设 $dp_{i,j}$ 表示以 $i$ 为结尾且出现次数最多的为 $j$ 的权值最大值，算一下内存 $3\times10^5\times26\approx6\times10^6$，开得下！

你：答案就是 $\max_{i=1}^n\max_{j=1}^{26}dp_{i,j}$！

没错，状态转移方程很好想，分为两种情况：

你：一种是 $j=a_i$，另一种是 $j\ne a_i$！

~~别插嘴！~~

- $j=a_i$，$dp_{i,j}=\max_{u\to i}dp_{u,j}+1$，这里 $\to$ 指有连边，下面同理。

- $j\ne a_i$，$dp_{i,j}=\max_{u\to i}dp_{u,j}$。

你：初始化为 $dp_i=1[in_i=0]$，其他全是 $dp_i=0$！

是的呢！ 
# code

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, ans, a[300005], in[300005], dp[300005][35];
vector<int> g[300005];
void topsort() {
  queue<int> q;
  for (int i = 1; i <= n; i++)
    if (!in[i]) q.push(i);
  while (!q.empty()) {
    int x = q.front();
    q.pop();
    dp[x][a[x]]++;
    for (int i = 0; i < g[x].size(); i++) {
      int nxt = g[x][i];
      for (int i = 0; i < 26; i++) dp[nxt][i] = max(dp[nxt][i], dp[x][i]);
      if (!--in[nxt]) q.push(nxt);
    }
  }
  for (int i = 1; i <= n; i++)
    if (in[i]) {
      cout << -1;
      return;
    }
  for (int i = 1; i <= n; i++)
    for (int j = 0; j < 26; j++) ans = max(ans, dp[i][j]);
  cout << ans;
}
int main() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    char c;
    cin >> c;
    a[i] = c - 'a';
  }
  for (int i = 1, x, y; i <= m; i++) {
    cin >> x >> y;
    g[x].push_back(y);
    in[y]++;
  }
  topsort();
  return 0;
}
```

---

## 作者：IGpig (赞：1)

## CF919D

### Problem

给你一个有向图，每个点有一个小写字母权值，定义一条路径的权值是这条路径出现次数最多的字母的个数，求出这个图权值最大权值的路径的权值。

### Solution

这个题很容易想到深搜，但是发现 $n\le 300000$，考虑动态规划，但是因为 $n\le 300000$，所以把我们的第二维空间卡的很死，而这道题又跟字符有关，那么很容易想到 $dp_{i,j}( 0\le j \le 25)$ 表示在第 $i$ 个位置字符为 $j$ 的答案。

考虑转移，很好想。如果当前的字符与 $j$ 相同，那么自然可以加一，否则不变，那么对于一条边：
$$
dp_{v,j}=max(dp_{v,j},dp_{u,j}+(s[v]==j))
$$
答案即为最大的一个，按照拓扑排序的顺序更新即可。

### Code

短且易读的代码。

~~~cpp
#include<bits/stdc++.h>
using namespace std;
using LL=long long;
const LL N=3e5+5;
LL n,m,f[N][30],in[N],ans,cnt,x,y;
vector<LL> g[N];
string s;
queue<LL> q;
int main(){
    cin>>n>>m;
    cin>>s;
    while(m--){
        cin>>x>>y;
        g[x].emplace_back(y);
        in[y]++;
    }
    s=' '+s;
    for(int i=1;i<=n;i++){
        if(!in[i]){
            q.push(i);
            f[i][s[i]-'a']=1;
        }
    }
    while(!q.empty()){
        LL to=q.front();q.pop();
        for(auto i : g[to]){
            for(int j=0;j<26;j++) f[i][j] = max(f[i][j],f[to][j] + LL(bool(s[i]-'a'==j))),ans=max(ans,f[i][j]);
            if(!(--in[i])){
                q.push(i);
            }
        }
        cnt++;
    }
    cout<<(cnt<n ? -1 : ans);
    return 0; 
}
~~~

---

## 作者：hexu2010 (赞：1)

# CF919D Substring 题解

传送门：[$\otimes$](https://www.luogu.com.cn/problem/CF919D)[$\oplus$](https://codeforces.com/problemset/problem/919/D)

## 题目大意

给定一个 $n$ 点 $m$ 边的有向图，每个顶点代表一个小写字母。定义一条路径的权值为出现最多次数的字母的出现次数。例如一条路径上的字母分别是 `abaca`，那么这条路径的权值就是 $3$。你的任务是找到这张图上最大的路径权值。（有环则输出 `-1`.）

## 解析

首先考虑 dfs/dp，在合并信息的过程中发现“最多出现的字母”是**不可加**的，也就是说不能只记录最多出现的字母。于是便想到了用 $f_{i,j}$ 记录以 $i$ 为结尾的路径中，字母 $j$ 最多出现的次数。在这里，我们需要将小写字母量化，常用方法是 `str[i] = s[i - 1] - 'a'`，即 ASCII 码相减。

再看题目中，有向图+环+路径，自然让人联想到了拓扑排序，核心思想是用一个节点的所有前驱更新这个节点的信息。将拓扑排序作为转移顺序，也就是拓扑排序的同时完成转移。对于一条边 $(u,v)$，先将 $u$ 的信息合并到 $v$ 上，再考虑这条边产生的贡献。即对于 $\forall i,f_{v,i}=\max(f_{v,i},f_{u,i})$，再把 $v$ 对应的小写字母 $str_v$ 用 $f_{u,str_v}+1$ 更新最大值。

最后考虑一下环的情况。拓扑排序可以判环，记录入队的元素个数 $cnt$，若 $cnt\not=n$（严格来讲是 $cnt<n$）则说明存在环，反之不存在。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	char ch;
	int s = 0, w = 1;
	for(; ch < '0' || ch > '9'; w *= ch == '-' ? -1 : 1, ch = getchar());
	for(; ch >= '0' && ch <=' 9'; s = s * 10 + ch - '0', ch = getchar());
	return s * w;
}
const int MAXN = 300005;
const int MAXM = 300005;
int N, M, f[MAXN][30], str[MAXN], indeg[MAXN];
struct Graph{
	struct Edge{
		int to, nxt;
	} e[MAXM << 1];
	int head[MAXN], tot;
	void add(int u, int v){
		e[++tot].to = v;
		e[tot].nxt = head[u];
		head[u] = tot;
	}
} G;
signed main(){
	cin >> N >> M;
	string s;
	cin >> s; 
	for(int i = 1; i <= N; i++){
		str[i] = s[i - 1] - 'a';
		f[i][str[i]]++;
	}
	for(int i = 1, u, v; i <= M; i++){
		u = read(), v = read();
		indeg[v]++;
		G.add(u, v);
	}
	queue<int> q;
	int cnt = 0;
	for(int i = 1; i <= N; i++){
		if(indeg[i] == 0){
			q.push(i);
			cnt++;
		}
	}
	while(!q.empty()){
		int u = q.front();
		q.pop();
		for(int i = G.head[u], v; i; i = G.e[i].nxt){
			v = G.e[i].to;
			indeg[v]--;
			if(indeg[v] == 0) {
				q.push(v);
				cnt++;
			}
			for(int j = 0; j < 26; j++){
				f[v][j] = max(f[v][j], f[u][j]);
			}
			f[v][str[v]] = max(f[v][str[v]], f[u][str[v]] + 1);
		}
	}
	if(cnt != N){
		cout << -1 << endl;
		return 0;
	}
	int res = 0;
	for(int i = 1; i <= N; i++){
		for(int j = 0; j < 26; j++){
			res = max(res, f[i][j]);
		}
	}
	cout << res << endl;
	return 0;
}
```


---

## 作者：ZolaWatle (赞：1)

# CF919D题解

容易发现，对于每一个点都只有一个状态，而且对于整张图最多只有26个状态（即所有小写字母的总数）。

再看数据范围，$ n $ 的范围 $ 3e5 $，搜索肯定是不行的。在状态数量那么小的情况下，状态是很好表示的。为了方便数组存储，可以用 $ idx_i = tmp - 'a\ ' + 1 $ 表示（$ tmp $ 是 $ i $ 号节点的字母）。这样一来，$ a - z $ 可以转化为 $ 1 - 26 $ 这26个数字。

我们考虑使用**DP**：开一个数组 $ dp_{i,j} $ 表示当走到 $ i $ 点时字母 $ j $ 的最大出现次数。当然，经过了前面的分析，$ j $ 是使用数字表示的。

应当在读入每个点的字母时初始化 dp 数组，使得路径 “ $ x -> x $ ” 上字母 $ idx_x $ 的出现次数为 $ 1 $。

由于这张图是**有向图**，为了满足动态规划的**无后效性**，考虑使用**拓扑排序**进行dp。

设当前操作是从节点 $ x $ 走向节点 $ y $，我们分两种情况考虑状态转移方程：

-	若 $ idx_y = j $，即节点 $ y $ 的字母和现在扫描到的字母相同，那么走到 $ y $ 后，这个字母的出现次数要加一。即：$ dp_{y,j} = max $ { $ dp_{y,j} , dp_{x,j} + 1 $ } 。

-	同理，若字母不同，次数不必加一。即：$ dp_{y,j} = max $ { $ dp_{y,j} , dp_{x,j} $ } 。

在进行拓扑排序时进行状态转移即可。

当然，还要考虑输出 $ -1 $ 的情况。可在拓扑排序过程中开一个计数器 $ sum $，每有一个元素出队就加一，最后判断它是否小于 $ n $，如果小于，则说明有环，输出 $ -1 $ 就行了。

完整代码如下（详情见注释）：

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#define re register int
using namespace std;

const int MAXN=3e5+1;
int n,m,ans,sum,idx[MAXN],in[MAXN],dp[MAXN][27];
vector <int> E[MAXN];
queue <int> q;

inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}
	while (isdigit(ch)){x=x*10+ch-48;ch=getchar();}
	return x*f;
}

int main()
{
	n=read(),m=read();
	
	for(re i=1;i<=n;i++)
	{
		char tmp=getchar();  //这样读入速度更快 
		idx[i]=tmp-'a'+1;  //也可以写tmp-95 
		dp[i][idx[i]]++;  //初始化 
	}
	
	for(re i=1;i<=m;i++)
	{
		re x=read(),y=read();
		E[x].push_back(y);  //用vector存边 
		in[y]++;  //统计入度 
	}
	
	for(re i=1;i<=n;i++)
		if(!in[i])
			q.push(i);
	while(!q.empty())
	{
		re x=q.front();
		q.pop();
		in[x]=-1;  //删点 
		sum++;
		for(re i=0;i<E[x].size();i++)
		{
			re y=E[x][i];
			for(re j=1;j<=26;j++)
			{
				if(idx[y]==j)
					dp[y][j]=max(dp[y][j],dp[x][j]+1);
				else
					dp[y][j]=max(dp[y][j],dp[x][j]);
			}//状态转移 
			in[y]--;
			if(!in[y])
				q.push(y);
		}
	}//拓扑基本操作 
	
	if(sum<n)
	{
		printf("-1");
		return 0;
	}//The value can be arbitrarily large
	
	for(re i=1;i<=n;i++)
		for(re j=1;j<=26;j++)
			ans=max(ans,dp[i][j]);  //由于这条路径可以在任意点出发，任意点结束，因此在dp完毕后还要像这样计算答案 

	printf("%d",ans);
	return 0;
}
```

谢谢观看~

---

## 作者：Fairicle (赞：1)

看到这是一个黄题，我一开始以为一遍 $dfs$ 就可以艹过去了，直到我发现连非极限数据都能T飞...

我们发现权值只有 $26$ 个小写字母，那么状态很好表示，考虑 $dp$。

记 $f_{i,j}$ 表示在 $i$ 这个点，字母 $j$ 的答案。

容易想到可以用 $0...25$ 分别表示 $a...z$。

考虑转移方程：

对于一条边 $(u,v)$，有 $f_{v,j}$ $=$ $max$ $($ $f_{v,j}$ $,$ $f_{u,j}$ $+$ $(ch_v-'a'=j)$ $)$

其中 $ch$ 数组代表每个点的权值是什么，$(ch_v-'a'=j)$  表示的是，如果括号中的条件为真，值为 $1$，否则为 $0$。

那么接下来要考虑的就是，对于每个将要被更新的 $v$，都要保证能更新它的点已经被更新了。这时候想到拓扑排序。

```cpp
拓扑排序使得图中任意一对顶点u和v，若边<u,v>∈E(G)，则u在线性序列中出现在v之前。 ——百度百科
```
想到了这些，代码就很好写了。

code：
```cpp
include"bits/stdc++.h"
using namespace std;
#define ll long long
#define ul unsigned long long
#define ui unsigned int
#define ri register int
inline int read(){
	int x=0,flag=1;
	char ch=getchar()；
	while(ch<'0'||ch>'9'){if(ch=='-') flag=-1;ch=getchar()；}
	while(ch>='0'&&ch<='9'){x=x*10+(ch^48);ch=getchar();}
	return x*flag;
}
int n,m，head[300010],ans,wl,flag，in[300010],f[300010][26];
char ch[300010];
struct node{
	int nxt,to;
}star[300010];
inline void add(int x,int y){
	wl++;
	star[wl].to=y;
	star[wl].nxt=head[x]；
	head[x]=wl;
}
int main()
{
	n=read(),m=read();
	scanf("%s",ch+1);
	for(ri i=1;i<=m;++i)
	{
		int x,y;
		x=read(),y=read();
		if(x==y)
		{
			cout<<-1;
			return 0;
		}
		add(x,y);
		in[y]++;
	}
	queue<int> q;
	for(ri i=1;i<=n;++i)
	if(!in[i])
	{
		q.push(i);
		f[i][ch[i]-'a']++;
	}
	int cnt = 0 , flag = 1;
	while(!q.empty())
	{
		int u = q.front();q.pop()
		for(ri i=head[u];i;i=star[i].nxt)
		{
			int v = star[i].to;
			for(ri j=0;j<26;++j)
			f[v][j] = max(f[v][j],f[u][j] + ((ch[v]-'a'==j)?1:0));
			in[v]--;
			if(in[v]==0) q.push(v);
		}
		cnt++;
	}
	if(cnt<n)
	{
		cout<<-1；
		return 0;
	}
	for(ri i=1;i<=n;++i)
	for(ri j=0;j<26;++j)
	ans = max(ans,f[i][j]);
	cout<<ans;
   	return 0；
}
```


---

## 作者：ArcherHavetoLearnWhk (赞：0)

### 题意
一个 $n$ 个点 $m$ 条边的有向图中，结点有小写字母权值，一条路径的权值是路径上出现次数最多字母的个数，求路径最大权值。若结果为无穷大输出 ```-1```。
### 思路
拓扑排序结合 DP。
#### 路径权值无穷大情况
因为图有环时路径长度可以为无穷大，则路径权值可以为无穷大，所以路径权值为无穷大时，图中一定有环。

考虑通过拓扑排序判断是否有环处理该情况。

拓排流程为：每次所有入度为 $0$ 的结点入队，并取出队首结点，将它及其邻边从图中删除。

拓排结束时，若图有环，因为环中不存在入度为 $0$ 的结点，所以无法删完，否则结点一定删完。所以拓排时统计取出结点个数 $tot$，若 $tot<m$ 则有环。
#### DP
去掉有环的情况后，图变为 DAG，因为 DAG 有拓扑序可以满足 DP 无后效性，考虑 DP。

定义状态：$dp_{i,j}$ 表示以结点 $i$ 为起点的路径中字母 $j$ 出现次数最多的次数。

DP 流程：拓排时，对于队首结点 $u$ 的某邻点 $v$，枚举 $26$ 个小写字母。

转移方程：枚举到当前小写字母 $j$ 时，转移方程有两种情况。

结点 $v$ 的字母权值等于 $j$ 时，$dp_{v,j}=\max(dp_{v,j},dp_{u,j}+1)$，这里 $dp_{u,j}+1$，是因为结点 $v$ 的字母权值等于 $j$，由 $u$ 为起点的路径中 $j$ 的最大出现次数加上结点 $v$ 的贡献 $1$ 进行更新。

否则，$dp_{v,j}=\max(dp_{v,j},dp_{u,j})$，同理。

结合状态的定义很好理解转移方程，

最大的 $dp_{i,j}$ 即为答案。

注意初始化，在读入 $i$ 结点的字母权值 $j$ 时，$dp_{i,j}=1$，因为此时从结点 $i$ 为起点的路径中字母 $j$ 最大出现次数为 $1$，路径即为 $i$ 自己。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,tot,s[300005],in[300005],dp[300005][26];
vector<int>e[300005];
queue<int>q;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);//输入输出优化可以省几百ms
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		char ch;
		cin>>ch;
		s[i]=ch-'a';//转成数字便于处理
		dp[i][s[i]]=1;//dp数组初始化
	}
	while(m--){
		int u,v;
		cin>>u>>v;
		e[u].push_back(v);//存图
		in[v]++;//更新结点入度
	}
	for(int i=1;i<=n;i++)
		if(!in[i])q.push(i);//入度为0就入队
	while(!q.empty()){//拓扑排序
		int u=q.front();
		q.pop();//取出队首的点
		tot++;//统计取出结点数
		in[u]=-114514;//入度设为负数避免再次入队
		for(auto v:e[u]){//简洁的auto和:写法枚举当前结点的邻点
			for(int j=0;j<26;j++){//dp
				if(s[v]==j)dp[v][j]=max(dp[v][j],dp[u][j]+1);
				else dp[v][j]=max(dp[v][j],dp[u][j]);//状态转移
			}
			in[v]--;//当前邻点入度减一
			if(!in[v])q.push(v);//入度为0就入队
		}
	}
    if(tot<n)cout<<-1;//取出结点数小于总数则有环
    else{
        int ma=0;
        for(int i=1;i<=n;i++)
        	for(int j=0;j<26;j++)ma=max(dp[i][j],ma);
		cout<<ma;//否则答案为所有情况中最大的
    }
	return 0;
}
```

---

## 作者：FReQuenter (赞：0)

考虑 dp。令 $f_{i,j}$ 表示从任意一点到点 $i$，字母 $j$ 的最多出现次数。

注意到这是一个图，没有明确的先后顺序，那么我们可以边拓扑排序边 dp。转移就是和自己的父亲节点比 $\max$。

```cpp
#include<bits/stdc++.h>
using namespace std;
vector<int> gv[300005];
string s;
int n,m,ans,ind[300005],f[300005][26];
signed main(){
	cin>>n>>m>>s;
	s='#'+s;
	for(int i=1;i<=m;i++){
		int x,y;
		cin>>x>>y;
		gv[x].push_back(y);
		ind[y]++;
	}
	queue<int> q;
	for(int i=1;i<=n;i++) if(!ind[i]) q.push(i);
	while(!q.empty()){
		int fr=q.front();
		q.pop();
		f[fr][s[fr]-'a']++;
		for(int i=0;i<(int)gv[fr].size();i++){
			ind[gv[fr][i]]--;
			for(int j=0;j<26;j++) f[gv[fr][i]][j]=max(f[gv[fr][i]][j],f[fr][j]);
			if(!ind[gv[fr][i]]) q.push(gv[fr][i]);
		}
	}
	for(int i=1;i<=n;i++) if(ind[i]) return cout<<-1,0;
	for(int i=1;i<=n;i++) for(int j=0;j<26;j++) ans=max(ans,f[i][j]);
	cout<<ans;
}
```

---

