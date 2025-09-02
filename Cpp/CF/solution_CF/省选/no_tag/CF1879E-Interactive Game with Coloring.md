# Interactive Game with Coloring

## 题目描述

**这是一个交互题。** 

给你一棵有 $n$ 个顶点的树；顶点 $1$ 是树的根。对于每一个 $i \in [2, n]$，$i$ 的父顶点是 $p_i$（满足 $p_i<i$）。

您必须使用**尽可能少的颜色**来为树的所有边着色，这样您才能在这棵树上赢得游戏（每条边都应恰好涂上一种颜色）。

游戏内容是**在你给出染色方案之后**，交互库会钦定一个点 $x$，但并不会告诉你 $x$ 的值。

设你给出的染色方案用了 $k$ 种颜色。

交互库会告诉你对于 $i\in[1,k]$ 的每个颜色 $i$，与点 $x$ 相连的颜色为 $i$ 的边的数量。

然后你要给出选择的颜色 $w$，交互库将钦定任意一条与 $x$ 相连的颜色为 $w$ 的边并从 $x$ 走到这条边的另一个端点。

假设 $x$ 点到根节点的距离为 $d$，你需要在 $d$ 步之内走到根节点，不然你就输了。

**这个问题的交互库是自适应的**。这意味着起始顶点和当前顶点都**不固定**，可能会根据程序的输出而发生变化。

换句话说，**顶点可能变化，但一定符合先前给出的所有交互信息**。

**输出之后记得刷新缓存区！**

## 说明/提示

在第一个示例中，从 $2$ 到 $n$ 的每个顶点都与根相连。因此，我们可以将所有边涂成相同的颜色 $1$ ，当游戏开始时，只有一条边与当前顶点相连（它将通向根）。

在第二个示例中，树是一条由 $4$ 个顶点组成的路径。我们必须把它的边涂成不同的颜色，因为我们可以证明只有两种颜色的策略是无法取胜的。

## 样例 #1

### 输入

```
5
1 1 1 1
0
1
1```

### 输出

```
1
1 1 1 1
1```

## 样例 #2

### 输入

```
4
1 2 3
0
0 1 0
0
1 1 0
0
1 0 1
1```

### 输出

```
3
3 1 2
2
1
3```

## 样例 #3

### 输入

```
3
1 2
0
1 1
1```

### 输出

```
2
1 2
1```

# 题解

## 作者：_HCl_ (赞：9)

小蒟蒻觉得这道题非常的有意思，所以写一篇题解复盘一下思路。

因此这篇题解不会使用传统的“题解”格式，而是会更接近“解题报告”。

# CF1879E 题解

**题意简述**

给定一棵 $n$ 个节点的有根树，你需要对树的每条边进行染色。你要和交互库在这棵树上玩这样一个游戏：

交互库选择一个起点，放置棋子。

交互库不告诉你棋子的位置，但会告诉你和棋子所连的边的颜色情况（每种颜色的边有几条）。

你需要告诉交互库一种颜色，交互库会沿着这条颜色的边移动。如果这种颜色的边数大于 $1$，则由交互库来选择。

如果棋子向叶向走，那么交互库胜。走到根节点则你胜。

求出在保证获胜的情况下，最少需要染几种颜色。给出染色方案，并与交互库玩这个游戏。

**思路引导**

> 在本文中:
> 
> 节点从 $1$ 起标，且 $1$ 是根节点；
> 
> 节点层数从 $0$ 起标，根节点是第 $0$ 层；
>
> 边的层数定义为，其沿叶向连到的节点层数。

我们先来考虑怎么来染色。

首先，容易注意到，对于每一个节点，根向的边不能与叶向的边颜色相同。否则，你意图选择根向的边，但交互库可以选择颜色相同的叶向边走。

那么我们就可以把根向染成一种颜色，把叶向全部染成相同的另一种颜色。于是，我们就有了第一版思路：对于奇数层边，全部染成红色，对于偶数层边，全部染成蓝色。如图所示

![](https://cdn.luogu.com.cn/upload/image_hosting/lago9g3k.png)

这样对于每一个节点，我们选择只有一条边的颜色，就可以一直沿着根向走。

但我们也很快可以发现问题。如果一个节点只有一个儿子，也就是叶向边和根向边都只有一条（如下图实心点），那么我们选哪一条呢？

![](https://cdn.luogu.com.cn/upload/image_hosting/fw2jplv9.png)

发现两种颜色是不够的。（虽然这个图用两种颜色染是可行的，但我们先沿着目前的策略，这个之后再讨论）

我们考虑用同样的思路，使用三种颜色进行染色。也就是同一层的边用一种颜色染，相邻层的边“红蓝绿”循环染，如下图所示。

![](https://cdn.luogu.com.cn/upload/image_hosting/nhglznqt.png)

这样，我们的策略就是：如果节点连的边是红蓝，那么选红；如果连的边是蓝绿，那么选蓝；如果连的边是红绿，那么选绿。可以证明这样的染色方案和策略是一定可行的。

也就是说，用 $3$ 种颜色是一定可行的，但有可能不是颜色种类最少的。

那哪些情况用两种颜色就可以染好呢？

> 我们将“只有 $1$ 个儿子的节点”称为“单子节点”。

如果树中不存在“单子节点”，那么用两种颜色就可以染好。

如果所有的“单子节点”深度的奇偶相同，也可以用两种颜色染好。游戏时我们规定，对于单子节点，我们沿着红色/蓝色走即可。如下图所示。

![](https://cdn.luogu.com.cn/upload/image_hosting/042o29qx.png)

比如上图我们就规定单子节点沿红色边走。

其实再仔细想想，所谓“层数奇偶相同”的本质其实是，根向边的颜色相同。也就是对于一个图，如果我们有办法能让所有单子节点根向边的颜色相同，就可以用 $2$ 种颜色完成染色。

所以我们接下来考虑，对于层数奇偶性不同的单子节点，怎么处理让它们根向边的颜色相同。

再回顾一下我们一开始的想法，之所以让同一层的边颜色相同，是为了让根向边不要和叶向边撞色。然而根节点没有根向边，所以我们可以让根节点连接的第 $1$ 层边颜色不同。

> 我们将 $1$ 的所有儿子为根的子树称为“大子树”

然后我们就会发现，奇偶性不同的单子节点，它们的根向边就可以相同了。对于奇数层的单子节点，我们正常处理；对于偶数层的单子节点，我们找到其所在的“大子树”的根，翻转子树根的根向边，那么子树里所有的边都会发生翻转。这样偶数层单子节点的根向边就和奇数层单子节点根向边颜色相同了。如下图所示。

![](https://cdn.luogu.com.cn/upload/image_hosting/elbwacmp.png)

当然，如果一棵大子树中有奇偶不同的单子点，就会导致颜色翻转时发生矛盾，这样的情况就无法用两种颜色完成染色，必须要用三种。

所以我们在实现时，先判断是否会产生矛盾，如果不会，就用两种颜色染，如果会，就用三种颜色染。

还有一些需要特判情况：

- 只有两层的树，只用 $1$ 种颜色。
- 只有三层的树，只用 $2$ 种颜色。

然后这道题的构造部分就做完了。下面的交互部分就会简单很多。

首先，我们记录每种颜色的边数是否为 $1$。我们把“是 $1$”记成 $1$，“不是 $1$”记成 $0$，然后就可以列出一个类似“真值表”的东西。

| 红 | 蓝 | 绿 | 选择 |
| ----------- | ----------- | ----------- | ----------- |
| 1 | 1 | 0 | 红 |
| 0 | 1 | 1 | 蓝 |
| 1 | 0 | 1 | 绿 |
| 1 | 0 | 0 | 红 |
| 0 | 1 | 0 | 蓝 |
| 0 | 0 | 1 | 绿 |

然后根据真值表选择颜色即可。

**代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,DEP,K,rt[10001],dep[10001],col[10001];
vector<int> son[1001];
void dfs(int x,int fa){
	rt[x]=fa;//rt 记录所在大子树的根节点 
	DEP=max(DEP,dep[x]);//记录数的高度 
	for(auto y:son[x]){
		dep[y]=dep[x]+1;
		dfs(y,fa);
	}
}
bool check(){
	if(DEP==1)return 0;//只有两层for循环进不去 
	for(int i=2;i<=n;++i)
		if(son[i].size()==1){//单子节点 
			if((~col[rt[i]])&&col[rt[i]]!=(dep[i]&1))return 0;//矛盾了 
			col[rt[i]]=dep[i]&1;//根据层数奇偶性 
		}
	return 1;
}
void color_2(int x){//染两种颜色 
	if(col[x]==-1)col[x]=0;
	for(auto y:son[x]){
		if(x!=1)col[y]=col[x]^1;
		color_2(y);
	}
	if(col[x]==0)col[x]=2;
}
void color_3(int x){//染三种颜色 
	if(x!=1)col[x]=dep[x]%3;
	for(auto y:son[x])color_3(y);
}
int main(){
	cin>>n;
	for(int i=2;i<=n;++i){
		int par;
		scanf("%d",&par);
		son[par].push_back(i);
	}
	for(auto y:son[1])dep[y]=1,dfs(y,y);
	memset(col,0xff,sizeof(col));
	if(check()){
		K=2;
		cout<<"2\n";
		color_2(1);
	}
	else{
		K=min(3,DEP);//注意特判 
		cout<<K<<"\n";
		color_3(1);
	}
	for(int i=2;i<=n;++i)
		cout<<(col[i]+2)%3+1<<" ";
	cout<<endl;
	while(1){
		int sta,ec[4]={0,0,0,0}; 
		scanf("%d",&sta);
		if(sta==1||sta==-1)return 0;
		for(int i=1;i<=K;++i){
			int tmp;
			scanf("%d",&tmp);
			if(tmp==1)ec[i]=1;//标注为 1 
		}
		if(ec[1]&&!ec[3])cout<<"1";
		else if(ec[2])cout<<"2";
		else cout<<"3";
		cout<<endl;
	}
}
```


---

## 作者：樱雪喵 (赞：7)

被坑惨了。珍爱生命，远离构造。

## Description

这是一道交互题。

你在和交互库玩这样一个游戏。给你一棵 $n$ 个点，以 $1$ 为根的树，其中树上每条边都被染了某种颜色。交互库把一棵棋子放在了树上除根节点外的某个位置，并告诉你与这个点相连的所有边中每种颜色出现的次数。然后你要选择一种颜色的边，令交互库沿该颜色的方向移动棋子。若有多条边均是该颜色，则由交互库来选择一条。

设起点到根节点的距离为 $x$，若你用 $x$ 步把棋子移动到了根节点，则获胜。

现请你在保证能够获胜的前提下，用 **最小的颜色数** 对边染色，并给出方案。随后交互库与你进行上述游戏，你要对每一步给出应该选择的边直至获胜。

交互库自适应，$n\le 100$。

## Solution

发现题意本质是构造方案，使在任意位置给出每种颜色的边数，都能唯一确定通向根的那条边。

因为如果选择某种颜色的边，且这样的边不止一条，会由交互库来选择，所以通向根的边不能与其他边颜色相同。而连向儿子的边不属于同一棵子树，它们之间选什么颜色都互不影响。为了方便地判断根所在的边，我们希望连向儿子的颜色都相同。

那么设 $son_u$ 表示 $u$ 的儿子数，则对于 $son_u>1$ 的点判断是容易的：出现次数为 $1$ 的颜色只有一个，它就是通往父亲的边。也就是说，我们只需要考虑染色方案能否使 $son_u=1$ 的点判断出答案。令这类点叫作特殊点。

先不考虑该问题，我们只需要两种颜色，$dep_u\bmod 2=1$ 的点到父亲的边染颜色 $1$，其余染颜色 $2$。这里发现，若特殊点的深度奇偶性均相同，则会出现，对于所有特殊点，它们连向父亲的边都是同一个颜色，我们记录这个颜色是什么即可。

考虑奇偶性不同的情况，发现此时它们连向父亲的边不是同一个颜色，无法区分。这里考虑引入第三种颜色。从根节点向下依次染色，对于非特殊点，只需保证父亲的边和儿子的边不同色即可；对于特殊点，我们钦定：若连向父亲的边颜色为 $x$，连向儿子的边颜色就赋成 $x\bmod 3+1$。即，$1\to 2,2\to 3,3\to 1$。那么我们根据边的种类，即可判断它们的方向关系。

看起来很对？Wrong answer on test 4.

点 $1$ 不需要保证儿子都同色。所以如果奇偶性不同的两个特殊点不在一棵子树，可以把其中某棵子树的染色状态取反（$\text{swap}(1,2)$），而无需添加一种颜色。

完全没想到这点，鉴定为菜。

```cpp
const int N=105;
int n,fa[N];
vector<int> e[N];
int son[N],dep[N],mx;
void dfs(int u)
{
    dep[u]=dep[fa[u]]+1; mx=max(mx,dep[u]);
    for(auto v:e[u]) dfs(v);
}
int flag[2],col[N];
namespace sub3
{
    int x[N];
    void dfs(int u)
    {
        for(auto v:e[u])
        {
            if(son[u]==1) col[v]=((col[u]+1)>3)?1:col[u]+1;
            else {for(int j=1;j<=3;j++) if(j!=col[u]) {col[v]=j;break;}}
            dfs(v);
        }
    }
    void solve()
    {
        for(auto v:e[1]) col[v]=1;
        for(auto v:e[1]) dfs(v);
        cout<<3<<endl;for(int i=2;i<=n;i++) cout<<col[i]<<" ";cout<<endl;
        // assert(false);
        while("qwq")
        {
            int op=read();
            if(op==1) return;
            assert(op!=-1);
            static int cnt[5]; int sum=0;
            for(int i=1;i<=3;i++) cnt[i]=read(),sum+=cnt[i];
            if(sum==2)
            {
                if(cnt[1]&&cnt[3]) cout<<3<<endl;
                else if(cnt[1]) cout<<1<<endl;
                else cout<<2<<endl;
            }
            else for(int i=1;i<=3;i++) if(cnt[i]==1) {cout<<i<<endl;break;}
        }
    }
}
namespace sub2
{
    int x[N],ff;
    void dfs(int u)
    {
        for(auto v:e[u])
        {
            for(int j=1;j<=2;j++) if(j!=col[u]) {col[v]=j;break;}
            if(son[u]==1&&u!=1) ff=col[u];
            dfs(v);
        }
    }
    void solve()
    {
        for(auto v:e[1]) dfs(v);
        cout<<2<<endl;for(int i=2;i<=n;i++) cout<<col[i]<<" ";cout<<endl;
        while("qwq")
        {
            int op=read();
            if(op==1) return;
            assert(op!=-1);
            static int cnt[5]; int sum=0;
            for(int i=1;i<=2;i++) cnt[i]=read(),sum+=cnt[i];
            if(sum==2) cout<<ff<<endl;
            else for(int i=1;i<=2;i++) if(cnt[i]==1) {cout<<i<<endl;break;}
        }
    }
}
void check(int u)
{
    if(son[u]==1) flag[dep[u]%2]=1;
    for(auto v:e[u]) check(v);
}
int main()
{
    n=read();
    for(int i=2;i<=n;i++) fa[i]=read(),e[fa[i]].push_back(i),son[fa[i]]++;
    dfs(1);
    if(mx==2)
    {
        cout<<1<<endl;
        for(int i=2;i<=n;i++) cout<<1<<" ";
        cout<<endl;
        int op=read(); for(int i=1;i<=1;i++) int x=read();
        cout<<1<<endl,op=read(); return 0;
    }
    int qwq=0;
    for(auto v:e[1])
    {
        flag[0]=flag[1]=0;
        check(v);
        if(flag[0]&&flag[1]) {sub3::solve();return 0;}
        col[v]=flag[1]?2:1;
    }
    sub2::solve();
    return 0;
}
```

---

## 作者：huangrenheluogu (赞：1)

VP 时切了它，感觉好爽啊。

（我在 VP 的时候用了 $3$ 发罚时才通过本题，会导致我损失 $150$ 分）。

前言：感谢绘图软件 [csacademy](https://csacademy.com/app/graph_editor/)。

用 $col_i$ 表示 $i$ 和 $p_i$ 的颜色。

首先，一种构造是显然成立的，$col_i=dep_i$（这里的 $dep_i$ 指 $i$ 的深度，并且 $dep_1=0$）。

然后就无脑上交，`Wrong answer on test 4`，才发现需要颜色最少。

我们的染色需要满足什么条件？显然，对于任意一个节点，返回的值可以引导我们往根走。

颜色怎样最少呢？循环一下。比如，用 $1,2,3,1,2,3,1,2,3\dots,1,2,3$ 进行循环，那么如果这个点连出的边的颜色是 $(1,3)$，就往 $3$ 走；如果是 $(1,2)$，就往 $1$ 走；如果是 $(2,3)$，就往 $2$ 走。

看起来很对，不是吗？

比如这个样例：

```
9
1 1 2 2 3 3 4 4
```

图是这样的：

![](https://cdn.luogu.com.cn/upload/image_hosting/ap5jl5x7.png)

但是，我们却可以用两种颜色进行染色。

![](https://cdn.luogu.com.cn/upload/image_hosting/um1a8au5.png)

怎么判断？

容易想到，$2\sim n$ 中儿子个数不为 $1$，就可以用两种颜色然成功。对于一个节点，走到少的就行了。

那，如果有儿子数量为 $1$ 的一定不行吗？

比如上图中把 $9$ 号点去掉，上面的染色方案仍然可行。

那么，只有一个儿子的点（除 $1$ 外）的数量为 $1$ 的才可以用两种颜色？

不行。比如下面这张图（直接放染色结果了）。

![](https://cdn.luogu.com.cn/upload/image_hosting/x4xzpmev.png)

那么，需要这种“特殊点”（除 $1$ 以外只有 $1$ 个儿子的点）深度奇偶性相同？

还是不行。

![](https://cdn.luogu.com.cn/upload/image_hosting/dur06njm.png)

这里，$dep_{11}=3,dep_9=2$，但是仍然可行。

发现这张图和上面有所不同，$(1,2)$ 和 $(1,3)$ 染了不同的颜色。

因此，我们应该把一个儿子数为 $1$ 的特殊点放到它们 $dep=1$ 的祖先上，看看这个祖先和其父亲连边应该是 $1$ 还是 $2$。

因此，我们的 `check` 函数可以这么写。

```cpp
inline bool check(){//1 : k = 2; 2 : k != 2
	if(k == 1) return 0; // 这里的 k 是前面 dfs 中的 maxdep，如果不足 2，就分段考虑
	for(int i = 2; i <= n; i++){
		if(sz[i] == 1){
			if(col[faa[i]] != -1){//faa[i] 就是 1 的儿子，自己的祖先，这里对 faa[i] 不同分开判断
				if(col[faa[i]] ^ (dep[i] & 1)) return 0;
			}
			col[faa[i]] = dep[i] & 1;//这里钦定特殊点到父亲的边颜色为 1，目前是 0/1，后面改成 2/1
		}
	}
	return 1;
}
```

确定完每个 $faa_i$ 的颜色之后，我们重新染色即可。

好了，确定了这个东西是不是 $k=2$ 之后，就是交互部分了。

这个交互写起来就很简单了。

- $k=2$

如果只有 $1$ 种颜色是一条边，走那一种颜色；否则，这个点就是特殊点，走颜色为 $1$ 的那条边。

- $k=3$

简单的循环染色，用位运算记录即可。

[code](https://codeforces.com/contest/1879/submission/239579533)

---

## 作者：Leasier (赞：1)

折磨高妙的题。

------------

注意到若我们需要判断哪种颜色的边对应的是 $u$ 的父向边，则这种颜色在 $u$ 的出边中一定是**唯一**的。

于是一个简单的想法是对这棵树黑白染色，但问题在于若存在 $p, q$ 使得 $q$ 为 $p$ 的儿子、$p, q$ 都只有一个儿子且我们从 $q$ 出发，则我们将无法判断哪条边是 $q$ 的父向边。

于是另一个简单的想法是按照深度 $\bmod \ 3$ 来染色，于是所需颜色个数 $\leq 3$。现在我们只需要判断所需颜色个数是否可以为 $1/2$。

考虑把 $1$ 删掉，若剩下的连通块都是孤点，则我们只需要一种颜色。

现在我们只需要判断是否可以只用两种颜色，此时我们显然需要对每个连通块黑白染色。

若此时存在一个连通块内有前述 $p, q$ 这样的点，我们是否还可能可以黑白染色？

若只存在一对这样的点，我们不妨给 $q \to p$ 染上颜色 $1$，则我们碰到无法判断的情况选 $1$ 即可。

推而广之，若所有这样的 $q$ 的深度奇偶性相同，我们就强制给所有 $q \to p$ 染上颜色 $1$，然后就可以推出连通块内其他边的染色情况了。

~~然后这道题就做完了，十分好写！！！~~

代码：
```cpp
#include <stdio.h>
#include <stdbool.h>

int p[107], depth[107], e[7], son_cnt[107], bucket[107][7], color[107];

int main(){
	int n;
	bool flag = true;
	scanf("%d", &n);
	for (int i = 2; i <= n; i++){
		scanf("%d", &p[i]);
		depth[i] = depth[p[i]] + 1;
		flag &= depth[i] == 1;
	}
	if (flag){
		printf("1\n");
		for (int i = 2; i <= n; i++){
			printf("1 ");
		}
		printf("\n");
		fflush(stdout);
		while (true){
			int op;
			scanf("%d", &op);
			if (op == 1) break;
			scanf("%d", &e[1]);
			printf("1\n");
			fflush(stdout);
		}
		return 0;
	}
	for (int i = 2; i <= n; i++){
		son_cnt[p[i]]++;
	}
	for (int i = n; i >= 2; i--){
		if (son_cnt[i] == 1) bucket[i][depth[i] % 2]++;
		bucket[p[i]][0] += bucket[i][0];
		bucket[p[i]][1] += bucket[i][1];
	}
	flag = true;
	for (int i = 2; i <= n; i++){
		if (p[i] == 1){
			if (bucket[i][0] > 0 && bucket[i][1] > 0){
				flag = false;
				break;
			}
			if (bucket[i][0] > 0){
				color[i] = 1;
			} else {
				color[i] = 0;
			}
		} else {
			color[i] = color[p[i]] ^ 1;
		}
	}
	if (flag){
		printf("2\n");
		for (int i = 2; i <= n; i++){
			printf("%d ", color[i] + 1);
		}
		printf("\n");
		fflush(stdout);
		while (true){
			int op;
			scanf("%d", &op);
			if (op == 1) break;
			scanf("%d %d", &e[1], &e[2]);
			if (e[1] == 1){
				printf("1\n");
			} else {
				printf("2\n");
			}
			fflush(stdout);
		}
		return 0;
	}
	printf("3\n");
	for (int i = 2; i <= n; i++){
		printf("%d ", (depth[i] - 1) % 3 + 1);
	}
	printf("\n");
	fflush(stdout);
	while (true){
		int op;
		scanf("%d", &op);
		if (op == 1) break;
		scanf("%d %d %d", &e[1], &e[2], &e[3]);
		if (e[1] > 0 && e[2] > 0){
			printf("1\n");
		} else if (e[2] > 0 && e[3] > 0){
			printf("2\n");
		} else if (e[3] > 0 && e[1] > 0){
			printf("3\n");
		} else if (e[1] > 0){
			printf("1\n");
		} else if (e[2] > 0){
			printf("2\n");
		} else {
			printf("3\n");
		}
		fflush(stdout);
	}
	return 0;
}
```

---

## 作者：xiezheyuan (赞：0)

## 简要题意

**这是一道交互题**。

给定一个 $n$ 个点的树，根节点为 $1$，你需要给出一个 $k$，然后用 $k$ 种颜色给每条边染色。

接下来，交互库会选择一个非根的点 $u$，然后进行若干轮游戏。

每轮游戏交互库会先给出一个 $o$，若 $o=1$ 表示 $u=1$，游戏结束，否则会给出一个长度为 $k$ 的序列 $a$，表示一端点为 $u$ 的所有边中，颜色为 $i$ 的边数为 $a_i$。然后你需要输出一个颜色，然后交互库会选择一条为你给出的颜色的边，然后将 $u$ 设定为另一个端点。

你需要在最少的轮数结束游戏，同时要求 $k$ 最小。注意操作库是自适应的。

$1\leq n\leq 100$。

## 思路

令 $d_i$ 表示点 $i$ 的深度，$f_i$ 表示 $i$ 的父节点，$c_i$ 表示边 $(f_i,i)$ 的颜色。

### Part 1

首先注意到题意相当于给树边染色，使得 $(f_i,i)$ 的颜色与其他端点为 $i$ 的边不同（如果点 $i$ 度数为 $2$，我们还要要求可以确定 $(f_i,i)$ 的颜色）。

> 最优的 $k$ 最大值为 $3$。

证明：取 $c_i=d_i\bmod 3 + 1$，那么可以通过点 $i$ 哪些颜色存在边，简单分类讨论推出哪个点是父节点。

但是并不满足最优的 $k=3$，样例就给出了两组例子。不过好在现在只需要讨论 $k=1,2,3$ 三种情况了。

对于 $k=1$，是简单的，一定是菊花图，否则一定无法确定。最复杂的情况便是 $k=2$。

### Part 2

现在我们需要了解，为什么 $k$ 不总等于 $2$，这是因为树上会存在度数为 $2$ 的点 $i$，这个时候确定 $c_i$ 比较困难。因此，如果存在这样的 $i$，必须保证所有 $(f_i,i)$ 的颜色全部相同（要不然根据有限的信息无法推出来，如果推出来总能被交互库 hack）。

由于颜色是对称的，于是可以将所有度数为 $2$ 的点 $i$ 的 $c_i$ 钦定一种颜色，为了方便，不妨将颜色附着在深度较大的点上，跑一个类似二分图染色的过程即可。注意 $1$ 的出边颜色允许不同（要不然会 WA on #4）。

如果存在一组合法的方案，就可以用 $k=2$，否则就按照 $k=3$ 的方法跑即可。时间复杂度 $O(n)$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 105;
int n, fa[N], dep[N];
vector<int> g[N];
int col[N];

void dfs1(int u){
    for(int v : g[u]) dep[v] = dep[u] + 1, dfs1(v);
}

bool dfs2(int u, int color){
    if(col[u] && col[u] != color) return false;
    col[u] = color;
    for(int v : g[u]){
        if(!dfs2(v, 3 - color)) return false;
    }
    return true;
}

void clear(int u){
    if(g[u].size() != 1) col[u] = 0;
    for(int v : g[u]) clear(v);
}

signed main(){
    cin >> n;
    for(int i=2;i<=n;i++) cin >> fa[i], g[fa[i]].push_back(i);
    dfs1(1);
    for(int i=1;i<=n;i++){
        if(g[i].size() == 1) col[i] = 1;
    }
    bool flag = 1;
    for(int i : g[1]){
        if(!dfs2(i, 1)){
            clear(i);
            if(!dfs2(i, 2)){
                flag = 0;
                break;
            }
        }
    }
    if(count(fa + 2, fa + n + 1, 1) == n - 1){
        cout << "1" << endl;
        for(int i=2;i<=n;i++) cout << 1 << ' ';
        cout << endl;
        cout.flush();
        while(true){
            int op; cin >> op;
            assert(op != -1);
            if(op) break;
            int a; cin >> a;
            cout << 1 << endl;
            cout.flush();
        }
    }
    else if(flag){
        cout << "2" << endl;
        for(int i=2;i<=n;i++) cout << col[i] << ' ';
        cout << endl;
        cout.flush();
        while(true){
            int op; cin >> op;
            assert(op != -1);
            if(op) break;
            int a, b; cin >> a >> b;
            if(a == 1 && b != 1) cout << 1 << endl;
            else if(a != 1 && b == 1) cout << 2 << endl;
            else cout << 1 << endl;
            cout.flush();
        }
    }
    else{
        cout << "3" << endl;
        for(int i=2;i<=n;i++) cout << (dep[i] % 3 + 1) << ' ';
        cout << endl;
        cout.flush();
        while(true){
            int op; cin >> op;
            assert(op != -1);
            if(op) break;
            int a, b, c; cin >> a >> b >> c;
            if(!a && !b) cout << 3 << endl;
            else if(!b && !c) cout << 1 << endl;
            else if(!a && !c) cout << 2 << endl;
            else if(!a) cout << 2 << endl;
            else if(!b) cout << 3 << endl;
            else cout << 1 << endl;
            cout.flush();
        }
    }
    return 0;
}

// Written by xiezheyuan
```

---

## 作者：__Remake__ (赞：0)

神秘。

首先咱们知道：使得选手胜利的决策必然是每次都限制该点只能向父亲方向走，那么问题转化为了如何染色使得该点每轮只能向父亲方向走，即对于每个点，都能根据与其邻接的边中的每种颜色的边数来区分其走向父亲的边是什么颜色，且其向父亲的边的颜色与其他与其邻接的边的颜色均不同。

咱们令 $f_x$ 表示 $x$ 的父节点，$c_x$ 表示 $x$ 到 $f_x$ 这条边的颜色，$S_x$ 为 $x$ 的子节点集合，$d_{x, c}$ 表示与 $x$ 邻接的所有边中颜色为 $c$ 的边数，则 $d_{x, c_x} = 1$ 为有解的必要条件。

记 $H_x$ 表示与 $x$ 邻接的所有边的颜色集合，若咱们可以建立一个映射 $f : \{H_1, H_2, \cdots, H_n\} \rightarrow \cup_{i = 1}^n H_i$，使得 $f(H_x)$ 为 $x \rightarrow f_x$ 这条边的颜色，则可以构造解。

首先咱们注意到一个色数 $k = 3$ 的构造：令 $f(\{1, 2\}) = 1, f(\{2, 3\}) = 2, f(\{1, 3\}) = 3$，对于每个点 $x$，若 $x \rightarrow f_x$ 的颜色为 $1$，则令所有 $y \in S_x, y \rightarrow x$ 的边颜色为 $2$；若 $x \rightarrow f_x$ 的颜色为 $2$，则令所有 $y \in S_x, y \rightarrow x$ 的边颜色为 $3$；若 $x \rightarrow f_x$ 的颜色为 $3$，则令所有 $y \in S_x, y \rightarrow x$ 的边颜色为 $1$。

因此可知 $k \in \{1, 2, 3\}$，先考虑 $k = 1$ 的情况：此时树高 $\le 1$，因为否则则与 $d_{x, c_x} = 1$ 矛盾；接下来咱们考虑 $k = 2$ 的情况：因为 $k = 2$，故 $|H_x| \le 2$，又因 $d_{x, c_x} = 1$，因此对于所有 $c_x$ 存在的 $x$ 有 $\forall y_1, y_2 \in S_x, c_{y_1} = c_{y_2}$（树根的 $c_x$ 不存在，故不受该条件约束），此时咱们无法再构造映射 $f$ 了，因为绝大多数 $H_x = \{1, 2\}$，很容易构造 $f$ 不为映射的反例（比如：一个高 $\ge 3$ 的树），因此咱们只能考虑通过 $d_{x, c}$ 来判断 $[c = c_x]$。首先如果 $|S_x| \ge 2$，那么 $d_{x, c'} \ge 2 > 1 = d_{x, c_x}, c' \neq c_x$，此时一定能够确定 $[c = c_x]$ 的值；否则，若存在多个 $x$ 满足 $|S_x| = 1$，且她们的 $c$ 不均相等，则必然无解，反之，则可以钦定所有满足 $|S_x| = 1$ 的 $x$ 的 $c_x = p$，则可以有解，现在咱们只需要考虑什么情况下可以使得 $|S_x| = 1$ 的 $c_x$ 均相等。不失一般性地，咱们令 $p = 1$（因为将整棵树所有边的颜色 $1 \rightarrow 2$，$2 \rightarrow 1$ 后构造仍然合法）。

记 $h_x$ 表示 $x$ 的高度。若有点 $x$ 满足 $|S_x| = 1$，则其 $c_x = 1$，因此 $c_{f_x} = 2, c_{f_{f_x}} = 1, \cdots$。故若有 $x$ 和 $y$ 满足 $|S_x| = |S_y| = 1$ 且 $x \in \mathrm{Subtree}_y$，并且 $x$ 与 $y$ 均不为树根的同时有 $2 \perp h_x - h_y$，则在满足 $c_x = 1$ 的条件下必然有 $c_y = 2 \neq 1$，故此时不存在 $k = 2$ 的构造。反之，咱们钦定所有满足 $|S_x| = 1$ 的 $c_x = 1$ 后必然可以构造一组解，构造方法为：先给定一个初始解，这个解只需要满足 $k = 2$ 和 $d_{x, c_x} = 1$ 的条件，然后咱们逐步将这个解调整到一个合法解：假设 $|S_x| = 1$ 且在当前解中 $c_x \neq 1$，将 $\mathrm{Subtree}_{f_x}$ 内的所有边的颜色均翻转（$1 \rightarrow 2$，$2 \rightarrow 1$），并将 $f_x$ 到树根的链上的所有边的颜色翻转，得到新的解仍然合法，并且满足了 $c_x = 1$，不断调整至对所有 $|S_x| = 1$ 的 $c_x$ 均为 $1$ 即可，这样最终一定能调整到一组合法解而不会来回死循环，因为陷入死循环当且仅当存在两个 $x_1, x_2$，使得 $c_{x_1} = 1$ 与 $c_{x_2} = 1$ 矛盾，而这种情况已经被咱们排除了。

丑陋不堪的代码：

```cpp
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>

#define MAXN 105

using namespace std;

struct node {
    int to, col;
};

int n, nextcol[4], hgt, fcol[MAXN], k, hg[MAXN];
bool vis[2];
vector <node> T[MAXN];

void dfs0(int u, int h) {
    hgt = max(hgt, h);
    hg[u] = h;
    for(node nxt : T[u]) {
        int v = nxt.to;
        dfs0(v, h + 1);
    }
    return ;
}

void dfs(int u, int col) {
    for(node& nxt : T[u]) {
        int v = nxt.to;
        nxt.col = nextcol[col];
        dfs(v, nxt.col);
    }
    return ;
}

bool dfsb(int u, int col) {
    bool ret = false, rev = false;
    int sz = T[u].size();
    if(u == 1) {
        for(node& nxt : T[u]) {
            int v = nxt.to;
            nxt.col = nextcol[col];
            bool rt = dfsb(v, nxt.col);
            if(rt) nxt.col = nextcol[nxt.col];
        }
    }
    else if(sz > 1) {
        for(node& nxt : T[u]) {
            int v = nxt.to;
            nxt.col = nextcol[col];
            bool rt = dfsb(v, nxt.col);
            rev = rev || rt;
        }
        if(rev) {
            for(node& nxt : T[u]) {
                int v = nxt.to;
                nxt.col = nextcol[nxt.col];
                dfsb(v, nxt.col);
            }
            ret = true;
        }
    }
    else if(sz == 1) {
        node& nxt = T[u][0];
        nxt.col = 2;
        if(col == 2) ret = true;
        dfsb(nxt.to, 2);
    }
    return ret;
}

void dfsp(int u) {
    if(T[u].size() == 1) vis[hg[u] & 1] = true;
    for(node nxt : T[u]) dfsp(nxt.to);
    return ;
}

void output_col(int u) {
    for(node nxt : T[u]) {
        int v = nxt.to;
        fcol[v] = nxt.col;
        output_col(v);
    }
    return ;
}

void game() {
    int opt = 0;
    pair <int, int> st[4];
    scanf("%d", &opt);
    while(opt != 1 && opt != -1) {
        int ccnt = 0;
        for(int i = 1; i <= k; i++) {
            int rd = 0;
            scanf("%d", &rd);
            if(rd > 0) {
                ++ccnt;
                st[ccnt].first = i;
                st[ccnt].second = rd;
            }
        }
        if(ccnt == 1) printf("%d\n", st[1].first);
        else if(k == 2) {
            if(st[1].second > 1) printf("%d\n", st[2].first);
            else if(st[2].second > 1) printf("%d\n", st[1].first);
            else puts("1");
        }
        else {
            if(st[1].first == 1 && st[2].first == 2) puts("1");
            else if(st[1].first == 2 && st[2].first == 3) puts("2");
            else puts("3");
        }
        fflush(stdout);
        scanf("%d", &opt);
    }
    return ;
}

int main() {
    scanf("%d", &n);
    for(int i = 2; i <= n; i++) {
        int fa = 0;
        scanf("%d", &fa);
        T[fa].push_back((node){i, 0});
    }
    dfs0(1, 0);
    bool sym1 = false;
    for(node nxt : T[1]) {
        int u = nxt.to;
        vis[0] = vis[1] = false;
        dfsp(u);
        if(vis[0] && vis[1]) {
            sym1 = true;
            break;
        }
    }
    if(hgt == 1) {
        k = 1;
        puts("1");
        nextcol[1] = 1;
        dfs(1, 1);
        output_col(1);
        for(int i = 2; i <= n; i++) printf("%d ", fcol[i]);
        puts("");
    }
    else if(hgt <= 2) {
        k = 2;
        puts("2");
        nextcol[1] = 2, nextcol[2] = 1;
        dfs(1, 2);
        output_col(1);
        for(int i = 2; i <= n; i++) printf("%d ", fcol[i]);
        puts("");
    }
    else if(!sym1) {
        k = 2;
        puts("2");
        nextcol[1] = 2, nextcol[2] = 1;
        dfsb(1, 2);
        output_col(1);
        for(int i = 2; i <= n; i++) printf("%d ", fcol[i]);
        puts("");
    }
    else {
        k = 3;
        puts("3");
        nextcol[1] = 2, nextcol[2] = 3, nextcol[3] = 1;
        dfs(1, 3);
        output_col(1);
        for(int i = 2; i <= n; i++) printf("%d ", fcol[i]);
        puts("");
    }
    fflush(stdout);
    game();
    return 0;
}
```


---

## 作者：spdarkle (赞：0)

题意简述：

>给定一颗以 $1$ 为根的树，现在来玩一个游戏。这个游戏规则如下：
>
>首先，你需要将边染为 $k$ 种不同的颜色，然后有以下操作：
>
>我们提前选好一个点 $x$，现在你需要以最小的步数将 $x$ 移动到根节点。(你不会知道 $x$)。
>
>我们每一次会告诉你当前走到的点，连接它的所有边的每一种颜色的边的个数。
>
>求在确保在最坏情况下仍然能以最少步数移动到根的情况下，所使用颜色最少。

首先，一个直觉的想法是，每一条边按照儿子的 $dep$ 进行染色。这样我们只需要每一次找到给出的边的颜色最小值走就可以了。

那么进一步思考发现，我们必须要保证可以在最坏情况下每次仍然可以找到当前点的父亲节点。


这是染色方案合法的充要条件。

那么我们来思考一个普遍性的情况。

注意到一个性质：若对于每个点，连接父亲的边和连接儿子的边的颜色是不同的。则连接父亲的边的个数必定为一。这是另一个判定的条件。

首先对于叶子节点，也即有唯一边可以走的，我们当然走，然后考虑利用这个性质。

注意到，我们可以给边固定顺序，染色时按照 $1\rightarrow2\rightarrow 3\rightarrow 1$ 的顺序给每**层**边染色，接着我们每次就只会得到两种颜色的边。且知道这两种边的颜色，这会让我们直接判断出父亲节点的边。

如 $(1,2)$ 颜色存在，就走 $1$，若是 $(2,3)$，走 $2$，若是 $(1,3)$，走 $3$。

那么可以得到 $k\le 3$。

事实上，这样的**3的循环染色非常常见**。

现在考虑 $k=1,k=2$ 的两种情况。

$k=1$ 非常显然，这必然需要树的高仅为 $2$ 才可以办到。

$k=2$ 是烦恼的。

叶子节点不必多说，我们现在来考虑颜色1和颜色2的数量分别是 $(a,b)$ 的情况。我们现在是进行黑白染色。

首先，$a,b$ 之中必然至少有一个为一，若有且仅有一个，则走为一的边即可。

那么我们真正要处理的是 $(1,1)$。

这时候怎么判断？明显，我们得到这个输入，就必须指定走某个颜色。

而什么情况下当我们得到 $(1,1)$ 选择走 $1$ 都是正确的呢？（选择走 $2$ 由对称性可知等价。）

那么就必然有，这一类点连父亲的边全部都被染成了 $1$。

这一类点，本质上是 $|Son(u)|=1$ 的点的集合。

若想要这些点的都被染为一，则必然有这些点的深度的奇偶性相同。这样我们可以通过选择第一层的颜色确保这些边颜色全部为一。

真的是这样吗？注意到根节点 $1$ 的不同子树无关系，可以对于每一颗子树单独选择起始颜色。那么我们对每一个 $1$ 的子树跑一遍，判断是否合法即可。

[code](https://codeforces.com/contest/1879/submission/225085291)



---

## 作者：WRuperD (赞：0)

非常简单的构造题。

首先先考虑在一颗满 $n$ 叉树上怎么做。一个非常明显的事情是所有点到根节点的路径上，对于任意一个节点，指向父亲节点的那条边的颜色应当是当前节点与所有节点的连边中颜色唯一的那一条边。不然交互库就可以选择不走那一条边。所以考虑分层黑白染色。发现对于一个满 $n$ 叉树，这时候每一个节点会有 $k$ 条指向儿子的边和一条与他们异色的指向父亲的边。（忽略叶子，叶子是显然的。）但是如果 $k = 1$ 也就是一条链就完蛋了。因为每种颜色都出现了一次，所以无法判断哪一条边是指向父亲的边。所以就只能使用三种颜色。发现三种颜色分层间隔染后我们可以根据出现的是哪两种颜色判定该选哪一条边。

交上去发现在第四个点就挂了？为什么。题目要求最少颜色。发现根节点的所有出边可以随便染色。意味着即使这棵树中存在多个节点度数为 $2$，只要它们的指向父亲节点的边可以被调节成一致的，那我们还是可以只用两种颜色。

秒了。

```cpp
// Problem: Interactive Game with Coloring
// URL: https://www.luogu.com.cn/problem/CF1879E
// Written by WRuperD

#include<bits/stdc++.h>
using namespace std;
const long long inf = 1e18;
const int mininf = 1e9 + 7;
#define int long long
#define pb emplace_back
inline int read(){int x;cin>>x;return x;}
inline void write(int x){cout<<x;}
#define put() cout<<' '
#define endl cout<<endl

const int MAX = 1e2 + 10;
int w[MAX][MAX];
vector <int> g[MAX];
int deg[MAX];
int fa[MAX];

void dfs(int u, int col, int mod){
	for(int v : g[u]){
		w[u][v] = col;
		fa[v] = u;
		dfs(v, (col + 1) % mod, mod);
	}
}

int fla;
int num2[MAX];

int totfla;
int mk[MAX];

void check(int u, int facol){
	num2[0] = num2[1] = num2[2] = 0;
	num2[facol]++;
	
	for(int v : g[u]){
		num2[w[u][v] + 1]++;
	}
	int preflag = fla;
	if(num2[1] == 1 and num2[2] == 1 and u != 1){
		// write(u), put(), write(facol), endl;
		if(facol == 1){
			if(fla == -1 or fla == 2){
				fla = -1;
			}else	fla = 1;
		}else{
			if(fla == -1 or fla == 1){
				fla = -1;
			}else{
				fla = 2;
			}
		}
	}
	if(fla == -1)	totfla = -1;
	for(int v : g[u]){
		check(v, w[u][v] + 1);
		mk[u] += mk[v];
	}
	if(fla == -1)	totfla = -1;
	if(fla != -1 and fa[u] == 1){
		// write(fla), put(), write(totfla), endl;
		if(totfla){
			if(totfla != fla)	mk[u] = 1;
		}else{
			totfla = fla;
		}
		fla = 0;
	}
}

void rever(int u, int fl){
	if(u == 1){
		for(int v : g[u]){
			if(mk[v]){
				w[u][v] ^= 1;
				rever(v, 1);
			}
		}
		return ;
	}
	for(int v : g[u]){
		w[u][v] ^= fl;
	}
	for(int v : g[u]){
		rever(v, fl);
	}
}

void solve(){
	int n;
	cin>>n;
	for(int i = 2; i <= n; i++){
		fa[i] = read();
		g[fa[i]].pb(i);
		deg[fa[i]]++, deg[i]++;
	}
	dfs(1, 0, 2);
	check(1, 0);
	// write(fla), endl;
	if(totfla == -1){
		dfs(1, 0, 3);
	}else{
		rever(1, 1);
	}
	int num = 0;
	for(int i = 2; i <= n; i++)	num = max(num, w[fa[i]][i] + 1);
	write(num), endl;
	for(int i = 2; i <= n; i++){
		write(w[fa[i]][i] + 1), put();
	}
	endl;
	while(1){
		int x = read();
		if(x == 1 or x == -1)	return ;
		for(int i = 1; i <= num; i++){
			num2[i] = read();
		}
		bool fl = 0, fl2 = 0, fl3 = 0;
		if(num2[1] == 1)	fl = 1;
		if(num2[2] == 1)	fl2 = 1;
		if(num2[3] == 1)	fl3 = 1;
		int cnt = 0;
		cnt += fl, cnt += fl2, cnt += fl3;
		if(cnt == 1){
			if(fl) cout<<1,endl;
			if(fl2)	cout<<2,endl;
			if(fl3)	cout<<3,endl;	
		}else{
			if(fl and fl2 and fla != -1){
				cout<<totfla,endl;
			}
			else if(fl and fl2){
				cout<<1,endl;
			}else if(fl2 and fl3){
				cout<<2, endl;
			}else{
				cout<<3,endl;
			}
		}
	}
}

signed main(){
	int t = 1;
	while(t--)	solve();
	return 0;
}
```

---

