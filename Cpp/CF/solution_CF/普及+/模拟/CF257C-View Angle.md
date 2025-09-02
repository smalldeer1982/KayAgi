# View Angle

## 题目描述

Flatland has recently introduced a new type of an eye check for the driver's licence. The check goes like that: there is a plane with mannequins standing on it. You should tell the value of the minimum angle with the vertex at the origin of coordinates and with all mannequins standing inside or on the boarder of this angle.

As you spend lots of time "glued to the screen", your vision is impaired. So you have to write a program that will pass the check for you.

## 说明/提示

Solution for the first sample test is shown below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF257C/52a22a58227cc8e3cd175061056d878bb5e11b91.png)Solution for the second sample test is shown below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF257C/ec228a55fc379b89df62107b0fadfa9651c34033.png)Solution for the third sample test is shown below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF257C/477a3f097accae6f2425e7d37a546ed3af1f9885.png)Solution for the fourth sample test is shown below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF257C/8ce489535c5d9f609dbb5be22269ebed1502e2d2.png)

## 样例 #1

### 输入

```
2
2 0
0 2
```

### 输出

```
90.0000000000
```

## 样例 #2

### 输入

```
3
2 0
0 2
-2 2
```

### 输出

```
135.0000000000
```

## 样例 #3

### 输入

```
4
2 0
0 2
-2 0
0 -2
```

### 输出

```
270.0000000000
```

## 样例 #4

### 输入

```
2
2 1
1 2
```

### 输出

```
36.8698976458
```

# 题解

## 作者：Special_Tony (赞：3)

# 思路
其实我们可以把这个平面看成一个圆，然后需要切除一部分并使所有点不被切除，此时显然我们只能切掉任意**相邻的**两个点之间的夹角才能不伤及无辜。注意因为是平面，所以头尾间的夹角也要考虑。

这题的难点在于如何计算夹角。但是好在 c++ 提供了一个很好用的函数：`atan2`。`atan2(y,x)` 可以自动求出坐标位于 $(x,y)$ 的点与原点的夹角。另外记住这个函数它会返回弧度，如果要转换为角度请自行乘上 $\frac{180}\pi$。

至于 $\pi$ 怎么求，那你可以自己背出精度较高的 $\pi$（前提条件别被错），也可以使用 c++ 自带的 `acos(-1)`。

[Code](https://codeforces.com/problemset/submission/257/264208693)。

---

## 作者：Y_QWQ_Y (赞：2)

多背函数没烦恼。

直接请出 C++ 库函数：`atan2(y,x)`。这个函数的作用就是计算点 $(x,y)$ 与原点的夹角，但由于返回值为弧度，所以乘上 $\frac{180}{\pi}$ 即可。

关于 $\pi$，可以背，也可以用 C++ 库函数 `acos(-1)` 表示。

那么代码就显而易见了。
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n;
double x, y, a[100005], ans;
signed main ()
{
	ios::sync_with_stdio (0), cin.tie (0), cout.tie (0);
	cin >> n;
	for (int i = 0; i < n; ++ i)
	{
		cin >> x >> y;
		a[i] = atan2 (y, x) * 180 / acos (- 1);
	}
	sort (a, a + n);
	ans = 360 - a[n - 1] + a[0];
	for (int i = 0; i < n - 1; ++ i)ans = max (ans, a[i + 1] - a[i]);
	cout << fixed << setprecision (12) << 360 - ans;//记得输出多位小数
	return 0;
}
```

---

## 作者：迟暮天复明 (赞：2)

[题面](https://codeforces.com/contest/257/problem/C)

[没说更好的阅读体验](https://www.cnblogs.com/1358id/p/16292584.html)

Description:

平面上有 $n(1\leq n\leq 10^5)$ 个点。你要从原点引出两条射线，将平面分成两个部分，保证其中一个部分覆盖了所有的点。问这个部分与原点所夹的角的最小度数。

-----
正难则反。我们可以把问题转化为求一个部分不包含所有的点，问这个部分在原点的角度最大值。

用贪心的思想，这个部分的两条射线肯定要经过点，否则一定不是最优。而且，这两个点之间不能有任何点。所以，我们可以把点的坐标转化为角度。这样的话，我们要找的两个点在把角度排序后一定相邻。因此，我们把角度排序，每一次找相邻的两个点的夹角，不断更新最大值即可。最终的答案就是 $360^\circ$ 减去这个最大值。注意第一个点和最后一个点夹角的处理。

在数学库中，$\operatorname{atan2}$ 函数可以方便地求出 $\arctan(\dfrac{y}{x})$ 的值。注意传参进去的时候先纵后横，并且出来的值是弧度。你可以用 $\operatorname{atan2}(y,x)\times180\div\pi$ 得到经过点 $(x,y)$ 和原点的射线与 $x$ 的夹角度数。

[代码](https://paste.ubuntu.com/p/3q3bF3JwDG/)

---

## 作者：RainWorld_XIV (赞：0)

[更好的阅读体验](https://www.cnblogs.com/MithrilSwordXIV/p/18345903)

[题目传送门](https://www.luogu.com.cn/problem/CF257C)

## 题意

平面上有 $n$ 个点。从原点引出两条射线，将平面分成两个部分，使其中一个部分覆盖所有的点。求这个部分与原点所夹的角的最小度数。

## 思路

既然一个部分覆盖了所有的点，那么另一个部分就一个点都没覆盖，那么要让这个部分最优，这两条射线一定经过两个中间没有任何点的点。那么我们就可以先求出所有点与 $x$ 轴正半轴的夹角度数，再将这些度数排序，可以看出排完序后相邻的两个点间是没有其他点的。

然后我们只需要算出所有相邻点间的度数取最大值即可，但不要忘了这时一个点也没有覆盖的部分的角度，答案还需要用 $360\degree$ 再减一下。

那么怎么求角度呢？我们已经知道了这个点的坐标 $(x,y)$，由数学知识可得角度即为 $\arctan(\dfrac{y}{x})$。看到题解区其他大佬用的都是 $\text{atan2}$ 这个函数求的角度，蒟蒻的我第一反应想到的是 $\text{atan}$。

由于 $\text{atan}$ 返回的是与 $x$ 轴以弧度为单位的角度，并且当点在一三象限时是正值，在二四象限时是负值，而 $\text{atan2}$ 返回的是与 $x$ 轴**正半轴**以弧度为单位的角度，并且点在 $x$ 轴上方时为正，在 $x$ 轴下方时为负。因此当点在二三象限时我们需要对 $\text{atan}$ 函数返回值进行处理，具体见代码。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long 
#define MAX 100005
using namespace std;
const double p=acos(-1);
int n;
double ans,at[MAX];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1,x,y;i<=n;i++){
		cin>>x>>y;
		at[i]=atan(double(y*1.0/x))*180/p;//弧度不要忘了乘上180/π
		if(x<0&&y==0)at[i]=180;//如果点在x负半轴上，度数为180 
		if(x<0&&y<0)at[i]=at[i]-180;//点在第三象限 
		if(x<0&&y>0)at[i]=at[i]+180;//点在第二象限 
		//如果不理解可以手造几组数据输出一下看看结果 
	}
	sort(at+1,at+1+n);
	ans=360-(at[n]-at[1]);
	for(int i=1;i<=n-1;i++)ans=max(ans,at[i+1]-at[i]);
	cout<<fixed<<setprecision(10)<<360-ans<<'\n';
	return 0;
}
```

---

