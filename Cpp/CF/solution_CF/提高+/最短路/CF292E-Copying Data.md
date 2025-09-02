# Copying Data

## 题目描述

We often have to copy large volumes of information. Such operation can take up many computer resources. Therefore, in this problem you are advised to come up with a way to copy some part of a number array into another one, quickly.

More formally, you've got two arrays of integers $ a_{1},a_{2},...,a_{n} $ and $ b_{1},b_{2},...,b_{n} $ of length $ n $ . Also, you've got $ m $ queries of two types:

1. Copy the subsegment of array $ a $ of length $ k $ , starting from position $ x $ , into array $ b $ , starting from position $ y $ , that is, execute $ b_{y+q}=a_{x+q} $ for all integer $ q $ $ (0<=q&lt;k) $ . The given operation is correct — both subsegments do not touch unexistent elements.
2. Determine the value in position $ x $ of array $ b $ , that is, find value $ b_{x} $ .

For each query of the second type print the result — the value of the corresponding element of array $ b $ .

## 样例 #1

### 输入

```
5 10
1 2 0 -1 3
3 1 5 -2 0
2 5
1 3 3 3
2 5
2 4
2 1
1 2 1 4
2 1
2 4
1 4 2 1
2 2
```

### 输出

```
0
3
-1
3
2
3
-1
```

# 题解

## 作者：Lee666666 (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF292E)

又是一道标签劝退题。

看到区间处理和 $10^5$ 的数据范围首先想到**线段树**处理。

因为 a 数组和 b 数组的元素是随机的，但**下标**是连续的，所以考虑用线段树维护 b 数组每个下标对应到 a 数组的下标（我们用 0 表示没有覆盖，所以**初始化**只要将值全部赋成0即可）。

但又因为这题的区间修改虽然是覆盖但并不是全部覆盖成一个值，而是覆盖成一个**公差**为 1 的递增序列，没法直接维护。于是注意到**公差**是一致的，所以我们可以用线段树维护下标的**差分序列**并支持区间求和，于是就可以直接区间覆盖了，求下标只需要求和就好了。

时间复杂度 $O(m \log n)$，实现有一些细节见代码注释。

```cpp
#include <cstdio>
using namespace std;

typedef long long LL;

const int maxn = 100015;

inline int read() {
    int s = 0, f = 1;
    char ch = getchar();
    while (ch < 48 || ch > 57) {
        if (ch == 45) {
            f = -1;
        }
        ch = getchar();
    }
    while (ch > 47 && ch < 58) {
        s = (s << 3) + (s << 1) + ch - 48;
        ch = getchar();
    }
    return s * f;
}

int n, m, a[maxn], b[maxn];
bool L[maxn << 2];
LL diff[maxn << 2], lazy[maxn << 2];

void pushup(int id) {
    diff[id] = diff[id << 1] + diff[id << 1 | 1];
    return;
}

void pushdown(int id, LL len) {
    if (L[id]) {
        lazy[id << 1] = lazy[id << 1 | 1] = lazy[id];
        diff[id << 1] = lazy[id] * (len - (len >> 1)); // 左右孩子的区间长度注意一下
        diff[id << 1 | 1] = lazy[id] * (len >> 1);
        L[id << 1] = L[id << 1 | 1] = 1;
        L[id] = 0;
    }
    return;
}

void update(int id, int l, int r, int x, int y, LL v) {
    if (x <= l && r <= y) {
        diff[id] = v * (r - l + 1);
        lazy[id] = v;
        L[id] = 1;
        return;
    }
    pushdown(id, r - l + 1);
    int mid = (l + r) >> 1;
    if (x <= mid) {
        update(id << 1, l, mid, x, y, v);
    }
    if (y > mid) {
        update(id << 1 | 1, mid + 1, r, x, y, v);
    }
    pushup(id);
    return;
}

LL query(int id, int l, int r, int x, int y) {
    if (x <= l && r <= y) {
        return diff[id];
    }
    pushdown(id, r - l + 1);
    int mid = (l + r) >> 1;
    LL res = 0;
    if (x <= mid) {
        res += query(id << 1, l, mid, x, y);
    }
    if (y > mid) {
        res += query(id << 1 | 1, mid + 1, r, x, y);
    }
    return res;
}

int main() {
    n = read();
    m = read();
    for (register int i = 1; i <= n; i++) {
        a[i] = read();
    }
    for (register int i = 1; i <= n; i++) {
        b[i] = read();
    }
    int t, x, y, k, tmp;
    while (m--) {
        t = read();
        if (t - 2) {
            x = read();
            y = read();
            k = read();
            /*
            区间修改要注意一下：
            众所周知，差分序列区间修改需要额外修改区间左端点和右端点的值
            这里我直接暴力求出需要知道的下标的值然后直接做减法并赋值
            但是需要注意的是顺序
            因为暴力求值须建立在该下标前的值都准确的前提下
            然而我们只修改一个差分值的操作是不完整的，也就是不准确的
            所以我们需要先右后左，避免这种不准确对答案带来的影响
            */
            if (y + k <= n) { // 右
                tmp = query(1, 1, n, 1, y + k);
                update(1, 1, n, y + k, y + k, tmp - x - k + 1);
            }
            if (y > 1) { // 左
                tmp = query(1, 1, n, 1, y - 1);
                update(1, 1, n, y, y, x - tmp);
            }
            else { // 别忘了处理左端点下表为 1 的特殊情况
                update(1, 1, n, y, y, x);
            }
            if (k > 1) {
                update(1, 1, n, y + 1, y + k - 1, 1);
            }
        }
        else {
            x = read();
            tmp = query(1, 1, n, 1, x);
            if (tmp) {
                printf("%d\n", a[tmp]);
            }
            else {
                printf("%d\n", b[x]);
            }
        }
    }
    return 0;
}
```

完结撒花~


---

## 作者：pigstd (赞：2)

线段树+差分。

用 $k_i$ 表示此时的 $b_i$ 的值为 $a_{k_i}$，如果 $k_i=0$ 则说明 $b_i$ 还没有被变过。那么显然对于一次修改操作，只要让 $k_y =x,k_{y+1}=x+1…k_{y+k-1}=x+k-1$ 就可以了。

但是如何维护这个 $k$ 呢？我们可以考虑差分。那么很显然，对于一次修改操作，那么 $k$ 的差分数据 $c$ 就会进行如下操作：$c_y = x - k_{y - 1},c_{y + 1} = c_{y + 2} = … = c_{ y + k - 1 } = 1, c_{ y + k } = k_{ y + k } - ( x + k - 1)$ ，用线段树维护这个 $c$ 就可以了。那么，$k$ 也就很容易求出来了。

[code](https://www.luogu.com.cn/paste/e5o5b8kj)。

---

## 作者：tzc_wk (赞：2)

这道题可以考虑使用线段树求解。线段树每个节点维护一个延迟标记$ lz $——对于每一个区间，如果它的$ lz $值为$ 0 $，那么表示该区间没有覆盖记录，否则它表示$ b $数组中该区间$ [l,r] $被a数组覆盖的左端点。

考虑延迟标记的下传：

设当前节点下标为$ k $

如果节点$ k $的$ lz $值为$ 0 $，那么就不用下传操作了。

如果节点$ k $的$ lz $值不是$ 0 $：

如果节点$ k $的表示区间为$ [L,R] $，那么它左儿子表示的区间为$ [L,\frac{L+R}{2}] $，右儿子表示的区间为$ [\frac{L+R}{2}+1,R] $。假设节点$ k $的$ lz $值为$ t $。则因为$ a $数组所覆盖区间的长度与$ b $数组被覆盖区间的长度相等，所以这个标记表示$ b $数组中的区间$ [L,R] $被$ a $数组中的$ [t,t+R-L+1] $覆盖。

再考虑它的子节点。首先左子节点的左端点$ L $下标被$ a $数组中的第$ t $个数覆盖，因此$ k $的左子节点的值就是$ t $。又根据它的区间长度为$ \frac{L+R}{2}-L+1 $，它的右端点被$ a $数组的第$ t+\frac{L+R}{2}-L $个数覆盖，因此节点$ k $的左子节点的右端点的后驱，即节点$ k $的右子节点的左端点，应被$ a[t+\frac{L+R}{2}-L+1] $覆盖，所以$ k $的右子节点的$ lz $为$ t+\frac{L+R}{2}-L+1 $。

上述操作写成代码就是这样：

```cpp
void pushdown(int k){
	if(!s[k].lz)	return;//如果它的lz为0，那么就直接结束
	s[k<<1].lz=s[k].lz;//将k的标记传给左儿子
	s[k<<1|1].lz=s[k<<1].r-s[k<<1].l+1+s[k].lz;//将k的标记传给右儿子
	s[k].lz=0;//清空k的标记
}
```

区间修改和单点查询没什么好说的，具体见注释：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,a[100005],b[100005];
struct node{
	int l,r,lz;//节点的结构体 l:左端点 r:右端点 lz:延迟标记
} s[400020];
void build(int k,int l,int r){//建树
	s[k].l=l;s[k].r=r;s[k].lz=0;
	if(l==r)	return;//如果递归到叶子节点，那么返回
	int mid=(l+r)>>1;
	build(k<<1,l,mid);//递归左子树
	build(k<<1|1,mid+1,r);//递归右子树
}
void pushdown(int k){//下传操作
	if(!s[k].lz)	return;//如果它的lz为0，那么就直接结束
	s[k<<1].lz=s[k].lz;//将k的标记传给左儿子
	s[k<<1|1].lz=s[k<<1].r-s[k<<1].l+1+s[k].lz;//将k的标记传给右儿子
	s[k].lz=0;//清空k的标记
}
void change(int k,int l,int r,int L,int R){
//区间修改 k:当前节点 
//l:要被覆盖的b数组的左端点 r:要被覆盖的b数组的右端点
//L:要覆盖的a数组的左端点 R:要覆盖的a数组的右端点
	if(l<=s[k].l&&s[k].r<=r){//如果当前区间已经被包含在要修改的区间里面了
		s[k].lz=L;//打上懒标记
		return;
	}
	pushdown(k);
	int mid=(s[k].l+s[k].r)>>1;
	if(r<=mid)		change(k<<1,l,r,L,R);//待修改区间完全在mid之前
	else if(l>mid)	change(k<<1|1,l,r,L,R);//待修改区间完全在mid之后
	else			change(k<<1,l,mid,L,L+(mid-l)),//待修改区间在mid前的一部分
					change(k<<1|1,mid+1,r,R-(r-mid-1),R);//待修改区间在mid后的一部分
}
int query(int k,int ind){
	if(s[k].l==s[k].r){
		if(!s[k].lz)	return b[ind];//如果lz为0，表示该节点从来没有被覆盖过，就返回b数组的当前位置
		else			return a[s[k].lz];//否则返回a数组的lz值
	}
	pushdown(k);
	int mid=(s[k].l+s[k].r)>>1;
	if(ind<=mid)	return query(k<<1,ind);//如果待查询的点在mid前
	else			return query(k<<1|1,ind);//如果待查询的点在mid后
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)	cin>>a[i];
	for(int i=1;i<=n;i++)	cin>>b[i];
	build(1,1,n);
	while(m--){
		int type;
		cin>>type;
		if(type==1){
			int x,y,k;cin>>x>>y>>k;
			change(1,y,y+k-1,x,x+k-1);//将a数组的[x,x+k-1]覆盖到b数组的[y,y+k-1]位置上
		}
		else{
			int i;cin>>i;
			cout<<query(1,i)<<endl;
		}
	}
}
```


---

## 作者：yuhan0204 (赞：1)

怎么没人写可持久化的。

### 题意：

在 $a$ 数组中把一段区间中的值复制到 $b$ 里面去。

单点查询 $b$ 数组。

### 思路：

看到题解区各位大佬的线段树维护方式，鄙人十分膜拜。

如果考试的时候想不到差分维护下标怎么办（比如我）？

那就使用高级数据结构。~~根本不用思考，只需要无脑打代码。~~

题目中出现了关键句：把一个数组里的值**区间覆盖**到另一个数组里。

所以考虑可持久化平衡树。

具体怎么做呢？

对 $a$ 数组维护一棵平衡树，在每次要给 $b$ 数组区间赋值时，把 $a$ 数组需复制的区间分裂出来。再把 $b$ 数组分裂好，将 $a$ 数组分裂出来的接到 $b$ 数组里即可。

这个过程可以使用可持久化平衡树完成。

但是过不了，空间炸了。

定期重构即可。

```cpp
#include<bits/stdc++.h>
#define maxm 10000005
#define maxn 200005
using namespace std;
int n,m,sum,fl,qwq=0,tott,tot,p=1,ans;
int rt1,rt2;
int a[maxn],b[maxn];
struct Fhq{
	int l,r;
	int key,rk,sz;
}t[maxm];
void Pushup(int k){
	t[k].sz=t[t[k].l].sz+t[t[k].r].sz+1;
} 
void Split(int k,int x,int &L,int &R){
	if(!k)L=R=0;
	else{
		int rt=++tot;
		t[rt]=t[k];
		if(t[t[rt].l].sz+1<=x){
			L=rt;
			Split(t[rt].r,x-t[t[rt].l].sz-1,t[rt].r,R);		
		}else{
			R=rt;
			Split(t[rt].l,x,L,t[rt].l);
		}Pushup(rt);
	}
}
int Merge(int x,int y){
	int rt=++tot;
	if(!x||!y){
		t[rt]=t[x+y];
		return rt;
	}
	if(t[x].rk>t[y].rk){
		t[rt]=t[x];
		t[rt].r=Merge(t[rt].r,y);
	}else{
		t[rt]=t[y];
		t[rt].l=Merge(x,t[rt].l);
	}Pushup(rt);
	return rt;
}
int Newnode(int x){
	t[++tot]=(Fhq){0,0,x,rand(),1};
	return tot;
}
void Insert(int x,int op){
	if(!op)rt1=Merge(rt1,Newnode(x));
	else rt2=Merge(rt2,Newnode(x));
}
void Print(int rt){
	if(t[rt].l)Print(t[rt].l);
	cout<<t[rt].key<<" ";
	if(t[rt].r)Print(t[rt].r) ;
} 
void Copy(int x,int y,int z){
	int a1,b1,c1;
	Split(rt1,x-1,a1,c1);
	Split(c1,z,b1,c1);
	int a2,b2,c2;
	Split(rt2,y-1,a2,c2);
	Split(c2,z,b2,c2);	
	rt2=Merge(Merge(a2,b1),c2);
	rt1=Merge(Merge(a1,b1),c1);
}
int Ask(int k,int x){
	while(k){
		int sum=t[t[k].l].sz+1;
		if(sum==x)return t[k].key;
		if(sum<x){
			x-=sum;
			k=t[k].r;
		}else k=t[k].l;
	}
}
void Cha(int rt,int op){
	if(t[rt].l)Cha(t[rt].l,op);
	if(!op)a[++qwq]=t[rt].key;
	else b[++qwq]=t[rt].key;
	if(t[rt].r)Cha(t[rt].r,op) ;
} 
void Rebuild(){
	if(tot<=7000000)return;
	qwq=0;
	Cha(rt1,0);
	rt1=0;
	
	qwq=0;
	Cha(rt2,1);
	rt2=0;
	
    tot=0;
	for(int i=1;i<=n;i++)Insert(a[i],0);
	for(int i=1;i<=n;i++)Insert(b[i],1);
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	srand(time(0));
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		int x;
		cin>>x;
		Insert(x,0);
	}tott=tot;
	for(int i=1;i<=n;i++){
		int x;
		cin>>x;
		Insert(x,1);
	}	
	while(m--){
		int op,x,y,z;
		cin>>op>>x;
		if(op==1){
			cin>>y>>z;
			Copy(x,y,z);
            Rebuild();
		}else cout<<Ask(rt2,x)<<"\n";
	}
	return 0;
}
```

高级数据结构的**其中一个意义**是让你不用思考过多。

---

## 作者：cosf (赞：1)

我们开一个线段树。存的不是值，而是下标差。

我们可以将 $a$ 和 $b$ 连起来，组成：

$$
c = \{a_1, a_2, \dots, a_n, b_1, b_2, \dots, b_n\}
$$

并且维护下标差 $d = \{d_1, d_2, \dots, d_n\}$ 使得我们询问 $b_i$ 时只需访问 $c_{i + d_i}$ 即可。

显然，默认 $d = \{\underbrace{n, n, \dots, n}_{\text{there are }n\text{ '}n\text{'s}}\}$，因为此时 $c_{i + d_i} = b_i$。

对于修改操作，我们把 $a_{x \dots (x + k)}$ 复制到 $b_{y \dots (y + k)}$ 就相当于让 $d_{y \dots (y + k)} \gets x - y$。这样在询问 $b_m (y \le m \le y + k)$ 的时候，$c_{m + d_m} = c_{m + x - y} =$ 对应 $a$ 中的元素。

```cpp
#include <iostream>
using namespace std;

#define MAXN 200005

int n, m;

int t[MAXN << 1];
int u[MAXN << 1];

int a[MAXN];

void pushdown(int p)
{
    if (u[p])
    {
        t[p << 1] = t[p << 1 | 1] = t[p];
        u[p << 1] = u[p << 1 | 1] = 1;
        u[p] = 0;
    }
}

void build(int p, int l, int r)
{
    if (l == r)
    {
        t[p] = n;
        return;
    }
    int mid = (l + r) >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
}

int query(int p, int l, int r, int q)
{
    if (l == r)
    {
        return t[p];
    }
    pushdown(p);
    int mid = (l + r) >> 1;
    if (mid >= q)
    {
        return query(p << 1, l, mid, q);
    }
    else
    {
        return query(p << 1 | 1, mid + 1, r, q);
    }
}

void set(int p, int l, int r, int ql, int qr, int v)
{
    if (ql <= l && r <= qr)
    {
        t[p] = v;
        u[p] = 1;
        return;
    }
    pushdown(p);
    int mid = (l + r) >> 1;
    if (mid >= ql)
    {
        set(p << 1, l, mid, ql, qr, v);
    }
    if (mid < qr)
    {
        set(p << 1 | 1, mid + 1, r, ql, qr, v);
    }
}

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= 2 * n; i++)
    {
        cin >> a[i];
    }
    build(1, 1, n);
    while (m--)
    {
        int o, x;
        cin >> o >> x;
        if (o == 1)
        {
            int y, k;
            cin >> y >> k;
            set(1, 1, n, y, y + k - 1, x - y);
        }
        else
        {
            cout << a[x + query(1, 1, n, x)] << endl;
        }
    }
    return 0;
}

```

---

## 作者：louhao088 (赞：1)

线段树

## 思路

首先我们可以用lazy来标记有无被覆盖

如果被覆盖了，我们可以记录覆盖那一段的左右下标，每次向下就$push$一下，询问时只需输出a[下标]或b[下标]即可

而更新时的位置只要用线段树建树时的$l,r$即可


```cpp
void change(int rt,int l,int r,int L,int R,int x)//更新
{
	
	if(l>R||r<L)return;
	if(l>=L&&r<=R)
	{
		tr[rt].l=x+(l-L);tr[rt].r=x+(r-L);
		tr[rt].lazy=1;return;
	}
	push(rt);int mid=l+r>>1;
	change(ls,l,mid,L,R,x),change(rs,mid+1,r,L,R,x);
}
int query(int rt,int l,int r,int x)//查询
{
	if(l>x||r<x)return 0;
	if(l==x&&r==x)
	{
		if(tr[rt].lazy==1)return a[tr[rt].l];
		else return b[l];
	}
	push(rt);int mid=l+r>>1;
	return query(ls,l,mid,x)+query(rs,mid+1,r,x);
}
```

简而言之，就是用线段树维护覆盖位置，用建树时的$l,r$来更新，每次$push$一下



```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
	char ch=getchar();bool f=0;int x=0;
	for(;!isdigit(ch);ch=getchar())if(ch=='-')f=1;
	for(;isdigit(ch);ch=getchar())x=(x<<1)+(x<<3)+(ch^48);
	if(f==1)x=-x;return x;
}
const int maxn=2e5+5;
#define ls rt<<1
#define rs rt<<1|1
struct node
{
	int l,r,lazy;
}tr[maxn*4];
int a[maxn],b[maxn],c[maxn],n,m,x,y,z,k;
void push(int rt)
{
	if(tr[rt].lazy==1)
	{
		tr[ls].lazy=1,tr[rs].lazy=1;
		tr[ls].r=tr[rt].l+(tr[ls].r-tr[ls].l),tr[ls].l=tr[rt].l;
		tr[rs].l=tr[ls].r+1;tr[rs].r=tr[rt].r;
	}tr[rt].lazy=0;
}
void build(int rt,int l,int r)
{
	tr[rt].l=l,tr[rt].r=r;tr[rt].lazy=0;
	if(l==r)return;
	int mid=l+r>>1;
	build(ls,l,mid),build(rs,mid+1,r);
}
void change(int rt,int l,int r,int L,int R,int x)
{
	
	if(l>R||r<L)return;
	if(l>=L&&r<=R)
	{
		tr[rt].l=x+(l-L);tr[rt].r=x+(r-L);
		tr[rt].lazy=1;return;
	}
	push(rt);int mid=l+r>>1;
	change(ls,l,mid,L,R,x),change(rs,mid+1,r,L,R,x);
}
int query(int rt,int l,int r,int x)
{
	if(l>x||r<x)return 0;
	if(l==x&&r==x)
	{
		if(tr[rt].lazy==1)return a[tr[rt].l];
		else return b[l];
	}
	push(rt);int mid=l+r>>1;
	return query(ls,l,mid,x)+query(rs,mid+1,r,x);
}
int main()
{
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)b[i]=read();
	build(1,1,n);
	for(int i=1;i<=m;i++)
	{
		k=read();
		if(k==1)x=read(),y=read(),z=read(),change(1,1,n,y,y+z-1,x);
		else x=read(),printf("%d\n",query(1,1,n,x));
	}
	return 0;
}
```




---

## 作者：DennyQi (赞：1)

如果我们知道某一个位置最后一次是被哪一次操作覆盖的，那么就可以知道这个位置对应的值。

由此问题转化为求解某一个位置最后一次被哪个操作覆盖。这显然是一个区间赋值（染色）问题。利用线段树就可以维护好——我们每一次将一个对应区间set成操作编号，每一次询问只需要找出对应叶节点的编号就知道是哪一次操作（特殊的，0意味着没有操作）。

```cpp
/*DennyQi 2019*/
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
inline int read(){
    int x(0),w(1); char c = getchar();
    while(c^'-' && (c<'0'||c>'9')) c = getchar();
    if(c == '-') w = -1, c = getchar();
    while(c>='0' && c<='9') x = (x<<3) + (x<<1) + c - '0', c = getchar();
    return x*w;
}
int n,m,opt,p,x,Q,a[100010],b[100010],qx[100010],qy[100010],qz[100010],c[400010],set[400010];
inline void pushdown(int u, int l, int r){
	if(!set[u]) return;
	c[u<<1] = set[u];
	c[u<<1|1] = set[u];
	set[u<<1] = set[u];
	set[u<<1|1] = set[u];
	set[u] = 0;
}
int query(int u, int l, int r, int x){
	if(l == r){
		return c[u];
	}
	pushdown(u,l,r);
	int mid = (l+r)/2;
	if(x <= mid) return query(u<<1,l,mid,x);
	else return query(u<<1|1,mid+1,r,x);
}
void modify(int u, int l, int r, int x, int y, int k){
	if(r<x || l>y) return;
	if(x<=l && r<=y){
		set[u] = k;
		c[u] = k;
		return;
	}
	pushdown(u,l,r);
	int mid = (l+r)/2;
	modify(u<<1,l,mid,x,y,k);
	modify(u<<1|1,mid+1,r,x,y,k);
}
int main(){
//	freopen(".in","r",stdin);
	n = read(), m = read();
	for(int i = 1; i <= n; ++i) a[i] = read();
	for(int i = 1; i <= n; ++i) b[i] = read();
	for(int i = 1; i <= m; ++i){
		opt = read();
		if(opt == 1){
			++Q;
			qx[Q] = read(), qy[Q] = read(), qz[Q] = read();
			modify(1,1,n,qy[Q],qy[Q]+qz[Q]-1,Q);
		}else{
			x = read();
			p = query(1,1,n,x);
			if(!p){
				printf("%d\n",b[x]);
			}
			else{
				printf("%d\n",a[qx[p]+x-qy[p]]);	
			}
		}
	}
	return 0;
}
```


---

## 作者：DDF_ (赞：0)

## 题面

给两个长度为 $n$ 的数列 $a$，$b$。

有两种操作：

- 区间覆盖。将 $b$ 中一段以 $y$ 开头，长度为 $k$ 的区间覆盖为 $a$ 中一段以 $x$ 开头，长度为 $k$ 的区间。
- 单点查询。求 $b_{x}$ 的值。

对于每次第二种操作，输出所求得答案。

## 思路

对于一段区间，它的值是难以维护的。因为这段区间中的值没有规律，只能从 $y$ 到 $y+k-1$ 依次赋值，时间复杂度为 $O(n^{2})$，显然过不了。

然而，下标是有规律可循的，一段连续区间中，下标是一个等差数列。

因为数列 $a$ 不会被数列 $b$ 覆盖，所以可以想到维护数列 $b$ 中下标对应的数列 $a$ 中下标。

设 $f_{i}$ 为数列 $b$ 中下标对应的 $a$ 中下标。

对于每一次第一种操作，就是将 $f$ 中以 $x$ 开头的序列赋值为一段首项为 $y$，公差为 $1$ 的等差数列。

因为赋的值是一个等差数列，是有规律的，所以可以用线段树维护。

于是就想，用线段树维护一段区间左端点 $l$ 的 $f_{l}$。

第一种操作中，如果区间 $[l,r]$ 完全被包含在区间 $[x,x+k-1]$ 中，那么显然这段区间的维护的值 $V_{k}$ 为 $y+(l-x)$。

由于是区间赋值，所以一定有懒标记，考虑懒标记的下传。

可以发现，一段区间，左儿子维护的值和它相同，因为它们拥有相同的左端点。

因为右儿子左端点为 $mid+1$，又因为维护的是一段等差数列，所以右儿子维护的值为 $V_{k}+mid+1-l$。

可以发现下传的值就是维护的值。

第二种操作就是单点查询，如果线段树中有维护的值，就输出 $a$ 中的值，反之输出 $b$ 中的值。

时间复杂度 $O(m \log(n))$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+2;
int n,m;
int a[N],b[N];
struct segment {
	int l,r;
	int v;
	bool t;
} s[N*4];
void pushdown(int k) {
	int l=s[k].l,r=s[k].r,mid=(l+r)/2;
	s[k*2].v=s[k].v,s[k*2+1].v=s[k].v+(mid+1-l);
	s[k*2].t=s[k*2+1].t=1,s[k].t=0;
	return;
}
void build(int l,int r,int k) {
	s[k].l=l,s[k].r=r;
	if(l==r) return;
	int mid=(l+r)/2;
	build(l,mid,k*2);
	build(mid+1,r,k*2+1);
	return;
}
void update(int L,int R,int st,int ed,int k) {
	int l=s[k].l,r=s[k].r;
	if(l>=L&&r<=R) {s[k].v=st+l-L,s[k].t=1;return;}
	int mid=(l+r)/2;
	if(s[k].t) pushdown(k);
	if(mid>=L) update(L,R,st,ed,k*2);
	if(mid<R) update(L,R,st,ed,k*2+1);
	return;
} //区间赋值
int getans(int x,int k) {
	int l=s[k].l,r=s[k].r;
	if(l==r) return (s[k].v)?a[s[k].v]:b[x];
	if(s[k].t) pushdown(k);
	int mid=(l+r)/2;
	if(mid>=x) return getans(x,k*2);
	if(mid<x) return getans(x,k*2+1);
} //单点查询
int main() {
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<=n;i++) scanf("%d",&b[i]);
	build(1,n,1);
	while(m--) {
		int op,x,y,k;
		scanf("%d%d",&op,&x);
		if(op==1) {
			scanf("%d%d",&y,&k);
			update(y,y+k-1,x,x+k-1,1);
		}
		if(op==2) printf("%d\n",getans(x,1));
	}
	return 0;
}
```

---

## 作者：WorldMachine (赞：0)

考虑维护 $b_i$ 对应的 $\{a\}$ 中坐标，发现其实就是区间赋值成等差数列，这是一个很板的东西，考虑使用线段树维护。

当然还要记录一下每个 $b_i$ 是否被修改过，如果没有就是它原本的值。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 100005;
int n, m, a[N], b[N], op, x, y, k, orz;
namespace Segtree {
	int c[N * 4];
	bool v[N * 4];
	void update(int p, int l, int r, int s, int e, int d) {
		if (s <= l && r <= e) return v[p] = 1, c[p] = d + l - s, void();
		int mid = l + r >> 1;
		if (c[p]) {
			c[p * 2] = c[p], c[p * 2 + 1] = c[p] + mid - l + 1;
			c[p] = 0;
		}
		if (v[p]) {
			v[p * 2] = v[p * 2 + 1] = 1;
			v[p] = 0;
		}
		if (s <= mid) update(p * 2, l, mid, s, e, d);
		if (e > mid) update(p * 2 + 1, mid + 1, r, s, e, d);
	}
	int query(int p, int l, int r, int x) {
		if (l == r) return v[p] ? c[p] : 0;
		int mid = l + r >> 1;
		if (c[p]) {
			c[p * 2] = c[p], c[p * 2 + 1] = c[p] + mid - l + 1;
			c[p] = 0;
		}
		if (v[p]) {
			v[p * 2] = v[p * 2 + 1] = 1;
			v[p] = 0;
		}
		if (x <= mid) return query(p * 2, l, mid, x);
		return query(p * 2 + 1, mid + 1, r, x);
	}
}
using namespace Segtree;
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for (int i = 1; i <= n; i++) scanf("%d", &b[i]);
	while (m--) {
		scanf("%d%d", &op, &x);
		if (op == 1) {
			scanf("%d%d", &y, &k);
			update(1, 1, n, y, y + k - 1, x);
		} else {
			orz = query(1, 1, n, x);
			printf("%d\n", orz ? a[orz] : b[x]);
		}
	}
}
```

---

## 作者：SpringFullGarden (赞：0)

## 题意

给定序列 $a$ 和序列 $b$，长度均为 $n$。有 $m$ 次操作：

1. `1 x y k`：$b _ {y + i} \gets a_{x + i}(0 \le i < k)$。
2. `2 x`：输出 $b_x$。

## 思路

修改：线段树维护区间上一次修改的的 $x, y$（$x, y$ 同修改中的 $x, y$，即代码中 $aa, bb$）。

查询：若未修改（即 $aa = 0$）输出 $b_l$，否则输出 $a_{x + l - y}$（即代码中的 $a_{aa - l - bb}$）。

## 代码

```cpp
struct node {
	int l, r, aa, bb;
} tr[400005];
int a[100005], b[100005];

void dn(ll x) {
	if(tr[x].aa) tr[x << 1].aa = tr[x << 1 | 1].aa = tr[x].aa;
	if(tr[x].bb) tr[x << 1].bb = tr[x << 1 | 1].bb = tr[x].bb;
	tr[x].aa = tr[x].bb = 0;
}
void bd(ll x, ll l, ll r) {
	tr[x].l = l, tr[x].r = r;
	if(l == r) { tr[x].aa = 0, tr[x].bb = l; return; }
	ll mid = (l + r) >> 1;
	bd(x << 1, l, mid), bd(x << 1 | 1, mid + 1, r);
	return;
}
void cg(ll x, ll l, ll r, ll aaa, ll bbb) {
	if(tr[x].l > r || tr[x].r < l) return;
	if(tr[x].l >= l && tr[x].r <= r) {
		tr[x].aa = aaa;
		tr[x].bb = bbb;
		return;
	}
	dn(x);
	cg(x << 1, l, r, aaa, bbb), cg(x << 1 | 1, l, r, aaa, bbb);
	return;
}
ll fd(ll x, ll l, ll r) {
	if(tr[x].l > r || tr[x].r < l) return 0;
	if(tr[x].l == tr[x].r) {
		if(tr[x].aa) return a[tr[x].aa + tr[x].l - tr[x].bb];
		else return b[tr[x].l];
	}
	dn(x);
	return fd(x << 1, l, r) + fd(x << 1 | 1, l, r);
}
signed main() {
	int n = rd(), m = rd();
	for(int i = 1; i <= n; i++) a[i] = rd();
	for(int i = 1; i <= n; i++) b[i] = rd();
	bd(1, 1, n);
	for(int i = 1; i <= m; i++) {
		int opt = rd();
		if(opt == 1) {
			int x = rd(), y = rd(), k = rd();
			cg(1, y, y + k - 1, x, y);
		}
		else {
			int x = rd();
			cout << fd(1, x, x) << '\n';
		}
	}
    return 0;
}
```

---

## 作者：Network_Flow (赞：0)

## CF292E 题解

提供一个比较简单的做法。

对于每一次覆盖，不用线段树直接去存两端点 $[l,r]$，可以存下来这次修改对应第几次覆盖（未被覆盖为 $0$），查找时再根据存储的次数去输出。

最后输出时如果未被覆盖，直接输出 $b[i]$，如果有覆盖次数 $num$，则对应数组 $A$ 的下标为：($X$，$Y$ 为对应 $A$ 和 $B$ 该次覆盖的下标)

$$(i-x[num]+1)+y[num]-1=i-x[num]+y[num]$$

时间复杂度 $O(m\log{n})$，可以通过本题。

```cpp
#include <iostream>
#include <cstdio>
#define SIZE 131072
#define ll long long

using namespace std;
int x[100005], y[100005], w[SIZE*2+5], tag[SIZE*2+5], cnt, n, m, a[100005], b[100005];
//线段树
void build(ll p, ll l, ll r){
	tag[p]=0;
	if(l==r){
		w[p]=0;
		return;
	}
	int mid=(l+r)>>1;
	build(p*2, l, mid);
	build(p*2+1, mid+1, r);
	w[p]=w[p*2]+w[p*2+1];
}
void f(ll p, ll l, ll r, ll k){
//下推的时候注意，如果k=0(没有)就不要往下放，要不然会覆盖掉原有的标记（被卡了好久）
	if(k!=0) tag[p]=k;
	if(k!=0) w[p]=(r-l+1)*k;
}
void update(ll p, ll nl, ll nr, ll l, ll r, ll k){
	if(nl<=l&&nr>=r){
		tag[p]=k;
		w[p]=(r-l+1)*k;
		return;
	}
	ll mid=(l+r)>>1;
	f(p*2, l, mid, tag[p]);
	f(p*2+1, mid+1, r, tag[p]);
	tag[p]=0;
	if(nl<=mid) update(p*2, nl, nr, l, mid, k);
	if(nr>mid) update(p*2+1, nl, nr, mid+1, r, k);
	w[p]=w[p*2]+w[p*2+1];
}
ll query(ll p, ll nl, ll nr, ll l, ll r){
	ll res=0;
	if(nl<=l&&nr>=r) return w[p];
	//下放到下面一层
	ll mid=(l+r)>>1;
	f(2*p, l, mid, tag[p]);
	f(2*p+1, mid+1, r, tag[p]);
	tag[p]=0;
	if(nl<=mid) res+=query(2*p, nl, nr, l, mid);
	if(nr>mid) res+=query(2*p+1, nl, nr, mid+1, r);
	return res;
}
int main(){
    scanf("%d%d", &n, &m);
    for (int i=1; i<=n; i++) scanf("%d", &b[i]);
    for (int i=1; i<=n; i++) scanf("%d", &a[i]);
    build(1, 1, n);
    while (m--){
        long long cmd;
        scanf("%lld", &cmd);
        if(cmd==1){
        	ll z;++cnt;
        	scanf("%d%d%lld", &y[cnt], &x[cnt], &z);
           	//更新时范围是从起点到起点+z-1（输入时数组写反了）
			update(1, x[cnt], x[cnt]+z-1, 1, n, cnt); 
		}
		else{
			int u;scanf("%d", &u);
			ll num=query(1, u, u, 1, n);
        		//分情况输出
			if(num) printf("%d\n", b[u-x[num]+y[num]]);
			else printf("%d\n", a[u]);
		}
    }
    return 0;//完结撒花
}
```

---

## 作者：Eric_jx (赞：0)

## 解题思路

用线段树维护一个一开始全为 $0$ 的数列，每次修改操作先记录下来，把这次修改操作所影响到位置对应的区间修改为这次操作的序数。

查询的时候，查询最后影响到这个数字的操作是哪一个，找到那次操作的具体内容，对比一下就可以得到答案了。

## AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int x[1000001],y[1000001],z[1000001],a[1000001],b[1000001];
struct stu{
	int l,r,lazy=0;
}t[1000001];
void build(int p,int l,int r){
	if(l==r){
		t[p].l=l,t[p].r=r;
		return; 
	}
	t[p].l=l;t[p].r=r;
	int mid=(l+r)/2;
	build(p*2,l,mid);
	build(p*2+1,mid+1,r);
}
void change(int p,int x,int y,int k){
	int l=t[p].l,r=t[p].r;
	if(l>=x&&r<=y){
		t[p].lazy=k;
		return ;
	}
	if(l==r){
		return;
	}
	if(t[p].lazy!=0){
		t[p*2].lazy=t[p].lazy;
		t[p*2+1].lazy=t[p].lazy;
		t[p].lazy=0;
	}
	int mid=(l+r)/2;
	if(mid>=x){
		change(p*2,x,y,k);
	}
	if(mid<y){
		change(p*2+1,x,y,k);
	}
}
int ask(int p,int x){
	int l=t[p].l,r=t[p].r;
	if(l==r){
		return t[p].lazy;
	}
	if(t[p].lazy!=0){
		t[p*2].lazy=t[p].lazy;
		t[p*2+1].lazy=t[p].lazy;
		t[p].lazy=0;
	}
	int mid=(l+r)/2;
	if(mid>=x){
		return ask(p*2,x);
	}
	else{
		return ask(p*2+1,x);
	}
}
int main(){
	int n,m;
	cin>>n>>m;
	build(1,1,n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
	}
	for(int i=1;i<=n;i++){
		scanf("%d",&b[i]);
	}
	int cnt=0;
	for(int i=1;i<=m;i++){
		int op;
		cin>>op;
		if(op==1){
			cin>>x[i]>>y[i]>>z[i];
			change(1,y[i],y[i]+z[i]-1,i);
		}
		else{
			int xx;
			cin>>xx;
			int d=ask(1,xx);
			if(d<=0){
				cout<<b[xx]<<"\n";
			}
			else{
				cout<<a[x[d]+xx-y[d]]<<"\n";
			}
		} 
	}
	return 0;
}
```



---

## 作者：Wf_yjqd (赞：0)

如此板子的数据结构题，且 $n\le10^5$，怎么没有人写分块啊。。

------------

考虑每个块维护 $lazy$ 数组。

单块修改先拆 $lazy$ 标记，传到每个位置，然后暴力遍历改。

整块用 $lazy$ 数组记录块的左端点对应 $a$ 的位置。

查询时，判断是否有 $lazy$ 标记。有就通过 $lazy$ 求对应位置，否则直接输出。

复杂度 $\operatorname{O}(m\times \sqrt{n})$。

------------

不会求对应位置的可以看代码啊。

毫不卡常进第一页。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+84;
const int maxsq=384;
int n,m,op,x,y,k,DatA[maxn],bu[maxn];
struct Block{
    int SizE,CnT,L[maxsq],R[maxsq],LazY[maxsq],Mp[maxn];
    void IniT(){
        SizE=sqrt(n+1);
        CnT=(n-1)/SizE+1;
        for(int i=1;i<=CnT;i++){
            L[i]=R[i-1]+1;
            R[i]=R[i-1]+SizE;
            if(i==CnT)
                R[i]=n;
            for(int j=L[i];j<=R[i];j++){
                DatA[j]=read();
                Mp[j]=i;
            }
        }
        return ;
    }
    inline void modify(int l,int bl,int k){
        if(Mp[l]==Mp[l+k]){
            if(LazY[Mp[l]]){
                for(int i=L[Mp[l]];i<=R[Mp[l]];i++)
                    DatA[i]=bu[LazY[Mp[l]]+i-L[Mp[l]]];
                LazY[Mp[l]]=0;
            }
            for(int i=l;i<=l+k;i++)
                DatA[i]=bu[i-l+bl];
            return ;
        }
        if(LazY[Mp[l]]){
            for(int i=L[Mp[l]];i<=R[Mp[l]];i++)
                DatA[i]=bu[LazY[Mp[l]]+i-L[Mp[l]]];
            LazY[Mp[l]]=0;
        }
        for(int i=l;i<=R[Mp[l]];i++)
            DatA[i]=bu[i-l+bl];
        if(LazY[Mp[l+k]]){
            for(int i=L[Mp[l+k]];i<=R[Mp[l+k]];i++)
                DatA[i]=bu[LazY[Mp[l+k]]+i-L[Mp[l+k]]];
            LazY[Mp[l+k]]=0;
        }
        for(int i=L[Mp[l+k]];i<=l+k;i++)
            DatA[i]=bu[i-l+bl];
        for(int i=Mp[l]+1;i<=Mp[l+k]-1;i++)
            LazY[i]=L[i]-l+bl;
        return ;
    }
    inline int query(int x){
        return LazY[Mp[x]]?bu[LazY[Mp[x]]+x-L[Mp[x]]]:DatA[x];
    }
}Sherry;
int main(){
    n=read();
    m=read();
    for(int i=1;i<=n;i++)
        bu[i]=read();
    Sherry.IniT();
    while(m--){
        op=read();
        x=read();
        if(op==2){
            write(Sherry.query(x));
            putchar('\n');
            continue;
        }
        y=read();
        k=read();
        Sherry.modify(y,x,k-1);
        for(int i=1;i<=n;i++){
            write(DatA[i]);
            putchar(' ');
            write(Sherry.LazY[Sherry.Mp[i]]);
            puts("\nSherry");
        }
    }
    return 0;
}
```


---

## 作者：forgotmyhandle (赞：0)

[你谷传送门](https://www.luogu.com.cn/problem/CF292E)

[原题传送门](http://codeforces.com/problemset/problem/292/E)

## 分析
一眼可以看出，这题实际上是让你维护区间覆盖、单点查询操作。于是考虑线段树。

进一步观察可以发现，一次覆盖操作实际上是把 $a_x$ 及其后的 $k-1$ 个元素赋给 $b_y$ 及其后的 $k-1$ 个元素。我们画个图来理解一下：

![样例，但是不完全样例](https://cdn.luogu.com.cn/upload/image_hosting/c0it0c2m.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

也就是 $b$ 数组里的每一个 $b_y$ 在一次操作后都会变成 $a$ 数组里的一个 $a_{y+\Delta}$。这个 $\Delta$ 其实就是这次操作的 $x - y$。可以发现 $\Delta$ 其实是 $b$ 里某段区间的一个属性，代表这个区间里的每个 $b_x$ 都即将被改成 $a_{x+\Delta}$。所以这玩意显然是可以用线段树维护的。把 $\Delta$ 作为懒标记，每次将 $\Delta$ 下传。查询时查到叶子就直接返回 $a$ 里的对应值。

由于 $x$ 和 $y$ 可以相等，所以 $\Delta$ 可以是 $0$。所以我们就不能用 $0$ 标记区间没有被覆盖过，而要用无穷大来标记。

## 代码
```cpp
#include <iostream>
using namespace std;
const int N = 131072;
const int inf = 2147483647;
int a[N << 2], b[N << 2];
int tag[N << 2];
void Build(int o, int l, int r) {
    tag[o] = -inf; // 初始化懒标记：这里没有被覆盖过
    if (l == r) 
        return;
    int mid = (l + r) >> 1;
    Build(o << 1, l, mid);
    Build(o << 1 | 1, mid + 1, r);
}
void pushdown(int o) {
    if (tag[o] == -inf) 
        return;
    int t = tag[o];
    tag[o] = -inf;
    tag[o << 1] = tag[o << 1 | 1] = t; // 左右儿子都要移 △ 位
}
void Change(int o, int l, int r, int L, int R, int d) {
    if (L <= l && r <= R) {
        tag[o] = d; // 赋为 △
        return;
    }
    pushdown(o);
    int mid = (l + r) >> 1;
    if (L <= mid) 
        Change(o << 1, l, mid, L, R, d);
    if (R > mid) 
        Change(o << 1 | 1, mid + 1, r, L, R, d);
}
int Query(int o, int l, int r, int x) {
    if (l == r) 
        return (tag[o] == -inf ? b[x] : a[x + tag[o]]);
        // 如果没有被覆盖过，则返回原本值。如果被覆盖过，返回 a 里的对应值。
    pushdown(o);
    int mid = (l + r) >> 1;
    if (x <= mid) 
        return Query(o << 1, l, mid, x);
    else 
        return Query(o << 1 | 1, mid + 1, r, x);
}
int main() {
    Build(1, 1, N);
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    for (int i = 1; i <= n; i++) scanf("%d", b + i);
    while (m--) {
        int op, x, y, k;
        cin >> op;
        if (op == 1) {
            cin >> x >> y >> k;
            Change(1, 1, N, y, y + k - 1, x - y); // △ = x - y
        } else {
            cin >> x;
            cout << Query(1, 1, N, x) << "\n";
        }
    }
    return 0;
}
```
### 完结撒花~~~

---

## 作者：Setsugesuka (赞：0)

这里提供一种简单的做法

每次用 $a$ 中的一段区间覆盖 $b$ 中的一段区间，动态查询 $b$ 中某个节点的值是多少。

事实上，我们只需要维护 $b$ 中的每个位置最后一次被覆盖的操作是哪个就可以了。

我们记每个操作为 $l,r,k$ ，那么如果我们查询的那个节点它的最后一次覆盖操作是 $i$ ，那么它的值显然就是 $a[q[i].l+(pos-q[i].r)]$ 这里的 $pos$ 指这个节点在 $b$ 中的下标。

特别的，当它没有被覆盖时，只需要输出原来 $b$ 数组的值即可。

于是问题就转化为了区间赋值，单点查询。

$ODT$ 可以高效地解决这类问题。

```cpp
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#include<bits/stdc++.h>
using namespace std;

template <class T>
inline void write(T x)
{
    if(x>9)
    {
        write(x/10);
    }
    putchar(x%10+'0');
}

inline char nc()
{
    static char buf[1000000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++;
}

inline void read(int &sum)
{
    char ch=nc();
    int tf=0;
    sum=0;
    while((ch<'0'||ch>'9')&&(ch!='-')) ch=nc();
    tf=((ch=='-')&&(ch=nc()));
    while(ch>='0'&&ch<='9') sum=sum*10+(ch-48),ch=nc();
    (tf)&&(sum=-sum);
}

const int MAXN=1e5+10;

struct node
{
    int l,r,v;
    node(){}
    node(int L,int R=-1,int V=0):l(L),r(R),v(V){}
    bool operator <(const node &o) const
    {
        return l<o.l;
    }
};

set<node> s;

inline set<node>::iterator split(int pos)
{
    set<node>::iterator it=s.lower_bound(node(pos));
    if(it!=s.end()&&it->l==pos) return it;
    --it;
    int L=it->l,R=it->r,V=it->v;
    s.erase(it);
    s.insert(node(L,pos-1,V));
    return s.insert(node(pos,R,V)).first;
}

inline void assignval(int l,int r,int v)
{
    set<node>::iterator itr=split(r+1),itl=split(l);
    s.erase(itl,itr);
    s.insert(node(l,r,v));
}

struct qnode
{
    int l,r,k;
};

qnode q[MAXN];
int a[MAXN],b[MAXN];
int n,m,cnt=0;

int main()
{
    read(n),read(m);
    for(int i=1;i<=n;++i)
        read(a[i]);
    for(int i=1;i<=n;++i)
        read(b[i]);
    s.insert(node(1,n,0));
    while(m--)
    {
        int op;
        read(op);
        if(op==1)
        {
            ++cnt;
            read(q[cnt].l),read(q[cnt].r),read(q[cnt].k);
            assignval(q[cnt].r,q[cnt].r+q[cnt].k-1,cnt);
        }
        else
        {
            int pos;
            read(pos);
            int which=split(pos)->v;
            if(which==0)
            {
                int ans=b[pos];
                if(ans<0)
                {
                    putchar('-');
                    ans=-ans;
                }
                write(ans);
                putchar('\n');
            }
            else
            {
                int ans=a[q[which].l+(pos-q[which].r)];
                if(ans<0)
                {
                    putchar('-');
                    ans=-ans;
                }
                write(ans);
                putchar('\n');
            }
        }
    }
    return 0;
}
```


---

