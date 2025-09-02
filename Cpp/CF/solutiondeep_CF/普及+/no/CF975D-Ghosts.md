# 题目信息

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

# AI分析结果

### 题目翻译
# 幽灵

## 题目描述
幽灵们和谐平静地生活着，它们在太空中游荡，除了吓唬挡在它们路上的任何东西之外没有其他目的。

宇宙中有 $n$ 个幽灵，它们在 $OXY$ 平面上移动，每个幽灵都有自己不变的速度：$\overrightarrow{V} = V_{x}\overrightarrow{i} + V_{y}\overrightarrow{j}$，其中 $V_{x}$ 是它在 $x$ 轴上的速度，$V_{y}$ 是在 $y$ 轴上的速度。

幽灵 $i$ 有经验值 $EX_i$，它表示在过去有多少幽灵试图吓唬它。如果两个幽灵在某一时刻处于同一笛卡尔点，它们就会互相吓唬。

由于幽灵以恒定速度移动，在某个时刻之后将不再有吓唬行为（真是松了一口气！），幽灵种群的经验值 $GX = \sum_{i=1}^{n} EX_i$ 也将不再增加。

塔米姆（Tameem）是一颗红巨星，他在某个时刻 $T$ 拍摄了笛卡尔平面的照片，神奇的是所有幽灵都排列在形如 $y = a \cdot x + b$ 的直线上。你必须计算在无限的未来幽灵种群的经验指数 $GX$ 会是多少，这就是你今天的任务。

请注意，当塔米姆拍照时，$GX$ 可能已经大于 $0$，因为在 $[-\infty, T]$ 之间的任何时刻，许多幽灵可能已经互相吓唬过了。

## 说明/提示
有四次碰撞 $(1,2,T - 0.5)$，$(1,3,T - 1)$，$(2,4,T + 1)$，$(3,4,T + 0.5)$，其中 $(u,v,t)$ 表示幽灵 $u$ 和 $v$ 在时刻 $t$ 发生了碰撞。每次碰撞时，每个幽灵都获得一个经验点，这意味着 $GX = 4 \cdot 2 = 8$。

在第二个测试用例中，所有点将在 $t = T + 1$ 时碰撞。

![图片说明](https://cdn.luogu.com.cn/upload/vjudge_pic/CF975D/d912223a1fc5da70d046e3cc6e21283e2634fbe3.png)
红色箭头表示第一个幽灵的速度，橙色表示第二个幽灵的速度，蓝色表示第三个幽灵的速度。

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

### 算法分类
数学

### 题解综合分析与结论
这两道题解思路本质相同，都是通过推导得出两个幽灵发生碰撞的条件为 $v_{y2}-a\times v_{x2}=v_{y1}-a\times v_{x1}$ 。然后利用哈希表（`map` 或 `unordered_map`）来统计满足该条件的幽灵对数，从而计算碰撞次数。不同点在于实现细节和优化方式。

### 题解1（作者：是个汉子）
- **星级**：4星
- **关键亮点**：思路清晰，直接推导碰撞条件公式，并利用两个 `map` 分别记录满足碰撞条件的数量以及速度完全相同（相对静止）的点的数量，代码简洁明了，易于理解。
- **重点代码核心实现思想**：遍历每个幽灵，计算 `vy - a * vx` 的值并存入 `map` 中，同时记录速度相同的幽灵对。每次遍历通过 `map` 中已有的满足碰撞条件的幽灵数量减去速度相同的幽灵对数量，累加到答案中，最后答案乘2得到总的碰撞次数。
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
        mp[res]++;
        same[tmp]++;
    }
    printf("%lld\n",ans*2);
    return 0;   
}
```

### 题解2（作者：柠檬熟了）
- **星级**：3星
- **关键亮点**：同样推导碰撞条件，使用 `unordered_map` 进行统计。在计算答案部分有一定优化思路，通过对哈希表中数据的处理，避免了 $O(N^2)$ 的复杂度。但整体代码结构和思路表述稍显复杂，可读性略逊一筹。
- **重点代码核心实现思想**：遍历幽灵计算 `vy - a * vx` 并存入二维 `unordered_map`，然后通过对哈希表中每个 `vy - a * vx` 对应的不同 `vx` 的幽灵数量进行处理，先减去每个 `vx` 幽灵数量的平方，再加上总幽灵数量的平方，从而得到总的碰撞次数。
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

### 最优关键思路或技巧
通过数学推导得出幽灵碰撞的条件公式，并利用哈希表（`map` 或 `unordered_map`）高效统计满足条件的幽灵对数，从而计算碰撞次数。在处理相对静止的幽灵时，采用额外的数据结构（如 `map<PLL, int>` 或二维 `unordered_map`）进行记录并在计算时排除。

### 可拓展思路
此类题目属于几何与数学结合的问题，类似套路可应用于其他涉及物体运动轨迹、碰撞检测等场景。比如将平面拓展到三维空间，或者幽灵的速度不再恒定等情况。

### 推荐洛谷题目
- [P1082 同余方程](https://www.luogu.com.cn/problem/P1082)：考察数论中的同余方程求解，与本题类似，需要运用数学推导和计算。
- [P2613 【模板】有理数取余](https://www.luogu.com.cn/problem/P2613)：涉及有理数取余的数学运算，锻炼数学思维和代码实现能力。
- [P1463 [POI2002][HAOI2007]反素数](https://www.luogu.com.cn/problem/P1463)：需要对数字的性质进行深入分析，与本题一样，通过数学性质来解决问题。 

---
处理用时：62.87秒