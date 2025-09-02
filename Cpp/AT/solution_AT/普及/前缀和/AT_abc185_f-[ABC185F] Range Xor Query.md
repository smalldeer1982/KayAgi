# [ABC185F] Range Xor Query

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc185/tasks/abc185_f

長さ $ N $ の整数列 $ A $ があります。  
 あなたは今からこの数列について $ Q $ 個のクエリを処理します。$ i $ 番目のクエリでは、 $ T_i,\ X_i,\ Y_i $ が与えられるので、以下の処理をしてください。

- $ T_i\ =\ 1 $ のとき  
   $ A_{X_i} $ を $ A_{X_i}\ \oplus\ Y_i $ で置き換える
- $ T_i\ =\ 2 $ のとき  
   $ A_{X_i}\ \oplus\ A_{X_i\ +\ 1}\ \oplus\ A_{X_i\ +\ 2}\ \oplus\ \dots\ \oplus\ A_{Y_i} $ を出力する

ただし $ a\ \oplus\ b $ は $ a $ と $ b $ のビット単位 xor を表します。  
 ビット単位 xor とは  整数 $ A,\ B $ のビット単位 xor 、$ A\ \oplus\ B $ は、以下のように定義されます。

\- $ A\ \oplus\ B $ を二進表記した際の $ 2^k $ ($ k\ \geq\ 0 $) の位の数は、$ A,\ B $ を二進表記した際の $ 2^k $ の位の数のうち一方のみが $ 1 $ であれば $ 1 $、そうでなければ $ 0 $ である。
 
 例えば、$ 3\ \oplus\ 5\ =\ 6 $ となります (二進表記すると: $ 011\ \oplus\ 101\ =\ 110 $)。

## 说明/提示

### 制約

- $ 1\ \le\ N\ \le\ 300000 $
- $ 1\ \le\ Q\ \le\ 300000 $
- $ 0\ \le\ A_i\ \lt\ 2^{30} $
- $ T_i $ は $ 1 $ または $ 2 $
- $ T_i\ =\ 1 $ なら $ 1\ \le\ X_i\ \le\ N $ かつ $ 0\ \le\ Y_i\ \lt\ 2^{30} $
- $ T_i\ =\ 2 $ なら $ 1\ \le\ X_i\ \le\ Y_i\ \le\ N $
- 入力は全て整数

### Sample Explanation 1

$ 1 $ 個目のクエリでは $ 1\ \oplus\ 2\ \oplus\ 3\ =\ 0 $ を出力します。 $ 2 $ 個目のクエリでは $ 2\ \oplus\ 3\ =\ 1 $ を出力します。 $ 3 $ 個目のクエリでは $ A_2 $ が $ 2\ \oplus\ 3\ =\ 1 $ で置き換えられます。 $ 4 $ 個目のクエリでは $ 1\ \oplus\ 3\ =\ 2 $ を出力します。

## 样例 #1

### 输入

```
3 4
1 2 3
2 1 3
2 2 3
1 2 3
2 2 3```

### 输出

```
0
1
2```

## 样例 #2

### 输入

```
10 10
0 5 3 4 7 0 0 0 1 0
1 10 7
2 8 9
2 3 6
2 1 6
2 1 10
1 9 4
1 6 1
1 6 3
1 1 7
2 3 5```

### 输出

```
1
0
5
3
0```

# 题解

## 作者：scp020 (赞：4)

本题我在原网站通过了，详情看本篇题解最底下。

看到大家都用的 BIT，于是我补一个线段树题解。

解本题前先介绍两个关于异或的性质。

- $x \oplus y \oplus z = x \oplus z \oplus y$。

- $x \oplus 0 = x$。

对于操作 $1$，把 $a_x$ 改为 $a_x \oplus y$，则 $\forall {1 \le i \le x,x \le j \le n}$，有 $\sum \limits _ {k = i} ^ {j} a_k$ 改为 $(\sum \limits _ {k = i} ^ {j} a_k) \oplus y$。

对于操作 $2$，输出 $\sum \limits _ {k = i} ^ {j} a_k$ 即可。

这是一个单点修改，区间查询的线段树。

下面给出代码，我写的动态开点线段树，虽然有 $90$ 行，但是快读快写占了许多行，如果看不懂可以跳过，其作用与标准输入输出相同。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ls l,mid
#define rs mid+1,r
#define Getchar() p1==p2 and (p2=(p1=Inf)+fread(Inf,1,1<<21,stdin),p1==p2)?EOF:*p1++
#define Putchar(c) p3==p4 and (fwrite(Ouf,1,1<<21,stdout),p3=Ouf),*p3++=c
char Inf[1<<21],Ouf[1<<21],*p1,*p2,*p3=Ouf,*p4=Ouf+(1<<21);
inline void read(int &x,char c=Getchar())
{
	bool f=c!='-';
	x=0;
	while(c<48 or c>57) c=Getchar(),f&=c!='-';
	while(c>=48 and c<=57) x=(x<<3)+(x<<1)+(c^48),c=Getchar();
	x=f?x:-x;
}
inline void write(int x)
{
	if(x<0) Putchar('-'),x=-x;
	if(x>=10) write(x/10),x%=10;
	Putchar(x^48);
}
int n,q,t,x,y,cnt;
struct node
{
	int sum,lazy;
	node *lc,*rc;
	inline void pushup()
	{
		sum=lc->sum^rc->sum;
	}
	inline void pushdown()
	{
		if(lazy)
		{
			lc->lazy^=lazy,rc->lazy^=lazy,lc->sum^=lazy,rc->sum^=lazy;
			lazy=0;
		}
	}
};
node tree[600010],*root;
inline node *newnode()
{
	return &tree[++cnt];
}
inline node *build(int l,int r)
{
	node *rt=newnode();
	if(l==r) read(rt->sum);
	if(l<r)
	{
		int mid=(l+r)/2;
		rt->lc=build(ls),rt->rc=build(rs),rt->pushup();
	}
	return rt;
}
inline void fix(node *rt,int l,int r,const int &p,const int &val)
{
	if(l==r)
	{
		rt->sum^=val,rt->lazy^=val;
		return;
	}
	rt->pushdown();
	int mid=(l+r)/2;
	if(p<=mid) fix(rt->lc,ls,p,val);
	else fix(rt->rc,rs,p,val);
	rt->pushup();
}
inline int ask(node *rt,int l,int r,const int &L,const int &R)
{
	if(L<=l && r<=R) return rt->sum;
	rt->pushdown();
	int mid=(l+r)/2,ret=0;
	if(L<=mid) ret^=ask(rt->lc,ls,L,R);
	if(R>mid) ret^=ask(rt->rc,rs,L,R);
	return ret;
}
signed main()
{
	read(n),read(q),root=build(1,n);
	for(int i=1,op,x,y;i<=q;i++)
	{
		read(op),read(x),read(y);
		if(op==1) fix(root,1,n,x,y);
		else write(ask(root,1,n,x,y)),Putchar('\n');
	}
	fwrite(Ouf,1,p3-Ouf,stdout),fflush(stdout);
	return 0;
}
```

由于洛谷的 RMJ 寄了，我只能去原题交代码，下面附上评测记录。[记录](https://atcoder.jp/contests/abc185/submissions/41018357)。

---

## 作者：andyli (赞：1)

可以使用树状数组解决这个问题，与普通树状数组的区别是所有对值的加号和减号换成异或。

```python
(n, q), a, *Q = [[*map(int, s.split())] for s in open(0)]
c = [0] * n
def query(x):
    ans = 0
    while x > 0:
        ans ^= c[x - 1]
        x -= x & (-x)
    return ans
for i, x in enumerate(a):
    i += 1
    while i <= n:
        c[i - 1] ^= x
        i += i & (-i)
for op, x, y in Q:
    if op == 1:
        while x <= n:
            c[x - 1] ^= y
            x += x & (-x)
    else:
        print(query(y) ^ query(x - 1))
```

---

## 作者：lkjzyd20 (赞：0)

## 思路

这道题，线段树模版题。

- 操作 $1$：将 $A_X$ 替换为 $A_X \oplus Y$（单点修改）
- 操作 $2$：输出 $A_{X}\oplus A_{X+1}\oplus A_{X+2}\oplus\dots\oplus A_Y$（区间异或和）。

于是这道题只需要维护一个支持单点修改，区间求和的数据结构即可，直接在线段树模版上改一改就行了。

## 代码如下
```cpp
#include <bits/stdc++.h>

using namespace std;

// #define int long long
#define rep(i, l, r) for(int i = l; i <= r; ++ i)
#define per(i, r, l) for(int i = r; i >= l; -- i)
#define me0(a); memset(a, 0, sizeof a);
#define me3(a); memset(a, 0x3f, sizeof a);
#define PII pair<int, int>

const int INF = 0x3f3f3f3f, MOD = 1e9 + 7;

inline void read(int &n)
{
    bool w = 0;
    char c = getchar();
    for(; c < 48 || c > 57; c = getchar())
        w = c == 45;
    for(n = 0; c >= 48 && c <= 57; c = getchar())
        n = n * 10 + c - 48;
    n = w ? -n : n;
}

inline void write(int x, char a)
{
    char c[40], s = 0;
    if(x < 0) putchar(45), x = -x;
    for(; x ;) c[s ++] = x % 10, x /= 10;
    if(!s) putchar(48);
    for(; s -- ;) putchar(c[s] + 48);
    putchar(a);
}

const int MAXN = 1000001;
#define ls num + num
#define rs num + num + 1
int sum[MAXN << 2], p[MAXN], addans;
void update(int num) {sum[num] = sum[ls] ^ sum[rs];}
void build(int num, int l, int r)
{
	if(l == r)
	{
		sum[num] = p[l];
		return;
	}
	int mid = (l + r) >> 1;
	build(ls, l, mid);
	build(rs, mid + 1, r);
	update(num);
}
void find(int num, int l, int r, int x, int y)
{
	if(x <= l && r <= y)
	{
		addans ^= sum[num];
		return;
	}
	int mid = (l + r) >> 1;
	if(mid >= x) find(ls, l, mid, x, y);
	if(mid < y) find(rs, mid + 1, r, x, y);
}
void change(int num, int l, int r, int pos, int val)
{
	if(l == r)
	{
		sum[num] ^= val;
		return;
	}
	int mid = (l + r) >> 1;
	if(pos <= mid) change(ls, l, mid, pos, val);
	else change(rs, mid + 1, r, pos, val);
	update(num);
}
int n, Q;
main()
{
	read(n); read(Q);
    rep(i, 1, n) read(p[i]);
    build(1, 1, n);
	rep(i, 1, Q)
	{
		int c, x, y;
		read(c); read(x); read(y);
		if(c == 1)
			change(1, 1, n, x, y);
		else
		{
			addans = 0;
			find(1, 1, n, x, y);
			write(addans, '\n');
		}
	}
}
```

---

## 作者：loser_seele (赞：0)

吐槽：怎么会有这么板子的题目放在 F 题。

不难发现异或显然满足可减性质和前缀性质，即区间 $ [l,r] $ 的异或和为 $ sum_r \oplus sum_{l-1} $。于是实际上只需要维护一个支持单点修改，区间求和的数据结构即可，直接在树状数组板子上改一改就行了。

代码：

```cpp
#import <bits/stdc++.h>
using namespace std;
#define int long long
#define lowbit(x) (x&(-x))
int c[2000020],n;
inline void add(int x,int v) 
{
	while(x<=n)
	c[x]^=v,x+=lowbit(x);
}
inline int query(int x) 
{
	int res=0;
	while(x)
	res^=c[x],x-=lowbit(x);
	return res;
}
signed main() 
{
	int m;
	cin>>n>>m;
	for (int i=1;i<=n;i++) 
    {
		int x;
		cin>>x;
		add(i,x);
	}
	while(m--) 
    {
		int opt,l,r;
		cin>>opt>>l>>r;
		if(opt==1)
		add(l,r); 
        else
		cout<<(query(r)^query(l-1))<<endl;
	}
}
```


---

## 作者：tZEROちゃん (赞：0)

感觉是有史以来最简单的 F 题？

注意到我们要实现单点修改，区间查询，而 $a_x\oplus a_{x+1}\oplus \cdots \oplus a_y=s_y\oplus s_{x-1}$，其中 $s$ 是前缀异或和。

于是考虑使用 BIT，代码如下。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define rep(i, l, r) for(auto i = (l); i <= (r); ++i)

inline int rd() { 
  int x = 0, f = 1; char c = getchar();
  while (c < '0' || c > '9') { if (c == '-') f = -1; c = getchar(); } 
  while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar(); 
  return x * f;
}

const int N = 3e5 + 10;
int a[N];

namespace BIT {
  int c[N];
  int lowbit(int x) { return x & -x; }
  int ask(int x) {
    int ans = 0;
    for (; x; x -= lowbit(x)) ans ^= c[x];
    return ans;
  }
  void add(int x, int y) {
    for (; x <= N - 9; x += lowbit(x)) c[x] ^= y;
  }
}

using namespace BIT;

int main() {
  int n = rd(), q = rd();
  rep (i, 1, n) {
    add(i, rd());
  } 
  while (q--) {
    if (rd() == 1) {
      int x = rd(), k = rd();
      add(x, k);
    }
    else {
      int l = rd(), r = rd();
      cout << (ask(r) ^ ask(l - 1)) << endl;
    }
  }
}
```

---

