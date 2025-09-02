# Professor's task

## 题目描述

Once a walrus professor Plato asked his programming students to perform the following practical task.

The students had to implement such a data structure that would support a convex hull on some set of points $ S $ . The input to the program had $ q $ queries of two types:

1\. Add a point with coordinates $ (x,y) $ into the set $ S $ . Note that in this case the convex hull of $ S $ could have changed, and could have remained the same.

2\. Say whether a point with coordinates $ (x,y) $ belongs to an area limited by the convex hull, including the border.

All the students coped with the task. What about you?

## 样例 #1

### 输入

```
8
1 0 0
1 2 0
1 2 2
2 1 0
1 0 2
2 1 1
2 2 1
2 20 -1
```

### 输出

```
YES
YES
YES
NO
```

# 题解

## 作者：Elegia (赞：22)

这是一道动态凸包的模板题。

听罢昨天徐明宽的计算几何题，分享一下以坐标排序的凸包建立方法。个人认为相对于极角排序，坐标排序能够减小精度误差，尤其是这样一道坐标都为整数的题。

静态凸包的构建方法是：

1. 将各点坐标按 $x$ 从小到大排序
2. 分别维护上凸壳和下凸壳。注意到如果之前有两点 $A$ 和 $B$ ，当插入新节点 $C$ 时，以上凸壳为例，如果 $\overrightarrow{AB} \times \overrightarrow{AC} \ge 0$ 时，这说明 $B$ 在线段 $AC$ 的下方，就可以将 $B$ 删除。我们可以看出此时凸包是一个类似单调栈的结构。

排序过程是算法的瓶颈，效率 $\Theta(n \log n)$。而后面的构建是 $\Theta(n)$ 的。

从上面的启发我们可以找到一种动态维护凸包的方法。

用 $\texttt{std::map}$ 维护上下凸壳， $x$ 为第一关键字， $y$ 为第二关键字。在插入一个新的点到凸壳上时，检查它周围的点是否可以被删掉，用与静态凸包类似的方法判断。

虽然插入一个点时可能删除若干个点，但注意到每个点只有在被删除时才会多贡献这 $\mathcal O(\log n)$ 的时间，所以本算法支持凸包的单次插入有**摊还**意义上的时间复杂度 $\mathcal O(\log n)$ 。

题外话：注意到这是摊还意义上的，所以单次操作的实际消耗时间可能远远不止 $\mathcal O(\log n)$ ，简单的构造方法：放一个点在 $(+\infty, +\infty)$ ，这样就会把所有点除了最左点都顶掉，单次就变成了 $\Theta(n)$ 的。（想一想，为什么不是 $n\log n$ ？）所以这个方法**不能**直接转化为可持久化凸包。

```cpp
#include <cstdio>
#include <cmath>

#include <algorithm>
#include <map>

typedef std::map<int, int> map;
typedef map::iterator iterator;
typedef int num;
typedef long long ll;

map top, down;

ll det(int x1, int y1, int x2, int y2);
bool check_top(int x, int y);
bool check_down(int x, int y);
bool remove_top(iterator it);
bool remove_down(iterator it);
void insert_top(int x, int y);
void insert_down(int x, int y);

int main() {
	int q, op, x, y;
	scanf("%d", &q);
	while (q--) {
		scanf("%d%d%d", &op, &x, &y);
		if (op == 1) {
			insert_top(x, y);
			insert_down(x, y);
		} else
			puts((check_top(x, y) && check_down(x, y)) ? "YES" : "NO");
	}
	return 0;
}

void insert_top(int x, int y) {
	if (check_top(x, y))
		return;
	top[x] = y;
	iterator it = top.find(x);
	iterator jt = it;
	if (it != top.begin()) {
		--jt;
		while (remove_top(jt++))
			--jt;
	}
	if (++jt != top.end())
		while (remove_top(jt--))
			++jt;
}

ll det(int x1, int y1, int x2, int y2) {
	return (ll)x1 * y2 - (ll)x2 * y1;
}

void insert_down(int x, int y) {
	if (check_down(x, y))
		return;
	down[x] = y;
	iterator it = down.find(x);
	iterator jt = it;
	if (it != down.begin()) {
		--jt;
		while (remove_down(jt++))
			--jt;
	}
	if (++jt != down.end())
		while (remove_down(jt--))
			++jt;
}

bool remove_top(iterator it) {
	if (it == top.begin())
		return false;
	iterator jt = it, kt = it;
	--jt;
	++kt;
	if (kt == top.end())
		return false;
	if (det(it->first - jt->first, it->second - jt->second, kt->first - jt->first, kt->second - jt->second) >= 0) {
		top.erase(it);
		return true;
	}
	return false;
}

bool remove_down(iterator it) {
	if (it == down.begin())
		return false;
	iterator jt = it, kt = it;
	--jt;
	++kt;
	if (kt == down.end())
		return false;
	if (det(it->first - jt->first, it->second - jt->second, kt->first - jt->first, kt->second - jt->second) <= 0) {
		down.erase(it);
		return true;
	}
	return false;
}

bool check_top(int x, int y) {
	iterator it = top.lower_bound(x);
	if (it == top.end())
		return false;
	if (it->first == x)
		return y <= it->second;
	if (it == top.begin())
		return false;
	iterator jt = it;
	--jt;
	return det(it->first - jt->first, it->second - jt->second, x - jt->first, y - jt->second) <= 0;
}

bool check_down(int x, int y) {
	iterator it = down.lower_bound(x);
	if (it == down.end())
		return false;
	if (it->first == x)
		return y >= it->second;
	if (it == down.begin())
		return false;
	iterator jt = it;
	--jt;
	return det(it->first - jt->first, it->second - jt->second, x - jt->first, y - jt->second) >= 0;
}
```

---

## 作者：旋转卡壳 (赞：9)

~~为此题贡献了一页红~~

原来if(calc(balabala...)>0)写成if(calc(balabala...))居然会错
我一直以为是对的(菜得真实

动态凸包裸题

因为用极角排序会有精度误差~~(而我又只会atan2的极角排序)~~ 所以我们可以把所有点的坐标都乘3 误差就没那么大了？

极角排序需要一个原点 题目一开始就给3个点 所以我们直接用这个三角形的重心

对于一个要加入凸包的点 我们一要找到它对于凸包的位置 二就要因它而修改凸包

对于第一个问题就拿个set维护就行了(巨佬们花5m50s打个平衡树之类的更好！) 比较函数就是极角排序的函数 

第二个问题我们可以很容易想到(想一想,为什么?) 由要加入的点向两边一直求叉积 一直修改就行了

如果是询问的话其实就是像插入一样找到位置后看叉积

具体实现看代码和代码注释~~(自认代码风格完美)~~

没有代码注释的：[云剪贴板](https://www.luogu.org/paste/p4fi9i68)（有了代码注释感觉代码变丑了）

```cpp
#include <cstdio>
#include <set>
#include <cmath>

using namespace std;

typedef long long ll;

int n,opr,x,y;

struct p {int x,y;double ang;}o,ori[4]; 
//ang 极角
 
set<p> S;
set<p>::iterator pre,suc;

inline bool operator < (p i,p j)
{return i.ang==j.ang?i.x<j.x:i.ang<j.ang;}

p operator - (p i,p j) {return (p){i.x-j.x,i.y-j.y};}

ll cross(p i,p j) {return (ll)i.x*j.y-(ll)i.y*j.x;}

set<p>::iterator PRE(set<p>::iterator x)
{return x==S.begin()?--S.end():--x;}
//注意边界 

set<p>::iterator SUC(set<p>::iterator x)
{return (++x)==S.end()?S.begin():x;}

inline void insert(p x) {
    if(cross(x-*pre,*suc-x)<=0) return ; //在凸包内 解释看询问处 
    S.insert(x);
    set<p>::iterator cur=S.find(x),i=PRE(cur),j=PRE(i);
    //相当于P=cur=p A=i=s[top] B=j=s[top-1] 
    while(cross(*cur-*j,*i-*j)>=0) S.erase(i),i=j,j=PRE(j);
    //往极角小的地方修改 向量BP在向量BA上或右边 就删掉A 
    //下面同理 画个图就很清晰了 
    i=SUC(cur);j=SUC(i);
    while(cross(*cur-*j,*i-*j)<=0) S.erase(i),i=j,j=SUC(j);
}

int main() {
    scanf("%d",&n);
    for(register int i=1;i<=3;++i) { //先读入三个点定原点 
        scanf("%d %d %d",&opr,&ori[i].x,&ori[i].y);
        o.x+=ori[i].x;o.y+=ori[i].y;
        ori[i].x*=3;ori[i].y*=3; //注意精度处理 
    } for(register int i=1;i<=3;++i) {
        ori[i].ang=atan2(ori[i].y-o.y,ori[i].x-o.x); //求波极角 
        S.insert(ori[i]);
    } for(register int i=4;i<=n;++i) { //读入剩下的 
        scanf("%d %d %d",&opr,&x,&y);x*=3;y*=3;
        p P=(p){x,y,atan2(y-o.y,x-o.x)};
        if((suc=S.lower_bound(P))==S.end()) suc=S.begin();
        //找插入点后面的位置 
		//就是找到大于等于插入点的点在凸包上的位置
		//想象成指南针那样的会很好理解？ 最小的极角在x正半轴
		//最大的极角是逆时针绕一圈后也在x正半轴 
		//如果没有 说明插入点将是最大的 它的后面就设为开头 
        pre=PRE(suc);
        //找插入点前面的位置 
        if(opr==1) insert(P);
        else if(cross(P-*pre,*suc-P)<=0) printf("YES\n");
        //相当于 极角较小的点A[*pre] 和极角较大的点B[*suc]
		//他们之间有个点P 如果向量AP在向量PB上或者左边
		//P点就在凸包内 可以画图想想 
        else printf("NO\n");
    } return 0;
}
```



---

## 作者：xukuan (赞：4)

**前置**

3月的时候听517将这题，过了这么久，终于做了这题，发篇题解帮助理解一下

**题意**

动态二维凸包，加点和判断一个点是否在凸包内

**分类**

- 数学，数论
- 计算几何
- 模板系列

**前置知识**

[静态二维凸包](https://www.luogu.org/problem/P2742)

**想法**

回忆静态二维凸包的构建方法，我们先维护一个上下凸壳，再进行操作

实际上现在就是让这个维护变成动态的

C++ STL里的map会非常好用

开两个map，一个叫top，维护上凸壳；一个叫down，维护下凸壳。

top/down[x]表示横坐标为x的点的纵坐标是什么

**对于check操作：** 判断当前点的上下边界是什么然后返回结果

**对于delete操作：** 当前点如果已经在凸包内，删除之

**对于insert操作：** 在当前位置加上一个点，然后delete掉被包括在内部的点

数学要求：叉积

**喜闻乐见代码系列**

```cpp
#include<bits/stdc++.h>
#include<iostream>
#include<cstdio>
#define ll long long
#define map_it map<ll,ll>::iterator
using namespace std;

ll n;
map<ll,ll> top,down;

inline ll read(){
	ll x=0,tmp=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-') tmp=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<3)+(x<<1)+(ch^48);
		ch=getchar();
	}
	return tmp*x;
}

inline bool check_top(ll x,ll y){
    map_it i=top.lower_bound(x);
    if(i==top.end()) return 0;
    if(i->first==x) return y<=i->second;
    if(i==top.begin()) return 0;
    map_it j=i; j--;
    return (i->first-j->first)*(y-j->second)-(i->second-j->second)*(x-j->first)<=0;
}

inline bool check_down(ll x,ll y){
    map_it i=down.lower_bound(x);
    if(i==down.end()) return 0;
    if(i->first==x) return y>=i->second;
    if(i==down.begin()) return 0;
    map_it j=i; j--;
    return (i->first-j->first)*(y-j->second)-(i->second-j->second)*(x-j->first)>=0;
}

inline bool delete_top(map_it i){
	if(i==top.begin()) return 0;
	map_it j=i,k=i; j--; k++;
	if(k==top.end()) return 0;
	if((i->first-j->first)*(k->second-j->second)-(i->second-j->second)*(k->first-j->first)>=0){
		top.erase(i);
		return 1;
	}
	return 0;
}

inline bool delete_down(map_it i){
	if(i==down.begin()) return 0;
	map_it j=i,k=i; j--; k++;
	if(k==down.end()) return 0;
	if((i->first-j->first)*(k->second-j->second)-(i->second-j->second)*(k->first-j->first)<=0){
		down.erase(i);
		return 1;
	}
	return 0;
}

inline void insert_top(ll x,ll y){
	if(check_top(x,y)) return;
	top[x]=y;
	map_it i=top.find(x),j=i;
	if(i!=top.begin()){
		j--;
		while(delete_top(j++)) j--;
	}
	if(++j!=top.end()) while(delete_top(j--)) j++;
}

inline void insert_down(ll x,ll y){
	if(check_down(x,y)) return;
	down[x]=y;
	map_it i=down.find(x),j=i;
	if(i!=down.begin()){
		j--;
		while(delete_down(j++)) j--;
	}
	if(++j!=down.end()) while(delete_down(j--)) j++;
}

int main(){
	n=read();
	for(ll i=1; i<=n; i++){
		ll op=read(),x=read(),y=read();
		if(op==1){
			insert_top(x,y);
			insert_down(x,y);
		}
		else{
			if(check_top(x,y)&&check_down(x,y)) puts("YES");
			else puts("NO");
		}
	}
	return 0;
}
```

---

## 作者：OIer_Tan (赞：4)

[CF 传送门](https://codeforces.com/problemset/problem/70/D)  [洛谷传送门](https://www.luogu.com.cn/problem/CF70D)

一道动态凸包板子。

闲话：前两天 @[\_radio\_](https://www.luogu.com.cn/user/996338) 还在问我有没有这种题，结果今天就翻到了。

## 题意

有两种操作，一种是插入点 $(x,y)$，另外一种是查询点 $(x,y)$ 是否在凸壳包含的范围内。

## 思路

考虑用 `set` 分别维护上下凸壳。

对于操作 $1$，可以对于上下凸壳分别判断是否需要插入，再将点插入到对应的位置，然后像静态凸包那样删除凸包内多余的点。\
平均时间复杂度 $O(\log q)$。

对于操作 $2$，可以直接查询点分别在在上下凸壳的哪两点之间，然后用向量叉积判断在这两个点组成的线段的上方或者下方或者重合即可。\
时间复杂度 $O(\log q)$。

总时间复杂度 $O(q\log q)$。

需要注意的是，对于横坐标相同的点，你只能保留后来的那个店，否则会神秘过不了样例。

## 代码

```cpp
#include<bits/stdc++.h>

#ifndef CRT
#define endl '\n' 
#endif

using namespace std ;

typedef long long ll ;
typedef unsigned long long ull ;
typedef long double ld ;

struct point 
{
	ll x , y ;
	point ( const ll & x = 0 , const ll & y = 0 ) : x ( x ) , y ( y ) {}
	friend bool operator < ( const point & a , const point & b )
	{
//		if ( a.x == b.x )
//		{
//			return a.y < b.y ;
//		}
		return a.x < b.x ;
	}
};

ld det ( const point & a , const point & b )
{
	return a.x * b.y - b.x * a.y ; 
}

ll q ;

set <point> up , down ;

bool check_up ( const point & s )
{
	auto it = up.lower_bound ( s ) ;
	if ( it == up.end () )
	{
		return 0 ;
	}
	if ( it -> x == s.x )
	{
		return s.y <= ( it -> y ) ;
	}
	if ( it == up.begin () )
	{
		return 0 ;
	}
	auto it2 = prev ( it ) ;
	return det ( point ( it -> x - it2 -> x , it -> y - it2 -> y ) , point ( s.x - it2 -> x , s.y - it2 -> y ) ) <= 0 ;
}

bool check_down ( const point & s )
{
	auto it = down.lower_bound ( s ) ;
	if ( it == down.end () )
	{
//		cout << "SHAPINGBA" << endl ;
		return 0 ;
	}
	if ( it -> x == s.x )
	{
		return s.y >= ( it -> y ) ;
	}
	if ( it == down.begin () )
	{
//		cout << "YANGJIAPING" << endl ;
		return 0 ;
	}
	auto it2 = prev ( it ) ;
	return det ( point ( it -> x - it2 -> x , it -> y - it2 -> y ) , point ( s.x - it2 -> x , s.y - it2 -> y ) ) >= 0 ;
}

bool query ()
{
	point s ;
	cin >> s.x >> s.y ;
	if ( ! check_up ( s ) )
	{
//		cout << "YUHEXIAN" << endl ;
		return 0 ;
	}
	if ( ! check_down ( s ) )
	{
//		cout << "JIANGTIAOXIAN" << endl ;
		return 0 ;
	}
	return 1 ;
}

bool remove_up ( const set <point>::iterator it )
{
	if ( it == up.begin () )
	{
		return 0 ;
	}
	auto it2 = it , it3 = it ;
	it2 -- , it3 ++ ;
	if ( it3 == up.end () )
	{
		return 0 ;
	}
	if ( det ( point ( it -> x - it2 -> x , it -> y - it2 -> y ) , point ( it3 -> x - it2 -> x , it3 -> y - it2 -> y ) ) >= 0 )
	{
		up.erase ( it ) ;
		return 1 ;
	}
	return 0 ;
}

bool remove_down ( const set <point>::iterator it )
{
	if ( it == down.begin () )
	{
		return 0 ;
	}
	auto it2 = it , it3 = it ;
	it2 -- , it3 ++ ;
	if ( it3 == down.end () )
	{
		return 0 ;
	}
	if ( det ( point ( it -> x - it2 -> x , it -> y - it2 -> y ) , point ( it3 -> x - it2 -> x , it3 -> y - it2 -> y ) ) <= 0 )
	{
		down.erase ( it ) ;
		return 1 ;
	}
	return 0 ;
}

void update_up ( const point & s )
{
	if ( check_up ( s ) )
	{
		return ;
	}
	up.erase ( up.lower_bound ( point ( s.x , -1e9 ) ) , up.upper_bound ( point ( s.x , 1e9 ) ) ) ;
	auto it = up.insert ( s ).first , it2 = it ;
	if ( it != up.begin () )
	{
		it2 -- ;
		while ( remove_up ( it2 ++ ) ) it2 -- ;
	}
	if ( ++ it2 != up.end () )
	{
		while ( remove_up ( it2 -- ) ) ++ it2 ;
	}
}


void update_down ( const point & s )
{
	if ( check_down ( s ) )
	{
		return ;
	}
	down.erase ( down.lower_bound ( point ( s.x , -1e9 ) ) , down.upper_bound ( point ( s.x , 1e9 ) ) ) ;
	auto it = down.insert ( s ).first , it2 = it ;
	if ( it != down.begin () )
	{
		it2 -- ;
		while ( remove_down ( it2 ++ ) ) it2 -- ;
	}
	if ( ++ it2 != down.end () )
	{
		while ( remove_down ( it2 -- ) ) ++ it2 ;
	}
}

void update ()
{
	point s ;
	cin >> s.x >> s.y ;
	update_up ( s ) ;
	update_down ( s ) ;
	return ;
}

int main ()
{
	// freopen ( ".in" , "r" , stdin ) ;
	// freopen ( ".out" , "w" , stdout ) ;
	ios::sync_with_stdio ( 0 ) ;
	cin.tie ( 0 ) ;
	cout.tie ( 0 ) ;
	cin >> q ;
	while ( q -- )
	{
		ll opt ;
		cin >> opt ;
		if ( opt == 1 )
		{
			update () ;
		}
		else
		{
			cout << ( query () ? "YES" : "NO" ) << endl ;
		}
	}
	return 0 ;
}
```

---

## 作者：seika27 (赞：3)

### 思路
我们现在已经有了一个三个点的凸包，我们有两个 ```map```，分别是 ```up``` 和 ```lw```。

一个用来维护上凸壳，一个用来维护下凸壳。

那么我们先来对操作二进行分析。

一个点要在凸包之内，横坐标的限制很好搞定，纵坐标怎么办呢。

对于一个上凸壳，我们把第一个横坐标大于检查点横坐标的点记作 $(a,b)$，第一个横坐标小于检查点横坐标的点记作 $(c,d)$，把检查点记作 $(p,q)$。

我们令 $k_{ca}$ 表示为经过 $(c,d)$ 和 $(a,b)$ 的一条直线的斜率，令 $k_{cp}$ 表示为经过 $(c,d)$ 和 $(p,q)$ 的一条直线的斜率。

只有 $k_{ca}\geq k_{cp}$ 时，我们的查询点才在上凸壳之下。

当然如果有横坐标相等的点直接判一下纵坐标的大小就好。

我们当然可以把这个做法推广到下凸壳，那么我们也可以判断一个点在不在下凸壳之上了。

如果一个点既在上凸壳之下，又在下凸壳之上，那么这个点肯定在这个凸包之中。

在这里给出判断代码。

注意，为了防止精度问题这里交叉相乘了。

```cpp
inline bool checklw(int x,int y)
{
	auto it=lw.lower_bound(x);
	if(it==lw.end())return 0;
	if(it->first==x)return y>=it->second;
	if(it==lw.begin())return 0;
	auto pre=it;
	--pre;
	return ((it->second)-(pre->second))*(x-(pre->first))<=(y-(pre->second))*((it->first)-(pre->first));
}
inline bool checkup(int x,int y)
{
	auto it=up.lower_bound(x);
	if(it==up.end())return 0;
	if(it->first==x)return y<=it->second;
	if(it==up.begin())return 0;
	auto pre=it;
	--pre;
	return ((it->second)-(pre->second))*(x-(pre->first))>=(y-(pre->second))*((it->first)-(pre->first));
}
```

接下来我们考虑加入一个点后，如何维护这个凸包。

当我们加入一个新点后，如果在凸包内就不管，如果在上凸壳之上就加入上凸壳，在下凸壳之下就加入下凸壳。

假设这里我们把这个点放在了上凸壳上，那么加入一个新点之后，自然会有原来的一些点被删除。删除的规则很简单，我们求出要判断的点的前后一个点，然后比较斜率即可。

这里给出删除的代码。



```cpp
inline bool delup(auto it)
{
	if(it==up.begin())return 0;
	auto pre=it,nxt=it;
	--pre,++nxt;
	if(nxt==up.end())return 0;
	if(((nxt->second)-(pre->second))*((it->first)-(pre->first))<((it->second)-(pre->second))*((nxt->first)-(pre->first)))return 0;
	up.erase(it);
	return 1;
}
inline bool dellw(auto it)
{
	if(it==lw.begin())return 0;
	auto pre=it,nxt=it;
	--pre,++nxt;
	if(nxt==lw.end())return 0;
	if(((nxt->second)-(pre->second))*((it->first)-(pre->first))>((it->second)-(pre->second))*((nxt->first)-(pre->first)))return 0;
	lw.erase(it);
	return 1;
}
```

最后一个就是加点了，其实本质上就是一个套用删除函数的循环，没有什么好讲的，只是需要注意迭代器一些神秘小规则。


```cpp
inline void addup(int x,int y)
{
	if(checkup(x,y))return;
	up[x]=y;
	auto it=up.find(x),chg=it;
	if(it!=up.begin())
	{
		--chg;
		while(delup(chg++))--chg;
	}
	if(++chg!=up.end())while(delup(chg--))++chg;
	return;
}
inline void addlw(int x,int y)
{
	if(checklw(x,y))return;
	lw[x]=y;
	auto it=lw.find(x),chg=it;
	if(it!=lw.begin())
	{
		--chg;
		while(dellw(chg++))--chg;
	}
	if(++chg==lw.end())return;
	while(dellw(chg--))++chg;
	return;
}
```

到这里这道题就差不多了，主函数就不放了很简单，也是纪念一下第一道紫的计算几何，当然差不多止步于此了。

---

## 作者：Cat_shao (赞：3)

建凸包，除了 Andrew 算法还有 Graham 扫描法。然而有人认为“极角排序”丢精度、效率低，这里我给一个不需要 atan2 的极角排序。

### 怎么“极角排序”

![](https://cdn.jsdelivr.net/gh/Cat-shao/MyPic2@master/dymanic-convexhull-1)

为了方便，我们定义从原点沿 $y$ 轴负半轴方向的向量角度最小，逆时针旋转越来越大。


![](https://cdn.jsdelivr.net/gh/Cat-shao/MyPic2@master/dymanic-convexhull-2)

例如上图 $a$ 的角度小于 $b$ 的角度。

一个朴素的想法：判断两个向量 $a$ 的角度是否小于 $b$ 的角度，可以通过 $a$ 的斜率与 $b$ 的斜率比较。但是向量在 $y$ 轴上时没法计算斜率，我们需要一些特判。
1. 如果 $a, b$ 在 $y$ 轴右侧，$a$ 的角度比 $b$ 的角度小且当 $a$ 的斜率小于 $b$ 的斜率。
2. 如果 $a, b$ 在 $y$ 轴左侧或其中一个在 $y$ 轴上另一个在 $y$ 轴左侧，将它们绕原点旋转 $180^{\circ}$ 二者角度关系不变，变成了第一种情况。
3. 如果 $a, b$ 在 $y$ 轴两侧，哪个在右侧哪个角度小。
4. 当 $a, b$ 在 $y$ 轴上时，谁朝下谁角度小。二者都朝下，角度相同。
5. 当 $a$ 在 $y$ 轴上，$b$ 在 $y$ 轴右侧（从情况 2 转换来的），如果 $a$ 朝下那么 $a$ 角度小，如果 $a$ 朝上 $a$ 角度大。$b$ 在 $y$ 轴上时类似。

原点不会出现在凸包的边缘上，不需要考虑原点的角度。

```cpp
bool operator<(vec a, vec b) {
    if (a.x == 0 && b.x == 0) {
        if (signbit(a.y) == signbit(b.y)) { // 4
            return false;
        }
        return a.y < 0;
    }
    if (a.x <= 0 && b.x <= 0) { // 2
        return -a < -b;
    }
    if ((a.x == 0 && a.y < 0) || (b.x == 0 && b.y > 0)) { // 5
        return true;
    }
    if ((a.x == 0 && a.y > 0) || (b.x == 0 && b.y < 0)) { // 5
        return false;
    }
    if (signbit(a.x) != signbit(b.x)) { // 3
        return a.x > b.x;
    }
    return (long long) a.y * b.x < (long long) b.y * a.x; // 1
}
```

### 剩下的部分

我们把给我们所有的点的坐标都乘上 3 。由一开始的三个点，计算出这三个点围成的三角形的重心（因为坐标都乘上 3 所以重心的坐标必为整数），并将所有点一起平移，使得重心落在原点上。这样处理方便我们比较角度。

用平衡树维护凸包边缘上的点（向量），按极角排序。

![](https://cdn.jsdelivr.net/gh/Cat-shao/MyPic2@master/dymanic-convexhull-4)

考虑怎么做询问。记给我们的向量为 $b$ ，在凸包边缘上角度小于 $b$ 且最大的向量为 $a$ （$b$ 的前驱），角度大于等于 $b$ 且最小的向量为 $c$ （$b$ 的后继）。判断 $b$ 是否在凸包上（内部和边缘），只需要判断 $b$ 是否在 $ac$ 的左侧或边缘，即 $\overrightarrow{ac} \times \overrightarrow{ab} \ge 0$ 。

```cpp
// 这里实现的是 "b" 是不是在凸包外。hull 是 std::set 。prev 不是 std::prev ，是我自己写的 prev 。
// prev(hull.begin()) == std::prev(hull.end()) 。
// 同理下面 insert 中的 next 也不是 std::next ，是我自己写的 next 。
bool outHull(vec b) {
    auto it = hull.lower_bound(b);
    if (it == hull.end()) {
        it = hull.begin();
    }
    auto c = *it, a = *prev(it);
    return cross({a, c}, {a, b}) < 0;
}
```

![](https://cdn.jsdelivr.net/gh/Cat-shao/MyPic2@master/dymanic-convexhull-6-new)


考虑怎么做插入。首先判断给我们的点 $p$ 是不是在凸包上（内部和边缘）。如果在凸包上那么就不用插入了。然后把 $p$ 插入到平衡树中。如左上图，逆时针，给 $p$ 周围的向量起个名。 $p$ 插入后 $d, c, p$ 是凹的，即 $\overrightarrow{pc} \times \overrightarrow{cd} \le 0$ ，删除 $c$ 。删完后可能还是凹的，重复这个过程。同理 $p, b, a$ 是凹的，即 $\overrightarrow{pb} \times \overrightarrow{ba} \ge 0$ ，把 $b$ 删掉，如果还是凹的就重复这个过程。

```cpp
void insert(vec v) {
    hull.erase(v); // 方向相同的向量会被判为相等
    auto it = hull.insert(v).first;
    while (cross({*it, *next(it)}, {*next(it), *next(it, 2)}) <= 0) {
        hull.erase(*next(it));
    }
    while (cross({*it, *prev(it)}, {*prev(it), *prev(it, 2)}) >= 0) {
        hull.erase(*prev(it));
    }
}
```

分析下时间复杂度，平衡树选用红黑树，查找 $\Theta(\log n)$ ，插入 $O(1)$ ，删除 $O(1)$ 。对于询问，相当于两次查找，时间复杂度是 $\Theta(\log n)$ 。对于插入，查找 $p$ 需要插入的位置 $\Theta(\log n)$ ，由于一个点只能删除一次，均摊到每次操作 1 就是 $O(1)$ 的，所以时间复杂度是均摊 $\Theta(\log n)$ 。

### 题外话

注意到插入的时间复杂度是均摊 $\Theta(\log n)$ ，有没有什么严格 $\Theta(\log n)$ 的做法？答案是有的。《COMPUTATIONAL GEOMETRY AN INTRODUCTION》中 3.3.6 节提到了这一做法，3.3.7 节提到了有插入、删除维护动态凸包的 $\Theta(\log^2 n)$ 做法。各位有兴趣可以去看看，讲得挺好。

不难想出本题还有一个询问 $\Theta(\log n)$ ，插入 $\Theta(\sqrt{n})$ 的做法，基于块状链表。不好说实现出来有没有我上文介绍了一大顿类似 Graham 扫描法的解法快。说到效率，我开了 Ofast 和快读后就拿到 codeforces 上的最优解了。[测评记录](https://codeforces.com/contest/70/submission/164984350)

有问题可以在评论区中问我。如果发现了我的题解有错误麻烦各位指出，谢谢。

---

## 作者：GKxx (赞：3)

这题居然搞了我一晚上。。。

首先题面的翻译并不清晰，如果仔细阅读英文原题会看到，询问的是点(x,y)是否在凸包内部（含边界），~~可能也只有我这种傻x一开始理解成了询问在不在凸包上~~，以及还有一句话没有翻译：所有加入集合S的点都不同。

然后来说这题怎么做。回顾我们求凸包的过程：先按坐标排序，然后先求个上凸壳，再求个下凸壳，围起来就是整个凸包。所以这题我们也可以用两个数据结构分别维护上凸壳和下凸壳。

考虑用平衡树来维护凸壳。以上凸壳为例。先不考虑一些边界之类的细节问题，加入一个点的时候，首先要判断它是否会产生影响，即如果它在现有的凸包内部（上凸壳的下方，下凸壳的上方）就直接退出。在已知它一定会加入凸包的情况下，考虑它左右的点是否会形成凹的图形，这里可以用叉积来判断。叉积一定要开long long！

比方说如果加入上凸壳的点P(x, y)，左边第一个点是A，第二个点是B，如果折线BAP向下凹就要删除A，然后继续这样做下去。对右边也这样做，然后对下凸壳也是一样。

具体的实现上，注意到因为我们是维护上凸壳和下凸壳，因此在一个凸壳上，所有的点的x坐标两两不同，因此我们可以用std::map<int, int>来维护，以横坐标为关键字，纵坐标为值。在迭代器的使用上要倍加小心，仔细考虑边界情况，具体可以看代码。

最后再介绍一下我在代码中使用的，令很多OIer深恶痛绝的std::next（以及它的兄弟std::prev）。自C++11起，头文件<iterator>中，命名空间std内新增了三个函数：std::advance, std::next, std::prev。其中std::next和std::prev都是转而调用std::advance。std::next接受两个参数，第一个是迭代器i，第二个是一个带符号整数n（默认为1），会返回一个迭代器，指向i往后移n的位置。std::prev也一样，唯一的区别是它往前移。作为一个看完了整本《C++Primer》的人，我表示C++Primer上并没有提到三个函数......我也是查了cppreference才知道。好在我从来都没有用bits/stdc++.h库和写using namespace std的习惯，因此从来没有因为next而CE过。。。
  
完整代码：

```cpp
#include <cctype>
#include <cstdio>
#include <climits>
#include <algorithm>
#include <map>
#include <iterator>

template <typename T> inline void read(T& t) {
    int f = 0, c = getchar(); t = 0;
    while (!isdigit(c)) f |= c == '-', c = getchar();
    while (isdigit(c)) t = t * 10 + c - 48, c = getchar();
    if (f) t = -t;
}
template <typename T, typename... Args>
inline void read(T& t, Args&... args) {
    read(t); read(args...);
}

#define rep(I, A, B) for (int I = (A); I <= (B); ++I)
#define rrep(I, A, B) for (int I = (A); I >= (B); --I)
#define erep(I, X) for (int I = head[X]; I; I = next[I])

std::map<int, int> up, down;
int n;

inline long long cross(int x1, int y1, int x2, int y2) {
    return 1ll * x1 * y2 - 1ll * x2 * y1;
}
inline bool checkUp(int x, int y) {
    auto pos = up.lower_bound(x);
    if (pos == up.end()) return false;
    if (pos->first == x) return y <= pos->second;
    if (pos == up.begin()) return false;
    auto prev = std::prev(pos);
    return cross(x - prev->first, y - prev->second, pos->first - prev->first, pos->second - prev->second) >= 0;
}
inline bool checkDown(int x, int y) {
    auto pos = down.lower_bound(x);
    if (pos == down.end()) return false;
    if (pos->first == x) return y >= pos->second;
    if (pos == down.begin()) return false;
    auto prev = std::prev(pos);
    return cross(x - prev->first, y - prev->second, pos->first - prev->first, pos->second - prev->second) <= 0;
}
inline void insertUp(int x, int y) {
    if (checkUp(x, y)) return;
    up[x] = y;
    auto pos = up.find(x);
    auto next = std::next(pos);
    if (next != up.end()) {
        auto next2 = std::next(next);
        while (next2 != up.end()) {
            if (cross(next->first - x, next->second - y, next2->first - x, next2->second - y) >= 0) {
                up.erase(next);
                next = next2;
                next2 = std::next(next2);
            } else break;
        }
    }
    if (pos == up.begin()) return;
    auto prev = std::prev(pos);
    while (prev != up.begin()) {
        auto prev2 = std::prev(prev);
        if (cross(prev->first - x, prev->second - y, prev2->first - x, prev2->second - y) <= 0) {
            up.erase(prev);
            prev = prev2;
        } else break;
    }
}
inline void insertDown(int x, int y) {
    if (checkDown(x, y)) return;
    down[x] = y;
    auto pos = down.find(x);
    auto next = std::next(pos);
    if (next != down.end()) {
        auto next2 = std::next(next);
        while (next2 != down.end()) {
            if (cross(next->first - x, next->second - y, next2->first - x, next2->second - y) <= 0) {
                down.erase(next);
                next = next2;
                next2 = std::next(next2);
            } else break;
        }
    }
    if (pos == down.begin()) return;
    auto prev = std::prev(pos);
    while (prev != down.begin()) {
        auto prev2 = std::prev(prev);
        if (cross(prev->first - x, prev->second - y, prev2->first - x, prev2->second - y) >= 0) {
            down.erase(prev);
            prev = prev2;
        } else break;
    }
}

int main() {
    read(n);
    rep(i, 1, n) {
        int q, x, y;
        read(q, x, y);
        if (q == 1) {
            insertUp(x, y);
            insertDown(x, y);
        } else {
            puts(checkUp(x, y) && checkDown(x, y) ? "YES" : "NO");
        }
    }
    return 0;
}
```

---

## 作者：Meteor_ (赞：2)

# CF70D Professor's task 题解

## 前言

此篇题解用的是 Andrew，不想看这种做法的可以绕道。

## 题意

动态凸包板子题。

维护动态凸包。两种操作，加一个点或查询一个点是否在凸包内。

## 题解

首先你得会[静态二维凸包](https://www.luogu.com.cn/problem/P2742)。

维护二维凸包的方法挺多的，比如什么 Andrew 算法，Jarvis 算法还有 Graham 扫描法，极角法（当然我个人认为极角法不太好，掉精啥的麻烦），在二维凸包板子题的题解里里有一位大佬写的非常好，给个[链接](https://www.luogu.com.cn/blog/ShineEternal/convex-hull)（会的可以略过此部分）。

我觉得 Andrew 好打还方便 ~~我就会这一个~~ 所以这里用的 Andrew 算法。

考虑怎么维护动态的凸包。

对于查询，我们比较好办，只需要查一下它是不是在下凸壳上面并且在上凸壳下面，如果是，那就在里面，不是，则不在。

怎么查？向量积（叉乘）呗。$\operatorname {check}$ 函数不就出来了吗。

那怎么加点？

先想想静态凸包我们干了点什么：

1. 以横坐标为第一关键字，纵坐标为第二关键字排了遍序；

2. 每次叉乘判断是否加入一个新点；

3. 加入的过程中弹出原来的不是最优的点。

所以我们现在也需要维护这些东西：

1. 需要一直保证有序，于是选用 map，方便一会用指针遍历，也能保证有序；

2. 加入新点也是一样的，还是叉乘判断；

3. 弹出有点麻烦，不想原来那样打个指针走就行，这次得打个函数，因为我们需要维护那个 map。

就没了。

总结一下：$\operatorname {check}$ 函数，$\operatorname {insert}$ 函数，$\operatorname {remove}$ 函数，上凸壳和下凸壳都各自需要这三个函数，所以总共是 $6$ 个。具体细节见代码。

说一下时间复杂度。

第一篇题解的时间复杂度讲的有点，，，反正我猛一下没看懂，但是还是比较好分析的。

每一个点最多都会加一次再弹出一次，单次加进去和单次弹出都是 $O(\log n)$，于是总的就是 $O(n \log n)$。

## 代码

```cpp
//https://www.luogu.com.cn/problem/CF70D CF70D Professor's task
#include <bits/stdc++.h>
#define int long long
#define P pair<int, int>
#define MP make_pair

using namespace std;

int n;
map<int, int> top, bottom;

P operator - (P x, P y) {return {y.first - x.first, y.second - x.second};}

inline int cross(P x, P y) {return x.first * y.second - x.second * y.first;}

inline bool check_top (int x, int y) {
    auto pos = top.lower_bound(x);
    if(pos == top.end())
        return false;
    if(pos -> first == x)
        return y <= pos -> second;
    if(pos == top.begin())
        return false;
    auto pre = pos;
    -- pre;
    return cross(MP(pre -> first, pre -> second) - MP(pos -> first, pos -> second), MP(pre -> first, pre -> second) - MP(x, y)) <= 0;
}

inline bool check_bottom(int x, int y) {
    auto pos = bottom.lower_bound(x);
    if(pos == bottom.end())
        return false;
    if(pos -> first == x)
        return y >= pos -> second;
    if(pos == bottom.begin())
        return false;
    auto pre = pos;
    -- pre;
    return cross(MP(pre -> first, pre -> second) - MP(pos -> first, pos -> second), MP(pre -> first, pre -> second) - MP(x, y)) >= 0;
}

inline bool remove_top(map<int, int>::iterator pos) {
    if(pos == top.begin())
        return false;
    auto pre = pos, nex = pos;
    -- pre, ++ nex;
    if(nex == top.end())
        return false;
    if(cross(MP(pre -> first, pre -> second) - MP(pos -> first, pos -> second), MP(pre -> first, pre -> second) - MP(nex -> first, nex -> second)) < 0)
        return false;
    top.erase(pos);
    return true;
}

inline bool remove_bottom(map<int, int>::iterator pos) {
    if(pos == bottom.begin())
        return false;
    auto pre = pos, nex = pos;
    -- pre, ++ nex;
    if(nex == bottom.end())
        return false;
    if(cross(MP(pre -> first, pre -> second) - MP(pos -> first, pos -> second), MP(pre -> first, pre -> second) - MP(nex -> first, nex -> second)) > 0)
        return false;
    bottom.erase(pos);
    return true;
}

inline void add_top(int x, int y) {
    if(check_top(x, y))
        return;
    top[x] = y;
    auto pos = top.find(x), ji = pos;
    if(pos != top.begin()) {
        -- ji;
        while(remove_top(ji ++))
            -- ji;
    }
    if(++ ji != top.end())
        while(remove_top(ji --))
            ++ ji;
}

inline void add_bottom(int x, int y) {
    if(check_bottom(x, y))
        return;
    bottom[x] = y;
    auto pos = bottom.find(x), ji = pos;
    if(pos != bottom.begin()) {
        -- ji;
        while(remove_bottom(ji ++))
            -- ji;
    }
    if(++ ji != bottom.end())
        while(remove_bottom(ji --))
            ++ ji;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> n;
    for(int i = 1; i <= n; ++ i) {
        int op, x, y;
        cin >> op >> x >> y;
        if(op == 1) {
            add_top(x, y);
            add_bottom(x, y);
        }
        else {
            if(check_top(x, y) && check_bottom(x, y))
                cout << "YES\n";
            else
                cout << "NO\n";
        }
    }
}
```

---

## 作者：StaroForgin (赞：2)

## 题解

这道题很明显是让你动态维护凸包并判断点是否在凸包内。

这里给出一种很奇怪的动态维护凸包的方法，是笔者在上课时偶然想到的。

首先我们考虑凸包上的点具有什么特殊性质。

![image-20210806222231759](https://cdn.luogu.com.cn/upload/image_hosting/txz5321o.png)

很明显，凸包上的点一定会存在一条为某个斜率的直线从无限远处向凸包平移时第一个碰到它，也就是这个点与这个凸包"相切"。

我们设对于凸包上的点 $(x,y)$，它的对应直线斜率为 $k$，明显有 $y=kx+b$。由于它是被第一个碰到的，所以 $b$ 要么是所有点中最大的，要么是所有点中最小的。

我们将直线的表达式改写成一般式 $ax+by=c$，我们的目的是让 $c$ 最小。

而当 $k$ 一定时 $a$ 与 $b$ 一定呈某种倍数关系，这个倍数是一定的，所以我们当 $a$ 一定时 $b$ 只与 $k$ 有关，我们不妨设 $a+b=1$，可得 $ax_0\pm(1-a)y_0=a(x_0\pm y_0)\mp y_0=c$。

同样在一般式中依旧有对于凸包上的点，存在某个斜率使得该点对应的 $c$ 是所有点中最大或者最小的，即 $\exist x,(x_0\pm y_0)x\mp y_0=\min((x_i\pm y_i)x\mp y_i)$。

对于每个点，我们可以将 $c$ 的值与斜率的关系转化成一个一次函数：$f_i(x)=(x_i\pm y_i)x\mp y_i$。如果这个函数能在 $x\in[0,1]$ 中存在比其它的 $f$ 函数值都大/小的时候，那么它就一定是凸包上的点。

这明显可以用李超线段树来进行维护，$x$ 的取值区间为 $[0,1]$，在这个区间中用动态开点的方式维护所有点的函数，如果该函数在某个位置可以更新原线段树，那么它就可以成为凸包上的点。

插入一个点明显是 $\log\,n$ 的，直接像维护一次函数一样暴力插入即可。

而查询时可能出现它在这个位置上比当前节点的函数大，但却没有某个祖先的函数大的情况，所以我们需要在查询的过程中同时下传它比所有祖先的函数值都大的取值范围，这很明显可以直接解出来，在向子孙下传时需要更新，查询的时间复杂度仍然是 $\log\,n$。

 总时间复杂度 $O\left(n\log\,n\right)$，但由于要维护四个函数，常数可能会有点大。

## 源码

```cpp
#include<cstdio>
#include<cmath>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
#define MAXN 100005
#define lowbit(x) (x&-x)
#define reg register
#define pb push_back
#define mkpr make_pair
#define fir first
#define sec second
typedef long long LL;
typedef unsigned long long uLL;
const int mo=998244353;
const int jzm=2333;
const int lim=15;
const int orG=3,invG=332748118;
const double Pi=acos(-1.0);
const double eps=1e-7;
typedef pair<int,int> pii;
template<typename _T>
_T Fabs(_T x){return x<0?-x:x;}
template<typename _T>
void read(_T &x){
	_T f=1;x=0;char s=getchar();
	while(s>'9'||s<'0'){if(s=='-')f=-1;s=getchar();}
	while('0'<=s&&s<='9'){x=(x<<3)+(x<<1)+(s^48);s=getchar();}
	x*=f;
}
template<typename _T>
void print(_T x){if(x<0){x=(~x)+1;putchar('-');}if(x>9)print(x/10);putchar(x%10+'0');}
LL gcd(LL a,LL b){return !b?a:gcd(b,a%b);}
int add(int x,int y,int p){return x+y<p?x+y:x+y-p;}
int qkpow(int a,int s,int p){int t=1;while(s){if(s&1LL)t=1ll*a*t%p;a=1ll*a*a%p;s>>=1LL;}return t;}
int q;
struct line{
	double k,b;line(){k=b=0;}
	line(double K,double B){k=K;b=B;}
	double ask(const double x){return k*x+b;}
};
struct ming{line mx;int lson,rson;ming(){mx=line(-1e9,-1e9);lson=rson=0;}};
class LiCao_SegmentTree{
	private:
		int tot;ming tr[MAXN];
	public:
		int root;line nd;
		void insert(int &rt,double l,double r,line aw,int dep){
			if(l>r||!dep)return ;if(!rt)rt=++tot;const double mid=(l+r)/2.0;
			if(tr[rt].mx.ask(mid)<aw.ask(mid))swap(tr[rt].mx,aw);
			if(tr[rt].mx.ask(l)<aw.ask(l))insert(tr[rt].lson,l,mid,aw,dep-1);
			if(tr[rt].mx.ask(r)<aw.ask(r))insert(tr[rt].rson,mid,r,aw,dep-1);
		}
		bool query(int rt,double l,double r,line aw,double al,double ar){
			if(al>ar)return 0;const double mid=(l+r)/2.0;
			if(!rt||(al<=mid&&mid<=ar&&tr[rt].mx.ask(mid)<aw.ask(mid)))return 1;double bl=al,br=ar;
			if(tr[rt].mx.ask(l)<aw.ask(l)||tr[rt].mx.ask(mid)<aw.ask(mid)){
				ar=min(ar,mid);
				if(tr[rt].mx.ask(al)>aw.ask(al))al=max(al,(tr[rt].mx.b-aw.b)/(aw.k-tr[rt].mx.k))+eps;
				if(tr[rt].mx.ask(ar)>aw.ask(ar))ar=min(ar,(tr[rt].mx.b-aw.b)/(aw.k-tr[rt].mx.k))-eps;
				if(query(tr[rt].lson,l,mid,aw,al,ar))return 1;
			}
			if(tr[rt].mx.ask(r)<aw.ask(r)||tr[rt].mx.ask(mid)<aw.ask(mid)){
				al=bl;ar=br;al=max(al,mid);
				if(tr[rt].mx.ask(al)>aw.ask(al))al=max(al,(tr[rt].mx.b-aw.b)/(aw.k-tr[rt].mx.k))+eps;
				if(tr[rt].mx.ask(ar)>aw.ask(ar))ar=min(ar,(tr[rt].mx.b-aw.b)/(aw.k-tr[rt].mx.k))-eps;
				if(query(tr[rt].rson,mid,r,aw,al,ar))return 1;
			}
			return 0;
		}
}T[4];
signed main(){
	read(q);
	for(int i=1;i<=q;i++){
		int opt,x,y;read(opt);read(x);read(y);
		line tmp1=line(1.0*x+1.0*y,-1.0*y),tmp2=line(1.0*x-1.0*y,1.0*y);
		line tmp3=line(-1.0*x-1.0*y,1.0*y),tmp4=line(1.0*y-1.0*x,-1.0*y);
		if(opt==1)
			T[0].insert(T[0].root,0.0,1.0,tmp1,lim),
			T[1].insert(T[1].root,0.0,1.0,tmp2,lim),
			T[2].insert(T[2].root,0.0,1.0,tmp3,lim),
			T[3].insert(T[3].root,0.0,1.0,tmp4,lim);
		else{
			bool tp1=T[0].query(T[0].root,0.0,1.0,tmp1,0.0,1.0);if(tp1){puts("NO");continue;}
			bool tp2=T[1].query(T[1].root,0.0,1.0,tmp2,0.0,1.0);if(tp2){puts("NO");continue;}
			bool tp3=T[2].query(T[2].root,0.0,1.0,tmp3,0.0,1.0);if(tp3){puts("NO");continue;}
			bool tp4=T[3].query(T[3].root,0.0,1.0,tmp4,0.0,1.0);if(tp4){puts("NO");continue;}
			puts("YES");
		}
	}
	return 0;
}

```





---

## 作者：hzy1 (赞：1)

## 动态凸包

分别用两个 $\text{std::map}$：$top$ 与 $down$ 来维护上下凸包。需要支持：
- 单点加入。
- 单点询问与凸包位置关系。

其中 $top[x]/down[x]$ 表示的是凸包上横坐标为 $x$ 的点的纵坐标，即 $top[x]/down[x]=y$。

### 基本函数
$\text{vec()}$ 将两个点转化为向量，$\text{cross}$ 是叉积。与静态凸包一样。
```cpp
pii vec(pii x, pii y) {
	return {y.first - x.first, y.second - x.second};
}
int cross(pii a, pii b) {
	return a.first * b.second - a.second * b.first;
}
```

### 判断点是否在凸包内部
如图，以上凸包为例，蓝点在凸包内部，红点在外部。
![](https://cdn.luogu.com.cn/upload/image_hosting/go3tijzo.png)

所以判断是否在内部与静态凸包基本一样，用叉积或者斜率判断即可。

具体地，在维护上凸包时，如果由 $i-1$ 与 $i$ 构成的向量 $×$ 由 $i-1$ 与 $x$ 构成的向量 $\le 0$，那么就是图中的蓝点蓝线情况。红点同理。

斜率也一样。总之对着图画一画就能画出来。

代码，以上凸包为例：
```cpp
bool inside_top(int x, int y) {
	auto it = top.lower_bound(x);
	if(it == top.end()) return false;
	if(it->first == x) return y <= it->second;
	if(it == top.begin()) return false;
	auto i = it, j = it;
	--j;
	return cross(vec({j->first, j->second}, {i->first, i->second}), vec({j->first, j->second}, {x, y})) <= 0;
}
```

### 凸包上单点删除
这个操作是用来删除凸包上不合法的点的，在单点插入时需要使用。

通过点 $i$ 与它两边的点的斜率关系来判断是否删除。

代码，以上凸包为例：
```cpp
bool delete_top(map<int,int>::iterator i) {
	if(i == top.begin()) return false;
	auto j = i, k = i; 
	--j;
	++k;
	if(k == top.end()) return false;
	if(cross(vec({j->first, j->second}, {i->first, i->second}), vec({j->first, j->second}, {k->first, k->second})) >= 0) {
		top.erase(i);
		return true;
	}
	return false;
}
```

### 单点插入
以上凸包为例，插入点 $(x,y)$时：

先令 $top[x]=y$，然后不断删除左右两边不符合条件的点，需要用到上面的单点删除。

代码：
> 关于 $\text{std::next}$ 与 $\text{std::prev}$：给它一个迭代器 $it$，返回 $it$ 的下一个/上一个迭代器。

```cpp
void insert_top(int x, int y) {
	if(inside_top(x, y)) return;
	top[x] = y;
	auto i = top.find(x), j = i;
	if(i != top.begin()) {// 向左边删 
		--j;
		auto next_j = next(j); 
		while(delete_top(j)) {
			j = next_j; 
			--j;
			next_j = next(j);
		}
		++j;
	}
//	assert(j == i); 
	if(j != top.end()) { //向右边删 
		while(++j != top.end()) {
			auto prev_j = prev(j);
			while(delete_top(j)) {
				j = prev_j;
				++j;
				prev_j = prev(j);
			}
		}
	}
}
```

但是这个写法有点蠢，并且 $\text{std::next}$ 与 $\text{std::prev}$ 常数有点大，比 $it++/it--$ 慢。

所以网上更通用的写法大概是这样：
```cpp
void insert_top(int x, int y) {
	if(inside_top(x, y)) return;
	top[x] = y;
	auto i = top.find(x), j = i;
	if(i != top.begin()) {
		--j;
		while(delete_top(j++)) --j;
		//注意上面这一行，最后一次会 j++ 但是不会 --j
	}
	if(++j != top.end()) {
		while(delete_top(j--)) ++j;
		//同理
	}
}
```

代码短，跑得还快，真香~

自此，我们已经写学习了动态凸包所需的所有操作！

### 模板：CF70D. Professor's task

[代码戳这里](https://www.luogu.com.cn/paste/lto905of)



---

## 作者：Melo_DDD (赞：0)

居然能写模版题题解。我喜欢计算几何。

维护两种操作：

- 加入一个点，实时维护当前点集的凸包。

- 查询一个点是否在当前点集的凸包内。

**注意：凸壳上的点的横坐标是严格单增的。**

与静态的凸包相类似，我们的凸包可以拆成上凸壳和下凸壳，分别维护这两个即可。

平衡树有点麻烦，可以用 map，原因是既可以简便赋值还可以 $\Theta(\log n)$ 地查找。

对于查询操作，一个点在凸包上等价于在上凸壳下方同时在下凸壳上方（当然也可以在凸壳上）。这里的“下”是严格的下，左下或者右下不算，“上”同理。

那么对于一个点，我们首先判断它是否已经跑到了整个凸包的左侧或者右侧（这样肯定不行），之后找到凸壳上它左右两边距离最近的两个点，用向量叉积判断是否合法即可。

对于插入操作，注意到当前这个点需要更新凸包的充要条件是它不在原凸包里面，分别尝试更新上凸壳和下凸壳即可。

整体复杂度 $\Theta(n\log n)$，可以通过本题。

更详细的解释在代码里：

```cpp
#include <bits/stdc++.h>
#define int long long 

#define fi first 
#define se second 
#define mk std :: make_pair 
#define iter std :: map < int ,int > :: iterator 
using pii = std :: pair < int ,int > ; 

template < typename T > inline void read ( T &x ) {
	x = 0 ;
	bool flag (0) ; char ch = getchar () ;
	while (! isdigit (ch))
	{ flag = ch == '-' ; ch = getchar () ;}
	while (isdigit (ch))
	{ x = (x << 1) + (x << 3) + (ch ^ 48) ; ch = getchar () ;}
	flag ? x = - x : 0 ;
} template < typename T ,typename ...Args >
inline void read ( T & x ,Args &...tmp ) { read (x) ,read (tmp...) ;}

int q ; std :: map < int ,int > top ,bot ;
// top 和 bot 分别维护上下凸壳

inline pii operator - (const pii & ,const pii &) ;
inline int cross (const pii & ,const pii &) ;

namespace convhull {
	inline bool check_top (const pii &) ;
	inline bool check_bot (const pii &) ;
	
	inline bool del_top (iter it) ;
	inline bool del_bot (iter it) ;
	
	inline void add_top (const pii &) ;
	inline void add_bot (const pii &) ;
}

signed main () {
	read (q) ; while (q --) {
		int op ,x ,y ; read (op ,x ,y) ;
		if (op == 1) {
			convhull :: add_top (mk (x ,y)) ;
			convhull :: add_bot (mk (x ,y)) ;
		} else {
			const pii a = mk (x ,y) ;
			if (convhull :: check_top (a) && convhull :: check_bot (a)) puts ("YES") ;
			else puts ("NO") ;
		}
	}
	return 0 ;
}

inline pii operator - (const pii &a ,const pii &b) 
{ return mk (a.fi - b.fi ,a.se - b.se) ;}
inline int cross (const pii &a ,const pii &b) 
{ return a.fi * b.se - b.fi * a.se ;}

namespace convhull {
	inline bool check_top (const pii &a) {
		iter it = top.lower_bound (a.fi) ;
		if (it == top.end ()) return false ; // 在整个凸壳的右侧
		if (it -> fi == a.fi)	
			return a.se <= it -> se ; // 直接和凸壳上横坐标相同的点比较即可
		if (it == top.begin ()) return false ; // 在整个凸壳左边
		iter it_ = it ; it_ -- ;
		const pii b = mk (it -> fi ,it -> se) ,c = mk (it_ -> fi ,it_ -> se) ;
		return cross (b - c ,a - c) <= 0ll ; // 叉积判断
	}
	inline bool check_bot (const pii &a) {
		iter it = bot.lower_bound (a.fi) ;
		if (it == bot.end ()) return false ;
		if (it -> fi == a.fi) 
			return a.se >= it -> se ;
		if (it == bot.begin ()) return false ;
		iter it_ = it ; it_ -- ;
		const pii b = mk (it -> fi ,it -> se) ,c = mk (it_ -> fi ,it_ -> se) ;
		return cross (b - c ,a - c) >= 0ll ;
 	} // 下凸壳同理
 	
 	inline bool del_top (iter it) { // 这个函数表示查询 it 指向的点是否需要被删去
 		if (it == top.begin ()) return false ; // 一个凸壳最左边的点不能删
 		iter bef ,af ; bef = af = it ;
 		bef -- ; af ++ ;
 		if (af == top.end ()) return false ;  // 最右边的也不能删
 		const pii a = mk (bef -> fi ,bef -> se) ,b = mk (it -> fi ,it -> se) ,
 				  c = mk (af -> fi ,af -> se) ;
 		if (cross (b - a ,c - b) < 0ll) return false ; // 不能取等
 		top.erase (it) ;
 		return true ;
	}
	inline bool del_bot (iter it) {
		if (it == bot.begin ()) return false ;
		iter bef ,af ; bef = af = it ;
		bef -- ; af ++ ;
		if (af == bot.end ()) return false ;
		const pii a = mk (bef -> fi ,bef -> se) ,b = mk (it -> fi ,it -> se) ,
				  c = mk (af -> fi ,af -> se) ;
		if (cross (b - a ,c - b) > 0ll) return false ; 
		bot.erase (it) ;
		return true ;
	}
	
	inline void add_top (const pii &a) {
		if (check_top (a)) return ; // 在凸包里面一定不需要更新
		top[a.fi] = a.se ; // 加入凸包
		iter it = top.find (a.fi) ,it_ = it ;
		if (it_ != top.begin ()) {
			it_ -- ;
			for ( ; del_top (it_ ++) ; it_ --) ;
		} if (++ it_ != top.end ()) 
			for ( ; del_top (it_ --) ; it_ ++) ;
                // 将不合法的点删了
	}
	inline void add_bot (const pii &a) {
		if (check_bot (a)) return ; 
		bot[a.fi] = a.se ;
		iter it = bot.find (a.fi) ,it_ = it ;
		if (it_ != bot.begin ()) {
			it_ -- ;
			for ( ; del_bot (it_ ++) ; it_ --) ;
		} if (++ it_ != bot.end ()) 
			for ( ; del_bot (it_ --) ; it_ ++) ;
	}
}
```

---

## 作者：JimmyLee (赞：0)

# 题意

>实现以下两种操作:
>
>1. 往点集 $S$ 中添加一个点 $(x,y)$。
>
>2. 询问点 $(x,y)$ 是否在点集 $S$ 的凸包中。
>

# 分析

动态凸包板子。

建议先完成 [P2521 [HAOI2011] 防线修建](https://www.luogu.com.cn/problem/P2521)。

上题维护的是上半个凸包，本题维护上下两个。

将凸包中的点按 $x$ 排序，通过 $(x,y)$ 前驱和后继连成的直线判断 $(x,y)$ 是否位于凸包内。

若在凸包外，则加入这个点，并删除当前凸包中所有不符合凸包性质的点。

---

考虑使用平衡树。

既然只用查前驱和后继，用 `set` 就能解决。

为了便于计算，定义结构体 `vec`。

```cpp
struct vec
{
    double x, y;
    vec(double X=0, double Y=0): x(X), y(Y) {}
    friend vec operator-(vec a, vec b) {return {a.x-b.x, a.y-b.y};}
    friend double cross(vec a, vec b) {return a.x*b.y-a.y*b.x;}
    bool operator<(vec b) const {return x<b.x;}
};
```

因为要维护上下两个凸包，再封装一个结构体存凸包。

```cpp
struct convex_hull:set<vec>
{
    auto pre(iterator it) {return --it;}
    auto aft(iterator it) {return ++it;}

    bool is_up; // 记录该凸包为上凸包还是下凸包
    convex_hull(bool x): is_up(x) {}
```

通过前驱和后继检查该点是否在凸包内：

```cpp
bool chk(vec A)
{
    auto it=lower_bound(A);
    if(it==end()) return 0;
    if(it->x==A.x) 
        return is_up?it->y>=A.y:it->y<=A.y;
    if(it==begin()) return 0;
    vec B=*it, C=*--it;
    double st=cross(B-A, B-C);
    return is_up?st<=0:st>=0;
}
```

从凸包中移除一个点：

```cpp
bool remove(set<vec>::iterator it)
{
    if(it==begin()) return 0;
    auto itl=pre(it);
    auto itr=aft(it);
    if(itr==end()) return 0;
    vec a=*it-*itl, b=*itr-*it;
    if(is_up?cross(a, b)<0:cross(a, b)>0) return 0;
    return erase(it), 1;
}
```

向凸包中加入一个点：

```cpp
void append(vec A)
{
    if(chk(A)) return;
    auto it=find(A);
    if(it!=end()) erase(it);
    it=insert(A).first;
    while(it!=begin()&&remove(pre(it)));
    while(aft(it)!=end()&&remove(aft(it)));
}
```

每个点最多进一次凸包点集，也最多出一次凸包点集，时间复杂度 $O(n\log n)$。

[AC 记录](https://codeforces.com/contest/70/submission/276510518)

---

