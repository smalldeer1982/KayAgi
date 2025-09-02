# [USACO13DEC] The Bessie Shuffle S

## 题目描述

Bessie is practicing her card tricks.  She has already mastered the Bessie- shuffle -- a shuffle on M (2 <= M <= 100,000) cards that reorganizes the cards so the i-th card from the top is now the P[i]-th card from the top.

Now Bessie is practicing shuffles on larger decks.  She has a deck of N cards (M <= N <= 100,000) conveniently labeled 1 to N.  She shuffles this deck by taking the first M cards and performing the Bessie-shuffle on them, placing the shuffled cards back on top of the deck.  She then removes the top card from the deck and places it face down.  She repeats this process, placing the top cards successively on top of each other, until she is out of cards.  When Bessie has less than M cards left, she no longer performs the Bessie-shuffle, but continues to place the top card on top of the others.

Bessie knows that the deck initially started in sorted order, with 1 on top, 2 next, and N on the bottom.  Given the description of the Bessie-shuffle, help Bessie compute which cards end up located at Q different specified positions (1 <= Q <= N, Q <= 5,000) in the deck.

贝西有一种独门的洗牌方法，称为 A 类洗牌法；

A 类洗牌法的具体过程：将一堆共 $M$（$2 \le M \le 10 ^ 5$）张从上到下编号 $1, 2, \cdots, M$ 的纸牌，从上到下第 $i$ 张牌洗到位置 $p _ i$。

例如，$M=3，p = \{3, 1, 2\}$，则执行一次 A 类洗牌法后，从上到下将变为 $2, 3, 1$，即牌 $1$ 放到位置 $3$，牌 $2$ 放到位置 $1$，牌 $3$ 放到位置 $2$。


贝西现在要练习另外一种洗牌方法，称为 B 类洗牌法。


B 类洗牌法的具体过程： 

有一堆 $N$（$M \le N \le 10 ^ 5$）张编号为 $1, 2, \cdots, N$ 的牌，并按从上到下 $1$ 到 $N$ 的顺序堆放。另有一个牌堆用来辅助洗牌，称为临时堆，开始时为空。

1. 将最上面 $M$ 张牌进行一次 A 类洗牌法；
2. 将最上面的一张牌放到临时堆的最上方；
3. 重复前两个操作，直到原先的堆没有牌为止。


以上过程中，当原先堆的牌不足 $M$ 张的时候，将不进行 A 类洗牌法，而是将最上面的牌依次放到临时堆上。


给定 $N, M$ 和排列 $p$。现在有 $Q$（$1 \le Q \le \min(N, 5000)$）个询问，请求出对其做一次 B 类洗牌法后临时堆中 $q _ i$ 位置上的牌的编号。


## 说明/提示

Bessie has a deck of 5 cards initially ordered as [1, 2, 3, 4, 5].  Her shuffle is on 3 cards and has the effect of moving the top card to the bottom.  There are 5 queries querying each position in the deck.


The shuffle proceeds as:

```cpp
[1, 2, 3, 4, 5] -> [2, 3, 1, 4, 5] (put 2 face down) 
[3, 1, 4, 5] -> [1, 4, 3, 5] (put 1 face down) 
[4, 3, 5] -> [3, 5, 4] (put 3 face down) 
[5, 4] (put 5 face down) 
[4] (put 4 face down) 
```
This produces the final order of [4, 5, 3, 1, 2]

## 样例 #1

### 输入

```
5 3 5 
3 
1 
2 
1 
2 
3 
4 
5 
```

### 输出

```
4 
5 
3 
1 
2 
```

# 题解

## 作者：HyB_Capricornus (赞：7)

~~本蒟蒻居然 AC 了紫题~~

本蒟蒻就把自己的思考过程写一下：

首先，本人想到了如果题面改为如下：

有 $m$ 张牌，进行 $n$ 次贝西洗牌A，求最后牌的顺序。

对于这个问题，我们可以很容易想到[倍增](https://oi-wiki.org/basic/binary-lifting/)。

### 倍增预处理

我们定义 $f_{i,j}$ 为从第 $i$ 次变换开始变换 $2^j$ 的序列，并且可以用求 LCA 的方法知道倍增预处理方法：

$$f_{i,j}=f_{f_{i,j-1},j-1},$$

### 套倍增

但是如果换为题面，我们需要在每次交换时取出第一个，这个无法预处理，我们就无法用二进制拆分 $O(log_2n)$ 的解决，退化成了 $O(n)$ 了。

但是我们怎么把原始序列往里套呢？

下面给出我的方法，强烈建议先自行思考再阅读本文。

若还需要倍增，就需要通过长度为 $m$ 的 $p$ 序列构造长度为 $n$ 的 $q$ 序列，**那么我们可以~~用时3天~~想到将已经取出的元素放置序列末尾**。

我们可以如此构造 $q$ 序列：

- 对于 $i \in [1,m]$，$q_i=p_i-1$，其中 $p_i=1$ 的移到队尾：$n$。

- 对于 $i \in [m+1,n]$，我们仅需向前挪，及 $p_i=i-1$。

### [代码](https://www.luogu.com.cn/paste/83fwktli)

本人给出本人被卡的地方，警示后人 ~~(给个赞呗)~~。

1. 请注意本题是一个牌堆，相当于一个栈，所以牌堆最后的顺序是反着的。

2. 建议先将临时牌堆的数据存储下来，再 $O(1)$ 输出。 ~~(本人不知为何 WA)~~

3. 注意题目中不足 $m$ 张时要依次放到牌堆上。~~(本人被卡无数次)~~

---

## 作者：analysis (赞：6)

做题，首先要思考朴素做法及其时空复杂度（一眼题除外）。

暴力的做，每次使用 $O(n)$ 处理，一共处理 $n-(m-1)$ 次。

总时间复杂度

$$
O((n-(m-1))n) = O(n^2-nm+n)
$$

显然，$m$ 越小时间复杂度越高，最高接近 $O(n^2)$。

如果特判 $m$ 特别小的情况是没有用的，$m$要到达较大的值时才对结果有优化。

所以，朴素做法的时间复杂度可以直接视作 $O(n^2)$。

接下来想优化。

想要过了这道题，至少需要 $O(n\log n)$ 的时间复杂度。

优化，我们可以从复杂度中的两个 $n$ 入手。

先想想两个 $n$ 分别代表的什么意义吧。

一个 $n$，表示状态之间的转移。

一个 $n$，表示转移的状态数。

由于需要求得最后排列中的所有值，第一个 $n$ 难以优化。

考虑优化转移。

这里，许久之前做的 [[CSP-S 2022] 数据传输](https://www.luogu.com.cn/problem/P8820) 给我了一些思路（我也不知道为什么忽然想起来了）。

我们把一个个状态转移称之为线性转移，他无疑是低效的。

我们可以把线性转移转变为倍增转移，从而优化时间复杂度。

那么很容易写出式子：

$$
f_{i,j} = f_{f_{i,j-1},j-1},f_{i,0} = p_i
$$

这道题还需要你取出堆头，但由于倍增推导的性质，你不能“拿出来”（无论哪里，你都要使用 $f$ 转移，如果你拿出来了，倍增就要标记第几次推导，也就失去了倍增的作用）。

所以我们要考虑把它放在哪里（一个较为特殊的地方）。

我的解决方案是放到本堆尾部（堆位不受操作影响，且没有拿出来）。

如此，我们可以改一下初始化：

- 当 $i \leq m$ 时：

如果 $p_i = 1$

$$
f_{i,0} = n
$$

如果 $p_i \not= 1$

$$
f_{i,0} = p_i-1
$$

- 当 $i > m$ 时：

$$
f_{i,0}=i-1
$$

然后就可以切掉这道题了。

```cpp
#include<bits/stdc++.h>
const int maxn = 1e5;
using namespace std;
int n,m,Q;
int p[maxn + 5];
int f[maxn + 5][35];
vector<int> q[35];
int k;
int main()
{
    cin>>n>>m>>Q;
    for(int i=1;i<=m;i++)
    {
        cin>>p[i];
    }
    for(int i=1;i<=n;i++)
    {
        if(i<=m)
        {
            if(p[i] == 1)f[i][0] = n;
            else f[i][0] = p[i] - 1;
        }
        else
        {
            f[i][0] = i-1;
        }
    }
    for(int j=1;j<=30;j++)
    {
        for(int i=1;i<=n;i++)
        {
            f[i][j] = f[f[i][j-1]][j-1];
        }
    }
    q[++k].resize(n + 5);
    for(int i=1;i<=n;i++)q[k][i] = i;
    int num = n - (m-1);
    for(int j=30;j>=0;j--)
    {
        if((1<<j) <= num)
        {
            q[++k].resize(n + 5);
            for(int i=1;i<=n;i++)
            {
                q[k][f[i][j]] = q[k-1][i];
            }
            num -= (1<<j);
        }
    }
    while(Q--)
    {
        int x;
        cin>>x;
        x = n-x+1;
        int pos = (m + x - 1)>n?(m + x - 1)-n:(m + x - 1);
        cout<<q[k][pos]<<endl;
    }
    return 0;
}
```

---

## 作者：WerChange (赞：4)

提供一种思路，可以做到 $O(n)$。

`update 2023.08.13` 修改了 Latex 滥用问题。

`update 2023.08.12` 修改了空格问题。

`update 2023.08.11` 修改了空格问题。

`update 2023.07.29` 完工，期望无 bug （暑假快乐吖）

`update 2023.07.27` ~~（要原题检测了，先占个坑，有时间再补）~~
## 原题大意
> 有 $n$ 张牌，每次取出 $m \;(m<n)$ 张牌进行置换操作。操作完一轮后会出第 $1$ 张牌，并再加入 $1$ 张牌继续进行新一轮的置换操作。

> 最后无法再进行操作时，则按现顺序不断出牌。
>
> 求倒数第 $x$ 次出牌的原编号是多少。

## 暴力解法
如果没有思考直接开码的话，得到的暴力代码是 $O(nq)$ 的。这个时间复杂度 2013 年的老机器是过不了的。

预计： 73pts
## 倍增解法
这是正解的一种。通过倍增优化后，时间复杂度是 $O(n \log n)$。

此处不展开讲倍增解法，原因有三：
1. 本题已有大量倍增解法的题解。
2. 虽然是 $O(n \log n)$，可以通过本题，但还不是最优解，本帖主要讲最优解 $O(n)$ 做法。
3. ~~本人只会**不熟练**的运用倍增求 LCA 问题（虽然现在还是用树链剖分求 LCA ），倍增还能优化是我听教练讲解后才知道的。~~

预计： 100pts
## $O(n)$ 解法
**[warning]**： 前方请准备好草稿纸，有演算过程……

## Part 0 思考性质
首先我们考虑普通的置换。

例如下面的这个情景：
> 有 5 个学生要换位置。

> 原位置：
> $$1\;2\;3\;4\;5$$
> 目标位置：
> $$4\;3\;1\;5\;2$$
> **推论**：如果我们把原位置上的数与目标位置上的数进行建边，会得到一些（可能一个）环或点。

> 如上例：
> $$1\to 4\to 5\to 2\to 3\to 1$$
> 多举几个例子，会发现都符合推论。

那我们再来看本题的置换。

但是本题的置换有一个很大的特色——每次置换后都会推出第 $1$ 个数，加入第 $m+1$ 个数。

这样的特色带来了一个**性质**：那就是本题置换不会出现环，只会出现链。

为什么呢？因为有一个都被推出了，相当于下一次的置换就再也找不到那一个。因此不会形成环。

那现在，就对我们的置换操作，来分些 Part 吧。
## Part 1 “直接走”操作
为什么叫“直接走”？这个操作用来得到被推出来的 $n-m+1$ 张牌。

$n-m+1$ 是因为最多只会做 $n-m+1$ 次置换。

因此，可以用 dfs 染色的方法先把含$1$的链得出。那么按 dfs 顺序得到的一些 $x_i$ 代表着正数第 $i$ 次原编号为 $x$ 的牌就被推出了。

但是要一点要注意，因为有的时候置换的操作不多，所以可能有一些残留的、与答案不符的。

所以需要做个判断，假设得到的 $x$ 数组长度为 $len$。
+ 若 $len< n-m+1$，则将 $x_i$ 其中 $i\in [1,len]$ 一个一个地压入答案的 $ans[]$ 数组里。
+ 否则，直接将 $i\in [1,n-m+1]$ 的所有 $x_i$ 压入 $ans[]$ 即可。

但是，第一种情况时，还有一些 $(n-m+1-len)$ 的元素还没压入怎么办？如何考虑这些元素？

请移步 Part 2
## Part 2 “直接走没走完”操作
这里，我们如何思考？

考场上，可以通过打表法来观察。即我们手搓样例，再模拟出牌过程。

**[warning]**： 如果你不想思考、不想自己动手，可以直接跳到**一个结论**部分。

这里可以提供一组样例，**十分建议**大家手搓一下：
### 输入
```
10 5 10
4
1
3
5
2
10
9
8
7
6
5
4
3
2
1
```
### 输出
```
2
3
1
5
6
7
10
8
9
4
```
这个样例，是属于“直接走没走完”的情况。因为含 $1$ 的链，只有
$$2\to 3\to 1\to 5$$
这也正是样例输出的前四个。

但是 $n-m+1=10-5+1=6$，现在只得到了“直接走”部分的前 $4$ 个，还有俩没输出呢，怎么办？

仔细看看样例输出，$6$ 和 $7$ 是接下来的这俩。

有啥规律吗？如果你再多搓几组样例，就会发现一个结论。

### 一个结论
$$
x_i=m+i\;\;\;\;\; i\in [len+1,n-m+1-len]
$$

但是道理是什么？

因为我们这 $m$ 个位置的置换可以分成两部分：
+ 从入口 $0$ 到 $m$ 的一条链（路径）
+ 其余部分

而这个其余部分是**各种大小不一的环**，而置换后，本质上数的位置就是环中不断变换的位置。

结论已出，那此 Part 结束。现在，我们剑指 Part 3。
## Part 3 “走不完”操作
为什么叫“走不完”？

因为剩下的部分数量 $< m $ 无法进行置换操作。故称“走不完”。

此处要注意的是，有些人一开始会认为：“这些牌做不了置换，那就没有发生过位置变动，直接一个一个按原顺序压入 $ans[]$ 好了。”

错误的。

因为有一些部分“经历过”置换，可能是被换过来的。所以上面的说法并不正确。

那这一部分怎么处理呢？

先假设从入口 $0$ 到 $m$ 的链（路径）长度为 $l$。

因为这是最后的 $m-1$ 个数，所以链（路径）中留下来的就是最后进入链（路径）的 $l-1$ 个数。因为没有第 $m$ 个数了（数量都 $< m$ 了嘛），意味着没有新的数加入进来。其余位置也就是环了（这里解释过，在 Part 2 末），那么可以用同余的方式得出每个位置上的数。

## Part 4 查询操作
那现在，我们把置换分成的这 3 个部分全分析清楚了，那么出牌顺序就可以存下来 $ans[]$ 。询问的时候，$O(1)$ 输出就好了。

时间复杂度： $O(n)$。

预计： 100pts
## 代码实现
虽然时间复杂度降下来了，但是这个方法的思考难度、实现难度都比倍增法更难一些。

所以这里贴一份全代码，各位奆奆洁身自好、**不要 COPY**。

此处贴一份原题检测时AC的代码，因为是原题检测，为了手速就丢掉快读、快写了。`79ms`的评测代码是加了快读、快写的。

评测下来是 `90ms`，这仍比 $O(n\log n)$ 的倍增做法快了不止一点。

**[warning]**： 码风丑的话喷轻一点（逃

code
```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long
#define pb push_back

const int MAXN=1e5+5;

int n,m,q;
int p[MAXN],f[MAXN];
int tot,cnt,len=-1;
int rk[MAXN];
int col[MAXN],ans[MAXN],b[MAXN],c[MAXN];
bool vis[MAXN];
struct node
{
    vector<int> v;
}a[MAXN];

void dfs(int x,int co)
{
    if(col[x]) return;
    if(co==1)
        b[++len]=x;
    col[x]=co;
    rk[x]=a[co].v.size();
    a[co].v.pb(x);
    if(x>=m) return;
    dfs(f[x+1],co);
}

void work1(int x)
{
    if(col[x]==1)
    {
        if(rk[x]>=n-m+1)
            c[a[1].v[rk[x]-n+m-1]]=x;
    }
    else
    {
        int co=col[x];
        int l=a[co].v.size();
        c[a[co].v[((rk[x]-n+m-1)%l+l)%l]]=x;
    }
}

void work2(int x,int y)
{
    if(vis[x]) return;
    if(rk[m]>=y)
        c[a[1].v[rk[m]-y]]=x;
}

signed main()
{
    scanf("%lld%lld%lld",&n,&m,&q);
    for(int i=1;i<=m;i++)
        scanf("%lld",&p[i]),f[p[i]]=i;
    for(int i=0;i<=m;i++)
        if(!col[i])
            dfs(i,++tot);
    if(len<n-m+1)
    {
        for(int i=1;i<=len;i++)
            ans[++cnt]=b[i];
        for(int i=1;i<=n-m+1-len;i++)
            ans[++cnt]=m+i,vis[m+i]=1;
    }
    else for(int i=1;i<=n-m+1;i++)
        ans[++cnt]=b[i];
    for(int i=1;i<=m;i++)
        work1(i);
    for(int i=m+1,j=n-m;i<=n;i++,j--)
        work2(i,j);
    for(int i=1;i<m;i++)
        ans[++cnt]=c[i];
    while(q--)
    {
        int x;
        scanf("%lld",&x);
        printf("%lld\n",ans[n-x+1]);
    }
    return 0;
}
```

---

## 作者：Egg_eating_master (赞：3)

这里补一个 $O(nq)$ 的做法。

暴力 $O(nm)$ 显然是不行的。但我们看到 $q$ 的范围很小，只有 $5000$，所以考虑对每个询问，用 $O(n)$ 或 $O(m)$ 的时间解决掉。

考虑倒推。我们**从后往前**模拟每次置换，求出当前牌在本轮置换以前的位置。这样单次询问的复杂度就做到$O(n)$了。

时间卡的有点紧，吸了口氧跑过去了。

代码很短。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n, m, q;
int rep[100005];
inline int read() {
	int x = 0; char c = getchar();
	while (!isdigit(c)) c = getchar();
	while (isdigit(c)) {x = (x << 3) + (x << 1) + (c ^ 48); c = getchar();}
	return x;
}
int main() {
	n = read(); m = read(); q = read();
	for (int i = 1; i <= m; i++)
	    rep[read()] = i;//rep[i]表示对于一个排列置换后，位置i上原本的数
	for (int i = 1; i <= q; i++) {
		int x = read(), pl = n - x + 1;
		for (int j = n - x + 1; j >= 1; j--)
		    if (pl <= j + m - 1 && j + m - 1 <= n) pl = j + rep[pl - j + 1] - 1;//模拟倒推
		printf("%d\n", pl);
	}
	return 0;
}
```


---

## 作者：AquaRio (赞：2)

 食用效果更佳：[**我的博客**](http://39.105.95.125/index.php/archives/380/)

既然没有正解，那我就来写一发把。

### 思路:

我们对问题仔细研究，很快就会发现，问题就是给定一个位置 $x$ ，问它经过若干轮置换后会到达哪个位置。

值得注意的是我们需要对置换做出一些调整，因为每次都会删除头部的元素，所以真实的置换是 $p[i]-1$。  

举个栗子：

$[1, 2, 3, 4, 5] -> [2, 3, 1, 4, 5] -> [3,1,4,5]$  

在这里面，$p[1]=3$，但是 $1$ 在置换到 $3$ 号位置的时候，$2$ 被弹了出来，所以 $1$ 实际上换到的位置是 $p[1]-1=2$ 。

我们瞄一眼数据范围，$1e5$ 好吓人，我们必须找出一种带有 $\log$ 的方法来求出每一个询问的数置换的最终位置。

灵机一动，**倍增**！

我们设 $a[i][j]$ 表示 $j\ (1 \leq j \leq m) $ 在置换 $2^{i}$ 次后的位置。

于是我们就可以找到最终位置辣 (>_<)

但是要注意当中途走到 $0$ 时，说明离开了队列，应及时终止。

### 代码：

```cpp
/*
	Name: P3095 [USACO13DEC]贝西洗牌The Bessie Shuffle
	Author: AquaRio
	Date: 30/09/19 22:01
	State: Accepted
	Anti_Copy: Enabled 
*/

#include<bits/stdc++.h>
using namespace std;

const int N=100005,M=30;

int n,m,q;
int a[M][N];

inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-'){f=-1;}ch=getchar();}
	while(ch>='0'&&ch<='9') {x=x*10+ch-'0';ch=getchar();}
	return x*f;
}

int main(){
//	freopen("testdata.in","r",stdin); 
	n=read();m=read();q=read();
	for(int i=m;i;i--){
		int x=read();
		a[0][m-x+1]=i-1;//注意置换是P[i]-1 
	}
	for(int i=1;i<M;i++)
		for(int j=1;j<=m;j++)
			a[i][j]=a[i-1][a[i-1][j]];//倍增预处理
	int x,r,len;
	while(q--){
		x=read();
		if(x<m) r=m;
		else r=x,x=m;
		len=n-r+1;　 
		for(int i=M-1;~i;i--)
			if((1<<i)<=len && a[i][x]) 
				x=a[i][x],len-=1<<i,r+=1<<i;//倍增查找最终位置 
		if(len) x=a[0][x],r++;//注意弹出去
		cout<<n-r+m-x+1<<endl; 
	} 
	return 0;
}
```


---

## 作者：Liang_9 (赞：1)

## 题意分析
对一个序列进行 $n-m$ 次变换，每次对前 $m$ 张牌进行交换，变换后把第 $1$ 张牌弹出序列。
## 做法
注意到 $q<5 \times 10^3$，$n<1 \times 10^5$，所以  $O(nq)$ 是可以通过此题的。
所以可以在询问时，倒推出该位置上的数在原序列中的位置。
对于一个位置上的数，上一轮的位置一定是已知的。
当 $p_i=j$，$j$ 位置上的数上一轮一定在 $i+1$ 位置（每次取走队首，所以下标 $+1$）。
若 $i+1>m$，则证明这个数，初始未在前 $m$ 个数，因为每一轮下面的数会减少一个，所以根据轮数即可知道编号。

## 代码实现
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;

int n,m,q;
int p[N],sp[N];

signed main()
{
    cin>>n>>m>>q;
    for(int i=1;i<=m;i++) cin>>p[i],sp[p[i]]=i;//逆映射，方便查询
    
    while(q--)
    {
        int s,x;//s表示轮数，x表示当前位置
        cin>>s;
        s=n-s+1;//从上到下的顺序颠倒
        x=1;//弹出的是第一位
        if(n-s<m) x=m-(n-s),s=n-m+1;//不足一轮，把他变回倒数第一轮
        while(s--)
        {
            x=sp[x]+1;
            if(x>m)//初始不在队列
            {
                x=m+s;//第s轮增加的是m+s
                break;
            }
        }
        if(s==-1) x--; //初始在队列，多余的1减掉
        cout<<x<<'\n';//输出
    }
}
```

---

## 作者：曹老师 (赞：1)

## Sol ##

[blog食用](http://www.caolaoshi.men/index.php/archives/usaco13dec-shuffle.html)

~~没有题解，不知道介不介意收一个未AC的题解~~

**暴力解法**

全网就只有一个很玄学的做法？然而我用暴力还是打了不少分的……

与其说暴力，不如说是模拟，因为完全是按照题目中让做的来做的。就是取出前$M$个，然后交换位置，再取出$M$个，被删掉的数字放到一个新的数组里，原数组的初始位置不断地向后移动，最后构不成$M$，不就结束了吗，然后就是询问，$O(1)$的输出。

## Code ##

```
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;

const int L = 100005;
int n , m , q , p[L] , num[L] , ans[L] , cnt = 0;

void exc(int t[] , int top) {
	int  s[L];
	for(int i=1; i<=top; i++)
		s[p[i]] = t[i];
	ans[++cnt] = s[1];
	for(int i=2; i<=top; i++)
		num[cnt+i-1] = s[i];
}

void sol() {
	int t[L];
	for(int j=cnt+1; j<=n-m+1; j++) {
		for(int i=j; i<=j+m-1; i++)
			t[i-j+1] = num[i];
		exc(t , m);
	}
	int temp = cnt;
	for(int i=temp+1; i<=n; i++)
		ans[++cnt] = num[i];
}

int main() {
	scanf("%d%d%d",&n,&m ,&q);
	for(int i=1; i<=n; i++)
		num[i] = i;
	for(int i=1; i<=m; i++)
		scanf("%d",&p[i]);
	sol();
	while(q--) {
		int x;
		scanf("%d",&x);
		printf("%d\n",ans[n-x+1]);
	}
	return 0;
}
```


  [1]: https://www.luogu.org/problemnew/show/P3095

---

## 作者：__HHX__ (赞：0)

# 思路
我们首先将所有操作列出来，我们令牌 $i$ 从上到下的位置为 $c_i$，其中 $p$ 与原题中 $p$ 意义相同。

1. $c_i := p_{c_i}(c_i \leq m)$
2. $c_i := c_i - 1$
3. 取走 $c_i=0$，$i$ 记录入答案。

我们将操作一二合并，其中 $c_i > m$ 时 $p_{c_i} = c_i$。

得操作：$c_i := p_{c_i} - 1$。

我们将所有 $c_i$ 和 $p_{c_i} - 1$ 连边。

我们发现除点 $n,0$，其他点出入度均为 $1$。

然后我们可以推出 $f_{i,j} = f_{f{i, j -1}, j- 1}$ 这样的倍增式子，用倍增就能愉快地解决这题。

但我不同，我要不愉快地解决这题。

我们发现其中点 $n$ 出度为 $1$，点 $0$ 入度为 $1$。

而且这张图一定为一条 $n$ 到 $0$ 的链和若干个环。

我们先处理环，我们发现洗牌操作会做 $n - m + 1$ 次。

所以环上点会向后走 $n - m + 1$ 步，假设走 $\infty$ 步，我们将走的位置写下来，我们发现其实循环的，每个循环节就是这个环上的节点一个接一个构成的，其中循环节的长度就是环的节点个数。

所以我们只要记录环 $k$ 上每个点 $i$ 的在环上位置 $k_i$ 和环的长度 $si_k$。

经过 $n - m + 1$ 次操作后，点 $i$ 在环上位置 $k_i$ 会跳到 $(k_i + n - m + 1) \bmod si_k$ 的位置。

环上问题就解决了。

接下来处理链上的问题。

我们做个双指针，第一个指针 $i$ 表示完成操作前的点，第二个指针 $j$ 表示完成操作后点。

其中 $i$ 的下一个节点 $i'$，所对应的 $j'$ 就是 $j$ 的下一个节点，其中 $i,j$ 距离为 $n - m + 1$。

如果 $j$ 是 $0$ 后面，那就说明已经弹出，记录答案。

然后将剩下的点按编号顺序输出即可。

---

## 作者：红黑树 (赞：0)

## [题意](https://www.luogu.com.cn/problem/P3095)
给定一个 $M$ 的置换，初始有一个 $1$ 到 $N$ 的排列，不断对前 $M$ 个数进行置换，然后取出第一个数，不足 $M$ 时不置换只取出。

然后进行 $Q$ 次询问，每次求出取出的第 $x$ 个数。

## 题解
### 算法 1
在普通置换问题中，每个位置经过置换后都会到达一个互不相同的位置，而本题中，所有数置换后还会向前移一位，第 $1$ 个数被取出，有一个数被补到最后。仔细分析置换的过程，可以发现任意时刻在第 $M$ 个位置上的数，经过多次置换和向前移动的操作后，必然都会被取出，因为不会有一个已经出现过的数被替换到位置 $M$ 形成环。

所以我们可以将 $M$ 个位置分成两类，其中有一条从入口位置 $0$ 到位置 $M$ 的路径，这条路径不断的取出新的数并补充新的数进来。另一类就是各种大小不一的环，里面的数置换后就是环中不断变换的位置。

基于上述分析，我们可以将取数流程分为三段，假定从 $0$ 到 $M$ 的路径长度为 $t$。首先是 $N - M + 1$ 次置换后取出的数，其中又可以细分为两段，前 $t$ 个数时路径中已有的数，之后是从 $M + 1$ 开始的补充进来的数。最后一段是所有置换完成后剩下的 $M - 1$ 个数。

对于最后的 $M - 1$ 个数，路径的位留下的是最后进入路径的 $t - 1$ 个数，位置 $M$ 没有数，因为此时已经没有新的数补充进来。其他位置就是环，我们可以一次找一个环，用同余求出每个位置上的数。

我们可以求出整个取数序列，然后每次询问就可以直接求解了。

注意，有可能置换的操作次数很少，导致最初在路径中的数都没取出来，此时路径中可能会有一些最初就在路径中，但是位置变化的数，还有一些是新补充进来的数。

时间复杂度 $\mathcal O\left(N\right)$

### 算法 2
预处理出每个位置置换 $2^i$ 次时的倍增数组。

每次询问暴力跳倍增即可。

注意走到 $0$ 时应及时终止，因为已经离开了队列。

时间复杂度 $\mathcal O\left(N \log N\right)$

### 算法 3
倒推。**从后往前** 模拟每次置换，求出当前牌在本轮置换以前的位置。这样单次询问的复杂度就是 $\mathcal O\left(N\right)$。总时间复杂度 $\mathcal O(N \cdot Q)$，2013 年的老机器过不了。

代码写的是 算法 2。

## 代码
```cpp
constexpr tp Hat_LM = 30, Hat_M = 1e5 + 3;
tp n = ra, m = ra, q = ra;
array<array<tp, Hat_M>, Hat_LM> p;
for (tp i = m; i; --i) {
  p[0][m - ra + 1] = i - 1;
}
for (tp i = 1; i < Hat_LM; ++i) {
  for (tp j = 1; j <= m; ++j) {
    p[i][j] = p[i - 1][p[i - 1][j]];
  }
}
while (q--) {
  tp q = ra, t = q < m ? m : q, l = n - t + 1, ql = 0;
  q = q < m ? q : m;
  for (tp i = Hat_LM - 1; ~i; --i) {
    if (tp loc = ql + (1ll << i); loc <= l && p[i][q]) {
      ql = loc;
      q = p[i][q];
      t += 1ll << i;
    }
  }
  printf("%lld\n", n - t + m - (ql != l ? p[0][q] : q - 1));
}
```

---

