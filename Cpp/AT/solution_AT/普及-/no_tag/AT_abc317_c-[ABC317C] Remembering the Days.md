# [ABC317C] Remembering the Days

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc317/tasks/abc317_c

ある地方に、$ 1 $ から $ N $ の番号がついた $ N $ 個の街と、$ 1 $ から $ M $ の番号がついた $ M $ 本の道路があります。

$ i $ 番目の道路は街 $ A_i $ と街 $ B_i $ を双方向に結び、長さは $ C_i $ です。

好きな街からスタートして同じ街を二度以上通らずに別の街へ移動するときの、通る道路の長さの和としてありえる最大値を求めてください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 10 $
- $ 1\ \leq\ M\ \leq\ \frac{N(N-1)}{2} $
- $ 1\leq\ A_i\ <\ B_i\ \leq\ N $
- $ (A_i,B_i) $ は相異なる
- $ 1\leq\ C_i\ \leq\ 10^8 $
- 入力は全て整数である
 
### Sample Explanation 1

$ 4\to\ 1\to\ 3\to\ 2 $ と移動すると、通る道路の長さの和は $ 1110 $ となります。

### Sample Explanation 2

道路と繋がっていない街が存在するかもしれません。

### Sample Explanation 3

!\[図\](https://img.atcoder.jp/abc317/06ac62d13dd1c4b2b469a524a60eb093.png)

## 样例 #1

### 输入

```
4 4
1 2 1
2 3 10
1 3 100
1 4 1000```

### 输出

```
1110```

## 样例 #2

### 输入

```
10 1
5 9 1```

### 输出

```
1```

## 样例 #3

### 输入

```
10 13
1 2 1
1 10 1
2 3 1
3 4 4
4 7 2
4 8 1
5 8 1
5 9 3
6 8 1
6 9 5
7 8 1
7 9 4
9 10 3```

### 输出

```
20```

# 题解

## 作者：Jorisy (赞：30)

数据很小，考虑直接枚举起点搜一遍图，在搜的时候处理当前经过的边权和的最大值即可。代码太简单就不放了。

---

## 作者：LiJoQiao (赞：2)

[题目链接](https://www.luogu.com.cn/problem/AT_abc317_c) [提交记录](https://atcoder.jp/contests/abc317/submissions/44955637)
### 题意简述  
给定 $N$ 个点的无向图有 $M$ 条边，第 $i$ 条路连接 $A_i$ 和 $B_i$ 两点，边权为 $C_i$。  

找到一条每个点只能经过一次的路径，使得边权和最长并输出这个和。  

### 深搜做法
我们观察到这个题的 $N$ 较小（$2 \le N \le 10$），于是我们考虑用深搜来做。  

从一个节点开始，尝试遍历每一条边，在搜索的过程中给每个点打上标记确保不会重复经过某点（并且回溯时需要去掉标记），当前搜索的结果通过函数的返回值来传递，取其中的最大值即可。

主函数内写循环略显繁琐，于是我建立了一个超级源点可以到达每个点，且连接的有向边边权为零，这样在主函数内调用一次即可获得结果。

代码如下。  
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN=10+5,MAXM=MAXN*(MAXN-1)/2;
int N,M,head[MAXN],cnt;
bool vis[MAXN];
struct EDGE
{
    int v,w,nxt;
}edge[MAXM];
void add(int u,int v,int w)
{
    ++cnt;
    edge[cnt].v=v;
    edge[cnt].w=w;
    edge[cnt].nxt=head[u];
    head[u]=cnt;
}
int dfs(int u)
{
    vis[u]=1;
    int ret=0;
    for(int i=head[u];i;i=edge[i].nxt)
    {
        int v=edge[i].v,w=edge[i].w;
        if(!vis[v])ret=max(ret,dfs(v)+w);
    }
    vis[u]=0;
    return ret;
}
inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int main()
{
    N=read();M=read();
    for(int i=1;i<=M;++i)
    {
        int u=read(),v=read(),w=read();
        add(u,v,w);
        add(v,u,w);
    }
    for(int i=1;i<=N;++i)
    {
        add(0,i,0);
    }
    cout<<dfs(0)<<'\n';
    return 0;
}
```

---

## 作者：HEzzz (赞：1)

#### 问题陈述

某地区有编号为 $1$ 至 $N$ 的 $N$ 个城镇和编号为 $1$ 至 $M$ 的 $M$ 条公路。$i$ 号公路双向连接 $A_i$ 号镇和 $B_i$ 号镇，全长 $C_i$。

求从你选择的一个城镇出发，到达另一个城镇时，在不多次经过同一城镇的情况下，你所经过的道路的最大可能总长度。

#### 分析

首先我们可以观察一下这道题的数据范围，仅仅只有 $N\le10$。所以这道题就是**图的遍历**，然后求最大能走的距离的值。最后因为 $N$ 实在是太小了，我们可以使用最笨的方法来遍历图，即暴力遍历。

code

```cpp
#include<bits/stdc++.h>
#define _rep(i,a,b) for(int i=(a);i<=(b);i++)
#define _antirep(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
typedef long long lxl; 
const int N=20;
int n,m,e[N][N],ans;
bool vis[N];
void dfs(int u,int s)
{
	vis[u]=1;
	ans=max(ans,s);//求最大
	_rep(i,1,n) if(!vis[i]&&e[u][i]!=0) dfs(i,s+e[u][i]);//暴力看这个点是否有跟u连边，如果有直接走这条边
	vis[u]=0;//细节，记得要回溯
}
int main()
{
	scanf("%d%d",&n,&m);
	_rep(i,1,m)
	{
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		e[u][v]=w;e[v][u]=w;//暴力存图
	}
	_rep(i,1,n) dfs(i,0);//每一个点都走一下
	printf("%d",ans);
	return 0;
}

```
# 建议评橙

---

## 作者：God_Max_Me (赞：1)

## 题意

给定一个图，求其中任意两点之间距离的最大值，不能重复访问（类似于最长路（也许））。

## 思路

由于我赛时的时候脑子抽了不知道咋写，差点挂，最后写成了状压DP，设 $dp[i][S]$ 表示通过了集合 $S$ 的点，最后在 $i$ 点的最长路径。

那么转移方程可得：

$$
dp_{v,S\operatorname{xor} (2^v)}\gets\ \max\left\{dp_{u,s}+cost\right\}
$$

## 代码
~~~cpp
#include<bits/stdc++.h>
#define int long long
#define endl "\n"
using namespace std;
template<typename P>
inline void read(P &x){
   	P res=0,f=1;
   	char ch=getchar();
   	while(ch<'0' || ch>'9'){
   		if(ch=='-') f=-1;
   		ch=getchar();
   	}
   	while(ch>='0' && ch<='9'){
   		res=res*10+ch-'0';
   		ch=getchar();
	}
	x=res*f;
}
int n,m;
const int Max=20;
struct node{
	int to,w;
};
vector<node> e[120];
int dp[120][1<<14];
signed main(){
	read(n),read(m);
	int u,v,w;
	for(int i=1;i<=m;++i){
		read(u),read(v),read(w);
		u--,v--;
		e[u].push_back(node{v,w});
		e[v].push_back(node{u,w});
	}
	int ans=0;
	int mas=1<<n;
	int to;
	for(int s=0;s<mas;++s){
		for(int i=0;i<n;++i){
			if((s>>i)&1){
				for(auto edge:e[u=i])
					if(!(s>>(to=edge.to)&1)){
						dp[to][s^(1<<to)]=max(dp[to][s^(1<<to)],dp[u][s]+edge.w);
					}
			}
		}
	}
	for(int i=0;i<n;++i){
		ans=max(ans,dp[i][mas-1]);
	}
	cout<<ans<<endl;
	return 0;
}


~~~

---

## 作者：sunkuangzheng (赞：1)

**【题目分析】**

$n \le 10$，直接暴力 dfs。

从每个点开始 dfs，用 $vis$ 记录点是否经过，累加答案即可。

注意开全局变量搜索要回溯，否则会导致答案错误。

**【代码】**

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5+5;
int head[maxn],cnt,vis[15],ans,res,m,u,v,w,n;
struct edge{int to,nxt,w;}e[maxn*2];
void add(int u,int v,int w){e[++cnt].to = v,e[cnt].nxt = head[u],e[cnt].w = w,head[u] = cnt;}
void dfs(int u){
    res = max(ans,res);
    for(int i = head[u],v;v = e[i].to,i;i = e[i].nxt){
        if(vis[v]) continue;
        ans += e[i].w,vis[v] = 1,dfs(v),ans -= e[i].w,vis[v] = 0;
    }
}
int main(){
    cin >> n >> m;
    for(int i = 1;i <= m;i ++) cin >> u >> v >> w,add(u,v,w),add(v,u,w);
    for(int i = 1;i <= n;i ++){
        memset(vis,0,sizeof(vis)),vis[i] = 1,dfs(i);
    }cout << res;
}
```

---

## 作者：FinderHT (赞：0)

### 题面描述

某地区有编号为 $1$ 至 $N$ 的 $N$ 个城镇和编号为$1$至 $M$ 的 $M$ 条道路。

长度为 $C_i$ 的第 $i$ 条道路双向连接城镇 $A_i$ 和城镇 $B_i$。

你可以选择任意一个城镇作为起点出发到任意一个城镇，在不多次经过同一城镇的情况下，你所经过的道路的最大可能总长度。

### 思路分析

我们先建图，然后遍历这 $N$ 个点，从每个点开始 dfs 这张图，我们搜索时，用两个状态 $now$ 和 $sum$，$now$ 表示现在遍历到的点的编号，$sum$ 表示目前遍历过的所有边的边权之和，我们把搜过得点用一个 $vis$ 数组标记，我们搜索前先把起点标记上，然后从 $now$ 这个点开始找联通的边，如果发现有哪个与这条边连接的下一个点未被标记过，就继续从这个点开始往下搜，更新状态 $now$ 为与这条边连接的下一个点，$sum$ 为原来的 $sum$ 加上这条边的边权，如果从起点开始的一条路径上的所有点都被搜过且这条路径上的 $sum$ 大于答案，就更新答案，接着回溯取消上个点的标记，继续搜索从上个点开始的下一条路径。如果 $now$ 重新回到起点，也就是从起点开始的所有路径都被搜完了，就结束本次搜索，取消标记，继续搜索由下一个点作为起点的所有路径，最后输出答案，可保证它是最大的。

### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
struct Edge{
	int v,w,next;
}e[1005];
int ans=-1,cnt=0;
int n,m;
int hd[1005];
void Add_Edge(int u,int v,int w){//链式前向星
	e[cnt].v=v;
	e[cnt].w=w;
	e[cnt].next=hd[u];
	hd[u]=cnt++;
}
vector<int>vis(1005,false);
void dfs(int now,int sum){
    for(int i=hd[now];i!=0;i=e[i].next){//遍历与这个点连接的所有边
        if(!vis[e[i].v]){
			vis[e[i].v]=true;//标记	
            dfs(e[i].v,sum+e[i].w);//继续搜索，更新状态
			vis[e[i].v]=false;//回溯
        }
    }
    ans=max(ans,sum);//维护答案
}
signed main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int a,b,c;
		cin>>a>>b>>c;
        Add_Edge(a,b,c);
        Add_Edge(b,a,c);
		//建双向边
    }
    for(int i=1;i<=n;i++){
		vis[i]=true;	
        dfs(i,0);
		vis[i]=false;//取消标记，继续下一个点的搜索
	}
    cout<<ans;
    return 0;
}
```

---

## 作者：bryce (赞：0)

## 题目大意
给一个无向图，边有边权，要你求任意两点间的最大长度的最大值，每个点只能经过一次。（图不连通）
## 思路分析
枚举每一个点，进行深搜，记得搜到一个点打上标记，遍历完后要回溯。
## 代码
```cpp
#include<iostream>
#define int long long

using namespace std;

inline int read(){register int x = 0, f = 1;register char c = getchar();while (c < '0' || c > '9'){if (c == '-') f = -1;c = getchar();}while (c >= '0' && c <= '9'){x = (x << 1) + (x << 3) + (c ^ 48);c = getchar();}return x * f;}
inline void write(int x){if (x < 0) putchar('-'), x = -x;if (x > 9) write(x / 10);putchar(x % 10 + '0');}

const int N = 15;
int n, m, maxn;
int ans[N][N];
struct edge{
    int v, w, nxt;
}e[200];
int head[N], cnt;
void add(int u, int v, int w){
    e[++cnt] = (edge){v, w, head[u]};
    head[u] = cnt;
}
bool vis[N];
void dfs(int s, int u, int d){
    ans[s][u] =  max(ans[s][u], d);
    for (int i = head[u]; i; i = e[i].nxt){
        int v = e[i].v;
        if (!vis[v]){
            vis[v] = 1;
            dfs(s, v, d + e[i].w);
            vis[v] = 0;
        }
    }
}

signed main(){
    n = read(), m = read();
    for (int i = 1; i <= m; i++){
        int u = read(), v = read(), w = read();
        add(u, v, w), add(v, u, w);
    }
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= n; j++) vis[j] = 0;
        vis[i] = 1;
        dfs(i, i, 0);
        for (int j = 1; j <= n; j++) maxn = max(maxn, ans[i][j]);
    }
    cout << maxn;
    return 0;
}
```


---

## 作者：Failure_Terminator (赞：0)

## Solution

$n$ 范围很小，考虑 dfs。

对于每一点在图中跑一遍 dfs，对于每次调用 dfs，用一个变量记录最大值。

注意标记是否已被访问的标记 $vis$ 在内层 dfs 完成后要还原。

## Code

[Link](https://atcoder.jp/contests/abc317/submissions/44950544)

---

## 作者：Sky_dreamer (赞：0)

## 题目描述
给定有 $n$ 个节点，$m$ 条边的无向图，求从任意节点出发到任意节点结束的最长路。其中每一个节点最多经过一次。

## 解法分析
暴力 DFS 即可。  

枚举每个起始点进行 DFS，求出其最长路。需要注意的是要记录每个点是否走过。

## 代码
[ACcode](https://atcoder.jp/contests/abc317/submissions/44995683)


---

## 作者：BLuemoon_ (赞：0)

[link-LG](https://www.luogu.com.cn/problem/AT_abc317_c)

[link-AT](https://atcoder.jp/contests/abc317/tasks/abc317_c)

## 题意

有 $N$ 个点，$M$ 条边，第 $i$ 条边 $A_i$ 连接 $B_i$ 个点，费用是 $C_i$。求在不重复经过点的情况下，最大费用是什么。

## 思路

DFS 爆搜。

因为保证没有负权边，所以只要能走，对答案就有贡献。如果已经没有点能走了，那就更新答案。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int kMaxN = 15;
int n, m, vis[kMaxN], e[kMaxN][kMaxN], cnt, ans; //e存费用
vector<int> g[kMaxN]; //存哪两个点之间有边
void S(int x) {
  bool flag = 1; //判断还有没有点能走
  for (int i : g[x]) {
    if (vis[i]) {
      continue;
    }
    flag = 0; //还能走
    cnt += e[x][i]; //更新目前答案
    vis[i] = 1;
    S(i); //递归
    cnt -= e[x][i]; //回溯
    vis[i] = 0; //回溯
  }
  if (flag) { //如果没有能走的
    ans = max(ans, cnt); //更新答案
  }
}
signed main() {
  cin >> n >> m;
  for (int i = 1, u, v, w; i <= m; i++) {
    cin >> u >> v >> w;
    g[u].push_back(v), g[v].push_back(u); //存图
    e[u][v] = e[v][u] = w;
  }
  for (int i = 1; i <= n; i++) {
    fill(vis, vis + kMaxN - 2, 0); 
    vis[i] = 1; //这里一定要记得改，我就是最开始没有改
    S(i);
  }
  cout << ans << '\n';
  return 0;
}
```

---

## 作者：Paris_Commune (赞：0)

### 分析

DFS 暴搜。

用 `vis` 数组记录城镇是否访问，`cnt` 记录当前的道路总长。

时间复杂度 $O(n\times n!)$。

### AC 代码

```
#include <bits/stdc++.h>
using namespace std;
int n,m,a[15][15],vis[15],ans;
void dfs(int i,int x){
	vis[i]=1;
	ans=max(ans,x);
	for(int j=1;j<=n;j++){
		if(!vis[j]&&a[i][j]){
			dfs(j,x+a[i][j]);
		}
	}
	vis[i]=0;
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int u,v,w;
		cin>>u>>v>>w;
		a[u][v]=a[v][u]=w;
	}
	for(int i=1;i<=n;i++){
		dfs(i,0);
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：tbdsh (赞：0)

# Update
关于时间复杂度的问题已经更新。感谢 @[dlsnb ](/user/910101) 的指正。
# 题意简述
[更好的阅读体验](https://www.luogu.com.cn/blog/tianbiandeshenghuo11/solution-at-abc317-c)

[洛谷题目传送门](https://www.luogu.com.cn/problem/at_abc317_c)

[AtCoder 题目传送门](https://atcoder.jp/contests/abc317/tasks/abc317_c)

给定 $n$ 个点和 $m$ 条边。每条边连接点 $a_i$ 和 $b_i$，长度为 $c_i$。

请你选择任意一个点作为起点，在不重复经过点的情况下，求出此时会走过的道路的最长长度。

# 分析
本题就是道暴力。

对于每一个点都跑一遍 DFS，边走边更新答案，最后输出最大值即可。

时间复杂度：$O(n\times n!)$。其中，$n!$ 表示 $n$ 的阶乘。

空间复杂度：$O(n)$。

# Code
```cpp
#include<bits/stdc++.h>

using namespace std;
const int MAXN = 15;
int n, m;
long long ans = 0;
struct Node{
  int x, v;
};
vector<Node> a[MAXN];
bool vis[MAXN];
void dfs(int x, long long cnt){
  if (vis[x]){
    return ;
  }
  ans = max(ans, cnt);
  vis[x] = 1;
  for (auto v : a[x]){
    dfs(v.x, cnt + v.v);
  }
  vis[x] = 0;
}
int main(){
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> n >> m;
  while (m--){
    int u, v, w;
    cin >> u >> v >> w;
    a[u].push_back({v, w});
    a[v].push_back({u, w});
  }
  for (int i = 1; i <= n; i++){
    dfs(i, 0);
  }
  cout << ans;
  return 0;
}
```

---

