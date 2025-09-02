# ADD DIV MAX RESTORE

## 题目描述

[problemUrl]: https://atcoder.jp/contests/jag2018summer-day2/tasks/jag2018summer_day2_i

You are given an integer sequence $ a_0,\ a_1,\ ...,\ a_{N-1} $.

You have to perform $ Q $ queries, each query is one of the following:

- `ADD QUERY(t=0 l r x)` : for each $ i $ between $ l $ and $ r $, inclusive, replace $ a_i $ with $ a_i\ +\ x $.
- `DIV QUERY(t=1 l r x)` : for each $ i $ between $ l $ and $ r $, inclusive, replace $ a_i $ with $ {\rm\ floor}(a_i\ /\ x) $, where $ {\rm\ floor}(y) $ is the biggest integer that is not greater than $ y $.
- `MAX QUERY(t=2 l r x=0)` : print $ {\rm\ max}(a_l,\ a_{l+1},\ ...,\ a_r) $.
- `RESTORE QUERY(t=3 l r x=0)` : for each $ i $ between $ l $ and $ r $, inclusive, set $ a_i $ to the initial value of $ a_i $, that is, the value given in the input.

## 说明/提示

### Constraints

- All input values are integers.
- $ 1\ \leq\ N,\ Q\ \leq\ 200,000 $
- $ 0\ \leq\ a_i\ \leq\ 10^8 $
- $ t_i\ =\ 0,\ 1,\ 2,\ 3 $
- $ 0\ \leq\ l_i\ \leq\ r_i\ \leq\ N-1 $
- $ 1\ \leq\ x_i\ \leq\ 1000 $(when $ t_i\ \neq\ 2,\ 3 $)

### Sample Explanation 1

\- $ {\rm\ max}(1,\ 2,\ 3,\ 4,\ 5)\ =\ 5 $ - $ 1,\ 2,\ 3,\ 4,\ 5\ →\ 11,\ 12,\ 3,\ 4,\ 5 $ - $ {\rm\ max}(11,\ 12,\ 3,\ 4,\ 5)\ =\ 12 $ - $ {\rm\ max}(3)\ =\ 3 $ - $ 11,\ 12,\ 3,\ 4,\ 5\ →\ 2,\ 3,\ 3,\ 4,\ 5 $ - $ {\rm\ max}(2)\ =\ 2 $ - $ {\rm\ max}(3)\ =\ 3 $ - The array is restored to $ 1,\ 2,\ 3,\ 4,\ 5 $ - $ {\rm\ max}(1,\ 2)\ =\ 2 $

## 样例 #1

### 输入

```
5 9
1 2 3 4 5
2 0 4 0
0 0 1 10
2 0 4 0
2 2 2 0
1 0 1 4
2 0 0 0
2 1 1 0
3 0 4 0
2 0 1 0```

### 输出

```
5
12
3
2
3
2```

## 样例 #2

### 输入

```
4 7
0 1 0 1
2 0 3 0
0 0 3 1
1 0 3 2
2 0 3 0
0 0 3 1
1 0 3 2
2 0 3 0```

### 输出

```
1
1
1```

## 样例 #3

### 输入

```
10 23
13 1 22 8 28 18 23 9 22 27
1 3 4 5
1 8 8 8
0 3 9 5
0 2 6 3
3 0 4 0
1 1 3 7
2 2 2 0
2 3 5 0
0 1 4 2
3 0 9 0
2 0 1 0
0 3 9 8
2 1 9 0
0 8 9 5
1 5 7 7
0 3 5 7
0 7 9 7
3 3 6 0
2 1 6 0
0 1 1 7
1 4 8 10
2 0 9 0
1 5 6 1```

### 输出

```
3
28
13
36
28
47```

# 题解

## 作者：harmis_yz (赞：3)

题解摘自[CSP2024 前做题情况](https://www.luogu.com.cn/article/3yyu431w)。

## 分析

很显然，有还原的题基本不能用势能分析做。

考虑线段树。

考虑换个方式维护。因为这题目有区间加法和区间除法。我们记录下来每次除法之后，得到的商、余数和除数。即：$c\times b+a=c'$。其中 $c$ 是商，也就是当前的值，$b$ 是除数，$a$ 是余数，$c'$ 是除法前的数也就是被除数。

那么，考虑一种映射：$f(x)=\lfloor\frac{a+x}{b}\rfloor+c$。对于每个数，我们都记录下来最近一次除法或加法后得到的商、余数和除数。那我们就可以快速得到当前这个数实际上的值了。及其分别为 $c,a,b$。

加法操作。直接就是在 $c$ 上面进行加法操作。

除法操作。假设该操作为区间除以 $w$。这里的 $x$ 并未改变，我们需要调整的只有该映射中的 $a,b,c$。所以有：$a'=(a+bc)\bmod bw,b'=bw,c'=\lfloor\frac{a+bc}{bw}\rfloor$。在这里，我们将 $\frac{a}{b}+c$ 写成了 $\frac{a+bc}{b}$，方便计算。然后除法操作就可以直接维护了。

还原操作。我们再维护一个 $rmax$，表示当前节点在最开始的区间 $max$ 值。那么一个还原操作就相当于将当前的 $max$ 值变成 $rmax$，并且清空其映射的参数。记录一个懒标记表示该节点的子树是否需要全部还原即可。

询问操作。直接就是正常的区间询问最大值，不再赘述。

该算法的时间复杂度为 $O(n\log n)$。有一个小细节，就是在我们维护的 $b$ 这个参数比 $3\times 10^8$ 大时，能够证明 $b$ 的增加是无效的。所以可以直接让 $b$ 成为其中一个能够被接受的值。不然可能会 RE 或者 WA。

## 代码

```cpp
struct node{
	int a,b,c;
	il void clear(){
		a=c=0,b=1;
		return ;
	}
	il void add(int x){
		c+=x;
		return ;
	}
	il void div(int x){
		int a_=a,b_=b,c_=c;
		a=(a_+b_*c_)%(b_*x);
		b=b_*x;
		c=(a_+b_*c_)/(b_*x);
		if(b>=inf){
			a=(a-b+inf);
			b=inf;
			a=max(a,0ll);
		}
		return ;
	} 
};
struct Tree{
	int l,r,mx,rmx;
	node tag1;
	int tag2;
}tr[N<<2];

il void up(int u){
	tr[u].mx=max(tr[ls(u)].mx,tr[rs(u)].mx);
	return ;
}
il void down(int u){
	if(tr[u].tag2){//reset
		tr[ls(u)].mx=tr[ls(u)].rmx,tr[rs(u)].mx=tr[rs(u)].rmx;
		tr[ls(u)].tag1.clear(),tr[rs(u)].tag1.clear();
		tr[ls(u)].tag2=1,tr[rs(u)].tag2=1;
		tr[u].tag2=0;
	}
	if(tr[u].tag1.a){
		tr[ls(u)].tag1.add(tr[u].tag1.a),
		tr[rs(u)].tag1.add(tr[u].tag1.a);
		tr[ls(u)].mx+=tr[u].tag1.a,
		tr[rs(u)].mx+=tr[u].tag1.a;
		tr[u].tag1.a=0;
	}
	if(tr[u].tag1.b){
		tr[ls(u)].tag1.div(tr[u].tag1.b),
		tr[rs(u)].tag1.div(tr[u].tag1.b);
		tr[ls(u)].mx/=tr[u].tag1.b,
		tr[rs(u)].mx/=tr[u].tag1.b;
		tr[u].tag1.b=1;		
	}
	if(tr[u].tag1.c){
		tr[ls(u)].tag1.add(tr[u].tag1.c),
		tr[rs(u)].tag1.add(tr[u].tag1.c);
		tr[ls(u)].mx+=tr[u].tag1.c,
		tr[rs(u)].mx+=tr[u].tag1.c;
		tr[u].tag1.c=0;
	}	
	return ;
}
il void build(int u,int l,int r){
	tr[u].l=l,tr[u].r=r,tr[u].tag1.clear();
	if(l==r){
		tr[u].mx=tr[u].rmx=a[l];
		return ;
	}
	int mid=l+r>>1;
	build(ls(u),l,mid),build(rs(u),mid+1,r);
	up(u),tr[u].rmx=tr[u].mx;
	return ;
}
il void modify_add(int u,int l,int r,int x){
	if(tr[u].l>=l&&tr[u].r<=r){
		tr[u].tag1.add(x);
		tr[u].mx+=x;
		return ;
	}
	down(u);
	int mid=tr[u].l+tr[u].r>>1;
	if(l<=mid) modify_add(ls(u),l,r,x);
	if(mid< r) modify_add(rs(u),l,r,x);
	return up(u),void(0);
}
il void modify_div(int u,int l,int r,int x){
	if(tr[u].l>=l&&tr[u].r<=r){
		tr[u].tag1.div(x);
		tr[u].mx/=x;
		return ;
	}
	down(u);
	int mid=tr[u].l+tr[u].r>>1;
	if(l<=mid) modify_div(ls(u),l,r,x);
	if(mid< r) modify_div(rs(u),l,r,x);
	return up(u),void(0);	
}
il void modify_res(int u,int l,int r){
	if(tr[u].l>=l&&tr[u].r<=r){
		tr[u].tag1.clear();
		tr[u].mx=tr[u].rmx,tr[u].tag2=1;
		return ;
	}
	down(u);
	int mid=tr[u].l+tr[u].r>>1;
	if(l<=mid) modify_res(ls(u),l,r);
	if(mid< r) modify_res(rs(u),l,r);
	return up(u),void(0);
}
il int query(int u,int l,int r){
	if(tr[u].l>=l&&tr[u].r<=r) return tr[u].mx;
	down(u);
	int mid=tr[u].l+tr[u].r>>1,mx=0;
	if(l<=mid) mx=max(mx,query(ls(u),l,r));
	if(mid< r) mx=max(mx,query(rs(u),l,r));
	up(u);
	return mx;
}
```

---

## 作者：scp020 (赞：3)

# AT_jag2018summer_day2_i ADD DIV MAX RESTORE 题解

拿来题一看，哟，这不雅礼集训市场那题吗，狂喜。

## 解法

但是读完题后发现最后一个操作会使区间的势能重置，复杂度并没有保障。所以考虑新做法。为了方便表述，我们分别称 $4$ 个操作为加法、除法、查询、重置操作。

显然还是考虑线段树做法，但是这里维护懒标记的方法非传统方法。

我们把加法操作和除法操作看作是一种 $f(x)$ 的映射，其中 $x$ 即为线段树当前节点的答案。本题中形如 $f(x) = (ax + b)/c$ 和 $f(x)=(a + x)/b + c$ 的映射都是可以的，这里我们只讨论后者。

重置操作过于简单，这里不多说了。

加法操作即直接在 $c$ 上加 $val$ 就可以了。

对于除法操作，我们重构 $a,b,c$ 的值。通分后原来的值为 $\dfrac{a + bc}{b}$，$a$ 的意义是除以 $b$ 的余数，$c$ 的意义是除以 $b$ 的商，所以 $a,b,c$ 的新值分别为 $a+bc\mod {(b \times val)},\left\lfloor \dfrac{a + bc}{b \times val} \right\rfloor,b \times val$。

剩下的就全是基础的线段树操作了。

## 代码

```cpp
#include<bits/stdc++.h>
namespace fast_IO
{
    /**
     * useless fast IO
     */
};
using namespace fast_IO;
#define int long long
const int V=1e9;
int n,m,a[200010];
// 节点表示为 (x+a)/b+c
struct fun
{
    int a,b,c;
    inline fun()
    {
        a=0,b=1,c=0;
    }
    inline void clear()
    {
        a=0,b=1,c=0;
    }
    inline int calc(const int x)
    {
        return (x+a)/b+c;
    }
    inline void add(const int x)
    {
        c+=x;
    }
    inline void div(const int x)
    {
        int na,nb,nc;
        nb=b*x,nc=(a+b*c)/nb,na=(a+b*c)%nb;
        if(nb>V) na=std::max(0ll,na-nb+V),nb=V;
        a=na,b=nb,c=nc;
    }
};
struct node
{
    int maxi,ori_maxi,tag;
    fun lazy;
    node *lc,*rc;
    inline node()
    {
        maxi=ori_maxi=tag=0,lc=rc=nullptr;
    }
    inline void pushup()
    {
        maxi=std::max(lc->maxi,rc->maxi);
    }
    inline void pushdown()
    {
        if(tag)
            lc->lazy.clear(),rc->lazy.clear(),lc->maxi=lc->ori_maxi,rc->maxi=rc->ori_maxi,lc->tag=rc->tag=1,tag=0;
        if(lazy.a) lc->lazy.add(lazy.a),rc->lazy.add(lazy.a),lc->maxi+=lazy.a,rc->maxi+=lazy.a,lazy.a=0;
        if(lazy.b!=1) lc->lazy.div(lazy.b),rc->lazy.div(lazy.b),lc->maxi/=lazy.b,rc->maxi/=lazy.b,lazy.b=1;
        if(lazy.c) lc->lazy.add(lazy.c),rc->lazy.add(lazy.c),lc->maxi+=lazy.c,rc->maxi+=lazy.c,lazy.c=0;
    }
};
class seg_tree
{
    #define ls l,mid
    #define rs mid+1,r
private:
    node *root;
    inline node *build(int l,int r)
    {
        node *rt=new node();
        if(l==r) rt->maxi=rt->ori_maxi=a[l];
        else
        {
            int mid=(l+r)/2;
            rt->lc=build(ls),rt->rc=build(rs),rt->pushup(),rt->ori_maxi=rt->maxi;
        }
        return rt;
    }
    inline void add(node *rt,const int L,const int R,const int val,int l,int r)
    {
        if(L<=l && r<=R)
        {
            rt->maxi+=val,rt->lazy.add(val);
            return;
        }
        int mid=(l+r)/2;
        rt->pushdown();
        if(L<=mid) add(rt->lc,L,R,val,ls);
        if(R>mid) add(rt->rc,L,R,val,rs);
        rt->pushup();
    }
    inline void div(node *rt,const int L,const int R,const int val,int l,int r)
    {
        if(L<=l && r<=R)
        {
            rt->maxi/=val,rt->lazy.div(val);
            return;
        }
        int mid=(l+r)/2;
        rt->pushdown();
        if(L<=mid) div(rt->lc,L,R,val,ls);
        if(R>mid) div(rt->rc,L,R,val,rs);
        rt->pushup();
    }
    inline void fil(node *rt,const int L,const int R,int l,int r)
    {
        if(L<=l && r<=R)
        {
            rt->maxi=rt->ori_maxi,rt->lazy.clear(),rt->tag=1;
            return;
        }
        int mid=(l+r)/2;
        rt->pushdown();
        if(L<=mid) fil(rt->lc,L,R,ls);
        if(R>mid) fil(rt->rc,L,R,rs);
        rt->pushup();
    }
    inline int ask(node *rt,const int L,const int R,int l,int r)
    {
        if(L<=l && r<=R) return rt->maxi;
        int mid=(l+r)/2,ret=LONG_LONG_MIN;
        rt->pushdown();
        if(L<=mid) ret=std::max(ret,ask(rt->lc,L,R,ls));
        if(R>mid) ret=std::max(ret,ask(rt->rc,L,R,rs));
        return ret;
    }
public:
    inline void build()
    {
        root=build(1,n);
    }
    inline void add(const int L,const int R,const int val)
    {
        add(root,L,R,val,1,n);
    }
    inline void div(const int L,const int R,const int val)
    {
        div(root,L,R,val,1,n);
    }
    inline void fil(const int L,const int R)
    {
        fil(root,L,R,1,n);
    }
    inline int ask(const int L,const int R)
    {
        return ask(root,L,R,1,n);
    }
};
seg_tree tree;
signed main()
{
    in>>n>>m;
    for(int i=1;i<=n;i++) in>>a[i];
    tree.build();
    for(int i=1,op,x,y,z;i<=m;i++)
    {
        in>>op>>x>>y>>z,x++,y++;
        if(op==0) tree.add(x,y,z);
        else if(op==1) tree.div(x,y,z);
        else if(op==2) out<<tree.ask(x,y)<<'\n';
        else tree.fil(x,y);
    }
    fwrite(Ouf,1,p3-Ouf,stdout),fflush(stdout);
    return 0;
}
```

---

## 作者：Tjaweiof (赞：1)

# AT_jag2018summer_day2_i 题解
[题目传送门](https://www.luogu.com.cn/problem/AT_jag2018summer_day2_i)

线段树。

考虑到有 `DIV` 操作，可以维护三个标记 $ad,ad2,di$，表示 $x$ 要变为 $\lfloor\frac{x+ad}{di}\rfloor+ad2$。`ADD` 时增加 $ad2$ 的值即可。`DIV` 时，假设要将 $\lfloor\frac{x+ad}{di}\rfloor+ad2$ 除以 $v$，即 $\lfloor\frac{\lfloor\frac{x+ad}{di}\rfloor+ad2}v\rfloor$，这个式子可以变为$\lfloor\frac{x+(ad+di\times ad2)\bmod(di\times v)}{di}\rfloor+\lfloor\frac {ad+di\times ad2}{di\times v}\rfloor$，可以发现，它又回到了最初 $\lfloor\frac{x+ad}{di}\rfloor+ad2$ 的形式，所以这个标记方法是可行的。

对于 `RESTORE` 操作，维护一个标记即可，注意要清空其它所有标记。

最后注意一下，需要用一些小技巧（见代码）防止爆炸。

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define FILE(x) freopen(x".in", "r", stdin);freopen(x".out", "w", stdout);
const int N = 2e5, inf = 1e9;
long long a[N + 1], ta[N << 2], t[N << 2], ad[N << 2], di[N << 2], ad2[N << 2];
bool re[N << 2];
void add(int x, long long v, int L, int R){
	t[x] += v;
	ad2[x] += v;
	return;
}
void div(int x, long long v, int L, int R){
	long long tmp = ad[x] + di[x] * ad2[x];
	t[x] /= v;
	di[x] *= v;
	ad[x] = tmp % di[x];
	ad2[x] = tmp / di[x];
    if (di[x] >= inf){
		ad[x] -= di[x] - inf;
		ad[x] = max(ad[x], 0ll);
		di[x] = inf;
	}
	return;
}
void restore(int x, int L, int R){
	t[x] = ta[x];
	ad[x] = 0;
	di[x] = 1;
	ad2[x] = 0;
	re[x] = true;
	return;
}
void pushup(int x){
	t[x] = max(t[x << 1], t[x << 1 | 1]);
	return;
}
void pushdown(int x, int L, int R){
	int mid = (L + R) >> 1;
	if (re[x]){
		restore(x << 1, L, mid);
		restore(x << 1 | 1, mid + 1, R);
		re[x] = false;
	}
	if (ad[x]){
		add(x << 1, ad[x], L, mid);
		add(x << 1 | 1, ad[x], mid + 1, R);
		ad[x] = 0;
	}
	if (di[x] != 1){
		div(x << 1, di[x], L, mid);
		div(x << 1 | 1, di[x], mid + 1, R);
		di[x] = 1;
	}
	if (ad2[x]){
		add(x << 1, ad2[x], L, mid);
		add(x << 1 | 1, ad2[x], mid + 1, R);
		ad2[x] = 0;
	}
	return;
}
void build(int x, int L, int R){
	di[x] = 1;
	if (L == R){
		t[x] = a[L];
		ta[x] = a[L];
		return;
	}
	int mid = (L + R) >> 1;
	build(x << 1, L, mid);
	build(x << 1 | 1, mid + 1, R);
	pushup(x);
	ta[x] = max(ta[x << 1], ta[x << 1 | 1]);
	return;
}
void changeadd(int x, long long v, int l, int r, int L, int R){
	if (l == L && r == R){
		add(x, v, L, R);
		return;
	}
	pushdown(x, L, R);
	int mid = (L + R) >> 1;
	if (r <= mid){
		changeadd(x << 1, v, l, r, L, mid);
	} else if (l > mid){
		changeadd(x << 1 | 1, v, l, r, mid + 1, R);
	} else {
		changeadd(x << 1, v, l, mid, L, mid);
		changeadd(x << 1 | 1, v, mid + 1, r, mid + 1, R);
	}
	pushup(x);
	return;
}
void changediv(int x, long long v, int l, int r, int L, int R){
	if (l == L && r == R){
		div(x, v, L, R);
		return;
	}
	pushdown(x, L, R);
	int mid = (L + R) >> 1;
	if (r <= mid){
		changediv(x << 1, v, l, r, L, mid);
	} else if (l > mid){
		changediv(x << 1 | 1, v, l, r, mid + 1, R);
	} else {
		changediv(x << 1, v, l, mid, L, mid);
		changediv(x << 1 | 1, v, mid + 1, r, mid + 1, R);
	}
	pushup(x);
	return;
}
void changerestore(int x, int l, int r, int L, int R){
	if (l == L && r == R){
		restore(x, L, R);
		return;
	}
	pushdown(x, L, R);
	int mid = (L + R) >> 1;
	if (r <= mid){
		changerestore(x << 1, l, r, L, mid);
	} else if (l > mid){
		changerestore(x << 1 | 1, l, r, mid + 1, R);
	} else {
		changerestore(x << 1, l, mid, L, mid);
		changerestore(x << 1 | 1, mid + 1, r, mid + 1, R);
	}
	pushup(x);
	return;
}
long long query(int x, int l, int r, int L, int R){
	if (l == L && r == R){
		return t[x];
	}
	pushdown(x, L, R);
	int mid = (L + R) >> 1;
	if (r <= mid){
		return query(x << 1, l, r, L, mid);
	} else if (l > mid){
		return query(x << 1 | 1, l, r, mid + 1, R);
	} else {
		return max(query(x << 1, l, mid, L, mid), query(x << 1 | 1, mid + 1, r, mid + 1, R));
	}
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, q, op, l, r;
	long long x;
	cin >> n >> q;
	for (int i = 1; i <= n; i++){
		cin >> a[i];
	}
	build(1, 1, n);
	while (q--){
		cin >> op >> l >> r >> x;
		l++;
		r++;
		if (!op){
			changeadd(1, x, l, r, 1, n);
		} else if (op == 1){
			changediv(1, x, l, r, 1, n);
		} else if (op == 2){
			cout << query(1, l, r, 1, n) << "\n";
		} else {
			changerestore(1, l, r, 1, n);
		}
	}
	return 0;
}
```

---

