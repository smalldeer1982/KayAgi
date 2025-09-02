# Gardening Friends

## 题目描述

#### 题意翻译
有一棵有 $n$ 个节点的树，根节点为节点 $1$，每条边的权值为 $k$。现在可以进行挪根操作，每次耗费 $c$ 价值，将树的根转移到与原来根结点相邻的点上。

定义这棵树的价值为根节点到子节点的最远距离 $a$ 与挪根耗费总价值 $b$ 之差（可能不会挪根）。求这棵树经过挪根操作后的最大价值

## 样例 #1

### 输入

```
4
3 2 3
2 1
3 1
5 4 1
2 1
4 2
5 4
3 4
6 5 3
4 1
6 1
2 6
5 1
3 2
10 6 4
1 3
1 9
9 7
7 6
6 4
9 2
2 8
8 5
5 10```

### 输出

```
2
12
17
32```

# 题解

## 作者：SegTree (赞：7)

### 题意

一颗 $n$ 个节点的树，根为 $1$，边的长度为 $k$，将根移动一条边的代价为 $c$。对于节点 $x$，记 $f(x)$ 为 $x$ 为树根时树的深度，$g(x)$ 为将原来的树根移到 $x$ 的代价。求 $\max f(x)-g(x)$。

### 题解
移根代价显然好算，只需要对于每个节点求出以该结点为根时的最深深度。记 $x$ 的父亲为 $y$。下面讨论哪些地方会对 $x$ 的答案造成贡献。

+ 除去以 $y$ 为根的子树，将根移到 $x$ 后的深度（图中红色部分）。

+ $y$ 的非 $x$ 儿子的子树内的深度（图中蓝色部分）。

+ $x$ 为根的子树（图中绿色部分）。

需要求后两者，只需要先对于每个结点求出子树最深深度和儿子结点中的最深和次深的结点编号和深度即可。（记录次深是因为需要考虑 $x$ 恰好是子树最深的结点，此时需考虑次深。）而结点的第一种贡献本质就是父亲的第一种贡献和该结点的第二种贡献合并。于是这道题就做完了，时间和空间复杂度均为 $\mathcal{O}(n)$。

![](https://cdn.luogu.com.cn/upload/image_hosting/lyj19vhb.png)

[提交记录。](https://codeforces.com/contest/1822/submission/214498335)

---

## 作者：bzzltl (赞：7)

提供一种思路不同，码量比较小的代码。

由题目可以想到：

>结点的深度即为挪根次数。

>根结点到子结点的最远距离中的子结点一定是这个根结点的树的直径的两个最长结点之一。

因此这个题目和树的深度和树的直径的两个点有关。

那么，我们很容易就想到用 $3$ 个搜索找根的深度和树直径的两个最长结点，有没有办法只搜索一遍即可得到答案呢？

定义： $max_1$ 为 $u$ 的一个包含子结点 $v_1$ 的最长链中结点的个数，$max_2$ 为 $u$ 的一个包含子结点 $v_2$ 的非严格次长链的长度，$dep$ 为 $u$ 结点的深度。

对于一个结点 $u$，假设最长链的两个端点都在它的子树里面，则此时答案是 $max_1 \times k+\max \left\{ 0,max_2 \times (k-c)-dep \times c \right\}$。


答案可以看作在 $u$ 结点为根的子树中，最长链的长度乘以边的权值，次长链乘以边的权值再减去把根从 $u$ 挪到次长链的底端的花费，这两者之和再减去把根从 $1$ 号结点挪到 $u$ 号结点的花费。

若 $k>c$ 则挪根只要能让根结点到子结点的最远距离增加就可以更新答案，所以直接挪到次大链底端即可。

注意：

1.直接 `define int long long` 会导致 MLE。

2.`ans` 需要在每一个结点都要更新而不是只更新结点 $1$ 就够了，下面这个数据会卡掉只更新结点 $1$ 的。

输入：

```
1
6 4 1
5 1
3 5
4 3
2 5
6 2
```

输出：
```
13
```
![](https://pic.imgdb.cn/item/648cfd8e1ddac507cc621a78.jpg)
	
代码如下：
	
```
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=2e5+6;

inline int read()
{
	int x=0,y=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-') y=-y;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+(c^'0');c=getchar();}
	return x*y;
}

int n,k,c,cnt,head[N];
ll ans;
struct node{
	int v,nex;
}t[N<<1];

void add(int u,int v)
{
	t[++cnt]=(node){v,head[u]};
	head[u]=cnt;
	t[++cnt]=(node){u,head[v]};
	head[v]=cnt;
}

int dfs(int u,int fa,int dep)
{
	int mx1=0,mx2=0;
	for(int i=head[u];i;i=t[i].nex)
	{
		int v=t[i].v;
		if(v==fa) continue;
		int d=dfs(v,u,dep+1)+1;
		if(d>mx1) mx2=mx1,mx1=d;
		else mx2=max(mx2,d);
	}
	ans=max(ans,1ll*mx1*k+max(0ll,1ll*mx2*(k-c)-1ll*dep*c));
	return mx1;
}

void solve()
{
	n=read(),k=read(),c=read();
	ans=0;cnt=0;
	for(int i=1;i<=n;i++)
	{
		head[i]=0;
		t[i].v=0,t[i].nex=0;
		t[i+n].v=0,t[i+n].nex=0;
	}
	for(int i=1;i<n;i++) add(read(),read());
	dfs(1,-1,0);
	printf("%lld\n",ans);
}

signed main()
{
	int T=read();
	while(T--) solve();
	return 0;
}
```

---

## 作者：2c_s (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/CF1822F)

## 思路

可以把本题抽象为类似于求树的直径的问题。

最远距离挪点的耗费就是这棵树的直径（每条边的权值**都是** $1$，直径上的权值和**乘 $k$** 就是挪点的耗费）。

挪根的最大花费是每个节点都挪到每个编号比自己小的节点的位置，再**乘 $c$**。这样挪根的花费是 $1$ 号节点距离当前节点长的之差（可以理解为一种前缀和）。

读入数据后跑**三遍 dfs**（将当前 dfs 的节点记为 $i$）。

- **第一遍**：从根节点 $1$ 开始搜索，找这棵树上最“偏僻”的节点（距离 $1$ **最远**的节点），记为 $A$。在寻找过程中记录每个点距离 $1$ 的长度，记为 ``dis[i]``。

- **第二遍**：从 $A$ 开始搜索，找这棵树上距离 $A$ **最远**的节点，记为 $B$。在寻找过程中记录每个点距离 $A$ 的长度，记为 ``disA[i]``。

- **第三遍**：从 $B$ 开始搜索，找这棵树上所有节点距离 $B$ 的长度，记为 ``disB[i]``。

跑完三遍 dfs 后，从 $1$ 到 $n$ 循环，将当前循环到的节点记为 $i$。每次循环时找 $i$ 到 $A$ **或**（不能挪两次）到 $B$ 的最大值乘 $k$，再减去 $c$ 乘当前节点到根节点的距离差最大的值，记为 ``ans``。最后输出 ``ans`` 即可。

上文的核心代码：``ans=max(ans,max(disA[i],disB[i])*k-c*(dis[i]-dis[1]));``

## 注意事项

- 数据范围可能达到 $2\times10^{14}$，记得开 long long。

- 有多组测试数据，记得清空。

- 可能会访问到第 $n+1$ 个节点，所以要**先 dfs，后清空**（这样下一组就不会访问到上一组测试数据跑完后没清空的节点）。

这里不放代码了，根据上面的思路一步步写即可。

---

## 作者：ShenTianYi_ (赞：4)

~~看了一圈，我的代码内存是最小的，来发篇题解~~

# 第一部分：分析推导

### 题目大意

有一棵有 $n$ 个节点的树，根节点为节点 $1$，每条边的权值为 $k$。现在可以进行挪根操作，每次耗费 $c$ 价值，将树的根转移到与原来根结点相邻的点上。

令 $a$ 为树的深度（根节点深度为 $1$，下同），$b$ 为挪根消耗的价值，则卖出该树可得利润为 $ak-b$。

现在给定一棵树，可以对它进行任意次挪根操作，求可以获得的最大利润。

### 分析推导

首先，我们考虑：每次挪根操作最多只能将树的深度增加 $1$，也就是将树的利润增加 $k$，而挪根的消耗则要增加 $c$。假如 $k \le c$，那么无论怎么挪根，树的利润都不会增加。这个时候，我们就不需要挪根了，直接输出结论即可。

接下来我们考虑 $k > c$ 的情况。如果不考虑挪根消耗的价值，那么最终树的深度肯定就是树的直径的长度。但因为挪根可能会消耗价值，所以我们还需要知道将根节点移到任何一个节点耗费的价值，以及将任何一个节点当作根节点时树的深度。

容易证明，树上任何一个节点到其他所有节点中，距离最长的那个节点一定是树的直径的两个端点之一。

因此，我们需要知道以下三个量：

- 每个点的深度；

- 每个点到树的直径的第一个端点的距离；

- 每个点到树的直径的第二个端点的距离。

现在，这个问题就转变成了：怎么求出树的直径的两个端点？

我们可以先以根节点为起点进行一次 bfs，得到所有节点距离根节点的距离（即结点的深度），根据我们上面得到的结论，深度最大的节点一定是树的直径的两个端点之一，不妨令它为第一个端点；

以刚才搜索到的第一个端点为起点，进行第二次 bfs，得到所有节点距离第一个端点的距离，由树的直径的定义可知，距第一个端点最远的节点就是树的直径的第二个端点，该距离就是树的直径的长度；

以第二个端点为起点，进行第三次 bfs，得到所有节点距离第二个端点的距离。这样，刚才要求的三个量就都求完了。

我们设第 $i$ 个节点的深度是 $d_{1,i}$，到树的直径的第一个端点的距离是 $d_{2,i}$，到树的直径的第二个端点的距离是 $d_{3,i}$。那么，如果以这个节点作为根节点，此时树的深度就是 $\max\{d_{2,i},\:d_{3,i}\}$，将根节点挪到该节点所花费的价值就是 $c\:\times\:d_{1,i}$。因此，此时树的利润就是 $k\:\times\:\max\{d_{2,i},\:d_{3,i}\}\:-\:c\:\times\:d_{1,i}$，而答案就是 $\max\{k\:\times\:\max\{d_{2,i},\:d_{3,i}\}\:-\:c\:\times\:d_{1,i}\}\;(1 \le i \le n)$。

# 第二部分：代码

公式都推导完了，代码就呼之欲出了。有能力的同学们可以自己写，不参考下面的代码。最终的结果记得开 `long long`。

```cpp
#include<bits/stdc++.h>
#define N 200005
using namespace std;
int to[2*N],nxt[2*N];					//链式前向星建图，无向图大小要开两倍
int n,m,k,c,ecnt=0,head[N];
void add_edge(int from,int to_){
	ecnt++;
	to[ecnt]=to_;
	nxt[ecnt]=head[from];
	head[from]=ecnt;
}
void add_double_edge(int a,int b){		//无向图
	add_edge(a,b);
	add_edge(b,a);
}
void check(){
	int x,y,v,w1,w2,w3,dis1=0,dis2=0,dis3=0,d1[N]={},d2[N]={},d3[N]={};
										//d1, d2, d3意义如上；
										//dis1, dis2, dis3分别是d1, d2, d3的最大值
	bool v1[N]={1},v2[N]={1},v3[N]={1};
										//bfs 的 visit 数组不能忘
	cin>>n>>k>>c;
	memset(head,-1,sizeof(head));
	memset(nxt,-1,8*n);					//链式前向星的初始化
	for(int i=1;i<n;i++){
		cin>>x>>y;
		add_double_edge(x,y);
	}
	queue<int>q1,q2,q3;					//三次 bfs
	q1.push(1);
	v1[1]=1;
	while(!q1.empty()){
		int p=q1.front();
		q1.pop();
		for(int i=head[p];i>0;i=nxt[i]){
			if(!v1[to[i]]){
				q1.push(to[i]);
				v1[to[i]]=1;
				d1[to[i]]=d1[p]+1;
			}
		}
	}
	for(int i=2;i<=n;i++){
		if(d1[i]>dis1){
			w1=i;
			dis1=d1[w1];
		}
	}
										//第一次 bfs 结束，d1, dis1 求解完毕
	if(k<=c){
		cout<<1ll*k*dis1<<endl;			//如果 k <= c 直接输出结果
	}
	else{								//继续进行后两次 bfs
		q2.push(w1);
		v2[w1]=1;
		while(!q2.empty()){
			int p=q2.front();
			q2.pop();
			for(int i=head[p];i>0;i=nxt[i]){
				if(!v2[to[i]]){
					q2.push(to[i]);
					v2[to[i]]=1;
					d2[to[i]]=d2[p]+1;
				}
			}
		}
		for(int i=1;i<=n;i++){
			if(d2[i]>dis2){
				w2=i;
				dis2=d2[w2];
			}
		}
										//第二次 bfs 结束，d2, dis2 求解完毕
										//dis2 即为树的直径的长度
		q3.push(w2);
		v3[w2]=1;
		while(!q3.empty()){
			int p=q3.front();
			q3.pop();
			for(int i=head[p];i>0;i=nxt[i]){
				if(!v3[to[i]]){
					q3.push(to[i]);
					v3[to[i]]=1;
					d3[to[i]]=d3[p]+1;
				}
			}
		}
		for(int i=1;i<=n;i++){
			if(d3[i]>dis3){
				w3=i;
				dis3=d3[w3];
			}
		}
										//第三次 bfs 结束，d3, dis3 求解完毕
		long long ans=0;				//ans 记得开 long long
		for(int i=1;i<=n;i++){
			int dis;
			if(d2[i]>d3[i]){
				dis=d2[i];
			}
			else{
				dis=d3[i];
			}							//dis = max{d2[i], d3[i]}
			ans=max(ans,1ll*k*dis-1ll*c*d1[i]);
										//套公式
		}
		cout<<ans<<endl;
	}
}
int main(){								//常规主函数不多说
	int t;
	cin>>t;
	while(t--){
		check();
	}
}
```

---

## 作者：wangkelin123 (赞：0)

这题的题目我就不解释了，~~自己看去~~。关键是题面已经写得够明白了，字数也不能再缩减了。

## 解法
### 1.开数组
关注到 $n\leq2\times10^5$，所以肯定要用 vector 数组动态分配内存（这也是**树**题目常用的类型）。
### 2.清空数组
考虑到输入含有多组数据，所以每次循环开始前要清空一次数组。但 vector 数组只需 $O(n)$ 的时间复杂度就可以了。

方法很多，我知道以下几种（当然建立在循环内）：

`e[i].clear();` `vector v;swap(e[i],v);`或`vector<int>().swap(v[i]);`等等。


输入我就不讲了，直接读入双向边。因为虽然题目中的树是有根树，但题目只说读入一条边，没说谁是孩子谁是父亲。

实际上因为可以挪根，所以**也不需要知道谁是孩子谁是父亲**。
### 3.第一遍 dfs
这一遍 dfs 是为了实现挪根操作。也就是如果以当前节点为根需要挪几次，实际上就是求深度，完毕后用数组存起来，最后用。
### 4.第二、三遍 dfs
这两遍 dfs 当然是为了求最远距离，所以和第一遍用的 dfs 是一样的。

首先找到第一遍 dfs 跑下来的数组中最深的编号。可以循环查找一遍，也可以用函数 max_element。记住，最后要减去数组，这样得到的才会是编号。

接着以最深的节点为根，跑一遍 dfs，先记录一次根到每个节点的距离。但因为这题可以挪根且第一遍 dfs 不一定是最佳答案，所以得再由最深节点为根跑一遍。

最后，将两次的 dfs 答案的每个节点深度取个 max。
### 5.求答案
求答案还得再循环一遍。其实就是价值减去对应的挪根操作的代价的最大值。输出就行了。

总时间复杂度：$O(∑n)=2\times10^5$。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=2e5+5;//n等于 2*10^5 !!!
ll T,n,k,c,dep[N],dis[N],w[N];
vector<int>v[N];
void dfs(int u,int fa){
	for(auto s:v[u]){
		if(s!=fa){
			dep[s]=dep[u]+1;//求长度
			dfs(s,u);
		}
	}
}
int main(){
	cin>>T;
	while(T--){
		cin>>n>>k>>c;
		for(int i=1;i<=n;i++)
			vector<int>().swap(v[i]);
		for(int i=1;i<n;i++){
			int a,b;
			cin>>a>>b;
			v[a].push_back(b);
			v[b].push_back(a);
		}
		dep[1]=0;
		dfs(1,0);
		for(int i=1;i<=n;i++)
			dis[i]=dep[i];
		int x=max_element(dep+1,dep+n+1)-dep;//最大值的位置（减去dep才会得到地址）
		dep[x]=0;
		dfs(x,0);
		for(int i=1;i<=n;i++)w[i]=dep[i];//第一次更新
		int y=max_element(dep+1,dep+n+1)-dep;
		dep[y]=0;
		dfs(y,0);
		for(int i=1;i<=n;i++)w[i]=max(w[i],dep[i]);//第二次更新
		ll ans=0;
		for(int i=1;i<=n;i++)//答案取最大值
			ans=max(ans,k*w[i]-c*dis[i]);
        //三次 dfs 结束！
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：Merge_all (赞：0)

### 思路：
- 这道题其实就是**求树的直径。**
- 直径的性质：
1. **距离任意一个点最远的点一定是直径的一个端点。**
- 所以我们可以用 2 次 dfs 求出直径的两个端点，然后求出每个点到这两个端点的距离，其中一个肯定是最大距离。
- 代价的话我们可以从 1 出发 dfs，**遍历所有点**。
- 定义 $dis$ 是指每个点的最大距离，$ans$ 是最后的答案。
- 答案就是：$\max(ans,dis \times k-c)$。
### 代码：
```
#include <bits/stdc++.h>
using namespace std;

#define int long long

const int N = 200010;
vector<int> v[N];
int T;
int n, k, c;
int d[N], d1[N];
int b[N];
int L, R, ans;

void A(int x, int fa) {
	for (auto i : v[x]) {
		if (i == fa){
			continue;
		}
		b[i] = b[x] + 1;
		A(i, x);
	}
}

void B(int x, int fa) {
	for (auto i : v[x]) {
		if (i == fa){
			continue;
		}
		d[i] = d[x] + 1;
		if (d[i] > d[L]) {
			L = i;
		}
		B(i, x);
	}
}

void C(int x, int fa) {
	for (auto i : v[x]) {
		if (i == fa){
			continue;
		}
		d1[i] = d1[x] + 1;
		if (d1[i] > d1[R]) {
			R = i;
		}
		C(i, x);
	}
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> T;
	while (T--) {
		for (int i = 1; i <= n; i++) {
			v[i].clear();
			d[i] = 0;
		}
		cin >> n >> k >> c;
		for (int i = 1, x, y; i < n; i++) {
			cin >> x >> y;
			v[x].push_back(y);
			v[y].push_back(x);
		}
		b[1] = 0;
		A(1, 0);
		d[1] = 0;
		B(1, 0);
		d1[L] = 0;
		C(L, 0);
		d[R] = 0;
		B(R, 0);
		ans=-0x3f3f3f3f;
		for (int i = 1; i <= n; i++) {
			ans = max(max(d[i], d1[i]) * k - b[i] * c, ans);
		}
		cout << ans << "\n";
	}
}/**/
```

---

## 作者：FireRain (赞：0)

# 思路

发现我们只需要将所有点变为根的答案求出取 $\max$ 即可。

于是我们发现一个深度为 $d$ 的点，它换到根所需的代价是 $dc$。其中 $i$ 的深度表示 $i$ 到根节点所经过的最小边数。

其次，对于一个点为根时最远点是在当前树的形态下，深度最大的节点，于是我们用线段树维护 $d$ 数组即可。（可以发现当根由 $u$ 变为 $v$ 时，所有在 $v$ 子树的节点深度减 $1$，其余节点加 $1$）

# Code

```cpp
#include <bits/stdc++.h>
#define re register
#define int long long

using namespace std;

const int N = 2e5 + 10,M = 4e5 + 10,inf = 1e9 + 10;
int n,k,c;
int num,id[N],pid[N],sz[N],d[N],dp[N];
int idx,h[N],ne[M],e[M];

inline int read(){
    int r = 0,w = 1;
    char c = getchar();
    while (c < '0' || c > '9'){
        if (c == '-') w = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9'){
        r = (r << 3) + (r << 1) + (c ^ 48);
        c = getchar();
    }
    return r * w;
}

struct seg{
    #define ls(u) (u << 1)
    #define rs(u) (u << 1 | 1)

    struct node{
        int l,r;
        int Max,tag;
    }tr[N << 2];

    inline void calc(int u,int k){
        tr[u].Max += k;
        tr[u].tag += k;
    }

    inline void pushup(int u){
        tr[u].Max = max(tr[ls(u)].Max,tr[rs(u)].Max);
    }

    inline void pushdown(int u){
        if (tr[u].tag){
            calc(ls(u),tr[u].tag);
            calc(rs(u),tr[u].tag);
            tr[u].tag = 0;
        }
    }

    inline void build(int u,int l,int r){
        tr[u] = {l,r,-inf,0};
        if (l == r){
            tr[u].Max = d[pid[l]];
            return;
        }
        int mid = l + r >> 1;
        build(ls(u),l,mid);
        build(rs(u),mid + 1,r);
        pushup(u);
    }

    inline void modify(int u,int l,int r,int k){
        if (l <= tr[u].l && tr[u].r <= r){
            calc(u,k);
            return;
        }
        pushdown(u);
        int mid = tr[u].l + tr[u].r >> 1;
        if (l <= mid) modify(ls(u),l,r,k);
        if (r > mid) modify(rs(u),l,r,k);
        pushup(u);
    }

    inline int query(int u,int l,int r){
        if (l <= tr[u].l && tr[u].r <= r) return tr[u].Max;
        pushdown(u);
        int res = -inf;
        int mid = tr[u].l + tr[u].r >> 1;
        if (l <= mid) res = max(res,query(ls(u),l,r));
        if (r > mid) res = max(res,query(rs(u),l,r));
        return res;
    }

    #undef ls
    #undef rs
}T;

inline void add(int a,int b){
    ne[idx] = h[a];
    e[idx] = b;
    h[a] = idx++;
}

inline void calc(int u){
    dp[u] = k * (T.query(1,1,n) - 1) - (d[u] - 1) * c;
}

inline void dfs1(int u,int fa){
    num++;
    sz[u] = 1;
    id[u] = num;
    pid[num] = u;
    d[u] = d[fa] + 1;
    for (re int i = h[u];~i;i = ne[i]){
        int j = e[i];
        if (j == fa) continue;
        dfs1(j,u);
        sz[u] += sz[j];
    }
}

inline void dfs2(int u,int fa){
    calc(u);
    for (re int i = h[u];~i;i = ne[i]){
        int j = e[i];
        if (j == fa) continue;
        T.modify(1,1,n,1);
        T.modify(1,id[j],id[j] + sz[j] - 1,-2);
        dfs2(j,u);
        T.modify(1,1,n,-1);
        T.modify(1,id[j],id[j] + sz[j] - 1,2);
    }
}

inline void solve(){
    int ans = -inf;
    idx = num = 0;
    n = read();
    k = read();
    c = read();
    for (re int i = 1;i <= n;i++) h[i] = -1;
    for (re int i = 1;i < n;i++){
        int a,b;
        a = read();
        b = read();
        add(a,b);
        add(b,a);
    }
    dfs1(1,0);
    T.build(1,1,n);
    dfs2(1,0);
    for (re int i = 1;i <= n;i++) ans = max(ans,dp[i]);
    printf("%lld\n",ans);
}

signed main(){
    int T;
    T = read();
    while (T--) solve();
    return 0;
}
```

---

## 作者：Shimotsuki (赞：0)

首先挪根代价非常好算，设 $dep_i$ 为以 $1$ 为根的树（即操作前的原树）中点 $i$ 的深度（初始化 $dep_1=0$），因为挪根是往当前根的相邻节点挪的，所以根节点挪到 $i$ 的最小挪根代价是 $dep_i \times c$。

接下来考虑求出原树中深度最深的节点 $x$，设 $V$ 为根节点 $1$ 到 点 $x$ 经过的链上除点 $1$ 之外的点的集合，可以发现挪根到点 $i(i \notin V)$ 形成的树中深度最深的点也是点 $x$。证明：当以点 $i(i \notin V)$ 为根时，$V$ 中的所有点全部深度增大，并且与其他深度会增大的点的增大值相同，而点 $x$ 在原树中深度最大，所以得证；当以点 $i(i \in V)$ 为根时，设 $dis(u,v)$ 为点 $u$ 到点 $v$ 的距离（$1 \le u,v \le n$），则 $dis(i,x) \le dis(1,x)$，且挪根代价增大，所以不符合该结论。

而以点 $i(i \in V)$ 为根时，可以考虑把根从点 $1$ 移到原树深度为 $dep_i$ 的点 $j(j \notin V)$，设 $y$ 为以根为点 $i$ 的树中的深度最深的点 $y$，可从树上前缀和的性质得 $dis(i,y) \le dis(j,x)$，且挪根代价相等，故无需考虑把根移动到点 $i$。

最后枚举所有以点 $i(i \notin V)$ 的树的代价，即 $dis(i,x)-dep_i \times c$，取最大值即为答案。时间复杂度 $O(n \log n)$。

注意多测清空。

---

