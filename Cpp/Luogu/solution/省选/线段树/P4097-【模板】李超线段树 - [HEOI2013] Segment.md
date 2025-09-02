# 【模板】李超线段树 / [HEOI2013] Segment

## 题目描述

要求在平面直角坐标系下维护两个操作：

1. 在平面上加入一条线段。记第 $i$ 条被插入的线段的标号为 $i$。
2. 给定一个数 $k$，询问与直线 $x = k$ 相交的线段中，交点纵坐标最大的线段的编号。

## 说明/提示

### 样例 $1$ 解释

对于第一次操作，解密后为 `1 8 5 10 8`。

对于第二次操作，解密后为 `1 6 7 2 6`。

对于第三次操作，解密后为 `0 2`，此时 $lastans$ 被更新为 $2$。

对于第四次操作，解密后为 `0 11`，此时 $lastans$ 被更新为 $0$。

对于第五次操作，解密后为 `1 4 7 6 7`。

对于第六次操作，解密后为 `0 5`。

### 数据范围与约定

对于 $30\%$ 的数据，保证 $n \leq 10^3$。

对于 $100\%$ 的数据，保证 $1 \leq n \leq 10^5$，$1 \leq k, x_0, x_1 \leq 39989$，$1 \leq y_0, y_1 \leq 10^9$。

### 提示

不保证 $x_0 \neq x_1$。对于一条 $x_0' = x_1'$ 的线段，认为其与 $x = x_0'$ 的交点为其两端点中纵坐标较大的端点。

## 样例 #1

### 输入

```
6 
1 8 5 10 8 
1 6 7 2 6 
0 2 
0 9 
1 4 7 6 7 
0 5```

### 输出

```
2 
0 
3```

# 题解

## 作者：do_while_true (赞：112)

欢迎来看 [OI Wiki](https://oi-wiki.org/ds/li-chao-tree/) 上李超树的教程，其中有一部分是我写的，所以可能在内容上会~~被包含~~有所重合。

---

李超树：插入直线/线段，支持查询单点极值。

用线段树对于每个区间维护在 $m=\frac{l+r}{2}$ 处取值最大的直线的信息。

现在我们需要插入一条线段 $f$，在这条线段完整覆盖的线段树节点代表的区间中，某些区间的最优线段可能发生改变。

考虑某个被新线段 $f$ 完整覆盖的区间，若该区间无最优线段，则该线段可以直接成为最优线段。

否则，设该区间的中点为 $m$，我们拿新线段 $f$ 在中点处的值与原最优线段 $g$ 在中点处的值作比较。

如果新线段 $f$ 更优，则将 $f$ 和 $g$ 交换。那么现在考虑在中点处 $f$ 不如 $g$ 优的情况：

1. 若在左端点处 $f$ 更优，那么 $f$ 和 $g$ 必然在左半区间中产生了交点，递归到左儿子中进行插入；
2. 若在右端点处 $f$ 更优，那么 $f$ 和 $g$ 必然在右半区间中产生了交点，递归到右儿子中进行插入。
3. 若在左右端点处 $g$ 都更优，那么 $f$ 不可能成为答案，不需要继续下传。

由于仅有一个交点，所以两边子区间最多会递归一个。复杂度 $\mathcal{O}(\log n)$．

> 这个做法比大部分分类讨论做法简洁，不需要对斜率正负等信息进行冗长的分类讨论，更容易记忆。

查询 $x=k$ 答案时，从根走到 $[x,x]$ 节点记录的所有最优直线在 $x=k$ 时取值的答案极值即为所求。这里是运用了**标记永久化**的思想。

一些基本的扩展：

- 如果是**插入线段**，需要定位到线段横坐标区间在李超树上的拆分出的区间，然后一个个递归修改下去，复杂度是 $\mathcal{O}(\log^2n)$ 的。
- 李超树的经典应用是斜率优化，[这里是关于此我之前写过的总结](https://www.cnblogs.com/do-while-true/p/15404389.html)。

```cpp
#include <iostream>
#include <string>
#define MOD1 39989
#define MOD2 1000000000
#define MAXT 40000
using namespace std;
typedef pair<double, int> pdi;

const double eps = 1e-9;

int cmp(double x, double y) {
  if (x - y > eps) return 1;
  if (y - x > eps) return -1;
  return 0;
}

struct line {
  double k, b;
} p[100005];

int s[160005];
int cnt;

double calc(int id, int d) { return p[id].b + p[id].k * d; }

void add(int x0, int y0, int x1, int y1) {
  cnt++;
  if (x0 == x1)  // 特判直线斜率不存在的情况
    p[cnt].k = 0, p[cnt].b = max(y0, y1);
  else
    p[cnt].k = 1.0 * (y1 - y0) / (x1 - x0), p[cnt].b = y0 - p[cnt].k * x0;
}

void upd(int root, int cl, int cr, int u) {  // 对线段完全覆盖到的区间进行修改
  int &v = s[root], mid = (cl + cr) >> 1;
  int bmid = cmp(calc(u, mid), calc(v, mid));
  if (bmid == 1 || (!bmid && u < v)) swap(u, v);
  int bl = cmp(calc(u, cl), calc(v, cl)), br = cmp(calc(u, cr), calc(v, cr));
  if (bl == 1 || (!bl && u < v)) upd(root << 1, cl, mid, u);
  if (br == 1 || (!br && u < v)) upd(root << 1 | 1, mid + 1, cr, u);
}

void update(int root, int cl, int cr, int l, int r,
            int u) {  // 定位插入线段完全覆盖到的区间
  if (l <= cl && cr <= r) {
    upd(root, cl, cr, u);
    return;
  }
  int mid = (cl + cr) >> 1;
  if (l <= mid) update(root << 1, cl, mid, l, r, u);
  if (mid < r) update(root << 1 | 1, mid + 1, cr, l, r, u);
}

pdi pmax(pdi x, pdi y) {  // pair max函数
  if (cmp(x.first, y.first) == -1)
    return y;
  else if (cmp(x.first, y.first) == 1)
    return x;
  else
    return x.second < y.second ? x : y;
}

pdi query(int root, int l, int r, int d) {  // 查询
  if (r < d || d < l) return {0, 0};
  int mid = (l + r) >> 1;
  double res = calc(s[root], d);
  if (l == r) return {res, s[root]};
  return pmax({res, s[root]}, pmax(query(root << 1, l, mid, d),
                                   query(root << 1 | 1, mid + 1, r, d)));
}

int main() {
  ios::sync_with_stdio(false);
  int n, lastans = 0;
  cin >> n;
  while (n--) {
    int op;
    cin >> op;
    if (op == 1) {
      int x0, y0, x1, y1;
      cin >> x0 >> y0 >> x1 >> y1;
      x0 = (x0 + lastans - 1 + MOD1) % MOD1 + 1,
      x1 = (x1 + lastans - 1 + MOD1) % MOD1 + 1;
      y0 = (y0 + lastans - 1 + MOD2) % MOD2 + 1,
      y1 = (y1 + lastans - 1 + MOD2) % MOD2 + 1;
      if (x0 > x1) swap(x0, x1), swap(y0, y1);
      add(x0, y0, x1, y1);
      update(1, 1, MOD1, x0, x1, cnt);
    } else {
      int x;
      cin >> x;
      x = (x + lastans - 1 + MOD1) % MOD1 + 1;
      cout << (lastans = query(1, 1, MOD1, x).second) << endl;
    }
  }
  return 0;
}
```

---

## 作者：cjlak1o1 (赞：46)

~~这个hack数据是真的强。~~

模板题的题解很重要哦，希望你能找到适合自己的。

[博客食用更佳哦](https://www.cnblogs.com/windseekerblog/p/16600139.html)

## 李超线段树的定义

对于李超线段树的定义，[JHSeng](https://www.cnblogs.com/JHSeng/p/10896570.html)大佬的定义简洁精炼：

**李超线段树是一种用于维护平面直角坐标系内线段关系的数据结构。**

而[洛谷P4097Segment](https://www.luogu.com.cn/problem/P4097)就是李超线段树维护的板子题了。

题目大意（~~偷个懒~~）：

```
要求在平面直角坐标系下维护两个操作：

1. 在平面上加入一条线段。记第 i 条被插入的线段的标号为 i。

2. 给定一个数 k，询问与直线 x=k 相交的线段中，交点纵坐标最大的线段的编号。
```

## 具体维护操作

我们主要维护区间内**最优线段（交点纵坐标最大的线段的编号）**。

我们假设平面内已有一条线段：

![](https://cdn.luogu.com.cn/upload/image_hosting/oudc7e40.png)

这时显然，其为所有区间内的最优线段，接下来我们再插入一条线段。
![](https://cdn.luogu.com.cn/upload/image_hosting/e9j7othh.png)

明显可以看出，插入新的线段后，两条线段的交点左区间最优线段为新线段，而交点右边区间最优线段则为原来的线段。扫一遍肯定来不及，所以我们**二分递归**求出所有区间的最优线段。

首先先取当前处理区间的 $mid$，如果新线段在 $x=mid$ 时纵坐标更大，则**先将当前区间的最优线段更替为新线段**，从这里可以看出，每一个区间长度大于一的区间存的线段，**只满足取区间内大部分横坐标其为最优解。**

```cpp
if(f[i](mid)-f[id](mid)>eps) swap(i,id);
```

![](https://cdn.luogu.com.cn/upload/image_hosting/nkaejwuk.png)

红色线段为最优线段。

但是实际上交点右边的区间最优线段不是它，所以我们要两条线段再次进行比较，比较区间的左右两端点（即是判断区间内两条线段是否有交点，有交点说明要重新更新）。

如果被淘汰的线段在左右端点的比较中胜出，则将它继续递归，更新。

```cpp
if(f[i](l)-f[id](l)>eps||(f[i](l)==f[id](l)&&i<id)) update(lson,ql,qr,i);
if(f[i](r)-f[id](r)>eps||(f[i](r)==f[id](r)&&i<id)) update(rson,ql,qr,i);
```
最后得出所有区间的最优线段。

![](https://cdn.luogu.com.cn/upload/image_hosting/9osmuu1l.png)

询问的时候单点询问，递归取 max 即可。

## 一个蒟蒻入坑过的小问题

蒟蒻在第一次写李超线段树的时候，非常不明白询问的时候为什么要取 max。单点询问直接取当前点的最优线段不就行了，在经过思考后，发现：

1. 李超线段树**没有或者说不需要 push_down 操作**，所以可能当前点并没有值。

2. 李超线段树**大区间和小区间内存的都不一定是最优线段**，大区间刚刚讲过了，只是满足大部分，而小区间由于没有 push_down 也可能出现**存的不是最优解**，例如如图所示的情况。

![](https://cdn.luogu.com.cn/upload/image_hosting/chsfj66q.png)

当前询问 $x$ 点的最高纵坐标，加入第二条直线时，一二条直线右边区间的最优线段变为了图中粉色区间，而再加入第三条线段时，更新最优线段后，新线段在中间和右端点都是压倒性优势，所以图示粉色区间并没有被递归更新，造成了小区间非最优解的情况。

## code
```cpp
#include<bits/stdc++.h>
#define ls rt<<1
#define rs rt<<1|1
#define lson ls,l,mid
#define rson rs,mid+1,r
#define mp make_pair
#define db double
using namespace std;
const int N=4e5+10,M=39990,Inf=1e9+7;
const double eps=1e-10;//可能误差较小，无法比较，所以取eps

inline int read(){
	char ch=getchar();int res=0,f=1;
	while(ch<'0'||'9'<ch){if(ch=='-')f=-1;ch=getchar();}
	while('0'<=ch&&ch<='9') res=res*10+ch-'0',ch=getchar();
	return res*f;
}

struct line{
	db k,b;int xmi,xma;
	db operator()(int x){//重载括号 
		if(xmi<=x&&x<=xma) return k*x+b;//由于不是直线，判断是否在符合范围内
		else return -Inf;//不是返回极小值
	}
}f[N];

struct TREE{
	int id[N<<2];
	pair<db,int> _max(pair<db,int> a,pair<db,int> b){//定义max函数
		if(a.first-b.first>eps) return a;
		else if(b.first-a.first>eps) return b;
		else return a.second<b.second?a:b;
	}//有些人可能会问pair取max不是直接按第一第二关键字以此比较的吗，但是蒟蒻感觉不知道是不是精度的问题，那样会炸，希望巨佬能为我解答。
	void update(int rt,int l,int r,int ql,int qr,int i){
		if(ql<=l&&r<=qr){
			//没有直接更新 
			if(!id[rt]) return id[rt]=i,void();
			int mid=(l+r)>>1;//更新的时候交换，可能被淘汰的线段在左右区间会是最优线段
			if(f[i](mid)-f[id[rt]](mid)>eps) swap(i,id[rt]);
			//等于时让编号小的去更新 
			if(f[i](l)-f[id[rt]](l)>eps||(f[i](l)==f[id[rt]](l)&&i<id[rt])) update(lson,ql,qr,i);
			if(f[i](r)-f[id[rt]](r)>eps||(f[i](r)==f[id[rt]](r)&&i<id[rt])) update(rson,ql,qr,i);
			return;
		}
		int mid=(l+r)>>1;
		if(ql<=mid) update(lson,ql,qr,i);
		if(mid<qr) update(rson,ql,qr,i);
	}
	pair<db,int> query(int rt,int l,int r,int k){
		pair<double,int> res;
		if(id[rt]) res=mp(f[id[rt]](k),id[rt]);
		if(l==r) return res;
		int mid=(l+r)>>1;
		if(k<=mid) res=_max(query(lson,k),res);
		else res=_max(query(rson,k),res);
		return res;
	}
}root;

int n,lst,cnt;

int main()
{
	n=read();
	for(int i=1,op,k,x0,x1,y0,y1;i<=n;i++)
	{
		op=read();
		if(op==0){
			k=read();k=(k+lst-1)%39989+1;
			printf("%d\n",lst=root.query(1,1,M,k).second);
		}
		else{
			x0=read(),y0=read(),x1=read(),y1=read();
			x0=(x0+lst-1)%39989+1;x1=(x1+lst-1)%39989+1;
			y0=(y0+lst-1)%1000000000+1;y1=(y1+lst-1)%1000000000+1;
			cnt++;
			if(x0==x1){
				f[cnt].k=0;
				f[cnt].b=max(y1,y0);
				f[cnt].xmi=f[cnt].xma=x0;
			}
			else{
				f[cnt].k=1.0*(1.0*y1-y0)/(1.0*x1-x0);
				f[cnt].b=1.0*(1.0*y1-f[cnt].k*x1);
				f[cnt].xmi=min(x0,x1);
				f[cnt].xma=max(x0,x1);
			}
			root.update(1,1,M,min(x0,x1),max(x0,x1),cnt);
		}
	}
	return 0;
}
/*
3
1 8 7 3 9
1 10 9 4 3
0 8
*/
/*
1
*/
```
## 一些可以用李超做的题目

[P4097Segment](https://www.luogu.com.cn/problem/P4655) 

[P4254Blue Mary开公司](https://www.luogu.com.cn/problem/P4254) 

[P4655Building Bridges](https://www.luogu.com.cn/problem/P4655)






---

## 作者：Glacial_Shine (赞：24)

**2025.1.16 UPD**：之前的描述有些许笼统，修改了一下使其更为详细。

来本蒟蒻的[博客](https://blog.csdn.net/weixin_46700592/article/details/133041704)看看吧！！！

这是一个版题，既然是版题，那就得讲讲这个算法。（废话

# 引言
在很长一段时间，我一直都以为 $\text{Link-Cut Tree}$ 和李超线段树是一个东西，毕竟都是 $\text{LCT}$。（雾

直到学了 $\text{Link-Cut Tree}$ 才知道两者不是一个东西，虽然当时很好奇李超线段树是啥，但因为比较菜，一直到今天才学……

# 原理
~~总所周知，李超线段树是一颗线段树。~~

李超线段树是用来解决如下问题的：

给定一个平面直角坐标系，支持**动态**插入一条线段，对于每一个询问，给一条竖线，问这条竖线与所有线段的**最高的交点**（即 $y$ 值最大）。

![](https://cdn.luogu.com.cn/upload/image_hosting/7nj8vgs6.png)

如上图，两条蓝色的直线就是两个询问，那么答案分别就是 $A$ 点和 $B$ 点。

我们先引入一个概念，**最优势线段**，就是当前区间**中点处**最高的线段。

李超线段树维护的是有可能成为当前区间的**最优势线段**。某个节点的**最优势线段**在这个节点到根节点路径上所有**最优势线段**的之中。

为什么要这样维护呢？

因为不这样做的话加入一个线段你就要遍历整个区间，此时时间复杂度就会退化的十分严重（可能到 $n^2$）。

而如果像我们这样子维护的话，我们就不用每次加入线段都遍历整个区，而是可以在一个可以替换的区间停下。

我们先来看看如何**插入线段**。

我们会分为以下几种情况：

- 该线段与当前线段树枚举到的区间**不相交**，此时直接返回即可。
- 该线段覆盖**部分**当前线段树枚举到的区间，递归到左右子区间继续处理。（前两步其实就是将线段用线段树上的区间覆盖）
- 该线段**完全覆盖**当前线段树枚举到的区间，则继续分类

  - 该线段在两个端点处值**均比**当前区间的最优势线段**更大**，则将当前区间的最优势线段设为该线段，然后返回。（此时旧的最优势线段已经无用了）
  - 该线段在两个端点处的值**均比**当前区间的最优势线段**更小**，则返回。（此时我们新加的线段也已经无用了）
  - 现在只剩下一个端点新加入的线段大，另一个端点区间的最优势线段大的情况，我们可以这样考虑。

    因为我们一个区间存储的是中点位置的最优势线段，所以我们需要判断一下新加入的线段和原先区间的最优势线段在中点位置的大小，并且更新改区间的最优势线段。

    因为这两个线段不能互相替代，所以我们并不能直接将一个线段舍弃，也就是说我们要将没被记录的线段往两边递归，但是由于在中点处未被记录的线段更小，所以在某一边该线段是完全小于被记录的线段的，所以不需要往该边递归，只需要往另一边递归即可。（被记录的线段指的是被存储到该区间的最优势线段，未被记录的线段指的是另一条线段）
    

  ~~（有点长，耐心点看）~~

这样子我们动态插入线段就搞定了，可以参照下面代码理解理解：

```cpp
bool pd(int i, int j, int x) {
	//即比较两个线段在该位置的大小，由于精度问题，需要特殊处理一下，不然会被卡
    if (a[i].k * x + a[i].b - a[j].k * x - a[j].b > eps)
        return true;
    if (a[j].k * x + a[j].b - a[i].k * x - a[i].b > eps)
        return false;
    return i < j;
}
void change(int &x, int l, int r, int sl, int sr, int now) {
	//now是插入线段的编号
    if (r < sl || sr < l)//不相交
        return ;
    if (!x)//动态开点
        x = ++Tcnt;
    if (sl <= l && r <= sr) {//完全覆盖
        if (pd(now, tr[x].id, l) && pd(now, tr[x].id, r)) {
            tr[x].id = now;
            return ;
        }
        if (pd(tr[x].id, now, l) && pd(tr[x].id, now, r))
            return ;
        int mid = (l + r) >> 1;
        if (pd(now, tr[x].id, mid))
            swap(now, tr[x].id);
        if (pd(now, tr[x].id, l))
            change(tr[x].ls, l, mid, sl, sr, now);
        if (pd(now, tr[x].id, r))
            change(tr[x].rs, mid + 1, r, sl, sr, now);
    }
    else {//覆盖部分
        int mid = (l + r) >> 1;
        change(tr[x].ls, l, mid, sl, sr, now), change(tr[x].rs, mid + 1, r, sl, sr, now);
    }
}
```

查询就更简单了，直接往下找到该区间，并且将路径上所有区间的最优势线段都拿出来比较一下，可以参照下面代码理解。

```cpp
void solve(int x, int l, int r, int s) {
    if (!x || r < s || s < l)
        return ;
    if (pd(tr[x].id, ansid, s))//这里记录的是编号
        ansid = tr[x].id;
    if (l == r)
        return ;
    int mid = (l + r) >> 1;
    solve(tr[x].ls, l, mid, s), solve(tr[x].rs, mid + 1, r, s);
}
```

到这里，李超线段树就完成了！！！

考虑一下时间复杂度，我们知道线段会在线段树上分成 $\log n$ 个区间，而看到我们插入操作，分成的每个区间不会再分裂，而只会往一边更新，最多更新 $\log n$ 层，所以时间复杂度是 $log^2 n$。

其实对于所有的斜率优化 $\text{DP}$，都可以用李超线段树解决，只是时间会套上 $\log^2n$。（毕竟斜率优化 $\text{DP}$ 本质上是用直线来优化 $\text{DP}$，这就很能李超树）

然后我们就可以来看这道版题，没什么好说的，直接上代码。

唯一的坑点就是精度问题。

```cpp
#include <bits/stdc++.h>
using namespace std;
const double eps = 1e-9;
int T, Lastans, n = 39989, m, Tcnt, Rt, ansid;
struct Line { double k, b; } a[1000005];
struct Tree { int ls, rs, id; } tr[10000005];
bool pd(int i, int j, int x) {
    if (a[i].k * x + a[i].b - a[j].k * x - a[j].b > eps)
        return true;
    if (a[j].k * x + a[j].b - a[i].k * x - a[i].b > eps)
        return false;
    return i < j;
}
void change(int &x, int l, int r, int sl, int sr, int now) {
    if (r < sl || sr < l)
        return ;
    if (!x)
        x = ++Tcnt;
    if (sl <= l && r <= sr) {
        if (pd(now, tr[x].id, l) && pd(now, tr[x].id, r)) {
            tr[x].id = now;
            return ;
        }
        if (pd(tr[x].id, now, l) && pd(tr[x].id, now, r))
            return ;
        int mid = (l + r) >> 1;
        if (pd(now, tr[x].id, mid))
            swap(now, tr[x].id);
        if (pd(now, tr[x].id, l))
            change(tr[x].ls, l, mid, sl, sr, now);
        if (pd(now, tr[x].id, r))
            change(tr[x].rs, mid + 1, r, sl, sr, now);
    }
    else {
        int mid = (l + r) >> 1;
        change(tr[x].ls, l, mid, sl, sr, now), change(tr[x].rs, mid + 1, r, sl, sr, now);
    }
}
void solve(int x, int l, int r, int s) {
    if (!x || r < s || s < l)
        return ;
    if (pd(tr[x].id, ansid, s))
        ansid = tr[x].id;
    if (l == r)
        return ;
    int mid = (l + r) >> 1;
    solve(tr[x].ls, l, mid, s), solve(tr[x].rs, mid + 1, r, s);
}
int main() {
    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);
    scanf("%d", &T);
    while (T--) {
        int id;
        scanf("%d", &id);
        if (id == 0) {
            int x;
            ansid = 0;
            scanf("%d", &x), x = (x + Lastans - 1) % n + 1;
            solve(1, 1, n, x), Lastans = ansid;
            printf("%d\n", ansid);
        }
        else {
            int sx, sy, ex, ey;
            scanf("%d%d%d%d", &sx, &sy, &ex, &ey);
            sx = (sx + Lastans - 1) % n + 1, sy = (sy + Lastans - 1) % 1000000000 + 1, ex = (ex + Lastans - 1) % n + 1, ey = (ey + Lastans - 1) % 1000000000 + 1;
            if (ex < sx)
                swap(sx, ex), swap(sy, ey);
            if (ex != sx)
                m++, a[m].k = 1.0 * (ey - sy) / (ex - sx), a[m].b = 1.0 * sy - a[m].k * sx;
            else
                m++, a[m].k = 0, a[m].b = max(sy, ey);
            // a[m].k *= 10, a[m].b *= 10;
            change(Rt, 1, n, sx, ex, m);
        }
    }
    return 0;
}
```

---

## 作者：tyccyt (赞：8)

# P4097 【模板】李超线段树

## 前置知识

- #### [线段树的基本思路](https://oi-wiki.org/ds/seg/)

- #### [初中八年级基础知识](https://baike.baidu.com/item/%E4%B8%80%E6%AC%A1%E5%87%BD%E6%95%B0/1653577)

## 大体思路

李超线段树利用线段树思想，

可以支持维护支持区间插入线段，与单点查询最值。

在线段树中，每个节点存放线段的**下标**，同时，存的这一条线段在该区间内**大部分**处于比其他线段更高的位置

## 具体思路

- ### 变量

  ```cpp
  int n,cnt;
  /*
  cnt:目前线段数
  */
  struct node
  {
  	long double k,b;
      /*
      k:斜率
      b:y轴截距
      */
  }a[D];//每个线段y轴的斜率、截距
  int t[N<<4];//线段树
  ```

  

- ### 查询

  ```cpp
  inline int Max(int p,int q,int x)
  {
      if(f(p,x)!=f(q,x))
      {
          if(f(p,x)>f(q,x))
          {
              return p;
          }
          return q;
      }
      return min(p,q);
  }
  inline int query(int k,int l,int r,int x)//x:横坐标，k:线段树中的节点下标
  {
  	if(l==r)return t[k];
  	int mid=(l+r)>>1;
  	if(x<=mid)return Max(t[k],query(k<<1,l,mid,x),x);
  	else return Max(t[k],query(k<<1|1,mid+1,r,x),x);
      /*
      if,else作用：
      求最大的纵坐标
      */
  }
  ```

  

- ### 修改

  下图中**橙线**指**新**的一条线，**红线**指**目前在线段树中**的线。

  设 $a$ 为橙线，$b$ 为红线，

  $k_a$ 为橙线斜率，$k_b$ 为红线斜率，

  $l$ 为当前线段树区间左端点，$r$ 为当前线段树区间右端点，

  $mid$ 为前线段树区间中点。

  - #### $k_a>k_b$

    - #### 在 $mid$ 处， $a$ 比 $b$ 高。

      ![img](https://cdn.luogu.com.cn/upload/image_hosting/p0be4uw1.png)

      在左子树中 $a$ **仍可能**比 $b$ 高，

      这时，我们更新 $a$ 为这个区间最高的直线，

      将 $b$ 下传至左子树。

    - #### 在 $mid$ 处， $a$ 比 $b$ 低。

      ![img](https://cdn.luogu.com.cn/upload/image_hosting/rcxoejm5.png)

      在右子树中 $b$ **仍可能**比 $a$ 高，

      这时，我们仍用 $b$ 作为这个区间最高的直线，

      将 $a$ 下传至右子树。

  - #### $k_a<k_b$

    - #### 在 $mid$ 处， $a$ 比 $b$ 高。

      #### ![img](https://cdn.luogu.com.cn/upload/image_hosting/qbkzgi4k.png)

      在右子树中 $b$ **仍可能** 比 $a$ 高，

      这时，我们更新 $a$ 为这个区间最高的直线，

      将 $b$ 下传至右子树。

    - #### 在 $mid$ 处， $a$ 比 $b$ 低。

      #### ![img](https://cdn.luogu.com.cn/upload/image_hosting/dj2dajtp.png)

      在左子树中 $a$ **仍可能** 比 $b$ 高，

      这时，我们仍用 $b$ 作为这个区间最高的直线，

      将 $a$ 下传至左子树。

  - ### $a$ 在区间内，起点高，终点高。

    ![img](https://cdn.luogu.com.cn/upload/image_hosting/q7k4i6nm.png)

    这样的话，$b$ 就没用了，将 $a$ 取代 $b$。

  - ### $b$ 在区间内，起点高，终点高。

    ![img](https://cdn.luogu.com.cn/upload/image_hosting/eoahwcap.png)

    这样的话，$a$ 就没用了，保留 $b$。

  加一条线段时的代码如下：

  ```cpp
  inline long double f(int w,int x){return {a[w].k*x+a[w].b};}
  inline void modify(int k,int l,int r,int x,int y,int w)
  {
  	int mid=(l+r)>>1;
  	if(x<=l&&r<=y)//将整个区间包含 
  	{//下面就是上述分类讨论
  		if(f(w,l)>f(t[k],l)&&f(w,r)>f(t[k],r))//起点终点都高 ，更改 
  		{
  			t[k]=w;
  			return;
  		}
  		if(f(w,l)<=f(t[k],l)&&f(w,r)<=f(t[k],r))//起点终点都矮 ，直接return 
  		{
  			return;
  		} 
  		if(a[w].k>a[t[k]].k)
  		{
  			if(f(w,mid)>f(t[k],mid))
  			{
  				modify(k<<1,l,mid,x,y,t[k]);
  				t[k]=w;
  			}
  			else
  			{
  				modify(k<<1|1,mid+1,r,x,y,w);
  			}
  		}
  		else
  		{
  			if(f(w,mid)>f(t[k],mid))
  			{
  				modify(k<<1|1,mid+1,r,x,y,t[k]);
  				t[k]=w;
  			}
  			else
  			{
  				modify(k<<1,l,mid,x,y,w);
  			}
  		}
  		return;
  	}
  	if(x<=mid)modify(k<<1,l,mid,x,y,w);
  	if(mid<y) modify(k<<1|1,mid+1,r,x,y,w);
  }
  ```

## 总代码（含注释）：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int mod = 39989;
const int Mod = 1000000000;
const int D=1e5+5; 
const int N=4e5+5;
int n,cnt;
struct node
{
	long double k,b;
}a[D];
int t[N<<4];
inline node get(long double x0,long double y0,long double x1,long double y1)
{//获取k,b
	if(x0==x1)return (node){0,max(y0,y1)};
	long double k=(y1-y0)/(x1-x0),b=y1-k*x1;
	return (node){k,b};
}
inline long double f(int w,int x){return {a[w].k*x+a[w].b};}//获取y坐标
inline void modify(int k,int l,int r,int x,int y,int w)
{
   	if(l==r)//当区间为一个点时，很好分辨哪个高，哪个低
 	{
 		if(f(w,l)>f(t[k],l))
 		{
 			t[k]=w;
 		}
 		return;
 	}
	int mid=(l+r)>>1;
	if(x<=l&&r<=y)//将整个区间包含 
	{//下面就是上述分类讨论
		if(f(w,l)>f(t[k],l)&&f(w,r)>f(t[k],r))//起点终点都高 ，更改 
		{
			t[k]=w;
			return;
		}
		if(f(w,l)<=f(t[k],l)&&f(w,r)<=f(t[k],r))//起点终点都矮 ，直接return 
		{
			return;
		} 
		if(a[w].k>a[t[k]].k)
		{
			if(f(w,mid)>f(t[k],mid))
			{
				modify(k<<1,l,mid,x,y,t[k]);
				t[k]=w;
			}
			else
			{
				modify(k<<1|1,mid+1,r,x,y,w);
			}
		}
		else
		{
			if(f(w,mid)>f(t[k],mid))
			{
				modify(k<<1|1,mid+1,r,x,y,t[k]);
				t[k]=w;
			}
			else
			{
				modify(k<<1,l,mid,x,y,w);
			}
		}
		return;
	}
	if(x<=mid)modify(k<<1,l,mid,x,y,w);
	if(mid<y) modify(k<<1|1,mid+1,r,x,y,w);
}
inline int Max(int p,int q,int x)
{
	if(f(p,x)!=f(q,x))
    {
        if(f(p,x)>f(q,x))
        {
            return p;
        }
        return q;
    }
    return min(p,q);
}
inline int query(int k,int l,int r,int x)
{
	if(l==r)return t[k];
	int mid=(l+r)>>1;
	if(x<=mid)return Max(t[k],query(k<<1,l,mid,x),x);
	else return Max(t[k],query(k<<1|1,mid+1,r,x),x);
}
int main()
{
	scanf("%d",&n);
	int last=0;
	for(int i=1,op,x0,x1,y0,y1,k;i<=n;i++)
	{
		scanf("%d",&op);
		if(op==0)
		{
			scanf("%d",&k);
			k=(k+last-1+mod)%mod+1;
			last=query(1,1,mod,k);
			cout<<last<<'\n';
		}
		else
		{
			scanf("%d%d%d%d",&x0,&y0,&x1,&y1);
			x0=(x0+last-1+mod)%mod+1;
			x1=(x1+last-1+mod)%mod+1;
			y0=(y0+last-1+Mod)%Mod+1;
			y1=(y1+last-1+Mod)%Mod+1;
			if(x0>x1)
			{
				swap(x0,x1);
				swap(y0,y1);
			}
			a[++cnt]=get(x0,y0,x1,y1);
			modify(1,1,mod,x0,x1,cnt);
		}
	}
	return 0;
}
```

## 关于Subtask #0  #5

### 输入：

```cpp
3
1 8 7 3 9
1 10 9 4 3
0 8
```

### 输出：

```cpp
1
```

由于```double```的**精度**原因，要开 ```long double``` ！！！

## 一些可能的疑问：

- 如果两条线的交点恰好在线段树中一个区间的中点怎么办？

  ![img](https://cdn.luogu.com.cn/upload/image_hosting/mzo0phbx.png)

  其实，这里的线段树主要是使查询时，$O(\log_2 n)$ 找到最大值；修改时，$O(\log_2 n)$ 修改罢了，随便一个下传**都可以**，因为查询的横坐标总会经过你要的正确答案的。

个人认为比较详细，望通过！！！

---

## 作者：cold_jelly (赞：8)

[推荐在我的博客查看](https://www.cnblogs.com/cold-jelly/p/18891748)

前置知识：[线段树](https://oi-wiki.org/ds/seg/)、基础解析几何知识。

本篇文章参考了 [Glacial_Shine](https://www.luogu.com.cn/user/363139) 的[这篇文章](https://www.luogu.com.cn/article/zx6bj5c0)，在此一并感谢。

****

### 简介

李超线段树是一种用于维护平面直角坐标系内线段关系的数据结构。

具体而言，李超线段树支持在平面直角坐标系中动态插入线段，支持快速询问给定竖线与所有线段交点的最大纵坐标。

例如，例题 [P4097 【模板】李超线段树 / [HEOI2013] Segment](https://www.luogu.com.cn/problem/P4097) 中，需要我们完成的操作：

- 在平面直角坐标系中插入一条线段；
- 给定 $k$，求所有线段与直线 $x=k$ 的交点的纵坐标最大值。

就可以用李超线段树维护。

如果还不理解的话，下图展示了插入了 $5$ 条线段后，分别询问 $k=3,6$ 的答案点：

![](https://cdn.luogu.com.cn/upload/image_hosting/jydpxs31.png)

### 原理与实现

李超线段树是线段树的一种，所以其操作与普通线段树的操作基本一致。

以上面的例题为例，我们来好好讲讲李超线段树的原理。

对于一个研究区间，我们只关心该区间中的**最优线段**。何为最优线段？我们规定在区间 $[L,R]$ 中，与直线 $x=\dfrac{L+R}{2}$ 交点纵坐标最大的线段为该区间内的最优线段。李超线段树通过维护小区间内的最优线段，然后在每次询问某节点的最优线段时遍历这个节点到根节点的路径，从路径中的所有最优线段中找出答案。

对于例题中的第一种操作，即插入操作（insert），我们不妨考虑即将插入的这条线段对一定区间内维护的最优线段的影响情况。

采用分类讨论的思想，我们不难发现可以分为这样几种情况：

1. 该线段与区间没有交集，因此对区间内维护的最优线段没有影响；
2. 该线段与区间有交集，但区间不是该线段定义域的子集，此时考虑递归到该区间的左右子区间作进一步细化处理；
3. 区间是该线段定义域的子集，此时分三种情况讨论：
- 若该线段在区间两端点处纵坐标均比该区间内原先最优线段的大，那么可以形象地理解为该线段在该区间内**完全碾压**原先最优线段，往后该区间内其不可能再成为最优线段了，所以该线段成为新的最优线段，原本的舍弃；
- 若该线段在区间两端点处纵坐标均比该区间内原先最优线段的小，那么可以形象地理解为该线段在该区间内**被**原先最优线段**完全碾压**，同上，区间内最优线段不做任何修改，将该线段舍弃；
- 否则，该线段与原先的最优线段一定有交点，考虑最优线段的定义，我们比较在区间中点 $mid=\dfrac{L+R}{2}$ 处两条线段对应的纵坐标谁大，将大的那条作为新的最优线段。但由于这两条线段相互之间都不能被对方完全碾压，所以考虑将没成为最优线段的那条线段往该区间的左右子区间下放，作递归处理（只需要往有比最优线段更优的一端递归即可）。

可以结合下面的图示理解（黑色线段为待插入线段，蓝色线段为区间原先最优线段）：

![](https://cdn.luogu.com.cn/upload/image_hosting/7bu31izz.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/s837nzdl.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/2hefgjwx.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/6itxr2pv.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/2p4dl9sh.png)

李超线段树需要好好根据示意图来理解，如果没懂的话再反复看几遍。

具体实现的话可以参考代码：

```cpp
	inline double Ycalc(int i, int X)//计算纵坐标 
	{
		return line[i].k * X + line[i].b;
	}
	inline bool cmp(int i, int j, int X)//比较编号为 i 和 j 的线段在 X 处的纵坐标 
	{
		//由于精度误差，不能直接比较 
		if(Ycalc(i, X) - Ycalc(j, X) > eps) return true;
		if(Ycalc(j, X) - Ycalc(i, X) > eps) return false;
		return i < j;
	}
	void insert(int &u, int l, int r, int L, int R, int id)//插入线段，编号为 id 
	{
		//区间为 [l, r] 
		if(r < L || R < l) return;//线段与该区间不交 
		if(!u) u = ++ cnt;//动态开点 
		if(L <= l && r <= R)//线段完全覆盖该区间 
		{
			if(cmp(id, tr[u].id, l) && cmp(id, tr[u].id, r))//该线段比当前区间最优线段完全更优 
			{
				tr[u].id = id;
				return;
			}
			if(cmp(tr[u].id, id, l) && cmp(tr[u].id, id, r))//该线段比当前区间最优线段完全更劣
				return;
			//两线段有交点，都不能完全覆盖彼此 
			int mid = (l + r) / 2;
			if(cmp(id, tr[u].id, mid)) swap(id, tr[u].id);
			//处理左右子区间 
			if(cmp(id, tr[u].id, l)) insert(tr[u].l, l, mid, L, R, id);
			if(cmp(id, tr[u].id, r)) insert(tr[u].r, mid + 1, r, L, R, id);
		}
		else//线段覆盖部分该区间 
		{
			int mid = (l + r) / 2;
			//处理左右子区间 
			insert(tr[u].l, l, mid, L, R, id);
			insert(tr[u].r, mid + 1, r, L, R, id);
		}
	}
```

我的李超线段树是用动态开点实现的，所以不需要建树。

线段在树上被分割为 $\log n$ 个小区间，最多向下递归 $\log n$ 层，因此插入操作的时间复杂度是 $O(\log^2 n)$ 的。

对于例题中的第二种操作，即查询操作（query），我们在树上查询，在路径上的所有区间的最优线段找到最优的那一个，注意本题所求的是线段的编号 $id$。

```cpp
	void query(int u, int l, int r, int X)
	{
		if(!u || r < X || X < l) return; 
		if(cmp(tr[u].id, ans, X)) ans = tr[u].id;//比较路径上的最优线段，记录编号 
		if(l == r) return;
		//在树上往下查询最优线段 
		int mid = (l + r) / 2;
		query(tr[u].l, l, mid, X);
		query(tr[u].r, mid + 1, r, X);
	}
```

同插入操作的分析，查询操作的时间复杂度是 $O(\log n)$ 的。

分析完毕，建议反复看几遍加深理解，实在不行可以再结合总代码理解：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e5 + 10;
const double eps = 1e-10;//调精度 
struct Line//线段 
{
	double k, b;//直线参数 
}line[N];
int n, op, k, x_0, x_1, y_0, y_1;
const int mod1 = 39989, mod2 = 1e9;
int ans, lastans;
int root;
int Lcnt;
struct LiChaoSegmentTree//李超线段树 
{
	int cnt;
	struct Tree
	{
		int l, r;//区间左右端点 
		int id;//编号 
	}tr[N * 4];
	inline double Ycalc(int i, int X)//计算纵坐标 
	{
		return line[i].k * X + line[i].b;
	}
	inline bool cmp(int i, int j, int X)//比较编号为 i 和 j 的线段在 X 处的纵坐标 
	{
		//由于精度误差，不能直接比较 
		if(Ycalc(i, X) - Ycalc(j, X) > eps) return true;
		if(Ycalc(j, X) - Ycalc(i, X) > eps) return false;
		return i < j;
	}
	void insert(int &u, int l, int r, int L, int R, int id)//插入线段，编号为 id 
	{
		//区间为 [l, r] 
		if(r < L || R < l) return;//线段与该区间不交 
		if(!u) u = ++ cnt;//动态开点 
		if(L <= l && r <= R)//线段完全覆盖该区间 
		{
			if(cmp(id, tr[u].id, l) && cmp(id, tr[u].id, r))//该线段比当前区间最优线段完全更优 
			{
				tr[u].id = id;
				return;
			}
			if(cmp(tr[u].id, id, l) && cmp(tr[u].id, id, r))//该线段比当前区间最优线段完全更劣
				return;
			//两线段有交点，都不能完全覆盖彼此 
			int mid = (l + r) / 2;
			if(cmp(id, tr[u].id, mid)) swap(id, tr[u].id);
			//处理左右子区间 
			if(cmp(id, tr[u].id, l)) insert(tr[u].l, l, mid, L, R, id);
			if(cmp(id, tr[u].id, r)) insert(tr[u].r, mid + 1, r, L, R, id);
		}
		else//线段覆盖部分该区间 
		{
			int mid = (l + r) / 2;
			//处理左右子区间 
			insert(tr[u].l, l, mid, L, R, id);
			insert(tr[u].r, mid + 1, r, L, R, id);
		}
	}
	void query(int u, int l, int r, int X)
	{
		if(!u || r < X || X < l) return; 
		if(cmp(tr[u].id, ans, X)) ans = tr[u].id;//比较路径上的最优线段，记录编号 
		if(l == r) return;
		//在树上往下查询最优线段 
		int mid = (l + r) / 2;
		query(tr[u].l, l, mid, X);
		query(tr[u].r, mid + 1, r, X);
	}
}T;
signed main()
{
	cin >> n;
	for(int i = 1; i <= n; i ++)
	{
		scanf("%lld", &op);
		if(op == 0)
		{
			scanf("%lld", &k);
			k = (k + lastans - 1) % mod1 + 1;
			ans = 0;
			T.query(1, 1, mod1, k);
			printf("%lld\n", ans);
			lastans = ans;
		}
		else
		{
			scanf("%lld%lld%lld%lld", &x_0, &y_0, &x_1, &y_1);
			x_0 = (x_0 + lastans - 1) % mod1 + 1;
			x_1 = (x_1 + lastans - 1) % mod1 + 1;
			y_0 = (y_0 + lastans - 1) % mod2 + 1;
			y_1 = (y_1 + lastans - 1) % mod2 + 1;
			if(x_1 < x_0)
			{
				swap(x_1, x_0);
				swap(y_1, y_0);
			}
			Lcnt ++;
			if(x_1 != x_0)
			{
				line[Lcnt].k = 1.0 * (y_1 - y_0) / (x_1 - x_0);
				line[Lcnt].b = 1.0 * y_0 - line[Lcnt].k * x_0;
			}
			else//特殊处理竖直线段 
			{
				line[Lcnt].k = 0;
				line[Lcnt].b = max(y_0, y_1);
			}
			T.insert(root, 1, mod1, x_0, x_1, Lcnt);
		}
	}
	return 0;
}
```

~~个人感觉马蜂海星，将就着看吧~~=￣ω￣=。

---

## 作者：不知名用户 (赞：4)

题意：

在二维平直坐标系支持以下两种操作：

- 插入线段
- 查询横坐标为 $x$ 在所有线段中纵坐标最大的编号，不存在则为 0，多个输出编号的最小的

前言：因为这是一篇题解，并且李超线段树存储的信息过于抽象，所以只讲实现，关于正确性等放在了这个[博客](https://www.luogu.com.cn/blog/nothavename/li-chao-xian-duan-shu-zheng-que-xing-ji-wei-hu-di-shi-shi-me-xin-xi)。希望读者先一口气读完再回看，因为在每个线段树区间存的（题目中实际）线段到底怎么办很难讲清楚（可能按不同顺序插入相同线段得到的线段树也不同！~~虽然还没造出数据~~）

李超线段树是以 $x$ 下标为节点的线段树。每个节点保存着一个完全覆盖它（这个节点对应线段树上区间）线段，不存在则为 $0$。（这到底是什么线段我也不是特别清楚，但是我知道这样一定是对的）

对于插入线段：

如果这是一条竖线 $(x_0,y)(y_0\le y\le y_1)$，就把它看作一个点 $x_0,y_1$。

```cpp
struct Line
{
	int x1, x2, y1, y2;
	lf get(int x)//拿到横坐标为 x 的值
	{
		if(x==x1) return y1;
		return (lf)1.0 * (y2 - y1) / (x2 - x1) * (x - x1) + y1;
	}
	void gi(int _x1, int _x2, int _y1, int _y2)
	{
		if(_x1>_x2) swap(_x1,_x2), swap(_y1,_y2);
		x1 = _x1, x2 = _x2, y1 = _y1, y2 = _y2;
		if(x1==x2) y1 = y2 = max(_y1,_y2);//竖线
	}
}s[N];int cur;
```

像正常的线段树一样，需要在覆盖 $x_0\to x_1$ 的线段打 tag（具体是哪些线段参照区间加，怎么 tag 等会儿说）：

```cpp
void ins(int p, int L, int R, int x)//x 表示线段编号
{
	if(s[x].x1<=L&&R<=s[x].x2) return tag(p,L,R,x), void();//别急，等会儿讲 tag
	int mid = L + R >> 1;
	if(s[x].x1<=mid) ins(p*2,L,mid,x);
	if(mid<s[x].x2) ins(p*2+1,mid+1,R,x);
}
```

对于打 tag，我们记插入的线段为 $f$，线段树原来的线段为 $g$，现在在线段树区间 $[L,R],mid=\frac{L+R}{2}$：

1. 若 $f$ 在 $mid$ 处更高，交换 $f,g$（即保持 $g$ 在 $mid$ 更高）
2. 若 $g$ 在 $L,R$ 处均比 $f$ 高，则 $f$ 无效
3. 若 $f$ 在 $L$ 处更高，说明线段的交点在 $[L,mid]$，在 $[mid+1,R]$ 处完全不比 $g$ 高，所以只需递归左子树；反之在 $R$ 处更高只需递归右子树

有点标记永久化的思想。

```cpp
bool eq(lf x, lf y){return x + eps > y && y + eps > x;}

bool cmpline(int a, int b, int x)//a 和 b 在 x 谁更大 
{
	lf aa = s[a].get(x), bb = s[b].get(x);
	if(eq(aa,bb)) return a < b;//为了满足题意的高度相同编号小
	else return aa > bb;
}

void tag(int p, int L, int R, int f)
{
	int mid = L + R >> 1, &g = seg[p];
	if(!g) return seg[p] = f, void();
	if(cmpline(f,g,mid)) swap(f,g);
	if(cmpline(g,f,L)&&cmpline(g,f,R)) return;//f 毫无作用
	if(cmpline(f,g,L)) tag(p*2,L,mid,f);
	else tag(p*2+1,mid+1,R,f);
}
```

对于单点查询：~~显而易见~~只有在线段树从根到该位置一路经过节点上的线段有效，直接比较即可。

```cpp
int ask(int p, int L, int R, int x)
{
	int mn = seg[p], mid = L + R >> 1, m2 = 0;
	if(L==R) return mn;
	if(x<=mid) m2 = ask(p*2,L,mid,x);
	else m2 = ask(p*2+1,mid+1,R,x);
	if(!mn||cmpline(m2,mn,x)) mn = m2;
	return mn;
}
```

复杂度：插入线段在线段树上有 $\log LEN$，tag 又有 $\log LEN$，单点查询 $\log LEN$，故总为 $\Theta(n\log^2LEN)$。

```cpp
#include<bits/stdc++.h>
#define lf long double 
using namespace std;

const int N = 1e5 + 10, M = 4e4 + 10;
const lf eps = 1e-9;

bool eq(lf x, lf y){return x + eps > y && y + eps > x;}

struct Line
{
	int x1, x2, y1, y2;
	lf get(int x)
	{
		if(x==x1) return y1;
		return (lf)1.0 * (y2 - y1) / (x2 - x1) * (x - x1) + y1;
	}
	void gi(int _x1, int _x2, int _y1, int _y2)
	{
		if(_x1>_x2) swap(_x1,_x2), swap(_y1,_y2);
		x1 = _x1, x2 = _x2, y1 = _y1, y2 = _y2;
		if(x1==x2) y1 = y2 = max(_y1,_y2);
	}
}s[N];int cur;

int seg[M*4]; 

bool cmpline(int a, int b, int x)
{
	lf aa = s[a].get(x), bb = s[b].get(x);
	if(eq(aa,bb)) return a < b;
	else return aa > bb;
}

void tag(int p, int L, int R, int f)
{
	int mid = L + R >> 1, &g = seg[p];
	if(!g) return seg[p] = f, void();
	if(cmpline(f,g,mid)) swap(f,g);
	if(cmpline(g,f,L)&&cmpline(g,f,R)) return;
	if(cmpline(f,g,L)) tag(p*2,L,mid,f);
	else tag(p*2+1,mid+1,R,f);
}

void ins(int p, int L, int R, int x)
{
	if(s[x].x1<=L&&R<=s[x].x2) return tag(p,L,R,x), void();
	int mid = L + R >> 1;
	if(s[x].x1<=mid) ins(p*2,L,mid,x);
	if(mid<s[x].x2) ins(p*2+1,mid+1,R,x);
}

int ask(int p, int L, int R, int x)
{
	int mn = seg[p], mid = L + R >> 1, m2 = 0;
	if(L==R) return mn;
	if(x<=mid) m2 = ask(p*2,L,mid,x);
	else m2 = ask(p*2+1,mid+1,R,x);
	if(!mn||cmpline(m2,mn,x)) mn = m2;
	return mn;
}

int main()
{
	int n, lst = 0;
	cin>>n;
	while(n--)
	{
		int op;cin>>op;
		if(op==0)
		{
			int k;cin>>k;
			k = (k + lst - 1) % 39989 + 1;
			lst = ask(1,1,M-10,k);
			cout<<lst<<'\n';
		}
		else
		{
			int x1, y1, x2, y2;
			cin>>x1>>y1>>x2>>y2;
			x1 = (x1 + lst - 1) % 39989 + 1;
			x2 = (x2 + lst - 1) % 39989 + 1;
			y1 = (y1 + lst - 1) % 1000000000 + 1;
			y2 = (y2 + lst - 1) % 1000000000 + 1;
			s[++cur].gi(x1,x2,y1,y2);
			ins(1,1,M-10,cur);
		}
	}
	return 0;
} 
```

后记：由于李超线段树本身过于抽象，所以本人无法很直接地讲，在此深表歉意。希望有懂的读者向我推荐关于证明 正确性 以及 每个线段树区间的线段编号是什么意思 有关的文章。

---

## 作者：wosile (赞：3)

李超线段树。

其实感觉这个线段树也没什么特别的。

昨天晚上发现自己没写过这道题，就来写一写。然后今天早上把这题过了，发现半个小时内怎么有 $20$ 个提交，哪个邪恶势力上课在讲这题啊。

既然是区间修改单点查询，我们考虑上大力线段树。每个区间维护区间某点处值最大的线段是一个很自然的想法，这个点取线段树上的 `mid` 即可。

然后很难受的一点是，修改标记的时候不能大力修改，如果直接把标记覆盖掉，可能被覆盖的线段虽然在 `mid` 处比新线段小，但是在某些地方比新线段大，直接覆盖掉的话这个信息就丢失了。

所以我们需要在覆盖标记的时候下传标记。

一种下传标记复杂度正确性的理解：如果在某个区间内一个线段完全覆盖另一个，就不用下传标记可以直接更新。更新某个区间标记的时候，我们只需要下传两个线段交点所在的那个区间即可。因为这两个线段的交点最多只有一个，所以每个区间下传标记最多只会下传到左右儿子中的一个，即总共下传 $O(h)=O(\log n)$ 次。在线段树上一个线段会被拆成 $O(\log n)$ 个线段，所以修改的复杂度是 $O(\log^2 n)$。

好像大家都喜欢标记永久化的写法，这道题里这样写常数显著更小而且可以做到 $O(\log n)$ 查询。但是我写了个用 `pushdown` 的，感觉非常好写。

这题对精度的要求没那么高，不用写分数来比较线段。

~~实际上我写的分数类常数太大直接 TLE 了。~~

```cpp
#include<bits/stdc++.h>
using namespace std;
#define eps 1e-8
namespace IO{
	int read(){
		int x=0,c=getchar(),f=1;
		while(c<'0' || c>'9'){
			if(c=='-')f=-1;
			c=getchar();
		}
		while(c>='0' && c<='9'){
			x=(x<<3)+(x<<1)+c-'0';
			c=getchar();
		}
		return f==1?x:-x;
	}
	void write(int x){
		if(x<0){
			putchar('-');
			write(-x);
			return;
		}
		if(x>9)write(x/10);
		putchar(x%10+48);
	}
	void write(int x,char div){
		write(x);
		putchar(div);
	}
	void write(const char *s){
		int pos=0;
		while(s[pos])putchar(s[pos++]);
	}
}
using namespace IO;
#define N 40000
struct seg{
	double k,b;
	int id;
	seg(){k=0,b=0,id=0;}
	seg(double k_,double b_,int id_):k(k_),b(b_),id(id_){}
	double f(int x){
		return k*x+b;
	}
}tag[200005];
inline bool cmp(seg x,seg y,int pos){
	// 比较两条线段在 x=pos 处的取值
	if(x.f(pos)-y.f(pos)>eps)return true;
	if(y.f(pos)-x.f(pos)>eps)return false;
	return x.id<y.id;
}
int stp=0,sdp=0,sqp=0;
inline void updtag(int l,int r,int x,seg s){
	int mid=(l+r)/2;
	if(cmp(s,tag[x],mid))swap(tag[x],s);
	if(cmp(s,tag[x],l))updtag(l,mid,x<<1,s);
	if(cmp(s,tag[x],r))updtag(mid+1,r,x<<1|1,s);
	// 显然两个 if 最多只会成立一个。若两个都成立会被 swap。
}
inline void pushdown(int l,int r,int x){
	// pushdown 挺好写的
	int mid=(l+r)/2;
	if(tag[x].id){
		updtag(l,mid,x<<1,tag[x]);
		updtag(mid+1,r,x<<1|1,tag[x]);
		tag[x]=seg(0,0,0);
	}
}
inline int query(int l,int r,int x,int pos){
	if(l==r)return tag[x].id;
	int mid=(l+r)/2;
	pushdown(l,r,x);
	if(pos<=mid)return query(l,mid,x<<1,pos);
	else return query(mid+1,r,x<<1|1,pos);
}
inline void upd(int l,int r,int x,int L,int R,seg s){
	if(L<=l && r<=R){
		updtag(l,r,x,s);
		return;
	}
	int mid=(l+r)/2;
	pushdown(l,r,x);
	if(L<=mid)upd(l,mid,x<<1,L,R,s);
	if(R>mid)upd(mid+1,r,x<<1|1,L,R,s);
}
int main(){
	int T=read(),lastans=0;
	int tot=0;
	while(T--){
		int op=read();
		if(op==0){
			int x=(read()+lastans-1)%39989+1;
			write(lastans=query(1,N,1,x),10);
		}
		else{
			int x0=(read()+lastans-1)%39989+1;
			int y0=(read()+lastans-1)%1000000000+1;
			int x1=(read()+lastans-1)%39989+1;
			int y1=(read()+lastans-1)%1000000000+1;
			if(x0>x1){
				swap(x0,x1);
				swap(y0,y1);
			}
			if(x0==x1)upd(1,N,1,x0,x1,seg(0,max(y0,y1),++tot));
			else{
				double tk=1.0*(y0-y1)/(x0-x1);
				double tb=y0-tk*x0;
				upd(1,N,1,x0,x1,seg(tk,tb,++tot));
			}
		}
	}
	return 0;
}
//quod erat demonstrandum
```

---

## 作者：2020tanjunming (赞：3)

## 介绍
李超线段树，是用来解决平面直角坐标系中直线或线段的集合在某一点 $x$ 处的最大值或最小值问题。

在实现李超线段树的时候，打的标记是不用下传的，也就是标记永久化。在查询时，根节点到对应叶节点上的所有节点的贡献都要计算。

线段树的区间对应的是平面直角坐标系的 $x$ 轴上的区间，对于每个区间，要维护的是在这个区间上较优的直线或线段。


## 维护线段

在线段树上的操作如下：
- 修改操作：加入一条线段
- 查询操作：查询所有包含 $x=x_0$ 的线段在 $x=x_0$ 时能取到的最大值

下面来分类讨论一下每种情况。

- 如果线段覆盖的这个区间与当前区间并不相交，则直接返回
- 如果线段覆盖了这个区间的一部分，则递归对应的左右子区间继续处理
- 如果线段覆盖了整个区间
  - 如果线段在区间两端点处的值都比原来区间大，则用当前线段替换原来的线段并返回
  - 如果线段在区间两端点处的值都比原来区间小，则直接返回
  - 否则，比较当前线段和原来线段在区间中点处的值，如果当前线段值更大，则将原来线段和当前线段交换；然后判断左右端点的值，如果当前线段在一边不占优势，则递归对应左右子区间

修改时要先找到修改分配到 $\log n$ 个线段树上的区间，这些区间需要 $O(\log n)$ 的时间复杂度下传，所以单次修改的时间复杂度为 $O(\log^2 n)$ 。同样地，查询也是 $O(\log^2 n)$ 。

### 例题
[P4097 【模板】李超线段树 / \[HEOI2013\] Segment](https://www.luogu.com.cn/problem/P4097)

模板题，按上面说的做即可。时间复杂度为 $O(n\log^2 n)$ 。

## code
```cpp
#include<bits/stdc++.h>
using namespace std;
const double eps=1e-8;
const long long mod1=39989,mod2=1000000001;
int n,s1,cnt=0,rt,ans=0;
struct node{
	double k,b;
}s[100005];
struct tree{
	int lc,rc,c;
}tr[500005];
bool pd(int od,int wd,int x){
	double y1=s[od].k*x+s[od].b;
	double y2=s[wd].k*x+s[wd].b;
	if(abs(y1-y2)<eps) return od>wd;
	return y1<y2;
}
void insert(int &k,int l,int r,int x,int y,int c){
	if(!k) k=++cnt;
	if(l>=x&&r<=y){
		if(pd(tr[k].c,c,l)&&pd(tr[k].c,c,r)){
			tr[k].c=c;return;
		}
		if(pd(c,tr[k].c,l)&&pd(c,tr[k].c,r)) return;
		int mid=l+r>>1;
		if(pd(tr[k].c,c,mid)) swap(tr[k].c,c);
		if(pd(tr[k].c,c,l)) insert(tr[k].lc,l,mid,x,y,c);
		else insert(tr[k].rc,mid+1,r,x,y,c);
		return;
	}
	if(l>y||r<x) return;
	if(l==r) return;
	int mid=l+r>>1;
	if(x<=mid) insert(tr[k].lc,l,mid,x,y,c);
	if(y>mid) insert(tr[k].rc,mid+1,r,x,y,c);
}
int find(int k,int l,int r,int x){
	if(l==r&&l==x) return tr[k].c;
	int mid=l+r>>1,re=0;
	if(x<=mid) re=find(tr[k].lc,l,mid,x);
	else re=find(tr[k].rc,mid+1,r,x);
	if(pd(re,tr[k].c,x)) re=tr[k].c;
	return re;
}
int main()
{
	scanf("%d",&n);
	for(int i=1,op,v1,v2,w1,w2;i<=n;i++){
		scanf("%d",&op);
		if(op==1){
			scanf("%d%d%d%d",&v1,&w1,&v2,&w2);
			v1=(v1+ans-1)%mod1+1;
			v2=(v2+ans-1)%mod1+1;
			w1=(w1+ans-1)%mod2+1;
			w2=(w2+ans-1)%mod2+1;
			if(v1>v2){
				swap(v1,v2);swap(w1,w2);
			}
			if(v1==v2){
				s[++s1]=(node){0,max(w1,w2)};
			}
			else{
				double k=(w2-w1)*1.0/(v2-v1);
				s[++s1]=(node){k,w1-v1*k};
			}
			
			insert(rt,1,40000,v1,v2,s1);
		}
		else{
			scanf("%d",&v1);
			v1=(v1+ans-1)%mod1+1;
			ans=find(rt,1,40000,v1);
			printf("%d\n",ans);
		}
	}
	return 0;
}
```


## 维护直线
与维护线段的方法类似，还要简单一些。不用考虑线段没有覆盖整个区间的情况，再按维护线段的方法实现即可。

修改时直线只分配到 $1$ 个线段树上的区间（就是整个线段树维护的区间），这个区间需要 $O(\log n)$ 的时间复杂度下传，所以单次修改的时间复杂度为 $O(\log n)$ 。同样地，查询也是 $O(\log n)$ 。

### 例题
[P4254 \[JSOI2008\] Blue Mary 开公司](https://www.luogu.com.cn/problem/P4254)

也是一道模板题，在维护线段的代码的基础上删掉线段没有覆盖整个区间的情况即可。时间复杂度为 $O(n\log n)$ 。

## code
```cpp
#include<bits/stdc++.h>
using namespace std;
const double eps=1e-8;
int n,s1,cnt=0,rt,ans;
char ch[15];
struct node{
	double k,b;
}s[100005];
struct tree{
	int lc,rc,c;
}tr[500005];
bool pd(int od,int wd,int x){
	double w1=s[od].k+x*s[od].b;
	double w2=s[wd].k+x*s[wd].b;
	if(abs(w1-w2)<eps) return od>wd;
	return w1<w2;
}
void insert(int &k,int l,int r,int c){
	if(!k) k=++cnt;
	if(pd(tr[k].c,c,l)&&pd(tr[k].c,c,r)){
		swap(tr[k].c,c);return;
	}
	if(pd(c,tr[k].c,l)&&pd(c,tr[k].c,r)) return;
	int mid=l+r>>1;
	if(pd(tr[k].c,c,mid)) swap(tr[k].c,c);
	if(pd(tr[k].c,c,l)) insert(tr[k].lc,l,mid,c);
	else insert(tr[k].rc,mid+1,r,c);
}
int find(int k,int l,int r,int x){
	if(l==r&&l==x) return tr[k].c;
	int mid=l+r>>1,re=0;
	if(x<=mid) re=find(tr[k].lc,l,mid,x);
	else re=find(tr[k].rc,mid+1,r,x);
	if(pd(re,tr[k].c,x)) re=tr[k].c;
	return re;
}
int main()
{
	scanf("%d",&n);
	s[0]=(node){0,-1e9};
	for(int i=1,x;i<=n;i++){
		scanf("%s",ch);
		if(ch[0]=='P'){
			double k,b;
			scanf("%lf%lf",&k,&b);
			s[++s1]=(node){k-b,b};
			insert(rt,1,50000,s1);
		}
		else{
			scanf("%d",&x);
			ans=find(rt,1,50000,x);
			ans=s[ans].k+x*s[ans].b;
			if(ans<0) ans=0;
			printf("%d\n",ans/100);
		}
	}
	return 0;
}
```

---

## 作者：licn (赞：3)

[题目链接](https://www.luogu.com.cn/problem/P4097)

本题是板题我们讲一下**李超线段树**。

李超线段树是通过斜率和某一点的位置关系，从而判断两条线的关系。主要是通过将其转化为平面直角坐标系上，维护区间中最高的点。

## **如何通过斜率和在某一点的位置关系？**

![](https://cdn.luogu.com.cn/upload/image_hosting/tah6ekbv.png)

我们发现两条线在横坐标为 $3$ 的点相交，在横坐标小于 $3$ 时，$CD$在 $AB$ 上面，而横坐标大 $3$ 时，$AB$在 $CD$ 上面。我们需要通过用 $mid$ 来判断关系。如上图，$mid=4$，我们发现 $AB$ 在 $CD$ 上且 $AB$ 的斜率大于 $CD$ 的斜率，那么 $mid$ 右边的 $AB$ 一定大于 $CD$，而 $mid$ 左边不确定就继续去判断，直到 $mid$ 等于交点时停止。

### **分类：**
两条线段分别为 $a$，$b$。（$slope$ 为斜率）

当 $slope(a)$ 大于 $slope(b)$ 且 $a$ 与 $mid$ 交点的纵坐标大于 $b$ 与 $mid$ 交点的纵坐标，则 $mid$ 右边 $a$ 上点的纵坐标都是大于 $b$ 上点的纵坐标，$mid$ 左边不确定。

当 $slope(a)$ 大于 $slope(b)$ 且 $a$ 与 $mid$ 交点的纵坐标小于 $b$ 与 $mid$ 交点的纵坐标，则 $mid$ 左边 $b$ 上点的纵坐标都是大于 $a$ 上点的纵坐标，$mid$ 右边不确定。

当 $slope(a)$ 小于 $slope(b)$ 且 $a$ 与 $mid$ 交点的纵坐标小于 $b$ 与 $mid$ 交点的纵坐标，则 $mid$ 右边 $b$ 上点的纵坐标都是大于 $a$ 上点的纵坐标，$mid$ 左边不确定。

当 $slope(a)$ 小于 $slope(b)$ 且 $a$ 与 $mid$ 交点的纵坐标大于 $b$ 与 $mid$ 交点的纵坐标，则 $mid$ 左边 $a$ 上点的纵坐标都是大于 $b$ 上点的纵坐标，$mid$ 右边不确定。

注意：本题是区间修改，单点查询。但是区间修改不需要下传懒惰标记，但是在查询时，我们取出它自己和它儿子中最大的。

## **code**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e5+10,Mx=39989,My=1e9;
const double eps=1e-8;
int n,last,tot;
struct node
{
	double slope,z;
}a[N];
struct node2
{
	int l,r,num;
}t[N<<3];
double point(int x,int p)
{
	return (double)x*a[p].slope+a[p].z;
}
bool judge(int p,int q,int x)
{
	double f1=point(x,p),f2=point(x,q);
	return fabs(f1-f2)<=eps?p>q:f1<f2;
}
void build(int p,int l,int r)
{
	t[p].l=l,t[p].r=r;
	if(l==r)return;
	int mid=l+r>>1;
	build(p<<1,l,mid);
	build(p<<1|1,mid+1,r);
}
void modify(int p,int l,int r,int x)
{
	int mid=t[p].l+t[p].r>>1;
	if(l<=t[p].l&&t[p].r<=r)
	{
		if(judge(t[p].num,x,mid))swap(x,t[p].num);
		if(judge(x,t[p].num,t[p].l)&&judge(x,t[p].num,t[p].r))return;
		if(judge(t[p].num,x,t[p].l))modify(p<<1,l,r,x);
		if(judge(t[p].num,x,t[p].r))modify(p<<1|1,l,r,x);
		return;
	}
	if(l<=mid)modify(p<<1,l,r,x);
	if(r>mid)modify(p<<1|1,l,r,x);
}
int query(int p,int x)
{
	if(t[p].l==t[p].r)return t[p].num;
	int ret=0;
	int mid=t[p].l+t[p].r>>1;
	if(x<=mid)ret=query(p<<1,x);
	else ret=query(p<<1|1,x);
	if(judge(ret,t[p].num,x))ret=t[p].num;
	return ret;
}
signed main(){
	cin>>n;
	build(1,1,Mx);
	for(int i=1;i<=n;i++)
	{
		int op;
		cin>>op;
		if(op==0)
		{
			int k;
			cin>>k;
			int x=(k+last-1+Mx)%Mx+1;
			last=query(1,x);
			cout<<last<<endl;
		}
		else
		{
			int x0,y0,x1,y1;
			cin>>x0>>y0>>x1>>y1;
			x0=(x0+last-1+Mx)%Mx+1,x1=(x1+last-1+Mx)%Mx+1;
			y0=(y0+last-1+My)%My+1,y1=(y1+last-1+My)%My+1;
			tot++;
			if(x0>x1)swap(x0,x1),swap(y0,y1);
			if(x1==x0)a[tot].slope=0,a[tot].z=max(y0,y1);
			else a[tot].slope=(double)(y1-y0)/(double)(x1-x0),a[tot].z=(double)y1-(double)x1*a[tot].slope;	
			modify(1,x0,x1,tot);
		}
	}
	return 0;
}

---

## 作者：gyyyyx (赞：3)

[题面](https://www.luogu.com.cn/problem/P4097)

再次推销自己的[博客](https://www.luogu.com.cn/blog/s19418/li-chao-xian-duan-shu-xue-xi-bi-ji)。

这题和[P4254 [JSOI2008]Blue Mary开公司 ](https://www.luogu.com.cn/problem/P4254)很像，只不过维护的不是直线，而是线段。

其实没什么区别，按照普通线段树的思路，把线段拆分成不超过 $\log n$ 个区间，这样每个区间都被线段完全包含。

往这些完全被包含的区间中插入线段等同于插入直线。

时间复杂度多了一个 $\log$，总时间为 $O(n\log^2m)$。

代码有很多细节要调，下面说几点注意事项：

1. 注意精度，斜率为小数，注意不能直接比较是否相等，会被 Hack 掉。

2. 注意 $x0=x1$ 的问题，题目里也说了，特判否则计算斜率会 RE。

3. 注意更新最优线段时要加上判断编号大小。

代码：

```cpp
#include<bits/stdc++.h>
#define N 40005
#define eps 1e-8
using namespace std;
#define CALC(a,b,c) (a=(a+b-1)%c+1)
int n,lastans,cnt,Best[N<<2];
vector <double> K(1,0),B(1,0);
inline double GetY(int id,int x){
	return x*K[id]+B[id];
}
inline bool Cmp(int id1,int id2,int x){
	double a(GetY(id1,x)),b(GetY(id2,x));
	return abs(a-b)>eps?a>b:id1<id2;
}
#define ls (k<<1)
#define rs (k<<1|1)
#define mid (l+r>>1)
inline void Insert(int k,int l,int r,int s,int t,int id){
	if(l>t||r<s) return;
	if(s<=l&&r<=t){
		if(!Best[k]) return void(Best[k]=id);
		if(Cmp(id,Best[k],mid)) swap(id,Best[k]);
		if(l==r||abs(K[id]-K[Best[k]])<eps) return;
		if(Cmp(id,Best[k],l)) Insert(ls,l,mid,s,t,id);
		if(Cmp(id,Best[k],r)) Insert(rs,mid+1,r,s,t,id);
		return;
	}
	Insert(ls,l,mid,s,t,id);
	Insert(rs,mid+1,r,s,t,id);
}
inline int Query(int k,int l,int r,int x){
	if(l==r) return Best[k];
	int res(x<=mid?Query(ls,l,mid,x):Query(rs,mid+1,r,x));
	return Cmp(res,Best[k],x)?res:Best[k];
}
int main(){
	scanf("%d",&n);
	while(n--){
		int op;scanf("%d",&op);
		if(op){
			int a,b,c,d;scanf("%d%d%d%d",&a,&b,&c,&d);
			CALC(a,lastans,39989);CALC(b,lastans,1000000000);
			CALC(c,lastans,39989);CALC(d,lastans,1000000000);
			if(a>c) swap(a,c),swap(b,d);++cnt;
			if(a==c) K.push_back(0),B.push_back(max(b,d));
			else K.push_back(double(b-d)/(a-c)),B.push_back(b-a*K[cnt]);
			Insert(1,0,N,a,c,cnt);
		}
		else{
			int x;scanf("%d",&x);CALC(x,lastans,39989);
			printf("%d\n",(lastans=Query(1,0,N,x)));
		}
	}
	return 0;
}
```

---

## 作者：Erica_N_Contina (赞：2)

## 思路

先看看题目，我们要维护的是什么？是对于每个 $x$，其上方最高的线段是那一条。我们想到，当我们往图中加入一条新的线段时，假如这条线段在某个区间是最高的，那么我们就需要把这个区间的答案都修改为这个线段。所以很明显我们可以考虑用类似线段树的数据结构来维护。

但是首先要明确一点，每次加入一条线段可能要修改多个区间，也有可能一个区间都不修改。

![image.png](https://img1.imgtp.com/2023/08/31/zIqxDRY9.png)

![image.png](https://img1.imgtp.com/2023/08/31/1StgkIdf.png)

我们从线段树的模板上来修改。

## 修改

首先是修改函数。这里我们要实现的功能是添加一条线段，然后修改对应的值。

```C++
void change(int x,int l,int r,int ql,int qr,int v){
	if(l>=ql&&r<=qr){
		pushup(x,l,r,v);return ;
	}
	int mid=(l+r)>>1;
	if(ql<=mid)change(x<<1,l,mid,ql,qr,v);
	if(qr>mid)change(x<<1|1,mid+1,r,ql,qr,v);
}
```


这里的代码还是比较简洁的。注意这里应该是拿区间修改的线段树模板来修改（注意最后两行）而不是单点修改的。

解释一下这里的 $v$，这里的 $v$ 是插入的线段是编号。我们开一个结构体 `line{k,b}` 来记录每一条线段的 $k,b$，然后我们使用数组 `lne[]` 来记录所有线段。

当我们访问到一个区间在要修改的区间 $[  ql,qr]$ 之内时，我们就需要修改这个区间内的信息了。我们使用  `pushup()` 函数来修改（实际上叫做 `update` 更好，但由于是线段树改的，我们姑且叫他 `pushup`）。

```C++
void pushup(int x,int l,int r,int u){//ok
	int &v=s[x];
	int mid=(l+r)>>1,bmid=cmp(cal(u,mid),cal(v,mid));
	if(bmid==1||(!bmid&&u<v))swap(u,v);
	
	int bl=cmp(cal(u,l),cal(v,l));
	int br=cmp(cal(u,r),cal(v,r));
	
	if(bl==1||(!bl&&u<v))pushup(x<<1,l,mid,u);
	if(br==1||(!br&&u<v))pushup(x<<1|1,mid+1,r,u);	
}
```


这里的 `s[]` 数组就相当于线段树中的每个节点，在我的线段树板子里就是 `tr[]` 数组。我们这颗线段树记录的是“区间最高的线段的编号”，所以 $s$ 中记录的信息是线段的编号。那么这里的 $x$ 就是线段树上的节点的编号，`s[x]` 就是原来这个节点上记录的线段的编号。我们要比较这个就线段 $v$ 和我们新加入的线段 $u$ 的高度关系，并且考虑更新 `s[x]`。

这里我们需要两个辅助函数。

```C++
int cmp(double x, double y) {
  if (x-y>eps) return 1;
  if (y-x>eps) return -1;
  return 0;
}

db cal(int id,int p){//
	return 1.00*lne[id].b+p*lne[id].k;//计算直线id在x=p处的y
}

```


第一个是比较大小的。这个不用说了，因为小数运算会出现精度问题。

第二个我来解释一下，其实也没什么，就是我们传入线段的编号和当前的 $x$，计算这条线段在 $x=p$ 时的 $y$ 值（即高度值）。

我们再回到 `pushup` 函数 。

![image.png](https://img1.imgtp.com/2023/08/31/m7UCSjgY.png)

第一步，我们先计算当 $x=mid$ 时两个线段的高度关系。假设线段 $u$（记住在该例子里 $u$ 是新加入的线段）在 $x =mid$ 时的高度大于 $v$ 的，那么我们就把 $u,v$ 交换一下，有利于减少讨论情况。注意这里不仅仅是简单交换值，而是把映射关系也交换了。

![image.png](https://img1.imgtp.com/2023/08/31/h6OlHxio.png)

在交换之后，我们就默认 $u$ 在 $x=mid$ 处比 $v$ 低了。那么这时我们来分类讨论一下。我们记录 $4$ 个端点的高度值 $ul,ur,vl,vr$。

![image.png](https://img1.imgtp.com/2023/08/31/yCx40Z8h.png)

- 当 $vl≥ul$ 且 $vr≥ur$ 时，在 $[l,r]$ 中 $u$ 肯定不如 $v$。相反也如此。

- 当 $vl>ul$ 但是 $vr<ur$ 时，那么说明线段 $u,v$ 在 $[mid,r]$ 区间内肯定有交点。这时区间 $[l,mid]$ 的答案应该不变（但由于我们不知道 $u,v$ 有没有交换过，所以我们还是修改一下。修改也很简单，对应区间修改的线段树，我们把 $[l,mid]$ 打上 tag），区间 $[mid,r]$ 我们应该递归下去。（如上图）


![image.png](https://img1.imgtp.com/2023/08/31/Qj53aKYh.png)

- 当 $ul>vl$ 但是 $vr>ur$ 时，那么说明线段 $u,v$ 在 $[l,mid]$ 区间内肯定有交点。这时区间 $[mid,r]$ 的答案应该不变（但由于我们不知道 $u,v$ 有没有交换过，所以我们还是修改一下。修改也很简单，对应区间修改的线段树，我们把 $[mid,r]$ 打上 tag），区间 $[l,mid]$ 我们应该递归下去。（如上图）

注意在讨论时我们要注意到在 $x=mid$ 处 $v$ 比 $u$ 高这个大前提哈。

还有两种特殊情况，即有一个端点重合。那么我们就需要知道 $u,v$ 有没有交换过了。我们考察下面的代码。

```C++
	if(bl==1||(!bl&&u<v))pushup(x<<1,l,mid,u);
```


我们把 `!bl&&u<v` 这种情况和 `bl==1`（即 $ul>vl$）的情况放在一起，因为我们知道新加入的线段的编号一定是大于之前的线段的编号的，所以如果 $u<v$，那么就说明 $v$ 是新线段。如下。所以我们应该往左边的区间递归。

![image.png](https://img1.imgtp.com/2023/08/31/qAiQIM9L.png)

另外一种情况类似，请大家自己想一想吧！

那么现在 $6$ 种情况我们都讨论过了，请仔细理解鸭。

## 查询

现在我们来看查询的部分。

```C++
pr query(int x,int l,int r,int q){
	if(q<l||q>r){
		return {0,0};
	}
	db res=cal(s[x],q);
	if(l==r)return {res,s[x]};
	int mid=(l+r)>>1;
	
	return pmax({res,s[x]},pmax(query(x<<1|1,mid+1,r,q),query(x<<1,l,mid,q)));
}
```


可以发现，这里和普通的线段树还是有一点区别的。这里的返回值是一个 `pair<double,int>` 分别是在 $x=q$ 时的最高的线段的高度和线段的编号。

首先对于无解的情况，即询问的 $x$ 在范围之外，我们直接返回最小值 $-inf$ 或者 $0$（因为本题求最大值）即可，同时返回 $id=0$ 表示不存在这条线段。

然后我们就需要计算当前这个节点对应的线段在 $x=q$ 时的高度了，我们记为 $res$。假如 $l=r$，那么说明我们已经找到了叶子节点，直接返回 $res$ 即可。但是如果这个点不是叶子节点，我们为什么还需要考虑当前节点的线段呢？直接递归下去不就行了？

注意！这里我们可没有 `pushdown` 操作！所以也许当前节点存储了新加入的高度更高的线段，但是叶子节点并没有更新！所以我们还需要采纳非叶子节点但也属于区间内的节点信息。当然，既然这个节点 $[l,r]$ 记录了这个线段，就说明再某个时刻这个区间内的最高点都在这个线段上，也就是说这个线段一定覆盖了这个区间，那么对于 $x=q$ 也一定经过了这条线段。但是至于这条线段是否是最终答案我们暂时还不知道。总而言之，**这条线段一定有成为答案的可能。**

这里我们还需要引入一个辅助函数 `pmax()`。

```C++
pr pmax(pr a,pr b){//
	if(cmp(a.pf,b.pf)==-1)return b;
	if(cmp(a.pf,b.pf)==1)return a;
	if(a.ps<b.ps)return a;
	return b;
}
```


这个函数的功能是传入两个线段 $a,b$（注意这里传入的线段 $a,b$ 为 `pair<double,int>` 类型，即已经计算好了当 $x=q$ 时的高度值了，存放在 `pair` 的 `.first` 中），我们比较两个线段的 `.first`（代码中 `define` 为 `pf`），返回高的那个即可。请注意回顾 `cmp` 函数。

当然，题目要求“若有多条线段与查询直线的交点纵坐标都是最大的，则输出编号最小的线段”，所以就有了最后两行。

## 其他

现在线段树部分已经讲完了，我们最后考察加线段的函数（不是在线段树中，而是把线段加入 `lne[]` 数组中）。

```C++
void add(int x,int y,int a,int b){
	if(x==a){
		lne[++cnt].k=0,lne[cnt].b=max(y,b);
	}else{
		lne[++cnt].k=1.0*(b-y)/(a-x),lne[cnt].b=y-lne[cnt].k*x;
	}
}
```


这里线段的两个端点分别为 $(x,y)(a,b)$，注意 $x=a$ 的特殊情况。其他就是计算斜率和截距的常规操作了，初中知识即可。

## 代码

```C++
/*////////ACACACACACACAC///////////
       . Coding by Ntsc .
       . FancyKnowledge .
       . Prove Yourself .
/*////////ACACACACACACAC///////////

//头文件
#include<bits/stdc++.h>

//数据类型
#define int long long
#define ull unsigned long long
#define db double
#define endl '\n'
#define pr pair<double,int> 
#define pf first
#define ps second
//命名空间
using namespace std;
//常量
const int N=4e5+5;
const int M=1e3;
const int MOD=1e9+1;
const int INF=1e9;
const db eps=1e-9;
//变量
int n,m,a,b,c,s[N],y[N],lans,res,tmp,cnt,web[M][M];

struct line{
	db k,b;
}lne[N];

void add(int x,int y,int a,int b){
	if(x==a){
		lne[++cnt].k=0,lne[cnt].b=max(y,b);//why max?
		
	}else{
		lne[++cnt].k=1.0*(b-y)/(a-x),lne[cnt].b=y-lne[cnt].k*x;
	}
}

int cmp(double x, double y) {
  if (x-y>eps) return 1;
  if (y-x>eps) return -1;
  return 0;
}

db cal(int id,int p){//
	return 1.00*lne[id].b+p*lne[id].k;//计算直线id在x=p处的y
}

pr pmax(pr a,pr b){//
	if(cmp(a.pf,b.pf)==-1)return b;
	if(cmp(a.pf,b.pf)==1)return a;
	if(a.ps<b.ps)return a;
	return b;
	
}

void pushup(int x,int l,int r,int u){//ok
	int &v=s[x];
	int mid=(l+r)>>1,bmid=cmp(cal(u,mid),cal(v,mid));
	if(bmid==1||(!bmid&&u<v))swap(u,v);
	
	int bl=cmp(cal(u,l),cal(v,l));
	int br=cmp(cal(u,r),cal(v,r));
	
	if(bl==1||(!bl&&u<v))pushup(x<<1,l,mid,u);
	if(br==1||(!br&&u<v))pushup(x<<1|1,mid+1,r,u);
	
	
}


void change(int x,int l,int r,int ql,int qr,int v){//ok
	if(l>=ql&&r<=qr){
		pushup(x,l,r,v);return ;
	}
	int mid=(l+r)>>1;
	if(ql<=mid)change(x<<1,l,mid,ql,qr,v);
	if(qr>mid)change(x<<1|1,mid+1,r,ql,qr,v);
}


pr query(int x,int l,int r,int q){//ok
//	cerr<<"query l="<<l<<" r="<<r<<endl;
	if(q<l||q>r){
		return {0,0};
	}
	db res=cal(s[x],q);
	if(l==r)return {res,s[x]};
	int mid=(l+r)>>1;
	
	return pmax({res,s[x]},pmax(query(x<<1|1,mid+1,r,q),query(x<<1,l,mid,q)));
}


void solve(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++){
		int op,x,y,a,b,k;
      	cin>>op;
      	if(op){
      		cin>>x>>y>>a>>b;
      		x=(x+lans-1+39989)%39989+1;
      		y=(y+lans-1+MOD)%MOD+1;//注意加上一个MOD
      		a=(a+lans-1+39989)%39989+1;
      		b=(b+lans-1+MOD)%MOD+1;
      		if(x>a)swap(x,a),swap(y,b);
      		add(x,y,a,b);
      		change(1,1,39989,x,a,cnt);
		}else{
			cin>>k;
			
//			cerr<<"query k="<<(k+lans-1+39989)%39989+1<<endl;
			lans=query(1,1,39989,(k+lans-1+39989)%39989+1).ps;
			cout<<lans<<endl;
		}
	}
}

signed main(){
	int T;
	//	cin>>T;
	T=1;
	while(T--){
		solve();
	}
	
	return 0;
}

```




---

## 作者：Cindy_Li (赞：1)

李超线段树：用于维护平面上的一次函数，支持在线插入 & 求单点最大值（编号）。

-------------------

### 插入

现在要加入一个一次函数 $f(x)=kx+b$，定义域 $[s,t]$。

*注意：当线段垂直于 $x$ 轴时，应插入定义域为 $[x,x]$ 的一次函数 $f(x)=0\cdot x+y_1$。*

考虑某个被 $f$ 完全覆盖的节点 $x$，区间 $[l,r]$。

标记 $tg_x$ 代表可更新本区间**超过一半**的线段编号。

1. 如果该区间还没有标记，直接标记为 $f$ 即可。
2. 如果已经有标记了，根据定义，需要分类下传标记。

![](https://oi-wiki.org/ds/images/li-chao-tree-1.png)

如图，按 $f$ 取值是否大于 $tg_x$，可以分出两个子区间。
- 一定有一个子区间**超过一半**，将 $tg_x$ 更新为这个子区间对应的较大值。
- 对于另一个**被左/右区间完全包含**的子区间，可以直接递归下传标记。

显然这样做是不会漏掉任何线段的。

具体实现考虑 $l,mid,r$ 三个点处的取值，分类讨论。

实现：
```c++
const double eps=1e-9;
inline int cmp(double x,double y){
    if(x-y>eps) return 1;
    if(y-x>eps) return -1;
    return 0;
}

//...

void updtg(int x,int l,int r,int id){
    if(!tg[x]) return tg[x]=id,void();
    int mid=(l+r)>>1;
    int fmid=cmp(calc(mid,id),calc(mid,tg[x]));
    if(fmid==1 || (!fmid && id<tg[x])) swap(id,tg[x]);
    int fl=cmp(calc(l,id),calc(l,tg[x])),fr=cmp(calc(r,id),calc(r,tg[x]));
    if(fl==1 || (!fl && id<tg[x])) updtg(ls[x],l,mid,id);
    if(fr==1 || (!fr && id<tg[x])) updtg(rs[x],mid+1,r,id);
}
void ins(int x,int l,int r,int s,int t,int id){
    if(l>=s && r<=t) return updtg(x,l,r,id);
    int mid=(l+r)>>1;
    if(s<=mid) ins(ls[x],l,mid,s,t,id);
    if(t>mid) ins(rs[x],mid+1,r,s,t,id);
}
```

### 查询

显然，根据标记的定义，所有包含 $p$ 的线段树节点中，一定有一个的 $tg_x$ 是在 $p$ 处取值最大的线段。

故可以直接递归比较得出答案。

实现：
```c++
Pdi que(int x,int l,int r,int p){
    Pdi res=(Pdi){calc(p,tg[x]),tg[x]};
    if(l==r) return res;
    int mid=(l+r)>>1;
    if(p<=mid) return pmax(res,que(ls[x],l,mid,p));
    return pmax(res,que(rs[x],mid+1,r,p));
}
```

-----------------

### 时间复杂度

查询显然是 $O(\log n)$ 的。

插入时，原线段拆分成 $O(\log n)$ 个区间，每个区间需要 $O(\log n)$ 时间递归下传，总复杂度 $O(\log^2 n)$。

---------

完整代码；

```c++
#include<bits/stdc++.h>
using namespace std;
#define rep(i,x,y) for(int i=x;i<=y;i++)
#define per(i,x,y) for(int i=x;i>=y;i--)
#define REPG(i,g,x) for(int i=g.head[x];~i;i=g.edge[i].nxt)
#define LL long long
#define y1 yyyyyy

template<class T>
inline void read(T &x){
    T s=0,f=1;char c=getchar();
    for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
    for(;isdigit(c);c=getchar()) s=s*10+c-'0';
    x=s*f;
}

const int N=1e5+5;
const double eps=1e-9;
inline int cmp(double a,double b){
    if(a-b>eps) return 1;
    if(b-a>eps) return -1;
    return 0;
}
struct line{
    double k;
    double b;
    int l,r;
    inline void init(int x0,int y0,int x1,int y1){
        if(x0==x1) k=0,b=max(y0,y1);
        else k=1.0*(y1-y0)/(x1-x0),b=y0-x0*k;
        l=min(x0,x1),r=max(x0,x1);
    }
}ln[N];
int cnt;
inline double calc(int id,int x){
    if(id==0) return 0;
    return ln[id].k*x+ln[id].b;
}
struct Pdi{
    double first;
    int second;
};
Pdi pmax(Pdi a,Pdi b){
    if(cmp(a.first,b.first)!=0) 
        return (cmp(a.first,b.first)==1?a:b);
    return (a.second<b.second?a:b);
}

namespace ST{
    int tot;
    int ls[N],rs[N];
    int tg[N];//mid max

    int build(int l,int r){
        int x=++tot;
        if(l==r) return x;
        int mid=(l+r)>>1;
        ls[x]=build(l,mid);
        rs[x]=build(mid+1,r);
        return x;
    }

    void updtg(int x,int l,int r,int id){
        int mid=(l+r)>>1;
        int fmid=cmp(calc(id,mid),calc(tg[x],mid));//if id better?
        if(fmid==1 || (!fmid && id<tg[x])) swap(id,tg[x]);
        int fl=cmp(calc(id,l),calc(tg[x],l)),fr=cmp(calc(id,r),calc(tg[x],r));
        if(fl==1 || (!fl && id<tg[x])) updtg(ls[x],l,mid,id);
        if(fr==1 || (!fr && id<tg[x])) updtg(rs[x],mid+1,r,id);
    }
    void upd(int x,int l,int r,int s,int t,int id){
        if(l>=s && r<=t) return updtg(x,l,r,id);
        int mid=(l+r)>>1;
        if(s<=mid) upd(ls[x],l,mid,s,t,id);
        if(t>mid) upd(rs[x],mid+1,r,s,t,id);
    }

    inline Pdi que(int x,int l,int r,int p){
        if(r<p || p<l) return (Pdi){0,0};
        int mid=(l+r)>>1;
        double res=calc(tg[x],p);
        if(l==r) return (Pdi){res,tg[x]};
        return pmax((Pdi){res,tg[x]},pmax(que(ls[x],l,mid,p),que(rs[x],mid+1,r,p)));
    }
}
int n;
const int mod1=39989;
const int mod2=1e9+1;
int lstans;
int r1(int x){
    return (x+lstans-1+mod1)%mod1+1;
}
int r2(int y){
    return (y+lstans-1+mod2)%mod2+1;
}

int main(){
    ST::build(1,mod1+1);
    read(n);
    while(n--){
        int op;
        read(op);
        if(op==0){
            int k;read(k);
            int res=ST::que(1,1,mod1+1,r1(k)).second;
            printf("%d\n",res);
            lstans=res;
        }
        else{
            int x0,y0,x1,y1;
            read(x0),read(y0),read(x1),read(y1);
            ln[++cnt].init(r1(x0),r2(y0),r1(x1),r2(y1));
            ST::upd(1,1,mod1+1,ln[cnt].l,ln[cnt].r,cnt);
        }
    }
    return 0;
}
```

---

