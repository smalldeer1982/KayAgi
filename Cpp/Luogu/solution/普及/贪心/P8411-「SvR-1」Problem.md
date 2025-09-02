# 「SvR-1」Problem

## 题目背景

小 L 打颓被 nodgd 发现，于是他开始做题了。

## 题目描述

他的 DS 非常菜，于是他把一共 $n$ 道 DS 题加到了自己的计划题单里，其中第 $i$ 道题的有趣程度为 $a_i$。

由于他并不精通 DS，他发现他在做一些题目之前需要先做另一些题目。这样的关系共有 $n - 1$ 组，他还发现每道题都出现在了这些关系中且没有重复。

他发现 $\forall 2 \leq i \leq n$，第 $i$ 题和第 $fa_i$ 题间存在上文所述的关系，且 $1 \leq fa_i < i$。**他必须先做第 $fa_i$ 题后才能做第 $i$ 题**。

他发现，如果他在做一道题之前高兴程度为 $k$，则他做完第 $i$ 题后，他的高兴程度便会变为 $\min(k, a_i)$。**他做题前的高兴程度为无穷大**。

他想问你**在必须先做第 $1$ 题且不能重复做某一道题**的情况下，他在做题的全过程中每做完一道题后**高兴程度之和的最大值**。

## 说明/提示

#### 样例 #1 解释
在该组样例中 $a = [3398922311, 3077554952, 2933028207, 4018360144, 1263042788, 835814542]$，$fa_2 = fa_3 = fa_4 = 1$，$fa_5 = fa_6 = 2$。

最优方案之一：依次做第 $1, 4, 2, 3, 5, 6$ 题，最大值为 $3398922311 + 3398922311 + 3077554952 + 2933028207 + 1263042788 + 835814542 = 14907285111$。
#### 伪代码参考
$$
\def{\b}#1{ \textbf{ #1 } }\def{\t}#1{\text{ #1 }}\def{\s}{\quad}\def{\f}#1{\textsf{ #1 }}
\def{\l}{\underline{\kern{300pt}}\\[-10pt]} 
\def{\r}{\overline{\underline{\kern{300pt}}}}
\begin{aligned}
&\r\\&\b{Algorithm:}\t{Get }a_i,fa_i\\[-13pt]&\l\\
&\begin{aligned}
    \f{1.}&\b{function} \b{\color{red}unsigned int} \t{getnext}(\b{\color{red}unsigned int}\&seed): \\
    \f{2.}&\s seed=seed\oplus\t{left}(seed,13)\\
    \f{3.}&\s seed=seed\oplus\t{right}(seed,17)\\
    \f{4.}&\s seed=seed\oplus\t{left}(seed,5) \\
    \f{5.}&\s \b{return} seed\\
    \f{6.}&\b{function} \t{main}(n):\\
    \f{7.}&\s \b{for} i \b{from} 1 \b{to} n \b{step}1\\
    \f{8.}&\s\s a_i=\t{getnext}(seed)\\
    \f{9.}&\s \b{end for} \\
    \f{10.}&\s \b{for} i \b{from} 2 \b{to} n \b{step}1\\
    \f{11.}&\s\s fa_i=\t{getnext}(seed)\bmod(i-1)+1\\
    \f{12.}&\s \b{end for} \\
    \end{aligned}\\[-12pt]
&\r
\end{aligned}
$$

其中 $\text{left}(x,d)$ 和 $\text{right}(x,d)$ 分别表示将 $x$ 左移或右移 $d$ 位。
#### 数据规模与约定
**本题自动开启捆绑测试和 O2 优化。**
$$
\newcommand{\arraystretch}{1.5}
\begin{array}{c|c|c}\hline\hline
\textbf{Subtask} & \bm{n \leq} & \textbf{分值} \\\hline
\textsf{1} & 10 & 10 \\\hline
\textsf{2} & 10^4 & 20 \\\hline
\textsf{3} & 10^6 & 20 \\\hline
\textsf{4} & \text{无特殊限制} & 50 \\\hline\hline
\end{array}
$$

对于 $100\%$ 的数据，$1 \leq n \leq 10^7$，$0 \leq seed < 2^{32}$。

## 样例 #1

### 输入

```
6 114514```

### 输出

```
14907285111```

# 题解

## 作者：liangbowen (赞：24)

## 前言

[题目传送门！](https://www.luogu.com.cn/problem/P8411)

[更好的阅读体验？](https://www.luogu.com.cn/blog/liangbowen/solution-p8411)

本次比赛第二题，好像没有人抢题解，那我来一发。

思路还是挺巧妙的。

## $\texttt{10 pts}$ 思路

深搜求解即可。

最坏情况，时间复杂度 $O(n!)$。

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
typedef unsigned int UI;
typedef unsigned long long ULL;
inline UI get_next(UI &seed) //直接套用给出的随机数代码即可。
{
	seed ^= seed << 13;
	seed ^= seed >> 17;
	seed ^= seed << 5;
	return seed;
}
UI n, seed;
UI a[105], fa[105];
ULL maxn = 0;
bool vis[105];
void dfs(int x, ULL sum, UI minn)
{
	if (x == n)
	{
		//cout<<"sum="<<sum<<'\n';
		maxn = max(maxn, sum);
		return;
	}
	for (int i = 1; i <= n; i++)
		if (!vis[i] && vis[fa[i]]) //选过 fa[i] 且没选过 i 才可以。
		{
			vis[i] = true;
			dfs(x+1, sum + min(minn, (UI)a[i]), min(minn, (UI)a[i]));
			vis[i] = false; //回溯。
		}
}
int main()
{
	scanf("%u%u", &n, &seed);
	for (int i = 1; i <= n; i++) a[i] = get_next(seed);
	for (int i = 2; i <= n; i++) fa[i] = get_next(seed) % (i-1) + 1;
	vis[1] = true;
	dfs(1, (ULL)(a[1]), a[1]);
	printf("%llu", maxn);
    return 0;
}
```

## $\texttt{50 pts}$ 思路

前置知识点：拓扑排序。

没学过没关系，可以直接看正解。

---

观察本题，捕捉关键句，如下。

> 先完成 $fa_i$ 才能完成 $i$。

> 求和的最大值。

这不就是**拓扑排序**吗？

容易看出，用优先队列求解，每次选当前队列里的**最大值**即可。

所以要重载一下。

时间复杂度是带 $\log$ 的，可以卡过 $50\%$ 的数据。

最后按照拓扑序计算和即可。

类似模版，没有什么需要特别理解的地方。

```cpp
#include <iostream>
#include <cstdio>
#include <queue>
#define N 10000005
using namespace std;
typedef unsigned int UI;
typedef unsigned long long ULL;
inline UI get_next(UI &seed)
{
	seed ^= seed << 13;
	seed ^= seed >> 17;
	seed ^= seed << 5;
	return seed;
}
UI n, seed;
UI a[N], fa[N];
struct Edge
{
	int now, nxt;
}e[N];
int head[N], cur;
void add(int x, int y)
{
	e[++cur].now = y;
	e[cur].nxt = head[x];
	head[x] = cur;
}
struct Node
{
	UI x;
	bool operator <(const Node &t) const
	{
		return a[x] < a[t.x];
	}
};
int in[N], topo[N], Cur;
void topo_sort()
{
	priority_queue <Node> Q;
	Q.push( (Node){1} );
	while (!Q.empty())
	{
		int topi = Q.top().x;
		topo[++Cur] = topi;
		Q.pop();
		for (int i = head[topi]; i; i = e[i].nxt)
		{
			int p = e[i].now;
			in[p]--;
			if (in[p] == 0) Q.push( (Node){p} );
		}
	}
}
int main()
{
	scanf("%u%u", &n, &seed);
	for (int i = 1; i <= n; i++) a[i] = get_next(seed);
	for (int i = 2; i <= n; i++) fa[i] = get_next(seed) % (i-1) + 1;
	for (int i = 2; i <= n; i++) add(fa[i], i), in[i]++;
	topo_sort();
	ULL sum = 0, minn = 1e18;
	for (int i = 1; i <= n; i++) minn = min(minn, (ULL)a[topo[i]]), sum += minn;
	printf("%llu", sum);
    return 0;
}
```

## 正解

讲完部分分，终于可以将正解了。

~~然而正解和部分分几乎没有关系。~~

---

正解的突破口在于：$1 \leq fa_i < i$。

换句话说，**顺着扫一遍数组**，必定先扫到 $fa_i$ 再扫到 $i$。

进一步讲，**顺着扫，等同于遵守了拓扑序**。

这下，问题就很简单了，转移方程 $f_i = min(a_i, f_{fa_i})$。

注意到 $a_i$ 在后面没有用了，所以可以直接用 $a_i$ 代替$f_i$，节约空间。

另外，不存在 $fa_1$，所以开头稍作改变。

看到代码，你会觉得很简单的。

时间复杂度 $O(n)$。

```cpp
#include <iostream>
#include <cstdio>
#include <queue>
#define N 10000005
using namespace std;
typedef unsigned int UI;
typedef unsigned long long ULL;
inline UI get_next(UI &seed)
{
	seed ^= seed << 13;
	seed ^= seed >> 17;
	seed ^= seed << 5;
	return seed;
}
UI a[N], fa[N];
int main()
{
	int n;
	UI seed;
	scanf("%d%u", &n, &seed);
	for (int i = 1; i <= n; i++) a[i] = get_next(seed);
	for (int i = 2; i <= n; i++) fa[i] = get_next(seed) % (i-1) + 1;
	ULL sum = a[1]; //注意这里需要 long long 来储存。
	for (int i = 2; i <= n; i++) a[i] = min(a[i], a[ fa[i] ]), sum += a[i];
	printf("%llu", sum);
    return 0;
}
```

希望能帮助到大家，谢谢！

---

## 作者：Hisaishi_Kanade (赞：14)

### 零、前言

~~这道题我用链式前向星做的时候死活是TLE，眼泪都下来了~~

本题解会将`get_next`函数略加改动，效果一样。

题意很通俗易懂~~终于能看懂了~~，不多加解释，直接讲思路。

### 一、思路

首先很容易想到 $n\log n$ 的优先队列做法，每次在堆中选取最大值。

然而 $n\le10^7$，显然不能通过。

此时，我们需要发现这是一颗树，由树的特殊性质（一般的图不保证），得到**除了根节点（即1节点）的任意一个节点，都只有一个父节点**，那么就说明对于 $a_i$，它会不会变成 $\min\left\{k,a_i\right\}$ 就取决于 $fa_i$ 这个节点！

### 二、代码

```cpp
#include <stdio.h>
unsigned int seed;
inline void get_next(){
	seed^=seed<<13;
	seed^=seed>>17;
	seed^=seed<<5;
	return;
}
long long ans;
unsigned int a[10000005],fa[10000005];
int n,i;
#define min(a,b) a<b?a:b
int main(){
	scanf("%d %u",&n,&seed);
	for(i=1;i<=n;i++){
		get_next();
		a[i]=seed;
	}
	for(i=2;i<=n;++i){
		get_next();
		fa[i]=seed%(i-1)+1;
	}
	ans=a[1];//显然，a[1]必定会原封不动的被选
	for(i=2;i<=n;++i)
		ans+=a[i]=min(a[i],a[fa[i]]);
	/*
	首先，a[i]必定要和已经被选的a[fa[i]]的求min（fa[i]<i）
	然后，此时ans+=min(k,a[i]) （a[fa[i]]即k）
	*/
	printf("%lld",ans);//输出
	return 0;
}
//over
```

---

## 作者：stntn (赞：5)

## [题目链接](https://www.luogu.com.cn/problem/P8411)

## 优先队列？

首先很容易想到，我们一定是从上到下地去选择这些节点，即先选择 $fa_i$ 后才可能选择 $i$，并且一定是按权值由大到小地选择。

由此可以想到，对于目前可以选择的点，我们维护一个优先队列，每次从队首取点，更新答案，并压入其儿子节点。

复杂度 $O(n\log n)$，期望得分 50。

## DP？

只是有点像DP罢了，实际就是搜索。

按上面的思路考虑更新答案的方式，要想选择某个节点，必先选择其父亲节点 $fa_i$ 和其他能够选择的，**权值比它大**的节点。

因为节点 $i$ 的贡献为 $\min(k,a_i)$，**任何权值比它大的节点**不会对答案造成任何影响，所以对于节点 $i$ 可能影响答案的节点有且只有选择 $fa_i$ 时的贡献，也就是 $\min(k_{fa_i},a_{fa_i})$。

由此，我们记录一个节点的贡献为 $f_i$，可得转移方程为 $f_i=\min(f_{fa_i},a_i)$。 

复杂度 $O(n)$ 期望得分 100。

```cpp
#include<bits/stdc++.h>
#define N 10000010
#define M 110
#define LL long long
#define ULL unsigned long long
#define DB double
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define per(i,a,b) for(int i=a;i>=b;i--)
#define tep(i,u) for(int i=head[u];~i;i=e[i].nxt)
#define INF 0x3f3f3f3f3f3f3f
#define pir pair<LL,LL>
#define mp(i,j) make_pair(i,j)
#define se second
using namespace std;
template <typename T> inline void read(T &a)
{
	a=0;T w=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){a=(a<<3)+(a<<1)+(ch^48);ch=getchar();}
	a*=w;
}
template <typename T,typename ...Args> inline
void read(T &x,Args &...args){read(x);read(args...);}
int n,fa[N],head[N],cc;
LL a[N],ans;
struct EDGE{int v,nxt;}e[N<<1];
inline void add_edge(int u,int v){e[++cc]={v,head[u]};head[u]=cc;}
unsigned int seed;
inline unsigned int get_next(unsigned int &seed)
{
	seed^=seed<<13;
	seed^=seed>>17;
	seed^=seed<<5;
	return seed;
}
inline void dfs(int u,int f,LL now)
{
	ans+=min(now,a[u]);
	tep(i,u)
	{
		int v=e[i].v;if(v==f) continue;
		dfs(v,u,min(now,a[u]));
	}
}
signed main()
{
	memset(head,-1,sizeof(head));
	read(n,seed);
	// ...
	rep(i,1,n) a[i] = get_next(seed);
	rep(i,2,n) fa[i] = get_next(seed) % (i - 1) + 1,add_edge(fa[i],i);
	// ...
	dfs(1,0,INF);
	printf("%lld\n",ans);
	return 0;
}
```

然而实际得分 50。

至此，题面文本上能得到的信息已用尽，貌似已无法优化。

**但是**

```cpp
for (register int i = 2; i <= n; i++)
	fa[i] = get_next(seed) % (i - 1) + 1;
```

**节点 $i$ 的父亲 $fa_i$ 满足 $fa_i<i$。**

因为更新到 $i$ 时，$fa_i$ 一定已被更新，所以我们可以省略掉建树和搜索，**直接在 $fa$ 数组上跑 $DP$**。

复杂度 $O(n)$ 期望得分 100，实际得分 100。

```cpp
#include<bits/stdc++.h>
#define N 10000010
#define LL long long 
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define per(i,a,b) for(int i=a;i>=b;i--)
#define INF 0x3f3f3f3f3f3f3f
int n;LL ans;
unsigned int seed,a[N];
inline unsigned int min(unsigned int a,unsigned int b){return a>b ? b:a;}
inline unsigned int get_next(unsigned int &seed)
{
	seed^=seed<<13;
	seed^=seed>>17;
	seed^=seed<<5;
	return seed;
}
signed main()
{
	scanf("%d%d",&n,&seed);
	rep(i,1,n) a[i]=get_next(seed);ans=a[1];
	rep(i,2,n) a[i]=min(a[i],a[get_next(seed)%(i-1)+1]),ans+=a[i];
	printf("%lld\n",ans);
	return 0;
}
```
**注意 `unsigned int` 最好不要改为其他类型，也不要 `#define int long long`**

---

## 作者：InterN_NOT_FOUND (赞：5)

根据题意，我们可以对所有题目建一棵树，有趣值即点权。

这里就拿样例当例子了。

![](https://cdn.luogu.com.cn/upload/image_hosting/9u9i0n6w.png)

如图，上面红色的数字是点权，下面蓝色的数字是更新后的点权。

根据题意，每做一道题就必须先做它的所有祖先，而做这道题的有趣值为这个点的点权与上一道题点权的最小值。所以我们把每个点的点权更新为**这个点的点权和它的上一级祖先点权的最小值**。同时因为树的特殊性质，对于每一个非根节点有且只有一个父节点，说明对于每一个非根节点的点权 $a_i$ 是否会更新为 $\min (k, a_i)$ 仅与其上一级祖先点权 $fa_i$ 有关。然后再把每个点的点权加起来就可以了。

code:
```cpp
#include<bits/stdc++.h>
#define int unsigned int

namespace IO{
	inline bool isnum(char ch){return ch>='0'&&ch<='9';}
	inline __int128 read()
	{
		__int128 x=0,f=1;char ch=getchar();
		while (!isnum(ch)){if (ch=='-') f=-1;ch=getchar();}
		while (isnum(ch)){x=x*10+ch-48;ch=getchar();}
		return x*f;
	}
	inline void out(__int128 x,char ch){
	    if(x<0){putchar('-');x=-x;}
	    if(x>9)out(x/10,'/');
	    putchar(x%10+'0');
	    if(ch=='l')putchar('\n');
	    if(ch=='s')putchar(' ');
	}
}

using namespace std;
using namespace IO;

inline int get_next(int &seed){
	seed ^= seed << 13;
	seed ^= seed >> 17;
	seed ^= seed << 5;
	return seed;
}

const int N = 1e7 + 10;

int a[N], fa[N], n = read(), seed = read();

unsigned __int128 ans;

signed main()
{
	for (register int i = 1; i <= n; i++){
		a[i] = get_next(seed);
	}
	for (register int i = 2; i <= n; i++){
		fa[i] = get_next(seed) % (i - 1) + 1;
	}//输入
	
	for (int i = 2; i <= n; ++i) {
		a[i] = min(a[i], a[fa[i]]);//更新点权
	}
	
	for (int i = 1; i <= n; ++i) {
		ans = ans + a[i];
	}
	
	out(ans, 'l');
	return 0;
}

// ypa!

```


---

## 作者：zesqwq (赞：4)

本题目十分地**卡常**，如果使用链式前向星建图并且代码较为繁琐，则容易TLE。

这里提供一种不用建图的方法，142ms。

## 题意

给你一棵树，这棵树根节点是1，每个节点代表一个题目，每个题目有自己的高兴程度 $a_i$ 。

对于一个作业 $i$ ，只有做了 $fa_i(1 \leq fa_i<i)$，才可以完成题目 $i$ 。

一开始他是十分开心，高兴值为无穷大，但是每做一个题目高兴值就会变成 当前开心值与作业高兴值的最小值。

假设这些题目都要做完，求一个顺序使得**做完每道题目后高兴值的总和**最小。

## 分析

最简单的 $\Theta(n \log n)$ 的做法就是用一个优先队列表示现在能做的作业。

先把第一个节点放入队列，然 后每次取出队列中开心值最大的作业，把它完成并且更新高兴值之后把它的孩子放入队列。

这样做正确的原因是因为当你做了作业 $i$ 之后的高兴值肯定小于 $a_i$，那肯定开始就要取尽可能大的。

这样卡卡常数可以过 $10^6$ 的点。

然后就是如何达到 $\Theta(n)$ 。

思考如果你做了作业 $i$ ，说明一定已经完成了所有 $i$ 的祖先，此时我们就令 $b_i$ 为 $\min(a_i, a_\text{i的所有祖先})$

这样处理后 $\forall i, b_i \leq b_{fa_i}$ 。

此时就不用记录高兴值了，因为如果和 $\Theta(n \log n)$ 做法一样用优先队列存储，那么后面进入优先队列的高兴值肯定不大于其先进入的祖先，此过程中优先队列依次取出的数一定呈非严格递减关系。

那么**变换后他每次做完一个作业后的高兴值就是这个作业的高兴值**。

既然每个作业都和以前的高兴值状态无关了，那还要这个优先队列干嘛？直接遍历变换后每个作业的高兴值，然后累加就行了，这样就把优先队列的 $\Theta(\log n)$ 优化掉了。

## 关于建图

这里其实是不用建图的，因为我们可以遍历到节点 $i$ 时不断向上跳直到遇到一个已经变换之后的节点，然后自上向下更新。

但是题目中有一个限制 $1 \leq fa_i<i$ ，意味着如果从1到n遍历，那么其父亲肯定是变换过的。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e7 + 10;
unsigned seed, a[N];
int n, fa[N];
inline unsigned get_next(unsigned &seed){
	seed ^= seed << 13, seed ^= seed >> 17, seed ^= seed << 5;
	return seed;
}
int main(){
    cin >> n >> seed;
    for (int i = 1; i <= n; i++)
		a[i] = get_next(seed);
    for (int i = 2; i <= n; i++)
		fa[i] = get_next(seed) % (i - 1) + 1;
    a[0] = UINT_MAX;
    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        if (a[i] > a[fa[i]])
            a[i] = a[fa[i]];
        ans += a[i];
    }
    cout << ans;
    return 0;
}
```





---

## 作者：Zvelig1205 (赞：4)

# P8411 「SvR-1」Problem

感谢这场比赛，让我的比赛分 +29![](//图.tk/3)。

[题目传送门](https://www.luogu.com.cn/problem/P8411)

题意比较通俗，就不再解释了。

## Solution.1

第一反应：搜索。

贪心一下，每次选取能走的点里最大的点。

那么就可以用一个优先队列将现在的点储存下来，每次取最大值。

时间复杂度 $O(n\log n+m)$。

Code:

```cpp
#define int unsigned int
const int inf=1e7+7;
int n,seed;
long long ls=1e18,ans;
inline int get_next(int &seed){
	seed ^= seed << 13;
	seed ^= seed >> 17;
	seed ^= seed << 5;
	return seed;
}
int a[inf],b[inf],fa[inf];
struct node{
	int id,val;
	bool operator <(const node &b)const
	{
		return val<b.val;
	}
};
int fir[inf],nex[inf<<1],poi[inf<<1],cnt;
void ins(int x,int y)
{
	nex[++cnt]=fir[x];
	poi[cnt]=y;
	fir[x]=cnt;
}
priority_queue<node>h;
signed main(){
	n=re();seed=re();
	for (register int i = 1; i <= n; i++)
		a[i] = get_next(seed);
	for (register int i = 2; i <= n; i++)
	{
		fa[i] = get_next(seed) % (i - 1) + 1;
		ins(fa[i],i);
	}
	h.push((node){1,a[1]});
	while(h.size())
	{
		node now=h.top();h.pop();
		ls=min(ls,now.val+0ll);
		ans+=ls;
		for(int i=fir[now.id];i;i=nex[i])
			h.push((node){poi[i],a[poi[i]]});
	}
	wr(ans);
	return 0;
}
```

实测 50。

## Solution.2

~~没什么用的优化。~~

优先队列 bfs 的瓶颈在于堆的排序会多一个 log，那么可不可以将这个 log 去掉？

通过观察，可以发现，各个兄弟节点之间是毫无影响的。

那么就可以通过 dfs，在递归的时候比较从根到当前节点的最小值与子节点的权值，就可以消除兄弟节点间的影响了。

时间复杂度 $O(n+m)$。

Code:

```cpp
#define int unsigned int
const int inf=1e7+7;
int n,seed;
int a[inf],b[inf],fa[inf];
long long ans;
inline int get_next(int &seed){
	seed ^= seed << 13;
	seed ^= seed >> 17;
	seed ^= seed << 5;
	return seed;
}
int fir[inf],nex[inf],poi[inf],cnt;
inline void ins(int x,int y)
{
	nex[++cnt]=fir[x];
	poi[cnt]=y;
	fir[x]=cnt;
}
void dfs(int now,int val)
{
	ans+=val;
	for(int i=fir[now];i;i=nex[i])
		dfs(poi[i],min(val,a[poi[i]]));
}
signed main(){
	n=re();seed=re();
	for (register int i = 1; i <= n; i++)
		a[i] = get_next(seed);
	for (register int i = 2; i <= n; i++)
	{
		fa[i] = get_next(seed) % (i - 1) + 1;
		ins(fa[i],i);
	}
	dfs(1,a[1]);
	wr(ans);
	return 0;
}
```

实测 50。

## Solution.3

既然兄弟节点之间没有影响，那么建图其实是多余的。

题目保证 $fa_i<i$，就可以直接 for 一遍所有节点，给当前节点取当前节点与其父节点的最小值，相加即可。

时间复杂度 $O(n)$。

Code:

```cpp
#define int unsigned int
const int inf=1e7+7;
int n,seed;
int a[inf],fa[inf];
long long ans;
inline int get_next(int &seed){
	seed ^= seed << 13;
	seed ^= seed >> 17;
	seed ^= seed << 5;
	return seed;
}
signed main(){
	n=re();seed=re();
	for (int i = 1; i <= n; i++)
		a[i] = get_next(seed);
	for (int i = 2; i <= n; i++)
		fa[i] = get_next(seed) % (i - 1) + 1;
	ans=a[1];
	for(int i=2;i<=n;i++)
	{
		a[i]=min(a[i],a[fa[i]]);
		ans+=a[i];
	}
	wr(ans);
	return 0;
}
```

实测 100。

## 打广告![](//图.tk/3)

[My Blog](https://www.cnblogs.com/adm-1223/)

---

## 作者：sgl654321 (赞：2)

### 题目大意
- 给定 $n$ 道题目，在做第 $i$ 道题目之前，必须先做第 $fa_i$ 道题目。其中所有的 $fa_i<i(2\leq i\leq n)$。必须先做第 $1$ 题。
- 设某人的开心程度为 $k$。一开始某人的开心程度为无穷大。每做完一道题后，开心程度就会变为 $\min(k,a_i)$。
- 安排一种合法的做题顺序，使得每做完一道题之后的开心程度之和最大。

### 解题思路
一开始还想着用一种树形结构，来存储从属关系。可是一看到这个数据规模 $1\leq n \leq 10^7$，就知道一定是 $O(n)$ 的做法了。

再看一遍题目，本题最关键的一个信息就是对于所有的 $i(2 \leq i\leq n)$，有 $fa_i<i$。 因此，从前往后做一定是合法的做题顺序。

再考虑怎样让开心程度之和最大。显然，对于同一层级的（即 $fa$ 相等的几道题目），肯定要先做开心程度较大的。由于开心程度会变为 $\min(k,a_i)$，所以按照这一种方法做题，做完一道题后的开心程度就会变为 $\min(a_{fa_i},a_i)$。

还有一个要注意的点，不仅要把最后的答案加上开心程度，每一道题目的开心程度也要随之变化。就是说，要把 $a_i$ 赋值为 $\min(a_{fa_i},a_i)$。因为这道题目可能是后面有些题目的父亲。

### 代码部分

按照下面的步骤编写代码：
1. 输入 $n$ 和 $seed$，并用题目中的方法生成所有的 $a_i$ 与 $fa_i$。
2. 将 $ans$ 赋值为 $a_1$（必须先做第 $1$ 题）。
3. 从 $i=2$ 开始遍历。每一次既要修改 $a_i$，即 $a_i \gets min(a_i,a_{fa_i})$，又要把 $ans$ 加上 $a_i$。

需要注意的:
1. $n$，$seed$，$a$ 数组，$fa$ 数组都要开成 ```unsigned int```。
2. $ans$ 要开成 ```long long``` 或 ```unsigned long long```。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef unsigned int uint;
uint n,seed,a[10000010],fa[10000010];
unsigned long long ans;
inline uint get_next(uint &seed){
	seed ^= seed << 13;
	seed ^= seed >> 17;
	seed ^= seed << 5;
	return seed;
}

int main(){
	cin>>n>>seed;
	for (register int i = 1; i <= n; i++){
		a[i] = get_next(seed);
	}
	for (register int i = 2; i <= n; i++){
		fa[i] = get_next(seed) % (i - 1) + 1;
	}
	ans=a[1]; 
	for(register int i=2;i<=n;i++){
		//想要做 a[i],必定要先做a[fa[i]],在他的前面 
		//从前往后做就可以了！
		a[i]=min(a[fa[i]],a[i]);
		ans+=min(a[fa[i]],a[i]);
	//	cout<<ans<<endl; 
	}
	cout<<ans<<endl;
	
	return 0;
}
```
[传送门](https://www.luogu.com.cn/problem/P8411)在这里。

---

## 作者：farfarqwq (赞：2)

# 前言
本题思维难度中等，但我比赛时却没过（只得了 50 分）~~我太菜了~~。
# 正文

### 题目大意
有 $n$ 道题，对于每道题 $i$ 的高兴程度为 $a_i$，必须先做第 $fa_i$ 道题才能做它。走到每点 $i$ 时你的高兴程度会变成现在的高兴程度与 $a_i$ 的最小值，开始时高兴程度为无穷。求做完每道题后高兴程度之和的最大值。
### 题目分析
可以把它想象成一棵树，$fa_i$ 就为 $i$ 的父节点。

### 50 分做法：

贪心，但是用优先队列维护，走到每个节点时统计答案，并把它的字节点放进优先队列里，每次优先走开心值最大的节点。

部分代码：
```cpp
int fa[10000005];
vector<int> son[10000005];
long long ans = 0, now = 1e18;
struct node {
	long long num;
	int id;
	bool operator < (const node &b) const {
		return num < b.num;
	}
} a[10000005];//结构体存点（优先队列用)
```
BFS：
```cpp
void bfs() {
	priority_queue<node> q;
	q.push(a[1]);
	while (!q.empty()) {
		int id = q.top().id;
		now = min(now, q.top().num);//更新高兴程度
		ans += now;
		q.pop();
		for (register int i = 0; i < son[id].size(); i++)
			q.push(a[son[id][i]]);
	}
}
```
建树：
```cpp
for (register int i = 1; i <= n; i++){
	a[i].num = get_next(seed);
	a[i].id = i;
}
for (register int i = 2; i <= n; i++){
	fa[i] = get_next(seed) % (i - 1) + 1;
	son[fa[i]].push_back(i);
}
```

复杂度：$O(n \log n)$
### 满分做法
看看数据范围：$n \le 10^7$，会 TLE，我们应该把它变成 $O(n)$ 的。

对于每个点，走到它时的高兴程度最大应该为从根节点到它的路径上最小的节点，并且并不会被其他点影响（如果被人比它的答案小就晚点走它就行了）。最终答案就是每个点答案的总和，于是我们就可以开心的解决这个问题了！

满分代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef unsigned int uint;
int fa[10000005];
uint a[10000005];
inline uint get_next(uint &seed) {
	seed ^= seed << 13;
	seed ^= seed >> 17;
	seed ^= seed << 5;
	return seed;
}
int main() {
	// ...
	int n;
	uint seed;
	cin >> n >> seed;
	for (register int i = 1; i <= n; i++) {
		a[i] = get_next(seed);
	}
	for (register int i = 2; i <= n; i++) {
		fa[i] = get_next(seed) % (i - 1) + 1;
	}
	a[0] = 1e18;//开始时的高兴值，fa数组定义在全局，默认是0
	register long long ans = 0;
	for (register int i = 1; i <= n; i++) {//因为fa[i]<i，所以可以正着推，避免了复杂的搜索
		a[i] = min(a[i], a[fa[i]]);
		ans += a[i];
	}//关键语句
	cout << ans;
	return 0;
}
```
请勿抄袭呦~

---

## 作者：ande (赞：2)

###### ~~水一发题解：~~

仔细读题，注意题干的这几句话：

**他必须先做第 $fa_i$ 题后才能做第 $i$ 题。这样的关系共有 $n - 1$ 组，他还发现每道题都出现在了这些关系中且没有重复。**

所以可以很明显的发现是树型图，贪心的想一想，我们需要按照从大到小顺序进行遍历，所以很快想到了~~最短路~~最长路，我们可以从根节点开始在树上跑一个基础的最长路来确定每个问题的最优贡献值（需要提前建树，此处使用链式前向星存图）：
  
```cpp
 void dfs_ans(int s){
	 priority_queue<pair<uint , uint> > pq;
 //反向Dijk 将greater替换掉即可
	 pq.push({a[1],s});
	 // mp[s] = 1;//这里可+可不+
	 while(!pq.empty()){
		 pair<int ,int> p;
		 p = pq.top();
		 pq.pop();
		 int now =  p.second;
		 if(mp[now] == 1)
			 continue;
		 mp[now] = 1;
		 if(k >= a[now])
			 k = a[now];//k代表当前最小值，即最大贡献
		 ans += k;
		 for(int i = head[now]; i; i = edge[i].next){
			 int to_ = edge[i].to;
			 if(mp[to_] == 1)
				 continue;
			 pq.push({a[to_], to_});
		 }
	 }
}

```
  
快乐提交，获得了非常高的 50 分，往回看下题面和思路，找找我们思路哪里还可以优化，这里给读者一个思考时间，可以不往下翻回去重温题面想想优化。

------------
好的我们重读题面发现了一个至关重要的信息：

**他发现  $\forall 2 \leq i \leq n$，第 $i$ 题和第 $fa_i$ 题间存在上文所述的关系，且 $1 \leq fa_i$**；

所以对于每一个 $i$ ，它的 $fa_i$ 是在它之前指出的，并且每一个 $i$ 对应的贡献值是只与 $fa_i$ 有关，这就可以在每次指出 $i$ 对应的 $fa_i$ 时直接更新此时 $i$ 节点的最大贡献，就不需要存图 + 最长路了。
于是优化后的代码如下文：

```cpp
int main(){
	
	n = read(); seed = read();
	for (register int i = 1; i <= n; i++){
		a[i] = get_next(seed);
	}
	for (register int i = 2; i <= n; i++){
		fa[i] = get_next(seed) % (i - 1) + 1;
		a[i] = min(a[i],a[fa[i]]);//因为此时的fa[i]的贡献已经确定，所以直接更新即可
	}
	for(int i=1;i<=n;i++){
		ans += a[i];
	}
		
	printf("%lld",ans);//十年oi一场空，不开long long见祖宗
	return 0;

}
                   
```
                                     
OK ，完成啦，不会的私信欢迎问题哦~


---

## 作者：lanretE (赞：2)

先分析题目，每一道题看成一个节点，它必须在写完另一题以后才可以做，$1$ 号除外，显然这是一个以 $1$ 为根的树形结构。我们定义一个 $num$ 数组表示每个节点权值，$num_i$ 表示做完第 $i$ 道题之后的最大高兴程度，那么，$num_i$ 最大应该是点 $i$ 到根节点的路径上所有节点权值的最小值，因为路径上所有的点都是到达此节点前必须经过的。

当然，并不是所有时候节点的权值都可以取到上述最大值的，因为做这个题之前可能还会做并非它祖先节点的题，所以，我们要让在此节点之前的，并非此节点祖先节点的其他节点权值尽可能大。

我们把树形结构里面的每一条链以**链上权值最小值**为关键字从大到小排序，然后依次做每一条链上每个节点代表的题目。如此构造一下，所有节点的权值都只会被它的祖先影响（这是不可避免的），因为在它之前的，并非其祖先的节点，权值一定是大于当前节点的。

所以，每个节点的权值就是其到根节点的路径上所有节点权值的最小值。具体实现的时候，由于 $fa_i<i$，我们从前向后遍历节点，每次把当前节点的高兴程度与父亲节点的权值取较小值即可。

```
#include<iostream>
using namespace std;
typedef unsigned int uint;
uint n,seed;
const int N=10000010;
uint a[N],num[N],fa[N];
inline uint get_next(uint &seed){
	seed ^= seed << 13;
	seed ^= seed >> 17;
	seed ^= seed << 5;
	return seed;
}
int main(){
    scanf("%d%d",&n,&seed);
	
	for (register int i = 1; i <= n; ++i){
		a[i] = get_next(seed);
	}
	for (register int i = 2; i <= n; ++i){
		fa[i] = get_next(seed) % (i - 1) + 1;
	}
	
	for(register int i=1;i<=n;++i) num[i]=a[i];
	fa[1]=1;
	for(register int i=1;i<=n;++i) num[i]=min(num[i],num[fa[i]]);
	long long ans=0;
	for(register int i=1;i<=n;++i) ans+=num[i];
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：accomplishment (赞：1)

[传送门](https://www.luogu.com.cn/problem/P8411)

~~这题卡了我整场比赛。~~

首先我们来推一下样例：
> a = [3398922311, 3077554952, 2933028207, 4018360144, 1263042788, 835814542]
> 
> fa = [Null, 1, 1, 1, 2, 2]

因此我们可以通过 $fa$ 数组来画出一棵**树**：

![](https://cdn.luogu.com.cn/upload/image_hosting/7l7bi44a.png)

一个满足题目条件先完成第 $fa_i$ 道题再完成第 $i$ 道题的遍历顺序就是**从上到下**（其实就是满足**拓扑序**），即必须先完成 $1$，再完成 $2, 3, 4$；先完成 $2$，再完成 $5, 6$。

下面是具体的**思考方法**（建议仔细理解一下）：

那么影响到做完第 $i$ 道题**高兴程度** $k_i$ 的因素就是做完第 $fa_i$ 道题的高兴程度 $k_{fa_i}$ 与 第 $i$ 道题的**有趣程度** $a_i$。而若想**达到最大值**一定是先完成可以完成的题目中有趣程度**尽量大**的，再依次完成更小的。由于只有 $k_i$ 一定在 $k_{fa_i}$ 的后面，其他的顺序可以随便（尽量从大到小，**一定可以**），而 $k_{fa_i}$ 一定**大于等于** $k_i$，所以我们不用担心最大值取不到的情况。

根据题目中给出的代码 ```fa[i] = get_next(seed) % (i - 1) + 1``` 我们知道，$fa_i$ 的值是一定**小于** $i$ 的，所以我们一定**已经计算过** $fa_i$ 的有趣程度 $k_{fa_i}$。所以做完第 $i$ 道题的有趣程度 $k_i$ 的最大值是 $\min(k_{fa_i}, a_i)$。

```cpp
k[i] = min(k[fa[i]], a[i]);
```
而结果就是所有 $k_i$ 之和（注意 $k_1$ 为 $a_1$）。

```cpp
res = res + k[i];
```

注意初始化：

```cpp
res = k[1] = a[1];
```

完整 $Code$：

```cpp
/*
 * Author: guzheran @YYXX
 */

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef long double ldb;
typedef vector<int> vi;
typedef pair<int, int> pii;

#define fi first
#define se second
#define rg register
#define mp make_pair
#define pb push_back
#define pf push_front

#define rep(i, s, t) for (int i = s; i <= t; i++)
#define per(i, s, t) for (int i = t; i >= s; i--)

/* template ends here */

const int MAXN = 1e7 + 9;

typedef unsigned int uint;

ll res = 0;
uint n, seed, a[MAXN], fa[MAXN];
uint k[MAXN]; // after do the i-th problem, the maximum that k can change to. 

inline uint get_next(uint &seed){
	seed ^= seed << 13;
	seed ^= seed >> 17;
	seed ^= seed << 5;
	return seed;
}

int main () {
	
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	cin >> n >> seed;
	
	for (register int i = 1; i <= n; i++){
		a[i] = get_next(seed);
	}
	
	for (register int i = 2; i <= n; i++){
		fa[i] = get_next(seed) % (i - 1) + 1;
	}
	
	res = k[1] = a[1];
	
	for (register int i = 2; i <= n; i++) {
		k[i] = min(k[fa[i]], a[i]);
		res = res + k[i];
	}
	
	cout << res << '\n';
	
	return 0;
	
}
```

---

## 作者：what_else (赞：1)

### 题目大意

- 有 $n$ 道题， $n-1$ 条关系，每道题有一个权值 $a_i$，以及一个指数 $k$。
- 做一道题前必须做完第 $fa_i$ 题，做完该题后，$k=\min(k,a_i)$。
- 求出做完每题的 $k$ 的总和。

### 题目思路

$n-1$ 条关系，$n$ 个结点，很容易想到，这是一棵**树**。

样例：

![](https://cdn.luogu.com.cn/upload/image_hosting/3kmwsaci.png)

我们从 $1$ 号结点开始做题，让后向下遍历，寻找一个合适的结点后，以此类推向下，直到跑完所有结点。

那什么是最优的选择呢？

为了使向下的 $k$ 最大，不难发现，可以先做 $a_i$ 较大的题，这样就能让答案尽量的大。

那么思路大致是：

- 寻找可到达的最大 $a_i$ 结点。
- 删掉其，更新 $k$ 和答案。
- 将删掉结点的子结点视为可到达，重复直到所有结点被删。

这样，如果暴力查找最大值，时间复杂度 $O(n^2)$，用堆的话，就可以达到 $O(n\log{n})$。然而，$n$ 最大可达到 $10^7$，所以这个办法欠妥。最多拿到 $50$ 分。

```cpp

#include<iostream>
#include<cstdio>
#include<bits/stdc++.h>
#include<vector>
using namespace std;
typedef	unsigned int uint;
#define MAXN 10000010
long long t,n,uke;
long long a[MAXN];
unsigned seed;
long long ans,k=LONG_LONG_MAX-2;
vector <int> p[MAXN];
struct sp{
	int nod;
	long long num;
}out[MAXN*2+1];
inline uint get_next(uint &seed){
	seed ^= seed << 13;
	seed ^= seed >> 17;
	seed ^= seed << 5;
	return seed;
}

void modify(int x){
	if(x==1 || (out[x].num < out[(x>>1)].num))return;
	swap(out[x],out[(x>>1)]);
	modify((x>>1));
}
void push(long long x,int v){
	t++;
	out[t].num=x;
	out[t].nod=v;
	modify(t);
}
void repair(int x){
	if((x<<1) > t)return;
	int tar = (x<<1);
	if((x<<1)+1 <= t)
	tar = (out[(x<<1)].num > out[(x<<1)+1].num) ? (x<<1) : (x<<1)+1;
	if(out[x].num < out[tar].num){
		swap(out[x],out[tar]);
		repair(tar);
	} 
}
void pop(){
	swap(out[1],out[t]);
	t--;
	repair(1);
}
int main(){
	cin>>n>>seed;
	uke=n;
	for (register int i = 1; i <= n; i++)
	a[i] = get_next(seed);
	for (register int i = 2; i <= n; i++)
	p[get_next(seed) % (i - 1) + 1].push_back(i);
	push(a[1],1);
	while(uke){
		k=min(k,out[1].num);
		ans+=k;
		int szp=out[1].nod;
		pop();
		for(int i=0,sz=p[szp].size();i<sz;i++)
			push(a[p[szp][i]],p[szp][i]);
		uke--;
	}
	cout<<ans;
}

```

接着，研究这棵树的 **特别性质**。

性质 $1$:

在做子结点题目时的 $k$，一定不大于父结点的 $k$。

证明：

因为有 $k=\min(k,a_i)$，使得树从上到下， $k$ **单调不升**。

性质 $2$:

除根结点外，每个结点对答案贡献为 $\min(a_i,$ 做父结点题目时的 $k$ $)$。

证明：

由性质 $1$，如果用先前的策略，请读者自行完成证明。

有这两个性质，就易得出正解。

CODE：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef unsigned int uint;
long long ans,a[10000010];
int n;
unsigned seed;
inline uint get_next(uint &seed){
	seed ^= seed << 13;
	seed ^= seed >> 17;
	seed ^= seed << 5;
	return seed;
}
int main(){
    cin>>n>>seed;
	for (register int i = 1; i <= n; i++){
		a[i] = get_next(seed);
	}
	ans+=a[1];
	for (register int i = 2; i <= n; i++){
	    a[i]=min(a[i],a[get_next(seed) % (i - 1) + 1]);
	    ans+=a[i];
	}
	
	cout<<ans;
}
```





---

## 作者：xiaohaoaibiancheng66 (赞：1)

# 思路
### 1.解法
以 $end_i$ 为做到第 $i$ 题时的最大的高兴程度，则答案为 $\sum_{i=1}^{n} end_i$。

那么现在就要使 $end_i$ 最大。

由于 $end_i$ 不可能超过 $a_i$，所以 $end_i \leq a_i$；

又因要**先做 $fa_i$ 题再做 $i$ 题**，所以 $end_i \leq end_{fa_i}$。

所以这样就可以得到一个递推式：$end_i=\min(a_i,end_{fa_i})$。其中，初始值为 $end_1=a_1$。
### 2.证明
试想，有没有一种情况：

解决这个问题，就需要用到数据结构的帮助。把 $i$ 作为节点编号，把 $fa_i$ 看成 $i$ 的父节点，把 $end_i$ 看成 $i$ 的权值，把 $1$ 号节点作为树根，这就是一棵**父亲 $\leq$ 孩子的树**！

做题的过程可以理解为：做了一道题等于删除此节点。由于做的题只能为根结点。根结点被删除后可以用类似堆的方法选最大的孩子当树根。

这样的方法可以造出一条顺序可以实现在做 $i$ 题是已经把 $end_j$ 比 $end_i$ 大的 $j$ 都做完了，而 $end_j$ 比 $end_i$ 小的 $j$ 一题都没做。

所以，不存在“做第 $i$ 题时的高兴程度小于 $end_i$”这种情况。
# AC code
```cpp
#include<bits/stdc++.h>
using namespace std;

typedef unsigned int uint;

inline uint get_next(uint &seed){
	seed ^= seed << 13;
	seed ^= seed >> 17;
	seed ^= seed << 5;
	return seed;
}

uint n,a[10000000+10],fa[10000000+10];
long long ans=0;
uint seed;

int main(){
	cin>>n>>seed;
	for (register int i = 1; i <= n; i++){
		a[i] = get_next(seed);
	}
	ans=a[1];
	for (register int i = 2; i <= n; i++){
		fa[i] = get_next(seed) % (i - 1) + 1;
		a[i]=min(a[i],a[fa[i]]);//把a[i]作为end[i]，省空间。
		ans+=a[i];
	}
	cout<<ans;
	return 0;
} 
```


---

## 作者：Leasier (赞：1)

### Subtask $1$
前置芝士：[拓扑排序](https://oi-wiki.org/graph/topo/)

显然可以发现题目中给定的做题顺序构成了一棵以 $1$ 为根的**树**，而一道新的题目可以被做必须满足其父亲节点的题目已经被做。

看上去有些像拓扑排序。但是即使如此，我们也可能会得到多个可能的顺序。

直接暴力枚举所有可能的顺序即可。时间复杂度为 $O(n \times n!)$。
### Subtask $2$
如果不直接枚举所有可能的顺序怎么办呢？观察高兴程度的变化式可知：**在多道题目都可做的情况下，先做更有趣的题显然更优**。

证明：假设我们在某一步选择了一个小于当前可选者中最大者 $a_u$ 的可选者 $a_v$，且选择 $a_v$ 优于 $a_u$。设这一步之前还没有选择的点的集合为 $S$（注意：我们这里提到的集合都是可重的），如果选择 $a_u$，此时集合 $S$ 可以等效于 $S' = \{x \in S \mid \min(x, a_u)\}$；如果选择 $a_v$，此时集合 $S$ 可以等效于 $S'' = \{x \in S \mid \min(x, a_v)\}$。由于 $a_u > a_v$，将 $S', S''$ 分别从小到大排列后 $S'$ 中的每一项对应不小于 $S''$ 中对应的项，于是选择 $S'$ 优于 $S''$。这与选择 $a_v$ 优于 $a_u$ 的前提矛盾。

于是我们暴力循环 $n$ 次，维护一个 vector，添加元素时 push_back 到其尾部，查询最大值时暴力，删除元素时 erase 最大值所在位置即可。时间复杂度为 $O(n^2)$。
### Subtask $3$
前置芝士：[优先队列](https://oi-wiki.org/lang/csl/container-adapter/#_13)

实际上，我们并不需要每次都暴力排序。

考虑队列优化拓扑排序的做法：用普通的队列维护当前入度为 $0$ 的节点并每次从队头取出元素。

考虑到我们在 Subtask $2$ 中提到的拓扑序需要满足一定的排序规则，我们显然可以把它丢进一个优先队列来维护。

时间复杂度为 $O(n \log n)$。
### Subtask $4$
考虑到一个 $a_u$ 最多只可能带来 $a'_u = \displaystyle\min_{v \in ancestor_u} a_v$ 的贡献，则我们显然可以把 $a'_u$ 当做 $a_u$ 来计算。由于 $\forall 2 \leq i \leq n$，$a'_u \leq a'_{fa_u}$，所以如果我们不考虑拓扑序中祖先后代带来的选择限制，依次选择最大的 $a'_u$ 可以被看做遵守了拓扑序的限制。

于是我们建出有根树的结构，求出 $a'_u$ 并求和即可。时间复杂度为 $O(n)$。

代码：
```cpp
#include <stdio.h>

typedef unsigned int uint;
typedef long long ll;

uint a[10000007];

inline uint get_next(uint &seed){
	seed ^= seed << 13;
	seed ^= seed >> 17;
	seed ^= seed << 5;
	return seed;
}

inline uint min(uint a, uint b){
	return a < b ? a : b;
}

int main(){
	int n;
	uint seed;
	ll ans = 0;
	scanf("%d %u", &n, &seed);
	for (register int i = 1; i <= n; i++){
		a[i] = get_next(seed);
	}
	for (register int i = 2; i <= n; i++){
		uint fa = get_next(seed) % (i - 1) + 1;
		a[i] = min(a[i], a[fa]);
	}
	for (register int i = 1; i <= n; i++){
		ans += a[i];
	}
	printf("%lld", ans);
	return 0;
}
```

---

## 作者：zhijinyu (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P8411)

### 题意简述：

有 $n$ 道题，对于每道题 $i$ 的高兴程度为 $a_i$ ，必须先做第 $fa_i$ 道题才能做。

走到每点 $i$ 时高兴程度会变成现在高兴程度与 $a_i$的最小值。开始时高兴程度为无穷。

求做完每道题后高兴程度之和的最大值。

### 50分做法：

#### 贪心，用优先队列维护。

走到每个节点就计答案，把字节点放进优先队列，先走开心值最大的那个节点。

但是……

50分做法的复杂度为：$O(n \log n)$, $n \le 10^7$,肯定会  TLE。

所以这不是正解，就不贴代码了。

### 接下来看正解：

当走到每一个点时，最大的高兴程度为根节点到它路径上最小节点，并不会被其他点影响。

答案为每个点答案的总和。

$Code:$

```
#include<bits/stdc++.h>
using namespace std;
typedef unsigned int uint;
uint n,seed,a[10000010],fa[10000010];//unsigned int型
inline uint get_next(uint &seed){
    seed ^= seed << 13;
    seed ^= seed >> 17;
    seed ^= seed << 5;
    return seed;
}
int main()
{
    cin>>n>>seed;
    for (register int i = 1; i <= n; i++){
        a[i] = get_next(seed);
    }
    for (register int i = 2; i <= n; i++){
        fa[i] = get_next(seed) % (i - 1) + 1;
    }
    long long ans = a[1]; //答案要用long long 型
    for (register int i = 2; i <= n; i++) a[i]=min(a[fa[i]],a[i]) , ans += a[i];
    cout<<ans;
    return 0;
}
```


---

## 作者：Composite_Function (赞：0)

# 思路

## 10 pts

不难想到使用 dfs 可以得到暴力分。

时间复杂度 $O(n!)$，但个人认为实际的运行结果应该更快一些。

这种算法可得 $10$ 分。

关键代码

```cpp
	for(int i = 1; i <= n; ++i)
		if(vis[i] == false && vis[fa[i]] == true)
			vis[i] = true, dfs(tmp + 1, min(k, a[i]), num + k), vis[i] = false;
```

------------

## 50 pts

因为必须先做 $fa_i$ 题后才能做 $a_i$ 题。

所以可以把题目看成一颗树了，其中父节点为 $fa_i$，子节点为 $a_i$。

写个树状数组即可。时间复杂度 $O(n\log n)$。

这种算法可得 $50$ 分。

------------

## 100 pts 正解

我们可以看到数据范围 $n \leq 1e7$，立即明白正解得时间复杂度必然是 $O(n)$。

再看看题面，可以发现一个特殊性质 $\forall ~~ 2 \leq i \leq n ~~ 1 \leq i \leq n$。

于是，就可以在 $\text{50pts}$ 算法上进一步优化。很容易看出，这个性质保证了在这棵树上除了根节点，其他节点有且仅有一个父节点。因此可以得出 $\min(a_i, k)$ 的取值只关乎于 $a_{fa_i}$！

或者用另一个角度说明，在顺着扫数组 $a$ 以找出最大值时，$fa_i$ 一定比 $a_i$ 先判断到，这样就不关乎于遍历顺序了。状态转移方程也很好推，即 $f_i = \min(a_i, f_{fa_i})$。

不管采用哪一种方法，都可以得到同样的效果：时间复杂度与空间复杂度均为 $O(n)$，均可通过此题。

------------

# 代码

这里说一下一个坑点：答案是要用 `unsigned long long` 类型的，然而数据只能用 `unsigned int` 类型的，不然就会错了。

代码还是很短的。

```cpp

#include <bits/stdc++.h>
using namespace std;
#define int unsigned int
#define ll unsigned long long
const int N = 1e7 + 10;
int n, seed, a[N], fa[N];
ll ans;
int get_next(int &seed)
{
	seed ^= seed << 13;
	seed ^= seed >> 17;
	seed ^= seed << 5;
	return seed;
}
signed main()
{
    cin >> n >> seed;
	for (int i = 1; i <= n; ++i)
        a[i] = get_next(seed);
	for (int i = 2; i <= n; ++i)
        fa[i] = get_next(seed) % (i-1) + 1;
    ans = a[1];
	for (int i = 2; i <= n; ++i)
        a[i] = min(a[i], a[fa[i]]), ans += a[i];
	cout << ans << endl;
    return 0;
}
```


---

## 作者：dingshengyang (赞：0)

~~怎么还可以水题解。~~

废话少说，来。

容易发现，题目之间呈树状关系：

假设 $a_i=5,4,3,2,1(n=5)$。

然后设 $fa_i=/,1,1,3,2$（$1$ 号没有嘛）。


RT：

~~图丑勿喷。~~

![](https://cdn.luogu.com.cn/upload/image_hosting/9rmbcnqe.png)

然后……

其实感觉这像树形 DP。

你要走到第 $i$ 点，必须从 $1$（树根）开始，老老实实走下来嘛。

你要走到第 $i$ 点，必须从 $fa_i$ 走下来啊！

然后……

$f_i = \min(a {\footnotesize_{fa_i}})$。

特别情况：$f_1=a_1$。

令答案为 $ans$。

$ans=\sum^{n}_{1}f_i$。

不就完了吗！

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef unsigned int uint;
typedef unsigned long long LL; 
const int N = 1e7+5;
uint a[N],fa[N],n,seed; 
inline uint get_next(uint &seed){
	seed ^= seed << 13;
	seed ^= seed >> 17;
	seed ^= seed << 5;
	return seed;
}

int init(){
	// ...
	for (register int i = 1; i <= n; i++){
		a[i] = get_next(seed);
	}
	for (register int i = 2; i <= n; i++){
		fa[i] = get_next(seed) % (i - 1) + 1;
	}
	// ...
	return 0;
}
int main() 
{
	cin >> n >> seed;
	init();
	LL ans = a[1],happy = a[1];
	for(int i = 2;i <= n;i ++){
		if(a[i] > a[fa[i]]){
			a[i] = a[fa[i]];
		}
		ans += a[i];
	}
	cout << ans << endl;
	return 0;
}

```

---

## 作者：Jasper08 (赞：0)

### 【题目描述】

有 $n$ 道题，第 $i$ 道题的有趣程度是 $a_i$ . $\forall 2\leq i\leq n$ ,  **必须** 要先做第 $fa_i$ 道题才能做第 $i$ 道题，且 $1\leq fa_i< i$ . 小 L 初始时的开心程度为无穷大，如果他做第 $i$ 道题之前的开心程度为 $k$ , 那么他做完第 $i$ 道题后的开心程度就变为 $\min(k,a_i)$ . 

现在，小 L 想请你求出在他 **必须先做第 $1$ 道题且不能重复做题的情况下** ，他在做题过程中每做完一道题的开心程度之和。

### 【题目分析】

看到题目 $500\text{ms}$ 的时间限制就知道本题肯定要用一种神奇的算法来秒杀。定义 $h_i$ 表示小 L 做完第 $i$ 道后的开心程度。可以得到结论 $h_i=\min(a_i,h_{fa_i})$ .

证明：因为小 L 要先做第 $fa_i$ 题再做第 $i$ 题，根据题目中的定义，可知做完第 $i$ 道题时的开心程度最大为 $\min(a_i,h_{fa_i})$ .

因为题目保证 $fa_i<i$ ，所以我们可以在生成数据的同时计算 $h_i$ .

### 【代码】

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

typedef unsigned int uint;

#define int __int128 //防止爆long long

const int N = 1e7 + 10;

uint a[N], fa[N];

inline uint get_next(uint &seed){
	seed ^= seed << 13;
	seed ^= seed >> 17;
	seed ^= seed << 5;
	return seed;
}

void write(int x) { //__int128需要使用快输
	if (x < 0) {
		putchar('-');
		x = -x;
	}
	
	int y = 10, len = 1;
	while (y <= x) {
		y *= 10;
		len ++;
	}
	while (len --) {
		y /= 10;
		putchar(x/y + 48);
		x %= y;
	}
}

signed main(){
	uint n, seed;
	cin >> n >> seed;
	int sum = 0;
	for (register int i = 1; i <= n; i++){
		a[i] = get_next(seed);
	}
	for (register int i = 2; i <= n; i++){
		fa[i] = get_next(seed) % (i - 1) + 1;
		a[i] = min(a[i], a[fa[i]]); //每次统计h[i]
	}
	for (register int i = 1; i <= n; i++)
		sum += min(a[i], a[1]); //因为先做第1题，所以要再取一次min
	write(sum);
	return 0;
}
```

---

## 作者：xinggancaixukun (赞：0)

## 思路

题面比较绕。其实可以看做 $fa_i$ 是 $i$ 的父节点，$1$ 是根节点，题目其实就转化为求每一个点到 1 的路径中所有点的点权最小值之和。

因此，我们直接想出了最基础的 dfs：

```cpp
uint a[MAXN],ans[MAXN];
long long Tot;
vector<int> E[MAXN];
void dfs(int u)
{
	Tot+=ans[u];
	for(register int i=0;i<E[u].size();i++)
	{
		int v=E[u][i];
		ans[v]=ans[u]>a[v]?a[v]:ans[u];
		dfs(v);
	}
}
```

最后的答案就是 ```Tot```。当然，这样做被卡了。毕竟这个做法的常数比较大，我们再次寻找题目的特点，试一下优化掉 dfs 转而用循环求。

我们发现，$1 \leq fa_i < i$。因此，我们处理到 $i$ 的时候，它的 $fa_i$ 一定都处理过了。所以我们考虑把 dfs 转化成为逐步的递推。令 $ans_i$ 表示从 $1$ 到 $i$ 中路径上点权的最小值。和 dfs 一样，$ans_i = \min(ans_i,ans_{fa_i})$。但是由于题目的特点，我们从 $1$ 到 $n$ 循环一次，每次进行递推即可。

记得初始化：$ans_1 = a_1$（显然的。）

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN=10000005;
typedef unsigned int uint;
inline uint get_next(uint &seed)
{
	seed^=seed<<13;
	seed^=seed>>17;
	seed^=seed<<5;
	return seed;
}
uint a[MAXN],fa[MAXN],ans[MAXN];
long long Tot;
int main()
{
	int n; uint seed; cin>>n>>seed;
	for(register int i=1;i<=n;i++) a[i]=get_next(seed);
	for(register int i=2;i<=n;i++) fa[i]=get_next(seed)%(i-1)+1;
	Tot+=a[1]; ans[1]=a[1]; // 初始化
	for(register int i=2;i<=n;i++)
	{
		ans[i]=min(a[i],ans[fa[i]]); // 递推
		Tot+=(long long)ans[i];
	}
	cout<<Tot;
	return 0;
}
```

---

## 作者：y_kx_b (赞：0)

本以为这题和几天前的 CCC 红题一样太简单不能交题解，后来发现这是月赛题。。。

---
题意
---
（首先题目与题目之间构成树的关系，因为 $n$ 个点只有 $n-1$ 条边（$i$ 与 $fa_i$ 之间建边））

定义一个节点的高兴程度为该节点到根的链上的点的点权的最小值，求所有点的高兴程度之和。

Sol.
---
这是一道树上乱搞题（确信）
### 常规做法（[会被卡常](https://www.luogu.com.cn/discuss/449571)）
---

先遍历一遍这个树（dfs 或 bfs 均可），对于搜到的每个节点 $i$ 有：
$$
ans_i=\min(ans_{fa_i},a_i) \ (i\not=1)
$$
（$ans_i$ 表示节点 $i$ 的高兴程度）

因为是搜索，所以对于搜到的每个节点 $i$，$ans_{fa_i}$ 肯定被计算出来了。

最后统计，所有点的 $ans$ 一加就行。（统计记得开 long long）

---
现在证明上面的递推方程是正确的：即对于上面计算出来的高兴程度值，总有一种做题方法与之契合。（上面计算出来的高兴程度值为最佳答案：易证。）

对于兄弟节点 $i$ 和 $j$，不妨设 $ans_i\leqslant ans_j$，则先做 $j$ 题再做 $i$ 题，就可以各自达到 $ans$ 值。

```cpp
#define int uint
int a[N],fa[N],to[N<<1],ne[N<<1],head[N],idx=0,ans[N];
void add(int u,int v){
	ne[++idx]=head[u],to[idx]=v,head[u]=idx;
}
void dfs(int cur){
	for(int i=head[cur];i;i=ne[i])
		ans[to[i]]=min(ans[cur],a[to[i]]),dfs(to[i]);
}
void major(){
	int n=read();
	uint seed;scanf("%u",&seed);
	for (register int i = 1; i <= n; i++){
		a[i] = data::get_next(seed);
	}
	for (register int i = 2; i <= n; i++){
		fa[i] = data::get_next(seed) % (i - 1) + 1;
		add(fa[i],i);
	}
	dfs(1);
	long long sum=0;
	for(int i=1;i<=n;i++)
		sum+=ans[i];
	printf("%lld",sum);
}
```
### 考场 ~~（指中考考场）~~ 做法
---
和上面基本一样，但是 ~~不用建树，所以时间会少很多~~

注意到
$$
ans_i=\min(ans_{fa_i},a_i) \ (i\not=1)
$$
节点 $i$ 的高兴程度只与节点 $fa_i$ 的高兴程度有关，与兄弟节点无关

那么我们可以不按照树形搜，随便怎么都可以。
我这里是
```cpp
#define int uint
int a[N],fa[N],ans[N];
void dfs(int cur){
//	if(ans[fa[cur]]==-1)
//		dfs(fa[cur]);
	ans[cur]=min(ans[fa[cur]],a[cur]);
}
void major(){
//	memset(ans,-1,sizeof ans);
	int n=read();
	uint seed;scanf("%u",&seed);
	for (register int i = 1; i <= n; i++){
		a[i] = data::get_next(seed);
	}
	for (register int i = 2; i <= n; i++){
		fa[i] = data::get_next(seed) % (i - 1) + 1;
	}
	ans[1]=a[1];
	long long ret=0;
	for(int i=2;i<=n;i++)
		dfs(i);
	for(int i=1;i<=n;i++)
		ret+=ans[i];
	printf("%lld",ret);
}
```
因为是顺着搜的，对于搜到的每个节点 $i$，$ans_{fa_i}$ 肯定被计算出来了（因为 $fa_i< i$），所以注释部分可以去掉。

如果乱搜的话（[当然会被卡](https://www.luogu.com.cn/record/77696185)），注释部分得加上（有可能搜到的节点的父节点 $ans$ 未计算）

---
_Thanks for reading!_

_Having fun coding!_

---

## 作者：Polaris_Australis_ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P8411)

暴力做法比较简单，这里直接说正解了。

考虑选择一个点的最大贡献：即在选择这个点之前必须要选择的点中的点权最小值与当前点的点权取 $\min$，维护前者即可，设前者为 $limit_i$，则转移方程为：

$$limit_i=min(limit_{fa_i},a_i)$$

这样就可以在线性时间复杂度内求出答案了。

代码：

```
// Problem: P8411 「SvR-1」Problem
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P8411
// Memory Limit: 512 MB
// Time Limit: 500 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
#define miny(x, y) x = min(x, y)
#define maxy(x, y) x = max(x, y)
#define uint unsigned int
#define lowbit(x) ((x) & (-(x)))
#define fu(i, l, r) for (int i = (l); i <= (r); ++i)
#define fd(i, r, l) for (int i = (r); i >= (l); --i)
#define mem(x, y) memset(x, y, sizeof(x))
#define file(x)                 \
  freopen(x ".in", "r", stdin); \
  freopen(x ".out", "w", stdout);
#define mod 998244353
#ifdef int
#define inf 0x3f3f3f3f3f3f3f3f
#else
#define inf 0x3f3f3f3f
#endif
#define inv(x) qp(x, mod - 2)
using namespace std;
namespace Std {
template <typename tp>
void read(tp &x) {
  x = 0;
  int y = 1;
  char c = getchar();
  while (c < '0' || c > '9') {
    if (c == '-') y = -1;
    c = getchar();
  }
  while (c >= '0' && c <= '9') {
    x = (x << 1) + (x << 3) + (c & 15);
    c = getchar();
  }
  x *= y;
}
template <typename tp>
void write(tp x) {
  if (x < 0) {
    putchar('-');
    write(-x);
    return;
  }
  if (x > 9) write(x / 10);
  putchar((x % 10) | 48);
}
int qp(int x, int y) {
  int cmp = 1;
  while (y) {
    if (y & 1) (cmp *= x) %= mod;
    (x *= x) %= mod;
    y >>= 1;
  }
  return cmp;
}
uint seed;
inline uint get_next() {
  seed ^= seed << 13;
  seed ^= seed >> 17;
  seed ^= seed << 5;
  return seed;
}
uint n, minn[10000010], aa[10000010];
signed main() {
  read(n);
  read(seed);
  uint a;
  for (uint i = 1; i <= n; ++i) {
    aa[i] = get_next();
  }
  minn[1] = aa[1];
  long long ans = aa[1];
  for (uint i = 2; i <= n; i++) {
    a = get_next() % (i - 1) + 1;
    minn[i] = min(minn[a], aa[i]);
    ans += minn[i];
  }
  write(ans);
  return 0;
}
}  // namespace Std
signed main() { return Std::main(); }
```


---

