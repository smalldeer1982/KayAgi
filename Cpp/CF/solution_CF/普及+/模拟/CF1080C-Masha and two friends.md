# Masha and two friends

## 题目描述

Masha 有一个宽度为 $n$，长度为 $m$ 的国际象棋盘。

这个象棋盘左下角的坐标为 $(1,1)$，且颜色为白色。(象棋盘是黑白相间的)

现在 Maxim 首先选择了一个矩形，并把这个矩形内的象棋盘刷成了白色，然后 Denis 又选择了一个矩形并把这个矩形内的象棋盘刷成了黑色。 (注意先后顺序)

请输出这个象棋盘最后有多少个黑色格子，多少个白色格子。

## 说明/提示

$1\leq t\leq 10^3$

$1 \leq n,m \leq 10^9$

$1 \leq x1 \leq x2 \leq m$, $1 \leq x3 \leq x4 \leq m$

$1 \leq y1 \leq y2 \leq n$, $1 \leq y3 \leq y4 \leq n$

## 样例 #1

### 输入

```
5
2 2
1 1 2 2
1 1 2 2
3 4
2 2 3 2
3 1 4 3
1 5
1 1 5 1
3 1 5 1
4 4
1 1 4 2
1 3 4 4
3 4
1 2 4 2
2 1 3 3
```

### 输出

```
0 4
3 9
2 3
8 8
4 8
```

# 题解

## 作者：Siyuan (赞：7)

[$$\Large\texttt{My Blog}$$](https://hydingsy.github.io/)

---

> 题目链接：[Codeforces 1080C](https://codeforces.com/contest/1080/problem/C)

在一个 $n\times m$ 的国际象棋棋盘内，其中 $(1,1)$ 的格子为白色，首先将一个子矩形全都染成白色，再将一个子矩形全都染成黑色（两次染色有先后顺序）。求最后有多少个白色格子和黑色格子（多组数据）。

数据范围：$1\leqslant T\leqslant 10^3$，$1\leqslant n,m\leqslant 10^9$

------

## Solution

因为只有两次染色，所以我们只需要分类讨论就行了！

首先我们记 $B(x_1,y_1,x_2,y_2)$ 和 $W(x_1,y_1,x_2,y_2)$ 分别为矩形 $(x_1,y_1),(x_2,y_2)$ 内的黑色和白色格子数量。经过推算我们可以得到，白色格子的增量为：$B(x_1,y_1,x_2,y_2)-B((x_1,y_1,x_2,y_2)\cap(x_3,y_3,x_4,y_4))-W(x3,y3,x4,y4)$。其中第二项括号内的 $\cap$ 表示两个矩形的交集（如果没有交集，则第二项的值为 $0$）。

对于如何求 $B$ 和 $W$，直接分类讨论或者拆成 $4$ 个矩形容斥均可！

**时间复杂度**：$O(T)$

------

## Code

```cpp
#include <cstdio>
#include <algorithm>

long long getblack(int x1,int y1,int x2,int y2) {
    bool opt=(x1+y1)&1;
    int n=x2-x1+1,m=y2-y1+1;
    if(opt) return 1LL*n*(m/2)+((m&1)?(n/2)+(n&1):0);
    else return 1LL*n*(m/2)+((m&1)?(n/2):0);
}
long long getwhite(int x1,int y1,int x2,int y2) {
    return 1LL*(x2-x1+1)*(y2-y1+1)-getblack(x1,y1,x2,y2);
}
int main() {
    int T;
    for(scanf("%d",&T);T--;) {
        int n,m,x1,y1,x2,y2,x3,y3,x4,y4;
        scanf("%d%d",&n,&m),n^=m^=n^=m;
        long long s1=getwhite(1,1,n,m);
        scanf("%d%d%d%d%d%d%d%d",&x1,&y1,&x2,&y2,&x3,&y3,&x4,&y4);
        int u=std::max(x1,x3),d=std::min(x2,x4);
        int l=std::max(y1,y3),r=std::min(y2,y4);
        if(u<=d&&l<=r) {
            s1+=getblack(x1,y1,x2,y2)-getblack(u,l,d,r)-getwhite(x3,y3,x4,y4);
        } else {
            s1+=getblack(x1,y1,x2,y2)-getwhite(x3,y3,x4,y4);
        }
        printf("%I64d %I64d\n",s1,1LL*n*m-s1);
    }
    return 0;
}
```



---

## 作者：Ted_Tong (赞：5)

### 分析
我们对一个棋盘填色，不仅仅只是减去一半就完了，对于长宽都是奇数的棋盘，我们要特别判断。例如：

1 0 1

0 1 0

1 0 1

（1是黑，0是白）

这样的棋盘如果我们涂黑，就是涂$9/2+1$个，根据题意，当一个格子奇偶相同，那么就是白色，不同就是黑色。

我们就先涂白的，再不考虑交集涂黑的，那么你会问了，如果有交集，黑的不就涂少了？对，是涂少了，我们再判断加上就好了。

例如，
交集是：

1 0 1

0 1 0

1 0 1

我们先涂白：

0 0 0

0 0 0

0 0 0

再不考虑涂白，将它涂黑：

0 1 0 

1 0 1

0 1 0

那么我们就要处理，将它变成这样：

1 1 1

1 1 1

1 1 1

这不就是再进行一遍涂黑的工作吗？

好，讲到这，你应该懂了。
### 参考代码

```cpp
//  奇偶相同是白
#include <iostream>
#include <cstdio>
#define ll long long
using namespace std;
ll t,n,m,black,white;
int main() {
    cin>>t;
    for (int tt=1; tt<=t; tt++) {
        cin>>n>>m;
        black=white=(n*m)/2;
        if ((n*m) & 1) {
            white++;
        }
        ll ax1,ax2,ay1,ay2,bx1,bx2,by1,by2;
        cin>>ax1>>ay1>>ax2>>ay2>>bx1>>by1>>bx2>>by2;
        //white
        ll achang=ax2-ax1+1,akuan=ay2-ay1+1;
        white+=(achang*akuan)/2;
        black-=(achang*akuan)/2;
        if ((achang & 1) && (akuan & 1) && ((ax1 & 1)!=(ay1 & 1))) {//如果长和宽都是奇数，而且左下角的还是黑色 
            white++;
            black--;
        }
        //black
        achang=bx2-bx1+1;
        akuan=by2-by1+1;
        white-=(achang*akuan)/2;
        black+=(achang*akuan)/2;
        if ((achang & 1) && (akuan & 1) && ((bx1 & 1)==(by1 & 1))) {//如果长和宽都是奇数，而且左下角的还是白色 
            white--;
            black++;
        }
        //cover
        ll x1=max(ax1,bx1),y1=max(ay1,by1),x2=min(ax2,bx2),y2=min(ay2,by2); 
        if ((x2-x1+1)>0 && (y2-y1+1)>0) {//如果有交集 
            achang=x2-x1+1;
            akuan=y2-y1+1;
            white-=(achang*akuan)/2;
            black+=(achang*akuan)/2;
            if ((achang & 1) && (akuan & 1) && ((x1 & 1)!=(y1 & 1))) {////如果长和宽都是奇数，而且左下角的还是黑色  
                white--;
                black++;
            }
        }
        cout<<white<<" "<<black<<endl;
    }
    return 0;
}


```

---

## 作者：dblark (赞：3)

发一波Codeforces的Pascal题解~~~

又是大数据，显然$O(n)$。

首先我们先算出开始黑白块的数量。黑白各一半，因为左下角为白色，所以如果有奇数块，白色还要+1。

然后第一次染色。把一个矩形涂成黑色。不难处理，把这块矩形里的白色块染成黑色就行了，原来的黑色块不用管。

这里要注意怎么计算白色块的数量：照例是平分。但是如果有奇数块的话要判断了，如果左下角是白色块，白色块比黑色块多，那么白色块+1，否则就不需要了。

判断一个某一块是白是黑不难，算$(x+y) MOD 2$，是$1$就是白色，是$0$就是黑色。

第二次染色同第一次。

但是有特殊情况：两个矩形重叠了，那么重叠的部分还要进行一些判断。

这里给出计算两个矩形的办法：$(x1,y1,x2,y2)\cap (x3,y3,x4,y4)=(max(x1,x3),max(y1,y3),min(x2,x4),min(y2,y4))$

明显当$max(x1,x3)>min(x2,x4)$或$max(y1,y3)>min(y2,y4)$时没有真正的重叠部分。

那么有重叠部分处理也不难。

重叠部分的这一块，白色因为已经被染成了黑色，但后来又染成了白色，应该是要计算的，但是漏了。所以实际上要把这部分白色变成黑色。

所以代码就来了：

```pas
var
  t,i,n,m,x1,x2,x3,x4,y1,y2,y3,y4,x5,y5,x6,y6:longint;
  s1,s2,t1,t2,t3,t4:int64;
function max(x,y:longint):longint;//没什么好说的
begin
  if x>y then
    exit(x)
  else
    exit(y);
end;
function min(x,y:longint):longint;
begin
  if x<y then
    exit(x)
  else
    exit(y);
end;
begin
  read(t);
  for i:=1 to t do
  begin
    read(n,m,x1,y1,x2,y2,x3,y3,x4,y4);
    x5:=max(x1,x3);            //这里处理一下重叠的部分
    y5:=max(y1,y3);
    x6:=min(x2,x4);
    y6:=min(y2,y4);
    t1:=int64(n)*m;            //棋盘有几块
    t2:=int64(x2-x1+1)*(y2-y1+1);//涂黑的有几块
    t3:=int64(x4-x3+1)*(y4-y3+1);//涂白的有几块
    s1:=t1 div 2+t1 mod 2;     //开始棋盘上的白块
    s2:=t1 div 2;              //开始棋盘上的黑块
    inc(s1,t2 div 2);          //这里处理涂黑
    dec(s2,t2 div 2);
    if (x1+y1) mod 2=1 then    //如果左下角是白块特殊处理
    begin
      inc(s1,t2 mod 2);
      dec(s2,t2 mod 2);
    end;
    dec(s1,t3 div 2);          //这里处理涂白，跟上面差不多
    inc(s2,t3 div 2);
    if (x3+y3) mod 2=0 then    //如果左下角是黑块特殊处理
    begin
      dec(s1,t3 mod 2);
      inc(s2,t3 mod 2);
    end;
    if (x5<=x6) and (y5<=y6) then//如果有重叠部分
    begin
      t4:=int64(x6-x5+1)*(y6-y5+1);//重叠部分有几块
      dec(s1,t4 div 2);        //处理：把这里的白块变成黑块
      inc(s2,t4 div 2);
      if (x5+y5) mod 2=1 then
      begin
        dec(s1,t4 mod 2);
        inc(s2,t4 mod 2);
      end;
    end;
    writeln(s1,' ',s2);
  end;
end.
```

---

## 作者：WuMin4 (赞：1)

## [CF1080C Masha and two friends](https://codeforces.com/problemset/problem/1080/C)

## 题意

给出一个边长为 $n$ 的黑白相间的棋盘，在两块矩形区域**分别**染上白色和黑色，问最后棋盘上黑色和白色格子的数量。

## 思路

~~这是 1500？外国人均模拟大佬（bushi。~~

考虑如何快速计算出一块矩形区域的白色和黑色格子数量。

容易发现当矩形面积为偶数时，白色和黑色格子的数量是一样多的，因为白色数量和黑色数量之差无论如何都不会超过 $1$。

当面积为奇数时，若矩形左下角的方块为白色，则白色比黑色多 $1$，反之黑色比白色多 $1$。

考虑两矩形区域之间没有交集时如何计算面积。

![](https://cdn.luogu.com.cn/upload/image_hosting/pp61oar3.png)

假如给绿色区域染白，红色区域染黑，容易发现白色面积增加了白色区域的黑色格子数量，黑色面积增加了黑色区域的白色格子数量，然后再来考虑有交集时的数量。

![](https://cdn.luogu.com.cn/upload/image_hosting/y6m4nvlp.png)

容易发现按照原来的方法算格子数量的话，因为白色先染，黑色后染，所以白色会多算交集的黑色部分，黑色会少算交集的白色部分。

设两矩形左下角和右上角坐标分别为 $(x1,y1),(x2,y2),(X1,Y1),(X2,Y2)$，则交集矩形坐标可以简单地表示为 $(\max(x1,X1),\max(y1,Y1)),(\min(x2,X2),\min(y2,Y2))$。

## 代码

```cpp
#include <bits/stdc++.h>
#define bc(x,y,xx,yy) (x>xx||y>yy?0:(xx-x+1)*(yy-y+1)%2==0?(xx-x+1)*(yy-y+1)/2:(x+y)%2==0?(xx-x+1)*(yy-y+1)/2:(xx-x+1)*(yy-y+1)/2+1)
#define wc(x,y,xx,yy) ((xx-x+1)*(yy-y+1)-bc(x,y,xx,yy))
using namespace std;
#define int long long
int T,n,m,x,y,_x,_y,X,Y,_X,_Y;
signed main() {
	cin>>T;
	while(T--){
		cin>>n>>m;
		cin>>x>>y>>_x>>_y;
		cin>>X>>Y>>_X>>_Y;
		cout<<wc(1,1,n,m)+bc(x,y,_x,_y)-wc(X,Y,_X,_Y)-bc(max(x,X),max(y,Y),min(_x,_X),min(_y,_Y))<<" ";
		cout<<bc(1,1,n,m)-bc(x,y,_x,_y)+wc(X,Y,_X,_Y)+bc(max(x,X),max(y,Y),min(_x,_X),min(_y,_Y))<<endl;
	}
	return 0; 
}
```

---

## 作者：C6H14 (赞：1)

## 一点废话

[题目传送门](https://www.luogu.com.cn/problem/CF1080C)

[My blog](https://www.luogu.com.cn/blog/128433/#)

## 思路

假设一块矩形长为 $x$，宽为 $y$，左下角的方块是白色，那么矩形中黑色格子数量为 $\left\lfloor \dfrac{xy}{2} \right\rfloor$；反之亦然。

分两种情况讨论答案：

情况 $1$：两个矩形没有交集，假设白色矩形中原来有 $a$ 块黑色格子，黑色矩形中原来有 $b$ 块白色格子，那么答案就是$\left\lceil \dfrac{xy}{2} \right\rceil+a-b$；

情况 $2$：两个矩形有交集，设白色矩形中原来有 $a$ 块黑色格子，黑色矩形中原来有 $b$ 块白色格子，交集处有 $c$ 块黑色格子，那么答案就是 $\left\lceil \dfrac{xy}{2} \right\rceil+a-b-c$。

时间复杂度为 $\Theta(t)$，空间复杂度为 $\Theta(1)$。

## 代码

```cpp
ll q,n,m,w,b,col,x,y;
ll white(ll x,ll y,ll col)
{
	if (col)
		return x*y>>1;
	return x*y-(x*y>>1);
}
ll black(ll x,ll y,ll col)
{
	if (!col)
		return x*y>>1;
	return x*y-(x*y>>1);
}
ll color(ll x,ll y)
{
	if ((x&1)^(y&1)) return 1;
	return 0;
}
int main()
{
	q=read();
	while (q--)
	{
		n=read(),m=read();
		b=n*m>>1;
		w=n*m-b;
		ll ta=read(),tb=read(),tc=read(),td=read(),ma=read(),mb=read(),mc=read(),md=read();
		x=min(tc,mc)-max(ta,ma)+1,y=min(td,md)-max(tb,mb)+1;
		if (x>0 && y>0)
		{
			w-=white(mc-ma+1,md-mb+1,color(ma,mb));
			w+=black(tc-ta+1,td-tb+1,color(ta,tb));
			w-=black(x,y,color(max(ta,ma),max(tb,mb)));
		}
		else
		{
			w+=black(tc-ta+1,td-tb+1,color(ta,tb))-white(mc-ma+1,md-mb+1,color(ma,mb));
		}
		write(w,' '),write(n*m-w,'\n');
	}
	return 0;
}
```

---

## 作者：浮光掠影 (赞：0)

### 【题目大意】

一个 $n\times m$ 的国际象棋棋盘，左下角为白格，接下来将棋盘的一个矩形所有格染白，再将另一个矩形所有格染黑，问白格和黑格各有多少个，多组数据。

### 【解题思路】

先设置一个函数，只要知道左下角的位置是黑色还是白色，然后知道这个选中的方格的大小，然后就可以算出里面的黑格和白格算出来。

然后进行容斥：

定义：$F1$ 为 $A$ 选中的方框，$F2$ 为 $B$ 选中的方框，$F3$ 为矩阵的面积。

白格 $=$ 原来白格 $+$ $F1$ 黑 $-$ $F2$ 白 $-$ $F3$ 黑色。

黑格 $=$ 原来黑格 $-$ $F1$ 黑 $+$ $F2$ 白 $+$ $F3$ 白色。

主要是求出这个矩阵的面积并首先是求出两个长方形的排序，然后把它们的交点，通过最大最小值比较得出两个交点。最后就是把这个矩阵算出来 $F3$ 的黑格。

### 【Code】


```cpp
#include<bits/stdc++.h>
#define mkp make_pair
#define fi first
#define se second
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;
ll n,m;
pii ans;

ll read()
{
	ll ret=0,f=1;char c=getchar();
	while(!isdigit(c)) {if(c=='-')f=0;c=getchar();}
	while(isdigit(c)) ret=ret*10+(c^48),c=getchar();
	return f?ret:-ret;
}

struct point{ll x,y;};
struct node
{
	point a,b;
	node(){}
	node(ll x,ll y,ll xx,ll yy){a.x=x;a.y=y;b.x=xx;b.y=yy;}
	void init(){a.x=read();a.y=read();b.x=read();b.y=read();}
}p1,p2,emp;

pii operator -(const pii&x,const pii &y){return mkp(x.fi-y.fi,x.se-y.se);} 
pii operator +(const pii&x,const pii &y){return mkp(x.fi+y.fi,x.se+y.se);} 
pii calc(ll x,ll y)
{
	if(!x || !y) return mkp(0,0);
	if((ll)x*y%2==0) return mkp((ll)x*y/2,(ll)x*y/2);
	return mkp((ll)x*y/2+1,(ll)x*y/2);
}
pii get(const point &a,const point &b){return calc(b.x,b.y)-calc(b.x,a.y-1)-calc(a.x-1,b.y)+calc(a.x-1,a.y-1);}
ll getsize(const point &a,const point &b){return (ll)(b.x-a.x+1)*(b.y-a.y+1);}

node getmerge(node a,node b)
{
	if(a.a.x>b.a.x) swap(a,b);
	if(b.a.x>a.b.x) return emp;
	if(b.b.y<a.a.y) return emp;
	if(b.a.y>a.b.y) return emp;
	return node(max(a.a.x,b.a.x),max(a.a.y,b.a.y),min(a.b.x,b.b.x),min(a.b.y,b.b.y));
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("C.in","r",stdin);
	freopen("C.out","w",stdout);
#endif
	int T=read();emp=node(-1,-1,-1,-1);
	while(T--)
	{
		n=read();m=read();
		p1.init();p2.init();
		pii t1=calc(n,m),t2=get(p1.a,p1.b),t3=get(p2.a,p2.b);
		node tmp=getmerge(p1,p2);
		if(tmp.a.x==-1)
		{
			ans.fi=t1.fi-t2.fi-t3.fi+getsize(p1.a,p1.b);
			ans.se=t1.se-t2.se-t3.se+getsize(p2.a,p2.b);
		}
		else
		{
			pii t4=get(tmp.a,tmp.b);
			ans.fi=t1.fi-t2.fi-t3.fi+t4.fi+getsize(p1.a,p1.b)-getsize(tmp.a,tmp.b);
			ans.se=t1.se-t2.se-t3.se+t4.se+getsize(p2.a,p2.b);
		}
		printf("%lld %lld\n",ans.fi,ans.se);
	}

	return 0;
}

```

---

## 作者：Ouaoan (赞：0)

题目：[Masha and two friends](https://www.luogu.org/problemnew/show/CF1080C)

----

[更好阅读体验?](https://blog.csdn.net/rabbit_ZAR/article/details/85269867)


---

思路：

首先这题思路很简单，模拟+容斥就可以了。

即 最终的白块数 = 原网格图的白块数 + 涂白增加的白块数 - 涂黑减少的白块数 - 又涂了白又涂了黑的那一块减少的白块数。

这里重点说下怎么求两矩形交，我最开始就是这里不会写的。

下面的题解大多分类讨论了，其实可以不用讨论的。

如图，要求黑色矩形和红色居心的交。

![](https://i.loli.net/2018/12/28/5c25a06ff2d06.png)

设黑色矩形左上角坐标 ( x1 , y1 )，右下角 ( x2 , y2 ) ; 

红矩形左上角坐标 ( a1 , b1 )，右下角 ( a2 , b2 )。

根据重点公式，可以算出 $O1 = ( \frac{ x1 + x2 }{2} , \frac{ y1 + y2 }{2} ) ，O2 = ( \frac{ a1 + a2 }{2} , \frac{ b1 + b2 }{2})$。

所以相交的条件就是：

$abs(\frac{ x1 + x2 }{2}-\frac{ a1 + a2 }{2})<=\frac{x2-x1}{2}+\frac{a2-a1}{2}$

且

$abs(\frac{ y1 + y2 }{2}-\frac{ b1 + b2 }{2})<=\frac{y2-y1}{2}+\frac{b2-b1}{2}$

整理得

$abs( x1 + x2 - a1 - a2)<=x2-x1+a2-a1$

且

$abs( y1 + y2 - b1 - b2)<=y2-y1+b2-b1$

判断完相交，就是求相交部分的坐标了。

也很好看出来，左上角是 $( max(x1,a1) , min(x2,a2))$，右下角是$(max(y1,b1),min(y2,b2))$。

---

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

#define read(x) scanf("%d",&x)
#define ll long long

ll gets(int x,int y) {
	return ((ll)x*y+1)/2;
}

ll find(int x1,int y1,int x2,int y2) {
	x1--,y1--;
	return gets(x2,y2)+gets(x1,y1)-gets(x1,y2)-gets(x2,y1);
}

int n,m;

int main() {
	int T;
	read(T);
	while(T--) {
		read(n),read(m);
		int x1,y1,x2,y2;
		read(x1),read(y1),read(x2),read(y2);
		int a1,b1,a2,b2;
		read(a1),read(b1),read(a2),read(b2);
		
		ll ans=find(1,1,n,m);
		ans+=((ll)x2-x1+1)*(y2-y1+1)-find(x1,y1,x2,y2);
		ans-=find(a1,b1,a2,b2);
		
		if(abs(x1+x2-a1-a2)<=(x2-x1+a2-a1)&&abs(y1+y2-b1-b2)<=(y2-y1+b2-b1)) {
			ans-=((ll)min(x2,a2)-max(x1,a1)+1)*(min(y2,b2)-max(y1,b1)+1)-find(max(x1,a1),max(y1,b1),min(x2,a2),min(y2,b2));
		}
		
		printf("%I64d %I64d\n",ans,((ll)n*m)-ans);
	}
	return 0; 
}
```


---

## 作者：小黑AWM (赞：0)

2018.11.24的CF_Round#524 div.2是一场时间很好，题目很水，适合上分的比赛（我从灰的边缘爬到了青呢23333

这是那天的C题

很水吧

首先解释下题面吧：**初始有一个黑白相间的矩阵，给出两次操作分别覆盖白色和黑色，请问操作后的黑白块总数**

嗯，看数据$n ≤ 10^8, t ≤ 10^3$，妥妥地找规律了

观察归纳发现以下规律，对于初始矩形，当横纵坐标奇偶性相同时为白点，否则为黑点，且对于任意一个矩形，在矩形面积为偶数时，黑白块数量相等，否则关于矩形角上的颜色分类讨论，当为黑色时，矩形中有n/2+1块黑色，n/2块白色，若为白色则相反。

有了这些规律我们就可以很容易的处理覆盖白色后的黑白块数了。是不是很简单。只需要把覆盖的矩形中的黑色块数减掉，再把白块数加上就行了。
***

然后就是黑块的事了。

为了方便，可以考虑把重叠部分还原为原始状态，然后在按照白色的逻辑做。

CF46ms

```cpp
#include <cstdio>
#include <iostream>
#define judge(x,y) ((x&1)==(y&1))
#define ll long long
#define max(a,b) a>b?a:b
#define min(a,b) a<b?a:b
using namespace std;
int t;
ll n, m, x1, y1, x2, y2, x3, y3, x4, y4;
ll white, black, size;
void work(ll size, bool color, int mode){//mode = 1 为白色 mode = -1 为黑色
    white = white + ((size>>1) + (color ? (size&1) : 0))*mode;
    black = black - ((size>>1) + (color ? (size&1) : 0))*mode;
}
int main(){
    cin >> t;
    while(t--){
        cin >> n >> m;
        white = n * m / 2 + ((n * m) & 1);
        black = n * m / 2;
        cin >> x1 >> y1 >> x2 >> y2;
        size = (x2 - x1 + 1) * (y2 - y1 + 1);
        work(size, !judge(x1, y1), 1);
        cin >> x3 >> y3 >> x4 >> y4;
        if(x3 <= x2 && x4 >= x1 && y4 >= y1 && y3 <= y2 ){//将重叠部分还原
            size = ((min(x2, x4)) - (max(x1, x3)) + 1) * ((min(y2, y4)) - (max(y1, y3)) + 1);
            ll x = min(x2, x4);
            ll y = min(y2, y4);
            work(size, !judge(x, y), -1);
        }
        work((x4 - x3 + 1) * (y4 - y3 + 1), judge(x3, y3), -1);

        cout << white << " " << black << endl;
    }
    return 0;
}

```


---

## 作者：little_sun (赞：0)

# 题解 CF1080C 【Masha and two friends】

## [安利博客](https://www.cnblogs.com/little-sun0331/p/10014591.html)

这道题要注意的细节超级多，是一道分类讨论好题

其实这道题要求的就是

白色：原白色面积$+$矩形$(x1, y1, x2, y2)$中的黑色面积-矩形$(x3, y3, x4, y4)$中白色面积-矩形$(x1, y1, x2, y2)$与矩形$(x3, y3, x4, y4)$交集中的白色面积(注：本处的黑/白色面积指原矩形中的黑/白面积)

黑色：总面积-白色

好了做完了

（注意：左下角为黑色的矩形中白色的个数为$\lfloor \frac{n*m}2 \rfloor$，左下角为白色的矩形中白色的个数为$\lceil \frac{n*m}2 \rceil$）

**Code：**
```cpp
#include <bits/stdc++.h>

#define ll long long

int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        ll n, m;
        ll x[10], y[10];
        scanf("%I64d%I64d", &n, &m);
        for (int i = 1; i <= 4; i++)
            scanf("%I64d%I64d", &x[i], &y[i]), std::swap(x[i], y[i]);
        ll w = (n * m + 1) / 2, b = (n * m) - w;
        ll c1 = (x[2] - x[1] + 1) * (y[2] - y[1] + 1) - (((x[2] - x[1] + 1) * (y[2] - y[1] + 1) + ((x[1] % 2) == (y[1] % 2))) / 2);
        w += c1, b -= c1;
        ll c2 = (((x[4] - x[3] + 1) * (y[4] - y[3] + 1) + ((x[3] % 2) == (y[3] % 2))) / 2);
        w -= c2, b += c2;
        ll c3 = 0;
        if (((std::min(x[2], x[4]) >= std::max(x[1], x[3])) && ((std::min(y[2], y[4]) >= std::max(y[1], y[3])))))
            c3 = ((std::min(x[2], x[4]) - std::max(x[1], x[3]) + 1) * (std::min(y[2], y[4]) - std::max(y[1], y[3]) + 1)) - ((((std::min(x[2], x[4]) - std::max(x[1], x[3]) + 1) * (std::min(y[2], y[4]) - std::max(y[1], y[3]) + 1))) + ((std::max(x[1], x[3]) % 2) == (std::max(y[1], y[3]) % 2))) / 2;
        c3 = std::max(c3, 0ll);
        w -= c3, b += c3;
        printf("%I64d %I64d\n", w, b);
    }
    return 0;
}
```

---

## 作者：Zechariah (赞：0)

细节题...  
对于一个如题染色的棋盘，如果格子总数为偶数，则黑白各占一半，否则四个角的颜色会多一个  
所以就直接求了，窝的方法是求出黑色格子的总数，用总格子数-黑格子数得到白格子数，刚开始先初始化ans=格子数/2，因为(1,1)是白的，要多一个也是白色多一个，然后第一个询问把范围内的黑色格子数剪掉，第二个询问把范围内原本应该是白色格子的总数加上，最后求一下两个询问的重合部分，这部分的黑色是被剪掉了的，所以加上重合部分原本是黑色的格子数
```
#include <bits/stdc++.h>
#define jh(x,y) (x^=y^=x^=y)
#define lowbit(x) (x&-x)
#define y1 y
#define int long long
const double PI = acos(-1.0);
const int N = 1e5 + 10, mod = 1e9 + 7;
using namespace std;
namespace fast_IO {
    int read()
    {
        register int num = 0;
        register char ch;
        register bool flag = false;
        while ((ch = getchar()) == ' ' || ch == '\n' || ch == '\r');
        if (ch == EOF)return ch; if (ch == '-')flag = true; else num = ch ^ 48;
        while ((ch = getchar()) != ' '&&ch != '\n'&&ch != '\r'&&~ch)
            num = (num << 1) + (num << 3) + (ch ^ 48);
        if (flag)return -num; return num;
    }
};
int x1, y, x2, y2, xx, yy, xx1, yy1, s1, t1, s2, t2, ans, n, m;

signed main()
{
    register int t = fast_IO::read();
    while (t--)
    {
        ans = s1 = t1 = s2 = t2 = 0;
        m = fast_IO::read(), n = fast_IO::read();
        ans = n * m /2;//ans Black
        x1 = fast_IO::read(), y = fast_IO::read(), x2 = fast_IO::read(), y2 = fast_IO::read();
        if (x1 > x2)jh(x1, x2); if (y > y2)jh(y, y2);
        ans -= (y2 - y + 1)*(x2 - x1 + 1) >> 1;
        if (((y2 - y + 1)*(x2 - x1 + 1) & 1) && (x1 + y & 1))--ans;
        xx = fast_IO::read(), yy = fast_IO::read(), xx1 = fast_IO::read(), yy1 = fast_IO::read();
        if (xx > xx1)jh(xx, xx1); if (yy > yy1)jh(yy, yy1);
        ans += ((yy1 - yy + 1)*(xx1 - xx + 1)) / 2;
        if (((yy1 - yy + 1)*(xx1 - xx + 1) & 1) && !(xx + yy & 1))++ans;
        s1 = max(x1, xx), t1 = max(y, yy), s2 = min(x2, xx1), t2 = min(y2, yy1);
        if (s1 > s2 || t1 > t2)s1 = t1 = s2 = t2 = 0;
        if (s1)ans += (t2 - t1 + 1)*(s2 - s1 + 1) >> 1;
        if (s1&&((t2 - t1 + 1)*(s2 - s1 + 1) & 1) && (s1 + t1 & 1))++ans;
        cout << (long long)n * m - ans << ' ' << ans << endl;
    }
    return 0;
}

```


---

## 作者：liuyz11 (赞：0)

原比赛题解：[https://www.cnblogs.com/nblyz2003/p/10014521.html]()

题意：有一个n * m的黑白相间的棋盘，(1, 1)为白色。现在把(x1, y1)到(x2, y2)这个矩阵涂白(x1 <= x2, y1 <= y2)，再把(x3, y3)到(x4, y4)这个矩阵涂黑(x3 <= x4, y3 <= y4)。现在问你有多少个黑格子和白格子。注：有多组数据。

A 、B两题都挺水，C、D开始就是数学题了，感觉自己好菜。

要求求黑格子和白格子，只要求其中一个就好了，另一个就是拿总个数减一下，我就是求白格子的个数。

这题看上去很烦（其实打起来也很烦），但其实就是原有的个数 + 第一次涂白的黑格子个数 - 第二次涂黑的白格子个数。

第一次涂白的黑格子数就是(x1, y1)到(x2,y2)这个矩阵中原有的黑格数（然而我统计了白格子个数再拿总数减）。

统计白格子的个数方法就是总的格子个数 / 2， 如果总个数是奇数，就看左下角是否是白格子((x + y) % 2 == 0)。求黑格子数也是一样。

求第二次涂黑的白格子个数是(x3, y3)到(x4, y4)这个矩阵原有的白格数 + 两次涂色相交的矩阵中原来黑格子的个数（因这些格子已经被涂成白色，已经被算入答案，要减掉）。

求区间内原有的黑白格数我就不再说了，主要就是求相交的矩阵。

先判断有无相交：

x2 < x3 || x1 > x4 || y2 < y3 || y1 > y4　　

可以画个图方便理解。

然后就是相交的矩阵的坐标。（用X1, Y1, X2, Y2表示）

X1 = max(x1, x3), X2 = min(x2, x4), Y1 = max(y1, y3), Y2 = min(y2, y4)
　　

这题就这样草率的讲完了，有不理解可以看代码画几个图模拟下。

代码如下

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#define rep(x, l, r) for(LL x = l; x <= r; x++)
#define repd(x, r, l) for(LL x = r; x >= l; x--)
#define clr(x,y) memset(x, y, sizeof(x))
#define all(x) x.begin(), x.end()
#define pb push_back
#define mp make_pair
#define MAXN
#define fi first
#define se second
#define SZ(x) ((LL)x.size())
using namespace std;
typedef long long LL;
typedef vector<LL> vi;
typedef pair<LL, LL> pii;
const LL INF = 1 << 30;
const LL p = 10000007;
LL lowbit(LL x){ return x & -x; }
LL fast_power(LL a, LL b){ LL x; for(x = 1; b; b >>= 1){ if(b & 1) x = 1ll * x * a % p; a = 1ll * a * a % p; } return x; }
//head by DYH

LL judge(LL x1, LL y1, LL x2, LL y2){
    LL x = x2 - x1 + 1, y = y2 - y1 + 1;
    LL res = x * y / 2;
    if(x * y % 2 == 1 && (x1 + y1) % 2 == 0) res++;
    return res;
}

LL check(LL x1, LL y1, LL x2, LL y2, LL x3, LL y3, LL x4, LL y4){
    if(x2 < x3 || x1 > x4 || y2 < y3 || y1 > y4) return 0;
    LL X1 = max(x1, x3), X2 = min(x2, x4), Y1 = max(y1, y3), Y2 = min(y2, y4);
    return (X2 - X1 + 1) * (Y2 - Y1 + 1) - judge(X1, Y1, X2, Y2);
}

int main(){
    LL t;
    scanf("%I64d", &t);
    rep(times, 1, t){
        LL n, m;
        scanf("%I64d%I64d", &n, &m);
        LL x1, y1, x2, y2, x3, y3, x4, y4;
        scanf("%lI64d%I64d%Id%I64d%I64d%I64d%I64d%I64d", &x1, &y1, &x2, &y2, &x3, &y3, &x4, &y4);
        LL ans = judge(1, 1, n, m);
        ans += (x2 - x1 + 1) * (y2 - y1 + 1) - judge(x1, y1, x2, y2);
        ans -= check(x1, y1, x2, y2, x3, y3, x4, y4) + judge(x3, y3, x4, y4);
        printf("%I64d %I64d\n", ans, n * m - ans);
    }
    return 0;
}
 Problem-C
```

---

