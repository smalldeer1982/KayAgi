# Lucky Days

## 题目描述

Bob and Alice are often participating in various programming competitions. Like many competitive programmers, Alice and Bob have good and bad days. They noticed, that their lucky and unlucky days are repeating with some period. For example, for Alice days $ [l_a; r_a] $ are lucky, then there are some unlucky days: $ [r_a + 1; l_a + t_a - 1] $ , and then there are lucky days again: $ [l_a + t_a; r_a + t_a] $ and so on. In other words, the day is lucky for Alice if it lies in the segment $ [l_a + k t_a; r_a + k t_a] $ for some non-negative integer $ k $ .

The Bob's lucky day have similar structure, however the parameters of his sequence are different: $ l_b $ , $ r_b $ , $ t_b $ . So a day is a lucky for Bob if it lies in a segment $ [l_b + k t_b; r_b + k t_b] $ , for some non-negative integer $ k $ .

Alice and Bob want to participate in team competitions together and so they want to find out what is the largest possible number of consecutive days, which are lucky for both Alice and Bob.

## 说明/提示

The graphs below correspond to the two sample tests and show the lucky and unlucky days of Alice and Bob as well as the possible solutions for these tests.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1055C/19d7a3762431cf8ed7d41c7aa787eb194dc6ab47.png)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1055C/dee255111b7c12483568555df6c88766f900f855.png)

## 样例 #1

### 输入

```
0 2 5
1 3 5
```

### 输出

```
2
```

## 样例 #2

### 输入

```
0 1 3
2 3 6
```

### 输出

```
1
```

# 题解

## 作者：an_da (赞：3)


[更好的观感](http://wyqz.top/p/4188452413.html)

# 思路

题目要求两个区间的重合度最大的长度。

首先第一个点我们要想到：要想使两个区间的重合度最高，需要让两个区间尽可能逼近。最优的情况就是两个区间的 **左端点尽可能相等** ，这样重合度是最大的。

即使  $la + x \times ta = lb + y \times tb$

将式子进行移项得 $x \times ta - y \times tb = lb - la$  （此时我们假设$la < lb$，代码中已做相关的操作，这样只是为了方便）

我们需要看式子是否有解，式子结构和 **裴蜀定理** 比较像，拿出来进行对比。

裴蜀定理 ： 存在整数 $x, y$ ，满足 $a \times x + b \times y = \gcd(a,b)$

 该式子进行 $y$ 符号变为正，表示 $y$ 是整数，则 $x \times ta + y \times tb = lb - la$

我们令 $d = \gcd(ta, tb)$

那么可以发现如果 $d | (lb - la)$，则该式子有解，左端点可以重合。

---

但是如果左端点不能重合怎么办，尽可能逼近就行。

此时别忘了式子右边的 $lb-la$ 代表的是什么，是 **区间a左端点移动的距离**，那么因为 $x \times ta + y \times tb = d$ 是存在解的，则**区间a移动的距离可进一步变为**  $d$ 。

> 注意：我说的区间a可以移动，是指的一定存在某种状态，上下两个人有两个区间的距离发生了变化，叫为区间移动更容易理解。如
>
>  $ta = 3,[1,4]->[4,7]->[7,10]->[10,13]$
>
>  $tb = 4,[3,5]->[7,9]->[11,13]$
>
>  $[1,4][3,5]$ 左端点相差 $2$，这是一种区间状态，通过移动，会出现另一种区间状态 $[10,13][11,13]$ 左端点相差 $1$ 。移动了一步（ $d = \gcd(3,4) = 1$ ）

左端点不重合就尽可能逼近。

有两种状态可能是合适的。

> $dis$ 代表a区间左端点与b区间左端点相差的最小距离（a区间左端点我认为小于等于b区间左端点），即 $dis = (lb - la) \bmod d$

- 区间a左端点移动到和区间b左端点相差 $(lb-la) \bmod d$，可能是距离最近的
  -  $min(rb - lb + 1, ra - la + 1 - dis)$

- 然后是上面的情况在往后移一步，即区间a左端点超过区间b左端点 $d-(lb-la)\bmod d$

  - $dis = d - dis$ 
  
  - $min(ra - la + 1, rb - lb + 1 - dis)$

> 两个计算请画图领悟计算方法。
>
> 计算：左端点重合的情况可以合并在左端点能合并的代码里面，即左端点合并是左端点不合并的特殊情况。



# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int N = 1e5 + 5, mod = 1e9 + 7;

// [l[a] + k * ta, r[a] + k * ta]
// 3 [1, 4] [4, 7] [7, 10] [10, 13] [13, 16] ---
// 4 [3, 5] [7, 9] [11, 13]         [15, 17] ---
// 起点尽可能相同
// 裴蜀定理：存在x,y 使 ax + by = gcd(a, b)
// la + x * ta = lb + y * tb
// x * ta - y * tb = lb - la
// gcd(ta, tb) | (lb - la)有解
// d = gcd(ta, tb) 看成相对移动的距离
// la -> la + d -> la + k * d    lb
// 差 = lb - la 
// dis = (lb - la) % d

void solve()
{
	int la, ra, ta, lb, rb, tb;
	cin >> la >> ra >> ta >> lb >> rb >> tb;
	if(la > lb)
	{
		swap(la, lb);
		swap(ra, rb);
		swap(ta, tb);
	}
	int d = __gcd(ta, tb);
	int dis = (lb - la) % d; // 左端点的差
	int ans = 0;
	ans = max(ans, min(rb - lb + 1, ra - la + 1 - dis));
	dis = d - dis; // 向右移动一步
	ans = max(ans, min(ra - la + 1, rb - lb + 1 - dis));
	cout << ans << "\n";
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int t;
	// cin >> t;
	t = 1;
	while(t--)
		solve();
	return 0;
}
```




---

## 作者：liujiaxi123456 (赞：1)

## [\*CF1055C -- Lucky Days](https://www.luogu.com.cn/problem/CF1055C)

很有意思的题。

可以考虑从**特殊情况入手**，再推广：

- **特殊情况会有很多，尽量从多方面思考。**

- 假设两个区间的长度是相等的，此时就要让左/右端点尽可能的靠近。

- 写成式子：$l_1+k_1t_1 = l_2+k_2t_2 $，根据裴蜀定理，有整数解当且仅当 $(t_1, t_2)|l_2-l_1 $。

- 相当于可以将两个区间的左端点的距离变化多次 gcd。

- 求左端点距离最小多少即可。

推广：

- 发现只是两个区间在左端点对不齐时，靠左/右有一定的区别。

- 分讨一下即可。

**总结：**

- 特殊情况关键是在于给一个**入手/分析的方向**。

- 比如这道题是让我们注重观察单个端点之间的变化，而不是整个区间。

Code:
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

// const int Maxn = ;

namespace Josh_zmf {
	
	int l1, r1, l2, r2, t1, t2;

	inline int main() {
		cin>> l1>> r1>> t1>> l2>> r2>> t2;
		if(l1 > l2)	swap(l1, l2), swap(r1, r2), swap(t1, t2);
		int k = __gcd(t1, t2), len = l2-l1;
		int move = len/k*k;
		int ans = min(r1, r2-move) - max(l1, l2-move) + 1;
		move += k;
		ans = max(ans, min(r1, r2-move)-max(l1, l2-move)+1);
		cout<< max(ans, 0)<< '\n';
		return 0;
	}

}

int main() {
	Josh_zmf::main();
	return 0;
}
```

---

## 作者：gcwixsxr (赞：0)

### [CF1055C Lucky Days](https://www.luogu.com.cn/problem/CF1055C)

题目大意：给定 $l_a,r_a,t_a,l_b,r_b,t_b$，对于所有的非负整数 $k$，将区间 $[l_a+kt_a,r_a+kt_a]$ 打上标记 $1$，将区间 $[l_b+kt_b,r_b+kt_b]$ 打上标记 $2$。求出最长的连续区间使得该区间中的所有位置都被同时打上的 $1,2$ 标记。

数据范围：$1\leq l_a,r_a,t_a,l_b,r_b,t_b\leq 10^9$。

由题意，两个区间的循环分别为 $t_a,t_b$。由裴蜀定理可以知道，存在 $x,y,p$ ，使得 $xt_a+yt_b=p\gcd(t_a,t_b)$。换言之，存在一种位置，使得两个区间的**相对位置**相较初始的**相对位置**移动了 $\gcd(t_a,t_b)$。

举个例子，$l_a=0,r_a=2,t_a=4,l_b=1.r_b=4,t_b=6$，如下图。

![](https://cdn.luogu.com.cn/upload/image_hosting/ewl6vj1s.png)

此时其相对位置我们定义为两个区间循环若干次后左端点相减，那么初始位置的相对位置就是 $l_b-l_a=1$，由于 $\gcd(t_a,t_b)=2$，也就意味着其相对位置可以移动 $2$ ，相对位置变为 $-1$，也就是后面那种情况。实际上，$[l_a+2t_a,r_a+2t_a]$ 和 $[l_b+1t_b,r_b+1t_b]$ 的相对位置正是 $-1$。

那么，要使两个阴影部分重合最大，使左端点尽可能对齐即可。

```cpp
#include<cstdio>
#include<iostream>
#include<set>

using namespace std;

int l1,r1,t1,l2,r2,t2;
int gcd(int x,int y){
	return x==0?y:gcd(y%x,x);
}
int step,dis,ans;
int main(){
	scanf("%d%d%d%d%d%d",&l1,&r1,&t1,&l2,&r2,&t2);
	step=gcd(t1,t2);
	dis=((l2-l1)%step+step)%step;
	ans=max(ans,min(l2-dis+r1-l1-l2+1,r2-l2+1));
	dis-=step;
	ans=max(ans,min(r2-(l2-dis)+1,r1-l1+1));
	printf("%d\n",ans);
	return 0;
}
 
```


---

