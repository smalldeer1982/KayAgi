# Ghosts

## 题目描述

Ghosts live in harmony and peace, they travel the space without any purpose other than scare whoever stands in their way.

There are $ n $ ghosts in the universe, they move in the $ OXY $ plane, each one of them has its own velocity that does not change in time: $ \overrightarrow{V} = V_{x}\overrightarrow{i} + V_{y}\overrightarrow{j} $ where $ V_{x} $ is its speed on the $ x $ -axis and $ V_{y} $ is on the $ y $ -axis.

A ghost $ i $ has experience value $ EX_i $ , which represent how many ghosts tried to scare him in his past. Two ghosts scare each other if they were in the same cartesian point at a moment of time.

As the ghosts move with constant speed, after some moment of time there will be no further scaring (what a relief!) and the experience of ghost kind $ GX = \sum_{i=1}^{n} EX_i $ will never increase.

Tameem is a red giant, he took a picture of the cartesian plane at a certain moment of time $ T $ , and magically all the ghosts were aligned on a line of the form $ y = a \cdot x + b $ . You have to compute what will be the experience index of the ghost kind $ GX $ in the indefinite future, this is your task for today.

Note that when Tameem took the picture, $ GX $ may already be greater than $ 0 $ , because many ghosts may have scared one another at any moment between $ [-\infty, T] $ .

## 说明/提示

There are four collisions $ (1,2,T-0.5) $ , $ (1,3,T-1) $ , $ (2,4,T+1) $ , $ (3,4,T+0.5) $ , where $ (u,v,t) $ means a collision happened between ghosts $ u $ and $ v $ at moment $ t $ . At each collision, each ghost gained one experience point, this means that $ GX = 4 \cdot 2 = 8 $ .

In the second test, all points will collide when $ t = T + 1 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF975D/d912223a1fc5da70d046e3cc6e21283e2634fbe3.png)The red arrow represents the 1-st ghost velocity, orange represents the 2-nd ghost velocity, and blue represents the 3-rd ghost velocity.

## 样例 #1

### 输入

```
4 1 1
1 -1 -1
2 1 1
3 1 1
4 -1 -1
```

### 输出

```
8
```

## 样例 #2

### 输入

```
3 1 0
-1 1 0
0 0 -1
1 -1 -2
```

### 输出

```
6
```

## 样例 #3

### 输入

```
3 1 0
0 0 0
1 0 0
2 0 0
```

### 输出

```
0
```

# 题解

## 作者：是个汉子 (赞：6)

~~吐槽一句，这题是绿的就离谱。~~

### 题意

给一条直线的斜率 $a$ 和截距 $b$ ，和某一时刻 $n$ 个在直线上的点的横坐标，还有每个点沿坐标轴的速度 $v_x,v_y$ 。

问这些点在 $(-\infty,+\infty)$ 的时间内的碰撞次数。

### Solution

设某两个点在时间 $t$ 发生了碰撞，则有：
$$
x_1+v_{x1}t=x_2+v_{x2}t\\y_1+v_{y1}t=y_2+v_{y2}t
$$
移项+消去 $t$ ，可得：
$$
\dfrac {x_1-x_2}{v_{x2}-v_{x1}}=\frac {y_1-y_2}{v_{y2}-v_{y1}}
$$
又由某个斜率的表达式 $k=\frac {y_1-y_2}{x_1-x_2}$ ，得到：
$$
\frac {v_{y2}-v_{y1}}{v_{x2}-v_{x1}}=a\Rightarrow v_{y2}-v_{y1}=a\times (v_{x2}-v_{x1})
$$
再次移项，可以得到：
$$
v_{y2}-a\times v_{x2}=v_{y1}-a\times v_{x1}
$$
也就是当两个点满足这个条件时，就会在某个时间发生碰撞。

所以可以开一个 $map$ 记录 $v_y-a\times v_x$ 的数量。但是还有些点，它们的 $v_x,v_y$ 如果相同，是保持相对静止的，所以还要开一个 $map$ 记录这些点，计算的时候减去。

### 代码

```c++
#include<bits/stdc++.h>
#define ll long long
#define PLL pair<ll,ll>

using namespace std;
ll a,b,n,ans;
map<ll,int> mp;
map<PLL,int> same;

int main(){
    scanf("%lld%lld%lld",&n,&a,&b);
    for(int i=1;i<=n;i++){
        ll x,vx,vy;
        scanf("%lld%lld%lld",&x,&vx,&vy);
        ll res=vy-a*vx;
        PLL tmp={vx,vy};
        ans+=mp[res]-same[tmp];
        mp[res]++;da
        same[tmp]++;
    }
    printf("%lld\n",ans*2);//这里乘2是因为ans只记录了会碰撞的点，不是次数
    return 0;   
}
```



---

## 作者：柠檬熟了 (赞：2)

## [Luogu CF975D Ghosts](https://www.luogu.com.cn/problem/CF975D)

比较有趣的一个 Geometry? 迫真 Geometry! 

> 前情提要：
>
> /duel challenge @xxx 2000 geometry *from Meatherm*
>
> 然后 我们都没 *Do* 出来，$Meatherm$ 真男人 *Give Up* 了
>
> 最后被 *zhicheng* **三十秒钟爆切**

### **思路部分**

考虑拍照时 **所有幽灵** 在一条直线上，相当的规范！

那么我们可以想到蛤，任意两只幽灵 **横纵坐标差是成比例的**，比值就是 $a ~~ (\dfrac {y} {x})$。

这下好耍喽，如果要让两个幽灵 **撅到一起**，那么他们的 **相对运动速度** 也得满足这个比例噻。

也就是说 $\dfrac {Vy_i - Vy_j} {Vx_i - Vx_j} = a$ （好好理解，蛤！）

然后简单变形就得到了 $Vy_i - aVx_i = Vy_j - aVx_j$，把 $i,j$ 分开了咩！

后头就好搞了噻，直接把每个 **幽灵** 的这坨东西 $Vy_i - aVx_i$ 算出来。

阔到一个 **unordered\_map** 里头，然后对每只 **幽灵** 查询一遍，加个答案，就好了咩！

真的好了咩？**如好！**

我们少考虑喽一种情况得嘛，如果说啥子 $Vx_i = Vx_j$，上头那个式子分母就莫得咯。

那不就瓜起！所以我们就额外记录一哈每个 **幽灵** 的 $Vx$，开个两维的 **unordered\_map**。

每次加的时候跳过与自己 $Vx$ 相等的 **幽灵** 就好了咩！



### **实现部分**

按上面的思路，肯定有人要这么写嘛（就是我这个瓜货

```cpp
unordered_map <long long, unordered_map<int, int> > mp;
for (int i = 1; i <= N; ++ i) {
    for (auto Mea : mp[P[i].vy - a * P[i].vx]) 
        Ans += Mea.second;
    Ans -= mp[P[i].vy - a * P[i].vx][P[i].vx];
}
```

要这么写肯定给你 T 的哈起，要是所有的 **幽灵** 都在那儿 装怪。

然后 $Vy_i - aVx_i$ 全都相等，那就完了噻，$O(N^2)$ 喽！

啷个办嘛？要像这样！

```cpp
for (auto i : mp) {
    for (auto Mea : i.second) Sum += Mea.second;
    for (auto Mea : i.second) Ans += Mea.second * (Sum - Mea.second);
    Sum = 0;
}
```

很显然噻，阔以再优化一哈。

```cpp
for (auto i : mp) {
    for (auto Mea : i.second) Ans -= 1ll * Mea.second * Mea.second, Sum += Mea.second;
    Ans += Sum * Sum, Sum = 0;
}
```



### **完整代码**

```cpp
#include <bits/stdc++.h>

const int MAXN = 200005;

using namespace std;

struct Node {
	int x, vx, vy;
} P[MAXN];

long long N, a, b, Sum, Ans;
unordered_map <long long, unordered_map<int, int> > mp;

int main () {

	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	
	cin >> N >> a >> b;
	
	for (int i = 1; i <= N; ++ i) 
		cin >> P[i].x >> P[i].vx >> P[i].vy;
	
	for (int i = 1; i <= N; ++ i)
		++ mp[P[i].vy - a * P[i].vx][P[i].vx];
	
	for (auto i : mp) {
		for (auto Mea : i.second) Ans -= 1ll * Mea.second * Mea.second, Sum += Mea.second;
		Ans += Sum * Sum, Sum = 0;
	}
		
	cout << Ans << endl;
	
	return 0;
}

```



---

