# Cars

## 题目描述

坐标轴 $O\!X$ 上有 $n$ 辆汽车。每辆车最初位于一个整数点，并且没有两辆车位于同一点。此外，每辆车都可以向左或向右定向地、可以随时以任何恒定的正速度地沿该方向移动。

更正式地说，我们可以用一个字母和一个整数来描述第 $ i $ 辆汽车：它的方向 $ ori_i $ 和它的位置 $ x_i $ 。如果 $ ori_i = L \ \left(Left\right) $ ，则 $ x_i $ 以相对于时间的恒定速率递减。类似地，如果 $ ori_i = R \ \left(Right\right)$ ，则 $ x_i $ 以相对于时间的恒定速率增加。

如果两辆汽车无论速度如何都永远不会到达同一点，我们称它们为 **无关紧要的**。换句话说，它们在任何时候都不会处于相同的坐标。

如果两辆汽车无论速度如何，它们一定会到达同一点，我们就称它们为 **命中注定的** 。换句话说，它们一定会在某个时刻处于相同的坐标。

不幸的是，我们丢失了有关我们汽车的所有信息，但我们依然记得这些车之间的 $ m $ 个关系。有两种类型的关系：

 - $ 1$ $ i $ $ j $ — 第 $ i $ 辆车和第$ j $ 辆车是 **无关紧要的**。

- $ 2 $ $ i $ $ j $— 第 $ i $ 辆车和第 $ j $ 辆车是 **命中注定的**。

要求求出满足关系的汽车的方向和位置，或着回答满足关系的车不可能存在的。如果有多个解决方案，则输出任何一个。

**请注意，如果两辆车处于相同的坐标，它们将相交，但同时它们将继续沿各自的方向移动。**

## 样例 #1

### 输入

```
4 4
1 1 2
1 2 3
2 3 4
2 4 1```

### 输出

```
YES
R 0
L -3
R 5
L 6```

## 样例 #2

### 输入

```
3 3
1 1 2
1 2 3
1 1 3```

### 输出

```
NO```

# 题解

## 作者：CWJ020311 (赞：6)

[例题链接](https://codeforces.com/problemset/problem/1635/E)

- **题目描述：** 给定 n,m ，分别表示一共有 $n$ 辆车和 $m$ 个限制。每个限制形如：$u,v,op$ ，若 $op=1$ 表示 $u,v$ 注定不相关；若 $op=2$ 表示 $u,v$ 注定相关。
- 每辆车有方向和位置两个属性。若注定不相关，则无论车以怎样的速度，都不会遇见；若注定相关，则无论车以怎样的速度，都会遇见。
- 判断是否可以满足所有限制，若不能输出 NO，否则输出 YES 以及每辆车的方向和位置。（每辆车的起始位置均不相同）$n,m<=2e5,x_i\in[-1e9,1e9]$

- **问题分析：** 
- **步骤1：**
- 若两辆车以同一个方向行驶，则即不可能保证遇见，也不可能保证不遇见
- 因此两个车必然是相对而行（注定不会遇见）和相向而行（注定会遇见）
- 因此，所有有限制的车方向都是相反的。
- 可以为有限制的车连边，判断是否存在二分图
- 若存在二分图，则表示可以将所有点分成朝左方向的点和朝右方向的点。
- 否则，不可能符合题意

- **步骤2：** 
- 已经确定完了所有点的方向了，开始确定起始位置
- 枚举每一对有限制的车 $i,j$，设 $i$ 为朝左方向的点，$j$ 为朝右方向的点
- 若 $i,j$ 注定不相关，则 $x_i<x_j$  ，建图 $i->j$
- 若 $i,j$ 注定相关，则 $x_i>x_j$，建图 $j->i$

- 最后检查一下是否出现环即可，若未出现环，则表示图是一个 $DAG$ 图，拓扑序设置 $x$ 即可
- 若出现环，则不符合题意

- 总时间复杂度：$O(n+m)$

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5;
const long long inf=1e15;
#define LL long long

vector<int>G[N];
vector<pair<int,int>>rel[3];
int n,m,vis[N],col[N],du[N];
int ans[N];

void dfs(int u){
    for(auto &v:G[u]){
        if(col[v]==-1){
            col[v]=col[u]^1;
            dfs(v);
        }else if(col[v]==col[u]){
            cout<<"NO";
            exit(0);
        }
    }
}
void dfs2(int u){
    vis[u]=1;
    for(auto &v:G[u]){
        if(vis[v]==1){
            cout<<"NO";
            exit(0);
        }else if(vis[v]==0){
            dfs2(v);
        }
    }
    vis[u]=2;
}
int main(){
    int op,u,v;
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cin>>op>>u>>v;
        G[u].push_back(v);
        G[v].push_back(u);
        rel[op].push_back(make_pair(u,v));
    }
    for(int i=1;i<=n;i++)col[i]=-1;
    for(int i=1;i<=n;i++){//vis[i]=0，表示朝左
        if(col[i]==-1){
            col[i]=0;
            dfs(i);
        }
    }
    for(int i=1;i<=n;i++)G[i].clear();
    for(auto &[u,v]:rel[1]){//注定不相遇
        if(col[u]==0){
            G[u].push_back(v);
            du[v]++;
        }else{
            G[v].push_back(u);
            du[u]++;
        }
    }
    for(auto &[u,v]:rel[2]){//注定相遇
        if(col[u]==0){
            G[v].push_back(u);
            du[u]++;
        }else{
            G[u].push_back(v);
            du[v]++;
        }
    }

    for(int i=1;i<=n;i++)vis[i]=0;
    for(int i=1;i<=n;i++){
        if(du[i]==0){
            dfs2(i);
        }
    }
    for(int i=1;i<=n;i++){
        if(vis[i]==0){
            cout<<"NO";
            return 0;
        }
    }
    queue<int>q;
    for(int i=1;i<=n;i++){
        if(du[i]==0)q.push(i);
    }
    int t=-1e9;
    while(!q.empty()){
        int u=q.front();
        q.pop();
        ans[u]=++t;
        for(auto &v:G[u]){
            du[v]--;
            if(du[v]==0){
                q.push(v);
            }
        }
    }
    
    cout<<"YES"<<endl;
    for(int i=1;i<=n;i++){
        if(col[i]==0)cout<<"L ";
        else cout<<"R ";
        cout<<ans[i]<<endl;
    }
    
    return 0;
}
```

---

## 作者：清烛 (赞：4)

一维数轴上，初始在 $n$ 个不同位置有 $n$ 辆车，车的朝向确定，而速度可以为任意常数。定义两种车子之间的关系：

- 称两辆车**风马牛不相及**当且仅当不论他们的速度如何，他们都永远无法相遇。
- 称两辆车**双向奔赴命中注定**当且仅当不论他们的速度如何，他们都能在一个点相遇。

现在给定 $m$ 条这样的关系，请还原出 $n$ 辆车的坐标和朝向。$n,m\le 2\times 10^5$。

首先不难发现，“风马牛不相及”指的就是两辆车是往两边散开的，“双向奔赴命中注定”指的就是两辆车是往中间双向奔赴的。**有关系的车的朝向都是不一样的**，这个可以用二分图染色染一下。

然后，对于风马牛不相及的车的关系，可以发现 $x_L<x_R$，相应的对于双向奔赴的，有 $x_R<x_L$，于是我们可以考虑给原来二分图的边定向：若 $x_u<x_v$，则连边 $u\to v$，反之亦然。

这样下来，发现这些约束关系是天然的偏序关系，有解当且仅当图是张 DAG，并且需要求方案的话输出拓扑序就可以了。所以总结一下算法流程：二分图染色（判断无解），给边定向，拓扑排序（判断无解）并给点赋坐标。

```cpp
const int maxn = 2e5 + 5;
vector<int> G0[maxn], G[maxn];
int n, m, vis[maxn], col[maxn], ind[maxn], x[maxn];
bool flg = 1;

struct Relation {
    int op, u, v;
} a[maxn];

void dfs(int u, int cur) {
    col[u] = cur, vis[u] = 1;
    for (int &v : G0[u]) {
        if (vis[v] && col[v] == cur) flg = 0;
        if (vis[v]) continue;
        dfs(v, cur == 1 ? 2 : 1);
    }
}

int main() {
    read(n, m);
    FOR(i, 1, m) read(a[i].op, a[i].u, a[i].v), G0[a[i].u].push_back(a[i].v), G0[a[i].v].push_back(a[i].u);
    FOR(i, 1, n) if (!vis[i]) dfs(i, 1);
    if (!flg) {
        print("NO");
    } else {
        FOR(i, 1, m) {
            const int &u = a[i].u, &v = a[i].v;
            if (a[i].op == 1) {
                if (col[u] == 1) G[u].push_back(v), ++ind[v];
                else G[v].push_back(u), ++ind[u];
            } else {
                if (col[u] == 2) G[u].push_back(v), ++ind[v];
                else G[v].push_back(u), ++ind[u];
            }
        }
        queue<int> q;
        FOR(i, 1, n) if (!ind[i]) q.push(i);
        int cntx = 0;
        while (!q.empty()) {
            int u = q.front();
            x[u] = ++cntx;
            q.pop();
            for (const int &v : G[u]) {
                if (!--ind[v]) q.push(v);
            }
        }
        if (cntx != n) {
            print("NO");
        } else {
            print("YES");
            FOR(i, 1, n) {
                putchar(col[i] == 1 ? 'L' : 'R'); putchar(' ');
                print(x[i]);
            }
        }
    }
    return output(), 0;
}
```



---

## 作者：include_BM (赞：3)

若两辆车不会相遇（操作 1），那么说明它们方向相反，且向右的那辆在向左的那辆右边；若两辆车一定会相遇（操作 2），那么说明它们方向相反，且向右的那辆在向左的那辆左边。

先考虑方向相反，可以使用并查集，同一集合中的车辆方向相同，设 $a[i]$ 表示第 $i$ 辆车的方向，显然若 $a[i]\not=a[j]$ 且 $a[i]\not=a[k]$，那么 $a[j]=a[k]$。设 $b[i]$ 表示与 $a[i]$ 方向相反的任意一辆车的编号，那么如果 $a[i]\not=a[j]$ 就将 $j$ 与 $b[i]$ 合并。

```cpp
for(int i=1;i<=m;++i){
    op[i]=read(),x[i]=read(),y[i]=read();
    if(getf(x[i])==getf(y[i])) return puts("NO"),0;//x[i],y[i] 方向已经相同，不满足方向不同的要求。
    if(!b[x[i]]) b[x[i]]=y[i]; else merge(b[x[i]],y[i]);
    //若 b[x[i]] 为 0 说明目前还没有方向与 x[i] 相反的车辆，直接将 y[i] 赋给 s[x[i]] 即可，下同。
    if(!b[y[i]]) b[y[i]]=x[i]; else merge(b[y[i]],x[i]);
}
```

处理完这步之后，枚举所有集合并确定方向。

```cpp
for(int i=1;i<=n;++i) vc[getf(i)].push_back(i);
for(int i=1;i<=n;++i)
    if(getf(i)==i&&!a[i]){//若 a[i]!=0 则说明该集合方向已经被确认。
        for(auto x:vc[i]) a[x]=1;
        for(auto x:vc[getf(b[i])]) a[x]=-1;//方向相反的集合。
    }
//1 表示向右，-1 表示向左。
```

再次枚举车辆之间的关系，由于方向已知，可以得出 $x[i],y[i]$ 坐标的大小关系，由坐标较小的向较大的连一条边，那么若有解，按拓扑序排列坐标一定是符合要求的（坐标小的一定在坐标大的之前）。

```cpp
for(int i=1;i<=m;++i){
    if(op[i]==1){
        if(a[x[i]]==1) e[y[i]].push_back(x[i]),++du[x[i]];
        else e[x[i]].push_back(y[i]),++du[y[i]];
    }
    else{
        if(a[x[i]]==1) e[x[i]].push_back(y[i]),++du[y[i]];
        else e[y[i]].push_back(x[i]),++du[x[i]];
    }
}
//坐标较小的向较大的连边。

for(int i=1;i<=n;++i) if(!du[i]) q.push(i),pos[i]=++cnt;

while(!q.empty()){
    int u=q.front(); q.pop();
    for(auto x:e[u]) if(!--du[x]) q.push(x),pos[x]=++cnt;//此时比 x 坐标小的车辆已经被安排好了。
}
//按拓扑序排列所有车辆。
```

若图中存在环，拓扑排序一定无法遍历完所有点（简单模拟一下可得），即最终 $cnt\not=n$，判断有无解并输出即可。

```cpp
if(cnt==n){
    puts("YES");
    for(int i=1;i<=n;++i) printf("%c %d\n",a[i]==1?'R':'L',pos[i]);
}
else puts("NO");
```


---

## 作者：Lvlinxi2010 (赞：3)

学校的题单里的题，来写一篇题解。

可以发现两辆车有关系他们的方向必定相反，那我们连边进行黑白染色，如果有两个相邻的点同色则不合法。

可以发现合法的图一定是一个二分图，然后我们给边定向，令 $L$ 表示一条边中方向向左的车，$R$ 表示一条边中方向向右的车。

如果两车是**无关紧要的**，$X_R<X_L$，如果两车是**命中注定的**，$X_L<X_R$。（因为题目要求 $X_i$ 互不相同，所以不取等）。

把坐标小的向坐标大的连边，跑拓扑排序，同时记录遍历到的点数 $cnt$，如果 $cnt<n$ 证明出现了环，不合法。

最后输出方向和坐标即可。

附上代码：

```cpp
#include<bits/stdc++.h>
#define FL(i,a,b) for(int i=(a);i<=(b);i++)
#define FR(i,a,b) for(int i=(a);i>=(b);i--)
#define ll long long
using namespace std;
const int MAXN = 2e5 +10;
const int inf = 0x3f3f3f3f;
struct data{
	int op,u,v;
}e[MAXN]; 
int col[MAXN],X[MAXN],cnt=0,in[MAXN];
vector<int>G[MAXN],E[MAXN];
void dfs(int u,int fa){
	for(int v:G[u]){
		if(v==fa) continue;
		if(!col[v]){
			col[v]=3-col[u];
			dfs(v,u);
		}
		else if(col[v]==col[u]){
			puts("NO");
			exit(0);
		}
	}
}
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	FL(i,1,m){
		scanf("%d%d%d",&e[i].op,&e[i].u,&e[i].v);
		G[e[i].u].push_back(e[i].v);
		G[e[i].v].push_back(e[i].u);
	}
	FL(i,1,n) if(!col[i]) col[i]=1,dfs(i,0);
	FL(i,1,m){
		if(e[i].op==1){
			if(col[e[i].u]==1) swap(e[i].u,e[i].v);
			E[e[i].u].push_back(e[i].v),in[e[i].v]++;
		}
		else{
			if(col[e[i].u]==2) swap(e[i].u,e[i].v);
			E[e[i].u].push_back(e[i].v),in[e[i].v]++;
		}
	}
	queue<int>q;
	FL(i,1,n) if(!in[i]) q.push(i);
	while(!q.empty()){
		int u=q.front();
		q.pop();
		X[u]=++cnt;
		for(int v:G[u]){
			in[v]--;
			if(!in[v]) q.push(v);
		}
	}
	if(cnt!=n){
		puts("NO");
		exit(0);
	}
	puts("YES");
	FL(i,1,n){
		printf("%c %d\n",(col[i]==1)?'R':'L',X[i]);
	}
}
```

---

## 作者：Dtw_ (赞：1)

[luogu](https://www.luogu.com.cn/problem/CF1635E)
# 题目大意
对于两个车，如果无论如何都不能遇见那么称他们为**无关紧要**的，在此叫他为 1 ，如果无论如何都能遇见那么称他们为**命中注定**的，在此叫他 2 。给出他们的关系让你求每个车的移动方向以及速度

# 思路
考虑怎样才能满足 1/2

1：方向相反并且向右走的在向左走的左边

![](https://cdn.luogu.com.cn/upload/image_hosting/zk8hkdj2.png)


2：方向相反并且向右走的在向左走的右边

![](https://cdn.luogu.com.cn/upload/image_hosting/a13fugdk.png)

那么我可以开始连边了，有关系的都可以连边，先考虑方向，这个图可以有环吗？

可以有偶数环，但不能有奇环。因为相连的两个点的方向是相反的，如果出现奇环那显然是不行的

没有奇环，很容易想到二分图

对于所有点用二分图染色，如果出现奇环那就直接输出 `NO` 。

之后怎么办？

连边跑拓扑排序，如果拓扑排序没跑完那肯定也是不合法的，最后输出就行

如何连边？

假设按照无关紧要的连边，那就按照不能相遇建边。

如果是 1 ，那么向左走的向向右走的连一条边

如果是 2 ，则反过来，向右走的向向左走的连一条边

如果按照命中注定的连边，把所有的反过来就行了

# Code

```cpp
#include<bits/stdc++.h>

using namespace std;

#define endl '\n'

#define TRACE 1
#define tcout TRACE && cout

#define IN(o) insert(o)

#define fi first
#define se second

#define int long long

#define fst ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

const int INF = 0x3f3f3f3f3f3f3f3f;

const int P = 998244353;

const int N = 1e6 + 10;

struct Edge
{
	int w, x, y;
}a[N];

int n, m;

int col[N];

int idg[N];

int f[N];

int tot;

vector<int> G[N], g[N];

queue<int> q;

void dfs(int u, int c)
{
	col[u] = c;
	for(auto v : g[u])
	{
		if(col[v] == c)
		{
			cout << "NO";
			exit(0);
		}
	}
	for(auto v : g[u])
	{
		if(col[v] == 0)
		{
			dfs(v, -c);
		}
	}
}

signed main()
{
	cin >> n >> m;
	for(int i=1; i<=m; i++)
	{
		cin >> a[i].w >> a[i].x >> a[i].y;
		g[a[i].x].push_back(a[i].y);
		g[a[i].y].push_back(a[i].x);
	}
	for(int i=1; i<=n; i++)
	{
		if(col[i] == 0)
		{
			dfs(i, -1);
		}
	}
	for(int i=1; i<=m; i++)
	{
		if(col[a[i].x] == 1)
		{
			swap(a[i].x, a[i].y);
		}
		if(a[i].w == 1)
		{
			G[a[i].x].push_back(a[i].y);
			idg[a[i].y]++;
		}
		else
		{
			G[a[i].y].push_back(a[i].x);
			idg[a[i].x]++;
		}
	}
	
	for(int i=1; i<=n; i++)
	{
		if(idg[i] == 0)
		{
			q.push(i);
		}
	}
	while(!q.empty())
	{
		int u = q.front();
		q.pop();
		f[u] = ++tot;
		for(auto v : G[u])
		{
			idg[v]--;
			if(idg[v] == 0)
			{
				q.push(v);
			}
		}
	}
	if(tot != n)
	{
		cout << "NO";
		return 0;
	}
	cout << "YES" << endl;
	for(int i=1; i<=n; i++)
	{
		if(col[i] == -1)
		{
			cout << "L " << f[i] << endl;
		}
		else
		{
			cout << "R " << f[i] << endl;
		}
	}
	return 0;
}



```


---

## 作者：saixingzhe (赞：1)

# 思路
首先我们观察到，每两辆车之间如果有关系，那么这两辆车的方向一定是相反的，可以用二分图染色染出每辆车的方向。

如果此图不是二分图则无解。

然后我们可以得出两辆车直接的大小关系，进行拓扑排序，若无法进行拓扑排序则无解。

拓扑序即为每个车的坐标，按序输出即可。

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int m,n,type,u,v,vis[200002],dis[200002],ans[2000002],tot,tvis[200002];
struct Node{
	int type,to;
};
vector <Node> G[200002];
vector <int> f[200002];
bool dfs(int i,int col){//0L,1R
	vis[i]=col;
	for(auto v:G[i]){
		if(vis[v.to]==vis[i])	return 0;
		if(vis[v.to]==-1&&dfs(v.to,col^1)==0)	return 0;
	}
	return 1;
}
void topsort(){
	queue<int>q;
	for(int i=1;i<=n;i++) if(!dis[i]) q.push(i);
	while(!q.empty()){
		int w=q.front();
		q.pop();
		if(tvis[w])	continue;
		tvis[w]=1;
		ans[w]=(++tot);
		for(int v:f[w]){
			dis[v]--;
			if(!dis[v])	q.push(v);
		}
	}
}
int main(){
	memset(vis,-1,sizeof(vis));
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)	scanf("%d%d%d",&type,&u,&v),G[u].push_back({type,v}),G[v].push_back({type,u});
	for(int i=1;i<=n;i++){
		if(vis[i]==-1&&!dfs(i,0)){
			printf("NO");
			return 0;
		}
	}
	for(int i=1;i<=n;i++){
		for(auto v:G[i]){
			if(v.type==1){
				if(vis[i])	f[v.to].push_back(i),dis[i]++;
				else	f[i].push_back(v.to),dis[v.to]++;
			}
			else{
				if(vis[i])	f[i].push_back(v.to),dis[v.to]++;
				else	f[v.to].push_back(i),dis[i]++;
			}
		}
	}
	topsort();
	if(tot==n){
		printf("YES\n");
		for(int i=1;i<=n;i++){
			if(vis[i])	printf("R ");
			else	printf("L ");
			printf("%d\n",ans[i]);
		}
	}
	else	printf("NO");
	return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：1)

# CF1635E 题解



## 思路分析

注意到确定位置的过程是和每个点的方向有关的，因此考虑先确定方向。

注意到如果 $(u,v)$ 出现在限制中，那么无论是相遇还是不相遇，都能保证 $u$ 和 $v$ 方向不同，因此把 $\{ori_i\}$ 看成 $n$ 个 01 变量解一遍 2-SAT 即可得到每个点的方向。

注意到这里的 2-SAT 只存在 $ori_u\oplus ori_v=1$ 的限制，可以用扩域并查集求解，具体过程和用 tarjan 解 2-SAT 比较类似，令 $i$ 表示 $ori_i=0$，$i+n$ 表示 $ori_i=1$：

1. 合并所有 $u+n,v$ 和 $u,v+n$。
2. 如果存在 $u,u+n$ 在同一个块内，则该 2-SAT 无解。
3. 讨论每个块的 01 情况，用一个标记维护每个块是否确定了 01 情况，对于每个 $u$，有如下三种情况：

- 如果 $u$ 和 $u+n$ 所在的块都未被标记，则令 $ori_u=0$，并标记 $u$ 所在块。
- 如果 $u$ 所在的块被标记，则 $ori_u=0$。
- 如果 $u+n$ 所在的块被标记，则 $ori_u=1$。

这样我们能够确定一组合法的 $\{ori_i\}$，那么此时再对于 $(u,v)$ 讨论能够得到每对 $x_u,x_v$ 的相对大小关系。

因此我们可以建立一个差分约束系统，注意到这个系统的所有边权都是 $-1$ 的，因此只需要对其进行拓扑排序即可，$x_u$ 即为 $u$ 的拓扑序，如果差分系统中有环，那么该差分系统一定无解。

不过我们需要保证对于任何一组合法的 $\{ori_i\}$，如果其对应的差分系统无解，则原问题无解。

> 我们只能通过每次对一个块内所有节点取反来修改 $\{ori_i\}$，注意到如果差分系统中存在一个环，那么这个环中的节点一定是在一个块内的，假如我们对这个块内所有节点的 $ori_i$ 取反，等价于对这个差分系统里这些节点之间的边取反，显然这样的操作是不可能消掉差分系统里的环的。

因此只要求解出随意一组合法的 $\{ori_i\}$ 都不会对答案产生影响。

时间复杂度 $\Theta(m\alpha(n))$。

## 代码呈现

```cpp
#include<bits/stdc++.h>
#define L false
#define R true
#define MEET 2
#define LEAVE 1
using namespace std;
const int MAXN=2e5+1;
struct node {
	int u,v,w;
};
vector <node> edges;
int dsu[MAXN<<1];
inline int find(int x) {
	if(dsu[x]==x) return x;
	return dsu[x]=find(dsu[x]);
}
inline void merge(int u,int v) {
	dsu[find(u)]=find(v);
}
bool dir[MAXN],ch[MAXN<<1],vis[MAXN<<1];
vector <int> G[MAXN];
int deg[MAXN],pos[MAXN];
signed main() {
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=2*n;++i) dsu[i]=i;
	for(int i=1;i<=m;++i) {
		int w,u,v;
		scanf("%d%d%d",&w,&u,&v);
		edges.push_back((node){u,v,w});
		merge(u,v+n),merge(u+n,v);
	}
	for(int i=1;i<=n;++i) {
		if(find(i)==find(i+n)) {
			puts("NO");
			return 0;
		}
		int x=find(i),y=find(i+n);
		if(!vis[x]) {
			dir[i]=L;
			vis[x]=vis[y]=true;
			ch[x]=true,ch[y]=false;
		} else dir[i]=ch[x]?L:R;
	}
	for(auto e:edges) {
		int u=e.u,v=e.v,w=e.w;
		if(w==LEAVE) {
			if(dir[u]==L&&dir[v]==R) G[u].push_back(v),++deg[v];
			if(dir[u]==R&&dir[v]==L) G[v].push_back(u),++deg[u];
		}
		if(w==MEET) {
			if(dir[u]==L&&dir[v]==R) G[v].push_back(u),++deg[u];
			if(dir[u]==R&&dir[v]==L) G[u].push_back(v),++deg[v];
		}
	}
	queue <int> q;
	vector <int> ord;
	for(int i=1;i<=n;++i) if(!deg[i]) q.push(i);
	while(!q.empty()) {
		int p=q.front(); q.pop();
		ord.push_back(p);
		for(int v:G[p]) {
			--deg[v];
			if(!deg[v]) q.push(v);
		}
	}
	if((int)(ord.size())<n) {
		puts("NO");
		return 0;
	}
	for(int i=0;i<n;++i) pos[ord[i]]=i;
	puts("YES");
	for(int i=1;i<=n;++i) printf("%c %d\n",dir[i]==L?'L':'R',pos[i]);
	return 0;
}
```



---

## 作者：AmamiyaYuuko (赞：1)

根据题意，只要两辆车之间有关系，无论是相关还是不相关，这两辆车最开始面对的方向一定不同，那么有解时一定是二分图，首先黑白染色判断。

接下来考虑如何构造合法的解。假设 $i, j$ 相关，且 $i$ 朝向左，$j$ 朝向右，那么一定有 $x_i < x_j$。类似地可以得到其他关系。

看到这种式子不免让人想到差分约束，但是一种更简单的做法是利用拓扑序。若 $x_i < x_j$，就加边 $i \to j$，那么有解时一定形成了一个 DAG。对 DAG 进行拓扑排序，每个点的坐标即为该点的拓扑序。容易证明这样得到的答案是合法的。

注意判断无解的情况。

代码：

```cpp
#include <bits/stdc++.h>

template <class T>
inline void read(T &x) {
    x = 0;
    int f = 0;
    char ch = getchar();
    while (!isdigit(ch))    { f |= ch == '-'; ch = getchar(); }
    while (isdigit(ch))     { x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar(); }
    x = f ? -x : x;
    return ;
}

typedef unsigned long long uLL;
typedef long long LL;

struct Edge {
    int u, v, w;
} e[200010];

std::queue<int> q;
std::vector<int> g[200010];
int col[200010], d[200010], ans[200010];
int n, m, cnt;
bool vis[200010];

void dfs(int x, int c) {
    col[x] = c;
    for (auto i : g[x]) {
        if (col[i] && col[i] != 3 - c) {
            puts("NO");
            exit(0);
        } else if (!col[i]) {
            dfs(i, 3 - c);
        }
    }
}

int main() {
    read(n), read(m);
    for (int i = 1; i <= m; ++i) {
        read(e[i].w), read(e[i].u), read(e[i].v);
        g[e[i].u].push_back(e[i].v), g[e[i].v].push_back(e[i].u);
    }
    for (int i = 1; i <= n; ++i) {
        if (!col[i]) {
            dfs(i, 1);
        }
    }
    for (int i = 1; i <= n; ++i)    g[i].clear();
    for (int i = 1; i <= m; ++i) {
        if (e[i].w == 1) {
            if (col[e[i].u] == 1)    g[e[i].u].push_back(e[i].v), ++d[e[i].v];
            else    g[e[i].v].push_back(e[i].u), ++d[e[i].u];
        } else {
            if (col[e[i].u] == 1)    g[e[i].v].push_back(e[i].u), ++d[e[i].u];
            else    g[e[i].u].push_back(e[i].v), ++d[e[i].v];    
        }
    }
    for (int i = 1; i <= n; ++i) {
        if (!d[i]) {
            q.push(i);
            vis[i] = true;
        }
    }
    if (q.empty()) {
        puts("NO");
        return 0;
    }
    while (!q.empty()) {
        int u = q.front();
        vis[u] = true;
        ans[u] = ++cnt;
        q.pop();
        for (auto i : g[u]) {
            if (vis[i]) {
                puts("NO");
                return 0;
            }
            --d[i];
            if (!d[i])    q.push(i);
        }
    }
    if (cnt != n) {
        puts("NO");
        return 0;
    }
    puts("YES");
    for (int i = 1; i <= n; ++i)    printf("%c %d\n", col[i] == 1 ? 'L' : 'R', ans[i]);
    return 0;
}
```

---

## 作者：tommymio (赞：1)

作为一道合格的图论入门题，是整场 Round 唯一看上去不那么显然的题，我愿称这场 Round 为 Epic Boring。

观察可以发现，若车 $i,j$ 间存在关系，无论是否相遇，其方向必然相反。~~我在没完全看懂题意之前以为 $i,j$ 不相遇可以同向，直到我发现每个车的速度是任意的~~。于是可以想到染色，相邻的两个点颜色不同，若存在冲突即无解。那么这就是一个二分图判定。

确定了方向之后，考虑如何确认车的位置。不妨设对于相遇的两个点 $i,j$，$i$ 的方向为左，则 $j$ 的方向为右，显然有 $x_i>x_j$，对于不相遇的两个点也是同理。于是可以想到对于 $x_i<x_j$ 的约束建图，跑一个类似差分约束的东西。

时间复杂度为 $O(n)$。

```c++
/* stuff you should look for
	* int overflow, array bounds, uppercase/lowercase
	* special cases (n=1?)
	* do sth. instead of nothing and stay organized
	* WRITE STUFF DOWN
	* DON'T GET STUCK ON ONE APPROACH
*/
#include<cstdio>
#include<vector>
#include<queue>
struct Graph {
	void buildDirectedEdge(int x,int y) {
		mp[x].push_back(y);
	}
	void buildEdge(int x,int y) {
		mp[x].push_back(y);
		mp[y].push_back(x);
	}
	std::vector<int> mp[200005];	
}g1,g2;
struct edge {
	int op,x,y;
}e[200005];
int col[200005],a[200005],deg[200005];
inline int read() {
	int x=0,f=1; char s=getchar();
	while(s>'9'||s<'0') {if(s=='-') f=-1;s=getchar();}
	while(s>='0'&&s<='9') {x=x*10+s-'0';s=getchar();}
	return x*f;
}
inline void swap(int &x,int &y) {int tmp=x;x=y;y=tmp;}
inline bool bfs(int u) {
	std::queue<int> q;
	q.push(u); col[u]=1;
	while(q.size()) {
		int x=q.front(); q.pop();
		for(auto y:g1.mp[x]) {
			if(!col[y]) {
				col[y]=3-col[x];
				q.push(y);
			}
			else if(col[x]==col[y]) {
				return 0;
			}
		}
	}
	return 1;
}
inline bool topo(int n) {
	int tot=0;
	std::queue<int> q;
	for(int x=1;x<=n;++x) {
		if(!deg[x]) q.push(x);
	}
	while(q.size()) {
		int x=q.front(); q.pop(); 
		a[x]=++tot;
		for(auto y:g2.mp[x]) {
			if(!(--deg[y])) {
				q.push(y);
			}
		}
	}
	for(int x=1;x<=n;++x) {if(deg[x]) return 0;}
	return 1;
}
int main() {
	int n=read(),m=read(),tot=0;
	for(int i=1;i<=m;++i) {
		int op=read(),x=read(),y=read();
		e[++tot]=(edge){op,x,y};
		g1.buildEdge(x,y);
	}
	for(int i=1;i<=n;++i) {
		if(!col[i]) {
			if(bfs(i)) {} else {printf("NO\n"); return 0;}
		}
	}
	for(int i=1;i<=m;++i) {
		int x=e[i].x,y=e[i].y;
		if(col[x]==2) swap(x,y);//col[x]==1
		if(e[i].op==1) {g2.buildDirectedEdge(x,y); ++deg[y];}
		else {g2.buildDirectedEdge(y,x); ++deg[x];}
	}
	if(topo(n)) {
		printf("YES\n");
		for(int i=1;i<=n;++i) {
			printf("%c %d\n",col[i]==1? 'L':'R',a[i]);
		}
	}
	else {
		printf("NO\n");
	}
	return 0;
}

```


---

## 作者：xuyifei0302 (赞：0)

首先，对于两辆车而言，注定相遇就是相向而驰，注定不相遇就是背道而驰，没有关系的两辆车就是同向的。如果一辆车既向左开，又向右开，那么这种情况一定无解，输出 ```NO```。我们就可以用二分图染色的方法来判断它。然后方向确定了，我们还要考虑位置的问题。我们设第 $i$ 辆车的方向为右，第 $j$ 辆车的方向为左。如果这两辆车注定相遇，则第 $i$ 辆车的初始位置要小于第 $j$ 辆车的初始位置。如果这两辆车注定不相遇，则第 $i$ 辆车的初始位置要大于第 $j$ 辆车的初始位置。在二分图染色的过程中，我们可以对于一种颜色的汽车，将它们设为同一种方向。如果这些汽车的位置依赖关系存在环，则这种情况也一定无解，输出 ```NO```。所以我们就可以进行拓扑排序来判断是否有环，同时为每辆车赋上初始位置。然后输出即可。

下面是代码环节:

```cpp
#include<bits/stdc++.h>
using namespace std;
struct Node {
	int op, x, y;
} a[200005];
int n, m, color[200005], ans[200005], num[200005];
bool flag;
queue<int> q;
vector<int> v1[200005];
vector<pair<int, int>> v[200005];
void dfs(int u, int father) {
	for (auto i : v[u]) {
		if (i.first != father) {
			if (!color[i.first]) {
				color[i.first] = 3 - color[u];
				dfs(i.first, u);
			} else if (color[i.first] != 3 - color[u]) {
				flag = true;
			}
		}
	}
}
signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= m; i ++) {
		cin >> a[i].op >> a[i].x >> a[i].y;
		v[a[i].x].push_back({a[i].y, a[i].op});
		v[a[i].y].push_back({a[i].x, a[i].op});
	}
	for (int i = 1; i <= n; i ++) {
		if (!color[i]) {
			color[i] = 1;
			dfs(i, i);
		}
	}
	if (flag) {
		cout << "NO";
		return 0;
	}
	for (int i = 1; i <= m; i ++) {
		if (a[i].op == 1) {
			if (color[a[i].x] == 1) {
				v1[a[i].x].push_back(a[i].y);
				num[a[i].y] ++;
			} else {
				v1[a[i].y].push_back(a[i].x);
				num[a[i].x] ++;
			}
		} else if (a[i].op == 2) {
			if (color[a[i].x] == 1) {
				v1[a[i].y].push_back(a[i].x);
				num[a[i].x] ++;
			} else {
				v1[a[i].x].push_back(a[i].y);
				num[a[i].y] ++;
			}
		}
	}
	for (int i = 1; i <= n; i ++) {
		if (num[i] == 0) {
			q.push(i);
		}
	}
	int cnt = 0;
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		ans[u] = ++cnt;
		for (auto i : v1[u]) {
			num[i] --;
			if (num[i] == 0) {
				q.push(i);
			}
		}
	}
	for (int i = 1; i <= n; i ++) {
		if (ans[i] == 0) {
			cout << "NO";
			return 0;
		}
	}
	cout << "YES\n";
	for (int i = 1; i <= n; i ++) {
		if (color[i] == 1) {
			cout << "L " << ans[i] << "\n";
		} else {
			cout << "R " << ans[i] << "\n";
		}
	}
	return 0;
}
```

---

## 作者：ifffer_2137 (赞：0)

duel 上分题。
### 题意
有 $n$ 辆车。每辆车有一个初始位置（两两不同）和一个方向（左右），给定若干对关系，表示两辆车相对而行或相背而行，构造方案或报告无解。
### 分析
看着就很图论。

于是连一下边，由于连边的两辆车方向一定不同，所以有奇环就直接扬了（类似三值逻辑）。剩下合法的没有奇环，是个二分图，于是合法的黑白染色方案只有一种（容易发现交换所有车的方向本质相同）。然后相对和相背本质是告诉我们两个位置的大小关系，连一下有向边跑个拓扑判断一下有没有环即可，输出方案在染色和拓扑的时候就可以处理好了。
### 代码

```cpp
//From: ifffer_2137
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define inf 0x7fffffff
#define eb emplace_back
#define pii pair<int,int>
#define mkpr make_pair
#define fir first
#define sec second
inline int read(){
	char ch=getchar();int x=0,w=1;
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+ch-48,ch=getchar();return w==1?x:-x;
}
const int maxn=2e5+5;
int n,m,cnt;
int x[maxn];
vector<pii> G[maxn];
vector<int> iG[maxn];
int d[maxn],vis[maxn];
int col[maxn];
int ok;
vector<int> tmp;
bool topo(){
	for(int u:tmp){
		for(pii e:G[u]){
			int v=e.fir;
			if(col[u]){
				if(e.sec) iG[u].eb(v),d[v]++; 
			}else{
				if(!e.sec) iG[u].eb(v),d[v]++;
			}
		} 
	}
	queue<int> q;
	for(int u:tmp) if(!d[u]) q.push(u),vis[u]=1,x[u]=++cnt;
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int v:iG[u]){
			d[v]--;
			if(!d[v]) q.push(v),vis[v]=1,x[v]=++cnt;
		}
	}
	for(int x:tmp) if(d[x]) return false;
	return true;
}
void dfs(int u){
	tmp.eb(u);
	for(pii e:G[u]){
		int v=e.fir;
		if(col[v]!=-1){
			if(col[v]!=col[u]) continue;
			else ok=false;
			continue;
		}
		col[v]=col[u]^1;
		dfs(v);
	}
}
signed main(){
	#ifndef ONLINE_JUDGE
	freopen("data.in","r",stdin);
	freopen("test.out","w",stdout);
	#endif
	cin.tie(0),cout.tie(0);
	n=read(),m=read();
	for(int i=1;i<=m;i++){
		int w=read()-1,u=read(),v=read();
		G[u].eb(mkpr(v,w)),G[v].eb(mkpr(u,w));
	}
	for(int i=1;i<=n;i++) col[i]=-1;
	for(int i=1;i<=n;i++){
		if(col[i]==-1){
			col[i]=0,ok=1,tmp.clear();
			dfs(i);
			if(!ok){
				puts("NO");
				return 0;
			}
			if(topo()) continue;
			else{
				puts("NO");
				return 0;
			}
		}
	}
	puts("YES");
	for(int i=1;i<=n;i++){
		if(col[i]) cout<<"R ";
		else cout<<"L ";
		cout<<x[i]<<'\n';
	}
	cout<<'\n';
	return 0;
}
```

---

## 作者：Xdik (赞：0)

## 题意
有 $n$ 辆车，每个车有一个运行的方向（L 表示向左走，R 表示向右走）和初始位置，速度为任意值，这些都是不知道的，需要我们去求，已知的是 $m$ 个关系 。

$1$ $i$ $j$ 表示第 $i$ 辆车和第 $j$ 辆车必定不会相遇。

$2$ $i$ $j$ 表示第 $i$ 辆车和第 $j$ 辆车必定会相遇。

## Solution
考虑在何种情况下两辆车必定不会相遇，因为速度任意，所以两辆车不能是同一个方向，因为这样可能会发生追及，所以方向只能是一个向左一个向右，然后很容易就能得出向左走的那辆车必须在向右走的那辆车的左边。再考虑何种情况一定会发生相遇，发现与上一种情况一样，不能是同向的，因为这样不一定会发生追及，所以这两辆车的方向还是不一样，与上一种情况的区别就是向左走的那辆车必须在向右走的那辆车的右边，那么现在我们就发现有关系的两辆车它们的方向一定是不一样的，又因为只有 L 和 R 两种情况，所以很容易想到了二分图，于是我们用二分图染色跑一遍，如果出现了奇环就说明无解，现在我们得到了每辆车的方向之后就只用解决它们的位置。为要处理大小关系，所以一开始我的想法是差分约束系统，但是发现时间复杂度不正确。因为我们只用处理某个数比某个数小或者比某个数大的情况，所以可以用拓扑排序来解决。如果 $a_i < a_j$ 那么我们就从 $i$ 到 $j$ 连一条边，再来跑拓扑排序，最后得到的拓扑序肯定是一个合法的 $a$ 序列。为什么这样是对的呢？因为我们跑拓扑是按照入度为 0 才入队的，因为 $i$ 向 $j$ 连了一条边，所以肯定是 $i$ 出队了 $j$ 才可能入队，所以就满足了 $a_i < a_j$ 的条件。

因为二分图的时间复杂度为 $O(n)$ 拓扑排序的时间复杂度也为 $O(n)$ 所以总的时间复杂度也是 $O(n)$ 。

这道题结合了二分图和拓扑排序，还是挺有价值的。

AC code:
```cpp
#include<bits/stdc++.h>
#define int long long
#pragma GCC optimeze(2)
#pragma GCC optimeze(3)
#define lowbit(x) (x&(-x))
#define fi first	
#define PII pair<int,int> 
#define se second 
#define pu(x) push_back(x)
using namespace std;
const int N=2e5+5;
int read() {
	int x=0,flag=1;
	char ch=0;
	while(ch<'0'||ch>'9') {
		if(ch=='-')flag=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	return flag*x;
}
void write(int x) {
  if(x<0)putchar('-'),x=-x; 
  static int sta[35];
  int top = 0;
  do {
    sta[top++] = x % 10, x /= 10;
  } while (x);
  while (top) putchar(sta[--top] + 48);
}
int n,m,in[N],ans[N],c[N],head[N],ver[N*2],ne[N*2],op[N],u[N],v[N],tot,cnt;
vector<int>G[N];
void add(int x,int y){
	ver[++tot]=y,ne[tot]=head[x],head[x]=tot;
}
void dfs(int t,int co){
	c[t]=co;
	for(int i=head[t];i;i=ne[i]){
		int to=ver[i];
		if(c[to]){
			if(c[to]==c[t]){
				cout<<"NO";
				exit(0);
			}
		}
		else dfs(to,3-co);
	}
}
signed main() {
	n=read(),m=read();
	for(int i=1;i<=m;i++){
		op[i]=read(),u[i]=read(),v[i]=read();
		add(u[i],v[i]),add(v[i],u[i]);
	}
	for(int i=1;i<=n;i++){
		if(!c[i])dfs(i,1);
	}
	for(int i=1;i<=m;i++){
		if(op[i]==1){
			if(c[u[i]]==1)G[u[i]].push_back(v[i]),in[v[i]]++;
			else G[v[i]].push_back(u[i]),in[u[i]]++;
		}
		else{
			if(c[u[i]]==2)G[u[i]].push_back(v[i]),in[v[i]]++;
			else G[v[i]].push_back(u[i]),in[u[i]]++;
		}
	}
	queue<int>q;
	for(int i=1;i<=n;i++){
		if(!in[i])q.push(i);
	
	while(q.size()){
		int t=q.front();
		q.pop();
		ans[t]=++cnt;
		for(auto to:G[t]){
			in[to]--;
			if(!in[to])q.push(to);
		}
	}
	if(cnt<n){
		cout<<"NO";
	}
	else{
		puts("YES");
		for(int i=1;i<=n;i++){
			cout<<(c[i]==1? 'L':'R')<<" "<<ans[i]<<endl;
		}
	}
	return 0;
}

---

## 作者：wangyutian111 (赞：0)

根据题意可以发现，不管两辆车是怎样的关系，方向都是相反的。于是我们考虑运用二分图染色去判定是否有解。随后我们就可以根据这几辆车的位置大小关系建边，进行拓扑排序，排出来的名次就可以作为最后的答案。

代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+10;
#define int long long
bool vis[maxn];
int t,n,m,col[maxn],in[maxn],ans[maxn],cnt;
struct f{
	int z,u,v;
}a[maxn];
vector<int> ma[maxn],maa[maxn];
queue<int> q;
int dfs(int u,int c){
	col[u]=c;
	vis[u]=1;
	for(int v:ma[u]){
		if(col[v]==c){
			return 0;
		}
		if(col[v]==-1&&!dfs(v,c^1)){
			return 0;
		}
	}
	return 1;
}
int tp(){
	for(int i=1;i<=n;i++){
		if(in[i]==0){
			q.push(i);
			cnt++;
			ans[i]=cnt;
		}
	}
	while(!q.empty()){
		int u=q.front();
		q.pop();
		for(int v:maa[u]){
			in[v]--;
			if(in[v]==0){
				cnt++;
				ans[v]=cnt;
				q.push(v);
			}
		}
	}
	if(cnt!=n){
		return 0;
	}
	else{
		return 1;
	}
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		col[i]=-1;
		vis[i]=0;
		ma[i].clear();
	}
	for(int i=1;i<=m;i++){
		cin>>a[i].z>>a[i].u>>a[i].v;
		ma[a[i].u].push_back(a[i].v);
		ma[a[i].v].push_back(a[i].u);
	}
	bool flag=0;
	for(int i=1;i<=n;i++){
		if(!vis[i]){
			int z=dfs(i,0);
			if(z==0){
				flag=1;
			}
		}
	}
	if(flag==1){
		cout<<"NO"<<endl;
		return 0;
	}
	for(int i=1;i<=m;i++){
		if(col[a[i].u]!=0){
			swap(a[i].u,a[i].v);
		}
		if(a[i].z==1){
			in[a[i].v]++;
			maa[a[i].u].push_back(a[i].v);
		}
		else{
			in[a[i].u]++;
			maa[a[i].v].push_back(a[i].u);
		}
	}
	int pan=tp();
	if(pan==0){
		cout<<"NO";
		return 0;
	}
	cout<<"YES"<<endl;
	for(int i=1;i<=n;i++){
		if(col[i]==0){
			cout<<"L"<<" ";
		}
		else{
			cout<<"R"<<" ";
		}
		cout<<ans[i]<<endl;
	}
	return 0;
}
```

---

## 作者：Zhuluoan (赞：0)

## 题目简述
一条数轴上有 $n$ 辆车，每辆车都可以向左或向右定向移动，并且可以随时以任何恒定的正速度沿该方向移动。两辆车之间可以有以下两种关系：

- 如果两辆汽车无论速度如何都永远不会到达同一点，我们称它们为 **无关紧要的**。

- 如果两辆汽车无论速度如何，它们一定会到达同一点，我们称它们为 **命中注定的**。

现在给定 $m$ 条关系，你要确定每辆车初始的位置与方向，满足这 $m$ 条关系。

## 题目分析
首先，我们可以通过模拟发现如果两辆车是 **无关紧要的**，它们只能是相背而行。同理，如果两辆车是 **命中注定的**，它们则是相对而行。也就是说，无论给出那种关系，他们的方向必定是相反的，这启发我们使用二分图染色来确定他们的方向。

如果不是二分图，那必定无解。如果是，我们就让染成黑色的向左行驶，染成白色的向右行驶。当然，相反也是可以的。

接下来，我们考虑如何确定他们的位置，我们可以枚举每一对关系，为了方便一些，我们设 $i$ 为向右行驶的车，$j$ 为向左行驶的车。我们分成两种情况来讨论：

- 如果两辆车是 **命中注定的**，那么 $i$ 一定在 $j$ 的前方，读者可以画图模拟一下，这说明 $i$ 的坐标 $x_i$ 一定小于 $j$ 的坐标 $x_j$，即 $x_i \lt x_j$。

- 同理，如果两辆车是 **无关紧要的**，那么 $j$ 一定在 $i$ 的前方，这说明 $x_j \lt x_i$。

现在问题被转化成了给出 $m$ 条形如 $A \lt B$ 的关系，让你对其排序。我们可以利用 [P1347 排序](https://www.luogu.com.cn/problem/P1347) 的做法，分别建立一条 $A \to B$ 的有向边，再进行拓扑排序，最后按出队顺序赋值即可，当然，如果图中有环的话就是无解。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int n,m,opt[N],x[N],y[N],col[N],tot,ans[N],in[N];
vector<int> G1[N],G2[N];
queue<int> q;
bool dfs(int u,int c)
{
	col[u]=c;
	for(int v:G1[u])
	{
		if(col[v]==c||(col[v]==-1&&!dfs(v,c^1))) return 0;
	}
	return 1;
}
bool topo()
{
	for(int i=1;i<=n;i++)
	{
		if(!in[i]) q.push(i);
	}
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		ans[u]=tot++;
		for(int v:G2[u])
		{
			if(!(--in[v]))
			{
				q.push(v);
			}
		}
	}
	return tot<n?1:0;
}
int main()
{
	cin>>n>>m;
	memset(col,-1,sizeof col);
	for(int i=1;i<=m;i++)
	{
		cin>>opt[i]>>x[i]>>y[i];
		G1[x[i]].push_back(y[i]);
		G1[y[i]].push_back(x[i]);
	}
	for(int i=1;i<=n;i++)
	{
		if(col[i]==-1)
		{
			if(!dfs(i,0))
			{
				printf("NO\n");
				return 0;
			}
		}
	}
	for(int i=1;i<=m;i++)
	{
		if(opt[i]==1)
		{
			if(col[x[i]]==1&&col[y[i]]==0)
			{
				G2[y[i]].push_back(x[i]);
				in[x[i]]++;
			}
			else
			{
				G2[x[i]].push_back(y[i]);
				in[y[i]]++;
			}
		}
		else
		{
			if(col[x[i]]==1&&col[y[i]]==0)
			{
				G2[x[i]].push_back(y[i]);
				in[y[i]]++;
			}
			else
			{
				G2[y[i]].push_back(x[i]);
				in[x[i]]++;
			}
		}
	}
	if(topo())
	{
		printf("NO");
		return 0;
	}
	printf("YES\n");
	for(int i=1;i<=n;i++)
	{
		cout<<(!col[i]?'L':'R')<<" "<<ans[i]<<"\n";
	}
	return 0;
}
```

---

## 作者：peterwuyihong (赞：0)

一道有关于車的有趣的题。

题意：给定 $n$ 辆車，给定若干关系形如 $x,y$ 車必定相向，或必定背向，构造一种所有車的朝向和横坐标，若无解输出 NO。

看到这个题，我首先的想法是 yy 出 $2n$ 个节点，$n$ 个表示第 $i$ 辆車向左，另外表示第 $i$ 辆車向右，然后按并查集那个套路来，结果发现两种关系本质是一样的，弃了。

转而往图伦上去考虑，发现每种关系都是两个車异向，不可能有奇环，有奇环必无解。

那么没有奇环必定有解吗？

首先定向可以凭借二分图染色解决，那么坐标如何解决呢？

我把向右的車掏出来，让相向关系的点连向它，让它连向背向关系的点，于是乎，这里连边的关系也变得明了了，就是横坐标靠左的连到靠右的，这个时候做一个拓扑排序就行了。

这个时候如果出现环了，也是没有解的，这里卡了很久。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define rep(i,j,k) for(int i=j;i<=(k);i++)
#define per(i,j,k) for(int i=j;i>=(k);i--)
#define all(x) x.begin(),x.end()

vector<int>color(vector<vector<int> >g){
  int n=g.size();
  vector<int>ans(n,-1);
  bool gg=0;
  function<void(int,int)>dfs=[&](int x,int c){
    if(gg)return;
    if(~ans[x]){
      if(ans[x]!=c)gg=1;
      return;
    }
    ans[x]=c;
    for(int y:g[x])dfs(y,c^1);
  };
  rep(i,0,n-1)if(ans[i]==-1)dfs(i,0);
  if(gg)return{};
  return ans;
}
vector<int>topsort(vector<vector<int> >g){
  int n=g.size();
  vector<int>in(n);
  for(int i=0;i<n;i++)
  for(int j:g[i])in[j]++;
  queue<int>q;
  vector<int>ans;
  for(int i=0;i<n;i++)if(!in[i])q.push(i);
  while(q.size()){
    int x=q.front();q.pop();
    for(int y:g[x])
      if(--in[y]==0)q.push(y);
    ans.push_back(x);
  }
  return ans;
}
signed main(){
  ios::sync_with_stdio(NULL);
  int n,m;
  cin>>n>>m;
  vector<vector<int> >g(n);
  vector<array<int,3> >v(m);
  for(auto&[op,x,y]:v){
    cin>>op>>x>>y,x--,y--;
    g[x].push_back(y);
    g[y].push_back(x);
  }
  auto C=color(g);
  if(C.size()==0)return cout<<"NO",0;
  g.clear();g.resize(n);
  for(auto[op,x,y]:v){
    if(C[x]==0&&op==1)swap(x,y);
    if(C[x]==1&&op==2)swap(x,y);
    g[x].push_back(y);
  }
  auto t=topsort(g);
  vector<int>pos(n);
  if(t.size()!=n)return cout<<"NO",0;
  rep(i,0,n-1)pos[t[i]]=i;
  cout<<"YES"<<endl;
  rep(i,0,n-1)
    cout<<(C[i]?"L":"R")<<' '<<pos[i]<<endl;
}
```

---

## 作者：enucai (赞：0)

## Preface

想了一会儿的，如果打了这场可能要掉分了。

## Analysis

两辆车 irrelevant **当且仅当** 两辆车背向而驰。

两辆车 destined **当且仅当** 两辆车相向而行。

因此我们对每一对有 irrelevant 或 destined 关系的车之间建一条边，表示他们行驶的方向相反。

如果构造出的图不是二分图，则一定无解。

否则用一遍 Dfs 对二分图进行黑白染色，黑的点向左开，白的点向右开。复杂度 $O(n)$。

为了分配各车的位置，我们还要进行一次拓扑排序。复杂度 $O(m)$。

最终复杂度 $O(n+m)$，轻松通过此题。

## Code

**Talk is cheap, show me the code.**

[Codeforce Status](https://codeforces.com/contest/1635/submission/147480887)

```cpp
#define int long long
struct node{
	int type,x,y;
}a[200010];
int n,m,col[200010],in[200010],pos[200010],tot=0;
vi e[200010],g[200010];
queue<int> q;
void dfs(int u,int c){
	col[u]=c;
	for(auto v:e[u]) if(col[v]==c) puts("NO"),exit(0);
	for(auto v:e[u]) if(!col[v]) dfs(v,-c);
}
signed main(){
	read(n,m);
	For(i,1,m) read(a[i].type,a[i].x,a[i].y);
	For(i,1,m) e[a[i].x].pb(a[i].y),e[a[i].y].pb(a[i].x);
	For(i,1,n) if(!col[i]) dfs(i,-1);
	For(i,1,m){
		if(col[a[i].x]==1) swap(a[i].x,a[i].y);
		if(a[i].type==1) g[a[i].x].pb(a[i].y),in[a[i].y]++;
		else g[a[i].y].pb(a[i].x),in[a[i].x]++;
	}
	For(i,1,n) if(in[i]==0) q.push(i);
	while(!q.empty()){
		int u=q.front();q.pop();
		pos[u]=++tot;
		for(auto v:g[u]){
			in[v]--;
			if(in[v]==0) q.push(v);
		}
	}
	if(tot!=n) puts("NO"),exit(0);
	puts("YES");
	For(i,1,n){
		if(col[i]==-1) printf("L %lld\n",pos[i]);
		else printf("R %lld\n",pos[i]);
	}
}
```

---

## 作者：Duramente (赞：0)

## 题意
有 $n$ 辆车，每辆车朝向左或者右。  
有 $m$ 条性质形如：第 $i$ 辆车和第 $j$ 辆车朝着自己的方向按照任意的速度行驶，总会相遇或不可能相遇。    

构造合法的满足条件的解，要求给出每辆车的朝向和位置

## Solution  
分析发现，总会相遇的情况只有两个车面对面，即为 ```
R L``` 这个样子的。  
永远不会相遇的情况只有两个车背对背，即为 ```L R``` 这个样子的。  
所以对于每个限制，第 $i$ 辆车和第 $j$ 辆车的朝向是相反的，因此可以想到二分图染色，如果不能染成一个合法的二分图，就一定是无解的情况。  

二分图染色后，每个点都已经标好了方向。我们来讨论一个朝向为 ```L``` 的点。  
另外的 ```L``` 和他一定没有限制，所以只需要考虑剩下的和他有限制的 ```R```。   
和他总会相遇的 ```R``` 一定在他的左侧，和他不可能相遇的 ```R``` 一定在他的右侧，没有限制的 ```R``` 放哪里和他无关。  

我们从左往右放所有的车，因此，想要放一个 ```L``` 时，需要先把所有总会和他相遇的 ```R``` 先放好；想要放一个 ```R``` 时，需要把所有不可能和他相遇的 ```L``` 先放好。对于这种有依赖性的图的关系，可以联想到拓扑排序。拓扑排序安放所有的车即可，有环无解。

## Code
```cpp
#include<bits/stdc++.h>
#define forn(i,a,b)for(int i=(a),_b=(b);i<=_b;i++)
#define fore(i,b,a)for(int i=(b),_a=(a);i>=_a;i--)
#define rep(i,n)for(int i=0,_n=n;i<n;i++)
#define ll long long
#define pii pair<int,int>
#define m_p make_pair
#define pb push_back
#define fi first
#define se second
#define int ll
#define foreach(i,c) for(__typeof(c.begin())i=(c.begin());i!=(c).end();i++)
using namespace std;
const int N=200010;
int n,m;
vector<int>g[N];
struct qry{
	int t,u,v;
}q[N]; 
int c[N],ans[N],in[N];
void dfs(int u,int cl){
	c[u]=cl;
	rep(i,g[u].size()){
		int v=g[u][i];
		if(c[v]!=-1){
			if(cl^1!=c[v]){
				cout<<"NO\n";
				exit(0);
			}
		}
		else{
			dfs(v,cl^1);
		}
	}
}
signed main(){
    cin.tie(0);
	ios::sync_with_stdio(0);
	cin>>n>>m;
	forn(i,1,m){
		cin>>q[i].t>>q[i].u>>q[i].v;
		g[q[i].u].pb(q[i].v);
		g[q[i].v].pb(q[i].u);
	}
	memset(c,-1,sizeof(c));
	forn(i,1,n){
		if(c[i]==-1){
			dfs(i,0);
		}
	}
	forn(i,1,n){
		g[i].clear();
	}
	forn(i,1,m){
		if(c[q[i].u]==1)swap(q[i].u,q[i].v);
		if(q[i].t==1){
			g[q[i].u].pb(q[i].v);
			in[q[i].v]++;
		}
		else{
			g[q[i].v].pb(q[i].u);
			in[q[i].u]++;
		}
	}
	queue<int>q;
	forn(i,1,n){
		if(!in[i])q.push(i);
	}
	int cnt=0;
	while(!q.empty()){
		int u=q.front();q.pop();
		cnt++;
		ans[u]=cnt;
		rep(i,g[u].size()){
			int v=g[u][i];
			in[v]--;
			if(!in[v]){
				q.push(v);
			}
		}
	}
	if(cnt!=n){
		cout<<"NO\n";
		return 0;
	}
	cout<<"YES\n";
	forn(i,1,n){
		if(c[i])cout<<"R ";
		else cout<<"L ";
		cout<<ans[i]<<"\n";
	}
	return 0;
}



---

