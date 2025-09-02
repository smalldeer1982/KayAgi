# 题目信息

# [USACO14OPEN] Cow Optics G

## 题目背景

征求翻译。如果你能提供翻译或者题意简述，请直接发讨论，感谢你的贡献。


## 题目描述

Farmer John's cows would like to host a dance party in their barn, complete with a laser light show.  Unfortunately, the only working laser they have found is located far away from the barn and too heavy to move, so they plan to re-direct the laser light to the barn using a series of mirrors.

The layout of the farm has the laser at position (0,0) pointing north (in the positive y direction), and the barn at (Bx, By); we can think of both the laser and the barn as points in the 2D plane.  There are already N cows (1 <= N <= 100,000) scattered throughout the farm holding mirrors that are aligned at angles of 45 degrees to the axes.  For example, a mirror aligned like \ will take a beam of light entering from below and reflect it to the left.  We can also think of the mirrors as being located at points in the 2D plane.

Just before pressing the big red button to activate the laser, Bessie noticed a major flaw in the plan: the laser cannot hit the barn with the mirrors in their current configuration!  As a result, she plans to run out onto the field, and hold up one more mirror (placed once again at a 45 degree angle) in order to redirect the laser onto the barn. Please count the number of locations in the field where Bessie can stand to accomplish this goal.

All coordinates are integers between -1,000,000,000 and 1,000,000,000. It is guaranteed that any mirrors to be placed will be in this range as well. The cows running the laser insist that the beam should never come back to (0,0) after leaving this location (and with the mirrors in their initial configuration, it is guaranteed that this will not happen).  No two cows occupy the same point in space, and Bessie cannot locate herself at the same position as an existing cow.

农场主约翰的牛想在谷仓里面举办舞会，用激光灯来表演。但不幸的是唯一的激光灯离谷仓太远，并且搬不动，所以牛们想用镜子来反射激光，使得激光照到谷仓。


激光的位置在（0,0），指向为北方（即y轴正方向），谷仓在位置（Bx，By）。已经有N头奶牛拿着镜子分散在农场的各个位置（1 <= N <= 100,000），镜子与原点之间的夹角为45度。例如一个这样（“\“）的镜子可以把从下方射来的光线反射成向左的光线。


Bessie在启动激光的前一刻意识到计划有缺陷，所以她自己又拿着一面镜子出去了，恰好使得激光照到谷仓。


请计算Bessie可能站在的位置的总数。


坐标范围：-1,000,000,000 到 1,000,000,000，数据保证初始时激光光束不会反射回（0,0）位置。同一点上不可能有多头牛，Bessie不能站在其他牛的位置。


## 说明/提示

A mirror at (0,1) or (0,2) placed in either direction would do the trick.

样例中Bessie可能站在（0,1）或者（0,2）。

感谢@SystemLLH  提供翻译


## 样例 #1

### 输入

```
4 1 2 
-2 1 \ 
2 1 / 
2 2 \ 
-2 2 / 
```

### 输出

```
2 
```

# AI分析结果



---

**算法分类**  
模拟与几何

---

**综合分析与结论**  
题目要求找到Bessie放置镜子的位置，使得激光从原点反射后到达谷仓。核心思路是模拟原点和谷仓的激光路径，记录路径上的线段，求交点作为候选点，并验证是否满足反射条件。

### 核心算法流程
1. **路径模拟**  
   - 从原点出发，向北模拟路径，记录所有垂直线段。
   - 从谷仓出发，向四个方向（北、南、东、西）模拟路径，记录所有水平/垂直线段。
   - 每次遇到镜子时，根据类型和当前方向计算新方向，继续模拟。

2. **交点计算**  
   - 原点的垂直线段与谷仓的水平线段求交点。
   - 原点的水平线段与谷仓的垂直线段求交点。
   - 交点的有效性条件：未被现有牛占据，且反射方向正确。

3. **反射验证**  
   - 根据交点处的原方向和谷仓方向，确定所需镜子类型（`/`或`\`）。
   - 使用预定义的反射规则表验证方向是否合法。

### 可视化设计思路
- **动画展示**：用不同颜色线段表示原点和谷仓路径，高亮显示交点。
- **步进控制**：可单步模拟路径生成过程，观察边的添加和方向变化。
- **像素风格**：用网格表示坐标系，镜子和谷仓用不同像素块表示，反射路径动态绘制。

---

**题解清单 (4星)**  
1. **yangwenbin的题解（4星）**  
   - **亮点**：通过双向路径模拟和线段相交快速定位候选点，利用扫描线高效计算交点。
   - **心得**：预处理镜子的分组结构，大幅优化路径模拟效率。

---

**代码实现关键逻辑**  
```python
import bisect
from collections import defaultdict

def main():
    import sys
    input = sys.stdin.read().split()
    idx = 0
    N = int(input[idx]); idx +=1
    Bx = int(input[idx]); idx +=1
    By = int(input[idx]); idx +=1

    cows = set()
    mirrors_north_south = defaultdict(list)  # x -> sorted list of y
    mirrors_east_west = defaultdict(list)    # y -> sorted list of x
    mirror_type_dict = {}  # (x,y) -> type

    for _ in range(N):
        x = int(input[idx]); idx +=1
        y = int(input[idx]); idx +=1
        t = input[idx]; idx +=1
        cows.add((x,y))
        mirrors_north_south[x].append(y)
        mirrors_east_west[y].append(x)
        mirror_type_dict[(x,y)] = t

    # Sort mirrors
    for x in mirrors_north_south:
        mirrors_north_south[x].sort()
    for y in mirrors_east_west:
        mirrors_east_west[y].sort()

    # Direction mapping for mirror reflections
    direction_map = {
        ('N', '\\'): 'E',
        ('E', '\\'): 'N',
        ('S', '\\'): 'W',
        ('W', '\\'): 'S',
        ('N', '/'): 'W',
        ('W', '/'): 'N',
        ('S', '/'): 'E',
        ('E', '/'): 'S',
    }

    def simulate(start_x, start_y, init_dir):
        edges = []
        x, y = start_x, start_y
        dir = init_dir
        visited = set()
        while True:
            if (x, y) in visited:
                break  # loop detected
            visited.add((x, y))
            next_x, next_y = None, None
            if dir in ['N', 'S']:
                # Move vertically
                candidates = mirrors_north_south.get(x, [])
                if dir == 'N':
                    idx = bisect.bisect_right(candidates, y)
                    if idx < len(candidates):
                        next_y = candidates[idx]
                        next_x = x
                else:  # S
                    idx = bisect.bisect_left(candidates, y) - 1
                    if idx >= 0:
                        next_y = candidates[idx]
                        next_x = x
            else:  # E or W
                candidates = mirrors_east_west.get(y, [])
                if dir == 'E':
                    idx = bisect.bisect_right(candidates, x)
                    if idx < len(candidates):
                        next_x = candidates[idx]
                        next_y = y
                else:  # W
                    idx = bisect.bisect_left(candidates, x) - 1
                    if idx >= 0:
                        next_x = candidates[idx]
                        next_y = y
            if next_x is None or next_y is None:
                break  # no mirror, path ends
            if (next_x, next_y) not in mirror_type_dict:
                break  # invalid mirror
            # Record edge from (x,y) to (next_x, next_y)
            edges.append( (x, y, next_x, next_y, dir) )
            # Update direction
            mirror_type = mirror_type_dict[(next_x, next_y)]
            new_dir = direction_map.get( (dir, mirror_type), None )
            if not new_dir:
                break
            dir = new_dir
            x, y = next_x, next_y
        return edges

    # Simulate origin path (0,0) North
    origin_edges = simulate(0, 0, 'N')

    # Simulate barn paths in four directions
    barn_dirs = ['N', 'S', 'E', 'W']
    barn_edges = []
    for d in barn_dirs:
        edges = simulate(Bx, By, d)
        barn_edges.extend(edges)

    # Collect all candidate points
    candidates = set()

    # Check vertical (origin) + horizontal (barn)
    for o_edge in origin_edges:
        ox1, oy1, ox2, oy2, o_dir = o_edge
        if o_dir not in ['N', 'S']:
            continue  # only vertical edges
        x = ox1
        y_min = min(oy1, oy2)
        y_max = max(oy1, oy2)
        for b_edge in barn_edges:
            bx1, by1, bx2, by2, b_dir = b_edge
            if b_dir not in ['E', 'W']:
                continue  # only horizontal edges
            y = by1
            x_min = min(bx1, bx2)
            x_max = max(bx1, bx2)
            if x_min <= x <= x_max and y_min <= y <= y_max:
                # Check if (x,y) is not a cow
                if (x, y) not in cows:
                    candidates.add( (x, y) )

    # Check horizontal (origin) + vertical (barn)
    for o_edge in origin_edges:
        ox1, oy1, ox2, oy2, o_dir = o_edge
        if o_dir not in ['E', 'W']:
            continue  # only horizontal edges
        y = oy1
        x_min = min(ox1, ox2)
        x_max = max(ox1, ox2)
        for b_edge in barn_edges:
            bx1, by1, bx2, by2, b_dir = b_edge
            if b_dir not in ['N', 'S']:
                continue  # only vertical edges
            x = bx1
            y_min = min(by1, by2)
            y_max = max(by1, by2)
            if y_min <= y <= y_max and x_min <= x <= x_max:
                if (x, y) not in cows:
                    candidates.add( (x, y) )

    print(len(candidates))

if __name__ == '__main__':
    main()
```

---

**同类型题推荐**  
1. P2730 [USACO3.2] Magic Squares 魔板  
2. P1443 马的遍历  
3. P1514 引水入城

---
处理用时：435.09秒