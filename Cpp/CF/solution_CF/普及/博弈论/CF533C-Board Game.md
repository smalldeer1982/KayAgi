# Board Game

## 题目描述

Polycarp and Vasiliy love simple logical games. Today they play a game with infinite chessboard and one pawn for each player. Polycarp and Vasiliy move in turns, Polycarp starts. In each turn Polycarp can move his pawn from cell $ (x,y) $ to $ (x-1,y) $ or $ (x,y-1) $ . Vasiliy can move his pawn from $ (x,y) $ to one of cells: $ (x-1,y),(x-1,y-1) $ and $ (x,y-1) $ . Both players are also allowed to skip move.

There are some additional restrictions — a player is forbidden to move his pawn to a cell with negative $ x $ -coordinate or $ y $ -coordinate or to the cell containing opponent's pawn The winner is the first person to reach cell $ (0,0) $ .

You are given the starting coordinates of both pawns. Determine who will win if both of them play optimally well.

## 说明/提示

In the first sample test Polycarp starts in $ (2,1) $ and will move to $ (1,1) $ in the first turn. No matter what his opponent is doing, in the second turn Polycarp can move to $ (1,0) $ and finally to $ (0,0) $ in the third turn.

## 样例 #1

### 输入

```
2 1 2 2
```

### 输出

```
Polycarp
```

## 样例 #2

### 输入

```
4 7 7 4
```

### 输出

```
Vasiliy
```

# 题解

## 作者：nyC20 (赞：2)

# 思路
Polycarp 的棋子只能往左或往下走，而 Vasiliy 的棋子可以直接往左下走，所以 Vasiliy 是处于优势的，他的最优策略应该是一直往左下走，直到碰到边界才一直往一个方向走。这样，就可以把棋盘上的局势分为以下三种:
1. Vasiliy 的棋子在纵轴上。

2. Vasiliy 的棋子在横轴上。

3. Vasiliy 的棋子既不在纵轴上也不再横轴上。

那么我们对于这三种情况进行特判即可。对于第一种情况，Vasiliy 的棋子离终点的距离是 Vasiliy 棋子的 $y$ 值。对于第二种情况，Vasiliy 的棋子离终点的距离是 Vasiliy 棋子的 $x$ 值。对于第三种情况，Vasiliy 的棋子离终点的距离是 Vasiliy 棋子的 $x$ 值与 $y$ 值相加。

对于上述三种情况，Polycarp 的棋子离终点的距离都是 Polycarp 的棋子的 $x$ 值与 $y$ 值相加。所以只需分三种情况比较两者的棋子离终点的距离，然后由于 Polycarp 先手，所以两者距终点距离相等也是 Polycarp 赢。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int xp, yp, xv, yv;
int main() {
	scanf("%d%d%d%d",&xp,&yp,&xv,&yv);
	if(yv>=xp+yp)printf("Polycarp");//第一种情况 
	else if(xv>=xp+yp)printf("Polycarp");//第二种情况 
	else if(xv>=xp&&yv>=yp)printf("Polycarp");//第三种情况 
	else printf("Vasiliy");//都不是，Vasiliy赢 
	return 0;
}
```

---

## 作者：封禁用户 (赞：1)

### [题目传送门](https://www.luogu.com.cn/problem/CF533C)
---
## 思路
读完题后，可以发现：这是一道大水题。

Polycarp 可以往左或下走，而 Vasiliy 能往左，下或左下走。

可以分类讨论：

1.Polycarp 的 $x$ 和 $y$ 加起来没有 Vasiliy 的 $x$ 大，Polycarp 赢。

2.Polycarp 的 $x$ 和 $y$ 加起来没有 Vasiliy 的 $y$ 大，Polycarp 赢。

3.Polycarp 的 $x$ 和 $y$ 没有对手的 $x$ 和 $y$ 大，Polycarp 赢。

4.其余 Vasiliy 赢。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;

int x1,y1,x2,y2;

int main(){
   cin>>x1>>y1>>x2>>y2;
   
   if(x1+y1<=x2) cout<<"Polycarp";//1.
   else if(x1+y1<=y2) cout<<"Polycarp";//2.
   else if(x1<=x2&&y1<=y2) cout<<"Polycarp";//3.
   else cout<<"Vasiliy";//4.
   
   return 0;
}
```

---

## 作者：Wilderness_ (赞：1)

题目链接：[CodeForces](https://codeforces.com/problemset/problem/533/C) / [Luogu(目前 RMJ 炸了)](https://www.luogu.com.cn/problem/CF533C).

### 思路
首先 $\texttt{Polycarp}$ 和 $\texttt{Vasiliy}$ 两人的下法不同：
- $\texttt{Polycarp}$ 一次移动可以移动到 $(x-1,y)$、$(x,y-1)$ 或者不动。
- $\texttt{Vasiliy}$ 一次移动可以移动到 $(x-1,y)$、$(x-1,y-1)$、$(x,y-1)$ 或者不动。

两人都希望自己赢，那么他们必然不会不动，那么 $\texttt{Vasiliy}$ 由于可以斜着向坐下走（即向 $(x-1,y-1)$ 移动），胜率会大一些。此时我们可以分析枚举 $\texttt{Polycarp}$ 能够胜利的情况来进行判断谁会赢：

1. 当 $Vasiliy_x \ge Polycarp_x+Polycarp_y$ 的时候，那么此时$\texttt{Polycarp}$ 能够胜利（至于取等时，因为 $\texttt{Polycarp}$ 先移动，所以 $\texttt{Polycarp}$ 会比 $\texttt{Vasiliy}$ 快1步）。

![](https://cdn.luogu.com.cn/upload/image_hosting/n9c9g5h1.png)

2. 当 $Vasiliy_y \ge Polycarp_x+Polycarp_y$ 的时候，与第一种情况相似，就不多赘述了。

![](https://cdn.luogu.com.cn/upload/image_hosting/0oxe0hnt.png)

3. 当 $Vasiliy_x \ge Polycarp_x$ 且 $Vasiliy_y \ge Polycarp_y$ 的时候，那么 $\texttt{Polycarp}$ 也能够胜利。

![](https://cdn.luogu.com.cn/upload/image_hosting/jt3d7tg3.png)

简单判断即可。

### Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
long long Px,Py,Vx,Vy;
int main()
{
	scanf("%lld%lld%lld%lld",&Px,&Py,&Vx,&Vy);
	printf((Vy>=Px+Py)||(Vx>=Px+Py)||(Vx>=Px&&Vy>=Py)?"Polycarp\n":"Vasiliy\n");//按照以上3种情况判断
	return 0;//撒花(￣▽￣)
} 
```

---

## 作者：louliu (赞：1)

### [题解传送门](https://www.luogu.com.cn/problem/CF533C)

初看这道题目的时候有点蒙，但细细一想，可以将 Polycarp 和 Vasiliy 的游戏看作是四种情况：

1. Polycarp 占尽了优势， $x$ 轴与 $y$ 轴加起来都没有对方 $x$ 轴大，且 Polycarp 是先手，每人又只能走一步，必赢。

2. 与上同理，只不过将比较的换做了 $y$ 轴。

3. Polycarp 的 $x$ 轴与 $y$ 轴都没有 Vasiliy 的 $x$ 轴与 $y$ 轴大，那 Vasiliy 自然不会超过。

4. 其余情况 Vasiliy 赢。
 
## 代码：
 ```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,c,d;
int main(){
	cin>>a>>b>>c>>d;
	if(a+b<=c)cout<<"Polycarp";//情况一
	else if(a+b<=d)cout<<"Polycarp";//情况二
	else if(a<=c&&b<=d)cout<<"Polycarp";//情况三
	else cout<<"Vasiliy";//情况四
	return 0;
}
```
希望大家能够理解这道题，谢谢！

---

## 作者：Billhqh9 (赞：0)

[AC 记录。](https://codeforces.com/problemset/submission/533/315131726)

## 思路
我们把题目中提到的三种移动方式编个号，下文均用编号简称：
- 法一：从 $(x,y)$ 移动到 $(x-1,y)$；
- 法二：从 $(x,y)$ 移动到 $(x,y-1)$；
- 法二：从 $(x,y)$ 移动到 $(x-1,y-1)$。

结合平面直角坐标系可知，Polycarp 只能用法一和法二，而 Vasiliy 多了法三。Vasiliy 法三一步的过程需要 Polycarp 两步的法一和法二才能实现。所以在不考虑对手的情况下，Polycarp 的最少移动次数是 $x_p+y_p$，而 Vasiliy 的最少移动次数是 $\max(x_v,y_v)$。

那么，Polycarp 想赢，只有这两种情况：
- 直接往终点 $(0,0)$ 移动也比 Vasiliy 快，即 $x_p+y_p \le \max(x_v,y_v)$；
- Polycarp 能在 Vasiliy 的最快路线上卡在 Vasiliy 身前，不让其使用法三，保持自己的领先位置，也就是说出发时 Polycarp 的横纵坐标都小于等于 Vasiliy 的横纵坐标（至于为什么，见下文），即 $x_p \le x_v$ 且 $y_p \le y_v$。


如下图，红色线是 Vasiliy 的最快路线，对于 Polycarp 来说，当其出发点在黄色部分时，极端情况下，如果 Polycarp 从 $A$，$B$，$C$ 或 $D$ 出发，也依然能至少快一步卡在 Vasiliy 的最快路线上。这就说明，当且仅当 Polycarp 的横纵坐标都小于等于 Vasiliy 的横纵坐标时，Polycarp 可以卡住 Vasiliy。  
![](https://pic1.imgdb.cn/item/67fa58c188c538a9b5cc5810.png)

其余的情况一定都是 Vasiliy 赢。

## AC Code
```cpp
#include <iostream>
using namespace std;
int main() {
	int x_p, x_v, y_p, y_v;
	cin >> x_p >> y_p >> x_v >> y_v;
	if(x_p + y_p <= max(x_v, y_v) || (x_p <= x_v && y_p <= y_v))
		cout << "Polycarp" << endl;
	else
		cout << "Vasiliy" << endl;
	return 0;
}
```

---

## 作者：sea_bird (赞：0)

自从 CSP 以来写的第一篇题解。

[题目传送门](https://www.luogu.com.cn/problem/CF533C)。

# 题目分析

这个游戏看上去并不公平，因为 Vasiliy 每次能比 Polycarp 多走一步，就是当**横坐标纵坐标都减少一位**时，因此要保证 Vasiliy 获胜只需**运用他的优势**就可以了，至于题目中可以不动的条件可以忽略，因为为了保证获胜他们必须要保持移动。

接着就是 Polycarp 的获胜条件了，虽然他的移动速度更慢，但是题目说了不能让两个棋子在同一格，这正是 Polycarp 的优势所在，因为他是先手所以他有机会卡住对手的路，而 Vasiliy 则没有。

因此可以做出总结，Polycarp 的获胜条件是卡住 Vasiliy 的路。

最佳获胜策略有了，那么如何用代码实现呢？一步一步来，首先是从 Polycarp 的角度来获胜，可以发现只要在 Vasiliy 到原点的范围内，他就能卡住 Vasiliy 从而取得胜利，因此判断他胜利的方式就简化成判断其是否在对手移动范围内，当然别忘了他还有一个获胜的条件，就是哪怕 Vasiliy 可以做到一直移动两个单位，他到原点的距离依旧远于 Polycarp。而 Vasiliy 的获胜条件就是剩余情况，也就是 Polycarp 卡不住他时。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
string game(ll x_a,ll y_a,ll x_b,ll y_b){
	if(x_a<=x_b&&y_a<=y_b){//Polycarp获胜条件1 
		return "Polycarp";
	}
	else if(max(x_b,y_b)>=x_a+y_a){//Polycarp获胜条件2
		return "Polycarp";
	}
	else{
		return "Vasiliy";
	}
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	ll x_Polycarp,y_Polycarp,x_Vasiliy,y_Vasiliy;
	cin>>x_Polycarp>>y_Polycarp>>x_Vasiliy>>y_Vasiliy;
	cout<<game(x_Polycarp,y_Polycarp,x_Vasiliy,y_Vasiliy)<<endl;
	return 0;
}
```

关于这段代码我要说：

- 由于 [Codeforces RemoteJudge 暂不可用](https://www.luogu.com.cn/discuss/598533)。所以我暂时不能提交。

---

## 作者：wanyiheng (赞：0)

## 思路

分析一下题目，我们可以发现 Vasiliy 一直处于优势。毕竟 Polycarp 只能往左或往下走，而 Vasiliy 可以往左下走。而我们又可以将 Vasiliy 的状态分为 $3$ 种：

1. Vasiliy 的 $x=0$。
2. Vasiliy 的 $y=0$。
3. Vasiliy 的 $x \ne 0 , y \ne 0$。

所以我们可以得到答案的四种情况：

1. Polycarp 的 $x+y$ 值比 Vasiliy 的 $x$ 值大。则 Polycarp 赢。
2. Polycarp 的 $x+y$ 值比 Vasiliy 的 $x$ 值大。则 Polycarp 赢。
3. Polycarp 的 $x$ 值比 Vasiliy 的 $x$ 值大，Polycarp 的 $y$ 值比 Vasiliy 的 $y$ 值大。则 Polycarp 赢。
4. 最后 Vasiliy 赢。

## code:


```cpp
#include <bits/stdc++.h>

using namespace std;

int xp,yp,xv,yv;

int main() {
	scanf("%d%d%d%d", &xp, &yp, &xv, &yv);

	if(xp+yp<=xv)puts("Polycarp");
	else if(xp+yp<=yv)puts("Polycarp");
	else if(xp<=xv&&yp<=yv)puts("Polycarp");
	else puts("Vasiliy");

	return 0;
}

```

---

## 作者：huangjunhan (赞：0)

# 题目大意
Polycarp 和 Vasiliy 各有一枚棋子，Polycarp 的棋子可以往左边或往下面走一格，而 Vasiliy 的棋子可以往左边、下面和左下方走一格。告诉你两人分别的起点，求谁能先到达点 $（0,0）$。
# AC思路
因为 Vasiliy 的棋子可以往左下走，所以 Vasiliy 是更有优势的，他的最优方案是一直往左下方走，直到碰到边界后，再一直往一个方向走。这样，棋盘中的情况就只会有这三种:

1.Vasiliy 的棋子在 $x$ 轴上。

2.Vasiliy 的棋子在 $y$ 轴上。

3.Vasiliy 的棋子既不在 $x$ 轴上也不在 $y$ 轴上。

对于上述三种情况，Polycarp 的棋子离终点的距离都是 Polycarp 的棋子的 $x$ 值与 $y$ 值的和。只需将 Polycarp 和 Vasiliy 到终点的距离相比，哪个更小，哪个就是最终答案。如果两数相等，由于是 Polycarp 先手，还是他先到达终点。
# AC代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int lx,ly,rx,ry;
int main() {
	cin>>lx>>ly>>rx>>ry;
	if(ry>=lx+ly)puts("Polycarp");//情况一
	else if(rx>=lx+ly)puts("Polycarp");//情况二
	else if(rx>=lx&&ry>=ly)puts("Polycarp");//情况三
	else puts("Vasiliy");//否则 Vasiliy 取胜。
}
```

---

## 作者：xxseven (赞：0)

下面用 P 代指 Polycarp，V 代指 Vasiliy。

我们发现，V 的优势是可以一次性移动两步，因此如果没有阻拦，他只需要 $\max(x_v,y_v)$ 步就可以到达。

但我们发现规则有一条：不能移动到另一个人的棋子上。因此 P 可以把棋子堵在 V 下一次斜着移动能到达的位置，那么 V 的移动就只能退化成一步。

![](https://cdn.luogu.com.cn/upload/image_hosting/84h6x42t.png)

观察这张图片，可以发现，由于 P 可以选择停一步不走，所有涂黄的区域 P 都可以卡住 V 的移动。那么当 P 的初始横纵坐标都不大于 V 的初始横纵坐标时，P 能堵住 V 从而获胜。

还有一种情况，P 不需要阻拦 V，一直移动到终点也比 V 快，也就是 $x_p+y_p\le \max(x_v,y_y)$。

其余情况下 V 必胜。

代码很短：


```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,x,y;
int main(){
	cin>>a>>b>>x>>y;
	if(a<=x&&b<=y) cout<<"Polycarp";//P堵住V
	else if(max(x,y)>=a+b) cout<<"Polycarp";//P直接走到终点
	else cout<<"Vasiliy";
	return 0;
}

```

---

## 作者：_VEGETABLE_OIer_xlc (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF533C)



看完题目后第一反应是：Vasiliy 肯定是选择**将棋子移动到 $(x-1,y-1)$ 的点，可以收获两步的效果**。所以 Vasiliy 最小的步数是 $\max(x_v,y_v)$。而可怜的 Polycarp 只能一步一步走，要用 $x_p+y_p$ 步。

如果连这样子的话步数都比 Polycarp 多，那么：

+ 当 $\max(x_v,y_v) \ge x_p+y_p $ 时，Polycarp 胜！

**Polycarp 肯定不能让 Vasiliy 这么干**，~~由于只有小米加步枪，~~“足够聪明”的他只好钻规则的空子了。

注意到规则：

+ 别人的棋子在 $(x,y)$，那么就是不合法情况。

所以很明显，Polycarp 在 Vasiliy 里面时，就可以卡在 Vasiliy 的最佳行进路线上，**使 Vasiliy 只能向左或向下移动**。

~~Vasiliy：好好好这么玩是吧。~~

于是第二种情况：

+ 当 $x_p \le x_v$ 且 $y_p \le y_v$ 时，Polycarp 胜！

其余情况全是 Vasiliy 赢。

简单讨论即可。

AC 代码奉上。

```cpp
#include<bits/stdc++.h>
using namespace std;
int xp,yp,xv,yv;
int main(){
	cin>>xp>>yp>>xv>>yv;
	if(max(xv,yv)>=xp+yp)
	{
		cout<<"Polycarp";
		return 0;
	}
	if(xp<=xv&&yp<=yv)
	{
		cout<<"Polycarp";
		return 0;
	}
	cout<<"Vasiliy";
	return 0;
}
```

---

## 作者：hexuchen (赞：0)

无人区写题解的第七天

[题目传送门](https://www.luogu.com.cn/problem/CF533C)

[更好的阅读体验？](https://www.luogu.com.cn/article/xdlhng78)

## 题目意思

有两个人在下棋。每个人可以向左上角下一步棋。假设两人都足够聪明，请问谁能先走到 $ (1,1) $。

## 思路分析

分几种情况。

- 第一种情况，$\texttt{Polycarp}$ 的 $x$ 与 $y$ 坐标均比 $\texttt{Vasiliy}$ 大，则无论 $\texttt{Vasiliy}$ 怎么追，都是追不上的。 $\texttt{Polycarp}$ 必胜

- 第二种情况，$\texttt{Polycarp}$ 的 $x$ 与 $y$ 坐标之和小于等于（因为 $\texttt{Polycarp}$ 先手） $\texttt{Vasiliy}$ 的 $x$ 与 $y$ 坐标的最大值，则也是 $\texttt{Polycarp}$ 必胜

- 第三种情况，则 $\texttt{Vasiliy}$ 必胜。

## AC 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int x_1,x_2,y_1,y_2;
signed main(){
	cin>>x_1>>y_1>>x_2>>y_2;
	if(x_2>=x_1 && y_2>=y_1) //如果横竖坐标都占了优势（第一种情况）
		cout<<"Polycarp"<<endl;
	else if((x_1+y_1)<=max(x_2,y_2)){ //如果横竖坐标之和小于等于对手横竖坐标中的最大值（第二种情况）
		cout<<"Polycarp"<<endl;
	}
	else{ //否则对手必胜
		cout<<"Vasiliy"<<endl;
	}
	return 0;
}
```

---

