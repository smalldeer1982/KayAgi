# Lost Tree

## 题目描述

This is an interactive problem.

Little Dormi was faced with an awkward problem at the carnival: he has to guess the edges of an unweighted tree of $ n $ nodes! The nodes of the tree are numbered from $ 1 $ to $ n $ .

The game master only allows him to ask one type of question:

- Little Dormi picks a node $ r $ ( $ 1 \le r \le n $ ), and the game master will reply with an array $ d_1, d_2, \ldots, d_n $ , where $ d_i $ is the length of the shortest path from node $ r $ to $ i $ , for all $ 1 \le i \le n $ .

Additionally, to make the game unfair challenge Little Dormi the game master will allow at most $ \lceil\frac{n}{2}\rceil $ questions, where $ \lceil x \rceil $ denotes the smallest integer greater than or equal to $ x $ .

Faced with the stomach-churning possibility of not being able to guess the tree, Little Dormi needs your help to devise a winning strategy!

Note that the game master creates the tree before the game starts, and does not change it during the game.

## 说明/提示

Here is the tree from the first example.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1534D/db5986557f00451a4bfc4f6b9560af77b9bcbfc0.png)Notice that the edges can be output in any order.

Additionally, here are the answers for querying every single node in example $ 1 $ :

- $ 1 $ : $ [0,1,2,2] $
- $ 2 $ : $ [1,0,1,1] $
- $ 3 $ : $ [2,1,0,2] $
- $ 4 $ : $ [2,1,2,0] $

Below is the tree from the second example interaction.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1534D/391f4de27a316d6b5f59760a326b58ab613c06c0.png)Lastly, here are the answers for querying every single node in example $ 2 $ :

- $ 1 $ : $ [0,4,1,3,2] $
- $ 2 $ : $ [4,0,3,1,2] $
- $ 3 $ : $ [1,3,0,2,1] $
- $ 4 $ : $ [3,1,2,0,1] $
- $ 5 $ : $ [2,2,1,1,0] $

## 样例 #1

### 输入

```
4

0 1 2 2

1 0 1 1```

### 输出

```
? 1

? 2

!
4 2
1 2
2 3```

## 样例 #2

### 输入

```
5

2 2 1 1 0```

### 输出

```
? 5

!
4 5
3 5
2 4
1 3```

# 题解

## 作者：kradcigam (赞：13)

比赛当时降智了，没有想出来。

我们询问一个点，与它距离为 $1$ 的所有点都跟它有边。

所以，我们想知道树的所有边只需查询所有深度为奇数的点，或所有深度为偶数的点就可以了。

这样我们就可以先查询任意一个节点，把它拉出来作根，然后再比较深度为奇数的点的个数和深度为偶数的点的个数（注意不要把根节点算进去），然后取小的那个去查询就好了。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2010;
int h[2];
vector<int> v[2], ans[N];
int main() {
	int n;
	cin >> n;
	cout << "? " << 1 << endl;
	fflush (stdout);
	for (int i = 1;  i <= n; i++) {
		int dep;
		cin >> dep;
		if (dep == 1) ans[1].push_back(i);
		if (dep != 0) {
			h[dep&1]++;
			v[dep&1].push_back(i);
		}
	}
	int k=0;
	if (h[0] > h[1]) k = 1;
	for (int i : v[k]) {
		cout << "? " << i << endl;
		fflush (stdout);
		for (int j = 1; j <= n; j++) {
			int dep;
			cin >> dep;
			if (dep == 1)ans[i].push_back(j);
		}
	}
	cout << "!" << endl;
	for (int i = 1; i <= n; i++)
		for (int j : ans[i])
			if (j != 1)
				cout<<i<<" "<<j<<endl;
	return 0;
}
```

---

## 作者：Eibon (赞：5)

题目限制询问不得超过 $ \lceil \frac{n}{2} \rceil $ 次，很容易让人联想到奇数与偶数。

显然，深度为偶数(或者奇数)的点一定能遍历到深度为奇数(或者偶数)的点。

考虑直接令 $1$ 点为根，得到各个点的深度，选择深度奇数或者偶数个数较小的进行询问。

如果是偶数，应当将 $1$ 点相连的点加上，因为 $1$ 点深度为偶数。

判断时应将 $1$ 点视为深度为偶数的点。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=2000+5;
const int mod=1e9+7;
int n,tot,ans=1,num;
int head[maxn],dis,sum[maxn];
struct edge
{
	int to,nxt;
};
edge e[maxn<<1];
void add(int u,int v)
{
	e[++tot]={v,head[u]};
	head[u]=tot;
}
void dfs(int u,int fa)
{
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v==fa){
			continue;
		}
		cout<<u<<" "<<v<<endl;
		dfs(v,u);
	}
}
void VIP(int u)
{
	cout<<"? "<<u<<endl;
	for(int v=1;v<=n;v++){
		cin>>dis;
		if(dis==1){
			add(u,v);
			add(v,u);
		}
	}
}
signed main()
{
	cin>>n;
	cout<<"? "<<1<<endl;
	for(int v=1;v<=n;v++){
		cin>>sum[v];
		if(sum[v]&1){
			num++;
		}
	}
	if(num*2<n){
		for(int i=1;i<=n;i++){
			if(sum[i]&1){
				VIP(i);
			}
		}
	}
	else{
		for(int i=1;i<=n;i++){
			if(sum[i]==1){
				add(1,i);
			}
		}
		for(int i=2;i<=n;i++){
			if(!(sum[i]&1)){
				VIP(i);
			}
		}
	}
	cout<<"!"<<endl;
	dfs(1,0);
	return 0;
}
//dyyyyds
```

---

## 作者：scp020 (赞：3)

### 题面大意

**警告：本题要及时清空缓存区。**

你知道一棵树有 $n$ 个节点，且你可以询问最多 $\lceil \dfrac{n}{2} \rceil$ 次，格式为 `? x`，每次询问评测机给出 $n$ 个整数，第 $i$ 个数代表 $i$ 节点与 $x$ 节点之间的简单路径长度。

所有询问结束后，要求输出一个 `!`，下面 $n-1$ 行，每行 $2$ 个正整数 `u v`，表示 $u$ 节点和 $v$ 节点间有边。

### 解决

注意到我们不知道树根，所以我们可以把 $1$ 节点当作树根，我们先对树根进行询问，得到 $n$ 个数，第 $i$ 个数即表示 $i$ 节点的深度，这里树根的深度认为是 $0$。

题目中说到可以询问最多 $\lceil \dfrac{n}{2} \rceil$ 次，想到了对与节点的深度分成两类，分为奇数和偶数，如果奇数深度的节点少我们就全部询问奇数深度的节点，反之同理。对于相邻的两个节点，他们的简单路径长度一定为 $1$。

例如样例 $1$，第一次询问询问树根 $1$，给出了各个节点的深度。作图来自 [Graph Editor](https://csacademy.com/app/graph_editor/)。

![](https://cdn.luogu.com.cn/upload/image_hosting/ot6f597u.png)

发现奇数深度的节点有 $1$ 个，偶数深度的节点有 $2$ 个（不包含树根，因为没有查询的必要），所以我们选择奇数深度的节点询问。询问 $2$ 节点，给出四个数 `1 0 1 1`，即表示 $1$ 节点、$3$ 节点、$4$ 节点与 $2$ 节点有连边，最后把这三个边输出即可。

### 正确性证明

这样做的正确性很容易证明，因为奇数深度的节点一定只会与偶数深度的节点相邻而不会与奇数深度的节点相邻，偶数深度的节点一定只会与奇数深度的节点相邻而不会与偶数深度的节点相邻。

给个例子。作图来自画图。

![](https://cdn.luogu.com.cn/upload/image_hosting/nl28g37e.png)

我们选择奇数深度的节点询问，对于每次询问，我们都会得到该节点与上下两层偶数深度的节点之间的连边，这里我们把边进行分层。如下图。

![](https://cdn.luogu.com.cn/upload/image_hosting/w46pdm84.png)

对于每一层深度为奇数的节点，询问后加的边即为两层连续的奇数深度的边和偶数深度的边。这样在询问完所有深度为奇数的节点后我们就可以加到所有的边了。选择奇数深度的节点询问同理。

### 代码

``` c++
#include<bits/stdc++.h>
using namespace std;
int n,dep[2010],cntodd,cnt;
inline void ask(const int &pos)
{
	printf("? %d\n",pos),fflush(stdout);
}
struct Edge
{
	int from,to;
};
Edge edge[2010];
inline void add(const int &x,const int &y)
{
	edge[++cnt].from=x,edge[cnt].to=y;
}
int main()
{
	scanf("%d",&n),ask(1);
	for(int i=1;i<=n;i++) scanf("%d",&dep[i]),cntodd+=(dep[i]&1);//奇数深度统计一下
	if(cntodd*2<n)//奇数深度数量少，不大于一半
	{
		for(int i=2,dis;i<=n;i++)
			if(dep[i]&1)
			{
				ask(i);
				for(int j=1;j<=n;j++)
				{
					scanf("%d",&dis);
					if(dis==1) add(i,j);
				}
			}
	}else//相反，偶数深度数量少
	{
		for(int i=1;i<=n;i++) if(dep[i]==1) add(1,i);//因为问偶数深度，而树根 1 的儿子都是深度为 1，是奇数，所以先连一波边
		for(int i=2,dis;i<=n;i++)//和上面几乎一样
			if(!(dep[i]&1))
			{
				ask(i);
				for(int j=1;j<=n;j++)
				{
					scanf("%d",&dis);
					if(dis==1) add(i,j);
				}
			}
	}
	putchar('!'),putchar('\n');
	for(int i=1;i<n;i++) printf("%d %d\n",edge[i].from,edge[i].to);
	return 0;
}
```


---

## 作者：_lyx111 (赞：2)

# CF1534D Lost Tree

[题目传送门](https://codeforces.com/problemset/problem/1534/D)

## 分析

**交互题**。

钦定根为 $1$，那么先询问 `? 1` 得到 $n$ 个整数 $dep_1,\cdots,dep_n$，按照深度的奇偶性对节点进行黑白染色（偶数为黑色，奇数为白色）。

设黑色点的个数为 $t$，偶数点的个数为 $s$。因为 $s+t=n$，所以 $\min\{s,t\}\le\lfloor\dfrac{n}{2}\rfloor$。

- 若 $s<\lceil\dfrac{n}{2}\rceil$，那么直接询问所有白色点，然后将距离为 $1$ 的黑白色点对记录下来，输出即可；

- 若 $s\ge\lceil\dfrac{n}{2}\rceil$，则 $t\le\lceil\dfrac{n}{2}\rceil$，那么先将和结点 $1$ 距离为 $1$ 的白点记录下来，然后询问除了 $1$ 的所有黑色点，并将距离为 $1$ 的黑白色点对记录下来，输出即可。

注意在每次输出之后，都要再加一句 `fflush(stdout);`。


### [代码](https://codeforces.com/contest/1534/submission/192251671)

## 写在最后

蒟蒻很菜，如果写的有不清楚或不对的地方望读者私信我指出，我会及时修正。

---

## 作者：听取MLE声一片 (赞：2)

简单题。

容易想到我们询问每一个点，如果 $dis_{ij}=1$ 那么就在 $i$ 和 $j$ 连一条边。可惜这样询问是线性的，过不去。

显然这样会把每条边建两次，所以我们只需要去掉一半的情况就能达到 $n$ 的一半的目标。

我们假定 1 为根，只需要询问 1，得到的数组就是各个结点的深度。不难发现深度奇偶性相同的点之间不可能有边相连。所以我们只需要分别统计深度为奇数和偶数的个数，然后把个数少的都问一遍即可。

---

## 作者：Cutest_Junior (赞：1)

## 题解 CF1534D 【Lost Tree】

### 题意

+ $n$ 个点的树；
+ 每次可以查询点 $x$ 与其他所有点的距离；
+ 最多查询 $\lceil\dfrac{n}{2}\rceil$ 次；
+ 求树的结构；
+ $n\le2000$。

### 做法

很多题解都是奇偶性分类，这里是贪心。

求的是树的结构，其实只有求出每个点的父亲节点即可。

考虑先选一个根，我习惯选 $1$，查询一次求所有点的深度。

深度为 $1$ 的点父亲肯定是 $1$。

按深度从小到大排序。

对于每个点，如果该点的父亲还未求出，查询一次，所有与它距离为 $1$ 的点，不是父亲就是儿子，根据深度判断。

复杂度还是不对，hack 数据：

```
1 2
2 3
2 4
2 5
2 5
2 6
2 7
...
```

如果有一个点有很多儿子，且这个点没被查过，那么就会被卡爆。

发现一个特性，距离为 $2$ 且深度相同的两个点肯定有相同的父亲，有相同的父亲的两个点肯定深度相同且距离为 $2$。

那每次查询就可以找到该点所有儿子的父亲和所有兄弟的父亲，可过。

为什么正确呢？

因为按深度排序，如果一个点被遍历到且未被查过，那么他的父亲肯定没被查过，最坏的情况是没有兄弟，那么一对父子最多也只查一次。

### 代码

```cpp
#include <cstdio>
#include <vector>

using namespace std;
//
typedef long long ll;

const int inf = (1 << 30) - 1;
const ll linf = (1ll << 60) - 1;

const int N = 2005;

vector<int> v[N];

int dep[N];
int a[N];

int father[N];

int n;

void dfs(int x) {
	if (father[x]) {
		return;
	}
	printf("? %d\n", x);
	fflush(stdout);
	int a[N];
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
	}
	for (int i = 1; i <= n; ++i) {
		if (a[i] == 1) {
			if (dep[i] < dep[x]) {
				father[x] = i;
			}
			else {
				father[i] = x;
			}
		}
	}
	for (int i = 1; i <= n; ++i) {
		if (a[i] == 2 && dep[i] == dep[x]) {
			father[i] = father[x];
		}
	}
//	for (int i = 1; i <= n; ++i) {
//		if (a[i] == 2 && dep[i] == dep[x] + 2) {
//			if (!father[i]) {
//				dfs(i);
//			}
//		}
//	}
}

void solve() {
	scanf("%d", &n);
	printf("? 1\n");
	fflush(stdout);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &dep[i]);
	}
	for (int i = 1; i <= n; ++i) {
		if (dep[i] == 1) {
			father[i] = 1;
		}
	}
	for (int i = 1; i <= n; ++i) {
		v[dep[i]].push_back(i);
	}
	for (int i = 1; !v[i].empty(); ++i) {
		for (int j = 0; j < (int)v[i].size(); ++j) {
			int t = v[i][j];
			if (!father[t]) {
				dfs(t);
			}
		}
	}
//	for (int i = 1; i <= n; ++i) {//
//		if (dep[i] == 2) {
//			dfs(i);
//		}
//	}
	printf("!\n");
	for (int i = 2; i <= n; ++i) {
		printf("%d %d\n", i, father[i]);
	}
	fflush(stdout);
}

int main() {
//	int t;
//	scanf("%d", &t);
//	while (t--) {
		solve();
//	}
}
```

---

## 作者：cirnovsky (赞：1)

首先肯定要钦定一个根，对其进行一次询问。

然后查询出来的相当于是深度。观察次数限制 $\lceil\frac{n}{2}\rceil$，大概是一半的节点。

考虑如何规划一半的节点去询问。一次询问能确定的边就是查询出来距离为 $1$ 的。

~~注意到相邻奇数偶数之间总是相差 $1$。~~

然后把节点进行关于深度的奇偶分层，查询 奇 / 偶 中数量较少的节点即可。

```cpp
#include <bits/stdc++.h>
using ll = long long;
#define all(x) (x).begin(), (x).end()
int main() {
//	std::ios_base::sync_with_stdio(false);
//	std::cin.tie(nullptr);
//	std::cout.tie(nullptr);
	int n;
	std::cin >> n;
	auto ask = [&] (int x) {
		std::cout << "? " << x + 1 << "\n";
		std::vector<int> res(n);
		for (int &x : res) std::cin >> x;
		return res;
	};
	std::vector<int> d = ask(0);
	std::vector<std::pair<int, int>> ans;
	std::vector<std::vector<int>> cat(2);
	for (int i = 0; i < n; ++i) {
		if (d[i] == 1) ans.emplace_back(std::make_pair(0, i));
	}
	for (int i = 1; i < n; ++i) {
		if (d[i] & 1) cat[1].emplace_back(i);
		else cat[0].emplace_back(i);
	}
	std::vector<int> point;
	if (cat[0].size() > cat[1].size()) point = cat[1];
	else point = cat[0];
	for (int x : point) {
		d = ask(x);
		for (int i = 0; i < n; ++i) {
			if (d[i] == 1) ans.emplace_back(std::make_pair(x, i));
		}
	}
	for (auto &x : ans) {
		if (x.first > x.second) std::swap(x.first, x.second);
	}
	std::sort(all(ans));
	ans.erase(std::unique(all(ans)), ans.end());
	std::cout << "!\n";
	for (auto x : ans) std::cout << x.first + 1 << " " << x.second + 1 << "\n";
	return 0;
}
```

---

## 作者：Glori (赞：1)

这一道题又双叒叕是考场 WA Pretest 赛后秒调出来的 ...

---

首先这是一道交互题。  
然后看到条件，发现每一次询问 $id$，交互器会给出它与每一个点的距离。

那么最后要求树的形态。

那么既然是树，则有下面几个性质

- 与其距离为 $1$ 的必定与它连了一条边 $→(1)$
- 有 $n-1$ 条边（点的数目是 $n$） $→(2)$

那么由 $(2)$ 可知，显然我们可以通过一定次数的操作，然后开一个 FLAG 来标记当前边是否被找到过，然后弄一个 VECTOR `v` 装答案，那么最后 `v.size()=n-1` 的时候就停止。

由 $(1)$ 呢？是否可以推广一下结论呢？

显然是可以的。

- 与某个点距离为 $n$ 的必定与某个距离为 $n+1$ 的点相连

那么随便推一下就可以知道这个是对的。

这个时候我们看到 $\lceil\frac{n}{2}\rceil$ 这个条件可以想到什么呢？

由小学数学知道 $n$ 与 $n+1$ 必定奇偶性不同。

那么就有了一个 idea，即奇偶性分组，又因为只能用一半的询问，所以就贪心，选择 size 更小的那一个奇偶性的组，记得特判一下已经处理过的 $1$ 不要再询问一遍就可以了，因为如果再询问一遍，那么碰到两组 siz 相同，而你又去询问了一遍 $1$，这样就会被判定为 WA。

正确性的话，因为关于某个点的距离 $n$ 必定可以连到 $n-1$ 和 $n+1$，当然前提是有这个点的存在。那么由于这个边是双向的，那么可以只通过某一种奇偶的 $n$ 来获取所有 $n+1$ 或者 $n-1$ 的信息，这个才是最妙的。

代码非常简单易懂。

```cpp
#include <bits/stdc++.h>
using namespace std;

int n,id;queue<pair<int,int> >tr;
vector <int> dis[2010];
#define pb push_back
bool has[2010][2010];
bool asked[2010];
vector<int>g[2];
bool G[2010][2];

void ask(int id){cout<<"? "<<id<<endl;}
void search(int to) {
    if(tr.size()==n-1)return;
    ask(to); vector<int>cur;
    cur.clear();cur.pb(0);
    for(int i=1;i<=n;++i){
        int res;cin>>res;cur.pb(res);
    }vector<int>a;a.clear();a.pb(0);
    for(int i=1;i<=n;++i){
        if(cur[i]==1)a.pb(i); // 连边距离 1 存储
    }for(int i=1;i<a.size();++i){
        if(has[to][a[i]]||has[a[i]][to])continue;
        has[to][a[i]]=has[a[i]][to]=true;
        // 如果没有标记过就直接丢进答案
        tr.push(make_pair(to,a[i]));
        asked[a[i]]=true; // 标记
    }// deal with dist 1
    return;
}

int main() {
    cin>>n;
    if(n==2){cout<<'!'<<endl<<1<<' '<<2<<endl;return 0;}
    // 特判，不太确定要不要加（
    vector<int>one;one.clear();
    ask(1); for(int i=1;i<=n;++i){
        int cur;cin>>cur;
        if(cur%2==0)g[0].pb(i);
        else g[1].pb(i);
        // 分别存储奇偶性
        if(cur==1)one.pb(i);
    }if(g[0].size()>g[1].size())id=1;else id=0;
    if(g[id][0]^1)search(g[id][0]);
    else for(int i=0;i<one.size();++i)tr.push(make_pair(1,one[i]));
    for(int i=1;i<g[id].size();++i)search(g[id][i]);
    // 奇偶性分组然后暴力查询
    puts("!");
    while(!tr.empty()){
        pair<int,int>cur=tr.front();tr.pop();
        cout<<cur.first<<' '<<cur.second<<endl;
    }return 0;
}
```

---

## 作者：船酱魔王 (赞：0)

# Lost Tree 题解

## 题意回顾

你知道存在一棵 $ n $ 个点的无根无权树，但未知树的结构。你可以问评测器**最多 $ \lceil \frac{n}{2} \rceil $ 次**问题，查询一个点到所有点的距离。请还原树的形态。

$ 2 \le n \le 2000 $。

## 分析

看到 $ \lceil \frac{n}{2} \rceil $ 这个限制，想到树是二分图这个性质，我们可以把树的结点黑白染色，则必然一种颜色点数不超过询问限制，问这种颜色即可使得所有点要么被询问，要么和被询问的点距离不超过 $ 1 $，则根据哪些点离被询问的点距离为 $ 1 $ 就可以找到所有边。

但是我们不知道树的形态，不过我们可以发现一个性质：对于一棵有根树的黑白染色方案，一种颜色全在奇数深度，另一种全在偶数深度。故我们先定 $ 1 $ 为根，查询到所有点距离（即深度值），则我们由深度的奇偶性确定了黑白染色的情况。

显然 $ 1 $ 无需重复询问。

则询问次数极限为 $ 1+\lfloor \frac{n-1}{2} \rfloor=\lfloor \frac{n+1}{2} \rfloor=\lceil \frac{n}{2} \rceil $，证明可以讨论 $ n $ 的奇偶性。

注意不要重复询问点 $ 1 $。

## AC 代码

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
const int N = 2005;
int n;
int depth[N];
int rem[2];
int el = 0;
int u[N], v[N];
int main() {
	scanf("%d", &n);
	cout << "? 1" << endl;
	for(int i = 1; i <= n; i++) scanf("%d", &depth[i]);
	for(int i = 2; i <= n; i++) rem[depth[i] % 2]++;
	int rm = (rem[0] < rem[1]) ? 0 : 1;
	int x;
	if(rm == 0) {
		for(int i = 1; i <= n; i++) {
			if(depth[i] == 1) u[++el] = 1, v[el] = i;
		}
	}
	for(int i = 1; i <= n; i++) {
		if(i > 1 && depth[i] % 2 == rm) {
			cout << "? " << i << endl;
			for(int j = 1; j <= n; j++) {
				scanf("%d", &x);
				if(x == 1) u[++el] = i, v[el] = j;
			}
		}
	}
	printf("!\n");
	for(int i = 1; i < n; i++) printf("%d %d\n", u[i], v[i]);
	cout << endl;
	return 0;
}
```

---

## 作者：5k_sync_closer (赞：0)

钦定 $1$ 为树根，询问 $1$ 得到每个点的深度。

令 $A=\{x|\text{dep}_x\equiv1\pmod2\},B=\{x|\text{dep}_x\equiv0\pmod2\}$。

显然 $\min(|A|,|B|)\le\lfloor\dfrac n2\rfloor$。

询问 $x$ 可以得到 $x$ 的邻边集 $S_x$。

容易发现，$\bigcup\limits_{x\in A}S_x=\bigcup\limits_{x\in B}S_x=E$。

询问 $A,B$ 中较小者的所有元素即可。

```cpp
#include <cstdio>
int n, m, c[2], d[2050], u[2050], v[2050];
int main()
{
    scanf("%d", &n);
    puts("? 1");
    fflush(stdout);
    for (int i = 1; i <= n; ++i)
        scanf("%d", d + i), ++c[d[i] & 1];
    if (c[1] < c[0])
    {
        for (int i = 1; i <= n; ++i)
            if (d[i] & 1)
            {
                printf("? %d\n", i);
                fflush(stdout);
                for (int j = 1, x; j <= n; ++j)
                {
                    scanf("%d", &x);
                    if (x == 1)
                        u[m] = i, v[m++] = j;
                }
            }
    }
    else
    {
        for (int i = 1; i <= n; ++i)
            if (d[i] == 1)
                u[m] = 1, v[m++] = i;
        for (int i = 2; i <= n; ++i)
            if (!(d[i] & 1))
            {
                printf("? %d\n", i);
                fflush(stdout);
                for (int j = 1, x; j <= n; ++j)
                {
                    scanf("%d", &x);
                    if (x == 1)
                        u[m] = i, v[m++] = j;
                }
            }
    }
    puts("!");
    for (int i = 0; i < m; ++i)
        printf("%d %d\n", u[i], v[i]);
    fflush(stdout);
    return 0;
}
```


---

## 作者：出言不逊王子 (赞：0)

我们发现这棵树没有根，于是我们假设它的根是 $1$。于是每个点有了一个父亲。

我们先查询一下 $1$，发现他给出了每个节点的深度。

然后我们发现，和 $1$ 距离为 $1$ 的节点都是 $1$ 的儿子了。

然后我们发现 $1$ 儿子的儿子还不知道自己的父亲是谁，所以我们查询这些和 $1$ 距离为 $2$ 的节点。

于是我们发现：

- 和这些到 $1$ 的距离为 $2$ 的节点的父亲到 $1$ 的距离都是 $1$，也就是 $2-1$。
- 和这些到 $1$ 距离为 $2$ 的节点的节点的儿子到 $1$ 的距离都是 $3$，也就是 $2+1$。

进一步地，我们可以发现：

- 和这些到 $1$ 的距离为 $k$ 的节点的父亲到 $1$ 的距离都是 $k-1$。
- 和这些到 $1$ 距离为 $k$ 的节点的节点的儿子到 $1$ 的距离都是 $k+1$。

然后我们发现，有了到 $1$ 距离为奇数节点的数据，我们就有了到 $1$ 距离为偶数节点的数据，反过来同理。

所以在查询 $1$ 以后，我们统计一下到 $1$ 距离为奇数和偶数的点的个数，选最小的一个个去查询即可。

代码：
```cpp
#include<bits/stdc++.h>
#define fs(i,x,y,z) for(int i=x;i<=y;i+=z)
#define ft(i,x,y,z) for(int i=x;i>=y;i+=z)
#define ll long long
#define ull unsigned long long
#define db double
#define ms(a,b) memset(a,b,sizeof(a))
#define sz(a) sizeof(a)
using namespace std;
const int rw[]={-1,0,1,0,-1,1,-1,1},cl[]={0,1,0,-1,-1,1,1,-1};
const int N=2001,inf=0x3f3f3f3f;
inline int read(){
	int date=0,w=1;char c=0;
	while(c<'0'||c>'9'){if(c=='-')w=-1;c=getchar();}
	while(c>='0'&&c<='9'){date=date*10+c-'0';c=getchar();}
	return date*w;
}
int chk,n,delta[N][N],dgr[2],fa[N],chklist[N],chktot;
void qry(int cur){
	cout<<"? "<<cur<<endl;
	fs(i,1,n,1) cin>>delta[cur][i];
}
bool cmp(int x,int y){return delta[1][x]<delta[1][y];}//近的先排前面 
int main(){
	cin>>n;
	qry(1);
	fs(i,2,n,1){
		dgr[delta[1][i]&1]++;
		if(delta[1][i]==1) fa[i]=1;//确定关系 
	}
//	if(!dgr[0]) chk=1;
//	else if(!dgr[1]) chk=0;
	if(dgr[0]>dgr[1]) chk=1;
	else chk=0;
	fs(i,2,n,1) if((delta[1][i]&1)==chk) chklist[++chktot]=i;//i是节点编号 
	sort(chklist+1,chklist+chktot+1,cmp);
	fs(i,1,chktot,1){
		int cur=chklist[i];//当前查询谁
		qry(cur);
		fs(j,1,n,1){
			if(delta[cur][j]==1){//j是符合条件的节点编号 
				if(delta[1][j]-delta[1][cur]==1) fa[j]=cur;
				else if(delta[1][cur]-delta[1][j]==1) fa[cur]=j;
				else return puts("fuck1"),1; 
			}
		} 
	}
	fs(i,2,n,1) if(!fa[i]) return puts("fuck"),1; 
	cout<<"!\n";
	fs(i,2,n,1) cout<<i<<' '<<fa[i]<<'\n';
	cout<<endl;
	return 0;
}
/*
以奇数为例
先按照深度排序
然后对于每个点看他dis=1的
如果dis0<curdis那么是dad否则是son
那像fa[5]这样的呢 
*/
```

---

## 作者：精神小火 (赞：0)

这题其实有另一种方法。考场上基本想出正解了，但是我是对每相邻两层取较小的，就挂了，不知道在想啥。

考虑先询问一次得到深度，把所有点按深度排序，挨个询问，每次可以确定这个点的父亲，以及**和他同父的兄弟**，简单分析一下，最差情况所有点没有兄弟，也是满足要求的。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define forg(i,x) for(register int i=fir[x];i;i=nxt[i])
#define uu unsigned
#define scanf a14=scanf
#define rint register int
#define fre(x) freopen(#x".in","r",stdin),freopen(#x".out","w",stdout)
typedef long long ll;
typedef uu long long ull;
typedef pair<int,int>pii;
int a14;
inline int rd(int l,int r){return rand()%(r-l+1)+l;}

const int mxn=2003;
int n,g[mxn][mxn],b[mxn],de[mxn],fa[mxn];
void aak(int x){printf("? %d\n",x);fflush(stdout);for(int i=1;i<=n;++i)scanf("%d",b+i);}
vector<int>dd[mxn];
int main(){
    scanf("%d",&n);
    aak(1);for(int i=1;i<=n;++i)de[i]=b[i],dd[b[i]].push_back(i);
    for(int i:dd[1])fa[i]=1;
    
    for(int d=2;d<=n;++d){
        for(int i:dd[d])if(!fa[i]){
            aak(i);
            for(int j=1;j<=n;++j)if(b[j]==1){if(de[j]==de[i]+1)fa[j]=i;else fa[i]=j;}
            for(int j=1;j<=n;++j)if(b[j]==2&&de[j]==de[i])fa[j]=fa[i];
        }
    }
    puts("!");
    for(int i=2;i<=n;++i)printf("%d %d\n",fa[i],i),assert(fa[i]);
    return 0;
}
```

---

## 作者：Acfboy (赞：0)

感觉我好像做复杂了？为什么我要用 dp?

首先我们询问 $1$ 就可以得到每个点在以 $1$ 为根的树上的深度。那么每一层就确定了。

显然我们不需要询问所有的层，任意两层中只要有一层被问过了，就一定可以推出剩下的。我们记录一下每一层的点个数，那么就把问题转换成 $n$ 个数相邻两个至少选一个，问最少的选出的数的和。  
这个答案肯定是不会超过 $\lceil\frac{n}{2}\rceil$ 的。

所以 dp 的时候记录一下方案，把方案中选中的层给询问一次就可以了。

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
const int N = 2005;
std::vector<int> v[N], an;
std::vector<std::pair<int, int> > ans;
int pre[N], f[N][2], buf[N], n, m;
bool vis[N][N];
void ask(int x) {
    std::cout << "? " << x << std::endl;
    for(int i = 1; i <= n; i++) std::cin >> buf[i];
}
int main() {
    std::cin >> n;
    ask(1);
    for(int i = 1; i <= n; i++) v[buf[i]].push_back(i), m = std::max(m, buf[i]);
    for(int i = 1; i <= n; i++) 
        if(buf[i] == 1) vis[1][i] = vis[i][1] = 1, ans.push_back(std::make_pair(i, 1));
    for(int i = 1; i <= m; i++) {
        if(f[i-1][0] < f[i-1][1]) pre[i] = 0, f[i][1] = f[i-1][0];
        else pre[i] = 1, f[i][1] = f[i-1][1];
        f[i][1] += v[i].size();
        f[i][0] = f[i-1][1];
    }
    int fin;
    if(f[m][0] < f[m][1]) fin = 0; else fin = 1;
    for(int i = m, j = fin; i >= 1; i--) {
        if(j == 1) an.push_back(i);
        if(j == 0) j = 1;
        else j = pre[i];
    }
    for(int i = 0; i < (signed)an.size(); i++) 
        for(int j = 0; j < (signed)v[an[i]].size(); j++) {
            ask(v[an[i]][j]);
            for(int k = 1; k <= n; k++)
                if(buf[k] == 1 && !vis[v[an[i]][j]][k]) 
                    vis[v[an[i]][j]][k] = vis[k][v[an[i]][j]] = 1, ans.push_back(std::make_pair(v[an[i]][j], k));
        }
    std::cout << "!" << std::endl;
    for(int i = 0; i < (signed)ans.size(); i++)
        std::cout << ans[i].first << " " << ans[i].second << std::endl;
}
```

---

