# The Child and Toy

## 题目描述

On Children's Day, the child got a toy from Delayyy as a present. However, the child is so naughty that he can't wait to destroy the toy.

The toy consists of $ n $ parts and $ m $ ropes. Each rope links two parts, but every pair of parts is linked by at most one rope. To split the toy, the child must remove all its parts. The child can remove a single part at a time, and each remove consume an energy. Let's define an energy value of part $ i $ as $ v_{i} $ . The child spend $ v_{f1}+v_{f2}+...+v_{fk} $ energy for removing part $ i $ where $ f_{1},f_{2},...,f_{k} $ are the parts that are directly connected to the $ i $ -th and haven't been removed.

Help the child to find out, what is the minimum total energy he should spend to remove all $ n $ parts.

## 说明/提示

One of the optimal sequence of actions in the first sample is:

- First, remove part $ 3 $ , cost of the action is $ 20 $ .
- Then, remove part $ 2 $ , cost of the action is $ 10 $ .
- Next, remove part $ 4 $ , cost of the action is $ 10 $ .
- At last, remove part $ 1 $ , cost of the action is $ 0 $ .

So the total energy the child paid is $ 20+10+10+0=40 $ , which is the minimum.

In the second sample, the child will spend $ 400 $ no matter in what order he will remove the parts.

## 样例 #1

### 输入

```
4 3
10 20 30 40
1 4
1 2
2 3
```

### 输出

```
40
```

## 样例 #2

### 输入

```
4 4
100 100 100 100
1 2
2 3
2 4
3 4
```

### 输出

```
400
```

## 样例 #3

### 输入

```
7 10
40 10 20 10 20 80 40
1 5
4 7
4 5
5 2
5 7
6 4
1 6
1 3
4 3
1 4
```

### 输出

```
160
```

# 题解

## 作者：无心揽青丝 (赞：21)

## Description
```cpp
n个带权点，m条无向边，
删除一个点就要付出所有与之有联系且没有被删除的点的点权之和的代价。
求删除所有点的最小代价。
```
## Input
```cpp
懒得翻译，看原题
```
## Output
```cpp
同上
```
## Sample Input 1
```cpp
4 3
10 20 30 40
1 4
1 2
2 3
```
## Sample Output 1
```cpp
40
```
## Sample Input...
## Sample Output...

## Mentality
```cpp
考虑贪心，其实我们发现，删点其实就是删边的过程，
于是我们可以把题面进行改变，变成删边。
然后对于删每一条边，再用删点的贪心思想去做。
我们发现对于删除一条边两端的点，肯定是删权值大的点最优，
即删这条边对答案的贡献为两端点的点权中的最小值。
然后就for循环删边即可，每次答案加上两端点的点权中的最小值即可。
```
## Code
```cpp
#include<bits/stdc++.h>
#define itn int//手残党专用
#define ll long long
using namespace std;
int n,m,a[1005],x,y;
ll ans;
int main(){
    scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d",a+i);
	for(int i=1;i<=m;i++){
		scanf("%d%d",&x,&y);
		ans+=min(a[x],a[y]);
	}
	printf("%lld",ans);
    return 0;
}
```


---

## 作者：KEBrantily (赞：6)

为什么大家都是删边啊。

看来我老年人思维能力差石锤了。

![/kk](https://cdn.luogu.com.cn/upload/pic/62227.png)

那就提供一种比较贪心的做法。


每个点都会被删掉，而每次删掉一个点会加上周围未被删除的点的权值。

删点的总次数无法改变，但我们可以改变每个点被删的顺序。

换句话说，我们可以改变每个点的权值被统计的次数。

如果一个点越晚被删除，那么它被统计的次数就越多。

为了使贡献最小，我们肯定希望点权越大的点被统计的次数越少。

因此可以贪心地想到，我们要尽可能的使权值大的点尽早被删除，避免被加上更多次。

所以我们将点按点权从大到小排序，依次删点加贡献即可。

代码很简单就不放了。

---

## 作者：little_sun (赞：4)

容易发现，若要使得总价值最小，对于一条边上的两个点，价值大的点总在价值小的点之前被删。

从这里我们可以想到拓扑排序，对于一条边，我们从边权大的点向边权小的点连边，然后跑拓扑排序

你兴高采烈的写了一下，发现你` Wrong answer on test 20 `了

然后你理性分析了一下，发现某些点的边权可能相等，于是就可能形成了一些环，由于拓扑排序只对$\mathrm{DAG}$有效，于是你理所当然的`Wrong answer`了

那么什么东西可以把环缩成点呢？这时我们想到了$\mathrm{tarjan}$算法，于是你写了个$\mathrm{tarjan}$，然后发现你`Accepted`了，于是这道题就结束了

```cpp
#include <bits/stdc++.h>

#define R register
#define ll long long

const int MaxN = 1e5 + 10;

struct edge
{
	int next, to;
};

ll ans = 0;
edge e[MaxN << 1];
int n, m, cnt, dfsnum, color;
std::queue<int> q;
std::vector<int> vec;
int a[MaxN], head[MaxN], ind[MaxN], col[MaxN];
int u[MaxN], v[MaxN], dfn[MaxN], low[MaxN], ins[MaxN], val[MaxN], cntt[MaxN];

inline void add_edge(int u, int v)
{
	++cnt;
	e[cnt].to = v;
	e[cnt].next = head[u];
	head[u] = cnt;
}

void tarjan(int u)
{
	dfn[u] = low[u] = ++dfsnum;
	ins[u] = 1, vec.push_back(u);
	for (int i = head[u]; i; i = e[i].next)
	{
		int v = e[i].to;
		if (!dfn[v])
			tarjan(v), low[u] = std::min(low[u], low[v]);
		else if (ins[v])
			low[u] = std::min(low[u], dfn[v]);
	}
	if (dfn[u] == low[u])
	{
		int v = 0, cnt_ = 0;
		++color;
		do
		{
			v = vec.back(), vec.pop_back();
			cnt_++, ins[v] = 0, col[v] = color, val[color] = a[v];
		} while (u != v);
	}
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	for (int i = 1; i <= m; i++)
	{
		scanf("%d%d", &u[i], &v[i]);
		if (a[u[i]] > a[v[i]])
			add_edge(u[i], v[i]);
		else
			add_edge(v[i], u[i]);
	}
	for (int i = 1; i <= n; i++)
		if (!dfn[i])
			tarjan(i);
	cnt = 0;
	memset(head, 0, sizeof(head));
	for (int i = 1; i <= m; i++)
	{
		if (col[u[i]] == col[v[i]])
		{
			ans += val[col[u[i]]];
			continue;
		}
		if (val[col[u[i]]] > val[col[v[i]]])
			add_edge(col[u[i]], col[v[i]]), ind[col[v[i]]]++;
		else
			add_edge(col[v[i]], col[u[i]]), ind[col[u[i]]]++;
	}
	vec.clear();
	for (int i = 1; i <= color; i++)
		if (ind[i] == 0)
			q.push(i);
	while (!q.empty())
	{
		int u = q.front();
		q.pop(), vec.push_back(u);
		for (int i = head[u]; i; i = e[i].next)
		{
			int v = e[i].to;
			if (ind[v])
			{
				--ind[v], ans += val[v];
				if (ind[v] == 0)
					q.push(v);
			}
		}
	}
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：Prean (赞：3)

思路很妙/youl

题目大意见翻译，说得很清楚/youl

首先，这个图到最后所有点都会被删除，所以所有边都会被删除。

但是考虑点的贡献会很麻烦，所以在这里我们考虑边的贡献。

边的贡献就是，左端点和右端点中权值较小的那个（显然）

然后没了。。。

code：
```cpp
#include<cstdio>
const int M=1e5+5;
int n,m,a[M];
long long ans;
inline int min(const int&a,const int&b){
    return a>b?b:a;
}
signed main(){
    register int i,u,v;
    scanf("%d%d",&n,&m);
    for(i=1;i<=n;++i)scanf("%d",a+i);
    for(i=1;i<=m;++i){
        scanf("%d%d",&u,&v);
        ans+=min(a[u],a[v]);
    }
    printf("%lld",ans);
}
```

---

## 作者：Evfidiw (赞：3)

~~第一次luogu题解~~

利用贪心思想，一一找出最大点（这样可以保证每条边选择相对小的点权消耗掉）


上个代码：
```cpp
#pragma G++ optimize(2)
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<queue>
#include<vector>
using namespace std;
#define REG register
#define REP(i,x,y) for(REG int i=x;i<=y;i++)
#define UP(i,x,y) for(REG int i=x;i>=y;i--)
#define IN inline
#define LL long long
#define inf 0x3f3f3f3f

const int maxn=2005;
LL ans=0;
int w[maxn];

int main(){
	int n,m;
	scanf("%d %d",&n,&m) ;
	REP(i,1,n) scanf("%d",&w[i]);
	REP(i,1,m){
		int x,y;
		scanf("%d %d",&x,&y);
		ans+=min(w[x],w[y]);	//stl太强了
	}
	printf("%lld",ans);		//听说longlong保智商
	 
    return 0;
}
```
~~似乎正解是神仙图论去写~~

~~主要是要来~~**练习贪心**~~思想~~

---

## 作者：雄鹰展翅 (赞：2)

这道题如果从点的视角来看，会十分麻烦，可以考虑从边的视角切入。

 - 对于一条边，它最后一定会被删去（如果有边没删掉则意味着有点没删掉）；
 
 - 对于一条边，它对最终答案的最优贡献为连接的两个点中较小的那个；
 
 - 对于一条边，它贡献最优时先删较大的点；
 
 - 如果所有的边都达到最优贡献，则删点的顺序为从大到小删点；
 
 - 如果从大到小删点，删一个点时权值比它大的点已经删完了，所以不会出现删点时达不到最优贡献的情况；
 
 - 故从大到小删点这种方法可行，对每一条边取连接的两个点中较小的那个即可。
 
 代码：
 
```cpp 
#include<iostream>
using namespace std;

int n,m,ans;
int a[1005];

int main(){
    int i,x,y;
    cin>>n>>m;
    for(i=1;i<=n;i++) cin>>a[i];
    for(i=1;i<=m;i++){
    	cin>>x>>y;
    	ans+=min(a[x],a[y]);
	}
	
    cout<<ans<<endl;
    return 0;
}

```

---

## 作者：nalemy (赞：1)

这道题有一种特别帅的解法。

我们以第一个样例为例，并进行如下步骤：

![](https://cdn.luogu.com.cn/upload/image_hosting/v4oh5bpu.png)

1. 将这个图上的所有节点按照点权从小到大排序，并把边标在上面（如上图所示）
2. 从后往前一个一个删点

3. 统计答案并输出
4. 等待 AC

这是从点的角度考虑的问题。为什么它是对的呢？我们需要从边的角度考虑。

对于每一条边，我们都有如下事实：

1. 它总是要被删掉
2. 当删掉自己连接的**其中一个节点**时自己就被删掉了
3. 自己被删掉时对答案产生的贡献是**没有被删掉的**那另一个节点

综上所述，因为每一条边的贡献之和就是答案，所以如果我们使得每一条边的贡献最小，那么答案也就最小。

很显然，我们只要保证每一条边的删除都是由**点权较大**的点造成的就可以了。从后往前删点正好能保证这一点。

那么如何统计答案呢？答案就隐藏在文中，每一条边的**贡献之和**就是答案！这道题不就完了？

AC 代码：

```C++
#include<iostream>
#define N 1000
using namespace std;

int w[N];
int main() {
    int n, m, ans = 0; cin >> n >> m;
    for (int i=0; i<n; i++)
        cin >> w[i];
    for (int i=0, u, v; i<m; i++)
        cin >> u >> v, ans += min(w[u-1], w[v-1]);
    return cout << ans, 0;
}
```



---

## 作者：傅思维666 (赞：1)

## 题解：

2020.11.26模拟赛T3 满分场。

场上看到最优化先想了DP。但是这道题压根就划分不出状态。看到很多大神用的拓扑序解法。各种玄学，反正我是没想到。既然DP没戏了，那就开始想贪心。

怎么贪呢？手推了几组样例，发现**每次删除的总是当前没被删除的所有点中权值最大的那个点**。然后按这个顺序都删完就是最优解。（出题人向其中加入了重边和自环，所以代码里有些许这道题用不上的点）

考场上没证明这个贪心，过了大样例就没再管。

然后场下证明这个贪心：如果不是每次删除当前状态下权值最大的节点，那么会导致这个节点至少被算入贡献一次。此时就没有直接删除它更优秀。

代码：

```cpp
#include<cstdio>
#include<set>
#include<queue>
#include<algorithm>
#define int long long
using namespace std;
const int maxn=1e4+4;
int n,m,ans;
int w[maxn];
bool v[maxn];
priority_queue<pair<int,int> >q;
set<int> e[maxn];
int tot,head[maxn],nxt[maxn<<2],to[maxn<<2];
void add(int x,int y)
{
    to[++tot]=y;
    nxt[tot]=head[x];
    head[x]=tot;
}
signed main()
{
    // freopen("star.in","r",stdin);
    // freopen("star.out","w",stdout);
    scanf("%lld%lld",&n,&m);
    for(int i=1;i<=n;i++)
    {
        scanf("%lld",&w[i]);
        q.push(make_pair(w[i],i));
    }
    for(int i=1;i<=m;i++)
    {
        int x,y;
        scanf("%lld%lld",&x,&y);
        if(x==y)
            continue;
        if(e[x].find(y)==e[x].end())
        {
            add(x,y);
            add(y,x);
            e[x].insert(y);
            e[y].insert(x);
        }
    }
    while(!q.empty())
    {
        int x=q.top().second;
        q.pop();
        v[x]=1;
        for(int i=head[x];i;i=nxt[i])
        {
            int y=to[i];
            if(v[y])
                continue;
            ans+=w[y];
        }
    }
    printf("%lld\n",ans);
    return 0;
}
```



---

## 作者：寒鸽儿 (赞：1)

考虑边的贡献。  
我们记点的权值为$w_i$。对于边的两个端点u, v.先删除u后删除v的贡献为$w_u$,否则为$w_v$。  
正确性:首先我们不能找到一种更小的方案使得取值更小。因为条边的贡献都取了最小值。然后,不会存在对于一组边得出u比v先删而对于另一组边得出v比u先删的情况,因为依据上述策略得出u比v先删的必要条件是$w_u > w_v$。而对于两个点$u, v$不可能$w_u < w_v$和$w_v < w_u$同时成立。  
```cpp
#include <iostream>
#define ull unsigned long long

using namespace std;

const int maxn = 1010;
int a[maxn];

int main() {
	ios::sync_with_stdio(false);
	ull ans = 0;
	int u, v, n, m;
	cin >> n >> m;
	for(int i = 1; i <= n; i++) cin >> a[i];
	for(int i = 1; i <= m; i++) {
		cin >> u >> v;
		ans += min(a[u], a[v]);
	}
	cout << ans << endl;
	return 0;
}
```

---

## 作者：nekko (赞：1)

一条边删除后，与它相连的两个点中的某一个点会对答案产生贡献

这样一来，从点权大的往点权小的方式删除时，一条边对答案的贡献一定是较小的那个点权

所以做完了，图都不用读

``` cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1010;

int n, m, a[N];
long long ans;

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1 ; i <= n ; ++ i) scanf("%d", &a[i]);
    while(m --) {
        int x, y; scanf("%d%d", &x, &y);
        ans += min(a[x], a[y]);
    }
    printf("%lld\n", ans);
}
```

---

## 作者：Aw顿顿 (赞：0)

## 题意

$n$ 个带权点，$m$ 条无向边，删除一个点就要付出所有与之有联系且没有被删除的点的点权之和的代价。

求删除所有点的最小代价。

## 分析

一看，这是一道贪心。再一看，一开始可以存起来所有点的代价，每次删掉一个点，就把和它相连的点代价全部减掉我的点权，然后再选择点权最大的点删掉……看着像拓扑排序。

但是这并不是一个 DAG，可能存在环，所以这并不能过。

于是你想到了，这应该是需要转化的。既然从点入手不那么顺，那么就从边入手吧。考虑图被删光的最后结果，一定是 $0$ 边 $0$ 点，那么我们删掉所有边，就等效于删掉所有点。

对于每一条边，它的最优情况下的贡献就是较小的那个点权。因为我们可以谋划删点顺序，对于每条边总是删除点权较大的那个点，从而最大限度的降低删除其他点时的代价，因此我们会付出较小点权的那个代价。

那么存边的时候顺便累加一下答案即可。

## 代码

于是代码就出人意料地简单。

```cpp
#include<bits/stdc++.h>
#define rint register int
using namespace std;
int n,m,ans,a[1005];
signed main(){
    scanf("%d%d",&n,&m);
    for(rint i=1;i<=n;i++)scanf("%d",&a[i]);
    for(rint i=1;i<=m;i++){
        int x,y;
    	scanf("%d%d",&x,&y);
    	ans+=min(a[x],a[y]);
	}printf("%d\n",ans);
    return 0;
}

```

---

## 作者：Phoenix_chaser (赞：0)

## 核心：贪心
### 本题求的是让我们得到删除所有的边

如果把图建好了再处理似乎不大好解决，于是我们就要一边建边，一边删边，这样也~~**相当于去删边**~~

但是，删边也要付出最小代价，所以我们**需要挑代价小的点去掉**

#### 只需要在输入时判断就好了

上代码：
```cpp
#include<iostream>
using namespace std;
int a[1313131],n,m,a1,a2;
long long ans=0;
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	cin>>a[i];
	for(int i=1;i<=m;i++){
	cin>>a1>>a2;
	ans+=min(a[a1],a[a2]);
}
	cout<<ans;
}
```
谢谢观看

---

## 作者：YanYou (赞：0)

# Solution
考虑每条边，容易发现权值大的点一定在权值小的点前被删。

那么每条边删除的代价都是其两个端点中较小的权值。

于是解法就很显然了，每次输入一条边，我们只要把答案加上较小的权值即可。

# Code

```pascal
var n,m,i,x,y:longint;
    ans:int64;
    a:array[0..1010] of longint;
begin
  readln(n,m);
  for i:=1 to n do read(a[i]); readln;
  for i:=1 to m do begin
    readln(x,y);
    if a[x]<a[y] then inc(ans,a[x]) else inc(ans,a[y]);
  end;
  writeln(ans);
end.
```


---

## 作者：EdenHazard (赞：0)

# 基本思路---贪心
既然要求最小代价，当用一定顺序删除时代价一定最小，不难发现，每次都删去x,y中最小的，最后的总代价业一定最小！
因此就可以写出下面的简单的代码
# 代码
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>//头文件 
using namespace std; 
int n,m,val[1025]/*权值*/,ans,x,y; 
int main()
{
	cin>>n>>m;
	for(register int i=1;i<=n;i++)
		cin>>val[i]; //输入 
	while(m--)
	{
		cin>>x>>y; 
		ans+=min(val[x],val[y]); //每步求最小 
	}
	cout<<ans<<endl;
	return 0; 
}
```
//求过！

---

## 作者：DennyQi (赞：0)

感觉这题不能完全算作贪心来看，更本质的是其中的拓扑序。

删点的实质是在删边，因为到最后所有点都会被删完。每条边的贡献一定是其两端的一个点。**理论上的最小值**就是每条边都选择较小的那个点来贡献。这要求我们**对于每条边都要先删除点权较大的点**。这让人想起了……拓扑排序！

那么这个理论上的最小值是否能够实现呢，也就是说，整个图**是否可以**拓扑排序呢？我们将每条无向边都改为从点权大的点连向点权小的边的有向边，貌似可以形成$DAG$。然而如果点权相等呢？那就可能有环。不过没关系，环内的点先后是无所谓的，可以tarjan缩点，然后就形成$DAG$了。

所以这道题删点的顺序就是其拓扑序了。

所幸这道题不需要输出方案。

```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
inline int read(){
    int x(0),w(1); char c = getchar();
    while(c^'-' && (c<'0'||c>'9')) c = getchar();
    if(c == '-') w = -1, c = getchar();
    while(c>='0' && c<='9') x = (x<<3) + (x<<1) + c - '0', c = getchar();
    return x*w;
}
int n,m,x,y,ans,a[1010];
int main(){
	n = read(), m = read();
	for(int i = 1; i <= n; ++i) a[i] = read();
	for(int i = 1; i <= m; ++i){
		x = read(), y = read();
		ans += min(a[x],a[y]);
	}
	printf("%d",ans);
	return 0;
}
```


---

## 作者：Mickey_snow (赞：0)

[CF437C](http://codeforces.com/problemset/problem/437/C) _The Child and Toy_ : 贪心

由于删除的顺序不同，每个点会为我们带来不同的代价。

但是无论我们按照什么顺序删除，我们每删除掉一个点，这个点的所有连边都会消失，如果从边的角度考虑，删除每一条边的代价最小是这条边所连两个点中价值最小的，所以可以贪心进行求解，时间复杂度为 $O(N)$.

代码如下：

```c#
using System;

namespace CF437C
{
	class Program 
	{
		static void Main(string[] args) 
		{
			string[] inp = Console.ReadLine().Split(' ');
			int totPoints = Convert.ToInt32(inp[0]), totEdges = Convert.ToInt32(inp[1]), a, b;
			int[] w = new int[totPoints];

			inp = Console.ReadLine().Split(' ');
			for(int i = 0;i < totPoints;i++)
				w[i] = Convert.ToInt32(inp[i]);

			Int64 cnt = 0;
			for(int i = 0;i < totEdges;i++) {
				inp = Console.ReadLine().Split(' ');
				cnt += Math.Min(w[Convert.ToInt32(inp[0]) - 1], w[Convert.ToInt32(inp[1]) - 1]);
			}
			Console.WriteLine(cnt.ToString());
		}
	}
}
```

---

## 作者：人间凡人 (赞：0)

#### 题意:

$n$ 个带权点，$m$ 条无向边，删除一个点就要付出所有与之有联系且没有被删除的点的点权之和的代价。求删除所有点的最小代价。

#### 思路：

求删除的最小代价，那么我们可以逐边进行考虑，每一次删除权值较大的点，所以答案应该加上权值较小的边，最后输出即可。

Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,ans,x,y,a[1005];
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=1;i<=m;i++){scanf("%d%d",&x,&y);ans=ans+min(a[x],a[y]);}
	printf("%d\n",ans);
	return 0;
}
```


---

