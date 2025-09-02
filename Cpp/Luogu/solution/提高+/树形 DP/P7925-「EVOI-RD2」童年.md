# 「EVOI-RD2」童年

## 题目背景

池塘边的榕树上 知了在声声地叫着夏天  
操场边的秋千上 只有蝴蝶儿停在上面  
黑板上老师的粉笔还在拼命叽叽喳喳写个不停  
等待着下课 等待着放学  
等待游戏的童年



## 题目描述

Charlie 童年时代很喜欢爬树。

有一天，Charlie 准备向一棵高大的苹果树发起挑战。这棵苹果树有 $n$ 个结点，其中结点 $1$ 为树根。

每个结点会有若干个苹果或一个鸟巢。若这个结点上是若干个苹果，则 Charlie 会摘下所有的苹果装入自己的口袋中；若这个结点是鸟巢**且 Charlie 是第一次访问它**，则 Charlie 会给这个鸟巢中的每只鸟儿一个苹果~~不要问鸟儿为什么喜欢苹果~~。

特别地，如果 Charlie 当前口袋中的苹果不足以给该结点的每只鸟儿一个，则他就不会走向这个结点。注意 Charlie 重复经过一个结点时，不会重复采摘苹果，也不会重复给出苹果。

一开始，Charlie 口袋中有 $s$ 个苹果。Charlie 将从树根开始爬树，每次经过一条边到达一个结点，并执行对应的操作（摘苹果或给苹果，根结点的操作也要执行）。Charlie 希望最终拥有的苹果数最多。由于 Charlie 还在忙着爬其他的树，他想请你写个程序帮帮他。

## 说明/提示

**样例 1 解释：**

可以摘走所有苹果。

**样例 2 解释：**

只能摘走结点 $1,3$ 的苹果，结点 $2$ 因为鸟儿太多无法访问。

**样例 3 解释：**  

![样例3解释](https://cdn.luogu.com.cn/upload/image_hosting/hj7eoes3.png)

结点 $1$ 给掉 $2$ 个苹果，先摘完结点 $3,6,7$ 的苹果，此时口袋中有 $6$ 个苹果。再闯过结点 $2$，然后拿走结点 $5$ 的苹果，结点 $4$ 由于鸟儿太多没必要走。

一种最优的具体路径：$1 \rightarrow 3 \rightarrow 6 \rightarrow 3 \rightarrow 7  \rightarrow 3 \rightarrow 1 \rightarrow 2 \rightarrow 5 \rightarrow 2 \rightarrow 1$。

**数据规模与约定**

**本题采用捆绑测试。**

+ Subtask 1 (10 pts)：$\, n \leq 10$。   
+ Subtask 2 (20 pts)：$\, n \leq 100$ 。  
+ Subtask 3 (10 pts)：$\, p_i=1$。  
+ Subtask 4 (30 pts)：$\, p_i=i-1$。  
+ Subtask 5 (30 pts)：无特殊限制。

对于 $100\%$ 的数据，$1 \leq n \leq 6000, 1 \leq p_i \lt i, |a_i| \leq 10^9,0 \leq s \leq 10^9$。

---

“记得门前，有两株树，一株是苹果树，还有一株……也是苹果树。”

## 样例 #1

### 输入

```
5 0
1 1 2 2
1 1 1 1 1```

### 输出

```
5```

## 样例 #2

### 输入

```
5 0
1 1 2 2
1 -3 1 2 2```

### 输出

```
2```

## 样例 #3

### 输入

```
8 5
1 1 2 2 3 3 4
-2 -6 1 -7 8 1 1 6```

### 输出

```
8```

# 题解

## 作者：bluewindde (赞：9)

upd 2023.8.1：修改了题解的表述错误。

## 解法

首先，用一个正常人的思维，我们只应该在**能赚**的前提下进入一颗子树，所以需要先预处理出进入以节点 $i$ 为根节点的子树的进入的需求 $need_i$。然后再用 bfs 统计答案。

### 预处理

那么应该怎么处理子树的进入需求呢？

我们可以使用 dfs，在回溯时处理需求。这里有两种情况：

- 节点 $u$ 不是鸟巢，即 $a_u\ge0$，此时不需要进入需求，$need_u=0$。
- 节点 $u$ 是鸟巢，即 $a_u<0$。  
此时把节点 $u$ 的子节点加入优先队列，记录当前总的收入 $tot$。  
每次循环取出优先队列中 $need_v$ 最小的节点 $v$。  
若 $tot-need_u\ge0$，意味着搜索到可以赚的点，此时退出循环；  
若 $tot<need_v$，意味着当前的收入不足以进入节点 $v$，则使 $tot\gets need_v$。  
在循环结束时，将 $tot$ 加上节点 $v$ 的权值 $a_v$，并把节点 $v$ 的所有子节点加入优先队列。  
退出循环后，**一定要再判断一次**是否满足 $tot-need_u\ge0$。如果没有搜索到可以赚的点，意味着无论如何都会亏，所以不走这棵子树，将 $need_u\gets\inf$。

### 统计答案

用 bfs 统计，先向优先队列内推入根节点，令 $ans\gets s$，每次取出优先队列中 $need_v$ 最小的节点 $v$。若 $ans<need_v$，则退出循环。否则将 $ans$ 加上 $a_v$，并把 $v$ 的子节点推入优先队列。

更多的内容可以看代码注释。

## AC 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

struct node {
	int need,index;
	inline node(int n,int i):need(n),index(i) {}
	inline bool operator<(const node &b) const { // 重载比较函数 记得加 const
		return need>b.need;
	}
};
priority_queue<node> to_vis;

int n,s;
int fa[6005],a[6005],need[6005];
vector<int> child[6005];

inline void clear() {
	while(!to_vis.empty()) {
		to_vis.pop();
	}
}

inline void dfs(int u) {
	clear();
	for(auto i:child[u]) { // 优先处理子节点
		dfs(i);
	}
	if(a[u]>=0) { // 没有鸟巢，所以进入条件为0
		need[u]=0;
		return ;
	}
	clear();
	for(auto i:child[u]) {
		to_vis.push(node(need[i],i));
	}
	need[u]-=a[u]; // 要给这个节点上的鸟的苹果的数量
	bool flag=false;
	int tot=0;
	while(!to_vis.empty()) {
		if(tot-need[u]>=0) { // 搜索到可以赚的点，退出
			flag=true;
			break;
		}
		node x=to_vis.top();
		to_vis.pop();
		if(tot<need[x.index]) {
			need[u]+=need[x.index]-tot; // 排除这个点，继续尝试
			tot=need[x.index];
		}
		tot+=a[x.index]; // 向子树加入新的点
		for(auto i:child[x.index]) { // 并且把这个点的子节点加进队列
			to_vis.push(node(need[i],i));
		}
	}
	if(tot-need[u]>=0) { // 搜索到可以赚的点，退出
		flag=true;
	}
	if(!flag) {
		need[u]=1e18; // 无论如何都会亏，所以不走这棵子树
	}
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>s;
	for(int i=2;i<=n;++i) {
		cin>>fa[i];
		child[fa[i]].push_back(i);
	}
	for(int i=1;i<=n;++i) {
		cin>>a[i];
	}
	dfs(1);
	clear();
	to_vis.push(node(need[1],1));
	int ans=s;
	while(!to_vis.empty()) {
		node x=to_vis.top();
		to_vis.pop();
		if(ans<need[x.index]) { // 没有达到任何一棵子树可以进入的要求，退出
			break;
		}
		ans+=a[x.index];
		for(auto v:child[x.index]) {
			to_vis.push(node(need[v],v));
		}
	}
	cout<<ans;
	return 0;
}


```

## 注意事项

如果用 `auto` 关键字遍历列表，一定要记得选 `-std=c++14` 或者更高。

[优先队列](https://learn.microsoft.com/zh-cn/cpp/standard-library/priority-queue-class?view=msvc-170)不能用 `clear` 方法清空，需要手写循环来清空。

开 `long long`！！！

---

## 作者：冷月葬T魂 (赞：8)

首先定下一个目标：如果我们预处理出对于每个结点，**至少**要带着多少个苹果进入它的子树，才能够赚到若干个苹果之后再出来，就直接从根结点开始，每次把所有有得赚的结点放进一个优先队列中，进行一次 bfs 即可。由于每次我们都能够赚到，因此我们的苹果数就会越来越多，于是之前能进去的结点，现在也能进得去（“进得去”的含义是进去之后在出来之前能够赚到）。一直到任何一个子树都赚不到为止即可。那么现在问题就变成了如何求出进入一个子树所需的苹果数，设为 $f_u$。  

插一句，为什么要能够赚得到才进入一棵子树呢？因为要是你进去了什么也没赚到，反而亏了，那么原来去不了的地方，现在还是去不了；反而有可能原来能去的地方，现在也去不了了。换句话说，现在去得了的地方，现在就去呗，先吃了亏再去干嘛？你想去，等把能赚的都赚完了再去好吧。那时候，能去得了就去，去不了就罢了。  

接下来求 $f_u$。用同样的思路，$f_u$ 置为 $0$，并维护一个变量 $cur$，代表当前拥有的苹果数。开一个优先队列，一开始塞入 $u$ 的所有子结点。每次取出一个 $f$ 值最小的结点 $v$，看看是否有 $f_u \geq f_v$，若是，则进去 $v$，并更新 $cur$；若不然，则令 $cur \leftarrow f_v$，这样就意味着一开始要多拿 $f_v-f_u$ 个苹果，因此再令 $f_u \leftarrow f_u+(f_v-cur)$。当 $cur>f_u$ 时就意味着现在的苹果数多于拿进来的苹果数，可以停止了，此时 $f_u$ 即为所求。若 $cur$ 始终小于 $f_u$，说明怎么搞都赚不到，那么 $f_u=inf$。  

代码如下：  

```cpp
#include <bits/stdc++.h>
#define For(i,a,b) for(int i=a;i<=b;i++)
#define Rev(i,a,b) for(int i=a;i>=b;i--)
#define clr(a,v) memset(a,v,sizeof(a))
#define int long long
using namespace std;

const int N=1e4+5,INF=1e16;

struct cpdd{
	int pos,need;
	bool operator< (const cpdd& cp) const
	{
		return need>cp.need;
	}
};

int n,a[N],fa[N];
vector<int> son[N];

int f[N];

priority_queue<cpdd> q;

void dp(int u)
{
	int sz=son[u].size();
	
	For(i,0,sz-1){
		int v=son[u][i];
		dp(v);
	}
	
	if(a[u]>=0){
		f[u]=0;
		return;
	}
	
	while(q.size()) q.pop();
	
	For(i,0,sz-1){
		int v=son[u][i];
		q.push((cpdd){v,f[v]});
	}
	
	f[u]=-a[u];
	
	int cur=0,ok=0;
	
	while(q.size()){
		if(cur-f[u]>=0){
			ok=1;
			break;
		}
		
		int v=q.top().pos; q.pop();
		
		if(cur<f[v]){
			f[u]+=f[v]-cur;
			cur=f[v];
		}
		
		cur+=a[v];
		assert(cur>=0);
		
		int szv=son[v].size();
		For(i,0,szv-1){
			int w=son[v][i];
			q.push((cpdd){w,f[w]});
		}
	}
	
	if(cur-f[u]>=0) ok=1;
	
	if(!ok) f[u]=INF;
}

signed main()
{
	int s;
	cin>>n>>s;
	
	For(i,2,n){
		cin>>fa[i];
		son[fa[i]].push_back(i);
	}
	
	For(i,1,n) cin>>a[i];
	
	dp(1);
	
	while(q.size()) q.pop();
	
	q.push((cpdd){1,f[1]});
	
	int ans=s;
	
	while(q.size()){
		int u=q.top().pos; q.pop();
		
		if(ans<f[u]) break;
		
		ans+=a[u];
		
		int sz=son[u].size();
		
		For(i,0,sz-1){
			int v=son[u][i];
			q.push((cpdd){v,f[v]});
		}
	}
	
	cout<<ans<<endl;
	
	return 0;
}

/*
20 76
1 1 1 3 5 2 4 3 1 3 9 7 1 11 7 1 17 16 18 
43 -91 -38 -22 26 98 -84 73 77 1 47 62 -12 76 12 42 59 -11 100 23 
*/

/*
30 98
1 2 2 2 3 4 7 5 5 9 6 7 3 11 12 8 3 15 1 8 2 9 22 15 17 11 7 11 5
-1 -45 -69 -92 80 3 -35 71 91 30 -83 -31 -80 5 47 70 -78 -40 79 -74 -24 -83 94 -69 54 20 -66 46 -25 2
*/

/*
10 29
1 1 1 3 4 1 5 8 8 
70 61 -23 -4 -13 6 89 -75 84 -98 
*/
```

---

## 作者：shanxinhan (赞：4)

## 前言

本篇题解主要做一些求**进入子树需求**部分的详细解释，可作为其它题解的补充说明。

相比之下，我认为在求出进入子树需求后用 bfs 统计答案个过程更加简单，而这两个过程的思路求法其实差不多，所以建议先看怎么统计答案，再看怎么求进入子树需求。

## 做法

我们使用 dfs，假设当前遍历到结点 $u$，现在在回溯阶段（即已遍历完 $u$ 的所有儿子），记 $u$ 的进入子树需求为 $f_u$。

这个 dfs 的大体思路是这样的：如果 $a_u \ge 0$，也就是这个结点上有苹果或什么都没有，那么直接将 $f_u$ 设为 $0$，退出。

否则，先将 $f_u$ 设为 $-a_u$，因为不管你能在儿子的地方赚到多少苹果，你都必须先有 $-a_u$ 个苹果才能进入这颗以 $u$ 为根的子树。再设一个变量 $sum$ 表示我们当前赚到的苹果，只要在任意时刻 $sum \ge f_u$，那么我们进入 $u$ 的行为就一定不亏。

然后，我们就要想办法进入部分儿子结点来赚取苹果，这样才能填补进入 $u$ 所消耗掉的苹果，以做到不亏。

我们将 $u$ 的所有儿子 $v$ 放入**以 $f_v$ 为关键字从小到大排序的的优先队列** $q$，取出需求最小的儿子（即队首），准备进入 $v$。

**重点来了！！！敲黑板**

进入 $v$ 是要有代价的，如果 $f_v > sum$，也就是大于之前进入其它儿子得到的苹果，那前面所有的苹果都要用在这里而且还不够用，我们还需要把 $f_u$ 加上 $f_v-sum$，也就是赔进所有苹果还要补的苹果，再把 $sum$ 设为 $f_v$，因为我们把进入 $u$ 所需的苹果提高了 $f_v-sum$，也就是初始拥有的苹果多了 $f_v-sum$，所以相应地，$sum$ 也加上 $f_v-sum$，也就是赋值成了 $f_v$。

注意这只是在给准备进入 $v$ 制造好条件，因为如果不经过上面的操作就无法合法进入 $v$。

这个有同学就会疑惑了，既然进入这个 $v$ 得不到还要贴进去苹果，我还要进入 $v$ 干嘛？解答就是只要 $f_v \ne +\infty$（$+\infty$ 就是进入该结点无论如何都得不到苹果，下文会讲到），那么我们肯定是会在以 $v$ 为根的子树中得到苹果的，所以现在的亏损只是暂时的亏损而已，优先进入它一定是正确的（因为进入其它儿子需要更多的苹果啊）。

进入 $v$ 之后就很简单了，讲 $sum$ 加上 $a_v$，也就是加上该结点的苹果或减去该结点所需的苹果。判断此时得到的苹果 $sum$ 和 $f_u$，如果 $sum \ge f_u$，那无论怎么样，进入 $f_u$一定是不亏的，我们的目的达到，直接停止本次操作。

要是遍历完所有 $u$ 的子孙，还是不能使 $sum \ge f_u$，也就是得到苹果，~~那么说明它无药可救了~~，把 $f_u$ 设为 $+\infty$，表示不可进入，停止操作。

## 部分代码

```cpp
struct node{
	int id;
	long long f;
	bool operator<(const node &b)const{
		return f>b.f;
	}
};
void dfs(int u){
	for(int v:g[u])
		dfs(v);
	if(a[u]>=0){
		f[u]=0;
		return;
	}
	priority_queue<node>q;
	for(int v:g[u])
		q.push((node){v,f[v]});
	long long sum=0;
	f[u]=-a[u];
	while(!q.empty()){
		node s=q.top();
		q.pop();
		int v=s.id;
		if(f[v]>sum){
			f[u]+=f[v]-sum;
			sum=f[v];
		}
		sum+=a[v];
		if(sum>=f[u]){
			return;
		}
		for(int son:g[v])
			q.push((node){son,f[son]});
	}
	f[u]=inf;
}
```

---

## 作者：xiezheyuan (赞：3)

## 思路

首先本题有一个强化版 P10759。那道题 $O(n^2)$ 是不可以做的。因此我们在这里讨论一下如何改进这道题现有的解法。

我们在这里简要说一下本题的做法。对于每一个点 $i$，引入一个估价函数 $f(i)$ 表示要想在以 $i$ 为根的子树中获益，则进入子树前至少需要有的钱 / 苹果。

以下的叙述中，我们用钱代指赚到的苹果，这样做主要是因为关于钱的词多一点，方便叙述做法。

假如我们已经求得了 $f(i)$，那么就好做了。从根节点开始，将子节点丢进一个小根堆中。每次取出 $f(i)$ 最小的，那么这个点可以去完成的。于是我们就加上这个点的贡献，并且将这个点的儿子全部踹进堆中。

所以问题是如何求出 $f(i)$？一个朴素的想法是，我们维护一个堆，将子节点塞到堆中，每次还是走 $f(i)$ 最小的，如果我们获益了（当前钱数大于投入钱数），也就是当前的钱数已经可以满足需求了，那么我们就可以走人了（满足了求 $f(i)$ 的条件），如果这个点的 $f$ 比现在投入钱数大，那么我们就需要抬高投入钱数。

容易发现这个做法是 $O(n^2\log n)$ 的。难以通过加强版。

为了优化，我们将求 $f(i)$ 的过程称为对 $i$ 的扩展，将最终扩展到的点集称为边界弧。为什么叫边界弧呢，因为弧上面均被扩展，下面均未被扩展，并且长得像弧（bushi）。

然后每一次扩展的时候，都求了一遍它的子树中某一个点的这个边界弧，十分浪费。于是一个直观的想法就是将边界弧存起来。

还是沿用以前的思路，将边界弧用堆存起来。然后考虑拓展的时候不再重复遍历子树了，而是转而直接使用原本边界弧方式。这一部分需要可并堆。我比较懒，所以就用 pbds 了。

但是这样子，我们很难求出当前的钱数了。这个时候，我们再引入一个 $g(i)$ 表示第 $i$ 个点我们拓展到边界弧可以赚的钱数。那么合并堆的时候，需要加上这一部分的贡献，同时我们在走人之前也需要更新这个 $g(i)$。

合并堆用启发式合并的方法，复杂度就变成了 $O(n\log^2 n)$。可以通过本题。

## 代码

```cpp
#include <bits/stdc++.h>
#include <bits/extc++.h>
#define int long long
using namespace std;

const int N = 3e5 + 5;
int n, s;

struct edge{
    int nxt, to;
} g[N << 1];
int head[N], ec, p[N];
__int128 f[N], got[N];

void add(int u, int v){
    g[++ec].nxt = head[u];
    g[ec].to = v;
    head[u] = ec;
}

struct cmp{
    bool operator()(const int &x, const int &y) const {
        return f[x] > f[y];
    }
};

using heap = __gnu_pbds::priority_queue<int, cmp, __gnu_pbds::pairing_heap_tag>;
heap hp[N];

void ytxy(int u){// 拓展 u 节点
    hp[u].push(u);
    int now = 0;
    while(!hp[u].empty()){
        int v = hp[u].top();
        hp[u].pop();
        if(now < f[v]) {
            f[u] += f[v] - now;
            now = f[v];
        }
        if(v == u) {
            now += p[v];
            for(int i=head[v];i;i=g[i].nxt){
                int to = g[i].to;
                hp[u].push(to);
            }
        } else {
            now += got[v];
            if(hp[u].size() < hp[v].size()) hp[u].swap(hp[v]);
            if(u != v) hp[u].join(hp[v]);
        }
        if(now > f[u]) {
            got[u] = now - f[u];
            return;
        }

    }
    f[u] = LLONG_MAX;
}

void dfs(int u, int fa){
    for(int i=head[u];i;i=g[i].nxt){
        int v = g[i].to;
        if(v == fa) continue;
        dfs(v, u);
    }
    ytxy(u);
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin >> n >> s;
    for(int i=2,u;i<=n;i++){
        cin >> u;
        add(u, i);
    }
    for(int i=1;i<=n;i++) cin >> p[i];
    dfs(1, 0);
    // for(int i=1;i<=(n + 1);i++) cout << (i - 1) << ' ' << f[i] << '\n';
    heap q;
    __int128 now = s;
    q.push(1);
    while(!q.empty()){
        int u = q.top();
        q.pop();
        if(now < f[u]) break;
        now += p[u];
        // cout << (u - 1) << ' ' << now << '\n';
        for(int i=head[u];i;i=g[i].nxt){
            int v = g[i].to;
            q.push(v);
        }
    }
    cout << (long long)(now);
    return 0;
}

// Written by xiezheyuan
```

---

## 作者：A_man (赞：3)

大致学习了下其他人的题解，~~并没有看懂~~。

所以为了方便理解，我写了一篇稍微详细点的，~~可能有些啰嗦~~，如有错误欢迎指出。

### 大体思路

首先根据题意，每一个苹果节点一定对答案有贡献，而每个鸟巢一定对答案有负贡献，所以最优方案肯定是**只选择苹果节点**。

但是在一棵树中，我们在选择某些苹果节点前可能要**先经过某些鸟巢**，然后才能走到苹果节点。

这时我们不难想到贪心，当且仅当**选择这些苹果的贡献大于经过其必须经过鸟巢的负贡献**时，我们才会去选这些苹果。

然后在树上来考虑这个问题，对于每个鸟巢，如果进入其子树能够使得我们总的苹果数量增加，我们就进入其子树。

对于这个问题，我们只需要从遍历一遍整棵树，然后在回溯的时候贪心算一遍就可以了。（就是在回溯的时候只取贡献为正的子树）

但在此之前，我们还要保证我们**有足够的苹果来进入这些鸟巢的子树**，这就给我们的贪心增加了一条限制。

在增加了这一限制后，我们原本的贪心策略不变。在此基础上，我们优先考虑需求小的鸟巢。

这一点其实并不难想，（在所有可到达的点中）我们肯定要先通过**需求小的鸟巢**（或者是需求为 $0$ 的苹果节点）增加自己的苹果数量，然后再考虑选择需求大的鸟巢。（当然以上都是在保证**鸟巢与其子树贡献和为正**的前提下）

那么接下来问题就可以分成两步：

+ 求进入每个节点的最少苹果需求量（前提保证贡献为正）。

+ 求能得到的最多苹果数量。

然后我们来分别考虑这两步的具体思路。

### 求进入每个节点的最少苹果需求量

首先我们令 $f_x$ 表示所求的进入每个节点的最少苹果需求量。

考虑在回溯时转移，进入一个节点的最少苹果的需求量应当由其儿子转移而来，然而具体转移比较麻烦，我们一点点来说。

无论如何，我们首先要保证贡献为正，所以我们套用上文中**求能得到的最多苹果数量**时所用到的贪心策略，先考虑其子树中所有可达的点（开始是其所有儿子），选择其中**需求最小的点**来更新其贡献，然后再将我们选择的点的儿子标记为可达的点，这样一直循环下去，不断更新我们的 $f_x$，直到我们的贡献为正为止。

那么，不妨设我们走到这个点时苹果数量为 $0$，我们若想要进入这棵子树，必然要先亏损一些苹果，在保证总贡献为正的前提下我们亏损苹果的最小值就是 $f_x$。

只有在我们获得的苹果数量大于当前亏损的量（即大于 $f_x$）时，子树的总贡献才为正，此时的 $f_x$ 就是最小需求量。

#### 具体一点的实现思路

每个苹果节点的需求为 $0$。

对于每个鸟巢节点，用一个优先队列存下所有可以到达的子节点。同时，我们用 $num$ 来表示当前我们拥有的苹果数量（初始化为 $0$）。

+ 每次取出收益最小的子节点，并尝试进入这个子节点。若我们当前拥有的节点数量不足，则更新 $f_x$，令其增加不足的部分，并将当前拥有的苹果数，使其能够进入子节点。

具体地，$f_x=f_x+(f_y-num)$，然后令 $num=f_y$。

+ 进入这个子节点后，我们加上子节点的收益，同时令其子节点的儿子入队。

+ 重复上两步操作，直到收益为正（$num>f_x$）为止。

若收益始终不为正，则该节点没有进入的必要，将其需求设置为正无穷（即不会进入）。

~~可能完全没有必要的解释：~~

为什么子节点的儿子要入队：因为我们并不知道一个子节点具体的收益，这会影响我们对其他子节点的选择，所以需要不停地按照能赚则赚的原则遍历每一个能赚的节点。

### 求能得到的最多苹果数量

实际上呢，这部分和上面求需求的核心思路是一样的，所以直接讲步骤：

（仍然是拿优先队列维护需求最小的节点）

+ 从根节点开始，每次取出需求最小的节点，加上其贡献，并将其儿子入队。

+ 不停循环上面的步骤，直到**当前的苹果数量小于最小的需求**时退出。

（本质上就是重复了一遍前面求解最大贡献的部分）

### 代码实现

```cpp
//个人原因所以代码比较长
#include <bits/stdc++.h>
using namespace std;
const long long INF=1e18+1;
const int M=2e4+10;
const int N=6e3+10;
int n;
int head[N],ver[M],Next[M],tot=-1;
long long a[N],f[N],s;
int read()
{
	int x=0,f=1; char ch=getchar();
	while(ch>'9'||ch<'0'){if((ch^45)==0){f=-1;} ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48); ch=getchar();}
	return x*f;
}
void write(long long x)
{
    if(!x){putchar('0'); putchar('\n'); return;} 
    if(x<0){x=-x; putchar('-');}
    short len=0,c[40];
    while(x!=0){c[++len]=(x%10)^48; x/=10;}
    while(len!=0) putchar(c[len--]);
	putchar('\n');
}
void add(int x,int y)
{
	ver[++tot]=y;
	Next[tot]=head[x];
	head[x]=tot;
}
void dfs(int x)
{
	for(int i=head[x];i!=-1;i=Next[i])
	{
		int y=ver[i];
		dfs(y);
	}
	if(a[x]>0) //苹果节点需求为0 
	{
		f[x]=0;
		return ;
	}
	priority_queue<pair<long long,int> > Q; //优先队列默认大根堆 
	for(int i=head[x];i!=-1;i=Next[i])
	{
		int y=ver[i];
		Q.push(make_pair(-f[y],y)); 
	}
	long long num=0;
	bool flag=0;
	f[x]-=a[x]; //当前节点的初始需求 
	while(!Q.empty())
	{
		long long cost=-Q.top().first; 
		int u=Q.top().second;
		
		Q.pop(); //每次取出存在收益的情况下需求最小的子节点 
		if(num<cost) //当前所持有的苹果比需求最小的儿子的苹果还少 
		{
			f[x]+=(cost-num); //此时需要修改节点x的最小需求 差多少补多少
			num=cost; //同时我们持有的苹果数变为进入这一节点的最低苹果数要求 
		}
		//然后我们接下来加入这个节点的收益
		num+=a[u];
		for(int i=head[u];i!=-1;i=Next[i])
		{
			int y=ver[i];
			Q.push(make_pair(-f[y],y));
		}
		if(num>f[x]) //最后 如果持有大于需求 则说明该节点此时存在收益 
		{
			flag=1;
			break;
		}  
	}
	if(flag==0) //无收益则无视该点 
	{
		f[x]=INF;
	}
	while(!Q.empty()) Q.pop();
}
void bfs(int x)
{
	priority_queue<pair<long long,int> > Q;
	Q.push(make_pair(-f[x],x));
	while(!Q.empty())
	{
		long long cost=-Q.top().first;
		int u=Q.top().second;
		Q.pop();
		if(s<cost) break; //如果连需求最小的点都进不去就不用走了 
		s+=a[u]; //正常统计收益就好了 
		for(int i=head[u];i!=-1;i=Next[i])
		{
			int y=ver[i];
			Q.push(make_pair(-f[y],y));
		}
	}
	write(s);
}
int main()
{
	memset(head,-1,sizeof(head));
	n=read(); s=(long long)read();
	for(int i=2;i<=n;++i)
	{
		int x=read();
		add(x,i); //按照题意建单向边就行 
	}
	for(int i=1;i<=n;++i)
	{
		a[i]=read();
	}
	dfs(1); //求需求 
	bfs(1); //求答案 
	return 0;
}
```

码字不易，不喜勿喷。有问题欢迎指出探讨交流。

---

## 作者：Exp10re (赞：2)

笑点解析：这一篇复杂度 $O(n^2\log n)$ 做法的题解可以通过 $n\leq 3\times 10^5$ 的 [P10759 [BalticOI 2024] Jobs](https://www.luogu.com.cn/problem/P10759)。

因为那一题数据太水，这个又算是假做法，所以题解投在这一道题了。

以下是模拟赛赛时思路。

## 解题思路

考虑树上动态规划，维护 $f_i$ 表示你当前至少需要有 $f_i$ 个苹果才能在以该点为根的子树中得到更多苹果。如果进入该子树一定会亏苹果，则记 $f_i=+\infty$。

首先我们考虑一下在所有 $f_i$ 都被计算出来的情况下如何得到答案：

- 记录当前苹果数量。
- 将根节点加入可选集中。
- 每一次从可选集中找一个 $f$ 值最小的点，记为 $x$。
- 将当前苹果数量加上 $a_x$，将 $x$ 的所有孩子加入可选集中，并从可选集中删除 $x$。
- 重复步骤三到四，直到 $f$ 值最小的点的 $f$ 值大于当前苹果数量，当前苹果数量即为答案。

考虑以上做法的正确性：由 $f$ 的定义可知：若当前苹果数量小于等于 $f_x$ 进入 $x$ 节点一定可以带来正收益，否则一定不能带来正收益。

如果当前所有可达节点都不能带来正收益，那么走这个节点一定是亏的。

由此可以得知：走到一个 $f$ 较小的节点一定不劣于走到一个 $f$ 较大的节点。

以上可以用堆维护，时间复杂度 $O(n\log n)$。

计算答案的部分讲完，接下来考虑如何维护 $f$。

考虑使用类似于计算答案的做法维护 $f_i$。具体的：

- 将 $f_i$ 的所有孩子加入可选集中。记当前苹果亏损量为 $-a_i$。
- 每一次从可选集中找一个 $f$ 值最小的点，记为 $x$。
- 将当前亏损减去 $a_x$，将 $x$ 的所有孩子加入可选集中，并从可选集中删除 $x$。
- 记录操作过程中的最大亏损。
- 重复步骤二到四，直到 $f$ 值最小的点的 $f$ 值为 $+\infty$（即进入可选集中的点均没有收益），或者亏损为负（即得到了收益）。
- $f_i$ 即为最大亏损。

正确性证明与得到答案的证明类似，不多赘述。

每个点维护 $f$ 的时间复杂度都为 $O(n\log n)$，总时间复杂度 $O(n^2\log n)$，可以通过。

---

## 作者：wxzzzz (赞：1)

题解区首篇 $O(n\log n)$ 最优解做法。

### 思路

令 $f_x$ 表示 $x$ 子树的最大子树和（可以为 $0$，最大和子树必须以 $x$ 为根），$g_x$ 表示走完 $x$ 的最大和子树至少在进入 $x$ 前有多大的值。

对于 $x$，先将其所有子树处理完，然后将子节点按 $g_y$ 排序。

这里的排序将钦定走 $x$ 各个子树的顺序，$g_y$ 最小的肯定先走，因为如果它走不了那么 $g_y$ 更大的也走不了，而走完最小 $g_y$ 答案单增，对走后面的子树不劣。

按排序后的顺序枚举子节点 $y_i$，当前的 $f_x$ 表示了 $\operatorname{T}(y_{1\sim i-1})\cup x$ 的最大子树和（$\operatorname{T}(x)$ 表示 $x$ 的子树），分类讨论：

1. $g_y\le f_x$

   此时可以在走完 $\operatorname{T}(y_{1\sim i-1})\cup x$ 后直接走 $y_i$，不用更新 $g_x$。

1. $g_y>f_x$
  
    此时在走完 $\operatorname{T}(y_{1\sim i-1})\cup x$ 后还需增加 $g_y-f_x$ 的值才能走 $y_i$，这个值仅能从进入 $x$ 之前加上，故有 $g_x\gets\max(g_x,g_y-f_x)$。

预处理完 $f,g$ 就从根开始模拟走的过程。

假设当前走到了 $x$，$ans$ 为当前答案：

1. $g_x\le ans$

   此时可走完 $x$ 的最大和子树，$ans\gets ans+f_x$。

1. $g_x>ans$

    此时无法走完 $x$ 的最大和子树，但可以走其中一部分，递归下去。

    但有可能递归走下去并不优，那么在递归之前记 $lans$ 为 $ans$，递归完之后若 $ans<lans$ 则反悔操作，记 $ans\gets lans$ 即可。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, s, w[1000005], ft[1000005];
long long ans, f[1000005], g[1000005];
vector<int> e[1000005];
bool cmp(int x, int y) {
    return g[x] < g[y];
}
void add(int x, int y) {
    e[x].push_back(y);
}
void dfs1(int x) {
    for (int y : e[x])
        dfs1(y);

    sort(e[x].begin(), e[x].end(), cmp);
    f[x] += w[x];
    g[x] -= w[x];

    for (int y : e[x]) {
        if (!f[y])
            continue;

        if (g[y] > f[x])
            g[x] = max(g[x], g[y] - f[x]);

        f[x] += f[y];
    }

    f[x] = max(f[x], 0ll);
    g[x] = max(g[x], 0ll);
}
void dfs2(int x) {
    if (!f[x] || ans + w[x] < 0)
        return;

    if (g[x] <= ans) {
        ans += f[x];
        return;
    }

    long long lans = ans;
    ans += w[x];

    for (int y : e[x])
        dfs2(y);

    if (ans < lans)
        ans = lans;
}
int main() {
    cin >> n >> s;

    for (int i = 2; i <= n; i++) {
        cin >> ft[i];
        add(ft[i], i);
    }

    for (int i = 1; i <= n; i++)
        cin >> w[i];

    dfs1(1);
    ans = s;
    dfs2(1);
    cout << ans;
    return 0;
}
```

---

