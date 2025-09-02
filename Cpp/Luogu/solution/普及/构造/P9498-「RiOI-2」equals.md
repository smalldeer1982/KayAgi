# 「RiOI-2」equals

## 题目背景

在小树上坐落着一个幻想的城堡。这里是 E 国的领地，而小 E，则是 E 国之王。

为了打造一个完美的 E 国，他需要明辨是非，走向正义。

但是，他似乎有些太理想了。有时并没有一个完美的准则。是黑是白，谁能分辨？

## 题目描述

给定一棵 $n$ 个结点，以 $1$ 为根的树，定义一个结点的深度 $d_i$ 表示它到根结点的简单路径上的结点个数。

你需要给每个结点黑白染色，满足黑色结点的深度和等于白色结点的深度和。设 $c_i = \{0, 1\}$ 分别代表编号为 $i$ 的结点为黑色或白色，那么这即 $\displaystyle\sum_{c_i=0}d_i=\sum_{c_i=1}d_i$。

若无解，仅输出一行一个整数 $-1$。

## 说明/提示

### 样例解释

对于第一组数据，每个结点的深度分别是 $d=[1,2,2,3,3,3]$。黑色结点的深度和为 $d_1+d_5+d_6=1+3+3=7$，白色结点的深度和为 $d_2+d_3+d_4=2+2+3=7$。它们相等，所以样例输出是正确的。可能的正确输出包括但不限于样例输出、`0 1 1 0 0 1`，`1 0 0 1 0 1` 等。

### 数据规模与约定

**本题采用捆绑测试。**

| $\rm Subtask$ | 分值 | $n\le $ | 特殊性质 |
| :-----------: | :--: | :-----: | :------: |
| $0$ | $5$ | $20$ | / |
| $1$ | $15$ | $500$ | / |
| $2$ | $20$ | $5\times 10^3$ | / |
| $3$ | $10$ | / | $n$ 为偶数 |
| $4$ | $5$ | / | 树为菊花图（不保证根为菊花中心） |
| $5$ | $5$ | / | 树为一条链（不保证根为链的端点） |
| $6$ | $40$ | / | / |

斜杠表示这一栏无特殊限制。

对于 $100\%$ 的数据，$1\le n\le 10^6$，$1\le u_i,v_i\le n$，输入数据构成一棵树。

## 样例 #1

### 输入

```
6
1 2
1 3
2 4
2 5
2 6```

### 输出

```
0 1 1 1 0 0```

## 样例 #2

### 输入

```
5
1 2
1 3
2 4
2 5```

### 输出

```
-1```

# 题解

## 作者：TernaryTree (赞：18)

这是 RiOI R2 的 2C 题解。

## $\text{Subtask} \ 0$

直接爆搜。复杂度 $\Theta(2^n)$。

## $\text{Subtask} \ 1$

把爆搜加上记忆化，或者跑背包。因为值域大小是 $\Theta(n^2)$ 的，所以这里复杂度是 $\Theta(n^3)$ 的。

## $\text{Subtask} \ 2$

不知道有没有针对这个 sub 的做法。

## $\text{Subtask} \ 3$

讲到 $\text{Sub} \ 6$ 的时候再说。

## $\text{Subtask} \ 4$

既然是菊花图，那么有两种情况：

- 根是菊花的中心

  深度是 $1,2,2,2,\dots$。总和显然为奇数，无解。
  
- 根不是菊花的中心

  深度是 $1,2,3,3,\dots$。则仅当有奇数个结点时有解，可以对于深度为 $1,2$ 的全选上黑色，然后剩下的都是 $3$，按需分配即可。
  
## $\text{Subtask} \ 5$

既然是链，也有两种情况：

- 根是链的一端

  链的深度是这样的：$1,2,3,4,\dots$。

  易证得，当 $n\bmod4\in\{1,2\}$ 时总和为奇数而无解。

  从后往前四个四个分组，如果前面不够就补 $0$。然后黑色的选一组中间的，白色的选一组两边的。显然，$i+(i+3)=(i+1)+(i+2)$。

- 根不是链的一端

  大概是这样：$1,2,2,3,3,4,4,5,5,6,7,8,\dots$
  
  于是对于中间那段出现两次重复的，就一黑一白抵消。对于后面的和深度为 $1$ 的可以参考根是链的一端的情况处理。
  
## $\text{Subtask} \ 3\ \&\ 6$

考虑树深度序列的性质。

显然的一点，树深度序列排序后，相邻两个差的绝对值不超过 $1$。换句话说，这玩意值域上是连续的。

### $\text{Sub} \ 3$

先不考虑奇数。我们将排序后的序列两两分组，则每组的两个数之间差的绝对值也不超过 $1$。

我们从前往后每组每组选，维持当前黑色总和减去白色总和的绝对值在 $1$ 以内。做出一个大胆的猜想：这样最后一定可以回到 $0$。

具体地，我们维护一个偏移量，表示黑色总和减去白色总和。接下来，我们把所有在一组内的两个数不同的组称为“异值”组。如果当前组内两个数相等，那么我们一黑一白，什么也不用动；剩下来的，都是相邻差为 $1$ 的“异值”，考虑怎么处理它。如果当前的偏移量为 $1$，说明黑色多。那么我们就要让组内第一个（更小的一个）涂黑，另外一个就是白色。这样我们的偏移量回到了 $0$。如果偏移量为 $-1$ 同理。如果为 $0$ 怎么办？随便选一个。稍后会证明这样最终偏移量一定能回到 $0$。

### $\text{Sub} \ 6$

奇数怎么办呢？如果仍然从头开始分组，那么最后一个就很难处理了。俗话说得好，正着不行就倒过来做，我们从后往前分组，最后剩下来的一定是 $1$，这个是很好处理的。

你可以把它想象为在序列最前面补了一个 $0$。

### 正确性证明

对排序后的深度序列模 $2$ 考虑。问题转化为，我们所有的“异值”组个数的奇偶性是不是就是整个序列的和的奇偶性。

一个结论：两个中间没有“异值”组的“异值”组之间的所有和全都是偶数。这是因为，中间被分成了若干偶数组，这些组里面的数两两相同，故恒为偶数。而“异值”中两个数不同，所以和为奇数。奇数乘以奇数得到奇数，乘以偶数得到偶数。于是，“异值”组个数的奇偶性就是整个序列的和的奇偶性。得证。

### 实现

两种实现方式：一种是 dfs + 排序 $\Theta(n\log n)$，一种是 bfs $\Theta(n)$。实际上两者速度差别不大。

dfs:

```
#include <bits/stdc++.h>
#define int long long
#define fs first
#define sc second

using namespace std;

const int maxn = 1e6 + 10;

int n, tot, cur, flag;
vector<int> g[maxn];
pair<int, int> dep[maxn];
int c[maxn];

void dfs(int u, int fa) {
	dep[u] = make_pair(dep[fa].fs + 1, u);
	for (int i = 0; i < g[u].size(); i++) {
		int v = g[u][i];
		if (v != fa) dfs(v, u);
	}
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
	cin >> n;
	for (int i = 1, u, v; i <= n - 1; i++) {
		cin >> u >> v;
		g[u].push_back(v), g[v].push_back(u);
	}
	dfs(1, 0);
	if (n & 1) ++n, flag = true;
	sort(dep + 1, dep + 1 + n);
	for (int i = 1; i <= n; i++) tot += dep[i].fs;
	if (tot & 1) return (puts("-1"), 0);
	for (int i = 1; i <= n; i += 2) {
		if (dep[i].fs == dep[i + 1].fs) c[dep[i].sc] = 0, c[dep[i + 1].sc] = 1;
		else c[dep[i].sc] = cur == -1, c[dep[i + 1].sc] = !c[dep[i].sc], cur = cur != 0 ? 0 : -1;
	}
	for (int i = 1; i <= n - flag; i++) cout << c[i] << " ";
	return 0;
}
```

bfs:

```
#include <bits/stdc++.h>
#define int long long
#define fs first
#define sc second

using namespace std;

const int maxn = 1e6 + 10;

int n, tot, cur, flag;
vector<int> g[maxn];
int now;
pair<int, int> dep[maxn];
int d[maxn];
int c[maxn];
int vis[maxn];

void bfs(int s) {
    queue<int> que;
    que.push(s);
    vis[s] = true;
    dep[++now] = make_pair(1, s);
    d[s] = 1;
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        for (int i = 0; i < g[u].size(); i++) {
            int v = g[u][i];
            if (!vis[v]) {
                que.push(v);
                vis[v] = true;
                dep[++now] = make_pair(d[u] + 1, v);
                d[v] = d[u] + 1;
            }
        }
    }
}

int tn[maxn];

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> n;
    for (int i = 1, u, v; i <= n - 1; i++) {
        cin >> u >> v;
        g[u].push_back(v), g[v].push_back(u);
    }
    if (n & 1) ++n, ++now, flag = true;
    bfs(1);
    for (int i = 1; i <= n; i++) tot += dep[i].fs;
    if (tot & 1) return (puts("-1"), 0);
    for (int i = 1; i <= n; i += 2) {
        if (dep[i].fs == dep[i + 1].fs) c[dep[i].sc] = 0, c[dep[i + 1].sc] = 1;
        else c[dep[i].sc] = cur == -1, c[dep[i + 1].sc] = !c[dep[i].sc], cur = cur != 0 ? 0 : -1;
    }
    for (int i = 1; i <= n - flag; i++) cout << c[i] << " ";
    return 0;
}
```

---

## 作者：ys_kylin__ (赞：9)

本题是一道有一点思维难度的题，但是整体不是非常难。首先 dfs 跑一遍记录树的深度，这个简单不讲。接下来的才是更重要的部分。
### 5pts 做法
使用递归枚举加或减，时间复杂度为 $2^n$ 直接 T 飞，但是数据还是施舍了 $5$ 分。关键代码为
```cpp
void dfs2(int dd,int x) {
	if(dd==0 && x==n+1) {
		for(int i=1;i<=n;i++) printf("%d ",ans[i]);
		exit(0);
	}
	if(x==n+1) return;
	ans[x]=1;dfs2(dd-d[x],x+1);
	ans[x]=0;dfs2(dd+d[x],x+1);
}
```
### AC 思路
在计算出深度 $d$ 数组后，不难发现问题变成了分配数使得双方平衡，其实如果是随便的数而不是树的深度的话，本题还会更难一些。不过他有一个特殊性质，也就是**树的深度**。

为什么说它是特殊的性质？因为如果是深度的话，节点的深度必然是连续的。也就是假如 $d_i$ 是整个 $d$ 数组里面最大的，那么 $d$ 数组中，必然会出现过从 $1$ 到 $d_i$。因为他是一棵树，子节点必然能找到一个父节点。

而又要如何利用该性质呢？我们可以将 $d$ 排序（此处要将 $d$ 设成结构体，因为要记住其初始位置，用 $num$ 代表其数值，用 $id$ 代表其编号），然后先计算 $d$ 的加和，如果是奇数，则无解，否则**一定有解**，因为上文提到深度是连续的。

接下来，用另一个计数器 $sum2$ 记下，从大到小枚举，如果满足 `sum2+d[i].num<sum/2`，$sum2$ 加上 $d _ i$ 的 $num$ 并且加入黑色（可以白也可以黑，看初始化）。否则往下查找，找到某个数加上 $sum2$ 是否为 $sum\div2$ ，是的话将它染色后输出。**注意这里必定可以找到满足条件的数。**

特别提示：不开 long long 见祖宗！
## code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
vector <int> ve[1000005];//vector存图
int ans[1000005];
int n;
struct node {
	int num,id;
}d[1000005];
void dfs(int x,int ftr) {//将深度构建
	for(int i=0;i<ve[x].size();i++) {
		int v=ve[x][i];
		if(v==ftr) continue;
		d[v].num=d[x].num+1;
		dfs(v,x);
	}
}
bool cmp(node x,node y) {
	return x.num<y.num;
}
signed main() {
	scanf("%lld",&n);
	for(int i=1;i<n;i++) {
		int u,v;
		scanf("%lld%lld",&u,&v);
		ve[u].push_back(v);
		ve[v].push_back(u);
		d[i].id=i;
	}
	d[n].id=n;
	d[1].num=1;
	dfs(1,-114);
	int sum=0,sum2=0;
	for(int i=1;i<=n;i++) {
		sum+=d[i].num;
	}
	if(sum%2==1) {
		printf("-1");//必为无解
		return 0;
	}
	sort(d+1,d+n+1,cmp);
	for(int i=n;i;i--) {
		if(sum2+d[i].num<sum/2) {//满足条件直接染色
			sum2+=d[i].num;
			ans[d[i].id]=1;
		}
		else {
			for(int j=i;j;j--) {//向下查找
				if(sum2+d[j].num==sum/2) {
					ans[d[j].id]=1;
					break;
				}
			}
			for(int j=1;j<=n;j++) printf("%lld ",ans[j]);
			return 0;
		}
	}
	return 0;
}
```

---

## 作者：GaCGe (赞：5)

# [P9498 「RiOI-2」equals](https://www.luogu.com.cn/problem/P9498) 题解
## 题意
对于一棵有根树的深度序列，问是否存在一种划分方式（染色），使得划分出两个序列的权值相等。
## 解法
首先，当深度序列之和为奇数时，显然不存在着一种划分，输出 $-1$。

直观来看，树的深度序列排序后相邻两项之差不超过 $1$ ，考虑将序列排序后相邻的两项染上不同的颜色，又考虑到数值较大的项比较难以处理，所以将序列降序排序，先处理数值大的。从头遍历时统计染成黑色点的权值和和染成白色点的权值和，将这个点染成权值和较小的那一种颜色。

## 正确性证明
1. $n$ 为偶数时，由于深度序列的性质，能够保证每处理两项时黑白点权值之差为 $0$ 或 $1$ 或 $-1$，显然序列的最后两项必为 $2$ 和 $1$，而且有解时序列所有项之和一定为偶数，所以前 $n-2$ 项划分出的黑白点的权值之差必为 $1$ 或 $-1$，显然能够使两个染色方法权值相等。
2. $n$ 为奇数时，相似地，前 $n-1$ 项划分出的黑白点的权值之差必为 $1$ 或 $-1$，序列的最后一项必为 $1$，能够使两个染色方法权值相等。
## 实现
一遍 dfs，一遍排序，复杂度 $Θ(n\log{n})$.

```cpp
#include<bits/stdc++.h>
using namespace std;
vector<int>a[1000005];
bool flag[1000005];
int d[1000005];
long long n,u,v,cnt,cnt1,cnt2;
void dfs(int noww,int fa,int dep){
	d[noww]=dep;
	for(int i=0;i<a[noww].size();i++){
		int y=a[noww][i];
		if(y==fa)continue;
		dfs(y,noww,dep+1);
	}
}
struct node{int num;int dd;};
node e[1000005];
bool cmp(node x,node y){
	return x.dd>y.dd;
}
int main(){
	cin>>n;
	for(int i=1;i<=n-1;i++){
		cin>>u>>v;
		a[u].push_back(v);
		a[v].push_back(u);
	}dfs(1,-1,1);
	for(int i=1;i<=n;i++){
		e[i].dd=d[i];
		e[i].num=i;
		cnt+=d[i];
	}if(cnt&1){
		cout<<-1<<endl;
		return 0;
	}
	sort(e+1,e+1+n,cmp);
	for(int i=1;i<=n;i++){
		if(cnt1>cnt2){
			flag[e[i].num]=1;
			cnt2+=e[i].dd;
		}
		else cnt1+=e[i].dd;
	}for(int i=1;i<=n;i++)cout<<flag[i]<<" ";
	return 0;
} 
```


---

## 作者：sane1981 (赞：5)

## 背景
正所谓只要敢贪心，就能够 AC。
## 题目解读
[原题传送门](https://www.luogu.com.cn/problem/P9498)

先在树上跑一遍 DFS，求出每个节点的深度（记为 $dep[u]$）。然后我们设 $sum$ 为所有结点的深度之和，那么这道题变成了在一串数中任意挑选使得那些数和为 $\dfrac{sum}{2}$。

看到了 $1 \leq n \leq 10^6$ 的数据范围，我们意识到只能用 $O(n \operatorname{log}n )$ 或 $O(n)$ 的算法。看到深度一定是 $1,2,3,\dots$  这样子排列的，因此我们开始想到贪心。
### 贪心策略
对于 $sum$ 为奇数显然无解。

如果不然，先按深度从小到大排序（双关键字排序，第二关键字是原节点的编号）

然后从左向右依次枚举，找到第一个 $i$ 满足 $S_i=\sum_{k=1}^{i}dep[i] \ge \dfrac{sum}{2}$。

之后我们只需去除其中一个深度为 $S_i-\dfrac{sum}{2}$ 的结点。
### 证明
我们若在 $i$ 满足 $S_i \ge \dfrac{sum}{2}$，那么在 $i-1$ 时必定满足 $S_{i-1}<\dfrac{sum}{2}$。

由于我们经过排序，因此在 $[1,i]$ 里的数，都必定在 $\{1,2,\dots,S_i-S_{i-1}\}$ 集合中出现。

所以我们 $S_i-\dfrac{sum}2$ 一定可以取到。也就是一定能够找到一组解。

### 注意事项
十年 OI 一场空，不开 long long 见祖宗。
## AC_Code
```cpp
#include<bits/stdc++.h>
#include<vector>
using namespace std;
int n,a,b;
long long need;
vector <int> e[1000005];
int ans[1000005];
struct point{
	int deep,id;
}c[1000005];
bool cmp(point x,point y){
	return x.deep<y.deep;
}
void dfs(int u,int fa){
	c[u].deep=c[fa].deep+1;
	c[u].id=u;
	for(int i=0;i<e[u].size();i++){
		int v=e[u][i];
		if(v==fa) continue;
		dfs(v,u);
	}
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<n;i++){
		scanf("%d%d",&a,&b);
		e[a].push_back(b);
		e[b].push_back(a);
	}
	dfs(1,0);
	sort(c+1,c+n+1,cmp);
	for(int i=1;i<=n;i++) need+=(long long)c[i].deep;
	if(need&1){
		printf("-1\n");
		return 0;
	}
	long long cut=0,temp=0;
	for(int i=1;i<=n;i++){
		temp+=(long long)c[i].deep;
		ans[c[i].id]=1;
		if(temp>=need/2){
			cut=temp-need/2;
			break;
		}
	}
	for(int i=1;i<=n;i++)
		if(cut==(long long)c[i].deep){
			ans[c[i].id]=0;
			break;
		}
	for(int i=1;i<=n;i++) printf("%d ",ans[i]);
	printf("\n");
	return 0;
}
```


---

## 作者：what_can_I_do (赞：3)

[传送门](https://www.luogu.com.cn/problem/P9498)

感觉有种橙题的错觉。

先考虑计算每个节点的深度。这个简单，我用的是 bfs 遍历节点计算深度。由于本题考察的似乎不是计算深度，在此我也就不过多阐述。

计算完所有节点的深度后，我们用一个变量 $sum$ 来记录所有节点的深度和。很明显，若 $sum$ 为奇数时一定构成不了满足条件的方案，因为奇数无法平均分成两份。

接下来证明 $sum$ 为偶数一定有解。首先我们可以确定，一颗树的每一条从根到叶子结点的路径上每个节点的深度一定都是从 $1$ 到叶子结点的深度的相差为 $1$ 的等差数列。接着我们知道从 $1$ 到 $n$ 相差为 $1$ 的等差数列的所有数是一定能构成从 $1$ 到整个数列的和中的所有数的。而题目中的树又是由多个这样的等差数列组成的，所以一定能够成 $1$ 到 $sum\div 2$ 中的所有数。

那么接下来想如何构造方案。很显然，这是贪心。我们要从深度最大的节点入手，若当前的权值可以在保证加上这个节点的深度后不超过 $sum\div 2$ 时，就选择把当前节点染色，否则不选这个节点，往小的去继续枚举。这样做就一定能构造出方案。

这很好证明。如果你从小的开始选，那么选到后面假设你现在的权值为 $m$，可是 $sum\div 2-m<d_i$，也就是剩余的可选择的空间不够了，那么明显就错了。但从大的开始选。由于节点深度的最小值为 $1$，所以不管可选择的空间有多少，到最后肯定也是不会小于 $1$ 的，这时直接选择 $1$ 就行了。当然了，这里的 $1$ 只是说明这样子选择它是一定能构造出方案的。

# CODE:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
long long sum=0,s=0;
bool vis[1000010]={0};
vector<int> ed[1000010];
struct bbb
{
	int d,f,k;
}a[1000010];
inline bool cmp(bbb x,bbb y)
{
	return x.d>y.d;
}
inline bool cmp1(bbb x,bbb y)
{
	return x.k<y.k;
}
inline void bfs()
{
	queue<pair<int,int> > q;
	q.push(make_pair(1,1));
	while(!q.empty())
	{
		int x=q.front().first,s=q.front().second;
		q.pop();
		vis[x]=1,a[x].d=s;
		for(register int i=0;i<=ed[x].size()-1;i++)
			if(vis[ed[x][i]]==0) q.push(make_pair(ed[x][i],s+1));
	}
}
int main()
{
	scanf("%d",&n);
	for(register int i=1;i<=n-1;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		ed[u].push_back(v);
		ed[v].push_back(u);
	}
	bfs();
	for(register int i=1;i<=n;i++) a[i].k=i,sum+=a[i].d;
	if(sum%2==1){printf("-1");return 0;}
	sort(a+1,a+n+1,cmp);
	for(register int i=1;i<=n;i++)
	{
		if(s+a[i].d<=sum/2) s+=a[i].d,a[i].f=1;
		if(s==sum/2) break;
	}
	sort(a+1,a+n+1,cmp1);
	for(register int i=1;i<=n;i++) printf("%d ",a[i].f);
	return 0;
}
```

---

## 作者：CEFqwq (赞：2)

结论题。

本题有一个性质，当这棵树存在深度为 $k$ 的节点时，必然有深度小于 $k$ 的节点存在。

那么将深度求和，记为 $s$。如果和是奇数，无解；否则必定有解，从小到大求深度和到大于 $\dfrac{s}{2}$，往回找到一个结点使得当前深度和减去该节点深度刚好等于 $\dfrac{s}{2}$ 就可以了。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct node{
	int dep,id;
	bool operator <(node b)const{//按深度从小到大排序
		return this->dep<b.dep;
	}
}tr[1000001];
vector<int>G[1000001];
int n,dep[1000001];
bool vis[1000001];
bool cho[1000001];
void dfs(int u,int depp){
	if(vis[u])return;
	vis[u]=1;
	dep[u]=depp; 
	for(auto &v:G[u]){
		dfs(v,depp+1);
	}
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n;
	for(register int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	dfs(1,1);//dfs 求深度
	int zh=0;
	for(register int i=1;i<=n;i++){
		zh+=dep[i];
	}
	if(zh%2==1){//无解
		cout<<-1;
		return 0;
	}
	int sum=0;
	for(register int i=1;i<=n;i++){
		tr[i].id=i;
		tr[i].dep=dep[i];
	}
	sort(tr+1,tr+1+n);
	for(register int i=1;i<=n;i++){
		sum+=tr[i].dep;//求和
		cho[tr[i].id]=1;//标记是否取
		if(sum>(zh>>1)){//如果大于上文的 s/2
			for(register int j=1;j<=i;j++){
				if(tr[j].dep==sum-(zh>>1)){//找到相应结点
					cho[tr[j].id]=0;//改为不取，直接输出
					for(register int k=1;k<=n;k++)cout<<cho[k]<<" ";
					return 0;
				}
			}
		}
	}
}
```

最后加一句，这是天波老师第一次过 T3，天波老师 tql！快给本题解点赞，支持天波！

---

## 作者：Hughpig (赞：2)

先一次 $\text{dfs}$ 求出每个点的深度。记深度和为 $sum$。显然 $sum$ 为奇数无法平分为相同的两部分，直接输出 $-1$ 即可。

然后考虑如何染色，使得黑色节点深度和等于 $\dfrac{sum}{2}$。

我们把所有节点按深度从大到小排序，然后从大往小扫，如果这个点可以取就直接取，否则就跳过这个点。

因为树上所有点的深度必然连续，因此如果当前取的点和小于 $\dfrac{sum}{2}$ （还没取满）且取了当前的点会超过上限，那么必然会有比当前点更小的点可以满足取了那个点就可以取满。因为是从大到小扫的，所以第一次扫到的可以取的节点就是最优的（取了它就正好取满）。

代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,dep[1000007],cnt;
bool ans[1000007];
vector<ll> G[1000007];

struct node
{
	ll num,dep;	
}tree[1000007];

void dfs(int u,int fa){
	dep[u]=dep[fa]+1;
	cnt+=dep[u];
	for(int i=0;i<G[u].size();i++){
		int v=G[u][i];
		if(fa==v)continue;
		dfs(v,u);
	}
}

bool cmp(node a,node b){
	return a.dep>b.dep;
}

int main()
{
	ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin>>n;
    for(int i=1,u,v;i<n;i++){
    	cin>>u>>v;
    	G[u].push_back(v);
    	G[v].push_back(u);
	}
	dfs(1,0);
	if(cnt&1){
		cout<<-1;
		return 0;
	}
	for(int i=1;i<=n;i++){
		tree[i].num=i,tree[i].dep=dep[i];
	}
	sort(tree+1,tree+n+1,cmp);
	cnt/=2;
	for(int i=1;i<=n;i++){
		if(cnt>=tree[i].dep)cnt-=tree[i].dep,ans[tree[i].num]=1;
	}
	for(int i=1;i<=n;i++)cout<<ans[i]<<' ';
	return 0;
}
```

---

## 作者：N_z_ (赞：1)

## 思路
对于一个 $dep$ 序列，我们做出如下断言：有解当且仅当和为偶数，且从大到小贪心构造是对的。

首先和为奇数显然是无解，我们对和为偶数的构造进行证明。

这一问题等价于对 $dep$ 序列取子集使它和为 $k=sum\div2$。我们对 $dep$ 从大到小排序之后贪心选取，记 $m$ 为当前数列剩余数的最大值，当 $k>m$ 时，$k\gets k-m$，这时候 $k$ 和 $sum$ 的差值没有变，$k\le m$ 时，直接选择 $k$，问题解决。由于 $k<sum$，这样贪心是对的。 
## 代码
```cpp
#define int long long
vector<int>e[1000001];
int ans[1000001];
pair<int,int>dep[1000001];
int sum=0;
void dfs(int u,int f)
{
	dep[u]={dep[f].first+1,u};
	sum+=dep[u].first;
	for(auto q:e[u])
	if(q!=f)
	{
		dfs(q,u);
	}
}
main()
{
	int n;
	cin>>n;
	for(int x=1;x<n;x++)
	{
		int u,v;
		cin>>u>>v;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	dep[0].first=0;
	dfs(1,0);
	if(sum%2==1)cout<<-1<<endl;
	else
	{
		sort(dep+1,dep+1+n);
		for(int x=n;x>=1;x--)
		if(sum-2*dep[x].first>=0)sum-=2*dep[x].first,ans[dep[x].second]=1;
		for(int x=1;x<=n;x++)
		cout<<ans[x]<<' ';cout<<endl;
	}
}
```
注：[这](https://www.luogu.com.cn/paste/a5e7tybl)是这份代码的头。

---

## 作者：Elairin176 (赞：1)

[传送门](https://www.luogu.com.cn/problem/P9498)     
2C 就这？   
## 题意
给定一棵树，把每个结点染色，只能染成黑白。   
求一种染色方案使所有黑结点的深度和等于白结点的深度和，或报告无解。    
## 解法
只能染成黑白，那么两种颜色的深度和应该都是总深度和的一半。那么明显在总深度和是奇数的时候无解，其他时候都有解。   
- 为什么其他时候都有解？  

这时候，总深度和为偶数。那么我们设这个数为 $d$，我们只需要达到 $\dfrac{d}{2}$ 就可以了。   
明显地，每一条链上的深度都具有单调性，而树上所有的深度所组成的数列也明显具有单调性且每次数值变化中，数值只增大 $1$。    
每次只增大 $1$，那么很明显可以组成 $\dfrac{d}{2}$。    
现在问题来了：如何找到一组方案呢？    
我们可以对所有的深度从大到小排序，根据上面的结论，我们扫一遍，能加则加就可以了。    
时间复杂度 $O(n\log n)$，可以通过。     
[CODE](https://www.luogu.com.cn/paste/ii0xw52e)

---

## 作者：Paracelestia (赞：1)

# P9498 「RiOI-2」equals

[题目传送门](https://www.luogu.com.cn/problem/P9498)

## $\mathtt{Description}$

定义一个结点的深度表示它到根结点的简单路径上的结点个数。

给定一棵以 $1$ 为根的树，求如何将树上的点分成两组，使两组点的深度和相等。


## $\mathtt{Solution}$

深度一遍 DFS 即可维护，重要的是如何分配节点。

首先，如果深度总和是奇数，肯定无解。

然后，我们可以看出，一棵树的节点的深度，其值域是连续的。深度大的节点到根的路径，一定包含若干深度小的节点到根的路径。

考虑贪心。将节点按深度从大到小排序，贪心地选择深度较大的点，看是否能够合法地染色。

复杂度为 DFS $O(N)$ + 排序 $O(N \log N)$ + 贪心 $O(N)$，共 $O(N \log N)$，可以通过此题。

## $\mathtt{Code}$

```cpp
#include <bits/stdc++.h>
using namespace std;

#define N 114514 / 20
#define M 1919810 * 2
#define fi first
#define se second

typedef long long ll;
typedef pair<int, int> pii;

template<typename T> T read() {
    T x = 0, f = 1; char ch = 0;
    for(; !isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
    for(; isdigit(ch); ch = getchar()) x = (x << 3) + (x << 1) + (ch - '0');
    return x * f;
}

#define int long long // 不开 long long 见祖宗！

struct edge {
    int to, nxt;
} e[M];
int head[M], tot;
void add(int u, int v) {
    e[++ tot] = {v, head[u]};
    head[u] = tot;
}

struct node {
    int id, val;
    bool operator<(const node &x) const {
        return val > x.val;
    }
} p[M];

int n, dep[M], f[M], cnt, s;

void dfs(int u, int fa) {
    dep[u] = dep[fa] + 1;
    p[++ cnt] = {u, dep[u]};
    s += dep[u];
    for(int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].to;
        if(v == fa) continue;
        dfs(v, u);
    }
}

bool ans[M];

signed main() {
    n = read<int>();
    for(int i = 1; i < n; ++ i) {
        int u = read<int>(), v = read<int>();
        add(u, v), add(v, u);
    }
    dfs(1, 0);
    sort(p + 1, p + 1 + n);
    if(s % 2) return puts("-1"), 0;
    s /= 2;
    for(int i = 1; i <= n; ++ i) {
        if(s >= p[i].val) {
            s -= p[i].val;
            ans[p[i].id] = 1;
        } 
    }
    for(int i = 1; i <= n; ++ i) printf("%d ", ans[i]);
    return 0;
}
```


---

## 作者：ssSSSss_sunhaojia (赞：1)

[原题传送门](https://www.luogu.com.cn/problem/P9498)
# 思路：
我们首先用深搜预处理出每个节点的深度，在得到每个节点的深度后，问题就转换成了：给定一个长度为 $n$ 的序列，将它划分成两个子序列，使得这两个子序列的和相等。

此时我们很容易想到背包的做法，只用管其中一个子序列，其和为整个序列的和除以 $2$，这就是一个模板的01背包。可是这个做法会超时。

此时我们可以观察整个序列的特点。发现，当一个非根节点的深度为 $x$ 时，必定存在一个节点的深度为 $x-1$，比如它的父亲节点就是深度为 $x-1$ 的。

换句话说，假设最大深度的节点深度为 $ma$，则从 $1$ 到 $ma$ 之间的所有数都是至少一个节点的深度。所以，只要整个序列之和是要是 $2$ 的倍数，就一定存在一种合法的方案。

我们将整个序列从大到小排序一下（记得保存序号），按顺序访问其中的每一个元素。对于其中一个元素，只要目前选中的所有数之和加上这个数后不超过总和的一半，就选择此元素。

# AC Code:
```
#include <bits/stdc++.h>
using namespace std;
#define in inline
#define re register
#define IOS ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
typedef long long LL;
LL m, u, v, ma, sum, f[1001001], a[1001001], n;
vector <LL> g[1001001];  
struct no {
	LL v, id; 
}b[1001001]; 
bool cmp(no x, no y) {return x.v > y.v; }
in LL qpow(LL a, LL b) {LL res = 1; while(b) {if(b & 1) res = res * a; a = a * a; b >>= 1; } return res; }
in void dfs(LL u, LL fa) {
	a[u] = a[fa] + 1; 
	LL v;  
	for(re int i = 0; i < g[u].size(); i ++) {
		v = g[u][i];  
		if(v == fa) continue; 
		dfs(v, u); 
	}
}
int main() {
	IOS;
	cin >> n; 
	for(re int i = 1; i < n; i ++) cin >> u >> v, g[u].push_back(v), g[v].push_back(u);   
	dfs(1, 0); //预处理深度
	for(re int i = 1; i <= n; i ++) sum += a[i], b[i].v = a[i], b[i].id = i; 
	sort(b + 1, b + n + 1, cmp); //排序
	if(sum & 1) {cout << -1; return 0; }//不是2的倍数就无解
	else {
		sum >>= 1; 
		for(re int i = 1; i <= n; i ++) {
			if(sum >= b[i].v) sum -= b[i].v, f[b[i].id] = 1; //目前选中的所有数这和加上这个数后不超过总和的一半
			if(sum == 0) break; 
		}
		for(re int i = 1; i <= n; i ++) cout << f[i] << " ";  //输出
	}
	return 0;
}
```

---

## 作者：Convergent_Series (赞：1)

先 dfs 一遍计算每个结点的深度。

若总深度为奇数，则一定不可能分成深度和相等的两份，输出无解即可。

否则，考虑先用深度较小的点凑出其中一种颜色。

从 $1$ 依次往下枚举深度，记录目前的深度和。

设总深度的一半为 $s$，当前深度为 $i$，深度和为 $k$。

若加上深度为 $i$ 的所有点后 $k$ 不超过 $s$，则将其全部染色；

否则，染色到 $k$ 刚好超过或等于 $s$。

若等于，则直接输出染色方案；否则，设超出的数为 $j$，则 $j$ 一定小于 $i$，去掉一个深度为 $j$ 的点即可。

对于树上任一条链，深度一定连续。因为有深度为 $i$ 的点，则长度为 $i$ 的链一定存在，链上一定有深度为 $j$ 的点。因为已经枚举到 $i$，所以深度为 $j$ 的点全部被染色，则应去掉的点一定存在。

代码：
```cpp
#include<bits/stdc++.h>
#define int long long
#define pcs putchar(' ')
#define pcn putchar('\n')
using namespace std;
int read(){
	int a=0;char ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9') a=(a<<3)+(a<<1)+(ch^'0'),ch=getchar();
	return a;
} 
void write(int a){
	if(a>9) write(a/10); 
	putchar(a%10+'0');
}
const int N=1e6+10;
struct edge{int to,ne;}e[2*N];
int n,cnt=0,fi[N],d[N],col[N];
vector<int>t[N];
void add(int u,int v){
	cnt++;
	e[cnt].to=v;e[cnt].ne=fi[u];
	fi[u]=cnt;
}
void dfs(int x,int fa){
	d[x]=d[fa]+1;
	for(int i=fi[x];i;i=e[i].ne){
		if(e[i].to==fa) continue;
		dfs(e[i].to,x);
	}
}
signed main(){
	n=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		add(u,v);add(v,u);
	}
	dfs(1,0);int s=0;
	for(int i=1;i<=n;i++) s+=d[i];
	if(s&1){
		putchar('-');putchar('1');return 0;
	}s>>=1;int l=0;
	for(int i=1;i<=n;i++) t[d[i]].push_back(i),l=max(l,d[i]);
	int k=0;
	for(int i=1;i<=l;i++){
		if(k+i*t[i].size()<s){
			k+=i*t[i].size();
			for(int j=0;j<t[i].size();j++) col[t[i][j]]=1;
			continue;
		}
		if(k+i*t[i].size()==s){
			k+=i*t[i].size();
			for(int j=0;j<t[i].size();j++) col[t[i][j]]=1;
			for(int i=1;i<=n;i++) putchar(col[i]+'0'),pcs;
			return 0;
		} 
		int sum=(s-k)/i;
		k+=sum*i;
		if(sum!=0) for(int j=0;j<sum;j++) col[t[i][j]]=1;
		if(k==s){
			for(int i=1;i<=n;i++) putchar(col[i]+'0'),pcs;
			return 0;
		}
		col[t[i][sum]]=1;
		col[t[i+k-s][0]]=0;
		for(int i=1;i<=n;i++) putchar(col[i]+'0'),pcs;
		return 0;
	}
	return 0;
}
```

---

## 作者：rmzls (赞：1)

### 思路
统计每个节点深度后，计算深度和 $sum$。我们将每个节点深度从小到大排序，贪心全取，不停累加当前已选深度和 $tot$。当 $tot$ 第一次大于 $sum$ 的时候，我们找到一个深度为 $tot-sum$ 的点，将他取消标记即可。这里的查找直接枚举搜索即可，不会改变复杂度。   
因为深度排序后是连续的，因此当取到 $tot$ 的时候一定存在一个已经被选的一个深度为 $tot-sum$ 的点。

------------
### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e6+10;
const int M=1e8+10;
int n,head[N],nxt[N],l,r,cha,to[N],fm[N],cnt,u,v,sum,flag,col[N],ans,tot;
struct node{
	int d,id;
	bool operator <(const node &p)const{
		return d<p.d;
	}
}d[N]; 
void add(int u,int v){
	to[++cnt]=v;
	fm[cnt]=u;
	nxt[cnt]=head[u];
	head[u]=cnt;
}
void dfs(int x){
	for(int i=head[x];i;i=nxt[i]){
		int y=to[i];
		if(d[y].d){
			continue;
		}
		d[y].d=d[x].d+1;
		dfs(y);
	}
}
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n-1;i++){
		scanf("%lld%lld",&u,&v);
		add(u,v);
		add(v,u);
	}
	d[1].d=1;
	dfs(1);
	for(int i=1;i<=n;i++){
		sum+=d[i].d;
		d[i].id=i;
	}
	if(sum&1){
		printf("-1\n");
		return 0;
	}
	sort(d+1,d+1+n);
	for(int i=1;i<=n;i++){
		tot+=d[i].d;
		col[d[i].id]=1;
		if(tot>=sum/2){
			if(tot==sum/2){
				break;
			}
			cha=tot-sum/2;
			for(int j=1;j<=n;j++){
				if(d[j].d==cha&&col[d[j].id]==1){
					col[d[j].id]=0;
					break;
				}
			}
			break;
		}
	}
	for(int i=1;i<=n;i++){
		printf("%lld ",col[i]);
	}
	return 0;
}
```


---

## 作者：DengDuck (赞：1)

这题显然是一道背包问题，但是由于数据很大，我们需要找一些特殊性质。

首先可以转换，我们考虑一开始所有点都是黑的，深度之和为 $S$，接下来选点变白，则点 $x$ 的贡献应该是深度的两倍 $2\times dep_x$，我们要使得所有的 $2\times dep_x$ 之和为 $S$。

我们发现当 $S$ 为奇数的时候无解。

我们可以先把深度贡献和 $S$ 除去一个二，这样画风会正常一点。

那为偶数一定有解吗？是的，首先由于 $S$ 是深度之和的一半，所以我们全选一定大于 $S$，因此不用担心凑不出这么大的值。

我们设最大深度为 $x$，根据树的性质，显然深度 $[1,x]$ 都存在，因此我们可以贪心地从大往小找数填充，这样为什么可以填充出来呢？

我们考虑第一次因为 $S$ 太小而无法填充，之前肯定是所有节点无脑嗯塞，其深度也减去了（注意，$S$ 是深度和的一半），所以这些点可以直接当成删掉了。

现在我们设这个节点的深度为 $x$，我们注意到 $S$ 的值显然比当前节点深度的一半还要小，所以问题变成了一个更好解决的，规模更小的问题，考虑一直向下做，显然规模是在不断变小的，所以是有解的。

时间复杂度可以做到 $O(n)$。
 
```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const LL N=1e6+5;
LL n,x,y,c[N],sum,dep[N],mx,hav[N],ned[N];
vector<LL>v[N];
void dfs(LL x,LL f)
{
	dep[x]=dep[f]+1;
	sum+=dep[x];
	hav[dep[x]]++;
	mx=max(mx,dep[x]);
	for(LL i:v[x])
	{
		if(i==f)continue;
		dfs(i,x);
	}
}
int main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n-1;i++)
	{
		scanf("%lld%lld",&x,&y);
		v[x].push_back(y);
		v[y].push_back(x);
	}
	dfs(1,0);
	if(sum%2==1)
	{
		puts("-1");
		return 0;
	}
	sum/=2;
	for(int i=mx;i>=1;i--)
	{
		for(int j=1;j<=hav[i]&&i<=sum;j++)
		{
			ned[i]++;
			sum-=i;
		}
	}
	for(int i=1;i<=n;i++)
	{
		if(ned[dep[i]])c[i]=1,ned[dep[i]]--;
		printf("%lld ",c[i]);
	}
}
```

---

## 作者：Not_defined (赞：0)

## 题目大意
给树上结点染成黑白两色，使黑色与白色的结点深度和相等。
## 思路
很显然，当所有节点深度和为奇数时不满足情况，直接输出 $-1$ 即可。其次我们可以将结点深度从小到大排序，由于相邻两项深度差要么是 $0$ 或 $1$，那么肯定存在一种情况满足，我们可以不断累加，如果超出总深度和的一半，去找超出的那部分，并去掉标记。
## Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10;
int n,cnt,head[N],vis[N],sum;
struct node
{
	int next,to;
}e[N<<1];
struct Point
{
	int size,id;
}a[N];
void add(int u,int v)
{
	e[++cnt].next=head[u];
	e[cnt].to=v;
	head[u]=cnt;
}
void dfs(int x,int fa)
{
	for(int i=head[x];i;i=e[i].next)
	{
		int y=e[i].to;
		if(y==fa)continue;
		a[y].size=a[x].size+1;
		dfs(y,x);
	}
}
bool cmp(Point x,Point y)
{
	return x.size<y.size;
}
main()
{
	cin>>n;
	a[1].size=1;
	for(int i=1;i<=n;i++)a[i].id=i;
	for(int i=1;i<n;i++)
	{
		int u,v;
		cin>>u>>v;
		add(u,v);
		add(v,u);
	}
	dfs(1,0);
	for(int i=1;i<=n;i++)sum+=(int)a[i].size;
	if(sum&1)
	{
		puts("-1");
		return 0;
	}
	sum=sum/2;
	int ans=0,cut=0;
	sort(a+1,a+1+n,cmp);
	for(int i=1;i<=n;i++)
	{
		ans+=(int)a[i].size;
		vis[a[i].id]=1;
		if(ans>=sum)
		{
			cut=ans-sum;
			break;
		}
	}
	for(int i=1;i<=n;i++)
	{
		if(cut==a[i].size)
		{
			vis[a[i].id]=0;
			break;
		}
	}
	for(int i=1;i<=n;i++)cout<<vis[i]<<" ";
	return 0;
}
```


---

## 作者：cppcppcpp3 (赞：0)

[传送门](https://www.luogu.com.cn/problem/P9498)。

## $\textbf{Solution}$

可以 $O(n)$ 地求出每个点的深度 $dep_i$。

然后我们发现好像不需要再关注树的其他条件了。设 $tot=\sum_{i=1}^{n} dep_i$，则我们要做到的是选择若干个 $dep_i$ 来凑出 $\frac{tot}{2}$。

当然，若 $tot$ 为奇数，输出 $-1$。

将数对 $(dep_i,i)$ 按照 $dep_i$ 从小到大排序。然后递归寻找 $\frac{tot}{2}$ 能否满足。具体见代码：

```cpp
// b[x]=1/-1 表示能否凑出 x

int dp(int x,int r){ //表示当前选择点的区间（经过排序）在 [1,r] 中
	if(b[x]!=0) return b[x];
	if(!x) return b[x]=1; 
	if(!r) return b[x]=-1; //x 不等于 0，但已经无数可选
	b[x]=-1;
	while(x<dep[r].fi) --r; //x 小于该点深度，右端点向左移动
	for(int i=r;i;--i) if(dp(x-dep[i].fi,i-1)==1) return b[x]=1;
	return b[x];
}
```

若 $dp(x,n)=1$ 则有解。

记录答案再同样搜一遍，标记经过的点即可。

```cpp
#include<bits/stdc++.h>
#define il inline
#define int long long
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
const int N=1e6+5;

il int wrd(){
	int x=0,f=1; char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1; c=getchar();}
	while(isdigit(c)){x=x*10+c-48,c=getchar();}
	return x*f;
}

int n,cnt,head[N];

struct edge{
	int to,nxt;
}e[N<<1];

il void add(int u,int v){
	e[++cnt]=edge{v,head[u]},head[u]=cnt;
}

int tot,f[N],ans[N];
pii dep[N];
map<int,bool> b;

void dfs1(int u,int fa){
	dep[u]={dep[fa].fi+1,u},f[u]=fa,tot+=dep[u].fi;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v^fa) dfs1(v,u);
	}
}

int dp(int x,int r){
	if(b[x]!=0) return b[x];
	if(!x) return b[x]=1;
	if(!r) return b[x]=-1;
	b[x]=-1;
	while(x<dep[r].fi) --r;
	for(int i=r;i;--i) if(dp(x-dep[i].fi,i-1)==1) return b[x]=1;
	return b[x];
}

void solve(int x,int r){
	if(!x) return;
	while(x<dep[r].fi) --r;
	for(int i=r;i;--i){
		if(b[x-dep[i].fi]==1){
			ans[dep[i].se]=1;
			solve(x-dep[i].fi,i-1);
			return;
		}
	}
}

main(){
	n=wrd();
	for(int i=1;i<n;++i){
		int u=wrd(),v=wrd();
		add(u,v),add(v,u);
	}
	dfs1(1,0);
	sort(dep+1,dep+n+1);
	if((tot&1) || dp(tot/2,n)==-1) return puts("-1"),0;
	solve(tot/2,n);
	for(int i=1;i<=n;++i) printf("%lld ",ans[i]);
	return 0;
}
```

---

