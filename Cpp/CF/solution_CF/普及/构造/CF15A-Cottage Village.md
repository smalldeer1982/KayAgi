# Cottage Village

## 题目描述

给定一个坐标轴，轴上有 $n$ 座房子，每座房子的位置是 $x_i$，边长是 $a_i$。有个人想要贴着其中一座房子建造一座他自己的边长为 $t$ 的房子，请输出共有多少种建造方法。

## 说明/提示

$1\le n,t\le10^3$，$0\le|x_i|\le10^3$，$1\le a_i\le10^3$。

---
译自[残阳如血](/user/726139)。

## 样例 #1

### 输入

```
2 2
0 4
6 2
```

### 输出

```
4
```

## 样例 #2

### 输入

```
2 2
0 4
5 2
```

### 输出

```
3
```

## 样例 #3

### 输入

```
2 3
0 4
5 2
```

### 输出

```
2
```

# 题解

## 作者：The_Lost_09 (赞：4)

## [传送门](https://www.luogu.com.cn/problem/CF15A)

### 题目描述：
给定一坐标轴，轴上有 $n$ 座房子，每座房子的位置是 $x_{i}$ ，边长是 $a_{i}$ ，有个人想要贴着其中一座房子建造他自己的一座边长为 $t$ 的房子，输出共有多少种建法 

#### 注意：$x_{i}$ 为每座房子的中心坐标
即：第 $i$ 栋房子左右分别在 $x_{i} \mp \frac{a_{i}}{2}$处

### 思路：

1. 若相邻两栋房子间距等于 $t$ ，则可以建在它们之间且只能紧贴着它们建，所以答案加 1

2. 若相邻两栋房子间距大于 $t$ ，则可以建在它们之间且分别紧贴着它们建，所以答案加 2

3. 最左和最右一定可以建，所以答案加 2

#### 接下来就是你们最喜欢的 $Code$

$My Code$:

```cpp
#include<stdio.h>
#include<algorithm>
using namespace std;

struct Node{
	double s,f; //注意用 double
}a[1005];

bool cmp(Node x,Node y){
	return x.s<y.s;
}

int main(){
	int n;
	double t;
	scanf("%d%lf",&n,&t);
	for(int i=0;i<n;i++){
		double b,l;
		scanf("%lf%lf",&b,&l);
		a[i].s=b-l/2; //左端点
		a[i].f=b+l/2; //右端点
	}
	sort(a,a+n,cmp);
	int ans=2; //最左与最右，初值直接赋 2
	for(int i=1;i<n;i++){
		if(a[i].s-a[i-1].f>t)ans+=2;//差距大于t
		if(a[i].s-a[i-1].f==t)ans++; //差距等于t
	}
	printf("%d",ans);
	return 0; //完结撒花
}
```
管理员辛苦啦！求过

---

## 作者：Buried_Dream (赞：3)

## 题意：
给定一个长度为 $n$ 的一个数轴，上面有好几个小区间，

问如果再在小区间的端点去建造一个长度为 $t$ 的子区间，求总方案数。

## 思路：

对于每两个房子的间隔，我们都要遍历到一遍，

所以我们要先按照区间左端点来排序。

然后如果相邻的区间中的距离大于 $t$，答案就加 $2$；

因为当这个距离大于 $t$ 的时候，那么在这个最左边放也可以，最右边放也可以。

但当这个距离刚好等于 $t$ 的时候，答案只加 $1$，这是因为在左端点放和右端点放是本质相同的两种情况，所以只加 $1$。

最后答案数还要加 $2$，最左边和最右边一定可以放。

注意好精度问题；

## AC code:

```cpp
	scanf("%lld %lf", &n, &k); 
	for(int i = 1; i <= n; i++)	a[i].l = read(), a[i].r = read();
	sort(a + 1, a + n + 1, cmp);
	for(int i = 2; i < n; i++) {
		if((a[i].l - a[i].r / 2) - (a[i - 1].l + a[i - 1].r /2) > k ) ans += 2;
		else if((a[i].l - a[i].r / 2) - (a[i - 1].l + a[i - 1].r / 2) == k) ans++;
	}
	printf("%lld\n", ans + 2);

```



---

## 作者：fls233666 (赞：2)

首先，我们注意到我们要盖的房子必须贴着其他的房子去盖。而其他的房子数量 $n$ 最多只有 $1000$ 。因此，我们可以考虑遍历每个已经有的房子，检查每个房子的左右两边能否盖房子，统计得到答案。

接着，我们考虑什么时候我们统计会得到重复的方案。观察样例二，我们不难发现，**按上述方法统计时，方案会重复，当且仅当两个房子之间的距离为 $T$ 。** 因此，在统计完成后，我们可以再遍历一遍所有房子，统计间距为 $T$ 的相邻房子数量，并删减答案。这样就能得到正确答案了。

最后，需要注意的是，房子序列的开头和结尾的一定能盖房子的，因此要特判一下。因为精度问题，本题需要使用 double 才能通过。为了便于操作，建议把房子按照中心位置坐标排序。否则对于每个房子还要再遍历一遍，寻找这个房子相邻的两个房子。这样时间复杂度会退化为 $O(n^2)$，而如果排序则时间复杂度只有 $O(n \log(n))$，显然更优。

放上 AC 代码：

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm> 
#define ll long long
#define rgt register int
using namespace std;

int n,ans;
double nt; //你要盖的房子长度
struct house{
	double mid;  //已有的房子中心坐标
	double wid;  //已有的房子长度
}hs[1010]; 

inline bool cmp(struct house h1,struct house h2){
	return h1.mid<h2.mid;
}

int main(){
	scanf("%d%lf",&n,&nt);
	for(rgt i=1;i<=n;i++)
		scanf("%lf%lf",&hs[i].mid,&hs[i].wid);
        
	sort(hs+1,hs+1+n,cmp);  //排序
	for(rgt i=1;i<=n;i++){
		if(i-1<=0||hs[i-1].wid/2+hs[i-1].mid<=hs[i].mid-hs[i].wid/2-nt)
			ans++;  //判断左端能否盖房子
		if(i+1>n||hs[i].wid/2+hs[i].mid+nt<=hs[i+1].mid-hs[i+1].wid/2)
			ans++;  //判断右端能否盖房子
	}
	for(rgt i=2;i<=n;i++)
		if(hs[i].mid-hs[i].wid/2-hs[i-1].wid/2-hs[i-1].mid==nt)
			ans--;  //扣除重复方案
            
	printf("%d",ans);
	return 0;
}

```


---

## 作者：Nozebry (赞：2)

## $Problems$
在 $x$ 轴上已经盖了 $n$ 座房子。

房子边长平行于坐标轴，房子之间不能重叠，例如![](https://cdn.luogu.com.cn/upload/image_hosting/b0qsi5u9.png)
但可以相邻，即有同一条边,例如![](https://cdn.luogu.com.cn/upload/image_hosting/flpm9b2t.png)。

现在给出每座房子的边长和中心所在位置，问如果要再盖一座边长为 $t$ 房子，并且要与其他房子相邻，还有几个可能的位置。
## $Answer$
这道题我们需要先计算两个房子中间的间隔 $:$

 	如果大于等于 t 则说明中间有可能可以建房子
 	如果小于 t 则说明没有位置可以建房子
    
因为这条坐标轴是无限大的，所以在首尾也能建房子，故在开始时应该把累加器 $ans$（当然也可以是其他的 $QwQ$）的初始值赋为 $2$
## $Code$
```cpp
#include<bits/stdc++.h>
#define FOR(i,x,y) for(int i=x;i<y;++i)
using namespace std;
struct node
{
	double xi,ai;
}a[1050];//结构体排序起来比较方便
inline bool cmp(node a,node b){return a.xi<b.xi;}
int main()
{
	double t;
	int n,ans=2;//头尾各建一所
	scanf("%d%lf",&n,&t);
	FOR(i,0,n)scanf("%lf%lf",&a[i].xi,&a[i].ai);
	sort(a,a+n,cmp);
	FOR(i,1,n)
		if(((a[i].xi-a[i].ai/2)-(a[i-1].xi+a[i-1].ai/2))>t)ans+=2;//如果房子与房子之间的间隔如果大于 t 则可以建2所房子
	  	else
		  if(((a[i].xi-a[i].ai/2)-(a[i-1].xi+a[i-1].ai/2))==t)ans++;//如果房子与房子之间的间隔如果等于 t 则可以建1所房子
	printf("%d",ans);
}
```

---

## 作者：Firstly (赞：1)

## **题目思路：**

我们首先求出每幢房子的左端点和右端点。一幢房子的左端点为 $x_i-\frac{a_i}{2}$右端点为 $x_i+\frac{a_i}{2}$。注意数据中可能出现房子边长为奇数的情况，所以请注意精度问题。

求出没幢房子的左端点和右端点之后，我们将每幢房子从左到右进行排序。然后进行循环判断。

如果右面房子的左端点和左面房子的右端点之间的距离大于 $t$，那么可以建造两幢房子，即靠在左面房子和右面房子的两种；如果右面房子的左端点和左面房子的右端点之间的距离小于 $t$，那么显然，我们是无法建造房子的；如果右面房子的左端点和左面房子的右端点之间的距离正好等于 $t$，那么我们能建一幢房子，即紧挨着左、右两间房子。

当然，在最左面房子的左面和最右面房子的右面都是可以建造的，不要忘记加上这两种情况。

## **Code:**

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int n,t,ans=2;
struct node{
	double left,right;
}a[1005];
inline bool cmp(node n1,node n2){
	return n1.left<n2.left;
}
int main(){
	cin>>n>>t;
	for(int i=1;i<=n;i++){
		int x,aa;
		cin>>x>>aa;
		a[i].left=1.0*x-aa/2.0;
		a[i].right=1.0*x+aa/2.0;
	}sort(a+1,a+n+1,cmp);
	for(int i=1;i<n;i++){
		if(a[i+1].left-a[i].right>t)ans+=2;
		else if(a[i+1].left-a[i].right==t)ans++;
	}cout<<ans;
	return 0;
}
```


---

## 作者：封禁用户 (赞：1)

### 前言

这道题目没什么好说的了。。。就是一道典型的贪心+模拟。

### 分析

题目的要求是有好多个房子，然后呢 …… 要建造一个房子，并且必须贴着某个房子建造。

贪心一下。

我们可以发现，它贴着房子造，最前面和最后面肯定都是可以造的。

那么接下来就是处理中间的了。

(由于我们已经排好序了，所以几个房子都是按照远近来的)

那么怎么处理中间呢？

有 $3$ 中可能性是需要注意的。

1. 当两边的空隙大于 $t$ 也就是房子的边长，那么两边都可以造。

1. 当两边的空隙等于 $t$ ，那么就只能造一个。

1. 当两边的空隙小于 $t$ ，那么不能建造。

上面已经把情况列出来的。

那么我们还需要处理一下精度问题也就是用 `double` 。

所以按照上面的思路很快写出了下面的代码

### 代码

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
//头文件。
using namespace std;
const int INF=1005;
int n,t,ans=2;
//ans 最前面和最后面是一定可以建造的。
double x,y;
// double 注意精度问题。
struct _node {
        double l,r;
} a[INF];
//设定一个结构体方便之后排序。
__inline__ bool cmp(_node b,_node c) {//cmp 是这次的重点。
        if (b.l!=c.l) return b.l<c.l;//如果说 l 不等于，那么按照 l 从小到大排序。
        else return b.r<c.r;//否则按照 r 从小到大排序。
}
signed main()
{
        scanf("%d %d",&n,&t);
        //读入 n 和 t。
        for (int i=1; i<=n; i++) {
                scanf("%lf %lf",&x,&y);
                //读入两个需要处理的变量。
                a[i].l=(double) x-y/2.0;
                //计算出左边界，注意精度。
                a[i].r=(double) x+y/2.0;
                //计算出右边界，同样注意精度。
        }
        sort(a+1,a+1+n,cmp);//按照 cmp 函数来排序。
        for (int i=2; i<=n; i++) {
                if (a[i].l-a[i-1].r>t) {
                        ans=ans+2;//如果说 大于 t 那么就两边都可以建造。
                }
                else if (a[i].l-a[i-1].r==t) ans++;//如果刚刚好，那么就只能建造一个。
        }
        printf("%d\n",ans);//输出 ans。
        return 0;
}

```

### 写在后面的话

我这篇题解如果有错误，那么请在评论区里留言，我将会很感谢反映的人。

**谢谢观赏！**

---

## 作者：2c_s (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF15A)

## 思路

这题用结构体加上排序就能通过。

首先，定义结构体时要注意开 double 类型，因为数据不一定是整数。

其次，排序按照每个房子左端点从小到大排序即可。

最后，循环排序完遍历时，如果上一栋房子的右端点和这座房子的左端点恰好能放一栋房子，那么答案就 $+1$。如果上一栋房子的右端点和这座房子的左端点能放一栋房子还多，那么答案就 $+2$，因为可以贴着左边放，也可以贴着右边放。

## 代码

~~~cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1010;
struct node{
    double l,r;
};node a[N];
int n,ans=2;//注意赋初始值（两边的房子）。
double t;
bool cmp(node a,node b){return a.l<b.l;}
int main(){
    cin>>n>>t;
    for(int i=1;i<=n;++i){
        double mid,x;
        cin>>mid>>x;
        a[i].l=mid-x/2.0;
        a[i].r=mid+x/2.0;
    }
    sort(a+1,a+1+n,cmp);
    for(int i=2;i<=n;++i){
        if(a[i].l-a[i-1].r==t)ans++;
        if(a[i].l-a[i-1].r>t)ans+=2;
    }
    cout<<ans;
    return 0;
}
~~~

[AC 记录](https://www.luogu.com.cn/record/96744743)

---

## 作者：Fat_Fish (赞：0)

一道暴力模拟题，涉及结构体、手写cmp、排序，以及各种细节处理。
难度不高，只需弄清楚可以造房子的两种情况。
首先，肯定能装的下房子。则房子之间的距离大于等于房子的边长。
这时分类讨论。刚好装下，一种（=）；还有多余边长一种（>）。
第一种，因为两面贴墙只有一种。
第二种，因为可贴左边墙也可贴右边墙，所以两种。
话不多说，上代码：
```cpp
#include<iostream> 
#include<bits/stdc++.h>//从大佬那学来的万能头 
using namespace std;
struct FF{
	double left,right;//用结构体，记录房子的左端点和右端点 
};
bool cmp(FF x,FF y){
	return x.left<y.left;//手写cmp，从小到大，按房子左端点 
}
int main(){
	int n;
	double t;//t可能为小数 
	ios::sync_with_stdio(false);//关闭缓冲区 
	cin>>n>>t;
	FF ff[n+1];
	int x,a,ans=2;//ans=2是最左右房子的情况 
	for(int i=1;i<=n;++i){
		cin>>x>>a;
		ff[i].left=x-a/2.0;//中心点减边长的一半 
		ff[i].right=x+a/2.0;//中心点加边长的一半 |  。  | 
	}
	sort(ff+1,ff+1+n,cmp);//sort排序，STL 
	for(int i=2;i<=n;++i){//第一个的左边没房子，从二开始 
		if(ff[i].left-ff[i-1].right==t){
			ans+=1;//刚好在中间，贴着两个房子 
		}if(ff[i].left-ff[i-1].right>t){
			ans+=2;//刚好在中间，贴着一个房子 ，两种情况 
		}
	}
	cout<<ans<<'\n';//输出 
	return 0; 
} 
```


---

## 作者：CrTsIr400 (赞：0)

**贪心**题目，直接模拟就好（ $10^{3}$ 的数据绰绰有余）。

首先，要给每栋房子的起端和末端**排一下序。**

注意：因为这些房子**不会重叠**，所以要按照**升序排序**。

就是为了**更容易求出房子与房子之间的距离**。

（其实按照**降**序也可以。）

如果能放得下，那就判断是否**刚好塞下**。

如果**刚好**塞下（**紧贴两端**），它对答案贡献 $1$ ；

否则（**两边有空隙**），它就对答案贡献 $2$ 。**（可以紧贴左或右端）**

输出答案时，记得把**答案加上 $2$ ！（最左和最右两个方案）**

而且当每栋房子的边长为**奇数**时，就要在程序里使用**实数**。

```cpp
#include<bits/stdc++.h>
#define inf ((1<<30)-1)
#define linf ((1<<62)ll-1)
#define Fu(i,a,b) for(register int i=a;i<=b;i++)
#define Fd(i,a,b) for(register int i=a;i>=b;i--)
#define Fn(i,a) for(register int i=las[a];i;i=nex[i])
int Fl,Pn,SI=100;char mch=' ',ch,Bf[21];
template<typename t>void in(t&a){a=0;ch=getchar();Fl=1;while((ch<'0')||(ch>'9'))Fl=(ch=='-')?-Fl:Fl,ch=getchar();while((ch>='0')&&(ch<='9'))a=a*10+ch-'0',ch=getchar();a*=Fl;}
template<typename t>void out(t a){if(a<0)putchar('-'),a=-a;if(a==0)putchar('0');while(a)Bf[++Pn]=a%10+'0',a/=10;while(Pn)putchar(Bf[Pn]),--Pn;putchar(mch);}
template<typename t,typename ...ARGS>void in(t&a,ARGS&...args){in(a);in(args...);}
template<typename t,typename ...ARGS>void out(t a,ARGS... args){out(a);out(args...);}
using namespace std;
int n,m,t1,t2,ans;
struct node
{
	double s,e;
	bool operator <(const node&y)const
	{
		return s<y.s;//重载运算符
	}
}a[1001];
int main()
{
	in(n,m);
	Fu(i,1,n)in(t1,t2),a[i].s=t1-t2/2.00,a[i].e=t1+t2/2.00;//注意：有坑，如果t2是奇数的话，那就要小数。
	stable_sort(a+1,a+n+1);//排序
	Fu(i,1,n)if(a[i].s-a[i-1].e>m)ans+=2;else if(a[i].s-a[i-1].e==m)ans++;//判断
	cout<<ans+2;//输出答案。
	return 0;
}

```



---

## 作者：TRZ_2007 (赞：0)

**[题解 【CF15A Cottage Village】](https://www.luogu.com.cn/problem/CF15A)**    
# Solution  

这题就是一个数学问题……  
我们先把所有的房子按照左端点排序，得到他们位置的相对关系，注意，这里不能用中心位置排，因为房子的边长是一个不确定的量。  
好接下来我们考虑如何计数。  
- 1：最左边的左和最右边的右肯定是可以放的。  
- 2：两个房子中间的间隔如果正好是我要建的房子的边长，那么在这里我就只有一种建造方法。  
- 3：两个房子中间的间隔如果大于我的房子的边长，那么我可以建在靠左房子的右边和靠右房子的左边，有两种建造方法。
- 4：两个房子中间的间隔如果小于我的房子的边长，那么显然我在这里不能造房子。  

综合上述分类，加一下就可以了，注意卡精度。

# Code  
```cpp
#include <cstdio>
#include <algorithm>

const int N = 1009;

int n,ans = 2; double t,d;	//最左边和最右边肯定可以

struct node {
	double xi,l,r;	//记录位置，左右端点
}p[N];

bool cmp(node u,node v) {	//按左端点排序
	if(u.l != v.l) return u.l < v.l;
	else return u.r < v.r;
}

int main() {
	scanf("%d %lf",&n,&t);
	for(int i = 1;i <= n;i++) {
		scanf("%lf %lf",&p[i].xi,&d);
		p[i].l = p[i].xi - d / 2; p[i].r = p[i].xi + d / 2;
	}
	std::sort(p + 1,p + n + 1,cmp);
	for(int i = 2;i <= n;i++) {
		if(p[i].l - p[i - 1].r > t) ans += 2;
		if(p[i].l - p[i - 1].r == t) ans++;
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：封禁用户 (赞：0)

题目传送>>[CF15A](https://www.luogu.com.cn/problem/CF15A)。  
### 题意简述：  
- 一坐标轴上有 $n$ 栋中心坐标为 $x_i$，边长为 $a_i$ 的房子，求可贴房新建边长为 $t$ 的房子的方案数。  
- $1 \leq n,t \leq 1000$，$ -1000 \leq x_{i}<=1000,1 \leq a_{i} \leq 1000$。  

### 题目分析：  
首先毫无疑问的是端点处的两房子端外是宽广无比的，两个建房方案便这样产生了。然后考虑在旧房子间新建房子，我们可以先求出每个房子的两端坐标，然后以房子中心坐标对所有旧房子排个序，并一一求出两两相邻房子的间距，将间距与新建房子的边长进行比较，若间距小于新建房子边长则该间隙无法新建房子，若恰等则仅有一新建房子方案，另若间距大于新建房子边长则有两新建房子方案（即可贴左房建，亦可贴右房建）。  
#### 需注意：  
1. 坐标：并不一定全整，会出现小数;  
1. 间距：因坐标可在坐标轴负半轴，亦可在正半轴，故需分类计算。  

### Code：  
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long ll;
typedef long double ld;
#define endl '\n'
const ll MAXN = 1e3 + 10;
ll n, t;   //定义旧房子数，新建房子的边长
ll x, a;   //定义旧房子中心坐标，旧房子边长
ll ans = 0;   //定义方案数
ld J;   //定义旧房子间间距
struct house    //用结构体存各旧房子中心坐标，左端坐标，右端坐标
{
	ll m;
	ld l, r;
} h[MAXN];
bool cmp(house x, house y)    //以房子中心坐标对所有旧房子排序（升）
{
	return x.m < y.m;
}
ld dis(ld x, ld y)  //定义函数求两两旧房子间距
{
	if (x < 0 and y < 0)
	{
		return abs(x) - abs(y);
	}
	else
	{
		return y - x;
	}
}
int main()
{
	//freopen("input.in","r",stdin);
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> n >> t;
	ans += 2;   //端点处的两房子端外两方案
	for (ll i = 1; i <= n; i++)
	{
		cin >> x >> a;
		h[i].m = x, h[i].l = x - a / 2.0, h[i].r = x + a / 2.0;
	}
	sort(h + 1, h + n + 1, cmp);
	for (ll i = 1; i < n; i++)
	{
		J = dis(h[i].r, h[i + 1].l);
		if (J > (ld)t)
		{
			ans += 2;
		}
		else if (J == (ld)t)
		{
			ans += 1;
		}
	}
	cout << ans;
	return 0;
}
```
### 结果:  
![JieGuo](https://cdn.luogu.com.cn/upload/image_hosting/cj7vsb3v.png)  
企鹅的题解到此结束，祝各位 OIers 进步 ++~

---

