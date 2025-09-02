# Game On Leaves

## 题目描述

Ayush and Ashish play a game on an unrooted tree consisting of $ n $ nodes numbered $ 1 $ to $ n $ . Players make the following move in turns:

- Select any leaf node in the tree and remove it together with any edge which has this node as one of its endpoints. A leaf node is a node with degree less than or equal to $ 1 $ .

A tree is a connected undirected graph without cycles.

There is a special node numbered $ x $ . The player who removes this node wins the game.

Ayush moves first. Determine the winner of the game if each player plays optimally.

## 说明/提示

For the $ 1 $ st test case, Ayush can only remove node $ 2 $ or $ 3 $ , after which node $ 1 $ becomes a leaf node and Ashish can remove it in his turn.

For the $ 2 $ nd test case, Ayush can remove node $ 2 $ in the first move itself.

## 样例 #1

### 输入

```
1
3 1
2 1
3 1```

### 输出

```
Ashish```

## 样例 #2

### 输入

```
1
3 2
1 2
1 3```

### 输出

```
Ayush```

# 题解

## 作者：ShineEternal (赞：4)

[更佳的阅读效果](https://vipblog.github.io/yPNLqcRv7/)

## description：

给定 $n$ 个节点的无根树。

两名选手轮流操作，每次可以选择一个叶节点并删除它以及所有和它相连的边。叶节点指度数不超过 $1$ 的节点。删除节点 $x$ 的选手胜利。

你需要判断先手是否有必胜策略。

## solution：

首先观察到这道题的一个特判点：如果 $x$ 刚开始就在叶子节点上，那么先手必然胜利。

注意不要忘了一个小 feature：这棵树可能只有一个节点，所以特判时不能只判度为 $1$。

那么如果不在呢？

这时我们可以知道，与 $x$ 节点相连的边数一定 $\geq 2$。所以由于两个人都实行最优策略，所以到了仅剩下两条与 $x$ 相连的边时就只会开始拆其他的点。

那么答案就只与 $n$ 的奇偶性有关了。判断一下即可。

## code：
```cpp
#include<cstdio>
#include<cstring>
using namespace std;
int p[1005];
int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		int a,b;
		int n,x;
		scanf("%d%d",&n,&x);
		memset(p,0,sizeof(p));
		for(int i=1;i<n;i++)
		{
			scanf("%d%d",&a,&b);
			p[a]++;
			p[b]++;
		}
		if(p[x]<=1)
		{
			printf("Ayush\n");
		}
		else
		{
			if(n%2==1)
			{
				printf("Ashish\n");
			}
			else
			{
				printf("Ayush\n");
			}
		}
	}
	return 0;
} 
```


---

## 作者：npqenqpve (赞：2)

### 题意：

给定一棵 $n$ 个节点的无根树，和一个目标节点 $x$ ，每次可以删除一个叶子节点，问是谁能先删掉 $x$ 节点。

### 思路：

注意是无根树，即将结束时的情况一定可以认为是以 $x$ 为根和一些深度为 $1$ 的叶子节点构成的树，因为每个人都不会在一棵子树上使劲删，而是尽量使得 $x$ 的度数不变，所以最后是这样子，判断 $n$ 的奇偶即可，当 $n$ 为偶数时先手会把与 $x$ 相邻的唯一一个点删掉，后手胜，反之先手胜。

### 代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int head[20005];
struct node
{
    int to,next;
}edge[20005];
int cnt=0;
void add(int u,int v)
{
    edge[++cnt].to=v;
    edge[cnt].next=head[u];
    head[u]=cnt;
}
signed main()
{
	int t;cin>>t;
    while(t--)
    {
    	memset(d,0,sizeof(d));
    	int n,x;cin>>n>>x;
    	if(n==1)
    	{
    		puts("Ayush");
    		continue;
		}
		for(int i=1;i<n;i++)
    	{
    		int u,v;cin>>u>>v;
    		add(u,v),add(v,u);
			d[u]++,d[v]++;
		}
		if(d[x]==1)
		{
			puts("Ayush");
		}
		else if(n%2)
		{
			puts("Ashish");
		}
		else 
		{
			puts("Ayush");
		}
    }
}
```

---

## 作者：boluo2014 (赞：1)

代码超短！
### 思路

首先，题目要求删除的是节点 $x$。那我们就看一下节点 $x$ 关联的边有几条。如果这个条数是 $0$ 或 $1$，那显然，删了就可以，所以 Ayush 赢。

否则，只能把 $n$ 条都给分别取了。那只需要看 $n$ 的奇偶性即可。

这题真简单吧！

---

## 作者：_Revenge_ (赞：1)

### 题目简化和分析：  

首先注意特判 $ x $ 在叶子节点上 ( 即度为 $1$ )。   

因为每人都采用最优策略所以不可能有人执着的为别人开路。   
就是不在同一颗子树上挣扎，会从外围不断清理。    
但是每步必须删除所以就看谁先将周围的点删除，这就别成了对奇偶性的判断。   

至于先删哪一个节点我们没必要考虑。  

- $ n $ 为奇数 不行
- $ n $ 为偶数 可行    


### Solution:   

```cpp
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef double db;

const int N=1e3+50;
const int M=1e5+50;
const int Mod=1e9+7;

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return x*f;
}

int t,n,x;
int siz[N];
int main()
{
	t=read();
	while(t--){
		memset(siz,0,sizeof(siz));
		n=read(),x=read();
		for(int i=1;i<n;++i){
			int u,v;
			u=read(),v=read();
			++siz[u],++siz[v];
		}
		if(siz[x]<2){
			printf("Ayush\n");
		}else{
			if(n&1){
				printf("Ashish\n");
			}else{
				printf("Ayush\n");
			}
		}
	}
	return 0;
}

```

---

## 作者：EC75 (赞：1)

### 难度

这道题黄，但是用 Python 做，就会很简单（前提是去掉加速板子）。

### 思路

**关键思维**：这个问题的主要思想是向后思考。我们不考虑游戏将如何进行，而是考虑游戏的倒数第二个状态会是什么样子，等等。此外，我们还会处理游戏将立即结束的情况（即，当特殊节点是叶节点时）。

**详细解释**：首先，我们来处理游戏结束的情况。只有当特殊节点 $x$ 是叶节点时才会发生这种情况，所以我们所要做的就是检查 $\deg[x]=1$。请注意，$n=1$ 必须在这里单独处理（仅输出```Ayash```）。

在 $x$ 不是叶节点的情况下，答案如下：如果 $n$ 是奇数，```Ashish```获胜，如果 $n$ 是偶数，```Ayush```获胜。

根据关键思想的提示，让我们反向分析这个游戏（为了清楚地解释，假设 $n>10$）。当 $x$ 从游戏中移除时，它不能是剩下的唯一节点（因为之前的玩家可能也移除了 $x$，因此他没有以最佳方式玩）。假设游戏的结构与最后一步的 WLOG 类似（连接到 $x$ 的树可以是任意树）。

想想```Ayush```赢了，最后一步是移除 $x$。现在，在这一举动之前的状态可能是什么？如果```Ashish```从树上移除了一个节点，那么他就没有发挥出最佳效果：因为他本可以移除 $x$！因此，他一定从 $x$ 上移除了一些东西。

考虑到这种情况，```Ashish```实际上不应该移除它，而是应该从树上移除另外一些东西。因此，我们假设游戏结束时的状态是不可能的：实际上，连接到 $x$ 的树应该只包含一个节点（我们已经证明 $x$ 不能是剩下的唯一节点）。

这样子，那就解出来了。

### 代码

我把板子给去掉了以后~~变得非常非常简单~~：

```python
for _ in range(int(input()) if True else 1):
    n, x = map(int, input().split())
    graph = [0]*(n+69)
    graph2 = [0]*(n+69)
    for _ in range(n-1):
        p, q = map(int, input().split())
        graph[p] += 1
        graph[q] += 1
        if p != x and q != x:
            graph2[p] += 1
            graph2[q] += 1
    if graph[x] <= 1:
        print("Ayush")
        continue
    print("Ayush"if (sum(graph2) - n) % 2==0else "Ashish")
```
结束了。

---

## 作者：fighter (赞：1)

首先我们特判一下x一开始就是叶子或者整张图只有一个节点的情况。

对于剩余的情况，如果我们把x看成根，那他必然有大于等于2棵子树。在这个时候，如果双方都采用最优的策略，那么最后一定会变成下图这种情况：

![tdh9zj.png](https://s1.ax1x.com/2020/06/03/tdh9zj.png)

此时先手必败。

由于两人都不想拿完子树，否则x就成为了叶子，所以两个人一定会留下两棵子树，并且一直拿到实在没有办法了才会把x变成叶子。于是就是上面这种情况了。

可以发现根据这个分析，树的结构对两人的策略和结果没有影响，所以只要判断节点的奇偶性即可。

```cpp
#include <bits/stdc++.h>
#define MAX 1005
using namespace std;

int n, m, in[MAX];

int main()
{
    int T;
    cin >> T;
    while(T--){
        memset(in, 0, sizeof(in));
        cin >> n >> m;
        int x, y;
        for(int i = 1; i < n; i++){
            scanf("%d%d", &x, &y);
            in[x]++, in[y]++;
        }
        if(in[m] <= 1) puts("Ayush");
        else if(n&1) puts("Ashish");
        else puts("Ayush");
    }

    return 0;
}
```

---

## 作者：Yizhixiaoyun (赞：0)

[本套题所有题解](https://www.luogu.com.cn/blog/yizhixiaoyun/cf1363-ti-xie)

由于笔者水平较弱，所以可能只能一路做到自己做不了的题，不保证能全部写完。

------------

首先考虑两种特殊情况：$x$ 在叶子节点和只有一个节点，这两种情况都是先手必胜的。

接着我们再考虑，如果两边都采取最优策略，会出现什么情况？

无论开始的时候树的结构是什么，$x$ 节点最后一定会剩下两棵子树。两人都会尽量避免拿掉一棵子树，因为这样 $x$ 就成为叶子，另外一人必胜。

因此这个胜负只与节点个数有关，判断节点个数奇偶性即可。

开始想复杂了，代码实现比较繁琐，请见谅。

```cpp
#include<bits/stdc++.h>
#define betterIO ios::sync_with_stdio(false);cin.tie(0)
#define first puts("Ayush")
#define second puts("Ashish")
using namespace std;
const int maxn=10010;
int T;
int n,x;
int u,v;
map<int,int> mp;

int cnt_edge,head[maxn];
struct edge{
	int to,nxt;
}e[maxn<<1];
void add(int u,int v){
	e[++cnt_edge].nxt=head[u];
	e[cnt_edge].to=v;
	head[u]=cnt_edge;
}

inline void init(){
	mp.clear();
	cin>>n>>x;
	for(register int i=1;i<n;++i){
		cin>>u>>v;
		add(u,v);add(v,u);
		mp[u]++;mp[v]++;
	}
}
int main(){
	betterIO;
	cin>>T;
	while(T--){
		init();
		if(n==1){
			first;continue;
		}
		if(mp[x]==1) first;
		else{
			if(n%2==0) first;
			else second;
		}
	}
}
```

---

