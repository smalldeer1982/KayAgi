# Three Arrays

## 题目描述

There are three arrays $ a $ , $ b $ and $ c $ . Each of them consists of $ n $ integers. SmallY wants to find three integers $ u $ , $ v $ , $ w $ $ (0<=u,v,w<=n) $ such that the following condition holds: each number that appears in the union of $ a $ , $ b $ and $ c $ , appears either in the first $ u $ elements of $ a $ , or in the first $ v $ elements of $ b $ , or in the first $ w $ elements of $ c $ . Of course, SmallY doesn't want to have huge numbers $ u $ , $ v $ and $ w $ , so she wants sum $ u+v+w $ to be as small as possible.

Please, help her to find the minimal possible sum of $ u+v+w $ .

## 说明/提示

In the first example you should choose $ u=3,v=0,w=2 $ .

In the second example you should choose $ u=1,v=3,w=1 $ .

## 样例 #1

### 输入

```
3
1 1 101
1 2 1
3 2 1
```

### 输出

```
5```

## 样例 #2

### 输入

```
5
1 1 2 2 3
2 2 4 3 3
3 3 1 1 1
```

### 输出

```
5```

# 题解

## 作者：米奇 (赞：3)

## 题解

首先肯定是要枚举一个的，我枚举的是$u$（$A$中的位置）。

但我们不能从小到大枚举，要从大到小枚举。

为什么呢？从大到小枚举的话，相当于是每次会多一些限制，这样比较好维护（如果是撤销限制，那不是很麻烦吗）。

考虑会多什么限制呢？

就是那个数原来是在$A$中被消灭的，现在不能在$A$中被消灭了，那么就得在$B$或$C$中被消灭。

那到底是在$B$中还是$C$中呢？

这就到了本题的关键地方了，我们把在$B$中消灭的位置看成横坐标，在$C$中消灭的位置看成纵坐标。这样的话，在二维平面中就有了一些点，我们要选一个横坐标$X$和一个纵坐标$Y$，使得所有点要么横坐标$<=X$，要么纵坐标$<=Y$。我们要求最小的$X+Y$。

怎么维护二维平面上的点呢，我们用线段树下标代替横坐标，用线段树维护纵坐标。

具体怎么维护，比如一个点$(x,y)$，那么相当于横坐标$<x$的纵坐标都必须$>=y$，相当于$[0,x-1]$的位置上区间覆盖最大值$y$。

由于是$X+Y$，所以我们相当于在线段树下标为$i$的地方都应该加上$i$。

这就让我们不能用普通办法区间覆盖了。因为有些位置上最大值是大于要覆盖的数的，但你不知道，你会以为那个位置小，就用那个位置+覆盖的数来修改答案。

这时候，你发现随着横坐标的增大，纵坐标是单调不增的。那么我们找到第一个覆盖的值$<y$的位置（$y$是当前要覆盖的值），然后就可以区间覆盖了，因为这时横坐标上覆盖的值都$<y$了，那么你用最小的位置+覆盖的数来修改答案就是对的。

如何找到第一个覆盖的值$<y$的位置呢？

线段树上二分即可。

**细节：**

可能有些是只在$B$或$C$中出现，那么相当于$X,Y$都有一个下界，$X$没关系（线段树区间查询），$Y$的话我们就区间覆盖啊，做法同上。



## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define next Next
#define last Last
const int N=1e6+5;
int n,RR,gs,ans=1e9,Xma,Yma,ma[N],a[N],b[N],c[N],d[N],La[N],Lb[N],Lc[N],lst[N],tree[N*4],mi[N*4],lazy[N*4];
char buf[1<<21],*p1=buf,*p2=buf;
inline int gc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++;}
inline int read()
{
	int ret=0,f=0;char c=gc();
	while(!isdigit(c)){if(c=='-')f=1;c=gc();}
	while(isdigit(c)){ret=ret*10+c-48;c=gc();}
	if(f)return -ret;return ret;
}
void build(int nod,int l,int r)
{
	if(l==r)
	{
		tree[nod]=mi[nod]=l;
		return;
	}
	int mid=(l+r)/2;
	build(nod*2,l,mid);
	build(nod*2+1,mid+1,r);
	tree[nod]=min(tree[nod*2],tree[nod*2+1]);
	mi[nod]=min(mi[nod*2],mi[nod*2+1]);
}
void pushdown(int nod)
{
	if(!lazy[nod])return;
	mi[nod*2]=max(mi[nod*2],tree[nod*2]+lazy[nod]);
	mi[nod*2+1]=max(mi[nod*2+1],tree[nod*2+1]+lazy[nod]);
	lazy[nod*2]=max(lazy[nod*2],lazy[nod]);
	lazy[nod*2+1]=max(lazy[nod*2+1],lazy[nod]);
	ma[nod*2]=max(ma[nod*2],lazy[nod]);
	ma[nod*2+1]=max(ma[nod*2+1],lazy[nod]);
	lazy[nod]=0;
}
void change(int nod,int l,int r,int L,int R,int val)
{
	if(l==L&&r==R)
	{
		ma[nod]=max(ma[nod],val);
		mi[nod]=max(mi[nod],tree[nod]+val);
		lazy[nod]=max(lazy[nod],val);
		return;
	}
	pushdown(nod);
	int mid=(l+r)/2;
	if(R<=mid)change(nod*2,l,mid,L,R,val);
	else if(L>mid)change(nod*2+1,mid+1,r,L,R,val);
	else{
		change(nod*2,l,mid,L,mid,val);
		change(nod*2+1,mid+1,r,mid+1,R,val);
	}
	mi[nod]=min(mi[nod*2],mi[nod*2+1]);
	ma[nod]=min(ma[nod*2],ma[nod*2+1]);
}
int find(int nod,int l,int r,int L,int R)
{
	if(l==L&&r==R)return mi[nod];
	pushdown(nod);
	int mid=(l+r)/2;
	if(R<=mid)return find(nod*2,l,mid,L,R);
	else if(L>mid)return find(nod*2+1,mid+1,r,L,R);
	else return min(find(nod*2,l,mid,L,mid),find(nod*2+1,mid+1,r,mid+1,R));
}
int query(int nod,int l,int r,int val)
{
	if(l==r)
	{
		if(ma[nod]>=val)return l+1;
		else return l;
	}
	pushdown(nod);
	int mid=(l+r)/2;
	if(ma[nod*2]>=val)return query(nod*2+1,mid+1,r,val);
	else return query(nod*2,l,mid,val);
}
signed main()
{
	n=read();
	for(int i=1;i<=n;i++)
	{
		a[i]=read();
		d[++gs]=a[i];
	}
	for(int i=1;i<=n;i++)
	{
		b[i]=read();
		d[++gs]=b[i];
	}
	for(int i=1;i<=n;i++)
	{
		c[i]=read();
		d[++gs]=c[i];
	}
	sort(d+1,d+gs+1);
	gs=unique(d+1,d+gs+1)-d-1;
	for(int i=1;i<=n;i++)a[i]=lower_bound(d+1,d+gs+1,a[i])-d;
	for(int i=1;i<=n;i++)b[i]=lower_bound(d+1,d+gs+1,b[i])-d;
	for(int i=1;i<=n;i++)c[i]=lower_bound(d+1,d+gs+1,c[i])-d;
	for(int i=1;i<=gs;i++)lst[i]=0;
	for(int i=1;i<=n;i++)
	{
		if(lst[a[i]])continue;
		lst[a[i]]=1;
		La[a[i]]=i;
	}
	for(int i=1;i<=gs;i++)lst[i]=0;
	for(int i=1;i<=n;i++)
	{
		if(lst[b[i]])continue;
		lst[b[i]]=1;
		Lb[b[i]]=i;
	}
	for(int i=1;i<=gs;i++)lst[i]=0;
	for(int i=1;i<=n;i++)
	{
		if(lst[c[i]])continue;
		lst[c[i]]=1;
		Lc[c[i]]=i;
	}
	build(1,0,n);
	for(int i=1;i<=n;i++)
		if((!La[b[i]])&&(Lb[b[i]]==i))
		{
			if(!Lc[b[i]])Xma=max(Xma,i);
		}
	for(int i=1;i<=n;i++)
		if((!La[c[i]])&&(Lc[c[i]]==i))
		{
			if(!Lb[c[i]])Yma=max(Yma,i);
		}
	for(int i=1;i<=n;i++)
		if((!La[b[i]])&&(Lb[b[i]]==i))
		{
			if(Lc[b[i]])
			{
				int x=query(1,0,n,Lc[b[i]]);
				if(x<=i-1)change(1,0,n,x,i-1,Lc[b[i]]);
			}
		}
	int x=query(1,0,n,Yma);
	if(x<=n)change(1,0,n,x,n,Yma);
	ans=min(ans,n+max(Xma+Yma,find(1,0,n,Xma,n)));
	for(int i=n;i;i--)
	{
		if(La[a[i]]==i)
		{
			
			if(!Lb[a[i]])
			{
				if(!Lc[a[i]])break;
				Yma=max(Yma,Lc[a[i]]);
			}
			else if(!Lc[a[i]])Xma=max(Xma,Lb[a[i]]);
			else{
				int x=query(1,0,n,Lc[a[i]]);
				if(x<=Lb[a[i]]-1)change(1,0,n,x,Lb[a[i]]-1,Lc[a[i]]);
			}
		}
		int x=query(1,0,n,Yma);
		if(x<=n)change(1,0,n,x,n,Yma);
		ans=min(ans,i-1+max(Xma+Yma,find(1,0,n,Xma,n)));
	}
	cout<<ans;
}
/*
枚举x
然后就是线段树维护 
*/
```


---

## 作者：HDWR (赞：0)

## CF392D Three Arrays

### 解题报告

首先，我们只能枚举一个数组用多少数，且必须在 $O(\log^2 n),O(\log n)$ 或更短时间内求出另外两个数组的答案。

先对每一个数进行一个转换：设数对 $t_i\rightarrow (x_i, y_i, z_i)$ 的三个参数分别表示 $t_i$ 这个数在 $a_i,b_i,c_i$ 中第一次出现的位置（不存在就是无穷大），那么一个合法的方案 $(u, v, w)$ 即满足 $\forall t_i,a_i \leq u \text{ or } b_i \leq v \text{ or } c_i \leq w$。

既然我们已经枚举了第一维的 $u$，那么通过对数对的第一维进行排序（毕竟我们不关心每个数字的具体大小，我们只关心每个数对有没有满足条件，所以排序完全没有问题），我们可以快速得出哪些数是已经满足条件的，而哪些数没有满足条件。接下来就是对**剩下不满足条件的数对**（以下均称“数对”）进行求解。

---

忽略第一维后，考虑将数对看作二维平面上的点 $(X_i,Y_i)$（字母大写和上面的数对定义做区分），那么问题就转化成了求两条直线 $x = v, y = w$，满足：所有点要么在 $x = v$ 的左边、要么在 $y = w$ 的下面。

也就是把第一象限再划分成四个小块，让每个点都不在右上方的小块（可以在边界上）。

![4cNQXR.png](https://z3.ax1x.com/2021/09/26/4cNQXR.png)

图中的当然不是最优方案。（可能的）最优方案一定要满足，**固定一条线后，另一条线下降到不能再下降**。因为坐标轴可以旋转，所以这里一律固定 $x = v$ 并让 $y = w$ 尽可能下降。也就是这样：

![4cUiCD.png](https://z3.ax1x.com/2021/09/26/4cUiCD.png)

（细心的同学可以发现这张图其实是重画了的，大家尽量理解一下）

通俗地说，选定两个相邻的“最外层”的点（类似于一个凸包），以左边点的横坐标作为 $v$，以右边点的纵坐标作为 $w$，这样选出来的直线 $x = v,y = w$ 才有可能成为一个最优的方案，该方案的答案就是 $v + w$。

下一个方案、再下一个方案是这样的：

[![4cUbZt.png](https://z3.ax1x.com/2021/09/26/4cUbZt.png)](https://imgtu.com/i/4cUbZt)

可以看到，**它是一个“阶梯型”下降的趋势**。这个阶梯图样非常重要，是本题解题关键。

---

刚刚说到了对第一维进行排序，排完序之后不满足的点就可以一个一个加入这个二维平面，寻找一个能让它满足的方案。一个点加入后就不能删除，那么有些点永远也无法落在“阶梯”上，成为“最外层”的点，让我们直接忽略它们！

接下来你有了一堆纵坐标递减的点，选定两个相邻的点构成的直线即是一个“阶梯”，能产生的所有答案就是所有相邻的 $X_i +Y_{i + 1}$，到时候更新答案即是求它的最小值。

考虑加入一个新点会对它们有什么影响。

[![4ca2Os.png](https://z3.ax1x.com/2021/09/26/4ca2Os.png)](https://imgtu.com/i/4ca2Os)

此时加入一个新点：

[![4cdP6H.png](https://z3.ax1x.com/2021/09/26/4cdP6H.png)](https://imgtu.com/i/4cdP6H)

首先，D 和 E 组成的答案无法满足 J 的条件，这个答案应当被删除。

其次，B、C、D 三个点不再是“最外层”的点，应当把它们和它们产生的答案从图中删去。此时我们也可以看出，**一个点是“最外层的点”的充要条件是：不存在横纵坐标都比它大的点。**

在做完上述两个处理之后，我们就可以放心添加 $X_A +Y_J, X_J+Y_E$ 这两个答案了。

**所以，加入一个新点，应当先删除相邻节点不合法的答案，再循环删除所有不在最外层的点，最后再计算它与相邻点产生的答案。**

---

维护这个二维平面的点需要快速插入、查找、删除（按一定顺序的）相邻节点；维护这个二维平面上所有的答案需要快速插入、查找、删除，查询最小值。

这几个操作只需要 `std::set` 和 `std::multiset` 即可完成。

### 代码实现

英文注释是因为 Dev-C++ 和 VSCode 使用不同编码（GB2312 和 UTF8），懒得每次打开都切换了。

```cpp
const int MAXN = 1e5 + 10;

int n; int aa[4][MAXN];

struct ND {
    int val, pos, from;
    bool operator < (const ND &th) const {
        return val < th.val;
    }
    bool operator == (const ND &th) const {
        return val == th.val && pos == th.pos && from == th.from;
    }
} nds[MAXN * 3];

struct POS {
    int from[4];
    POS() { from[0] = from[1] = from[2] = from[3] = 0x3f3f3f3f; }
    bool operator < (const POS &th) const {
		return from[1] > th.from[1];
	}
} whereis[MAXN]; int cnt;

struct Point {
	int x, y;
	bool operator < (const Point &th) const {
		return x == th.x ? y < th.y : x < th.x;
	}
	bool operator == (const Point &th) const {
		return x == th.x && y == th.y;
	}
}; std::set<Point> pts; std::multiset<int> sums;
// pts: store Points on the Ladder

void Insert(POS in) {
	Point now = {in.from[2], in.from[3]};
	pts.insert(now);
	auto it_now = pts.find(now); 
	auto it_next = it_now; ++it_next;
	if (it_next->x >= it_now->x && it_next->y >= it_now->y) {
		pts.erase(now); return; // not on the Ladder
	} auto it_prev = it_now; --it_prev;
	if (sums.find(it_prev->x + it_next->y) != sums.end()) {
		sums.erase(sums.find(it_prev->x + it_next->y));
	} // remove an illegal sol which cannot contain the Point just added
	while (true) {
		// remove all Points which will be contained by the new Ladder
		it_now = pts.find(now);
		it_prev = it_now; --it_prev;
		auto it_cprv = it_prev; --it_cprv;
		if (!(it_prev->x <= it_now->x && it_prev->y <= it_now->y)) break;
		if (sums.find(it_cprv->x + it_prev->y) != sums.end())
			sums.erase(sums.find(it_cprv->x + it_prev->y));
		pts.erase(it_prev);
	} it_now = pts.find(now); // insert the new sol
	it_next = it_now; ++it_next;
	it_prev = it_now; --it_prev;
	sums.insert(it_now->y + it_prev->x);
	sums.insert(it_now->x + it_next->y);
}

void solve() {
	std::sort(whereis + 1, whereis + 1 + cnt);
	pts.insert({0, 0x3f3f3f3f + 2}); pts.insert({0x3f3f3f3f + 2, 0}); // placeholder
	sums.insert(0); // placeholder
	int ans = 0x3f3f3f3f;
	for (int fst = n, now = 1; fst >= 0; --fst) {
		while (now <= cnt && whereis[now].from[1] > fst) { // whereis[] is sorted in <from[1]>-decreasing order
			// add nums which cannot be covered by [1]
			Insert(whereis[now++]);
		} ans = std::min(ans, *sums.begin() + fst);
	} cout << ans << endl; 
}

int main() {
    std::ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n;
    rep (t, 1, 3) {
        rep (i, 1, n) { cin >> aa[t][i]; nds[i + (t - 1) * n] = {aa[t][i], i, t}; }
    }

    std::sort(nds + 1, nds + 1 + n * 3);
    for (int i = 1; i <= 3 * n; ++i) { // sort, unique and record the first pos the num exists
        if (nds[i].val != nds[i - 1].val) ++cnt;
        aa[nds[i].from][nds[i].pos] = cnt;
        whereis[cnt].from[nds[i].from] = std::min(whereis[cnt].from[nds[i].from], nds[i].pos);
    }
    
    solve();

    return 0;
}

```



---

