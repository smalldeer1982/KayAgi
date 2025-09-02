# CODESPTB - Insertion Sort

## 题目描述

给定一个长度为 $n$ 的序列，求使其交换至有序（从小到大）的最少交换次数（逆序对）

## 说明/提示

$1 \le T \le 5$，$1 \le n \le {10}^5$，$1 \le a_i \le {10}^6$。

## 样例 #1

### 输入

```
2
5
1 1 1 2 2
5
2 1 3 1 2
```

### 输出

```
0
4
```

# 题解

## 作者：Pethly_Cat (赞：8)

在肝掉这题之间，了解**归并排序**是必不可少的了。

那么，什么是归并排序？

归并排序是利用**二分法**来实现的一种排序算法，主要是将一组数平均分开到不能分的时候，在合并过程中进行排序的一种排序算法。它的时间复杂度为$O(n\ log\ n)$。

下面一张图证明了一切（图片来自网络）：

![](https://cdn.luogu.com.cn/upload/image_hosting/tdwnbw5c.png)

那么，究竟怎样才能把两个序列合并呢？

通过图片可以发现，每次合并两个序列时，它们**本身**都是排好序的。那么合并序列中最小的数一定是两个序列的第一个数较小的那个，第二个数就是剩下的数中最小的······以此类推。

那么，我们就可以艰（yu）难（kuai）地打出代码了：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[500001],c[500001];
long long sum;
void msort(int x,int y)
{
    if(x==y) return;//不用排序的情况
    int mid=(x+y)/2,i=x,j=mid+1,k=x;
    msort(x,mid);//二分
    msort(mid+1,y);
    while(i<=mid&&j<=y){
    	if(a[i]<=a[j]) c[k++]=a[i++];
        else c[k++]=a[j++],sum+=mid-i+1;//求逆序对最关键的一步
	}
    while(i<=mid)//合并序列
    c[k++]=a[i++];
    while(j<=y)
    c[k++]=a[j++];
    for(int l=x;l<=y;l++)//存回原来的数组
    a[l]=c[l];
} 
int main()
{
	cin>>t;
	for(int i=1;i<=t;i++){
		cin>>n;
    	for(int j=1;j<=n;j++)
    	cin>>a[j];
    	memset(c,0,sizeof(c));//一定要清零！一定要清零！！一定要清零！！！（重要的事情说三遍）
    	sum=0;
    	msort(1,n);
    	cout<<sum<<endl;
	}
    return 0;
}
```

只求两字：

### 过和赞

---

## 作者：IzumiSagiri (赞：3)

简要分析下题意，发现这就是个可以交换任意两个数的排序最少交换次数问题，即为逆序对

于是我就跑了个归并排序求逆序对

代码如下：

```c++
#include<cstdio>
int a[100005];//原数组
int t[100005];//辅助数组
long long s;
void gb(int l,int r) {//归并排序
    if(l==r) {
        return;
    }
    int mid=(l+r)>>1;
    int i;
    gb(l,mid);
    gb(mid+1,r);
    int t1=l,t2=mid+1;
    int top=0;
    while(t1<=mid&&t2<=r) {
        if(a[t1]<=a[t2]) {
            t[++top]=a[t1++];
        } else {
            s+=mid+1-t1;//求逆序对关键步骤
            t[++top]=a[t2++];
        }
    }
    while(t1<=mid) {
        t[++top]=a[t1++];
    }
    while(t2<=r) {
        t[++top]=a[t2++];
    }
    for(i=1; i<=top; i++) {
        a[l+i-1]=t[i];
    }
    return;
}
int main() {
    int t;
    scanf("%d",&t);
    while(t--) {
        s=0;//注意这里要清零，之前就忘了清零
        int n;
        scanf("%d",&n);
        int i;
        for(i=1; i<=n; i++) {
            scanf("%d",&a[i]);
        }
        gb(1,n);
        printf("%lld\n",s);
    }
    return 0;
}
```

---

## 作者：傅思维666 (赞：2)


## 题解

一道求逆序对的题目。

求逆序对是一个问题，对于这个问题，一般来讲有两种求解方法。博客食用口味更佳：

[求逆序对的两种方法](https://www.cnblogs.com/fusiwei/p/11656303.html)



## 逆序对的概念

先放一波啥是逆序对...

对于一个数列$a$，假如$a[i]>a[j]$并且$i<j$，那么这个$a[i],a[j]$就叫做这个数列的一个逆序对。

简单理解一下：假如本来这个数列是单调递增的，突然出来了一对不和谐的，它非要皮一下，两个数调换一下位置。那么这个不和谐的数对就叫做逆序对。

---



## 归并排序求逆序对

归并排序是求逆序对的一个常见并好用的手段。

如果又小可爱不太了解归并排序，那么请翻阅我的这篇博客：

[归并排序详解](https://www.cnblogs.com/fusiwei/p/11656294.html)

~~其实这篇博客已经讲了咋用归并排序求逆序对...就是我下面讲的那些（Ctrl CV大法）~~

首先来放结论：如果在归并排序过程中，出现$a[i]>a[j]$，那么就会产生$mid-i+1$个逆序对。

很奇妙吧？下面来讲证明：

因为我们做归并排序是用到了分治的思想，最后的操作其实就是递归回溯，从小到大地合并，所以这个时候，我们的两个子序列（即$l-mid$，$mid+1-r$其实都是已经排好序的），这个时候，出现了一个不和谐的$a[i]$，说明从这个数一直到$a[mid]$的所有数都是不和谐的。我们直接累加就好。

代码只需要在模板归并排序的基础上再加一行即可：（已经用$Attention$标明）

```cpp
void merge_sort(int l,int r)
{
    if(l==r)
        return;
    int mid=(l+r)>>1;
    merge_sort(l,mid);
    merge_sort(mid+1,r);
    int i=l,j=mid+1,k=l;
    while(i<=mid && j<=r)
    {
        if(a[i]<=a[j]) 
            b[k++]=a[i++];
        else
        {
            b[k++]=a[j++];
            ans+=mid-i+1;//Attention
        }
    }
    while(i<=mid)
        b[k++]=a[i++];
    while(j<=r)
        b[k++]=a[j++];
    for(int p=l;p<=r;p++)
        a[p]=b[p],b[p]=0;
}
```

---



## 树状数组求逆序对

使用树状数组求逆序对的想法可能更加的抽象一些。

关于树状数组，如果有需要补习的小伙伴，推荐自己的这篇博客：

[树状数组知识点详解](https://www.cnblogs.com/fusiwei/p/11275978.html)

首先，我们需要明白，为什么逆序对可以使用树状数组来求：其实，根据逆序对的定义，我们会发现：其实求解逆序对的过程就是在找一个序列中，在一个数的前面有多少比它大的数。那么，这种区间统计的题，完全可以使用树状数组这种数据结构来解决。

树状数组的功能就是单点修改，区间查询。那么，我们开一个树状数组

（注意：这里的数据可能需要进行离散化，当数据量过大的时候，需要把区间大小离散成元素数量，如有离散化不明白的小伙伴，可以看我的这篇博客：）

[浅谈离散化](https://www.cnblogs.com/fusiwei/p/11622517.html)

这个树状数组表示的是**在当前元素前且比当前元素大的元素个数**。我们从头开始扫，每碰到一个数，就用树状数组的修改操作向上修改，加1。我们查询的时候就可以知道有多少个数比它大，然后用现在已经插入的元素个数减去查询的数量（包括它自己），就可以得出当前逆序对的个数。

模板大致如下：（[JDOJ 1927 求逆序对](https://www.cnblogs.com/fusiwei/p/11281266.html)）

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int c[500010],rk[500010],n;
long long ans; 
struct point
{
    int num,val;
}a[500010];
inline bool cmp(point q,point w)
{
    if(q.val==w.val)
        return q.num<w.num;
    return q.val<w.val;
}
inline void fix(int p,int d)
{
    for(;p<=n;p+=p&-p)
        c[p]+=d; 
}
inline int getsum(int x)
{
    int sum=0;
    for(;x;x-=x&-x)
        sum+=c[x];
    return sum;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i].val),a[i].num=i;
    sort(a+1,a+1+n,cmp);
    for(int i=1;i<=n;i++)
        rk[a[i].num]=i;
    for(int i=1;i<=n;i++)
    {
        fix(rk[i],1);
        ans+=i-getsum(rk[i]);
    }
    printf("%lld",ans);
    return 0;
}
```



最后在放一波AC代码：（归并排序求法）

```cpp
#include<cstdio>
using namespace std;
const int maxn=1e5+1;
int a[maxn],b[maxn],n,ans;
void merge_sort(int l,int r)
{
    if(l==r)
        return;
    int mid=(l+r)>>1;
    merge_sort(l,mid);
    merge_sort(mid+1,r);
    int i=l,j=mid+1,k=l;
    while(i<=mid && j<=r)
    {
        if(a[i]<=a[j])
            b[k++]=a[i++];
        else
        {
            b[k++]=a[j++];
            ans+=mid-i+1;
        }
    }
    while(i<=mid)
        b[k++]=a[i++];
    while(j<=r)
        b[k++]=a[j++];
    for(int p=l;p<=r;p++)
        a[p]=b[p],b[p]=0;
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--)
    {
        ans=0;
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        merge_sort(1,n);
        printf("%d\n",ans);
    }
    return 0;
}
```


---

## 作者：⚡LZSY01_XZY⚡ (赞：2)

# 解：由题意可得：
$$\color{red}\text{求N个数的逆序对}$$
***
# 进入正题

众所周知，求逆序对一般有两种方法：

    1.  归并排序
    2.  树状数组

## 1. 归并排序
归并排序分为分解、合并两个过程，如图：
![](https://cdn.luogu.com.cn/upload/pic/54788.png )
$$\tiny\text{(向luogu图床致敬)~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~}$$

这个题目，我们在合并过程中处理就可以了：

### code：
```
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;
int n,a[200005],b[200005];
long long ans=0;

void sort(int l,int r)
{
	int mid,i,j,k;
	if(l<r)
	{
		mid=(l+r)/2;
		i=l;j=mid+1;k=l;
		sort(l,mid);sort(mid+1,r);
		while((i<=mid) || (j<=r))
		{
			if((i<=mid) && ((j>r) || (a[i]<=a[j])))
			{
				b[k]=a[i];
				ans=ans+j-mid-1;
				i++;
			}
			else 
			{
				b[k]=a[j];
				j++;
			}
			k++;
		}
		for(int i=l;i<=r;i++)a[i]=b[i];
	}
	return ;
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	sort(1,n);
	printf("%lld\n",ans);
	return 0;
}
```

## 2. 树状数组
树状数组在处理单点修改，区间查询时时间复杂度都是$O(logn)$,那么总的时间复杂度为$O(mlogn)$，其中$m$为操作次数，那么这题用树状数组时间复杂度为$O(nlogn)$，效率不错。

树状数组：
![](https://cdn.luogu.com.cn/upload/pic/54793.png )

### code:
```
#include <cstdio>
#include <cstring>
using namespace std;

int read()
{
	int x=0,f=1;char c=getchar();
	while (c<'0' || c>'9'){if (c=='-')f=-1;c=getchar();}
	while (c>='0'&&c<='9'){x=(x<<1)+(x<<3)+c-48;c=getchar();}
	return x*f;
}

const int MAXN=100000000;
int n,k,max;long long ans;
int tree[MAXN];

inline long long sum(int k)
{
	long long res=0;
	for (int i=k;i<=max;i+=(i&-i))res+=tree[i];
	return res;
}

inline void updata(int k)
{
	for (int i=k;i>0;i-=(i&-i))tree[i]++;
	return ;
}

int main()
{
	int cas;cas=read();
	while (cas--)
	{
		n=read();ans=0;
		memset(tree,0,sizeof(tree));
		for (int i=1;i<=n;i++)
		{
			k=read();
			ans+=sum(k+1);
			updata(k);
			if (k>max)max=k;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```
# 后记
这题没有给定数据范围，让我$WA$了一次，还是有点坑的。对于树状数组解题还要注意的是，当$a_i$的值过大，还要使用离散化。

~~点个赞吧~~

---

## 作者：Mono_pigsicklie (赞：2)



------------
###### ~~终于可以臭不要脸的说一句了，这道题的提交基本都是我的，~~
------------

##### 太惨了，要么听取WA声一片，要么眼见TLE满屏。


#### 言归正传：


### 这题可以用归并排序直接来做，因为求逆序对只需要在归并排序上加一步就好啦，不过这一步也是很重要的呢！！

一定要注意，代码会附上注释，帮助理解归并排序。

上代码：（纯本人自己做出，如有雷同，纯属巧合）
```cpp
#include<bits/stdc++.h>
using namespace std;
int k,n,ans=0;
int a[500100],b[500100];//a原数组，b暂存数组 
void merge_sort(int l,int r) {//归并 
	if(l==r)return ;//一个数不用排
	int m=(l+r)>>1;
	merge_sort(l,m);//排序左边 
	merge_sort(m+1,r);//排序右边 
	int i=l,j=m+1,k=0;//i左边最小位置，j右边最小位置
	while(i<=m&&j<=r)
		if(a[i]<=a[j])b[++k]=a[i++];
		else ans+=m-i+1,b[++k]=a[j++];//加入右半段时，逆序对数增加
	while(i<=m)b[++k]=a[i++];//加入左边剩余的数
	while(j<=r)b[++k]=a[j++];//加入右边剩余的数
	for(i=1; i<=k; i++)a[l+i-1]=b[i];//从暂存数组中赋值 
}
int main() {
	scanf("%d",&k);
	for(int i=1; i<=k; i++) {
		ans=0;
		scanf("%d",&n);
		for(int i=1; i<=n; i++)
			scanf("%d",&a[i]);
		merge_sort(1,n);
		printf("%d\n",ans);
	}
	return 0;
}
```

未做任何防抄袭处理，只为帮助别人更好理解归并。

另外，考场上使用归并是较为稳定的排序。


---

## 作者：xxzjbd (赞：1)

## 一道归并排序模板题
简单介绍一下何谓归并排序

归并排序是**利用二分思想对数组进行排序**，使之变成升序或降序。二分的目的是将大区间不断变为小区间，显然当每个小区间都有序时，合并出的大区间一定有序。具体实现过程需要另一暂存数组，每次小区间判断完后利用暂存数组更新原数组的顺序，再进入下一次排序。

比起方便的快排，归并排序不会被特殊构造数据卡掉，且可以方便求出**交换次数最小类题目**，如此题，输出将序列变为升序的最小操作次数，也就是逆序对。

记录逆序对只需在二分过程中，若位置靠前的数大于位置靠后的数，那么交换两数，把答案加上两数的位置差即为操作次数。
## 代码如下
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int maxn=500010;
int a[maxn],c[maxn],n;
long long ans;
void msort(int l,int r){
	if(l==r) return ;
	int mid=(l+r)/2;
	msort(l,mid);
	msort(mid+1,r);
	int i=l,j=mid+1,k=l;
	while(i<=mid&&j<=r){
		if(a[i]>a[j]){
			ans+=mid-i+1;
			c[k++]=a[j++];
		}
		else
			c[k++]=a[i++];
	}
	while(i<=mid)c[k++]=a[i++];
	while(j<=r) c[k++]=a[j++];
	for(int i=l;i<=r;i++){
		a[i]=c[i];
	}
}
int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		memset(c,0,sizeof(c));
		memset(a,0,sizeof(a));
		ans=0;
		int n;
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
		}
		msort(1,n);
		printf("%lld\n",ans);
	}
}
```
## 谢谢观赏

---

## 作者：skysoft (赞：1)

本蒟蒻的第一篇题解（pascal写的)，写的不太好，大佬勿喷。
# 进入正题
这道题就是彻彻底底的逆序对，用两重循环先做一下
```pascal
for i:=1 to n-1 do
for j:=i+1 to n do 
if a[i]>a[j] then inc(s);
```
一片TLE，然后换神奇的归并排序
```pascal
var n,m,i,j:longint;

s:int64;

a,b:array[0..1000000] of longint;

procedure merge(l,r:longint);{归并排序}

var mid,i,j,k:longint;

 begin
    {接下来进行拆分}
        if l=r then exit;

        mid:=(l+r) div 2;

        merge(l,mid);

        merge(mid+1,r);  
        {开始做}

        i:=l;

	j:=mid+1;

	k:=l-1;{进行排序}

        while (i<=mid)and(j<=r) do

         begin

		while (a[i]<=a[j])and(i<=mid) do

                	begin

                        	inc(k);

                        	b[k]:=a[i];

                        	if j<=r then s:=s+j-mid-1;
                            {核心公式，开始操作}

                        	inc(i);

                	end;

                while (a[i]>a[j])and(j<=r) do

                	begin

                        	inc(k);

                        	b[k]:=a[j];

                        	inc(j);

                	end;

         end;
       {开始合并}
        while i<=mid do

         begin

                	inc(k);

                	b[k]:=a[i];

                	s:=s+j-mid-1;
                   {继续操作}
                	inc(i);

         end;

         for i:=l to j-1 do a[i]:=b[i];  {合并序列}

end;

begin	

        readln(m);

        for i:=1 to m do 

        begin

        s:=0;

        readln(n);

        for j:=1 to n do read(a[j]);

        merge(1,n);

        writeln(s);

        end;

end.
```
奇迹般的AC了这道题。

---

## 作者：fjy666 (赞：0)

## 0x01 思路
经典的[**求逆序对**](https://baike.baidu.com/item/%E9%80%86%E5%BA%8F%E5%AF%B9/11035554?fr=aladdin)问题。


题目翻译中已经写明逆序对了。


我们都知道归并排序，可以考虑怎么把归并排序的思路应用到求逆序对上。  
在归并排序中，先将左子序列排序，再将右子序列排序，最后合并。  
那么，假设归并排序时已经求出左子序列和右子序列的逆序对个数之和，那么我们只要统计 **横跨** 左右子序列的逆序对个数即可。  
很简单：每当有一个右子序列的数被放到辅助数组中时，左子序列的剩下所有数 **都比这个数大** ，直接统计即可。  
这样可以保证：
- 不重  
每个逆序对 $(a_i,a_j)$ 只会被 $a_j$ 统计一次。
- 不漏  
每个逆序对 $(a_i,a_j)$ 肯定被 $a_j$ 统计。

时间复杂度：$\Theta(n\log n)$，和归并排序的复杂度相同。  
关于代码：我虽然不能在 SPOJ 上提交，但逆序对的正确性在其他求逆序对的题目上验证过。
## 0x02 代码
```cpp
#include <cstdio>
#define _rep(i_,a_,b_) for(int i_ = a_;i_ <= b_;++i_)
typedef long long ll;
using namespace std;
const int kN = 1005000;
int a[kN],b[kN];
ll cnt;
void mergeSort(int L,int R){
	if(L == R)return;
	int mid = L+R>>1;
	mergeSort(L,mid);
	mergeSort(mid+1,R);
	int pL = L,pR = mid + 1;
	_rep(i,L,R){
		if(pL <= mid && (pR > R || a[pR] >= a[pL]))b[i] = a[pL++];
		else b[i] = a[pR++],cnt += mid - pL + 1;
	}
	_rep(i,L,R)a[i] = b[i]; 
}
int main(){
    int T;
	scanf("%d",&T);
	int n;
    _rep(fjy666,1,T){
        scanf("%d",&n);
		_rep(i,1,n)
			scanf("%d",a+i);
		cnt = 0;
		mergeSort(1,n);
		printf("%lld\n",cnt);
	}
    return 0;
}
```

---

## 作者：胡金梁 (赞：0)

这一题就是归并排序的模板题。归并排序是利用分治的思想，把要排序的数组不断细分，再归并。归并排序要用递归，是本人学会的第一种快速的排序。推荐大家学习学习。在这里交换次数其实就是记录逆序对数。记录逆序对只需在二分过程中，若位置靠前的数大于位置靠后的数，那么交换两数，把答案加上两数的位置差即为操作次数。
```cpp
#include<bits/stdc++.h>
using namespace std;
int sum,a[500001],gd[500001];
void quick_sort(int q[],int kai,int jie)
{
	if(kai>=jie)
	{
		return ;
	}
	int middle=(kai+jie)>>1;
	quick_sort(q,kai,middle);
	quick_sort(q,middle+1,jie);
	int i=kai,j=middle+1,k=0;
	while(i<=middle&&j<=jie)
	{
		if(q[i]<=q[j])
		{
			gd[k]=q[i];
			i++;
		}
		else
		{
			gd[k]=q[j];
			j++;
            sum+=middle-i+1;
		}
		k++;
	}
	while(i<=middle)
	{
		gd[k]=q[i];
		i++;
		k++;
	}
	while(j<=jie)
	{
		gd[k]=q[j];
		j++;
		k++;
	}
	for(i=kai,j=0;i<=jie;i++,j++)
	{
		q[i]=gd[j];
	}
}
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int n;
		cin>>n;
		for(int j=1;j<=n;j++)
		{
			cin>>a[j];
		}
		memset(gd,0,sizeof(gd));
		sum=0;
		quick_sort(a,1,n);
		cout<<sum<<endl;
	}
}
```


---

## 作者：旭日临窗 (赞：0)

- 这是一道很经典的归并排序的题，我们想，如果$a[i] > a[j]$且$i < j$就必须交换一次，所以这道题实际上就是在求**逆序对。**

- 逆序对的求法：

![](https://cdn.luogu.com.cn/upload/image_hosting/0in48b5n.png)

定义$solve(i,j)$表示从$i$到$j$逆序对的数量

其中$i$和$j$有三种情况：

1.$i,j\le mid$那么就是$solve(l,mid);$

2.$i,j\ge mid$那么就是$solve(mid + 1,r);$

3.$i\le mid,j > mid$暴力的话会超时，所以可以考虑[尺取](https://blog.csdn.net/doubleguy/article/details/81265327)。

而尺取的前提是要有序，所以我们很快就会想到**归并排序**。

**注意要开longlong!!!**

$code:$

```c
#include <bits/stdc++.h>
#define ll long long
using namespace std;
int t,n;
int a[500010],b[500010];
int solve(int l,int r)
{
	if(l == r) return 0;
	int mid = l + r >> 1;
	ll ans = solve(l,mid) + solve(mid + 1,r);
	int p1 = l,p2 = mid + 1,p = l,j = mid + 1;
	for(int i = l;i <= mid;i++)
	{
		while(j <= r && a[i] > a[j]) j++;
		ans += j - mid - 1;
	}
	while(p1 <= mid && p2 <= r)
	{
		if(a[p1] < a[p2]) b[p++] = a[p1++];
		else b[p++] = a[p2++];
	}
	while(p1 <= mid) b[p++] = a[p1++];
	while(p2 <= r) b[p++] = a[p2++];
	for(int i = l;i <= r;i++) a[i] = b[i];
	return ans;
}
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		for(int i = 1;i <= n;i++) scanf("%d",&a[i]);
		printf("%d\n",solve(1,n));
	}
	return 0;
} 
```

有一道很相似的题[P1908](https://www.luogu.com.cn/problem/P1908)

~~/管理员大大求过，thanks/~~

---

## 作者：Phoenix_chaser (赞：0)

# 我来讲讲原理
最近在刷归并排序的题，看到这题就尝试了一下，结果自己过了

很多大佬在题解里说 **_归并排序_** ，并且讲得非常详细了，这里暂不赘述

但是我看了一圈，没有人仔细的讲解说为什么用归并排序能过

### 其实归并排序就是一个排序

但它一般跟一个东西连在一块

### 逆序对是什么

**在一个数列a中，满足a[i]>a[j]并且i<j的数对就叫做逆序对。**

### 为什么要引入逆序对

首先归并排序用到了二分的思想，在排序过程中如果a[i]<=a[j]就不会产生逆序对，如果a[i]>a[j]就会产生mid−i+1个逆序对

我们先看一下归并排序如何操作

将一个有序升序序列A[l~r]分成两半A[l~mid]和A[mid+1~r]

所以A[l~mid]的编号肯定都大于A[mid+1~r]的编号

我们让i属于A[l~mid]，j属于A[mid+1~r]

只有A[i]<A[j]才不是逆序对

要不然就产生逆序对，并且A[i]后面的数都会对A[j]产生逆序对

#### 也就是产生了mid+1-i个逆序对

### 每产生一个逆序对在归并中就是一次交换

因为最后归并出来的肯定是有序的

如图

![](https://cdn.luogu.com.cn/upload/image_hosting/cz5l0opj.png?x-oss-process=image/resize,m_lfit,h_170,w_225)


所以最小交换次数就是用归并求的逆袭对

以下是代码

```cpp
#include<iostream> 
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
int a[500010],c[500010],n,t;
long long ans=0;
void msort(int l,int r){
	if(l==r)
	return ;
	int mid=(l+r)/2;
	msort(l,mid);
	msort(mid+1,r) ;
	int i=l,j=mid+1,k=l;
	while(i<=mid&&j<=r){
		if(a[i]>a[j])
		{ans+=mid-i+1 ;
		//逆序对 
		c[k++]=a[j++];
		 }
		 else 
		 c[k++]=a[i++]; 
	}
	while(i<=mid) c[k++]=a[i++];
	while(j<=r) c[k++]=a[j++];
	for(int i=l;i<=r;i++)
	a[i]=c[i];
	
}
int main(){
	scanf("%d",&t);
	for(int i=1;i<=t;i++)
	{ans=0;
	memset(c,0,sizeof(c));
	scanf("%d",&n);
	for(int i=1;i<=n;i++) 
	scanf("%d",&a[i]);
	msort(1,n);
	cout<<ans<<"\n";
	}
	return 0;
}
```
## 谢谢观看
### THE END


---

## 作者：noall (赞：0)

嗯\~\~

终于用树状数组把这题A了，~~欧耶~~。

咳咳

**逆序对**：“对于给定的一段正整数序列，逆序对就是序列中$a_i>a_j$且$i<j$的有序对”。

这个题，有三种解法：

1. 暴力枚举每个数字。（肯定不可行，T飞）
2. 归并排序
3. 树状数组

今天，我们来谈谈树状数组的解法。

因为，我们都知道，树状数组是维护前缀和的一个数据结构。

那么，很容易想到，我们可以用树状数组来维护每一个数之前比它大的数的个数之和。

这就需要排序，从大到小排序。

但是，有可能数会重复，单单按照数进行排序肯定会影响答案的正确性，you know。（好好想一想为什么）

所以我们还要改变排序的算法：当数相等时，按照下标从小到大进行排序。

所以compare函数如下：

```cpp
inline bool cmp(int x,int y){
	if(a[x].num==a[y].num) return a[x].x>a[y].x;
	return a[x].num>a[y].num; 
}
```

#### code

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>

#define int long long
const int maxn=5e5+10;

int n,tree[maxn],r[maxn],ans;

struct type{
	int num,x;
}a[maxn];

inline bool cmp(int x,int y){
	if(a[x].num==a[y].num) return a[x].x>a[y].x;
	return a[x].num>a[y].num; 
}

inline int lowbi(int x){return x&(-x);}

inline void update(int x){
	while(x<=n){
		tree[x]+=1;
		x+=lowbi(x);
	}
	return ;
}

inline int query(int x){
	int sum=0;
	while(x>=1){
		sum+=tree[x];
		x-=lowbi(x);
	}
	return sum;
}

inline int read(){
    char ch=getchar();int x=0,f=1;
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return f*x;
}

signed main(){
	int t=read();
	for(register int cnt=1;cnt<=t;cnt++){
		memset(tree,0,sizeof(tree));
		ans=0;
		n=read();
		for(register int i=1;i<=n;i++) a[i].num=read(),a[i].x=i,r[i]=i;
		std::sort(r+1,r+1+n,cmp);
		for(register int i=1;i<=n;i++){
			update(r[i]);
			ans+=query(r[i]-1);
		}
		printf("%lld\n",ans);
	}
	return 0; 
}
```

---

