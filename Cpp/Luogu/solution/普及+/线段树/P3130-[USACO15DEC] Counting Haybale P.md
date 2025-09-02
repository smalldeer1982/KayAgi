# [USACO15DEC] Counting Haybale P

## 题目描述

Farmer John 正在尝试雇佣承包商来帮助他重新安排农场，但到目前为止，所有承包商在看到 FJ 希望他们遵循的复杂指令序列后都辞职了。FJ 不得不自己完成这个项目，他意识到自己可能把项目搞得比必要的还要复杂。请帮助他按照指令完成农场的升级。

FJ 的农场由一排 $N$ 个田地组成，编号为 $1 \ldots N$。每个田地里可以有任意数量的干草堆。Farmer John 的指令包含三种类型的条目：

1) 给定一个连续的田地区间，向每个田地添加一个新的干草堆。

2) 给定一个连续的田地区间，确定该区间内田地中干草堆的最小数量。

3) 给定一个连续的田地区间，计算该区间内干草堆的总数。

## 样例 #1

### 输入

```
4 5
3 1 2 4
M 3 4
S 1 3
P 2 3 1
M 3 4
S 1 3```

### 输出

```
2
6
3
8```

# 题解

## 作者：pipiispig (赞：10)

##
线段树(ｷ｀ﾟДﾟ´)!!

维护两个值,sum,min;
然后还有懒标记；
是不是很简单；

不会线段树的可以去做模板题，虽然我觉得这个也是个模板QwQ;
```
#include<iostream>
#include<cstdio>
#include<cmath>
#include<queue>
#include<cstring>
#include<algorithm>
#define int long long
using namespace std;
const int N=400000;
int n,m,a[N];
char c;
struct tree
{
    int l;
    int r;
    int min;
    int sum;
    int add;
}t[N<<2];//四倍！！！
void pushup(int p)
{
    t[p].sum=t[p<<1].sum+t[p<<1|1].sum;
    t[p].min=min(t[p<<1].min,t[p<<1|1].min);
}//个人比较喜欢写函数，方便好调试；（向上传）
void pushdown(int p)
{
	if(!t[p].add)return;
    t[p<<1|1].add+=t[p].add; 
	t[p<<1].add+=t[p].add;	
	t[p<<1].min+=t[p].add;
	t[p<<1|1].min+=t[p].add;
	t[p<<1|1].sum+=(t[p<<1|1].r-t[p<<1|1].l+1)*t[p].add;
	t[p<<1].sum+=(t[p<<1].r-t[p<<1].l+1)*t[p].add;
	t[p].add=0;//不要忘了清零QwQ
}//对于懒标记的处理（向下传）
void build(int p,int l,int r)
{
    t[p].l=l,t[p].r=r;
    if(l==r){t[p].min=t[p].sum=a[l];return;}
    int mid=l+r>>1;
    build(p<<1,l,mid);build(p<<1|1,mid+1,r);
    pushup(p);//别忘了传递，这里用手写函数的话是不是很好看，线段树多可爱呀！
}//建树没什么说的吧QwQ
void change(int p,int l,int r,int z)
{
    if(l<=t[p].l&&r>=t[p].r){t[p].add+=z,t[p].min+=z,t[p].sum+=(t[p].r-t[p].l+1)*z;return;}
    pushdown(p);
    int mid=t[p].l+t[p].r>>1;
    if(l<=mid)change(p<<1,l,r,z);
    if(r>mid)change(p<<1|1,l,r,z);
    pushup(p);//传递
}
int querysum(int p,int l,int r)
{
    if(l<=t[p].l&&r>=t[p].r)return t[p].sum;
    pushdown(p);//懒标记要向下传递信息；
    int mid=t[p].l+t[p].r>>1;
    int ans=0;
    if(l<=mid)ans+=querysum(p<<1,l,r);
    if(r>mid)ans+=querysum(p<<1|1,l,r);
    return ans;
}
int querymin(int p,int l,int r)
{
    if(l<=t[p].l&&r>=t[p].r)return t[p].min;
    pushdown(p);
    int mid=t[p].l+t[p].r>>1;
    int ans=0x7f7f7f7f;
    if(l<=mid)ans=querymin(p<<1,l,r);
    if(r>mid)ans=min(ans,querymin(p<<1|1,l,r));
    return ans;
}//这个和sum没什么区别吧，嘻嘻
signed main()
{
    scanf("%lld%lld",&n,&m);
    for(int i=1;i<=n;i++)
    {
        scanf("%lld",&a[i]);
    }
    build(1,1,n);
    for(int i=1;i<=m;i++)
    {
        cin>>c;
        if(c=='P')
        {
            int l,r,z;
            scanf("%lld%lld%lld",&l,&r,&z);
            change(1,l,r,z);
        }
        if(c=='M')
        {
            int l,r;
            scanf("%lld%lld",&l,&r);
            printf("%lld\n",querymin(1,l,r));
        }
        if(c=='S')
        {
            int l,r;
            scanf("%lld%lld",&l,&r);
            printf("%lld\n",querysum(1,l,r));
        }
    }
    return 0;
}
```
总结：线段树是个妹子，她很可爱

---

## 作者：流逝丶 (赞：4)

## 线段树

这题标签错了吧。明明是线段树裸题啊

维护区间和，区间最小值，区间加修改，基本操作嘛，注意开longlong

一遍过，直接上代码吧。。

```cpp
#include<iostream>
#include<cstdio>
#define lson k<<1,l,mid
#define rson k<<1|1,mid+1,r
#define ls k<<1
#define rs k<<1|1
#define mid ((l+r)>>1)
#define LL long long
using namespace std;
const int N=200005;
int n,q;
LL tr[N<<2],laz[N<<2],mi[N<<2];
inline int read(){
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){s=s*10+ch-'0';ch=getchar();}
	return w*s;
}
inline void update(int k){
	tr[k]=tr[ls]+tr[rs];
	mi[k]=min(mi[ls],mi[rs]);
}
inline void down(int k,int l,int r){
	laz[ls]+=laz[k];laz[rs]+=laz[k];
	tr[ls]+=laz[k]*(mid-l+1);mi[ls]+=laz[k];
	tr[rs]+=laz[k]*(r-mid);mi[rs]+=laz[k];
	laz[k]=0;
}
void build(int k,int l,int r){
	if(l==r){
		tr[k]=mi[k]=read();
		return ;
	}
	build(lson);build(rson);
	update(k);
}
void change(int k,int l,int r,int x,int y,int z){
	if(l==x&&y==r){
		tr[k]+=(LL)z*(r-l+1);
		mi[k]+=z;
		laz[k]+=z;
		return ;
	}
	if(laz[k])down(k,l,r);
	if(y<=mid)change(lson,x,y,z);
	else if(x>mid)change(rson,x,y,z);
	else change(lson,x,mid,z),change(rson,mid+1,y,z);
	update(k);
}
LL ask(int k,int l,int r,int x,int y){
	if(l==x&&y==r){
		return tr[k];
	}
	if(laz[k])down(k,l,r);
	if(y<=mid)return ask(lson,x,y);
	else if(x>mid)return ask(rson,x,y);
	else return ask(lson,x,mid)+ask(rson,mid+1,y);
}
LL query(int k,int l,int r,int x,int y){
	if(l==x&&y==r){
		return mi[k];
	}
	if(laz[k])down(k,l,r);
	if(y<=mid)return query(lson,x,y);
	else if(x>mid)return query(rson,x,y);
	else return min(query(lson,x,mid),query(rson,mid+1,y));
}
int main(){
	n=read();q=read();
	build(1,1,n);
	char ch[5];
	int x,y,z;
	while(q--){
		scanf("%s",ch+1);
		x=read();y=read();
		if(ch[1]=='P'){z=read();change(1,1,n,x,y,z);}
		else if(ch[1]=='M'){printf("%lld\n",query(1,1,n,x,y));}
		else if(ch[1]=='S'){printf("%lld\n",ask(1,1,n,x,y));}
	}
	return 0;
}

```


---

## 作者：K2sen (赞：2)

## P3130
### 思路
线段树爆改，真不懂为什么标签里有并查集和离散化

注意别忘记开long long
#### 修改
修改区间和的时候，别忘了要把最小值也要加上。
```cpp
void update(int rt, int c, int l, int r, int L, int R) {
	if (L <= l && r <= R) {
		tree[rt].sum += tree[rt].len * c;
		tree[rt].min += c;
		tree[rt].lazy += c;
		return;
	}
	push_down(rt);
	int mid = (l + r) >> 1;
	if (L <= mid) update(lson, c, l, mid, L, R);
	if (R > mid) update(rson, c, mid + 1, r, L, R);
	push_up(rt);
}
```
然后就是常规的区间和和区间最小值，最小值别忘了取个极大值
#### 求区间和
```cpp
int query_sum(int rt, int l, int r, int L, int R) {
	if (L <= l && r <= R) return tree[rt].sum;
	push_down(rt);
	int mid = (l + r) >> 1, ans = 0;
	if (L <= mid) ans += query_sum(lson, l, mid, L, R);
	if (R > mid) ans += query_sum(rson, mid + 1, r, L, R);
	return ans;
}
```

#### 求区间最小值
```cpp
int query_min(int rt, int l, int r, int L, int R) {
	if (L <= l && r <= R) return tree[rt].min;
	push_down(rt);
	int mid = (l + r) >> 1, ans = 2147483647;
	if (L <= mid) ans = min(ans, query_min(lson, l, mid, L, R));
	if (R > mid) ans = min(ans, query_min(rson, mid + 1, r, L, R));
	return ans;
}

```

### code
```cpp
#include <bits/stdc++.h>
#define int long long
#define N 200010
#define M 1010
#define lson rt << 1
#define rson rt << 1 | 1

using namespace std;
struct node {
	int min, sum, lazy, len;
}tree[N << 2];
int n, m;

int read() {
	int s = 0, f = 0; char ch = getchar();
	while (!isdigit(ch)) f |= (ch == '-'), ch = getchar();
	while (isdigit(ch)) s = s * 10 + (ch ^ 48), ch = getchar();
	return f ? -s : s;
}

void push_up(int rt) {
	tree[rt].sum = tree[lson].sum + tree[rson].sum;
	tree[rt].min = min(tree[lson].min, tree[rson].min);
}

void build(int rt, int l, int r) {
	tree[rt].len = r - l + 1;
	if (l == r) {
		tree[rt].sum = tree[rt].min = read();
		return;
	}
	int mid = (l + r) >> 1;
	build(lson, l, mid);
	build(rson, mid + 1, r);
	push_up(rt);
}

void push_down(int rt) {
	if (!tree[rt].lazy) return;
	tree[lson].sum += tree[lson].len * tree[rt].lazy;
	tree[rson].sum += tree[rson].len * tree[rt].lazy;
	tree[lson].min += tree[rt].lazy;
	tree[rson].min += tree[rt].lazy;
	tree[lson].lazy += tree[rt].lazy;
	tree[rson].lazy += tree[rt].lazy;
	tree[rt].lazy = 0;
}

void update(int rt, int c, int l, int r, int L, int R) {
	if (L <= l && r <= R) {
		tree[rt].sum += tree[rt].len * c;
		tree[rt].min += c;
		tree[rt].lazy += c;
		return;
	}
	push_down(rt);
	int mid = (l + r) >> 1;
	if (L <= mid) update(lson, c, l, mid, L, R);
	if (R > mid) update(rson, c, mid + 1, r, L, R);
	push_up(rt);
}

int query_sum(int rt, int l, int r, int L, int R) {
	if (L <= l && r <= R) return tree[rt].sum;
	push_down(rt);
	int mid = (l + r) >> 1, ans = 0;
	if (L <= mid) ans += query_sum(lson, l, mid, L, R);
	if (R > mid) ans += query_sum(rson, mid + 1, r, L, R);
	return ans;
}

int query_min(int rt, int l, int r, int L, int R) {
	if (L <= l && r <= R) return tree[rt].min;
	push_down(rt);
	int mid = (l + r) >> 1, ans = 2147483647;
	if (L <= mid) ans = min(ans, query_min(lson, l, mid, L, R));
	if (R > mid) ans = min(ans, query_min(rson, mid + 1, r, L, R));
	return ans;
}

signed main() {
	n = read(), m = read();
	char sy;
	build(1, 1, n);
	for (int i = 1, x, y, d; i <= m; i++) {
		cin >> sy;
		if (sy == 'P') {
			x = read(), y = read(), d = read();
			update(1, d, 1, n, x, y);
		}
		if (sy == 'M') {
			x = read(), y = read();
			printf("%lld\n", query_min(1, 1, n, x, y));
		}
		if (sy == 'S') {
			x = read(), y = read();
			printf("%lld\n", query_sum(1, 1, n, x, y));
		}
	}
	return 0;
}
```


---

## 作者：Melo_DDD (赞：1)

索引：分块是一种优美的暴力。
## 分块为什么优美
简述分块思想：将原序列划分成一堆块，大块整体操作，小块暴力更改。

分块的优美之处：我们尝试将原序列划分成 $t$ 个元素一块的若干堆块，不管是查询还是修改操作，如果我们暴力更改小块，复杂度是 $\mathcal{O}(t)$，如果加上大块的整体操作，复杂度是 $\mathcal{O}(\frac{n}{t}+t)$，根据均值不等式，当 $t=\sqrt{n}$ 时最优，复杂度均为 $\mathcal{O}(\sqrt{n})$。

整体复杂度分析：我们不妨令 $n$、$q$ 同阶，则整体复杂度为 $\mathcal{O}(n\sqrt{n})$，虽然在渐进意义上不如线段树的 $\log$，但是对于本题一样的数据仍然绰绰有余（虽然带点小常数）。

为什么要用分块：好想，实现简单（~~总比懒标记好记~~），直观。
## 题目实现
首先最为朴素的区间加和求和操作，我们对于小块直接暴力更改、求和，对于大块，考虑维护一个增量标记 $add$，表示这个块加了多少**而我们还没有统计**。最后加上增量标记乘区间长度即可。

对于稍微不朴素的区间最小值操作，显然如果我们对整块进行区间加，那么这个块的最小值也相应地增加这个数，所以可以在 $\mathcal{O}(1)$ 时间内完成。但是如果对一个块的一部分进行操作（也就是小块），那整个大块的最小值不一定会变成什么样子，所以我们选择**暴力重更新**。$\mathcal{O}(\sqrt{n})$ 仍然可以接受。

千万别忘了 $add$。

其余的看代码：


```cpp
#include <bits/stdc++.h>
#define inf LONG_LONG_MAX 
#define f(i ,m ,n ,x) for (int i = (m) ;i <= (n) ;i += (x))
using namespace std ;
template < typename T > inline void read ( T&x ) {
	x = 0 ;
	bool flag (0) ;
	register char ch = getchar () ;
	while (! isdigit (ch)) {
		flag = ch == '-' ;
		ch = getchar () ;
	}
	while (isdigit (ch)) {
		x = (x << 1) + (x << 3) + (ch ^ 48) ;
		ch = getchar () ;
	}
	flag ? x = -x : 0 ;
}
const int N = 2e5 + 7 ;
const int M (666) ;
#define int long long
int n ,q ,l[M] ,r[M] ,belong[N] ;
int a[N] ,sum[M] ,add[M] ,minn[M] ;
namespace shin {
	inline void modify (int L ,int R ,int k) {
		int p = belong[L] ,q = belong[R] ;
		if (p == q) {
			minn[p] = inf ; // 直接重新更新
			f (i ,l[p] ,r[p] ,1) { // L、R 在一个块内
				if (i >= L && i <= R) {
					a[i] += k ; // 区间加
				}
				minn[p] = min (minn[p] ,a[i] + add[p]) ;
			}
			sum[p] += (R - L + 1) * k ;
			return ;
		}
    // 若不在，则可以变成若干大块加两小块的样式
		minn[p] = minn[q] = inf ;
		f (i ,l[p] ,r[p] ,1) {
			if (i >= L) {
				a[i] += k ;
			} 
			minn[p] = min (minn[p] ,a[i] + add[p]) ;
		}
		sum[p] += (r[p] - L + 1) * k ;
		f (i ,l[q] ,r[q] ,1) {
			if (i <= R) {
				a[i] += k ;
			}
			minn[q] = min (minn[q] ,a[i] + add[q]) ;
		}
		sum[q] += (R - l[q] + 1) * k ;
		f (i ,p + 1 ,q - 1 ,1) {
			add[i] += k ;
			minn[i] += k ;
		}
	}
	inline int find (int L ,int R) {
		int p = belong[L] ,q = belong[R] ;
		if (p == q) {
			int ans = inf ;
			f (i ,L ,R ,1) {
				ans = min (ans ,a[i] + add[p]) ;
			} 
			return ans ;
		}
		int ans = inf ;
		f (i ,L ,r[p] ,1) {
			ans = min (ans ,a[i] + add[p]) ;
		}
		f (i ,l[q] ,R ,1) {
			ans = min (ans ,a[i] + add[q]) ;
		}
		f (i ,p + 1 ,q - 1 ,1) {
			ans = min (ans ,minn[i]) ;
		}
		return ans ;
	}
	inline int query (int L ,int R) {
		int p = belong[L] ,q = belong[R] ;
		if (p == q) {
			int ans (0) ;
			f (i ,L ,R ,1) {
				ans += a[i] + add[p] ;
			}
			return ans ;
		} 
		int ans (0) ;
		f (i ,L ,r[p] ,1) {
			ans += a[i] + add[p] ;
		}
		f (i ,l[q] ,R ,1) {
			ans += a[i] + add[q] ;
		}
		f (i ,p + 1 ,q - 1 ,1) {
			ans += sum[i] + add[i] * (r[i] - l[i] + 1) ;
		}
		return ans ;
	}
}
signed main () {
	read (n) ,read (q) ;
	f (i ,1 ,n ,1) {
		read (a[i]) ; 
	}
	int t = sqrt (n) ; // 求块长和块数
	f (i ,1 ,t ,1) {
		minn[i] = inf ;
		l[i] = (i - 1) * t + 1 ;
		r[i] = i * t ;
	} // 记录大块左右断点
	if (r[t] < n) {
		t ++ ;
		l[t] = r[t - 1] + 1 ;
		r[t] = n ;
	} // t 很可能不是真正的 sqrt (n)，也就是说最后可能会剩下一个小块
	f (i ,1 ,t ,1) {
		f (j ,l[i] ,r[i] ,1) {
			belong[j] = i ;
			sum[i] += a[j] ;
			minn[i] = min (minn[i] ,a[j]) ;
		}
	} // 记录每个点属于哪个块，顺带统计块和和块内最小值
	do {
		int a ,b ;
		int c ;
		char ch ;
		cin >> ch ;
		if (ch == 'P') {
			read (a) ,read (b) ,read (c) ;
			shin :: modify (a ,b ,c) ;
		}
		else if (ch == 'M') {
			read (a) ,read (b) ;
			cout << shin :: find (a ,b) << '\n' ; 
		}
		else {
			read (a) ,read (b) ;
			cout << shin :: query (a ,b) << '\n' ;
		}
	} while (q -- != 1) ;
	return 0 ;
}
```

---

## 作者：Fheiwn (赞：1)

本来是想找并查集的，发现了这道线段树，就直接水过去。


主要的就是线段树模板：区间求和+区间最小值+Lazy标记（不知道不加能不能过）。


线段树不多讲，“线段树模板”这道题有很多人讲得很好。注意就是要开long long。










    

```cpp
#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<queue>
#include<stack>
#include<vector>
#include<set>
#include<bitset>
#include<sstream>
#include<cstdlib>
#define QAQ int
#define TAT long long
#define ORZ double
#define OwO bool
#define SHO short
#define F(i,j,n) for(QAQ i=j;i<=n;++i)
#define E(i,j,n) for(QAQ i=j;i>=n;--i)
#define MES(i,j) memset(i,j,sizeof(i))
#define MEC(i,j) memcpy(i,j,sizeof(j))
#define mid (l+r>>1)
#define LS l,mid,o<<1
#define RS mid+1,r,o<<1|1
using namespace std;
const QAQ N=200000;
QAQ n,m;
struct data{
    TAT sum,Min,lazy;
}tree[N<<2];
void push_up(QAQ o){
    tree[o].sum=tree[o<<1].sum+tree[o<<1|1].sum;
    tree[o].Min=min(tree[o<<1].Min,tree[o<<1|1].Min);
}
void push_down(QAQ o,TAT l){
    if(tree[o].lazy!=0){
        tree[o<<1].lazy+=tree[o].lazy;
        tree[o<<1].Min+=tree[o].lazy;
        tree[o<<1].sum+=tree[o].lazy*(l-(l>>1));
        tree[o<<1|1].lazy+=tree[o].lazy;
        tree[o<<1|1].Min+=tree[o].lazy;
        tree[o<<1|1].sum+=tree[o].lazy*(l>>1);
        tree[o].lazy=0;
    }
}
void build(QAQ l,QAQ r,QAQ o){
    if(l==r){
        scanf("%lld",&tree[o].sum);
        tree[o].Min=tree[o].sum;
        return ;
    }
    build(LS);build(RS);
    push_up(o);
}
void add(QAQ l,QAQ r,QAQ o,QAQ a,QAQ b,TAT c){
    if(l>=a&&r<=b){
        tree[o].sum+=c*(r-l+1);
        tree[o].Min+=c;
        tree[o].lazy+=c;
        return ;
    }
    push_down(o,(TAT)r-l+1);
    if(a<=mid) add(LS,a,b,c);
    if(b>mid) add(RS,a,b,c);
    push_up(o);
}
TAT Qmin(QAQ l,QAQ r,QAQ o,QAQ a,QAQ b){
    if(l>=a&&r<=b) return tree[o].Min;
    push_down(o,(TAT)r-l+1);
    TAT Min=1e18;
    if(a<=mid) Min=min(Min,Qmin(LS,a,b));
    if(b>mid) Min=min(Min,Qmin(RS,a,b));
    return Min;
}
TAT Qsum(QAQ l,QAQ r,QAQ o,QAQ a,QAQ b){
    if(l>=a&&r<=b) {
        return tree[o].sum;
    }
    push_down(o,(TAT)r-l+1);
    TAT ans=0;
    if(a<=mid) ans+=Qsum(LS,a,b);
    if(b>mid) ans+=Qsum(RS,a,b);
    return ans;
}
QAQ main(){
    scanf("%d%d",&n,&m);
    build(1,n,1);
    while(m--){
        char c;
        cin>>c;
        if(c=='P'){
            QAQ l,r;
            TAT x;
            scanf("%d%d%lld",&l,&r,&x);
            add(1,n,1,l,r,x);
        }
        if(c=='M'){
            QAQ l,r;
            scanf("%d%d",&l,&r);
            printf("%lld\n",Qmin(1,n,1,l,r));
        }
        if(c=='S'){
            QAQ l,r;
            scanf("%d%d",&l,&r);
            printf("%lld\n",Qsum(1,n,1,l,r));
        }
    }
    return 0;
}
```

---

## 作者：zhengrunzhe (赞：0)

来一波指针Splay

裸的线段树题，~~但我偏要用Splay做~~

Splay维护序列，支持区间加、区间最小值、区间和

像线段树那样打个懒标记像线段树那样做就可以了

每个数初始最大10^5，每次加最大10^5，最多有10^5次操作，会爆int，记得开long long
```cpp
#include<cstdio>
#include<algorithm>
using std::min;
template<class type>inline const void read(type &in)
{
	in=0;char ch=getchar();short fh=1;
	while (ch<48||ch>57)fh=ch=='-'?-1:fh,ch=getchar();
	while (ch>47&&ch<58)in=(in<<3)+(in<<1)+ch-48,ch=getchar();
	in*=fh;
}
typedef long long ll;
const int N=2e5+10;
const ll INF=1e11;
int n,m;
ll a[N];
class Splay
{
	private:
		struct tree
		{
			int size;
			ll tag,sum,value,mn;
			tree *fa,*son[2];
			inline const void pushup()
			{
				size=son[0]->size+1+son[1]->size;
				sum=son[0]->sum+value+son[1]->sum;
				mn=min(min(son[0]->mn,son[1]->mn),value);
			}
			inline const void pushdown()
			{
				if (!tag)return;
				son[0]->add(tag);
				son[1]->add(tag);
				tag=0;
			}
			inline void add(ll w)
			{
				tag+=w;mn+=w;value+=w;sum+=size*w;
			}
			inline const bool identity()
			{
				return fa->son[1]==this;
			}
		}memory_pool[N],*tail;
	public:
		tree *root,*null;
	protected:
		inline const void init()
		{
			tail=memory_pool;
			null=tail++;
			null->mn=INF;
			null->fa=null->son[0]=null->son[1]=null;
			null->tag=null->value=null->sum=null->size=0;
			root=null;
		}
		inline tree *newtree(ll key)
		{
			tree *p=tail++;
			p->size=1;p->tag=0;
			p->mn=p->value=p->sum=key;
			p->fa=p->son[0]=p->son[1]=null;
			return p;
		}
		inline const void connect(tree *p,tree *fa,bool which)
		{
			if (p!=null)p->fa=fa;
			if (fa!=null)fa->son[which]=p,fa->pushup();
		}
		inline const void rotate(tree *p)
		{
			tree *fa=p->fa;
			bool id=p->identity();
			fa->pushdown();p->pushdown();
			connect(p,fa->fa,fa->identity());
			connect(p->son[id^1],fa,id);
			connect(fa,p,id^1);
			fa->pushup();p->pushup();
		}
		inline const void splay(tree *p,tree *goal)
		{
			for (tree *fa;(fa=p->fa)!=goal;rotate(p))
				if (fa->fa!=goal)
					rotate(p->identity()^fa->identity()?p:fa);
			if (goal==null)root=p;
		}
		inline tree *findrank(int ranking)
		{
			ranking++;tree *now=root; //因为加入了哨兵节点所以实际上查第k个点就是第k+1个
			while (now->pushdown(),1)
				if (ranking<=now->son[0]->size)now=now->son[0];
				else if (!(ranking-=(now->son[0]->size+1)))return now;
					else now=now->son[1];
		}
		inline tree *split(int l,int r)  //把区间[l,r]提取出来
		{
			tree *pre=findrank(l-1),*nxt=findrank(r+1);
			splay(pre,null);splay(nxt,pre);
			return nxt->son[0];
		}
	public:
		inline Splay(){init();}
		inline tree *build(int l,int r,tree *fa) //建树
		{
			if (l>r)return null;
			int mid=l+r>>1;
			tree *p=newtree(a[mid]);p->fa=fa;
			if (l==r)return p;
			p->son[0]=build(l,mid-1,p);
			p->son[1]=build(mid+1,r,p);
			return p->pushup(),p;
		}
		inline const void add(int l,int r,int w)
		{
			split(l,r)->add(w);
		}
		inline const ll querymin(int l,int r)
		{
			return split(l,r)->mn;
		}
		inline const ll querysum(int l,int r)
		{
			return split(l,r)->sum;
		}
}S;
int main()
{
	read(n);read(m);
	for (int i=1;i<=n;i++)read(a[i]);
	a[0]=a[n+1]=INF;S.root=S.build(0,n+1,S.null); //添加哨兵节点0和n+1防止处理区间[1,x]/[x,n]时找不到前驱/后继
	while (m--)
	{
		char opt;int l,r,x;
		scanf(" %c",&opt);read(l);read(r);
		switch (opt)
		{
			case 'M':printf("%lld\n",S.querymin(l,r));break;
			case 'P':read(x);S.add(l,r,x);break;
			case 'S':printf("%lld\n",S.querysum(l,r));break;
		}
	}
	return 0;
}
```

---

