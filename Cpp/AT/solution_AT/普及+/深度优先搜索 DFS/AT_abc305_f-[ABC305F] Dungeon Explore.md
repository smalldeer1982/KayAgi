# [ABC305F] Dungeon Explore

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc305/tasks/abc305_f

この問題は **インタラクティブな問題**（あなたが作成したプログラムとジャッジプログラムが標準入出力を介して対話を行う形式の問題）です。

$ N $ 個の頂点と $ M $ 本の辺からなる連結かつ単純な無向グラフがあります。 頂点には $ 1 $ から $ N $ までの整数の番号がついています。

あなたは、はじめ頂点 $ 1 $ にいます。 隣り合う頂点に移動することを最大 $ 2N $ 回まで繰り返して、頂点 $ N $ へ移動してください。

ただし、はじめはグラフの辺をすべて知ることはできず、今いる頂点と隣り合っている頂点の情報を知ることができます。

### Input &amp; Output Format

最初に、グラフの頂点数 $ N $ と辺数 $ M $ を標準入力から受け取ってください。

> $ N $ $ M $

次に、あなたはジャッジに対して問題文中の操作を $ 2N $ 回まで繰り返すことができます。

各操作のはじめには、あなたが現在いる頂点に隣接する頂点が次の形式で標準入力から与えられます。

> $ k $ $ v\ _\ 1 $ $ v\ _\ 2 $ $ \ldots $ $ v\ _\ k $

ここで、$ v\ _\ i\ (1\leq\ i\leq\ k) $ は $ 1 $ 以上 $ N $ 以下の整数で、$ v\ _\ 1\lt\ v\ _\ 2\lt\cdots\lt\ v\ _\ k $ を満たします。

あなたは、$ v\ _\ i\ (1\leq\ i\leq\ k) $ を $ 1 $ つ選んで以下の形式で標準出力へ出力してください。

> $ v\ _\ i $

この操作をすることで、あなたは頂点 $ v\ _\ i $ へ移動します。

移動回数が $ 2N $ 回を上回ったり、不正な出力を行った場合、ジャッジは標準入力に `-1` を送ります。

移動する先の頂点が頂点 $ N $ である場合、ジャッジは標準入力に `OK` を送り、終了します。

`-1` もしくは `OK` を受け取った場合、ただちにあなたのプログラムを終了させてください。

## 说明/提示

### 制約

- $ 2\leq\ N\leq100 $
- $ N-1\leq\ M\leq\dfrac{N(N-1)}2 $
- グラフは連結かつ単純
- 入力はすべて整数
 
### 注意点

- **出力を行うたびに、末尾に改行を入れて標準出力を flush してください。そうしなかった場合、ジャッジ結果が TLE となる可能性があります。**
- **対話の途中で不正な出力を行った、あるいはプログラムが途中で終了した場合のジャッジ結果は不定です。**
- 頂点 $ N $ に到達したらただちにプログラムを終了してください。そうしない場合、ジャッジ結果は不定です。
- **この問題のジャッジはアダプティブです。つまり、制約および以前の出力に矛盾しない範囲でグラフの形が変わる場合があります。**
 
### 入出力例

以下は、$ N=4,M=5 $ の場合の入出力例です。 この入出力では、グラフは以下の図のようになっています。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_abc305_f/c0782babede862d29b96c59cb832ffd123590408.png)

    入力 出力 説明     `4 5`  $ N $ と $ M $ が与えられます。   `2 2 3`  はじめ、あなたは頂点 $ 1 $ にいます。頂点 $ 1 $ に隣接している頂点が与えられます。    `3` 移動する頂点として、頂点 $ v\ _\ 2=3 $ を選びます。    `3 1 2 4`  頂点 $ 3 $ に隣接している頂点が与えられます。    `2` 移動する頂点として、頂点 $ v\ _\ 2=2 $ を選びます。    `3 1 3 4`  頂点 $ 2 $ に隣接している頂点が与えられます。    `4` 移動する頂点として、頂点 $ v\ _\ 3=4 $ を選びます。    `OK`  $ 8(=2\times4) $ 回以内で頂点 $ 4 $ に到達したので、`OK` が渡されます。   `OK` を受け取ったあと、ただちにプログラムを終了することで正解と判定されます。

# 题解

## 作者：CaiZi (赞：4)

## [ABC305F] Dungeon Explore 题解
**[题目链接](https://www.luogu.com.cn/problem/AT_abc305_f)**
### 题目分析
考虑直接 DFS，记录下每个点来之前的点，若走不通则回溯，回溯的时候也要进行询问，这样才能走回之前的点。

因为每个点会被经过和回溯各 $1$ 次，所以询问数最大是 $2N$，本题 $M$ 是没用的。
### 代码展示
代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k;
bool p[501];
inline bool dfs(int u,int v){
	if(u==n){
		return true;
	}
	int w[501];
	cin>>k;
	for(int i=1;i<=k;i++){
		cin>>w[i];
	}
	for(int i=1;i<=k;i++){
		if(!p[w[i]]){
			cout<<w[i]<<endl;
			p[w[i]]=true;
			if(dfs(w[i],u)){
				return true;
			}
		}
	}
	cout<<v<<endl;
	cin>>k;
	for(int i=1;i<=k;i++){
		cin>>w[i];
	}
	return false;
}
signed main(){
	cin.tie(nullptr)->sync_with_stdio(false);
	cin>>n>>m;
	p[1]=true;
	dfs(1,0);
	return 0;
}
```
**[提交记录](https://www.luogu.com.cn/record/163658691)**

---

## 作者：Flanksy (赞：3)

### 模拟

------------

#### 题意

给出一个 $n$ 个节点，$m$ 条边的图，刚开始你在 $1$ 号节点。在节点 $u$ 时测评系统会给出 $u$ 的所有相邻节点，选择其中一个节点移动到那里。

至多移动 $2n$ 次，到达节点 $n$。

------------

#### 解法

考虑图的深度优先遍历。完整遍历一张图时，一定进入了每个节点恰好一次。同时，除了每次遍历的第一个节点外，一定会从每个节点返回上一个节点一次。所以模拟深度优先遍历，在 $2n$ 次移动之内必然可以遍历整张图，到达节点 $n$。

每次优先向未访问过的节点移动，如果某个节点的相邻节点都被访问过则返回上一个节点，记录每个节点的上一节点模拟即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k,pos,path[105];
vector<int> v[105];
bool on[105];
void explore(int x){
	printf("%d\n",x);
	fflush(stdout);
	if(x==n) exit(0);
}
void read(int x){
	scanf("%d",&k);
	on[x]=1,v[x].resize(k);
	for(int &i:v[x]) scanf("%d",&i);
	for(int i:v[x]) if(!on[i])
		return path[pos=i]=x,void();
	pos=path[x];
}
int main(){
	scanf("%d%d",&n,&m);
	pos=1;
	while(1) read(pos),explore(pos);
	return 0;
}
```


---

## 作者：luogu_gza (赞：2)

直接当做 `dfs` 做。

然后就完了，记得回溯的时候也要前往点，需要一个栈来辅助记录。

交互题，所以记得用 `cout` 和 `endl`，或者 `fflush`。

细节见代码的注释：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define MT int TTT=R;while(TTT--)
#define pc putchar
#define R read()
#define fo(i,a,b) for(register int i=a;i<=b;i++)
#define rep(i,a,b) for(register int i=a;i>=b;i--)
#define m1(a,b) memset(a,b,sizeof a)
int read()
{
    int x=0;
    char ch=getchar();
    bool f=0;
    while(!isdigit(ch)){if(ch=='-') f=1;ch=getchar();}
    while(isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    if(f) x=-x;
    return x;                                       
}
template<typename T> inline void write(T x)
{
    if(x<0)
    {
        pc('-');
        x=-x;
    }
    if(x>9) write(x/10);
    pc(x%10+'0');
}
const int N=110,M=N*N;
int n,m;
bool st[N];//是否遍历
int stk[N],cnt;//栈
vector<int> g[N];//vector存图
void dfs(int u)
{
    if(u==n) exit(0);//搜到了就好了
    st[u]=1;//标记
    int k,tt;
    cin>>k;
    fo(i,1,k)
    {
        cin>>tt;
        g[u].push_back(tt);//顺便把图建出来
    }
    for(auto i:g[u]) 
    {
        if(!st[i])
        {
            cout<<i<<endl;//需要前往的点
            stk[++cnt]=u;
            dfs(i);
            cnt--;//记得弹出栈
        }
    }
    cout<<stk[cnt--]<<endl;//记得弹出
    dfs(stk[cnt+1]);
}
signed main(){
    cin>>n>>m;
    dfs(1);
}
```

---

## 作者：lbh666 (赞：1)

### 思路分析

考虑模拟 `dfs` 的过程。

- 记下每个点是从哪个点搜索过来的，方便回溯时用。

- 每次优先向未访问的节点访问，若都访问过或访问不到 $n$，考虑回溯。

- 每个点最坏情况下只会被遍历和回溯各 $1$ 次，所以总访问次数不会超过 $2N$。

### 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
#define rep(i,l,r) for(int i=l;i<=r;++i)
using namespace std;

const int N=105;
int n,m,k;
bool vis[N];
vector<int> e[N];

void dfs(int x,int fa){//fa用来记录这个节点是哪一个节点搜索过来的 
	if(x==n)exit(0);
	cin>>k;
	rep(i,1,k){
		int v;
		cin>>v;
		e[x].push_back(v);//vector存图 
	}
	for(auto y:e[x]){
		if(!vis[y]){//优先访问未访问过的节点 
			cout<<y<<"\n";
			vis[y]=1; 
			dfs(y,x);
		}
	}
	cout<<fa<<"\n";//回溯 
	cin>>k;
	rep(i,1,k){//需要再询问一次才能走回去 
		int v;
		cin>>v;
	}
}

int main(){
	cin>>n>>m;
	vis[1]=1;
	dfs(1,0);
	return 0;
}
```

---

## 作者：mysterys (赞：1)

# 思路
-  简单小结论：由于是无向联通图，所以每个点都遍历一遍，操作次数一定在 $2N$ 内，所以本题不用判 ```-1```。
- 直接 ```dfs```，注意要回溯。
- 本题是交互题，注意格式。
# $Code$
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
int n,m;
vector<int>v[105];
stack<int>q; 
bool vis[105];
int k;
inline void dfs(int u,int l){
	if(u==n) exit(0);
	vis[u]=1;
	cin>>k;
	for(int i=1;i<=k;i++){
		int to;
		cin>>to;
		v[u].push_back(to);
	}
	for(int i:v[u]){
		if(vis[i]) continue;
		vis[i]=1;
		cout<<i<<endl;
		dfs(i,u);
	}
	cout<<l<<endl;
	cin>>k;
	for(int i=1;i<=k;i++){
		int to;
		cin>>to;
	}
}
signed main(){
	cin>>n>>m;
	dfs(1,0);
	return 0;
}
```

---

## 作者：Lan_yan (赞：0)

### 思考

不会像楼下的大佬用 BFS，只能 DFS 了。 

从起点开始深搜，遇到死路就回溯，那么每个点最多会被遍历两次，一次探路，另一次回头。

从而保证最多只会有 $2 \times n$ 次搜索，符合题意。

### 代码

说实话细节挺多，回溯的方法大家各有千秋，动态数组，静态数组，还有无限循环，蒟蒻不会，只能套在函数里面了。

一定不要把 $k$ 定义成局部变量！

```cpp
#include<bits/stdc++.h>
using namespace std;
int c[505],n,m,k;
void dfs(int x,int last)
{
	if(x==n)exit(0);
	c[x]=1;
	int i,way[505];
	cin>>k;
	for(i=1;i<=k;i++)cin>>way[i];
	for(i=1;i<=k;i++)
	{
		if(c[way[i]]!=1)
		{
			cout<<way[i]<<endl;
			dfs(way[i],x);
		}
	}
	cout<<last<<endl;
	cin>>k;
	for(i=1;i<=k;i++)cin>>way[i];
}
int main()
{
	cin>>n>>m;
	dfs(1,0);
}
```

---

## 作者：2022linzhiyi (赞：0)

## 题目大意
这是一道交互题。

给定一个 $n$ 个点，$m$ 条边的无向连通图，每走到一个点就会给出与它相连的点，要求在 $2n$ 步之内到达点 $n$。
## 解法
考虑深搜，每次只需要标记走过的点，不重复即可，直到搜到点 $n$。

设与一个点相邻的点数为 $k$，那么从这个点出发会往下走最多 $k$ 个点，同时这 $k$ 个点最坏情况下会回溯 $k$ 次，因此走 $2n$ 次一定能走到 $n$ 点，不会出现无解情况。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
bool vis[110];
vector<int> vec[110];
void dfs(int x) {
	if (x == n) {
		string str;
		cin >> str;
		exit(0);
	}
	int k;
	cin >> k;
	for (int i=1;i<=k;i++) {
		int p;
		cin >> p;
		vec[x].push_back(p);
	}
	for (int i=0;i<k;i++) {
		if (!vis[vec[x][i]]) {
			vis[vec[x][i]]=1,cout << vec[x][i] << endl,dfs(vec[x][i]);
			cout << x << endl;
			int t;
			cin >> t;
			for (int j=0;j<t;j++) {
				int p;
				cin >> p;
				vec[x].push_back(p);
			}
		}
	}
}
int main() {
	cin >> n >> m;
	vis[1]=1; dfs(1);
	return 0;
}

```

---

## 作者：lmy_2011 (赞：0)

在题目中，第一次操作你哪里都不连通，此时我们可以假设两个点 $a$ 与 $b$ 之间含有一条有向边，则构造了一张有向完全图。

之后我们将每条边的边权默认为 $1$，并维护一个集合使边权最小，从点 $x$ 开始最短路径算法，这里我会用弗洛伊德算法（$\tt Floyd$）配合拓扑排序（$\tt topo-sort$）来做。

我们先用拓扑找到当前图的拓扑序中的第 $1$ 个点，也就是入度为 $0$ 的点，将它指向的点均设为 $x$ 点，来进行最短路算法，**单次**时间复杂度 $\mathrm{O(m)}$。

接下来还有一个注意事项，既然你要求不超过 $2\cdot n$ 次操作，其实相当于暗示我们没有存在不合法的情况，即不需要输出 $-1$。

最短路：
```cpp
for(int k = 1; k <= n; k ++)
   for (int i = 1; i <= n; i ++ )
       for (int j = 1; j <= n; j ++ )
           d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
```

拓扑排序维护环：
```cpp
queue<int>q;
for(int i=1;i<=n;i++)
	if(!in[i]) 
       	q.push(i);	 
while(q.size()){
	int x=q.front();
       q.pop();
	sum++;
	for(unsigned int i=0;i<v[x].size();i++)
       {
		in[v[x][i]]--;
		if(in[v[x][i]]==0) q.push(v[x][i]); 
	}
} 
return sum==n;
```



---

## 作者：cosf (赞：0)

## [ABC305F](https://atcoder.jp/contests/abc305/tasks/abc305_f) [探索地牢](https://www.luogu.com.cn/problem/AT_abc305_f)

### 前言

看到大家都用 `dfs`，那我就发一篇 `bfs` 的吧。

### 思路

在我的思路当中，题面中的 $m$ 没有任何作用。

在最开始时（第一次操作前），我们什么信息都不知道，所以可以假设每两个点之间都有一条边，即完全图。然后对于每一次询问，我们更新边集然后从点 $N$ 跑最短路。因为这个图的边权都为 $1$，没有负环，所以可以直接 `bfs`（拓扑也可以）。然后就直接走到当前节点到 $N$ 最短路中的下一个点就行了。

单次时间复杂度为 $O(m)$。

### AC 代码

```cpp
#include <iostream>
#include <cstring>
#include <queue>
#include <set>
using namespace std;

#define MAXN 105

set<int> to[MAXN]; // 边集
int dis[MAXN];
int from[MAXN];

int n;

void bfs() // bfs 版最短路
{
    memset(dis, 0x3f, sizeof(dis));
    memset(from, 0, sizeof(from));
    dis[n] = 0;
    queue<int> que;
    que.push(n);
    while (!que.empty())
    {
        int c = que.front();
        que.pop();
        for (int t : to[c])
        {
            if (dis[t] > dis[c] + 1)
            {
                dis[t] = dis[c] + 1;
                from[t] = c;
                que.push(t);
            }
        }
    }
}

int main()
{
    cin >> n;
    int m;
    cin >> m;
    for (int i = 1; i <= n; i++) // 完全图
    {
        for (int j = 1; j <= n; j++)
        {
            if (i != j)
            {
                to[i].insert(j);
            }
        }
    }
    int at = 1;
    int cnt = 0;
    while (at != n)
    {
        cnt++;
        to[at].clear(); // 更新边集
        int k;
        cin >> k;
        for (int i = 1; i <= k; i++)
        {
            int v;
            cin >> v;
            to[at].insert(v);
        }
        for (int i = 1; i <= n; i++)
        {
            if (!to[at].count(i))
            {
                to[i].erase(at);
            }
        }
        bfs();
        at = from[at];
        cout << at << endl;
    }
    return cnt > 2 * n; // 事实上，这个永远为 0（否则过不了）
}

```

---

注：该做法在稀疏图中复杂度特别低。


---

## 作者：CQ_Bob (赞：0)

## 分析

一道无脑交互题。

对于一张联通的图，我们能够走到的点最多就是这张图中点的数量。针对这道题，我们可以考虑尝试走完所有能走的点，因为我们是不知道完整的图的。如果我们把每一个能走的点都走一遍，那么最大的步数是一定不大于 $2 \times n$ 的，因为在某个点不能再走时（或者和它相连的点都走过时）我们在没走完所有点的情况下都会退回到某一个已经走到过的点。这种情况那个不能走再走的点所经过的次数就只有 $1$，返回的那个点的经过次数就会加 $1$，等价于每个点经过 $2$ 次。根据这个贪心，我们将所有能走的点都去尝试一遍，看看尝试的过程中是否能到 $n$ 即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m;
const int N=1e3+10;
int k,x;
int f[N][N];
//用来存边,f[i][j]表示测评姬返回的第i个点连接的第j条边的内容 
int last;
//当前所在的节点编号 
bool vis[N];
//判断某个点是否走过 
int fa[N];
//fa[i]表示i是通过与fa[i]相连的边走过来的，方便返回 
signed main(){
	cin>>n>>m>>k;
	for(int i=1;i<=k;i++){
		cin>>x;
		f[1][i]=x;
	}
	for(int i=1;i<=k;i++){
		if(!vis[f[1][i]]){//找到一个没走过的点就去尝试，反正都要走 
			vis[f[1][i]]=1,last=f[1][i],fa[last]=1;
			cout<<f[1][i]<<endl;
			break;
		}
	}
	while(1){//一直走，直到到达n 
		cin>>k;//得到last的所有边 
		for(int i=1;i<=k;i++){
			cin>>f[last][i];
			if(f[last][i]==n){//能到n 
				cout<<n;
				return 0; 
			}
		}
		bool bo=0;//判断这个点能否走到新的点 
		for(int i=1;i<=k;i++){
			if(!vis[f[last][i]]){//有一个就走 
				vis[f[last][i]]=1;
				fa[f[last][i]]=last;
				last=f[last][i];
				bo=1;
				cout<<last<<endl;
				break;
			}
		}
		if(!bo){//走不了，退回去 
			cout<<fa[last]<<endl; 
			last=fa[last];
		}
	}
	return 0;
}
```


---

## 作者：_zzzzzzy_ (赞：0)

# 思路
这是一道很常规的交互题。

可以简单证明一条边最多会走 $2$ 次，那么我们就不可能输出 $-1$。

剩下的就是很简单的遍历图的操作了。

我们这里用 dfs 遍历，对于一个节点我们要遍历他的儿子要先知道他所有的儿子，也就是最开始先询问一遍知道他的儿子。

然后就可以遍历儿子了，遍历完之后要回来的时候还要在询问一下自己，因为要回来，并且自己和自己的儿子显然是相邻的。

这样就可以通过这题了。

# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
const int maxn = 1000000;
vector<int>e[maxn];
int vis[maxn];
vector<int> get(int x) {
	cout << x << endl;
	int k;
	cin >> k;
	vector<int> ans;
	for (int i = 1; i <= k; i++) {
		int x;
		cin >> x;
		ans.push_back(x);
	}
	return ans;
}
void dfs(int u) {
	vis[u] = 1;
	if (u != 1) {
		e[u] = get(u);
	}
	for (int v : e[u]) {
		if (vis[v]) {
			continue;
		}
		dfs(v);
		get(u);
	}
}
int main() {

	int n, m;
	cin >> n >> m;
	int k;
	cin >> k;
	for (int i = 1; i <= k; i++) {
		int x;
		cin >> x;
		e[1].push_back(x);
	}
	dfs(1);
	return 0;
}
```

---

## 作者：run_away (赞：0)

## 题意

一张未知的 $n$ 个点，$m$ 条边的无向连通图。

从 $1$ 号点开始，每次交互库给出与它相连的点编号，其中选出一个往下走。

在 $2n$ 次交互内到达 $n$ 号点。

## 分析

看到 $2n$ 的次数，可以想到搜索。

遍历一遍的次数是 $n$，这一轮可以把图建出来。

正好剩下 $n$ 次，可以直接再遍历一遍。

时间复杂度 $O(n)$。

~~这么简单的题怎么评绿的。~~

## Code

```cpp
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
#define dbg(x) cout<<#x<<": "<<x<<"\n"
// static char buf[100],*p1=buf,*p2=buf,obuf[100],*p3=obuf;
// #define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,100,stdin),p1==p2)?EOF:*p1++
// #define putchar(x) (p3-obuf<100)?(*p3++=x):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=x)
inline ll read(){ll x=0,f=1;char c=getchar();while(c<48||c>57){if(c==45)f=0;c=getchar();}while(c>47&&c<58)x=(x<<3)+(x<<1)+(c^48),c=getchar();return f?x:-x;}
mt19937_64 rnd(chrono::system_clock::now().time_since_epoch().count());
const ll mod=1e9+7,maxn=1e5+5,maxt=505;
ll n,m,k,sta[maxn],top;
bool vis[maxn];
vector<ll>son[maxn];
inline void dfs(ll u){
    if(u==n)exit(0);
    vis[u]=1;k=read();
    for(ll i=1;i<=k;++i){
        ll v=read();
        son[u].push_back(v);
    }
    for(auto v:son[u]){
        if(!vis[v]){
            sta[++top]=u;cout<<v<<endl;
            dfs(v);--top;
        }
    }
    cout<<sta[top]<<endl;
    dfs(sta[top--]);
    return;
}
inline void solve(){
    n=read(),m=read();
    dfs(1);
}
signed main(){
    ll t=1;
    while(t--){
        solve();
    }
    // fwrite(obuf,p3-obuf,1,stdout);
    return 0;
}
```

---

