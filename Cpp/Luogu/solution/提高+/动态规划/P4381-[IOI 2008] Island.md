# [IOI 2008] Island

## 题目描述

你准备浏览一个公园，该公园由 $N$ 个岛屿组成，当地管理部门从每个岛屿 $i$ 出发向另外一个岛屿建了一座长度为 $L_i$ 的桥，不过桥是可以双向行走的。同时，每对岛屿之间都有一艘专用的往来两岛之间的渡船。相对于乘船而言，你更喜欢步行。你希望经过的桥的总长度尽可能长，但受到以下的限制：

- 可以自行挑选一个岛开始游览。
- 任何一个岛都不能游览一次以上。
- 无论任何时间，你都可以由当前所在的岛 $S$ 去另一个从未到过的岛 $D$。从 $S$ 到 $D$ 有如下方法：
  - 步行：仅当两个岛之间有一座桥时才有可能。对于这种情况，桥的长度会累加到你步行的总距离中。
  - 渡船：你可以选择这种方法，仅当没有任何桥和以前使用过的渡船的组合可以由 $S$ 走到 $D$ (当检查是否可到达时，你应该考虑所有的路径，包括经过你曾游览过的那些岛)。

注意，你不必游览所有的岛，也可能无法走完所有的桥。

请你编写一个程序，给定 $N$ 座桥以及它们的长度，按照上述的规则，计算你可以走过的桥的长度之和的最大值。

## 说明/提示

**样例解释**：

![样例图示](https://cdn.vijos.org/fs/c82895f1d6f84d5756610176662d6ee644c3e55e)

样例 $N=7$ 座桥，分别为 $(1-3), (2-7), (3-4), (4-1), (5-1), (6-3)$ 以及 $(7-2)$。注意连接岛 $2$ 与岛 $7$ 之间有两座不同的桥。

其中一个可以取得最大的步行距离的方法如下：

- 由岛 $5$ 开始。
- 步行长度为 $9$ 的桥到岛 $1$。
- 步行长度为 $8$ 的桥到岛 $3$。
- 步行长度为 $4$ 的桥到岛 $6$。
- 搭渡船由岛 $6$ 到岛 $7$。
- 步行长度为 $3$ 的桥到岛 $2$。

最后，你到达岛 $2$，而你的总步行距离为 $9+8+4+3=24$。

只有岛 $4$ 没有去。注意，上述游览结束时，你不能再游览这个岛。更准确地说：

- 你不可以步行去游览，因为没有桥连接岛 $2$ (你现在的岛) 与岛 $4$。
- 你不可以搭渡船去游览，因为你可由当前所在的岛 $2$ 到达岛 $4$。一个方法是：走 $(2-7)$ 桥，再搭你曾搭过的渡船由岛 $7$ 去岛 $6$，然后走 $(6-3)$ 桥，最后走 $(3-4)$ 桥。

**数据范围**：

对于 $100\%$ 的数据，$2\leqslant N\leqslant 10^6,1\leqslant L_i\leqslant 10^8$。


## 样例 #1

### 输入

```
7
3 8
7 2
4 2
1 4
1 9
3 4
2 3```

### 输出

```
24```

# 题解

## 作者：TEoS (赞：129)

一道不错的题目，思路比较灵活，但码量不大，在现在的时空限制下也基本不会出现被卡的情况，总体还是很好的。

当时看到题目的颜色我就**了，刚开始没有思路，想参考题解又发现大佬们要么讲得十分深奥要么讲得十分简略，不过后来有了思路之后写起来也不会太难。所以我就写一篇~~自认为~~浅显易懂的题解吧。

可能和有些大佬实现方法相同，不过我会尽可能讲得清晰的！

------------
实现流程：dfs+树形DP+单调队列

思路：
 
由于这个公园有$N$座岛屿和$N$座桥，就相当于一个由$N$个节点和$N$条边构成的无向图。显然，这样的一个无向图就是一个基环树森林。

因此，根据题意，要使经过的总路径最长且每棵基环树都只能经过一次，显然答案就是每棵基环树的最长链，或者也可以叫直径的和。如何求基环树的直径呢？和求树的直径类似，只不过要多考虑这个环罢了。对于每个基环树，我们先把这个环看做一个整体并作为这棵基环树的根节点，就成为了一棵普通的树，之后再对环进行讨论。基环树的直径显然有下面两种可能：

1.  在“根节点”的某一棵子树中
1.  经过“根节点”，在“根节点”的某两棵子树中

对于上面的两种情况，我们分类讨论，最后取大的答案就可以了。在处理这些之前，应该先找出当前基环树的环，这步用dfs实现就可以。找出来后，将它们作上标记，方便之后的操作。

对于第一种情况，我们对“根节点”的每棵子树单独讨论，求每棵子树的直径，取其中最大的答案就可以了。“根节点”的每棵子树也就是以环上的每个节点为根的子树。这步可以用树形DP来解决，并且在解决这种情况的同时，还能处理出以环上每个节点为起点，走向以其为根的子树，能够到达的最远距离，为处理下一种情况做准备。这里将这个数据存入$d$数组，即$d_i$代表$i$节点对应的值。注意，为了方便，在之前找出环并标记之后，环上的节点都以在环上的次序命名，即$i$节点实际对应的是环上的第$i$个

对于第二种情况，显然对于这种情况，我们需要找到环上的两个节点$i,j$，使得$d_i+d_j+dist_{i,j}$最大，其中$dist_{i,j}$表示节点$i,j$在环上的距离。如果一个个枚举的话，显然时间复杂度太大，不可行。这里可以断开环将断开后的链复制到两倍的长度，用单调队列进行优化，在下面会进行详细讲解。

上面的思路可能讲得比较笼统，如果没看懂可以接下去看。

下面给出具体实现流程。


------------
具体实现流程：

**1、输入**

输入就是最普通的邻接表存图，就不多说了，直接上代码。

输入代码：
```cpp
ll n,tot;
ll edge[2*N],head[N],ver[2*N],Next[2*N];

il void add(int x,int y,int z)
{
    edge[++tot]=z,ver[tot]=y,Next[tot]=head[x],head[x]=tot;
}//邻接表插入

cin>>n;
for(int i=1;i<=n;i++)
{
    int y,z;
    scanf("%d %d",&y,&z);
    add(i,y,z);
    add(y,i,z);//无向边成对存储
}
```

------------
**2、dfs找环**

就是基本的深搜，深搜的同时标记是否走过，走到走过的节点即为找到了环，在这里我们把这个节点叫做环的衔接点。如何剔出这个环呢？在这里定义一个bool类型的dfs函数，当找到环时返回值为1，回溯时一直到第三次走到衔接点时，将返回值恢复为0，就可以解决这个问题。

我们要对环上的节点存储一些信息。我们将环的衔接点定为$1$号节点，按回溯方向依次为$2,3,...,n$号节点，表示这个环由$n$个节点组成。对于$i$号节点，该节点的原始编号，即输入时的编号为$x$，我们要存储以下信息：

- $v_x=1$，表示这个节点在dfs时被走过了。特别的，若该节点是环的衔接点，则令$v_x=2$，用来辨识衔接点。这个标记在dfs时走过的所有节点都要做。
- $v2_x=1$，表示这个节点所在的基环树已经走过了。这个标记之后所有节点都要做，目的是判断一棵基环树是否走过，在这里先给环上的点标记是为了后面方便。
- $r_i=x$，表示环上的$i$号节点的原始编号为$x$。
- $s_i=s_{i-1}+dist_{i-1,i}$，此时$dist_{i-1,i}$就等于当前遍历到的边的长度。特别的，由于后面的操作要断环并复制链，复制$s$数组时为了保证复制数据的正确性，要在$0$号位置存储一个数据，使得$s_0=s_1-dist_{0,1}$。这个步骤到后面复制的时候可以更好的理解。

这里有一个问题，为什么还要额外开一个$v2$数组来判定是否走过呢？因为在$v$数组只是用来判定dfs时是否走过，而dfs时并不是所有节点都会被遍历到，而$v2$数组在之后的操作中可以保证每个节点都被遍历到，因此可以作为一棵基环树是否走过的依据。

在dfs时还有一个点要注意，因为遍历时要保证走向的下一个节点不是上一个节点，因此我们要对此进行特判。怎么特判呢？原来我有一个想法，存储上一个节点的编号，保证不再走到这个节点。然而看了样例之后我就把这个想法否决了（这个样例真的良心，自己看看就知道原因了）。于是只能把思路往边上放。

众所周知，邻接表存无向图时是将同一条边拆作两条有向边分开存的，而指向这两条有向边的指针的数值是相邻的，并且其中偶数较大，奇数较小。利用这个特点，我们就可以判断当前循环到的边是否是刚刚走过的这条边。操作如下：

```cpp
if(i!=((la-1)^1)+1)//la指向刚刚走过的那条边，i指向现在循环到的这条边
//当这个条件成立时，说明当前循环到的边不是刚刚走过的那条边
//((x-1)^1)+1，指向与x相邻的数y，并且x,y中偶数较大。例如，若x=3，则y=4；若x=4，则y=3。
//原理请读者自己思考
```


dfs找环代码：
```cpp
ll cnt;
ll v[N],v2[N],r[N],s[N];

il bool dfs(int now,int la)
{
    if(v[now]==1)
    {
        v[now]=2,r[++cnt]=now,v2[now]=1;
        return 1;//返回值改为1
    }//找到衔接点
    v[now]=1;//维护访问数组
    for(int i=head[now];i;i=Next[i])
        if(i!=((la-1)^1)+1 && dfs(ver[i],i))//如果当前边不是上一条边并且当前节点在环上
        {
            if(v[now]!=2)//当前节点不是衔接点
                r[++cnt]=now,v2[now]=1,s[cnt]=s[cnt-1]+edge[i];
            else//是衔接点
            {
                s[st-1]=s[st]-edge[i];
                return 0;//返回值改为0
            }
            return 1;//返回1
        }
    return 0;	
}
```


------------
**3、处理第一种情况**

对于环上的每个节点，求以其为根的子树的直径。这就是求树的直径的模板问题了，用树形DP就可以解决，不懂的可以[点击食用](https://www.cnblogs.com/TEoS/p/11351462.html)，这里就不赘述了。

对于代码有一点要说明的，因为在这里$cnt$的计算是没有重置的，因此会一直加下去，所以在dp前要先存储起始值。

处理第一种情况代码：
```cpp
ll ans,ans2;//ans存储当前子树的直径，ans2存储第一种情况的答案
ll d[N];

st=cnt+1,ans2=0;
il void tree_dp(int now)
{
    v2[now]=1;
    for(int i=head[now];i;i=Next[i])
    {
        int y=ver[i];
        if(v2[y])
            continue;
        tree_dp(y);
        ans=max(ans,d[now]+d[y]+edge[i]);
        d[now]=max(d[now],d[y]+edge[i]);
    }
}//树形DP求树的直径

for(int i=st;i<=cnt;i++)
{
    ans=0;//初始化
    tree_dp(r[i]);
    ans2=max(ans2,ans);//找出最大的答案
}
```


------------
**4、处理第二种情况**

找出满足$d_i+d_j+dist_{i,j}$最大的$i,j$，枚举显然会超时。对于这类环形问题，有一种比较常用的做法就是从某个点断开环并复制为一条两倍长度的链。复制过程只要将一些关键信息再存一遍就可以了。于是问题可以等价为：在一条长度$2n$的链上，找到两个满足$abs(i-j)\leq n$的节点$i,j$，使得$d_i+d_j+dist_{i,j}$最大。

这个问题是不是一脸可以用单调队列优化的亚子？~~要你寡~~ 根据单调队列的思想，及时排除一定不是最优的决策。因为要找的是最大的$d_i+d_j+dist_{i,j}$，其中$dist_{i,j}$即为$s_i-s_j(j<i)$。整理后即为：$d_i+s_i+d_j-s_j$。

对于每个节点$i$，显然如果一个节点$j(j<i)$满足$d_j-s_j\leq d_i-s_i$，那么根据最优性，$j$是一定不会被选作最终决策的，因此可以将其从答案队列中删除。讲到这里，实现起来就很简单了。

对于代码有一点要说明的，因为$cnt$没有重置，根据定义环上节点的数量为$cnt-st+1$，因此断环复制后的节点范围即为$st~cnt+cnt-st+1$。这样，节点$i$对应的另一个节点即为$i+cnt-st+1$。

处理第二种情况代码：

```cpp
int ans3;
ll dp[2*N];

ans3=0;
for(int i=st;i<=cnt;i++)
{
    dp[i+cnt-st+1]=dp[i]=d[r[i]]; 
    s[i+cnt-st+1]=s[i+cnt-st]+s[i]-s[i-1]; //和第2步递推s数组同理，s[i]-s[i-1]即为两点之间的距离
}//复制环
deque<int> q;
for(int i=st;i<=2*cnt-st+1;i++)//对复制后的链进行遍历
{
    while(q.size() && q.front()<=i-cnt+st-1)
        q.pop_front();//排除超出范围的决策
    if(q.size()) 
        ans3=max(ans3,dp[i]+dp[q.front()]+s[i]-s[q.front()]);//更新答案
    while(q.size() && dp[q.back()]-s[q.back()]<=dp[i]-s[i])
        q.pop_back();//排除过时的决策
 	q.push_back(i);//将当前决策插入队列
}
```

------------
这样就结束了，也不会太复杂吧。

最后奉上完整代码：
```cpp
#include<iostream>
#include<cstdio>
#include<queue>
#define ll long long
#define il inline
using namespace std;
const int N=1e6+100;
ll n,tot=0,cnt,ans,anss,st,ans2,ans3;
ll edge[2*N],head[N],ver[2*N],Next[2*N];
ll v[N],v2[N],r[N],d[N],dp[2*N],s[N];
il void add(int x,int y,int z)
{
    edge[++tot]=z,ver[tot]=y,Next[tot]=head[x],head[x]=tot;
}
il bool dfs(int now,int la)
{
    if(v[now]==1)
    {
        v[now]=2,r[++cnt]=now,v2[now]=1;
        return 1;
    }
    v[now]=1;
    for(int i=head[now];i;i=Next[i])
        if(i!=((la-1)^1)+1 && dfs(ver[i],i))
        {
            if(v[now]!=2)
                r[++cnt]=now,v2[now]=1,s[cnt]=s[cnt-1]+edge[i];
            else
            {
                s[st-1]=s[st]-edge[i];
                return 0;
            }
            return 1;
        }
    return 0;		
}//2、dfs找环
il void tree_dp(int now)
{
    v2[now]=1;
    for(int i=head[now];i;i=Next[i])
    {
        int y=ver[i];
        if(v2[y])
            continue;
        tree_dp(y);
        ans=max(ans,d[now]+d[y]+edge[i]);
        d[now]=max(d[now],d[y]+edge[i]);
    }
}//3、处理第一种情况
il ll brt(int root)
{
    st=cnt+1,ans2=0,ans3=0;
    dfs(root,0);
    for(int i=st;i<=cnt;i++)
    {
        ans=0;
        tree_dp(r[i]);
        ans2=max(ans2,ans);
        dp[i+cnt-st+1]=dp[i]=d[r[i]];
        s[i+cnt-st+1]=s[i+cnt-st]+s[i]-s[i-1];
    }
    deque<int> q;
    for(int i=st;i<=2*cnt-st+1;i++)
    {
        while(q.size() && q.front()<=i-cnt+st-1)
            q.pop_front();
        if(q.size()) 
            ans3=max(ans3,dp[i]+dp[q.front()]+s[i]-s[q.front()]);
        while(q.size() && dp[q.back()]-s[q.back()]<=dp[i]-s[i])
            q.pop_back();
        q.push_back(i);
    }//4、处理第二种情况
    return max(ans2,ans3);//取大的答案
}
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        int y,z;
        scanf("%d %d",&y,&z);
        add(i,y,z);
        add(y,i,z);
    }//1、输入
    for(int i=1;i<=n;i++)
        if(!v2[i])//如果没走过就走
            anss+=brt(i);//加上答案
    cout<<anss;
    return 0;
}
```
该讲的都讲得很清楚了，完整代码里就不再注释了。


------------
希望对大家有帮助，有不足之处请指出。

---

## 作者：Mivik (赞：68)

[可到我的博客食用](https://mivik.gitee.io/2020/solution/ioi2008-island/)

这道题确实非常简单... 只是没有看懂其他题解为什么要用单调队列，明明记两个最大值就可以解决？

---

题目大意是给出一个基环树森林（每一个点有一条无向边），让你求出所有基环树的直径（即一条不经过重复点的基环树上的最长路径）之和。

我们考虑不使用邻接表，而是只记录一个点的边的目标位置（ $tar_x$ ）和这条边的长度 （ $wei_x$ ）。

我们发现对于一个在环上的点 $x$，$tar_x$ 必定是这个环上的另一个点。而对于不在环上的点，它们必定构成一个树形结构，而且所有树的根的 $tar$ 必定是一个环上的点。很容易理解，不加说明。

下面，对于基环树环上的每个点 $x$ ，我们称不在环上 $tar$ 为 $x$ 的所有树和 $x$ 共同组成的集合为外环树（自己瞎造的名字）。举个例子：

![为什么莫名有一种喜感](https://cdn.luogu.com.cn/upload/image_hosting/28yc46cg.png)

这里的 1、2、3 都是环上的点。那么 1 的外环树就是 $\{1,5,6,7,8\}$，2 的外环树是 $\{2\}$ ，3 的外环树是 $\{3,4\}$。

我们记一个点 $x$ 的外环树的直径为 $g_x$ ，外环树上从 $x$ 开始的最长链的长度为 $f_x$。同样以上面那张图为例子，那么 $f_1$ 就是 7（3+4），$g_1$ 就是 8（4+1+3）。

我们发现，一个基环树的直径要不是一个外环树的直径，要不就是 $f_i$ +（$i \to j$）+ $f_j$ （ $i,j$ 都是环上的点）。

第二种情况可能不太好理解。以上图为例，$4\to 3\to 2\to 1\to 5\to 7$ 就属于是第二种情况。

那么接下来就简单了。我们只需要用拓扑序处理出每一个环上的点的 $f$ 和 $g$，然后再对于每一个环处理。我们从任意一个点开始，将整个环转换为一条链（比如上图中的环从 1 开始会变成 $[1,2,3]$ ，然后从左到右扫。我们注意到，对于两个点 $i$ 和 $j$（$i$ 在数组中的位置小于 $j$），$(i\to j)$ 事实上是可以选择两条不同的路径（如上图 $(1\to 2)$ 可以是 $1\to 2$ 或 $1\to 3\to 2$。因此我们令环上路径长度的前缀和为 $pre$，环的路径总长度为 $len$，再记（下面 $i$ 的下标小于 $j$）：
$$
\begin{aligned}
ret1&=\max\{f_i+f_j+pre_j-pre_i\}\\
ret2&=\max\{f_i+f_j+len-(pre_j-pre_i)\}
\end{aligned}
$$
我们发现 $i$ 和 $j$ 的贡献在上面两个式子中是独立的，我们可以记一下当前下标小于 $j$ 的 所有 $i$ 中最大的 $f_i-pre_i$（ $m1$ ） 和 $f_i+pre_i$（ $m2$ ），然后每次新扫到一个点就可以用 $m1$ 和 $m2$ 更新。

那么最后的答案就是（$i$ 为环上的点）：
$$
ans=\max\{ret1,ret2,g_i\}
$$
对于每一个环扫一遍即可。

---

小优化：

- 我们再遍历完一个环之前并没法拿到这个环的长度 $len$，因此我们更新 $ret2$ 时不加上 $len$，最后遍历完后再给 $ret2$ 加上 $len$ 即可。

- 我们可以把 $g_i$ 顺便统计到 $ret1$ 里面，~~并没有什么用~~。

---

代码（494ms / 30.84MB，目前洛谷2nd最优解）：

[mivik.h](https://mivik.gitee.io/mivik.h)

```cpp
// Mivik 2020.8.22
#include <mivik.h>

#include <algorithm>
#include <climits>

#ifdef MIVIK
MI cin(popen("xsel -ob", "r"));
#else
MI cin;
#endif

typedef long long qe;

const int nmax = 1000005;

template<typename T> inline bool getmax(T &a, const T &b) { return a<b && (a = b, true); }

int n;
int tar[nmax], wei[nmax];
// deg -> degree 度数
int deg[nmax];
qe f[nmax], g[nmax];
inline qe loop(int x) {
	const int beg = x;
	qe m1 = f[x], m2 = f[x];
	qe pre = wei[x];
	qe ret1 = g[x];
	x = tar[x];
	qe ret2 = LLONG_MIN;
	while (x!=beg) {
		deg[x] = 0;
		getmax(ret1, f[x]+pre+m1);
		getmax(ret2, f[x]-pre+m2);
		getmax(ret1, g[x]);
		getmax(m1, f[x]-pre);
		getmax(m2, f[x]+pre);
		pre += wei[x];
		x = tar[x];
	}
	return std::max(ret1, ret2+pre);
}
int main() {
	int i;
	cin>n;
	for (i=1;i<=n;i++) {
		cin>tar[i]>wei[i];
		++deg[tar[i]];
	}
	static int q[nmax];
	int head = 1, tail = 0;
	for (i=1;i<=n;i++) if (!deg[i]) q[++tail] = i;
    // 计算出环上每个点的 f[i] 和 g[i]
	while (head<=tail) {
		const int x = q[head++];
		const qe cc = f[x]+wei[x];
		getmax(g[tar[x]], f[tar[x]]+cc);
		getmax(g[tar[x]], g[x]);
		getmax(f[tar[x]], cc);
		if (!(--deg[tar[x]])) q[++tail] = tar[x];
	}
	qe ans = 0;
	for (i=1;i<=n;i++) // 如果 deg[i] 不为 0 代表 i 是在环上
    	if (deg[i]) ans += loop(i);
	cout<ans<endl;
	return 0;
}
```

---

## 作者：marTixx (赞：35)

[myblog](https://martixx.gitee.io/2020/11/26/%E5%AD%A6%E4%B9%A0%E7%AC%94%E8%AE%B0-%E5%9F%BA%E7%8E%AF%E6%A0%91/)


## 题意
给你一个基环树森林，要你求森林的直径之和(一棵基环树的直径要求点和边都不重复)

## Sol

把环看成根，考虑两种情况，直径不经过根和经过根

### 不经过环的

不经过根的很好做，对于根的每棵子树求直径就可以了

### 经过环的

设$f_x$表示$x$子树中离$x$最远的点的距离，则答案便是

$$ans_1=max\left\{f_i + f_j + dis_{i,j}\right\}$$

对环上的边权前缀和一下为$dis_i$，答案变成
$$ans_1=max\left\{ f_i + f_j + dis_i - dis_j \right\}$$

整理一下
$$ans_1=max\left\{ (f_i  + dis_i )+ (f_j - dis_j) \right\}$$

设环上边权总和为$len$，其实当$dis_i - dis_j < 0$时，严谨地说答案应为
$$ans2=max\left\{ (f_i  + dis_i )+ (f_j - dis_j) + len \right\}$$

所以只要求一下$max\left\{ f_i  + dis_i \right\}$和$max\left\{f_i - dis_i\right\}$即可

所以第二种情况的答案为$max\left\{ans_1,ans_2 \right\}$

## code

代码超级简洁

```cpp
#include <queue>
#include <cstdio>
#include <climits>
#include <algorithm>

typedef long long LL;
const int N = 1e6 + 30;

int n;
int to[N], w[N], in[N];
LL ans;
LL f[N], g[N];

std::queue < int > q;

int read()
{
    int ss = 0, ff = 1; char ch = getchar();
    while (ch < '0' || ch > '9') {if (ch == '-') ff = -1; ch = getchar();}
    while (ch >= '0' && ch <= '9') ss = ss * 10 + ch - '0', ch = getchar();
    return ss * ff;
}

LL get(int p)
{
    int tmp = p; p = to[p];
    LL m1 = f[tmp], m2 = f[tmp], s = w[tmp], ans1 = g[tmp], ans2 = LLONG_MIN;
    while (p != tmp)
    {
        in[p] = 0;
        ans1 = std::max(ans1, std::max(g[p], f[p] + s + m1));
        ans2 = std::max(ans2, f[p] - s + m2);
        m1 = std::max(m1, f[p] - s), m2 = std::max(m2, f[p] + s);
        s += w[p], p = to[p];
    }
    return std::max(ans1, ans2 + s);
}

int main()
{
    n = read();
    for (int i = 1; i <= n; ++i) to[i] = read(), w[i] = read(), ++ in[to[i]];
    for (int i = 1; i <= n; ++i)
        if (!in[i]) q.push(i);
    while (!q.empty())
    {
        int p = q.front(); q.pop();
        LL c = f[p] + w[p];
        g[to[p]] = std::max(g[to[p]], std::max(f[to[p]] + c, g[p]));
        f[to[p]] = std::max(f[to[p]], c);
        if (!--in[to[p]]) q.push(to[p]);
    }
    for (int i = 1; i <= n; ++i)
        if (in[i]) ans += get(i);
    printf ("%lld\n", ans);
    return 0;
}
```

---

## 作者：iMya_nlgau (赞：33)

## [P4381【[IOI2008]Island】](https://www.luogu.com.cn/problem/P4381)

这是我$A$掉的第一道黑题，所以来发篇题解纪念一下。

先来分析一下题目：

>公园由 $N$ 个岛屿组成，当地管理部门从每个岛屿 $i$ 出发向另外一个岛屿建了一座长度为 $L_i$ 的桥。

这句话说明该公园的形态是一个由 $N$ 个点和 $N$ 条边构成的图 (不一定连通)，即一个基环树森林。

>你希望经过的桥的总长度尽可能长，但任何一个岛都不能游览一次以上。

从这句话告诉我们题目要求，即求各个连通块 (基环树) 中的最长简单路径的和。类比树的直径的定义，我们把基环树的最长简单路径定义为基环树的直径。

### 算法:求基环树的直径

首先我们应该找到环，找环是基环树上的一个基本算法，程序中，我们用数组 $lp$ 存环，环的大小为 $size$，环上的结点依次为$lp[1],lp[2],...,lp[size]$。

```cpp
int lp[maxn],size;	//loop存环，size最终为环的大小 
int fa[maxn];
int dfn[maxn],idx;
void get_loop(int u){
	dfn[u]=++idx;	//时间戳 
	for(int i=head[u];~i;i=edge[i].nxt){
		int v=edge[i].to;
		if(v==fa[u]) continue;
		if(dfn[v]){
			if(dfn[v]<dfn[u]) continue;	//注意：第一次遇到环时先不存 
			lp[++size]=v;				//在dfs的回归过程中再次遇到该环时再记录 
			for(;v!=u;v=fa[v]) lp[++size]=fa[v];	//记录环 
		}
		else fa[v]=u,get_loop(v);	//继续dfs子节点 
	}
}

```

基环树去掉环上的所有边后会形成若干个子树，所以基环树的直径显然可以分为两种情况:

1. 完全位于基环树去掉环的某个子树上

2. 经过环且直径的两端分别位于两个子树上

下面我们就分这两个情况讨论。

#### 情况一:

就是求普通的树的直径，自然有两种方法:

1. 树形dp

2. 两次 $dfs$ (或 $bfs$)

不会树的直径的可以看看这个[模板题](https://www.luogu.com.cn/problem/UVA10308)。

分别求出每棵子树的直径更新答案即可，复杂度为 $O(N)$ 。

无论是那种算法，都能得到一个数组 $d$ : $d[i]$ ( $i$在环上 ) 表示以 $i$ 为根的子树中以 $i$ 为端点的最长链，这可以应用在情况二中。这里我采用了树形$dp$的方法。

```cpp
ll d[maxn],ansd;	//d[i]表示从i出发走向以 i 为根的子树，能到达的最远距离 
//ansd最终为该树的直径
void dp(int u){	//dp求树的直径 
	vis[u]=true;
	for(int i=head[u];~i;i=edge[i].nxt){
		int v=edge[i].to,w=edge[i].w;
		if(vis[v]) continue;
		dp(v);
		ansd=max(ansd,d[u]+d[v]+w);	//用经过点u的最长链更新ansd 
		//最长链即各个 d[v]+w 的最大值和次大值的和，
		//最后一次更新时的 d[u] 一定是次大值，d[v]+w 为最大值 
		d[u]=max(d[u],d[v]+w);	//d[u] 应为所有 d[v]+w 中的最大值 
	}
}
```

#### 情况二:

即找到环上不同的两点 $lp[i]$ 和 $lp[j]$，使得
$$d[lp[i]]+d[lp[j]]+dis(lp[i],lp[j])$$
最大，其中 $dis(lp[i],lp[j])$ 表示 $lp[i]$ 和 $lp[j]$ 在环上的距离。

如果直接枚举 $i$ 和 $j$ 的话，复杂度是$\Omega(N^2)$ ，显然不能用，需要优化。

为了方便研究，我们把环上的边权推到点上，将环破坏为链，再复制一倍，得到数组 $a[1..2\times size-1]$，其中 $a[i]$ 表示边 $(lp[(i-1)\%size],lp[i\%size])$ 的边权 (为了方便，这里令 $lp[0]=lp[size]$ )，再处理出 $a$ 的前缀和 $s$，便有 $dis(lp[i],lp[j])=s[j]-s[i]$。这样，问题就归结为: 找出两个位置 $i,j\ (i<j\ \text{且}\ j-i<size)$ 使得
$$d[lp[i\%size]]+d[lp[j\%size]]+s[j]-s[i]$$
最大。这显然可以用单调队列求解。

不会单调队列的可以写一下这个[模板](https://www.luogu.com.cn/problem/P1886)。

我们可以枚举 $j$，然后用单调队列求出使 $d[lp[i\%size]-s[i]$ 最大的 $i\in [j-size+1,j-1]$ 来更新答案。复杂度为$O(size)$。~~我单调队列写的太烂，这个位置调了好长时间~~

```cpp
l=r=1; q[1]=0;
for(int i=1;i<size<<1;i++){	//单调队列计算情况二的答案 len2 
	while(l<=r&&q[l]<=i-size) l++;
	//判断队头的决策是否超出size的范围，超出则出队 
	len2=max(len2,d[lp[q[l]%size]]+d[lp[i%size]]+s[i]-s[q[l]]);
	//此时队头即为使 d[lp[i%size]-s[i] 最大的 i，并更新答案 
	while(l<=r&&s[q[r]]-d[lp[q[r]%size]]>=s[i]-d[lp[i%size]]) r--;
	//若队尾的值没有当前的 i 更优，出队 
	q[++r]=i;	//将 i 入队 
}
```
最后 $len1$ 和 $len2$ 中较大的即为所求的基环树直径，按此方法求出所有基环树的直径并累加，就能得到答案。总的复杂度为 $O(N)$。

下面放上完整代码：
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
const int maxn=1e6+10; 
const int maxm=maxn<<1;	//无向图存边需要2倍的空间 
typedef long long ll;
struct Edge{	//链式前向星存图 
	int to,w,nxt;
}edge[maxm];
int head[maxn],cnt;
inline void Init(){	//初始化邻接表 
	for(int i=0;i<maxn;i++) head[i]=-1;
	for(int i=0;i<maxm;i++) edge[i].nxt=-1;
	cnt=1;
}
inline void addedge(int u,int v,int w){	//加入边 
	edge[cnt]={v,w,head[u]};
	head[u]=cnt++;
}
inline int read(){	//快读 
	int z=0; char c=getchar();
	while(c<'0'||c>'9') c=getchar();
	while(c>='0'&&c<='9'){
		z=(z<<3)+(z<<1)+(c^'0'); c=getchar();
	}
	return z;
}
int n;
bool vis[maxn];
int lp[maxn],size;	//loop存环，size最终为环的大小 
int fa[maxn];
int dfn[maxn],idx;
void get_loop(int u){
	dfn[u]=++idx;	//时间戳 
	for(int i=head[u];~i;i=edge[i].nxt){
		int v=edge[i].to;
		if(v==fa[u]) continue;
		if(dfn[v]){
			if(dfn[v]<dfn[u]) continue;	//注意：第一次遇到环时先不存 
			lp[++size]=v;				//在dfs的回归过程中再次遇到该环时再记录 
			for(;v!=u;v=fa[v]) lp[++size]=fa[v];	//记录环 
		}
		else fa[v]=u,get_loop(v);	//继续dfs子节点 
	}
}
ll d[maxn],ansd;	//d[i]表示从i出发走向以 i 为根的子树，能到达的最远距离 
void dp(int u){	//dp求树的直径 
	vis[u]=true;
	for(int i=head[u];~i;i=edge[i].nxt){
		int v=edge[i].to,w=edge[i].w;
		if(vis[v]) continue;
		dp(v);
		ansd=max(ansd,d[u]+d[v]+w);	//用经过点u的最长链更新ansd 
		//最长链即各个 d[v]+w 的最大值和次大值的和，
		//最后一次更新时的 d[u] 一定是次大值，d[v]+w 为最大值 
		d[u]=max(d[u],d[v]+w);	//d[u] 应为所有 d[v]+w 中的最大值 
	}
}
ll s[maxn<<1];	//s为前缀和数组 
int q[maxn<<1],l,r;	//单调队列 
inline ll solve(int p){
	idx=size=0; get_loop(p);
	ll len1=0,len2=0; 
	lp[0]=lp[size];
	for(int i=1;i<=size;i++) vis[lp[i]]=true;
	for(int i=1;i<=size;i++){
		ansd=0; dp(lp[i]);
		len1=max(len1,ansd);
	}//计算出情况一的答案 len1 
	if(size==2){	//单独处理由两个点构成的环的情况 
	    for(int i=head[lp[1]];~i;i=edge[i].nxt){
	        if(edge[i].to==lp[2])
	            len2=max(len2,d[lp[1]]+d[lp[2]]+edge[i].w);
	    }
	    return max(len1,len2);
	}
	for(int i=1;i<=size;i++){
		int lpw;
		for(int j=head[lp[i]];~j;j=edge[j].nxt)
			if(edge[j].to==lp[i-1]){
				lpw=edge[j].w; break;
			}//找到边 (lp[i-1],lp[i])
		s[i]=s[i-1]+lpw;	//计算前缀和 
	}
	for(int i=1;i<size;i++) s[size+i]=s[size]+s[i];	//复制一倍 
	l=r=1; q[1]=0;
	for(int i=1;i<size<<1;i++){	//单调队列计算情况二的答案 len2 
		while(l<=r&&q[l]<=i-size) l++;
		//判断队头的决策是否超出size的范围，超出则出队 
		len2=max(len2,d[lp[q[l]%size]]+d[lp[i%size]]+s[i]-s[q[l]]);
		//此时队头即为使 d[lp[i%size]-s[i] 最大的 i，并更新答案 
		while(l<=r&&s[q[r]]-d[lp[q[r]%size]]>=s[i]-d[lp[i%size]]) r--;
		//若队尾的值没有当前的 i 更优，出队 
		q[++r]=i;	//将 i 入队 
	}
	return max(len1,len2);	//最终答案为两种情况中较大的 
}
int main(){
	n=read();
	Init();
	for(int i=1;i<=n;i++){
		int j=read(),l=read();
		addedge(i,j,l); addedge(j,i,l);
	}//读入图 
	ll ans=0;
	for(int i=1;i<=n;i++)
		if(!vis[i]) ans+=solve(i);	//计算每个连通块（基环树）的直径并累加 
	printf("%lld\n",ans);	//输出答案 
	return 0;
}
```
感谢阅读！点个赞吧，谢谢！

如果我的题解有什么错误或有问题，欢迎大家留言或私信我 （^_^;)

---

## 作者：ywy_c_asm (赞：31)

$emm……$这题虽然现在测不了但是在$bzoj$上$A$了就来写个题解吧……毕竟没题解还是挺尴尬的……

首先这个题意用一句话概括就是，给一个基环树森林，求每个基环树的最长链之和。

那么我们可以用基环树的套路来干这个事，就是先不管环，对于环上的每个点我们都对他的子树进行一遍树形$dp$把最长链与根到子树内点的最长链$dp[i]$（我们要求出前者是因为可能在这个基环树里面不走环而走一个子树内的一个路径是最优解，这东西我们在一个点处拼接他两个儿子的到底下的最长链即可）求出来，然后我们考虑在环上的点，他们可以进行两两之间的答案的拼接，比如有两个点$i$和$j$，就可以先从$i$子树内的最深处点走到$i$，这段距离是$dp[i]$，然后再从环上$i$到$j$的路径上走到$j$，然后再走到$j$子树内最深的点，这段距离是$dp[j]$。

然后我们接着套路的把环从一个地方断开搞成一段序列，然后再把它复制一份接在后面，就转化成了序列上的问题，为了更直观的理解我画了个图：

![](https://cdn.luogu.com.cn/upload/pic/39711.png)

容易发现这样做之后这个序列上任意一段边数小于$n$（环上的点数）的路径都是合法的，并且涵盖了环上所有的合法路径，我们不妨对这个序列（称他为$a$）做一个边权的前缀和$dis[i]$表示序列的第一个点到它的距离，这样能够方便求环上距离，于是我们要枚举每个序列上的终点$i$，对他求：

$max_{i-n<j<i}\{dp[a[i]]+dp[a[j]]+dis[i]-dis[j]\}$

首先这是在一个固定长度的决策区间内最大化这个式子的值，然后这个式子可以写成$(dp[a[i]]-dis[i])+(dp[a[j]]-dis[j])$的形式，前者只和$i$有关，后者只和$j$有关，这是单调队列的套路，维护一下$max\{dp[a[j]]-dis[j]\}$就行了。

以上就是大致思路，还是不难的，可以发现这题就是由一堆套路拼成的。不过基环树这玩意我觉得代码写起来还是不那么容易，下面说一下实现的一些细节：

1.我们用一个邻接表配合并查集存每个基环树的所有点，这样省的每次都暴力找点（开$100$万个$vector$会炸……）

2.关于找环的问题，我们可以把这个基环树的树的部分删掉，就是考虑到每个叶子的度数都是1，就可以用类似拓扑排序的方法删点，当这个点的度数为1也就是说他没有前驱了就可以把他删掉加到队列里，注意这个跟拓扑排序不一样的地方是别忘了这是无向图，在遍历这个点的出边的时候别忘了排除已经删过的点。

3.把这个环转化成序列，就是先找一个环上的点，然后把他加入队列进行$bfs$（其实这是在环上并没必要用$bfs$，但是感觉比较好写），我们对每个环上的点维护一个$nxt[i]$表示他指向下一个点的边权是啥，注意别通过反向边走回去了。不过这里有个比较恶心的地方就是最后一个点，我们需要判一下他指向第一个点的边然后退出$bfs$，所以我们的$vis$标记需要标记在边上，这个可以用网络流里那种反向边^1的方法来标记边，然后把队列里的点复制一份接到后面就行了。

4.为防止爆栈要用$bfs$进行树形$dp$……

上代码~

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define ll long long
using namespace std;
inline int get(){//快读 
    int n=0;char c;
	while((c=getchar())||23333){
        if(c>='0'&&c<='9')break;
		if(c=='-')goto s;
    }
	n=c-'0';
	while((c=getchar())||23333){
        if(c>='0'&&c<='9')n=n*10+c-'0';
		else return(n);
    }
	s:while((c=getchar())||23333){
        if(c>='0'&&c<='9')n=n*10-c+'0';
		else return(n);
    }
}typedef struct _b{//边 
    int dest;int nxt;int len;unsigned char vis;//标记 
}bian;
bian memchi[2000001];
int gn=2;
int heads[1000001];
ll dp[1000001];
ll maxn=0;
int que[2001001];//队列 
inline void add(int s,int t,int l){
    memchi[gn].dest=t;
	memchi[gn].len=l;
	memchi[gn].nxt=heads[s];
	heads[s]=gn;gn++;
}
int nxts[1000001],fheads[1000001];//用来给基环树存点的邻接表 
int ints[1000001],deg[1000001];//并查集与度数数组 
unsigned char nohuan[1000001];//是否不在环上 
int find(int n){
    if(ints[n]==n)return(n);
	return(ints[n]=find(ints[n]));
}
int fa[1000001];//树形dp的时候维护父亲 
int nxt[1000001];//环上的点的出边的边权 
int xulie[2001001];//环转化成的序列 
unsigned char bv[1000001];
ll dis[2001001];
inline void tree_dp(int pt){//bfs树形dp 
    register int head=0,tail=1;que[0]=pt;do{
        int me=que[head];head++;
		for(register int i=heads[me];i;i=memchi[i].nxt){
            if(memchi[i].dest==fa[me]||!nohuan[memchi[i].dest])continue;
            fa[memchi[i].dest]=me;
			que[tail]=memchi[i].dest;
			tail++;
        }
    }while(head<tail);
	for(register int a=tail-1;a>=0;a--){//把队列里的点倒过来就能按顺序了 
        int me=que[a];
		for(register int i=heads[me];i;i=memchi[i].nxt){
            if(memchi[i].dest==fa[me]||!nohuan[memchi[i].dest])continue;
            ll p=dp[memchi[i].dest]+memchi[i].len;
			maxn=max(maxn,p+dp[me]);
			dp[me]=max(dp[me],p);
        }
    }
}
inline ll solve(int jh){//求基环树的最长链 
    register int head=0,tail=0;
	for(register int i=fheads[jh];i;i=nxts[i]){
        if(deg[i]==1)que[tail]=i,tail++,bv[i]=1;
    }
	while(head<tail){//对叶子进行“拓扑排序”只保留环 
        int me=que[head];head++;
		nohuan[me]=1;
		for(register int i=heads[me];i;i=memchi[i].nxt){
            if(bv[memchi[i].dest])continue;
            deg[memchi[i].dest]--;
			if(deg[memchi[i].dest]==1){
                que[tail]=memchi[i].dest;
				tail++;
				bv[memchi[i].dest]=1;
            }
        }
    }
	ll ans=0;
	int st;//环上第一个点 
	int cnt=0;
	for(register int i=fheads[jh];i;i=nxts[i]){
        if(!nohuan[i]){st=i;cnt++;
            maxn=0;
            tree_dp(i);
            ans=max(ans,maxn);
			ans=max(ans,dp[i]);
        }
    }
	bv[st]=1;
	head=0,tail=1;
	que[0]=st;
	int rcnt=cnt;//环长 
	do{//把这个环转化成序列 
        int me=que[head];
		head++;
		cnt--;
		for(register int i=heads[me];i;i=memchi[i].nxt){
            if(nohuan[memchi[i].dest])continue;
            if(memchi[i^1].vis)continue;//对走过的边进行标记 
            if(memchi[i].dest==st){//注意特判最后一个点 
                nxt[me]=memchi[i].len;break;
            }
			bv[memchi[i].dest]=1;
			nxt[me]=memchi[i].len;
			memchi[i].vis=1;
            que[tail]=memchi[i].dest;
			tail++;
            break;
        }
    }while(head<tail);
	int ptr=1;
	for(register int i=0;i<tail;i++){
        xulie[ptr]=que[i];ptr++;
    }
	for(register int i=0;i<tail;i++){//复制一份接到后面 
        xulie[ptr]=que[i];ptr++;
    }
	ptr--;
	for(register int i=2;i<=ptr;i++)dis[i]=dis[i-1]+nxt[xulie[i-1]];//前缀和 
    head=0,tail=0;
	for(register int i=1;i<=ptr;i++){//这个再普通不过的单调队列优化dp无需多解释了吧 
        while(head<tail&&i-que[head]>=rcnt)head++;
		if(head<tail){
            ans=max(ans,dis[i]+dp[xulie[i]]-dis[que[head]]+dp[xulie[que[head]]]);
        }
		while(head<tail&&dp[xulie[que[tail-1]]]-dis[que[tail-1]]<=dp[xulie[i]]-dis[i])tail--;
		que[tail]=i;tail++;
    }
	return(ans);
}
signed main(){
    int n;
	n=get();
	for(register int i=1;i<=n;i++)ints[i]=i;
	ll tot=0;
    for(register int i=1;i<=n;i++){
        int t=get(),l=get();
		add(i,t,l);
		add(t,i,l);
		deg[i]++;
		deg[t]++;
		tot+=l;
		int aa=find(i),ab=find(t);
        if(aa!=ab){
            ints[aa]=ab;
        }
    }
	ll ans=0;
	for(register int i=1;i<=n;i++){
        int aa=find(i);
		nxts[i]=fheads[aa];//使用邻接表向基环树里存点 
		fheads[aa]=i;
    }
	for(register int i=1;i<=n;i++){
        if(ints[i]==i)ans+=solve(i);//统计答案 
    }
	cout<<ans<<endl;
    return(0);
}
```

---

## 作者：小塘空明 (赞：7)

~~读题读了我10min emmmmm~~

题解参考了lyd大佬进阶指南上的思路。

可以看出，给出的图是由几颗基环树构成的。

因为离开某颗基环树就不能再回来，所以题目的答案就是各颗基环树的直径之和。

基环树的直径显然有两种。

**（1）**：处于不在环上的节点的某颗子树中

**（2）**：部分经过环且去掉处于环上的边后位于两颗不同的子树内。

所以我们可以先用拓扑排序求出环上所有的点。

同时求出从每个环上节点出发在不经过环的前提下的最长链，并用求树的直径的方法更新答案处理第一种情况。

对于第二种情况，就等价于从环上找出两点i.j,让f[i]+dis(i,j)+f[j]最大，dis(i,j)为两点在环上的距离，考虑顺时针和逆时针两种走法。

为了快速求出f[i]+dis(i,j)+f[j]的值，我们破环成链，用单调队列优化。

```
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<string>
#include<cstring>
#include<cmath>
using namespace std;
typedef long long ll;
const int u=1000010;
int ver[2*u],edge[2*u],next[2*u],head[u],du[u],c[u],v[u],q[2*u];
ll f[u],d[u],a[2*u],b[2*u],ans;
int n,m,tot,t,i,x,y;
inline ll read(){
	ll x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+ch-'0';ch=getchar();}
	return x*f;
}
inline void add(int x,int y,int z){
	ver[++tot]=y;edge[tot]=z;next[tot]=head[x];head[x]=tot;du[y]++;
}
inline void bfs(int s,int t){
	int l,r,i;
	q[l=r=1]=s;c[s]=t;
	while(l<=r){
		for(i=head[q[l]];i;i=next[i])
			if(!c[ver[i]]){q[++r]=ver[i];c[ver[i]]=t;}
		l++;
	}
}
inline void topsort(){
	int l=1,r=0,i,x,y;
	for(i=1;i<=n;i++) if(du[i]==1) q[++r]=i;
	while(l<=r){
		for(i=head[x=q[l]];i;i=next[i]){
			if(du[y=ver[i]]>1){
				d[c[x]]=max(d[c[x]],f[x]+f[y]+edge[i]);
				f[y]=max(f[y],f[x]+edge[i]);
				if((--du[y])==1) q[++r]=y;
			}
		}
		l++;
	}
}
inline void dp(int t,int x){
	int m=0,i,l=0,r,y=x;
	do{
		a[++m]=f[y];du[y]=1;
		for(i=head[y];i;i=next[i]){
			if(du[ver[i]]>1){
				b[m+1]=b[m]+edge[i];y=ver[i];break;
			}
		}
	}while(i);
	if(m==2){
		for(i=head[y];i;i=next[i]){
			if(ver[i]==x){
				l=max(l,edge[i]);
			}
		}
		d[t]=max(d[t],f[x]+f[y]+l);
		return;
	}
	for(i=head[y];i;i=next[i]){
		if(ver[i]==x){
			b[m+1]=b[m]+edge[i];break;
		}
	}
	for(i=1;i<m;i++) a[m+i]=a[i],b[m+i]=b[m+1]+b[i];
	q[l=r=1]=1;
	for(i=2;i<2*m;i++){
		while(l<=r&&i-q[l]>=m) l++;
		d[t]=max(d[t],a[i]+a[q[l]]+b[i]-b[q[l]]);
		while(l<=r&&a[q[r]]-b[q[r]]<=a[i]-b[i]) r--;
		q[++r]=i;
	}
}
int main(){
	n=read();
	for(i=1;i<=n;i++){
		x=read();y=read();
		add(i,x,y);add(x,i,y);
	}
	for(i=1;i<=n;i++){
		if(!c[i]) bfs(i,++t);
	}
	topsort();
	for(i=1;i<=n;i++){
		if(du[i]>1&&!v[c[i]]){
			v[c[i]]=1;dp(c[i],i);ans+=d[c[i]];
		}
	}
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：bugaile (赞：6)

题目大意$:$

给你一棵基环树森林，求出基环树的直径之和.

题意比较简单,但写起来可不简单.对于基环树森林,我们只需要遍历一次,就可以找出所有树,在每个分别处理直径即可.但关键就在于求基环树直径,这里指最长简单路径,即最长的没有重复边和重复点的路径.

那么我们来说怎么求基环树直径.

对于基环树,我们将环看作根,那么直径有两种情况$:$

$1.$不经过环,也就是环上某个点的子树内部,对于这种情况,直接在子树内部处理直径,更新答案即可;

$2.$经过环,那么预处理出环上每个点到其子树上的最长距离,在预处理一个环上前缀和,$ans=max${$sondis[i]+sondis[j]+sumcircle[i]-sumcircle[j]$},更新答案即可.

最后再累加答案即可.

代码实现上,先跑一遍$bfs$,预处理出每一个点所属的基环树,在跑一遍$top$ $sort$,更新直径,同时出每个点往子树方向所能到达的最大值.

再每棵树跑一遍情况$2$,累加答案,维护单调队列时将长度开为两倍,断环为链即可,具体细节看代码注释,另外要特殊处理二元环.

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#define ll long long
using namespace std;
const int N=1e6+3;
int to[N<<1],nex[N<<1],head[N],w[N<<1],tt;
int c[N];//记录当前节点属于第几棵基环树;
int dg[N];//记录度数;
int q[N<<1];//数组模拟队列;
ll d[N];//d[i]记录第i棵树上的直径;
ll f[N];//f[i]记录从i点向儿子方向上所可以走的最长距离;
ll sumcircle[N<<1];//环上距离前缀和;
ll sondis[N<<1];//sondis[i]记录环上的第i个点到其子树的最远距离;
int cnt,n;
bool vis[N];//标记当前基环树是否已解决过;
inline void add(int x,int y,int W){
    to[++tt]=y,w[tt]=W,nex[tt]=head[x],head[x]=tt;
    return ;
}
inline void bfs(int p,int t){
    int l=0,r=1;
    q[1]=p,c[p]=t;//广搜预处理每一个点所属基环树的编号;
    while(l<r){
        ++l;
        int x=q[l];
        for(int i=head[x],v;i;i=nex[i]){
            v=to[i];
            if(!c[v]){
                q[++r]=v;
                c[v]=t;
            }
        }
    }
    return ;
}
inline void top_sort(){//拓扑排序求不经过环的直径,从叶子节点向根(环)遍历;
    int l=0,r=0;
    for(int i=1;i<=n;++i)if(dg[i]==1)q[++r]=i;//将所有度数为1的点先加入队列中(即叶子结点);
    while(l<r){
        ++l;
        int x=q[l];
        for(int i=head[x],v;i;i=nex[i]){
            v=to[i];
            if(dg[v]>1){//此时v在以环为根的树上是其实是x的父亲;
                d[c[x]]=max(d[c[x]],f[x]+f[v]+w[i]);//更新当前基环树上的答案,;
                f[v]=max(f[v],f[x]+w[i]);//更新父节点可以到达的最远节点;
                if(--dg[v]==1)q[++r]=v;//若当前度数现在变为1,入队;
            }
        }
    }
    return ;
}
inline void work(int t,int x){
    int tot=0,l,r,v=x,u,i;//在拓扑排序后已经将非环上的边遍历完了,环上的边和点均还未遍历,且度数为2,将x看做环上的起点,v看做终点;
    do{
        dg[v]=1,sondis[++tot]=f[v];//将当前点度数记为1,防止反向遍历,同时记录第tot号环上节点到子树上的最短距离;
        for(i=head[v];i;i=nex[i]){
            u=to[i];
            if(dg[u]>1){//环上的点度数均大于1,所以度数大于1的点即是环上的点;
                v=u;//更新终点;
                sumcircle[tot+1]=sumcircle[tot]+w[i];//处理环上距离前缀和;
                break;//保证向一边枚举,所以找到一个点就break;
            }
        }
    }while(i);
    if(tot==2){//特殊处理二元环;
        int len=0;
        for(i=head[v];i;i=nex[i]){
            u=to[i];
            if(u==x){
                len=max(len,w[i]);//找出两个点之间较大的边; 
            }
        }
        d[t]=max(d[t],(ll)len+f[x]+f[v]);//更新答案;
        return ;
    }
    for(int i=head[v],u;i;i=nex[i]){
        u=to[i];
        if(u==x){
            sumcircle[tot+1]=sumcircle[tot]+w[i];//将起点和终点的距离处理出来;
            break;
        }
    }
    for(i=1;i<tot;i++)sondis[tot+i]=sondis[i],sumcircle[tot+i]=sumcircle[tot+1]+sumcircle[i];//断环为链,再复制一遍数组;
    q[1]=1;
    l=r=1;
    for(int i=2;i<tot<<1;++i){
        while(l<=r&&i-q[l]>=tot)++l;//将超出环长度的部分弹出;
        d[t]=max(d[t],sondis[q[l]]+sondis[i]+sumcircle[i]-sumcircle[q[l]]);
        while(l<=r&&sondis[q[r]]+sumcircle[i]-sumcircle[q[r]]<=sondis[i])--r;//将队尾答案不够优秀的部分弹出;
        q[++r]=i;//入队;
    }
    return ;
}
int main(){
    freopen("ceshi.in","r",stdin);
    cin>>n;
    int x,W;
    for(int i=1;i<=n;++i)scanf("%d%d",&x,&W),add(x,i,W),add(i,x,W),++dg[x],++dg[i];
    for(int i=1;i<=n;++i)if(!c[i])bfs(i,++cnt);//预处理;
    top_sort();//拓扑排序求直径;
    ll ans=0;
    for(int i=1;i<=n;++i)
        if(dg[i]>1&&!vis[c[i]]){//如果当前基环树未被处理,并且当前点是环上点,就处理;
            vis[c[i]]=true;
            work(c[i],i);
            ans+=d[c[i]];//累加答案;
        }
    cout<<ans<<'\n';
    return 0;
}
```

---

## 作者：Xiao_Mi (赞：6)

#### 题目大意：求多棵基环树的直径总和。

#### 思路：对于基环树系列的题，最重要的就是找环，其他操作都是基于环的。本题也是如此：一棵基环树的直径有两种情况：1、经过环上两个节点外加他们子树的最深深度，也就是dis(i,j)+dep[i]+dep[j]，其中dep代表从根节点开始所能到达的最深节点，dist代表i到j的最大距离，有两种情况（顺时针或逆时针，取大的那个）。2、环上某个节点子树的直径。

#### 首先如何找环？本来可以用dfs随便找，但是毒瘤出题人卡dfs，那怎么办呢？我们发现这个输入特别妙，他每次给出第i个点通向哪里，我们可以就按这样模拟，直到找到曾经访问过的点就找到了环。

#### 第一种情况：对于处理出来的环，我们要将其破环城链，也就是记录两遍环的节点。然后我们预处理出他们的dep，可以用bfs或dfs求。注意：dep不是直径。对于每个dis(i,j)，我们记个前缀和，以环上某个节点为基准，可以列出一个简单式子：ans=Max{(sum[j]-dep[j])+(sum[i]+dep[i])},（因为我们把环拆成两倍，所以涵盖了所有顺时针和逆时针的状态）对这个式子，我们可以枚举i，也就是知道了sum[i]+dep[i]的值，然后我们要求最大的sum[j]-dep[j]，这可以用一个单调队列维护。

#### 第二种情况：对每个环上节点求一遍树的直径，我是用树形dp，设dp[x]是以x为根的最长链，我们对于x的任意两个儿子节点i,j，经过x的最长链就是就过i的最长链加dis(x,i),和过j的最长链加dis(x,j)，也就是ans=max(dp[i]+dp[j]+dis(x,i)+dis(x,j))(1<=i<j<son[x])。这看似要双重循环，但我们观察到dp[x]包含了x到dp[i]的最长链，所以我们只要枚举另一个子节点j+dis(x,j)和dis[x]相加更新ans，然后用dp[j]+dis(x,j)更新dis[x]。

#### 最后一、二种情况取个max就是答案

#### 注意：这题毒瘤得很，空间开得很小，又卡dfs，因为要破环城链所以要开两倍空间。还有dep不是树的直径，而是最深节点。有些数组要开long long。

#### 代码如下：

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<cstdlib>
using namespace std;
const int Maxn=1e6+7;
int n,dfn[Maxn],id;
int last[Maxn],tot,cnt;
int vis[Maxn],que[2*Maxn],pd[Maxn],f[Maxn],dvi[Maxn];
long long las,nic,dep[2*Maxn],Q[2*Maxn],dis[Maxn],ans;
struct edge{
    int to,next,w;
}e[4*Maxn];
struct hoop{
    int to,w;
}fa[Maxn],ring[Maxn];
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-') w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
inline void add_edge(int x,int y,int w){
    e[++tot].to=y;
    e[tot].next=last[x];
    e[tot].w=w;
    last[x]=tot;
    return;
}
inline long long K(int x){
    return dep[x]-Q[x];
}
inline void find_hoop(int x){ //找树上的环，不能用dfs求
    dvi[x]=1;
    while(1){
        int u=fa[x].to;
        if(dvi[u]){
            ring[++cnt].to=u;
            ring[cnt].w=fa[u].w;dfn[u]=1;
            for(int i=x;i!=u;i=f[i]) dfn[i]=1,ring[++cnt].to=i,ring[cnt].w=fa[i].w;
            break;
        }
        else{
            dvi[u]=1;
            f[u]=x;
        }
        x=u;
    }
    return;
}
inline void dp(int x){ //树形dp
    vis[x]=1;dfn[x]=1;
    for(int i=last[x];i;i=e[i].next){
        int u=e[i].to;
        if(vis[u]||pd[u]) continue;
        dp(u);
        nic=max(nic,dis[x]+dis[u]+e[i].w);
        dis[x]=max(dis[x],dis[u]+e[i].w); 
    }
    return;
}
void dfs(int x,int f,long long w){ //求环上每个节点的dep值
    if(w>=nic) nic=w;
    for(int i=last[x];i;i=e[i].next){
        int u=e[i].to;
        if(u!=f&&!pd[u]) dfs(u,x,w+e[i].w);
    }
}
inline void first(int i){
    nic=0;dfs(ring[i].to,0,0);dep[i]=nic;//!!!
    nic=0;dp(ring[i].to);
    las=max(las,nic);
    return;
}
inline void quee(){ //单调队列优化
    int head=1,tail=0;
    for(int i=1;i<=2*cnt;++i){
        if(i<=cnt) Q[i]=Q[i-1]+ring[i].w;
        else Q[i]=Q[i-1]+ring[i-cnt].w;
        if(head<=tail) las=max(las,K(que[head])+Q[i]+dep[i]);
        while(head<=tail&&K(que[tail])<=K(i)) --tail;
        que[++tail]=i;
        while(head<=tail&&que[head]<=i-cnt+1) ++head;
    }
    ans+=las;
    return;
}
int main(){
    int y,w;
    n=read();
    for(int i=1;i<=n;++i){
        y=read();w=read();
        add_edge(i,y,w);add_edge(y,i,w);
        fa[i].to=y;fa[i].w=w; //记录方便枚举
    }
    for(int i=1;i<=n;++i){
        if(!dfn[i]){
            cnt=0;id=0;las=0;
            find_hoop(i);
            for(int j=1;j<=cnt;++j) pd[ring[j].to]=1;
            for(int j=1;j<=cnt;++j) first(j);
            for(int j=1;j<=cnt;++j) dep[j+cnt]=dep[j]; //把环断成链 
            quee();
        }
    }
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：hater (赞：4)

因为题解区都是单调队列 所以补充一个不一样的做法 

题目要求 ： 求所有基环树的直径和 

（注 ： 遇到环走边权和大的那一边 ） 

这道题是无向树 无向树一般有这种套路 ：

1 . 找出环 2 . 除环外的子树各自单独处理 3 综合计算 

回看到题目 

每一个基环树的直径有两种可能 

1 . 除环外的子树的直径  

2 . 直径经过环上的边 ，端点在2个不同子树中 

先看情况 2 有一个小结论显然成立 ：

基环树的直径不会经过所有环上的边 

证明 ： 点不能被重复经过 

也就是说 删掉某1条边 不会对基环树的直径产生影响

算法的思路大致如下 ： 枚举删掉的1条边 再求树的直径 

问题的瓶颈也在于 ： 如何**快速**求出处理后的树的直径 

设 

环长为$len$ 环上的节点为 $v$ 

以环上节点为根节点的最长链 $f$ ( 显然除去环 ）

边权的前缀和为 $S$ 

现在考虑删掉 $v_{k}$到$v_{k+1}$的边 

1 如果直径的两个点都在 i的**左端**  那么直径就是 

$f_{i}-S_{i}+f_{j}+S_{j}  ( 1 <= i < j <=k )$  

$L0_{k}$ 记录这个式子的最大值 

(注 ： 左端点一律i 右端点一律是j ) 

2 如果都在右端 同上 

$f_{i}-S_{i}+f_{j}+S_{j} ( k < i < j <= len )$ 

$R0_{k+1}$ 记录这个式子的最大值 

3 如果左端点在i左边 右端点在i+1右边 

$f_{i}+S_{i}+f_{j}+(S_{len}-S{j}) ( 1 <= i <= k , k<j<=len)$ 

分开来维护 

$f_{i}+S_{i}$ 的最大值记录为$L_{k}$ 

$f_{j}+(S_{len}-S{j})$ 的最大值记录为$R_{k+1}$ 

接下来就比较简单了 只要求出这些数组 

先考虑 情况1 

假设现在正在求$L0_{j}$ 

设 $Now$ 是 $f_{i}-S_{i}(1<=i<j)$ 的最大值 

那么有递推式 $L0_{j}=max(L0_{j-1},f_{j}+Now+S_{i})$ 

之后将要求$L0_{j+1}$ 我们把Now更新一下就OK了 

其他三个数组以此类推 

（注 ： 代码中的左右端点与上文不同 请注意 ）

代码 ： 

```cpp
#include <bits/stdc++.h> 
#define Rg register 
#define MAX 1000005 
#define LL long long 
#define INF 1e17 
#define IL inline 
using namespace std ; 
IL int read( ) { 
    Rg int x=0,f=1; Rg char ch=getchar();
    while(ch<'0'||ch>'9') { if(ch=='-') f = -1 ; ch=getchar(); } 
    while(ch>='0'&&ch<='9') { x = (x<<1) + (x<<3) + (ch^48) ; ch=getchar();}
    return x*f; } 
int ins[MAX] , lis[MAX] , Val[MAX] , n , len , 　q[MAX] , l=1 , r ; 
vector <int> v[MAX] , edge[MAX] ; bool In[MAX] ;
LL Ans , Ans1 , Ans2 , f[MAX] , S[MAX] , L[MAX] , R[MAX] , D[MAX] , L0[MAX] , R0[MAX] , Now ; 
IL LL max( Rg LL A , Rg LL B ) { return A > B ? A : B ; }   
IL void find_c( Rg int x ) { 
	In[x] = 1 ; 
	for( Rg int i=0; i<v[x].size(); i++) { 
		int u = v[x][i] , z = edge[x][i] ; 
		if( In[u] || ins[u] <= 1 ) continue ;  
		lis[++len] = u ;  Val[len] = z ; 
		find_c( u ) ; return ;  
	}
} 
IL void Solve( int p ) {
	len = 0 ;  Ans1 = Ans2 = -INF ;   
	lis[++len] = p ; find_c( p ) ;    
	if( len == 2 ) {  
	    Rg LL Z1 = -1 , Z2 = -1 ;  
	    for( Rg int i=0;i<v[lis[2]].size(); i++) { 
	    	int u = v[lis[2]][i] , z= edge[lis[2]][i] ;
	    	if( u == lis[1] ) 
	    	   if( Z1 == -1 ) Z1 = z ; else { Z2 = z ;  break; } 
		}  
		Ans1 = max( Z1 , Z2 ) + f[lis[1]] + f[lis[2]] ; 
		Ans2 = max( D[lis[1]] , D[lis[2]] ) ; 
		Ans += max( Ans1 , Ans2 ) ; 
		return ;  
	}  
	for( int i=0; i<v[lis[len]].size(); i++) 
		if( v[lis[len]][i] == p )  { Val[1] = edge[lis[len]][i] ; break; } 
	Now = -INF ; L[0] = L0[0] = -INF ; 
	for(Rg int i=1; i<=len; i++) { 
	    S[i] = S[i-1]+Val[i] ;
		L[i] = max( L[i-1] , f[lis[i]]+S[i] ) ;
		L0[i] = max( L0[i-1] , f[lis[i]]+Now+S[i] ) ;
		Now = max( Now , f[lis[i]]-S[i] ) ; 
	} Now = -INF ; R[len+1] = R0[len+1] = -INF ;  
	for(Rg int i=len; i>0; i--) {   
		R[i] = max( R[i+1] , f[lis[i]]+S[len]-S[i] ) ;  
		R0[i] = max( R0[i+1] , f[lis[i]]-S[i]+Now ) ; 
		Now = max( Now , f[lis[i]]+S[i] ) ;  
	} 
	for(Rg int i=1; i<=len; i++)  
	  Ans2 = max( Ans2 , max( max( L0[i] , R0[i+1] ) ,  max( D[lis[i]] , L[i]+R[i+1] ) ) ) ; 
	Ans += max( Ans1 , Ans2  ) ;  
} 
signed main() {
	n = read() ;  Rg int x , z ;
	for(Rg int i=1; i<=n; i++) {  
		x = read() ; z = read() ;  ins[i]++ ; ins[x]++ ; 
		v[x].push_back(i) ;
		edge[x].push_back(z) ;
		v[i].push_back(x) ; 
		edge[i].push_back(z) ;  
	}   
	for(Rg int i=1; i<=n; i++)  
		if( ins[i] == 1 ) q[++r] = i ;   
	while( l<=r ) {  
		Rg int u = q[l++] ;   
		for( int i=0; i<v[u].size(); i++) {   
			int x = v[u][i] , z = edge[u][i] ; 
			if( ins[x] <= 1 ) continue ; 
			D[x] = max( D[x] , f[x]+f[u]+z ) ; 
		    D[x] = max( D[x] , D[u] ) ; 
		    f[x] = max( f[x] , f[u]+z ) ; 
			ins[x] -- ; 
			if( ins[x] == 1 ) 
			  q[++r] = x ;  
		}   
	}   
	for(Rg int i=1; i<=n; i++)  
	 if( ins[i] >= 2 && !In[i] ) Solve( i ) ;
	cout << Ans << endl;  
	return 0 ;  
} 
```

（吐槽 ： 代码效率极低 人丑常数不是一般的大 

就算开O2也是在极限卡时过的 ） 

这个思路其实在这道题里的题解中  [CF835F](https://www.luogu.com.cn/problem/CF835F)  

这位才是[原创作者](https://www.luogu.com.cn/user/73489)

如有冒犯了原创 请多见谅 或是联系窝

---

## 作者：pipiispig (赞：4)

前置知识：单调队列优化环形dp + topsort找环 + 基环树

对于基环树系列的题，最重要的就是找环，其他操作都是基于环的。所以叫“基环树”QwQ
一棵基环树的直径有两种情况：

1、经过环上两个节点外加子树的最深深度，也就是dis(i,j)+dep[i]+dep[j]，其中dep代表从根节点开始所能到达的最深节点，dis代表i到j的最大距离.这里有逆时针和顺时针两种情况， 我们要取大的情况， 也就是我们要断环成链， 进行单调队列优化dp的原因

2、某个不经过环上某个点的子树的最长的直径， 这里我们可以进行dfs或者bfs求最长链， 但是dfs的深度可能是n， 会有爆栈的风险， 所以我们选择bfs；

以上是预处理， 那么我们就要进行单调队列优化了， 这里我们有1点要注意

我们在进行单调队列优化的时候要先弹出开头， 然后计算最大值， 然后再与队列结尾比较弹出结尾！！

对我们可以得知， 本题的要求是一个岛不能重复经过， 也就是一个点不能到达2次， 如果我们是先弹出后面， 再弹出前面， 再计算最大值， 就可能出现， 一个点重复计算2次的情况， 也就是队首元素就是当前元素的特殊情况， 如果不注意的话会得到90分高分（对于这种巨大的错误来说， 90分真的是高分了）

```c++
#include <iostream>
#include <cmath>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <deque>
#include <queue>
#define int long long
#define ll long long
using namespace std;
const int N = 1e6 + 5;
inline int read() {
	int x = 0, f = 1; char c = getchar();
	while(c < '0' || c > '9') {if(c == '-1') f = -1; c = getchar();}
	while(c >= '0' && c <= '9') {x = x * 10 + c - '0'; c = getchar();}
	return f * x;
}
bool vis[N];
int ver[N << 1], e = 1, nexts[N << 1], head[N], ins[N], belong[N];
ll edge[N << 1], ans , dis[N], maxn[N], a[N <<1], b[N <<1];
inline void add(int x, int y, ll z) {
	ver[++ e] = y;
	nexts[e] = head[x];
	head[x] = e;
	edge[e] = z;
	ins[y] ++;
}
int n, tot = 0;
inline void bfs(int x, int num) {
	queue<int> q;
	q.push(x); 
	while(!q.empty()) {
		int x = q.front();
		q.pop();
		belong[x] = num;
		for(int i = head[x]; i; i = nexts[i]) {
			int v = ver[i];
			if(!belong[v]) q.push(v);
		}
	}
}
inline void topsort() {
	queue<int>q;
	for(int i = 1; i <= n; i ++)
		if(ins[i] == 1)
			q.push(i);
	while(!q.empty()) {
		int x = q.front();
		q.pop();
		for(int i = head[x]; i; i = nexts[i]) {
			int v = ver[i];
			if(ins[v] != 1) {
				ins[v] --;	
				maxn[belong[x]] = max(maxn[belong[x]], dis[v] + dis[x] + edge[i]);
				dis[v] = max(dis[v], dis[x] + edge[i]);
				if(ins[v] == 1)
					q.push(v);
			}
		} 
	}
}
inline ll dp(int num, int xx) {
	int x = xx;
	int y = x, m = 0, i;
	ll  Dis = maxn[num], l = 0;
	do {
		a[++m] = dis[y]; ins[y] = 1;
		for(i = head[y]; i; i = nexts[i]) 
			if(ins[ver[i]] > 1) {
				y = ver[i];
				b[m + 1] = b[m] +edge[i];
				break;
			} 
	}while(i);

	for(i = head[y]; i; i = nexts[i])
		if(ver[i] == x) {
			b[m + 1] = b[m] + edge[i];
		}
	for(i = 1; i <m; i ++) {
		a[m + i] = a[i];
		b[m + i] = b[m + 1] + b[i]; 
	}
	deque<int> q;
	q.push_back(1);
	for(i = 2; i < 2 * m; i ++) {
		while(!q.empty() && i - q.front() >= m) q.pop_front();
		Dis = max(Dis, a[i] + a[q.front()] + b[i] - b[q.front()]);
			while(!q.empty() && a[q.back()] + b[i] - b[q.back()] <= a[i]) q.pop_back();
		q.push_back(i);
	}
	return Dis;
}
signed main() {
	//freopen("tjj.in", "r", stdin);
	//freopen("tjj.out", "w", stdout);
	n = read();
	for(int i = 1; i <= n; i ++) {
		int x = read(), y = read();
		add(i, x, y); add(x, i, y);
	}
	for(int i = 1; i <= n; i ++)
		if(belong[i] == 0)
			bfs(i, ++tot);
	topsort();
		for(int i = 1; i <= n; i ++)
		if(ins[i] > 1 && belong[i]) {
			ans += dp(belong[i], i), belong[i] = 0;
		}	
	printf("%lld\n", ans);
}

---

## 作者：是个汉子 (赞：3)

[洛谷传送门](https://www.luogu.com.cn/problem/P4381)

### Solution

因为有 $n$ 个点和 $n$ 条边，所以这就是一个基环树森林。

那么题目让我们求的就是基环树的直径之和。

基环树的直径只有两种可能：1.在以环上某一点为根的子树中  2.在两颗子树中并经过环上一部分

那么分别求出两种可能的最大值然后比较大小即可。

对于第一种可能，选择对每一棵树进行树形DP，正常求树的直径。

同时要记录下来 $len$ 数组，其中 $len_i$ 表示以环上第 $i$ 个点为根的子树中，到根最大的距离。这是为了第二种可能准备。

对于第二种可能，设环为 $E$ ，我们只要求出 $\max\limits_{i,j\in E,j<i}\{len_i+len_j+dis_{i,j}\}$ 。

但是如果枚举 $i,j$ 的话复杂度是不允许的。我们将环破为链，并且复制成两倍，设 $sum_{i}$ 表示从 $1$ 到 $i$ 的 $dis$ 的前缀和，也就是 $sum_i=sum_{i-1}+dis_{i-1,i}$ ，那么上面的式子就成了 $len_i+len_j+sum_i-sum_j\rightarrow len_i+sum_i+len_j-sum_j$ 。

将 $i$ 固定，只考虑 $j$ ，那么对于两个点 $j,k$ ， 如果有 $len_j-sum_j<len_k-sum_k$ ，那么肯定选择 $k$ ，所以用单调队列优化DP。

### Code
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
#define out puts("Debug")
#define int long long
const int N=4e6+9;
int ver[N<<1],nxt[N<<1],w[N<<1],h[N],tot=0;
int dis[N],vis[N],n,x,y,z,res,chk1,chk2,ans,tag[N],num,bc,cnt,ring[N],sum[N];
int f[N],Q[N];
bool Vis[N];

inline void add(int x,int y,int z)
{
	ver[++tot]=y,nxt[tot]=h[x],w[tot]=z,h[x]=tot;
}

inline bool dfs(int u,int le)
{
	if(vis[u]==1)
	{
		vis[u]=2;
		tag[u]=1;
		ring[++cnt]=u;
		return true;
	}
	vis[u]=true;
	for(int i=h[u];i;i=nxt[i])
	{
		int v=ver[i];
		if(i!=((le-1)^1)+1&&dfs(v,i))
		{
			if(vis[u]!=2)
			{
				ring[++cnt]=u,tag[u]=1,sum[cnt]=sum[cnt-1]+w[i];
			}
			else
			{
				sum[bc]=sum[bc+1]-w[i];
				return false;
			}	
			return true;
		}
	}
	return false;
}

inline int dp(int u)
{
	tag[u]=true;
	for(int i=h[u];i;i=nxt[i])
	{
		int v=ver[i];
		if(tag[v]) continue;
		dp(v);
		res=max(res,dis[v]+dis[u]+w[i]);
		dis[u]=max(dis[u],dis[v]+w[i]);
	}
	return res;
}

int get_ans(int rt)
{
	bc=cnt;chk1=chk2=0;
	dfs(rt,-3);
	for(int i=bc+1;i<=cnt;i++)
	{
		res=0;
		int tem=dp(ring[i]);
		chk1=max(chk1,res);
		f[cnt-bc+i]=f[i]=dis[ring[i]];
		sum[cnt-bc+i]=sum[cnt-bc+i-1]+sum[i]-sum[i-1];
	}
	int hh=0,tt=-1;
	for(int i=bc+1;i<=cnt*2-bc;i++)
	{
		while(hh<=tt&&Q[hh]<=i-cnt+bc) ++hh;//warning
		if(hh<=tt) chk2=max(chk2,f[Q[hh]]+f[i]+sum[i]-sum[Q[hh]]);
		while(hh<=tt&&f[Q[tt]]-sum[Q[tt]]<=f[i]-sum[i]) --tt;
		Q[++tt]=i;
	}
	return max(chk1,chk2);
}

signed main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld%lld",&y,&z);
		add(i,y,z),add(y,i,z);
	}
	for(int i=1;i<=n;i++) if(!tag[i]) ans+=get_ans(i);
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：lgswdn_SA (赞：2)

本题其实就是要求**基环森林**中，每棵基环树的直径之和。

求基环树直径也比较无脑：**找到环，把它看成“根节点”**（常见的套路）。然后一个直径有两种可能，第一种是在根节点的一个子树内部。第二种是经过这个环，为了方便，我们可以**破环成链**用前缀和计算环上的两个点的最长距离。

第一种情况用树形 $dp$ 求出 $f_u$（以 $u$ 为顶的最长链）。在求最长链的过程中，我们也可以一边求出直径（也可以再写个 $dfs$ 用换根 $dp$）。

第二种情况破环成链，然后取环上两点 $i,j$，显然 $dis(i,j)+f(i)+f(j)$ 就是取这两个点的答案。我们对所有这样的答案取最大值即可。

部分分代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e6 + 9;
struct edge {
    int to, nxt, w;
} e[N * 2];
int hd[N], tot = 1;
void add(int u, int v, int w) {
    e[++tot] = (edge){ v, hd[u], w };
    hd[u] = tot;
}
int n;

int fa[N], cnt, loop[N], tp, vst[N];
bool inl[N];          // inl表示是否在环中
int sum[N * 2], fat;  //前缀和
bool dfs(int u) {     //人人都会的朴素基环树找环
    vst[u] = 1;
    bool ret = 0;
    for (int i = hd[u]; i; i = e[i].nxt)
        if (i != fa[u]) {
            int v = e[i].to;
            if (!vst[v]) {
                fa[v] = i ^ 1, ret |= dfs(v);
            } else if (vst[v] == 1) {
                tp = v;
                ret = 1;
                loop[++cnt] = v;
                inl[v] = 1;
                fat = i;
            }
        }
    vst[u] = 2;
    if (u == tp)
        ret = 0;
    if (ret)
        loop[++cnt] = u, inl[u] = 1;
    return ret;
}

int tmp = 0, f[N];  // f记录最长链
void dp(int u, int faa) {
    for (int i = hd[u], v; i; i = e[i].nxt) {
        if ((v = e[i].to) == faa || inl[v])
            continue;
        dp(v, u);
        tmp = max(tmp, f[u] + f[v] + e[i].w), f[u] = max(f[u], f[v] + e[i].w);
    }
}

int cal() {  //第二种情况，即直径经过环
    for (int i = 1; i <= cnt + 1; i++) sum[i] = sum[i - 1] + e[fa[loop[i - 1]]].w;
    for (int i = cnt + 2; i <= cnt * 2 + 1; i++)
        sum[i] = sum[i - 1] + (sum[i - cnt] - sum[i - cnt - 1]), loop[i] = loop[i - cnt];
    loop[cnt + 1] = loop[1];
    int ret = 0;
    for (int i = 1; i <= cnt; i++) {
        for (int j = i + 1; j < i + cnt; j++) {
            ret = max(ret, f[loop[i]] + f[loop[j]] + sum[j] - sum[i]);
        }
    }
    return ret;
}

signed main() {
    scanf("%lld", &n);
    for (int i = 1, u, w; i <= n; i++) scanf("%lld%lld", &u, &w), add(u, i, w), add(i, u, w);
    int foin = 0;
    for (int i = 1; i <= n; i++) {
        if (vst[i])
            continue;
        cnt = 0, tmp = 0;
        dfs(i);
        fa[loop[1]] = fat;
        for (int j = 1; j <= cnt; j++) {  //处理环的每个子树内的直径
            int u = loop[j];
            dp(u, 0);
        }
        int ans = max(tmp, cal());
        foin += ans;
    }
    printf("%lld", foin);
    return 0;
}
```

前面的东西都很简单。那复杂度到底在哪里爆炸了？

很显然是这里：

```cpp
for (int i = 1; i <= cnt; i++) {
    for (int j = i + 1; j < i + cnt; j++) {
        ret = max(ret, f[loop[i]] + f[loop[j]] + sum[j] - sum[i]);
    }
}
```

显然，由于这里面的 $i,j$ 是独立的，我们可以用单调队列。

$f_i+f_j+s_j-s_i$ 不大好看，我们换成 $(f_j+s_j)+(f_i-s_i)$，于是我们存 $g_i=f_i-s_i$。

显然这是个**滑动窗口**，窗口大小为 $cnt$，我们每次需要求 $i$ 到 $i+cnt-1$ 这段中 $g_j$ 最大的值。这个单调队列就比较模板了。

```cpp
int cal() {  //第二种情况，即直径经过环
    for (register int i = 1; i <= cnt + 1; i++) sum[i] = sum[i - 1] + e[fa[loop[i - 1]]].w;
    for (register int i = cnt + 2; i <= cnt * 2 + 1; i++)
        sum[i] = sum[i - 1] + (sum[i - cnt] - sum[i - cnt - 1]), loop[i] = loop[i - cnt];
    loop[cnt + 1] = loop[1];
    for (register int i = 1; i <= cnt * 2; i++) g[i] = f[loop[i]] - sum[i];
    int ret = 0;
    for (register int i = 2; i <= cnt * 2; i++) q[i] = 0;  // q初始化
    register int l = 1, r = 2, i = 2;
    q[1] = 1;
    while (i <= cnt * 2) {
        while (l < r && i - q[l] >= cnt) l++;
        ret = max(ret, g[q[l]] + sum[i] + f[loop[i]]);
        while (l < r && g[i] >= g[q[r - 1]]) r--, ret = max(ret, g[q[l]] + sum[i] + f[loop[i]]);
        q[r++] = i++;
    }
    return ret;
}
```

其他都一样，把 cal 里面改了即可。

---

## 作者：Infiltrator (赞：2)

~~这是一道模板题~~  

题意简明扼要，有一堆基环树构成了基环树森林，需求所有基环树的直径之和。  

>基环树定义：一棵树有n个节点n条边  

显然一棵普通的树有n个节点n-1条边，那么基环树就是在普通的树的基础上多加了一条边，这条边必然会形成一个环。  

所以基环树相对于树来讲就是多了一个环的处理。  

基环树的直径求法：

首先肯定要找到环上的所有节点，就是相当于无向图找环。大致上常用的有拓扑排序和dfs，，tarjan也可以。(我使用了dfs找环  

dfs在无向图上找环比较麻烦，它只能处理环的变数>2的环，所以=2的环还要进行特判。（大体来说就是num从1开始建边这样一条边的反向边就是i^1这样特判一下就好了。  

找到环后，通过对一些例子的手玩，不难发现基环树直径的构成情况：  
>1.就是不在环上的节点组成的最长链。  
>2.由环上两点及分别以他们为根的子树中的经过根的最长链构成。

对第一种情况我们开一个数组记录哪些点在环上，对环上每个点分别跑一遍最长链的dp并同时更新answer即可。如果他的儿子在环上就continue。跑完之后再开一个数组记录经过根的最长链。

(最长链dp就是对每个节点求出以他为根的子树且经过他的最长链和次长链，每求完一个节点的信息就对answer进行更新。

对于环上的两点之间的距离，可能是顺时针也可能是逆时针。所以需要破环成链，这样每个节点都会被逆时针顺时针走一遍。求出一个距离前缀数组，两点之间差值即为环上距离。  

那么现在可以写出dp式子$answer=max(answer,d[i]+d[j]+dis[i]-dis[j])$  

这个dp式子的与i有关和与j有关的项是独立的，所以可以单调队列优化。  

对于每个节点找到他之前的$d[j]-dis[j]$最大的j更新即可  

# CODE
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
#define ll long long
#define int long long
#define N 1000050
int head[N],num=1,n,vis[N],ins[N],stack[N],top,circle[N],cnt,flag,zongshu,huan[N],q[N*2],ooo,tmp;
ll ans,answer,dis[N*2],dp[N][2],d[N*2];
struct node
{
	int next,to;
	ll dis;
}edge[N*2];
void addedge(int u,int v,ll w)
{
	edge[++num]=(node){head[u],v,w};
	head[u]=num;
}
void dfs(int x,int fa)
{
	ins[x]=1,stack[++top]=x;
	for(register int i=head[x];i;i=edge[i].next)
	{
		if(flag)return;
		int v=edge[i].to;
		if(v==fa)continue;
		if(ins[v])
        {
            flag=1;circle[++cnt]=v;huan[v]=1;
            while(stack[top]!=v)
                huan[stack[top]]=1,circle[++cnt]=stack[top--];
            return;
        }
		dfs(v,x);
	}
	top--;ins[x]=0;
}
void dfs2(int x,int fa)
{
	if(!vis[x])zongshu++,vis[x]=1;
	for(int i=head[x];i;i=edge[i].next)
	{
		int v=edge[i].to;
		if(v==fa)continue;
		if(!vis[v])dfs2(v,x);
	}
}
void dpp(int x,int fa)
{
	for(int i=head[x];i;i=edge[i].next)
	{
		int v=edge[i].to;
		if(v==fa || huan[v])continue;
		dpp(v,x);
		if(dp[v][0]+edge[i].dis>dp[x][0])
		{
			dp[x][1]=dp[x][0];
			dp[x][0]=dp[v][0]+edge[i].dis;
		}
		else
			if(dp[v][0]+edge[i].dis>dp[x][1])
			{
				dp[x][1]=dp[v][0]+edge[i].dis;
			}
	}
	answer=max((ll)dp[x][0]+dp[x][1],answer);
}
void dfs3(int x,ll uuu)
{
	dis[++ooo]=uuu;
	for(int i=head[x];i;i=edge[i].next)
	{
		if(ooo==2*cnt)return;
		int v=edge[i].to;
		if(v!=q[ooo+1])continue;
		dfs3(v,uuu+edge[i].dis);
	}
}
void find2(int x,int fa,int last)
{
	for(int i=head[x];i;i=edge[i].next)
	{
		if(flag)return;
		int v=edge[i].to;
		if(v==fa && i!=last && i!=(last^1))
		{
			circle[++cnt]=x;
            circle[++cnt]=fa;
            huan[x]=huan[fa]=1;flag=1;
            tmp=max(edge[i].dis,edge[last].dis);
		}
		else if(v!=fa)find2(v,x,i);
	}
}
ll solve(int root)
{
	zongshu=0;
	dfs2(root,0);
	if(zongshu==2)
	{
		answer=0;
		for(int i=head[root];i;i=edge[i].next)answer=max(answer,edge[i].dis);
		return answer;
	}
	for(int i=1;i<=n;i++)stack[i]=0,ins[i]=0;
	flag=top=cnt=answer=0;
	dfs(root,0);
	if(cnt==0)
	{
		flag=0;
		tmp=0;
		find2(root,0,-1);
		for(int i=1;i<=cnt;i++)dpp(circle[i],0),d[circle[i]]=dp[circle[i]][0];
		answer=max(answer,tmp+d[circle[1]]+d[circle[2]]);
		return answer;
	}
	ooo=0;
	for(int i=1;i<=cnt;i++)dpp(circle[i],0),d[circle[i]]=dp[circle[i]][0];
	for(int i=1;i<=cnt;i++)q[i]=circle[i],q[i+cnt]=circle[i],circle[i+cnt]=circle[i];
	dfs3(q[1],0);
	int head=0,tail=1;
	q[++head]=1;
	for(int i=2;i<=2*cnt;i++)
	{
		while(head<=tail && q[head]<=i-cnt)head++;
		answer=max(answer,d[circle[i]]+d[circle[q[head]]]+dis[i]-dis[q[head]]);
		while(head<=tail && d[circle[i]]-dis[i]>=d[circle[q[tail]]]-dis[q[tail]])tail--;q[++tail]=i;
	}
	return answer;
}
signed main()        
{
	freopen("random.out","r",stdin);
	freopen("myanswer.out","w",stdout);
	scanf("%lld",&n);
	int u;ll v;
	for(int i=1;i<=n;i++)scanf("%lld%lld",&u,&v),addedge(i,u,v),addedge(u,i,v);
	for(int i=1;i<=n;i++)if(!vis[i])ans+=solve(i);
	printf("%lld",ans);
	return 0;
}
```
------
这应该是这道题最丑最长的一份代码，为了求环跑了一遍dfs，为了标记跑了一遍dfs，为了求前缀和又跑了一遍dfs，特判还有一遍dfs

---

## 作者：风随逐影 (赞：2)

# 基环树
~~（我的第二道黑题）~~


------------
### 思路：
1. 根据题意，若以前使用过的渡船组合可以由S走到D，则D点不能被到达

1. 换句话说基环树上的点全部可以被到达，但离开一个基环树以后，不能再回到原来的那颗基环树。

1. 那么问题就转换成了求基环森林的最长链之和。


------------

#### 包含的知识点：
1. 无向图缩点
1. 拓扑排序找基环（排序以后入度仍大于1的为环）
1. 重边的处理
1. 用BFS写树形DP求直径
1. 基环树直径的求法
1. 破环成链的应用
1. 单调队列优化DP


------------

代码如下

```c
//b[m+i]表示转了一圈后到达i号点经过的距离 
#include<bits/stdc++.h>
using namespace std;
#define go(i,a,b) for(int i=(a);i<=(b);++(i))
#define com(i,a,b) for(int i=(a);i>=(b);--(i))
#define mem(a,b) memset((a),(b),sizeof(a))
#define inf 0x3f3f3f3f
#define fin freopen("input.txt","r",stdin)
#define fout freopen("output.txt","w",stdout)
const int maxn=1000010;
typedef long long ll;
int head[maxn],que[maxn*2],du[maxn],c[maxn],cnt=0,tim=0,n;
bool vis[maxn];
ll f[maxn],d[maxn],a[2*maxn],b[2*maxn];
struct edge{
    int nxt,v,w;
}e[maxn*2];

void read(int &x){
    int f=1;char s=getchar();x=0;
    while(!isdigit(s)){
    	if(s=='-') f=-1;s=getchar();
    }
    while(isdigit(s)){
   		x=(x<<3)+(x<<1)+s-'0';s=getchar();
    }
    x*=f;
}//读入优化

void add(int u,int v,int w){
    e[cnt]=(edge){head[u],v,w};
    head[u]=cnt++;du[v]++;
}
queue<int>q;

void bfs(int st,int tim){//标记每个点所属的基环树的编号
    c[st]=tim;q.push(st);
    while(!q.empty()){
        int u=q.front();q.pop();
        for(int i=head[u];i+1;i=e[i].nxt){
            int v=e[i].v;if(c[v]) continue;
            c[v]=tim;q.push(v);
        }
    }
}

void topsort(){
 	go(i,1,n) if(du[i]==1) q.push(i);
    while(!q.empty()){
        int u=q.front();q.pop();
        for(int i=head[u];i+1;i=e[i].nxt){
            int v=e[i].v,w=e[i].w;
            if(du[v]<=1) continue;//在有向图中可以不加这句话
            //在无向图中存在访问父节点的可能 ，而父节点的du为1，起到排除父节点的作用 
            d[c[u]]=max(d[c[u]],f[u]+f[v]+w);
            //当前子树最长链==f[x]+w,f[y]==之前子树中的最长链 
            f[v]=max(f[v],f[u]+w);//当前链变为之前链
            if((--du[v])==1) q.push(v);
        }
    }
}

void dp(int x,int co){
    int l=0,r,m=0,y=x,i;
    do{
        a[++m]=f[y];du[y]=1;
        for(i=head[y];i+1;i=e[i].nxt){
            int v=e[i].v,w=e[i].w;
            if(du[v]>1){
            y=v;b[m+1]=b[m]+w;break;
            }
        }
    }while(i+1);
    if(m==2){//处理重边
        for(i=head[y];i+1;i=e[i].nxt){
            if(e[i].v==x) l=max(l,e[i].w);
        }
        d[co]=max(d[co],f[x]+f[y]+l);return;
    }
    for(i=head[y];i+1;i=e[i].nxt){
        if(e[i].v==x){
        b[m+1]=b[m]+e[i].w;break;
		//特别提醒：b[m+1]=max(b[m+1],b[m]+e[i].w)这种写法是错误的
		//首先，有重边的都已被单独算作环，不需要考虑最大值
		//其次，由于可能有多个基环树，b[m+1]的值可能已经求出，并且比正确的值更大 
        }
    }
    for(i=1;i<m;i++)a[i+m]=a[i],b[i+m]=b[i]+b[m+1];
    que[l=r=1]=1;//记住：手写队列的条件永远是L<=r 
    for(i=2;i<2*m;i++){//单调队列优化DP 
        while(l<=r&&i-que[l]>=m) l++;
        d[co]=max(d[co],a[i]+a[que[l]]+b[i]-b[que[l]]);
        while(l<=r&&a[i]-b[i]>=a[que[r]]-b[que[r]]) r--;
        que[++r]=i;
    }
}

int main()
{
    //fin;
    mem(head,-1);
    read(n);
    go(i,1,n){
        int v,w;read(v);read(w);
        add(i,v,w),add(v,i,w);
    }
    go(i,1,n){
        if(!c[i]) bfs(i,++tim);
    }
    topsort();//判环（两个点有重边的也算作环）
    ll ans=0;
    go(i,1,n){
        if(!vis[c[i]]&&du[i]>1){
            vis[c[i]]=1;
            dp(i,c[i]);
            ans+=d[c[i]];
        }
    }
    printf("%lld",ans);
    return 0;
}
```


---

## 作者：DukeLv (赞：2)

这个题有点坑,这里提供一个思路.

这里其实可以用tarjan判一下联通块的个数以及其中包含的元素(滑稽),然后记录每个块的代表元素.
放一下tarjan代码,大家可以参考一下.

```
void tarjan(int x)
{
	low[x] = dfn[x] = ++cnt;
	str[++top] = x;
	vis[x] = 1;
	for(int k = lst[x];k;k = a[k].nxt)
	{
		int y = a[k].r;
		if(!dfn[y])
		{
			tarjan(y);
			low[x] = min(low[x],low[y]);
		}
		else if(vis[y])
		{
			low[x] = min(low[x],dfn[y]);
		}
	}
	if(low[x] == dfn[x])
	{
		ans++;
		int v;
		da[ans] = x;
		do
		{
			num[ans]++;
			vis[str[top]] = 0;
			v = str[top--];
			col[v] = ans;
		}
		while(x != v);
	}
}
```

判完之后,大家有没有发现和NOIP2018D2T1有一点像,都是判环,所以我们可以搞一个dfs,然后维护一个栈,每次压入,但是结束的时候有多余元素怎么办呢?我们从队首向后找,找到成环的位置就行了.

找环代码:

```

void cir(int x,int fa,int lenth)
{
	// cout<<x<<" "<<fa<<endl;
	if(vis[x] != 0)
	{
		// cout<<x<<" "<<fa<<" "<<lenth<<endl;
		f1 = x;f2 = fa;
		lst_len = lenth;
		return;
	}
	str[++top] = x;
	leng[top] = lenth;
	vis[x] = 1;
	/*duke(i,1,top)
	{
		printf("%d ",str[i]);
	}
	enter;*/
	int mx = 0,rem = 0;
	for(int k = lst[x];k;k = a[k].nxt)
	{
		int y = a[k].r;
		if(y == fa)
		{
			rem = fa;
			mx = max(mx,a[k].w);
			fa = 0;
			continue;
		}
		if(rem != 0 && y == rem)
		{
			// cout<<mx<<" "<<a[k].w<<endl;
			a[k].w = max(a[k].w,mx);
			cir(y,x,max(a[k].w,mx));
		}
		cir(y,x,a[k].w);
		if(f1 != 0 && f2 != 0) return;
	}
	top--; vis[x] = 0;
}
int dp(int x)
{
	f1 = f2 = 0;
	clean(str);top = 0;
	cir(x,0,0);
	/*duke(i,1,top)
	{
		printf("%d ",str[i]);
	}
	puts("");*/
	duke(i,1,top)
	{
		if(str[tail] != f1 && str[tail] != f2)
		{
			tail++;
		}
	}
}

```

剩下好像就是基本操作,维护单调队列来优化复杂度,每个奇环树上找最大的长度,2种情况,可以选两个点和中间的路径,也可以就是自己加上环的总长度.

总的来说这个题是个好题...

---

## 作者：虚心竹gulu (赞：1)

#### **题目大意**

求各个基环树的直径和

先用dfs或拓扑排序找到基环树的环，把环上的点标记，再对每个点进行dfs，就可以访问以该点为根的子树。
在每棵子树中求出直径。设$f[x]$表示以$x$为根的子树的直径。设$i,j$为环上两点,$d[i]$表示环上边权的前缀和。
那么基环树的直径就是$f[i]+f[j]+d[j]-d[i]$,其中$d[j]-d[i]$是$i,j$两点的在环上的距离。对于d数组，可以把环断开复制一遍，枚举j,用单调队列维护$f[i]-d[i]$的最大值.
时间复杂度：$O(n)$
```cpp
#include <iostream> 
#include <queue>
using namespace std;
int n;
int nx[2000006],he[1000006],vr[2000006],eg[2000006],tot;
inline void add(int x,int y,int z){
	vr[++tot]=y;
	eg[tot]=z;
	nx[tot]=he[x];
	he[x]=tot;
}
int in[1000006],ku[1000006],v[1000006],t,q[2000006];
long long ans,d[1000006],f[1000006],a[1000006],b[1000006];
// 一定要开long long !!!
void topsort(){
	queue<int> q;
	for(int i=1;i<=n;++i) if(in[i]==1) q.push(i);
	while(q.size()){
		int x=q.front();
		q.pop();
		for(int i=he[x];i;i=nx[i]){
			if(in[vr[i]]>1){
				d[ku[x]]=max(d[ku[x]],f[x]+f[vr[i]]+eg[i]);
				f[vr[i]]=max(f[vr[i]],f[x]+eg[i]);// 树的直径
				if(--in[vr[i]]==1) {
					q.push(vr[i]);
				}
			}
		}
	}
}
void dp(int k,int x){
	int m=0;// 环上点的数量
	int y=x,z=0,len=0;
	do{
		a[++m]=f[y];// 记录以环上各点为根的子树的直径
		in[y]=1;
		for(z=he[y];z;z=nx[z]){
			if(in[vr[z]]>1){
				y=vr[z];
				b[m+1]=b[m]+eg[z];// 标记环上的点
				break;
			}
		}
	}while(z);
	if(m==2){
		for(int i=he[y];i;i=nx[i]){
			if(vr[i]==x){
				len=max(len,eg[i]);
			}
		}
		d[k]=max(d[k],f[x]+f[y]+len);
		return;
	}
	for(int i=he[y];i;i=nx[i]){
		if(vr[i]==x){
			b[m+1]=b[m]+eg[i];
			break;
		}
	}
	for(int i=1;i<m;++i){
		a[i+m]=a[i];b[i+m]=b[m+1]+b[i]; // 复制
	}
	int l,r;
	q[l=r=1]=1;// 单调队列
	for(int i=2;i<(m<<1);++i){
		while(l<=r && i-q[l]>=m) ++l;
		d[k]=max(d[k],a[q[l]]+a[i]+b[i]-b[q[l]]);
		while(l<=r && a[q[r]]-b[q[r]]<=a[i]-b[i]) --r;
		q[++r]=i;
	}
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin>>n;
	int x,z;
	for(int i=1;i<=n;++i){
		cin>>x>>z;
		add(x,i,z);
		add(i,x,z);
		++in[x];++in[i];
	}
	queue<int> q;
	for(int i=1;i<=n;++i){ // 遍历每个连通块
		if(ku[i]) continue;
		while(q.size()) q.pop();
		q.push(i);
		ku[i]=++t;
		while(q.size()){
			x=q.front();
			q.pop();
			for(int i=he[x];i;i=nx[i]){
				if(ku[vr[i]]) continue;
				q.push(vr[i]);
				ku[vr[i]]=t;
			}
		}
	}
	topsort();// 拓扑排序
	for(int i=1;i<=n;++i){
		if(in[i]>1 && !v[ku[i]]) { // 如果该点入度大于1，那么就是环上的点
			v[ku[i]]=1;// 标记
			dp(ku[i],i);
			ans+=d[ku[i]];// 统计每个基环树最长简单路径
		}
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：lky1433223 (赞：1)

# [IOI2008]Island
# [推销博客](https://www.cnblogs.com/Shiina-Rikka/p/11701492.html)
本篇博客的程序在洛谷以及darkBZOJ通过，但是使用的是DFS，在BZOJ可能导致爆栈。（不过BZOJ爆炸了我也没办法测）
## 题面
你准备浏览一个公园，该公园由 $N$ 个岛屿组成，当地管理部门从每个岛屿 $i$ 出发向另外一个岛屿建了一座长度为 $L_i$ 的桥，不过桥是可以双向行走的。同时，每对岛屿之间都有一艘专用的往来两岛之间的渡船。相对于乘船而言，你更喜欢步行。你希望经过的桥的总长度尽可能长，但受到以下的限制：
- 可以自行挑选一个岛开始游览。
- 任何一个岛都不能游览一次以上。
- 无论任何时间，你都可以由当前所在的岛 $S$ 去另一个从未到过的岛 $D$。从 $S$ 到 $D$ 有如下方法：
  - 步行：仅当两个岛之间有一座桥时才有可能。对于这种情况，桥的长度会累加到你步行的总距离中。
  - 渡船：你可以选择这种方法，仅当没有任何桥和以前使用过的渡船的组合可以由 $S$ 走到 $D$ (当检查是否可到达时，你应该考虑所有的路径，包括经过你曾游览过的那些岛)。

**注意，你不必游览所有的岛，也可能无法走完所有的桥。**
请你编写一个程序，给定 $N$ 座桥以及它们的长度，按照上述的规则，计算你可以走过的桥的长度之和的最大值。
## 解
通过对题面的分析，我们发现给出的图是一个基环树森林。（$n$个点$n$条边不保证图联通）

因此我们的答案便是每棵基环树上长度最大的简单路径。这个路径就是基环树的直径。

这个问题就被转化成了求基环树的直径。通过分析我们发现基环树的直径有两种情况：
- 位于基环树上某一棵树上。
- 基环树上两颗树的链加上他们之间环上的路径。

求第一种情况，$DP$求即可。
对于第二种情况，我们把环断成链进行操作。

----

##### 具体细节：
**1.找环**

这道题找环不能记$father$,因为会有这个样子的环：

![这个](https://s2.ax1x.com/2019/10/18/Ke082T.png)

如果记$father$这个环就跑不到了。

我使用了直接标记边的方法以防止跑到反向边。

在建边时题目给出的正向边的id都是偶数，反向边都是奇数，这样就不会跑反向边。
```cpp
    for (register int i = head[x]; i; i = e[i].nxt)
    {
        if (i & 1)
            continue;
    }
```
我们发现题目原本是建立双向道路这样无法遍历整个图，但我们跑环不需要遍历啊，所以并查集维护一下就好了。
```cpp
class FIND
{
public:
    int fa[MAXN];
    inline int find(int x)
    {
        return fa[x] == x ? fa[x] : fa[x] = find(fa[x]);
    }
    inline void merge(int x, int y)
    {
        x = find(x);
        y = find(y);
        if (x != y)
            fa[y] = x;
    }
    inline void init()
    {
        for (register int i = 1; i <= n; ++i)
            fa[i] = i;
    }
} fd;

if (fd.find(i) == i)
{
    now = i;
    rd[0].push_back(now);
    top = 0;
    v[0] = 0;
    dfs_round(i);
} 
```
**2.一棵树的直径**

使用DP法求树的直径，同时维护树的深度。
```cpp
void dp(int x)
{
    v[x] = 1;
    for (register int i = head[x]; i; i = e[i].nxt)
    {
        register int y = e[i].ver;
        if (v[y] || rond[y])
            continue;
        dp(y);
        d[now] = max(d[now], f[x] + f[y] + e[i].edge);
        f[x] = max(f[x], f[y] + e[i].edge);
        l[now] = max(l[now], f[x]);
    }
}
```
**3.基环树的直径**

第一种在一棵树上的情况已经求出，现在计算链加路径的情况。

环上问题使用DP求解将环断成链并复制成两倍。

使用$L[i]$表示以$i$为根的树的最长链长度，$f[i]$表示$i$到断开的点在环上的路径长度。

枚举右端点$r$,当左端点是$l$时的答案

$ans = \max(ans,L[r] + L[l] + f[r] - f[l])$

也就是说，我们要维护出在合法范围内，$L[i] - f[i]$最小的点。

枚举右端点，使用单调递增的单调队列进行维护左端点。

推荐[环路运输](https://ac.nowcoder.com/acm/contest/1045/B?&headNav=acm)
- 队头状态不合法，出队
- 当前队头元素便是最优左端点，更新答案
- 如果队尾元素大于当前元素，弹队尾
- 将当前元素入队
```cpp
    for (register int i = 1; i <= len; ++i)
        g[i] = g[i + len] = l[s[i]];
    ans = 0;
    for (register int i = 1; i < len * 2; ++i)
    {
        while (q.size() && i - q.front() >= len)
            q.pop_front();
        if (q.size())
        {
            ans = max(ans, f[i] - f[q.front()] + g[i] + g[q.front()]);
        }
        while (q.size() && g[i] - f[i] > g[q.back()] - f[q.back()])
            q.pop_back();
        q.push_back(i);
    }
```
大体就是这样，具体的在代码里有注释。

另外特别注意一点，由于每次dfs只是一个连通块，并不会遍历整张图，所以并没有必要dfs一遍就清空vis数组，这样会导致TLE，而是应该当前图被完全遍历之后清空vis数组。
## 放代码
```cpp
#include <bits/stdc++.h>
using namespace std;
//快读
namespace fdata
{
inline char nextchar()
{
    static const int BS = 1 << 21;
    static char buf[BS], *st, *ed;
    if (st == ed)
        ed = buf + fread(st = buf, 1, BS, stdin);
    return st == ed ? -1 : *st++;
}
template <typename Y>
inline void poread(Y &ret)
{
    ret = 0;
    char ch;
    while (!isdigit(ch = nextchar()))
        ;
    do
        ret = ret * 10 + ch - '0';
    while (isdigit(ch = nextchar()));
}
#undef nextcar
} // namespace fdata
using fdata::poread;
const int MAXN = 1e6 + 10;
int n;
struct node
{
    int nxt, ver, edge;
} e[MAXN << 1];
int head[MAXN], tot = 1;
inline void add(const int &x, const int &y, const int &z)
{
    e[++tot].ver = y;
    e[tot].edge = z;
    e[tot].nxt = head[x];
    head[x] = tot;
}
//并查集 没错我封装了
class FIND
{
public:
    int fa[MAXN];
    inline int find(int x)
    {
        return fa[x] == x ? fa[x] : fa[x] = find(fa[x]);
    }
    inline void merge(int x, int y)
    {
        x = find(x);
        y = find(y);
        if (x != y)
            fa[y] = x;
    }
    inline void init()
    {
        for (register int i = 1; i <= n; ++i)
            fa[i] = i;
    }
} fd;
#define int long long
//双端队列 没错我自己封装的
class QUE
{
private:
    long long q[MAXN << 1];
    int l = 1, r;

public:
    inline bool size()
    {
        return r >= l;
    }
    inline void init()
    {
        l = 1, r = 0;
    }
    inline void push_back(const long long x)
    {
        q[++r] = x;
    }
    inline long long back()
    {
        return q[r];
    }
    inline void pop_back()
    {
        --r;
    }
    inline void pop_front()
    {
        ++l;
    }
    inline long long front()
    {
        return q[l];
    }
} q;
bool v[MAXN << 1];
int sta[MAXN], top;
int rond[MAXN], now;
//使用vector记录环上的点
vector<int> rd[MAXN];
//找环
inline bool dfs_round(int x)
{
    //入栈
    sta[++top] = x;
    v[x] = 1;
    for (register int i = head[x]; i; i = e[i].nxt)
    {
        //判断是不是反向边
        if (i & 1)
            continue;
        register int y = e[i].ver;
        //当前点跑到过  已经跑完了这个环 栈中到当前点点之间的点就是环上的点
        if (v[y])
        {
            register int z = 0;
            do
            {
                z = sta[top--];
                assert(z);
                rd[now].push_back(z);
                rond[z] = now;
            } while (z != y);
            return 1;
        }
        if (dfs_round(y))
            return 1;
    }
    sta[top--] = 0;
    return 0;
}
long long f[MAXN << 1], s[MAXN << 1], d[MAXN], l[MAXN << 1];
long long g[MAXN << 1];
//求树的直径
void dp(int x)
{
    v[x] = 1;
    for (register int i = head[x]; i; i = e[i].nxt)
    {
        register int y = e[i].ver;
        if (v[y] || rond[y])
            continue;
        dp(y);
        d[now] = max(d[now], f[x] + f[y] + e[i].edge);
        f[x] = max(f[x], f[y] + e[i].edge);
        l[now] = max(l[now], f[x]);
    }
}
long long ans;
int len;
//跑环
inline void dfs(int x, int nw)
{
    for (register int i = head[x]; i; i = e[i].nxt)
    {
        register int y = e[i].ver;
        if (v[i] || !rond[y])
            continue;
        v[i] = v[i ^ 1] = 1;
        //边的长度
        f[nw] = e[i].edge;
        //环上的点，顺序记录便于DP
        s[nw] = y;
        dfs(y, nw + 1);
    }
}
/*计算答案*/
inline long long sov(const int &now)
{
    int len = rd[now].size();
    s[1] = rd[now][0];
    dfs(rd[now][0], 2);
    q.init();
    //断环成链并复制
    for (register int i = 2; i <= len; ++i)
        f[i + len + 1 - 1] = f[i];
    //求前缀和，O(1)查询区间和
    for (register int i = 1; i <= len * 2; ++i)
        f[i] = f[i - 1] + f[i];
    //将环上每棵树的深度信息复制
    for (register int i = 1; i <= len; ++i)
        g[i] = g[i + len] = l[s[i]];
    ans = 0;
    //DP求第二种情况
    for (register int i = 1; i < len * 2; ++i)
    {
        while (q.size() && i - q.front() >= len)
            q.pop_front();
        if (q.size())
        {
            ans = max(ans, f[i] - f[q.front()] + g[i] + g[q.front()]);
        }
        while (q.size() && g[i] - f[i] > g[q.back()] - f[q.back()])
            q.pop_back();
        q.push_back(i);
    }
    //第一种情况，直接取max
    for (register vector<int>::iterator it = rd[now].begin(); it != rd[now].end(); ++it)
    {
        ans = max(ans, d[*it]);
    }
    return ans;
}
signed main()
{
    poread(n);
    fd.init();
    for (register int i = 1, y, z; i <= n; ++i)
    {
        //建图 维护连通性
        poread(y), poread(z);
        add(i, y, z);
        add(y, i, z);
        fd.merge(i, y);
    }
    for (register int i = 1; i <= n; ++i)
    {
        //遍历每一个连通块 求环
        if (fd.find(i) == i)
        {
            now = i;
            rd[0].push_back(now);
            top = 0;
            v[0] = 0;
            dfs_round(i);
        }
    }
    //整张图完全遍历 清空vis
    memset(v, 0, sizeof(v));
    //对每一个环上的点为根的树求直径和深度
    for (vector<int>::iterator it = rd[0].begin(); it != rd[0].end(); ++it)
    {
        for (register vector<int>::iterator jt = rd[*it].begin(); jt != rd[*it].end(); ++jt)
        {
            now = *jt;
            dp(*jt);
        }
    }
    memset(v, 0, sizeof(v));
    long long ANs = 0;
    //对每一个连通块求解并统计答案
    for (vector<int>::iterator it = rd[0].begin(); it != rd[0].end(); ++it)
    {
        ANs += sov(*it);
    }
    cout << ANs << endl;
    return 0;
}

```

---

## 作者：Llf0703 (赞：1)

推广博客：https://llf0703.com/p/luogu-4381.html

## 题意

给出一个基环森林，求所有基环树的直径之和。

点数 $N\le 10^6$ 。

## 题解

### 思想

先考虑求一个基环树的直径。

设 $\text{f[i]}$ 是 $i$ 向环外延伸的最长距离，直径有两种情况：

1. 不经过环，答案为环的子树直径，即 $\mathrm{max}(\text{f[x]}+\text{f[y]}+w)$ ，其中 $x,y$ 是子树中两点，$w$ 是两点距离。
2. 经过环，则答案为 $\mathrm{max}(\text{f[x]}+\text{f[y]}+\mathrm{len}(x,y))$ ，其中 $x,y$ 是环上两点，$\mathrm{len(x,y)}$ 是两点在环上的较长距离。

对于情况 $2$ ，直接 $O(n^2)$ 枚举肯定会爆，考虑断环成链后用单调队列优化。

将环断成原来的两倍长，从任意一个点出发，用 $\text{s[i]}$ 表示第 $i$ 个点，设编号为 $p$ ，的 $\text{f[p]}$ 值 ；用 $\text{dis[i]}$ 代表 $i$ 距离起点的距离。答案化为

$$s[x]+s[y]+dis[y]-dis[x]$$

枚举 $y$ ，去除已知量后答案化为

$$s[x]-dis[x]$$

要求这个值最大 ，用单调队列维护就行了。

最后对于每个子树，对两种情况取最大值相加即可。

### 实现

1. 先用 $\text{dfs}$ 求出每个点 $i$ 所属的子树 $\text{scc[i]}$ 。
2. 拓扑排序找环，还可以用树形dp顺便求出 $\text{f[i]}$ 和上述情况 $1$ 。
3. 从任意一个在环上的点出发断环成链，注意还需要找终点到起点的边。完成后将子树标记，$vis[scc[x]]=1$ 。
4. 用单调队列求出情况 $(2)$ 的答案。注意两个点成环的重边情况需要单独考虑。
5. 开 `long long` 。

### 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 1000005

using namespace std;

inline ll read()
{
    char ch=getchar();
    ll f=1,x=0;
    while (ch<'0' || ch>'9')
    {
        if (ch=='-') f=-1;
        ch=getchar();
    }
    while (ch>='0' && ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return f*x;
}

struct Edge {
    ll next,to,w;
} edge[N<<1];
bool vis[N];
ll cnt,head[N],n,a,b,ans,scnt,scc[N],deg[N],mx[N],f[N],s[N],dis[N];

inline void add(ll u,ll v,ll w); //加边
void dfs(ll x); //dfs划分子树
inline void t_sort(); //拓扑排序，处理情况1
inline void dp(ll x); //处理情况2

signed main()
{
    n=read();
    for (ll i=1;i<=n;i++)
    {
        a=read(); b=read();
        add(i,a,b);
        add(a,i,b);
        deg[i]++; deg[a]++; //度数
    }
    for (ll i=1;i<=n;i++) //划分子树
    {
        if (scc[i]) continue;
        scnt++;
        dfs(i);
    }
    t_sort();
    for (ll i=1;i<=n;i++)
    {
        if (!deg[i] || vis[scc[i]]) continue; //不在环上或该子树被访问过则跳过
        dp(i);
        ans+=mx[scc[i]]; //统计答案
    }
    return !printf("%lld",ans);
}

inline void add(ll u,ll v,ll w)
{
    edge[++cnt].to=v;
    edge[cnt].w=w;
    edge[cnt].next=head[u];
    head[u]=cnt;
}

void dfs(ll x) //划分子树
{
    scc[x]=scnt;
    for (ll i=head[x];i;i=edge[i].next)
    {
        ll y=edge[i].to;
        if (scc[y]) continue;
        dfs(y);
    }
}

inline void t_sort() //拓扑排序
{
    queue <ll> q;
    for (ll i=1;i<=n;i++)
    {
        if (deg[i]>1) continue;
        q.push(i); //不在环上入队
    }
    while (!q.empty())
    {
        ll x=q.front(); q.pop();
        for (ll i=head[x];i;i=edge[i].next)
        {
            ll y=edge[i].to,w=edge[i].w;
            if (!deg[y]) continue; //父节点跳过
            mx[scc[x]]=max(mx[scc[x]],f[x]+f[y]+w);
            f[y]=max(f[y],f[x]+w); //树形dp
            deg[x]--; deg[y]--;
            if (deg[y]==1) q.push(y);
        }
    }
}

inline void dp(ll x)
{
    ll st=x,id=scc[x],pcnt=0; //pcnt为环上点的个数
    vis[id]=1; //标记已处理过
    for (;;)
    {
        s[++pcnt]=f[x];
        deg[x]=0; //标记访问过
        bool flag=0; //flag表示还有下一个点
        for (ll i=head[x];i;i=edge[i].next)
        {
            ll y=edge[i].to,w=edge[i].w;
            if (!deg[y]) continue; //不在环上或访问过
            flag=1;
            dis[pcnt+1]=dis[pcnt]+w;
            x=y;
            break;
        }
        if (!flag) break; //没有下一个点了退出
    }
    if (pcnt==2) //单独处理两点成环的情况
    {
        ll res=0;
        for (ll i=head[x];i;i=edge[i].next)
        {
            ll y=edge[i].to,w=edge[i].w;
            if (y!=st) continue;
            res=max(res,w);
        }
        mx[id]=max(mx[id],f[st]+f[x]+res);
    }
    for (ll i=head[x];i;i=edge[i].next) //从终点到起点
    {
        ll y=edge[i].to,w=edge[i].w;
        if (y!=st) continue;
        dis[pcnt+1]=dis[pcnt]+w;
        break;
    }
    for (ll i=1;i<pcnt;i++) //扩成两倍
    {
        s[i+pcnt]=s[i];
        dis[i+pcnt]=dis[1+pcnt]+dis[i];
    }
    deque <ll> q;
    q.emplace_back(1);
    for (ll i=2;i<(pcnt<<1);i++) //单调队列得到答案
    {
        while (!q.empty() && i-q.front()>=pcnt) q.pop_front();
        if (!q.empty()) mx[id]=max(mx[id],s[i]+s[q.front()]+dis[i]-dis[q.front()]);
        while (!q.empty() && s[q.back()]-dis[q.back()]<=s[i]-dis[i]) q.pop_back();
        q.emplace_back(i);
    }
}
```

---

## 作者：Piwry (赞：0)

这题的单调队列优化不是对所有基环树上路径最值问题都适用的；

例如 [CF835F](https://www.luogu.com.cn/problem/CF835F)，直接套用，将每次从单调队列取出的答案的取 max 改成取 min，是错的，因为每次从单调队列取出的答案实际上**并不是当前断环方案的树直径**。

高赞貌似都没提到这点，于是就写个题解补充下了

## 解析

### 找环

由于数据给出的是一个森林，因此特判部分可能会比较多

这里讲一个我做时遇到的坑点：

有一个想法是用 `vis` 数组记录已 dfs 的点，如果 dfs 到了已遍历的点（且不是 dfs 树父亲），就代表找到了一个环。每次找到环后立即给整个环染色标记，不做其他特殊处理（也不清空 `vis`）。在下次 dfs 时如果遇到染色的点，就代表正在遍历一个已经找到环的连通子图，直接返回；否则就检查这个点是否已遍历过（检查 `vis` 数组），接着按上述方式处理

但这种方法并不能百分百发现当前连通子图是已经找到环的，还会判错环，考虑这样的情况：

![findCircle](https://cdn.luogu.com.cn/upload/image_hosting/69x7sc3p.png)

程序会认为找到了一个环，但这实际上是错的

正确的方式是在找到环后给当前整个连通子图都打上标记（可能还需要一个数组），之后不再遍历打上该标记的结点

### 找直径

（或者说图中最长路径，一般都是这么定义的X）

我们先对环上 “挂着” 的树都做一次树内 dp，并统计出树内的最长路径，接下来就只需考虑过环的路径是否可能成为直径，最后给这两个路径取个 max 就可以了

在做树 dp 时，我们应该已经对环上每一个点处理出了它只向子树走的最长路径，记为 $f(u)$

一个路径从某个子树进入环，它可能顺时针走环，也可能逆时针走环进入另外一个子树；如果它是顺时针走环，其实也可以看做从终点子树逆时针走过来。因此我们规定只能往一个方向走环

我们随便设环上一个结点为起点，并从它开始按规定方向不重复遍历环上结点，就得到了一个序列 $\{u_0, \cdots, u_{k-1}\}$，设序列从 $0$ 开始，其中 $k$ 为环上结点个数。对于一条路径，它有可能只经过这序列上**连续**的一段，也有可能跨过 $u_{k-1}$，变成了两段，但它最多遍历 $k$ 个结点；如果我们将该序列复制一遍，得到序列 $\{u_0, \cdots, u_{k-1}, u_0, \cdots, u_{k-1}\}$，重标号为 $\{u_0, \cdots, u_{k-1}, u_k, \cdots, u_{2k-1}\}$，并且规定路径只从左半段区间内的元素出发，就可以保证任何可能的环上路径都在这序列中是**连续的一段**。同时我们还要保证路径的长度至多为 $k$；这实际上就像一个宽为 $k$ 滑动窗口在序列中滑动

再来考虑一段路径的贡献，其显然为 $f(u)+f(v)+dist(u, v)$，其中 $u$ 是环上起点，$v$ 是环上终点，$dist(u, v)$ 指从 $u$ 到 $v$ 在环上按规定方向遍历的路径长

而 $dist(u, v)$ 其实可以用前缀和维护。具体来说，给 $u_0$ 赋权值 $0$，对于其余的 $u_i$ 赋权值 $w(u_{i\mod k}, u_{(i-1)\mod k})$，其中 $w(u, v)$ 指图中对应边的权值；我们给这个值做一个前缀和，记为 $s(u)$，上面的贡献式子就可以写为 $f(u)-s(u)+f(v)+s(v)$，我们要**令它最大**

（**接下来是开头提到的部分了**）

滑动窗口加最值，很容易想到单调队列，于是就有一种分别维护 $f(i)-s(i)$ 和 $f(i)+s(i)$ 最值的思想。但注意这两个最值可能取同样的 $i$（如果 $f(i)$ 足够大），这时就要求维护滑动窗口维护次大值，但**这是单调队列不可做的**（例如像开头提到那题，强制要求求出每次断边后的树直径，不能用单调队列）

于是我们再换一种思路，考虑枚举其中一个元素，而单调队列维护另一个。具体来说，我们从 $i=k-1$ 开始枚举，每次枚举当前结点 $u_i$ 的 $f(u_i)+s(u_i)$，并用单调队列维护 $[u_{i-(k-1)}, u_{i-1}]$ 区间中最大的 $f(u_j)-s(u_j)$（其实也可反过来维护），并组合这两个值，对每次枚举得到的值取 max 就是答案

这种方式最后得出的答案是正确的。考虑答案路径，如下图：

![proof](https://cdn.luogu.com.cn/upload/image_hosting/uyflqcdn.png)

它一定会在我们遍历到图中标号 $A$ 的红色结点时被统计

但注意当我们枚举 $i$ 时，从单调队列取出的值不保证是对应断 $(u_{i-k}, u_{i-(k-1)})$ 边的树直径。做反例应该很简单，只要使这种方案的直径**不经过** $u_i$ 即可

（如果有什么奇奇怪怪的单调队列方法欢迎打脸qwq。不过这个问题（滑动窗口维护次大值）其实也有 $O(n)$ 做法，可以见这个 [讨论](https://www.luogu.com.cn/discuss/show/255658?page=1)。另外对于基环树，求每次断边的树直径，其实还有更简单的方法，具体可见开头那道题的题解区以及官方题解）

## CODE

代码里的单调队列部分并没有从 $u_{k-1}$ 开始统计答案；但因为缺省值都是 $0$，所以这样从单调队列取出的值都是偏小的（窗口大小还不足 $k-1$），不会影响最终答案

```cpp
#include <cstdio>
#include <iostream>
//#pragma GCC optimize("O3")
//#pragma GCC optimize("Ofast", "-funroll-loops", "-fdelete-null-pointer-checks")
//#pragma GCC target("ssse3", "sse3", "sse2", "sse", "avx2", "avx")
#define ll long long
using std::max;

const int MAXN =1e6+50;

/*------------------------------Map------------------------------*/

int n, m;
int first[MAXN], tote;
struct edge{
	int net, to, w;
}e[MAXN<<1];

inline void addedge(int u, int v, int w){
	++tote;
	e[tote].to =v, e[tote].w =w, e[tote].net =first[u];
	first[u] =tote;
	++tote;
	e[tote].to =u, e[tote].w =w, e[tote].net =first[v];
	first[v] =tote;
}

/*------------------------------Circle------------------------------*/

int circle[MAXN], lenc[MAXN]/*环长度*/, cntc;
int pre[MAXN], net[MAXN], evalpre[MAXN], evalnet[MAXN];
bool vis[MAXN], vis2[MAXN], color[MAXN];
int stk[MAXN], top;

int predfs(int u, int eid/*处理重边环 ( 两个结点的环 )*/){
	if((eid&1) == 0)
		--eid;
	else
		++eid;
	vis[u] =1;
	stk[top++] =u;
	for(int l =first[u]; l; l =e[l].net)
		if(l != eid){
			net[u] =e[l].to;
			evalnet[u] =e[l].w;
			if(vis[e[l].to])
				return e[l].to;
			else{
				int ret =predfs(e[l].to, l);
				if(ret != 0)
					return ret;
			}
		}
	--top;
	return 0;
}

/*标记这一整个连通子图*/
void markdfs(int u){
	vis2[u] =1;
	for(int l =first[u]; l; l =e[l].net)
		if(!vis2[e[l].to])
			markdfs(e[l].to);
}

void getCircle(){
	for(int i =1; i <= n; ++i){
		if(vis2[i])
			continue;
		top =0;
		int cir =predfs(i, 0);
		markdfs(cir);
		circle[cntc] =cir;
		lenc[cntc] =1;
		/*接环并给环染色*/
		pre[cir] =stk[top-1];
		evalpre[cir] =evalnet[stk[top-1]];
		color[cir] =1;
		while(stk[top-1] != cir){
			++lenc[cntc];
			pre[stk[top-1]] =stk[top-2];
			evalpre[stk[top-1]] =evalnet[stk[top-2]];
			color[stk[top-1]] =1;
			--top;
		}
		++cntc;
	}
}

/*------------------------------Dfs------------------------------*/

ll dp1[MAXN], dp2[MAXN];/*从 u 向子树走最大、次大的路径*/
ll Ans1;

void dfs1(int u, int fa){
	for(int l =first[u]; l; l =e[l].net)
		if(e[l].to != fa && !color[e[l].to]/*避免走环*/){
			dfs1(e[l].to, u);
			if(e[l].w+dp1[e[l].to] > dp1[u]){
				dp2[u] =dp1[u];
				dp1[u] =e[l].w+dp1[e[l].to];
			}
			else if(e[l].w+dp1[e[l].to] > dp2[u])
				dp2[u] =e[l].w+dp1[e[l].to];
		}
	Ans1 =max(Ans1, dp1[u]+dp2[u]);
}

/*------------------------------单调队列------------------------------*/

ll val[MAXN<<1];
int t[MAXN<<1]/*入队时间*/, head, tail, Len;

inline void push(ll va, int ti){
	while(tail > head && va >= val[tail-1])
		--tail;
	val[tail] =va;
	t[tail++] =ti;
	while(tail > head && ti-t[head] >= Len-1)
		++head;/*框选区间长度为 Len-1*/
}

/*------------------------------Main------------------------------*/

inline int read(){
	int x =0; char c =getchar();
	while(c < '0' || c > '9') c =getchar();
	while(c >= '0' && c <= '9') x = (x<<3) + (x<<1) + (48^c), c =getchar();
	return x;
}

int main(){
	n =read();
	for(int i =1; i <= n; ++i){
		int v =read(), w =read();
		addedge(i, v ,w);
	}
	getCircle();
	ll ans =0;
	for(int k =0; k < cntc; ++k){
		Ans1 =0;
		for(int u =circle[k], flg =0; u != circle[k] || flg == 0; u =net[u]){
			if(u == circle[k])
				flg =1;
			dfs1(u, 0);
		}
		head =tail =0, val[0] =0;
		Len =lenc[k];
		ll Ans2 =0, sum =-evalpre[circle[k]];
		/*走两圈，其实第一圈可以不统计答案，不过即使统计了也无妨，不是最优*/
		for(int u =circle[k], flg =0, i =0; u != circle[k] || flg < 2; u =net[u], ++i){
			if(u == circle[k])
				++flg;
			sum +=evalpre[u];
			Ans2 =max(Ans2, dp1[u]+sum+val[head]);
			push(dp1[u]-sum, i);
		}
		ans +=max(Ans1, Ans2);
	}
	printf("%lld", ans);
}
```

---

## 作者：huangzirui (赞：0)

题意：

给定一个由 $n$ 个点组成的森林，每个点都分别有一条通往其他点的边（其实是无向边），现在你需要求出每个连通块的直径之和。

$n \leq 10^6$

---
简单分析一下，其实就是在一个基环树森林上的每棵基环树上寻找直径长度。

现在考虑某一棵基环树怎么寻找直径。和树不同的一点是有一个环，貌似不太好搞。

这里不妨从环上入手，考虑一条经过两颗环连接的树和一段环上边的路径。那么假设目前选择的两颗树所在环的点为 $x,y$ ，定义 $dis_a$ 为 $a$ 点所在树的最长链，$len_{a,b}$ 为 $a,b$ 在环上的最长路径长度。那么这条路径长度就是 $dis_x+dis_y+len_{x,y}$ 。

这个形式很优美，我们就从这个式子下手。首先考虑把 $len$ 拆掉，因为涉及到一个最大值。那么我们先把链复制一遍再断开，设 $L_x$ 为点 $x$ 到断开点的长度，这样就可以直接令 $len_{x,y} = L_y-L_x$ 。

再把式子分成两块： $(dis_x-L_x)+(dis_y+L_y)$ ，于是只需要对每个点记录它的 $dis_x - L_x$ ，取最大值，然后对每个点记录答案即可。

那么这样做复杂度是 $O(n)$ 的，十分优秀。

回顾一下，破题点在于把复杂的计算 ($\max$) 分成简单的 (四则运算)，再把难以直接处理的式子尽量分成几块互不干扰的容易处理的小块，分别计算答案时就很简单了。

---

## 作者：Day4331Dream (赞：0)

# P4381 Island

~~可不要因为它是紫题就被吓住了嗷~~

~~这不就是几道绿题捏一块了么~~

**本题解不会细讲一些基础的模板类问题，建议有一定基础再看。**

## 题目大意
N个节点，N条边，**没有自环**。同时，根据题目描述可知，**每个**节点都有**一条**边连向另外一个节点，稍加思索可以得出，题目给出的图是**若干个基环树**。

因为题目的限定，**只要离开了这棵基环树，就不能再次进入它**。因为一棵基环树上的点全是连通的（~~废话~~），又因为所有**使用过的渡船**把所有**进入过的**基环树连通了，因此在**当前的基环树**上，一定有一种“桥和以前使用过的渡船的组合”（题目原句）可以回到**之前进入过的**基环树上，所以离开了一棵基环树，就不能再次进入它。

因此，我们好好珍惜进入一棵基环树的机会，~~尽可能榨干它~~。于是，它就是在基环树上求**最长路**的问题。

## Solution
考虑到每棵基环树的最长路求法都一样，我们可以将求最长路的模块封装起来，每次调用即可。

最长路有两种可能：
1. 在基环树上的**某一棵子树内**部
2. 某两棵子树的高度之和加上两个树根在环上**较长的**那段距离。

它们的解法：
1. 此时只需处理每一棵树内的最长路，找最大的那个。这是很基础的树形DP，对于一棵树中的每一棵子树，求它内部的**最长路**和到它树根的**最长链和次长链**，向上返回这两个值里**较大**的那个，过于简单，不细讲。
2. 树的高度就是**到树根的最长链**长度，很好求，不展开说明。求完树高之后，整个基环树真正有效的信息就是**一个环**。我们需要找到$height[i]+height[j]+distance(i,j)$的最大值，其中$height$是树高，$distance(i,j)$表示环上节点$i~j$的较长的那条路的长度。当我们预处理完环上的节点与树高和距离的**前缀和**之后，就可以进行**环形DP**。

环形DP是求出答案的核心步骤：

- 将环上的节点展开形成链，**复制一遍接在末尾**来避免枚举断点。
- 现在得到了一条由**树的高度值**组成的节点数为**环的二倍**的链。对于每一个点$i$，求出$min\{\ dis[i-1]-dis[j-1]+height[i]+height[j]\ \},max(0,i-n)<j<i$，其中$dis$是环上距离的前缀和，$n$是环上节点数。
- 枚举肯定会炸，考虑用**单调队列**维护。根据上面的方程，对于每个决策$j$，我们可以维护$height[j]-dis[j-1]$，这样就能$O(n)$求解。

代码实现的时候注意细节，此题会爆`int`，上面所有的步骤都不要漏（~~我就是写着写着忘了第一种情况，第一遍只拿了85分~~）。建议分成多个模块处理。

贴一下代码吧，~~时间限制太宽松了~~。

```cpp
#include<bits/stdc++.h>
#define Long long long
using namespace std;
class Node{
public:
	struct Edge{
		Node*a,*b;
		Long dis;
		Edge(Node*a,Node*b,Long dis){
			this->a=a; this->b=b;
			this->dis=dis;
		}
		inline Node* operator[](Node*e){
			return e==a?b:a;
		}
	};
	Long height,sec,res;
	bool traversable,top;
	list<Edge*> nei;
	Node(){
		traversable=true; res=0;
		height=0; sec=0; top=false;
	}
	inline void connect(Node*e,Long dis){
		Edge*tmp=new Edge(e,this,dis);
		this->nei.push_back(tmp);
		e->nei.push_back(tmp);
	}
    //找环
	bool find(Edge*pre,vector<Node*>&ring,vector<Long>&dis){
		if(!traversable){
			ring.push_back(this);
			dis.push_back(pre->dis);
			return top=true;
		}
		traversable=false;
		Node*tmp;
		for(auto e:nei){
			tmp=(*e)[this];
			if(e==pre) continue;
			if(tmp->find(e,ring,dis)){
				if(*ring.begin()==this) return false;
				ring.push_back(this);
				dis.push_back(pre->dis);
				return top=true;
			}
			if(!ring.empty()) return false;
		}
		return false;
	}
    //计算树高和树内的最长路
	void initAsTree(Edge*pre){
		Node*tmp;
		traversable=false;
		for(auto e:nei){
			tmp=(*e)[this];
			if(tmp->top||e==pre) continue;
			tmp->initAsTree(e);
			if(height<e->dis+tmp->height){
				sec=height;
				height=e->dis+tmp->height;
			}else{
				sec=max(sec,e->dis+tmp->height);
			}
			res=max(res,tmp->res);
		}
		res=max(height+sec,res);
	}
};
Node**p;
Long*seq,*dis;
//环形DP
Long solve(vector<Node*>&r,vector<Long>&d){
	Long n=r.size(),res=0;
	for(int i=0;i<n;i++){
		seq[i]=seq[i+n]=r[i]->height;
		dis[i]=dis[i+n]=d[i];
		res=max(res,r[i]->res);
	}
	for(int i=1;i<(n<<1);i++) dis[i]+=dis[i-1];
	deque<int> q; q.push_back(0);
	for(int i=1;i<(n<<1);i++){
		while(!q.empty()&&i-q.front()>=n) q.pop_front();
		res=max(res,seq[q.front()]+seq[i]+dis[i-1]-dis[q.front()-1]);
		while(!q.empty()&&seq[i]-dis[i-1]>=
			  seq[q.back()]-dis[q.back()-1]) q.pop_back();
		q.push_back(i);
	}
	return res;
}
int main(){
	int n; scanf("%d",&n);
	p=new Node*[n+1];
	for(int i=0;i<=n;i++) p[i]=new Node();
	for(int i=1,e,dis;i<=n;i++){
		scanf("%d%d",&e,&dis);
		p[i]->connect(p[e],dis);
	}
	
	seq=new Long[n<<1];
	dis=new Long[(n<<1)+1]; *(dis++)=0;
	
	Long res=0;
    //处理每个基环树
	for(int i=1;i<=n;i++){
		if(!p[i]->traversable) continue;
		vector<Node*> ring; vector<Long> dis;
		p[i]->find(NULL,ring,dis);
		for(auto e:ring) e->initAsTree(NULL);
		res+=solve(ring,dis);
	}
	printf("%lld",res);
	return 0;
}
```

如有错误，欢迎指出！

---

