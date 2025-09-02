# Xor Tree

## 题目描述

For a given sequence of distinct non-negative integers $ (b_1, b_2, \dots, b_k) $ we determine if it is good in the following way:

- Consider a graph on $ k $ nodes, with numbers from $ b_1 $ to $ b_k $ written on them.
- For every $ i $ from $ 1 $ to $ k $ : find such $ j $ ( $ 1 \le j \le k $ , $ j\neq i $ ), for which $ (b_i \oplus b_j) $ is the smallest among all such $ j $ , where $ \oplus $ denotes the operation of bitwise XOR ([https://en.wikipedia.org/wiki/Bitwise\_operation#XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)). Next, draw an undirected edge between vertices with numbers $ b_i $ and $ b_j $ in this graph.
- We say that the sequence is good if and only if the resulting graph forms a tree (is connected and doesn't have any simple cycles).

It is possible that for some numbers $ b_i $ and $ b_j $ , you will try to add the edge between them twice. Nevertheless, you will add this edge only once.

You can find an example below (the picture corresponding to the first test case).

Sequence $ (0, 1, 5, 2, 6) $ is not good as we cannot reach $ 1 $ from $ 5 $ .

However, sequence $ (0, 1, 5, 2) $ is good.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1446C/787661480e10ca394e5bb0097a1db13aac775e6e.png)You are given a sequence $ (a_1, a_2, \dots, a_n) $ of distinct non-negative integers. You would like to remove some of the elements (possibly none) to make the remaining sequence good. What is the minimum possible number of removals required to achieve this goal?

It can be shown that for any sequence, we can remove some number of elements, leaving at least $ 2 $ , so that the remaining sequence is good.

## 说明/提示

Note that numbers which you remove don't impact the procedure of telling whether the resulting sequence is good.

It is possible that for some numbers $ b_i $ and $ b_j $ , you will try to add the edge between them twice. Nevertheless, you will add this edge only once.

## 样例 #1

### 输入

```
5
0 1 5 2 6```

### 输出

```
1```

## 样例 #2

### 输入

```
7
6 9 8 7 3 5 2```

### 输出

```
2```

# 题解

## 作者：BlankAo (赞：141)

那是代代相传的处事真言：“如果不能铲除更多不如意，不如去保留更多的幸福。”

将每个数字代表的点化作星斗，那么仰望星空，星图上最多会有 $n$ 条轻灵丝线。而我们需要遮蔽掉尽量少的星斗，也就是让尽量多的星斗照耀，使得有且仅有一对星斗——牛郎织女星 $(i,j)$，互相都有 $a_i\ \text{xor}\ a_j$ 为它们的最小值。依此法做，$i$ 会指向 $j$，且 $j$ 会指向 $i$，双向奔赴，丝线重合，星图上只有 $n-1$ 条丝线，我们仰头探望，便是树状星辰。

想到 $\text{xor}$，思想的平原上便生长出一棵茂盛多枝的字典树，而神妙的肥料就是我们插入的星斗数值 $a_i$。我们在字典树的 $x$ 号点上刻上数字 $f_x$，代表探索到 $x$ 号点的瞬间，我们最优还能保留多少星斗，使多少星斗照耀。

那么，刻画的数字 $f_x$ 满足以下规律：如果 $f_x$ 没有左向的枝丫，那么 $f_x$ 就是右向的枝丫刻画的数字；如果 $f_x$ 没有右向的枝丫，那么 $f_x$ 就是左向的枝丫刻画的数字。

尽管如此，如果 $x$ 既有左向的枝丫，又有右向的枝丫，那么该如何是好？不要慌张，不要大意，我们仅需令 $f_x$ 等于左向的枝丫刻画的数字与右向的枝丫刻画的数字的极大之值，再加上恒本之 “$1$” 即可。原因如下，如果左向枝丫、右向枝丫各只对应一个星斗数值，分别为 $a_i,a_j$ 那么这一对 $(i,j)$ 满足条件。否则，例如左向枝丫刻画之树稍大，那么我们可以保留全部的左向枝丫对应的星辰，再选一个右边的星斗。设 $x$ 的深度为 $dep_x$，由于它们在二进制下从高向低第 $dep_x+1$ 位不同，所以右边的星斗必不会与左边的星斗满足条件（左边的星斗互相连显然更优）。因此，当这棵字典树上数字刻尽，再向上望去，必将也是一棵大树——满足题设的、长在星辰大海中的苍天之树。而擦拭汗水后，用 $n$ 减去字典树根节点的刻画的数字（因为求的是最少遮蔽多少星辰，便是 $n-f_{\text{root}}$），便是我们将大声呼喊出的，世间的最终真理。

---

## 作者：tommymio (赞：40)

遇到这种求最小删除数的题目，都可以转化为求最大保留数。

将题目的题意转化一下，保留最多的数，令只存在一对 $(i,j)$ 对彼此而言 $a_i\oplus a_j$ 的值都是最小的。

自然想到 $\text{trie}$。把所有数插入进 $\text{trie}$ 里，递归考虑 $\text{trie}$ 的一棵子树 $x$，记令子树 $x$ 合法的最大保留数为 $f_x$，子树 $x$ 的左右儿子对应的是二进制意义下的第 $k$ 位。

那么当子树 $x$ 只存在左/右儿子时，$f_x$ 的值就是左右儿子的值。否则就是左儿子的 $f$ 值与右儿子的 $f$ 值取 $\max$ 再 $+1$。怎么理解呢？在第 $k$ 位之前，对应位的值都相同，仅第 $k$ 位不相同，保留左右子树中的一棵，再保留其余子树的一个节点，一定就能确保当前子树内只存在一对上述的 $(i,j)$。

最后答案就是 $n-f_{rt}$。时间复杂度为 $O(n \log n)$。

```cpp
#include<cstdio>
int rt=1,tot=1;
int a[200005],ch[4000005][2];
inline int read() {
	register int x=0,f=1;register char s=getchar();
	while(s>'9'||s<'0') {if(s=='-') f=-1;s=getchar();}
	while(s>='0'&&s<='9') {x=x*10+s-'0';s=getchar();}
	return x*f;
}
inline int max(const int &x,const int &y) {return x>y? x:y;}
inline void insert(int val) {                        
	int p=rt;
	for(register int i=30;i>=0;--i) {
		int cur=val>>i&1;
		if(!ch[p][cur]) ch[p][cur]=++tot;
		p=ch[p][cur];
	}
}
inline int GetMaxPoint(int p) {
	if(!ch[p][0]&&!ch[p][1]) return 1;
	if(!ch[p][0]) return GetMaxPoint(ch[p][1]);
	if(!ch[p][1]) return GetMaxPoint(ch[p][0]);
	return max(GetMaxPoint(ch[p][0]),GetMaxPoint(ch[p][1]))+1;
}
int main() {
	int n=read();
	for(register int i=1;i<=n;++i) insert(a[i]=read());
	printf("%d\n",n-GetMaxPoint(rt));
	return 0;
}
```

---

## 作者：Marsrayd (赞：10)

## [题目传送门](https://www.luogu.com.cn/problem/CF1446C)

## 题意简述

给定你一个序列 $a$（序列为互不相同的正整数），对于每个 $i$，它会向序列中的满足 $a_i⊕a_j$ 最小的 $j$ 连双向边，并且如果 $j$ 也向 $i$ 连了边，只算一条边。现在要让你删去序列中的一些数，使得最后形成的图是一颗树，输出最少需要删除几个数。

## 前置芝士

- $\texttt{Trie }$树：看到这类异或值最大最小的字眼很容易想到 “ $\texttt{Trie }$树 ”。

- 简单 dp 能力。

## $\texttt{SOLUTION}$

求最小删除数十分困难，不如转过来求最大保留。

先将每个数字插入 $\texttt{Trie}$ 树中。

因为异或值最小的两个数才会连边。

所以没删除前一定是 $\texttt{Trie}$ 树中如下图所示的点所表示的数会连边，不难发现他们是不连通的。

![](https://cdn.luogu.com.cn/upload/image_hosting/b3kkyhqz.png)

要让他们变为一棵树，就就必须删除一些点。

记以 $u$ 为根的子树中的数字连完边后为一棵树的最大保留数为 $dp_u$（有点拗口qwq）。

其实按上图中连边，我们已经求出了：$dp_4=dp_5=dp_6=dp_7=2$。

然后我们继续递归处理。

开始处理 $dp_2$ 想要让以 $4$ 为根的子树中的数与以 $5$ 为根的子树连边。就必须要让两棵子树的其中一棵只保留一个数字。

为什么呢？因为 $\text{Trie}$ 树中一个子树内任意两个数的异或值一定比一个子树内的数与一个子树外的数异或值小。

所以为了让这棵子树内的树与另一棵子树上的树连边，只能令这棵子树只留下它一个数。

于是 $dp$ 转移出来了。

记 $u$ 的两个儿子为 $v_1,v_2$。

$$
dp_u=\left\{
\begin{aligned}
1(u\ \text{不存在儿子，即}u\text{为叶子}) \\
dp_{v_1}\ (u\text{不存在}v_2\text{儿子})\\
dp_{v_2}\ (u\text{不存在}v_1\text{儿子})\\
\max\{dp_{v_2},dp_{v_1}\}+1\ (u\text{存在两个儿子})\\


\end{aligned}
\right.
$$


列完转移发现甚至不需要记录 $dp$ 数组。一遍递归即可解决。

$\texttt{AC CODE}$

```cpp
#include<bits/stdc++.h>
#define IN inline

const int N=3000010;

IN int read()
{
	int x=0; char ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return x;
}
int idx;
struct Trie_Tree{int son[2];}tr[N];
inline void insert(int x)
{
	int p=0;
	for(int i=30;i>=0;i--)
	{
		int tmp=(x>>i)&1;
		if(!tr[p].son[tmp]) tr[p].son[tmp]=++idx;
		p=tr[p].son[tmp];
	}
}
long long dp(int p)
{
	if(!tr[p].son[0]&&!tr[p].son[1]) return 1;
	if(!tr[p].son[0]&&tr[p].son[1]) return dp(tr[p].son[1]);
	if(tr[p].son[0]&&!tr[p].son[1]) return dp(tr[p].son[0]);
	return std::max(dp(tr[p].son[0]),dp(tr[p].son[1]))+1;
}
int main()
{
	int n=read();
	for(int i=1;i<=n;i++) insert(read());
	return !printf("%lld",n-dp(0));
}
```

欢迎提问or提出我的问题，会改的。

---

## 作者：Piwry (赞：7)

## 解析

首先发现任意序列至少有一对重边；只需考虑所有元素对中异或和最小的那对就行

于是我们只需判断结果图是否连通

考虑为所有元素建一个 01trie。对于第 $i$ 位的某对左右子树 $S_{i, 0}, S_{i, 1}$，不难发现若有 $|S_{i, 0}|\geq 2$ 且 $|S_{i, 1}|\geq 2$，那么两颗子树中的元素一定都仅会往自己子树中的元素连边（贪心考虑最高位即可）；这样左右子树的元素间就不连通了

于是考虑从 01trie 的根 dfs，做一遍 dp 即可

具体来说，考虑子树 $T$ 的答案（保持连通需要删掉的最小元素数量）。如果 $T$ 的左右子树 $S_{i, 0}, S_{i, 1}$ 的大小均不大于 $1$，那么 $T$ 就不需要删元素。否则的话，设子树的答案 $v_0, v_1$，对 $v_0+\max(0, |S_{i, 1}|-1)$ 和 $v_1+\max(0, |S_{i, 0}|-1)$ 取个 min 即可（枚举要将哪颗子树的大小减少到 $1$；注意有可能枚举的要减少的子树的大小已经不大于 $1$）

解释不太清楚的地方可参考代码qaq

## CODE

```cpp
#include <cstdio>
#include <iostream>
using std::min;
using std::max;

const int MAXN =2e5+20, MAXT =2e5*31+20, LEAF =30;

/*------------------------------IO------------------------------*/

int read(){
	int x =0; char c =getchar(); bool f =0;
	while(c < '0' || c > '9') (c == '-') ? f =1, c =getchar() : c =getchar();
	while(c >= '0' && c <= '9') x =(x<<1)+(x<<3)+(48^c), c =getchar();
	return (f) ? -x : x;
}

/*------------------------------01Trie------------------------------*/

int ls[MAXT], rs[MAXT], root =1, tot =1;
int siz[MAXT];

void insert(const int &val, const int &dep =0, const int &x =root){
	if(dep == LEAF){
		siz[x] =1;
		return;
	}
	if(val&(1<<(LEAF-1-dep)))
		insert(val, dep+1, rs[x] =(rs[x]) ? rs[x] : ++tot);
	else
		insert(val, dep+1, ls[x] =(ls[x]) ? ls[x] : ++tot);
	siz[x] =siz[ls[x]]+siz[rs[x]];
}

int dfs(const int &x =root){
	if(siz[ls[x]] <= 1 && siz[rs[x]] <= 1)
		return 0;
	int ret =0x3f3f3f3f;
	if(ls[x])
		ret =min(ret, dfs(ls[x])+max(0, siz[rs[x]]-1));
	if(rs[x])
		ret =min(ret, dfs(rs[x])+max(0, siz[ls[x]]-1));
	return ret;
}

/*------------------------------Main------------------------------*/

int main(){
	int n =read();
	for(int i =0; i < n; ++i){
		int a =read();
		insert(a);
	}
	printf("%d", dfs());
}
```

---

## 作者：duyi (赞：7)

[噜啦噜啦咧噜啦噜啦咧的阅读体验！！！！](https://www.cnblogs.com/dysyn1314/p/14008246.html)


# CF1446C Xor Tree

## 题目大意

[题目链接](https://codeforces.com/contest/1446/problem/C)

对于一个长度为 $k$ 的序列 $b_1,b_2,\dots,b_k$，数字互不相等，我们可以这样构造一张图：

图上有 $k$ 个节点，第 $i$ 个点上写着数字 $b_i$。对每个 $i$，找到一个 $j$，满足 $j\neq i$，且 $b_i\operatorname{xor}b_j$ 最小。然后在 $i,j$ 之间连一条无向边。

我们称一个序列 $b$ 是好的，当且仅当由它生成的无向图，是一个环长为 $2$ 的基环树。

给出一个长度为 $n$ 的序列 $a_1,a_2,\dots,a_n$，数字互不相等。求最少删去多少个数，能使序列变成好的。

数据范围：$1\leq n\leq 2\times10^5$，$1\leq a_i\leq 10^9$。

## 本题题解

首先，任意一个序列，连出来的图一定是一个基环树森林（点数 $=$ 边数）。

考虑所有 $\frac{n(n-1)}{2}$ 对数的 $\operatorname{xor}$ 值，选出其中一对 $\operatorname{xor}$ 值最小的数 $(a_x,a_y)$，则 $a_x$ 与 $a$ 中其他数异或，得到的结果一定大于 $a_x\operatorname{xor}a_y$（因为选出的是最小的，所以不可能小于；因为所有数互不相同，所以不可能等于）；对 $a_y$ 也是同理。所以 $x$, $y$ 一定组成了一个大小为 $2$ 的环。

于是在只有一棵基环树时，环的大小一定是 $2$。进而可以归纳证明，**整个基环树森林，没有大小超过 $2$ 的环**。

于是问题转化为，判断图的**连通性**：如果图联通，序列就是好的；否则就是不好的。

我们**从高到低**考虑每一位。假设当前剩余的数的总数至少为 $3$。把当前剩余的数分成：当前位为 $0$ 的数、当前位为 $1$ 的数两类。分别放入集合 $S_0$, $S_1$。

- 如果某个集合大小 $\leq 1$，则该集合里的数，会直接挂到另一个集合的某个节点上。所以不用考虑它，直接带着另一个集合，考虑下一位。
- 否则，对于大小至少为 $2$ 的集合，里面的数一定会内部连边，不会考虑另一个集合里的点（因为这样能保证当前位的异或值为 $0$）。于是图就至少分裂为两个连通块。我们需要选择一个集合，将其删到只剩一个点，然后递归到下一位，解决另一个集合。

简单讲就是一个递归的过程。我们定义一个递归函数，$f(S,\text{bit})$，表示对于集合 $S$，考虑里面的数在高于 $\text{bit}$ 的位全部相等。现在要使得 $S$ 构成一个连通图，最少还需删掉多少数。那么：
$$
f(S,\text{bit}) = \begin{cases}
0 && |S| < 3\\
\min(f(S_0,\text{bit} - 1) + \max(0,|S_1|-1),f(S_1,\text{bit} - 1) + \max(0,|S_0| - 1)) && |S|\geq 3
\end{cases}
$$
注意：直接选 $S_0,S_1$ 里大小较小的一个删，是不对的。因为这本质是一个 DP 问题而不是贪心问题，局部的最优不一定带来全局的最优。数据 #4 就是一个例子。

值得一提的是，如果你把找异或最小值的过程，想象成在 Trie 树上查找，则上述的递归，也可以理解为在 Trie 树上做树形 DP。我们要保证，不存在某个节点，两个儿子子树大小都 $\geq 2$。

因为最多递归 $O(\log a)$ 层，每层里集合大小 $S$ 之和是 $O(n)$ 的，所以总时间复杂度 $O(n\log a)$。

## 参考代码

[勇敢向前进，前进有奖品！！！](https://www.cnblogs.com/dysyn1314/p/14008246.html)




---

## 作者：AFOier (赞：4)

我们把问题转化为删掉若干个数，使得这个图中只有一个联通块，显然这个连通块不会为一个环，所以问题转化后与转化前等价

将每个数插入一棵01trie

我们发现对于任意节点，若左儿子和右儿子的$siz$都大于$1$，则会形成两个子图（两个儿子之内的数子互相连边）

所以我们必须删除一些节点，使某一儿子的$siz=1$，DP解决即可

```
#include <bits/stdc++.h>
using namespace std;
int n, s, cnt, dig[31], rt, tot;
struct node {
    int son[2], siz;
} a[6000011];
void ins(int &k, int w) {
    if(!k) k = ++tot;
    a[k].siz++;
    if(!w) return;
    ins(a[k].son[dig[w]], w-1);
}
int f[6000011]; //f[i]存以i为根的子树至少需要删除多少个数
void dfs(int k, int w) {
    if(!k || !w) return;
    dfs(a[k].son[0], w-1);
    dfs(a[k].son[1], w-1);
    f[k] = f[a[k].son[0]] + f[a[k].son[1]];
    a[k].siz = a[a[k].son[0]].siz + a[a[k].son[1]].siz; //更新siz
    if(a[a[k].son[0]].siz > 1 && a[a[k].son[1]].siz > 1) {
        if(a[a[k].son[0]].siz > a[a[k].son[1]].siz) {
            a[k].siz -= a[a[k].son[1]].siz - 1;
            f[k] += a[a[k].son[1]].siz - 1;
        }
        else {
            a[k].siz -= a[a[k].son[0]].siz - 1;
            f[k] += a[a[k].son[0]].siz - 1;
        }
    } //如果左右儿子的siz都>1,就将siz较小的儿子siz减为1
}
int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        scanf("%d", &s); cnt = 0;
        memset(dig, 0, sizeof(dig));
        while(s) {
            dig[++cnt] = s % 2;
            s /= 2;
        }
        ins(rt, 30);
    } //01trie建树
    dfs(rt, 30);
    cout << f[rt] << endl;
    return 0;
}
```

---

## 作者：wind_seeker (赞：2)

这是一道字典树好题。

- 性质:

最后留下的数中有且仅有两个数 $(i,j)$ 相互满足 $a_i\oplus a_j$ 是最小的。

- 证明:

$n$ 个点形成树，必然是 $n-1$ 条边，所以有且仅有一条重边。

- 做法:

如果你认为只需要对于其余互相数对删掉一个，建议你仔细思考一下是否会出现删去以后重新形成数对。

然后接下来我们考虑把所有数变成一颗字典树，那么对于一个节点来讲的话。

假设当前节点存的是第 $k$ 位，那么对于当前节点会出现以下三种情况:

- 没有子树，那么直接返回 $1$。

- 没有左子树，访问右子树，返回右子树可存最大个数。

- 没有右子树，访问左子树，返回左子树可存最大个数。

- 同时拥有两个子树，我们必然选择保留其中一个子树，自然是可存最大个数最大的那个，然后在其基础上加 $1$。

对于前三种情况，想必大家是没有什么问题的。

所以只需要证明一下最后一种情况:

假设保留子树 $1$。

所谓的加 $1$，其实是保留子树 $2$ 上的一个数。

首先对于异或，显然两数不一样处位数越低越好。

所以我们取了其中子树 $1$，则子树 $2$ 保留的那唯一一个数就会向子树 $1$ 连边。假设子树 $2$ 保留两个，子树 $2$ 就会产生至少一个数对，而鉴于子树 $1$ 能保留的更多，所以其内部也会至少产生一个，这样就不能满足情况了。

对于子树 $1$:

- 内部自己连。

- 只有一个数时与子树 $2$ 留下的那条形成数对，且在递归过程中只会出现一次。

以上则满足了题目要求，那么只要插入加递归即可完成了。

---

## 作者：hgzxwzf (赞：2)

分治。

从高到低枚举每一位，假设考虑到了 $i$ 位，把数字分组，每一组中所有元素前 $i$ 位相同，如果一个组内元素个数大于 $1$，那么该组中每个元素都是和组内的元素连边。

设 $div(a,i)$ 表示考虑了前 $i$ 位使序列 $a$ 构造出来的图是一棵树能保留的最大元素个数。

如果 $a$ 的大小为 $1$，那么 $div(a,i)=1$。

否则将一个大组 $a$ 分成两个小组，将 $i$ 位为 $0$ 的数分到 $x$ 组中，为 $1$ 的数分到 $y$ 组中。

如果 $x$ 为空，$div(a,i)=div(y,i-1)$；

如果 $y$ 为空 $div(a,i)=div(y,i-1)$；

否则，$div(a,i)=\max(div(x,i-1),div(y,i-1))+1$，意味着 $x,y$ 中其中一个集合只能保留一个元素，因为如果两个集合中都有超过 $2$ 个元素，重边数量就会大于 $1$，而图如果是树必须保证重边有且仅有一条。

```cpp
int div(vector<int>a,int p)
{
	if((int) a.size()==1) return 1;
	vector<int>x,y;
	for(auto &i: a)
		if(i&(1<<p)) x.push_back(i);
		else y.push_back(i);
	if(y.empty()) return div(x,p-1);
	if(x.empty()) return div(y,p-1);
	return max(div(x,p-1),div(y,p-1))+1;
}

int main()
{
	int n;
	scanf("%d",&n);
	vector<int>a(n);
	rep(i,0,n-1) scanf("%d",&a[i]);
	printf("%d",n-div(a,30));
	return 0;
}
```


---

## 作者：几何之舞丶 (赞：1)

### 01 Trie 好题
萌新刚听说01 trie,就遇到这个题.

#### 大概翻译一下
给定一个序列$A$,对于每一个$i$,在剩余的元素中选择一个和$a[i]$异或值最小的$a[j]$,然后给这两个点之间连一条无向边.

显然这张图可能有环或者不连通.

所以我们需要删掉一些序列中的元素,使得剩下的元素组成的图是一棵树.


我们先对于原序列建01trie,然后发现连边的情况肯定是某一个节点的两棵子树之间.

然后对于size大于1的子树,他们肯定只会在子树内连边,两个子树就形成了两个联通块,肯定是不行的.


所以我们需要让一个子树size为1

而这个可以直接树形dp求解.继续见代码吧..
```cpp
#include <vector>
#include <cstdio>
#include <cctype>
#include <utility>
#include <cstring>
#include <cassert>
#include <iostream>
#include <algorithm>
#define R register
#define I inline 
#define int long long
#define ll long long
#define pll pair<ll,ll>
#define rep(i,a,b) for(R int i=a;i<=b;i++)
#define per(i,a,b) for(R int i=a;i>=b;i--)
using namespace std;
template <class T>
inline void read(T &x) {
    x = 0;
    char ch = getchar(), w = 0;
    while (!isdigit(ch)) w = (ch == '-'), ch = getchar();
    while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
    x = w ? -x : x;
    return;
}
const int N =2e5+50;const int lg=30;
namespace Trie
{
    int f[N*lg],sz[N*lg],son[N*lg][2],rt,cnt;
    I void init(){cnt=1;rt=1;}
    I void insert(int x)
    {
        int now =rt;sz[now]++;
        per(i,30,1)
        {
            int opt= (x>>i)&1;
            
            if(!son[now][opt])son[now][opt]=++cnt;
            now=son[now][opt];sz[now]++;
        }

    }  
    I void dfs(int now )
    {
        if(now==0){f[now]=0;return ;}
        int lc=son[now][0];int rc=son[now][1];
        dfs(lc);dfs(rc);
        if(!lc)f[now]=f[rc];
        else
        if(!rc)f[now]=f[lc];
        else
                f[now]=min(f[lc]+sz[rc]-1,f[rc]+sz[lc]-1);
    }
}
signed main()
{
    int n;read(n);
    Trie::init();
    rep(i,1,n)
    {
        int x;read(x);
        Trie::insert(x);
    }
    Trie::dfs(1);
    cout<<Trie::f[1]<<endl;
    return 0;
}
```



---

## 作者：Pecco (赞：1)

这个题是存在不用01-trie的写法的。

我们考虑对所有数按二进制位分组，那么删完数后的最好结果一定是：某一组的点数，加上比它大的组数，如果它不是最小的一组，再加上1。所以我们枚举每一个组寻找答案。

![](https://pic.yuntu.ru/2020/12/11/image0161b695a2771349.png)

但是这个组内部不一定构成一棵树，所以组内也需要删除部分数来构成树。而这只需要删去组内每个数最高位的1，然后递归下去即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2e5 + 5;
int A[MAXN];
int bl(int x) { return 32 - (x == 0 ? 32 : __builtin_clz(x)); } // 二进制长度
void d1(int &x) { x ? x -= (1 << (bl(x) - 1)) : 0; } // 删除最高位的1
int solve(int A[], int n)
{
    int *B = new int[n], *nxt = new int[n];
    if (n == 1)
        return 1;
    int last = 0, cnt = 1, cur, ma = 0;
    for (int i = 0; i < n - 1; ++i)
        if (bl(A[i]) != bl(A[i + 1]))
            nxt[last] = i + 1, last = i + 1, cnt++;
    nxt[last] = n;
    cur = cnt;
    for (int i = 0; i < n; i = nxt[i])
    {
        cur--;
        copy(A + i, A + nxt[i], B);
        for_each(B, B + nxt[i] - i, d1);
        int extra = solve(B, nxt[i] - i);
        ma = max(cur + extra + (i != 0), ma);
    }
    delete[] B;
    delete[] nxt;
    return ma;
}
int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i)
        cin >> A[i];
    sort(A, A + n);
    cout << n - solve(A, n);
    return 0;
}
```

---

## 作者：xukuan (赞：0)

根据套路，这种题应该用字典树来做

满足的条件是存在且只存在一对$(i,j)$，$a_i \space xor \space a_j$的值对双方都是最小的

那么询问的时候，
$$
query(p)=\begin{aligned}
1,lson_p=empty,rson_p=empty\\
query(lson_p),lson_p \neq empty,rson_p=empty\\
query(rson_p),lson_p=empty,rson_p \neq empty\\
max(query(lson_p),query(rson_p))+1,lson_p \neq empty,rson_p \neq empty\\
\end{aligned}
$$

前三个柿子都不解释，就解释最后一个

我们假设有两个集合：lson和rson，最小的结果就是一个的最优解加上另外里面选1个，这样另外集合xor剩下的当前为都是1，所以一定不影响结果

代码：
```cpp
#include<bits/stdc++.h>
#include<iostream>
#include<cstdio>
#define ll long long
using namespace std;

const ll N=200010;
ll n,cnt=1,tree[N*20][2],root=1;

inline ll read(){
	ll x=0,tmp=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-') tmp=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<3)+(x<<1)+(ch^48);
		ch=getchar();
	}
	return tmp*x;
}

inline void Insert(ll val){
	ll p=root;
	for(ll i=30; i>=0; i--){
		ll x=(val>>i)&1;
		if(!tree[p][x]) tree[p][x]=++cnt;
		p=tree[p][x];
	}
}

ll query(ll p){
	if(!tree[p][0]&&!tree[p][1]) return 1;
	if(!tree[p][0]) return query(tree[p][1]);
	if(!tree[p][1]) return query(tree[p][0]);
	return max(query(tree[p][0]),query(tree[p][1]))+1;
}

int main(){
	n=read();
	for(ll i=1; i<=n; i++) Insert(read());
	cout<<n-query(root)<<endl;
	return 0;
}
```

---

