# Adam and Tree

## 题目描述

树指的是一种无向连通图且满足任意两个点间不存在两条不同的简单路径；

彩色树指的是一种每条边都有一种颜色的树，并且同一种颜色的边集一定形成一条路径。

对于彩色树上的任意一个点 $u$，定义其权值 $w(u)$ 为 $u$ 至根节点（即 1 号点）的路径上所有边的颜色种类数。

彩色树会生长，初始时树中仅有根节点 1 号点，每个时刻都会有一个新节点长出来。每个时刻（包括初始时刻），你需要决定每条边的颜色，在满足彩色树的定义的前提下，使这个时刻树中节点权值的最大值最小。

## 样例 #1

### 输入

```
11
1 1 1 3 4 4 7 3 7 6 6
```

### 输出

```
1 1 1 1 1 2 2 2 2 2 3 ```

# 题解

## 作者：幻影星坚强 (赞：13)

~~前一篇题解连复杂度都没说我还以为是暴力老哥。~~

首先一个点的到儿子的两条边颜色相同答案显然不会更优，原因是这两条边不会同时出现在某个节点到根的路径上。所以每个节点到其儿子的所有边颜色都不一样。

我们下文称一个节点的值为确定该节点的子树内及到其父亲的所有边的颜色后答案的最小值。

然后我们发现在一个点子树内的最优方案已经确定的情况下，这个点到其父亲这条边的颜色应当是它到其儿子中值最大的那一条边的颜色，原因是假如这两条边的颜色不同，那么这个点将会经过一条颜色不同的边，所以这个节点的值将是其儿子最大值加一，显然没有让这个儿子不加来得优。所以一个节点其它儿子都会经过一条颜色不同的边，我们直接拿出其儿子的次大值便能代表这些经过颜色不同的边。设一个节点的值为 $f$，其儿子 $f$ 的最大值为 $max_o$，其儿子 $f$ 的次大值为 $se_o$，我们便有：

$$f_o=\max(max_o,se_o+1)$$

然后对于每次加点都暴力转移的复杂度为 $O(n^2)$。

有个非常不像优化的优化，对于每次加点，我们发现只要更新它到根这条路径上的点，这样在链的情况依然是 $O(n^2)$ 的，但是我们发现每加一个 $f$ 值会发生修改的点只会是它到其某个祖先的这条路径。因为假如有某个值不会发生修改，那么这个点到其父亲的转移将和不加该点相同，所以不必继续，我们设 $ans_o$ 为所有点都加完后的 $f_o$，这样每个点只会被更新 $O(ans_o)$ 次，复杂度为 $O(\sum_{i=1}^{n} ans_i)$。这样看上去依然是 $O(n^2)$ 的，但是我们发现假如对这棵树进行重链剖分并按剖分后的结果进行染色，根据重链剖分的性质，每个点到根经过的重链条数是 $O(\log n)$ 的。于是 $ans_o$ 的级别也是 $O(\log n)$，这样复杂度便是 $O(n \log n)$。

值得注意的是根没有向上的边，所以根的 $f$ 值就是 $max$ 值。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 10;
int n;
int dp[N], maxs[N], se[N];
vector<int>v[N];
bool pushup(int to, int o)
{
	if(dp[to] > maxs[o])
	se[o] = maxs[o], maxs[o] = dp[to];
	else
	if(dp[to] > se[o])
	se[o] = dp[to];
	if(max(maxs[o], se[o] + 1) == dp[o])return 0;
	return 1;
}
int from[N];
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> n;
	dp[1] = 1;
	for (int i = 2; i <= n + 1; ++ i)
	{
		dp[i] = 1;
		int fa;
		cin >> fa;
		from[i] = fa;
		v[fa].push_back(i);
		fa = i;
		for (; pushup(fa, from[fa]) && from[fa]; fa = from[fa])
		dp[from[fa]] = max(maxs[from[fa]], se[from[fa]] + 1);
		cout << maxs[1] << " ";
	}
}
```


---

## 作者：Llx2022 (赞：9)

# **Adam and Tree**

## **题目描述**

Adam 有一棵彩色树，初始时只有根节点。每次往这棵树中加入一个节点，你需要对每条边染上一种颜色，使得树中每个节点到根节点的路径上边的颜色种类数最小。求每次添加节点后的最小颜色种类数。

**注意**：
- 给定的保证一定是一棵树。
- 染色时一定要保证同一种颜色必须形成一条路径，**这一点非常重要，是理解题意的重要内容**。

## **思路分析**

首先需要理解一下题意中的**边的颜色种类数最小**是什么意思。我们可以从样例中看到一个有用的信息：第 $6$ 个时刻添加节点后，根节点到节点 $11$ 的路径上颜色种类数为 $2$，而到节点 $12$ 的路径上颜色种类数为 $3$。由此可知，每次添加节点后最小颜色种类数的定义应该是：**从根节点到新添加的节点路径上颜色种类数的最大值**。

**那么我们如何去染色呢**？首先我们需要一个数据结构来维护每个节点到根节点路径上的颜色种类数。因为每次添加节点后只会影响到新节点到根节点的路径上的颜色种类数，所以我们可以**从新节点开始向上更新路径上所有节点的颜色种类数**,即用树链部分将复杂度降低到 $O(n \log n)$。具体来说，我们从新节点开始向上遍历每个节点的父亲，分别记录它们的儿子节点中**最大的权值 $v_1$** 和**次大的权值 $v_2$**，以及它们**将要更新（即临时记录）的儿子节点的最大权值 $s$**，然后计算出**当前节点的权值 $w$**：

$$w = \max(v_1, v_2 + 1)$$

其中 $v_1$,$v_2$ 是当前节点的父亲节点的儿子节点的最大权值和次大权值，而 $v_2 + 1$ 是因为当前节点和它的父亲节点之间的边的颜色种类数为 $1$。如果计算出来的 $w$ 大于当前节点将要更新的儿子节点的最大权值 $s$，那么我们就用 $w$ 更新 $s$，然后将 $s$ 作为当前节点的权值。**这里之所以用 $s$ 作为当前节点的权值，是因为当前节点的权值只与它的父亲节点有关，而 $s$ 正是父亲节点将要更新的儿子节点的最大权值。**
### **总结**


- 本题出发点就是对于每添加 $1$ 条边会对答案有怎样的贡献？
- 答案又是怎样处理出来的？
- 如何找到递推关系？

## 参考代码

```cpp
#include<iostream>
using namespace std;
template<typename T>inline void read(T &x){
	x=0;T f=1;char ch=getchar();
	while(ch<48||ch>57){if(ch=='-'){f=-1;}ch=getchar();}
	while(ch>=48&&ch<=57){x=x*10+ch-48;ch=getchar();}
	x*=f;
}
template<typename T>inline void write(T x) {
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+48);
}
const int N=1e6+10;
//first_val表示当前节点的儿子中最大权值，second_val表示当前节点的儿子中次大权值
//son_max表示当前节点将要更新（即临时记录）的儿子的最大权值
int n,father[N],son_max[N],first_val[N],second_val[N];
bool update(int x){
    //最大值更新
    if(first_val[father[x]]<son_max[x]){
        second_val[father[x]]=first_val[father[x]];
        first_val[father[x]]=son_max[x];
    }
    //次大值更新
    else if(second_val[father[x]]<son_max[x]){
        second_val[father[x]]=son_max[x];
    }
    int ans=max(first_val[father[x]],second_val[father[x]]+1);
    //若答案仍相同不更新
    if(son_max[father[x]]==ans) return 0;
    son_max[father[x]]=ans;
    return 1;
}
int main(){
    read(n);n++;son_max[1]=1;
    for(int i=2;i<=n;i++){
        read(father[i]);son_max[i]=1;
        for(int j=i;father[j];j=father[j]){if(!update(j)){break;}}
        write(first_val[1]);putchar(' ');
    }
    return 0;
}
```


---

## 作者：Meltryllis_ (赞：9)

//--------------------因为前几天同学提醒我在贴代码时少贴了一个return 1-------------------------// //--------------------所以重新交了一遍，希望能够通过，以免误导他人-------------------------------//



这个题是前天树形dp考试时的第一题，学长原本要给我们讲这个题目，结果发现某张姓巨佬切了这道题。。。所以这篇题解算是转述他的思路。
首先，可以想出一个dp，用dp i表示在含i的子树中最大权值，用mx1 i表示i子树中最大的权值，mx2 i表示i子树中次大的权值，可以发现，dp i=max(mx1 i,mx2 i+1)而不难发现，每一次加上一个节点影响的必定只是其到根节点的路径上的一条链，所以每次更新只要向上更新即可。
```cpp
bool update(int x,int y)
{
	if(mx2[y]>dp[x])
	return 0;
	if(mx1[y]<dp[x])
	{
		mx2[y]=mx1[y];
		mx1[y]=dp[x];
	}
	else if(mx2[y]<dp[x])
	{
		mx2[y]=dp[x];
	}
	int upd=max(mx1[y],mx2[y]+1);
	
	if(upd==dp[y])
	return 0;
    	return 1;
   ```

从复杂度上来看应该没有太大问题，不过还是应该在不能更新时直接退出，防止超时
```
for(j=i;fth[j]&&update(j,fth[j]);j=fth[j]);
```
最后的答案显然就是dp 1了，每次输出即可。
完整代码：
```
#include<cstdio>
#include<iostream>
#include<cmath>
#include<algorithm>
#define N 1000010
using namespace std;
int i,j,k,m,n,u,v;
int mx1[N]={},mx2[N]={};
int dp[N]={},fth[N]={};
void read(int &s)
{
	s=0;
	char ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9')
	{
		s=(s<<3)+(s<<1)+ch-'0';
		ch=getchar();
	}
}
bool update(int x,int y)
{
	if(mx2[y]>dp[x])
	return 0;
	if(mx1[y]<dp[x])
	{
		mx2[y]=mx1[y];
		mx1[y]=dp[x];
	}
	else if(mx2[y]<dp[x])
	{
		mx2[y]=dp[x];
	}
	int upd=max(mx1[y],mx2[y]+1);
	
	if(upd==dp[y])
	return 0;
	dp[y]=upd;
	return 1;
}
int main()
{
//	freopen("tree1.in","r",stdin);
//	freopen("tree.out","w",stdout);
	read(n);
	n++;
//	cout<<"0"<<'\n';
	dp[1]=1;
	for(i=2;i<=n;i++)
	{
		read(fth[i]);
		dp[i]=1;
		for(j=i;fth[j]&&update(j,fth[j]);j=fth[j]);
		cout<<mx1[1]<<'\n';
	}
	return 0;
}
```



---

## 作者：Gokix (赞：4)

[CF442D](https://www.luogu.com.cn/problem/CF442D)

状态有点难想但想出状态来就简单了的 DP 题。

------------

不难想到用 DP。

状态设 3 个：$dp_u$ 表示**非根**节点 $u$ 的权值；$fir_u$ 表示节点 $u$ 的所有儿子中权值最大的一个；$sec_u$ 表示节点 $u$ 的所有儿子中权值次大的一个。

转移显然。用儿子的 $dp_v$ 更新父亲 $u$ 的状态。先更新 $fir_u,sec_u$，然后 $dp_u=\max(fir_u,sec_u+1)$。

答案最后就是 $fir_{root}$。注意并不是 $dp_{root}$，因为根 $root$ 到自己是没边的，我们设定状态 $dp$ 的时候也没有算上根。

注意到每新拴上一个节点 $u$，不必改变整棵树的权值，只需改变从 $u$ 到根 $root$ 这条路径上的节点权值，显然不会更劣。

当向上更新时发现已经更新不了这个节点了，那就直接退出（更向上的节点也更新不了了）。

时间复杂度是 $\mathcal O(n \log n)$ 的。可以考虑重链剖分的结论来证明这点。

------------

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;

const long long N=1e6+10;
long long n,f[N],dp[N],fir[N],sec[N],ok;

inline long long read(){char ch=getchar();long long x=0,f=1;while(ch<'0' || ch>'9'){if(ch=='-') f=-1;ch=getchar();}while('0'<=ch && ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}
inline void write(long long x){if(x<0){putchar('-');x=-x;}if(x>9) write(x/10);putchar(x%10+'0');}//1e6的IO量得用更快的输入输出方式

bool upd(long long x){
    if(fir[f[x]]<dp[x]){
        sec[f[x]]=fir[f[x]];
        fir[f[x]]=dp[x];
    }
    else if(sec[f[x]]<dp[x]){
        sec[f[x]]=dp[x];
    }
    long long ans=max(fir[f[x]],sec[f[x]]+1);
    if(dp[f[x]]==ans) return 0;//不能更新就退出
    dp[f[x]]=ans;
    return 1;
}

int main(){
    long long i,j,u,v;
    n=read();n++;
    dp[1]=1;
    for(i=2;i<=n;i++){
        f[i]=read();
        dp[i]=1;
        for(j=i;f[j];j=f[j]){
            if(!upd(j)) break;//不能更新就退出
        }
        write(fir[1]);
        putchar(' ');
    }
    putchar('\n');
    return 0;
}
```


---

## 作者：Felix72 (赞：2)

先来一个朴素动规。

对于每个节点设置两个状态，表明从它的子树中的某一个节点跳到他本身时经过最多的颜色最少能是多少。之所以要记两个，是因为更新时要用到次大值。这也要求两条路径之间不重合，和求树的直径类似。

转移时，考虑每个节点对其父亲的影响。不难想到可以贪心，根据当前的最大值染色，从而用最大值更新。但是因为一条边只能染一种颜色，那么次大值的量会加一。

那么对于每种情况，动规一次即可，这样可以过数据较小的测试点。

再来考虑优化。

刚才我们注意到，每加一个点都要重新动规一次，这很浪费时间，于是我们开始考虑从新点往上跳。转移方程可以不变，但是如果一棵字数很大，那么他的子节点上跳时，很有可能用自己把父亲更新了多次。于是再加入两个数组，记录转移的位置。更新时，需要特判是否有自己之前的贡献，若有，则需删除。

这种方法已经优秀了许多，但仍然会被链卡住。我们加个小优化：如果自己对父亲没贡献，再上跳也没有意义了，直接退出。于是我们发现，这个黑题就这么通过了。为什么呢？

这是因为，我们考虑一种不太优秀的方式：直接树剖。就算这样，每个值也是对数级别的答案。也就是说，每个点不需要被更新很多次，那么暴力上跳的方法自然没问题了。

代码有注释讲解：

```cpp
//我把朴素的DP也放在了里面，也就是treedp 
#pragma GCC target("avx")
#pragma GCC optimize(2)
#pragma GCC optimize(3,"Ofast","inline")
#include <bits/stdc++.h>
using namespace std;
const int N = 1000010;
int n, prt[N], h[N], cnt, fin[N], f1[N], f2[N], tot, dep[N], ans;
//这里有些数组（包括链式前向星）在正解中无需用到，忽略即可
int p1[N], p2[N];
struct edge {int to, next;} e[N * 2];
inline void add(int x, int y)
{e[++cnt].to = y, e[cnt].next = h[x], h[x] = cnt;}
inline void treedp(int now, int maxn)
{
	f1[now] = 0, f2[now] = 0;
	int ans = 0;
	for(int i = h[now]; i; i = e[i].next)
	{
		int to = e[i].to;
		if(to == prt[now] || to > maxn) continue;
		treedp(to, maxn);
		int cur = max(f2[to] + 1, f1[to]);
		if(cur > f1[now]) f2[now] = f1[now], f1[now] = cur;
		else if(cur > f2[now]) f2[now] = cur;
	}
}
inline void jump(int now) //上跳 
{
	if(f1[now] < f2[now]) swap(f1[now], f2[now]), swap(p1[now], p2[now]);
	if(now == 1) return ;
	int cur = max(f1[now], f2[now] + 1);
	if(cur > f1[prt[now]] && p2[prt[now]] != now)
	{
		if(p1[prt[now]] == now)
		{
			f1[prt[now]] = cur; //上次的贡献也是自己给的，需要删除 
		}
		else
		{
			p2[prt[now]] = p1[prt[now]], p1[prt[now]] = now;
			f2[prt[now]] = f1[prt[now]], f1[prt[now]] = cur;
		}
		jump(prt[now]);
	}
	else if(cur > f2[prt[now]] && p1[prt[now]] != now)
	{
		p2[prt[now]] = now;
		f2[prt[now]] = cur, jump(prt[now]);
	}
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n;
	dep[1] = 1;
	for(int i = 2; i <= n + 1; ++i)
	{
		cin >> prt[i];
		dep[i] = dep[prt[i]] + 1;
		add(prt[i], i);
	}
	for(int i = 2; i <= n + 1; ++i)
	{
		jump(i);
		cout << f1[1] << " ";
	}
	return 0;
}
```

这类题目看似不太可做，但有时答案的值域也很重要。

这里再提供一个思路：

由于答案单调递增，并且值域很小，所以可以二分对数次，里面使用动规检验。然而这样时间复杂度多一个对数级，难以通过此题的百万数据。

---

## 作者：xfrvq (赞：0)

暴力 dp，设 $f_u$ 为仅考虑 $u$ 子树时答案。

+ 根节点：给每个子树 $(u,v)$ 分配新颜色，$f_u=\max(f_v)+1$。

+ 非根节点：可以给某个 $v$ 分配 $(fa_u,u)$ 的颜色，其余子树答案 $+1$。贪心给最大的 $f_v$ 即可。$f_u=\max\{\max(f_v),\mathrm{secmax}(f_v)+1\}$。

考虑剪枝，更新不了答案就返回。复杂度 $O(\sum f_i)$，$f_i$ 为每个点最终答案。

由于答案优于重剖，有 $O(\sum f_i)\le O(n\log n)$，因此复杂度正确。

---

## 作者：cosf (赞：0)

暴力题。

我们先看一下最优策略。

~~我们令 $\sout{dp_i}$ 表示以 $\sout{i}$ 为根子树的答案，则输出的就是 $\sout{dp_1}$。可以发现，这样是不够的，所以我们要重新设。~~

我们先定义一下 $i$ 点的答案 $a_i$。假设根为 $r$ 且 $r$ 有连向 $i$ 的边（讨论子树），则 $a_i$ 为最小化的 $\max_{j \in S_i}\{w_r(j)\}$，其中 $S_i$ 表示 $i$ 的子树的点集。

接着，我们令 $m_i$ 表示 $i$ 的所有子节点的最大 $a_i$，$s_i$ 表示次大 $a_i$。注意，$m_i$ 可能等于 $s_i$，并且，输出的东西是 $m_1$，不是 $a_1$。因为 $1$ 没有父节点。

这个东西怎么转移呢？对于一个节点 $i$，它连接到它的父节点（$p_i$）的边应该是什么颜色呢？当然和 $i$ 连向 $a_j$ 最大的子节点的边的颜色一样。这样，$a_i$ 就是 $\max\{m_i, s_i + 1\}$。如果颜色是其他的，$a_i$ 就是 $m_i + 1$，显然不优。这个连的方式满足同种颜色形成一条链。

注意：对于一条链，如果它内部所有点的最近公共祖先不是链的一端，则把这个链拆开，两边分别染色效果一致，所以讨论的链都是一段从某个点往根的路径的一部分。

小结一下，我们得到了转移方程（$v_i$ 为 $p_j = i$ 的 $j$ 够成的集合）：

$$
a_i = \max\{m_i, s_i + 1\}\\
m_i = \max_{j \in v_i}\{a_i\}\\
s_i = \operatorname{submax}_{j \in v_i}\{a_i\}\\
$$

接着，我们讨论一下答案的范围。

我们猜测一下答案是 $\log n$ 级别的。假设 $d_k$ 表示 $a_i = k$ 的最小点数。

注意到，$a_i \gt m_i = \max_{j \in v_i}\{a_i\}$ 当且仅当 $m_i = s_i$，所以，$a_i \gt m_i$ 的 $i$，它的点数就必将大于 $m_i$ 所在的子节点的点数 $\times 2$，即，$d_k \ge 1 + 2 \times d_{k - 1}$。

显然，$d_k$ 是指数级增长的。这也就是说，每个点的 $a_i$ 至多会更新 $O(\log n)$ 次。因此，在此题中，每加入一个点，都暴力地更新它的父节点即可。当然，如果更新了一个父节点，它的 $a_i$ 没有变，就没必要继续更了，这样就保证总复杂度是 $O(n\log n + n) = O(n \log n)$ 的了。

代码不长。记得快读。

```cpp
#include <iostream>
using namespace std;

#define MAXN 1000006

int fa[MAXN];

int mx[MAXN][2];

void del(int i, int x)
{
    if (mx[i][1] == x)
    {
        mx[i][1] = 0;
    }
    else if (mx[i][0] == x)
    {
        mx[i][0] = mx[i][1];
        mx[i][1] = 0;
    }
}

void add(int i, int x)
{
    if (mx[i][0] < x)
    {
        mx[i][1] = mx[i][0];
        mx[i][0] = x;
    }
    else if (mx[i][1] < x)
    {
        mx[i][1] = x;
    }
}

int n;

int main()
{
    n = read();
    for (int i = 2; i < n + 2; i++)
    {
        fa[i] = read();
        int x = i;
        int lm = 0;
        while (x != 1 && lm != max(mx[x][0], mx[x][1] + 1))
        {
            int cm = max(mx[fa[x]][0], mx[fa[x]][1] + 1);
            del(fa[x], lm);
            lm = cm;
            add(fa[x], max(mx[x][0], mx[x][1] + 1));
            x = fa[x];
        }
        printf("%d ", mx[1][0]);
    }
    puts("");
    return 0;
}

```

---

## 作者：MiniLong (赞：0)

考虑确定树的形态怎么做，显然染色可以是一条链，那么设 $f_u$ 是 $u$ 子树中距离 $u$ 上的路径中颜色最多的那个最少是多少。转移显然有 $f_u = semax_u$，其中 $semax_u$ 为 $u$ 的儿子中非严格次小的 $f_v$。

这时就有 $\Theta(n^2)$ 做法了，就是每次加一个点就更新所有祖先。

其实这个是 $\Theta(n\log n)$ 的，考虑证明。首先所有只有一个儿子的链显然可以压起来，这时整棵树的树高是 $\Theta(\log n)$ 的，那么因为每个点的 $f_u$ 的上界是它子树中最大深度，所以 $f$ 的和上界是 $\Theta(n \log n)$ 的。

由于每次更新都是使 $f$ 的和增加，所以有效更新只有 $\Theta(n\log n)$ 次，每次暴力往上更新的时候如果一次无效直接摆烂就行。

总复杂度 $\Theta(n\log n)$。

---

没想到复杂度是 $\Theta(n \log n)$，还是太菜了。

---

## 作者：Phartial (赞：0)

很厉害的题！

显然我们可以把一条拐弯的同色路径在 LCA 处划分成两条直的同色路径（互相不同色）且不影响答案，所以题目问的就是最佳链剖分。

设 $f_i$ 表示只考虑 $i$ 的子树时的答案。但是 $f_i$ 无法转移，因为枚举连向儿子的边的颜色并决策的开销是极大的。

于是考虑将 $f_i$ 定义修改为考虑 $i$ 的子树与 $i$ 到父亲的边时的答案，发现 $i$ 到父亲这条边会使除了一个儿子外的其他所有儿子的 $f$ 加一，那么这个不被加的儿子必然是选 $f$ 的最大值最优。

设 $g_{i,0/1}$ 为 $i$ 的所有儿子中 $f$ 的最大值/非严格次大值，有转移方程 $f_i=\max(g_{i,0},g_{i,1}+1)$。于是我们做到了单次 $\mathcal{O}(n)$，总共是 $\mathcal{O}(n^2)$ 的，考虑优化。

显然添加一个叶子只会改变它到根的路径上的 $f$ 与 $g$，因此加入一个叶子时可以只跳父亲并更新 $f,g$，但这样还是 $\mathcal{O}(n^2)$ 的。

我们再加入一个优化：如果跳到了一个节点并且这个节点的 $f$ 没有被更新，那么它的祖先就不会被影响了，于是我们可以直接结束更新流程。于是你就过了。

是不是特别厉害！事实上它的复杂度是 $\mathcal{O}(n\log n)$ 的，因为 $f$ 值总是单调不减的，而且对一个节点的有效更新必然会使其上的 $f$ 值增加一，所以总时间复杂度是 $\mathcal{O}(\sum\Delta f_i)=\mathcal{O}(n\Delta f_1)$ 的（无效更新只会在每个更新流程中遇到最多一次，所以它只会贡献 $\mathcal{O}(n)$ 的复杂度，无关紧要）。于是我们只需要给出 $\Delta f_1$ 的一个上界。

注意到当我们链剖分的方案是重链剖分时 $f_1$ 是 $\mathcal{O}(\log n)$ 的，所以 $\Delta f_1$ 也是 $\mathcal{O}(\log n)$ 的，于是总时间复杂度 $\mathcal{O}(n\log n)$，并且常数极小。

```cpp
#include <iostream>

using namespace std;

const int kN = 1e6 + 1;

int n, fa[kN], f[kN], g[kN][2];

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n, ++n;
  fill(g[1], g[n + 1], -n);
  f[1] = 1;
  for (int i = 2; i <= n; ++i) {
    cin >> fa[i];
    f[i] = 1;
    for (int x = i, p = fa[i]; x > 1; x = p) {
      p = fa[x];
      if (f[x] >= g[p][0]) {
        g[p][1] = g[p][0], g[p][0] = f[x];
      } else if (f[x] > g[p][1]) {
        g[p][1] = f[x];
      }
      int _f = max(g[p][0], g[p][1] + 1);
      if (_f == f[p]) {
        break;
      }
      f[p] = _f;
    }
    cout << g[1][0] << ' ';
  }
  return 0;
}
```
# 

---

## 作者：BotYoung (赞：0)

前置知识：**树形 DP**、**树链剖分**

## 题意
有一棵有根树，初始只有节点 $1$。现在依次加入 $n$ 个节点，并对所有的边进行染色。对于每一种颜色，需要保证它的边集一定是一条简单路径。定义一棵树的价值为：从根节点出发，一条简单路径经过边的不同颜色数量的最大值。每次加入节点后，你需要使树的价值最小，并输出这个最小值。
## 思路
`*2600` 下位黑，算是小清新题目，还是简单讲讲吧。

### Q1：这个问题的静态版本？
如题，我们考虑给定树的形态确定时，如何计算树的最小价值。

我们把边的颜色下放，那么每条边的颜色无非分为两种简单情况：要么与父亲节点相同，要么不同。

为什么这样想？因为一旦选定了父亲的颜色扩展的方向，其他儿子显然与父亲的颜色不同，不然这个颜色对应的边集就是一棵树了，不满足题意。

所以我们的策略是：我们对于每个节点，选择它的一个子节点染成相同的颜色。

令 $f_u$ 表示以 $u$ 为根的子树的最小价值。直接暴力选择，转移式为：

$$f_u=\min\limits_{x\in u}(f_x+1,\max\limits_{y\in u,y\neq x}f_y)$$

简单的贪心一下，不难发现，选择儿子的子树价值一定是所有儿子中最大的。所以问题实际上是一个最大值转移，判断一下当前子树的最大价值是否由所有儿子子树中的最大价值转移而来。令儿子对应子树中答案的最大值为 $mxn$，次大值为 $se$，写出新的表达式为：

$$f_u=\max(mxn_u,se_u+1)$$

到这里都还算简单。
### Q2：如何进行动态维护？
首先举一个熟悉得不能再熟悉得例子：$O(n\log n)$ 求最长上升子序列。

思考一下，我们维护最长上升子序列是怎么维护的？

我们会暂存一个可能的“方案”，每加入一个数就尽可能长地更新上升子序列。

类比此题，大致思路是一样的。加入一个点后，只会对根节点到这个点的路径上的答案产生影响。我们需要更新这条路径上每个点子树中的最大和次大价值。

所以我们从新加入的节点开始不断往上跳，尽可能远地更新答案，并把新的价值“暂存”。若一个子树的价值不会变化，那么就停止更新。
### Q3：这种做法的复杂度？
有句话说得好：有些看似假的算法却有着正确的复杂度。

观察法发现，树的价值不会超过 $\log n$。

考虑一种暴力的划分策略。有一个~~显然的~~结论是：**最优解会按照重链剖分的结果进行划分**。虽然我们不需要每次对原树进行暴力剖分，但是这个结论提醒我们，一个点被更新的次数不会超过重链条数，即 $\log n$。

所以这个做法的总复杂度是 $O(n\log n)$ 的。

喜闻乐见 Again & Again：
```cpp
#include <bits/stdc++.h>
#define reg register
#define rep(i, l, r) for (reg int i = l; i <= r; i++)
#define per(i, r, l) for (reg int i = r; i >= l; i--)
using namespace std;
typedef long long ll;
typedef unsigned long long llu;
namespace io {
inline ll read(){
    reg ll s = 0, f = 1;
    reg char ch = getchar();
    while (ch < '0' || ch > '9') { if (ch == '-') f = -1; ch = getchar(); }
    while (ch >= '0' && ch <= '9') s = (s << 1) + (s << 3) + (ch ^ '0'), ch = getchar(); 
    return s * f;
}
inline void write(reg ll x){
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) write(x / 10); putchar(x % 10 ^ '0');
}
inline void write(reg ll x, reg char c){
    write(x), putchar(c);
}
}//namespace io
using namespace io;
const int N = 1e6 + 5;
int n, fa[N], f[N][2], dp[N];
inline bool update(int u, int v){
    if (dp[v] > f[u][0]) f[u][1] = f[u][0], f[u][0] = dp[v];
    else if (dp[v] > f[u][1]) f[u][1] = dp[v];
    return max(f[u][0], f[u][1] + 1) != dp[u];
}
int main(){
    n = read();
    dp[1] = 1;
    rep(i, 2, n + 1){
        fa[i] = read();
        dp[i] = 1;
        for (int u = i; update(fa[u], u) && fa[u]; u = fa[u])
            dp[fa[u]] = max(f[fa[u]][0], f[fa[u]][1] + 1);
        write(f[1][0], ' ');
    }
    return 0;
}
```

---

