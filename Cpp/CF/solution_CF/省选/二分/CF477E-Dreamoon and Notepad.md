# Dreamoon and Notepad

## 题目描述

Dreamoon has just created a document of hard problems using notepad.exe. The document consists of $ n $ lines of text, $ a_{i} $ denotes the length of the $ i $ -th line. He now wants to know what is the fastest way to move the cursor around because the document is really long.

Let $ (r,c) $ be a current cursor position, where $ r $ is row number and $ c $ is position of cursor in the row. We have $ 1<=r<=n $ and $ 0<=c<=a_{r} $ .

We can use following six operations in notepad.exe to move our cursor assuming the current cursor position is at $ (r,c) $ :

1. up key: the new cursor position $ (nr,nc)=(max(r-1,1),min(a_{nr},c)) $
2. down key: the new cursor position $ (nr,nc)=(min(r+1,n),min(a_{nr},c)) $
3. left key: the new cursor position $ (nr,nc)=(r,max(0,c-1)) $
4. right key: the new cursor position $ (nr,nc)=(r,min(a_{nr},c+1)) $
5. HOME key: the new cursor position $ (nr,nc)=(r,0) $
6. END key: the new cursor position $ (nr,nc)=(r,a_{r}) $

You're given the document description ( $ n $ and sequence $ a_{i} $ ) and $ q $ queries from Dreamoon. Each query asks what minimal number of key presses is needed to move the cursor from $ (r_{1},c_{1}) $ to $ (r_{2},c_{2}) $ .

## 说明/提示

In the first sample, the first query can be solved with keys: HOME, right.

The second query can be solved with keys: down, down, down, END, down.

The third query can be solved with keys: down, END, down.

The fourth query can be solved with keys: END, down.

## 样例 #1

### 输入

```
9
1 3 5 3 1 3 5 3 1
4
3 5 3 1
3 3 7 3
1 0 3 3
6 0 7 3
```

### 输出

```
2
5
3
2
```

## 样例 #2

### 输入

```
2
10 5
1
1 0 1 5
```

### 输出

```
3
```

# 题解

## 作者：DaiRuiChen007 (赞：3)

# CF477E 题解



## 题目大意

> 给定一个 $n$ 行的文档，第 $i$ 行的长度为 $a_i$，你有一个光标所处位置为 $(r,c)$，每次可以以如下 $6$ 种方式之一移动：
>
> - $\mathrm{Left}$：$(r,c)\gets(r,\max\{0,c-1\})$。
> - $\mathrm{Right}$：$(r,c)\gets(r,\min\{a_r,c+1\})$。
> - $\mathrm{Up}$：$(r,c)\gets(r-1,\min\{a_{r-1},c\})$（$r>1$）。
> - $\mathrm{Down}$：$(r,c)\gets(r+1,\min\{a_{r+1},c\})$（$r<n$）。
> - $\mathrm{Home}$：$(r,c)\gets(r,0)$。
> - $\mathrm{End}$：$(r,c)\gets (r,a_r)$。
>
> $q$ 组询问，每次查询 $(r_1,c_1)\to(r_2,c_2)$ 至少要移动多少次。
>
> 数据范围：$n,q\le 4\times 10^5$。



## 思路分析



**没有 $\mathbf{End}$ 的情况**

先考虑 $r_1$ 和 $r_2$ 的关系，不妨假设 $r_1\le r_2$，否则可以考虑将 $a_1\sim a_n$ 翻转后再计算，容易证明上述 $6$ 中操作可以在翻转后找到一一对应的操作。因此我们只需要考虑 $r_1\le r_2$ 的情况，下同。

1. 只使用 $\mathrm{Down}$ 和 $\mathrm{Left}/\mathrm{Right}$

   容易发现最优策略一定是先用 $\mathrm{Down}$ 走到第 $r_2$ 行然后再用 $\mathrm{Left}/\mathrm{Right}$ 横向移动，这样可以避免向下过程中的移动损失。

   因此此时的答案应该是 $r_2-r_1+|\min\{\min[r_1,r_2],c_1\}-c_2|$，其中 $\min[r_1,r_2]$ 表示 $a_{r_1},a_{r_1+1},\dots a_{r_2}$ 中的最小值。

2. 使用了 $\mathrm{Home}$

   容易发现多次使用 $\mathrm{Home}$ 只会被抵消，最优解一定是在 $r_1$ 使用 $\mathrm{Home}$，然后下行到 $r_2$ 然后用 $\mathrm{Right}$ 横向移动。

   此时答案为 $r_2-r_1+c_2+1$。



**使用了 $\mathbf{End}$ 的情况**

3. 使用了 $\mathrm{End}$

   根据分析，我们知道此时 $\mathrm{End}$ 恰使用一次，且 $\mathrm{Home}$ 不会被使用，原因是 $\mathrm{Home}$ 和 $\mathrm{End}$ 会互相抵消，且这样的抵消是无视剩下 $4$ 种操作的，我们只需要保留最后一个位置即可。

   假设我们在第 $r_0$ 行使用 $\mathrm{End}$，那么最终我们所在的列应该是 $\min[r_0,r_2]$，答案为 $r_2-r_1+|c_2-\min[r_0,r_2]|+1$。

   由于纵向的移动距离是确定的，因此我们要最小化 $c_2-\min[r_0,r_2]$。

   - $c_2\ge \min[r_0,r_2]$

     此时我们要找到 $\min[r_0,r_2]\le c_2$ 且 $\min[r_0,r_2]$ 最大的 $r_0$，容易发现根据 $\min[r_0,r_2]$ 的单调性，我们只需要最小化 $r_0$ 并且保证 $\min[r_0,r_2]\le c_2$ 即可，可以直接二分 $r_0$ 的位置，$\min[r_0,r_2]$ 可以用 ST 表加速 $\mathcal O(1)$ 求出。

   - $c_2<\min[r_0,r_2]$

     此时的 $\min[r_0,r_2]>c_2$ 且 $r_0$ 应该尽可能大，观察容易发现此时的 $r_0$ 应该是 $c_2\ge \min[r_0,r_2]$ 情况中二分出的 $r_0$ 的下一行，即 $r_0+1$，在二分出上一种情况的 $r_0$ 后顺便计算这种情况即可。



**向下绕行的情况**

4. 向下绕行，且使用了 $\mathrm{End}$

   同理，$\mathrm{End}$ 只会恰好使用一次，设使用时的所在行为 $r_0$，显然 $r_2\le r_0\le n$。

   此时的代价为 $(r_0-r_1)+(r_0-r_2)+|c_2-\min[r_2,r_0]|+1$。

   - $\min[r_2,r_0]\le c_2$

     类似前一种情况，最小化 $2r_0-\min[r_2,r_0]$，此时 $2r_0$ 和 $-\min[r_2,r_0]$ 都关于 $r_0$ 递增，因此直接最小化 $r_0$，考虑用情况 3 类似的策略 ST 维护二分判定即可。

   - $\min[r_2,r_0]>c_2$

     此时最小化的式子为 $2r_0+\min[r_2,r_0]$，并且 $r_0<r'_0$，$r'_0$ 为上一种情况二分出的最小 $r_0$。 

     注意到这个式子两项随着 $r_0$ 增大分别增大和减小，直接用 $r'_0-1$ 肯定不优，考虑一个观察：对于最优解中的 $r_0$ 一定有 $\min[r_2,r_0]=a_{r_0}$ 否则将 $a_{r_0}$ 缩小到 $\min[r_2,r_0]$ 所在行，第一项减小，第二项不变，显然调整后更优。

     因此我们只需要维护 $[r_2,r'_0)$ 中最小的 $2i+a_i$，直接 ST 表维护即可。

5. 向下绕行，且未使用 $\mathrm{End}$

   考虑最终得到的列应该是 $\min\{c_0,\min[r_2,r_0]\}$，其中 $c_0=\min\{c_1,\min[r_1,r_2]\}$，表示只用 $\mathrm{Down}$ 操作走到第 $r_2$ 行所在的列标号。

   - $c_0< c_2$

     此时向下绕行只会使 $c$ 单调减小从而使 $|c-c_2|$ 的代价增加，显然这种策略一定不优，因此此时不需要向下绕行。

   - $c_0\ge c_2$

     - $c_0<\min[r_2,r_0]$

       此时向下绕行操作不会改变 $c$ 的值，并且额外带来纵向移动的代价，此时一定不优。

       并且由于对于任意 $r_0$ 均有 $\min[r_2,r_0]>c_0\ge c_2$，那么说明在向下绕行后使用 $\mathrm{End}$ 得到的列也不会优于直接从 $r_1$ 走到 $r_0$，因此此时向下绕行的任何决策都是不优的。

     - $c_0\ge \min[r_2,r_0]$
     
       此时从 $(r_2,c_0)$ 向下不使用 $\mathrm{End}$ 的效果和使用 $\mathrm{End}$ 完全等效，分类讨论和贡献计算完全相等，只不过节省了一次用 $\mathrm{End}$ 操作的 $+1$ 代价。
   
    综上所述，在实际实现中，我们只需要比较 $c_0$ 和 $c_2$ 的大小判断是否需要执行 $\mathrm{End}$ 操作即可。



**向上绕行的情况**

同上一种，考虑向上二分 $\min[r_0,r_2]\le c_2$ 的最大行，ST 表维护 $a_i-2i$ 的最值，根据 $c_0$ 与 $c_2$ 的关系判断是否执行 $\mathrm{End}$ 操作。

这种情况不是无意义的，考虑如下数据：

```
3
3 10 10
1
2 10 3 3
```

最优答案为 $3$，操作序列是 $\mathrm{Up}\to\mathrm{Down}\to\mathrm{Down}$，即向上绕路后使得所在列为 $3$ 从而减少横向移动。



**总结**

综上所述，我们需要维护三个 ST 表表示 $a_i,a_i+2i,a_i-2i$ 的最值，询问时需要进行二分。

时间复杂度 $\mathcal O((n+q)\log n)$。



## 代码呈现

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=4e5+1;
struct RMQ {
	int f[MAXN][20];
	inline int bit(int x) { return 1<<x; }
	inline void build(int *a,int n) {
		for(int i=1;i<=n;++i) f[i][0]=a[i];
		for(int k=1;k<20;++k) {
			for(int i=1;i+bit(k-1)<=n;++i) {
				f[i][k]=min(f[i][k-1],f[i+bit(k-1)][k-1]);
			}
		}
	}
	inline int query(int l,int r) {
		int k=__lg(r-l+1);
		return min(f[l][k],f[r-bit(k)+1][k]);
	}
}	A,U,D; //a[i], a[i]-2i, a[i]+2i
struct Query {
	int r1,c1,r2,c2,id;
	Query(int _r1=0,int _c1=0,int _r2=0,int _c2=0,int _id=0):
		r1(_r1),c1(_c1),r2(_r2),c2(_c2),id(_id) {}
};
int a[MAXN],u[MAXN],d[MAXN],res[MAXN];
signed main() {
	int n,q;
	scanf("%d",&n);
	for(int i=1;i<=n;++i) scanf("%d",&a[i]),u[i]=a[i]-2*i,d[i]=a[i]+2*i;
	scanf("%d",&q);
	vector <Query> P,Q;
	for(int i=1;i<=q;++i) {
		int r1,c1,r2,c2;
		scanf("%d%d%d%d",&r1,&c1,&r2,&c2);
		if(r1<=r2) P.push_back(Query(r1,c1,r2,c2,i));
		else Q.push_back(Query(n-r1+1,c1,n-r2+1,c2,i));
	}
	auto solve=[&](const vector <Query> Q) -> void {
		for(auto q:Q) {
			int r1=q.r1,r2=q.r2,c1=q.c1,c2=q.c2,c0=min(c1,A.query(r1,r2)),mov=(c0>=c2)?0:1;
			int ans=(r2-r1)+c2+1;
			ans=min(ans,(r2-r1)+abs(c2-c0));
			auto Find1=[&](int r1,int r2) -> int {
				int l=r1,r=r2,res=r1-1;
				while(l<=r) {
					int mid=(l+r)>>1;
					if(A.query(mid,r2)<=c2) res=mid,l=mid+1;
					else r=mid-1;
				}
				return res;
			};
			int r0=Find1(r1,r2);
			if(r0>=r1) ans=min(ans,(r2-r1)+(c2-A.query(r0,r2))+1);
			if(r0<r2) ans=min(ans,(r2-r1)+(A.query(r0+1,r2)-c2)+1);
			auto Find2=[&](int r1,int r2) -> int {
				int l=r2,r=n,res=n+1;
				while(l<=r) {
					int mid=(l+r)>>1;
					if(A.query(r2,mid)<=c2) res=mid,r=mid-1;
					else l=mid+1;
				}
				return res;
			};
			r0=Find2(r1,r2);
			if(r0<=n) ans=min(ans,(r0-r1)+(r0-r2)+(c2-A.query(r2,r0))+mov);
			if(r0>r2) ans=min(ans,D.query(r2,r0-1)-r1-r2-c2+mov);
			auto Find3=[&](int r1,int r2) -> int {
				int l=1,r=r1,res=0;
				while(l<=r) {
					int mid=(l+r)>>1;
					if(A.query(mid,r2)<=c2) res=mid,l=mid+1;
					else r=mid-1;
				}
				return res;
			};
			r0=Find3(r1,r2);
			if(r0>=1) ans=min(ans,(r1-r0)+(r2-r0)+(c2-A.query(r0,r2))+mov);
			if(r0<r1) ans=min(ans,U.query(r0+1,r1)+r1+r2-c2+mov);
			res[q.id]=ans;
		}
	};
	A.build(a,n),U.build(u,n),D.build(d,n);
	solve(P);
	reverse(a+1,a+n+1);
	for(int i=1;i<=n;++i) u[i]=a[i]-2*i,d[i]=a[i]+2*i;
	A.build(a,n),U.build(u,n),D.build(d,n);
	solve(Q);
	for(int i=1;i<=q;++i) printf("%d\n",res[i]);
	return 0;
}

```



---

## 作者：Tyyyyyy (赞：2)

## CF477E
### 题意简述
有一个 $n$ 行的网格，第 $i$ 行有 $a_i$ 列。你可以通过下面几种种方式在网格中移动：

- 左右移动一步。若超出本行的范围则无效。

- 上下移动一步。若超出目标行的范围，则移到目标行的末端。

- 移到本行的最左边或最右边。

$q$ 次询问，每次给出起点和终点坐标，求最少步数。

$1\leq n,q\leq 4\times 10^5,1\leq a_i\leq 10^8$。

### 题目分析

巨大分类讨论题。我们可以找到所有 **可能成为最优解** 的情况，然后取个 $\min$ 就好了。

下面我们默认起点在终点上面，在下面的情况是类似的。我们设起点为 $(r_1,c_1)$，终点为 $(r_2,c_2)$。

#### Case 1
首先我们可以只上下左右移动来走到目标点。此时上下移动的 $r_2-r_1$ 步是必须要走的，同时我们还要找到左右需要移动多少次。因为上下移动时可能会被强制移到行末，所以左右移动的次数就是 $|c_2-\min\{c_1,a_{r_1},\dots,a_{r_2}\}|$。

#### Case 2
考虑我们走的时候用一次走到行首的操作，不难发现在哪里用都是等价的，且只会用一次。

这时答案就是 $r_2-r_1+c_2+1$。

#### Case 3
考虑用一次走到行末的操作，这种情况比较麻烦。我们发现如果在一个位置走到行末，而后面又出现了一个比它列数少的行，那么等价于在那一行走到行末。

因此，我们可以找到 $r_2$ 前面第一个比它窄的行 $r_0$，那么只需要考虑在第 $r_0\sim r_2$ 行走到行末即可，因为在 $r_1\sim r_0-1$ 行走等价于在第 $r_0$ 行走。

此时上下走的步数仍为 $r_2-r_1$，而左右走的步数即 $\min\{c_2-a_{r_0},\min\{a_{r_0+1},\dots,a_{r_2}\}-c_2\}$。

#### Case 4
看起来上面的三种情况就足够了，但其实还不够。如样例 2，我们有可能先走到第 $r_2$ 行下面，走到某一行行末，再走回第 $r_2$ 行。注意，如果我们走到了 $r_2$ 行下面，那么一定是为了走到某一行的行末，因为其他情况都是不优的。

分析这种情况的步数。假设我们走到了第 $r_0(r_0>r_2)$ 行，那么上下方向走的步数就是 $r_2-r_1+2(r_0-r_2)$。左右方向走的步数就是 $|c_2-\min\{a_{r_2},\dots,a_{r_0}\}|$。

记 $\min\{a_l,\dots,a_r\}$ 为 $g(l,r)$，我们把绝对值拆开，则有两种情况：

- $g(r_2,r_0) \geq c_2$。那么我们要求 $f(x)=2x+g(r_2,x)$ 在 $(r_2,n]$ 上的最小值。简单分析可以发现这里可能成为最优解的 $x$ 一定是从第 $r_2$ 行开始的前缀最小行，单调栈 + 倍增即可。

- $g(r_2,r_0)<c_2$。那么我们要求 $f(x)=2x-g(r_2,x)$ 的最小值。可以发现这种情况的最优 $r_0$ 一定是第一个比 $c_2$ 小的 $r_0$，因为往下走是不优的。

#### Case 5
我们还有可能先往 $r_1$ 上面走再往下走，这种情况和 Case 4 是类似的。

至此，所有的情况都讨论完毕，分步实现即可。

代码太丑不放了，可以看 CF 提交记录。

---

## 作者：xtx1092515503 (赞：1)

大毒瘤数据结构题。好不容易自己A掉就来发篇题解。

------------

首先，因为 $r_1$ 和 $r_2$ 的大小关系不确定，故我们可以对于 $r_1>r_2$ 的询问，将 $r$ 变成 $n-r+1$ 并翻转整个序列，将其变成 $r_1\leq r_2$ 的情形。所以我们下面默认 $r_1\leq r_2$。

然后我们下面考虑画出图来：

![](https://cdn.luogu.com.cn/upload/image_hosting/yjqqsp6j.png)

假设我们有一个光标，它想从 $1$ 走到 $8$，应该怎样走呢？

我们发现，无论怎样乱跑，从 $1$ 到 $8$ 的七次向右走（实际上应该是 `down` 操作，但是因为我把图竖过来了所以就是向右走）总是免不了的。与此同时，向上向下走，我们会发现无论在哪里走都是没有区别的（当然，并非这样——你有可能在某个位置向上向下走了很多，但是往右又走了一些就被一个顶给撞下去了，也就是说提前的上下移动有可能是无用功——所以我们不如直接统一在 $r_2$ 处上下移动）。

那么，上下左右的事情我们都分析过了（不，实际上左右还有其它的可能，但是我们待会再说），就只剩 `HOME` 和 `END` 操作了。因为我们把图竖过来了，所以下文统一把 `HOME` 称作下跳，`END` 称作上跳。

我们发现，下跳操作，无论在任何位置实行也都是一样的，所以我们也可以统一在 $r_2$ 处处理。就只剩上跳操作了。

我们再回到上图。明显，只有在某些位置的上跳是有意义的——例如，在 $4$ 处的上跳，会马上再被 $5$ 撞下去；而只有 $5,7,8$ 处的上跳，是不会被撞下去的。观察发现，有效的位置可以直接使用单调栈维护。

因为无论在哪个位置上跳需要的操作都是 $1$ 次，所以我们肯定选择在离 $c_2$ 最近的那个位置处上跳。于是我们可以在单调栈中二分，找到离 $c_2$ 最近的两个位置（一个比 $c_2$ 大，一个比 $c_2$ 小），判断哪个位置更优即可。

则我们现在可能使用的策略共可以归纳如下：

1. 在未到终点之前，只执行向右操作。到了终点之后，通过上下操作移到终点。

此部分可以通过二分在单调栈中求出 $r_1$ 在单调栈里的下一个位置（也就是从 $r_1$ 到 $r_2$ 的路径中，其会被撞得最低的一次），然后与 $c_1$ 取 $\min$ 找到到达终点时它的高度，然后上下移动即可。

2. 在未到终点之前，只执行向右操作。到了终点之后，下跳一次，然后上下移动。

3. 在未到终点之前，执行向右操作，并在单调栈上某个位置上跳一次；到终点之后，上下移动。

如上所述，可以通过二分找到最优的上跳点。

到这里似乎没有什么更好的策略了。于是我们兴冲冲把代码写出来，然后一下过了第一组样例，再测第二组，出锅了。我们可以看一下第二组样例：

```
2
10 5
1
1 0 1 5
```

可以发现，第二组样例的思想，是利用左右移动和上跳来代替上下移动。再回到我们上面那幅图，假如我们想从 $2$ 走到 $4$ 的**中部**，可能向右走到 $5$ 再走回来反而会更优。

观察发现，这样向左向右移动所走到的位置，必定还是单调栈上的位置。

先考虑从终点出发向右走的情形。我们考虑从 $(r_2,fin)$，其中 $fin$ 是从 $r_1$ 走到 $r_2$ 的终点，走到其右方的某个位置，设成 $R$，然后再上跳到位置 $C$ 的距离，发现是

$$2(R-r_2)+|fin-C|+[fin<C]$$

其中，前两项是简单的距离；后一项是表示如果需要时，还需要上跳一下。

对于绝对值，我们的套路是把它拆开，然后就可以把它分成两半，一半只与 $(r_2,fin)$ 有关，一半只与 $(R,C)$ 有关。然后使用数据结构维护 $(R,C)$ 即可。这里因为觉得离散化什么的比较麻烦，我就直接上平衡树维护了。

再考虑从起点出发向左走的情形。这里也会发现与前面类似，就不再赘述了——详情可以见代码。

则时间复杂度 $O(n\log n)$。常数极大，但可以通过。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define y1 _19260817
#define y2 _17680321
int n,m,a[400100],stk[400100],res[400100],tp;
struct Query{
	int x1,x2,y1,y2,id;
	Query(int i){scanf("%d%d%d%d",&x1,&y1,&x2,&y2),id=i;}
	friend bool operator <(const Query &x,const Query &y){return x.x2<y.x2;}
};
#define lson t[x].ch[0]
#define rson t[x].ch[1]
int cnt,rt;
struct Treap{
	int ch[2],sz,val,pos,mnp,mnm,rd;
}t[400100];
void pushup(int x){
	t[x].mnp=t[x].val-2*t[x].pos;
	t[x].mnm=-t[x].val-2*t[x].pos;
	t[x].sz=1;
	if(lson)t[x].mnp=min(t[x].mnp,t[lson].mnp),t[x].mnm=min(t[x].mnm,t[lson].mnm),t[x].sz+=t[lson].sz;
	if(rson)t[x].mnp=min(t[x].mnp,t[rson].mnp),t[x].mnm=min(t[x].mnm,t[rson].mnm),t[x].sz+=t[rson].sz;
}
int merge(int x,int y){
	if(!x||!y)return x+y;
	if(t[x].rd>t[y].rd){t[x].ch[1]=merge(t[x].ch[1],y),pushup(x);return x;}
	else{t[y].ch[0]=merge(x,t[y].ch[0]),pushup(y);return y;}
}
void splitbypos(int x,int k,int &u,int &v){//u:<k.
	if(!x){u=v=0;return;}
	if(t[x].pos<k)u=x,splitbypos(rson,k,rson,v);
	else v=x,splitbypos(lson,k,u,lson);
	pushup(x);
}
void splitbyval(int x,int k,int &u,int &v){//u:<k.
	if(!x){u=v=0;return;}
	if(t[x].val<k)u=x,splitbyval(rson,k,rson,v);
	else v=x,splitbyval(lson,k,u,lson);
	pushup(x);
}
void splitbysize(int x,int k,int &u,int &v){
	if(!x){u=v=0;return;}
	if(t[lson].sz>=k)v=x,splitbysize(lson,k,u,lson);
	else u=x,splitbysize(rson,k-t[lson].sz-1,rson,v);
	pushup(x);
}
int newnode(int x){
	int u=++cnt;
	t[u].ch[0]=t[u].ch[1]=0;
	t[u].pos=x,t[u].val=a[x];
	t[u].rd=rand()*rand();
	pushup(u);
	return u;
}
void Insert(int x){
	int a,b;
	splitbypos(rt,x,a,b);
	rt=merge(merge(a,newnode(x)),b);
}
void Delete(int x){
	int a,b,c;
	splitbypos(rt,x,a,b);
	splitbysize(b,1,b,c);
	rt=merge(a,c);
}
int Ask(int bef,int x,int now){
	int a,b,c,e,f;
	splitbysize(rt,bef-1,b,c);
	splitbyval(b,x,a,b);
	int ret=0x3f3f3f3f;
	splitbyval(a,now+1,e,f);
	ret=min(ret,min(t[e].mnm+x,t[f].mnm+x+1));
	a=merge(e,f);
	
	splitbyval(b,now+1,e,f);
	ret=min(ret,min(t[e].mnp-x,t[f].mnp-x+1));
	b=merge(e,f);
	
	rt=merge(merge(a,b),c);
	return ret;
}
void Iterate(int x){
	if(!x)return;
	Iterate(lson);
	printf("[%d:%d]",x,a[x]);
	Iterate(rson);
}
void func(vector<Query>&v){
	sort(v.begin(),v.end());
	tp=0;
	cnt=rt=0;
	for(int i=0,j=1;i<v.size();i++){
//		printf("[%d,%d]\n",v[i].x1,v[i].x2);
		while(j<=v[i].x2){
			while(tp&&a[stk[tp]]>a[j])Delete(stk[tp--]);
			Insert(stk[++tp]=j++);
		}
//		for(int k=1;k<=tp;k++)printf("%d ",stk[k]);puts("");
//		for(int k=1;k<=tp;k++)printf("%d ",a[stk[k]]);puts("");
		int tmp=lower_bound(stk+1,stk+tp+1,v[i].x1)-stk;
		int fin=min(v[i].y1,a[stk[tmp]]);
//		printf("%d,%d\n",tmp,fin);
		res[v[i].id]=min(res[v[i].id],abs(v[i].x1-v[i].x2)+abs(fin-v[i].y2));//do not press anything special
		
		res[v[i].id]=min(res[v[i].id],abs(v[i].x1-v[i].x2)+v[i].y2+1);//press a HOME somewhere.
		
		a[n+1]=v[i].y2;
		int pmt=lower_bound(stk+tmp,stk+tp+1,n+1,[](int u,int v){return a[u]<a[v];})-stk;
		res[v[i].id]=min(res[v[i].id],abs(v[i].x1-v[i].x2)+abs(a[stk[pmt]]-v[i].y2)+1);//press an END somewhere in [x1,y1]
		if(pmt>tmp)res[v[i].id]=min(res[v[i].id],abs(v[i].x1-v[i].x2)+abs(a[stk[pmt-1]]-v[i].y2)+1);
		
		res[v[i].id]=min(res[v[i].id],v[i].x2+v[i].x1+Ask(tmp,v[i].y2,v[i].y1));//move to somewhere in [1,x1), and press an END if need.
		
		v[i].y1=fin;//stock fin for later use.
	}
	tp=0;
	cnt=rt=0;
	reverse(v.begin(),v.end());
	for(int i=0;i<v.size();i++)v[i].x1=n-v[i].x1+1,v[i].x2=n-v[i].x2+1;
	reverse(a+1,a+n+1);
	for(int i=0,j=1;i<v.size();i++){
		while(j<=v[i].x2){
			while(tp&&a[stk[tp]]>a[j])Delete(stk[tp--]);
			Insert(stk[++tp]=j++);
		}
//		Iterate(rt);puts("");
//		printf("%d %d\n",v[i].y2,v[i].y1);
		res[v[i].id]=min(res[v[i].id],abs(v[i].x1-v[i].x2)+2*v[i].x2+Ask(tp+1,v[i].y2,v[i].y1));//move to somewhere in (x2,n], press an END if need.
	}
	reverse(a+1,a+n+1);
}
vector<Query>v1,v2;
int main(){
	scanf("%d",&n),memset(res,0x3f,sizeof(res)),t[0].mnm=t[0].mnp=0x3f3f3f3f;
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	scanf("%d",&m);
	for(int i=1;i<=m;i++){
		Query q(i);
		if(q.x1<=q.x2)v1.push_back(q);
		else q.x1=n-q.x1+1,q.x2=n-q.x2+1,v2.push_back(q);
	}
	func(v1);
	reverse(a+1,a+n+1);
	func(v2);
	for(int i=1;i<=m;i++)printf("%d\n",res[i]);
	return 0;
}
/*
13
245468 180916 290696 340113 166951 259500 135270 32481 211977 128410 185376 380953 27639
1
1 244718 8 27128
*/
```

---

## 作者：是青白呀 (赞：0)

一道很折磨的分类讨论+数据结构题。给一种用线段树实现的方法。
## 分析
这里设起始点的行数为 $sx$，列数为 $sy$，终止点的行数为 $ex$，列数为 $ey$。设 $\min_{l,r}$ 表示 $\min a_i\ (l\leq i\leq r)$。

不难发现走的过程是**不可逆**的，所以先分 $sx\leq ex$ 和 $sx > ex$ 两种情况讨论。主要考虑 $sx\leq ex$ 的情况。设 $c_1$ 表示从起始点一直往下走到 $ex$ 行时所处的列数，有 $c_1=\min (\min_{sx,ex},sy)$。

接下来分类讨论所有可能最优的情况，并对所有情况的答案取最小值。

### 1.直接走
考虑不绕弯，先走到 $ex$ 行的情况。容易想到先竖着走，再横着走一定是最优的，可以避免原先走的横向步数被较短的行抵消的情况。

1. 只往上/下/左/右方向走：答案显然为 $ex-sx+|c_1-ey|$。

2. 使用 HOME 按键：不难发现在任意一行使用它的结果是一样的，答案显然为 $ex-sx+ey+1$。

3. 在最后一行使用 END 按键：答案显然为 $ex-sx+1+a_{ex}-ey$。

### 2.在 $sx$ 和 $ex$ 之间的行使用一次 END 按键

显然的是，使用多次 END 操作实际上等效与在最后一行使用 $1$ 次 END，因而 END 按键最多使用 $1$ 次，且一旦使用 END 按键，就一定不会使用 HOME 按键，否则其中一个按键的效果会被抵消。

考虑分析在哪些行使用 END 按键是可能最优的。设我们在 $r$ 行使用了 END，若 $\min_{r,ex-1}\neq a_r$，则说明使用 END 后，接下来的 DOWN 操作会被某个 $a_i$ 更小的行限制，实际上等效于在 $a_i$ 更小的那一行使用 END。此外，我们更希望选择寻找最接近 $ey$ 的 $a_i$ 使用 END，使得最后的左右移动步数最少。

因而我们知道，最优解仅在 $ex$ 行以上的首个 $a_{r_0}>ey$ 的行 $r_0$，及其以下的行中的某一部分出现。在这样的限制下，$a_i$ 小于 $ey$ 的最接近 $ey$ 的行 $r_1$ 不会被其它的行遮挡，所以其它行可以参与答案的统计而不会影响答案。

最终的答案为 $ex-sx+1+a_{r_0}-ey$ 与 $ex-sx+1+ey-a_{r_1}$ 中较小的一个。在线段树上维护$a_i$ 的值，$r_0$ 可以通过线段树上二分找到，而最优的 $r_1$ 可以通过在 $[r_0+1,ex-1]$ 这一区间中求区间最小值找到。

### 3.走到 $ex$ 行下方后再返回

我们可以利用 $a_i$ 较小的行的限制，达到快速改变光标横向位置的目的。不难想到走到 $ex$ 行以下的行后，唯一操作是走到该行的末尾后，再往上返回。

仍然考虑哪些行使用 END 按键是可能最优的。设最终走到 $r_2$ 行，则答案显然为 $2\times r_2-ex-sx+1+|\min_{ex,{r_2}}-ey|$。考虑拆绝对值，分类讨论。注意若走到 $r_2$ 行时已经是在最后一格，就不用按 END 键，可以不加 $1$。

1. 若 $\min_{ex,{r_2}}<ey$，当 $r_2$ 增大时，$\min_{ex,{r_2}}$ 的值单调递减，整个式子单调递减，所以最优答案只会在最小的满足条件的 $r_2$ 处取到。$r_2$ 可以通过线段树上二分找到，判断到达 $r_2$ 时是否为最后一格只需要判断 $a_{r_2}$ 和 $c_1$ 的大小关系即可，因为 $a_{r_2}$ 的值一定为前缀最小值，不会有其它行进行限制。下面设此处求得的行为 $r_3$。

2. 若 $\min_{ex,{r_2}}\geq ey$，原式不单调，考虑到对答案作出贡献的行一定满足 $a_{r_2}=\min_{ex,r_2}$，否则在前缀最小值所在的行使用 END 一定更优。原式即可化为 $2\times r_2-ex-sx+1+a_{r_2}-ey$，在线段树上维护 $2\times r_2+a_{r_2}$ 的值，每次在区间 $[ex+1,r_3-1]$ 内求最小值即可。对于不需要按 END 的行，设 $r_4$ 表示 $ex$ 下方首个 $a_i$ 不小于 $c_1$ 的行，由于接下来的 $a_i$ 更大的行一定不优，故考虑直接在 $[r_4,r_3-1]$ 的区间内求最小值即可。

### 4.先往上走若干行后再往下走

与第三类类似，答案为 $-2\times r_2+ex+sx+1+|\min_{{r_2},ex}-ey|$。又由于对答案有贡献的行一定满足 $\min{r_2,sx}=a_{r_2}$，故原式简化为 $-2\times r_2+ex+sx+1+|\min(\min_{sx,ex},a_{r_2})-ey|$。同样考虑分类讨论。

1. 若 $a_{r_2}\leq ey$，则绝对值中被减数一定小于减数。和第三类类似，最优行只可能为 $sx$ 以上的首个满足条件的行，直接判断是否需要按 END 并计算即可。下面设此处求得的行为 $r_3$。

2. 若 $a_{r_2}> ey$，不难想到仅有 $a_{r_2}\geq \min_{sx,ex}$ 的行才可能贡献答案，否则可以直接在 $a_i=\min_{sx,ex}$ 的行找到更优的答案，也就是类型二中计算的答案。于是原式可化为 $-2\times r_2+ex+sx+1+a_{r_2}-ey$。容易找到首个满足 $a_{r_4}\geq \min_{sx,ex}$ 的行 $r_4$，则在区间 $[r_3+1,r_4]$ 中求 $a_{r_2}-2\times r_2$ 的最小值即可。对于不需要按 END 的答案，只需要在区间 $[r_3+1,r_4]$ 中找到最后一个 $a_i$ 不小于 $sy$ 的行，同样地求区间最小值即可。

$sx > ex$ 的情况是类似的。为了好写，可以将所有询问离线，先处理所有 $sx \leq ex$ 的询问，处理完后将整个 $a$ 序列和 $sx$、$ex$ 翻转即可。对于三个不同值求最小值的操作，可以写进同一个函数里。整体时间复杂度 $O(n\log n)$，常数稍大。

## Code

注意代码中的部分变量名称与题解中不符。

```cpp
#include<bits/stdc++.h> 
#define int long long
#define rep(i,j,k) for(int i=j;i<=k;i++)
#define repp(i,j,k) for(int i=j;i>=k;i--)
#define ls(x) x*2
#define rs(x) x*2+1
#define mp make_pair
#define fir first
#define sec second
#define pii pair<int,int>
#define lowbit(x) x&-x
#define coded by Qingbai666
using namespace std;
typedef long long ll;
const int N=4e5+5,mo=1e9+7,inf=1e18+7;
void read(int &p){
	int x=0,w=1;
	char ch=0;
	while(!isdigit(ch)){
		if(ch=='-')w=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	p=x*w;
}
int n,a[N],Q;
int sx,sy,ex,ey;

struct seg{
	int minn[N*4],t1[4*N],t3[4*N];//2r0+a[r0]的min;a[r0]-2r0的min 
	void pushup(int x){
		t1[x]=min(t1[ls(x)],t1[rs(x)]),t3[x]=min(t3[ls(x)],t3[rs(x)]);
		minn[x]=min(minn[ls(x)],minn[rs(x)]);
	}
	void build(int x,int le,int ri){
		if(le==ri){
			minn[x]=a[le];
			t1[x]=2*le+a[le],t3[x]=a[le]-2*le;
			return;
		}
		int mid=(le+ri)>>1;
		build(ls(x),le,mid);
		build(rs(x),mid+1,ri);
		pushup(x);
	}
	int query1(int x,int le,int ri,int ql,int qr,int v,int op){//查询区间中最靠近0ql，1qr的小于v的下标 
		if(minn[x]>=v||qr<ql)return 0;
		if(le==ri)return le;
		int mid=(le+ri)>>1;
		int ret=0;
		if(!op){//靠近ql 
			if(ql<=mid&&minn[ls(x)]<v)ret=query1(ls(x),le,mid,ql,qr,v,op);
			if(ret)return ret;
			if(qr>mid&&minn[rs(x)]<v)ret=query1(rs(x),mid+1,ri,ql,qr,v,op);
			return ret;
		}
		else{
			if(qr>mid&&minn[rs(x)]<v)ret=query1(rs(x),mid+1,ri,ql,qr,v,op);
			if(ret)return ret;
			if(ql<=mid&&minn[ls(x)]<v)ret=query1(ls(x),le,mid,ql,qr,v,op);
			return ret;
		}
	}
	int querymin(int x,int le,int ri,int ql,int qr,int op){//1.查minn 2.查t1  3.T2 4.T3
	    if(ql>qr)return inf;
		if(ql<=le&&qr>=ri){
			if(op==1)return minn[x];
			if(op==2)return t1[x]; 
			if(op==4)return t3[x];
		}
		int mid=(le+ri)>>1,ret=inf;
		if(ql<=mid)ret=min(ret,querymin(ls(x),le,mid,ql,qr,op));
		if(qr>mid)ret=min(ret,querymin(rs(x),mid+1,ri,ql,qr,op));
		return ret;
	}
}T; 
int nid;
int solve1(){
	int ans,minn=T.querymin(1,1,n,sx,ex,1),r1=sy;
	sy=min(sy,minn);
	//1.直接走
	ans=min(1+ey+ex-sx,min(abs(sy-ey)+ex-sx,ex-sx+a[ex]-ey+1));
	//2.走到sx与ex之间的某排，然后end，再继续走
	int r0=T.query1(1,1,n,sx,ex,ey,1);
	if(r0)ans=min(ans,ex-sx+1+ey-a[r0]);
	else r0=sx-1;
	ans=min(ans,ex-sx+1+T.querymin(1,1,n,r0+1,ex,1)-ey);
	//3.走过了结束的那一行，走到结尾再回去
	r0=T.query1(1,1,n,ex+1,n,ey,0);
	int r3=T.query1(1,1,n,ex+1,n,sy+1,0);//首个不大于sy的 这之后就不用加1了，这之前的要加end的1 
	if(r0){
		if(a[r0]<=sy)ans=min(ans,r0-sx+r0-ex+abs(a[r0]-ey));
		else ans=min(ans,r0-sx+r0-ex+1+abs(a[r0]-ey));
	}
	if(!r3)r3=n+1;
	if(!r0)r0=n+1;
	ans=min(ans,T.querymin(1,1,n,ex,r0-1,2)-sx-ex+1-ey);
	ans=min(ans,T.querymin(1,1,n,r3,r0-1,2)-sx-ex-ey);
	//4.初始时先往上走，然后再下来 
	r0=T.query1(1,1,n,1,sx-1,ey,1),r3=T.query1(1,1,n,1,sx-1,minn,1);
	int r4=T.query1(1,1,n,r0+1,r3,r1+1,1);
	if(r0){
		int res=T.querymin(1,1,n,r0,ex,1);
		if(a[r0]<=r1)ans=min(ans,sx+ex-2*r0+ey-res);
		else ans=min(ans,sx+ex-2*r0+ey-res+1);
	}
	ans=min(ans,T.querymin(1,1,n,r0+1,r3,4)+sx+ex+1-ey);
	ans=min(ans,T.querymin(1,1,n,r0+1,r4,4)+sx+ex-ey);
	return ans;
}
struct query{
	int r1,r2,c1,c2,id,tp;
	friend bool operator<(query x,query y){
		return x.tp<y.tp;
	}
}q[N];
int ans[N]; 

void reverse(){
	rep(i,1,n/2)
	    swap(a[i],a[n-i+1]);
	T.build(1,1,n);
}

signed main(){
	read(n);
	rep(i,1,n)
	    read(a[i]);
	T.build(1,1,n);
	read(Q);
	rep(i,1,Q){
		read(q[i].r1),read(q[i].c1),read(q[i].r2),read(q[i].c2),q[i].id=i;
		if(q[i].r1>q[i].r2)q[i].tp=2;
		else q[i].tp=1;
	}
	sort(q+1,q+Q+1);
	q[0].tp=1;
	rep(i,1,Q){
		if(q[i].tp!=q[i-1].tp)reverse();
		sx=q[i].r1,sy=q[i].c1,ex=q[i].r2,ey=q[i].c2,nid=q[i].id;
		if(q[i].tp==2)sx=n-sx+1,ex=n-ex+1;
		ans[q[i].id]=solve1();
	} 
	rep(i,1,Q)
	    printf("%lld\n",ans[i]);
	return 0;
}
```

---

