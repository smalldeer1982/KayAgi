# Tell Your World

## 题目描述

题意

用线连接无数的点，直到我们到达远方。
坐标平面上有$n$ 个点，第$i$ 个点的坐标为$(i,y_{i})$ 。
确定是否能画两条平行且不重叠的线，使得集合中的每个点都在他们之中的一条线上，且每条线至少经过一个点。

## 样例 #1

### 输入

```
5
7 5 8 6 9
```

### 输出

```
Yes
```

## 样例 #2

### 输入

```
5
-1 -2 0 0 -5
```

### 输出

```
No
```

## 样例 #3

### 输入

```
5
5 4 3 2 1
```

### 输出

```
No
```

## 样例 #4

### 输入

```
5
1000000000 0 0 0 0
```

### 输出

```
Yes
```

# 题解

## 作者：是个汉子 (赞：2)

### Solution

我们可以想到构造三条基准线： $k_{1,2},k_{2,3},k_{1,3}$ ，分别以 $a_1,a_2$ ，$a_2,a_3$ 和 $a_1,a_3$ 为线上的点，然后去判断剩下的点是否是在另一条与**某一条**基准线平行的线上。

### 代码

```c++
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;
const int N=1010;
double a[N];
int n;

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(!isdigit(ch)){if(ch=='-') f=-1;ch=getchar();}
    while(isdigit(ch)){x=x*10+(ch^48);ch=getchar();}
    return x*f;
}

inline int solve(double k){
    int flag=0,point=-1;
    for(int i=2;i<=n;i++){
        if(a[i]-a[1]==k*(i-1)) continue;//可能这条平行线有1
        flag=1;
        if(point<0) point=i;//没有1就记录点
        else if(a[i]-a[point]!=k*(i-point)){
            flag=0;//还不行就真不行了
            break;
        }
    }
    if(flag==1) return 1;
    else return 0;
}

int main(){
    n=read();
    for(int i=1;i<=n;i++)
        a[i]=read();
    double k1=a[2]-a[1],k2=a[3]-a[2],k3=(a[3]-a[1])/2;
    if(solve(k1)||solve(k2)||solve(k3)) puts("Yes");
    else puts("No");
    return 0;
}
```



---

## 作者：_lxy_ (赞：1)

### 题意
平面上有 $n$ 个点，第 $i$ 个点的坐标是 $( i , y[ i ] ) $ 。问是否能找到两条不重合的平行线，使这 $n$ 个点都在这两条平行线上。

### 分析
两点确定一条直线，再加一个点就能确定一对平行线。只需选前三个点中的任意 $2$ 个点，形成 $3$ 条直线，再枚举剩下的点是否在这条直线上或在它的同一条平行线上。

### 代码
```cpp
#include <bits/stdc++.h>
#define elif else if
using namespace std;
int T,n;
vector<int>y;
bool check(double k)
{
    bool flag=false;
    int x=-1;
    for(int i=2;i<=n;i++)
    {
        if(y[i]-y[1]==k*(i-1)) continue; // 在这条直线上
        flag=true;
        if(x==-1) x=i; // 如果之前没有点在这条直线的平行线上，就记录这个点
        elif((y[i]-y[x])!=k*(i-x)) // 这个点既不在这条直线上，也不在它的平行线上
        {
            flag=false;
            break;
        }
    }
    return flag;
}
int main()
{
    scanf("%d",&n);
    int i,j;
    y.push_back(0);
    for(i=0;i<n;i++)
    {
        int x;
        scanf("%d",&x);
        y.push_back(x);
    }
    double a1=double(y[2]-y[1]); // 分别计算3条直线的斜率
    double a2=double((y[3]-y[1])*0.5);
    double a3=double(y[3]-y[2]);
    if(check(a1)||check(a2)||check(a3)) // 分别枚举三条直线
    {
        printf("Yes\n");
    }
    else printf("No\n");
    return 0;
}
```


---

## 作者：joker_opof_qaq (赞：0)

## 题意

在同一平面内有 $n$ 个点，第 $i$ 个点的坐标是 $(i,y_i)$。能否用这 $n$ 个点构成两条平行线。

## 分析

先任意选取 $3$ 个点，这三个点必定有一条线，枚举哪两个点构成直线，再根据过一点有且仅有一条直线与已知直线平行，去求出直线斜率，再去算没给点是否在这两条直线上即可。

## code

```cpp

#include<iostream>
#include<algorithm>
#include<cstdio>
#include<iomanip>
#include<cstring>
#include<string>
#include<cmath>
#include<queue>
#include<map>
#include<list>
#include<stack>
#include<cctype>
#include<cstdlib>
#include<utility>
#include<set>
#include<bitset>
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+ch-48;ch=getchar();}
	return x*f;
}
inline void write(int x) {
	if (x<0)x=-x,putchar('-');
	if (x>9)write(x/10);
	putchar(x%10+'0');
}
inline int solve(double k){
	int flag=0,point=-1;
	for(int i=2;i<=n;i++){
		if(a[i]-a[1]==k*(i-1))continue;
		flag=1;
		if(point<0)point=i;
    	else if(a[i]-a[point]!=k*(i-point)){
			flag=0;
			break;
		}
	}
	if(flag==1)return 1;
	else return 0;
}
int main(){
	int n=read();
	for(int i=1;i<=n;i++){
		y[i]=read();
		x[i]=i; 
	}
	for(int i=1;i<=n;i++){
		for(int j=1;i+1;j<=n;j++){
			if(solve(a[j]-a[i])){
				puts("Yes");
				return 0;
			}
		}
	} 
	puts("No");
	return 0;
}

```

---

## 作者：smartdevil (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF849B)
## 题意：

平面上有 $n$ 个点，第 $i$ 个点的坐标是 $(i,y_i)$ 。问能不能找到两条平行线覆盖所有 $n$ 个点。

## 分析：
分类讨论，1 号点和 $2 \sim n$ 号点分别组直线，不在这条直线上的，判断在不在另一条直线上，并判断两条直线是否平行。

如果不行，就是 1 号点单独一条线，判断其他点是否在同一直线上，复杂度 $O(n^2)$。

---

## 作者：skyskyCCC (赞：0)

## 前言。
思维题，加上一点点的平面几何分析。

本片题解默认读者了解[斜率](https://baike.baidu.com/item/%E6%96%9C%E7%8E%87/4914111)及一次函数。
## 分析。
考虑建立平面直角坐标系。两个在此坐标系中的平行的直线，其斜率一定相等，所以我们可以先算出两条直线的斜率 $k$ 然后求解。很显然，我们我们可以将这两条直线的最左下的点作为基准点，检验其他点和基准点之间的斜率是否为 $k$ 即可。即去查找其他点是否在这条斜率为 $k$ 的直线上。

那么我们现在的问题就来到了如何求 $k$ 这个问题上。最暴力的做法就是枚举点，然后将每个点 $y_i$ 同其它点的 $y_j$ 计算斜率，明显复杂度极高。考虑优化。

考虑到两点确定一条直线，过直线外一点有且仅有一条直线与已知直线平行，所以找到两个点再加一个点就能确定一对平行线。所以我们可以用数据的前三个数构造三条直线。我们可以先去分别枚举第一个点与第二个点、第三个点之间的斜率分别为 $k1$ 与 $k2$ 的结果。如果与真正的斜率**不同**，则第一个点与第二个点**不在**同一直线上，与第三个点**也不在**同一直线上。那此时必定第二、三点在一条直线上。既然这样，我们可以再算出斜率 $k3$ 即第二、第三个点组成的直线的斜率。真正的斜率一定是这三个里的一个。然后其它点对应到斜率上，看看是否在同一线上即可。

对于怎么确定点是否在直线上，我们就是套一次函数即可。

代码如下，仅供参考：
```
#include<iostream>
using namespace std;
double n,y[1005];
bool pd(double xl){
	int fg=0,i2;//定义一个判断值。
	for(int i=2;i<=n;i++){
		if((y[i]-y[1])==xl*(i-1)){
		    continue;
		}
		if(!fg){
			fg=1;
			i2=i;
		}
		else{
			if((y[i]-y[i2])!=xl*(i-i2)){
				fg=0;
				break;
			}
		}
	}
	if(!fg){
	    return false;
	}
	else return true;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>y[i];
	}
	double k1=y[2]-y[1],k2=(y[3]-y[1])/2.0,k3=(y[3]-y[2]);//其实这里的/2.0可以换成/2但是为了精度还是保留。
	if(pd(k1)||pd(k2)||pd(k3)){
	    cout<<"Yes\n";
	    return 0;
	}
	cout<<"No\n";
	return 0;
}
```
## 后记。
大家如有疑问，可以在评论区提出，我会尽力解答的。

---

## 作者：泠小毒 (赞：0)

# Tell Your World

给定一堆点，问这堆点能否构成两条平行的直线，每条直线至少过一个点，所有的点都在直线上

## 广告插入

在我的博客里看题解使用效果更佳哦QwQ

[慕容琳的后花园](https://muronglin.top/hgoi-20190429/)

## 解法

分类讨论，1号点和2~n号点组一条直线，对于不在这条直线上的点，判断是否在另一条直线上，并判断是否平行

如果不行，就是1号点单独一条线，判断剩余的点是否在同一直线上，细节有点多，复杂度是n方

## ac代码
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{int x,y;}p[1010];
int n,cnt,a[1010],fg,flg;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=2;i<=n;i++)
	{
		cnt=0,fg=1;
		for(int j=2;j<=n;j++)
			if((a[i]-a[1])*(j-1)!=(a[j]-a[1])*(i-1))
				p[++cnt]={j,a[j]};
		if(cnt==0)continue;
		if(cnt==1){flg=1;break;}
		if((a[i]-a[1])*(p[2].x-p[1].x)!=(p[2].y-p[1].y)*(i-1))continue;
		for(int j=3;j<=cnt;j++)
			if((p[2].y-p[1].y)*(p[j].x-p[1].x)!=(p[j].y-p[1].y)*(p[2].x-p[1].x))
				{fg=0;break;}
		if(fg){flg=1;break;}
	}
	fg=1;
	for(int i=4;i<=n;i++)
		if((a[3]-a[2])*(i-2)!=(a[i]-a[2])*(3-2))
			{fg=0;break;}
	if((a[3]-a[2])*(3-1)==(a[3]-a[1])*(2-1))fg=0;
	if(flg||fg)puts("Yes");
	else puts("No");
	return 0;
}
```

---

