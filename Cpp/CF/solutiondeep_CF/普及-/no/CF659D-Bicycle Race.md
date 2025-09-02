# 题目信息

# Bicycle Race

## 题目描述

Maria participates in a bicycle race.

The speedway takes place on the shores of Lake Lucerne, just repeating its contour. As you know, the lake shore consists only of straight sections, directed to the north, south, east or west.

Let's introduce a system of coordinates, directing the $ Ox $ axis from west to east, and the $ Oy $ axis from south to north. As a starting position of the race the southernmost point of the track is selected (and if there are several such points, the most western among them). The participants start the race, moving to the north. At all straight sections of the track, the participants travel in one of the four directions (north, south, east or west) and change the direction of movement only in bends between the straight sections. The participants, of course, never turn back, that is, they do not change the direction of movement from north to south or from east to west (or vice versa).

Maria is still young, so she does not feel confident at some turns. Namely, Maria feels insecure if at a failed or untimely turn, she gets into the water. In other words, Maria considers the turn dangerous if she immediately gets into the water if it is ignored.

Help Maria get ready for the competition — determine the number of dangerous turns on the track.

## 说明/提示

The first sample corresponds to the picture:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF659D/d384618c4de83253addcd24088af2096098ca28a.png)The picture shows that you can get in the water under unfortunate circumstances only at turn at the point $ (1,1) $ . Thus, the answer is $ 1 $ .

## 样例 #1

### 输入

```
6
0 0
0 1
1 1
1 2
2 2
2 0
0 0
```

### 输出

```
1
```

## 样例 #2

### 输入

```
16
1 1
1 5
3 5
3 7
2 7
2 9
6 9
6 7
5 7
5 3
4 3
4 4
3 4
3 2
5 2
5 1
1 1
```

### 输出

```
6
```

# AI分析结果

【题目内容（中文重写）】
# 自行车比赛

## 题目描述
玛丽亚参加了一场自行车比赛。

赛道位于卢塞恩湖岸边，刚好沿着湖的轮廓。如你所知，湖岸仅由指向北、南、东或西的直线段组成。

我们引入一个坐标系，将 $Ox$ 轴从西向东，$Oy$ 轴从南向北。比赛的起点选在赛道的最南端（如果有多个最南端的点，则选最西边的那个）。参赛者从起点向北出发。在赛道的所有直线段上，参赛者朝四个方向（北、南、东或西）之一行进，并且仅在直线段之间的转弯处改变行进方向。当然，参赛者绝不会掉头，即不会从北转向南或从东转向西（反之亦然）。

玛丽亚还很年轻，所以在某些转弯处她会感到不自信。具体来说，如果玛丽亚在转弯失败或转弯不及时的情况下会掉进水里，她就会觉得这个转弯很危险。换句话说，如果玛丽亚忽略某个转弯就会立即掉进水里，那么她就认为这个转弯是危险的。

帮助玛丽亚为比赛做好准备——确定赛道上危险转弯的数量。

## 说明/提示
第一个样例对应下图：

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF659D/d384618c4de83253addcd24088af2096098ca28a.png)
该图显示，只有在点 $(1,1)$ 处的转弯，在不幸的情况下才可能掉进水里。因此，答案是 $1$。

## 样例 #1
### 输入
```
6
0 0
0 1
1 1
1 2
2 2
2 0
0 0
```
### 输出
```
1
```

## 样例 #2
### 输入
```
16
1 1
1 5
3 5
3 7
2 7
2 9
6 9
6 7
5 7
5 3
4 3
4 4
3 4
3 2
5 2
5 1
1 1
```
### 输出
```
6
```

【算法分类】
数学

【综合分析与结论】
这些题解的核心思路都是将问题转化为求 $n$ 边形中 $270^{\circ}$ 角的个数。通过多边形内角和公式列出方程，求解出 $270^{\circ}$ 角的个数与边数 $n$ 的关系为 $x = \frac{n - 4}{2}$。各题解的算法要点均是利用数学方程求解，解决的难点在于发现问题的本质并列出正确的方程。

【所选的题解】
- Seth（4星）：思路清晰，通过分析得出问题本质，列出方程求解，代码简洁明了。
- 引领天下（4星）：直接给出代码，代码简洁，实现了核心公式的计算。
- MattL（4星）：详细推导了方程的求解过程，代码简单易懂。

【重点代码】
```cpp
// Seth的代码
#include <cstdio>
#include <iostream>
using namespace std;
int main() {
    int n;
    cin>>n;
    cout<<(n - 4) / 2;
    return 0;
}

// 引领天下的代码
#include <cstdio>
int n;
int main(void){
    scanf ("%d",&n);
    printf ("%d",(n-4)/2);
}

// MattL的代码
#include<bits/stdc++.h>
using namespace std;
int n;
int main()
{
    cin>>n;
    cout<<(n-4)/2;
    return 0;
}
```
【核心实现思想】
这些代码的核心实现思想都是读取输入的边数 $n$，然后根据公式 $(n - 4) / 2$ 计算并输出 $270^{\circ}$ 角的个数，即危险转弯的数量。

【可拓展之处】
同类型题可能会改变多边形的角度条件，或者增加其他限制，解题思路依然是根据多边形内角和等数学知识列出方程求解。类似算法套路就是遇到几何相关的计数问题，尝试通过数学公式建立方程来求解。

【推荐题目】
1. P1048 采药（考察数学方程求解资源分配问题）
2. P1216 [USACO1.5] 数字三角形 Number Triangles（考察数学递推关系）
3. P1616 疯狂的采药（考察数学优化的动态规划问题）

【个人心得】
这些题解中没有包含个人心得。 

---
处理用时：27.00秒