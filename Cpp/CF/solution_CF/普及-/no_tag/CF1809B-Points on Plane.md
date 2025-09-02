# Points on Plane

## 题目描述

You are given a two-dimensional plane, and you need to place $ n $ chips on it.

You can place a chip only at a point with integer coordinates. The cost of placing a chip at the point $ (x, y) $ is equal to $ |x| + |y| $ (where $ |a| $ is the absolute value of $ a $ ).

The cost of placing $ n $ chips is equal to the maximum among the costs of each chip.

You need to place $ n $ chips on the plane in such a way that the Euclidean distance between each pair of chips is strictly greater than $ 1 $ , and the cost is the minimum possible.

## 说明/提示

In the first test case, you can place the only chip at point $ (0, 0) $ with total cost equal to $ 0 + 0 = 0 $ .

In the second test case, you can, for example, place chips at points $ (-1, 0) $ , $ (0, 1) $ and $ (1, 0) $ with costs $ |-1| + |0| = 1 $ , $ |0| + |1| = 1 $ and $ |0| + |1| = 1 $ . Distance between each pair of chips is greater than $ 1 $ (for example, distance between $ (-1, 0) $ and $ (0, 1) $ is equal to $ \sqrt{2} $ ). The total cost is equal to $ \max(1, 1, 1) = 1 $ .

In the third test case, you can, for example, place chips at points $ (-1, -1) $ , $ (-1, 1) $ , $ (1, 1) $ , $ (0, 0) $ and $ (0, 2) $ . The total cost is equal to $ \max(2, 2, 2, 0, 2) = 2 $ .

## 样例 #1

### 输入

```
4
1
3
5
975461057789971042```

### 输出

```
0
1
2
987654321```

# 题解

## 作者：听取MLE声一片 (赞：7)

考虑转化，因为点都是整点，欧几里得距离大于 $1$ 也就是每对点最近都要是在单位正方形的斜对顶点上。$|x|+|y|\leq d$ 的点即为曼哈顿距离不大于 $d$ 点。

因为要问这个 $d$ 的最小值为多少才能填上 $n$ 个点，可以求出每个 $d$ 最多能填多少。

每对点的欧几里得距离大于 $1$，也就是说，我们要尽可能多的放置单位正方形的斜对顶点才最优，而且要从最外围开始放，否则一定会产生浪费。

这是 $d=3$ 的最优填法。

![](https://cdn.luogu.com.cn/upload/image_hosting/xnpztlk0.png)

观察发现，这是边长为 $4$ 的正方形，是否对于 $d$ 最多就能填 $(d+1)^2$ 个呢？

考虑这样一种方案，对 $|x|+|y|$ 的奇偶性分类，只选奇偶性相同的点一定满足欧几里得距离限制，最多能填的数量即为奇个数和偶个数的最大值。因为与 $d$ 奇偶性相同的点在最外面有一圈，所以答案即为与 $d$ 奇偶性相同的点的个数。这些点构成一个边长为 $d+1$ 的正方形，答案即为 $(d+1)^2$。

然后只需要求最小的 $d$ 使得 $n\leq(d+1)^2$，答案是$\lceil \sqrt n \rceil -1$ 可以直接用 `sqrtl`，但我当时用的二分。

代码很简单就不放了。


---

## 作者：jhdrgfj (赞：4)

$2023.4.3$ 添加了一些空格。
## 题目大意

你需要在平面直角坐标系放置 $n$ 个点，放在 $(x,y)$ 的点的代价为 $\left\vert x \right\vert + \left\vert y \right\vert$。定义总代价为所有点中代价最高的点的代价，求总代价？

## 思路

不难想到最好的放置方法如下图。
![](https://cdn.luogu.com.cn/upload/image_hosting/9g8ytz81.png)
但如何求出对每个 $n$ 最优的代价呢？让我们逆向思考，对每个给定的代价 $x$ 最多能放多少个点呢？将上图旋转 $45 ^ \circ$，可得到下图。
![](https://cdn.luogu.com.cn/upload/image_hosting/uf4bco9e.png)
上图所使用的代价为 $3$，而放置的点数为 $(3 + 1) ^ 2 = 16$。所以可以推出总代价为 $x$ 时可放置 $(x + 1) ^ 2$ 个点。则 $n$ 个点所需的代价为 $\sqrt{n} - 1$。

还需强调的一点是，由于数据范围太大，所以 C++ 里内置的开根函数会掉精度，所以必须要手写二分开根。

## 上代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long int ef(long long int a){    //开根函数
	__int128 l=0,r=a,mid=a/2ll;     //由于 longlong 在判断时会溢出，所以用__int128
	while (l<r){
		if (mid*mid<a){
			l=mid+1;
		}else if (mid*mid>=a){
			r=mid-1;
		}
		mid=(l+r+1)/2;
	}
    	long long int c=l;
    	if (c*c<a) return c+1;    //由于我们要求的是向上取整的根，所以要防止我的玄学开根返回向下取整的根
	return c;
} 
int main()
{
	long long int t,n;
	cin>>t;
	while (t--){
		cin>>n;
		cout<<ef(n)-1<<endl;    //调用开根函数，然后减 1
	}
}
```

---

## 作者：Terry2011 (赞：1)

# 题目解析
因为要使得每对棋子之间的欧几里得距离严格大于 $1$，且成本尽可能小。

所以，我们要让每个点尽可能地靠近原点，且点和点之间的直线距离大于 $1$，
也可以说互不相邻。想到了什么？
```   
      1
    1 1 1
  1 1 1 1 1
1 1 1 1 1 1 1
  1 1 1 1 1
    1 1 1
      1
```
倒过来看，一个完美的正方形。所以，输出 $\lfloor \sqrt{n-1}\rfloor$ 即可
# Code
```
#include<bits/stdc++.h>
using namespace std;
int main() {
  int t;
  cin >> t;
  while(t--) {
    long long n; //不开long long见祖宗
    cin >> n;
    cout << (long long)sqrt(n - 1) << endl;
  }
  return 0;
}
```

---

## 作者：Miyamizu_Mitsuha (赞：0)

## 思路 
对于欧几里得距离严格大于 $1$ 的限制，我们可以采用一种最节约空间的方法来放置点，即将点按照单位正方形的对角线排列。这样每个点与相邻点的距离为 $\sqrt{2}$，同时也是最节省空间的排列方式。
排列点后，我们可以观察到这些点形成了一个网状结构，每个正方形边长是 $\sqrt{n}$ 个点，而里面的点个数是 $n$ 的平方。
我们已经知道点的个数 $n$，现在要求最小花费。根据观察，花费比边长小 $1$，所以答案为 $\lfloor \sqrt{n-1} \rfloor$。

## 代码

```cpp
#include <iostream>
#include <cmath>

using namespace std;

int main() {
  int t;
  cin >> t;
  while(t--) {
    long long n; //不开ll见祖宗
    cin >> n;
    cout << (long long)sqrt(n - 1) << endl;
  }
  return 0;
}
```




---

## 作者：xiaofeng_and_xiaoyu (赞：0)

很明显题目的填法是按照菱形来填为最优解，下面给个例子（数字表示成本）：
```cpp
	  3
   3 2 3
  3 2 1 2 3
3 2 1 0 1 2 3
  3 2 1 2 3
   3 2 3
	  3
```
（不知道为什么对不齐，将就看吧……）

不难发现，成本的个数表示为平方数。

所以要想还原，就要把它开根。

但是！！

每队棋子的欧几里得的范围要严格大于 $1$，而且又是在格点上，所以只需要判断为在对角线上距离为 $\sqrt{2}$ 的就可以了。

数据已经给出，只需要依次判断是否小于 $1,4,9\dots$ 就可以了。

同时还可以发现，成本是个数开根的结果，所以直接输出符合要求数字的根就可以了。

由于$\sqrt{10^{18}}= 10^{9}$，在 int 范围内，所以开根后的结果保留 int 类型就可以了。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	long long int n,s;
    cin>>n;
   	while(n--){
   		cin>>s;
   		s-=1;//减1是因为当他为平方数时，正好为上一级的个数，做出特判就行
    cout<<int(sqrt(s))<<endl;
	}
    return 0;
}
```



---

## 作者：隐仞Mrsu (赞：0)

# 题意
在平面直角坐标系上选择 $n$ 个**坐标值为整数**的点，满足点与点之间的欧几里得距离大于一，使得总花费最小。

选择一个点 $(x,y)$ 的花费为 $\lvert x\rvert+\lvert y\rvert$。

选择 $n$ 个点的总花费为每个点花费的最大值。

# 分析
有两个点 $(x_1,y_1)\ (x_2,y_2)$，则两者之间的欧几里得距离为 $\sqrt{(x_1-x_2)^2+(y_1-y_2)^2}$。

要使点与点之间的欧几里得距离严格大于一，任意两点不能在坐标轴方向上相邻。

当 $n=1$ 时，只用选择一个点，则选择**坐标原点**使得答案最小。

再分析 $n=2$ 时，如果在坐标原点上选择一个点，另外一个点只能选到 $(\pm 1,\pm 1)$ 或者 $(0,\pm 2)$ 还有 $(\pm 2,0)$。此时答案为二，并非最小值。当选择 $(1,0)$ 和 $(0,1)$ 时，满足条件，答案为一，是最小的。

于是，对于 $2\le n\le 4$，我们可以在 $(1,0)\ (0,1)\ (-1,0)\ (0,-1)$进行选择，即选择 $\lvert x\rvert+\lvert y\rvert=1$ 的点。

当 $5\le n\le 9$，由于 $\lvert x\rvert+\lvert y\rvert=1$ 的点只有四个，不够用。于是，我们先选择 $(0,0)$，然后在 $\lvert x\rvert+\lvert y\rvert=2$ 的八个点中进行选择，答案为二。

当 $10\le n\le 16$，我们在，然后在 $\lvert x\rvert+\lvert y\rvert=1$ 四个点的基础上，再在 $\lvert x\rvert+\lvert y\rvert=3$ 的十二个点中进行选择，答案为三。

以此类推，发现规律如下。

```
n=1 => 0
2<=n<=4 => 1
5<=n<=9 => 2
10<=n<=16 => 3
17<=n<=25 => 4
......
```
于是，答案 $cost=\lfloor\sqrt{n-1}\rfloor$。

# 代码

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
LL _,n;
void work(){
	cin>>n;
	LL res=sqrt(n-1);
	cout<<res<<'\n';
}
int main(){
	ios::sync_with_stdio(false);
	cin>>_;
	while(_--){
		work();
	} 
}
```


---

## 作者：Iniaugoty (赞：0)

题目[传送门 1](/problem/CF1809B)，[传送门 2](https://codeforces.com/problemset/problem/1809/B)。

简单题，~~珂以乱搞过~~。

***

## 题意

坐标为 $(x,y)$ 的点的权值为 $\lvert x\rvert+\lvert y\rvert$，$n$ 个点的权值为每个点权值的最大值。现在要将 $n$ 个点放在平面直角坐标系上，使得每个点都是整点，且两点间的欧几里得距离都**严格大于** $1$，求出 $n$ 个点的权值最小多大。

***

## 解法 1：乱搞

~~乱搞是一种做 CF 思维题的好方法！~~

在第四种数据中，输出结果为 $987654321$，非常巧妙的数字。说明什么？出题人可能是先出了输出数据，再据此反推出了输入的 $975461057789971042$。于是，这道题很有可能存在一个 $\operatorname O(1)$ 的通项公式，可以快速算出结果，并根据答案反推输入。

打开计算器，很容易发现：

$$987654321^2+1=975461057789971042$$

即答案为 $\sqrt{n-1}$。

或者：

$$\lfloor\sqrt{975461057789971042}\rfloor=987654321$$

即答案为 $\lfloor\sqrt{n}\rfloor$。

又或者：

$$\lceil\sqrt{975461057789971042}\rceil-1=987654321$$

即答案为 $\lceil\sqrt{n}\rceil-1$。

显然，第一式不一定能得到整数解，由题意知答案为整数，所以是错的。

把其他三组数据带进第二式，发现也有误。

而第三式是都符合的。于是你可以快乐的 AC 这道题。

事实上，经过推导，正确答案也是 $\lceil\sqrt{n}\rceil-1$。

***

## 解法 2：正儿八经做

容易发现，一个点的权值 $\lvert x\rvert+\lvert y\rvert$ 其实就是这个点到坐标原点的曼哈顿距离。

那么题目转化成：求出一个 $d$，使得存在 $n$ 个整点，每个整点到原点的曼哈顿距离不大于 $d$。

考虑**贪心**，点尽可能地靠近原点放。

自己手动模拟几下，可以发现，当 $n$ 为偶完全平方数时，放下的点一定组成一个斜的方阵，那么 $d=\sqrt{n}-1$。

当 $n$ 为其他情况时，放下的点可以看成 $m$ 个点中去掉最外边一些，$d$ 一定是 $\sqrt{m}-1$，其中 $m$ 是大于 $n$ 的最小偶完全平方数。

所以答案为 $\lceil\sqrt{n}\rceil-1$。

***

## 代码

非常短。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n;
signed main(){
	scanf("%lld",&t);
	while(t--){
		scanf("%lld",&n);
		printf("%lld\n",(long long)ceil((long double)sqrtl(n))-1);
	}
	return 0;
}
```

***

全文完。

---

