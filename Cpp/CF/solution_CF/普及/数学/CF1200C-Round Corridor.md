# Round Corridor

## 题目描述

Amugae is in a very large round corridor. The corridor consists of two areas. The inner area is equally divided by $ n $ sectors, and the outer area is equally divided by $ m $ sectors. A wall exists between each pair of sectors of same area (inner or outer), but there is no wall between the inner area and the outer area. A wall always exists at the 12 o'clock position.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1200C/7fdeabfa2ad973f1b56c678ed3354417ac806e5e.png)The inner area's sectors are denoted as $ (1,1), (1,2), \dots, (1,n) $ in clockwise direction. The outer area's sectors are denoted as $ (2,1), (2,2), \dots, (2,m) $ in the same manner. For a clear understanding, see the example image above.

Amugae wants to know if he can move from one sector to another sector. He has $ q $ questions.

For each question, check if he can move between two given sectors.

## 说明/提示

Example is shown on the picture in the statement.

## 样例 #1

### 输入

```
4 6 3
1 1 2 3
2 6 1 2
2 6 2 4
```

### 输出

```
YES
NO
YES
```

# 题解

## 作者：QwQcOrZ (赞：5)

### Update on 2020.6.5：添加了结论的证明

## 题意：

一个圆形走廊，给出里外的房间$n$和$m$，两间相邻的房间不连通，但是里外的房间连通（描述不清请看图理解）

## 题解：

显然房间会在 $lcm(len_1,len_2)$ 处不连通（$len_1,len_2$表示内外圈房间长度，可以用自己的方式表示），但是直接求 $lcm$ 会炸 $long$ $long$

怎么办？？？

~~__int128！！！（滑稽~~

我们发现，里面的房间会在第 $n/gcd(n,m)$ 个房间处截断，外面的房间会在第 $m/gcd(n,m)$ 个房间处截断

证明：

设走廊总长度是$n\times m$

那么内圈每个房间的长度就是 $n\times m/n=m$

外圈每个房间的长度就是 $n\times m/m=n$

于是显然内圈构成一个联通块的房间个数是 $lcm(m,n)/m=n\times m/gcd(n,m)/m=n/gcd(n,m)$

外圈个数则为 $lcm(m,n)/n=n\times m/gcd(n,m)/n=m/gcd(n,m)$

故此得证

于是我们可以就 $O(1)$ 计算出他们分别在哪个联通块里，接着直接判

然后就可以愉快的$AC$辣

$Code\ Below$

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
 
inline ll read()
{
	register ll s=0;
	register char c=getchar(),lc='+';
	while (c<'0'||'9'<c) lc=c,c=getchar();
	while ('0'<=c&&c<='9') s=s*10+c-'0',c=getchar();
	return lc=='-'?-s:s;
}
void write(register ll x)
{
	if (x<0)
	{
		putchar('-');
		x=-x;
	}
	if (x<10) putchar(x+'0');
	else
	{
		write(x/10);
		putchar(x%10+'0');
	}
}
inline void print(const register ll x,const register char c='\n')
{
	write(x);
	putchar(c);
}
ll gcd(ll x,ll y)
{
	return y==0?x:gcd(y,x%y);
}
ll get(ll a,ll b,ll x,ll y)
{
	if (x==1) return (y-1)/a;
		 else return (y-1)/b;
}
 
int main()
{
	ll n=read(),m=read(),q=read(),g=gcd(n,m),a=n/g,b=m/g;
	while (q--)
	{
		ll x1=read(),y1=read(),x2=read(),y2=read(),ans1=get(a,b,x1,y1),ans2=get(a,b,x2,y2);
		if (ans1==ans2) puts("Yes");
				   else puts("No");
	}
 
	return 0;
}
```

---

## 作者：Kizuna_AI (赞：3)

这道题要用到gcd，gcd的倍数是里外两层都是墙的情况了

看着各位大佬都在手写gcd，然而我比赛的时候忘了gcd该怎么手写了怎么办？  
这时候就只能`algorithm`库中的__gcd来救你了。

Note: __gcd兹磁long long，所以可以直接使用

代码：
```
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,m,q;
ll gcdnm;
int main() {
	scanf("%I64d%I64d%I64d",&n,&m,&q);
	long long sx,sy,ex,ey;
	gcdnm=__gcd(n,m);
	n/=gcdnm;m/=gcdnm;
	for(int i=1;i<=q;i++) {
		scanf("%I64d%I64d%I64d%I64d",&sx,&sy,&ex,&ey);
		if(sx==1 && ex==1) {  //都是里层
			if((sy-1)/n==(ey-1)/n) printf("YES\n"); //-1的原因是方便int的计算，int自动向零取整
			else printf("NO\n");
		}
		else if(sx==1 && ex==2) { //一个里层，一个外层
			if((sy-1)/n==(ey-1)/m) printf("YES\n");
			else printf("NO\n");
		}
		else if(sx==2 && ex==1) { //一个外层，一个里层
			if((sy-1)/m==(ey-1)/n) printf("YES\n");
			else printf("NO\n");
		}
		else if(sx==2 && ex==2) { //都是外层
			if((sy-1)/m==(ey-1)/m) printf("YES\n");
			else printf("NO\n");
		}
	}
	return 0;
}
```
Note: NOIP不能使用下标开头的函数，~~但是考试的时候你可以去编译器里面找到__gcd是怎么写的。~~

---

## 作者：lygmh (赞：2)

update 1：代码有点丑，更改了一下。
## 做题经历
我太蒟了，纯属瞎搞。
## 思路分析
这是一道数学题；

用gcd求出有几个联通的区间，在求出起点和终点所在的区间。
判断起点和终点是否在同一个区间。
## AC代码
```cpp
#include<cstdio>
#include<iostream>
#define LL long long
using namespace std;
LL m,n,q;
LL gcd(LL a,LL b) {
	LL r;
	while(b) {r=a%b;a=b;b=r;}
	return a;
}
int main() {
	scanf("%lld%lld%lld",&m,&n,&q);
	LL br=gcd(m,n);
	while(q--) {
		LL f1,f2,t1,t2,q1,q2;
		scanf("%lld%lld%lld%lld",&f1,&f2,&t1,&t2);
		q1=(f1==1)? ((f2-1)/(m/br)):((f2-1)/(n/br));
		q2=(t1==1)? ((t2-1)/(m/br)):((t2-1)/(n/br));
		if(q1==q2)printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
```


---

## 作者：Social_Zhao (赞：1)

UPD：修正一个沙雕错误

$\color{grey}\mathtt{Specialist}$蒟蒻水题解

当时的想法：

> 看到要判断两点是否连通，有几种算法涌入了我的脑海：$dfs$、并查集......
> 
> 但是看到数据范围之后我绝望了。

来看一下体面上的这个图：

![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1200C/7fdeabfa2ad973f1b56c678ed3354417ac806e5e.png)

发现只有两堵墙将这些空间完全隔断了。

很容易发现，$2=gcd(4, 6)$

并且，内圈每个两个房间（$4\div 2$）就有一堵墙隔断，外圈每隔三个房间（$6\div 3$）就有一堵墙隔断.

把这个内外圈被隔断的周期分别设为$block\_in$和$block\_out$。

然后通过以下的式子就可以判断某个房间所在的连通块编号：

- 内圈$(1,x)$：$col_1=(x - 1) \div block\_in+1$
- 外圈$(2,x)$：$col_2=(x - 1) \div block\_out+1$

如果$col_1=col_2$，很明显这两个点就是联通的。

于是代码：（写的有一点乱，勿喷）

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

int get()
{
	int x = 0, f = 1; char c = getchar();
	while(!isdigit(c)) { if(c == '-') f = -1; c = getchar(); }
	while(isdigit(c)) { x = x * 10 + c - '0'; c = getchar(); }
	return x * f;
}

int gcd(int a, int b)
{
	if(a % b == 0) return b;
	else return gcd(b, a % b);
}

int block_in, block_out;
int cut_line;

int ask_in(int pos)
{
	return (pos - 1) / block_in + 1; //求内圈房间所在的连通块编号
}

int ask_out(int pos)
{
	return (pos - 1) / block_out + 1; //求外圈房间所在的连通块编号
}

signed main()
{
	int n = get(), m = get(), q = get();
	cut_line = gcd(n, m); //cut_line代表有几堵墙能将走廊隔断
	block_in = n / cut_line; //内圈隔断的周期为房间数/能隔断的墙数
	block_out = m / cut_line; //外圈隔断的周期为房间数/能隔断的墙数
	for(int i = 1; i <= q; i++) {
		int opt1 = get(), pos1 = get(), opt2 = get(), pos2 = get();
		int col_1, col_2;
		if(opt1 == 1) col_1 = ask_in(pos1);
		else col_1 = ask_out(pos1);
		if(opt2 == 1) col_2 = ask_in(pos2);
		else col_2 = ask_out(pos2);
		//printf("%lld %lld\n", col_1, col_2);
		if(col_1 == col_2) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}

```

---

## 作者：Abeeel51 (赞：0)

#### 题目大意
数学方法解题

看图即理解
![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1200C/7fdeabfa2ad973f1b56c678ed3354417ac806e5e.png)
内圆和外圆分别被 $n$ 和 $m$ 堵墙分成 $n$ 和 $m$ 块，每块都标上号（从 $12$ 点方向，$1,2,3...$ 以此类推，内圈 $x$ 为 $1$ ，外圈 $x$ 为 $2$ ），问块 $(sx,sy)$ 和块 $(ex,ey)$ 是否连通， $12$ 点钟方向一定有一堵贯穿内外圆的墙，如图 $(2,1)$ , $(1,1)$ , $(2,6)$ , $(1,4)$ 之间的点。
#### 题目分析
如果这一堵墙贯穿内外圈，则这堵墙的两边不会连通（仅有一堵除外）。这样贯穿内外圆的墙一定会在 $n$ 或 $\frac{m}{\gcd (n,m)}$ 的位置出现。这样就可以判断两个块是否连通了。
#### AC代码
详解在代码里
```cpp
//要开long long
#include <bits/stdc++.h>
using namespace std;
long long GCD(long long x,long long y){
    if(y==0){
    	return x;
    }else{
    	return GCD(y,x%y);
    }
}//最大公约数
int main(){
    long long n,m;
    scanf("%lld%lld",&n,&m);
    long long q;
    scanf("%lld",&q);
    long long GGG=GCD(n,m);
    long long NGCD=n/GGG;
    long long MGCD=m/GGG;
    while(q--){//多组数据
        long long a,b,c,d;
        scanf("%lld%lld%lld%lld",&a,&b,&c,&d);
        b-=1;d-=1;
        long long ans=0,ans2=0;
        if(a==1){
            ans=b/NGCD;
        }else{
            ans=b/MGCD;
        }
        if(c==1){
            ans2=d/NGCD;
        }else{
            ans2=d/MGCD;
        }//判断
        if(ans==ans2){
            printf("YES\n");
        }else{
            printf("NO\n");
        }//输出
    }
    return 0;
}
```


---

## 作者：d3NtMDAw (赞：0)

一道好数论题。我一开始想成计算几何或者搜索。后来才想到可以数学方法解决。 
![pic]( https://cdn.luogu.com.cn/upload/pic/71439.png )
  
观察这个图,假设,走廊的长度为$1$。那么墙的位置在$(1,1/n)$,$(1,2/n)$...$(1,1)$。     
不妨定义外圈和里圈都有墙为**双重墙**，显然双重墙是过不去的。如果在$(1,x)$有一堵双重墙,则对于$y<x$,$x<z$,我们不能从y移动到Z。       

记$g=\gcd(n,m)$,容易发现双重墙出现在$(1,1/g),(1,2/g)$等位置。所以我们可以把走廊分为$g$组，例如**扇形**(注意这里不是墙，所以记录方式不一样)$(1,1),(1,2)...(1,n/g)$是第一组的。而$(1,n/g+1)则是另外一组$，两组被双重墙挡住无法互相抵达。   
同样的外圈也可分成$g$组,$(1,1)...(1,m/g)$也是第一组。
所以我们可以针对每一组询问,确认$(sx,sy)$和$(ex,ey)$是否属于同一组,如果是，输出$YES$。否则输出$NO$   
复杂度$o(\log(max(n,m)+q)$   
坑点提醒：$m,n\le10^{18}$,要使用$longlong$

---

## 作者：Doveqise (赞：0)

这道题 一道数论题(小学奥数题)  
我们通过看图 发现在12点方向以外，gcd(n,m)的整数倍地方有大墙  
所以我们可以把内圈分成n/gcd(n,m)块，外圈分成m/gcd(n,m)块  
然后判断两点是否在同一块内  
暴力判断代码长的雅痞  
旁边巨佬疯狂嘲讽我代码长  
最后告诉我只要-1就可以  
emmm  
awcsl  
下见代码(然鹅还是比旁边神仙长)   
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define int long long
ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}
signed main()
{
	int n,m,q;
	scanf("%lld%lld%lld",&n,&m,&q);
	int g=gcd(n,m);
	for(int i=1,sx,sy,ex,ey;i<=q;i++)
	{
		scanf("%lld%lld%lld%lld",&sx,&sy,&ex,&ey);
		if(sx==1) sy=(sy-1)/(n/g);
		else sy=(sy-1)/(m/g);
		if(ex==1) ey=(ey-1)/(n/g);
		else ey=(ey-1)/(m/g);
		puts(sy==ey?"YES":"NO");
	}
}
```


---

## 作者：破壁人五号 (赞：0)

~~从样例可以猜到~~所有房间被分成了 $\gcd(m,n)$ 个互不连通的块。

胡乱证明：

假如两部分被完全隔开，一定是因为内外两面墙在同一处，即：

$\frac{a}{m}=\frac{b}{n}(0\leq a<m,0\leq b<n)$

假设其约分后是 $\frac{x}{y}(gcd(x,y)=1,0\leq x<y)$，显然 $y|m,y|n$，即 $y|\gcd(m,n)$，这样的分数个数为：$\sum \limits_{d|\gcd(m,n)}\phi(d)=\gcd(m,n)$

所以内圈每 $n/\gcd(m,n)$ 一个块，外圈每 $m/\gcd(m,n)$ 一个块。

每次询问简单计算出两个询问的房间在哪个块，相同即可以连通。

记得开 `long long`

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll getint(){
    ll ans=0,f=1;
    char c=getchar();
    while(c>'9'||c<'0'){
        if(c=='-')f=-1;
        c=getchar();
	}
    while(c>='0'&&c<='9'){
        ans=ans*10+c-'0';
        c=getchar();
    }
    return ans*f;
}
ll gcd(ll a,ll b){
	return b?gcd(b,a%b):a;
}
int main(){
	ll n=getint(),m=getint(),q=getint();
	ll g=gcd(m,n),gn=n/g,gm=m/g;
	while(q--){
		ll sx=getint(),sy=getint()-1,ex=getint(),ey=getint()-1;
		sy=(sx==1?sy/gn:sy/gm);
		ey=(ex==1?ey/gn:ey/gm);
		puts(sy==ey?"YES":"NO");
	}
	return 0;
}
```

---

## 作者：弦巻こころ (赞：0)

~~万恶的谷歌翻译把10的18次方翻译成10，害我又挂了50分~~

思路：由于每隔一个点就会有一个板子，我们可以得出 如果有两个板子重合，这两个板子左右的数不可到达。

### 那么什么时候板子会重合呢？

很简单，由于这是一个圆，只要圆心角相等，则这两个板子重合，即板子间距离为 n/gcd(n,m) 或m/gcd(n,m),共有 gcd(n,m)个板子。

我们只需要知道给定的两个点，它们是否在两个板子之间就行了。

考试代码，码风巨长巨丑，见谅qaq。（最开始以为外围圆是反着的，导致加了巨多特判）

```cpp
#include<bits/stdc++.h>
using namespace std;
long long gcd(long long a,long long b)
{
	return b==0?a:gcd(b,a%b);
}
long long n,m,q;
long long l,a1,a2;
long long l1,l3,l2,l4;//l1，l3为x1,x2 l2，l4为y1，y2
long long cnt1,cnt2;
int main()
{
	scanf("%I64d%I64d%I64d",&n,&m,&q);
	l=gcd(n,m);
	a1=n/l,a2=m/l;
 
	for(long long i=1;i<=q;i++)
	{
		cnt1=0,cnt2=0;
		scanf("%I64d%I64d%I64d%I64d",&l1,&l3,&l2,&l4);
		if(l1==l2)//如果两个在同一个圆内 
		{
			if(l1==1)//如果在内围圆中
			{
				if(l4%a1!=0){cnt2=1;}//我ceil写挂了TAT
				if(l3%a1!=0){cnt1=1;}
				l3/=a1;
				l4/=a1;
				l3+=cnt1;l4+=cnt2;//这里是因为我ceil写挂了。。。
				if(l3==l4)//如果在同一个区域
				{
					printf("YES\n");
					continue;
				}
			}
			else//如果在外围圆中
			{
				if(l4%a2!=0){cnt2=1;}
				if(l3%a2!=0){cnt1=1;}
				l3/=a2;l4/=a2;
				l3+=cnt1;l4+=cnt2;
				if(l3==l4)
				{
					printf("YES\n");
					continue;
				}
			}
			printf("NO\n");
		}
		else//如果在不同的圆中 （其实所有特判都没太大区别）
		{
			if(l1==2){swap(l1,l2);swap(l3,l4);}
			if(l4%a2!=0){cnt2=1;}
			if(l3%a1!=0){cnt1=1;}
			l3/=a1;l4/=a2;
			l3+=cnt1;l4+=cnt2;
			if(l3==l4)
			{
				printf("YES\n");
				continue;
			}
			printf("NO\n");
		}
	}
}
```

---

## 作者：Sakii (赞：0)

### 解析：
~~我第一反应是并查集做的来着~~

然后发现是一道小学奥数题

很明显能完全隔开两边的墙的个数为$GCD(n,m)$

所以只要知道$n,m$的$gcd$就能知道一共有多少堵墙能完全隔开两边,然后分别用$n,m$除以$gcd$就能知道每一块里面的点的个数.

对于每次询问处理出两个点分别在哪一部分即可.

注意特判，当询问的$s_y$或$e_y$是$n/gcd$或$m/gcd$的倍数时，所求出来的所在块的编号要减一.（~~别的~~~~应该没有什么要注意了~~

------------
### 代码：



```cpp
//≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈
//  Date : Plz press Shift + Ctrl + . in proper Sublime
//  Author : Sakii
//  website : zcqiever.tk
//  I'm so vegetable , QAQ..
//≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈

#include<bits/stdc++.h>
#define re register
#define il inline
#define lowbit(x) x&(-x)

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

template <class T> inline void read(T &s){
    s = 0; re char ch = getchar(); re int w = 0;
    while(!isdigit(ch)) w |= ch == '-', ch = getchar();
    while(isdigit(ch)) s = (s << 1) + (s << 3) + (ch ^ 48), ch = getchar();
    if(w) s = -s;
}

namespace Sakii {
    il ll gcd(ll a, ll b){return b == 0 ? a : gcd(b, a % b);}
    ll n,m,sx,sy,ex,ey;
    int q;

    il void main() {
        read(n); read(m);
        ll g = gcd(m,n);
        n /= g, m /= g;
        read(q);
        while(q--) {
            read(sx); read(sy);
            read(ex); read(ey);
            if(sx==1) {if(sy%n==0) sy--; sy = sy / n;}
            else if(sx==2) {if(sy%m==0) sy--; sy = sy / m;}
            if(ex==1) {if(ey%n==0) ey--; ey = ey / n;}
            else if(ex==2) {if(ey%m==0) ey--; ey = ey / m;}
            if(sy==ey) printf("YES\n");
            else printf("NO\n");
        }
        return;
    }
}

int main(){
    Sakii::main();
    return 0;
}


```


---

