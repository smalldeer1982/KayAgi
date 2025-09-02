# Network Topology

## 题目描述

This problem uses a simplified network topology model, please read the problem statement carefully and use it as a formal document as you develop the solution.

Polycarpus continues working as a system administrator in a large corporation. The computer network of this corporation consists of $ n $ computers, some of them are connected by a cable. The computers are indexed by integers from $ 1 $ to $ n $ . It's known that any two computers connected by cable directly or through other computers

Polycarpus decided to find out the network's topology. A network topology is the way of describing the network configuration, the scheme that shows the location and the connections of network devices.

Polycarpus knows three main network topologies: bus, ring and star. A bus is the topology that represents a shared cable with all computers connected with it. In the ring topology the cable connects each computer only with two other ones. A star is the topology where all computers of a network are connected to the single central node.

Let's represent each of these network topologies as a connected non-directed graph. A bus is a connected graph that is the only path, that is, the graph where all nodes are connected with two other ones except for some two nodes that are the beginning and the end of the path. A ring is a connected graph, where all nodes are connected with two other ones. A star is a connected graph, where a single central node is singled out and connected with all other nodes. For clarifications, see the picture.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF292B/4b8e00a09b5404153c7328227c396879fd344c8f.png)(1) — bus, (2) — ring, (3) — starYou've got a connected non-directed graph that characterizes the computer network in Polycarpus' corporation. Help him find out, which topology type the given network is. If that is impossible to do, say that the network's topology is unknown.

## 样例 #1

### 输入

```
4 3
1 2
2 3
3 4
```

### 输出

```
bus topology
```

## 样例 #2

### 输入

```
4 4
1 2
2 3
3 4
4 1
```

### 输出

```
ring topology
```

## 样例 #3

### 输入

```
4 3
1 2
1 3
1 4
```

### 输出

```
star topology
```

## 样例 #4

### 输入

```
4 4
1 2
2 3
3 1
1 4
```

### 输出

```
unknown topology
```

# 题解

## 作者：sto__Liyhzh__orz (赞：4)

[传送门](https://www.luogu.com.cn/problem/CF292B)

这个题其实很简单啦~~，只需要分清楚三种图性质就行啦。

### 链形结构：

![](https://cdn.luogu.com.cn/upload/image_hosting/qsrx04hj.png)

如上图，就是一个非常明显的链形结构。

根据上图，我们可以发现：

**链形结构有且只有两个入度和出度之和（以下简称出入和）为 $1$ 的点，剩余点出入和皆为 $2$。**

根据这个性质，我们就可以判断是否是链形结构：

```cpp
bool bus()//链形结构
{
	int cnt1=0,cnt2=0;
	for(int i=1;i<=n;i++)
	{
		if(a[i].size()>=3) return 0;//出入和不是1或2
		else if(a[i].size()==1) ++cnt1;//出入和为1
		else ++cnt2;//出入和为2
	}
	return cnt1==2;//判断出入和为1的点是否有两个
}
```

### 环形结构

![](https://cdn.luogu.com.cn/upload/image_hosting/7cgxt5n7.png)

如上图，就是一个基本的环形结构。

我们就能发现：

**当所有点得出入和皆为 $2$ 时，它是环形结构。**

根据环形结构的特点我们就能判断它了：

```cpp
bool ring()//环形结构
{
	for(int i=1;i<=n;i++)
	{
		if(a[i].size()!=2) return 0;//出入和不为2
	}
	return 1;//出入和皆为2
}
```

### 星形结构

![](https://cdn.luogu.com.cn/upload/image_hosting/bu9sno2y.png)

见上图，很明显就是一个星形结构

我们能够发现：

**当所有点都围绕着其中一个点时，即有一个点出入度为 $n - 1$ 其他所有点出入度为 $1$ 时，它是星形结构。**

写出如下代码：

```cpp
bool star()//星型结构
{
	int cntn=0,cnt1=0;
	for(int i=1;i<=n;i++)
	{
		if(a[i].size()!=1 && a[i].size()!=n-1) return 0;//出入度不为1或n-1
		else if(a[i].size()==n-1) ++cntn;//中间那个点
		else ++cnt1;//分散在两边的点
	}
	return cnt1==n-1 && cntn==1;//只能有1个和n-1个
}
```

### 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

#define LL long long
#define LI long long int
#define UI unsigned int
#define UL unsigned long long
#define ULI unsigned long long int

const int MAXN=100000+5;
vector<int>a[MAXN]; //用vector存图
int n,m;

bool bus()//链形结构
{
	int cnt1=0,cnt2=0;
	for(int i=1;i<=n;i++)
	{
		if(a[i].size()>=3) return 0;//出入和不是1或2
		else if(a[i].size()==1) ++cnt1;//出入和为1
		else ++cnt2;//出入和为2
	}
	return cnt1==2;//判断出入和为1的点是否有两个
}

bool ring()//环形结构
{
	for(int i=1;i<=n;i++)
	{
		if(a[i].size()!=2) return 0;//出入和不为2
	}
	return 1;//出入和皆为2
}

bool star()//星型结构
{
	int cntn=0,cnt1=0;
	for(int i=1;i<=n;i++)
	{
		if(a[i].size()!=1 && a[i].size()!=n-1) return 0;//出入度不为1或n-1
		else if(a[i].size()==n-1) ++cntn;//中间那个点
		else ++cnt1;//分散在两边的点
	}
	return cnt1==n-1 && cntn==1;//只能有1个和n-1个
}

int main()
{
    ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
        //存图
		int u,v;
		cin>>u>>v;
		a[u].push_back(v);
		a[v].push_back(u);
	}
	if(bus()) return cout<<"bus topology\n",0;//满足链形结构
	if(ring()) return cout<<"ring topology\n",0;//满足环形结构
	if(star()) return cout<<"star topology\n",0;//满足星型结构
	cout<<"unknown topology\n";//什么都不满足
    return 0;
}

```

---

## 作者：PaRz1VaL (赞：3)

这道题只要分清楚链形图、环形图和星形图的特点即可。

- 链形图的特点是每一个结点的最大入度为2，且每个结点的入度总和是 $2(n-1)$ 。
- 环形图的特点是每一个结点的最大入度为2，且每个结点的入度总和是 $2n$ 。
- 星形图的特点是每一个结点的最大入度等于边数，且每个结点的入度总和是 $2n$ 。

代码如下。

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
const int MAX = 1e5+5;

int n, m;
int in[MAX];
int out[MAX];
bool flag1 = false;//判断链形图
bool flag2 = false;//判断环形图
bool flag3 = false;//判断星形图

void upd(int x,int y) {
    in[y]++;
    out[x]++;
}

void inp() {

    scanf("%d %d",&n,&m);
    for(int i = 1; i <= m; i++) {
        int x,y;
        scanf("%d %d",&x,&y);
        upd(x,y);
        upd(y,x);
    }
}

void judge() {

    int IN = 0;	//统计入度和
    int OUT = 0;//统计出度和
    int Max = 0;//统计最大入度

    for(int i = 1; i <= n; i++) {
        IN += in[i];
        OUT += out[i];
        Max = max(Max,in[i]);
    }

    if(IN == n*2 && Max == 2)
        flag2 = true;
    else if(IN == m*2 && Max == m)
        flag3 = true;
    else if(Max == 2 && IN == 2*n-2)
        flag1 = true;
}

int main() {

    inp();

    judge();

    if(flag1)
        puts("bus topology");
    else if(flag2)
        puts("ring topology");
    else if(flag3)
        puts("star topology");
    else puts("unknown topology");

    return 0;
}
```

---

## 作者：zzhbpyy (赞：2)

首先，容易发现，这三种图都是连通的，所以我们先用一个 DFS 判断图是否连通。若不连通直接输出`unknown topology`。否则根据每个点的度数判断图的形状，若有 $n-1$ 个点度数为一则为星型，所有点度数为 $2$ 则为环，两个点度数为 $1$，其余点度数为 $2$ 则为总线。

## Code

```c++
#include<bits/stdc++.h>
using namespace std;
struct Edge{
	int u,v,nxt;
}a[200005];
int n,m,ct,ans,head[100005],deg[100005];
inline void add(int u,int v){
	a[++ct]={u,v,head[u]};
	head[u]=ct;
}
bool vis[100005];
void dfs(int u){
	ans++;
	for(int i=head[u];i;i=a[i].nxt){
		int v=a[i].v;
		if(vis[v])continue;
		vis[v]=true,dfs(v);
	}
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(nullptr);
	cin>>n>>m;
	for(int i=1,a,b;i<=m;i++){
		cin>>a>>b;
		add(a,b),add(b,a);deg[a]++,deg[b]++;
	}vis[1]=true,dfs(1);
	if(ans!=n)cout<<"unknown topology",exit(0);
	int _1=0,_2=0;
	for(int i=1;i<=n;i++){
		if(deg[i]==1)_1++;
		if(deg[i]==2)_2++;
	}
	if(_1==2&&_2==n-2)cout<<"bus topology";
	else if(_2==n)cout<<"ring topology";
	else if(_1==n-1)cout<<"star topology";
	else cout<<"unknown topology";
}
```

---

## 作者：FJ_OIer (赞：2)

很简单的一道题，甚至不需要建图。

由于此题不会出现图不连通的情况，不难发现：

- 总线形：$m=n-1$，且最大度数为 $2$。
- 环形：$m=n$，且最大度数为 $2$。
- 星形：其中一个点的度数为 $m$。

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,mx;
int u,v;
int d[100001];
int main(){
	cin>>n>>m;
	for (int i=1;i<=m;i++){
		cin>>u>>v;
		d[u]++;
		d[v]++;
		if (d[u]==m||d[v]==m){
			cout<<"star topology";
			return 0;
		}
		mx=max(mx,max(d[u],d[v]));
	}
	if (m==n&&mx==2){
		cout<<"ring topology";
		return 0;
	}
	if (m==n-1&&mx==2){
		cout<<"bus topology";
		return 0;
	}
	cout<<"unknown topology";
	return 0;
}
```

---

## 作者：Citlali_qwq (赞：1)

## 题意

给定一个图，请你判断这个图是条链，环还是菊花图。

## 解法

由于图保证联通，我们直接记录每个点的度数。

若这些点最大的度数为 $n-1$，且其他点的度数均为 $1$，这个图就是一个菊花图。

如果有两个点度数为 $1$，而其他 $n-2$ 个点的度数都是 $2$，那么这个图就是一个链。

如果每个点的度数都是 $2$，这个图就是一个环。

根据以上性质我们一个一个判断即可。

## 代码

```cpp
/*****************************************
备注：
******************************************/
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cmath>
#include <cassert>
#include <climits>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define int ll
const int MAXN = 2e6 + 10;
const int MR = 10 + 5;
const int INF = 0x3f3f3f3f;
const int MOD = 1e9 + 7;
const int _ = 0;
const bool debug = false;
#define check(x)cout << #x << "   ===   " << x << endl;

inline int read()
{
    int s = 0, f = 1;
    char x = getchar();
    while(x < '0' || x > '9')
    {
        if(x == '-')f = -1;
        x = getchar();
    }
    while(x >= '0' && x <= '9')
    {
        s = s * 10 + x - '0';
        x = getchar();
    }
    return s * f;
}

void print(int x)
{
    printf("%d", &x);
}

int T = 1;
int n, m, du[MAXN];
void solve()
{
	cin >> n >> m;
	for(int i = 1; i <= m; i++)
	{
		int x, y;
		cin >> x >>y;
		du[x]++, du[y]++;
	}
	int num1 = 0, num2 = 0, maxx = 0, num0 = 0;
	for(int i = 1; i <= n; i++)
	{
		num1 += (du[i] == 1);
		num2 += (du[i] == 2);
		num0 += (du[i] == 0);
		maxx = max(maxx, du[i]);
	}
	if(num1 == 2 && num2 == n - 2)cout << "bus topology";
	else if(num2 == n)cout << "ring topology";
	else if(maxx == n - 1 && num1 == n - 1)cout << "star topology";
	else cout << "unknown topology";
}
signed main()
{
	// int start = clock();
	while(T--)solve();
	// printf("%.3lf", clock() - start);
    return ~~(0^_^0);
}
````

---

## 作者：wang_freedom (赞：0)

### 题意：
给你一个图，让你判断它是链，环还是菊花图。
### 思路：
链的特征：有 $2$ 个点度数为 $1$，有 $n-2$ 个点度数为 $2$。

环的特征：每个点度数都为 $2$。

菊花图的特征：有 $n-1$ 个点度数为一。

以此判断即可。
### AC Code:
```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
int n,m,u,v,cnt1,cnt2;
vector<int>e[100005]; 
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>m;
	rep(i,1,m){
		cin>>u>>v;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	rep(i,1,n){
		if(e[i].size()==1)
			cnt1++;
		if(e[i].size()==2)
			cnt2++;
	}
	if(cnt1==2&&cnt2==n-2)
		cout<<"bus topology";
	else if(cnt2==n)
		cout<<"ring topology";
	else if(cnt1==n-1)
		cout<<"star topology";
	else
		cout<<"unknown topology";
	return 0;
}
```

---

## 作者：lzj666_luogu (赞：0)

## 题目大意

给定一张图，判断其是否为一条链（例如二叉搜索树的最劣情况）、一个环、菊花图（SPFA 算法最怕的图）。

## 分析

观察三种图的点与边的关系，可以发现以下结论：

- 对于一条连，只有两个点是连着一条边的，其余的点都是连着两条边的。
- 对于环，所有的点都连着两条边。
- 对于菊花图，只有一个点连着 $n - 1$ 个边，其余的点都连着一条边。

于是想到使用桶记录每个点连的边数，再 $O(1)$ 判断。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n, m;
int cnt[100000 + 10], edge[100000 + 10];
int main() {
	cin >> n >> m;
	for (int i = -m + 1, tmp; i <= m; ++i) {
		cin >> tmp;
		edge[tmp]++;
	}
	for (int i = 1; i <= n; ++i) cnt[edge[i]]++;
	if (cnt[2] == n - 2 && cnt[1] == 2) cout << "bus topology" << endl;
	else if (cnt[2] == n) cout << "ring topology" << endl;
	else if (cnt[n - 1] == 1 && cnt[1] == n - 1) cout << "star topology" << endl;
	else cout << "unknown topology" << endl;
	return 0;
}
```

---

## 作者：Chenyichen0420 (赞：0)

## 思路分析

简单区分一下性质。这里有向当无向。

首先 $n-m$ 的值不为 $0,1$ 的一定是未知的图。

其次，如果 $n=m$，那么统计每个点的度，每个点都应满足度为 $2$。

如果 $n=m+1$，那么统计度为 $1$ 的点数。如果为 $2$ 就是链，如果是 $n-1$ 就是花。因为题目保证了 $n>3$，所以两种情况必定不重。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n, m, a, b, d[100005], cn;
signed main() {
	ios::sync_with_stdio(0);
	cin >> n >> m;
	if (n - m != 0 && n - m != 1) {
		puts("unknown topology");
		return 0;
	}
	for (int i = 1, a, b; i <= m; ++i)
		cin >> a >> b, d[a]++, d[b]++;
	if (n == m) {
		for (int i = 1; i <= n; ++i)
			if (!(d[i] & 2)) {
				puts("unknown topology");
				return 0;
			}
		puts("ring topology");
		return 0;
	}
	for (int i = 1; i <= n; ++i)
		cn += (d[i] == 1);
	if (cn == 2) {
		puts("bus topology");
		return 0;
	}
	else if (cn == n - 1) {
		puts("star topology");
		return 0;
	}
	puts("unknown topology");
	return 0;
}
```

---

## 作者：leo120306 (赞：0)

## 思路
首先读题。题目让我们判断给定的图是链式图，环形图还是菊花图。搞清楚定义就很简单了：
- 链式图：$2$ 个点度数为 $1$，其余图度数为 $2$。
- 环形图：所有点度数为 $2$ **且连通**。
- 菊花图：一个点度数为 $n-1$，其余点度数为 $1$。

可以发现判定度数的条件只需要记录每个点的度数并计数，无需构图。那么对于环形图，连通性怎么判断？难道要用并查集吗？其实不然。认真扫视一遍英文题面，我们注意到这样一句话：
> It's known that any two computers connected by cable directly or through other computers.

这句话就告诉你这张图一定连通，所以连通性就不用判了。~~中文题面居然没写上，太坑了。~~ 知道了这些，我们就可以直接开始敲代码了：记录度数，各度数计数，判断输出。
## 实现
还是比较简单的。
```cpp
#include <cstdio>
using namespace std;

namespace io{ // 快读快写已省略
	inline int readi(){
		int i;
		scanf("%d",&i);
		return i;
	}
	#define writes puts
};
using namespace io;

int n,m,d[100005];

int main(){
	int n=readi(),m=readi();
	for(int i=1;i<=m;i++){
		int x=readi(),y=readi();
		d[x]++,d[y]++;
	}
	int cnt1=0,cnt2=0,cnt3=0;
	for(int i=1;i<=n;i++){
		d[i]==1&&cnt1++;
		d[i]==2&&cnt2++;
		d[i]==n-1&&cnt3++;
	}
	if(cnt1==2&&cnt2==n-2)writes("bus topology");
	else if(cnt2==n)writes("ring topology");
	else if(cnt3&&cnt1==n-1)writes("star topology");
	else writes("unknown topology");
//	flush();
	
	return 0;
} 
```

---

## 作者：Ryan_Adam (赞：0)

# CF292B Network Topology 题解
## 题意
见翻译，注意翻译数据范围错了，应该是 $n\le10^5$。
## 思路分析
发现几种图的类型最大的区别就是边的连接方式。说白了，就是点的出度入度方式。因为本题是无向图，所以不考虑出入度的区别。

用 $a_i$ 来表示点 $i$ 的度数。下面是几种图度数的特点。

- **链形结构**：边数为 $n-1$，每个点度数不超过 $2$，所有点的度数和为 $2n-2$。
- **环形结构**：边数为 $n$，每个点度数不超过 $2$，所有点的度数和为 $2n$。
- **星形结构**：边数为 $n-1$，其中一个点度数为 $n-1$，剩下点度数为 $1$。

剩下结构输出 `unknown` 即可。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
namespace Raiden
{
    int n,m;
    const int N=1e5+5;
    int a[N];
    signed work()
    {
        cin>>n>>m;
        for(int i=1;i<=m;i++)
        {
            int x,y;
            cin>>x>>y;
            a[x]++;
            a[y]++;
        }
        int flag=0;
        int sum=0;
        for(int i=1;i<=n;i++)
        {
            if(a[i]<=2)
            {
                sum+=a[i];
            }
            else
            {
                flag=1;
                sum=a[i];
                break;
            }
        }
        if(flag)
        {
            if(sum==n-1&&m==n-1)
                cout<<"star topology"<<endl;
            else
                cout<<"unknown topology"<<endl;
        }
        else
        {
            if(sum==2*n-2)cout<<"bus topology"<<endl;
            else if(sum==2*n)cout<<"ring topology"<<endl;
            else cout<<"unknown topology"<<endl;
        }
        return 0;
    }
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return Raiden::work();
}   

```

---

## 作者：luuia (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/CF292B)

### 题意

给你一张无向图，判断图的种类，分为链形，星形和环形，具体定义题目中已给出。

### 分析

#### 链形图

顾名思义即为一条链。显然两端的点的度数为 $1$，其余点的度数均为 $2$，将所有点的度数排序之后判断即可。

#### 星形图

点的度数中最大的为边数 $m$，其余均为 $1$，同样排序后判断即可。

#### 环形图

顶点数等于边数，每个点的度数均为 $2$。

如果均不是以上结构，则输出 $\texttt{unknown error}$。

#### 具体实现

用一个数组记录每个顶点的度数，将度数排序后一个一个判断即可。

### 代码

[AC 记录](https://www.luogu.com.cn/record/146935268)

```cpp
#include<bits/stdc++.h>
using namespace std;

int a[110000],n,m,u,v;//数组a记录度数 

int main()
{
	cin >> n >> m;
	for(int i = 1;i <= m;i++) 
	{
		cin >> u >> v;
		a[u]++,a[v]++;
	}
	sort(a + 1,a + n + 1);
	if(a[n] == n - 1 && a[n] == m)//星形图 
	{
		for(int i = 1;i < n;i++)
		{
			if(a[i] != 1)
			{
				cout << "unknown topology" << endl;
				return 0;
			}
		}
		cout << "star topology" << endl;
		return 0;
	}
	else if(a[1] == 1 && a[2] == 1 && m == n - 1)//链形图 
	{
		for(int i = 3;i <= n;i++)
		{
			if(a[i] != 2)
			{
				cout << "unknown topology" << endl;
				return 0;
			}
		}
		cout << "bus topology" << endl;
		return 0;
	}
	for(int i = 1;i <= n;i++)//环形图 
	{
		if(a[i] != 2)
		{
			cout << "unknown topology" << endl;
			return 0;
		}
	}
	cout << "ring topology" << endl;
	return 0;
} 
```


---

## 作者：L_shadow (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF292B)
## 思路：
先读懂题意，明确一下它说的结构是什么东西。

核心在于如何判断它给你的图是什么结构：

1. 如果有 $n$ 个点的入度为 2 并且 $n=m$，那么这个图就是环形结构。

2. 如果有 $n-2$ 个点的入度为 2 并且有两个点入度为 1 并且 $n-1=m$，那么这个图就是链型结构。

3. 如果有 $n-1$ 个点的入度为 1 并且有一个点入度为星形结构。

这边建议用一个桶装入度，比较方便。
## code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,vis[100005],ton[100005];
int main(){
	cin>>n>>m;
	ton[0]=n;
	for(int i=1;i<=m;i++){
		int a,b;
		cin>>a>>b;
		ton[vis[a]]--;//记得变更桶的计数
		vis[a]++;
		ton[vis[a]]++;
		ton[vis[b]]--;
		vis[b]++;
		ton[vis[b]]++;
	}
	if(ton[2]==n&&n==m){
		cout<<"ring topology";
	}
	else if(ton[2]==n-2&&ton[1]==2&&n==m+1){
		cout<<"bus topology";
	}
	else if(ton[m]==1&&ton[1]==n-1&&n==m+1){
		cout<<"star topology";
	}
	else cout<<"unknown topology";
	return 0;
}

```


---

## 作者：A_Đark_Horcrux (赞：0)

在编程中不能直接用形状判断图像，我们需要寻找一些其他的性质，例如一个点的度数。

不难发现：环形图所有点的度数都为二，链状图只有两端的两个点度数为一，其他的点度数为二，星形图中间的点的度数就是边数。然后枚举判断即可。复杂度 $O(n)$，做不到更快了

```cpp
#include<cstdio>
using namespace std;
int n,m,x,y,s,t,i,a[1000010];
int main()
{
	scanf("%d %d",&n,&m);
	for(i=1;i<=m;i++) scanf("%d %d",&x,&y),a[x]++,a[y]++;//边输入边记录度数
	for(i=1;i<=n;i++) if(a[i]==m) {puts("star topology"); return 0;}//一个点度数为边总数，星形
	for(i=1;i<=n;i++) s+=(a[i]==2); if(s==n) {puts("ring topology"); return 0;} s=0;//所有点度数为二，环形
	for(i=1;i<=n;s+=a[i]==1,t+=a[i]==2,i++);
	if(s==2&&s+t==n) {puts("bus topology"); return 0;}//两个点度数为1，其余为2，链形
	puts("unknown topology");//不对就是其他的。
    return 0;
}
```
第一篇题解里写的总度数貌似不用考虑。



---

## 作者：小杨小小杨 (赞：0)

## 题意
给你一个图，让你判断是链形、环形和星形。具体定义题目已给出。
## 思路
根据图的性质可知，链形图两端的点度数为一，其他的点度数为二；环形图所有点的度数都为二；星形图中央点度数为总数减一，其他点的度数为一。    
综上所述，枚举加上记录度数即可。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,x,y,f[100001],i;
bool pd1(){
	int ans1=0,ans2=0;
	for (int i=1;i<=n;i++)
		if (f[i]==1) ans1++;//它的入度为一
		else if (f[i]==2) ans2++;//它的入度为二
	if (ans1==2&&ans2==n-2) return true;//如果只有两个入度为一的（两端）和总数减二个入度为二的（其余），那么就是链形图
	return false;
}
bool pd2(){
	int ans=0;
	for (int i=1;i<=n;i++)
		if (f[i]==2) ans++;//它的入度为二
	if (ans==n) return true;//如果正好全都是入度为二，那么就是环形图
	return false;
}
bool pd3(){
	int ans1=0,ans2=0;
	for (int i=1;i<=n;i++)
		if (f[i]==n-1) ans1++;//如果它的入度为总数减一
		else if (f[i]==1) ans2++;//如果它的入度为一
	if (ans1==1&&ans2==n-1) return true;//如果正好有一个度数为总数减一（中央）和总数减一个度数为一的（周围），那么就是星形图
	return false;
}
int main(){
	scanf("%d%d",&n,&m);
	for (i=1;i<=m;i++) scanf("%d%d",&x,&y),f[y]++,f[x]++;//度数累计
	if (pd1()){printf("bus topology\n");return 0;}//如果是链形图
	if (pd2()){printf("ring topology\n");return 0;}//如果是环形图
	if (pd3()){printf("star topology\n");return 0;}//如果是星形图
	printf("unknown topology\n");//如果啥都不是
	return 0;
}

```


---

