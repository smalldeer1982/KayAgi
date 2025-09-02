# Queue

## 题目描述

On a cold winter evening our hero Vasya stood in a railway queue to buy a ticket for Codeforces championship final. As it usually happens, the cashier said he was going to be away for 5 minutes and left for an hour. Then Vasya, not to get bored, started to analyze such a mechanism as a queue. The findings astonished Vasya.

Every man is characterized by two numbers: $ a_{i} $ , which is the importance of his current task (the greater the number is, the more important the task is) and number $ c_{i} $ , which is a picture of his conscience. Numbers $ a_{i} $ form the permutation of numbers from $ 1 $ to $ n $ .

Let the queue consist of $ n-1 $ people at the moment. Let's look at the way the person who came number $ n $ behaves. First, he stands at the end of the queue and the does the following: if importance of the task $ a_{i} $ of the man in front of him is less than $ a_{n} $ , they swap their places (it looks like this: the man number $ n $ asks the one before him: "Erm... Excuse me please but it's very important for me... could you please let me move up the queue?"), then he again poses the question to the man in front of him and so on. But in case when $ a_{i} $ is greater than $ a_{n} $ , moving up the queue stops. However, the man number $ n $ can perform the operation no more than $ c_{n} $ times.

In our task let us suppose that by the moment when the man number $ n $ joins the queue, the process of swaps between $ n-1 $ will have stopped. If the swap is possible it necessarily takes place.

Your task is to help Vasya model the described process and find the order in which the people will stand in queue when all the swaps stops.

## 样例 #1

### 输入

```
2
1 0
2 1
```

### 输出

```
2 1 ```

## 样例 #2

### 输入

```
3
1 3
2 3
3 3
```

### 输出

```
3 2 1 ```

## 样例 #3

### 输入

```
5
2 3
1 4
4 3
3 1
5 2
```

### 输出

```
3 1 5 4 2 ```

# 题解

## 作者：MaxDYF (赞：5)

看到绝大部分大佬都写的$SPlay$ ，但是我太弱了根本不会$Splay$ , 所以只能写暴力了。





首先把整个序列**大力分块**，对每个块维护**最大重要值**，然后每次有人来排队，先一步一步跳出**当前块**，因为有了块的最大值，所以可以一大块一大块跳，最后不能跳时，再一步一步跳，这样就找到了排队的位置。



但是很明显，找到位置后还要插入新数值，可能会对后面的**所有块**有影响，所以就不能直接维护最大值了。这里我们给每一个块一个$set$和$deque$，用$set$维护最大值，$deque$存块内队列，每次插入之后，不断把块内**最后一个元素**弹到后面一个块的**最前面**去，同时维护最大值。



查找插入位置复杂度为$O(m\frac{n}{block})$，插入+调整后面块复杂度为$O(m\frac{n\ log \ block}{block})$，取$block=\sqrt{n \ log\ n}$，则总复杂度为$O(m\ \frac{n\ log\ \sqrt{n\ log\ n}}{\sqrt{n\ log\ n}})$，再加上$O2$优化和打消同步，这题就A了。



代码:

```cpp
#pragma GCC optimize(3)
#include <bits/stdc++.h>
using namespace std;
deque<int> a[10000];
set<int> s[10000];
int ipt[1000000], c[1000000];
int lb[1000000], rb[1000000];
int block;
int lnk[1000000];
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        // cin >> ipt[i] >> c[i];
        ipt[i] = c[i] = i;
    }
    block = sqrt(n * log2(n));
    for (int i = 0; i < n; i++)
    {
        if (i % block == 0)
            lb[i / block] = i;
        rb[i / block] = i;
        lnk[i] = i / block;
    }
    for (int i = 0; i < n; i++)
    {
        int pos = i;
        if (i)
        {
            if (i == 19)
            {
                i = 19;
            }
            // jump to the front of present block
            while (pos != lb[lnk[pos]] && ipt[i] > ipt[a[lnk[i]][pos - lb[lnk[i]] - 1]] && c[i]-- > 0)
                pos--;
            // jump above blocks
            while (pos == lb[lnk[pos]] && lnk[pos] && (c[i] >= block && (*s[lnk[pos] - 1].rbegin()) < ipt[i]))
            {
                pos = lb[lnk[pos] - 1];
                c[i] -= block;
            }
            // jump in the last block
            if (pos == lb[lnk[pos]] && c[i]-- > 0 && lnk[pos] && ipt[a[lnk[pos] - 1].back()] < ipt[i])
            {
                pos--;
                while (c[i]-- > 0 && pos != lb[lnk[pos]] && ipt[i] > ipt[a[lnk[pos]][pos - lb[lnk[pos]] - 1]])
                    pos--;
            }
        }
        a[lnk[pos]].insert(a[lnk[pos]].begin() + pos - lb[lnk[pos]], i);
        s[lnk[pos]].insert(ipt[i]);
        int now = lnk[pos];
        while (a[now].size() > block)
        {
            a[now + 1].push_front(a[now].back());
            s[now + 1].insert(ipt[a[now].back()]);
            s[now].erase(ipt[a[now].back()]);
            a[now].pop_back();
            now++;
        }
        /*
        for(int i = 0; i < ceil((double)n / (double)block); i++)
            for(auto x : a[i])
                cout << x + 1 << ' ';
            cout << endl;
        */
    }
    int t = ceil((double)n / (double)block);
    for (int i = 0; i < t; i++)
        for (auto x : a[i])
            cout << x + 1 << ' ';
}

```





---

## 作者：tangyigeng (赞：4)

### 简要题意
每次加入一个数 $a_i$ 要交换到第一个大于 $a_i$ 的数后面，且至多交换 $c_i$ 次。最后输出这个序列。

### 分析
因为要将 $a_i$ 交换到交换到第一个大于 $a_i$ 的数后面，所以我们肯定至少需要维护一个区间最大值，考虑到还会修改，所以这道题用平衡树维护，这里我是用 fhq treap 维护的。

由于最多只能交换 $c_i$ 次，所以不妨直接把 $i - c$ 到 $i - 1$ 分裂出来，这样分裂后交换后的 $a_i$ 就只可能在这个区间里面，然后在这个区间里面找到第一个大于 $a_i$ 的数。

接下来根据平衡树的性质找区间里的第一个大于 $a_i$ 的数，如果右儿子的最大值满足就递归右儿子，如果根满足就直接返回，如果左儿子满足就递归左儿子。由于是找第一个大于 $a_i$ 的数，所以必须按照先找右儿子再找根最后再找左儿子的顺序。

然后把 $a_i$ 加入到第一个大于 $a_i$ 的数的后面，最后中序遍历输出即可。

### 代码
```cpp
#include<cstdio>
#include<iostream>
#include<random>
#define ls(x) treap[x].lson
#define rs(x) treap[x].rson
using namespace std;
namespace AKIOI{
    const int N = 1e5, inf = 2e9;
    struct node{
        int val, id, max, size, pri, lson, rson;
    } treap[N + 10];
    int n;
    int Root, cnt;
    random_device R;
    mt19937 G(R());
    int rd(int l, int r){
        return uniform_int_distribution<int>(l, r)(G);
    }
    void newnode(int &u, int val, int id){
        u = ++cnt;
        treap[u].pri = rd(1, inf);
        treap[u].size = 1;
        treap[u].val = treap[u].max = val;
        treap[u].id = id;
        ls(u) = rs(u) = 0;
    }
    void push_up(int u){
        treap[u].size = treap[ls(u)].size + treap[rs(u)].size + 1;
        treap[u].max = max(max(treap[ls(u)].max, treap[rs(u)].max), treap[u].val);
    }
    void merge(int &u, int root_l, int root_r){
        if(!root_l || !root_r)
            return void(u = root_l | root_r);
        if(treap[root_l].pri >= treap[root_r].pri){
            u = root_l;
            merge(rs(root_l), rs(root_l), root_r);
        }
        else{
            u = root_r;
            merge(ls(root_r), root_l, ls(root_r));
        }
        push_up(u);
    }
    void split_size(int u, int &root_l, int &root_r, int cri){
        if(!u)
            return void(root_l = root_r = 0);
        if(treap[ls(u)].size + 1 <= cri){
            root_l = u;
            split_size(rs(root_l), rs(root_l), root_r, cri - treap[ls(u)].size - 1);
        }
        else{
            root_r = u;
            split_size(ls(root_r), root_l, ls(root_r), cri);
        }
        push_up(u);
    }
    int find(int u, int a){//返回以u为根的子树里第一个大于a的数的下标
        if(treap[rs(u)].max > a)
            return find(rs(u), a) + treap[ls(u)].size + 1;
        else if(treap[u].val > a)
            return treap[ls(u)].size + 1;
        else if(treap[ls(u)].max > a)
            return find(ls(u), a);
        else
            return 0;
    }
    void dfs(int u){
        if(!u)
            return;
        dfs(ls(u));
        printf("%d ", treap[u].id);
        dfs(rs(u));
    }
    int main(){
        scanf("%d", &n);
        for(int i = 1; i <= n; i++){
            int a, c;
            scanf("%d%d", &a, &c);
            int root_l, root_r, root_r_l, root_r_r, son;
            split_size(Root, root_l, root_r, i - c - 1);//分裂出下标大于i-c-1的数，即大于等于i-c的数
            split_size(root_r, root_r_l, root_r_r, find(root_r, a));//找到第一个大于a的数
            newnode(son, a, i);//插入
            merge(root_r_r, son, root_r_r);
            merge(root_r, root_r_l, root_r_r);
            merge(Root, root_l, root_r);
        }
        dfs(Root);
        return 0;
    }
}
int main(){
    return AKIOI::main();
}
```


---

## 作者：EnofTaiPeople (赞：3)

$\text{AVL Tree}$

这是最早被发明的平衡二叉搜索树。

看到这题不需要翻转，自然使用它会更快更好写。

维护一个 $a$ 数组的最大值，在树中查询靠右连续小于的数的个数，这个在平衡树上剪枝可以做到 $O(\log_2n)$。

最后代码加 `fread` 都比能找到的伸展树短，并成为了最优解。

1.61KB，1.24s 的 AC 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e5+5;
namespace fast_io{
    char buf[N+5],*p1,*p2;
    int ot,t,c;
    #define gc (p1==p2&&(p2=(p1=buf)+fread(buf,1,N,stdin),p1==p2)?EOF:*p1++)
    inline int read(){
        int an=0,f=1;while(!isdigit(c=gc))if(c=='-')f=-f;
        do an=an*10+(48^c);while(isdigit(c=gc));return an*f;
    }
    char ob[N+20],stk[20];
    inline void fls(){
        fwrite(ob,1,ot,stdout),ot=0;
    }
    inline void write(ll x,char c=' '){
        if(x<0)ob[ot++]='-',x=-x;
        while(x>9)stk[++t]=48^(x%10),x/=10;
        for(ob[ot++]=48^x;t;ob[ot++]=stk[t--]);
        ob[ot++]=c;if(ot>N)fls();
    }
}
using fast_io::read;
using fast_io::write;
int n,a[N],mx[N],sz[N],d[N];
int t[N][2],tp,nw,rt;
#define ls t[x][0]
#define rs t[x][1]
inline void pp(int x){
    sz[x]=sz[ls]+sz[rs]+1;
    d[x]=max(d[ls],d[rs])+1;
    mx[x]=max({mx[ls],mx[rs],a[x]});
}
inline void rot(int &x,int k){
    int y=t[x][k];t[x][k]=t[y][!k];
    pp(t[y][!k]=x),pp(x=y);
}
int qry(int x=rt){
    if(!x)return 0;
    if(a[tp]<=a[x])return qry(rs);
    if(a[tp]>mx[rs])return sz[rs]+1+qry(ls);
    else return qry(rs);
}
void Ins(int &x=rt){
    if(!x){pp(x=tp);return;};
    int k;
    if(nw>sz[rs])nw-=sz[rs]+1,k=0;
    else k=1;
    int &y=t[x][k];
    Ins(y);
    if(d[y]>d[t[x][!k]]+1){
        if(d[t[y][!k]]>d[t[y][k]])rot(y,!k);rot(x,k);
    }else pp(x);
}
void putans(int x=rt){
    if(x)putans(ls),write(x),putans(rs);
}
int main(){
    n=read();
    for(tp=1;tp<=n;++tp){
        a[tp]=read();
        nw=min(read(),qry());
        Ins(rt);
    }putans();
    fast_io::fls();
    return 0;
}
```

---

## 作者：Linghua_dog (赞：1)

看到题的时候发现他有两个限制，那么先不考虑 $c_i$ 的影响，发现就是一个维护数列从大到小的数据结构，这里想到用 splay 实现，那么再考虑 $c_i$ 其实就是每个插入的点只能在 $i - c_i \sim i - 1$ 这个区间内插入，那么思路就出来了，在正常 splay 的基础上维护一个最大值，插入时看一下是否大于当前的右儿子以及本身的最大值，如果是，那么就往左儿子递归，否则往右儿子递归，如果区间插入则先把区间左端点转到根即可，注意这里 splay 维护的中序是下标，不是 $a_i$ 的大小。

```cpp
#include <iostream>
#include <cstring>
#include <algorithm>

#define rep(i, a, b) for(int i = (a); i <= (b); i++)

using namespace std;

const int N = 1e5 + 10;

int root;
struct tree
{
	int s[2];
	int p, siz, id;
	int maxx;
}tr[N];
int idx;
int a[N], c[N];

void pushup(int u)
{
	tr[u].maxx = max({tr[tr[u].s[0]].maxx, tr[tr[u].s[1]].maxx, a[u]});
	tr[u].siz = tr[tr[u].s[0]].siz + tr[tr[u].s[1]].siz + 1;
}

void rotate(int x)
{
	int y = tr[x].p, z = tr[y].p;
	int k = tr[y].s[1] == x;
	tr[z].s[(tr[z].s[1] == y)] = x, tr[x].p = z;
	tr[y].s[k] = tr[x].s[k ^ 1], tr[tr[x].s[k ^ 1]].p = y;
	tr[x].s[k ^ 1] = y, tr[y].p = x;
	pushup(y), pushup(x);
}

void splay(int x, int k)
{
	while(tr[x].p != k)
	{
		int y = tr[x].p, z = tr[y].p;
		if(z != k)
		{
			if((tr[y].s[1] == x) ^ (tr[z].s[1] == y)) rotate(x);
			else rotate(y);
		}
		rotate(x);
	}
	if(!k) root = x;
}

int get_k(int k)
{
	int u = root;
	while(true)
	{
		if(tr[tr[u].s[0]].siz >= k) u = tr[u].s[0];
		else if(tr[tr[u].s[0]].siz + 1 == k) return u;
		else k -= tr[tr[u].s[0]].siz + 1, u = tr[u].s[1];
	}
	return -1;
}

void insert(int &x, int fa, int val)
{
	if(!x)
	{
		x = ++idx;
		tr[x].p = fa;
		tr[x].maxx = val;
		tr[x].siz = 1;
		return ;
	} 
 	
	if(val > tr[tr[x].s[1]].maxx && val > a[x]) insert(tr[x].s[0], x, val);
	else insert(tr[x].s[1], x, val);
	pushup(x);
}

void output(int u)
{
	if(tr[u].s[0]) output(tr[u].s[0]);
	cout << u << ' ';
	if(tr[u].s[1]) output(tr[u].s[1]);
}

int main()
{
	int n;
	
	cin >> n;
	rep(i, 1, n)
	{
		cin >> a[i] >> c[i];
		if(i - 1 <= c[i]) insert(root, 0, a[i]);
		else
		{
			int l = get_k(i - c[i] - 1);
			splay(l, 0);
			insert(tr[l].s[1], l, a[i]);
		}
		splay(idx, 0);
	}
	
	output(root);
}
```

---

## 作者：zesqwq (赞：1)

# CF38G Queue 题解

[题目传送门](https://www.luogu.com.cn/problem/CF38G)

题解中总共就一篇是讲解关于分块的，但是那一篇并没有达到分块可以达到 $O(\sqrt n)$ 的较快速度。

我们考虑把一个序列分成 $O(\sqrt n)$ 块，每块有 $O(\sqrt n)$ 个数。然后我们维护一个块中的最大重要值。

我们的一个操作分为 $2$ 部分，查询位置，然后插入。查询位置可以暴力扫到第一个良心不够用或有最大重要值比要插入的重要值更大的块，然后暴力扫这个块。插入操作就是根据查询信息 $O(\sqrt n)$ 暴力插入，然后当某个块大小超过一个阈值时暴力重构就行了。

$\text{Code:}$

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10, M = 1000;
int len[M], lzy[M], maxa[N], tot;
struct Point {
    int a, c, id;
    inline void read() { scanf("%d %d", &a, &c); }
} a[M][M];
struct Node {
    int col, pos;
};
void rebuild() {
    int cur = 0;
    for (int i = 1; i <= tot; i++) pushdown(i), maxa[i] = 0;
    for (int i = 1; i <= tot; i++)
        for (int j = 1; j <= len[i]; j++) vals[++cur] = a[i][j];
    for (int i = 1; i <= tot; i++) len[i] = 0;
    int s = sqrt(cur), pos;
    for (int i = 1; i <= cur; i++) {
        pos = (i - 1) / s + 1;
        a[pos][++len[pos]] = vals[i];
        maxa[pos] = max(maxa[pos], vals[i].a);
    }
    tot = (cur - 1) / s + 1;
}
void insert(Node x, Point v) {
    ++len[x.col];
    for (int i = len[x.col]; i > x.pos; i--) a[x.col][i] = a[x.col][i - 1];
    a[x.col][x.pos] = v, maxa[x.col] = max(maxa[x.col], v.a);
    if (len[x.col] >= 1000) rebuild();
}
inline void pushdown(int x) {
    if (!lzy[x]) return;
    for (int i = 1; i <= len[x]; i++) a[x][i].c -= lzy[x];
    lzy[x] = 0;
}
Point vals[N];
Node find(Point &v) {
    for (int i = tot; i; i--) {
        if (maxa[i] > v.a || len[i] >= v.c)
            for (int j = len[i]; ~j; j--) {
                if (!v.c || a[i][j].a > v.a) return {i, j + 1};
                --v.c;
            }
        v.c -= len[i];
    }
    return {1, 1};
}
int main() {
    memset(maxa, 0, sizeof(maxa));
    int n;
    cin >> n;
    Point r;
    for (int i = 1; i <= n; i++) {
        r.read(), r.id = i;
        if (!tot)
            ++tot, a[1][len[1] = 1] = r, rebuild();
        else
            insert(find(r), r);
    }
    int cur = 0;
    for (int i = 1; i <= tot; i++) pushdown(i), maxa[i] = 0;
    for (int i = 1; i <= tot; i++)
        for (int j = 1; j <= len[i]; j++) vals[++cur] = a[i][j];
    for (int i = 1; i <= cur; i++) printf("%d ", vals[i].id);
    return 0;
}
```

---

## 作者：a999999 (赞：1)

乍一看这题有点难，实际上是很简单的

题目翻译有点问题：

输出的应该是排好队后**每个人的编号**，翻译中没有讲清楚（导致我错了4遍...）

首先，假设没有$c_i$的限制，这题就成了一道简单的排序题，可以用平衡树、跳表$\cdots$来解决，这里我们使用Splay。

有了$c_i$的限制后，我们发现第i个人的位置只能在$i-c_i,i-c_i+1, \cdots i$这些位置。如果$i>c_i+1$的话，$1,2\cdots i-c_i-1$这些位置是不能通过交换到达的。

所以，我们可以建一棵**区间splay**，节点间的关系不是依靠值而是依靠位置，即每个节点构成的子树代表了这些人构成的一段区间。同时在每个节点上记录区间大小和区间最大值，方便我们接下来的操作。

每次操作时，若$i>c_i+1$，把前$i-c_i-2$个数拉到根的左子树里，第$i-c_i-1$个数作为根，在根的右子树里插入第$i$个人。插入时，判断当前这个人的$a_i$是否大于**右子树**的最大值以及当前递归到的节点，如果是就往**左子树**递归（说明这个人可以和右子树**对应区间**的人全部交换而到达左子树），否则就往**右子树**递归。

如果$i<c_i+1$，则表明当前这个人可以与Splay内任何一个人交换，直接从**根**开始递归。

记得每次操作完之后将新插入的节点$splay$到根，保证Splay的复杂度。最后输出的时候用**中序遍历**，你懂的。

时间复杂度$\Theta(N\log_2 N)$

## $code$:
```cpp
#include<algorithm>
#include<cstdio>
#define N 100010
using namespace std;
int a[N],c[N],n;
int val[N],siz[N],maxn[N],fa[N],ch[N][2],len,root;
int read()
{
	static int res;static char op;
	do op=getchar();while(op>'9'||op<'0');
	for(res=0;op>='0'&&op<='9';op=getchar())res=res*10+(op^48);
	return res;
}
bool relation(int x){return ch[fa[x]][1]==x;}
void update(int x)
{
	siz[x]=siz[ch[x][0]]+siz[ch[x][1]]+1;
	int p=a[val[x]],ch1=a[maxn[ch[x][0]]],ch2=a[maxn[ch[x][1]]];
	if(p>ch1&&p>ch2)maxn[x]=val[x];
	else if(ch1>ch2)maxn[x]=maxn[ch[x][0]];
	else maxn[x]=maxn[ch[x][1]];
}
void rotate(int x)
{
	int f=fa[x],ff=fa[f],k=relation(x),y=ch[x][!k];
	fa[f]=x;fa[x]=ff;fa[y]=f;
	ch[x][!k]=f;ch[f][k]=y;ch[ff][ch[ff][1]==f]=x;
	update(f);update(x);
}
void _splay(int x,int p)
{
	for(int f;fa[x]!=p;rotate(x))
		if(fa[f=fa[x]]!=p)
			rotate(relation(x)^relation(f)?x:f);
	if(!p)root=x;
}
int _find(int rank)
{
	int now=root;
	while(siz[ch[now][0]]+1!=rank)
	{
		if(siz[ch[now][0]]>=rank)
			now=ch[now][0];
		else rank-=siz[ch[now][0]]+1,now=ch[now][1];
	}
	return now;
}
void ins(int&x,int f,int v)
{
	if(!x)
	{
		x=++len;
		fa[x]=f;maxn[x]=val[x]=v;siz[x]=1;
		return;
	}
	if(a[v]>a[maxn[ch[x][1]]]&&a[v]>a[val[x]])
		ins(ch[x][0],x,v);
	else ins(ch[x][1],x,v);
	update(x);
}
void print(int x)
{
	if(ch[x][0])print(ch[x][0]);
	printf("%d ",val[x]);
	if(ch[x][1])print(ch[x][1]);
}
signed main(int argc,char **argv)
{
	n=read();
	for(int i=1;i<=n;++i)
		a[i]=read(),c[i]=read();
	for(int i=1;i<=n;++i)
	{
		if(i-c[i]>1)
		{
			_splay(_find(i-c[i]-1),0);
			ins(ch[root][1],root,i);
		}
		else ins(root,0,i);
		_splay(len,0);
	}
	print(root);
	return 0;
}
```

---

## 作者：黑影洞人 (赞：0)

数据结构好题。

题意：给你一个排列，$n$ 对数据 $a,c$，依次插入，对于每个 $i$，寻找左边连续一段长度小于等于 $c_i$ 的段，要求该段的 $a$ 值都比当前的 $a_i$ 值小，尽可能长，然后把当前数据插入该段段首，最后输出最终的序列。

看到插入的操作，很容易联想到平衡树，我们用 FHQ-treap 维护序列，然后记录每个节点的最大值。

这样在不考虑 $c$ 的情况下，我们可以求出一个值左边连续的最长的全部小于等于该值的段的长度。

```cpp
int query(int x,int pos){
	if(!x)return 0;
	if((!lc)&&(!rc))return val[x]<a[pos];
	if(mx[rc]>=a[pos]||val[x]>=a[pos])return query(rc,pos);
	else return query(lc,pos)+1+siz[rc];
}
```
调用这个函数可以求出以 $x$ 为根的平衡树中右端连续的比 $a_{pos}$ 小的段。

分三类讨论即可，没有子节点直接判断自己符不符合，右节点最大值等于如果大于 $a_{pos}$ 那么就不用调用左节点，若小于，则全部算入贡献。

然后插入的话也要分类。

如果当前的连续长度大于 $c_i$ 那么就可以不管长度，否则要减去多余的长度。

```cpp
if(i-1<=c[i]){
	int x,y;
	t.split(rt,i-t.query(rt,i)-1,x,y);
	rt=t.merge(x,t.merge(t.newnode(a[i]),y));	
}else{
	int x,y,z;
	t.split(rt,i-c[i]-1,x,y);
	t.split(y,c[i]-t.query(y,i),y,z);
	rt=t.merge(t.merge(x,y),t.merge(t.newnode(a[i]),z));
}
```
完整代码：

```cpp
#include<cstdio>
#include<algorithm>
#define N 114514
using namespace std;
int seed,md=19260817;
void _srand(int x){seed=x;}
int _rand(){seed=((seed*7%md)+13)%md;return seed;}
int n,a[N],c[N];
int rt;
struct fhq_treap{
	int ch[N][2],rnd[N],siz[N],val[N],mx[N],tot;
	#define lc ch[x][0]
	#define rc ch[x][1]
	int pushup(int x){
		siz[x]=siz[lc]+siz[rc]+1;
		mx[x]=max(mx[lc],max(val[x],mx[rc]));
		return x;
	}
	void split(int p,int k,int &x,int &y){
		if(!p)return void(x=y=0);
		if(k>siz[ch[p][0]])split(ch[x=p][1],k-siz[ch[p][0]]-1,ch[p][1],y);
		else split(ch[y=p][0],k,x,ch[p][0]);
		pushup(p);
	}
	int merge(int x,int y){
		if(!x||!y)return x+y;
		if(rnd[x]<rnd[y]){rc=merge(rc,y);return pushup(x);}
		else{ch[y][0]=merge(x,ch[y][0]);return pushup(y);}
	}
	int query(int x,int pos){
		if(!x)return 0;
		if((!lc)&&(!rc))return val[x]<a[pos];
		if(mx[rc]>=a[pos]||val[x]>=a[pos])return query(rc,pos);
		else return query(lc,pos)+1+siz[rc];
	}
	int newnode(int v){
		int x=++tot;
		val[x]=v,mx[x]=v,siz[x]=1;
		rnd[x]=_rand();
		return x;
	}
	void print(int x){
		if(lc)print(lc);
		printf("%d ",x);
		if(rc)print(rc);
	}
}t; 
signed main(){
	_srand(1966);
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d%d",&a[i],&c[i]);
		if(i-1<=c[i]){
			int x,y;
			t.split(rt,i-t.query(rt,i)-1,x,y);
			rt=t.merge(x,t.merge(t.newnode(a[i]),y));
		}else{
			int x,y,z;
			t.split(rt,i-c[i]-1,x,y);
			t.split(y,c[i]-t.query(y,i),y,z);
			rt=t.merge(t.merge(x,y),t.merge(t.newnode(a[i]),z));
		}	
	}
	t.print(rt);
	return 0;
}
```

---

## 作者：FatOldEight (赞：0)

发现大多都是 Splay 的，来水一个 FHQ 的。

[更好的阅读体验](https://fat-old-eight.github.io/%E9%A2%98%E8%A7%A3/2023/03/10/solution-cf38g.html)

### 做法
首先为了方便实现，我们先将整个队列反转一下，原问题就变成了在队列前 $c_i$ 个数中插入一个数（位置为 $k$），使得对于任意的 $1\leq j < k \leq c_i+1$ 都有 $a_j < a_k$。（很好理解吧。）

好了现在问题就解决了，先建一个以下标为权值的 $\text{FHQ}$ 。

然后对于每次插入，先以大小分裂出 $x$ 和 $z$ 两棵树，然后再在 $x$ 中根据前缀最大值分裂出 $x$ 和 $y$ 两棵树，将新节点插入 $x$ 与 $y$ 之间即可。

输出类似中序遍历，但是要先访问右儿子。

### 代码

~~~ cpp
#include<algorithm>
#include<iostream>
using namespace std;
struct FHQ
{
    int root,cnt;
    struct sss
    {
        int l,r,s,v,w,mx,id,rmx;
        #define l(x) tree[x].l
        #define r(x) tree[x].r
        #define s(x) tree[x].s
        #define v(x) tree[x].v
        #define w(x) tree[x].w
        #define mx(x) tree[x].mx
        #define id(x) tree[x].id
        #define rmx(x) tree[x].rmx
    }tree[1000005];
    int New(int x,int id)
    {
        w(++cnt)=rand();
        s(cnt)=1;
        rmx(cnt)=v(cnt)=mx(cnt)=x;
        id(cnt)=id;
        return cnt;
    }
    void pushup(int x)
    {
        s(x)=s(l(x))+s(r(x))+1;
        mx(x)=max({mx(l(x)),mx(r(x)),v(x)});
        rmx(x)=max(mx(l(x)),v(x));
    }//维护前缀最大值
    void splits(int root,int s,int &x,int &y)
    {
        if(!root)x=y=0;
        else if(s(l(root))<s)
        {
            x=root;
            splits(r(root),s-s(l(root))-1,r(x),y);
            pushup(root);
        }
        else
        {
            y=root;
            splits(l(root),s,x,l(y));
            pushup(root);
        }
    }
    void splitv(int root,int key,int &x,int &y)
    {
        if(!root)x=y=0;
        else if(rmx(root)<=key)
        {
            x=root;
            splitv(r(root),key,r(x),y);
            pushup(root);
        }
        else
        {
            y=root;
            splitv(l(root),key,x,l(y));
            pushup(root);
        }
    }
    int merge(int x,int y)
    {
        if(!x||!y)return x^y;
        else if(w(x)>w(y))
        {
            r(x)=merge(r(x),y);
            pushup(x);
            return x;
        }
        else
        {
            l(y)=merge(x,l(y));
            pushup(y);
            return y;
        } 
    }
    void insert(int key,int c,int id)//插入
    {
        int x,y,z;
        splits(root,c,x,z);
        splitv(x,key-1,x,y);
        root=merge(merge(merge(x,New(key,id)),y),z);
    }
    void print(int x)//输出
    {
        if(r(x))print(r(x));
        printf("%d ",id(x));
        if(l(x))print(l(x));
    }
}T1;
int T;
int main()
{
    scanf("%d",&T);
    for(int i=1;i<=T;i++)
    {
        int key,c;
        scanf("%d%d",&key,&c);
        T1.insert(key,c,i);
    }
    T1.print(T1.root);
}
~~~

---

## 作者：__stick (赞：0)


## 题意

给定 $n$ 个人，每个人有一个权值 $a$ 与一个约束值  $c$，我们需要按顺序插入这  $n$ 个人，每次插入一个人后，如果这个点的权值比上一个点的权值大，则需要与上一个点交换位置，一个点最多能与  $c$ 个 点交换位置，求最后的序列。

## 思路

首先不难想到使用文艺平衡树维护这个问题，每次新来一个人，不断往前交换其实就是插入某个位置的过程，这时候就是文艺平衡树的基础操作了。然后问题就是如何找出这个插入位置。
首先 $c$ 限制了能插入的位置，是 $[i-1-c,i-1]$ 我们先用 split 操作将这个区间对应的子树提取出来，然后在这棵树上进行二分。二分出最靠右的大于等于当前 $a $ 的位置，这个维护一个区间最大值就可以了，每到一个节点就看看右子树的区间最大值，如果大于等于当前的 $a$ 那就说明右子树中可以找到某个节点满足条件，直接递归即可，如果正好是当前子树满足要求，就直接返回当前节点对应的位置，否则就递归处理左子树。

找到这个位置后就对应用 split 操作裂开这个区间，然后按顺序合并回去就行了。

然后中序遍历输出这个序列就行了。
## 代码
```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>
#include<vector>
#include<set>
#include<map>
#include<queue>
#include<bits/stdc++.h>
using namespace std;
template<typename T>
inline void cmax(T& a,const T& b){a<b?a=b:0;}
template<typename T>
inline void cmin(T& a,const T& b){b<a?a=b:0;}
typedef long long ll;
typedef pair<int,int> pii;
typedef unsigned long long ull;
typedef unsigned int ui;
typedef vector<int> vi;
typedef vector<vector<int> > vii;
#define X first
#define Y second
const int mod=998244353;
const int MAXN=2e5+10;
struct node
{
	int l,r,pr;
	int siz;
	int mmax,w,id;	
}t[MAXN];
int tt;
inline int add(int val,int id)
{
	int x=++tt;
	t[x].pr=rand();
	t[x].siz=1;
	t[x].mmax=t[x].w=val;
	t[x].id=id;
	return x;
}
#define ls t[u].l
#define rs t[u].r
inline void push_up(int u)
{
	t[u].siz=t[ls].siz+t[rs].siz+1;
	t[u].mmax=max({t[u].w,t[ls].mmax,t[rs].mmax});
}
void split(int u,int siz,int &x,int &y)
{
	if(!u)return x=y=0,void();
	if(t[t[u].l].siz+1<=siz)
	{
		x=u;split(t[x].r,siz-(t[t[u].l].siz+1),t[x].r,y);
	}
 	else y=u,split(t[y].l,siz,x,t[y].l);
	push_up(u);
}
int merge(int x,int y)
{
	if(!x||!y)return x+y;
	if(t[x].pr>t[y].pr)
	{
		t[x].r=merge(t[x].r,y);
		push_up(x);
		return x;
	}
	else 
	{
		t[y].l=merge(x,t[y].l);
		push_up(y);
		return y;
	}
}
int ask(int u,int k)
{
	if(!u)return 0;
	if(t[rs].mmax>=k)return ask(rs,k)+1+t[ls].siz;
	else if(t[u].w>=k)return ask(rs,k)+1+t[ls].siz;
	else return ask(ls,k);
}
void dfs(int u)
{
	if(!u)return;
	dfs(ls),cout<<t[u].id<<' ',dfs(rs);
}
int main()
{
	ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int T;cin>>T;
	int rt=0;
	for(int i=1;i<=T;i++)
	{
		int a,c;cin>>a>>c;
		int x=0,y=0,z=0;
		split(rt,max(0,t[rt].siz-c),x,y);
		split(y,ask(y,a),y,z);
		rt=merge(mergea(x,y),merge(add(a,i),z));
	}
	dfs(rt);

}
```


---

## 作者：shao0320 (赞：0)

看到单点插入，果断选择 $\text{FHQ Treap}$ 。

以位置作为权值建 $\text{FHQ Treap}$ ，这样单点插入的时候我们只需要通过 $\text{split}$ 操作把那个位置找出来之后申请新节点 $\text{merge}$ 即可。

首先讨论一下这个 $c_i$ 的限制是否有意义，如果无意义的话直接查询插入到的位置，有意义的话就先把那些可能被第 $i$ 个人超过的那些人 $\text{split}$ 出来后再查询。

查询的话就是维护一下子树最大值，找到一个尽量左的位置插入即可。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define N 200005
using namespace std;
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return x*f;
}
int n,a[N],c[N];
struct FHQTreap
{
	int siz[N],val[N],Mx[N],rnd[N],cnt,ch[N][2],ID[N],rt;
	int Get(int x)
	{
		siz[++cnt]=1;val[cnt]=a[x];Mx[cnt]=a[x];ID[cnt]=x;
		rnd[cnt]=rand();return cnt;
	}
	void pushup(int x)
	{
		siz[x]=1+siz[ch[x][0]]+siz[ch[x][1]];
		Mx[x]=max(max(Mx[ch[x][0]],Mx[ch[x][1]]),val[x]);
	}
	int merge(int x,int y)
	{
		if(!x||!y)return x+y;
		if(rnd[x]<rnd[y]){ch[x][1]=merge(ch[x][1],y);pushup(x);return x;}
		else{ch[y][0]=merge(x,ch[y][0]);pushup(y);return y;}
	}
	void split(int now,int k,int &x,int &y)
	{
		if(!now){x=y=0;return;}
		if(siz[ch[now][0]]+1<=k)x=now,split(ch[now][1],k-siz[ch[now][0]]-1,ch[x][1],y);
		else y=now,split(ch[now][0],k,x,ch[y][0]);
		pushup(now);
	}
	int query(int now,int p)
	{
		if(!now)return 0;
		if((!ch[now][0])&&(!ch[now][1]))return val[now]<a[p];
		if(Mx[ch[now][1]]>=a[p])return query(ch[now][1],p);
		if(val[now]>=a[p])return query(ch[now][1],p);
		return query(ch[now][0],p)+1+siz[ch[now][1]];
	}
	void insert(int p)
	{
		if(p-c[p]<=1)//the hole treap
		{
			int pos=query(rt,p);
			int A,B,C,D;
			split(rt,p-1-pos,A,B);
			rt=merge(merge(A,Get(p)),B);
		}
		else
		{
			int A,B,C,D;
			split(rt,p-c[p]-1,A,B);
			int pos=c[p]-query(B,p);
			split(B,pos,C,D);
			rt=merge(merge(merge(A,C),Get(p)),D);
		}
	}
	void print(int x)
	{
		if(!x)return;
		print(ch[x][0]);
		printf("%d ",x);
		print(ch[x][1]);
	}
}T;
int main()
{
	n=read();
	for(int i=1;i<=n;i++)
	{
		a[i]=read();c[i]=read();
		T.insert(i);
	}
	T.print(T.rt);puts("");
}

```



---

## 作者：whiteqwq (赞：0)

[CF38G Queue](https://www.luogu.com.cn/problem/CF38G)解题报告：

[更好的阅读体验](https://zybuluo.com/xiaoziyao/note/1706260)

题意：给定$n$个点，每个点有一个权值$a_i$与一个约束值$c_i$，我们需要按顺序插入这$n$个数，每次插入一个点后，如果这个点的权值比上一个点的权值大，则需要与上一个点交换位置，一个点最多能与$c_i$个点交换位置，求最后的序列。

刚看到这道题，想维护小于一个值的一个数组，但是没搞出来，于是写了个Splay。

这道题所使用的Splay是类似[【模板】文艺平衡树](https://www.luogu.com.cn/problem/P3391)的Splay，叫做区间Splay，它就是以一个点的位置为权值来维护Splay的方法。

我们先定义一个数组$maxx_i$，代表以$i$为根节点的子树中最大值存在的位置，可以很容易写出它的$pushup$方式：
```
maxx[now]=val[now];
if(a[maxx[chd[now][0]]]>a[maxx[now]])
	maxx[now]=maxx[chd[now][0]];
if(a[maxx[chd[now][1]]]>a[maxx[now]])
	maxx[now]=maxx[chd[now][1]];
```

然后我们再考虑一个点的插入，当位置为$v$，权值为$a_v$的结点插入到$x$位置后，可以发现如果$a_v$大于$x$位置的权值和$x$的右子树的$maxx$的权值的话，这个结点就可以插入到$x$的左子树，否则就可以插入到右子树。

接下来，我们开始实现解决问题的核心操作$work$函数（$p$代表位置，$c$代表约束值），我们可以分两种情况讨论一下：
1. 如果当前位置可以和前面的任意多个节点换（只要满足条件），那我们就可以直接从根插入这个节点。
2. 否则，你需要用循环（或递归）找出编号$p-c-1$的节点，并将其设为根，因为这是一颗区间Splay，所以当前节点可以和这个$p-c-1$的右子树中任意一个节点交换（只要满足条件），就可以从根的右儿子节点插入。
```
void work(int p,int c){
	if(p-c>1){
		splay(getnum(p-c-1),0);
		insert(chd[root][1],root,p);
	}
	else insert(root,0,p);
	splay(cnt,0);
}
```

最后输出用中序遍历，应该大家都会吧。

时间复杂度：$O(n\log n)$（$n$次操作，每次操作用区间Splay可以达到$\log n$的复杂度（可以用势能分析））

代码：
```
#include<stdio.h>
#define inf 1000000000
const int maxn=100005;
int i,j,k,m,n;
int a[maxn];
inline int max(int a,int b){
	return a>b? a:b;
}
struct SPLAY{
	int cnt,root;
	int val[maxn],chd[maxn][2],f[maxn],size[maxn],maxx[maxn];
	inline void init(){
		cnt=root=0;
	}
	inline int newnode(int x,int fth){
		size[++cnt]=1,chd[cnt][0]=0,chd[cnt][1]=0,val[cnt]=x,f[cnt]=fth;
		return cnt;
	}
	inline void pushup(int now){
		size[now]=size[chd[now][0]]+size[chd[now][1]]+1;
		maxx[now]=val[now];
		if(a[maxx[chd[now][0]]]>a[maxx[now]])
			maxx[now]=maxx[chd[now][0]];
		if(a[maxx[chd[now][1]]]>a[maxx[now]])
			maxx[now]=maxx[chd[now][1]];
	}
	inline int check(int now){
		return chd[f[now]][0]==now? 0:1;
	}
	inline void connect(int now,int son,int dir){
		f[son]=now,chd[now][dir]=son;
	}
	inline void rotate(int now){
		int fth=f[now],gfth=f[fth],frlt=check(now),grlt=check(fth);
		connect(gfth,now,grlt),connect(fth,chd[now][frlt^1],frlt),connect(now,fth,frlt^1);
		pushup(fth),pushup(now);
	}
	void splay(int now,int aim){
		while(f[now]!=aim){
			int fth=f[now],gfth=f[fth],frlt=check(now),grlt=check(fth);
			if(gfth!=aim)
				rotate(frlt^grlt? now:fth);
			rotate(now);
		}
		if(aim==0)	
			root=now;
	}
	int getnum(int x){
		int now=root;
		while(now){
			if(x==size[chd[now][0]]+1)
				return now;
			if(x<=size[chd[now][0]])
				now=chd[now][0];
			else x-=size[chd[now][0]]+1,now=chd[now][1];
		}
		return now;
	}
	void insert(int &x,int lst,int v){
		if(x==0){
			x=newnode(v,lst);
			return ;
		}
		if(a[v]>a[val[x]]&&a[v]>a[maxx[chd[x][1]]])
			insert(chd[x][0],x,v);
		else insert(chd[x][1],x,v);
		pushup(x);
	}
	void work(int p,int c){
		if(p-c>1){
			splay(getnum(p-c-1),0);
			insert(chd[root][1],root,p);
		}
		else insert(root,0,p);
		splay(cnt,0);
	}
	void out(int x){
		if(chd[x][0])
			out(chd[x][0]);
		printf("%d ",val[x]);
		if(chd[x][1])
			out(chd[x][1]);
	}
	void write(){
		out(root);
	}
}Splay;
int main(){
	scanf("%d",&n);
	Splay.init();
	for(i=1;i<=n;i++){
		int c;
		scanf("%d%d",&a[i],&c);
		Splay.work(i,c);
	}
	Splay.write();
	return 0;
}
```





---

