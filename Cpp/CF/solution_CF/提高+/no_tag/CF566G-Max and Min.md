# Max and Min

## 题目描述

# 题目背景

有两只特别珂爱的小猫，一个叫做 Min ，另一个叫做 Max 。


今天， Min 和 Max 来玩一个游戏。

游戏开始时，有两个整数。

每只猫都有许多组可以用来玩游戏的数对。

小猫 Max 有 $n$ 对非负整数 $(a_i,b_i)$ ，同理，小猫 Min 也有 $m$ 对非负整数 $(c_j,d_j)$ 。

当轮到小猫 Max 走的时候，它可以选择任何一对 $(a_i,b_i)$ 并将 $x$ 加上 $a_i$ ， $y$ 加上 $b_i$ ；当轮到 Min 的时候，它可以选择任何可用的对 $(c_j,d_j)$ 并把 $x$ 减去 $c_j$ ，把 $y$ 减去 $d_j$ 。

Max 和 Min 可以在不同的移动过程中多次使用每一对。

 Max 先开始游戏。
 
如果在某个时刻 $x,y$ 两个数字同时为负整数，那么 Min 就获胜了！否则，为 Max 获胜。

这两只珂爱的小猫想让你告诉它们，到底谁会赢？假设两只小猫都足够聪明，都会以最优方法来走。

## 说明/提示

在第一个样例中， Min 可以通过移动（3,10）（3,10）对 Max 移动（2,3）（2,3）做出响应，并通过移动（10,3）（10,3）来响应 Max 的移动（3,2）（3,2）的方案。因此，对于每一对最大值和最小值的移动，数字 $x$ 和 $y$ 的值都将严格减小，因此，Min迟早会赢。



在第二个样本测试中，每对最大值和最小值移动后，数字 $x$ 和 $y$ 只会增加，因此它们都不会变为负值。

$1\le n,m\le100000$

$1\le x,y\le10^{9}$

$ 1\le a_{i},b_{i}\le10^{9}$

$ 1\le c_{i},d_{i}\le10^{9}$

## 样例 #1

### 输入

```
2 2
42 43
2 3
3 2
3 10
10 3
```

### 输出

```
Min
```

## 样例 #2

### 输入

```
1 1
1 1
3 4
1 1
```

### 输出

```
Max
```

# 题解

## 作者：Leap_Frog (赞：4)

### P.S.
来更啦，题解一血 get。  

### Description.
博弈，`Min` 有很多向量，`Max` 有很多向量。  
初始位于 $(x_0,y_0)$，`Max` 先手。  
每次可以把当前点加上可以选的任意一个向量，可以选多次。  
`Min` 的目标是把点移动到第三像限，`Max` 的目标是阻止他这样做。  
问谁赢。  

### Solution.
首先，设 `Min` 为攻方，`Max` 为守方。  
因为守方先手，所以如果攻方最后能赢，显然步数和守方一样多，那么可以复制这段过程，使得平面上的任意一个点都是攻方赢。  
于是我们证明了初始点和游戏结果无关。  
然后，相当于如果攻方有一个向量，它能“脱颖而出”，那么攻方就赢了。  
考虑“脱颖而出”需要什么条件，就是存在一个斜率，使得这个斜率移动下来第一个切到的点是这个向量。  
再仔细思考一下这是什么，这就是强制斜率初始不大于零的凸包。  
凸包上的所有点都是“脱颖而出”的。  
具体怎么求有限制的凸包，就直接把当前凸包内 $y$ 坐标小于当前点的弹调即可。 

### Coding.
```cpp
//是啊……你就是那只鬼了……所以被你碰到以后，就轮到我变成鬼了{{{
#include<bits/stdc++.h>
using namespace std;typedef long long ll;
template<typename T>inline void read(T &x)
{
	x=0;char c=getchar(),f=0;
	for(;c<'0'||c>'9';c=getchar()) if(c=='-') f=1;
	for(;c>='0'&&c<='9';c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	if(f) x=-x;
}/*}}}*/
struct pnt
{
	int x,y,id;
	char operator<(pnt b) const {return x^b.x?x<b.x:y>b.y;}
	char operator==(pnt b) const {return x==b.x&&y==b.y&&id==b.id;}
}a[200005],st[200005];
int n,m,tp,zkakioi,xxynb;
inline char chk(pnt a,pnt b,pnt c) {return 1ll*(a.x-b.x)*(b.y-c.y)<1ll*(b.x-c.x)*(a.y-b.y);}
int main()
{
	read(n),read(m),read(zkakioi),read(xxynb);
	for(int i=1;i<=n;i++) read(a[i].x),read(a[i].y),a[i].id=1;
	for(int i=1;i<=m;i++) read(a[i+n].x),read(a[i+n].y);
	sort(a+1,a+n+m+1);int cnt=unique(a+1,a+n+m+1)-a-1;
	for(int i=1;i<=cnt;i++)
	{
		while(tp&&st[tp].y<a[i].y) tp--;
		while(tp>1&&chk(st[tp],st[tp-1],a[i])) tp--;
		st[++tp]=a[i];
	}
	for(int i=1;i<=tp;i++) if(st[i].id) return puts("Max"),0;
	return puts("Min"),0;
}
```

---

