# New Year Tree Decorations

## 题目描述

Due to atheistic Soviet past, Christmas wasn't officially celebrated in Russia for most of the twentieth century. As a result, the Russian traditions for Christmas and New Year mixed into one event celebrated on the New Year but including the tree, a Santa-like 'Grandfather Frost', presents and huge family reunions and dinner parties all over the country. Bying a Tree at the New Year and installing it in the house is a tradition. Usually the whole family decorates the tree on the New Year Eve. We hope that Codeforces is a big and loving family, so in this problem we are going to decorate a tree as well.

So, our decoration consists of $ n $ pieces, each piece is a piece of colored paper, its border is a closed polyline of a special shape. The pieces go one by one as is shown on the picture. The $ i $ -th piece is a polyline that goes through points: $ (0,0) $ , $ (0,y_{0}) $ , $ (1,y_{1}) $ , $ (2,y_{2}) $ , ..., $ (k,y_{k}) $ , $ (k,0) $ . The width of each piece equals $ k $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF379E/69b6f4a3736ea64c0c3cc034ee4bc0d7ac63d241.png)The figure to the left shows the decoration, the figure to the right shows the individual pieces it consists of.The piece number 1 (shown red on the figure) is the outer piece (we see it completely), piece number 2 (shown yellow) follows it (we don't see it completely as it is partially closed by the first piece) and so on. The programmers are quite curious guys, so the moment we hung a decoration on the New Year tree we started to wonder: what area of each piece can people see?

## 样例 #1

### 输入

```
2 2
2 1 2
1 2 1
```

### 输出

```
3.000000000000
0.500000000000
```

## 样例 #2

### 输入

```
1 1
1 1
```

### 输出

```
1.000000000000
```

## 样例 #3

### 输入

```
4 1
2 7
7 2
5 5
6 4
```

### 输出

```
4.500000000000
1.250000000000
0.050000000000
0.016666666667
```

# 题解

## 作者：shiroi (赞：1)


## Description

给定二维平面坐标系上的 $n$ 个互相覆盖的多边形，求每个多边形露出的面积。





## Solution

一道思路非常神奇的几何题目。

此题的计算几何做法过于难写。观察到题目中对精度要求非常小，可以考虑类似求积分的方式解决问题。

类似求积分的方式，我们可以将所有的多边形拆分成宽度很小的段，对于每一段多边形可以用矩形近似求出面积。每次记录下先前覆盖在相同位置的最长的矩形，由于每段长度固定，求出现有矩形长度与先前的差值和即为多边形露出的面积。

这种做法对精度有一定要求，因此需要使用`long double` ，并且将横坐标映射进更大的范围内来卡精度。输出答案时建议使用 `cout` ，此时使用 `printf` 精度可能会出锅。

```cpp
#include <bits/stdc++.h>
using namespace std;

inline int read()
{
    int x=0,f=1,c=getchar();
    while(c<48) c=='-'&&(f=-1),c=getchar();
    while(c>47) x=x*10+c-'0',c=getchar();
    return x*f;
}

typedef long double ld;
const int MAXN = 1000005;
ld val[MAXN],ans,slp,cur;
int n,k,lim;

int main(int argc, char const *argv[])
{
    n=read(); k=read(); lim=1e6/k;
    int x,y;
    for(int t=1; t<=n; ++t)
    {
        x=read(); ans=0;
        for(int i=0; i<k; ++i)
        {
            y=read(); slp=(ld)(y-x)/lim;
            for(int j=0; j<=lim; ++j)
            {
                cur=(ld)x+slp*j;
                if(cur>val[i*lim+j])
                    ans+=cur-val[i*lim+j],val[i*lim+j]=cur;
            }
            x=y;
        }
        cout<<ans/lim<<endl;
    }
    return 0;
}
```



---

## 作者：Leap_Frog (赞：0)

### P.S.
来个比较正常的题解

### Description.
略

### Solution.
贡献拆开，计算每段 $\forall i\in[1,n],[i-1,i]$ 的贡献。  
脑补一下每一时刻 $[i-1,i]$ 中图形构成了什么形状。  
肯定是一个下凸壳下面的面积。  
所以我们每次求一个下凸壳，然后差分就是多出来的面积。  
求下凸壳的话可以参考 [这题](https://www.luogu.com.cn/problem/P3194)，就直接算两两交点即可。  
注意这题是求区间的下凸壳，所以需要加一点特判。  

如果用 `set` 等动态维护凸包，复杂度应该能做到 $O(nk\log n)$。  
$k$ 是枚举 $[i-1,i]$ 的 $i$，$n$ 是从上往下每次插入一条线。  

但是笔者很懒，就写了个 $O(n^2k)$，就是每次暴力重新求一遍下凸壳。  

### Coding.
```cpp
//是啊，你就是那只鬼了，所以被你碰到以后，就轮到我变成鬼了{{{
#include<bits/stdc++.h>
using namespace std;typedef long long ll;
template<typename T>inline void read(T &x)
{
	x=0;char c=getchar(),f=0;
	for(;c<48||c>57;c=getchar()) if(!(c^45)) f=1;
	for(;c>=48&&c<=57;c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	f?x=-x:x;
}
template<typename T,typename...L>inline void read(T &x,L&...l) {read(x),read(l...);}//}}}
typedef long double ld;const ld eps=1e-9;
const int N=305;int n,K,a[N][N],lt;
struct ${int a,b;}l[N];ld rs[N],cf[N],pos[N];
inline ld slop($ a,$ b) {return (b.a-a.a)*1.0/(b.a-b.b-a.a+a.b);}
inline char chk($ a,$ b,$ c)
{
	if(c.a>=b.a&&c.b>=b.b) return 1;
	ld s1=slop(a,b),s2=slop(b,c);if(s2>1+eps) return 0;
	if(s2<-eps||s1>=s2-eps) return 1;else return 0;
}
int main()
{
	read(K,n);for(int i=1;i<=K;i++) for(int j=0;j<=n;j++) read(a[i][j]);
	for(int q=1;q<=n;q++)
	{
		for(int p=1;p<=K;p++)
		{
			lt=p;for(int i=1;i<=p;i++) l[i]=($){a[i][q-1],a[i][q]};
			sort(l+1,l+lt+1,[]($ a,$ b){return a.b-a.a==b.b-b.a?a.a<b.a:a.b-a.a<b.b-b.a;});
			int tl=1;for(int i=2;i<=lt;i++) if(l[i].a-l[i].b==l[i-1].a-l[i-1].b) l[tl]=l[i];else l[++tl]=l[i];
			lt=tl,tl=0;for(int i=1;i<=lt;i++)
			{
				while(tl>1&&chk(l[tl-1],l[tl],l[i])) tl--;
				while(tl>0&&l[i].a>=l[tl].a&&l[i].b>=l[tl].b) tl--;
				if(!tl||l[i].b>l[tl].b) l[++tl]=l[i];
			}pos[0]=0,pos[tl]=1;ld &rs=cf[p];rs=0;
			for(int i=1;i<tl;i++) pos[i]=(l[i].a-l[i+1].a)*1.0/(l[i+1].b-l[i].b+l[i].a-l[i+1].a);
			for(int i=1;i<=tl;i++)
			{
				ld k1=pos[i-1],k2=pos[i];
				rs+=(k2-k1)*((2-k1-k2)*l[i].a+(k1+k2)*l[i].b)/2;
			}
		}
		for(int p=1;p<=K;p++) rs[p]+=cf[p]-cf[p-1];
	}
	for(int i=1;i<=K;i++) printf("%.10Lf\n",rs[i]);
	return 0;
}
```

---

