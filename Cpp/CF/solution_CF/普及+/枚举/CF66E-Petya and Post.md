# Petya and Post

## 题目描述

### 题意翻译

有 $n$ 个邮局，在每个邮局都有一个加油站。（邮局编号从 $1$ 开始）

对于第 $i$ 个邮局，$a_i$ 表示位于这个邮局加油站最多能加多少油，$b_i$ 表示它到第 $i+1$ 个邮局会耗费多少油。特殊的，对于第 $n$ 个邮局，$b_n$ 表示它到第 $1$ 个邮局会耗费多少油。

现在可以任意选择一个邮局出发，开始的油量为 $0$。可以选择顺时针或者逆时针走动，一旦决定方向就不可以回头。 要求路途上任一时刻油量$\ge 0$。

## 样例 #1

### 输入

```
4
1 7 2 3
8 1 1 3
```

### 输出

```
2
2 4
```

## 样例 #2

### 输入

```
8
1 2 1 2 1 2 1 2
2 1 2 1 2 1 2 1
```

### 输出

```
8
1 2 3 4 5 6 7 8
```

# 题解

## 作者：Fireworks_Rise (赞：4)

# 分析题意

本题意在求在一个长度为 $n$ 的环中，从任意点出发，按照逆时针（或顺时针）的方向走，最终可以回到出发点的点的数目及其编号。

# 思路

遇到有环的题型，最好的解决方法就是开两倍的数列（即在原数列的末尾插入整个数列）。

讨论顺时针的方案：

观察题目，可知，每个站点的耗油量为 $p_i-d_i$ ，而是若能回到出发点，所剩的油量必然 $\ge 0$，所以可先预处理前缀和从 $1$ 出发到当前点的总耗油量。

由于在行驶的过程中，任一时刻油量都必须 $\ge 0$，进而题目转化为维护前缀和的最小值，此处方法很多，如线段树、 st 表都可以维护。

本蒟蒻则是采用了单调队列维护前缀和最小值。

逆时针的算法同上，最后把符合条件的点离线标记，最后处理编号即可。

# Code

贴上蒟蒻代码...


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e6+10;
int n,p[N],d[N],s[N];
int q[N],head,tail=-1;
bool flag[N];
signed main() {
    scanf("%lld",&n);
    for(int i=1;i<=n;i++)
        scanf("%lld",&p[i]);
    for(int i=1;i<=n;i++) {
    	scanf("%lld",&d[i]);
        s[i]=s[i+n]=p[i]-d[i];
    }
    for(int i=1;i<=n*2;i++) s[i]+=s[i-1];
    q[++tail]=n*2+1;
    for(int i=n*2;i>=0;i--) {
        if(q[head]>i+n) head++;
        if(i<n&&s[i]<=s[q[head]])
			flag[i+1]=1;
        while(head<=tail&&s[q[tail]]>=s[i]) tail--;
        q[++tail]=i;
    }
    d[0]=d[n];
    for(int i=1;i<=n;i++) s[i]=s[i+n]=p[i]-d[i-1];
    for(int i=1;i<=n*2;i++) s[i]+=s[i-1];
    head=0,tail=-1;
    q[++tail]=0;
    for(int i=1;i<=n*2;i++) {
        if(q[head]<i-n) head++;
        if(i>n&&s[i]>=s[q[head]])
    		flag[i-n]=1;
        while(head<=tail&&s[q[tail]]<=s[i]) tail--;
        q[++tail]=i;
    }
    int res=0;
    for(int i=1;i<=n;i++)
        if(flag[i]) res++;
    printf("%lld\n",res);
    for(int i=1;i<=n;i++) {
    	if(flag[i])
    		printf("%lld ",i);
	}
	printf("\n");
    return 0;
}
```


---

## 作者：xkcdjerry (赞：2)

挺有意思一个题，反复优化朴素思路得到最终解。

提供一个不用单调队列，只用前后缀和的 $O(n)$ 做法。

首先显然顺时针走和逆时针走是一样的，解决了一个也就解决了另一个，所以后面以顺时针为例子。~~逆时针存在的唯一意义就是让代码长度翻倍~~

首先考虑最暴力的做法：对于每个点分别判定是否可行。  
判定方法是整个扫一圈，维护每段结束时的油量，如果每段结束时油量都 $\geqslant 0$ 那么就可行。  
每个点要花 $O(n)$ 的时间，总复杂度 $O(n^2)$。

---

考虑一下挖掘性质优化：

列一下对点 $1$，从每个点出发后即将达到下个点时的油量：  
$$a_1-b_1,a_2-b_2+a_1-b_1,\dots,a_n-b_n+a_{n-1}-b_{n-1}+\dots+a_1-b_1$$  
不妨令 $c_i=a_i-b_i$，则为：  
$$c_1,c_1+c_2,c_1+c_2+c_3,\dots,c_1+c_2+\dots+c_n$$  
即从点 $i$ 出发即将到达点 $i+1$ 时的油量就是 $\sum_{j=1}^i c_i$。
 
那么对于点 $2$ 呢：（注意下面的数组依然是从 $1$ 开始）  
$$\sum_{i=1}^n c_i, c_2, c_2+c_3, \dots , c_2+c_3+\dots+c_n$$

注意到什么了吗？这里除了第一个变成了 $\sum_{i=1}^n c_i$ 之外，别的都增加了 $-c_1$。  
原因也很好理解：  除了 $1$ 到 $2$ 的路油量外，每个开头都少耗了 $c_1$ 的油，而从 $1$ 到 $2$ 的油量变成了从 $2$ 到 $2$ 的油量，即转一整圈，花了 $\sum_{i=1}^n c_i$ 的油。

整理一下，我们需要做如下的操作：前缀加，后缀加，单点赋值，全局查最小值。  
显然可以线段树做，时间复杂度 $O(n \log n)$。

伪代码：
```c++
for(int i=1;i<=n;i++) c[i]=a[i]-b[i];
for(int i=1;i<=n;i++) f[i]=f[i-1]+c[i];
init(1,n,f);
for(int i=1;i<=n;i++)
{
    if(query_min()>=0) ans[i]=true;
    if(i!=1) add(1,i,-c[i]);
    if(i!=n) add(i,n,-c[i]);
    set(i,val[n]);
}
```

---

还能怎么优化呢？我们这次改为挖掘代码的性质。

我们发现既然在加法后给第 $i$ 位赋值了，那也就不用专门绕过它了。直接改为全局加，去除了麻烦的区间修改操作：

```c++
// ...clipped for brevity...
for(int i=1;i<=n;i++)
{
    if(query_min()>=0)
    add(-c[i]);
    set(i,val[n]);
}
```
到这里其实已经可以 $O(n)$ 做了：  
维护一个后缀最小值然后查询的时候给他加上全局加 tag。然后对于修出来的前缀维护一个最小值，每次全局加的时候给它也加，然后和新插入进来的值取 $\min$。（觉得文字不清楚的可以看[代码](https://codeforces.com/contest/66/submission/237527267)）

---

但是稍微再思考一下能得到一个更优雅的做法：

再次考虑，这个单点赋值性质非常的差：如果没有它我们就能够把全局加直接对整个数组打 tag 而不用分开维护。  
而如果我们知道此时第 $i$ 位的值，我们就能把单点赋值转化为单点加，这个就不影响全局加 tag 了。  
很巧，我们刚好知道：原来这里的值是 $\sum_{j=1}^i c_i$，而我们对于 $1 \sim i$ 之间的每个值 $j$ 都全局加了了一次 $-c_j$。换句话说，单点修改前位置 $i$ 的值恰好为 $0$。  
那么我们就可以把单点赋值转化为单点加 $\sum c_i$。

由于前缀每个点加的值都一样，那么只需要维护一个 $f$ 数组的前缀最小值 $g$ 和一个后缀最小值 $h$。可得以 $i$ 为起点的全局最小值就是：  
$$\min(g_{i-1}+\sum c_i,h_i)-\sum_{j=1}^i c_j$$

[提交记录](https://codeforces.com/contest/66/submission/237512425)

---

细节注意：  
由于 $b$ 数组代表的是从第 $i$ 个到第 $i+1$ 个的距离，所以计算逆时针的时候不能直接 `std::reverse`，会导致错位。  
要先把最后一个（原来的 $n$ 到 $1$）放到最前面然后再 `reverse`，这样仍然代表了数组中最后一个（即 $1$）到数组中第一个一个（即 $n$）的距离。  
而由于顺次距离的特性对齐任何一个就会全部对齐，所以显然其他的也不会错位。细节可见代码注释。

---

## 作者：JK_LOVER (赞：2)

## 题意
求问一个环中满足逆时针走或者顺时针走，可以到达起点的点的个数和编号。
## 分析
根据题意我们可以写出朴素的 $O(n^3)$ 的暴力。
$$
ans = \sum_i^n[\sum_j^{i+n}\sum_{k=i}^{j}(A[k]-B[k]) >0]
$$
可以运用前缀和可以优化为 $O(n^2)$ 。
$$
ans = \sum_i^n[\sum_j^{i+n} sum[j] - sum[i-1]>0] 
$$
发现算法的瓶颈在于求出一个最小值，那么我们运用线段树或者 $st$ 表维护。复杂度为 $O(n\log n)$ 。
$$
ans = \sum_i^n[sum_{min} - sum_{i-1} >0] 
$$
代码就简单了。其实好像可以用单调队列优化到 $O(n)$ ，其中有个破环成链的小技巧。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
    {
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}
const int N = 2e5+10;
int sum[N],st[N][23],n,ans;
int Query(int l,int r)
{
    int k=log2(r-l+1); 
    return min(st[l][k],st[r-(1<<k)+1][k]);
}
bool vis[N];
void work(int A[],int B[],int p)
{
	memset(sum,0,sizeof(sum));
	memset(st,0,sizeof(st));
	for(int i = 1;i <= n*2;i++)
	{
		if(i <= n)
		sum[i] = sum[i-1] + (A[i] - B[i]);
		else 
		sum[i] = sum[i-1] + (A[i-n] - B[i-n]);
		st[i][0] = sum[i];
	}
	for(int j=1;j<=21;j++)
    for(int i=1;i+(1<<j)-1<=2*n;i++)
        st[i][j]=min(st[i][j-1],st[i+(1<<(j-1))][j-1]);
    for(int i = 1;i <= n;i++)
    {
    	if(Query(i,i+n-1) - sum[i-1] < 0) continue;
    	if(!vis[i] && !p) 
    	{
    		vis[i] = 1;
    		ans++;
		}
		if(!vis[n-i+1] && p)
		{
			vis[n-i+1] = 1;
			ans++;
		}
	}
}
int A[N],B[N],C[N],D[N];
int main()
{
	n = read();
	for(int i = 1;i <= n;i++) A[i] = read();
	for(int i = 1;i <= n;i++) B[i] = read();
	work(A,B,0);
	for(int i = 1;i <= n/2;i++) 
	B[0] = B[n];
	for(int i = 1;i <= n;i++)
	C[i] = B[i-1],D[i] = A[i];
	for(int i = 1;i <= n;i++)
	B[i] = C[n-i+1];
	for(int i = 1;i <= n;i++)
	A[i] = D[n-i+1];
	work(A,B,1);
	cout<<ans<<endl;
	for(int i = 1;i <= n;i++)
	if(vis[i]) cout<<i<<" ";
}


```
[地址](https://www.luogu.com.cn/blog/xzc/solution-cf66e)


---

## 作者：_edge_ (赞：1)

好题！

我们先来考虑一下暴力搞这个东西。

首先枚举一下要判定的点，那个点顺时针逆时针模拟一遍。

为了下面优化方便一点，我们这里统一将它断环为链，就是把环复制一遍，从一个端点开始到另外一个相同的端点这样一个区间。

暴力模拟一下这个过程，大概就是搞一个 $sum$ 存一下每一个 $a_i-b_i$。

当然这里顺时针和逆时针要稍微注意一下细节。

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
const int INF=5e5+5; 
int n,a[INF],b[INF],ans[INF];
bool check1(int x) {
	int sum=0;
	for (int i=x;i<n+x;i++) {
		sum+=a[i]-b[i];
		if (sum<0) return false;
	}
	return true;
}
 
bool check2(int x) {
	int sum=0;
	for (int i=x+n;i>x;i--) {
		int p=i-1;if (p==0) p=n;
		sum+=a[i]-b[p];
		if (sum<0) return false;
	}
//	for (int i=n;i>x;i--) {
//		sum+=a[i]-b[i-1];
//		if (sum<0) return false;
//	}
	return true;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin>>n;
	for (int i=1;i<=n;i++) cin>>a[i];
	for (int i=1;i<=n;i++) cin>>b[i];
	
	for (int i=n+1;i<=n*2;i++) a[i]=a[i-n];
	for (int i=n+1;i<=n*2;i++) b[i]=b[i-n];
	
	for (int i=1;i<=n;i++) {
		
		int l=check1(i);
		
		int k=check2(i);
		
		if (l || k) ans[++ans[0]]=i;
	}
	cout<<ans[0]<<"\n";
	for (int i=1;i<=ans[0];i++)
		cout<<ans[i]<<" ";
	return 0;
}
```

时间复杂度是 $O(n^2)$。

我们发现这个东西好像不太好优化，因为它关于的是 $a$ 和 $b$ 两个序列。

为了方便，以下的描述都在顺时针下。

但是我们发现其实在 check 的时候只和 $a_i - b_i$ 有关，不妨把他们变成一个前缀和的样子。

然后你会发现它可以变成 $sum_{i \le j < i+n}-sum_{i-1} >0$ 的形式。

我们发现其实右边那个东西，在确定 $i$ 之后是一个定值。

然后我们又要找出不符合条件的，显然当前面那个取最小值的时候，如果符合条件，那么其他的都符合条件。

问题转化成维护 $sum_{i \le j < i+n}$ 的最小值。

这个东西用单调队列，线段树，各种各样的数据结构都可以维护。

然后这个问题就解决了，时间复杂度是 $O(n)$ 或者 $O(n \log n)$。

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
const int INF=5e5+5; 
int n,a[INF],b[INF],ans[INF],sum1[INF],q1[INF],l1,r1,sum2[INF];
int q2[INF],l2,r2;
bool check1(int x) {
	int sum=-sum1[x-1];
	// 1 ~ n
	// 2 ~ n+1
	
	while (l1<=r1 && q1[l1]<x) l1++;
	while (l1<=r1 && sum1[q1[r1]]>=sum1[n+x-1]) r1--;
	q1[++r1]=n+x-1;
	
//	for (int i=x;i<n+x;i++) {
//		int kk=sum+sum1[i];
//		if (kk<0) return false;
//	}
	
	if (sum+sum1[q1[l1]]<0) return false;
	
	// ... a[x]-b[x]
	// ... a[x]-b[x]+a[x+1]-b[x+1]
	// 
	return true;
}

bool check2(int x) {
	int sum=sum2[x+n];
	// 1~n
	// 2~n+1
	
	while (l2<=r2 && q2[l2]<x) l2++;
	while (l2<=r2 && sum2[q2[r2]]<=sum2[n+x-1]) r2--;
	q2[++r2]=n+x-1;
	
//	for (int i=x+n;i>=x+1;i--) {
//		int kk=sum-sum2[i-1];
//		if (kk<0) return false;
//	}
	int kk=sum-sum2[q2[l2]];
	if (kk<0) return false;
	return true;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin>>n;
	for (int i=1;i<=n;i++) cin>>a[i];
	for (int i=1;i<=n;i++) cin>>b[i];
	
	for (int i=n+1;i<=n*2;i++) a[i]=a[i-n];
	for (int i=n+1;i<=n*2;i++) b[i]=b[i-n];
	
	for (int i=1;i<=n*2;i++) sum1[i]=sum1[i-1]+a[i]-b[i];l1=1;
	for (int i=1;i<=n*2;i++) sum2[i]=sum2[i-1]+a[i]-b[i-1];l2=1;
	
	
	for (int i=1;i<n;i++) {
		while (l1<=r1 && sum1[q1[r1]]>=sum1[i]) r1--;
		q1[++r1]=i;
	}
	
	for (int i=1;i<n;i++) {
		while (l2<=r2 && sum2[q2[r2]]<=sum2[i]) r2--;
		q2[++r2]=i;
	}
	
	for (int i=1;i<=n;i++) {
		int l=check1(i);
		int k=check2(i);
		if (l || k) ans[++ans[0]]=i;
	}
	cout<<ans[0]<<"\n";
	for (int i=1;i<=ans[0];i++)
		cout<<ans[i]<<" ";
	return 0;
}
```


---

## 作者：_171829 (赞：0)

# 1st 题意
在一个环中可以逆时针走或者顺时针走求可以 **到达起点** 的点的 **个数** 以及 **编号**。

# 2st 分析

首先分析一下：

$D_1=a_1-b_1$

$D_2=(a_1+a_2)-(b_1+b_2)$

$D_3=(a_1+a_2+a_3)-(b_1+b_2+b_3)$

$\dots\dots$

$D_n=(a_1+a_2+…+a_n)-(b_1+b_2+…+b_n)$

$∴x=\min(D(i))$

如果 $x \ge 0$ 那么从这个点走就一定 OK。

现在如果要走下一个点，就不需要从头到尾再算上一遍了。

$D_2=a_2-b_2$

$D_3=(a_2+a_3)-(b_2+b_3)$

$\dots\dots$

$D_n=(a_2+…+a_n)-(b_2+…+b_n)$

$D_1=(a_1+a_2+…+a_n)-(a_1+b_2+…+b_n)$

和前一次相比就是当前的值减去上一点的差值，除了 $D_1$ 例外，但由题意知这个点一定为 $0$ 符合条件。

那么把 **前一次的最小值** 减去 **那个点的差值** 就是下一个点的最小值了。


# 3rd code

```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
const int mm=1e5+9;
const int oo=1e9;
int a[mm],b[mm];
bool vis[mm];
int main()
{
  int n;
  while(cin>>n)
  { memset(vis,0,sizeof(vis));
    for(int i=0;i<n;++i)cin>>a[i];
    for(int i=0;i<n;++i)cin>>b[i];
    int mi=oo,z=0,mmi=oo,zz=0;
    for(int i=0;i<n;++i)
    {z+=a[i]-b[i];zz+=a[n-i-1]-b[(n-i-2+n)%n];
     mi=min(mi,z);mmi=min(mmi,zz);
    }
    int num=0;
    for(int i=0;i<n;++i)
    {
      if(mi>=0&&!vis[i+1])vis[i+1]=1,++num;//正方向
      if(mmi>=0&&!vis[n-i])vis[n-i]=1,++num;//逆方向
      mi-=a[i]-b[i];
      mmi-=a[n-i-1]-b[(n-i-2+n)%n];
    }
    cout<<num<<"\n";
    for(int i=0;i<=n;++i)
      if(vis[i])
      cout<<i<<" ";
    cout << endl;
  }
}
```





---

## 作者：Tx_Lcy (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF66E)
## 思路
给出一种比较暴力的做法。

先考虑搞出正向的答案。

显然，若从 $1$ 开始，则到达每一个加油站的时的和为 $a_1-b_1,a_1-b_1+a_2-b_2,a_1-b_1+a_2-b_2+a_3-b_3,...$

若这些数中有一个 $<0$，那么这个位置就不符合。

我们发现直接处理是 $O(n^2)$ 的。

考虑用数据结构优化。

先列出从 $2,3$ 开始的和：

+ $2:$ $a_2-b_2,a_2-b_2+a_3-b_3,a_2-b_2+a_3-b_3+a_4-b_4,...$
+ $3:$ $a_3-b_3,a_3-b_3+a_4-b_4,a_3-b_3+a_4-b_4+a_5-b_5,...$

我们发现这些柿子大部分都是一样的，所以可以考虑线段树乱搞。

设 $d_i$ 表示每一个位置的和。

假设当前是从 $i$ 开始，那么我们该如何转到从 $i+1$ 开始呢？就直接给除 $i$ 以外的点 $\verb!update!$ 一个 $-(a_i-b_i)$，然后把 $i$ 改成 $d_n$ 即可。

这个请读者自行理解，比较简单。

倒向的直接 $\verb!reverse!$ 即可，注意要清空线段树的 $\verb!lazy!$ 标记，~~我就是因为这个调了一个小时~~。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int const N=1e5+10;
int d[N];
struct Segment_Tree{
    #define ls (x<<1)
    #define rs (x<<1|1)
    #define mid ((l+r)>>1)
    int c[N<<2],lazy[N<<2];
    inline void build(int x,int l,int r){
        if (l==r){c[x]=d[l];return;}
        build(ls,l,mid);build(rs,mid+1,r);
        c[x]=min(c[ls],c[rs]);
    }
    inline void pushdown(int x){
        c[ls]-=lazy[x];c[rs]-=lazy[x];
        lazy[ls]+=lazy[x];lazy[rs]+=lazy[x];
        lazy[x]=0;
    }
    inline void update(int x,int l,int r,int ll,int rr,int v){
        if (ll<=l && r<=rr){lazy[x]+=v;c[x]-=v;return;}
        pushdown(x);
        if (ll<=mid) update(ls,l,mid,ll,rr,v);
        if (mid<rr) update(rs,mid+1,r,ll,rr,v);
        c[x]=min(c[ls],c[rs]);
    }
}T;
int a[N],b[N],cc[N];
int main(){
    int n;
    //读入
    int num=0;vector<int>ans;
    for (int i=1;i<=n;++i) d[i]=d[i-1]+a[i]-b[i];
    num=d[n];
    T.build(1,1,n);
    for (int i=1;i<=n;++i){
        if (T.c[1]>=0) ans.push_back(i);
        if (i!=1) T.update(1,1,n,1,i-1,a[i]-b[i]);
        if (i!=n) T.update(1,1,n,i+1,n,a[i]-b[i]);
        int now=num-(a[i]-b[i]);
        T.update(1,1,n,i,i,-now);
    }
    for (int i=1;i<=n;++i) cc[i]=b[i];
    int now=b[n];
    for (int i=1;i<n;++i) b[i+1]=cc[i];
    b[1]=now;//因为 b[i] 表示 i 到 i+1 的 dis，所以倒置的时候会出现一点问题，需要整体位移
    reverse(a+1,a+n+1);
    reverse(b+1,b+n+1);
    memset(T.c,0,sizeof(T.c));
    memset(T.lazy,0,sizeof(T.lazy));
    memset(d,0,sizeof(d));
    num=0;
    for (int i=1;i<=n;++i) d[i]=d[i-1]+a[i]-b[i];
    num=d[n];
    T.build(1,1,n);
    for (int i=1;i<=n;++i){
        if (T.c[1]>=0) ans.push_back(n-i+1);
        if (i!=1) T.update(1,1,n,1,i-1,a[i]-b[i]);
        if (i!=n) T.update(1,1,n,i+1,n,a[i]-b[i]);
        int now=num-(a[i]-b[i]);
        T.update(1,1,n,i,i,-now);
    }
    sort(ans.begin(),ans.end());
    ans.erase(unique(ans.begin(),ans.end()),ans.end());
    io.writeln(ans.size());
    for (auto i:ans) io.write(i),io.push(' ');
    io.push('\n');
    return 0;
}
```


---

