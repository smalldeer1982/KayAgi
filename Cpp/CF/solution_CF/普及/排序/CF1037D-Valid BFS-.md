# Valid BFS?

## 题目描述

[BFS](https://en.wikipedia.org/wiki/Breadth-first_search) 算法定义如下：

1. 给定一个顶点编号为 $1$ 到 $n$ 的无向图。初始化队列 $q$，仅包含顶点 $1$，并将顶点 $1$ 标记为已访问。
2. 从队列 $q$ 的队首取出一个顶点 $v$。
3. 输出顶点 $v$ 的编号。
4. 按任意顺序遍历所有满足条件的顶点 $u$，其中 $u$ 是 $v$ 的邻居且尚未被标记为已访问。将顶点 $u$ 标记为已访问，并插入到队列 $q$ 的队尾。
5. 如果队列不为空，则返回第 2 步。
6. 否则算法结束。

由于每个顶点的邻居选择顺序可以不同，因此 BFS 可能输出多种不同的遍历序列。

本题要求你判断，给定的一个序列是否可能是从顶点 $1$ 开始对给定树进行 BFS 遍历得到的某种合法顺序。这里的“树”指的是一个无向图，任意两点之间恰好有一条简单路径。

## 说明/提示

两个样例测试用例中使用的是同一棵树。

对于这棵树，有两种合法的 BFS 遍历顺序：

- $1, 2, 3, 4$，
- $1, 3, 2, 4$。

序列 $1, 2, 4, 3$ 不对应于任何合法的 BFS 遍历顺序。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4
1 2
1 3
2 4
1 2 3 4
```

### 输出

```
Yes```

## 样例 #2

### 输入

```
4
1 2
1 3
2 4
1 2 4 3
```

### 输出

```
No```

# 题解

## 作者：小粉兔 (赞：27)

短码$^- \Delta ^-$。

思路：输入的$a$数组确定了每个点遍历到的前后顺序关系，应该优先遍历先出现的点。那么我们按照优先级进行BFS，应该要得到和$a$数组一样的遍历顺序。

所以通过输入的数组确定每个节点的优先级，一个节点$x$出现时间越早，它的优先级就越高。定义一个数组$b_i$表示节点$i$在$a$数组中出现的位置。

邻接链表按照优先级排序，这里我用了`vector`这一支持排序的容器，排序的比较函数我使用了lambda表达式。

接下来从节点$1$进行BFS，按照优先级的顺序进行遍历，注意判断不能走父亲节点的边。

最后判断BFS序列是否和输入一致即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,y,a[200001],b[200001],A[200001],c;
vector<int> G[200001];
int que[200001],l,r;
int main(){
	scanf("%d",&n);
	for(int i=1;i<n;++i) scanf("%d%d",&x,&y), G[x].push_back(y), G[y].push_back(x);
	for(int i=1;i<=n;++i) scanf("%d",a+i), b[a[i]]=i;
	for(int i=1;i<=n;++i) sort(G[i].begin(),G[i].end(),[](int x,int y){return b[x]<b[y];});
	que[l=r=1]=1;
	while(l<=r){
		int u=que[l++];
		A[++c]=u;
		for(int i:G[u]) if(b[i]>b[u]) que[++r]=i;
	}
	for(int i=1;i<=n;++i) if(a[i]!=A[i]) return 0*puts("No");
	return 0*puts("Yes");
}
```

---

## 作者：Anguei (赞：9)

不知道你们为什么要用 dfs 判断深度啊？直接根据题意 bfs 模拟就可以了啊。

大体思路是，按照给出的 order 进行 bfs，如果发现无法继续 bfs，输出 no 结束。

核心代码如下。

```cpp
const int N = 200000 + 5;
int n;
bool vis[N];
std::queue<int> order, q;
std::vector<int> g[N];

void bfs() {
    q.push(1); order.pop();
    std::set<int> set;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        vis[u] = true;
        for (const auto &v : g[u]) {
            if (!vis[v]) set.insert(v);
        }
        while (!set.empty()) { // 根据给出的 order，决定下一步广搜从哪里出发
            if (set.count(order.front())) {
                set.erase(order.front());
                q.push(order.front());
                order.pop();
            } else { // 走不动了
                puts("No");
                exit(0);
            }
        }
    }
    puts("Yes");
}

void solution() {
    n = read();
    for (int i = 2; i <= n; ++i) {
        int u = read(), v = read();
        g[u].push_back(v), g[v].push_back(u);
    }
    for (int i = 1; i <= n; ++i) order.push(read());
    if (a[1] != 1) puts("No"), exit(0);
    bfs();
}
```

---

## 作者：sxyugao (赞：6)

怎么没人写 $O(n)$ 呀，赶紧水一发 ~~（其实主要是洛谷咕值贡献掉到 0 了）~~

同步发表于[我的Blog](https://sxyugao.top/p/3396b077.html)，欢迎各位大佬来玩。

---

言归正传。

第一眼看到这题时，大部分人都会想到，既然是树，那么它一定是一层一层地向下 BFS。

也就是说，BFS 序中越后出现的节点，它树上的深度肯定是大于它前面的节点的。

于是照这个思想打完后，发现 Wrong Answer 了。

显然这个思路是有反例的，比如下图的情况：

![](https://i.loli.net/2019/01/29/5c5061bbb4545.png)

输入给的 BFS 序为：1 5 2 3 4 6

如果根据原来的思路输出就是 Yes，然而正确的 BFS 序显然是 1 5 2 6 3 4

再仔细思考一下，发现合法的 BFS 序不仅要满足刚才的深度条件，而且满足每个节点的父亲在 BFS 序中的位置都要不晚于在它后面出现的节点父亲的位置。

这么看貌似时间复杂度是$O(N^2)$的，如何减小复杂度呢？

我们发现一个节点的子树是一个连续的区间，我们直接把每个节点重新编号为它父节点的编号，再把连续相同编号的节点的合并成一个节点即可 ~~(其实可以不用unique的，但是当时没细想）~~ 。合并好以后有一个很好的性质，若输入的序列为合法的 BFS 序，重新编号后的序列元素在原序列中的位置单调递增。这样，时间复杂度就降到了$O(n)$了。

代码详见[博客](https://sxyugao.top/p/3396b077.html)。

---

## 作者：_Give_up_ (赞：4)

## 题目大意
给定一棵个点的有根树，根为 1 号点。再给一个序列 $a$，请你回答这个序列是不是这棵树的合法 BFS 序。

## 思路
首先我们必须知道 DFS 序是什么东东。

BFS 序：在 BFS 过程中访问的节点编号的序列。

可以这样想，在 BFS 序中较早出现的一定是先访问的，所以把每个点连出去的边按出现的前后顺序排个序。再看一下按顺序遍历出来的序列与给出的是否相同就行了。

## Code
```cpp
#include<bits/stdc++.h>
#define N 200010

using namespace std;

typedef long long ll;

int read()
{
    int x = 0,f = 1;
    char c = getchar();
    while(c<'0' || c>'9')
	{
        if(c=='-') f = -1;
        c = getchar();
    }
    while(c>='0' && c<='9')
	{
        x = (x<<3)+(x<<1)+(c^48);
        c = getchar();
    }
    return x*f;
}

int a[N],z[N],k=0,f[N],t[N];
vector <int> v[N];

bool cmp(int x,int y)
{
	return t[x]<t[y];
}

void bfs()
{
	queue <int> q;
	q.push(1);
	while(!q.empty())
	{
		int p = q.front();
		q.pop();
		z[++k] = p,f[p] = 1;
		for(int i=0,l;i<v[p].size();i++)
			if(!f[(l=v[p][i])]) q.push(l);
	}
}

int main()
{
	int n=read();
	for(int i=1;i<n;i++)
	{
		int x=read(),y=read();
		v[x].push_back(y); v[y].push_back(x);
	}
	for(int i=1;i<=n;i++) 
	{
		a[i]=read();
		t[a[i]] = i;
	}
	for(int i=1;i<=n;i++) 
		sort(v[i].begin(),v[i].end(),cmp);
	bfs();
	for(int i=1;i<=n;i++)
		if(z[i]!=a[i]) 
		{
			printf("No\n");
			return 0;
		}
	printf("Yes\n");
}
```

---

## 作者：灵茶山艾府 (赞：3)

思路很多的题。最优雅的方案如下：

首先根据输入构造第一颗树 t1，然后根据 BFS 序构造第二颗树 t2，最后判断 t1 和 t2 是否同构就行了，即对每个点判断两棵树的边是否相同。

AC 代码如下（Golang）：

```go
package main
 
import (
	"bufio"
	. "fmt"
	"os"
	"sort"
)

func main() {
	in := bufio.NewReader(os.Stdin)
	var n, v, w int
	Fscan(in, &n)
	g := make([][]int, n+1)
	g[1] = []int{0}
	for m := n - 1; m > 0; m-- {
		Fscan(in, &v, &w)
		g[v] = append(g[v], w)
		g[w] = append(g[w], v)
	}
 
	g2 := make([][]int, n+1)
	g2[1] = []int{0}
	Fscan(in, &v)
	for q := []int{v}; len(q) > 0; {
		v, q = q[0], q[1:]
		for m := len(g[v]) - 1; m > 0; m-- {
			Fscan(in, &w)
			g2[v] = append(g2[v], w)
			g2[w] = append(g2[w], v)
			q = append(q, w)
		}
	}
 
	for i, e := range g {
		e2 := g2[i]
		if len(e) != len(e2) {
			Print("No")
			return
		}
		sort.Ints(e)
		sort.Ints(e2)
		for j, w := range e {
			if w != e2[j] {
				Print("No")
				return
			}
		}
	}
	Print("Yes")
}
```


---

## 作者：GaoZiyou (赞：3)

[题目链接](https://www.luogu.org/problemnew/show/CF1037D)  

**题目大意：**  
给出一棵 $n$ 个点的树，以及一个序列 $a$，判断 $a$ 是不是该序列的合法 BFS 序。  

对于序列 $a$ 中的每个 $a_i$，记录一个 $p(a_i)=i$。  
可以发现，当且仅当每个结点的后继结点被按照 $p$ 升序排列访问时，整棵树的 BFS 序才有可能与 $a$ 相同。  
于是，对一个点 $u$ 的邻接结点集合按照 $p(v)$ 升序排列后，判断整棵树的 BFS 序是否与 $a$ 完全一致。  
```cpp
#include <cstdio>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

const int N = 2e5 + 10;

int n, a[N], b[N], p[N];
vector<int> G[N];
bool vis[N];

struct cmp {
  bool operator () (const int x, const int y) { return p[x] < p[y]; }
};

void bfs() {
  static queue<int> Q;
  int cnt = 0;
  Q.push(1);
  while (!Q.empty()) {
    int u = Q.front(); Q.pop();
    vis[u] = true;
    b[++cnt] = u;
    for (int i = 0, v; i < static_cast<int>(G[u].size()); ++i) {
      v = G[u][i];
      if (vis[v]) continue;
      Q.push(v);
    }
  }
}

int main() {
  scanf("%d", &n);
  for (int i = 1, u, v; i < n; ++i) {
    scanf("%d%d", &u, &v);
    G[u].push_back(v);
    G[v].push_back(u);
  }
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
    p[a[i]] = i;
  }
  for (int i = 1; i <= n; ++i)
    sort(G[i].begin(), G[i].end(), cmp());
  bfs();
  for (int i = 1; i <= n; ++i)
    if (a[i] != b[i]) {
      puts("No");
      return 0;
    }
  puts("Yes");
  return 0;
}
```

---

## 作者：Gold14526 (赞：1)

# CF1037D Valid BFS?题解
## 1、题意简化
给定一棵根节点为 $1$ 的多叉树和一个序列，问是否有一种从根节点开始的 BFS 序列与其给出的相同。
## 2、主要思路
#### 2.1、建树
读入的每一条边以无向边存储（互相各连一条），在建树时，从根节点开始，枚举该节点所能够到达的节点，如果这个节点已被使用，则跳过，否则使其成为自己的子节点，并使这个子节点进行同样的操作。判断节点是否被使用可以打标记判断。

另外，因为这是多叉树，所以存储子节点需要挂链。
#### 2.2、BFS
BFS 序列合法的条件：

根节点第一个出现，先出现的节点其子节点先出现，后出现的节点其子节点后出现，出现所有节点。

我们以模拟 BFS 过程的方式判断序列是否合法。

先将根节点 $1$ 入队。每次取出队首，在输入序列中往后找队首的子节点数个节点，判断是否全是队首的子节点，如果不是直接返回```No```，否则，将所有子节点按照输入顺序加入队尾。

如果 BFS 结束时仍未发现不合法情况，返回```Yes```。
## 3、Code（带有少量注释）
```cpp
#include<bits/stdc++.h>
using namespace std;
int num;
char ch;
int read()//快速读入 
{
	num=0;
	ch=getchar();
	while(ch<'0'||ch>'9')
	{
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		num=(num<<1)+(num<<3)+ch-'0';
		ch=getchar();
	}
	return num;
}
struct node{
	int to,next;
}l[399999];	//邻接表（用于存输入的边） 
int head[200001];
struct tree{
	int head,son;
}t[200001];//存多叉树的节点 
struct point{
	int id,next;
}pts[200001];//存多叉树节点的子节点 
int ts;
bool f[200001];
struct que{
	int a[1000001],h,t;
	void clear(){h=0,t=-1;}
	bool empty(){return t<h;}
	int front(){return a[h];}
	void push(int x){a[++t]=x;}
	void pop(){++h;}
	int size(){return t-h+1;}
}q;//手写队列 
int a[200001],n;
bool check()//BFS
{
	q.clear();
	q.push(1);
	if(a[1]!=1)return 0;
	int m=1,p;
	while(!q.empty())
	{
		p=q.front();
		q.pop();
		for(int i=1;i<=t[p].son;++i)		//
		{									//
			f[a[++m]]=1;					//
			q.push(a[m]);					//
		}									//判断输入是否合法 
		for(int i=t[p].head;i;i=pts[i].next)//
		{									//
			if(!f[pts[i].id])return 0;		//
		}									// 
	}
	return 1;
}
void build(int x)//建树 
{
	f[x]=1;
	for(int i=head[x];i;i=l[i].next)
	{
		if(f[l[i].to])continue;
		++t[x].son;							//
		pts[++ts]=point{l[i].to,t[x].head};	//挂链 
		t[x].head=ts;						//
		build(l[i].to);
	}
}
int d;
void line(int x,int y)//建边 
{
	l[++d]=node{y,head[x]};
	head[x]=d;
}
int main()
{
	n=read();
	int x,y;
	for(int i=1;i<n;++i)
	{
		x=read();
		y=read();
		line(x,y);
		line(y,x);
	}
	build(1);
	memset(f,0,sizeof(f));
	for(int i=1;i<=n;++i)
	{
		a[i]=read();
	}
	if(check())
	{
		puts("Yes");
	}
	else
	{
		puts("No");
	}
	return 0;
}
```
## 4、写在最后
个人认为这道题作为蓝题是虚高的，应是绿题。

主要这道题思维难度也不高，代码实现也并不复杂，考的只有多叉树基础和 BFS。

最后，如果对题解有什么问题、建议或意见，可以在评论区说。

---

## 作者：Xx_queue (赞：1)

[题目链接](https://www.luogu.org/problem/CF1037D)

比较容易的一道题目，直接模拟树的BFS过程就可以啦；

这里我采用了一种神奇的方法，大家可以看一看：

用DFS搜索出每个节点的儿子个数，以及每个节点的父亲；

再直接用队列维护，模拟一下过程，对于每个点，判断当前节点的儿子个数是否符合之前所搜索出来的，

并判断其父亲是否正确，正确就又插入队列中，错误直接判断错误；

虽然慢了一点，但也不失为一个不错的方法呢！主要是灵活运用了BFS序的有关性质；

具体细节见代码：
```cpp
 1 #include <bits/stdc++.h>
 2 #define N 200000+5
 3 using namespace std;
 4 int n,flag,vis[N],son[N],fa[N];
 5 vector <int> edge[N];
 6 queue <int> q;
 7 void dfs(int u)
 8 {
 9     vis[u]=1;
10     for(int i=0;i<edge[u].size();i++)
11     {
12         int now=edge[u][i];
13         if(!vis[now])
14         {
15             vis[now]=1;
16             fa[now]=u;
17             son[u]++;
18             dfs(now);
19         }
20     }
21 }
22 int main()
23 {
24     scanf("%d",&n);
25     for(int i=1;i<n;i++)
26     {
27         int u,v;
28         scanf("%d%d",&u,&v);
29         edge[u].push_back(v);
30         edge[v].push_back(u);
31     }
32     dfs(1);
33     int a;
34     scanf("%d",&a);
35     if(a!=1) flag=1;
36     q.push(a);
37     memset(vis,0,sizeof(vis));
38     vis[a]=1;
39     while(!q.empty())
40     {
41         int now=q.front();
42         q.pop();
43         int cnt=son[now];
44         for(int i=1;i<=cnt;i++)
45         {
46             scanf("%d",&a);
47             if(vis[a])
48             {
49                 flag=1;
50                 continue;
51             }
52             else
53             {
54                 vis[a]=1;
55                 q.push(a);
56                 if(fa[a]!=now) flag=1;
57             }
58         }
59     }
60     if(flag)printf("No");
61     else printf("Yes");
62     return 0;
63 }
```

---

## 作者：彭骐飞 (赞：1)

我好菜啊qwq

我在赛场上想到了一个奇怪的方法，然后巧妙而又完美地避开了简单的正解qwq

题目意思就不赘述了，我当时非常$naive$地认为只要后面的深度$ \ge $前面的深度。

然后就很愉快地$WA$了qwq[42386330](http://codeforces.com/contest/1037/submission/42386330)

接着，我茅塞顿开，发现自己$naive$了。

看着代码，因为我写了个$dfs$求深度和父节点，然后我又不舍得删掉，进行了一番分析后发现了一个玄妙的方法：

（敲黑板）我发现自己的代码之所以$WA$了，是因为一种长成这样的形态：

![1](https://cdn.luogu.com.cn/upload/pic/31885.png)

此时，虽然满足后面深度$ \ge $前面深度，但由于$2$的子节点在$3$的前面，所以$5$在$4$前是不合法的（$naive$ qwq）。

对着这个错误的，假的代码，我想出了这么个东西：

因为先访问的节点的子节点（直系子节点，以后亦是这个意思）也是先访问的，所以这个好像也是个队列。

所以，我们可以开一个队列，来模拟这个事情。有人就说，搞什么啊，不又回到基本的$BFS$了吗？但是，这个题目的特别就在于每一个节点的子节点是按随机的顺序加入到队列，但这个顺序又决定了这些节点子节点的顺序，所以说我对于一个节点的每个儿子是不能区分的，而只能在儿子的儿子把每一个儿子的所有儿子相对区分出来（好像有点抽象啊）。

举个例子，
![2](https://cdn.luogu.com.cn/upload/pic/31962.png)
在这个图中，如果$1$先入了队，那我们不能在搜索它的子节点时把$2$放在$3$的前面，否则就不符合题意了。所以我们怎么排$2$和$3$继续往后搜呢？

很简单，我们边做边判断。

在此时，入队的一定是$2$或$3$，所以我们读入下一个入队的，判断一下，自然就知道先访问的哪个节点了。比如$BFS$序中下一个是$3$，那我们就把$3$的子节点丢到队尾就行了。后面又来了个$2$，我们就把$2$的子节点丢到队尾，然后就可以区分相对顺序。

但怎么把不同节点的新一层子节点区分出来呢？还要写一大堆的东西保留分界线吗？

我当时脑子一抽，想到了个玩意儿，叫$queue<vector<int>>$。qwq

把每个节点的子节点预处理出来，存在一个$vector$数组$son$里，然后先判一下$1$，若合法则将$son[1]$插到$q$里。

然后当我们要判有没有$x$时，只要在$q.front()$里$lower_bound()$一下（因为我太弱了，写不好$vector$的二分函数），判断是不是$x$，不是就$-1$，否则就删掉。

但删掉的复杂度是不对的，因为$vector$的删除是线性的。接着，我脑子又一抽，问了一个问题：
![3](https://cdn.luogu.com.cn/upload/pic/31965.png)
所以说询问的不重复，而$vector$也不重复，所以说一个点只会被出队（$vector$）一次。

那还要删除干嘛，直接搞个计数器累加一下看看等不等于$size$不就行了吗。

然后，我开心地写完了，然后开心地交了上去，$WA$掉了（[42393717](http://codeforces.com/contest/1037/submission/42393717)）。

我又开心地发现，我的$lower_bound$假掉了，因为我没按子节点排序。qwq

然后，我又开心地改掉了，然后开心地交了上去，又$WA$掉了（[42396238](http://codeforces.com/contest/1037/submission/42396238)）。

我又开心地发现，如果堆了一些叶子节点的$vector$，$size$就是$0$，而我后面在对一个空$vector$在$lower_bound$，所以就$WA$了。qwq

然后就好了。

代码：（[42398197](http://codeforces.com/contest/1037/submission/42398197)）
```cpp
#pragma comment (linker,"/STACK:1024000000") 
#pragma GCC optimize(2)
#pragma GCC target(arch=corie7-acx)
#include<bits/stdc++.h>
using namespace std;
int n;
vector<int> E[200001];
vector<int> son[200001];
int fa[200001];
void dfs (int u)
{
	for (auto v:E[u])
	{
		if (v==fa[u]) continue;
		son[u].push_back(v);
		fa[v]=u;
		dfs(v);
	}
	return;
}
int u,v;
int x,m;
queue<vector<int>> q;
vector<int> t;
int num,sum;
vector<int>::iterator it;
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n-1;i++)
	{
		scanf("%d%d",&u,&v);
		E[u].push_back(v);
		E[v].push_back(u);
	}
	dfs(1);
	scanf("%d",&x);
	if (x!=1) return puts("No"),0;
	q.push(son[1]);
	t=q.front();
	sort(t.begin(),t.end());
	for (int i=2;i<=n;i++)
	{
		scanf("%d",&x);
		while (sum==t.size())
		{
			q.pop();
			if (q.empty()) return puts("No"),0;
			t=q.front();
			sort(t.begin(),t.end());
			sum=0;
		}
		it=(lower_bound(t.begin(),t.end(),x)+1);
		//printf("%d ",x);
		num=it-t.begin();
		//printf("%d:%d\n",num,t[num-1]);
		if (x!=t[num-1]) return puts("No"),0;
		sum++;
		q.push(son[x]);
	}
	printf("Yes");
	return 0;
}
```
这题细节好多啊（或许是我写的作死吧）。

---

## 作者：风浔凌 (赞：1)

啊。。。这个题就是一个bfs。。。。。。  
~~然而比赛时我竟然dfs bfs傻傻分不清？？？~~  
因为我们要找符合询问的序列，所以我们可以按照询问的序列进行排序，然后队列bfs之后看序列和询问序列是否一样来判断yes或者no。
为了方便排序，我们可以开一个pair，第一维存放在同一个父亲的所有儿子里面的优先度（根据询问序列进行排序），第二位存放id;  
还有就是注意如果询问序列中出现重复的数字，那么一定不存在合法序列。  
然后比赛有note更新说根节点是一。  
然后就没有然后了，记得添加的时候是双向边添加两遍。  
代码如下：
```c
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#define MAXN 200010
using namespace std;
vector<pair<int,int> >vec[MAXN];
int q[MAXN],order[MAXN],a[MAXN],done[MAXN];
int n,l,r;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<n;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		vec[u].push_back(make_pair(0,v));
		vec[v].push_back(make_pair(0,u));
	}
	for(int i=0;i<n;i++)
	{
		scanf("%d",&q[i]);
		order[q[i]]=1;
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<vec[i].size();j++)
		  vec[i][j].first=order[vec[i][j].second];
		sort(vec[i].begin(),vec[i].end());
	}
	int l=0,r=0;
	a[r++]=1;
	done[1]=1;
	while(l<r)
	{
		int v=a[l];
		for(int k=0;k<vec[v].size();k++)
		{
			pair<int,int>e=vec[v][k];
			if(done[e.second]) continue;
			done[e.second]=1;
			a[r++]=e.second;
		}
		l++;
	}
	for(int i=0;i<n;i++)
	{
		if(a[i]!=q[i])
		{
			printf("No\n");
			return 0;
		}
	}
	printf("Yes\n");
	return 0;
}
```

---

## 作者：happybob (赞：0)

## 题意

给定一棵树和一个序列，问这个序列是否是一个可能的 BFS 序列。

## 做法

我的代码应该是非常长的了。

可以考虑模拟，从根节点开始往下，每层判断上一层是否所有结点都遍历过，以及判断出队顺序是否有误，具体可以看代码，欢迎 hack。

复杂度应该为线性。

对于 BFS 序列里每一个点，判断之前的点最后一层是否已满，如果未满，显然应该继续填。

此外还应该判断出队顺序。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;

int n, a[N], fa[N], dep[N];
vector<int> G[N];
int id[N], cnt[N];

void dfs2(int u, int fa, int depth)
{
	dep[u] = depth;
	for (int i = 0; i < G[u].size(); i++)
	{
		int j = G[u][i];
		if (j == fa) continue;
		dfs2(j, u, depth + 1);
	}
}


void dfs(int u, int Fa)
{
	fa[u] = Fa;
	for (int i = 0; i < G[u].size(); i++)
	{
		int j = G[u][i];
		if (j == Fa) continue;
		dfs(j, u);
	}
}

struct Node
{
	int val, cnt;
	Node(int _v, int _c): val(_v), cnt(_c){}
};

deque<Node> mp[N];

bool bfs()
{
	memset(id, -1, sizeof id);
	queue<int> q;
	q.push(1);
	for (int i = 1; i <= n; i++)
	{
		cnt[dep[i]]++;
	}
	mp[1].push_front(Node(1, G[1].size()));
	for (int i = 0; i < G[1].size(); i++)
	{
		int j = G[1][i];
		if (j != fa[1])
		{
			id[j] = 1;
		}
	}
	cnt[1] = 0;
	int last = 1;
	for (int i = 2; i <= n; i++)
	{
		int v = a[i];
		if (id[v] == -1)
		{
			//printf("1331\n");
			return false;
		}
		q.push(v);
		//id[v] = -1;
		for (int j = 0; j < G[v].size(); j++)
		{
			int k = G[v][j];
			if (k != fa[v])
			{
				id[k] = v;
			}
		}
		if (mp[last].empty()) last = dep[v];
		if (dep[v] != last)
		{
			if (dep[v] > last + 1) 
			{
				//if (n > 100) printf("%d\n", 12312);
				return false;	
			}
			if (dep[v] == last + 1)
			{
				//printf("%d %d %d\n", v, mp[last].front().val, mp[last].front().cnt);
				if (cnt[last]) 
				{
					//printf("1333\n");
					return false;	
				}
				if (mp[last].front().cnt <= 0)
				{
					mp[last].pop_front();
				}
				if (id[v] != mp[last].front().val) 
				{
					//printf("1333\n");
					return false;	
				}
				mp[last][0].cnt--;
				if (mp[last].front().cnt <= 0)
				{
					mp[last].pop_front();
				}
				if (mp[last].empty()) last = dep[v];
				cnt[dep[v]]--;
			}
		}
		else
		{
			cnt[last]--;
		}
		if (mp[last].empty()) last = dep[v];
		id[v] = -1;
		if (G[v].size() - 1) mp[dep[v]].push_back(Node(v, G[v].size() - 1));
	}
	return true;
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	dfs(1, -1);
	dfs2(1, -1, 1);
	set<int> p;
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]), p.insert(a[i]);
	if (a[1] != 1 || p.size() != n)
	{
		printf("No\n");
		return 0;
	}
	if (bfs()) printf("Yes\n");
	else printf("No\n");
	return 0;
}
```


---

## 作者：Nero_Claudius (赞：0)

不管怎么说，这都不是道紫题吧。。。

------------

这里采用的思想有点类似轻重链剖分。

我们按照每个节点在序列里面出现的顺序，把每一个节点连出去的边都排一个序。

这样（如果序列没错）肯定会按照序列的方式遍历完全图。

所以我们就按照这个图跑一遍BFS。

一边BFS一边查看是否符合。

程序的速度不算特别快，最优解rank11。（写丑了）

------------

AC代码如下：

`1925ms 9776kb`

```cpp
#include<bits/stdc++.h>

using namespace std;

namespace StandardIO{

	template<typename T>inline void read(T &x){
		x=0;T f=1;char c=getchar();
		for(;c<'0'||c>'9';c=getchar())if(c=='-')f=-1;
		for(;c>='0'&&c<='9';c=getchar())x=x*10+c-'0';
		x*=f;
	}

	template<typename T>inline void write(T x){
		if(x<0)putchar('-'),x*=-1;
		if(x>=10)write(x/10);
		putchar(x%10+'0');
	}

}

using namespace StandardIO;

namespace Solve{
	
	const int N=200200;
	int n,cnt;
	int a[N],b[N],vis[N];
	vector<int>G[N];
	
	inline bool cmp(int x,int y){
		return a[x]<a[y];
	}
	
	inline void solve(){
		read(n);
		for(register int i=1;i<=n-1;++i){
			int u,v;
			read(u),read(v);
			G[u].push_back(v),G[v].push_back(u);
		}
		for(register int i=1;i<=n;++i){
			read(b[i]),a[b[i]]=i;
		}
		for(register int i=1;i<=n;++i){
			sort(G[i].begin(),G[i].end(),cmp);
		}
		queue<int>q;
		q.push(1);
		while(!q.empty()){
			int now=q.front();q.pop();
			if(vis[now])continue;
			vis[now]=1;
			if(b[++cnt]!=now){
				puts("No");
				return;
			}
			for(register int i=0;i<G[now].size();++i){
//				cout<<G[now][i]<<endl;
				q.push(G[now][i]);
			}
		}
		puts("Yes");
	}
}

using namespace Solve;

int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	solve();
}


```

---

## 作者：tnvj86 (赞：0)

主要的思路就是将待判断的序列一个一个读进来的时候，确保它的各个元素是符合BFS顺序的。主要就是2个步骤
1. 读入邻接表
2. 对给定的序列进行bfs模拟，参照邻接表判断正确与否


在读入邻接表的过程中，把每个节点的子节点都放到一个set当中，所以邻接表是一个set的数组。因为数据规模很大，不能用邻接矩阵，否则会MLE。

对给定的序列进行bfs模拟。模拟过程和普通的bfs没什么区别，都是用queue，一个一个入队，然后看这个头节点有几个子节点，然后读入相应数量的子节点，并参照邻接表进行判断，是合法的子节点则从当前头节点对应的子节点集合中删去，如果序列是正确的，那么应该删空，否则肯定是错误的序列。 


```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <set>
#include <cstring>
using namespace std;
#define MAXN 200005
int n;
int que[MAXN];
int main(){
    cin>>n;
    set<int> a[MAXN];
    memset(que,0,sizeof(que));
    for(int i=1;i<n;i++){
        int x,y;
        cin>>x>>y;
        a[x].insert(y);
        a[y].insert(x);
    }
    int front = 1;
    int rear = 1;
    que[front] = 1;
    int head;
    int tmp;
    cin >> tmp; // skip the input of root node
    if(tmp!=1){cout<<"No"<<endl;return 0;}
    while(front <= rear){
        head=que[front++];
        int cnt=a[head].size();
        for(int i=1;i<=cnt;i++){
            int x;
            cin >> x;
            if(a[head].count(x)){
                a[head].erase(x);
                a[x].erase(head);
                que[++rear] = x;
            }
        }
        if(!a[head].empty()){
            cout<<"No"<<endl;
            return 0;
        }
    }    
    cout<<"Yes"<<endl;
    return 0;
}
```


---

## 作者：BLUESKY007 (赞：0)

题目大意:给定一个$n(1\leq n\leq 2\cdot10^5)$个节点的树的$n-1$条边和这棵树的一个$BFS$序$a_1,a_2,\dots,a_n$,判断这个$BFS$序是否是一个从节点$1$开始的合法$BFS$序,若合法则输出$Yes$,否则输出$No$  
题目核心问题是判断给出的$BFS$序的合法性,根据$BFS$的定义,每个节点的所有子节点在加入队列时应当是连续的,且同深度的节点的子节点入队顺序应该整体与父节点入队顺序相同,不妨把每个节点的所有子节点在给定的$BFS$序列中的顺序看做连续的区间.  
考虑到$BFS$序列不合法的原因有以下可能:  
- $a_1\neq 1$  
- 存在$i,j$满足$i<j$且$dep[a_i]>dep[a_j]$  
- 存在$i,j$满足$i\neq j$且$a_i=a_j$  
- 存在$i,j$满足$i<j$且$a_i$的某个子节点$u$与$a_j$的某个子节点$v$满足在$BFS$序中$u$在$v$之后  

处理思路:对于给出的树先跑一边$BFS$求每个点的$dep$和其子节点在$a$序列中的位置区间,按照上述四种情况进行判断.  

下面放$AC$代码$\downarrow\downarrow\downarrow$  
```cpp
#include<cstdio>//CF1037D
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#include<queue>

using namespace std;

const int N=200010,NN=400020;

struct interval{
	int l,r;
};

int fr[N],edge[NN],nxt[NN],n,dep[N],vis[N],app[N],a[N],fa[N],dy[N];

interval il[N];

queue<int>q;

void bfs(){
	q.push(1);
	dep[1]=1;
	int u;
	while(!q.empty()){
		u=q.front();
		vis[u]=1;
		q.pop();
		int now=fr[u],v;
		while(now){
			v=edge[now];
			if(!vis[v]){
				dep[v]=dep[u]+1;
				fa[v]=u;
				q.push(v);
				il[u].l=min(il[u].l,dy[v]);
				il[u].r=max(il[u].r,dy[v]);
			}
			now=nxt[now];
		}
	}
}

bool check(){
	if(a[1]!=1){
		return false;
	}
	int nowdep;
	for(int i=1;i<=n;i++){
		if(dep[a[i]]<nowdep||app[a[i]]){
			return false;
		}
		else{
			app[a[i]]=1;
			nowdep=dep[a[i]];
		}
	}
	int tr=1;
	for(int i=1;i<=n;i++){
		if(il[a[i]].l==200010){
			continue;
		}
		if(il[a[i]].l>tr){
			tr=il[a[i]].r;
		}
		else{
			return false;
		}
	}
	return true;
}

int main(){
	scanf("%d",&n);
	int u,v;
	for(int i=1;i<=n;i++){
		il[i].l=200010;
		il[i].r=0;
	}
	for(int i=1;i<n;i++){
		int j=i+n;
		scanf("%d%d",&u,&v);
		edge[i]=v;
		nxt[i]=fr[u];
		fr[u]=i;
		edge[j]=u;
		nxt[j]=fr[v];
		fr[v]=j;
	}
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		dy[a[i]]=i;
	}
	bfs();
	if(check()){
		printf("Yes\n");
		return 0;
	}
	else{
		printf("No\n");
		return 0;
	}
	return 0;
} 
```

---

