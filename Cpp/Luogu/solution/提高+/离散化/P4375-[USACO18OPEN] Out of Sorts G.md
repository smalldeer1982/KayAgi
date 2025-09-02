# [USACO18OPEN] Out of Sorts G

## 题目描述

留意着农场之外的长期职业生涯的可能性，奶牛 Bessie 开始在不同的在线编程网站上学习算法。

她到目前为止最喜欢的算法是“冒泡排序”。以下是 Bessie 最初的对长度为 $N$ 的数组 $A$ 进行排序的代码实现：

```
sorted = false
while (not sorted):
   sorted = true
   moo
   for i = 0 to N-2:
      if A[i+1] < A[i]:
         swap A[i], A[i+1]
         sorted = false
```

显然，代码中的 `moo` 指令的作用只是输出“moo”。奇怪的是，Bessie 似乎执着于在她的代码中的不同位置使用这个语句。

在用若干个数组测试了她的代码之后，Bessie 观察到一个有趣的现象：大的元素很快就会被拉到数组末尾，而小的元素需要很长时间“冒泡”到数组的开头（她怀疑这就是这个算法得名的原因）。为了实验和缓解这一问题，Bessie 修改了她的代码，使代码在每次循环中向前再向后各扫描一次，从而无论是大的元素还是小的元素在每一次循环中都有机会被拉较长的一段距离。她的代码现在是这样的：

```
sorted = false
while (not sorted):
   sorted = true
   moo
   for i = 0 to N-2:
      if A[i+1] < A[i]:
         swap A[i], A[i+1]
   for i = N-2 downto 0:
      if A[i+1] < A[i]:
         swap A[i], A[i+1]
   for i = 0 to N-2:
      if A[i+1] < A[i]:
         sorted = false
```

给定一个输入数组，请预测 Bessie 修改后的代码会输出多少次“moo”。


## 说明/提示

供题：Brian Dean

## 样例 #1

### 输入

```
5
1
8
5
3
2```

### 输出

```
2```

# 题解

## 作者：Meepo (赞：37)

[点我了解详情(´▽`)ﾉ ](https://hatate.cn/2018/09/17/usaco18openout-of-sorts-g/)
<!--more-->

推荐我的[博客](https://hatate.cn/)
```cpp
sorted = false
while (not sorted):
   sorted = true
   moo
   for i = 0 to N-2:
      if A[i+1] < A[i]:
         swap A[i], A[i+1]
   for i = N-2 downto 0:
      if A[i+1] < A[i]:
         swap A[i], A[i+1]
   for i = 0 to N-2:
      if A[i+1] < A[i]:
         sorted = false
```
问上述程序会输出几次moo。

首先读题，知道他想让你做什么。

奶牛的代码就是问你如果把冒泡排序该成双向的要排几次。

如果普通的冒泡，那么他的遍数= max {1，每个数前面有几个比它大}；

因为你每次会把一个比某个数小的数移到这个数后面。

我们先离散化，每个数的值为他的排名，就是第几大。

例如 100 1000 10000离散化后是1 2 3；

同理我们可以得到双向冒泡排序遍数=max{前?个位置上值>?的数有多少个，1}

注意它和普通冒泡排序的不同。

为什么结论是这个？

因为对于每个?

1. 向后扫会保证把前 ? 个位置上一个值> ? 的数扔到后边去  
2. 向前扫会保证被换到前? 个位置上的新数的值是≤ ? 的

如果不懂可以看下面。

拿样例举例

5

1 8 5 3 2

离散化后 1 5 4 3 2

位置为 &emsp;1 2 3 4 5

例如i=3

前3个数分别是1 5 4

5和4>3

后两个数分别是 3 2

3 2<=3

所以我们就换了两次。

然后我们就可以模拟了。

懒得模拟写树状数组也行。


````cpp
#include <cstdio>
#include <algorithm> 

using namespace std;
const int N=100005;

struct data
{
    int val,num;
    friend bool operator <(data x,data y){if(x.val==y.val)return x.num<y.num;return x.val<y.val;}
}a[N];
int n,ans=1,cnt;
int vis[N];
int main()
{
	scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i].val),a[i].num=i;
    sort(a+1,a+n+1);
    for(int i=1;i<=n;i++)
    {
        if(i<a[i].num) cnt++;
        if(vis[i]) cnt--;
        vis[a[i].num]=true;
        ans=max(ans,cnt);
    }
   printf("%d",ans);
}
````

---

## 作者：hs_black (赞：20)


### [P4375 Out of Sorts G](https://www.luogu.org/problem/P4375)
### [博客](https://www.luogu.org/blog/hs-black/mao-pao-pai-xu-shen-ru-li-xie)内食用效果更佳

题意:求双向冒泡排序的排序次数

### 对于一个序列, 我们称之为有序的, 当且仅当对于任意一个位置前面没有比它大的数(可以模拟一下)

我们暂且称它为平衡条件吧

首先将序列离散化

相比较于Out of Sorts S, 本题思路在于不动的位置, 结论为对于位置x, ans = max{ans, 前面有几个数的数值大于x}

为什么呢

在x不满足平衡条件的时候

### 首先第一波操作的时候,对于前x个位置一定会换出一个大于x的数

因为它不满足平衡条件

### 第二波操作时, 又会有一个小于等于x的数插回来

因为回来的时候一定会冒泡出一个位置在x后的最小值, 因为x不满足平衡条件, 所以最小值小于等于x, 就又插了回来

有人可能会问为什么Out of Sorts S不能用这个式子嘞, 因为每次换出的一定大于x, 但x+1位置上的数可能换过来, 而它有可能大于x

由此可知, 求每个位置前大于其的数就行啦

代码:

```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N = 100500;
int d[N], n;
int read(void) {
	int x = 0;
	char c = getchar();
	while (!isdigit(c)) c = getchar();
	while (isdigit(c)){
		x = (x << 3) + (x << 1) + c - '0';
		c = getchar();
	}
	return x;
}
struct node{
	int val, pos;
	bool operator < (const node &i) const{
		if (val == i.val) return pos < i.pos;
		return val < i.val;
	}
}p[N];
inline int low(int x) {
	return x & -x;
}
int get(int x) {
	int tmp = 0;
	for (;x;x -= low(x)) tmp += d[x];
	return tmp;
}
void add(int x) {
	for (;x <= n; x += low(x)) d[x]++;
}
bool cmp(node i,node j) {
	return i.pos < j.pos;
}
int main() {
	n = read();
	for (int i = 1;i <= n; i++) p[i] = (node){read(),i};
	sort(p + 1,p + n + 1);
	for (int i = 1;i <= n; i++) p[i].val = i;
	sort(p + 1,p + n + 1, cmp);
	int ans = 1;
	for (int i = 1;i <= n; i++) {
		add(p[i].val);
		ans = max(ans, i - get(i));
	}
	printf ("%d\n", ans);
	return 0;
}
/*
6
2 5 6 3 1 4

*/
```

---

## 作者：xixike (赞：14)

[博客食用更佳](https://www.cnblogs.com/xixike/p/15472038.html)

# Description

[洛谷传送门](https://www.luogu.com.cn/problem/P4375)

# Solution

一道很巧妙的结论题。

我们观察到题目中是一个双向冒泡排序。然后问你要进行多少轮才能排好序。

我们首先对于原数组进行离散化。

考虑冒泡排序的过程（假设当前数组未排好序）：

- 第一次：找出一个最大值放到最后面。

  对于位置 $x$，冒泡之后一定有一个大于 $x$ 的数被放到了 $x$ 后面。

- 第二次：找出一个最小值放到最前面。

  同理，对于位置 $x$，一定有一个小于等于 $x$ 的值放到了 $x$ 的前面。

这样一来，相当于把 $x$ 前面的一个大于它的数和它后面一个小于等于它的数交换了。

因此，结论就是：$$ans = max(ans, x 前面大于 x 的数的个数)$$

用树状数组维护一下即可。

# Code

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

inline int read(){
    int x = 0, f = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9') {if(ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9') x = (x << 3) + (x << 1) + ch - '0', ch = getchar();
    return x * f;
}

const int N = 1e5 + 10;
int n;
struct node{
    int pos, val;
    bool operator < (const node &b) const{
        return val != b.val ? val < b.val : pos < b.pos;
    }
}p[N];
int c[N];

inline void update(int x){
    for(; x <= n; x += x & (-x))
        c[x]++;
}

inline int query(int x){
    int res = 0;
    for(; x; x -= x & (-x))
        res += c[x];
    return res;
}

int main(){
    n = read();
    for(int i = 1; i <= n; ++i){
        p[i].val = read();
        p[i].pos = i;
    }
    sort(p + 1, p + 1 + n);
    int ans = 1;
    for(int i = 1; i <= n; ++i){
        update(p[i].pos);
        ans = max(ans, i - query(i));
    }
    printf("%d\n", ans);
    return 0;
}
```

# End

---

## 作者：ljc20020730 (赞：14)

考虑这样一个事情，如果正反来了一边那么每一次对于i位置上的数a[i]来说他左边位置j $\in $ [1,i-1]比a[i]严格大的数有一个被放到了i的右边

他右边的位置j$\in $ [i+1,n]比a[i]严格小的数有一个被放到了i的左边。当且仅当a[i]左边和右边不存在上述的数那么停止。

如果把一个数组变为有序显然第i个位子上放置第i大的数。

显然他们的位置一定在i位置后面。所有至少需要移动这么多次，把每一个比i大的数移动到i的右面。

显然我们冒泡1次对于每个i对应的有多少数在他左边只能减少1个这样的数，所以答案就是max{前i个数里面有多少个数字离散化后是比i大的，1}

```
# include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int c[N],n;
struct rec{int x,id;}a[N];
bool cmp(rec a,rec b)
{
    if (a.x!=b.x) return a.x<b.x;
    return a.id<b.id;
}
void update(int x){for (;x<=n;x+=x&-x) c[x]++;}
int query(int x){int ret=0; for (;x;x-=x&-x) ret+=c[x]; return ret;}
int main()
{
    scanf("%d",&n);
    for (int i=1;i<=n;i++)
     scanf("%d",&a[i].x),a[i].id=i;
    sort(a+1,a+1+n,cmp);
    int ans=1;
    for (int i=1;i<=n;i++){
        update(a[i].id);
        ans=max(ans,i-query(i));
    }
    printf("%d\n",ans);
    return 0;
}

```

---

## 作者：Otomachi_Una_ (赞：11)

一道珂爱并且喵喵的可爱题。

## 题目简述

- 求双重冒泡排序循环次数。
- $n\leq10^5$。

## 题目分析

我们先说结论，假设 $a$ 已经经历过离散化，那么答案是：

$$\max_{i=1}^n \{\sum_{j=1}^i [a_j>i]\}$$

我们证明一下。

这个式子其实就是在 $[1,i]$ 中不属于这个区间的数的个数。

每一次如果 $[1,i]$ 没有排序好，左冒泡走掉的肯定不属于这个区间，并且右冒泡肯定会补回来一个，所以单独对于这个区间来说就需要 $\sum_{j=1}^i [a_j>i]$ 的次数。

那么排序，就是要对任意的 $i$，下标为 $[1,i]$ 的数当中只有 $[1,i]$ 所以结论得证。

## 参考代码

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
const int MAXN=1e5+5;
int n;
struct node{
	int val,id;
}a[MAXN];
bool cmp1(node x,node y){return ((x.val!=y.val)?x.val<y.val:x.id<y.id);}
bool cmp2(node x,node y){return x.id<y.id;}
int t[MAXN];
int lowbit(int x){
	return x&(-x);
}
void add(int x){
	while(x<=n){
		t[x]++;
		x+=lowbit(x);
	}
}
int que(int x){
	int res=0;
	while(x>0){
		res+=t[x];
		x-=lowbit(x);
	}
	return res;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i].val,a[i].id=i;
	sort(a+1,a+n+1,cmp1);
	for(int i=1;i<=n;i++)
		a[i].val=i;
	sort(a+1,a+n+1,cmp2);
	int ans=1;
	for(int i=1;i<=n;i++){
		add(a[i].val);
		ans=max(ans,i-que(i));
	}
	cout<<ans<<endl;
}
```


---

## 作者：404Not_Found (赞：4)

结论题。

结论：对于每一个位置 $x$ 在它前面离散化后小于 $x$ 的值的数量的最大值。

证明很简单。考虑冒泡排序的过程：对于一个位置 $x$，先把它之前的一个大于 $x$ 的数放在它后面，再把它后面一个小于等于 $x$ 的数放在它前面。就相当于把大于它的和小于等于它的数字交换。

所以，结论成立。这个东西用树状数组维护一下就行。

有一个坑点是当序列原本有序的时候奶牛也会叫一次。 把答案和 $1$ 取一遍 $\max$ 就行了。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
int c[MAXN],n,ans=1;
pair<int,int> a[MAXN];
int lowbit(int x){return x&-x;}
void add(int x,int k){for(;x<=n;x+=lowbit(x)) c[x]+=k;}
int query(int x){int ret=0;for(;x;x-=lowbit(x)) ret+=c[x]; return ret;}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i].first),a[i].second=i;
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++)
	{
		add(a[i].second,1);
		ans=max(ans,i-query(i));
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：曹老师 (赞：4)

终于~~在帮助下~~AC了

**知识点：树状数组 + ~~智商题~~**

开始的时候想的是找规律 结果发现找不到

后来被告知是**树状数组**（我太菜啦

**sum[i] 表示 排好序之后有多少个数在 [1，i]内**

所以 不在 [1,i]内的就可以用 i-sum[i]

（开始的时候把sum理解成了前缀和 于是懵了好久

排序记录下原来的num 在原来的num基础上标记树状数组

**ins 简单理解就是打标记 ask 就是询问有多少个不在[1,i]内的数**

最后 **答案就是i-ask(i)的最大值**啊

Ps：还有一个比较坑的地方就是已经排好序的 这个时候你可能会输出0

但是答案最少也是1 所以 巧妙地处理一下就好了
```cpp
printf("%d",max(ans,1));
```
~~（滑稽~~ 分割线

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<queue> 
#define MAXN 100005
#define LL long long
#define INF 2147483640
#define MOD 100000007
#define free(s) freopen("s.txt","r",stdin);
#define lowbit(x) ((x&(-x))) 
using namespace std;
const int L=1e5+5;
struct node{
	int x,num;
};
bool cmp(const node &a,const node &b)
{
	return a.x<b.x||(a.x==b.x&&a.num<b.num);
}
int n,ans,sum[L];
node a[L];
void ins(int x)
{
	for(int i=x;i<=L;i+=lowbit(i))
		sum[i]++;
}
int ask(int x)
{
    int res=0;
    for(int i=x;i;i-=lowbit(i))
    	res+=sum[i];
    return res;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i].x);
		a[i].num=i;
	}
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++)
	{
		ins(a[i].num);
		ans=max(ans,i-ask(i));
	}
	printf("%d",max(ans,1));
	return 0;
}
```

---

## 作者：Del_Your_Heart (赞：3)

# $zkw$线段树$+$离散化
## $zkw:$树状数组=线段树，哈哈

------------
[传送门 洛谷P4375 [USACO18OPEN]Out of Sorts G](https://www.luogu.org/problem/P4375)

[欢迎在我的博客查看（也许更好的阅读体验？）](https://www.luogu.org/blog/trc233231/solution-p4375)



------------

### 最近刚好在学$zkw$线段树，于是我就在题库里翻标签有树状数组的题，刚好切到这一题，看到题解里都是树状数组$or$模拟，我就来发一篇$zkw$线段树。

这里简单讲一下$zkw$线段树，它是一种**自下向上**修改和查询的**非递归**的线段树。它源于$zkw$大佬的发现——**线段树的叶子节点编号与原数组下标的差值是一定的**。通过**小学生找规律**的方法易得，这个**差值$d=2^{log{(n+1)}}$**。

![](https://cdn.luogu.com.cn/upload/pic/71036.png )
------------

**$d$的求法：**
```cpp
while(d<=n+1)d<<=1;
```
**单点更新操作：($zkw$:是不是很像树状数组？是就对了。因为树状数组=线段树，哈哈。)**
```cpp
inline void update(int pos,int val){
	for(pos+=d;pos;pos>>=1)
    	zkw[pos]+=val;
}

```
**区间查询操作：这个有点复杂，$zkw$决定采用“左右夹♂击”(?)的方式具体请见如下代码**。

**前方位运算高能警告！！！**

```cpp
l=l+d-1;//找到左区间的左边的叶子节点的编号
r=r+d+1;//找到左区间的左边的叶子节点的编号
l^r^1//其返回值的意义为l和r是否为兄弟
l>>=1,r>>=1;//l,r往上走
~l&1//其返回值的意义为l是否为左儿子
l^1//其返回值为l的兄弟
r&1//其返回值的意义为r是否为右儿子
r^1//返回r的兄弟

//于是代码如下
inline int query(int l,int r){
	int ans=0;
    for(l=l+d-1,r=r+d+1;l^r^1;l>>=1,r>>=1){
    	if(~l&1)
            ans+=zkw[l^1];
        if(r&1)
            ans+=zkw[r^1];
    }//应该好理解
    return ans;
}

```
### 完整$AC$代码如下：~~我知道泥萌只看介个（逃~~

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
inline int read(){
    int x=0,f=0;char ch=getchar();
    while(!isdigit(ch))f|=ch=='-',ch=getchar();
    while(isdigit(ch))x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
    return f?-x:x;
}//快读
int n,d=1,zkw[maxn<<1];
inline void update(int pos,int val){for(pos+=d;pos;pos>>=1)zkw[pos]+=val;}
inline int query(int l,int r){int ans=0;for(l=l+d-1,r=r+d+1;l^r^1;l>>=1,r>>=1){if(~l&1)ans+=zkw[l^1];if(r&1)ans+=zkw[r^1];}return ans;}//写zkw不压行没有灵魂
struct node{
    int w;
    int id;
    inline bool operator< (const node& a) const{
        return w==a.w?id<a.id:w<a.w;
    }//重载运算符，不然sort不了
}a[maxn];
int main(){
    n=read();
    while(d<=n+1)
        d=d<<1;
    for(int i=1;i<=n;++i){
        a[i].w=read();
        a[i].id=i;//离散化
    }
    int res=1;
    sort(a+1,a+n+1);
    for(int i=1;i<=n;++i){
        update(a[i].id,1);
        res=max(res,i-query(1,i));
    }
    printf("%d",res);
    return 0;
}
```

# ---------------------------------$OVER$------------------------------------


---

## 作者：Coros_Trusds (赞：2)

# 题目大意

求对一个序列进行多少次双向冒泡排序可以使其有序。

# 题目分析

对 $a$ 进行编号（其实这里不应该叫做“离散化”，因为就算数据很小也需要进行所谓的“离散化”），则答案为 $\max_{i=1}^n\{\sum\limits_{j=1}^i[a[j]\gt i]\}$，其中 $[a]$ 的 $a$ 是一个逻辑语句，若 $a$ 为真则 $[a]=1$，反之则 $[a]=0$。

~~很遗憾，您上传的题解 P4375 [USACO18OPEN]Out of Sorts G 未能通过审核。原因是 应补充正确性证明；对解法的说明过少/不够清晰。~~

证明：

排序后，对于 $[1,i]$ 范围内不属于这个区间，即 $\exists j\in[1,i],a[j]\gt i$ 的所有 $a[j]$ 显然都会被移到 $[1,i]$ 外面去；相对应的，同时属于 $[1,i]$ 的也会被移一个进来。所以操作数就是 $[1,i]$ 内大于 $a[i]$ 的数的个数。

而这类似于逆序对，可使用树状数组维护值域求解。

---

## 作者：loser_seele (赞：1)

本题的结论：最终答案为对于每个位置，在这个位置之前比它大的数的总数中的最大值。

考虑奶牛的代码中每次排序实际上是把一个最小元素放置到最前面，最大元素放在最后面，于是对于一个位置，等价于把一个比它大的元素和一个比它小的元素交换，其余不变。

但是由于数据的范围太大，直接维护难以通过，考虑离散化后求排名，最后用排名作为其大小重新排序一遍之后进行维护。

这是一个支持单点修改和区间查询的数据结构，可以用树状数组实现，但这里使用 LCT 实现，时间复杂度 $ \mathcal{O}(n \log{n}) $，实际运行效率十分感人，不开氧气喜提最劣解。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long//保险
const int maxn=2e5+10;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
    return x*f;
}
int c[2000020],tag[2000020],n;
struct Splay
{
    int ch[maxn][2],fa[maxn],siz[maxn],val[maxn],sum[maxn],add[maxn],mul[maxn],rev[maxn];
    void clear(int x)
    {
        ch[x][0]=ch[x][1]=fa[x]=siz[x]=val[x]=sum[x]=add[x]=rev[x]=0;
        mul[x]=1;
    }
    int getch(int x)
    {
        return (ch[fa[x]][1]==x);
    }
    int isroot(int x)
    {
        clear(0);
        return ch[fa[x]][0]!=x&&ch[fa[x]][1]!=x;
    }
    void maintain(int x)
    {
        clear(0);
        siz[x]=(siz[ch[x][0]]+1+siz[ch[x][1]]);
        sum[x]=(sum[ch[x][0]]+val[x]+sum[ch[x][1]]);
    }
    void pushdown(int x)
    {
        clear(0);
        if(mul[x]!=1)
        {
            if(ch[x][0])
            mul[ch[x][0]]=(mul[x]*mul[ch[x][0]]),val[ch[x][0]]=(val[ch[x][0]]*mul[x]),sum[ch[x][0]]=(sum[ch[x][0]]*mul[x]),add[ch[x][0]]=(add[ch[x][0]]*mul[x]);
            if(ch[x][1])
            mul[ch[x][1]]=(mul[x]*mul[ch[x][1]]),val[ch[x][1]]=(val[ch[x][1]]*mul[x]),sum[ch[x][1]]=(sum[ch[x][1]]*mul[x]),add[ch[x][1]]=(add[ch[x][1]]*mul[x]);
            mul[x]=1;
        }
        if(add[x])
        {
            if(ch[x][0])
            add[ch[x][0]]=(add[ch[x][0]]+add[x]),val[ch[x][0]]=(val[ch[x][0]]+add[x]),sum[ch[x][0]]=(sum[ch[x][0]]+add[x]*siz[ch[x][0]]);
            if(ch[x][1])
            add[ch[x][1]]=(add[ch[x][1]]+add[x]),val[ch[x][1]]=(val[ch[x][1]]+add[x]),sum[ch[x][1]]=(sum[ch[x][1]]+add[x]*siz[ch[x][1]]);
            add[x]=0;
        }
        if(rev[x])
        {
            if(ch[x][0])
            rev[ch[x][0]]^=1,swap(ch[ch[x][0]][0],ch[ch[x][0]][1]);
            if(ch[x][1])
            rev[ch[x][1]]^=1,swap(ch[ch[x][1]][0],ch[ch[x][1]][1]);
            rev[x]=0;
        }
    }
    void update(int x)
    {
        if(!isroot(x))
        update(fa[x]);
        pushdown(x);
    }
    void rotate(int x)
    {
        int y=fa[x],z=fa[y],chx=getch(x),chy=getch(y);
        fa[x]=z;
        if(!isroot(y))
        ch[z][chy]=x;
        ch[y][chx]=ch[x][chx^1];
        fa[ch[x][chx^1]]=y;
        ch[x][chx^1]=y;
        fa[y]=x;
        maintain(y);
        maintain(x);
        maintain(z);
    }
    void splay(int x)
    {
        update(x);
        for(int f=fa[x];f=fa[x],!isroot(x);rotate(x))
        if(!isroot(f))
        rotate(getch(x)==getch(f)?f:x);
    }
    void access(int x)
    {
        for(int f=0;x;f=x,x=fa[x])
        splay(x),ch[x][1]=f,maintain(x);
    }
    void makeroot(int x)
    {
        access(x);
        splay(x);
        swap(ch[x][0],ch[x][1]);
        rev[x]^=1;
    }
    int find(int x)
    {
        access(x);
        splay(x);
        while(ch[x][0])
        x=ch[x][0];
        splay(x);
        return x;
    }//前面都是LCT板子部分
    void added(int u,int c)
    {
        int v=u;
        makeroot(u), access(v), splay(v);
      val[u] = (val[v] + c) ;
      sum[v] = (sum[v] + siz[v] * c ) ;
      add[v] = (add[v] + c) ;
        return;
    }//单点加（相当于对区间[u,u]加）
    int query(int u)
    {
        if(u==0)
            return 0;
        int v=1;
        makeroot(u), access(v), splay(v);
        return sum[v];
    }//区间查询（注意特判u=0的情况，在转化前缀和时1-1=0会出问题）
    void link(int u,int v)
    {
    if (find(u) != find(v)) 
    makeroot(u), fa[u] = v;
    }
}st;
int c1[maxn],d1[maxn],c2[maxn],d2[maxn],a[maxn];
struct node
{
    int fir,sec;
    bool operator<(const node &i)const
    {
		if (fir==i.fir) 
        return sec<i.sec;
		return fir<i.fir;
	}
}seele[maxn];
inline bool seele_cmp(node a,node b)
{
return a.sec<b.sec;
}
signed main()
{
        int n;
        cin>>n;
        for(int i=1;i<=n;i++)
        seele[i]=(node){read(),i};
        sort(seele+1,seele+n+1);
        for(int i=1;i<=n;i++)
        seele[i].fir=i;
        sort(seele+1,seele+n+1,seele_cmp);
        for(int i=1;i<=maxn/2;i++)
        st.clear(i),st.val[i]=0,st.maintain(i),st.splay(i);
        for(int i=1;i<=100000;i++)
            st.link(i,i+1);
        int ans=1;
        for(int i=1;i<=n;i++)
        {
        st.added(seele[i].fir,1);
        ans=max(ans,i-st.query(i));
        }
        cout<<ans;
}
```


---

## 作者：Danno0v0 (赞：1)

~~在人类智慧题面前显示了我是个大聪明~~

首先离散化，相同的数原本位置在前的离散后更靠前。

然后对每个位置 $i$ 单独考虑。

很显然所有大于 $i$ 的数都不应该排在位置 $i$ 和它的前面。

然后再来看一下那个两次排序。

手动模拟，第一次排序可以将一个且只有一个在 $i$ 或它之前的一个大于 $i$ 的数挪到 $i$ 的后面去。

（假如只有一个大于 $i$ 的数，那么在第一次冒泡中在 $i$ 及 $i$ 之前不会有大于这个数的数，那么一定会被冒泡带出    $i$ ,假如有两个或者更多，那么假如现在正在移动了一个数 $k$ ，假如遇到了一个大于 $k$ 的 $l$ ，那么会选择冒泡 $l$ 而不是 $k$ ，所以只有一个数能被带出 $i$）

那么直接易得把 $i$ 和它之前的所有大于 $i$ 的数（假设有 $k_i$ 个）挪出去要 $k_i$ 次。

根据上面的分析也易得然后把所有不在 $i$ 和它之前的所有小于等于 $i$ 的 $k_i$ 个数（一定等于在大于 $i$ 的数的个数）挪回来也需要 $k_i$ 次，恰好就在 $k_i$ 次循环内搞定。

至于最终要求有序的话易证经过 $k_i$ 次后在 $i$ 上的一定是 $i$ ，所以只要对每个位置都经过 $k_i$ 次移动最终一定有序。

答案就是 $\max(k_i)$ 。

然后坑逼的是假如数列原本有序Bessie也会叫一声。

code：

```
#include<bits/stdc++.h>
#define lb(x) x&(-x)
using namespace std;
int tree[1000001],ans=1,n;
int num[1000001],b[1000001],cnt[1000001],check[1000001],size;
void change(int x,int d){for(;x<=cnt[size];x+=lb(x)) tree[x]+=d;}
int query(int x)
{
	int ans=0;
	for(;x;x-=lb(x)) ans+=tree[x];
	return ans;
}	
bool cmp(int x,int y){return x<y;}
int find(int x)
{	
	int l=1,r=size,m;
	while(l<=r)
	{
		m=(l+r)>>1;
		if(b[m]==x) return m;
		else if(b[m]<x) l=m+1;
		else r=m-1;
	}
}	
int main()
{	
	cin>>n;
	for(int i=1;i<=n;i++) cin>>num[i],b[i]=num[i];
	sort(b+1,b+n+1,cmp);
	size=unique(b+1,b+n+1)-b-1;
	for(int i=1;i<=n;i++) cnt[find(num[i])]++;
	for(int i=2;i<=size;i++) cnt[i]+=cnt[i-1];
	for(int i=1;i<=n;i++)
	{
		int x=find(num[i]);
		num[i]=cnt[x-1]+check[x]+1;
		check[x]++;
	}
	for(int i=1;i<=n;i++)
	{
		change(num[i],1);
		ans=max(ans,query(cnt[size])-query(i));
	}
	cout<<ans;
}	
```


---

## 作者：Jayun (赞：1)

# 链接：

[洛谷](https://www.luogu.com.cn/problem/P4375)

[博客园](https://www.cnblogs.com/GJY-JURUO/p/14419835.html)

# 题目大意：

有一段代码：

```pascal
sorted = false
while (not sorted):
   sorted = true
   moo
   for i = 0 to N-2:
      if A[i+1] < A[i]:
         swap A[i], A[i+1]
   for i = N-2 downto 0:
      if A[i+1] < A[i]:
         swap A[i], A[i+1]
   for i = 0 to N-2:
      if A[i+1] < A[i]:
         sorted = false
```

让你求这段代码里的 `moo` 会运行多少次。

# 正文：

这道题的思路很妙。首先单独看第一个 `for` 循环，你会发现这个操作其实等价于将若干个数 $a_i$ 移到一个第一个大于它的数的前面，第二个循环类似。设 $x$ 表示一个中心点，要求两个循环的若干个数中分别至少有一个数在移动的时候经过 $x$。我们不妨把每次 `moo` 都是第一个循环的那个数和第二个循环的那个数互相搭配。

如果要让 `moo` 的次数多，那么就意味着让 $x$ 前后更多数相搭配。归纳一下，我们给 $a$ 数组离散化得到排名数组 $r$，那么相搭配必定是 $x$ 前的数的排名要大于 $x$，$x$ 后的数相反。答案即：

$$\max_{x=1}^{n}\{(\sum_{i\leq x,r_i>x}1)\}$$

然后就可以树状数组维护了。

# 代码：

```cpp
const int N = 1e5 + 10;

int n;
struct node
{
	int id, val;
}a[N];
int t[N], ans = 1;

void modify(int x){for (; x <= n; x += x & -x) t[x]++;}
int query(int x){int ans = 0;for (; x; x -= x & -x) ans += t[x]; return ans;}

bool cmp(node a, node b){return a.val < b.val;} 
bool cmp2(node a, node b){return a.id < b.id;} 

int main()
{
//	freopen(".in", "r", stdin);
//	freopen(".out", "w", stdout);
	scanf ("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf ("%d", &a[i].val), a[i].id = i;
	sort (a + 1, a + 1 + n, cmp);
	for (int i = 1; i <= n; i++) a[i].val = i;
	sort (a + 1, a + 1 + n, cmp2);
	for (int i = 1; i <= n; i++)
	{
		modify(a[i].val);
		ans = max(ans, i - query(i));
	}
	printf ("%d\n", ans);
    return 0;
```

---

