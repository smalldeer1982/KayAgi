# [ABC302E] Isolation

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc302/tasks/abc302_e

最初 $ N $ 頂点 $ 0 $ 辺の無向グラフがあり、各頂点には $ 1 $ から $ N $ まで番号がついています。  
 $ Q $ 個のクエリが与えられるので、順に処理し、各クエリの後における「他のどの頂点とも辺で結ばれていない頂点」の数を出力してください。

$ i $ 個目のクエリは $ \mathrm{query}_i $ であり、各クエリは次の $ 2 $ 種類いずれかです。

- `1 u v`: 頂点 $ u $ と頂点 $ v $ を辺で結ぶ。このクエリが与えられる直前の時点で、頂点 $ u $ と頂点 $ v $ は辺で結ばれていない事が保証される。
- `2 v` : 頂点 $ v $ と他の頂点を結ぶ辺をすべて削除する。（頂点 $ v $ 自体は削除しない。）

## 说明/提示

### 制約

- $ 2\ \leq\ N\leq\ 3\times\ 10^5 $
- $ 1\ \leq\ Q\leq\ 3\times\ 10^5 $
- $ 1 $ 番目の種類のクエリにおいて、$ 1\leq\ u,v\leq\ N $, $ u\neq\ v $
- $ 2 $ 番目の種類のクエリにおいて、$ 1\leq\ v\leq\ N $
- $ 1 $ 番目の種類のクエリの直前の時点で、そのクエリの $ u,v $ について頂点 $ u $ と頂点 $ v $ は辺で結ばれていない。
- 入力はすべて整数
 
### Sample Explanation 1

$ 1 $ 個目のクエリの後で、頂点 $ 1 $ と頂点 $ 2 $ は互いに結ばれており、頂点 $ 3 $ のみが他のどの頂点とも辺で結ばれていません。 よって、$ 1 $ 行目には $ 1 $ を出力します。 また、$ 3 $ 個目のクエリの後でどの相異なる $ 2 $ 頂点の間も辺で結ばれていますが、$ 4 $ 個目のクエリによって、 頂点 $ 1 $ と他の頂点を結ぶ辺、すなわち 頂点 $ 1 $ と頂点 $ 2 $ を結ぶ辺および頂点 $ 1 $ と頂点 $ 3 $ を結ぶ辺が削除されます。 この結果として、頂点 $ 2 $ と頂点 $ 3 $ は互いに結ばれているが、頂点 $ 1 $ は他のどの頂点とも辺で結ばれていない状態となります。 よって、$ 3 $ 行目には $ 0 $ を、$ 4 $ 行目には $ 1 $ を出力します。

### Sample Explanation 2

$ 2 $ 番目の種類のクエリを行う直前の時点で、すでにその頂点と他の頂点を結ぶ辺が $ 1 $ 本も存在しないこともあります。

## 样例 #1

### 输入

```
3 7
1 1 2
1 1 3
1 2 3
2 1
1 1 2
2 2
1 1 2```

### 输出

```
1
0
0
1
0
3
1```

## 样例 #2

### 输入

```
2 1
2 1```

### 输出

```
2```

# 题解

## 作者：Sunny郭 (赞：7)

看见题解区里面全部是用 set 的，复杂度带 log 的。

我们看完题目后发现，一条边删了之后就没有贡献（用处）了，那就是说每条边可以直接删去，而且只会被删去一次，那么我们其实不用马上删掉。

具体做法：把一条双向边拆成两个有向边（常规操作）。在删一个点的边时，把这个点连出去的有向边删了，并把两个原本相邻的点按照题意处理一下。另外那个原本相邻点连过来的边，在删那个点时再删掉就好了，不需要实时维护。

代码小技巧：
```cpp
通过异或 (xor) 的计算规则，我们可以知道：
(2*n) xor 1 = 2*n+1， (2*n+1) xor 1 = 2*n
例如：
3 xor 1 = 2， 2 xor 1 = 3
因为通常把双向边存储为两个方向互逆的单项边，
我们利用这些可以通过"^1"互相推出的成对数字来存储边的下标，
就很容易可以通过一条边的编号知道其反向边的编号了。
```

本题我使用链式前向星存储边。

如果是纯跳（即没有清空链头）的的话，会发现会有超时。

原因在于并没有真正的删去了边，即每次跳相邻边时可能会重复遍历删过的边。所以每次跳完（删完边）要把链头赋值为空。

接下来就是无脑模拟时间了。空间复杂度 $O(n)$，时间复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 3e5+17;
int i, j, k, n, m, f, x, q, a, b, c, t, l=1;
int d[N], h[N], u[N<<1];//d[i]表示i有多少个相连的点，u[i]表示当前边是否删除过
struct ab {
	int b, n;
} e[N<<1];
void cun(int a, int b) {
	e[++l] = (ab) {b, h[a]}, h[a] = l;
}
signed main(){
	scanf("%d%d", &n, &q);
	while(q--) {
		scanf("%d%d", &x, &a);
		if(x == 1) {
			scanf("%d", &b);
			if(++d[a] == 1) ++t;
			if(++d[b] == 1) ++t;
			cun(a, b), cun(b, a);//存边
		} else {
			for(i=h[a]; i; i=e[i].n) {
				b = e[i].b;
				if(!u[i]) {//没删过
					if(d[b]-- == 1) --t;
					u[i^1] = 1;//利用小知识的内容把另一条边标记被删除
				}
			}
			if(d[a]) --t;
			h[a] = d[a] = 0;//这里把链头改成0，防止下次再次遍历到被删除的边（核心）
		}
		printf("%d\n", n-t);
	}	
	return 0;
}
```

---

## 作者：ran_qwq (赞：7)

用 $n$ 个 set 维护这张图，同时维护一个变量 $ans$，记录当前没有边相连的点数。

### 一、对于操作 $1$，连接两个点 $x,y$：

1. 如果之前 $x$ 没边相连，$ans$ 减一；如果之前 $y$ 没边相连，$ans$ 同样减一。

2. 然后再在第 $x$ 和 $y$ 个 set 中加边。

### 二、对于操作 $2$，清除与 $x$ 相连的所有边：

1. 对于每条与 $x$ 相连的边，遍历第 $x$ 个 set。

2. 设 $y$ 与 $x$ 相连。在第 $y$ 个 set 中用 lower_bound 找到 $x$，在 $y$ 中删除。

3. 如果现在 $y$ 没边了，$ans$ 加一。

4. 遍历完 $x$ 的所有边后，把第 $x$ 个 set 清空，$ans$ 加一。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3e5+10,INF=0x3f3f3f3f;
int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();return x*f;}
void Write(int x){if(x<0){putchar('-'),Write(-x);return;}if(x<10){putchar(x+'0');return;}Write(x/10),putchar(x%10+'0');}
void write(int x,char *s){Write(x),printf("%s",s);}
int n,m,ans;
set<int>s[N];
set<int>::iterator it;
void solve()
{
	n=read(),m=read(),ans=n;
	while(m--)
	{
		int opt=read(),x=read(),y;
		if(opt==1) y=read(),ans-=s[x].empty()+s[y].empty(),s[x].insert(y),s[y].insert(x);
		else
		{
			for(it=s[x].begin();it!=s[x].end();it++)
			{
				int y=*it;
				s[y].erase(s[y].lower_bound(x)),ans+=s[y].empty();
			}
			if(s[x].size()) ans++,s[x].clear();
		}
		write(ans,"\n");
	}
}
signed main()
{
	int T=1;
	while(T--) solve();
}

```

---

## 作者：Xiphi (赞：3)

upd（5/23）：修改了一处错误

## 题意
有一张 $n$ 个点，初始时没有边的无向图。

有 $q$ 次操作，操作分两种：

- 添加一条 $u$ 到 $v$ 的边。
- 删除与 $u$ 相连的所有边。

每次操作后，输出没有边与其连接的点的数量。

## 解题思路

对于每条边，我们发现至多被删除 $1$ 次，所以可以直接暴力删边或者加边。然后用一个变量维护“被孤立点”的数量。这里注意要用 `set` 维护这张图。

这里我们讨论一下如何维护 $ans$ 变量，也就是维护数量的变量：

- 对于加边操作，即操作 $1$，如果加入这条边后 $u$ 或 $v$ 的度为 $1$，`ans-=1`，当然，如果两个点的度在加入边后都为 $1$，`ans-=2`。

- 对于删边操作，在删去一条边后，与 $u$ 相连的这个点度变为 $0$，`ans++`。

代码实现：

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<queue>
#include<vector>
#include<stack>
#include<string>
#include<cmath>
#include<cstring>
#include<set>
#include<map>
#define N 15
using namespace std;
int n,q,ans;
set<int> Adj[300005];
signed main(){
	ios::sync_with_stdio(false);
    cin.tie(0);
	cin>>n>>q;
	ans=n;
	while(q--){
		int op,u,v;
		cin>>op;
		if(op==1){
			cin>>u>>v;
			Adj[u].insert(v);
			Adj[v].insert(u);
			ans-=(Adj[u].size()==1)+(Adj[v].size()==1);
			cout<<ans<<'\n';
		}else{
			cin>>u;
			for(set<int>::iterator it=Adj[u].begin();it!=Adj[u].end();++it){
				Adj[*it].erase(u);
				if(Adj[*it].size()==0) ans++;
			}
//			Adj[u].clear();
			if(Adj[u].size()!=0)++ans;//特判
			Adj[u].clear();//千万记得clear
			cout<<ans<<'\n';
		}
	}
	return 0;
}
```

---

## 作者：happybob (赞：3)

## 题意

有一张 $n$ 个点，初始时没有边的无向图。

你要维护 $q$ 次操作，每次操作可能是下面的其中一个：

1. 添加一条 $u$ 到 $v$ 的边。
2. 删除与 $u$ 相连的所有边。

每次操作后，输出孤立点数量。

## 解法

发现添加只会添加一条边，而删除则可能删除许多。一条边如果被加入一次，那么最多只会被删除一次。

于是我们可以暴力删除，并且维护每个点的度。每个操作都将涉及到的点暴力重新算贡献。

```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <set>
#include <map>
#include <unordered_map>
#include <queue>
#include <stack>
#include <vector>
#include <utility>
#include <cstdlib>
#include <string>
using namespace std;

#define ll long long

const int N = 3e5 + 5, INF = 2e9, MOD = 1e9 + 7;

inline int read()
{
	int op = 1, x = 0;
	char ch = getchar();
	while ((ch < '0' || ch > '9') && ch != '-') ch = getchar();
	while (ch == '-')
	{
		op = -op;
		ch = getchar();
	}
	while (ch >= '0' and ch <= '9')
	{
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return x * op;
}

inline void write(int x)
{
	if (x < 0) putchar('-'), x = -x;
	if (x > 9) write(x / 10);
	putchar(x % 10 + '0');
}

int n, m, t;
set<int> G[N];
int d[N];
int ans;
int main()
{
	// freopen("*.in", "r", stdin);
	// freopen("*.out", "w", stdout);
	scanf("%d%d", &n, &m);
	ans = n;
	while (m--)
	{
		int op;
		scanf("%d", &op);
		if (op == 1)
		{
			int u, v;
			scanf("%d%d", &u, &v);
			G[u].insert(v);
			G[v].insert(u);
			ans -= (d[u] == 0);
			ans -= (d[v] == 0);
			d[u]++;
			d[v]++;
		}
		else
		{
			int x;
			scanf("%d", &x);
			for (auto i : G[x])
			{
				d[i]--;
				ans += (d[i] == 0);
				G[i].erase(x);
			}
			G[x].clear();
			ans += (d[x] != 0);
			d[x] = 0;
		}
		printf("%d\n", ans);
	}
	return 0;
}
```


---

## 作者：FreedomKing (赞：2)

### 思路

使用 set 暴力加边删边，暴力删边，然后遍历统计没有连接边的节点，复杂度为 $O(N^2)$。

不难发现，复杂度比较高的地方在于最后的遍历上，会使复杂度飙升，前面的操作复杂度仅仅只有 $O(N\log N)$。所以，我们考虑优化答案统计：

一开始，所有节点都没有连接的边，答案为 $n$ 个。

- 当加入一条边时，判断其连接的节点原本是否是答案，如果其中有原本是答案的，将其排除。

- 当删除一个节点连接的所有边时，判断删除后原先连接的每个节点是否新成为了答案，如果是，加入。

经过以上优化，时间复杂度成功优化到 $O(N\log N)$。

------------

### AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
int a[N],n,m,t,k;
set<int>st[N];
int main(){
	cin>>n>>t;
	k=n;
	while(t--){
		int op;
		cin>>op;
		if(op==1){
			int l,r;
			cin>>l>>r;
			if(st[l].empty()) k--;
			if(st[r].empty()) k--;
			st[l].insert(r);
			st[r].insert(l);
		}
		if(op==2){
			int x;
			cin>>x;
			for(auto i=st[x].begin();i!=st[x].end();i++){
				st[*i].erase(x);
				if(st[*i].empty()) k++;
			}
			if(!st[x].empty()) k++;
			st[x].erase(st[x].begin(),st[x].end());
		}
		cout<<k<<'\n';
	}
	return 0;
}
```

---

## 作者：MYiFR (赞：2)

### 题目大意
给定一个初始状态有 $N$ 个点，没有连边的图，你需要维护 $Q$ 次操作，操作类型有两种：

1. 将点 $u$ 和点 $v$ 用一条无向边连接起来，保证执行此操作时 $u$ 和 $v$ 之间没有直接的连边。
2. 将点 $u$ 所有的连边删除。

每次执行操作后，你需要输出没有连边的点的数量。

### 手撕样例
```
Input
3 7
1 1 2
1 1 3
1 2 3
2 1
1 1 2
2 2
1 1 2

Output
1
0
0
1
0
3
1
```
1. 此时只有 $3$ 没有连边
2. 此时没有点没有连边
3. 同 2
4. 此时 $1$ 没有连边
5. 同 2
6. 此时 $1,2,3$ 都没有连边
7. 同 1

### 解题思路
首先注意到 $Q\leq3\times 10^5$，所以最多加入 $3\times 10^5$ 条边；同理，每条边最多被删除一次，所以最多删除 $3\times 10^5$ 条边。

当然，初始状态，即尚未开始操作时 $ans=N$。

那么就可以用 stl 维护每个点直接连通的点，同时记录每个点的连边数量 $cnt_i$。加入边就向容器里丢点，检查 $cnt_u$ 是否等于 $0$，是的话 $ans-1$，$v$ 同理。否则遍历要删除所有连边的点 $x$ 对应的容器，将 $x$ 从所有连向的点对应的容器中删除，$cnt_y$ 自减。如果 $cnt_y=0$，$ans+1$。最后将 $cnt_x$ 归零，清空点 $x$ 对应的容器，$ans+1$。

stl 的选择有很多，但是涉及到将 $x$ 从所有连向的点对应的容器中删除的操作显然需要用到二分查找，所以建议选择 `set`，或者用 `vector`，在插入的时候排序亦可。

注：后面的 AC 代码 1（赛时代码）和上述思路都有一个空间的优化，就是 stl 自带的 `size` 功能可以实现维护 $cnt$ 的功能，所以 $cnt$ 数组是没有必要开的。

### AC 代码 1
```
#include<bits/stdc++.h>
#define ll long long
#define db double
#define pii pair<int,int>
#define pll pair<ll,ll>
#define pdd pair<db,db>
#define F first
#define S second
using namespace std;
const int N=3e5+5;
int n,q,opt,a,b,ans,cnt[N];
set<int> e[N];
int main(){
	scanf("%d%d",&n,&q);
	ans=n;
	while(q--){
		scanf("%d",&opt);
		if(opt==1){
			scanf("%d%d",&a,&b);
			e[a].insert(b);
			e[b].insert(a);
			if(cnt[a]==0) --ans;
			if(cnt[b]==0) --ans;
			++cnt[a];
			++cnt[b];
		}
		else{
			scanf("%d",&a);
			for(int to:e[a]){
				--cnt[to];
				if(cnt[to]==0) ++ans;
				e[to].erase(e[to].find(a));
			}
			e[a].clear();
			if(cnt[a]!=0) ++ans;
			cnt[a]=0;
		}
		printf("%d\n",ans);
	}
	return 0;
}
//Ltwcfm.
```

### AC 代码 2
```
#include<bits/stdc++.h>
#define ll long long
#define db double
#define pii pair<int,int>
#define pll pair<ll,ll>
#define pdd pair<db,db>
#define F first
#define S second
using namespace std;
const int N=3e5+5;
int n,q,opt,a,b,ans;
set<int> e[N];
int main(){
	scanf("%d%d",&n,&q);
	ans=n;
	while(q--){
		scanf("%d",&opt);
		if(opt==1){
			scanf("%d%d",&a,&b);
			if(e[a].empty()) --ans;
			if(e[b].empty()) --ans;
			e[a].insert(b);
			e[b].insert(a);
		}
		else{
			scanf("%d",&a);
			for(int to:e[a]){
				e[to].erase(e[to].find(a));
				if(e[to].empty()) ++ans;
			}
			if(!e[a].empty()) ++ans;
			e[a].clear();
		}
		printf("%d\n",ans);
	}
	return 0;
}
//Ltwcfm.
```

---

## 作者：FReQuenter (赞：1)

我们可以使用 map 记录点 $u$ 和点 $v$ 是否有边，命名为 `mp`。对于答案，我们维护一个变量 $s$，表示独立的点的数量。初值为 $n$。

对于操作 $1$：我们只需要将 `mp[u][v]` 和 `mp[v][u]` 都设为 $1$。如果操作前 `mp[u]` 为空，则 $s$ 减 $1$；如果操作前 `mp[v]` 为空，则 $s$ 再减 $1$；

对于操作 $2$：我们一一将它周围的点 （设为 $u$）去掉当前点（设为 $v$），即 `mp[u][v]=0,mp[v].clear()`。答案统计一下周围点变成孤立点的数量。别忘了当前点。

复杂度分析：每一次操作 $2$ 执行的数量都是到上一次操作 $2$ 之间执行的操作 $1$ 的数量，所以相当于执行了 $2$ 倍操作 $1$，则时间复杂度 $O(2n \log n)=O(n \log n)$。

```cpp
#include<bits/stdc++.h>
#define fi first
#define se second
using namespace std;
map<int,bool> mp[300005];
signed main(){
	int n,q;
	cin>>n>>q;
	int sum=n;
	while(q--){
		int op;
		cin>>op;
		if(op==1){
			int u,v;
			cin>>u>>v;
			if(!mp[u].size()) sum--;
			if(!mp[v].size()) sum--;
			mp[u][v]=1;
			mp[v][u]=1;
		}
		else{
			int v;
			cin>>v;
			if(mp[v].size()) sum++;
			for(auto nx:mp[v]){
				mp[nx.fi].erase(v);
				if(!mp[nx.fi].size()) sum++;
			}
			mp[v].clear();
		}
		cout<<sum<<'\n';
	}
}
```

---

## 作者：2huk (赞：1)

## 题目描述

有一个无向图，顶点标号 $1 \sim N$，最初没有边。

给定 $Q$ 个操作，每次操作完后输出孤立点的数量。

- `1 u v`：连接点 $u$ 和点 $v$；
- `2 v`：删掉所有与 $v$ 相连的边。

$2 \le N \le 3 \times 10^5,\ 1 \le Q \le 3 \times 10^5$

## 分析

这道题可以直接根据题意模拟。

定义答案变量  `res​` 表示当前孤立点的数量，显然最初 `res = n`。

由于接下来会有删除这种操作，这样使用 `vector` 或邻接表存图比较困难，因此使用 `set` 存图。

接下来分别处理两种操作。

- `1 u v`：连接点 $u$ 和点 $v$；
  
  如果连边前 $u$ 是孤立点，那么连边后孤立点的数量就会少 $1$，因此 `res​ -- `。$v$ 同理。然后连一条无向边。
  
  ```cpp
  if (g[u].empty()) res -- ;
  if (g[v].empty()) res -- ;
  g[u].insert(v);
  g[v].insert(u);
  ```
- `2 v`：删掉所有与 $v$ 相连的边。
  
  如果 $v$ 本身就是一个孤立点，那么删完边后没有发生变化，所以不做考虑。以下讨论的都是 $v$ 不是孤立点时的情况。
  
  首先找到所有与 $v$ 相邻的点，并在这个点所能到达的点的集合里将 $v$ 删除，然后判断删除后这个点是不是孤立点。若是则 `res ++ `。
  
  由于删完边后就没有了与 $v$ 连接的点，所以 $v$ 就变成了一个孤立点，因此再次 `res ++ `，然后删除所有与 $v$ 相连的边。
  
  ```cpp
  if (!g[u].empty())
  {
      res ++ ;
      for (int i : g[u])
      {
          g[i].erase(u);
          if (g[i].empty()) res ++ ;
      }
      g[u].clear();
  }
  ```

最后输出答案即可。

[Code](https://atcoder.jp/contests/abc302/submissions/41583636)


---

## 作者：Escapism (赞：0)

感觉放 ``E`` 还是稍微简单了一点。

[ATC 原题](https://atcoder.jp/contests/abc302/tasks/abc302_e)

# 题意

给出一张有 $n$ 个节点的图，图中初始时没有边。现在要求进行两种操作：

- 操作一：在节点 $u$ 和 $v$ 之间添加一条边。

- 操作二：删除与节点 $u$ 连接的所有边。

对于每一次操作，都需要给出操作之后有多少个节点一条边都没有连过。

# 思路

赛时脑抽了想不到可以直接暴力。

首先我们使用 ``set`` 来维护图。不使用 ``vector`` 的原因是它无法快速查询两个节点之间有没有连边，但 ``set`` 可以。

我们使用一个变量 $ans$ 来实时维护没有连边的节点的数量，那么我们依据两种操作会分成如下情况：

- 操作一，如果其中有一个节点之前没有连边，$ans$ 加 $1$；如果两个都没有连边，$ans$ 加 $2$。

- 操作二，首先对于操作的 $u$ 节点要 $ans$ 减一，还要考虑减去所有只与这一节点连接的点。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
 
const int MAXN = 3 * 1e5 + 5;
int n,q,ans;
set<int> XLR[MAXN]; //%%% XLR
 
int main(){
	scanf("%d %d",&n,&q);
	ans = n;
	while(q--){
		int op,u,v;
		cin>>op;
		if(op == 1){
			cin>>u>>v;
			XLR[u].insert(v);
			XLR[v].insert(u);
			if (XLR[u].size() == 1) ans--; //判断有几个节点是之前没有连过边的
			if (XLR[v].size() == 1) ans--;
			cout<<ans<<endl;
		}
		else{
			cin>>u;
			if (XLR[u].size() == 0){ //特判对没有连边的节点做操作二，参考样例二。
				cout<<ans<<endl;
				continue;
			}
			for(set<int>::iterator it = XLR[u].begin();it != XLR[u].end();++it){ //循环遍历 set 当中的每个元素，不会用的可以去看 wiki。
				XLR[*it].erase(u); //删边
				if(XLR[*it].size() == 0) ans++; //ans 加 1
			}
			ans++; //它本身也成为了一个没有连边的节点
			XLR[u].clear(); //清除
			cout<<ans<<endl;
		}
	}
	return 0;
}
```

[通过记录](https://atcoder.jp/contests/abc302/submissions/41651407)


---

## 作者：hellolin (赞：0)

## AtCoder Beginner Contest 302 - E - Isolation

[洛谷题面](https://www.luogu.com.cn/problem/AT_abc302_e) | [AtCoder 题面](https://atcoder.jp/contests/abc302/tasks/abc302_e) | [AC 记录](https://www.luogu.com.cn/record/111080126) | $\texttt{\color{73f273}*988}$

考虑开一个 `set` 来存图。剩下的就交给暴力了！（代码中有注释）

但是每次请求结束时还要输出 $\mathrm{ans}$，实际上此时不用浪费时间从头跑了，请求内部就可以计算答案，动态维护这个 $\mathrm{ans}$，复杂度 $O(Q\log N)$，可以通过本题。

完整代码如下：

``` cpp
// 珍爱账号，请勿贺题
#include <bits/stdc++.h>
using namespace std;
#define int long long

int n,q,x,u,v,ans;
vector<set<int>>a;
void solve(){
    cin>>n>>q;
    a.resize(n+1);
    ans=n; // 一开始所有点都是孤立的
    for(int i=1;i<=q;i++){
        cin>>x>>u;
        if(x==1){
            cin>>v;
            // 如果这个点之前就是孤立点，那么现在有边相连了，需要将 ans 减一
            ans-=a[u].empty();
            ans-=a[v].empty();
            // 加边
            a[u].insert(v);
            a[v].insert(u);
        }
        else{
            ans+=!a[u].empty(); // 如果这个点之前不是孤立的而现在是孤立的，需要 ans 加一
            for(int x:a[u]){ // 要删除所有与当前点相连的边，此处枚举每个与当前点相连的点并分别 erase 掉与当前点相连的边
                a[x].erase(u);
                ans+=a[x].empty(); // 如果删了之后有点被孤立了 ans 就加一
            }
            a[u].clear(); // 删边
        }

        cout<<ans<<endl;
    }
}

int32_t main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();

    return 0;
}
```


---

## 作者：_zzzzzzy_ (赞：0)

# 思路
用 `set` 来进行模拟删边和加边，用一个值来进行动态记录答案。

下面详细的说一下流程。

我们设一个 `ans` 初始值为 `n`，表示没有边连接的点的数量。

当我们遇到操作一的时候我们可以加上这一条边，然后判断这两个点之前的入度是否为 `0`，如果是 `0` 我们就令 `ans` 减去一个。

当我们遇见操作二的时候我们可以直接动态删除，如果删除了这条边之后没有入度了让 `ans` 加上一，最后我们可以发现删除后我们要删的点一定是没有边连接的，但如果他本身就是就不能再加一了。

最后我们来分析一下为什么这样是对的。

因为我们每一次删边最多是删除之前我们加的所有的边，所以简单分析可知复杂度是 $O(m\log m)$

# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
const int maxn = 500050;
set<int> S[maxn];
int in[maxn];
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, q, ans;
	cin >> n >> q;
	ans = n;
	for (int i = 1; i <= q; i ++) {
		int op ;
		cin >> op;
		if (op == 1){
			int u, v;
			cin >> u >> v;
			S[u].insert(v);
			S[v].insert(u);
			if (in[u] == 0){
				ans--;
			}
			if (in[v] == 0){
				ans--;
			}
			in[u]++;
			in[v]++;
		}
		else {
			int x;
			cin >> x;
			for (int k : S[x]) {
				in[k]--;
				if (in[k] == 0) {
					ans++;
				}
				S[k].erase(x);
			}
			if (S[x].size()){
				S[x].clear();
				ans++;
				in[x] = 0;
			}
		}
		cout << ans << "\n";
	}
	return 0;
}
```

---

## 作者：chlchl (赞：0)

## 题意
给定一个 $n$ 个节点的图。一开始图上没有连边。再给定 $q$ 次操作。

每次操作可能是以下两种之一：
- `1 u v`：新建一条无向边连接 $u,v$（保证 $u,v$ 在此之前没有连边）；
- `2 u`：删除所有与 $u$ 相连的边。

请输出每次操作后度为 $0$ 的点的个数。

## Solution
LCT？~~你怕是在想 p 吃~~。

其实直接对每个点开个 `set` 维护一下与它相连的边就行。因为每一条边最多被加进来一次删除一次，并且无法恢复，所以顶多操作 $q$ 次，时间复杂度 $O(q\log q)$，可以过的。

不过你需要动态维护度为 $0$ 的点的数量哦！

```cpp
#include<bits/stdc++.h>
using namespace std;
 
const int N = 3e5 + 10;
int n, q, cnt;
set<int> g[N];
 
int main(){
	scanf("%d%d", &n, &q);
	cnt = n;
	while(q--){
		int op, u, v;
		scanf("%d%d", &op, &u);
		if(op == 1){
			scanf("%d", &v);
			g[u].insert(v);
			g[v].insert(u);
//			cout << g[u].size() << ' ' << g[v].size() << endl;
			if(g[u].size() == 1)
				--cnt;
			if(g[v].size() == 1)
				--cnt;
		}
		if(op == 2){
			if(g[u].size())
				++cnt;
			for(set<int>::iterator i=g[u].begin();i!=g[u].end();i++){
				int v = *i;
				g[v].erase(g[v].find(u));
				if(!g[v].size())
					++cnt;
			}
			g[u].clear();
		}
		printf("%d\n", cnt);
	}
	return 0;
}
```

---

