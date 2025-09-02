# [USACO16OPEN] Diamond Collector S

## 题目描述

奶牛 Bessie 一直喜欢闪闪发光的物体，她最近在业余时间开始了一项爱好——挖掘钻石！她收集了 $N$ 颗大小各不相同的钻石（$N \leq 50,000$），并希望将它们中的一部分放在谷仓里的两个展示柜中展示。

由于 Bessie 希望每个展示柜中的钻石大小相对接近，她决定如果两颗钻石的大小相差超过 $K$，就不能将它们放在同一个展示柜中（如果两颗钻石的大小相差恰好为 $K$，则可以将它们一起展示在同一个展示柜中）。给定 $K$，请帮助 Bessie 确定她可以在两个展示柜中一起展示的最大钻石数量。

## 样例 #1

### 输入

```
7 3
10
5
1
12
9
5
14```

### 输出

```
5```

# 题解

## 作者：a1455520571 (赞：146)

#### 本蒟蒻的第一篇题解，求过
   看题解都是先预处理再做，那本蒟就来一篇边处理边做的的题解吧。这个方法有点尺取的感觉...
## 分析题意
   题目大意就是要在排好序的数列中找出两段长度和最大的不重合的区间，并使两个区间中的最大值与最小值的差不大于k。
## 做法
   立个 ma 和 r , ma  表示某个位置的左边最多可以取多少颗钻石，放在第一个架子上；r  表示从某个位置向右最多可以延伸到的位置，放在第二个架子上。然后不断枚举位置(i)即可。
 ## 参考代码
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int n,k,a[50005],c[50005],r=2,ma,ans;//c[i]用来存从i-1向左最多可以取多少颗钻石。 
int main(){
    scanf("%d %d",&n,&k);
	a[n+1]=2100000000;//立个哨兵，防止r"跑丢"... 
    for(int i=1;i<=n;++i)
        scanf("%d",&a[i]);
    sort(a+1,a+n+1);
    for(int i=1;i<=n;++i){
        while(a[r]<=a[i]+k)r++;//可以往右就尽量往右，因为我们只需要最长的。 
        c[r]=max(r-i,c[r]);
        ma=max(ma,c[i]);//记录第i颗钻石（不包括i）前可以摆最多的钻石。即第一个架子上的钻石。 
        ans=max(ans,ma+r-i);//为什么是'r-i'而不是'c[r]'? 因为要防区间重叠.qwq
    }
    printf("%d",ans);
    return 0;
}
```

---

## 作者：以墨 (赞：51)

看到C党势力居然没有P党强（此楼），我决心来一发C~

看到楼下都是DP，我就先来一个DP吧。

我没怎么看楼下的，主要是一下看到辣莫多P党的，就不想看了。

**思路**

既然是两个互不相交的序列，那么也就是说选取一个断开点，让该断开点左边的数形成一个序列，右边的数形成另外一个序列。

就可以用一种DP的思想，用l[i]记录i左边的最长的可延伸长度（**不一定和第i个数有关**），r[i]同理。

这样就可以枚举每一个断开点，求它左边的最长长度加上右边的最长长度的和的最大值。

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
const int N=50002;
int l[N],r[N],a[N],ans,i,j,n,k;
int main(){
    freopen("diamond.in","r",stdin);
    freopen("diamond.out","w",stdout);
    scanf("%d%d",&n,&k);
    for(i=1;i<=n;i++)
        scanf("%d",&a[i]);
    sort(a+1,a+1+n);//必须要排序
    for(i=2,j=1,l[1]=1;i<=n;i++){
        while(a[i]-a[j]>k)
            j++;
        l[i]=max(l[i-1],i-j+1);
    }
    for(i=n-1,j=n,r[n]=1;i>=1;i--){
        while(a[j]-a[i]>k)
            j--;
        r[i]=max(r[i+1],j-i+1);
    }
    for(i=1;i<=n-1;i++)
        ans=max(ans,l[i]+r[i+1]);//这里是r[i+1]，因为不清楚l[i]和r[i]是否和第i个数有关
    printf("%d\n",ans);
    return 0;
}
```
其实本题还有一个思路，就是用二分的思想。
既然已经排好序，为什么不可以找出第i个数向左延伸和向右延伸的最长长度？

虽然这里是包括第i个数的，但后面可以改一改





```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
const int N=50002;
int p[N],q[N],a[N],n,i,j,ans,m;
int ALIKE_1(int x){//向左延伸
    int l,r,mid;
    for(l=1,r=n;l<=r;){
        mid=(l+r)>>1;
        if(a[mid]<x)
            l=mid+1;//当现在的值小于a[i]-m时，应调整下界，让值大一点
        else
            r=mid-1;//当现在的值不小于a[i]-m时，应调整上届，因为这不是最左端
    }
    return l;
}
int ALIKE_2(int x){
    int l,r,mid;
    for(l=1,r=n;l<=r;){
        mid=(l+r)>>1;
        if(a[mid]<=x)
            l=mid+1;//当值不大于a[i]+m时，应调整下界，因为这不是最右端
        else
            r=mid-1;//当值大于a[i]+m时，应调整上界，让值小一点
    }
    return r;
}
int main(){
    freopen("diamond.in","r",stdin);
    freopen("diamond.out","w",stdout);
    scanf("%d%d",&n,&m);
    for(i=1;i<=n;i++)
        scanf("%d",&a[i]);
    sort(a+1,a+1+n);
    for(i=1;i<=n;i++){
        p[i]=i-ALIKE_1(a[i]-m)+1;//第i个数向左延伸的最左端的值应不小于a[i]-m
        q[i]=ALIKE_2(a[i]+m)-i+1;//第i个数向右延伸的最右端的值应不大于a[i]+m
    }
    for(i=1;i<=n;i++){
        ans=max(ans,p[i-1]+q[i]);
        p[i]=max(p[i-1],p[i]);
    }
    printf("%d\n",ans);
    return 0;
}
这样的时间复杂度是O(nlogn)，还是很快的~
```

---

## 作者：牛蛙丶丶 (赞：29)

#### 排序 + 2-pointer 做法

#### 思路

先排序。

然后我们以两个指针分别从最左端和最右端开始扫，分别记录两端的最大值，从最左端开始扫记录每一个点的左端最大的差小于等于 k 的序列，而从最右端开始扫则记录的是每一个点的右端最大的差小于等于 k 的序列。这样处理之后，在一遍枚举所有的点，对他两端的状态进行求和，得到的便是最终的答案，即$ ans = max(ans,ansl(i)+ansl(i+1)) $ ，在这之中为了避免重复计算一个点的值，我们要加和的是 *i* 和  *i+1*。

#### code

```cpp
#include <cstdio>
#include <algorithm>
#define sf(x) scanf("%d",&x)
#define pf(x) printf("%d\n",x)
#define N 50077
using namespace std;

int n,k;
int a[N],ansl[N],ansr[N];

int main(){
	sf(n),sf(k);
	for(int i=1;i<=n;++i) sf(a[i]);
	sort(a+1,a+n+1);
	int l=1,r=n;
	for(int i=1;i<=n;++i){
		while(a[i]-a[l]>k&&l<=i) l++;
		ansl[i]=max(ansl[i-1],i-l+1);
	}
	for(int i=n;i>=1;--i){
		while(a[r]-a[i]>k&&r>=i) r--;
		ansr[i]=max(ansr[i+1],r-i+1);
	}
	int ans=0;
	for(int i=1;i<n;++i)
		ans=max(ans,ansl[i]+ansr[i+1]);
	pf(ans);	
}
```



---

## 作者：llzzxx712 (赞：26)

# P3143
~~(为什么我6个小时后交的一篇题解都过了，这篇题解没有通过也没有被打回……我再交一遍吧）~~
## 题意简述

- 给出 n 个数，从其中选出两组数，使每一组的 最大值与最小值之差不超过 k

## 题目分析

题目中选数是可以任意的，但是要尽量接近，所以我们选的数一定是一段长度连续的数。所以我们可以先对它排序。

我们很容易可以想到一个贪心思路（错的），一次考虑每一个点，算出以这个点为左端点可以选几个数，然后选出最大的两个点，相加得到答案。

但是这个贪心思路可能选出的两段区间会有重叠部分，导致答案错误。

**但是我们只要解决这个重叠问题就可以了**，我们可以考虑每个点，算出以它左边最大可以选的区间有多长，它右边最大可以选的区间有多长，再相加，这样就不会出现重叠了！

**但怎么计算它左边最大可以选的区间有多长呢？**~~（暴力出奇迹！）~~ 设 $le[i]$ 为$i$点左边最大可以选择的区间长度，我们只要从左往右依次考虑每个点，枚举这个点为左端点可以选 k 个数，然后 $max(k,le[i-1])$ 就是 $le[i]$ 的值了 。（同样，计算右区间同理）

最后，枚举一遍 $ i $，$le[i]+r[i+1]$最大的就是答案。

## 易错点

- 不要忘了排序
- 后面的点比前面的点大，枚举右区间时不要弄反了
- $le[1]$ 和 $r[n]$ 应先设为1再去枚举

## AC代码

内带详细注释

```cpp
#include<bits/stdc++.h>
using namespace std;
void read(int &x){//快读 
	int f=1;x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') { x=x*10+ch-'0';ch=getchar();}
	x*=f;
}
#define N 50010
int n,k,ans;
int a[N],le[N],r[N];
int main(){
	read(n),read(k);
	for(int i=1;i<=n;i++) read(a[i]);
	sort(a+1,a+1+n);//易错点1 
	le[1]=r[n]=1;//易错点3  
	for(int i=2,now=1;i<=n;i++){ 
		while(a[i]-a[now]>k) now++;//找 "k" 
		le[i]=max(le[i-1],i-now+1);//类似递推 
	}
	for(int i=n-1,now=n;i>=1;i--){
		while(a[now]-a[i]>k) now--;
		r[i]=max(r[i+1],now-i+1);//易错点2
	}
	for(int i=1;i<n;i++){
		ans=max(ans,le[i]+r[i+1]);//最后的枚举 
	}
	cout<<ans;
}

```

蒟蒻写题解不易，点个赞呗~


---

## 作者：EarthGiao (赞：17)

## 【思路】
排序 + 双指针      
### 【前缀思想】
很有意思的一道题目     
这个需要找两组差不超过k的并且和最大的序列     
因为需要差不超过k，     
所以可以先将序列排一下序      
然后就成为了有序的序列（很显然对吧）     
这样就可以用双指针记录头和尾     
然后只要头和尾的差小于等于k     
就可以尝试一下这个区间能不能再扩大     
所以可以很简单的就用双指针找出最长的差小于等于k的序列     
 
### 【中心思想】
但是，这道题目有两个陈列架     
所以找出一个最大的是不行的     
而且找出次大的和最大的加起来也是不可行的     
因为不保证最大和次大的区间不重叠     
所以可以正序扫一遍然后找出     
到每一个点之前最长的差小于等于k的序列    
然后再倒序找一遍找出    
到每一个点之后最长的差小于等于k的序列     

###  【小细节】
这样，只需要再枚举一遍每一个点      
然后比较前后加起来的和最大的就是了       
不过，如果出现了前后最大的刚好重叠在枚举到的这个点       
那么加起来的和就会重复一次       
而且是不合法的      
毕竟你不能把一个宝石放在两个陈列架上    
所以就有了后面在比较时候的：    
M = max(M,qian[i] + hou[i + 1]);      
这样就不会出现一个点刚好是两个区间的交点的情况了     
 
## 【完整代码】
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>

using namespace std;
const int Max = 50005;
int a[Max];
int qian[Max];
int hou[Max];
int main()
{
	int n,k;
	cin >> n >> k;
	for(register int i = 1;i <= n;++ i)
		cin >> a[i];
	sort(a + 1,a + 1 + n);
	for(register int l = 1,r = 1;r <= n;++ r)
	{
		while(a[r] - a[l] > k && l <= r)l ++;
		qian[r] = max(qian[r - 1],r - l + 1);
	}
	for(register int r = n,l = n;l >= 1;l --)
	{
		while(a[r] - a[l] > k && l <= r)r --;
		hou[l] = max(hou[l] + 1,r - l + 1);
	}
	int M = 0;
	for(register int i = 1;i < n;++ i)
		M = max(M,qian[i] + hou[i + 1]);
	cout << M << endl;
	return 0;
}
```

---

## 作者：wjyyy (赞：16)

## 吐槽
   解法众多的一道毒瘤题？
   
### [我的blog](http://www.wjyyy.top/1497.html)

## 题解
   其实这个题可以用暴力线段树，也可以用DP单调栈。不过想到一种RMQ方法，也可以完成这道题。

   题目要求每个陈列架中的元素最大-最小不超过定值$k$，可以贪心地认为，它们处在一个区间里，下界是一个元素$a_i$，上界是$a_i+k$，这样避免了下界的浪费。同时因为没有顺序的要求，所以可以排序。

   而我们要选择两个区间，就得使两个区间并中的元素个数最多。可以考虑用一个数组$f[i]$存下以$a[i]$开始，长度为$k$的区间有多少个数。

   当两个区间不相交的时候，答案肯定就是两个数相加。当两个区间相交的时候呢？我们知道，相交肯定没有不相交优。如果两个区间相交了，可以把稍微靠后的区间向后平移一段，这样不会损失任何区间，反而可能会使答案变优。



   所以枚举左边的区间，然后在左区间右端点以右找最大值。可以直接维护后缀最大值来转移，用$mus[i]$表示$\max\limits_{j\in[i,n]}f[i]$，就可以在$O(n)$的时间内转移，并在总时间$O(n\log n)$内完成全部过程。



## Code：
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
int mus[51000];//后缀最大值
int a[51000];
int b[51000];
int main()
{
    int n,k;
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;++i)
        scanf("%d",&b[i]);
    std::sort(b+1,b+1+n);
    int t1=n;
    for(int i=n;i;--i)
    {
        while(b[t1]>b[i]+k)
            --t1;
        a[i]=t1-i+1;//用two-pointer统计上界
        mus[i]=std::max(mus[i+1],a[i]);
    }

    int ans=0;
    for(int i=1;i<=n;++i)
    {
        int ans1=0;
        ans1=mus[i+a[i]];//转移最大值
        ans=std::max(ans,a[i]+ans1);
    }
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：Freeyer (赞：11)

来一篇比较详细的题解吧....

模型：给定一个序列，求两个无重叠的区间，且每个区间最大值与最小值相差不超过k，求两区间元素之和的最大值

贪心？dp？

先对数据进行排序，一定不会影响正确性，因为数字的选择是随意的，而排序后更加容易处理

首先，两个区间一定分别连续，因为加入中间有间隔的元素，且两边本别有元素在选择区间内，那么加入他一定不会影响最大值和最小值。

接着预处理出l[i]和r[i],分别表示以i为起点向左能选择的最长区间和向右(不包括i）能选择的最长区间，直接模拟即可
```cpp
int j=1;
for(int i=1;i<=n;++i)
{
	for(;j<=n;++j)//不需要每次都从i+1开始，因为a[i+1]必然大于a[i],故a[i+1]一定满足a[j]-a[i+1]<=k
	{
		if(a[j]-a[i]<=k)
			l[j]=j-i+1;
		else break;
	}
	r[i]=j-i;（因为不包括i所以区间长度为j-i）
}
```
由于我们要求的是每个元素向左和向右对包括的点没有限制的最长区间，因此令

ll[i]=max(ll[i-1],l[i]); 

rr[i]=max(rr[i+1],r[i+1]);

即可递推求出向左和向右的最长区间

最后枚举断点，ans=max(ans,ll[i]+rr[i]);

代码：
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
const int N=5e5+5;
int a[N],l[N],r[N],ll[N],rr[N],ans,n,k;
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;++i)
		scanf("%d",&a[i]);
	sort(a+1,a+1+n);
	for(int i=1;i<=n;++i)
		l[i]=1;
	int j=1;
	for(int i=1;i<=n;++i)
	{
		for(;j<=n;++j)
		{
			if(a[j]-a[i]<=k)
				l[j]=j-i+1;
			else break;
		}
		r[i]=j-i;
	}
	ll[1]=1;
	for(int i=2;i<=n;++i)	
		ll[i]=max(ll[i-1],l[i]);
	for(int i=n-1;i>=1;--i)
		rr[i]=max(rr[i+1],r[i+1]);
	for(int i=1;i<=n;++i)
		ans=max(ans,ll[i]+rr[i]);
	cout<<ans;
	return 0;
}
```


---

## 作者：issue_is_fw (赞：10)

也是预处理,但是和上面的稍有不同

但是这里面用到了差分、二分的做法(hh~)

第一行是钻石高度，第二行是钻石往右最多延伸的长度

| 1 |5  |5  |9  |10  |12  |14  |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
|  1|2  |1  |3  |2  |2  |1  |

怎么处理出这个表格呢?

比如如果某个钻石能包含最后一个高度$14$的钻石

那么高度一定大于等于$11(14-3==11)$

所以枚举每个钻石$R$，二分找出一个能刚好包括这颗钻石的钻石$L$

那么区间$[L,R]$的钻石往右扩展的长度都$+1$

这个过程我们用差分完成，也就是这样

```cpp
for(int i=n;i>=1;i--)
{
	int z=fen(a[i]-k);//找出的左边界 
	cha[z]++,cha[i+1]--;//差分 
}
```
然后，差分数组一直累加就得到了每个钻石往右扩展的长度

```cpp
for(int i=1;i<=n;i++)
	cha[i]+=cha[i-1];
```

用$ans$数组表示从第$i$个钻石往后最多扩展的钻石数

```cpp
for(int i=n;i>=1;i--)	ans[i]=max(ans[i+1],cha[i]);
```
接下来就是求两段不相交的最大和，也就是

```cpp
for(int i=1;i<=n;i++)
	last=max(last,cha[i]+ans[i+cha[i]]);
```
完结撒花!!!
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,k;
int a[50009],cha[50009],ans[50009];
int fen(int s)
{
	int l=1,r=n,mid;
	while(r>l)
	{
		mid=(l+r)>>1;
		if(a[mid]>=s)	r=mid;
		else	l=mid+1;	
	}
	return r;
}
int main()
{
	cin>>n>>k;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	sort(a+1,a+1+n);
	for(int i=n;i>=1;i--)
	{
		int z=fen(a[i]-k);//找出的左边界 
		cha[z]++,cha[i+1]--;//差分 
	}
	for(int i=1;i<=n;i++)
		cha[i]+=cha[i-1];
	for(int i=n;i>=1;i--)	ans[i]=max(ans[i+1],cha[i]);
	int last=0;
	for(int i=1;i<=n;i++)
		last=max(last,cha[i]+ans[i+cha[i]]);
	cout<<last;
}
```





---

## 作者：Azuree (赞：7)

## ~~有splay的标签~~
# 其实用two-pointer就能轻松搞定
### 时间复杂度为O(n)
我们可以发现,将数据答案一定是数据的某两个区间的长度和。对于判断一个区间是否能够被放到一个架子上，只需要判断这个区间的首尾数据的差是否超过了k。
这里，我们可以用两个two-pointer来线性枚举区间，最后枚举这两个区间之间的分割点来更新答案。
```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>
#include<vector>

using namespace std;

int n,k,a[51000],l[51000],r[51000],p1,p2,maxx;

int mysort(int a,int b) {return a < b;}

void two_pointer()
{
	p1 = 0;
	p2 = 1;
	for(int i = 1; i <= n; i++)
	{
		p1 ++;
		while(a[p2] - a[p1] <= k && p2 < n) p2 ++;
		if(a[p2] - a[p1] > k) p2 -- ;
		l[p1] = p2 - p1 + 1;
	}
for(int i = n-1; i > 0; i--) l[i] = max(l[i], l[i + 1]); //使用右侧的最优解更新当前节点
}

void tow_pointer()
{
	p1 = n + 1;
	p2 = n;
	for(int i = 1; i <= n; i++)
	{
		p1 --;
		while(a[p1] - a[p2] <= k && p2 > 1) p2 --;
		if(a[p1] - a[p2] > k) p2 ++;
		r[p1] = p1 - p2 + 1;
	}
	
	for(int i = 2; i <= n; i++) r[i] = max(r[i], r[i - 1]);//使用右侧的最优解更新当前节点
}

int main()
{
	scanf("%d%d",&n,&k);
	for(int i = 1; i <= n; i++) scanf("%d",&a[i]);
	sort(a+1,a+n+1,mysort);
	two_pointer();  //枚举分割点右侧的区间
	tow_pointer();  //枚举分割点左侧的区间
	for(int i = 1; i < n; i++)
			maxx = max(maxx, l[i + 1] + r[i]); //枚举分界点更新答案
	cout << maxx;
	return 0;
}
```

---

## 作者：FendtSilence (赞：5)

USACO总是喜欢在最优化问题上搞事，比如，两个最优，此题就是例子。

先分析一下题意，每一个架子上的钻石差值不能超过$K$，那就是说每个架子上的$a[max_i]-a[min_i]<=K$，这个时候可以先排一下序，这样就能把选择问题转换成区间问题，这个时候我们发现，只要找出两个符合$a[R]-a[L]<=K$的不重叠区间，并且使和最大就可以了。

我们可以先使用一个数组$f[i]$初始化成以$i$为开头的最长允许的区间长度，这个可以在$a[R]<=a[L]+K$的意义下二分找出答案，这里推荐使用STL神器$lower_bound()$，处理出长度之后提供两种方法，一种是处理出$f[]$的st表来，枚举第一个区间，再用st表查询第二个最大的区间，然后不断更新答案。另一种方法比较方便，我们以$(from n to 1)$的方法枚举$i$，每一次处理出$i$之后的最长的区间值，然后再加上$f[i+f[i]]$来更新答案，非常巧妙。

最后献上代码

```cpp
#include<iostream>
#include<stdio.h>
#include<algorithm>
using namespace std;
const int maxn=500001;
int n,k,a[maxn],f[maxn],ans;
bool cmp(const int &a,const int &b)
{
    return a<=b;
} 
inline void solve()
{
    cin>>n>>k;
    for(int i=1;i<=n;i++) cin>>a[i];
    sort(a+1,a+n+1);
    for(int i=1;i<=n;i++) f[i]=lower_bound(a+1,a+1+n,a[i]+k,cmp)-a-i;
    for(int i=n;i>=1;i--) ans=max(ans,f[i]+f[i+f[i]]),f[i]=max(f[i],f[i+1]);
      cout<<ans;
}
int main()
{
    solve();
    return 0;
}
```

---

## 作者：fy0123 (赞：5)

算是动规？我也说不清 类似的吧

先排序

然后用“区间伸缩大法”（具体是什么看代码就知道 大概是扫描左边界右边界这样子）做出f[ ] g[ ]

f[i]表示1~i的钻石中差值不超过k的最多几个 g[i]表示i~n的钻石中差值不超过k的最多几个

答案就是 max{f[i]+g[i+1]}

```cpp
type arr=array[0..50000]of longint;
var n,k,i,j,l,r,ans,m:longint;
    a,f,g:arr;
function max(x,y:longint):longint;
begin
if x>y then exit(x) else exit(y);
end;
procedure sort(l,r: longint;var a:arr);
var i,j,x,y: longint;
begin
i:=l;j:=r;
x:=a[(l+r) div 2];
repeat
  while a[i]<x do inc(i);
  while x<a[j] do dec(j);
  if not(i>j) then
     begin
       y:=a[i];a[i]:=a[j];a[j]:=y;
       inc(i);dec(j);
     end;
until i>j;
if l<j then sort(l,j,a);
if i<r then sort(i,r,a);
end;
begin
read(n,k);
for i:=1 to n do read(a[i]);
sort(1,n,a);
l:=1;r:=1;
f[1]:=1;
while (l<=r)and(r<=n) do
      begin
      while (r<=n)and(a[r]-a[l]<=k) do
            begin
             f[r]:=max(r-l+1,f[r-1]);
             inc(r);
            end;
      if r>n then break;
      f[r]:=f[r-1];
      while (l<=r)and(a[r]-a[l]>k) do inc(l);
      end;
g[n]:=1;
l:=n;r:=n;
while (l<=r)and(l>=1) do
      begin
      while (l>=1)and(a[r]-a[l]<=k) do
            begin
              g[l]:=max(r-l+1,g[l+1]);
              dec(l);
            end;
      if l<1 then break;
      g[l]:=g[l+1];
      while (l<=r)and(a[r]-a[l]>k) do dec(r);
      end;
for i:=1 to n-1 do
    ans:=max(ans,f[i]+g[i+1]);
writeln(ans);
end.
```

---

## 作者：Zenith_Yeh (赞：3)

看到放一串相差小于等于的钻石，就想到“滑动窗口”的算法。

后面发现，要放两串，所以我们可以选择一个断开点，分别做两次。

但是若在线做的话，会超过亿点点时间。

所以要预处理。

**上菜：**
```cpp
#include<bits/stdc++.h>
#define read() Read<int>()
namespace pb_ds{//优美的快读
    namespace io{
        const int MaxBuff=1<<15;
        const int Output=1<<23;
        char B[MaxBuff],*S=B,*T=B;
		#define getc() ((S==T)&&(T=(S=B)+fread(B,1,MaxBuff,stdin),S==T)?0:*S++)
        char Out[Output],*iter=Out;
        inline void flush(){
            fwrite(Out,1,iter-Out,stdout);
            iter=Out;
        }
    }
    template<class Type> inline Type Read(){
        using namespace io;
        register char ch;
        register Type ans=0;
        register bool neg=0;
        while(ch=getc(),(ch<'0' || ch>'9') && ch!='-');
        ch=='-'?neg=1:ans=ch-'0';
        while(ch=getc(),'0'<= ch && ch<='9') ans=ans*10+ch-'0';
        return neg?-ans:ans;
    }
    template<class Type> inline void Print(register Type x,register char ch='\n'){
        using namespace io;
        if(!x) *iter++='0';
        else{
            if(x<0) *iter++='-',x=-x;
            static int s[100];
            register int t=0;
            while(x) s[++t]=x%10,x/=10;
            while(t) *iter++='0'+s[t--];
        }
        *iter++=ch;
    }
}
using namespace pb_ds;
using namespace std;
int l[50005],r[50005],a[50005],ans,n,k;
int main()
{	n=read(),k=read(); 
	for(register int i=1;i<=n;++i)a[i]=read();
	sort(a+1,a+1+n);//注意排序
	l[1]=1;
    for(register int i=2,j=1;i<=n;i++)//预处理左边可延伸的
	{   while(a[i]-a[j]>k)j++;
        l[i]=max(l[i-1],i-j+1);
    }
    r[n]=1;
    for(register int i=n-1,j=n;i>=1;i--)//预处理右边可延伸的
	{   while(a[j]-a[i]>k)j--;
        r[i]=max(r[i+1],j-i+1);
    }
    for(register int i=1;i<=n-1;i++)ans=max(ans,l[i]+r[i+1]);//取max
    printf("%d\n",ans);
    return 0;
}
```


---

## 作者：OnlyU (赞：3)

这道题很容易就能看出是一道贪心题。因为不能把两个大小相差K以上的钻石同时放在一个陈列架上，所以我们可以用upper_bound求出一个钻石到比它大K以内的钻石数，之后再枚举求解。具体见代码注释解释。
下为完整代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,ans=0,a[5000001],sum[100001]={0},l[1000001];
int main() {
    cin>>n>>k;
    for(int i=1; i<=n; i++)
        cin>>a[i];
    sort(a+1,a+n+1);//先排序
    for(int i=1;i<=n;i++){
        l[i]=upper_bound(a+1,a+n+1,a[i]+k)-a-1;
        if(l[i]==n+1)l[i]--;
    }
    for(int i=n;i>=1;i--)
        sum[i]=max(sum[i+1],l[i]-i+1);枚举
    for(int i=n;i>=1;i--)
        ans=max(ans,sum[l[i]+1]+l[i]-i+1);取最大值
    printf("%d",ans);
    return 0;
}
```


---

## 作者：Patrickpwq (赞：3)

萌新又冒泡

我最初的想法就是先找到最长的一段 删去后找次长的一段

不过很显然 这个方法有很多毛病 比如最长的不止一段 就会对次长的一段的抉择产生影响

不过我们可以以此做一点修改 可以先排序 接着预处理出每个数往后最长的一段

然后可以考虑枚举每一个数 对于这个数后的最长段 次长段一定在最长段之后的某一段 可以不考虑在之前的情况 因为之前是会被枚举到的

那对于次长段的寻找 甚至可以套上线段树等数据结构 不过由于单调性 我们可以倒序枚举 边枚举边取max 具体见代码

```cpp
#include<bits/stdc++.h>
using namespace std;

#define maxn 50015
int n,k,a[maxn],ans[maxn];

int main()
{
  	scanf("%d%d",&n,&k);
  	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
  	sort(a+1,a+1+n);
	int Ans=0,j=1;
	for(int i=1;i<=n;i++)
  	{
    	while(a[j]-a[i]<=k&&j<=n)	j++;
    	ans[i]=j-i;
  	}
  	//ans[i] 包括自己可以延伸到的最远的地方 
  	for(int i=n;i>=1;i--)
  	{
    	Ans=max(Ans,ans[i]+ans[i+ans[i]]);	//防重叠 
    	ans[i]=max(ans[i],ans[i+1]);	//累积更新ans 一直取max 因为要在右边取最大的 
  	}
  	cout<<Ans<<endl;
  	return 0;
}
```

---

## 作者：redegg (赞：3)

一看数据范围，线段树，剩下的这题就两个问题：我要如何快速处理出所有可能个数？两个架子我该怎么办？

对于第一个问题，我们只需要**先排序**，**然后两个标记一起向右移动就可以了**：

p是左端点，v是右端点，如果左端点与右端点差大于了k，则记下这个点可以最多延伸多远，存到数组b中，然后左端点右移一格，如果差小于k，则右端点右移直到差大于k或者到底了。

第二个问题，我们枚举第一个架子上放的数量，这个很简单，**枚举数组b就可以了**，然后确定了第一个架子的范围，第二个架子的范围就在除去第一个架子的范围里，我们没必要从前面找了（因为这种情况已经被考虑过），我们**在剩下的范围里，找到最大的那个第二个架子，然后相加和答案max一下就可以了**，至于如何找到最大的那个，我写的是**线段树**

不知道大家看懂了没有，这是我这几天可以说是能够完全掌握的题了（哭晕）

代码在下（连续交三发线段树题解？）
```cpp
#include <bits/stdc++.h>
using  namespace std;

int a[100000];
int b[100000];

int p;
int v;
int n,k;

int maxn[500000];

void build(int l,int r,int id)
{
    if(l==r)
    {
        maxn[id]=b[l];
        return ;
    }
    int mid=(l+r)/2;
    build(l,mid,id*2);
    build(mid+1,r,id*2+1);
    maxn[id]=max(maxn[id*2],maxn[id*2+1]);
}

int cck(int l,int r,int z,int y,int id)
{
    if(l==z&&r==y)
    {
        return maxn[id];
    }
    int mid=(l+r)/2;
    if(mid>=y)return cck(l,mid,z,y,id*2);
    if(mid<z)return cck(mid+1,r,z,y,id*2+1);
    else
    {
        return max(cck(l,mid,z,mid,id*2),cck(mid+1,r,mid+1,y,id*2+1));
    }
}

int main()
{
    scanf("%d%d",&n,&k);
    b[0]=1;
    for(int i=1; i<=n; i++)
    {
        b[i]=1;
        scanf("%d",&a[i]);
    }
    sort(a+1,a+1+n);
    p=1;
    v=2;
    while(1)
    {
        if(p>n)break;
        if(v>n)
        {
            b[p]=v-p;
            p++;
            continue;
        }
        if(v==p)v++;
        if(a[v]-k<=a[p])
        {
            v++;
            continue;
        }
        else
        {
            b[p]=v-p;
            p++;
        }
    }
    build(1,n,1);
    int maxn=0;
    for(int i=1; i<=n; i++)
    {
        if(b[i]+i<=n)
        {
            maxn=max(b[i]+cck(1,n,b[i]+i,n,1),maxn);
        }
    }
    printf("%d\n",maxn);
    return 0;
}

```

---

## 作者：曹老师 (赞：2)

## Sol ##

[blog食用](http://www.caolaoshi.men/index.php/archives/usaco16open-dc.html)

**警告：这种思路有坑，坑了我好久！**

以下称：区间内相差不超过$K$的数的个数 为 满足条件的数的个数

第一种想法：将数字排序，枚举左端点，右端点就能确定，二分右端点，找到在数组中的下标，能确定有多少个满足条件的，然后找这些满足条件个数的第一大和第二大，相加即为答案。

第二种想法：对第一种想法进行简单的改动，把每一个区间的左右端点，和这个区间内满足条件的数的个数放入一个大根堆中，堆顶肯定要，从堆中不断地往外取，如果和第一次取出来的没有交点，就取出，两次取出来的数相加即为答案。

第三种想法：对第一种想法的更简便的改动，维护出以每一个点为左端点的区间的满足条件的个数，再维护以每一个点为左端点，以$n$为右端点的区间满足条件的个数。枚举左端点，就能这个连续区间的右端点（若左端点为$l$，右端点不为$l+K-1$，因为有重复)，两部分相加即为答案。

**以上三种想法，只有第三种想法正确！**

解释：对于第一种想法，没有考虑到第一大和第二大重叠的部分，于是为了重叠部分就有了第二种想法，第二种想法能够很好地处理掉重叠的部分，但是第二种想法脱离了前一部分和后一部分的关系，因为堆顶的元素不一定必须取！可能取了堆顶的元素，就把一个更优的解的第二大给分开了（语文功底不好，自行理解），所以啊，还是第三种想法是正确的，而且复杂度很低，是$O(n)$的复杂度。

## Code ##

```
#include<iostream>
#include<cstdio>
#include<cmath>
#include<queue>
#include<algorithm>
using namespace std;

int n , k , num[50005] , ans = 0 , front[50005] , back[50005];

int main() {
	scanf("%d%d",&n,&k);
	for(int i=1; i<=n; i++)
		scanf("%d",&num[i]);
	sort(num+1 , num+n+1);
	for(int i=1; i<=n; i++) {
		int l = i , r = upper_bound(num+1, num+n+1, num[i]+k)-num-1;
		front[i] = r - l + 1;
	}
	for(int i=n; i>=1; i--)
		back[i] = max(back[i+1] , front[i]);
	for(int i=1; i<=n; i++)
		ans = max(ans , front[i] + back[min(i+front[i],n)]);
	printf("%d",ans);
	return 0;
}
```


  [1]: https://www.luogu.org/problemnew/show/P3143

---

## 作者：ww3113306 (赞：2)

一次过，而且速度还不错，心情大好，遂来分享一下做法，

PS：我看其他题解大多是直接查询的f[i]+f[f[i]+i]的最大值，但是我并不是很理解，因为不知道为什么最优解一定会挨在一起，，，反正我是得不到这个结论，可能是我太弱了吧╮(╯▽╰)╭

由于相差不超过k才可以放在一起，要判断不超过k这个条件，显然我们需要排序

首先我们需要一个f数组，f[i]意义看代码开头注释,

假设我们可以选择的某一个区间是a[l]~a[r]（已排序且最优(最长的意思））,那么这个区间要符合这样一个性质：

a[r]-a[l]<=k

移项一下，

a[r]<=k+a[l]（r要尽可能大）

而a[l]中的l我们是枚举得到的，因此我们只需要求出对应的r即可

我们观察移项后的式子可以发现，我们要求的r其实是数列中小于等于k+a[l]的最大值

那么这显然是符合可二分性的，

所以我们二分查找r的位置，由此可以得到f[l]=half(k+a[l]) - l + 1;

然后我们可以枚举第一个架子放的是从哪里开始的

因为不允许重叠，因此我们需要查询f[f[i]+i]~f[n]的最大值（第二个架子），

为什么不用查询前面的？

与枚举数对同理，如果足够优的话，前面的会查询到后面的，所以不必重复查询（而且也不好处理，因为不知道前面查询到的会不会和后面冲突),

那么区间查询最大值，无修改，我们可以想到什么呢？

ST表！

那么ST表是什么？

ST[i][j]存从i开始往后面2^j个（包括i自己）的最大值

根据倍增的思想，我们可以在nlogn的时间内建出ST表

然后再次根据倍增的思想，我们可以实现O(1)查询

这里ST表就不作过多解释了，还不会的去写模板[ST表](https://www.luogu.org/problemnew/show/P3865)即可
```cpp
#include<bits/stdc++.h>
using namespace std;
#define R register int
#define AC 50020
/*二分查找f[i]，以i为开头最多能放几个，然后对f数组建立ST表，
查询f[f[i]+i] ~ f[n]的最大值，
为什么不用查询前面的？
与枚举数对同理，如果足够优的话，前面的会查询到后面的，所以不必重复查询（而且也不好处理),
这样的话,时间复杂度O(nlogn(获取f数组) + nlogn(获取ST表) + n(查询))
O(nlogn+n)? --- > O(nlogn)*/
int n,ans,k;
int ST[AC][17],f[AC],a[AC],p[AC];
inline int read()
{
	int x=0;char c=getchar();
	while(c>'9' || c<'0') c=getchar();
	while(c>='0' && c<='9') x=x*10+c-'0',c=getchar();
	return x;
}

inline void upmax(int &a,int b)
{
	if(b>a) a=b;
}

inline int Min(int a,int b)
{
	if(a<b) return a;
	else return b;
}

inline int Max(int a,int b)
{
	if(a>b) return a;
	else return b;
}

inline int half(int x)//二分查找小于等于x的最大值，并返回下标
{
	int l=1,r=n,mid;
	while(l<r)
	{
		mid=(l+r+1)>>1;//由于符合条件时应尽可能向右移，这时为了保持ans在区间内，
		//---> l=mid,但这样的话，由于传统mid偏向l，将会导致死循环
		//因此将mid手动偏向r，这时由于不符合才会移动r，所以--->r=mid-1,本就不需要mid，
		//因此每次转移必定会有偏移量，所以就不会死循环了
		if(a[mid] <= x) l=mid;//由于mid偏向l，所以+1防止死循环
		else r=mid-1;
	}
	return l;
}

void pre()
{
	n=read(),k=read();
	for(R i=1;i<=n;i++) a[i]=read();
	sort(a+1,a+n+1);
	for(R i=1;i<=n;i++) f[i]=half(k+a[i]) - i + 1;//f[i]存个数
}

void built()
{
	int key=1;
	for(R i=1;i<=n;i++)
	{
		if(i==(key<<1)) p[i]=p[i-1]+1,key<<=1;
		else p[i]=p[i-1];//存下长度为i时，最长包含2的几次方,以保证一定包含了整个区间
		ST[i][0]=f[i];
	}
	for(R j=1;j<=17;j++)
		for(R i=1;i<=n;i++)
			ST[i][j]=Max(ST[i][j-1] , ST[Min(i + (1 << (j - 1)),n)][j-1]);//因为可能剩下的i~n,根本就不够1<<j,所以要取Min
}

void work()
{
	for(R i=1;i<=n;i++)
	{
		int l=f[i] + i,r=n;
		k=p[r-l+1];
		upmax(ans,f[i] + Max(ST[l][k],ST[r - (1<<k) +1][k]));
	}	
	printf("%d\n",ans);
}

int main()
{
	freopen("in.in","r",stdin);
	pre();
	built();
	work();
	fclose(stdin);
	return 0;
}
```

---

## 作者：Orion_Rigel (赞：2)

可以想到，排序好每一个架子上都是一段区间，然后只需要统计每个点向左向右最长延伸的区间。

然后考虑到不会有重叠（重叠部分可以放入一个架子，然后另一个架子还可以延伸）

刚开始看成了大于k才能放进一个架子。。。。

···
```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int a[50001],n,k,ans=0;
int l[50001],r[50001];
int main()
{
    scanf("%d%d",&n,&k);
    for (int i=1;i<=n;++i) scanf("%d",&a[i]);
    sort(a+1,a+n+1);
    int h=1; l[1]=1;
    for (int i=2;i<=n;++i)
    {
        while (a[i]-a[h]>k) h++;
        l[i]=max(l[i-1],i-h+1);
    }
    r[n]=1;
    h=n;
    for (int i=n-1;i>=1;--i) 
    {
        while (a[h]-a[i]>k) h--;
        r[i]=max(r[i+1],h-i+1);
    }
    for (int i=1;i<n;++i)
        ans=max(ans,l[i]+r[i+1]);
    printf("%d\n",ans);
}
···
```

---

## 作者：Y_B_Y (赞：2)

**warning:暴力警告**

看到这一题,我一开始**眼瞎地**以为只是找到一个最大的子序列,使其中的元素差最大不超过k,那可以先排序,然后再找一段满足要求的最长序列就可以了,发现连样例都过不了

于是我又在**找完第一遍后删掉第一遍找到的那个最大子序列**,**再找第二遍**,再累加答案.

后来的情况大概是这样的....

内心OS:

稍微修改一下轻松水过大水题,$WA$了?不要怕,转换一下题意,反手来一个线段树,给代码一波重构,要是这个数据能把我线段树卡了,我当场,就把这个电脑屏幕吃下去.

轻松AC~

![](https://cdn.luogu.com.cn/upload/image_hosting/f7tqvn36.png)

我们发现上面提到了线段树,为什么要用线段树呢?我们先来看为什么我上面的方法会$WA$,我们发现当下面这种情况,上面的做法是错的

$k=3$,序列排序后为{$1 ,2 ,3 ,5 ,5 ,7$},如果用上面的方法就会先找到$2,3,5,5$这一段,然后只能再取单个$1$这一段了

但是我们发现我们可以先取$1,2,3$再取$5,5,7$这样是更优的

走到死胡同了,我们可以转换一下题意,我们先将**序列从小到大排序**,以排序后元素的**序号作为数轴上的一点**,然后我们将每一个点$i$作为一条线段的左端点,将它**能到达的最远点**(即最大的点$j$,是$i$到$j$,的所有元素的差不超过k)做为**右端点**,这样数轴上就有n条线段(也可以是点),如图

###### ("以为"改为"因为")

![](https://cdn.luogu.com.cn/upload/image_hosting/53xd7hwa.png)


那么我们其实就是要**找两条线段**,使他们**覆盖的范围最大**,对于两条线段$i,j$,设他们的端点为$l_i,r_i,l_j,r_j$($l_j≥l_i$,由于前面找线段是从左到右的,所以**左端点是有序的**,即$l_j≥l_i$且$i≠j→j>i$),那么我们可以**分情况讨论**

当$r_i≥l_j$时,即线段**有重合**时,覆盖的长度为,$max(r_i,r_j)-l_i+1$(可以自己画图理解)

当$r_i<l_j$时,线段**无重合**,长度即为$r_i-l_i+1+r_j-l_j+1$

我们发现我们可以枚举$i$,然后再通过**二分**找出最大的$j(i<j≤n)$,使$r_i≥l_j$,再在$i+1$到$j$中找到最大的$r$,由于**数列从小到大排序,所以$l$越大,$r$也越**大,所以最大的$r$即为$r_j$,所以此时能得到的最大长度为$max(r_i,r_j)-l_i+1$,更新一下答案

前面我们找到的最大的$j$,使$r_i≥l_j$,所以从$j+1$到$n$这一部分,就是线段无重合,我们可以用**线段树**直接找出最大的$r_x-l_x+1(j<x≤n)$,所以此时能得到的最大长度为$r_i-l_i+1+r_x-l_x+1$,更新一下答案

时间复杂度$O(NlogN)$

~~前面标答复杂度最大在排序为一个$NlogN$,我这个虽然暴力,但其实也就是多了几个$NlogN$嘛~~.

细节看有亿点长的代码吧

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=50001;
ll n,k,a[50001],l,r,ans,cnt;
struct xd
{
	ll l,r;
}x[N];//存线段
/*下面为求区间最大值的线段树*/
struct tr
{
    long long x,l,r,lz;
}t[10*N+1];//数组大小开大一点
void bd(ll p,ll l,ll r)
{
    t[p].l=l;
    t[p].r=r;
    if(l==r)  return;
    ll mid=(l+r)/2;
    bd(2*p,l,mid);
    bd(2*p+1,mid+1,r);
    t[p].x=max(t[p*2].x,t[p*2+1].x);
    return;
}
void sd(ll p)
{
    if(t[p].lz)
    {
        t[p*2].x+=t[p].lz;
        t[p*2+1].x+=t[p].lz;
        t[p*2].lz+=t[p].lz;
        t[p*2+1].lz+=t[p].lz;
        t[p].lz=0;
    }
    return;
}
void cg(ll p,ll l,ll r,ll k)
{
    if(p==1&&l>r) return;//非常重要,可以防止l>r的情况
    if(t[p].l>=l&&t[p].r<=r)
    {
        t[p].x+=k;
        t[p].lz+=k;
        return;
    }
    sd(p);
    ll mid=(t[p].l+t[p].r)/2;
    if(l<=mid) cg(2*p,l,r,k);
    if(r>mid) cg(2*p+1,l,r,k);
    t[p].x=max(t[2*p].x,t[2*p+1].x);
    return;
}
ll gt(ll p,ll l,ll r)
{
    if(p==1&&l>r) return 0;//同上
    if(t[p].l>=l&&t[p].r<=r) return t[p].x;
    sd(p);
    ll mid=(t[p].l+t[p].r)/2;
    ll ans=-0x3f;
    if(l<=mid) ans=max(ans,gt(2*p,l,r));
    if(r>mid) ans=max(ans,gt(2*p+1,l,r));
    return ans;
}
/*上面为线段树*/
bool cmp(xd s1,xd s2){return s1.l<s2.l;}//排序用
ll lb(ll w,ll l,ll r)//二分找(上文提到的)最大的j
{
	ll g=0;
	while(l<=r)
	{
		ll mid=(l+r)/2;
		if(x[mid].l<=w) g=mid,l=mid+1;
		else r=mid-1;
	}
	return g;
}
int main()
{
	cin>>n>>k;
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
	sort(a+1,a+n+1);//排序
	while(l<n)//求线段
	{
		l++;
		while(a[r+1]-a[l]<=k&&r<n) r++;
		x[++cnt].l=l;
		x[cnt].r=r;
	}
	bd(1,1,n);//建树
	for(int i=1;i<=n;i++)  cg(1,i,i,x[i].r-x[i].l+1);//将长度加入线段树
	for(int i=1;i<=n;i++)
	{
		int now=lb(x[i].r,i+1,n);//求(上文提到的)最大的j
		int r2=x[now].r;
		if(r2>x[i].r) ans=max(ans,r2-x[i].l+1);
		else ans=max(ans,x[i].r-x[i].l+1);//更新
		int l2=gt(1,now+1,n);//在j+1~n中,求长度最大的一段
		ans=max(ans,x[i].r-x[i].l+1+l2);//更新
	}
	return printf("%lld",ans),0;
}
```


---

## 作者：飞翔 (赞：2)

简单的DP题目，预处理出每个点向左、向右拓展的距离，再枚举分割点打擂台。

```c
uses math;
var
  i,j,n,k,ans:longint;
    a,fl,fr:array[0..100001]of longint;
procedure qsort(l,r:longint);
var
  i,j,temp,mid:longint;
begin
  i:=l; j:=r;
  mid:=a[(l+r) div 2];
  repeat
    while a[i]<mid do inc(i);
    while a[j]>mid do dec(j);
    if i<=j then
    begin
      temp:=a[i];a[i]:=a[j];a[j]:=temp;
      inc(i);dec(j);
    end;
  until i>j;
  if l<j then qsort(l,j);
  if i<r then qsort(i,r);
end;
begin
  readln(n,k);
    for i:=1 to n do read(a[i]);
    qsort(1,n);
    i:=1;
    for j:=1 to n do begin
      while a[j]-a[i]>k do inc(i);
        fl[j]:=max(fl[j-1],j-i+1);//向左
    end;
    j:=n;
    for i:=n downto 1 do begin
      while a[j]-a[i]>k do dec(j);
        fr[i]:=max(fr[i+1],j-i+1);//向右
    end;
    for i:=1 to n-1 do ans:=max(ans,fl[i]+fr[i+1]);//枚举分割点
    write(ans);
end.
```

---

## 作者：jins3599 (赞：1)

## 题目大意

给定n个数，求取出最大的两堆数字，使得每堆中的每个元素之间的差值不大于k。

## 思路

我们先把这个数列排序一遍，题目就转化为了求两个最大的不相交的区间，使得区间中的每个数之间差值不大于k。

难点是在于处理不相交的。

一个比较显然的思路是枚举断点，然后再找左右区间的最大区间。

直接暴力的去找的话，复杂度是$O(n^3)$的。

我们考虑可以把这个找最大区间的过程预处理一下。

我们给定两个数组$pre[i],suf[i]$

$pre[i]$代表从$i$出发向左的最大区间

$suf[i]$代表从$i$出发向右的最大区间

我们用$l,r$来代表这个区间的左右端点。

我们观察到$l,r$是单调不降的。

因此我们就可以线性处理出$suf,pre$
。

最后再枚举断点统计答案即可。

```cpp
#include <bits/stdc++.h>

using namespace std;

const int maxn = 50000 + 5;
int n , k, a[maxn];
int pre[maxn] , suf[maxn];

int main () {
    scanf("%d%d" , &n , &k);
    for(int i = 1 ; i <= n ; ++ i) scanf("%d" , a + i);
    sort(a + 1 , a + 1 + n);
    int l , r;
    l = r = 1;
    for(r = 1 ; r <= n ; ++ r) {
        while(a[r] - a[l] > k) l ++;
        pre[r] = r - l + 1;
        pre[r] = max(pre[r] , pre[r - 1]);
    }
    l = r = n;
    for(l = n ; l >=1 ; -- l) {
        while(a[r] - a[l] > k) r --;
        suf[l] = r - l + 1;
    }
    int ans = 0;
    for(int i = 1 ; i <= n ; ++ i) {
        ans = max(ans , suf[i] + pre[i - 1]);
    }
    printf("%d\n" , ans);
    return 0;
}
```

---

## 作者：ueettttuj (赞：1)

[题目](https://www.luogu.org/problem/P3143)

这道题目可以先处理处数组$ans1$和$ans2$。现将钻石按大小从小到大排序。$ans1[i]$表示在$1\sim i$钻石中必须取第$i$颗钻石后能得到的钻石个数最大值，$ans2[i]$表示在$i\sim n$钻石中必须取第$i$颗钻石后能得到的钻石个数最大值。对于这两个数组，可以二分预处理出来。

然后就是统计答案。对于第$i$颗钻石，我们令它放在第二个架子上，然后再在$1\sim i-1$ 中找出最多的放钻石方案放在第一个架子上。也就是$ans[i]=max(ans1[j])+ans2[i] \ \ (1\le j \le i-1)$。然后答案就是$max(ans[i])\ \ (1\le i \le n)$

对于$ans[i]=max(ans1[j])+ans2[i] \ \ (1\le j \le i-1)$这条式子，我们显然不能$O(n^2)$暴力去求，所以可以使用树状数组$O(nlogn)$。其实$O(n)$也行,我们对于记一个$mx=max(ans1[j])\ \ (1\le j \le i-1)$
就行了(理解不了看代码)

贴代码

```cpp
#include <bits/stdc++.h>
using namespace std;
long long n,k;
long long a[50010];
long long ans1[50010],ans2[50010];
long long tree[50010];
/* 
void add(long long x,long long y){
	for(;x<=n;x+=(x&-x)) tree[x]=max(tree[x],y);
}
long long ask(long long x){
	long long anss=0;
	for(;x;x-=(x&-x)) anss=max(anss,tree[x]);
	return anss;
}
*/
int main(){
	scanf("%lld %lld",&n,&k);
	for(long long i=1;i<=n;i++)
		scanf("%lld",&a[i]);
	sort(a+1,a+n+1);
	for(long long i=1;i<=n;i++){
		long long l=1,r=i;
		while(l<=r){       //二分 
			long long mid=(l+r)/2;
			if(a[i]-a[mid]<=k){
				ans1[i]=max(ans1[i],(i-mid+1));
				r=mid-1;
			}
			else l=mid+1;
		}
	}
	for(long long i=1;i<=n;i++){
		long long l=i,r=n;
		while(l<=r){      //二分 
			long long mid=(l+r)/2;
			if(a[mid]-a[i]<=k){
				ans2[i]=max(ans2[i],(mid-i+1));
				l=mid+1;
			}
			else r=mid-1;
		}
	}
	long long ans=0;
	long long mx=ans1[1]; //mx存最大的ans1[j] 
	for(long long i=2;i<=n;i++){
		ans=max(ans,mx+ans2[i]);
		mx=max(mx,ans1[i]);
	}
	printf("%lld\n",ans);
	return 0;
} 
```

---

