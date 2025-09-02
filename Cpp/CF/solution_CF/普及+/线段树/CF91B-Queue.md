# Queue

## 题目描述

There are $ n $ walruses standing in a queue in an airport. They are numbered starting from the queue's tail: the $ 1 $ -st walrus stands at the end of the queue and the $ n $ -th walrus stands at the beginning of the queue. The $ i $ -th walrus has the age equal to $ a_{i} $ .

The $ i $ -th walrus becomes displeased if there's a younger walrus standing in front of him, that is, if exists such $ j $ ( $ i<j $ ), that $ a_{i}>a_{j} $ . The displeasure of the $ i $ -th walrus is equal to the number of walruses between him and the furthest walrus ahead of him, which is younger than the $ i $ -th one. That is, the further that young walrus stands from him, the stronger the displeasure is.

The airport manager asked you to count for each of $ n $ walruses in the queue his displeasure.

## 样例 #1

### 输入

```
6
10 8 5 3 50 45
```

### 输出

```
2 1 0 -1 0 -1 ```

## 样例 #2

### 输入

```
7
10 4 6 3 2 8 15
```

### 输出

```
4 2 1 0 -1 -1 -1 ```

## 样例 #3

### 输入

```
5
10 3 1 10 11
```

### 输出

```
1 0 -1 -1 -1 ```

# 题解

## 作者：mcqueen (赞：14)

****提供一种O（nlogn）的做法，无需各种神奇的数据结构（线段树、树状数组都不需要****）

****大概是基于分治思想（也带点贪心）****

------------
用数组b记录输入的数组a中的后缀最小值，然后对于每一个Ai，在Ai+1~An中进行分治，每次优先取右边的最小值

具体见代码

```cpp
#include<cstdio>
int a[100005],b[100005],n,i,v;
inline void in(int &x)
{
    x=0;
    char c=getchar();
    while(c<'0'||c>'9')c=getchar();
    while(c>='0'&&c<='9')x=x*10+c-'0',c=getchar();
}//快读
inline void go(int l,int r)
{
    if(l==r){printf("%d ",l-i-1);return;}
    int mid=l+r>>1;
    if(b[mid+1]<v)go(mid+1,r);
    else go(l,mid);
}//贪心&分治
int main()
{
    in(n);
    for(i=1;i<=n;i++)in(a[i]);
    b[n]=a[n];
    for(i=n-1;i;i--)b[i]=b[i+1]>a[i]?a[i]:b[i+1];//预处理后缀最小值数组
    for(i=1;i<n;i++)
    {
        v=a[i];
        if(b[i+1]>=v)printf("-1 ");//说明Ai右边没有比它还小的数
        else go(i+1,n);
    }
    puts("-1");//特判An
    return 0;
} 
```
**方法挺快的，~~（目前洛谷速度第一）~~**

**希望能帮到大家**



---

## 作者：一水清浅 (赞：9)

### **这题大佬们已经说过查询右子树优先了，但是没有给出完整的代码。其他小可爱们发布的题解也不是线段树的代码，这么好的机会我可不能放过，我来补充一下线段树的代码吧。**

只要读者知道这题是查询右子树优先，应该立刻就能看懂我的代码

```cpp
#include <cstdio>
#include <iostream>
#define lc root*2
#define rc root*2+1

using namespace std;
const int maxn=100005;

struct SegTreeNoed{
	int val;
}str[4*maxn];
int a[maxn];
int n,m,ans;

inline void push_up(int root)
{
	str[root].val=min(str[lc].val,str[rc].val);
}

inline void build(int root,int a[],int is,int ie)
{
	if(is==ie)
	{
		str[root].val=a[is];
		return;
	}
	else
	{
		int mid=(is+ie)>>1;
		build(lc,a,is,mid);
		build(rc,a,mid+1,ie);
		push_up(root);
	}
}

inline int query(int root,int is,int ie,int qs,int qe,int judge)
{
	if(is>qe||ie<qs) return -1;
	if(str[root].val>=judge) return -1;
	else
	{
		if(is==ie) return is;
		int k,mid=(is+ie)>>1;
		k=query(rc,mid+1,ie,qs,qe,judge);
		if(k!=-1) return k;
		else return query(lc,is,mid,qs,qe,judge);
	}
}

int main ()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	  scanf("%d",&a[i]);
	build(1,a,1,n);
	for(int i=1;i<=n;i++)
	{
		ans=query(1,1,n,i,n,a[i]);
		if(ans==-1) printf("-1 ");
		else printf("%d ",ans-i-1);
	} 
	return 0;
}
```

代码比较简单，望管理大大给过……

---

## 作者：ModestCoder_ (赞：7)

非常简单的题目

对于每个数，需要找到比自己小的下标最大的数，直接离散化然后开个以权值为下标的树状数组维护一下实际下标最大值就完事了

Code：

```cpp
#include <bits/stdc++.h>
#define maxn 100010
#define _ 0 
using namespace std;
struct data{
	int x, id;
}b[maxn];
int n, a[maxn], ans[maxn], tree[maxn], p;

inline int read(){
	int s = 0, w = 1;
	char c = getchar();
	for (; !isdigit(c); c = getchar()) if (c == '-') w = -1;
	for (; isdigit(c); c = getchar()) s = (s << 1) + (s << 3) + (c ^ 48);
	return s * w;
}

bool cmp(data x, data y){ return x.x < y.x; }
void update(int x, int y){ for (; x <= p; x += x & -x) tree[x] = max(tree[x], y); }
int query(int x){ int sum = 0; for (; x; x -= x & -x) sum = max(sum, tree[x]); return sum; }

int main(){
	n = read();
	for (int i = 1; i <= n; ++i) b[i] = (data){read(), i};
	sort(b + 1, b + 1 + n, cmp);
	b[0].x = b[1].x + 1;
	for (int i = 1; i <= n; ++i) a[b[i].id] = b[i].x == b[i - 1].x ? p : ++p;
	for (int i = n; i; --i){
		ans[i] = max(-1, query(a[i] - 1) - i - 1);
		update(a[i], i);
	}
	for (int i = 1; i <= n; ++i) printf("%d ", ans[i]);
	return 0 ^ _ ^ 0;
}
```


---

## 作者：王熙文 (赞：5)

## 思路

这题大家可能都想复杂了。

对于这种跟 $a$ 里具体的数没有关系，只有大小关系的题，可以先把 $a$ 数组离散化一下，这样值域就变成了 $[1,n]$。

定义一个数组 $ax$，$ax_i$ 表示小于等于 $i$ 的数中的**最大下标**。

那么我们可以先把等于 $i$ 的数更新，即 $ax_{a_i}=\max(ax_{a_i},i)$。

之后，对于 $i \in [2,n]$，都与 $ax_{i-1}$ 更新，类似前缀和的思想。

查询的时候对于每一个数输出 $ax_{a_i-1}$ 就好了。

## 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;

int a[100010],b[100010];

int ax[100010];

int main()
{
	memset(ax,-0x3f,sizeof(ax));
	int n;
	scanf("%d",&n);
	for(int i=1; i<=n; ++i) scanf("%d",&a[i]),b[i]=a[i];
	sort(b+1,b+n+1);
	int tot=unique(b+1,b+n+1)-b-1;
	for(int i=1; i<=n; ++i) a[i]=lower_bound(b+1,b+n+1,a[i])-b;
	for(int i=1; i<=n; ++i) ax[a[i]]=max(ax[a[i]],i);
	for(int i=2; i<=n; ++i) ax[i]=max(ax[i],ax[i-1]);
	for(int i=1; i<=n; ++i) printf("%d ",max(ax[a[i]-1]-i-1,-1));
	return 0;
}
```

---

## 作者：zhuweiqi (赞：4)

本题中的其它题解貌似都太复杂了，都用到了一些高级算法或数据结构，作者在这里介绍一种时间复杂度较低，代码简短，思路易懂，对萌新来说比较友好的一种方法。

题目大意：对于每个数 $a_i$，让你求出在它右边并且比它小的最右边的数的位置。

思路：二分查找即可，我们首先定义一个一维数组 $f$，令 $f_i=\max(f_i,...,f_n)$，显然 $f_i$ 可以逆序递推得来，然后对每个数 $a_i$ 进行二分查找，初始时令 $l=i+1,r=n$，每次取中间值 $mid=(l+r+1)\div 2$（注意，由于我们查找的是最右边的数（也就是靠右位置上的数），所以需要 $+1$），如果 $a_i>f_{mid}$ 说明在 $mid$ 后面有小于 $a_i$ 的数，$l=mid$ 继续往后查找；否则 $r=mid-1$ 往前查找。当 $l=r$ 时退出循环，如果此时 $a_i>f_l$，就说明 $a_l$ 是比 $a_i$ 小的最右边的数，输出 $l-i-1$；否则输出 $-1$。需要注意的是，当 $i=n$ 时需要特判并输出 $-1$，否则将会出现二分查找时 $l>r$ 的情况。参考代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100002];
int f[100002];
int main(){
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	f[n]=a[n];
	for(int i=n-1;i;i--) f[i]=min(a[i],f[i+1]);
	for(int i=1;i<n;i++){
		int l=i+1,r=n,mid,ans;
		while(l<r){
			mid=l+r+1>>1;
			if(a[i]>f[mid]) l=mid;
			else r=mid-1;
		}
		if(a[i]>f[l]) ans=l-i-1;
		else ans=-1;
		printf("%d ",ans);
	}
	printf("-1");
	return 0;
}
```

此方法的时间复杂度为 $O(n \log_2 n)$，空间复杂度为 $O(2n)$，是同级别复杂度的方法中代码最短的，也是最简单的，可见我们在做一道题目时选对做法的重要性。

---

## 作者：Tx_Lcy (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/CF91B)
## 思路
翻遍了所有题解发现没有像我这样的在单调队列上二分的思路。

考虑从右往左把数加入单调队列，如果当前的数比单调队列的队尾要大，显然不可能作为答案，因为明明有更右边且比它更小的数存在，所以不能加入单调队列。而如果当前的数比单调队列的队尾要小，显然可以加入单调队列，但是此时的答案是 $-1$，因为没有任何数比它小。

找答案的过程可以视为在单调队列上二分的过程，我们只需要找到第一个小于它的数即可。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int const N=1e5+10;
int a[N],ans[N];
struct node{int val,id;}q[N];
inline int find(int l,int r,int x){
	while (l<r){
		int mid=(l+r)>>1;
		if (q[mid].val<x) r=mid;
		else l=mid+1;
	}
	return q[l].id;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int n;cin>>n;
	for (int i=1;i<=n;++i) cin>>a[i];
	int top=0;
	for (int i=n;i>=1;--i)
		if (!top || a[i]<=q[top].val) ans[i]=-1,q[++top].val=a[i],q[top].id=i;
		else ans[i]=find(1,top,a[i])-i-1;
	for (int i=1;i<=n;++i) cout<<ans[i]<<' ';
	cout<<'\n';
	return 0;
}
```


---

## 作者：君のNOIP。 (赞：3)

~~离散化+树状数组？tql 本蒟蒻怎么可能想出来？~~

~~线段树？主席树？orz 本蒟蒻压根不会。~~


------------
### 数据范围：

- $N \le 10^5 $

一眼看这个范围，正解一般只能是 $ \Theta(NlogN) $ 了。

~~很显然，本蒟蒻不会正解。~~

 没关系， $N \le 10^5 $ ， 当然用~~暴力~~**分块**啦！


 
## 正片开始：

### **基本思路：**

- 定一个数组 $mi_i$ ，表示第 $i$ 块里の最小值。

- 从 1 到 $n$ ，每次从最后一块开始，for 循环一直到 $i$ 所在块の下一块。

- 若 $mi_j < a_i $ ，则for 循环暴力遍历第 $j$ 块，从后往前第一个 $< a_i$ の数の位置就是答案。

- 若 $i$ 后面の块里の数都不小于 $a_i$ ，就for 循环暴力从 $i$ 所在块右端暴力遍历到 $i+1$ ，从后往前第一个 $< a_i$ の数の位置就是答案。

- 若还没找到，直接输出 $-1$

- 看代码可能更好理解。

- 由于求间距，答案记得 -1 

- 还有最后一块の右端点要设成 $n$ 

### 时间复杂度： $ \Theta(N \sqrt{N} ) $ 

**代码如下：**


------------
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;
#define G() Cr=getchar()
int Xr;char Cr;
inline int rd(){   //读入优化
	Xr=0,G();
	while(Cr<'0'||Cr>'9')G();
	while(Cr>='0'&&Cr<='9')Xr=(Xr<<3)+(Xr<<1)+Cr-'0',G();
	return Xr;
}
#define MAX_N 100002
int n;
int block,num;
int pos[MAX_N],va[MAX_N];
int r[2000],mi[2000];  // l 用不着 。 

int solve(int t){
	for(int i=num;i>pos[t];i--) //最后一块开始
		if(mi[i]<va[t])      //符合条件
			for(int j=r[i];;j--)
				if(va[j]<va[t])return j-t-1;  //找到答案。 
				
	for(int i=r[pos[t]];i>t;i--) //当前块右端开始
		if(va[i]<va[t])return i-t-1;  //找到答案。 
		
	return -1;  //无答案。 
}
int main(){
	n=rd();
	block=(int)sqrt(n); //快大小。 
	num=(n-1)/block+1;  //总块数 。 
	for(int i=1;i<=n;i++)va[i]=rd(), pos[i]=(i-1)/block+1;
	for(int i=1;i<=num;i++)r[i]=i*block, mi[i]=2147483647;
	r[num]=n;  // 这里细节一定要注意。 
	for(int i=1;i<=n;i++)mi[ pos[i]]=min(mi[ pos[i]], va[i]); //预处理每块min 
	for(int i=1;i<=n;i++)printf("%d ",solve(i)); //用函数可以直接return更方便。 
}
```


------------

### ps:

码完后十分开心地交了（我先用树状数组写的）。

结果3.62s ，一看我用树状数组の，3.67s ？

~~果然暴力即正解！暴力出奇迹！~~

---

## 作者：xfrvq (赞：1)

## 逆序对问题

[原题链接](https://www.luogu.com.cn/problem/CF91B)

[博客食用](https://www.luogu.com.cn/blog/368107/solution-cf91b)



------------


 _**解法**_ 

Part 1.值域线段树介绍

归并排序可以解决统计逆序对总数的题目，但是如果要求第一个点是 $i$ 的逆序对，就需要用线段树或树状数组

以线段树为例 ~~其实我只会线段树~~

求逆序对的线段树叫做**值域线段树**

普通的线段树，第 $i$ 项在树中的位置，但值域线段树中，第 $x$ 项在树中的位置，统计的是值为 $x$ 项在输入数组中的出现次数

因为逆序对必须是编号比当前编号大而值比当前值小，所以求第一个点是 $i$ 的逆序对总数等于

$$query(i+1,n)$$

而将值为 $x$ 的数的总数加一就是

$$update(x,1)$$

Part 2.值域线段树实现

在第一部分中，值域线段树需开到 $4\times a_i$ 大小

假如 $a_i \lt 10^9$ 就直接MLE

这时就用到一种神奇的方法——**离散化**

离散化的大意就是：如果第 $i$ 个数是数组中第 $j$ 小的，则舍弃 $i$ ，用 $j$ 来代替

因为我们只关心数的大小，不关心值是多少，所以这样OK且省下了空间

我们定义一个结构体数组 $q$ ，$q_i$ 表示输入第 $i$ 个数的值与 编号( $i$ )

接着按值对 $q$ 排序（如果值相同，则按编号大小排序）

最后遍历 $q$ ，此时 第 $i$ 项的编号就是我们上文说到的代替 $i$ 的 $j$

可是main函数怎么写呢？

main函数流程图：

1. 输入 $n$ 与 $n$ 个数，并保存至 $q$ 中
2. 按数值给 $q$ 排序
3. 遍历 $q$ ：
	+ 把值域线段树中第 $q[i].id$ 项的位置加一
	+ 输出 $query(q[i].id + 1,n)$ 
    
Part 3.值域线段树代码：

求逆序对总数：

```cpp
#include<stdio.h>
#include<algorithm>
#define int long long
#define lc (i << 1)
#define rc (i << 1 | 1)
#define mid (L + R >> 1)
const int maxn = 100001;
int T[maxn << 2],n,ans = 0;
void push_up(int i){
	T[i] = T[lc] + T[rc];
}
void update(int p,int i = 1,int L = 1,int R = n){
	if(L == R){
		++T[i];
		return;
	}
	if(p <= mid) update(p,lc,L,mid);
	else update(p,rc,mid + 1,R);
	push_up(i);
}
int query(int l,int r,int i = 1,int L = 1,int R = n){
	if(l <= L && R <= r) return T[i];
	int res = 0;
	if(l <= mid) res += query(l,r,lc,L,mid);
	if(r > mid) res += query(l,r,rc,mid + 1,R);
	return res;
}
struct Query{
	int x,id;
	bool operator<(const Query& Q) const{
		return x != Q.x ? x < Q.x : id < Q.id;
	}
} q[maxn];
signed main(){
	scanf("%lld",&n);
	for(int i = 1;i <= n;++i) scanf("%lld",&q[i].x),q[i].id = i;
	std::sort(q + 1,q + n + 1);
	for(int i = 1;i <= n;++i){
		int id = q[i].id;
		update(id);
		ans += i - query(1,id);
	}
	printf("%lld\n",ans);
	return 0;
}
```

Part 4.本题的思路

~~然鹅以上并不是AC代码。。。~~

这题要求的是对于每个 $i$ ，逆序对 $(i,j)$ 中 $j$ 取最大时 $j-i-1$ 的值

由于并不是统计数量，所以线段树维护的也不是数量，**而是最大值**

什么意思呢？比如第 $i$ 号点在树中的位置的值表示的是 **与 $i$ 成逆序对的最大 $j$**

但也是值域线段树的思想

**_代码_**

```cpp
#include<stdio.h>
#include<algorithm>
#define lc (i << 1)
#define rc (i << 1 | 1)
#define mid (L + R >> 1)
#define Max(a,b) ((a) > (b) ? (a) : (b))
int T[400001],n;
void update(int p,int i = 1,int L = 1,int R = n){
	if(L == R){
		T[i] = p;
		return;
	}
	if(p <= mid) update(p,lc,L,mid);
	else update(p,rc,mid + 1,R);
	T[i] = Max(T[lc],T[rc]);
}
int query(int l,int r,int i = 1,int L = 1,int R = n){
	if(l <= L && R <= r) return T[i];
	int res = -1;
	if(l <= mid) res = Max(res,query(l,r,lc,L,mid));
	if(r > mid) res = Max(res,query(l,r,rc,mid + 1,R));
	return res;
}
struct Query{
	int x,id;
	bool operator<(const Query& Q) const{
		return x != Q.x ? x < Q.x : id < Q.id;
	}
} q[100001];
int ans[100001];
signed main(){
	scanf("%lld",&n);
	for(int i = 1;i <= n;++i) scanf("%lld",&q[i].x),q[i].id = i;
	for(int i = 0;i <= (n << 2);++i) T[i] = -1;
	std::sort(q + 1,q + n + 1);
	for(int i = 1;i <= n;++i){
		int id = q[i].id;
		update(id);
		int res = query(id + 1,n);
		if(res >= 0) ans[id] = res - id - 1;
		else ans[id] = -1;
	}
	for(int i = 1;i <= n;++i) printf("%d ",ans[i]);
	return 0;
}
```

---

## 作者：傅思维666 (赞：1)

## 题解：

首先概括题意：要求一个序列每一个位置最右侧的比自己小的数是谁。没有输出-1.

发现完全可以用线段树处理，维护一个区间最小值的线段树，查询的时候返回位置，每次优先查询右面。

有人说这叫线段树上二分，我觉得线段树本身就是二分的一个结构，所以不太算吧。

那么就直接上代码吧：

```cpp
#include<cstdio>
#include<algorithm>
#define lson pos<<1
#define rson pos<<1|1
using namespace std;
const int maxn=1e5+5;
int n;
int a[maxn];
int mn[maxn<<2];
void build(int pos,int l,int r)
{
    int mid=(l+r)>>1;
    if(l==r)
    {
        mn[pos]=a[l];
        return;
    }
    build(lson,l,mid);
    build(rson,mid+1,r);
    mn[pos]=min(mn[lson],mn[rson]);
}
int query(int pos,int l,int r,int x,int y,int k)//查询x-y区间中下标最大的小于k的数的下标
{
    int mid=(l+r)>>1;
    int ret=0;
    if(mn[pos]>=k)
        return -1;
    if(l==r)
        return l;
    if(y>mid)
    {
        ret=query(rson,mid+1,r,x,y,k);
        if(ret!=-1)
            return ret;
    }
    if(x<=mid)
        ret=query(lson,l,mid,x,y,k);
    return ret;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    build(1,1,n);
    for(int i=1;i<n;i++)
    {
        int ans=query(1,1,n,i+1,n,a[i]);
        if(ans==-1)
            printf("%d ",ans);
        else 
            printf("%d ",ans-i-1);
    }
    printf("-1");
    return 0;
}
```



---

## 作者：Catalan1906 (赞：1)

其他题解已经说了普通线段树的做法了，

但是这道题还有用主席树做的方法

（其实是我不会普通线段树的做法）

对于第$i$个人，建立一棵第$i$个人到第$n$个人的主席树

主席树里的节点$[l, r]$存：身高在$[l, r]$且站在最前面的人

每个人的不高兴度：以这个人建立的主席树中，身高在$[1, a_i-1]$范围内站在最前面的人

当然，本题还需要离散化

离散化复杂度：$O(n \log n)$

建初始树复杂度：$O(n \log n)$

给一个人建树复杂度：$O(\log n)$

单次查询复杂度：$O(\log n)$

总时间复杂度：$O(n \log n)$，空间复杂度：$O(n \log n)$

```cpp
#include <bits/stdc++.h>

using namespace std;

int n, a[100010], b[100010], cnt[100010], root[100010], tree[2000010], L[2000010], R[2000010], qwq;
map < int , int > mp;

void build(int &rt, int l, int r) {
	rt = ++qwq;
	if(l == r) return ;
	int mid = (l + r) >> 1;
	build(L[rt], l, mid);
	build(R[rt], mid + 1, r);
}

void update(int &rt, int rt1, int l, int r, int val, int pos) {
	rt = ++qwq;
	L[rt] = L[rt1], R[rt] = R[rt1], tree[rt] = tree[rt1];
	if(l == r) {
		if(!tree[rt]) tree[rt] = pos;
		return ;
	}
	int mid = (l + r) >> 1;
	if(val <= mid) update(L[rt], L[rt1], l, mid, val, pos);
	else update(R[rt], R[rt1], mid + 1, r, val, pos);
	tree[rt] = max(tree[L[rt]], tree[R[rt]]);
}

int query(int rt, int l, int r, int val) {
	if(val < l) return -1;
	if(r <= val) {
		if(!tree[rt]) return -1;
		return tree[rt];
	}
	int mid = (l + r) >> 1;
	int res = -1;
	res = query(L[rt], l, mid, val);
	if(val > mid) res = max(res, query(R[rt], mid + 1, r, val));
	return res;
}

int main() {
	cin >> n;
	for(int i = 1; i <= n; i++) {
		cin >> a[i];
		b[i] = a[i];
	}
	sort(b + 1, b + n + 1);
	b[0] = 0x7fffffff;
	int cnt = 0;
	for(int i = 1; i <= n; i++) {
		if(b[i] != b[i - 1]) cnt++, mp[b[i]] = cnt;
	}
	for(int i = 1; i <= n; i++) {
		a[i] = mp[a[i]];
	}
	build(root[n + 1], 1, cnt);
	for(int i = n; i; i--) {
		update(root[i], root[i + 1], 1, cnt, a[i], i);
	}
	for(int i = 1; i <= n; i++) {
		int qwq = query(root[i], 1, cnt, a[i] - 1);
		if(qwq == -1) cout << -1 << " ";
		else cout << qwq - i - 1 << " ";
	}
	cout << endl;
	return 0;
} 
```

---

## 作者：tiaotiao (赞：1)

## 无需线段树的神奇做法
总时间复杂度$O(nlogn)$

对于小数据其实可以$O(n)$

题意大概是有一串数，求出每个数和在其前面的比他小的最前面的数的距离

对于求两者距离的常用思想，只需要求出两者到队首的距离然后作差

这里我们定义 f 数组，f [ i ] 表示在年龄为 i 的人前面的最靠前的比他年轻的人距离队首的距离，那么对于编号为 i ，年龄为 a [ i ] 的人，其不高兴程度就是 ( n - i ) - f [ a [ i ] ] - 1 ，其中 n - i 为其自身与队首的距离（注意输入的队列顺序是倒序的），并且因为求的是间隔，所以需要多减1

那么我们可以从队首往队尾遍历，一边求答案一边更新 f 数组。由于排在后面的人即使年龄再小，也不会覆盖前面人的 f ，所以 f 的每个元素至多被更新一次，总复杂度为$O ( n )$

这样就结束了吗？并没有。我们注意到年龄最大是$ 10^9 $，因此 f 数组如果开这么大会直接爆空间（事实上编译都过不了）

考虑到人数最多只有$ 10^5$个，那么年龄最多也只有$ 10^5$种，题目只考虑年龄的大小而不考虑相对差，那么我们可以进行离散化处理。离散化复杂度$ O(nlogn) $

AC代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int inf = 0x3f3f3f3f;
//快速读入
ll rd(){register ll r=0,fh=1;register char c=getchar();while((c<'0'||c>'9')&&c!='-')c=getchar();if(c=='-')fh=-1,c=getchar();while(c>='0'&&c<='9')r=r*10+c-'0',c=getchar();return r*fh;}

#define MAXN 100005

int n;
int a[MAXN],b[MAXN];
int f[MAXN];
int ans[MAXN];

int main()
{
	memset(f,inf,sizeof(f));
	n = rd();
	//读入 + 离散化 
	for(int i = 1; i <= n; ++i)//编号小的为队尾 
		b[i] = a[i] = rd();
	sort(b+1,b+1+n);
	int cnt=1;
	for(int i = 2; i <= n; ++i)
		if(b[i] != b[cnt])b[++cnt] = b[i];
	for(int i = 1; i <= n; ++i)
		a[i] = lower_bound(b + 1, b + 1 + cnt, a[i]) - b;
	//处理数组f
	//f[i] 年龄小于i的第一个人与队首的距离 
	int j = cnt;
    	//j定义在前面，防止算法退化成O(n^2)
	for(int i = n; i >= 1; --i){//从队首开始处理 
		int dis = n - i;//到队首的距离 
		ans[i] = dis - f[a[i]] - 1;//求的是间隔距离，所以要 -1 
		if(ans[i] < 0)ans[i] = -1; 
		//加入f数组 
		for(; j >= a[i] + 1 && dis < f[j]; --j){
			f[j] = dis;
		}
	}
	//输出答案 
	for(int i = 1; i <= n; ++i)
		printf("%d ",ans[i]);
	printf("\n");
	return 0;
}
```

---

## 作者：registerGen (赞：1)

[更好的阅读体验](https://registergen.github.io/post/solution-cf91b/)

# Solution

标准的线段树上跑二分。

建出一棵维护 $a$ 的 $\min$ 的线段树。

对于每次查询，我们一定是尽可能往右子树跑。

具体细节见代码。

# Code

核心部分：

```cpp
int query(int i,int l,int r,int ql,int qr,int x){
	if(t[i].minn>=x)return -1; // 说明整个区间都没有小于 x 的数，返回 -1
	if(l==r)return l;
	int mid=(l+r)>>1;
	int res;
	if(qr>mid){ // 优先往右子树跑
		res=query(rs(i),mid+1,r,ql,qr,x);
		if(res!=-1)return res; // 如果有答案，则返回它
	}
	if(ql<=mid)return query(ls(i),l,mid,ql,qr,x); // 如果右子树没有答案，则往左子树跑
	return res;
}
```

完整代码：

```cpp
#include<cstdio>
#include<algorithm>

const int N=1e5;

struct Node{
	int minn;
};

int n,a[N+10];
Node t[N*4+10];

#define ls(x) (x<<1)
#define rs(x) (x<<1|1)

inline void pushUp(int i){t[i].minn=std::min(t[ls(i)].minn,t[rs(i)].minn);}
void build(int i,int l,int r){
	if(l==r)return t[i].minn=a[l],void();
	int mid=(l+r)>>1;
	build(ls(i),l,mid);
	build(rs(i),mid+1,r);
	pushUp(i);
}

int query(int i,int l,int r,int ql,int qr,int x){
	if(t[i].minn>=x)return -1;
	if(l==r)return l;
	int mid=(l+r)>>1;
	int res;
	if(qr>mid){
		res=query(rs(i),mid+1,r,ql,qr,x);
		if(res!=-1)return res;
	}
	if(ql<=mid)return query(ls(i),l,mid,ql,qr,x);
	return res;
}

#undef ls
#undef rs

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",a+i);
	build(1,1,n);
	for(int i=1;i<n;i++){
		int res=query(1,1,n,i+1,n,a[i]);
		if(res==-1)printf("-1 ");
		else printf("%d ",res-i-1);
	}
	puts("-1");
	return 0;
}
```

---

## 作者：yzx72424 (赞：1)

一道裸裸的线段树板子

建个保存着区间最小值的线段树，每次查询右子树优先

附上查询的子函数：

```
inline int cx(int num ,int pos, int l, int r, int id){
    if(l == r)return a[l]<num?l:-1;
    int m=(l+r)>>1,ans=-1;
    if(minn[id<<1|1]<num)
        ans =cx(num,pos,l,m,id<<1);
    else if(m > pos &&minn[id<<1] < num)//mid比所在位置大，才执行左子树。
        ans =cx(num,pos,m+1,r,id<<1|1);
    return ans;
}

```

---

## 作者：mango09 (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF91B)

[更好的观赏效果](https://www.luogu.com.cn/blog/305532/solution-cf91b)

---

**题目大意：**

- 给定 $n$ 个正整数 。
- 对于每一个数 $a_i$，需要输出一个答案：
	
    - 设 $a_j > a_i$ 且 $j > i$；
    - 在满足第一条的基础上使 $j-i-1$ 尽可能大，此时 $j-i-1$ 即为答案。
	- 若没有找到 $j$ 使得 $a_j > a_i$ 且 $j > i$，输出 $-1$。
    
---

**本题思路**

由 $a_j > a_i$ 且 $j > i$ 可以想到逆序对，既然刚学了值域线段树，那就用值域线段树吧。

[不会值域线段树的先做这题](https://www.luogu.com.cn/problem/P1908)

但注意数据范围：$a_i \le 10^9$，直接开数组会爆，故需**离散化**一下。

离散化很简单，举个例子：

$1\quad-100\quad5\quad-10^9$

离散化大概就是：**如果一个数 $i$ 是数组中第 $j$ 大（或小）的，那么就用 $j$ 来代替 $i$。**

上面的数组离散化就变成了（从大到小）

$2\quad3\quad1\quad4$

本题另一个需要注意的地方是：答案求的是最大值，所以线段树保存的是最大值。

---

**[$\color{black}\texttt{AC}$](https://www.luogu.com.cn/record/49796052) $\color{black}\texttt{CODE}$**

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#define lpos pos << 1
#define rpos pos << 1 | 1
using namespace std;

const int MAXN = 1e5 + 5;

int n;
int ans[MAXN];

struct num
{
	int val, id;
	bool operator <(const num &x)const
	{
		if (x.val == val)
		{
			return x.id > id;
		}
		return x.val > val;
	}
}a[MAXN];

struct tree
{
	int l, r, val;
}t[MAXN << 2];

void pushup(int pos)
{
	t[pos].val = max(t[lpos].val, t[rpos].val);
}

inline void build(int pos, int l, int r)
{
	t[pos].l = l, t[pos].r = r;
	if (l == r)
	{
		return;
	}
	int mid = (l + r) >> 1;
	build(lpos, l, mid);
	build(rpos, mid + 1, r);
}

inline void update(int pos, int dis)
{
	int l = t[pos].l, r = t[pos].r;
	if (l == r)
	{
		t[pos].val = dis;
		return;
	}
	int mid = (l + r) >> 1;
	if (dis <= mid)
	{
		update(lpos, dis);
	}
	else
	{
		update(rpos, dis);
	}
	pushup(pos);
}

inline int query(int pos, int L, int R)
{
	int l = t[pos].l, r = t[pos].r;
	if (l >= L && r <= R)
	{
		return t[pos].val;
	}
	int mid = (l + r) >> 1, res = -1;
	if (L <= mid)
	{
		res = query(lpos, L, R);
	}
	if (R > mid)
	{
		res = max(res, query(rpos, L, R));
	}
	return res;
}

int main()
{
	scanf("%d", &n);
	build(1, 1, n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i].val);
		a[i].id = i;
	}
	sort(a + 1, a + n + 1);
	for (int i = 1; i <= n; i++)
	{
		int id = a[i].id;
		update(1, id);
		int res = query(1, 1, n);
		if (res >= 0)
		{
			ans[id] = res - id - 1;
		}
		else
		{
			ans[id] = -1;
		}
	}
	for (int i = 1; i <= n; i++)
	{
		printf("%d ", ans[i]);
	}
	return 0;
}
```

---

## 作者：BreakPlus (赞：0)

开始还看不出来什么，然后发现因该是 $O(n \log n)$ 的，然后发现二分可做。

重点在于如何二分。

首先我们知道，想要让 $j-i-1$ 大，那么 $j$ 就需要尽量大。二分的时候我们要尽量往右，如果不能往右则“退而求其次”往左。问题在于如何判断是否可以往右。我们可以维护一颗线段树/一个ST表存储每个区间的最小值。如果右区间的最小值小于 $a_i$ ，那么可以往右区间，否则如果左区间的最小值小于 $a_i$，那么可以望左区间，再否则输出 $-1$ 跑路。

这样的话，时间复杂度就是 $n \log n$ 乘以一个二分的复杂度 $\log n$ 等于 $O(n \log^2 n)$。

下面提供本题代码。

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<windows.h>
using namespace std;
typedef long long ll;
#define maxn 100010
inline ll rd(){
    ll x=0,f=1; char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-') f=-1; ch=getchar();}
    while(ch>='0'&&ch<='9') {x=x*10+ch-'0'; ch=getchar();}
    return 1ll*x*f;
}
ll maxx(ll a,ll b){return a>b?a:b;}
ll minn(ll a,ll b){return a<b?a:b;}
void wr(ll x,char ch){
    printf("%lld%c",x,ch);
}
ll n,a[maxn],val[maxn<<2],ls[maxn<<2],rs[maxn<<2];
void pushup(ll pos){
    val[pos]=minn(val[pos<<1],val[pos<<1|1]);
}
void build(ll l,ll r,ll pos){
    ls[pos]=l,rs[pos]=r;
    if(l==r) {val[pos]=a[l]; return;}
    ll mid=l+r>>1ll;
    if(l<=mid) build(l,mid,pos<<1);
    if(mid<r) build(mid+1,r,pos<<1|1);
    pushup(pos);
}
ll query(ll l,ll r,ll pos){
    if(l<=ls[pos]&&rs[pos]<=r) return val[pos];
    ll mid=(ls[pos]+rs[pos])/2ll,ans=1e18;
    if(l<=mid) ans=query(l,r,pos<<1);
    if(mid<r) ans=minn(ans,query(l,r,pos<<1|1));
    return ans;
}
int main(){
    n=rd();
    for(ll i=1;i<=n;i++) a[i]=rd();
    build(1,n,1);
    for(ll i=1;i<n;i++){
        ll lft=i+1,rit=n,ansl,ansr1;
        bool _1=false;
        if(lft==rit){
            if(a[i]>a[n]) wr(0,' ');
            else wr(-1,' ');
            continue;
        }
        while(lft<rit){
            ll mid=lft+rit>>1;
            if(a[i]>query(mid+1,rit,1)){
                ansl=mid+1,ansr1=rit;
                lft=mid+1;
            }else if(a[i]>query(lft,mid,1)){
                ansl=lft,ansr1=mid;
                rit=mid;
            }else{
                _1=true;
                break;
            }
        }
        if(_1) wr(-1,' ');
        else wr(ansl-i-1,' ');
    }
    wr(-1,'\n');
    return 0;
}
```

---

## 作者：Fan_Tuan (赞：0)

# 题意
给出一个长度为n的序列，求序列中每一个元素与位于它右侧的离它最远的比它小的数的之间的数的个数。（~~我坚信我语文很好~~）
# 思路
线段树，节点保存区间最小值。每次将当前的数更新为INF，然后查找整个区间内最右边比它小的数的坐标。
# 代码
```
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<queue>
#include<iostream>
#define int long long
#define INF 1000000005
using namespace std;

const int maxn = 200005;
int n, a[maxn], s[maxn];

struct node{
	int l, r, minn;
}tree[maxn << 2];

void pushup(int rt) {
	tree[rt].minn = min(tree[rt << 1].minn, tree[rt << 1 | 1].minn); 
}

void build(int rt, int l, int r) {
	tree[rt].l = l;
	tree[rt].r = r;
	if (l == r) {
		s[l] = tree[rt].minn = a[l];
		return;
	}
	int mid = (l + r) >> 1;
	build(rt << 1, l, mid);
	build(rt << 1 | 1, mid + 1, r);
	pushup(rt);
}

int query(int rt, int l, int r, int x) {
	if (l == r) 
		return l;
	int mid = (l + r) >> 1;
	if (tree[rt << 1 | 1].minn < x) return query(rt << 1 | 1, mid + 1, r, x);
	else return query(rt << 1, l, mid, x);
}

void change(int rt, int l , int r, int x) {
	if (l == r) {
		tree[rt].minn = INF;
		return;
	}
	int mid = (l + r) >> 1;
	if (x <= mid) change(rt << 1, l, mid, x);
	else change(rt << 1 | 1, mid + 1, r, x);
	pushup(rt);
}

signed main() {
	scanf("%lld", &n);
	for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	build(1, 1, n);
	for (int i = 1; i <= n; i++) {
		change(1, 1, n, i);
		if (tree[1].minn >= s[i]) printf("-1 ");
		else printf("%lld ", query(1, 1, n, s[i]) - i - 1);
	}
	return 0;
}
```


---

## 作者：神之蒟蒻xyk (赞：0)

翻了一下大佬们的题解，发现没有人和我的思路相同。。。

一种比较好些的nlogn做法，没有用任何高级数据结构

a[i]表示年龄，f[]表示答案

整个序列，把所有年龄扔进大根堆。

再从右往左扫描序列，每次从堆中弹出大于当先a[]的所有人，并统计f
可以证明这是最远的。

还有一些小细节，具体看注释：

```cpp
#include<bits/stdc++.h>
#define fir(a, b, c) for(register int a = b; a <= c; a ++)
#define ll long long
using namespace std;

inline int read() {
	int x = 0; bool flag = 1; char c = getchar();
	for(; !isdigit(c); c = getchar())  if(c == '-') flag = 0;
	for(; isdigit(c); c = getchar()) x = x * 10 + c - '0';
	return flag ? x : -x;
}

typedef pair<int ,int> pl;
const int N = 1e5+10;
int n, a[N], f[N];
priority_queue<pl> q;

int main() {
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	n = read();
	fir (i, 1, n) {
		a[i] = read();
		q.push(make_pair(a[i], i));
	}
	fir (i, 1, n) f[i] = -2;//赋初值：-2表示还未处理
	for (int i = n; i >= 1; -- i) {
		if (f[i] != -2) continue;//如果已经标记过答案，说明比前面的年龄大，对其他答案就无贡献
		f[i] = -1;
		while (!q.empty() && q.top().first > a[i]) {
			if (f[q.top().second] != -2) {
				q.pop();
				continue;
			}
			f[q.top().second] = i-q.top().second-1;
			q.pop();
		}
	}
	fir (i, 1, n) printf("%d ", f[i]);
	printf("\n");
	return 0;
}



```



---

## 作者：洛容MX (赞：0)

一道CF~~大水~~题......

如有不足或错误，请在评论中指出或私信告诉我 ~~能憋着最好憋着~~

## 话不多说，进入正题

---------------------------------------------我是分割线---------------------------------------------


假设我们要求A的 “ 不高兴度 ”，那么根据题意，就是要找到一个人B，使得：
1. B的年龄比A小；
1. 在所有年龄比A小的人中，B离A最远；

那么B与A的距离就是A的 “ 不高兴度 ”。

其实大家也应该发现了，上述B所要满足的这两个关系，是存在一种 _递进关系_ 的，也就是说，**我们在寻找B时，可以现将所有比A小的人找出来，再去找其中离A最远的那个**，那个人就是B。

找比A年龄小的人的时候，可以用 **sort排序** 把比A年龄小的都弄到一个区间中，再在其中用 **线段树** 维护区间（距离）最大值。

综上所述，这道题的做法就是 **sort排序＋线段树**（~~我也不知道我为啥要再说一遍~~）

附上ＡＣ代码：
```cpp
//码风清奇请见谅 
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+2;
int n,v,maxn[4*N],idn[N];//maxn表示区间年龄最大值 
struct syzs{
    int id,num,ans;
} a[N];
bool cmp(syzs a,syzs b){
    return a.num<b.num;
}//按照年龄从小到大排序 
void build(int x,int y,int k){
    if(x==y){
    	maxn[k]=a[x].id;
    	return;
    } 
    int mid=x+y>>1,op=k<<1;
    build(x,mid,op);
    build(mid+1,y,op+1);
    maxn[k]=max(maxn[op],maxn[op+1]);
}
void ser(int x,int y,int k,int l,int r){
    if(x>=l&&y<=r){
    	v=max(v,maxn[k]);
    	return;
    }	
    int mid=x+y>>1,op=k<<1;
    if(mid>=l) ser(x,mid,op,l,r);
    if(mid<r) ser(mid+1,y,op+1,l,r);
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i].num);//输入年龄 
        a[i].id=i;
		//这里的id有两个含义：一个是i在队列中的位置，储存下来方便计算距离，另一个含义是记录下每个人在队列中的顺序，方便输出答案。 
    }
    sort(a+1,a+n+1,cmp);
    build(1,n,1);//初始化 
    for(int i=1;i<=n;i++){
        if(a[i].num==a[i-1].num) idn[i]=idn[i-1];
        else idn[i]=i-1;
		//由于队列中有可能有与A年龄相同的人，而这些人不能被考虑，所以要维护一个idn数组储存与A年龄最接近（且比A小）的人在现数组中的位置。 
        v=-1;//v 表示B在队列中的位置 
        if(idn[i]>=1) ser(1,n,1,1,idn[i]);//寻找B 
        a[a[i].id].ans=max(-1,v-a[i].id-1);//要注意本道题计算距离的方式；如果在比A年龄小的人中，没有一个站在A前面，根据题意，答案为-1.		
    }
    for(int i=1;i<=n;i++) printf("%d ",a[i].ans);//按照原本在队列中的顺序输出答案 
}
```
### 就这样吧......

---

