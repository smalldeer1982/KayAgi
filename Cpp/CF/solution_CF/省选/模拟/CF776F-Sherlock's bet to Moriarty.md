# Sherlock's bet to Moriarty

## 题目描述

Sherlock met Moriarty for a final battle of wits. He gave him a regular $ n $ sided convex polygon. In addition to it, he gave him certain diagonals to form regions on the polygon. It was guaranteed that the diagonals did not intersect in interior points.

He took each of the region and calculated its importance value. Importance value for a region formed by vertices $ a_{1},a_{2},...\ ,a_{x} $ of the polygon will be given by $ 2^{a_{1}}+2^{a_{2}}+...+2^{a_{x}} $ . Then, he sorted these regions on the basis of their importance value in ascending order. After that he assigned each region an index from $ 1 $ to $ k $ , where $ k $ is the number of regions, and index of region is its position in the sorted array calculated above.

He wants Moriarty to color the regions using not more than $ 20 $ colors, such that two regions have same color only if all the simple paths between these two regions have at least one region with color value less than the color value assigned to these regions. Simple path between two regions $ f $ and $ h $ is a sequence of regions $ r_{1},r_{2},...\ r_{t} $ such that $ r_{1}=f $ , $ r_{t}=h $ , for each $ 1<=i&lt;t $ regions $ r_{i} $ and $ r_{i+1} $ share an edge, and $ r_{i}=r_{j} $ if and only if $ i=j $ .

Moriarty couldn't answer and asks Sherlock to solve it himself. Help Sherlock in doing so.

## 说明/提示

In 2nd input, regions formed in order after sorting will be $ (1,2,3) $ , $ (1,3,4) $ , $ (1,4,5) $ , $ (1,5,6) $ , i.e, region $ (1,2,3) $ is first region followed by region $ (1,3,4) $ and so on.

So, we can color regions $ 1 $ and $ 3 $ with same color, as region number $ 2 $ is on the path from $ 1 $ to $ 3 $ and it has color $ 1 $ which is less than color of $ 1 $ and $ 3 $ , i.e., color number $ 2 $ .

## 样例 #1

### 输入

```
4 1
1 3
```

### 输出

```
1 2
```

## 样例 #2

### 输入

```
6 3
1 3
1 4
1 5
```

### 输出

```
2 1 2 3
```

# 题解

## 作者：Alex_Wei (赞：1)

> D. [CF776F Sherlock's bet to Moriarty](https://www.luogu.com.cn/problem/CF776F) *2800

> 存在一个 $n$ 个点的多边形，点按顺序从 $1$ 到 $n$ 标号。$m$ 条不在除了端点以外的地方相交的对角线将多边形划分成 $m + 1$ 个区域 $R_1, R_2, \cdots, R_{m + 1}$。
>
> 令某个区域的端点为 $a_1, a_2, \cdots, a_{|R_i|}$，定义一个区域的重要度为 $f(R_i) = \sum\limits_{j = 1} ^ {|R_i|} 2 ^ {a_j}$。将所有区域按重要度从小到大排序并编号，即 $f(R_1) < f(R_2) < \cdots < f(R_{m + 1})$。
>
> 现在，你要给每个区域染上一种颜色，用一个 $1\sim 20$ 之间的正整数表示。
>
> 求出这样一种染色方案，使得对于任意两个颜色相同的区域 $R_i$ 和 $R_j(i\neq j)$，均满足它们之间的任何一条简单路径上都均存在至少一个区域 $R_k$ 使得 $R_k$ 的颜色小于 $R_i$ 和 $R_j$ 的颜色。简单路径定义为不经过重复区域，且路径上相邻两个区域有一条公共边的路径。
>
> 按编号顺序输出每个区域的颜色。
>
> 可以证明在题目限制下一定存在解，若有多解输出任意一个。
>
> $3\leq n \leq 10 ^ 5$，$0\leq m \leq n - 3$。

阅读理解 + STL 基础使用练习题。

我们将整个多边形剖分的区域建出树来，任意两个区域的简单路径就是它们在树上的简单路径。相当于我们要给整棵树染色，使得任意两个相同颜色的节点之间存在颜色小于它的节点。

那么问题就变成了两部分，一是给多边形剖分建树，二是树染色。

---

先解决第一部分建树。

设所有对角线连接顶点 $a_i, b_i$，且 $a_i < b_i$。由于保证对角线两两不交，所以我们类似括号序列那样处理每条对角线。将所有二元组涉及到的共 $2m$ 个顶点按标号从小到大排序，然后依次扫描。注意若两个顶点编号相同，那么按照类型为 $b$ 的顶点在前，类型为 $a$ 的顶点在后，这样才能保证不会错误匹配。

设当前节点为 $x_i$。若 $x_i$ 是某个 $a_j$，那么将其入栈。否则 $x_i$ 是某个 $b_j$，且当前栈顶即为其对应的 $a_j$。那么 $[a_j, b_j]$ 这个区间就形成了一个区域。想象用一把刀把它切掉，这意味着我们将所有在 $(a_j, b_j)$ 范围内的顶点删去（有些节点在之前的操作中已经被删去了）。本次操作被删去的顶点，再加上两个端点 $a_j$ 和 $b_j$，就是当前区域 $R_k$ 的顶点。删点可以用双向链表或 `set` 维护。

这样，我们得到了所有 $m + 1$ 个区域的所有顶点。将其按照字典序（题目中的规则）从小到大排序得到编号。然后枚举每一条对角线，它是某两个区域的公共边，找到这两个区域（通过 `map` 或其他方式容易实现）并在他们之间连一条边，即可得到最终的剖分树。

---

第二部分看起来有些棘手（但我不会告诉你本人做过一道非常类似的题目所以直接秒掉了，题目在题解最后）。尝试分析一些性质。

先假设我们已经找到了符合条件的染色方案。**很多问题都是先从一个满足限制的局面出发分析性质，从而推得满足限制的充要条件**。

对于某种颜色 $c$，找到树上所有颜色为 $c$ 的节点 $S$。考虑点集 $S$ 在原树上张成的虚树，必然需要有若干颜色 $< c$ 的节点将 $S$ 分割开来。也即扣掉颜色 $< c$ 的点之后 $S$ 不连通。

考察点分治的过程，我们将根节点扣掉后，形成若干不连通的子树。这与上面的观察有相似之处，考虑定量描述。因为一棵树的深度具有子节点大于父节点的性质，所以原图的任意一棵点分树的深度情况均为一种可行的染色方案。

（我已经尽力在说明应该怎么想到点分树了，可是看起来还是有些不自然 /ll）

因此，只需对原树进行点分治，求出每个点在点分树上的深度。标号大小为严格 $\log_2 n + 1$，符合题目 $20$ 的限制。前提是在寻找子树重心时正确下传子树大小，而非用当前分治重心的父亲作为根时对应子树大小作为以当前分治重心作为根时对应子树大小，尽管后者不影响时间复杂度但会使得递归层数不满足严格 $\log_2 n$ 的限制（应该至多乘上一个 $2$，那么就寄了）。

时间复杂度线性对数。类似的问题见 [P5912 [POI2004]JAS](https://www.luogu.com.cn/problem/P5912)。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
int n, m, stc[N], top;
pair <int, int> p[N << 1];
map <pair <int, int>, int> mp;
set <int> s;
vector <int> rg[N];
int R, mx[N], vis[N], sz[N], label[N];
vector <int> g[N];
void findroot(int id, int fa, int tot) {
	mx[id] = 0, sz[id] = 1;
	for(int it : g[id]) {
		if(it == fa || vis[it]) continue;
		findroot(it, id, tot);
		sz[id] += sz[it], mx[id] = max(mx[id], sz[it]);
	}
	mx[id] = max(mx[id], tot - sz[id]);
	if(mx[R] > mx[id]) R = id;
}
void findsize(int id, int fa) {
	sz[id] = 1;
	for(int it : g[id]) if(it != fa && !vis[it]) findsize(it, id), sz[id] += sz[it];
}
void divide(int id) {
	vis[id] = 1;
	for(int it : g[id]) {
		if(vis[it]) continue;
		findsize(it, id); // ADD THIS LINE
		R = 0, findroot(it, id, sz[it]);
		label[R] = label[id] + 1, divide(R);
	}
}
int main() {
	// freopen("1.in", "r", stdin);
	cin >> n >> m;
	mx[0] = n;
	for(int i = 1; i <= n; i++) s.insert(i);
	for(int i = 1, x, y, cnt = 0; i <= m; i++) {
		cin >> x >> y;
		if(x > y) swap(x, y);
		p[++cnt] = {x, 1}, p[++cnt] = {y, 0};
	}
	sort(p + 1, p + m * 2 + 1);
	for(int i = 1, cnt = 0; i <= m * 2; i++) {
		int id = p[i].first;
		if(p[i].second) {stc[++top] = id; continue;}
		int l = stc[top--];
		// cerr << l << " " << id << endl;
		rg[++cnt].push_back(l), rg[cnt].push_back(id);
		while(1) {
			// cerr << l << " " << r << " " << *--s.end() << endl;
			auto it = s.upper_bound(l);
			assert(it != s.end());
			if(*it == id) break;
			rg[cnt].push_back(*it), s.erase(it);
		}
	}
	m++;
	while(!s.empty()) rg[m].push_back(*--s.end()), s.erase(--s.end());
	for(int i = 1; i <= m; i++) sort(rg[i].begin(), rg[i].end()), reverse(rg[i].begin(), rg[i].end());
	// for(int i = 1; i <= m; i++) {
	// 	cerr << "chk " << i << " : ";
	// 	for(int it : rg[i]) cerr << it << " ";
	// 	cerr << endl;
	// }
	sort(rg + 1, rg + m + 1);
	for(int i = 1; i <= m; i++) {
		// cerr << "chk " << i << " : ";
		// for(int it : rg[i]) cerr << it << " ";
		// cerr << endl;
		for(int j = 0; j < rg[i].size(); j++) {
			int x = rg[i][j], y = j ? rg[i][j - 1] : rg[i].back();
			if(x > y) swap(x, y);
			if(x == 1 && y == n || x + 1 == y) continue;
			// cerr << "chk " << x << " " << y << endl;
			auto it = mp.find(make_pair(x, y));
			if(it == mp.end()) mp[make_pair(x, y)] = i;
			else g[it -> second].push_back(i), g[i].push_back(it -> second);
		}
	}
	findroot(1, 0, m), label[R] = 1, divide(R);
	for(int i = 1; i <= m; i++) cout << label[i] << " ";
	return 0;
}

/*
2022/5/1
start thinking at 14:06

把整个剖分建成树.
搞个点分树就好了.
求最小染色数量也有原题 POI2004 JAS

剖分连边写挂了 =.= 直接用栈搞就好了啊!!!
直接写不严谨的点分治是不行的!!!! 要严谨的点分治.

start coding at 14:27
finish debugging at 15:13
*/
```

---

## 作者：xtx1092515503 (赞：0)

阅读理解题。

------

翻译：给定一个正 $n$ 边形，用 $m$ 条对角线将其分开，保证对角线两两无交。

你需要为分成的每个部分染色（即赋一个值），满足对于任两个同色部分，对于每一条路径（路径指若干部分构成的序列，满足在序列中相邻的部分有公共边），路径都中存在一个部分，满足其颜色对应的值小于此二同色部分的颜色对应的值。你只能使用不超过 $20$ 种颜色。

输出一种方案。使用如下的方式为每个部分标号：

- 定义一个部分的权值为 $\sum 2^{a_i}$，其中 $\{a\}$ 是与之相邻的顶点集合。
- 将所有部分按照权值递增排序。
- 排序完后，一个部分在序列中的位置即为其标号。

按照标号顺序输出每个元素的染色。

------

首先先考虑多边形分割问题。然后发现它割出来一棵树。

那么染色问题就很好办了。直接大力淀粉质，将一个点的权值赋成其在分治树上的深度即可。显然这样我们只需 $O(\log m)$ 种不同颜色。

然后就要建出树来了。在 $1-n$ 边处断环成链，然后用栈随便搞搞就出来了。

然后就需要处理标号。可以发现，所有部分的所有相邻顶点集合的大小总和是 $O(n+m)$ 的，于是我们可以暴力处理出节点的大小集合；然后，观察发现任两个部分不存在三个公共顶点，于是比较是 $O(1)$ 的，进而可以直接排序。

复杂度 $n\log n$。

代码：

```cpp
/*
Criteria:
1.read the problem carefully; WRITE DOWN SPECIAL CONSTRAINTS when the problem is long;
2.consider special situations/constraints to get observations;
3.think of everything throughout before coding;
4.return to the initial list of notifications after coding.

CONSTRAINTS:

OBSERVATIONS:

OTHER NOTIFICATIONS:

THINK CAREFULLY AND CODE DETERMINEDLY!
*/
#include<bits/stdc++.h>
using namespace std;
int n,m,stk[100100],tp,fa[100100],ord[100100],RT,SZ,msz[100100],sz[100100],res[100100];
pair<int,int>p[100100];
vector<int>v[100100],u[100100];
vector<int>w;
bool vis[100100];
void getroot(int x,int fa){
	msz[x]=0,sz[x]=1;
	for(auto y:v[x])if(y!=fa&&!vis[y])getroot(y,x),msz[x]=max(msz[x],sz[y]),sz[x]+=sz[y];
	msz[x]=max(msz[x],SZ-sz[x]);
	if(msz[x]<msz[RT])RT=x;
}
void getsz(int x,int fa){sz[x]=1;for(auto y:v[x])if(y!=fa&&!vis[y])getsz(y,x),sz[x]+=sz[y];}
void solve(int x,int dep){
	getsz(x,0),vis[x]=true,res[x]=dep;
	for(auto y:v[x])if(!vis[y])RT=0,SZ=sz[y],getroot(y,0),solve(RT,dep+1);
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1,x,y;i<=m;i++){
		scanf("%d%d",&x,&y);
		if(x>y)swap(x,y);
		p[i]=make_pair(x,y);
	}
	p[++m]=make_pair(1,n);
	sort(p+1,p+m+1,[](const pair<int,int>&u,const pair<int,int>&v){return u.first==v.first?u.second<v.second:u.first>v.first;});
	for(int i=1;i<=m;i++){
		w.push_back(p[i].first);
		while(tp&&p[stk[tp]].second<=p[i].second)
			w.push_back(p[stk[tp]].first),w.push_back(p[stk[tp]].second),v[i].push_back(stk[tp]),v[stk[tp]].push_back(i),tp--;
		w.push_back(p[i].second);
		for(int j=0;j+1<w.size();j+=2)for(int k=w[j];k<=w[j+1];k++)if(u[i].empty()||u[i].back()!=k)u[i].push_back(k);
		w.clear();
		stk[++tp]=i;
	}
	for(int i=1;i<=m;i++)ord[i]=i;
	sort(ord+1,ord+m+1,[](int x,int y){
		for(auto i=u[x].rbegin(),j=u[y].rbegin();;i++,j++)if(*i!=*j)return *i<*j;
	});
	SZ=m,msz[RT=0]=m,getroot(1,0),solve(RT,1);
	for(int i=1;i<=m;i++)printf("%d ",res[ord[i]]);puts("");
	return 0;
}
```



---

