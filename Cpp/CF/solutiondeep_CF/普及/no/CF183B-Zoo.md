# 题目信息

# Zoo

## 题目描述

The Zoo in the Grid Kingdom is represented by an infinite grid. The Zoo has $ n $ observation binoculars located at the $ OX $ axis. For each $ i $ between $ 1 $ and $ n $ , inclusive, there exists a single binocular located at the point with coordinates $ (i,0) $ . There are $ m $ flamingos in the Zoo, located at points with positive coordinates. The flamingos are currently sleeping and you can assume that they don't move.

In order to get a good view over the flamingos, each of the binoculars can be independently rotated to face any angle (not necessarily integer). Then, the binocular can be used to observe all flamingos that is located at the straight line passing through the binocular at the angle it is set. In other words, you can assign each binocular a direction corresponding to any straight line passing through the binocular, and the binocular will be able to see all flamingos located on that line.

Today, some kids from the prestigious Codeforces kindergarten went on a Field Study to the Zoo. Their teacher would like to set each binocular an angle to maximize the number of flamingos that can be seen by the binocular. The teacher is very interested in the sum of these values over all binoculars. Please help him find this sum.

## 说明/提示

This picture shows the answer to the example test case.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF183B/757dceb4f771edfe053738d9268c557dc412c79e.png)

## 样例 #1

### 输入

```
5 5
2 1
4 1
3 2
4 3
4 4
```

### 输出

```
11
```

# AI分析结果



# Zoo

## 题目描述

动物园所在的网格王国由一个无限大的网格表示。动物园沿 OX 轴放置了 $n$ 个观测望远镜。对于 $1$ 到 $n$ 之间的每个 $i$，在坐标 $(i,0)$ 处有一个望远镜。动物园中有 $m$ 只火烈鸟，位于坐标严格为正的点。火烈鸟正在睡觉，可以视为静止不动。

为了让孩子们获得更好的观察体验，每个望远镜可以独立旋转至任意角度。望远镜调整角度后，可以观察到所有位于该直线上的火烈鸟。老师希望为每个望远镜设置最佳角度，使得每个望远镜能观察到的火烈鸟数量最大。求所有望远镜的最大观察数量之和。

## 样例 #1

### 输入

```
5 5
2 1
4 1
3 2
4 3
4 4
```

### 输出

```
11
```

---

**算法分类**：数学

---

### 解题思路

#### 关键思路
1. **垂直方向统计**：直接统计每个望远镜正上方（x 坐标相同）的火烈鸟数量。
2. **共线方向统计**：枚举所有火烈鸟对，计算它们的连线与 OX 轴的交点 i。若该交点在有效范围内，统计该直线上所有火烈鸟数目，更新对应望远镜的最大值。

#### 解决难点
- **高效计算共线点**：通过计算两点连线的交点，将其斜率表示为最简分数形式，避免重复计算同一方向。
- **符号处理**：统一分数符号，确保同一方向的不同表示被合并。

---

### 题解代码
```python
import math

n, m = map(int, input().split())
flamingos = [tuple(map(int, input().split())) for _ in range(m)]

# 垂直方向统计
cnt_vertical = [0] * (n + 1)
for a, b in flamingos:
    if 1 <= a <= n:
        cnt_vertical[a] += 1

max_hor = [0] * (n + 1)
processed = [set() for _ in range(n + 1)]  # 记录每个i已处理的直线

for p1 in range(m):
    a1, b1 = flamingos[p1]
    for p2 in range(p1 + 1, m):
        a2, b2 = flamingos[p2]
        denominator = b2 - b1
        if denominator == 0:
            continue  # 水平线，无法形成有效交点
        numerator = a1 * b2 - a2 * b1
        if numerator % denominator != 0:
            continue
        i = numerator // denominator
        if 1 <= i <= n:
            # 计算当前点对确定的直线方向（归一化斜率）
            dx = a1 - i
            dy = b1
            if dx == 0:
                continue  # 垂直方向已统计
            # 调整分母为正
            num = dy
            den = dx
            if den < 0:
                num = -num
                den = -den
            g = math.gcd(num, den)
            num //= g
            den //= g
            key = (num, den)
            if key in processed[i]:
                continue
            processed[i].add(key)
            # 统计该直线上的点数
            count = 0
            for a, b in flamingos:
                delta_x = a - i
                if delta_x == 0:
                    continue  # 垂直方向已统计
                # 检查是否满足 num/den = b/delta_x
                if num * delta_x == den * b:
                    count += 1
            if count > max_hor[i]:
                max_hor[i] = count

total = sum(max(cnt_vertical[i], max_hor[i]) for i in range(1, n + 1))
print(total)
```

---

### 关键技巧
1. **分数归一化**：将斜率转换为互质分数形式，确保同一直线的不同表示被统一。
2. **预处理与缓存**：对每个望远镜维护已处理直线集合，避免重复计算。

---

### 拓展练习
1. [CF1114D Flood Fill](https://www.luogu.com.cn/problem/CF1114D)  
   **同类思路**：动态规划结合颜色段合并。
2. [P1351 联合权值](https://www.luogu.com.cn/problem/P1351)  
   **数学分析**：通过枚举中间节点统计联合权值。
3. [P1495 曹冲养猪](https://www.luogu.com.cn/problem/P1495)  
   **同余方程**：中国剩余定理的经典应用。

---
处理用时：492.54秒