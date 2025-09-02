# Willem, Chtholly and Seniorious

## 题目描述

【题面】
请你写一种奇怪的数据结构，支持：
- $1$  $l$  $r$  $x$ ：将$[l,r]$ 区间所有数加上$x$ 
- $2$  $l$  $r$  $x$ ：将$[l,r]$ 区间所有数改成$x$ 
- $3$  $l$  $r$  $x$ ：输出将$[l,r]$ 区间从小到大排序后的第$x$ 个数是的多少(即区间第$x$ 小，数字大小相同算多次，保证 $1\leq$  $x$  $\leq$  $r-l+1$  )
- $4$  $l$  $r$  $x$  $y$ ：输出$[l,r]$ 区间每个数字的$x$ 次方的和模$y$ 的值(即($\sum^r_{i=l}a_i^x$ ) $\mod y$ )

## 样例 #1

### 输入

```
10 10 7 9
```

### 输出

```
2
1
0
3
```

## 样例 #2

### 输入

```
10 10 9 9
```

### 输出

```
1
1
3
3
```

# 题解

## 作者：泥土笨笨 (赞：259)

## 0x00 前言

事情是这样的，有一天，教练群里面讨论这道题，我说这道题排名前 $10$ 的题解里面，有 $7$ 个都是错的，我打算写一个对的，避免同学们被误导。这时候，群里的 lxl 默默的来了一句：

![](https://cdn.luogu.com.cn/upload/image_hosting/9vd7ykl9.png)

好的，既然是 lxl 大神出的题，我就更有必要写一篇正确的题解，来表达我对他的膜拜了。

## 0x01 为什么很多题解不对，照着写会RE
因为如果要用 `split` 操作，截取一段区间的时候，必须要先 `split(r+1)` ，再 `split(l)` ，否则会有 RE ，具体原因我后面会细说。请大家参考其他题解或者资料的时候，也注意这一点。

## 0x02 什么是珂朵莉树

珂朵莉树，还有个名字叫老司机树（Old Driver Tree, ODT），是一个暴力数据结构。甚至都不一定可以将其称之为数据结构了，我们不妨认为它是一类题目的暴力做法，对于随机数据比较有效。

## 0x03 珂朵莉树可以解决什么问题

有一类问题，对一个序列，进行一个**区间推平操作**。就是把一个范围内，比如 $[l,r]$ 范围内的数字变成同一个。可能除了推平以外，还夹杂其他操作。如果数据是随机的，就可以用珂朵莉树啦。比如这道题中的操作 $2$ ，将 $[l,r]$ 区间内的所有数都改成 $x$ ，这就是一个区间推平操作。

## 0x04 珂朵莉树的基本原理
暴力的地方来喽，刚才不是提到有推平操作么？那么推平操作结束以后，被推平的区间内的每个数字都是相同的。其实经过若干次推平以后，我们可以看成，这个序列上的数字是一段一段的，每一小段里面数字相同，整个区间由若干个小段组成。类似这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/k4fik6l0.png)

这个时候，我们定义一个结构体，用一个结构体变量，来表示每个数字相同的段。

```cpp
struct Node {
    ll l, r;//l和r表示这一段的起点和终点
    mutable ll v;//v表示这一段上所有元素相同的值是多少

    Node(ll l, ll r = 0, ll v = 0) : l(l), r(r), v(v) {}

    bool operator<(const Node &a) const {
        return l < a.l;//规定按照每段的左端点排序
    }
};
```

相关变量的含义，注释里面已经解释了。这里有个细节是， `v` 变量前面加个了 `mutable` 关键字。 `mutable` 的意思是，即使它是个常量，也允许修改v的值，具体我在下面区间修改的地方解释。

当每个数字相同的区间都用一个结构体变量表示以后，我们把这四段插入到一个 `set` 里面， `set` 会按照每段的左端点顺序进行排序，这样这个序列就维护好了，类似下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/nd7klccn.png)

当然，对于本题，一开始的时候，每段都只有一个数，所以我们的set里面维护n个长度为1的段。

## 0x05 核心操作 `split`
天下大势，分久必合，合久必分，珂朵莉树也一样。随着推平操作的进行，有一些位置被合并到了一个 `Node` 里面，但是也有可能一个 `Node` 要被拆开，其中的一部分要被改变值。

`split` 操作就是干这个用的，参数是一个位置 `pos` ，以 `pos` 去做切割，找到一个包含 `pos` 的区间，把它分成 `[l,pos-1]` , `[pos,r]` 两半。当然，如果 `pos` 本身就是一个区间的开头，就不用切割了，直接返回这个区间。

先看代码

```cpp
set<Node>::iterator split(int pos) {
    set<Node>::iterator it = s.lower_bound(Node(pos));
    if (it != s.end() && it->l == pos) {
        return it;
    }
    it--;
    if (it->r < pos) return s.end();
    ll l = it->l;
    ll r = it->r;
    ll v = it->v;
    s.erase(it);
    s.insert(Node(l, pos - 1, v));
    //insert函数返回pair，其中的first是新插入结点的迭代器
    return s.insert(Node(pos, r, v)).first;
}
```

首先，第一行里面的 `s` 是一个全局变量，是那个装 `node` 的 `set` 。大家知道 `set` 里面有个函数叫 `lower_bound` ，它的作用是返回跟参数相等的，或者比参数更大的第一个 `set` 中元素的位置，返回的是一个迭代器。

那么我们按照 `pos` 创建一个 `node` ，然后去查询，就找到了 `it` 这个位置。这个时候有三种情况，一种是我们正好找到了一个区间，它是以 `pos` 开头的，所以就对应了代码中的第一个 `if` 判断，这时候直接返回这个区间的迭代器 `it`。

还有两种情况是，我们找到的这个区间是正好比包含 `pos` 的区间大一点点的，或者`pos`太大了，超过了最后一个区间的右端点。不管怎样先把`it`往前挪一个格，然后这时候看看`it`的右端点，如果比`pos`小，说明是`pos`太大了，就直接返回`s`的`end()`迭代器。否则的话，现在`it`就是应该包含了`pos`的那个区间。这时候，我们要把它一分为二，把原来的那个区间删掉，然后插入两个新区间，分别是`[l,pos-1]`和`[pos,r]`。

这里还有个小技巧，`insert`这个函数是有返回值的，它返回的是一个`pair`，`pair`的第一个字段正好是新插入的那个`node`的位置的迭代器，所以`return`那个东西就行了。

## 0x06 推平操作`assign`
刚刚的`split`作用是分，现在还需要一个相反的操作，就是合并。当出现对区间的推平操作的时候，我们可以把整个`set`中所有要被合并掉的`node`都删掉，然后插入一个新区间表示推平以后的结果。

![](https://cdn.luogu.com.cn/upload/image_hosting/y63fx4wt.png)

如图，按照上面的例子，`set`里面有$4$个`node`，此时我们想进行一次推平操作，把`[2,8]`区间内的元素都改成$666$.首先我们发现，`[8,10]`是一个区间，那么需要先`split(9)`，把`[8,8]`和`[9,10]`拆成两个区间。同理，原来的`[1,2]`区间，也需要拆成`[1,1]`和`[2,2]`。

接下来，我们把要被合并的从$2$到$8$的所有`node`都从`set`里面删掉，再重新插入一个`[2,8]`区间就行了。删除某个范围内的元素可以用`set`的`erase`函数，这个函数接受两个迭代器`s`和`t`，把`[s,t)`范围内的东西都删掉。

代码如下：
```cpp
void assign(ll l, ll r, ll x) {
    set<Node>::iterator itr = split(r + 1), itl = split(l);
    s.erase(itl, itr);
    s.insert(Node(l, r, x));
}
```

## 0x07 推平操作里面RE的坑

现在说一下为啥大部分题解都不对，注意刚刚`assign`函数里面调用的那两次`split`，我是先`split(r+1)`，计算出`itr`，然后再`split(l)`，计算`itl`的。**这个顺序不能反**。

为啥不能反？举个具体例子，比如现在有个区间是`[1,4]`，我们想从里面截取`[1,1]`出来，那么我们需要调用两次`split`，分别是`split(2)`和`split(1)`。

假设先调用`split(1)`，如图中间的结果：
![](https://cdn.luogu.com.cn/upload/image_hosting/igxn8u1h.png)

现在的`itl`指向的还是原来的那个`node`，没有什么变化。但是当我们后续调用`itr`的时候，出事儿了。因为这时候，我们把原来的`[1,4]`区间删掉了，拆成了两份，`itr`指向的是后面那个，但是原来`itl`指向的那个已经被`erase`掉了。这时候用`itl`和`itr`调用`s.erase`的时候就会出问题，直接RE。

有同学说我顺序反了没RE啊，也AC。恭喜你，你人品好。这东西理论上会RE，但是实际上概率不大，我对拍了一下，大概1%的概率RE吧。但是人品不好的同学，可能上来就RE一片，而且是随机RE，同一个数据，一会儿能过，一会儿过不了。所以，还是别给自己找麻烦了。

## 0x08 修改操作`add`
区间内每个数都加上`x`，这个实现方式和前面的推平差不多，我们还是找到这个区间的首尾，然后循环一遍区间内的每个`node`，把每个`node`的`v`都加上`x`就行
```cpp
void add(ll l, ll r, ll x) {
    set<Node>::iterator itr = split(r + 1), itl = split(l);
    for (set<Node>::iterator it = itl; it != itr; ++it) {
        it->v += x;
    }
}
```

这里是用一个迭代器`it`遍历每个位置，把每个位置的`v`都加`x`。大家发现前面提到的`mutable`的作用了么？因为这里`it`是个常量迭代器，它不能修改它指向的那个`node`，而我们这里要改`node`里面的`v`，所以就把`v`声明为`mutable`，就可以改了。否则会得到类似这样的编译错误：
`error: cannot assign to return value
      because function 'operator->' returns a const value`
      
## 0x09 其他操作
其他操作都是类似的暴力操作。比如要找区间第$k$小，那么就把区间内所有的`node`拿出来，按照`v`从小到大排序，把每个`node`里面的区间长度相加，看看啥时候加够为止。这里就不细致展开，有问题可以去看代码。

## 0x0A 复杂度
因为本题数据是随机的，所以每次`assign`操作的区间长度大概在$vmax/3$，所以经过很多次`assign`以后，区间个数不会太多，大概在`log`这个数量级上。这样每次暴力操作的复杂度差不多也是这个数量级。详细的分析，可以参考这篇博客：

https://www.luogu.com.cn/blog/blaze/solution-cf896c

## 0x0B 代码时间

```cpp
#include <iostream>
#include <set>
#include <algorithm>
#include <vector>
#include <cstdio>

using namespace std;

typedef long long ll;
const ll MOD = 1000000007;
const ll MAXN = 100005;

struct Node {
    ll l, r;//l和r表示这一段的起点和终点
    mutable ll v;//v表示这一段上所有元素相同的值是多少

    Node(ll l, ll r = 0, ll v = 0) : l(l), r(r), v(v) {}

    bool operator<(const Node &a) const {
        return l < a.l;//规定按照每段的左端点排序
    }
};

ll n, m, seed, vmax, a[MAXN];
set<Node> s;

//以pos去做切割，找到一个包含pos的区间，把它分成[l,pos-1],[pos,r]两半
set<Node>::iterator split(int pos) {
    set<Node>::iterator it = s.lower_bound(Node(pos));
    if (it != s.end() && it->l == pos) {
        return it;
    }
    it--;
    if (it->r < pos) return s.end();
    ll l = it->l;
    ll r = it->r;
    ll v = it->v;
    s.erase(it);
    s.insert(Node(l, pos - 1, v));
    //insert函数返回pair，其中的first是新插入结点的迭代器
    return s.insert(Node(pos, r, v)).first;
}

/*
 * 这里注意必须先计算itr。
 * 比如现在区间是[1,4]，如果要add的是[1,2],如果先split(1)
 * 那么返回的itl是[1,4]，但是下一步计算itr的时候会把这个区间删掉拆成[1,2]和[3,4]
 * 那么itl这个指针就被释放了
 * */
void add(ll l, ll r, ll x) {
    set<Node>::iterator itr = split(r + 1), itl = split(l);
    for (set<Node>::iterator it = itl; it != itr; ++it) {
        it->v += x;
    }
}

void assign(ll l, ll r, ll x) {
    set<Node>::iterator itr = split(r + 1), itl = split(l);
    s.erase(itl, itr);
    s.insert(Node(l, r, x));
}

struct Rank {
    ll num, cnt;

    bool operator<(const Rank &a) const {
        return num < a.num;
    }

    Rank(ll num, ll cnt) : num(num), cnt(cnt) {}
};

ll rnk(ll l, ll r, ll x) {
    set<Node>::iterator itr = split(r + 1), itl = split(l);
    vector<Rank> v;
    for (set<Node>::iterator i = itl; i != itr; ++i) {
        v.push_back(Rank(i->v, i->r - i->l + 1));
    }
    sort(v.begin(), v.end());
    int i;
    for (i = 0; i < v.size(); ++i) {
        if (v[i].cnt < x) {
            x -= v[i].cnt;
        } else {
            break;
        }
    }
    return v[i].num;
}

ll ksm(ll x, ll y, ll p) {
    ll r = 1;
    ll base = x % p;
    while (y) {
        if (y & 1) {
            r = r * base % p;
        }
        base = base * base % p;
        y >>= 1;
    }
    return r;
}

ll calP(ll l, ll r, ll x, ll y) {
    set<Node>::iterator itr = split(r + 1), itl = split(l);
    ll ans = 0;
    for (set<Node>::iterator i = itl; i != itr; ++i) {
        ans = (ans + ksm(i->v, x, y) * (i->r - i->l + 1) % y) % y;
    }
    return ans;
}

ll rnd() {
    ll ret = seed;
    seed = (seed * 7 + 13) % MOD;
    return ret;
}

int main() {
    cin >> n >> m >> seed >> vmax;
    for (int i = 1; i <= n; ++i) {
        a[i] = (rnd() % vmax) + 1;
        s.insert(Node(i, i, a[i]));
    }
    for (int i = 1; i <= m; ++i) {
        ll op, l, r, x, y;
        op = (rnd() % 4) + 1;
        l = (rnd() % n) + 1;
        r = (rnd() % n) + 1;
        if (l > r) swap(l, r);
        if (op == 3) {
            x = (rnd() % (r - l + 1)) + 1;
        } else {
            x = (rnd() % vmax) + 1;
        }
        if (op == 4) {
            y = (rnd() % vmax) + 1;
        }
        if (op == 1) {
            add(l, r, x);
        } else if (op == 2) {
            assign(l, r, x);
        } else if (op == 3) {
            cout << rnk(l, r, x) << endl;
        } else {
            cout << calP(l, r, x, y) << endl;
        }
    }
    return 0;
}
```



---

## 作者：SuperJvRuo (赞：81)

珂朵莉树模板题。

## 一、什么是珂朵莉树

珂朵莉树，又称Old Driver Tree(ODT)。是一种基于```std::set```的暴力数据结构。B站上有UESTC的[讲解视频](https://www.bilibili.com/video/av21651173)。

## 二、什么时候用珂朵莉树

关键操作：推平一段区间，使一整段区间内的东西变得一样。保证数据随机。

就像这道题。

$n$个数，$m$次操作$(n,m\leq10^5)$。

操作：

1. 区间加
2.  **区间赋值**
3. 区间第k小
4. 求区间幂次和

**数据随机**，时限2s。

## 三、珂朵莉树的初始化

这道题里，这样定义珂朵莉树的节点：
```
struct node
{
	int l,r;
	mutable LL v;
	node(int L, int R=-1, LL V=0):l(L), r(R), v(V) {}
	bool operator<(const node& o) const
	{
		return l < o.l;
	}
};
```
这样的一个节点表示$[l,r]$内的所有数都是v。需要注意的是```mutable```，意为易变的，不定的。它对```v```的修饰，使得我们可以在```add```操作中修改```v```的值。没有它的修饰会在```add```函数里导致CE。

我们把节点存在```set```里。
```
set<node> s;
```

像CF896C这道题就这样初始化。
```
cin>>n>>m>>seed>>vmax;
for (int i=1; i<=n; ++i)
{
	a[i] = (rnd() % vmax) + 1;
	s.insert(node(i,i,a[i]));
}
```

初始化完了？初始化完了。

## 四、珂朵莉树的核心操作：split

```split(pos)```操作是指将原来含有pos位置的节点分成两部分：$[l,pos-1]$和$[pos,r]$。

看这个操作的代码：

```
#define IT set<node>::iterator
IT split(int pos)
{
	IT it = s.lower_bound(node(pos));
	if (it != s.end() && it->l == pos) return it;
	--it;
	int L = it->l, R = it->r;
	LL V = it->v;
	s.erase(it);
	s.insert(node(L, pos-1, V));
	return s.insert(node(pos, R, V)).first;
}
```

一行一行来看。

```
#define IT set<node>::iterator
```

宏定义没什么好说的，记住NOI系列赛事不能用```auto```。```auto```一时爽，评测火葬场。

```
IT it = s.lower_bound(node(pos));
```

找到首个$l$不小于pos的节点。

```
if (it != s.end() && it->l == pos)
	return it;
```

如果无需```split```，直接返回。

```
--it;
```

否则pos一定在前一个区间中。

```
int L = it->l, R = it->r;
```
$[L,R]$就是要被分割的区间。

```
LL V = it->v;
```
取出这个节点的值。

```
s.erase(it);
```
删除原节点。

```
s.insert(node(L, pos-1, V));
```
插入前半段。

```
return s.insert(node(pos, R, V)).first;
```
插入后半段，返回后半段的迭代器。这里利用了```pair<iterator,bool> insert (const value_type& val)```的返回值。

## 五、珂朵莉树的推平操作：assign

要是只有```split```还不得复杂度爆炸？我们需要```assign```操作迅速减小```set```的规模。

```
void assign(int l, int r, LL val=0)
{
	IT itl = split(l),itr = split(r+1);
	s.erase(itl, itr);
	s.insert(node(l, r, val));
}
```

一些萌新可能没有见过```erase```的这种用法，你们应该学习一个。C++98中```void erase (iterator first, iterator last)```可删除$[first,last)$区间。这里就是把$[l,r+1)$内的部分推成一段。

珂朵莉树的复杂度是由```ass```♂```ign```保证的。由于数据随机，有$\frac{1}{4}$的操作为```assign```。```set```的大小快速下降，最终趋于$\log n$，使得这种看似暴力无比的数据结构复杂度接近$m\log n$。

## 六、其他操作：一个比一个暴力

区间加：
```
void add(int l, int r, LL val=1)
{
	IT itl = split(l),itr = split(r+1);
	for (; itl != itr; ++itl) itl->v += val;
}
```

分裂出来挨个加一下就行。

区间第k小：
```
LL rank(int l, int r, int k)
{
	vector<pair<LL, int> > vp;
	IT itl = split(l),itr = split(r+1);
	vp.clear();
	for (; itl != itr; ++itl)
		vp.push_back(pair<LL,int>(itl->v, itl->r - itl->l + 1));
	sort(vp.begin(), vp.end());
	for (vector<pair<LL,int> >::iterator it=vp.begin();it!=vp.end();++it)
	{
		k -= it->second;
		if (k <= 0) return it->first;
	}
	return -1LL;
}
```
暴力取出排序就好了，反正也没有多少段。

```
LL sum(int l, int r, int ex, int mod)
{
	IT itl = split(l),itr = split(r+1);
	LL res = 0;
	for (; itl != itr; ++itl)
		res = (res + (LL)(itl->r - itl->l + 1) * pow(itl->v, LL(ex), LL(mod))) % mod;
	return res;
}
```
暴力遍历，快速幂，然后加起来。

那么，这道题就可做了。而且我们交了一发，发现这玩意跑得完全不像暴力，最慢的点是500多ms。

## 七、一些习题

UESTC的B站讲解里还有另两道题，一道是[CF915E](https://www.luogu.org/problemnew/show/CF915E)，另一道是[BZOJ4293割草](http://ruanx.pw/bzojch/p/4293.html)(权限题)。这两道题的主流做法都是线段树，珂朵莉树也可做。但珂朵莉树仍能体现出代码量较小、易查错的优势，适合作为珂朵莉树的练习题。

```
#include<cstdio>
#include<set>
#include<vector>
#include<utility>
#include<algorithm>
#define IT set<node>::iterator

using std::set;
using std::vector;
using std::pair;

typedef long long LL;
const int MOD7 = 1e9 + 7;
const int MOD9 = 1e9 + 9;
const int imax_n = 1e5 + 7;

LL pow(LL a, LL b, LL mod)
{
	LL res = 1;
	LL ans = a % mod;
	while (b)
	{
		if (b&1) res = res * ans % mod;
		ans = ans * ans % mod;
		b>>=1;
	}
	return res;
}

struct node
{
	int l,r;
	mutable LL v;
	node(int L, int R=-1, LL V=0):l(L), r(R), v(V) {}
	bool operator<(const node& o) const
	{
		return l < o.l;
	}
};

set<node> s;

IT split(int pos)
{
	IT it = s.lower_bound(node(pos));
	if (it != s.end() && it->l == pos) return it;
	--it;
	int L = it->l, R = it->r;
	LL V = it->v;
	s.erase(it);
	s.insert(node(L, pos-1, V));
	return s.insert(node(pos, R, V)).first;
}

void add(int l, int r, LL val=1)
{
	IT itl = split(l),itr = split(r+1);
	for (; itl != itr; ++itl) itl->v += val;
}

void assign_val(int l, int r, LL val=0)
{
	IT itl = split(l),itr = split(r+1);
	s.erase(itl, itr);
	s.insert(node(l, r, val));
}

LL rank(int l, int r, int k)
{
	vector<pair<LL, int> > vp;
	IT itl = split(l),itr = split(r+1);
	vp.clear();
	for (; itl != itr; ++itl)
		vp.push_back(pair<LL,int>(itl->v, itl->r - itl->l + 1));
	std::sort(vp.begin(), vp.end());
	for (vector<pair<LL,int> >::iterator it=vp.begin();it!=vp.end();++it)
	{
		k -= it->second;
		if (k <= 0) return it->first;
	}
	return -1LL;
}

LL sum(int l, int r, int ex, int mod)
{
	IT itl = split(l),itr = split(r+1);
	LL res = 0;
	for (; itl != itr; ++itl)
		res = (res + (LL)(itl->r - itl->l + 1) * pow(itl->v, LL(ex), LL(mod))) % mod;
	return res;
}

int n, m;
LL seed, vmax;

LL rnd()
{
	LL ret = seed;
	seed = (seed * 7 + 13) % MOD7;
	return ret;
}

LL a[imax_n];

int main()
{
	scanf("%d %d %lld %lld",&n,&m,&seed,&vmax);
	for (int i=1; i<=n; ++i)
	{
		a[i] = (rnd() % vmax) + 1;
		s.insert(node(i,i,a[i]));
	}
	s.insert(node(n+1, n+1, 0));
	int lines = 0;
	for (int i =1; i <= m; ++i)
	{
		int op = int(rnd() % 4) + 1;
		int l = int(rnd() % n) + 1;
		int r = int(rnd() % n) + 1;
		if (l > r)
			std::swap(l,r);
		int x, y;
		if (op == 3)
			x = int(rnd() % (r-l+1)) + 1;
		else
			x = int(rnd() % vmax) +1;
		if (op == 4)
			y = int(rnd() % vmax) + 1;
		if (op == 1)
			add(l, r, LL(x));
		else if (op == 2)
			assign_val(l, r, LL(x));
		else if (op == 3)
			printf("%lld\n",rank(l, r, x));
		else
			printf("%lld\n",sum(l, r, x, y));
	}
	return 0;
}
```

---

## 作者：Nero_Claudius (赞：26)

貌似珂朵莉树是目前为止（我学过的）唯一一个可以维护区间x次方和查询的高效数据结构。

但是这玩意有个很大的毛病，就是它的**高效**建立在数据随机的前提下。

在数据随机的时候assign操作比较多，所以它的复杂度会趋近于mlogn（m为询问次数）。假如出题人想要卡珂朵莉树的话，那肯定是会T得没边。

因此不要指望什么题目都套珂朵莉树（虽然它能水过很多数据结构题），特别是在数据非随机的情况下不要使用。

当然，如果题目让你求区间x次方和而在题目条件下你想不出巧算，那写一颗珂朵莉树还是很OK的。

------------

不得不说珂朵莉树的博客我也看了很多篇了，大家却一笔带过（可能是我太弱了）细节只讲大致框架，而某大佬在B站上的视频讲解被某不知名的管理员noip大佬喷了所以没敢去看，只好一个人颓代码。

我讲的也不一定多标准，有什么错误麻烦各位指正。

另：不太熟悉set的可以参考[这篇博客](https://www.cnblogs.com/omelet/p/6627667.html)

------------

**珂朵莉树的核心操作在于推平一个区间。**

（貌似每篇博客都说这句话）

当然事实上珂朵莉树是将所有要操作的区间整合到一起去做的，实现也可以不依赖set，比如自己写一颗fhq Treap之类的。

先讲一下大体思路：

可以发现，这里面有一个操作是推平一整段区间。

因此我们让每一个节点维护一个区间，然后对于2号操作清空区间[l,r]里的所有区间，用一个大区间[l,r]取代他们。

对于1,3,4号操作，我们暴力地找到每一个[l,r]里面的区间，然后对它们各个进行操作。

时间复杂度的证明可以参考发明者的原话：[传送门](http://codeforces.com/blog/entry/56135)(注意是第五条)

------------

珂朵莉树的节点是这样定义的：

```cpp
struct node{
	int l,r;mutable ll v;
	node(int L,int R=-1,ll V=0):l(L),r(R),v(V){}
	bool operator < (const node &o)const{
		return l<o.l;
	}
};
```

这个节点维护的是区间[l,r]，里面的每个数都初始化为v。

------------

有了基本的节点之后，通过set建立一棵树。

（set是C++自带的平衡树，但是慢到一种境界。只有在刷时限给力的题目时推荐）

```cpp
set<node> s;
```

------------

然后是很核心的split操作，这个操作如同它的名字，将一个区间拆分开来。

```cpp
#define IT set<node>::iterator
IT split(int pos){
	IT it=s.lower_bound(node(pos));
	if(it!=s.end()&&it->l==pos)return it;
	it--;
	int L=it->l,R=it->r;ll V=it->v;s.erase(it),s.insert(node(L,pos-1,V));
	return s.insert(node(pos,R,V)).first;
}
```

IT代表的玩意建议用宏，手打可以让你怀疑人生。

第一行使用了lower_bound，这个函数的作用是求前驱。

然后我们先看是否需要split这个区间，如果不需要就直接返回it。

假如现在程序还在运行，那说明我们需要split。

因此pos肯定在上一个区间里（显然），那我们把前一个彻底抹掉，然后再插入两段区间。

现在看来我们什么事情都没有做，删掉了区间又把它放回来了。

注意，其实我们并不是什么事情都没有做，因为我们在这个过程中已经拿到了需要的东西：后半段区间的迭代器（什么用后面说）

最后的返回语句可能比较玄学，事实上，set的insert操作返回一个<iterator,bool>的pair，我们只拿走第一个。

split操作就这样结束了，它的复杂度应该是log级的（set通过红黑树实现，而那玩意（我没写过）的操作据说是近似logn的）。

------------

同样核心的assign操作，是将一个区间的每一个值都设为一个值。

```cpp
void assign(int l,int r,int val=0){
	IT itl=split(l),itr=split(r+1);
	s.erase(itl,itr),s.insert(node(l,r,val));
}
```

val默认为0（因为很多时候我们直接推平）。

首先我们拿到itl和itr，这两个东西分别是split(l)与split(r+1)的返回值，看起来可能不太好理解，但是画个图似乎挺明了的。

![丑陋的配图](https://cdn.luogu.com.cn/upload/pic/29324.png)

然后我们把中间的都删除（这是erase的另一种用法，删除区间内的所有元素），用一个大区间代替所有小区间。

没了，时间复杂度很能接受。

------------

add操作，给区间每个数加上val。

```cpp
void add(int l,int r,ll val=1){
	IT itl=split(l),itr=split(r+1);
	for(;itl!=itr;++itl)itl->v+=val;
}
```

像我们之前说的那样，对于[l,r]内的所有小区间，暴力遍历一遍，给他们每一个都加上val。

可能有人会问：不会有加重复或者漏加的情况吗？

事实上不会。

漏加这个很明显是没有的，而重复加之所以没有是因为

1. 最开始没有重复。

2. 每一次推平不会产生重复。

------------

接下来是求区间k小值。

```cpp
ll rank(int l,int r,int k){
	vector<pair<ll,int> >vp;vp.clear();
	IT itl=split(l),itr=split(r+1);
	for(;itl!=itr;++itl)vp.push_back(pair<ll,int>(itl->v,itl->r-itl->l+1));
	sort(vp.begin(),vp.end());
	for(vector<pair<ll,int> >::iterator it=vp.begin();it!=vp.end();++it){
		k-=it->second;
		if(k<=0)return it->first;
	}
	return -1ll;
}
```

我们采取类似的思路：把[l,r]里面的所有元素取出来，扔到一个vector里面去。

然后给这个vector排个序。

便利一遍就可以找到最小值了。

最后的return -1ll;是特判找不到的情况，当然本题保证找得到。

------------

最后一个操作是区间x次方和，这个也十分暴力：

```cpp
ll sum(int l,int r,int ex,int mod){
	IT itl=split(l),itr=split(r+1);ll res=0;
	for(;itl!=itr;++itl)res=(res+(ll)(itl->r-itl->l+1)*power(itl->v,(ll)ex,(ll)mod))%mod;
	return res;
}
```

对于[l,r]每一个元素都暴力x次方，这个过程通过快速幂实现。

------------

然后珂朵莉树的操作基本就完了。

有人问我为什么代码都这么一样。

我也很无奈啊，只能说我学习的那篇博客和大家重复了qwq。

---

## 作者：StudyingFather (赞：25)

珂朵莉树（Chtholly Tree），又名老司机树（Old Driver Tree, ODT），是一种非常暴力的维护序列信息的数据结构。

其通过维护值相同的连续段来保证效率，在特殊构造的数据下会退化为普通暴力算法。

**注：下列代码均可以在 `C++14` 标准下编译。**

## 1 前置知识

1. 熟练掌握 `std::set` 的用法。

没了？没错。

## 2 一个例子

[CF896C](http://codeforces.com/problemset/problem/896/C) 是一个非常经典的模板题，珂朵莉树也正是来源于本题。

下面是题面部分：

> 你需要维护一个序列，并支持如下几种操作：
>
> 1. 给区间 $ [l,r] $ 内的所有数字加上 $ x $ 。
> 2. 将区间 $ [l,r] $ 内的所有数字赋值为 $ x $ 。
> 3. 求区间 $ [l,r] $ 内所有数字中第 $ x $ 小的数字（重复数字多次计算）。
> 4. 求 $ \sum_{i=l}^{r} a_i^x \bmod y $ 的值。
>
> 题目保证数据随机。

前三个操作都不算太难，使用常规的数据结构（主席树）都可以圆满解决。

问题在于第四个操作。为什么常规的数据结构在第四个操作面前无能为力呢？主要在于其并不能方便地分解为两个子区间的问题。

这时候珂朵莉树就要出场了。

## 3 ODT 的基本操作

### 3.1 节点结构

我们这样定义一个珂朵莉树的节点：

```cpp
struct node
{
 int l,r;//该节点对应的区间
 mutable long long val;
 //mutable 修饰该变量之后，就可以直接在 set 中修改该变量的值，而不是取出元素修改后再重新插入 set
 node(int L,int R=-1,long long Val=0)
 {
  l=L,r=R,val=Val;
 }
 bool operator<(const node&a)const
 {
  return l<a.l;
 }
};
```

接下来，我们定义一个 `set<node> odt` 来维护一棵 ODT。

### 3.2 分割区间操作：split

给出一个区间 $ [l,r] $ 和一个位置 $ pos $ ，怎么把这个区间分割为 $ [l,pos-1] $ 和 $ [pos,r] $ 两个区间呢？

大致流程很简单：

1. 先在 ODT 中找到含有 $ pos $ 位置的区间。
2. 如果 $ pos $ 已经是一个区间的左端点，则无需分割。
3. 否则我们把原来的区间删除，插入两个新区间。

详细代码如下：

```cpp
auto split(int pos)
{
 auto it=odt.lower_bound(node(pos));//找到左端点不小于 pos 的区间
 if(it!=odt.end()&&it->l==pos)return it;//pos 是区间左端点时无需分割
 it--;//pos 一定在前一个区间中
 int l=it->l,r=it->r;
 long long val=it->val;
 odt.erase(it);//删除原来的区间
 odt.insert(node(l,pos-1,val));
 return odt.insert(node(pos,r,val)).first;//插入两个新区间
 //这里的返回值是后半段区间对应的迭代器
}
```

经过这样的分割操作后，容易发现任意两个区间没有相交的部分，这是保证我们接下来操作正确性的前提。

### 3.3 合并区间操作：assign

如果光分割区间而不合并的话，我们事实上就是对一堆长度为 $ 1 $ 的区间进行操作，珂朵莉树也就会退化为普通暴力算法。

通过合并操作，我们可以迅速降低珂朵莉树的大小，保证珂朵莉树的效率。

这里先给出合并操作的代码：

```cpp
void assign(int l,int r,long long val)
{
 auto itr=split(r+1),itl=split(l);
 odt.erase(itl,itr);//删除[itl,itr)区间内的所有元素（注意左闭右开区间）
 odt.insert(node(l,r,val));//将原来的诸多小区间用一个大区间代替
}
```

注意：**在执行 `split` 操作时，应先 `split` 右端点，再 `split` 左端点**，否则可能会 RE。

通过两次 `split` 操作， $ [l,r] $ 区间内一定都是整段区间。因此我们可以安全地删除原来的零散区间，用大区间代替。

经过 `assign` 操作后，ODT 的规模会下降不少，从而保证 ODT 的实际运行效率。

### 3.4 其他操作

所有区间操作都可以套这样的一个模板：

1. 先 `split` 右端点，再 `split` 左端点，获得两个端点（左闭右开）的迭代器。
2. 对两个端点之间的所有区间暴力更改。

代码差不多长这样：

```cpp
void update(int l,int r)
{
 auto itr=split(r+1),itl=split(l);
 for(auto it=itl;it!=itr;it++)
  //do something
}
```

我们回到那道模板题。

首先是区间加一个值：

```cpp
void add(int l,int r,long long val)
{
 auto itr=split(r+1),itl=split(l);
 for(auto it=itl;it!=itr;it++)
  it->val+=val;//因为 val 被 mutable 关键字修饰，从而可以直接修改 set 里元素的值
}
```

接下来是区间第 $ k $ 小，暴力取出区间内所有段排序一遍即可：

```cpp
typedef pair<long long,int> pii;
long long kth(int l,int r,int k)
{
 vector<pii> a;
 auto itr=split(r+1),itl=split(l);
 for(auto it=itl;it!=itr;it++)
  a.push_back(pii(it->val,(it->r)-(it->l)+1));
 sort(a.begin(),a.end());
 for(auto it=a.begin();it!=a.end();it++)
 {
  k-=it->second;
  if(k<=0)return it->first;
 }
 return -1;
}
```

然后是区间幂次和，还是暴力，取出区间内所有段累加求和：

```cpp
long long sum(int l,int r,int x,int y)
{
 long long ans=0;
 auto itr=split(r+1),itl=split(l);
 for(auto it=itl;it!=itr;it++)
  ans=(ans+fpow(it->val,x,y)*((it->r)-(it->l)+1))%y;
 return ans;
}
```

**注意到我们的区间操作都是直接对值相同的连续段进行处理，当段数较多的时候，效率就会降低。**

模板题的完整代码如下：

```cpp
#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#define MOD 1000000007
using namespace std;
struct node
{
 int l,r;
 mutable long long val;
 node(int L,int R=-1,long long Val=0)
 {
  l=L,r=R,val=Val;
 }
 bool operator<(const node&a)const
 {
  return l<a.l;
 }
};
typedef pair<long long,int> pii;
set<node> odt;
long long a[100005],n,m,seed,vmax;
long long rnd()
{
 long long ret=seed;
 seed=(seed*7+13)%MOD;
 return ret;
}
long long fpow(long long x,long long y,long long mod)
{
 long long ans=1;
 x%=mod;
 while(y)
 {
  if(y&1)ans=ans*x%mod;
  x=x*x%mod;
  y>>=1;
 }
 return ans;
}
auto split(int pos)
{
 auto it=odt.lower_bound(node(pos));
 if(it!=odt.end()&&it->l==pos)return it;
 it--;
 int l=it->l,r=it->r;
 long long val=it->val;
 odt.erase(it);
 odt.insert(node(l,pos-1,val));
 return odt.insert(node(pos,r,val)).first;
}
void assign(int l,int r,long long val)
{
 auto itr=split(r+1),itl=split(l);
 odt.erase(itl,itr);
 odt.insert(node(l,r,val));
}
void add(int l,int r,long long val)
{
 auto itr=split(r+1),itl=split(l);
 for(auto it=itl;it!=itr;it++)
  it->val+=val;
}
long long kth(int l,int r,int k)
{
 vector<pii> a;
 auto itr=split(r+1),itl=split(l);
 for(auto it=itl;it!=itr;it++)
  a.push_back(pii(it->val,(it->r)-(it->l)+1));
 sort(a.begin(),a.end());
 for(auto it=a.begin();it!=a.end();it++)
 {
  k-=it->second;
  if(k<=0)return it->first;
 }
 return -1;
}
long long sum(int l,int r,int x,int y)
{
 long long ans=0;
 auto itr=split(r+1),itl=split(l);
 for(auto it=itl;it!=itr;it++)
  ans=(ans+fpow(it->val,x,y)*((it->r)-(it->l)+1))%y;
 return ans;
}
int main()
{
 cin>>n>>m>>seed>>vmax;
 for(int i=1;i<=n;i++)
 {
  a[i]=rnd()%vmax+1;
  odt.insert(node(i,i,a[i]));
 }
 for(int i=1;i<=m;i++)
 {
  int op=rnd()%4+1,l=rnd()%n+1,r=rnd()%n+1,x,y;
  if(l>r)swap(l,r);
  if(op==3)x=rnd()%(r-l+1)+1;
  else x=rnd()%vmax+1;
  if(op==4)y=rnd()%vmax+1;
  if(op==1)add(l,r,x);
  else if(op==2)assign(l,r,x);
  else if(op==3)cout<<kth(l,r,x)<<endl;
  else cout<<sum(l,r,x,y)<<endl;
 }
 return 0;
}
```

## 4 效率？

ODT 的做法看起来非常暴力，但是在随机数据的情况下，它的表现其实非常优秀。

我们可以证明，一个有 $n$ 个数的序列，在经过 $k$ 次**随机的**区间赋值操作后，期望段数大约在 $O(\dfrac{n}{k})$ 的级别。

证明可以点击 [这里](https://codeforces.com/blog/entry/56135?#comment-398940) 查看，这里不再展开。

在模板题中，因为数据随机，有 $\dfrac{1}{4}$ 的操作均为**随机的**区间赋值操作，因此 ODT 的实际段数很低，效率当然不错。

## 5 一点扩展

珂朵莉树并不单单只能解决序列问题，对于树上问题，可以通过重链剖分后转化为序列问题，再考虑用珂朵莉树解题。

当然珂朵莉树虽然名为树，也并不一定必须用平衡树（`std::set`）实现。

我们发现区间分裂操作就是删除一个区间，再插入两个小区间；区间合并操作就是将一些区间删掉，再插入一个更大的区间。这个操作可以使用链表来实现，效率也很不错。

## 6 总结

说了这么多，不过要注意的是：使用珂朵莉树的前提是题目有区间赋值的性质，且数据随机。

**在数据中区间赋值操作较多的时候，珂朵莉树的实际运行效率较高**。但特殊构造的数据往往并不具有这样的性质，导致其退化为普通暴力算法，因此要结合题目性质来考虑是否使用珂朵莉树来解题。

虽然事实上珂朵莉树在很多题目中都可以用其他常规数据结构代替，但其简单直接，易于调试的特点让它成为了一个解决不少题目的第二选择。

---

## 作者：灵茶山艾府 (赞：23)

## 基于链表实现的珂朵莉树

珂朵莉树实质上是一种可以维护区间上的分裂与合并的数据结构，但要求数据是随机的，或者有大量的随机合并操作，这样才能保证维护的区间个数是一个很小的值。

一开始，我们用不同的节点表示 $[1,1],[2,2],...,[n,n]$ 以及该区间上的值。

本题中的“把区间 $[l,r]$ 赋值为 $x$”对应着一个合并操作，若随机到的 $[l,r]$ 范围比较大，则意味着有大量的节点会合并成一个节点。经测试，在若干次随机合并后，**区间个数会骤降至一个稳定的范围**（大约几十个），这是理解珂朵莉树的关键。

图例：横轴为操作次数，纵轴为区间个数

![](https://cdn.luogu.com.cn/upload/image_hosting/y5roe0d7.png)

### 数据定义

目前主流的实现是基于 `set` 来维护节点，但由于平均维护的区间个数很小，`set` 的优势并不明显。相比之下，链表（或数组）能更简洁地维护分裂与合并操作。
```cpp
typedef long long int64;

struct Block {
    Block *next; // 链表下一节点
    int l, r; // 区间范围
    int64 val; // 区间上的值

    Block(Block *next, int l, int r, int64 val): next(next), l(l), r(r), val(val) {}
    bool operator<(const Block &b) const { return val < b.val; }
} *root;
```

## 基本操作

### 分裂区间

```cpp
// 返回左端点为 mid+1 的区间
Block *split(int mid) {
    for (Block *b = root; b; b = b->next) { // 遍历链表
        if (b->l == mid + 1) { // 左端点为 mid+1
            return b;
        }
        // 寻找能包含 mid 和 mid+1 的区间 [l, r]，将其被拆分成 [l, mid] 和 [mid+1, r]
        if (b->l <= mid && mid + 1 <= b->r) {
            b->next = new Block(b->next, mid + 1, b->r, b->val);
            b->r = mid;
            return b->next;
        }
    }
    return nullptr; // 未找到，返回空
}
```

在操作区间时，由于不能只维护区间的一部分，所以下面的操作进行之前都需要预先分裂区间，再完成相应操作。

```cpp
Block *lb, *rb;

// 预分裂，保证后续操作在 [l, r] 内部
void prepare(int l, int r) {
    lb = split(l - 1);
    rb = split(r);
}
```

### 合并区间

```cpp
void merge(int l, int r, int64 val) {
    prepare(l, r);
    lb->r = r; // 将区间 [lb.l, lb.r] 修改成 [lb.l, r]
    lb->val = val;
    lb->next = rb; // 将 [lb.l, r] 链至其右侧相邻区间
}
// 注：这里没有释放被删除节点的内存，若有需要可自行添加
```

### 区间修改与计算

遍历统计 $[l,r]$ 即可。

```cpp
// 区间更新
void add(int l, int r, int64 val) {
    prepare(l, r);
    for (Block *b = lb; b != rb; b = b->next)
        b->val += val;
}

// 区间第 k 小
int64 kth(int l, int r, int k) {
    prepare(l, r);
    vector<Block> blocks;
    for (Block *b = lb; b != rb; b = b->next)
        blocks.emplace_back(*b);
    sort(blocks.begin(), blocks.end());
    k--;
    for (Block b: blocks) {
        int cnt = b.r - b.l + 1;
        if (k >= cnt) k -= cnt;
        else return b.val;
    }
}

// 快速幂
int64 quick_pow(int64 x, int n, int64 mod) {
    x %= mod;
    int64 res = 1 % mod;
    for (; n; n >>= 1) {
        if (n & 1) res = res * x % mod;
        x = x * x % mod;
    }
    return res;
}

// 区间幂和
int64 pow_sum(int l, int r, int n, int64 mod) {
    prepare(l, r);
    int64 sum = 0;
    for (Block *b = lb; b != rb; b = b->next)
        sum += int64(b->r - b->l + 1) * quick_pow(b->val, n, mod);
    return sum % mod;
}
```

## AC 代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
typedef long long int64;

int64 seed;

// 生成 [0, n-1] 的随机数
int rand(int n) {
    int64 ret = seed;
    seed = (seed * 7 + 13) % int64(1e9 + 7);
    return int(ret) % n;
}

struct Block {
    Block *next;
    int l, r;
    int64 val;

    Block(Block *next, int l, int r, int64 val): next(next), l(l), r(r), val(val) {}
    bool operator<(const Block &b) const { return val < b.val; }
} *root, *lb, *rb;

Block *split(int mid) {
    for (Block *b = root; b; b = b->next) {
        if (b->l == mid + 1) {
            return b;
        }
        if (b->l <= mid && mid + 1 <= b->r) {
            b->next = new Block(b->next, mid + 1, b->r, b->val);
            b->r = mid;
            return b->next;
        }
    }
    return nullptr;
}

void prepare(int l, int r) {
    lb = split(l - 1);
    rb = split(r);
}

void add(int64 val) {
    for (Block *b = lb; b != rb; b = b->next)
        b->val += val;
}

void merge(int r, int64 val) {
    lb->r = r;
    lb->val = val;
    lb->next = rb;
}

int64 kth(int k) {
    vector<Block> blocks;
    for (Block *b = lb; b != rb; b = b->next)
        blocks.emplace_back(*b);
    sort(blocks.begin(), blocks.end());
    k--;
    for (Block b: blocks) {
        int cnt = b.r - b.l + 1;
        if (k >= cnt) k -= cnt;
        else return b.val;
    }
}

int64 quick_pow(int64 x, int n, int64 mod) {
    x %= mod;
    int64 res = 1 % mod;
    for (; n; n >>= 1) {
        if (n & 1) res = res * x % mod;
        x = x * x % mod;
    }
    return res;
}

int64 pow_sum(int n, int64 mod) {
    int64 sum = 0;
    for (Block *b = lb; b != rb; b = b->next)
        sum += int64(b->r - b->l + 1) * quick_pow(b->val, n, mod);
    return sum % mod;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, v_max;
    cin >> n >> m >> seed >> v_max;
    root = new Block(nullptr, 0, 0, rand(v_max) + 1);
    Block *b = root;
    for (int i = 1; i < n; i++) {
        b->next = new Block(nullptr, i, i, rand(v_max) + 1);
        b = b->next;
    }

    for (; m; m--) {
        int op = rand(4) + 1;
        int l = rand(n), r = rand(n);
        if (l > r) swap(l, r);
        int x = op == 3 ? rand(r - l + 1) + 1 : rand(v_max) + 1;
        prepare(l, r); // 所有操作前预分裂区间
        switch (op) {
            case 1:
                add(x);
                break;
            case 2:
                merge(r, x);
                break;
            case 3:
                cout << kth(x) << '\n';
                break;
            default:
                int64 y = rand(v_max) + 1;
                cout << pow_sum(x, y) << '\n';
        }
    }
    return 0;
}
```

---

## 作者：myEnd (赞：17)

~~这道题根据给的图片能明显看出是一道珂朵莉树~~

经典的珂朵莉树例题！
## 名称简介

老司机树，ODT（Old Driver Tree），又名珂朵莉树（ Chtholly Tree ）。起源自  CF896C （本题）。

## 前置的必会知识
由于使用到 STL 的集合，需要你会使用 `set`。

## 核心思想
把值相同的区间合并成一个结点保存在 `set` 里面。
类似于 lazytag。

## 用处
~~高情商：暴力，低情商：骗分。~~

只要是有区间赋值操作的数据结构题都可以用来骗分。在数据随机的情况下一般效率较高，但在不保证数据随机的场合下，会被精心构造的特殊数据卡到超时。

如果要保证复杂度正确，必须保证数据随机。详见 [CF(Codeforces) 上关于珂朵莉树的时间复杂度的证明](http://codeforces.com/blog/entry/56135?#comment-398940).

更详细的严格证明见 珂朵莉树的复杂度分析。对于  `add`, `assign` 和 `sum` 操作，用 `set` 实现的珂朵莉树的复杂度为 $O(n \log \log n)$ ，而用链表实现的复杂度为 $O(n \log n)$.

# 正文
首先，对于每一个区间，我们一般定义一个节点结构体：
```cpp
struct Node
{
    int l,r;
    mutable int v;
    Node(const int &il, const int &ir, const int &iv) : l(il), r(ir), v(iv) {}//构造函数
    inline bool operator<(const Node &o) const { return l < o.l; }
};
```
> `mutable` 关键字的作用是什么？


> `mutable` 是一个英语单词。他的中文意思是`可变的`，由于 `set` 本身不可以修改值，我们加上 `mutable` 关键字后让我们可以修改这个值。在 C++ 中，`mutable` 的存在其实是为了突破 `const` 的限制而设置的。被 `mutable` 修饰的变量（`mutable` 只能用于修饰类中的非静态数据成员），将永远处于可变的状态，即使在一个 `const` 函数中。

在这之后，我们有了节点结构体了，我们定义一个集合存储并维护这些节点。
```cpp
set<Node> ct;//Chtholly Tree
```
为了简化下面的代码，我们`typedef`一个`it`类型：
```cpp
typedef set<Node>::iterator it;
```
其中 `iterator` 是迭代器的意思。当然了，如果题目像本题一样支持 C++11，使用 `auto` 也是可以的。
> `iterator`(迭代器)小知识

> 在 STL 中，迭代器（Iterator）用来访问和检查 STL 容器中元素的对象，它的行为模式和指针类似，但是它封装了一些有效性检查，并且提供了统一的访问格式.类似的概念在其他很多高级语言中都存在，如 Python 的 `__iter__` 函数，C# 的 `IEnumerator`。

## split
`split` 是最核心的操作之一，它用于将原本包含点 $x$ 的区间（ 先将其设为 $[l,r]$ ）分裂为两个区间 $[l,x)$ 和 $[x,r]$ 并返回指向后者的迭代器。参考代码如下：
```cpp
it split(int x) 
{
  if (x > n) return ct.end();
  it iter = --ct.upper_bound((Node){x, 0, 0});
  if (iter->l == x) return iter;
  int l = iter->l, r = iter->r, v = iter->v;
  ct.erase(iter);
  ct.insert(Node(l, x - 1, v));
  return ct.insert(Node(x, r, v)).first;
}
```
那么 `split` 函数的具体作用是什么呢？
任何对于 $[l,r]$ 的区间操作，都可以转换成 `set` 上 $[split(l),split(r+1)]$  的操作。
## assign
刚才提到了区间赋值，这就是 `assign` 函数的作用。
对于 ODT 来说，区间操作只有这个比较特殊，也是保证复杂度的关键。如果 ODT 里全是长度为 $1$ 的区间，就成了暴力，但是有了 `assign`，可以使 ODT 的大小下降。参考代码如下：
```cpp
void assign(int l, int r, int v) 
{
  it itr = split(r + 1), itl = split(l);
  ct.erase(itl, itr);
  ct.insert(Node(l, r, v));
}
```
## 其他操作
一般更改以下模板就好啦！参考模板代码如下：
```cpp
void performance(int l, int r) 
{
  it itr = split(r + 1), itl = split(l);
  for (; itl != itr; ++itl) 
  {
    // Puts your code here!
    //这个循环迭代 [split(l),split(r+1)] 中的每一个元素
  }
}
```
注：珂朵莉树在进行求取区间左右端点操作时，必须先 `split` 右端点，再 `split` 左端点。若先 `split` 左端点，返回的迭代器可能在 `split` 右端点的时候失效，可能会导致 RE。
## 对于本题的其他操作
### 1.区间+
直接改模板就好啦！参考代码如下所示：
```cpp
void add(int l, int r,int v) 
{
  it itr = split(r + 1), itl = split(l);
  for (; itl != itr; ++itl) 
  {
    itl->v += v;//由于我们的v声明时使用了mutable关键字，直接更改即可
  }
}
```
### 2.区间第k小
这个我们可以先定义一个 `vector` 动态数组存储区间 $[l,r]$ 的每一个元素， 之后直接对这个 `vector` 数组排序，然后访问第k小元素即可。对于 `vector` 存储的类型，我们可以存 `pair`，`first` 存值，`second` 存这个元素在珂朵莉树里的位置，刚好可以使用 STL 的 `sort` 函数（算法头文件有定义 `pair` 的小于号,比较 `first` 元素的大小 ）。 参考代码如下：
```cpp
inline int kth(int l,int r,int k)
{
   vector< pair<int,int> > a;
   it itr=split(r+1),itl=split(l);
   for(it iter=itl;iter!=itr;iter++)
      a.push_back(pair<int,int>(iter->v,(iter->r)-(iter->l)+1));//使用pair的构造函数
   sort(a.begin(),a.end());
   for(vector< pair<int,int> >::iterator iter=a.begin();iter!=a.end();iter++)
   {
      k-=iter->second;
      if(k<=0)return iter->first;
   }
   return -1;
}
```
### 3.区间次幂和
同样还是暴力，不过比区间第k小相对简单，我们直接取出每个值之后相加就可以。  参考代码如下：
```cpp
long long fpow(long long x,long long y,long long mod)
{
    long long ans=1;
    x%=mod;
    while(y) //快速幂
    {
        if(y&1)ans=ans*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return ans;
}
int sum(int l,int r,int x,int y)
{
   int ans=0;
   it itr=split(r+1),itl=split(l);
   for(it it=itl;it!=itr;it++)
      ans=(ans+fpow(it->v,x,y)*((it->r)-(it->l)+1))%y;//注意使用fpow函数，这个函数是我们自己定义的快速幂。
   return ans;
}
```
## 注意事项
我们的区间操作都是直接对值相同的连续段进行处理，当段数较多的时候，效率就会降低。

## 参考代码
```cpp
#include <set>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;
#define int long long 
struct Node
{
    int l,r;
    mutable int v;
    Node(const int &il, const int &ir, const int &iv) : l(il), r(ir), v(iv) {}//构造函数
    inline bool operator<(const Node &o) const { return l < o.l; }
};
set<Node> ct;//Chtholly Tree
#define S ct
long long n, m, seed, vmax;
typedef set<Node>::iterator it;
it split(int x)
{
    if (x > n) return ct.end();
    it iter = --ct.upper_bound((Node){x, 0, 0});
    if (iter->l == x) return iter;
    int l = iter->l, r = iter->r, v = iter->v;
    ct.erase(iter);
    ct.insert(Node(l, x - 1, v));
    return ct.insert(Node(x, r, v)).first;
}
void assign(int l, int r, int v) 
{
    it itr = split(r + 1), itl = split(l);
    ct.erase(itl, itr);
    ct.insert(Node(l, r, v));
}
void add(int l, int r,int v) 
{
    it itr = split(r + 1), itl = split(l);
    for (; itl != itr; ++itl) 
    {
        itl->v += v;//由于我们的v声明时使用了mutable关键字，直接更改即可
    }
}
inline int kth(int l,int r,int k)
{
    vector< pair<int,int> > a;
    it itr=split(r+1),itl=split(l);
    for(it iter=itl;iter!=itr;iter++)
        a.push_back(pair<int,int>(iter->v,(iter->r)-(iter->l)+1));//使用pair的构造函数
    sort(a.begin(),a.end());
    for(vector< pair<int,int> >::iterator iter=a.begin();iter!=a.end();iter++)
    {
        k-=iter->second;
        if(k<=0)return iter->first;
    }
    return -1;
}
long long fpow(long long x,long long y,long long mod)
{
    long long ans=1;
    x%=mod;
    while(y) //快速幂
    {
        if(y&1)ans=ans*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return ans;
}
int sum(int l,int r,int x,int y)
{
    int ans=0;
    it itr=split(r+1),itl=split(l);
    for(it it=itl;it!=itr;it++)
        ans=(ans+fpow(it->v,x,y)*((it->r)-(it->l)+1))%y;//注意使用fpow函数，这个函数是我们自己定义的快速幂。
    return ans;
}

long long a[100010];
inline long long rnd() 
{
    long long ret = seed;
    seed = (seed * 7LL + 13) % 1000000007LL;
    return ret;
}
signed main()
{
    ct.clear();
    cin>>n>>m>>seed>>vmax;
    for(int i = 1; i <= n; ++i)
    {
        a[i] = (rnd()%vmax) + 1;
        S.insert(Node(i, i, a[i]));
    }
    S.insert(Node(n+1,n+1,0));
    for(int i = 1; i <= m; ++i)
    {
        long long op = rnd()%4 + 1;
        long long l = rnd() % n + 1, r = rnd() % n + 1;
        if(l > r)
        {
            long long tmp = l;
            l = r;
            r = tmp;
        }
        long long x, y;
        if(op == 3)
        {
            x = rnd() % (r - l + 1) + 1;
        }
        else
        {
            x = rnd() % vmax + 1;
        }
        if(op == 4)
        {
            y = rnd() % vmax + 1;
        }
        if(op == 1)  add(l, r, x);
        else if(op == 2)  assign(l, r, x);
        else if(op == 3)  printf("%lld\n", kth(l, r, x));
        else if(op == 4)  printf("%lld\n", sum(l, r, x, y));
    }
    return 0;
}
```

## 写在最后
以上就是关于本道 ODT/珂朵莉树 模板题题解的全部内容啦！祝你能够通过自己的能力通过本题，不要抄袭。

新人第一次写题解，若有不足请见谅。

---

## 作者：mzgwty (赞：14)

来一篇比较水的题解

~~据说本题是ODT这个数据结构的开端,出题人居然能自造数据结构也是够强的了~~

~~说实话，看题解前我以为这是带修莫队，不过这都是很久以前的事了~~

咳咳，言归正传

这题一共有4种操作

1.区间加

2.区间赋值

3.区间第K大

4.区间N次方和？

如果只看前三种操作，估计有同学会想到用主席树来维护~~但我不会QAQ~~，但对于第四种操作我们却无从下手。

于是......~~暴力啊~~

直接暴力乱搞，这样会拿到一个还看得下去的分数

但有没有方法优化一下暴力呢？

于是，诸多神仙就发明了这个数据结构————珂朵莉树

学完这个数据结构后，你应该会掌握：

1.能够快速解决询问区间N次方和的问题

2.在数据随机并带有区间赋值的情况下用它来A题

3.优化暴力，骗取一点分数

~~4.在构造数据下不要用这个玩意儿~~

开始吧

## 一、节点

珂朵莉树首先节点非常玄学,它储存的是一个区间，并且这个区间所有节点的权值相同

比如：

$l:1 \ r:4 \ val:4$

$l:5 \ r:5 \ val:1$

这就是两个节点

看上去好像和树没有一点关系，但因为它的节点是储存在$set$里面的，而$set$又是平衡树实现的，所以它也是树辣

结构体就这样

```cpp
struct node {
	int lft,rht;
	mutable ll val;
	node (int l,int r=-1,ll v=0) :lft(l),rht(r),val(v) {}
	bool operator < (node a) const {
		return lft<a.lft;
	}
};
```

小于符号是弄$set$必备的，这是指每个区间按左端点递增来排成的

```cpp
set <node> s;
```

## 二、初始化

这个题的初始化很简单

直接把每个节点先孤立起来，直接插入$set$就好了

```cpp
for(register int i=1 ; i<=n ; ++i) s.insert(node(i,i,rnd()%vmax+1));
```

## 三、split操作

```cpp
#define IT set<node>::iterator
```

这个函数$split(pos)$的意思就是把包含pos这个位置的节点分成左段$l$到$pos-1$,右段$pos$到$r$，并返回右段地址

这个应当一句一句解释

```cpp
inline IT split(int pos) {
	IT it=s.lower_bound(node(pos));//找到第一个左端点大于等于pos的节点
	if(it!=s.end()&&it->lft==pos) return it;//这是指这个节点在set内并且这个节点的左端点下标就是pos，那么我们就可以直接返回该节点，因为它不必再分成两段，已经分好了
	--it;//否则pos就在它前面的那个节点
	int l=it->lft,r=it->rht;
	ll v=it->val;
	s.erase(it);//先在set里删除这个节点
	s.insert(node(l,pos-1,v));//然后再插入节点l到pos-1
	return s.insert(node(pos,r,v)).first;//最后插入节点pos到r并返回下标
}
```
这段代码是借鉴了 SuperJvRuo 的

剩下的一切区间操作，我们都可以很容易解决了

1.区间赋值

先分离出l到r的所有节点，然后删除它们，再新建一个l到r，权值为v的节点

```cpp
inline void assign(int l,int r,ll v) {
	IT itr=split(r+1),itl=split(l);
	s.erase(itl,itr);
	s.insert(node(l,r,v));
}
```
2.区间加

同样，先分离出l到r的所有节点，然后把每个节点的权值都加上v

```cpp
inline void add(int l,int r,ll v) {
	IT itr=split(r+1),itl=split(l);
	while(itl!=itr) itl->val+=v,++itl;
}
```

3.区间第k小

先分离，再把节点按权值从小到大排，每遍历到一个节点，就将k减去它的长度，如果k小于等于0，则当前节点的权值即是第k小值

刚开始因打了万能头且将r小写，我就挂了，CE了，还被这个巨佬嘲讽了，@ThomasX

```cpp
inline ll Rank(int l,int r,int k) {
	vector < pair<ll,int> > v;
	IT itr=split(r+1),itl=split(l);
	v.clear();
	while(itl!=itr) v.push_back(make_pair(itl->val,(itl->rht)-(itl->lft)+1)),++itl;
	sort(v.begin(),v.end());
	for(register vector< pair<ll,int> >::iterator it=v.begin() ;it!=v.end() ; ++it) {
		k-=it->second;
		if(k<=0) return it->first;
	}
	return -1;
}
```

4.区间N次方和

先分离，再遍历节点，将ans加上权值的N次方乘以节点表示的区间长度，输出即可

要用快速幂哦~~本蒟蒻因快速幂写错而调了半小时~~

```cpp
inline ll sum(int l,int r,ll x,ll y) {
	IT itr=split(r+1),itl=split(l);
	ll ans=0;
	while(itl!=itr) {
		ans+=((itl->rht)-(itl->lft)+1)*qpow(itl->val,x,y)%y;
		ans%=y;++itl;
	}
	return ans;
}
```
 
## 完结 hhh，挺水的
 
```cpp
#include<bits/stdc++.h>
#include<vector>
#include<set>
#include<algorithm>
#define IT set<node>::iterator
#define ll long long
using namespace std;

inline ll read() {
	ll res=0,f=1;char ch;
	while(!isdigit(ch=getchar())) if(ch=='-') f=-1;
	do {
		res=res*10+ch-'0';
	} while(isdigit(ch=getchar()));
	return res*f;
}

inline ll qpow(ll a,ll b,ll p) {
	ll ans=1,base=a%p;
	while(b) {
		if(b&1) ans=(ans*base)%p;
		base=(base*base)%p;
		b>>=1;
	}
	return ans;
}

ll seed,vmax,mod=1e9+7;

inline int rnd() {
	ll ret=seed;
	seed=(seed*7+13)%mod;
	return ret;
}

struct node {
	int lft,rht;
	mutable ll val;
	node (int l,int r=-1,ll v=0) :lft(l),rht(r),val(v) {}
	bool operator < (node a) const {
		return lft<a.lft;
	}
};

set <node> s;

inline IT split(int pos) {
	IT it=s.lower_bound(node(pos));
	if(it!=s.end()&&it->lft==pos) return it;
	--it;
	int l=it->lft,r=it->rht;
	ll v=it->val;
	s.erase(it);
	s.insert(node(l,pos-1,v));
	return s.insert(node(pos,r,v)).first;
}

inline void assign(int l,int r,ll v) {
	IT itr=split(r+1),itl=split(l);
	s.erase(itl,itr);
	s.insert(node(l,r,v));
}

inline void add(int l,int r,ll v) {
	IT itr=split(r+1),itl=split(l);
	while(itl!=itr) itl->val+=v,++itl;
}

inline ll Rank(int l,int r,int k) {
	vector < pair<ll,int> > v;
	IT itr=split(r+1),itl=split(l);
	v.clear();
	while(itl!=itr) v.push_back(make_pair(itl->val,(itl->rht)-(itl->lft)+1)),++itl;
	sort(v.begin(),v.end());
	for(register vector< pair<ll,int> >::iterator it=v.begin() ;it!=v.end() ; ++it) {
		k-=it->second;
		if(k<=0) return it->first;
	}
	return -1;
}

inline ll sum(int l,int r,ll x,ll y) {
	IT itr=split(r+1),itl=split(l);
	ll ans=0;
	while(itl!=itr) {
		ans+=((itl->rht)-(itl->lft)+1)*qpow(itl->val,x,y)%y;
		ans%=y;++itl;
	}
	return ans;
}

int main() {
	ll n=read(),m=read();seed=read(),vmax=read();
	for(register int i=1 ; i<=n ; ++i) s.insert(node(i,i,rnd()%vmax+1));
	while(m--) {
		ll op=(rnd()%4)+1,l=(rnd()%n)+1,r=(rnd()%n)+1,x,y;
		if(l>r) swap(l,r);
		if(op==1) {
			x=(rnd()%vmax)+1;
			add(l,r,1LL*x);
		}
		else if(op==2) {
			x=(rnd()%vmax)+1;
			assign(l,r,1LL*x);
		}
		else if(op==3) {
			x=(rnd()%(r-l+1))+1;
			printf("%lld\n",Rank(l,r,x));
		}
		else {
			x=(rnd()%vmax)+1,y=(rnd()%vmax)+1;
			printf("%lld\n",sum(l,r,x,y));
		}
	}
	return 0;
}
```

---

## 作者：Blaze (赞：13)

从题目名字可以看出这题要使用一种神奇的数据结构就是**珂朵莉树**！

### 1. 珂朵莉树的原理

**将序列拆成区间来~~暴力~~维护。**

如: $1, 3, 3, 4, 7, 2, 2, 2$

会被拆成(其中一种拆法)：

$[1,1]:1,[2,3]:3,[4,4]:4,[5,5]:7,[6,8]:2$

但也有可能会会被拆成(这也正是珂朵莉树会被卡的原因之一)：

$[1,1]:1,[2,2]:3,[3,3]:3,[4,4]:4,[5,5]:5,[6,6]:2,[7,7]:2,[8,8]:8$
### 2. 珂朵莉树的适用范围

**题目数据随机且有区间修改操作(如本题)或者对拍(因为好打)~~以及骗分~~。**
### 3. 珂朵莉树的节点

```cpp
template<typename _Tp> //要维护信息的类型
struct chtholly_node   //珂朵莉树的节点
{
  typedef _Tp value;   //重命名_Tp为value
  mutable int l, r;    //要维护的区间[l, r]
  mutable value v;     //整个区间[l, r]上序列所共有的值
  chtholly_node(int L, int R, value x) : l(L), r(R), v(x) { };
  bool operator<(const chtholly_node &x) const
  { return l < x.l; }  //按左端点从小到大排序
};
```
每个节点维护一段区间$[l,r]$及其上的值$v$(注意区间不能相交)。(注：下面不再区分节点和区间，即区间有可能是节点，节点也有可能是区间，需结合自己理解。)

### 4. 珂朵莉树的构造

```cpp
template<typename _Tp> //要维护信息的类型
struct chtholly_tree : public set<chtholly_node<_Tp> >
{
  //重命名
  typedef _Tp value;
  typedef chtholly_node<value> node;
  typedef typename set<chtholly_node<value> >::iterator it;
  //操作
  it split(int pos);
  void assign(int l, int r, value x);
};
```
珂朵莉树继承了set,使得可以像使用set一样使用它，并重命名了一些冗长的数据类型，以及附加了两个新操作。

### 5. 珂朵莉树的操作

1. **it split(int pos)**

 ```cpp
 template<typename _Tp>
 typename chtholly_tree<_Tp>::it chtholly_tree<_Tp>::split(int pos)
 {
     it itl = this->lower_bound(node(pos, -1, value()));
     if(itl != this->end() && itl->l == pos) return itl; --itl;
     it itr = this->insert(node(pos, itl->r, itl->v)).first; itl->r = pos - 1;
     return itr;
 }
 ```
 作用：将$pos$所在的区间$[l,r]$分成$[l,pos-1]$和$[pos,r]$并返回$[pos,r]$所在的迭代器(若$pos = l$则返回$[l,r]$所在的迭代器)。

 内容：首先 **lower_bound(node(pos, -1, value())** 返回左端点大于等于$pos$且最小的区间所在的迭代器并赋给迭代器$itl$，然后判断$itl$所指区间的左端点是否等于$pos$，如果是的就直接返回$itl$即区间$[l,r]$所在的迭代器，否则就跳到上一个迭代器(即左端点小于$pos$且最大的区间所在的迭代器)，接着 **insert(node(pos, itl->r, itl->v)).first** 会复制区间$[l,r]$上的$[pos,r]$并插入且返回$[pos,r]$所在的迭代器赋给$itr$，此时只需将$itl$所指的区间$[l,r]$改为$[l,pos-1]$即将$r$改为$pos-1$即可，最后返回$itr$即$[pos,r]$所在的区间。

2. **void assign(int l, int r, value x)**

 ```cpp
 template<typename _Tp>
 void chtholly_tree<_Tp>::assign(int l, int r, value x)
 {
     it itl = this->split(l), itr = this->split(r + 1);
     this->erase(itl, itr); this->insert(node(l, r, x));
 }
 ```
 作用：将区间$[l,r]$上的序列所共有的值修改为$x$。

 内容：首先 **split(l)** 返回一个以$l$为左端点的区间的迭代器赋给$itl$, **split(r + 1)** 返回一个以$r + 1$为左端点的区间的迭代器赋给$itr$, 然后 **erase(itl, itr)** 会删除所有左端点在区间$[l,r + 1)$即$[l,r]$的区间即删除区间$[l,r]$上的整个序列， 接着 **insert(node(l, r, x))** 会插入一个序列所共有的值为$x$的区间$[l,r]$。

**注意：请确保调用 split 和 assign 时 chtholly_tree 不为空。**

### 6.珂朵莉树的声明

一维：
```cpp
//重命名
typedef long long value;
typedef chtholly_tree<value> tree;
typedef tree::node node;
typedef tree::it it;
//声明
tree T;
```
二维：
```cpp
//重命名
typedef long long value;
typedef chtholly_tree<chtholly_tree<value> > tree;
//声明
tree T; //跟一维差不多的用法
```
### 7. 珂朵莉树的初始化

```cpp
for(int i = 1; i <= n; i++)
  T.insert(node(i, i, rnd() % vmax + 1));
```
注：如果一开始序列是空的那么就 **T.insert(l, r, v)** 其中$[l,r]$为全域大小，$v$为一个空值，如 **T.insert(0, (int)1e9, 0)** 。

### 8. 珂朵莉树的~~暴力~~维护

1. **区间加**

 ```cpp
 //将[l,r]区间所有数加上x
 void add(int l, int r, value x)
 {
     it itl = T.split(l), itr = T.split(r + 1);
     for(; itl != itr; ++itl) itl->v += x;
 }
 ```
 直接将左端点在$[l,r)$的区间中最左边的区间依次加到最右边的区间。

2. **区间修改**

 ```cpp
 //将[l,r]区间所有数改成x
 void change(int l, int r, value x)
 { T.assign(l, r, x); }
```
 
 调用 **assign** 直接修改

3. **区间第k小**

 ```cpp
 //将[l,r]区间从小到大排序后的第x个数是的多少
 value select(int l, int r, value x)
 {
     it itl = T.split(l), itr = T.split(r + 1);
     vector<pair<value, int> > vp;
     for (; itl != itr; ++itl)
       vp.push_back(pair<value,int>(itl->v, itl->r - itl->l + 1));
      std::sort(vp.begin(), vp.end());
     for(vector<pair<value,int> >::iterator it = vp.begin(); it != vp.end(); ++it)
       if((x -= it->second) <= 0)
         return it->first;
     return -1;
 }
```

 将左端点在$[l,r)$的区间中最左边的区间到最右边的区间依次复制到 **vector** 里，排序，顺次找到第k小(注意：**vector** 里保存的是区间)。

4. **区间幂次和**

 ```cpp
 //快速幂
 value pow(value x, value y, value m)
 {
     value res = 1, ans = x % m;
     while(y)
     {
       if(y & 1) res = res * ans % m;
       ans = ans * ans % m;
       y >>= 1;
     }
     return res;
 }
 //返回[l,r]区间每个数字的x次方的和模y的值
 value sum(int l, int r, value x, value y)
 {
     it itl = T.split(l), itr = T.split(r + 1);
     value res = 0;
     for(; itl != itr; ++itl)
       res = (res + (itl->r - itl->l + 1) * pow(itl->v, x, y)) % y;
     return res;
 }
 ```

 将左端点在$[l,r)$的区间中最左边的区间到最右边的区间依次快速幂累加即可。

### 9. 珂朵莉树的时间复杂度

记 $m$为区间数即**T.size()**。

1. 对于随机的$l$和$r$其区间$[l,r]$的平均长度为$\frac{n-1}{3}$

 证明：$\overline{x} = \frac{\sum_{l=1}^{n}\sum_{r=l}^{n}(r-l)}{\sum_{l=1}^{n}\sum_{r=l}^{n}1}=\frac{\frac{1}{2}\sum_{l=1}^{n}(\sum_{l=1}^{n}l^2-(2n+1)\sum_{l=1}^{n}l+n^3+n^2)}{\frac{1}{2}n(n+1)} =\frac{\frac{2}{3}n(n+1)(n-1)}{\frac{1}{2}n(n+1)}=\frac{n-1}{3}$

2. $m$(平均值)的上界为$(log_\frac{3}{2}4)(log_2n)$~~因为准确界我求不出来~~
 
 由于$m$与$n$对应，每次 **assign** 均会使得$m$变为$\frac{2}{3}m+\frac{2}{3}$且有概率在$l$及$r$上分裂出两个新区间，又因为只需求出$m$(平均值)的上界于是我们可以使得每次 **assign** 均会使得$m$变为$\frac{2}{3}m$，且永久地增加两个区间，可知进行$k$次操作后$m$变为$(\frac{2}{3})^km$有$1=(\frac{2}{3})^km$即$k=log_\frac{3}{2}m$，于是最终会有$2k$即$2log_\frac{3}{2}m$个区间，由初始条件$m=n$得出在进行足够多的 **assign** 情况下$m$(平均值)的上界为$2log_\frac{3}{2}n$即$(log_\frac{3}{2}4)(log_2n)$。(经过测试$m$的收敛速度远没有上述那么快($n=1e8$时大约要$1e6$次 **assign** 操作$m$(平均值)才会基本上不会变动)，另外$m$(平均值)的值大约在$\frac{3}{2}log_2n$左右)。

3. **split** 的均摊时间复杂度为$O(log_2log_2n)$

 由 **split** 的时间复杂度为$O(log_2m)$可知 **split** 的均摊时间复杂度为$O(log_2log_2n)$。

4. **assign** 的均摊时间复杂度为$O(log_2log_2n)$

 由 **assign** 的时间复杂度为$O(log_2m)$可知 **assign** 的均摊时间复杂度为$O(log_2log_2n)$。

5. **add** 的均摊时间复杂度为$O(log_2n)$

 由 **add** 的时间复杂度为$O(m)$可知 **add** 的均摊时间复杂度为$O(log_2n)$。

6. **change** 的均摊时间复杂度为$O(log_2log_2n)$

 由 **change** 的时间复杂度为$O(log_2m)$可知 **change** 的均摊时间复杂度为$O(log_2log_2n)$。

7. **select** 的均摊时间复杂度为$O((log_2n)(log_2log_2n))$

 由 **select** 的时间复杂度为$O(mlog_2m)$可知 **select** 的均摊时间复杂度为$O((log_2n)(log_2log_2n))$。

8. **sum** 的均摊时间复杂度为$O(log_2n)$

 由 **pow** 的时间复杂度为$O(1)$(全域为$[1,1e9]$)，
 
 及 **sum** 的时间复杂度为$O(m)$可知 **sum** 的均摊时间复杂度为$O(log_2n)$。

**从此可以看出珂朵莉树的时间复杂度完全是由随机的 assign 操作保证的，这也就导致了珂朵莉树的适用范围狭小。**

### 10.珂朵莉树的参考程序

```cpp
#include<algorithm>
#include<iostream>
#include<vector>
#include<set>
using namespace std;

//珂朵莉树的节点
template<typename _Tp>
struct chtholly_node
{
  typedef _Tp value;
  mutable int l, r;
  mutable value v;
  chtholly_node(int L, int R, value x) : l(L), r(R), v(x) { }
  bool operator<(const chtholly_node& x) const { return l < x.l; }
};

//珂朵莉树的构造
template<typename _Tp>
struct chtholly_tree : public set<chtholly_node<_Tp> >
{
  typedef _Tp value;
  typedef chtholly_node<value> node;
  typedef typename set<chtholly_node<value> >::iterator it;
  
  //珂朵莉树的操作
  it split(int pos)
  {
    it itl = this->lower_bound(node(pos, -1, value()));
    if(itl != this->end() && itl->l == pos) return itl; --itl;
    it itr = this->insert(node(pos, itl->r, itl->v)).first; itl->r = pos - 1;
    return itr;
  }
  void assign(int l, int r, value x)
  {
    it itl = this->split(l), itr = this->split(r + 1);
    this->erase(itl, itr); this->insert(node(l, r, x));
  }
};

//珂朵莉树的声明
typedef long long value;
typedef chtholly_tree<value> tree; typedef tree::node node; typedef tree::it it;
tree T;

//珂朵莉树的维护
void add(int l, int r, value x)
{
  it itl = T.split(l), itr = T.split(r + 1);
  for(; itl != itr; ++itl) itl->v += x;
}
void change(int l, int r, value x)
{ T.assign(l, r, x); }
value select(int l, int r, value x)
{
  it itl = T.split(l), itr = T.split(r + 1);
  vector<pair<value, int> > vp;
  for (; itl != itr; ++itl)
    vp.push_back(pair<value, int>(itl->v, itl->r - itl->l + 1));
  std::sort(vp.begin(), vp.end());
  for(vector<pair<value, int> >::iterator it = vp.begin(); it != vp.end(); ++it)
    if((x -= it->second) <= 0)
      return it->first;
  return -1;
}
value pow(value x, value y, value m)
{
  value res = 1, ans = x % m;
  while(y)
  {
    if(y & 1) res = res * ans % m;
    ans = ans * ans % m;
    y >>= 1;
  }
  return res;
}
value sum(int l, int r, value x, value y)
{
  it itl = T.split(l), itr = T.split(r + 1);
  value res = 0;
  for(; itl != itr; ++itl)
    res = (res + (itl->r - itl->l + 1) * pow(itl->v, x, y)) % y;
  return res;
}

value n, m, seed, vmax;
value rnd()
{ value ret = seed; seed = (seed * 7 + 13) % 1000000007; return ret; }

int main(int argc, char* argv[])
{
  cin >> n >> m >> seed >> vmax;
  value op, l, r, x, y;
  
  //珂朵莉树的初始化
  for(int i = 1; i <= n; i++) T.insert(node(i, i, rnd() % vmax + 1));
  
  for(int i = 1; i <= m; i++)
  {
    op = rnd() % 4 + 1; l = rnd() % n + 1; r = rnd() % n + 1;
    if(l > r) swap(l, r);
    if(op == 3) x = rnd() % (r - l + 1) + 1;
    else x = (rnd() % vmax) + 1;
    if(op == 4) y = rnd() % vmax + 1;
    switch(op)
    {
    case 1:
      add(l, r, x);
      break;
    case 2:
      change(l, r, x);
      break;
    case 3:
      cout << select(l, r, x) << endl;
      break;
    case 4:
      cout << sum(l, r, x, y) << endl;
      break;
    }
  }
  return 0;
}
```


---

## 作者：Bring (赞：12)

[更好的阅读体验请点这里](https://www.cnblogs.com/BrianPeng/p/12356392.html)

### Intro: 

~~珂朵莉树模板题~~

怎么所有题解都是珂朵莉树啊啊啊啊

### 于是本蒟蒻决定来一发中(feng)规(kuang)中(luan)矩(gao)的线段树

首先这棵线段树**只维护懒标记**

### 来一发定义

线段树节点$u$维护区间$[l_u,r_u]$的内容

**懒标记**$t_u$：当$t_u\not=0$时表示区间$[l_u,r_u]$全是$t_u$，$t_u=0$就是没有懒标记

---

### 建立线段树

在建立时顺便处理$l_u,r_u$，只要当$l_u=r_u$时就打上标记

P.s $Ls=2u,Rs=2u+1$

```cpp
void bld(int u){
	if(t[u].l==t[u].r){t[u].v=rnd()%vmx+1;return;}
	t[Ls].l=t[u].l,t[Rs].l=(t[Ls].r=(t[u].l+t[u].r)>>1)+1,t[Rs].r=t[u].r;
	bld(Ls),bld(Rs);
}
```

### 区间加

找到所有被覆盖且有标记的区间，让$t_u$加上$x$

P.s Don't forget **pushdown()**.

```cpp
void pd(int u){if(t[u].v)t[Ls].v=t[Rs].v=t[u].v,t[u].v=0;}
void mdfa(int u){
	if(r<t[u].l||t[u].r<l)return;
	if(l<=t[u].l&&t[u].r<=r&&t[u].v)t[u].v+=x;
	else pd(u),mdfa(Ls),mdfa(Rs);
}
```
### 区间设置

与一般懒标记操作最为类似，找到覆盖区间，打上标记即可

```cpp
void mdfs(int u){
	if(r<t[u].l||t[u].r<l)return;
	if(l<=t[u].l&&t[u].r<=r)t[u].v=x;
	else pd(u),mdfs(Ls),mdfs(Rs);
}
```

### 区间查询

在这里我们借助一个 vector

```cpp
struct Q{int v,s;};
vector<Q>q;
```
其中$v$表示区间值，$s$表示区间长度

首先把所有**有交集**且有标记的区间全部存到这个 vector 里（注意$s$的处理）

```cpp
void qry(int u){
	if(r<t[u].l||t[u].r<l)return;
	if(t[u].v)q.push_back({t[u].v,min(t[u].r,r)-max(t[u].l,l)+1});
	else qry(Ls),qry(Rs);
}
```

那么对于区间第$x$小，将$q$按$v$排序，然后暴力即可 ~~（vector 真好用）~~

```cpp
q.clear(),qry(1);
sort(q.begin(),q.end(),[](Q a,Q b){return a.v<b.v;});
for(Q i:q){
	if(x<=i.s){wr(i.v),Pe;break;}
	x-=i.s;
}
```

对于区间幂次和，排序都不用了，**直接暴扫** ~~（这么感觉和珂朵莉树一副德行）~~

```cpp
ans=0,y=rnd()%vmx+1,q.clear(),qry(1);
for(Q i:q)ans=(ans+i.s*fpw(i.v,x)%y)%y;
wr(ans),Pe;
```

**Time complexity:** $O($玄学$)$（大雾

**Memory complexity:** $O(n)$

附上总代码（$10.60$s / $9.05$MB）

~~（打的比珂朵莉树难，空间比珂朵莉树大，跑的比珂朵莉树慢）~~

```cpp
//This program is written by Brian Peng.
#pragma GCC optimize("Ofast","inline","no-stack-protector")
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define Rd(a) (a=read())
#define Gc(a) (a=getchar())
#define Pc(a) putchar(a)
int read(){
	int u;char c(getchar());bool k;
	while(!isdigit(c)&&c^'-')if(Gc(c)==EOF)exit(0);
	if(c^'-')k=1,u=c&15;else k=u=0;
	while(isdigit(Gc(c)))u=(u<<1)+(u<<3)+(c&15);
	return k?u:-u;
}
void wr(int a){
	if(a<0)Pc('-'),a=-a;
	if(a<=9)Pc(a|'0');
	else wr(a/10),Pc((a%10)|'0');
}
signed const INF(0x3f3f3f3f),NINF(0xc3c3c3c3);
long long const LINF(0x3f3f3f3f3f3f3f3fLL),LNINF(0xc3c3c3c3c3c3c3c3LL);
#define Ps Pc(' ')
#define Pe Pc('\n')
#define Frn0(i,a,b) for(int i(a);i<(b);++i)
#define Frn1(i,a,b) for(int i(a);i<=(b);++i)
#define Frn_(i,a,b) for(int i(a);i>=(b);--i)
#define Mst(a,b) memset(a,b,sizeof(a))
#define File(a) freopen(a".in","r",stdin),freopen(a".out","w",stdout)
#define N (262150)
#define Ls (u<<1)
#define Rs (Ls|1)
int n,m,sd,vmx,op,l,r,x,y,ans;
struct SgT{int l,r,v;}t[N];
struct Q{int v,s;};
vector<Q>q;
int rnd(){int r(sd);sd=(sd*7+13)%1000000007;return r;}
void pd(int u){if(t[u].v)t[Ls].v=t[Rs].v=t[u].v,t[u].v=0;}
void bld(int u);
void mdfa(int u);
void mdfs(int u);
void qry(int u);
int fpw(int a,int b){int r(1);a%=y;while(b)b&1?r=r*a%y:0,a=a*a%y,b>>=1;return r;}
signed main(){
	t[1].l=1,t[1].r=Rd(n),Rd(m),Rd(sd),Rd(vmx);
	bld(1);
	while(m--){
		op=rnd()%4+1,l=rnd()%n+1,r=rnd()%n+1;
		if(l>r)swap(l,r);
		x=rnd()%(op==3?r-l+1:vmx)+1;
		switch(op){
			case 1:mdfa(1);break;
			case 2:mdfs(1);break;
			case 3:q.clear(),qry(1);
				sort(q.begin(),q.end(),[](Q a,Q b){return a.v<b.v;});
				for(Q i:q){
					if(x<=i.s){wr(i.v),Pe;break;}
					x-=i.s;
				}break;
			case 4:ans=0,y=rnd()%vmx+1,q.clear(),qry(1);
				for(Q i:q)ans=(ans+i.s*fpw(i.v,x)%y)%y;
				wr(ans),Pe;break;
		}
	}
	exit(0);
}
void bld(int u){
	if(t[u].l==t[u].r){t[u].v=rnd()%vmx+1;return;}
	t[Ls].l=t[u].l,t[Rs].l=(t[Ls].r=(t[u].l+t[u].r)>>1)+1,t[Rs].r=t[u].r;
	bld(Ls),bld(Rs);
}
void mdfa(int u){
	if(r<t[u].l||t[u].r<l)return;
	if(l<=t[u].l&&t[u].r<=r&&t[u].v)t[u].v+=x;
	else pd(u),mdfa(Ls),mdfa(Rs);
}
void mdfs(int u){
	if(r<t[u].l||t[u].r<l)return;
	if(l<=t[u].l&&t[u].r<=r)t[u].v=x;
	else pd(u),mdfs(Ls),mdfs(Rs);
}
void qry(int u){
	if(r<t[u].l||t[u].r<l)return;
	if(t[u].v)q.push_back({t[u].v,min(t[u].r,r)-max(t[u].l,l)+1});
	else qry(Ls),qry(Rs);
}
```

---

### Conclusion: 

仔细想想其实这个线段树也是利用**随机数据的多次区间设置**，**减少有效懒标记的数量**以优化查询复杂度

如果没有区间设置，照样$O(nm)$爆炸

~~所以**以后看见线段树是这么构造的，就果断使用珂朵莉树吧**~~（大雾

### Special announcement

虽然这题我没打珂朵莉树，但是

## 我永远喜欢珂朵莉！！！！！

有输入法为证

![](https://cdn.luogu.com.cn/upload/image_hosting/lrmebcd7.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/xhugky1p.png)



---

## 作者：Thomasguo666 (赞：9)

# 珂朵莉树 

珂朵莉树是一种基于平衡树的暴力数据结构。一般用std::set来实现。

## 什么时候用珂朵莉树：

1. 当有区间赋值操作时
2. 当有区间幂次和等线段树树状数组显然不能胜任的操作时

## 定义

珂朵莉树是把连续的一段值相同的区间当作一个节点对待。下面是一个节点的定义

```c++
typedef long long ll;
struct node
{
	int l,r;//节点的左、右端点
	mutable ll v;//如果不加mutable修饰符，那么v变量初始化后就不能修改了。
	node (int l,int r=-1,ll v=0):l(l),r(r),v(v) {}//构造函数
	bool operator <(const node &rhs) const
	{
	    return l<rhs.l;
	}
};
set<node> s;
```

## 基本操作

### 初始化

```c++
for (int i=1;i<=n;i++) s.insert(node(i,i,a[i]));
```

### 重要：区间分裂

就是把包含mid的区间[l,r]分裂成[l,mid-1]和[mid,r]，并返回[mid,r]的指针。

具体来讲，是先把区间[l,r]删去，再分别把区间[l,mid),和[mid,r]加入。

![](https://i.loli.net/2019/02/03/5c56eb626b143.png)

```c++
typedef set<node>::iterator IT;
IT split(int mid)
{
    IT it=s.lower_bound(node(mid));//寻找第一个左端点大于等于k的区间。
    if (it!=s.end()&&it->l==mid) return it; //如果找到的这个区间的左端点就是mid那么就返回这个区间的指针。
    --it;//否则mid一定在上一个区间里
    int l=it->l,r=it->r;
    ll v=it->v;
    s.erase(it);//删掉区间[l,r]
    s.insert(node(l,mid-1,v));//插入区间[l,mid-1]
    return s.insert(node(mid,r,v)).first; //s.insert()返回的其实是一个pair，其中的first是变量的指针。
}
```



### 核心：区间赋值

就是把区间[l,r]的值全都改为v。

![](https://i.loli.net/2019/02/03/5c56ecd2e058f.png)

区间赋为5后

![](https://i.loli.net/2019/02/03/5c56edab6e31d.png)

```c++
void assign(int _l,int _r,ll v)
{
    IT r=split(_r+1),l=split(_l); //重点！一定要按照这个次序，否则可能会导致指针失效而RE，下同
    s.erase(l,r); //删除区间[l,r+1)，是一个方便但比较少见的操作
    s.insert(node(_l,_r,v));
}
```

这个操作直接使set的大小接近logn，把整体时间复杂度减小至接近mlogn



其他的操作就可以用暴力了，这里讲几个常见的。



### 区间加

直接加就行了，十分暴力

```c++
void add(int _l,int _r,ll v)
{
    IT r=split(_r+1),l=split(_l);
    for (;l!=r;l++) l->v+=v;
}
```

### 区间k小值

把区间里每段拿出来排个序就行了。

```c++
ll kth(int _l,int _r,int k)
{
    IT r=split(_r+1),l=split(_l); //把区间里
    vector<pair<ll,int> > v;
    v.clear();
    for (;l!=r;l++) v.push_back(pair<ll,int>(l->v,l->r-l->l+1));// 每段拿出来
    sort(v.begin(),v.end());// 排个序
    for (vector<pair<ll,int> >::iterator it=v.begin();it!=v.end();it++)
    {
        k-=it->second;
        if (k<=0) return it->first; //就行了
    }
}
```

### 区间幂次和

直接快速幂就行了。

```c++
ll sum(int _l,int _r,int x,int y)
{
    IT r=split(_r+1),l=split(_l);
    ll ans=0;
    for (;l!=r;l++) 
    {
        ans=((ans+(ll)(l->r-l->l+1)*qpow(l->v,(ll)x,(ll)y))%y+y)%y;
    }
    return ans;
}
```



从以上几个操作我们可以看出，珂朵莉树不仅有代码量小，易调试的优点，并且还可以解决许多线段树树状数组等数据结构无法胜任的问题。


[题目链接](https://www.luogu.org/problemnew/show/CF896C) 

代码：

```c++
#include <bits/stdc++.h>
#define IT set<node>::iterator
using namespace std;
typedef long long ll;
int p=1000000007;
ll qpow(ll a,ll k,ll p)
{
    a%=p;
    ll ans=1;
    while (k)
    {
        if (k&1) ans=ans*a%p;
        a=a*a%p;
        k>>=1;
    }
    return ans;
}
struct node
{
	int l,r;
	mutable ll v;
	node (int l,int r=-1,ll v=0):l(l),r(r),v(v) {}
	bool operator <(const node &rhs) const
	{
	    return l<rhs.l;
	}
};
set<node> s;
IT split(int k)
{
    IT it=s.lower_bound(node(k));
    if (it!=s.end()&&it->l==k) return it;
    --it;
    int l=it->l,r=it->r;
    ll v=it->v;
    s.erase(it);
    s.insert(node(l,k-1,v));
    return s.insert(node(k,r,v)).first;
}
void add(int _l,int _r,ll v)
{
    IT r=split(_r+1),l=split(_l);
    for (;l!=r;l++) l->v+=v;
}
void assign(int _l,int _r,ll v)
{
    IT r=split(_r+1),l=split(_l);
    s.erase(l,r);
    s.insert(node(_l,_r,v));
}
ll kth(int _l,int _r,int k)
{
    IT r=split(_r+1),l=split(_l);
    vector<pair<ll,int> > v;
    v.clear();
    for (;l!=r;l++) v.push_back(pair<ll,int>(l->v,l->r-l->l+1));
    sort(v.begin(),v.end());
    for (vector<pair<ll,int> >::iterator it=v.begin();it!=v.end();it++)
    {
        k-=it->second;
        if (k<=0) return it->first;
    }
}
ll sum(int _l,int _r,int x,int y)
{
    IT r=split(_r+1),l=split(_l);
    ll ans=0;
    for (;l!=r;l++) 
    {
        ans=((ans+(ll)(l->r-l->l+1)*qpow(l->v,(ll)x,(ll)y))%y+y)%y;
    }
    return ans;
}
int n,m;
ll seed,vmax;
ll a[100005];
ll rnd()
{
    ll ans=seed;
    seed=(seed*7+13)%p;
    return ans;
}
int main()
{
    cin>>n>>m>>seed>>vmax;
    for (int i=1;i<=n;i++) a[i]=(rnd()%vmax)+1,s.insert(node(i,i,a[i]));
	s.insert(node(n+1,n+1,0));
	for (int i=1;i<=m;i++)
    {
        int op=int(rnd()%4)+1,l=int(rnd()%n)+1,r=int(rnd()%n)+1,x,y;
        if (l>r) swap(l,r);
        if (op==3) x=int(rnd()%(r-l+1))+1;
        else x=int(rnd()%vmax)+1;
        if (op==4) y=int(rnd()%vmax)+1;
        if (op==1) add(l,r,ll(x));
        else if (op==2) assign(l,r,ll(x));
        else if (op==3) cout<<kth(l,r,x)<<endl;
        else cout<<sum(l,r,x,y)<<endl;
    }
    return 0;
}
```





完结撒花！！！*★,°*:.☆(￣▽￣)/$:*.°★* 。

---

## 作者：Erina (赞：4)

# 珂朵莉树

## 100%的观影体验请去: [这里......](https://www.cnblogs.com/blackhuaji/p/11113022.html)

~~珂朵莉最珂爱了不接受反驳~~

好了我们进入正题......

## 一些必须知道的东西

1. 珂朵莉树**不是树!!!**
   1. 珂朵莉树只是一种基于平衡树的数据结构.
2. 珂朵莉树的使用需要两个条件
   1. 数据随机
   2. 有**区间赋值**操作
3. 珂朵莉树适用范围并不是很大, 但是珂以解决一些奇怪的问题, 比如说:
   1. [T43829](https://www.luogu.org/problemnew/show/T43829)非常难至今我只拿了90分剩下WA了......
   2. [CF896C](https://codeforces.com/contest/896/problem/C)
   3. [CF915E](https://codeforces.com/contest/915/problem/E)
4. 珂朵莉树较好调试, 但是有时珂以把你RE出屎......
5. 珂朵莉树的变种数量实在太多, 所以我们不会吧它封装起来.
6. 珂朵莉树是一种**暴力数据结构**

好了差不多就是这么多了, 大家看着办吧......

## 珂朵莉的结构

先看一道例题, 以CF896C为例.

我们要

1. 区间加法
2. **区间赋值**
3. 区间第x小
4. 区间k次方和......

数据保证随机(随机数生成器都给你了你还说他不随机?)

咋一看是一道毒瘤, 但是一看第二个操作比较好, 从它入手

然后经过一些随机操作我们会发现这个数组不难看, 比如说:

`1, 1, 5, 5, 5, 5, 12, 7, 7, 7, 15`

如果创建一个数据结构, 使得它里面存储的是大量的区间, 那么我们每一次2号操作, [L,R]里面的区间就只剩一个了.

我们最后决定用平衡树来存储区间, 因为我们需要进行二分操作.

每一次操作时把需要区间最左右的元素所在的区间切开, 然后对中间的每一个区间操作.

最终我们得到了一个$O(\sqrt{n})$的数据结构.

使用`stl::set`来代替一个手写的平衡树, 然后我们得到了这样一个东西:

```cpp
class kotree {
	class node {
	public:
		int l, r;
		mutable long long val;// mutable 表示"不能为const", 因为iterator加上*运算符后会返回const值, 这里加上mutablr就珂以进行修改.
		bool operator < (const node& ot)const {
			return l < ot.l;
		}//平衡树需要的比较操作
	};
	set<node>odt;
};
```

好了我们先来看最基本的操作: 切分, 把一个区间砍成两个

我们先找到要砍那个区间, 然后砍它就是了......

```cpp
auto split(int x) {// 找到x所在的区间, 然后把它切成两半并返回右侧的迭代器(x在右面的那一半)
	auto it = odt.lower_bound({ x,0,0 });// 寻找切分目标右面的那个
	if (it != odt.end() && it->l == x)return it;// 如果寻找到的恰好左端点就是x那么无需切分, 直接返回即珂
	it--;// x在左面的区间里
	int l = it->l, r = it->r;
	long long val = it->val;
	odt.erase(it);
	odt.insert({ l,x - 1,val });
	return odt.insert({ x,r,val }).first; //insert的返回值包含两部分: first:迭代器  second: 成功与否
}
```

然后**全部**都是暴力操作啊......

```cpp
void add(int l, int r, long long x) {
	auto rb = split(r + 1), lb = split(l);
	while (lb != rb)lb->val += x, lb++;//遍历区间的日常方式
}
void assign(int l, int r, long long x) {
	auto rb = split(r + 1), lb = split(l);
	odt.erase(lb, rb);//想不到吧一次全删
	odt.insert({ l,r,x });
}
long long kth(int l, int r, int x) {
	vector<mp>ygy;
	auto rb = split(r + 1), lb = split(l);
	while (lb != rb)ygy.push_back(mp(lb->val, lb->r - lb->l + 1)), lb++;
	sort(ygy.begin(), ygy.end());
	for (auto it : ygy) {
		x -= it.second;
		if (x <= 0)return it.first;
	}
	return -1;
}
long long sum(int l, int r, int k, long long m) {
	auto rb = split(r + 1), lb = split(l);
	long long ans = 0;
	while (lb != rb)ans = (ans + 1ll * ksm(lb->val, k, m) * (1ll * lb->r - lb->l + 1) % m) % m, lb++;
	return ans;
}
```

是的你没看错就是这么暴力......

~~珂朵莉: 我这么珂爱怎么会暴力呢?......~~

然后整棵树长成这样:

```cpp
typedef pair<long long, int>mp;
class kotree {
	class node {
	public:
		int l, r;
		mutable long long val;
		bool operator < (const node& ot)const {
			return l < ot.l;
		}
	};
	set<node>odt;
	auto split(int x) {
		auto it = odt.lower_bound({ x,0,0 });
		if (it != odt.end() && it->l == x)return it;
		it--;
		int l = it->l, r = it->r;
		long long val = it->val;
		odt.erase(it);
		odt.insert({ l,x - 1,val });
		return odt.insert({ x,r,val }).first;
	}
public:
	kotree(int n = 0) {
		odt.clear();
		odt.insert({ 1,n,0 });
	}
	void add(int l, int r, long long x) {
		auto rb = split(r + 1), lb = split(l);
		while (lb != rb)lb->val += x, lb++;
	}
	void assign(int l, int r, long long x) {
		auto rb = split(r + 1), lb = split(l);
		odt.erase(lb, rb);
		odt.insert({ l,r,x });
	}
	long long kth(int l, int r, int x) {
		vector<mp>ygy;
		auto rb = split(r + 1), lb = split(l);
		while (lb != rb)ygy.push_back(mp(lb->val, lb->r - lb->l + 1)), lb++;
		sort(ygy.begin(), ygy.end());
		for (auto it : ygy) {
			x -= it.second;
			if (x <= 0)return it.first;
		}
		return -1;
	}
	long long sum(int l, int r, int k, long long m) {
		auto rb = split(r + 1), lb = split(l);
		long long ans = 0;
		while (lb != rb)ans = (ans + 1ll * ksm(lb->val, k, m) * (1ll * lb->r - lb->l + 1) % m) % m, lb++;
		return ans;
	}
}ygy;
```

然后将题目主体(main)补充一下就珂以了...... 题目连伪代码都给你了......

总之代码如下:

```cpp
#include<iostream>
#include<cstdio>
#include<queue>
#include<stack>
#include<algorithm>
#include<set>
using namespace std;
namespace fio {
	streambuf* in = cin.rdbuf();
	char bb[1000000], * s = bb, * t = bb;
#define gc() (s==t&&(t=(s=bb)+in->sgetn(bb,1000000),s==t)?EOF:*s++)
	inline int read() {
		int x = 0; char ch = gc();
		while (ch < 48)ch = gc();
		while (ch >= 48)x = x * 10 + ch - 48, ch = gc();
		return x;
	}
}using namespace fio;
long long ksm(long long a, long long b, long long k) {
	long long ans = 1;
	for (a %= k; b; a = a * a % k, b >>= 1)if (b & 1)ans = ans * a % k;
	return ans;
}
typedef pair<long long, int>mp;
class kotree {
	class node {
	public:
		int l, r;
		mutable long long val;
		bool operator < (const node& ot)const {
			return l < ot.l;
		}
	};
	set<node>odt;
	auto split(int x) {
		auto it = odt.lower_bound({ x,0,0 });
		if (it != odt.end() && it->l == x)return it;
		it--;
		int l = it->l, r = it->r;
		long long val = it->val;
		odt.erase(it);
		odt.insert({ l,x - 1,val });
		return odt.insert({ x,r,val }).first;
	}
public:
	kotree(int n = 0) {
		odt.clear();
		odt.insert({ 1,n,0 });
	}
	void add(int l, int r, long long x) {
		auto lb = split(l), rb = split(r + 1);
		while (lb != rb)lb->val += x, lb++;
	}
	void assign(int l, int r, long long x) {
		auto rb = split(r + 1), lb = split(l);
		odt.erase(lb, rb);
		odt.insert({ l,r,x });
	}
	long long kth(int l, int r, int x) {
		vector<mp>ygy;
		auto rb = split(r + 1), lb = split(l);
		while (lb != rb)ygy.push_back(mp(lb->val, lb->r - lb->l + 1)), lb++;
		sort(ygy.begin(), ygy.end());
		for (auto it : ygy) {
			x -= it.second;
			if (x <= 0)return it.first;
		}
		return -1;
	}
	long long sum(int l, int r, int k, long long m) {
		auto rb = split(r + 1), lb = split(l);
		long long ans = 0;
		while (lb != rb)ans = (ans + 1ll * ksm(lb->val, k, m) * (1ll * lb->r - lb->l + 1) % m) % m, lb++;
		return ans;
	}
}ygy;
int n, m, k, d;
class rng {
	int seed, vmax;
public:
	int rand(int mod = 4) {
		int ret = seed;
		seed = (1ll * seed * 7 + 13) % 1000000007;
		return ret % mod;
	}
	rng(int seed = 0, int vmax = 0) :seed(seed), vmax(vmax) {}
}rnd;
int main() {
	cin >> n >> m >> k >> d;
	rnd = rng(k, d);
	ygy = kotree(n);
	for (int i = 1; i <= n; i++)ygy.assign(i, i, 1ll * rnd.rand(d) + 1);
	for (int i = 1; i <= m; i++) {
		int op = rnd.rand() + 1;
		int l = rnd.rand(n) + 1, r = rnd.rand(n) + 1;
		if (l > r)swap(l, r);
		int x, y;
		if (op == 3)x = rnd.rand(r - l + 1) + 1;
		else x = rnd.rand(d) + 1;
		if (op == 4)y = rnd.rand(d) + 1;
		switch (op) {
		case 1:
			ygy.add(l, r, x);
			break;
		case 2:
			ygy.assign(l, r, x);
			break;
		case 3:
			cout << ygy.kth(l, r, x) << endl;
			break;
		case 4:
			cout << ygy.sum(l, r, x, y) << endl;
			break;
		}
	}
}
```

看完了, 注意以下几点:

1. 一定要记住这个细节:```auto rb = split(r + 1), lb = split(l);```不然将你<font color=#9966FF>RE出屎就是这里! 想一想为什么.~~但是现在市面上大多数珂朵莉树都是这么写的天知道它们是怎么过的......~~
2. `split`函数一定一定不要写错! 是整个珂朵莉树的根基函数.
3. 记住珂朵莉树的应用条件有数据随机一项......

我们再来看一道CF915E, 原则上要用动态开点线段树, 但是珂朵莉树也是随便秒...... 因为...... **所有操作都是区间赋值你想让我干什么?!**

但是注意一下这么几点: 这一题不能直接区间赋值然后计算, 小心30点<font color=#00CCFF>TLE掉.

计算的时候要加一个优化(求和)

嗯对差不多就是这样了.

```cpp
#include"pch.h"
#include<iostream>
#include<cstdio>
#include<queue>
#include<stack>
#include<algorithm>
#include<set>
using namespace std;
namespace fio {
	streambuf* in = cin.rdbuf();
	char bb[1000000], * s = bb, * t = bb;
#define gc() (s==t&&(t=(s=bb)+in->sgetn(bb,1000000),s==t)?EOF:*s++)
	inline int read() {
		int x = 0; char ch = gc();
		while (ch < 48)ch = gc();
		while (ch >= 48)x = x * 10 + ch - 48, ch = gc();
		return x;
	}
}using fio::read;
int n, m, k;
class kotree {
protected:
	class node {
	public:
		int l, r;
		bool val;
		bool operator < (const node ot)const {
			return l < ot.l;
		}
	};
	set<node>odt;
	auto split(int x) {
		auto nex = odt.lower_bound({ x,0,0 });
		if (nex != odt.end() && nex->l == x)return nex;
		nex--;
		int l = nex->l, r = nex->r;
		bool val = nex->val;
		odt.erase(nex), odt.insert({ l,x - 1,val });
		return odt.insert({ x,r,val }).first;
	}
	int ans;
public:
	kotree(int n = 0) { odt.clear(), odt.insert({ 1,n,1 }), ans = n; }
	void assign(int l, int r, bool val) {
		auto rb = split(r + 1), lb = split(l);
		for (auto it = lb; it != rb; it++)ans -= it->val * (it->r - it->l + 1);
		ans += (r - l + 1) * val;
		odt.erase(lb, rb), odt.insert({ l,r,val });
	}
	int total() { return ans; }
}ygy;
void w(int x) {
	if (x > 9)w(x / 10);
	putchar(x % 10 + 48);
}
int main() {
	n = read(), m = read();
	ygy = kotree(n);
	for (int i = 1; i <= m; i++) {
		int a = read(), b = read(), c = read();
		ygy.assign(a, b, (c - 1) != 0);
		w(ygy.total()), putchar('\n');
	}
}
```

简单, 霸气, **快**!

然而这是一种暴力(?)数据结构. 只能应对随机数据, 这样珂以有效地限制区间数量.

emmm就是这么多了...... 如果有什么问题请私信提出(然而我珂能不看......)

---

## 作者：ISYRHH (赞：3)

## [CF896C]Willem, Chtholly and Seniorious

------------

根据题目背景可以看出，这题要用珂朵莉树写。（/doge )

然而珂朵莉树是一种建立在 set 基础上的数据结构，甚至更偏向于一种做法，不是很能体现 C 艹面向对象的特点。（~~瞎扯~~）

为了推广珂学，为了充分显示珂朵莉树面向对象的特征，（~~为了水一篇题解~~），简单介绍一下珂朵莉树，并提供一篇set继承封装的珂朵莉树题解。

------------


## 题意分析

跳过花里胡哨的输入，题目可以总结为动态维护一个数列，并支持 4 种操作：

##### 1.区间加
##### 2.区间推平
##### 3.区间第 k 大
##### 4.区间 k 次方和

其中区间推平看起来非常友好，推平的一大段数可以同过记录相同的值和起点终点位置记录这段数的所有信息，并以一个非常友好的复杂度支持另外三种操作。

而且数据又是随机的，也就意味着操作中会有很多的 2 操作，期望上能将数列推平成很少的几段，然后就能高效的维护这个数列。

顺着这个思想，珂朵莉树就诞生了。

------------


## 解法

考虑将推平操作分成的段按照左端点排序，用一个 set 维护

开始时每个数都单独属于一段。

每当有操作 2 时，将覆盖到的段挑出来合并成一段，塞进 set 里，原有的区间全部删掉。

对于操作 1，将覆盖到的段挑出来，每段的值都加上 x。

对于操作 3，将覆盖到的段挑出来，分别把每段丢进一个数组里，sort 一下，然后从小到大枚举第k个数。

对于操作 4，将覆盖到的段跳出来，快速幂分别取出 $x^k$ 乘上段内数的个数，然后加起来输出。

由于操作 2 帮我们把数列划成的段数是很少的，操作 1，3，4 均可以在较高的效率下处理。

貌似还有一个问题……

如何将一个区间对应的段取出？

找的话可以通过 set 自带的 lower_bound() 二分找到左端点和右端点所在的段，然后遍历中间的段。

但是……左端点和右端点可能是会卡在一段的中间的……

这时候我们可以直接把左端点和右端点所在的段拆成两段，使左端点作为一段的开头，右端点作为一段的结尾。

然后再遍历中间的段。

这个分裂段来的段，再以分界点向两边重建两段实现，然后将这两段塞回到 set 里。

还有一点需要注意的是在分裂左右端点时要先分裂右端点再分裂左端点。

当左右端点位于同一块时，若先分裂左端点，分裂右端点时会对左端点所在的块进行修改，导致程序 RE，而先分裂右端点可以避免这一情况。

这点楼上巨佬已经提过，不再赘述。

------------

## 关于继承


###### 类的继承，是新的类从已有类那里得到已有的特性。从已有类产生新类的过程就是类的派生。

###### 通过类的派生可以建立具有共同关键特征的对象家族，从而实现代码的重用。

###### ——《 C++ 语言程序设计》

------------


简单来说，就是在原有的类的基础上增加一些新的内容，如函数，成员等，得到一个新的类

众所周知，stl 里好东西很多，但 stl 终究是有极限的，好多有用的内容 stl 的模板库本身不能实现

比如 stl 里有 set 的模板，但是没有珂朵莉树的模板……

但要是从头自己实现，又显得太麻烦了

我们可以通过继承的方式从 stl 里套取到我们想要的，并把我们想要加进去的内容以成员和成员函数的形式加进去，作为一个新类。

例如珂朵莉树，就可以在继承 set 的基础上加入 assign（推平），add（区间加），kth（区间第 k 大）等新的成员函数，一个 vector 成员作为排序时的辅助数组，得到珂朵莉树这个新类

另外在写继承时要注意多态性和对象的作用域等问题，这些就不再赘述，debug 多了自然就会了……

附上代码……

------------


## 代码（附简单注释）

```cpp
#include<algorithm>
#include<cstdio>
#include<vector>
#include<set>
#define mmo 1000000007
using namespace std;
int n,m,ma,op,in1,in2,in3,in4,mo;
int seed;
//取模
inline long long moo(long long x)
{
    return x%mo;
}
//快速幂
inline long long poww(long long x,int y)
{
    long long r=1;x=moo(x);
    while(y)
    {
        if(y&1)r=moo(r*x);
        x=moo(x*x);
        y>>=1;
    }
    return r;
}
//记录段的类
class node
{
    private:
        friend bool operator <(const node &x,const node &y)
        {
            return x.l<y.l;
        }
    public:
        int l,r;
        mutable long long dat;
        node(int l,int r=-1,long long dat=0):l(l),r(r),dat(dat){}
};
//set继承的珂朵莉树类
class odt:public set<node>
{
    private:
        //分裂
        set<node>::iterator splt(int x)
        {
            set<node>::iterator ite=lower_bound(node(x));
            if(ite!=end()&&ite->l==x)return ite;ite--;
            int nl=ite->l,nr=ite->r;long long nv=ite->dat;
            erase(ite);
            insert(node(nl,x-1,nv));
            return insert(node(x,nr,nv)).first;
        }
        vector<pair<long long,int> >no;//排序用的辅助数组
    public:
        //这个声明可以使子类随意调用基类的构造函数，省去一个个写的麻烦
        //但有时会产生bug，视实际情况使用
        using set<node>::set;
        //区间加
        void add(int l,int r,long long dd)
        {
            set<node>::iterator rit=splt(r+1),lit=splt(l);
            while(lit!=rit){lit->dat+=dd;lit++;}
        }
        //区间推平
        void assn(int l,int r,long long dd)
        {
            set<node>::iterator rit=splt(r+1),lit=splt(l);
            erase(lit,rit);insert(node(l,r,dd));
        }
        //区间第k大
        void kth(int l,int r,int id)
        {
            set<node>::iterator rit=splt(r+1),lit=splt(l);no.clear();
            while(lit!=rit)
            {
                no.push_back(pair<long long,int>(lit->dat,lit->r-lit->l+1));
                lit++;
            }
            sort(no.begin(),no.end());int now=0;
            for(vector<pair<long long,int> >::iterator ite=no.begin();ite!=no.end();ite++)
            {
                if(now+ite->second<id){now+=ite->second;continue;}
                printf("%lld\n",ite->first);return;
            }
        }
        //区间k次幂和
        void poor(int l,int r,int t)
        {
            set<node>::iterator rit=splt(r+1),lit=splt(l);long long ans=0;
            while(lit!=rit){ans=moo(1ll*ans+moo(1ll*poww(lit->dat,t)*moo(lit->r-lit->l+1)));lit++;}
            printf("%lld\n",ans);
        }
};
odt se;//难得一次没用指针
//题目中给的伪随机生成
inline int rnd()
{
    int ret=seed;
    seed=(1ll*seed*7+13)%mmo;
    return ret;
}
int main()
{
    scanf("%d%d%d%d",&n,&m,&seed,&ma);
    for(int i=1;i<=n;i++)
    {
        se.insert(node(i,i,rnd()%ma+1));
    }
    for(int i=1;i<=m;i++)
    {
        //数据生成
        op=rnd()%4+1;
        in1=rnd()%n+1;in2=rnd()%n+1;
        if(in1>in2)swap(in1,in2);
        if(op==3)in3=rnd()%(in2-in1+1)+1;
        else in3=rnd()%ma+1;
        if(op==4)mo=rnd()%ma+1;
        //4个操作
        switch(op)
        {
            case 1:
                se.add(in1,in2,in3);
                break;
            case 2:
                se.assn(in1,in2,in3);
                break;
            case 3:
                se.kth(in1,in2,in3);
                break;
            case 4:
                se.poor(in1,in2,in3);
                break;
        }
    }
    return 0;
}
```


## **end**

---

## 作者：swiftc (赞：3)

ODT 模版题

### 1.什么是ODT

ODT是一种基于set __在有区间赋值操作，且是随机数据下复杂度有保证__ 的数据结构，可以维护很多东西（因为操作基本都是暴力）。

### 2.ODT的实现
1.split

ODT使用 set 维护数值相同的区间，当数值发生改变时，就需要把一个区间查看，使用```set.lower_bound```就可以很容易的实现。
```cpp

IT split(int pos){
    IT it=st.lower_bound(node(pos));
    if(it!=st.end()&&it->ll==pos)return it;
    --it;
    int ll=it->ll,rr=it->rr;
    lt val=it->val;
    st.erase(it);
    st.insert(node(ll,pos-1,val));
    return st.insert(node(pos,rr,val)).first;
}
```

2.assign

这是一个能保证ODT复杂度的操作，区间赋值，即把多个数值相同的区间合并，使用 ```split``` 把区间两侧拆开，然后删除中间的所有元素，最后插入即可。

```cpp
void assign(int ll,int rr,lt val){
    IT itr=split(rr+1),itl=split(ll);
    st.erase(itl,itr);
    st.insert(node(ll,rr,val));
}
```

3.剩下的操作

暴力即可

### 3.复杂度证明

我不会（

### 4.完整代码

```cpp
//珂朵莉树模板
#include<bits/stdc++.h>
using namespace std;
#define  lt long long
#define IT set<node>::iterator
#define pir pair<lt,int>
#define mkp(x,y) make_pair(x,y)
lt seed,vmax;
lt rnd(){
    lt res=seed;
    seed=(seed*7+13)%1000000007;
    return res;
}

const int maxn=100010;
int n,m;
lt  a[maxn];
struct node{
    int ll,rr;
    mutable lt val;
    node(int L,int R=-1,lt V=0): ll(L),rr(R),val(V){}
    bool operator <(const node &tt)const {return ll<tt.ll;}
};
set<node> st;

lt qpow(lt a,lt k,lt p){
    lt res=1;a%=p;
    while(k>0){
        if(k&1)res=(res*a)%p;
        a=(a*a)%p; k>>=1;
    }
    return res;
}
IT split(int pos){
    IT it=st.lower_bound(node(pos));
    if(it!=st.end()&&it->ll==pos)return it;
    --it;
    int ll=it->ll,rr=it->rr;
    lt val=it->val;
    st.erase(it);
    st.insert(node(ll,pos-1,val));
    return st.insert(node(pos,rr,val)).first;
}

void assign(int ll,int rr,lt val){
    IT itr=split(rr+1),itl=split(ll);
    st.erase(itl,itr);
    st.insert(node(ll,rr,val));
}
void add(int ll,int rr,int val){
    IT itr=split(rr+1),itl=split(ll);
    for(;itl!=itr;++itl)itl->val+=val;
}
lt kth(int ll,int rr,int k){
    vector<pir>vec;
    IT itr=split(rr+1),itl=split(ll);
    for(;itl!=itr;++itl)
    vec.push_back(pir(itl->val,itl->rr-itl->ll+1));
    sort(vec.begin(),vec.end());
    for(vector<pir>::iterator it=vec.begin();it!=vec.end();++it){
        k-=it->second;
        if(k<=0)return it->first;
    }
    return -1;
}

lt qsum(int ll,int rr,lt x,lt y){
    lt res=0;
    IT itr=split(rr+1),itl=split(ll);
    for(;itl!=itr;++itl)
    res+=(qpow(itl->val,x,y)*((itl->rr-itl->ll+1)%y))%y,res%=y;
    return res;
}
int main(){
    scanf("%d",&n);
    scanf("%d",&m);
    scanf("%lld",&seed);
    scanf("%lld",&vmax);
    for(int i=1;i<=n;i++){
        a[i]=(rnd()%vmax)+1;
        st.insert(node(i,i,a[i]));
    }
    for(int i=1;i<=m;i++){
        int op=(rnd()%4)+1;
        int ll=(rnd()%n)+1,rr=(rnd()%n)+1;
        lt x,y;
        if(ll>rr)swap(ll,rr);
        if(op==3)x=(rnd()%(rr-ll+1))+1;
        else x=(rnd()%vmax)+1;
        if(op==4) y=(rnd()%vmax)+1;

        if(op==1)add(ll,rr,x);
        else if(op==2)assign(ll,rr,x);
        else if(op==3)printf("%lld\n",kth(ll,rr,x));
        else if(op==4)printf("%lld\n",qsum(ll,rr,x,y));
    }
    #ifdef WIN32
    system("pause");
    #endif
}
```


---

## 作者：Jeblqr (赞：1)

#### 我们先来看一道题：[CF896C Willem, Chtholly and Seniorious](https://www.luogu.org/problem/CF896C)

题目大概是：**维护一个数据结构，之前区间加（$[L,R] \space + \space x$），区间修改值（$[L,R] \space = \space x$）,区间$k$小值和区间每个数字的$
x$次方$mod \space y$的值（$(\sum^R_{i=R}) \space mod \space y$）。**

### 下面我们来正式地开始讲解珂朵莉树。
#### 珂朵莉树是什么？

珂朵莉树，又称老司机树（$Old\space Diver\space Tree , ODT$),是一种基于红黑树（$std::set$）的算法。至于为什么挑选$set$呢？~~那当然是因为$STL$ 自带啊！~~ 是因为$set$支持$split$操作，可以划分开来（要是你用$FHQ\space Treap, \space Splay,\space Red \space Black\space Tree$写我也无话可说~~毕竟我一个都不会~~）。

先来康康两个**基•本•的**操作

先放代码

(我的代码非·常·之·丑，求原谅)


```cpp
#include <bits/stdc++.h>
using namespace std;

class ChthollyTree
{
protected:
#define Maxn 200000001
	struct Node // set中用于存储每段区间的类型 
	{
		int l, r;
      //该区间的左右端点
		mutable long long val;
       //储存了该段区间的值
       //matable意为“可变的”，和“const”互为反义词，
       //用于声明一个无论何时都可变的变量
       //（即使在一个类中是protected的，在外部也可以修改其值）
		bool operator<(const Node &t) const 
       // 用左端点（l）来比较，匹配区间
		{
			return l < t.l;
		};
	};
	set<Node> st;//定义一个存储Node类型的set
	set<Node>::iterator split(int pos);

public:
	void assign(int l, int r, long long val);
};

set<ChthollyTree::Node>::iterator ChthollyTree::split(int pos)
{
	set<Node>::iterator it = st.lower_bound(Node{pos, -1, 0});
	if (it != st.end() && it->l == pos)
		return it;
	it--;
	Node tmp = *it;
	st.erase(it);
	st.insert(Node{tmp.l, pos - 1, tmp.val});
	return st.insert(Node{pos, tmp.r, tmp.val}).first;
}

void ChthollyTree::assign(int l, int r, long long val)
{
	set<Node>::iterator it_r = split(r + 1), it_l = split(l);
	st.erase(it_l, it_r);
	st.insert(Node{l, r, val});
}

class T : protected ChthollyTree
{
private:
	long long power(long long a, long long b, long long mod)
	{
		long long ans = 1;
		a %= mod;
		while (b)
		{
			if (b & 1)
				ans = ans * a % mod;
			a = a * a % mod;
			b >>= 1;
		}
		return ans;
	}

public:
	void assign(int l, int r, long long val)
	{
		set<Node>::iterator it_r = split(r + 1), it_l = split(l);
		st.erase(it_l, it_r);
		st.insert(Node{l, r, val});
	}
	void insert(int l, int r, long long val)
	{
		st.insert(Node{l, r, val});
	}
	void add(int l, int r, int val)
	{
		set<Node>::iterator it_r = split(r + 1), it_l = split(l);
		for (; it_l != it_r; it_l++)
			it_l->val += val;
	}
	long long find_kth(int l, int r, int k)
	{
		set<Node>::iterator it_r = split(r + 1), it_l = split(l);
		vector<pair<long long, int>> vec;
		for (; it_l != it_r; it_l++)
			vec.push_back(make_pair(it_l->val, it_l->r - it_l->l + 1));
		sort(vec.begin(), vec.end());
		for (vector<pair<long long, int>>::iterator it = vec.begin(); it != vec.end(); it++)
		{
			k -= it->second;
			if (k <= 0)
				return it->first;
		}
		return -1LL;
	}
	long long power(int l, int r, int x, int mod)
	{
		set<Node>::iterator it_r = split(r + 1), it_l = split(l);
		long long ans = 0;
		for (; it_l != it_r; it_l++)
		ans = (ans + ((long long)(it_l->r - it_l->l + 1)) * power(it_l->val, (long long)x, (long long)mod)) % mod;
		return ans;
	}
};

T t;

typedef long long LL;
const int MOD7 = 1e9 + 7;
const int MOD9 = 1e9 + 9;
const int imax_n = 1e5 + 7;
int n, m;
LL seed, vmax;

LL rnd()
{
	LL ret = seed;
	seed = (seed * 7 + 13) % MOD7;
	return ret;
}

LL a[imax_n];

int main()
{
	auto aaa=1;
	scanf("%d %d %lld %lld", &n, &m, &seed, &vmax);
	for (int i = 1; i <= n; ++i)
	{
		a[i] = (rnd() % vmax) + 1;
		t.insert(i, i, a[i]);
	}
	t.insert(n+1, n+1, 0);
	int lines = 0;
	for (int i = 1; i <= m; ++i)
	{
		int op = int(rnd() % 4) + 1;
		int l = int(rnd() % n) + 1;
		int r = int(rnd() % n) + 1;
		if (l > r)
			std::swap(l, r);
		int x, y;
		if (op == 3)
			x = int(rnd() % (r - l + 1)) + 1;
		else
			x = int(rnd() % vmax) + 1;
		if (op == 4)
			y = int(rnd() % vmax) + 1;
		if (op == 1)
			t.add(l, r, LL(x));
		else if (op == 2)
			t.assign(l, r, LL(x));
		else if (op == 3)
			cout << t.find_kth(l, r, x) << '\n';
		else
			cout << t.power(l, r, x, y) << '\n';
	}
	return 0;
}
```

PS：一定要先把上面的变量定义看完
是不是看起来很复杂？
我们一个个来分解，您就会知道珂朵莉树是多么的**暴•力**


### $split$

#### 根据$pos$，把$set$分成$[L,pos-1],\space [pos,R]$区间（抽象意义上的那种）


```cpp
set<ChthollyTree::Node>::iterator ChthollyTree::split(int pos)
{
	set<Node>::iterator it = st.lower_bound(Node{pos, -1, 0});
	if (it != st.end() && it->l == pos)
		return it;
	it--;
	Node tmp = *it;
	st.erase(it);
	st.insert(Node{tmp.l, pos - 1, tmp.val});
	return st.insert(Node{pos, tmp.r, tmp.val}).first;
}
}
```


可能一开始看的时候比较复杂（蛮多是迭代器的操作）~~我一开始看的时候也是看不懂然后就放弃了~~。我们一句句来分析。

```cpp
set<Node>::iterator it = st.lower_bound(Node{pos, -1, 0});
```

声明一个$Node$类型的$set$的迭代器

用$set$自带的二分查找查找第一个$l$小于等于$pos$的地方，并返回其迭代器并传到$it$


PS:如果有，用$STL$中自带的二分查找会比$algorithm$中的二分查找快许多


```cpp
if (it != st.end() && it->l == pos)
	return it;
```

如果如果二分查找到的$it$不是$st.end()$（说明没找到（$set$等$STL$容器的迭代器都是左闭右开区间（$[L,R+1)$）））且$it->l\space =\space pos$（说明找到了$pos$这个节点），就直接$return$好了。

```cpp
it--;
Node tmp = *it;
st.erase(it);
st.insert(Node{tmp.l, pos - 1, tmp.val});
return st.insert(Node{pos, tmp.r, tmp.val}).first;
```

否则，$it$指向上一个迭代器（因为是用$l$匹配的，所以这个节点位置不在$it$就在$it-1$），用一个临时变量$tmp$存储$it$的值。
然后，直接把它从$st$里面删掉，并且分开储存（在$st$中分开加入）。值得一提的是，最后一行用了$std::pair<iterator,bool>\space insert(const\space value\_type\&\space value)$的函数，返回一个$pair$，其第一个就是插入位置迭代器，省得再二分一次。


### $assign$

$ODT$的精髓就在于$assign$操作。它让我们可以使用**区间推平**（区间修改为某个值）的操作。
```cpp

void ChthollyTree::assign(int l, int r, long long val)
{
	set<Node>::iterator it_r = split(r + 1), it_l = split(l);
	st.erase(it_l, it_r);
	st.insert(Node{l, r, val});
}
```
第一句，从$st$中把$[L,R]$给$split$出来（分成$[L,l-1],\space [l,r],\space [r+1,R]$三部分）

第二句，把[$l,r]$中的全部删掉。这里用到了$iterator\space erase( const\_iterator\space first,\space const\_iterator\space last )$，可以把$it_l$到$it_r$之间的全部删掉。

第三句，直接把$Node\{l,\space r,\space val\}$直接插回去。

这里一定要注意了：**在进行set<Node>::iterator it_r = split(r + 1), it_l = split(l)的操作时，不能把it_r和it_l位置调换！** 因为如果先搞it_l再搞it_r，就会使it_l失效。

看到这里，怎么样？够不够暴力?

剩下的操作更加暴力，没什么好说的，拖出来过一下就好了。


```cpp
void insert(int l, int r, long long val)
{
	st.insert(Node{l, r, val});
}
```
直接插

```cpp
void add(int l, int r, int val)
{
	set<Node>::iterator it_r = split(r + 1), it_l = split(l);
	for (; it_l != it_r; it_l++)
		it_l->val += val;
}
```

把$[l,r]$剥出来，然后遍历每个区间并加上$val$

```cpp
long long find_kth(int l, int r, int k)
{
	set<Node>::iterator it_r = split(r + 1), it_l = split(l);
	vector<pair<long long, int>> vec;
	for (; it_l != it_r; it_l++)
		vec.push_back(make_pair(it_l->val, it_l->r - it_l->l + 1));
	sort(vec.begin(), vec.end());
	for (vector<pair<long long, int>>::iterator it = vec.begin(); it != vec.end(); it++)
	{
		k -= it->second;
		if (k <= 0)
			return it->first;
	}
	return -1LL;
}
```

不要看着一大堆代码堆在一起很复杂，耐心往下看~~~
先定义一个$vector$，储存了一个$pair<long long,int>$分别代表区间的值和其大小。
然后把$[l,r]$中的每一段区间给丢进去（注意其区间大小！）。再然后直接$sort$一遍，然后再每个扫过去。


```cpp
long long power(int l, int r, int x, int mod)
{
	set<Node>::iterator it_r = split(r + 1), it_l = split(l);
	long long ans = 0;
	for (; it_l != it_r; it_l++)
	ans = (ans + ((long long)(it_l->r - it_l->l + 1)) * power(it_l->val, (long long)x, (long long)mod)) % mod;
	return ans;
}
```
把$[l,r]$内每段区间的$val$拖出来快速幂，然后乘上该区间大小并累加上去


讲完了！撒花！*★,°*:.☆(￣▽￣)/$:*.°★* 。✿✿ヽ(°▽°)ノ✿


Upd: 2019.11.7

上个月有一道题[语文1（chin1）- 理理思维](https://www.luogu.org/problem/P2787),调了好久调不出来。今天突然想起，改了很久。本来想发贴求助，然后突然发现在讨论版里有和我一样问题的人。因此：**在进行set<Node>::iterator it_r = split(r + 1), it_l = split(l)的操作时，不能把it_r和it_l位置调换！** 因为如果先搞it_l再搞it_r，就会使it_l失效。我看很多本题题解都写错了（如第一、二、三篇）都没有提到这个，而且这个错误在本题里面并不会导致错误。所以以后写珂朵莉树时要务必注意了！（be copied to the text）


---

## 作者：BF_AlphaShoot (赞：1)

声明：对于这部分知识我也是从网上学习的，若有雷同绝非有意抄袭。

首先我们要知道，要想完成这道题的第 4 个操作，最简单的办法便是**珂朵莉树**。

## 0x01 珂朵莉树简介

**珂朵莉树**，又名 ODT，恰是出自[这道题](https://www.luogu.com.cn/problem/CF896C)的正解。主要处理区间修改、查询问题。

是一种基于`std::set`的 ”指代一种特定的基于数据随机的算法“，它**不是数据结构**，这点 lxl 先生[本人也承认了](https://www.zhihu.com/question/377469286)。

它的适用范围狭小，当且仅当以下情况全部满足时才可以使用：

1. 有区间赋值操作。
2. 数据保证完全随机。在数据随机的前提下有着优秀的复杂度。

关于 **ODT 的时间复杂度**证明较为复杂，本人不太会计算，还请到网上自行学习吧。

## 0x02 结构体初始化

```cpp
struct ct{
    int l,r;
    mutable ll v;
    ct(int L,int R=-1,ll V=0){
        l=L,r=R,v=V;
    }
    bool operator <(const ct &a)const{
        return l<a.l;
    }
};
set<ct> s;
```

其中值得注意的是，$v$ 被 mutable 修饰，因为这样可以直接在 set 中修改该变量的值。

但是我们查询的时候不能保证查询的区间端点一定与这些节点的端点重合，如果采用分块思想肯定行不通，因为会退化成暴力。所以我们有了下一步。

## 0x03 分割区间操作

这是珂朵莉树的核心。

```cpp
#define str set<ct>::iterator//太长了啊qwq
inline str split(int pos){
    str it=s.lower_bound(ct(pos));
    if(it!=s.end()&&it->l==pos)
        return it;
    it--;
    int l=it->l,r=it->r,v=it->v;
    s.erase(it);
    s.insert(ct(l,pos-1,v));
    return s.insert(ct(pos,r,val)).first;
}
```

注意，一些人可能会用到 **auto** 。在以前的 NOI 系列赛事中不可以用 auto，但时代变了，所以**可以用**了。

这一部分对于 $pos$ 节点分为 $[l,pos)$ 和 $(pos,r]$ 两部分，并且对所选取的节点 $it$ 进行判断。当为 $(pos,r]$ 时，直接返回；当为 $[l,pos)$ 时，再次分裂并删去原来的区间。但当 $pos$ 恰为两边界之一时，会直接返回这个位置。

请注意，代码中 split 的顺序一定要是先 `split(r+1)`，再 `split(l)`，否则会随机 RE。

## 0x04 合并区间操作

有分裂就要有合并。

```cpp
inline void assign(int l,int r,int v) {
	str it2=split(r+1),it1=split(l);//注意，这里一定要先split(r+1)再split(l)
	s.erase(it1,it2);
	s.insert(ct(l,r,v));
}
```

assign 的本质就是分离出 $l$ 到 $r$ 的所有节点，然后删除它们，再新建一个 $l$ 到 $r$，权值为 $v$ 的节点。看似暴力，却能大大优化复杂度。

assign 的作用很大：保证珂朵莉树的时间复杂度不退化，同时也是保证其在随机数据下时间复杂度较低（趋近于 $O(m\log n)$）的根源。

## 0x05 区间加操作

```cpp
inline void add(int l,int r,ll val){
    str it2=split(r+1),it1=split(l);
    for(;it1!=it2;it1++)
        itl->v+=val;
}
```

先分离出 $l$ 到 $r$ 的所有节点，然后把每个节点的权值都加上 $v$。

## 0x06 区间第 $k$ 小

```cpp
inline ll rank(int l,int r,int k){
    vector<pair<ll,int>> p;
    str it2=split(r+1),it1=split(l);
    p.clear();
    for (;it1!=it2;it1++)
        p.push_back(pair<ll,int>(it1->v,it1->r-it1->l+1));
    sort(p.begin(),p.end());
    for(vector<pair<ll,int>>:iterator  it=p.begin();it!=p.end();it++){
        k-=it->second;
        if(k<=0) 
            return it->first;
    }
}
```

分离后把节点按权值从小到大排序，每遍历到一个节点，就将 $k$ 减去它的长度。如果 $k\leqslant 0$，则当前节点的权值即为第 $k$ 小值。

## 0x07 区间幂次和

```cpp
inline ll sum(int l, int r, int x, int y){
    str it2=split(r+1),it1=split(l);
    ll res=0;
    for(;it1!=it2;it1++)
        res=(res+(ll)(it1->r-it1->l+1)*qpow(it1->v,ll(x),ll(y)))%y;
    return res;
}
```

暴力遍历找到元素，左端点在 $[l,r)$ 的区间中最左边的区间到最右边的区间依次使用**快速幂**加入 $res$ 。

伪代码都已经给你了，种子生成器很好写，其余的主函数内容也很简单。

View code：

```cpp
#include<bits/stdc++.h>
using namespace std;

//#define int long long
#define ll long long
#define ri register int
#define il inline
#define str set<ct>::iterator

const int MOD=1e9+7;
int n,m;
ll seed,vmax;
struct ct{
    int l,r;
    mutable ll v;
    ct(int L,int R=-1,ll V=0){
        l=L,r=R,v=V;
    }
    bool operator <(const ct &a)const{
        return l<a.l;
    }
};
set<ct> s;

il ll read(){
    ll x=0,y=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
            y=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=x*10+c-'0';
        c=getchar();
    }
    return x*y;
}

il str split(int pos){
    str it=s.lower_bound(ct(pos));
    if(it!=s.end()&&it->l==pos) 
        return it;
    it--;
    int l=it->l,r=it->r;
    ll v=it->v;
    s.erase(it);
    s.insert(ct(l,pos-1,v));
    return s.insert(ct(pos,r,v)).first;

}

il void assign(int l,int r,ll v) {
	str it2=split(r+1),it1=split(l);
    s.erase(it1,it2);
    s.insert(ct(l,r,v));
}

il void add(int l,int r,ll val){
    str it2=split(r+1),it1=split(l);
    for(;it1!=it2;it1++)
        it1->v+=val;
}

il ll rk(int l,int r,int k){
    vector<pair<ll,int>> p;
    str it2=split(r+1),it1=split(l);
    p.clear();
    for(;it1!=it2;it1++)
        p.push_back(pair<ll,int>(it1->v,it1->r-it1->l+1));
    sort(p.begin(),p.end());
    for(vector<pair<ll,int>>::iterator it=p.begin();it!=p.end();it++){
        k-=it->second;
        if(k<=0) 
            return it->first;
    }
    return -1;
}

il ll qpow(ll x,ll y,ll p){
    ll res=1,ans=x%p;
    while(y){
        if(y&1) 
            res=res*ans%p;
        ans=ans*ans%p;
        y>>=1;
    }
    return res;
}

il ll sum(int l,int r,int x,int y){
    str it2=split(r+1),it1=split(l);
    ll res=0;
    for(;it1!=it2;it1++)
        res=(res+1ll*(it1->r-it1->l+1)*qpow(it1->v,1ll*x,1ll*y))%y;
    return res;
}

il ll rnd(){
    ll ret=seed;
    seed=(seed*7+13)%MOD;
    return ret;
}

signed main(){
    n=read(),m=read(),seed=read(),vmax=read();
    for(ri i=1;i<=n;i++)
        s.insert(ct(i,i,rnd()%vmax+1));
    s.insert(ct(n+1,n+1,0));
    for(ri i=1;i<=m;i++){
        int op=int(rnd()%4)+1,l=int(rnd()%n)+1,r=int(rnd()%n)+1,x,y;
        if(l>r)
            swap(l,r);
        if(op==3){
            x=int(rnd()%(r-l+1))+1;
            printf("%lld\n",rk(l,r,x));
        }
        else
            x=int(rnd()%vmax) +1;
        if(op==1)
            add(l,r,1ll*x);
        if(op==2)
            assign(l,r,1ll*x);
        if(op==4){
            y=int(rnd()%vmax)+1;
            printf("%lld\n",sum(l,r,x,y));
        }
    }
    return 0;
}
```



---

