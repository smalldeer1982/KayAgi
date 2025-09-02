# Ultra-QuickSort

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=20&page=show_problem&problem=1751

[PDF](https://uva.onlinejudge.org/external/108/p10810.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10810/751b373c4650fd9cb6ed8962c612343e8c3faf34.png)

## 样例 #1

### 输入

```
5
9
1
0
5
4
3
1
2
3
0```

### 输出

```
6
0```

# 题解

## 作者：AmadeusSG (赞：5)

这就是一道求**逆序对**的模板吧

为了使代码的常数不要太辣鸡，所以要用~~金坷垃~~，

呸，要用**树状数组**。

#### 首先对于树状数组，当前的理解是

```
对于一个1~n的序列，一共有n个前缀和，每个前缀的下标都有唯一的二进制分解形式

```
通过这个性质我们可以在分解前缀下标log的时间内，分解前缀加和的过程

加的时候，比如算1~10，我们知道10=2+8,先算9~10，长度为2，然后再算1~8，长度为8，分解完成，两步算出

那么递归地减小要算的前缀和，我们发现它总是对的

那么如何更新它呢，那我们就要看在统计和的过程中，要更新的位置对树状数组的哪些节点有贡献，很显然他一定对于

x-lowbit(x)进行若干次变换得到他当前的下标的值有贡献，那么它就对于cur+lowbit(cur)进行若干次迭代有贡献

直到它超过我们统计的范围N，因此范围N我们一定要知道，因此离散化使得N变小是很必要的，或者处理一些负值

 

### 如何统计逆序对呢

一种方法是，我们每插入一个数就计算插入时间在它前面但是值比他大的数有多少，很显然这是一个区间和sum(a+1,N)

另外一种方法是，按照原插入序列的倒序插入，这样我们需要检测的是时间在它后面但是值比它小的数有多少，很显然这是一个前缀和sum(a-1)


```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long
using namespace std;
const ll maxn=1000000+5;
ll n,m,ans;
ll A[maxn],C[maxn]/*Tree[]*/,D[maxn]/*离散化*/;
string s;
ll x,y;
inline ll read()
{
    ll x=0;
    char c=getchar();
    bool f=false;
    while(!isdigit(c))
	{
        if(c=='-') f=true;
        c=getchar();
    }
    while(isdigit(c))
	{
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return f?-x:x;
}
inline ll LowBit(ll k){return k&(-k);}//lowbit技术
ll Get_Sum(ll x)//求和操作
{
	ll ans=0;
	for(ll i=x;i>0;i-=LowBit(i))ans+=C[i];
	return ans;
}
inline void Update(ll x,ll d)//更新操作
{for(ll i=x;i<=n;i+=LowBit(i))C[i]+=d;}
void Discretize()
{
    sort(D+1,D+1+n);
    unique(D+1,D+1+n)-D-1;
    for(ll i=1;i<=n;i++)A[i]=lower_bound(D+1,D+1+n,A[i])-D;
}
int main()
{
	ll i,j;
	while(1)
	{
		ans=0;
		n=read();
		if(n==0)break;
		for(i=1;i<=n;i++)A[i]=read(),D[i]=A[i];
		Discretize();
		for(i=1;i<=n;i++)C[i]=0;
		for(i=n;i>=1;i--)//倒叙
		{
			Update(A[i],1);
			ans+=Get_Sum(A[i]-1);//比它小的数的个数
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：权御天下 (赞：4)

#### 在解题之前，先让我们来看一看本题会用到而萌新可能不懂的几个事项：

本题大意：对于给定的无序数组，求出经过最少多少次相邻元素的交换之后，可以使数组从小到大有序

对于逆序对的解释：两个数（a, b）的排列，若满足a > b，则称之为一个逆序对

归并排序的思想：先把每个数看成一段，然后两两合并成一个较大的有序数组，再把较大的两两合并，直到最后成为一个有序数组

归并排序复杂度：$ O(nlogn) $

#### 接下来就是我们解题的步骤了:

（P.S：听说这道题还是到数状树组的板子题，可惜本蒟蒻想了半天想不出来数状树组解法，于是就来了一发归并排序）

根据排序算法，我们知道如果相邻的两个元素满足前一个大于后一个便会交换一次，由于题目要求排序后是单调递增，所以我们可以将这道题看做求原数组逆序对的数量

举一个归并排序的例子：

假设初始数组为4 2 1 3

先把每一个数单独分成一组，即(4) (2) (1) (3)

接着两两合并，即(2 4) (1 3)

最后合成一个有序的数组，即(1 2 3 4)

不难发现，在排序过程中，若某个数向前移动了N位，则必定存在N个逆序数,如上面例子中，数字1由原先的第三位移到了第一位，前移了两位，则存在(2 1)和(4 1)两个逆序

而根据题意，我们只需要在归并排序的过程中把这个数记下来即可

接下来上一下代码（自测90ms、~~毒瘤的~~卡常与优化后60ms，算是比较快的方法）

```cpp
#include<cstdio>
using namespace std;
#define ll long long

ll ans[500010], mem[500010], anss;
int n;

void merge(int lo, int mid, int hi){
    int i = lo, e = mid + 1, k =lo;
    while(i <= mid && e <= hi){
        if(ans[i] <= ans[e])
            mem[k++] = ans[i++];
        else
            anss += e - k, mem[k++] = ans[e++];
            /*上面的ans += e - k 就是求逆序对和的过程*/
    }
    while(i <= mid)
        mem[k++] = ans[i++];
    while(e <= hi)
        mem[k++] = ans[e++];
    for(i = lo; i <= hi; ++i)
        ans[i] = mem[i];
}

void merge_sort(int x, int y){
    if(x < y){
        int mid = (x + y) / 2;
        merge_sort(x, mid);
        merge_sort(mid + 1, y);
        merge(x, mid, y);
    }
}

int main(){
    while (scanf("%d", &n) != EOF && n > 0)
    {
        anss = 0;
        for (int i = 0; i < n; ++i)
        {
            scanf("%lld", ans + i);
        }
        merge_sort(0, n - 1);
        printf("%lld\n", anss);
    }
    return 0;
}
```

---

## 作者：LB_tq (赞：2)

# Problem
给定一个数列，一次操作只能进行交换一对数。**求最少操作次数使得数列由小到大排序。**
# Solution
设数列为a。
每次交换一对数，显然要交换的a[i]与a[j]**满足a[i]>a[j]且i<j**。这样才能保证操作次数最少。

由这个条件可以联想到**逆序对**。逆序对可以使用树状数组或归并排序来求。这里重点说一下**归并排序**的方法。

考虑归并排序的实现原理：**不断合并两个有序子区间使得整个区间有序。** 那么对于一个区间的两个子区间，因为它们内部是有序的，所以**当a[i]>a[j]时，a[i~mid]都大于a[j]，相当于产生了mid-i+1对逆序对。** 那么我们可以将**ans+=mid-i+1**。

基于归并排序，可以在 **O(nlogn)** 的时间复杂度内求得一个序列的逆序对数。注意读入多组数据。
# Code
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#define ll long long
using namespace std;
const int maxn=5e5+10;
ll n,ans,a[maxn],b[maxn];
ll fr(){
	char ch=getchar();
	while(ch>'9'||ch<'0')
		ch=getchar();
	ll sum=ch-'0';
	while((ch=getchar())>='0'&&ch<='9')
		sum=(sum<<3)+(sum<<1)+ch-'0';
	return sum;
}
void msort(ll l,ll r){
	if(l==r)
		return;
	ll i,j,k,mid=(l+r)>>1;
	i=k=l;
	j=mid+1;
	msort(l,mid);
	msort(mid+1,r);
	while(i<=mid&&j<=r){
		if(a[i]<=a[j])
			b[k++]=a[i++];
		else{
			b[k++]=a[j++];
			ans+=mid-i+1;
		}
	}
	while(i<=mid)
		b[k++]=a[i++];
	while(j<=r)
		b[k++]=a[j++];
	for(int h=l;h<=r;h++)
		a[h]=b[h];
}
int main(){
	while(1){
		n=fr();
		if(!n)
			break;
		for(int i=1;i<=n;i++)
			a[i]=fr();
		ans=0;
		msort(1,n);
		printf("%lld\n",ans);
	}
	return 0;
}
```


---

## 作者：hkr04 (赞：2)

求逆序对，用归并排序或者树状数组什么的都可以。代码网上有很多，个人码风不太一样，我的代码仅供参考。  

**我主要想说说为什么只能交换相邻两个数来构成有序数列的交换次数为逆序对数量**

假设有序数列的排列为$\{1,2,3,4,...,n-1,n\}$（这里的数字为从小到大的排名，最小为1，因为有序所以排名与下标相同）  
那么给出的序列可能是$\{2,4,1,n-1,n,...,3\}$  
我们可以假设我们从大到小把这些数一个个地归位

因为n是最大的，现在n所处的位置下标为[4]，目标位下标是[n]，那么它需要换n-4次才能到达目标位，由于n是最大的，所以n前所有数不和它构成逆序对，n后所有数和它构成逆序对（这里指的是初始给出的无序序列）

当我们把n归位后，得到的序列就是$\{2,4,1,n-1,...3,n\}$  
这时我们可以发现，将n归位后不需要去管它了，应该要将剩下的n-1个数依次归位，且n归位没有影响到小于n的数的逆序对个数。依次类推，排名为i的数要回到下标为i的位置的代价为i的逆序对，所以综上所述，总代价为总的逆序对。

贴代码，我用的是归并排序：（注意题目有多组输入）
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
const int size=500010;
long long num[size],ans=0;
void merge(int l,int mid,int r)
{
	int len_L=mid-l+1;//存下左右区间的长度
	int len_R=r-(mid+1)+1;
	int L[size],R[size];
	for (int i=1;i<=len_L;i++)
	L[i]=num[l+i-1];//复制左边区间
	for (int i=1;i<=len_R;i++)
	R[i]=num[mid+i];//复制右边区间
	for (int i=1,j=1,k=l;k<=r;k++)//从区间开始点开始扫描
    {
		if (i>len_L)num[k]=R[j++];
		else if (j>len_R)num[k]=L[i++];
		else
        {
			if (L[i]<=R[j])
			num[k]=L[i++];//如果左区间小于等于直接放回去
			else//存在逆序对，更新区间的同时顺便更新逆序对个数
            {
				ans+=len_L-i+1;//L[i]~L[len_l]都大于r[j]，所以存在这么多逆序对
				num[k]=R[j++];
			}
	    }
    }
}
void merge_sort(int l,int r)//将序列分成一个个小区间来排序
{
	if (l<r)
    {
	int mid=(l+r)/2;
	merge_sort(l,mid);//直到分到区间为[i,i]，只有一个元素的区间本身有序
	merge_sort(mid+1,r);
	merge(l,mid,r);//合并两个有序区间成为一个大的有序区间（左右区间有序不影响大区间内逆序对个数，可以自己在草稿纸上试一下或者感性理解一下）
	}
}
int main()
{
	int n[size];
	int i=0;
    while (cin>>n[i]&&n[i]!=0)
    {
	for (int j=1;j<=n[i];j++)cin>>num[j];
	merge_sort(1,n[i]);
	cout<<ans<<endl;
	i++;
	ans=0;
    }
	return 0;
}
```

---

## 作者：Wall_breaker (赞：1)

~~我惊奇地发现这一道题目没有翻译~~

不知道大家题目有没有看懂，下面看一下我的翻译（大概意思）：

在本问题中，你需要给一个共有n个整数的序列排序（从小到大），现在我们只允许用比较和交换相邻的两个数字两种操作，问最少几步交换后可以是序列从小到大有序排列？


------------

乍一看，欸，这不是冒牌排序的板子题吗？（~~蓝题怎么可能这么水~~）

然而这里的意思是说：用冒泡排序最少几步完成排序。所以这里并不是要我们编一个冒泡排序。（~~n * n的复杂度完美超时~~）

我们是怎么冒泡排序的呢？在排序中，我们只要找到有一对顺序相反的数对，就要交换一次。因此，我们只需要统计逆序对的个数就行了。

## 关键问题来了：怎么求逆序对？——归并排序

归并排序就是把1~n的序列分割成1~n/2与n/2+1~n两段序列，然后分别排序，最后合并，运用了递归思想。不过，无论某个数在哪一个区间，最终它都会和别的区间的数进行比较，因此就能很快求出逆序对的个数。
```
inline void q_merge(int l, int r) {
	if (l == r) return;
	int mid = l + r >> 1;
	q_merge(l, mid);
	q_merge(mid + 1, r);
	int i = l, j = mid + 1, k = l;
	while(i <= mid || j <= r) {
		if (j > r || i <= mid && a[i] <= a[j]) b[k ++] = a[i ++];
		else {
			b[k ++] = a[j ++];
			ans += mid - i + 1;说明第j个数小于第i个数且j>i，由于i~mid从小到大，则它们都是逆序对。
		} 
	}
	for (int i = l; i <= r; i ++) a[i] = b[i];
	return;
}
```

所以，我们就做完了。
上代码：

```
#include<bits/stdc++.h>
using namespace std;
template <typename T>
inline void read(T &x) {
	x = 0;
	T f = 1;
	char c = getchar();
	for (; !isdigit(c); c = getchar()) if (c == '-') f = -1;
	for (; isdigit(c); c = getchar()) x = (x << 1) + (x << 3) + (c ^ 48);
	x *= f;
}
inline void d_read(double &x) {
	x = 0.0;
	int f = 1;
	char c = getchar();
	for (; !isdigit(c); c = getchar()) if (c == '-') f = -1;
	for (; isdigit(c); c = getchar()) x = x * 10 + (c ^ 48);
	if (c == '.'){
		double num = 1.0;
		c = getchar();
		for (; isdigit(c); c = getchar()) x = x + (num /= 10) * (c ^ 48);
	}
	x *= f;
}

template <typename T>
inline void w(T x) {
	if (x > 9) w(x / 10);
	putchar(x % 10 + 48);
}
template <typename T>
inline void write(T x, char c) {
	if (x < 0){
		putchar('-');
		x = -x;
	}
	w(x);
	putchar(c);
}
long long ans = 0;
int a[500005], b[500005];
inline void q_merge(int l, int r) {
	if (l == r) return;
	int mid = l + r >> 1;
	q_merge(l, mid);
	q_merge(mid + 1, r);
	int i = l, j = mid + 1, k = l;
	while(i <= mid || j <= r) {
		if (j > r || i <= mid && a[i] <= a[j]) b[k ++] = a[i ++];
		else {
			b[k ++] = a[j ++];
			ans += mid - i + 1;
		} 
	}
	for (int i = l; i <= r; i ++) a[i] = b[i];
	return;
}
int main(){
	int n;
	read(n);
	while(n) {
		for (int i = 1; i <= n; i ++) {
			read(a[i]);	
		}
		ans = 0;
		q_merge(1, n);
		write(ans, '\n');
		read(n);
	}
	return 0;
}
```

---

## 作者：Xx_queue (赞：1)

题面说是冒泡排序，实际上这道题目与冒泡排序并没有很大的关系……

#### 深入理解这道题目，发现其实就是求**逆序对**的题呃~~

下面我给出树状数组求解逆序对的模板：（没有离散化，大佬勿喷）

```cpp
//逆序对——树状数组解法 
#include <bits/stdc++.h>
#define MAX 2000000+5
using namespace std;
int n,a[MAX],c[MAX],Max;//a是普通的数组，c是树状数组 
int lowbit(int x)//lowbit函数 （求二进制最后一位1） 
{
	return x&(-x);
}
void add(int x,int k)//单点修改 （增加） 
{
	for(int i=x; i<=Max; i+=lowbit(i))c[i]+=k;
}
long long getsum(int x)//区间查询求前缀和 
{
	long long ans=0;
	for(int i=x; i>0; i-=lowbit(i))ans+=c[i];
	return ans;
}
int main()
{
	while(1)
	{
		memset(a,0,sizeof(a));
		memset(c,0,sizeof(c));
		scanf("%d",&n);
		if(n==0) break;
		for(int i=1; i<=n; i++)
		{
			scanf("%d",&a[i]);
			a[i]++;
			Max=max(Max,a[i]);
		}
		long long sum=0;
		for(int i=n; i>=1; i--)//倒序扫描，通过树状数组查询每个数后面有多少个数比他小
		//这样就可以满足i<j&&a[i]>a[j] 
		{
			sum+=getsum(a[i]-1);
			add(a[i],1);
		}
		printf("%lld\n",sum);
	}
	return 0;
}
```


---

## 作者：Kaizyn (赞：1)

求 **逆序对** ，用 **归并排序** 。不解释啦
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int Maxn = 5e5 + 7;

int n;
long long ans;
int a[Maxn], tmp[Maxn];

void merge_sort(int l, int r) // [L, R)
{
    if(r - l <= 1) return;
    int mid = (l + r) >> 1;
    merge_sort(l,mid); // [L, Mid)
    merge_sort(mid,r); // [Mid, R)

    int i = l, j = mid, pos = l;
    while(pos < r)
    {
        if(i >= mid || j < r && a[j] < a[i] )
        {
            tmp[pos++] = a[j++];
            ans += mid - i;
        }
        else tmp[pos++] = a[i++];
    }
    memcpy(a+l,tmp+l,sizeof(int)*(r-l));
    // for(int k = l; k < r; ++k) a[k] = tmp[k];
}

int main()
{
    while( scanf("%d",&n) && n !=0 )
    {
        for(register int i = 0; i < n; ++ i) scanf("%d",a+i);
        ans = 0;
        merge_sort(0,n);
        printf("%lld\n",ans);
    }
    return 0;
}
```

---

## 作者：洛璟 (赞：0)

本蒟蒻昨晚刚刚学习了归并，这也是蒟蒻的第一篇题解。

这一题，说白了就是求一个数组中逆序对的个数，有人觉得：冒泡排序可以做欸……再一看：n≤500000……

所以，蒟蒻介绍一种的方法：

## 归并排序

归并排序是一种稳定的、高效的排序方法，您只需要用O（n log n）的时间就能排好序 ~~（这不跟sort一样吗，用归并干嘛）~~

但是呢，~~还有人记得手打快排吗~~快排怎么求逆序对呢？所以这就是归并的好处了。

归并排序的原理：通过使部分有序，从而达到全体有序，就是用分治法，不断地分为左右两边，分到仅剩一个时，就有序了~~一个数怎么可能是无序的呢？~~（和二分有点像）。代码如下：

```cpp
void mergesort(long long l,long long r)//归并初始化 
{
	if(l<r)
	{
		long long mid=(l+r)>>1;
		mergesort(l,mid);
		mergesort(mid+1,r);
		mergesortdl(l,mid,mid+1,r);//归并合并
	}
}
```
（由于这个题目的需求，我就开了long long）

最后分完后将各个有序的子序列合并起来就好啦

那么子序列之间的合并可以看代码，思路非常简单QWQ

重点来了：那要怎么求逆序对的个数呢？

所谓逆序对，就是一个数组a中有俩数字a[i]>a[j],但是他们的下标i<j。

那么在归并排序合并后一段与前一段的过程中，两段会进行比较，由于这两段都是有序的，所以只需和另一段中没被排序过的最前一个数比较即可。这时，如果后一段的这个数比前面的第l1个数小，那么这个数组中关于这个数的逆序对就有(假设第一段最后一个数下标为r1）:r1-l1+1个。

为什么呢？
前面已经说了，每一段都是有序的，那么若后面一段中任意一个点比前面一段任意一点小，那么前面一段的那个点之后的点一定大于后面一段那个点。

那么废话不多说，~~上菜：~~
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,ans;
long long a[1000010],b[1000010];
inline long long read()//快读 
{
	long long x=0,f=1;
	char c=getchar();
	while(c<'0'|| c>'9')
	{
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0' && c<='9')
	{
		x=(x<<1)+(x<<3)+(c^48);
		c=getchar();
	}
	return x*f;
}
void mergesortdl(long long l1,long long r1,long long l2,long long r2)//归并排序合并，l1为前一段起点，r1第一段终点，l2、r2同理，只不过是第二段的
{
	long long tot=0;
	while(l1<=r1 && l2<=r2)//当每一段左右两点没重合时
	{
		if(a[l1]<=a[l2])//进行比较，小的在前
			b[++tot]=a[l1++];
		else
		{
			b[++tot]=a[l2++];
			ans+=r1-l1+1;//归并排序加上这一句话就成了求逆序对的程序
		}

	}
	while(l1<=r1) b[++tot]=a[l1++];//把剩下的放进去
	while(l2<=r2) b[++tot]=a[l2++];//同上，但两个只会执行一次
	for(long long i=tot,j=r2; i>=1; i--,j--)//放到原数组里
	{
		a[j]=b[i];
	}

}
void mergesort(long long l,long long r)//归并初始化 
{
	if(l<r)//不断递归，到仅剩一个
	{
		long long mid=(l+r)>>1;
		mergesort(l,mid);
		mergesort(mid+1,r);
		mergesortdl(l,mid,mid+1,r);//开始合并
	}
}
int main()
{
	while(1)
	{	
		ans=0;
		n=read();
		if(n==0) return 0;
		for(long long i=1; i<=n; i++)
		{
			a[i]=read();
		}
		mergesort(1,n);
		printf("%lld\n",ans);
	}

	return 0;
}
```
~~由于本蒟蒻不会树状数组，所以就只能用归并了~~
蒟蒻第一次写题解，难免有错误，谢谢指正。


---

## 作者：亦笙箫 (赞：0)

## 简化题目
题目就是让我们求每组数据的逆序对。


所以，我们可以用冒泡排序直接暴力求。

但题目的数据范围是$n<=500,000$

冒泡排序时间为$O(n^2)$

所以我们要换方法--->

# 一：归并排序

用归并排序求逆序对是很快的

因为归并排序时每块里面的数都是有序的

所以我们可以以$O(nlogn)$的时间求出所有逆序对。

而且我们只需要在归并排序里面加一条语句即可

附上关键代码：

```cpp
int GuiBing_sort_NXD ( int l, int r, ll *a, ll *rr, ll &tot )
{
    long long mid, i, j, k ;
    if ( l == r )
        return 0;
    mid = ( l + r ) / 2 ;
    GuiBing_sort_NXD( l, mid, a, rr, tot ) ;
    GuiBing_sort_NXD( mid + 1, r, a, rr, tot ) ;
    i = l ;
    j = mid + 1 ;
    k = l ;
    while ( i <= mid && j <= r )
    {
        if( a[ i ] <= a[ j ] )
            rr[ k ++ ] = a[ i ++ ] ;
        else
        {
            tot += mid - i + 1 ;//重点
            rr[ k ++ ] = a[ j ++ ] ;
        }
    }
    while ( i <= mid )
        rr[ k ++ ] = a[ i ++ ] ;
    while ( j <= r )
        rr[ k ++ ] = a[ j ++ ] ;
    for ( int i = l ; i <= r ; i ++ )
        a[ i ] = rr[ i ] ;
    return 0;
}
```

# 二：线段树

线段树的过程其实就是用区间加法减少时间

先读入，记录下标$index_i$，$sort$一下，在从$[1-index_i)$统计即可

$index_i$计算过后把这个数删掉，其实就是把这个数加上$-1$或变为$0$

### 总结一下就是一个*单点修改，区间查询的线段树*

附上线段树代码：

```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>

using namespace std;

#define int long long
#define P pair<int,int>

const int MAXX = 500000;

struct node
{
    int l,r,w;
}tree[MAXX*4+5];

int n;
int x,y;
int ans,Ans;
P a[MAXX+5];

void build(int l,int r,int k)
{
    tree[k].l=l;tree[k].r=r;
    if(l==r)
    {
        tree[k].w=1;
        return ;
    }
    int m=(l+r)/2;
    build(l,m,k*2);
    build(m+1,r,k*2+1);
    tree[k].w=tree[k*2].w+tree[k*2+1].w;
}

void add(int k)
{
    if(tree[k].l==tree[k].r)
    {
        tree[k].w+=y;
        return;
    }
    int m=(tree[k].l+tree[k].r)/2;
    if(x<=m) add(k*2);
    else add(k*2+1);
    tree[k].w=tree[k*2].w+tree[k*2+1].w;
}

void sum(int k)
{
    if(tree[k].l>=x&&tree[k].r<=y)
    {
        ans+=tree[k].w;
        return;
    }
    int m=(tree[k].l+tree[k].r)/2;
    if(x<=m) sum(k*2);
    if(y>m) sum(k*2+1);
}

signed main()
{
    while(scanf("%lld",&n)&&n)
    {
    	memset(a,0,sizeof(a));Ans=0;
    	for(int i=1;i<=n;i++)
            scanf("%lld",&a[i].first),a[i].second=i;
        sort(a+1,a+1+n);
        build(1,n,1);
        for(int i=1;i<=n;i++)
        {
            ans=0,x=1,y=a[i].second-1,sum(1);
            Ans+=ans,x=y,y=-1,add(1);
        }
        printf("%lld\n",Ans);
    }
    return 0;
}
```


***********
实际上树状数组也能做

但我比较~~菜鸡~~没有那么多时间，所以就没有打

请见谅QAQ


---

## 作者：hovny (赞：0)

## [题面](https://www.luogu.org/problemnew/show/UVA10810#sub)

~~看不懂？！~~  

#### 大概的意思就是：  

给出一个长度为n的序列，然后每次只能交换相邻的两个数，问最小需要几次使序列**严格上升 ** 

不断读入n，直到n=0结束  

## 思路：  

交换相邻的两个数，这不就类似冒泡排序吗？但是**n<500000**  

~~算了吧，我回去颓A+B~~ 

于是我们就发现用**冒泡排序**直接**计算次数**是行不通的  

但我们要知道：  

冒泡排序的**交换次数**就是序列的**逆序对数**！！！  

所以——~~就简单了吧~~~  

### 如何求逆序对？

[较easy版的逆序对](https://www.luogu.org/problemnew/show/P1908)  

1、归并排序  

思想是分治法  

不断划分为两小段  

然后依次由小序列合并为大序列，同时求出逆序数

2、树状数组

因为树状数组的修改查询是log级的所以可以使用（前缀和的方法），没学的建议先去学习一下，不是很难

Code：

```c++
#include<bits/stdc++.h>
#define ll long long
using namespace std;
struct node{
	int x,i;
}a[500010];
int n;
int b[500010];
int f[500010];
ll ans;
int read()
{
	int s=0;
	char c=getchar();
	while(!isdigit(c))
		c=getchar();
	while(isdigit(c))
	{
		s=(s<<1)+(s<<3)+c-'0';
		c=getchar();
	}
	return s;
}
void update(int x)//修改
{
	for(;x<=n;x+=x&(-x))
		f[x]++;
	return;
}
ll sum(int x)//求前缀和
{
	ll res=0;
	for(;x;x-=x&(-x))
		res+=f[x];
	return res;
}
bool cmp(node a,node b)
{
	return a.x>b.x;
}
int main()
{
	int i,j;
	n=read();
	while(n)
	{
		ans=0;
		memset(f,0,sizeof(f));
		for(i=1;i<=n;i++)
		{
			a[i].x=read();
			a[i].i=i;
		}
		sort(a+1,a+n+1,cmp);
		for(i=1;i<=n;i++)//先hash一下,按数值给其标记，方便后面求逆序对
			b[a[i].i]=i;
		for(i=1;i<=n;i++)
		{
			update(b[i]);//一步一做
			ans+=sum(b[i]-1);
		}
		printf("%lld\n",ans);
		n=read();
	}
	return 0;
}
```



---

