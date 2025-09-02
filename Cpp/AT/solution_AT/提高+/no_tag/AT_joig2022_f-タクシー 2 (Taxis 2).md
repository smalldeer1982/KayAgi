# タクシー 2 (Taxis 2)

## 题目描述

### 题目要求

IOI 国家有 $N$ 个城市，编号从 $1$ 到 $N$；$M$ 条道路，编号从 $1$ 到 $M$ 。

想通过每条道路，都只能乘坐出租车。第 $i$（$1 \le i \le M$ ）条道路连接第 $A_i$ 个城市和第 $B_i$ 个城市，$C_i=1$ 表示出租车是红色的，$C_i=2$ 表示出租车是蓝色的。当然，出租车是收费的，收费如下：

- 设 $a$ 为上出租车前所持有的钱数，$b$ 为下车后你的钱数。
- 如果出租车是红色的，那么 $b=a - 1$ 。
- 如果出租车是蓝色的，那么 $b=\lfloor \frac{a+0.5}{2}\rfloor$。

你住在 IOI 国家的 $1$ 号城市。现在，你有 $Q$ 个朋友，第 $i$ 个朋友住在编号为 $t_i$ 的城市。现在你想知道，如果你想到达第 $i$ 个朋友家且到达后身上至少有 $1$ 元钱，那么你至少要带多少元钱？特别的，当这个钱数大于 $L$ 元时，输出 `Large`。

## 说明/提示

**本题有捆绑测试。**

对于 $100\%$ 的数据：

- $2 \le N \le 2\times10^5$，
- $N - 1 \le M \le 2\times10^5$，
- $1 \le Q \le 2\times10^5$，
- $1 \le L \le 10^9$，
- $\forall i \in[1,M],1 \le A_i \lt B_i \le N,C_i\in\{1,2\}$，
- $\forall i\neq j ,(A_i,B_i) \neq (A_j,B_j)$，
- $\forall i \in[2,Q],2 \le T_j \le N$，
- 在任意两个城市之间，你可以通过多条路径来回穿梭，
- 所有输入值均为整数。

#### 部分分

| 子任务编号 | $N\le$ | $M\le$ | $Q\le$ | 特殊性质 | 分数 |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | 
| 1 | $100$ | $N-1$ | $1$ | $\textbf{A},\textbf{C}$ | $9$ |
| 2 | $2\times10^5$ | $N-1$ | $1$ | $\textbf{A}$ | $19$ |
| 3 | $2\times10^5$ | $N-1$ | $2\times10^5$ | $\textbf{A}$ | $19$ |
| 4 | $5\times10^4$ | $5\times10^4$ | $1$ | $\textbf{B}$ | $16$ |
| 5 | $5\times10^4$ | $5\times10^4$ | $1$ | 无 | $20$ |
| 6 | $5\times10^4$ | $5\times10^4$ | $5\times10^4$ | 无 | $12$ |
| 7 | $2\times10^5$ | $2\times10^5$ | $2\times10^5$ | 无 | $5$ |

特殊性质 $\textbf{A}$：$\forall i \in[1,M],(A_i,B_i)=(i,i+1)$。

特殊性质 $\textbf{B}$：$\forall i \in[1,M],C_i=1$。

特殊性质 $\textbf{C}$：$L\le100$。

由 [OIer_Tan](\user\700210) 翻译。

## 样例 #1

### 输入

```
7 6 1 10
1 2 2
2 3 1
3 4 2
4 5 1
5 6 1
6 7 2
5```

### 输出

```
10```

## 样例 #2

### 输入

```
10 9 3 25
1 2 2
2 3 1
3 4 1
4 5 1
5 6 2
6 7 1
7 8 1
8 9 1
9 10 2
10
9
3```

### 输出

```
Large
22
4```

## 样例 #3

### 输入

```
5 6 1 1000000000
1 4 1
1 5 1
4 5 1
3 4 1
3 5 1
2 3 1
2```

### 输出

```
4```

## 样例 #4

### 输入

```
9 11 5 10
1 2 1
1 3 2
2 3 2
2 9 2
3 9 1
4 9 1
8 9 1
5 8 1
5 7 1
4 7 2
6 7 2
2
6
7
8
9```

### 输出

```
2
Large
7
5
3```

# 题解

## 作者：可爱的小棉羊 (赞：0)

好的这是一道题，题意很清楚，我们要是没有那个 ** 蓝边就好了。

我们要是倒着走有个显然的方法，遇到蓝边 $\times 2$，遇到红边 $+1$，然后。。我们就不能跑最短路了。

别急容易发现，从 $1$ 开始走一条边的代价为 $2^{\text{目前路径已走的蓝边数量}}$。

等等，目前路径已走的蓝边数量，想到什么了吗？分层图啊！

然后就简单了，容易发现只有 $O(\log L)$ 条会在我们路径上，只需建立 $32$ 层即可，对于每一层他的边权为他的下层的两倍，蓝边连上上一层，不连通的点就输出 `large`。

[我的提交记录](https://atcoder.jp/contests/joig2022-open/submissions/57903879)

---

## 作者：xiao7_Mr_10_ (赞：0)

## 前言

这题没人写题解？是什么原题吗，不清楚。

考试原题。

## Step 1 问题分析

小学数学有这样一类问题：有一只猴子吃桃子，他第一天吃了一半数量的桃子，第二天吃了 $1$ 个桃子，第三天又吃了剩下桃子的一半，然后它现在只有 $1$ 个桃子，问你一开始它有多少个。

这种问题我们采用**逆推思想**，显然可以得到答案为 $6$。

这题也是一样的，每次询问我们可以以点 $u$ 为起点跑最短路，遇到红色出租车相当于 $+1$，遇到蓝色出租车相当于 $\times 2$。然后初始距离 $dis_{u}$ 设为 $1$ 即可。

时间复杂度 $O((n+m)q \log m)$。

## Step2 算法优化

我们考虑优化。

首先，我们注意到实际上 $\times 2$ 的次数不太多，不然就输出 Large 了。所以合法答案在跑最短路时实际上不会出现 $\log L$ 次蓝边。

所以我们就可以借用**分层图**的思想，把图分层 $\log L +1$ 层，第 $i$ 层表示遇到了 $i$ 次蓝色出租车的点。

但是这样就有一个问题，你的贡献计算出错了。

我们回顾那个问题，实际上对于第 $i$ 层 $+1$ 操作相当于加 $2^i$。

因为这次操作我们会经历 $i$ 次除以 $2$，所以在此 $+1$ 相当于加 $2^i$。

所以我们就可以用 $O((n+m)\log n \log L)$ 的复杂度过掉这题。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e5+5,inf=1e18;
struct Point{
	int v,val;
};
struct state{
	int v,val,dep;
};
struct cmp{
	inline bool operator()(state x,state y){
		return x.val>y.val;
	}
};
priority_queue <state,vector<state>,cmp> q;
vector <Point> e[N];
int n,m,u,v,dis[N][33],L,qt,maxn,now=1,ansu[N];
bool vis[N][33];
inline int query(int x){
	int ans=inf;
	for(register int i = 0;i <= 32;i++)ans=min(ans,dis[x][i]);
	return ans;
}
int w;
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m >>qt >>L;
	for(int i = 1;i <= m;i++){
		cin >> u >> v >> w;w-- ;
		e[u].push_back((Point){v,w});
		e[v].push_back((Point){u,w});
	}
	while(now<=L)now*=2ll,maxn++;
	memset(dis,0x3f,sizeof(dis));
	dis[1][0]=1;
	q.push((state){1,1,0});
	while(!q.empty()){
		int head=q.top().v,tlh=q.top().dep,num=q.top().val;	
		q.pop();
		if(vis[head][tlh])continue;
		vis[head][tlh]=1;
		int tmp=num+(1<<tlh);
		for(register int i = 0;i < e[head].size();i++){
			int v=e[head][i].v,w=e[head][i].val;
			if(!w){ 
				if(dis[v][tlh]>tmp){
					dis[v][tlh]=tmp;
					q.push((state){v,dis[v][tlh],tlh});
				}
			}
			else{
				if(tlh+1<maxn&&dis[v][tlh+1]>tmp){
					dis[v][tlh+1]=tmp;
					q.push((state){v,dis[v][tlh+1],tlh+1});
				}
			}
		}
	}
	for(register int i = 1;i <= qt;i++){
		cin >> u;
		int num=query(u);
		if(num>L)cout << "Large\n";
		else cout << num << "\n";
	}
	return 0;
}
```

# 另一种方法

当然在考试的时候我们的老师卡时，所以刚刚算法不卡常过不了。

所以我们还有更加优秀的做法。

这题问题就是出在实现问题上，迪杰斯特拉的那个 $\log m$ 看着让人非常不爽，但是对于一般的带权图稳定情况下时间复杂度也没多少比它高，你也不可能写斐波那契堆优化这种抽象东西。

但是我们可以不走寻常路，你看看这分层图的每一层是不是长一个样的？

然后我们注意到实际上蓝边的代价为 $0$，然后第 $i$ 层的红边代价为 $2^i$。

所以我们可以首先对每一层单独跑一遍最短路，因为边权一样，所以可以直接 bfs。

然后我们注意到实际上我们可以用上一层的答案去更新这层的答案，但是显然层级越高答案越不优秀。

实际上，这个 bfs 相当于 spfa，你也可以用 01-bfs 的方式实现，处理一层时间复杂度均为 $O(m)$。

但是老师说这题要对状态排序，但是不排序也能过，我觉得不需要排序，有人能给详细证明吗。

对了，这个算法的时间复杂度是 $O((n+m)\log L)$ 的，理论上更加优秀。(~~实际上也是~~)。

---

## 作者：U•ェ•*U (赞：0)

首先我们看到：
- 出租车为红色时，坐车后带的钱变为 $a-1$ 元。
- 出租车为蓝色时，坐车后带的钱变为 $\lfloor \frac{a}{2}\rfloor$ 元。

我们看到 $\lfloor \frac{a}{2}\rfloor $ 和 $a-1$，不难想到单源最短路。

考虑如何做单源最短路（这里采用 $\texttt{Dijkstra}$）：
* $a-1$ 可以直接做。
* $\lfloor \frac{a}{2}\rfloor $ 可以考虑分层图。

什么是分层图？[P4568 飞行路线](https://www.luogu.com.cn/problem/P4568) 了解一下：

* 所谓分层图，即把一整个完整的图，分为若干层，每层对应着原图中的某种状态。

* 分层图每一层大致有如下特点：
  1. 每一层极为相似甚至相同，以至于通常只需要在逻辑上划分出层次即可；
  2. 层层之间有拓扑序；
  3. 每一层都对应原图中的某一种状态。

分层图该如何去做呢：
* 层数不会超过 $O(\log L)$ 层。
* 考虑维护第 $k$ 层边权，因为我们分的是 $\lfloor \frac{a}{2}\rfloor$ 的情况，所以第 $k$ 层的边权就是 $2^k$。
* 然后我们正常的跑一边最短路就可以了，注意加上边权。

如图所示：
![](https://cdn.luogu.com.cn/upload/image_hosting/epgwx4j2.png)

我们直接用 $\texttt{Dijkstra}$ 将每层跑一遍即可，时间复杂度 $O(m\log L\log m)$。

最后找最优答案输出，完结撒花~

---

