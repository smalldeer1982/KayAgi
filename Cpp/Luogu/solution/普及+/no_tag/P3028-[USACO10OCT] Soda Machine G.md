# [USACO10OCT] Soda Machine G

## 题目描述

To meet the ever-growing demands of his N (1 &amp;lt;= N &amp;lt;= 50,000) cows, Farmer John has bought them a new soda machine. He wants to figure out the perfect place to install the machine.

The field in which the cows graze can be represented as a one-dimensional number line. Cow i grazes in the range A\_i..B\_i (1 &amp;lt;= A\_i &amp;lt;= B\_i; A\_i &amp;lt;= B\_i &amp;lt;= 1,000,000,000) (a range that includes its endpoints), and FJ can place the soda machine at any integer point in the range 1..1,000,000,000.  Since cows are extremely lazy and try to move as little as possible, each cow would like to have the soda machine installed within her grazing range.

Sadly, it is not always possible to satisfy every cow's desires. Thus FJ would like to know the largest number of cows that can be satisfied.

To demonstrate the issue, consider four cows with grazing ranges 3..5, 4..8, 1..2, and 5..10; below is a schematic of their grazing ranges:

```cpp

         1   2   3   4   5   6   7   8   9  10  11  12  13
         |---|---|---|---|---|---|---|---|---|---|---|---|-...
                 aaaaaaaaa
                     bbbbbbbbbbbbbbbbb
         ccccc           ddddddddddddddddddddd
```
As can be seen, the first, second and fourth cows share the point 5, but the third cow's grazing range is disjoint.  Thus, a maximum of 3 cows can have the soda machine within their grazing range.


有N个人要去膜拜JZ，他们不知道JZ会出现在哪里，因此每个人有一个活动范围，只要JZ出现在这个范围内就能被膜拜，

伟大的JZ当然希望膜拜他的人越多越好，但是JZ不能分身，因此只能选择一个位置出现，他最多可以被多少人膜拜呢，

这个简单的问题JZ当然交给你了


## 说明/提示

If the soda machine is placed at location 5, cows 1, 2, and 4 can be satisfied. It is impossible to satisfy all four cows.


## 样例 #1

### 输入

```
4 
3 5 
4 8 
1 2 
5 10 
```

### 输出

```
3 
```

# 题解

## 作者：Starria的脑残粉 (赞：26)

显然。。可以直接快排一下然后瞎搞啊。。

类似于区间差分

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,sum,ans;
struct lsg{int x,y;}a[2000000];
bool pd(lsg x,lsg y){return x.x<y.x||x.x==y.x&&x.y>y.y;}//快排
int main(){
    ios::sync_with_stdio(false);
    cin>>n;for (int i=1;i<=n;i++)cin>>a[i].x>>a[i+n].x,a[i].y=1,a[i+n].y=-1;//差分
    sort(a+1,a+1+n*2,pd);
    for (int i=1;i<=n*2;i++)sum+=a[i].y,ans=max(ans,sum);
    cout<<ans<<endl;
}
```

---

## 作者：Watermatter (赞：6)

膜拜那些用数据结构的大佬。。。

我还是弱弱地发一个差分+离散化的代码吧，感觉挺慢的，但个人感觉简洁明了。

差分思想我不多赘述，不懂的同学请右转百度。。

差分模板
```cpp
int delta[];//差分数组
for(int i=1;i<=n;i++)
{
	int l,r;//需要修改的左端点和右端点
    delta[l]++;                 
    delta[r+1]--;                     
}                     
for(int i=1;i<=(题目要求的范围);i++)
{
之后按题意来。。。
}
```


关键就是这个离散化，考试的时候没有离散化，数据范围过大，导致只有40分（洛谷上没有交过，但题解中似乎看到有人没用离散化qwq）。。。 以后可得长点心了。。。

完整代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define maxn 100001
struct node
{
    ll x,y;
}num[maxn];
ll op[maxn],t[maxn],n,cnt=0,h[maxn],ans;
int main()
{
    scanf("%lld",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%lld%lld",&num[i].x,&num[i].y);
        op[++cnt]=num[i].x;
        op[++cnt]=num[i].y;
    }
    sort(op+1,op+1+cnt);
    int m=unique(op+1,op+1+cnt)-op-1;
    for(int i=1;i<=n;i++)
    {
        ll l=lower_bound(op+1,op+1+cnt,num[i].x)-op;
        ll r=lower_bound(op+1,op+1+cnt,num[i].y)-op;
        h[l]++;
        h[r+1]--;
    }
    for(int i=1;i<=2*n;i++)
    {
        h[i]+=h[i-1];
        ans=max(ans,h[i]);
    }
    printf("%lld",ans);
    return 0;
}
```
有问题在右方写下你的评论，谢谢！



---

## 作者：nstk0513 (赞：5)

题目的本质就是求数列上的一个点最多被多少个区间所覆盖。

此题可以用线段树来做，但数据量很大，需要先离散化，预防MLE。

离散化：

建立一个c数组，往里面添加所有输入的点编号。为避免重复，可利用STL的list去重，再依次加入c数组中。为预防TLE，用二分查找寻找点的位置。

线段树：

对每一个范围，在线段树中添加1，直接添加到lazy上就行，change时是否下放无所谓（我写了），query时统一下放。

下放lazy用函数pushdown。

之后在最底层点寻找lazy最大值，即结果。

以下是代码：


```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <list>
using namespace std;
const int MAXN=500005;//数组要开大一些，否则会RE/WA
struct Node
{
    int left,right;
    int lazy;
}t[2*MAXN];
int n,a[MAXN],b[MAXN],c[2*MAXN],size;
list<int> lst;//定义STL list
list<int>::iterator it;//迭代器
//建树
void buildtree()
{
    int ln=1;
    while(ln<size) ln*=2;
    for(int i=ln; i<=ln*2; i++)
    {
        t[i].left=t[i].right=i-ln+1;
        t[i].lazy=0;
    }
    for(int i=ln-1; i>=1; i--)
    {
        t[i].left=t[i<<1].left;
        t[i].right=t[i<<1|1].right;
        t[i].lazy=0;
    }
}
void change(int id,int l,int r)
{
    if(t[id].left==l && t[id].right==r)
    {
        t[id].lazy++;
        return;
    }
    if(t[id].lazy!=0)
    {
        t[id<<1].lazy+=t[id].lazy;
        t[id<<1|1].lazy+=t[id].lazy;
        t[id].lazy=0;
    }
    if(t[id<<1].right>=r) change(id<<1,l,r);
    else if(t[id<<1|1].left<=l) change(id<<1|1,l,r);
    else
    {
        change(id<<1,l,t[id<<1].right);
        change(id<<1|1,t[id<<1|1].left,r);
    }
}
//下放lazy函数
void pushdown(int id)
{
    if(t[id].left==t[id].right) return;
    if(t[id].lazy!=0)
    {
        t[id<<1].lazy+=t[id].lazy;
        t[id<<1|1].lazy+=t[id].lazy;
        t[id].lazy=0;
    }
    pushdown(id<<1);
    pushdown(id<<1|1);
}
int query()
{
    pushdown(1);
    int ans=-1,ln=1;
    while(ln<size) ln*=2;
    for(int i=ln; i<ln*2; i++) ans=max(ans,t[i].lazy);
    return ans;
}
//二分查找
int binarySearch(int x)
{
    int l=1,r=size,mid;
    while(l<=r)
    {
        mid=(l+r)/2;
        if(c[mid]==x) return mid;
        else if(c[mid]>x) r=mid-1;
        else l=mid+1;
    }
    return mid;
}
int main()
{
    scanf("%d",&n);
    for(int i=1; i<=n; i++)
    {
        scanf("%d%d",&a[i],&b[i]);
        lst.push_back(a[i]);//将每个点编号放入list内
        lst.push_back(b[i]);
    }
    lst.sort();//list必须排序，unique函数去重只能去相邻的
    lst.unique();//去重
    for(it=lst.begin(); it!=lst.end(); it++)
    {
        size++;//在循环时顺便求出c数组大小
        c[size]=*it;
    }
    buildtree();//不能过早建树，要先计算完size
    for(int i=1; i<=n; i++)
    {
        change(1,binarySearch(a[i]),binarySearch(b[i]));
    }
    printf("%d\n",query());
    return 0;
}
```

---

## 作者：fls233666 (赞：2)

### 题意简述

有 $n$ 个区间 $[A_i,B_i]$ ，找一个点 $x$ ，使 $x$ 被最多的区间覆盖。

### 解题思路

首先可以注意到的一个难点是区间的坐标范围：$1 \le A_i,B_i \le 10^9$。这显然对于直接开数组进行标记造成了困难。

但进一步观察可以发现，区间的数量 $n$ 还是很小的：$1 \le n \le 5 \times 10^4$，这说明输入数据中最多只会出现 $2n$ 个不同的区间端点。

**那么考虑离散化，将出现的各个区间端点映射到 $[1,2n]$ 这个范围内。** 把每一个区间的左右端点 $A_i,B_i$ 存到另一个数组中，然后排序，去重。那么最后区间端点在数组中对应的下标就是离散化后得到的数字。

离散化后，由于最多只有 $2n$ 个不同数字，所以考虑开一个大小为 $2n$ 的数组进行标记。进一步思考会发现，直接暴力地一个一个点去改是 $O(n^2)$ 的，显然过不去。

**于是考虑进行差分，将 $O(n)$ 的区间修改操作转化为 $O(1)$ 的单点修改操作和一次 $O(n)$ 求前缀和的操作。** 对于一个区间 $[l,r]$ ，可以在数组下标为 $l$ 的位置 $+1$ ，在数组下标为 $r+1$ 的位置 $-1$ 。对所有区间操作完成后，对每个位置求前缀和，即可得到每个位置被多少个区间覆盖。在所有位置中取最大值即可。

至此，此题得解。

### 解题代码

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm> 
#define ll long long
#define rgt register int
#define qmx(a,b) a<b?b:a
using namespace std;

const int mxn = 5e4+4;

int b[mxn<<1],l[mxn],r[mxn],c[mxn<<1];
int n,ans,lb;
//b[]为离散化数组，c[]为差分数组

inline int q(int x){   //离散化后的查询函数
	return lower_bound(b+1,b+1+lb,x)-b;
}

int main(){
	scanf("%d",&n);
	for(rgt i=1;i<=n;i++){
		scanf("%d%d",&l[i],&r[i]);
		lb++;
		b[lb]=l[i];
		lb++;
		b[lb]=r[i];
	}  //读入数据并把区间段点加入离散化数组
	sort(b+1,b+lb+1);  //排序
	lb=unique(b+1,b+lb+1)-(b+1);  //去重
	for(rgt i=1;i<=n;i++){
		c[q(l[i])]++;
		c[q(r[i])+1]--;
	}   //对所有的区间差分
	for(rgt i=1;i<=lb;i++){
		c[i]+=c[i-1];
		ans=qmx(c[i],ans);
	}  //求前缀和并取最大值
	printf("%d",ans);  //得到答案
	return 0;
}
```


---

## 作者：jgvccc (赞：1)

小蒟蒻不太会离散化，这里提供一些其他思路。

首先考虑差分，但是发现每一头奶牛的位置可以到达 $10^9$ 这么大，内存肯定会炸，所以直接排除。

***

换个角度想，每个奶牛的放牧区域都有左右端点。如果只看一头奶牛，就会发现在左端点的时候，这个区域的奶牛数量 $+1$；在右端点的时候这个数量会 $-1$。可以把这两个值看做端点的权值（因为小蒟蒻太懒不想特判这个点是左端点还是右端点了）。

于是大概思路就出来了。

$n$ 头奶牛的放牧区域有 $2n$ 个端点，给每个端点都设一个权值（$1$ 或者 $-1$，左端点设 $1$，右端点设 $-1$）然后以端点坐标为关键字从小到大排序。

此时新创建一个变量 $x$。排序之后，从左往右扫，每到一个新的点，$x$ 就要加上在这个点的所有端点的权值（更新能喝到汽水的奶牛数量），然后和最终答案取 $\max$ 即可。

需要注意的是，所有的右端点需要在原来的基础上向右移动一位，否则会出问题。

最后，奉上代码。

```cpp
#include<bits/stdc++.h>
using namespace std;

int n,t,tt,dcnt;
//dcnt用来记录目前“点”的次数

int cnt,ans,now;

struct node
{
    int pos;
    int val;
}a[100001];

bool cmp(node a,node b)
{
    return a.pos<b.pos;
}
//结构体快排

signed main()
{
    std::ios::sync_with_stdio(false);
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>t>>tt;
        a[++dcnt].pos=t;
        a[dcnt].val=1;
        a[++dcnt].pos=tt+1;
        //这里坐标要+1，否则区间会提早结束
        a[dcnt].val=-1;
    }
    sort(a+1,a+dcnt+1,cmp);
    for(int i=1;i<=dcnt;i++)
    {
        if(a[i].pos!=now)
        {
            //注意一定要等到更新完一个值再取max
            //不然会WA一个点
            now=a[i].pos;
            ans=max(cnt,ans);
        }
        cnt+=a[i].val;
    }
    cout<<ans;
	return 0;
}
```

~~求求啦管理员大大给过吧~~

---

## 作者：RainFestival (赞：1)

用朴素算法~~MLE~~

离散化~~（我也不知道是不是正解）~~

每个区间左端点值为+1，右端点值为-1

按照区间位置快排，如位置相同，则+1排在-1前面（贪心）

最后扫一遍，统计最大值，再输出~~（不需要树状数组或线段树，虽然我也会用它们）~~

下面是代码：

（友情提示：虽然没有坑，但请勿抄袭）


91分：

```pascal
type
  arr=array[0..1000005] of longint;
var
  b,e:arr;
  i,j,k,s,maxs,minb,maxe,n:longint;
procedure qsort(l,r:longint;var a:arr);
var
  i,j,t,x:longint;
begin
  i:=l;
  j:=r;
  x:=a[(i+j) div 2];
  repeat
    while a[i]<x do inc(i);
    while a[j]>x do dec(j);
    if i<=j then
              begin
                t:=a[i];
                a[i]:=a[j];
                a[j]:=t;
                inc(i);
                dec(j);
              end;
  until i>j;
  if l<j then qsort(l,j,a);
  if i<r then qsort(i,r,a);
end;
begin
  minb:=$7fffffff;
  maxe:=$80000000;
  maxs:=$80000000;
  readln(n);
  for i:=1 to n do
    begin
      read(b[i],e[i]);
      inc(e[i]);
      if b[i]<minb then minb:=b[i];
      if e[i]>maxe then maxe:=e[i];
    end;
  qsort(1,n,b);
  qsort(1,n,e);
  j:=1;
  k:=1;
  for i:=minb to maxe do
    begin
      while b[j]=i do
        begin
          inc(s);
          inc(j);
        end;
      while e[k]=i do
        begin
          dec(s);
          inc(k);
        end;
      if s>maxs then maxs:=s;
      //writeln(i,':',s);
      if j>n then break;
    end;
  writeln(maxs);
end.
```
AC：

```pascal
type
  arr=array[0..200005] of longint;
var
  a,b:arr;
  i,s,maxs,m,n,x,y:longint;
procedure qsort(l,r:longint);
var
  i,j,t,x1,x2:longint;
begin
  i:=l;
  j:=r;
  x1:=a[(i+j) div 2];
  x2:=b[(i+j) div 2];
  repeat
    while (a[i]<x1) or (a[i]=x1) and (b[i]>x2) do inc(i);
    while (a[j]>x1) or (a[j]=x1) and (b[j]<x2) do dec(j);
    if i<=j then
              begin
                t:=a[i];
                a[i]:=a[j];
                a[j]:=t;
                t:=b[i];
                b[i]:=b[j];
                b[j]:=t;
                inc(i);
                dec(j);
              end;
  until i>j;
  if l<j then qsort(l,j);
  if i<r then qsort(i,r);
end;
begin
  maxs:=$80000000;
  readln(n);
  for i:=1 to n do
    begin
      read(x,y);
      inc(m);
      a[m]:=x;
      b[m]:=1;
      inc(m);
     // inc(y);
      a[m]:=y;
      b[m]:=-1;
    end;
  qsort(1,m);
  for i:=1 to m do
    begin
      s:=s+b[i];
      if s>maxs then maxs:=s;
    end;
  writeln(maxs);
end.
```

谢谢巨佬们观赏！！！

---

## 作者：Celebrate (赞：1)

我的博客：

```cpp
https://blog.csdn.net/zsyzClb/article/details/84196644
```

根据观察，可以发现区间都非常大达到10^9如果直接暴力是O（10^9n）肯定会超时，所以我采用了离散化，将区间离散

这样可以把最大时间复杂度降低到O（n^2）

代码：

```cpp
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;
inline int read(){
	int x=0,f=0;char s=getchar();
	while(!isdigit(s))f|=s=='-',s=getchar();
	while( isdigit(s))x=(x<<1)+(x<<3)+s-48,s=getchar();
	return f==0?x:-x;
}
const int N=5e4+10;
struct LSnode{
	int x,z,p;
	inline bool operator<(const LSnode &k)const{
		return x<k.x;
	}
}b[N<<1];int a[N<<1];
int n;
int sum[N<<1];
int main(){
	n=read();
	for(int i=1;i<=n;i++){
		b[2*i-1].x=read();
		b[2*i  ].x=read();
		b[2*i-1].p=2*i-1;
		b[2*i  ].p=2*i;
	}
	sort(b+1,b+2*n+1);
	b[1].z=1;
	for(int i=2;i<=(n<<1);i++){
		if(b[i].x==b[i-1].x)b[i].z=b[i-1].z;
		else b[i].z=b[i-1].z+1;
	}
	for(int i=1;i<=(n<<1);i++)a[b[i].p]=b[i].z;
	int maxx=0;
	for(int i=1;i<=n;i++){
		for(int j=a[2*i-1];j<=a[2*i];j++)
			sum[j]++,maxx=max(maxx,sum[j]);
	}
	printf("%d\n",maxx);
	return 0;
}

```

但是这个时间复杂度是O（n^2）还是会超时两个点，所以我想可以在区间修改时优化一下

因为上面的代码每次修改都是要从左到右每一个点都+1，所以我们可以考虑用前缀和的方式优化，因此只需要在每个区间的其实点+1，在区间的结束点+1的位置上-1，统计时不断的加这个点的sum值就好了

AC代码

```cpp
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;
inline int read(){
	int x=0,f=0;char s=getchar();
	while(!isdigit(s))f|=s=='-',s=getchar();
	while( isdigit(s))x=(x<<1)+(x<<3)+s-48,s=getchar();
	return f==0?x:-x;
}
const int N=5e4+10;
struct LSnode{
	int x,z,p;
	inline bool operator<(const LSnode &k)const{
		return x<k.x;
	}
}b[N<<1];int a[N<<1];
int n;
int sum[N<<1];
int main(){
	n=read();
	for(int i=1;i<=n;i++){
		b[2*i-1].x=read();
		b[2*i  ].x=read();
		b[2*i-1].p=2*i-1;
		b[2*i  ].p=2*i;
	}
	sort(b+1,b+2*n+1);
	b[1].z=1;
	for(int i=2;i<=(n<<1);i++){
		if(b[i].x==b[i-1].x)b[i].z=b[i-1].z;
		else b[i].z=b[i-1].z+1;
	}
	for(int i=1;i<=(n<<1);i++)a[b[i].p]=b[i].z;
	int maxx=0;
	for(int i=1;i<=n;i++){
		sum[a[2*i-1]]++;
		sum[a[2*i]+1]--;
	}
	int s=0;
	for(int i=1;i<=b[n<<1].z;i++)s+=sum[i],maxx=max(maxx,s);
	printf("%d\n",maxx);
	return 0;
}

```

---

## 作者：jzqjzq (赞：1)

我的做法比较傻。。。（是不是我数据结构题写太多写傻了？）

其实可以很快地看出这是可以用支持区间修改单点求值的东西维护一下的

所以离散化之后直接上树状数组了

其他做法我不是很了解。。。

代码就不多解释了

```cpp
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>
#include <ctime>
#include <map>
#include <queue>
#include <cstdlib>
#include <string>
#include <climits>
#include <set>
#include <vector>
using namespace std;
int f[1000001],x[1000001],y[1000001],b[1000001];
int n,cnt=0;
inline void add(int x,int y){for(;x<=cnt;x+=x&-x)f[x]+=y;}
inline int sum(int x){int ans=0;for(;x;x-=x&-x)ans+=f[x];return ans;}//树状数组
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d%d",&x[i],&y[i]);
        b[++cnt]=x[i];b[++cnt]=y[i];
    }
    sort(b+1,b+cnt+1);
    for(int i=1;i<=n;i++){
        x[i]=lower_bound(b+1,b+cnt+1,x[i])-b;
        y[i]=lower_bound(b+1,b+cnt+1,y[i])-b;//离散化
        add(x[i],1);add(y[i]+1,-1);//区间修改（加）
    }
    int ans=0;
    for(int i=1;i<=cnt;i++)ans=max(ans,sum(i));//单点求值
    printf("%d",ans);
    return 0;
}
```

---

## 作者：Cloote (赞：0)

首先可以看到区间端点的数据范围：$0<x\le y<10^9$，而 n 的范围明显小很多，故考虑使用离散化。

离散化后，有一个很容易想到的暴力：枚举每一段区间，将这个区间所包含的范围都 +1。最后再遍历一遍，求出最大值即可。

示例代码：

~~~cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e4+5;
int n,a[N<<1],sum[N];

struct node{
	int x,y;
}cow[N];

int main(){
	ios::sync_with_stdio(false);
	cin>>n;
	int tot=0;
	for(int i=1;i<=n;i++){
		cin>>cow[i].x>>cow[i].y;
		a[++tot]=cow[i].x;
		a[++tot]=cow[i].y;
	}
	sort(a+1,a+tot+1);
	int m=unique(a+1,a+tot+1)-a-1,maxi=0;
	for(int i=1;i<=n;i++){
		cow[i].x=lower_bound(a+1,a+m+1,cow[i].x)-a;//离散化
		cow[i].y=lower_bound(a+1,a+m+1,cow[i].y)-a;
		for(int j=cow[i].x;j<=cow[i].y;j++) maxi=max(maxi,++sum[j]);
	}
	cout<<maxi;
	return 0;
}
~~~

这样你可以拿到 72pts。

于是我们考虑一种类似于扫描线的想法。首先将 cow 数组按照左端点从小到大的顺序排列，每次遇到一个左端点便 +1，遇到右端点便 -1。

判断是否遇到右端点可以使用优先队列维护小根堆，遇到左端点时将右端点加进队列里。

代码如下：

~~~cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e4+5;
int n,a[N<<1],sum[N];

struct node{
	int x,y;
}cow[N];

struct Node{
	int x;
	bool operator < (const Node &x) const{//优先队列默认大根堆，这里要改成小根堆
		return x.x<this->x;
	}
};

bool cmp(node x,node y){
	if(x.x==y.x) return x.y<y.y;
	return x.x<y.x;
}

int main(){
	ios::sync_with_stdio(false);
	cin>>n;
	int tot=0;
	for(int i=1;i<=n;i++){
		cin>>cow[i].x>>cow[i].y;
		a[++tot]=cow[i].x;
		a[++tot]=cow[i].y;
	}
	sort(a+1,a+tot+1);
	int m=unique(a+1,a+tot+1)-a-1,cnt=0,ansi=0;
	for(int i=1;i<=n;i++){
		cow[i].x=lower_bound(a+1,a+m+1,cow[i].x)-a;
		cow[i].y=lower_bound(a+1,a+m+1,cow[i].y)-a;
	}
	sort(cow+1,cow+n+1,cmp);
	priority_queue<Node>q;
	tot=1;
	for(int i=cow[1].x;i<=cow[n].x;i++){
		 while(i==cow[tot].x){//使用while防止端点重合的情况，下面同理
		 	cnt++;
			Node tmp={cow[tot].y};
		 	q.push(tmp);
		 	tot++;
		 	ansi=max(ansi,cnt);
		 }
		 while(q.empty()==false&&i==q.top().x){
		 	cnt--;
		 	q.pop();
		 }
	}
	cout<<ansi;
	return 0;
}
~~~

---

## 作者：lsj2009 (赞：0)

## 题目大意
给定 $n$ 个区间 $[l_i,r_i]$，找到一个点，使之包含它的区间最多。
## 思路
我们将题目换一种方法来理解：给定 $n$ 个区间 $[l_i,r_i]$ 将其中的每个元素都给 $+1$，求问最后的所有元素最大值。

是的，聪明的你一下子就看了出来，这是一道裸的差分。

```cpp
for(int i=1;i<=n;i++) {
	int l,r;
	scanf("%d%d",&l,&r);
	d[l]++; d[r+1]--;
}
```
但...这样就完了吗？不，我们看见 $l_i,r_i\le10^9$，数组无疑存不下这么大的空间，就算存的下，我们将 $0$ 至 $\max\{r_i\}$ 一一遍历仍会超时。

这是，我们需要使用一种方法叫做离散化，这里不作过多介绍。
## Code:
```cpp
#include<bits/stdc++.h>
#define pd push_back
#define pb pop_back
#define mk make_pair
//#define int long long
#define PII pair<int,int>
#define _for(a,b,c) for(int a=b;a<=c;a++)
#define _rep(a,b,c) for(int a=b;a>=c;a--)
using namespace std;
template <typename T> inline void read(T& x) {
	x=0; T f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') { if(ch=='-') f=-1; ch=getchar(); }
	while(ch>='0'&&ch<='9') { x=(x<<1)+(x<<3)+(ch&15); ch=getchar(); }
	x=x*f;
	return;
}
template <typename T,typename ...Arg> inline void read(T& x,Arg& ...arg){
	read(x); read(arg...);
}
int power(int a,int b) {
	int ans=1;
	do {
		if(b&1) ans*=a; a*=a;
	} while(b>>=1);
	return ans;
}
const int N=1e5+5;
int d[N],l[N],r[N],v[N],tot,n,ans;
signed main() {
	read(n);
	_for(i,1,n)
		read(l[i],r[i]),v[++tot]=l[i],v[++tot]=r[i];
	sort(v+1,v+tot+1); //排序
	tot=unique(v+1,v+tot+1)-(v+1); //去重
	_for(i,1,n) {
//		printf("(%d,%d)+=1\n",lower_bound(v+1,v+tot+1,l[i])-v,lower_bound(v+1,v+tot+1,r[i])-v);
		++d[lower_bound(v+1,v+tot+1,l[i])-v],--d[lower_bound(v+1,v+tot+1,r[i])-v+1]; //将离散化后的 l[i]~r[i] 区间+1
	}
	_for(i,1,tot+1)
		ans=max(ans,d[i]+=d[i-1]); //做前缀和，还原数组
	printf("%d",ans);
	return 1;
}

```

---

