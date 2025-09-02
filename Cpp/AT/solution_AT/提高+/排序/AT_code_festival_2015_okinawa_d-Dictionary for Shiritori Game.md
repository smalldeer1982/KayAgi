# Dictionary for Shiritori Game

## 题目描述

[problemUrl]: https://atcoder.jp/contests/code-festival-2015-okinawa-open/tasks/code_festival_2015_okinawa_d



## 说明/提示

### Problem

In a country where $ N $ different kinds characters are being used, there is a dictionary that contains $ M $ entries, each entry is a definition for a word. All the kinds of characters are listed as character $ 1 $, character $ 2 $, ..., character $ N $. The $ i_{th} $ entry (as a word) of this dictionary begins with the letter $ p_i $, and ends with the letter $ q_i $.

 Cat Snuke and Wolf Sothe will use this dictionary to play a game called **Shiritori** . (Please note that Shiritori in this game is different from a normal Shiritori game.)

- The first move will be made by Cat Snuke, then two players will move alternately.
- For the first move, the player in turn has to say a word the begins with character $ 1 $. If there are no any words that begin with character $ 1 $, the player in turn loses.
- For the rest moves, the player of that turn has to say any word that begins with the last character of the word being said in the previous move from the dictionary. If there is not any appropriate word, the player in turn loses.
- **Any word can be said any number of times** .

There should be some dictionaries that two players can not change the result of the game even if they tried their best. For these dictionaries, in this case, we want to find out if the first player or the second player will win, or even the game will never halt.

All the words in the dictionary will be given. We can assume that the two players will try their best. Please decide if the first player (Cat Snuke) or the second player (Wolf Sothe) will win, or even the game will never halt.

### Sample Explanation 1

\- For the first move, Cat Snuke has to say the first word. - For the second move, if Wolf Sothe said the 6th word, Cat Snuke will have no appropriate word to say for the next move, thus Wolf Sothe wins.

### Sample Explanation 4

Please note that for the first move it is possible that there is no appropriate word that can be said.

## 样例 #1

### 输入

```
6 5
1 2
2 3
3 4
4 2
2 5```

### 输出

```
Sothe```

## 样例 #2

### 输入

```
6 6
1 2
2 3
3 4
4 2
2 5
5 6```

### 输出

```
Draw```

## 样例 #3

### 输入

```
6 8
1 2
1 3
3 4
3 5
2 1
4 5
4 6
5 6```

### 输出

```
Snuke```

## 样例 #4

### 输入

```
4 8
2 3
2 3
3 4
4 1
3 1
2 2
4 2
4 3```

### 输出

```
Sothe```

# 题解

## 作者：Daniel_7216 (赞：2)

昨天艾教讲的题，懒得写，今天写了一下，感觉难度不大，~~可能去年我刚学完广搜就会写了~~

我们通过第三组样例来思考本题做法。首先，由于两个人在玩接龙游戏，所以可以把每个词的开头向结尾连一条有向边，于是游戏就变成了：

从一号点开始，两人轮流在一张有向图上走，无法操作的人失败，问胜负。

于是有下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/xx0x3nqp.png)

根据博弈论的经典套路，我们可以只考虑先手的胜负情况。我们对图上每一个点定义一个状态，表示玩家从这个点出发走一步，最优策略下他的胜负状况。设 T 表示必胜，F 表示必败。不难看出，由于 $6$ 没有出边，当先手从该点出发时必败。因此可以得出第一个结论：如果一个点没有出边，那么这个点对应的状态一定是必败态。

![](https://cdn.luogu.com.cn/upload/image_hosting/6ctmsy3z.png)

这里有一个很经典的结论，对于公平博弈而言，能直接导致必败态出现的状态一定是必胜态。如图 $4$ 和 $5$ 就属于必胜态。

![](https://cdn.luogu.com.cn/upload/image_hosting/1k29njv4.png)

由刚刚的结论不难想到，如果一个状态所导致所有状态全部必胜的话，则该状态必败。如图，$3$ 的两条出边所指向的点都是必胜的，所以一旦先手走到这里，后手接下来走的点都是必胜的。

![](https://cdn.luogu.com.cn/upload/image_hosting/tanrqm8e.png)

根据前面推导的结论，可以推出 $1$ 是必胜点，因为它可以直接导向必败点，$2$ 是必败点，因为它的所有出边所连接的点都是必胜的。

![](https://cdn.luogu.com.cn/upload/image_hosting/yaxvm123.png)

然后代码就很好实现了，~~非常简单，有手就行，唉我手呢~~

```cpp
#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;
int n, m, a, b, vis[100001], cnt[100001];
queue <int> q;
vector <int> G[100001];
void bfs(){
	int x, y;
	while (!q.empty()){
		x = q.front();
		q.pop();
		for (int i = 0; i < G[x].size(); i++){
			y = G[x][i];
			if (vis[x] == 1) cnt[y]--;
			if (vis[y] != -1) continue;
			if (cnt[y] == 0){
				vis[y] = 0;
				q.push(y);
			}
			if (vis[x] == 0){
				vis[y] = 1;
				q.push(y);
			}
		}
	}
}
int main(){
	memset(vis, -1, sizeof(vis));
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++){
		scanf("%d%d", &a, &b);
		G[b].push_back(a);
		cnt[a]++;
	}
	for (int i = 1; i <= n; i++){
		if (cnt[i] == 0){
			vis[i] = 0;
			q.push(i);
		}
	}
	bfs(); 
	if (vis[1] == 1) printf("Snuke\n");
	else if (vis[1] == 0) printf("Sothe\n");
	else printf("Draw\n");
	return 0;
}
```

vis 数组在这里就是记录每个点的状态，$-1$ 表示状态未确定，$0$ 表示必败，$1$ 表示必胜。

---

## 作者：WhisperingWillow (赞：0)

套路的，我们对 $a_i\leftarrow b_i$。

在原图上拓扑排序即可。

```
void bfs(int x){
	while(q.size()){
		int x=q.front();
		q.pop();
		for(auto i:a[x]){
			if(vis[x]==1)--cnt[i];
			if(vis[i]) continue;
			if(cnt[i]==0){
				vis[i]=-1;
				q.push(i);
			}
			if(vis[x]==-1){
				vis[i]=1;
				q.push(i);
			}
		}
	}
}
```

---

## 作者：AutumnKite (赞：0)

[Blog](https://autumnkite.github.io/atcoder-cfoo15D-sol/) 使用效果更佳

[题目传送门](https://code-festival-2015-okinawa-open.contest.atcoder.jp/tasks/code_festival_2015_okinawa_d)

## 题意

给定大小为 $n$ 的字符集和 $m$ 个单词，第 $i$ 个单词以字符 $a_i$ 开头，以字符 $b_i$ 结尾。

Snuke 和 Sothe 轮流玩单词接龙游戏（Snuke 先手）。每次游戏那个人必须说出一个以上个单词的末尾字符开头的单词，第一个人必须说出一个以字符 1 开头的单词。若轮到该人进行游戏时，说不出符合条件的单词，则该人失败。

假设两人绝对聪明，判断谁是胜者或者游戏会永远进行下去。

$n\le 10^5,m\le 2\times 10^5$

## 题解

每个字符当作一个状态，建出游戏图（$a_i\to b_i$）。若游戏图中某个点的所有儿子都是必胜态，则当前点必败；若当前点的所有儿子中有一个状态是必败，则当前点必胜；否则为平局。

直接用 dfs 会因为有环而变得很难搞（求助路过的 dalao 帮蒟蒻看一下 [代码](https://code-festival-2015-okinawa-open.contest.atcoder.jp/submissions/3917268)，WA 3个点 QAQ），所以考虑建反图，倒着推。

## 代码

```cpp
#include <cstdio>
#include <cctype>
#include <cstring>
int read(){
	register int x = 0, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) ;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return x;
}
#define N 100005
#define M 200005
int n, m, f[N], h, t, Q[N], d[N];
int edge, to[M], pr[M], hd[N];
void addedge(int u, int v){  // 连边
	to[++edge] = v, pr[edge] = hd[u], hd[u] = edge;
}
int main(){
	n = read(), m = read();
	for (register int i = 1, x, y; i <= m; ++i)
		x = read(), y = read(), addedge(y, x), ++d[x]; // 倒推，反向连边
	h = 0, t = 0;
	for (register int i = 1; i <= n; ++i) if (!d[i]) Q[++t] = i, f[i] = 2; // 边界状态
	while (h < t){
		int u = Q[++h];
		if (f[u] == 2)  // 当前状态必败
			for (register int i = hd[u]; i; i = pr[i])
				!f[to[i]] ? Q[++t] = to[i] : 0, f[to[i]] = 1; // 则父状态必胜
		else // 当前状态必胜
			for (register int i = hd[u]; i; i = pr[i])
				if (!(--d[to[i]])) Q[++t] = to[i], f[to[i]] = 2; // 所有后继状态都是必胜，则必败
	}
	if (f[1] == 0) printf("Draw\n");
	else if (f[1] == 1) printf("Snuke\n");
	else if (f[1] == 2) printf("Sothe\n");
}
```

---

## 作者：YY_rainbow (赞：0)

[双倍经验](https://www.luogu.com.cn/problem/P6560)

这题问的是先后手的必胜与必输，因此先从博弈论的角度思考这个问题。

关于博弈论，有一个很常用的结论：一个状态 $s$ 是先手必胜状态，当且仅当它的所有后继状态 $t_i$ 中，最少有一个先手必输状态；一个状态 $s$ 是先手必输状态，有可能是它的所有后继状态都是先手必胜**或**它没有任何后继状态。需要注意的是，这些所谓的先手状态，表示的是**面临当前状态的先手，而不是全局的先手**。

上述的结论很好理解，~~性感的想一下也是对的吧~~。

然后我们回到这道题的题面，对于每个单词的开头 $s$ 和结尾 $t$ ，我们可以考虑建反图，即从 $t$ 向 $s$ 连一条单向边，考虑对于每个节点 $i$ 的状态，我们不难看出，在反图上所有入度为 $0$ 的点一定是原图上所有只能作为结尾但不能开头的单词，那么显然，这样的情况一定是先手必输的。我们考虑在反图上拓扑，对于每一个确认状态的点，我们都把他们放进队列去更新其他点。

很明显，通过前面第二段博弈论的结论，如果我们当前的节点 $x$ 可以更新新节点 $y$ ,那么，如果 $x$ 的状态是先手必输 $0$ ，则 $y$ 的状态便一定会被更新为先手必胜 $1$ ，如果当前的 $y$ 入度已经变为了 $0$ 但是 $y$ 的状态仍未更新，我们就可以知道，所有可以转移到 $y$ 的状态，要么全是先手必胜，要么没有状态可以转移到它，则 $y$ 的状态一定是先手必输 $0$ 。

特别的，如果反向图构成了环之后，两个人可以疯狂耍赖，即一直在环上转圈，~~什么为所欲为为所欲为~~，这时候，在环上的节点必定不会更新，始终为 $-1$ 。

最后的答案就是起点 $1$ 的状态。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+99;
int n,m;
int deg[N];
vector<int> g[N];
int ans[N];
queue<int> q;
void topo(){
	for(int i=1;i<=n;i++){
		if(!deg[i]){
			ans[i]=0;
			q.push(i);
		}
	}
	while(!q.empty()){
		int x=q.front();q.pop();
		for(auto y:g[x]){
			deg[y]--;
			if(ans[x]==0){
				if(ans[y]==-1){
					ans[y]=1;
					q.push(y);
				}
			}
			else if(!deg[y]){
				if(ans[y]==-1){
					ans[y]=0;
					q.push(y);
				}
			}
		}
	}
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++) ans[i]=-1;
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		g[v].push_back(u);
		deg[u]++;
	}
	topo();
	if(ans[1]==1) cout<<"Snuke"<<endl;
	else if(ans[1]==0) cout<<"Sothe"<<endl;
	else cout<<"Draw"<<endl;
    return 0;
}
```

---

