# One-Way Reform

## 题目描述

There are $ n $ cities and $ m $ two-way roads in Berland, each road connects two cities. It is known that there is no more than one road connecting each pair of cities, and there is no road which connects the city with itself. It is possible that there is no way to get from one city to some other city using only these roads.

The road minister decided to make a reform in Berland and to orient all roads in the country, i.e. to make each road one-way. The minister wants to maximize the number of cities, for which the number of roads that begins in the city equals to the number of roads that ends in it.

## 样例 #1

### 输入

```
2
5 5
2 1
4 5
2 3
1 3
3 5
7 2
3 7
4 2
```

### 输出

```
3
1 3
3 5
5 4
3 2
2 1
3
2 4
3 7
```

# 题解

## 作者：Erina (赞：6)

首先证明一下最大的入度等于出度的点就是偶数度点的数量......

怎么证呢? 构造.

加一个虚节点, 然后把它和所有奇数度的点连起来, 那么所有点的度数都是偶数, 这个图必定有一个欧拉回路, 也就是一个经过所有边一次的路径.

这样所有偶数度的节点入度和出度都是总度数的一半, 是相等的......

然后...... 就没有然后了......

放一下代码......

```cpp
#include<iostream>
#include<unordered_set>// 哈希表代替set去掉O(lgn)的复杂度
#include<vector>
#include<algorithm>
using namespace std;
namespace fio {
	streambuf* in = cin.rdbuf();
	char bb[1000000], * s = bb, * t = bb;
#define gc() (s==t&&(t=(s=bb)+in->sgetn(bb,1000000),s==t)?EOF:*s++)
	inline int read() {// 快读 背下来就好, 卡常利器
		int x = 0;
		char ch = gc();
		while (ch < 48)ch = gc();
		while (ch >= 48)x = x * 10 + ch - 48, ch = gc();
		return x;
	}
}using fio::read;
int n, m;
unordered_set<int>road[100005];// 存储边
typedef pair<int, int>mp;
vector<mp>alb;// 阿鲁巴~~~~其实是答案
void dfs(int x) {// 欧拉回路, 用搜索给变定向
	while (road[x].size()) {
		int nex = *road[x].begin();
		road[x].erase(nex);
		road[nex].erase(x);
		alb.push_back(mp(x, nex));
		dfs(nex);
	}
}
void solve() {
	n = read(), m = read();
	int cnt = 0;
	for (int i = 1; i <= m; i++) {// 建图
		int l = read(), r = read();
		road[l].insert(r);
		road[r].insert(l);
	}
	for (int i = 1; i <= n; i++)
		if (road[i].size() & 1)
			road[i].insert(0), road[0].insert(i), cnt++;// 连接虚节点对应的边
	for (int i = 1; i <= n; i++)
		dfs(i);
	cout << n - cnt << endl;// 偶数度数的节点个数
	for (mp it : alb)
		if (min(it.first, it.second))
			cout << it.first << ' ' << it.second << endl;// 记住不要把虚节点输出了, CF上cout跑的出奇的快, 无需卡常......
	alb.clear();
}
int main() {
	int t = read();
	while (t--)solve();// 为什么CF的题目还会有多组数据......
}
```


---

## 作者：Peter_Z (赞：4)

### 写在前面

~~我太蒻了欧拉回路都能写错qwq~~

需要点亮的技能：

1.邻接矩阵存图&记录点度数

2.判断欧拉回路的存在性

3.求一个图的欧拉回路

## 大致思路

首先应该了解两个概念：

奇点：无向图中连接奇数条边的点。

偶点：无向图中连接偶数条边的点。

思考怎样的点才能让入度=出度：

入度=出度，说明这个点连出或连入了偶数条边，即它在无向图里是一个偶点。

同理入度不等于出度的点一定是无向图中的奇点。

因此，答案的上界一定是图中的偶点个数。

~~答案的下界应该是0……那不是一个很显然的二分？~~

这里多画几个图手算一下，就可以发现，所有图都可以构造出所有偶点的入度=出度的情况。

因此，这里考虑怎样构造出这样的情况。

由于有一些点是奇点，另一些是偶点，处理奇点会比较繁琐，

因此新建一个点S，让它与图中所有的奇点连边，然后图中所有的奇点就都变成了偶点。

又因为图中奇点的个数显然是偶数，所以S也是一个偶点。

因此这个图必定存在欧拉回路（欧拉回路：从起点开始，经过所有边一次，最后又回到起点）。

把搜索欧拉回路时边的方向设为最后的方向，就是题目要求的情况。

正确性需要yy一下：

对于一个偶点x，设它连着2k条边。

则每次搜到它时会从一条边进入，从另一条边出去。

进去和出去的边是不会重复的，因此进入它的边数为k，从它出去的边数也为k。

因此满足题意。

于是得出解法——求出ans（偶点的个数），然后跑一遍欧拉回路，回路中边的方向即为答案的方向。

## 放 ~~毒瘤~~ 代码：

```cpp
/*n方过百万 暴力碾标算*/
/*大力出奇迹 骗分过样例*/
/*爆搜挂着机 打表出省一*/
//我好菜啊qwq
#include<stdio.h>
#include<cstring>
#include<algorithm>
#include<queue>
#define re register int
using namespace std;
typedef long long ll;
int read() {
    re x=0,f=1;
    char ch=getchar();
    while(ch<'0' || ch>'9') {
        if(ch=='-')	f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9') {
        x=10*x+ch-'0';
        ch=getchar();
    }
    return x*f;
}
const int Size=205;
const int INF=0x3f3f3f3f;
int n,m,S,cnt,indegree[Size];
int to[Size][Size];
void dfs(int x) {
	//dfs求欧拉回路
    for(int i=1; i<=S; i++) {
        if(to[x][i]) {
        	//把这条边删去
            to[x][i]=to[i][x]=0;
            if(x!=S && i!=S) {
                printf("%d %d\n",x,i);
            }
            dfs(i);
        }
    }
}
int main() {
    int T=read();
    while(T--) {
        memset(to,0,sizeof(to));
        memset(indegree,0,sizeof(indegree));
        n=read();
        m=read();
        for(re i=1; i<=m; i++) {
            int u=read();
            int v=read();
            to[u][v]=to[v][u]=1;
            //统计这个点的度数
            indegree[u]++;
            indegree[v]++;
        }
        S=n+1;
        int ans=0;
        for(re i=1; i<=n; i++) {
            if(indegree[i]&1) {
                to[i][S]=to[S][i]=1;
                indegree[S]++;
                indegree[i]++;
            } else {
            	//ans为偶点个数
                ans++;
            }
        }
        printf("%d\n",ans);
        for(re i=1; i<=n; i++) {
        //对于每个点都要跑一遍 
        	dfs(i);
    	}
    }
    return 0;
}
```

---

## 作者：FutaRimeWoawaSete (赞：4)

考虑这个问题的上界。              

显然如果一个点的入度等于出度，那么显然这个点的度数为偶数。        

那么我们知道这个问题的上界答案就是度数为偶数的点数。            

联想到所有点入度等于出度是一个有向图具有欧拉回路的充要条件，由于无向图的欧拉回路可以通过对于边指定方向转化为有向图欧拉回路，我们考虑建立一个虚点 $0$，让所有奇点向 $0$ 连一条边，所有除 $0$ 以外的点就都是偶点了。       

最后把 dfs 出来的无向图欧拉回路转换成一个有向图欧拉回路就可以构造出一种使得所有偶点的入度都等于出度的方案，取到了答案的上界就结束了。

时间复杂度 $O(tn^2)$。          

```cpp
#include "bits/stdc++.h"
using namespace std;
const int Len = 205;
int n,m,deg[Len],mp[Len][Len],st[Len],res;
bool flag[Len];
vector<int> v[Len];
struct Node
{
	int x,y;
	Node(){x = y = 0;}
	Node(int X,int Y){x = X , y = Y;}
};
vector<Node> Print;
void dfs(int x)
{
	flag[x] |= 1;
	for(int i = 0 ; i < v[x].size() ; i = max(i + 1 , st[x]))
	{
		int to = v[x][i];
		if(!mp[x][to]) continue;
		mp[x][to] -- , mp[to][x] --;
		if(x && to) Print.push_back(Node(x , to));
		st[x] = i + 1;
		dfs(to);
	}
}
int main()
{
	int t;
	scanf("%d",&t);
	while(t --)
	{
		scanf("%d %d",&n,&m);Print.clear();
		memset(deg , 0 , sizeof deg);
		memset(flag , 0 , sizeof flag);
		for(int i = 1 ; i <= m ; i ++)
		{
			int x,y;scanf("%d %d",&x,&y);
			v[x].push_back(y) , v[y].push_back(x);
			mp[x][y] ++ , mp[y][x] ++;
			deg[x] ++ , deg[y] ++;
		}
		res = 0;
		for(int i = 1 ; i <= n ; i ++) 
		{
			res += (deg[i] % 2 == 0);
			if(deg[i] % 2 == 1) 
			{
				v[i].push_back(0) , v[0].push_back(i);
				mp[i][0] ++ , mp[0][i] ++;
			}
		}
		for(int i = 1 ; i <= n ; i ++) if(!flag[i]) dfs(i);
		printf("%d\n",res);
		for(int i = 0 ; i < Print.size() ; i ++) printf("%d %d\n",Print[i].x,Print[i].y); 
		for(int i = 0 ; i <= n ; i ++)
		{
			st[i] = deg[i] = flag[i] = 0;
			for(int j = 0 ; j < v[i].size() ; j ++) mp[i][v[i][j]] = mp[v[i][j]][i] = 0;
			v[i].clear();
		}
	}
	return 0;
}
```

---

## 作者：qfy123 (赞：2)

# CF723E
[传送门](https://www.luogu.com.cn/problem/CF723E)
## 思路
~~一道比较水的紫题。~~

想要让一个有向图其中的一些点入度等于出度，那它入边、出边的总和一定是偶数，在无向图中，就是一个偶点。因此，**无向图中偶点的个数等于这个无向图改为有向图后入度等于出度的点的最大数量**。于是我们统计无向图中偶点的个数并输出即可。

现在考虑构造方案。由于题目所给无向图中既有奇点，又有偶点，直接处理奇点比较麻烦。因此，我们可以考虑建立一个虚拟节点 $V$，将其与所有奇点连一条无向边，这样就可以将所有奇点变为偶点，然后就能跑欧拉回路了，边跑边输出方案就行。

正确性证明：跑欧拉回路时，每经过一次偶点，都会从一条边进，删掉跑过的那条无向边，并从另一条边出，正好满足有向图中入度等于出度的限制条件。

具体实现见代码，还是比较清晰的。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 210;
int g[N][N],n,m,T,ans,deg[N];
void dfs(int u){
	for(int i=1;i<=n+1;i++){
		if(g[u][i]){
			g[u][i] = g[i][u] = 0;
			dfs(i);
			if(u==n+1 || i==n+1) continue;//原图中不存在虚拟节点，因此判断这条边的两个端点都不是虚拟节点时才能输出
			printf("%d %d\n",u,i);
		}
	}
}
int main(){
	scanf("%d",&T);
	while(T--){
		ans = 0;
		memset(deg,0,sizeof(deg));
		memset(g,0,sizeof(g));
		scanf("%d%d",&n,&m);
		for(int i=1;i<=m;i++){
			int u,v;
			scanf("%d%d",&u,&v);
			g[u][v] = g[v][u] = 1;
			deg[v]++;deg[u]++;
		}
		for(int i=1;i<=n;i++){
			if(deg[i]&1) g[i][n+1] = g[n+1][i] = 1;//如果是奇点，与虚拟节点连一条无向边
			else ++ans;//统计偶点个数
		}
		printf("%d\n",ans);
		for(int i=1;i<=n;i++) dfs(i);
	}	
	return 0;
}
```
[AC记录](https://www.luogu.com.cn/record/164138350)

---

## 作者：_HwH_ (赞：2)

* [传送门](https://www.luogu.com.cn/problem/CF723E)


## 分析
首先，乍一看本题可能没有思路，但是手推一下这几组样例：
* 样例一

![](https://cdn.luogu.com.cn/upload/image_hosting/hvgjaqu5.png?x-oss-process=image/resize,m_lfit,h_170,w_225 "样例一")

其中入度等于出度的点为 **1,2,5**

* 样例二

![](https://cdn.luogu.com.cn/upload/image_hosting/s1rdbtr2.png?x-oss-process=image/resize,m_lfit,h_170,w_225 "样例二")

其中入度等于出度的点为 **1,5,6**

由此，我们可以发现，所以的入度等于出度的点，其入度与出度之和为偶数，于是我们可以猜想：最大化的满足入度等于出度的点，那么其中满足条件的节点的出度与入度之和为偶数

#### 证明：
显然，图中的满足入度等于出度的点，所有与其相连的出边会且仅会被遍历到一次，依次类推，与其相连的所有入边都只会被遍历到一次，那么如果出度等于入度，该点的总度数必然为 $2\times k$ 次， 那么我们如果要最大化入度等于出度的点的数量，那么就需要尽量的构造出出入度之和为偶数的点

## Solution
由上面的分析，我们可以发现，如果想要最大化图中入度与出度和为偶数的点，我们可以增加一个超级点 $x$ ，并让 $x$ 点与其他本身入度与出度和为奇数的点两边，这样，图中的所有点的入度与出度和均为偶数

那么，如果我们把这个图看为一个无向图，显然，此时的整个图边存在一个欧拉回路（或者说一个有向图存在欧拉回路的充要条件为所有顶点的入度等于出度且该图是连通图），那么我们只要跑一遍欧拉回路即可解决问题，总共的满足条件的节点个数即为原图中本身的总度数是偶数的点的数量

## Code
```
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<math.h>
#include<vector>
#define ll long long
using namespace std;

const ll maxn=210;
ll t,n,m,ret,pos;
ll used[maxn][maxn],sum[maxn];

inline void dfs(ll x)//欧拉回路 dfs 板子
{
	for(int i=1;i<=pos;i++)
	{
		if(used[x][i])
		{
			used[x][i]=0;
			used[i][x]=0;
			
			if(i!=pos&&x!=pos)
			{
				printf("%lld %d\n",x,i);
			}
			
			dfs(i);
		}
	}
}

int main(void)
{
	scanf("%lld",&t);
	
	while(t--)
	{
		ret=0,pos=0;
		memset(sum,0,sizeof(sum));
		memset(used,0,sizeof(used));
		
		scanf("%lld%lld",&n,&m);
		
		for(int i=1;i<=m;i++)
		{
			ll x,y;
			scanf("%lld%lld",&x,&y);
			used[x][y]=1;
			used[y][x]=1;
			sum[x]++;
			sum[y]++;
		}
		
		pos=n+1;
		
		for(int i=1;i<=n;i++)
		{
			if(sum[i]%2==1)
			{
				used[pos][i]=used[i][pos]=1;
			}
			else ret++;
		}
		
		printf("%lld\n",ret);
		
		for(int i=1;i<=n;i++)
		{
			dfs(i);
		}
	}
	
	return 0;
}
```


---

## 作者：_Cheems (赞：1)

称度数为偶数的点为偶数点，反之为奇数点。

首先答案上界必定是偶数点数量。

尝试构造到上界。由于欧拉回路上的点必定入度 $=$ 出度，所以如果构造出一个欧拉回路图，那么就能卡到上界了。

有个结论：无向图奇数点数量必定为偶数。证明也很简单，总度数为偶数嘛。

所以让奇数点两两相连即可，为了省事可以让它们统一连向一个虚点。这也是欧拉路一类问题的常用套路了。

然后在新图上跑欧拉回路，跟着回路来定向，如果是原来的边就输出即可。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 2e2 + 5;
int T, n, m, ans, ct[N][N], u, v;
bool was[N];
vector<int> to[N];

inline void add(int u, int v) {to[u].push_back(v), ++ct[u][v];}
inline void dfs(int u){
	was[u] = 1;
	for(auto v : to[u]){
		if(!ct[u][v]) continue;
		--ct[u][v], --ct[v][u];
		if(u && v) printf("%d %d\n", u, v);
		dfs(v);
 	}
}
inline void calc(){
	memset(ct, 0, sizeof ct);
	for(int i = 0; i < N; ++i) was[i] = 0, to[i].clear();
	cin >> n >> m, ans = n;
	for(int i = 1; i <= m; ++i) 
		scanf("%d%d", &u, &v), add(u, v), add(v, u);
	for(int i = 1; i <= n; ++i)
		if(to[i].size() & 1) --ans, add(0, i), add(i, 0);
	printf("%d\n", ans);
	for(int i = 1; i <= n; ++i) if(!was[i]) dfs(i);
}
int main(){
	cin >> T;
	while(T--) calc();
	return 0;
}
```

---

## 作者：Lucius7 (赞：1)

有向图中入度等于出度的点的必要条件是在无向图中（有向图的有向边变成无向边）一定是偶点。可以发现构造方法：在求无向图欧拉回路的 DFS 算法，DFS 的方向作为有向图的边的方向，得到的有向图的点入度等于出度。

但是题目给出的无向图不一定是欧拉图。创建一个虚拟源点，将无向图中的奇点与虚拟源点相连。奇点就变成了偶点。因为奇点一定是偶数个，所以虚拟源点也是偶点。这个无向图就是欧拉图。根据上面的构造方法，DFS 的时候把搜索方向记作边的方向，且不输出与虚拟源点连的边即可。

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef pair <int, int> pii;

constexpr int N = 210, M = 5E4 + 10;

int n, m;
int h[N], e[M], ne[M], idx;
int d[N];
bool used[M];

void add (int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}

void dfs (int u) {
    for (int &i = h[u]; ~i; ) {
        if (used[i]) {
            i = ne[i];
            continue;
        }

        used[i] = true;
        used[i ^ 1] = true;

        int j = e[i];
        i = ne[i];

        dfs (j);
        if (u != 0 && j != 0) {
            cout << u << " " << j << "\n";
        }
    }
}

void solve () {
    cin >> n >> m;

    memset (h, -1, sizeof h);
    idx = 0;

    memset (d, 0, sizeof d);

    memset (used, 0, sizeof used);

    for (int i = 0; i < m; i ++ ) {
        int a, b;
        cin >> a >> b;
        add (a, b);
        add (b, a);
        d[a] ++ ;
        d[b] ++ ;
    }

    int cnt = 0;

    for (int i = 1; i <= n; i ++ ) {
        if (d[i] & 1) {
            add (0, i);
            add (i, 0);
            d[0] ++ ;
            d[i] ++ ;
        } else {
            cnt ++ ;
        }
    }

    cout << cnt << "\n";

    for (int i = 1; i <= n; i ++ ) {
        if (~h[i]) {
            dfs (i);
        }
    }
}

int main () {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T -- ) {
        solve ();
    }

    return 0;
}
```



---

## 作者：My_hanshuang (赞：1)

# CF723E One-Way Reform

~~前面的题解说的很详细了，我来多补充两句~~

题目大意：给出一些边让我们定向，使得这个图中尽可能多的点满足入度等于出度。

**注意：题目虽然说的是无向图，但是我们定向操作后，就可以认为是有向图了**

在我们看到题面的时候，我们很容易想到欧拉回路，因为欧拉回路有一个很特殊的性质： **其中的每一个点的入度与出度均相等。** 即题目所求的最优解。因此我们考虑构造欧拉回路。

对有向图G，若想要成为欧拉回路，则必须 **满足图中所有点的度数都是偶数。** 但是难点其实就是在这。因为在题目中，很容易会出现度数为奇数的点。这时候怎么处理这些点就是关键。

## 选择构造出一个虚拟的点，让每一个度数为奇数的点与之相连

在连接虚拟点之后我们就可以愉快地跑欧拉回路了。[欧拉回路模板](https://www.luogu.com.cn/problem/P7771)

对于第一个问题，我们发现入度为偶数的点的个数就是答案。

对于第二个问题，我们在跑欧拉回路的时候可以一边跑一边定向（具体见代码）

贴一下蒟蒻的模板。~~码风不好，轻喷~~

```cpp

#include<iostream>
#include<cstring>
using namespace std;
const int N=1e3;
int t;
int n,m,a[N];
int g[N][N];
int rd[N];
void dfs(int u){
    for(int i=1;i<=n+1;i++){
        if(g[u][i]){
            g[u][i]=g[i][u]=0;//删除边，防止死循环
            if(i!=n+1 && u!=n+1)
            	cout<<u<<" "<<i<<endl;
                //从结点u跑到i，故存在一条u-->i的边
            dfs(i);
        }
    }
}
int main(){
    cin>>t;
    while(t--){
        memset(rd,0,sizeof rd);
        cin>>n>>m;
        for(int i=1;i<=m;i++){
            int a,b;
            cin>>a>>b;
            g[a][b]=g[b][a]=1;
            rd[a]++;rd[b]++;
        }
        int ans=0;
        for(int i=1;i<=n;i++){
            if(rd[i]%2){//度数为奇的点连接虚拟点
                g[n+1][i]=g[i][n+1]=1;
            }
            else ans++;//度数为偶数的点的个数为答案
        }
        cout<<ans<<endl;
        for(int i=1;i<=n;i++)
            dfs(i);
    }
}

```


---

## 作者：Crab_Dave (赞：1)

### 题意

给出一个 $n$ 个点 $m$ 条边的无向图，你需要给每条边定向，使得有尽量多的点，入度等于出度，输出最多的点数并给出一种构造方案。多组数据。$n \le 200$

### 题解

**入度等于出度的点度数一定是偶数。**

由此可以得到第一问的解。

同时，入度等于出度令我们有端联想到**欧拉回路**。

并且我们发现一个很妙的东西，**一个欧拉回路的子图必然满足题意**。

那我们求出一个欧拉回路，把它删成给出的图即可。

但显然度数为奇数的点个数不为 $2$ 或 $0$ 的话欧拉回路是不存在的，无法直接求解。

然后我们把所有度数为奇数的点连到一个虚拟节点 $0$ 上。

**这样整个图就是一个欧拉回路了。**

遍历一遍图求出欧拉回路，将其中所有与 $0$ 相连的边删去即为一种可行的方案。

### 代码

```cpp
void dfs(int u){
	for(int i=0;i<g[u].size();i++){
		int v=g[u][i];
		if(!mp[u][v])continue;
		if(u&&v)printf("%d %d\n",u,v);
		mp[u][v]--;mp[v][u]--;dfs(v);
	}
}

void solve(){
	n=read();m=read();rep(i,0,n)g[i].clear();
	rep(i,0,n)rep(j,0,n)mp[i][j]=0;
	rep(i,1,m){int u=read(),v=read();g[u].push_back(v);g[v].push_back(u);mp[u][v]++;mp[v][u]++;}
	int ans=n;
	rep(i,1,n)if(g[i].size()&1)g[0].push_back(i),g[i].push_back(0),mp[0][i]++,mp[i][0]++,ans--;
	printf("%d\n",ans);rep(i,0,n)dfs(i);
}
```

---

## 作者：XL4453 (赞：0)

### $\text{Difficulty : 2200}$
---
### 解题思路：

根据入度和出度相等，可以想到欧拉回路，考虑再找出一条欧拉回路之后直接按照遍历的顺序给图定向，只要能够定向，每一个点的入度和出度都一定是相等的。但问题是题目中给出的点里面是很可能存在度数为奇数的点的。

可以发现，任意的度为奇数的点都不可能满足要求，最大的可能答案就是度为偶数的点的数量，所以其实并不关心奇数点实际上是怎么连边的，只要偶数点能够满足就行了。那么不妨建立一个空点，然后将所有的度为奇数的点和这个空点链接，这样就使得所有的点的度数都为偶数了（因为每一条边都能且仅能提供 $2$ 的度，所不可能存在只有一个奇数度数点的情况）。

然后直接跑欧拉路就行了。

---
注意清空新建点的数据。

---
### 代码：

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
const int MAXN=205;
int n,T,m,f[MAXN][MAXN],x,y,d[MAXN],top,st[MAXN*MAXN],ans,v[MAXN];
void init(){
	for(int i=1;i<=n+1;i++)
	for(int j=1;j<=n+1;j++)
	f[i][j]=0;
	for(int i=1;i<=n+1;i++)v[i]=0;
	for(int i=1;i<=top+1;i++)st[i]=0;
	for(int i=1;i<=n+1;i++)d[i]=0;
	top=0;ans=0;x=0;y=0;
}
void dfs(int x){
	v[x]=1;
	for(int i=1;i<=n+1;i++){
		if(f[i][x]){
			f[i][x]--;
			f[x][i]--;
			dfs(i);
		}
	}
	st[++top]=x;
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&m);
		for(int i=1;i<=m;i++){
			scanf("%d%d",&x,&y);
			f[x][y]++;f[y][x]++;
			d[x]++;d[y]++;
		}
		for(int i=1;i<=n;i++){
			if(d[i]%2==1){
				f[i][n+1]++;
				f[n+1][i]++;
			}
			else ans++;
		}
		printf("%d\n",ans);
		for(int i=1;i<=n;i++)
		if(v[i]==0){
			dfs(i);
			for(int i=top;i>1;i--)
			f[st[i]][st[i-1]]=1;
			top=0;
		}
		for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		if(f[i][j])printf("%d %d\n",i,j);
		init();
	}
	return 0;
}
```


---

