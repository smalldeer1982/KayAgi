# Energy exchange

## 题目描述

It is well known that the planet suffers from the energy crisis. Little Petya doesn't like that and wants to save the world. For this purpose he needs every accumulator to contain the same amount of energy. Initially every accumulator has some amount of energy: the $ i $ -th accumulator has $ a_{i} $ units of energy. Energy can be transferred from one accumulator to the other. Every time $ x $ units of energy are transferred ( $ x $ is not necessarily an integer) $ k $ percent of it is lost. That is, if $ x $ units were transferred from one accumulator to the other, amount of energy in the first one decreased by $ x $ units and in other increased by ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF68B/b2812228d37ba851de724c292afa8e13e0ea3f33.png) units.

Your task is to help Petya find what maximum equal amount of energy can be stored in each accumulator after the transfers.

## 样例 #1

### 输入

```
3 50
4 2 1
```

### 输出

```
2.000000000
```

## 样例 #2

### 输入

```
2 90
1 11
```

### 输出

```
1.909090909
```

# 题解

## 作者：vanueber (赞：3)

[CF原题传送门](https://codeforces.com/problemset/problem/68/B)

# 题目大意

电池在传递能量的时候会有 $k\%$ 的能量损失，求在满足所有电池电量相等的条件下的最大单个能量。

# 题目分析

[前置芝士-二分法/二分答案](https://oi-wiki.org/basic/binary/)

因为 $ a_{i}$ 小于 $1000$，得出答案一定在 $0$ 与 $1000$ 之间，于是我们考虑二分答案。设定 $l$ 为答案下界，$r$ 为答案下界，进行如下的操作去寻找答案。

- 使 $mid$ 为 $(l+r)/2$。
- 判定让 $mid$ 作为答案是否可行。扫描整个序列，求出比答案高的电量与答案的差的和，即多出总电量，与答案与比答案低的电量之差之和，即缺少总电量，如果多出的电量扣去 $k\%$ 后仍能大于等于缺少的电量，即为可行。
- 缩小答案区间。如果可行，让 $l=mid$，否则 $r=mid$。
- 重复上操作，直到 $r-l \leqslant eps$。

最终的 $l$ 就是答案，具体实现见代码。

# 代码

```cpp
#include <cstdio>
#include <iostream>
#define eps 1e-8 // 注意浮点类型二分时的精度问题

using namespace std;

int n, k;
int a[100005];

bool check(double x)
{
    double s1 = 0, s2 = 0;
    for (int i = 1; i <= n; i++)
    {
        if (a[i] < x)
            s1 += x - (double)a[i]; // 多的
        else
            s2 += (double)a[i] - x; // 少的
    }
    double tmp = s2 * ((100.0 - k) / 100.0); // 扣去k%
    if (tmp >= s1)
        return true;
    else
        return false;
}

int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    double l = 0.0, r = 10000.0, mid;
    while (r - l > eps)
    {
        mid = (l + r) / 2.0;
        if (check(mid))
            l = mid;
        else
            r = mid;
    }
    printf("%.8lf", l); // 不保留8位也是对的！？
    return 0;
}

```
[AC记录](https://codeforces.com/problemset/submission/68/218535456)

---

## 作者：yutong_Seafloor (赞：1)

# [题目在这里 · CF68B Energy exchange](https://www.luogu.com.cn/problem/CF68B) 
### 题目简要：

有 $n$ 个电池，已知它们的电量，我们需要通过操作使他们的电量相同，具体的，我们一次性选两个电池进行传输，但是传输会损失 $k\%$ 的电量，一个少 $x$ 个电量，一个多 $x- \frac{xk}{100}$ 的电量，我们要尽量的通过操作使最后的电量是最大的还是相同的。

------------
### 题意分析

看了一眼范围，嗯，非常符合二分的范围，但是是小数二分。

答案范围证据显然是 $[ \max (a_i),\min (a_i)]$，不可能大于最大的 $a_i$，能量一旦传递电量总和显然会变小，也不可能是最小的，很显然不符合最优解，范围找到以后找判断依据。

找到一个中间值 $mid$，枚举全部的电池电量，大于的就转给小于 $mid$ 的，把大于 $mid$ 的加起来，这里用 $big$ 表示，小于 $mid$ 的也加起来，用 $small$ 表示，如果 $big \ge small$，说明小的都能补上还有剩余，调大 $mid$，反之，就说明小于 $mid$ 的太多了，需要把 $mid$ 调小。



------------
注意小数点取 $8$ 位！！！

（冷知识：`printf` 具有四舍五入的功能，不用担心会全舍。）

------------
## 代码 
```
#include<bits/stdc++.h>
using namespace std;
int n,k,a[100010];
double l,r,mid;
bool pd(double x)
{
    double big=0,small=0,ans;
    for(int i=1;i<=n;i++)
    if(a[i]>x) big+=1.0*a[i]-x;
    else small+=x-1.0*a[i];
	return big*((100.0-k)/100)>=small;
}
int main()
{
    cin>>n>>k;
    for(i=1;i<=n;i++)
    cin>>a[i];
    r=1e4;
    while(r-l>0.0000001)
    {
        mid=(l+r)/2.0;
        if(pd(mid)) l=mid;
        else r=mid;
    }
    printf("%.8lf",r);
    return 0;
}//by·yutong_Seafloor
```

---

## 作者：A_B_ (赞：1)

[洛谷题目传送门](https://www.luogu.com.cn/problem/CF68B)。

[Codeforses 题目传送门](https://codeforces.com/problemset/problem/68/B)。

# 题意简述
就是题目中的电池每次传送都会有 $k\%$ 的能耗损失，求在所有电池电量一样的情况下最大的电池单量的最大电量。
# 题目思路
题目说了给定一个队列 $a_i$，让你求最大的电池电量，显然范围就是 $[\min(a_i),\max(a_i)]$ 考虑二分答案。把整个数组的中间设为 $mid$，遍历整个队列，直到找到答案。

不知道二分答案知识的这里有：[二分答案](https://oi-wiki.org/basic/binary/)。
# C++ Code:
~~~cpp
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

const int MAXN = 10000;
const double EPS = 1e-9;

int n, k;
double a[MAXN];

bool check(double x)
{
    double need = 0, extra = 0;
    for (int i = 0; i < n; i++)
    {
        if (a[i] < x)
        {
            need += x - a[i];
        }
        else
        {
            extra += a[i] - x;
        }
    }
    return extra * (100 - k) / 100 >= need;
}

int main()
{
    cin >> n >> k;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    double left = 0, right = 1000;
    while (right - left > EPS)
    {
        double mid = (left + right) / 2;
        if (check(mid))
        {
            left = mid;
        }
        else
        {
            right = mid;
        }
    }
    cout << fixed << setprecision(9) << left << endl;
    return 0;
}
~~~
## AC [记录](https://codeforces.com/contest/68/submission/223079502)。

---

## 作者：ask_silently (赞：1)

## [传送门](https://www.luogu.com.cn/problem/CF68B)
## 题目分析
有 $n$ 个电池，要把他们的电量保持一致。每两个电池之间可以进行电量传递，当然，电量传递需要代价，传递一次会损耗 $k\%$ 的电量，问单体电量最大是多少。
## 思路
- 首先，大家应该很容易能看出来这是一个浮点二分，要求最大值。那二分枚举谁呢？我们看出来，单体电量具有单调性，单体电量越大，比这个枚举的单体电量的电池电量大的值就越少。所以我们决定枚举单体电量。

- 其次，二分肯定要有一个判断函数，我们要判断我们枚举的单体电量值是否是合法的。如果要让全部的电池电量都达到枚举的 $mid$ 的话，我们就需要让比 $mid$ 大的值转给比 $mid$ 小的值。所以我们求出来比 $mid$ 大的值与比 $mid$ 小的值的总和，判断能否补上小的值，如果能补上，那就说明 $mid$ 还可以再大一些；如果补不上，那就说明 $mid$ 还要再小一些。

## AC代码
最后附上代码，注释上有当前部分是干什么的。
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,k;
double a[100010];

//判断函数 
bool judge(double x){
	double duo=0,shao=0;//比mid多的值和比mid小的值的总和 
	for(int i=1;i<=n;i++){
		if(a[i]>x) duo+=a[i]-x;
		else shao+=x-a[i];
	}
	if(shao>duo*(100-k)/100) return false;//判断能否补上 
	return true;
}

int main(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++) scanf("%lf",&a[i]);
	//二分 
	double l=0,r=10000,mid;
	while(r-l>1e-8){//二分终止条件
		mid=(l+r)/2;//mid枚举单体电量 
		if(judge(mid)) l=mid;//能满足mid可以更大一些 
		else r=mid;//不能满足mid需要变小 
	}
	printf("%.8lf",l);//输出最后答案 
	return 0;
}
```


---

## 作者：ZM____ML (赞：1)

## 题意
让每个电池之间进行能量传递让所有电池电量相等。

## 分析
因为每次能量传递都会出现消耗，所以答案一定是在最小值到最大值之间的，所以我们可以考虑二分来寻找答案。

- 设出中间值，计算出比中间值多的电量的和以及比中间值少的电量的和。

- 如果多出的电量减去消耗的电量小于少的电量，说明中间值取大了，需要更改右端点，否则就更改左端点。

## 代码
```c
#include<cstdio>
#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)
using namespace std;
const int N=1e5+5;
inline int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=(x<<3)+(x<<1)+c-48;
		c=getchar();
	}
	return x*f;
} 
int n,k;
int maxn,minn=N,a[N];
int main(){
    n=read(),k=read();
    for(int i=1;i<=n;i++)a[i]=read(),maxn=max(maxn,a[i]),minn=min(minn,a[i]);
    double l=minn,r=maxn;
    while(r-l>1e-8){
        double mid=(l+r)/2,sum1=0,sum2=0;
        for(int i=1;i<=n;i++){
            if(a[i]<mid) sum1+=mid-a[i];
            else sum2+=a[i]-mid;
        }
        if(sum1>sum2*(100-k)/100) r=mid;
        else l=mid;
    }
    printf("%.8lf",l);
    return 0;
}
```


---

## 作者：Keroshi (赞：1)

# 题目分析   
根据题意，需要将能量传递让所有电池电量相等，但每次都要损失 $k\%$。   
不难想到可以计算出多出电量和缺少电量的总和，如果缺少电量正好比多出电量损失 $k\%$ ，那么答案就是当前单个电量。   
最后需要二分枚举单个电量的值即可。   
# 代码   
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int n,k;
double a[N];
int main(){
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++){
        scanf("%lf",&a[i]);
    }
    // 二分
    double l=0,r=1e4;
    while(r-l>1e-8){
        double mid=(r+l)/2;
        double s1=0,s2=0;
        for(int i=1;i<=n;i++){
            if(a[i]<mid) s1+=mid-a[i];
            else s2+=a[i]-mid;
        }
        if(s1>s2*(100-k)/100) r=mid;
        else l=mid;
    }
    printf("%.8lf",l);
    return 0;
}
```

---

## 作者：_outcast_ (赞：1)

### 题意

给定一个序列，两两之间可以相互转移，每次转移会有一定的损耗，要求使得序列所有数相等时数的最大值 。

### 分析

非常显然的是，最后的答案一定是在 $[ \max(a_i),\min(a_i)]$ 之间的，所以我们可以考虑二分来寻找答案，具体过程如下：

- 设中间值为 $mid$，扫描整个序列，累加所有大于当前 $mid$ 的量记为 $sum1$ ；累加所有小于当前 $mid$ 的量记为 $sum2$ 。

- 如果 $sum2$ 减去损失量小于 $sum1$，说明 $mid$ 取值过大，反之过小 。

### 代码实现

（注意精度）

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
const double eps=1e-8;
int n;
double k,a[N];
int main(){
    scanf("%d%lf",&n,&k);
    for(int i=1;i<=n;i++) scanf("%lf",&a[i]);
    sort(a+1,a+n+1);
    double l=a[1],r=a[n],mid;
    while(r-l>eps){
    	mid=(l+r)/2;
    	double sum2=0,sum1=0;
    	for(int i=1;i<=n;i++){
    		if(a[i]<mid) sum1+=mid-a[i];
    		if(a[i]>mid) sum2+=a[i]-mid;
		}
    	if(sum2*((100-k)/100)>sum1) l=mid;
    	else r=mid;
	}
	printf("%0.7f",l);
}
```


---

## 作者：vsidssa (赞：0)

## 题意
电池在传递能量的时候会有 $k\%$ 的能量损失，求在满足所有电池电量相等的条件下的最大单个能量。
## 分析
因为 $a_i$ 小于 $1000$，得出答案一定在 $0$ 与 $1000$ 之间，于是我们考虑二分。
我们看出来，单体电量具有单调性，单体电量越大，比这个枚举的单体电量的电池电量大的值就越少。
设中间值为 $mid$，扫描整个序列，累加所有大于当前 $mid$ 的量记为 $l$,累加所有小于当前 $mid$ 的量记为 $r$。
如果 $r$ 减去损失量小于 $l$，说明 $mid$ 取值过大，反之过小。
## AC 代码
```cpp
#include <bits/stdc++.h>
#define eps 1e-8
using namespace std;
int n, k;
int a[100005];
bool check(double x)
{
    double s1 = 0, s2 = 0;
    for (int i = 1; i <= n; i++)
    {
        if (a[i] < x)
            s1 += x - (double)a[i];
        else
            s2 += (double)a[i] - x;
    }
    double tmp = s2 * ((100.0 - k) / 100.0);
    if (tmp >= s1)
        return true;
    else
        return false;
}
int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    double l = 0.0, r = 10000.0, mid;
    while (r - l > eps)
    {
        mid = (l + r) / 2.0;
        if (check(mid))
            l = mid;
        else
            r = mid;
    }
    printf("%lf", l);
    return 0;
}

```


---

## 作者：LOLchn0 (赞：0)

# 题意：
让每个电池之间进行能量传递让所有电池电量相等，但是每次都要损失百分之 $k$。

# 思路：
求出多余的电量和缺少电量的总和，如果缺少电量正好比多余的电量损失百分之 $k$，那么答案就是当前单个电量。最后二分枚举，得出单个电量的值。

# 代码：

```c
#include<bits/stdc++.h>
using namespace std; 
double ener[10010];
int cmp(double a, double b)
{
	return a > b;
}
int main()
{
	int n, k;
	while(~scanf("%d%d", &n ,&k))
	{
		bool flag = false;
		for(int i = 0; i < n; i++)
		{
			scanf("%lf", &ener[i]);
			if(i >= 1)
			{
				if(ener[i] != ener[i - 1])
				{
					flag = true;
				}
			}
		}
		if(n == 1 || !flag )
		{
			printf("%.9f\n", ener[0]);
			continue;
		}
		sort(ener, ener + n,cmp);
		double l = ener[n - 1];
		double r = ener[0];
		double mid;
		double ans;
		while( r - l > 1e-9 )
		{
			bool flag = true;
			double cur_ener = 0;
			mid = (l + r) / 2;
			for(int i = 0; i < n; i++)
			{
				if(ener[i] - mid >= 1e-9)
					cur_ener += (ener[i] - mid);
				else
				{
					double dis = 1.0 * (mid - ener[i]) * 100 / (100 - k);
					if(dis - cur_ener > 1e-9)
					{
						flag = false;
						break;
					}
					else
						cur_ener -= dis;
				}
			}
			if(flag)
			{
				ans = mid;
				l = mid;
			}
			else
				r = mid;
		}
		printf("%.9f\n", ans);
	}
	return 0;
}
```


---

