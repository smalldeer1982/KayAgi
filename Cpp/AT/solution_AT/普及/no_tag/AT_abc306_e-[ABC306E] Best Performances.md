# [ABC306E] Best Performances

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc306/tasks/abc306_e

長さ $ N $ の数列 $ A=(A_1,A_2,\dots,A_N) $ があり、最初全ての項が $ 0 $ です。  
 入力で与えられる整数 $ K $ を用いて関数 $ f(A) $ を以下のように定義します。

- $ A $ を降順に (広義単調減少となるように) ソートしたものを $ B $ とする。
- このとき、 $ f(A)=B_1\ +\ B_2\ +\ \dots\ +\ B_K $ とする。
 
この数列に合計 $ Q $ 回の更新を行うことを考えます。  
 数列 $ A $ に対し以下の更新を $ i=1,2,\dots,Q $ の順に行い、各更新ごとにその時点での $ f(A) $ の値を出力してください。

- $ A_{X_i} $ を $ Y_i $ に変更する。

## 说明/提示

### 制約

- 入力は全て整数
- $ 1\ \le\ K\ \le\ N\ \le\ 5\ \times\ 10^5 $
- $ 1\ \le\ Q\ \le\ 5\ \times\ 10^5 $
- $ 1\ \le\ X_i\ \le\ N $
- $ 0\ \le\ Y_i\ \le\ 10^9 $
 
### Sample Explanation 1

この入力では $ N=4,K=2 $ です。 $ Q=10 $ 回の更新を行います。 - $ 1 $ 回目の更新を受けて $ A=(5,0,0,0) $ となります。このとき $ f(A)=5 $ です。 - $ 2 $ 回目の更新を受けて $ A=(5,1,0,0) $ となります。このとき $ f(A)=6 $ です。 - $ 3 $ 回目の更新を受けて $ A=(5,1,3,0) $ となります。このとき $ f(A)=8 $ です。 - $ 4 $ 回目の更新を受けて $ A=(5,1,3,2) $ となります。このとき $ f(A)=8 $ です。 - $ 5 $ 回目の更新を受けて $ A=(5,10,3,2) $ となります。このとき $ f(A)=15 $ です。 - $ 6 $ 回目の更新を受けて $ A=(0,10,3,2) $ となります。このとき $ f(A)=13 $ です。 - $ 7 $ 回目の更新を受けて $ A=(0,10,3,0) $ となります。このとき $ f(A)=13 $ です。 - $ 8 $ 回目の更新を受けて $ A=(0,10,1,0) $ となります。このとき $ f(A)=11 $ です。 - $ 9 $ 回目の更新を受けて $ A=(0,0,1,0) $ となります。このとき $ f(A)=1 $ です。 - $ 10 $ 回目の更新を受けて $ A=(0,0,0,0) $ となります。このとき $ f(A)=0 $ です。

## 样例 #1

### 输入

```
4 2 10
1 5
2 1
3 3
4 2
2 10
1 0
4 0
3 1
2 0
3 0```

### 输出

```
5
6
8
8
15
13
13
11
1
0```

# 题解

## 作者：CarroT5656 (赞：7)

**题目大意**

给定一个长度为 $N$ 的序列 $A$。$A$ 初始每一项都为 $0$。

有 $Q$ 次操作，每次操作会将 $A_x$ 替换为 $Y$。

每次操作后，输出 $A$ 中前 $K$ 大的值的和。

**解题思路**

可以用线段树或平衡树等数据结构来维护。这里介绍一种简便的做法。

首先考虑到每次最多只会改变一个数的值，比较好维护。

开两个 `multiset`，记为 $s$ 和 $s1$。

$s$ 记录 $A$ 中前 $K$ 大的数，$s1$ 记录前 $N-K$ 小的数。

再用一个变量 $cnt$ 记录前 $K$ 大的数的和。

每次操作就从 $s$ 和 $s1$ 中删掉 $A_x$，插入 $Y$。

如果集合中的元素个数不符，那就从另一个集合中搬过来。

时间复杂度 $O(q\log n)$，可以通过。

**Code**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ins insert
#define N 500005
ll n,k,q,a[N],ans;
multiset<ll> s,s1;
int main(){
	scanf("%lld%lld%lld",&n,&k,&q);
	for(ll i=1;i<=k;i++) s.ins(0);
	for(ll i=1;i<=n-k;i++) s1.ins(0);
	for(ll i=1,x,y;i<=q;i++){
		scanf("%lld%lld",&x,&y);
		if(s.find(a[x])!=s.end()) s.erase(s.find(a[x])),ans-=a[x];
		else s1.erase(s1.find(a[x]));
		a[x]=y;
		if(s1.size()>0&&y>=*s1.rbegin()) s.ins(y),ans+=y;
		else s1.ins(y);
		if(s.size()<k){
			s.ins(*s1.rbegin());
			ans+=*s1.rbegin();
			s1.erase(s1.find(*s1.rbegin()));
		}
		if(s.size()>k){
			s1.ins(*s.begin());
			ans-=*s.begin();
			s.erase(s.begin());
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：AkeRi (赞：3)

# Description

维护一个序列，支持单点修改和前 $k$ 大和。

# Solution

注意到前 $k$ 大和的变化次数有限，我们可以用一个平衡树来维护。修改时分类讨论更改前对应位置上的值对答案的贡献即可。

平衡树需要维护的关系有：

- 第 $k$ 大。
- 排名。
- 插入、删除。

```cpp
//省略kth rank insert del 的代码，就是模板。
//注意 kth 若是求第 k 大则是 n-k+1 小。
int a[KI],n=read(),k=read(),q=read();
signed main()
{
    k=n-k+1;
    for(int i=1;i<=n;i++) 
    {
        a[i]=0;
        insert(0);
    }
    int cnt=0;
    while(q--)
    {   
        int x=read(),y=read();
        int S=rank(a[x]);
        if(S<k)
        {
            int v=kth(k);
            cnt-=v;
            del(a[x]);
            a[x]=y;
            insert(y);
            int s=rank(y);
            if(s>=k) cnt+=y;
            else cnt+=v;
        }
        else
        {
            cnt-=a[x];
            del(a[x]);
            a[x]=y;
            insert(y);
            int s=rank(y);
            int v=kth(k);
            if(s>=k) cnt+=y;
            else cnt+=v;
        }
        std::cout<<cnt<<'\n';
    }
}
```

---

## 作者：XSean (赞：3)

## E：Best Performances

[E - Best Performances](https://atcoder.jp/contests/abc306/tasks/abc306_e)

本题一共有两种作法。

### 方法1：

使用权值线段树。

思路：普通线段树的单点修改，找到第 $K$ 大，然后区间求和即可。

细节：

1. 一个权值线段树的信息有区间有多少数，区间的权值和，每一个叶子节点表示的是哪个数，其实就是数字在 $A$ 数组的位置。

```cpp
LL Num[N << 2], Sum[N << 2], Pos[N << 2];
```

2. $A$ 数组的值的数值的范围太大，采用哈希。但是我们发现因为是权值线段树，所以当 $A$ 数组中的多个位置的数值相同时，都会在一个节点更新值，当查询的第 $K$ 大并区间求和的时候会把和第 $K$ 大相同的数字的值一起加进去就错了。所以使用每一个输入的数字都给予一个编号。

`chan` 数组是修改数组。

```cpp
const int N = 5e5 + 10;
int n, k, q;
PII chan[N];
PII h[N]; int len;

rd(n, k, q);
rep(i, 1, q){
    int x, y; rd(x, y);
    chan[i] = {x, y};
    h[i] = {y, i};
}
sort(h + 1, h + q + 1);
len = q;
rep(i, 1, q) chan[h[i].se].se = i;
```

下面是各函数的代码：

`Sum` 数组是数字个数的区间总和，`Num` 数组是区间取值和。

- 单点修改：

```cpp
void pushup(int p){
	Num[p] = Num[ls(p)] + Num[rs(p)];
	Sum[p] = Sum[ls(p)] + Sum[rs(p)];
}
void modify(int p, int l, int r, int pos, int t){
	if(l == r){
		Sum[p] += t;
		Num[p] += t * h[pos].fi;
		Pos[p] = pos;
		return;
	}
	int mid = (l + r) >> 1;
	if(pos <= mid) modify(ls(p), l, mid, pos, t);
	else modify(rs(p), mid + 1, r, pos, t);
	pushup(p);
}
```

- 寻找第 $K$ 大：

```cpp
int qsum(int p, int l, int r, int ql, int qr){
	if(ql <= l && r <= qr) return Sum[p];
	int res = 0;
	int mid = (l + r) >> 1;
	if(ql <= mid) res += qsum(ls(p), l, mid, ql, qr);
	if(mid <  qr) res += qsum(rs(p), mid + 1, r, ql, qr);
	return res;  
}
int qpos(int p, int l, int r, int pos){
	if(l == r) return Pos[p];
	int mid = (l + r) >> 1;
	int temp = qsum(1, 1, len, mid + 1, r);
	if(temp >= pos) return qpos(rs(p), mid + 1, r, pos);
	else return qpos(ls(p), l, mid, pos - temp);
}
```

- 区间求和：

```cpp
LL qnum(int p, int l, int r, int ql, int qr){
	if(ql <= l && r <= qr) return Num[p];
	LL res = 0;
	int mid = (l + r) >> 1;
	if(ql <= mid) res += qnum(ls(p), l, mid, ql, qr);
	if(mid <  qr) res += qnum(rs(p), mid + 1, r, ql, qr);
	return res;	
}
```

复杂度：$O(Q\log^2N)$。

**[完整代码](https://www.luogu.com.cn/paste/9dbjkknr)**

### 方法2：

使用两个 multiset。

multiset 是排好序的，`*S.begin()` 就是这个 multiset 的最小值，`*--S.end()` 就是这个 multiset 的最大值。

思路：一个维护前 $K$ 大的元素，一个维护其他元素。普通对顶堆的思路，应该好理解。

细节：维护前 $K$ 大的 multiset 的时候先将维护其他元素的 multiset 的最大值取出插入维护前 $K$ 大的 multiset，然后将更改后的数也插入维护前 $K$ 大的 multiset，最后将维护前 $K$ 大的 multiset 的最小值取出插入维护其他元素的 multiset。

复杂度：$O(Q\log N)$。

**[完整代码](https://www.luogu.com.cn/paste/dylx0lpa)**

---

## 作者：GI录像机 (赞：1)

### 题目大意：
现有一个大小为 $n$ 的数组 $A$，数组中的数初始为 $0$。给定一个 $k$ 与 $m$ 个单点修改操作，求每次操作后数组的前 $k$ 大值之和。

### 解题思路：
~~观察到空间和时间十分充足，考虑大力线段树。~~

建一个动态开点权值线段树，记录当前区间数的个数和和所有数总和。为了选出更大的值，查询时尽量往右半区间靠。如果右半区间不够，剩下的数就从左半区间里拿。

记得初始要给 $0$ 这个节点增加 $n$ 个，否则会出现把整个线段树拿完都不够 $k$ 个的情况。

### 参考代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int read() {
	int f = 1, x = 0;
	char c = getchar();
	while (c < '0' || c > '9') {
		if (c == '-')f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		x = x * 10 + c - '0';
		c = getchar();
	}
	return f * x;
}
void write(int x) {
	if (x < 0) {
		putchar('-');
		x = -x;
	}
	if (x > 9)write(x / 10);
	putchar(x % 10 + '0');
}
const int N = 5e7 + 10, MOD = 1e9 + 7, INF = 0x3f3f3f3f;
int n = read(), k = read(), q = read(), ans, b[N], tot = 1;
struct Node {
	int sum, num, lson, rson;
} a[N];
void pushup(int pos) {
	a[pos].num = a[a[pos].lson].num + a[a[pos].rson].num;
	a[pos].sum = a[a[pos].lson].sum + a[a[pos].rson].sum;
}
void change(int pos, int l, int r, int L, int K) {
	if (l == r) {
		a[pos].sum += l * K;
		a[pos].num += K;
		return;
	}
	int mid = (l + r) >> 1;
	if (!a[pos].lson)a[pos].lson = ++tot;
	if (!a[pos].rson)a[pos].rson = ++tot;
	if (mid >= L)change(a[pos].lson, l, mid, L, K);
	else change(a[pos].rson, mid + 1, r, L, K);
	pushup(pos);
}
int query(int pos, int l, int r, int K) {
	if (l == r)return l * K;
	int mid = (l + r) >> 1, tmp = 0;
	if (!a[pos].lson)a[pos].lson = ++tot;
	if (!a[pos].rson)a[pos].rson = ++tot;
	if (a[a[pos].rson].num < K) {
		tmp += a[a[pos].rson].sum;
		tmp += query(a[pos].lson, l, mid, K - a[a[pos].rson].num);
	} else if (a[a[pos].rson].num == K)tmp += a[a[pos].rson].sum;
	else tmp += query(a[pos].rson, mid + 1, r, K);
	return tmp;
}
signed main() {
	//freopen(".in", "r", stdin);
	//freopen(".out", "w", stdout);
	change(1, 0, 1e9, 0, n);
	while (q--) {
		int x = read(), y = read();
		change(1, 0, 1e9, b[x], -1);
		b[x] = y;
		change(1, 0, 1e9, b[x], 1);
		write(query(1, 0, 1e9, k));
		putchar('\n');
	}
	return 0;
}
```

---

