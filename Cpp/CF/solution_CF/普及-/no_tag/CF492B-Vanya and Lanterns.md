# Vanya and Lanterns

## 题目描述

Vanya walks late at night along a straight street of length $ l $ , lit by $ n $ lanterns. Consider the coordinate system with the beginning of the street corresponding to the point $ 0 $ , and its end corresponding to the point $ l $ . Then the $ i $ -th lantern is at the point $ a_{i} $ . The lantern lights all points of the street that are at the distance of at most $ d $ from it, where $ d $ is some positive number, common for all lanterns.

Vanya wonders: what is the minimum light radius $ d $ should the lanterns have to light the whole street?

## 说明/提示

Vanya walks late at night along a straight street of length $ l $ , lit by $ n $ lanterns. Consider the coordinate system with the beginning of the street corresponding to the point $ 0 $ , and its end corresponding to the point $ l $ . Then the $ i $ -th lantern is at the point $ a_{i} $ . The lantern lights all points of the street that are at the distance of at most $ d $ from it, where $ d $ is some positive number, common for all lanterns.

Vanya wonders: what is the minimum light radius $ d $ should the lanterns have to light the whole street?

## 样例 #1

### 输入

```
7 15
15 5 3 7 9 14 0
```

### 输出

```
2.5000000000
```

## 样例 #2

### 输入

```
2 5
2 5
```

### 输出

```
2.0000000000
```

# 题解

## 作者：封禁用户 (赞：5)

题目传送>>[CF492B](https://www.luogu.com.cn/problem/CF492B)  
### 题意简述:  
- 一长度为 $L(0-L)$ 的街道上有 $n$ 个相同的灯，第 $i$ 个灯的位置是 $a_i$ ，求能照亮整个街道，灯的最小半径。  
- $n\le1000$，$L\le10^9$。  
  
### 题目分析：  
要照亮整个街道，即要使灯的光亮遍布 $0-L$，不能有间断。而两灯之间的地方可由来自其最近两端的灯分别从该端向中间照射，所以其两端的灯的半径至少要大于等于它们之间距离的一半，所以我们需贪心求出该街道所放置的灯两两之间的距离的最大值。但是值得注意的是，靠近街头和街尾的灯并不一定就放置在起始处和尽头处，所以靠近街头和街尾的灯还需能够照亮至起始处和尽头处。  
综上，我们只需对靠近街头的灯到起始处的距离、街道上的灯两两之间距离的最大值的一半、靠近街尾的灯到尽头处的距离进行比较，其最大值即问题的解。  
### Code：  
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>   //sort排序含于此
#include<iomanip>   //输出位数控制含于此
using namespace std;
double a[1001];   //开数组存每个灯的位置
int main()
{
	//freopen("input.in","r",stdin);
	//freopen("print.out","w",stdout);
	ios::sync_with_stdio(0);   //关同步加速cin输入和cout输出
	int n;   //定义灯的个数
	double l,r;   //定义街道的长度，灯所需的最小半径
	cin>>n>>l;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}	
	sort(a+1,a+1+n);   //对灯的位置进行排序
	r=max(a[1],l-a[n]);   //率先求出靠近街头的灯到起始处的距离和靠近街尾的灯到尽头处的距离的最大值
	for(int i=1;i<n;i++)   //注意此处i是小于n
	{
		r=max(r,(a[i+1]-a[i])/2);   //与街道上的灯两两之间距离的最大值的一半进行最大值比较，不断更新灯所需的最小半径
	}
	cout<<fixed<<setprecision(10)<<r;   //控制输出结果为题目要求的10位小数
	return 0;   //结束整个程序
}
```
### 结果（未吸氧）:  
![JieGuo](https://cdn.luogu.com.cn/upload/image_hosting/dnl7aqoj.png)  
企鹅的题解到此结束，祝各位 OIers 进步 ++~

---

## 作者：伟大的王夫子 (赞：2)

这题并不是一道难题，只需耐心思考，耐心分析即可。

先排序，排序不亏

首先在中间的路灯要想覆盖相邻两个路灯之间的区域$[a_i, a_{i + 1}]$

半径$r$必须小于$\dfrac{a_{i +1} - a_i}{2}$

边界上的路灯$1,n$想要覆盖周围的区域，半径必须要大于$\max(a_1, L-a_n)$

所以$ans={\max \limits_{2 \le i\le n}{\dfrac{a_i - a_{i - 1}}{2}}}$ 与 $\max({a_1, L-a_n})$中较大者。

因为我们已经排了序，所以我们顺序扫描

实现程序如下

记得开double并保留10位小数

```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
double a[1010], L, ans;
int main() {
	cin >> n >> L;
	for (register int i = 1; i <= n; ++i) cin >> a[i];
	sort(a + 1, a + n + 1);
	ans = max(a[1], L - a[n]);
	for (register int i = 2; i <= n; ++i) ans = max(ans, (a[i] - a[i - 1]) / 2);
	printf("%.10lf", ans);
}
```

---

## 作者：Eason_AC (赞：2)

## Content
一条长为 $L$ 的街道上有 $n$ 盏灯，第 $i$ 盏灯的位置为 $a_i$。求灯的半径⾄少要是多少，才能使得整个街道都有灯光。

**数据范围：$n\leqslant 1000,L\leqslant 10^9$。**
## Solution
我们得要先求出哪一段的距离最大。

实在不好用文字解释，就画个图为例子讲下吧：

![](https://cdn.luogu.com.cn/upload/image_hosting/xd88wpyi.png)

把图中的四个灯从左往右编号为 $1,2,3,4$。然后我们要求的距离就是下面用五彩斑斓的颜色区分的几条线段：

![](https://cdn.luogu.com.cn/upload/image_hosting/9g1z2cw0.png)

特别注意 $0$ 到第一盏灯的距离和最后一盏灯到 $L$ 的距离，由于它们旁边只有 $1$ 盏灯，需要单独拿出来判断。
## Code
```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <iostream>
using namespace std;

int n, l, a[100007], ans;

int main() {
	scanf("%d%d", &n, &l);
	for(int i = 1; i <= n; ++i)	scanf("%d", &a[i]);
	sort(a + 1, a + n + 1);
	for(int i = 2; i <= n; ++i)
		ans = max(ans, a[i] - a[i - 1]);
	return printf("%.8lf", max(ans / 2.0, max((double)a[1], (double)(l - a[n])))), 0;	
}
```

---

## 作者：smyslenny (赞：1)

思路：**贪心**

- 所求的路灯的最大半径为路灯之间距离一半的最大距离。所以只要挨个求出每个路灯间的距离，求一个max即可。

```c
ans=max(double(sz[i+1]-sz[i])/2,ans);
```
- 但是
需要注意的是，路灯除了要考虑它们之间的距离之外，还需考虑两头的路灯与街道两端的距离。而此时的半径即为距离，不用再除以二。所以我们还要再处理一下边界问题。


于是，我们得出了一份完美的AC代码。


```c
#include<bits/stdc++.h>
using namespace std;
int m,n;
int sz[1005];
inline int read(){//快读
	char ch=getchar();
	int x=0,f=1;
	while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') x=x*10+(ch^48),ch=getchar();
	return x*f;
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		sz[i]=read();
	}
	sort(sz+1,sz+n+1);//确定每个路灯的位置
	double ans;
	for(int i=1;i<=n;i++)
	{
		if(i==1)
		{
			ans=max(double(sz[i]-0),ans);
		}//处理边界问题
		if(i==n)
		{
			ans=max(double(m-sz[i]),ans);
		}
		else
		ans=max(double(sz[i+1]-sz[i])/2,ans);
	}
	printf("%.10lf",ans);//完结撒花
	return 0;
}
```


---

## 作者：KEBrantily (赞：1)

**题意**

一条长为L的路，在n个不同的位置都放置了路灯，灯光半径相同，问半径至少为多少时灯光可以覆盖整条路。

那我们就先排序，使灯的位置是从路的一边依次排到另一边的
，然后求出两两挨着的灯之间距离的**最大值**，因为灯光半径相等，所以两盏灯之间的距离就是**两盏灯灯光的半径之和**（也就是一盏灯灯光的直径），就把这个值除以二记录下来。

然后，因为要求整个道路全部被灯光覆盖，所以把刚刚记录的那个值与路最两端的灯到路两端的距离做比较取最大值（因为**路的两段不会发光**，所以覆盖这两段的只能是最边上的灯的半径，因此**不用再把这个值除以二**）

最后代码

```cpp
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<algorithm>
#define maxn 100010

using namespace std;

int main(){
	int n;
	double l,a[10010];
	double w=0;
	cin>>n>>l;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	a[n+1]=l;
	a[0]=0;
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++){
		w=max(w,a[i]-a[i-1]);
	}
	w=max(a[1],w/2);
	w=max(l-a[n],w);
	printf("%.9lf",w);
	return 0;
}
```


---

## 作者：YONIC (赞：0)

# [CF492B Vanya and Lanterns](https://www.luogu.com.cn/problem/CF492B)
本题不是一道难题。

试想一下，我们每两个灯笼之间，都有一块黑暗的地方，这块黑暗需要被灯光完全覆盖的话，就需要两头的灯来照射，由于每一盏灯的功率与照射半径是相同的，所以它们的“势力范围”就至少要达到这一块黑暗的中点。

简单直观。

但是有一个重要的坑：灯笼两头到坐标 $0$ 与坐标 $L$ 之间是没有灯笼的，而灯光要想到这两头只能靠最左边或最右边的灯笼来照射，其间范围之外没有灯，所以这两段长度并不能像我们平常处理的那样除以二，需要特判。

知道了这两点，这道题目你就基本上做完了。

Code:
```
#include<bits/stdc++.h>
using namespace std;
int n;
double l,r,d[1003];
int main(){
	scanf("%d%lf",&n,&l);
	for(int i=1;i<=n;++i) scanf("%lf",d+i);
	sort(d+1,d+1+n);
	r=max(d[1],l-d[n]);
	for(int i=1;i<n;++i) r=max(r,(d[i+1]-d[i])/2);
	printf("%.10lf",r);
	return 0;
}
```
请管理大大手下留情（

---

## 作者：ytcccf (赞：0)

### 题意简述

长为 $L$ 的街道上有 $n$ 盏灯，给出 $n$ 盏灯的坐标，求出灯光照射范围半径的最小值，使得 $0\sim L$ 的每个位置都被灯光照得到。

### 题目分析

题目难度：普及-

$\text{AC code}$ 时间复杂度为 $\Theta(n\log n)$


### 解题思路 

仔细思考后发现此题难度不高，求得其实就是距离最远的相邻的两个路灯之间距离的一半，写完，$\text{WA}$ 警告！

原因是因为没有计算开头和结尾处，请注意，开头和结尾处没有路灯，所以计算时不需要除以 $2$ ，在之后单独处理即可，于是此题被我们愉快的解决了。

### AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	ios::sync_with_stdio(false);//cin、cout优化 
	int n,l;
	int a[1010];
	cin>>n>>l;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	sort(a+1,a+n+1);//把灯的位置排个序，方便处理 
	double ans=-1;
	for(int i=1;i<=n-1;i++)
	{
		ans=max(ans,(a[i+1]-a[i])*0.5);
	}
	ans=max(ans,(double)max(a[1],l-a[n]));//别忘了计算开头和结尾 
	printf("%.10lf\n",ans);//要求精度为1e-9，所以保留10位小数 
	return 0;//完结撒花~ 
}
```

---

## 作者：Zxsoul (赞：0)

# Sort 排序+ （double） 与 （int） 转换 + 模拟
### 题面 ：

• 一个长为 L 的街道（左端点是 0，右端点是 L）上有 n 个相同的灯，第 i 个灯放置的位置是 ai

• 问灯的半径至少要是多少，才能使得整个街道都有灯光。

• n <= 1000, L <= 10^9

## 思路：
1. 首先需要理解题意：想要整个街道都有灯光的含义就是——**灯与灯之间和灯与边界都必须要明亮。**
1. 所以我们思考的方向就是如何使光路半径最小的灯满足要求 

## 做法 :
- 将灯的位置按从大到小排序
- 判断灯与灯之间的距离（相当于一灯个的直径）（只有最大值可以满足所有灯之间的明亮）
- 完成上步得到最大值后，再与两边界相邻最近灯的距离进行比较（此时相当于比较灯的半径）
- 等到的最值即为所求（也有一点贪心的感觉）		
        
## 请看 Code
```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<cctype>
#include<cmath>
#include<set>
#include<map>
#include<queue>
#include<vector>
using namespace std;
const int manx = 50009;
typedef long long LL;
long long   n,m,a[manx];//数组过大MLE，本蒟蒻亲身经历过 
long long   qwq;//没有名字可想 
double w;//答案最后要求输出小数点后10位，需要开double 
int main(){
	cin >> n >> m;
	for (int i = 1; i <= n; i++){
		cin>> a[i];
	}
	sort(a + 1, a + 1 + n);//灯排序 
	for (int i = 1; i <= n; i++){
		qwq = max(qwq,a[i]-a[i-1]);
		//比较出最大光路直径，记住是直径 
	}
	w = qwq; //数据类型转换，因为下面比较半径，所以需要double / 2; 
	w = w / 2; 
	if(a[1] > w)//两边界距最近灯距离问题 
		w = (double)a[1];//强制类型转换 
	if(m - a[n] > w)
		w = (double)m - a[n];//强制类型转换 
	printf("%.10lf",w);//printf .10 霸气收场（其实刚开始我把.10写成10,变成首行缩进）希望大家不要犯我这种低级错误
	return 0; 
}
```
# 感谢观看~

---

## 作者：Histone (赞：0)

水题WA了n次，自信心--

### 思路：

很简单的贪心，两两相邻路灯间的最大距离就是每个路灯最大照射范围的二倍。

将n个路灯排序后，从 $[ 1 , n )$ 取第 $i+1$ 和第 $i$ 个的间距 $dx \div 2$ ，**特别地**，还要计算第一个和最后一个路灯照射边界的情况。

### 注意事项：

- 输出注意精度，C++可以用 `printf("%.10lf",ans)` 控制精度

- 边界处理

~~PS：蒟蒻的我因为边界与路灯的距离也除了2，导致WA好多次，大家引以为戒~~

代码很简单

```cpp
#include<bits/stdc++.h>
#define re register
using namespace std;
inline int read(){
	re int ans = 0;re bool f = 1;re char ch = getchar();
	while(ch<'0'||ch>'9'){if (ch=='-')f = 0;ch = getchar();}
	while(ch>='0'&&ch<='9'){
		ans = (ans<<3)+(ans<<1)+(ch^48);
		ch = getchar();
	}
	return f?ans:~(ans-1);
}
int num[2048];
signed main(void){
	double ans = 0;
	int n = read(),len = read();
	for(re int i=1;i<=n;++i)
		num[i] = read();
	sort(num+1,num+n+1);
	for(re int i=1;i<n;++i)
		ans = max(ans,(double)(num[i+1]-num[i])/2.0);
	ans = max((double)len-num[n],max(ans,(double)num[1]-0));//判断边界情况
	printf("%.10lf\n",ans);
	return 0;
}
```


---

## 作者：Create_Random (赞：0)

蒟蒻思路：

贪心。

要求灯的半径最小。

就是求每两个相邻灯之间距离一半的最大值。

但要注意判断边界。

(第一盏灯和最后一盏灯必须照到路的两端)

贴代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,l;
double a[1010];
double ans;
int main()
{
	cin>>n>>l;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	sort(a+1,a+n+1);
//      a[0]=0;
	a[n+1]=l;//标注路的两端
	for(int i=1;i<=n+1;i++)
	{
		if(i==1||i==n+1)
		{
			ans=max(ans,a[i]-a[i-1]);//如果是第1盏或最后一盏就要照到路的边界。
		}
		else
		{
			ans=max(ans,(a[i]-a[i-1])/2);//否则就找相邻两盏灯之间最大值的一半。
		}
		
	}
	printf("%.10lf",ans);
	return 0;
}
```


---

