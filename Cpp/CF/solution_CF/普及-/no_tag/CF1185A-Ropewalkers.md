# Ropewalkers

## 题目描述

数轴上有3个整点A,B,C，分别分布在数a,b,c的地方。现需要让三个点之间两两距离不小于d。每秒钟有且仅有一个点可以移动一步，每步可以向左或向右移动恰好1个单位长度。我们想知道：为了达成目标，至少需要多少秒？

## 说明/提示

对于100%的数据，保证1<=a,b,c,d<=10^9。

## 样例 #1

### 输入

```
5 2 6 3
```

### 输出

```
2
```

## 样例 #2

### 输入

```
3 1 5 6
```

### 输出

```
8
```

## 样例 #3

### 输入

```
8 3 3 2
```

### 输出

```
2
```

## 样例 #4

### 输入

```
2 3 10 4
```

### 输出

```
3
```

# 题解

## 作者：lukelin (赞：3)

写一个比较正常A题题解  
我们发现，有一个贪心思想，如果让两边的远离中间，一定比让中间远离两边更优或者至少相等，所以，我们的答案就是排序以后在左右两边的节点远离中间节点要走的路程和，设原来的三个点为$a_1,a_2,a_3$，答案也就是$max(d-a_1+a_0,0)+max(d-a_2+a_1,0)$。  

下面放个代码(主要长度在于read函数 $Q\ A\ Q$)：

```cpp
#include <cstdio>
#include <algorithm>

using namespace std;

int read(){
    int x = 0; int zf = 1; char ch = ' ';
    while (ch != '-' && (ch < '0' || ch > '9')) ch = getchar();
    if (ch == '-') zf = -1, ch = getchar();
    while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar(); return x * zf;
}

int a[3];

int main(){
	a[0] = read(), a[1] = read(), a[2] = read(); int d =  read();
	sort(a, a + 3);
	int ans = 0;
	if (a[1] - a[0] < d)
		ans += d - a[1] + a[0];
	if (a[2] - a[1] < d)
		ans += d - a[2] + a[1];
	printf("%d", ans);
	return 0;
}
```

---

## 作者：wpj20241021005 (赞：1)

这一道题没有这么难，因为只有三个数，所以只有4种情况，三个if就AC了

先上代码：
```
#include<bits/stdc++.h>
using namespace std; 
int a[4],b;//定义
int main(){
	cin>>a[1]>>a[2]>>a[3]>>b;//输入
	sort(a+1,a+4);
	if(a[2]-a[1]>=b&&a[3]-a[2]>=b){//第一种情况：都大于b（也就是题目中的d），所以就没有必要做下去了
		cout<<0;
		return 0;//完结
	}
	if(a[2]-a[1]<b&&a[3]-a[2]>=b){//第二种：第一区间小于b
		cout<<b-a[2]+a[1];//将a[1]向左移动b-a[2]+a[1]位（秒）
		return 0;//完结
	}
	if(a[3]-a[2]<b&&a[2]-a[1]>=b){//第三种：第二区间小于b
		cout<<b-a[3]+a[2];//将a[3]向右移动b-a[3]+a[2]位
		return 0;//完结
	}
	cout<<2*b-a[3]+a[1];//是（b-a[3]+a[2]）+(b-a[2]+a[1])化简后的结果
	return 0;//撒花
}
```

这一道题三个数有两个区间，而且这些数都是在数轴上（意思是不论正负），所以最简方法就是只考虑移动最大的数和最小的数，使它们与中间数的距离等于d。所以呢，我们就可以使用三个if，来分情况，然后再输出就可以了。

---

## 作者：九月_014 (赞：0)

一共三个点，从贪心的角度出发，中间点不动，分别移动两端的点，要比移动中间的点要节约。
证明：若中间点B发生了移动，则AB间距离与BC间距离都会发生改变(一个变大，一个变小)，容易导致原本合法的点不合法了，还得在移动另一个点。
综上所述，只需要将两端的点分别向两端移动，中间点保持不变，大体为这个样子：![](https://cdn.luogu.com.cn/upload/image_hosting/3nvwlej4.png)

------------
代码的实现也很容易，利用数组存三点坐标，利用sort排序后，轻易得出中间点,则两端分别移动的大小为“d-abs(a[1]-a[2])”，“d-abs(a[2]-a[3])”。
核心代码如下
~~~cpp
for(int i=1;i<=3;i++){
	a[i]=read();
}
sort(a+1,a+4);
d=read();
int ans=0;
if(abs(a[1]-a[2])<d)
	ans+=d-abs(a[1]-a[2]);
if(abs(a[2]-a[3])<d)
	ans+=d-abs(a[2]-a[3]);
printf("%d",ans);
~~~

---

## 作者：xh39 (赞：0)

~~这道题好在只有3个点,如果有n个点我就不知道怎么做了。~~

## 我们可以先排序,再移动左边的和右边的,中间的不动。

为什么中间的不动要好一些呢?

因为如果移动中间的,那么左边和右边有可能也要跟着动,肯定不如移两边的好。

讲解完毕,上ac代码
```cpp
#include<bits/stdc++.h> //超级头文件,包含所有c++库,用于偷懒。
using namespace std;
int main(){
	int a,b,c,d;
	cin>>a>>b>>c>>d;
	if(a>b) swap(a,b);//这三行冒泡排序。
	if(b>c) swap(b,c);
	if(a>b) swap(a,b);
	cout<<max(0,d-b+a)+max(0,d-c+b);//max(a,b)表示对a,b取最大值,因为不能小于0,所以0与结果取最大值d-b+a本来是d-(b-a),b-a表示距离,目标距离-相差距离就是最少移动次数。同理,d-c+b也是d-(c-b)。
	return 0;
}
```

---

## 作者：Law_Aias (赞：0)

## div2的A题，难度800，没什么好讲的。


```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std;

#define LL long long

LL a,b,c,d,ans;
LL pos1,pos2,pos3;

int main() {
    cin>>a>>b>>c>>d;
    pos1 = min(min(a,b),c);
    pos3 = max(max(a,b),c);
    pos2 = a+b+c - pos1 - pos3;
    LL left = 0,right = 0;
    left = pos2 - pos1;
    right = pos3 - pos2;
    if(left < d) ans += (d - left);
    if(right < d) ans += (d - right);
    //cout<<pos1<<" "<<pos2<<" "<<pos3<<endl;
    //cout<<left<<" "<<right<<endl;
    cout<<ans;   
    //system("pause");
    return 0;
}
```


---

