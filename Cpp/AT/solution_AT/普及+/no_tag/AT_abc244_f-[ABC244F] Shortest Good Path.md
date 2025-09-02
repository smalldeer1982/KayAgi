# [ABC244F] Shortest Good Path

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc244/tasks/abc244_f

$ N $ 個の頂点と $ M $ 本の辺からなる単純（自己ループおよび多重辺を持たない）かつ連結な無向グラフが与えられます。  
 $ i\ =\ 1,\ 2,\ \ldots,\ M $ について、$ i $ 番目の辺は頂点 $ u_i $ と頂点 $ v_i $ を結びます。

下記の $ 2 $ つの条件をともに満たす整数列 $ (A_1,\ A_2,\ \ldots,\ A_k) $ を長さ $ k $ の**パス**と呼びます。

- すべての $ i\ =\ 1,\ 2,\ \dots,\ k $ について、$ 1\ \leq\ A_i\ \leq\ N $ 。
- すべての $ i\ =\ 1,\ 2,\ \ldots,\ k-1 $ について、頂点 $ A_i $ と頂点 $ A_{i+1} $ は辺で直接結ばれている。

空列も長さ $ 0 $ のパスとみなします。

$ S\ =\ s_1s_2\ldots\ s_N $ を $ 0 $ と $ 1 $ のみからなる長さ $ N $ の文字列とします。 パス $ A\ =\ (A_1,\ A_2,\ \ldots,\ A_k) $ が下記を満たすとき、パス $ A $ を $ S $ に関する**良いパス**と呼びます。

- すべての $ i\ =\ 1,\ 2,\ \ldots,\ N $ について、次を満たす。
  - $ s_i\ =\ 0 $ ならば、$ A $ に含まれる $ i $ の個数は偶数である。
  - $ s_i\ =\ 1 $ ならば、$ A $ に含まれる $ i $ の個数は奇数である。

$ S $ として考えられる文字列（すなわち、$ 0 $ と $ 1 $ のみからなる長さ $ N $ の文字列）は $ 2^N $ 個ありますが、そのすべてにわたる「 $ S $ に関する良いパスのうち最短のものの長さ」の総和を出力してください。

この問題の制約下において、$ 0 $ と $ 1 $ からなる長さ $ N $ のどのような文字列を $ S $ として選んでも、$ S $ に関する良いパスが少なくとも $ 1 $ つ存在することが示せます。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 17 $
- $ N-1\ \leq\ M\ \leq\ \frac{N(N-1)}{2} $
- $ 1\ \leq\ u_i,\ v_i\ \leq\ N $
- 与えられるグラフは単純かつ連結
- 入力はすべて整数

### Sample Explanation 1

\- $ S\ =\ 000 $ のとき、空列 $ () $ は $ S $ に関する最短の良いパスであり、その長さは $ 0 $ です。 - $ S\ =\ 100 $ のとき、$ (1) $ は $ S $ に関する最短の良いパスであり、その長さは $ 1 $ です。 - $ S\ =\ 010 $ のとき、$ (2) $ は $ S $ に関する最短の良いパスであり、その長さは $ 1 $ です。 - $ S\ =\ 110 $ のとき、$ (1,\ 2) $ は $ S $ に関する最短の良いパスであり、その長さは $ 2 $ です。 - $ S\ =\ 001 $ のとき、$ (3) $ は $ S $ に関する最短の良いパスであり、その長さは $ 1 $ です。 - $ S\ =\ 101 $ のとき、$ (1,\ 2,\ 3,\ 2) $ は $ S $ に関する最短の良いパスであり、その長さは $ 4 $ です。 - $ S\ =\ 011 $ のとき、$ (2,\ 3) $ は $ S $ に関する最短の良いパスであり、その長さは $ 2 $ です。 - $ S\ =\ 111 $ のとき、$ (1,\ 2,\ 3) $ は $ S $ に関する最短の良いパスであり、その長さは $ 3 $ です。 よって、求める答えは $ 0\ +\ 1\ +\ 1\ +\ 2\ +\ 1\ +\ 4\ +\ 2\ +\ 3\ =\ 14 $ です。

## 样例 #1

### 输入

```
3 2
1 2
2 3```

### 输出

```
14```

## 样例 #2

### 输入

```
5 5
4 2
2 3
1 3
2 1
1 5```

### 输出

```
108```

# 题解

## 作者：appear_hope (赞：3)

考虑状态设计：

状态：$(S,u,cnt)$ 表示当前路径是字符串 $S$ 的好路径，当前在点 $u$，路径长度为 $cnt$。

转移：$(S,u,cnt) \rightarrow (S \oplus 2^v, v,cnt+1)$，其中 $v$ 和 $u$ 有一条连边。

初始状态：$(2^i, i,1)$

可以发现转移是没有拓扑序，而转移的代价都是 $1$，从而考虑广度优先搜索。

代码如下：

```cpp
#include<bits/stdc++.h>

using namespace std;

const int N = 18, M = (1 << 18);

struct Node{
    int s, u, cnt;
}que[0];

bool vis[M][N];
vector<int> g[N];
int n, m, ans, head = 1, tail, dp[M];

void Record(int s, int u, int cnt){
    if(vis[s][u]){
        return ;
    }
    que[++tail] = {s, u, cnt};
    dp[s] = min(dp[s], cnt), vis[s][u] = 1;
}

int main(){
	cin >> n >> m;
    for(int i = 1, u, v; i <= m; i++){
        cin >> u >> v, --u, --v;
        g[u].push_back(v), g[v].push_back(u);
    }
    for(int i = 1; i < (1 << n); i++){
        dp[i] = 1e4;
    } 
    for(int i = 0; i < n; i++){
        Record(1 << i, i, 1);
    }
    while(head <= tail){
        Node q = que[head++];
        for(int v : g[q.u]){
            Record(q.s ^ (1 << v), v, q.cnt + 1);
        }
    }
    for(int i = 1; i < (1 << n); i++){
        ans += dp[i];
    }
    cout << ans;
	return 0;
}
```

---

## 作者：loser_seele (赞：3)

看到 $ N \leq 17 $ 果断状压。

类似旅行商问题的思路，考虑算出两两之间的最短路之后直接相加即可。

每个点出现次数的奇偶性可以视为异或，因为异或满足偶数次操作抵消的性质。

于是记录两个状态：当前集合和最后点的编号，则显然对于每一条连边 $ (u,v) $ 都可以从 $ dp_{S,u} $ 转移到 $ dp_{S \oplus 2^v,v} $，然后直接暴力 bfs 预处理距离，最后直接取所有距离的最小值即可。

总时间复杂度 $ \mathcal{O}(2^N \times N^2) $，可以通过。

代码：

```cpp
#import <bits/stdc++.h>
using namespace std;
vector<int>g[18];
int n, m, u, v;
int dp[1 << 17 + 1][18];
queue<pair<int, int>>q;
int main() 
{
	cin>>n>>m;
	while(m--) 
    {
		cin>>u>>v;
		u--,v--; 
		g[u].push_back(v);
		g[v].push_back(u);
	}
	int N=1<<n;
	for(int i=0;i<=N;i++)
    for(int j=0;j<=n;j++)
    dp[i][j]=1e9;
	for(int i=0;i<n;i++) 
    {
		dp[1<<i][i]=1;
		q.push({1<<i,i});
	}
	while(q.size()) 
    {
		auto [s, u]=q.front(); 
        q.pop();
		for (auto v:g[u]) 
        {
			int ns=s ^ (1 << v);
			if (dp[ns][v]!=1e9)
            continue;
			dp[ns][v]=dp[s][u]+1;
			q.push({ns,v});
		}
	}
	long long ans=0;
	for(int s=1;s<N;s++) 
    {
		int temp=1e9;
		for(int u=0;u<n;u++) 
		temp=min(temp,dp[s][u]);
		ans+=temp;
	}
	cout<<ans;
}
```


---

## 作者：lyas145 (赞：2)

题目在[这里](https://www.luogu.com.cn/problem/AT_abc244_f)。

## 解题思路

$N \le 17$，一看就是状压。

在这篇题解中，我们把 $S$ 当成一个二进制数。

注意一下，我喜欢这样写：节点编号从 $1$ 开始，第 $i$ 个节点的状态对应二进制数的第 $i-1$ 位。

从题目中可以得出，路径长度是**经过的点的数量**，相当于**点权是 $1$**，路径长度是**经过的点的点权和**，并且是要求出**最短**的好路径。

似乎和 **bfs** 有点关系？

不是似乎，是一定有关系！

于是我们可以令 **$f_{u,j}$ 表示以 $u$ 为终点且 $S$ 是 $j$ 时的最短好路径长度**，然后从每个点开始进行 **bfs**（注意别走重了）。在转移过程中（假设从 $u$ 到 $v$ 进行转移且 $u$ 和 $v$ 之间有边），$S$ 的第 $v-1$ 位需要改变，这可以直接异或一下，因为一定是**奇变偶**或**偶变奇**，转移为：

$$f_{v,j\oplus 2^{v-1}}=f_{u,j}+1$$

具体的一些其他细节可以看代码。

## 码儿

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=20,M=1<<17,INF=0x3f3f3f3f;
int n,m,ans;
int f[N][M];
bool dis[N][N];        //我用邻接矩阵存的图。
struct Node{int u,s;}; //u 和 s 的含义分别与 f 的第一维和第二维相同。
queue<Node> q;
inline int read() {    //快读。
	int x=0;
	char c=getchar();
	while (!isdigit(c)) {c=getchar();}
	while (isdigit(c)) {x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x;
}
void bfs() {
	while (!q.empty()) {
		Node u=q.front();
		q.pop();
		for (int v=1;v<=n;v++) {
			if (!dis[u.u][v]) {continue;}          //没边就不走。
			if (f[v][u.s^(1<<v-1)]<INF) {continue;}//之前走过了也不走。
			q.push({v,u.s^(1<<v-1)});              //加入队列。
			f[v][u.s^(1<<v-1)]=f[u.u][u.s]+1;      //更新 f 数组。
		}
	}
}
int main() {
	memset(f,0x3f,sizeof f);       //把 f 初始化为正无穷。
	n=read();m=read();
	while (m--) {
		int a=read(),b=read();
		dis[a][b]=dis[b][a]=1;
	}
	for (int i=1;i<=n;i++) {
		//若 S 的每一位都是 0，那就最好一个点也别去，最短好路径长度就是 0。
		f[i][0]=0;
		q.push({i,0});
	}
	bfs();
	for (int i=1;i<1<<n;i++) {     //统计答案。
		int t=INF;
		for (int j=1;j<=n;j++) {t=min(t,f[j][i]);}
		ans+=t;
	}
	printf("%d\n",ans);
	return 0;
}
```

Thanks for reading！

---

## 作者：KarmaticEnding (赞：1)

### 阅读题面

我们观察这道题的题面，已经发现了两个特点。

  - $n\le 17$，很小。
  - 题面上有一个图，并且还是一个无向图。
  - 题面明确给出了“二进制数” $S$。
我们想想，一道题 $n$ 很小，有一个图，要用二进制，那么这道题是什么？对了，这不就是一个 TSP 旅行商问题吗？

[关于 TSP 旅行商到底是个什么东西](https://www.luogu.com.cn/problem/P1171)

### 构建思路

其实这道题并不是板子 TSP 旅行商问题，但是我们可以应用板子的思想。

我们想想，“若 $s_i=0$，则 $A$ 中有偶数个 $i$”和“若 $s_i=1$，则 $A$ 中有奇数个 $i$”这两个条件是在提醒我们什么？

如果我们认为每一个点都有两种颜色，黑色和白色，开始的时候每个点都视为白色，我们每走过这个点一次就反转一次颜色，那么我们想，这个点是不是走过奇数次之后，它的颜色是黑色？是不是走过偶数次之后，它的颜色是白色？

那么这道题的重头戏来了：异或。__我们不要根据 $S$ 去构造“好路径”，相反，我们应当走完所有路径之后，看每个 $S$ 的最短“好路径”是多长__。

那么这道题的解法也就出来了。第一步，我们要建图。

```cpp
for(int i=1,u,v;i<=m;++i){
	scanf("%d%d",&u,&v);
	--u,--v;//下标是从0开始的
	g[u].push_back(v);
	g[v].push_back(u);
}
```

建完图之后，我们要执行 $dp$ 数组的初始化。怎么初始化呢？

首先我们把 $dp$ 数组赋值为一个极大值。
```cpp
for(int i=0;i<(1<<n);++i){
	for(int j=0;j<n;++j){
		dp[i][j]=2100000000;
	}
}
```

其次，我们来想想，如果我们只走一个点，也即 $S$ 的二进制表示中只有一个 $1$，那么 $S$ 的“好路径”长度是不是一定是 $1$？所以我们应该这样做：

```cpp
for(int i=0;i<n;++i){
	dp[1<<i][i]=1;
	q.push({1<<i,i});
}
```

然后跑 Dijkstra。这里一定要注意，你 Dijkstra 的 `pair<int,int>` 到底表示的是什么？还是{距离，点编号}吗？不是的，你应当储存{状态，点编号}。

```cpp
while(q.size()){
	PII t=q.front();
	q.pop();
	int st=t.first,u=t.second;
	for(int v:g[u]){
		int newst=st^(1<<v);
		if(dp[newst][v]==2100000000){//这个点没有被更新过
			dp[newst][v]=dp[st][u]+1;
			q.push({newst,v});
		}
	}
}
```

最后就可以统计答案了。

```cpp
long long ans=0;
for(int st=1;st<(1<<n);++st){
	int tmp=2100000000;
	for(int u=0;u<n;++u){
		tmp=min(tmp,dp[st][u]);
	}
	ans+=tmp;
}
```

那么这道题就这样圆满的结束了。个人觉得自己讲得不很清楚，如果您没有听懂，或者您认为我可以从哪些方面优化这个题解，可以在评论区吱个声；如果您觉得我讲得好，请点一个赞，谢谢

---

