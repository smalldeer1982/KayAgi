# Graph Without Long Directed Paths

## 题目描述

You are given a connected undirected graph consisting of $ n $ vertices and $ m $ edges. There are no self-loops or multiple edges in the given graph.

You have to direct its edges in such a way that the obtained directed graph does not contain any paths of length two or greater (where the length of path is denoted as the number of traversed edges).

## 说明/提示

The picture corresponding to the first example: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1144F/fc796670216638599d8ac1ff04285340e3fcfa12.png)

And one of possible answers: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1144F/c977822c41ff79938ae076a798e7208fe7f3d987.png)

## 样例 #1

### 输入

```
6 5
1 5
2 1
1 4
3 1
6 1
```

### 输出

```
YES
10100
```

# 题解

## 作者：Deft_t (赞：6)

# 思路
手画一下容易发现，要使得图中不存在长度 $\geq2$ 的路径。只能是每个顶点相连的边都是指向它或者从它出发.
相当于每个顶点满足以下两个性质之一：

- 入度为 $0$ 
- 出度为 $0$   

同时还要加上一个限制条件：相邻的顶点性质不同。  
此时问题就变成了二分图染色问题。因为是连通图，直接选定任意一个点作为起点染色即可。
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
struct edge{
	int u,v,next;
}e[400005];
int p[400005],eid = 0;
void addedge(int u,int v){
	e[eid].v = v;
	e[eid].u = u;
	e[eid].next = p[u];
	p[u] = eid++;
}
int u[200005],v[200005];
bool ok = true;
int col[200005];
bool vis[200005];
void dfs(int u,int c){
	if(!ok) return;
	col[u] = c;
	for(int i = p[u];i!=-1;i=e[i].next){
		int v = e[i].v;
		if(col[v]==col[u]){
			ok = false;
			return;
		}
		if(col[v]==-1) dfs(v,1-c);
	}
}
int main()
{
	int n,m;
	cin>>n>>m;
	memset(p,-1,sizeof(p));
	for(int i = 1;i <= m;i++){
		scanf("%d%d",&u[i],&v[i]);
		addedge(u[i],v[i]);
		addedge(v[i],u[i]);
	}
	memset(col,-1,sizeof(col));
	memset(vis,false,sizeof(vis));
	dfs(1,0);
	if(ok){
		puts("YES");
		for(int i = 1;i <= m;i++){
			if(col[u[i]]) printf("1");
			else printf("0");
		}
		puts("");
	}
	else puts("NO");
	return 0;
}
```


---

## 作者：天泽龟 (赞：3)

## 题目大意：

给你一个无向图，让你把所有边标记方向，并使其没有距离$>=2$的边，问你是否存在并输出方案。

## 题解：

不是，这题蓝的我可以理解，但是能上紫我是真的不知道啊。。而且一个$div.3$的题，$BCD$居然都能紫？？而且你谷判恶意评分居然是按比例排的，想把它评回黄都不行。。

~~以上扯淡，~~来看这道题。先随手画个样例：

![](https://cdn.luogu.com.cn/upload/pic/55674.png)

1. 图中我们可以看到，那个 `1-3-2` 肯定违法了，因为你无论`2-3`怎么连，要么与`1-3`重，要么与`1-2`重。。

2. 但明显的是，`1-6-5-4`可以通过`1`往外连，`5`往内连边的方式造出符合题意的图。

3. 但我们发现，对于`1-7-8-9`即使有4个顶点，若`7-9`有连边则仍不行。。

### ~~于是我们猜想，只要存在奇数环就肯定不行，否则就行。~~

虽然这个猜想十分正确，但显然您并不能根据这短短的一句话敲出一个正确的代码。因为虽然判环我们可以通过拓扑，但判断连边情况却没有一个体系的方法。。

### 于是考虑柯学证明：

**引入黑白染色法，** 将源点（这里默认为1）涂黑，凡是有边相连的涂白，就这样来回染色，我们的样例就变成这样。

![](https://cdn.luogu.com.cn/upload/pic/55675.png)

我们在来观察能否成功连边的情况：

1. 可以看出，原来不能连边的环里都出现了**同色点有直接连边的情况**，证明也是显然的，由于正常黑点连到白点形成偶数的配对，若同色则必会出现奇数条边。

2. 若没有同色连则也很容易的构造出答案：将所有黑点连向白点即可。这样搞的话边是方向交替变的（就像`1-6-5-4`一样）

然后就没有辣！以上操作均可以在一个DFS内完成，上我丑陋的代码：
```cpp
#include <iostream>
using namespace std;

struct ed{
	int u,next,v;
}e[600000];
int n,m,x,y,st=1,fir[300000],col[300000],v[300000];
bool fal;
void add(int x,int y)
{
	e[++st].u=y; e[st].next=fir[x]; fir[x]=st;
	e[++st].u=x; e[st].next=fir[y]; fir[y]=st;
}

void dfs(int x,int fa)
{
	if (v[x]&&col[x]==col[fa]) {fal=1; return;} //同色直接死。
	col[x]=!col[fa]; v[x]++;
	if (v[x]==1) for (int i=fir[x];i;i=e[i].next)
	{
		int u=e[i].u; if (u==fa) continue; //无向图不走回头路。
		if (col[x]) e[i].v=1,e[i^1].v=0; else e[i^1].v=1,e[i].v=0;
     //i^1表示标记它的反边，从网络流那里学的技巧。。
     dfs(u,x); 
	}
}

int main()
{
	cin>>n>>m;
	for (int i=1;i<=m;i++) cin>>x>>y,add(x,y);
	dfs(1,0);
	if (fal) cout<<"NO"<<endl;
	else 
	{
		cout<<"YES"<<endl;
		for (int i=2;i<=2*m;i+=2) cout<<e[i].v;
	}
}
```

---

## 作者：SuyctidohanQ (赞：2)

### 题意分析

把所有的边标记方向，使得整张图中没有距离 $ \ge 2$ 的路径。如果这张图中没有距离 $ \ge 2$ 的路径，那么输出 `YES` 并且按照读入顺序输出连边方向；否则输出 `NO`。

### 做法分析

要看整张图中有没有距离 $ \ge 2$ 的路径，不难发现，顶点要满足以下其中一个条件：

- 入度为 $0$。

- 出度为 $0$。

这时候，我们就可以采用二分图染色问题来解决此题（也就是黑白染色问题）。

我们任意选定一个点作为起点进行染色；染色黑白点之间随便定一个方向，可以黑到白染色，同时也可以白到黑染色。

### AC Code


```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
bool vis[N];
int shu[N], n, m;
vector <int> vec[N];
struct node {
	int u, v;
} a[N];
bool dfs (int u, int c) {
	if (vis[u]) {
		if(shu[u] == c) return true;
		else return false;
	}
	vis[u] = true; shu[u] = c;
	for (int i : vec[u])
		if (dfs(i, 3 - c) == false) return false;
	return true;
}
int main() {
	cin >> n >> m;
	for (int i = 1; i <= m; i ++) {
		cin >> a[i].u >> a[i].v;
		vec[a[i].u].push_back(a[i].v);
		vec[a[i].v].push_back(a[i].u);
	}
	if (dfs(1,1)) cout << "YES" << endl; 
	else {
		cout << "NO" << endl; 
		return 0;
	}
	for (int i = 1; i <= m; i ++) {
		if (shu[a[i].u] == 1) cout << 1;
		if (shu[a[i].u] == 2) cout << 0;
	}
	cout << endl;
	return 0;
}
```

---

## 作者：jiuguaiwf (赞：2)

这题贼水的好吗，用不着那么ke学吧...QvQ

~~省选前堕落到来这划水，我tm肯定凉了~~

首先，题目描述：1.连通图  2.没有大于等于二的路径

那我们就有两点推论了：

1.合法方案中将所有边反向依旧成立

2.由于没有**等于二的路径**，因此，每确定一条边的方向就能推及原图中与此边相邻所有边的方向

可知，我们由此及彼的每一步操作都是唯一的，且最正确的（换而言之不合法直接退出输出NO就完事儿了）

哇，这不就是纯dfs么....

另外，假设一条无向边链接u,v，我们规定方向为从v到u，我们可以标记vis[u]=0,vis[v]=1，表示这条边确定后，所有与u相连的边均指向u，所有与v相连的边均由v指向别人（很好理解，不然两条边就不合法了）

至此，边的方向变成了点的颜色（0色和1色...）,水之

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<queue>
#include<vector>
using namespace std;
int n,m,fail,a[200005],b[200005];
int h[200005],vis[200005],cnt;
struct wf{
	int to,nxt;
}edge[200005<<1];
void add(int u,int v)
{
	edge[++cnt].to=v;
	edge[cnt].nxt=h[u];
	h[u]=cnt;
}
void dfs(int u,int fa,int col)
{
	if (fail) return;//一旦不合法，就退出
	vis[u]=col;
	for (int i=h[u];i;i=edge[i].nxt)
	{
		int v=edge[i].to;
		if (v==fa) continue;
		if (!vis[v]) dfs(v,u,col^1);
		else if (vis[v]==vis[u]) 
		{
			fail=1;
			return;
		}
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	int u,v;
	for (int i=1;i<=m;i++)
	{
		scanf("%d%d",&u,&v);
		add(u,v);
		add(v,u);
		a[i]=u;
		b[i]=v;
	}
	dfs(1,-1,0);
	if (fail) printf("NO");
	else
	{
		printf("YES\n");
		for (int i=1;i<=m;i++)
		  if (!vis[a[i]]) printf("0");
		  else printf("1");
	}
	return 0;
}
```

希望对您有所帮助
++RP；


---

## 作者：fanfansann (赞：1)

# $F.\ Graph\ Without\ Long\ Directed\ Paths$

一道水题，二分图染色。


$Description$

给你一个无向图，把所有边标记方向，并使整张图中没有距离 ≥2 的路径，问你是否存在并输出方案。

第一行输出“YES”或“NO”，若存在，第二行按照读入顺序输出连边方向（对于每一条边，如果该条边的连边方向是按照输入的方向有$u_i$到$v_i$就输出1，否则就输出0）。


$Solution$

很明显这是一道染色问题，如果路径≥2，那么就会有两个相邻的点同时为入，或者同时为出。如果没有，就说明没有两条边或以上是连着走的。
画一下样例，顺便加一点数据。
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200531093906601.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80NTY5Nzc3NA==,size_16,color_FFFFFF,t_70)
~~虽然入度和出度不是这个意思，但是这里把它魔改一下用还是挺清晰的~~ 
然后代码就非常简单了。

$Code$

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<bitset>
#include<vector>

#define over(i,s,t) for(register int i = s;i <= t;++i)
#define lver(i,t,s) for(register int i = t;i >= s;--i)
//#define int __int128
#define lowbit(p) p&(-p)
using namespace std;

typedef long long ll;
typedef pair<int,int> PII;

const int N = 2e5+7;
struct node{int u,v,val;}a[N];
int n,m;
vector<int>G[N];
int vis[N];//记录颜色
int v[N];//记录是否走过
void dfs(int now,int sta){
    vis[now] = sta;
    v[now] = 1;
    //cout<<sta<<endl;
    for(int i = 0;i < G[now].size();++i){
        int to = G[now][i];
        if(!v[to])
        dfs(to,-sta);//往下染
    }
}

int main()
{
    bool flag = 1;
    scanf("%d%d",&n,&m);
    over(i,1,m){
        int u,v;
        scanf("%d%d",&a[i].u,&a[i].v);
        G[a[i].u].push_back(a[i].v);//先建无向图
        G[a[i].v].push_back(a[i].u);
    }
    dfs(1,1);//染色
    over(i,1,m){
        if(vis[a[i].u] != vis[a[i].v]){
            if(vis[a[i].u] == 1)//是出度则为1也就是选择的边是从ui到vi的
                a[i].val = 1;
            else a[i].val = 0;//不是则为0
        }
        else flag = 0;
    }
    if(!flag){
        puts("NO");
    }
    else {
        puts("YES");
        over(i,1,m)
        printf("%d",a[i].val);
        puts("");
    }
    return 0;
}
```


---

## 作者：ChrisK (赞：1)

二分图染色的题

一看到不能大于等于$2$就能想到染色

那就染色黑白点之间随便定一个方向，可以黑到白也可以白到黑

代码如下

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2*1e5+10;
int n,m,head[maxn],tot=1;
struct node{
    int to,nxt,id;
    #define to(x) e[x].to
    #define nxt(x) e[x].nxt
}e[maxn<<1];
inline void add(int from,int to){
    to(++tot)=to;nxt(tot)=head[from];head[from]=tot;
}
int cl[maxn],fl=1;
void dfs(int x,int co){
    cl[x]=co;
    for(int i=head[x];i;i=nxt(i)){
        int y=to(i);
        if(cl[y] && cl[y]==cl[x]){
            fl=0;return;
        }
        if(!cl[y]) dfs(y,3-co);
        if(cl[x]==1 && cl[y]==2) e[i].id=1,e[i^1].id=0;
        if(cl[x]==2 && cl[y]==1) e[i].id=0,e[i^1].id=1;
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int x,y,i=1;i<=m;i++){
        scanf("%d%d",&x,&y);add(x,y);add(y,x);
    }
    dfs(1,1);
    if(!fl) printf("NO\n");
    else{
        printf("YES\n");
        for(int i=2;i<=2*m;i+=2){
            cout<<e[i].id;
        }
    }
    puts("");
    return 0;
}
```

---

## 作者：2huk (赞：0)

注意到图中没有距离 $\ge 2$ 的路径等价于所有点的出度为 $0$ 或入度为 $0$。

我们令 $c_i = 0/1$ 表示 $i$ 的出度为 $0$ 还是入度为 $0$。

注意到相邻两点 $u, v$ 的 $c$ 一定不同。证明的话，如果这条边定向为 $u \to v$，那么 $c_u=1,c_v=0$。$u \gets v$ 同理。

因此变成了一个二分图染色的问题。

---

## 作者：断清秋 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1144F)

首先图是无向连通图。

路径长度 $\le 2$，等价于一个点不能既有入边又有出边，即一个点要么入度为 $0$，要么出度为 $0$。

注意到相邻的点必然具有的性质不同，那么直接二分图染色即可。

---

## 作者：chlchl (赞：0)

水题，建议降蓝或降绿（~~我实在不理解我什么时候能够一眼秒紫题了~~）。

## Solution
无向图变有向，不存在大于等于 $2$ 的路径，意味着对于每一条边，所有与这条边相邻的边都**必须与其反向**。

但是这样变成了边的“二分图”。我们从点上考虑。

显然对于每一个点，不可能同时存在入度和出度（因为如果同时存在，走这两条边路径长度就是 $2$ 了）。所以每个点要么只出不进，要么只进不出。

并且有边直接相连的两个点不可能同属一类，结论显然，读者画图自证不难。

所以这其实就是一个二分图染色问题，套个模板就可以收工了。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10;
int n, m, f, uu[N], vv[N], col[N];
int id, head[N << 1], to[N << 1], nxt[N << 1];

void add(int u, int v){
	to[++id] = v;
	nxt[id] = head[u], head[u] = id;
}

void dfs(int u){
	for(int i=head[u];i;i=nxt[i]){
		int v = to[i];
		if(col[u] == col[v])
			f = 1;//染出矛盾了，不存在连边方案 
		if(col[v] == -1)
			col[v] = col[u] ^ 1, dfs(v);
	}
}

int main(){
	memset(col, -1, sizeof(col));
	scanf("%d%d", &n, &m);
	for(int i=1;i<=m;i++){
		scanf("%d%d", &uu[i], &vv[i]);
		add(uu[i], vv[i]), add(vv[i], uu[i]);
	}
	col[1] = 1;
	dfs(1);
	if(f)
		return printf("NO\n"), 0;
	printf("YES\n");
	for(int i=1;i<=m;i++){
		if(col[uu[i]])//随便判，反正两端一定是一个 1 一个 0 
			printf("1");
		else
			printf("0");
	}
	return 0;
}
```


---

## 作者：Lily_White (赞：0)

UPD：修改了一处笔误

我们来分析这个题给的要求。

> 不能有长度大于$2$的路。

那这就意味着，这张图必须要能被分为两个部分$A$和$B$，使得只存在从$A$到$B$的边，而没有回来的边。

这就说明了，这张图是一个**二分图**。直接染色判断即可。

代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int (i) = 0; (i) < n; (i)++)
const int INF = 0x3f3f3f3f;
const long double EPS = 1e-6;
const int N = 200020;
vector <int> G[N];
int n, m, col[N];
void dfs(int u, int nowcol) {
	col[u] = nowcol;
	for (auto v:G[u]) {
		if (col[v] == -1) {//没有染过色
			dfs(v, nowcol ^ 1);//染上与现在不同的颜色
		}
		else if (col[v] == nowcol) {//有一个点已经染色且与当前点颜色相同
			cout << "NO" << endl;//不可能
			exit(0);//直接结束程序
		}
	}
}
vector <pair <int, int> >Edges;
int main() {
	ios::sync_with_stdio(false);
	cin >> n >> m;
	rep(i, m) {
		int u, v;
		cin >> u >> v;
		--u, --v;//我从0开始编号
		G[u].pb(v);
		G[v].pb(u);
		Edges.pb(mp(u, v));
	} 
	memset(col, -1, sizeof(col));//-1表示没有染过色
	dfs(0, 0);
	cout << "YES" << endl;
	for (auto i:Edges) {
		if (col[i.first] == 0)cout << 1;
		else cout << 0;
	} 
	return 0;
}
```

---

