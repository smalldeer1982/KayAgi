# 泪光 | Tears

## 题目背景

「为什么哭呢？」

“因为自己的期许和现实相去甚远。”

「哭能改变什么呢？」

“什么都不能。正如同既成事实的过去一样。”

「那么为何不抹去泪水向前迈进呢？」

“… 我在等我的灵魂追上时间。”

> After night
>
> 长夜之后
>
> In boundless light
>
> 无垠光中
>
> He calls my name
>
> 他呼唤着我
>
> I do the same
>
> 我望向彼方，回应

## 题目描述

「不想回忆的事，就别再去想了吧。为了分散你的注意力，正好我有一道与人的感情相关的题目，你看看怎么样？」

“… 真是令人想吐槽呢。怎么，又是那个人在支配吗？”

「什么嘛，令人不快… 你以前对这种事不是有很大的热情吗？」

“… 说不准。”

「咳咳… 那么听好了。现在共有 $n$ 个人，每个人都有一个情绪值：用 **实数** $v_i$ 表示。现在由于一些特殊的变化，使得这些人的情感发生了纠缠…」

“嗯哼？”

「第一种纠缠有四个参数 $a,b,c,d$，表示：现在已知存在无穷个 $f:\R\rightarrow\R$，使得 $\frac{f(v_a)}{f(v_b)}=\frac{v_c}{v_d}$。」

“等等等等一下！这数学公式是怎么说出来的啊？！还有什么 $f:\R\rightarrow\R$ 是什么意思啊！”

「你瞧，你不也说出来了吗？」

“… 可恶，果然是你吗，那个人…”

「简单来说，$f:\R\rightarrow\R$ 就是代表一个定义域和值域都是实数的函数。如果这都不能理解的话，我要开始怀疑你作为高中生的身份了哦…」

“好吧… 继续吧。”

「第二种纠缠有两个参数 $a,b$，表示：现在已知存在有穷个 $f:\R\rightarrow\R$，使得 $f(v_a)\ne f(v_b)$。」

“什么叫‘有穷个’？”

「就是有一个确切的数目啦… 只要有一个自然数 $k$ 能表示这样函数的数目，那么就叫‘存在有穷个函数’哦？」

“嗯…”

「接下来，在纠缠不断增加的过程中，你也需要回答一些问题。第一种是，给出 $a,b$，你需要判断 $v_a$ 是否总是等于 $v_b$；第二种是，给出 $a$，你需要计算有多少个 $b$（$1\le b\le n$，$b$ 可以等于 $a$）使得 $v_a=v_b$ 恒成立。」

“… 题目我明白了，但是这跟人的情感有什么关系吗？”

「哈哈… 就是想逗你开心嘛，别那么严肃。」

“… 无聊。”

### 简要题意

有 $n$ 个 **正实数** 变量 $v_1,\dots,v_n$。你需要根据当前已知的条件作出判断。每次给出两种条件之一：

- 给出常数 $a,b,c,d$：表示现在已知存在无穷个 $f:\R\rightarrow\R$，使得 $\frac{f(v_a)}{f(v_b)}=\frac{v_c}{v_d}$。

- 给出常数 $a,b$：表示现在已知存在有穷个 $f:\R\rightarrow\R$，使得 $f(v_a)\ne f(v_b)$。

或者两种询问之一：

- 给出常数 $a,b$：询问 $v_a=v_b$ 是否恒成立。

- 给出常数 $a$：询问有多少个 $b$（$1\le b\le n$，$b$ 可以等于 $a$）使得 $v_a=v_b$ 恒成立。

## 说明/提示

对于全部数据，有 $1\le n,m\le 6\times 10^5$。保证操作一中 $a\ne b,c\ne d$，操作二中 $a\ne b$，操作三中 $a\ne b$。

Subtask 1（5 pts）：保证不出现操作一和操作二。

Subtask 2（10 pts）：保证不出现操作一。

Subtask 3（35 pts）：保证 $n\le 5000$。

Subtask 4（50 pts）：无特殊限制。

## 样例 #1

### 输入

```
2 2
2 1 2
3 1 2```

### 输出

```
entangled```

## 样例 #2

### 输入

```
5 7
1 1 2 3 4
3 1 2
2 1 2
3 1 2
3 3 4
4 1
4 2```

### 输出

```
separate
entangled
entangled
2
2```

## 样例 #3

### 输入

```
7 6
1 1 2 3 4
1 3 5 6 7
2 4 5
3 6 7
2 1 2
3 6 7```

### 输出

```
separate
entangled```

# 题解

## 作者：Mivik (赞：16)

## Subtask 1

你不会吗？

你真的不会吗？

## Subtask 2

要拿到这一档分，我们需要来看看操作二。

> 给出常数 $a,b$：表示现在已知存在有穷个 $f:\R\rightarrow\R$，使得 $f(v_a)\ne f(v_b)$。

有穷个函数？为什么呢？我不是应该想有多少个函数就有多少个函数吗？只需要让 $f(v_a)\ne f(v_b)$ 就可以了，它们的取值任意，那不是有无穷种函数吗…

且慢。$v_a\ne v_b$ 时确实是这样，但 $v_a=v_b$ 时呢？

我们发现当且仅当 $v_a=v_b$ 时，不存在符合条件的函数——也就是说，存在“有穷个”（零个）符合条件的函数。

于是操作二翻译过来就是：

> 给出常数 $a,b$：表示现在已知 $v_a=v_b$。

那么再看原题，不难发现就是个并查集的板子，直接做就好了。

## Subtask 3

现在来看操作一：

> 给出常数 $a,b,c,d$：表示现在已知存在无穷个 $f:\R\rightarrow\R$，使得 $\frac{f(v_a)}{f(v_b)}=\frac{v_c}{v_d}$。

沿用上面的思路，我们对 $v_a=v_b$ 和 $v_a\ne v_b$ 两种情况分别讨论。

### $v_a\ne v_b$

那么对于任意可能的 $v_c,v_d$，我们都只需要使 $f(v_a),f(v_b)$ 的取值满足上面的等式即可，当然有无穷多个函数。也就是说此时这个条件什么用都没有。

### $v_a=v_b$

首先根据初中数学 $f(v_b)\ne 0$。其次由于 $v_a=v_b$，则必有 $f(v_a)=f(v_b)$。联系上面的等式，也就是说 $v_c=v_d$ 恒成立。

于是操作一翻译过来就是：

> 给出常数 $a,b,c,d$：表示若 $v_a=v_b$，则 $v_c=v_d$。

转换为并查集的操作，也就是说当 $v_a,v_b$ 这两个变量所对应的点连通时，我们就需要在 $v_c,v_d$ 中间连一条边。由于本 Subtask 中操作总数并不多，我们每加入一条边后对前面每一个操作一都检查一下也可以通过，时间复杂度 $O(n^2)$。

## Subtask 4

遇到操作一时，如果 $v_a,v_b$ 已经连通，则直接把 $v_c,v_d$ 相连即可；否则，我们分别向 $v_a,v_b$ 所在的连通块添加一个本次操作序号的标记（用一个 $set$ 维护），表示当以后将这个连通块与其它合并时需要检查一下有没有满足这个操作一的条件。然后由于这样的连接是双向的，我们合并两个连通块时只需要对一个连通块中所有的标记检查一次即可。此时不难发现我们可以套用启发式合并的思想，每次选择标记较少的连通块检查，即可通过本题。时间复杂度 $O(n\log^2n)$。

此外要注意一次合并可能会触发多次新的合并，可以用递归或者队列实现。

[ametus.h](https://pastebin.com/U0qK4eJb) / [tears.cpp](https://pastebin.com/RjMhGcg6)



---

## 作者：kymru (赞：6)

# 题意

[[Mivik Round] 梦境彼岸 泪光 | Tears](https://www.luogu.com.cn/problem/U193833?contestId=61868)

有 $n$ 个正实数变量 $v1, ..., v_n$ 和 $m$ 个询问，根据已知条件回答询问。

每次给出两种条件之一：

+ 给出常数 $a, b, c, d$，表示现在已知存在无穷个 $f:\mathbb{R} \rightarrow \mathbb{R}$，使得 $\frac{f(v_a)}{f(v_b)} = \frac{v_c}{v_d}$
+ 给出常数 $a, b$，表示现在已知存在有穷个 $f:\mathbb{R} \rightarrow \mathbb{R}$，使得 $f(v_a) \neq f(v_b)$

其中 $f:\mathbb{R} \rightarrow \mathbb{R}$ 表示一个定义域和值域都是实数的函数。

有穷个的定义是可以用一自然数 $k$ 表示满足条件的函数个数。

或者两种询问之一：

+ 给出常数 $a, b$，询问 $v_a = v_b$ 是否恒成立。
+ 给出常数 $a$，询问 $\sum\limits_{1 \leq b \leq n} [v_a = v_b]$

初始时可以认为所有变量互不相同，之后根据条件自行判断。

对于全部数据，有 $1 \leq n, m \leq 6 \times 10^5$

# 思路

转化 + 并查集。

对于第二种条件，显然当 $v_a \neq v_b$ 时容易构造出无穷个满足条件的函数，当且仅当 $v_a = v_b$ 时能构造出零个（有穷个）满足条件的函数。因此第二种条件实际上等价于 $v_a = v_b$

对于第一种条件，若 $v_a \neq v_b$，显然容易构造出无穷个满足条件的函数，该条件无用。若 $v_a = v_b$，此时 $f(v_a) = f(v_b)$，即 $\frac{v_c}{v_d} = 1$。因此第一种条件相当于若 $v_a = v_b$，则 $v_c = c_d$

考虑用并查集维护答案。对于操作二，直接并查集合并。对于操作一，当 $n \leq 5000$ 时可以暴力 $\mathcal{O}(n^2)$ 枚举此前的操作一维护答案，可以拿到 $\texttt{Subtask 3}$ 的 $35$ 分。

对于所有数据，可以考虑给每个并查集附上与其内部结点有关的条件标记。对于第 $i$ 个操作一，若 $a, b$ 属于同一并查集，则直接合并 $c, d$ 所属的并查集；反之，向 $a, b$ 所属的并查集的根附上当前操作的标记 $i$，表示以后维护与该并查集有关的操作二时需要检查是否符合第 $i$ 个操作一的条件。

由于我们向两个并查集都加入了标记，所以检查时只需要检查其中一个并查集的标记即可。考虑使用启发式合并优化，每次检查标记数较少的并查集并且将它的条件标记加入另一并查集。注意一次合并可能会带出多次合并，因此应该使用队列存储当前需要合并的结点。

用 `set` 实现，时间复杂度为 $\mathcal{O}(n \log^2 n)$。

# 代码

```cpp
#include <cstdio>
#include <set>
#include <queue>
using namespace std;

const int maxn = 6e5 + 5;
const int maxm = 6e5 + 5;

int n, m;
int fa[maxn], siz[maxn];
int a[maxm], b[maxm], c[maxm], d[maxm];
bool vis[maxm];
set<int> st[maxn];
queue<pair<int, int> > q;

int get(int x) {
	if (fa[x] == x) {
		return x;
	}
	return fa[x] = get(fa[x]);
}

void merge(int x, int y) {
	x = get(x);
	y = get(y);
	if (x != y) {
		if (st[x].size() < st[y].size()) {
			int temp = x;
			x = y, y = temp;
		}
		for (set<int>::iterator it = st[y].begin(); it != st[y].end(); it++) {
			int cur = *it;
			if (vis[cur]) {
				continue;
			}
			if ((get(a[cur]) == x) && (get(b[cur]) == y)) {
				vis[cur] = true;
				st[x].erase(cur);
				q.push(make_pair(c[cur], d[cur]));
			} else if ((get(a[cur]) == y) && (get(b[cur]) == x)) {
				vis[cur] = true;
				st[x].erase(cur);
				q.push(make_pair(c[cur], d[cur]));
			}
		}
		for (set<int>::iterator it = st[y].begin(); it != st[y].end(); it++) {
			int cur = *it;
			if (!vis[cur]) {
				st[x].insert(cur);
			}
		}
		fa[y] = x;
		siz[x] += siz[y];
	}
}

void modify() {
	while (!q.empty()) {
		int x = q.front().first;
		int y = q.front().second;
		q.pop();
		merge(x, y);
	}
}

int main() {
	int opt;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		fa[i] = i;
		siz[i] = 1;
	}
	for (int i = 1; i <= m; i++) {
		scanf("%d", &opt);
		if (opt == 1) {
			scanf("%d%d%d%d", &a[i], &b[i], &c[i], &d[i]);
			if (get(a[i]) == get(b[i])) {
				q.push(make_pair(c[i], d[i]));
				modify();
				vis[i] = true;
				continue;
			}
			st[get(a[i])].insert(i);
			st[get(b[i])].insert(i);
		} else if (opt == 2) {
			scanf("%d%d", &a[i], &b[i]);
			q.push(make_pair(a[i], b[i]));
			modify();
		} else if (opt == 3) {
			scanf("%d%d", &a[i], &b[i]);
			puts((get(a[i]) == get(b[i])) ? "entangled" : "separate");
		} else {
			scanf("%d", &a[i]);
			printf("%d\n", siz[get(a[i])]);
		}
	}
	return 0;
}
```

---

## 作者：chaynflow (赞：5)

我们直奔正解。

其实前面的题解已经讲的比较清楚了，大概逻辑就是：

对于操作 2，3，4，其实就是几个并查集的板子：连接两个节点、查询是否在同一并查集内、查询所在并查集的节点个数。 

对于操作 1：如果 $a,b$ 连通，直接连接 $c,d$；否则先打上标记，等后面连通 $a,b$ 时合并 $c,d$，然后将所有的操作用栈等实现。

前面的两篇题解好像都是 $O(n \log^2 n)$ 的（用了 set），我们把他尝试优化到 $O(n \log n)$。

我们用 vector + 结构体来维护标记。

定义结构体用来存 $a,b,c,d$，就像操作一所定义的那样。

在打标记的时候，把 $\{a,b,c,d\}$ 直接扔到 vector 后面去，启发式合并的时候，利用**并查集**的特点，枚举小的 vector，去标记多的树上上找一找有没有这个标记的 $b$，如果没有，直接把这个标记扔到标记多 vector 的后面，如果有，**仅将这个标记的 $c,d$ 扔进操作栈中，不删除这个标记**。因为最多就 $m$ 个标记，即使不删除，也是 $O(n)$ 的。这样就保证了复杂度。

由于我们没有用 set，所以启发式合并 + vector 的复杂度是 $O(n \log n)$ 的。

亲测：在不开 O2 的情况下，我写的 set 最大点用了 376ms，而 vector 最大点用了 247ms。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 6e5 + 5;
int n, m, fa[N], sz[N], tg[N];
void init()
{
	for (int i = 1; i <= n; i++) fa[i] = i, sz[i] = 1, tg[i] = 0;
}
int cnt;
struct Tag
{
    int a, b, c, d;
    Tag(){}
    Tag(int _a, int _b, int _c, int _d):a(_a),b(_b),c(_c),d(_d){}
};
vector <Tag> tag[N];
stack <Tag> ned;
int Find(int u)
{
	if (fa[u] == u) return u;
	return fa[u] = Find(fa[u]);
}
void Union(int u, int v) // 合并
{
	int ru = Find(u), rv = Find(v);
	if (ru == rv) return;
	if (tg[ru] > tg[rv]) swap(ru, rv); // 启发式合并
	for (int i = 0; i < (int)tag[ru].size(); i++)
    {
        Tag t = tag[ru][i];
		if (Find(t.b) == rv) ned.push(Tag(t.c, t.d, 0, 0)), tg[rv]--; // 加入下一个操作，并把 rv 的 tag 数量减 1
		else tag[rv].push_back(t), tg[rv]++; // 把标记加入 rv ，并把 rv 的 tag 数量加 1
    }
	tag[ru].clear(); tg[ru] = 0; // 节约空间！
	fa[ru] = rv;
	sz[rv] += sz[ru];
}
int main()
{
	//freopen("tears.in", "r", stdin);
	//freopen("tears.out", "w", stdout);
	scanf("%d%d", &n, &m);
	init();
	while (m--)
	{
		int op, a, b, c, d, ra, rb;
		scanf("%d%d", &op, &a);
		if (op <= 3) scanf("%d", &b);
		if (op == 1) scanf("%d%d", &c, &d);
		switch (op)
		{
			case 1:
				ra = Find(a), rb = Find(b);
				if (ra == rb) Union(c, d);
				else tg[ra]++; tg[rb]++; tag[ra].push_back(Tag(a, b, c, d)); tag[rb].push_back(Tag(b, a, c, d));
				break;
			case 2:
				Union(a, b);
				break;
			case 3:
				puts((Find(a) == Find(b) ? "entangled" : "separate"));
				break;
			case 4:
				printf("%d\n", sz[Find(a)]);
				break;
		}
		while (!ned.empty())
		{
			Tag u = ned.top();
			ned.pop();
			Union(u.a, u.b);
		}
	}
	return 0;
}
```


---

## 作者：lzxyl (赞：3)

### 题目分析

有 $n$ 个正实数变量 $v_1,\dots,v_n$。我们需要根据当前已知的条件作出判断。

根据题意，这道题有两个操作，两个询问。

#### 首先来分析第一个操作：已知有无穷个 $f:\R\rightarrow\R$，使得 $\frac{f(v_a)}{f(v_b)}=\frac{v_c}{v_d}$。

第一种情况： $v_a \ne v_b$ 。
此时$f(v_a),f(v_b),v_c,v_d$ 只是成比例关系，对于解题没有帮助，考虑下一种情况。

第二种情况：$v_a = v_b$ 。
因为 $\frac{f(v_a)}{f(v_b)}=\frac{v_c}{v_d}$ 且 $v_a = v_b$，所以 $f(v_a)=f(v_b)$，所以 $v_c = v_d$ （~~这里还要知道 $f(v_b)$ 是不能为 $0$ 的哦，分母不为 $0$~~）。

所以操作一就是告诉我们当 $a=b$ 时， $c=d$（ $v_a=v_b$ 时， $v_c=v_d$ ）。

#### 接下来是第二个操作：已知存在有穷个 $f:\R\rightarrow\R$，使得 $f(v_a)\ne f(v_b)$。

有穷个？要知道在实数域，随便找两个不一样的数，都可以满足 $f(v_a)\ne f(v_b)$。所以，只有当 $v_a = v_b$ 时，才会存在有穷个 $f(v_a)\ne f(v_b)$ （其实就是一个也没有）。

所以操作二就是告诉我们 $a=b$ 的（这样 $v_a$ 才能等于 $v_b$ ）。

#### 接下来两个查询分别询问 $v_a=v_b$ 是否恒成立和有多少个 $b$ 可以使 $v_a=v_b$。

合着这两个查询我们就一起记录了呗，反正求的东西也差不多。

### 解决方法

我们可以用并查集维护数与数的关系。对于每一个操作二，因为 $a=b$ ，所以就在 $a,b$ 之间建一条边，并与之前建好的集合合并。对于每一个操作一，当 $a=b$ 时，在 $c,d$ 间建一条边，与之前的集合合并；当 $a \ne b$ 时，就分别插入 $a,b$ 两个数（当然要放在它们各自的集合里，要先找它们的祖先）。

接下来在代码里会有一些注释，请大家食用。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> PII;//建二元组
const int N=6e5+10;
int a[N],b[N],c[N],d[N];
int fa[N],vis[N],siz[N];
queue<PII> q;
set<int> st[N];
int get(int x){//寻找祖先
	if(fa[x]==x) return x;
	return fa[x]=get(fa[x]);
}
void merge(int x,int y){//合并集合 
	x=get(x),y=get(y);//先找到祖先
	if(x!=y){//不在同一集合，进行合并
		if(st[x].size()>st[y].size()) swap(x,y);//将小的集合放进大的里，提高效率
		for(set<int>::iterator it=st[x].begin();it!=st[x].end();it++){//遍历set容器
			int u=*it;
			if(vis[u]) continue;
			if((get(a[u])==x&&get(b[u])==y)||(get(a[u])==y&&get(b[u])==x)){
				vis[u]=1;
				st[y].erase(u);
				q.push({c[u],d[u]});
			}
		}
		for(set<int>::iterator it=st[x].begin();it!=st[x].end();it++){//遍历set容器
			int u=*it;
			if(!vis[u]) st[y].insert(u);
		}
		fa[x]=y;
		siz[y]+=siz[x];
	}
}
void modify(){//修改
	while(!q.empty()){
		PII u=q.front();
		q.pop();
		merge(u.first,u.second);
	}
}
int main(){
	int n,m,opt;
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		fa[i]=i;
		siz[i]=1;
	}
	for(int i=1;i<=m;i++){
		cin>>opt>>a[i];
		if(opt==1){
			cin>>b[i]>>c[i]>>d[i];
			if(get(a[i])==get(b[i])){//已处于同一集合/还未记录：va=vb
				q.push({c[i],d[i]});//va=vb => vc=vd
				modify();
				vis[i]=1;
			}
			else{//va!=vb
				st[get(a[i])].insert(i);//分别存下来
				st[get(b[i])].insert(i);//分别存下来
			}
		}
		else if(opt==2){
			cin>>b[i];
			q.push({a[i],b[i]});//有穷个(0个) => va=vb
			modify();
		}
		else if(opt==3){
			cin>>b[i];
			if(get(a[i])==get(b[i])) cout<<"entangled";//恒等
			else cout<<"separate";//不恒等
		}
		else cout<<siz[get(a[i])];
		if(opt>2&&i<m) cout<<endl;//个人加的判断换行的代码，大家可根据个人喜好进行调整
	}
	return 0;
}
```

点个赞吧~

---

## 作者：naught (赞：2)

[更好的阅读体验](https://www.cnblogs.com/naughty-naught/p/18466667)

# 泪光 | Tears

## 题意

通过函数的基本知识可以简化题意：

> 操作 $ 1 $：若 $a$ 和 $b$ 在一个块中，使 $c$ 并入 $d$ 块中。

> 操作 $ 2 $：使 $a$ 并入 $b$ 块中。

> 操作 $ 3 $：询问 $a$ 是否与 $b$ 在一个块中。

> 操作 $ 4 $：询问 $a$ 的块大小。

## Solution

不难想到并查集可做。

但观察到题目中一句话“你需要根据当前已知的条件作出判断”。也就是说每次操作 $ 2 $ 可能会使操作 $ 1 $ 条件满足，进行完操作后使其他的操作 $ 1 $ 条件满足……

比如说这组样例：

```
6 9
1 1 2 3 4
1 3 4 5 6
3 1 2
3 3 4
3 5 6
2 1 2
3 1 2
3 3 4
3 5 6
```

这样的话，很遗憾直接并查集复杂度会变成 $O(n^2)$ 

如何优化呢？

在学并查集的时候，我们知道，并查集有两种优化方法：路经压缩和启发式合并，路经压缩十分自然，那么启发式合并呢？

考虑给每个不满足条件的操作 $ 1 $ 打上标记，标记带着 $a,b,c,d$，把标记放入一个 `vector` 中，在启发式合并时枚举小的 `vector`，去有较多标记的块中看是否有带 $b$ 的标记。如果有，将标记的 $c,d$ 放入一个操作栈中（不要删除，因为 `vector` 删除中间的元素是 $O(n)$ 的）；若没有，直接将标记**整个**放入 `vector` 中即可。

这样由于标记至多只有 $m$ 个，不删除复杂度是 $O(n)$，算上启发式的 $\log n$，总复杂度为 $O(n \log n)$。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define Maxn 6000005
#define fo(i, l, r) for (int i = l; i <= r; ++i)
#define fr(i, r, l) for (int i = l; i >= r; --i)
// #define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
// char buf[1<<21], *p1 = buf, *p2 = buf;
inline int read(int x=0, bool f=0, char c=getchar()) {for(;!isdigit(c);c=getchar()) f^=!(c^45);for(;isdigit(c);c=getchar()) x=(x<<1)+(x<<3)+(c^48);return f?-x:x;}
inline ll lread(ll x=0, bool f=0, char c=getchar()) {for(;!isdigit(c);c=getchar()) f^=!(c^45);for(;isdigit(c);c=getchar()) x=(x<<1)+(x<<3)+(c^48);return f?-x:x;}

int n, m, fa[Maxn], siz[Maxn], tag_to_point[Maxn];

struct Tag
{
    int a, b, c, d;
    Tag() {}
    Tag(int a, int b, int c, int d) : a(a), b(b), c(c), d(d) {}
};

vector<Tag> tag[Maxn];
stack<Tag> stk;

int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }

void merge(int x, int y)
{
    int fx = find(x), fy = find(y);
    if( fx == fy ) return ;
    if(tag_to_point[fx] > tag_to_point[fy]) swap(fx, fy);
    for(Tag x : tag[fx])
    {
        if(find(x.b) == fy) stk.push(Tag(x.c, x.d, 0, 0));
        else tag[fy].push_back(x), ++tag_to_point[fy];
    } 
    fa[fx] = fy;
    siz[fy] += siz[fx], siz[fx] = 0;
}

int query(int x) { return siz[find(x)]; }

void Init() { fo(i, 1, n) fa[i] = i, siz[i] = 1, tag_to_point[i] = 0; }

int main()
{
    n = read(), m = read();
    Init();
    fo(i, 1, m) 
    {
        int op = read();
        if(op == 1) 
        {
            int a = read(), b = read(), c = read(), d = read(), fa = find(a), fb = find(b);
            if(fa == fb) merge(c, d);
            else ++tag_to_point[fa], ++tag_to_point[fb], tag[fa].push_back(Tag(a, b, c, d)), tag[fb].push_back(Tag(b, a, c, d));
        }
        else if(op == 2) {int a = read(), b = read(); merge(a, b);}
        else if(op == 3) {int a = read(), b = read(); puts(find(a) == find(b) ? "entangled" : "separate");}
        else {int a = read(); printf("%d\n", query(a));}
        while( ! stk.empty() ) {Tag x = stk.top(); stk.pop(); merge(x.a, x.b);}
    }
    return 0;
}

```

## Tips

记得初始化。

---

## 作者：xixisuper (赞：1)

# P8149 泪光 | Tears 题解

昨天去看 abc G，机房里同学说跟本题是同一个 trick，于是花了一点时间把本题做出来了。

## 思路

先把那两个看起来就很不友好的条件转化一下：

> - 存在无穷个 $f:\R\rightarrow\R$，满足 $\frac{f(v_a)}{f(v_b)}=\frac{v_c}{v_d}$
>
> 当 $v_a\ne v_b$ 的时候，显然 $\frac{f(v_a)}{f(v_b)}$ 是啥都有可能，所以这条限制跟没有一样。
>
> 当 $v_a = v_b$ 的时候，显然 $\frac{f(v_a)}{f(v_b)}=1$，所以此时 $v_c=v_d$。
>
> 那么我们就能够把这个条件等价转化为：**当 $v_a=v_b$ 时可知 $v_c=v_d$。**


> - 存在有穷个  $f:\R\rightarrow\R$，满足 $f(v_a)\ne f(v_b)$
>
> 当 $v_a\ne v_b$ 时，由于我们并不知道 $f$ 的映射方式，所以显然会存在无穷个不同的映射 $f$ 满足上述条件。就举个最简单的例子，假设 $f$ 是一个正比例函数，那么就能够满足 $f(v_a)\ne f(v_b)$，然而显然不同的正比例函数有无穷个，所以只能是 $v_a\ne v_b$ 这一假设是错的。
>
> 当 $v_a=v_b$ 时，$f(v_a)=f(v_b)$，而 $0$ 个满足条件的 $f$ 也是有穷个 $f$。
>
> 那么我们就能够把这个条件等价转化为：**已知 $v_a=v_b$**。

操作 $3$ 显然只需要用并查集维护一下连通性即可，操作 $4$ 显然只需要额外维护一个并查集的大小就可以了，而操作 $2$ 显然就是并查集的合并操作。

考虑如何进行操作 $1$，不难想的是把每一个操作 $1$ 的标记打到 $a,b$ 上，当你发现 $a,b$ 被合并到一起后就进行合并 $c,d$ 的操作。在并查集的根上额外维护一个 `set`，用来存储该集合中所包含的操作 $1$ 即可。

在并查集合并时，把 `set` 的小的合并到大的一方，可知 `set` 里的每个元素最多被合并 $\log$ 次，再加上 `set` 自带的 $\log$，并把 $n,q$ 视为等阶，时间复杂度就是 $O(n\log^2n)$ 的，足够通过本题。

注意合并之后可能会触发多次操作 $1$，而操作 $1$ 又会触发合并，所以需要通过一个类似队列状物去维护这一过程。

## 代码

本题想明白了代码就不难写了。

```cpp
#include <iostream>
#include <set> 
#include <algorithm>
#define ll long long
using namespace std;
const ll N=7e5+10;
ll n,q,fa[N],siz[N];
set<ll> st[N];
inline ll findf(ll x){return (fa[x]==x)?x:(fa[x]=findf(fa[x]));}
pair<ll,ll> dat[N],ask[N];
ll frt=1,top;
inline void mege(ll x,ll y){
	x=findf(x),y=findf(y);
	if(x!=y){
		if(st[x].size()>st[y].size()) swap(x,y);
		while(!st[x].empty()){
			set<ll>::iterator it=st[x].begin();
			if(st[y].find(*it)!=st[y].end()){
				dat[++top]=ask[*it];
				st[y].erase(*it);
			}
			else st[y].insert(*it);
			st[x].erase(it);
		}
		fa[x]=y;
		siz[y]+=siz[x];
	} 
}
void solve(){
	while(frt<=top){
		mege(dat[frt].first,dat[frt].second);
		frt++;
	}
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>q;
	for(ll i=1;i<=n;i++) fa[i]=i,siz[i]=1;
	while(q--){
		ll opt,a,b,c,d;
		cin>>opt;
		if(opt==1){
			cin>>a>>b>>c>>d;
			ask[q].first=c;
			ask[q].second=d;
			if(findf(a)==findf(b)) dat[++top]=make_pair(c,d),solve();
			else st[findf(a)].insert(q),st[findf(b)].insert(q);
		}
		if(opt==2){
			cin>>a>>b;
			dat[++top]=make_pair(a,b);
			solve();
		}
		if(opt==3){
			cin>>a>>b;
			if(findf(a)==findf(b)) cout<<"entangled\n";
			else cout<<"separate\n";
		}
		if(opt==4){
			cin>>a;
			cout<<siz[findf(a)]<<"\n";
		}
	}
	return 0;
}
```

---

