# [PA 2014] Lustra

## 题目描述

Byteasar 公司专门外包生产带有镜子的衣柜。

刚刚举行的招标会上，有 $n$ 个工厂参加竞标。所有镜子都是长方形的，每个工厂能够制造的镜子都有其各自的最大、最小宽度和最大、最小高度。镜子不可以旋转。

如果存在某家工厂满足这样的条件：其他所有工厂能够制造的镜子，它都能够制造。那么这家工厂显然会胜出。若不存在，评判工作将会遇到麻烦。

Byteasar 想知道，是否存在某家工厂符合上述条件。

## 说明/提示

对于 $100\%$ 的数据，$1\le t\le 10$，$2\le n\le 10^5$，$1\le w_1\le w_2\le 10^9$，$1\le h_1\le h_2\le 10^9$。

## 样例 #1

### 输入

```
3
3
2 3 3 5
1 4 2 6
1 3 4 6
3
1 5 1 3
2 4 1 3
3 4 2 5
4
1 2 1 10
1 2 3 8
2 2 7 10
1 2 1 10```

### 输出

```
TAK
NIE
TAK```

# 题解

## 作者：Up_Xu (赞：5)

# 题意
给出 $n$ 个制镜厂各自所能制造镜子的最小宽度、最大宽度、最小高度、最大高度，
求是否有制镜厂能制出所有其它制镜厂能制出的镜子。

# 思路
若有一家制镜厂 $i$ 能制出所有其它制镜厂能制出的镜子，就说明此制镜厂所制镜子的最小宽度 $w1_i$ 为所有厂制镜最小宽度的最小值，最大宽度 $w2_i$ 为所有厂制镜最大宽度的最大值，最小高度 $h1_i$ 为所有厂制镜最小高度的最小值，最大高度 $h2_i$ 为所有厂制镜最大高度的最大值。

这么一想，本题就超级简单了。求出所有制镜厂制镜最小宽度的最小值 $mw1$，制镜最大宽度的最大值 $mw2$，制镜最小高度的最小值 $mh1$，以及制镜最大高度的最大值 $mh2$。然后枚举每家制镜厂，看是否有一家的最小宽度与 $mv1$ 相等，最大宽度与 $mv2$ 相等，最小高度与 $mh1$ 相等，最大高度与 $mh2$ 相等即可。

# 代码

```
#include <bits/stdc++.h>
#define M 100010
using namespace std;
int T,n;
int w1[M],w2[M],h1[M],h2[M],mw1,mh1,mw2,mh2;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);//加速代码 
	cin>>T;
	while(T--){
		cin>>n;
		mw1=mh1=1e9;mw2=mh2=0;//先赋上最大值与最小值 
		for(int i=1;i<=n;i++){
			cin>>w1[i]>>w2[i]>>h1[i]>>h2[i];
			mw1=min(mw1,w1[i]);//求最小宽度的最小值
			mw2=max(mw2,w2[i]);//求最大宽度的最大值
			mh1=min(mh1,h1[i]);//求最小高度的最小值
			mh2=max(mh2,h2[i]);//求最大高度的最大值
		}
		int flag=1;
		for(int i=1;i<=n;i++)
			if(w1[i]==mw1&&w2[i]==mw2&&h1[i]==mh1&&h2[i]==mh2){//判断是否都相等 
				cout<<"TAK\n";
				flag=0;
				break;
			}
		if(flag)cout<<"NIE\n";
	}
}
```

---

## 作者：York佑佑 (赞：2)

## 题意
给出 $n$ 个制镜厂各自所能制造镜子的最小宽度、最大宽度、最小高度、最大高度，求是否有制镜厂能制出所有其它制镜厂能制出的镜子。有则输出 `TAK`，无则输出 `NIE`。

很明显，问题可以转化为：给定若干组区间 $w1,w2,h1,h2$，问是否有一组区间包含所有的区间。
## 分析
把题意转化后，问题其实就很简单了。

我们定义四个变量 $min\_w,max\_w,max\_h,min\_h$，分别代表最小的 $w1$，最大的 $w2$，最小的 $h1$，最大的 $h2$。


那么，我们每读入一组数据，如果这个区间包含所有区间，那么这个就是包含所有区间的区间。如果这个区间还不在包含所有区间的区间内，那么没有区间包含所有的区间。

同时，要更新 $min\_w,max\_w,max\_h,min\_h$ 的数值。判断到最后一组区间时，就可以知道是否有一组区间包含所有的区间了。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int t,n,w1,w2,h1,h2;
int max_h,max_w,min_h,min_w;
bool flag;//flag代表这组区间是否包含所有区间 
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>n;
		flag=1;//别忘了flag初始定义 
		min_w=min_h=1e9+1;
		max_w=max_h=-1;
		for(int i=1;i<=n;i++)
		{
			cin>>w1>>w2>>h1>>h2;
			if(w1<=min_w&&w2>=max_w&&h1<=min_h&&h2>=max_h)//如果当前输入的区间包含所有区间 
				flag=1;//那么存在包含所有区间的区间 (这个就是)
			else if(!(w1>=min_w&&w2<=max_w&&h1>=min_h&&h2<=max_h))//如果这个区间还不在包含所有区间的区间内 
				flag=0;//那么没有区间包含所有的区间 
			min_w=min(min_w,w1);
			max_w=max(max_w,w2);
			min_h=min(min_h,h1);
			max_h=max(max_h,h2);//更新min_w,max_w,max_h,min_h的数值 
		}
		cout<<(flag?"TAK":"NIE")<<endl;//输出 
	}
	return 0;
}
```



---

## 作者：SingularPoint (赞：2)

### 题目大意
给定两条数轴和若干组区间 $[w1,w2]$、$[h1,h2]$，问是否存在一组区间使得其它所有区间在对应数轴上都是该区间的子集。
### 分析
其实就是询问区间总合的最值是否属于一组区间~

但是我们也可以换种想法

考虑到我们只需要关注当前要查询的区间与总区间的关系，并且题目并不要求我们必须求出符合要求的区间序号，可以**只记录在当前区间之前的区间最值**和**是否有满足条件的区间**，并与当前区间进行比较。

由上文我们可以明显地知道，如果当前有区间符合要求，则我们所记录的区间最值就是符合要求的区间，对结果没有影响。

而当前区间与区间最值的关系也显而易见：如果是包含关系则当前区间**可能**符合要求，如果区间相交则说明当前区间**不可能**符合要求，如果被包含则当前状况**不变**。

上面分析的实现过程直接在输入过程中就可以实现~

上代码！
### Code
```cpp
#include<bits/stdc++.h>
#define ull unsigned long long
#define ll long long
#define db double
using namespace std;
int T,n;
int w1,w2,h1,h2;
int maw,miw,mah,mih;
bool key;
int main()
{
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		scanf("%d%d%d%d",&miw,&maw,&mih,&mah);
			//先将第一组数据作为总区间 
		key=1;//key记录是否有数据符合要求 
		for(int i=2;i<=n;i++){
			scanf("%d%d%d%d",&w1,&w2,&h1,&h2);
			if(w1<=miw && w2>=maw && h1<=mih && h2>=mah) key=1;
				//当前输入的区间可以作为答案 
			else if(w1>=miw && w2<=maw && h1>=mih && h2<=mah) key=key;
				//被包含，无影响 
			else key=0;
			miw=min(miw,w1);
			maw=max(maw,w2);
			mih=min(h1,mih);
			mah=max(h2,mah);
				//更新总区间 
		}
		if(key) printf("TAK\n");
		else printf("NIE\n");
	}
	return 0;
}
```
完结撒fa~

---

## 作者：Adolfo_North (赞：1)

#### 提供一种极易理解的纯模拟做法。

虽然时空都不是很优秀，但是距离时空超限还绰绰有余。并且没有运用什么深奥的算法与技巧，非常适合算法初学者，并且还留有极大的优化空间。

理解题意，题目要求我们求出是否有工厂可以生产其他所有工厂的镜子，为满足这个要求，那么符合条件的工厂的  $w1,w2,h1,h2$ 一定是最小的。所以可将问题转化为求所有数据中 $w1,w2,h1,h2$ 四个数的最小值，是否在同一工厂。

- 易错点：

### Q:

那么不是在输入的时候将 $w1,w2,h1,h2$ 四个数的最小值，分别记录，并且记录下它们的下标就可以了吗？这不就是在一串数中找最大、最小值的位置吗？然后，如果 $w1,w2,h1,h2$ 四个数的最小值的下标都一样，就输出  `TAK` 否则输出 `NIE`。

### A:

其实不然，请看数据（在 $n=4$ 时）：

```
1 5 2 3
2 3 2 6
1 5 1 6
1 5 1 4
```
$w1,w2$ 的最小值都存在于第一家工厂、第三家工厂和最后一家工厂中。但是一般性的查询 $w1,w2$ 两个数的最大、最小值的下标都会记录第一家工厂或最后一家工厂。然后程序就会发现 $h1,h2$ 两个数的最大、最小值的下标不在第一家工厂，与最后一家工厂，从而输出 `NIE`。但答案确是 `TAK`。

如何解决这种情况呢？我们可以将输入进来的 $w1,w2,h1,h2$ 四个数与前边已经计算好的 $w1,w2,h1,h2$ 的最大、最小值比较，如果等于最大、最小值，就将其加入标记数组中，代表这家工厂有可能有能力生产其他所有工厂的镜子。如果大于、小于最大、最小值，就见最大、最小值跟换，并清空标记数组。

这一部分的代码实现。

```cpp
if(w1<=minw1){
    if(w1==minw1) fw1[i]=1;
    else {
        minw1=w1;
        memset(fw1,0,sizeof fw1);
        fw1[i]=1;
    }
}
```


------------

整体代码实现：

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n;
int minw1,maxw2,minh1,maxh2;
bool fw1[100001],fw2[100001],fh1[100001],fh2[100001];
int main(){
	cin>>T;
	while(T--){
		minw1=minh1=10e9+1;
		maxw2=maxh2=-1;
		int a,b,c,d;
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a>>b>>c>>d;
            //这一部分已讲解，不再添加注释。
			if(a<=minw1){
				if(a==minw1) fw1[i]=1;
				else {
					minw1=a;
					memset(fw1,0,sizeof fw1);
					fw1[i]=1;
				}
			}
			if(b>=maxw2){
				if(b==maxw2) fw2[i]=1;
				else {
					maxw2=b;
					memset(fw2,0,sizeof fw2);
					fw2[i]=1;
				}
			}
			if(c<=minh1){
				if(c==minh1) fh1[i]=1;
				else {
					minh1=c;
					memset(fh1,0,sizeof fh1);
					fh1[i]=1;
				}
			}
			if(d>=maxh2){
				if(d==maxh2) fh2[i]=1;
				else {
					maxh2=d;
					memset(fh2,0,sizeof fh2);
					fh2[i]=1;
				}
			}
		}
        //遍历 n 家工厂，如果某家工厂四个数值都符合条件，输出 TAK。
		bool flag=1;
		for(int i=1;i<=n;i++){
			if(fw1[i]&&fw2[i]&&fh1[i]&&fh2[i]){
				cout<<"TAK"<<'\n';
				flag=0;
				break;
			}
		}
		if(flag) cout<<"NIE"<<'\n';
		memset(fh2,0,sizeof fh2);
		memset(fh1,0,sizeof fh1);
		memset(fw2,0,sizeof fw2);
		memset(fw1,0,sizeof fw1);
	}
	return 0;
}
```


---

## 作者：RNTBW (赞：1)

## 题意

有 ``n`` 个玻璃工厂，每个工厂可以生产宽度 $w$，高度 $h$ 的玻璃，满足 $w_1 \leqslant w \leqslant w_2,h_1 \leqslant h \leqslant h_2$，其中 $w_1,w_2,h_1,h_2$ 是给出的。

让你求有没有一家工厂，它能生产其他所有工厂能生产的玻璃。

## 思路

吐槽一下，此题也就橙题难度吧...

第一眼看到题面，这是啥意思？？

相信很多人都有我这个疑问。

然而，我们要记住这样一句话：

 _想要切一道题，得先理解题意；想要理解题意，得先模拟样例。_
 
~~沃.兹基硕德~~

所以，以第一组样例为例：

2 3 3 5

1 4 2 6

1 3 4 6

然后可以发现，第二个工厂是符合要求的。

为什么这么说呢？

仔细观察，第一个工厂的 $w_1$ 是 2，$w_2$ 是 3。

也就是说，第一个工厂的玻璃宽度最小是 2，最大是 3。

而第二个工厂的玻璃宽度最小是 1，最大是 4。

所以第二个工厂的玻璃宽度是覆盖了第一个工厂的。

高度同理，所以第二个工厂生产的玻璃是可以完全覆盖第一个工厂的，不管第一个工厂生产 $w,h$ 为多少的玻璃。

恍然大悟，一个工厂能生产另一个工厂能生产的玻璃就是指 **这个工厂能生产的玻璃宽度把另一个工厂能生产的玻璃宽度覆盖在内，高度亦然。**

那这道题不就迎刃而解了吗？

我们设 ``k`` , ``s`` , ``l`` , ``p`` 四个变量：

$$
k=\min \limits_{1 \le i \le n}w_1
$$
$$
l=\max \limits_{1 \le i \le n}w_2
$$
$$
s=\min \limits_{1 \le i \le n}h_1
$$
$$
p=\max \limits_{1 \le i \le n}h_2
$$

很明显，它们代表了玻璃宽度，高度的最大范围。

只要把 ``k`` , ``s`` , ``l`` , ``p`` 求出来，并判断它们是不是一个工厂能生产出来的就可以了。

时间复杂度 $O(T \times 2 \times n)$。

~~道理自己去想吧~~~

放代码喽~~

```cpp
#include<cstdio>
#define mx 100005
int x1[mx],x2[mx],x3[mx],x4[mx];
int t,n,i,k,l,s,p;
bool f;
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		k=s=1e9;l=p=f=0;
		for(i=1;i<=n;i++)
		{
			scanf("%d%d%d%d",&x1[i],&x2[i],&x3[i],&x4[i]);
			if(x1[i]<k)k=x1[i];
			if(x2[i]>l)l=x2[i];
			if(x3[i]<s)s=x3[i];
			if(x4[i]>p)p=x4[i];
		}
		for(i=1;i<=n;i++)
			if(x1[i]==k&&x2[i]==l&&x3[i]==s&&x4[i]==p)f=1;//判断宽度最小值，最大值，高度最小值，最大值是不是同一家工厂能生产的
                //如果不是，则无解
		if(f)puts("TAK");
		else puts("NIE");
	}
	return 0;
}
```
完结撒花~

---

## 作者：JK_LOVER (赞：1)

## 题意
是否有一个矩形可以包含所有矩形，边界重合也算。
## 分析
当一个矩形包含其它矩形时满足（此时 矩形 $2$ 包含矩形 $1$ ）
$$
x_{1max}\le x_{2max},x_{2min}\le x_{1min}
$$
$$
y_{1max}\le y_{2max},y_{2min}\le y_{1min}
$$
那我们可以维护全局最大值，最小值。代码就比较简单了。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod = 1000000007;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
inline void write(int x)
{
    if(x<0){putchar('-');x=-x;}
	if(x>9)write(x/10);
    putchar(x%10+'0');
}
const int N = 12010;
struct node{int x,X,y,Y;}S[N];
int main()
{
	int T = read();
	while(T--)
	{
		int maxx=-1,maxy=-1,minx=1e9,miny=1e9,n;
		n = read();
		for(int i = 1;i <= n;i++)
		{
			int a = read(),b = read(),c = read(),d = read();
			S[i] = (node){a,b,c,d};
			minx = min(minx,a);
			maxx = max(maxx,b);
			miny = min(miny,d);
			maxy = max(maxy,d);
		}
		for(int i = 1;i <= n;i++)
		{
			if(S[i].X>=maxx&&S[i].Y>=maxy&&S[i].x<=minx&&S[i].y<=miny)
			{
				cout<<"TAK"<<endl;
				break;
			}
			if(i == n) 
			cout<<"NIE"<<endl;
		}
	}
	return 0;
	
}
```
[地址](https://www.luogu.com.cn/blog/xzc/solution-p5995)

---

## 作者：Terrible (赞：1)

我们把所有工厂的**全局范围**求出来，对比**最大工厂范围**。
#### 如果最大厂子范围等于全局范围，那么存在某家工厂符合条件。
##### **全局范围**：
所有工厂的最小宽、高到最大宽、高的范围，任意一个工厂的范围都在全局范围内
##### **最大工厂范围**：
因为很有可能两个工厂的范围相交而不包含，所以我们要设定对比最小宽、高和最大宽、高范围的优先级，但是**我们只需要确定是否存在某工厂范围等于全局范围**。如果存在这个工厂那么这个工厂的范围就是全局范围，按任何优先级别都可以得出最大工厂范围，如果不存在，那么按任何优先级别的出的工厂都不满足要求；
###### 附上代码：
```cpp
#include<cstdio>
#define N 2147483647
#define min(a,b) (a<b?a:b)
#define max(a,b) (a>b?a:b)
#define change w0=a,w1=b,h0=c,h1=d			//用于后面的交换 
inline int read()							//快读 
{
	int a=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9')a*=10,a+=c-'0',c=getchar();
	return a*f;
}
int main()
{
	int t=read();
	while(t--){								//t组数据	
		int n=read();
		int wmin=N,wmax=-N,hmin=N,hmax=-N;	//初始化 全局范围
		int w0=N,w1=-N,h0=N,h1=-N;			//初始化 最大工厂范围
		for(register int i=0;i<n;i++){
			int a=read(),b=read(),c=read(),d=read();
			wmin=min(wmin,a);
			wmax=max(wmax,b);
			hmin=min(hmin,c);
			hmax=max(hmax,d);		//取 全局范围 最大值。 
			if(w0>a) change;		//最大工厂范围 判断依次是： 
			else					//最小宽、最大宽、最小高、最大高。 
			{						//可以调换判断顺序，前一项相等，  
				if(w0==a)			//那么对比下一项，取范围最大。 
				{					//如果一家工厂能生产所有工厂的镜子， 
					if(w1<b) change;//那么全局范围等于最大工厂范围。 
					else
					{
						if(w1==b)
						{
							if(h0>c) change;
							else
							{
								if(h0==c)
								{
									if(h1<d) change;
								}
							}
						}
					}
				}
			}
		}
		if(w0==wmin&&w1==wmax&&h0==hmin&&h1==hmax)printf("TAK\n");
		else printf("NIE\n");		//输出 
	}
}

```


---

## 作者：Crasole (赞：0)

## 题意

------

有 $n$ 个玻璃工厂参加了竞标，对于工厂 $i$ 能生产的玻璃宽最小为 ${w1}_ i$，最大为 ${w2}_ i$。高最小为 ${h1}_ i$，最大为 ${h2}_ i$。

现在问，是否存在一座工厂 $i$，${w1}_ i$，${h1}_ i$ 最小，${w2}_ i$，${h2}_ i$ 最大。有则输出 `TAK`，否则输出 `NIE`。

一共有 $T$ 组数据。

## 思路

------

我们可以统计所有工厂中最小的 $w1$，最大的 $w2$，最小的 $h1$，最大的 $h2$。

- $minw$ 代表所有工厂中最小的 $w1$。

- $maxw$ 代表所有工厂中最大的 $w2$。

- $minh$ 代表所有工厂中最小的 $h1$。

- $maxh$ 代表所有工厂中最大的 $h2$。

统计好后，我们只需看一下 $n$ 个工厂中是否存在工厂 $i$，$w1_i$ 等于 $minw$，$w2_i$ 等于 $maxw$，$h1_i$ 等于 $minh$，$h2_i$ 等于 $maxh$。有则输出 `TAK`，否则输出 `NIE`。

## 代码

-----

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int t,n,w1[N],w2[N],h1[N],h2[N];
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		int maxw=-1,minw=1e9+1,maxh=-1,minh=1e9+1;
		for(int i=1;i<=n;i++){
			cin>>w1[i]>>w2[i]>>h1[i]>>h2[i];
			maxw=max(maxw,w2[i]),minw=min(minw,w1[i]),
			maxh=max(maxh,h2[i]),minh=min(minh,h1[i]);
            		//统计maxw,minw,maxh,minh
		}
		bool flag=0;//flag标记
		for(int i=1;i<=n;i++)
			if(w1[i]==minw&&w2[i]==maxw&&h1[i]==minh&&h2[i]==maxh){//如果存在工厂i
				flag=1;break;//flag标1
			}
		cout<<(flag?"TAK":"NIE")<<endl;//输出 		
	}
	return 0;
}
```

---

## 作者：_Sushi (赞：0)

题目：[P5995](https://www.luogu.com.cn/problem/P5995)

题目大意：给定平面上若干个矩形，判断是否有一个矩形包含其他所有矩形。

分析：先找出一个最小的矩形（不一定是输入的矩形中的），使得它能够包含那些输入的矩形。显然，如果解存在的话，必定和这个最小的矩形重合。反之亦然，如果输入的矩形中没有与这个最小的矩形重合，那么必定无解。因为如果一个矩形不重合于这个最小的矩形且包含其它输入的矩形，那么这个“最小的矩形”就不是最小的矩形了。

那怎么求这个最小的矩形呢？其实也很简单。对于每个输入的矩形，求出 $h$ 和 $w$ 的最大值和最小值就行了。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
int wl[500000],wr[500000],hl[500000],hr[500000];
int minw,maxw,minh,maxh;
bool flag;
int main()
{
    scanf("%d",&t);
    while(t--)   //多组数据
    {
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
        {
            scanf("%d%d%d%d",&wl[i],&wr[i],&hl[i],&hr[i]);
            if(i==1) minw=wl[i],maxw=wr[i],minh=hl[i],maxh=hr[i];
            else minw=min(minw,wl[i]),maxw=max(maxw,wr[i]),minh=min(minh,hl[i]),maxh=max(maxh,hr[i]);     //求出最大值和最小值
        }
        flag=1;     //由于有多组数据，所以记得初始化
        for(int i=1;i<=n;i++)
            if(minw==wl[i]&&maxw==wr[i]&&minh==hl[i]&&maxh==hr[i])    //如果两个这矩形重合，就必定有解
            {
            	flag=0;
            	printf("TAK\n");
            	break;
            }
        if(flag) printf("NIE\n");//否则无解
    }
    return 0;
}
```


---

## 作者：ajhuhe (赞：0)

# 题目简述

每次给定两个区间 $[w1,w2]$ 以及 $[h1,h2]$，我们需要求出是否存在一组 $[w1_i,w2_i]$ 包含了之前所有的 $[w1,w2]$ 区间，以及在同一组数据中的一组 $[h1_i,h2_i]$ 包含了之前所有的 $[h1,h2]$ 区间。

# 题目分析

这道题采用**模拟**的算法。用四个变量分别记录几组数据中 $w,h$ 最大值 $w_{max}$，$h_{max}$ 以及最小值 $w_{min}$，$h_{min}$。最后枚举是否存在一个工厂生产镜子的宽度 ($w1$，$w2$) 以及高度 ($h1$，$h2$)，满足：$w1=w_{min}$，$w2=w_{max}$，$h1=h_{min}$，$h2=h_{max}$。每组测试数据的时间复杂度为 $O(2N)$。最后，记得每一次清空脏数据！


# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int INF=1e9+1;
int n,t,wmax,wmin=INF,hmax,hmin=INF;
struct node//储存输入
{
	int w1;
	int w2;
	int h1;
	int h2;
}a[100001];
int main()
{
	cin>>t;
	while(t--)
	{
		hmax=wmax=0;//初始化很重要！
		hmin=wmin=INF;
		for(int i=1;i<=n;i++)
			a[i].h1=a[i].h2=a[i].w1=a[i].w2=0;
		cin>>n;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i].w1>>a[i].w2>>a[i].h1>>a[i].h2;
        	//讨论 w,l 的范围
			wmax=max(wmax,a[i].w2);
			wmin=min(wmin,a[i].w1);
			hmax=max(hmax,a[i].h2);
			hmin=min(hmin,a[i].h1);
		}
		int i;
		for(i=1;i<=n;i++)
		{
			if(a[i].w1<=wmin&&a[i].w2>=wmax&&a[i].h1<=hmin&&a[i].h2>=hmax)//判断是否符合要求 
			{
				cout<<"TAK\n";//符合要求，输出TAK 
				break;
			}
		}
		if(i>n)
			cout<<"NIE\n";//不符合要求，输出NIE 
	}
	return 0;
}
```

---

## 作者：书雪 (赞：0)

如果一家工厂满足其他所有工厂能够制造的镜子，它都能够制造的条件，那么它能生产的最小宽一定是所有工厂能生产的最小宽中最小的（可以并列），它能生产的最大宽一定是所有工厂能生产的最大宽中最大的，高也是一样。

那么我们只需要求出所有厂家最小宽的最小值，最大宽的最大值，最小高的最小值，最大高的最大值，在枚举是否有厂家能全部满足这些条件就可以了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,minw=0x7fffffff,maxw,minp=0x7fffffff,maxp;//为了求出最小值和最大值先初始化
struct node{
	int w1,w2,p1,p2;
}a[100010];
int main(){
	scanf("%d",&t);
	for(int i=1;i<=t;i++){
		scanf("%d",&n);
		for(int j=1;j<=n;j++){
			scanf("%d%d%d%d",&a[j].w1,&a[j].w2,&a[j].p1,&a[j].p2);
			minw=min(minw,a[j].w1);//求出最大值和最小值
			minp=min(minp,a[j].p1);
			maxw=max(maxw,a[j].w2);
			maxp=max(maxp,a[j].p2);
		}
		for(int j=1;j<=n;j++){
			if(a[j].p1==minp&&a[j].p2==maxp&&a[j].w1==minw&&a[j].w2==maxw){
				printf("TAK\n");//如果有厂家满足所有条件，就输出TAK并重新初始化，为下一轮做准备
				minw=0x7fffffff,maxw=0,minp=0x7fffffff,maxp=0;
				break;
			}
			if(j==n){
				printf("NIE\n");//如果遍历完最后一个厂家仍然没有满足条件的，就输出NIE并初始化
				minw=0x7fffffff,maxw=0,minp=0x7fffffff,maxp=0;
				break;
			}
		}
	}                        
        return 0;
}

```


---

## 作者：Daidly (赞：0)

## 简析题目

给出$n$个矩形的长宽，问是否有一个矩形的长和宽大于等于所有的矩形的长和宽。

## 思路与做法

如果存在一个矩形的长和宽大于等于所有的矩形的长和宽，那么它必定是这些矩形中所有数据 $(w1,w2,h1,h2)$ 最大的那一个。

所以我们只需要找到所有 $(w1,w2,h1,h2)$ 的最大值，再一个一个判断看有没有符合的就行了，代码很简单，如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 100005
template<class T>inline bool read(T &x){x=0;register char c=getchar();register bool f=0;
while(!isdigit(c)){if(c==EOF)return false;f^=c=='-',c=getchar();}
while(isdigit(c))x=(x<<3)+(x<<1)+(c^48),c=getchar();if(f)x=-x;return true;}
template<class T>inline void print(T x){if(x<0)putchar('-'),x=-x;if(x>9)print(x/10);putchar(x%10^48);}
template<class T>inline void print(T x,char c){print(x),putchar(c);}
//快读不用关注
int t,n,wmin[N],wmax[N],hmin[N],hmax[N];
int main(){
	read(t);
	while(t--){
		read(n);
		int w_min=1e9,w_max=0,h_min=1e9,h_max=0;
		for(int i=1;i<=n;++i){
			read(wmin[i]),read(wmax[i]),read(hmin[i]),read(hmax[i]);
			w_min=min(w_min,wmin[i]);
			w_max=max(w_max,wmax[i]);
			h_min=min(h_min,hmin[i]);
			h_max=max(h_max,hmax[i]);
		}
		for(int i=1;i<=n;++i){
			if(wmin[i]==w_min&&wmax[i]==w_max&&hmin[i]==h_min&&hmax[i]==h_max){
				puts("TAK");break;
			}else if(i==n)puts("NIE");
		}
	}
}
```
谢谢大家，希望能让您理解这道题。

---

## 作者：sinsop90 (赞：0)

这道题最重要的是如何判断一个商家能否生产其他商家能生产的所有玻璃

我们考虑对于$w1, w2$, 找到 $w1$ 的最小值和 $w2$ 的最大值

显然商家对于这个最小值和最大值, 只有 $w1$ $=$ $minx$ 并且 $w2$ $=$ $maxx$ 这样的情况

我们对于 $h1, h2$ 也做一次这样的处理

显然商家对于这个最小值和最大值的情况和 $w1,w2$ 是一样的

因此我们只需要求出两个最小值和最大值,再一个个判断就可以了

代码:

```
#include<bits/stdc++.h>
using namespace std;
struct node {
	int x, y, xx, yy;
}e[200005];
int main() {
	int T;
	cin >> T;
	while(T--) {
		int n, minx=2147483647, maxx=-1, miny=2147483647, maxy=-1;
		cin >> n;
		for(int i = 1;i <= n;i++) {
			cin >> e[i].x >> e[i].y >> e[i].xx >> e[i].yy;
			minx = min(minx, e[i].x);//找到最小值最大值
			maxx = max(maxx, e[i].y);
			miny = min(miny, e[i].xx);
			maxy = max(maxy, e[i].yy);
		}
		bool flag = false;
		for(int i = 1;i <= n;i++) {
			if(e[i].x == minx && e[i].y == maxx && e[i].xx == miny && e[i].yy == maxy) {//一一比较
				flag = true;
				cout<<"TAK"<<endl;
				break;
			}
		}
		if(!flag) cout << "NIE" << endl;
		
	}
}
```


---

## 作者：bystander_silent (赞：0)

对于这题我的思路是先按某一维（最大长，最大宽，最小长或是最小宽）排序，然后比较：如果有第一个生产不了的，就输出 NIE 否则就是 TAK 。因为一旦有第一个生产不了的，那么那一个也肯定无法生产出所有第一个可以生产的。
附代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
struct node{
	int maxw,maxh,minw,minh;
}a[1000000];
bool cmp(node s,node d)//我这里是按最小宽优先来排 。 
{
	if(s.minw==d.minw && s.maxw==d.maxw)//如果最大宽和最小宽一样，那么就按长来排。 
	{
		if(s.minh==d.minh)
			return s.maxh>d.maxh;
		return s.minh<d.minh;
	}
	if(s.minw==d.minw)//如果最小宽一样 
		return s.maxw>d.maxw;
	return s.minw<d.minw;
} 
int main()
{
	scanf("%d",&t);
	for(int p=1;p<=t;p++)
	{
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
			scanf("%d%d%d%d",&a[i].minw,&a[i].maxw,&a[i].minh,&a[i].maxh);
		sort(a+1,a+n+1,cmp);
		int flag=0;
		for(int i=2;i<=n;i++)
		{
			if(a[i].maxh>a[1].maxh || a[i].minh<a[1].minh)//如果有第一个生产不了的 
			{
				flag=1;
				break;
			}
		}
		if(flag)
			printf("NIE\n");
		else
			printf("TAK\n");
	}
	return 0;//华丽结束 
}
```



---

