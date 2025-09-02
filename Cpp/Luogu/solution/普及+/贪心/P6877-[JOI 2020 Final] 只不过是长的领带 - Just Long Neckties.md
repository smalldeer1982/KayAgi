# [JOI 2020 Final] 只不过是长的领带 / Just Long Neckties

## 题目描述

JOI 公司发明了一种领带，一共有 $N+1$ 条领带，编号为 $1$ 到 $N+1$，第 $i$ 条领带的长度为 $A_i$。

JOI 公司开了一个派对，派对中有 $N$ 名员工，第 $j$ 名员工刚开始戴了长度为 $B_j$ 的领带。

派对这样举行：

1. 首先，JOI 公司的老板 JOI 君选出一条领带拿走。
2. 然后，每个员工选一条领带，保证没有两名员工选了相同的领带。
3. 最后，他们取下最先戴的领带，戴上选择的领带。

如果一名员工刚开始戴的领带长度为 $b$，选择的领带长度为 $a$，那么他就会产生 $\max\{a-b,0\}$ 的奇怪感，整场派对的奇怪程度为所有员工的奇怪感的最大值。

于是 JOI 君定义 $C_k$ 为他选出第 $k$ 条领带后的最小奇怪程度。

JOI 君想知道 $C_k$ 的具体值。

## 说明/提示

#### 样例 1 解释

让我们假设 JOI 君选择了第 $4$ 条领带，那么员工们可以这么选择：

- 第 $1$ 名员工选择第 $1$ 条领带，产生奇怪感 $2$
- 第 $2$ 名员工选择第 $2$ 条领带，产生奇怪感 $0$
- 第 $3$ 名员工选择第 $3$ 条领带，产生奇怪感 $3$

奇怪程度为 $3$。

但我们还可以继续减小奇怪程度：

- 第 $1$ 名员工选择第 $2$ 条领带，产生奇怪感 $1$
- 第 $2$ 名员工选择第 $3$ 条领带，产生奇怪感 $1$
- 第 $3$ 名员工选择第 $1$ 条领带，产生奇怪感 $0$

奇怪程度为 $1$。

因此 $C_4=1$。

#### 数据规模与约定

**本题采用捆绑测试。**

- Subtask 1（1 pts）：$N \le 10$。
- Subtask 2（8 pts）：$N \le 2000$。
- Subtask 3（91 pts）：无特殊限制。

对于 $100\%$ 的数据：

- $1 \le N \le 2 \times 10^5$。
- $1 \le A_i \le 10^9$。
- $1 \le B_j \le 10^9$。

#### 说明

翻译自 [第19回日本情報オリンピック　本選](https://www.ioi-jp.org/joi/2019/2020-ho/index.html) [A 長いだけのネクタイ](https://www.ioi-jp.org/joi/2019/2020-ho/2020-ho-t1.pdf)。

## 样例 #1

### 输入

```
3
4 3 7 6
2 6 4```

### 输出

```
2 2 1 1```

## 样例 #2

### 输入

```
5
4 7 9 10 11 12
3 5 7 9 11```

### 输出

```
4 4 3 2 2 2```

# 题解

## 作者：liangbowen (赞：24)

## 前言

[题目传送门！](https://www.luogu.com.cn/problem/P6877)

[更好的阅读体验？](https://www.cnblogs.com/liangbowen/p/16991114.html)

贪心。内容抄自某校课件。

## 思路

### 部分分

这个随便搞都可以，可以二分答案然后建边然后跑二分图最大匹配。

### 正解

考虑贪心。这里有一个很容易猜到或想到的结论：

> 将 $a$ 与 $b$ 从小到大排序，直接按位配对（$a_i$ 配 $b_i$），就是最优解。

设排序后的数组是 $a ^ \prime$ 与 $b ^ \prime$，也就是说我们要找到 $\min k$ 满足 $\forall a_i^\prime - b_i^\prime \le k$。那么很显然，答案就是 $\max\limits_{i = 1}^n (a_i^\prime - b_i^\prime)$。

然后问题就在于，迅速的维护这个东西了。

这个很简单：维护 $(a_i - b_i)$ 的前缀 $\max$ 与 $(a_{i + 1} - b_i)$ 的后缀 $\max$，然后挨个查询即可。

## 代码

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
const int N = 2e5 + 5;
struct Monkey {int val, id;} a[N];
bool cmp(Monkey p, Monkey q) {return p.val < q.val;}
int b[N], pre[N], suf[N], ans[N]; //pre[i]记录ai-bi前缀mx，suf[i]记录ai+1 - bi后缀mx
int main()
{
	ios::sync_with_stdio(false);
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n + 1; i++) scanf("%d", &a[i].val), a[i].id = i;
	for (int i = 1; i <= n; i++) scanf("%d", &b[i]);
	sort(a + 1, a + n + 2, cmp), sort(b + 1, b + n + 1);
	for (int i = 1; i <= n; i++) pre[i] = max(pre[i - 1], a[i].val - b[i]);
	for (int i = n; i; i--) suf[i] = max(suf[i + 1], a[i + 1].val - b[i]);
	for (int i = 1; i <= n + 1; i++) ans[a[i].id] = max(pre[i - 1], suf[i]);
	for (int i = 1; i <= n + 1; i++) printf("%d ", max(ans[i], 0));
	return 0;
}
```

希望能帮助到大家！

---

## 作者：Thunder_S (赞：8)

# Solution

首先排序，将 $A$ 和 $B$ 从小到大排序，同时记录 $A$ 中每个元素的排名。

考虑贪心，可以证得，在不删数字的情况下， $A_i$ 和 $B_i$ 对应最优。

简单证明：

假设 $A_i$ 不与 $B_i$ 对应，而是跟 $B_j(j<i)$ 对应，而 $A_j$ 和 $B_i$ 对应。

根据排序有 $A_i\ge A_j,B_i\ge B_j$。

那么 $A_i-B_j\ge A_j-B_j\ge A_j-B_i$，因此 $\max(A_i-B_j,A_j-B_i)=A_i-B_j\ge A_i-B_i$。

答案更劣。~~感性理解一下~~

那么在删去某个数字后，此数字前面的不变，但这个数字后面的要依次与前面的对应。

注意到是 1 至某个数字，某个数字到 $N$，这与前后缀十分相似。

而且 1 至某个数字是 $A_i-B_i$，某个数字到 $N$ 是 $A_{i+1}-B_i$。

所以在排完序后，求出 $A_i-B_i$ 的前缀和 $A_{i+1}-B_i$ 的后缀。

然后枚举，以这个数字在 $A$ 中的位置为断点，求出前后缀的 $\max$，就是答案。

# Code

```cpp
#include<cstdio>
#include<algorithm>
#define N 200005
using namespace std;
struct node
{
	int val,id;
}a[N];
int n,b[N],rk[N],c1[N],c2[N];
bool cmp(node x,node y) {return x.val<y.val;}
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n+1;++i)
		scanf("%d",&a[i].val),a[i].id=i;
	for (int i=1;i<=n;++i)
		scanf("%d",&b[i]);
	sort(a+1,a+1+n+1,cmp);
	sort(b+1,b+1+n);
	for (int i=1;i<=n;++i)
		c1[i]=max(c1[i-1],max(a[i].val-b[i],0));
	for (int i=n;i;--i)
		c2[i]=max(c2[i+1],max(a[i+1].val-b[i],0));
	for (int i=1;i<=n+1;++i)
		rk[a[i].id]=i;
	for (int i=1;i<=n+1;++i)
		printf("%d ",max(c1[rk[i]-1],c2[rk[i]]));
	return 0;
}
```



---

## 作者：White_gugu (赞：2)

题意：
-
给出数组A和数组B，求出删去A数组中的一个数后剩下的数和B数组的数一一配对， $\max \limits_{0<x<n+2,0<y<n+1}a_{x}- b_{y} $ 最小值为多少。

思路
-
首先确定一点：当删去某个数后，剩下的数按照大小排序后一一匹配必为最优。

原因：假设按照排序后的最大值为 $a_{i}$ $-$ $b_{i}$ ，那么 $a_{i}$ 一定大于 $b_{i}$ ，如果 $b_{i}$ 变为 $b_{i-1}$ ，那么最大值的值就会变大，唯一可行的就是 $b$ 往后移动，但是最后会发现始终有原来的 $b_{i}$ 无处安放（使最大值变大），故最优解为排序后一一匹配。

排序后，我们的问题就转化为：对于所有的 $i$ ,求出其 $1$ ~ $i$ $-$ $1$ 和 $i$ $+$ $1$ ~ $n$ $+$ $1$ 中的一一匹配后的最大值，为区间最大值维护，可以用线段树来解决（甚至比线段树模板更简单，因为不需要修改），维护两个区间的最大值即可。

代码
-
```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
struct node{
	int val,id;
}a[200200],b[200200];
int n; 
int tree1[4000400];
int tree2[4000400];
int an[200200];
bool cmp(node x,node y)
{
	return x.val<y.val;
}
void pushup(int k)
{
	tree1[k]=max(tree1[k*2],tree1[k*2+1]);
	tree2[k]=max(tree2[k*2],tree2[k*2+1]);
	return;
}
void build(int k,int l,int r)
{
	if(l==r)
	{
		tree1[k]=max(a[l].val-b[l].val,0);
		tree2[k]=max(a[l].val-b[l-1].val,0);
		return;
	}
	int mid=(l+r)/2;
	build(k*2,l,mid);
	build(k*2+1,mid+1,r);
	pushup(k);
}
int query1(int k,int l,int r,int L,int R)
{
	if(L<=l&&r<=R)
	return tree1[k];
	int mid=(l+r)/2;
	if(R<=mid)
	return query1(k*2,l,mid,L,R);
	else if(L>mid)
	return query1(k*2+1,mid+1,r,L,R);
	else
	return max(query1(k*2,l,mid,L,mid),query1(k*2+1,mid+1,r,mid+1,R));
}
int query2(int k,int l,int r,int L,int R)
{
	if(L<=l&&r<=R)
	return tree2[k];
	int mid=(l+r)/2;
	if(R<=mid)
	return query2(k*2,l,mid,L,R);
	else if(L>mid)
	return query2(k*2+1,mid+1,r,L,R);
	else
	return max(query2(k*2,l,mid,L,mid),query2(k*2+1,mid+1,r,mid+1,R));
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n+1;i++)
	{
		scanf("%d",&a[i].val);
		a[i].id=i;
	} 
	for(int i=1;i<=n;i++) 
	{
		scanf("%d",&b[i].val);
		b[i].id=i;
	}
	sort(a+1,a+n+2,cmp);
	sort(b+1,b+n+1,cmp);
	build(1,1,n+1);
	
	for(int i=1;i<=n+1;i++)
	{
		if(i!=1)
		an[a[i].id]=query1(1,1,n+1,1,i-1);
		if(i!=n+1)
		an[a[i].id]=max(an[a[i].id],query2(1,1,n+1,i+1,n+1));
	}
	for(int i=1;i<=n+1;i++)
	printf("%d ",an[i]);
}
```


---

## 作者：AbsMatt (赞：2)

## [题目传送器](https://www.luogu.com.cn/problem/P6877)
## [更爽的阅读体验](https://yaohaoyou.blog.luogu.org/solution-p6877)

# 题意
有两个数组 $a$ 和 $b$，满足 $a_i(i \in n+1)$ 且 $b_i(i \in n)$，有 $n+1$ 次操作，第 $i$ 次操作取出 $a_i$（操作完之后再放回去），问将 $b$ 数组重新排列后 $\max_{i=1}^{n}a_i-b_i$ 的最小值。

# 思路分析

这题的思路就是**贪心**。

贪心思路：分别把 $a$ 和 $b$ 数组排过序后，$a_i$ 和 $b_i$ 一一匹配即是最优解。

既然 $a_i$ 只能和 $b_i$ 匹配，那么题目就转变为：对于每一个 $x(1 \le x \le n+1)$，求出取出 $a_x$ 后的 $\max_{i=1}^{n}a_i-b_i$，直接处理需要 $O(n^2)$。

我们可以考虑用前后缀来解决，取出了 $a_x$ 后，对于 $\le x$ 的 $i$，最大值仍是 $\max(a_i-b_i)$，此时可以维护前缀。但是对于 $\ge x$ 的 $i$，最大值变成了 $\max(a_{i+1}-b_i)$，此时可以维护后缀，所以每次只需查询两者的最大值即可，贪心部分时间复杂度便降为了 $O(n)$。

# 总结
第一眼其实我看到 $1 \le n \le 2 \times 10^5$ 时，认为这道题是**二分答案**，但最后正解是**贪心**，这道题最终的时间复杂度为 $O(n \times \log_2 n)$，极限为排序。

# AC Code
```cpp
#include<bits/stdc++.h>  // 开始了
using namespace std;
const int maxn=2e5+10;
int n,b[maxn];
pair<int,int> a[maxn];
int pre[maxn],nxt[maxn],ans[maxn];  // 前后缀，答案数组。
int main(){
    // 输入
	scanf("%d",&n);
	for(int i=1;i<=n+1;i++){
		scanf("%d",&a[i].first);
		a[i].second=i;
	}
	for(int i=1;i<=n;i++)	scanf("%d",&b[i]);

    // 两次排序
	sort(a+1,a+n+2);
	sort(b+1,b+n+1);

    // 前后缀
	pre[0]=nxt[n+1]=0;
	for(int i=1;i<=n;i++){
		pre[i]=max(pre[i-1],a[i].first-b[i]);
	}
	for(int i=n;i>0;i--){
		nxt[i]=max(nxt[i+1],a[i+1].first-b[i]);
	}
	for(int i=1;i<=n+1;i++){
		ans[a[i].second]=max(pre[i-1],nxt[i]);
	} 

    // 输出
	for(int i=1;i<=n+1;i++){
		printf("%d ",max(0,ans[i]));
	}
    return 0;  // 拜拜
}
```

---

## 作者：HDZmessi (赞：1)

贪心。

此题基本上基础定理都被其他大佬说了，例如排序后的一一对应之类，但有些定理很难理解原因，大佬们都没有证明，蒟蒻着手两个东西用样例证明一下。

第一个就是前缀和后缀的那玩意儿，具体结论我也说不清楚。我们不妨简单一点，直接把排序好的样例拿来研究研究。

排序好的样例如下：

```cpp
3 4 6 7

2 4 6

```



下标分别是从 $0$ 到 $3$（蒟蒻习惯从 $0$ 开始）。

分 $4$ 种情况讨论

1. 如果老板拿走长度为 $3$ 的领带，则答案为 $\max(a _ {1}-b _ {0},a _ {2}-b _ {1},a _ {3}-b _ {2})$。

1. 如果老板拿走长度为 $4$ 的领带，则答案为长为 $4$ 的前缀和最大值，与长为 $4$ 的后缀最大值进行比较，取最大。

后面的就依次类推，都是前缀最大和后缀最大进行比较，取最大的，但后缀不是一一对应，说明白点就是斜着对应。

第二个就是为什么大佬们都要用结构体了，开始蒟蒻没把这个想明白 WA 了无数次，其实很简单，刚才上述的证明过程是建立在排序好了的情况下，所以需要先排序，而排序后的输出顺序是不对的，例如排序前老板先会取走长为 $4$ 的领带，而排序后先取的是长为 $3$ 的领带，所以需要一个结构体保存下标，然后再按照最正确的顺序输出。

AC Code:

```cpp
#include<iostream>  //cin,cout
#include<cstdio> //scanf
#include<algorithm> //max
#define r register int  //这样貌似速度更快 
using namespace std;
const int N=2e5+5;  //定义边界 
int n,b[N],f[N],h[N],ans[N];
struct node{
	int f,u;  //结构体 
}a[N];
bool operator <(node x,node y){
	return x.f<y.f;   //重载小于号，排序。 
}
int main(){
	scanf("%d",&n);
	for(r i=0;i<=n;i++) cin>>a[i].f,a[i].u=i; //记录下标 
	for(r i=0;i<n;i++) cin>>b[i];
	sort(a,a+n+1);sort(b,b+n);  
	for(r i=1;i<=n;i++) f[i]=max(f[i-1],(a[i-1].f-b[i-1]));  //前缀依次记录最大 
	for(r i=n-1;i>=0;i--) h[i]=max(h[i+1],(a[i+1].f-b[i]));  //后缀 
	for(r i=0;i<=n;i++){
		ans[a[i].u]=max(f[i],h[i]);  //一定要改正顺序！！ 
	}
	for(r i=0;i<=n;i++){
		ans[i]=max(ans[i],0); //这行代码是为什么？审题去！ 
		cout<<ans[i]<<" ";
	}
	return 0; //华丽结束 
} 
```
管理员给过谢谢啦～

---

## 作者：CYZZ (赞：1)

# [P6877 选领带](https://www.luogu.com.cn/problem/solution/P6877)
一个小贪心。
# 思路分析
考虑贪心，这题的结论比较容易猜：分别把 $A$ 和 $B$ 数组排过序后，$A
_i$ 和 $B_i$ 一一匹配即是最优解。

既然 $A_i$ 只能和 $B_i$ 匹配，那么题目就转变为：对于每一个 $k(1 \le k \le n+1)$，求出抽出 $A_k$ 后的 $\max(A_i-B_i)$，$i \in [1,n]$。关键就在于怎么用 $O(n)$ 的时间处理出来。

我们考虑用前后缀解决。拿出了 $A_k$ 后，对于小于 $k$ 的 $i$，最大值仍是 $\max(A_i-B_i)$，维护前缀。但是对于大于等于 $k$ 的 $i$，最大值变成了 $\max(A_{i+1}-B_i)$，维护后缀。所以我们每次只需查询两者的最大值即可。
# 代码实现
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,b[200005],sum1[200005],sum2[200005],idx[200005];
struct ties
{
	int v,id;
}a[200005];
bool cmp(ties x,ties y)
{
	return x.v<y.v;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n+1;i++)
	{
		scanf("%d",&a[i].v);
		a[i].id=i;//要记录原来的编号，排序后会打乱。
	}
	sort(a+1,a+n+2,cmp);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&b[i]);
	}
	sort(b+1,b+n+1);
	for(int i=1;i<=n;i++)
	{
		sum1[i]=max(max(a[i].v-b[i],0),sum1[i-1]);//维护前缀
	}
	for(int i=n;i>=1;i--)
	{
		sum2[i]=max(max(a[i+1].v-b[i],0),sum2[i+1]);//维护后缀
	}
	for(int i=1;i<=n+1;i++)
	{
		idx[a[i].id]=i;
	}
	for(int i=1;i<=n+1;i++)
	{
		printf("%d ",max(sum1[idx[i]-1],sum2[idx[i]]));
	}
	return 0;
}
```
希望本篇题解可以帮到大家！！！

---

## 作者：冷笑叹秋萧 (赞：1)

## 题意
有两个数组 $a[i](i\in n+1)$ ， $b[i](i\in n)$ ，有 $n+1$ 次操作，第 $i$ 次操作取出 $a[i]$ （操作完之后再放回去），问将 $b$ 数组重新排列后 $\max(a[i]-b[i])(i \in n)$ 的最小值。
## 题解
~~好不容易模拟赛有一道签到题~~ 

首先可以显然证明，在拿掉一个领带后，将剩下的领带长度从大到小排序，把人本来戴着的领带长度从小到大排序，然后一一对应来取 $\max(0,a[i]-b[i])$ 是可以使最大值最小的。

然后我们就可以每次都这样做，于是可以得到一个 $O(n^2\log n)$ 的算法，只能拿到 50 分。

显然以上算法浪费了很多的操作，我们知道将 $n+1$ 个领带排好序后，取一个领带出来，那这个领带左边的（也就是比它长的）贡献是不会受到影响的
所以我们可以写两个线段树，一个统计排序后的 $\max(0,a[i]-b[i])$ 的区间最大值 $max1$ ，一个统计排序后的 $\max(0,a[i+1]-b[i])$ 的区间最大值 $max2$ 。

然后找到拿走的领带在排序后的位置 $num$ ，查询这个点左边的 $max1$ 和右边的 $max2$ 再取较大的那个即可，复杂度 $O(n\log n)$ 轻松通过。

当然也可以记录前缀最大值和后缀最大值然后进行相同的操作，复杂度 $O(n)$ 。
## CODE（线段树法）

```cpp
#include<cstdio>
#include<string>
#include<algorithm>
#define R register int
#define N 200005
#define ll long long
using namespace std;
int n,tree1[N<<2],tree2[N<<2],num[N],c1[N],c2[N],b[N];
struct arr{int x,id;}a[N];
int max(int a,int b) {return a>b?a:b;}
int min(int a,int b) {return a<b?a:b;}
void read(int &x)
{
	x=0;int f=1;char ch=getchar();
	while (!isdigit(ch)) {if (ch=='-') f=-1;ch=getchar();}
	while (isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=getchar();x*=f;
}
bool cmp(arr x,arr y) {return x.x>y.x;}
bool cmp1(int x,int y) {return x>y;}
void build1(int u,int l,int r)
{
	if (l==r) {tree1[u]=c1[l];return;}
	int mid=l+r>>1;build1(u<<1,l,mid);build1(u<<1|1,mid+1,r);
	tree1[u]=max(tree1[u<<1],tree1[u<<1|1]);
}
void build2(int u,int l,int r)
{
	if (l==r) {tree2[u]=c2[l];return;}
	int mid=l+r>>1;build2(u<<1,l,mid);build2(u<<1|1,mid+1,r);
	tree2[u]=max(tree2[u<<1],tree2[u<<1|1]);
}
int find1(int u,int l,int r,int x,int y)
{
	if (l>=x && r<=y) return tree1[u];
	int mid=l+r>>1,res=0;
	if (x<=mid) res=max(res,find1(u<<1,l,mid,x,y));if (y>mid) res=max(res,find1(u<<1|1,mid+1,r,x,y));
	return res;
}
int find2(int u,int l,int r,int x,int y)
{
	if (l>=x && r<=y) return tree2[u];
	int mid=l+r>>1,res=0;
	if (x<=mid) res=max(res,find2(u<<1,l,mid,x,y));if (y>mid) res=max(res,find2(u<<1|1,mid+1,r,x,y));
	return res;
}
int main()
{
	read(n);
	for (R i=1;i<=n+1;++i)
		read(a[i].x),a[i].id=i;
	for (R i=1;i<=n;++i)
		read(b[i]);
	sort(a+1,a+1+n+1,cmp);sort(b+1,b+1+n,cmp1);
	for (R i=1;i<=n+1;++i)
		num[a[i].id]=i;
	for (R i=1;i<=n;++i)
		c1[i]=max(a[i].x-b[i],0),c2[i]=max(a[i+1].x-b[i],0);
	build1(1,1,n);build2(1,1,n);
	for (R i=1;i<=n+1;++i)
	{
		if (num[i]==1) printf("%d ",find2(1,1,n,1,n));
		else if (num[i]==n+1) printf("%d ",find1(1,1,n,1,n)); 
		else printf("%d ",max(find1(1,1,n,1,num[i]-1),find2(1,1,n,num[i],n)));
	}
	printf("\n");
	return 0;
}
```

---

## 作者：Hexarhy (赞：1)

### Preface

大家好，我喜欢暴力无脑解法，所以我用平衡树的 $1 \log$ 解法过了这题。

~~杀鸡得用牛刀。~~

### Solution

想让奇怪程度尽可能小，就让每个人选更小的 $a_i$。很快就能得到一种贪心思路：对 $a_i$ 和 $b_i$ 排序，离线回答 $C_k$，每个 $b_i$ 对 $a_i$ 作差。

正确性显然。假设一个 $b_i$ 选了更大的 $a_j$ ，那么会留下一个更小的 $a_i$ 没被选，如果让更大的 $b_j$ 去选择 $a_i$，那么两者代价是 $a_j-b_i$；但显然 $\max\{a_i-b_i,a_j-b_j\}$ 代价更小。

考虑如何做到多次询问。离线做，从小到大枚举剔除的 $a_i$ 来询问。

此时剩下的与 $b_i$ 一一对应作差。但只要手玩一下样例就能发现，每次剔除一个 $a_i$，受影响的只有一个 $b_i$，而且改变的对应关系只有从 $b_i\to a_i$ 变成 $b_i\to a_{i-1}$。

观察下列表格就能明白受影响的是哪些。表格中数字取自样例 #1。第一行是 $a_i$，其余 $4$ 行是不同询问下的答案。

|   3    |   4    |   6    |   7    |
| :----: | :----: | :----: | :----: |
| JOI 君 |   2    |   4    |   6    |
|   2    | JOI 君 |   4    |   6    |
|   2    |   4    | JOI 君 |   6    |
|   2    |   4    |   6    | JOI 君 |


答案是这些差值的最大值，因此可以用一个**可删堆**动态地维护这些差值，非常直观方便。

时间复杂度 $O(n\log n)$。其实前后缀做法也是 $O(n\log n)$，瓶颈却在排序，本身是线性的。

### Notice

可删堆的实现一般有如下方法：

- 对 STL 很熟练，使用 `multiset`。
- 使用两个 `priority_queue`。
- 平衡树。

笔者考场写前两个出了锅，因此很无脑地写了平衡树……

### Code

用的 WBLT。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cctype>
#include <climits>
#include <cstring>
using namespace std;

namespace IO
{
    inline char getc(void)
    {
        static const int IN_LEN=1<<21|1;static char buf[IN_LEN],*s,*t;
        return (s==t)&&(t=(s=buf)+fread(buf,1,IN_LEN,stdin)),s==t?-1:*s++;
    }
    template<typename tp>
    void read(tp& a)
    {
        register tp num=0;register int f=1;register char ch=getc();
        while(!isdigit(ch) && ch!='-') ch=getc();
        if(ch=='-') f=-1,ch=getc();
        do
            num=num*10+int(ch-'0'),ch=getc();
        while(isdigit(ch));
        a=num*f;
    }
}using namespace IO;

const int MAXN=4e5+10;
int n;
struct data
{
    int val,id;
    bool operator<(const data& a)const
    {
        if(val!=a.val)  return val<a.val;
        return id<a.id;
    }
}a[MAXN];
int b[MAXN],ans[MAXN];

class WBLT
{
private:
    typedef const int cint;
    struct node
    {
        node *lson,*rson;
        int val,w;
        node(){}
        node(node *Lson,node *Rson,cint Val,cint W)
		{
			lson=Lson;rson=Rson;val=Val;w=W; 
		}
    }*null,*root,tr[MAXN<<1],*pool[MAXN<<1];
    cint ratio=4;int tot;
    inline node* newnode(node* lson,node* rson,cint val,cint w)
    {
        return &(*pool[tot++]=node(lson,rson,val,w));
    }
    inline node* merge(node* u,node* v)
    {
        return newnode(u,v,v->val,u->w+v->w);
    }
    inline void maintain(node* cur)
    {
        if(cur->lson->w>cur->rson->w*ratio)
        {
            cur->rson=merge(cur->lson->rson,cur->rson);
            pool[--tot]=cur->lson;
            cur->lson=cur->lson->lson;
        }
        if(cur->rson->w>cur->lson->w*ratio)
        {
            cur->lson=merge(cur->lson,cur->rson->lson);
            pool[--tot]=cur->rson;
            cur->rson=cur->rson->rson;
        }
    }
    inline void pushup(node* cur)
    {
        if(cur->lson==null || cur->rson==null)  return;
        cur->w=cur->lson->w+cur->rson->w;
        cur->val=cur->rson->val;
    }
    void insert(node* cur,cint val)
    {
        if(cur->w==1)
        {
            cur->lson=newnode(null,null,min(cur->val,val),1);
            cur->rson=newnode(null,null,max(cur->val,val),1);
        }
        else if(val<=cur->lson->val) insert(cur->lson,val);
        else    insert(cur->rson,val);
        pushup(cur);
        maintain(cur);
    }
    void erase(node *cur,cint val)
    {
        if(cur->lson->w==1 && cur->lson->val==val)
        {
            pool[--tot]=cur->lson;pool[--tot]=cur->rson;
            *cur=*cur->rson;
        }
        else if(cur->rson->w==1 && cur->rson->val==val)
        {
            pool[--tot]=cur->rson;pool[--tot]=cur->lson;
            *cur=*cur->lson;
        }
        else if(val<=cur->lson->val)    erase(cur->lson,val);
        else    erase(cur->rson,val);
        pushup(cur);
        maintain(cur);
    }
    int kth(node* cur,cint k)
    {
        if(cur->w==1)   return cur->val;
        if(k<=cur->lson->w) return kth(cur->lson,k);
        return kth(cur->rson,k-cur->lson->w);
    }
public:
    inline int top(void)    {return kth(root,root->w-1);}
    inline void insert(cint val)    {insert(root,val);}
    inline void erase(cint val) {erase(root,val);}
    inline void reset(void)
    {
        null=new node(NULL,NULL,0,0);
        memset(tr,0,sizeof(tr));
        for(register int i=0;i<(MAXN<<1);++i)    pool[i]=&tr[i];
        root=new node(null,null,INT_MAX,1);
    }
}t;

void solve(void)
{
    t.reset();
    for(register int i=1;i<=n;++i)   t.insert(max(0,a[i+1].val-b[i]));
    ans[a[1].id]=t.top();
    for(register int i=1;i<=n;++i)
    {
        t.erase(max(0,a[i+1].val-b[i]));
        t.insert(max(0,a[i].val-b[i]));
        ans[a[i+1].id]=t.top();
    }
}

int main()
{
    read(n);
    for(register int i=1;i<=n+1;++i)    a[i].id=i;
    for(register int i=1;i<=n+1;++i)    read(a[i].val);
    for(register int i=1;i<=n;++i)      read(b[i]);
    sort(a+1,a+2+n);sort(b+1,b+1+n);
    solve();
    for(register int i=1;i<=n+1;++i)    cout<<ans[i]<<' ';
    cout<<endl;
    return 0;
}
```

---

## 作者：NewJeanss (赞：1)

蒟蒻比较菜，所以从一个完全萌新的角度来讲讲蒟蒻怎么思考的。

首先，关注到我们的答案是**所有**员工的奇怪感的**最大值**。很明显的**二分答案**特点。

因为员工的顺序不影响答案，所以想到**从小到大排序**。为什么要排序？因为排序后可以做到 $\mathcal{O}(n)$ （暴力）处理。如果 $a[i].a-b[j]>x$ ，那么没有 $a[i].a$ 能和 $b[j]$ 配对，使得差小于 $x$ 。

所以蒟蒻写了一个二分：

```cpp
void solve(int x,int p){//假设答案是x，第p条领带被选了
	int t=0;
	for(int i=1;i<=n;i++){
		if(i==p) t=1;
		if(a[i+t].a-b[i]>x) return false;
	}
	return true;
}
```

然而可以发现，每一次判断二分答案的复杂度是 $\mathcal{O}(n)$ ,总复杂度 $\mathcal{O}(n^2 \log k)$ ， $k$ 是二分范围，只有可怜的9分。

所以在此基础上**优化**。发现每一次`for(int i=1;i<p;i++)` 这一段是**重复**做了。可以预处理。

同理`for(int i=p;i<=n;i++)` 这一段也可以预处理处其中的最大值，直接和 $x$ 比较。

为了保留思考痕迹，在最终答案中还是保持了二分的结构：

```
#include <bits/stdc++.h>
#define N 200005
using namespace std;
int n,x,y,ans[N],Max1[N],Max2[N]，b[N];
struct peo{ int a,id; }a[N];
bool cmp(peo a,peo b){ return a.a<b.a; }
inline bool check(int x,int p){
	if(Max1[p-1]>x) return false;
	if(Max2[p]>x) return false;
	return true;
}
signed main(){
	ios::sync_with_stdio(false); cin.tie(0);
	while(cin>>n){
		for(int i=1;i<=n+1;i++) cin>>a[i].a,a[i].id=i;
		for(int i=1;i<=n;i++) cin>>b[i];
		sort(b+1,b+n+1);
		sort(a+1,a+n+2,cmp);
		for(int i=1;i<=n;i++) Max1[i]=max(Max1[i-1],a[i].a-b[i]);//前缀 
		for(int i=n;i>=1;i--) Max2[i]=max(Max2[i+1],a[i+1].a-b[i]);//后缀 
		for(int i=1;i<=n+1;i++){
			int l=a[1].a-b[1],r=a[n+1].a;//二分范围 
			while(l<=r){
				int mid=(l+r)>>1;
				if(check(mid,i)) r=mid-1;
				else l=mid+1;
			}
			ans[a[i].id]=l;
		}
		for(int i=1;i<=n+1;i++) cout<<ans[i]<<" ";
		cout<<endl;
	}
	return 0;
}
```

------------

先写**暴力**（通过找题目中的**关键词->算法**），再优化，对于蒟蒻我还是很有用的。

---

## 作者：rainygame (赞：0)

比较平凡的一道题。

首先可以发现一个简单的性质，取最大的 $A_i$ 和最大的 $B_j$ 配一定是最优的，同理，取最小的 $A_i$ 和最小的 $B_j$ 配也一定是最优的。这样我们可以先对 $A$ 和 $B$ 排序处理。

排序之后，我们可以发现，在有序的 $A$ 里面相邻地换“空位”，只会影响一个人的产生的值，所以问题转化为：

给定一些数，需要满足一些询问：

- 把其中一个 $x$ 改为 $y$。
- 求这些数最大值。

这可以用 `multiset` 维护，将 $x$ 删除并添加一个 $y$ 即可，注意 `multiset` 的删除方式。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define MAXN 200002

int n, now;
int b[MAXN], ans[MAXN];
multiset<int, greater<int>> st;

struct Node{
    int ind, val;
}a[MAXN];

bool cmp(Node a, Node b){
    return a.val < b.val;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    for (int i(1); i<=n+1; ++i){
        cin >> a[i].val;
        a[i].ind = i;
    }
    for (int i(1); i<=n; ++i) cin >> b[i];
    sort(a+1, a+n+2, cmp);
    sort(b+1, b+n+1);

    for (int i(1); i<=n; ++i) st.insert(max(a[i+1].val-b[i], 0ll));
    ans[a[1].ind] = *st.begin();
    for (int i(2); i<=n+1; ++i){
        st.insert(max(a[i-1].val-b[i-1], 0ll));
        st.erase(st.find(max(a[i].val-b[i-1], 0ll)));
        ans[a[i].ind] = *st.begin();
    }
    for (int i(1); i<=n+1; ++i) cout << ans[i] << ' ';

    return 0;
}

```


---

## 作者：Light_Star_RPmax_AFO (赞：0)


#### 前言

[传送门](https://www.luogu.com.cn/problem/P6877)


[更好的阅读体验](https://www.luogu.com.cn/blog/JJL0610666/post-ti-xie)

# 这题的思路——贪心

为了让 $a-b$ 最小，我们需要把小的与小的配对，

我们便可以得出将 $A_i$ 与 $B_i$ 排序后再配对就可以得出最优解。

接下来，我们定义一个结构体用来储存领带的信息，因为领带有两个信息如下：第几条与长度。
```cpp
struct yu{
    int na,x;// na 用来记录第几条领带，x 是领带长度。
}a[200020];
```

------------
因为结构体不能直接用 sort 函数排序，所以我们写一个 cmp 函数。

此函数意思为给出两个需要排序的数，如果小的是在前面返回 true。（也就是正序）。
```cpp
bool cmp(yu a,yu b){return a.x<b.x; }
```


------------


## 这题的难点，敲黑板
因为，我们有 $n+1$ 条领带，而只有 $n$ 个人，所以我们不能直接去找最大值，不然就会少一条领带没有奇怪程度。

看到这题后我们发现很像前后缀，所以，我们这题可以使用前后缀来使每个领带都有值。

我们需要取前缀 $A_i-B_i$ 的最大值和后缀 $A_{i+1}-B_i$ 的最大值。

```cpp
for(int i=1;i<=n+1;i++)
        qian[i]=max(qian[i-1],a[i].x-b[i]);//用来记录前缀
    for(int i=n;i;i--)
        hou[i]=max(hou[i+1],a[i+1].x-b[i]);//用来记录后缀
    for(int i=1;i<=n+1;i++)
        ans[a[i].na]=max(hou[i],qian[i-1]);//前缀与后缀的最大值便是答案
```


------------
## 代码

结论得出，接下来就是你们要看的环节。

```cpp
#include<bits/stdc++.h>
using namespace std;

inline int read() {
    char ch = getchar(); int x = 0, f = 1;
    while(ch < '0' || ch > '9') {
        if(ch == '-') f = -1;
        ch = getchar();
    } while('0' <= ch && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    } return x * f;
}//快读，使用 scanf 或者 cin 都可以。

struct yu{
    int na,x;
}a[200020];
bool cmp(yu a,yu b){return a.x<b.x; }
int b[200020],ans[200020],qian[200020],hou[200020];// b 用来记录员工原领带长。

int  main(){
    int n;
    cin>>n;
    for(int i=1;i<=n+1;i++)
        a[i].x=read()，a[i].na=i;//因为最后我们还需要按顺序输出所以我们要储存编号。
    for(int i=1;i<=n;i++)b[i]=read();//前面是正常的读入。
    
    sort(a+1,a+2+n,cmp);
    sort(b+1,b+1+n);//使用 sort 快排。
    
    for(int i=1;i<=n+1;i++)
        qian[i]=max(qian[i-1],a[i].x-b[i]);
    for(int i=n;i;i--)
        hou[i]=max(hou[i+1],a[i+1].x-b[i]);
    for(int i=1;i<=n+1;i++)
        ans[a[i].na]=max(hou[i],qian[i-1]);//前后缀得出答案。
        
    for(int i=1;i<=n+1;i++)
        cout<<max(ans[i],0)<<" ";//不要忘记题目中写的，max（A-B,0)
    return 0;
}
```
[AC 记录](https://www.luogu.com.cn/record/99330823)

QWQ ，本人第一次写题解请见谅。



---

## 作者：LCat90 (赞：0)

[更好的阅读体验？](https://www.luogu.com.cn/blog/487539/solution-p6877)

题目要求我们求出 $\max \left\{\max \left\{a_i-b_j,0 \right\}\right\}$

首先考虑**贪心**：若要使答案最小，即两个数之间的差值尽量小。所以将数组分别从小到大排序后，得到的答案肯定最小。

然后暴力枚举拿掉第 $k$ 个领带的答案 $(1\leq k\leq N+1)$，这样的时间复杂度为 $O(n^2)$，无法通过。

可以发现，在每次统计答案的时候，设当前枚举到 $i$，我们只需求出 $[1,i-1]$ 中 $a_i-b_i$ 的最大值 和 $[i+1,n+1]$ 中 $a_i-b_{i-1}$ 的最大值（排完序后的数组）。

这是不是很像**前缀和**？所以我们利用前缀和优化，从而**直接求出**答案。统计答案的时间复杂度为 $O(n)$。但是排序的时间复杂度是 $O(n\log n)$，所以总的时间复杂度是 $O(n\log n)$，可以通过本题。

**注意：排序过后打乱了答案的编号，应按照输入顺序输出（见参考代码）。**

**参考代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int Maxn = 2e5 + 5;
int n, b[Maxn], pre1[Maxn], pre2[Maxn], tp[Maxn], c[Maxn], t[Maxn];
struct node {
	int x, id; // 存储下标
} a[Maxn];
bool cmp(node a, node b) {
	return a.x < b.x;
}
inline int read();
int main() {
	scanf("%d", &n);
	for(int i = 1;i <= n + 1; ++i) a[i].x = read(), a[i].id = i;
	for(int i = 1;i <= n; ++i) b[i] = read();
	sort(a + 1, a + n + 2, cmp);
	sort(b + 1, b + n + 1);
	for(int i = 1;i <= n; ++i) pre1[i] = max(0, max(pre1[i - 1], a[i].x - b[i])); // 求 i 前面的最大值
	for(int i = n + 1;i >= 2; --i) pre2[i] = max(0, max(pre2[i + 1], a[i].x - b[i - 1])); // 求 i 后面的最大值
	for(int i = 1;i <= n + 1; ++i) c[i] = max(0, max(pre1[i - 1], pre2[i + 1])); // 统计答案
	for(int i = 1;i <= n + 1; ++i) t[a[i].id] = i; // 存储输出的下标
	for(int i = 1;i <= n + 1; ++i)
		printf("%d ", c[t[i]]); // 按原顺序输出
	return 0;
}

inline int read() {
    register char c;
    register int f = 1, sum = 0;
    while(c < '0' or c > '9') {
    	if(c == '-') f = -1;
    	c = getchar();
    }
    while(c >= '0' and c <= '9') {
        sum = (sum << 3) + (sum << 1) + (c ^ 48);
        c = getchar();
    } 
    sum *= f;
    return sum;
}
```

---

## 作者：祖国的花梗 (赞：0)

**题目大意**

给你一个长度为 $\textbf{n+1}$ 的序列 $\textbf{A}$ ,还有一个长度为 $\textbf{n}$ 的序列 $\textbf{B}$ ，每次将 $\textbf{A[i](1}\sim\textbf{n)}$ 从 $\textbf{A}$ 序列中删除，并将 $\textbf{A}$ 序列剩下的数与 $\textbf{B}$ 序列的数一 一配对，使得差值最大值最小，输出每次操作的答案。

**思路**

首先我们发现将要使差值最小，肯定是将两个序列中最小的两个数字相减，第二小的相减……一直到最大的和最大的相减

然后我们继续思考，拿样例来说（排完序后）

序列 $\textbf{A}$ ： 3 4 7 6  
序列 $\textbf{B}$： 2 4 6   

当我们把3这个数从 $\textbf{A}$ 序列删除，那么 $\textbf{B}$ 序列所有的数则分别向后移一位匹配，即：

序列 $\textbf{A}$：~~3~~ 4 7 6  
序 列 $\textbf{B}$ ：   2 4 6  
这样匹配才是差值最小

当我们把4这个数从 $\textbf{A}$ 序列中删除，那么与4这个数匹配的数以及后面的数全部往后移一位匹配，前面的数并没有影响

由此我们可以发现规律
当我们把 $\textbf{A[i]}$ 这个数从数组删除时，只会对 $\textbf{B[i]}\sim\textbf{B[n]}$ 这些数造成影响，前面 $\textbf{B[1]}\sim\textbf{B[i-1]}$ 依然是一 一匹配，而后面 $\textbf{B[i]}\sim\textbf{B[n]}$ 则是往后移一位与 $\textbf{A[i+1]}\sim\textbf{A[n+1]}$ 匹配。

所以我们只需要预处理出两个数组

$\textbf{Maxn[i]}$ 表示前 $\textbf{i}$ 个 $\textbf{A[i]}$ 与 $\textbf{B[i]}$ 匹配差值的最大值  
$\textbf{Maxn2[i]}$ 表示后 $\textbf{i}$ 个 $\textbf{A[i+1]}$ 与  $\textbf{B[i]}$ 匹配差值的最大值

$\textbf{O(n)}$跑一边即可  
**注意：排序完之后，数字的位置会发生改变，所以要记录下来下标**

以下为代码：
```c
#include<bits/stdc++.h>
using namespace std;
struct Van{ int x,date; }a[200005];
int n,b[200005],ans[200005],maxn[200005],maxn2[200005];

bool cmp(Van a,Van b){ return a.x<b.x; }

int main()
{
	scanf("%d",&n);
	for(register int i=1;i<=n+1;i++) scanf("%d",&a[i].x),a[i].date=i;
	for(register int i=1;i<=n;i++) scanf("%d",&b[i]);
	sort(a+1,a+n+2,cmp); sort(b+1,b+n+1);
	for(register int i=1;i<=n;i++)
		maxn[i]=max(maxn[i-1],max(a[i].x-b[i],0));
	for(register int i=n;i>=1;i--)
		maxn2[i]=max(maxn2[i+1],max(a[i+1].x-b[i],0));
	for(register int i=1;i<=n+1;i++)
		ans[a[i].date]=max(maxn[i-1],maxn2[i]);
	for(register int i=1;i<=n+1;i++)
		printf("%d ",ans[i]);
	return 0;
}
```
蒟蒻第一次写题解，有问题还请指出。

---

## 作者：gi_A (赞：0)

首先考虑所有 $a_i$ 都参与选择的情况：第 $i$ 小的 $b$ 选择第 $i$ 小的 $a$（即：**小的配小的，大的配大的**）。

然后考虑每一条领带被拿走后的变化：少了一个选择 ~~（废话）~~ 。仍然使用上述策略，于是就可以写出 $O(n^2)$ 的暴力（每次去掉一个 $a$，排序，找最大值）。

发现拿走第 $i$ 小的 $a$ 时，会改变选择的是第 $j$（$i\le j\le n$）的 $b$，这些 $b$ 的选择策略是 **向后移一位** （没拿时，$b_j$ 选择 $a_j$，拿走后 $b_j$ 选择 $a_{j+1}$）。

因此，我们可以从大到小枚举拿走的 $a$，每拿一个，就将它对应的 $b$ 的选择向后移一位。

具体见代码：

```cpp
bool cmp(const dian &a,const dian &b){//对a排序
	return a.x<b.x;//（a.x是a的值，a.id是对应在原序列中的编号）
}
int main()
{
	n=read();n++;//为了方便将n加1
	for(int i=1;i<=n;i++){
		a[i].x=read();
		a[i].id=i;
	}
	sort(a+1,a+1+n,cmp);
	for(int i=1;i<n;i++)b[i]=read();
	sort(b+1,b+n);
	int ans=0;
	for(int i=1;i<n;i++)ans=max(ans,a[i].x-b[i]);//不拿
	anss[a[n].id]=ans;//拿第n（题目中的n+1）大的a不会影响答案
	for(int i=n-1;i>=1;i--){//从大到小拿
		ans=max(ans,a[i+1].x-b[i]);//拿走i后，b[i]与a[i+1]配对
		anss[a[i].id]=ans;//记录答案
	}
	for(int i=1;i<=n;i++)cout<<anss[i]<<" ";
	return 0;
}
```


---

## 作者：Paris_Bentley (赞：0)

先说结论：一个典型的排序+前缀预处理题目。

按照题目的要求，我们先考虑 N 个人有 N 个项链时，那么原始领带长度从小到大第 i 长的人如果有新领带中第 i 长的那么就能得到最小的奇怪值。（数学推导，偷懒就不证明了，感兴趣的可以反证法证明一下）

所以，那对于这个题目，是不是我们就只需要每次删掉一个领带，然后排序求一次值就可以得到最后的奇怪值了。但是看看数据量，有 n 次询问，每次排序再计算会得到非常大的值。
所以我们就要对于每组数据都进行一次排序和一次遍历。这样很显然会 TLE ，所以我们就要选择一种“聪明”一点的方法。

我们会发现每次排序后的大概顺序其实是不变的，我们可以通过得到每个数的前缀最大值得到这个数前的最大值 l[i] 那后面的怎么办呢？？当然是再来一次后缀了，这样对于每个数，他前面的最大值和后面的最大值确定，就能得出当前状态下的结果了。




```cpp
#include<bits/stdc++.h>
using namespace std;
struct Node
{
	int val,id;
}a[200005];
bool cmp(Node x,Node y)
{
	return x.val<y.val;
}
int b[200005],l[200005],r[200005],ans[200005];//领带，前缀max，后缀max 
int n;
int main()
{
	scanf("%d",&n);
	for (register int i=1;i<=n+1;i++)
	{
		scanf("%d",&a[i].val);
		a[i].id=i;
	}	
	for (register int i=1;i<=n;i++)
		scanf("%d",&b[i]);
	sort(b+1,b+n+1);
	sort(a+1,a+n+2,cmp);
	for (register int i=1;i<=n;i++)
		l[i]=max(l[i-1],a[i].val-b[i]);//,cout<<l[i]<<" ";cout<<endl;
	for (register int i=n+1;i>1;i--)
		r[i]=max(r[i+1],a[i].val-b[i-1]);//,cout<<a[i].val<<" "<<b[i-1]<<" "<<r[i]<<"   ";cout<<endl;
	for (register int i=1;i<=n+1;i++)
		ans[a[i].id]=max(l[i-1],r[i+1]);
	for (register int i=1;i<=n+1;i++)
		printf("%d ",ans[i]);
	return 0;
 } 
```


---

## 作者：Time_tears (赞：0)

首先我们有一个很简单的贪心，大的对应大的，小的对应小的。

但是由于每次会删掉一个，我们考虑会对贡献产生什么影响。

注意到 $b_i$ 只会和 $a_i$ and $a_{i+1}$ 产生贡献，那么直接做一个前缀和和后缀和。

对于每次查询加起来即可。

```cpp
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#include<cstdio>
#include<algorithm>
#define N 200005
using namespace std;
int sum1[N],sum2[N];
int n,a[N],ans[N];
#define O4 __inline__ __attribute__((always_inline))
struct node {
	int x,id;
	O4 bool operator <(node a) const {
		return x<a.x;
	}
} b[N];
const int Mxdt=200000;
O4 char gc() {
	static char buf[Mxdt],*p1=buf,*p2=buf;
	return p1==p2&&(p2=(p1=buf)+fread(buf,1,Mxdt,stdin),p1==p2)?EOF:*p1++;
}
O4 char pc(char ch,bool bj) {
	static char buf[Mxdt],*p1=buf,*p2=buf+Mxdt;
	return (bj||(*p1++=ch)&&p1==p2)&&fwrite(p1=buf,1,p1-buf,stdout),0;
}
O4 int read() {
	int res=0;
	char ch=gc();
	while(ch<'0')ch=gc();
	while(ch>='0')res=(res<<3)+(res<<1)+(ch^48),ch=gc();
	return res;
}
void print(int x) {
	if(x>9)print(x/10);
	pc(x%10^48,false);
}
O4 void printnum(int x,char ch) {
	print(x),pc(ch,false);
}
O4 int Max(int a,int b) {
	return a>b?a:b;
}
int nt=65535,bb[200002],h[65536],nx[200002];
inline void T_Sort(int a[],int n) {
	int i,p;
	for(i=1; i<=n; ++i)nx[i]=h[a[i]&nt],h[a[i]&nt]=i;
	for(i=0,p=n+1; i<=nt; ++i)while(h[i])bb[--p]=a[h[i]],h[i]=nx[h[i]];
	for(i=1; i<=n; ++i)nx[i]=h[bb[i]>>16],h[bb[i]>>16]=i;
	for(i=p=0; i<=nt; ++i)while(h[i])a[++p]=bb[h[i]],h[i]=nx[h[i]];
}

int main() {
	n=read();
	for(int i=1; i<=n+1; ++i)b[i].x=read(),b[i].id=i;
	for(int i=1; i<=n; ++i)a[i]=read();
	T_Sort(a,n),sort(b+1,b+n+2);
	for(int i=1; i<=n; ++i)sum1[i]=Max(sum1[i-1],Max(b[i].x-a[i],0));
	for(int i=n; i; --i)sum2[i]=Max(sum2[i+1],Max(b[i+1].x-a[i],0));
	for(int i=1; i<=n+1; ++i)ans[b[i].id]=Max(sum1[i-1],sum2[i]);
	for(int i=1; i<=n+1; ++i)printnum(ans[i],' ');
	return pc('h',true);
}
```


---

## 作者：gyh20 (赞：0)

贪心。

如果是 $n$ 个数匹配 $n$ 个数，肯定大的匹配大的，小的匹配小的，sort 即可。

首先我们先将两个数组排序，当删除第 $i$ 个数时对于所有 $b_j(j<i)$ 匹配 $a_j$，对于所有 $b_j(j\geq i) $ 匹配 $a_{j+1}$，记录前缀最大值和后缀最大值即可。

```cpp
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#include<cstdio>
#include<algorithm>
#define re register
using namespace std;
struct node{int val,id;bool operator <(const node x)const{return val<x.val;};}p[200002];
int n,b[200002],pre[200002],suf[200002],ans[200002];
const int Mxdt=200000;	//单次大小 
inline char gc(){
	static char buf[Mxdt],*p1=buf,*p2=buf;
	return p1==p2&&(p2=(p1=buf)+fread(buf,1,Mxdt,stdin),p1==p2)?EOF:*p1++;
}
inline int read(){
	re int t=0;re char v=gc();
	while(v<'0')v=gc();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=gc();
	return t;
}
int nt=65535,bb[200002],h[65536],nx[200002];
inline void T_Sort(int a[],int n)
{
	int i,p;       //稍稍帮你用位运算优化了哈（%太慢了）
	for(i=1;i<=n;++i)nx[i]=h[a[i]&nt],h[a[i]&nt]=i;     //前向星乱搞
	for(i=0,p=n+1;i<=nt;++i)      //这里也是O(n)的，注意b倒序
	while(h[i])bb[--p]=a[h[i]],h[i]=nx[h[i]];      //按后16位排
	for(i=1;i<=n;++i)nx[i]=h[bb[i]>>16],h[bb[i]>>16]=i;
	for(i=p=0;i<=nt;++i)
	while(h[i])a[++p]=bb[h[i]],h[i]=nx[h[i]];      //按前16位排
}
int main(){
	n=read();
	for(re int i=1;i<=n+1;++i)p[i].val=read(),p[i].id=i;
	for(re int i=1;i<=n;++i)b[i]=read();
	sort(p+1,p+n+2),sort(b+1,b+n+1);
	for(re int i=1;i<=n;++i)pre[i]=max(pre[i-1],p[i].val-b[i]);ans[p[n+1].id]=pre[n];
	for(re int i=n;i;--i)suf[i]=max(suf[i+1],p[i+1].val-b[i]),ans[p[i].id]=max(pre[i],suf[i]);
	for(re int i=1;i<=n+1;++i)printf("%d ",ans[i]);
}
```


---

