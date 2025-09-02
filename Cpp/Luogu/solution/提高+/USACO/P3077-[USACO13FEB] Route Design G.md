# [USACO13FEB] Route Design G

## 题目描述

After escaping from the farm, Bessie has decided to start a travel agency along the Amoozon river.  There are several tourist sites located on both sides of the river, each with an integer value indicating how interesting the tourist site is.

Tourist sites are connected by routes that cross the river (i.e., there are no routes connecting a site with a site on the same side of the river).  Bessie wants to design a tour for her customers and needs your help.  A tour is a sequence of tourist sites with adjacent sites connected by a route. In order to best serve her customers she wants to find the route that maximizes the sum of the values associated with each visited site.

However, Bessie may be running several of these tours at the same time.  Therefore it's important that no two routes on a tour

intersect.  Two routes (a <-> x) and (b <-> y) intersect if and only if (a < b and y < x) or (b < a and x < y) or (a = b and x = y).

Help Bessie find the best tour for her agency.  Bessie may start and end at any site on either side of the Amoozon.

河左岸有n个点，右岸有m个点，各有权值。有R条跨河的桥，求一条不交叉的路径使得点权和最大。

(a <-> b) 与 (x <-> y) 交叉指(a < b and y < x) or (b < a and x < y) or (a = b and x = y)。


## 说明/提示

There are three sites on the left side of the Amoozon with values 1, 1, and 5.  There are two sites on the right side of the Amoozon with values 2 and 2.  There are four routes connecting sites on both sides of the river.


The optimal tour goes from site 1 on the left, site 1 on the right, and ends at site 3 on the left.  These respectively have values 1, 2, and 5 giving a total value of the trip of 8.


## 样例 #1

### 输入

```
3 2 4 
1 
1 
5 
2 
2 
1 1 
2 1 
3 1 
2 2 
```

### 输出

```
8 
```

# 题解

## 作者：zx2003 (赞：5)

DP
仔细分析题目后我们发现，我们走的路线一定是在L方向严格递增，R方向严格递增。我们自然想到以点作为状态，但这样时空复杂度都是O(N^2)级别的，不能承受。于是我们考虑以边作为事件来解决。

我们先对边排序，左端点由大到小。这时候被这条边连接的两个点便可以状态转移。我们设DPA[i]表示左边以i结尾的最大收益，DPB[i]表示右边以i结尾的最大收益。

得到状态转移方程：

存在边<i,j>时

FL[i]=max{DL[i]+FR[j]} //注意边界，若FR[j]=0,则FL[i]=max(DL[i]+DR[i]),下同

    FR[j]=max{DR[j]+FL[i]} 

转移的时候拿两个临时变量存一下就行了

uses math;

type
 bridge=record

l,r:longint



```cpp
 end;
var
 dl,dr,fl,fr:array[1..40000] of int64;
 ans,x,y,u,v:int64;
 i,j,n,m,r:longint;
 a:array[1..100000] of bridge;
operator <(a,b:bridge)c:boolean;
begin
 c:=(a.l<b.l)or(a.l=b.l)and(a.r<b.r)
end;
operator =(a,b:bridge)c:boolean;
begin
 c:=(a.l=b.l)and(a.r=b.r)
end;
procedure sort(l,r:longint);
var
 i,j:longint;
 x,y:bridge;
begin
 if l>r then exit;
 i:=l;
 j:=r;
 x:=a[(l+r) shr 1];
 repeat
  while a[i]<x do inc(i);
  while x<a[j] do dec(j);
  if i<=j then
  begin
   y:=a[i];
   a[i]:=a[j];
   a[j]:=y;
   inc(i);
   dec(j)
  end
 until i>j;
 if l<j then sort(l,j);
 if i<r then sort(i,r);
end;
begin
// assign(input,'a.txt');reset(input);
 readln(n,m,r);
 for i:=1 to n do
 begin
  readln(dl[i]);
  if dl[i]>ans then ans:=dl[i]
 end;
 for i:=1 to m do
 begin
  readln(dr[i]);
  if dr[i]>ans then ans:=dr[i]
 end;
 for i:=1 to r do readln(a[i].l,a[i].r);
 sort(1,r);
 fl[a[1].l]:=dl[a[1].l]+dr[a[1].r];
 fr[a[1].r]:=fl[a[1].l];
 for i:=2 to r do
 begin
  if a[i]=a[i-1] then continue;
  x:=fl[a[i].l];
  y:=fr[a[i].r];
  u:=dl[a[i].l];
  v:=dr[a[i].r];
  if x=0 then fr[a[i].r]:=max(fr[a[i].r],u+v)
   else fr[a[i].r]:=max(fr[a[i].r],x+v);
  if y=0 then fl[a[i].l]:=max(fl[a[i].l],u+v)
   else fl[a[i].l]:=max(fl[a[i].l],y+u)
 end;
 for i:=1 to n do if fl[i]>ans then ans:=fl[i];
 for i:=1 to m do if fr[i]>ans then ans:=fr[i];
 writeln(ans)
end.
```

---

## 作者：滑不拉稽 (赞：4)

## 思路

首先，考虑怎么选点才能满足题目中 “ 路径不交叉 ” 的条件：

很容易想到，一条合法的路径必须满足选的左部点一定大于上一次选的左部点，选的右部点一定大于上一次选的右部点，这会让我们想到排序，排序后顺序遍历得到的路径就一定不会交叉了。

其次，因为已经有序，每一次更新的点就已经是最优状况，可以直接转移。

## 方法

$val[i][0/1]$ 表示左(0)/右(1)边第 $i$ 个顶点的权值。

$f[i][0/1]$ 表示走到左(0)/右(1)边第 $i$ 个顶点的最大点权和。

排序时以左部点为第一关键字，右部点为第二关键字。

最后统计答案即可。

## 细节

题目中 R 可以等于0，意味着一座桥也没有，此时最大点权和即所有顶点中的最大值。

所以需要在输入时记录所有点里面的最大值。

### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define re register long long
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch)){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return f==1?x:-x;
}
const int N=4e4+10,M=1e5+10;
int n,m,q,f[N][2],val[N][2],ans;
pair<int,int> e[M];
signed main()
{
	n=read(),m=read(),q=read();
	for(re i=1;i<=n;++i)ans=max(ans,f[i][0]=val[i][0]=read());
	for(re i=1;i<=m;++i)ans=max(ans,f[i][1]=val[i][1]=read());
	for(re i=1;i<=q;++i)e[i].first=read(),e[i].second=read();
	sort(e+1,e+q+1);
	for(re i=1;i<=q;++i)
	{
		int x=e[i].first,y=e[i].second,tmp=f[y][1];
		f[y][1]=max(f[y][1],f[x][0]+val[y][1]);
		f[x][0]=max(f[x][0],tmp+val[x][0]);
	}
	for(int i=1;i<=n;++i)ans=max(ans,max(f[i][0],f[i][1]));
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：XiXi (赞：3)

先感谢楼上，给我带了不少灵感，这篇权当楼上的C++版吧，感谢楼上

#include<bits/stdc++.h>     //万能头文件，不过有时也会有副作用


```cpp
using namespace std;
struct node{int x,y;}l[111111];
long long n,m,r,s,p,q,u,v,i,a[111111],b[111111],f1[111111],f2[111111];
bool cmp(node a,node b) {return (a.x<b.x)||(a.x==b.x&&a.y<b.y);}     //排序的关键字
int main()
{
    cin>>n>>m>>r;
    s=-99999999;
    for (i=1;i<=n;i++)    
    {
        cin>>a[i];
        s=max(s,a[i]);
    }
    for (i=1;i<=m;i++)    
    {
        cin>>b[i];
        s=max(s,b[i]);
    }
    for (i=1;i<=r;i++) cin>>l[i].x>>l[i].y;   //前面全在读入
    sort(l+1,l+1+r,cmp);     //STL模板排序
    f1[l[1].x]=a[l[1].x]+b[l[1].y];
    f2[l[1].y]=f1[l[1].x];
    for (i=2;i<=r;i++)
    {
        if (l[i].x==l[i-1].x&&l[i].y==l[i-1].y) continue;
        p=f1[l[i].x];
         q=f2[l[i].y];
          u=a[l[i].x];
          v=b[l[i].y];
          if (p==0) f2[l[i].y]=max(f2[l[i].y],u+v); else f2[l[i].y]=max(f2[l[i].y],p+v);
          if (q==0) f1[l[i].x]=max(f1[l[i].x],u+v); else f1[l[i].x]=max(f1[l[i].x],q+u);
    }
    for (i=1;i<=n;i++) s=max(f1[i],s);
    for (i=1;i<=m;i++) s=max(f2[i],s);
    cout<<s;
    return 0;
}
具体推导过程大家还是看楼上P党的吧，我就当个小小的搬运工啦
```

---

## 作者：Betrayer_of_love (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/P3077)

### 题解

把所有边按第一维排序，相等的按第二维排序。

设 $f[i]$ 表示走到河左边的第 $i$ 个景点的最大收益， $g[i]$ 表示走到河右边的第 $i$ 个景点的最大收益。

因为已经有序，河左边的在此之前没有被更新过，河右边能更新 $x$ 的也已经是最优情况，直接转移即可。

### CODE

```c
#include <bits/stdc++.h>
using namespace std;
#define N 100050
#define fs first
#define sd second
#define _max(x,y) ((x)>(y)?(x):(y))
inline char nc() {
    static char buf[100000],*p1,*p2;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
}
inline int rd() {
    int x=0; char s=nc();
    while(s<'0'||s>'9') s=nc();
    while(s>='0'&&s<='9') x=(x<<3)+(x<<1)+s-'0',s=nc();
    return x;
}
int f[40050],g[40050],n,m,q,val[N];
pair<int,int>e[N];
int main() {
    n=rd(); m=rd(); q=rd();
    int i,ans=0,x,y,tmp;
    for(i=1;i<=n;i++) f[i]=val[i]=rd(),ans=_max(ans,f[i]);
    for(i=1;i<=m;i++) g[i]=val[i+n]=rd(),ans=_max(ans,g[i]);
    for(i=1;i<=q;i++) e[i].fs=rd(),e[i].sd=rd();
    sort(e+1,e+q+1);
    for(i=1;i<=q;i++) {
        x=e[i].fs,y=e[i].sd,tmp=g[y];
        g[y]=_max(g[y],f[x]+val[y+n]); f[x]=_max(f[x],tmp+val[x]); ans=_max(ans,max(f[x],g[y]));
    }
    printf("%d\n",ans);
    return 0;
}
```

**完结撒花，谢谢！！！**

---

## 作者：Zikl (赞：0)

感觉之前的题解解释的不是很清楚，所以发一篇题解捏。


------------
题意：

河左岸有 $n$ 个点，右岸有 $m$ 个点，各有权值。有 $R$ 条跨河的桥，求一条不交叉的路径使得点权和最大。

思路：

为满足 “ 路径不交叉 ” 的条件，我们以左部点为第一关键字，右部点为第二关键字排序，然后每次用左边更新右边，右边更新左边。

这样我们就能保证更新左边的点时，所有贡献了点权的点在右边或为左边且小于被更新点，在右边贡献了点权的点合法，因为更新右边的点的操作与左边是相同的，所以不用担心是否有点不合法，而在左边贡献了点权的点显然合法。

用两个数组分别保存左点和右点的最大点权和，输出所有点里面的最大值。

剩下细节看代码。

my code

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<cmath>
#define int long long
const int N=4e4+5,RR=1e5+5;
using namespace std;
int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();} 
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	return x*f;
}
int n,m,R,a[N],b[N],f[RR],g[RR],ans;
pair<int,int>e[RR];
signed main(){
	
	n=read(),m=read(),R=read();
	for(int i=1;i<=n;i++) a[i]=read(),f[i]=a[i];
	for(int i=1;i<=m;i++) b[i]=read(),g[i]=b[i];
	for(int i=1;i<=R;i++){
		int u=read(),v=read();
		e[i]=make_pair(u,v);
	}
	sort(e+1,e+1+R);
	for(int i=1;i<=R;i++){
		int x=e[i].first,y=e[i].second;
		int dd=g[y],ddd=f[x];
		g[y]=max(g[y],ddd+b[y]);
		f[x]=max(f[x],dd+a[x]);
	}
	for(int i=1;i<=n;i++)
	ans=max(ans,f[i]);
	for(int i=1;i<=m;i++)
	ans=max(ans,g[i]);
	cout<<ans;
	return 0;
} 
```


---

