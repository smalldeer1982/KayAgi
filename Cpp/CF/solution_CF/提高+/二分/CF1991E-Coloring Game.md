# Coloring Game

## 题目描述

This is an interactive problem.

Consider an undirected connected graph consisting of $ n $ vertices and $ m $ edges. Each vertex can be colored with one of three colors: $ 1 $ , $ 2 $ , or $ 3 $ . Initially, all vertices are uncolored.

Alice and Bob are playing a game consisting of $ n $ rounds. In each round, the following two-step process happens:

1. Alice chooses two different colors.
2. Bob chooses an uncolored vertex and colors it with one of the two colors chosen by Alice.

Alice wins if there exists an edge connecting two vertices of the same color. Otherwise, Bob wins.

You are given the graph. Your task is to decide which player you wish to play as and win the game.

## 说明/提示

Note that the sample test cases are example games and do not necessarily represent the optimal strategy for both players.

In the first test case, you choose to play as Alice.

1. Alice chooses two colors: $ 3 $ and $ 1 $ . Bob chooses vertex $ 3 $ and colors it with color $ 1 $ .
2. Alice chooses two colors: $ 1 $ and $ 2 $ . Bob chooses vertex $ 2 $ and colors it with color $ 2 $ .
3. Alice chooses two colors: $ 2 $ and $ 1 $ . Bob chooses vertex $ 1 $ and colors it with color $ 1 $ .

Alice wins because the edge $ (3, 1) $ connects two vertices of the same color.

In the second test case, you choose to play as Bob.

1. Alice chooses two colors: $ 2 $ and $ 3 $ . Bob chooses vertex $ 1 $ and colors it with color $ 2 $ .
2. Alice chooses two colors: $ 1 $ and $ 2 $ . Bob chooses vertex $ 2 $ and colors it with color $ 1 $ .
3. Alice chooses two colors: $ 2 $ and $ 1 $ . Bob chooses vertex $ 4 $ and colors it with color $ 1 $ .
4. Alice chooses two colors: $ 3 $ and $ 1 $ . Bob chooses vertex $ 3 $ and colors it with color $ 3 $ .

Bob wins because there are no edges with vertices of the same color.

## 样例 #1

### 输入

```
2
3 3
1 2
2 3
3 1


3 1

2 2

1 1
4 4
1 2
2 3
3 4
4 1

2 3

1 2

2 1

3 1```

### 输出

```
Alice
3 1

1 2

2 1






Bob

1 2

2 1

4 1

3 3```

# 题解

## 作者：_O_v_O_ (赞：3)

很明显当图中有一个奇环，那么 Alice 肯定有必胜策略，我们只用一直向 Bob 推 `1 2` 即可，因为奇数环上一定会出现在连接两个相同颜色结点的边。

然后我们就发现反之 Bob 必胜。

因为图中已经没有奇环了，所以这张图一定是**二分图**，那么我们遇到一个 $(a,b)$：

- 如果 $a=1,b=2$，那么我们可以选一个左部点染 $1$，如果左部点染完了，那么就在右部点染 $2$。
- 如果 $a=1,b=3$，那么我们可以选一个左部点染 $1$，如果左部点染完了，那么就在右部点染 $3$。
- 如果 $a=2,b=3$，那么我们可以选一个右部点染 $2$，如果右部点染完了，那么就在左部点染 $3$。

那么为什么这个是正确的呢？我们注意到，左部点只会染 $1,3$，右部点只会染 $2,3$，而 $3$ 作为“备用”的颜色，只会在一边全部染完了才会出现，也就是说，左部点与右部点出现的颜色集合的交集肯定为空集，所以我们根据二分图的性质进而推断出不会出现连接两个相同颜色结点的边！

最后多测记得清空，IO 交互题输出换行用 `endl`。

本蒟蒻又臭又长的代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=1e4+5;
int T;
int n,m;
vector<int> e[N];
int vis[N];
bool fg;

bool bfs(int x){//bfs染色求二分图左右部点
	queue<int> q;q.push(1);
	fill(vis+1,vis+n+1,-1);
	vis[1]=0;
	while(!q.empty()){
		int f=q.front();q.pop();
		for(int i:e[f]){
			if(vis[i]!=-1&&vis[i]==vis[f]) return 1;
			if(vis[i]!=-1) continue;
			vis[i]=vis[f]^1;
			q.push(i);
		}
	}
	return 0;
}

void solve(){
	cin>>n>>m;
	for(int i=1,u,v;i<=m;i++){
		cin>>u>>v;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	if(bfs(1)){
		cout<<"Alice"<<endl;
		for(int i=1,a,b;i<=n;i++){
			cout<<1<<' '<<2<<endl;
			cin>>a>>b;
		}
	}
	else{
		cout<<"Bob"<<endl;
		vector<int> v[2];
		for(int i=1;i<=n;i++){
			v[vis[i]].push_back(i);
		}
		for(int i=1,a,b;i<=n;i++){
			cin>>a>>b;
			if(a>b) swap(a,b);
			if(a==1){
				if(!v[0].empty()){
					cout<<v[0].back()<<' '<<a<<endl;
					v[0].pop_back();
				}
				else{
					cout<<v[1].back()<<' '<<b<<endl;
					v[1].pop_back();
				}
			}
			else{
				if(!v[1].empty()){
					cout<<v[1].back()<<' '<<b<<endl;
					v[1].pop_back();
				}
				else{
					cout<<v[0].back()<<' '<<a<<endl;
					v[0].pop_back();
				}
			}
		}
	}
	for(int i=1;i<=n;i++) e[i].clear();//多测清空
}

signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>T;
	while(T--) solve();
	return 0;
}
```

---

## 作者：Reunite (赞：2)

构造场被创飞了。

感觉 $E$ 小于 $D$。考虑二分图染色，若不是二分图，则说明有奇环，那我们选择 Alice，每次无脑输出 $1\ 2$，这样相当于丢给 Bob 去二分图染色，可这都不是二分图，所以肯定赢。

若是二分图，分成左右两部考虑，直接给出如下构造。选择 Bob，只要 Alice 给出了 $1$，并且左部点还有，那我们就随便把一个左部点染成 $1$，同理右部点染成 $2$。因为她每次至少会给出 $1,2$ 中的一个，所以我们一定能先用一种颜色染完某一部的点。剩下的我们只需要选择和染完的那部点颜色不一样的颜色去把另一边的点染完就行。

复杂度 $O(n+m)$。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

int T,n,m,ok;
int col[10005];
int a[10005];
int b[10005];
vector <int> g[10005];

inline void in(int &n){
	n=0;
	char c=getchar();
	while(c<'0' || c>'9') c=getchar();
	while(c>='0'&&c<='9') n=n*10+c-'0',c=getchar();
	return ;
}

inline void dfs(int u,int c){
	col[u]=c;
	for(int v:g[u]){
		if(!col[v]) dfs(v,3-c);
		else if(3-c!=col[v]){
			ok=0;
			return ;
		}
		if(!ok) return ;
	}
}

int main(){
	in(T);
	while(T--){
		in(n),in(m);
		for(int i=1;i<=n;i++) g[i].clear(),col[i]=0;
		while(m--){
			int u,v;
			in(u),in(v);
			g[u].emplace_back(v);
			g[v].emplace_back(u);
		}
		ok=1;
		dfs(1,1);
		if(!ok){
			puts("Alice");
			fflush(stdout);
			while(n--){
				puts("1 2");
				fflush(stdout);
				int u,v;
				in(u),in(v);
			}
		}
		else{
			int c1=0,c2=0;
			for(int i=1;i<=n;i++)
				if(col[i]==1) a[++c1]=i;
				else b[++c2]=i;
			puts("Bob");
			fflush(stdout);
			while(n--){
				int x,y;
				in(x),in(y);
				if((x==1||y==1)&&c1) printf("%d 1\n",a[c1--]);
				else if((x==2||y==2)&&c2) printf("%d 2\n",b[c2--]);
				else if(c1) printf("%d %d\n",a[c1--],(x==1||y==1)?1:3);
				else printf("%d %d\n",b[c2--],(x==2||y==2)?2:3);
				fflush(stdout);
			}
		}
	}

	return 0;
}

```

---

## 作者：Jairon314 (赞：1)

> [更好的体验](https://www.cnblogs.com/Jair314/p/18330313)

$$ \large\textbf{Solution} $$

----------
$$ \text{Coloring Game} $$

> E
> 
> [题目链接](https://www.luogu.com.cn/problem/CF1991E)
> 
> [提交记录](https://www.luogu.com.cn/record/169268116)

题意：给你一张连通图和三种颜料，$A$ 和 $B$ 博弈，每轮 $A$ 限制一种颜色不能选择，$B$ 可以选一个点用剩下两种颜色的一种涂色。涂色完仍然没有一条边上相邻两个点的颜色相同则 $B$ 胜，否则 $A$ 胜。问谁必胜？在图上交互。

分析：

思路有点点清奇。。一开始觉得第三种颜色没有用，所以直接想了 $A$ 持续限制颜料 $3$ 的使用时的情况，发现这样的话链好处理，剩下的可以把图拆成若干可重叠的环。此时想到对环的长度进行奇偶分讨。

1. 当存在奇环时，显然 $A$ 就必胜了，只须一直限制颜料三的使用，$B$ 只能在一个环上两种颜料交替涂色，奇环注定会出现同色碰在一起的情况。

2. 考虑 $n$ 元偶环。当时构思了一个很古怪的构造，感觉上好像偶环是 $B$ 必胜。

这时我突然意识到，貌似存在奇环 $A$ 必胜，否则 $B$ 必胜。

那怎么构造对抗交互呢？好像我的构造又有点难实现出来，也想不清楚。

然后回头审视一下，其实对于有无奇环的判断，就相当于对图是否为二分图的判断。那么为什么二分图 $B$ 必胜呢？接下来就准备利用二分图的性质构造了。

考虑到二分图具有左部点集和右部点集，且这两个点集内部两两无边。

考虑尽量使得左部点集都涂颜料 $1$，右部点集都涂颜料 $2$。因为二分图嘛，这个想法是自然的。但是题目环境下，可能会限制一个颜色不让用，但是不管限制哪个颜色，要么能使用 $1$，要么能使用 $2$，要么能使用 $1$ 或者 $2$，所以只要左部点集和右部点集都没有被涂满，总能选一个涂上色。如果两个集合里有一个集合中所有点已经被涂满了，那么剩下的点我们能涂对应部点集的颜色就涂这种颜色，不能涂就涂颜料 $3$。

然后就找到正确的构造了。

总结：非常棒的构造+分讨题，赛时最后五分钟过了，没有掉分。。不过本来也没几分。

----------

---

## 作者：yyz1005 (赞：1)

图论丁真，鉴定为二分图。

首先如果图不是二分图也就是说有一个奇环则无法只用两种颜色染色，选 Alice 不停的给 1,2 就可以。

如果是二分图，那么首先染色，然后用 1 去填第一种颜色，2 去填第二种颜色，如果给出的是 $x \; 3$ 但是颜色 $x$ 已经被染完了那就用 $y$ 去染另一种，做完了。

[Code](https://codeforces.com/contest/1991/submission/273270194)

---

## 作者：白鲟 (赞：1)

猜测一定与二分图染色相关。

易知若给出的图不是二分图，选 Alice 每次均给出 $1,2$ 即可获胜。是否存在一种策略，若给出的是二分图，选 Bob 就可以获胜？

注意到 Alice 每轮提供的颜色至少有 $1,2$ 中的一种。考虑先使用 $1,2$ 对图进行二分图预染色。在面对 Alice 的给出的颜色时，尽量先使用 $1,2$ 染色避免 $3$ 的干扰，迫不得已时再选择 $3$。

具体地，对于每一轮，若 Alice 提供的颜色中含有 $1$ 且预染色为 $1$ 的点还没染光，则挑出其中一个染为 $1$；若提供的颜色中含有 $2$ 且预染色为 $2$ 的点还没染光，则挑出其中一个染为 $2$；否则，则一定有一种预染色的点已经被染光，此时另一种预染色的点染为 $3$ 不会影响二分图染色的性质。综上，在预染色的两种点都还未被染光时，遵从预染色的结果进行染色是可行的；在某一种预染色的点被染光后，另一种预染色的点无论染成它本身的颜色还是 $3$ 均可，这也是可行的。


```cpp
#include <cstdio>
#include <vector>
const int maxn = 1e4;
int T, n, m, x, y, tot, head[maxn + 1], suc[maxn << 1 | 1], to[maxn << 1 | 1],
    color[maxn + 1];
bool flag;
std::vector<int> waiting[2];
inline void add_edge(int x, int y) {
    suc[++tot] = head[x];
    head[x] = tot;
    to[tot] = y;
}
void binary_color(int now, int last) {
    color[now] = 3 - last;
    for (int i = head[now]; i; i = suc[i]) {
        if (!color[to[i]]) {
            binary_color(to[i], color[now]);
        }
        else if(color[to[i]] == color[now]) {
            flag = false;
        }
    }
    return;
}
int main() {
    scanf("%d", &T);
    while (T--) {
        tot = 0;
        flag = true;
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; ++i) {
            head[i] = 0;
            color[i] = 0;
        }
        for (int i = 1; i <= m; ++i) {
            scanf("%d%d", &x, &y);
            add_edge(x, y);
            add_edge(y, x);
        }
        for (int i = 1; i <= n; ++i) {
            if (!color[i]) {
                binary_color(i, 1);
            }
        }
        if (!flag) {
            puts("Alice");
            fflush(stdout);
            for (int i = 1; i <= n; ++i) {
                puts("1 2");
                fflush(stdout);
                scanf("%*d%*d");
            }
        }
        else {
            puts("Bob");
            fflush(stdout);
            waiting[0].clear();
            waiting[1].clear();
            for (int i = 1; i <= n; ++i) {
                waiting[color[i] - 1].push_back(i);
            }
            for (int i = 1; i <= n; ++i) {
                scanf("%d%d", &x, &y);
                if(x != 3 && y != 3) {
                    if(!waiting[0].empty()) {
                        printf("%d 1\n", waiting[0].back());
                        waiting[0].pop_back();
                    }
                    else {
                        printf("%d 2\n", waiting[1].back());
                        waiting[1].pop_back();
                    }
                }
                else if(x != 2 && y != 2) {
                    if(!waiting[0].empty()) {
                        printf("%d 1\n", waiting[0].back());
                        waiting[0].pop_back();
                    }
                    else {
                        printf("%d 3\n", waiting[1].back());
                        waiting[1].pop_back();
                    }
                }
                else {
                    if(!waiting[1].empty()) {
                        printf("%d 2\n", waiting[1].back());
                        waiting[1].pop_back();
                    }
                    else {
                        printf("%d 3\n", waiting[0].back());
                        waiting[0].pop_back();
                    }
                }
                fflush(stdout);
            }
        }
    }
    return 0;
}
```

---

## 作者：Cute__yhb (赞：0)

## 思路

先考虑 Alice 赢的情况。

注意到是三种颜色来染色，但如果不是二分图的话，图中存在奇环，不能进行二染色，所以对于每次交互，直接输出 $1$ $2$ 即可。

接着考虑 Bob 赢的情况。

既然是 Bob 赢，说明是二分图，先进行二染色，用两个栈存两种颜色。

然后可以让一部分染 $1$，一部分染 $2$。

如果这两个栈不空的情况下，可以先染 $1$ 和 $2$。$3$ 最后其中一个栈空再染。

证明：

先染 $1$ $2$ 可以保证它们不在同一个集合里，最后染 $3$，可以让 $3$ 颜色都集中在同一集合，不会有连边。

## 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define INF 0x3f3f3f3f
#define endl '\n'
#define fi first
#define se second
#define pii pair<int,int>
#define p_q priority_queue
#define iter iterator
#define pb push_back
#define eps 1e-8
#define oper operator
#define mk make_pair
#define ls x<<1
#define rs x<<1|1
int n,vis[200005],F[200005],m;
vector<int>a[200005];
stack<int>st1,st2;
bool dfs(int x,int col){//二分图判定/染色
	vis[x]=col;
	for(int i=0;i<a[x].size();i++){
		int y=a[x][i];
		if(vis[y]==col) return 0;
		if(!vis[y]&&!dfs(y,3-col)) return 0;
	}
	return 1;
}
void solve(){
	cin>>n>>m;
	while(!st1.empty()) st1.pop();//多测不清空，爆零两行泪
	while(!st2.empty()) st2.pop();
	for(int i=1;i<=n;i++) vis[i]=0,F[i]=0;
	for(int i=1;i<=n;i++) a[i].clear();
	bool f=0;
	for(int i=1;i<=m;i++){//建边
		int x,y;
		cin>>x>>y;
		a[x].pb(y);
		a[y].pb(x);
	}
	for(int i=1;i<=n;i++){//判定二分图
		if(!vis[i]&&!dfs(i,1)){
			f=1;
			break;
		}
	}
	if(f){//不是二分图，Alice赢
		puts("Alice");
		while(n--){
			puts("1 2");//二染色
			fflush(stdout);//清空缓冲区
			int x,y;
			cin>>x>>y;
		}
	}else{
		puts("Bob");//二分图，Bob赢
		for(int i=1;i<=n;i++){
			if(vis[i]==1){//两个集合，用来存颜色
				st1.push(i);
			}else st2.push(i);
		}
		while(n--){
			int x,y;
			cin>>x>>y;
			if((x==1||y==1)&&!st1.empty()){//1栈不空
				cout<<st1.top()<<" 1"<<endl;
				st1.pop();
			}else if((x==2||y==2)&&!st2.empty()){//2栈不空
				cout<<st2.top()<<" 2"<<endl;
				st2.pop();
			}else{
				if(st1.empty()){//1栈空，2栈不空，把3放到2栈
					cout<<st2.top()<<" 3"<<endl;
					st2.pop();
				}else{//2栈空，放到1栈
					cout<<st1.top()<<" 3"<<endl;
					st1.pop();
				}
			}
			fflush(stdout);
		}
	}
}
int main(){
	int t;
	cin>>t;
	while(t--) solve();
    return 0;
}
```

---

## 作者：zhangxiao666 (赞：0)

看到染色想到二分图。

首先原图要么是二分图要么有奇环，这个可以用染色法判断。

那么分类讨论。

1. 原图存在奇环。那么肯定选 Alice，一直输出 $1 2$ 即可，由于有奇环，所以 Bob 必输。

2. 原图为二分图。首先选 Bob。然后按照二分图把点分成两个集合，$1$ 染左边，$2$ 染右边，一个集合染没了另一个集合染另外 $2$ 种颜色即可，由于只有 $3$ 种颜色，所以一定会有 $1$ 个能染的颜色。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e4 + 10;

int n, m, flag;

vector<int> e[N];
int col[N];

int cntl, cntr, l[N], r[N];

void Dfs(int u, int c)
{
	col[u] = c;
	for (int v : e[u])
	{
		if (! col[v])
			Dfs(v, 3 - c);
		else if (col[v] != 3 - c)
		{
			flag = 0;
			return ;
		}
	}
} 

int main()
{
	std::ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int T; cin >> T;
	while (T --)
	{
		cin >> n >> m;
		for (int i = 1; i <= n; i ++)
			col[i] = 0, e[i].clear();
		for (int i = 1; i <= m; i ++)
		{
			int u, v; cin >> u >> v;
			e[u].push_back(v);
			e[v].push_back(u);
		}
		
		flag = 1;
		Dfs(1, 1);
		
		if (flag == 0) 
		{
			cout << "Alice\n";
			cout.flush();
			for (int i = 1; i <= n; i ++)
			{
				cout << "1 2\n";
				cout.flush();
				int u, v; cin >> u >> v;
			}
		}
		else
		{
			cout << "Bob\n";
			cout.flush();
			cntl = cntr = 0;
			for (int i = 1; i <= n; i ++)
			{
				if (col[i] == 1)	
					l[++ cntl] = i;
				else 
					r[++ cntr] = i;
			}
			
			for (int i = 1; i <= n; i ++)
			{
				int a, b; cin >> a >> b;
				if (a > b)
					swap(a, b);
				if (a == 1)
				{
					if (cntl)
						cout << l[cntl--] << " " << a << "\n";
					else
						cout << r[cntr--] << " " << b << "\n";
				}
				else
				{
					if (cntr)
						cout << r[cntr--] << " " << b << "\n";
					else 
						cout << l[cntl--] << " " << a << "\n";
				}
				cout.flush();
			}
		}
	}
	return 0;
}

```

---

## 作者：AKPC (赞：0)

我们可以先考虑颜色只有两种的情况，显然与原图是否为二分图有关。

- 如果不是，选 Alice。
- 如果是，选 Bob。

下面是证明以及策略：

- 如果不是，Alice 可以控制颜色范围在 $1,2$ 中，因为无论对方扮演的 Bob 的决策，给非二分图黑白染色，一定存在一条边连接同色两点，故 Alice 肯定获胜。
- 如果是，对方扮演的 Alice 在两种颜色的限制中不停地问 $1,2$ 两种颜色，因为是二分图，Bob 一定存在一种黑白染色策略，使得没有连接两个同色点的边。

依然考虑据是否为二分图讨论，扩展到三种颜色是这样的：

- 如果不是二分图，Alice 仍然可以不断限制 $1,2$，达到目的。
- 如果是，根据 $k$ 分图的性质，如果一个图是 $k$ 分图，那么其也是 $k+1$ 分图。显然，二分图扩展到三种颜色依然是三分图，故 Bob 依然可以模拟。

---

## 作者：Engulf (赞：0)

类似的题目：CF1537F。

请注意区分对点进行黑白染色和按照题目要求染色的区别，作者发现时已经快写完了，不想修改，相信读者能根据语境区分开来。

对原图进行染色，使得相邻两个点的颜色不同。分两种情况讨论：

- 无法完成染色，即存在奇环，我们选择 Alice，只允许交互库用两种不同颜色染色，如每次都输出 $\tt{1, 2}$。
- 完成了染色，我们选择 Bob。此时整张图被分为两个点集，分别记作黑点和白点。记每次给出的颜色为 $a, b(a<b)$，按照如下策略染色：
  - $a=1$，若存在未染色的白点，找一个白点染上 $1$。否则只能对黑点染色，染 $b$。
  - $a\neq 1$，即 $b=3$，若存在未染色的黑点，染 $b$，否则只能对白点染色，染 $a$。

下面我们证明正确性：
- 我们作为 Alice 时，我们只允许交互库用两个颜色，因为环长为奇数，无论如何都会有两个相邻节点颜色相同。自行画图理解，这个很 trival。
- 作为 Bob 时，记将白点染为 $1$，黑点染为 $3$ 为**理想状态**。
  - 交互库给出 $1, 3$，我们总能染我们想要的。
  - 交互库给出 $1, 2$，存在白点，则给白点染 $1$，否则没有白点了，给黑点染 $2$。
  - 交互库给出 $2, 3$，存在黑点，则给黑点染 $3$，否则没有黑点，给白点染 $2$。
- 发现 $2$ 只会出现在其中一种颜色染完色，这种颜色达成了**理想状态**，即都 $\neq 2$，所以剩下的颜色染 $2$ 还是相应的理想状态都是合法的。

代码实现很烦。

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;

#ifdef ONLINE_JUDGE
#define debug(...) 0
#else
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#endif

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tt;
    cin >> tt;
    while (tt--) {
        int n, m;
        cin >> n >> m;
        vector<vector<int>> g(n + 1);
        for (int i = 1, x, y; i <= m; i++) {
            cin >> x >> y;
            g[x].emplace_back(y);
            g[y].emplace_back(x);
        }

        vector<int> col(n + 1, -1);
        bool adjacent = [&]() {
            queue<int> q;
            q.push(1); col[1] = 0;
            while (!q.empty()) {
                int u = q.front(); q.pop();
                for (auto v: g[u]) {
                    if ((~col[v]) && col[u] == col[v])
                        return false;
                    if (~col[v]) continue;
                    col[v] = col[u] ^ 1;
                    q.push(v);
                }
            }
            return true;
        }();

        cout << (!adjacent ? "Alice" : "Bob") << endl;

        if (!adjacent) {
            for (int i = 1; i <= n; i++) {
                cout << "1 2" << endl;
                int ver, c;
                cin >> ver >> c;
            }
        } else {
            vector<int> v[2];
            for (int i = 1; i <= n; i++)
                v[col[i]].emplace_back(i);

            for (int i = 1; i <= n; i++) {
                int a, b;
                cin >> a >> b;
                if (a > b) swap(a, b);

                if (a == 1) {
                    if (v[0].size()) {
                        cout << v[0][0] << " " << a << endl;
                        v[0].erase(v[0].begin());
                    } else {
                        cout << v[1][0] << " " << b << endl;
                        v[1].erase(v[1].begin());
                    }
                } else {
                    if (v[1].size()) {
                        cout << v[1][0] << " " << b << endl;
                        v[1].erase(v[1].begin());
                    } else {
                        cout << v[0][0] << " " << a << endl;
                        v[0].erase(v[0].begin());
                    }
                }
            }
        }
    }
    return 0;
}
```

有无大佬解释一下为啥我用 `endl` 换行就能用 `fflush(stdout)` 就 ILE 啊。

---

## 作者：lfxxx (赞：0)

假若原图不是一个二分图，那么 Alice 就赢了，策略就每次只给两种固定的颜色就行，Bob 肯定无法染色，否则 Bob 绝对会赢，构造考虑对原图染色后每次先把包含 $1$ 的放入左部包含 $2$ 的放入右部直到一边放满，放满了还有按照原来的规则要放入这一边的就取另一个值（显然这个值应该是应当放入另一边的值或者 $3$）放入另一边，最后构造出来一边全是 $1$ 或者 $2$ 而另一边则全部是另一种数加上 $3$，符合 Bob 的胜利条件。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5+114;
int fa[maxn<<1];
int found(int u){
    return fa[u]=(fa[u]==u?u:found(fa[u]));
}
int n,m;
vector<int> E[maxn];
int col[maxn];
bool flag;
int vis[maxn];
queue<int> q1,q2;
void dfs(int u,int cl){
    if(cl==1) q1.push(u);
    else q2.push(u);
    vis[u]=1;
    for(int v:E[u]){
        if(vis[v]==0) dfs(v,cl^1);
    }
}
void work(){
    cin>>n>>m;
    for(int i=1;i<=n;i++) E[i].clear(),fa[2*i-1]=2*i-1,fa[2*i]=2*i,col[i]=0,vis[i]=0;
    flag=true;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        if(found(2*u)!=found(2*v-1)) fa[found(2*u)]=found(2*v-1);
        if(found(2*v)!=found(2*u-1)) fa[found(2*v)]=found(2*u-1);
        if(found(2*u)==found(2*u-1)||found(2*v)==found(2*v-1)) flag=false;
        E[u].push_back(v);
        E[v].push_back(u);
    }
    if(flag==false){
        cout<<"Alice"<<endl;
        for(int i=1;i<=n;i++){
            cout<<1<<' '<<2<<endl;
            int p,c;
            cin>>p>>c;
        }
    }else{
        dfs(1,1);
        cout<<"Bob"<<endl;
        for(int i=1;i<=n;i++){
            int a,b;
            cin>>a>>b;
            if((a==1||b==1)&&q1.size()>0){
                int u=q1.front();
                q1.pop();
                cout<<u<<' '<<1<<endl;
            }else{
                if((a==2||b==2)&&q2.size()>0){
                    int u=q2.front();
                    q2.pop();
                    cout<<u<<' '<<2<<endl;
                }else{
                    int u;
                    if(q1.size()==0) u=q2.front(),q2.pop();
                    else u=q1.front(),q1.pop();
                    cout<<u<<' '<<3<<endl;
                }
            }
        }
    }
}
int main(){
    int t;
    cin>>t;
    while(t--) work();
}
/*
4 4
1 2
2 3
3 4
4 1

2 3

1 2

2 1

3 1
*/
```

---

## 作者：_lmh_ (赞：0)

注意到如果有奇环，那么 Alice 只要一直输出 `1 2` 就能逼迫 Bob 在环上选出两个颜色相同的相邻点。

否则，将图黑白染色，黑为 1，白为 2。

考虑 Bob 的策略：Alice 给的两种颜色一定有至少一个不是三，不妨设它就是 1。

如果还有没染色的黑点就把它设为 1，否则，注意到黑点全部为 1，那么互不相邻的白点是 2 还是 3 没有本质区别，用另一种颜色染色即可。反之亦然。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll N=10007;
struct edge{ll to,nxt;}e[N<<1];
ll T,n,m,hd[N],nE,col[N],vis[N];
char ans;
void add(ll u,ll v){e[++nE]=(edge){v,hd[u]};hd[u]=nE;}
queue<ll> vec1,vec2;
void dfs(ll u,ll fa){
	vis[u]=1;col[u]=col[fa]^3;
	if (col[u]==1) vec1.push(u);
	else vec2.push(u);
//	cout<<"DYE "<<u<<' '<<col[u]<<endl;
	for (int v,i=hd[u];i;i=e[i].nxt){
		if (vis[v=e[i].to]){
			if (col[u]==col[v]) ans='A';
		}
		else dfs(v,u);
	}
}
void Alice(){
	cout<<"Alice"<<endl;
	for (int i=1,a,b;i<=n;++i){
		cout<<"1 2"<<endl;
		cin>>a>>b;
	}
}
void Bob(){
	cout<<"Bob"<<endl;
	for (int a,b,u,i=1;i<=n;++i){
		cin>>a>>b;
		if (a>b) swap(a,b);
		if (a==1){
			if (vec1.empty()){
				u=vec2.front();
				cout<<u<<' '<<b<<endl;
				vec2.pop();
			}
			else{
				u=vec1.front();
				cout<<u<<' '<<a<<endl;
				vec1.pop();
			}
		}
		else{
			if (vec2.empty()){
				u=vec1.front();
				cout<<u<<' '<<b<<endl;
				vec1.pop();
			}
			else{
				u=vec2.front();
				cout<<u<<' '<<a<<endl;
				vec2.pop();
			}
		}
	}
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>T;col[0]=2;
	while(T--){
		cin>>n>>m;
		while(m--){
			ll u,v;cin>>u>>v;
			add(u,v);add(v,u);
		}
		ans='B';
		dfs(1,0);
		if (ans=='A') Alice();
		else Bob();
		for (int i=1;i<=n;++i) hd[i]=col[i]=vis[i]=0;nE=0;
		while(!vec1.empty()) vec1.pop();
		while(!vec2.empty()) vec2.pop();
	}
	return 0;
}
```

---

