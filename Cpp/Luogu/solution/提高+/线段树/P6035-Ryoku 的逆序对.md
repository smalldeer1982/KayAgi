# Ryoku 的逆序对

## 题目背景

Ryoku 并不知道这题的背景是什么。

## 题目描述

Ryoku 有一个正整数 $\{1,2,\cdots,n\}$ 的排列 $A = \{a_i\}$。

她告诉你一个序列 $B = \{b_i\}$，表示对于每个数 $a_i$，对于所有 $j>i$ 有 $b_i$ 个数可以与 $a_i$ 组成逆序对（逆序对的定义是：满足 $i>j$ 且 $a_i < a_j$ 的一组 $(a_i, a_j)$ 称作一对逆序对）。

不幸的是，Ryoku 给你的序列 $B$ 有一些位置污损了，你想知道有多少个可能的排列 $A$ 能符合条件。

请你输出答案并构造一个**字典序最小**的排列 $A$（对于排列 $A = \{a_i\},\ A' = \{a'_i\}$ 若存在某个位置 $i$，使得 $\forall j < i, a_j = a'_j$ 且 $a_i < a'_i$，则 $A$ 的字典序小于 $A'$）。

## 说明/提示

**【样例 1 说明】**

对于 $5$，存在逆序对 $(5,2),(5,3),(5,4)$ 共三对。

**【样例 2 说明】**

符合条件的排列有：$\{1, 5, 4, 2, 3\}, \{1, 5, 3, 2, 4\}, \{1, 5, 2, 3, 4\}$。共三种，其中字典序最小的为 $\{1, 5, 2, 3, 4\}$。

---

**【数据规模与约定】**

对于 $10\%$ 的数据，$b_i \neq -1$。  
对于另外 $10\%$ 的数据，$n \le 10$。  
对于另外 $10\%$ 的数据，$b_i = -1$。  
对于另外 $30\%$ 的数据，$n \le 10^3$。  
对于另外 $30\%$ 的数据，$n \le 10^5$。  
对于 $100\%$ 的数据，$0< n \le 10^6$，$-1 \le b_i \le n$。

## 样例 #1

### 输入

```
5
0 3 0 0 0
```

### 输出

```
1
1 5 2 3 4```

## 样例 #2

### 输入

```
5
0 3 -1 0 0
```

### 输出

```
3
1 5 2 3 4```

## 样例 #3

### 输入

```
5
0 3 -1 0 1
```

### 输出

```
0```

# 题解

## 作者：feecle6418 (赞：6)

第一问，每个为 `-1` 的位置 $i$ 都会造成 $n-i+1$ 种可能，由乘法原理，乘起来就是答案。重点在第二问。

贪心地从前往后拼凑。假如 $a$ 之后有 $b$ 个比他小，就从小到大找第 $b+1$ 个还没被选到的数 $x$，并令 $a\leftarrow x$。假如是 `-1`，就找当前没有选到的最小值。

现在的问题是怎么维护“第 $k$ 个还没被选到的数”。可以使用树状数组，在树状数组上倍增往上跳，同时累加前缀和，加到 $k+1$ 时就是答案。

这样说很抽象，看代码：

```cpp
#include<bits/stdc++.h>
#define mod 1000000007
using namespace std;
int c[1000005],a[1000005],ans[1000005],used[1000005],n,now=1,s=1;
void Update(int x,int k) {
	while(x<=n)c[x]+=k,x+=x&-x;
}
int Find(int x) {
	int ret=0,now=0;
	for(int i=19; i>=0; i--) {
		if((ret+(1<<i))<=n&&now+c[ret+(1<<i)]<=x)ret+=(1<<i),now+=c[ret];//		cout<<now<<' '<<ret<<endl;
	}
	return ret+1;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]),Update(i,1);
		if(a[i]>n-i)return puts("0"),0;
		if(a[i]==-1)s=1ll*s*(n-i+1)%mod;
	}
	printf("%d\n",s);
	for(int i=1;i<=n;i++){
		if(~a[i]){
			ans[i]=Find(a[i]);
			Update(ans[i],-1);
			used[ans[i]]=1;
		}
		else {
			while(used[now])now++;
			ans[i]=now;
			Update(ans[i],-1);
			used[ans[i]]=1;
		}
		printf("%d ",ans[i]);
	}
	return 0;
}
```

---

## 作者：JohnVictor (赞：5)

这道题和下列题目存在“撞题”嫌疑.

https://www.luogu.com.cn/problem/UVA11525

看到$b_i$的定义是在$a_i$之后的逆序对，立刻想到康托展开.

而在康托展开中，每一组合法的$b_i$恰对应着一个排列，所以我们只要对于$b_i=-1$求出它有多少种合法的情况即可.

而$b_i$不大于$i$后面数的个数，也就是$n-i$.这个只要在输入的时候特判即可.

```cpp
for(int i=1;i<=k;i++){
    	scanf("%d",&s[i]);
    	if(s[i]>k-i){
    		cout<<0<<endl;
    		return;
		}
		
```
也可以类似的得出，如果第$i$位是$-1$，那么它有$0,1,...,n-i$共$n-i+1$种可能，只要开一个变量ans存一下即可,也就是

```cpp
		if(s[i]==-1)s[i]=0,sol=one*sol*(k-i+1)%p;
		tree.Insert(1,1,k,i);
	}
```
之后就是逆康托展开的模板了，可以见我前面的链接，用维护$k$大$k$小的数据结构维护即可.

核心代码都在上面了，剩下的都是板子.

---

## 作者：pyqpyq (赞：3)

首先把[链接](https://www.luogu.com.cn/problem/P6035)放上再步入正题。
# 题目分析
初看题目没什么头绪，但我们可以先拿样例一分析一下：
```
输入#1
5
0 3 0 0 0

输出#1
1
1 5 2 3 4
```
我们一个数一个数分析：

第一个数 $b_1$ 为 $0$，表示 $a_1$ 后面没有数与它可以构成逆序对，故 $a_1$ 只能为目前可选的数中最小的 $1$，因为如果为其他数，则 $1$ 就会在它后面并与它构成逆序对，与条件矛盾。

第二个数 $b_2$ 为 $3$，而它后面只有 $3$ 个数，则表明它与后面每一个数都与它够成逆序对，同理可得 $a_2$ 只能为目前可选的数中最大的，故为 $5$。

第三个数 $b_3$ 为 $0$，与 $b_1$ 情况一样，不过 $1$ 已经被选了，只能选目前可选的数中最小的 $2$ 了。

$b_4$ 与 $b_5$ 方法同上，最后可以得到唯一答案 $1 5 2 3 4$。

到这里应该可以总结出来：$a_i$ 就是目前可选的数中第 $b_i+1$ 大的数。

原因很简单：把第 $b_i+1$ 大的数选出来后，后面会有 $b_i$ 个数比它小，正好构成 $b_i$ 个逆序对。

而可选的数没有 $b_i+1$ 个就构成无解。

以上是没有 $b_i$ 为 $-1$ 的 $10$ 分部分分的情况。而有 $-1$ 呢？

我们会发现，$b_i$ 为 $-1$ 时，选出任意可选的数后，剩下的数构成的方案数都相同。

感性理解一下，在分析完以上的步骤时，会发现方案的可行性与数值已经没有太大关联了。当 $a_i$ 任意取完后，并不影响剩下的数构成方案的合法性。

然而由于要给出字典序最小的，所以当 $b_i$ 为 $-1$ 时，我们选可选的数中最小的数输出。
# 具体实现
回顾上述过程，我们发现要维护一个集合（当前可选的数），支持三种操作：

* ~~初始化~~
* 查找第 $k$ 大（选出 $a_i$ ）
* 删除指定元素（因为 $a$ 是排列，元素不重复，选出$a_i$后要把它删掉）

再看数据范围 $0<n≤10^6$，很明显要用 $O(nlogn)$ 时间复杂度~~或n方过百万~~。

所以神仙就可以打平衡树，而我这个蒟蒻就只能打权值线段树了。

权值线段树中每个节点维护的是当前**数值**区间中剩下的数的个数。（剩下的看代码吧）

~~谢天谢地不用离散化。~~
# 参考代码
码风见谅……~~应该好懂吧~~
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a,s[1000011],tree[4000011];
long long ans=1;
int build(int i,int l,int r)
{
	if(l==r)
		return tree[i]=1;
	else
		return tree[i]=build(i<<1,l,l+r>>1)+build(i<<1|1,(l+r>>1)+1,r);
}
int molify(int i,int x,int l,int r)
{
	if(l==r)
		return tree[i]=0;
	else if(l<=x&&x<=l+r>>1)
		return tree[i]=molify(i<<1,x,l,l+r>>1)+tree[i<<1|1];
	else if((l+r>>1)+1<=x&&x<=r)
		return tree[i]=tree[i<<1]+molify(i<<1|1,x,(l+r>>1)+1,r);
}
int query(int i,int x,int l,int r)
{
	if(l==r)
		return l;
	else if(1<=x&&x<=tree[i<<1])
		return query(i<<1,x,l,l+r>>1);
	else if(tree[i<<1]+1<=x&&x<=tree[i])
		return query(i<<1|1,x-tree[i<<1],(l+r>>1)+1,r);
}
int main()
{
	scanf("%d",&n);
	build(1,1,n);
	for(int i=1;i<=n;++i)
	{
		scanf("%d",&a); 
		if(a==-1)
		{
			if(i>=n+1)
			{
				printf("0");
				return 0;
			}
			molify(1,s[i]=query(1,1,1,n),1,n);
			ans=ans*(n-i+1)%1000000007;
		}
		else
		{
			if(a+i>=n+1)
			{
				printf("0");
				return 0;
			}
			molify(1,s[i]=query(1,a+1,1,n),1,n);
		}
	}
	printf("%d\n",ans);
	for(int i=1;i<=n;++i)
		printf("%d ",s[i]);
	return 0;
}
```
$ans$ 和 $s$ 记录答案，$tree$ 为权值线段树。

完结撒花\\(^o^)/

---

## 作者：WYXkk (赞：2)

我觉得这题显然没有蓝啊，顶多绿吧。

这是一道非常显然的结论题。

首先，$b_i+1$ 就是第 $i$ 个数在 $a_i\sim a_n$ 中的相对排名，所以一旦剩下的数集确定了，且 $b_i\neq-1$，那么 $a_i$ 也是唯一确定的。

因此，对于每个 $b_i=-1$，这个数可以任意选择，不会对后面数的造成影响，所以 $ans=\prod\limits_{b_i=-1}(n-i+1)$。

接下来考虑最小化这个排列的字典序，很显然每次 $b_i=-1$ 的直接选最小的即可。

样例四对这两个结论的提示性太强了，建议去掉。

所以我们只需要写一个能初始化，查询第 $k$ 小并删除的数据结构就好了。

平衡树，权值线段树都可以。这里我使用了权值线段树。

$\texttt{code:}$

```cpp
#include<cstdio>
#include<iostream>
#include<fstream>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
#define Set(a) memset(a,0,sizeof(a))
#define F(i,a,b) for(register int i=a,i##end=b;i<=i##end;++i)
#define UF(i,a,b) for(register int i=a,i##end=b;i>=i##end;--i)
#define openf(a) freopen(#a".in","r",stdin);freopen(#a".out","w",stdout)
#define re register
#define ri re int
#define il inline
typedef long long ll;
typedef unsigned long long ull;
template<typename T> inline T rd(T& x)
{
	T f=1;x=0;char c=getchar();
	for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
	for(; isdigit(c);c=getchar()) x=(x<<3)+(x<<1)+(T)(c-'0');
	x*=f;
	return x;
}
ll rd(){ll x;rd(x);return x;}
inline int max(int a,int b){return a>b?a:b;}
inline int min(int a,int b){return a<b?a:b;}
const int inf=1<<30;

const int N=1000005;
const ll p=1000000007;
int a[N];
ll ans=1;
int tree[N<<2];
int n;
void build(int k,int l,int r)
{
	tree[k]=r-l+1;
	if(l!=r) {int mid=(l+r)>>1;build(k<<1,l,mid);build(k<<1|1,mid+1,r);}
}
void del(int pos)
{
	int k=1,l=1,r=n;--tree[1];
	while(l!=r)
	{
		int mid=(l+r)>>1;
		if(pos<=mid) r=mid,k<<=1;
		else l=mid+1,k=k<<1|1;
		--tree[k];
	}
}
int query(int rk)
{
	int k=1,l=1,r=n;
	while(l!=r)
	{
		int mid=(l+r)>>1;
		if(rk<=tree[k<<1]) r=mid,k<<=1;
		else l=mid+1,rk-=tree[k<<1],k=k<<1|1;
	}
	return l;
}
int main()
{
	cin>>n;
	build(1,1,n);
	F(i,1,n)
	{
		int bi=rd();
		if(bi>n-i) {puts("0");return 0;}
		if(bi==-1) ans=(ans*(n-i+1))%p,a[i]=query(1);
		else a[i]=query(bi+1);
		del(a[i]);
	}
	printf("%lld\n",ans);
	F(i,1,n) printf("%d ",a[i]);puts("");
	return 0;
}
```



---

## 作者：stansxt (赞：1)

# 思路
- 这题其实不算太难。就是一个逆康托展开，再稍微加了点东西。
- 我们从前往后遍历这个$B$数组，发现$a_i$其实就是 __现有的所有数当中第$b_i+1$小的数__。
- 为啥呢？因为$b_i$表示$i$号元素之后有多少元素是要小于$a_i$的。
- 容易发现，当遍历到$i$号元素时，1~$n$中还剩下的数一定是$n-i+1$个（已经选了$i-$1个了）。所以$a_i$最多是第$n-i+1$小的。
- 因此，当且仅当$b_i>n-i$时，不存在排列$A$，也即是要输出$0$。
- 同时第一问的答案也出来了：$b_i$可以取$0$~$n-i$中任意一个值，所以答案就是$\Pi_{i=1}^{n}(b_i == -1?n-i+1:0)$。
- 对于第二问，我们知道$b_i$一定时$a_i$就定下来了，而为了使字典序最小，我们从左往右遍历时应该贪心的让每一个$b_i==-1$的$a_i$都取最小。那么也就是说，$b_i$应该取$0$。
- 之后就是逆康托的板子了，双倍经验戳[这里](https://www.luogu.com.cn/problem/UVA11525)。
- 稍微讲一下权值线段树的做法（毕竟题目标签上也是有线段树的嘛），相当于要用线段树找出当前区间第$K$大并支持删除操作（已经被用过的数就不能再用了）。
- 开一颗线段树，叶子节点下标表示$1$~$n$中的一个数，线段树节点存储当前线段（区间）总共还剩多少个能用的数。
- 建树的时候每个数都能用，叶子节点全部赋值$1$，非叶子节点就左右子树求和。
- 每次查询的同时进行删除，当前区间能用的数减一，然后看看左子树是否有$K$个能用的数，有就递归查找左子树，否则右子树（注意右子树中查找的是 __第$K-$左子树剩余能用的数的个数__ 个数）。若到达叶子节点就返回该节点的 __下标__ 即可。
- 然后大概就完了，话不多说，直接上代码~
---
# 代码
```
//P6035 Ryoku 的逆序对
//submit 3
//By sxt on 2020.8.23 
#include<bits/stdc++.h>
#define rg register int
#define il inline
#define in read()
#define _num(x) (x >= '0' && x <= '9')
#define Mem(x) memset(x, 0, sizeof(x)) 
#define mid (l+r>>1)
#define el else if
#define lowbit(x) (x&(-x))
#define upd update(rt)
#define psd pushdown(rt)
using namespace std;
const int N = 1e6+7;
const int P = 1e9+7;
il int read(){
	int x=0,f=1;
	char ch=getchar();
	while(!_num(ch)){
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(_num(ch)){
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x*f;
}
char f[10];
int pcnt;
il void pint(int x){
	pcnt = 0;
	if(x == 0) putchar('0');
	while(x){
		f[++pcnt] = x % 10 + '0';
		x /= 10;
	}
	while(pcnt) putchar(f[pcnt--]);
	putchar('\n');
}
int n, a[N], ans, ls;
int tr[N<<2];
il void update(int rt){return (void)(tr[rt] = tr[rt<<1] + tr[rt<<1|1]);}
void build(int l, int r, int rt){
	if(l == r){
		tr[rt] = 1;
		return ;
	}
	build(l, mid, rt<<1), build(mid+1, r, rt<<1|1);
	return upd;
}
int query(int l, int r, int num, int rt){
	-- tr[rt];
	if(l == r)return l;
	if(tr[rt<<1] >= num) return query(l, mid, num, rt<<1);
	else return query(mid + 1, r, num - tr[rt<<1], rt<<1|1);
}
signed main()
{
//	freopen("1.txt", "r", stdin);
	n = in;
	ans = 1;
	build(1, n, 1);
	for(rg i = 1; i <= n; ++ i){
		a[i] = in;
		if(a[i] > n-i){
			printf("0\n");
			return 0;
		}
		if(a[i] == -1) ans = 1ll * ans * (n-i+1) % P, a[i] = 0;
		a[i] = query(1, n, a[i]+1, 1);
	}
	printf("%d\n", ans);
	for(rg i = 1; i <= n; ++ i)
		if(i != n)printf("%d ", a[i]);
		else printf("%d\n", a[i]);
	return 0;
}
```

---

