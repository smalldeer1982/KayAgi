# [ABC062C] Chocolate Bar

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc062/tasks/arc074_a

縦 $ H $ ブロック、横 $ W $ ブロックの板チョコがあります。 すぬけ君は、この板チョコをちょうど $ 3 $ つのピースに分割しようとしています。 ただし、各ピースはブロックの境目に沿った長方形でなければなりません。

すぬけ君は、$ 3 $ つのピースの面積 (ブロック数) をできるだけ均等にしようとしています。 具体的には、$ 3 $ つのピースの面積の最大値を $ S_{max} $、最小値を $ S_{min} $ としたとき、$ S_{max}\ -\ S_{min} $ を最小化しようとしています。 $ S_{max}\ -\ S_{min} $ の最小値を求めてください。

## 说明/提示

### 制約

- $ 2\ <\ =\ H,\ W\ <\ =\ 10^5 $

### Sample Explanation 1

次図のように分割すると、$ S_{max}\ -\ S_{min}\ =\ 5\ -\ 5\ =\ 0 $ となります。 !\[2a9b2ef47b750c0b7ba3e865d4fb4203.png\](https://atcoder.jp/img/arc074/2a9b2ef47b750c0b7ba3e865d4fb4203.png)

### Sample Explanation 2

次図のように分割すると、$ S_{max}\ -\ S_{min}\ =\ 8\ -\ 6\ =\ 2 $ となります。 !\[a42aae7aaaadc4640ac5cdf88684d913.png\](https://atcoder.jp/img/arc074/a42aae7aaaadc4640ac5cdf88684d913.png)

### Sample Explanation 3

次図のように分割すると、$ S_{max}\ -\ S_{min}\ =\ 10\ -\ 6\ =\ 4 $ となります。 !\[eb0ad0cb3185b7ae418e21c472ff7f26.png\](https://atcoder.jp/img/arc074/eb0ad0cb3185b7ae418e21c472ff7f26.png)

## 样例 #1

### 输入

```
3 5```

### 输出

```
0```

## 样例 #2

### 输入

```
4 5```

### 输出

```
2```

## 样例 #3

### 输入

```
5 5```

### 输出

```
4```

## 样例 #4

### 输入

```
100000 2```

### 输出

```
1```

## 样例 #5

### 输入

```
100000 100000```

### 输出

```
50000```

# 题解

## 作者：seac_blue (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/AT2565)

### 题目大意

给定一个大小为 $H \times W$ 的矩形，切成三部分，只能沿整边切且三个部分均为矩形。

输出三个矩形中最大面积与最小面积差值最小值。

### 思路

切法只有两种：

1. 沿同一个方向切。

2. 先切一刀，在较大的一块上再沿另一个方向切一刀。

令 $S=S_{\max}-S_{\min}$，切法 1 的 $S$ 满足公式：

$$S=\left\{
\begin{aligned}
 0,3\ |\ H \\
 W,\text{otherwise} 
\end{aligned}
\right.$$

切法 2 本人只能想到暴力算法：枚举第一条切边的位置，第二条边只需要从 $\lfloor\dfrac{H}{2}\rfloor$ 处切，判断三个矩形的最小值即可。

矩形可以翻转，所以只需要横着跑一遍，$W,H$ 翻转跑一遍即可。取最小值。

### 代码

```cpp
// 头文件
using namespace std;
typedef long long ll;

ll read(){/* 快读 */}
const ll INF=1145141919810;
ll w,h;
ll minans=INF;

ll Min(ll x,ll y){return x<y?x:y;}
ll Max(ll x,ll y){return x>y?x:y;}
ll Abs(ll x){return x>0?x:-x;}

void work(ll a,ll b){
	if(!(a%3)){
		minans=0;
		return;
	}
	ll res=b;
	ll ceilb=(b>>1)+(b&1);
	for(ll i=1;i<=a;++i){
		ll rect1=b*i;
		ll rect2=ceilb*(a-i);
		ll rect3=(b-ceilb)*(a-i);
		res=Min(res,Max(Abs(rect1-rect2),Max(Abs(rect1-rect3),Abs(rect2-rect3))));
	}
	minans=Min(minans,res);
}

int main(){
	w=read();h=read();
	work(w,h);
	work(h,w);
	printf("%lld\n",minans);
	return 0;
}
```

---

## 作者：01背包 (赞：2)

### 题意：将一个矩形分成三份，使得三份面积的极差最小，输出极差。


### 思路：割法无非就两种，平行割三刀，或者先割一刀分成两半1和2，再在其中一半横着割一刀分成1，3，4，那么比较这俩情况就行了，对于第二种情况，最小的矩形要么是1要么是3或4，再分这两种情况计算就行了。
## _code_ :

```cpp

#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
int cal(int a, int b)
{
    int c = a/2;
    if((LL)a+c > (LL)b*c)
         return (int)((LL)a+c-(LL)b*c);
    int x = (int)ceil(b*c*1.0/(a+c));
    return max((a+c)*x-b*c, (b-x)*(a-2*c));
}
int cal2(int a, int b)
{
    int c = (int)ceil(a/2.0);
    if(a+c > (LL)b*c) return 1e9;
    int x = (LL)b*c/(c+a);
    return max((int)((LL)b*c-(LL)x*(a+c)), (int)((LL)(b-x)*(2*c-a)));
}
int cal3(int a, int b)
{
    double x = floor(b/3.0);
    double y = ceil(b/3.0);
    return (int)(y*a-x*a);
}
int main()
{
    int a, b;
    scanf("%d%d",&a,&b);
    int ans = min(cal(a, b), min(cal(b, a), min(cal2(a, b), min(cal2(b, a), min(cal3(a, b), cal3(b, a))))));
    printf("%d\n",ans);
    return 0;
}
```




---

## 作者：EatBread (赞：1)

竟然没人发`if`大军？我来补一补。

# 思路：

先分为两种情况：被三整除或不能被三整除。

被三整除不用说，直接输出零。

重点来说说不能被三整除的情况。

这里又分了两种情况：有双数或没双数。

### 有双数：

情况一：两个都是双数。

直接输出小的那个除二。

情况二：有一个单数。

输出双数除二或直接输出单数，两个当中选小的。

### 没双数：

情况一：有一个数对三求余等于一。

输出两个数当中小（横切）的或求一下竖切，两个当中选小的。

公式：`((n/3*2+1)*(m/2+1))-(n/3*m)`

情况二：没有数对三求余等于一。

输出思路一样，不过公式得改一下。

公式：`((n/3+1)*m)-((n/3*2+1)*(m/2))`

然后？然后就没有然后了。代码太丑了，不过还是贴一下。

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<string>
#include<algorithm>
using namespace std;
int n,m;
int main()
{
	cin>>n>>m;
	if(n%3==0||m%3==0){cout<<0<<endl;return 0;}
	if(n%2==1)swap(n,m);
	if(n%2==0){
		if(m%2==1){
			cout<<min(n/2,m)<<"\n";return 0;}
		cout<<min(n,m)/2<<"\n";return 0;}
	if(n%3==2)swap(n,m);
	if(n%3==1){cout<<min(((n/3*2+1)*(m/2+1))-(n/3*m),min(n,m))<<"\n";return 0;}
	cout<<min(((n/3+1)*m)-((n/3*2+1)*(m/2)),min(n,m))<<"\n";
	return 0;
}

```






---

## 作者：so_cool (赞：0)

**暴力**解法，一共就两种情况，一条边上平行两刀和一边一刀，讨论即可。

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
    long long h,w,i;//h长，w宽
    long long cut1,cut2,s1,s2,s3,max1,min1;
    cin>>h>>w;;
    long long ans=10000000000;
    //case1 长上平行切两刀
    for(i=1;i<h;i++)
    {
        cut1=i;
        cut2=(h-i)/2;
        s1=cut1*w;
        s2=cut2*w;
        s3=(h-i-cut2)*w;
        max1=max(s1,max(s2,s3));
        min1=min(s1,min(s2,s3));
        ans=min(ans,max1-min1);

    }
    //case2 宽上平行切两刀
    for(i=1;i<w;i++)
    {
        cut1=i;
        cut2=(w-i)/2;
        s1=cut1*h;
        s2=cut2*h;
        s3=(w-cut1-cut2)*h;
        max1=max(s1,max(s2,s3));
        min1=min(s1,min(s2,s3));
        ans=min(ans,max1-min1);

    }
    //case3长一刀，宽两刀
    for(i=1;i<h;i++)
    {
        cut1=i;
        cut2=w/2;
        s1=cut1*w;
        s2=(h-i)*cut2;
        s3=(h-i)*(w-cut2);
        max1=max(s1,max(s2,s3));
        min1=min(s1,min(s2,s3));
        ans=min(ans,max1-min1);

    }
    //case4宽一刀，长两刀
    for(i=1;i<w;i++)
    {
        cut1=i;
        cut2=h/2;
        s1=cut1*h;
        s2=cut2*(w-i);
        s3=(h-cut2)*(w-i);
        max1=max(s1,max(s2,s3));
        min1=min(s1,min(s2,s3));
        ans=min(ans,max1-min1);

    }
    cout<<ans;
}
```

---

