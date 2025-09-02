# Ring road

## 题目描述

Nowadays the one-way traffic is introduced all over the world in order to improve driving safety and reduce traffic jams. The government of Berland decided to keep up with new trends. Formerly all $ n $ cities of Berland were connected by $ n $ two-way roads in the ring, i. e. each city was connected directly to exactly two other cities, and from each city it was possible to get to any other city. Government of Berland introduced one-way traffic on all $ n $ roads, but it soon became clear that it's impossible to get from some of the cities to some others. Now for each road is known in which direction the traffic is directed at it, and the cost of redirecting the traffic. What is the smallest amount of money the government should spend on the redirecting of roads so that from every city you can get to any other?

## 样例 #1

### 输入

```
3
1 3 1
1 2 1
3 2 1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
3
1 3 1
1 2 5
3 2 1
```

### 输出

```
2
```

## 样例 #3

### 输入

```
6
1 5 4
5 3 8
2 4 15
1 6 16
2 3 23
4 6 42
```

### 输出

```
39
```

## 样例 #4

### 输入

```
4
1 2 9
2 3 8
3 4 7
4 1 5
```

### 输出

```
0
```

# 题解

## 作者：Fearliciz (赞：8)



不理解为什么那么多人想得复杂了。

+ [这篇题解](https://www.luogu.com.cn/blog/iwara/solution-cf24a)

+ [这篇题解](https://www.luogu.com.cn/blog/xiaozhuzhu233/solution-cf24a)

这里提供一种贪心的方法。

其实很好想，思路如下：

一共有两种情况，取其较小的即可。

第一种方法：

凡是遇到一个已经存了的点，就用 $cnt$ 累加费用，然后存边。

第二种方法：

与第一种相反，修改剩余。

代码也很好写，没什么可讲的。

```cpp
#include<bits/stdc++.h>

using namespace std;

int n,x,y,z;
int cnt,sum;
bool from[110],to[110];

int main()
{
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>x>>y>>z;
		if(from[x]) from[y]=1,to[x]=1,cnt+=z; //如果有连接两点的边，cnt 累计并反向存边
		else if(to[y]) from[y]=1,to[x]=1,cnt+=z;
		else from[x]=1,to[y]=1; //如果没有，则直接存
		sum+=z; //累计总和
	}
	cout<<min(sum-cnt,cnt)； //输出两种方法的最小的
	return 0;
}
```

我的代码有防作弊哦！



---

## 作者：xiayucc (赞：4)

#### ~~不是很懂楼上大佬的链式前向星，所以这里写一发常规的大法师~~

### 题意：
	给我们一个图 ：一共n个点，然后给出n条路，
    每个路正向的边权是0，反向的边权是v
    （正向的路已经建好，v是建反方向路的代价）
    让我们找出一个边权最小且经过所有点的环
    因为需要两两之间可达且费用最低
    
###    思路：
	正常的DFS肯定是超时的，所以我们需要必要的剪枝，用记忆化搜索来找环，如果这个点被访问过了，我们不需要在搜索这个点
   （因为环上面的点最多只出现一次）
  
##  CODE：
   ```c
#include<bits/stdc++.h>
#define maxn 233
using namespace std;
int edge[maxn][maxn];
int vis[maxn];
int minn,n,e,v,s;
void dfs(int st,int en,int sum,int step)
{
    if(st==en&&step==n)//如果起点终点一样，且一共经过了n个点那么更新最小值
    {
        minn=min(minn,sum);
    }
    for(int i=1;i<=n;i++)
    {
        if(vis[i]==1)//如果访问过就跳过
            continue;
        if(edge[en][i]!=0&&edge[i][en]==0)//如果i这个点没访问过且这条边存在且是边权不为零的边，那将en调整成i继续往下走
        {
            vis[i]=1;//记忆化搜索的步骤
            dfs(st,i,sum+edge[en][i],step+1);
            vis[i]=0;//记忆化搜索的步骤
        }
        else if(edge[en][i]==0&&edge[i][en]!=0)//如果i这个点没访问过且这条边存在且是边权为零的边，那将en调整成i继续往下走
        {
            vis[i]=1;
            dfs(st,i,sum,step+1);
            vis[i]=0;
        }
    }
}
int main()
{
    cin>>n;
    for(int i=0;i<n;i++)
    {
        cin>>s>>e>>v;
        edge[s][e]=0;
        edge[e][s]=v;
    }
    minn=100000000;
    dfs(1,1,0,0);
    cout<<minn<<endl;//输出经过所有点的最小环
    return 0;
}

```

    
    
    

---

## 作者：XL4453 (赞：3)

### $\text{Difficulty : 1400}$
---
做 $\text{Ring Road 2}$ 的时候跳过来的，顺手写掉。

---
### 解题思路：

题目给出的图在吧有向边变成无向边时候是一个环，而如果想要一个环上每一个点都能到达其他的任意点，只有将环上所有的边的方向更改成同一个就行了。

可以考虑将每一个边拆成两个建立，一个边权为正，另一个为负，然后便利的时候只取正的或者负的就完成了对方向的处理。

题目中只有一个环，不需要考虑太多复杂情况。

---
### 代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=10005;
int n,head[MAXN],nxt[MAXN],num[MAXN],w[MAXN],tot,x,y,z;
void add(int x,int y,int z){
	nxt[++tot]=head[x];head[x]=tot;num[tot]=y;w[tot]=z;
}
int dfs(int now,int fa){
	if(now==1&&fa!=1)return 0;
	if(now==1&&fa==1){
		int ans=2147483647;
		for(int i=head[now];i;i=nxt[i])
		ans=min(ans,dfs(num[i],now)+max(0,w[i]));
		return ans;
	}
	for(int i=head[now];i;i=nxt[i])
	if(num[i]!=fa)return dfs(num[i],now)+max(0,w[i]);
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d%d%d",&x,&y,&z);
		add(x,y,-z);add(y,x,z);
	}
	printf("%d\n",dfs(1,1));
	return 0;
}
```


---

## 作者：UperFicial (赞：3)

# 图论

### 前言

图论一直是我的短板，正好拿来补一补（

对于蒟蒻而言还是很妙的一道题。

题目链接：[$\text{Link}$](https://www.luogu.com.cn/problem/CF24A)

### 题目大意

给定 $n$ 个点 $n$ 条边的有向图，调整一条边的方向的花费为 $k_i$，求要使每两个点互相联通的情况下花费最小。

### 解题思路

先来考虑什么情况下每两个互相联通。

很显然，在 $n$ 个点 $n$ 条边的图中，只有形成了一个**环**，每两个点才会联通。

由此，题目就变成求将图变为一个**环**后花费最小。

明显是用 $dfs$ 毕竟 $n\le 100$。

但是重要的就是建图，我们对于给定的 $u,v$ 之间连一条 $u\to v$ 花费为 $0$ 的单向边，意思是本身就已经有了方向，花费 $0$ 就可以达到这个方向；同理连一条 $v\to u$ 花费为 $w$ 的单向边。

建好图，开始 $dfs$，结束条件是当目前的 $u$ 回到了起点并且经过了 $n$ 个点，就说明走出了个环，更新 $ans$，否则就需从目前的 $u$ 去寻找能到达的所有的点，并用一个 $vis$ 来表示 $u$ 点有没有到达过。

$AC$ 记录：[$\text{Link}$](https://www.luogu.com.cn/record/42186991)

[$code$](https://paste.ubuntu.com/p/Nv3HYs2Wq9/)

$$\texttt{The End.by UF}$$

---

## 作者：sssscy_free_stdio (赞：2)

这是本蒟蒻写的第一篇题解~

可以发现，这题题意就是找边权和最小且经过所有点的环。

思路：

这题由于是找经过所有点的环，因此可以 DFS。

可是暴力 DFS 会超时，那怎么办呢，可以用一个数组标记这个点是否走过，如果是，就不走，否则走并标记，就可以通过了。

AC CODE:
```cpp
#include<bits/stdc++.h>
using namespace std;
vector<int>g[110];
int n,u,v,w,th[110][110],mi=0x7fffffff,vis[110];
void dfs(int s,int u,int now,int cnt){
	if(s==u&&cnt==n){//如果走回来了(是个环)，且经过了所有点，更新mi
		mi=min(mi,now);
	}for(int i=0;i<(int)g[u].size();i++){
		int v=g[u][i];//可以走的下一个点
		if(!vis[v]&&th[u][v]>0){//判断是否走过，且th[u][v]>0
			vis[v]=1;//标记为走过
			dfs(s,v,now+th[u][v],cnt+1);
			vis[v]=0;
		}if(!vis[v]&&th[u][v]==0){//判断是否走过，且th[u][v]==0
			vis[v]=1;//标记为走过
			dfs(s,v,now,cnt+1);
			vis[v]=0;
		}
	}
}int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d%d%d",&u,&v,&w);
		g[u].push_back(v),g[v].push_back(u);//双向建边
		th[v][u]=w;//反向建路的花费
	}dfs(1,1,0,0);
	printf("%d",mi);
	return 0;
}
```

---

## 作者：Wsy_flying_forever (赞：2)

## dfs训练题  
 
### 思路 
倘若没看到 $E=n$ 这个条件，思维难度会跃升到紫题（转换为强联通 $DAG$ 的最小步数问题），但有了这个限制条件，我们不难想到，任选一个点出发跑一整遍图，只有 $2$ 种可能性，这也就保证了$\mathcal{O}(2n)$ 的时间复杂度。（当然这题 $n$ 最大就 $100$ ）  

最后补充一个小技巧，看到很多题解都用链式前向星做，但个人认为针对此题 Vector 更简便，且更高效。

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=1e3+10;
inline int read() {
	int x=0,f=1;
	char ch=getchar();
	while (!isdigit(ch)) {
		if (ch=='-') f=-1;
		ch=getchar();
	}
	while (isdigit(ch)) {
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x*f;
}
struct Node {
	int to;
	int val;
	inline Node () {}
	inline Node (int x,int y) : to(x),val(y) {}
};
int n,ans=INT_MAX;
vector <Node> a[maxn];
inline void dfs(int x,int fa,int cost) {
	if (x==1 && fa) {
		ans=min(ans,cost);
		return ;
	}
	for (int i=0;i<2;i++) {
		int y=a[x][i].to;
		if (y==fa) continue;
		dfs(y,x,cost+a[x][i].val);
	}
}
int main() {
	n=read();
	for (int i=1;i<=n;i++) {
		int x=read(),y=read(),z=read();
		a[x].push_back(Node(y,0));
		a[y].push_back(Node(x,z));
	}
	dfs(1,0,0);
	printf("%d\n",ans);
	return 0;
}
```
完结撒花！

---

## 作者：WRuperD (赞：2)

### 题意：
在一个有 $n$ 个点，$n$ 条边**单向**没有重边的图中，你可以改变任意一条边的方向，但需要花钱，问你最**少花多少钱改变多少条边的方向才能使得图联通**。	
### 思路：
由于是 $n$ 个点，$n$ 条边**单向没有重边的图**，所以为了保证联通，最后结果肯定是一个**环**，所以我们只需要对每个点枚举逆时针的环和顺时针的环两种情况，看看每条边是否要改变即可。
### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
bool vis[105]; // 是否到过这个点 
long long ans = 0x3f3f3f3f; 
int n;

struct edge{
	int to, val;
};	vector <edge> p[105];

void dfs(int x, long long cnt, int num){
	if(x == 1 and num == n){
		ans = min(ans, cnt);
		return ;
	}
	if(vis[x])	return ;
	vis[x] = true;
	dfs(p[x][0].to, cnt + p[x][0].val, num+1);//一种环 
	dfs(p[x][1].to, cnt + p[x][1].val, num+1);//另一种环 
	vis[x] = false;
	return ;
}

int main()
{
	
	cin>>n;
	for(int i = 1; i <= n; i++)
	{
		int a, b, c;
		cin>>a>>b>>c;
		p[a].push_back(edge{b,0});
		p[b].push_back({edge{a,c}});
	}
	dfs(1, 0, 0);
	cout<<ans<<endl;
	return 0;
 } 
```


---

## 作者：yimuhua (赞：2)

## 题意：
给出 $n$ 条从 $x$ 到 $y$ 的路径，可以以 $w_i$ 的代价改变第 $i$ 条路径的方向，求最后使得 $n$ 个点全部联通的最小代价。

## 思路：
分析题意，发现 $n$ 个点全部连通的情况只有可能是一个环，于是我们以第一个点为起点，分别跑一遍顺时针和逆时针的搜索，选择代价更小的那个。

## 代码实现：
使用 ```vector``` 建边，```dfs``` 找环，```dfs(x,fa,sum)``` 表示当前在点 $x$，上一个点为 $fa$，目前代价为 $w$。

## AC代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
vector<int> v[1005];
int n, m, mini = 1e9, ans[5], a[1005][1005];
void dfs(int x, int fa, int w) {
    w += a[fa][x];
    if(x == 1) {
        mini = min(mini, w);
        return;
    }
    for(int i = 0; i < v[x].size(); i++)
        if(v[x][i] != fa)
            dfs(v[x][i], x, w);
    return;
}
int main() {
    cin >> n;
    for(int i = 1, x, y; i <= n; i++) {
        cin >> x >> y, a[x][y] = 0, cin >> a[y][x], v[x].push_back(y), v[y].push_back(x);
        if(x == 1)
            ans[++m] = y;
        if(y == 1)
            ans[++m] = x;
    }
    dfs(ans[1], 1, 0), dfs(ans[2], 1, 0), cout << mini;
    return 0;
}
```


---

## 作者：Bad_Luck_No_Fun (赞：0)

大水题，题面其实是诈骗。

我们会发现原来的图是一棵基环树。

把基环树改成有向图后，除非所有点在一个环里，否则不可能联通。

就比如叶子结点，他只可能有出度或有入度，而不可能都有。

所以只能是一个环。

那就简单了，直接建立双向边，跑一遍 dfs 就行了。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
# define Rep(i,a,b) for(int i=a;i<=b;i++)
# define _Rep(i,a,b) for(int i=a;i>=b;i--)
# define RepG(i,u) for(int i=head[u];~i;i=e[i].next)
# define maxn 1005
typedef long long ll;
template<typename T> void read(T &x){
	x=0;int f=1;
	char c=getchar();
	for(;!isdigit(c);c=getchar())if(c=='-')f=-1;
	for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+c-'0';
	x*=f;
}
# define int long long
int n, m, all;
vector <int> e[maxn];
vector <int> g[maxn];
bool vis[maxn];
int dfs(int u, int fa)
{
	if(vis[u]) return 0;
	vis[u] = 1;
	if(e[u][0] != fa) return g[u][0] + dfs(e[u][0], u);
	else return g[u][1] + dfs(e[u][1], u);
}
signed main()
{
	read(n);
	for(int i = 1; i <= n; i++){
		int u, v, w;
		read(u); read(v); read(w);
		e[u].push_back(v), e[v].push_back(u);
		g[u].push_back(0), g[v].push_back(w);
		all += w;
	}
	int k = dfs(e[1][0], 1);
	cout << min(k, all - k) << endl;
	return 0;
}

```


---

## 作者：Nephren_Sakura (赞：0)

题目描述：[link](https://www.luogu.com.cn/problem/CF24A)

第一次看到本题，首先阅读题面：

根据题意，城市中只有 $n$ 条边。

若这 $n$ 条边可以使这 $n$ 个城市两两连通，则这 $n$ 条边必定构成环。

则以第一个点为起点，分别顺时针与逆时针寻找。

在代码中，本人使用了链式前向星建边，dfs 找环。

```dfs(fa,cur,sum)``` 表示当前在 $cur$ 点，上一个点为 $fa$，目前权值为 $w$。

注意：

1. 记得分顺时针与逆时针。

1. 建边时，如果是同向权值为 $0$，否则权值为 $w$。

1. dfs 边界条件为 $cur=1$。

下附代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while (ch<'0'||ch>'9'){
		if (ch=='-')
			f=-1;
		ch=getchar();
	}
	while (ch>='0'&&ch<='9'){
		x=(x<<1)+(x<<3)+ch-48;
		ch=getchar();
	}
	return x*f;
}
inline void put(int x)
{
    if (x > 9) put(x / 10);
    putchar(x % 10 + 48);
}
int n=read(),tot,head[1000005],ans[1000005],cnt,mini=1e18;
int vis[1005][1005];
struct edge{
	int to,next;
}a[1000005];
void add(int x,int y){
	tot++;
	a[tot].next=head[x];
	a[tot].to=y;
	head[x]=tot;
	return;
}
void dfs(int fa,int cur,int sum){
	sum+=vis[fa][cur];
	if(cur==1){
		mini=min(mini,sum);
		return;
	}
	for(int i=head[cur]; i; i=a[i].next){
		int nxt=a[i].to;
		if(nxt!=fa)
			dfs(cur,nxt,sum);
	}
	return;
}
signed main(){
	for(int i=1; i<=n; i++){
		int x=read(),y=read();
		vis[x][y]=0;
		vis[y][x]=read();
		add(x,y);
		add(y,x);
		if(x==1)
			ans[++cnt]=y;
		if(y==1)
			ans[++cnt]=x;
	}
	dfs(1,ans[1],0);
	dfs(1,ans[2],0);
	cout<<mini;
	return 0;
}
```

---

