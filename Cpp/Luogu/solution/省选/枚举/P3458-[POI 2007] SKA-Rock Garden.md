# [POI 2007] SKA-Rock Garden

## 题目描述

**译自 POI 2007 Stage 2. Day 1「[Skalniak](https://szkopul.edu.pl/problemset/problem/s5ECsFKlMHti0g29uVkdKlQw/site/?key=statement)」**

Vicomte de Bajteaux 收藏了许多石头并准备把它们放到花园里。

花园是一个正方形，边长为 $1\ 000\ 000\ 000$。Vicomte de Bajteaux 让他的仆人为他用石头布置花园。但他忘记告诉仆人坐标的顺序，以至于一些点的坐标以 $(x,y)$ 的形式给出，一些点的坐标以 $(y,x)$ 的形式给出，并且石头已经按这样的顺序放好了。

为了保护石头，Vicomte de Bajteaux 按照实际的坐标规划了一排栅栏来围住这些石头，使得栅栏的总长最小。为了美观，栅栏必须是平行于坐标轴的矩形。为了让错误不那么明显，你需要帮助仆人选择一部分石头并将它们从 $(x,y)$ 移动到 $(y,x)$，在最小化栅栏的长度的基础上最小化需要移动的石头的总重。

## 样例 #1

### 输入

```
5
2 3 400
1 4 100
2 2 655
3 4 100
5 3 277```

### 输出

```
10 200
01010```

# 题解

## 作者：小塘空明 (赞：8)

~~既然没有题解我就自己写一篇吧~~

参照了claris的题解。

这道题一拿到时，看了下n，1000000，下意识去分析单调栈，但怒调半小时样例都没过（太弱了），开始推结论。

很明显为了让周长更短，矩形应该集中在更小的区域内。

经过一波画图和推导后，我们发现最优情况一定是所有石头翻到直线y=x同侧。

本人并不会很严谨的证明，但在这给出自己的分析思路：分析每个点带来的周长变化，按照矩形沿x轴方向长还是y轴方向长分两类讨论，方便起见我们假设这个矩形在y=x下方，翻过去后改动的周长就是当前点沿y轴方向到直线距离和翻过去的点沿x轴方向到直线的距离（距离不算上矩阵内的长度）之差，我们发现这肯定会让答案变大。

如果有大佬发现错误或有严谨证明，希望在评论区指出。

因为矩形的四个点可以同时被点的x值和y值更新，所以分四种情况讨论。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<string>
#include<cstring>
#include<cmath>
#include<queue>
using namespace std;
typedef long long ll;
const ll N=1e6+10,inf=1e18;
ll n,m[N],x[N],y[N],v[N],fin[N],lx=inf,rx,ly=inf,ry,now,ans=inf,i,j;
inline ll read(){
	ll x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
inline void calc(ll lx,ll rx,ll ly,ll ry){
	for(now=0,i=1;i<=n;i++){
		if(lx<=x[i]&&x[i]<=rx&&ly<=y[i]&&ry>=y[i]){v[i]=0;continue;}
		if(lx<=y[i]&&y[i]<=rx&&ly<=x[i]&&ry>=x[i]){v[i]=1;now+=m[i];}
		else return;
	}
	if(now<ans){ans=now;for(i=1;i<=n;i++)fin[i]=v[i];}
}
int main(){
	n=read();
	for(i=1;i<=n;i++){
		x[i]=read(),y[i]=read(),m[i]=read();
		if(x[i]<=y[i]){
			lx=min(lx,x[i]);rx=max(rx,x[i]);
			ly=min(ly,y[i]);ry=max(ry,y[i]);
		}
		else{
			lx=min(lx,y[i]);rx=max(rx,y[i]);
			ly=min(ly,x[i]);ry=max(ry,x[i]);
		}
	}
	printf("%lld ",2*(rx+ry-lx-ly));
	calc(lx,rx,ly,ry);calc(lx,ry,ly,rx);calc(ly,rx,lx,ry);calc(ly,ry,lx,rx);
	printf("%lld\n",ans);
	for(i=1;i<=n;i++)printf("%lld",fin[i]);
	return 0;
}
```

---

## 作者：Asuka二号机 (赞：6)

做法看隔壁 我来证结论（撸袖子）

从小学奥数我们可以知道这个轮廓线必然是个正好能包括所有点的矩形，而挪动一个点可以几何地看做对直线y=x作对称。

结论：把所有点翻到y=x一边去是最优的

定义最左点：决定矩形左边界的点，即min(xi)（1<=i<=n）其他类似。

### **第一种情况长这个样子**
![](https://cdn.luogu.com.cn/upload/pic/69176.png)

这个很显然，红色边界那边翻折一波。

无论你怎么瞎翻，各个边界都不会变大，周长也不会变大。甚至最上点和最左点可能会改变，决策就比较优。

### **第二种情况**
上图：
![](https://cdn.luogu.com.cn/upload/pic/69175.png)

浅灰色部分是原矩阵，深灰色部分是选择折叠的部分，不妨假设左下角到y=x的距离<右下角到y=x的距离（如果不是的话就下面的部分翻上去 都是一样的）所以显然红色框内就是新的矩阵的**最差**情况。

显然最左点必然改变（好事情），最上点可能改变（变了就赚 不变不亏）最下点可能改变（变了可能会亏）最右点必然不变

——最差情况，意思就是原来的最左点现在折下去变成了最下点，且最上点没有改变。

但是即使是这样的情况，也可以看出来周长没有发生改变，具体的已经标出来了，同一颜色圈圈里的边互相对应。

那么这样改变之后还有一定的可能性最上点下移，这样就比较优。

------------

那就证明了这么搞不会更劣，那为什么这么搞就是最优的呢？

答：实际上是这样的，可以先考虑单个点的决策——与这个单点在直线同一侧的其他点都可以不看，这和上面的过程是一样的。那么这个单点可能会影响答案，可能不会，但是这样改变后必然不会更不优。然后问题就变成了下一个单点，显然这个单点也可以这么操作。这样下去，把同侧的所有点都翻过来就成了必然的最优决策。

但是电脑不长眼睛，解决 _假设左下角到y=x的距离<右下角到y=x的距离_ 本来是可以直接算的，但是考虑到重量需要处理，所以翻上去翻下去跑两次即可。

在搞重量之前扫一遍，那些挪不挪都无所谓的点，就不用挪了，放回去就行。

---

## 作者：Hua_Tian (赞：1)

### 题目分析
此题分为 $2$ 种情况，一种是 $x$ 轴方向长；一种是是 $y$ 轴方向长。而又因为矩形的四个点可以同时被点的 $x$ 值和 $y$ 值更新，所以每种情况又要分 $2$ 个可能去算。
### 整体思路
先说结论：把所有点翻到 $x=y$ 一边去是最优的，具体论证可看[隔壁](https://www.luogu.com.cn/article/vv8h5fnz)。

此题在算法上没有难度，输入输出用一般的 ```cin``` 和 ```cout``` 即可过关（~~看了看一楼好像写了个什么快速输入~~），但需要进行深入思考。依靠题意可知进行优化（在几何上可以看成翻页）后被改动的周长就是优化前的点沿 $y$ 方向来到直线的距离和沿 $x$ 方向到直线的距离差，到了这里，连抄代码的都应该能发现，如果 $x=y$，那么被改动的周长就为 $0$！那么，即可证明把所有点翻到 $x=y$ 一边去是最优的。

知道了结论，再依靠结论模拟即可，这一步就简单到不能再简单了。
### 代码区
核心代码：


```cpp
void f(int lf,int rf,int df,int uf){
    long long sum=0;
    for(int i=1;i<=n;i++){
        if(a[i].x>=lf&&a[i].x<=rf&&a[i].y>=df&&a[i].y<=uf){//分类1
        	a[i].v=0;//记录
        	continue;
		}
        if(a[i].y>=lf&&a[i].y<=rf&&a[i].x>=df&&a[i].x<=uf){//分类2
        	a[i].v=1;//记录
        	sum+=a[i].w;
		}
        else return;
    }
    if(sum<ans){
    	ans=sum;
    	for(int i=1;i<=n;i++)out[i]=a[i].v;
	}
}
```


第一种情况（$x \le y$）：


```cpp
l=min(l,a[i].x),r=max(r,a[i].x);
d=min(d,a[i].y),u=max(u,a[i].y);
```
第二种情况（$x > y$）：


```cpp
l=min(l,a[i].y),r=max(r,a[i].y);
d=min(d,a[i].x),u=max(u,a[i].x);
```


所以，您听懂了吗？只需要分情况讨论，相信聪明的读者一定能完成 AC 代码！

接下来就是美丽的完整代码啦，希望各位别直接复制粘贴，~~至少也要听懂了再复制（小声~~。
```cpp
#include<bits/stdc++.h>
using namespace std;
struct point{//结构体启动！！！
    int x,y,w,v;
};
point a[1000001];
int n,l=INT_MAX,r,u,d=INT_MAX,out[1000010];
long long ans=20000000001;
void f(int lf,int rf,int df,int uf){
    long long sum=0;
    for(int i=1;i<=n;i++){
        if(a[i].x>=lf&&a[i].x<=rf&&a[i].y>=df&&a[i].y<=uf){//分类1
        	a[i].v=0;//记录
        	continue;
		}
        if(a[i].y>=lf&&a[i].y<=rf&&a[i].x>=df&&a[i].x<=uf){//分类2
        	a[i].v=1;//记录
        	sum+=a[i].w;
		}
        else return;
    }
    if(sum<ans){
    	ans=sum;
    	for(int i=1;i<=n;i++)out[i]=a[i].v;
	}
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        scanf("%d %d %d",&a[i].x,&a[i].y,&a[i].w);
        if(a[i].x<=a[i].y){//情况1
            l=min(l,a[i].x),r=max(r,a[i].x);
            d=min(d,a[i].y),u=max(u,a[i].y);
        }
        else{//情况2
            l=min(l,a[i].y),r=max(r,a[i].y);
            d=min(d,a[i].x),u=max(u,a[i].x);
        }
    }
    cout<<(r-l+u-d)*(long long)(2)<<" ";
    f(l,r,d,u);
    f(d,u,l,r);
    f(l,u,d,r);
    f(d,r,l,u);
    cout<<ans<<endl;
    for(int i=1;i<=n;i++)cout<<out[i];
    return 0;
}
```

---

