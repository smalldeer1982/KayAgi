# 题目信息

# Chess Placing

## 题目描述

You are given a chessboard of size $ 1×n $ . It is guaranteed that  $ n $ is even. The chessboard is painted like this: "BWBW $ ... $ BW".

Some cells of the board are occupied by the chess pieces. Each cell contains no more than one chess piece. It is known that the total number of pieces equals to ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF985A/e98ace5c1ad627053f6404505602ba90672a171b.png).

In one step you can move one of the pieces one cell to the left or to the right. You cannot move pieces beyond the borders of the board. You also cannot move pieces to the cells that are already occupied.

Your task is to place all the pieces in the cells of the same color using the minimum number of moves (all the pieces must occupy only the black cells or only the white cells after all the moves are made).

## 说明/提示

In the first example the only possible strategy is to move the piece at the position $ 6 $ to the position $ 5 $ and move the piece at the position $ 2 $ to the position $ 3 $ . Notice that if you decide to place the pieces in the white cells the minimum number of moves will be $ 3 $ .

In the second example the possible strategy is to move ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF985A/4f3653422b6429c3f89311497c438fd20547c4f8.png) in 4 moves, then ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF985A/6c4181624e2b8f95750df668d534111d8ee2005d.png) in 3 moves, ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF985A/74a8630d5d683f941562dca49b5d40bcde2fe1ef.png) in 2 moves and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF985A/b97ec32af1cd5347877d0d15bd3de6cc845fde76.png) in 1 move.

## 样例 #1

### 输入

```
6
1 2 6
```

### 输出

```
2
```

## 样例 #2

### 输入

```
10
1 2 3 4 5
```

### 输出

```
10
```

# AI分析结果

### 题目内容中文重写
# 棋盘放置

## 题目描述
给定一个大小为 $1×n$ 的棋盘，保证 $n$ 是偶数。棋盘按 “BWBW ... BW” 的方式涂色。

棋盘的某些格子上放置了棋子，每个格子最多放置一个棋子。已知棋子的总数等于 $\frac{n}{2}$。

在一步操作中，你可以将一个棋子向左或向右移动一个格子。不能将棋子移出棋盘边界，也不能将棋子移动到已经被占用的格子上。

你的任务是使用最少的移动步数，将所有棋子放置在相同颜色的格子中（所有棋子在所有移动完成后必须只占用黑色格子或只占用白色格子）。

## 说明/提示
在第一个样例中，唯一可能的策略是将位置 $6$ 的棋子移动到位置 $5$，将位置 $2$ 的棋子移动到位置 $3$。注意，如果你决定将棋子放置在白色格子中，最小移动步数将是 $3$。

在第二个样例中，可能的策略是将某个棋子移动 $4$ 步，然后另一个棋子移动 $3$ 步，再一个棋子移动 $2$ 步，最后一个棋子移动 $1$ 步。

## 样例 #1
### 输入
```
6
1 2 6
```
### 输出
```
2
```

## 样例 #2
### 输入
```
10
1 2 3 4 5
```
### 输出
```
10
```

### 综合分析与结论
- **思路**：所有题解思路一致，都发现最终棋子放置位置只有奇数位置（对应黑色格子）和偶数位置（对应白色格子）两种情况。由于棋子不能跨越其他棋子，所以棋子从左到右应分别与奇数位置和偶数位置从左到右一一对应。
- **算法要点**：先将输入的棋子位置从小到大排序，然后分别计算棋子移动到奇数位置和偶数位置所需的总移动步数（通过对应位置差的绝对值求和），最后取这两个总移动步数的最小值。
- **解决难点**：关键在于理解棋子的相对位置不变，要按顺序与目标位置对应，以及明确最终只有两种目标放置情况。

### 题解评分
- little_sun：4星。思路清晰，代码注释详细，变量命名直观，可读性高。
- Yizhixiaoyun：3星。思路明确，但代码注释较少。
- E1_de5truct0r：3星。思路有图辅助说明，但代码注释不够详细。
- GusyNight：3星。对排序原因有解释，但代码风格一般。
- Jerry_heng：3星。思路阐述清晰，但代码注释较少。
- olegekei：3星。思路分析较深入，但代码注释不多。
- OdtreePrince：3星。思路简单提及，代码注释少。

### 所选题解
- little_sun（4星）
  - 关键亮点：思路清晰，代码注释详细，变量命名直观，可读性高。
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[101];
int odd[101]/*奇数*/,even[101]/*偶数*/;
int main()
{
    int n;
    scanf("%d",&n);
    int ans1=0,ans2=0;/*奇,偶情况下的解*/
    for(int i=1;i<=n/2;i++)
    {
        scanf("%d",&a[i]);
    }
    sort(a+1,a+n/2+1);
    for(int i=1;i<=n/2;i++)
    {
        //算对应位
        odd[i]=i*2-1;
        even[i]=i*2;
        //更新答案
        ans1+=abs(odd[i]-a[i]);//记得绝对值
        ans2+=abs(even[i]-a[i]);
    }
    printf("%d",min(ans1,ans2));//最小值
    return 0;
}
```
核心实现思想：先读取输入的 $n$ 和棋子位置，对棋子位置排序，然后分别计算棋子移动到奇数位置和偶数位置的总移动步数，最后输出两者的最小值。

### 最优关键思路或技巧
- 思维方式：通过分析题目条件，发现最终只有两种目标放置情况，且利用棋子相对位置不变的特点，按顺序对应目标位置。
- 代码实现技巧：使用排序确保棋子位置有序，方便与目标位置对应，通过绝对值计算移动步数。

### 可拓展之处
同类型题或类似算法套路：涉及位置移动和最优解的问题，如在一维数轴上移动点到特定位置求最小移动距离，可参考本题思路，先确定目标位置，再按顺序对应计算移动距离。

### 推荐题目
- [P1047 校门外的树](https://www.luogu.com.cn/problem/P1047)
- [P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094)
- [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)

### 个人心得摘录与总结
GusyNight 提到要先排序的原因是所有棋子最后会走到对应的 $2*i$ 上的偶数或者 $2*i - 1$ 上的奇数位置，减的是和 $i$ 有关的，所以要对应才能保证移动到正确位置，总结来说就是排序是为了保证棋子与目标位置一一对应，从而正确计算移动步数。 

---
处理用时：35.52秒