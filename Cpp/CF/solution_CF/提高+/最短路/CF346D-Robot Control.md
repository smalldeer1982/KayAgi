# Robot Control

## 题目描述

The boss of the Company of Robot is a cruel man. His motto is "Move forward Or Die!". And that is exactly what his company's product do. Look at the behavior of the company's robot when it is walking in the directed graph. This behavior has been called "Three Laws of Robotics":

- Law 1. The Robot will destroy itself when it visits a vertex of the graph which it has already visited.
- Law 2. The Robot will destroy itself when it has no way to go (that is when it reaches a vertex whose out-degree is zero).
- Law 3. The Robot will move randomly when it has multiple ways to move (that is when it reach a vertex whose out-degree is more than one). Of course, the robot can move only along the directed edges of the graph.

Can you imagine a robot behaving like that? That's why they are sold at a very low price, just for those who are short of money, including mzry1992, of course. mzry1992 has such a robot, and she wants to move it from vertex $ s $ to vertex $ t $ in a directed graph safely without self-destruction. Luckily, she can send her robot special orders at each vertex. A special order shows the robot which way to move, if it has multiple ways to move (to prevent random moving of the robot according to Law 3). When the robot reaches vertex $ t $ , mzry1992 takes it off the graph immediately. So you can see that, as long as there exists a path from $ s $ to $ t $ , she can always find a way to reach the goal (whatever the vertex $ t $ has the outdegree of zero or not).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF346D/70cbc1b898581d5fe7e403c459e5024fa4aa2e72.png) Sample 2 However, sending orders is expensive, so your task is to find the minimum number of orders mzry1992 needs to send in the worst case. Please note that mzry1992 can give orders to the robot while it is walking on the graph. Look at the first sample to clarify that part of the problem.

## 说明/提示

Consider the first test sample. Initially the robot is on vertex 1. So, on the first step the robot can go to vertex 2 or 3. No matter what vertex the robot chooses, mzry1992 must give an order to the robot. This order is to go to vertex 4. If mzry1992 doesn't give an order to the robot at vertex 2 or 3, the robot can choose the "bad" outgoing edge (return to vertex 1) according Law 3. So, the answer is one.

## 样例 #1

### 输入

```
4 6
1 2
2 1
1 3
3 1
2 4
3 4
1 4
```

### 输出

```
1
```

## 样例 #2

### 输入

```
4 5
1 2
2 1
1 3
2 4
3 4
1 4
```

### 输出

```
1
```

# 题解

## 作者：369Pai (赞：3)

由于终点的答案容易知道，考虑在反图上 DP。设 $dp_u$ 表示 $u$ 到终点的最少命令数。

对于一个点 $u$，假设它的原图上的出边中没有已经经过的点，那么可以随机走或者用命令走。

$dp_u = \min(\min(dp_v + 1) , \max(dp_v))$。

考虑最终求出答案的路径，绕一圈一定是不优的，所以满足机器人不会到曾经到过的点。

这个方程可以用 SPFA 计算转移，具体见楼下。

由于相邻两点 $dp$ 值的差不超过 $1$，可以使用 01-BFS。

在双端队列中 $dp$ 值是从小到大排序的，所以最后更新点 $u$ 的那个点 $v$ 的 $dp_v$，就是 $\max(dp_v)$。

时间复杂度 $\mathcal{O}(n+m)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
char buf[1 << 23] , *pn , *pe;
inline char Gc(){return pn == pe && (pe = (pn = buf) + fread(buf , 1 , 1 << 23 , stdin) , pn == pe) ? EOF : *pn++;}
inline ll Read()
{
	ll x = 0 , f = 1; char ch = 0;
	for(; !isdigit(ch) ; ch = Gc())if(ch == '-')f = -1;
	for(; isdigit(ch) ; ch = Gc())x = x * 10 + ch - 48;
	return x * f;
}
const int N = 1e6 + 5 , M = N;
int n , m , s , t , tot = 1 , head[N] , in[N] , f[N];
bool vis[N]; struct Edge{int to , nxt;}e[M * 2];
void Add(int u , int v){e[++tot] = {v , head[u]} , head[u] = tot;}
deque<int>dq;
int main()
{
	n = Read() , m = Read();
	for(int i = 1 ; i <= m ; i++)
	{
		int u = Read() , v = Read();
		Add(v , u) , in[u]++;
	}
	s = Read() , t = Read();
	memset(f , 0x3f , sizeof f);
	f[t] = 0 , dq.push_back(t);
	while(!dq.empty())
	{
		int u = dq.front(); dq.pop_front();
		if(vis[u])continue ; 
		vis[u] = 1;
		for(int i = head[u] ; i ; i = e[i].nxt)
		{
			int v = e[i].to;
			in[v]--;
			if(!in[v] && f[u] < f[v])
			{
				f[v] = f[u];
				dq.push_front(v);
			}
			else if(in[v] && f[u] + 1 < f[v])
			{
				f[v] = f[u] + 1;
				dq.push_back(v);
			}
		}
	}
	printf("%d\n" , (f[s] > 1e9 ? -1 : f[s]));
	return 0;
}
```

---

## 作者：yaoyuchen2021 (赞：1)

# 题目大意
给定一张  $N$  点  $M$  边的有向图，机器人每次随机选一条路走，走到走过的点会爆炸，可以在某一时刻要求机器人走特定边，求最坏情况下使机器人安全到达终点的最少的指令数。

# 解题思路
机器人每次会随机走路，可以发现很难正着思考，考虑由终点往前推。

思考一下每一步在干什么：方法一是使机器人从当前节点走到到达终点所需代价最小的一个相邻节点，花费代价 $1$；方法二为机器人随机游走，最坏情况走到到终点代价最大的相邻节点，无代价。最终问题转化为在边权为 $01$ 的图上求最短路，可以使用 01bfs。

# AC Code

```cpp
#include <bits/stdc++.h>
//#define int long long
using namespace std;
int n,m,u,v,s,t,in[1000005],d[1000005];
int H[1000005],N[2000005],G[2000005],l;//链式前向星存图
bool f[1000005];
deque<int> q;
void add(int u,int v)
{
    N[++l]=H[u];H[u]=l;
    G[l]=v;
}
void bfs()//01bfs
{
    while(!q.empty())
    {
        u=q.front();q.pop_front();
        if(f[u])continue;f[u]=true;
        for(int i=H[u];i;i=N[i])
        {
            v=G[i];in[v]--;
            if(d[u]<d[v]&&!in[v])//剩下到终点最劣的边，不花费代价
            {
                d[v]=d[u];
                q.push_front(v);
            }
            else if(d[u]+1<d[v]&&in[v])//选择走指定路径，花费代价1
            {
                d[v]=d[u]+1;
                q.push_back(v);
            }
		}
	}
}
signed main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin>>n>>m;memset(d,0x3f,sizeof(d));
    for(int i=1;i<=m;i++)
    {
        cin>>u>>v;
        add(v,u);in[u]++;
    }
    cin>>s>>t;d[t]=0;q.push_back(t);
    bfs();
    if(d[s]>1e9)cout<<"-1";//无法到达，输出-1
    else cout<<d[s];
	return 0;
}
```

---

## 作者：yspm (赞：1)

设 $f_{i}$ 表示 $i$ 走到终点 $T$ 的最小操作次数，边界为 $f_{T}=1$

根据实际含义，如果不加指令让机器人任意移动那么应当使用 $\max\limitss_{v\in to_x} f_v$ 来更新 $f_x$；而钦定一个出边进行移动一定选择的是最小的 $f_v$，也就是使用 $1+(\min f_v)$ 来转移

那么根据上述转移可以发现：伴随路径增长权值不降

再考察题目中涉及的 “机器人不能走到已经经过了的点”，也就是在一个 $\rm SCC$ 里面走，此时重复经过环上节点一定不是最优选择

最后的工作就是求最短路，本题强制两种转移并行：

使用队列维护待转移点集，每次取出队首 $x$ 并使用 $f_x$ 作为 $\min$ 更新在反向图上能走到的点

完成转移后使用正向图上 $x$ 的后继点的 $\max$ 更新 $f_x$，如果 $f_x$ 被更新，则重新入队

不难证明上述过程的正确性，同时每个元素入队次数不会超过边权最值加 $1$，也即 $2$，所以时间复杂度为 $\Theta(n+m)$

$\texttt{Code Display:}$

```cpp
const int N=1e6+10;
int n,m;
vector<int> G[N],revG[N];
signed main(){
    n=read(); m=read();
    for(int i=1;i<=m;++i){
        int u=read(),v=read();
        G[u].emplace_back(v);
        revG[v].emplace_back(u);
    }
    int S=read(),T=read();
    vector<int> dp(n+1,n+1);
    vector<bool> vis(n+1);
    queue<int> q;
    q.push(T);
    dp[T]=0;
    while(q.size()){
        int fr=q.front(); vis[fr]=0;
        q.pop();
        for(auto t:revG[fr]) if(dp[fr]+1<=dp[t]){
            dp[t]=dp[fr]+1;
            if(!vis[t]) q.push(t),vis[t]=1;
        } 
        int Mx=0;
        for(auto t:G[fr]) ckmax(Mx,dp[t]);
        if(Mx<dp[fr]){
            dp[fr]=Mx;
            q.push(fr);
            vis[fr]=1;
        }
    }
    if(dp[S]==n+1) puts("-1");
    else print(dp[S]);
    return 0;
}
```

---

## 作者：SamHJD (赞：0)

## [CF346D Robot Control](https://www.luogu.com.cn/problem/CF346D)

### 题意

有一个机器人，在有向图中随机行走。你不能让它走到曾经走的地方并使其到达 $t$。你可以添加一些限制使机器人在某一点只能往某一边走，问最小的限制数量。

### 解法

设 $f_u$ 为 $u$ 走到 $t$ 的最小限制数量，那么：

$$f_u=\min(\min(f_v+1),\max(f_v))$$

即增加一条限制和不增加限制取最小值。

相邻两点的 $f$ 值差值小于等于 $1$，因此我们可以用类似 01bfs 的方式转移。

转移从 $t$ 点开始，建立反图即可。

### [代码](https://www.luogu.com.cn/paste/8ntudbqe)

---

## 作者：1234567890sjx (赞：0)

$*2600$？没有这么高吧。

考虑建反图然后 $T\to S$。然后考虑 dp。设 $f_i$ 表示当前在 $i$，到 $T$ 最多走多少步。对于点 $i$ 枚举 $i$ 的所有出点 $j$，用 $i$ 来转移 $j$ 即可。实现的话可以写一个 01-bfs。

dp 具体的话：对于 $i$ 的每一个出点 $j$，可以是随便走到也可以强制命令到。因此有 $f_i=\min(\max(f_j),\min(f_j)+1)$。容易发现相邻状态的差不会超过 $1$ 所以可以 01 bfs 的过程中维护 dp 的值。

时间复杂度为 $O(n+m)$，很快。

---

