# Multi-Colored Segments

## 题目描述

Dmitry has $ n $ segments of different colors on the coordinate axis $ Ox $ . Each segment is characterized by three integers $ l_i $ , $ r_i $ and $ c_i $ ( $ 1 \le l_i \le r_i \le 10^9, 1 \le c_i \le n $ ), where $ l_i $ and $ r_i $ are are the coordinates of the ends of the $ i $ -th segment, and $ c_i $ is its color.

Dmitry likes to find the minimum distances between segments. However, he considers pairs of segments of the same color uninteresting. Therefore, he wants to know for each segment the distance from this segment to the nearest differently colored segment.

The distance between two segments is the minimum of the distances between a point of the first segment and a point of the second segment. In particular, if the segments intersect, then the distance between them is equal to $ 0 $ .

For example, Dmitry has $ 5 $ segments:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1741F/79204e7473b447d8fc1f451b9209c375a1af681c.png)- The first segment intersects with the second (and these are segments of different colors), so the answers for them are equal to $ 0 $ .
- For the $ 3 $ -rd segment, the nearest segment of a different color is the $ 2 $ -nd segment, the distance to which is equal to $ 2 $ .
- For the $ 4 $ -th segment, the nearest segment of a different color is the $ 5 $ -th segment, the distance to which is equal to $ 1 $ .
- The $ 5 $ -th segment lies inside the $ 2 $ -nd segment (and these are segments of different colors), so the answers for them are equal to $ 0 $ .

## 说明/提示

In the first test case of the first sample there is only one segment of color $ 2 $ , and all other segments have color $ 1 $ . Therefore, for segments of color $ 1 $ , the answer is equal to the distance to the $ 3 $ rd segment, and for $ 3 $ rd one, the answer is equal to the minimum of the distances to segments of color $ 1 $ .

In the second test case of the first sample there are only $ 2 $ segments, and for both of them the answer is equal to the distance between them.

In the third test case of the first sample, each segment intersects at least one of its ends with a segment of a different color, so all answers are equal to $ 0 $ .

The fourth test case of the first sample is described in the problem statement.

In the fifth test case of the first sample, one segment lies completely inside the other, and for both of them the answer is $ 0 $ .

In the sixth test case of the first sample, all segments are points of different colors.

## 样例 #1

### 输入

```
9
3
1 2 1
3 4 1
5 6 2
2
100000000 200000000 1
900000000 1000000000 2
5
1 2 1
2 3 2
3 4 3
4 5 4
5 6 5
5
1 5 1
4 9 2
1 2 1
8 9 2
5 7 3
2
1 100 2
10 90 1
3
1 1 1
10 10 2
1000000000 1000000000 3
3
3 4 1
2 5 1
1 6 2
6
5 6 2
11 12 3
7 8 2
3 4 2
1 2 1
9 10 2
2
1 3 1
2 3 2```

### 输出

```
3 1 1 
700000000 700000000 
0 0 0 0 0 
0 0 2 1 0 
0 0 
9 9 999999990 
0 0 0 
3 1 3 1 1 1 
0 0```

## 样例 #2

### 输入

```
4
8
11 16 7
12 15 7
2 5 8
17 22 5
1 8 8
19 23 8
16 16 6
6 7 5
9
1 4 3
5 11 1
8 11 3
1 10 1
2 11 1
1 10 4
3 11 1
5 7 1
1 11 1
9
25 25 1
26 26 1
24 24 2
13 14 2
12 16 2
17 18 1
19 19 1
24 27 2
24 27 1
9
15 18 1
20 22 2
13 22 2
13 22 2
3 13 2
6 10 2
3 6 2
19 24 2
22 24 2```

### 输出

```
0 1 1 0 0 0 0 0 
0 0 0 0 0 0 0 0 0 
0 0 0 3 1 1 3 0 0 
0 2 0 0 2 5 9 1 4```

# 题解

## 作者：MMXIandCCXXII (赞：12)

一个数据结构都不用的方法（除了数组）。
好像没有我这样做的题解……

## 思路
看到这个题的数据肯定不能去枚举，$\text O(n^2)$ 就炸了，所以肯定不能枚举，那么就想到去找和当前线段离的最近的左右两条不同色线段，计算长度。

那么我们就需要给线段排序，这里我用的是左端点越靠左越前。排完序后就可以去找左边和右边的不同色线段了。

但如果有一大段同色的线段，每个都去找一定是会超时的，但由于他们都是一种颜色，左右两边最近的不同色也是一样的，我们只用在这个区间的第一条线段那里处理一次就行了。

然后就是去找左边和右边最近的。右边好处理，因为是按左端点排序，右边的一个不同色的左端点就是右边最近的，而左边的就要注意了。

首先，你会想到类似右边的方法找，但这样是错误的，因为会有这种情况：
![](https://cdn.luogu.com.cn/upload/image_hosting/z119l2j7.png)

排完序后红箭头指向的红线段是黑线段区间前的最后一个，但他不是右端点最靠右的。**所以我们的问题是找前面的线段中右端点最靠右的。**

但这样还是有问题：

![](https://cdn.luogu.com.cn/upload/image_hosting/pjj1oszu.png)

如图，箭头指的是这个黑区间前面的线段中右端点最靠右的，而它和当前区间同色。所以我们除了记录最靠右，还要记录和最靠右的颜色不同的最靠右的，根据情况判断用哪一个就行了。

## code
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

struct node
{
	int l, r, c;
	int id;
} a[200010];

bool cmp(node x, node y)
{
	if (x.l != y.l) return x.l < y.l;
	return x.r < y.r;
}

int ans[200010];

signed main()
{
//	freopen ("F.in", "r", stdin);
//	freopen ("F.out", "w", stdout);
	int t;
	cin >> t;
	a[0] = {-2000000000000, -200000000000, 0, 0}; //千万不要在这里直接写-2e9，下面同理
	while (t--)
	{
		int n;
		cin >> n;
		for (int i = 1; i <= n; i++) cin >> a[i].l >> a[i].r >> a[i].c, a[i].id = i;
		sort (a + 1, a + n + 1, cmp);
		a[n + 1] = {200000000000, 200000000000, 0, 0};
		int max1 = -1e18, max2 = -1e18, maxt, r;
		for (int i = 1; i <= n; i++)
		{
			if (a[i].c != a[i - 1].c)
			{
				r = i + 1;
				while (a[i].c == a[r].c) r++;//找右边线段
//				cout << l << " " << r << endl; 
			}
          
        //找左边线段  
			if (a[i].r > max1)
			{
				if (a[i].c != maxt) max2 = max1, maxt = a[i].c;
				max1 = a[i].r;
			}
			else if (a[i].r > max2 && a[i].c != maxt) max2 = a[i].r;
			
          //记录答案，左边和右边取最小
          ans[a[i].id] = min (max (a[i].l - (a[i].c == maxt ? max2 : max1), 0ll), max (a[r].l - a[i].r, 0ll));
		}
		for (int i = 1; i <= n; i++) cout << ans[i] << " ";
		cout << endl;
	}
	return 0;
}
```

---

## 作者：shinkuu (赞：6)

为啥现在的题解都感觉这么复杂。我来个容易理解的。

维护一个序列 $a$，表示当前点被几个线段覆盖。如果当前选出了颜色 $x$，那么 $\forall i,c_i=x$，$[l_i,r_i]$ 内所有 $a_i\leftarrow a_i-1$。这样就只有 $c_i\not=x$ 的 $i$ 会产生贡献了。此时只要找到最近的一个 $a_i>0$，即为答案位置。线段树上二分维护。

再特判一下线段有交集，就是简单区间查询。

最后发现 $1\leq l_i\leq r_i\leq 10^9$。离散化一下即可。

code：

```cpp
int n,m,d[N],L[N],R[N],c[N],ans[N];
vector<int> col[N];
ll tr[N<<2],tag[N<<2];
inline void pushup(int o){
	tr[o]=tr[o<<1]+tr[o<<1|1];
}
inline void pushdown(int l,int r,int o){
	int mid=(l+r)>>1;
	tr[o<<1]+=(mid-l+1)*tag[o],tr[o<<1|1]+=(r-mid)*tag[o];
	tag[o<<1]+=tag[o],tag[o<<1|1]+=tag[o];
	tag[o]=0;
}
void update(int l,int r,int o,int x,int y,int k){
	if(l>=x&&r<=y){
		tr[o]+=(r-l+1)*k;
		tag[o]+=k;
		return;
	}
	pushdown(l,r,o);
	int mid=(l+r)>>1;
	if(x<=mid)
		update(l,mid,o<<1,x,y,k);
	if(y>mid)
		update(mid+1,r,o<<1|1,x,y,k);
	pushup(o);
}
bool query(int l,int r,int o,int x,int y){
	if(l>=x&&r<=y)
		return tr[o];
	pushdown(l,r,o);
	int mid=(l+r)>>1;
	if(x<=mid&&y>mid)
		return query(l,mid,o<<1,x,y)|query(mid+1,r,o<<1|1,x,y);
	if(x<=mid)
		return query(l,mid,o<<1,x,y);
	return query(mid+1,r,o<<1|1,x,y);
}
int query_l(int l,int r,int o,int x){
	if(l>x||!tr[o])
		return 0;
	if(l==r){
		if(tr[o])
			return l;
		return 0;
	}
	pushdown(l,r,o);
	int mid=(l+r)>>1;
	if(x>mid){
		int ret=query_l(mid+1,r,o<<1|1,x);
		if(ret>=1)
			return ret;
	}
	return query_l(l,mid,o<<1,x);
}
int query_r(int l,int r,int o,int x){
	if(r<x||!tr[o])
		return m+1;
	if(l==r){
		if(tr[o])
			return l;
		return m+1;
	}
	pushdown(l,r,o);
	int mid=(l+r)>>1;
	if(x<=mid){
		int ret=query_r(l,mid,o<<1,x);
		if(ret<=m)
			return ret;
	}
	return query_r(mid+1,r,o<<1|1,x);
}
void solve(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		col[i].clear();
	for(int i=1;i<=n;i++){
		scanf("%d%d%d",&L[i],&R[i],&c[i]);
		d[i]=L[i],d[i+n]=R[i];
		col[c[i]].eb(i);
	}
	sort(d+1,d+n*2+1);
	m=unique(d+1,d+n*2+1)-d-1;
	for(int i=1;i<=m*4;i++)
		tr[i]=tag[i]=0;
	for(int i=1;i<=n;i++){
		L[i]=lower_bound(d+1,d+m+1,L[i])-d;
		R[i]=lower_bound(d+1,d+m+1,R[i])-d;
		update(1,m,1,L[i],R[i],1);
	}
	d[0]=-inf,d[m+1]=inf;
	for(int i=1;i<=n;i++){
		for(int j:col[i])
			update(1,m,1,L[j],R[j],-1);
		for(int j:col[i]){
			if(query(1,m,1,L[j],R[j]))
				ans[j]=0;
			else{
				int pl=query_l(1,m,1,L[j]),pr=query_r(1,m,1,R[j]);
				ans[j]=min(1ll*d[L[j]]-d[pl],1ll*d[pr]-d[R[j]]);
			}
		}
		for(int j:col[i])
			update(1,m,1,L[j],R[j],1);
	}
	for(int i=1;i<=n;i++)
		printf("%d ",ans[i]);
	puts("");
}
signed main(){
//	freopen("ex_data1.in","r",stdin);
	int t=1;
		scanf("%d",&t);
	while(t--)
		solve();
}
```

---

## 作者：wxzzzz (赞：4)

### 题意

给定 $n$ 条线段，对于每条线段求离它最近的与颜色不同的线段的距离。

### 思路

对于一条线段，如果它和一条颜色不同的线段相交，它的答案为 $0$。

考虑判断一条线段是否和一条颜色不同的线段相交。

分别考虑每种颜色。

先添加所有线段，将 $n$ 条线段覆盖的区间分别区间加 $1$。

对于颜色 $i$：

1. 把颜色为 $i$ 的线段删掉，将这些线段覆盖的区间分别区间减 $1$。

1. 如果某个颜色为 $i$ 的线段所覆盖的区间之和不为 $0$，说明该线段至少和一条颜色不为 $i$ 的线段相交。

1. 复原，将所有颜色为 $i$ 的线段覆盖的区间分别区间加 $1$。

区间修改、求和可用线段树维护。

接着考虑离每条线段最近的不同颜色线段的距离。

类似判断线段相交，分颜色考虑，先添加所有线段，然后删去颜色为 $i$ 的线段。

令线段覆盖后的数组为 $a$，有：

$$\min_{c_i\ne c_j} dis(i,j)=\min\Big(\big(l_i-\max_{j<l_i,a_j>0}j\big),\big(\min_{j>r_i,a_j>0}j-r_i\big)\Big)$$

$\displaystyle\max_{j<l_i,a_j>0}j$ 是 $l_i$ 左边第一个颜色不为 $c_i$ 的线段的右端点，$\displaystyle\min_{j>r_i,a_j>0}j$ 是 $r_i$ 右边第一个颜色不为 $c_i$ 的线段的左端点。

这两个值可以用线段树维护。

需要实现几个函数：

1. $findlt(x)$ 维护子树内最大的 $i$，满足 $a_i>0$。
	
    - 如果每棵子树都和为 $0$，返回无解。
    
    - 每次向一棵和不为 $0$ 的子树递归，优先递归右子树，保证找到的 $i$ 最大。

1. $findrt(x)$ 维护子树内最小的 $i$，满足 $a_i>0$。
	
    - 和 $findlt(x)$ 同理。

1. $findl(x)$ 维护 $\displaystyle\max_{i\le x,a_i>0}i$。
	
    - 先在线段树上向下递归，找到 $x$。
    
    - 如果 $a_x>0$，返回 $x$。
    
    - 否则向上回溯，找到第一个节点 $u$，$u$ 的左子树 $v$ 内有至少一个 $a_i>0$（因为要保证答案小于 $x$，所以只能去左子树）。
    
    - 在 $v$ 子树内用 $findlt$ 找到最大的 $i$，满足 $a_i>0$。

1. $findr(x)$ 维护 $\displaystyle\min_{i\ge x,a_i>0}i$。
	
    - 和 $findl(x)$ 同理。

最后注意，$l_i,r_i$ 可达 $10^9$，要离散化。

### 代码

此题代码几个易错的点：

1. 初始化非常多，非常容易错，如果样例部分错了，建议一个一个单独测一遍，看看是不是初始化写错了。常见的错误是在线段树中只清空了 $n\times 4$ 个节点，但是此题有 $n$ 条线段，$n\times 2$ 个端点，线段树应清空 $n\times 8$ 个节点。

1. 找线段树左有边第一个有值的位置时，左右容易搞反，应该是在 $[1,l-1]$ 中找一个最靠右的位置、在 $[r+1,nv]$ 中找一个最靠左的位置。（$l,r$ 是线段左右端点，$nv$ 是全局端点总数）

```cpp
#include <bits/stdc++.h>
using namespace std;
int T, n, nv, val[400005], ans[400005];
struct seg {
    int l, r, c, id;
};
vector<seg> c[400005];
struct node {
    int l, r, val, tag;
} t[400005 << 2];
void pushup(int p) {
    t[p].val = t[p << 1].val + t[p << 1 | 1].val;
}
void pushdown(int p) {
    if (!t[p].tag)
        return;

    t[p << 1].val += (t[p << 1].r - t[p << 1].l + 1) * t[p].tag;
    t[p << 1 | 1].val += (t[p << 1 | 1].r - t[p << 1 | 1].l + 1) * t[p].tag;
    t[p << 1].tag += t[p].tag;
    t[p << 1 | 1].tag += t[p].tag;
    t[p].tag = 0;
}
void build(int p, int l, int r) {
    t[p].l = l, t[p].r = r;

    if (l == r)
        return;

    int mid = l + r >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
}
void change(int p, int l, int r, int k) {
    if (t[p].l >= l && t[p].r <= r) {
        t[p].val += (t[p].r - t[p].l + 1) * k;
        t[p].tag += k;
        return;
    }

    pushdown(p);
    int mid = t[p].l + t[p].r >> 1;

    if (l <= mid)
        change(p << 1, l, r, k);

    if (mid < r)
        change(p << 1 | 1, l, r, k);

    pushup(p);
}
int query(int p, int l, int r) {
    if (t[p].l >= l && t[p].r <= r)
        return t[p].val;

    pushdown(p);
    int mid = t[p].l + t[p].r >> 1, ret = 0;

    if (l <= mid)
        ret += query(p << 1, l, r);

    if (mid < r)
        ret += query(p << 1 | 1, l, r);

    return ret;
}
int findlt(int p) {
    if (t[p].l == t[p].r) {
        if (t[p].val)
            return t[p].l;

        return 0;
    }

    pushdown(p);
    int mid = t[p].l + t[p].r >> 1;

    if (t[p << 1].val)
        return findlt(p << 1);
    else if (t[p << 1 | 1].val)
        return findlt(p << 1 | 1);

    return 0;
}
int findrt(int p) {
    if (t[p].l == t[p].r) {
        if (t[p].val)
            return t[p].l;

        return 0;
    }

    pushdown(p);
    int mid = t[p].l + t[p].r >> 1;

    if (t[p << 1 | 1].val)
        return findrt(p << 1 | 1);
    else if (t[p << 1].val)
        return findrt(p << 1);

    return 0;
}
int findl(int p, int x) {
    if (t[p].l == t[p].r) {
        if (t[p].val)
            return t[p].l;

        return 0;
    }

    pushdown(p);
    int mid = t[p].l + t[p].r >> 1, tmp;

    if (x <= mid)
        return findl(p << 1, x);
    else {
        tmp = findl(p << 1 | 1, x);

        if (tmp)
            return tmp;

        return findrt(p << 1);
    }
}
int findr(int p, int x) {
    if (t[p].l == t[p].r) {
        if (t[p].val)
            return t[p].l;

        return 0;
    }

    pushdown(p);
    int mid = t[p].l + t[p].r >> 1, tmp;

    if (x <= mid) {
        tmp = findr(p << 1, x);

        if (tmp)
            return tmp;

        return findlt(p << 1 | 1);
    } else
        return findr(p << 1 | 1, x);
}
int main() {
    cin >> T;

    while (T--) {
        for (int i = 1; i <= n; i++)
            c[i].clear();

        for (int i = 1; i <= n * 8; i++)
            t[i].l = t[i].r = t[i].val = t[i].tag = 0;

        cin >> n;
        nv = 0;

        for (int i = 1, l, r, col; i <= n; i++) {
            cin >> l >> r >> col;
            c[col].push_back({l, r, col, i});
            val[++nv] = l, val[++nv] = r;
            ans[i] = 1e18;
        }

        sort(val + 1, val + nv + 1);
        nv = unique(val + 1, val + nv + 1) - val - 1;
        build(1, 1, nv);

        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < c[i].size(); j++) {
                c[i][j].l = lower_bound(val + 1, val + nv + 1, c[i][j].l) - val;
                c[i][j].r = lower_bound(val + 1, val + nv + 1, c[i][j].r) - val;
                change(1, c[i][j].l, c[i][j].r, 1);
            }
        }

        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < c[i].size(); j++)
                change(1, c[i][j].l, c[i][j].r, -1);

            for (int j = 0, tmp; j < c[i].size(); j++) {
                if (query(1, c[i][j].l, c[i][j].r))
                    ans[c[i][j].id] = 0;
                else {
                    tmp = findl(1, c[i][j].l - 1);

                    if (tmp)
                        ans[c[i][j].id] = min(ans[c[i][j].id], val[c[i][j].l] - val[tmp]);

                    tmp = findr(1, c[i][j].r + 1);

                    if (tmp)
                        ans[c[i][j].id] = min(ans[c[i][j].id], val[tmp] - val[c[i][j].r]);
                }
            }

            for (int j = 0; j < c[i].size(); j++)
                change(1, c[i][j].l, c[i][j].r, 1);
        }

        for (int i = 1; i <= n; i++)
            cout << ans[i] << ' ';

        cout << '\n';
    }

    return 0;
}
```

---

## 作者：_maojun_ (赞：3)

一种不用线段树上二分的做法。

---

首先考虑怎么求出离一条线段最近的线段。

如果没有颜色的区别。那么先从左到右扫一遍，如果找到了一个右端点，则把 $dis$ 设为 $0$；对于每个端点，找到时都加上它到它之前的第一个端点的距离；如果找到了一个左端点，则用 $dis$ 更新答案。然后再从右到左扫一遍。

那么考虑加上颜色怎么做。可以对于每个颜色都开一个 $dis$，更新操作相同，但查询的时候用**全局除这个颜色之外的所有颜色的最小距离**更新答案。那么这是一个全局加，区间赋值，区间求 $\min$ 的问题，朴素线段树维护，复杂度 $O(n\log n)$。

然后发现样例都过不了，因为还有相交的情况

那么先对坐标离散化。我们发现可以先把所有线段覆盖的点加一，然后枚举每种颜色。先把这种颜色的所有线段分离出来，即全部减一；检验每条线段覆盖的区间是否存在非 $0$ 值，若存在，则将对应的答案标为 $0$；最后把拿出来的线段放回去，即全部加一。

于是再整一只线段树，区间加，区间查询 $\max$。因为每个线段只会加入 $2$ 次，删除 $1$ 次，所以这一部分的复杂度仍然是 $O(n\log n)$。

然而因为有两只线段树，所以跑得稍微慢于线段树上二分的写法。

```cpp
#include<algorithm> 
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
using namespace std;

inline int max(int x,int y){return x>y?x:y;}
inline void chkmax(int&x,int y){x=x>y?x:y;}
inline void chkmin(int&x,int y){x=x<y?x:y;}
typedef long long ll;
const int MAXN=2e5+5,INF=0x3f3f3f3f;
int n,m=0,l[MAXN],r[MAXN],c[MAXN],ans[MAXN];

namespace Solve1{			// 计算离每条线段最近的异色线段距离（不相交）
	namespace SegmentTree{
		struct segtree{int value,lazy;}tr[MAXN<<2];
		#define ls p<<1
		#define rs p<<1|1
		#define Ls ls,l,mid
		#define Rs rs,mid+1,r
		#define all 1,1,m
		#define val(p) tr[p].value
		#define tag(p) tr[p].lazy
		inline void push_up(int p){val(p)=min(val(ls),val(rs));}
		inline void change(int p,int k){val(p)+=k,tag(p)+=k;}
		inline void push_down(int p){
			if(!tag(p))return;
			change(ls,tag(p));change(rs,tag(p));
			tag(p)=0;
		}
		void build(int p,int l,int r){tag(p)=0;val(p)=INF;if(l==r)return;int mid=l+r>>1;build(Ls);build(Rs);}
		void update(int p,int l,int r,int P){
			if(l==r){val(p)=0;return;}
			int mid=l+r>>1;push_down(p);
			P<=mid?update(Ls,P):update(Rs,P);
			push_up(p);
		}
		inline void update(int k){change(1,k);}
		int query(int p,int l,int r,int L,int R){
			if(L<=l&&r<=R)return val(p);
			int mid=l+r>>1;push_down(p);
			if(L>mid)return query(Rs,L,R);if(R<=mid)return query(Ls,L,R);
			return min(query(Ls,L,R),query(Rs,L,R));
		}
	}using namespace SegmentTree;
	int tot=0;
	struct node{
		int p,pos,col;bool flag;node(){}
		node(int p,int pos,int col,bool flag):p(p),pos(pos),col(col),flag(flag){}
		inline bool operator<(const node&b)const{return p<b.p;}
	}a[MAXN<<1];
	inline void solve1(){
		tot=0;
		for(int i=1;i<=n;i++){
			a[++tot]=node(l[i],i,c[i],false);
			a[++tot]=node(r[i],i,c[i],true);
		}
		sort(a+1,a+tot+1);
		build(all);if(a[1].flag)update(all,a[1].col);		// 从左到右扫一遍
		for(int i=2;i<=tot;i++){
			update(a[i].p-a[i-1].p);
			if(a[i].flag)update(all,a[i].col);
			else{
				if(1<=a[i].col-1)chkmin(ans[a[i].pos],query(all,1,a[i].col-1));
				if(a[i].col+1<=m)chkmin(ans[a[i].pos],query(all,a[i].col+1,m));
			}
		}
		build(all);if(!a[tot].flag)update(all,a[tot].col);	// 从右到左扫一遍
		for(int i=tot-1;i>=1;i--){
			update(a[i+1].p-a[i].p);
			if(!a[i].flag)update(all,a[i].col);
			else{
				if(1<=a[i].col-1)chkmin(ans[a[i].pos],query(all,1,a[i].col-1));
				if(a[i].col+1<=m)chkmin(ans[a[i].pos],query(all,a[i].col+1,m));
			}
		}
	}
	#undef ls
	#undef rs
	#undef Ls
	#undef Rs
	#undef all
	#undef val
	#undef tag
}using Solve1::solve1;
namespace Solve2{			// 判是否有异色线段和每条线相交
	namespace SegmentTree{
		struct segtree{int value,lazy;}tr[MAXN<<3];
		#define ls p<<1
		#define rs p<<1|1
		#define Ls ls,l,mid
		#define Rs rs,mid+1,r
		#define all 1,1,tot
		#define val(p) tr[p].value
		#define tag(p) tr[p].lazy
		inline void push_up(int p){val(p)=max(val(ls),val(rs));}
		inline void change(int p,int k){val(p)+=k;tag(p)+=k;}
		inline void push_down(int p){
			if(!tag(p))return;
			change(ls,tag(p));change(rs,tag(p));
			tag(p)=0;
		}
		void build(int p,int l,int r){tag(p)=val(p)=0;if(l==r)return;int mid=l+r>>1;build(Ls);build(Rs);}
		void update(int p,int l,int r,int L,int R,int k){
			if(L<=l&&r<=R)return change(p,k);
			int mid=l+r>>1;push_down(p);
			if(L<=mid)update(Ls,L,R,k);if(R>mid)update(Rs,L,R,k);
			push_up(p);
		}
		int query(int p,int l,int r,int L,int R){
			if(L<=l&&r<=R)return val(p);
			int mid=l+r>>1;push_down(p);
			if(L>mid)return query(Rs,L,R);if(R<=mid)return query(Ls,L,R);
			return max(query(Ls,L,R),query(Rs,L,R));
		}
	}using namespace SegmentTree;
	
	struct node{
		int l,r,c,pos;node(){}
		node(int l,int r,int c,int pos):l(l),r(r),c(c),pos(pos){}
		inline bool operator<(const node&b)const{return c<b.c;}
	}a[MAXN];
	int tot,d[MAXN<<1];
	inline void solve2(){
		tot=0;
		for(int i=1;i<=n;i++)d[++tot]=l[i],d[++tot]=r[i];
		sort(d+1,d+tot+1);tot=unique(d+1,d+tot+1)-d-1;
		for(int i=1;i<=n;i++){								// 离散化
			l[i]=lower_bound(d+1,d+tot+1,l[i])-d,
			r[i]=lower_bound(d+1,d+tot+1,r[i])-d,
			a[i]=node(l[i],r[i],c[i],i);
		}
		sort(a+1,a+n+1);
		build(all);
		for(int i=1;i<=n;i++)update(all,l[i],r[i],1);
		int lst=1;
		a[n+1].c=1919810;
		for(int i=2;i<=n+1;i++)
			if(a[i].c^a[lst].c){							// 把同色段提取出来
				for(int j=lst;j<i;j++)update(all,a[j].l,a[j].r,-1);
				for(int j=lst;j<i;j++){
					if(query(all,a[j].l,a[j].r))ans[a[j].pos]=0;
				}
				for(int j=lst;j<i;j++)update(all,a[j].l,a[j].r,1);
				lst=i;
			}
	}
	#undef ls
	#undef rs
	#undef Ls
	#undef Rs
	#undef all
	#undef val
	#undef tag
}using Solve2::solve2;
const int LIMIT=5e7;
inline void solve(){
	scanf("%d",&n);m=0;
	for(int i=1;i<=n;i++)
		scanf("%d%d%d",&l[i],&r[i],&c[i]),ans[i]=INF,chkmax(m,c[i]);
	solve1();solve2();
	for(int i=1;i<=n;i++)printf("%d ",ans[i]);
	printf("\n");
}
int main(){
	int T;scanf("%d",&T);
	while(T--)solve();
	return 0;
}
```

---

## 作者：ifffer_2137 (赞：1)

感觉很板子的一道题啊，会线段树上二分应该一眼就能做完了，码量也不算特别大。
### 题意
给定一维数轴上 $n$ 条线段，每条线段都有给定的颜色 $c_i$，对于每个 $i$，请求出：
$$\min_{c_j \neq c_i} dis(i,j)$$
其中 $dis(i,j)$ 表示线段 $i$，$j$ 之间的距离，特别地，有相交（包括端点）的两条线段之间的距离定义为 $0$。
### 分析
容易想到，可以把同种颜色的线段一起求解，因为它们所面对的情形是一样的，都是除掉该颜色线段的所有线段覆盖的情形。

这个东西显然要用 ds 来维护，容易想到线段树。对于一条线段，想要求解
$$\min_{c_j \neq c_i} dis(i,j)$$
只需要先判断一下有没有线段和它相交，再找出它左边和它右边离它最近的一个端点，取两者距离较小值就行了。

判断相交维护区间加区间求和就可以了，左/右边最近的非零位置是线段树上二分的板子。最后注意到值域达到了 $10^9$，加个离散化的小 tirck 就好了。

这样复杂度就可以做到时间 $\mathcal O(n\log_2n)$，空间 $\mathcal O(n)$ 了，记得数组开两倍。
### 代码
```cpp
//From: ifffer_2137
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define inf 0x7fffffff
inline int read(){
    char ch=getchar();int x=0,w=1;
    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+ch-48,ch=getchar();return w==1?x:-x;
}
const int maxn=4e5+5;
int T;
int n;
struct node{
	int id;
	int l,r;
}a[maxn];
vector<node> s[maxn];
int tmp[maxn*2],tot;
int c[maxn],ans[maxn];
struct Segment_Tree{
	int sumv[maxn*4],tag[maxn*4];
	void pushup(int o){
		sumv[o]=sumv[o*2]+sumv[o*2+1];
	}
	void pushdown(int o,int l,int r){
		if(tag[o]){
			int m=(l+r)/2;
			tag[o*2]+=tag[o];
			sumv[o*2]+=tag[o]*(m-l+1);
			tag[o*2+1]+=tag[o];
			sumv[o*2+1]+=tag[o]*(r-m);
			tag[o]=0;
		}
	}
	void build(int o,int l,int r){
		sumv[o]=tag[o]=0;
		if(l==r){
			return;
		}
		int m=(l+r)/2;
		build(o*2,l,m);
		build(o*2+1,m+1,r);
	}
	void update(int o,int l,int r,int x,int y,int k){
		if(x<=l&&r<=y){
			tag[o]+=k;
			sumv[o]+=k*(r-l+1);
			return;
		}
		pushdown(o,l,r);
		int m=(l+r)/2;
		if(x<=m) update(o*2,l,m,x,y,k);
		if(y>m) update(o*2+1,m+1,r,x,y,k);
		pushup(o);
	}
	int getsum(int o,int l,int r,int x,int y){
		if(x<=l&&r<=y){
			return sumv[o];
		}
		pushdown(o,l,r);
		int m=(l+r)/2,res=0;
		if(x<=m) res+=getsum(o*2,l,m,x,y);
		if(y>m) res+=getsum(o*2+1,m+1,r,x,y);
		return res;
	}
	int query_mn(int o,int l,int r,int x){
		if(r<x||!sumv[o]) return tot+1;
		if(l==r){
			if(sumv[o]) return l;
			return tot+1;
		}
		pushdown(o,l,r);
		int m=(l+r)/2;
		if(x<=m){
			int res=query_mn(o*2,l,m,x);
			if(res<=tot) return res;
		}
		return query_mn(o*2+1,m+1,r,x);
	}
	int query_mx(int o,int l,int r,int x){
		if(l>x||!sumv[o]) return 0;
		if(l==r){
			if(sumv[o]) return l;
			return 0;
		}
		pushdown(o,l,r);
		int m=(l+r)/2;
		if(x>m){
			int res=query_mx(o*2+1,m+1,r,x);
			if(res>=1) return res;
		}
		return query_mx(o*2,l,m,x);
	}
}seg;
signed main(){
	cin.tie(0),cout.tie(0);
	T=read();
	while(T--){
		n=read();
		tot=0;
		for(int i=1;i<=n;i++){
			s[i].clear();
			int l=read(),r=read();
			a[i]={i,l,r};
			c[i]=read();
			tmp[++tot]=l,tmp[++tot]=r;
		}
		sort(tmp+1,tmp+tot+1);
		tot=unique(tmp+1,tmp+tot+1)-tmp-1;
		seg.build(1,1,tot);
		for(int i=1;i<=n;i++){
			a[i].l=lower_bound(tmp+1,tmp+tot+1,a[i].l)-tmp;
			a[i].r=lower_bound(tmp+1,tmp+tot+1,a[i].r)-tmp;
			seg.update(1,1,tot,a[i].l,a[i].r,1);
			s[c[i]].push_back(a[i]);
		}
		tmp[0]=-inf,tmp[tot+1]=inf;
		for(int i=1;i<=n;i++){
			if(!s[i].size()) continue;
			for(node x:s[i]){
				seg.update(1,1,tot,x.l,x.r,-1);
			}
			for(node x:s[i]){
				if(seg.getsum(1,1,tot,x.l,x.r)) ans[x.id]=0;
				else{
					ans[x.id]=min(tmp[x.l]-tmp[seg.query_mx(1,1,tot,x.l)],tmp[seg.query_mn(1,1,tot,x.r)]-tmp[x.r]);
				}
			}
			for(node x:s[i]){
				seg.update(1,1,tot,x.l,x.r,1);
			}
		}
		for(int i=1;i<=n;i++){
			cout<<ans[i]<<" ";
		}
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：ningago (赞：1)

> 智商不够，DS来凑。

首先离散化掉左右端点，用 $idx$ 表示离散化后最大值。

用 $tr_i$ 表示被线段树维护的点。

考虑到第 $i$ 条线段时，将于 $c_i$ 颜色不同的所有线段插入线段树里，插入线段 $j$ 的方式就是 $\forall k\in [l_j,r_j],tr_k$ 暴力加一。

于是问题就变成了：

- 如果线段树上 $\exists j\in[l_i,r_i],tr_j \ne 0$，那么答案就是 $0$（也就是有交点）。

- 否则，找到 $\max_{j\in [1,l_i),tr_j \ne 0},j$ 和 $\min_{j\in (r_i,idx],tr_j \ne 0},j$，输出两者之间对于 $l_i$ 和 $r_i$ 最短的距离即可。

那么怎么找到上面那一大段式子的值呢？使用线段树上二分即可。

复杂度 $O(n\log ^2 n)$

```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <algorithm>

#define N 400010

int n;
std::map <int,int> mp;
int fmp[N << 1];
int mpidx;

struct Tree
{
	int l,r;
	int sum;
	int mx;
	int lazy;
	void push(int z)
	{
		sum += (r - l + 1) * z;
		mx += z;
		lazy += z;
	}
}tr[N << 2];

#define lson k << 1
#define rson k << 1 | 1

void pushup(int k)
{
	tr[k].sum = tr[lson].sum + tr[rson].sum;
	tr[k].mx = std::max(tr[lson].mx,tr[rson].mx);
}

void pushdown(int k)
{
	if(tr[k].lazy)
	{
		tr[lson].push(tr[k].lazy);
		tr[rson].push(tr[k].lazy);
		tr[k].lazy = 0;
	}
}

void build(int k,int l,int r)
{
	tr[k].l = l,tr[k].r = r;
	tr[k].mx = tr[k].sum = 0;
	tr[k].lazy = 0;
	if(l == r)
		return;
	int mid = l + r >> 1;
	build(lson,l,mid);
	build(rson,mid + 1,r);
}

void change(int k,int ql,int qr,int z)
{
	int l = tr[k].l,r = tr[k].r;
	if(ql <= l && r <= qr)
	{
		tr[k].push(z);
		return;
	}
	pushdown(k);
	int mid = l + r >> 1;
	if(ql <= mid)
		change(lson,ql,qr,z);
	if(mid < qr)
		change(rson,ql,qr,z);
	pushup(k);
}

int query_sum(int k,int ql,int qr)
{
	int res = 0;
	int l = tr[k].l,r = tr[k].r;
	if(ql <= l && r <= qr)
		return tr[k].sum;
	pushdown(k);
	int mid = l + r >> 1;
	if(ql <= mid)
		res += query_sum(lson,ql,qr);
	if(mid < qr)
		res += query_sum(rson,ql,qr);
	return res;
}

int query_last(int k)
{
	if(tr[k].l == tr[k].r)
	{
		if(tr[k].mx != 0)
			return tr[k].l;
		return 1;
	}
	pushdown(k);
	if(tr[rson].mx != 0)
		return query_last(rson);
	if(tr[lson].mx != 0)
		return query_last(lson);
	return 1;
}

int query_first(int k)
{
	if(tr[k].l == tr[k].r)
	{
		if(tr[k].mx != 0)
			return tr[k].l;
		return mpidx;
	}
	pushdown(k);
	if(tr[lson].mx != 0)
		return query_first(lson);
	if(tr[rson].mx != 0)
		return query_first(rson);
	return mpidx;
}

int query_last_um_nik(int k,int ql,int qr)
{
	int l = tr[k].l,r = tr[k].r;
	if(ql <= l && r <= qr)
		return query_last(k);
	int res = 1,mid = l + r >> 1;
	if(ql <= mid)
		res = std::max(res,query_last_um_nik(lson,ql,qr));
	if(mid < qr)
		res = std::max(res,query_last_um_nik(rson,ql,qr));
	return res;
}

int query_first_um_nik(int k,int ql,int qr)
{
	int l = tr[k].l,r = tr[k].r;
	if(ql <= l && r <= qr)
		return query_first(k);
	int res = mpidx,mid = l + r >> 1;
	if(ql <= mid)
		res = std::min(res,query_first_um_nik(lson,ql,qr));
	if(mid < qr)
		res = std::min(res,query_first_um_nik(rson,ql,qr));
	return res;
}

struct node
{
	int l,r,c,id;
	bool operator < (const node &B)const
	{
		return c < B.c;
	}
}a[N];

int ans[N];

int T;
int sta[N << 2],top;

int main()
{
	scanf("%d",&T);
	while(T--)
	{
		mp.clear();
		top = 0;
		mpidx = 0;
		scanf("%d",&n);
		for(int i = 1;i <= n;i++)
		{
			scanf("%d%d%d",&a[i].l,&a[i].r,&a[i].c);
			sta[++top] = a[i].l;
			sta[++top] = a[i].r;
			a[i].id = i;
		}
		sta[++top] = 0;
		sta[++top] = 0x3f3f3f3f;
		std::sort(sta + 1,sta + 1 + top);
		for(int i = 1;i <= top;i++)
		{
			if(!mp[sta[i]])
			{
				mp[sta[i]] = ++mpidx;
				fmp[mpidx] = sta[i];
			}
		}
		for(int i = 1;i <= n;i++)
		{
			a[i].l = mp[a[i].l];
			a[i].r = mp[a[i].r];
		}
		std::sort(a + 1,a + 1 + n);
		int last = 0;
		build(1,1,mpidx);
		for(int i = 1;i <= n;i++)
		{
			change(1,a[i].l,a[i].r,1);
		}
		for(int i = 1;i <= n;i++)
		{
			if(last != a[i].c)
			{
				int p = i - 1;
				while(p >= 1 && a[p].c == last)
				{
					change(1,a[p].l,a[p].r,1);
					p--;
				}
				last = a[i].c;
				p = i;
				while(p <= n && a[p].c == last)
				{
					change(1,a[p].l,a[p].r,-1);
					p++;
				}
			}
			if(query_sum(1,a[i].l,a[i].r))
			{
				ans[a[i].id] = 0;
			}
			else
			{
				int left = query_last_um_nik(1,1,a[i].l - 1);
				int right = query_first_um_nik(1,a[i].r + 1,mpidx);
				int res = 0x3f3f3f3f;
				if(left != 1)
					res = std::min(res,fmp[a[i].l] - fmp[left]);
				if(right != mpidx)
					res = std::min(res,fmp[right] - fmp[a[i].r]);
				ans[a[i].id] = res;
			}
		}
		for(int i = 1;i <= n;i++)
			printf("%d ",ans[i]);
		putchar('\n');
		build(1,1,mpidx);
		for(int i = 1;i <= mpidx;i++)
			fmp[mp[i]] = 0;
	}
	return 0;
}
```

---

