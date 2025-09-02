# Chat Screenshots

## 题目描述

There are $ n $ people in the programming contest chat. Chat participants are ordered by activity, but each person sees himself at the top of the list.

For example, there are $ 4 $ participants in the chat, and their order is $ [2, 3, 1, 4] $ . Then

- $ 1 $ -st user sees the order $ [1, 2, 3, 4] $ .
- $ 2 $ -nd user sees the order $ [2, 3, 1, 4] $ .
- $ 3 $ -rd user sees the order $ [3, 2, 1, 4] $ .
- $ 4 $ -th user sees the order $ [4, 2, 3, 1] $ .

 $ k $ people posted screenshots in the chat, which show the order of participants shown to this user. The screenshots were taken within a short period of time, and the order of participants has not changed.

Your task is to determine whether there is a certain order that all screenshots correspond to.

## 样例 #1

### 输入

```
10
5 1
1 2 3 4 5
4 4
1 2 3 4
2 3 1 4
3 2 1 4
4 2 3 1
6 2
1 3 5 2 4 6
6 3 5 2 1 4
3 3
1 2 3
2 3 1
3 2 1
10 2
1 2 3 4 5 6 7 8 9 10
10 9 8 7 6 5 4 3 2 1
1 1
1
5 2
1 2 3 5 4
2 1 3 5 4
3 3
3 1 2
2 3 1
1 3 2
5 4
3 5 1 4 2
2 5 1 4 3
1 5 4 3 2
5 1 4 3 2
3 3
1 3 2
2 1 3
3 2 1```

### 输出

```
YES
YES
YES
YES
NO
YES
YES
YES
YES
NO```

# 题解

## 作者：yyrwlj (赞：3)

## 思路

每个人看到的顺序不能说明具体位置，但是给出了前后关系。对于第 $i$ 个顺序，对于 $j \in [2,n-1]$，都能说明 $a_{ij}$ 在 $a_{ij+1}$ 前面。

所有前面的向后面的连边，最后拓扑排序看建出来的图是不是拓扑图。

拓扑排序判环：拓扑排序后有点没有入队过就代表有环。

每个 $a_{ij}$ 只用向后面第一个连边，因为后面第一个会和后面第二个连边，一直到最后，它们肯定是联通的，判环不需要管中间有几条边，建出来这些边只会浪费时间和空间。

## Code

```cpp
#include <iostream>
using namespace std;
const int N = 200005;
struct Edge{
    int to, nxt;
}g[N];
int h[N], d[N], idx;
int a[N], q[N];
void add(int a,int b)
{
    g[++idx].to = b, g[idx].nxt = h[a], h[a] = idx;
    d[b] ++;
}
void work()
{
    int n, k;
    scanf("%d%d", &n, &k);
    for (int i=1;i<=n;i++)
        h[i] = d[i] = 0;
    idx = 0;
    for (int i=1;i<=k;i++)
    {
        for (int j=1;j<=n;j++)
            scanf("%d", &a[j]);
        for (int j=2;j<n;j++)
            add(a[j], a[j + 1]);
    }
    int hh = 0, tt = -1;
    for (int i=1;i<=n;i++)
        if (d[i] == 0)
            q[++tt] = i;
    while (hh <= tt)
    {
        int t = q[hh ++];
        for (int i = h[t]; i; i = g[i].nxt)
        {
            int j = g[i].to;
            if (--d[j] == 0)
                q[++tt] = j;
        }
    }
    for (int i=1;i<=n;i++)
        if (d[i] > 0)
        {
            puts("NO");
            return;
        }
    puts("YES");
}
```

---

## 作者：SXqwq (赞：2)

注意到每位截图者的画面除了第一位，其余顺序都是可以确定的。考虑建图，跑拓扑排序找环。若图上存在环则不合法。

具体地，将每位截图者的图像定义为数组 $a$，则 $\forall a_i,a_{i+1}(i\ne 1) $ 连边。然后拓扑排序，如果有环则显然无法将所有的点访问，我们只需要使用一个 $cnt$ 记录访问了多少点和 $n$ 比较即可。

还是比较典的。

### Code

```cpp
#include <bits/stdc++.h> 
using namespace std;
const int N = 100010;
int n,k;
int last;
int T;
vector <int> Edge[N];
int d[N];
int vis[N];
bool flag = 1;
int cnt = 0;
queue <int> q;
void topsort()
{
	while(!q.empty())
	{
		int u = q.front();
		q.pop();
		cnt ++;
		for(auto v:Edge[u])
		{
			d[v] --;
			if(!d[v]) q.push(v);
		}
	}
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>T;
	while(T--)
	{
		cin>>n>>k;
		for(int i=1;i<=n;i++) 
		{
			d[i] = 0;
			vis[i] = 0;
		}
		for(int i=1;i<=n;i++) Edge[i].clear();
		while(!q.empty()) q.pop();
		flag = 1;
		cnt = 0;
		for(int i=1;i<=k;i++)
		{
			for(int j=1;j<=n;j++)
			{
				int x;
				cin>>x;
				if(j > 2) 
				{
					Edge[last].push_back(x);
					d[x] ++;
				}
				last = x; 
			}
		}
		for(int i=1;i<=n;i++)
		{
			if(!d[i]) 
			{
				q.push(i);
			}
		}
		topsort();
		if(cnt == n) cout<<"Yes"<<endl;
		else cout<<"No"<<endl;
	}
}
```

---

## 作者：信息向阳花木 (赞：2)

输入每次给的信息相当于，除了第一个人，其他 $n - 1$ 个人都满足前一个在聊天室的位置在后一个人前面。给了 $k$ 组这样的信息，问 $n$ 个人有没有一种满足所有信息的顺序。

显然可以按大小关系建一个有向图。如果确定 $x$ 在 $y$ 前面，就从 $x$ 向 $y$ 连一条有向边。如果其中出现了环，就无解。否则就按拓扑序排。显然判环直接用拓扑排序判环就好了。

```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

typedef pair<int, int> PII;

const int N = 200010;

int t, k, n;
int a[N], h[N], e[N], ne[N], r[N], idx;

void add(int x, int y)
{
	e[idx] = y, ne[idx] = h[x], h[x] = idx ++;
}

int main()
{
	scanf("%d", &t);
	while (t -- )
	{
		memset(h, -1, sizeof h);
		memset(r, 0, sizeof r);
		idx = 0;
		scanf("%d%d", &n, &k);
		for (int i = 1; i <= k; i ++ )
			for (int j = 1; j <= n; j ++ )
			{
				scanf("%d", &a[j]);
				if(j <= 2) continue;
				add(a[j - 1], a[j]);
				r[a[j]] ++;
			}
		queue<int> q;
		int cnt = 0;
		for (int i = 1; i <= n; i ++ ) if(!r[i]) q.push(i);
		while (!q.empty())
		{
			int t = q.front(); cnt ++;
			q.pop();
			for (int i = h[t]; ~i; i = ne[i])
			{
				int j = e[i];
				r[j] --;
				if(r[j] == 0) q.push(j);
			}
		}
		if(cnt == n) puts("Yes");
		else puts("No");
	}
	return 0;
}
```

---

## 作者：2huk (赞：2)

> 有 $n$ 个人在排队，编号 $1 \sim n$。他们已经按照一定的顺序排好队了。
>
> 其中的 $k$ 个人发了 $k$ 条消息，表示他看到的所有人的排队顺序。但是每个人发的消息中都把自己放在了最前面。
>
> 请你判断这 $k$ 个人是否都说的是真话。
>
> 多测。$1 \le t \le 10^4$，$1 \le k \le n \le 2 \times 10^5$，$\sum n\cdot k \le 2 \times 10^5$。

由于每条消息的发送者都会把自己排在最前面，所以所有的 $a_{i, 1}$ 都是没有用的。我们推理需要用的信息为 $a_{i, 2}, a_{i, 3}, \dots, a_{i, n}$。

这些信息意味着 $a_{i, 2}$ 一定在 $a_{i, 3}$ 之前，$a_{i, 3}$ 一定在 $a_{i, 4}$ 之前，以此类推，$a_{i, k - 1}$ 一定在 $a_{i, k}$ 之前。

对于这种两者之间有关系的推理，可以启发我们将其转化成图论问题。

若我们将 $a_{i, j} \to a_{i, j + 1}(2 \le j < k)$ 连边，表示 $a_{i, j}$ 在 $a_{i, j + 1}$ 之前。那么如果最终的图中**有环**，就代表答案为 NO。反之为 YES。

判断图中是否有环可以使用拓扑排序。若我们用拓扑排序的方法遍历完整张图后，存在节点没有遍历到，那么图中有环。否则无环。

```cpp
void solve() {
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= k; ++ i ) {
		int x, y;
		scanf("%d", &x);
		for (int j = 2; j <= n; ++ j ) {
			scanf("%d", &y);
			if (j != 2) g[x].push_back(y);
			x = y;
		}
	}
	
	for (int i = 1; i <= n; ++ i ) {
		sort(g[i].begin(), g[i].end());
		g[i].erase(unique(g[i].begin(), g[i].end()), g[i].end());
		for (int j : g[i]) ++ d[j];
	}
	
	int cnt = 0;
	queue<int> q;
	for (int i = 1; i <= n; ++ i )
		if (!d[i])
			q.push(i),
			st[i] = true;
	
	while (q.size()) {
		int t = q.front();
		q.pop();
		for (int v : g[t]) {
			if (!st[v]) {
				if (!( -- d[v])) {
					st[v] = true;
					q.push(v);
				}
			}
		}
	}
	
	for (int i = 1; i <= n; ++ i ) cnt += st[i];
	puts(cnt == n ? "Yes" : "No");
}
```

---

## 作者：__FL__ (赞：1)

## 题意
有 $n$ 个人在一个聊天队列里，对于第 $i$ 个人来说，他看到的序列是将 $i$ 放在最前面，且其余人的顺序不变。现在给定一些人看到的序列，请你判断存不存在一个可能的聊天队列。
## 分析
对于每个序列，第一个人在哪里无法确定，但我们知道其他人的顺序，可以使用拓扑排序。除第一个人以外，其他人从前往后顺次连边（$A_2 \to A_3 \to A_4 \to ... \to A_n$），表示一个从前往后的次序，然后跑一遍拓扑排序就可以了。

需要注意的是，题目判断的是拓扑能不能跑下来，也就是图中有没有环。我们可以使用一个 $cnt$ 变量，每找到一个新点就加一，最后判断找到的总点数是不是 $n$ 就可以了。
## 代码
因为是多测，所以注意清空。
```cpp
#include <bits/stdc++.h>
using namespace std;
int t,n,k,a[200005],in[200005];
vector<int>vec[200005];
queue<int>q;
bool toposort() //拓扑排序
{
	int cnt = 0; //点的数量
	while (!q.empty())
	{
		int now = q.front();
		q.pop();
		cnt++;
		for (int i: vec[now])
			if (--in[i] == 0)
				q.push(i);
	}
	if (cnt == n) return 0;
	return 1;
}
void solve()
{
	scanf("%d %d",&n,&k);
	for (int i = 1; i <= n; i++) //清空
	{
		vec[i].clear();
		in[i] = 0;
	}
	for (int i = 1; i <= k; i++)
	{
		for (int j = 1; j <= n; j++)
			scanf("%d",&a[j]);
		for (int j = 2; j < n; j++)
			{vec[a[j]].push_back(a[j+1]); in[a[j+1]]++;} //连边
	}
	for (int i = 1; i <= n; i++)
		if (!in[i])
			q.push(i);
	if (toposort()) printf("NO\n");
	else printf("YES\n");
}
int main()
{
	scanf("%d",&t);
	while (t--)
		solve();
	return 0;
}
```

---

## 作者：zhanglh (赞：1)

### 拓扑序

根据给定的 $k$ 个顺序建有向图。对于每个顺序，建从当前元素指向下一个元素的有向边，其中前两个元素之间不建边。跑一遍拓扑序判环，没环则代表存在合法的方案，反之则不存在。

[Code](https://www.luogu.com.cn/record/146887178)

---

## 作者：Lele_Programmer (赞：1)

# CF1931F 题解

## 题目大意

$n$ 个人排成一个队伍，但对于第 $i$ 个人，他总会将自己排在第一位，其余的人会按照在原队列里的顺序出现在他的描述中。

不妨举个例子：

队伍为 $ 1,5,2,3,4 $。

第 1 个人的描述 $ 1,5,2,3,4 $。

第 2 个人的描述 $ 2,1,5,3,4 $。

第 3 个人的描述 $ 3,1,5,2,4 $。

第 4 个人的描述 $ 4,1,5,2,3 $。

第 5 个人的描述 $ 5,1,2,3,4 $。

题目问的是，给你 $k$ 个对总人数为 $n$ 的队伍的描述，问是否存在一个可行的队伍。

## 题目分析

我们不难发现，对于一个人的描述，除去最左边的人（也就是他自己）之外，后面的若干个数都是原队列的子序列，顺序是没有变化的。

不妨将每一个人视为一个节点，按照每个人的描述，将除去第一个元素之外的所有数，从左到右进行连边。

举个例子：

假设一个人的描述是这样的：$ 3,1,5,2,4 $。

那么我们会从 $1$ 向 $5$ 连边，从 $5$ 向 $2$ 连边，从 $2$ 向 $4$ 连边。

那如何判断有没有解呢？

不难发现，当建立的图是一张 DAG（有向无环图），则有解，如果出现环，则无解。

再举个例子：

假设有一个人描述的 $1$ 处于 $3$ 之前，而另一个人的描述中，$1$ 位于 $3$ 之后，那么这张图就会出现环，出现矛盾，无解。

所以，我们不妨通过拓扑排序，判定一张有向图是否为 DAG 即可！

## 拓扑排序过程

1. 先将原图中所有入度为 0 的点入队。
2. 从队列中取出一个点，删除与该点有关的所有边。
3. 将新的入度为 0 的点入队。
4. 若队列不为空，回到步骤 2.。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N=200005;
const int M=400005;

int T,n,k,tmp,last;
int a[N];
int e[M],ne[M],h[N],tot;
int in[N];

void add(int a,int b) {
    e[tot]=b,ne[tot]=h[a],h[a]=tot++;
}

bool topu() {
    int cnt=0;
    queue<int> q;
    for (int i=1;i<=n;++i) {
        if (in[i]==0) {
            q.push(i);
        }
    }
    while (!q.empty()) {
        int u=q.front(); q.pop();
        cnt++;
        for (int i=h[u];~i;i=ne[i]) {
            in[e[i]]--;
            if (in[e[i]]==0) {
                q.push(e[i]);
            }
        }
    }
    return cnt==n;
}

int main() {
    scanf("%d",&T);
    while (T--) {
        scanf("%d %d",&n,&k);
        tot=0;
        for (int i=1;i<=n;++i) h[i]=-1,in[i]=0;
        for (int i=1;i<=k;++i) {
            for (int i=1;i<=n;++i) {
                scanf("%d",&tmp);
                if (i>=3) {
                    add(last,tmp);
                    in[tmp]++;
                }
                last=tmp;
            }
        }
        if (topu()) puts("YES");
        else puts("NO");
    }
    return 0;
}
```

最后，祝贺我赛时 18 分钟无伤 AC 此题~

---

## 作者：I_will_AKIOI (赞：1)

### 题目大意

有 $k$ 个数组和一个原数组，这 $k$ 个数组都是将原数组中的一个数放到最前面得到的，求原数组是否存在。

### 思路

我们考虑暴力枚举，枚举每个数组可能由哪个原数组变换来的，如果某个原数组可以被 $k$ 个数组变换而来，说明存在。

所以每次循环，交换 $i$ 和 $i+1$，用 map 记录当前的序列出现次数，看有没有出现 $k$ 次。

由于记录一整个序列，复杂度还得乘上一个 $n$，所以考虑哈希。每次交换，减去交换的两个位置对哈希值的贡献，交换后在加回来。复杂度 $O(nk\log n)$。我看正解是建图跑拓扑排序，我的解法还是太麻烦了。

注意多测要清空，我赛时就 TLE 了，导致本题没过。

### 代码

```
#include<bits/stdc++.h>
#define int unsigned long long
#define BASE 9191891
using namespace std;
int t,n,k,p[200005],h[200005];
vector<int>v[200005],a;
map<int,int>vis;
void Hash(int x)
{
  for(int i=0;i<n;i++) h[x]=h[x]*BASE+v[x][i];
  return;
}
bool check()
{
  for(int i=0;i<a.size();i++) if(vis[a[i]]==k) return 1;//有一个序列出现了k次，说明存在
  return 0; 
}
signed main()
{
  ios::sync_with_stdio(0);
  cin>>t;
  while(t--)
  {
  	cin>>n>>k;
  	for(int i=1;i<=k;i++) h[i]=0;
  	for(int i=1;i<=k;i++) v[i].clear();
  	vis.clear();
  	a.clear();
  	for(int i=1;i<=k;i++)
  	{
  	  for(int j=1;j<=n;j++)
  	  {
  	  	int x;
  	  	cin>>x;
  	  	v[i].push_back(x);
	  }
	  Hash(i);
	  if(vis[h[i]]==0) a.push_back(h[i]);//a数组记录哪些值出现过
	  vis[h[i]]++;
	}
	p[0]=1;
	for(int i=1;i<=n;i++) p[i]=p[i-1]*BASE;
	for(int i=1;i<=k;i++)
	{
	  for(int j=0;j<n-1;j++)
	  {
	    h[i]-=p[n-j-1]*v[i][j];
	  	h[i]-=p[n-j-2]*v[i][j+1];
	  	swap(v[i][j],v[i][j+1]);
	  	h[i]+=p[n-j-1]*v[i][j];
	  	h[i]+=p[n-j-2]*v[i][j+1];
	  	//交换两个数位，并求出hash值 
	  	if(vis[h[i]]==0) a.push_back(h[i]);
	  	vis[h[i]]++;
	  }
	}
	if(check()) cout<<"YES\n";
	else cout<<"NO\n";
  }
  return 0;
}
```

---

## 作者：sjr3065335594 (赞：0)

## 题意简述

给出 $n$ 个人进行的聊天室中，$k$ 个人做的截图，每个截图中截图者都在第一位置，其后各位按照发帖时间前后确定。判断这些聊天室截图是否自洽（即能确定至少一种可能的发帖顺序）。

## 思路

由前往后处理每一个人的截图，假设第一个截图是 `1 2 3 4`，那么我们就可以知道 3 在 2 的后边，4 在 3 的后边，如果在后边的截图中出现了 `2 1 4 3` 说明 3 又在 4 的后边，与前边的结论矛盾，所以无法自洽。

所以可以将问题进行转化，给定一些 $a_i<a_j$ 的不等关系，问最后有没有一种赋值方式，使得 $a_i$ 各不相同且满足所有的不等关系约束。

考虑使用 tarjan，对于 $a_i<a_j$ 这一条约束关系，我们只需要从 $i$ 向 $j$ 建一条有向边，此时，如果存在一条 $j\to i$ 的路线，即存在一个环，说明这些约束一定是矛盾的，所以建图使用 tarjan 判是否存在环即可。

## 代码实现

```cpp
#include<bits/stdc++.h>
#define ll long long
#define mkp(x,y) make_pair(x,y)
#define CLR(a,x) memset(a,x,sizeof(a))
//#define int long long
//#define int __int128
using namespace std;
const int N=2e5+5;
const int M=1e6+5;
const int INF=2e9+5;
int t,n,K,a[N],head[N],cnt,flag;
struct EDGE {
	int v,next;
}edge[M];
void add_edge(int x,int y) {
	edge[++cnt]=(EDGE){y,head[x]};
	head[x]=cnt;
}
int DFN[N],Low[N],Time,instac[N],stac[N],top;
void tarjan(int x) {
	DFN[x]=Low[x]=++Time;
	instac[x]=1;stac[++top]=x;
	for(int i=head[x];~i;i=edge[i].next) {
		int v=edge[i].v;
		if(!DFN[v])tarjan(v),Low[x]=min(Low[x],DFN[v]);
		if(instac[v])Low[x]=min(Low[x],Low[v]);
	}
	if(Low[x]==DFN[x]) {
		int y,c=0;
		while(y=stac[top--]) {
			instac[y]=0;
			if(x==y)break;
			c++;
		}
		if(c)flag=1;
	}
}
void solve() {
	scanf("%d%d",&n,&K);flag=0;
	for(int i=1;i<=n;i++)head[i]=-1;
	for(int i=1;i<=n;i++)DFN[i]=Low[i]=Time=instac[i]=0;
	top=0;
	for(int i=1;i<=cnt;i++)edge[i].v=edge[i].next=0;
	for(int i=1;i<=K;i++) {
		for(int j=1;j<=n;j++)
			scanf("%d",&a[j]);
		for(int j=2;j<=n-1;j++)
			add_edge(a[j+1],a[j]);
	}
	for(int i=1;i<=n;i++)
		if(!DFN[i])tarjan(i);
	if(flag)printf("NO\n");
	else printf("YES\n");
}
int main() {
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	scanf("%d",&t);
	while(t--)solve();
	return 0;
}

```


---

## 作者：_smart_stupid_ (赞：0)

## [题目](https://codeforces.com/contest/1931/problem/F)

我们发现，对于每一张截图，除开第一个数字，如果 $a$ 比 $b$ 靠前，说明序列中 $a$ 比 $b$ 靠前。如有一张截图中 $a$ 比 $b$ 靠前，另一张截图中 $b$ 比 $a$ 靠前（均除开第一个数字），说明无解。暴力枚举 $a$ 和 $b$ 是不行的。我们发现这个关系可以看做一张图中的边，而每一个数字就是一个点。如果这张图中有环，说明无解。

对于每一张截图，除开第一个数字，对于每一个剩下的数字，我们往后面的一个数字建一条有向边，不需要建多条，因为其他的关系可以通过这些边推导出来。然后在这张图上判断一遍是否有环即可。可以用 DFS 或拓补排序判断。我推荐拓补，稳定的 $O(n)$。

## AC Code：

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
#include <stack>
#include <cmath>
#include <list>
#include <set>
#include <map>
using namespace std;
struct edge{
	int u, v, nxt;
};
edge ed[400100];
int edcnt, head[200100];
void addedge(int u, int v){
	edcnt++;
	ed[edcnt].u = u;
	ed[edcnt].v = v;
	ed[edcnt].nxt = head[u];
	head[u] = edcnt;
}
int t;
int n, k;
int a[200100];
int deg[200100];
queue<int> q;

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> t;
	while (t --) {
		edcnt = 0;
		memset(head, 0, sizeof(head));
		memset(deg, 0, sizeof(deg));
		cin >> n >> k;
		for (int i = 1; i <= k; i ++) {
			for (int j = 1; j <= n; j ++) {
				cin >> a[j];
			}
			for (int j = 2; j < n; j ++) {
				addedge(a[j], a[j + 1]);
				deg[a[j + 1]]++;
			}
		}
		for (int i = 1; i <= n; i ++) {
			if (!deg[i]) {
				q.push(i);
			}
		}
		int cnt = 0;
		while (q.size()) {
			int now = q.front();
			q.pop();
			cnt++;
			for (int i = head[now]; i; i = ed[i].nxt) {
				int v = ed[i].v;
				deg[v]--;
				if (!deg[v]) {
					q.push(v);
				}
			}
		}
		if (cnt == n) {
			cout << "YES\n";
		}
		else {
			cout << "NO\n";
		}
	}
	return 0;
}
```

---

## 作者：I_am_kunzi (赞：0)

# CF1931F 题解

### 题目翻译

现在有一个 $ n $ 人的聊天室，$k $ 个人来截图，他们截图的方法是：将自己的帖子排在第一位，剩下的按照顺序依次排列。问有无一种合法的发帖顺序，满足这 $ k $ 个人的截图。

### 题目思路

我们发现，$k $ 个人截图都有一个特征：后面 $ n - 1 $ 个帖子的顺序是正确的，和顺序有关的东西，很容易让人想到拓扑排序。我们可以对后 $ n - 1 $ 个帖子中相邻两个连一条从前到后的有向边，在拓扑排序的过程中记录下当前答案中有几个点，最后判断这个数值是否为 $ n$。如果是，那么证明这 $ n $ 个点有一个合法的拓扑序，即答案存在；反之则答案不存在。

### 题目代码

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<string>
#include<algorithm>
#include<iomanip>
#include<vector>
#include<map>
#include<queue>
#include<stack>
#include<set>
#include<list>
#include<limits.h>
using namespace std;
void solve()
{
	int n , k;
	scanf("%d%d" , &n , &k);
	vector < int > in(n + 5); // 入度
	vector < int > v[n + 5]; // 边表
	for(int i = 1 ; i <= k ; i++)
	{
		vector < int > a(n + 5); // 第 i 个人截出图片中 n 个人的顺序
		for(int j = 1 ; j <= n ; j++)
		{
			scanf("%d" , &a[j]);
		}
		for(int j = 2 ; j < n ; j++) // ，每次从 j 向 j + 1 连边，注意边界范围
		{
			in[a[j + 1]]++;
			v[a[j]].push_back(a[j + 1]);
		}
	}
	int nowans = 0; // 当前选定了几个点
	queue < int > q; // 正常的拓扑排序，将每找到答案就输出改为 nowans++;
	for(int i = 1 ; i <= n ; i++)
	{
		if(!in[i])
		{
			q.push(i);
			nowans++;
		}
	}
	while(q.size())
	{
		int i = q.front();
		q.pop();
		for(int j : v[i])
		{
			in[j]--;
			if(in[j] == 0)
			{
				q.push(j);
				nowans++;
			}
		}
	}
	printf("%s\n" , (nowans == n ? "Yes" : "No")); // 输出答案
}
signed main()
{
	int t;
	scanf("%d" , &t);
	while(t--)
	{
		solve();
	}
	return 0;
}
```

---

## 作者：SamHJD (赞：0)

## Chat Screenshots

### Description

有一个 $1\dots n$ 的排列 $a$，给出 $k$ 个信息，每个信息为将排列中的某个元素移到首位后的排列 $a'$。问是否有一个排列满足每一个信息。

### Solution

对于每一个信息仅有 $[2,n]$ 是有用的，我们可以知道这些数在原排列中的位置关系。设 $3\le i\le n$，我们将 $a'_i$ 连向 $a'_{i-1}$，代表 $a'_i$ 的位置在 $a'_{i-1}$ 之后。最终建成的图若有环则无解。

### [code](https://codeforces.com/contest/1931/submission/246352498)

---

## 作者：VitrelosTia (赞：0)

对于一个截图，除了发布者也即第一个数，后面的数都代表了前后顺序。解决这种前后顺序矛盾的问题非常经典的思路是按时间顺序的前后关系建图然后拓扑排序，如果出现了环就代表“某个人同时出现在一个人前后”，这代表着矛盾。

```cpp
struct Edge { int to, nxt; } e[N];
int cur, head[N], in[N];
void Add(int u, int v) { e[++cur] = {v, head[u]}; head[u] = cur; in[v]++; }
#define GoEdge(i, u, v) for (int v, i = head[u]; v = e[i].to, i; i = e[i].nxt)
 
bool topo() {
	queue <int> q;
	for (int u = 1; u <= n; u++) 
		if (in[u] == 0) 
			q.push(u);
	while (!q.empty()) {
		int u = q.front(); q.pop();
		GoEdge(i, u, v)
			if ((--in[v]) == 0) 
				q.push(v);
	}
	for (int u = 1; u <= n; u++)
		if (in[u] != 0) 
			return false;
	return true;
}
void solve() {
	cin >> n >> k;
	for (int i = 1; i <= n; i++) head[i] = in[i]; cur = 0;
	while (k--) {
		for (int i = 1; i <= n; i++) cin >> a[i];
		for (int i = 2; i < n; i++) Add(a[i + 1], a[i]);
	}
	cout << (topo() ? "Yes\n" : "No\n");
}
 
```

---

## 作者：DrAlfred (赞：0)

# Codeforces Round 925 (Div. 3) F - Chat Screenshots 题解

## 题意

有一个排行榜 $A$，其中 $A_i$ 表示第 $i$ 名的用户编号 ( $1 \leq A_i \leq n$ )。用户 $i$ 看到的排行榜会把他本身放在第一位，其余用户按照在原排行榜中的相对顺序排列。

现在给定 $k$ 个用户看到的排行榜，问是否存在至少一个满足每位用户看到的排行榜的原排行榜。

## 分析思路

记第 $i$ 个看到的排行榜的第 $j$ 位为 $a_{i, j}$ ( $1 \leq i \leq k, 0 \leq j < n$ )。则 $a_{i, 1}, a_{i, 2}, \cdots, a_{i, n - 1}$ 为有效信息，可以得到在原排行榜中的相对顺序有 $ a_{i, 1} < a_{i, 2} < \cdots < a_{i, n - 1} $。

考虑对问题进行图论建模。若可以得到 $x$ 在原排行榜中的排名相较于 $y$ 比较靠前，则连接一条 $y \to x$ 的有向边。若图中有环，即出现矛盾。所以建立图之后判断环即可。拓扑排序或 `dfs` 均可解决有向图判环问题。

时间复杂度 $O(\sum {n \cdot k})$，可以通过本题。

## 代码

`dfs` 版：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 200010;
vector<int> G[N];
int t, n, k, a[N], vis[N], col[N];
inline bool judge(int x) {
    col[x] = 0;
    for (auto y : G[x]) {
        if (col[y] == 0) return false;
        else if (col[y] == -1) {
            if (!judge(y)) return false;
        }
    }
    return col[x] = 1, true;
}
inline bool check(void) {
    for (int i = 1; i <= n; i++) {
        if (col[i] == -1 && !judge(i)) {
            return false;
        }
    }
    return true;
}
inline void solve(void) {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        vis[i] = 0, G[i].clear(), col[i] = -1;
    }
    for (int i = 1; i <= k; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> a[j];
            if (j >= 3) G[a[j]].push_back(a[j - 1]);
        }
    }
    cout << (check() ? "YES" : "NO") << '\n';
}
inline void optimizeIO(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
}
int main(int argc, char const *argv[]) {
    optimizeIO(), cin >> t;
    while (t--) solve();
    return 0;
}

```

拓扑排序版：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 200010;
vector<int> G[N];
int t, n, k, u, a[N], in[N], vis[N];
inline bool check(void) {
    int cnt = 0;
    queue<int> Q;
    for (int i = 1; i <= n; i++) {
        if (in[i] == 0) Q.push(i);
    }
    while (!Q.empty()) {
        u = Q.front(), Q.pop();
        if (!vis[u]) vis[u] = 1, ++cnt;
        for (auto v : G[u]) {
            if (--in[v] == 0) Q.push(v);
        }
    }
    return cnt == n;
}
inline void solve(void) {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        G[i].clear(), in[i] = vis[i] = 0;
    }
    for (int i = 1; i <= k; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> a[j];
            if (j >= 3) {
                G[a[j]].push_back(a[j - 1]), ++in[a[j - 1]];
            }
        }
    }
    cout << (check() ? "YES" : "NO") << '\n';
}
inline void optimizeIO(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
}
int main(int argc, char const *argv[]) {
    optimizeIO(), cin >> t;
    while (t--) solve();
    return 0;
}

```

---

## 作者：tanghg (赞：0)

对于这种约束的问题我们通常都去思考能否转成图论问题。

本题之中，我们发现其实本题就是让我们去确定一个先后关系是否成立。那对于每一个给出的截图，我们对 $a_{j}$ 向 $a_{j+1}$ 连一条有向边代表一个顺序关系（$a_1$ 除外），之后如果有环显然就代表这个顺序关系回来了，也就错误了。那就拓扑排序去判环即可。

```cpp
#include <bits/stdc++.h>
#define endl "\n"
using namespace std;
typedef long long ll;
const ll MAXN=2e5+5;
ll t;
ll n,k;
vector<ll>adj[MAXN];
ll ind[MAXN];
bool huan(){
    queue<ll>q;
    for(int i=1;i<=n;++i){
        if(ind[i]==0){
            q.push(i);            
        }
    }
    ll num=0;
    while(!q.empty()){
        ll u=q.front();
        //cout<<u<<endl;
        q.pop();
        num++;
        for(auto v:adj[u]){
            ind[v]--;
            if(ind[v]==0){
                q.push(v);
            }
        }
    }
    return num!=n;
}
int main(){
    ios::sync_with_stdio(false);
    cin>>t;
    while(t--){
        cin>>n>>k;
        for(int i=1;i<=n;++i){
            ind[i]=0;
            adj[i].clear();
        }
        for(int i=1;i<=k;++i){
            ll x;
            cin>>x;
            ll last=0;
            if(n>1){
                cin>>last;
            }
            for(int j=1;j<=n-2;++j){
                ll u;
                cin>>u;
                adj[last].push_back(u);
                ind[u]++;
                //cout<<last<<" "<<u<<endl;
                last=u;
            }
        }
        if(huan()){
            cout<<"NO"<<endl;
        }else{
            cout<<"YES"<<endl;
        }
    }
    return 0;
}
```

---

