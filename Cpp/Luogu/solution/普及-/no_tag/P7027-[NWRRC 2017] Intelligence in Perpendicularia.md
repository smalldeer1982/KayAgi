# [NWRRC 2017] Intelligence in Perpendicularia

## 题目描述

给你一个数 $ n $ ，再给你 $ n $ 个点（$ x_i , y_i $），这 $ n $ 个点依次连成一个多边形。（保证多边形的每条边都与坐标轴平行或垂直，点不重合，点不在边上，边无相交）

求有多长的边是安全的？

（一个单位长度的边是安全的当且仅当它向外平移后能与其余边相遇，结合一下图看看）

## 样例 #1

### 输入

```
10
1 1
6 1
6 4
3 4
3 3
5 3
5 2
2 2
2 3
1 3
```

### 输出

```
6
```

# 题解

## 作者：Red_river (赞：4)

# 题目大意

首先这道题，就是变相的给你一个图形，然后让你求“安全”的边是有多长。（一个单位长度的边是安全的当且仅当它向外平移后能与其余边相遇）。

### “安全”的定义可以转化成：不被算在最外层的边的线，就是“安全”的线。
所以我们就可以用总周长减去不“安全”的长就行了。

时间复杂度分析：$ O ( N ) $。

# code
```cpp
#include<bits/stdc++.h>
#define INF 1e6
#define M 1005
using namespace std;
int n,m,k,jk,x2,y2,ans,sum,x[M],y[M];//y1会编译错误 
int u=-INF,d=INF,l=INF,r=-INF;
void solve(int x,int y)
{
	u=max(u,y);r=max(r,x);
	d=min(d,y);l=min(l,x);
	sum+=abs(x-x2)+abs(y-y2);
	x2=x;y2=y;
}
int main()
{
	scanf("%d%d%d",&n,&x[1],&y[1]);x2=x[1],y2=y[1];
	for(register int i=2;i<=n;++i) scanf("%d%d",&x[i],&y[i]);
	//输入部分 为了后面统一处理： 
	for(register int i=2;i<=n;++i) solve(x[i],y[i]);//处理  
	sum+=abs(x[1]-x2)+abs(y[1]-y2);//首尾相连 
	printf("%d",sum-(r-l+u-d)*2);//输出 
	return 0;}
```

---

## 作者：David_yang (赞：3)

[传送门](https://www.luogu.com.cn/problem/P7027)

第三篇题解，还是：如有不妥请~~忽视~~指出。

~~看到题解通道还没关闭，赶快来一波吧。~~

## 题目大意：

给定一个任意两边不平行就垂直的多边形，求一共有多长的边是“安全”的？

## 算法：

好像就是周长的计算......

## 解析：

乍一看，“一个单位长度的边是安全的当且仅当它向外平移后能与其余边相遇”是什么意思？“结合一下图看看”，图呢？图片在哪呢？直到看了 @xiangqizhen2011 画的图我才知道是这个样子。下面我把他的这张图摆出来：

![](https://cdn.luogu.com.cn/upload/image_hosting/3v02j83k.png?x-oss-process=image/resize,m_lfit,h_340,w_455)

可以看出，画黑线的是要补齐的部分，画红线的才是我们要求的部分。

那画红线的部分怎么求呢？是不是可以用总周长减去黑色部分周长？而黑色部分周长是不是就是大长方形的周长？于是这道题就迎刃而解了。

下面是带注释版代码，希望你能理解。

## Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,y,xx,yy,xxx,yyy,sum,l,r,u,d;	//开了万能头文件后最好不要用x1,y1,x2,y2这些变量名，避免CE。
int main()
{
	scanf("%d%d%d",&n,&x,&y);
	l=r=xxx=x;
	u=d=yyy=y;
	for(int i=1;i<n;i++)
	{
		scanf("%d%d",&xx,&yy);
		l=min(l,xx);
		r=max(r,xx);
		u=min(u,yy);
		d=max(d,yy);					//取大长方形的边界。
		sum+=abs(x-xx)+abs(y-yy);		//求总周长。
		x=xx;
		y=yy;
	}
	sum+=abs(x-xxx)+abs(y-yyy);			//注意最后一个点和第一个点只间也有一条边。
	printf("%d",sum-2*((r-l)+(d-u)));	//总周长-黑色部分周长。
	return 0;
}
```

注：代码已AC过，请放心食用。

最后，浏览过看过也要赞过！

---

## 作者：saixingzhe (赞：3)

# 分析
**安全的边指在四周被其它边挡住的边。**

有了清晰的题意，代码就好写了，我们运用小学的知识，知道边可以平移使其周长不变但形状变为矩形。所以我们求出周长和上下左右四个边界，最后用周长减去即可。

对于周长的头尾处理，写变量存好即可。

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,c,x,y,x2,y2,x3,y3,u=-1e6,d=1e6,l=1e6,r=-1e6;//c表示周长
int main(){
	cin>>n;
	cin>>x2>>y2;
	x3=x2,y3=y2;
	for(int i=2;i<=n;i++){
		cin>>x>>y;
		u=max(u,y);
		d=min(d,y);
		l=min(l,x);
		r=max(r,x);
		c+=abs(x-x2)+abs(y-y2);
		x2=x;y2=y;
	}
	c+=abs(x3-x2)+abs(y3-y2);
	cout<<c-(r-l+u-d)*2;
	return 0;
}
```

---

## 作者：Chillturtle (赞：1)

# 题意

给你很多个点的坐标，将这些点依次连接起来。问有多少线段是安全的，输出这些线段的长度之和。

- 安全的定义：一个单位长度的边是安全的当且仅当它向外平移后能与其余边相遇，其实**就是被其他边包住的边**。

# 思路

我们先来分析一下样例，画成图就是以下这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/m9lcpbux.png)

又因为安全的边即为被包住的边，所以就又有了下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/me6gsif7.png)

所以被涂成绿色的边既是安全边。那么怎么计算长度呢？好的，我们在这个 $n$ 边形中可以对某些边进行平移，具体操作如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/jj7dcno5.png)

从图中我们将两条黑色的边向图中这个矩形的边上平移，那么我们就可以得出结论了。**图中绿色部分的周长就等于所有线段的总长减去外面这个矩形的周长**。

综上，我们在输入的时候顺便记录这个举行的左上角与右下角并累加总长度即可。注意，**在第一个点与最后一个点之间还有一条边**，所以我们需要特别记录第一个点的位置来确定最后一条边。

# AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int main(){
	cin>>n;
	int firstx,firsty;
	cin>>firstx>>firsty;
	int startx=firstx,starty=firsty;
	int s=INT_MAX,x=-1,z=INT_MAX,y=-1;
	int cd=0;
	int x1,y1;
	for(int i=2;i<=n;i++){
		cin>>x1>>y1;
		if(x1==firstx){
			cd+=(abs(firsty-y1));
			firsty=y1;
		}else if(y1==firsty){
			cd+=(abs(firstx-x1));
			firstx=x1;
		}
		s=min(s,y1);
		x=max(x,y1);
		z=min(z,x1);
		y=max(y,x1);
	}
	cd+=(abs(firsty-starty)+abs(firstx-startx));
//	cout<<cd<<" "<<s<<" "<<x<<" "<<z<<" "<<y<<endl;
	cout<<cd-(2*(x-s)+2*(y-z))<<endl;
return 0;
}
```

---

## 作者：Danny_chan (赞：1)

其实题目就是要求出图形**里面**的边的长度总和，就相当于周长减去外面的边。

正确代码：

```
#include<iostream>
using namespace std;
int main() {
	int n,zhouchang=0,x,y,x1,y1,l=1e9,r=-1e9,u=-1e9,d=1e9;
	cin>>n;
	cin>>x1>>y1;
	int x3=x1,y3=y1;
	for(int i=2; i<=n; i++) {
		cin>>x>>y;
		r=max(r,y); u=max(u,x); l=min(l,y); d=min(d,x);//取最大值
		zhouchang+=abs(x-x1)+abs(y-y1);// 周长+计算出的长度
		x1=x;//更替
		y1=y;
	}
	zhouchang+=abs(x3-x1)+abs(y3-y1);//加上第一个点的距离
	cout<<zhouchang-(r-l+u-d)*2;//减去不符合的
	return 0;
}
```

---

## 作者：L_sdcs (赞：1)

### 题目大意

给你一个多边形，保证每条边都与坐标轴平行或垂直，求有多长的边是相对的（~~雾~~

### 大致思路

第一眼看上去，暴力即可，把每条边都移到坐标轴上计数。

只要大于$2$。就说明对$ans$有贡献，累加即可。

于是以下代码诞生了：

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[2000006],b[2000006];
int main()
{
	int n,ans=0;
	cin>>n;
	int xx,yy;
	cin>>xx>>yy;
	int xxx=xx,yyy=yy;//记录，最后一个点要用
	for(int i=2;i<=n;i++)
	{
		int x,y;
		cin>>x>>y;
		if(x==xx)//判断与x轴平行还是垂直
			for(int j=min(y,yy)+1e6;j<max(y,yy)+1e6;j++)//为什么要加1e6？别问，问就是有负数。
				if(b[j]==2)
					ans++;
				else
					b[j]++;//累加
		else
			for(int j=min(x,xx)+1e6;j<max(xx,x)+1e6;j++)
				if(a[j]==2)
					ans++;
				else
					a[j]++;
		xx=x;
		yy=y;
	}
	if(xxx==xx)
		for(int j=min(yyy,yy)+1e6;j<max(yyy,yy)+1e6;j++)
			if(b[j]==2)
				ans++;
			else
				b[j]++;
	else
		for(int j=min(xxx,xx)+1e6;j<max(xxx,xx)+1e6;j++)
			if(a[j]==2)
				ans++;
			else
				a[j]++;
    //最后一条边额外计算。
	cout<<ans<<endl;
	return 0;
}
  
```

做完之后发现我做法假了，如果数据够强的话，复杂度可到$2e9$。

但还是过了。

~~所以说，数据肯定不是lxl出的。~~

所以我决定打正解。

~~其实如果我提交的翻译过了的话，那就是我的锅。~~

原来的题意定义的安全距离是从外面看，看不见的边。

这就十分好想。~~但我在最开始的时候脑袋一抽，就翻译成···。~~

但是问题不大，我们继续来分析。

显然的，外面的可视部分可以平移成一个矩形，矩形范围为它的上下左右界。

于是我们把它的周长存下，减去矩形周长即可。

### 代码如下

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n,s=0,xx,yy;
	cin>>n;
	int u=-1e7,d=1e7,l=1e7,r=-1e7;
	cin>>xx>>yy;
	int xxx=xx,yyy=yy;//还是记录，最后要用。
	for(int i=2;i<=n;i++)
	{
		int x,y;
		cin>>x>>y;
		u=max(u,y);//上
		d=min(d,y);//下
		l=min(l,x);//左
		r=max(r,x);//右
		s+=abs(x-xx)+abs(y-yy);//周长记下
		xx=x;yy=y;
	}
	s+=abs(xxx-xx)+abs(yyy-yy);//最后一条边也要记。
	cout<<s-(r-l+u-d)*2;
	return 0;
}
```
~~所以我之前的暴力是在干什么~~

哦哦，有个错误

这道题的时限是$3s$，暴力还是能过的，最慢的点跑了1.43s。

---

## 作者：Flaw_Owl (赞：0)

# P7027 [NWRRC2017] Intelligence in Perpendicularia 题解

原题链接：[P7027 [NWRRC2017] Intelligence in Perpendicularia](https://www.luogu.com.cn/problem/P7027)

## 题目分析

题目中文翻译对安全边的诠释为：

> 一个单位长度的边是安全的当且仅当它向外平移后能与其余边相遇，结合一下图看看。

如果无法理解，也可以参见英文原文的直译：它指的是**从这个图形的四个方向看**向这个图形的**所有看不见的边**。如果我们将所有**能看得见**的边都画出来，我们会发现它的长度刚好就是**这个图形所在的最小矩形的周长**。也就是说，所有**看不见的边**的长度之和就是**边的总长**与**矩形的长度**之差。

当然，更准确的解释是被从图形的四个方向形成的投影包裹的边。而投影的长度当然就等同于这个矩形的周长。

理解这一点之后，我们只要维护出这个图形的四个点（即 $x$ 和 $y$ 坐标的最大最小值），就可以求出这个矩形的周长了。在读入数据的时候就可以顺便计算出所有边的长度。

值得注意的是，要记得这是个封闭图形，需要连上最后一个点和第一个点之间的边。

## 参考代码

```cpp
#include <iostream>
#include <cctype>
#define ll long long

using namespace std;

int read()
{
    int x = 0, f = 1;
    char ch = 0;
    while (!isdigit(ch))
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (isdigit(ch))
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

const int maxN = 1005;
const int INF = 0x3f3f3f3f; // 代表一个极大的值

int n;
int minX = INF, maxX = -INF, minY = INF, maxY = -INF;
ll tot; // 边的总长

pair<int, int> a[maxN];

int main()
{
    n = read();
    for (int i = 1; i <= n; i++)
    {
        a[i].first = read(), a[i].second = read();
        minX = min(minX, a[i].first);
        minY = min(minY, a[i].second);
        maxX = max(maxX, a[i].first);
        maxY = max(maxY, a[i].second);
        if (i >= 2)
            tot += abs((a[i].first - a[i - 1].first) + (a[i].second - a[i - 1].second));
    }
    tot += abs((a[n].first - a[1].first) + (a[n].second - a[1].second));
    printf("%lld\n", tot - (maxX - minX) * 2 - (maxY - minY) * 2);
    return 0;
}
```

---

## 作者：_czy (赞：0)

### 题目大意
给你一个多边形，你求安全的边多长。

且很关键的：**不安全就是被算在最外层的边的线。**
### 算法
我们可以用总周长减去不安全的边的长就行了。时间复杂度显然是 $O(n)$。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 1003
int n,X,Y,s,x,y,fx,fy,u=INT_MIN,d=INT_MAX,l=INT_MAX,r=INT_MIN;
int main(){
	scanf("%d%d%d",&n,&fx,&fy);
	X=fx,Y=fy;
	for(int i=2;i<=n;i++){
		scanf("%d%d",&x,&y);
		u=max(u,y),r=max(r,x),d=min(d,y),l=min(l,x);
		s+=abs(x-X)+abs(y-Y),X=x,Y=y;
	}
	s+=abs(fx-X)+abs(fy-Y);
	printf("%d",s-(r-l+u-d)*2);
}
```

---

## 作者：CleverPenguin (赞：0)

代码难度不大，重在理解。

向外平移后能与其他边相遇：除了上下左右的最外边，其他的都很安全。

也就是说，只需要将上下左右的最值统计，再计算周长，用周长减去最值和即为最终结果。

注意：可能有负值，第一个点要再和最后一个点算。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,c=0,x,y,z1,z2,l=INT_MAX,r=INT_MIN,u=INT_MIN,d=INT_MAX;
int main(){
	scanf("%d%d%d",&n,&z1,&z2);
	int m=z1,k=z2;//特殊处理第一个点，存在最后一个点再计算 
	for(int i=2;i<=n;i++){
		scanf("%d%d",&x,&y);
		r=max(r,y);//上下左右的大值统计出来用周长去减 
		u=max(u,x);
		l=min(l,y);
		d=min(d,x);
		c+=abs(x-z1)+abs(y-z2);//周长计算 
		z1=x;//记录为下一个计算点 
		z2=y;
	}
	c+=abs(m-z1)+abs(k-z2);//最后一个距离 
	printf("%d",c-(r-l+u-d)*2);
	return 0;
}
```

---

## 作者：Peck (赞：0)

## 题意

给定一个多边形，求“安全”的线的总长。

## 分析 

“安全”的的定义会让人有点疑惑，其实就是一条边被其他边挡住了，出不去。可以换一种理解方法：**不被算在最外层的边的线**，就是“安全”的线。

说到这，是不是恍然大悟了？没错，就是算不被统计到周长中的线的长度。

那么，解决这个问题，就很简单了，只需求出四个顶点的位置与该多边形的周长，再用四个顶点围出的矩形周长减去多边形的周长，就是答案了。 

**注意：第一次与最后一次的点也会连一条线**。

## 代码

一定要注意第一次输入的情况！

```cpp
#include <iostream>
#include <cmath>
using namespace std;

int n, sum = 0;
int fx, fy, up = -1e9, down = 1e9, r = -1e9, l = 1e9, ux, uy;
//注意题目中的 x与 y会是负数 
//fx、fy为一开始的点的坐标，ux、uy为上一次点的坐标（为了连线） 

signed main() {
	cin >> n;
	for (int i = 1, x, y; i <= n; i++) {
		cin >> x >> y;
		if (i == 1)
			fx = x, fy = y;
		up = max(y, up);
		down = min(y, down);
		l = min(x, l);
		r = max(x, r);
		//计算四个顶点 
		if (i != 1)//注意这里是只有当 ux, uy 有值时才能这么干，所以不能是第一次 
			sum += abs(x - ux) + abs(y - uy);
		ux = x, uy = y;//记录 
	}
	sum += abs(fx - ux) + abs(fy - uy);//连接一开始的点和最后的点 
	int C = ((up - down) + (r - l)) * 2;//周长 
	cout << sum - C << endl;
	return 0;
}
```


---

## 作者：封禁用户 (赞：0)

# P7027 [NWRRC2017] Intelligence in Perpendicularia 题解

[题面](https://www.luogu.com.cn/problem/P7027)

## 思路

1. 安全的边指在四周被其它边挡住的边。

2. 因为边的平移使其周长不变但形状变为矩形，所以我们求出周长和上下左右四个边界，最后用周长减去即可。

## code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define il inline
#define re register
#define endl '\n'

const int maxn=1001;
int n,x[maxn],y[maxn],c,u=-1e18,d=1e18,l=1e18,r=-1e18;

signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>x[i]>>y[i];
		if(i>1)
		{
			u=max(u,y[i]);
			d=min(d,y[i]);
			l=min(l,x[i]);
			r=max(r,x[i]);
			c+=abs(x[i]-x[i-1])+abs(y[i]-y[i-1]);
		}
	}
	c+=abs(x[n]-x[1])+abs(y[n]-y[1]);
	cout<<c-(r-l+u-d)*2<<endl; 
	return 0;
}
```

---

## 作者：封禁用户 (赞：0)

~~水社贡ing~~
# 题意
题目说呢有个多边形啊，然后它的边是垂直或平行于水平面的。

他要让你求出“安全”的边，题目说的是 “一个单位长度的边是安全的当且仅当它向外平移后能与其余边相遇”，翻译成~~人话~~正常的话就是被其他的边包住的边。

# 思路
如果每个边移动到坐标轴上去看，一个一个判断坐标轴上的点是不是有两个以上的边。

但是可能会报时间~~虽然数据较水，不会爆~~

其实，我们可以用小学二年级的知识，把外面的边移成一个矩形，里面的边就是安全的边。

那安全的边的长度就是里面的边的长度。怎么算？所有的边的长度就是这个多边形的周长。而外面矩形的周长就是最上最下最左最右四个点组成矩形的周长。简单来说就像这样：
![](https://cdn.luogu.com.cn/upload/image_hosting/3v02j83k.png?x-oss-process=image/resize,m_lfit,h_340,w_455)

**~~画的有点丑~~**

那只要在输入里统计就好啦~

## AC code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,cd=0,x,y,first1,first2;
signed main(){
    int l=INT_MAX/2,r=INT_MIN/2,u=INT_MIN/2,d=INT_MAX/2;
	cin>>n>>first1>>first2;
	int ff1=first1,ff2=first2;//先存着第一个点（最后一个点和第一个点还能组成一条边）
	for(int i=2;i<=n;i++){
		cin>>x>>y;
		cd+=abs(first1-x)+abs(first2-y);//继续累加周长 
        //找到上下左右的最大值（矩形）
		u=max(x,u);//上
		d=min(x,d);//下
		r=max(y,r);//右
		l=min(y,l);//左
		first1=x;//
		first2=y;
	}
	cd+=abs(ff1-first1)+abs(ff2-first2);//最后一个距离 
	cout<<cd-(u-d+r-l)*2;
	return 0;
}

```

---

