# [USACO20FEB] Triangles B

## 题目描述

Farmer John 想要给他的奶牛们建造一个三角形牧场。

有 $N$（$3\le N\le 100$）个栅栏柱子分别位于农场的二维平面上不同的点 $(X_1,Y_1)\ldots(X_N,Y_N)$。他可以选择其中三个点组成三角形牧场，只要三角形有一条边与 $x$ 轴平行，且有另一条边与 $y$ 轴平行。

Farmer John 可以围成的牧场的最大面积是多少？保证存在至少一个合法的三角形牧场。 

## 说明/提示

### 样例解释 1

位于点 $(0,0)$、$(1,0)$ 和 $(1,2)$ 的木桩组成了一个面积为 $1$ 的三角形。所以，答案为 $2\cdot 1=2$。只有一个其他的三角形，面积为 $0.5$。

## 样例 #1

### 输入

```
4
0 0
0 1
1 0
1 2```

### 输出

```
2```

# 题解

## 作者：zhouchuer (赞：3)

## [题目传送门](https://www.luogu.com.cn/problem/P9949)
update on 2024/12/1：修改了一处笔误，望管理通过。
### 思路
观察一下数据范围，发现 $n$ 比较小，可以直接暴力，时间复杂度为 $O(n^3)$。直接暴力枚举三个点，然后用三角形面积公式求三角形面积，那么这里注意，题目让你输出乘 $2$ 后的结果，这就和它本身要除以 $2$ 抵消了。所以比较的时候就可以直接把三角形面积乘 $2$ 的结果进行比较，因为小数实在太容易错了。所以我们在比较的时候找出更大的值就马上更新，最后输出答案，这一题就通过了。

### 代码
```c
#include<bits/stdc++.h>
using namespace std;

int s[110],c[110],ans;
int main(){
    int n;
    cin>>n;
    for(int i=1;i<=n;i++) cin>>s[i]>>c[i];
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            for(int k=1;k<=n;k++){
                if(s[i]==s[k]&&c[i]==c[j]) ans=max(ans,abs(s[i]-s[j])*abs(c[i]-c[k]));      
                else if(s[i]==s[j]&&c[i]==c[k]) ans=max(ans,abs(s[i]-s[k])*abs(c[i]-c[j]));
				else continue;                      
            }
        }
    }
    cout<<ans;
    return 0;
} 
```
这是通过记录：[已通过](https://www.luogu.com.cn/record/158061754)。

---

## 作者：Cute__yhb (赞：3)

## 思路
首先，肯定可以 $O(n^{3})$ 暴力枚举，考虑优化。

要知道，如果与 $x$ 轴和 $y$ 轴均平行，那么有两个点 $x$ 坐标相等，有两个 $y$ 坐标相等。

三角形的一条边长为 $x$ 坐标相等的两个点 $y$ 坐标之差的绝对值，另一条边长为 $y$ 坐标相等的两个点 $x$ 坐标之差的绝对值。

要想要面积最大，可以让三角形的两条边分别最大，时间复杂度降了一维。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int x[105],y[105],n,maxx=0,xmax[105],ymax[105];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>x[i]>>y[i];
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(i==j) continue;
			if(x[i]==x[j]) xmax[i]=max(xmax[i],abs(y[i]-y[j]));//一条最大
			if(y[i]==y[j]) ymax[i]=max(ymax[i],abs(x[i]-x[j]));//另一条
		}
	}
	int maxx=0;
	for(int i=1;i<=n;i++) maxx=max(maxx,xmax[i]*ymax[i]);//求最大值
	cout<<maxx;
    return 0;
}
```


---

## 作者：Eason_cyx (赞：2)

一种很优的 $O(n)$ 解法，但是思路大致相同。

输出时记录四个数组：横坐标为 $i$ 的所有点中纵坐标最大值，横坐标为 $i$ 的所有点中纵坐标最小值，纵坐标为 $i$ 的所有点中横坐标最大值，纵坐标为 $i$ 的所有点中横坐标最小值。对于每一个点，选择 $x$ 轴离它最远的和 $y$ 轴离它最远的组成三角形即可。编写代码时需要区分好四个数组。

```cpp
#include <bits/stdc++.h>
using namespace std;
int maxx[20005],minx[20005],maxy[20005],miny[20005],X[105],Y[105];
//例：maxx[i]表示所有(i,?)的点中?最大的
//例：miny[i]表示所有(?,i)的点中?最小的
int main() {
    memset(maxx,-0x3f,sizeof maxx);
    memset(minx,0x3f,sizeof minx);
    memset(maxy,-0x3f,sizeof maxy);
    memset(miny,0x3f,sizeof miny);
    int n; cin >> n;
    for(int i = 1;i <= n;i++) {
        cin >> X[i] >> Y[i];
        X[i] += 10000; Y[i] += 10000; //负数处理，防止越界
        maxx[X[i]] = max(maxx[X[i]],Y[i]);
        minx[X[i]] = min(minx[X[i]],Y[i]);
        maxy[Y[i]] = max(maxy[Y[i]],X[i]);
        miny[Y[i]] = min(miny[Y[i]],X[i]);
    }
    int ans = 0;
    for(int i = 1;i <= n;i++) {
        int mxdis_x = max(abs(X[i]-miny[Y[i]]),abs(maxy[Y[i]]-X[i]));
        int mxdis_y = max(abs(Y[i]-minx[X[i]]),abs(maxx[X[i]]-Y[i]));
        ans = max(ans,mxdis_x * mxdis_y);
    }
    cout << ans << endl;
    return 0;
}
```

---

## 作者：Pyrf_uqcat (赞：2)

主要讲一下思路，题目的关键点在于 $N \le 100$，数据小，所以解法就是**枚举**。

那应该怎么枚举呢？最后求的是最大三角形面积，而三角形有三个点，那就直接**三层循环**，**枚举每一个点**。每一个三角形都判断是否有一条边与 $x$ 轴平行且有一条边与 $y$ 轴平行，如果有则记录答案，最后要输出最大值。

### 代码
```cpp
//P9949 [USACO20FEB] Triangles B
#include <bits/stdc++.h>//万能头文件
using namespace std;
int a[105],b[105];//定义x和y
int ans;//存答案
int main() {
	int n;cin>>n;//输入n
	for(int i=1;i<=n;i++) cin>>a[i]>>b[i];//输入点的坐标
	for(int i=1;i<=n;i++) {//枚举第一个点
		for(int j=i+1;j<=n;j++) {//枚举第二个点,j=i+1防止重复
			for(int k=j+1;k<=n;k++) {//枚举第三个点,k=j+1防止重复
				//六种情况判断
				if(a[i]==a[j]&&b[i]==b[k]) ans=max(ans,abs(b[i]-b[j])*abs(a[i]-a[k]));//xi=xj且yi=yk
				else if(a[i]==a[j]&&b[j]==b[k]) ans=max(ans,abs(b[i]-b[j])*abs(a[j]-a[k]));//xi=xj且yj=yk
				else if(a[i]==a[k]&&b[i]==b[j]) ans=max(ans,abs(b[k]-b[i])*abs(a[j]-a[i]));//xi=xk且yj=yi
				else if(a[i]==a[k]&&b[j]==b[k]) ans=max(ans,abs(b[k]-b[i])*abs(a[j]-a[k]));//xi=xk且yj=yk
				else if(a[j]==a[k]&&b[j]==b[i]) ans=max(ans,abs(b[k]-b[j])*abs(a[j]-a[i]));//xk=xj且yj=yi
				else if(a[j]==a[k]&&b[i]==b[k]) ans=max(ans,abs(b[k]-b[j])*abs(a[i]-a[k]));//xk=xj且yi=yk
				else continue;//不满足条件，这句也可以没有
			}
		}
	}
	cout<<ans<<endl;//输出答案
	return 0;//完结，撒花！
}
```

---

## 作者：Awatesolo (赞：1)

* 逆天暴力水题，感觉难度应变为红。
* 由于 $n \le 100$，$O(n^3)$ 的时间复杂度即可。
* 枚举 $3$ 个点后先判断是否有 $2$ 条横平竖直的边即可。
```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m;
template<typename T>
inline void read(T &x) {
    x = 0;
    register char c = getchar();
    register short f = 1;
    while (c < '0' || c > '9') {
        if (c == '-') f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9') {
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }
    x *= f;
}
template <typename T, typename... Args>
inline void read(T &x, Args &...temps)
{
	read(x), read(temps...);
}
int x[105],y[105];
signed main(){
	read(n);
	for(int i=1;i<=n;i++) read(x[i],y[i]);
	int ans=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			for(int k=1;k<=n;k++){
				if(x[i]==x[j]&&y[i]==y[k]){
					ans=max(ans,abs(x[i]-x[k])*abs(y[i]-y[j]));//由于不知道谁在左谁在右谁上谁下，因此用绝对值
				}
				if(x[i]==x[k]&&y[i]==y[j]){
					ans=max(ans,abs(x[i]-x[j])*abs(y[i]-y[k]));
				}
			}
		}
	}
	cout<<ans;
	return 0;
}

---

## 作者：_Deer_Peach_ (赞：1)

### 题意简述：
给出 $n$ 个点的 $x$ 和 $y$ 坐标，从中选取 $3$ 个点求出最大的三角形面积。

### 思路：
由于 $n$ 的数据范围很小，所以可以直接进行三重循环的暴力。先枚举出三个点的坐标，再求出这三个点围成的三角形面积，比较大小。注意：算出的答案需要乘以二。

### 可能可以用到的公式：
求两个点的距离公式：$\sqrt{(x_1 - x_2)^2 + (y_1 -y_2)^2}$。

海伦公式：若三角形三边长为 $a,b,c$，设半周长 $p=\frac{a+b+c}{2}$，则三角形面积为 $S=\sqrt{p(p-a)(p-b)(p-c)}$。

### 代码：
```
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n;
	double res=0;
	cin>>n;
	double x[n+1],y[n+1];
	for(int i=1;i<=n;i++){
		cin>>x[i]>>y[i];
	}for(int i=1;i<n-1;i++){
		for(int j=i+1;j<n;j++){
			for(int k=j+1;k<=n;k++){
					double a=sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]));
					double b=sqrt((x[j]-x[k])*(x[j]-x[k])+(y[j]-y[k])*(y[j]-y[k]));
					double c=sqrt((x[k]-x[i])*(x[k]-x[i])+(y[k]-y[i])*(y[k]-y[i]));
					double p=(a+b+c)/2;
					double cnt=sqrt(p*(p-a)*(p-b)*(p-c));
					res=max(res,cnt);
				}
			}
		}
	}cout<<int(res*2);
	return 0;
}
```
但是，则只有 $20$ 分，因为蒟蒻审题不仔细，没注意到合法的三角形需要有一条边与 $x$ 轴平行，且有另一条边与 $y$ 轴平行。

所以，加上判断条件就行啦！
### 代码如下：
```
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n;
	double res=0;
	cin>>n;
	double x[n+1],y[n+1];
	for(int i=1;i<=n;i++){
		cin>>x[i]>>y[i];
	}for(int i=1;i<n-1;i++){
		for(int j=i+1;j<n;j++){
			for(int k=j+1;k<=n;k++){
				if((x[i]==x[j] or x[i]==x[k] or x[j]==x[k]) and (y[i]==y[j] or y[i]==y[k] or y[j]==y[k])){
					double a=sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]));
					double b=sqrt((x[j]-x[k])*(x[j]-x[k])+(y[j]-y[k])*(y[j]-y[k]));
					double c=sqrt((x[k]-x[i])*(x[k]-x[i])+(y[k]-y[i])*(y[k]-y[i]));
					double p=(a+b+c)/2;
					double cnt=sqrt(p*(p-a)*(p-b)*(p-c));
					res=max(res,cnt);
				}
			}
		}
	}cout<<int(res*2);
	return 0;
}
```

---

## 作者：bitset_iTM (赞：1)

很简单的一道题，对于学过一点坐标系的人这题应该是个模拟题。  
**很显然，三重循环暴力枚举三个点，判断是否有一条边与 $x$ 轴平行，且有另一条边与 $y$ 轴平行。**


```cpp
#include <bits/stdc++.h>
using namespace std;

struct point //用结构体存储每一个点的信息
{
    int x, y;
};

point a[105];

int get(int i, int j, int k) //判断是否符合题意。若符合就返回其面积的二倍
{
    int x1 = a[i].x, x2 = a[j].x, x3 = a[k].x; //三个点x坐标
    int y1 = a[i].y, y2 = a[j].y, y3 = a[k].y; //三个点y左边
    
    if (((x1 == x2) || (x2 == x3) || (x1 == x3)) 
     && ((y1 == y2) || (y2 == y3) || (y1 == y3)))
        return (max({x1, x2, x3}) - min({x1, x2, x3})) * 
               (max({y1, y2, y3}) - min({y1, y2, y3})); //直接判断
    else return 0; //不符合题意，返回0
}

int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d %d", &a[i].x, &a[i].y); //Input
    
    int love_YW = 0;
    for (int i = 1; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            for (int k = j + 1; k <= n; k++) //三重循环暴力枚举3个点
                love_YW = max(love_YW, get(i, j, k)); //养成用函数的好习惯
    printf("%d\n", love_YW); //Output The Answer
    return 0; //Happily End!
}
```


---

## 作者：__O_v_O__ (赞：1)

此题我使用结构体存储。

因为 $n$ 很小，所以考虑立方的复杂度枚举三个点。

假设当前枚举的三个点为 $i,j,k$，则有以下六种情况。

1. $i$ 的横坐标等于 $j$ 的横坐标，$i$ 的纵坐标等于 $k$ 的纵坐标。

2. $i$ 的横坐标等于 $j$ 的横坐标，$j$ 的纵坐标等于 $k$ 的纵坐标。

3. $i$ 的横坐标等于 $k$ 的横坐标，$j$ 的纵坐标等于 $k$ 的纵坐标。

4. $i$ 的横坐标等于 $k$ 的横坐标，$i$ 的纵坐标等于 $j$ 的纵坐标。

5. $j$ 的横坐标等于 $k$ 的横坐标，$i$ 的纵坐标等于 $k$ 的纵坐标。

6. $j$ 的横坐标等于 $k$ 的横坐标，$i$ 的纵坐标等于 $j$ 的纵坐标。

对于每种情况，使用三角形面积公式求出面积，注意输出的是面积的**两倍**！！！

**AC code:**
```cpp
#include<bits/extc++.h>
using namespace std;
#define BTS 0
#define STB 1
#define afor(i,n,m,dir) for(int i=n;dir?i<=m:i>=m;dir?i++:i--)
#define int long long
struct P{int x,y;}a[101];//结构体
int n,ma=-1;//定义
signed main(){
	ios::sync_with_stdio(0);//读入优化
	cin>>n;//输入
	afor(i,1,n,STB)cin>>a[i].x>>a[i].y;//输入
	afor(i,1,n-2,STB)afor(j,i+1,n-1,STB)afor(k,j+1,n,STB){//枚举三个点
		if(a[i].x==a[j].x&&a[i].y==a[k].y)ma=max(ma,abs(a[i].y-a[j].y)*abs(a[i].x-a[k].x));//1
		else if(a[i].x==a[j].x&&a[j].y==a[k].y)ma=max(ma,abs(a[i].y-a[j].y)*abs(a[j].x-a[k].x));//2
		else if(a[i].x==a[k].x&&a[j].y==a[k].y)ma=max(ma,abs(a[i].y-a[k].y)*abs(a[j].x-a[k].x));//3
		else if(a[i].x==a[k].x&&a[i].y==a[j].y)ma=max(ma,abs(a[i].y-a[k].y)*abs(a[i].x-a[j].x));//4
		else if(a[j].x==a[k].x&&a[i].y==a[k].y)ma=max(ma,abs(a[j].y-a[k].y)*abs(a[i].x-a[k].x));//5
		else if(a[j].x==a[k].x&&a[i].y==a[j].y)ma=max(ma,abs(a[j].y-a[k].y)*abs(a[i].x-a[j].x));//6
	}cout<<ma;//输出
	return 0;
}
```

---

## 作者：Ag77 (赞：1)

## 分析：
当看完题目后注意到 $3 \le N \le 100$，~~此时任何优化都没有意义了。~~

很简单的一道题，由于数据十分小，所以直接大暴力。

题目要寻找三个点构成的三角形的最大面积，但是多了一个特殊要求要三角形有一条边与 $x$ 轴平行，且有另一条边与 $y$ 轴平行。

我们只需要进行 $3$ 重循环，为了方便我们固定一个点 $i$，考虑另外两个点，点 $j$ 和点 $k$ 和它的关系，有两种可能：

直线 $l_{i,j}$ 与 $x$ 轴平行，则 $l_{i,k}$ 或 $l_{j,k}$ 与 $y$ 轴平行。

直线 $l_{i,j}$ 与 $y$ 轴平行，则 $l_{i,k}$ 或 $l_{j,k}$ 与 $x$ 轴平行。

## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int x[110],y[110],ans,sum;
int main(){
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>x[i]>>y[i];
  //为了方便直接用数组存储点的横纵坐标（x为横坐标，y为纵坐标）
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            for(int k=1;k<=n;k++){
                if(x[i]==x[k]&&y[i]==y[j]){
                    sum=abs(x[i]-x[j])*abs(y[i]-y[k]);//第一种情况；
                }               
                ans=max(sum,ans);//两种情况都取max
                if(x[i]==x[j]&&y[i]==y[k]){
                    sum=abs(x[i]-x[k])*abs(y[i]-y[j]);//第二种情况；
                }
                ans=max(sum,ans);//两种情况都取max                             
            }
        }
    }
    cout<<ans;
    return 0;
} 
```

---

## 作者：FlyPancake (赞：1)

## [P9949 [USACO20FEB] Triangles B](https://www.luogu.com.cn/problem/P9949) 题解

计算几何入门题，~~但是假贪心~~。

## Ideas

枚举每个点的坐标，为使面积最大，分别再遍历找到与该点在同一水平直线上距离最远的点和与该点在同一竖直直线上距离最远的点，将两距离分别作为底和高，相乘即可。（这样就不用再除以 $2$ 了）

## Code

```
#include <bits/stdc++.h>
using namespace std;

int x[105], y[105];
int main(){
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int n, ans = 0; cin>>n;
    for(int i=1; i<=n; i++) cin>>x[i]>>y[i];
    for(int i=1; i<=n; i++){
        int h = 0, w = 0;
        for(int j=1; j<=n; j++){
            if(x[i]==x[j]) h = max(h, abs(y[i]-y[j]));
            if(y[i]==y[j]) w = max(w, abs(x[i]-x[j]));
            ans = max(ans, h*w);
        }
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：wwxxbb (赞：0)

## 思路

观察到 $n$ 很小，$O(n^3)$ 也能过，所以直接暴力枚举三个点，判断是否有两点横坐标相同，两点纵坐标相同，再算一下面积取一下最大值即可。

## 代码

`````
#include <bits/stdc++.h>
using namespace std;

const int N = 110;

int n, x[N], y[N];
int ans = INT_MIN;

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> x[i] >> y[i];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            for (int k = 1; k <= n; k++) {
                if (i == j || j == k || k == i) continue;
                if (x[i] == x[j] && y[j] == y[k]) ans = max(ans, abs(x[k] - x[j]) * abs(y[j] - y[i]));
            }
    return cout << ans, 0;
}
`````

---

## 作者：J_Kobe (赞：0)

### 思路
首先我们要知道：

- 如果两个点的横坐标相同，那么这两个点连成的边就平行于 $y$ 轴。
- 如果两个点的纵坐标相同，那么这两个点连成的边就平行于 $x$ 轴。

所以我们就可以双重循环，找到两个横坐标相同的点，再找到两个纵坐标相同的点，如果找到了的话，就可以求出这个三角形的面积，然后每次算完后再取一个最大值就好了。

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

int x[110], y[110], ans, mx1, mx2, n;

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie();cout.tie();
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> x[i] >> y[i];
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            for (int r = 1; r <= n; r++)
            {
                if (x[i] == x[r] && y[i] == y[j])
                {
                    mx1 = abs(x[i] - x[j]) * abs(y[i] - y[r]);
                }               
                if (x[i] == x[j] && y[i] == y[r])
                {
                    mx2 = abs(x[i] - x[r]) * abs(y[i] - y[j]);
                }
                if (ans < mx1)
                {
                	ans = mx1;
                }
                if (ans < mx2)
                {
                	ans = mx2;
				}
            }
        }
    }
    cout << ans;
    return 0;
} 
```

---

## 作者：Quartz_Blocks (赞：0)

## P9949 [USACO20FEB] Triangles B 题解

已知 $n$ 个点，求可以合法围成的三角形，并且要有一条轴与 $x$ 轴平行，且有另一条轴与 $y$轴平行。


由于数据貌似不大，所以我直接使用了暴力。于是就被打了脸（$50$ 分）：
```cpp
#include <iostream>
using namespace std;
struct node{
    int a,b;
}a[110];
int n,res = 0;
int main(){
    cin >> n;
    for(int i = 1;i <= n;i++) cin >> a[i].a >> a[i].b;
    for(int i = 1;i <= n-2;i++){
        for(int j = i+1;j <= n-1;j++){
            for(int k = j+1;k <= n;k++){
                if(((a[i].a == a[j].a && a[i].a != a[k].a) || (a[i].a == a[k].a && a[i].a != a[j].a) || (a[j].a == a[k].a && a[i].a != a[j].a)) && ((a[i].b == a[j].b && a[i].b != a[k].b) || (a[i].b == a[k].b && a[i].b != a[j].b) || (a[j].b == a[k].b && a[i].b != a[j].b))){
                    res = max(res,(max(a[i].a,max(a[j].a,a[k].a) - min(a[i].a,min(a[j].a,a[k].a))) * max(a[i].b,max(a[j].b,a[k].b) - min(a[i].b,min(a[j].b,a[k].b)))));
                }
            }
        }
    }
    cout << res;
    return 0;
}
```
这个代码有很多问题，不能保证数组有序，会有正负数问题。中间码风不够整洁……
于是有了 $90$ 分代码：
```cpp
#include <iostream>
#include <algorithm>
using namespace std;
struct node{
    int a,b;
}a[110];
bool cmp(node x,node y){
    if(x.a != y.a) return x.a>y.a;
    return x.b>y.b;
}
int n,res = 0;
int main(){
    cin >> n;
    sort(a+1,a+1+n,cmp);
    for(int i = 1;i <= n;i++) cin >> a[i].a >> a[i].b;
    for(int i = 1;i <= n-2;i++){
        for(int j = i+1;j <= n-1;j++){
            for(int k = j+1;k <= n;k++){
                if(((a[i].a == a[j].a && a[i].a != a[k].a) || (a[i].a == a[k].a && a[i].a != a[j].a) || (a[j].a == a[k].a && a[i].a != a[j].a)) && ((a[i].b == a[j].b && a[i].b != a[k].b) || (a[i].b == a[k].b && a[i].b != a[j].b) || (a[j].b == a[k].b && a[i].b != a[j].b))){
                    int t = int(max(a[i].a,max(a[j].a,a[k].a))-min(a[i].a,min(a[j].a,a[k].a)));
                    int b = int(max(a[i].b,max(a[j].b,a[k].b))-min(a[i].b,min(a[j].b,a[k].b)));
                    res = max(res,t*b/2);
                }
            }
        }
    }
    cout << res*2;
    return 0;
}
```
问题就出在第 $22$ 行，当 $t \times b$ 得到一个奇数时，$t \times b\div2$          会由于强制类型转换的原因丢失 $0.5$，后期再 $\times2$ 时就会少了 $( 0.5 \times 2 ) = 1$，导致 WA 
（悲

于是就有了 AC 代码：
```cpp
#include <iostream>
#include <algorithm>
using namespace std;
struct node{
    int a,b;
}a[110];
bool cmp(node x,node y){
    if(x.a != y.a) return x.a>y.a;
    return x.b>y.b;
}
int n,res = 0;
int main(){
    cin >> n;
    sort(a+1,a+1+n,cmp);
    for(int i = 1;i <= n;i++) cin >> a[i].a >> a[i].b;
    for(int i = 1;i <= n;i++){
        for(int j = i+1;j <= n;j++){
            for(int k = j+1;k <= n;k++){
                if(((a[i].a == a[j].a && a[i].a != a[k].a) || (a[i].a == a[k].a && a[i].a != a[j].a) || (a[j].a == a[k].a && a[i].a != a[j].a)) && ((a[i].b == a[j].b && a[i].b != a[k].b) || (a[i].b == a[k].b && a[i].b != a[j].b) || (a[j].b == a[k].b && a[i].b != a[j].b))){
                    int t = int(max(a[i].a,max(a[j].a,a[k].a))-min(a[i].a,min(a[j].a,a[k].a)));
                    int b = int(max(a[i].b,max(a[j].b,a[k].b))-min(a[i].b,min(a[j].b,a[k].b)));
                    res = max(res,t*b);
                }
            }
        }
    }
    cout << res;
    return 0;
}
```

---

## 作者：卷王 (赞：0)

观察题目中 $n$ 的范围，可以直接 $O(n^3)$。于是可以暴力枚举三角形的三个点，然后用三角形的计算公式直接求出面积，取最大值即可。
```cpp
#include <bits/stdc++.h>
using namespace std;
//#define int long long
typedef long long ll;
typedef pair<int, int> pr;
#define up(l, r, i) for(int i = (l); i <= (r); i++)
#define down(r, l, i) for(int i = (r); i >= (l); i--)
const int mod = 1000000007;
const int base = 2333;
const double eps = 1e-6;

inline int read() {
	int x = 0, f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-') f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') {
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return x * f;
}

int n, m, k, Q, T, _, ans = 0;
struct node {
	int x, y;
} a[107];

signed main() {
	n = read();
	for (int i = 1; i <= n; i++) {
		a[i].x = read(), a[i].y = read();
	}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			for (int k = 1; k <= n; k++) {
				if (i == j || j == k || i == k) continue;
				int x1 = a[i].x, y1 = a[i].y;
				int x2 = a[j].x, y2 = a[j].y;
				int x3 = a[k].x, y3 = a[k].y;
				if (y1 == y2 && x2 == x3) ans = max(ans, abs(x2 - x1) * abs(y3 - y2));
			}
	cout << ans;
	return 0;
}
```

---

## 作者：lgydkkyd (赞：0)

题意简述：题目会给出一些坐标，问一条边与横轴平行且一条边与纵轴平行的最大三角形面积的两倍是多少。下面讲一下思路，这道题是可以三重循环枚举任意三点组成的三角形面积的，但是要判断是否一条边与横轴平行且一条边与纵轴平行，如果是则有一个变量每次取较大值，否则不用管，最后输出结果即可。
# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,x[101],y[101];
double s=0.0;
int main(){
    scanf("%lld",&n);
    for(int i=1;i<=n;i++){
        scanf("%lld%lld",&x[i],&y[i]);
    }
    for(long long i=1;i<=n;i++){
        for(long long j=i+1;j<=n;j++){
            for(long long k=j+1;k<=n;k++){
            	if((x[i]==x[j]||x[i]==x[k]||x[k]==x[j])&&(y[i]==y[j]||y[i]==y[k]||y[k]==y[j]))
                s=max(0.5*(abs(x[i]*y[j]+x[j]*y[k]+x[k]*y[i]-x[i]*y[k]-x[j]*y[i]-x[k]*y[j])),s);
            }
        }
    }
    printf("%.0lf",s*2);
    return 0;
}
```

---

## 作者：_Weslie_ (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/P9949)。

思路显然。

枚举三个点，看看它们是否有两个横坐标相等且有两个纵坐标相等。如果有就统计答案。

时间复杂度 $\operatorname{O}(n^3)$，可以通过本题。

```
#include<iostream>
using namespace std;
int x[105],y[105],n,ans;
int abss(int a){
	if(a>0)return a;
	return -a;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>x[i]>>y[i];
	}
	for(int i=1;i<=n;i++){
		for(int j=1+i;j<=n;j++){
			for(int k=j+1;k<=n;k++){
				if(x[i]==x[j]){
					if(y[i]==y[k])ans=max(ans,abss(y[i]-y[j])*abss(x[i]-x[k]));
					else if(y[j]==y[k])ans=max(ans,abss(y[i]-y[j])*abss(x[j]-x[k]));
				} 
				else if(x[i]==x[k]){
					if(y[i]==y[j])ans=max(ans,abss(y[i]-y[k])*abss(x[i]-x[j]));
					else if(y[j]==y[k])ans=max(ans,abss(y[i]-y[k])*abss(x[j]-x[k]));
				} 
				else if(x[k]==x[j]){
					if(y[i]==y[k])ans=max(ans,abss(y[k]-y[j])*abss(x[i]-x[k]));
					else if(y[j]==y[i])ans=max(ans,abss(y[k]-y[j])*abss(x[j]-x[i]));
				} 
			}
		}
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：1234567890sjx (赞：0)

计算几何入门题。

枚举三个点的坐标，判断是否有两个点的 $x$ 坐标相同，两个点的 $y$ 坐标相同。如果有的话直接用海伦公式求三角形面积，求最大值即可。

时间复杂度 $O(n^3)$。

---

## 作者：watergod (赞：0)

# P9949 [USACO20FEB] Triangles B 题解

[题目传送门](https://www.luogu.com.cn/problem/P9949)

## 题目分析

这题相当于选 $3$ 个点围成一个三角形，但是这个三角形必须满足有一条边是平行于坐标轴的，求这个三角形的面积的两倍。众所周知，三角形的面积是底 $\times$ 高 $\div$ $2$，为了避免小数点问题，我直接选择在计算面积的时候算两倍，最后比较输出即可。 

## 思路

枚举每个点的坐标 $(x,y)$。

之后，我们先找到和这个点在同一水平直线上的点。即另外一个点的 $x$ 坐标也为 $x$ 的点，为使面积最大，我们找到距离这个点最远的点，也就是使这个三角形的底边取最大值，并记录下来。

同理，我们随后先找到和这个点在同一竖直直线上的点，然后找到距离这个点最远的点，使宽取到最大值，记录下来。

这样，针对遍历的每个点 $(x,y)$，我们可以算出该点的最大面积。之后我们计算所有点的最大面积，求出最大值即可。

**注意事项**

1. 注意小数点的精度问题

2. 在遍历每个点时，长和宽的最大值要清零。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

long long n;
long long a[114514][2];
long long area;
long long c,k;

int main(){
	cin >> n;
	for(register int i=1;i<=n;i++){
		cin >> a[i][0] >> a[i][1];
	}
	for(register int i=1;i<=n;i++){
		c = 0;
		k = 0;
		for(register int j=1;j<=n;j++){
			if(a[i][0] == a[j][0]){
				k = max(k,abs(a[i][1]-a[j][1]));
			}
			if(a[i][1] == a[j][1]){
				c = max(c,abs(a[i][0]-a[j][0]));
			}
			area = max(area,k*c);
		}
	}
	cout << area << endl;
	return 0;
}

```

[AC 记录](https://www.luogu.com.cn/record/140209311)

---

