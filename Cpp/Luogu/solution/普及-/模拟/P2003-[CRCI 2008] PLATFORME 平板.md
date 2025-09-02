# [CRCI 2008] PLATFORME 平板

## 题目描述

为了进行一种游戏，现决定搭造一些平板，而各个平板的地址已经选定。基于最普遍的认识，没有任何支持物的平板不可能漂浮在空中。说的更精确些，任意一平板的两端必需有支柱或者它在另一块平板上。

你会得到各个平板在坐标系中的坐标（如左下图）。每一块平板的坐标都是由它的高度（与地板间的垂直距离）和它的水平方位（开始和结束）决定的。每个支柱都距它支撑的平板的边缘半个单位（如图）。

算出支持所有平板的支柱的总长度。

 ![](https://cdn.luogu.com.cn/upload/pic/994.png) 



## 样例 #1

### 输入

```
3
1 5 10
3 1 5
5 3 7
```

### 输出

```
14```

# 题解

## 作者：mzyy1001 (赞：19)

这题的N比较水（只有100）~~n^3都能过。。。~~
两个循环暴搜一遍就行，连排序都不用。就是在判断时注意两块板末尾对齐或开头对齐是可以支撑的，但末尾对开头是不能支撑的就行，一下贴代码。
```
#include<bits/stdc++.h>
using namespace std;
struct Node
{
	int y,x1,x2;
}a[1001];
int main()
{
	int n;
	cin >> n;
	int ans = 0;
	for(int i = 1;i <= n;i++)
		scanf("%d%d%d",&a[i].y,&a[i].x1,&a[i].x2);
	for(int i = 1;i <= n;i++)
	{
		int y = a[i].y,x1 = a[i].x1,x2 = a[i].x2;  
		int h1 = 0,h2 = 0;
		for(int j = 1;j <= n;j++)
		{
			if(i == j) 
				continue;
			if(a[j].y >= y) 
				continue;
			if(a[j].x2 > x1 && a[j].x1 <= x1)
				h1 = max(h1,a[j].y);
			if(a[j].x2 >= x2 && a[j].x1 < x2)
				h2 = max(h2,a[j].y);
		}
	//	printf("%d %d %d %d %d %d^^\n",y,a[i].x1,a[i].x2,i,h1,h2); //调试用的
		ans += y * 2 - h1 - h2;
	}
	cout << ans;
	return 0;
 } 
```

---

## 作者：Makasukaka (赞：18)

# 写一篇关于线段树做法的题解
## 事先声明：
此题不需要用线段树也可拿到满分。原因是n<=100 这么小的数据范围直接导致了n^2可做。

## n^2 

我们考虑对于每一个板子，用float 存左钉子和右钉子的位置。O(n) 寻找满足可插钉的最高高度。事实上，由于相对高点的板子所计算的距离一定是小于底板子的距离的 所以每次取Min一定满足存在性和最优性。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#define LL long long
#define INF 0x7fffffff
using namespace std;
const int N=1e2+5;
struct leb{
	int y,x1,x2;
}a[N];
LL ans=0;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int main(){
	int n=read();
	for(int i=1;i<=n;++i){
		a[i].y=read();
		a[i].x1=read();
		a[i].x2=read();
	}
	for(int i=1;i<=n;++i){
		int c1=INF,c2=INF,f1=0,f2=0;
		double l=a[i].x1+0.5,r=a[i].x2-0.5;
		for(int j=1;j<=n;++j){
			if(i==j)continue;
			int ll=a[j].x1,rr=a[j].x2;
			if(l>ll&&l<rr&&a[i].y>a[j].y)c1=min(c1,a[i].y-a[j].y),f1=1;
			if(r>ll&&r<rr&&a[i].y>a[j].y)c2=min(c2,a[i].y-a[j].y),f2=1;
		}
		if(!f1)c1=min(c1,a[i].y);
		if(!f2)c2=min(c2,a[i].y);
		ans+=(c1+c2);
	}
	printf("%lld\n",ans);
	return 0;
}
```

## nlogn+nlogh

我们考虑：对于每一个板子i，什么板子j是有可能成为它的支撑板。充要条件即为 y[j]<y[i]。

这样，我们不妨把板子按照y值升序排序。这样，对于当前处理的板子i，在它之前处理的板子j 一定有可能成为它的支撑板。

问题即转换为，对于板子的左右两钉子点 l,r。
查询l,r位置处的 最大高度y。 相当于单点查

如果我们处理完了当前版i，那么i 就又对后面的板子有贡献了。 相当于区间修改

我们想到了线段树

注意：我用的线段树的每个子段是闭区间。这导致了一个查询的问题。此题我是查[l,l+1] 与 [r-1,r]的 这就会使边界相交的板子误判可插钉 事实上差0.5个单位长度

为了解决此问题，我一开始考虑修改询问或建树方式。但是不太好改。。 我们不如转换一下思路，既然我们此题的(l,r)是开区间，我的线段树是闭区间，那么可以令我区间修改时，不修改[l,r] 而是修改[l+1,r-1] 这样就相当于开区间了。

于是此题就有了一个相对优的做法。复杂度nlogh+nlogn 
复杂度解释：对板子排序是nlogn 线段树修改查询是nlogh 
h为x的域。
****
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#define LL long long
using namespace std;
const int N=1e4+5;
struct leb{
	int y,x1,x2;
}a[N];
struct segtree{
	int l,r,v,tag;
}tr[N<<2];
LL ans=0;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
inline bool cmp(const leb &a,const leb &b){
	return a.y<b.y;
}
inline void build(int k,int s,int t){
	tr[k].l=s;tr[k].r=t;
	if(s==t)return ;
	int mid=(s+t)/2;
	build(k<<1,s,mid);
	build((k<<1)|1,mid+1,t);
}
inline void pushdown(int k){
	int w=tr[k].tag;
	tr[k<<1].v=max(tr[k<<1].v,w);
	tr[k<<1].tag=max(tr[k<<1].tag,w);
	tr[(k<<1)|1].v=max(tr[(k<<1)|1].v,w);
	tr[(k<<1)|1].tag=max(tr[(k<<1)|1].tag,w);
	tr[k].tag=0;
}
inline int query(int k,int s,int t){
	int l=tr[k].l,r=tr[k].r;
	if(s==l&&t==r)return tr[k].v;
	if(tr[k].tag)pushdown(k);
	int mid=(l+r)/2;
	if(t<=mid)return query(k<<1,s,t);
	else if(s>mid)return query((k<<1)|1,s,t);
	else return max(query(k<<1,s,mid),query((k<<1)|1,mid+1,t));
}
inline void insert(int k,int s,int t,int w){
	int l=tr[k].l,r=tr[k].r;
	if(s==l&&t==r){
		tr[k].v=max(tr[k].v,w);
		tr[k].tag=w;
		return ;
	}
	if(tr[k].tag)pushdown(k);
	int mid=(l+r)/2;
	if(t<=mid)insert(k<<1,s,t,w);
	else if(s>mid)insert((k<<1)|1,s,t,w);
	else {
		insert(k<<1,s,mid,w);
		insert((k<<1)|1,mid+1,t,w);
	}
	tr[k].v=max(tr[k<<1].v,tr[(k<<1)|1].v);
}
int main(){
	int n=read();
	for(int i=1;i<=n;++i){
		a[i].y=read();
		a[i].x1=read();
		a[i].x2=read();
	}
	sort(a+1,a+1+n,cmp);
	build(1,1,N);
	for(int i=1;i<=n;++i){
		int l=a[i].x1,r=a[i].x2;
		int d=query(1,l,l+1);
		ans+=(a[i].y-d);
		//printf("%d ",a[i].y-d);
		d=query(1,r-1,r);
		ans+=(a[i].y-d);
		//printf("%d\n",a[i].y-d);
		insert(1,l+1,r-1,a[i].y);
	}
	printf("%lld\n",ans);
	return 0;
}
```



---

## 作者：HOOCCOOH (赞：7)

这题N太小了，导致暴力也能过，但是我们要追求更高效率的算法。

事实上，可以在O(NlogN+NlogH)时间内解决这个问题。

我们可以维护[1,H]区间中每个x的高度，先给平板从低到高排序，一个个加入，只用查询两点的当前高度以及修改平板覆盖区间范围即可，所以当然是用线段树啦=w=

所以即使N,H在10^5范围也没事啦

```cpp

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <cctype>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int iRead()
{
    int ret = 0;
    int ch;
    while(!isdigit(ch = getchar()) && ch != '-');
    bool bm = (ch == '-'); if(bm) ch = getchar();
    while(ret = ret * 10 + (ch - '0'), isdigit(ch = getchar()));
    return bm ? -ret : ret;
}

const int N = 103;
const int M = 10003;
struct iT
{
    int s;
    int val;
    bool mark;
    iT *l, *r;
}ss[M * 4], *sp = ss;

void iDown(iT *c)
{
    if(c->mark)
    {
        c->l->val = c->r->val = c->val;
        c->l->mark = c->r->mark = true;
        c->mark = false;
    }
}

iT *iMake(int l, int r)
{
    iT *c = sp++;
    if(l + 1 == r)
        *c = (iT){1, 0, false, NULL, NULL};
    else
    {
        int m = l + r >> 1;
        *c = (iT){r - l, 0, false, iMake(l, m), iMake(m, r)};
    }
    return c;
}

void iSet(iT *c, int l, int r, int val)
{
    if(l <= 0 && r >= c->s)
    {
        c->val = val;
        c->mark = true;
        return;
    }
    iDown(c);
    int m = c->s >> 1;
    if(l < m)
        iSet(c->l, l, r, val);
    if(m < r)
        iSet(c->r, l - m, r - m, val);
}

int iQuery(iT *c, int pos)
{
    if(c->s == 1)
        return c->val;
    iDown(c);
    int m = c->s >> 1;
    if(pos < m)
        return iQuery(c->l, pos);
    else
        return iQuery(c->r, pos - m);
}

struct iQ
{
    int y;
    int a, b;
    bool operator<(const iQ &r) const {return y < r.y;}
}arr[N];

int main()
{
    iT *head = iMake(0, M);
    int n = iRead();
    for(int i = 0; i < n; ++i)
    {
        int y = iRead(),
            a = iRead(),
            b = iRead();
        arr[i] = (iQ){y, a, b};
    }
    sort(arr, arr + n);
    int ans = 0;
    for(int i = 0; i < n; ++i)
    {
        ans += arr[i].y - iQuery(head, arr[i].a);
        ans += arr[i].y - iQuery(head, arr[i].b - 1);
        iSet(head, arr[i].a, arr[i].b, arr[i].y);
    }
    printf("%d\n", ans);
    
    return 0;
}

```

---

## 作者：重回巅峰！ (赞：4)

这题我卡了很多次，提交的好几次

先将此题的坑爹之处告诉大家：

1. 因为支柱在平板边缘往里0.5距离，为了方便计算，必须将读入的数据扩大两倍。

2。数组不能开小，我刚开始一看N最大为100，就只开了800的数组，结果RE7个点。然后开到8000，RE3个点。

然后开到80000，RE2个点，最后我一狠心，开了80W的数组，居然AC了。

3. 这题不能用暴力水过，因为错过了这种水题，就没有好的题目来练线段树了



```cpp
type
  hx=record
        left,right,value:longint;
      end;
var
  node:array[0..800000]of hx;
  a:array[0..800000]of hx;
  n,m,left,right,i,j,ans:longint;
procedure sort(l,r: longint);
var i,j,x: longint;
    y:hx;
begin
  i:=l;j:=r;x:=a[(l+r) div 2].value;
  repeat
    while a[i].value<x do inc(i);
    while x<a[j].value do dec(j);
    if not(i>j) then
    begin
       y:=a[i];a[i]:=a[j];a[j]:=y;
       inc(i);j:=j-1;
    end;
  until i>j;
  if l<j then sort(l,j);
  if i<r then sort(i,r);
end;
function max(a,b:longint):longint;
begin
  if a>b then exit(a) else exit(b);
end;
procedure build(u,left,right:longint);
var mid:longint;
begin
  node[u].right:=right; node[u].left:=left;
  if (left=right) then exit;
  mid:=(left+right) div 2;
  build(u*2,left,mid);
  build(u*2+1,mid+1,right);
end;
procedure change(u,left,right,k:longint);
begin
  if (node[u].left>right)or(node[u].right<left) then exit;
  if (node[u].left>=left)and(node[u].right<=right) then
  node[u].value:=max(node[u].value,k);
  change(u*2,left,right,k);
  change(u*2+1,left,right,k);
end;
function query(u,left,right:longint):longint;
begin
  if (node[u].left>right)or(node[u].right<left) then exit(0);
  if (node[u].left>=left)and(node[u].right<=right) then exit(node[u].value);
  exit(max(query(u*2,left,right),query(u*2+1,left,right)));
end;
begin
  readln(n); left:=maxlongint; right:=-maxlongint;
  for i:=1 to n do
  begin
    readln(a[i].value,a[i].left,a[i].right);
    a[i].left:=a[i].left*2;
    a[i].right:=a[i].right*2;
    if a[i].left<left then left:=a[i].left;
    if a[i].right>right then right:=a[i].right;
  end;
  build(1,left,right);
  sort(1,n);
  for i:=1 to n do
  begin
    ans:=ans+2*a[i].value;
    ans:=ans-query(1,a[i].left+1,a[i].left+1)
            -query(1,a[i].right-1,a[i].right-1);
    //writeln(ans);
    change(1,a[i].left,a[i].right,a[i].value);
  end;
  writeln(ans);
end.

```

---

## 作者：谬悠 (赞：4)

我！这个蒟蒻！决定发一篇不需要线段树、搜索、枚举的题解！

就是模拟！~~没办法我用不来线段树~~

由于范围很小，我们可以用一个数组来记录那个位置的当前高度，当那个地方不为零时是可以搭在已有木板上的，but！我们不是在木板边缘搭也不是在中间，而是分别在左+0.5和右-0.5的位置上，那么怎么处理呢Qwq？

我们可以给左右坐标乘2鸭！

注意：范围扩大了两倍，数组至少开到2w

主要在代码里解释吧

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
int ans,tu[40050];
struct node {//储存题目输入的信息、、、因为要按高度排序所以没办法喽
	int a,b,c;
} num[200];
void jie(int a,int b,int c) {//模拟核心
	b=b+b;//加法比乘法块
	c=c+c;
	if(tu[b+1]!=0)ans+=(a-tu[b+1]);//询问这两个点是否有木板存在
	else ans+=a;
	if(tu[c-1]!=0)ans+=(a-tu[c-1]);
	else ans+=a;
	for(int j=b; j<=c; j++) {//更新线段图，模拟放置木板
		tu[j]=a;
	}
}
bool com(node x,node y){
	return x.a<y.a;
}
int main() {
	int n,a,b,c;
	cin>>n;
	for(int i=0; i<n; i++) {
		cin>>num[i].a>>num[i].b>>num[i].c;//读入
	}
	sort(num,num+n,com);//按高度先排序，从低到高，不然10分
	for(int i=0;i<n;i++)jie(num[i].a,num[i].b,num[i].c);//一块一块堆叠模拟，嘟嘟嘟
	cout<<ans<<endl;
	return 0;
}
```

望通过Qwq


---

## 作者：wuzhoupei (赞：4)

这道题可以用暴力水过；

我们先按照高度从低到高排序，然后记一个h[]数组；

h[i]代表x轴i这个位置目前最高的一个板；

由于柱子只能撑住边缘的半个单位；

那我们就把坐标上的线改为点；

就是用(x，y)这个点来代表原来(x，y)到(x+1，y)这段板

所以只需要每次放一个木板时，更新下这个木板的从l到r-1这一段的h[]数组；

就好了；


cpp
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#define II int
#define B bool
#define R register
#define I 123456
using namespace std;


struct node {
    II y,l,r;
}aa[I];

II n,ans;

II h[I];

B maP(node a1,node a2) 
{
    if(a1.y==a2.y) return a1.l<a2.l;
      return a1.y<a2.y;
    // 从低到高排序; 
}


int main()
{
    freopen("1.in","r",stdin);
    
    scanf("%d",&n);
    for(R II i=1;i<=n;i++)
    {
        scanf("%d%d%d",&aa[i].y,&aa[i].l,&aa[i].r);
        aa[i].r--;
        // 化线段为点； 
    }
    
    sort(aa+1,aa+n+1,maP);
    
    for(R II i=1;i<=n;i++)
    {
        ans+=aa[i].y*2-h[aa[i].l]-h[aa[i].r];
        // 放板； 
        for(R II j=aa[i].l;j<=aa[i].r;j++)
        {
            h[j]=max(h[j],aa[i].y);
        }// 更新h[]数组； 
    }
    
    printf("%d\n",ans);
    exit(0);
}
```

---

## 作者：常清静矣 (赞：3)

#### 【前言】
这道题已有的题解已经把方法都说明了。补一个图解，帮助大家理解。
#### 【思路】
这道题和洛谷里一道染色的题是一样的，不过更简单一点。

核心思路，就是投影，把所有木板都投影到底层。

1.初始：

| 高度 |  |  |  |  |  |  |  |  |  |  |  |
| -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: |
| 4 |  |  |  |  |  |  |  |  |  |  |  |
| 3 |  |  |  |  |  |  |  |  |  |  |  |
| 2 |  |  |  |  |  |  |  |  |  |  |  |
| 1 |  |  |  |  |  |  |  |  |  |  |  |
| 0 | 0 | 0 | 0 | 0 | 0 |  0| 0 |0  | 0 |0  | 0 |
2.第一块木板出现：

| 高度 |  |  |  |  |  |  |  |  |  |  |  |
| -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: |
| 4 |  |  |  |  |  |  |  |  |  |  |  |
| 3 |  |  |  |  |  |  |  |  |  |  |  |
| 2 |  |  |  |  |  |  |  |  |  |  |  |
| 1 |  |  |  |  |  | a |a |a |a |a |  |
| 0 | 0 | 0 | 0 | 0 | 0 |  0| 0 |0  | 0 |0  | 0 |
3.第一块木板落下：

| 高度 |  |  |  |  |  |  |  |  |  |  |  |
| -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: |
| 4 |  |  |  |  |  |  |  |  |  |  |  |
| 3 |  |  |  |  |  |  |  |  |  |  |  |
| 2 |  |  |  |  |  |  |  |  |  |  |  |
| 1 |  |  |  |  |  |  | | | | |  |
| 0 | 0 | 0 | 0 | 0 | 1 |  1| 1 |1 | 1 |1  | 0 |
4.第二块木板出现：

| 高度 |  |  |  |  |  |  |  |  |  |  |  |
| -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: |
| 4 |  |  |  |  |  |  |  |  |  |  |  |
| 3 |  |  | b | b | b | b |  |  |  |  |  |
| 2 |  |  |  |  |  |  |  |  |  |  |  |
| 1 |  |  |  |  |  |  | | | | |  |
| 0 | 0 | 0 | 0 | 0 | 1 |  1| 1 |1 | 1 |1  | 0 |
5.第二块木板落下：

| 高度 |  |  |  |  |  |  |  |  |  |  |  |
| -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: |
| 4 |  |  |  |  |  |  |  |  |  |  |  |
| 3 |  |  |  |  |  |  |  |  |  |  |  |
| 2 |  |  |  |  |  |  |  |  |  |  |  |
| 1 |  |  |  |  |  |  | | | | |  |
| 0 | 0 | 0 | 3 | 3 | 3 |  3| 1 |1 | 1 |1  | 0 |
抽象的思路如上所示。

 _具体到这道题因为支柱在内侧0.5处，所以把木板左右端点✖2，方便处理。此外不确定木板的高度顺序，还需要对木板的高度做一个排序；_ 

**流程：输入所有木板→按高度排序→由低到高处理每一个木板→输出答案**

#### 【代码】
```c
#include<iostream>
#include<algorithm>
using namespace std;
const int nA=105,wA=10005  ;
int n;
struct Node{
	int h,l,r;
}B[nA];	//木板
int S[wA*2]={0};	//底层高度
int ans=0;

void publish(){
	cout<<ans<<endl;
}

void deal(){
	ans=0;
	for(int i=0;i<n;i++){
		ans+=B[i].h-S[B[i].l+1]+B[i].h-S[B[i].r-1];
		for(int j=B[i].l+1;j<B[i].r;j++){
			S[j]=B[i].h;
		}
	}
}

bool cmp(Node a,Node b){
	return a.h<b.h;
}

void creat(){
	cin>>n;
	for(int i=0;i<n;i++){
		int h,l,r;
		cin>>h>>l>>r;
		B[i].h=h;
		B[i].l=2*l;
		B[i].r=2*r;
	}
	sort(B,B+n,cmp); //
}

int main(){
	creat();
	deal();
	publish();
	return 0;
}

```



---

## 作者：Limerick (赞：3)

# STO  _**YGP**_  orz
###  n²枚举搞定.
#### 为了方便,规定平板所占的区间为平板区间.
#### 这题可以直接枚举每一个平板是否有另一个平板可以搭，因为n<=100.
#### 那么就好办了, _为什么这么说咧_ ,因为对于每个平板,只有两种情况:
#### 1.这个平板的左端被包含在某个平板区间里且高度大于这里的某一个平板.
#### 2.这个平板的右端被包含在某个平板区间里且高度大于这里的某一个平板.
#### 有的同学要问了, _为什么没有被包含咧？_ ,因为这种情况都满足以上两种情况,因此没必要再分支一种情况来讨论.
#### 然后取高度最小值加起来就行了
#### 有的同学又要问了,为什么有的平板区间虽然满足以上条件但却并另一个平板挡住了而导致搭不上,这种情况也算搭上了呢？原因很简单,因为取的是最小值,如果被挡住了,那么证明当前平板到这个挡住它的平板的支柱长度更小,那么上面这种情况的最小值会被更新,自然也就不会搭上这块平板了.
#### Code:
~~~#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<ctime>
using namespace std;
const int N=1005;
int n,ans,x=1000000000,y2=1000000000;
struct Node{
    int y,x1,x2;
}a[N];
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d%d%d",&a[i].y,&a[i].x1,&a[i].x2);//结构体:分别记录第i个平板的长度和起始坐标
    }
    for(int i=1;i<=n;i++){
        x=1000000000,y2=1000000000;//由于要取最小值,故初值设为最大
        for(int j=1;j<=n;j++){
            if(i==j){//肯定不会枚举相同平板的
                continue;
            }
            if(a[i].x1>=a[j].x1&&a[i].x1<a[j].x2&&a[i].y>a[j].y){//如果当前平板的左端在某一个平板区间中且高度大于此平板(PS:>=是因为支柱在平板内半个单位处)
                x=min(x,a[i].y-a[j].y);//那么当前平板的左端可以搭在这个平板上,注意取最小值
            }
            if(a[i].x2<=a[j].x2&&a[i].x2>a[j].x1&&a[i].y>a[j].y){//如果当前平板的右端在某一个平板区间中且高度大于此平板(PS:<=是因为支柱在平板内半个单位处)
                y2=min(y2,a[i].y-a[j].y);//那么当前平板的右端可以搭在这个平板上,注意取最小值
            }
        }
        ans+=min(x+y2,min(y2+a[i].y,min(x+a[i].y,2*a[i].y)));//ans加上所有情况中支柱长度的最小值(PS:如果当前平板左端或右端没有可搭的地方,那么就只能搭在地上,这样支柱就是x+a[i].y或y2+a[i].y,如果左端和右端都没有可搭的地方,那么只能都搭在地上,这样支柱就是2*a[i].y)
    }
    printf("%d\n",ans);//输出ans
    return  0;
}~~~
#### 不吝赐教.

---

## 作者：hongzy (赞：2)

## 排序 + 模拟

大致思路如下：把所有平板按高度排序，每次从左右两个端点往下找一个高度最大的平板，计算长度，就确定它为最优解(高度已排序)

还有一个值得注意的地方：判断j是否能支撑i时：

- j的左端点等于i的右端点 或 j的右端点等于i的左端点是不行的

- i的左端点等于j的左端点 或 i的右端点等于j的右端点是可以的

看起来有些暴力，不过复杂度只是O(n^2)，并且常数较优

```cpp
#include <iostream>
#include <algorithm>
using namespace std;

struct board { //平板 
	int l, r, h;
	bool operator <(const board b) const {return h < b.h;} //重载运算符 按高度比较 
} A[110];

int N, ans;

bool Check(int l, int r, int x, bool left) {         //判断端点x能不能靠[l,r]支撑 
	if(l < x && x < r) return true;                 //平板中央 
	if(left && l == x && x < r) return true;        //i的左端点等于j的左端点
	if(!left && l < x && x == r) return true;       //i的右端点等于j的右端点
	return false;
}

int main() {
	cin >> N;
	A[0].l = A[0].h = 0;
	A[0].r = 1e9;                                   //最底部的超大平板 
	for(int i=1; i<=N; i++) cin >> A[i].h >> A[i].l >> A[i].r;
	sort(A+1, A+N+1);                               //按高度排序 
	for(int i=1; i<=N; i++) {
		int lcost = -1, rcost = -1;                //两边需要的最短支柱长度 
		for(int j=i-1; j>=0; j--) {
			if(lcost != -1 && rcost != -1) break; //找到解立即退出 
			if(A[j].h < A[i].h) {
				if(lcost == -1 && Check(A[j].l, A[j].r, A[i].l, 1)) lcost = A[i].h - A[j].h;
				if(rcost == -1 && Check(A[j].l, A[j].r, A[i].r, 0)) rcost = A[i].h - A[j].h;
			}
		}
		ans += lcost + rcost;
	}
	cout << ans << endl;
	return 0;
}
```

---

## 作者：ghj1222 (赞：1)

我想问问草酸大神为啥要用线段树。。。我差点望而却步了。。。

d[i]就是表示第i个格子最上边的板子的高度(因为支柱是要摞在最上面的)。

首先将所有板子排序(貌似不用)，然后一个一个放，并动态更新d数组。

ans每次加上板子上两个端点d数组的和(注意有一个要+1。。。)

幸好这题没有可能有板子长度为1的坑(题目已经明确告诉了)

```cpp
#include <iostream>
#include <algorithm> 
using namespace std;
struct board
{
    int x1,x2,y;
}a[101];
bool cmp(board a,board b)
{
    return a.y<b.y;
}
int main()
{
    int d[10001]={0},n,ans=0;
    cin >> n;
    for(int i=1;i<=n;i++)
        cin >> a[i].y >> a[i].x1 >> a[i].x2;
    sort(a+1,a+1+n,cmp);
    for(int i=1;i<=n;i++)
    {
        ans+=a[i].y*2-d[a[i].x1+1]-d[a[i].x2];
        for(int j=a[i].x1+1;j<=a[i].x2;j++)
            d[j]=a[i].y;
    }
    cout << ans << endl;
    return 0;
}
```

---

## 作者：LittleZ (赞：1)

很简单的一道模拟题，连排序都不要。在最后加上第（n+1）个平板，高度为0，左端坐标为0，右端坐标为10001，表示地面。思路是对于每一块平板i，都有左端的最短支撑长度和右端的最短支撑长度，于是将左、右端最短支撑长度（lmin，rmin）设为maxlongint，然后暴搜一遍，满足以下条件更新lmin：

·第j块平板的高度小于第i块平板

·第j块平板的坐标包括第i块平板的左端坐标

·两块平板高度之差小于lminrn则lmin变为两块平板高度之差。

右端最短支撑长度类似。

扫完一遍后把lmin和rmin加入最后的答案。

```delphi

var
  y,x1,x2:array[1..101]of longint;
  n,i,j,ans,lmin,rmin:longint;
begin
  readln(n);
  for i:=1 to n do readln(y[i],x1[i],x2[i]);
  inc(n);
  y[n]:=0; x1[n]:=0; x2[n]:=10001;
  ans:=0;
  for i:=1 to n-1 do
  begin
    lmin:=maxlongint;
    rmin:=maxlongint;
    for j:=1 to n do
      if (i<>j) and (y[i]>y[j]) then
      begin
        if ((x1[j]<(x1[i]+0.5)) and ((x1[i]+0.5)<x2[j])) then
          if (y[i]-y[j])<lmin then lmin:=y[i]-y[j];
        if ((x1[j]<(x2[i]-0.5)) and ((x2[i]-0.5)<x2[j])) then
          if (y[i]-y[j])<rmin then rmin:=y[i]-y[j];
      end;
    inc(ans,lmin+rmin);
  end;
  writeln(ans);
end.

```

---

## 作者：rfsfreffr (赞：0)

我的方法是全场最暴力的....

### 时间复杂度：最坏$O(tn^2)$,最好$O(n)$，总体效率为$O(n*ans)$(ans为最后输出的答案),平均效率$O(kn^2)$(k不会太大)

我的思路是这样的：先按板子的高度排序，再从最小的开始，先建造左边的支柱，后建造右边的支柱。

造的时候，每下降一格，都看看有没有落在其他的板子上。

~~本来以为实现很容易的，可我被double与int玩了~~

# 代码:

~~~
#include<bits/stdc++.h>
#define for_int register int
#define endl '\n'
#define ll long long
#define ld long double
#define op operator
#define max(a, b)  (!((a) < (b)) ? (a) : (b))
#define min(a, b)  ((a) < (b) ? (a) : (b))
using namespace std;
struct oi {
	int t;
	double x1,x2;//一定要用double!!!!!!!!!!!!!!!!!!
};
bool cmp(oi x,oi y) {
	return x.t<y.t;
}
oi a[10001];
int n,ans;
void draw(oi x,int k) {
	x.x1=x.x1+0.5;
	x.x2=x.x2-0.5;

	for(double i=x.t; i>0; i--) {//建造左支柱
		int f=1;
		ans++;//建造
		for(for_int j=1; j<=n; j++) {
			if(j!=k) {//不能落在自己身上
				if(a[j].t==i) {//判断高度是否相符
					if(x.x1>a[j].x1) {//判断是否能落在上面
						if(x.x1<a[j].x2) {
							ans--;
							f=0;
							break;//退出
						}
					}

				}
			}

		}
		if(!f) break;

	}

	for(double i=x.t; i>0; i--) {//建造右支柱
		int f=1;
		ans++;
		for(for_int j=1; j<=n; j++) {
			if(j!=k)
				if(a[j].t==i&&x.x2>a[j].x1&&x.x2<a[j].x2) {
					ans--;
					f=0;
					break;
				}
		}
		if(!f) break;

	}

	return;
}

int main() {
	cin>>n;
	for(for_int i=1; i<=n; i++) {
		scanf("%d%lf%lf",&a[i].t,&a[i].x1,&a[i].x2);
	}
	sort(a+1,a+1+n,cmp);
	for(for_int i=1; i<=n; i++) {
		draw(a[i],i);//建造支柱
	}
//	cout<<(a[2].t==3&&a[3].x1>a[2].x1&&a[3].x1<a[2].x2);
	cout<<ans<<endl;
	return 0;
}
~~~


## 拓展:

显然在板子的时候可以，利用桶排（t不大）,这样时间可以优化到$O(kn)$~~与SPFA接近耶~~

代码留给你们思考


---

## 作者：kgory (赞：0)

楼下竟然用线段树，%%%，而我这种蒟蒻只会用贪心

直接按高度从小到大排就行（从大到小也行，个人习惯）。

接着枚举每一块木板，分左右两个端点向后找（为什么？因为左右两个端点除了高度相同以外没有联系，左边行的右边不一定行，反之亦然，又因为从小到大排的，找最小高度，当然向后找啦）。

然后就是判断左右端点的可行性，有两种情况：

1.端点重合（不解释了）

2.当前端点一定要严格地大于现在枚举的木板的左端点，严格地小于现在枚举的木板的右端点，因为要求支柱在平台的里面半个单位

最后，行的就把它们的高度差加入答案，进行下一次枚举。

上代码（~~我知道你最关注的是这个~~）

```cpp
#include <cstdio>
#include <algorithm>
#include <iostream>
using namespace std;

struct Node {  //横坐标，纵坐标，高度
	int x;
	int y;
	int h;
}a[1005];

bool cmp (Node xx,Node yy) { //按高度直接排
	return xx.h<yy.h;
}

int main () {
	int n;
	scanf ("%d",&n);
	int i;
	for (i=1;i<=n;i++)
		scanf ("%d%d%d",&a[i].h,&a[i].x,&a[i].y);//注意输入顺序
	sort (a+1,a+n+1,cmp);
	int j,ans=0;
	a[0].h=0;
	a[0].x=-1;
	a[0].y=100001;
    //由于从1开始，所以要赋个0号一个极小值
	for (i=1;i<=n;i++) {
		for (j=i-1;j>=0;j--)
			if ((a[i].x>a[j].x&&a[i].x<a[j].y&&a[i].h>a[j].h)||a[i].x==a[j].x) {
            //判断可行性，两种情况
				ans+=a[i].h-a[j].h;
				break;
			}
		for (j=i-1;j>=0;j--)
			if ((a[i].y>a[j].x&&a[i].y<a[j].y&&a[i].h>a[j].h)||a[i].y==a[j].y) {
            //判断可行性，两种情况
				ans+=a[i].h-a[j].h;
				break;
			}
	}
	printf ("%d\n",ans); //结束
	return 0;
}
附：我的代码可能还有不完美的地方，请私信找我，谢谢。
```

---

## 作者：_扶笙_ (赞：0)

P党真是越来越少了，我给P党发福利了

线段树好难啊，蒟蒻我只会用计数（数据很小）

我的大体思路：按照高度排序，然后计数，如果左端点或者右端点已经有了，用当前的告诉减去原来的高度即可。有一点，这题是线，从1~3只有2个，而不是3个，也许有些人题目没读懂才做不出来吧QAQ

人民喜闻乐见的代码：

```
var n,i,s,j:longint;
a,b,c,f:array[0..10000] of longint;//f保存每一个点到当前的高度（0表示当前这个点还没有出现过）a表示高度，b是左端点，c是右端点
procedure sort(l,r: longint);//快排（选择也可以）
var i,j,x,y: longint;
begin
i:=l;j:=r;x:=a[(l+r) div 2];//i是左指针，j是右指针，x是中间值
repeat
while a[i]<x do inc(i);//比中间小，左指针往后移
while x<a[j] do dec(j);//比中间大，右指针往前移
if not(i>j) then//在范围内
  begin
  y:=b[i];b[i]:=b[j];b[j]:=y;//交换b
  y:=c[i];c[i]:=c[j];c[j]:=y;//交换c
  y:=a[i];a[i]:=a[j];a[j]:=y;//交换a
  inc(i);j:=j-1;//往中间寻找
  end;
until i>j;//直到越界
if l<j then sort(l,j);
if i<r then sort(i,r);//继续递归下去
end;
begin
readln(n);//读入
for i:=1 to n do
  begin
  readln(a[i],b[i],c[i]);
  dec(c[i]);//这里是把点变成线来存放，由于1~3只有2个点，所以右端点-1（左端点+1也可以）
  end;
sort(1,n);//按照高度排序
for i:=1 to n do
  begin
  s:=s+a[i]-f[b[i]]{如果左端点已经有了，那么就用当前的高度减去原来的高度}+a[i]-f[c[i]]{如果右端点已经有了，那么就用当前的高度减去原来的高度}；//如果都没有的话-0等于没-
  for j:=b[i] to c[i] do f[j]:=a[i];//计数
  end;
writeln(s);//最后输出
end.
```
神犇请路过~
抄代码可耻！


---

## 作者：Deny_小田 (赞：0)

# 能用暴力的用暴力就AC了，何乐而不为呢？

## 实在不行再加几个剪枝。

# 我（们）追求的是AC而不是优美的代码。


# 把LZ大神的代码翻译成C++








```cpp
#include <cstdio>
typedef long long LL;
const LL inf = 1000000000,size = 105;
LL x1[size],x2[size],y[size],n,leftmin,rightmin,ans = 0;
int min(int a,int b){ return a<b?a:b; }
int main(int argc, char const *argv[]){
    scanf("%lld",&n);
    for(int i = 1; i <= n; i++) scanf("%lld %lld %lld",&y[i],&x1[i],&x2[i]); 
    n++;
    y[n] = x1[n] = 0;   x2[n] = 10001;
    for(int i = 1; i < n; i++){
        leftmin = rightmin = inf;
        for(int j = 1; j <= n; j++){
            if((i != j)&&(y[i] > y[j])){
                if((x1[j] < (x1[i]+0.5))&&((x1[i]+0.5) < x2[j])) leftmin = min(leftmin,y[i]-y[j]);
                if((x1[j] < (x2[i]-0.5))&&((x2[i]-0.5) < x2[j])) rightmin = min(rightmin,y[i]-y[j]);
            }
        }
        ans += (leftmin+rightmin);
    }
    printf("%lld\n",ans);
    return 0;
}
```

---

