# Watchmen

## 题目描述

Watchmen are in a danger and Doctor Manhattan together with his friend Daniel Dreiberg should warn them as soon as possible. There are $ n $ watchmen on a plane, the $ i $ -th watchman is located at point $ (x_{i},y_{i}) $ .

They need to arrange a plan, but there are some difficulties on their way. As you know, Doctor Manhattan considers the distance between watchmen $ i $ and $ j $ to be $ |x_{i}-x_{j}|+|y_{i}-y_{j}| $ . Daniel, as an ordinary person, calculates the distance using the formula ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF650A/fcefde1ea60e1105aa698e148af7dc900a7454c9.png).

The success of the operation relies on the number of pairs $ (i,j) $ ( $ 1<=i&lt;j<=n $ ), such that the distance between watchman $ i $ and watchmen $ j $ calculated by Doctor Manhattan is equal to the distance between them calculated by Daniel. You were asked to compute the number of such pairs.

## 说明/提示

In the first sample, the distance between watchman $ 1 $ and watchman $ 2 $ is equal to $ |1-7|+|1-5|=10 $ for Doctor Manhattan and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF650A/91477f866a0e0d69e03fe1418359568f2f96b567.png) for Daniel. For pairs $ (1,1) $ , $ (1,5) $ and $ (7,5) $ , $ (1,5) $ Doctor Manhattan and Daniel will calculate the same distances.

## 样例 #1

### 输入

```
3
1 1
7 5
1 5
```

### 输出

```
2
```

## 样例 #2

### 输入

```
6
0 0
0 1
0 2
-1 1
0 1
1 1
```

### 输出

```
11
```

# 题解

## 作者：yuzhechuan (赞：5)

只有三个map的一篇题解

---

### 1. 手推公式

$|x2-x1|+|y2-y1|=\sqrt{(x2-x1)^2+(y2-y1)^2}$

设|x2-x1|=a,|y2-y1|=b

$a+b=\sqrt{a^2+b^2}$

$(a+b)^2=a^2+b^2$

$a^2+2ab+b^2=a^2+b^2$

$2ab=0$

$ab=0$

$|x2-x1|*|y2-y1|=0$

$|x2-x1|=0\:\:or\:\:|y2-y1|=0$

**$x1=x2\:\:or\:\:y1=y2$**

---

### 2.算法 

由公式可知，横纵坐标二选一相同时，两点符合要求

坐标值域很大，可以直接上map

X[]存某行出现过点数,Y[]存某列出现过的点数,p[][]存某个坐标出现过的点数

X[x]+Y[y]-p[x][y]就是答案

---
### 3.优化

众所周知,map复杂度是log级的，而unordered_map是O(1)的

所以对于两个下标是int的我们可以用unordered_map代替

---
### 4.补充

make_pair(x,y)的意思是将x,y搞成一个pair<,>型东西

以下两段代码等价：

```cpp
a=make_pair(x,y);
```

```cpp
a.first=x;
a.second=y;
```

---
**(tips.因为CF的c++版本很高，所以要去掉斜杠那两句话，但NOIP中要加上)**
```cpp
#include <bits/stdc++.h>
//#include <tr1/unordered_map>
//using namespace std::tr1;
using namespace std;
unordered_map<int,int> X,Y;
map<pair<int,int>,int> p;
long long ans; //答案会爆int
int n;
signed main(){
    scanf("%d",&n);
    for(int i=1,x,y;i<=n;i++){
        scanf("%d%d",&x,&y);
        ans+=X[x]+Y[y]-p[make_pair(x,y)];
        X[x]++;
        Y[y]++;
        p[make_pair(x,y)]++;
    }
    printf("%I64d",ans);
}

```

---

## 作者：素质玩家孙1超 (赞：3)

~~由于我做题时没看到题解，所以就写一篇吧~~

这是一个hash的题目，也可以用map暴力（我就是这么干的）

题目解释：当两个点的欧几里得距离与其曼哈顿距离一样时，

他们一定是有相同的横坐标或纵坐标。我们用两个数组来存它们。

最后计算时，就只要算有多少种取点方式就好了。


------------



假如有n个点的横坐标相同（没有重点），那么我们可以很容易知道

我们有**n*(n-1)/2**种取法。


计算重点：加如有m个点在同一个坐标下，我们会重复取他们**m*（m-1）/2**次

我们只要在读到相同的点后将ans-=num就好了

（num表示已经读到那个位置的重点个数）

~~稍微吐槽一下，我p取1e9+7时被卡掉了。。。~~

下面放代码
```cpp
#include<bits/stdc++.h>
#define int long long 
//不开long long 会出事情的
using namespace std;
const int Maxn=2e6+10;
const int p=1e9+9;//hash用的质数
int a[Maxn],b[Maxn];//记录
map<int,int>flagg;//记录 
map<int,int>x;//存x坐标 
map<int,int>y;//存y坐标
map<int,bool>flagx;//标记x 
map<int,bool>flagy;//标记y 
int f(int n)
{
	return (n-1)*n/2;//计算取法
}
signed main()
{
	int n,ans=0;
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld%lld",&a[i],&b[i]);
		if(flagg[a[i]*p+b[i]])
		{
			ans-=flagg[a[i]*p+b[i]];//判断重复
			flagg[a[i]*p+b[i]]++;
		}
		else
			flagg[a[i]*p+b[i]]=1;
		flagx[a[i]]=0;//初始化（其实可以不要）
		flagy[b[i]]=0;
		x[a[i]]++;
		y[b[i]]++;
	}
	for(int i=1;i<=n;i++)
	{
		if(!flagx[a[i]])//如果有x一样的
		{
			ans+=f(x[a[i]]);
			flagx[a[i]]=1;
		}
		if(!flagy[b[i]])//如果有y一样的
		{
			ans+=f(y[b[i]]);
			flagy[b[i]]=1;
		}
	}
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：_Han (赞：2)

## 题意
给出 $n$ 个点，问有多少个点对满足它们的曼哈顿距离等于欧式距离。

## Sol
由题意易得 ：

$\left\vert x1-x2\right\vert+\left\vert y1-y2\right\vert=\sqrt{(x1-x2)^2+(y1-y2)^2}$  

两边同时平方，合并同类项，可得：  

$2\times\left\vert x1-x2\right\vert\times\left\vert y1-y2\right\vert=0$  

显然要使得上方的等式成立，则必有 $x1=x2$ 或 $y1=y2$ 。  
那么只需要统计出 $x1=x2$ 和 $y1=y2$ 的个数即可。  
显然可以用 $map$ 来维护这一操作。  
若有 $k$ 个点横坐标相同，那么总方案数为 $\sum_{i=1}^ki$ 。  
纵坐标相同时同理。  
**必须将横纵坐标均相同的点重复计算的方案数减去** 。

## Code
```cpp
#include<bits/stdc++.h>
#define mp make_pair
#define int long long
using namespace std;
int x,y,n,ans;
map<int,int> m1,m2;
map<pair<int,int>,int> m3; //保存点坐标相同的情况
inline int read()
{
	int az=0,ff=1;
	char ch=getchar();
	while (!isdigit(ch))
	{
		if (ch=='-') ff=-1;
		ch=getchar();
	}
	while (isdigit(ch))
	{
		az=az*10+(int)(ch-'0');
		ch=getchar();
	}
	return az*ff;
}
signed main()
{
	n=read();
	for (int i=1;i<=n;i++)
	{
		x=read(); y=read();
		ans+=(m1[x]+m2[y]-m3[mp(x,y)]); //容斥原理计算方案数
		m1[x]++; m2[y]++; m3[mp(x,y)]++; //累加横纵坐标和点坐标相同的数量
	}
	cout<<ans<<endl;
}
```


---

## 作者：爱滑稽的蒟蒻 (赞：2)

看楼上大佬的题解都好NB啊，本蒟蒻表示不是很懂……

这题貌似不需要这么麻烦也可以A啊？？

先理解题意：要使曼哈顿距离和欧几里德距离相同的话，当且仅当两个点的连线与坐标轴平行即可。

那么怎么用代码实现呢？只要判断两个点纵坐标或横坐标相同即可。

但是这样写的话会wa……

仔细想一下的话，发现会有重点，会把两个坐标相同的点在横坐标和纵坐标上都加了一次，但实际上只需要加一次就可以了

所以需要开一个数组去重，本蒟蒻想到的是开桶，但是数组开不下……

所以愉快地用了map

为了方便，直接在map里套结构体，每次读入的时候判断一下在map中是否出现过，用总次数cnt减去出现过的点数就能去重啦

最后不要忘了开long long（本蒟蒻因为用了int导致wa了3次）

上ac代码！！


```cpp
#include<bits/stdc++.h>
using namespace std;
map<int,int>a,b;//分别记录横坐标和纵坐标 
struct node{
	int x,y;
	friend bool operator<(node a,node b)
	{
		if(a.x==b.x)return a.y<b.y;
		return a.x<b.x;	
	}//如果map中套用结构体，要重载 
}fre;
long long cnt=0;
map<node,int>mp;//记录重点 
signed main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		fre.x=x;fre.y=y; 
		cnt-=mp[fre];//减去重点 
		mp[fre]++;//记录重点数 
		cnt+=a[x];cnt+=b[y];//加上相等的点 
		a[x]++;b[y]++;
	}
	cout<<cnt;//愉快地输出
	return 0;
}
```


---

## 作者：xsgqwxj (赞：2)

### 这是一道十分明显的哈希题。~~（嗯，是的）~~           

求曼哈顿距离和欧氏距离相等的坐标组，得知道这两个距离的含义 

两点的欧氏距离就是两点的直线距离……               

而两点的曼哈顿距离就是abs(x1-x2)+abs(y1-y2)；         

所以只要两点的横坐标相等或纵坐标相等就是答案了！

####   **（不过，你还要除因横纵坐标都相同的重复的点而算两遍的部分）**

```cpp
//才学疏浅，就不手写哈希了
#include <cstdio>
#include <map>//std库映射（不懂得可以去网上自学一下（map都不知道你是怎么到提高组的））
#include <vector>//std库 （同上）
using namespace std; 

map<long long,long long> a1,a2;//存每个横纵坐标
map<vector<long long>,long long> a3;//合起来存

map<long long,long long>::iterator iter;//迭代器（和map,vector一起的）
map<vector<long long>,long long>::iterator iter1;

vector<long long> kk;
long long sum1[300000],sum2[300000],sum3[300000];//存横纵坐标和整个坐标组出现的次数
long long n,now1,now2,now3; 
long long ans;
//开的下先开着long long （本人经历过因为为了卡空间所以一部分变量没开long long而与一等失之交臂的事（当然还有高中的保送，而我中考差半分上那所学校…………））

int main(){
	long long a,b;
	scanf("%lld",&n);
	for(int i=0;i<n;i++){
		scanf("%lld%lld",&a,&b);
		
		kk.clear();//清空
		kk.push_back(a);
		kk.push_back(b);
		iter1=a3.find(kk);
		if(iter1!=a3.end()){//第一次出现存入，否则删去他与已经存在的答案一次
			sum3[iter1->second]++;
			ans-=sum3[iter1->second];
		//	printf("%dkkkk",sum3[iter1->second]);
		}
                else{
       		        a3[kk]=++now3;
		}
		
		
		iter=a1.find(a);
		if(iter!=a1.end()){//第一次出现存入，否则加入他与已经存在的横坐标相同的坐标组的答案
			sum1[iter->second]++;
			ans+=sum1[iter->second];
		}
       	        else{
       		        a1[a]=++now1;
		}
		
		
		iter=a2.find(b);
 		if(iter!=a2.end()){//第一次出现存入，否则加入他与已经存在的纵坐标相同的坐标组的答案
			sum2[iter->second]++;
			ans+=sum2[iter->second];
		}
       	        else{
       		        a2[b]=++now2;
		}
		
		
	}
	printf("%lld",ans);
}

```


---

## 作者：Zekrom (赞：2)

## 离散化+hash+map去重    
1.离散化处理坐标   
2.Hash 坐标->$x*n+y$  
3.map保存Hash值便于去重   
4.剩下的就是组合的知识就不介绍了   
上代码   
```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<queue>
#include<map>
#include<algorithm>
#define inf 0x3f3f3f3f
#define N 200010
#define ll long long 
using namespace std;
inline ll read(){
	ll x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-f;ch=getchar();
	}while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();
	}return x*f;
}
ll x[N],x1[N],x2[N],y[N],y1[N],y2[N],n,totx,toty,cntx[N],cnty[N],del,ans;
map<ll,ll>mp;
int main(){
	n=read();
	for(int i=1;i<=n;i++){
		x[i]=read(),y[i]=read();
		x1[i]=x[i];y1[i]=y[i];
	}
	sort(x1+1,x1+1+n);totx=unique(x1+1,x1+1+n)-x1-1;for(int i=1;i<=n;i++)x2[i]=lower_bound(x1+1,x1+1+totx,x[i])-x1;
	sort(y1+1,y1+1+n);toty=unique(y1+1,y1+1+n)-y1-1;for(int i=1;i<=n;i++)y2[i]=lower_bound(y1+1,y1+1+toty,y[i])-y1;
	for(int i=1;i<=n;i++){
		cntx[x2[i]]++;
		cnty[y2[i]]++;
	}
	for(int i=1;i<=n;i++){
		mp[x2[i]*n+y2[i]]++;
	}
	for(int i=1;i<=n;i++){
		if(mp[x2[i]*n+y2[i]]>=2){
			del+=mp[x2[i]*n+y2[i]]*(mp[x2[i]*n+y2[i]]-1)>>1;
			mp[x2[i]*n+y2[i]]=1;
		}
	}
	for(int i=1;i<=n;i++){
		if(cnty[i])ans+=cnty[i]*(cnty[i]-1)>>1;		
		if(cntx[i])ans+=cntx[i]*(cntx[i]-1)>>1;
	}
	printf("%lld\n",ans-del);
	return 0;
}

```


---

## 作者：Link_Cut_Y (赞：1)

首先解释一下题目里面的两个概念：

- 曼哈顿距离：即 $|x_a - x_b| + |y_a - y_b|$

- 欧几里得距离：即 $\sqrt{(x_a - x_b) ^ 2 + (y_a - y_b)^2}$，也就是两个点在平面上的连线长度。


在图里表示一下就是这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/gbixksch.png)

在图中，$AB$ 即为 $A, B$ 两点间的欧几里得距离，$AC + BC$ 即为两点间的曼哈顿距离。（图中 $\angle C = 90 \degree$）

我们可以很容易的看出，两点间的欧几里得距离大于等于他们的曼哈顿距离。因为欧几里得距离就是如图所示三角形的斜边，而曼哈顿距离则为两直角边之和。众所周知，三角形两边之和大于第三边。因此，**重要结论如下:**

> 两点间欧氏距离等于曼哈顿距离，当且仅当两点的横坐标或纵坐标相同。

这样就非常简单了。我们搞三个 $\texttt{map}$，分别记录横坐标相同的点的个数，纵坐标相同的点的个数，横纵坐标都相同的点的个数。从 $1$ 到 $n$ 遍历每个点，对于当前点 $(x_i, y_i)$，我们可以选择从之前的横坐标等于 $x_i$ 的点中任意选一个，方案数为 $Map_{x_i}$，对于纵坐标同理。但是别忘了减去与当前点重合的点。

于是超级剪短的代码就出来了。

### 核心代码：

```
map<int, int> x, y;
map<PII, int> s;
PII p[N]; // PII represents for pair<int, int>
for (int i = 1; i <= n; i ++ ) {
	res += x[p[i].x] ++ + y[p[i].y] ++ - s[{p[i].x, p[i].y}] ++ ;
} // 代码压行勿喷
```

---

## 作者：SamHJD (赞：1)

要想知道两个点的曼哈顿距离和欧氏距离是否相等，我们首先要了解这两个东西是什么。

这是欧氏距离。
![](https://cdn.luogu.com.cn/upload/image_hosting/gfoo380z.png)

这是曼哈顿距离。
![](https://cdn.luogu.com.cn/upload/image_hosting/ri8mow2d.png)

可以看出，欧氏距离是**两点之间的线段长度**，曼哈顿距离是 $x$ $y$ **坐标的差值和**。

如果两距离相等，只有一种可能，也就是 $x$ 坐标或 $y$ 坐标相等。证明方法也很简单，若其中一个坐标相等，曼哈顿距离取决于另一个坐标的差，欧氏距离也是如此。

那么代码就很简单了，我们只需要定义两个map数组存放 $x$ $y$ 坐标即可。

但有一大坑点在这，我们可以用一张图形象的表示。

![](https://cdn.luogu.com.cn/upload/image_hosting/j9hzo6rd.png)

我们在~~幼儿园~~小学的数学课上学过，求不重合的浅灰色面积可以用两个圆的面积减去两个中间重合的部分，但我们要的是 $x$ **或** $y$ 相等的点，所以我们只用减去一个重合部分就行了。

**代码**

```cpp
#include<bits/stdc++.h>
#define ll long long//不开long long见祖宗
using namespace std;
map<ll,ll> mp,mp1;//第一个ll是坐标，第二个是出现次数
map<pair<ll,ll>,ll> mp2;//第一个是点的xy坐标，第二个是出现次数
ll n,ans;
int main(){
    cin>>n;
    for(ll i=1;i<=n;++i){
        ll x,y;
        scanf("%d%d",&x,&y);
        ans+=mp[x]+mp1[y];//加上x坐标相同的点和y坐标相同的点，对应上图的左右圆
        ans-=mp2[make_pair(x,y)];//减去中间重合部分，也就是重复的点
        mp[x]++;//注意ans处理完再加
        mp1[y]++;
        mp2[make_pair(x,y)]++;make_pair(x,y)将x，y变为一个pair类型
    }
    cout<<ans;
    return 0;
}
```


---

## 作者：Dr_Gilbert (赞：1)

# CF650A Watchmen

【题目大意】

给出 $n$ 对坐标 $(x_i,y_i)$。求问曼哈顿距离和欧氏距离相等的坐标组 $(i,j)$（$1\leq i< j\leq n$）有多少对。

首先我们知道，曼哈顿距离 $D_{ij}=|x_i-x_j|+|y_i-y_j|$。而欧几里得距离 $d_{ij}=\sqrt{(x_i-x_j)^2+(y_i-y_j)^2}$。把这两个距离画在直角坐标系中，可以发现这两个距离恰好围成了一个直角三角形，曼哈顿距离就是直角三角形的直角边长之和，而欧几里得距离则为斜边边长。

题目要求求曼哈顿距离和欧氏距离相等的坐标组数量，我们知道在三角形中两边之和大于第三边，所以如果两点的曼哈顿距离和欧几里得距离围成了一个直角三角形，那么两个距离不可能相等。也就是说，如果两点的两种距离相等，那么这两点间的连线就必须和 $x$ 轴或 $y$ 轴平行。如果不好理解可以尝试把样例在坐标系里画出来。

所以只需要按 $x$ 坐标和 $y$ 坐标分别排序，找到每个 $x$ 坐标或 $y$ 坐标相同的段，假如某段共有 $k$ 个坐标相同的点，则这一段的贡献即为 $\dbinom{k}{2}$ 对。同时由于输入中有重复的点，这些点在按 $x$ 坐标和 $y$ 坐标排序时都会被计算一次，所以输入时可以用 `map` 记录出现次数，最后遍历 `map` 减去重复部分的答案即可。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
int cmpmode;
struct point{
	int x, y;
	bool operator <(const point& a) const {
		if (y!=a.y) return y<a.y;
		else return x<a.x;
	}
}p[N];
bool cmp(point a, point b){
	return a.x<b.x;
}
map<point,int> mp;
signed main(){
	int n,ans=0;cin>>n;
	for (int i=1;i<=n;i++){
		cin>>p[i].x>>p[i].y;
		if (mp.count(p[i])) mp[p[i]]++;
		else mp[p[i]]=1;
	}
	sort(p+1,p+n+1);
	int cnt=0;
	for (int i=1;i<=n;i++){
		if (p[i].y!=p[i-1].y){
			ans+=(cnt-1)*cnt/2;
			cnt=1;
		}else cnt++;
	}ans+=(cnt-1)*cnt/2;
	cmpmode=1;sort(p+1,p+1+n,cmp);
	cnt=0;
	for (int i=1;i<=n;i++){
		if (p[i].x!=p[i-1].x){
			ans+=(cnt-1)*cnt/2;
			cnt=1;
		}else cnt++;
	}ans+=(cnt-1)*cnt/2;
	for (auto x:mp){
		int cnt=x.second;
		ans-=cnt*(cnt-1)/2;
	}
	cout<<ans;return 0;
}
```



---

## 作者：_HiKou_ (赞：0)

简单水题（虽然 WA 了几次）

第一篇题解已经证明了当 $x_1=x_2$ 或 $y_1=y_2$ 时，这两个点的欧几里得距离等于曼哈顿距离。

我们可以使用 ```map``` 来统计相同的横纵坐标，再累加到答案中，但是注意每两个点之间会算两次所以答案要除以 $2$。

但是交完会发现答案错误，这是因为如果有多个点的坐标相同时，答案会算多。

比如下面这组数据：

```
3
1 1
1 1
1 1
```

如果按照我们的算法，程序会输出 $6$，但实际上答案为 $3$。对于重复的坐标，如果有 $m$ 组相同的点，那么会多算 $\dfrac{m \times (m-1)}{2}$ 次。

我们可以使用结构体排序来去重。

CODE：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n;
ll ans;
map<ll,ll> qx,qy;
struct node{
	ll x,y;
}a[214514];
bool cmp(node x,node y){//结构体排序
	if(x.x==y.x)return x.y<y.y;
	return x.x<y.x;
}
int main(){
	scanf("%lld",&n);
	for(ll i=1;i<=n;i++)scanf("%lld%lld",&a[i].x,&a[i].y),qx[a[i].x]++,qy[a[i].y]++;//统计相同横纵坐标
	sort(a+1,a+1+n,cmp);
	ll com=1;//去重，注意 1×(1-1)=0 对答案无影响
	for(ll i=1;i<=n;i++){
		ans+=qx[a[i].x]-1+qy[a[i].y]-1;
		if(a[i].x==a[i-1].x&&a[i].y==a[i-1].y&&i!=1)com++;//第一个不计算 否则会 WA #48
		else{
			ans-=com*(com-1);//在输出时再统一除以 2
			com=1;//重置
		}
	}
	ans-=com*(com-1);//别忘了要统计最后的
	printf("%lld",ans/2);
	return 0;
}
```

---

## 作者：XBaiC (赞：0)

先推一波公式。

$$|x2-x1|+|y2-y1|=\sqrt{(x2-x1)^2+(y2-y1)^2}$$

设

$$|x2-x1|=a$$

设

$$|y2-y1|=b$$

则

$$a+b=\sqrt{a^2+b^2}$$

$$(a+b)^2=a^2+b^2$$

$$a^2+2ab+b^2=a^2+b^2$$

$$2ab=0$$

$$ab=0$$

则

$$|x2-x1|\times|y2-y1|=0$$

$$|x2-x1|=0\:\:or\:\:|y2-y1|=0$$

$$x1=x2\:\:or\:\:y1=y2$$

### 思路

前置知识：容斥原理。

根据有 $x$ 坐标的个数加上有 $y$ 坐标的个数再减去整个点重复的个数。

之后用 `map` 就能水过去了。

### CODE

```cpp
#include<bits/stdc++.h>
using namespace std;
long long x[1000001] , y[1000001];
map<int , int> m1 , m2;
map<pair<int , int> , int> m3; 
int main()
{
    long long n;
    cin >> n;
    long long sum = 0; 
    for( int i = 1; i <= n; i++ )
    {
        cin >> x[i] >> y[i];
        sum = sum + m1[ x[i] ] + m2[ y[i] ] - m3[make_pair( x[i] , y[i] )];
        m1[x[i]]++;
        m2[y[i]]++;
        m3[make_pair( x[i] , y[i] )]++;
    }
    cout << sum; 
    return 0;
}
```


---

## 作者：sjr3065335594 (赞：0)

题意翻译已经很清楚了，我就不废话了。

## 思路

要让 $\left\vert x_i-x_j\right\vert+\left\vert y_i-y_j\right\vert$ 等于 $\sqrt{(x_i-x_j)^2+(y_i-y_j)^2}$，我们可以这样想：如果 $x_i=x_j$，那么这两个式子的值就取决于 $\left\vert y_i-y_j\right\vert$ 和 $\sqrt{(y_i-y_j)^2}$，后者其实就是 $\left\vert y_i-y_j\right\vert$，所以它们相等；当 $y_i=y_j$ 时同理。所以只要保证 $x_i=x_j$ 或者 $y_i=y_j$ 就可以累加答案了。

怎么累加答案呢？我们这样想：先用map存储每个横和纵坐标的出现次数，输入的 $x_i,y_i$ 对答案的贡献是  `mapx[x]+mapy[y]-mapp[make_pair(x,y)]` （意思就是这个横和纵坐标可以和之前每一个和他相同的凑成一对，最后再减去重复的就是答案）。

## 代码实现
```cpp
#include <bits/stdc++.h>
#define mkp(i,j) make_pair(i,j)
using namespace std;
int n;
map<int,int>mx,my;//存储x和y出现次数
map<pair<int,int>,int>mp;
long long ans;//不开long long见祖宗
int main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		int x,y;
		cin>>x>>y;
		ans+=mx[x]+my[y]-mp[mkp(x,y)];//统计答案
		mx[x]++;//将这个x出现次数加一
		my[y]++;//将这个y出现次数加一
		mp[mkp(x,y)]++;//将这个坐标出现次数加一
	}
	cout<<ans<<endl;
    return 0;//圆满结束
}
```


---

## 作者：Pursuing_OIer (赞：0)

## Solution
这道题用枚举复杂度较高，我们考虑探究当两点的曼哈顿距离与欧氏距离相等时，它们横纵坐标的关系。  
如下图所示，$MO$ 与 $ON$ 长度之和为 $M$ 和 $N$ 两点间的曼哈顿距离，$MN$ 的长度则为两点间的欧氏距离。此时，在 $Rt\bigtriangleup MON$ 中，$MO+ON>MN$，不符合题意。  

![](https://cdn.luogu.com.cn/upload/image_hosting/jckd3yeo.png)  

所以，当 $Rt\bigtriangleup MON$ 不存在，即 $MN$ 与坐标轴平行时，$MO+ON=MN$，此时，有 $M$ 与 $N$ 的横坐标或纵坐标相等。  
我们也可以通过两种距离的计算公式推出这个结论。  

设 $M(x_i,y_i)$，$N(x_j,y_j)$。  
当 $|x_i-x_j|+|y_i-y_j|=\sqrt{(x_i-x_j)^2+(y_i-y_j)^2}$ 时，  
等式两边平方，得 $(x_i-x_j)^2+2|x_i-x_j||y_i-y_j|+(y_i-y_j)^2=(x_i-x_j)^2+(y_i-y_j)^2$。  
移项，合并同类项得 $2|x_i-x_j||y_i-y_j|=0$。  
从而有 $|x_i-x_j|=0$ 或 $|y_i-y_j|=0$。  
即 $x_i=x_j$ 或 $y_i=y_j$，得证。  

所以，我们可以分别记录相同的横坐标出现的次数和相同的纵坐标出现的次数，若某个横坐标或纵坐标出现了 $k$ 次，那么每两次都可以组成一对，总数应加上 $C_{k}^{2}=\frac{k!}{2!(k-2)!}=\frac{k(k-1)}{2}$。  
但通过阅读样例 $2$，可以发现有相同的点出现，导致我们在累加时将横纵坐标都相等的这些点计了两次，需要排掉一次。设对于某个位置上有 $q$ 个这样的点，我们应该减去一次这些点两两组合成的坐标组数，即减去 $C_{q}^{2}=\frac{q!}{2!(q-2)!}=\frac{q(q-1)}{2}$。 

## Code
通过三个映射表分别维护每个横坐标出现次数，每个纵坐标出现次数和每个位置上的重点数。  
注意开 `long long`！

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,ans;
map<long long,long long> xeql,yeql;
map<pair<long long,long long>,long long> alleql;
long long f(long long x){
	return (x*(x-1))/2;
}
int main(){
	long long temx,temy;
	scanf("%lld",&n);
	for(int i=1;i<=n;++i){
		scanf("%lld%lld",&temx,&temy);
		++xeql[temx];
		++yeql[temy];
		++alleql[{temx,temy}];
	}
	map<long long,long long>::iterator iter1;
	map<pair<long long,long long>,long long>::iterator iter2; 
	for(iter1=xeql.begin();iter1!=xeql.end();++iter1){
		ans+=f(iter1->second);
	}
	for(iter1=yeql.begin();iter1!=yeql.end();++iter1){
		ans+=f(iter1->second);
	}
	for(iter2=alleql.begin();iter2!=alleql.end();++iter2){
		ans-=f(iter2->second);
	}
    printf("%lld",ans);
}
```

---

