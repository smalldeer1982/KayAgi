# [CERC2007] robotic sort 机械排序

## 题目描述

SORT 公司是一个专门为人们提供排序服务的公司，该公司的宗旨是：“顺序是最美丽的”。他们的工作是通过一系列移动，将某些物品按顺序摆好。他们的工作规定只能使用如下方法排序：

![](https://cdn.luogu.com.cn/upload/pic/17272.png)

先找到编号最小的物品的位置 $P_1$，将区间 $[1,P_1]$ 反转，再找到编号第二小的物品的位置 $P_2$，将区间 $[2,P_2]$ 反转.........

上图是有 $6$ 个物品的例子，编号最小的一个是在第 $4$ 个位置。因此，最开始把前面 $4$ 个物品反转，第二小的物品在最后一个位置，所以下一个操作是把 $2\sim 6$ 的物品反转，第三步操作是把 $3\sim 4$ 的物品进行反转……

在数据中可能存在有相同的编号，如果有多个相同的编号，则按输入的原始次序操作。

## 样例 #1

### 输入

```
6
3 4 5 1 6 2```

### 输出

```
4 6 4 5 6 6```

# 题解

## 作者：宝硕 (赞：12)

更好的阅读体验：[https://oi.baoshuo.ren/cerc2007-sort/](https://oi.baoshuo.ren/cerc2007-sort/?utm_source=www.luogu.com.cn&utm_medium=uva1402_solution)

---

感谢这道题没有关闭题解通道。看到没有指针 FHQ Treap 的题解，于是来补一发留给后人参考。

其他题解都讲得挺清楚的，这里就不再细说思路了。考虑按照排名处理，每次找到最小值的排名 $k$，然后翻转区间 $[1, k]$，再删去这个最小值。对于每次操作 $k + i - 1$ 即为答案。

代码如下：

```cpp
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <limits>

using std::cin;
using std::cout;
const char endl = '\n';

const int N = 1e5 + 5;

struct node {
    node *lchild, *rchild;
    size_t size;
    unsigned key;
    int value, min;
    bool reversed;

    node()
        : lchild(nullptr),
          rchild(nullptr),
          size(0),
          key(rand()),
          value(0),
          min(std::numeric_limits<int>::max()),
          reversed(false) {}

    node(int _value)
        : lchild(nullptr),
          rchild(nullptr),
          size(1),
          key(rand()),
          value(_value),
          min(_value),
          reversed(false) {}

    ~node() {
        if (lchild != nullptr) delete lchild;
        if (rchild != nullptr) delete rchild;
    }

    inline size_t lsize() {
        return lchild == nullptr ? 0 : lchild->size;
    }

    inline size_t rsize() {
        return rchild == nullptr ? 0 : rchild->size;
    }

    inline void pushup() {
        size = lsize() + 1 + rsize();
        min = value;

        if (lchild != nullptr) {
            min = std::min(min, lchild->min);
        }

        if (rchild != nullptr) {
            min = std::min(min, rchild->min);
        }
    }

    inline void pushdown() {
        if (reversed) {
            std::swap(lchild, rchild);
            if (lchild != nullptr) lchild->reversed = !lchild->reversed;
            if (rchild != nullptr) rchild->reversed = !rchild->reversed;
            reversed = false;
        }
    }
};

int n, b[N];
std::pair<int, int> a[N];
node *root;

std::pair<node *, node *> split(node *u, int k) {
    if (u == nullptr) return std::make_pair(nullptr, nullptr);

    u->pushdown();

    if (k <= u->lsize()) {
        auto o = split(u->lchild, k);

        u->lchild = o.second;
        u->pushup();
        o.second = u;

        return o;
    }

    auto o = split(u->rchild, k - u->lsize() - 1);

    u->rchild = o.first;
    u->pushup();
    o.first = u;

    return o;
}

node *merge(node *x, node *y) {
    if (x == nullptr) return y;
    if (y == nullptr) return x;

    if (x->key < y->key) {
        x->pushdown();
        x->rchild = merge(x->rchild, y);
        x->pushup();

        return x;
    }

    y->pushdown();
    y->lchild = merge(x, y->lchild);
    y->pushup();

    return y;
}

void reverse(int k) {
    auto x = split(root, k);
    auto y = split(x.first, k - 1);
    if (y.first != nullptr) y.first->reversed = !y.first->reversed;
    delete y.second;
    root = merge(y.first, x.second);
}

int find(node *p) {
    int k = 1;

    while (p != nullptr) {
        p->pushdown();

        if (p->lchild != nullptr && p->min == p->lchild->min) {
            p = p->lchild;
        } else if (p->rchild != nullptr && p->min == p->rchild->min) {
            k += p->lsize() + 1;
            p = p->rchild;
        } else {
            return k + p->lsize();
        }
    }

    return -1;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    for (int i = 1; i <= n; i++) {
        cin >> a[i].first;

        a[i].second = i;
    }

    std::sort(a + 1, a + 1 + n);

    for (int i = 1; i <= n; i++) {
        b[a[i].second] = i;
    }

    for (int i = 1; i <= n; i++) {
        root = merge(root, new node(b[i]));
    }

    for (int i = 1; i <= n; i++) {
        int k = find(root);

        reverse(k);

        cout << k + i - 1 << ' ';
    }

    cout << endl;

    // Cleanup
    delete root;

    return 0;
}
```

---

## 作者：541forever (赞：7)

这是一道比较裸的平衡树模板题，这是一篇~~可能对细（keng）节（dian）解释比较详尽的~~屑题解。

思路与 [文艺平衡树](https://www.luogu.com.cn/problem/P3391) 相似，我们需要先增加两个哨兵节点，然后每次执行区间翻转操作时，就对区间左端点的前驱和右端点的后继进行 Splay 并把不断交换他们子节点的左右子树。而对于求解答案，我们要求的是这个节点的排名（即它在当前序列中的位置），我们可以将该节点提到根，然后统计它的左子树的大小 size（这个 size 没有算上这个节点本身，但算上了哨兵节点，所有两个影响抵消）。具体实现时，我们可以记录每个权值在平衡树中对应的节点编号记为 ``pos[i]``，然后每次翻转时找到当前节点 ``pos[i]`` 的后继，而在我们进行这一步操作前，将要操作的值前面的数已经是有序的了，所有它的前驱便是 ``pos[i-1]``。

注意：

1. 我们不太能直接以编号作为平衡树的权值进行操作，这样虽然仍能实现区间翻转，但查一个数在序列中的位置会较为麻烦。
2. 区间翻转需要提到根上的点时左端点的前驱和右端点的后继，而不是左端点和右端点（本蒟蒻就是因为这里一直不知道哪错了）。
3. 给定数组的值可能会有相等而我们需要按输入的原始次序操作，所以我们可以将原序列重新按离散的方式重新赋值。

下面是丑陋的代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,val[300005],tag[300005],ch[300005][2],tot,rt,fa[300005],si[300005],p[300005];//p记录权值在平衡树中对应的点的编号，tag作为懒标记记录是否需要交换左右子树
struct object{
    int val,num;
}ob[300005];
inline int read(){
	int x=0,f=1;
	char ch;
	do{
		ch=getchar();
		if(ch=='-'){
			f=-1;
		}
	}while(!(ch>='0'&&ch<='9'));
	while(ch>='0'&&ch<='9'){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	return x*f;
}
struct Splay{
    void push_up(int cur){
        si[cur]=si[ch[cur][1]]+si[ch[cur][0]]+1;
    }
    int get(int x){
        return x==ch[fa[x]][1];
    }
    int build(int l,int r,int f){
        if(l>r){
            return 0;
        }
        int mid=(l+r)>>1;
        int now=++tot;
        fa[now]=f;
        val[now]=ob[mid].val;
        p[ob[mid].val]=now;
        ch[now][0]=build(l,mid-1,now);
        ch[now][1]=build(mid+1,r,now);
        push_up(now);
        return now;
    }
    void push_down(int cur){
        if(tag[cur]){
            tag[cur]=0;
            swap(ch[cur][0],ch[cur][1]);
            tag[ch[cur][0]]^=1;
            tag[ch[cur][1]]^=1;
        }
    }
    int nex(){//找到后继
        push_down(rt);
        int x=ch[rt][1];
        while(1){
            push_down(x);
            if(!ch[x][0]){
                break;
            }
            x=ch[x][0];
        }
        return x;
    }
    void rotate(int x){
        int y=fa[x];
        int z=fa[y];
        push_down(y);
        push_down(x);
        int chk=get(x);
        ch[y][chk]=ch[x][chk^1];
        if(ch[x][chk^1]){
            fa[ch[x][chk^1]]=y;
        }
        fa[y]=x;
        ch[x][chk^1]=y;
        fa[x]=z;
        if(z){
            ch[z][y==ch[z][1]]=x;
        }
        push_up(y);
        push_up(x);
    }
    void splay(int x,int y){
        for(int f;(f=fa[x])!=y;rotate(x)){
            if(fa[f]==y){
                continue;
            }
            if(get(x)==get(f)){
                rotate(f);
            }else{
                rotate(x);
            }
        }
        if(y==0){
            rt=x;
        }
    }
    void reverse(int l,int r){
        splay(l,0);
        splay(r,l);
        tag[ch[r][0]]^=1;
    }
}tree;//Splay模板
bool cmp(object a,object b){
    if(a.val<b.val){
        return 1;
    }else{
        if(a.val==b.val){
            return a.num<b.num;
        }
    }
    return 0;
}
bool cmp2(object a,object b){
    return a.num<b.num;
}
signed main(){
    n=read();
    for(int i=1;i<=n;++i){
        ob[i+1].val=read();
        ob[i+1].num=i+1;
    }
    ob[1].val=0;
    ob[n+2].val=n+1;
    sort(ob+2,ob+n+2,cmp);
    for(int i=2;i<=n+1;i++){
        //离散
        ob[i].val=i-1;
    }
    sort(ob+2,ob+2+n,cmp2);
    rt=tree.build(1,n+2,0);//以类似线段树的方式建数
    for(int i=1;i<=n;++i){
        int x=p[i];//找到该权值对应的点的位置
        tree.splay(x,0);
        printf("%lld ",si[ch[x][0]]);
        x=tree.nex();//该权值的后继
        int y=p[i-1];//该权值的前驱
        tree.reverse(y,x);//区间翻转
    }
    return 0;
}
```


---

## 作者：xixike (赞：7)

[更好的阅读体验](https://www.cnblogs.com/xixike/p/15726570.html)

## Description

[Luogu传送门](https://www.luogu.com.cn/problem/P4402)

## Solution

题目要求我们找到第 $i$ 的数，其实就维护一下剩下的数中最小值在哪里即可。

我们考虑使用 $fhq-treap$。

说一下具体实现过程：

- 找到剩下的点中的最小值（其实就是根）。
- 输出答案，删去它，合并它的两个儿子。
- 维护区间翻转标记并下传。

然后就没了。。甚至连 split 都不需要（

并且维护的这个最小值正好满足小根堆的性质，为了方便，我们可以拿输入的数代替 rand 的值。

（但是会被卡）

我们考虑优化建树，使用建**笛卡尔树**的思想来建树。

关于笛卡尔树，戳[这里](https://www.cnblogs.com/xixike/p/15544463.html)。

我们把权值小于当前权值的点挂到当前点的左子树上，再把当前点挂到第一个大于它的点的右子树上，即可构建出一棵相对平衡的平衡树（事实上跑的飞快）。

这个过程就用单调栈维护一下即可。

（这样一来反而不如普通的 $fhq-treap$ 好写了 QwQ）

还有无关紧要的一点，**题目中可能会输入相同的数，如有相同先输出最靠左的**，所以稍微处理一下即可，具体见代码。

## Code

```cpp
#include <bits/stdc++.h>
#define ll long long
#define ls(x) t[x].l
#define rs(x) t[x].r

using namespace std;

namespace IO{
    inline int read(){
        int x = 0;
        char ch = getchar();
        while(!isdigit(ch)) ch = getchar();
        while(isdigit(ch)) x = (x << 3) + (x << 1) + ch - '0', ch = getchar();
        return x;
    }

    template <typename T> inline void write(T x){
        if(x > 9) write(x / 10);
        putchar(x % 10 + '0');
    }
}
using namespace IO;

const int N = 1e5 + 10;
int n;
struct fhq_treap{
    int siz, val, l, r;
    ll wei;
    bool rev;
}t[N];
int rt, tot;

inline void pushup(int x){
    t[x].siz = t[ls(x)].siz + t[rs(x)].siz + 1;
}

inline void pushdown(int x){
    if(t[x].rev){
        swap(ls(x), rs(x));
        if(ls(x)) t[ls(x)].rev ^= 1;
        if(rs(x)) t[rs(x)].rev ^= 1;
        t[x].rev = 0;
    }
}

inline int merge(int x, int y){
    if(!x || !y) return x | y;
    if(t[x].wei <= t[y].wei){
        pushdown(x);
        rs(x) = merge(rs(x), y);
        return pushup(x), x;
    }else{
        pushdown(y);
        ls(y) = merge(x, ls(y));
        return pushup(y), y;
    }
}

int stk[N], top;

inline void build(int x){
    while(top && t[x].wei < t[stk[top]].wei) ls(x) = stk[top--], pushup(ls(x));
    if(top) rs(stk[top]) = x;
    stk[++top] = x;
}

inline void update(int x){
    int l = ls(x), r = rs(x);
    ls(x) = rs(x) = 0;
    t[l].rev ^= 1;
    rt = merge(l, r);
}

signed main(){
    n = read();
    for(int i = 1; i <= n; ++i){
        t[i].wei = 1ll * read() * n + i, t[i].val = i, t[i].siz = 1;
        build(i);
    }
    while(top) pushup(stk[top--]);
    rt = stk[1];
    for(int i = 1; i <= n; ++i){
        pushdown(rt);
        write(t[ls(rt)].siz + i), putchar(' ');
        update(rt);
    }
    return puts(""), 0;
}
```

$$
\_EOF\_
$$


---

## 作者：swhsz (赞：7)

splay区间操作的练手题，在维护平衡的时候不是以数值，而是以位置为权值维护一颗splay。
翻转的时候就把第i个数的提到根，看它的左儿子的大小即它前面的数的个数。
然后模拟题目中说的操作，把i-1提到根，再把i的后继提到i-1的下面中间夹的就是 $i-1$ ~ $i$ 了
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
const int N=100005;
int n,fa[N],ch[N][2],val[N],siz[N],tot,pos[N],rt;
struct Node{
	int id,v;
}a[N];
bool cmp1(Node x,Node y) {return x.v==y.v?x.id<y.id:x.v<y.v;}
bool cmp2(Node x,Node y) {return x.id<y.id;}
bool rev[N];
inline void pushup(int x) {siz[x]=siz[ch[x][0]]+siz[ch[x][1]]+1;}
void pushdown(int x) {
	if(rev[x]) {
		swap(ch[x][0],ch[x][1]);
		rev[ch[x][0]]^=1,rev[ch[x][1]]^=1;
		rev[x]=0;
	}
}
int build(int f,int l,int r) {
	if(l>r) return 0;
	int now=++tot,mid=l+r>>1;
	val[now]=a[mid].v;fa[now]=f;
	pos[a[mid].v]=now;
	ch[now][0]=build(now,l,mid-1);
	ch[now][1]=build(now,mid+1,r);
	pushup(now);
	return now;
}
inline void rotate(int x) {
	int f=fa[x],ff=fa[f];
	pushdown(f);pushdown(x);
	bool tag=ch[fa[x]][1]==x;
	ch[f][tag]=ch[x][tag^1];
	fa[ch[f][tag]]=f;
	fa[f]=x;
	ch[x][tag^1]=f;
	fa[x]=ff;
	if(ff) ch[ff][f==ch[ff][1]]=x;
	pushup(f);pushup(x);
}
inline void splay(int x,int tar){
	for(int f;(f=fa[x])!=tar;rotate(x)) if(fa[f]!=tar)rotate((x==ch[fa[x]][0])==(f==ch[fa[f]][0])?f:x);
	if(!tar) rt=x;
}
int nxt(){
	pushdown(rt);
	int x=ch[rt][1];
	while(pushdown(x),ch[x][0]) x=ch[x][0];
	return x;
}
int main() {
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i+1].v),a[i+1].id=i+1;
	a[1].v=0;a[n+2].v=n+1;
	sort(a+2,a+2+n,cmp1);
	for(int i=2;i<=n+1;i++) a[i].v=i-1;
	sort(a+2,a+2+n,cmp2);
	rt=build(0,1,n+2);
	for(int i=1;i<=n;i++) {
		int x=pos[i];splay(x,0);
		printf("%d ",siz[ch[x][0]]);		
		x=nxt();
		int y=pos[i-1];
		splay(y,0);
		splay(x,y);
		rev[ch[x][0]]^=1;
	}
}
```

---

## 作者：ExplodingKonjac (赞：6)

### [原题链接](https://www.luogu.com.cn/problem/P4402)

蒟蒻刚学 Splay 来写一个题解 qwq。

**~~这是一道四倍经验题（~~**

## 解题思路

因为要区间翻转，肯定需要使用 Splay 来处理。首先就按照下标递归建 Splay，当然别忘记在前后插入一个 $\mathrm{-INF}$ 节点和一个 $\mathrm{INF}$ 节点（防止翻转 $[1,n]$ 时挂掉）。

### Case 1：如何得到第 $i$ 小的位置

我们可以首先记录下来每个数的下标，然后对这些数排序。因为题目要求相同的数按照编号排列，所以可以把值和下标放进一个 pair 里面来排序处理。

在建树的时候记录下来**每个原始下标对应的节点**。然后在处理的时候只需要遍历一遍排序后的数组 $[1,n]$，找到记录下来的下标对应的节点，并把这个节点 Splay 到根。此时根的左子树大小就是答案（因为我们插入了 $\mathrm{-INF}$ 节点，所以不需要 $+1$）。

### Case 2：如何进行翻转操作

使用二叉查找树的查数值操作找到排名为 $i-1$ 的节点，即目前序列的第 $i-1$ 个数。因为在 $\textbf{Case 1}$ 中已经找到了第 $i$ 小数的位置（即 Splay 中的排名），可以以同样操作找到其后继节点。

找到了需要翻转的区间左端点的前驱，右端点的后继，就可以进行 Splay 区间翻转的[模板操作](https://www.luogu.com.cn/problem/P3391)了。

## 注意事项

给大家讲讲我过这题的辛酸历程 qAq，警示后人:

* $n$ 久前：$\color{red}\texttt{0}$，根本不理解 Splay；
* 第 $2$ 次提交：$\texttt{{\color{#9d3dcf}RE}+{\color{#052242}TLE}}$，忘记删除调试代码了（；
* 第 $3$ 次提交：$\texttt{{\color{#9d3dcf}RE}+{\color{#e74c3c}WA}}$，在 rotate 操作中**自己和父亲的 pushdown、pushup 的顺序写错**；
* 后来的提交：卡常。

## 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;
const int INF=0x7fffffff;
int n;
pair<int,int> a[100005];
inline int read()
{
	char ch;int res=0;
	for(ch=getchar();isspace(ch);ch=getchar());
	for(;isdigit(ch);res=res*10+ch-'0',ch=getchar());
	return res;
}
struct TreeNode //Splay Tree节点
{
	int siz;
	bool tag;
	TreeNode *ch[2],*fa;
	TreeNode(): siz(1),tag(0)
		{ ch[0]=ch[1]=fa=nullptr; }
}*rt;
typedef TreeNode *pNode;
inline int which(pNode i) //判断自己是哪一个儿子
	{ return i==i->fa->ch[1]; }
inline void pushup(pNode &i) //更新子树大小
{
	if(!i)	return;
	i->siz=1;
	if(i->ch[0])	i->siz+=i->ch[0]->siz;
	if(i->ch[1])	i->siz+=i->ch[1]->siz;
}
inline void pushdown(pNode &i) //翻转标记下传
{
	if(i && i->tag)
	{
		if(i->ch[0])	i->ch[0]->tag^=i->tag;
		if(i->ch[1])	i->ch[1]->tag^=i->tag;
		swap(i->ch[0],i->ch[1]),i->tag=0;
	}
}
inline void rotate(pNode i) //rotate与splay，照搬模板
{
	if(i==rt)	return;
	pNode f=i->fa,gf=i->fa->fa;
	pushdown(f),pushdown(i); //注意pushup和pushdown的顺序
	bool x=which(i);
	i->fa=gf;
	if(gf)	gf->ch[which(f)]=i;
	f->ch[x]=i->ch[!x];
	if(f->ch[x])	f->ch[x]->fa=f;
	i->ch[!x]=f,f->fa=i;
	pushup(f),pushup(i);
}
inline void splay(pNode x,pNode y=nullptr)
{
	for(pNode f;(f=x->fa)!=y;rotate(x))
		if(f->fa!=y)
			rotate(which(x)==which(f)?f:x);
	if(!y)	rt=x;
}
pNode findValue(int k) //根据排名找节点
{
	pNode i=rt;
	while(true)
	{
		pushdown(i);
		int siz=i->ch[0]?i->ch[0]->siz:0;
		if(k<=siz)	i=i->ch[0];
		else if(k==siz+1)	return i;
		else	k-=siz+1,i=i->ch[1];
	}
}
pNode nd[100005]; //用于记录每个原始下标对应的节点
void build(int l,int r,pNode &i=rt,pNode f=nullptr)
{
	if(l>r)	return;
	int mid=(l+r)>>1;
	i=new TreeNode,i->fa=f,nd[mid]=i;
	build(l,mid-1,i->ch[0],i);
	build(mid+1,r,i->ch[1],i);
	pushup(i);
}
int main()
{
	n=read();
	for(int i=2;i<=n+1;i++)
		a[i].first=read(),a[i].second=i; //要记录下标
	build(1,n+2); //建树
	a[1]=make_pair(-INF,1);
	a[n+2]=make_pair(INF,n+2); //前后边界节点
	sort(a+1,a+n+3);
	for(int i=2;i<=n+1;i++)
	{
		auto &now=a[i];
		splay(nd[now.second]); //将a[i]对应的节点splay到根
		int zt=rt->ch[0]->siz; //左子树大小为答案
		pNode x=findValue(i-1),y=findValue(zt+2); //找到翻转区间的左右边界
		splay(x),splay(y,x); //区间翻转操作
		y->ch[0]->tag^=1;
		printf("%d ",zt);
	}
	return 0;
}
```


---

## 作者：peterwuyihong (赞：5)

题意：给定一个序列，你要通过奥妙重重的手段把它排序，就是第 $i$ 次找到 $[i,n]$ 中最小的，把序列的第一位和这一位之间的序列翻转，操作 $n$ 次，但你还要保证这是一个稳定的排序，就是相同元素相对位置不变，然后你每次要输出最小值的位置。

首先这个稳定排序比较奥妙重重，我们使用[[Ynoi2016] 掉进兔子洞](https://www.luogu.com.cn/problem/P4688)的套路，把每个元素加入一个数组，然后排序，但不要去重，离散化时求出排名加上已经出现过的次数，这就是一个完美的映射。

然后硬上万能 fhq 即可，维护区间翻转与最小值，然后每次转完就把最小的点删掉即可，要注意每次输出排名要加上删掉的数的个数。

现在是 $10:53$，我看我什么时候写完。

现在是 $11:17$，我写完了。

```cpp
#define maxn 100010
int n;
struct prpr{
	int l,r,tag;
	int dat,val,siz;
	int mn;
}tree[maxn];
int tot,rt,x,y,z;
mt19937 rnd(time(NULL));
int Build(int val){
	tree[++tot].val=val;
	tree[tot].dat=rnd();
	tree[tot].siz=1;
	tree[tot].mn=val;
	return tot;
}
void Pushdown(int x){
	if(tree[x].tag){
		if(tree[x].l)tree[tree[x].l].tag^=1;
		if(tree[x].r)tree[tree[x].r].tag^=1;
		swap(tree[x].l,tree[x].r);
		tree[x].tag=0;
	}
}
void Pushup(int x){
	tree[x].siz=tree[tree[x].l].siz+1+tree[tree[x].r].siz;
	tree[x].mn=tree[x].val;
	if(tree[x].l){
		if(tree[x].mn>tree[tree[x].l].mn){
			tree[x].mn=tree[tree[x].l].mn;
		}
	}
	if(tree[x].r){
		if(tree[x].mn>tree[tree[x].r].mn){
			tree[x].mn=tree[tree[x].r].mn;
		}
	}
}
void Split(int rt,int k,int &x,int &y){
	if(!rt)x=y=0;
	else{
		Pushdown(rt);
		if(tree[tree[rt].l].siz+1<=k)x=rt,Split(tree[x].r,k-tree[tree[rt].l].siz-1,tree[x].r,y);
		else y=rt,Split(tree[y].l,k,x,tree[y].l);
		Pushup(rt);
	}
}
int Merge(int x,int y){
	if(!x||!y)return x+y;
	if(tree[x].dat<tree[y].dat){
		Pushdown(x);
		tree[x].r=Merge(tree[x].r,y);
		Pushup(x);return x;
	}else{
		Pushdown(y);
		tree[y].l=Merge(x,tree[y].l);
		Pushup(y);return y;
	}
}
int G(int x){
	int k=1;
	while(1){
		Pushdown(x);
		if(tree[x].l&&tree[tree[x].l].mn==tree[x].mn)x=tree[x].l;
		else if(tree[x].r&&tree[tree[x].r].mn==tree[x].mn)k+=tree[tree[x].l].siz+1,x=tree[x].r;
		else return k+tree[tree[x].l].siz;
	}
}
int a[maxn],b[maxn],cnt[maxn];
signed main(){
#ifndef ONLINE_JUDGE
	freopen("testdata.in","r",stdin);
#endif
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i],b[i]=a[i];
	sort(b+1,b+n+1);
	for(int i=1;i<=n;i++)a[i]=lower_bound(b+1,b+n+1,a[i])-b,a[i]+=cnt[a[i]]++;
	for(int i=1;i<=n;i++)rt=Merge(rt,Build(a[i]));
	for(int i=1;i<=n;i++){
		int rk=G(rt);
		Split(rt,rk,x,y);
		Split(x,rk-1,x,z);
		tree[x].tag^=1;
		rt=Merge(x,y);
		cout<<rk+i-1<<' ';
	}
#ifndef ONLINE_JUDGE
	cerr<<endl<<(double)clock()/CLOCKS_PER_SEC;
#endif
}
```
[一倍经验](https://www.luogu.com.cn/problem/P4402)[双倍经验](https://www.luogu.com.cn/problem/P3165)[三倍经验](https://www.luogu.com.cn/problem/UVA1402)[四倍经验](https://www.luogu.com.cn/problem/SP2059)

---

## 作者：TheLostWeak (赞：5)

[在博客查看](https://www.cnblogs.com/chenxiaoran666/p/BZOJ3506.html)

**大致题意：** 给你$n$个数。第一次找到最小值所在位置$P_1$，翻转$[1,P_1]$，第二次找到剩余数中最小值所在位置$P_2$，翻转$[2,P_2]$，以此类推。求$P_1,P_2,...,P_n$的值。

------

### 初始化

这题应该是一道比较裸的$Splay$题。

关于$Splay$可以查看这篇博客：[简析平衡树（三）——浅谈Splay](https://www.cnblogs.com/chenxiaoran666/p/Splay.html)。

首先，我们将原数组排序一遍，记下**每一次操作的位置**。

有一个细节，题目要求**相同值要先取位置靠前的**（没注意到这点结果狂$WA$不止）。

然后便是建树。

注意，$Splay$建树的过程中我们一般会在序列左右各加一个多余节点，方便后面取出一段区间进行操作。

------

### 操作

每一次操作，我们把要操作的位置先$Splay$到根，然后就可以得出答案即为此时**左子树的$Size$**，记其为$ans$。

注意是$Size$而不是$Size+1$，要考虑到我们在序列左边加的那个多余节点已经使$Size$比实际存在的节点个数多$1$了。

然后，按照题目要求，我们要翻转区间$[i,ans]$。（关于这一操作的具体过程可以看这道题：[【洛谷3391】【模板】文艺平衡树（Splay）](https://www.luogu.org/problemnew/show/P3391)）

直接将$i$号节点和$ans+2$号节点分别旋到根节点和根节点的右儿子，然后翻转根节点的右儿子的左儿子即可。

------

### 代码

```cpp
#include<bits/stdc++.h>
#define Type template<typename I>
#define N 100000
#define swap(x,y) (x^=y^=x^=y)
#define INF 1e9
using namespace std;
int n;
struct Data
{
    int pos,val;
    inline friend bool operator < (Data x,Data y) {return x.val^y.val?x.val<y.val:x.pos<y.pos;}
}a[N+5];
class Class_FIO
{
    private:
        #define Fsize 100000
        #define tc() (A==B&&(B=(A=Fin)+fread(Fin,1,Fsize,stdin),A==B)?EOF:*A++)
        #define pc(ch) (FoutSize^Fsize?Fout[FoutSize++]=ch:(fwrite(Fout,1,Fsize,stdout),Fout[(FoutSize=0)++]=ch))
        #define Isi(x) (typeid(x).name()==typeid(1).name())
        #define Isc(x) (typeid(x).name()==typeid('a').name())
        int Top,FoutSize;char ch,*A,*B,Fin[Fsize],Fout[Fsize],Stack[Fsize];
    public:
        Class_FIO() {A=B=Fin;}
        Type inline void read(I& x) {x=0;while(!isdigit(ch=tc()));while(x=(x<<3)+(x<<1)+(ch&15),isdigit(ch=tc()));}
        Type inline void write(I x)
        {
            if(Isi(x)) {while(Stack[++Top]=x%10+48,x/=10);while(Top) pc(Stack[Top--]);}
            if(Isc(x)) pc(x);
        }
        template<typename I,typename... A> inline void read(I& x,A&... y) {read(x),read(y...);}
        template<typename I,typename... A> inline void write(I x,A... y) {write(x),write(y...);}
        inline void clear() {fwrite(Fout,1,FoutSize,stdout),FoutSize=0;}
}F;
class Class_Splay//Splay
{
    private:
        #define SIZE N
        #define PushUp(x) (node[x].Size=node[node[x].Son[0]].Size+node[node[x].Son[1]].Size+1)
        #define Rever(x) (swap(node[x].Son[0],node[x].Son[1]),node[x].Rev^=1)
        #define PushDown(x) (node[x].Rev&&(Rever(node[x].Son[0]),Rever(node[x].Son[1]),node[x].Rev=0))
        #define Which(x) (node[node[x].Father].Son[1]==x)
        #define Connect(x,y,d) (node[node[x].Father=y].Son[d]=x)
        #define Split(x,y) (Splay(get_pos(x),rt),Splay(get_pos((y)+2),node[rt].Son[1]),node[node[rt].Son[1]].Son[0])
        int rt;
        struct Tree
        {
            int Size,Rev,Father,Son[2];
        }node[SIZE+5];
        inline void Rotate(int x,int& k)
        {
            register int fa=node[x].Father,pa=node[fa].Father,d=Which(x);PushDown(fa),PushDown(x),
            (fa^k?node[pa].Son[Which(fa)]=x:k=x),node[x].Father=pa,Connect(node[x].Son[d^1],fa,d),Connect(fa,x,d^1),PushUp(fa),PushUp(x);
        }
        inline void Splay(int x,int& k) {register int fa;while(x^k) fa=node[x].Father,fa^k&&(Rotate(Which(x)^Which(fa)?x:fa,k),0),Rotate(x,k);}
        inline void Build(int l,int r,int& rt)
        {
            register int mid=l+r>>1;
            if(node[rt=mid].Size=1,!(l^r)) return;
            l<mid&&(Build(l,mid-1,node[rt].Son[0]),node[node[rt].Son[0]].Father=rt),
            r>mid&&(Build(mid+1,r,node[rt].Son[1]),node[node[rt].Son[1]].Father=rt),
            PushUp(rt);
        }
        inline int get_pos(int rk)
        {
            register int x=rt;
            while(x) 
            {
                if(PushDown(x),node[node[x].Son[0]].Size>=rk) x=node[x].Son[0];
                else if(!(rk-=node[node[x].Son[0]].Size+1)) return x;
                else x=node[x].Son[1];
            }
        }
    public:
        inline void Init(int len) {Build(1,len+2,rt);}
        inline int GetAns(int x) 
        {
            register int k,ans;
            Splay(a[x].pos+1,rt),ans=node[node[rt].Son[0]].Size,k=Split(x,ans),Rever(k);//找到ans，然后翻转
            return ans;//返回答案
        }
        #undef SIZE
}Splay;
int main()
{
    register int i,p;
    for(F.read(n),i=1;i<=n;++i) F.read(a[a[i].pos=i].val);//读入
    for(sort(a+1,a+n+1),Splay.Init(n),i=1;i<=n;++i) F.write(p=Splay.GetAns(i),' ');//初始化排序+依次操作
    return F.clear(),0;
}
```





---

## 作者：Mars_Dingdang (赞：4)

一道经典的区间平衡树题，用 fhq Treap 和 Splay 均可实现。下面提供两者的思路，详细解释前者并提供代码。

## 题目大意
有 $n$ 个数字，$1\le n\le 10^5$，用一个机械臂排序，方法如图所示，每次用机械臂夹住第 $i$ 个数和第 $i$ 小的数翻转，重复此过程直到结束，求第 $i$ 次翻转之前第 $i$ 大的数的位置。

## 大体思路
首先介绍 Splay 的思路。利用其能将结点旋转到根的功能，考虑区间翻转时找到最小的数，将其旋转到根，则其左子树大小就是数列中排在其左边的数的个数。

对于区间翻转，用类似线段树的懒标记记录反转情况，进行区间翻转时令标记 `rev ^= 1`，每次操作时标记下放即可。

注意，每次操作之后，得到的第 $i$ 小值将不参与后续的操作，因此将其直接从树中删除。计算第 $i$ 个排名时加上删去数的个数 $i-1$ 即可。
________

下面介绍 fhqTreap 的思路。由于其能够分裂合并，考虑按照排名进行分裂合并，每次操作时找到最小值的排名 $k$，并将区间 $[1, k]$ 翻转，随后删去该值。每次的答案即为 $k+i-1$。

主要操作涉及 `split`, `merge`, `insert`, `remove`, `pushdown` 等，对于其不熟悉请至模板题《普通平衡树》以及《文艺平衡树》。

## 代码 Code
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define rep(ii,aa,bb) for(re int ii = aa; ii <= bb; ii++)
#define Rep(ii,aa,bb) for(re int ii = aa; ii >= bb; ii--)
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef pair<int, int> PII;
const int maxn = 1e5 + 5;
namespace IO_ReadWrite {
	#define re register
	#define gg (p1 == p2 && (p2 = (p1 = _buf) + fread(_buf, 1, 1<<21, stdin), p1 == p2) ? EOF :*p1++)
	char _buf[1<<21], *p1 = _buf, *p2 = _buf;
	template <typename T>
	inline void read(T &x){
		x = 0; re T f=1; re char c = gg;
		while(c > 57 || c < 48){if(c == '-') f = -1;c = gg;}
		while(c >= 48 &&c <= 57){x = (x<<1) + (x<<3) + (c^48);c = gg;}
		x *= f;return;
	}
	inline void ReadChar(char &c){
		c = gg;
		while(!isalpha(c)) c = gg;
	}
	template <typename T>
	inline void write(T x){
		if(x < 0) putchar('-'), x = -x;
		if(x > 9) write(x/10);
		putchar('0' + x % 10);
	}
	template <typename T>
	inline void writeln(T x){write(x); putchar('\n');}
}
using namespace IO_ReadWrite;
// <------------------ 快读 ----------------->
int n, root, seed = 1, tot; 
// root: 根, tot: 动态开点 
struct node{
	int l, r;
	int val, sz, wei, mi, rev;
    //wei: 随机权值，rev: 懒标记
} a[maxn];
// <--------------- 变量申明 ---------------->
inline int rand1() { return seed *= 19491001; } // 随机权值
template <typename T>
inline T Min(T x, T y) {
	return x < y ? x : y;
}
template <typename T>
inline void Swap(T &x, T &y) {
	T t = x; x = y; y = t;
}
inline void pushup(int p) { //向上更新
	a[p].sz = a[a[p].l].sz + a[a[p].r].sz + 1;
	a[p].mi = Min(a[p].val, Min(a[a[p].l].mi, a[a[p].r].mi));
}
inline void pushdown(int p) { //标记下放
	if (!a[p].rev) return;
	Swap(a[p].l, a[p].r);
	a[a[p].l].rev ^= 1;
	a[a[p].r].rev ^= 1;
	a[p].rev = 0;
}
inline PII split(int p, int k) { 
	//分裂， 返回 pair 表示两棵树的根
	if(!p) return {0, 0};
	pushdown(p);
	if(a[a[p].l].sz < k) {// 分裂右子树
		k -= (a[a[p].l].sz + 1);
		PII t = split(a[p].r, k);
		a[p].r = t.first;
		pushup(p);
		return {p, t.second};
	} else {//继续分裂左子树
		PII t = split(a[p].l, k);
		a[p].l = t.second;
		pushup(p);
		return {t.first, p};
	}
}
inline int merge(int u, int v) {//合并
	if(!u || !v) return u | v;
	if(a[u].wei < a[v].wei) {//u 优先级高，作为父节点
		pushdown(u);
		a[u].r = merge(a[u].r, v);
		pushup(u); return u;
	} else {
		pushdown(v);
		a[v].l = merge(u, a[v].l);
		pushup(v); return v;
	}
}
inline void insert(int k) {
	a[++tot].wei = rand1(); a[tot].sz = 1; a[tot].val = a[tot].mi = k;
    //动态开点
	root = merge(root, tot);//合并
    //由于主函数已经按值排序，此处直接合并至右子树即可
}
inline int find(int p) {//找最小值
	int k = 1;
	while(p) {
		pushdown(p);
		if(a[p].l && a[p].mi == a[a[p].l].mi) p = a[p].l;//左子树
		else if(a[p].r && a[p].mi == a[a[p].r].mi)//右子树
			k += a[a[p].l].sz + 1,
			p = a[p].r;
		else return k + a[a[p].l].sz;//当前节点 
	}
}
inline void reverse(int k) {
	PII x = split(root, k);
	PII y = split(x.first, k - 1);//分离出区间 [1,k]
	a[y.first].rev ^= 1;//标记
	root = merge(y.first, x.second);//删除并合并
}

struct Node {
	int num, pos;
	bool operator <(const Node &x)const {
		if(num != x.num) return num < x.num;
		return pos < x.pos;
	}
} p[maxn];
int v[maxn];

int main () {
	a[0].mi = (1 << 30);//边界
	read(n);
	rep(i, 1, n) 
		read(p[i].num), p[i].pos = i;
	sort(p + 1, p + n + 1);//按值排序
	rep(i, 1, n)
		v[p[i].pos] = i;
	rep(i, 1, n) insert(v[i]);//插入
	rep(i, 1, n) {		
		int k = find(root);//找到最小值的位置
		reverse(k);//区间翻转并删除
		write(k + i - 1), putchar(' ');//输出
	}
	
	return 0;
}
```
## 后记
本题有四倍经验：P3165，P4402，SP2059，UVA1402。

---

## 作者：HenryHuang (赞：3)

## FHQ_Treap 太神辣

蒟蒻初学FHQ_Treap,于是来到了这道略显板子的题目

因为Treap既满足BST的性质，又满足Heap的性质，所以，对于这道题目，我们可以将以往**随机出的额外权值转化为每一个位置的高度**，这样我们就可以利用小根堆的性质，甚至连$Split$操作都可以省略掉，就可以AC这道题目

步骤：
1.首先找到现在的根节点，即当前高度最低的位置

2.根据Treap的性质，我们只需要将其左子树打一个反转的标记，然后将根节点删除，将其左右两个子树合并，那么，新的子节点就是我们接下来需要的第2小高度的位置

3.重复1，2操作，这个题目就完结撒花辣！！

但是高度有可能是相同的，题目中又要求取靠前的那一个，于是我们将所有的数乘上n，再加上i，这样就可以有效避免这一个问题。

~~愿望总是美好的~~

----

[CQOI2014]排序机械臂愉快的过掉了，但另外一道相同的题目却过不了（robotic sort）。然后，有dalao指出，这样的做法，只要数据是单调的，就会被卡成$O(n^2)$

于是，通过查阅资料，我们可以使用一种神奇的方法——笛卡尔树优化建树，这样就可以有效避免这个问题。

对于$Treap$来说，我们可以将每一个节点的信息简化为一个二元组$(val,rand)$，意义一看便知

我们按照val的顺序进行插入，而在本题中，val即初始位置1~n,所以不用重新排序。

我们可以维护一个单调栈，从而有效解决这个问题。

对于每一个节点，我们将栈中大于当前节点rand值的节点全部弹出，将他们挂在当前节点的左儿子上，然后再把连同当前节点一起的这一棵树挂在弹完所有值之后的栈顶节点的右儿子上，这样就可以构建出一颗相对平衡的Treap。

用通俗的话讲，对于当前节点u，我们只考虑将其放在最右边的这一条链上，如果他比所有节点的rand值都大，那么当然顺理成章的放在最右边，如果没有，我们就考虑同时维护BST与Heap的性质，于是就有了我们上面的做法。

### 目前是本题~~氧后~~rank1，开森

贴代码啦~

```cpp
//短短70行解决战斗
#include<bits/stdc++.h>
using namespace std;
const long long maxn=5e5+10;
long long inline read()
{
    long long x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
long long son[maxn][2],val[maxn],rnd[maxn],siz[maxn],cnt,rt,tag[maxn];
inline void upd(long long t){siz[t]=siz[son[t][0]]+siz[son[t][1]]+1;}
inline void down(long long x)
{
    if(tag[x])
    {
        swap(son[x][0],son[x][1]);
        if(son[x][0]) tag[son[x][0]]^=1;
        if(son[x][1]) tag[son[x][1]]^=1;
        tag[x]=0;
    }
}
inline long long init(long long x,long long qaq)
{
    ++cnt,val[cnt]=x,siz[cnt]=1,rnd[cnt]=qaq;
    return cnt;
}
inline long long merge(long long x,long long y)
{
    if(!x||!y) return x+y;
    if(rnd[x]<rnd[y])
    {
        down(x),son[x][1]=merge(son[x][1],y),upd(x);
        return x;
    }
    else
    {
        down(y),son[y][0]=merge(x,son[y][0]),upd(y);
        return y;
    }
}
struct cc{
    long long num,id;
}a[maxn];
int main()
{
    srand(time(0));
    long long opt,n,m,l,r,x,y,z;
    stack<int> q;
    scanf("%lld",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%lld",&rnd[i]),rnd[i]=rnd[i]*n+i,val[i]=i,siz[i]=1;
        while((!q.empty())&&rnd[i]<rnd[q.top()])
            son[i][0]=q.top(),q.pop(),upd(son[i][0]);
        if(!q.empty()) son[q.top()][1]=i;
        q.push(i);
    }
    while(!q.empty()) rt=q.top(),upd(q.top()),q.pop();
    for(int i=1;i<=n;++i)
    {
        down(rt);
        printf("%lld ",siz[son[rt][0]]+i);
        l=son[rt][0],r=son[rt][1];
        son[rt][0]=son[rt][1]=0;
        tag[l]^=1;
        rt=merge(l,r);
    }
    return 0;
}
```

---

## 作者：CodingJellyfish (赞：2)

### WBLT
感谢这道题没有关闭题解。

大家好，我是水母哥，我用了 WBLT 水掉了这道题。

我在网上并没有看到 WBLT 维护区间反转的方法，但是其实它可以，而且速度相当快（堪比 Spaly）。

WBLT 区间翻转的方式类似 Treap，需要将翻转的区间分裂出来，再打上标记，最后将这段区间合并回去。

WBLT 分裂方式和 Treap 基本相同，不过由于 WBLT 必须为一颗 Leafy Tree，所以在分裂同时要维护这个性质。

由于 WBLT 是其对应数列建成的 Kruskal 重构树，一棵 WBLT 非叶节点的个数为其叶节点个数 - 1。WBLT 分裂成两个后，序列长度不变，但是树却变成了两棵。所以非叶节点的个数为其叶节点个数 - 2。这样就多出了一个节点，这个节点只有一个儿子。只需要将它变成它的儿子就可以了。

合并的话，就用重构的合并，再重构一下就可以了。不要忘了上传标记。这个操作复杂度个人认为不可证，但是实测很难卡。

其他操作就很简单了，不过不要忘了离散化。

```c
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// IO

#define IO 10000
char _ibuf[IO], _obuf[IO];
char *_i = _ibuf, *_o = _obuf;

FILE *_is, *_os;
#define IS stdin
#define OS stdout

void init_IO(void)
{
    fread(_ibuf, IO, sizeof(char), IS);
}

void end_IO(void)
{
    fwrite(_obuf, _o - _obuf, sizeof(char), OS);
}

static inline char getch(void)
{
    if (_i == _ibuf + IO)
    {
        memset(_ibuf, 0, sizeof(_ibuf));
        fread(_ibuf, IO, sizeof(char), IS);
        _i = _ibuf;
    }

    return *_i++;
}

static inline void putch(char ch)
{
    if (_o == _obuf + IO)
    {
        fwrite(_obuf, IO, sizeof(char), OS);
        _o = _obuf;
    }

    *_o++ = ch;
}

static inline int getint(void)
{
    int num = 0, fac = 1;
    char ch = getch();

    while (!isdigit(ch))
    {
        if (ch == '-')
            fac = -1;
        ch = getch();
    }

    while (isdigit(ch))
    {
        num = num * 10 + ch - '0';
        ch = getch();
    }

    return num * fac;
}

void putint(int num)
{
    if (num < 0)
    {
        putch('-');
        num = -num;
    }
    if (num >= 10)
        putint(num / 10);
    putch(num % 10 + '0');
}

// Consts

#define RPOOL 400005

// Utility

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define SWAP(T, a, b) ({T t = a; a = b; b = t;})

// Pools

typedef struct
{
    int val;
    int siz;
    int ch[2];
    char tag;
}
WBLTNode;

WBLTNode wblt_pool[RPOOL];
int      wpsiz;

#define RATIO 2

#define wnode(x) wblt_pool[x]
#define wval(x)  wblt_pool[x].val
#define wsiz(x)  wblt_pool[x].siz
#define wlch(x)  wblt_pool[x].ch[0]
#define wrch(x)  wblt_pool[x].ch[1]
#define wtag(x)  wblt_pool[x].tag

// WBLT

static inline int neww(int x)
{
    wnode(++wpsiz) = (WBLTNode)
    {
        x, 1, {0, 0}, 0
    };
    return wpsiz;
}

static inline void downw(int x)
{
    if (wtag(x))
    {
        wtag(wlch(x)) ^= 1;
        wtag(wrch(x)) ^= 1;
        SWAP(int, wlch(x), wrch(x));
        wtag(x) = 0;
    }
}

static inline void upw(int x)
{
    if (wlch(x))
    {
        wsiz(x) = wsiz(wlch(x)) + wsiz(wrch(x));
        wval(x) = wval(wlch(x)) < wval(wrch(x))
                ? wval(wlch(x)) : wval(wrch(x));
    }
}

static inline int mergew(int ind, int a, int b)
{
    wlch(ind) = a;
    wrch(ind) = b;
    upw(ind);
    return ind;
}

static inline void lcutw(int x)
{
    int tmp = wlch(wlch(x));
    wrch(x) = mergew(wlch(x), wrch(wlch(x)), wrch(x));
    wlch(x) = tmp;
}

static inline void rcutw(int x)
{
    int tmp = wrch(wrch(x));
    wlch(x) = mergew(wrch(x), wlch(x), wlch(wrch(x)));
    wrch(x) = tmp;
}

static inline void balancew(int x)
{
    if (wsiz(wlch(x)) > wsiz(wrch(x)) * 3)
    {
        downw(wlch(x));
        if (wsiz(wrch(wlch(x))) > wsiz(wlch(wlch(x))) * 2)
            downw(wrch(wlch(x))), rcutw(wlch(x));
        lcutw(x);
    }
    else if (wsiz(wrch(x)) > wsiz(wlch(x)) * 3)
    {
        downw(wrch(x));
        if (wsiz(wlch(wrch(x))) > wsiz(wrch(wrch(x))) * 2)
            downw(wlch(wrch(x))), lcutw(wrch(x));
        rcutw(x);
    }
}

int buildw(int x, int l, int r, int *arr)
{
    if (l == r)
    {
        wval(x) = arr[l];
        wsiz(x) = 1;
        return x;
    }
    int mid = l + ((r - l) >> 1);
    wlch(x) = buildw(++wpsiz, l, mid, arr);
    wrch(x) = buildw(++wpsiz, mid + 1, r, arr);
    upw(x);
    return x;
}

void splitw(int x, int *l, int *r)
{
    if (wsiz(x) == 1)
    {
        *l = x;
        *r = 0;
        return;
    }
    downw(x);
    
    if (wval(wlch(x)) == wval(x))
        *r = x, splitw(wlch(x), l, &wlch(x));
    else
        *l = x, splitw(wrch(x), &wrch(x), r);

         if (wlch(x) == 0) wnode(x) = wnode(wrch(x));
    else if (wrch(x) == 0) wnode(x) = wnode(wlch(x));

    balancew(x);
    upw(x);
}

void dellw(int x, int fa)
{
    if (wsiz(x) == 1)
    {
        x = wlch(fa) == x ? wrch(fa) : wlch(fa);
        wnode(fa) = wnode(x);
        return;
    }
    downw(x);
    dellw(wlch(x), x);
    balancew(x);
    upw(x);
}

int mrgw(int x, int y)
{
    wlch(++wpsiz) = x;
    wrch(wpsiz) = y;
    balancew(wpsiz);
    upw(wpsiz);
    return wpsiz;
}

void outputw(int x)
{
    if (wsiz(x) == 1)
    {
        printf("%d ", wval(x));
        return;
    }
    downw(x);
    outputw(wlch(x));
    outputw(wrch(x));
}

// Main

int ai[RPOOL];
int ind[RPOOL];

void smallsort(int *a, int *b, int siz)
{
    for (int i = siz >> 1; i; i >>= 1)
        for (int j = i; j < siz; j++)
        {
            int tmp1 = a[j], tmp2 = b[j], k = j - i;
            while (k >= 0 && (a[k] > tmp1 || (b[k] > tmp2 && a[k] == tmp1)))
                a[k + i] = a[k], b[k + i] = b[k], k -= i;
            a[k + i] = tmp1, b[k + i] = tmp2;
        }
}

int main()
{
    init_IO();

    int n = getint();

    for (int i = 1; i <= n; i++)
    {
        ai[i] = getint();
        ind[i] = i;
    }
    smallsort(ai + 1, ind + 1, n);

    for (int i = 1; i <= n; i++)
    {
        ai[ind[i]] = i;
    }
    
    int root = buildw(++wpsiz, 1, n, ai);
    root = mrgw(root, neww(2147483647));

    for (int i = 1; i <= n; i++)
    {
        int rroot;

        splitw(root, &root, &rroot);

        putint(wsiz(root) + i - 1);
        putch(' ');
        
        if (wsiz(root) >= 2)
        {
            wtag(root) ^= 1;
            dellw(root, 0);
            root = mrgw(root, rroot);
        }
        else
            root = rroot;
        //outputw(root);
        //printf("\n");
    }

    end_IO();
    return 0;
}
```


---

## 作者：hl666 (赞：2)

这题作为一道十分经典的**平衡树维护序列**的问题，自然是值得一做的了。

写完翻了下题解发现都是写**Splay**的dalao，少有的暴力**FHQ_Treap**党还是用**指针**实现的。

所以这里略微讲解下数组实现的FHQ_Treap好了，感觉写起来比Splay舒服些。

首先我们要抽象化一下题意：给你$n$个数，第$i$次操作在$[i,n]$中找到最小值的位置$p_i$，并**翻转**$[i,p_i]$。最后输出所有$p_i$的值。

然后我们考虑转化问题（因为貌似FHQ_Treap不能同时支持**基于权值**的```split```和**基于排名**的分裂）。

所以离散化是必须的，尤其注意这里不能直接对数组排序（因为会有**权值相等**的点）。

然后我们记一下每个值原来的位置，再考虑对一个**基本序列**（即初始时为$1,2,3,\dots,n$）进行翻转。

手动推导一下我们发现其实就是先找出每次操作位置的**排名**，然后再基本序列上不停翻转区间即可。

由于FHQ_Treap树高期望$\log$的特性，所以我们查询排名的时候可以直接暴力从一个点跳到根然后反着算回来。

最后提一下那种以权值为保证堆性质的值的做法是**错误**的！这样会导致树高不平衡，一旦遇到单调的数据就卡到$O(n^2)$了。

CODE

```cpp
#include<cstdio>
#include<cctype>
#include<algorithm>
#define RI register int
#define CI const int&
#define Tp template <typename T>
using namespace std;
const int N=100005;
struct data
{
    int val,id;
    inline friend bool operator <(const data& A,const data& B)
    {
        return A.val<B.val||(A.val==B.val&&A.id<B.id);
    }
}a[N]; int n,rk;
class FileInputOutput
{
    private:
        static const int S=1<<21;
        #define tc() (A==B&&(B=(A=Fin)+fread(Fin,1,S,stdin),A==B)?EOF:*A++)
        #define pc(ch) (Ftop<S?Fout[Ftop++]=ch:(fwrite(Fout,1,S,stdout),Fout[(Ftop=0)++]=ch))
        char Fin[S],Fout[S],*A,*B; int Ftop,pt[15];
    public:
        Tp inline void read(T& x)
        {
            x=0; char ch; while (!isdigit(ch=tc()));
            while (x=(x<<3)+(x<<1)+(ch&15),isdigit(ch=tc()));
        }
        Tp inline void write(T x)
        {
            if (!x) return (void)(pc('0'),pc(' ')); RI ptop=0;
            while (x) pt[++ptop]=x%10,x/=10; while (ptop) pc(pt[ptop--]+48); pc(' ');
        }
        inline void Fend(void)
        {
            fwrite(Fout,1,Ftop,stdout);
        }
        #undef tc
        #undef pc
}F;
class FHQ_Treap
{
    private:
        struct treap
        {
            int ch[2],size,dat,fa; bool rev;
            inline treap(CI Dat=0,CI Size=0)
            {
                ch[0]=ch[1]=rev=fa=0; dat=Dat; size=Size;
            }
        }node[N]; int tot,rt,seed,stack[N],top;
        #define lc(x) node[x].ch[0]
        #define rc(x) node[x].ch[1]
        #define fa(x) node[x].fa
        inline int rand(void)
        {
            return seed=(int)seed*482711LL%2147483647;
        }
        inline void swap(int& x,int& y)
        {
            int t=x; x=y; y=t;
        }
        inline void rever(CI x)
        {
            swap(lc(x),rc(x)); node[x].rev^=1;
        }
        inline void pushup(CI x)
        {
            node[x].size=node[lc(x)].size+node[rc(x)].size+1; fa(lc(x))=fa(rc(x))=x;
        }
        inline void pushdown(CI x)
        {
            if (node[x].rev) rever(lc(x)),rever(rc(x)),node[x].rev=0;
        }
        inline void merge(int& now,int x,int y)
        {
            if (!x||!y) return (void)(now=x|y); if (node[x].dat>node[y].dat)
            pushdown(x),now=x,merge(rc(now),rc(x),y),pushup(x); else
            pushdown(y),now=y,merge(lc(now),x,lc(y)),pushup(y);
        }
        inline void split(int now,int& x,int& y,int rk)
        {
            if (!now) return (void)(x=y=0); pushdown(now); if (node[lc(now)].size<rk)
            x=now,split(rc(now),rc(x),y,rk-node[lc(now)].size-1); else
            y=now,split(lc(now),x,lc(y),rk); pushup(now);
        }
    public:
        FHQ_Treap() { seed=233; }
        inline void insert(CI val)
        {
            node[++tot]=treap(rand(),1); merge(rt,rt,tot);
        }
        inline void reverse(RI l,RI r)
        {
            int x,y,z; split(rt,x,y,l-1); split(y,y,z,r-l+1);
            rever(y); merge(y,y,z); merge(rt,x,y);
        }
        inline int get_rk(int now)
        {
            stack[top=1]=now; for (int t=now;fa(t);t=fa(t))	stack[++top]=fa(t);
            while (top) pushdown(stack[top--]); int ret=node[lc(now)].size;
            for (;now;now=fa(now)) if (now==rc(fa(now))) ret+=node[lc(fa(now))].size+1;
            return ret+1;
        }
        #undef lc
        #undef rc
}T;
int main()
{
    //freopen("CODE.in","r",stdin); freopen("CODE.out","w",stdout);
    RI i; for (F.read(n),i=1;i<=n;++i) F.read(a[i].val),a[i].id=i;
    for (sort(a+1,a+n+1),i=1;i<=n;++i) T.insert(i); for (i=1;i<=n;++i)
    rk=T.get_rk(a[i].id),F.write(rk),T.reverse(i,rk); return F.Fend(),0;
}
```



---

## 作者：南阳刘子骥 (赞：1)

题目要求我们对一个序列进行一系列反转操作，使得这个序列最终有序。

对于第 $i$ 次旋转，我们都需要找到第 $i$ 小的数，记其位置为 $p_i$，然后反转 $[i,p_i]$ 这段区间。

说到区间反转，我们就可以想到使用 Splay。  
这样就可以借鉴[文艺平衡树](https://www.luogu.com.cn/problem/P3391)的思路了。

我们每一次查询一个权值所对应的节点。找到我们需要反转的区间之后，将其左端点的前驱旋至根，然后将其右端点的后继旋至左端点前驱的下面，这样就拎出来了整个区间了。  
然后直接打反转标记即可。

但是我们还有一个问题。就是题目给出的序列是无序的，我们还需要自己排序。  
同时题目还要求我们做到稳定的排序。也就是两个物品如果高度相等，排序后它们的相对位置关系需要与初始时相同。  
那么我们拿一个结构体记录一下每一个物品的高度和一开始的位置，然后按照权值排序。

然后我们再建立一颗 Splay，像上面说的那样维护、反转区间就可以了。

同时题目要求输出第 $i$ 低的物品在操作之前的位置，我们就先将其代表的节点旋到根，其当前在序列内的位置就是其左子树的大小加上 1。  
这里我向序列中加入了两个哨兵节点，这样会使左子树的大小增加 1，直接输出左子树的大小就可以了。

代码如下：

``` cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010;
const int INF = 1e8;
int n, m;
struct Node
{
	int s[2], fa;
	int v, sz;
	int flag;
};
Node tr[N];
int rt;
void maintain(int p)
{
	tr[p].sz = tr[tr[p].s[0]].sz + tr[tr[p].s[1]].sz + 1;
}
void pushdown(int p)
{
	if(tr[p].flag)
	{
		if(tr[p].s[0])tr[tr[p].s[0]].flag ^= 1;
		if(tr[p].s[1])tr[tr[p].s[1]].flag ^= 1;
		swap(tr[p].s[0], tr[p].s[1]);
		tr[p].flag = 0;
	}
}
void rotate(int x)
{
	int y = tr[x].fa, z = tr[y].fa;
	int k = (tr[y].s[1] == x) ? 1 : 0;
	tr[z].s[tr[z].s[1] == y] = x, tr[x].fa = z;
	tr[y].s[k] = tr[x].s[k ^ 1], tr[tr[x].s[k ^ 1]].fa = y;
	tr[x].s[k ^ 1] = y, tr[y].fa = x;
	maintain(y); maintain(x);
}
void splay(int x, int k)
{
	while(tr[x].fa != k)
	{
		int y = tr[x].fa, z = tr[y].fa;
		pushdown(z), pushdown(y), pushdown(x);
		if(z != k)
		{
			if((tr[y].s[1] == x) ^ (tr[z].s[1] == y)) rotate(x);
			else rotate(y);
		}
		rotate(x);
	}
	if(!k)rt = x;
}
void build(int &p, int l, int r)
{
	if(l > r)return;
	int mid = (l + r) >> 1;
	p = mid;
	if(l == r)
	{
		tr[p].sz = 1;
		return;
	}
	if(l < mid)
	{
		build(tr[p].s[0], l, mid - 1);
		tr[tr[p].s[0]].fa = p;
	}
	if(r > mid)
	{
		build(tr[p].s[1], mid + 1, r);
		tr[tr[p].s[1]].fa = p;
	}
	maintain(p);
}
int get_k(int k)
{
	int p = rt;
	while(true)
	{
		pushdown(p);
		if(tr[tr[p].s[0]].sz >= k && tr[p].s[0])p = tr[p].s[0];
		else
		{
			k -= tr[tr[p].s[0]].sz + 1;
			if(k == 0)return p;
			else p = tr[p].s[1];
		}
	}
}
struct TBS
{
	int x, pos;
	bool operator < (const TBS &a)const
	{
		return (x == a.x) ? pos < a.pos : x < a.x;
	}
}p[N];
int main()
{
	scanf("%d", &n);
	p[1] = { -INF,1 }, p[n + 2] = { INF,n + 2 };
	for(int i = 2; i <= n + 1; i++)
	{
		scanf("%d", &p[i].x);
		p[i].pos = i;
	}
	sort(p + 2, p + 2 + n);
	build(rt, 1, n + 2);
	for(int i = 2; i <= n; i++)
	{
		splay(p[i].pos, 0);
		int ans = tr[tr[rt].s[0]].sz;
		printf("%d ", ans);
		int L = get_k(i - 1);
		int R = get_k(ans + 2);
		splay(L, 0); splay(R, L);
		tr[tr[R].s[0]].flag ^= 1;
	}
	printf("%d\n", n);
	return 0;
}
```

[四](https://www.luogu.com.cn/problem/P4402) [倍](https://www.luogu.com.cn/problem/P3165) [经](https://www.luogu.com.cn/problem/SP2059) [验](https://www.luogu.com.cn/problem/UVA1402)


---

## 作者：Erotate (赞：0)

### 题目大意：

给定一个有 $n$ 个数的序列，然后进行 $n$ 次操作。对于第 $i$ 次操作，记第 $i$ 小值在序列中的位置为 $k$，先输出 $k$，再把 $[i,k]$ 的区间翻转一次。

---
看到区间翻转，区间第 $k$ 小这两个操作，自然而然地就想到了伸展树。

我们发现，在操作中，并不关心每个元素的具体值，而是关心每个元素的位置。那么我们记录两个值，一个是元素在数列中的下标，另一个是元素的值，然后按值从小到大排序，值相同的按下标排序即可。**注意，记得插入哨兵。**

排完序后，值就没用了（因为已经单调递增了），直接建树即可。然后，我们想一想，既然已经单调递增了，那查询第 $k$ 小的时候是不是把序列中对应的下标旋转到根之后，左子树的大小加一就是就是答案了（注意，是下标，不是元素值，所以可以这样做）。最后在找到之后把要反转的区间反转一下一下即可。

### 注意：尽可能的多下传懒惰标记，能下传就下传！

代码：
```cpp
#include<bits/stdc++.h>
#define int long long
#define N 100005
#define inf 1000000007
using namespace std;
struct Splay{
    int f,s[2],sz,rev;
}tr[N];
struct num{
    int id,h;
}a[N];
int n,rt;
bool cmp(num x,num y){
    return x.h==y.h?x.id<y.id:x.h<y.h;
}
void push_up(int k){
    tr[k].sz=tr[tr[k].s[0]].sz+tr[tr[k].s[1]].sz+1;
}
void push_down(int k){
    if(!tr[k].rev) return;
    if(tr[k].s[0]) tr[tr[k].s[0]].rev^=1;
    if(tr[k].s[1]) tr[tr[k].s[1]].rev^=1;
    swap(tr[k].s[1],tr[k].s[0]);
    tr[k].rev=0;
}
void rotate(int x){
    int y=tr[x].f,z=tr[y].f,k=(tr[y].s[1]==x);
    push_down(y),push_down(x);
    tr[x].f=z,tr[z].s[tr[z].s[1]==y]=x;
    tr[y].s[k]=tr[x].s[k^1],tr[tr[x].s[k^1]].f=y;
    tr[x].s[k^1]=y,tr[y].f=x;
    push_up(y),push_up(x);
}
void splay(int x,int goal){
    while(tr[x].f!=goal){
        int y=tr[x].f,z=tr[y].f;
        if(z!=goal) push_down(z);
        push_down(y),push_down(x);
        if(z!=goal) rotate((tr[y].s[1]==x)^(tr[z].s[1]==y)?x:y);
        rotate(x);
    }
    if(!goal) rt=x;
}
void build(int l,int r,int fa){
    if(l>r) return;
    int mid=l+r>>1;
    if(mid<fa) tr[fa].s[0]=mid;
    else tr[fa].s[1]=mid;
    tr[mid].sz=1,tr[mid].f=fa;
    build(l,mid-1,mid);
    build(mid+1,r,mid);
    push_up(mid);
}
int find(int v){
    int x=rt;
    while(1){
        push_down(x);
        if(v<=tr[tr[x].s[0]].sz && tr[x].s[0]) x=tr[x].s[0];
        else{
            v-=tr[tr[x].s[0]].sz+1;
            if(v==0) return x;
            else x=tr[x].s[1];
        }
    }
}
void reverse(int l,int r){
    l=find(l-1),r=find(r+1);
    splay(l,0),splay(r,l);
    tr[tr[tr[rt].s[1]].s[0]].rev^=1;
}
signed main(){
    scanf("%lld",&n);
    for(int i=2;i<=n+1;++i){
        scanf("%lld",&a[i].h);
        a[i].id=i;
    }
    a[1].h=-inf,a[n+2].h=inf,a[1].id=1,a[n+2].id=n+2;
    sort(a+1,a+n+3,cmp);
    build(1,n+2,0);
    rt=n+3>>1;
    for(int i=2;i<=n;++i){
        splay(a[i].id,0);
        int ans=tr[tr[rt].s[0]].sz+1;
        printf("%lld ",ans-1);
        reverse(i,ans);
    }
    printf("%lld",n);
    return 0;
}
```


---

## 作者：MiniLong (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P4402)

## 题意

给定 $n$ 个整数 $p_1, p_2, p_3 \dots p_n $，$ n $ 次操作分别输出第 $i$ 小值在区间内的位置 $ k $，且翻转区间 $[i, k]$。

## 思路

从**区间翻转**能看出是用 splay 区间树，但 $k$ 小值无法在区间树中维护。

又因为题目只要求输出值的位置，所以考虑将原数组按高度为第一关键字，编号为第二关键字排序一遍，按照编号建树，然后把原数组中第 $k$ 个数值的编号旋转到根，它的左子树的 $ siz $（左子树的 $siz + 1$ 再减去哨兵的 $1$）就是它的位置了（因为排序后是单调递增的）。

接着是翻转操作，就是个 splay 的模板了，将排名为 $i$ 的值转到根，再把刚刚求出来的 $k+2$ 转到根的右子树（因为有哨兵，所以都要加一），这时根的右子树的左子树就是区间 $[i, k]$ 了，然后交换一下它的左右儿子，打个标记就好了。

**注意：标记一定要多 pushdown，在 rotate 和 getk 中都要下传！！！**

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
namespace fastio{
    template<typename T> inline void read(T &t){
        int x = 0, f = 1;
        char c = getchar();
        while(!isdigit(c)){
            if(c == '-') f = -f;
            c = getchar();
        }
        while(isdigit(c)) x = x * 10 + c - '0', c = getchar();
        t = x * f;
    }
    template<typename T, typename ... Args> inline void read(T &t, Args&... args){
        read(t);
        read(args...);
    }
    template<typename T> void write(T t){
        if(t < 0) putchar('-'), t = -t;
        if(t >= 10) write(t / 10);
        putchar(t % 10 + '0');
    }
    template<typename T> void writeln(T t){
        write(t);
        puts("");
    }
};
using namespace fastio;
const int N = 100005, inf = 0x3f3f3f3f;
int n, id[10000005];
struct node{
    int x, id;
    bool operator<(const node b)const{
        if(x == b.x) return id < b.id;
        return x < b.x;
    }
}w[N];
int cnt, rt;
struct Tree{
    int fa, son[2], val, rev, siz;
    #define ls a[x].son[0]
    #define rs a[x].son[1]
}a[N];
int New(int fa, int val){
    a[++cnt] = Tree{fa, {0, 0}, val, 0, 1};
    return cnt;
}
void update(int x){
    a[x].siz = a[ls].siz + a[rs].siz + 1;
}
void pushr(int x){
    swap(ls, rs);
    a[x].rev ^= 1;
}
void pushdown(int x){
    if(a[x].rev){
        if(ls) pushr(ls);
        if(rs) pushr(rs);
        a[x].rev = 0;
    }
}
void rotate(int x){
    int y = a[x].fa, z = a[y].fa, k = a[y].son[1] == x;
    pushdown(y), pushdown(x);
    a[z].son[a[z].son[1] == y] = x, a[x].fa = z;
    a[y].son[k] = a[x].son[k ^ 1], a[a[x].son[k ^ 1]].fa = y;
    a[x].son[k ^ 1] = y, a[y].fa = x;
    update(y), update(x);
}
void splay(int x, int goal){
    while(a[x].fa != goal){
        int y = a[x].fa, z = a[y].fa;
        if(z != goal) rotate((a[z].son[1] == y) ^ (a[y].son[1] == x) ? x : y);
        rotate(x);
    }
    if(!goal) rt = x;
}
int getk(int k){
    int x = rt;
    while(1){
        pushdown(x);
        if(k <= a[ls].siz) x = ls;
        else if(k <= a[ls].siz + 1){
            splay(x, 0);
            return x;
        }
        else k -= a[ls].siz + 1, x = rs;
    }
}
void build(int &x, int l, int r, int fa){
    if(l > r) return;
    int mid = l + r >> 1;
    x = mid, a[x] = Tree{fa, {0, 0}, w[mid].id, 0, 1};
    build(ls, l, mid - 1, x);
    build(rs, mid + 1, r, x);
    update(x);
}
int Find(int val){
    int x = rt;
    while(1){
        if(val == a[x].val){
            splay(x, 0);
            return x;
        }
        if(val < a[x].val) x = ls;
        else x = rs;
    }
}
void Reverse(int l, int r){
    int x = getk(l), y = r;
    splay(x, 0), splay(y, x);
    // cout << x << ' ' << y << endl;
    pushr(a[y].son[0]);
}
void debug(int x, bool f = 1){
    pushdown(x);
    if(f) cout << "=================" << '\n';
    printf("num: %d, val: %d, ls: %d, rs: %d, fa: %d\n", x, a[x].val, a[ls].val, a[rs].val, a[a[x].fa].val);
    if(ls) debug(ls, 0);
    if(rs) debug(rs, 0);
}
void dfs(int x){
    pushdown(x);
    if(ls) dfs(ls);
    if(a[x].val != inf && a[x].val != -inf) putchar(' ');
    if(rs) dfs(rs);
}

int main(){
    read(n);
    for(int i = 2; i <= n + 1; ++i){
        read(w[i].x), w[i].id = i;
    }
    w[1].x = -inf, w[n + 2].x = inf, w[1].id = 1, w[n + 2].id = n + 2;
    sort(w + 1, w + 3 + n);
    build(rt, 1, n + 2, 0);
    // debug(rt);
    for(int i = 2; i <= n + 1; ++i){
        splay(w[i].id, 0);
        // cout << id[w[i].id] << endl;
        int k = a[a[rt].son[0]].siz + 1;
        // debug(rt);
        write(k - 1), putchar(' ');
        int x = getk(i - 1), y = getk(k + 1);
        splay(x, 0), splay(y, x);
        pushr(a[y].son[0]);
        // debug(rt);
        // puts("");
    }
    return 0;
}
```

---

## 作者：alvis (赞：0)

## $\texttt{Content}$

给定一个长度为 $n$ 的序列，第 $i$ 次操作找到 $[i,n]$ 中最小值 $p_j$，并将区间 $[i,j]$ 翻转，使得实现一种**稳定**排序的效果。输出每次查询出的 $j$。

## $\texttt{Solution}$

很显然的 splay 板子。~~但是很难调~~

因为要实现的是区间反转操作，那么建树的时候就不是以当前点的权值建了，而是以当前点的位置来建。

所以就可以把输进去的值，排一下序，然后就按照下标插入到树里。由于我们按照权值从小到大排的，所以我们也知道了每次操作的 $P_j$ 是多少。

获取结果的时候，就把目标位置转到树顶，然后输出一下左子树大小即可。（加上自己，再减去哨兵节点相当于没有加）

然后区间翻转就是很 naive 的文艺平衡树操作了。

不知道为啥我 cout 跑的超级慢，然后就挂了很多次。

## $\texttt{Code}$
```cpp
#include <bits/stdc++.h>
using namespace std;

void qread(int &x) {
	int sum = 0;char c = getchar();
	while(c >= '0' && c <= '9') sum = sum * 10 + c -'0', c = getchar();
	x = sum;
}

const int N = 1e6+5, MAXN = 1e8;
//输入的序列
struct node {
	int v, id;
	node(){}
	node(int _v, int _id){
		v = _v, id = _id;
	}
}num[N];
struct spl{
	node v;
	int s[2], p, minn;
	int size, cnt, fl;
}g[N];
int n ,rt, idx;

//向上合并
void pushup(int u) {
	g[u].size = g[g[u].s[0]].size + g[g[u].s[1]].size + 1; 
	g[u].minn = min(g[u].v.v, min(g[g[u].s[0]].minn, g[g[u].s[1]].minn));
}

//传下翻转标记
void pushdown(int u) {
	if(g[u].fl) {
		swap(g[u].s[0], g[u].s[1]);
		g[g[u].s[0]].fl ^= 1;
		g[g[u].s[1]].fl ^= 1;
		g[u].fl = 0;
	}
}

//splay 板子
void ro(int u) {
	int x = g[u].p, y = g[x].p;
	int k = g[x].s[1] == u;
	g[y].s[g[y].s[1] == x] = u, g[u].p = y;
	g[x].s[k] = g[u].s[k^1], g[g[u].s[k^1]].p = x;
	g[u].s[k^1] = x, g[x].p = u;
	pushup(x); pushup(u);
}

void splay(int u, int k) {
	while(g[u].p != k) {
		int x = g[u].p;
		int y = g[x].p;
		if(y != k) {
			if((g[x].s[1] == u) ^ (g[y].s[1] == x)) ro(u);
			else ro(x);
		}
		ro(u);
	}
	if(!k) rt = u;
}

//插入
void insert(node v) {
	int u = rt, p = 0;
	while(u) p = u, u = g[u].s[v.id > g[u].v.id];
	if(u) {
		g[u].cnt ++;
	}else {
		u = ++ idx;
		if(p) g[p].s[v.id > g[p].v.id] = u;
		g[u].p = p;
		g[u].minn = v.v;
		g[u].size = 1;
		g[u].v = v;
	}
	splay(u, 0);
}

int find_min(int u) {
	while(true) {
		pushdown(u);
		if(g[u].minn == g[u].v.v) return u;
		if(g[u].minn == g[g[u].s[0]].minn) u = g[u].s[0];
		else u = g[u].s[1];
	}
}

int get_k(int k) {
	int u = rt;
	while(true) {
		pushdown(u);
		if(k > g[g[u].s[0]].size + 1) k -= g[g[u].s[0]].size + 1, u = g[u].s[1];
		else if(k == g[g[u].s[0]].size + 1) return u;
		else u = g[u].s[0];
	} 
	return u;
}

bool cmp(node a, node b) {
	if(a.v == b.v) return a.id < b.id;
	return a.v < b.v; 
}

int main() {
		qread(n);
		if(n == 0) {
			break;
		}
		idx = rt= 0;
		//建树
		//插入哨兵节点
		insert(node(MAXN, 1));
		insert(node(MAXN, n+2));
		g[0].minn = g[0].v.v = MAXN;
		for(int i = 1;i <= n;i ++) {
			qread(num[i].v);
			num[i].id = i;
		}
		
		sort(num+1, num+1+n, cmp);
		for(int i = 1;i <= n;i ++) insert(node(i, num[i].id+1)); 
		
		for(int i = 1;i <= n;i ++) {
			//找到目标节点
			int l = get_k(i), r = get_k(n+2);
			splay(l, 0); splay(r, l); 
			int x = find_min(g[r].s[0]);
			splay(x, 0);
			printf("%d ", g[g[rt].s[0]].size);
			l = get_k(i), r = get_k(g[g[rt].s[0]].size + 2);
			splay(l, 0);splay(r, l);
			g[g[r].s[0]].fl ^= 1; 
		}
		puts("");
		//清空数组
	return 0;
}
```

---

## 作者：Su_Zipei (赞：0)

### 不知道为啥难度是黑的。。。

一直对Splay维护区间操作不是很熟练，但是这道题让我学到了很多东西所以写篇题解来巩固一下。

首先模板题是比较好写的因为只有一个权值不需要转化，直接进行区间翻转即可，不过要注意区间反转之后元素的大小关系就发生了变化，即关键字大的就不一定在当前的平衡树中大，因为平衡树的大小关系实际上映射了整个序列。

那么考虑这道题，首先要知道需要干什么，区间翻转操作很好实现，打个标记就完了，但是找到翻转的区间就不那么容易了，可以发现第$i$小值是当前序列中从$i-n$的最小值，因为比它小的都去了前边，所以我们只需要知道最小值的位置就行了，但是如果按照题目中给的权值，最小值可能不唯一，于是先处理一下每个点的权值，因为可能会出现相等的情况，而题目中要求相等的按照下标排序，按照它的要求做就行了。

下面如何进行操作呢？

首先要把我当前处理的$i-n$区间转到右子树，然后找到其中的最小值，这时最小值一定是我要翻转的那个区间的右端点，所以直接对这个区间进行翻转，不过需要注意的是，Splay中第$k$大的元素就是序列中的第$k$个值，最开始这里没想明白然后就挂了。

Splay维护序列的本质就是用k$大的元素表示序列中的第$k$个值。

```
/*
6
3 4 5 1 6 2
4
3 3 2 1
0
*/
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=1e6+10;
struct Node{
	int id,x;
	Node(){}
	Node(int a,int b){id=a;x=b;}
	bool operator < (const Node&A)const{
		if(x==A.x)return id<A.id;
		return x<A.x;
	}
}a[N];
struct Splay_Tree{
	Node v[N];
	int fa[N],siz[N],Min[N],tag[N],ch[N][2],cnt,rt;
	void clear(){
		memset(fa,0,sizeof(fa));
		memset(siz,0,sizeof(siz));
		memset(Min,0,sizeof(Min));
		memset(tag,0,sizeof(tag));
		memset(ch,0,sizeof(ch));
		cnt=rt=0;
	}
	void up(int x){
		siz[x]=siz[ch[x][0]]+siz[ch[x][1]]+1;
		Min[x]=min(v[x].x,min(Min[ch[x][0]],Min[ch[x][1]]));
	}
	void down(int x){
		if(tag[x]){
			tag[ch[x][0]]^=1;
			tag[ch[x][1]]^=1;
			swap(ch[x][0],ch[x][1]);
			tag[x]=0;
		}
	}
	void rotate(int x){
		int y=fa[x];int z=fa[y];
		int k=ch[y][1]==x;
		ch[z][ch[z][1]==y]=x;
		fa[x]=z;
		ch[y][k]=ch[x][k^1];
		fa[ch[x][k^1]]=y;
		ch[x][k^1]=y;
		fa[y]=x;
		up(y);up(x);
	}
	void splay(int x,int to){
		while(fa[x]!=to){
			int y=fa[x];int z=fa[y];
			if(z!=to)
				(ch[y][1]==x)==(ch[z][1]==y)?rotate(y):rotate(x);
			rotate(x);
		}
		if(!to)rt=x;
	}
	void insert(Node a){
		int u=rt,ff=0;
		while(u)ff=u,u=ch[u][a.id>v[u].id];
		u=++cnt;
		fa[u]=ff;v[u]=a;siz[u]=1;Min[u]=v[u].x;
		if(ff)ch[ff][v[u].id>v[ff].id]=u;
		splay(u,0);
	}
	int kth(int x){
		int u=rt;
		while(1){
			down(u);
			int y=ch[u][0];
			if(siz[y]+1<x)x-=siz[y]+1,u=ch[u][1];
			else if(x<=siz[y])u=y;
			else return u;
		}
	}
	int get(int u){
		while(1){
			down(u);
			if(Min[u]==v[u].x)return u;
			if(Min[u]==Min[ch[u][0]])u=ch[u][0];
			else u=ch[u][1];
		}
	}
	void solve(int x,int n){
		int l=kth(x),r=kth(n+2);
		splay(l,0);
		splay(r,l);
		int now=get(ch[r][0]);
		splay(now,0);
		printf("%d",siz[ch[rt][0]]);
		l=kth(x);r=kth(siz[ch[rt][0]]+2);
		splay(l,0);
		splay(r,l);
		tag[ch[r][0]]^=1;
	}
}s;
int main(){
	int n;
	while(~scanf("%d",&n)){
		if(n==0)return 0;
		s.clear();
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i].x);
			a[i].id=i;
		}
		sort(a+1,a+n+1);
		s.insert(Node(1,0x7f7f7f7f));
		s.insert(Node(n+2,0x7f7f7f7f));
		s.v[0].x=s.Min[0]=0x7f7f7f7f;
			for(int i=1;i<=n;i++)
			s.insert(Node(a[i].id+1,i));
		for(int i=1;i<=n;i++){
			s.solve(i,n);
			if(i==n)printf("\n");
			else printf(" ");
		}
	}
	return 0;
}

```


---

