# [ABC296E] Transition Game

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc296/tasks/abc296_e

長さ $ N $ の数列 $ A=(A_1,A_2,\ldots,A_N) $ が与えられます。ここで、各 $ A_i $ $ (1\leq\ i\leq\ N) $ は $ 1\leq\ A_i\ \leq\ N $ をみたします。

高橋君と青木君が $ N $ 回ゲームを行います。$ i=1,2,\ldots,N $ 回目のゲームは次のようにして行われます。

1. 青木君が正整数 $ K_i $ を指定する。
2. 青木君の指定した $ K_i $ を聞いた後、高橋君は $ 1 $ 以上 $ N $ 以下の整数 $ S_i $ を選び、黒板に書く。
3. その後、 $ K_i $ 回次の操作を繰り返す。
  
  
  - 黒板に $ x $ が書かれているとき、それを消し、$ A_x $ を新しく書く。

$ K_i $ 回の操作の後で黒板に書かれている整数が $ i $ ならば $ i $ 回目のゲームは高橋君の勝ち、そうでないならば青木君の勝ちとなります。  
ここで、$ K_i,S_i $ は $ i=1,2,\ldots,N $ に対して独立に選ぶ事ができます。

両者が、自身が勝つために最善の行動をとったとき、$ N $ 回のゲームのうち高橋君が勝つ回数を求めてください。

## 说明/提示

### 制約

- $ 1\leq\ N\leq\ 2\times\ 10^5 $
- $ 1\leq\ A_i\leq\ N $
- 入力はすべて整数

### Sample Explanation 1

$ 1 $ 回目のゲームにおいて、青木君が $ K_1=2 $ を指定したとき、高橋君は $ S_1 $ として、$ 1,2,3 $ のいずれを選んでも勝つことはできません。 例えば、高橋君が最初に黒板に $ S_1=1 $ と書いたとすると、$ 2 $ 回の操作で黒板に書かれている数は順に $ 1\to\ 2(=A_1) $ 、$ 2\to\ 2(=A_2) $ と変化し、 最終的に黒板に書かれている数は $ 2(\neq\ 1) $ であるため、青木君の勝ちとなります。 一方、$ 2,3 $ 回目のゲームにおいては、青木君の指定した $ K_i $ の値によらず、高橋君はそれぞれ $ 2,3 $ を最初に黒板に書くことで勝つ事ができます。 よって、両者が、自分が勝つために最善の行動をとったとき、高橋君が勝つゲームは $ 2,3 $ 回目の $ 2 $ 回であるため、$ 2 $ を出力します。

### Sample Explanation 2

$ 1 $ 回目のゲームにおいて、高橋君は、青木君が指定した $ K_1 $ が奇数のときは $ 2 $、偶数のときは $ 1 $ を最初に黒板に書く事で勝つ事ができます。 同様に $ 2 $ 回目のゲームにおいても勝つ方法が存在するため、$ 1,2 $ 回目のゲームのいずれでも高橋君は勝利する事ができ、$ 2 $ が答えとなります。

## 样例 #1

### 输入

```
3
2 2 3```

### 输出

```
2```

## 样例 #2

### 输入

```
2
2 1```

### 输出

```
2```

# 题解

## 作者：fengqiao17 (赞：5)

### Problem

给定 $n$ 个数 $a_1,a_2,\cdots,a_n$，一共有 $n$ 轮游戏。

每轮游戏先手定一个数 $k$，后手定一个数 $s$ 并写在黑板上。一共有 $k$ 次操作，每一次操作可以将黑板上的数 $x$ 替换为 $a_x$。

如果第 $i$ 轮游戏 $i$ 被写在黑板上，后手获胜。求后手最多获胜多少轮。

### Solution

首先我们要明确题目中说的“最多能赢”是指**后手必定胜利的情况**，不是说他能够胜利，这一点比较坑人。

我们可以先假设现在的轮数 $i$ 点恰好在图中的某个环上，那么无论先手的 $k$ 选的是多少，我们都可以找到一个 $s$，让它在这个环中绕上几圈，使得在经过 $k$ 轮之后到点 $i$。

于是我们只需用判环即可，我的想法是用拓扑排序判环，只要看最后没有加入拓扑序的点是什么，那么这些点就一定在某个环上。

思路比较难想，需要好好回味一下。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
int a[N], cnt[N];
queue<int> q;
void kahn(int n)
{
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (cnt[i] == 0) {
            q.push(i); // 将入度为0的点加入队列
        }
    }
    while (!q.empty()) {
        int o = q.front(); // 删除该点
        q.pop();
        ans++;
        cnt[a[o]]--; // 它所指向的点入度减一
        if (cnt[a[o]] == 0) {
            q.push(a[o]); // 如果也入度为0那么进入队列
        }
    }
    return ans; // 返回拓扑序中的点数
}
int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        cnt[a[i]]++; // cnt[i]表示点i的入度是多少
    }
    cout << n - kahn(n); // 由于环上的点一定不在拓扑序里（入度不为0），直接输出数量即可。
    return 0;
}
```

---

## 作者：Register_int (赞：4)

建图，每个点出度都为 $1$，所以图是内向基环树森林。可以直接令 $K=114514^{1919^{810}}$，当点不在环上时必然不能找到对应点，所以只有环上的点满足要求。直接输出环的大小总和即可。

小寄巧：直接进行拓扑排序，由于每个点出度为 $1$，所以直接累加度数的结果就是环的总长度。

# AC 代码

```cpp
#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
const int MAXN = 2e5 + 10;
 
int n, a[MAXN], deg[MAXN], cnt;
 
inline 
void toposort() {
	queue<int> q; 
	for (int i = 1; i <= n; i++) if (!deg[i]) q.push(i);
	while (!q.empty()) {
		int u = q.front(); q.pop();
		if (!--deg[a[u]]) q.push(a[u]);
	}
}
 
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]), deg[a[i]]++;
	toposort();
	for (int i = 1; i <= n; i++) cnt += deg[i]; printf("%d", cnt);
}
```

---

## 作者：Neil_Qian (赞：4)

# [ABC296E] Transition Game 题解

## 题目描述

给出一个长度为 $n$ 的序列 $a_i$，对于每一个 $i$，甲给出 $k_i$，乙写一个 $s_i$，然后重复 $k_i$ 次：将写下的数设为 $x$，将其 $a_x$。若最后变成 $i$ 则乙胜利，反之甲胜利。若甲乙均以最优策略进行决策，那么乙能赢多少次？

## 突破口

很容易发现 $k_i$ 没有大小限制！也就是说，可以取一个极大值，甚至 $>n$，乙怎么才能胜利？

## 解决方案

我们先把题目的序列 $a_i$ 看成 $i\to a_i$ 的一张有向图，在这张有向图上移动即可。但起点无法确定，反而终点可以确定，建反图即可。问题变成从 $i$ 出发，问是否能走无限步。

显然，只有有环的时候才可以。只需要深搜判环，统计有多少个点参与到环中即可。建图是每个点只有一条入边，因此没有反例，只有形如 $1\to 2,2\to 3,\dots,n\to 1$ 会出现。

时间复杂度 $O(n)$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;const int N=2e5+2;
int n,a,cnt,ans;vector<int> v[N];bool vis[N];
//cnt:当前dfs的结点数量
//ans:答案
//v:存图
//vis:是否访问过
inline void dfs(int x,int s){//深搜判环
	vis[x]=1,cnt++;
	for(int t:v[x]){
		if(t==s)ans+=cnt;
		else dfs(t,s);
	}
	cnt--;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a),v[a].push_back(i);//建反图
	for(int i=1;i<=n;i++)if(!vis[i])dfs(i,i);//不一定联通
	return printf("%d\n",ans),0;
}
```

---

## 作者：FL_sleake (赞：4)

## 解题思路

**两个人都用最优策略时，第一个人将 $K_i$ 选择地很大时显然会让第二个人更难赢。**

**首先考虑环的情况**

在 $K_i$ 很大的情况下，我们可以在环中选择一个点，而后在环中不停**转圈**走到另一个点。由于起点自由选择，所以环中每个点都可以到达。因而环中的每个点都是必胜点。

**其次考虑一个点不在环中**

如果这个点可以通过环中的某个点达到，就同环中的情况类似，只是最后几步**走出**这个环，所以这个点也是必胜点。如果这个点通向一个环，显然没有任何用处，它并不是必胜点。

**结论**

环中的点和被环连接的点都是必胜点，其余点都是必败点。

## 如何实现

**类似于拓扑排序。** 环中的每个点入度都不可能变为 $0$ ，同理环所连接的点入度也不可能为 $0$  。

## 代码示例

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[200010],du[200010],ans=0;
queue<int> q;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i],du[a[i]]++;
	for(int i=1;i<=n;i++) if(du[i]==0) q.push(i);
	while(!q.empty()){//算出不在环中且不被环连接的点的数量
		int o=q.front();
		q.pop();
		ans++;
		du[a[o]]--;
		if(du[a[o]]==0) q.push(a[o]);
	}
	cout<<n-ans<<endl;//求的是必胜点的数量
	return 0;
}
```
~~不知道讲的清不清楚~~

---

## 作者：chlchl (赞：3)

## 题意简述
给定 $n$ 个数 $A=(A_1,A_2,\cdots,A_n)$（$1\leq A_i\leq n$），一共有 $n$ 轮游戏。

每一轮，先手选定 $k$，表示将要进行 $k$ 次操作。

后手选定一个数 $s(1\leq s\leq n)$，写在黑板上。一共进行 $k$ 次操作，设黑板上现在的数是 $x$，则每次操作都用 $a_x$ 替换成 $x$。

若第 $i$ 轮游戏后 $i$ 被写在黑板上，后手获胜，否则先手获胜。

问后手最多能赢多少轮。

## Solution
简单博弈论 + 图论。

主动权在先手手中。后手想要获胜，则必须满足无论先手规定玩多少次，后手都能选定一个 $s$ 使得最后能出现 $i$。

这启发我们往“环”上想。考虑对于 $i\rightarrow A_i$ 建出有向边，则整个图就是 $n$ 点 $n$ 边的基环树森林。

为什么是森林呢？**因为有可能出现自环**！

那么接下来很显然，我们只要找到在环上的所有点即可。

你可以用 dfs，用 Tarjan，用啥都行。我用的是拓扑排序（受大佬启发）。

考虑这么一个性质：拓扑排序用在 DAG 上。它的要求是入度为 $0$ 时才将节点入队。在环上的点，每个点都的出度入度都恰好为 $1$，所以永远不可能入队。

所以如果我们对每个图都跑一次拓扑排序，那么最后还有入度的点必定是在环上的点，统计即可。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10;
int n, ans, in[N], out[N];
int id, head[N], to[N << 1], nxt[N << 1];

void add(int u, int v){
	to[++id] = v;
	nxt[id] = head[u], head[u] = id;
}

void toposort(){
	queue<int> q;
	for(int i=1;i<=n;i++)
		if(!in[i])
			q.push(i);
	while(!q.empty()){
		int u = q.front();
		q.pop();
		for(int i=head[u];i;i=nxt[i]){
			int v = to[i];
			in[v]--;
			if(!in[v])
				q.push(v);
		}
	}
}

int main(){
	scanf("%d", &n);
	for(int i=1,x;i<=n;i++){
		scanf("%d", &x);
		add(i, x);
		in[x]++, out[i]++;
	}
	toposort();
	for(int i=1;i<=n;i++)
		if(in[i])//拓扑排序适用于有向无环图，拓扑完后如果不在环上，入度应该全部被删除 
			++ans;//如果还有入度证明存在环 
	printf("%d\n", ans);
	return 0;
}
```



---

## 作者：Zheng_iii (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc296_e)

## 思路
我们可以在环中任选一点，然后在环内可以转到另一个点。因为起点自由选择，所以环中每个点都可以到达，由此我们可以得知环上的所有点都是必胜点。

我们把这个问题抽象为一张图，用拓扑排序判环即可。

## AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 2e5 + 10;
int n,a[N],ind[N],ans;queue<int> q; 

void ts(){//拓扑排序
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		if (!--ind[a[u]]){
			q.push(a[u]);
		} 
	}
}

int main(){
	ios::sync_with_stdio(0),cout.tie(0),cin.tie(0);
	cin>>n;
	for (int i = 1; i <= n; i++)cin>>a[i],ind[a[i]]++;
	for (int i = 1; i <= n; i++)if (!ind[i])q.push(i);
	ts();
	for (int i = 1; i <= n; i++)ans += ind[i];
	cout<<ans;
	return 0;
}
```

---

## 作者：cwd2023 (赞：1)

# AT_abc_296_e题解 :
#### by  _cwd2023_ 


---

#### update 2024.10.27:
感谢管理员指正题解中的格式错误，已修改。

---

#### 前置知识：拓扑排序

不会的看这里->[link](https://blog.csdn.net/Happy2019_/article/details/130796610)。

---

### 题目大意：
有n轮游戏，每次先手选定 $k$（操作 $k$ 次），后手选定 $s$（初始写在黑板上的数字）。之后进行 $k$ 次操作，每次将黑板上的数 $x$ 替换为 $a[x]$。

若第 $i$ 轮时黑板上是数字 $i$，则后手胜。否则先手胜。问后手最多能赢多少轮（注意，这里指的是**一定赢**）。


### 思路：
我们可以把这个问题想象为一张图，每个 $x$ 指向 $a[x]$，那么似乎有一些元素可以构成一个环。

例如：
-  $n=5$
-  $a$ 数组：$2$ $4$ $3$ $5$ $1$
-  $s=1$

则: $1$  ->  $2$  -> $4$  ->  $5$  ->  $1$ 构成了一个环。

我们贪心地想：只要后手选择了一个环中的元素，那么只要 $k$ 足够的大，那么先手一定赢。

而题目中并没有限制 $k$ 的大小，所以结论转化为：
### 若后手选择环上的点或连接环的点，先手赢。
所以，我们知道了先手必胜的场数，那么后手必胜的场数为：
**$n$ 减去前者，即 $n$ 减去所有环长度之和**。


---

#### 如何求环？

方法很多，推荐拓扑排序，简单好写。


---

## code:
#### 详细注释版：


```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,ans;
ll a[200010],in[200010];//a是题目中的数组，in记录入度
queue<ll>q;//拓扑所用到的队列
int main(){
	ios::sync_with_stdio(0);
	cout.tie(0)，cin.tie(0);//输入输出加速
	cin>>n;
	for(ll i=1;i<=n;i++)cin>>a[i],in[a[i]]++;
                      //i指向a[i],增加a[i]的入度
	for(ll i=1;i<=n;i++)if(!in[i])q.push(i);
                      //压入入度为0的点
	while(q.size()){
		ll u=q.front();
		q.pop(),ans++;//ans统计答案
		if(!--in[a[u]])q.push(a[u]);
    //删除u所连接的边，压入入度为0的点
	}
	cout<<n-ans<<"\n";//n减去前者
	return 0;
}
```

#### 无注释版：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,ans;
ll a[200010],in[200010];
queue<ll>q;
int main(){
	ios::sync_with_stdio(0);
	cout.tie(0),cin.tie(0);
	cin>>n;
	for(ll i=1;i<=n;i++)cin>>a[i],in[a[i]]++;
	for(ll i=1;i<=n;i++)if(!in[i])q.push(i);
	while(q.size()){
		ll u=q.front();
		q.pop(),ans++;
		if(!--in[a[u]])q.push(a[u]);
	}
	cout<<n-ans<<"\n";
	return 0;
}
```

最后，希望我的题解对大家有所帮助，感谢观看。

#### 望管理员通过。

---

## 作者：Fire_flame (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc296_e)

## $\mathbf{Solution}$

显然如果节点 $i$ 不在环上，那么令 $K=\infty$，往前走 $K$ 步得到的结果一定不是 $i$。

而如果节点 $i$ 在环上，后手只需要适当的选一个初始节点 $j$ 就可以了，对于任意的 $K$ 都适用。

所以只需要统计有多少个节点在环上即可，题解采用的是缩点。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int read(){
    int s = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-')f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){s = s * 10 + (ch - '0');ch = getchar();}
    return s * f;
}
const int MAXN = 1e6 + 5,MR = 1e6 + 5;
struct edge{
    int from, to, nxt;
}e[MR];
int head[MAXN], cnt;
void add_edge(int u,int v){
    e[++ cnt] = {u, v, head[u]};
    head[u] = cnt;
}
int n, m, ans, a[MAXN], c[MAXN], fa[MAXN], dep[MAXN], vis[MAXN];
int find(int u){
    if(fa[u] == u)return u;
    return fa[u] = find(fa[u]);
}
void dfs(int x){
    for(int i = head[x];i;i = e[i].nxt){
        int v = e[i].to;
        if(!dep[v]){ 
            dep[v] = dep[x] + 1;
            dfs(v);
        }
        if(dep[find(v)] > 0){
            if(dep[find(x)] < dep[fa[v]])fa[fa[v]] = fa[x];
            else fa[fa[x]] = fa[v];
        }
    }
    dep[x] = -1;
}
void calc(int x){
    int mx = 0;
    dep[x] = 0;
    for(int i = head[x];i;i = e[i].nxt){
        int v = e[i].to;
        if(dep[v])calc(v);
        if(c[v] > c[mx])mx = v;
    }
    c[x] += c[mx];
}
void dfs2(int x, int last){
	if(last)add_edge(last, x);
	if(vis[x])return ;
	vis[x] = 1;
	dfs2(a[x], x);
}
int main(){
    n = read();
    for(int i = 1;i <= n;i ++)a[i] = read();
    for(int i = 1;i <= n;i ++){
		if(!vis[i])dfs2(i, 0);
	}
    for(int i = 1;i <= n;i ++)fa[i] = i;
    for(int i = 1;i <= n;i ++){
        if(dep[i])continue;
        dep[i] = 1;
        dfs(i);
    }
    for(int i = 1;i <= n;i ++)c[find(i)] ++;
    for(int i = 1;i <= n;i ++){
		if(c[find(i)] != 1 || a[i] == i)ans ++;
	}
	printf("%d", ans);
    return 0;
}
```


---

## 作者：Melo_DDD (赞：0)

含糊的题面困扰了我 $1$ 小时。

# 题目大意

本人经过深入研究，在此提出对题面的两点理解：

- 题目中的“后手最多能赢”指的是后手必胜的情况（两人都是最优策略）。

- 第  $i$ 轮游戏分为 $k$ 次，也就是说后手“最多赢多少轮”是指通过写下不同的 $s$ 一共能赢多少次。

这就解决了本人的一个问题：在一轮次中如何保证同时满足所有可行方案？其实不需要，因为每次满足一个就行。（不知道其他人有没有这个问题）

# 题目实现

根据题意，显然可以从 $x$ 向 $a_x$ 连一条有向边，那么如果后手可以胜利（帮助他胜利的这个数我们称之为 $m$），那么 $m$ 一定在一个环上（或者在一个环连接的一条链或者什么上），这样可以保证**从任意点出发**经过**任意步数**到达这个点。

判环可以用拓扑，注意无论在环上还是链上或者什么上入度一定不为零，而拓扑的入队条件是入度为零，只要记录入队个数将它减去即可。

或者还可以用缩点实现？

卡常小寄巧：快读，没有快写。

## 代码

```cpp
#include <bits/stdc++.h>
#define f(i ,m ,n ,x) for (int i = (m) ;i <= (n) ;i += (x))
using namespace std ; 
const int N = 2e5 + 7 ;
int n ,head[N << 1] ,tot ,in[N] ,a[N] ,ans ;
struct edge {
	int to ,nxt ;
} e[N << 1] ;
template <typename T> inline void read (T &x) {
	x = 0 ;
	bool flag (0) ;
	register char ch = getchar () ;
	while (! isdigit (ch)) {
		flag = ch == '-' ;
		ch = getchar () ;
	}
	while (isdigit (ch)) {
		x = (x << 1) + (x << 3) + (ch ^ 48) ;
		ch = getchar () ;
	}
	flag ? x = -x : 0 ;
}
namespace shin {
	inline void add (int u ,int v) {
		e[++ tot].nxt = head[u] ;
		head[u] = tot ;
		e[tot].to = v ;
		in[v] ++ ;
	}
	inline void topo () {
		queue <int> q ;
		f (i ,1 ,n ,1) {
			if (in[i] == 0) {
				q.push (i) ;
				ans ++ ;
			}
		} 
		while (! q.empty ()) {
			int now = q.front () ;
			q.pop () ;
			for (int i = head[now] ;i ;i = e[i].nxt) {
				int nex = e[i].to ;
				if (-- in[nex] == 0) {
					q.push (nex) ;
					ans ++ ;
				}
 			}
		}
	}
}
int main () {
	read (n) ;
	f (i ,1 ,n ,1) {
		read (a[i]) ;
		shin :: add (i ,a[i]) ;
	}
	shin :: topo () ;
	cout << n - ans << '\n' ;
	return 0 ;
}
```

---

## 作者：Penguin_Chen (赞：0)

## 题意
	
    
给定一个大小为 $n$ 的数组 $A$，一共有 $n$ 轮，每轮操作 $k$ 次，选定一个数字 $x$，每次操作都将 $x$ 替换为 $a_x$，问有几轮最后的数字等于当前轮数。

## 思路


首先，我们易知当 $a_i$ 等于 $i$ 时，无论 $k$ 等于**任何数**，最后剩下的数都等于 $i$。再通过观察，我们可以发现，可以将 $a_i$ 通过操作关系可将其与其他点连接： $i->a_i$（注意，是有向边），如果到最后将 $a_i$ 连成了一个**环**（不一定是所有的 $a_i$），则当前 $i$ 如果处于环上，高桥都必赢（这个可以自己思考一下，很简单），但如果是**连接到了其他的环上并且不属于这个环**就不是必赢了，不计入答案。

## Code
~~别问我为什么用 DFS，问就是不会 tarjan，也不会基环树。~~

码风有点奇怪，将就着看吧。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+1;
struct node
{
	int l,r;
}huan[maxn];
int n,ans;
bool s;
int f[maxn];
int flag[maxn];
int a[maxn],cnt;
inline void dfs(int l,int r)
{
	if(l==r)//如果已经成环 
	{
		flag[l]=1;//标记 
		s=1;//标记已成环  
		return;//返回 
	}
	dfs(a[l],r);//没成环就继续向下搜  
	if(s==1)//标记为1，说明已成环 
	{
		flag[l]=1;
		return;//标记后直接返回 
	}
	return;
}
inline int find(int x){return (f[x]==x?x:f[x]=find(f[x]));}//并查集路径压缩 
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("2.out","w",stdout);
	std::ios::sync_with_stdio(false);
	cin>>n;
	for(int i=1;i<=n;++i)f[i]=i;
	for(int i=1;i<=n;++i)
	{
		cin>>a[i];
		int fu=find(i),fv=find(a[i]);
		if(fu==fv)//如果已经连通过了 
		{
			huan[++cnt].l=a[i];//注意l为a[i],r为i 
			huan[cnt].r=i;//这是一个有向图，已经联通的话，判环的方向只能是 a[i]->i ,而不是 i->a[i] 
		}//一开始因为这个 WA了几次 
		else f[fv]=fu;//合并 
	}
	for(int i=1;i<=cnt;++i)
	{
		s=0; 
		dfs(huan[i].l,huan[i].r);//dfs判是否为环 
	}
	for(int i=1;i<=n;++i)
		ans+=flag[i];//统计数组中处于环上的点的个数 
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：Symbolize (赞：0)

# $\tt{Solution}$
首先我们可以发现，不管进行多少次操作，对应关系只有 $n$ 种，所以只要 $k$ 足够大，一定能找到若干个环，所以只需要将对应关系转化为边，形成一个图，然后跑一遍拓扑排序，没有进入拓扑序的就是在环上的点。这里因为是跑拓扑排序，所以只需要记录度数即可。

```cpp
/*
	Luogu name: Symbolize
	Luogu uid: 672793
*/
#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define x first
#define y second
#define rep1(i,l,r) for(register int i=l;i<=r;++i)
#define rep2(i,l,r) for(register int i=l;i>=r;--i)
#define rep3(i,x,y,z) for(register int i=x[y];~i;i=z[i])
#define rep4(i,x) for(register auto i:x)
#define debug() puts("----------")
const int N=2e5+10;
const int inf=0x3f3f3f3f3f3f3f3f;
const double pi=acos(-1);
using namespace std;
typedef complex<double> cp;
int n,a[N],times[N],ans;
inline int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return f*x;
}
void Top()
{
	queue<int> q;
	rep1(i,1,n) if(!times[i]) q.push(i);
	while(!q.empty())
	{
		int x=q.front();
		q.pop();
		++ans;
		--times[a[x]];
		if(!times[a[x]]) q.push(a[x]);
	}
	return;
}
signed main()
{
//	#ifndef ONLINE_JUDGE
//		freopen(".in","r",stdin);
//		freopen(".out","w",stdout);
//	#endif
	n=read();
	rep1(i,1,n)	++times[a[i]=read()];
	Top();
	cout<<n-ans<<endl;
	return 0;
}

```

---

