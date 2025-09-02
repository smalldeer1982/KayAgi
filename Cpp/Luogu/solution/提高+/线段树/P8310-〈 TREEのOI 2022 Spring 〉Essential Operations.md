# 〈 TREEのOI 2022 Spring 〉Essential Operations

## 题目背景

最近，月球上神秘出现了一个环。

据说，只要拿到这个环，便可以穿越时空……

![](https://tse1-mm.cn.bing.net/th/id/R-C.a57722cfcdec7e164113680dbf6a0403?rik=eVL5ObGthJQrqw&riu=http%3a%2f%2fimg2.diglog.com%2fimg%2f2021%2f1%2f79df8c71177d1b9035a179506645955b.jpg&ehk=yzECJQeeeiBu9KQrax2R7VjKNVzhg2XI1z0ykNOEx2g%3d&risl=&pid=ImgRaw&r=0)

## 题目描述

你需要维护一个 $n$ 个元素的数列 $A$ ，并执行 $m$ 个操作：

- `1 l r x`：$[l,r]$ 区间全部数加 $x$；

- `2 l r x`：$[l,r]$ 区间全部数乘 $x$；

- `3 l r`：输出 $[l,r]$ 区间所有数的和 $S \bmod 19260817$ 的值；

- `4`：$A$ 数列回溯到上一次`4`操作**前**（如果不存在上一次则回溯到初始状态），同时**倒序执行**上一次回溯后到回溯前的所有`1`操作和`2`操作（见样例解释）。

## 说明/提示

#### 样例解释：

##### 1

1. 初始状态 `1 2 3 4 5`；
2. `1 1 3 3` -> 此时数列为`4 5 6 4 5`；
3. `2 2 4 2` -> 此时数列为`4 10 12 8 5`；
4. `3 1 5` -> $ans=4+10+12+8+5=39$
5. `4` -> 回溯到初始状态`1 2 3 4 5` -> 依次执行`2 2 4 2`与`1 1 3 3` -> 此时数列为`4 7 9 8 5`；
6. `3 1 5` -> $ans=4+7+9+8+5=33$

##### 2

1. 初始状态 `1 1 1 1 1`
2. `1 1 3 1`: `2 2 2 1 1`
3. `2 2 4 2`: `2 4 4 2 1`
4. `4`: `2 3 3 2 1`
5. `1 1 5 1`: `3 4 4 3 2`
6. `2 1 5 2`: `6 8 8 6 4`
7. `4`: 回溯到`2 4 4 2 1`并依次执行`2 1 5 2` -> `1 1 5 1`: `5 9 9 5 3`
8. `3 1 5 2` 答案为 $31$

#### 数据范围

对于前 $10\%$ 的数据，没有 $4$ 操作。

对于前 $30\%$ 的数据，$n,m \le 10^3$。

对于前 $50\%$ 的数据，空间限制为 $400$ MB，另 $50\%$ 的数据空间限制为 $45$ MB。

对于 $100\%$ 的数据， $1 \le n \le 5 \times 10^5$，$0 \le A_i,x \le 10^3$，$1 \le m \le 10^5$ 。

d0j1a_1701 是个煽凉的出题人，所以时间限制为 $500$ ms。

---

#### 彩蛋


> ![](https://cdn.luogu.com.cn/upload/image_hosting/d4pi6qm9.png)


***

#### 【后记】

你穿着最新款高科技宇航服登上了月球。

那令人梦寐以求的环，就在眼前。

你缓缓走了过去。

只见环却从四周延伸出透明的屏障，里面散发出蓝绿的光芒，将你罩住。

你飞起来了！你已无法分清是你在控制环，还是环在控制你。

![](https://cdn.luogu.com.cn/upload/image_hosting/cy4fudx3.png)

突然，一道刺眼的亮光照射了进来，你下意识地闭上了眼睛，耳旁呼呼地响。你感觉好像有风，但又不是普通的风。

突然，风停了。腿脚又站在了陆地上。睁开迷蒙的眼睛，你看见，rin 和 len 在玩一个绝对简单的游戏……

## 样例 #1

### 输入

```
5 5
1 2 3 4 5
1 1 3 3
2 2 4 2
3 1 5
4
3 1 5```

### 输出

```
39
33```

## 样例 #2

### 输入

```
5 7
1 1 1 1 1
1 1 3 1
2 2 4 2
4
1 1 5 1
2 1 5 2
4
3 1 5```

### 输出

```
31```

## 样例 #3

### 输入

```
7 14
305 740 36 205 343 20 90 
4
2 2 7 529
3 1 2
1 2 4 713
4
3 3 7
3 2 4
4
1 6 7 597
1 1 4 232
3 2 4
1 1 3 220
3 1 7
4```

### 输出

```
391765
1121480
1650480
521784
763812```

# 题解

## 作者：ax_by_c (赞：3)

看到这道题目，相信很多同学以为这题是主席树。

但是，就算用了主席树，还是会被卡空间。

其实，这题的正解就是线段树，只要一点点骚操作就好了。

首先，非常明显，前三个操作就是常规的线段树 2 的操作。

仔细观察第 4 个操作，可以发现不是回溯到任意时间，而是回溯到上一个 4 操作前。

所以，我们只要记录上一次 4 操作前的数组状态，就能够实现回溯操作。

那么一棵线段树怎么记录呢？

一棵不够就开两棵，其中一棵是记忆树，另一棵就是当前状态的树（当前树）。

前 3 个操作仍然用当前树完成。

而遇到 4 操作时，把这两棵树换一下（回溯），然后倒序处理操作。

并且，此时的记忆树正是这次 4 操作前的树。

时间复杂度证明：每个操作至多执行 2 次（正序和倒序各一次），所以复杂度不变。

code:
```
#include<iostream>
#include<cstdio>
using namespace std;
typedef long long ll;
const ll mod=19260817;
const int N=5e5+5;
const int M=1e5+5;
int a[N];
struct node
{
	int sum,add,mul;
};
int mti(int a,int b)
{
	return (ll(a)%mod)*(ll(b)%mod)%mod;
}
int ad(int a,int b)
{
	return ll(a+b)%mod;
}
int lens(int l,int r)
{
	return r-l+1;
}
struct ST
{
	node tr[4*N];
	void pushup(int u,int l,int r)
	{
		tr[u].sum=ad(tr[u<<1].sum,tr[u<<1|1].sum);
	}
	void pushdown(int u,int l,int r)
	{
		int mid=l+((r-l)>>1);
		if(tr[u].mul!=1)
		{
			tr[u<<1].add=mti(tr[u<<1].add,tr[u].mul);
			tr[u<<1].mul=mti(tr[u<<1].mul,tr[u].mul);
			tr[u<<1].sum=mti(tr[u<<1].sum,tr[u].mul);
			tr[u<<1|1].add=mti(tr[u<<1|1].add,tr[u].mul);
			tr[u<<1|1].mul=mti(tr[u<<1|1].mul,tr[u].mul);
			tr[u<<1|1].sum=mti(tr[u<<1|1].sum,tr[u].mul);
			tr[u].mul=1;
		}
		if(tr[u].add)
		{
			tr[u<<1].add=ad(tr[u<<1].add,tr[u].add);
			tr[u<<1].sum=ad(tr[u<<1].sum,mti(lens(l,mid),tr[u].add));
			tr[u<<1|1].add=ad(tr[u<<1|1].add,tr[u].add);
			tr[u<<1|1].sum=ad(tr[u<<1|1].sum,mti(lens(mid+1,r),tr[u].add));
			tr[u].add=0;
		}
	}
	void build(int u,int l,int r)
	{
		tr[u].mul=1;
		if(l==r)
		{
			tr[u].sum=a[l];
			return ;
		}
		int mid=l+((r-l)>>1);
		build(u<<1,l,mid);
		build(u<<1|1,mid+1,r);
		pushup(u,l,r);
	}
	void update_add(int u,int l,int r,int ql,int qr,int vu)
	{
		if(ql<=l&&r<=qr)
		{
			tr[u].add=ad(tr[u].add,vu);
			tr[u].sum=ad(tr[u].sum,mti(vu,lens(l,r)));
			return ;
		}
		pushdown(u,l,r);
		int mid=l+((r-l)>>1);
		if(ql<=mid)
		{
			update_add(u<<1,l,mid,ql,qr,vu);
		}
		if(mid+1<=qr)
		{
			update_add(u<<1|1,mid+1,r,ql,qr,vu);
		}
		pushup(u,l,r);
	}
	void update_mul(int u,int l,int r,int ql,int qr,int vu)
	{
		if(ql<=l&&r<=qr)
		{
			tr[u].add=mti(tr[u].add,vu);
			tr[u].mul=mti(tr[u].mul,vu);
			tr[u].sum=mti(tr[u].sum,vu);
			return ;
		}
		pushdown(u,l,r);
		int mid=l+((r-l)>>1);
		if(ql<=mid)
		{
			update_mul(u<<1,l,mid,ql,qr,vu);
		}
		if(mid+1<=qr)
		{
			update_mul(u<<1|1,mid+1,r,ql,qr,vu);
		}
		pushup(u,l,r);
	}
	int Q(int u,int l,int r,int ql,int qr)
	{
		if(ql<=l&&r<=qr)
		{
			return tr[u].sum;
		}
		pushdown(u,l,r);
		int mid=l+((r-l)>>1);
		int ans=0;
		if(ql<=mid)
		{
			ans=ad(ans,Q(u<<1,l,mid,ql,qr));
		}
		if(mid+1<=qr)
		{
			ans=ad(ans,Q(u<<1|1,mid+1,r,ql,qr));
		}
		return ans;
	}
};
ST tr[2];
int n,m;
int op[M],l[M],r[M],x[M];
int cur;
int main()
{
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
	}
	tr[0].build(1,1,n);
	tr[1].build(1,1,n);
	cur=1;
	int lst=0;
	for(int i=1;i<=m;i++)
	{
		scanf("%d",&op[i]);
		if(op[i]==1)
		{
			scanf("%d %d %d",&l[i],&r[i],&x[i]);
		}
		if(op[i]==2)
		{
			scanf("%d %d %d",&l[i],&r[i],&x[i]);
		}
		if(op[i]==3)
		{
			scanf("%d %d",&l[i],&r[i]);
		}
	}
	for(int i=1;i<=m;i++)
	{
		if(op[i]==1)//常规操作
		{
			tr[cur].update_add(1,1,n,l[i],r[i],x[i]);
		}
		if(op[i]==2)
		{
			tr[cur].update_mul(1,1,n,l[i],r[i],x[i]);
		}
		if(op[i]==3)
		{
			printf("%d\n",tr[cur].Q(1,1,n,l[i],r[i]));
		}
		if(op[i]==4)
		{
			for(int j=i-1;j>lst;j--)//倒着处理
			{
				if(op[j]==1)
				{
					tr[1-cur].update_add(1,1,n,l[j],r[j],x[j]);
				}
				if(op[j]==2)
				{
					tr[1-cur].update_mul(1,1,n,l[j],r[j],x[j]);
				}
			}
			cur=1-cur;//互换树
			lst=i;
		}
	}
	return 0;
}
```
坑点：

1.不要存 l 和 r，不然会 MLE 。

2.别用 long long，强制转换就行了。

3.倒着处理时 3 操作不用做。

4.两棵树一开始都是初始状态。

5.不用管题目里说的 45M，只要尽你所能压就好了。

---

## 作者：d0j1a_1701 (赞：1)

题目传送门：[〈TREE の OI·R1〉Essential Operations](https://www.luogu.com.cn/problem/P8310)

[在 d0j1a_1701 的博客上查看](https://www.d0j1a1701.cc/p/477c80cd/)

# 10 pts

暴力模拟即可。

# 30 pts

暴力模拟即可。

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
struct Oper {
	int op, l, r, x;
};
const int mod = 19260817;
int n, m, lst = -1, arr[500010], mem[500010], tmp[500010];
vector<Oper> oper;
inline void process(int op, int l, int r, int x) {
	x %= mod;
	if(op == 1)
		for(int i = l; i <= r; i++)   arr[i] = ((long long)arr[i] + x) % mod;
	if(op == 2)
		for(int i = l; i <= r; i++)   arr[i] = ((long long)arr[i] * x) % mod;
	if(op == 3) {
		int sum = 0;
		for(int i = l; i <= r; i++)   sum = ((long long)sum + arr[i]) % mod;
		cout << sum << endl;
	}
}
inline void print() {
	for(int i = 1; i <= n; i++)   cout << arr[i] << ' ';
	cout << endl;
}
int main() {
	cin >> n >> m;
	for(int i = 1; i <= n; i++)   cin >> arr[i];
	copy(arr + 1, arr + 1 + n, mem + 1);
	for(int i = 1; i <= m; i++) {
		int op, l, r, x;
		cin >> op;
		if(op == 1 || op == 2)   cin >> l >> r >> x;
		if(op == 3)   cin >> l >> r;
		oper.push_back({op, l, r, x});
	}
	for(int i = 0; i < m; i++) {
		//cout << "Process:" << oper[i].op << ' ' << oper[i].l << ' ' << oper[i].r << ' ' << oper[i].x << endl;
		if(oper[i].op != 4)    process(oper[i].op, oper[i].l, oper[i].r, oper[i].x);
		else {
			copy(arr + 1, arr + 1 + n, tmp + 1);
			copy(mem + 1, mem + 1 + n, arr + 1);
			copy(tmp + 1, tmp + 1 + n, mem + 1);
			for(int j = i - 1; j >= lst + 1; j--)
				if(oper[j].op != 3) process(oper[j].op, oper[j].l, oper[j].r, oper[j].x);
			lst = i;
		}
		//print();
	}
	//system("pause");
	return 0;
}
```

# 50 pts

使用`可持久化线段树`优化暴力。

# 100 pts

注意这句话：

> 回溯到**上一次`4`操作前**（如果不存在上一次则回溯到初始状态），倒序执行上一次回溯后到回溯前的所有`1`操作和`2`操作

为什么是**上一次`4`操作前**？按照正常的逻辑不应该是上一次`4`操作后吗？

这句话就是一个突破口，我们可以离线执行，建立两棵线段树，一棵正序执行并输出结果，一棵从下一个`4`操作开始逆序执行所有操作。

每当遇到`4`操作，只需要交换一下两棵线段树，用原本倒序的线段树正序执行接下来的操作，即可 $O(1)$ 实现`4`操作。

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
const int p = 19260817;
int n, m, arr[500010];
namespace smt {
int tree[2][4000010], add[2][4000010], mul[2][4000010];
inline void pushup(int rt,int id) {
	tree[rt][id] = (tree[rt][id<<1] + tree[rt][id<<1|1]) % p;
}
inline void pushdown(int rt, int id, int l, int r) {
	int mid = l + r >> 1;
	tree[rt][id<<1] = ((long long)tree[rt][id<<1] * mul[rt][id] + (long long)add[rt][id] * (mid - l + 1) % p) % p;
	tree[rt][id<<1|1] = ((long long)tree[rt][id<<1|1] * mul[rt][id] + (long long)add[rt][id] * (r - mid) % p) % p;
	mul[rt][id<<1] = ((long long)mul[rt][id<<1] * mul[rt][id]) % p;
	mul[rt][id<<1|1] = ((long long)mul[rt][id<<1|1] * mul[rt][id]) % p;
	add[rt][id<<1] = ((long long)add[rt][id<<1] * mul[rt][id] + add[rt][id]) % p;
	add[rt][id<<1|1] = ((long long)add[rt][id<<1|1] * mul[rt][id] + add[rt][id]) % p;
	mul[rt][id] = 1, add[rt][id] = 0;
}
void build(int rt, int id, int l, int r) {
	mul[rt][id] = 1;
	if(l == r) {
		tree[rt][id] = arr[l] % p;
		return;
	}
	int mid = l + r >> 1;
	build(rt, id<<1, l, mid);
	build(rt, id<<1|1, mid + 1, r);
	pushup(rt, id);
}
void adjust1(int rt, int id, int x, int y, int k, int l, int r) {
	if(!id)	return;
	if(x <= l && r <= y) {
		add[rt][id] = (long long)(add[rt][id] + k) % p;
		tree[rt][id] = (tree[rt][id] + (long long)(r - l + 1) * k) % p;
		return;
	}
	pushdown(rt, id, l, r);
	int mid = l + r >> 1;
	if(x <= mid)  adjust1(rt, id<<1, x, y, k, l, mid);
	if(mid < y)   adjust1(rt, id<<1|1, x, y, k, mid + 1, r);
	pushup(rt, id);
}
void adjust2(int rt, int id, int x, int y, int k, int l, int r) {
	if(!id)	return;
	if(x <= l && r <= y) {
		tree[rt][id] = ((long long)tree[rt][id] * k) % p;
		mul[rt][id] = ((long long)mul[rt][id] * k) % p;
		add[rt][id] = ((long long)add[rt][id] * k) % p;
		return;
	}
	pushdown(rt, id, l, r);
	int mid = l + r >> 1;
	if(x <= mid)  adjust2(rt, id<<1, x, y, k, l, mid);
	if(mid < y)   adjust2(rt, id<<1|1, x, y, k, mid + 1, r);
	pushup(rt, id);
}
int query(int rt, int id, int x, int y, int l, int r) {
	if(!id)	return 0;
	if(x <= l && r <= y) return tree[rt][id] % p;
	pushdown(rt, id, l, r);
	int mid = l + r >> 1, res = 0;
	if(x <= mid)  res = query(rt, id<<1, x, y, l, mid) % p;
	if(mid < y)   res = (res + query(rt, id<<1|1, x, y, mid + 1, r)) % p;
	return res;
}
}
struct Oper {
	int op, l, r, x;
} oper[100010];
int op_4[100010], cnt, cur;
inline void process(int i, int rt, bool prt) {
	if(i <= 0)	return;
	Oper op = oper[i];
	if(op.op == 1)	smt::adjust1(rt, 1, op.l, op.r, op.x, 1, n);
	else if(op.op == 2)	smt::adjust2(rt, 1, op.l, op.r, op.x, 1, n);
	else if(op.op == 3 && prt)	cout << smt::query(rt, 1, op.l, op.r, 1, n) << endl;
}
inline void init() {
	smt::build(0, 1, 1, n);
	smt::build(1, 1, 1, n);
}
int main() {
	cin >> n >> m;
	for(int i = 1; i <= n; i++)	cin >> arr[i];
	for(int i = 1; i <= m; i++) {
		cin >> oper[i].op;
		if(oper[i].op < 4)	cin >> oper[i].l >> oper[i].r;
		if(oper[i].op < 3)	cin >> oper[i].x;
		if(oper[i].op == 4)	op_4[++cnt] = i;
	}
	init();
	int cur_op_4 = 0;
	for(int i = 1; i <= m; i++) {
		int rev = op_4[cur_op_4] + op_4[cur_op_4 + 1] - i;
		if(oper[i].op == 4) {
			cur_op_4++;
			cur ^= 1;
		} else process(i, cur, true), process(rev, cur^1, false);
	}
	//system("pause");
	return 0;
}
```

---

## 作者：Jorisy (赞：0)

不难，但挺有意思的。

最直接的思路当然是主席树，但是无论是空间还是时间都在明示这种做法的不必要性。

我们沿用主席树的思路，试着模拟一个操作过程看看我们到底需要存怎样的线段树。

我们按 $\tt 4$ 操作将整个操作过程划分成若干**块**：

$$
\gdef\red{\textcolor{ee0000}}
\gdef\blue{\textcolor{66ccff}}
\boxed{\textcolor{white}{11111}}\ 4\ \boxed{\textcolor{white}{11111}}\ 4\ \boxed{\textcolor{white}{11111}}\ 4\ \boxed{\textcolor{white}{11111}}\ 4\cdots
$$

对于第 $i$ **块**，如果是正序操作，我们记作 $\red i$；如果是逆序操作，我们记作 $\blue i$。

我们再记 $T_i$ 表示第 $i$ **段**操作（$\tt 4$ 本身也算作一段）后所影响树的操作序列。

- 显然有 $T_1=\red 1,T_2=\blue 1$。
- 对于 $T_3$，我们是在 $T_2$ 的基础上顺次操作，所以 $T_3=\blue1\red2$。
- 对于 $T_4$，由于题面说是先回到上一次 $\tt 4$ 操作**前**，故我们会回到 $T_1$，然后倒序做第二段，也就是 $T_4=\red1\blue2$。
- 显然 $T_5=\red1\blue2\red3$。
- ……

也就是说，对于一个 $k\in\mathbb N_+$，我们有 $T_{2k+1}=T_{2k}\red{k+1},T_{2k+2}=T_{2k-1}\blue{k}$，于是我们只要奇数下标和偶数下标的树各一个即可。

由于每个操作，最多被正序做一次，倒序做一次，所以时间复杂度 $O(q\log n)$。

```cpp
#include<bits/stdc++.h>
#define N 500005
#define ll long long
#define mod 19260817
using namespace std;

int n,m,a[N];
struct segt{
    #define mid (l+r>>1)
    #define lc (mid<<1)
    #define rc (mid<<1|1)
    struct node{
        int sum,add,mul;
    }sgt[N<<1];

    void upd(node &x,node y,node z)
    {
        x.sum=(y.sum+z.sum)%mod;
    }

    void build(int i,int l,int r)
    {
        sgt[i].mul=1;
        if(l>=r)
        {
            sgt[i]={a[r],0,1};
            return;
        }
        build(lc,l,mid);
        build(rc,mid+1,r);
        upd(sgt[i],sgt[lc],sgt[rc]);
    }

    void psd(int i,int l,int r)
    {
        int k=sgt[i].mul,d=sgt[i].add;
        sgt[i].mul=1;
        sgt[i].add=0;
        sgt[lc].sum=(1ll*sgt[lc].sum*k+1ll*d*(mid-l+1))%mod;
        sgt[lc].add=(1ll*sgt[lc].add*k+d)%mod;
        sgt[lc].mul=1ll*sgt[lc].mul*k%mod;
        sgt[rc].sum=(1ll*sgt[rc].sum*k+1ll*d*(r-mid))%mod;
        sgt[rc].add=(1ll*sgt[rc].add*k+d)%mod;
        sgt[rc].mul=1ll*sgt[rc].mul*k%mod;
    }

    void mdf(int i,int l,int r,int x,int y,int d,int op)
    {
        if(x<=l&&r<=y)
        {
            if(op)
            {
                sgt[i].sum=(sgt[i].sum+1ll*d*(r-l+1))%mod;
                sgt[i].add=(sgt[i].add+d)%mod;
                return;
            }
            sgt[i].sum=1ll*sgt[i].sum*d%mod;
            sgt[i].add=1ll*sgt[i].add*d%mod;
            sgt[i].mul=1ll*sgt[i].mul*d%mod;
            return;
        }
        psd(i,l,r);
        if(x<=mid) mdf(lc,l,mid,x,y,d,op);
        if(y>mid) mdf(rc,mid+1,r,x,y,d,op);
        upd(sgt[i],sgt[lc],sgt[rc]);
    }

    int qry(int i,int l,int r,int x,int y)
    {
        if(x<=l&&r<=y) return sgt[i].sum;
        psd(i,l,r);
        int res=0;
        if(x<=mid) (res+=qry(lc,l,mid,x,y))%=mod;
        if(y>mid) (res+=qry(rc,mid+1,r,x,y))%=mod;
        return res;
    }
}sgt[2];
struct node{
    int op,l,r,x;
}q[N];

int main()
{
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=m;i++)
    {
        int op,l,r,x;
        cin>>op;
        if(op<4) cin>>l>>r;
        if(op<3) cin>>x;
        q[i]={op,l,r,x};
    }
    sgt[0].build(1,1,n);
    sgt[1].build(1,1,n);
    vector<int>v;
    for(int i=1;i<=m;i++)
    {
        if(q[i].op^4) continue;
        v.push_back(i);
    }
    auto vp=v.begin();
    int tid=0,pos=vp!=v.end()?(*vp)-1:0;
    auto deal=[&](int id,int op,int l,int r,int x)
    {
        if(op==1) sgt[id].mdf(1,1,n,l,r,x,1);
        if(op==2) sgt[id].mdf(1,1,n,l,r,x,0);
        if(op==3&&id==tid) cout<<sgt[id].qry(1,1,n,l,r)<<'\n';
    };
    for(int i=1;i<=m;i++)
    {
        auto [op,l,r,x]=q[i];
        if(op==4)
        {
            vp++;
            pos=vp!=v.end()?(*vp)-1:0;
            tid^=1;
            continue;
        }
        if(pos) deal(tid^1,q[pos].op,q[pos].l,q[pos].r,q[pos].x),pos--;
        deal(tid,op,l,r,x);
        // for(int i=1;i<=n;i++) cerr<<sgt[tid].qry(1,1,n,i,i)<<' ';cerr<<'\n';
    }
    return 0;
}
```

---

## 作者：Drind (赞：0)

萌萌卡空间题。

### 题目解析

要求实现一个区间加，区间乘，区间求和的数据结构，并且支持一种回溯操作，每次回溯到上一次回溯操作前，然后把这之间的所有修改操作倒着做一遍。

一看这题，哎呀我直接可持久化秒了！兴冲冲地打完板子之后，发现空间限制 45MB，哎哟。

我们考虑用普通线段树解决。注意到每次回溯的位置不是随机的，一定是上一次操作前的位置，所以把上次操作的存下来就行了。但是因为旧版本重新写到线段树上复杂度是 $O(n\log n)$ 的，所以我们用另一颗线段树存。

我们惊奇的发现，线段树竟然可以循环使用，具体地，当遇到一次回溯操作时，我们先把手上的线段树放下，把存了上一个版本的线段树拿出来，倒着做一遍两次回溯之间的操作，然后接着用这个线段树走，直到下一个回溯点，这时先前放着的线段树竟然恰好保存了这个版本！

代码实现记得不能开 long long，区间不能存在节点上，乘法要强制类型转换再取模。注意一下区间操作的标记下传之类的。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e5+10;
const int M=1e5+10;
const int p=19260817;

int a[N];

int mul(int a,int b){
	return 1ll*a*b%p;
} 

struct segtree{
	struct node{
		int w,lazy1,lazy2;
	}tree[N*4];
	void pushup(int x){
		tree[x].w=(tree[x*2].w+tree[x*2+1].w)%p;
	}
	void pushdown(int x,int l,int r){
		int mid=l+r>>1;
		int lsiz=mid-l+1;
		int rsiz=r-(mid+1)+1;
		
		if(tree[x].lazy1!=1){
			int tag=tree[x].lazy1;
			tree[x*2].w=mul(tree[x*2].w,tag);
			tree[x*2+1].w=mul(tree[x*2+1].w,tag);
			tree[x*2].lazy1=mul(tree[x*2].lazy1,tag);
			tree[x*2+1].lazy1=mul(tree[x*2+1].lazy1,tag);
			tree[x*2].lazy2=mul(tree[x*2].lazy2,tag);
			tree[x*2+1].lazy2=mul(tree[x*2+1].lazy2,tag);
			tree[x].lazy1=1;
		}
		if(tree[x].lazy2!=0){
			int tag=tree[x].lazy2;
			tree[x*2].w=(tree[x*2].w+mul(tag,lsiz))%p;
			tree[x*2+1].w=(tree[x*2+1].w+mul(tag,rsiz))%p;
			tree[x*2].lazy2=(tree[x*2].lazy2+tag)%p;
			tree[x*2+1].lazy2=(tree[x*2+1].lazy2+tag)%p;
			tree[x].lazy2=0;
		}
	}
	
	void build(int x,int l,int r){
		tree[x].lazy1=1; tree[x].lazy2=0;
		if(l==r){
			tree[x].w=a[l];
			return;
		}
		int mid=(l+r)/2;
		build(x*2,l,mid); build(x*2+1,mid+1,r);
		pushup(x);
	}
	
	void modifyplus(int x,int L,int R,int l,int r,int val){
		//cout<<"PLUS "<<x<<" "<<l<<" "<<r<<" "<<val<<"\n";
		
		if(l<=L&&R<=r){
			//cout<<x<<"\n";
			tree[x].lazy2=(tree[x].lazy2+val)%p;
			tree[x].w=(tree[x].w+mul(val,(R-L+1)))%p;
			return;
		}
		if(L>r||R<l) return;
		pushdown(x,L,R); int mid=L+R>>1;
		modifyplus(x*2,L,mid,l,r,val);
		modifyplus(x*2+1,mid+1,R,l,r,val);
		pushup(x);	
	}
	
	void modifymul(int x,int L,int R,int l,int r,int val){
		if(l<=L&&R<=r){
			tree[x].lazy1=mul(tree[x].lazy1,val);
			tree[x].lazy2=mul(tree[x].lazy2,val);
			tree[x].w=mul(tree[x].w,val);
			return;
		}
		if(L>r||R<l) return;
		pushdown(x,L,R); int mid=L+R>>1;
		modifymul(x*2,L,mid,l,r,val);
		modifymul(x*2+1,mid+1,R,l,r,val);
		pushup(x);
	}
	
	int query(int x,int L,int R,int l,int r){
		if(l<=L&&R<=r){
			return tree[x].w;
		}
		if(L>r||R<l) return 0;
		pushdown(x,L,R); int mid=L+R>>1;
		return (query(x*2,L,mid,l,r)+query(x*2+1,mid+1,R,l,r))%p;
	}
}tree[2];

int L[M],R[M],opr[M],x[M];
int cnt=0;

inline void fake_main(){
	int n,m; cin>>n>>m; int now=1; int lst=0;
	for(int i=1;i<=n;i++) cin>>a[i];
	tree[0].build(1,1,n);
	tree[1].build(1,1,n);
	for(int i=1;i<=m;i++){
		int op; cin>>op;
		if(op==1){
			++cnt; opr[cnt]=1;
			cin>>L[cnt]>>R[cnt]>>x[cnt];
			tree[now].modifyplus(1,1,n,L[cnt],R[cnt],x[cnt]);
		}else if(op==2){
			++cnt; opr[cnt]=2;
			cin>>L[cnt]>>R[cnt]>>x[cnt];
			tree[now].modifymul(1,1,n,L[cnt],R[cnt],x[cnt]); 
		}else if(op==3){
			int l,r; cin>>l>>r;
			cout<<tree[now].query(1,1,n,l,r)<<"\n";
		}else if(op==4){
			now^=1;
			for(int j=cnt;j>lst;j--){
				if(opr[j]==1) tree[now].modifyplus(1,1,n,L[j],R[j],x[j]);
				else if(opr[j]==2) tree[now].modifymul(1,1,n,L[j],R[j],x[j]); 
			}
			lst=cnt;
		}
	}
}

signed main(){
	ios::sync_with_stdio(false);
	int t; t=1;
	while(t--) fake_main();
}
```

---

## 作者：Shanganze (赞：0)

### 分析：

前三个操作：

1. 区间加 
2. 区间乘 
3. 区间求和

这很明显需要用线段树来维护，不会以上操作的请先完成 [【模板】线段树 2](https://www.luogu.com.cn/problem/P3373)。
然后来分析操作 

4. A 数列回溯到上一次 4 操作前（如果不存在上一次则回溯到初始状态），同时倒序执行上一次回溯后到回溯前的所有 1 操作和 2 操作。

这时候明显需要维护多个线段树，可持久化线段树？，NO!。这道题只需要用到上一次 4 操作前的版本，所以只需要建两棵线段树交替使用就足够了，每次遇到 4 操作，交换两棵线段树，然后对新换来的线段树反向执行前面的操作，然后在用这棵树继续正序执行后面的操作，一直交替即可。

 然而，你以为这道题就这样轻松的 AC 了吗，不，煽凉的出题人把后 50% 的空间开成了 **45MB**，这可是要开 4 倍空间的线段树啊，喜欢存左右端点的朋友们注意了，这题**不能存左右端点**，我们也可以用动态开点来节省空间。并且这道题需要开 **long long**，但是必须在运算时强制转换，不然还会 MLE。一定要加上快读，能节省很多时间，还有就是取模运算不要太多，否则会很慢。

### AC Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e5+1;
struct a2
{
	int a,l,r,x;
}o[N];
struct a1
{
	int a,j,c;
}x[2][N<<2];
int d[N],p1=0,tree=0,mod=19260817;
inline void build(int l,int r,int p,int q)//建树
{
	x[q][p].c=1;x[q][p].j=0;
	x[q^1][p].c=1;x[q^1][p].j=0;
	if(l==r)
	{
		x[q][p].a=d[l];
		x[q^1][p].a=d[l];
		return ;
	}
	int mid=(l+r)>>1;
	build(l,mid,p<<1,q);
	build(mid+1,r,p<<1|1,q);
	x[q][p].a=(x[q][p<<1].a+x[q][p<<1|1].a);
	x[q^1][p].a=(x[q^1][p<<1].a+x[q^1][p<<1|1].a);
}
inline void pushdown(int p,int q,int s,int t)//懒标记下传，注意细节和先后顺序
{
	if(x[q][p].c!=1)
	{
		x[q][p<<1].c=1ll*(x[q][p].c*1ll*x[q][p<<1].c)%mod;
		x[q][p<<1|1].c=1ll*(x[q][p].c*1ll*x[q][p<<1|1].c)%mod;
		x[q][p<<1].j=1ll*(x[q][p].c*1ll*x[q][p<<1].j)%mod;
		x[q][p<<1|1].j=1ll*(x[q][p].c*1ll*x[q][p<<1|1].j)%mod;
		x[q][p<<1].a=1ll*(x[q][p].c*1ll*x[q][p<<1].a)%mod;
		x[q][p<<1|1].a=1ll*(x[q][p].c*1ll*x[q][p<<1|1].a)%mod;
		x[q][p].c=1;
	}
	if(x[q][p].j!=0)
	{
		int mid=(s+t)>>1;
		x[q][p<<1].j=1ll*(x[q][p].j+1ll*x[q][p<<1].j);
		x[q][p<<1|1].j=1ll*(x[q][p].j+1ll*x[q][p<<1|1].j);
		x[q][p<<1].a=1ll*((mid-s+1)*1ll*x[q][p].j+x[q][p<<1].a)%mod;
		x[q][p<<1|1].a=1ll*((t-mid)*1ll*x[q][p].j+x[q][p<<1|1].a)%mod;
		x[q][p].j=0;
	}
}
inline void chen(int s,int t,int l,int r,int p,int q,int k)//区间乘
{
	if(s>=l&&t<=r)
	{
	   x[q][p].a=1ll*(k*1ll*x[q][p].a)%mod;
	   x[q][p].j=1ll*(k*1ll*x[q][p].j)%mod;
	   x[q][p].c=1ll*(k*1ll*x[q][p].c)%mod;
	   return ;
	}
	pushdown(p,q,s,t);
	int mid=(s+t)>>1;
	if(mid>=l)chen(s,mid,l,r,p<<1,q,k);
	if(mid<r)chen(mid+1,t,l,r,p<<1|1,q,k);
	x[q][p].a=1ll*(x[q][p<<1].a+x[q][p<<1|1].a);
}
inline void jia(int s,int t,int l,int r,int p,int q,int k)//区间加
{
	if(s>=l&&t<=r)
	{
	   x[q][p].a=(1ll*(t-s+1)*k+x[q][p].a)%mod;
	   x[q][p].j=(1ll*k+x[q][p].j);
	   return ;
	}
	pushdown(p,q,s,t);
	int mid=(s+t)>>1;
	if(mid>=l)jia(s,mid,l,r,p<<1,q,k);
	if(mid<r)jia(mid+1,t,l,r,p<<1|1,q,k);
	x[q][p].a=1ll*(x[q][p<<1].a+x[q][p<<1|1].a);
}
inline int getsum(int s,int t,int l,int r,int p,int q)//区间求和
{
	if(s>=l&&t<=r)
	{
	   return x[q][p].a;
	}
	pushdown(p,q,s,t);
	int ans=0;
	int mid=(s+t)>>1;
	if(mid>=l)ans=1ll*(ans+getsum(s,mid,l,r,p<<1,q))%mod;
	if(mid<r)ans=1ll*(ans+getsum(mid+1,t,l,r,p<<1|1,q))%mod;
	return ans;
}
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=(x << 3) + (x << 1) +ch-48;ch=getchar();}//二进制优化快读
	return x*f;
	
}
int main()
{
	int n,m,mod;
	n=read();m=read();
	for(register int q=1;q<=n;q++)
	{
		d[q]=read();
	}
	build(1,n,1,0);
	for(register int q=1;q<=m;q++)
	{
		int a,l,r,x;
		a=read();
		if(a==1)
		{
			l=read();r=read();x=read();
			o[++p1].a=a;
			o[p1].l=l;
			o[p1].r=r;
			o[p1].x=x;
			jia(1,n,l,r,1,tree,x);
		}
		else if(a==2)
		{
			l=read();r=read();x=read();
			o[++p1].a=a;
			o[p1].l=l;
			o[p1].r=r;
			o[p1].x=x;
			chen(1,n,l,r,1,tree,x);
		}
		else if(a==3)
		{
			l=read();r=read();
			printf("%d\n",getsum(1,n,l,r,1,tree));
		}
		else //遇到4操作交换两棵树，同时倒序执行
		{
			tree=tree^1;
			for(register int i=p1;i>=1;i--)
			{
				int l=o[i].l,r=o[i].r,x=o[i].x;
				if(o[i].a==1)
				{
					jia(1,n,l,r,1,tree,x);
				}
				else
				{
					chen(1,n,l,r,1,tree,x);
				}
			}
			p1=0;
		}
	}
	return 0;
}
```



---

## 作者：Kalium (赞：0)

# P8310 〈 TREEのOI 2022 Spring 〉Essential Operations题解

## 前言：

线段树的小小变通题，以及卡点空间。

## 题意：

给定序列和一定操作，分别为区间加，区间乘，查询区间和，以及回溯操作。

啥意思，就是说从当前的 4 与上次的 4，用上次的 4 的序列，从当前的 4 开始，倒着执行操作直道遇到上次的 4 操作。

## 思路：

前面三个操作就不说了，不会的参考[线段树2](https://www.luogu.com.cn/problem/P3373)。

讲讲最后一个操作。

其实我们发现，我们需要用到之前的序列，一共有两种思路：

1.进行反操作，就是将之前所执行的操作全部反向执行一遍变成原先的序列。

2.重新建一个新的线段树。

明显法 1 繁琐复杂，并且常数会极大。

法 2 现实点并且好实现。

具体就是像走脚印一样，先把两棵树赋予相同的元素，当我们没遇到 4 操作时就对其中一个树进行正常加减，遇到 4 的时候，就调用另一棵树，因为这个时候这棵树还是在上一个 4 操作前的数组，所以说我们倒序调用一番操作进行修改，在对这棵树进行下一次操作，直到遇到下一个 4。

当然既然要反复调用操作，那么明显的操作需要离线一手。

大体思路是这样，实现其实也不难。

## 细节：

可以说卡空间就挺恶劣。

当然可能是我的线段树太过于恶臭或者说 rp 不够。

如果用结构体写线段树，千万不要把左右端点也记录到结构体中。

若是开 ll 的人，千万不要用 ll 定义变量，一定要在操作时强行转成 ll。

这边我连强转 ll 都搞不清楚，还是 [flysnow](https://www.luogu.com.cn/user/238445) 大佬帮忙的，在此膜拜和感谢一手。

## 代码：

```cpp
#include <iostream>
#include <cstring>
#include <cstdio>

const int N = 5e5 + 7;
const int M = 1e5 + 7;
const int mod = 19260817;

using namespace std;

int n, m;

int pos[N];

struct node {
	int op, l, r;
	int x;
} a[M];

struct SegmentTree {
	int mul, add;
	int sum;
} tree[N << 2 | 1][2];

struct SeTr {
	inline void push_up(int dep, int i) {
		tree[dep][i].sum = 1ll * (tree[dep << 1][i].sum + tree[dep << 1 | 1][i].sum) % mod;
	}
	
	inline void push_down(int dep, int i, int l, int r) {
		int mid = l + r >> 1;
		
		if (tree[dep][i].mul != 1) {
			tree[dep << 1][i].mul = (1ll * tree[dep << 1][i].mul * 1ll * tree[dep][i].mul) % mod;
			tree[dep << 1][i].add = (1ll * tree[dep << 1][i].add * 1ll * tree[dep][i].mul) % mod;
			tree[dep << 1][i].sum = (1ll * tree[dep << 1][i].sum * 1ll * tree[dep][i].mul) % mod;
			
			tree[dep << 1 | 1][i].mul = (1ll * tree[dep << 1 | 1][i].mul * 1ll * tree[dep][i].mul) % mod;
			tree[dep << 1 | 1][i].add = (1ll * tree[dep << 1 | 1][i].add * 1ll * tree[dep][i].mul) % mod;
			tree[dep << 1 | 1][i].sum = (1ll * tree[dep << 1 | 1][i].sum * 1ll * tree[dep][i].mul) % mod;
			
			tree[dep][i].mul = 1; 
		}
		
		if (tree[dep][i].add) {
			tree[dep << 1][i].add = (1ll * (1ll * tree[dep << 1][i].add + 1ll * tree[dep][i].add)) % mod;
			tree[dep << 1][i].sum = (1ll * (1ll * tree[dep << 1][i].sum + 1ll * tree[dep][i].add * 1ll * (mid - l + 1))) % mod;
			
			tree[dep << 1 | 1][i].add = (1ll * (1ll * tree[dep << 1 | 1][i].add + 1ll * tree[dep][i].add)) % mod;
			tree[dep << 1 | 1][i].sum = (1ll * (1ll * tree[dep << 1 | 1][i].sum + 1ll * tree[dep][i].add * 1ll * (r - mid))) % mod;
			
			tree[dep][i].add = 0;
		}
		
		return ;
	}
	
	void build(int dep, int l, int r, int i) {
		tree[dep][i].mul = 1;
		
		if (l == r) {
			tree[dep][i].sum = (1ll * pos[l]) % mod;
			return ;
		}
		
		int mid = l + r >> 1;
		
		build(dep << 1, l, mid, i);
		build(dep << 1 | 1, mid + 1, r, i);
		
		push_up(dep, i);
	}
	
	void update_add(int dep, int x, int y, int val, int i, int l, int r) {
		if (x <= l && y >= r) {
			tree[dep][i].add = (1ll * (1ll * tree[dep][i].add + 1ll * val)) % mod;
			tree[dep][i].sum = (1ll * (1ll * tree[dep][i].sum + 1ll * (r - l + 1) * 1ll * val)) % mod;
			
			return ;
		}
		
		push_down(dep, i, l, r);
		
		int mid = l + r >> 1;
		
		if (x <= mid) update_add(dep << 1, x, y, val, i, l, mid);
		if (y > mid) update_add(dep << 1 | 1, x, y, val, i, mid + 1 ,r);
		
		push_up(dep, i);
	}
	
	void update_mul(int dep, int x, int y, int val, int i, int l, int r) {
		if (x <= l && y >= r) {
			tree[dep][i].mul = (1ll * tree[dep][i].mul * 1ll * val) % mod;
			tree[dep][i].sum = (1ll * tree[dep][i].sum * 1ll * val) % mod;
			tree[dep][i].add = (1ll * tree[dep][i].add * 1ll * val) % mod;
			
			return ;
		} 
		
		push_down(dep, i, l, r);
		
		int mid = l + r >> 1;
		
		if (x <= mid) update_mul(dep << 1, x, y, val, i, l, mid);
		if (y > mid) update_mul(dep << 1 | 1, x, y, val, i, mid + 1, r);
		
		push_up(dep, i);
	}
	
	int query(int dep, int x, int y, int i, int l, int r) {
		int res = 0;
		
		if (x <= l && y >= r)
			return (1ll * tree[dep][i].sum) % mod;
		
		push_down(dep, i, l, r);
		
		int mid = l + r >> 1;
		
		if (x <= mid) res = (1ll * (1ll * res + 1ll * query(dep << 1, x, y, i, l, mid))) % mod;
		if (y > mid) res = (1ll * (1ll * res + 1ll * query(dep << 1 | 1, x, y, i, mid + 1, r))) % mod;
		
		return res;
	}
} segment;


inline void work(int i, int cur) {
	if (a[i].op == 1)
		segment.update_add(1, a[i].l, a[i].r, a[i].x, cur, 1, n);
	if (a[i].op == 2)
		segment.update_mul(1, a[i].l, a[i].r, a[i].x, cur, 1, n);
	if (a[i].op == 3)
		printf("%lld\n", (1ll * segment.query(1, a[i].l, a[i].r, cur, 1, n))); 
}

int main() {
	scanf("%d %d", &n, &m);
	
	for (int i = 1; i <= n; i ++)
		scanf("%d", &pos[i]);
	
	segment.build(1, 1, n, 0);
	segment.build(1, 1, n, 1);
	
	for (int i = 1; i <= m; i ++) {
		scanf("%d", &a[i].op);
		
		if (a[i].op == 1 || a[i].op == 2)
			scanf("%d %d %d", &a[i].l, &a[i].r, &a[i].x);
		else if (a[i].op == 3)
			scanf("%d %d", &a[i].l, &a[i].r);
		else continue;
	}
	
	int cur = 0;
	
	for (int i = 1; i <= m; i ++) {
		if (a[i].op == 4) {
			cur ^= 1;
			
			for (int j = i - 1; j >= 1; j --) {
				if (a[j].op == 4) break;
				if (a[j].op == 3) continue;
				
				work(j, cur); 
			}
		} else work(i, cur);
	}
	
	return 0;
}
```

$Atlantis.$

---

