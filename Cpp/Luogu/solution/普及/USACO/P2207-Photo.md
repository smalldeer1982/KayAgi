# Photo

## 题目描述

Farmer John 打算给他的 $n$ 头奶牛照相。

他们排成一条线，并且依次取 $1\sim n$ 作为编号。

每一张照片可以拍摄到这列奶牛中一个连续的区间中的奶牛。

对于每一头奶牛，FJ 都想要让 Ta 至少出现在一张照片里。

不幸的是，有 $k$ 对关系不好的奶牛，他们拒绝出现在同一张照片里。

已知所有关系不好的奶牛所在的位置，请计算出 FJ 需要的最小需要拍摄的照片数量。

## 说明/提示

#### 样例输入输出 1 解释

FJ 可以只拍三张照片：$[1,2]$，$[3,5]$，$[6,7]$。

---

#### 数据规模与约定

对于 $100\%$ 的数据，保证 $2\le n\le10^9$，$1\le k\le1000$，$1 \leq a_i, b_i \leq n$。

## 样例 #1

### 输入

```
7 3
1 3
2 4
5 6
```

### 输出

```
3```

# 题解

## 作者：哔哩哔哩 (赞：10)

### 【思路】
个人感觉这个USACO的题和种树相似 都是区间选点问题嘛qwq(如果不是的话别打我qwq)。    
贪心的思想，照片尽可能的少。  
先排序一遍，再回去处理。  
复杂度也不高 O(logn+n)
### 【代码】
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int read()
{
    int out=0;
    char c=getchar();
    while(c<48||c>57) c=getchar();
    while(c>=48&&c<=57)
    {
        out=out*10+c-48;
        c=getchar();
    }
    return out;
}//读优
class node { public:

        int l,r;
}interval[1005];
inline bool operator <(const node& a,const node& b)
{
    if(a.l!=b.l) return a.l<b.l;
    return a.r<b.r;
}//重载 使得结构体排序
int main()
{
    int N=read(),K=read(),a,b;
    for(int i=0;i<K;i++)
    {
        a=read();
        b=read();//读入
        if(a<b)
        {
            interval[i].l=a;
            interval[i].r=b;
        }
        else
        {
            interval[i].l=b;
            interval[i].r=a;
        }//读入的时候欲处理
    }
    sort(interval,interval+K);//关键的排序
    int cnt=1,last=-1;
    for(int i=0;i<K;i++)//开始一个一个处理
    {
        if(interval[i].l>=last)
        {
            cnt++;//统计 多一张照片
            last=interval[i].r;
        }
        else if(interval[i].r<last) last=interval[i].r;//不需要多拍照片
    }
    printf("%d",cnt);//输出
    return 0;
}
```

---

## 作者：呆瓜yy (赞：9)

## **一篇很水的题解**

首先，观察题目可知，既然N很大，K很小（假装是吧），那么突破口就在于K

假设一下，如果知道从哪里把奶牛分开，题目就很简单了，但如果用for循环n硬做，肯定会超时的。于是，根据科学猜题法，要做的是for循环k来找断点

#### 以下是很水的时间为ans*k的算法：

首先从1-n枚举第i头奶牛（会优化的，理论上不会超时），作为第ans张照片的第一头奶牛

然后在k个限制中找到a>=i对应的最小b值（当然，这需要排序）

最后ans++，i直接跳到找到的b
    
### 关于这个方法的解释：

如果我们要确定一张照片的奶牛，则必须保证这张照片中的奶牛关系友好。换句话说，就是找到第一只与照片中的奶牛关系不好的奶牛的前一只作为这张照片的最后一只奶牛。

于是我们可以枚举第一头奶牛i，并在k个限制中寻找第一只不能存在于同一照片中的奶牛（注意：若当前的a<i，则对应的b对于这张照片无影响）

### 很水的代码：

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
using namespace std;
namespace lyy
{
	int n,k,j,i,yy,ans;
	const int INF=0x7f7f7f7f;
	struct photo
	{
		int a,b;
	}p[1005];
}
using lyy::n;//忽略这些细节，只是为了好玩
using lyy::k;
using lyy::p;
using lyy::i;
using lyy::j;
using lyy::yy;
using lyy::ans;
using lyy::INF;
bool cmp(lyy::photo x,lyy::photo y)
{
	if(x.a!=x.b)
	  return x.a<y.a;
	return x.b<y.b;
}
int main()
{
//	freopen("photo.in","r",stdin);
//	freopen("photo.out","w",stdout);
	cin>>n>>k;
	for(i=1;i<=k;i++)
	{
		cin>>p[i].a>>p[i].b;
		if(p[i].a>p[i].b)
		  swap(p[i].a,p[i].b);
	}
	sort(p+1,p+k+1,cmp);
	for(i=1;i<=n;)
	{
		yy=INF;
		for(j=1;j<=k;j++)
	      if(p[j].a>=i)
	        yy=min(yy,p[j].b);
	    ans++;
	    i=yy;
	}
	cout<<ans;
	return 0;
}
```



---

## 作者：Mychael (赞：8)

其实就是区间取点问题

两个照片之间相当于有一个断点，那么就相当于取最少的断点，使得每一对关系不好的牛之间都有断点，这样子每一对关系不好的牛都不会出现在同一个照片里。

那么问题就转化为了给出K个区间，求出最少取几个点，使得每个区间都有点。


这就是经典的区间取点问题，也就是区间贪心。


按左端点从小到大将所有区间排序，然后对于所有左端点小于已选区间的右端点的，都可以只用一个点，但是如果有区间被包含在当前区间，也就是右端点小于当前右端点，那么右端点应更新为较小的那个，也就是小区间替代大区间【因为如果小区间有点，大区间一定有点】


若我讲的不清楚，可以百度，相信不难理解




```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn=1005;
int read()
{
    int out=0;
    char c=getchar();
    while(c<48||c>57) c=getchar();
    while(c>=48&&c<=57)
    {
        out=out*10+c-48;
        c=getchar();
    }
    return out;
}
```
class node
{
public:



```cpp
        int l,r;
}interval[maxn];
inline bool operator <(const node& a,const node& b)
{
    if(a.l!=b.l) return a.l<b.l;
    return a.r<b.r;
}
int main()
{
    int N=read(),K=read(),a,b;
    for(int i=0;i<K;i++)
    {
        a=read();
        b=read();
        if(a<b)
        {
            interval[i].l=a;
            interval[i].r=b;
        }
        else
        {
            interval[i].l=b;
            interval[i].r=a;
        }
    }
    sort(interval,interval+K);
    int cnt=1,last=-1;
    for(int i=0;i<K;i++)
    {
        if(interval[i].l>=last)
        {
            cnt++;
            last=interval[i].r;
        }
        else if(interval[i].r<last) last=interval[i].r;
    }
    cout<<cnt<<endl;
    return 0;
}

```

---

## 作者：嘒彼小星 (赞：4)

没有题解，我来一发。。详细题解（也是我）：<http://blog.csdn.net/u013512086/article/details/61616447>


每一对无法共存的关系储存在结构体num里，较小的为a，较大的为b。

我们按照较小的a对num进行排序。

我们逐个扫描每个num，记录当前所在分组的区间[l,r]，初始为[1,num[i].b]

这些num区间有三种情况：相交，相离，内含。因此我们需要对这三种情况进行处理。其实相交跟内含一样的。

扫一遍就行了。

大概流程这样






```cpp
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
long long n;
int k;
struct T
{
    int a,b;
}num[1000 + 10];
bool cmp(T q, T w){ return q.a < w.a;}
int ans;
int main()
{
    freopen("data.txt", "r", stdin);
    scanf("%d%d", &n, &k);
    for(int i = 1;i <= k;i ++)
    {
        int temp,tempp;
        scanf("%d%d", &temp, &tempp);
        num[i].a = std::min(temp,tempp);
        num[i].b = std::max(temp,tempp);
    }
    std::sort(num + 1,num + 1 + k, cmp);
    int r = num[1].b - 1;
    for(int i = 1; i <= k; i ++)
    {
        if(num[i].a > r)
        {
            ans ++;
            r = num[i].b - 1;
        }
        r = std::min(r, num[i].b - 1);
    }
    printf("%d", ans + 2);
    return 0;
}

```

---

## 作者：周楷然 (赞：2)

###**思想与楼下差不多（区间取点问题），来段Pascal。**

var n,m,ans:longint;

a:array[0..1010] of record


```cpp
                            x,y:longint;  end;
 procedure swap(var x,y:longint);
  var tem:longint;
   begin
     tem:=x;x:=y;y:=tem;
   end;
 procedure init;
  var i:longint;
   begin
     readln(n,m);
     for i:=1 to m do
       begin
         readln(a[i].x,a[i].y);
         if a[i].x>a[i].y then swap(a[i].x,a[i].y);
       end;
   end;
 procedure qsort(L,R:longint);
  var i,j,x,midx,midy:longint;
   begin
     i:=L;j:=R;x:=random(R-L+1)+L;midx:=a[x].x;midy:=a[x].y;
     repeat
       while (i<R)and((a[i].x<midx)or((a[i].x=midx)and(a[i].y<midy))) do inc(i);
       while (j>L)and((a[j].x>midx)or((a[j].x=midx)and(a[j].y>midy))) do dec(j);
       if i <= j then begin
                        swap(a[i].x,a[j].x);swap(a[i].y,a[j].y);inc(i);dec(j);
                      end;
     until i>j;
     if i<R then qsort(i,R);
     if L<j then qsort(L,j);
   end;
 procedure main;
  var i,left,right:longint;
   begin
     qsort(1,m);
     left:=1;right:=n;ans:=0;
     repeat
       for i:=1 to m do
         if (a[i].x >= left)and(a[i].y <= right) then right:=a[i].y-1;
       left:=right+1;right:=n;inc(ans);
     until left > n;
   end;
 procedure print;
  begin
    writeln(ans);
  end;
 begin
  init;
  main;
  print;
end.

```

---

## 作者：Snow_Dreams (赞：1)

这道题是区间取点问题，一种贪心的思想

把所有区间按b从小到大排列（b相同时a从大到小排列），第一个区间取最后一个点。

当你每一次都选择区间的最右端，才能保证每一个选的点覆盖的范围都是最广泛的，也就是说选的点才是最少的。

和之前不相交区间的思考方法类似，把区间进行预处理，按照端点的大小排序（同样，按照右端点排序会好理解一点，但是左端点排序一样可以起到作用，初学者不必迷信右端点排序）。 
预处理过后，求解策略的思路和求不相交区间相似，如果下一个区间的左端点不被覆盖，则答案+1，如下：

```cpp

while(剩余区间的数目不为0)
{
    if（找到符合条件的下一个区间）
    {
        当前区间 = 下一个区间；
        答案数+1；
    }
 
    区间数--；
}
```
（这是伪代码）

然后就是这道题了qwq，原理是一模一样的

---

