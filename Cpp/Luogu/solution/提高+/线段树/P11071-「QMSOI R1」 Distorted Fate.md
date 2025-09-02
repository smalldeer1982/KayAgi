# 「QMSOI R1」 Distorted Fate

## 题目背景

![](https://cdn.luogu.com.cn/upload/image_hosting/oeu0ft9d.png)
**O Fortuna velut luna statu variabilis……**

（图片来自 Phigros 曲绘，侵删。）

加强版 [T512613](https://www.luogu.com.cn/problem/T512613)。

## 题目描述

Geopelia 需要捕捉到一种特殊的，不同于黑洞的引力波。

第 $i$ 个引力波有着一个频率 $A_i$，而多个引力波会互相影响，叠加，形成一个频率更快的引力波。

具体的，对于一个长度为 $n$ 的序列 $A$，$A$ 中所有引力波叠加起来的频率 $f(A)$ 为：$\bigcup\limits_{i=1}^n A_i$。其中 $\bigcup$ 表示按位或。

现在，Geopelia 需要知道几段以同一引力波开始的区间的频率之和。

也就是说，Geopelia 要向你询问：
$$
\sum_{i=l}^rf(A[l,i])
$$
的值，其中 $A[l,r]$ 为 $A_l,A_{l+1},\cdots,A_{r-1},A_r$ 组成的序列。

但不幸的是，由于幽蓝边界的引力影响，某一个区间 $[l,r]$ 中所有引力波的频率可能会异或上一个值 $x$。

Geopelia 想实时更新她的数据，你可以帮帮她吗？

她知道引力波的频率可能很高，所以你只需要告诉她答案 $\bmod \ 2^{30}$ 的值就可以了。

## 形式化题意

给定一个长度为 $n$ 的数组 $A$，你需要完成以下 $q$ 次操作。

1. ```1 l r x``` 将 $A_i(l\le i\le r)$ 异或上 $x$。

2. ```2 l r``` 求：
$$(\sum_{i=l}^r\bigcup_{j=l}^i A_j) \bmod 2^{30}$$
其中 $\bigcup$ 表示按位或。

## 说明/提示

### 样例解释

对于第一组询问：此时 $A=\{1,2,3\}$，所以答案为 $1+1\cup 2+1\cup 2\cup 3=1+3+3=7$。

对于第二组询问：此时 $A=\{3,0,3\}$，所以答案为 $3+3\cup 0+3\cup 0\cup 3=3+3+3=9$。

### 数据范围
**本题使用 subtask 进行捆绑测试**，每个 subtask 的具体分值如下：

| 子任务 | $n$ | $q$ | 时间 | 空间 | 分值 |
| :----------: | :----------: | :----------: | :----------: | :----------: |:----------:|
| $0$ | $\le 100$ | $\le 100$ | $1s$ | $512MB$ | $20$ |
| $1$ | $\le 2\times 10^4$ | $\le 2\times 10^4$ | $1s$ | $512MB$ |$20$ |
| $2$ | $\le 2\times 10^5$ | $\le 2\times 10^5$ | $3s$ | $512MB$ |$20$ |
| $3$ | $\le 2\times 10^5$ | $\le 2\times 10^5$ | $3s$ | $\color{red}100MB$ |$40$ |

对于所有数据，满足 $0\le a_i,x< 2^{30}$，$1\le l\le r\le n$。

```
INITALIZING……
SCANING……
CONNECTING……__PhigrOS Client Login
TIME_OUT!
CONNECTING……__Unknown
SUCCESS!
————————
……九……鸟……
……鸠……！
……喂？
…听得到吗？
鸠?![SIGNAL LOST]
```

## 样例 #1

### 输入

```
3 3
1 2 3
2 1 3
1 1 2 2
2 1 3```

### 输出

```
7
9```

# 题解

## 作者：MornStar (赞：6)

## D.Distorted Fate 题解

出题人题解。

### Subtask 0(20 pts)
直接照着题目上的式子模拟就可以了，复杂度 $O(qn^2)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=200005,mod=(1<<30);
int n,q,a[N];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>n>>q;
	for(int i=1;i<=n;i++)	cin>>a[i];
	for(int i=1,opt,l,r,x;i<=q;i++){
		cin>>opt>>l>>r;
		if(opt==1){
			cin>>x;
			for(int j=l;j<=r;j++)	a[j]^=x;
		}else{
			long long ans=0;
			for(int j=l;j<=r;j++){
				int tmp=0;
				for(int k=l;k<=j;k++)	tmp|=a[k];
				ans=(ans+tmp)%mod;
			}
			cout<<ans<<"\n";
		}
	}
}
```


### Subtask 1(40 pts)

发现 $\sum_{i=l}^r\bigcap_{j=l}^i A_j$ 可以在求值的时候做前缀或，$O(n)$ 回答询问，时间复杂度 $O(qn)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=200005,mod=(1<<30);
int n,q,a[N];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>n>>q;
	for(int i=1;i<=n;i++)	cin>>a[i];
	for(int i=1,opt,l,r,x;i<=q;i++){
		cin>>opt>>l>>r;
		if(opt==1){
			cin>>x;
			for(int j=l;j<=r;j++)	a[j]^=x;
		}else{
			long long ans=0,tmp=0;
			for(int j=l;j<=r;j++){
				tmp|=a[j];
				ans=(ans+tmp)%mod;
			}
			cout<<ans<<"\n";
		}
	}
}
```
### Subtask 2(60 pts)

既然我们可以使用前缀或统计答案，说明在求和的右端点 $i$ 逐渐向右移的过程中，$\bigcap_{j=l}^i A_j$ 的的值在不断变大，而这种变化最多进行 $O(\log w)$ 次，因为一个数在二进制下最多只有 $O(\log w)$ 位为 $0$。

所以我们可以得到一个思路，找到答案改变的位置，这个可以很容易地使用线段树上二分做到。

考虑一个好写但时空复杂度不会变的思路，将每个数按二进制位拆开，开 $30$ 颗线段树分别维护每一位，这样，问题就转换成了寻找区间 $[l,r]$ 内的第一个 $1$。

从第一个 $1$ 的位置开始，直到 $r$ 这一段区间的长度乘上这一位的权值就是这一位的贡献。

线段树节点记录区间内 $1$ 的个数，以及异或标记，这个问题是容易在 $O(\log n)$ 的时间复杂度下解决的。

对每一位询问一次，需要询问 $O(\log w)$ 次，所以单次询问是 $O(\log n \log w)$ 的。

同理，单次修改也要对应修改每一位，时间复杂度也是 $O(\log n\log w)$ 的。

所以总的时间复杂度就是 $O(n\log n\log w)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5,C=30,mod=1<<30;
int n,q,a[N];
struct segment_tree{
	struct segment_tree_node{int num;bool tag;}t[N<<2];
	inline int ls(int x){return x<<1;}
	inline int rs(int x){return x<<1|1;}
	inline void f(int p,int l,int r){t[p].num=(r-l+1)-t[p].num,t[p].tag^=1;}
#define mid ((l+r)>>1)
	inline void push_down(int p,int l,int r){
		if(!t[p].tag)	return;
		f(ls(p),l,mid);
		f(rs(p),mid+1,r);
		t[p].tag=0;
	}
	inline void push_up(int x){t[x].num=t[ls(x)].num+t[rs(x)].num;}
	void build(int p,int l,int r){
		if(l==r)	return t[p].num=a[l]&1,void();
		else{
			build(ls(p),l,mid);
			build(rs(p),mid+1,r);
			push_up(p);
		}
	}
	void change(int p,int l,int r,int re_l,int re_r){
		if(re_l<=l&&r<=re_r)	return f(p,l,r);
		else{
			push_down(p,l,r);
			if(re_l<=mid)	change(ls(p),l,mid,re_l,re_r);
			if(mid<re_r)	change(rs(p),mid+1,r,re_l,re_r);
			push_up(p);
		}
	}
	int find(int p,int l,int r,int k){
		if(l==r)	return l;
		else{
			push_down(p,l,r);
			if(t[ls(p)].num>=k)	return find(ls(p),l,mid,k);
			else	return find(rs(p),mid+1,r,k-t[ls(p)].num);
		}
	}
	int query(int p,int l,int r,int re_l,int re_r){
		if(re_l<=l&&r<=re_r)	return t[p].num;
		else if(!(r<re_l||l>re_r))	return push_down(p,l,r),query(ls(p),l,mid,re_l,re_r)+query(rs(p),mid+1,r,re_l,re_r);
		else	return 0;
	}
}T[30];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>n>>q;
	for(int i=1;i<=n;i++)	cin>>a[i];
	for(int i=0;i<C;i++){
		T[i].build(1,1,n+1);
		for(int j=1;j<=n;j++)	a[j]>>=1;
	}
	for(int i=1,opt,l,r,x;i<=q;i++){
		cin>>opt>>l>>r;
		if(opt==1){
			cin>>x;
			for(int j=0;j<C;j++){
				if(x&(1<<j))	T[j].change(1,1,n+1,l,r);
			}
		}else{
			long long ans=0;
			for(int j=0;j<C;j++){
				int num=T[j].query(1,1,n+1,1,l-1),pos=T[j].find(1,1,n+1,num+1);
				ans=(ans+(1ll<<j)*(r-min(r+1,pos)+1ll))%mod;
			}
			cout<<ans<<"\n";
		}
	}
}
```
### Subtask 3(100pts)

Subtask 2 的做法在时间上已经足够优秀了，但是在空间上却不能满足要求。

考虑如何优化。

发现对于一个区间，我们并不关心其中 $1$ 的数量，只需要知道区间里是否有 $1$ 就行了。

我们可以在线段树节点中分别记录区间中这一位或起来的值 $x$ 和与起来的值 $y$。

考虑异或对区间带来的影响。

1. 当且仅当 $x=y=1$，区间内全是 $1$，这时，区间异或会使 $x$ 和 $y$ 均变为 $0$。
2. 当且仅当 $x=y=0$，区间内全是 $0$，这时，区间异或会使 $x$ 和 $y$ 均变为 $1$。
3. 否则，异或不会改变 $x$ 和 $y$ 的取值。

区间内有 $1$ 等价于 $x=1$。

这时候，我们就可以顺利进行修改和查询操作了。

这样就可以在线段树上二分了……吗？

考虑一个问题：为什么一定要在线段树中记录 $1$ 的个数呢？

因为这个条件可以具有可差分性，所以可以用线段树上二分求解。

而我们维护的这个信息很明显没有可差分性，那应该怎么办呢？

考虑修改一下线段树上二分的步骤。

在线段树上查询区间 $[l,r]$ 时，将这个区间分成 $O(\log n)$ 段（类似于区间查询）。

按从左往右的顺序遍历每个段，这个可以在线段树上先遍历左子树，后遍历右子树实现，若遍历到这个段时，若区间里没有 $1$ 就直接返回。

否则就在这个区间里线段树上二分找到答案，然后不再遍历后面的区间，因为这个区间内线段树节点维护的信息与询问区间以外的部分无关，所以这时就不需要维护的数据满足可差分性了。

考虑时间复杂度，线段树上查询将区间分为 $O(\log n)$ 段是正常线段树区间查询的 $O(\log n)$，线段树上二分是 $O(\log n)$，但由于上面所说的剪枝，线段树的上二分的步骤实际只执行了一次，所以一次这样的操作总复杂度仍然是 $O(\log n)$。

于是将线段树节点内存储的一个整型变量优化成了两个布尔变量，可以顺利通过 Subtask 3。

时间复杂度仍然是 $O(n\log n\log w)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5,C=30,mod=1<<30;
int n,q,a[N];
struct segment_tree{
	struct segment_tree_node{bool x,y,tag;}t[N<<2];
	inline int ls(int x){return x<<1;}
	inline int rs(int x){return x<<1|1;}
	inline void f(int p){
		if(t[p].x==t[p].y)	t[p].x^=1,t[p].y^=1;
		t[p].tag^=1;
	}
#define mid ((l+r)>>1)
	inline void push_down(int p){
		if(!t[p].tag)	return;
		f(ls(p)),f(rs(p));
		t[p].tag=0;
	}
	inline void push_up(int p){
		t[p].x=t[ls(p)].x|t[rs(p)].x;
		t[p].y=t[ls(p)].y&t[rs(p)].y;
	}
	void build(int p,int l,int r){
		if(l==r)	return t[p].x=t[p].y=a[l]&1,void();
		else{
			build(ls(p),l,mid);
			build(rs(p),mid+1,r);
			push_up(p);
		}
	}
	void change(int p,int l,int r,int re_l,int re_r){
		if(re_l<=l&&r<=re_r)	return f(p);
		else{
			push_down(p);
			if(re_l<=mid)	change(ls(p),l,mid,re_l,re_r);
			if(mid<re_r)	change(rs(p),mid+1,r,re_l,re_r);
			push_up(p);
		}
	}
	int find(int p,int l,int r){
		if(l==r)	return l;
		else{
			push_down(p);
			if(t[ls(p)].x)	return find(ls(p),l,mid);
			else	return find(rs(p),mid+1,r);
		}
	}
	int query(int p,int l,int r,int re_l,int re_r){
		if(re_l<=l&&r<=re_r){
			if(t[p].x)	return find(p,l,r);
			else	return -1;
		}else if(!(r<re_l||l>re_r)){
			push_down(p);
			int ansl=query(ls(p),l,mid,re_l,re_r);
			if(ansl!=-1)	return ansl;
			else	return query(rs(p),mid+1,r,re_l,re_r);
		}else	return -1;
	}
}T[30];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>n>>q;
	for(int i=1;i<=n;i++)	cin>>a[i];
	for(int i=0;i<C;i++){
		T[i].build(1,1,n+1);
		for(int j=1;j<=n;j++)	a[j]>>=1;
	}
	for(int i=1,opt,l,r,x;i<=q;i++){
		cin>>opt>>l>>r;
		if(opt==1){
			cin>>x;
			for(int j=0;j<C;j++){
				if(x&(1<<j))	T[j].change(1,1,n+1,l,r);
			}
		}else{
			long long ans=0;
			for(int j=0;j<C;j++){
				int pos=T[j].query(1,1,n+1,l,r);
				if(pos!=-1)	ans=(ans+(1ll<<j)*(r-min(r+1,pos)+1ll))%mod;
			}
			cout<<ans<<"\n";
		}
	}
}
```

---

## 作者：Lyrella (赞：4)

# 简要题意

现有一长度为 $n$ 的数组 $A$，支持以下两种操作：

1. `1 l r x` 将 $A_i(l\le i \le r)$ 异或上 $x$；
2. `1 l r` 求：

$$\sum^{r}_{i=l}\bigcup^{i}_{j=l}A_j\bmod2^{30}$$

其中 $\bigcup$ 表示按位或。

# 题解
首先看到按位操作可以想到拆位，但是你会发现此题内存限制极小，所以考虑每一位先分别计算答案，并将相同的数组重复使用。

观察式子可以发现：对于每次询问的区间 $[l,r]$，如果第 $i$ 个数当前位已经为一，因为第二层是前缀或，所以后面的值全部为二的幂次。

所以可以将题目转化成维护区间内第一个一出现位置，我们可以用 $s0,s1$ 分别表示区间内是否有 $0/1$，用线段树维护，遇到操作一就打标记即可。

查询时我们可以先正常找出目标区间，然后再在目标区间里进行二分，所以时间按复杂度为 $O(n\log^2n)$。

# 代码
```cpp
int n, m, a[N];
struct qarray{
    int op, l, r, x; ll ans;
}q[N];
bool b[N], s0[N << 2], s1[N << 2], tg[N << 2];

#define ls x << 1
#define rs x << 1 | 1
void upd(int x){
    s0[x] = s0[ls] | s0[rs];
    s1[x] = s1[ls] | s1[rs];
}

void build(int x, int l, int r){
    tg[x] = 0;
    if(l == r)return(void)(s0[x] = b[l] ^ 1, s1[x] = b[l]);
    int mid = l + r >> 1;
    build(ls, l, mid), build(rs, mid + 1, r);
    upd(x);
}
void pd(int x){
    if(! tg[x])return ;
    tg[ls] ^= 1, tg[rs] ^= 1;
    swap(s0[ls], s1[ls]);
    swap(s0[rs], s1[rs]);
    tg[x] = 0;
}
void mdf(int x, int l, int r, int ql, int qr){
    if(ql <= l and r <= qr)return(void)(swap(s0[x], s1[x]), tg[x] ^= 1);
    int mid = l + r >> 1; pd(x);
    if(ql <= mid)mdf(ls, l, mid, ql, qr);
    if(mid < qr)mdf(rs, mid + 1, r, ql, qr);
    upd(x);
}

int nkp;
bool op;

int fd(int x, int l, int r){
    if(l == r)return s1[x] ? l : - 1; pd(x); if(! s1[x])return - 1; int mid = l + r >> 1;
    if(s1[ls])return fd(ls, l, mid);
    else return fd(rs, mid + 1, r);
}

void qry(int x, int l, int r, int ql, int qr){
    if(op)return ;
    if(ql <= l and r <= qr){
        int res = fd(x, l, r);
        if(~ res)nkp = res, op = true;
        return;
    }
    int mid = l + r >> 1; pd(x);
    if(ql <= mid)qry(ls, l, mid, ql, qr);
    if(op)return ;
    if(mid < qr)qry(rs, mid + 1, r, ql, qr);
}
const int p = 1073741824;

signed main(){
    n = rd(), m = rd();
    for(int i = 1; i <= n; ++i)a[i] = rd();
    for(int i = 1; i <= m; ++i){
        int x = rd(), l = rd(), r = rd(), y;
        q[i] = {x, l, r};
        if(x == 1)q[i].x = rd();
    }
    for(int bit = 0; bit < 31; ++bit){
        for(int i = 1; i <= n; ++i)b[i] = a[i] >> bit & 1;
        build(1, 1, n);
        for(int i = 1; i <= m; ++i)if(q[i].op == 1){
            int x = q[i].x >> bit & 1;
            if(! x)continue; mdf(1, 1, n, q[i].l, q[i].r);
        }else{
            op = false, nkp = q[i].r + 1; qry(1, 1, n, q[i].l, q[i].r);
            q[i].ans += 1ll * (q[i].r - nkp + 1) * (1ll << bit) % p;
            q[i].ans %= p;
        }
    }
    for(int i = 1; i <= m; ++i)if(q[i].op ^ 1)printf("%lld\n", q[i].ans);
    return 0;
}
```

---

## 作者：快乐的大童 (赞：4)

介绍一种好想、在线、空间小、跑的还挺快的做法（？）

---

先暂时不考虑修改，只考虑怎么快速求解询问。

询问相当于区间内前缀按位或的和。根据按位或的性质，当区间内某个值在某一位下是 $1$，那么所有包含这个值的前缀的按位或结果在该位下都为 $1$。

考虑拆位，单独考虑每一位对答案的贡献，设 $w$ 是当前枚举的二进制位，$[l,r]$ 内从左往右第一个在该位下为 $1$ 的数的下标为 $p$，则这一位的贡献为 $2^w\times(r-p+1)$。我们只需要用一个数据结构快速查询区间内第一个某一位为 $p$，考虑到我们还有修改，我们选择用线段树维护，开 $O(\log V)$ 棵线段树，每个节点维护第一个 `0` 和第一个 `1` 的出现位置。时间复杂度 $O(n\log n\log V)$，空间复杂度 $O(n\log V)$，精细实现应该可以过题。

---

感觉开 $O(\log V)$ 棵线段树有点太浪费了，能不能只开一棵呢？

可以！

线段树维护区间按位或值，先考虑查询，将询问区间划分成 $O(\log n)$ 段，因为我们只需要知道每一位第一次出现的位置在哪里，所以处理某个区间时，设前面的区间按位或值是 $v$，对于这个区间，我们只需要考虑 $v$ 为 $0$ 的那些二进制位即可。如果没有，直接退出。

将询问区间划分好了之后，每个区间内部的处理和上面是一样的：当递归右子树时，求出左子树的按位或值，仍设其为 $v$，那么在右子树中只需要考虑 $v$ 为 $0$ 的二进制位即可，如果没有就退出。

分析时间复杂度。由于只有对答案的某几个位有贡献的那些链会一直往下递归到叶子，而这些从根走向叶子的链至多只有 $O(\log V)$ 条，每条这样的链的深度为 $O(\log n)$，故时间复杂度 $O(n\log n\log V)$。

---

接着考虑修改。众所周知，对区间异或 $x$ 后最终的区间按位或值不等于最初的按位或值异或 $x$。不难发现，对于某一位，当区间内的所有数在这一位上不全为 $1$，这个方法会出错。考虑再维护一个区间按位与值，那么出问题的数位在区间按位与值中为 $0$。将异或 $x$ 后的区间按位或值**或**上（不能异或）区间按位与值在模 $2^{30}$ 次方意义下按位取反后的值，得到的就是正确的区间 位或值。区间按位与的维护同理。

---

至此这道题就做完了，时间复杂度 $O(n\log n\log V)$，由于我们只需要维护懒标记以及区间按位或和按位与的值，所以空间复杂度为 $O(n)$。但注意到这 $\log V$ 条从根到叶子的链是会有很大一部分重复的，所以这两个 $\log$ 严重跑不满。实际运行效率也确实很高。

代码：https://www.luogu.com.cn/paste/1cfl00lm

---

## 作者：AKPC (赞：3)

这是一篇**分块**题解，因为线段树的空间我卡不过去，我不会太多玄学科技。

因为是位运算，我们可以考虑一个经典 trick，即拆位去处理这些位，变成 $32$ 个 $0/1$ 序列。

这样做的话，异或相当于区间 $0/1$ 取反，打标记即可处理。

而对于查询，可以考虑拆贡献。注意到对于二进制从右往左第 $i$ 位，第一个 $1$ 出现的位置 $t$ 才有 $2^{i-1}(r-t+1)$ 的贡献。我们只需要求出 $t$ 就不难，不考虑空间的话，线段树做法显然。

但是这个题，以及其加强版空间很难崩，导致线段树很难搞，而本题时间有 $3$ 秒，所以可以考虑**时间较劣，但空间较优**的方式，也就是**分块**。

具体地，可以维护每个块 $0/1$ 第一个出现的位置，然后修改还是整块标记散块暴力，查询散块暴力整块对标记取 $\min$ 即可。

时间复杂度 $\Theta(n\sqrt n\log V)$，空间复杂度 $\Theta(n+\sqrt n\log V)$。事实上也没有比线段树慢多少，而且空间小得很。

这同样能通过加强版，给出加强版[代码](https://www.luogu.com.cn/paste/ig6h44q9)。

---

## 作者：lzyqwq (赞：3)

奇异幽默搞笑题。CSP-S 出这个我得乐开花了。

> - 维护一个序列，支持区间异或一个数、查询区间所有前缀或的和。
> - $n,q\le 2\times 10^5$，值域 $V = [0,2^{30})$。
> - $\text{3 s / }\bf \red{75\space MB}$。

考虑每一位 $w$ 的贡献，找到她在区间中最左边出现的位置 $p$，则终点位于 $p$ 及其右边的所有前缀的这一位上均为 $1$，剩余的为 $0$。那么这一位的贡献就是 $2^w\times(r-p+1)$。

考虑线段树，维护区间内每一位 $w$ 为 $0/1$ 出现的最左边位置 $L_{0/1,w}$（为 $0$ 表示不存在这一位）。合并的时候考虑左儿子中是否有这一位，有就选择左儿子中这一位最左边的位置，否则选择右儿子的。

考虑怎样修改，异或对于每一位而言就是不变或 $0/1$ 取反。枚举要异或的数的每一位，如果她为 $0$ 则这一位信息不用变，否则 $0/1$ 信息互换。维护区间异或懒标记即可。代码里写的标记永久化。

如果到这里就结束未免太容易了。这个做法的空间是 $\mathcal{O}(n\log |V|)$ 的，但是线段树自带 $4$ 倍常数、$L$ 带 $2$ 倍常数，无法通过本题。

但是可以动态开点啊，这样线段树空间只带二倍常数了，而存储左右孩子编号的数组不带 $\log |V|$ 就不考虑了。没实现过，估计能压线过。

更优雅的方式是查理线段树。即，对于一个结点 $(x,l,r)$，$m=\left\lfloor\dfrac{l+r}{2}\right\rfloor$，令其左孩子编号为 $2m$，右孩子编号为 $2m+1$ 即可。容易证明任意两个不同的区间对应的结点编号都是不同的。

[这样已经可以压线空间通过本题了。](https://www.luogu.com.cn/record/177284148)但是无法通过加强版。

我们发现空间的大头在于 $L$ 数组，而 $L$ 数组中的信息显然是 $\le n$ 的，就是说她们的二进制位数最多为 $18$。考虑将 $L$ 数组中相邻三个下标的 `int` 数压进一个 `long long` 里面，这样实际只占用两个 `int` 的空间。就可以通过加强版了。时间复杂度为 $\mathcal{O}(n\log n\log |V|)$。

代码：


```cpp
#include <bits/stdc++.h>
#define ll long long
template<class T> void read(T &x) {
    x = 0; T f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -1;
    for (; isdigit(c); c = getchar()) x = (x << 3) + (x << 1) + c - 48; x *= f;
}
template<class T> void write(T x) {
    if (x > 9) write(x / 10); putchar(x % 10 + 48);
}
template<class T> void print(T x, char ed = '\n') {
    if (x < 0) putchar('-'), x = -x; write(x), putchar(ed);
}
using namespace std; const int N = 200005, V = 30, K = 10; 
const ll A[] = {0x3ffffffffc0000, 0x3ffff00003ffff, 0xfffffffff}; int n, q, a[N];
struct smallarr {
    ll a[K]; smallarr() { memset(a, 0, sizeof a); }
    int qry(int x) {
        return a[x / 3] >> (18 * (x % 3)) & ((1ll << 18) - 1);
    }
    void mdf(int x, int v) {
        a[x / 3] &= A[x % 3]; a[x / 3] |= (1ll * v) << ((x % 3) * 18);
    }
};
struct node { smallarr l0, l1; };
node operator+(node u, node v) {
    node ret;
    for (int i = 0; i < V; ++i)
        ret.l0.mdf(i, u.l0.qry(i) ? u.l0.qry(i) : v.l0.qry(i)),
        ret.l1.mdf(i, u.l1.qry(i) ? u.l1.qry(i) : v.l1.qry(i));
    return ret;
}
struct SGT {
    node s[N << 1]; int tg[N << 1];
    int ls(int x) { return x << 1; } int rs(int x) { return x << 1 | 1; }
    void build(int x, int l, int r) {
        if (l == r) {
            for (int i = 0; i < V; ++i)
                if (a[l] >> i & 1) s[x].l1.mdf(i, l); else s[x].l0.mdf(i, l);
            return;
        }
        int m = l + r >> 1; build(ls(m), l, m); build(rs(m), m + 1, r);
        s[x] = s[ls(m)] + s[rs(m)];
    }
    void mdf(int x, int l, int r, int ql, int qr, int v) {
        if (ql <= l && r <= qr) {
            tg[x] ^= v;
            for (int i = 0, a, b; i < V; ++i)
                if (v >> i & 1)
                    a = s[x].l1.qry(i), b = s[x].l0.qry(i),
                    s[x].l1.mdf(i, b), s[x].l0.mdf(i, a);
            return;
        }
        int m = l + r >> 1;
        if (ql <= m) mdf(ls(m), l, m, ql, qr, v);
        if (qr > m) mdf(rs(m), m + 1, r, ql, qr, v); s[x] = s[ls(m)] + s[rs(m)];
        for (int i = 0, a, b; i < V; ++i)
            if (tg[x] >> i & 1)
                a = s[x].l1.qry(i), b = s[x].l0.qry(i),
                s[x].l1.mdf(i, b), s[x].l0.mdf(i, a);
    }
    node qry(int x, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return s[x]; int m = l + r >> 1; node ret;
        if (qr <= m) ret = qry(ls(m), l, m, ql, qr);
        else if (ql > m) ret = qry(rs(m), m + 1, r, ql, qr);
        else ret = qry(ls(m), l, m, ql, qr) + qry(rs(m), m + 1, r, ql, qr);
        for (int i = 0, a, b; i < V; ++i)
            if (tg[x] >> i & 1)
                a = ret.l1.qry(i), b = ret.l0.qry(i),
                ret.l1.mdf(i, b), ret.l0.mdf(i, a);
        return ret;
    }
} tr;
signed main() {
    read(n); read(q); for (int i = 1; i <= n; ++i) read(a[i]); tr.build(1, 1, n);
    for (int op, l, r, x, la = 0; q--;) {
        read(op); read(l); read(r);
        l = (l ^ la) % n + 1; r = (r ^ la) % n + 1; if (l > r) swap(l, r);
        if (op & 1) read(x), tr.mdf(1, 1, n, l, r, x);
        else {
            node t = tr.qry(1, 1, n, l, r); ll ans = 0;
            for (int i = 0; i < V; ++i)
                if (t.l1.qry(i)) ans += (1ll << i) * (r - t.l1.qry(i) + 1);
            print(la = (ans & ((1ll << V) - 1)));
        }
    }
    return 0;
}
```

---

## 作者：可爱的小棉羊 (赞：2)

一眼秒了。

考虑拆位，

对于每一位，每个询问，我们需要知道这个区间内最前面的一个为 $1$ 的位置，而修改相当于区间反转，然后线段树显然维护。

好的，你就会因为 $O(n\log n)$ 的空间炸掉。

相信大家做过一些分块题吧，然后有个 trick，沿用到这个题上，离线后，每位分别考虑答案的贡献，每次重新清空线段树（tag 要清空！！）。

然后我们就以 $O(n \log n\log W)$ 过掉了这个题。

代码如下：


```
#include<bits/stdc++.h>
using namespace std;
struct quer{
	int opt,l,r,x;
}qu[200005];
struct node{
	int l,r;
	int fz,fo;
	bool tag;
}v[8000005];
long long ans[200005],a[200005];
long long fw[31],n,q;
void push_up(int rt){
	if(v[rt<<1].fo!=0x3f3f3f3f)v[rt].fo=v[rt<<1].fo;
	else if(v[rt<<1|1].fo!=0x3f3f3f3f)v[rt].fo=v[rt<<1|1].fo+v[rt<<1].r-v[rt<<1].l+1;
	else v[rt].fo=0x3f3f3f3f;
	if(v[rt<<1].fz!=0x3f3f3f3f)v[rt].fz=v[rt<<1].fz;
	else if(v[rt<<1|1].fz!=0x3f3f3f3f)v[rt].fz=v[rt<<1|1].fz+v[rt<<1].r-v[rt<<1].l+1;
	else v[rt].fz=0x3f3f3f3f;
}
//r-pos+1
//(r-pos+1+1)(r-pos+1)/2
//l,r r
void push_tag(int rt){
	v[rt].tag^=1;
	swap(v[rt].fz,v[rt].fo);
}
void push_down(int rt){
	if(v[rt].tag==0)return;
	push_tag(rt<<1);
	push_tag(rt<<1|1);
	v[rt].tag=0;
}
void build(int rt,int l,int r,int bit){
	v[rt].l=l;
	v[rt].r=r;
	v[rt].tag=0;
//	cout<<rt<<" "<<l<<" "<<r<<"\n";
	if(l==r){
//		cout<<a[l]<<" "<<(1<<bit)<<"\n";
		v[rt].fz=0x3f3f3f3f;
		v[rt].fo=0x3f3f3f3f;
		
		if(a[l]&(1<<bit))v[rt].fo=1;
		else v[rt].fz=1;
		return;
	}
	int mid=(l+r)>>1;
	build(rt<<1,l,mid,bit);
	build(rt<<1|1,mid+1,r,bit);
	push_up(rt);
}
void add(int rt,int l,int r){
	if(l<=v[rt].l&&v[rt].r<=r){
		push_tag(rt);
		return;
	}
	push_down(rt);
	int mid=(v[rt].l+v[rt].r)>>1;
	if(l<=mid)add(rt<<1,l,r);
	if(r>=mid+1)add(rt<<1|1,l,r);
	push_up(rt);
}
/*
3 4
1 0 1
2 1 3
1 1 3 1
2 2 2
2 2 3
*/
int  query(int rt,int l,int r){
//	cout<<rt<<":";
	if(l<=v[rt].l&&v[rt].r<=r){
//		cout<<v[rt].l<<" "<<v[rt].r<<" "<<v[rt].fo+v[rt].l-l<<"\n";
		return min(v[rt].fo+(v[rt].l-l),0x3f3f3f3f);
	}
	push_down(rt);
	int mid=(v[rt].l+v[rt].r)>>1;
	int ans=0x3f3f3f3f;
	if(l<=mid)ans=query(rt<<1,l,r);
	if(r>=mid+1)ans=min(ans,query(rt<<1|1,l,r));
	return min(ans,0x3f3f3f3f);
}
int main(){
	fw[0]=1;
	for(int i=1;i<=30;i++)fw[i]=fw[i-1]*2;
	cin>>n>>q;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=q;i++){
		cin>>qu[i].opt>>qu[i].l>>qu[i].r;
		if(qu[i].opt==1){
			cin>>qu[i].x;
			ans[i]=-1;
		}
	}
	//01 10 11
	//
	//11 00 11
	for(int W=0;W<=29;W++){
//		cout<<W<<":\n";
		build(1,1,n,W);
//		for(int i=1;i<=20;i++){
////			cout<<i<<" "<<v[i].l<<" "<<v[i].r<<" "<<v[i].fo<<"\n";
//		}
		for(int i=1;i<=q;i++){
			int l=qu[i].l,r=qu[i].r;
			if(qu[i].opt==1){
				if(qu[i].x&(1<<W))add(1,l,r);
			}else{
				long long sum=query(1,l,r),len=r-l+1;
				if(sum==0x3f3f3f3f)continue;
//				cout<<sum<<"\n";
				//3-2+1
				//6
				ans[i]=(ans[i]+(len-sum+1)%fw[30]*(1<<W)%fw[30])%fw[30];
			}
		}
	}
	for(int i=1;i<=q;i++){
		if(ans[i]==-1)continue;
		cout<<ans[i]<<"\n";
	}
}

```

---

## 作者：_7thRC_CB_CRP_ (赞：1)

首先这道题是关于区间修改区间查询的题目，一般对于这种二进制相关题目，且可以拆开二进制的，我们一般离线下来一位一位处理，求贡献。

那么在注意到，这道题的修改是亦或，老套路，维护两颗线段树，修改就交换再合并上去。

然后呢，我们最后考虑线段树维护什么值。由于是前缀区间求或那么我们自然地可以想到看第一个该位为 $1$ 的值，这个位置才会对答案造成影响。

所以由此就可以写出代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
ll n, q;
bool tag[3000001];
ll tr[2][3000001];
ll pw[31];
void push(ll i) {
	if (tag[i]) {
		swap(tr[0][i << 1], tr[1][i << 1]);
		swap(tr[0][i << 1 | 1], tr[1][i << 1 | 1]);
		tag[i << 1] ^= 1;
		tag[i << 1 | 1] ^= 1;
		tag[i] = 0;
	}
}
void add(ll i, ll l, ll r, ll x, ll y) {
	if (tag[i]) {
		swap(tr[0][i << 1], tr[1][i << 1]);
		swap(tr[0][i << 1 | 1], tr[1][i << 1 | 1]);
		tag[i << 1] ^= 1;
		tag[i << 1 | 1] ^= 1;
		tag[i] = 0;
	}
	if (x <= l && r <= y) {
		tag[i] ^= 1;
		swap(tr[0][i], tr[1][i]);
		return;
	}
	ll mid = (l + r) >> 1;
	if (x >= mid + 1)
		add(i << 1 | 1, mid + 1, r, x, y), push(i << 1);
	else if (y <= mid)
		add(i << 1, l, mid, x, y), push(i << 1 | 1);
	else
		add(i << 1 | 1, mid + 1, r, x, y), add(i << 1, l, mid, x, y);
	tr[0][i] = min(tr[0][i << 1], tr[0][i << 1 | 1]);
	tr[1][i] = min(tr[1][i << 1], tr[1][i << 1 | 1]);
}
ll ans(ll i, ll l, ll r, ll x, ll y) {
	push(i);
	if (x <= l && r <= y)
		return tr[1][i];
	ll mid = (l + r) >> 1;
	if (x >= mid + 1)
		return ans(i << 1 | 1, mid + 1, r, x, y);
	else if (y <= mid)
		return ans(i << 1, l, mid, x, y);
	else
		return min(ans(i << 1 | 1, mid + 1, r, x, y), ans(i << 1, l, mid, x, y));
}
void build(ll i, ll l, ll r) {
	if (l == r) {
		tr[0][i] = l, tr[1][i] = INT_MAX;
		return;
	}
	ll mid = (l + r) >> 1;
	build(i * 2 + 1, mid + 1, r), build(i * 2, l, mid);
	tr[0][i] = min(tr[0][i << 1], tr[0][i << 1 | 1]);
	tr[1][i] = min(tr[1][i << 1], tr[1][i << 1 | 1]);
}
ll a[200001];
ll op[200001];
ll qu[200001], lll[200001], rrr[200001], dss[200001];
long long res[200001];
int main() {
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> n >> q;
	pw[0] = 1;
	for (ll i = 1; i <= 30; i++)
		pw[i] = pw[i - 1] << 1;
	for (ll i = 1; i <= n; i++)
		cin >> a[i];
	for (ll i = 1; i <= q; i++) {
		cin >> op[i] >> lll[i] >> rrr[i];
		if (op[i] == 1)
			cin >> dss[i];
	}
	for (ll i = 0; i <= 29; i++) {
		memset(tag, 0, sizeof tag);
		build(1, 1, n);
		for (ll j = 1; j <= n; j++)
			if ((1 << i)&a[j])
				add(1, 1, n, j, j);
		for (ll j = 1; j <= q; j++) {
			if (op[j] == 1) {
				if (dss[j] & (1 << i))
					add(1, 1, n, lll[j], rrr[j]);
			} else {
				ll d = ans(1, 1, n, lll[j], rrr[j]);
				if (d != INT_MAX)
					res[j] += (1ll * pw[i] * (rrr[j] - d + 1) % pw[30]);
				res[j] %= pw[30];
			}
		}
	}
	for (int i = 1; i <= q; i++)
		if (op[i] == 2)
			cout << res[i] << '\n';
	return 0;
}
```

---

## 作者：Super_Cube (赞：1)

# Solution

学弟公开赛的题，来写个题解。

题意是序列的区间异或，区间前缀或和。

考虑或运算的性质：单调不减，只要某个 bit 位前面存在一个 $1$，后面全都为 $1$。

那么实际上就是要找到区间中每一个 bit 位上第一次出现的 $1$ 的位置。

很容易想到用线段树来解决这道题。

区间异或就不说了，打个异或标记。二进制下第 $i$ 位找 $1$ 的过程可以先计算 $[1,l)$ 中 $1$ 的个数（记为 $x$），然后找第 $x+1$ 个 $1$ 的出现位置（记为 $y$），那么对答案的贡献就是 $\max(0,r-y+1)\cdot 2^{i}$。

就，结束了。

很好奇为什么赛前评估紫，以及总结帖中写道通过人数高于预期。

---

## 作者：cancan123456 (赞：0)

本来想着难度橙到紫，看看最后一题能拿几分暴力，没想到切了，故写题解，并提供一种不同于官方题解的压空间方式。

看到位运算，套路性地考虑拆位，注意到只需要找 $[l,r]$ 中第一个一的位置，设为 $x$，则 $[l,x)$ 的前缀或都是零，$[x,r]$ 的前缀或是一。

区间异或运算对应到位上就是区间翻转，所以我们需要写一个数据结构维护零一序列，需要支持区间翻转，找一后第一个一的位置，只需要每个节点维护一的数量，即可线段树二分解决，时间复杂度 $O(n\log n\log V)$，空间复杂度 $O(n\log V)$，[然后就拿到了四十分](https://www.luogu.com.cn/record/177300123)。

先把空间压下来，注意到每一位之间相互独立，而且没有强制在线，所以离线修改、询问，枚举每一位依次解决，这样就不需要开值域的以二为底数的对数个线段树，只需要一个线段树，时间复杂度不变但空间复杂度降为 $O(n)$，[然后就拿到了四十分](https://www.luogu.com.cn/record/177301721)。

稍微卡卡常，就能过了，以下是参考代码。

```cpp
#include <cstdio>
using namespace std;
typedef unsigned uint;
const int N = 200005;
struct Node {
	int l, r, len, w, tag;
};
int b[N];
Node node[4 * N];
void push_up(int p) {
	node[p].w = node[2 * p].w + node[2 * p + 1].w;
}
void push_tag(int p) {
	node[p].tag ^= 1;
	node[p].w = node[p].len - node[p].w;
}
void push_down(int p) {
	if (node[p].tag == 1) {
		push_tag(2 * p);
		push_tag(2 * p + 1);
		node[p].tag = 0;
	}
}
void build(int p, int l, int r) {
	node[p].l = l;
	node[p].r = r;
	node[p].len = r - l + 1;
	node[p].tag = 0;
	if (l == r) {
		node[p].w = b[l];
	} else {
		int mid = (l + r) / 2;
		build(2 * p, l, mid);
		build(2 * p + 1, mid + 1, r);
		push_up(p);
	}
}
void modify(int p, int l, int r) {
	if (l <= node[p].l && node[p].r <= r) {
		push_tag(p);
	} else {
		push_down(p);
		int mid = (node[p].l + node[p].r) / 2;
		if (l <= mid) {
			modify(2 * p, l, r);
		}
		if (mid + 1 <= r) {
			modify(2 * p + 1, l, r);
		}
		push_up(p);
	}
}
int ans0, ans1;
void query(int p, int l, int r) {
	if (l <= node[p].l && node[p].r <= r) {
		ans1 += node[p].w;
	} else {
		push_down(p);
		int mid = (node[p].l + node[p].r) / 2;
		if (r <= mid) {
			query(2 * p, l, r);
		} else if (mid + 1 <= l) {
			ans0 += node[2 * p].w;
			query(2 * p + 1, l, r);
		} else {
			query(2 * p, l, r);
			query(2 * p + 1, l, r);
		}
	}
}
int query(int p) {
	if (node[p].l == node[p].r) {
		return node[p].l;
	} else {
		push_down(p);
		if (node[2 * p].w > 0) {
			return query(2 * p);
		} else {
			return query(2 * p + 1);
		}
	}
}
int query_leftmost(int p, int l, int l_w) {
	if (node[p].l == node[p].r) {
		return node[p].l;
	} else {
		push_down(p);
		int mid = (node[p].l + node[p].r) / 2;
		if (l <= mid) {
			if (l_w < node[2 * p].w) {
				return query_leftmost(2 * p, l, l_w);
			} else {
				return query(2 * p + 1);
			}
		} else {
			return query_leftmost(2 * p + 1, l, l_w - node[2 * p].w);
		}
	}
}
uint a[N];
struct Query {
	int op, l, r;
	uint x;
} que[N];
int main() {
//	freopen("in.txt", "r", stdin);
	int n, q;
	scanf("%d %d", &n, &q);
	for (int i = 1; i <= n; i++) {
		scanf("%u", &a[i]);
	}
	for (int i = 1; i <= q; i++) {
		scanf("%d %d %d", &que[i].op, &que[i].l, &que[i].r);
		if (que[i].op == 1) {
			scanf("%u", &que[i].x);
		}
	}
	for (int bit = 0; bit < 30; bit++) {
		for (int i = 1; i <= n; i++) {
			b[i] = (a[i] >> bit) & 1;
		}
		build(1, 1, n);
		for (int i = 1; i <= q; i++) {
			if (que[i].op == 1) {
				if (((que[i].x >> bit) & 1) == 1) {
					modify(1, que[i].l, que[i].r);
				}
			} else {
				const int & l = que[i].l;
				const int & r = que[i].r;
				ans0 = ans1 = 0;
				query(1, l, r);
				if (ans1 > 0) {
					int lw = query_leftmost(1, l, ans0);
					uint len = r - lw + 1;
					que[i].x += len << bit;
				}
			}
		}
	}
	for (int i = 1; i <= q; i++) {
		if (que[i].op == 2) {
			printf("%u\n", que[i].x % (1 << 30));
		}
	}
	return 0;
}
```

---

## 作者：Usada_Pekora (赞：0)

区间 `xor` 上 $x$，询问区间的所有前缀的 `or` 的和。

直接维护不好弄，考虑拆位去做，于是 `xor` 只要对为 1 的位做区间翻转就好。容易发现对于某个位 $k$，前缀 `or` 值从第一个为 1 的位置开始就都是 1 了，把这个位置 $m$ 找出来，这一位询问的贡献就是 $2^k(r-m+1)$。

以上操作就是区间翻转，区间查询第一个 1 的位置，然后就做完了，复杂度 $O(n\log n\log v)$。

```cpp
#include <bits/stdc++.h>
#define pb emplace_back
#define mkp make_pair
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
template<typename T> inline bool chkmin(T &x, const T &y) {
	return (y < x) && (x = y, true);
}
template<typename T> inline bool chkmax(T &x, const T &y) {
	return (x < y) && (x = y, true);
}
constexpr int N = 2e5 + 5;
int n, q, val[N << 2], tag[N << 2], a[N];
unsigned int ans[N];
vector<tuple<int, int, int, int>> OP;
inline void build(int p, int l, int r, int lg) {
	tag[p] = 0;
	if (l == r) {
		val[p] = a[l] >> lg & 1;
		return;
	}
	int mid = (l + r) >> 1;
	build(p << 1, l, mid, lg), build(p << 1 | 1, mid + 1, r, lg);
	val[p] = val[p << 1] + val[p << 1 | 1];
}
inline void pushrev(int p, int l, int r) {
	tag[p] ^= 1;
	val[p] = r - l + 1 - val[p];
}
inline void pushdown(int p, int l, int r) {
	int mid = (l + r) >> 1;
	if (tag[p])
		pushrev(p << 1, l, mid), pushrev(p << 1 | 1, mid + 1, r);
	tag[p] = 0;
}
inline void modify(int p, int l, int r, int L, int R) {
	if (L <= l && r <= R) {
		pushrev(p, l, r);
		return;
	}
	int mid = (l + r) >> 1;
	pushdown(p, l, r);
	if (L <= mid)
		modify(p << 1, l, mid, L, R);
	if (R > mid)
		modify(p << 1 | 1, mid + 1, r, L, R);
	val[p] = val[p << 1] + val[p << 1 | 1];
}
inline int query(int p, int l, int r, int L, int R) {
	if (L > R)
		return 0;
	if (L <= l && r <= R)
		return val[p];
	int mid = (l + r) >> 1, res = 0;
	pushdown(p, l, r);
	if (L <= mid)
		res += query(p << 1, l, mid, L, R);
	if (R > mid)
		res += query(p << 1 | 1, mid + 1, r, L, R);
	return res;
}
inline int getpos(int p, int l, int r, int k) {
	if (l == r)
		return l;
	int mid = (l + r) >> 1, res = -1;
	pushdown(p, l, r);
	if (val[p << 1] > k)
		return getpos(p << 1, l, mid, k);
	return getpos(p << 1 | 1, mid + 1, r, k - val[p << 1]);
}
signed main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cin >> n >> q, OP.resize(q);
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	for (auto &[op, l, r, x] : OP) {
		cin >> op >> l >> r;
		if (op == 1)
			cin >> x;
	}
	for (int lg = 0, id = 0; lg < 30; lg++, id = 0) {
		build(1, 1, n, lg);
		for (auto &[op, l, r, x] : OP) {
			if (op == 1) {
				if (x >> lg & 1)
					modify(1, 1, n, l, r);
			} else {
				int s = query(1, 1, n, 1, l - 1), m = getpos(1, 1, n, s);
				id++;
				if (m > r || val[1] <= s)
					continue;
				ans[id] += (unsigned int)(r - m + 1) * (1 << lg);
			}
		}
	}
	for (int i = 0, id = 0; i < q; i++) {
		if (get<0>(OP[i]) == 2) 
			cout << (ans[++id] & ((1 << 30) - 1)) << '\n';
	}
	return 0;
}
```

---

## 作者：Eterna (赞：0)

###  序

与正解有些许差异，并不可以通过加强版。（赛时还没调出来）

### 60分思路

有各种二进制操作，模数也是 $2$ 的幂，可以想到将数拆成二进制，也就是 $30$ 棵线段树。

修改操作相当于在 $x$ 某位二进制为 $1$ 的情况区间取反。

询问可以发现在某一位二进制上总是一段 $0$ 加上一段 $1$。而它们之间的分界点就是第一个 $1$ 的下标。因为有取反，所以再维护第一个 $0$ 的下标可以实现快速修改。

```cpp
int lazy[N<<2]={0},f0[N<<2],f1[N<<2];
void pushup(int id)
{
	if(f0[id<<1]<=n)f0[id]=f0[id<<1];
	else f0[id]=f0[id<<1|1];
	if(f1[id<<1]<=n)f1[id]=f1[id<<1];
	else f1[id]=f1[id<<1|1];
}
void init(int id,int l,int r,int k)
{
	if(l==r)
	{
		f0[id]=f1[id]=INT_MAX; 
		if(a[l][k])f1[id]=l;
		else f0[id]=l;
		return;
	}		
	int mid=l+r>>1;
	init(id<<1,l,mid,k);
	init(id<<1|1,mid+1,r,k);
	pushup(id);
}
void pushdown(int id,int l,int r)
{
	if(lazy[id])
	{
		swap(f0[id<<1],f1[id<<1]);
		swap(f0[id<<1|1],f1[id<<1|1]);
		lazy[id<<1]^=1,lazy[id<<1|1]^=1;
		lazy[id]=0;
	}
}
void insert(int id,int l,int r,int x,int y)
{
	if(l>=x&&r<=y)
	{
		swap(f0[id],f1[id]);
		lazy[id]^=1;
		return;
	}
	pushdown(id,l,r);
	int mid=l+r>>1;
	if(x<=mid)insert(id<<1,l,mid,x,y);
	if(y>mid)insert(id<<1|1,mid+1,r,x,y);
	pushup(id);
}
int ask(int id,int l,int r,int x,int y)
{
	if(l>=x&&r<=y)return f1[id];
	pushdown(id,l,r);
	int mid=l+r>>1,ans=INT_MAX;
	if(x<=mid)ans=min(ans,ask(id<<1,l,mid,x,y));		
	if(y>mid)ans=min(ans,ask(id<<1|1,mid+1,r,x,y));
	return ans;
}
```

### 100分思路

刚刚的代码只是空间不够，在时间上没有问题，我们卡卡空间就行。

首先，我们可以一眼发现 `lazy` 始终是 $0$ 或 $1$，换成 `bool`。

然后，我们看到某区间第一个 $1$ 的下标，第一个 $0$ 的下标之中，总有一个在开头的位置。

我们换成维护区间第一个下标对应的数，与第一个下标对应的数不同的第一个数的下标。

因为第一个下标的数始终是 $0$ 或 $1$，所以可以换成 `bool`。

但是一交还是 MLE，果断换成 `bitset`，卡卡常，直接 ac。

~~其实调了很久。~~

#### 代码


```cpp
#include<bits/stdc++.h>
#define N 200005
#define rd read()
#define gc pa == pb && (pb = (pa = buf) + fread(buf, 1, 100000, stdin), pa == pb) ? EOF : *pa++
using namespace std;
const int mod=(1<<30);
static char buf[100000], * pa(buf), * pb(buf);
int m,n;
inline int read()
{
	register int x=0,s=gc;
	while(s<'0'||s>'9')s=gc;
	while(s>='0'&&s<='9')x=(x<<1)+(x<<3)+(s^48),s=gc;
	return x;
}
bitset<(N<<2)> lazy[30];
bitset<(N<<2)> fir[30];
bitset<30> ki;
int f1[30][N<<2];
inline void pushup(int id,int mid,int k)
{
	fir[k][id]=fir[k][id<<1];
	if(fir[k][id<<1]==fir[k][id<<1|1])f1[k][id]=min(f1[k][id<<1],f1[k][id<<1|1]);
	else f1[k][id]=min(f1[k][id<<1],-~mid);
}
inline void init(int id,int l,int r)
{
	if(l==r)
	{
		int x=rd;
		for(int i=0;i<30;++i,x>>=1)fir[i][id]=x&1,f1[i][id]=INT_MAX;
		return;
	}
	register int mid=l+r>>1;
	init(id<<1,l,mid);
	init(id<<1|1,mid+1,r);
	for(register int i=0;i^30;i=-~i)pushup(id,mid,i);
}
inline void pushdown(int id,int l,int r,int k)
{
	if(lazy[k][id])
	{
		fir[k][id<<1]=fir[k][id<<1]^1;
		fir[k][id<<1|1]=fir[k][id<<1|1]^1;
		lazy[k][id<<1]=lazy[k][id<<1]^1;
		lazy[k][id<<1|1]=lazy[k][id<<1|1]^1;
		lazy[k][id]=0;
	}
}
void insert(int id,int l,int r,int x,int y)
{
	if(l>=x&&r<=y)
	{
		for(register int i=0;i^30;i=-~i)
		{
			if(ki[i])
			{
				fir[i][id]=fir[i][id]^1;
				lazy[i][id]=lazy[i][id]^1;
			}
		}
		return;
	}
	for(int i=0;i<30;++i)if(ki[i])pushdown(id,l,r,i);
	register int mid=l+r>>1;
	if(x<=mid)insert(id<<1,l,mid,x,y);
	if(y>mid)insert(id<<1|1,mid+1,r,x,y);
	for(register int i=0;i<30;i=-~i)if(ki[i])pushup(id,mid,i);
}
struct nod
{
	int re[30];	
}ba;
nod mind(nod x,nod y)
{
	nod r;
	for(register int i=0;i^30;i=-~i)r.re[i]=min(x.re[i],y.re[i]);
	return r;
}	
nod ask(int id,int l,int r,int x,int y)
{
	if(l>=x&&r<=y)
	{
		for(register int i=0;i^30;i=-~i)
		{
			if(fir[i][id])ba.re[i]=l;
			else ba.re[i]=f1[i][id];
		}
		return ba;
	}
	for(register int i=0;i^30;i=-~i)pushdown(id,l,r,i);
	register int mid=l+r>>1;
	if(x<=mid&&y>mid)return mind(ask(id<<1,l,mid,x,y),ask(id<<1|1,-~mid,r,x,y));
	if(x<=mid)return ask(id<<1,l,mid,x,y);
	if(y>mid)return ask(id<<1|1,mid+1,r,x,y);
}
int k,op,l,r;
signed main()
{
	n=rd,m=rd;
	init(1,1,n);
	while(m--)
	{
		op=rd,l=rd,r=rd;
		if(op==1)
		{
			int i=0;k=rd;
			while(k)
			{
				ki[i++]=k&1;
				k>>=1;
			}
			for(;i^30;i=-~i)ki[i]=0;
			insert(1,1,n,l,r); 
		}
		else
		{
			long long ans=0,mul=1;
			nod pos=ask(1,1,n,l,r);
			for(register int i=0;i^29;i=-~i)
			{
				if(pos.re[i]<=r)ans+=(r-pos.re[i]+1)*mul;
				mul<<=1;ans%=mod;
			}
			printf("%lld\n",ans);
		}
	}
	return 0;
}
```

---

