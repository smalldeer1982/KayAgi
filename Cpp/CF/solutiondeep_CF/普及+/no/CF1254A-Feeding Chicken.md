# 题目信息

# Feeding Chicken

## 题目描述

Long is a huge fan of CFC (Codeforces Fried Chicken). But the price of CFC is increasing, so he decides to breed the chicken on his own farm.

His farm is presented by a rectangle grid with $ r $ rows and $ c $ columns. Some of these cells contain rice, others are empty. $ k $ chickens are living on his farm. The number of chickens is not greater than the number of cells with rice on the farm.

Long wants to give his chicken playgrounds by assigning these farm cells to his chickens. He would like to satisfy the following requirements:

- Each cell of the farm is assigned to exactly one chicken.
- Each chicken is assigned at least one cell.
- The set of cells assigned to every chicken forms a connected area. More precisely, if two cells $ (x, y) $ and $ (u, v) $ are assigned to the same chicken, this chicken is able to walk from $ (x, y) $ to $ (u, v) $ by passing only its cells and moving from each cell to another cell sharing a side.

Long also wants to prevent his chickens from fighting for food. Hence he wants the difference between the maximum and the minimum number of cells with rice assigned to a chicken to be as small as possible. Please help him.

## 说明/提示

These pictures explain the sample output. Each color represents one chicken. Cells filled with patterns (not solid colors) contain rice.

In the first test case, each chicken has one cell with rice. Hence, the difference between the maximum and the minimum number of cells with rice assigned to a chicken is $ 0 $ .

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1254A/1bff8ca11bd265337b0e871e2919557b9f31df1c.png)

In the second test case, there are $ 4 $ chickens with $ 3 $ cells of rice, and $ 2 $ chickens with $ 2 $ cells of rice. Hence, the difference between the maximum and the minimum number of cells with rice assigned to a chicken is $ 3 - 2 = 1 $ .

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1254A/2ec7f9b3f1d8e0f97ddc9a49d6dcde16eae965cb.png)

In the third test case, each chicken has $ 3 $ cells with rice. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1254A/cc5ea14ecb6cc9df893cd1ba4b47e078c09da70f.png)

In the last test case, since there are $ 62 $ chicken with exactly $ 62 $ cells of rice, each chicken must be assigned to exactly one cell. The sample output is one of the possible way.

## 样例 #1

### 输入

```
4
3 5 3
..R..
...R.
....R
6 4 6
R..R
R..R
RRRR
RRRR
R..R
R..R
5 5 4
RRR..
R.R..
RRR..
R..R.
R...R
2 31 62
RRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR
RRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR
```

### 输出

```
11122
22223
33333
aacc
aBBc
aBBc
CbbA
CbbA
CCAA
11114
22244
32444
33344
33334
abcdefghijklmnopqrstuvwxyzABCDE
FGHIJKLMNOPQRSTUVWXYZ0123456789```

# AI分析结果

### 题目中文重写
# 养鸡问题

## 题目描述
Long 是 CFC（Codeforces 炸鸡）的超级粉丝。但 CFC 的价格不断上涨，所以他决定在自己的农场养鸡。

他的农场是一个有 $r$ 行 $c$ 列的矩形网格。其中一些格子里有稻谷，其他格子为空。农场里养了 $k$ 只鸡，鸡的数量不超过农场中含稻谷格子的数量。

Long 想通过分配农场的格子给鸡，为鸡们提供活动场地。他希望满足以下要求：
- 农场的每个格子都恰好分配给一只鸡。
- 每只鸡至少分配到一个格子。
- 分配给每只鸡的格子集合构成一个连通区域。更准确地说，如果两个格子 $(x, y)$ 和 $(u, v)$ 分配给了同一只鸡，这只鸡能够仅通过它自己的格子，从 $(x, y)$ 走到 $(u, v)$，且每次只能移动到与之共享一条边的格子。

Long 还想防止鸡们为食物争斗。因此，他希望分配给鸡的含稻谷格子的最大数量和最小数量之间的差值尽可能小。请帮助他解决这个问题。

## 说明/提示
这些图片解释了样例输出。每种颜色代表一只鸡。填充有图案（非纯色）的格子表示含有稻谷。

在第一个测试用例中，每只鸡都有一个含稻谷的格子。因此，分配给鸡的含稻谷格子的最大数量和最小数量之间的差值为 $0$。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1254A/1bff8ca11bd265337b0e871e2919557b9f31df1c.png)

在第二个测试用例中，有 $4$ 只鸡有 $3$ 个含稻谷的格子，$2$ 只鸡有 $2$ 个含稻谷的格子。因此，分配给鸡的含稻谷格子的最大数量和最小数量之间的差值为 $3 - 2 = 1$。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1254A/2ec7f9b3f1d8e0f97ddc9a49d6dcde16eae965cb.png)

在第三个测试用例中，每只鸡都有 $3$ 个含稻谷的格子。
![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1254A/cc5ea14ecb6cc9df893cd1ba4b47e078c09da70f.png)

在最后一个测试用例中，因为有 $62$ 只鸡和恰好 $62$ 个含稻谷的格子，每只鸡必须恰好分配到一个格子。样例输出是其中一种可能的分配方式。

## 样例 #1

### 输入
```
4
3 5 3
..R..
...R.
....R
6 4 6
R..R
R..R
RRRR
RRRR
R..R
R..R
5 5 4
RRR..
R.R..
RRR..
R..R.
R...R
2 31 62
RRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR
RRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR
```

### 输出
```
11122
22223
33333
aacc
aBBc
aBBc
CbbA
CbbA
CCAA
11114
22244
32444
33344
33334
abcdefghijklmnopqrstuvwxyzABCDE
FGHIJKLMNOPQRSTUVWXYZ0123456789
```

### 算法分类
构造

### 综合分析与结论
这些题解的核心思路都是先计算出含稻谷格子的总数，然后将其平均分配给鸡，使得每只鸡分配到的含稻谷格子数的极差最小。为了保证每只鸡的格子是连通的，都采用了蛇形遍历矩阵的方法。

- **思路**：先统计含稻谷格子的总数 $sum$，计算出每只鸡平均应分配的含稻谷格子数 $\lfloor\frac{sum}{k}\rfloor$，以及有 $sum \bmod k$ 只鸡需要多分配一个含稻谷的格子。然后蛇形遍历矩阵，按照上述规则为每只鸡分配格子。
- **算法要点**：
    - 统计含稻谷格子的总数。
    - 计算每只鸡应分配的含稻谷格子数。
    - 蛇形遍历矩阵进行格子分配。
- **解决难点**：
    - 保证每只鸡的格子是连通的，通过蛇形遍历实现。
    - 处理剩余的空缺格子，通常由最后一只鸡补上。

### 题解列表
- **copper_ingot（4星）**
    - **关键亮点**：思路清晰，代码注释详细，通过自定义函数 `nex` 确定下一个遍历的位置，`get` 函数获取对应的字符，逻辑明确。
- **_Lazy_zhr_（3星）**
    - **关键亮点**：代码简洁，通过预处理划分方案字符，直接在原矩阵上进行操作。
- **Saber_Master（3星）**
    - **关键亮点**：考虑了 $cnt\leq k$ 的特殊情况，通过补 $R$ 的方式兼容通用解法。
- **寒鸽儿（3星）**
    - **关键亮点**：通过自定义函数 `getpt` 根据时间戳计算坐标，实现蛇形遍历。

### 重点代码
#### copper_ingot 的核心代码
```cpp
pii nex(int x, int y){//用于确定下一个遍历的位置
	if (y == c && x % 2 == 1) x++;
	else if (y == 1 && x % 2 == 0) x++;
	else if (x % 2 == 1) y++;
	else y--;
	pii p; p.first = x, p.second = y; return p;
}
char get(int x){//获得对应的字符
	if (x <= 10) return x + '0' - 1;
	if (x <= 36) return x + 'A' - 11;
	return x + 'a' - 37;
}
```
**核心实现思想**：`nex` 函数根据当前位置和矩阵的行列信息，确定蛇形遍历的下一个位置；`get` 函数根据鸡的编号返回对应的字符。

### 最优关键思路或技巧
- 采用蛇形遍历矩阵的方法，保证每只鸡的格子是连通的。
- 先计算每只鸡应分配的含稻谷格子数，再进行分配，使得含稻谷格子数的极差最小。

### 可拓展之处
同类型题或类似算法套路：
- 矩阵的遍历问题，如螺旋矩阵、Z 字形遍历等。
- 连通区域的划分问题，如岛屿问题、图像分割等。

### 推荐题目
- [P1002 过河卒](https://www.luogu.com.cn/problem/P1002)
- [P1012 拼数](https://www.luogu.com.cn/problem/P1012)
- [P1047 校门外的树](https://www.luogu.com.cn/problem/P1047)

### 个人心得
题解中未包含个人心得。

---
处理用时：55.62秒