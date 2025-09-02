# Pair of Topics

## 题目描述

The next lecture in a high school requires two topics to be discussed. The $ i $ -th topic is interesting by $ a_i $ units for the teacher and by $ b_i $ units for the students.

The pair of topics $ i $ and $ j $ ( $ i < j $ ) is called good if $ a_i + a_j > b_i + b_j $ (i.e. it is more interesting for the teacher).

Your task is to find the number of good pairs of topics.

## 样例 #1

### 输入

```
5
4 8 2 6 2
4 5 4 1 3```

### 输出

```
7```

## 样例 #2

### 输入

```
4
1 3 2 4
1 3 2 4```

### 输出

```
0```

# 题解

## 作者：C　C　A (赞：14)

# $CF1324D\ Pair\ of\ Topics'\ Solution$
						
$\qquad\qquad\qquad\qquad\qquad\qquad\qquad\qquad\qquad\qquad\qquad\qquad\qquad\qquad\qquad By$ [$CCA$](https://www.luogu.com.cn/user/78645)

## $Problem$

$\qquad$给定两个数组$a$和$b$，问有多少$i,j(i < j)$对满足$a[i]+a[j]>b[i]+b[j]$。

## $Solution$

$\qquad$我们看到，式子两边同时有$i$和$j$，于是我们移项得$a[i]-b[i]>b[j]-a[j]$。

$\qquad$这样题目就变得非常简单，而且完全没必要用一些复杂的数据结构去维护，这里介绍一种双指针做法。

$\qquad$我们先将$a[i]-b[i]$和$b[i]-a[i]$用$c1[i]$和$c2[i]$保存起来，然后让$c1$和$c2$从小到大排序。

$\qquad$然后记$pos$为$c2$中第一个小于$c1[i]$的位置，我们在$c1$中从$1$扫到$n$，观察到$pos$是单调的，于是便可以在$O(N)$的复杂度内解决统计答案。

$\qquad$最后有一个要注意的点，我们统计出来的答案会出现$(i>j)$的情况，所以要输出$ans/2$。

$\qquad$排序加统计答案，总复杂度$O(NlogN)$。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10;

int n , a[N] , b[N] , c1[N] , c2[N] , pos;
long long ans;

int main(){
	scanf("%d" , &n);
	for(int i = 1; i <= n; i++) scanf("%d" , &a[i]);
	for(int i = 1; i <= n; i++) scanf("%d" , &b[i]);
	for(int i = 1; i <= n; i++)
		c1[i] = a[i] - b[i] , c2[i] = -c1[i] , ans -= (c1[i] > c2[i]);
	sort(c1 + 1 , c1 + n + 1);
	sort(c2 + 1 , c2 + n + 1);
	for(int i = 1; i <= n; i++){
		while(c1[i] > c2[pos + 1] && pos < n) pos++;
		ans += pos;
	}
	printf("%lld" , ans / 2);
	return 0;
}
```

自认为码风还是比较清奇可看的，大家可以对着$Solution$仔细看一下。

最后，[$This\ is\ my\ blog$](https://www.luogu.com.cn/blog/A66-888/) , 有兴趣的可以逛一下，应该能有所收获。

---

## 作者：Rainy7 (赞：8)

- 分析

  我们把这个式子转换一下: $a_i+a_j>b_i+b_j(i<j)$
  
  $$a_i-b_i+a_j-b_j>0(i<j)$$
  
  设 $c_i=a_i-b_i$
  
  所以要求的数对改为: $c_i+c_j \ge 1(i<j)$
  
  我们**把 $c_i$ 从小到大排序。**
  
  对于每一个 $i$ ，用**二分**找到满足条件的最小的 $j$ 。
  
  然后每次统计答案 $ans+=n-j+1$ 。
  
  复杂度 $O(nlogn)$ 。
  
  **注意，要开 long long** ，不然会死在第12个点 ~~（别问我为什么）~~ 。

------------

- 代码


```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const ll Maxn=2e5+5;
ll n,ans,a[Maxn],b[Maxn],c[Maxn];
ll l,r,mid,j;
int main()
{	scanf("%lld",&n);
	for(ll i=1;i<=n;i++)
		scanf("%lld",&a[i]);
	for(ll i=1;i<=n;i++)
		scanf("%lld",&b[i]);
	for(ll i=1;i<=n;i++)
		c[i]=a[i]-b[i];
	sort(c+1,c+1+n);
	for(ll i=1;i<=n;i++)
	{	l=i+1;r=n;j=0;
		while(l<=r)
		{	mid=(l+r)>>1;
			if(c[i]+c[mid]>=1)
			{	j=mid;
				r=mid-1;
			}
			else l=mid+1;
		}
		if(j)ans+=(n-j+1);
	}
	printf("%lld\n",ans);
	return 0;
}

```

---

## 作者：do_while_false (赞：5)

【题目大意】

给定两个长度为 $n$ 的序列，求满足 $a_i+a_j>b_i+b_j(i<j)$ 的$(i,j)$ 的对数.

【思路】

$$a_i+a_j>b_i+b_j(i<j)$$

变形可得
$$a_i-b_i>-(a_j-b_j)$$

设 $c_i=a_i-b_i$

则有
$$c_i+c_j\ge 0 (i<j)$$

我们可以将 $c$ 数组进行排序。

此时对于每一个 $c_i$，我们可以通过二分找出所有符合要求的 $j$。

找到之后 $ans\gets ans+n-j+1$

注意要开 ```long long```

---

## 作者：F_Mu (赞：4)

**题意**

对于两个长度为$n$的数组$a[]$和$b[]$，找到有多少对$i$和$j(i<j)$，满足$a_i+a_j>b_i+b_j$

**分析**

首先发现如果$i$和$j$互换不影响不等式，因此对于$i<j$这个条件，仅仅是满足二元组$(i,j)$和$(j,i)$只算一次

所以将数组打乱顺序后也只需找到所有的二元组$(i,j)$即可

将不等式移项得到
$$
a_j-b_j>b_i-a_i
$$
对于第$i$项来说，我们要找到所有的$j$满足上述条件

因此选择将$a_j-b_j$排序

定义数组$c[]$，有$c[i]=a[i]-b[i]$

方法一：

对于第$i$项，通过二分在$[i+1,n]$找到最小的$j$，满足该不等式，使用$upper\_bound$函数即可

则对于第$i$项，$j$~$n$都是满足的，将答案加上$n-j+1$，如果没找到，则$j=n+1$（$upper\_bound$已经满足）

```cpp
#pragma GCC optimize(3, "Ofast", "inline")

#include <bits/stdc++.h>

#define start ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define ll long long
#define int ll
#define ls st<<1
#define rs st<<1|1
#define pii pair<int,int>
using namespace std;
const int maxn = (ll) 3e5 + 5;
const int mod = 1000000007;
const int inf = 0x3f3f3f3f;

struct node {
    int a, b;
} a[maxn];

int c[maxn];

signed main() {
    start;
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> a[i].a;
    for (int i = 1; i <= n; ++i)
        cin >> a[i].b, c[i] = a[i].a - a[i].b;
    sort(c + 1, c + n + 1);
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        int t = upper_bound(c + i + 1, c + n + 1, -c[i]) - c;
        ans += n - t + 1;
    }
    cout << ans;
    return 0;
}
```



方法二：

注意到排序后，随$i$递增，$b_i-a_i$递减，可以发现满足条件的$j$递减，因此可采取滑动区间的方式

将$now$设置为$n+1$

每次循环若$now>i\&\&c[now - 1] > -c[i]$，则$now-1$也满足不等式，将$now$减一

+ $now>i$，同方法一，$ans+=n-now+1$
+ $now=i$，即$[i+1,n]$都满足条件，又由于$j$是递减的，所以对于后面的$i$，$now<i$，所以$[i+1,n]$也满足条件，采取数列求和直接统计答案即可

```cpp
#pragma GCC optimize(3, "Ofast", "inline")

#include <bits/stdc++.h>

#define start ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define ll long long
#define int ll
#define ls st<<1
#define rs st<<1|1
#define pii pair<int,int>
using namespace std;
const int maxn = (ll) 3e5 + 5;
const int mod = 1000000007;
const int inf = 0x3f3f3f3f;

struct node {
    int a, b;
} a[maxn];

int c[maxn];

signed main() {
    start;
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> a[i].a;
    for (int i = 1; i <= n; ++i)
        cin >> a[i].b, c[i] = a[i].a - a[i].b;
    sort(c + 1, c + n + 1);
    int ans = 0;
    int now = n + 1;
    for (int i = 1; i <= n; ++i) {
        while (now > i && c[now - 1] > -c[i])
            --now;
        if (now == i) {
            ans += (n - i + 1) * (n - i) / 2;
            break;
        }
        ans += n - now + 1;
    }
    cout << ans;
    return 0;
}
```

---

## 作者：WYXkk (赞：4)

题目大意：给定 $a_1,a_2,\cdots,a_n$ 以及 $b_1,b_2,\cdots,b_n$，求使得 $a_i+a_j>b_i+b_j$ 的**无序**数对 $(i,j)$ 的对数。$n\le 2\times10^5$。

解析：

设 $x_i=a_i-b_i$，那么答案就是 $x_i+x_j>0$ 的 $(i,j)$ 的对数。

不难想到对 $x_i$ 从小到大排序，此时若固定 $i$ 则满足条件的 $j$ 就是所有 $i^\prime\le j\le n$。

为了防止重复计数，可以直接强制设定 $j<i$，用 $l(=i^\prime),r(=i)$ 两个位置维护一下就好了。 

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

const int N=200005;
int a[N];
int main()
{
	int n=rd();
	F(i,1,n) rd(a[i]);
	F(i,1,n) a[i]-=rd();
	sort(a+1,a+n+1);
	int l=1,r=n+1;
	ll ans=0;
	while(l<r)
	{
		--r;
		while(a[l]+a[r]<=0) ++l;
		if(l<r) ans+=r-l;
	}
	printf("%lld\n",ans);
	return 0;
}
```



---

## 作者：夏子汐 (赞：2)

## 这里给出一个简单易懂（投机取巧）的方法。

# STL大法好！
题解里面都说了要求出每一个$a_i-b_i$。

怎么求对数呢？

令$k_i=a_i-b_i$。

对于一个$i$，含有它的答案数即为所有大于$-k_i$的数的个数减去$1$（如果$k_i>0$）。

即满足$k_i+k_j>0$且$j \ne i$的$j$的个数。

答案最多为$n^2$，故**每一次计算可以统计的对数一定大于一**，即每一次可以得到一个满足条件的**区间**，必然要是有序的。

先把$k$排序。

令求出的对中$j<i$。（这里的$i,j$均为排序后的下标）

很容易想到upper_bound。

```cpp
w=-k[i];
ans+=i-(upper_bound(k+1,k+1+n,w)-a);
```

复杂度$O(n \log_{n})$

```cpp
//本代码中用a数组代替k数组
#include<cstdio>
#include<iostream>
#include<algorithm>
#define ri register in
#define in long long
#define g() getchar()
inline in read(){//快读
	ri x=0;register char ch=g();
	while(ch>'9' || ch<'0')ch=g();
	while(ch<='9' && ch>='0')
		x=(x<<3)+(x<<1)+ch-'0',ch=g();
	return x;
}
using namespace std;
in a[200005];
int main(){
	ri n=read(),ans=0;
	for(ri i=0;i<n;++i)a[i]=read();
	for(ri i=0;i<n;++i)a[i]-=read();//直接计算k数组
	sort(a,a+n);
	for(ri i=upper_bound(a,a+n,0)-a,w;i<n;++i){
	//upper_bound返回目标指针，减去a就是目标的下标 
	//a[i]刚开始就是大于0的，加上一个比a[i]小的数可能大于0。 
		w=-a[i],ans+=i-(upper_bound(a,a+n,w)-a);
		//求出第一个大于-a[i]的下标，用i减它即是当前答案
		//如果没有符合条件的，会查找出来i，因为a[i]>0,对答案的贡献为0。 
	}
	cout<<ans;//I64d不好用
	return 0;
}
```
~~（偏序是什么？蒟蒻不知道）。~~

---

## 作者：小恐 (赞：2)

思路就是将差都记录下来，从小到大排序，对于每一个小于等于0的数，算出比他的相反数大的数的个数。对于所有大于0的数，算出挑选出两个数的方法数，应该是$C_n^2=\dfrac{n\times (n-1)} 2$。

至于算出比他的相反数大的数的个数，我们排完序后，找到第一个比它的相反数大的数。为了节省时间，我们采用二分。大佬们有用STL的，但我~~要锻炼自己~~（不会写），于是我写了一个递归的二分，查找第一个大于它的相反数的数。

上代码：
```cpp
#include<stdio.h>
#include<algorithm>
using namespace std;
int n,a[200005],cha[200005],b;
long long ans;
long long erfen(int l,int r,int x)
{
	int m=l+(r-l)/2;
	if(l>r)
		return l;
	if(cha[m]<=x)
		return erfen(m+1,r,x);
	return erfen(l,m-1,x);
}
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
		scanf("%d",a+i);
	for(int i=1;i<=n;++i)
	{
		scanf("%d",&b);
		cha[i]=a[i]-b;
	}
	sort(cha+1,cha+n+1);
	for(int i=1;i<=n;++i)
	{
		if(cha[i]>0)
		{
			ans+=(long long)(n-i+1)*(n-i)/2;
			break;
		}
		ans+=n-erfen(i+1,n,-cha[i])+1;
	}
	printf("%lld",ans);
	return 0;
}
```
**代码要自己敲，不要Ctrl c+Ctrl v哦！**

---

## 作者：devout (赞：1)

[博客内食用更佳](https://blog.csdn.net/devout_/article/details/104858457)

我们发现，这道题给出的条件是
$$a_i+a_j>b_i+b_j$$
$$-(a_i-b_i)<a_j-b_j$$
那么对于每个$i$，我们看有多少个$j$满足条件，显然这个东西可以用二分来解决

我们存出每个$a_i-b_i$，按从小到大排序

然后二分就可以，注意应该从$i+1$-$n$用$upper\_bound$，因为会算重

```cpp
#include <bits/stdc++.h>
using namespace std;

# define Rep(i,a,b) for(int i=a;i<=b;i++)
# define _Rep(i,a,b) for(int i=a;i>=b;i--)
# define RepG(i,u) for(int i=head[u];~i;i=e[i].next)

typedef long long ll;

const int N=2e5+5;

template<typename T> void read(T &x){
   x=0;int f=1;
   char c=getchar();
   for(;!isdigit(c);c=getchar())if(c=='-')f=-1;
   for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+c-'0';
    x*=f;
}

int n;
ll ans;

struct node{
    int a,b;
    bool operator < (const node &cmp)const{
        return a-b<cmp.a-cmp.b;
    }
}a[N];

int b[N];

int main()
{
    read(n);
    Rep(i,1,n)read(a[i].a);
    Rep(i,1,n)read(a[i].b);
    sort(a+1,a+n+1);
    Rep(i,1,n)b[i]=a[i].a-a[i].b;
    // Rep(i,1,n)printf("%d\n",b[i]);
    Rep(i,1,n){
        int x=upper_bound(b+i+1,b+n+1,-b[i])-b;
        ans+=(n-x+1);
    }
    printf("%lld\n",ans);
    return 0;
}
```


---

## 作者：chenxia25 (赞：1)

>### [洛谷题目页面传送门](https://www.luogu.com.cn/problem/CF1324D) & [CodeForces题目页面传送门](https://codeforces.com/contest/1324/problem/D)

>给定$2$个长度为$n$的数组$a,b$，求有多少个有序对$(i,j)$满足$i<j$且$a_i+a_j>b_i+b_j$。

>$n\in\left[2,2\times10^5\right],a_i,b_i\in\left[1,10^9\right]$。

$a_i+a_j>b_i+b_j\Leftrightarrow a_i-b_i>b_j-a_j$，这样左边仅关于$i$，右边仅关于$j$。于是我们把$\forall i\in[1,n],a_i-b_i,b_i-a_i$这$2n$个数一起离散化咯，然后类似BIT求逆序对那样建一个值域BIT，从后往前扫描，每扫到一个数$i$，给答案贡献值域区间$(-\infty,a_i-b_i)$上的区间计数的结果，再将$b_i-a_i$插入BIT。时间复杂度$\mathrm O(n\log_2n)$。

答案会爆`int`，记得开`long long`。

下面是AC代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long//答案爆int
#define pb push_back
int lowbit(int x){return x&-x;}
const int N=200000;
int n;
int a[N+1];
int b[N+1];
vector<int> nums;
void discrete(){//离散化 
	sort(nums.begin(),nums.end());
	nums.resize(unique(nums.begin(),nums.end())-nums.begin());
	for(int i=1;i<=n;i++)
		b[i]=lower_bound(nums.begin(),nums.end(),-a[i])-nums.begin()+1,
		a[i]=lower_bound(nums.begin(),nums.end(),a[i])-nums.begin()+1;
}
struct bitree{//BIT 
	int sum[2*N+1];
	void init(){memset(sum,0,sizeof(sum));}
	void add(int x){//添加x 
		while(x<=nums.size())sum[x]++,x+=lowbit(x);
	}
	int Sum(int x){//前缀计数 
		int res=0;
		while(x)res+=sum[x],x-=lowbit(x);
		return res;
	}
}bit;
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++)scanf("%lld",a+i);
	for(int i=1;i<=n;i++){
		int x;
		cin>>x;
		a[i]-=x;
		nums.pb(a[i]);//a[i]-b[i]
		nums.pb(-a[i]);//b[i]-a[i]
	}
	discrete();
	int ans=0;
	bit.init();
	for(int i=n;i;i--){
		ans+=bit.Sum(a[i]-1);//贡献答案 
		bit.add(b[i]);//添加 
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：suxxsfe (赞：1)

好像题解里都是树状数组(~~起码我翻到的是~~  
说一种cdq分治的（这应该算是cdq分治了  
用cdq比较简单，所以可以作为一个练手题  
cdq分治其实是一种模糊的思想，处理$[l,r]$区间内，有多少$(i,j)$满足某种条件  
这里假设$i<j$，我们取一个$mid=\frac{i+j}{2}$  

- $i<j\leq mid$，问题转换到区间$[l,mid]$上解决  
- $mid<i<j$， 问题转换到区间$[mid+1,r]$上解决  
- $i\leq mid <j$，注意这里才是真正干活的地方，前面两种情况都是甩锅给更小的区间  

然后具体看下这个题  
条件是$a_i+a_j>b_i+b_j(i<j)$  
可以转化为$a_i-b_i>b_j-a_j(i<j)$，其实就是把和$i,j$有关的项分别放在不等号两边  
考虑$i\leq mid<j$的情况，则$i<j$这个条件已经没用了  
开两个数组$x,y$，分别存$a_i-b_i(l\leq i\leq mid)$和$b_j-a_j(mid<j\leq r)$的值  
然后给它们排个序  
从小到大考虑x中元素，有几个y中元素比它小     
具体实现用一个cnt变量，表示对于当前的x中的元素，有几个比它小的y中元素，然后每次$ans=ans+cnt$，，然后用两个指针分别指向x和y中当前的值就行了  
每次对区间排序的复杂度是$O(r-l+1)$的，每个区间被排序$\log n$次（每次把一个区间分成它的一半，因此最多递归$\log n$层，每层）  
画张~~丑陋的~~图理解一下  
![](https://cdn.luogu.com.cn/upload/image_hosting/2wgpc8vh.png)
所以总时间复杂度$O(n \log^2 n)$  
```cpp  
#include<cstdio>
#include<algorithm>
#include<iostream>
#include<cmath>
#include<iomanip>
#include<cstring>
#define reg register
#define EN std::puts("")
#define LL long long
inline int read(){
	int x=0,y=1;
	char c=std::getchar();
	while(c<'0'||c>'9'){if(c=='-') y=0;c=std::getchar();}
	while(c>='0'&&c<='9'){x=x*10+(c^48);c=std::getchar();}
	return y?x:-x;
}
int n;
int a[200006],b[200006];
int x[200006],y[200006];
LL work(int l,int r){
	if(l==r) return 0;
	int mid=(l+r)>>1;
	x[0]=y[0]=0;
	for(reg int i=l;i<=mid;i++) x[++x[0]]=a[i]-b[i];
	for(reg int i=mid+1;i<=r;i++) y[++y[0]]=b[i]-a[i];
	std::sort(x+1,x+1+x[0]);std::sort(y+1,y+1+y[0]);
	reg int posl=1,posr=1,cnt=0;
	reg LL ans=0;
	for(;posl<=x[0];posl++){
		for(;posr<=y[0]&&y[posr]<x[posl];posr++) cnt++;
		ans+=cnt;
	}
	return ans+work(l,mid)+work(mid+1,r);
}
int main(){
	n=read();
	for(reg int i=1;i<=n;i++) a[i]=read();
	for(reg int i=1;i<=n;i++) b[i]=read();
	std::printf("%lld",work(1,n));
	return 0;
}
```

---

## 作者：__OwO__ (赞：1)

看到有大佬用权值线段树做,先膜

我觉得没有必要其实时间复杂度的瓶颈在排序

所以后面处理用$O(n)$即可

我们先预处理,$a_i-=b_i$

所以现在要做的就是判断数列里有多少对和大于零的数对

那我们先排序,在用两个指针从左到右和从右到左枚举即可求出对数

代码也很简单

```cpp
#include<bits/stdc++.h>
#define ull long long
using namespace std;
ull n;
ull arr[200010];
int main(){
	scanf("%lld",&n);
	for(register ull i=1;i<=n;i++)scanf("%lld",&arr[i]);
	for(register ull i=1;i<=n;i++){
		ull tmp;scanf("%lld",&tmp);
		arr[i]-=tmp;
	}
	sort(arr+1,arr+n+1);
	ull cur=1;
	ull ans=0;
	for(register ull i=n;i>=1;i--){
		if(arr[i]<0||cur>=i)break;
		while(arr[cur]+arr[i]<=0)cur++;
		if(i-cur>0)ans+=(i-cur);
	}
	printf("%lld",ans);
	return 0;
}
```
注意这道题要```long long```

---

## 作者：HoshizoraZ (赞：1)

题意：给定一个长度为 $n$ 的序列，求出满足 $1 \le i<j \le n$ 且 $a_i+a_j>b_i+b_j$ 的 $(i,j)$ 对数。

----------------

我们把 $a_i+a_j>b_i+b_j$ 变形，变成 $(a_i-b_i)+(a_j-b_j)>0$。

令 $c_i=a_i-b_i\;(1 \le i \le n)$，那么要求就只有 $c_i+c_j>0$ 了。

对于 $1$ 到 $n$ 中每一个 $i$，我们都找到满足 $c_j>-c_i$ 的 $j$ 的个数，并加起来统计，这可以用 **排序 + STL 或 二分** 解决。

 因为对于 $i \neq j$ 时，$(i,j)$ 和 $(j,i)$ 肯定有一个不满足 $i<j$，所以统计出来的答案有**恰好一半**是不满足 $i<j$ 的，要除以 $2$。

时间复杂度 $O(n\; \log\; n)$。

----------------

在统计的时候，我们发现统计到的 $j$ 没有满足 $j \neq i$。

如果当前的 $i$ 满足 $2c_i>0$，即 $c_i>0$ 时，自己肯定会被统计到。

所以答案是统计的值减去满足 $c_i>0$ 的 $i$ 的个数，再除以 $2$。

**参考代码**：

```cpp
#include <algorithm>
#include <cstdio>
#define INF 1e9
#define eps 1e-6
typedef long long ll;

int n, a[200010], b[200010], k;
ll ans;								// 注意开 long long

int main(){

	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	for(int i = 1, x; i <= n; i++)
		scanf("%d", &x), a[i] -= x;	// 此处 a_i 就等同于上面的 c_i
	
	std::sort(a + 1, a + n + 1);
	for(int i = 1; i <= n; i++){
		k = std::upper_bound(a + 1, a + n + 1, -a[i]) - a;	
		// 上面求的是第一个大于 -a_i 的数字的位置
		if(a[i] > 0) ans--;			// 特判 a_i > 0 的情况
		ans += (ll)n - k + 1;
	}
	
	printf("%lld\n", ans >> 1);		// 答案要除以 2

	return 0;
}
```

---

## 作者：LB_tq (赞：1)

# Solution
树状数组做法。

题意可以转化为：定义 $c_i=a_i-b_i$ 则要找出所有的 $i,j$ 满足 $c_i+c_j>0$ 且 $i<j$ 。

定义两个树状数组 $c1,c2$ 分别存储正数和负数的出现次数，其中 $c1_i$ 表示从 $1$ 到 $i$ 所有数的出现次数之和， $c2_i$ 表示从 $-i$ 到 $-1$ 所有数的出现次数之和。

之后依次考虑 $c_i$ :

- 若 $c_i=0$ ,则答案加上大于 $0$ 的 $c_j (j<i)$ 的出现次数。
- 若 $c_i>0$ ,则答案加上大于 $0$ 的 $c_j (j<i)$ 的出现次数与等于 $0$ 的 $c_j (j<i)$ 的出现次数之和。
- 若 $c_i<0$ ,则答案加上大于 $0$ 的 $c_j (j<i)$ 的出现次数。

每次维护树状数组即可，注意树状数组下标不能为 $0$ ,所以单独处理等于 $0$ 的情况。

数据范围较大，需要进行离散化。

时间复杂度 $O(nlogn)$ 。
# Code
```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
const int maxn=2e5+10;
int n,m,a[maxn],b[maxn],c[maxn];
int c1[maxn],c2[maxn];
long long ans;
int check(int x){
	int l=1,r=m,mid;
	while(l<r){
		mid=(l+r)>>1;
		if(c[mid]<x)
			l=mid+1;
		else
			r=mid;
	}
	return l;
}
int lowbit(int x){
	return x&-x;
}
int ask1(int x){
	int sum=0;
	for(int i=x;i>0;i-=lowbit(i))
		sum+=c1[i];
	return sum;
}
int ask2(int x){
	int sum=0;
	for(int i=x;i>0;i-=lowbit(i))
		sum+=c2[i];
	return sum;
}
void add1(int x,int y){
	for(int i=x;i<=m;i+=lowbit(i))
		c1[i]+=y;
}
void add2(int x,int y){
	for(int i=x;i<=m;i+=lowbit(i))
		c2[i]+=y;
}
int main(){
	int x,y,z;
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	for(int i=1;i<=n;i++){
		cin>>x;
		a[i]-=x;
		b[i]=abs(a[i]);
	}
	sort(b+1,b+n+1);
	for(int i=1;i<=n;i++){
		if(b[i]==0)
			continue;
		if(i==1||b[i]!=b[i-1])
			c[++m]=b[i];
	}
	x=y=0;
	for(int i=1;i<=n;i++){
		if(a[i]==0){
			ans+=x;
			y++;
		}
		else if(a[i]>0){
			ans+=x+y;
			z=check(a[i]);
			x++;
			ans+=ask2(z-1);
			add1(z,1);
		}
		else{
			a[i]=-a[i];
			z=check(a[i]);
			ans+=(x-ask1(z));
			add2(z,1);
		}
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：lcc17 (赞：0)

**Solution:**

- 记录每个c[i]=a[i]-b[i]。

- 因为要让老师赢，所以c[i]+c[j]>0。

- 从小到大排序数组c。

- 显然，若c[i]+c[j]>0,则c[i]+c[j+1]>0成立，所以二分查找合适的最小的j，记录ans=ans+n-j+1;

- 因为n最大为200000,所以ans<=n^2会爆int，要开long long。

```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
inline int read(){
	int f=1,res=0;char c=getchar();
	while(c<'0'||c>'9') {if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){res=res*10+c-'0',c=getchar();}
	return f*res;
}
const int maxn=2e5+5;
int a[maxn],b[maxn],c[maxn],n;
long long ans=0;
int main(){
	n=read();
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=1;i<=n;i++) {
		b[i]=read();
		c[i]=a[i]-b[i];
	}
	sort(c+1,c+n+1);
	for(int i=1;i<=n;i++){
		int l=i+1,r=n,cnt=n+1;//寻找的j>i
		while(l<=r){
			int mid=l+r>>1;
			if(c[i]+c[mid]>0) {
				r=mid-1;
				cnt=mid;
			}
			else l=mid+1;
		} 
		ans=ans+n-cnt+1;
	}
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：registerGen (赞：0)

- 给你两组数 $a_i,b_i$。
- 求满足 $a_i+a_j>b_i+b_j$ 的所有下标 $(i,j)$ 的数量。

---

由 $a_i+a_j>b_i+b_j$ 得 $(a_i-b_i)+(a_j-b_j)>0$，再令 $c_i=a_i-b_i$，则题目即，

- 给定 $c_i$，求满足 $c_i+c_j>0$ 的所有下标 $(i,j)$ 的数量。

怎么做呢？

我们先把 $c_i$ 排个序。

维护一个指针 $ptr$，初始值为 $1$。

运行以下的伪代码：

```plain
ans := 0
for i = n downto 1:
    if c[i] <= 0: break
    while c[ptr] + c[i] <= 0:
    	ptr := ptr + 1
    ans := ans + i - ptr
```

$ans$ 即为答案。

注意到此时 $c_i$ 单调，所以当程序进入下一次循环时，$c_1$ 到 $c_{ptr-1}$ 一定不是答案。

---

下面放出代码，时间复杂度 $O(n\log n+n)=O(n\log n)$。

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>

typedef long long ll;

const int N=2e5;

int n,a[N+10],b[N+10],c[N+10];

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",a+i);
	for(int i=1;i<=n;i++)
		scanf("%d",b+i),c[i]=a[i]-b[i];
	std::sort(c+1,c+n+1);
	int ptr=1;
	ll ans=0;
	for(int i=n;i>=1&&c[i]>0;i--)
	{
		while(c[ptr]+c[i]<=0)ptr++;
		ans+=i-ptr;
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

