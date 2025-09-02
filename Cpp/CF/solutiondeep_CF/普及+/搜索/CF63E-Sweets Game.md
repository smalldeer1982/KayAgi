# 题目信息

# Sweets Game

## 题目描述

Karlsson has visited Lillebror again. They found a box of chocolates and a big whipped cream cake at Lillebror's place. Karlsson immediately suggested to divide the sweets fairly between Lillebror and himself. Specifically, to play together a game he has just invented with the chocolates. The winner will get the cake as a reward.

The box of chocolates has the form of a hexagon. It contains 19 cells for the chocolates, some of which contain a chocolate. The players move in turns. During one move it is allowed to eat one or several chocolates that lay in the neighboring cells on one line, parallel to one of the box's sides. The picture below shows the examples of allowed moves and of an unacceptable one. The player who cannot make a move loses.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF63E/d39dc87a25b4bbc8e9ef90055ec2e2d8c38df358.png)Karlsson makes the first move as he is Lillebror's guest and not vice versa. The players play optimally. Determine who will get the cake.

## 样例 #1

### 输入

```
  . . .
 . . O .
. . O O .
 . . . .
  . . .
```

### 输出

```
Lillebror```

## 样例 #2

### 输入

```
  . . .
 . . . O
. . . O .
 O . O .
  . O .
```

### 输出

```
Karlsson```

# AI分析结果



![题目翻译]
# 糖果游戏

## 题目描述

Karlsson再次拜访了Lillebror。他们在Lillebror家发现了一盒巧克力和一个大奶油蛋糕。Karlsson立即提议公平分配糖果，具体方式是通过他发明的巧克力游戏决定胜负。胜者将获得蛋糕奖励。

巧克力盒呈六边形，包含19个格子，部分格子装有巧克力。玩家轮流进行操作：每次可吃掉同一行直线上相邻的1个或多个巧克力（需平行于六边形某边）。无法操作的玩家判负。Karlsson作为客人先手，双方都采取最优策略，请判断获胜者。

![图示](https://cdn.luogu.com.cn/upload/vjudge_pic/CF63E/d39dc87a25b4bbc8e9ef90055ec2e2d8c38df358.png)

## 样例 #1

输入：
```
  . . .
 . . O .
. . O O .
 . . . .
  . . .
```
输出：
```
Lillebror```

## 样例 #2

输入：
```
  . . .
 . . . O
. . . O .
 O . O .
  . O .
```
输出：
```
Karlsson```

---

### 题解综合分析

#### 关键思路与技巧
1. **状态压缩**：将19个格子的存在状态用19位二进制表示
2. **记忆化搜索**：存储已计算的状态胜负结果
3. **方向预处理**：用数组预先处理三个方向的移动增量
4. **SG定理应用**：通过递归判断子状态的NIM博弈性质

#### 共性难点
- 六边形坐标系的线性化处理
- 连续巧克力取法的状态转移模拟
- 必胜态/必败态的递归判断逻辑

---

### 优质题解推荐

#### 题解1（xuchenhao2008）⭐⭐⭐⭐⭐
**亮点**：
- 完整的坐标预处理系统（row数组、boost增量数组）
- 三方向独立处理逻辑清晰
- 记忆化剪枝效率高

**核心实现**：
```cpp
int dfs(int pl, int cur) {
    if (ans[cur] != 0) return ans[cur] == 1 ? pl : 1-pl;
    if (cur == 0) return 1-pl;

    int res = 1-pl;
    for (int st = 0; st < 19; ++st) {
        if (!(cur & (1<<st))) continue;
        
        // 处理三个方向
        for (int dir = 0; dir < 3; ++dir) {
            int to = cur;
            for (int i = st; valid_move(i, dir); ) {
                if (!(to & (1<<i))) break;
                to ^= (1<<i);
                if (dfs(1-pl, to) == pl) {
                    ans[cur] = 1;
                    return pl;
                }
                i = next_pos(i, dir);
            }
        }
    }
    ans[cur] = -1;
    return res;
}
```

#### 题解2（Elairin176）⭐⭐⭐⭐
**亮点**：
- 预处理所有合法取法存入vector
- 使用check函数验证连续合法性
- 代码结构简洁高效

**预处理逻辑**：
```cpp
vector<int> ok; // 存储所有合法取法
for (int len : {3,4,5}) {
    for (int mask = 1; mask < (1<<len); ++mask) {
        if (check(mask, len)) {
            for (auto &dir : 所有方向) {
                ok.push_back(生成该方向的mask状态);
            }
        }
    }
}
```

---

### 拓展练习
1. [P2734 游戏](https://www.luogu.com.cn/problem/P2734) - 区间取物的博弈策略
2. [P3185 分裂游戏](https://www.luogu.com.cn/problem/P3185) - 状压+SG定理应用
3. [P2960 棋盘游戏](https://www.luogu.com.cn/problem/P2960) - 六边形棋盘博弈进阶

---

### 心得分享
> "调试时发现坐标转换错误，通过打印各方向移动的增量数组解决了越界问题。预处理是此类题的关键，把棋盘特性转化为线性处理能极大简化逻辑。" —— xuchenhao2008

**总结**：坐标系的合理设计是解决非常规棋盘问题的关键，建议在编码前先建立清晰的坐标映射模型。

---
处理用时：43.33秒