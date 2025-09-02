# Gifts Order

## 题目描述

“T-Generation” 队计划采购一些毛衣以满足多种需求，他们拥有 $n$ 件毛衣编号从 $1$ 至 $n$。第 $i$ 件毛衣的尺寸为 $a_i$。现在，他们需要选出某段连续的毛衣送去参加奥林匹克竞赛。这些毛衣必须尽可能适合更多的人，同时又不能选择得太多。

他们需要选择两个下标 $l$ 和 $r$（$1 \le l \le r \le n$），使便利性最大化。便利性定义为 $\operatorname{max}(a_l, a_{l + 1}, \ldots, a_r) - \operatorname{min}(a_l, a_{l + 1}, \ldots, a_r) - (r - l)$，也就是尺寸的范围减去所选毛衣数量。

考虑到毛衣的尺寸可能会发生变化，总共有 $q$ 次这样的变动。每次变化中，第 $p$ 件毛衣的尺寸变为 $x$。

请帮助 “T-Generation” 团队计算出在所有可能的 $(l, r)$ 对中，初次和每次尺寸调整后的最大便利性。

## 说明/提示

来看第一个测试用例的情况：

- 在没有变化之前，可以选取所有毛衣，此时便利性等于 $\operatorname{max}(a_1, a_2) - \operatorname{min}(a_1, a_2) - (2 - 1) = 10 - 1 - 1 = 8$。
- 第一次查询后，两件毛衣的尺寸都变为 $10$，只能选取第一件毛衣，此时便利性等于 $10 - 10 - 0 = 0$。
- 第二次查询后，第一件毛衣的尺寸为 $10$，第二件为 $2$，可以选取所有毛衣，便利性为 $\operatorname{max}(a_1, a_2) - \operatorname{min}(a_1, a_2) - (2 - 1) = 10 - 2 - 1 = 7$。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
3
2 2
1 10
1 10
2 2
5 3
1 2 3 4 5
3 7
1 4
5 2
8 5
7 4 2 4 8 2 1 4
5 4
1 10
3 2
8 11
7 7```

### 输出

```
8
0
7
0
4
4
4
5
3
6
6
9
7```

# 题解

## 作者：SUNCHAOYI (赞：10)

**这是一篇 DDP 做法的题解。**

首先需要想通的一个点就是最值一定出现在端点处，否则区间长度变化而极差不变，会导致答案更劣。

设最值所在的位置为 $l,r$，则会有两种情况：

- 若最大值在最小值左侧，则答案为 $a_l - a_r - (r - l) = (a_l + l) - (a_r + r)$。

- 若最大值在最小值右侧，则答案为 $a_r - a_l - (r - l) = (a_r - r) - (a_l - l)$。

不难发现我们只需要维护 $a_i + i$ 和 $a_i - i$ 即可。

当本题不存在修改操作时，就是 [虹色的北斗七星](https://www.luogu.com.cn/problem/P8446)。设 $f_{i,0}$ 表示 $[1,i]$ 中 $a_i + i$ 的最大值，$f_{i,1}$ 表示 $[1,i]$ 中 $a_i - i$ 的最小值，$f_{i,2}$ 表示 $[1,i]$ 中答案的最大值。于是我们可以得到转移方程：

$$
\begin{cases}
f_{i,0} = \max \ \{\ f_{i - 1,0},a_i + i\ \}\\
f_{i,1} = \min \ \{\ f_{i - 1,1},a_i - i\ \}\\
f_{i,2} = \max \ \{\ f_{i - 1,2},f_{i - 1,0} - (a_i + i),(a_i - i) - f_{i - 1,1}\ \}
\end{cases}
$$

最后的答案便是 $f_{n,2}$。进一步可以发现 $f_{i,0/1/2}$ 的值只依赖于前一项，因此我们可以滚动数组优化空间，最后时间复杂度为 $O(n)$，空间复杂度为 $O(1)$。为了更好的为 DDP 做准备，可以通过增加负号的方式改写转移方程，使得均变为取 $\max$ 的形式：

$$
\begin{cases}
f_{i,0} = \max \ \{\ f_{i - 1,0},a_i + i\ \}\\
f_{i,1} = \color{red}\max\color{black} \ \{\ f_{i - 1,1},\color{red}-\color{black}(a_i - i)\ \}\\
f_{i,2} = \max \ \{\ f_{i - 1,2},f_{i - 1,0} - (a_i + i), (a_i - i)\color{red}{+}\color{black}f_{i - 1,1}\ \}
\end{cases}
$$

于是可以得到 [虹色的北斗七星](https://www.luogu.com.cn/problem/P8446) 的核心代码【注意初始化】：

```cpp
f[0][1] = -INF;
for (int i = 1;i <= n;++i)
{
	int x = read ();
	f[i & 1][0] = max (f[(i + 1) & 1][0],x + i);
	f[i & 1][1] = max (f[(i + 1) & 1][1],-(x - i));
	f[i & 1][2] = max (f[(i + 1) & 1][2],max (f[(i + 1) & 1][0] - (x + i),(x - i) + f[(i + 1) & 1][1]));
}
printf ("%d\n",f[n & 1][2] - 1);
```

既然已经写成了可以迭代的形式，那么就可以改写成矩阵去维护。当然，这里的矩阵乘法需要被重载为相加取最大值的形式。如下：

$$
\begin{bmatrix} 
0 & -\infty & -\infty & a_i + i\\
-\infty & 0 & -\infty & -(a_i - i)\\
-(a_i + i) & a_i - i & 0 & -\infty\\
-\infty & -\infty & -\infty & 0
\end{bmatrix}
\begin{bmatrix} 
f_{i - 1,0}\\
f_{i - 1,1}\\
f_{i - 1,2}\\
0
\end{bmatrix}
=
\begin{bmatrix} 
f_{i,0}\\
f_{i,1}\\
f_{i,2}\\
0
\end{bmatrix}
$$

由于转移的方程式仍然满足矩阵的结合律，因此用线段树单点修改就可以维护矩阵。但需要注意的是，矩阵不满足交换律，因此需要注意**线段树更新时的顺序**！令 $m = 4$，则单组数据的时间复杂度为 $O(m^3 q \log n)$。

最后放个代码吧：

```cpp
#include <bits/stdc++.h>
#define init(x) memset (x,0,sizeof (x))
#define ll long long
#define ull unsigned long long
#define INF 0x3f3f3f3f
using namespace std;
const int MAX = 2e5 + 5;
const int MOD = 1e9 + 7;
inline int read ();
struct Mat
{
	int a[4][4];
	Mat () {init (a);}
	void clear () {init (a);} 
} tree[MAX << 2],I,A;
int t,n,q,a[MAX]; 
Mat operator * (Mat A,Mat B);
void build (int cur,int l,int r);
void modify (int cur,int l,int r,int x,int v);
int main ()
{
	//freopen (".in","r",stdin);
	//freopen (".out","w",stdout);
	I.a[0][1] = I.a[0][2] = I.a[1][0] = I.a[1][2] = I.a[2][3] = I.a[3][0] = I.a[3][1] = I.a[3][2] = -INF;
	t = read ();
	while (t--)
	{
		n = read ();q = read ();
		for (int i = 1;i <= n;++i) a[i] = read ();
		build (1,1,n);
		Mat ans;ans.a[1][0] = -INF;
		ans = tree[1] * ans;
		printf ("%d\n",ans.a[2][0]);
		while (q--)
		{
			int x = read (),v = read ();
			modify (1,1,n,x,v);
			Mat ans;ans.a[1][0] = -INF;//注意初始化 
			ans = tree[1] * ans;
			printf ("%d\n",ans.a[2][0]);
		}
		for (int i = 1;i <= 4 * n;++i) tree[i].clear ();
	}
	return 0;
}
inline int read ()
{
    int s = 0;int f = 1;
    char ch = getchar ();
    while ((ch < '0' || ch > '9') && ch != EOF)
	{
        if (ch == '-') f = -1;
        ch = getchar ();
    }
    while (ch >= '0' && ch <= '9')
	{
        s = s * 10 + ch - '0';
        ch = getchar ();
    }
    return s * f;
}
Mat operator * (Mat A,Mat B)
{
	Mat C;
	for (int i = 0;i < 4;++i)
		for (int j = 0;j < 4;++j) C.a[i][j] = -INF;
	for (int i = 0;i < 4;++i)
		for (int j = 0;j < 4;++j)
			for (int k = 0;k < 4;++k) C.a[i][j] = max (C.a[i][j],A.a[i][k] + B.a[k][j]);//重载为相加后取最大值 
	return C;
}
void build (int cur,int l,int r)
{
	if (l == r)
	{
		tree[cur] = I;
		tree[cur].a[0][3] = a[l] + l;tree[cur].a[1][3] = -(a[l] - l);
		tree[cur].a[2][0] = - (a[l] + l);tree[cur].a[2][1] = a[l] - l;	
		return ;
	}
	int mid = (l + r) >> 1;
	build (cur << 1,l,mid);build (cur << 1 | 1,mid + 1,r);
	tree[cur] = tree[cur << 1 | 1] * tree[cur << 1];//注意顺序！！！ 
}
void modify (int cur,int l,int r,int x,int v)
{
	if (l == r)
	{
		a[l] = v;tree[cur] = I;//一些负无穷的处理放在 I 中 
		tree[cur].a[0][3] = a[l] + l;tree[cur].a[1][3] = -(a[l] - l);
		tree[cur].a[2][0] = - (a[l] + l);tree[cur].a[2][1] = a[l] - l;
		return ;
	}
	int mid = (l + r) >> 1;
	if (x <= mid) modify (cur << 1,l,mid,x,v);
	else modify (cur << 1 | 1,mid + 1,r,x,v);
	tree[cur] = tree[cur << 1 | 1] * tree[cur << 1];//注意顺序！！！ 
}
```

---

## 作者：liyifan202201 (赞：5)

## 思路

首先，我们关注一下题目最重要的一句话。
$$
\operatorname{max} (a_l, a_{l + 1}, \ldots, a_r) - \operatorname{min} (a_l, a_{l + 1}, \ldots, a_r) - (r - l),
$$
可以通过贪心思想，若此区间的最大值与最小值尽可能大，且长度最短，则最大值与最小值必须在同一个端点，则上面的式子可以转化为：
$$
  \begin{aligned}
  原式&=a_l - a_r - (r - l)
  \\&=
  a_l - a_r - r + l
  \\&=
  (a_l + l) - (a_r + r) 
  \end{aligned}
$$

要使这个值最大，则 $(a_l + l)$ 就要尽可能的大，$(a_r + r)$ 就要尽可能的小，对于者两个查询，可以使用线段树维护。

但是，题目要求 $l \le r$，而线段树显然是无法做到这一点，所以我们需要分类讨论。

1. 当 $a_l \le a_r$ 时：
> 与上述方法一致。
2. 当 $a_r \le a_l$ 时：
> $$
> \begin{aligned}
> 原式&=a_r - a_l-(r-l)
> \\&=a_r-r-a_l+l
> \\&=(a_r-r)-(a_l-l)
> \end{aligned}
> $$

对于这两种分内，我们就需要维护 $2$ 棵线段树用来维护。
## 实现
### 细节
1. `push_up`

这道题目的向上传递操作非常考验~~像我这样的~~蒟蒻，所以在这放一张图来辅助。
![](https://cdn.luogu.com.cn/upload/image_hosting/6qaih70l.png)
~~画的十分的丑+抽象，希望各位能理解。~~

### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
#define lr (ro*2)
#define rr (ro*2+1)
#define mid ((l+r)/2)
using namespace std; 
const int N=1e6;
int a[N];
int n,q;

// 线段树节点结构体，包含最大值、最小值和答案
struct node
{
    int max1,min1; // max1和min1分别表示a[i]+i的最大值和最小值
    int max2,min2; // max2和min2分别表示a[i]-i的最大值和最小值
    int ans1,ans2; // ans1和ans2分别表示两种情况下的最大便利值
};
node tr[N*4];

// 线段树的push_up操作，用于更新父节点的值
void push_up(int ro){
    // 更新当前节点的max1和min1
    tr[ro].max1=max(tr[lr].max1,tr[rr].max1);
    tr[ro].min1=min(tr[lr].min1,tr[rr].min1);
    // 更新当前节点的max2和min2
    tr[ro].max2=max(tr[lr].max2,tr[rr].max2);
    tr[ro].min2=min(tr[lr].min2,tr[rr].min2);
    // 更新当前节点的ans1和ans2
    tr[ro].ans1=max({tr[lr].ans1,tr[rr].ans1,tr[lr].max1-tr[rr].min1});
    tr[ro].ans2=max({tr[lr].ans2,tr[rr].ans2,tr[rr].max2-tr[lr].min2});
}

// 线段树的build操作，用于构建线段树
void build(int ro=1,int l=1,int r=n){
    if(l==r){
        // 叶子节点初始化
        tr[ro].max1=tr[ro].min1=a[l]+l;
        tr[ro].max2=tr[ro].min2=a[l]-l;
        tr[ro].ans1=tr[ro].ans2=0;
        return;
    }
    // 递归构建左右子树
    build(lr,l,mid);
    build(rr,mid+1,r);
    // 更新当前节点
    push_up(ro);
}

// 线段树的update操作，用于更新节点值
void update(int x,int d,int ro=1,int l=1,int r=n){
    if(l==r){
        // 更新叶子节点
        tr[ro].max1=tr[ro].min1=d+x;
        tr[ro].max2=tr[ro].min2=d-x;
        tr[ro].ans1=tr[ro].ans2=0;
        return;
    }
    // 递归更新左右子树
    if(x<=mid)
        update(x,d,lr,l,mid);
    else
        update(x,d,rr,mid+1,r);
    // 更新当前节点
    push_up(ro);
}

// 主函数，处理多个测试用例
signed main(){
    int T;
    cin>>T;
    while (T--)
    {
        cin>>n>>q;
        for(int i=1;i<=n;i++){
            cin>>a[i];
        }
        // 构建线段树
        build();
        // 输出初始的最大便利值
        cout<<max(tr[1].ans1,tr[1].ans2)<<endl;
        while (q--)
        {
            int p,x;
            cin>>p>>x;
            // 更新线段树
            update(p,x);
            // 输出更新后的最大便利值
            cout<<max(tr[1].ans1,tr[1].ans2)<<endl;
        }
    }
}
```

---

## 作者：yvbf (赞：5)

![](bilibili:BV1dkruY8ETZ?t=1204)

---

## 作者：封禁用户 (赞：3)

一个简单的 dp 做法。

考虑到每次答案更新时的右端点必定是当前区间的极值。

现在考虑当前右端点是最大值怎么做，可以考虑差分，令 $b_i = a_i - a_{i - 1} - 1$，减 $1$ 是为了实现 $-(r - l)$ 的贡献。那么现在就可以设 $f(i)$ 表示前 $i$ 个的最大贡献

$$
f(i) = \max(f(i - 1) + b_i, 0)
$$

答案为 $f(i)$ 中最大值。

因为最值点的 $b_i$ 肯定非负，那么就是说每次 $f(i)$ 必定只会在最值点处更新答案（答案是全局答案），否则肯定劣于附近的最值点，所以这个做法是正确的。

而至于右端点是最小值，只需要把 $a_i$ 取负再做一遍就行。

现在考虑怎么支持修改，可以构造广义矩阵乘法实现转移，这样更好维护修改。

广义矩乘满足对于乘法（$A, B, C$ 为矩阵） $A \times B = C$，$C_{i, j} = \max\{A_{i, k} + B_{k, j}\}$，可以证明该乘法有结合律。

那么此时只需要构造

$$
\begin{bmatrix}
 ans & f(i) & 0
\end{bmatrix}

\times 

\begin{bmatrix}
0  & -\infty  & -\infty\\
b_i  & b_i & -\infty\\
0  & 0 & 0
\end{bmatrix}

= 

\begin{bmatrix}
 ans(\text{new}) & f(i + 1) & 0
\end{bmatrix}
$$

此时的乘法为上述广义矩乘。

然后套个线段树即可维护修改，可以多维护个全 $0$ 的 $0$ 号结点，实现初始化和偷懒。

时间复杂度 $\mathcal{O}(\omega ^ 3 q \log n)$，$\omega = 3$。

[$\texttt{Code}$](https://codeforces.com/contest/2057/submission/300648672)

---

## 作者：cjh20090318 (赞：3)

非常好 D，让我晚一秒交上去，结果掉分了。

## 题意

一个长度为 $n$ 的序列 $a$，定义函数 $f(l,r)$：
$$
f(l,r) = \max(a_l, a_{l + 1}, \ldots, a_r) - \min (a_l, a_{l + 1}, \ldots, a_r) - (r - l)
$$
有 $q$ 次修改，在第一次修改前和每一次修改 $a_p \gets x$ 后，求对于所有 $1 \le l \le r \le n$，$f(l,r)$ 的最大值。

## 分析

为了让以上值最大区间长度一定不能浪费，所以能取最大值的只可能有两种情况：

1. $a_l$ 最小，$a_r$ 最大，表达式为 $(a_r - r) - (a_l - l)$。
2. $a_r$ 最小，$a_l$ 最大，表达式为 $(a_l + l) - (a_r + r)$。

所以直接用线段树分别维护 $a_i - i$ 和 $a_i + i$ 的最值即可。

具体操作见代码，时间复杂度 $O(n \log n)$。

## 代码

```cpp
//the code is from chenjh
#include<cstdio>
#include<algorithm>
#define MAXN 200002
#define lson (rt<<1)
#define rson (rt<<1|1)
using namespace std;
using ci=const int;
int n,q;
struct Node{
	//a_l + l - (a_r + r)
	//a_r - r - (a_l - l)
	int mx1,mx2,mn1,mn2,ans;// 1 表示 a_i + i，2 表示 a_i - i。
	Node operator + (const Node&A){//节点合并。
		Node ret;
		ret.mx1=max(mx1,A.mx1),ret.mx2=max(mx2,A.mx2);//对两个最大值取最大值。
		ret.mn1=min(mn1,A.mn1),ret.mn2=min(mn2,A.mn2);//对两个最小值取最小值。
		ret.ans=max({ans,A.ans,mx1-A.mn1,A.mx2-mn2});//两边的答案，以及 (a_l + l) - (a_r + r) 和 (a_r - r) - (a_l - l) 两种情况。
		return ret;
	}
}t[MAXN<<2];//线段树空间记得开 4 倍，要不然就会像我 RE on #7 遗憾离场。
int a[MAXN];
void bld(ci rt,ci l,ci r){
	if(l==r){t[rt].mx1=t[rt].mn1=a[l]+l,t[rt].mx2=t[rt].mn2=a[l]-l,t[rt].ans=0;return;}//线段树建树。
	int mid=(l+r)>>1;
	bld(lson,l,mid),bld(rson,mid+1,r);
	t[rt]=t[lson]+t[rson];
}
void upd(ci rt,ci l,ci r,ci p,ci v){//单点修改。
	if(l==r){a[l]=v,t[rt].mx1=t[rt].mn1=a[l]+l,t[rt].mx2=t[rt].mn2=a[l]-l,t[rt].ans=0;return;}
	int mid=(l+r)>>1;
	p<=mid?upd(lson,l,mid,p,v):upd(rson,mid+1,r,p,v);
	t[rt]=t[lson]+t[rson];
}
void solve(){
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	bld(1,1,n);
	printf("%d\n",t[1].ans);//直接查询全局最大值。
	for(int p,x;q--;){
		scanf("%d%d",&p,&x);
		upd(1,1,n,p,x);
		printf("%d\n",t[1].ans);
	}
}
int main(){
	int T;scanf("%d",&T);
	while(T--) solve(); 
	return 0;
}

```

---

## 作者：littlebug (赞：1)

唉果然还是一遇到 ds 就寄啊……

就这水题让我 Div.1+2 只过了 $3$ 题。

## Solution

首先很显然，当答案最大时，极值一定在两端（反证，如果不在两端的话，那一定可以从两边减少一些元素，使得 $\max(a_i) - \min(a_i)$ 不变但是 $r-l$ 变小）。然后分讨一下最小值和最大值在哪一边：

- 若最小值在左边，最大值在右边。原式可以转化为 $(a_r - a_l) - (r - l) = (a_l - l) - (a_r - r)$。
- 若最小值在右边，最大值在左边。原式可以转化为 $(a_l - a_r) - (r - l) = (a_l + l) - (a_r + r)$。

那如何求呢？想到上面的式子都是极值的形式，所以我们可以用线段树维护，具体地，分别维护 $a_i - i$ 和 $a_i + i$ 的最小值和最大值，再用一个 $ans$ 标记当前节点答案即可。

## Code

```cpp
class __segment_tree
{
#define lc v[pos<<1]
#define rc v[pos<<1|1]
#define lcp pos<<1
#define rcp pos<<1|1

private:

    int *a;
    struct node{int mx1,mn1,mx2,mn2,ans;} v[MAXN<<2];
    int p,x,lt,rt;

    il void pushup(int pos)
    {
        v[pos].mx1=max(lc.mx1,rc.mx1);
        v[pos].mn1=min(lc.mn1,rc.mn1);
        
        v[pos].mx2=max(lc.mx2,rc.mx2);
        v[pos].mn2=min(lc.mn2,rc.mn2);
        
        v[pos].ans=max({lc.ans,rc.ans,rc.mx1-lc.mn1,lc.mx2-rc.mn2});
    }

    il void build(int l,int r,int pos)
    {
        if(l==r) return v[pos]={a[l]-l,a[l]-l,a[l]+l,a[l]+l,0},void();
        int mid=l+r>>1;
        build(l,mid,lcp),build(mid+1,r,rcp);
        pushup(pos);
    }

    il void update(int l,int r,int pos)
    {
        if(l>=lt && r<=rt) return v[pos]={x-p,x-p,x+p,x+p,0},void();
        int mid=l+r>>1;
        mid>=lt && (update(l,mid,lcp),1);
        mid+1<=rt && (update(mid+1,r,rcp),1);
        pushup(pos);
    }

public:
    il void bui() {build(1,n,1);}
    il void bui(int *aa) {a=aa,build(1,n,1);}
    il void upd(int l,int r,int _p,int _x) {l>r && (swap(l,r),1); p=_p,x=_x,lt=l,rt=r; update(1,n,1);}
    il int q() {return v[1].ans;}

#undef lc
#undef rc
#undef lcp
#undef rcp
} tr;

il void solve(int __Ti)
{
    read(n,q),_::r(a,n);
    tr.bui(a);

    write(tr.q(),'\n');

    int p,x;
    while(q--)
    {
        read(p,x);
        tr.upd(p,p,p,x);
        write(tr.q(),'\n');
    }
}
```

---

## 作者：Drifty (赞：1)

### Preface

省流：用心感受，用脚维护。

### Solution

首先你会发现对于这个区间极差减区间长度有一个很典的结论，可以看这道题：[P8446 虹色的北斗七星](/problem/P8446)。

由那题的第一篇题解得知，我们只需要去维护 $b_i = a_i + i$ 和 $c_i = a_i - i$ 这两个序列中的 $\max\{b_i - b_j\}\ (i > j)$ 和 $\max\{c_j - c_i\}\ (i > j)$，这个线段树容易维护。

### Code

```cpp
#pragma GCC optimize(3, "Ofast")
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
constexpr int N = 2e5 + 7;
int T, n, q, a[N];
struct dat {int mx, mi, res;} tr1[N << 2], tr2[N << 2];
namespace Seg1 {
    #define tr tr1
    auto ls = [](int x) {return x << 1;};
    auto rs = [](int x) {return x << 1|1;};
    auto push_up = [](int x) {
        tr[x].mx = max(tr[ls(x)].mx, tr[rs(x)].mx);
        tr[x].mi = min(tr[ls(x)].mi, tr[rs(x)].mi);
        tr[x].res = max({tr[ls(x)].res, 
        tr[rs(x)].res, tr[rs(x)].mx - tr[ls(x)].mi});
    };
    void modify (int x, int d, int p, int pl, int pr) {
        if (pl == pr) {tr[p].mx = d, tr[p].mi = d, tr[p].res = 0; return ;}
        int mid = (pl + pr) >> 1;
        if (x <= mid) modify (x, d, ls(p), pl, mid);
        if (x > mid) modify (x, d, rs(p), mid + 1, pr);
        push_up(p);
    }
    #undef tr
}
namespace Seg2 {
    #define tr tr2
    auto ls = [](int x) {return x << 1;};
    auto rs = [](int x) {return x << 1|1;};
    auto push_up = [](int x) {
        tr[x].mx = max(tr[ls(x)].mx, tr[rs(x)].mx);
        tr[x].mi = min(tr[ls(x)].mi, tr[rs(x)].mi);
        tr[x].res = max({tr[ls(x)].res, 
        tr[rs(x)].res, tr[ls(x)].mx - tr[rs(x)].mi});
    };
    void modify (int x, int d, int p, int pl, int pr) {
        if (pl == pr) {tr[p].mx = d, tr[p].mi = d, tr[p].res = 0; return ;}
        int mid = (pl + pr) >> 1;
        if (x <= mid) modify (x, d, ls(p), pl, mid);
        if (x > mid) modify (x, d, rs(p), mid + 1, pr);
        push_up(p);
    }
    #undef tr
}
int query () {return max(tr1[1].res, tr2[1].res);}
void solve() {
    cin >> n >> q;
    for (int i = 1; i <= n; i ++) cin >> a[i];
    for (int i = 1; i <= 4 * n; i ++) tr1[i].mx = tr1[i].mi = tr1[i].res = 0;
    for (int i = 1; i <= 4 * n; i ++) tr2[i].mx = tr2[i].mi = tr2[i].res = 0;
    for (int i = 1; i <= n; i ++) Seg1::modify(i, a[i] - i, 1, 1, n);
    for (int i = 1; i <= n; i ++) Seg2::modify(i, a[i] + i, 1, 1, n);
    cout << query() << '\n';
    for (int i = 1; i <= q; i ++) {
        int p, x;
        cin >> p >> x;
        Seg1::modify(p, x - p, 1, 1, n);
        Seg2::modify(p, x + p, 1, 1, n);
        cout << query() << '\n';
    }
}
int32_t main() {
    cin.tie(NULL) -> sync_with_stdio(false);
    for (cin >> T; T --; ) solve();
    return 0;
}
```

---

## 作者：_Kamisato_Ayaka_ (赞：1)

[传送门](https://www.luogu.com.cn/problem/CF2057D)

## Statement

单点修改，全局查询所有 $[l,r]$ 中区间极差减去区间长度的最大值，多组数据。

## Solution

首先，如果区间的最大 / 最小值出现在区间中间，区间长度的改变并不会对其造成影响，反之，当最大值出现在区间左右端点时，区间长度改变可能会产生影响。

在保证区间最大 / 最小值存在于区间端点同时需要保证区间长度最小，这样为最优方案。

设区间最小值在右端点，最大值在左端点，答案：
$$
(a_l - a_r) - (r - l) = (a_l + l) - (a_r + r)
$$
最小值在左端点，最大值在右端，答案：
$$
(a_r - a_l) - (r - l) = (a_r - r) - (a_l - l)
$$

我们令 $x_i = a_i - i,y_i = a_i + i$，最后答案：

$$
\max\{\max_{l<r}\{x_r - x_l\},\max_{l<r}\{y_l - y_r\}\}
$$

区间最大 / 最小值可以拿线段树维护，然后再维护一个答案即可。

## code

[Submission](https://codeforces.com/contest/2057/submission/299834374)

---

## 作者：Jorisy (赞：1)

注意到最大化这个式子那么最大最小值一定是 $a_l$ 或 $a_r$。

那么原式可以讨论一下：
- 若 $a_l<a_r$，则原式 $=a_r-a_l-r+l=(a_r-r)-(a_l-l)$；
- 若 $a_l>a_r$，则原式 $=a_l-a_r-r+l=(a_l+l)-(a_r+r)$。

开两棵线段树分别维护 $a_i\pm i$ 即可。

---

## 作者：Magallan_forever (赞：0)

#### 简要说明题意：

给出一个有 $n$ 个元素的数组 $a$ 和 $q$ 次查询，对于初始状态和每次查询结束后的状态，求 $\max\{a_l,a_{l+1},\dots,a_{r-1},a_r\}-\min\{a_l,a_{l+1},\dots,a_{r-1},a_r\}-(r-l)$ 的最大值，其中 $1 \leq l \leq r \leq n$。

#### 题目分析：

应该不难想到，$l,r$ 一定是区间的两个最值，可以用反证法证明。

那么我们可以把后面的 $r-l$ 这一项整合进前面的式子。

如果最大值在最小值的右边，那就等价于 $b_i=a_i-i$ 求全局的 $\max\{b_r-b_l\} \quad (1 \leq l \leq r \leq n)$。最大值在最小值左边的情况也同理，$b_i=a_i+i$，求全局的 $\max\{b_l-b_r\} \quad (1 \leq l \leq r \leq n)$。

考虑到最大值不是在最小值左边就是右边（重合的情况两个式子都可以考虑到），所以我们同时维护两种情况，然后求两种情况的最大即可。

那么现在问题来了，要怎么维护这个带了一点条件（即最大在最小的右/左边）的极值？我们不能直接维护最大/最小，但我们如果已知两个区间的最大值，最小值和答案，我们可以合并成一个区间，这个过程就是线段树的 `push_up` 操作。

给出类似的题目：[CF527C](https://codeforces.com/problemset/problem/527/C) 和 [SPOJGSS3](https://www.spoj.com/problems/GSS3/en/)。用线段树维护区间的答案，最大/最小值。然后在 `push_up` 操作里维护。

具体看代码吧：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int a[200001],c[200001];
struct node{
    int l,r;
    long long min,max,cnt;
    node(int l_=-1,int r_=-1,long long min_=1.3e9,long long max_=-1.3e9,long long cnt_=0ll) :l(l_),r(r_),min(min_),max(max_),cnt(cnt_) {}
}tree0[800001],tree1[800001];
node push_up_tree0(node l,node r){
    node temp(l.l,r.r);
    temp.min=min(l.min,r.min);
    temp.max=max(l.max,r.max);
    temp.cnt=max(l.cnt,r.cnt);
    temp.cnt=max(temp.cnt,r.max-l.min);
    return temp;
}
node push_up_tree1(node l,node r){
    node temp(l.l,r.r);
    temp.min=min(l.min,r.min);
    temp.max=max(l.max,r.max);
    temp.cnt=max(l.cnt,r.cnt);
    temp.cnt=max(temp.cnt,l.max-r.min);
    return temp;
}
auto push_up=push_up_tree0;
void build(node* tree,int p,int l,int r,node push_up(node,node)){ //这个是函数指针，如果你是OI选手，这个和sort传cmp一样
    tree[p]=node(l,r);
    if(l==r) tree[p].min=tree[p].max=c[l];
    else build(tree,p<<1,l,(l+r)>>1,push_up),build(tree,(p<<1)|1,((l+r)>>1)+1,r,push_up),tree[p]=push_up(tree[p<<1],tree[(p<<1)|1]);
}
void modify(node* tree,int p,int x,int v,node push_up(node,node)){
    // printf("p=%d tree[p].l=%d tree[p].r=%d x=%d\n",p,tree[p].l,tree[p].r,x);
    if(tree[p].l==tree[p].r&&tree[p].l==x){
        tree[p].max=tree[p].min=v;
        return;
    }
    int mid=(tree[p].l+tree[p].r)>>1;
    if(x<=mid) modify(tree,p<<1,x,v,push_up);
    else modify(tree,(p<<1)|1,x,v,push_up);
    tree[p]=push_up(tree[p<<1],tree[(p<<1)|1]);
}
node query(node* tree,int p,int l,int r,node push_up(node,node)){ //答案合并和push_up的流程完全一样
    if(tree[p].l<=l&&tree[p].r<=r) return tree[p];
    int mid=(tree[p].l+tree[p].r)>>1;
    if(l<=mid&&mid<=r) return push_up(query(tree,p<<1,l,r,push_up),query(tree,(p<<1)|1,l,r,push_up));
    if(l<=mid) return query(tree,p<<1,l,r,push_up);
    return query(tree,(p<<1)|1,l,r,push_up);
}
int main(){
    int T,n,q,x,y;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&q);
        for(int i=1;i<=n;++i) scanf("%d",a+i),c[i]=a[i]-i;
        build(tree0,1,1,n,push_up_tree0);
        for(int i=1;i<=n;++i) c[i]=a[i]+i;
        build(tree1,1,1,n,push_up_tree1);
        printf("%lld\n",max(query(tree0,1,1,n,push_up_tree0).cnt,query(tree1,1,1,n,push_up_tree1).cnt));
        while(q--){
            scanf("%d%d",&x,&y);
            modify(tree0,1,x,y-x,push_up_tree0),modify(tree1,1,x,y+x,push_up_tree1);
            printf("%lld\n",max(query(tree0,1,1,n,push_up_tree0).cnt,query(tree1,1,1,n,push_up_tree1).cnt));
        }
    }
    return 0;
}
```

---

## 作者：YFffffffff (赞：0)

### 题解：D. Gifts Order

这道题要求在数组中选择子区间 $[l, r]$，使便利值 $\max(a_l, \dots, a_r) - \min(a_l, \dots, a_r) - (r - l)$ 最大化，并处理初始状态及 $q$ 次修改后的结果。直接枚举所有 $[l, r]$ 的复杂度为 $O(n^2)$，无法满足 $n, q \leq 2 \times 10^5$ 的时间限制，因此需要优化。

我们通过定义两个新数组来简化计算：$b[i] = a[i] - i$ 和 $c[i] = a[n-i+1] - (n - i + 1)$ ，分别用于考虑左端更大的情况和右端点更加大的情况。便利值可以看作 $\max(a_l - l, \dots, a_r - r) - \min(a_l - l, \dots, a_r - r)$，这启发我们用线段树维护区间信息。构建两棵线段树：一棵基于 $b[i]$ 维护从左到右的最大值和最小值，另一棵基于 $c[i]$ 维护从右到左的相关信息。每棵树节点记录区间最大值 $maxv$、最小值 $minv$ 和最大便利值 $ans$（考虑子区间或当前区间的 $maxv - minv$ 。

初始时，建树复杂度为 $O(n)$，将 $a[i]$ 转化为 $b[i]$ 和 $c[i]$ 存入两棵树。对于每次修改，更新位置 $p$ 在第一棵树的 $val - p$ 和第二棵树的 $val - (n - p + 1)$，复杂度 $O(\log n)$。便利值通过比较两棵树根节点的 $ans$ 取最大值。总复杂度为 $O(n + q \log n)$ ，满足时间要求。

```cpp
#include"bits/stdc++.h"
using namespace std;
#define int long long
struct node
{
	int val;
	int l,r;
	int minv=0x3f3f3f3f3f3f,maxv=-0x3f3f3f3f3f3f;
	int ans=0;
};
vector<node>a[2];///a[0]相当于b a[1]相当于c
void build(int u,int l,int r,vector<node>&tr)
{
	tr[u].l=l;
	tr[u].r=r;
	if(l==r)return;
	int mid=tr[u].r+tr[u].l>>1;
	build(2*u,l,mid,tr);
	build(2*u+1,mid+1,r,tr);
	return;
}

void modify(int u,int pos,int val,vector<node>&tr)
{
	if(tr[u].l==tr[u].r)
	{
		tr[u].minv=val;
		tr[u].maxv=val;
		return;
	}
	int ls=u*2;
	int rs=2*u+1;
	int mid=tr[u].l+tr[u].r>>1;
	if(pos<=mid)
	{
		modify(ls,pos,val,tr);
	}
	else
	{
		modify(rs,pos,val,tr);
	}
	tr[u].minv=min(tr[ls].minv,tr[rs].minv);
	tr[u].maxv=max(tr[ls].maxv,tr[rs].maxv);
	tr[u].ans=tr[rs].maxv-tr[ls].minv;
	tr[u].ans=max(tr[u].ans,tr[ls].ans);
	tr[u].ans=max(tr[u].ans,tr[rs].ans);
	return;
}

void sol()
{
	int n,q;
	cin>>n>>q;
	a[0].clear();
	a[1].clear();
	a[0].resize(4*n+1);
	a[1].resize(4*n+1);
	build(1,1,n,a[1]);
	build(1,1,n,a[0]);
	for(int i=1;i<=n;i++)
	{
		int x;
		cin>>x;
		modify(1,i,x-i,a[0]);
		modify(1,n-i+1,x-(n-i+1),a[1]);
	}
	int res=max(a[1][1].ans,a[0][1].ans);
	cout<<res<<endl;
	while(q--)
	{
		int pos,val;
		cin>>pos>>val;
		modify(1,pos,val-pos,a[0]);
		modify(1,n-pos+1,val-(n-pos+1),a[1]);
		int res=max(a[1][1].ans,a[0][1].ans);
		cout<<res<<endl;
	}
}
signed main(void)
{
	int t;cin>>t;
	while(t--)
	sol();
	return 0;
}

```

---

## 作者：wfc284 (赞：0)

似乎是一个很典的套路。  
我们注意到**一个区间成为答案时，最值一定在端点处**。  
（如果不是，那么收缩一个一定更优）  
于是我们就可以按照最值位置分类。

- 最大值在区间左边，最小值在区间右边：答案就是 $(a_l + l) - (a_r + r)$。
- 最大值在区间右边，最小值在区间左边：答案就是 $(a_r - r) - (a_l - l)$。

我们直接线段树维护 $a_i + i$ 的最值和 $a_i - i$ 的最值即可。  

Q：算出来的和原式不等价，为什么是对的？  
A：算的过程中相当于多包含了一些劣的情况，但是在取 $\max$ 的过程中自动舍掉了，于是是对的。

```cpp
#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
#define Linf 0x3f3f3f3f3f3f3f3f
#define pii pair<int, int> 
#define all(v) v.begin(), v.end()
using namespace std;

//#define filename "xxx" 
#define FileOperations() freopen(filename".in", "r", stdin), freopen(filename".out", "w", stdout)
#define multi_cases 1

namespace Traveller {
	const int N = 2e5+2;
	
	int n, q, a[N];
	
	struct data {
		int mx1, mx2, mn1, mn2;
		int ans;
		data() { }
		data(int a, int b, int c, int d, int e = 0) : mx1(a), mx2(b), mn1(c), mn2(d), ans(e) { }
	};
	data operator + (data a, data b) {
		int ans = max(max(a.ans, b.ans), max(a.mx1 - b.mn1, b.mx2 - a.mn2));
		int mx1 = max(a.mx1, b.mx1);
		int mx2 = max(a.mx2, b.mx2);
		int mn1 = min(a.mn1, b.mn1);
		int mn2 = min(a.mn2, b.mn2);
		return data(mx1, mx2, mn1, mn2, ans);
	}
	data operator + (data a, int b) {
		int mx1 = a.mx1 + b;
		int mx2 = a.mx2 + b;
		int mn1 = a.mn1 + b;
		int mn2 = a.mn2 + b;
		return data(mx1, mx2, mn1, mn2);
	}
	
	class SegmentTree {
		public:
			struct node {
				node *l, *r;
				data d;
				void up() { d = l->d + r->d; }
			} pool[N << 1], *tmp, *root;
			
			node *newnode() {
				tmp->l = tmp->r = NULL;
				tmp->d = data();
				return tmp++;
			}
			
			int l, r;
			
		public:
			void build(node *&p, int l, int r, int *a) {
				p = newnode();
				if(l == r) {
					p->d = data(a[l] + l, a[l] - l, a[l] + l, a[l] - l);
					return;
				}
				int mid = l + r >> 1;
				build(p->l, l, mid, a);
				build(p->r, mid+1, r, a);
				p->up();
			}
			void update(node *p, int l, int r, int idx, int v, int *a) {
				if(l == r) {
					p->d = p->d + (v - a[l]);
					a[l] = v;
					return;
				}
				int mid = l + r >> 1;
				if(mid >= idx) update(p->l, l, mid, idx, v, a);
				else update(p->r, mid+1, r, idx, v, a);
				p->up();
			}
			int query() { return root->d.ans; }
			
			void build(int l, int r, int *a) {
				tmp = pool;
				this->l = l, this->r = r;
				build(root, l, r, a);
			}
			void update(int idx, int v, int *a) { update(root, l, r, idx, v, a); }
	} tr;
	
	void main() {
		cin >> n >> q;
		for(int i = 1; i <= n; ++i) scanf("%d", &a[i]);
		tr.build(1, n, a);
		printf("%d\n", tr.query());
		for(int i = 1, idx, v; i <= q; ++i) {
			scanf("%d%d", &idx, &v);
			tr.update(idx, v, a);
			printf("%d\n", tr.query());
		}
	}
}

signed main() {
#ifdef filename
	FileOperations();
#endif
	
	signed _ = 1;
#ifdef multi_cases
	scanf("%d", &_);
#endif
	while(_--) Traveller::main();
	return 0;
}


```

---

## 作者：shicj (赞：0)

## 0x00 题目翻译

一个长度为 $n$ 的序列，求出对于所有 $1\le l\le r\le n$，

$$
\max (a_l, a_{l + 1}, \ldots, a_r) - \min (a_l, a_{l + 1}, \ldots, a_r) - (r - l)
$$

的最大值。

每一组数据，先输出这个序列的答案，之后 $q$ 行修改操作，每行的 `p x` 表示把 $a_p$ 修改为 $x$，修改对之后的所有操作有影响，每一次修改后，输出新序列的答案。

## 0x01 解题思路

解题的关键就是对这个式子进行变形：

$$
\max (a_l, a_{l + 1}, \ldots, a_r) - \min (a_l, a_{l + 1}, \ldots, a_r) - (r - l)
$$

首先观察到，选取的最大最小值一定在区间的两端（如果不在两端，那么可以去掉左右无用的部分，答案一定更优），于是式子变为：

$$
\vert a_l-a_r\vert- (r - l)
$$

绝对值意味着分类讨论，因为这里要求的是最大值，所以可以简单地去掉绝对值后对两种情况取最值：

$$
\max\{a_l-a_r- (r - l),a_r-a_l- (r - l)\}
$$

发现 $(r-1)$ 是一个和序列无关的整体，这并不好处理，可以想到合并到序列（我是看了题解才想到的）：

$$
\max\{(a_l+l)-(a_r+r),(a_r-r)-(a_l-l)\}
$$

这样就可以使 $(l-r)$ 和序列成为一个整体，为了方便表示和处理，令 $x_i=a_i+i$，$y_i=a_i-i$，于是变为：

$$
\max\{x_l-x_r,y_r-y_l\}
$$

这个时候就可以开始求答案了。

---

看到区间和修改，想到了线段树和区间DP，可以尝试结合这两者解决问题。

首先，对于题目的修改，想到用线段树去维护 $x$ 和 $y$ 两个序列，然后想怎样在线段树的合并（建树）中完成答案的求解。

线段树在建立的过程中不断合并左右两个子区间，求解也是类似的，每一次维护 $ans_1=x_l-x_r$，$ans_2=y_r-y_l$，结果就是 $\max\{ans_1,ans_2\}$，但还没有这么简单，接下来对区间进行讨论：

- 答案出现在左区间，直接取出计算完的数值；
- 答案出现在右区间，直接取出计算完的数值；
- 答案取自左区间和右区间，计算新的答案。

得出方程（符号表示有点混乱，具体看代码）：

$$
ans_{1_\text{now}}=\max\{ans_{1_l},ans_{1_r},x_{l_\text{max}}-x_{r_\text{max}}\}
\\
ans_{2_\text{now}}=\max\{ans_{2_l},ans_{2_r},y_{r_\text{max}}-y_{2_\text{max}}\}
$$

在线段树的 `pushup` 中完成计算就可以了。

## 0x02 算法实现

单点修改+区间查询，有不带懒标记的线段树直接实现即可。

## 0x03 程序代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct SegmentTree{
	struct data{
		int X,Y;
		//X:-i Y:+i
	};
	data dat[200005];
	struct node{
		int l,r,minX,minY,maxX,maxY,ansA,ansB;
	};
	node t[4*200005];
	void pushup(int x){
		t[x].minX=min(t[x<<1].minX,t[x<<1|1].minX);
		t[x].minY=min(t[x<<1].minY,t[x<<1|1].minY);
		t[x].maxX=max(t[x<<1].maxX,t[x<<1|1].maxX);
		t[x].maxY=max(t[x<<1].maxY,t[x<<1|1].maxY);
		t[x].ansA=max({t[x<<1].ansA,t[x<<1|1].ansA,t[x<<1|1].maxX-t[x<<1].minX});
		t[x].ansB=max({t[x<<1].ansB,t[x<<1|1].ansB,t[x<<1].maxY-t[x<<1|1].minY});
	}
	void build(int x,int l,int r){
		t[x].l=l,t[x].r=r;
		if(l==r){
			t[x].minX=t[x].maxX=dat[l].X;
			t[x].minY=t[x].maxY=dat[l].Y;
			t[x].ansA=t[x].ansB=0;
			return;
		}
		int mid=l+r>>1;
		build(x<<1,l,mid);
		build(x<<1|1,mid+1,r);
		pushup(x);
	}
	void update(int x,int X){
		int l=t[x].l,r=t[x].r;
		if(l==r){
			t[x].minX=t[x].maxX=dat[l].X;
			t[x].minY=t[x].maxY=dat[l].Y;
			return;
		}
		int mid=l+r>>1;
		if(X<=mid)update(x<<1,X);
		else update(x<<1|1,X);
		pushup(x);
	}
	int query(){
		return max(t[1].ansA,t[1].ansB);
	}
}SegTree;
int n,q,p,v;
void solve(){
	scanf("%lld%lld",&n,&q);
	for(int i=1;i<=n;i++){
		scanf("%lld",&v);
		SegTree.dat[i]={v-i,v+i};
	}
	SegTree.build(1,1,n);
	printf("%lld\n",SegTree.query());
	for(int i=1;i<=q;i++){
		scanf("%lld%lld",&p,&v);
		SegTree.dat[p]={v-p,v+p};
		SegTree.update(1,p);
		printf("%lld\n",SegTree.query());
	}
}
signed main(){
#ifdef USE_FILE_IO
	freopen("code.in","r",stdin);
	freopen("code.out","w",stdout);
#endif
	int t;
	cin>>t;
	while(t--){
		solve();
	}
	return 0;
}
```

![](https://cdn.luogu.com.cn/upload/image_hosting/nqs8d3re.png)

$$
\color{green}\text{Happy New Year!}
$$

---

## 作者：_O_w_O_ (赞：0)

类似的题目：[P8446 虹色的北斗七星
](/problem/P8446)，虽然两题要用的的算法不一样但是大致思路相同。碰巧的是，Good bye 2024 恰好是 
Cocoly Round 而本题出现在 Hello 2025 中。

我们注意到 $\max_{i=l}^r a_i$ 与 $\min_{i=l}^r a_i$ 分别为 $a_l$ 和 $a_r$，因为当区间两边不是最值时，区间可以往内缩这样 $\max-\min$ 不仅不会减少 $-(r-l)$ 还可以增加。

根据上述结论，我们又发现当 $a_l=\max_{i=l}^r a_i$ 时，答案为 $a_l-a_r-(r-l)=(a_l+l)-(a_r+r)$，否则，答案为 $a_r-a_l-(r-l)=(a_r-r)-(a_l-l)$。

那么我们直接拿线段树来维护区间内的以下四个信息：

- $tag1=\max\{a_i-i\}$；
- $tag2=\min\{a_i-i\}$；
- $tag3=\max\{a_i+i\}$；
- $tag4=\min\{a_i+i\}$。

那么单点修改是简单的，所以每次修改后答案为根节点的 $\max\{tag1-tag2,tag3-tag4\}$。

code：


```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=2e5+5;
int n,q,a[N];
struct seg{
#define ls(x) x<<1
#define rs(x) x<<1|1
	struct tree{
		int l,r;
		int mx1,mn1,mx2,mn2,ans;
	}tr[N<<2];
	void up(int u){
		tr[u].ans=max(tr[ls(u)].ans,tr[rs(u)].ans);
		tr[u].mx1=max(tr[ls(u)].mx1,tr[rs(u)].mx1);
		tr[u].mn1=min(tr[ls(u)].mn1,tr[rs(u)].mn1);
		tr[u].ans=max(tr[u].ans,tr[ls(u)].mx1-tr[rs(u)].mn1);
		tr[u].mx2=max(tr[ls(u)].mx2,tr[rs(u)].mx2);
		tr[u].mn2=min(tr[ls(u)].mn2,tr[rs(u)].mn2);
		tr[u].ans=max(tr[u].ans,tr[rs(u)].mx2-tr[ls(u)].mn2);
	}
	void build(int id,int l,int r){
		tr[id].l=l,tr[id].r=r;
		if(l==r){
			tr[id].ans=0;
			tr[id].mx1=tr[id].mn1=a[l]+l;
			tr[id].mx2=tr[id].mn2=a[l]-l;
			return;
		}
		int mid=l+r>>1;
		build(ls(id),l,mid),build(rs(id),mid+1,r);
		up(id);
	}
	void change(int id,int x,int y){
		if(tr[id].l==tr[id].r){
			tr[id].mx1=tr[id].mn1=y+x;
			tr[id].mx2=tr[id].mn2=y-x;
			return;
		}
		int mid=tr[id].l+tr[id].r>>1;
		if(x<=mid) change(ls(id),x,y);
		else change(rs(id),x,y);
		up(id);
	}
}tr;

signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int T;cin>>T;while(T--){
		cin>>n>>q;
		for(int i=1;i<=n;i++) cin>>a[i];
		tr.build(1,1,n);
		cout<<tr.tr[1].ans<<endl;
		while(q--){
			int x,y;
			cin>>x>>y;
			tr.change(1,x,y);
			cout<<tr.tr[1].ans<<endl;
		}
//		cout<<endl;
	}
	return 0;
}
```

---

## 作者：zhangxiao666 (赞：0)

[P8846](https://www.luogu.com.cn/problem/P8446) 的加强版。

考虑最优的区间极值一定位于左右端点（否则可以将区间缩小使其更优）。则可将原式转化为 $a_r-a_l-(r-l)$ 或 $a_l-a_r-(r-l)$。即 $(a_r-r)-(a_l-l)$ 或 $(a_l+l)-(a_r+r)$。显然维护 $a_i+i$ 和 $a_i-i$ 的极值，单点修改，全局最大，采用线段树维护即可。


```cpp
#include <bits/stdc++.h>
#define dbg(x) cout << #x << '=' << x << endl
#define rep(i, l, r) for (int i = (l); i <= (r); i++)
#define frep(i, r, l) for (int i = (r); i >= (l); i--)
//#define int long long
using namespace std;

const int N = 2e5 + 10;

int n, q;
int a[N];

namespace SgT
{
    struct node
    {
        int ans, max1, min1, max2, min2;
    } tr[N << 2];

    #define ls x << 1
    #define rs x << 1 | 1
    #define lson ls, l, mid
    #define rson rs, mid + 1, r    

    void PushUp(int x)
    {
        tr[x].ans = max(tr[ls].ans, tr[rs].ans);
        tr[x].max1 = max(tr[ls].max1, tr[rs].max1);
        tr[x].min1 = min(tr[ls].min1, tr[rs].min1);
        tr[x].ans = max(tr[x].ans, tr[ls].max1 - tr[rs].min1);
        tr[x].max2 = max(tr[ls].max2, tr[rs].max2);
        tr[x].min2 = min(tr[ls].min2, tr[rs].min2);
        tr[x].ans = max(tr[x].ans, tr[rs].max2 - tr[ls].min2);
        return;
    }

    void Change(int x, int k, int p)
    {
        tr[x].ans = 0;            
        tr[x].min1 = tr[x].max1 = k + p;
        tr[x].min2 = tr[x].max2 = k - p;        
    }

    void Build(int x, int l, int r)
    {
        if (l == r)
        {
            Change(x, a[l], l);
            return;
        }
        int mid = l + r >> 1;
        Build(lson), Build(rson);
        PushUp(x);
    }
    void Update(int x, int l, int r, int p, int k)
    {
        if (l == r)
        {   
            Change(x, k, p);
            return;
        }
        int mid = l + r >> 1;
        if (p <= mid)
            Update(lson, p, k);
        else
            Update(rson, p, k);
        PushUp(x);
    }    
}



void work()
{
    cin >> n >> q;
    rep(i, 1, n) cin >> a[i];
    SgT::Build(1, 1, n);
    cout << SgT::tr[1].ans << "\n";
    while (q--)
    {
        int p, x;
        cin >> p >> x;
        SgT::Update(1, 1, n, p, x);
        cout << SgT::tr[1].ans << "\n";
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1, opinput = 1;
    if (opinput) cin >> T;
    while (T--) work();
    return 0;
}
```

---

## 作者：_xguagua_Firefly_ (赞：0)

### 分析

首先，在最大值和最小值不变的情况，区间长度应该尽可能的小，否则答案不会更优。因此，在最优的情况下，区间最大最小值只可能出现在端点处。我们先假设 $a _ r$ 为区间的最大值，$a _ l$ 为区间的最小值，且 $l \le r$，则答案为 $a _ r - a _ l - (r - l) = (a _ r - r) - (a _ l - l)$。因此，我们可以考虑用数据结构来维护 $a _ i - i$ 的信息。

我们建棵线段树，维护区间内 $a _ i - i$ 的最大值、最小值与该子区间的答案。最大值最小值很好维护，而答案为右儿子的最大值减去左儿子的最小值、左儿子的答案、右儿子的答案三者取最大值。如果是叶子节点，则答案显然为 $0$。

但是这样可能会有遗漏，因为最大值不一定在右侧，最小值也不一定在左侧。所以，我们考虑再维护一个 $a _ i - (n - i)$，也就是维护一个翻转的序列。按上述方法维护最大值与最小值，因为维护的序列翻转了，所以答案为左儿子最大值减右儿子的最小值、左右儿子的答案取最大值。对于一个询问，我们回答正向的答案与逆向的答案中的最大值就行了。

### Code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

constexpr int MAXN = 2e5 + 24;
int T,n,q,a[MAXN],p,x;
struct Rukkhadevata
{
    int l,r,min,max,ans,rmin,rmax,rans;
}tree[MAXN << 2];
void pushup(int rt)
{
    tree[rt].min = min(tree[rt << 1].min,tree[rt << 1 | 1].min);
    tree[rt].max = max(tree[rt << 1].max,tree[rt << 1 | 1].max);
    tree[rt].ans = max(tree[rt << 1 | 1].max - tree[rt << 1].min,max(tree[rt << 1].ans,tree[rt << 1 | 1].ans));
    tree[rt].rmin = min(tree[rt << 1].rmin,tree[rt << 1 | 1].rmin);
    tree[rt].rmax = max(tree[rt << 1].rmax,tree[rt << 1 | 1].rmax);
    tree[rt].rans = max(tree[rt << 1].rmax - tree[rt << 1 | 1].rmin,max(tree[rt << 1].rans,tree[rt << 1 | 1].rans));
}
void build(int l,int r,int rt)
{
    tree[rt].l = l,tree[rt].r = r;
    if(l == r)
    {
        tree[rt].min = tree[rt].max = a[l] - l;
        tree[rt].rmin = tree[rt].rmax = a[l] - n + l;
        tree[rt].ans = tree[rt].rans = 0;
        return ;
    }
    int mid = (l + r) >> 1;
    build(l,mid,rt << 1);
    build(mid + 1,r,rt << 1 | 1);
    pushup(rt);
}
void modify(int l,int r,int rt,int val)
{
    if(l <= tree[rt].l && r >= tree[rt].r)
    {
        tree[rt].min = tree[rt].max = val - l;
        tree[rt].rmin = tree[rt].rmax = val - n + l;
        return ;
    }
    int mid = (tree[rt].l + tree[rt].r) >> 1;
    if(l <= mid)
        modify(l,r,rt << 1,val);
    if(r > mid)
        modify(l,r,rt << 1 | 1,val);
    pushup(rt);
}
signed main()
{
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin >> T;
    while(T--)
    {
        cin >> n >> q;
        for(int i = 1;i <= n;i++)
            cin >> a[i];
        build(1,n,1);
        cout << max(tree[1].ans,tree[1].rans) << "\n";
        while(q--)
        {
            cin >> p >> x;
            modify(p,p,1,x);
            cout << max(tree[1].ans,tree[1].rans) << "\n";
        }
    }
}
```

---

## 作者：_anll_ (赞：0)

## 思路
先讲一种比较石山的想法。

之前做过一道比较[类似的题](https://www.luogu.com.cn/problem/P7402)，是将原数组转成差分数组后操作，于是就自然而然地想偏了。其实本题差分数组也不是不能做，就是比较麻烦。具体地，我们分别记录它的前/后缀和以及它们分别的长度，合并的时候暴力分类讨论。但由于差分数组会有正负，一并而论会出问题，所以还需要分开存储，分别表示为正时的最大贡献、为负时最大贡献。

后来学习了一下，得到了另外一种更优的想法。考虑在原数组上直接操作，发现两个端点一定是 $minn$ 或 $maxn$，否则可以考虑往中间移使 $r-l$ 更小。不妨枚举一下情况：若 $num_l<num_r$，则贡献为 $num_r-num_l-r+l$；否则为 $num_l-num_r-r+l$。考虑将同时含有 $r$ 或 $l$ 的项合并，则第一种情况变成 $(num_r-r)-(num_l-l)$，第二种情况变成 $(num_l+l)-(num_r+r)$。于是我们只用维护区间 $num_x-x$、$num_x+x$ 就好了。

## 代码
差分数组：
```cpp
#include<cmath>
#include<iostream>
#define lc p<<1
#define rc p<<1|1
#define int long long
#define mid (tr[p].l+tr[p].r)/2
using namespace std;
const int N=2e6+5;
struct Tr{
	int l,r,slen,sum,maxn,qzh[2],qlen[2],hzh[2],hlen[2];
}tr[N];
int t,n,q,num[N],dif[N];
void pushup(int p){
	tr[p].sum=tr[lc].sum+tr[rc].sum;
	tr[p].qzh[0]=tr[lc].qzh[0],tr[p].qzh[1]=tr[lc].qzh[1];
	tr[p].qlen[0]=tr[lc].qlen[0],tr[p].qlen[1]=tr[lc].qlen[1];
	tr[p].hzh[0]=tr[rc].hzh[0],tr[p].hzh[1]=tr[rc].hzh[1];
	tr[p].hlen[0]=tr[rc].hlen[0],tr[p].hlen[1]=tr[rc].hlen[1];
	tr[p].maxn=max(tr[lc].maxn,tr[rc].maxn);
	for(int i=0;i<2;i++){
		for(int j=0;j<2;j++){
			int x=tr[lc].sum+tr[rc].qzh[j],
				len=tr[lc].slen+tr[rc].qlen[j];
			if(x>0){
				if(x-len>tr[p].qzh[0]-tr[p].qlen[0])
					tr[p].qzh[0]=x,tr[p].qlen[0]=len;
			}
			else{
				if(-x-len>-tr[p].qzh[1]-tr[p].qlen[1])
					tr[p].qzh[1]=x,tr[p].qlen[1]=len;
			}
			
			x=tr[lc].hzh[i]+tr[rc].sum,
			len=tr[lc].hlen[i]+tr[rc].slen;
			if(x>0){
				if(x-len>tr[p].hzh[0]-tr[p].hlen[0])
					tr[p].hzh[0]=x,tr[p].hlen[0]=len;
			}
			else{
				if(-x-len>-tr[p].hzh[1]-tr[p].hlen[1])
					tr[p].hzh[1]=x,tr[p].hlen[1]=len;
			}
			tr[p].maxn=max(tr[p].maxn,
						abs(tr[lc].hzh[i]+tr[rc].qzh[j])-tr[lc].hlen[i]-tr[rc].qlen[j]);
		}
	}
}
void build(int l,int r,int p){
	tr[p]={l,r,r-l+1};
	if(l==r){
		tr[p].sum=tr[p].maxn=
		tr[p].qzh[0]=tr[p].qzh[1]=
		tr[p].hzh[0]=tr[p].hzh[1]=dif[l];
		tr[p].qlen[0]=tr[p].qlen[1]=
		tr[p].hlen[0]=tr[p].hlen[1]=1;
		if(dif[l]<0)
			tr[p].qzh[0]=tr[p].hzh[0]=0,
			tr[p].qlen[0]=tr[p].hlen[0]=0;
		else
			tr[p].qzh[1]=tr[p].hzh[1]=0,
			tr[p].qlen[1]=tr[p].hlen[1]=0;
		if(tr[p].maxn<0) tr[p].maxn=-tr[p].maxn;
		tr[p].maxn--;
		return;
	}
	build(l,mid,lc);build(mid+1,r,rc);
	pushup(p);
}
void update(int a,int p){
	if(tr[p].l==tr[p].r){
		tr[p].sum=tr[p].maxn=
		tr[p].qzh[0]=tr[p].qzh[1]=
		tr[p].hzh[0]=tr[p].hzh[1]=dif[a];
		tr[p].qlen[0]=tr[p].qlen[1]=
		tr[p].hlen[0]=tr[p].hlen[1]=1;
		if(dif[a]<0)
			tr[p].qzh[0]=tr[p].hzh[0]=0,
			tr[p].qlen[0]=tr[p].hlen[0]=0;
		else
			tr[p].qzh[1]=tr[p].hzh[1]=0,
			tr[p].qlen[1]=tr[p].hlen[1]=0;
		if(tr[p].maxn<0) tr[p].maxn=-tr[p].maxn;
		tr[p].maxn--;
		return;
	}
	if(a<=mid) update(a,lc);
	else update(a,rc);
	pushup(p);
}
void solve(){
	cin>>n>>q;int op,x;
	for(int i=1;i<=n;i++) cin>>num[i];
	if(n==1){
		cout<<"0\n";
		while(q--){cin>>op>>x;cout<<"0\n";}
		return;
	}
	for(int i=2;i<=n;i++) dif[i]=num[i]-num[i-1];
	build(2,n,1);cout<<max(0ll,tr[1].maxn)<<endl;
	while(q--){
		cin>>op>>x;num[op]=x;
		if(op>1){
			dif[op]=num[op]-num[op-1];
			update(op,1);
		}
		if(op+1<=n){
			dif[op+1]=num[op+1]-num[op];
			update(op+1,1);
		}
		cout<<max(0ll,tr[1].maxn)<<endl;
	}
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>t;while(t--) solve();
	return 0;
}
```

原数组：
```cpp
#include<cmath>
#include<iostream>
#define lc p<<1
#define rc p<<1|1
#define int long long
#define mid (tr[p].l+tr[p].r)/2
using namespace std;
const int N=2e6+5;
struct Tr{
	int l,r,sum,maxna,minna,maxnb,minnb;
}tr[N];
int t,n,q,num[N],dif[N];
void pushup(int p){
	tr[p].maxna=max(tr[lc].maxna,tr[rc].maxna);
	tr[p].minna=min(tr[lc].minna,tr[rc].minna);
	tr[p].maxnb=max(tr[lc].maxnb,tr[rc].maxnb);
	tr[p].minnb=min(tr[lc].minnb,tr[rc].minnb);
	tr[p].sum=max(tr[lc].maxnb-tr[rc].minnb,tr[rc].maxna-tr[lc].minna);
	tr[p].sum=max(tr[p].sum,max(tr[lc].sum,tr[rc].sum));
}
void build(int l,int r,int p){
	tr[p]={l,r};
	if(l==r){
		tr[p].maxna=tr[p].minna=num[l]-l;
		tr[p].maxnb=tr[p].minnb=num[l]+l;
		return;
	}
	build(l,mid,lc);build(mid+1,r,rc);
	pushup(p);
}
void update(int a,int p){
	if(tr[p].l==tr[p].r){
		tr[p].maxna=tr[p].minna=num[a]-a;
		tr[p].maxnb=tr[p].minnb=num[a]+a;
		return;
	}
	if(a<=mid) update(a,lc);
	else update(a,rc);
	pushup(p);
}
void solve(){
	cin>>n>>q;int op,x;
	for(int i=1;i<=n;i++) cin>>num[i];
	build(1,n,1);
	cout<<max(0ll,tr[1].sum)<<endl;
	while(q--){
		cin>>op>>x;num[op]=x;
		update(op,1);
		cout<<max(0ll,tr[1].sum)<<endl;
	}
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>t;while(t--) solve();
	return 0;
}
```

---

