# [USACO16DEC] Counting Haybales S

## 题目描述

Farmer John 刚刚将他的 $N$ 个干草捆（$1 \leq N \leq 100,000$）安排在他农场的一维道路上的各个位置。为了确保它们之间的间距合适，请帮助他回答 $Q$ 个查询（$1 \leq Q \leq 100,000$），每个查询询问在道路的特定区间内有多少个干草捆。

## 样例 #1

### 输入

```
4 6
3 2 7 5
2 3
2 4
2 5
2 7
4 6
8 10```

### 输出

```
2
2
3
4
1
0```

# 题解

## 作者：Dr_殇 (赞：13)

#我很可怜p党，他们的函数库没有我们cpp多，sort都没有。这道题，cpp党很好做，因为algorithm库里有两个叫upper\_bound和lower\_bound的函数，他们的作用就是二分找比某个数小并与它最接近的那个数的下标和二分找比某个数大并与它最接近的那个数的下标。知道这两个函数后，特别简单。


##代码如下：




```cpp
#include <ctime>
#include <cmath>
#include <cstdio>
#include <string>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>//头文件准备，algorithm必须加，要不然编译不过
using namespace std;
int n,m,a[100005];
int main(){
    scanf ("%d %d",&n,&m);//读入
    for (int i=1;i<=n;i++){
        scanf ("%d",&a[i]);
    }
    sort (a+1,a+1+n);//注意：二分查找要排序，要不然就是在乱找
    for (int i=1;i<=m;i++){
        int x,y;
        scanf ("%d %d",&x,&y);//读入两个数
        printf("%d\n",upper_bound(a+1,a+n+1,y)-lower_bound(a+1,a+n+1,x));//注意：y是后面一个数，所以是先查后面一个数，再相减
    }
    while (1);//反抄袭
    return 0;
}

```

---

## 作者：z1431346079 (赞：8)

发现好像没人用离线算法的，于是来发一波题解

该题强化版本（P2163 [SHOI2007]园丁的烦恼）//同样的方法

**大体思路：离散化+树状数组维护前缀和**

对坐标离散化并排序后，便直接进行前缀和操作。（因为后面的点的x坐标必定大于等于前面的点的x坐标）

对于之后每一个按x坐标读入的点可进行加入草垛点**或**查询比该点x坐标小的点的数量两种操作。

鉴于线段树的代码量，为何不用树状数组来维护前缀和呢？

附上代码（有点丑，请多包涵）


------------

```cpp
/**
*　　┏┓　　　┏┓+ +
*　┏┛┻━━━┛┻┓ + +
*　┃　　　　　　　┃
*　┃　　　━　　　┃ ++ + + +
*  ████━████+
*  ◥██◤　◥██◤ +
*　┃　　　┻　　　┃
*　┃　　　　　　　┃ + +
*　┗━┓　　　┏━┛
*　　　┃　　　┃ + + + +Code is far away from 　
*　　　┃　　　┃ + bug with the animal protecting
*　　　┃　 　 ┗━━━┓ 神兽保佑,代码无bug　
*　　　┃ 　　　　　　 ┣┓
*　　  ┃ 　　　　　 　┏┛
*　    ┗┓┓┏━┳┓┏┛ + + + +
*　　　　┃┫┫　┃┫┫
*　　　　┗┻┛　┗┻┛+ + + +
*/
#include<bits/stdc++.h>//万能头文件
using namespace std;
inline int read()
{
    int f=1,num=0;
    char ch=getchar();
    while(0==isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
    while(0!=isdigit(ch)) num=(num<<1)+(num<<3)+ch-'0',ch=getchar();
    return num*f;
}//标配快读
const int N=350000;
int l[N],x[100010],top=0;
int tot=0;int a[N],b[N];
int n,m;
int ans[100050][3];//储存答案
int t[N];//树状数组

struct node{
	int f,id,x;
}q[N];

inline int find(int x){
	int L=1,R=top;
	while(L<=R){
		int mid=(L+R)>>1;
		if(l[mid]>=x){R=mid-1;}
		else L=mid+1;
	}
	return L;
}//用二分寻找离散化后的点

bool cmp(node a,node b){
	if(a.x==b.x)return a.f<b.f;
	return a.x<b.x;
}//先考虑所在位置，再优先处理有草垛的点

inline int lowbit(int x){return x&-x;}//树状数组

inline void add(int x)//树状数组加入点
{
	for(register int i=x;i<=tot;i+=lowbit(i)){
		t[i]+=1;//依次向上传递值
	}
}
inline int query(int x)查询编号比x小的点总数
{
	int sum=0;
	for(register int i=x;i;i-=lowbit(i)){
		sum+=t[i];//从编号x向下查询
	}
	return sum;
}
int main(){
	n=read();m=read();
	for(register int i=1;i<=n;i++){
		x[i]=read();//读入草垛坐标
		l[++top]=x[i];压入第一个队列
	}
	for(register int i=1;i<=m;i++){
		a[i]=read();//读入询问区间左端点
        l[++top]=a[i];
		b[i]=read();//右端点
        l[++top]=b[i];
	}
	sort(l+1,l+1+top);//注意先排序
	for(register int i=1;i<=n;i++){
		x[i]=find(x[i]);//离散化
		q[++tot].x=x[i];//压入第二个队列
	}
	for(register int i=1;i<=m;i++){
		a[i]=find(a[i]);b[i]=find(b[i]);//离散化
		q[++tot].x=a[i]-1;q[tot].id=i;q[tot].f=1;
		q[++tot].x=b[i];q[tot].id=i;q[tot].f=2;
        //压入询问区间左端点与右端点、询问区间编号
	}
	sort(q+1,q+1+tot,cmp);//再排一次序
	for(register int i=1;i<=tot;i++){
		if(!q[i].f)add(i);//如果是草垛，加点
		else{
			ans[q[i].id][q[i].f]=query(i);//计算前缀和
		}
	}
	for(register int i=1;i<=m;i++){
		cout<<ans[i][2]-ans[i][1]<<endl;//输出答案
	}
	return 0;
}
```

开开心心写完第一篇题解。

---

## 作者：a2920353120 (赞：3)

> ### $p3184$题解
>
> # 整体思路：排序、二分查找
> 
> ### 我发一个手写的非递归二分的题解
>
> ### ```二分思路```
>
> 二分之前先特判一下
>
> 如果左右边界都小于最小位置(A<a[1]&&B<a[1])或左右边界都大于最大位置(A>a[n]&&B>a[n])
>
> 那么输出0
>
>如果当前要查找的小于$a[1]$最小位置返回**1**,如果当前要查找的大于$a[n]$返回**n**
>

> 令$kl = 1, kr = a[n]$即左右边界
>
>```注意kr = a[n]```**右边界**初始值不能是**INF**否则有可能**炸int**并且会浪费很多的时间
>
> ### 当 $kl$ ```<``` $kr$时
>
> 令 $mid = (kl + kr + 1) >> 1$(等价于$mid = (kl + kr + 1) / 2$)
>
> ### $0)$如果a[mid] == 查找值 $return$  $mid;$
>
> ### $1)$如果$a[mid - 1] <$ 查找值 $< a[mid]$ 
> 
> #### $i.$如果查找的是左区间(A) 
>
> $return$  $mid;$
>
> #### $ii.$如果查找的是右区间(B)
>
> $return$ $mid-1;$
>
> ### $2)$如果$a[mid] <$ 查找值 $< a[mid + 1]$
> 
> #### $i.$如果查找的是左区间(A) 
>
> $return$  $mid + 1;$
>
> #### $ii.$如果查找的是右区间(B)
>
> $return$ $mid;$
>
> ### $3)$如果查找值不在区间$[a[mid-1],a[mid+1]]$
> #### $i.$ 如果$a[mid] >$ 查找值 
>
> 令$kr = mid$在左半部分查找
>
> #### $ii.$ else
>
> 令$kl = mid - 1$ 在右半部分查找
>
> ### $4)$查找完毕
>
> **输出右边界位置 - 左边界位置 + 1**
>
----
```代码实现```

 ```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<queue>
using namespace std;

const int N = 100000 + 10;
//const long long INF = 1e10;

int a[N], n, m;
//a数组记录位置 n为有n个点 m表示m次询问

int left_mid_find(long long x) {//二分查找左边界
	long long kl = 1, kr = n;
	if(x >= a[n]) return n;
	if(x <= a[1]) return 1;
    //特判
	while(kl < kr) {
		int mid = (kl + kr + 1) >> 1;
		if(a[mid] == x) return mid;//当前位置等于查找值
		if(a[mid - 1] < x && a[mid] > x) return mid;
        //查找值在当前位置与当前位置-1之间
		if(a[mid + 1] > x && a[mid] < x) return mid + 1;
        //查找值在当前位置与当前位置+1之间
		if(a[mid] > x) kr = mid;
		else kl = mid - 1;
	}
	return kl;
}

int right_mid_find(long long x) {//二分查找右边界
	long long kl = 1, kr = n;
	if(x >= a[n]) return n;
	if(x <= a[1]) return 1;
    //特判
	while(kl < kr) {
		int mid = (kl + kr + 1) >> 1;
		if(a[mid] == x) return mid;
        //同上
		if(a[mid - 1] < x && a[mid] > x) return mid - 1;//注意return值不同
		if(a[mid + 1] > x && a[mid] < x) return mid;
		if(a[mid] > x) kr = mid;
		else kl = mid - 1;
	}
	return kl;
}


int main() {
	int k, j, i;
	cin >> n >> m;
	for(i = 1; i <= n; i++) cin >> a[i];//读入
	sort(a + 1, a + n + 1);
	for(i = 1; i <= m; i++) {
		cin >> j >> k;
		if((j < a[1] && k < a[1])||(j > a[n] && k > a[n])) {
        	//特判
			cout << 0 << endl;
			continue;
		}
		int l = left_mid_find(j);//左边界位置
		int r = right_mid_find(k);//右边界位置
		cout << r - l + 1<< endl;//等价与r - (l - 1)
	}
	return 0;
}
```
# $\color{cyan}\text{最后祝NOIP2018 rp++}$

---

## 作者：封禁用户 (赞：3)

//排序加二分 二分：第一个大于等于和最后一个小于等于

第一个

```cpp
  procedure boe(l,r,x:longint);
begin
  if l>=r then
  begin
    x2:=r;
    exit;
  end;
  mid:=(l+r) div 2;
  if a[mid]>=x then
    boe(l,mid,x) else
  boe(mid+1,r,x);
end;
```
最后一个
```cpp
  procedure boe(l,r,x:longint);
begin
  if l>=r then
  begin
    x2:=r;
    exit;
  end;
  mid:=(l+r) div 2;
  if a[mid]>=x then
    boe(l,mid,x) else
  boe(mid+1,r,x);
end;
```
nlogn超时超不了（喽喽喽）
完整：


```cpp
var
  a:array[1..1000000] of longint;
  n,m,i,j,x,y,x1,x2,mid,c,d:longint;
procedure sort(l,r: longint);
      var
         i,j,x,y: longint;
      begin
         i:=l;
         j:=r;
         x:=a[(l+r) div 2];
         repeat
           while a[i]<x do
            inc(i);
           while x<a[j] do
            dec(j);
           if not(i>j) then
             begin
                y:=a[i];
                a[i]:=a[j];
                a[j]:=y;
                inc(i);
                j:=j-1;
             end;
         until i>j;
         if l<j then
           sort(l,j);
         if i<r then
           sort(i,r);
end;
procedure less(l,r,x:longint);
begin
  if l>=r then
  begin
    x1:=r;
    exit;
  end;
  mid:=(l+r+1) div 2;
  if a[mid]<=x then
    less(mid,r,x) else
  less(l,mid-1,x);
end;
procedure boe(l,r,x:longint);
begin
  if l>=r then
  begin
    x2:=r;
    exit;
  end;
  mid:=(l+r) div 2;
  if a[mid]>=x then
    boe(l,mid,x) else
  boe(mid+1,r,x);
end;
begin
  readln(n,m);
  for i:=1 to n do
    read(a[i]);
  sort(1,n);
  for i:=1 to m do
  begin
    readln(c,d);
    boe(1,n,c);
    less(1,n,d);
    mid:=0;
    if x1>=x2 then
    writeln(x1-x2+1) else
    writeln(0);
  end;
end.

```

---

## 作者：OfstAutomataMachine (赞：1)

~~STL大法好~~

首先，需要知道两个函数，upper_bound 和 lower_bound，关于他们的用法，推荐一篇博客：[这个](https://blog.csdn.net/qq_40160605/article/details/80150252)

整理一下：lower_bound函数是从一个排好序的数组找到第一个大于等于已知数的下标，而upper_bound函数是算第一个大于已知数的下标，由于使用二分查找，所以时间复杂度均为 $O(log(n))$ 。

喜闻乐见的代码：
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[100001],n,q;
signed main()
{
	cin>>n>>q;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	sort(a+1,a+1+n);
	while(q--)
	{
		int x,y;
		cin>>x>>y;
		int x_p=lower_bound(a+1,a+1+n,x)-a;
		int y_p=upper_bound(a+1,a+1+n,y)-a;
		cout<<y_p-x_p<<endl;
	}
	return 0;
}
```


---

## 作者：Yirannn (赞：1)

### 题目思路 ：
看到这题的时候第一想法是直接前缀和，离散化然后 $O(1)$ 查询

但是懒得处理离散化之后各种关系，虽然用`map`离散化也可以，但是我选择直接上一棵权值线段树

因为值域太大，直接开开不下，但是每次只会用到一条链，所以动态开点即可

可以当作线段树、分块等基础数据结构的练习题。

膜各位楼下大佬，`lower_bound` 我是不敢用的，怕用不明白，至于自己写二分 ？ 我觉得和写一个线段树差不多，还得考虑边界问题

下面是代码

```cpp
#include <cstdio>
const int INF = 1000000000;
const int N = 4010000;
int t[N], ls[N], rs[N];
void fix(int l, int r, int &p, int x) {
	static int _;
	if(!p) p = ++_;
	if(l == r) return t[p] ++, void();
	int mid = (l+r) >> 1;
	if(x <= mid) fix(l, mid, ls[p], x);
	else fix(mid+1, r, rs[p], x);
	t[p] = t[ls[p]]+t[rs[p]];
}
int inq(int l, int r, int p, int x, int y) {
	if(!p) return 0;
	if(x <= l && y >= r) return t[p];
	int mid = (l+r) >> 1;
	int ret = 0;
	if(x <= mid) ret += inq(l, mid, ls[p], x, y);
	if(y > mid) ret += inq(mid+1, r, rs[p], x, y);
	return ret;
}
int rot;
int main() {
	int n, q;
	scanf("%d%d", &n, &q);
	while(n -- ) {
		int x;
		scanf("%d", &x);
		fix(1, INF, rot, x);
	}
	while(q -- ) {
		int x, y;
		scanf("%d%d", &x, &y);
		printf("%d\n", inq(1, INF, 1, x, y));
	}
}

---

## 作者：kczno1 (赞：1)

给你一个序列，告诉你哪些位置是1。

然后多次问区间和。


离散化，之后处理出前缀和，sum:a[l]..a[r]=s[r]-s[l-1]

```cpp
#include<bits/stdc++.h>

const int N=1e5+5;
int a[N*3],s[N*3];
int n,q,i,t,u;

bool a_xiao(int x,int y)
{
    return a[x]<a[y];
}
int id[N*3];
void lisan()
{
    for(i=1;i<=t;++i)id[i]=i;
    std::sort(id+1,id+t+1,a_xiao);
    int now=-1;
    for(i=1;i<=t;++i)
    {
        int x=id[i];
        if(a[x]!=now){now=a[x];++u;}
        a[x]=u;
    }
}

int main()
{freopen("1.in","r",stdin);
    scanf("%d%d",&n,&q);
    for(i=1;i<=n;++i)scanf("%d",a+i);
    t=n;
    for(i=1;i<=q;++i,t+=2)scanf("%d%d",a+t+1,a+t+2);
    lisan();
    for(i=1;i<=n;++i)++s[a[i]];
    for(i=2;i<=u;++i)s[i]+=s[i-1];
    for(t=n,i=1;i<=q;++i,t+=2) printf("%d\n",s[a[t+2]]-s[a[t+1]-1]);
}
```

---

## 作者：Kano (赞：0)

这道题肯定先要排序   
然后再看，~~似乎是用前缀和来搞的~~   
因为$A,B$的范围是$0\sim10^9$，所以依赖坐标的办法都炸掉了（MLE   

排过序后是一个单调上升的序列，明显可以用二分   
不过为什么不用**倍增**呢？~~（反正我也不会写二分~~   

倍增的思想就是成倍地增长（~~或减小~~，直至查询到答案   
复杂度同二分，为$O(log\,n)$   
以下贴倍增代码
```cpp
int find(int x){
	int p=0,q=1;
	while(q>0){
	    while(p+q>n) q>>=1;       // p/=2
	    if(x>=a[p+q]) p+=q,q<<=1;  // p+=q,q*=2
	    else q>>=1;              // q/=2
	}
    return p;
}
```
通过倍增查询**最大的、小于等于x的序列中的数**，返回该数的下标，即可求出区间元素数量

对于样例中的第五次查询，$A,B$都不是序列中的元素，该怎么办呢？   
我们固定右端点，只考虑左端点，可以发现：   
**若 `x==a[p]` 则可直接返回 `p` ，反之应返回 `p+1`**  
（上述结论建议自己手推验证   
![](https://cdn.luogu.com.cn/upload/pic/60195.png)

分析**查询**的时间复杂度，约为$O(Q\,log\,n)$   
【代码部分】
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
#define N 100000+2
int n,Q,a[N]；
int find(int x,int upd){
    int p=0,q=1;
    while(q){
        while(p+q>n) q>>=1;
        if(x>=a[p+q]) p=p+q,q<<=1;
        else q>>=1;
    }
    return a[p]==x?p:p+upd;
}
int main(){
    cin>>n>>Q;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    sort(a+1,a+n+1);
    while(Q--){
        int x,y;
        cin>>x>>y;
        cout<<find(y,0)-find(x,1)+1<<endl;
    }
    return 0;
}
```


---

## 作者：Kevin_F (赞：0)

总体思想仍然是排序 + 二分

但我用了一个小小的技巧：
upper_bound函数和 lower_bound函数

upper_bound  说白了就是找第一个大于查找值的云素
lower_bound  是找第一个大于等于查找值的元素
（补充一下：这两个函数都是用二分来查找的，所以手打二分查找也可以）

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define maxn 100010
using namespace std;

int n,m,q,tot,x,y;
int p[maxn];

int main(){
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++)  
	  scanf("%d",&p[i]);
    sort(p+1,p+1+n);
    for(int i=1;i<=q;i++){
		scanf("%d%d",&x,&y);
        cout<<upper_bound(p+1,p+n+1,y) - lower_bound(p+1,p+n+1,x)<<endl;
    }
}
```

另外，当然可以用手写的二分来写代码了，个人认为手写的更好理解，也更容易上手

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 100050;

int n,q,x,y,p[maxn];
int l,r,mid;
long long maxx,minn;

void erd(int l,int r,int x){
	if(l >= r) {
		maxx = r;
		return;
	}
	mid = (l + r) / 2;
	if(p[mid] >= x)  erd(l , mid , x);
	else erd(mid+1 , r , x);
}

void erf(int l,int r,int y){
	if(l >= r) {
		minn = r;
		return;
	}
	mid = (l + r + 1) / 2;
	if(p[mid] <= y)  erf(mid , r , y);
	else erf(l , mid-1 , y);
}

int main(){
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++){
		scanf("%d",&p[i]);
	}
	sort(p+1,p+1+n);
	for(int i=1;i<=q;i++){
		maxx = 0;  minn = 0;
		scanf("%d%d",&x,&y);
    	if(x > p[n] || y < p[1]){
    		printf("0\n");
    		continue;
		}
		erd(1,n,x);
		erf(1,n,y);
		printf("%d\n",minn - maxx + 1);
	}
	return 0;
}
```

---

## 作者：Minclxc (赞：0)

排序后二分查找区间两端的下标，相减出答案

二分用STL的lower\_bound和upper\_bound就好了

区间左端点>=，所以用lower\_bound，区间右端点<=所以用upper\_bound-1

所以ans=upper\_bound-1-lower\_bound+1=upper\_bound-lower\_bound

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
#define fo(a,b,c) for(int a=b;a<=c;a++)
int read(){
    int a=0,f=0;char c=getchar();
    for(;c<'0'||c>'9';c=getchar())if(c=='-')f=1;
    for(;c>='0'&&c<='9';c=getchar())a=a*10+c-'0';
    return f?-a:a;
}
const int N=1e5+1;
int x[N];
int main(){
    int n=read(),q=read();
    fo(i,1,n)x[i]=read();
    sort(x+1,x+n+1);
    fo(i,1,q){
        int l=read(),r=read();
        printf("%d\n",upper_bound(x+1,x+n+1,r)-lower_bound(x+1,x+n+1,l));
    }
    return 0;
}
```

---

