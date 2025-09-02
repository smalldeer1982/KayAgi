# The Bakery

## 题目描述

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF833B/f46eccace96d929fa4c99a2b4ae6e89027b73fa1.png)Some time ago Slastyona the Sweetmaid decided to open her own bakery! She bought required ingredients and a wonder-oven which can bake several types of cakes, and opened the bakery.

Soon the expenses started to overcome the income, so Slastyona decided to study the sweets market. She learned it's profitable to pack cakes in boxes, and that the more distinct cake types a box contains (let's denote this number as the value of the box), the higher price it has.

She needs to change the production technology! The problem is that the oven chooses the cake types on its own and Slastyona can't affect it. However, she knows the types and order of $ n $ cakes the oven is going to bake today. Slastyona has to pack exactly $ k $ boxes with cakes today, and she has to put in each box several (at least one) cakes the oven produced one right after another (in other words, she has to put in a box a continuous segment of cakes).

Slastyona wants to maximize the total value of all boxes with cakes. Help her determine this maximum possible total value.

## 说明/提示

In the first example Slastyona has only one box. She has to put all cakes in it, so that there are two types of cakes in the box, so the value is equal to $ 2 $ .

In the second example it is profitable to put the first two cakes in the first box, and all the rest in the second. There are two distinct types in the first box, and three in the second box then, so the total value is $ 5 $ .

## 样例 #1

### 输入

```
4 1
1 2 2 1
```

### 输出

```
2
```

## 样例 #2

### 输入

```
7 2
1 3 3 1 4 4 4
```

### 输出

```
5
```

## 样例 #3

### 输入

```
8 3
7 7 8 7 7 8 1 7
```

### 输出

```
6
```

# 题解

## 作者：Styx (赞：56)

**这道题很好列出状态转移方程，dp[i][j]=max{dp[k][j-1]+cnt[k+1][i]}**

**dp[i][j]意为1~i之间分割j次所产生的最大值。cnt[i][j]表示i-j之间不同的颜色个数。**

**看到max可以考虑线段树优化，也就是如果我们有办法在O(logn)的时间内计算出cnt[i][j]的值就可以了，考虑一种颜色能够产生贡献的范围，为他上一次出现的位置到他当前的位置，产生贡献为1，可以使用线段树区间加，给pre[i]~i都加上1，从1到n进行枚举，逐渐进行上面的操作，每次换下一层的时候重构线段树，这样计算cnt[i][j]的复杂度就变成了logn的 orz**

**总复杂度是O(nklogn)，时限2500ms完全不虚~**

**代码如下**
```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define lson root<<1
#define rson root<<1|1 
using namespace std;

struct node
{
	int l,r,sum,lazy;
}tr[140010];
int dp[60][40000],pre[35010],pos[35010];

void init()
{
	memset(tr,0,sizeof(tr));
}

void push_up(int root)
{
	tr[root].sum=max(tr[lson].sum,tr[rson].sum);
}

void push_down(int root)
{
	tr[lson].sum+=tr[root].lazy;
	tr[lson].lazy+=tr[root].lazy;
	tr[rson].sum+=tr[root].lazy;
	tr[rson].lazy+=tr[root].lazy;
	tr[root].lazy=0;
}

void build(int root,int l,int r,int now)
{
	if(l==r)
	{
		tr[root].l=l;
		tr[root].r=r;
		tr[root].sum=dp[now][l-1];
		return ;
	}
	tr[root].l=l;
	tr[root].r=r;
	int mid=(l+r)>>1;
	build(lson,l,mid,now);
	build(rson,mid+1,r,now);
	push_up(root);
}

void update(int root,int l,int r,int val)
{
	if(tr[root].l==l&&tr[root].r==r)
	{
		tr[root].sum+=val;
		tr[root].lazy+=val;
		return ;
	}
	if(tr[root].lazy)
	{
		push_down(root);
	}
	int mid=(tr[root].l+tr[root].r)>>1;
	if(mid<l)
	{
		update(rson,l,r,val);
	}
	else
	{
		if(mid>=r)
		{
			update(lson,l,r,val);
		}
		else
		{
			update(lson,l,mid,val);
			update(rson,mid+1,r,val);
		}
	}
	push_up(root);
}

int query(int root,int l,int r)
{
	if(tr[root].l==l&&tr[root].r==r)
	{
		return tr[root].sum;
	}
	if(tr[root].lazy)
	{
		push_down(root);
	}
	int mid=(tr[root].l+tr[root].r)>>1;
	if(mid<l)
	{
		return query(rson,l,r);
	}
	else
	{
		if(mid>=r)
		{
			return query(lson,l,r);
		}
		else
		{
			return max(query(lson,l,mid),query(rson,mid+1,r));
		}
	}
}

int main()
{
	int n,k,t;
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&t);
		pre[i]=pos[t]+1;
		pos[t]=i;
	}
	for(int i=1;i<=k;i++)
	{
		init();
		build(1,1,n,i-1);
		for(int j=1;j<=n;j++)
		{
			update(1,pre[j],j,1);
			dp[i][j]=query(1,1,j);
		}
	}
	printf("%d\n",dp[k][n]);
}
```

---

## 作者：KevinYu (赞：52)

这道题是一道DP题。          
先贴上我的翻译（~~稍微比默认翻译优美一点~~）:
```
由于这道题来自CF，我提供一下翻译:
题目大意:
Slastyona开了一个蛋糕店，她发现把蛋糕装进盒子里可以盈利，且一个盒子里装的蛋糕种类越多，就可以卖的越贵。
题目规定一个盒子的价值为其中装蛋糕的种类。
她今天需要让k个盒子中被装上蛋糕，而且她的盒子不能为空。
装的蛋糕必须是取自一个连续的区间。
Slastyona希望最大化所有蛋糕盒的总价值。帮助她确定这个可能的最大值。
输入格式:
第一行包含两个正整数n,k，分别代表蛋糕的个数和盒子的个数。
第二行包含n个正整数，第i个数代表第i个蛋糕的类别

输出格式:
一个正整数，代表盒子的总价值。

范围:
保证n∈[1，35000]且为整数，k∈[1，min(n,50)]且为整数。
保证蛋糕的总种类数∈[1，n]且为整数。
```
翻译就到这里。         
这一题其实还是挺考验思维的，本题是一个典型的分组问题,使用区间动态规划求解(算法标签上没有写动规 orz)。    
我们先来定义一下f数组。       
由于我们只能取连续的区间，我们不妨定义```f[i][j]```为在i个盒子中装下1-j的所有蛋糕时的最大价值和。         
从这个定义中我们可以得出边界条件:       
```cpp
f[1][i]=col[1][i]
```
其中```col[i][j]```代表从i->j中的颜色种类和。    
为了得到状态转移方程，我们考虑一下在原有的基础上多切一刀的情况。         
```
我们设要分的那一刀的位置为k。
那么总价值的值就为f[j-1][k]+col[i][j]。
对于每一次更新j值，枚举每一个k，取其最大值，即为所求。
最终得转移方程:f[i][j]=max{f[j-1][k]+col[i][k+1]}
```
根据这个，我们就可以写出状态转移的程序了~~，这一题就结束了~~。       
结束了就好了，只可惜```n∈[1，35000]```，这么做要枚举两边n，一遍k，复杂度为```O(k*n^2)```，会直接爆炸。          
这个数据范围的话，我们需要优化掉一个log。    
怎么办呢?上线段树。      
在介绍这一题中线段树的写法之前，我们先探索一个东西:      
```cpp
哪一些点对我们的总价值是有益的呢?
```
实际上，一个点的有价值的范围可以仅由前一个与它同颜色的点决定。     
例:样例3(每一个颜色代表有效范围)
![](https://i.loli.net/2018/12/06/5c08deb35c5fd.jpg)       
所以我们用线段树来存储区间最值，然后就可以在```O(k*n*logn)```的时间内做完了。      
下面来过一遍算法流程:       
我们先记录下每一个点的有效范围:
```cpp
int main()
{
    int n,k,t;
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&t);
        pre[i]=pos[t]+1;
        pos[t]=i;
    }
```
然后对于每一个k值，我们都建立一次线段树。
```cpp
    for(int i=1;i<=k;i++)
    {
        memset(tr,0,sizeof(tr));
        build(1,1,n,i);
        for(int j=1;j<=n;j++)
        {
            update(1,pre[j],j,1);
            f[i][j]=query(1,1,j);
        }
    }
```
在这里面，我们发现，我们可以看作每一个颜色都可以“透过”分割线对后面的点产生影响:
![](https://i.loli.net/2018/12/06/5c08e2c4075cc.jpg)             
注意我们的build函数中，线段树的建树过程依赖于上一次dp。
```cpp
void build(int p,int l,int r,int now)
{
    if(l==r)
    {
        tr[p].l=l;
        tr[p].r=r;
        tr[p].val=f[now-1][l-1];
        return;
    }
    tr[p].l=l;
    tr[p].r=r;
    int mid=(l+r)>>1;
    build(ls(p),l,mid,now);
    build(rs(p),mid+1,r,now);
    push_up(p);
}
```
最后输出就行了。
```cpp
    printf("%d\n",f[k][n]);
	return 0;
}
```
完整程序:
```cpp
int main()
{
    int n,k,t;
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&t);
        pre[i]=pos[t]+1;
        pos[t]=i;
    }
    for(int i=1;i<=k;i++)
    {
        memset(tr,0,sizeof(tr));
        build(1,1,n,i);
        for(int j=1;j<=n;j++)
        {
            update(1,pre[j],j,1);
            f[i][j]=query(1,1,j);
        }
    }
    printf("%d\n",f[k][n]);
	return 0;
}
```

---

## 作者：CG__HeavenHealer (赞：27)

### 题意

给定一个序列 $a$，要把它分成 $k$ 个子段。每个子段的价值是其中不同元素的个数。求所有子段的价值之和的最大值。

### 解法

整个题解区就几个用决策单调性做的，~~有一个用的还是我不会的主席树维护~~，所以我就来补一发

首先想到DP应该很简单，方程也很显然：设 $f[i][j]$ 为把前 $i$ 个数分成 $j$ 段所需要的最大价值，可以得出： $ f[i][j]=\max\{f[i-1][j-1]+val(j+1,i)\} $，其中 $val(l,r)$ 表示的是 $[l,r]$ 这个区间的价值。

但是这样直接暴力转移的复杂度是 $\Theta(n^2k)$ ，不可承受。

对于这样的一个式子，直觉告诉我们可能**决策有单调性**。

那么怎么验证呢？

可以简单口胡一个证明：最大值是满足区间可加性的，对于两个区间 $[l,r]$ 和 ，$[l,r+1]$ ，设 $maxx$ 为 $[l,r]$ 中的最大值，那么在 $r$ 右移一位时，要么最大值不变，要么最大值变为 $r+1$ 上的元素，换句话说，在 $l$ 不变时，$maxx$ 随着 $r$ 的右移单调不降；两个区间同时加一个数 $x$ 后同理。所以 $f[i][j]$ 转移过程中是满足单调性的。

有了这个性质后，我们可以考虑分治优化DP。

由于答案单调，所以我们可以二分，设现在等待转移的区间为 $[l,r]$ ，可以转移过来的决策所在区间为 $[ql,qr]$ ，那么对于每一次查找，我们可以定义一个 $mid$ 为 $l,r$ 的中点，然后递归求解。

分治优化DP模板——代码片段（摘自OI-WIKI）

```cpp
void DP(int l, int r, int k_l, int k_r) {
  int mid = (l + r) / 2, k = k_l;
  // 求状态f[mid]的最优决策点
  for (int i = k_l; i <= min(k_r, mid - 1); ++i)
    if (w(i, mid) < w(k, mid)) k = i;
  f[mid] = w(k, mid);
  // 根据决策单调性得出左右两部分的决策区间，递归处理
  if (l < mid) DP(l, mid - 1, k_l, k);
  if (r > mid) DP(mid + 1, r, k, k_r);
}
```

回到本题，我们可以用同样的思路，设 $qmid$ 为最优决策所在的位置，最开始置为 $ql$ ，然后遍历 $ql$ 到 $qr$ ，遇到答案可以更新的时候就更新答案和 $qmid$ ，之后递归左、右区间分别求解。

```cpp
inline void solve(int l, int r, int ql, int qr, int tot) { // tot 表示当前子段数
    if (l > r) return;
    int mid = (l + r) >> 1, qmid = ql;
    for (ri i = ql; i <= min(qr, mid); i++) {
        int las = f[i - 1][tot - 1] + val(i, mid);
        bool updated = las > f[mid][tot];
        if (updated) f[mid][tot] = las, qmid = i;
    }
    solve(l, mid - 1, ql, qmid, tot);
    solve(mid + 1, r, qmid, qr, tot);
}
```

这样，DP的复杂度就成了 $k \log n$ 。

然后还需要考虑怎样高效维护每个子区间不重复数字的个数。

我们可以用**莫队**或**主席树**对这个信息进行维护。

下面给出莫队的代码片段：

```cpp
namespace mocap {
int L = 1, R, ans, cnt[N], a[N];
inline void add(int x) { ans += !cnt[x]++; }
inline void del(int x) { ans -= !--cnt[x]; }
inline int val(int l, int r) {
    while (L > l) add(a[--L]);
    while (R < r) add(a[++R]);
    while (R > r) del(a[R--]);
    while (L < l) del(a[L++]);
    return ans;
}
}  // namespace mocap
using namespace mocap;
```

有了这些，求解本题就易如反掌了。

总复杂度 $\Theta(nk\log n)$ 。

（另：理解了本题的思路后可以看看[这道题](https://www.luogu.com.cn/problem/CF868F)，思路几乎一样，检验一下学习成果）

### Code：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ri register int
const int N = 5e4 + 10, K = 50;
inline int read() {
    ri x = 0, f = 1;
    char ch = getchar();
    for (; !isdigit(ch); ch = getchar())
        if (ch == '-') f = -1;
    for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
    return f * x;
}
int f[N][K];
namespace mocap {
int L = 1, R, ans, cnt[N], a[N];
inline void add(int x) { ans += !cnt[x]++; }
inline void del(int x) { ans -= !--cnt[x]; }
inline int val(int l, int r) {
    while (L > l) add(a[--L]);
    while (R < r) add(a[++R]);
    while (R > r) del(a[R--]);
    while (L < l) del(a[L++]);
    return ans;
}
}  // namespace mocap
using namespace mocap;
inline void solve(int l, int r, int ql, int qr, int tot) {
    if (l > r) return;
    int mid = (l + r) >> 1, qmid = ql;
    for (ri i = ql; i <= min(qr, mid); i++) {
        int las = f[i - 1][tot - 1] + val(i, mid);
        bool updated = las > f[mid][tot];
        if (updated) f[mid][tot] = las, qmid = i;
    }
    solve(l, mid - 1, ql, qmid, tot);
    solve(mid + 1, r, qmid, qr, tot);
}
signed main() {
    int n = read(), k = read();
    for (ri i = 1; i <= n; i++) a[i] = read();
    memset(f, 0xcf, sizeof(f));
    f[0][0] = 0;
    for (ri i = 1; i <= k; i++) solve(1, n, 1, n, i);
    printf("%lld\n", f[n][k]);
    return 0;
}
```



---

## 作者：SpeMars (赞：17)

首先，我们看到这个划分区间，算总价值最大值的题，我们考虑一个朴素 DP 。

设 $f[i][j]$ 表示前 $j$ 个数划分为 $i$ 个连续区间的最大总价值。

那么转移方程就为：

$f[i][j]=\max(f[i-1][k]+val(k+1,i)) (i-1 \le k \le j-1) $

$val(l,r)$ 表示 $[l,r]$ 这个区间有多少个不同的数。

我们发现对于每次 $f[i][j]$ 的转移，只需要用到 $f[i-1][k]$ ，即上一次的划分。

所以 $f$ 数组可以滚动，~~其实没用~~。

这样一来，朴素 DP 时间复杂度就是 $O(n^3k)$ ~~稳稳 T 飞~~。

转念一想， $k \le 50$ 所以我们猜测正解时间复杂度。

由于 DP 数组都需要 $nk$ (不开滚动数组)所以时间复杂度至少要 $O(nk)$。

但是更新显然做不到 $O(1)$ ，$O(\log_n)$ 是最好的选择。

然后转移方程里出现了 $\max(...)$ 所以我们可以考虑线段树。

首先先用上一层的划分最大值建树，一共要建 $k$ 棵线段树，

空间重复利用就好了，时间也够。

接下来就是处理如何用线段树维护 $\max(f[i-1][k]+val(l,r))$ 了。

我们反过来考虑，对于每个数，它对于 $val(l,r)$ 的贡献在哪里？

记这个数为 $a[i]$ 的前面的第一个与它相等的数的位置为 $pre[a[i]]$ ，

那么这个 $a[i]$ 对于 $pre[a[i]] < l < i$ 的区间，是有贡献的，为 $1$ 。

那么我们顺序 DP 每一次先用上一次的 $i-1$ 的 DP 值建树，

然后每扫过一个数 $a[j]$ ，就在线段树上的区间 $[pre[a[j]],j-1]$ 全部加上$1$ 。

每次更新，就在线段树上 $[i-1,j-1]$ 的区间找 $\max(f[i-1][k]+val(l,r))$ 即可。

这里用线段树维护总的时间复杂度为 $O(nk\log_n)$ 显然可以通过本题。

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define int long long
using namespace std;
const int N=40010,M=111;
int n,m,a,f[M][N],lst[N],p[N],add[N*4];
struct laq{
	int l,r,mx;
}t[N*4];
void build(int k,int i,int l,int r){
	t[i]=(laq){l,r,0};
	if(l==r){
		t[i].mx=f[k][r];
		return;
	}
	int son=(i*2),mid=(l+r)/2;
	build(k,son,l,mid);
	build(k,son+1,mid+1,r);
	t[i].mx=max(t[son].mx,t[son+1].mx);
	return;
}
void addtag(int i,int k){
	add[i]+=k;
	t[i].mx+=k;
	return;
}
void downtag(int i){
	if(add[i]==0)return;
	int son=(i*2);
	if(t[son].l!=-1)addtag(son,add[i]);
	if(t[son+1].l!=-1)addtag(son+1,add[i]);
	add[i]=0;
	return;
}
void change(int i,int l,int r,int k){
	if(t[i].l>r||t[i].r<l)return;
	if(l<=t[i].l&&t[i].r<=r){
		addtag(i,k);
		return;
	}
	downtag(i);
	int son=(i*2);
	change(son,l,r,k);
	change(son+1,l,r,k);
	t[i].mx=max(t[son].mx,t[son+1].mx);
	return;
}
int query(int i,int l,int r){
	if(t[i].l>r||t[i].r<l)return 0;
	if(l<=t[i].l&&t[i].r<=r)return t[i].mx;
	downtag(i);
	int son=(i*2);
	return max(query(son,l,r),query(son+1,l,r));
}
signed main(){
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;++i){
		scanf("%lld",&a);
		lst[i]=p[a];
		p[a]=i;
	}
	for(int i=1;i<=m;++i){
		memset(t,-1,sizeof(t));
		memset(add,0,sizeof(add));
		build(i-1,1,0,n-1);
		for(int j=1;j<=n;++j){
			change(1,lst[j],j-1,1);
			f[i][j]=query(1,i-1,j-1);
		}
	}
	printf("%lld\n",f[m][n]);
	return 0;
}
```

---

## 作者：Star_Cried (赞：11)

## CF833B-线段树优化DP

### 题意

将一个长为$n$的序列分成$k$段，每段贡献为其中不同数字的个数，求最大贡献和。

### 思路

此处感谢@gxy001 聚铑的精彩讲解

先考虑暴力DP，可以想到一个时空复杂度$O(n^2k)$的方法，即记录前i个数字分成了j段。我们现在来思考几个问题来优化这个操作：

1. 对于一个数字，它对那些地方实际有贡献？
2. 每次分割出一个区间段对后续操作有影响的位置在哪？
3. 每次转移都从哪些地方继承？

下来一一解答这些问题。

1. 对于一个数字，它能产生贡献的区间其实就是该数字上一次出现的位置的后一位到它本身的位置。
2. 对于每次划分，它以前的位置的贡献已经被考虑，所以我们只能考虑后面的位置。
3. 相应的，每次转移会继承前面所有DP值的**最大值**。

那么我们可以将k提出来，每次循环继承上一次所有的dp值。因为只考虑从前面转移dp值，所以不会对之前的决策产生影响，所以是正确的。

看看1、3问题的答案，是不是想到了RMQ和区间赋值？

于是我们可以通过线段树来实现DP优化。

具体来讲，迭代k次，每次线段树更新为上一次序列的dp值，然后从前往后扫，每个数会对其上述区间产生1的贡献，转移继承前面所有dp值的最大值即可。

时间复杂度将一维优化为log。

### 代码

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cctype>
#include<algorithm>
#include<cmath>
using namespace std;
inline int read(){
	int w=0,x=0;char c=getchar();
	while(!isdigit(c))w|=c=='-',c=getchar();
	while(isdigit(c))x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return w?-x:x;
}
namespace star
{
	const int maxn=35005;
	int n,k,cur[maxn],pre[maxn],f[maxn][60];
	struct SegmentTree{
		#define ls (ro<<1)
		#define rs (ro<<1|1)
		struct tree{
			int l,r,tag,v;
		}e[maxn<<2];
		inline void pushup(int ro){
			e[ro].v=max(e[ls].v,e[rs].v);
		}
		inline void pushdown(int ro){
			e[ls].tag+=e[ro].tag;e[rs].tag+=e[ro].tag;
			e[ls].v+=e[ro].tag;e[rs].v+=e[ro].tag;
			e[ro].tag=0;
		}
		void build(int ro,int l,int r){
			e[ro].l=l,e[ro].r=r;
			if(l==r)return;
			int mid=l+r>>1;
			build(ls,l,mid);
			build(rs,mid+1,r);
		}
		void rebuild(int tim,int ro){
			int l=e[ro].l,r=e[ro].r;
			e[ro].tag=0;
			if(l==r){
				e[ro].v=f[l][tim];return;
			}
			rebuild(tim,ls);rebuild(tim,rs);
			pushup(ro);
		}
		void update(int ro,int x,int y){
			int l=e[ro].l,r=e[ro].r;
			if(l>=x and r<=y){
				e[ro].v+=1;
				e[ro].tag+=1;return;
			}
			pushdown(ro);
			int mid=l+r>>1;
			if(mid>=x)update(ls,x,y);
			if(mid<y)update(rs,x,y);
			pushup(ro);
		}
		int query(int ro,int x,int y){
			int l=e[ro].l,r=e[ro].r;
			if(l==x and r==y)return e[ro].v;
			pushdown(ro);
			int mid=l+r>>1;
			if(mid<x)return query(rs,x,y);
			else if(mid>=y)return query(ls,x,y);
			else return max(query(ls,x,mid),query(rs,mid+1,y));
		}
		#undef ls
		#undef rs 
	}T;
	inline void work(){
		n=read(),k=read();
		for(int x,i=1;i<=n;i++)x=read(),pre[i]=cur[x],cur[x]=i;
		T.build(1,0,n);
		for(int i=1;i<=k;i++){
			T.rebuild(i-1,1);
			for(int x=1;x<=n;x++) T.update(1,pre[x],x-1),f[x][i]=T.query(1,0,x-1);
		}
		printf("%d",f[n][k]);
	}
}
signed main(){
	star::work();
	return 0;
}
```



---

## 作者：littlewyy (赞：8)

##### [原题链接](http://codeforces.com/problemset/problem/834/D)

##### 题意

给你一个长度为n的序列，要求将其分成k段，每一段的贡献是这一段中不同的数的个数，求最大总贡献。

$1\leq n \leq 35000,1\leq k \leq min(n,50)$

##### 题解

状态：$f(i)(j)$表示前$i$个数分成$j$段的最大贡献

转移：$f(i)(j) = max_{k=0}^{i-1}f(k)(j-1)+w(k+1,i)$

时间复杂度：$O(n^2k)$

观察转移方程，不难发现$f(i)(j)$的决策集合与$f(i-1)(j)$的**决策集合有重合性**；且**附加值呈现区间性变化**：所有$w(k',i)$比$w(k',i-1)$多1，其中$k'$在$i$的前一个同类元素$pre(i)$之后；其余$w$不变。

区间增加，最值查询，不妨考虑**数据结构**维护。

将$f(i = 1 \rightarrow n )(j-1)$全部载入线段树中。处理$f(i)(j)$时，在线段树中将$[pre(i) , i - 1]$区间加1，再对$[0,i-1]$取$max$即可。

时间复杂度：$O(nlognk)$。[代码见此](https://github.com/littlewyy/luogu/blob/master/CF833Bseg.cpp)

##### 另解

根据决策集合的重合性和附加值仅末尾一段增加的性质，不难得出一个结论：

$f(i)(j)$相对于$f(i-1)(j)$的最优决策点单调不左移。

当dp具有**决策单调性**时，可以使用**分治法**求解。

具体地，计算完$f(1\rightarrow n)(j-1)$后，整体地转移到$f(1 \rightarrow n)(j)$。对于$f(l \rightarrow r)(j)$的求解，令$mid = (l + r) /2 $，暴力求出$f(mid)(j)$及其最优决策点$dmid$，则可确定$f(l\rightarrow mid)(j)$的决策点在$dmid$及其左边，$f(mid +1 \rightarrow r)(j)$的决策点在$dmid$及其右边，递归下去求解即可。

分治至多$logn$层，每层时间复杂度$O(n)$。共进行$k$次分治求解。

时间复杂度：$O(nlognk)$。[代码见此](https://github.com/littlewyy/luogu/blob/master/CF833Bmono.cpp)

实现上的细节问题：注意分治的意义在于决策区间被限定在$[ll,lr]$，递归函数内注意循环的范围。另外，快速求解$[l,r]$中不同数的种类数，可以使用差分+可持久化线段树。若每次计算$w$都调用线段树，复杂度会多一个log；实际上只需调用1次，计算出$[lr+2,mid]$中不同数的个数，其余在从后往前枚举决策点时累加即可。


---

## 作者：loveJY (赞：7)

提供一种**正常的决策单调性算法和证明**，和一种看上去较优秀复杂度算法

本题的dp转移具有决策单调性，证明：

设$x<y$，$uni(x,y)$表示区间$[x,y]$不同数字个数

$i$选择$y$，$i+1$选择$x$

有

1. $$uni(x,i+1)+dp[x]>uni(y,i+1)+dp[y]$$

2. $$uni(y,i)+dp[y]>uni(x,i)+dp[x]$$

根据uni函数的性质，我们有

3. $$uni(y,i+1)<=uni(y,i)+1$$

$1+2$可得

$$uni(x,i+1)+dp[x]+uni(y,i)+dp[y]>uni(y,i+1)+dp[y]+uni(x,i)+dp[x]$$

$$uni(x,i+1)+uni(y,i)>uni(y,i+1)+uni(x,i)$$

$$uni(x,i+1)-uni(x,i)>uni(y,i+1)-uni(y,i)$$

$uni(x,i+1)-uni(x,i)$必须为1，而$uni(y,i+1)-uni(y,i)$必须为0

但是$[x,i]$完全包括了$[y,i]$

所以当前者为1的时候，后者必须为1

故矛盾，i选择x一定不会更劣，证毕

回到这道题，因为我们要选择k次，而k很小

我们可以得到第一种做法：

利用分治决策单调性以及该决策单调性的"莫队"式移动的最多$nlogn$次结论直接写就可以得到$nklogn$的好复杂度！

code:


```cpp

#include<bits/stdc++.h>
const int MAXN=1e5+7;
using namespace std;
int n,k,a[MAXN],f[MAXN],g[MAXN];
int buc[MAXN];
int lx,rx,res;

inline int getw(int p,int q) {
	while(rx<q) {
		++rx;
		if(!buc[a[rx]])res++;
		buc[a[rx]]++;
	}
	while(rx>q) {
		buc[a[rx]]--;
		if(!buc[a[rx]])res--;
		--rx;
	}
	while(lx>p) {
		--lx;
		if(!buc[a[lx]])res++;
		buc[a[lx]]++;
	}
	while(lx<p) {
		buc[a[lx]]--;
		if(!buc[a[lx]])res--;
		++lx;
	}
	return res;
}

//use L,R update l,r
inline void solve(int L,int R,int l,int r) {
	int mid=(l+r)>>1;
	int maxx=-1,pos=-1;
	for(int i=L; i<=R; ++i) {
		if(i+1>mid)break;
		if(g[i]+getw(i+1,mid)>maxx) {
			maxx=g[i]+getw(i+1,mid);
			pos=i;
		}
	}
	assert(~pos);
	f[mid]=max(f[mid],maxx);
	if(l<mid)solve(L,pos,l,mid-1);
	if(r>mid)solve(pos,R,mid+1,r);
}

int main() {
	scanf("%d%d",&n,&k);
	for(int i=1; i<=n; ++i) {
		scanf("%d",&a[i]);
	}
	lx=1,rx=0;
	for(int i=1; i<=k; ++i) {
		for(int i=1; i<=n; ++i)f[i]=0;
		solve(0,n,1,n);//qwq
		for(int i=1; i<=n; ++i)g[i]=f[i];
	}
	printf("%d\n",g[n]);
	return 0;
}


```

可是我们并不满意于这个$ACcode$,难道就没有很好看的复杂度吗？比如去掉这个k

于是做法呼之欲出，在满足决策单调性的前提下，我们可以安心使用wqs二分把k这一维变成$logV$,而这道题的V和n同阶,所以可以得到$O(logn)$严格小于k的复杂度~~AC也证明了他的正确性~~

但不如人意的是，我们的转移变成了同层之间也可以的。。。所以就要用一个cdq分治来维护转移。。。

这样复杂度变成$O(nlog^3n)$，虽然严格来讲没有上个复杂度优秀,但是我们可以疯狂加强,把k开到和n同阶并且五万然后hh了

code：

```cpp

#include<bits/stdc++.h>
const int MAXN=1e5+7;
using namespace std;
int n,k,a[MAXN],f[MAXN],g[MAXN];
int buc[MAXN];
int lx,rx,res,ex;

inline int getw(int p,int q) {
	while(rx<q) {
		++rx;
		if(!buc[a[rx]])res++;
		buc[a[rx]]++;
	}
	while(rx>q) {
		buc[a[rx]]--;
		if(!buc[a[rx]])res--;
		--rx;
	}
	while(lx>p) {
		--lx;
		if(!buc[a[lx]])res++;
		buc[a[lx]]++;
	}
	while(lx<p) {
		buc[a[lx]]--;
		if(!buc[a[lx]])res--;
		++lx;
	}
	return res;
}

//use L,R update l,r
inline void cdq(int L,int R,int l,int r) {
	int mid=(l+r)>>1;
	int maxx=-1e9,pos=-1;
	for(int i=L; i<=R; ++i) {
		if(i+1>mid)break;
		if(f[i]+getw(i+1,mid)+ex>maxx) {
			maxx=f[i]+getw(i+1,mid)+ex;
			pos=i;
		}
	}
	if(maxx>f[mid]) {
		f[mid]=maxx;
		g[mid]=g[pos]+1;
	}
	if(l<mid)cdq(L,pos,l,mid-1);
	if(r>mid)cdq(pos,R,mid+1,r);
}

inline void solve(int l,int r) {
	if(l==r)return ;
	int mid=(l+r)>>1;
	solve(l,mid);
	cdq(l,mid,mid+1,r);
	solve(mid+1,r);
}

inline int chk() {
	for(int i=0; i<=n; ++i)f[i]=g[i]=0;
	solve(0,n);
	return g[n]<=k;
}

int main() {
	scanf("%d%d",&n,&k);
	for(int i=1; i<=n; ++i) {
		scanf("%d",&a[i]);
	}
	lx=1,rx=0;
	int tmpl=-n,tmpr=n,ans=0;
	while(tmpl<=tmpr) {
		ex=(tmpl+tmpr)>>1;
		if(chk()) {
			ans=f[n]-k*ex;
			tmpl=ex+1;
		} else {
			tmpr=ex-1;
		}
	}
	printf("%d\n",ans);
	return 0;
}


```


---

## 作者：resftlmuttmotw (赞：4)

此题可用决策单调性来做

证明 略

### 引入

[决策单调性($My blog$)](https://www.luogu.com.cn/blog/cqj/jue-ce-dan-diao-xing-you-hua-dp-fen-zhi-you-hua-jue-ce-dan-diao-xing)

### 思路

于是此题便可先用分治优化决策单调性


时间 $O(n^2*k)$ $101 tests$ 中 只能过前$9$个 $9pts$ ?
```cpp
#include <map>
#include <string>
#include <cstdio>
#include <string>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;
#define reg register int
#define isdigit(x) ('0' <= x&&x <= '9')
template<typename T>
inline T Read(T Type)
{
	T x = 0,f = 1;
	char a = getchar();
	while(!isdigit(a)) {if(a == '-') f = -1;a = getchar();}
	while(isdigit(a)) {x = (x << 1) + (x << 3) + (a ^ '0');a = getchar();}
	return x * f;
}
const int MAXN = 35010,inf = MAXN;
int a[MAXN],dp[MAXN][55];
bool vis[MAXN];
inline int cost(int l,int r)
{
	int res = 0;
	for(reg i = l;i <= r;i++)
	{
		if(!vis[a[i]]) res++;
		vis[a[i]] = 1;
	}
	for(reg i = 1;i <= r;i++) vis[a[i]] = 0;	
	return res;
}
inline void dfs(int k,int l,int r,int opl,int opr)
{
	if(l > r) return;
	int mid = l + r >> 1,maxl = -inf,id;
	for(reg i = opl;i <= min(opr,mid);i++)
	{
		int cur = dp[i - 1][k - 1] + cost(i,mid);
		if(cur > maxl) maxl = cur,id = i;
	}
	dp[mid][k] = maxl;
	dfs(k,l,mid - 1,opl,id);
	dfs(k,mid + 1,r,id,opr);
}
int main()
{
	int n = Read(1),k = Read(1);
	for(reg i = 1;i <= n;i++)
		a[i] = Read(1);
	for(reg i = 1;i <= k;i++) dfs(i,1,n,1,n);
	printf("%d\n",dp[n][k]);
	return 0;
}
```

考虑优化 

观察代码 发现$cost$(查询区间不同数个数)就有一层$n$

考虑降成$O(1)$ 但预处理是$O(n^2)$

于是只能降成$O(log_2^n)$

从我们学习的数据结构中寻找

发现主席树恰好可以胜任

用主席树$A$掉这道题

[SP3267 DQUERY - D-query](https://www.luogu.com.cn/problem/SP3267)

再粘过来就行了

然而我这道题写的莫队 现在又写了一遍主席树 233

### $Code$

时间复杂度 $O(n*log_2^n*k)$

```cpp
#include <map>
#include <string>
#include <cstdio>
#include <string>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;
#define reg register int
#define isdigit(x) ('0' <= x&&x <= '9')
template<typename T>
inline T Read(T Type)
{
	T x = 0,f = 1;
	char a = getchar();
	while(!isdigit(a)) {if(a == '-') f = -1;a = getchar();}
	while(isdigit(a)) {x = (x << 1) + (x << 3) + (a ^ '0');a = getchar();}
	return x * f;
}
const int MAXN = 35010,inf = MAXN;
int a[MAXN],dp[MAXN][55],n,k;
namespace segment_tree
{
	struct node
	{
		int l,r,val;
	}tree[MAXN * 40];
	map<int,int> vis;
	int cnt,root[MAXN];
	inline int update(int k,int l,int r,int pos,int v)
	{
	    tree[++cnt] = tree[k],tree[cnt].val += v;
	    k = cnt;
	    if(l == r) return k;
	    int mid = l + r >> 1;
	    if(pos <= mid) tree[k].l = update(tree[k].l,l,mid,pos,v);
	    else tree[k].r = update(tree[k].r,mid + 1,r,pos,v);
	    return k;
	}
	inline int query(int k,int pos,int l,int r)
	{
	    if(l >= pos) return tree[k].val;
	    int mid = l + r >> 1;
	    if(pos <= mid) return query(tree[k].l,pos,l,mid) + tree[tree[k].r].val;
	    return query(tree[k].r,pos,mid + 1,r);
	}
	inline void init()
	{
		n = Read(1),k = Read(1);
		root[0] = tree[0].l = tree[0].r = tree[0].val = 0;
		for(reg i = 1;i <= n;i++)
		{
			int x = Read(1);
			if(!vis[x]) root[i] = update(root[i - 1],1,n,i,1);
			else {
				int k = update(root[i - 1],1,n,vis[x],-1);
				root[i] = update(k,1,n,i,1);
			}
			vis[x] = i;
		}
	}
}
using namespace segment_tree;
inline int cost(int l,int r) {return query(root[r],l,1,n);}
inline void dfs(int k,int l,int r,int opl,int opr)
{
	if(l > r) return;
	int mid = l + r >> 1,maxl = -inf,id;
	for(reg i = opl;i <= min(opr,mid);i++)
	{
		int cur = dp[i - 1][k - 1] + cost(i,mid);
		if(cur > maxl) maxl = cur,id = i;
	}
	dp[mid][k] = maxl;
	dfs(k,l,mid - 1,opl,id);
	dfs(k,mid + 1,r,id,opr);
}
int main()
{
	init();
	for(reg i = 1;i <= k;i++) dfs(i,1,n,1,n);
	printf("%d\n",dp[n][k]);
	return 0;
}
```


---

## 作者：Jμdge (赞：4)

1 A 了

原因竟是做了类似的题： [ hdu 双倍不完全经验](http://acm.hdu.edu.cn/showproblem.php?pid=6070)

做法极其类似，只不过一个是二分一个是 dp

大概考虑一下这个数据范围，一看就是 nk 要的，然后 nk 之后好像还蛮富足（否则 n 就 1e5 了），那么大胆猜测还有个 log ，那么估计就是个 $n ~k\log n  $ 的线段树优化 dp 了，事实上证明确实是这样

然后难点就是考虑一段中出现的**不同的**数的个数

这个可以对于每个点 i 记一下上次出现的位置  $p[i]$ ，然后线段树区间覆盖的时候覆盖  $p[i]$ ~ $i-1$ 就好了

其次都是小细节

# Code

大常数 Judge

```
//by Judge (zlw ak ioi)
#pragma GCC optimize("Ofast")
#include<cstdio>
#include<cstring>
#include<iostream>
#define Rg register
#define fp(i,a,b) for(Rg int i=(a),I=(b)+1;i<I;++i)
#define fd(i,a,b) for(Rg int i=(a),I=(b)-1;i>I;--i)
#define db double
using namespace std;
const int M=1e5+3;
typedef int arr[M];
#ifndef Judge
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
#endif
char buf[1<<21],*p1=buf,*p2=buf;
template<class T>inline T Max(T a,T b){return a>b?a:b;}
inline int read(){ int x=0,f=1; char c=getchar();
	for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
	for(;isdigit(c);c=getchar()) x=x*10+c-'0'; return x*f;
} int n,k; arr a,p,f,las;
namespace SegT{ int t[M<<2],tag[M<<2];
#define ls k<<1
#define rs k<<1|1
#define len (r-l+1)
#define lson ls,l,mid
#define rson rs,mid+1,r
	inline void Add(int k,int v){ tag[k]+=v,t[k]+=v; }
	inline void Psd(int k){ if(!tag[k]) return ;
		Add(ls,tag[k]),Add(rs,tag[k]),tag[k]=0;
	}
	void Bud(int k,int l,int r){ tag[k]=0;
		if(l==r) return t[k]=f[l],void(); int mid=(l+r)>>1;
		Bud(lson),Bud(rson),t[k]=Max(t[ls],t[rs]);
	}
	void Upd(int k,int l,int r,int L,int R){
		if(L<=l&&r<=R) return Add(k,1),void();
		if(l>R||L>r) return ; int mid=(l+r)>>1; Psd(k);
		Upd(lson,L,R),Upd(rson,L,R),t[k]=Max(t[ls],t[rs]);
	}
	int Que(int k,int l,int r,int R){ int mid=(l+r)>>1;
		if(l>R) return 0; if(r<=R) return t[k];
		return Psd(k),Max(Que(lson,R),Que(rson,R));
	}
} using namespace SegT;
int main(){ n=read(),k=read(); fp(i,1,n) las[i]=0;
	fp(i,1,n) a[i]=read(),p[i]=las[a[i]],
		f[i]=f[i-1]+!las[a[i]],las[a[i]]=i;
	fp(i,2,k){ Bud(1,1,n);
		fp(j,1,n) Upd(1,1,n,p[j],j-1),f[j]=Que(1,1,n,j);
	} return !printf("%d\n",f[n]);
}
```






---

## 作者：lx_zjk (赞：4)

这道题采用了线段树优化动态规划的方法

```
f[i][j] = max(f[l][j - 1] + cnt[l + 1][j]);
```

暴力显然过不了 考虑优化

线段树 可以优化

扫一遍当前数组 $pre$表示$a[i]$个数可以影响到的数的第一个 也就是前面第一个相同的数的后面

那么第$i$个数只能对$pre[i], i$产生影响

那么线段树就是负责这样一个操作

当前线段数$t[p].dat$维护$f[i - 1][l - 1]$前面$i - 1$个分段到了第i个数

然后修改之后取$max$即可

# code

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int INF = 2139062143;

#define DEBUG(x) std::cerr << #x << ' = ' << x << std::endl

inline ll read() {
    ll f = 1, x = 0;char ch;
    do {ch = getchar();if (ch == '-')f = -1;} while (ch > '9' || ch < '0');
    do {x = x * 10 + ch - '0';ch = getchar();} while (ch >= '0' && ch <= '9');
    return f * x;
}

const int MAX_N = 35000 + 5;

const int MAX_K = 50 + 5;

int n, k, a[MAX_N], pre[MAX_N], pos[MAX_N], f[MAX_K][MAX_N];

struct segment_tree {
	int l, r, dat, tag;
} t[MAX_N << 2];

#define ls(p) (p << 1)
#define rs(p) (p << 1 | 1)

void build (int p, int l, int r, int now) {
	t[p].l = l; t[p].r = r;
	if (l == r) {
		t[p].dat = f[now][l - 1];
		return; 
	}
	int mid = (l + r) >> 1;
	build (ls(p), l, mid, now);
	build (rs(p), mid + 1, r, now);
	t[p].dat = max(t[ls(p)].dat, t[rs(p)].dat);
}

void push_down (int p) {
	if (t[p].tag == 0) return;
	t[ls(p)].dat += t[p].tag;
	t[rs(p)].dat += t[p].tag;
	t[ls(p)].tag += t[p].tag;
	t[rs(p)].tag += t[p].tag;
	t[p].tag = 0;
}

void change (int p, int l, int r, int v) {
	if (l <= t[p].l && t[p].r <= r) {
		t[p].dat += v;
		t[p].tag += v;
		return ;
	}
	push_down(p);
	int mid = (t[p].l + t[p].r) >> 1;
	if (l <= mid)
		change (ls(p), l, r, v);
	if (r > mid)
		change (rs(p), l, r, v);
	t[p].dat = max(t[ls(p)].dat, t[rs(p)].dat);
}

inline int query (int p, int l, int r) {
	if (l <= t[p].l && t[p].r <= r)
		return t[p].dat;
	push_down(p);
	int mid = (t[p].l + t[p].r) >> 1;
	int ans = 0;
	if (l <= mid)
		ans = query (ls(p), l, r);
	if (r > mid)
		ans = max(ans, query(rs(p), l, r));
	return ans;
}

int main() {
	n = read(); k = read();
	for (int i = 1; i <= n; i ++ ) {
		int t = read();
		pre[i] = pos[t] + 1, pos[t] = i;
	}
	for (int i = 1; i <= k; i ++ ) {
		memset (t, 0, sizeof(t));
		build (1, 1, n, i - 1);	
		for (int j = 1; j <= n; j ++ ) {
			change (1, pre[j], j, 1);
			f[i][j] = query (1, 1, j);
		}
	}
	printf("%d\n", f[k][n]);
	return 0;
}
```

---

## 作者：James_Brady (赞：3)

考虑dp

定义$dp[i][j]$为前$i$项分成$j$个区间的最大价值和

方程就为：$dp[i][j]=max(dp[l][j-1]+val(l+1,i))$

$val(l+1,i)$为$[l+1,i]$这个区间中不同数的个数

来慢慢看，先枚举$i$，$j$，再枚举$l$，再求$val(l+1,i)$，时间复杂度为$O(n^{3}k)$，会超时。

我们尝试优化，

我们可以把l倒着枚举，这样就可以边更新答案边统计$val(l+1,i)$。

代码是这个亚子：
```cpp
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=min(i,k);j++)
		{
			tot=1;
			memset(vis,0,sizeof(vis));
			vis[a[i]]=1;
			for(int l=i-1;l>=1;l--)
			{
				dp[i][j]=max(dp[i][j],dp[l][j-1]+tot);
				if(!vis[a[l]])
				tot++;
				vis[a[l]]=1;
			}
			dp[i][j]=max(dp[i][j],dp[0][j-1]+tot);
		}
	}
```

优化到了$O(n^{2}k)$，但还是会超时。

继续优化，

我们发现，我们枚举的这个$l$是一段连续的区间，我们想到了什么？线段树！

我们把每次求出的$dp[i][j]$丢到一棵线段树上，就可以$O(log_{2}n)$地查询了。岂不美哉？

那么问题又来了，$val(l+1,i)$怎么求呢？

我们记录$a[i]$上一次出现的位置$pos[i]$，则$a[i]$对$[pos[i]+1,i-1]$的$val$值都有贡献1，区间加即可，问题解决。

时间复杂度$O(nklog_{2}n)$

code：
```cpp
#include<iostream>
#include<cstdio>
#include<queue>
#include<cstring>
#define ll long long
#define lson id<<1,l,m
#define rson id<<1|1,m+1,r
using namespace std;
int dp[50010][60],n,k,a[50010],pos[50010],tot;
int t[60][200010],lzy[60][200010];//对于每个j都开一个线段树
void pushup(int num,int id)
{
	t[num][id]=max(t[num][id<<1],t[num][id<<1|1]);
}
void pushdown(int num,int id)
{
	if(lzy[num][id]!=0)
	{
		lzy[num][id<<1]+=lzy[num][id];
		lzy[num][id<<1|1]+=lzy[num][id];
		t[num][id<<1]+=lzy[num][id];
		t[num][id<<1|1]+=lzy[num][id];
		lzy[num][id]=0;
	}
}
void update(int num,int id,int l,int r,int x,int y,int p)
{
	if(x<=l&&r<=y)
	{
		t[num][id]+=p;
		lzy[num][id]+=p;
		return;
	}
	pushdown(num,id);
	int m=(l+r)>>1;
	if(x<=m)
	update(num,lson,x,y,p);
	if(y>m)
	update(num,rson,x,y,p);
	pushup(num,id);
}
int query(int num,int id,int l,int r,int x,int y)
{
	if(x<=l&&r<=y)
	return t[num][id];
	pushdown(num,id);
	int m=(l+r)>>1,ans=0;
	if(x<=m)
	ans=max(ans,query(num,lson,x,y));
	if(y>m)
	ans=max(ans,query(num,rson,x,y));
	return ans;
}
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
	scanf("%d",&a[i]);
	for(int i=1;i<=k;i++)
	update(0,1,0,n,i,i,-0x3f3f3f3f);//dp[0][1]~dp[0][k]不存在，赋为-inf
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<=min(i,k);j++)
		update(j,1,0,n,pos[a[i]],i-1,1);
		pos[a[i]]=i;//更新位置
		for(int j=1;j<=min(i,k);j++)
		{
			dp[i][j]=query(j-1,1,0,n,0,i-1);//转移
			update(j,1,0,n,i,i,dp[i][j]);
		}
	}
	printf("%d",dp[n][k]);
}
```

---

## 作者：BigJoker (赞：2)

# Preface

数据结构优化 DP 好题。

调了很久。。。

# Solution

* 考虑暴力 DP

不难想到 $f_{i,j}$ 表示前 $i$ 个数分为 $j$ 段的最大价值。

那么不难推出：

$f_{i,j}\gets \max_{k=0}^{i-1} f_{k,j-1}+p(k+1,i)$

然后复杂度就 $\Theta(n^2k)$。

虽然说 $p$ 可以优化掉，但是复杂度仍然不允许。

* 考虑优化

发现这个题的一些特点。

方程的 $j$ 只跟 $j-1$ 有关系，这让我们不难想到可以利用一个数据结构实现查询上一层的最大值。

但是问题在于 $p$ 函数不方便使用。

但是我们可以考虑转换一下。

我们设位置为 $i$，表示的数为 $a_i$。

上一个是 $a_i$ 的数是 $pre_{a_i}$

那么 $a_i$ 的贡献就只有 $[pre_{a_i}+1,i]$ 这些位置上的数有贡献。

那么不难想到利用线段树进行区间修改操作和查询最大值的操作。

复杂度为 $\Theta(nk\log n)$

注意到一些细节。

考虑 DP 的定义，不要把区间给加错了。

还需要注意到实时进行，不然答案可能会存在问题。

# Code

```cpp
#include<bits/stdc++.h>
#define re register
#define il inline
using namespace std;
const int N=35005;
const int M=55;
int n,m;
int a[N];
int dp[N][M],pre[N],id[N];
int vis[N],p[N];
struct Segment_Tree{
	struct node{
		int l,r,val,add;
	}t[4*N];
	void pushdown(int p){
		if(t[p].add){
			int l=p<<1,r=p<<1|1;
			t[l].val+=t[p].add;
			t[r].val+=t[p].add;
			t[l].add+=t[p].add;
			t[r].add+=t[p].add;
			t[p].add=0;
		}
	}
	void clear(int i,int p,int l,int r){
		t[p].l=l,t[p].r=r;
		if(l==r){
			t[p].val=dp[l][i];
			return ;
		}
		int mid=l+r>>1;
		clear(i,p<<1,l,mid);
		clear(i,p<<1|1,mid+1,r);
		t[p].val=max(t[p<<1].val,t[p<<1|1].val);
	}
	void update(int p,int l,int r,int x){
		if(t[p].l>=l && t[p].r<=r){
			t[p].add+=x,t[p].val+=x;
			return ;
		}
		pushdown(p);
		int mid=t[p].l+t[p].r>>1;
		if(l<=mid) update(p<<1,l,r,x);
		if(r>mid) update(p<<1|1,l,r,x);
		t[p].val=max(t[p<<1].val,t[p<<1|1].val);
	}
	int ask(int p,int l,int r){
		if(t[p].l>=l && t[p].r<=r) return t[p].val;
		pushdown(p);
		int mid=t[p].l+t[p].r>>1,res=0;
		if(l<=mid) res=ask(p<<1,l,r);
		if(r>mid) res=max(res,ask(p<<1|1,l,r));
		return res;
	}
}tr[M];
int main(){
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]),pre[i]=id[a[i]],id[a[i]]=i;
	for(int i=1;i<=n;i++){
		dp[i][1]=dp[i-1][1];
		if(!vis[a[i]]) vis[a[i]]=1,dp[i][1]++;
	}
	for(int j=2;j<=m;j++){
		tr[j-1].clear(j-1,1,0,n);
		for(int i=1;i<=n;i++){
			tr[j-1].update(1,pre[i],i-1,1);
			dp[i][j]=tr[j-1].ask(1,0,i-1);
		}
	}
	printf("%d",dp[n][m]);
	return 0;				
}
```

---

## 作者：Coros_Trusds (赞：1)

[更好的阅读体验](https://www.cnblogs.com/Coros-Trusds/p/15894491.html)

# 题目大意

将一个长度为 $n$ 的序列分为 $m$ 段，使得总价值最大。

一段区间的价值表示为区间内不同数字的个数。

# 题目分析

先不看数据范围，考虑朴素 $\rm dp$：

令 $dp[i][j]$ 表示前 $j$ 个数被分成了 $i$ 段的最大总价值，当前状态显然由分和不分区分开，即状态转移方程为 $dp[i][j]=\max\{dp[i-1][k]+val(k+1,j)\}(1\le k\lt j)$。

时间复杂度 $\mathcal{O}(n^3k)$，显然 $\verb!T!$ 飞。

可以用线段树维护最大值，存储 $dp[i-1][j]$，然后依次考虑每个点的贡献，显然是对区间 $[last[i]+1,i]$ 做贡献 $1$，$last[i]$ 表示序列中上一个值为 $a[i]$ 的数的位置。至于为什么会对这段区间产生贡献，可以看出来如果一个值在区间中出现了很多次，那这些重复的数都不会产生贡献了。优化后时间复杂度为 $\mathcal{O}(nk\log n)$。

# 代码

```cpp
//2022/2/13
//2022/2/14
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <climits>//need "INT_MAX","INT_MIN"
#include <cstring>//need "memset"
#include <algorithm>
#define enter() putchar(10)
#define debug(c,que) cerr << #c << " = " << c << que
#define cek(c) puts(c)
#define blow(arr,st,ed,w) for(register int i = (st);i <= (ed); ++ i) cout << arr[i] << w;
#define speed_up() cin.tie(0),cout.tie(0)
#define endl "\n"
#define mst(a,k) memset(a,k,sizeof(a))
#define Abs(x) ((x) > 0 ? (x) : (-x))
#define GET(x) ((x) < 0 ? (x) + mod : (x))
#define MOD(x) \
	((GET(x) >= mod) ? GET(x) - mod : GET(x))
namespace Newstd {
	char buf[1 << 21],*p1 = buf,*p2 = buf;
	inline int getc() {
		return p1 == p2 && (p2 = (p1 = buf) + fread(buf,1,1 << 21,stdin),p1 == p2) ? EOF : *p1 ++;
	}
	inline int read() {
		int ret = 0,f = 0;char ch = getc();
		while (!isdigit(ch)) {
			if(ch == '-') f = 1;
			ch = getc();
		}
		while (isdigit(ch)) {
			ret = (ret << 3) + (ret << 1) + ch - 48;
			ch = getc();
		}
		return f ? -ret : ret;
	}
	inline void write(int x) {
		if(x < 0) {
			putchar('-');
			x = -x;
		}
		if(x > 9) write(x / 10);
		putchar(x % 10 + '0');
	}
}
using namespace Newstd;
using namespace std;

const int ma1 = 3.5e4 + 5,ma2 = 55;
int a[ma1],pre[ma1],lst[ma1],dp[ma2][ma1];
//dp[i][j]:前 j 个数分成 i 段的最大价值和
int n,m;

struct Segment_Tree {
	struct Node {
		int l,r;
		int tag,Max;
	} node[ma1 << 2];
	#define lson (p << 1)
	#define rson (p << 1 | 1)
	inline void pushup(int p) {
		node[p].Max = max(node[lson].Max,node[rson].Max);
	}
	inline void build(int p,int l,int r,int k) {
		node[p].l = l,node[p].r = r,node[p].tag = 0,node[p].Max = 0;
		if (l == r) {
			node[p].Max = dp[k][l];
			return;
		}
		int mid = l + r >> 1;
		build(lson,l,mid,k),build(rson,mid + 1,r,k);
		pushup(p);
	}
	inline void pushdown(int p) {
		if (node[p].tag) {
			node[lson].tag += node[p].tag,node[rson].tag += node[p].tag;
			node[lson].Max += node[p].tag,node[rson].Max += node[p].tag;
			node[p].tag = 0;
		}
	}
	inline void update(int x,int y,int p,int k) {
		if (x <= node[p].l && node[p].r <= y) {
			node[p].tag += k,node[p].Max += k;
			return;
		}
		pushdown(p);
		int mid = node[p].l + node[p].r >> 1;
		if (x <= mid) update(x,y,lson,k);
		if (y > mid) update(x,y,rson,k);
		pushup(p);
	}
	inline int query(int x,int y,int p) {
		if (x <= node[p].l && node[p].r <= y) {
			return node[p].Max;
		}
		pushdown(p);
		int mid = node[p].l + node[p].r >> 1,res = 0;
		if (x <= mid) res = max(res,query(x,y,lson));
		if (y > mid) res = max(res,query(x,y,rson));
		return res;
	}
	#undef lson
	#undef rson
} seg;
int main(void) {
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	n = read(),m = read();
	for (register int i = 1;i <= n; ++ i) a[i] = read();
	for (register int i = 1;i <= n; ++ i) {
		lst[i] = pre[a[i]];
		pre[a[i]] = i;
	}
	for (register int i = 1;i <= m; ++ i) {
		seg.build(1,0,n - 1,i - 1);
		for (register int j = 1;j <= n; ++ j) {
			seg.update(lst[j] + 1,j,1,1);
			dp[i][j] = seg.query(1,j,1);
		}
	}
	printf("%d\n",dp[m][n]);

	return 0;
}
```

---

## 作者：Saber_Master (赞：1)

[CF833B The Bakery](https://www.luogu.com.cn/problem/CF833B)

#### 线段树优化dp

首先如果面对小数据范围，我们不难推出$kn^2dp$，即扫描$k$轮.我们若要求$f[i][j]$,则从$i$出发往前扫一遍，每次遇到没遇见过的数则$cnt$加上$1$,所以$f[i][j]=max{f[k][j-1]+cnt}$

我们发现每次$O(n)$扫一遍求$cnt$数组浪费大量时间，于是想办法优化.

设$g(i, j)$表示从$i$到$j$中不同的数字个数.我们固定住$j$，那么$num[j]$只对上一次出现位置的下一位置到$j$这里有贡献。所以维护一个$last$数组，$last[x]$表示$x$这个数字上次出现的位置.

接下来利用线段树维护，我们维护$k$轮，由于$k$很小，所以我们有很大的操作空间.每次新开一轮的时候重构线段树，第$k$轮将上面$l$位置的值表示为$f[l-1][k]$方便转移,每次扫描$f[i][k]$时，将线段树上$[last[i]+1, k]$的部分加上$1$.于是我们只需要线段树区间加,区间查询最大值即可.

$O(kn \log n)$

核心代码

```cpp
const ll N=3.5e4+5;

ll n, k;
ll f[N][51];
ll pos[N], last[N];
ll num[N];
struct segment{
	ll dat[N<<2], lazy[N<<2];
	
	inline void build(ll p, ll l, ll r, ll now){
		if (l==r) return (void) (dat[p]=f[l-1][now]);
		ll mid=l+r>>1;
		build(p<<1, l, mid, now); 
		build(p<<1|1, mid+1, r, now);
		dat[p]=max(dat[p<<1], dat[p<<1|1]);
	}
	
	inline void pushup(ll p, ll val){
		dat[p]+=val; lazy[p]+=val;
	}
	
	inline void pushdown(ll p, ll l, ll r){
		if (!lazy[p] || l==r) return;
		pushup(p<<1, lazy[p]); pushup(p<<1|1, lazy[p]);
		return (void)(lazy[p]=0);
	}
	
	inline void update(ll p, ll l, ll r, ll u, ll v, ll val){
		pushdown(p, l, r);
		if (u<=l && r<=v) return pushup(p, val);
		ll mid=l+r>>1;
		if (u<=mid) update(p<<1, l, mid, u, v, val);
		if (v>mid) update(p<<1|1, mid+1, r, u, v, val);
		dat[p]=max(dat[p<<1], dat[p<<1|1]);
	}
	
	inline ll query(ll p, ll l, ll r, ll u, ll v){
		pushdown(p, l, r);
		if (u<=l && r<=v) return dat[p];
		ll mid=l+r>>1, res=0;
		if (u<=mid) chkmax(res, query(p<<1, l, mid, u, v));
		if (v>mid) chkmax(res, query(p<<1|1, mid+1, r, u, v));
		return res;
	}
}tree[51];

int main(){
	read(n); read(k);
	for (R ll i=1; i<=n; i++){
		read(num[i]);
		last[i]=pos[num[i]];
		pos[num[i]]=i;
	}
	
	for (R ll i=1; i<=k; i++){
		tree[i].build(1, 1, n, i-1);
		for (R ll j=1; j<=n; j++){
			tree[i].update(1, 1, n, last[j]+1, j, 1);
			f[j][i]=tree[i].query(1, 1, n, 1, j);
		}
	}
	writeln(f[n][k]);
}
```


---

## 作者：Cylete (赞：1)

首先朴素的暴力DP比较显然

$f[i][j] = max\{f[k][j - 1] + val(k + 1, i)\}$

其中$f[i][j]$表示将前$i$个分为$j$段的最大价值，$val(i, j)$表示将$i$到$j$分为一段时这一段的价值

那么显然$j - 1 <= k <= i - 1$（至少分为$j - 1$段， 至多$i$为一段）

如果暴力上的话复杂度是$O(kn^2)$

首先$O(nk)$是无法优化的，毕竟数组都有$nk$了

我们考虑如果优化计算$val(i,j)$

考虑一个数字对答案的贡献

**显然只有在$[pre[a[i]] + 1, i]$分段时$a[i]$才会对这里的答案有贡献**

其中$pre[a[i]]$表示$a[i]$上一次出现的位置

所以我们就可以用线段树优化求$max$

对于每个$f[i][j]$，先建树，权值为$f[i][j - 1]$

对于每一个$i$，$O(log_2n)$加上它对答案的贡献$val$，然后求$max(j - 1, i)$(很多题解直接求$[1, i]$其实也是对的，这题随着分的段数越多答案是不减的，实测都可以通过）

```cpp
#define int long long
#define mid ((l+r)>>1)
#define lson (o<<1)
#define rson (o<<1|1)
#define R register

const int N = 35555;

int n, k;
int f[N][55], pos[N], pre[N];
int tree[N << 2], lazy[N << 2];

inline void pushup(int o)
{
	tree[o] = max(tree[lson], tree[rson]);
}

inline void pushdown(int o)
{
	if(!lazy[o]) return;
	tree[lson] += lazy[o];
	tree[rson] += lazy[o];
	lazy[lson] += lazy[o];
	lazy[rson] += lazy[o];
	lazy[o] = 0;
}

inline void build(int o, int l, int r, int now)
{
	lazy[o] = 0;//记得每次清0！！
	if(l == r)
	{
		tree[o] = f[l - 1][now - 1];//在上一个k的基础上建树 
		return;
	}
	build(lson, l, mid, now);
	build(rson, mid + 1, r, now);
	pushup(o);
}

inline void add(int o, int l, int r, int ql, int qr, int val)
{
	if(ql <= l && r <= qr)
	{
		tree[o] += val;
		lazy[o] += val;
		return;
	}
	pushdown(o);
	if(ql <= mid) add(lson, l, mid, ql, qr, val);
	if(qr > mid) add(rson, mid + 1, r, ql, qr, val);
	pushup(o);
}

inline int query(int o, int l, int r, int ql, int qr)
{
	if(ql <= l && r <= qr) return tree[o];
	pushdown(o);
	int res = 0;
	if(ql <= mid) res = max(res, query(lson, l, mid, ql, qr));
	if(qr > mid) res = max(res, query(rson, mid + 1, r, ql, qr));
	return res;
}

signed main()
{
	read(n); read(k);
	for(R int i = 1, x; i <= n; i++)
	{
		read(x);
		pre[i] = pos[x] + 1;
		pos[x] = i;
	}
	for(R int j = 1; j <= k; j++)
	{
		build(1, 1, n, j);
		for(R int i = 1; i <= n; i++)
		{
			add(1, 1, n, pre[i], i, 1);
			if(j - 1 <= i) f[i][j] = query(1, 1, n, j - 1, i);//[1, i]也是对的 
		}
	}
	writeln(f[n][k]);
	return 0;
}
```

---

## 作者：crashed (赞：1)

# 题目
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[点这里](https://www.luogu.com.cn/problem/CF833B)看题目。  
# 分析
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;一个非常暴力的$O(kn^2)$的$dp$很好想：  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$f(i,j)$：前$j$个数分成$i$段的最大权值和。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;转移：
$$f(i,j)=\max_{i-1\le k<j}\{f(i-1,k)+w(k+1,j)\}$$  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$w(i,j)$表示$[i,j]$的权值，也就是$[i,j]$中不重复的数的数量。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;显然是$T$的。考虑优化。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;不难发现本题的难点在于求出$w$。不过，根据主席树求区间不重复数的数量的方法（不知道的可以先去百度），我们也可以不用主席树，用线段树在扫一遍的过程中动态更新出$w$的值。   
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;考虑当前扫到了$a_i$，上一次出现$a_i$的位置是$lst(a_i)$。那么之后对于所有$<i$的转移点，它们的$w$中都会统计上$a_i$。而之前$<lst(a_i)$实际上已经计算过一次$a_i$了，所以还要减掉一次。这样的区间操作可以用线段树。所以直接用线段树维护每一个转移点上的对应的转移值，最后查询最大值就可以了。时间是$O(knlog_2n)$。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;~~学了决策单调性的优化，但是还是不会用才这样写的......~~
# 代码
```cpp
#include <cmath>
#include <cstdio>

#define isLeaf( a ) ( segTree[a].l == segTree[a].r ) 

const int INF = 0x3f3f3f3f, MAXN = 35005, MAXK = 55;

template<typename _T>
void read( _T &x )
{
	x = 0; char s = getchar();int f = 1;
	while( s < '0' || '9' < s ) { f = 1; if( s == '-' ) f = -1; s = getchar(); }
	while( '0' <= s && s <= '9' ) { x = ( x << 3 ) + ( x << 1 ) + s - '0', s = getchar(); }
	x *= f;
}

template<typename _T>
void write( _T x )
{
	if( x < 0 ) { putchar( '-' ), x = -x; }
	if( 9 < x ) { write( x / 10 ); }
	putchar( x % 10 + '0' );
}

template<typename _T>
_T MIN( const _T a, const _T b )
{
	return a < b ? a : b;
}

template<typename _T>
_T MAX( const _T a, const _T b )
{
	return a > b ? a : b;
}

struct segmentTreeNode
{
	int l, r;
	int mx, tag;
}segTree[MAXN << 2];

int f[MAXK][MAXN];
int a[MAXN], lst[MAXN];
int N, K, siz;

void upt( const int now ) { segTree[now].mx = MAX( segTree[now << 1].mx, segTree[now << 1 | 1].mx ); }

void build( const int k, const int now, const int left, const int right )
{
	segTree[now].l = left, segTree[now].r = right, segTree[now].tag = 0;
	if( isLeaf( now ) ) { segTree[now].mx = f[k - 1][left]; return; }
	int mid = left + right >> 1;
	build( k, now << 1, left, mid ), build( k, now << 1 | 1, mid + 1, right );
	upt( now );
}

void add( const int now, const int val ) 
{
	segTree[now].tag += val, segTree[now].mx += val;
}

void normalize( const int now )
{
	if( ! segTree[now].tag ) return ;
	add( now << 1, segTree[now].tag ), add( now << 1 | 1, segTree[now].tag );
	segTree[now].tag = 0;
}

void update( const int now, const int segL, const int segR, const int val )
{
	if( segR < segTree[now].l || segTree[now].r < segL ) return ;
	if( segL <= segTree[now].l && segTree[now].r <= segR ) { add( now, val ); return ; }
	if( isLeaf( now ) ) return ; normalize( now );
	update( now << 1, segL, segR, val ), update( now << 1 | 1, segL, segR, val );
	upt( now );
}

int query( const int now, const int segL, const int segR )
{
	if( segR < segTree[now].l || segTree[now].r < segL ) return -INF;
	if( segL <= segTree[now].l && segTree[now].r <= segR ) return segTree[now].mx;
	if( isLeaf( now ) ) return -INF; normalize( now );
	int val = query( now << 1, segL, segR );
	return MAX( val, query( now << 1 | 1, segL, segR ) );
}

int main()
{
	read( N ), read( K );
	for( int i = 1 ; i <= N ; i ++ ) read( a[i] );
	for( int i = 1 ; i <= N ; i ++ ) f[0][i] = -INF;
	for( int j = 1 ; j <= K ; j ++ )
	{
		for( int i = 1 ; i <= N ; i ++ ) lst[i] = -1;
		build( j, 1, 0, N - 1 );
		for( int i = 1 ; i <= N ; i ++ )
		{
			if( ~ lst[a[i]] ) update( 1, 0, lst[a[i]] - 1, -1 );
			update( 1, 0, i - 1, 1 ), lst[a[i]] = i;
			if( i >= j ) f[j][i] = query( 1, j - 1, i - 1 );
			else f[j][i] = -INF;
		}
	}
	write( f[K][N] ), putchar( '\n' );
	return 0;
}
```

---

## 作者：Ouaoan (赞：1)

题目：[The Bakery](https://www.luogu.org/problemnew/show/CF833B)

[kevin_yu的题解](https://www.luogu.org/blog/105496/solution-cf833b)

之前没有好好听@kevin_yu讲题，做了一晚上……

这篇题解主要是对kevin_yu的补充以及代码注释的扩充，可能有助于大家的理解。



#### 思路：
---
##### part 1.dp
一个很容易想到的$O(n^2k)$算法——

令$f[i][j]$表示前i的位置划分j次的价值。

转移方程：

$f[i][j]=max \ (f[k][j-1]+cnt[k][i] )$

其中，k是一个中间值，代表划分枚举的位置。

然后，我们知道这样做一定会超时，所以我们需要优化。

---
##### part 2.线段树

我们选择优化转移，也就是说省去中间值k的枚举。

再看我们的转移方程，可以发现，我们取得是$f[k][j-1]+cnt[k][i]$这一段的最大值。

对于这种类型的取max的dp的优化，可以选择 单调队列优化 / nlogn数据结构优化。

如果使用单调队列，我们可以处理出$\ max\ {f[k][j-1]}$，但是$cnt[k][i]$这种数据却无法操作。

所以考虑数据结构，也就是动态区间最值的最简单工具——线段树。

令pre[i]表示上一次出现与i同颜色的蛋糕的位置。

假设我们在pre[i]和i之间取分割点k，那么末点在区间$[k,i]$间都是可以拥有col[i]的，而$[\ pre[i] , k)$这一段一定是没有col[i]的。

这样看，我们每次在线段树上更新$[pre[i],i]$，查询$[1,i]$就可以处理cnt的问题了。

而f[k][j-1]只需要在建树时加上就好。

具体实现见代码及注释——

---

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;

#define maxn 35000
#define maxm 50
#define read(x) scanf("%d",&x)

#define lson (o*2)
#define rson (o*2+1)
#define mid (L+(R-L)/2)

int n,m;	
int f[maxn+5][maxm+5];	//f[i][j]：前i的位置划分j次的价值 

int pre[maxn+5];	//上一次出现与i同颜色的蛋糕的位置
map<int,int> mp;	//用来更新pre 

//线段树部分 

int a[maxn*10+5];	//线段树 
int lzy[maxn*10+5];	//lazy tag

void push_up(int o) {	//通过子节点更新父节点的值 
	a[o]=max(a[lson],a[rson]);
}

void make_tree(int o,int L,int R,int row) {	//建树
	a[o]=lzy[o]=0; 
	if(L==R) {
		a[o]=f[L-1][row-1];
		return ;
	}
	make_tree(lson,L,mid,row),make_tree(rson,mid+1,R,row);
	push_up(o);
}

void push_down(int o) {	//下传lazy tag 
	a[lson]+=lzy[o],a[rson]+=lzy[o];
	lzy[lson]+=lzy[o],lzy[rson]+=lzy[o];
	lzy[o]=0;
}

int P,Q;	//修改及查询的区间 

void update(int o,int L,int R) {	//更新 
	if(L>Q||R<P) return ;
	if(L>=P&&R<=Q) {
		lzy[o]++;
		a[o]++;
		return ;
	}
	push_down(o);
	update(lson,L,mid),update(rson,mid+1,R);
	push_up(o);
}

int query(int o,int L,int R) {	//查询 
	if(L>Q||R<P) return 0;
	if(L>=P&&R<=Q) {
		return a[o];
	}
	push_down(o);
	return max(query(lson,L,mid),query(rson,mid+1,R));
}

int main() {
	read(n),read(m);
	for(int i=1;i<=n;i++) {
		int x;
		read(x);
		if(mp.count(x)) pre[i]=mp[x]+1;
		else pre[i]=1;
		mp[x]=i;
	}
	for(int j=1;j<=m;j++) {
		make_tree(1,1,n,j);
		for(int i=1;i<=n;i++) {
			P=pre[i],Q=i;
			update(1,1,n);
			P=1,Q=i;
			f[i][j]=query(1,1,n);
		}
	}
	
	printf("%d",f[n][m]);
	
	return 0;
}
```

---

