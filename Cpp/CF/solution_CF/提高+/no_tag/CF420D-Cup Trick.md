# Cup Trick

## 题目描述

The employees of the F company have lots of ways to entertain themselves. Today they invited a famous magician who shows a trick with plastic cups and a marble.

The point is to trick the spectator's attention. Initially, the spectator stands in front of a line of $ n $ plastic cups. Then the magician places a small marble under one cup and shuffles the cups. Then the spectator should guess which cup hides the marble.

But the head coder of the F company isn't easy to trick. When he saw the performance, he noticed several important facts:

- each cup contains a mark — a number from $ 1 $ to $ n $ ; all marks on the cups are distinct;
- the magician shuffles the cups in $ m $ operations, each operation looks like that: take a cup marked $ x_{i} $ , sitting at position $ y_{i} $ in the row of cups (the positions are numbered from left to right, starting from 1) and shift it to the very beginning of the cup row (on the first position).

When the head coder came home after work he wanted to re-do the trick. Unfortunately, he didn't remember the starting or the final position of the cups. He only remembered which operations the magician performed. Help the coder: given the operations in the order they were made find at least one initial permutation of the cups that can go through the described operations in the given order. Otherwise, state that such permutation doesn't exist.

## 样例 #1

### 输入

```
2 1
2 1
```

### 输出

```
2 1 
```

## 样例 #2

### 输入

```
3 2
1 2
1 1
```

### 输出

```
2 1 3 
```

## 样例 #3

### 输入

```
3 3
1 3
2 3
1 3
```

### 输出

```
-1
```

# 题解

## 作者：golden_brick (赞：4)

# CF420D Cup Trick

[题目传送门](https://www.luogu.com.cn/problem/CF420D)

---

**题目大意：**

有一个你不知道长啥样的排列。

给你一堆操作，每个操作都有一个 $x$ 和一个 $y$，要你把在第 $y$ 个位置上的数 $x$ 扔到最前面去。

要你求可能的原排列中字典序最小的那个。

---

**fhq 做法：**

我们发现正着做有些难度，所以考虑倒着来做操作。

用一个文艺 fhq 来维护这个排列。

我们不知道最后的排列长什么样，所以我们在 fhq 里插入 $n$ 个 $0$ 表示未知数。

对于每一个操作 $x, y$，把 fhq 分裂成 $1-1$，$2-y$，$y+1-n$ 这三个部分，将它们称为 $l$、$m$、$r$，前两部分逆序合并即可。

手玩一组数据：

```
4 3
3 4
2 2
4 3
```

```
0 0 0 0  // fhq 初始化为 0
```

将 3 位置上的 4，放到 1 号位置，倒着来做，也就是将 4 插入到 3 号位置后

```
0 0 4 0 
```

将 2 位置上的 2 放到 1 号位置，也就是将 2 插入到 2 号位置后

```
0 2 4 0
```

将 4 位置上的 3 放到 1 号位置，也就是将 3 插入到 4 号位置后

```
2 4 0 3
```

答案就是 `2 4 1 3`。

注意一下，以下情况无解：

- 如果 $l$ 值不为 $0$ 且不等于 $x$，则无解。
- 如果 $l$ 不等于 $x_i$，且 $x_i$ 在之前处理的操作中已经出现过，则无解。

最后只需要按顺序输出即可，对于剩下的未知数，就在没出现过的数中按顺序给他排上就行了。

放上~~简洁明了~~的代码（附赠精美注释）

```cpp
#include <bits/stdc++.h>
#define fi first
#define se second
#define il inline
#define ls(u) fhq[u].l
#define rs(u) fhq[u].r
#define INF 0x3f3f3f3f
using namespace std;
typedef long long ll;
/*此处省略 35 行快读*/
const int N = 1e6 + 10;
/*以下为 fhq 模板*/
mt19937 rnd(114514);
struct Node
{
    int l, r;
    int val, key;
    int siz;
} fhq[N];
int ncnt, root;
il int newnode(int val)
{
    fhq[++ncnt].val = val;
    fhq[ncnt].key = rnd();
    fhq[ncnt].siz = 1;
    return ncnt;
}
il void pushup(int u) { fhq[u].siz = fhq[ls(u)].siz + fhq[rs(u)].siz + 1; }
int merge(int x, int y)
{
    if (!x || !y)
        return x | y;
    if (fhq[x].key < fhq[y].key)
    {
        fhq[x].r = merge(fhq[x].r, y);
        pushup(x);
        return x;
    }
    else
    {
        fhq[y].l = merge(x, fhq[y].l);
        pushup(y);
        return y;
    }
}
void split(int u, int &x, int &y, int k)
{
    if (!u)
    {
        x = y = 0;
        return;
    }
    int lk = fhq[ls(u)].siz + 1;
    if (lk <= k)
        x = u, split(rs(u), rs(x), y, k - lk);
    else
        y = u, split(ls(u), x, ls(y), k);
    pushup(u);
}
/*以上为 fhq 模板*/
bool vis[N];
int n, m, acnt = 1;
pair<int, int> q[N];
void print(int u) // 输出
{
    if (!u)
        return;
    print(ls(u));
    if (fhq[u].val) write(fhq[u].val), putchar(' ');
    else
    {
        while (vis[acnt]) acnt++;
        write(acnt), putchar(' ');
        vis[acnt] = 1;
    }
    print(rs(u));
}
signed main()
{
    read(n, m);
    for (int i = 1; i <= m; i++)
        read(q[i].fi, q[i].se);
    for (int i = 1; i <= n; i++) // 把 n 个 0 插到 fhq 里
        root = merge(root, newnode(0));
    for (int i = m, x, y, z; i >= 1; i--) // 逆序处理
    { // 此处的 x,y,z 就是题解里的 l,m,r
        split(root, x, y, 1), split(y, y, z, q[i].se - 1); // 分裂
        if (fhq[x].val != q[i].fi && (fhq[x].val || vis[q[i].fi]))
        { // 判断无解
            puts("-1");
            return 0;
        }
        fhq[x].val = q[i].fi;
        vis[q[i].fi] = 1;
        root = merge(merge(y, x), z);
    }
    print(root); // 完美的输出
    return 0; // 优雅的结束程序
}
```

看到这里，先别走，其实我们可以正着做。

---

**树状数组做法**

上面那个做法用 fhq 来维护的原因是数组插入操作十分难搞。

所以我们这个做法直接将数组开成两倍大。

由于一开始后面是有数的，所以后半部分一开始全是一。

插到前面就相当于当前位置减一，再在前面那一半加上加一。

这个数组用树状数组维护一下。

想找到某个位置上的数，只需二分一下即可。

另一个数组，与这个数组同步操作，只不过他存的是每个点的值。

我们发现，一次操作中将一个数从后一半插进了前一半，那所有操作前他就是这个位置。

从头到尾做完所有操作后，对于剩下的未知数，就在没出现过的数中按顺序给他排上就行了。

放上真正简洁明了的代码：

```cpp
#include <bits/stdc++.h>
#define il inline
#define lb(x) (x & -x)
#define INF 0x3f3f3f3f
using namespace std;
typedef long long ll;
/*此处省略 35 行快读*/
const int N = 1e6 + 10;
const int M = 1e6 + 5;
int n, m;
int a[N << 1], ans[N], c[N << 1];
bool vis[N];
il void add(int x, int val)
{
    for (; x <= M << 1; x += lb(x))
        c[x] += val;
}
il int query(int x)
{
    int res = 0;
    for (; x; x -= lb(x))
        res += c[x];
    return res;
}
signed main()
{
    for (int i = 1; i <= M; i++)
        add(i + M, 1);
    read(n, m);
    for (int i = 1, p = M, x, y; i <= m; i++)
    {
        read(x, y);
        int l = 1, r = M << 1, pos = -1;
        while (l <= r)
        {
            int mid = l + r >> 1;
            if (query(mid) < y)
                pos = l = mid + 1;
            else
                r = mid - 1;
        }
        if (pos > M)
        {
            if (vis[x])
            {
                puts("-1");
                return 0;
            }
            vis[x] = 1;
            ans[pos - M] = x;
        }
        else
        {
            if (a[pos] != x)
            {
                puts("-1");
                return 0;
            }
        }
        a[p] = x;
        add(pos, -1), add(p--, 1);
    }
    for (int i = 1, j = 1; i <= n; i++)
    {
        if (!ans[i])
        {
            while (vis[j])
                j++;
            ans[i] = j;
            vis[j] = 1;
        }
        write(ans[i]), putchar(' ');
    }
    return 0;
}
```

---

## 作者：Ryo_Yamada (赞：3)

比较直接的平衡树板子题，但是因为一些 nt 问题调了一天。

先按位置建一棵平衡树，然后从后向前做。开始每个节点的值都为 $0$。每次将平衡树按位置分裂：$1$，$2 \sim y_i - 1$，$y_i \sim n$。然后将第位置 $1$ 赋值为 $x_i$，接到 $y_i-1$ 后面。

对于判断无解：

- 如果位置 $1$ 的节点值不为 $0$ 且不等于 $x_i$，输出 $-1$。  
- 如果位置 $1$ 的节点不等于 $x_i$ 且 $x_i$ 在前面的操作中已经出现过，输出 $-1$。

求答案就是平衡树的中序遍历。对于整个操作过程中都没有用到的节点，按字典序排序，赋值给在中序遍历过程中节点值为 $0$ 的节点。

$\text{Code}$：

```cpp

#define def(N, K, b) const K N = b;
#define rep(i, b, s) for(int i = (b); i <= (s); ++i)
#define per(i, b, s) for(int i = (b); i >= (s); --i)

#define ls(x) t[x].ch[0]
#define rs(x) t[x].ch[1]

def(N, int, 1e6 + 5)

struct Treap {
	int sze;
	int val, rnd;
	int ch[2];
	
	Treap(int k = 0) {
		sze = k;
		rnd = rand();
		val = ch[0] = ch[1] = 0;
	}
} t[N];

int n, m, root, cnt;
int x[N], y[N];
bool vis[N];
int ans[N];

void pushup(int id) { t[id].sze = t[ls(id)].sze + t[rs(id)].sze + 1; }

int merge(int x, int y) {
	if(!x || !y) return x + y;
	if(t[x].rnd < t[y].rnd) {
		rs(x) = merge(rs(x), y);
		pushup(x);
		return x;
	}
	else {
		ls(y) = merge(x, ls(y));
		pushup(y);
		return y;
	}
}

void split(int rt, int &x, int &y, int k) {
	if(!rt) return x = y = 0, void();
	int rk = t[ls(rt)].sze + 1;
	if(rk <= k) {
		x = rt;
		split(rs(rt), rs(x), y, k - rk);
	}
	else {
		y = rt;
		split(ls(rt), x, ls(y), k);
	}
	pushup(rt);
}

void init(int rt) {
	if(!rt) return ;
	init(ls(rt));
	ans[++cnt] = t[rt].val;
	init(rs(rt));
}

int main() {
	srand(19260817);
	qread(n, m);
	rep(i, 1, m) qread(x[i], y[i]);
	rep(i, 1, n) {
		t[i] = Treap(1);
		root = merge(root, i);
	}
	per(i, m, 1) {
		int l, mid, r;
		split(root, l, mid, 1);
		split(mid, mid, r, y[i] - 1);
		//cout << l << endl;

		if(t[l].val != x[i] && vis[x[i]]) {
			puts("-1");
			return 0;
		}
		if(t[l].val && t[l].val != x[i]) {
			puts("-1");
			return 0;
		}
		
		t[l].val = x[i], vis[x[i]] = true;
		root = merge(merge(mid, l), r);
	}
	init(root);
	int now = 1;
	rep(i, 1, n) {
		if(!ans[i]) {
			while(vis[now]) ++now;
			ans[i] = now;
			vis[now] = true;
		}
	}
	rep(i, 1, n) printf("%d ", ans[i]);
 	return 0;
}
```


---

## 作者：C_Pos_Princess (赞：0)

## 题解
既然给出了修改的顺序，那我们只需要倒退回去，也就是倒着将每一步还原，从而得到确定的数的位置，剩下未定的位置直接贪心选择最小的即可。

具体怎么操作呢？

这种插入的问题，我们考虑用平衡树。

首先先构造出大小为 $n$ 的树，这里直接插入 $n$ 个 0 即可，然后对于每一个操作进行修改，每次把这个第一个数删掉，然后把当前操作的数字查到他相应的位置即可。

### 代码
```cpp
int n, m;
struct node {
	int l, r;
	int val;
	int siz;
	int key;
} tr[N];
int root;
inline void pushup(int p) {
	tr[p].siz = tr[tr[p].l].siz + tr[tr[p].r].siz+1;
}
int idx;
inline int get_node(int key) {
	tr[++idx].val = rand();
	tr[idx].key = key;
	tr[idx].siz = 1;
	return idx;
}

inline void split(int p, int key, int &x, int &y) {

	if (!p) x = y = 0;
	else {

		if (tr[tr[p].l].siz+1 <= key) {
			x = p;
			split(tr[p].r, key-tr[tr[p].l].siz-1, tr[p].r, y);
		} else {
			y = p;
			split(tr[p].l, key, x, tr[p].l);
		}
		pushup(p);
	}
}


inline int merge(int x, int y) {
	if (!x || !y) return x + y;
	if (tr[x].val < tr[y].val) {
		tr[x].r = merge(tr[x].r, y);
		pushup(x);
		return x;
	} else {
		tr[y].l = merge(x, tr[y].l);
		pushup(y);
		return y;
	}
}

inline void insert(int key) {
	root = merge(root,get_node(key));
}

int vis[N];
pii q[N];
int cnt = 1;

void print(int p) {
	if (!p) return;
	print(tr[p].l);
	if(tr[p].key) write(tr[p].key),SP;
	else{
		while(vis[cnt])cnt++;
		write(cnt);
//		write(cnt);
		SP;
		vis[cnt] = 1;
 	}
 	print(tr[p].r);
}

int main() {
	read(n, m);
	for (int i = 1; i <= n; i++) {
		insert(0);
	}
	for (int i = 1; i <= m; i++) {
		read(q[i].first, q[i].second);
	}
//	cout<<root<<endl;
	for (int i = m; i >= 1; i--) {
		int x, y, z;
		split(root, 1, x, y);
		split(y, q[i].second - 1, y, z);
		if (tr[x].key != q[i].first && (tr[x].key || vis[q[i].first])) {
			puts("-1");
			return 0;
		}
		tr[x].key = q[i].first;
		vis[q[i].first] = 1;
		root = merge(merge(y,x), z);
	}

//	cout<<root<<endl;
	print(root);
	return 0;
}
```

---

## 作者：Cry_For_theMoon (赞：0)

[传送门](https://codeforces.com/contest/420/problem/D)

CSP 前一晚写的题...

#### 分析：

**不用平衡树也能做。**

### Part1：

先考虑给定了初始排列，和若干次操作，判断能否成功执行。

当然是平衡树板题，不会怎么办，可以线段树。

具体说来，我们发现对于两次对 $x$ 纸杯的操作 $l\lt r$（它们中间不再有对 $x$ 纸杯的操作）来说，第一次操作 $x$ 会到 $1$，然后它的移动步数等于操作区间 $(l,r)$ 里被操作过的纸杯个数（如果一个纸杯被操作多次只计数一次）。

所以变成了右端点递增，每次查询区间颜色数的经典题。

不会的左转 [P4065](https://www.luogu.com.cn/problem/P4065)，对此部分不再赘述。

### Part2：

你发现若 $x$ 纸杯初始位置为 $pos$，其第一次操作是第 $i$ 次，则它在第 $i$ 次那个时候被操作前，位置应该是 $pos+cnt$，其中 $cnt$ 是操作区间 $[1,i)$ 里被操作过的纸杯个数（同样多个只贡献一次）。

这个东西只要你从小到大枚举操作，然后如果该操作的纸杯是第一次被操作那么操作序列上后缀加一就行了，用 BIT（我开始线段树被卡常了，因为后面还要二分）。

我们设维护出的这个东西为 $f_i$，那么纸杯 $x$ 的初始位置就必须是 $pos+f_{pos}=y$ 的 $pos$。同时 $pos$ 处未被之前的纸杯占据。

首先发现这东西单调上升，但是可能会取等号，然后发现如果取等号的话，即有一段连续位置的值相等，只可能最右边那个位置是空的（自己模拟一下，请）。

所以直接二分出最大的 $pos$ 满足 $pos+f_{pos}=y$ 即可。前文提到过，由于 $f$ 是动态变化的所以使用 BIT 维护。

时间复杂度：$O((n+m)\log^2 n)$。

~~这tm才 2200*~~

```
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define per(i,a,b) for(int i=(a);i>=(b);i--)
#define op(x) ((x&1)?x+1:x-1)
#define odd(x) (x&1)
#define even(x) (!odd(x))
#define lc(x) (x<<1)
#define rc(x) (lc(x)|1)
#define lowbit(x) (x&-x)
#define Max(a,b) (a>b?a:b)
#define Min(a,b) (a<b?a:b)
#define next Cry_For_theMoon
#define il inline
#define pb(x) push_back(x)
#define is(x) insert(x)
#define sit set<int>::iterator
#define mapit map<int,int>::iterator
#define pi pair<int,int>
#define ppi pair<int,pi>
#define pp pair<pi,pi>
#define fr first
#define se second
#define vit vector<int>::iterator
#define mp(x,y) make_pair(x,y)
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef double db;
using namespace std;
const int MAXN=1e6+10;
int n,m,x[MAXN],y[MAXN];
int p[MAXN],vis[MAXN];
int ord[MAXN];
set<int>s;
vector<int>occ[MAXN];
struct BIT{
	ll tree[MAXN];
	void update(int x,int val){
		for(;x<=n;x+=lowbit(x))tree[x]+=val;
	}
	int q(int x){
		ll ret=0;
		for(;x;x-=lowbit(x))ret+=tree[x];
		return ret;
	}
	int query(int S){
		return q(n)-q(S-1);
	}
}tree1;
struct SegmentTree{
	ll sum[MAXN<<2],tag[MAXN<<2];
	void pushup(int x){sum[x]=sum[lc(x)]+sum[rc(x)];}
	void pushdown(int x,int l,int r){
		int mid=(l+r)>>1;
		sum[lc(x)]+=tag[x]*(mid-l+1);sum[rc(x)]+=tag[x]*(r-mid); 
		tag[lc(x)]+=tag[x];tag[rc(x)]+=tag[x];tag[x]=0;
	}
	void update(int x,int l,int r,int ql,int qr,ll val){
		if(ql<=l && qr>=r){sum[x]+=val*(r-l+1);tag[x]+=val;return;}
		pushdown(x,l,r);int mid=(l+r)>>1;
		if(ql<=mid)update(lc(x),l,mid,ql,qr,val);
		if(qr>mid)update(rc(x),mid+1,r,ql,qr,val);
		pushup(x);
	}
	ll query(int x,int l,int r,int ql,int qr){
		if(ql<=l && qr>=r)return sum[x];
		pushdown(x,l,r);int mid=(l+r)>>1;ll ret=0;
		if(ql<=mid)ret+=query(lc(x),l,mid,ql,qr);
		if(qr>mid)ret+=query(rc(x),mid+1,r,ql,qr);
		pushup(x);return ret;
	}
}tree2;
void solve1(){
	rep(i,1,m){if(ord[i]!=0)continue;
		int L=1,R=n,ret=-1;
		while(L<=R){
			int mid=(L+R)>>1;
			//找到最右边的=y[i]的位置
			ll val=mid+tree1.query(mid);
			if(val==y[i]){
				ret=mid;
				L=mid+1;
			}else if(val<y[i])L=mid+1;
			else R=mid-1;
		}
		if(ret==-1){printf("-1\n");exit(0);}
		if(p[ret]){printf("-1\n");exit(0);}
		vis[x[i]]=ret;
		p[ret]=x[i];
		tree1.update(ret,1);
	}
}
void add(int pos){
	int u=x[pos];
	if(ord[pos]==0){
		tree2.update(1,1,m,1,pos,1);
	}else{
		tree2.update(1,1,m,occ[u][ord[pos]-1]+1,pos,1);
	}
}
void solve2(){
	rep(i,2,m){
		add(i-1);if(ord[i]==0)continue;
		ll ret=0,u=x[i];
		if(occ[u][ord[i]-1]+1<i){
			ret=tree2.query(1,1,m,occ[u][ord[i]-1]+1,occ[u][ord[i]-1]+1);
		} 
		if(1+ret!=y[i]){
			printf("-1\n");exit(0);
		}
	}
}
il void Read(int& num){
	char ch;
	while((ch=getchar()) && !isdigit(ch));
	num=ch-'0';
	while((ch=getchar()) && isdigit(ch))num=num*10+ch-'0';
}
int main(){
	Read(n);Read(m);
	rep(i,1,m){
		Read(x[i]);Read(y[i]);
		ord[i]=occ[x[i]].size();
		occ[x[i]].pb(i);
	}
	solve1(); //construct a permutation
	solve2(); //check the permutation
	rep(i,1,n)if(!vis[i])s.is(i); 
	rep(i,1,n)if(!p[i]){
		p[i]=*s.begin();
		s.erase(p[i]);
	}
	rep(i,1,n)printf("%d ",p[i]);
	return 0;
}
```

---

