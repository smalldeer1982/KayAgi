# Longtail Hedgehog

## 题目描述

This Christmas Santa gave Masha a magic picture and a pencil. The picture consists of $ n $ points connected by $ m $ segments (they might cross in any way, that doesn't matter). No two segments connect the same pair of points, and no segment connects the point to itself. Masha wants to color some segments in order paint a hedgehog. In Mashas mind every hedgehog consists of a tail and some spines. She wants to paint the tail that satisfies the following conditions:

1. Only segments already presented on the picture can be painted;
2. The tail should be continuous, i.e. consists of some sequence of points, such that every two neighbouring points are connected by a colored segment;
3. The numbers of points from the beginning of the tail to the end should strictly increase.

Masha defines the length of the tail as the number of points in it. Also, she wants to paint some spines. To do so, Masha will paint all the segments, such that one of their ends is the endpoint of the tail. Masha defines the beauty of a hedgehog as the length of the tail multiplied by the number of spines. Masha wants to color the most beautiful hedgehog. Help her calculate what result she may hope to get.

Note that according to Masha's definition of a hedgehog, one segment may simultaneously serve as a spine and a part of the tail (she is a little girl after all). Take a look at the picture for further clarifications.

## 说明/提示

The picture below corresponds to the first sample. Segments that form the hedgehog are painted red. The tail consists of a sequence of points with numbers $ 1 $ , $ 2 $ and $ 5 $ . The following segments are spines: ( $ 2 $ , $ 5 $ ), ( $ 3 $ , $ 5 $ ) and ( $ 4 $ , $ 5 $ ). Therefore, the beauty of the hedgehog is equal to $ 3·3=9 $ .

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF615B/dbda6af90158fd5ce193a3a2582b631a7f4eefdf.png)

## 样例 #1

### 输入

```
8 6
4 5
3 5
2 5
1 2
2 8
6 7
```

### 输出

```
9
```

## 样例 #2

### 输入

```
4 6
1 2
1 3
1 4
2 3
2 4
3 4
```

### 输出

```
12
```

# 题解

## 作者：jch123 (赞：4)

## 分析
发现可以从编号小的向编号大的搜索，但是这样依旧会超时。
思考一下可以发现每个点只需要用它一个子节点去搜索。所以只需要统计一下入度，没搜到一个点，这个点的入度减 $1$，只在这个点入度为 $0$ 时再搜就可以跑快很多。
## **代码**
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
vector<int> edge[N];
long long vis[N],d[N],in[N],l[N];
void dfs(int u)
{
	vis[u]=1;
	for(auto v:edge[u])
	{
		l[v]=max(l[v],l[u]+1);
		in[v]--;
		if(in[v]==0) dfs(v);
	}
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	int n,m;
	long long ans=0;
	cin>>n>>m;
	while(m--)
	{
		int u,v;
		cin>>u>>v;
		edge[min(u,v)].push_back(max(u,v));
		d[u]++,d[v]++;
		in[max(u,v)]++;
	}
	for(int i=1;i<=n;i++)
		if(vis[i]==0) l[i]=1,dfs(i);
	for(int i=1;i<=n;i++)
		ans=max(ans,l[i]*d[i]);
	cout<<ans;
	return 0;
}
```

---

## 作者：__Shine__ (赞：4)

## 题目链接

[codeforces 615 B. Longtail Hedgehog ](https://codeforces.com/contest/615/problem/B)
## 题目描述

给定 $n$ 个点，$m$ 条无向边的图，设一条节点递增的链末尾节点为 $u$，链上点的个数为 $P$，则该链的 beauty 值 $= \ P \times degree_{u}$。问你所有链中最大的 beauty 值。

## 解题思路

因为只需要找到**以每个节点为终点**的**最长递增链**即可，所以建图的时候可以建成从编号小的节点到编号大的节点的有向图，然后用深度优先搜索，但是直接暴搜会 TLE，然后就开始了我的 TLE 之路……

又改成了拓扑排序，而且跑得飞快，就是定义一个标志数组，记录**当前节点之前的节点是不是已经遍历完了**，如果遍历完了，那么当前节点就是最优的了，就从当前节点向下遍历。

## 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;
#define LL long long

const LL INF = 1e9+7;
const int maxn = 100010;
struct node
{
    int to, next;
} edge[maxn*4];


int head[maxn], tot, du[maxn], in[maxn];
LL ans[maxn];

void add (int from, int to)//建边
{
    edge[tot].to = to;
    edge[tot].next = head[from];
    head[from] = tot ++;
}
/**
    记录in[i]为i点的入度
    当入度为零时，当前节点更新为最优，
    然后从当前节点继续向下遍历
    向下遍历时层数参数为当前层加一
    而不是简单的上一层参数加一
*/
void dfs (int u, LL x)//搜索图
{

    for (int i=head[u]; i!=-1; i=edge[i].next)
    {
        int v = edge[i].to;
        ans[v] = max (ans[v], x);
        in[v]--;

        if(in[v] == 0)
            dfs (v, ans[v]+1);
    }
}

int main ()
{
    int n, m;

    scanf ("%d %d", &n, &m);
    memset (head, -1, sizeof(head));
    tot = 0;

    for (int i=0; i<m; i++)//建图
    {
        int u, v;
        scanf ("%d %d", &u, &v);
        if(u > v)
            swap (u, v);
        du[u] ++;
        du[v] ++;
        in[v]++;
        add (u, v);
    }

    for (int i=1; i<=n; i++)//调用搜索函数
    {
        if (ans[i] == 0)
        {
            ans[i] = 1;
            dfs (i, 2);
        }
    }

    LL sum = 0;
    for (int i=1; i<=n; i++)
        sum = max (sum, ans[i] * du[i]);

    printf ("%lld\n", sum);
    return 0;
}
```

---

## 作者：_shine_ (赞：3)

发现一个特质：只要存在一条从 $u$ 到 $v$ 的边且 $u>v$（单项边），则这条边的存在无意义。

而双向边可理解为两个单项边，定义 $f_u$ 表示为以 $u$ 结尾的最长链的长度，则 $f_u=f_v+1$（$f_v$ 这里取最大），而在删去了所有的无意义的边后整个图必不可能有环（只能从小到大），而这个想法会在第二十六的点时超时，那不妨对于每一个点都单独进行处理，用与其相连的几个点的值进行更新 $f_u$，在与其相连的点 $v$ 的入度为 $0$ 时再对 $v$ 进行搜索（避免了多次无效的更新）。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int,int>
#define lx first
#define ly second
const int maxn=2e5+10;
int n,m,in[maxn],on[maxn];
vector<int>e[maxn];
int f[maxn],vis[maxn];
void get_dfs(int u,int all_it){
    for(int i=0;i<e[u].size();++i){
        f[e[u][i]]=max(f[e[u][i]],all_it+1);on[e[u][i]]--;
        get_dfs(e[u][i],f[e[u][i]]);
    }
}
signed main(){
    scanf("%lld%lld",&n,&m);
    for(int i=1;i<=m;++i){int u,v;scanf("%lld%lld",&u,&v);if(u<v)e[u].push_back(v),on[v]++;if(v<u)e[v].push_back(u),on[u]++;in[u]++;in[v]++;}
    for(int i=1;i<=n;++i)if(f[i]==0){f[i]=1;get_dfs(i,1);}
    int ans=0;for(int i=1;i<=n;++i)ans=max(ans,f[i]*in[i]);
    printf("%lld\n",ans);
    return 0;
}
```


---

## 作者：yangzd (赞：3)

# 题目大意

在暑假里，沙耶非常喜欢画画。某一天，爷爷给她一幅画和一支笔。这幅画有 $n$ 个点和 $m$ 条线（这些线有可能会相交，不过我们可以先不理它）。每条线的左右两端是两个不一样的点，没有任何两条不同的线的两个端点是完全一样的。现在，沙耶想要给画中的一些线条涂上颜色，沙耶想要的是画出一只刺猬出来。在沙耶的印象中，刺猬应该有一个尾巴和若干根刺。她觉得画尾巴的时候应该满足如下规律：

·1、只能够给画中有的线条涂上颜色。

·2、尾巴应该是一条连续的包含若干个点的长线，每两个点之间的线条会被涂上了颜色。

·3、尾巴上的点的序号应该要按顺序严格递增。
沙耶觉得尾巴的长度就是尾巴上的点的个数。同时，沙耶也要画出刺猬的刺，因此她把一些线条也涂上了颜色，刺的一个端点必须和尾巴的末端点一样。沙耶觉得刺猬的美观值应该是尾巴的长度乘以刺的数量。沙耶想要画出一只美观值最大的刺猬。虽然大家觉得沙耶的想法很幼稚，但是她毕竟还是一个小萝莉

简单点来说就是：

 给定一张图，要求寻找序号递增的链，使得某链的长度乘以该链末端点的度数的值最大，求该值
 
# 分析

先统计每个点的度数，入度。建图时，只加从序号小的点到序号大的点的单向边。随后，从序号小且未被访问的点出发，进行 **dfs** 搜索。每次搜索到一个新的节点，将该点入度减一，同时如果新的值大于原有值，则更新，但并不马上往下递归，若入度为 $0$，方可往下递归（优化，避免无效更新）。最后，统计每个点的长度和度数，求最大值即可。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

struct edge
{
	long long fm,to;
}store[100010<<1];

long long head[100010],nxt[200010];
long long degree[100010],cnt=0,in[100010];
long long len[100010];
bool vis[100010];

void addedge(int fm,int to)
{
	nxt[cnt]=head[fm];
	head[fm]=cnt;
	store[cnt].fm=fm;
	store[cnt].to=to;
	cnt++;
}

void dfs(long long x)
{
	vis[x]=1;
	
	long long tmp=len[x]+1;
	
	for(long long i=head[x]; ~i; i=nxt[i])
	{
		len[store[i].to]=max(len[store[i].to],tmp);
		in[store[i].to]--;
		
		if(in[store[i].to]==0)
           dfs(store[i].to);
	}
}

signed main()
{
	ios::sync_with_stdio(0);
	
	long long n,m,a,b;
	long long ans=0,tmp;
	
	cin >> n >> m;
	
	memset(head,-1,sizeof(head));
	memset(degree,0,sizeof(degree));
	memset(in,0,sizeof(in));
	memset(vis,0,sizeof(vis));
	
	for(long long i=1; i<=m; i++)
    {
       cin >> a >> b;
       
	   degree[a]++;
	   degree[b]++;
	   
	   if(a<b)
	   {
		   addedge(a,b);
		   in[b]++;
	   }
	   
	   else
	   {
		   addedge(b,a);
		   in[a]++;
	   }
	}
 
	for(long long i=1; i<=n; i++)
	{
		if(!vis[i])
		{
			len[i]=1;
			dfs(i);
		}
	}
	
	for(long long i=1; i<=n; i++)
	{
		tmp=1*len[i]*degree[i];
		
		if(tmp>ans)
			ans=tmp;
	}
	
	cout << ans << endl; 
	
	return 0;
}
```

---

