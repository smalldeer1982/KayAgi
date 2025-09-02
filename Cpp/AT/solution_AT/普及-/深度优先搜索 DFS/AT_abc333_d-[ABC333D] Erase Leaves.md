# [ABC333D] Erase Leaves

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc333/tasks/abc333_d

頂点 $ 1, $ 頂点 $ 2,\ldots, $ 頂点 $ N $ の $ N $ 個の頂点からなる木が与えられます。 $ i $ 番目 $ (1\leq\ i\lt\ N) $ の辺は頂点 $ u\ _\ i $ と $ v\ _\ i $ を結んでいます。

次の操作を好きな回数繰り返すことを考えます。

- 葉である頂点 $ v $ を $ 1 $ つ選び、頂点 $ v $ およびそれに接続する辺をすべて削除する。
 
頂点 $ 1 $ を削除するまでに最小で操作を何回行う必要があるか求めてください。

 木とは？ 木とは、無向グラフのうち連結であって閉路がないものです。 詳しくはこちらをご覧ください: [Wikipedia「木 (数学)」](https://ja.wikipedia.org/wiki/%E6%9C%A8_(%E6%95%B0%E5%AD%A6))  葉とは？ 木の葉とは、木の頂点のうち次数がたかだか $ 1 $ であるものです。

## 说明/提示

### 制約

- $ 2\leq\ N\leq3\times10^5 $
- $ 1\leq\ u\ _\ i\lt\ v\ _\ i\leq\ N\ (1\leq\ i\lt\ N) $
- 与えられるグラフは木
- 入力はすべて整数
 
### Sample Explanation 1

与えられるグラフは次のようになります。 !\[\](https://img.atcoder.jp/abc333/6089239ee0c331bec4cd4472c032d197.png) たとえば、頂点 $ 9,8,7,6,1 $ の順に選んで操作を行うことで、$ 5 $ 回の操作で頂点 $ 1 $ を削除することができます。 !\[\](https://img.atcoder.jp/abc333/7dba9a660bfabdd403fe6882dac4e8ab.png) $ 4 $ 回以下の操作では頂点 $ 1 $ を削除することはできないため、$ 5 $ を出力してください。

### Sample Explanation 2

与えられたグラフにおいて、頂点 $ 1 $ は葉です。 よって、$ 1 $ 回目の操作で頂点 $ 1 $ を選んで削除することができます。

## 样例 #1

### 输入

```
9
1 2
2 3
2 4
2 5
1 6
6 7
7 8
7 9```

### 输出

```
5```

## 样例 #2

### 输入

```
6
1 2
2 3
2 4
3 5
3 6```

### 输出

```
1```

## 样例 #3

### 输入

```
24
3 6
7 17
7 20
7 11
14 18
17 21
6 19
5 22
9 24
11 14
6 23
8 17
9 12
4 17
2 15
1 17
3 9
10 16
7 13
2 16
1 16
5 7
1 3```

### 输出

```
12```

# 题解

## 作者：Running_a_way (赞：4)

update: 添加了在 [cnblogs](https://www.cnblogs.com/Running-a-way/p/18150534) 中阅读。

第一次打 atcoder - ABC 的比赛。at 题是真的不错。

如果运气好的话，这篇题解可能也是我第一篇过审的题解。
### Solution

题目来源：ABC333D （[访问洛谷](https://www.luogu.com.cn/problem/AT_abc333_d) | [访问 atcoder](https://atcoder.jp/contests/abc333/tasks/abc333_d)）。

题意：

>给你一棵有 $n$ 个结点的**无根**树，你可以花费 $1$ 的代价，删除一个叶子结点和其所连边（叶子结点指所连边数为 $1$ 的结点）。求删除 $1$ 号结点所需要的最小代价。$n \le3\times10^5$。

---

显然我们要删去结点 $1$，首先得让结点 $1$ 是叶子结点。而叶子结点的定义是「所连边数为 $1$ 的结点」，也就是说，我们要让结点 $1$ 的所连边数为 $1$。

不妨将结点 $1$ 看作根结点，这样，我们要通过删除操作，让根结点只剩下一颗子树，这个时候就可以把结点 $1$ 删去了。保留哪颗子树呢？若我们要让删除的子树结点数最小，那么需要让保留的子树结点最大。

那么我们只需从结点 $1$ 开始 dfs 求出以 $1$ 为根的、以 $i$ 为父结点的子树结点数 $val_i$，删除的结点数就是**结点 $1$ 所有子树结点数之和**减去**结点 $1$ 的最大子树结点数**。于是就做完了。记得把结点 $1$ 也删去，答案加上 $1$。

[Code](https://atcoder.jp/contests/abc333/submissions/48564889)

---

## 作者：Hughpig (赞：4)

考虑删除一个点的步骤：

* 如果这个点是叶子节点（度数为 $1$），那么可以直接删除。

* 否则可以设其度数为 $k$，那么要删除它的 $k-1$ 棵子树然后再删除它。

因此考虑先判断 $1$ 号节点入度是否为 $1$，如果是，直接输出 $1$。

否则一次 $\text{dfs}$ 搜出 $1$ 号节点的所有子树大小，然后找出最小的 $k-1$ 棵删去。记得答案要加上 $1$ 号节点自身。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int maxn=300007;
int n,deg[maxn],sz[maxn],ans,sum;
vector<int> G[maxn];

void calc(int u,int fa){//dfs 求出子树大小
	sz[u]=1;
	//cout<<u<<' ';
	for(int v:G[u]){
		if(fa==v)continue;
		calc(v,u);
		sz[u]+=sz[v];
	}
}

int main()
{
	ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1,u,v;i<n;i++)cin>>u>>v,deg[u]++,deg[v]++,G[u].push_back(v),G[v].push_back(u);
	if(deg[1]==1)cout<<1;//如果是叶子节点直接输出
	else{
		calc(1,0);
		for(int i:G[1]){
			ans=max(ans,sz[i]);//否则找出最大的子树不算，删去剩余的子树
			sum+=sz[i];//计算子树大小之和
		}
		cout<<sum-ans+1;
	}
	return 0;
}
```

---

## 作者：BLuemoon_ (赞：3)

[link](https://www.luogu.com.cn/problem/AT_abc333_d)

## 题意

给你一颗有 $N$ 个节点的**无根树**，你每次可以擦除一个叶子节点。问最少擦除几个叶子时，可以擦掉 $1$ 节点。

## 思路

根据无根树叶子的定义，当一个点的度为 $1$ 时，为叶子节点。而我们要消除 $1$ 节点，那我们就要让 $1$ 节点的度为 $1$。我们来放张大图：

![](https://cdn.luogu.com.cn/upload/image_hosting/av6a8jte.png)

每一颗字数都会对 $1$ 节点的度作出 $1$ 的贡献。所以我们如果要让 $1$ 节点的度为 $1$，就只能保留一个子树。为了使答案最小，我们要删掉前 $n - 1$ 小的子树，即只保留最大的子树。于是我们只需要找到最大的子树，答案就是总节点数减去最大的子树的节点个数。

## 代码

```cpp
// J2023 | BLuemoon_
#include <bits/stdc++.h>

using namespace std;
using LL = long long;

const int kMaxN = 3e5 + 5; //注意不是2e5

int n, cnt, ans;
vector<int> g[kMaxN];

void S(int x, int fa) {
    cnt++;
    for (int i : g[x]) {
        if (i != fa) {
            S(i, x);
        }
    }
}

int main() {
    cin >> n;
    for (int i = 1, u, v; i < n; i++) {
        cin >> u >> v;
        g[u].push_back(v), g[v].push_back(u);
    }
    for (int i : g[1]) {
        cnt = 0, S(i, 1);
        ans = max(ans, cnt);
    }
    cout << n - ans << '\n';
    return 0;
}
```

---

## 作者：2huk (赞：2)

# D - Erase Leaves

## Description

给定一颗 $n$ 个节点的无根树。每次你可以删除一个叶子节点（即度数为 $1$ 的点），问最少多少次操作可以删除 $1$ 节点。

$2 \le n \le 3 \times 10^5$。

## Solution

很显然的，如果我们把这棵树看作以 $1$ 节点为根，那么如果此时就能把根删掉就代表着根只有一个儿子，也就是只有一颗子树。

因为最开始 $1$ 有若干棵子树，所以我们要选择一颗子树留着，并将其它子树都删掉。可以发现删掉一个大小为 $s$ 的子树需要删 $s$ 次，所以最优情况下我们应该留下来那个最大的子树，并把其它小的子树删掉。

所以我们可以以 $1$ 为根，求出 $1$ 的每个儿子构成的子树的大小，并找出其中的最大值。若令这个最大值为 $res$，那么 $n - res$ 即为答案。

## Code

<https://atcoder.jp/contests/abc333/submissions/48554938>。

---

## 作者：xu222ux (赞：1)

# [ABC333D](https://www.luogu.com.cn/problem/AT_abc333_d)

## 思路

首先此题的树的根不是固定的，所以说我们可以把此题看成一个图。

先来思考一下，什么时候可以把节点 $1$ 删掉？

依题目来说，是叶子节点。那叶子节点有什么特性呢？没错，只有一个点和它相连。

也就是说，在节点 $1$ 只有一条边与之相连的时候，它就可以删掉了。之后就好想了，只需要留下 $1$ 的点数最多的子树就可以了，答案就是被删的节点个数。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int inf=1e18;
int n;
bool flag[300005];
vector<int>mp[300005];
int dfs(int x){
	if(flag[x])return 0;
	flag[x]=true;
	int res=1,mx=-inf;
	for(int i=0;i<mp[x].size();i++){
		int o=dfs(mp[x][i]);
		res+=o;
		mx=max(mx,o);
	}
	if(x==1)return res-mx;
	else return res;
}
signed main(){
	cin>>n;
	for(int i=1;i<n;i++){
		int u,v;cin>>u>>v;
		mp[u].push_back(v);
		mp[v].push_back(u);
	}
	cout<<dfs(1);
	return 0;
}
```

---

## 作者：yszkddzyh (赞：1)

题目大意：给出一个**无根树**，每次可以删去一个叶子结点，问至少删多少次才能把 $1$ 号节点删除。

很容易想到必须先删尽可能少的点，使 $1$ 变成叶子节点，然后删掉 $1$。

如何删尽可能少的点？要让 $1$ 变成叶子节点，即是让 $1$ 的度变成 $1$，所以我们如果将 $1$ 作为根节点，就要删掉一些子树，最后只保留一个子树，这时 $1$ 就已经变成原树中的叶子节点了。因为要删得尽可能少，所以保留的子树显然就是 $1$ 的所有子树中最大的。代码可以自己理解一下：

~~d 题貌似比 c 题简单。~~

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 3e5 + 5;
struct edge{
	int v, nxt;
}e[N << 1];
int n, tot, ans, head[N], siz[N];

void link(int u, int v){
	e[++tot].v = v;
	e[tot].nxt = head[u];
	head[u] = tot;
	return;
}
void dfs(int u, int f){//f为当前点的父节点
	siz[u] = 1;
	for(int i = head[u]; i; i = e[i].nxt){
		int v = e[i].v;
		if(v != f){
			dfs(v, u), siz[u] += siz[v];
			if(u == 1)
				ans = max(ans, siz[v]);//记录最大的子树的大小
		}
	}
	return;
}

int main(){
	
	scanf("%d", &n);
	for(int i = 1, u, v; i < n; i++){
		scanf("%d %d", &u, &v),
		link(u, v), link(v, u);
	}
	dfs(1, 0);
	printf("%d", n - ans);//n-ans即为答案
	
	return 0;
}
```

---

## 作者：2c_s (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc333_d)

## 思路

树链剖分。

题意是找出最少删掉几个相连的节点后能将 $1$ 号节点删除。如果我们将 $1$ 号节点作为这棵树的根来看，那么问题就变成了：

>最少删掉大小之和为多少的 $1$ 号节点的子树后，能将 $1$ 号节点的其中一颗子树保留。

进一步推理，想要使删除的 $1$ 号节点的子树的大小之和最小，那么我们保留的一定是 $1$ 号节点最大的一棵子树。于是问题被转化为了求总节点数减去 $1$ 号节点最大子树大小的值，用树链剖分很容易就能实现。

读入数据建树，之后从 $1$ 号节点开始进行树剖。树剖只需要找出每个节点子树的大小和其重儿子是谁。

树剖完毕后输出总节点个数减去 $1$ 号节点重儿子的大小的值即可。

## AC 代码

```cpp
#include<bits/stdc++.h>
#define pb push_back
using namespace std;
inline ll read(){//快读。
	ll k=0,flag=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')flag=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		k=(k<<1)+(k<<3)+(c^48);
		c=getchar();
	}
	return k*flag;
}
const int N=3e5+10;
int n,son[N],siz[N];
vector<int>g[N];
void dfs(int x,int f){//把这棵树剖成链。
	siz[x]=1;//这个节点的大小别忘加上这个节点本身。
	for(auto i:g[x]){
		if(i==f)continue;
		dfs(i,x);
		siz[x]+=siz[i];//记录大小。
		if(siz[son[x]]<siz[i])son[x]=i;//记录重儿子。
	}
	return ;
}
int main(){
	cin>>n;
	for(int i=1;i<n;++i){
		int u=read(),v=read();
		g[u].pb(v);
		g[v].pb(u);
	}
	dfs(1,0);
	cout<<n-siz[son[1]];
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/139916901)

---

## 作者：Milthm (赞：1)

容易发现除了 $1$ 以外的节点需要把以它为根的所有子树除了它以外都删掉，它才能成为叶子节点，从而才能被删掉。

而 $1$ 因为没有父亲节点，所以可以在保留一个儿子的子树的情况下成为可以被删除的节点。

假设这个子树的大小为 $siz$，你要使删除的节点数量，即 $n-siz$ 最小，很明显需要使 $siz$ 最大。

于是找到 $1$ 节点的儿子中子树大小最大的，用 $n$ 一减就行了。

### AC code

```cpp
#include<bits/stdc++.h>
#define int long long
#define N 300005
using namespace std;
int n,u,v,lxy;
vector<int>e[N];
int dfs(int u,int fa){
	int ans=1;
	for(int i=0;i<e[u].size();++i){
		int v=e[u][i];
		if(v!=fa)ans+=dfs(v,u);
	}
	return ans;
}
signed main(){
	cin>>n;
	for(int i=1;i<n;++i){
		cin>>u>>v;
		e[u].push_back(v);e[v].push_back(u);
	}
	if(e[1].size()==1){
		cout<<1;return 0;
	}
	for(int i=0;i<e[1].size();++i){
		int v=e[1][i];
		lxy=max(lxy,dfs(v,1));
	}
	cout<<n-lxy;
	return 0;
}

```


---

## 作者：U_star (赞：1)

ABC 终于上绿了！写篇题解祝贺一下！

这道题大意：给你一个有 $n$ 个节点的树，每次操作可以删除这棵树的一个叶子节点，求删掉 $1$ 号节点至少需要多少次操作。

由于我们每次只能删掉叶节点，因此最后删掉 $1$ 号节点时，它必然是一个叶子节点。接下来我们就可以理出大致思路：

- 如果 $1$ 号结点是叶子节点，那么直接输出 `1`。
- 否则，我们将 $1$ 号结点作为这棵树的根节点，接下来我们遍历它所有的子节点，很显然，为了删除这个子节点，我们必须删除以这个子节点为根的子树，而删除这个子树要多少次呢？很显然就是这个子树的大小。最后，我们需要删除所有子树，仅留下一棵，即可删除 $1$ 号节点。而最后留下的这颗子树必然是最难删除的（删除所需操作次数最多的）。

如果你还是不懂，那我用一个图演示一下：

![graph](https://picss.sunbangyan.cn/2023/12/17/16b003ecb6174ff377a0fd1e89059cb9.jpeg)

$1$ 号节点的子节点有 $2,3,5,6,9$，以它们为根的子树的大小分别是 $1,4,1,2,1$。因此此时的最优删除策略是 $2,5,10,6,9,1$，共需六次。可以看到，我们保留了删除次数最多的以 $3$ 为根的子树。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,u[300005],v[300005],p[300005],r[300005],ans=1,sum,maxn;
vector<int>e[300005];
int dfs(int k)
{
	if(r[k]==1)//标记数组，防止节点被重复遍历，陷入死循环
	return 0;
	r[k]=1;
	int t=e[k].size(),anss=1;//注意到删除该节点本身也需要一次操作，因此 anss 的初值为 1
	if(t==1)//如果是叶子节点直接返回 1
	return 1;
	for(int i=0;i<t;i++)//遍历其所有边
	{
		p[e[k][i]]=dfs(e[k][i]);
		anss+=p[e[k][i]];
	}
	return anss;//返回删除这个节点所需要的次数
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0); 
	cin>>n;
	for(int i=1;i<n;i++)
	{
		cin>>u[i]>>v[i];
		e[u[i]].push_back(v[i]);
		e[v[i]].push_back(u[i]);
	}
	int s=e[1].size();
	r[1]=1;
	for(int i=0;i<s;i++)
	{
		sum=dfs(e[1][i]);
		ans+=sum;
		maxn=max(maxn,sum);//maxn 记录以 1 的子节点为根的最大的子树的删除次数
	}
	cout<<ans-maxn<<"\n";//最后减去 maxn
	return 0;
}
```


---

## 作者：Heavy_Data_Struct (赞：1)

## 题目大意
有一棵树，每次可以删除一个叶节点，求出最少的删除次数使节点 $1$ 被删除。

## 分析
在下面的表示中，$\mathcal T^i$ 表示以 $i$ 为根时树的形态，$|\mathcal T^x_i|$ 表示以 $x$ 为根时以节点 $i$ 为根的子树大小。

性质：叶节点的度为 $1$，即一个节点 $x$ 为叶节点，当且仅当在 $\mathcal T^x$ 中，$x$ 的子树数量 $\le 1$。

最快让 $1$ 成为叶节点，可以删除除了 $1$ **最大的**子树外所有子树，使 $1$ 仅有一个子树，再删除 $1$，代价为 $N-\max_{i=2}^{n}|\mathcal T^1_i|$。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n, a[300005], ans[300005];
vector<int>vc[300005];
int dfs(int u, int f) {
  ans[u] = 1;
  int ret = 0;
  for(auto v : vc[u])
    if(v != f) {
      int t = dfs(v, u);
      ans[u] = max(ans[u], t + 1);
      ret += t;
    }
  return ret + 1;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n;
  for(int i = 1;i < n;i ++) {
    int u, v;
    cin >> u >> v;
    a[u] ++;
    a[v] ++;
    vc[u].push_back(v);
    vc[v].push_back(u);
  }
  if(a[1] == 1)cout << 1;
  else {
    int t = dfs(1, 0);
    cout << n - ans[1] +1;
  }
}
```

---

## 作者：tbdsh (赞：0)

# 题意简述
[洛谷原题面](//www.luogu.com.cn/problem/at_abc333_d)

[AtCoder 原题面](https://atcoder.jp/contests/abc333/tasks/abc333_d)

给定一颗有 $n(2\le n\le 3\times 10^5)$ 个结点的树。请你不断选择一个叶子结点，并删掉它以及它相连的所有边。输出删掉结点 $1$ 的最小操作次数。

# 分析
注意到要删掉结点 $1$ 的前提是它只连着 $1$ 个点。

除此之外，结点 $1$ 其它所有连着的点都要删掉。

那么，我们就保留结点 $1$ 子树最大的那一颗，其它子树全部删掉，最后在加上删掉结点 $1$ 的一次即可。

时间复杂度：$O(n)$。

空间复杂度：$O(n)$。

# Code
```cpp
#include<bits/stdc++.h>

using namespace std;
const int MAXN = 3e5 + 5;
int n, cnt, sz[MAXN], ans;
set<int> a[MAXN];
void dfs(int x, int fa){
  sz[x]++;
  for (auto v : a[x]){
    if (v != fa){
      dfs(v, x);
      sz[x] += sz[v];
      if (x == 1){
        cnt = max(cnt, sz[v]);
      }
    }
  }
  if (x == 1 && a[1].size() == 1){
    return ;
  }

  for (auto v : a[x]){
    if (v != fa && x == 1){
      ans += sz[v];
    }
  }
}
signed main(){
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> n;
  for (int i = 1, u, v; i < n; i++){
    cin >> u >> v;
    a[u].insert(v);
    a[v].insert(u);
  }
  dfs(1, 0);
  cout << ans - (a[1].size() == 1 ? 0 : cnt) + 1;
  return 0;
}
```

---

## 作者：1234567890sjx (赞：0)

**【前言】**

D 怎么比 E 难。

**【正文】**

比较简单的树形 dp。

设 $f_i$ 表示 $i$ 子树的元素数量，$g_i$ 表示删除 $i$ 子树内的元素需要的最少操作次数。（不包含 $i$ 点）

那么令点集 $V$ 为所有和 $i$ 有连边且在 $i$ 子树内的点的数量。显然有 $f_i=(\sum_{j\in V} f_j)+1$，$g_i=\sum_{j\in v}g_j-\max_{j\in V}g_j$。

根据定义得出答案就是 $g_1+1$。

时间复杂度 $O(n)$。

**【代码】**

实现的极端丑陋，略。

---

## 作者：_Weslie_ (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/AT_abc333_d)。

## 思路

以 $1$ 为根，将无根树变为有根树。

对于一个非 $1$ 节点，首先我们要先消掉它的所有子节点。

但是如果要消除 $1$，我们可以剩下一个子节点（这样 $1$ 也成了叶子节点）。

而剩下的子节点应该是子树大小最大的。

再来手搓一组样例：

![](https://cdn.luogu.com.cn/upload/image_hosting/j8si85rl.png)

我们看到，如果要删除 $1$，首先一定要删除 $2$、$4$、$7$ 之中的三个。

但是删除 $2$ 只需要删除 $3$，删除 $4$ 只需要删除 $5$、$6$，而删除 $7$ 需要删除 $8$、$9$、$10$、$11$。

很明显，删除 $2$、$3$，留下 $7$ 更合算。

所以这个样例答案是 $6$。

```
#include<bits/stdc++.h>
using namespace std;
int head[600005],to[600005],from[600005],cnt,nxt[600005],son[600005];
void add(int u,int v){
	to[++cnt]=v;
	from[cnt]=u;
	nxt[cnt]=head[u];
	head[u]=cnt;
}
int n,u,v;
int dfs(int now,int fa){
	int ans=0;
	for(int i=head[now];i;i=nxt[i]){
		if(to[i]!=fa)ans+=dfs(to[i],now); 
	} 
	son[now]=ans+1;
	return ans+1;
}
int du=0,kiss[300005],tot;
int main(){
	cin>>n;
	for(int i=1;i<n;i++){
		cin>>u>>v;
		add(u,v);
		add(v,u);
		if(u==1||v==1)du++;
	}
	if(du==1||du==0){
		cout<<1<<endl;
		return 0;
	}
	dfs(1,0);
	int ans=0,maxx=0;
	for(int i=head[1];i;i=nxt[i]){
		ans+=son[to[i]];
		maxx=max(maxx,son[to[i]]);
	}
	cout<<ans-maxx+1;
	return 0;
}
```

---

## 作者：Shadow_T (赞：0)

### 题目大意

给你一棵树，可以执行一下操作任意次：

- 选择一个叶结点 $v$，将其删除。

求至少要几次才可以删除点 $1$。

### 解题思路

很有意思的题目。

贪心，肯定要先找结点少的子树删。

那么我们可以求出 $1$ 的所有子树的结点数，设 $1$ 有 $s$ 个儿子，那么求出前 $s-1$ 小的字数节点数的和。最后答案再加一，删去结点 $1$。

求子树的结点数时直接搜索即可。

### 代码

```cpp
// LUOGU_RID: 139934389
#include<bits/stdc++.h>
using namespace std;
const int maxn=3e5+10;
vector<int> Node[maxn];
int vis[maxn];
int t,tot;
void dfs(int x)
{
	for(int i=0;i<Node[x].size();i++)
	if(vis[Node[x][i]]!=t)
	{
		tot++;
		vis[Node[x][i]]=t;
		dfs(Node[x][i]);
	}
}
int main()
{
	int n;
	cin>>n;
	int u,v;
	for(int i=1;i<=n-1;i++)
	{
		scanf("%d%d",&u,&v);
		Node[u].push_back(v);
		Node[v].push_back(u);
	}
	int ans=0;
	if(Node[1].size()==1)
	{
		cout<<1;
		return 0;
	}
	int zg=0;
	for(int i=0;i<Node[1].size();i++)
	{
		t++;
		vis[1]=t;
		vis[Node[1][i]]=t;
		dfs(Node[1][i]);
		ans=max(ans,tot);
		zg+=tot;
		tot=0;
	}
	cout<<n-1-ans;
	return 0;
}
```

---

## 作者：zhangjiting (赞：0)

## 题意

有一棵树，每次可以删掉一个叶子，求最少几次后可以删掉结点 $1$。

## 思路

我们如果想把 $1$ 变成叶子，只能保留他的一个儿子，这个儿子的子树长什么样都没关系。换句话说，我们需要删除这棵树上，$1$ 的一个儿子及其子树除外的所有结点。那我们一定希望保留的结点最多，也就是选择 $1$ 儿子中子树最大的保留，其余删除。只要求出每个点的子树大小就可以了。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e5+5;
int siz[N],son[N],n,ans=INT_MIN;
vector<int> G[N];
void dfs(int u,int fa){
	siz[u]=1;
	for(int i=0;i<G[u].size();i++){
		int v=G[u][i];
		if(v==fa) continue;
		dfs(v,u);
		siz[u]+=siz[v];
	}
}
signed main(){
	cin>>n;
	for(int u,v,i=1;i<n;i++){
		cin>>u>>v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	dfs(1,0);
	for(int i=0;i<G[1].size();i++){
		int y=G[1][i];
		ans=max(ans,siz[y]);
	}
	cout<<n-ans;
	return 0;
}

```


---

## 作者：yuyc (赞：0)

### 题意
给定一个由 $N$ 个结点组成的树。

你可以进行该操作若干次：

- 删除一个叶子结点和与其相连的那条边。

问：至少要操作多少次才能删除结点 $1$。
### 解析
想要删除结点 $1$ 就必须使结点 $1$ 变为叶子结点，即删除与结点 $1$ 相连的结点直至结点 $1$ 只与一个结点相连。

而想要删除与结点 $1$ 相连的结点，就同样必须使其变为叶子结点，即删除与 **与结点 $1$ 相连的结点** 相连的结点直至其只与一个结点相连。

依此类推，假设以结点 $1$ 为根，其儿子有 $x$ 个，那么想要删除结点 $1$ 就需要删除 $x-1$ 棵**以结点 $1$ 的儿子为根节点**的子树。

想要使得操作次数最少，选择结点数量最少的 $x-1$ 棵子树即可。

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 100005 * 3;
vector<vector<int> > tree;
vector<int> res;
bool vis[N];
int size(int x){
	vis[x] = true;
	int res = 1;
	for(int i=0;i<tree[x].size();i++){
		if(!vis[tree[x][i]]){			
			res += size(tree[x][i]);
		}
	}
	return res;
}
int main(){
	int ans = 1,maxres = 0;
	int n;
	cin>>n;
	tree.resize(n + 5);
	for(int i=0;i<n - 1;i++){
		int u,v;
		cin>>u>>v;
		tree[u].push_back(v);
		tree[v].push_back(u);
	}
	vis[1] = true;
	for(int i=0;i<tree[1].size();i++){
		int res = size(tree[1][i]);
		ans += res;
		maxres = max(maxres,res);
	}
	cout<<ans - maxres;
	return 0;
}
```


---

## 作者：Miss_SGT (赞：0)

### 题意：
给你一棵树，每次可以删掉一个叶子节点，问想要删除 $1$ 节点最少要删几个点。
### 做法：
想要删除 $1$ 节点，必须把它的直接儿子删的只剩一个，使它变成叶子。假设 $1$ 有 $d$ 个直接儿子，直接贪心排序选择前 $d-1$ 个，求和并加上删掉 $1$ 的一次操作即可。

赛时代码（很丑，因为错了了几次心情不好）：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3e5+5;
template<typename T>inline void read(T &x){
	x=0;int f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-') f=-1;c=getchar();}
	while(isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
	x*=f;
}
int head[N],to[N<<1],nxt[N<<1],tot;
inline void add(int x,int y){
	to[++tot]=y;
	nxt[tot]=head[x];
	head[x]=tot;
}
int n,sz[N],u,v;
void dfs(int p,int fa){
	sz[p]=1;
	vector<int> v;
	for(int o=head[p];o;o=nxt[o]){
		if(to[o]==fa) continue;
		dfs(to[o],p);
		sz[p]+=sz[to[o]];
		v.push_back(sz[to[o]]);
	}
	if(p==1){
		sort(v.begin(),v.end());
		int ans=1;
		for(int i=0;i<(int)v.size()-1;++i) ans+=v[i];
		cout<<ans;
	}
}
int main(){
	read(n);
	for(int i=1;i<n;++i){
		read(u),read(v);
		add(u,v);
		add(v,u);
	}
	dfs(1,0);
	return 0;
}

```


---

