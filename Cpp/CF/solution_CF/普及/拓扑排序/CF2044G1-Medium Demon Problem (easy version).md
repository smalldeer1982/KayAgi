# Medium Demon Problem (easy version)

## 题目描述

这是问题的简化版。两个版本之间的关键区别以粗体显著标出。

有一群 $n$ 只蜘蛛聚在一起交换他们的毛绒玩具。最初，每只蜘蛛都有 $1$ 个毛绒玩具。每年，如果第 $i$ 只蜘蛛拥有至少一个毛绒玩具，它就会给第 $r_i$ 只蜘蛛一个毛绒玩具。否则，它将不会进行任何操作。注意，所有的毛绒玩具转移是同时进行的。在这个版本中，如果一只蜘蛛在任意时刻拥有超过 $1$ 个毛绒玩具，它们会丢掉多余的，只保留一个。

如果在某年开始时，每只蜘蛛拥有的毛绒玩具数量与上一年相同，则这一年的过程是稳定的。请注意，第 $1$ 年永远不会是稳定的。

请找出该过程中首次出现稳定的年份。

## 说明/提示

对于第二个测试用例：

- 在第 $1$ 年，每只蜘蛛的毛绒玩具数量为 $[1, 1, 1, 1, 1]$。然后进行当年的交换。
- 到了第 $2$ 年，各蜘蛛的毛绒玩具数量仍然为 $[1, 1, 1, 1, 1]$。由于数量没有变化，因此这一年是稳定的。

对于第三个测试用例：

- 在第 $1$ 年，所有蜘蛛的毛绒玩具数量为 $[1, 1, 1, 1, 1]$。然后进行第 $1$ 年的交换。
- 在第 $2$ 年，这些数量变为 $[1, 1, 1, 1, 0]$ 。然后进行第 $2$ 年的交换。即便有两只蜘蛛给了第 $2$ 只蜘蛛毛绒玩具，第 $2$ 只蜘蛛也只能保留一个。
- 到第 $3$ 年，数量变为 $[1, 1, 0, 1, 0]$。然后进行交换。
- 第 $4$ 年，数量变为 $[1, 1, 0, 0, 0]$。然后进行交换。
- 第 $5$ 年，数量仍然为 $[1, 1, 0, 0, 0]$。由于数量保持不变，这一年是稳定的。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
5
2
2 1
5
2 3 4 5 1
5
2 1 4 2 3
5
4 1 1 5 4
10
4 3 9 1 6 7 9 10 10 3```

### 输出

```
2
2
5
4
5```

# 题解

## 作者：__Deng_Rui_Song__ (赞：9)

# presafe

~~从未见过如此水的 G 题~~

~~哦 Div 4 那没事了~~
# update

感谢 @XH9979 指出代码的错误！！！
# problem

[题目转送们](https://www.luogu.com.cn/problem/CF2044G1)

有 $n$ 个蜘蛛，每个蜘蛛有一个玩具，每隔一单位时间，每个蜘蛛 $i$ 就要把自己的**所以玩具**给 $r_i$，每个蜘蛛**最多只能有一个玩具**，多出来的要丢弃，这个一下简称传递。

若传递后每个蜘蛛的状态（有或没有玩具）与传递前相同，那么把这个时刻称为特殊时刻，求最早的特殊时刻。

# solution

## 1. 基环树

### 1.1. 什么是基环树

基环树就是有 $n$ 个点和 $n$ 条边且连通的图，换句话说，就是一棵树上再加一条边。

### 1.2. 什么是基环树森林

顾名思义，基环树森林就是有很多个基环树，本题就是一个基环树森林。

## 2. 环

### 2.1. 本题环的特殊

很明显，如果所有玩具都在一个环内，那么传递后肯定是特殊时刻，如果还是没搞明白，请看下图：![](https://cdn.luogu.com.cn/upload/image_hosting/n8x3nzad.png)

### 2.2 拓扑排序找环

拓扑排序能找环（你不会不知道吧），很明显，在环里的点互相咬合，谁也松弛不了谁，如果还是没搞懂，请看下图：![](https://cdn.luogu.com.cn/upload/image_hosting/m8018vv7.png)那找环有什么用呢？上面说过，如果所有玩具都在一个环内，传递后肯定是特殊时刻，那么就找什么时候所有玩具在一个环内嘛，什么时候呢？答案就是入度为 $0$ 的点到环的距离的最大值，如果还没弄懂，请看下图：![](https://cdn.luogu.com.cn/upload/image_hosting/m0jg1trh.png)可是怎么求呢？别急，~~欲知后事如何，请听下回分解。~~

### 2.3 拓扑排序与递推

既然图已经有序了，那是不是可以递推呢？设 $dp_i$ 为入度为 $0$ 到点 $i$ 的距离，那么把连着它的点放到一个集合 $S$，那么 $dp_i=\max\forall j\in S dp_j + 1$，初始化就给入度为 $0$ 的初始化为 $0$ 或 $1$，如果还搞不明白，请看下图：![](https://cdn.luogu.com.cn/upload/image_hosting/zrwmkdt3.png)

# code

```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n, in[200005], dp[200005];
vector<int> g[200005];
int topsort() {
  int ans = -1;
  queue<int> q;
  for (int i = 1; i <= n; i++) {
    if (!in[i]) q.push(i);
    dp[i] = 0;
  }// 初始化
  while (!q.empty()) {
    int x = q.front();
    q.pop();
    ans = max(ans, dp[x]);// 统计答案
    for (int i = 0; i < g[x].size(); i++) {
      int nxt = g[x][i];
      dp[nxt] = max(dp[nxt], dp[x] + 1);// 转移
      if (!--in[nxt]) q.push(nxt);
    }
  }
  return ans + 3;//第一个 +1：边数变点数，第二个 +1：变成时刻，第三个 +1：要过一个单位时间才跟上一个时刻相等
}
void solve() {
  cin >> n;
  for (int i = 1, x; i <= n; i++) {
    cin >> x;
    g[i].push_back(x);
    in[x]++;
  }
  cout << topsort() << '\n';
  for (int i = 1; i <= n; i++) {
    g[i].clear();
    in[i] = 0;
  }// 多测不清空，爆零两行泪
}
int main() {
  for (cin >> t; t--; solve());
  return 0;
}
```

# postscript

打字 + 画图不易，求点赞 + 收藏，谢谢！

---

## 作者：zyhe2013 (赞：3)

## 思路：

如果一个蜘蛛没有别人给他玩具，他就无法给别人了，那个人的玩具数量就减一，然后下一轮他就无法参与交换了。可以用类似拓扑排序的算法解决。然后用一个数组存储给他玩具的蜘蛛个数。如果一个人的玩具没了，就把它给的蜘蛛的玩具数量减一。直到没有会减少的为止。在这个过程中记录年份，最后答案是最大的年份加一。

## 配图：

![](https://cdn.luogu.com.cn/upload/image_hosting/lvp5rslb.png)

## 代码：

奇异马蜂谨慎观看。

```cpp
#include<bits/stdc++.h>
using namespace std;
int r[200005],f[200005];
struct node
{
  int x,t;
};
signed main()
{
  int T;
  cin>>T;
  while(T--)
  {
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)f[i]=0;
    for(int i=1;i<=n;i++)
    {
      cin>>r[i];
      f[r[i]]++;
    }
    for(int i=1;i<=n;i++)f[i]--;
    queue<node>q;
    for(int i=1;i<=n;i++)if(f[i]<0)q.push({r[i],2});
    int maxn=2;
    while(!q.empty())
    {
      int tx=q.front().x,ti=q.front().t;
      q.pop();
      maxn=max(maxn,ti+1);
      f[tx]--;
      if(f[tx]<0)q.push({r[tx],ti+1});
    }
    cout<<maxn<<"\n";
  }
  return 0;
}
```

---

## 作者：yangjinqian (赞：1)

赛时以为是模拟，然后挂了。。。

## 题意

有 $n$ 只蜘蛛，每只蜘蛛有一个指向的对象，初始时每只蜘蛛都有一个毛绒玩具，每经过一秒，每只蜘蛛会给指向的对象一个毛绒玩具，如果一只蜘蛛有大于 $2$ 个毛绒玩具，他会扔掉一些，只留 $1$ 个毛绒玩具，求第几秒时当前状态和上一秒一样（注：第一秒不算）。

## 思路

可以想成一个图的问题，对每只蜘蛛建一条指向他的对象的边，如果当前状态是稳定的，证明这在一个环里面，那么拓扑求一下环，并 dp 求到环的最长链的长度，这个长度加二就是答案了。

## code

```
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
int T, n;
queue<int> q;
vector<int> v;
vector<int> a[N];
int d[N], st[N], f[N];
int main(){;
	cin >> T;
	while (T--){
		cin >> n;
		int maxx = -1;
		for (int i = 1; i <= n; i++){
			int x;
			cin >> x;
			a[i].push_back(x);
			d[x]++;
		}
		for (int i = 1; i <= n; i++)
			if (!d[i])
				q.push(i);
		while (!q.empty()){
			int u = q.front(); q.pop();
			v.push_back(u);
			st[u] = 1;
			maxx = max(maxx, f[u]);
			for (int j = 0; j < a[u].size(); j++){
				int i = a[u][j];
				f[i] = max(f[i], f[u] + 1);
				d[i]--;
				if (!d[i]) q.push(i);
			}
		}
		cout << maxx + 3 << endl;
		v.clear();
		while (q.size()) q.pop();
		for (int i = 1; i <= n; i++) a[i].clear(), d[i] = 0, st[i] = 0, f[i] = 0;
	}
	return 0;
}
```

---

## 作者：FishPressedCoins (赞：1)

经典的拓扑排序。

将蜘蛛看作结点，给予玩具看作有向边。记录每个结点的入度，将入度为零的结点入队，并除去影响，将影响后入度为零的结点继续入队，直到队列为空。记录一共清空了多少次队列，就是答案。
```cpp
#include<iostream>
#include<vector>
#include<queue>
using namespace std;
int T, N, arr[200010];//数组记录结点的入度数量
vector<int>P[200010];//邻接表
int main()
{
	cin >> T;
	while (T--) {
		cin >> N;
		for (int i = 1,j; i <= N; i++) {
			cin >> j;
			arr[j]++, P[i].push_back(j);
		}
		queue<int>Q;
		int ans = 2, temp, sum;//第一年不可能，所以从二开始
		for (int i = 1; i <= N; i++) {
			if (arr[i] == 0) {
				Q.push(i);//找出所有入度为零的结点，入队
			}
		}
		while (!Q.empty()) {
			ans++, sum = Q.size();//记录上次队列长度
			for (int i = 0; i < sum; i++) {//清空上次队列
				temp = Q.front();
				Q.pop();
				for (auto t : P[temp]) {
					arr[t]--;//除去影响
					if (arr[t] == 0) {
						Q.push(t);//如果出现入度为零的结点，入队
					}
				}
			}
		}
		cout << ans << '\n';
		for (int i = 1; i <= N; i++) {
			P[i].clear(); arr[i] = 0;//为下一次数据初始化
		}
	}
	return 0;
}
```

---

## 作者：ohjun (赞：1)

## 思路分析
发现如果一个蜘蛛没有玩具，则它给的那只蜘蛛的玩具数量就会减 $1$。而不被任何 $r$ 指向的蜘蛛在第一轮过后就会没有玩具。可以用一个类似拓扑排序解决。首先在输入时用 $cnt_i$ 记录蜘蛛 $i$ 被多少个 $r$ 指向，接下来将 $cnt = 0$ 的蜘蛛设置轮数（初始轮数为 $2$）并压入队列，然后每次循环将弹出的蜘蛛对应的 $r$ 指向的蜘蛛的 $cnt$ 减 $1$。如果在这次操作使那只蜘蛛的 $cnt$ 降为 $0$，则将这只蜘蛛压入队列。循环结束后最后一只蜘蛛对应的轮数加 $1$ 就是答案。
## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define mkp make_pair
typedef pair<int, int> pii;
const int maxn = 2e5 + 5;
int t, n;
int r[maxn], cnt[maxn];
queue<pii> q;

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> t;
	while(t--)
	{
		cin >> n;
		memset(cnt, 0, sizeof(int) * (n + 1));
		for(int i = 1; i <= n; i++)
		{
			cin >> r[i];
			cnt[r[i]]++;
		}
		for(int i = 1; i <= n; i++)
			if(!cnt[i])
				q.push(mkp(i, 2));
		pii now = mkp(114514, 1);
		while(!q.empty())
		{
			now = q.front();
			q.pop();
			int u = now.first;
			cnt[r[u]]--;
			if(!cnt[r[u]])
				q.push(mkp(r[u], now.second + 1));
		}
		cout << now.second + 1 << '\n';
	}
	return 0;
}
```

---

## 作者：wflhx2011 (赞：0)

这篇题解将同时说明两个版本的解法。

要让一次变化后状态与上一次一样，也就是形成一个环，且只有环内的点有玩具。

因为是第 $i$ 人给第 $r_i$ 人，考虑从 $i$ 向 $r_i$ 连边建图，之后用拓扑排序或搜索找环。

找完环后，需要找出除环上的点都没有玩具的经过时间，这也是两个题的不同之处：

- 对于简单版本，因为每个点最多一个玩具，考虑 dp 求出，设 $v$ 表示连向了 $u$ 的点，状态转移应为 $dp_u=\max\{dp_v\}+1$，也就是环外的最长链。

- 对于困难版本，每个点可以有多个玩具，每次仍只能传递一个，仍用 dp，但每个点的值应是连向它的点的值的和，即 $dp_u=\sum dp_v+1$。

这个 dp 在拓扑排序时顺便就可以处理。

G1 代码：


```cpp
#include<bits/stdc++.h>
using namespace std;
vector<int> g[200005];
int in[200005],f[200005],n,ans;
queue<int> q;
void topo()
{
	ans=0;
	for(int i=1;i<=n;i++)
		if(!in[i])
			q.push(i);
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		for(int i=0;i<g[u].size();i++)
		{
			int v=g[u][i];
			in[v]--;
			ans=max(ans,++f[u]);
			f[v]=max(f[u],f[v]);
			if(!in[v])
				q.push(v); 
		}
	}
	cout<<ans+2<<"\n";
	return ; 
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin>>t;
	while(t--)
	{
		while(!q.empty())
			q.pop();
		cin>>n;
		for(int i=1;i<=n;i++)
			in[i]=0,f[i]=0,g[i].clear();
		for(int i=1;i<=n;i++)
		{
			int x;
			cin>>x;
			g[i].push_back(x);
			in[x]++;
		}
		topo();
	}
 	return 0;
}
```

G2 代码：


```cpp
#include<bits/stdc++.h>
using namespace std;
vector<int> g[200005];
int in[200005],f[200005],n,ans;
queue<int> q;
void topo()
{
	ans=0;
	for(int i=1;i<=n;i++)
		if(!in[i])
			q.push(i);
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		for(int i=0;i<g[u].size();i++)
		{
			int v=g[u][i];
			in[v]--;
			ans=max(ans,++f[u]);
			f[v]+=f[u];  
			if(!in[v])
				q.push(v); 
		}
	}
	cout<<ans+2<<"\n";
	return ; 
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin>>t;
	while(t--)
	{
		while(!q.empty())
			q.pop();
		cin>>n;
		for(int i=1;i<=n;i++)
			in[i]=0,f[i]=0,g[i].clear();
		for(int i=1;i<=n;i++)
		{
			int x;
			cin>>x;
			g[i].push_back(x);
			in[x]++;
		}
		topo();
	}
 	return 0;
}
```

---

## 作者：Anby_ (赞：0)

**本片题解将同时阐述 Easy version 与 hard version 的区别。**
### 思路
考虑拓扑。  
容易发现本题的图为**基环森林**，对于两题而言，**若图中只剩下了环，再如何传递，都不会发生变化了。** 
显然，两题只剩环的时间是不同的。  
以下，将环视为树根而言。  

对于第一题，由于每一个节点只会保留一个信息，那么，每个节点最后一个收到的信息一定是**最长链给到的信息**，那么，问题就转换成的找环上最长链。  

对于第二题，收到的信息是不限的，那么，他将收到**来自每一颗子树的大小的信息**。又由于他每次只会传递一个信息，那么他将信息传递完的时间是**各子树大小加它本身**。

如果使用数学语言会更为直观。  
对于第一题，一个结点的贡献为：
$$
dp_u=max(dp_v)+1
$$
对于第二题，一个结点的贡献为：
$$
dp_u=\sum{dp_v}+1
$$
其中，$v$ 为能够一步到达 $u$ 的节点。  
仅仅是一个符号的区别。  
如果一个点的答案更新完了，那么他也就可以更新其他节点。显而易见，本题应使用拓扑。
### AC code
**[CF2044G1](https://www.luogu.com.cn/problem/CF2044G1)：**
```cpp
#include<bits/stdc++.h>
#define int long long
#define x first
#define y second
using namespace std;
const int N=2e5+10,inf=0x3f3f3f3f,mod=1e9+7;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef long long ll;
/*

*/
int t,n,r[N],d[N],cnt[N],inq[N],ans;
void Solve(){
	cin>>n; ans=0;
	for(int i=1;i<=n;i++) inq[i]=0,d[i]=0,cnt[i]=0;
	for(int i=1;i<=n;i++) cin>>r[i],inq[r[i]]++;
	queue<int> q;
	for(int i=1;i<=n;i++) if(!inq[i]) q.push(i);
	while(!q.empty()){
		int u=q.front(),v=r[u]; q.pop();
		ans=max(ans,++d[u]);
		inq[v]--; d[v]=d[u];
		if(!inq[v]) q.push(v);
	}
	cout<<ans+2<<"\n";
}
signed main(){
	cin>>t;
	while(t--) Solve();
	return 0;
}
```
**[CF2044G2](https://www.luogu.com.cn/problem/CF2044G2)：**
```cpp
#include<bits/stdc++.h>
#define int long long
#define x first
#define y second
using namespace std;
const int N=2e5+10,inf=0x3f3f3f3f,mod=1e9+7;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef long long ll;
/*

*/
int t,n,r[N],d[N],cnt[N],inq[N],ans;
void Solve(){
	cin>>n; ans=0;
	for(int i=1;i<=n;i++) inq[i]=0,d[i]=0,cnt[i]=0;
	for(int i=1;i<=n;i++) cin>>r[i],inq[r[i]]++;
	queue<int> q;
	for(int i=1;i<=n;i++) if(!inq[i]) q.push(i);
	while(!q.empty()){
		int u=q.front(),v=r[u]; q.pop();
		ans=max(ans,++d[u]);
		inq[v]--; d[v]+=d[u];
		if(!inq[v]) q.push(v);
	}
	cout<<ans+2<<"\n";
}
signed main(){
	cin>>t;
	while(t--) Solve();
	return 0;
}
```

---

