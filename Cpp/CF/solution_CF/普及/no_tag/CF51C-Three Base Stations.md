# Three Base Stations

## 题目描述

The New Vasjuki village is stretched along the motorway and that's why every house on it is characterized by its shift relative to some fixed point — the $ x_{i} $ coordinate. The village consists of $ n $ houses, the $ i $ -th house is located in the point with coordinates of $ x_{i} $ .

TELE3, a cellular communication provider planned to locate three base stations so as to provide every house in the village with cellular communication. The base station having power $ d $ located in the point $ t $ provides with communication all the houses on the segment $ [t-d,t+d] $ (including boundaries).

To simplify the integration (and simply not to mix anything up) all the three stations are planned to possess the equal power of $ d $ . Which minimal value of $ d $ is enough to provide all the houses in the village with cellular communication.

## 样例 #1

### 输入

```
4
1 2 3 4
```

### 输出

```
0.500000
1.500000 2.500000 3.500000
```

## 样例 #2

### 输入

```
3
10 20 30
```

### 输出

```
0
10.000000 20.000000 30.000000
```

## 样例 #3

### 输入

```
5
10003 10004 10001 10002 1
```

### 输出

```
0.500000
1.000000 10001.500000 10003.500000
```

# 题解

## 作者：kirky_wang (赞：3)

### 原题

[传送门](https://codeforces.com/problemset/problem/51/C)



### 题意
  $ x $  水平轴上有 $ n $ ( $ ≤ $ $ 2 $ × $ 10 ^ 5 $ ) 个房子，建3个基站，使得每个基站的直径都是 $ d $ 最小且能覆盖所有房子。房子坐标都是整数，且 $ ≤ 10 ^ 9 $  ，输出基站半径和三个基站的中心坐标，保留  6  位小数。


### 解析
算法：枚举

中心位置未知、直径长度未知，似乎有两个变量需要二分搜索，且位置可能是小数，无从下手！不过，由于房子坐标都是整数，因此最小直径肯定也是整数，这样就无需枚举中心位置，只有一个量未知，我们可以试着写出枚举的程序，三条直径，我们枚举两条，剩下一条只需  check  即可：

```cpp
for(int i=1;i<=n;i++)
	for(int j=i;j<=n;j++)
		check(i,j);
```

$ i,j $ 可以看出是这两条直径的右端点：第一条 $ 1..i $ ，第二条   $ i + 1.. j  $ ，第三条 $ j + 1 . . n $ ， check()  是三条中选一条最小的。然而根据 $ n $ 的范围必然会超时。

实际上，当第一个端点确定后，后面一个端点也就确定了：即后半段的中间位置便是第二条直径的右端点，这样可以减少枚举量 $ j $

```cpp
for(int i=1,j=1;i<=n;i++)
{
	while(j<n&&a[n]-a[j-1]>a[j]-a[i+1])
		j++;
	check(i,j);
}
```

### 完整代码

不过这样可能会漏掉更小的答案，因为第一条直径确定后，答案可能在后半段的中间位置，因此还需check  $ j - 1 $  这个端点。程序如下：


```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 3;
int a[maxn], n;
double pa, pb, pc, ans = 1e9;
void check(int x, int y)
{
    if (y < 1) y = 1;
    int z = a[x] - a[1];
    z = max(a[y] - a[min(x+1, n)], z);
    z = max(a[n] - a[min(y+1, n)], z);
    if (z < ans)
    {
        ans = z;
        pa = a[x] + a[1];
        pb = a[y] + a[min(x+1, n)];
        pc = a[n] + a[min(y+1, n)];
    }
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", a + i);
    sort(a + 1, a + n + 1);

    for (int i = 1, j = 1; i <= n; i++)
    {
        while (j < n && a[n] - a[j+1] > a[j] - a[i+1])
            j++;        
        check(i, j-1);
        check(i, j);
    }
    printf("%.6lf\n%.6lf %.6lf %.6lf\n", ans / 2.0, pa / 2.0, pb / 2.0, pc / 2.0);
    return 0;
}

```

---

## 作者：皮卡丘最萌 (赞：3)

求最小距离，显然使用**二分**。

这里主要讲一下**判断过程**。

设每个点的坐标为$a_1,a_2,...,a_n$，此时二分距离为$d$。

为了**尽可能覆盖到后面的点**，第一个基地应该放在$a_1+d$的位置。

接下来扫描一遍，找到第一个**不能覆盖**的点，记做$a_i$。

显然，第二个基地应该放在$a_i+d$的位置。

重复此过程，直到放置完$3$个基地。

接下来判断能否覆盖**最后一个点**即可。

注意事项：

$1.$所有点应该先排序。

$2.$二分时改变值控制在$10^{-7}$及以下。

代码：
```pascal
var n,i:longint; bao,bao1,bao2,bao3,ans1,ans2,ans3,mid,t,w:real;
a:array[0..500001] of longint;
    procedure sort(l,r: longint);
      var i,j,x,y: longint;
      begin
         i:=l; j:=r;
         x:=a[(l+r) div 2];
         repeat
           while a[i]<x do inc(i);
           while x<a[j] do dec(j);
           if not(i>j) then
             begin
                y:=a[i];a[i]:=a[j];a[j]:=y;
                inc(i); j:=j-1;
             end;
         until i>j;
         if l<j then sort(l,j);
         if i<r then sort(i,r);
      end;                      //排序
function pd(x:real):boolean;
var i:longint;
begin
bao1:=a[1]+x;
for i:=1 to n do
  if a[i]>bao1+x then break;
bao2:=a[i]+x;
for i:=i to n do
  if a[i]>bao2+x then break;
bao3:=a[i]+x;
for i:=i to n do
  if a[i]>bao3+x then break;          //放置基地
if bao1>a[n] then bao1:=a[n];
if bao2>a[n] then bao2:=a[n];
if bao3>a[n] then bao3:=a[n];
exit((i=n)and(a[i]<=bao3+x));        //判断是否可行
end;

begin
readln(n);
for i:=1 to n do read(a[i]);
sort(1,n);
t:=0; w:=a[n];
while t<=w do
  begin
  mid:=(t+w)/2;
  if pd(mid) then
    begin
    bao:=mid;
    ans1:=bao1; ans2:=bao2; ans3:=bao3;     //保存答案
    w:=mid-(1e-7);
    end
  else t:=mid+(1e-7);
  end;
writeln(bao:0:6);
writeln(ans1:0:6,' ',ans2:0:6,' ',ans3:0:6);   //输出
end.
```


---

## 作者：TheSky233 (赞：2)

## Description

给定序列 $a_{1 \cdots n}$，求一个最小的半径 $d$，使得放置的三个基站能够覆盖到所有的点。

## Solution

思路：二分答案。

### 如何证明单调性

显然，半径越大，能够覆盖的点就越多；反之，能够覆盖的的就越小。

### 判断答案是否正确

先把 $a$ 数组按升序排序，容易想到，第一个基站一定设在 $a_1+d$ 的位置最优，因为能在最大限度上覆盖到其他点。把这个基站的位置记录下来，每当扫到一个 $a_i$ 比上一个建造的位置的值加 $d$ 还大，就说明要为这个点再设一个基站，重复上文即可。

当基站数量大于 $3$ 时，答案不成立，否则答案成立。

### 注意事项

不同于其他普通的二分题，这一题的答案是浮点数。所以有必要设置一个 $eps$ 来存储最小的精度限制，在本题中为 ```1e-7```。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=2e5+5;
const double eps=1e-7;

int n;
double a[N],l,r,ans,pos[4],tmp[4];

bool check(double k){
	int cnt=1;
	tmp[1]=a[1]+k;
	for(int i=2;i<=n;i++){
		if(a[i]>tmp[cnt]+k){
			if(cnt==3) return false;
			cnt++; tmp[cnt]=a[i]+k;
		}
	}
	return true;
}

int main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	sort(a+1,a+n+1);
	l=0,r=a[n];
	while(r-l>=eps){//浮点数直接用 == 不太保险
		double mid=(l+r)/2;
		if(check(mid)){
			ans=mid;
			for(int i=1;i<=3;i++) pos[i]=tmp[i];
			r=mid-eps;
		}
		else l=mid+eps;
	}
	cout<<fixed<<setprecision(6)<<ans<<'\n'<<pos[1]<<' '<<pos[2]<<' '<<pos[3];
	return 0;
}
```

------------

## $\texttt{The End.}$

---

## 作者：xiaozeyu (赞：1)

**定头尾，用二分的方法**

**记得高精度**

**上代码**

------------

```c
#include<bits/stdc++.h>
using namespace std;
int n;
int arr[200020];
double sol[3];
double tmp [3];//定义
bool v(double d)
{
	double end=0;//清零
	int j=0;
	for(int i=0;i<n;i++)
	{
		if(arr[i]>end)//判断
		{
			if(j==3) return 0;//不能
			tmp[j++]=d+arr[i];
			end=arr[i]+2.0*d;//求出
		}
	}
	for(int i=0;i<3;i++) sol[i]=tmp[i];//替换答案
	return 1;//能
}
double S()
{
	double lo=0;
	double hi=arr[n-1];//头尾
	for(int i=0;i<400;i++)//二分
	{
		double mid=(lo+hi)/2;
		if(v(mid)) hi=mid;
		else lo=mid;
	}
	return lo;
}
int main()
{
	cin>>n;
	for(int i=0;i<n;i++)
		cin>>arr[i];//输入
	sort(arr,arr+n);//记得先排序
	printf("%.6lf\n",S());
	printf("%.6lf %.6lf %.6lf",sol[0],sol[1],sol[2]);//输出
}
```


---

## 作者：FANTA5TlC (赞：1)

大家好，我是dyisz

一道非常简单的二分

1.二分d（距离）

2.判断这个距离能否让所有点被覆盖

3.如果能，缩短距离
	
如果不能，就是这个d的上一个

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX = 2e5 + 7;
int N;
double a[MAX];
double x, y, z,X,Y,Z;
bool check(double k){
	x = a[1] + k;
	y = z = 0.00000;
	double cover = x + k;
	for (int i = 2; i <= N; i++){
		if (a[i] - cover > 1e-7){
			if (y > 1e-7){
				if (z>1e-7)return 0;
				z = a[i] + k;
				cover = z + k;
			}
			else{
				y = a[i] + k;
				cover = y + k;
			}
		}
	}
	X=x,Y=y,Z=z;
	return 1;
}
int main(){
	scanf("%d",&N);
	for (int i = 1; i <= N; i++)scanf("%lf",&a[i]);
	double l = 0.0, r = 2e9 + 7;//记得类型
	double ans = 2e9 + 7;
	sort(a + 1, a + 1 + N);
	while (r - l > 1e-7){//就是判断r是否等于l，double直接==可能会精度误差
		double mid = (l + r) * 0.5//防止直接除以2后mid是int类型
		if (check(mid))r = mid;
		else l = mid;
	}
	printf("%.6lf\n", r);
	printf("%.6lf %.6lf %.6lf\n", X, Y, Z);	
    return 0;
} 

```



---

