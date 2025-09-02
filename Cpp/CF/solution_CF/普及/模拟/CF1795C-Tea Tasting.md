# Tea Tasting

## 题目描述

A tea manufacturer decided to conduct a massive tea tasting. $ n $ sorts of tea will be tasted by $ n $ tasters. Both the sorts of tea and the tasters are numbered from $ 1 $ to $ n $ . The manufacturer prepared $ a_i $ milliliters of the $ i $ -th sort of tea. The $ j $ -th taster can drink $ b_j $ milliliters of tea at once.

The tasting will be conducted in steps. During the first step, the $ i $ -th taster tastes the $ i $ -th sort of tea. The $ i $ -th taster drinks $ \min(a_i, b_i) $ tea (how much is available of the $ i $ -th sort and how much the $ i $ -th taster can drink). $ a_i $ also decreases by this amount.

Then all tasters move to the previous sort of tea. Thus, during the second step, the $ i $ -th taster tastes the $ (i-1) $ -st sort of tea. The $ i $ -th taster drinks $ \min(a_{i-1}, b_i) $ tea. The $ 1 $ -st person ends the tasting.

During the third step, the $ i $ -th taster tastes the $ (i-2) $ -nd sort of tea. The $ 2 $ -nd taster ends the tasting. This goes on until everyone ends the tasting.

Take a look at the tasting process for $ n = 3 $ , $ a = [10, 20, 15] $ , $ b = [9, 8, 6] $ . In the left row, there are the current amounts of each sort of tea. In the right column, there are current amounts of tea each taster has drunk in total. The arrow tells which taster each tea goes to on the current step. The number on the arrow is the amount — minimum of how much is available of the sort of tea and how much the taster can drink.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1795C/470487c0e21724392d7014bece095c7efdff8422.png)For each taster, print how many milliliters of tea he/she will drink in total.

## 说明/提示

The first testcase is described in the statement. Here are the remaining amounts of each sort of tea after each step and the total amount of tea each taster has drunk:

- $ a = [1, 12, 9] $ , $ \mathit{ans} = [9, 8, 6] $
- $ a = [0, 6, 9] $ , $ \mathit{ans} = [9, 9, 12] $
- $ a = [0, 6, 9] $ , $ \mathit{ans} = [9, 9, 12] $

In the second testcase, the only taster drinks $ \min(5, 7) $ milliliters of tea of the only sort.

Here are the remaining amounts of each sort of tea after each step and the total amount of tea each taster has drunk for the third testcase:

- $ a = [10, 4, 3, 3] $ , $ \mathit{ans} = [3, 4, 2, 1] $ ;
- $ a = [6, 2, 2, 3] $ , $ \mathit{ans} = [3, 8, 4, 2] $ ;
- $ a = [4, 1, 2, 3] $ , $ \mathit{ans} = [3, 8, 6, 3] $ ;
- $ a = [3, 1, 2, 3] $ , $ \mathit{ans} = [3, 8, 6, 4] $ .

Here are the remaining amounts of each sort of tea after each step and the total amount of tea each taster has drunk for the fourth testcase:

- $ a = [999999999, 999999999, 0] $ , $ \mathit{ans} = [1, 1, 1000000000] $ ;
- $ a = [999999998, 0, 0] $ , $ \mathit{ans} = [1, 2, 1999999999] $ ;
- $ a = [0, 0, 0] $ , $ \mathit{ans} = [1, 2, 2999999997] $ .

## 样例 #1

### 输入

```
4
3
10 20 15
9 8 6
1
5
7
4
13 8 5 4
3 4 2 1
3
1000000000 1000000000 1000000000
1 1 1000000000```

### 输出

```
9 9 12 
5 
3 8 6 4 
1 2 2999999997```

# 题解

## 作者：ztlh (赞：7)

# Solution

考虑每杯茶对人的贡献。

不难发现，第 $i$ 杯茶会对从第 $i$ 人开始的若干个人产生贡献。

我们可以维护两个数组:

- $cnt_i$ 表示对第 $i$ 人产生完整贡献的次数。

- $ex_i$ 表示对第 $i$ 人产生的不完整贡献。

于是最终第 $i$ 人的答案就是 $cnt_i \times b_i + ex_i$。

先求出 $a_i$ 的前缀和 $s_i$。对于每一杯茶，我们可以二分找到它的贡献终止的地方（具体见代码）。设最后一个得到完整贡献的人下标为 $j$，则 $cnt_i$ 到 $cnt_j$ 整体加 $1$。$ex_{j+1}$ 要加上剩余的茶 $a_i - (s_j - s_{i-1})$。

由于 $cnt$ 只需区间加和一次查询，差分即可。

# Code

```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 200005
using namespace std;
int T,n;
ll a[N];
ll b[N];
ll s[N];
ll cnt[N];
ll ex[N];
int main(){
	scanf("%d",&T);
	while(T--){
		memset(cnt,0,sizeof(cnt));
		memset(ex,0,sizeof(ex));
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
			scanf("%lld",&a[i]);
		for(int i=1;i<=n;i++)
			scanf("%lld",&b[i]);
		for(int i=1;i<=n;i++)
			s[i]=s[i-1]+b[i];
		for(int i=1,l,r,mid;i<=n;i++){
			if(s[n]-s[i-1]<=a[i]){
				cnt[i]++;
				continue;
			}
			l=i; r=n;
			while(l<r){
				mid=l+r>>1;
				if(s[mid]-s[i-1]<=a[i]) l=mid+1;
				else r=mid;
			}
			l--;
			cnt[i]++; cnt[l+1]--;
			ex[l+1]+=a[i]-(s[l]-s[i-1]);
		}
		for(int i=1;i<=n;i++){
			cnt[i]+=cnt[i-1];
			printf("%lld ",cnt[i]*b[i]+ex[i]);
		}
		printf("\n");
	}
	return 0;
}
```

---

## 作者：daiarineko (赞：5)

# 题解【CF1795C Tea Tasting】

## 简要题意

共有 $n$ 个人和 $n$ 种茶，第 $i$ 个人每次可以喝 $b_i$ 单位的茶，而第 $j$ 种茶有 $a_i$ 单位。第 $t$ 周期时，第 $i(i\geq t)$ 人将品尝第 $(i-t+1)$ 种茶，而另外的人将不品尝任何茶。最后，求出每个人将喝到茶的单位数。这里，品尝的定义为：第 $i$ 人品尝第 $j$ 种茶，则第 $i$ 人喝到 $\min (b_i, a_j)$ 单位的茶，此后，$a_j \gets a_j-\min (b_i, a_j)$。

## 思路

直接这么做的话是 $O(n^2)$ 的，不能通过。换一种想法，考虑每种茶能够“活”到什么时候，换句话说就是它在第几个周期被喝完（使得 $a_i=0$）。

看一下样例给的图，我们能够发现，第 $i$ 种茶最多能被 $i\sim n$ 这些人品尝，而前 $(i-1)$ 人品尝不到这种茶。

则，我们需要查询第 $i$ 种茶的数量支持它从第 $i$ 人开始，最多能够被第 $x$ 人品尝。记 `ps[i][j]` 为从 $i$ 开始的对 $b$ 进行前缀和的数组，那么我们要查询的内容就相当于：

```cpp
x = lower_bound(ps[i] + i, ps[i] + 1 + n, a[i]) - ps[i];
```

这样做虽然将计算的时间复杂度降到了 $O(n\log n)$，但是预处理的时间复杂度和空间复杂度仍然是 $O(n^2)$ 的。还需要优化。

发现 `ps[i][j]` 这样写有些多余，考虑记 `PS[i] = ps[1][i]`：

$$ps_{i,x} \geq a_i \iff PS_x-PS_{i-1}\geq a_i \iff PS_x\geq a_i+PS_{i-1}$$

`lower_bound` 的定义就是对于待查询的 $k$，找到第一个数值 $x$ 使得 $x\geq k$。因此利用以上推论，之前的代码可以修改成：

```cpp
x = lower_bound(PS + i, PS + 1 + n, PS[i - 1] + a[i]) - PS;
```

这样，预处理的时空复杂度都被优化成了 $O(n)$。

查询的方式就是这样。之后，考虑如何求出第 $i$ 种茶对答案的贡献。

> 我们需要查询第 $i$ 种茶的数量支持它从第 $i$ 人开始，最多能够被第 $x$ 人品尝。

那么，第 $x$ 人不一定能品尝到 $b_x$ 单位，因为茶在此刻可能并不足够。他实际能品尝到多少单位呢？设他能品尝到 $y$ 单位，则：

$$y + ps_{i,x-1} = a_i \iff y + PS_{x-1} - PS_{i-1} = a_i \iff y = a_i - PS_{x-1} + PS_{i-1}$$

根据这个式子，第 $x$ 人品尝的单位数就可以计算了。当然，对于第 $j(j\in [i, x-1])$ 个人，他所能品尝到的单位数即为 $b_j$。

最后，如何把贡献合并呢？

我的做法是，分整块和散点计算。对于第 $i$ 个人，“整块”即为使得他能品尝到 $b_i$ 单位的茶，“散点”相对整块，即为除整块外，能够让他品尝到的茶。

每种茶最多产生一个散点，可以暴力存储散点之和。

每种茶会产生多个整块，但这些整块必然是连续的。所以这相当于区间加、单点查询的操作，我赛时是利用差分树状数组维护的。（显然不用这么麻烦，因为全部修改完才会查询，可以先对差分数组修改，再 $O(n)$ 求出差分的前缀和即原数组）

设第 $i$ 个人的整块个数为 $k$，散点之和为 $l$，他的答案即为 $k b_i + l$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int T, n, a[200005], b[200005], s[200005], ful[200005], ex[200005];
int lowbit(int u) { return u & (-u); }
void update(int u, int w)
{
  for (int i = u; i <= n; i += lowbit(i))
    ful[i] += w;
}
int query(int u)
{
  int w = 0;
  for (int i = u; i; i -= lowbit(i))
    w += ful[i];
  return w;
}
signed main()
{
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> T;
  while (T--)
  {
    cin >> n;
    for (int i = 1; i <= n; ++i)
      cin >> a[i];
    for (int i = 1; i <= n; ++i)
      cin >> b[i], ful[i] = 0, ex[i] = 0, s[i] = s[i - 1] + b[i];
    s[n + 1] = s[n];
    for (int i = 1; i <= n; ++i)
    {
      int k = lower_bound(s + 1, s + 1 + n, s[i - 1] + a[i]) - s; // 题解中的 x
      int x = a[i] + s[i - 1] - s[k - 1]; // 题解中的 y
      update(i, 1);
      if (k <= n) // 有可能一种茶能支持所有人品尝，此时不需要把差分减回来，也不需要处理散点
      {
        update(k, -1);
        ex[k] += x;
      }
    }
    for (int i = 1; i <= n; ++i)
    {
      cout << b[i] * query(i) + ex[i] << ' ';
    }
    cout << '\n';
  }
  cout.flush();
  return 0;
}
```


---

## 作者：ダ月 (赞：3)

### 前置知识：

二分查找，前缀和，差分。

### 题目分析：

考虑暴力的话，就是模拟题意。但是这是 CF，你得不了分数。考虑优化。

我们可以注意到，每个 $a_i$ 可以对它所在的下标后面的数产生贡献，其中一部分贡献是完整的 $b_i$，一部分是剩余的。我们对 $b_i$ 做前缀和，然后用二分查找找到完整与剩余的分界线。对于完整的贡献，我们用差分记录次数，非完整的贡献，记录一个数组。最后答案就是一个数的完整贡献次数乘上 $b_i$，加上非完整贡献。

### 代码如下：

```
#include<bits/stdc++.h>
using namespace std;
int T;
int n;
typedef long long ll;
const int N=2e5+10;
ll a[N];
ll k[N];
ll s[N];
ll b[N];
ll ans[N];
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			scanf("%lld",&a[i]);
			b[i]=s[i]=ans[i]=0;
		}
		for(int i=1;i<=n;i++) scanf("%d",&k[i]);
		for(int i=1;i<=n;i++) s[i]=s[i-1]+k[i];
		for(int i=1;i<=n;i++){
			int pos=lower_bound(s+i,s+n+1,a[i]+s[i-1])-s;
			b[pos]--;b[i]++;ans[pos]+=a[i]-(s[pos-1]-s[i-1]);
		}for(int i=1;i<=n;i++) b[i]+=b[i-1];
		for(int i=1;i<=n;i++)
			printf("%lld ",ans[i]+b[i]*k[i]);
		puts("");
	}return 0;
} 
```

时间复杂度：$O(n\log n)$。

注意：答案很大，要开 ```long long```。


---

## 作者：HJY202three (赞：2)

稍微写一下。

由于本人比较笨，所以写的方法比较暴力。

考虑每次删除所有小于 $x_i$ 的茶。

维护一个 $dx$ 表示当前 $x_1+x_2+...+x_i$。每个 $b_j \leq dx$ 都会在本轮被喝光，所以这一部分的贡献是 $sum-num \times dx$，对于每个 $b_j \geq dx$，会被喝 $x_i$ 所以贡献为 $num \times x_i$。

对于新加入的一杯茶，大小应为 $b_i+dx$ 。

用平衡树维护即可，时间复杂度 $O(n \log n)$ 。

code:
```cpp
#include<iostream>
#include<cstring>
using namespace std;
#define int long long
const int MX=3e5+7;
int a[MX],b[MX],ans[MX];
struct node{
	int l,r,v,t,sum,h;
}s[MX*2];
int tNode=0,root=0;
int new_node(int x){
	s[++tNode].v=x;
	s[tNode].l=s[tNode].r=0;
	s[tNode].t=1;
	s[tNode].sum=x;
	s[tNode].h=rand();
	return tNode;
}
void upd(int x){
	s[x].t=s[s[x].l].t+s[s[x].r].t+1;
	s[x].sum=s[s[x].l].sum+s[s[x].r].sum+s[x].v;
}
int merge(int x,int y){
	if(x==0||y==0)return x|y;
	if(s[x].h<s[y].h){
		s[x].r=merge(s[x].r,y);
		upd(x);
		return x;
	}
	else{
		s[y].l=merge(x,s[y].l);
		upd(y);
		return y;
	}
}
void split(int root,int k,int &x,int &y){
	if(root==0)x=y=0;
	else{
		if(s[root].v<=k)	
			x=root,split(s[root].r,k,s[root].r,y);
		else
			y=root,split(s[root].l,k,x,s[root].l);
		upd(root);
	}
}
int kth(int root,int k){
	if(root==0||k==0)return 0;
	while(1){
		if(s[s[root].l].t+1==k)return root;
		if(k<=s[s[root].l].t)root=s[root].l;
		else k-=s[s[root].l].t+1,root=s[root].r;
	}
}
signed main(){
	int T;
	cin>>T;
	while(T--){
		int n,k,l,r,x,y,z;
		cin>>n;
		for(int i=1;i<=n;i++)cin>>a[i];
		for(int i=1;i<=n;i++)cin>>b[i];
		int dx=0;
		root=tNode=s[0].sum=s[0].v=0;
		for(int i=1;i<=n;i++){
			split(root,a[i]+dx,x,y);
			root=merge(x,merge(new_node(a[i]+dx),y));
			split(root,b[i]+dx,x,y);
			ans[i]=s[x].sum-s[x].t*dx+s[y].t*b[i];
		//	cout<<"i: "<<i<<" dx: "<<dx<<" s[x].sum "<<s[x].sum<<" s[y].t: "<<s[y].t<<endl;
			root=y;
			dx+=b[i]; 
		}
		for(int i=1;i<=n;i++)cout<<ans[i]<<' ';
		cout<<endl;
	}
	return 0;
}


```

---

## 作者：Hanx16Kira (赞：2)

# Tea Tasting

[Luogu CF1795C](https://www.luogu.com.cn/problem/CF1795C)

## 简要题意

> 有 $n$ 杯茶和 $n$ 个评委，$i$ 杯茶有 $a_i$ 的量，评委 $i$ 每次最多喝 $b_i$ 的茶。开始的时候评委 $i$ 对应茶 $i$，喝完一次过后评委 $i$ 移到 $i-1$ 的位置，然后继续上述操作，直到评委 $n$ 喝完了所有的茶。求每个评委喝了多少茶。

## Solution

可以考虑算出评委喝茶量的前缀和，然后对于每一杯茶，都可以二分找到是被哪一个评委喝完的，记茶 $i$ 被喝完的位置是 $\text{pos}_i$，那么对于 $j\in[i,\text{pos}_i)$ 的评委 $j$，喝这杯茶的量都会是 $b_j$。

那么得到一个做法，从 $1\sim n$ 地加入每一杯茶和每一个评委，对于评委 $j$，能对这个评委产生 $b_j$ 贡献的茶 $i$，一定满足 $\text{pos}_i>j$ 且 $i\le j$，这就是一个二维数点问题，用树状数组解决即可。

### Code

```cpp
#include<bits/stdc++.h>
#define int long long

using namespace std;

constexpr int _SIZE = 2e5;
int n, a[_SIZE + 5], b[_SIZE + 5], sum[_SIZE + 5]; 
int ans[_SIZE + 5], pos[_SIZE + 5];
int s[_SIZE + 5];

#define lowbit(_) (_ & -_)
#define Sum(l, r) (sum[r] - sum[l - 1])

void Modify(int x, int v) {
	for (; x <= n + 1; x += lowbit(x)) s[x] += v;
}

int Query(int x) {
	int res = 0;
	
	for (; x; x -= lowbit(x)) res += s[x];
	
	return res;
}

void Solve() {
	cin >> n;
	
	for (int i = 1; i <= n; ++i) ans[i] = s[i] = 0;
	
	for (int i = 1; i <= n; ++i)
		cin >> a[i];
	
	for (int i = 1; i <= n; ++i)
		cin >> b[i], sum[i] = sum[i - 1] + b[i];
	
	for (int i = 1; i <= n; ++i) {
		int l = i, r = n;
		
		while (l <= r) {
			int mid = (l + r) >> 1;
			
			if (Sum(i, mid) < a[i]) l = mid + 1;
			else r = mid - 1;
		}
		
		ans[r + 1] += a[i] - Sum(i, r); // 会对评委 r + 1 产生的贡献
		pos[i] = r + 1;
	}
	
	for (int i = 1; i <= n; ++i) {
		Modify(pos[i], 1); // 茶 i 会对评委 i 产生贡献
		int tmp = i - Query(i); // 对评委 i 产生 b_i 贡献的数量
		cout << tmp * b[i] + ans[i] << ' ';
	}
	
	cout << '\n';
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int T; cin >> T;
	
	while (T--) Solve();
}
```

---

## 作者：kjhhjki (赞：1)

## 【题意简述】
  有 $n$ 杯茶 $\{a_n\}$ 和 $n$ 个人喝茶，第 $i$ 个人从第 $i$ 杯茶向前喝，每次可以喝 $b_i$ ，求每个人最多喝多少。
## 【思路】
  记录每个人的杯数 $c_i$ 和因为各种因素少喝的毫升数 $d_k$ 。显然，在每杯茶都够的情况下第 $i$ 个人能喝 $i$ 杯。
  
  
  对于每一杯茶 $a_i$ ，如果它足够多，那么后面每个人都能喝满 $b_i$ ，不会对我们的结果有影响，跳过；反之必然有一个人 $k$ ，他刚好喝完，那么后面的人少喝一杯，即 $c_j,j \in [k+1,n]$ 减1，他自己杯数不变，但少喝 $b_k-a_i'$ （ $a_i'$ 为轮到他时剩下的数量），记录到 $d_k$ 中。
  
  由于 $b_i$ 为正，所以其前缀和单增，于是可以利用前缀和二分进行查找 $k$ 。用树状数组或者线段树维护 $c_i$ ，最后输出 $b_i \times c_i - d_i$ 。总复杂度 $O(nlogn)$ 。
  
  Code:

```cpp
#include<bits/stdc++.h>
#define MAXN 200005
typedef long long _ll;
using namespace std;
 
class Seg_Tree
{
    private:
        struct node { _ll plt,sum; } a[MAXN<<2];
    public:
        void build(int i, int l, int r);
        inline void pushdown(int i, int l, int r);
        inline void pushup(int i) { a[i].sum = a[i<<1].sum+a[i<<1^1].sum; }
        void add(int i, int l, int r, int x, int y, _ll k);
        _ll query(int i, int l, int r, int x, int y);
};
void Seg_Tree::build(int i, int l, int r)
{
    a[i].plt = 0;
    if(l==r) { a[i].sum = l; return; }
    int mid = l + r >> 1;
    build(i<<1,l,mid); build(i<<1^1,mid+1,r);
    pushup(i);
}
inline void Seg_Tree::pushdown(int i, int l, int r)
{
    int p = a[i].plt, mid = l + r >> 1;
    a[i<<1].sum += p*(mid-l+1); a[i<<1^1].sum += p*(r-mid);
    a[i<<1].plt += p; a[i<<1^1].plt += p;
    a[i].plt = 0;
}
void Seg_Tree::add(int i, int l, int r, int x, int y, _ll k)
{
    if(x<=l && r<=y) { a[i].sum += k*(r-l+1); a[i].plt += k; return; }
    int mid = l + r >> 1; pushdown(i,l,r);
    if(x <= mid) add(i<<1,l,mid,x,y,k);
    if(y >  mid) add(i<<1^1,mid+1,r,x,y,k);
    pushup(i);
}
_ll Seg_Tree::query(int i, int l, int r, int x, int y)
{
    if(x<=l && r<=y) return a[i].sum;
    int mid = l + r >> 1; pushdown(i,l,r);
    _ll res = 0ll;
    if(x <= mid) res += query(i<<1,l,mid,x,y);
    if(y >  mid) res += query(i<<1^1,mid+1,r,x,y);
    return res;
}
 
_ll t,n,pos,a[MAXN],b[MAXN],d[MAXN],s[MAXN];
_ll find(int i)
{
    int l = i, r = n, mid;
    while(l < r)
    {
        mid = l + r >> 1;
        if(s[mid]-s[i-1] ==a[i]) return mid;
        if(s[mid]-s[i-1] > a[i])  r = mid;
        else l = mid + 1;
    }
    return l;
}
void solve()
{
    cin >> n; Seg_Tree st; memset(d,0,sizeof(d));
    for(int i = 1; i <= n; ++i)
        scanf("%lld",a+i);
    for(int i = 1; i <= n; ++i)
        scanf("%lld",b+i),s[i]=b[i]+s[i-1];
    st.build(1,1,n);
    for(int i = 1; i <= n; ++i)
    {
        if(a[i] >= s[n]-s[i-1]) continue;
        pos = find(i);
        if(pos < n) st.add(1,1,n,pos+1,n,-1);
        d[pos] += b[pos]-(a[i]-(s[pos-1]-s[i-1]));
    }
    for(int i = 1; i <= n; ++i)
        printf("%lld ",st.query(1,1,n,i,i)*b[i]-d[i]);
    cout << endl;
}
 
int main()
{
    cin >> t;
    while(t--) solve();
    return 0;
}
```


---

## 作者：lizhous (赞：1)

[洛谷](https://www.luogu.com.cn/problem/CF1795C)

[CF](http://codeforces.com/problemset/problem/1795/C)

## 分析

数据范围显然需要复杂度为 $O(n)$。

考虑对于每个茶考虑。它一定会从他开始往后一段人做出完整贡献（喝到 $b_i$），然后为一个人做出不完整贡献，最后几个人不做出贡献。

对喝茶量前缀和，二分第一段贡献的终止点，可以计算第二段贡献的量。但是我们不能实时更改答案。

发现 $b_i$ 是固定的。我们需要知道的只是一个点受到多少次完整贡献，可以使用差分前缀和。而第二段的贡献只会有 $n$ 个，直接修改即可。

## 代码

关键部分

```cpp
for(int i=1;i<=n;i++)
{
	if(s[n]<=a[i]+s[i-1]) continue;
	int w=lower_bound(s+1,s+n+1,a[i]+s[i-1])-s;
	jian[w]++;
	ex[w]+=a[i]-s[w-1]+s[i-1]; 
}
for(int i=1;i<=n;i++)
{
	jian[i]+=jian[i-1];
	printf("%lld ",b[i]*(i-jian[i])+ex[i]);
}
```

---

## 作者：qzhwlzy (赞：0)

[题目](https://codeforces.com/contest/1795/problem/C)

### 大意

有 $n$ 个人和 $n$ 杯茶，第 $i$ 杯茶的体积为 $a_i$，第 $i$ 个人一次最多能喝 $b_i$ 单位体积的茶。初始第 $i$ 个人站在第 $i$ 杯茶前。之后每个人会喝面前的茶 $\min(a_i,b_i)$ 单位体积，然后每个人向前移一位，移出去的人就结束品茶，问每个人能喝到多少体积的茶。

### 思路

暴力显然是 $\mathcal{O}(n^2)$ 的，枚举每杯茶不断往后被喝，直到结束。

暴力过程中，我们发现，对于第 $i$ 杯茶，它一定被第 $i$ 个人喝 $b_i$ 体积，再被第 $i+1$ 个人喝 $b_{i+1}$ 体积，……，被第 $j-1$ 个人喝 $b_{j+1}$ 体积，剩下的全被第 $j$ 个人喝了。也就是说，把 $a_i$ 分解为 $b_{i}+b_{i+1}+\ldots+b_{j-1}+res$（$res < b_{j}$）。所以，第 $i$ 杯茶对其之后连续的一段人 $i\sim (j-1)$ 有着相应的“完整的” $b$ 的贡献，对第 $j$ 个人有着“零散的”贡献。

---

对于如何处理 $j$，我们可以预处理出 $b$ 的前缀和 $B$，在其中搜最小的大于 $a_i + b_{i-1}$ 的 $B_j$。（关于为什么要加 $b_{i-1}$，是因为我们要找第一个满足 $\sum\limits_{p=i}^{j} > a_i$，也就是 $B_j = \sum\limits_{p=1}^j > a_i + \sum\limits_{p=1}^{i-1} = a_i + B_{i-1}$）。这一点我们可以用二分或者 `lower_bound` 函数来实现。

对于如何统计答案，我们开两个数组 $r$ 和 $ans$ 分别统计“完整的”和“零散的”答案。对 $a_i$ 搜到 $j$ 时，将 $ans_j$ 加上 $a_i - \sum\limits_{p=i}^{j-1} = a_i - (B_{j-1} - B_{i-1})$；还需要将 $r_i\sim r_{j-1}$ 加上 $1$，那么这样就需要维护区间和的数据结构例如树状数组，利用差分思想，用 $res$ 表示 $r$ 的差分数组，$r$ 就是 $res$ 的前缀和，这样将 $res_i$ 加一，$res_j$ 减一即可。

最后第 $i$ 个人的答案自然就是 $r_i\times b_i + ans_i = \sum\limits_{p=1}^i res_p\times b_i + ans_i$ 了。

---

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#define maxn 200005
#define ll long long
using namespace std;
int T,n,a[maxn],res[maxn]; ll b[maxn],ans[maxn];
int main(){
    scanf("%d",&T); while(T--){
        scanf("%d",&n); for(int i=1;i<=n;i++){scanf("%d",&a[i]); res[i]=ans[i]=0;}
        for(int i=1;i<=n;i++){scanf("%lld",&b[i]); b[i]+=b[i-1];}
        for(int i=1;i<=n;i++){
            int pos=lower_bound(b+1,b+1+n,a[i]+b[i-1])-b;
            res[i]++; res[pos]--; ans[pos]+=a[i]-(b[pos-1]-b[i-1]);
        } ll sum=0LL; for(int i=1;i<=n;i++){sum+=res[i]; printf("%lld ",sum*(b[i]-b[i-1])+ans[i]);} printf("\n");
    } return 0;
}
```

---

## 作者：FatOldEight (赞：0)


## 分析


正面想每个人能喝多少有点困难，但是可以从另一个方面想一杯茶能给多少人喝就做出来了。

不难理解，固定 $l$，$l$ 到 $r$ 的人喝的总量随着 $r$ 的增大而增大。

于是我们可以二分一杯茶可以提供给多少人喝，剩下的加到后面第一个没喝到的人头上。

要用前缀和和差分优化时间复杂度。

总体复杂度 $O(n\log{n})$，详情见代码注释。

## 代码
``` cpp
#include<iostream>
#define int long long
using namespace std;
int a[500005],s[500005],n,T,d[500005],f[500005],ans[500005];
signed main()
{
    scanf("%lld",&T);
    while(T--)
    {
        
        scanf("%lld",&n);
        for(int i=1;i<=n;i++)scanf("%lld",&a[i]),f[i]=ans[i]=0;
        for(int i=1;i<=n;i++)scanf("%lld",&s[i]);
        for(int i=1;i<=n;i++)d[i]=d[i-1]+s[i];//前缀和优化
        for(int i=1;i<=n;i++)
        {
            int l=i,r=n,mid,cnt=-1;//二分主体
            while(l<=r)
            {
                mid=(l+r)>>1;
                if(d[mid]-d[i-1]<=a[i])
                {
                    l=mid+1;
                    cnt=mid;
                }
                else r=mid-1;
            }
            if(cnt!=-1)//记得特判一个人也不够
            {
                f[i]++;
                f[cnt+1]--;//差分优化
                ans[cnt+1]+=a[i]-d[cnt]+d[i-1];
            }
            else ans[i]+=a[i];
        }
        for(int i=1;i<=n;i++)f[i]+=f[i-1];//输出
        for(int i=1;i<=n;i++)printf("%lld ",ans[i]+f[i]*s[i]);
        puts("");
    }
}
```

---

