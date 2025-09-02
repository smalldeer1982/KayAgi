# ループを探せ

## 题目描述

# 寻找环


众所周知，顶点数和边数均为 $n$ 的无向图仅包含一个环。

给出一个这样的图，求出图中包含的环的长度。

## 样例 #1

### 输入

```
4
1 2
2 3
3 1
1 4```

### 输出

```
3```

## 样例 #2

### 输入

```
4
1 2
2 3
3 4
4 1```

### 输出

```
4```

# 题解

## 作者：opzc35 (赞：1)

## 题意

给你一个 $n$ 个点，$n$ 个边的无向联通图，让你找到这个图中环的长度

## 思路

众所周知，拓扑排序对于无环图可以遍历，那么没被遍历到的肯定就是环中的元素。

考虑对于图进行拓扑排序。记录每次遍历到的点，用 $n$ 减去遍历过的节点即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans;
vector<int> g[100005];//这里使用vector邻接表来存图
int d[100005];
bool vis[100005];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		int x,y;
		cin>>x>>y;
		d[x]++,d[y]++;
		g[x].push_back(y);
		g[y].push_back(x);
		//加边
	}
	queue<int> q;
	//找到第一次拓扑排序的点
	for(int i=1;i<=n;i++){
		if(d[i]==1){
			q.push(i);
			vis[i]=1;
		}
	}
	//拓扑排序过程
	while(q.size()){
		int t=q.front();
		q.pop();
		ans++;//计算遍历过的点的数量
		for(auto v:g[t]){
			if(vis[v])continue;
			d[v]--;
			if(d[v]==1){
				q.push(v);
				vis[v]=1;
				//找到下一次遍历的节点
			}
		}
	}
	cout<<n-ans;
	cout<<endl;//注意这里，Atcoder早期题目末尾必须加上这个
	return 0;
}
```

## TIPS

冷知识，Atcoder 前期比赛的输出末尾是要加上换行的，如果你没有加上，那么恭喜你，你将会全部答案错误。

---

## 作者：dvsfanjo (赞：1)

# 题解：AT_code_festival_relay_f ループを探せ

## 思路

我们反过来想，求唯一的环的长度，只用总节点数减去不在环上的节点数即可。我们都知道，拓扑排序只对无环图有用，所以拓扑排序时入队的节点数就是不在环上的节点数。跑一边拓扑排序就行。

## code


```cpp
#include <bits/stdc++.h>
#define pb push_back
using namespace std;
using ll = long long;
const int maxn = 1e5 + 5;
ll n, u, v, cnt, deg[maxn], vis[maxn];
vector <ll> G[maxn];
ll topo() {
	ll o = 0;
	queue <ll> q;
	for (int i = 1; i <= n; i++)
		if (deg[i] == 1) {
			q.push(i);
			vis[i] = true;
		}
	while (q.size()) {
		ll p = q.front();
		q.pop();
		o++;
		for (auto g : G[p])
			if (!vis[g]) {
				deg[g]--;
				if (deg[g] == 1) {
					q.push(g);
					vis[g] = true;
				}	
			}
	}
	return o;
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> u >> v;
		G[u].pb(v);
		G[v].pb(u);
		deg[u]++;
		deg[v]++;
	}
	cout << n - topo() << '\n';
	return 0;
}
```


AC 记录： [link](https://atcoder.jp/contests/code-festival-2014-relay/submissions/58526461) 。

---

## 作者：forever516 (赞：1)

~~气死我了，打这篇拓扑排序我测了十几遍！~~
## 题意
给出一个无向的图，求出图中包含的环的长度。
## 做法
注意这一行：

众所周知，顶点数和边数均为
$n$
的无向图仅包含一个环。

由此可知这是一个拓扑排序。大家都知道，拓扑序存在于有向无环图中。

#### 注意！
1. 题意中有提到是**无向图**！因此入度初始值应附为
$1$。
2. 一定要注意**最后换行，不包含多余的文字或空行。**

其他的与裸拓扑排序差不多，照题意模拟即可。



```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e5+5;
vector<int>e[N];
queue<int>q;
int n,in[N];
bool vis[N];
int main() {
	cin>>n;
	for(int i=1; i<=n; i++) {
		int u,v;
		cin>>u>>v;
		e[u].push_back(v);//双向建边 
		e[v].push_back(u);//双向建边 
		in[u]++;//双向建边 ，入度++ 
		in[v]++;//双向建边 ，入度++  
	}
	for(int i=1; i<=n; i++) {
		if(in[i]!=1)continue;
		q.push(i);
		vis[i]=1;
	}
	while(!q.empty()) {
		int u=q.front();
		q.pop();
		n--;//n在后面已经没有用了，直接用来记录答案 
		for(int v:e[u]) {
			if(vis[v])continue;
			in[v]--;
			if(in[v]==1) {
				q.push(v);
				vis[v]=1;
			}
		}
	}
	cout<<n<<"\n";

	return 0;
}
```

---

## 作者：Big_Dinosaur (赞：0)

为什么题解区清一色都是拓扑？

可以发现，把环上任意一条边删掉，环上两点仍然连通，这意味着它是连通图。同时它有 $n-1$ 条边，是一棵树。

如果依次想图中加边，若一条边两端在同一连通块中，该边两端已经连通，加入后，这两点一个在环上。计算加入前两边路径长度，加 $1$ 即可。判断是否在同一连通块上可以使用并查集。

```cpp
#include<bits/stdc++.h>
#define int long long
#define pb push_back
#define ri register int
#define pii pair<int,int>
#define mp make_pair
#define fi first
#define se second
using namespace std;
namespace IO{
	char ibuf[(1<<20)+1],*iS,*iT;
	#if ONLINE_JUDGE
		#define gh() (iS==iT?iT=(iS=ibuf)+fread(ibuf,1,(1<<20)+1,stdin),(iS==iT?EOF:*iS++):*iS++)
 	#else
		#define gh() getchar()
	#endif
	inline int r(){
		int o=1,p=0;
		char q=gh();
		while(q<'0'||q>'9'){if(q=='-')o=-1;q=gh();}
		while(q>='0'&&q<='9'){p=(p<<1)+(p<<3)+(q^48);q=gh();}
		return o*p;
	}
	inline char gc(){char q=gh();while(q<=' ')q=gh();return q;}
	inline string gs(){string s="";char g=gh();while(g<=' ')g=gh();while(g>' '){s+=g;g=gh();}return s;}
	inline void Wi(int E){
		if(E==0)return;if(E<0){E=-E;putchar('-');}
		Wi(E/10);putchar((E%10)^48);
	}
	inline void wln(int J){if(J==0)putchar('0');else Wi(J);putchar('\n');}
	inline void w(int J){if(J==0)putchar('0');else Wi(J);}
	inline void ww(int J){if(J==0)putchar('0');else Wi(J);putchar(' ');}
}
using namespace IO;
namespace D1n0{
	int fa[102000],n,A,B;
	vector<int>v[102000];
	inline int get(int x){//并查集
		if(fa[x]==x)return x;
		return fa[x]=get(fa[x]);
	}
	inline void dfs(int x,int fa,int len){//求路径长度
		if(x==B){
			wln(len+1);return;
		}
		for(auto it:v[x])if(it!=fa)dfs(it,x,len+1);
	}
	inline void _(){
		n=r();
		for(ri i=1;i<=n;++i)fa[i]=i;
		for(ri i=1;i<=n;++i){
			int X=r(),Y=r();
			int x=get(X),y=get(Y);
			if(x!=y)fa[x]=y,v[X].pb(Y),v[Y].pb(X);
			else A=X,B=Y;
		}
		dfs(A,0,0);
	}
}
signed main(){D1n0::_();}
```

---

## 作者：topcsa (赞：0)

## 类型
这是一道跟图论相关的题目。
## 重点

这道题是一个~~较为模板~~的拓扑排序题。

## 分析

首先先来看一下样例

![](https://cdn.luogu.com.cn/upload/image_hosting/lw5zuip0.png)

因为我们的思路不是加入点，而是删除跟环无关的点，则开始把答案赋值成 $n$ 。

我们发现 $4$ 号点的度数为 $1$，并且它不是环中的一个点，则我们可以把这个点标记删除，把答案减一。

然后剩余的点的度数均为 $2$，没有可以删的点，那么拓扑结束，剩余点就是环的长度，即为 $\texttt {ans}$。

## 验证正确性

我们来看一个较为复杂的样例

最初 $\texttt{ans}=7$

![](https://cdn.luogu.com.cn/upload/image_hosting/0wrovqia.png)

其中最外面的点 $3,7,6$ 的度数都是 $1$ ，根据上文的结论，直接删除，此时 $\texttt{ans} = 4$。

那么图就变成了

![](https://cdn.luogu.com.cn/upload/image_hosting/s4h3f7hz.png)

这时 $5$ 的度数变成了 $1$，把 $5$ 删除了，此时 $\texttt{ans} = 3$。图就变成了

![](https://cdn.luogu.com.cn/upload/image_hosting/6gqemutf.png)

剩下的点的度数都是 $2$，最终 $\texttt{ans} = 3$。

## 奉上代码

有注释

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 100010;
vector<int> g[N]; // 存图 
int ind[N]; // 存储度数 
int vis[N]; //表示这个点是否被处理过 
signed main()
{
	int n;
	cin >> n;
	int ans = n; // 我们用有多少个点不在环里来减 
	for (int i = 1; i <= n; i++) { ///输入和存图 
		int u, v;
		cin >> u >> v;
		g[u].push_back(v); // 存双向边 
		g[v].push_back(u);
		ind[u]++; //因为双向，所以都要加 1 
		ind[v]++;
	}
	queue<int> q;
	for (int i = 1; i <= n; i++) { // 把最边上的点加入队列，即度数为1的点 
		if (ind[i] == 1) {
			q.push(i);
			vis[i] = 1;
		}
	}
	while (!q.empty()) { //进行拓扑排序 
		int u = q.front(); //提出点的编号 
		q.pop();
		ans--; // 因为提出的点肯定是度数为1的点，那就是最外面的点 
		vis[u] = 1; // 标记 
		for (auto v : g[u]) { //遍历 
			if (vis[v]) continue; // 如果点处理过，就跳过，避免重复处理，造成死循环 
			ind[v]--; // 假设把这个点删除，检测度数是否为1
			if (ind[v] == 1) { // 因为删除最外面的点，那么深一层的点就变成了最外面的点 
				vis[v] = 1;
				q.push(v);
			}
		}
	} //这就是拓扑排序的流程 
	cout << ans << '\n';
	return 0;
}
```

## 最后

提醒一下，处理完一定要标记，不然会死循环，本人就是因为这个问题在本地调了许久才调出来，还有度数的增加是 $x$ 点和 $y$ 点的度数都要增加。

---

## 作者：_Sky_Dream_ (赞：0)

[传送门](https://www.luogu.com.cn/problem/AT_code_festival_relay_f)

友情提醒：行末请换行，不然爆零两行泪！！！！

首先，建图（不用我讲吧）。

其次，我们将所有度为 $1$ 的点加入队列。

然后将相邻的点的度减 $1$。

如果接下来的点的度为 $1$，加入队列。

这样除了环以外的点就全被我们访问过啦！

由于在无向图中，只有环才可以是度大于一，度为 $1$ 才是不在环内的点。

那么，采用类似于 bfs 的算法就可以筛出所有不在环中的点。

AC Code：

```cpp
//#pragma GCC optimize(1)
//#pragma GCC optimize(2)
//#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define int long long
#define rep(i,x,y) for(int i=x;i<=y;++i)
#define N 100005
#define MAX 1145141919810
using namespace std;
struct node{
	int to,next;
}e[200005];
int num[200005],cnt,n,d[200005];
queue<int>q;
#define go(i,u) for(int i=num[u];i;i=e[i].next)
inline void Add(int u,int v){
	e[++cnt]={v,num[u]};
	num[u]=cnt;
}
inline void Enchanted(){
	srand(time(0));
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	cin>>n;
	rep(i,1,n){
		int x,y;
		cin>>x>>y;
		Add(x,y);
		Add(y,x);
		++d[x];++d[y];
	}
	rep(i,1,n)
		if(d[i]==1)
			q.push(i);
	cnt=0;	
	while(!q.empty()){
		int tmp=q.front();
		q.pop();
		++cnt;
		go(i,tmp){
			int x=e[i].to;
			--d[x];
			if(d[x]==1)q.push(x);
		}
	} 
	cout<<n-cnt<<endl;
}
signed main(){Enchanted();return 0;}

```

再次提醒：行末请换行，不然爆零两行泪！！！！

---

## 作者：VitrelosTia (赞：0)

我们知道一个环中任意一点的度数都是 $2$，而这道题保证图中只有一个环并且除了形成环的元素的度数都不可能大于 $2$ （可以从点数和边数推导），于是可以想到一种有些类似 Kahn 的搜索方法：建一个队列，先将度数为 $1$ 的点入队，然后每次取出队头的点，将与这个点相邻的点的度数减 $1$，假如此时度数为 $1$ 就将这个点入队。显然，这样一定能把除了形成环的点都搜一遍，统计入过队的元素然后用 $n$ 减就是答案了。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int M = 2e5 + 5;
int n, m;

struct Edge {
    int to, nxt;
} e[M];
int head[M], cnt;
void Add(int u, int v) {
    e[++cnt] = {v, head[u]};
    head[u] = cnt;
}
#define GoEdge(i, u) for (int i = head[u]; i; i = e[i].nxt)

int d[M];
queue <int> q;

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int u, v;
        cin >> u >> v;
        Add(u, v);
        Add(v, u);
        d[v]++;
        d[u]++;
    }
    for (int i = 1; i <= n; i++) {
        if (d[i] == 1) {
            q.push(i);
        }
    }
    int cnt = 0;
    while (!q.empty()) {
        int u = q.front();
        cout << u << '\n';
        cnt++;
        q.pop();
        GoEdge(i, u) {
            int v = e[i].to;
            d[v]--;
            if (d[v] == 1) q.push(v);
        }
    }
    cout << n - cnt << '\n';
    return 0;
}
```

---

## 作者：zhoujunchen (赞：0)

前置芝士
--
拓扑排序。

做题思路
---
拓扑排序板子题，只不过是双向边。

首先有环的图是不能拓扑排序滴，那么我们把总点数减去可以拓扑排序的点数就是环的长度。

怎么统计拓扑排序的点数呢？拓扑排序时每取出一个队首就计数器加一。

code:


```cpp
#include<bits/stdc++.h>
using namespace std;
int n,d[100005],res;
vector<int> g[100005];
bool vis[100005];
void toposort(){
    queue<int> q;
    for(int i=1;i<=n;i++)if(d[i]==1)q.push(i);//将度唯一的点加入队列
    while(!q.empty()){
        int u=q.front();
        q.pop();
        res++;
        vis[u]=1;
        for(auto v:g[u]){
            if(vis[v])continue;
            d[v]--;
            if(d[v]==1)q.push(v);
        }
    }
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        int u,v;
        cin>>u>>v;
        g[u].push_back(v);//建双向边
        g[v].push_back(u);
        d[u]++;
        d[v]++;
    }
    toposort();
    cout<<n-res<<"\n";
    return 0;
}
```

---

