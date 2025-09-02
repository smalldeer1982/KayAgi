# [USACO11NOV] Above the Median G

## 题目描述

Farmer John has lined up his N (1 <= N <= 100,000) cows in a row to measure their heights; cow i has height H\_i (1 <= H\_i <= 1,000,000,000) nanometers--FJ believes in precise measurements! He wants to take a picture of some contiguous subsequence of the cows to submit to a bovine photography contest at the county fair.

The fair has a very strange rule about all submitted photos: a photograph is only valid to submit if it depicts a group of cows whose median height is at least a certain threshold X (1 <= X <= 1,000,000,000).

For purposes of this problem, we define the median of an array A[0...K] to be A[ceiling(K/2)] after A is sorted, where ceiling(K/2) gives K/2 rounded up to the nearest integer (or K/2 itself, it K/2 is an integer to begin with). For example the median of {7, 3, 2, 6} is 6, and the median of {5, 4, 8} is 5.

Please help FJ count the number of different contiguous subsequences of his cows that he could potentially submit to the photography contest.

给出一串数字，问中位数大于等于X的连续子串有几个。（这里如果有偶数个数，定义为偏大的那一个而非中间取平均）


## 说明/提示

FJ's four cows have heights 10, 5, 6, 2. We want to know how many contiguous subsequences have median at least 6.


There are 10 possible contiguous subsequences to consider. Of these, only 7 have median at least 6. They are {10}, {6}, {10, 5}, {5, 6}, {6, 2}, {10, 5, 6}, {10, 5, 6, 2}.


## 样例 #1

### 输入

```
4 6 
10 
5 
6 
2 
```

### 输出

```
7 
```

# 题解

## 作者：封禁用户 (赞：27)

其实每一个数都只有2种情况：大于等于x、小于x，我们把第一种情况当成1，第二种情况当成-1，相当于就变成了有多少个和不为负数的子序列，用前缀和解决就是n^2，但还是不行。继续考虑：现在这个问题是要求sum[j]-sum[i-1]>=0，同时加上sum[i-1]后就变成了询问j以前有多少个i满足sum[i]<=sum[j]。由于sum[j]和sum[j-1]最多相差1，那么如果sum[j]比较大，那么这个的答案就相当于ans[j-1]+之前sum[j]有多少个，反之类似。（开longlong）

附上代码：

```cpp
#include<cstdio>
long long n,t,x,ans,a[100001],b[200001];
int main()
{
    scanf("%lld%lld",&n,&x);
    a[0]=n;
    b[n]=1;
    for (int i=1;i<=n;i++)
    {
        scanf("%lld",&t);
        if (t>=x)a[i]=a[i-1]+1;
        else a[i]=a[i-1]-1;
    }
    t=0;
    for (int i=1;i<=n;i++)
    {
        if (a[i]>a[i-1])t-=b[a[i]];
        else t+=b[a[i-1]];
        b[a[i]]++;
        ans+=t;
    }
    printf("%lld",n*(n+1)/2-ans);
}
```

---

## 作者：关怀他人 (赞：18)

看到楼上的dalao讲了逆序对的写法但没给代码，我来补个代码

------------

#### 题目分析:####
   简单的dp的思想，树状数组优化。设数组dp[i]表示以第i元素结尾时，>=X的数
量。那么以第i元素结尾的符合条件的子序列要满足 大于X的数不少于小于X的数
则开头元素j需满足：
- $2 * (dp[i] - dp[j - 1]) >= i - (j - 1)$
- 即 $2 * dp[i] - i >= 2 * dp[j - 1] - (j - 1)$
- 令$ w = 2 * dp[i] - i$

只需结尾元素的 w 大于开头元素的 w ，树状数组维护即可
#### 代码:
- 树状数组版

```cpp
#include <bits/stdc++.h>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;

const int INF = 0x3f3f3f3f;

ll n,x,ans; //开long long
ll a,pre[200005],c[200005]; //注意要开2*10^5

int lowbit(int x){
	return x & -x;
}

void add(int x,int k){
	while(x <= n * 2 + 1){
		c[x] += k;
		x += lowbit(x);
	}
}

int sum(int x){
	int cnt = 0;
	while(x >= 1){
		cnt += c[x];
		x -= lowbit(x);
	}
	return cnt;
}

int main(){
	scanf("%lld%lld",&n,&x);
	for(int i = 1;i <= n;i++){
		scanf("%lld",&a);
		if(a >= x)
		    pre[i] = pre[i - 1] + 1;
		else
		    pre[i] = pre[i - 1] - 1; 
        //处理前缀
	}
	add(n + 1,1);
	for(int i = 1;i <= n;i++){
		//cout << pre[i] << " ";
		ans += sum(pre[i] + n + 1);
		add(pre[i] + n + 1,1);
	} //树状数组求逆序对
	printf("%lld\n",ans);
	return 0;
}

```

---

## 作者：BlueRose73 (赞：13)

前缀和优化，sum[i]记录1~i中>=x的数的个数（可以为负，当<x的数个数大于>x的数的个数），sum[i]-sum[j-1]>=0 (1<=j<=i)即区间[j,i]的中位数>=x。求这样的(i,j)的个数。移下项，变成sum[i]>=sum[j] (0<=j<i) ，发现就是求逆序对的个数。结合10^5数据范围，可以归并排序/树状数组求逆序对。

但是看了楼上dalao的题解，竟然有O(n)做法！它巧妙地利用了abs(sum[i]-sum[i-1])=1的性质，思想有点像dp，但是我看了一个小时才看懂，在这里更详细的注释一下代码。

如果数据范围开大就不仅普及了吧。。。

另外楼上其实先求的中位数<x的答案然后用总区间数去减，代码更简洁。这里我为了让大家更明白就不这样做了。

见代码注释

```cpp
#include<cstdio>
using namespace std;
const int maxn=1000005;//开100005会WA一个点，不知道为啥 
int n,x,sum[maxn],num[maxn];//sum是前缀和，num[i]表示大小为i的sum出现的次数 
int main(){
    scanf("%d%d",&n,&x);
    int h;
    for(int i=1;i<=n;i++){
        scanf("%d",&h);
        if(h>=x)sum[i]=sum[i-1]+1;
        else sum[i]=sum[i-1]-1;
    }//维护前缀和 
    long long ans=0;
    int pre=0;//pre记录上一个i的答案 ，即以i-1结尾的满足题意的区间个数 
    num[0]=1;//因为sum[0]=0，所以num[0]要赋1 
    for(int i=1;i<=n;i++){//以下两行为核心代码 
        if(sum[i]>sum[i-1])pre+=num[sum[i]]+1;//如果h[i]>h[i-1]以第i个数结尾的合法区间数=以i-1结尾的合法区间数 +[j,i] (j<i&&sum[j]==sum[i])+[i-1,i] 
        else pre-=num[sum[i-1]]-1;//如果h[i]<h[i-1] 以第i个数结尾的区间数=以i-1结尾的合法区间数 -[j,i](j<i-1&&sum[j]==sum[i-1])的个数。因为这些区间是i-1可以覆盖到而i不能覆盖到的。因为j<i-1所以减掉 num[sum[i-1]]之后还得加上j=i-1时多减的1 
        num[sum[i]]++;
        ans+=pre;
    }
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：徐晨轩✅ (赞：5)

这道题乍一看，好像要用 $ O(n^3\log_2n) $（两重循环+$ \mathtt{sort} $）的时间复杂度，但是 $ n \leq 10^5 $，肯定超时。

------------
但题目中说求中位数，并不需要整个排序。我们可以将大于等于 $ x $ 的数变成 $ 1 $，小于 $ x $ 的数变成 $ -1 $，这样题目就是问，有多少个区间 $ [i,j] $，使得 $ a[i..j] $ 的和 $ \geq 0 $。

------------
即使使用前缀和，也必须用双重循环（枚举i，j，$ O(n^2) $）才能做到，所以还是超时（此题只能用$ O(n\log_2n) $以下的时间复杂度）。

------------
这时，我们就要请出我们的重头戏：**逆序对！！！**$ O(n\log_2n) $

[逆序对不会的，请点击这里](http://luogu.com.cn/problem/P1908)

------------
刚才我们说到，要求 $ sum[i]-sum[j-1] \geq 0 $ 的有多少种 $ (i,j) $ 组合，不等式两边各加上 $ sum[j-1] $，就变成了 $ sum[i]≥sum[j-1] $。反过来，就是求有多少对不符合 $ sum[j-1]>sum[i] $，这就是我们熟悉的**逆序对**啦！**（注意要开 $ \mathtt{long} $ $ \mathtt{long} $）**

------------
最后别忘了，要用**总的组数 $ C_n^2+n = C_{n+1}^2 $ 减去逆序对个数**才是答案！！！

------------
$\mathtt{code}$ $\mathtt{below}$：
```cpp
#include <stdio.h>
long long n,x,num;
long long ans;
long long a[100001];
long long tmp[100001];
void merge(int l,int mid,int r)
{
	int i=l,j=mid+1,k=l;
	while(i<=mid&&j<=r)
	{
		if(a[i]<=a[j])tmp[k++]=a[i++];
		else tmp[k++]=a[j++],ans+=1ll*mid-i+1;
	}
	while(i<=mid)tmp[k++]=a[i++];
	while(j<=r)tmp[k++]=a[j++];
	for(int i=l;i<=r;i++)a[i]=tmp[i];
}
void msort(int l,int r)
{
	if(l==r)return;
	int mid=l+(r-l)/2;
	msort(l,mid);
	msort(mid+1,r);
	merge(l,mid,r);
}
int main()
{
	scanf("%lld%lld",&n,&x);
	for(int i=1;i<=n;i++)
		scanf("%lld",&num),
		a[i]=a[i-1]+(num>=x?1:-1);
	for(int i=1;i<=n;i++)
		printf("%lld ",a[i]);
	printf("\n");
	msort(0,n);
	//求逆序对
	//特别注意：这里一定要写成msort(0,n)，而不是msort(1,n)
	//因为前缀和包括a[0]！（坑1）
	printf("%lld",n*(n+1)/2-ans);
	//不要写成n*(n-1)/2-ans，因为还有n个[i,i]这样的区间
	//n*(n+1)/2=n*(n-1+2)/2=n*(n-1)+n*2/2=n*(n-1)/2+n（坑2）
	return 0;
}
```


---

## 作者：ycyaw (赞：5)

对于这种中位数的题目，按照套路，把大于等于$x$的置为$1$，小于$x$的置为$-1$，然后先计算一波前缀和。

然后，问题就转化成要找满足$sum[r]-sum[l-1]>=0$的$(l,r)$的对数。

枚举这个$l-1$，即枚举$0$到$n-1$，每次求$sum[r]>=sum[l-1]$的$r$的个数，显然我们可以用树状数组很方便的维护出来，那么这题就解决了。

注意$sum$可能为负，下标要进行整体加。

复杂度$O(n\ log \ n)$。

$Code\ below:$
```cpp
#include<bits/stdc++.h>
#define ts cout<<"ok"<<endl
#define ll long long
#define hh puts("")
using namespace std;
int n,m,a[100005],b[100005],s[100005],tr[500005],tong[500005];
ll ans;
inline int read(){
    int ret=0,ff=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-') ff=-ff;ch=getchar();}
    while(isdigit(ch)){ret=ret*10+(ch^48);ch=getchar();}
    return ret*ff;
}
inline int lowbit(int x){
    return (x)&(-x);
}
inline int change(int x){
    return x+100001;
}
inline void add(int x,int v){
    while(x<=210000){
        tr[x]+=v;
        x+=lowbit(x);
    }
}
inline int query(int x){
    int res=0;
    while(x){
        res+=tr[x];
        x-=lowbit(x);
    }
    return res;
}
signed main(){
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        a[i]=read();
        if(a[i]>=m) b[i]=1;
        else b[i]=-1;
    }
    add(change(0),1);
    tong[change(0)]++;
    for(int i=1;i<=n;i++){
        s[i]=s[i-1]+b[i];
        add(change(s[i]),1);
        tong[change(s[i])]++;
    }
    for(int i=0;i<n;i++){
        int t=n-i-query(change(s[i]))+tong[change(s[i])];
        ans+=t;
        add(change(s[i]),-1);
        tong[change(s[i])]--;
    }
    printf("%lld",ans);
    return 0;
}
```


---

## 作者：Zhai0915 (赞：3)

## [P3031 [USACO11NOV] Above the Median G](https://www.luogu.com.cn/problem/P3031) 题解

### 1. 审题

注意到 $n \le 10^5$，无法枚举每一段区间，考虑正难则反。

### 2.思路

用前缀和的思想，$a_i$ 不小于 $x$ 时第 $i$ 位是 $1$，否则是 $0$，前缀和累加起来。
若前缀和数组中形成了逆序对，则中间这段区间的中位数比 $x$ 小，这一个子串不符合要求。
所以，用总区间数减去前缀和数组中的逆序对数，就能得出答案。

### 3.代码

- 求逆序对数量的部分(不会逆序对的读者请移步[P1908 逆序对](https://www.luogu.com.cn/problem/P1908))

```cpp
long long a[5000001],b[5000001]; //b数组为临时数组
long long msort(int l,int r)
{
    long long ans=0;   //不开LL见祖宗
    if(l==r)
    return ans;
    int mid=(l+r)/2;
    ans+=msort(l,mid);  
    ans+=msort(mid+1,r);    //分治法统计子串答案
    int i=l,j=mid+1;
    while(i<=mid&&j<=r)
    {
        if(a[i]<=a[j])
        b[i+j-mid-1]=a[i],i++,ans+=j-mid-1;//边归并排序边算逆序对数
        else
        b[i+j-mid-1]=a[j],j++;      //此处不要重复计算逆序对数
    } 
    while(i<=mid)
    b[i+j-mid-1]=a[i],i++,ans+=j-mid-1; //把最后部分插入数组，别忘了计算逆序对数
    while(j<=r)
    b[i+j-mid-1]=a[j],j++;   
    for(int k=l;k<=r;k++)
    a[k]=b[k];    //复制到原数组
    return ans;
}
```

- 输入并做前缀和

```cpp
long long n;        //不开（）见（）
cin>>n;
long long x;       //不（）LL（）祖宗
cin>>x;
for(int i=1;i<=n;i++)
cin>>a[i];         //输入数组
for(int i=1;i<=n;i++)
{
    if(a[i]>=x)      
    a[i]=a[i-1]+1;
    else
    a[i]=a[i-1]-1;   //为求出中位数大于等于x的连续子串有几个而用前缀和处理
}
```

- 输出答案

```cpp
cout<<n*(n+1)/2-msort(0,n);  //1.注意子串中可只有1个元素 2.前缀和数组从0开始！否则喜提30pts
```

### 3.提交记录与结语

[提交记录(代码在上一部分已经给出)](https://www.luogu.com.cn/record/116462021) 

分治算法是一个十分有用的算法，希望读者可以掌握。此处给出几道练习题:[点击这个有十三个字的超链接](https://www.luogu.com.cn/training/342323)

---

## 作者：囧仙 (赞：2)

## 题目大意

> 给定长度为 $n$ 的序列 $A$ ，求其中有多少个子区间，它的中位数不小于 $x$ 。若长度为偶数，中位数取中间较大的那个数。

## 题解

容易发现，一个集合内的中位数不小于 $x$ ，等价于集合内“不小于 $x$ 的数字的个数”不小于“集合内小于 $x$ 的数的个数”（有一点绕口……）

将不小于 $x$ 的数字转换为 $1$ ，小于 $x$ 的数字转换为 $-1$ ，得到新的序列 $B$ ，问题转化为求出有多少个子区间的数值和不小于 $0$ 。可以使用前缀和进行优化。

记 $\displaystyle S_n=\sum_{i=1}^n B_i$ ，于是有 $\displaystyle\sum_{i=l}^rB_i=S_r-S_{l-1}$ 。枚举右端点 $r$ ，我们的任务是要计算出有多少个 $l-1$ ，满足 $S_{l-1}\le S_r$ 。使用树状数组。由于 $S_n$ 可能出现负数值，于是统一加上一个数字 $n$ 处理。



## 参考代码

````cpp
#include<bits/stdc++.h>
#define up(l,r,i) for(int i=l,END##i=r;i<=END##i;++i)
#define dn(r,l,i) for(int i=r,END##i=l;i>=END##i;--i)
using namespace std;
typedef long long i64;
const int INF =2147483647;
const int MAXN=2e5+3;
int n,x,D[MAXN],t,s; i64 ans;
int qread(){
    int w=1,c,ret;
    while((c=getchar())> '9'||c< '0') w=(c=='-'?-1:1); ret=c-'0';
    while((c=getchar())>='0'&&c<='9') ret=ret*10+c-'0';
    return ret*w;
}
void add(int x){        while(x<=t)  ++D[x],x+=x&-x;          }
int  qry(int x){int r=0;while(x> 0) r+=D[x],x-=x&-x; return r;}
int main(){
    n=qread(),t=n*2,x=qread(),add(n); up(1,n,i){
        int u=qread(); if(u>=x) ++s; else --s;
        ans+=qry(s+n),add(s+n);
    }
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：Fireworks_Rise (赞：1)

不是大佬的我只能总结小技巧：本题可把大于等于 $x$ 的数标为 $-1$，再把小于 $x$ 的数标为 $1$，用前缀和 $sum$ 维护。

对于某一个从 $j$ 到 $i$ 的子序列，要使得序列的中位数大于等于 $x$，则满足 $sum_i-sum{j-1}\ge 0$，可推出以 $i$ 为结尾的子序列对答案的贡献为 $i$ 之前 $sum_{j-1}\le sum_i$ 的个数，最后累加所有个数即可。

蒟蒻用了树状数组去做维护前缀和...

注意：$p$ 的值可能为负数，进而会导致 $c$ 数组的下标为负，所以需要整体偏移下标，即 $p+n+1$。

# Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10;
int n,x,a,c[N];
inline int lowbit(int x) {
	return x&(-x);
}
inline void add(int x,int k) {
	while(x<=(n<<1|1)) {
		c[x]+=k;
		x+=lowbit(x);
	}
}
inline int getsum(int x) {
	int ans=0;
	while(x) {
		ans+=c[x];
		x-=lowbit(x);
	}
	return ans;
}
signed main() {
	scanf("%lld%lld",&n,&x);
	add(n+1,1);
	int p=0,sum=0;
	for(int i=1;i<=n;i++) {
		scanf("%lld",&a);
		if(a>=x) p++;
		else p--;
		sum+=getsum(p+n+1);
		add(p+n+1,1);
	}
	printf("%lld\n",sum);
	return 0;
}
```


---

## 作者：JoyJoyGang (赞：0)

给出一串数字，问中位数大于等于X的连续子串有几个。这里如果有偶数个数，定义为偏大的那一个而非中间取平均。

要求找到子串的中位数大于等于 $x$，那么我们对原序列进行一个变化，将原序列中大于等于 $x$ 的数负值为 $1$，小于 $x$ 的就负值为 $-1$， 这样显然要是一个子段的中位数大于 $x$，那么他子段和一定大于等于 $0$，我们求一下变化后的前缀数组 $a[i]$，然后找到其中的正序对个数即可。但是我们发现我们的 $a[i]$ 数组里面有正有负，怎么办呢？

我们就需要离散化一下，然后树状数组求就可以啦！

这里注意一下 ：因为离散化之后都是正数了，当区间左端点为 $1$ 的时候，就会多算，所以要特殊处理一下。

代码：

```cpp
#include<cstdio>
#include<algorithm>
#define int long long
using namespace std;
const int MA=1000005;
int n,m,cnt=0,ans=0,a[MA],qian[MA],ag[MA];
struct zh{
	int x,nu;
}lu[MA];
bool pa(zh x,zh y){
	if(x.x!=y.x){
		return x.x<y.x;
	}
	return x.nu<y.nu;
}
void ada(int x){
	for(;x<=n;x+=x&(-x)){
		ag[x]+=1;
	}
}
int sua(int x){
	int sum=0;
	for(;x>0;x-=x&(-x)){
		sum+=ag[x];
	}
	return sum;
}
signed main()
{
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		if(a[i]>=m){
			a[i]=1;
		}
		else{
			a[i]=-1;
		}
		lu[i].x=lu[i-1].x+a[i];lu[i].nu=i;
	}
	sort(lu+1,lu+1+n,pa);
	lu[0].x=-10000;
	for(int i=1;i<=n;i++){
		if(lu[i-1].x!=lu[i].x){
			++cnt;
		}      
		if(lu[i].x>=0){
			++ans;
		}
		qian[lu[i].nu]=cnt;
	}
	for(int i=1;i<=n;i++){
		ans+=sua(qian[i]);ada(qian[i]);
	}
	printf("%lld",ans);
	return 0;
}
```



---

## 作者：Saber_Master (赞：0)

[P3031 [USACO11NOV]Above the Median G](https://www.luogu.com.cn/problem/P3031)

提起中位数，不妨先分析一下如何求区间中位数：

二分答案，设当前候选答案为$k$，那我们将所有小于$k$的值赋值为$0$，大于等于$k$的值赋值为$1$，然后最后扫一遍区间内$1$的个数，大于或等于区间长的一半则$k$大于或等于中位数，否则小于.

按照这个思路，我们先将给定序列中所有小于$x$的值赋值为$0$，大于等于$x$的值赋值为$1$，然后问题就转化为有多少个区间里$1$的个数超过或等于半区间长.

继续转化，我们先将新生成的$01$序列积一个前缀和$s$，然后区间$[l,r]$中$1$的个数就可以表示为$s_r-s_{l-1}$，这样，符合条件的区间$[l,r]$满足

$$2(s_r-s_{l-1})\geq (r-l+1)$$

再稍微变型

$$2(s_r-s_{l})\geq (r-l), (0\leq l<r\leq n)$$

$$2s_r-r \geq 2s_l-l, (0\leq l<r\leq n)$$

然后构造新序列$\{2s_x-x\}$求偏序对个数就好了

求的是二维偏序对，离散化$+$树状数组轻松完成任务.

记得把$0$算上

记得开$long \ long$

(代码也没什么放的必要了吧)


---

