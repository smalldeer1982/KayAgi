# Skyscrapers (hard version)

## 题目描述

这题是 [CF1313C1](https://www.luogu.com.cn/problem/CF1313C1) 的较难版本。这个版本中 $1 \leq n \leq 500000$。

Berland要起摩天大厦了。所有的摩天大厦都在高速公路附近建。发展商买了 $n$ 块地准备建 $n$ 栋摩天大厦，一块地一栋。

当规划一间摩天大厦的时候，建筑师要考虑一些条件。

第一，因为每栋摩天大厦有不同的用途，所以每栋摩天大厦都有自己的层数限制，也就是说，这栋摩天大厦的高度不能超过给定的值 $m_i$。

第二，根据城市的建设规则，一栋摩天大厦不能同时在左右有比它高的摩天大厦。

如果规范地表示，让我们把地编上一个编号从 $1$ 到 $n$。那么如果在第 $i$ 块地的摩天大厦有 $a_i$ 层，那么我们需要保证 $1 \le a_i \le m_i$。另外，这里不可以有整数 $j$ 和 $k$ 满足 $j < i < k$ 并且 $a_j > a_i < a_k$。第 $j, k$ 块地并不需要与第 $i$ 块地相邻。

发展商想要使得每块地上摩天大厦的楼层数之和最大。也请帮他找出在**任意一个**最优状况中每个摩天大厦的高度。也就是，要让建筑师考虑的条件都符合，而且要使得每块地上摩天大厦的楼层数之和最大。

## 样例 #1

### 输入

```
5
1 2 3 2 1```

### 输出

```
1 2 3 2 1```

## 样例 #2

### 输入

```
3
10 6 8```

### 输出

```
10 6 6```

# 题解

## 作者：Fairicle (赞：11)

有C1和C2。

唯一的差别是 $n$ 的取值。

观察性质可以发现要满足条件必定有一个最高点，使得从左边到最高点高度单调不递减，从右边到最高点高度单调不递减。

C1的做法可以是枚举最高点，计算最优答案。

做法是 $O(n^2)$ 的。

考虑优化找最高点这一个过程。

用数组 $l_i,r_i$ 表示以 $i$ 为最高点时，向左和向右的高度和。

那么求出对于每一个 $l_i,r_i$ 总高度就是 $(l_i+r_i-a_i)$，求 $max (l_i+r_i-a_i)$ 就可以计算答案了。

而求出 $l_i,r_i$ 过程用单调栈实现可以做到 $O(n)$。

循环一次 $1->n$ ， 比 $a_i$ 小的最右的点记做 $j$，那么 $l_i$ $=$ $l_j$ $+$ $a_i*(i-j)$。

同理可倒序求 $r_i$。

部分代码：
```cpp
	for(ri i=1;i<=n;++i)
	{
		while(top&&a[s[top]]>a[i]) top--;
		int now=s[top];
		l[i]=l[now]+a[i]*(i-now);
		s[++top]=i;
	}
	while(top) top--;
	s[++top]=n+1;
	for(ri i=n;i>=1;--i)
	{
		while(top&&a[s[top]]>a[i]) top--;
		int now=s[top];
		r[i]=r[now]+a[i]*(now-i);
		s[++top]=i;
	}
```
求出了峰值所在，就可以愉快地求出答案数组了。

别忘了开 long long！

code：
```cpp
#include“bits/stdc++.h”
using namespace std；
#define ll long long
#define ul unsigned long long
#define ui unsigned int
define ri register int
inline ll read(){
	ll x=0,flag=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') flag=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+(ch^48);ch=getchar();}
	return x*flag;
}
ll a[500010],l[500010],r[500010],s[500010],top;
int main()
{
	int n=read();
	for(ri i=1;i<=n;++i)
	a[i]=read()；
	for(ri i=1；i<=n;++i)
	{
		while(top&&a[s[top]]>a[i]) top--;
		int now=s[top];
		l[i]=l[now]+a[i]*(i-now);
		s[++top]=i;
	}
	while(top) top--;
	s[++top]=n+1；
	for(ri i=n;i>=1;--i)
	{
		while(top&&a[s[top]]>a[i]) top--;
		int now=s[top];
		r[i]=r[now]+a[i]*(now-i);
		s[++top]=i;
	}
	ll maxn=0,pos=0;
	for(ri i=1;i<=n;++i)
	{
		if(l[i]+r[i]-a[i]>maxn)
		{
			pos=i;
			maxn=l[i]+r[i]-a[i];
		}
	}
	int pre=a[pos];
	for(ri i=pos;i;--i)
	{
		if(a[i]>pre) a[i]=pre;
		pre=a[i];
	}
	pre=a[pos];
	for(ri i=pos;i<=n;++i)
	{
		if(a[i]>pre) a[i]=pre;
		pre=a[i];
	}
	for(ri i=1;i<=n;++i)
	printf("%lld ",a[i]);
    return0;
}
```


---

## 作者：Limit (赞：3)

# 题目大意

给出一个长度为 $N$ 的序列 $a$ 需要构造出一个长度为 $N$ 的序列 $h$ 使得 $\forall i \in \{1,2,\ldots ,N\} h_i \leq a_i$ 且 $\forall i \in \{2,3,\ldots ,N-1\}$,$\nexists  \forall j \in \{1,2,\ldots ,i-1\},k \in \{i+1,i+2 \ldots N\},h_j > h_i < h_k$,求出并输出 $\sum_{i=1}^{N}h_i$ 达到最大值时的 $h$ 序列.

再简化一下题意,就是需要找出一个序列 $h$,$h_i\leq a_i$,且以 $h$ 中的某一个元素看来,前面和后面的元素都是单调的.

本题在数据范围上分为两个部分,所以就写一下两种不同的做法.

# Part 1

## 分析

$N$ 的范围不大,只有 $1000$ 于是很容易想到时间复杂度应该是 $O(N^2)$ 的,可以想到先枚举最高的位置的点,在向两边计算,可以很容易想到最高位置的 $h_i=a_i$ 而且当最高位置确定以后,为了使得和最大,所以整一个序列也是确定的,那么就可以想出最开始的 $O(N^2)$ 的做法了

## 代码

```cpp
#include<bits/stdc++.h>
#define REP(i,first,last) for(int i=first;i<=last;++i)
#define DOW(i,first,last) for(int i=first;i>=last;--i)
using namespace std;
int N,h[114514];
int top;
long long ans[114514];
int main()
{
	scanf("%d",&N);
	REP(i,1,N)
	{
		scanf("%d",&h[i]);
	}
	int now;
	long long answer=0;
	long long sum;
	REP(i,1,N)//枚举最高的位置
	{
		now=h[i];//记录当前的位置
		sum=h[i];
		DOW(j,i-1,1)//向前扫
		{
			sum+=min(h[j],now);
			now=min(h[j],now);//这里的now因为要保证单调不下降,所以需要一直取min
		}
		now=h[i];//向后扫同理
		REP(j,i+1,N)
		{
			sum+=min(h[j],now);
			now=min(h[j],now);
		}
		if(sum>answer)//记录下最大值,以及最大值时时哪一个位置达到最大值了
		{
			answer=sum;
			top=i;
		}
	}
	//最后只需要将达到最大值时的序列输出就好了
	ans[top]=h[top];
	now=h[top];
	DOW(i,top-1,1)
	{
		ans[i]=min(h[i],now);
		now=min(h[i],now);
	}
	now=h[top];
	REP(i,top+1,N)
	{
		ans[i]=min(h[i],now);
		now=min(h[i],now);
	}
	REP(i,1,N)
	{
		printf("%d ",ans[i]);
	}
	return 0;
}
```

# Part 2

## 分析

$N$ 的范围变大了很多达到了 $500000$ 为了防止题解清一色的都是单调栈,这里是一种不是很常见的做法.

可以发现在第一种方法中如果 $j \leq i,h_j \leq h_i$ 时 $1$ 到 $j$ 的最大值肯定是被计算过的,于是就可以想到用一个数组 $L$ 维护从 $1$ 开始带第 $i$ 个位置时最高处为 $i$ 切 $h_1$ 到 $h_i$ 为单调不下降时 $h_1$ 到 $h_i$ 和的最大值,计算这个数组需要分两种情况.

1. 第一种情况时 $a_{i-1} \leq a_i$,这样 $L_i=L_{i-1}+a_i$.
2. 第二种情况就比较特殊了,没法直接从 $L_{i-1}$ 计算出来,需要找到上一个小于等于 $a_i$ 的位置 $j$,那么 $L_i=(j-i)*a_i+L_j$,即在这之间的大于 $a_i$ 的位置的高度都是 $a_i$ 这样就可以保证是单调不下降.

于是就要想办法找到上一个小于 $a_i$ 的位置,显然不可以用 $O(N)$ 的做法,那么就可以用一颗线段树维护最小值,在线段树上二分找到上一个位置.

用同样的方法计算出一个数组 $R$(即从 $h_i$ 开始到 $h_N$ 中单调不上升的和的最大值)与 $L$ 同理,这样以第 $i$ 个位置为最高值时总和就变成了 $L_i+R_i-a_i$ 取出最大值以后只要像方法一一样输出就好了.

## 代码

```cpp
#include<bits/stdc++.h>
#define REP(i,first,last) for(int i=first;i<=last;++i)
#define DOW(i,first,last) for(int i=first;i>=last;--i)
using namespace std;
const int MAXN=6e5+7;
int N,M;
int arr[MAXN];
long long L[MAXN],R[MAXN];
int ans[MAXN];
//线段树部分,不多讲
struct SegmentTree
{
	int min;
}sgt[MAXN*4];
#define LSON (now<<1)
#define RSON (now<<1|1)
#define MIDDLE ((left+right)>>1)
#define LEFT LSON,left,MIDDLE
#define RIGHT RSON,MIDDLE+1,right
void PushUp(int now)
{
	sgt[now].min=min(sgt[LSON].min,sgt[RSON].min);
}
void Build(int now=1,int left=1,int right=N)
{
	if(left==right)
	{
		sgt[now].min=arr[left];
		return;
	}
	Build(LEFT);
	Build(RIGHT);
	PushUp(now);
}
int QueryL(int l,int r,int num,int now=1,int left=1,int right=N)//查询下一个小于num的值的位置
{
	if(r<left||right<l)return -1;
	if(sgt[now].min>num)
	{
		return -1;
	}
	if(left==right)
	{
		return left;
	}
	int result=QueryL(l,r,num,LEFT);//因为是下一个,所以优先查询左边
	if(result!=-1)
	{
		return result;
	}
	return QueryL(l,r,num,RIGHT);
}
int QueryR(int l,int r,int num,int now=1,int left=1,int right=N)//查询上一个小于num的值的位置
{
	if(r<left||right<l)return -1;
	if(sgt[now].min>num)
	{
		return -1;
	}
	if(left==right)
	{
		return left;
	}
	int result=QueryR(l,r,num,RIGHT);
	if(result!=-1)
	{
		return result;
	}
	return QueryR(l,r,num,LEFT);
}
#undef LSON
#undef RSON
#undef MIDDLE
#undef LEFT
#undef RIGHT
int main()
{
	scanf("%d",&N);
	REP(i,1,N)
	{
		scanf("%d",&arr[i]);
	}
	Build();
	REP(i,1,N)
	{
		if(arr[i]>=arr[i-1])//计算L时的第一种情况
		{
			L[i]=L[i-1]+1ll*arr[i];
		}
		else
		{
			int top=QueryR(1,i-1,arr[i]);//找到上一个小于的位置
			if(top==-1)L[i]=1ll*i*arr[i];//不存在就直接计算
			else
			L[i]=1ll*(i-top)*arr[i]+L[top];//存在按第二种情况计算
		}
	}
	DOW(i,N,1)//计算R同理
	{
		if(arr[i]>=arr[i+1])
		{
			R[i]=R[i+1]+1ll*arr[i];
		}
		else
		{
			int top=QueryL(i+1,N,arr[i]);
			if(top==-1)R[i]=1ll*(N-i+1)*arr[i];
			else
			R[i]=1ll*(top-i)*arr[i]+R[top];
		}
	}
	int top=1;
	long long answer=0;
	long long sum;
	REP(i,1,N)
	{
		sum=L[i]+R[i]-arr[i];
		if(sum>answer)//找到最大位置
		{
			answer=sum;
			top=i;
		}
	}
	//同样方法输出
	ans[top]=arr[top];
	int now=arr[top];
	DOW(i,top-1,1)
	{
		ans[i]=min(arr[i],now);
		now=min(arr[i],now);
	}
	now=arr[top];
	REP(i,top+1,N)
	{
		ans[i]=min(arr[i],now);
		now=min(arr[i],now);
	}
	REP(i,1,N)
	{
		printf("%d ",ans[i]);
	}
	return 0;
}

```

---

## 作者：gyh20 (赞：2)

首先我们发现，最后的答案一定是一个不降序列加上一个不升序列。

令 $dp_i$ 表示从 $1\sim i$ 的不降序列值和的最大值， $dp1_i$ 表示从 $i\sim n$ 的不升序列值和的最大值。

得出 $dp_i=dp_k+(i-k)\times a_i$，其中 $k$ 为 $i$ 之前第一个 $a_k<a_i$ 的值。

同理可以得到 $dp1_i$ 的值。

和 C1 不同，此题达到了 $n \leq 500000$ ，上述算法的瓶颈在于找第一个 $a_k<a_i$ 的值，而这个其实可以用单调栈来维护。

```cpp
#include<cstdio>
#include<algorithm>
#include<map>
#include<set>
#include<iostream>
#define re register
#define int long long
using namespace std;
inline int read(){
	re int t=0;
	re char v=getchar();
	while(v<'0')v=getchar();
	while(v>='0'){
		t=(t<<3)+(t<<1)+v-48;
		v=getchar();
	}
	return t;
}
inline int max(re int x,re int y){
	return x>y?x:y;
}
inline int min(re int x,re int y){
	return x<y?x:y;
}
int t,a[500002],dp[500002],dp1[500002],n,lst[500005],p,mx,ans[500005],s[500005],tp;
signed main(){
n=read();
for(re int i=1;i<=n;++i)a[i]=read();
for(re int i=1;i<=n;++i){
	lst[i]=0;
	while(a[s[tp]]>a[i]&&tp)--tp;
	lst[i]=s[tp];
	s[++tp]=i;
}
for(re int i=1;i<=n;++i){
	dp[i]=dp[lst[i]]+(i-lst[i])*a[i];
}
reverse(a+1,a+n+1);
tp=0;
for(re int i=1;i<=n;++i){
	lst[i]=0;
	while(a[s[tp]]>a[i]&&tp)--tp;
	lst[i]=s[tp];
	s[++tp]=i;
}
for(re int i=1;i<=n;++i){
	dp1[i]=dp1[lst[i]]+(i-lst[i])*a[i];
}
reverse(dp1+1,dp1+n+1);
for(re int i=1;i<=n;++i){
	if(dp[i]+dp1[i+1]>mx){
		mx=dp[i]+dp1[i+1];
		p=i;
	}
}
reverse(a+1,a+n+1);
mx=a[p];
for(re int i=p;i>=1;--i){	
mx=min(mx,a[i]);
	ans[i]=mx;

}
mx=a[p+1];
for(re int i=p+1;i<=n;++i){	
mx=min(mx,a[i]);
	ans[i]=mx;

}
for(re int i=1;i<=n;++i)printf("%lld ",ans[i]);
}
```


---

## 作者：极寒神冰 (赞：1)

可以发现答案一定由一个不下降子序列和一个不上升子序列构成。那我们可以考虑将原数列分成两个数列，通过枚举峰值位置将左右两边的贡献加起来即可。

左边贡献$L_i$即从上一个$a_{last}<=a_i$推过来

$$L_i=L_{last}+a_i*(i-last)$$

右边贡献同理

可以发现朴素枚举$last$的复杂度$O(n^2)$。

但是每次都要枚举$last$太麻烦了，可以使用单调栈或者笛卡尔树进行优化,复杂度即为$O(n)$

```
#include<bits/stdc++.h>
#define ld long double
#define tset puts("qwq");
#define test puts("QAQ");
#define pb push_back
#define pii pair<int,int> 
#define mkp make_pair
#define Max(a,b) ((a>b)?a:b)
#define us unsigned 
#define int long long
using namespace std;
const int inf=1e18;
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21], *p1 = buf, *p2 = buf;
int read()
{
    int x=0,f=1;
    char c=getchar();
    while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
    while(isdigit(c)){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
    return x*f;
}
const int N=5e5+10;
int n,a[N];
int L[N],R[N];
int stk[N],top;
signed main()
{
	n=read();
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=1;i<=n;i++)
	{
		while(top&&a[stk[top]]>a[i]) top--;
		L[i]=L[stk[top]]+a[i]*(i-stk[top]);
		stk[++top]=i;
	}
	stk[top=1]=n+1;
	for(int i=n;i>=1;i--)
	{
		while(top&&a[stk[top]]>a[i]) top--;
		R[i]=R[stk[top]]+a[i]*(stk[top]-i);
		stk[++top]=i;
	}
	int res=-1,pos;
	for(int i=1;i<=n;i++) if(L[i]+R[i]-a[i]>res) pos=i,res=L[i]+R[i]-a[i];
	int tmp=a[pos];
	for(int i=pos;i>=1;i--) if(a[i]>tmp) a[i]=tmp;else tmp=a[i];
	tmp=a[pos];
	for(int i=pos;i<=n;i++) if(a[i]>tmp) a[i]=tmp;else tmp=a[i];
	for(int i=1;i<=n;i++) printf("%lld ",a[i]);
}
```



---

## 作者：眠ㅤㅤㅤ (赞：1)

最直观粗暴，也容易想到的应该是分治吧。

找到序列最小值的位置，则在这个最小值分为两侧，必有一侧的所有值要变为最小值。

对于一段序列 $solve(L,R)$，最小值 $min$ 的位置 $p$， 分治 $solve(L,p-1)$, $solve(p+1,R)$，有

左边覆盖为最小值的总价值为 $solve(p+1,R)+(p-L+1)*min$

右边覆盖为最小值的总价值为 $solve(L,p-1)+(R-p+1)*min$

比较这两个值，小的那一侧覆盖为最小值即可，维护最小值可以用线段树。复杂度$O(nlogn)$。

  
```cpp
constexpr auto Inf = 0X3F3F3F3F;
#ifndef LOCAL
	#include <bits/stdc++.h>
#endif
typedef long long LL;
using namespace std;

namespace IO {
	inline LL read() {
		LL o = 0, f = 1; char c = getchar();
		while (c < '0' || c > '9') { if (c == '-') f = -1; c = getchar(); }
		while (c > '/' && c < ':') { o = o * 10 + c - '0'; c = getchar(); }
		return o * f;
	}
	inline char recd() {
		char o; while ((o = getchar()) < '0' || o > '9'); return o;
	}
	inline double reod() {
		double o = read(), f = 1; char c;
		while ((c = getchar()) > '/' && c < ':') o += (c - '0') / (f *= 10);
		return o;
	}
}
using namespace IO;

const int SIZE = 5E5 + 7, Mod = 1E9 + 7;

struct Node {
	int L, R, w, Ind;
} Node[SIZE << 2]; int w[SIZE], ans[SIZE];

void BUILD(int now, int L, int R) {
	Node[now].L = L, Node[now].R = R;
	if (L == R) { Node[now].w = w[L], Node[now].Ind = L; return; }
	int M = (L + R) >> 1;
	BUILD(now << 1, L, M), BUILD(now << 1 | 1, M + 1, R);
	if (Node[now << 1].w < Node[now << 1 | 1].w) 
		Node[now].w = Node[now << 1].w, Node[now].Ind = Node[now << 1].Ind;
	else 
		Node[now].w = Node[now << 1 | 1].w, Node[now].Ind = Node[now << 1 | 1].Ind;
}

pair<int, int> Ask(int now, int L, int R) {
	if (Node[now].L == L && Node[now].R == R)
		return make_pair(Node[now].w, Node[now].Ind);
	int M = (Node[now].L + Node[now].R) >> 1;
	if (L > M) return Ask(now << 1 | 1, L, R);
	if (R <= M) return Ask(now << 1, L, R);
	pair<int, int> Lm = Ask(now << 1, L, M), Rm = Ask(now << 1 | 1, M + 1, R);
	return Lm.first < Rm.first ? Lm : Rm;
}

LL F(int L, int R) {
	if (L >= R) return L == R ? w[L] : 0;
	
	pair<int, int> M = Ask(1, L, R);
	LL Lsub = F(L, M.second - 1), Rsub = F(M.second + 1, R);
	LL Lw = Lsub + LL(R - M.second + 1) * M.first;
	LL Rw = Rsub + LL(M.second - L + 1) * M.first;

	if (Lw < Rw) 
		for (int pos = L; pos < M.second; pos++) ans[pos] = M.first;
	else
		for (int pos = M.second + 1; pos <= R; pos++) ans[pos] = M.first;
	return Lw > Rw ? Lw : Rw;
}

int main() {
	int N = read(); 
	for (int pos = 1; pos <= N; pos++) ans[pos] = w[pos] = read(); BUILD(1, 1, N);
	F(1, N);
	for (int pos = 1; pos <= N; pos++) printf("%d ", ans[pos]); puts("");
}
```



---

## 作者：Thinking (赞：1)

居然没有单调栈？

首先显然答案是一个不下降序列+一个不上升序列，因此考虑一下不下降序列怎么搞：

对于每一个$a_i$，找到它前面最大的$j$使$a_j<a_i$（如果不存在则$j=0$），然后把$(j,i]$内的楼全部改成$a_i$高度。直接做$O(n^2)$，单调栈优化后$O(n)$。

code：

```cpp
#include<cstdio>
#define For(i,A,B) for(i=(A);i<=(B);++i)
typedef long long ll;
const int N=500050;
int a[N],st[N],sl;
ll res[N],now;
inline int len(int x,int y){return x<=y?y-x:x-y;}
inline void push(int p){
    for(;sl&&a[st[sl]]>=a[p];--sl)now-=(ll)a[st[sl]]*len(st[sl],st[sl-1]);
    now+=(ll)a[p]*len(p,st[sl]);
    st[++sl]=p;
}
int main(){
    int n,i,j=1,p;
    ll ans;
    scanf("%d",&n);p=n;
    For(i,1,n)scanf("%d",a+i);
    For(i,1,n){
        push(i);
        res[i]=now;
    }
    ans=now;
    st[sl=now=0]=n+1;
    for(i=n;i;--i){
        push(i);
        if(res[i-1]+now>ans){
            ans=res[i-1]+now;
            p=i-1;
        }
    }
    sl=0;
    For(i,1,p)push(i);
    For(i,1,sl)
        for(;j<=st[i];++j)printf("%d ",a[st[i]]);
    sl=0;
    for(i=n;i>p;--i)push(i);
    for(i=sl;i;--i)
        For(j,st[i],st[i-1]-1)printf("%d ",a[st[i]]);
    return 0;
}
```


---

## 作者：Register (赞：1)

- 前置知识：笛卡尔树

### 题意：

把直方图切割成一个单峰的，使面积最大

### 解析：

- $1\le n\le 1000$ ：枚举每一个点作为峰点，然后直接模拟

- $1\le n\le 500000$ ：

看到直方图上搞事，显然可以弄成在笛卡尔树上做树形 DP

1. 建出笛卡尔树

2. 做树形 DP ，对于每个节点，记录这个子直方图的答案，比较左儿子和右儿子答案大小，选取打倒，并把另一边的子直方图高度全部赋值为与自己高度相同的

不过直接 DFS 赋值可能会被卡，可以打个标记最后一起搞~~我才不会告诉你我就是直接 DFS 赋值没被卡~~

代码：

```cpp
#include <cstdio>
#define int long long
int n,top,s[500001],sz[500001],a[500001],f[500001],c[500001][2];
inline int read(){
	char ch=getchar();int res=0,w=1;
	while(ch<'0'||ch>'9') {if(ch=='-') w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') {res=res*10+ch-'0';ch=getchar();}
	return res*w;
}
void gg(int x,int v){
	if(!x) return;
	a[x]=v;gg(c[x][0],v);gg(c[x][1],v);
}
void dfs(int x,int t){
	if(!x) return;
	dfs(c[x][0],a[x]);dfs(c[x][1],a[x]);sz[x]=sz[c[x][0]]+sz[c[x][1]]+1;f[x]=sz[x]*(a[x]-t);
	if(f[c[x][0]]>f[c[x][1]]) {gg(c[x][1],a[x]);f[x]+=f[c[x][0]];}
	else {gg(c[x][0],a[x]);f[x]+=f[c[x][1]];}
}
signed main(){
	n=read();
	for(register int i=1,j;i<=n;i++)
	{
		a[i]=read();j=top;
		while(j&&a[s[j]]>a[i]) j--;
		if(j) c[s[j]][1]=i;
		if(j<top) c[i][0]=s[j+1];
		top=j;s[++top]=i;
	}
	dfs(s[1],0);
	for(register int i=1;i<=n;i++) printf("%d ",a[i]);
	return 0;
}
```

---

## 作者：123456zmy (赞：1)

题意：  
给你一个数列 $m$，你要把其中的一部分数减少一些，使得存在至少一个 $k$ 使得 $m_1\le m_2\le…\le m_k\ge m_{k+1}\ge…\ge m_n$。输出操作后的数列。（$1\le n\le5\times10^5$）。
___
考虑优化 $O(n^2)$ 的暴力。暴力主要是要每次一个一个算贡献，因为数列的单调性，可以想到用单调栈来优化暴力，那样每次统计答案的时间复杂度可以做到均摊 $O(1)$ 然后找到答案最大的那个分界点，再跑一遍暴力求出答案即可。

代码：（O(n)）
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m[500001],la[500001],ra[500001],l[500001],r[500001],ln[500001],rn[500001],l1,r1,ansl[500001],ansr[500001],ans,ansi,ans_[500001];
signed main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)scanf("%lld",&m[i]);
	for(int i=1;i<=n;i++)
	{
		while(m[i]<l[l1])--l1;
		l[++l1]=m[i];
		ln[l1]=i;
		ansl[i]=la[l1]=la[l1-1]+m[i]*(i-ln[l1-1]);
	}
	rn[0]=n+1;
	for(int i=n;i>=1;i--)
	{
		while(m[i]<r[r1])--r1;
		r[++r1]=m[i];
		rn[r1]=i;
		ansr[i]=ra[r1]=ra[r1-1]+m[i]*(rn[r1-1]-i);
	}
	for(int i=1;i<=n;i++)if(ansl[i]+ansr[i]-m[i]>ans)
	{
		ans=ansl[i]+ansr[i]-m[i];
		ansi=i;
	}
	int k=m[ansi];
	for(int j=ansi-1;j>0;j--)ans_[j]=(k=min(m[j],k));
	k=m[ansi];
	for(int j=ansi+1;j<=n;j++)ans_[j]=(k=min(m[j],k));
	ans_[ansi]=m[ansi];
	for(int i=1;i<=n;i++)printf("%lld ",ans_[i]);
	return 0;
}
```

---

