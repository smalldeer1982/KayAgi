# Bear and Blocks

## 题目描述

Limak is a little bear who loves to play. Today he is playing by destroying block towers. He built $ n $ towers in a row. The $ i $ -th tower is made of $ h_{i} $ identical blocks. For clarification see picture for the first sample.

Limak will repeat the following operation till everything is destroyed.

Block is called internal if it has all four neighbors, i.e. it has each side (top, left, down and right) adjacent to other block or to the floor. Otherwise, block is boundary. In one operation Limak destroys all boundary blocks. His paws are very fast and he destroys all those blocks at the same time.

Limak is ready to start. You task is to count how many operations will it take him to destroy all towers.

## 说明/提示

The picture below shows all three operations for the first sample test. Each time boundary blocks are marked with red color.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF573B/256df13c1ef1192f2e98a72ff5ba9bb98f4ceade.png) After first operation there are four blocks left and only one remains after second operation. This last block is destroyed in third operation.

## 样例 #1

### 输入

```
6
2 1 4 6 2 2
```

### 输出

```
3
```

## 样例 #2

### 输入

```
7
3 3 3 1 3 3 3
```

### 输出

```
2
```

# 题解

## 作者：梦游的小雪球 (赞：7)

看了前几篇题解，似乎都有点麻烦，下面是本蒟蒻的想法

## 梦雪的思路：

- $V$数组：用来存每一列最快消失的时间。

- $h$数组：用来存每一列的高度。

- $n$：列的数量。

- $s$：存最终结果。

#### 统计每一列最快能在第几次爆炸后消失。

1. 从左边开始，左边的一列都没了，下一次就能把这一列炸掉，即$ v_i=v_{i-1}+1 $。

1. 从右边开始，右边的一列都没了，下一次就能把这一列炸掉，即$ v_i=v_{i+1}+1 $。

1. 从顶端开始一直炸到底部，即$v_i=h_i$。

1. 上面三个值的最小值即每一列最快消失的速度，即$v_i=min(min(h_i,v_{i+1}+1),v_{i-1}+1)$。

1. 所有$v$的最大值即最终结果，即$s$。

## AC代码：

```
#include<bits/stdc++.h>
using namespace std;
int n,s,h[100002],v[100002];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&h[i]);
	v[1]=1;
	for(int i=2;i<n;i++)
		v[i]=min(v[i-1]+1,h[i]);//先比较从左边和从顶端开始
	v[n]=1;
	for(int i=n-1;i>=0;i--)
		v[i]=min(v[i],v[i+1]+1);//再比较从右边开始
	for(int i=1;i<=n;i++)
		s=max(s,v[i]);//所有v的最大值即最终结果
	printf("%d\n",s);
	return 0;
}
```

望通过QWQ

---

## 作者：南橙未熟k (赞：7)

~~其实这道题没想象中那么难~~，模拟就过了。
下面我们来讲怎么模拟。

------------
当我们将读入的数组正着扫一遍，再反着扫一遍，就可以发现
我们炸掉的方块数即为a[i]与a[i+1]+1或a[i-1]+1之中小的那个数。


------------
知道了这样，就可以通过简单的模拟来求出炸几次可以炸完。
在下蒟蒻，大佬路过勿喷。
~~代码巨丑，qwq~~
```pascal
var     i,j,n,m,k,t,x:longint;
        a:array[0..1000000]of longint;
function min(x,y:longint):longint;//min函数
begin
        if x>y then exit(y);
        exit(x);
end;
function max(x,y:longint):longint;//max函数
begin
        if x>y then exit(x);
        exit(y);
end;
begin
        readln(n);
        for i:=1 to n do
                read(a[i]);//首先，我们读入a[i];
        for i:=1 to n do
                a[i]:=min(a[i],a[i-1]+1);//a[i]为a[i]与a[i-1]+1中小值
        for i:=n downto 1 do
                a[i]:=min(a[i],a[i+1]+1);//a[i]为a[i]与a[i+1]+1中小值
        for i:=1 to n do
                x:=max(x,a[i]);//x为a[i]中最大值
        writeln(x);
end.
```


---

## 作者：Karry5307 (赞：3)

### 题意

题意不好写，就略过了。

$\texttt{Data Range}:1\leq n\leq 10^5,1\leq h_i\leq 10^9$

### 题解

[不一定更好的阅读体验](https://www.cnblogs.com/Karry5307/p/13584641.html)

这神仙题差点把我给卡死。

首先考虑一次操作会对第 $i$ 列方块的高度有什么影响，分三种情况讨论一下：

- 如果这列方块比左边一列的方块高，那么高度变为 $h_{i-1}$。

- 如果这列方块比右边一列的方块高，那么高度变为 $h_{i+1}$。

- 否则最上面一个方块总是要被消去的，高度变为 $h_{i}-1$。

三种情况取个最小值得到 $h_i=\min(h_{i-1},h_{i+1},h_i-1)$。

接下来考虑两次操作对 $h_i$ 的影响，我们先算出 $h_{i-1},h_i,h_{i+1}$ 一次操作后的高度，分别为：

$$h_{i-1}=\min(h_{i-2},h_{i},h_{i-1}-1),h_i=\min(h_{i-1},h_{i+1},h_i-1),h_{i+1}=\min(h_{i},h_{i+2},h_{i+1}-1)$$

再套一遍公式我们得到：

$$h_i=\min(h_{i-2},h_{i-1}-1,h_i-2,h_{i+1}-1,h_{i+2})$$

利用数学归纳法我们知道 $k$ 次操作后有

$$h_{i}=\min(h_{i-k},h_{i-k+1}-1,\cdots,h_{i}-k,\cdots,h_{i+k})$$

于是我们的目标就是要求出对于每个 $i$ 使得 $h_{i}=0$ 的最小的 $k$ 的最大值。

接下来我们单独考虑某个 $h_i$，然后记 $k_j$ 表示由 $h_j$ 算出来的 $k$ 值。

对于 $j\in[i-k,i]$ 来说 $h_i=h_j-j+i-k_j$，即 $k_j=h_j-j+i$。

同理得到对于 $j\in[i,i+k]$ 来说 $k_j=h_j+j-i$。

由于现在 $i$ 是恒定的，所以我们只需要求出 $h_j-j$ 的前缀最小值和 $h_j+j$ 的后缀最小值即可。这个可以使用线段树搞出来，注意几个小细节就好了。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef int ll;
typedef long long int li;
const ll MAXN=2e5+51,inf=0x3f3f3f3f; 
struct SegmentTree{
	ll l,r,mn,mn2;
};
SegmentTree tree[MAXN<<2];
ll n,res=-inf;
ll h[MAXN];
inline ll read()
{
    register ll num=0,neg=1;
    register char ch=getchar();
    while(!isdigit(ch)&&ch!='-')
    {
        ch=getchar();
    }
    if(ch=='-')
    {
        neg=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        num=(num<<3)+(num<<1)+(ch-'0');
        ch=getchar();
    }
    return num*neg;
}
#define ls node<<1
#define rs (node<<1)|1
inline void update(ll node)
{
	tree[node].mn=min(tree[ls].mn,tree[rs].mn);
	tree[node].mn2=min(tree[ls].mn2,tree[rs].mn2);
}
inline void create(ll l,ll r,ll node)
{
	tree[node]=(SegmentTree){l,r,0,0};
	if(l==r)
	{
		return (void)(tree[node].mn=h[l]-l,tree[node].mn2=h[l]+l);
	}
	ll mid=(l+r)>>1;
	create(l,mid,ls),create(mid+1,r,rs),update(node);
}
inline ll query(ll l,ll r,ll node)
{
	if(l>r)
	{
		return inf;
	}
	if(l<=tree[node].l&&r>=tree[node].r)
	{
		return tree[node].mn;
	}
	ll mid=(tree[node].l+tree[node].r)>>1;
	return min(l<=mid?query(l,r,ls):inf,r>mid?query(l,r,rs):inf);
}
inline ll query2(ll l,ll r,ll node)
{
	if(l>r)
	{
		return inf;
	}
	if(l<=tree[node].l&&r>=tree[node].r)
	{
		return tree[node].mn2;
	}
	ll mid=(tree[node].l+tree[node].r)>>1;
	return min(l<=mid?query2(l,r,ls):inf,r>mid?query2(l,r,rs):inf);
}
#undef ls
#undef rs
int main()
{
	n=read();
	for(register int i=1;i<=n;i++)
	{
		h[i]=read();
	}
	create(0,n+1,1);
	for(register int i=0;i<=n+1;i++)
	{
		res=max(res,min(query(0,i,1)+i,query2(i,n+1,1)-i));
	}
	printf("%d\n",res);
}
```

---

## 作者：Farkas_W (赞：2)

$$\text{拆方块}$$

$\quad$表示完全看不懂其他 $dalao$ 的线段树， $st$ 表和曼哈顿最小生成树做法，于是自己写一发题解帮助其他像我一样的蒟蒻。

$\quad$首先我们不应该把方块看做一个一个的，而是一列一列的，$l$ , $r$ 分别来表示这列方块因左边，右边无方块而消失的时间，设这列方块的编号为 $i$ ，消失时间为 $f_i$ ，高度为 $h_i$ ，设左边那列的方块消失时间为 $f_{i-1}$，设右边那列的方块消失时间为 $f_{i+1}$ ，显然可以得到

$$f_i=\min(f_{i-1}+1,f_{i+1}+1,h_i)$$

$\quad$因为当左边的方块全部消失时，这列方块显然会在下一个时间消失(若这列方块之前没有消失)，当右边的方块全部消失时，这列方块显然会在下一个时间消失(若这列方块之前没有消失)，又因为每个时间每一列方块的高度会减 $1$ ，显然一列方块 $i$ 最多在 $h_i$ 时消失，所以可以得到

$$l_i=\min(l_{i-1}+1,h_i$$

$$r_i=\min(r_{i+1}+1,h_i)$$

$\quad$这需要两遍循环处理，从小到大循环处理 $l_i$ ，从大到小处理 $r_i$ ，最后第 $i$ 列方块消失的时间就是 $\min(l_i,r_i)$ 。

$\quad$如果还不理解就看看样例理解一下。

![](https://cdn.luogu.com.cn/upload/image_hosting/y2zkmk1x.png)![](https://cdn.luogu.com.cn/upload/image_hosting/5okwkt02.png)![](https://cdn.luogu.com.cn/upload/image_hosting/nyy9a1ci.png)

$\quad$注意一定要先更新高度，将 $l_i$ 和 $r_i$ 初始化为 $h_i$ 即可，如上面第二列，后面 $l_i$ 和 $r_i$ 都会受到高度的影响。

$\quad$极简代码，关键只有三行！！
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
#define re register int
#define int long long
#define il inline
il int read()
{
  int x=0,f=1;char ch=getchar();
  while(!isdigit(ch)&&ch!='-')ch=getchar();
  if(ch=='-')f=-1,ch=getchar();
  while(isdigit(ch))x=(x<<1)+(x<<3)+ch-'0',ch=getchar();
  return x*f;
}
il void print(int x)
{
  if(x<0)putchar('-'),x=-x;
  if(x/10)print(x/10);
  putchar(x%10+'0');
}
const int N=1e5+5;
int n,ans,l[N],r[N];
signed main()
{
  n=read();
  for(re i=1;i<=n;i++)l[i]=r[i]=read();//初始化大小为高度
  for(re i=1;i<=n;i++)l[i]=min(l[i],l[i-1]+1);//处理l数组
  for(re i=n;i>=1;i--)r[i]=min(r[i],r[i+1]+1);//处理r数组
  for(re i=1;i<=n;i++){ans=max(ans,min(r[i],l[i]));}//取最大的较小值
  print(ans);
  return 0;
}
```

---

## 作者：Plozia (赞：1)

宣传博客->[link](https://blog.csdn.net/BWzhuzehao/article/details/112493387)

这道题有一点思考难度，需要根据题意与样例来思考。

首先我们考虑 $a_i$ 在几次之后会降为 0。

接下来的分析只考虑这个柱子上面被摧毁的情况，不考虑左右的柱子高度为 0 的影响。

1. 如果 $a_i \leq a_{i - 1}$ 且 $a_i \leq a_{i + 1}$，那么只有最上面的格子会遭殃，消耗次数 $a_i$。
2. 否则，$a_i = \min{(a_{i - 1}, a_{i + 1})}$，此时我们可以通过暴力计算。

但是有没有更好的方法呢？

我们知道对于这种求最小值的题目，通常都可以使用 dp 来解决。

设 $f_i$ 为第 $i$ 根柱子被摧毁的次数，那么根据上面的分析，我们有状态转移方程：$$f_i = \max{(f_{i - 1} + 1, a_i, f_{i + 1} + 1)}$$

考虑到对于 $f_i$ 需要同时用到左右两边的数据，那么我们可以做两遍 dp 来解决。

那么现在再来考虑左右两边的情况。

其实我们只要在左右两边加上一根高度为 0 的虚拟柱子不就好了qwq。

代码：

```cpp
#include <bits/stdc++.h>
#define Max(a, b) ((a > b) ? a : b)
#define Min(a, b) ((a < b) ? a : b)
using namespace std;

typedef long long LL;
const int MAXN = 1e5 + 10;
int n, a[MAXN], f[MAXN], ans;

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	while (ch < '0' || ch > '9') {if (ch == '-') fh = -1; ch = getchar();}
	while (ch >= '0' && ch <= '9') {sum = (sum << 3) + (sum << 1) + (ch ^ 48); ch = getchar();}
	return sum * fh;
}

int main()
{
	n = read();
	for (int i = 1; i <= n; ++i) a[i] = read();
	for (int i = 1; i <= n; ++i) f[i] = Min(f[i - 1] + 1, a[i]);
	for (int i = n; i >= 1; --i) f[i] = Min(f[i + 1] + 1, f[i]);
	for (int i = 1; i <= n; ++i) ans = Max(ans, f[i]);
	printf("%d\n", ans);
	return 0;
}
```

---

## 作者：Alarm5854 (赞：1)

这道题主要的难点就是如何抽象，思维量较大，码量较小。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF573B/256df13c1ef1192f2e98a72ff5ba9bb98f4ceade.png)

根据样例解释的图片，有两种情况：

- 两边的柱子的高度都大于等于这个柱子的高度，这种情况下，只有最上面的一格会被摧毁，其他地方安然无恙，$h_i'=h_i-1$。
- 两边的柱子的高度至少有一个小于这个柱子的高度，这种情况下，从较矮的柱子的高度开始，这根柱子的上面部分都要遭殃，$h_i'=\min(h_{i-1},h_{i+1})$。

综上所述，$h_i'=\max(0,\min(h_{i-1},h_i-1,h_{i+1}))$。

为了方便，在第一根柱子之前和最后一根柱子之后都设立一根高度为 $0$ 的虚拟柱子，这样就很方便，打出了这样的暴力代码：

```cpp
#include<ctime>
#include<cctype>
#include<cstdio>
const int N = 1e5 + 10;
using namespace std;
inline int read() {
	int x = 0, f = 1; char c;
	while (!isdigit(c = getchar())) f -= (c == '-') * 2;
	while (isdigit(c)) x = x * 10 + f * (c - 48), c = getchar();
	return x;
}
int n, cnt, a[2][N];
int max(int x, int y) {return x > y ? x : y;}
int min(int x, int y) {return x < y ? x : y;}
int check(int d) {for (int i = 1; i <= n; ++i) if (a[d][i]) return 0; return 1;}//判断是否所有的柱子都完全摧毁
int main() {
	n = read();
	for (int i = 1; i <= n; ++i) a[0][i] = read();
	while (!check(cnt & 1)) {
		int x = cnt & 1, y = x ^ 1;
		for (int i = 1; i <= n; ++i)
		a[y][i] = max(0, min(a[x][i - 1], min(a[x][i] - 1, a[x][i + 1])));
		++cnt;
	}
	printf("%d", cnt);
	return 0;
}
```

时间复杂度为 $O(n^2)$，接下来，考虑如何不模拟来做。

不难发现，改变这个柱子的高度的方式只有三种：

- 变为左边的柱子的高度。
- 变为右边的柱子的高度。
- 在原高度的基础上减一。

可以想到动态规划。

记 $f_i$ 为第 $i$ 根柱子的高度变为 $0$ 的次数，初始状态 $f_0=f_{n+1}=0$，然后，根据上面所述，$f_i=\min(f_{i-1}+1,h_i,f_{i+1}+1)$。

发现不能同时进行，所以需要两次循环来解决。

最终答案为 $\max_{i=1}^{n}(f_i)$。

```cpp
#include<ctime>
#include<cctype>
#include<cstdio>
const int N = 1e5 + 10;
using namespace std;
inline int read() {
	int x = 0, f = 1; char c;
	while (!isdigit(c = getchar())) f -= (c == '-') * 2;
	while (isdigit(c)) x = x * 10 + f * (c - 48), c = getchar();
	return x;
}
int n, ans, a[N], f[N];
int max(int x, int y) {return x > y ? x : y;}
int min(int x, int y) {return x < y ? x : y;}
int main() {
	n = read();
	for (int i = 1; i <= n; ++i) a[i] = read();
	for (int i = 1; i <= n; ++i) f[i] = min(f[i - 1] + 1, a[i]);
	for (int i = n; i; --i) f[i] = min(f[i], f[i + 1] + 1);
	for (int i = 1; i <= n; ++i) ans = max(ans, f[i]);
	printf("%d", ans);
	return 0;
}
```

时间复杂度仅为 $O(n)$。

---

## 作者：DennyQi (赞：1)

其实这道题的线段树可以不用支持修改，也就是说事实上ST表就可以了。

根据题目的性质，可以得到每一次操作就是对序列进行如下操作：$h_i= \min\{h_i-1,h_{i-1},h_{i+1}\}$。意义是：如果左右两边存在一边比自己低，那么高的部分一定是暴露部分需要删掉；如果两边都比自己高，那么暴露的只有最上面那个。

暴力这样做是$O(n^2)$的。我们考虑迭代一下，

$h_i= \min\{h_i-1,h_{i-1},h_{i+1}\}$,

$h_{i-1}=\min\{h_{i-1}-1,h_{i-2},h_{i}\}$，

$h_{i+1}=\min\{h_{i+1}-1,h_i,h_{i+2}\}$，

合并起来，**操作两次**之后就有$h_i=\min\{h_{i-2},h_{i-1}-1,h_i-2,h_{i+1}-1,h_{i+2}\}$

以此类推，**操作$k$次**之后就有$h_i=\min\{h_{i-k},h_{i-k+1}-1,\cdots,h_i-k,\cdots,h_{i+k-1}-1,h_{i+k}\}$

对于$j \in [i-k,i]$，有$h_i=h_j-(j-(i-k))=h_j-j+i-k$

对于$j \in [i,i+k]$，有$h_i=h_j-(k-(j-i))=h_j+j-k-i$。

我们要让操作次数尽量少，也就是对于每个$i$，让其$k$尽量小。我们只要对于每个$i$求出$k_{min}$，对于所有$k_{min}$取最大值就是答案。

将$k$表示出来，那么对于$j \in [i-k,i]$，$k=h_j-j+i$；对于$j \in [i,i+k]$，$k=h_j+j-i$。$i$是常数，于是问题转化为求两边$h_j-j$或$h_j+j$的最小值（不用考虑负数的情况，因为保证了$k \geq 0$）。那么我们只要维护$h_i+i$的最小值就可以了，复杂度$O(n \log n)$。

特别需要注意的是，原序列的首位要插入0，不然就不符合我们最初的公式了。

```cpp
/*DennyQi 2019*/
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;
const int N = 100010;
inline int read(){
    int x(0),w(1); char c = getchar();
    while(c^'-' && (c<'0' || c>'9')) c = getchar();
    if(c=='-') w = -1, c = getchar();
    while(c>='0' && c<='9') x = (x<<3)+(x<<1)+c-'0', c = getchar(); 
    return x*w;
}
int n,ans,a[N],v1[N<<2],v2[N<<2];
void build(int* v, int u, int l, int r, int zf){
	if(l == r){
		v[u] = a[l] + l*zf;
		return;
	}
	int mid = (l+r)>>1;
	build(v,u<<1,l,mid,zf);
	build(v,u<<1|1,mid+1,r,zf);
	v[u] = min(v[u<<1],v[u<<1|1]);
}
int query(int* v, int u, int l, int r, int x, int y){
	if(l > y || r < x) return 0x3f3f3f3f;
	if(x <= l && r <= y) return v[u];
	int mid = (l+r)>>1;
	return min(query(v,u<<1,l,mid,x,y),query(v,u<<1|1,mid+1,r,x,y));
}
int main(){
	// freopen("file.in","r",stdin);
	n = read();
	a[1] = a[n+2] = 0;
	for(int i = 2; i <= n+1; ++i){
		a[i] = read();
	}
	build(v1,1,1,n+2,-1);
	build(v2,1,1,n+2,1);
	for(int i = 1; i <= n+2; ++i){
		ans = max(ans,min(query(v1,1,1,n+2,1,i)+i,query(v2,1,1,n+2,i,n+2)-i));
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：frankchenfu (赞：1)

这道题听说可以采用曼哈顿最小生成树的$\Theta(n \log_2n)$算法，不过这里不讨论。我们来讲一下如何使用线段树维护。

------------

读完题目之后，我们很容易发现，最后消失的那几个方块至少有一个一定位于最底层（因为它上面的方块一定不会比它后消除）。所以我们设每个“塔”的高度为$h_i$，那么我们会发现第一次操作的时候它的高度就是$\min(h_i-1,h_{i-1},h_{i+1})$。不过因为 这个转移它有后效性，不能直接DP/递推得出答案。所以我们考虑如下递推式：我们递推第$k$次在第$i$座“塔”上操作后的高度，则$$h_i=\max(0,\displaystyle\min_{j=0}^{i}\{\min(h_{i-j},h_{i+j})-(k-j)\})$$

我们发现这个式子需要枚举$i$和$j$，复杂度不符合要求，怎么办呢？

观察发现，我们这里因为$k$是一个常数，不影响最优性；也就是说，我们要求的是$\displaystyle\min_{j=0}^{i}\{h_{i-j}+j\}$和$\displaystyle\min_{j=0}^{i}\{h_{i+j}+j\}$，也就是两个区间最值。于是，我们就使用线段树维护这个东西。

------------

这样，我们就在$O(n\log_2n)$的时间内完成了递推，最后对于每一个$i$，我们就可以求出把这堆删除的最小时间。我们把答案取$\max$即可。代码如下：
```cpp
#include<cstdio>
#include<cstring>

int min(int x,int y)
{
	return x<y?x:y;
}
int max(int x,int y)
{
	return x>y?x:y;
}

class seg_tree
{
	private:
		static const int MAXN=100010;
		struct node
		{
			int l,r,val;
			int lazy;
		}tree[MAXN<<2];
		void upd(int o)
		{
			tree[o].val=min(tree[o<<1].val,tree[o<<1|1].val);
		}
		void pushdown(int o)
		{
			int tmp=tree[o].lazy;
			tree[o].lazy=0;
			if(tmp)
			{
				tree[o<<1].lazy+=tmp;
				tree[o<<1|1].lazy+=tmp;
				tree[o<<1].val+=tmp;
				tree[o<<1|1].val+=tmp;
			}
		}
	
	public:
		int ord[MAXN];
		void build(int o,int l,int r)
		{
			tree[o].l=l;
		    tree[o].r=r;
		    tree[o].lazy=0;
		    int mid=(l+r)>>1;
		    if(l==r) 
			{
			    tree[o].val=ord[l];
			    return;
			}
		    build(o<<1,l,mid);
		    build(o<<1|1,mid+1,r);
		    upd(o);
		}
		void update(int o,int lt,int rt,int v)
		{
			int l=tree[o].l,r=tree[o].r;
			int mid=(l+r)>>1;
			if(lt<=l&&r<=rt)
			{
				tree[o].val+=v;
				tree[o].lazy+=v;
				return;
			}
			pushdown(o);
		    if(lt<=mid&&rt>=l) 
				update(o<<1,lt,rt,v);
		    if(lt<=r&&rt>mid)
				update(o<<1|1,lt,rt,v);
		    upd(o);
		}
		int query(int o,int lt,int rt)
		{
			int l=tree[o].l,r=tree[o].r;
			int mid=(l+r)>>1;
			if(lt<=l&&r<=rt)
				return tree[o].val;
			pushdown(o);
			int res=2147483647;
			if(lt<=mid&&rt>=l) 
				res=min(res,query(o<<1,lt,rt));
		    if(lt<=r&&rt>mid)
				res=min(res,query(o<<1|1,lt,rt));
			return res;
		}
};
seg_tree sol;
int lans[100010],rans[100010];

int read()
{
	int res=0;char ch=getchar();
	while(ch>='0'&&ch<='9')
	{
		res=(res<<3)+(res<<1)+ch-'0';
		ch=getchar();
	}
	return res;
}

int main()
{
	int n=read();;
	for(int i=1;i<=n;i++)
		sol.ord[i]=read();
	sol.build(1,0,n+1);
	for(int i=1;i<=n;i++)
	{
		sol.update(1,0,i-1,1);
		lans[i]=sol.query(1,0,i);
	}
	sol.build(1,0,n+1);
	for(int i=n;i;i--)
    {
        sol.update(1,i+1,n+1,1);
        rans[i]=sol.query(1,i,n+1);
    }
    int ans=0;
    for(int i=1;i<=n;i++)
    	ans=max(ans,min(lans[i],rans[i]));
    printf("%d\n",ans);
	return 0;
}
```

---

## 作者：轻绘 (赞：0)

跟机房大佬思路不大一样，本题使用二分答案。

## 题意概要
给定一个由方块组成的图。

每次将边缘的方块炸掉，求几次能炸完。

## 题意转换
找到最后被炸掉的方块在第几次被炸掉。

# 思路

最后被炸掉的方块之一绝对在底层!

以下证明来自：

[某大佬](https://www.luogu.com.cn/user/151791)。

###### 简单来说，就是对于每一个方块而言，其下方不可能是悬空的，一定会坐落在地面或其它方块上方，而唯有在悬空这一种情况下，答案才有可能分布在最下面一行上方的方块之中，对于此题的输入，答案则一定分布在最下面一行。
由此可证明一个金字塔型是最“稳定”的，最后炸掉的方块便是金字塔底层中心。

即在图中找到最大金字塔是答案。

![](https://cdn.luogu.com.cn/upload/image_hosting/hzcl1u5e.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

![](https://cdn.luogu.com.cn/upload/image_hosting/qhvnh5g9.png?x-oss-process=image/resize,m_lfit,h_170,w_225)


![](https://cdn.luogu.com.cn/upload/image_hosting/newkvpiu.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

二分金字塔大小，判断图中是否存在该金字塔。

# 实现

对于每一次二分得到答案，从左向右遍历图。

两个指针， **$i$ 代表在图中哪一列，$j$ 代表在金字塔中哪一列，$a_i$ 代表图上第i列方块高度，$b_j$ 代表金字塔第j列的高度**。

## 步骤一

**若 $b_j \leq a_i$** 证明图的第 $i$ 列可以充当金字塔的第 $j$ 列，于是 $i++$ , $j++$。

判断第 $i+1$ 列能否充当金字塔的第 $j+1$ 列。

## 步骤二

**若 $a_i<b_j$**  则代表放不下。

将 $j$ 减小，因为在金字塔左半边 $j$ 越小 $b_j$ 越小，直到放的下为止。

此时的 $j$ 减小到 $p$ 。

因为金字塔左半边递增，所以金字塔 $1$～$p$ 列。

必然分别小于等于 $(i-p+1)$ ~ $ i $ 列。

此时将 $i++$ ,$j++$ 继续判断 $b_{j+1},a_{i+1}$ 的大小。

## 步骤三

当 $j$ 是金字塔中间列即最长列并 $b_j \leq a_i$ 时，判断后续能否将金字塔的后半部分完整放入。

若不能，则重复步骤二中的将 $j$ 减小直到符合要求（即 $b_j \leq a_i$ ）
并重新步骤一。

若能则返回 $\text{true}$，依靠二分继续尝试更大的金字塔。

## 步骤四

若最后 $i$ 遍历完整个序列依然没有符合要求，则返回 $\text{false}$ 。

## 步骤五

二分出最大金字塔后，（底边块数+1）/2（即爆炸次数）。

# 总结

因为对于每次二分后的 $\operatorname{check()}$ 函数，时间复杂度为 $O(n)$（即最多 $i$ 从 $1$ 遍历到 $n$ ），
而二分答案时间复杂度为 $O(\log n)$。

故总时间复杂度为 **$O(n \log n)$**。

# 代码
```
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int inline read(){
	int x=0,f=1;
	char ch=getchar();
	while(!isdigit(ch)){if(ch=='-') f=-1; ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-'0'; ch=getchar();}
	return x*f;
} 
struct note{
	int v,num;
}b[200000];
int nex=1;
int n,ans;
int a[200000];
bool check(int x){
	int nex=1;
	bool f=1;
	for(int i=1;i<=n;i++){
		if(a[i]>=nex){ //因为金字塔中b[nex]==nex所以直接用nex比较
			nex++; //继续判断下一列是否符合（步骤一）
			if(nex-1==x){ //已经比较完正中间一列并符合要求
                                      （以下为步骤三）
				f=0;
				for(int j=i+1;j<=i+x-1;j++){
					if(a[j]<x-j+i){//后半部分出现不符合
						nex=a[j]+1;//将nex减小到a[j]+1
						i=j; //将i移至j（下一步比较a[i+1]和b[nex]）
						f=1;
						break;
					}
				}
				if(f==0){
					return true;
				}
			}
		}
		else{
			nex=a[i]+1; //步骤二
		}
	}
	if(f)
		return false;
	return true;
}
int main(){
	n=read();
	for(int i=1;i<=n;i++){ 
		a[i]=read();
	}
	int l=1,r=n/2+1,mid;
	while(l<r){  //二分（金字塔边数+1）/2，即可爆炸次数
		mid=(l+r+1)>>1;
		if(check(mid)){
			l=mid;
		}
		else
			r=mid-1;		
	}
	printf("%d",l); //此时l就是最多爆炸次数
	return 0;
} 
```


---

## 作者：ykuouzf (赞：0)

学校里模拟赛考了这题，虽说最后成绩不怎么样，不过抢到了这题的首A（$20min$）~~勉强没有爆零~~

#### 思路：

一般来说看到这种题都会先想到模拟（尤其是在考场上时），可 $h_i <= 10^9$ 的数据范围告诉我们这是行不通的，需要另辟蹊径

结合图像思考和分析：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF573B/256df13c1ef1192f2e98a72ff5ba9bb98f4ceade.png)

可以很快发现这样一个规律：即**最后删去的方块一定在最下面一行**

为什么是这样呢？结合题意，题目直接告诉你整一列的高度，却并非一个点一个点地读进来，于是，画出来只可能是一个形如沙堆一样上小下大的图形：
```
  	    *
 	    *
 	   **
 	   **
	*  ****
   *********
```

而绝不可能是以下这样（上面大下面小）：

```
      *******
       *****
        ***
         *
```
简单来说，就是**对于每一个方块而言，其下方不可能是悬空的，一定会坐落在地面或其它方块上方，而唯有在悬空这一种情况下，答案才有可能分布在最下面一行上方的方块之中，对于此题的输入，答案则一定分布在最下面一行**

上述结论请读者自行完成证明（其实也用不着怎么证啦想想就明白了

确定了答案的分布，接下来统计答案，发现每个方块的答案都可由左右方块的答案来推出，考虑dp解决

由此我们可以很快写出转移方程：

$left$ $：$ $f_i = f_{i - 1} + 1$

$right$ $：$ $f_i = f_{i + 1} + 1$

还有一种向上延伸的情况，手动模拟可知（这里不多加阐述）：

$f_i = min(a_i - 1, min(a_{i - 1}, a_{i + 1}))$

最后上述三种情况取 $min$ 即可，时间 $O(n)$

$Code:$

```
#include <bits/stdc++.h>

int read() {
	int j = 0; char c = getchar();
	while (c < '0' || c > '9') { c = getchar(); }
	while (c >= '0' && c <= '9') { j = (j << 1) + (j << 3) + (c ^ 48); c = getchar(); }
	return j;
}

void write(int x) {
	char c[20]; int l = 0;
	do { c[++l] = x % 10 + 48; x /= 10; } while (x);
	do { putchar(c[l--]); } while (l);
	putchar('\n');
} 

int max(int x, int y) { return x > y ? x : y; }
int min(int x, int y) { return x < y ? x : y; }

const int N = 1e5 + 10;

int n, ans, a[N], f[N];

signed main() {
	n = read();
	for (int i = 1; i <= n; i++) { a[i] = read(); }
	//此处循环从2 ~ n - 1是因两端的方块必定只需一次操作即可（即必有f[1] = f[n] = 0），无需计算 
	for (int i = 2; i <= n - 1; i++) { f[i] = min(f[i - 1] + 1, min(a[i] - 1, min(a[i - 1], a[i + 1]))); } //左上 
	for (int i = n - 1; i >= 2; i--) { f[i] = min(f[i], f[i + 1] + 1); } //右 
	for (int i = 2; i <= n - 1; i++) { ans = max(ans, f[i]); } //统计答案 
	write(ans + 1); // ans + 1
	return 0;
}
```

### The end.

---

