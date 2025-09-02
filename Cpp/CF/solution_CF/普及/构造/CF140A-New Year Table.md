# New Year Table

## 题目描述

Gerald is setting the New Year table. The table has the form of a circle; its radius equals $ R $ . Gerald invited many guests and is concerned whether the table has enough space for plates for all those guests. Consider all plates to be round and have the same radii that equal $ r $ . Each plate must be completely inside the table and must touch the edge of the table. Of course, the plates must not intersect, but they can touch each other. Help Gerald determine whether the table is large enough for $ n $ plates.

## 说明/提示

The possible arrangement of the plates for the first sample is:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF140A/89a963dd60d2b50871a138411d49010a4f94431a.png)

## 样例 #1

### 输入

```
4 10 4
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
5 10 4
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
1 10 10
```

### 输出

```
YES
```

# 题解

## 作者：Buried_Dream (赞：7)

## 题意：

有一个半径为 $R$ 的大圆和若干个半径为 $r$ 的小圆，并且要保证大圆与小圆相切。要在大圆中放入 $n$ 个小圆，若能放下则输出 `YES`，不能则输出 `NO`。

## 思路：

既然题目中已经提到了大圆与小圆相切，我们就可以通过计算圆心角的度数来判断最多能放入多少个圆，也就是用 $2 π$ 来除以这个角度，得出答案后与 $n$ 比较即可。

这题会卡精度，注意好精度问题，可以在 $2π$ 后面加上一个非常接近 $0$ 的数，比如 $1e^{-10}$。

当然如果你背不过 $π$ 可以按住 `ctrl` 键进入 `math.h` 库里找到 $π$。
## AC code：

```cpp
/*
work by: TLE_Automation
Time: O(TLE)
knowledge:
*/
#include<bits/stdc++.h>
#include<math.h>
#define TLE std
#define int long long
#define Min(x, y)  (x > y ? y : x);
#define Max(x, y)  (x > y ? x : y);
#define orz cout << "szt lps fjh AK IOI";
using namespace TLE;

const int maxn = 3e6;
const int MAXN = 3e3;
const double down = 0.996;
const double limit = 1e-10;

inline int read() {
	int s = 0, w = 1;
	char ch = getchar();
	while (!isdigit(ch)) {if(ch == '-') {w = -1;}ch = getchar();}
	while (isdigit(ch)) {s = (s << 1) + (s << 3) + (ch ^ 48);ch = getchar();}
	return s * w;
}

inline void print(int x) {
	if (x < 0 ) putchar('-'), x = -x;
	if (x > 9 ) print(x / 10);
	putchar(x % 10 + '0');
}


const double Pr = 3.14159265358979323846;

signed main() {
	int k = read(), R = read(), r = read();
	if(r > R) return puts("NO"), 0;
	if(r > R / 2) {
		if(k == 1) return puts("YES"), 0;
		else return puts("NO"), 0;
	} double s = asin((double) r / (R - r));
	if(Pr / s  + 1e-12 > k) {
		return puts("YES"), 0;
	}else return puts("NO"), 0;
}

```

[AC 记录](https://www.luogu.com.cn/record/66303664)

---

## 作者：JimmyQ (赞：2)

# CF140A New Year Table
## 思路
注意到题目中提到了大圆与小圆相切，我们可以计算由两条经过小圆周长与大圆圆心的切线组成的圆心角的度数。但是这个角度其实不好算，所以我们可以求出它一半的正弦值，也就是 $b \div (a-b)$，然后用 asin 函数求出其度数（以弧度为单位）。最后答案就是判断 $2 \cdot \pi \div (2 \cdot b\div (a-b))$ 是否 $\ge n$。
## AC 代码
```
#include<bits/stdc++.h>
using namespace std;
#define pi 3.14159265358979
double n,a,b,c;
int main(){
	cin>>n>>a>>b;
	if(n<=2) cout<<(n*b<=a?"YES":"NO")<<endl;
	else cout<<((2*pi)/(2*asin(b/(a-b)))+1e-8>n?"YES":"NO")<<endl;
	return 0;
}
```
[AC 记录](https://codeforces.com/contest/140/submission/299913040)

---

## 作者：__UrFnr__ (赞：2)

**题目大意**：

在一个半径为 $R$ 的圆内放进若干个半径为 $r$ 的小圆，求是否能放下 $n$ 个这种小圆。

**题目思路**：

题目说了大圆内的小圆必须与大圆相切，这样我们就可以通过圆心角的度数来计算最多可以放下多少个圆，如果这个个数不足 $n$ 则输出 `NO`，反之输出 `YES`。

---

## 作者：wangyixuan_s_father (赞：1)

~~这题精度太屑了~~
## CF140A题解
#### 题意
有个半径为 $R$ 的大圆，现在求能否装下 $n$ 个半径为 $r$ 的小圆（大小圆必须相切，也就是小圆的边必须有一个点与大圆边重合）
#### 思路
数学方法。我们可以得知，一定会有一个扇形恰好能装下一个小圆，我们也知道一个圆的角度是 $360$ 度,那么我们就只需要求出扇形的圆心角度数，然后用 $360$ 度除一下就能得到最大能装下的小圆个数。

那么怎么求呢？直接求整个圆心角经过实践不行，但是求半个角可以。方法如下：取一端点为大圆心和小圆边的，长度为 $R-r$ 的线段 $n$，并使一线段 $m$ 连接大小圆圆心。这时，必有一条长度为 $r$ 的，垂直于 $m$ 的线段可与 $n$ 在小圆上的端点连接。这样就可求出半个圆心角的 $sin$ 值为 $r/(R-r)$ ,然后就能用反正弦函数求出半个圆心角的弧度值，接着处理一下就能切题了。
#### code
```cpp
#include<bits/stdc++.h>
using namespace std;
long double P=3.1415926535897932384626;
long double n,R,r,x=1919.810;
int main()
{
	cin>>n>>R>>r;
	if(n==1&&R>=r)//疯狂特判（其实不用，但能省点时间）
	{
		cout<<"YES";
		return 0;
	}
	if(n!=1&&R==r)
	{
		cout<<"NO";
		return 0;
	}
	if(R<r)
	{
		cout<<"NO";
		return 0;
	}
	x=asin(r/(R-r));//反正弦函数arcsin，能通过sin值反求角度，但是是弧度制
	x*=2;//完整的圆心角
	P*=2;
	if((P+1e-114514)/x>=n)cout<<"YES";//求圆心角个数（加精度处理）
	else cout<<"NO";
	return 0;//van结撒花
}
```
#### 题外话
所以说作者已经被精度卡自闭了~~作者太逊了~~

---

## 作者：Nightsky_Stars (赞：0)

# 题目大意：
给一个大圆和一个小圆的半径，求是否能放下 $n$ 个这种小圆，小圆必须在大圆内且与大圆相切。
# 题目思路：
我们就可以通过圆心角的度数来计算最多可以放下几个小圆，如果个数不足则输出 ```NO```，反之输出 ```YES```。
# CODE:
这题有点卡精度。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int R,r,n;
double p=3.1415926535897932384626;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>R>>r;
	if(r>R){
		cout<<"NO\n";
		return 0;
	}
	if(r>R/2) {
		if(n==1){
			cout<<"YES\n";
			return 0;
		}
		else{
			cout<<"NO\n";
			return 0;
		}
	}//特判
	double k=asin((double)r/(R-r));//计算最多可以放下几个小圆
	if(p/k+1e-12>n) cout<<"YES\n";
	else cout<<"NO\n";
    return 0;
}
```
[AC记录](https://codeforces.com/problemset/submission/140/301101665)

---

## 作者：Star_F (赞：0)

一道三角函数题。

## 题目大意：
给你一个半径 为 $R$ 的大圆和一些半径为 $r$ 的小圆，求大圆里是否能装下 $n$ 个小圆，并且满足大圆于小圆相切。

## 题目分析：

![](https://cdn.luogu.com.cn/upload/image_hosting/5scgkca8.png)

如图，我们可以发现，每装下一个小圆，就会占去大圆圆心角的一部分，并且每个圆占用的度数相等。我们可以求出每个小圆占用的度数，再用 $360$ 除以，即可算出最多能装下多少个小圆。

问题转化成了如何求出一个小圆占用的度数。

直接求不好求，我们考虑度数的正弦值，观察到为 $\frac{r}{R-r}$，再用 C++ 内置的 asin 函数求出度数即可。

本题有一个细节就是浮点数比较大小，通常加上一个特别小的数再进行比较。

## 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;

#define P 3.14159265358

int main()
{
	double n, R, r;
	cin >> n >> R >> r;
	if (n <= 2)     //特判
		cout<<((R >= n * r) ? "YES" : "NO");
	else 
	    cout << (((P / asin(r / (R - r))) + 0.000000001 > n)   ? "YES" : "NO");    //防止精度错误。
}
```

---

## 作者：Graph_Theory (赞：0)

### 思路
对于每一个盘子都和桌子边挨着所以我们可以想一个夹子，夹住每一个盘子，最后我们只要用 $360^{\circ}$ 除以一个夹子的角度计算最多数量的夹子与 $n$ 比较即可。

这里注意浮点数计算时不应该直接比较，应该增加一个可接受的误差值或者两数相减与误差值比较。
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

#define Pi 3.14159265359

double n, R, r;
int main()
{
	cin >> n >> R >> r;
	if(n<=2) return puts((    (R>=n*r)  ?"YES":"NO")),0;
	cout << ((   (Pi / asin(r /(R - r)))     + 0.000000001 > n) ? "YES" : "NO");
}
```

---

## 作者：Zooping (赞：0)

题目传送门： [CF140A New Year Table](https://www.luogu.com.cn/problem/CF140A) 。

让我们用几何方法来求解这道题吧[手动滑稽。


**一般地**，只要 $R$ 大于最小值，桌面上就一定可以摆下所有盘子，所以我们只要求出 ${R}_{min}$ 即可。

那我们先画图。

如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/drmmkaxb.png)





依次连接相邻的两个圆心，发现它们构成了一个正 $n$ 边形。

由 $n$ 边形内角和公式求得每个内角都是 $\frac{(n-2)}{n}·\pi$   （即图中 $\angle IDF , n=1 , 2$ 之后特判）。

上面结果除以 $2$ 求出 $\angle MDO$ 度数。

$\angle MDO = \frac{\frac{(n-2)}{n}·\pi}{2}=\frac{(n-2)}{2n}·\pi$

再通过三角函数求 $DO$ 长度

$\because DM \perp D''O$

$\therefore DO=\frac{DM}{cos(\angle MDO)}$

最短长度就是 $DO+BD=\frac{r}{cos(\frac{(n-2)}{2n}·\pi)}+r$。

最后与 $R$ 比较。





当 $n=1 , 2$ 时，画不出 $n$ 边形来，所以几何法不适用，直接特判即可。

```cpp
#include<cmath>
#include <iostream>
using namespace std;
const double pi = 3.14159265358979323846264;
int main()
{
    double R, r;
    int n;
    cin >> n >> R >> r;
    if (n <= 2)//特判
    {
        if (R >= n * r)cout << "YES";
        else cout << "NO";
        return 0;
    }

    if (R + 1e-7 < (r / cos((n - 2) * 0.5 * pi / n) + r))//注意精度
        cout << "NO";
    else
        cout << "YES";
    return 0;
}

```

#### 结尾
这题竟然没卡精度上，一遍过诶。


---

