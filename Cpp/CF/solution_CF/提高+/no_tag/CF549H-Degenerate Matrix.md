# Degenerate Matrix

## 题目描述

The determinant of a matrix $ 2×2 $ is defined as follows:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF549H/703e7742f6308e45304e4cbb5699ead68258b334.png)A matrix is called degenerate if its determinant is equal to zero.

The norm $ ||A|| $ of a matrix $ A $ is defined as a maximum of absolute values of its elements.

You are given a matrix ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF549H/a81c8b5329fb3da53e1141c4dfaddc43c5a88073.png). Consider any degenerate matrix $ B $ such that norm $ ||A-B|| $ is minimum possible. Determine $ ||A-B|| $ .

## 说明/提示

In the first sample matrix $ B $ is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF549H/d2b53d754fc99e5b9d2dd8345dc06167db4fa5e6.png)

In the second sample matrix $ B $ is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF549H/62b29d043f4b99bb231bfdf3cac3fe3c6d0ab461.png)

## 样例 #1

### 输入

```
1 2
3 4
```

### 输出

```
0.2000000000
```

## 样例 #2

### 输入

```
1 0
0 1
```

### 输出

```
0.5000000000
```

# 题解

## 作者：enyyyyyyy (赞：0)

- 思路：
  可以把这题看成二分。但复杂度太高，所以我写了一种 $O(1)$ 复杂度的算法，模拟！

- 做法：
  因题目提示：该矩阵为退化矩阵 $a\times d-b\times c$。 所以用一个变量去存值，还得用另一个变量去存 $abs(a+b+c+d)$,$abs(a-b+c-d))$,$abs(a-b-c+d)$,$abs(a+b-c-d)$ 中的最大值，如果等于 $0$，就输出 $0.000000000$ 即可，否则输出两数相除。

- 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef __int128 lint;
typedef double db;
typedef void vd;
typedef bool bl;
inline ll read() {
	ll s = 0, w = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-')
			w = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') s = s * 10 + ch - '0', ch = getchar();
	return s * w;
}
inline vd print(ll x) {
	if (x < 0) {
		putchar('-');
		x = -x;
	}
	if (x >= 10)
		print(x / 10);
	putchar(x % 10 + '0');
	return;
}
ll a,b,c,d;
db x,y;
int main() {
	a=read(),b=read(),c=read(),d=read();
 	x=abs(a*d-b*c);
	y=max(max(abs(a+b+c+d),abs(a-b+c-d)),max(abs(a-b-c+d),abs(a+b-c-d)));
	if(y==0) printf("0.000000000");
  	else printf("%.9f",x/y);
	return 0;
}

```


---

## 作者：优秀的渣渣禹 (赞：0)

此题是个**二分**

仔细理解题意发现**并不是**当四个差值绝对值相等的情况下才最优。

枚举这个差值的最大值，二分，不用$while(l <= r)$，因为是浮点数。我们就直接设定判断1000次差不多就行了。

求出两个最边界值，如果$0 \leq max$ 且 $min \leq 0$，那么一定会存在某种情况使
$ ad - bc = 0 $,
从而满足
$B$
是退化矩阵。

注意**不能断定**$(a+mid)*(d+mid)$是最大值,$(a-mid)*(d-mid)$是最小值。

下面是代码 

```cpp#define M cout << "BreakPoint" << endl;
#define O(x) cout << #x << " " << x << endl;
#define O_(x) cout << #x << " " << x << " ";
#define Msz(x) cout << "Sizeof " << #x << " " << sizeof(x)/1024/1024 << " MB" << endl;
#include<cstdio>
#include<cmath>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<queue>
#include<stack>
#define LL long long
#define inf 1000000009
#define N 200005
using namespace std;
#define A (a + mid)
#define A_ (a - mid)
#define B (b + mid)
#define B_ (b - mid)
#define C (c + mid)
#define C_ (c - mid)
#define D (d + mid)
#define D_ (d - mid)
int main(){
    double a,b,c,d;
    scanf("%lf%lf%lf%lf",&a,&b,&c,&d);
    double l = 0,r = 1000000000,mid;
    for(int i = 0;i < 1000;i++){
        mid = (l + r) / 2;
        double mx = max(max(A * D,A_ * D),max(A * D_,A_ * D_));
        double m_x = min(min(A * D,A_ * D),min(A * D_,A_ * D_));
        double my = max(max(B * C,B_ * C),max(B * C_,B_ * C_));
        double m_y = min(min(B * C,B_ * C),min(B * C_,B_ * C_));
        if(mx - m_y >= 0 && m_x - my <= 0) r = mid;
        else l = mid;
    } 
    printf("%.10lf\n",l);
    return 0;
}
```



---

