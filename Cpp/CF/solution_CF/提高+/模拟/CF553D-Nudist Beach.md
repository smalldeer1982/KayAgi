# Nudist Beach

## 题目描述

Nudist Beach is planning a military operation to attack the Life Fibers. In this operation, they will attack and capture several cities which are currently under the control of the Life Fibers.

There are $ n $ cities, labeled from 1 to $ n $ , and $ m $ bidirectional roads between them. Currently, there are Life Fibers in every city. In addition, there are $ k $ cities that are fortresses of the Life Fibers that cannot be captured under any circumstances. So, the Nudist Beach can capture an arbitrary non-empty subset of cities with no fortresses.

After the operation, Nudist Beach will have to defend the captured cities from counterattack. If they capture a city and it is connected to many Life Fiber controlled cities, it will be easily defeated. So, Nudist Beach would like to capture a set of cities such that for each captured city the ratio of Nudist Beach controlled neighbors among all neighbors of that city is as high as possible.

More formally, they would like to capture a non-empty set of cities $ S $ with no fortresses of Life Fibers. The strength of a city ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF553D/327104f0a95a1976121514a888c2d90724b0e13e.png) is defined as (number of neighbors of $ x $ in $ S $ ) / (total number of neighbors of $ x $ ). Here, two cities are called neighbors if they are connnected with a road. The goal is to maximize the strength of the weakest city in $ S $ .

Given a description of the graph, and the cities with fortresses, find a non-empty subset that maximizes the strength of the weakest city.

## 说明/提示

The first example case achieves a strength of 1/2. No other subset is strictly better.

The second example case achieves a strength of 1. Note that the subset doesn't necessarily have to be connected.

## 样例 #1

### 输入

```
9 8 4
3 9 6 8
1 2
1 3
1 4
1 5
2 6
2 7
2 8
2 9
```

### 输出

```
3
1 4 5
```

## 样例 #2

### 输入

```
10 8 2
2 9
1 3
2 9
4 5
5 6
6 7
7 8
8 10
10 4
```

### 输出

```
8
1 5 4 8 10 6 3 7
```

# 题解

## 作者：zhimao (赞：1)

此题与分数规划的思想有些类似，我们可以二分最小安全度，判断这个安全度能否到达。

但怎么判断并记录方案呢？选择占领的城市吗，这样难写，而且时间复杂度特高。我们其实可以这样想：先占领所有能占领的城市，这样只有无法占领的城市的邻居的安全度小于 1 ，判断这些城市，如果安全度低，则标记为没有占领，并且此时它周边的城市安全度减小了，需要判断。由此我们得出一种方法，把没有占领的城市入队，每次取队首判断被占领的邻居，安全度小就标记没有占领并入队。最后如果还有占领的城市就是可以的，记录方案，否则不行。由于每个城市最多入队出队一次，因此复杂度是节点个数级别的。

也许有人会问：开始占领部分能占领的城市会不会更优，答案当然是不会的。我们分类讨论：如果开始选择不占领的城市在先占领所有能占领的城市的方案中被舍弃，则无影响，不然选择不占领它会让邻居安全度变低，结果只会变坏。

注意题目给出的图不一定是联通图，因此我们还要记录每个联通块的最大安全度，取最优。

此外还有一些小细节，详见代码注释。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k,sum[100005],nm,ct[100005],nex[400005],wen[400005],hea[100005],len,boo[100005],bo[100005],booo[100005],l,r,lr[200005],maxp;
double b[100005],c[100005],maxx;
void add(int x,int y)
{
	++len;
	nex[len]=hea[x];
	wen[len]=y;
	hea[x]=len;
}
void dfs(int x)
{
	++sum[nm];
	boo[x]=nm;
	ct[nm]+=bo[x];
	for(int j=hea[x];j>0;j=nex[j])
		if(boo[wen[j]]==0) dfs(wen[j]);
}
void writeln1(int x)
{
	boo[x]=0;
	printf("%d ",x);
	for(int j=hea[x];j>0;j=nex[j])
		if(boo[wen[j]]) writeln1(wen[j]);
}
bool check(int x,double y)
{
	l=r=0;
	for(int i=1;i<=n;i++)
		if(boo[i]==x)
		{
			c[i]=b[i];
			booo[i]=bo[i];
			if(bo[i]) lr[++r]=i;
		}
	do
	{
		++l;
		int u=lr[l];
		for(int i=hea[u];i>0;i=nex[i])
		{
			int v=wen[i];
			--c[v];
			if(c[v]<y*b[v]&&booo[v]==0)
			{
				lr[++r]=v;
				booo[v]=1;
			}
		}
	}while(l<r);
	return l!=sum[x];
}
void writeln2(int x,double y)
{
	l=r=0;
	for(int i=1;i<=n;i++)
		if(boo[i]==x)
		{
			c[i]=b[i];
			booo[i]=bo[i];
			if(bo[i]) lr[++r]=i,--sum[x];
		}
	do
	{
		++l;
		int u=lr[l];
		for(int i=hea[u];i>0;i=nex[i])
		{
			int v=wen[i];
			--c[v];
			if(c[v]<y*b[v]&&booo[v]==0)
			{
				--sum[x];
				lr[++r]=v;
				booo[v]=1;
			}
		}
	}while(l<r);
	printf("%d\n",sum[x]);
	for(int i=1;i<=n;i++) if(boo[i]==x&&booo[i]==0) printf("%d ",i);	
}
int main()
{
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=k;i++)
	{
		int x;
		scanf("%d",&x);
		bo[x]=1;
	}
	for(int i=1;i<=m;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);add(y,x);
		b[x]+=1;b[y]+=1;
	}
	for(int i=1;i<=n;i++)
		if(!boo[i])
		{
			++nm;
			dfs(i);
			if(ct[nm]==0)//如果块里没有无法占领城市，安全度为 1 ，直接输出
			{
				printf("%d\n",sum[nm]);
				writeln1(i);
				return 0;
			}
		}
	for(int i=1;i<=nm;i++)
	{
		double l=0.0,r=1.0,mid=0.5;
		do
		{
			if(check(i,mid)) l=mid; else r=mid;
			mid=(l+r)/2.0;
		}while(r-l>0.000000001);//精度自选，保险起见，我开的大。
		if(maxx<l)
		{
			maxx=l;
			maxp=i;
		}
	}
	if(maxx==0)//无论怎么占领，没有城市的安全度大于零，随便输出一个可占领城市
	{
		int i=1;
		for(;i<=n;i++) if(!bo[i]) break;
		printf("1\n%d",i);
		return 0;
	}
	else writeln2(maxp,maxx);
}
```

---

## 作者：crimson000 (赞：1)

本题要求我们求一个最小值最大，这种问法很明显是二分的问法。于是我们考虑二分。

二分最关键的是 check 函数，我们思考一下已经有了安全值 $mid$ 后如何验证该安全值是否成立。

简单的说，我们可以考虑每个点，如果某个点就算周围的好点全部选上都不能达到安全值 $mid$，那么这个点就不能被选上。而不选这个点造成的后果就是它周围的点可能有的也会达不到 $mid$。不断重复这个删点的过程，直到没有点会被删去。这时我们再观察是否有点没有被删去，如果有点存留，那么这个 $mid$ 就是合法的。

## 算法流程

我们可以用类似拓扑排序的方法来进行删点的过程。

1. 将所有好点全部选中。
2. 先将坏点的周围点的入度减少。
3. 看有没有安全值小于 $mid$ 的点，有的话将其入队，并将其选中的标记取消。
4. 不断取出队头，将队头周围点的入度减少，如果产生新的安全值小于 $mid$ 的点，则将这个新点入队并将其选中的标记取消。
5. 不断循环上面的流程直到队列为空。
6. 看有没有点还处于被选中的状态，如果有的话该 $mid$ 即为合法。

## 完整代码

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 10;
int h[N], e[N], ne[N], idx;
int d[N], dd[N];
int c[N], tt;
bitset<N> bad, in;
queue<int> q;
int n, m, k;

inline void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

bool check(double mid)
{
    in.reset(); // in 即为是否被选中的标记
    for(int i = 1; i <= n; i ++ ) dd[i] = d[i];
    while(q.size()) q.pop();
    for(int i = 1; i <= n; i ++ )
    {
        if(bad[i])
        {
            for(int j = h[i]; j != -1; j = ne[j])
            {
                int v = e[j];
                dd[v] --;
            }
        }
        else in[i] = true;
    }
    for(int i = 1; i <= tt; i ++ )
        if((double)dd[c[i]] < (double)d[c[i]] * mid) // c[i] 为好点
        {
            q.push(c[i]);
            in[c[i]] = false;
        }
    
    while(q.size())
    {
        int u = q.front();
        q.pop();
        for(int i = h[u]; i != -1; i = ne[i])
        {
            int v = e[i];
            if(bad[v]) continue;
            dd[v] --;
            if((double)dd[v] < d[v] * mid && in[v]) 
            {
                q.push(v);
                in[v] = false;
            }
        }
    }

    for(int i = 1; i <= n; i ++ )
    {
        if(bad[i]) continue;
        if(in[i]) return true;
    }
    return false;
}

int main()
{
    memset(h, -1, sizeof h);

    n = read(), m = read(), k = read();
    for(int i = 1; i <= k; i ++ )
    {
        int x = read();
        bad[x] = true;
    }

    for(int i = 1; i <= n; i ++ )
        if(!bad[i])
            c[++ tt] = i;

    for(int i = 1; i <= m; i ++ )
    {
        int a = read(), b = read();
        add(a, b), add(b, a);
        d[a] ++, d[b] ++;
        dd[a] ++, dd[b] ++;
    }

    double l = 0, r = 1;
    while(r - l >= 1e-8)
    {
        double mid = (l + r) / 2;
        if(check(mid)) l = mid;
        else r = mid;
    }

    check(l); // 这里再 check 一遍是为了把合法方案（in 数组）搞出来

    int cnt = 0;
    for(int i = 1; i <= n; i ++ ) 
        if(in[i]) cnt ++;

    printf("%d\n", cnt);

    for(int i = 1; i <= n; i ++ )
        if(in[i])
            printf("%d ", i);

    return 0;
}
```

---

## 作者：lsw1 (赞：1)

看到有“最小的……尽可能大”或者“最大的安全度尽可能小”这类字眼，十有八九是二分。

考虑二分最小安全度。

假设二分到的最小安全度为 $mid$ （注意 $mid$ 是一个浮点数，所以要进行浮点数二分），初始先**假设**（注意，只是假设）能占领的点全部都被占领，然后把安全度小于 $mid$ 的点删去，注意删去一个不满足条件的点的同时，可能会使得其他满足条件的点变得不满足条件，而这些点只可能在这个被删掉的点的周围，所以在删掉一个点的同时，也要判断和它相邻的点是否符合条件。

考虑用队列来完成删点的过程。

初始先把所有点放入队列中，每次取出队首的点进行判断，如果安全度小于 $mid$ ，则把这个点删掉，并把和这个点相邻的点全部放入队列中。

注意，本题使用浮点数二分，所以要定义常数 $eps$ ，这里我设 $eps=10^{-8}$ 。

代码：

```cpp
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
const double eps = 1e-8;//eps
const int MAXN = 1e5;
vector<int>graph[MAXN + 5];//图
int a[MAXN + 5];//表示a[i]无法被选择
bool vis[MAXN + 5];//vis[i]表示点i是否被选择
int n,m,k;
bool check(double x)//x是我们二分出来的最小安全度
{
	for(int i = 1;i <= n;i++)//假设选全部能选的点
	{
		vis[i] = true;
	}
	for(int i = 1;i <= k;i++)//除了不能选的点以外
	{
		vis[a[i]] = false;
	}
	queue<int>q;
	for(int i = 1;i <= n;i++)
	{
		if(vis[i])
		{
			q.push(i);
		}
	}
	while(!q.empty())
	{
		int u = q.front();
		q.pop();
		int cnt = 0;
		for(int i = 0;i < graph[u].size();i++)
		{
			int v = graph[u][i];
			if(vis[v])//如果点v被占领
			{
				cnt++;
			}
		}
		if(cnt * 1.0 / graph[u].size() + eps < x)//若安全度达不到最低要求
		{//注意浮点数比较要加eps，否则会产生精度误差
			vis[u] = false;//选不上
			for(int i = 0;i < graph[u].size();i++)
			{
				int v = graph[u][i];
				if(vis[v])
				{
					q.push(v);//与之相邻的点要再进行检测
				}
			}
		}
	}
	for(int i = 1;i <= n;i++)
	{
		if(vis[i])//只要还有一个点被选中就行
		{
			return true;
		}
	}
	return false;
}
int main()
{
	cin >> n >> m >> k;
	for(int i = 1;i <= k;i++)
	{
		cin >> a[i];
	}
	for(int i = 1;i <= m;i++)
	{
		int u,v;
		cin >> u >> v;
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
	double l = 0,r = 1;
	while(l + eps < r)//注意要加eps，否则二分会死循环
	{
		double mid = (l + r) / 2;
		if(check(mid))
		{
			l = mid;
		}
		else
		{
			r = mid;
		}
	}
	check(l);//目的是跑出vis，注意l可能不是最后一个check的，所以要再跑一次
	int cnt = 0;
	for(int i = 1;i <= n;i++)
	{
		if(vis[i])
		{
			cnt++;
		}
	}
	cout << cnt << endl;
	for(int i = 1;i <= n;i++)
	{
		if(vis[i])
		{
			cout << i << " ";
		}
	}
	return 0;
}
```

---

## 作者：PZimba (赞：1)

[博客园](https://www.cnblogs.com/kjd123456/)

# 题目地址

[这里](https://www.luogu.com.cn/problem/CF553D)

# Solution

一道比较好想的二分，但是调代码花了我几个小时:(

先分析一下题目性质：任意城市被敌军占领，其周围城市的安全度都会降低 $\implies$ 
我们在选取城市时，应遵循这样一个原则： **所有能够被己方控制的城市都应当让己方控制。** 

这里的“能够”当然只在二分答案的限制下才有意义。

那么，解决方法就很简单了。
利用队列，先将必须被敌军占领（有堡垒）的城市入队，将队列中的城市一个个拿出来更新其周围城市的安全度，如果更新后安全度小于mid就将这个城市入队。

如果最后还有城市未被敌军占领，l = mid否则，r = mid，最终l为最大安全度。

另外，这道题对精度的要求比较高，我设置的精度是 $10^{-9}$ 。 $10^{-8}$ 以上大概就过不了了。

# Code
```cpp
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 10;
const double eps = 1e-9;

int n,m,k,siz[MAXN];
int num[MAXN],d[MAXN];//d：某城市周围被敌军占领的城市数量。
bool vis[MAXN];
vector<int> e[MAXN];
queue<int> q;

bool judge(double mid) {
    memset(vis,false,sizeof(vis));
    memset(d,false,sizeof(d));
    for (int i = 1; i <= k; i++) {
        q.push(num[i]);vis[num[i]] = true;
        for (int j = 0; j < siz[num[i]]; j++) {
            d[e[num[i]][j]]++;
        }
    }
    while (!q.empty()) {
        int u = q.front();q.pop();
        int len = e[u].size();
        for (int i = 0; i < len; i++) {
            int v = e[u][i];
            if (vis[v]) continue;
            double nu = ((siz[v] - d[v]) * 1.0 / siz[v]);
            if (nu < mid) {
                vis[v] = true;
                for (int j = 0; j < siz[v]; j++) {
                    d[e[v][j]]++;
                }
                q.push(v);
            }
        }
    }
    for (int i = 1; i <= n; i++) if (!vis[i]) return true;
    return false;
}

int main() {
    scanf("%d%d%d",&n,&m,&k);
    for (int i = 1; i <= k; i++) {
        scanf("%d",&num[i]);
    }
    for (int i = 1; i <= m; i++) {
        int u,v;
        scanf("%d%d",&u,&v);
        e[u].push_back(v);
        e[v].push_back(u);
    }
    for (int i = 1; i <= n; i++) siz[i] = e[i].size();
    double l = 0,r = 1.0;
    while (r - l > eps) {
        double mid = (l + r) / 2;
        if (judge(mid)) l = mid;
        else r = mid;
    }
    memset(vis,false,sizeof(vis));
    judge(l);
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            cnt++;
        }
    }
    cout << cnt << endl;
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) printf("%d ",i);
    }
    return 0;
}
```

---

