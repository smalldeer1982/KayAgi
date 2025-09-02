# Ping-Pong (Easy Version)

## 题目描述

In this problem at each moment you have a set of intervals. You can move from interval $ (a,b) $ from our set to interval $ (c,d) $ from our set if and only if $ c&lt;a&lt;d $ or $ c&lt;b&lt;d $ . Also there is a path from interval $ I_{1} $ from our set to interval $ I_{2} $ from our set if there is a sequence of successive moves starting from $ I_{1} $ so that we can reach $ I_{2} $ .

Your program should handle the queries of the following two types:

1. "1 x y" $ (x&lt;y) $ — add the new interval $ (x,y) $ to the set of intervals. The length of the new interval is guaranteed to be strictly greater than all the previous intervals.
2. "2 a b" $ (a≠b) $ — answer the question: is there a path from $ a $ -th (one-based) added interval to $ b $ -th (one-based) added interval?

Answer all the queries. Note, that initially you have an empty set of intervals.

## 样例 #1

### 输入

```
5
1 1 5
1 5 11
2 1 2
1 2 9
2 1 2
```

### 输出

```
NO
YES
```

# 题解

## 作者：zjy111 (赞：7)

这道题的题目意思大致如下：

如果存在两个区间a，b，且b的起点和终点间包含a的起点或终点，那么就可以转移，如下
```
a:   _________________
b:       _________________
或
a:        ________
b:   ___________
```
就可以从a转移到b（通俗的说就是两个区间有交集）

那么我们使用深度优先搜索DFS就可以啦~~

我们只需要在符合条件的转移情况下搜索可能的点，然后搜索完之后判断终点是否被访问即可

不知道大法师是什么的可以看[OI Wiki](https://oi-wiki.org/graph/dfs/)

献上码风奇特的代码

```cpp
#include <bits/stdc++.h>
using namespace std;
struct query{  //结构体表示区间
	int a,b;
}q[105];
bool vis[105]; //数组表示某个区间是否被标记
int n,cnt;
void dfs(int x){ //深搜
	vis[x]=1;  //标记为已搜索
	for(int i=1;i<=cnt;i++){  //枚举区间
		query y=q[i];
		if(vis[i])continue;  //已经被访问则跳过(递归调用自己的函数,不这么写会爆的!)
		if((y.a<q[x].a && q[x].a<y.b)||(y.a<q[x].b && q[x].b<y.b)) dfs(i);   //找到符合条件的点,转移
	} 
}
int main() {
	cin>>n;
	while(n--){
		int op,x,y;
		cin>>op>>x>>y;
		if(op==1)
			q[++cnt].a=x,q[cnt].b=y;//加区间
		if(op==2){
			for(int i=1;i<=100;i++)vis[i]=0;//初始化vis数组
			dfs(x); //搜索
			if(vis[y]) cout<<"YES\n"; //判断
			else cout<<"NO\n";
		}
	}
	return 0;
}

```



---

## 作者：_Dynamic_Programming (赞：1)

## 题目大意
如果存在两个区间 $a$，$b$，且 $b$ 的起点和终点间包含 $a$ 的起点或终点，那么就可以从 $a$ 走到 $b$。
```
a -------
b   --------
```
或
```
a   --------
b -------
```
## 做法
我们先开一个结构体，里面包含 $a$ 和 $b$ 两个元素，分别表示区间的左端点和右端点。
### 主函数
1. 输入 $op$\
当 $op = 1$ 时：加入一个区间\
当 $op = 2$ 时：将 $vis$ 数组（表示这个点有没有走到过）清空，DFS 枚举。
2. 如果 $vis[y] = 1$，说明 $y$（目标区间）走到过，输出 `YES`，否则输出 `NO`。
### DFS 函数
1. 走到一个点，将这个点标记为 $1$，表示走到过
2. 再枚举每一个区间，如果满足条件，就 DFS 继续枚举

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
struct point{
    int a, b;
};//定义结构体
point q[105];
int n, cnt, vis[105];
void dfs(int x)
{ 
    vis[x] = 1; //标记为1 
    for(int i = 1; i <= cnt; i++)
    {  
        point y = q[i];
	    if(vis[i] == 1) continue;  
	    if((y.a < q[x].a && q[x].a < y.b) || (y.a < q[x].b && q[x].b < y.b)) dfs(i); //如果满足条件，就dfs枚举
    } 
}
int main() 
{
    cin >> n;
    while(n--)
    {
	    int op, x, y;
	    cin >> op >> x >> y;
	    if(op == 1) q[++cnt].a = x, q[cnt].b = y;
	    else if(op == 2)
	    {
	        memset(vis, 0, 4*105); //vis置0
	        dfs(x); 
	        if(vis[y] == 1) cout << "YES" << endl;
	        else cout <<"NO" << endl;
	    }
    }
    return 0;
}
```

---

## 作者：A_grasser (赞：0)

## 题意简化

有若干操作，可以插入一条线段或询问一条线段能否到达另一条线段。

## 解法分析

首先将题目中一个点讲清楚：什么是两线段存在路径？看下面图就知道了：

![](https://cdn.luogu.com.cn/upload/image_hosting/ixwt9lh3.png)

存在路径的含义其实就是**两条线段有交集**。

解释完这条，接着想思路。我们用结构体存线段，插入是搞定了，那么询问呢？由于本题数据范围小，所以可以直接用深搜。

先初始化标记数组，接着开始从一条线段搜，能到达的都标记上，等到标完后检查另一条线段是否有标记。如果有，那么就能到达。

## 完整代码

```cpp
//已通过
#include<bits/stdc++.h>
//万能头文件
using namespace std;
int n,m;
struct line{int a,b;}q[107];
bool used[107];
void dfs(int u){
	used[u]=1;
	for(int i=1;i<=m;i++){//遍历所有线段 
		line v=q[i];
		if(used[i]!=0) continue;
		if((v.a<q[u].a && q[u].a<v.b) || (v.a<q[u].b && q[u].b<v.b)) dfs(i);//能到达，继续搜 
	} 
}
int main() {
	cin>>n;
	while(n--){
		int op,x,y;
		cin>>op>>x>>y;
		if(op==1){
			m++;
			q[m].a=x,q[m].b=y;
		}
		if(op==2){
			memset(used,0,sizeof(used));//先清空 
			dfs(x);
			if(used[y]!=0) printf("YES\n");//检查是否有标记 
			else printf("NO\n");
		}
	}
	return 0;
}
```

---

## 作者：Fubaogege (赞：0)

#### 思路
你有一些区间，你可以将区间$(a,b)$移动到区间$(c,d)$当且仅当 $c < a < d$ 或 $c < b < d$，如果从区间 $I_1$ 开始存在一个连续的“移动序列”可以到达，那么就有一条从 $I_1$ 到 $I_2$ 的路径。你需要处理下列两种操作：

- “$1$ $x$ $y$”$(x<y)$，添加一个新区间$(x,y)$，保证新区间的长度严格大于之前所有区间。
- “$2$ $a$ $b$”，回答询问：是否存在从第 $a$ 个（添加的）区间到第 $b$ 个区间的路径。从 $1$ 开始计数。

注意，最开始没有区间。

要求搜索从起点到不到的了终点。

- 使用深搜。
- 狂搜所有可能的点。
- 判断终点是否被访问。
- 代码。

```c
	while(cin>>o>>x>>y){
	n--;
	if(n==0)return 0;
		if(o==1)q[++cnt].a=x,q[cnt].b=y;
		if(o==2){
			for(int i=1;i<=100;i++)vis[i]=0;
			dfs(x);
			if(vis[y])cout<<"YES";
			else cout<<"NO";
		}
	}
```

---

## 作者：Empty_Dream (赞：0)

## 题意

有一些区间，当且仅当一个区间包含另一个区间的起点或终点时，这两个区间可以互相到达。

需要处理两种操作：

- 添加一个区间，保证这个区间的长度严格大于之前区间的长度。
- 询问一个区间是否能到达另一个区间。

## 分析

不难看出可以建图然后 dfs 一遍看起点能不能到达终点。

对于添加操作，相当于建图，如果区间 $x$ 能到达区间 $y$（满足题面上的条件），那么就连一条边，建反边同理（可以从 $y$ 转移到 $x$）。

对于查询操作，直接 dfs 看能不能从 $a$ 区间到达 $b$ 区间，dfs 部分不再赘述，最后输出。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int n, len, flag;
int l[105], r[105], vis[105];
vector<int> g[105];

void dfs(int x, int ex){
	if (flag) return ;
	if (x == ex){//走到了
		flag = 1;
		return ;
	}
	vis[x] = 1;
	for (int i = 0; i < g[x].size(); i++){
		int v = g[x][i];
		if (vis[v] == 0) dfs(v, ex);
	}
}

int main(){
	cin >> n;
	for (int i = 1, opt, x, y; i <= n; i++){
		cin >> opt >> x >> y;
		if (opt == 1){
			l[++len] = x, r[len] = y;
			for (int i = 1; i < len; i++){//这里只需要遍历已经添加过的边，后面加进来的边也会再来一次，建反边时相当于从这里建了一条正边
				if ((l[i] < l[len] && l[len] < r[i]) || (l[i] < r[len] && r[len] < r[i])) g[len].push_back(i);//满足条件建边
				if ((l[len] < l[i] && l[i] < r[len]) || (l[len] < r[i] && r[i] < r[len])) g[i].push_back(len);//建反向边
			} 
		}
		else{
			memset(vis, 0, sizeof(vis));//记录每个点是否走过
			flag = 0;
			dfs(x, y);//看能不能从x移动到y
			if (flag == 1) cout << "YES\n";
			else cout << "NO\n";
		}
	}
	return 0;
}
```



---

## 作者：TLEWA (赞：0)

## 思路

这道题的数据范围极小（$n \le 100$），考虑通过一些复杂度较大的算法通过本题。

我的做法是：使用 dfs 判断块之间的可达性，对于每一次询问，我们从始发块跑一遍 dfs，如果能够到达目标块，则输出 `YES`，否则输出 `NO`。接下来我们结合代码讲解。

## AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

struct Node {
	int l,r;
};
vector<Node> vec;

int n;
int x,y;

bool used[105];
bool dfs(int now) {
	if(now==y-1) return 1;
	used[now]=1;
	
	int p=-1;
	for(auto i:vec) {
		p++;
		if(used[p]) continue;
		if(((i.l<vec[now].l && vec[now].l<i.r) || (i.l<vec[now].r && vec[now].r<i.r)) && dfs(p)) return 1; //符合转移条件则向这个块转移
	}
	return 0;
}

int main() {
	cin >> n;
	
	int op;
	for(int i=1;i<=n;++i) {
		cin >> op >> x >> y;
		if(op==1) {
			vec.push_back({x,y});
		}else {
			memset(used,0,sizeof(used));
			if(dfs(x-1)) cout << "YES" << endl;
			else cout << "NO" << endl;
		}
	}
	return 0;
}

```

我们使用一个叫 `used` 的数组记录可达性，到达一个块时，我们尝试向所有尚未到达的块转移（实质就是在求连通块），最后判断是否到达目标块是否在联通块内即可。

## 复杂度分析

每次调用 dfs，都会产生至多 $n$ 次的循环调用，对于每一次询问，最多在每一个点跑一次 dfs，同样最多是 $n$ 次，最后至多 $n$ 次询问，时间复杂度为 $O(n^3)$，在本题的数据范围下可以通过。

---

## 作者：not_so_littlekayen (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF320B)

**前置知识：**[Floyd-Warshall](https://blog.csdn.net/yuewenyao/article/details/81021319)
## 思路
考虑到这是一个求任意两个点之间是否存在路径的问题，可用 Floyd 去求解，即每加一个区间就跑一遍 Floyd。Floyd 的时间复杂度为 $O(n^3)$，所以 $n=100$ 的数据量不会挂掉。

-  定义
```cpp
struct node{
   int l, r;
}section[101];//区间
bool connect[101][101];//两点之间是否连接
int n, num;//num为当前区间个数
```
-  连接

判断函数
```cpp
bool check(int x, int y)//是否存在路径
{
    if(section[y].l < section[x].l&&section[x].l < section[y].r)return 1;
    if(section[y].l < section[x].r&&section[x].r < section[y].r)return 1;
    return 0;
}
```
看不懂的同学可以看下图

![](https://cdn.luogu.com.cn/upload/image_hosting/27p3bxlo.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

连接端点

```cpp
int x, y;//左、右端点
scanf("%d%d", &x, &y);
num++;//增加了一个区间
section[num].l = x;
section[num].r = y;
for(int i = 1;i <= num-1;i++)
{
    if(check(i, num))connect[i][num] = 1;//连接
    if(check(num, i))connect[num][i] = 1;     
    //这里也可以写成connect[i][num] = check(i, num);
}
```
需要注意的是，这里第一个判断成立**不代表**第二个判断也一定成立。[WA记录](https://codeforces.com/contest/320/submission/218107735)

- Floyd
```cpp
for(int k = 1;k <= num;k++)//Floyd
      for(int i = 1;i <= num;i++)
          for(int j = 1;j <= num;j++)
      	 	if(connect[i][k]&&connect[k][j])
                {
                    connect[i][j] = 1;
                }
```
这边可以理解为：当 $i$ 到 $k$ 存在路径**且** $k$ 到 $j$ 也存在路径时，$i$ 一定可以到 $j$。

- 输出

```cpp
int a, b;
scanf("%d%d", &a, &b);
if(connect[a][b])puts("YES");
else puts("NO");
```

完整代码
```cpp
#include <bits/stdc++.h>
using namespace std;
struct node{
	int l, r;
}section[101];
bool check(int x, int y)
{
	if(section[y].l < section[x].l&&section[x].l < section[y].r)return 1;
	if(section[y].l < section[x].r&&section[x].r < section[y].r)return 1;
	return 0;
}
int main()
{
	bool connect[101][101];
	int n, num = 0;
	scanf("%d", &n);
	memset(connect, 0, sizeof(connect));
	while(n--)
	{
		int opt;
		scanf("%d", &opt);
		if(opt == 1)
		{
			int x, y;
			scanf("%d%d", &x, &y);
			num++;
			section[num].l = x;
			section[num].r = y;
			for(int i = 1;i <= num-1;i++)
			{
				if(check(i, num))connect[i][num] = 1;
                if(check(num, i))connect[num][i] = 1;
			}
			for(int k = 1;k <= num;k++)
				for(int i = 1;i <= num;i++)
					for(int j = 1;j <= num;j++)
						if(connect[i][k]&&connect[k][j])
						{
							connect[i][j] = 1;
						}
		}
		else
		{
			int a, b;
			scanf("%d%d", &a, &b);
			if(connect[a][b])puts("YES");
			else puts("NO");
		}
	}
	return 0;
}
```


---

## 作者：Uuuuuur_ (赞：0)

## 思路
比较简单的一道搜索题，可以抽象成一张有向图。

如果区间 $a$ 可以转移到区间 $b$，那么在它们俩之间建立一条有向边，对于每一个新增的区间，它都要和前面的区间判断是否能建边，时间复杂度 $O(n)$。

然后对于询问操作，从 $a$ 开始搜索，判断能不能到达 $b$ 就可以了，时间复杂度 $O(n)$。

总时间复杂度 $O(n^2)$，放心暴力。

注意这张图是会出现环的，所以要用 $vis$ 数组进行标记。


## 代码
```cpp
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
vector<int> g[105];
int a[105][2];
bool vis[105];//可能出现环，所以要判断是否遍历过
int n;
bool f;
int cnt = 1;
void dfs(int x, int y) {
	vis[x] = 1;
	if (x == y) {
		f = 1;
		return ;
	}
	if (f) return ;
	for (int i = 0; i < g[x].size(); i++) {
		int v = g[x][i];
		if (vis[v]) continue;
		dfs(v, y);
	}
}
int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		memset(vis, 0, sizeof(vis));
		int op, x, y;
		cin >> op >> x >> y;
		if (op == 1) {
			a[cnt][0] = x;
			a[cnt][1] = y;
			for (int j = 1; j < cnt; j++) {
				if ((a[j][0] > x && a[j][0] < y) || (a[j][1] > x && a[j][1] < y)) {
					g[j].push_back(cnt);//对于j->now
				}
				if ((x > a[j][0] && x < a[j][1]) || (y > a[j][0] && y < a[j][1])) {
					g[cnt].push_back(j);//对于now->j
                    
				}
			}
			cnt++;
			
		} 
		if (op == 2) {
			f = 0;
			dfs(x, y);
			if (f) cout << "YES" << endl;
			else cout << "NO" << endl;
		}
	}
	return 0;
}
```


---

## 作者：YCSluogu (赞：0)

### CF320B 

[题目链接](https://www.luogu.com.cn/problem/CF320B)

这么多人写 DFS，只有我一个人写 BFS？

#### 分析

基本上就可以将原题抽象成为一个 __有向__ 无环图，然后判断两个点是否在同一连通块。

可以上大法师，也可以像我一样写 BFS。

不过需要注意一点，当如下情况:

```
 ---1---
----2----
```

区间1可以转移区间 2，但是区间 2 无法转移到区间 1。

同时若两个区间仅仅只是存在共点，也是无法转移的。

~~我感觉 BFS 比 DFS 好些点~~

#### code

``` cpp
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e6;

struct node {
  int x, y;
}a[MAXN];

int x, y, cnt = 0;
bool vis[MAXN];
queue<int> q;

// 像这样写可以将转移写得更清晰
void Record(int u, int v) {
  if (vis[v] || u == v || !((a[u].x > a[v].x && a[u].x < a[v].y) || (a[u].y > a[v].x && a[u].y < a[v].y))) {
    return;
  }
  vis[v] = true;
  q.push(v);
}

bool bfs() {
  memset(vis, false, sizeof(vis));
  while (q.size()) q.pop();
  vis[x] = true;
  q.push(x);
  while (!q.empty()) {
    // 不同作用域内变量名不同没事
    int u = q.front();
    if (u == y) {
      return true;
    }
    for (int i = 1; i <= cnt; i++) {
      Record(u, i);
    }
    q.pop();
  }
  return false;
}

int main() {
  int n;
  cin >> n;
  while (n--) {
    int opt;
    cin >> opt >> x >> y;
    if (opt == 1) {
      a[++cnt] = {x, y};
    } else {
      cout << (bfs() ? "YES" : "NO") << endl;
    }
  }
  return 0;
}.
```

#### 完结撒花

---

