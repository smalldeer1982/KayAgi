# [ARC179E] Rectangle Concatenation

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc179/tasks/arc179_e

正整数 $ h,w $ に対し, 縦の辺の長さが $ h $, 横の辺の長さが $ w $ であるような長方形を $ (h,w) $ と表すことにします. なお, 本問では長方形を回転する操作は考えず, $ h\neq\ w $ のとき長方形 $ (h,w) $ と長方形 $ (w,h) $ は異なるものとして扱います.

長方形の列 $ ((h_1,w_1),(h_2,w_2),\dots\ ,(h_n,w_n)) $ が **長方形生成列** であるとは, 次の手順が成功するような方法が存在することを言います.

- 長方形 $ X $ を $ (h_1,w_1) $ とする. 以下では, 各時点での長方形 $ X $ の縦の辺の長さと横の辺の長さをそれぞれ $ H,W $ と表す.
- $ i=2,3,\dots\ ,n $ の順に次のいずれか一方の操作を行う. いずれも行うことができないとき手順は失敗とし, 手順を終了する.
  - $ X $ の縦の辺の長さが $ h_i $ に等しいとき, $ X $ に長方形 $ (h_i,w_i) $ を横向きに結合する. 正確には, その時点で $ H=h_i $ のとき $ X $ を長方形 $ (H,W+w_i) $ に置き換える.
  - $ X $ の横の辺の長さが $ w_i $ に等しいとき, $ X $ に長方形 $ (h_i,w_i) $ を縦向きに結合する. 正確には, その時点で $ W=w_i $ のとき $ X $ を長方形 $ (H+h_i,W) $ に置き換える.
- 上記の一連の操作が失敗しなかった場合は手順は成功とし, 手順を終了する.
 
- - - - - -

$ N $ 個の長方形が与えられます. $ i $ 番目の長方形は, 縦の辺の長さが $ H_i $, 横の辺の長さが $ W_i $ の長方形です.

$ 1\le\ l\le\ r\le\ N $ を満たす正整数の組 $ (l,r) $ であって次の条件を満たすものの個数を求めてください.

- 長方形の列 $ ((H_l,W_l),(H_{l+1},W_{l+1}),\dots\ ,(H_r,W_r)) $ が長方形生成列である.

## 说明/提示

### 制約

- $ 1\leq\ N\leq\ 3\times\ 10^5 $
- $ 1\ \leq\ H_i,W_i\ \leq\ 10^6 $
- 入力される値はすべて整数.
 
### Sample Explanation 1

条件を満たす $ (l,r) $ は $ (1,1),(1,2),(2,2),(2,3),(2,4),(3,3),(4,4) $ の $ 7 $ つです. 例えば, $ (l,r)=(2,4) $ については, 結合を縦向き $ \to $ 横向きの順に行うと手順が成功します.

## 样例 #1

### 输入

```
4
1 2
1 3
2 3
3 1```

### 输出

```
7```

## 样例 #2

### 输入

```
5
2 1
2 1
1 2
3 2
1 4```

### 输出

```
10```

## 样例 #3

### 输入

```
1
1000000 1000000```

### 输出

```
1```

## 样例 #4

### 输入

```
10
1 1
1 1
1 1
1 1
1 1
1 1
1 1
1 1
1 1
1 1```

### 输出

```
55```

# 题解

## 作者：Talaodi (赞：12)

一个好想好写的 $O(N)$ 做法。

先思考 $O(N^2)$ 怎么做。枚举一个 $l$，设 $S_r$ 为 $[l,r]$ 的面积和，发现以 $r$ 为右端点只可能有两种合法的矩形。

考虑递推，设 $f_{r,0/1}$ 表示以 $r$ 为右端点能不能横着或竖着放。有递推式：

$$
f_{r,0}=(f_{r-1,0}\land x_r=x_{r-1})\lor(f_{r-1,1}\land x_r=\frac{S_{r-1}}{y_{r-1}})
$$
$$
f_{r,1}=(f_{r-1,1}\land y_r=y_{r-1})\lor(f_{r-1,0}\land y_r=\frac{S_{r-1}}{x_{r-1}})
$$

考虑优化。

我们转而枚举 $r$，分别维护 $f_{r,0}$ 合法和 $f_{r,1}$ 合法的 $l$。发现两个式子的第一部分要么清空要么继承，而第二部分对 $S$ 有唯一的限制，因此只会涉及到一个地方的值。

所以总的修改量是 $O(N)$ 的，可以直接用数组模拟，暴力操作维护出两个集合并的大小。

此外，还需要用 hash 表找到第二部分修改的位置。

总复杂度 $O(N)$。

---

## 作者：vegetable_king (赞：5)

[可能更孬的阅读体验](https://yjh965.github.io/post/arc179e-rectangle-concatenation-ti-jie/)

场上没调出来，写个题解纪念一下。来一个值域无关的线性做法。

统计区间数量，一个经典的套路是考虑扫描线。

具体地，我们将右端点 $r$ 从左往右扫，并同时对于所有 $1 \le l \le r$ 的左端点 $l$，维护区间 $[l, r]$ 能生成的所有矩形。即，我们需要维护一个若干个三元组构成的集合 $S$，其中，$S$ 中的一个三元组 $(h, w, l)$ 代表区间 $[l, r]$ 能够生成矩形 $(h, w)$。

每次 $r \to r + 1$ 时，我们先更新 $S$ 内的所有三元组，丢掉不合法的，并加入 $[r, r]$ 所对应的集合 $(h_r, w_r, r)$，最后令 $ans \gets ans + cnt$。其中 $cnt$ 为集合内本质不同的左端点个数。

考虑形式化我们要支持的具体操作：

> 给你两个数 $H, W$，你要进行以下操作：
>
> 1. 新建一个集合 $S'$，并将 $(H, W, r)$ 加入 $S'$。
> 2. 对于 $S$ 内的每个三元组 $(h, w, l)$，你要执行以下操作：
>    - 若 $h = H, w = W$，将 $(2h, w, l), (h, 2w, l)$ 加入 $S'$。
>    - 若 $h = H, w \ne W$，将 $(h, w + W, l)$ 加入 $S'$。
>    - 若 $h \ne H, w = W$，将 $(h + H, w, l)$ 加入 $S'$。
>    - 若 $h \ne H, w \ne W$，则什么都不做。
> 3. 令 $S \gets S'$。

这个操作看起来很棘手，不好快速维护。所以我们考虑发掘一些性质；具体地，我们注意到，对于刚进行过 $H, W$ 操作得到的集合 $S$ 中的每一个三元组 $(h, w, l)$，一定有 $h = H$ 或 $w = W$。于是我们维护的东西一下就从二维的形式变成一维的形式了。

我们考虑换一下维护方式，转为维护两个若干个二元组构成的集合 $Sw, Sh$，并且记录 $lh, lw$ 分别为上次操作的 $H, W$。类似的，其中 $Sw$ 中的一个二元组 $(h, r)$ 代表区间 $[l, r]$ 能够生成矩形 $(h, lw)$，$Sh$ 中的一个二元组 $(w, r)$ 代表区间 $[l, r]$ 能够生成矩形 $(lh, w)$。那么我们可以直接维护了：

1. $H = lh, W = lw$。我们事先将 $(H, l), (W, l)$ 分别从 $Sw, Sh$ 里删除，这样就可以直接分别给 $Sh, Sw$ 两个集合打上整体加的 tag，最后再将 $(2H, l), (2W, l)$ 分别加入 $Sw, Sh$ 里即可。

2. $H = lh, W \ne lw$。类似地，事先将 $(W, l)$ 从 $Sh$ 里删除，给 $Sh$ 打上整体加的 tag；而对于 $Sw$，我们注意到 $Sw$ 在操作后至多会有 $O(1)$ 个元素，所以我们直接暴力清空 $Sw$，最后再将 $(2H, l), (2W, l)$ 分别加入 $Sw, Sh$ 里即可。$H \ne lh, W = lw$ 的情况是等价的。

3. $H \ne lh, W \ne lw$。这样，$Sh, Sw$ 在操作后都至多会有 $O(1)$ 个元素，所以类似地暴力清空即可。

注意到上述过程中每次只会插入 $O(1)$ 次，删除总共 $O(n)$ 次，均摊 $O(1)$ 次。并且当我们要删除元素时，要么只删除 $O(1)$ 个元素，要么只剩 $O(1)$ 个元素，所以被我们访问到但不被删去的元素个数每次是 $O(1)$ 的。

所以总插入删除访问次数是 $O(n)$ 的。直接使用两个哈希表维护，同时开一个桶记录左端点为 $l$ 的三元组的出现次数，即可做到 $O(n)$。如果手写哈希表记得不要用 `memset` 清空 `head` 数组，要对于已插入的元素手动清空。

[code](https://atcoder.jp/contests/arc179/submissions/54205319)

---

## 作者：Eraine (赞：4)

编号：AT_arc179_e

tag：set

难度：*2818（$\texttt{Clist}$ 数据）

本篇题解大致与 @UniGravity 的思路相同，主要提供一个较为简洁的实现方式。具体的思路可以参考 @UniGravity 的题解。

由于右端点到 $i$ 的生成矩阵必定至少满足 $h=h_i$ 和 $w=w_i$ 两个条件之一，而从 $i-1$ 转移的矩阵只有两种情况（只讨论 $h$，$w$ 是对称的），一种是 $h_{i-1}=h_i$，那直接继承 $i-1$ 的矩阵即可；一种是 $h_{i-1}\neq h_i$，对于 $i-1$ 的矩阵可以直接丢掉。新增 $i$ 矩阵即可。还有一种情况是从 $w$ 的矩阵里找到 $h=h_i$ 的矩阵加入。大抵就做完了。维护 $ans$ 只需开个桶（注意要区别 $h$ 和 $w$ 所以每一个元素要开两个桶）。

$\Theta(n\log n)$。

接下来的部分是对代码实现的讲解，直接贴代码，讲解在代码部分。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=1e6+5;
int n;
set<ll>s1,s2;
ll h[N],w[N],tag1,tag2,f[N];
// tag1,tag2 是 H 和 W 的标记
// 注意这里 h[i] 和 w[i] 是真实的 h[i] 和 w[i] 分别减去 tag1 和 tag2
int res,cnt[2][N];
void add(int x,int type){// 对于元素 x 的 type(H/W) 桶增加元素，del 减少
    if(!cnt[0][x]&&!cnt[1][x]){
        ++res;
    }
    ++cnt[type][x];
}
void del(int x,int type){
    --cnt[type][x];
    if(!cnt[0][x]&&!cnt[1][x]){
        --res;
    }
}
map<ll,int>mp;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d%d",&h[i],&w[i]);
        f[i]=f[i-1]+h[i]*w[i];
        mp[f[i]]=i;// 提前存好 [1,i] 的面积和
    }
    ll ans=0;
    for(int i=1;i<=n;i++){
        bool flag1=0,flag2=0;
        if(s2.count(tag2-h[i])){
            flag1=1;
        }// H = h_i 的矩阵从 i-1 的 W 矩阵集合转移而得
        if(s1.count(tag1-w[i])){
            flag2=1;
        }// W = w_i 的矩阵从 i-1 的 H 矩阵集合转移而得
        if(h[i]!=h[i-1]){// 全部删掉
            for(auto x:s1){
                del(mp[f[i-1]-h[i-1]*(tag1-x)]+1,1);// mp 方便知道总面积以后求得坐标
            }
            s1.clear();
            tag1=0;// 更新标记
        }
        if(flag1&&!cnt[1][mp[f[i-1]-h[i]*w[i-1]]+1]){
            add(mp[f[i-1]-h[i]*w[i-1]]+1,1);
            s1.insert(tag1-w[i-1]);
        }// 注意要判断是否已经存在，有可能出现矩阵 (h[i],w[i-1]) 已经出现在 i-1 的 H 集合里的情况
        add(i,1);// 增加 i 矩阵
        s1.insert(tag1);
        tag1=tag1+w[i];
        if(w[i]!=w[i-1]){
            for(auto x:s2){
                del(mp[f[i-1]-w[i-1]*(tag2-x)]+1,0);
            }
            s2.clear();
            tag2=0;
        }
        if(flag2&&!cnt[0][mp[f[i-1]-w[i]*h[i-1]]+1]){
            add(mp[f[i-1]-w[i]*h[i-1]]+1,0);
            s2.insert(tag2-h[i-1]);
        }
        add(i,0);
        s2.insert(tag2);
        tag2=tag2+h[i];
        ans=ans+res;// 更新答案
    }
    printf("%lld\n",ans);
    return 0;
}
```

若有疑问和错误请指出，虚心接受您的意见。

---

## 作者：Register_int (赞：1)

我没有脑子，所以写了这个唐诗做法。

容易发现方案数至多为 $2$，因为最终的面积大小是固定的，至少一条边是固定的。

数区间问题考虑分治。对于分治中心右侧，可以对于每个前缀处理出 $(x,y,dx,dy)$，表示：若初始矩形边长为 $(x,y)$，那么这段前缀的矩形都能加上去，最终的效果是 $(x,y)\to(x+dx,y+dy)$。特别地，若对 $x$ 或者 $y$ 没有限制，则对应的值为 $0$。对于分治中心左侧，同样对于每个后缀预处理出 $(x,y,dx,dy)$。两侧的递推直接把当前矩形暴力并上去即可。又因为方案数不会超过 $2$，每个位置对应的 $(x,y,dx,dy)$ 个数也不会超过 $2$，复杂度是对的。

统计答案时，由于分治中心右侧限制不断变紧，完全可以枚举左边二分找右边。时间复杂度 $O(n\log^2 n)$。

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 3e5 + 10;

struct node {
	ll x, y, dx, dy;
	node(ll x = 0, ll y = 0, ll dx = 0, ll dy = 0) : x(x), y(y), dx(dx), dy(dy) {};
}; vector<node> a[MAXN];

inline 
bool check(ll x, ll y, int k) {
	for (node p : a[k]) {
		if ((!p.x || p.x == x) && (!p.y || p.y == y)) return 1;
	}
	return 0;
}

inline 
int bound(ll x, ll y, int l, int r) {
	for (int mid; l < r; check(x, y, mid = l + r + 1 >> 1) ? l = mid : r = mid - 1);
	return l;
}

int n; ll x[MAXN], y[MAXN];

inline 
ll solve(int l, int r) {
	if (l == r) return 1;
	int mid = l + r >> 1; ll ans = 0;
	for (int i = l; i <= r; i++) a[i].clear();
	a[mid + 1].emplace_back(x[mid + 1], 0, 0, y[mid + 1]);
	a[mid + 1].emplace_back(0, y[mid + 1], x[mid + 1], 0);
	for (int i = mid + 2; i <= r; i++) {
		for (node p : a[i - 1]) {
			if (p.x && p.x + p.dx == x[i]) a[i].emplace_back(p.x, p.y, p.dx, p.dy + y[i]);
			else if (!p.x && x[i] > p.dx) a[i].emplace_back(x[i] - p.dx, p.y, p.dx, p.dy + y[i]);
			if (p.y && p.y + p.dy == y[i]) a[i].emplace_back(p.x, p.y, p.dx + x[i], p.dy);
			else if (!p.y && y[i] > p.dy) a[i].emplace_back(p.x, y[i] - p.dy, p.dx + x[i], p.dy);
		}
	}
	ans += bound(x[mid], y[mid], mid, r) - mid;
	a[mid].emplace_back(x[mid], 0, 0, y[mid]), a[mid].emplace_back(0, y[mid], x[mid], 0);
	for (int i = mid - 1, j; i >= l; i--) {
		j = mid;
		for (node p : a[i + 1]) {
			if ((!p.x || p.x == x[i]) && (!p.y || p.y == y[i])) {
				j = max(j, bound(x[i] + p.dx, y[i] + p.dy, mid, r));
			}
		}
		ans += j - mid;
		for (node p : a[i + 1]) {
			if (p.x && p.x == x[i]) {
				if (!p.y) a[i].emplace_back(p.x, p.y, p.dx, p.dy + y[i]);
				else if (p.y > y[i]) a[i].emplace_back(p.x, p.y - y[i], p.dx, p.dy + y[i]);
			} else if (!p.x && p.y > y[i]) a[i].emplace_back(x[i], p.y - y[i], p.dx, p.dy + y[i]);
			if (p.y && p.y == y[i]) {
				if (!p.x) a[i].emplace_back(p.x, p.y, p.dx + x[i], p.dy);
				else if (p.x > x[i]) a[i].emplace_back(p.x - x[i], p.y, p.dx + x[i], p.dy);
			} else if (!p.y && p.x > x[i]) a[i].emplace_back(p.x - x[i], y[i], p.dx + x[i], p.dy);
		}
	}
	return ans + solve(l, mid) + solve(mid + 1, r);
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%lld%lld", &x[i], &y[i]);
	printf("%lld", solve(1, n));
}
```

---

## 作者：CCPSDCGK (赞：1)

首先对于每个 $l$，他能到达的 $r$ 一定是以 $l$ 为开头的前缀，所以对于每个 $l$ 只需要找出最远的 $r$ 即可。

如果从 $i$ 开始一直走到 $j$ 中途没有变换方式，那么满足的条件为：$h_i=h_{i+1}=\cdots=h_{j-1}$ 或 $w_i=w_{i+1}=\cdots=w_{j-1}$，所以只需要找出以 $i$ 开头的最长相等连续段即可。

**下面这个点比较难想，也是本题的 corner case**，如果连续两次操作（这里记为第 $i-1$ 次操作和第 $i$ 次操作）选择了不同的方式，那么第 $i$ 次操作前矩形长宽一定是 $(h_{i-1},w_i)$ 或 $(h_i,w_{i-1})$ 或 $(h_i,0)$ 或 $(0,w_i)$（初始为 $(h_i,w_i)$ 可以看成经历开头时要从 $0$ 加到 $h_i$ 或 $w_i$）。

以 $(h_{i-1},w_i)$ 为例，如果到第 $j$ 次操作才变换方式，那么第 $j$ 次操作前矩形长宽为 $(h_j,w_{j-1})$。

假如 $(h_{i-1},w_i)$ 的确能执行到第 $j$ 次操作（含），那么需要满足的条件有两个：
$$w_i=w_{i+1}=\cdots=w_{j-1}$$
$$h_j=h_{i-1}+h_i+h_{i+1}+\cdots+h_{j-1}$$

那么满足以下条件的数对 $(i,j)$ 到底有多少个，$O(n^2)$？no no no，首先 $h_i>0$，单看 $h_j=h_{i-1}+h_i+h_{i+1}+\cdots+h_{j-1}$ 就知道 $i$ 至多只有一个了，因为 $h_{i-1}+h_i+h_{i+1}+\cdots+h_{j-1}$ 相当于以 $j-1$ 为结尾的后缀和，$h_i>0$ 说明后缀和单调。所以满足条件的 $(i,j)$ 一共只有 $O(n)$ 对，

$(h_i,w_{i-1}),(h_i,0),(0,w_i)$ 同理。

所以做法是，找出这些满足条件的 $(i,j)$，暴力转移即可。

这里有个小问题，可能会存在 $(i,i)$ 的情况，这种情况会导致转移的时候进行了自转移，即一个位置里出现了两次不同操作，这种情况是不合法的，需要单独判掉，写代码的时候才发现。

时间复杂度：$O(n)$
```cpp
int f[2][300005],r[300005],h[300005],w[300005],sufw[300005],sufh[300005];
ll sumh[300005],sumw[300005];
ump<ll,int> mph,mpw;
int main(){
	int n;cin>>n;
	for(int i=1;i<=n;i++) cin>>h[i]>>w[i];
	for(int i=1;i<=n;i++) r[i]=i;
	mph[0]=mpw[0]=0;
	for(int i=1;i<=n;i++){
		sumh[i]=sumh[i-1]+h[i],sumw[i]=sumw[i-1]+w[i];
		mph[sumh[i]]=i,mpw[sumw[i]]=i;
	}
	for(int i=n;i;i--) if(h[i]^h[i+1]) sufh[i]=f[0][i]=i;else sufh[i]=f[0][i]=f[0][i+1];
	for(int i=n;i;i--) if(w[i]^w[i+1]) sufw[i]=f[1][i]=i;else sufw[i]=f[1][i]=f[1][i+1];
	for(int i=1;i<=n;i++) r[i]=max(sufh[i],sufw[i]);
	for(int i=n;i;i--){
		if(mph.find(sumh[i-1]-h[i])!=mph.end()){
			int p=mph[sumh[i-1]-h[i]];
			if(p+2^i&&sufw[p+2]>=i-1) f[1][p+2]=max(f[1][p+2],f[0][i]);
			if(sufw[p+1]>=i-1) r[p+1]=max(r[p+1],f[0][i]);
		}
		if(mpw.find(sumw[i-1]-w[i])!=mpw.end()){
			int p=mpw[sumw[i-1]-w[i]];
			if(p+2^i&&sufh[p+2]>=i-1) f[0][p+2]=max(f[0][p+2],f[1][i]);
			if(sufh[p+1]>=i-1) r[p+1]=max(r[p+1],f[1][i]);
		}
	}
	ll ans=0;
	for(int i=1;i<=n;i++) ans+=r[i]-i+1;
	cout<<ans;
	return 0;
}
```

---

## 作者：qiuzx (赞：1)

显然从每个点开始能到达的右端点是单调的，所以只需要求出最右的一个能到的点即可。先考虑如果保证过程中不存在能同时合并长和宽的情况应该怎么做。此时每一步至多只有一种合并的可能性，所以可以考虑找到所有更换合并的维度的这些位置。即一开始有一段 $h$ 全部相等的位置，此时会一直积累 $w$ 直到某个位置 $w$ 和当前的一样，此时会切换到 $w$ 继续合并。注意到对于一个固定的切换的位置 $i$，无论前面做了什么操作，来到这个位置 $i$ 之前的这个矩形一定是用 $h$ 从上一个合并而来，所以其 $h$ 一定等于 $h_{i-1}$。而由于它能够和 $i$ 合并，所以其 $w$ 一定等于 $w_i$。这样固定一个 $i$ 以及合并的维度，后面能如何合并就和前面的操作没有任何关系了。

这样可以记 $g_{i,0/1}$ 表示从 $i$ 开始合并，初始矩形是 $(h_i,w_{i-1})$ 还是 $(h_{i-1},w_i)$ 时能合并到的最右位置。转移时直接二分出下一个需要切换的位置，如果合法就转化为另一个 $g$ 的子问题，从后往前转移即可。

现在还需要处理的问题是有可能能同时合并长和宽。但此时我们选择一维进行合并，那么最终的答案一定是两种选择的较大值。由于能同时合并的情形一定是在和 $i$ 尝试进行合并时前面一个矩形是 $(h_i,w_i)$，所以可以记 $f_i$ 表示这种情形的答案。那么在转移 $f,g$ 时，如果在下一步切换的位置之前就出现了两维均相等的情形，就可以直接从 $f$ 转移，否则再从 $g$ 转移。这个位置同样可以二分求出，所以复杂度 $O(n\log n)$。

[代码](https://atcoder.jp/contests/arc179/submissions/54175434)

---

## 作者：WrongAnswer_90 (赞：0)

# [My Blogs](https://www.cnblogs.com/WrongAnswer90/p/18352711)

### [[ARC179E] Rectangle Concatenation](https://www.luogu.com.cn/problem/AT_arc179_e)

唐完了。

稍微观察一下发现矩形只有两种形态。考虑暴力：从每个 $i$ 开始向后扫，设 $f_{j,0}$ 表示能否拼在左右，$f_{j,1}$ 表示能否拼在上下。设 $S_{l,r}$ 表示 $[l,r]$ 内矩形的面积和，没想到用面积判就败了：

$$
\begin{aligned}
f_{j,0}=(f_{j-1,0}\wedge x_j=x_{j-1})\vee(f_{j-1,1}\wedge S(i,j-1)=y_{j-1}x_j)\\
f_{j,1}=(f_{j-1,1}\wedge y_j=y_{j-1})\vee(f_{j-1,0}\wedge S(i,j-1)=x_{j-1}y_j)\\
\end{aligned}
$$

考虑优化：把 $j$ 从左向右扫，维护合法的 $i$。设 $S_0$ 表示 $f_{j,0}$ 合法的 $i$ 集合，$S_1$ 同理。发现 $j+1$ 的时候，观察式子左半部分，$S_0,S_1$ 可能会做一个清空操作。

右半部分看成面积前缀和相减，合法的 $i$ 是唯一的。是一个单点加入，容易维护。还需要拿一个桶维护 $|S_0\cup S_1|$。时间复杂度 $\mathcal O(n\log n)$ 或者 $\mathcal O(n)$。

```cpp
int n,s[300010],vis[300010],f0[300010],f1[300010],ans,sum;
pii a[300010];
inline void add(int x){sum+=!vis[x]++;}
inline void del(int x){sum-=!--vis[x];}
map<int,int> hash;
inline void mian()
{
	read(n),hash[0]=0;vi v0,v1;
	for(int i=1;i<=n;++i)read(a[i].fi,a[i].se),s[i]=s[i-1]+a[i].fi*a[i].se,hash[s[i]]=i;
	ans=1,add(1),add(1),v0.eb(1),v1.eb(1),f0[1]=f1[1]=1;
	for(int i=2;i<=n;++i)
	{
		int va0=1;
		if(hash.find(s[i-1]-a[i].se*a[i-1].fi)!=hash.end())va0=f0[hash[s[i-1]-a[i].se*a[i-1].fi]+1];
		int va1=1;
		if(hash.find(s[i-1]-a[i].fi*a[i-1].se)!=hash.end())va1=f1[hash[s[i-1]-a[i].fi*a[i-1].se]+1];
		if(a[i].fi!=a[i-1].fi){for(auto p:v0)del(p),f0[p]=0;v0.clear();}
		if(a[i].se!=a[i-1].se){for(auto p:v1)del(p),f1[p]=0;v1.clear();}
		int S=s[i-1]-a[i].fi*a[i-1].se;
		if(hash.find(S)!=hash.end()&&!f0[hash[S]+1]&&va1)
		add(hash[S]+1),v0.eb(hash[S]+1),f0[hash[S]+1]=1;
		S=s[i-1]-a[i].se*a[i-1].fi;
		if(hash.find(S)!=hash.end()&&!f1[hash[S]+1]&&va0)
		add(hash[S]+1),v1.eb(hash[S]+1),f1[hash[S]+1]=1;
		if(!f0[i])add(i),v0.eb(i),f0[i]=1;
		if(!f1[i])add(i),v1.eb(i),f1[i]=1;
		ans+=sum;
	}
	write(ans);
}
```

---

## 作者：UniGravity (赞：0)

## Solution AT_arc179_e Rectangle Concatenation
套路地先扫描线。$r$ 从 $1$ 到 $n$，每次统计满足条件的 $l$。

对于当前扫到的 $r$，定义一个状态 $(l,(h,w))$ 表示 $[l,r]$ 的序列生成了矩形 $(h,w)$。

根据定义，我们发现合法的 $(l,(h,w))$ 必然满足 $h=h_r$ 或 $w=w_r$。想到可以开两个 set 维护合法的状态。

令 $h_{lst},w_{lst}$ 表示上一次操作的长宽，$h_{now},w_{now}$ 表示当前长宽。$a$ 是满足 $h=h_{now}$ 的 set，$b$ 是满足 $w=w_{now}$ 的 set。分类讨论：
* 当 $h_{lst}=h_{now},w_{lst}=w_{now}$ 时，有 $(h_{lst},w)\to(h_{now},w+w_{now})$，$w$ 同理。且此时 $(h_{lst},w_{lst})$ 都有两种转移。考虑分别给两个 set 加全局 tag。理一下步骤：
  * 将 $(h_{lst},w_{lst})$ 提取出来。要删去。 
  * 给 a 和 b 打上 tag。a 打上 $w_{now}$，b 打上 $h_{now}$。
  * 加入 $(h_{lst},2w_{lst})$ 和 $(2h_{lst},w_{lst})$。分别加入 a 和 b。
* 当 $h_{lst}=h_{now},w_{lst}\neq w_{now}$ 时，我们直接清空 b。这是因为 b 中除了一个 $(h_{lst},w_{lst})$ 外，其他的都无法与当前矩形接起来，而 $(h_{lst},w_{lst})$ 在 a 中也存在。步骤：
  * 提出 $(h_{lst},w_{now})$，不用删去。
  * 给 a 全局 tag 打上 $w_{now}$。清空 b。
  * 向 b 加入 $(2h_{lst},w_{now})$。
* 当 $h_{lst}\neq h_{now},w_{lst}=w_{now}$ 时，与上述情况本质相同。
* 当 $h_{lst}\neq h_{now},w_{lst}\neq w_{now}$ 时，只留下 $(h_{lst},w_{now})$ 和 $(h_{now},w_{lst})$，然后清空 a 和 b。再加入二者。

然后问题变成了怎么统计答案。开个桶。注意清空的时候直接遍历 set，一个个清空从桶中删去。

具体实现时可以通过重载运算符来简化代码。时间复杂度 $O(n \log n)$。

[代码。](https://atcoder.jp/contests/arc179/submissions/54298186)

---

