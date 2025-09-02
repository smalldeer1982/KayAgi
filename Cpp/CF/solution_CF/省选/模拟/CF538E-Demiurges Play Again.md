# Demiurges Play Again

## 题目描述

Demiurges Shambambukli and Mazukta love to watch the games of ordinary people. Today, they noticed two men who play the following game.

There is a rooted tree on $ n $ nodes, $ m $ of which are leaves (a leaf is a nodes that does not have any children), edges of the tree are directed from parent to children. In the leaves of the tree integers from 1 to $ m $ are placed in such a way that each number appears exactly in one leaf.

Initially, the root of the tree contains a piece. Two players move this piece in turns, during a move a player moves the piece from its current nodes to one of its children; if the player can not make a move, the game ends immediately. The result of the game is the number placed in the leaf where a piece has completed its movement. The player who makes the first move tries to maximize the result of the game and the second player, on the contrary, tries to minimize the result. We can assume that both players move optimally well.

Demiurges are omnipotent, so before the game they can arbitrarily rearrange the numbers placed in the leaves. Shambambukli wants to rearrange numbers so that the result of the game when both players play optimally well is as large as possible, and Mazukta wants the result to be as small as possible. What will be the outcome of the game, if the numbers are rearranged by Shambambukli, and what will it be if the numbers are rearranged by Mazukta? Of course, the Demiurges choose the best possible option of arranging numbers.

## 说明/提示

Consider the first sample. The tree contains three leaves: 3, 4 and 5. If we put the maximum number 3 at node 3, then the first player moves there and the result will be 3. On the other hand, it is easy to see that for any rearrangement the first player can guarantee the result of at least 2.

In the second sample no matter what the arragment is the first player can go along the path that ends with a leaf with number 3.

## 样例 #1

### 输入

```
5
1 2
1 3
2 4
2 5
```

### 输出

```
3 2
```

## 样例 #2

### 输入

```
6
1 2
1 3
3 4
1 5
5 6
```

### 输出

```
3 3
```

# 题解

## 作者：老莽莽穿一切 (赞：8)

[更好的阅读体验](https://www.cnblogs.com/LaoMang-no-blog/p/16278300.html)

---

[**你谷 link**](https://www.luogu.com.cn/problem/CF538E)

[**CF link**](https://codeforces.com/problemset/problem/538/E)

首先将题目转化分别由自己和对面两个人布置叶子权值，求最大的叶子的权值，方便之后的解决。

考虑本题的计算是从叶子向上的，所以应该是自下而上的树形 dp，考虑设 $dp_{x,0/1}$ 表示以 $x$ 为根的子树，先手是不是想大的人，最大能走到的子树内的叶子是子树内第几大的。

如果是先手，则下一步自己就是后手，则应该取下一步后手能走到的子树内最小的，布置的时候就应该把最大的权值全都布置在这个子树里，若这一步是后手，则因为对面还会走到最小的，所以要给每一个儿子均匀分配，所以状态转移方程就是：

$$
\begin{aligned}
f_{x,1}=\min_{y\in\operatorname{son}(x)}\{f_{y,0}\}\\
f_{x,0}=\sum_{y\in\operatorname{son}(x)}f_{y,1}
\end{aligned}
$$

[代码](https://codeforces.com/contest/538/submission/157132426)非常简洁。

---

## 作者：Rem_CandleFire (赞：3)

### 题目大意

两个人（不妨称为 A 和 B）在一棵有 $n$ 个节点的有根树上玩游戏。游戏开始时根节点 $1$ 处有一颗棋子，A 和 B 轮流移动这颗旗子从某个节点至它的子节点，不能移动（即棋子到达叶子结点）时游戏结束。

每个叶子结点都有一个正整数 $v\in[1,m]$ 表示权值且不重复，一场游戏的得分即为棋子所在的叶子结点的权值，其中 $m$ 为叶子结点数。先手需要让得分最大，后手需要让得分最小。我们可以认为两个人都是绝对聪明的。

现在，在游戏之前你可以为所有叶子结点重新安排权值。请问，进行某种安排后，A 和 B 可以得到的游戏最大得分是多少？进行某种安排后，游戏的最小得分是多少？请分别输出并以一个空格隔开。

### 分析与做法

以上题意是根据英文原文得到的，个人认为清晰多了。

注意到本题的权值事实上是 $1$ 至 $m$ 的一个排列，且是从叶子结点开始至下而上推到根节点。于是考虑直接树形 dp。（也可以根据单调性通过二分转化为判定性问题）

我们设 $f_{u,0/1}$ 表示以 $u$ 为根节点的树内，想要取到 $\max/\min$ 的人，能取到的是该子树内第 $f_{u,0/1}$ 大的数。

首先考虑 $f_{u,0}$，若他走出这一步，下一步就是对方来走，所以这一步肯定是由 $f_{v,1}$ 转移过来的。因为我们表示的是第几大，所以对所有的儿子取 $\min$。即：

$$f_{u,0}=\min_{v\in son(u)}{f_{v,1}}$$

其次考虑 $f_{u,1}$，其下一步由对方取最大值，而无论怎么放权值，对方都有可能不选择某子树。所以问题可以看作我们需要放多少个数进入叶子结点才可以让此时的玩家保证能够取到数。而能取到的最小值就是这些数的最后一个。因为是子树内的第几大，所以可以直接求和。即：

$$f_{u,1}=\sum_{v\in son(u)}{f_{v,0}}$$

当 $u$ 为叶子结点时，初始化 $f_{u,0}=f_{u,1}=1$ 即可。

答案为 $m-f_{1,0}+1$ 和 $f_{1,1}$，理解了前面的东西这个就不用多说了吧，从状态出发。

代码很简单，一遍树形 DP 即可，时间复杂度 $O(n)$。

---

## 作者：皓月星辉 (赞：2)

## 题意
$n \le 2 \times 10^5$ 的一棵树，两个人轮流玩树上向下走一步，一个人先手，先手最大化收益，后手最小化收益，收益为最终到的叶子的权值，问当先手分配叶子权值（为一个排列）最大化收益为多少，后手最小化收益为多少。
## 分析
注意到相对大小与单调性，我们尝试二分验证 $mid$ 是否是对于先手而言可以分配取到的收益。

此时我们把过程描述为，至少需要放多少个 $1$ 在叶子，才能使得这个子树向下走可以必定走到一个 $1$ 的叶子。
## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
#define dd double
using namespace std;
char gc()
{
	static char buf[1<<16],*s,*t;
	if(s==t)
	{
		t=(s=buf)+fread(buf,1,1<<16,stdin);
		if(s==t)return EOF;
	}
	return *s++;
}
ll read()
{
	char c;
	ll w=1;
	while((c=getchar())>'9'||c<'0')if(c=='-')w=-1;
	ll ans=c-'0';
	while((c=getchar())>='0'&&c<='9')ans=(ans<<1)+(ans<<3)+c-'0';
	return ans*w;
}
void pc(char c,int op)
{
	static char buf[1<<16],*s=buf,*t=buf+(1<<16);
	(op||((*s++=c)&&s==t))&&(fwrite(buf,1,s-buf,stdout),s=buf);
}
void wt(int x)
{
	if(x>9)wt(x/10);
	pc('0'+x%10,0);
}
void wts(int x,char op)
{
	if(x<0)
	{
		pc('-',0);
		x=-x;
	}
	wt(x);
	pc(op,0);
}
const int xx=2e5+5;
struct node
{
	int next,to;
}e[xx<<1];
int cnt,h[xx];
void add(int x,int y)
{
	cnt++;
	e[cnt].next=h[x];
	h[x]=cnt;
	e[cnt].to=y;
}
int n,num,cr[xx];
void gnum(int x,int y)
{
	int vs=1;
	for(int i=h[x];i;i=e[i].next)
	{
		if(e[i].to==y)continue;
		gnum(e[i].to,x);
		vs=0;
	}
	num+=vs;
	cr[x]=vs;
}
int f[xx];
void dp(int x,int y,int dep)
{
	if(cr[x])return f[x]=1,void();
	int mn=1e9,sum=0;
	for(int i=h[x];i;i=e[i].next)
	{
		if(e[i].to==y)continue;
		dp(e[i].to,x,dep^1);
		sum+=f[e[i].to];
		mn=min(mn,f[e[i].to]);
	}
	if(dep&1)f[x]=mn;
	else f[x]=sum;
}
bool check1(int mid)
{
	dp(1,0,1);
	return f[1]<=n-mid+1;
}
bool check2(int mid)
{
	dp(1,0,0);
	return f[1]<=mid;
}
signed main(){
	n=read();
	for(int i=1;i<n;i++)
	{
		int a=read(),b=read();
		add(a,b),add(b,a);
	}
	gnum(1,0);
	dp(1,0,1);
	cout<<num+1-f[1]<<" ";
	dp(1,0,0);
	cout<<f[1]<<endl;
	pc('1',1);
	return 0;
}
```

---

## 作者：Zhl2010 (赞：1)

## 题目理解
在树上玩一个游戏，先手在树叶上分配权值，`A` 想要取得最大的数，`B` 想要取得最小的数，每次轮到自己时可以移动到当前点的任意一个子树。

~~不用说，这两人都是绝顶聪明~~。

如果还是不理解题目，可以自己玩一遍这个游戏。

## 思路
设 $f_{i,0}$ 表示假如先手是想取最大值的人，这个点的值。

设 $f_{i,0}$ 表示假如先手是想取最小值的人，这个点的值。

如果自己想取最大数，就要取下一步的子树中最小节点最大的情况，表达式：
$$f{i,1}=\min_{j \in son(i)}(f_{j,0})$$

如果自己想取最小数，就要取下一步的子树中最大节点最小的情况，表达式：
$$f{i,0}=\sum_{j \in son(i)}f_{j,1}$$

最后答案就是根节点，也就是 $m-f_{1,1}+1$ 和 $f_{1,0}$（$m$ 是叶子结点的个数）。

## 代码+注释
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,f[200010][2];
vector<int>e[200010];//存每条边 
int dfs(int x,int fa){//深搜遍历每个点 
	if(e[x].size()==(fa>0)){//到了叶子结点 
		m+=1;
		f[x][0]=f[x][1]=1;
		return 1;
	} 
	f[x][0]=0;
	f[x][1]=INT_MAX;
	for(int i=0;i<e[x].size();i++){
		int t=e[x][i];
		if (t==fa)continue;//自己不能再向父节点遍历了 
		dfs(t,x);
		f[x][1]=min(f[x][1],f[t][0]);//下一步的子树中最小节点最大的情况
		f[x][0]+=f[t][1];//取下一步的子树中最大节点最小的情况
	}
}
int main(){
	cin>>n;
	for (int i=1;i<n;++i){
		int x,y;
		scanf("%d%d",&x,&y);
		e[x].push_back(y);//存边 
		e[y].push_back(x);
	}
	dfs(1,0);
	cout<<m-f[1][1]+1<<' '<<f[1][0];
	return 0;
}
```

---

## 作者：Vocalise (赞：1)

若给定所有权值，那么问题就是一个简单的 DP:

$$
\begin{aligned}
f_v = \begin{cases}
\max(f_u), \text{if A operates.} \\
\min(f_u), \text{if B operates.} \\
w_v, \text{if }v \text{\ is a leaf.}
\end{cases}
\end{aligned}
$$

那么问题就是给定一个 $\min,\max$ 相互嵌套的式子，求排列使值最大或最小。先求最大值。

尝试二分。 把点集分为 $0/1$，然后子树 DP：但这样仍然要做背包，复杂度 $\mathcal O(n^2\log n)$。

反过来考虑，令 $g_v$ 在 $u$ 子树中 $f_v$ 能取得 $1$，子树中至少需要有的 $1$ 个数。显然是具有单调性的。

对于 $\max(f_u)$ 的情形，只需要至少一个 $1$ 即可，取最小的 $g_u$。

对于 $\min(f_u)$ 的情形，必须全是 $1$，将 $g_u$ 相加。

发现 $n - g_1 + 1$ 就是答案。最小值同理了。

时空复杂度 $\mathcal O(n)$。

---

