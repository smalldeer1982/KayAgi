# 题目信息

# Bender Problem

## 题目描述

Robot Bender decided to make Fray a birthday present. He drove $ n $ nails and numbered them from $ 1 $ to $ n $ in some order. Bender decided to make a picture using metal rods. The picture is a closed polyline, which vertices should be nails (in the given order). The segments of the polyline should be parallel to the coordinate axes. Polyline is allowed to have self-intersections. Bender can take a rod and fold it exactly once in any place to form an angle of 90 degrees. Then he can attach the place of the fold to some unoccupied nail and attach two ends of this rod to adjacent nails. A nail is considered unoccupied if there is no rod attached to it (neither by it's end nor the by the fold place). No rod could be used twice. It is not required to use all the rods.

Help Bender to solve this difficult task.

## 样例 #1

### 输入

```
4 2
0 0
0 2
2 2
2 0
4 4
```

### 输出

```
YES
1 -1 2 -1 
```

## 样例 #2

### 输入

```
6 3
0 0
1 0
1 1
2 1
2 2
0 2
3 2 3
```

### 输出

```
YES
1 -1 2 -1 3 -1 
```

## 样例 #3

### 输入

```
6 3
0 0
1 0
1 1
2 1
2 2
0 2
2 2 3
```

### 输出

```
NO
```

# AI分析结果



# Bender Problem

## 题目描述

机器人Bender决定给Fray制作生日礼物。他钉了$n$个钉子并按某种顺序编号为$1$到$n$，想用金属棒组成闭合折线。要求折线顶点按顺序连接钉子，线段必须与坐标轴平行，允许自相交。每根铁棒需弯折一次形成直角，折叠点固定在未被占用的钉子上，两端连接相邻钉子。同一根铁棒不能重复使用，且不必用完所有铁棒。请判断是否存在可行方案。

## 样例 #1

### 输入

```
4 2
0 0
0 2
2 2
2 0
4 4
```

### 输出

```
YES
1 -1 2 -1 
```

## 样例 #2

### 输入

```
6 3
0 0
1 0
1 1
2 1
2 2
0 2
3 2 3
```

### 输出

```
YES
1 -1 2 -1 3 -1 
```

## 样例 #3

### 输入

```
6 3
0 0
1 0
1 1
2 1
2 2
0 2
2 2 3
```

### 输出

```
NO
```

**算法分类**：构造

---

### 题解综合分析

各题解核心思路一致：折叠点必须间隔分布（奇偶位置二选一），每个折叠点对应两个相邻钉子的曼哈顿距离之和。解决难点在于环形结构的处理及铁棒长度的匹配验证。以下为关键思路：

1. **环形预处理**：将钉子首尾相接形成环，处理边界条件
2. **奇偶分组验证**：分别尝试从奇数位/偶数位开始分配折叠点
3. **贪心匹配**：对每个候选折叠点，查找满足长度的未使用铁棒

---

### 精选题解

#### 1. 作者：Frather_ （★★★★☆）
**关键亮点**：
- 清晰的环形预处理函数`Calc`
- 简洁的奇偶分组验证结构
- 使用模运算处理环形边界

**核心代码**：
```cpp
int Calc(int i, int j) {
    int x_ = abs(x[j] - x[(j + n - 1) % n]);
    int y_ = abs(y[j] - y[(j + n - 1) % n]);
    int _x = abs(x[j] - x[(j + 1) % n]);
    int _y = abs(y[j] - y[(j + 1) % n]);
    return x_ + y_ + _x + _y;
}

for (int i = 0; i < 2; i++) { // 尝试奇偶两种分组
    prepare();
    for (int j = i; j < n; j += 2) {
        int dis = Calc(i, j);
        // 查找匹配铁棒...
    }
}
```

#### 2. 作者：Peter20122012 （★★★★☆）
**关键亮点**：
- 显式的边界条件处理
- 函数封装提高可读性
- 清晰的失败回退逻辑

**核心代码**：
```cpp
bool findans(int st) {
    memset(ans, 0xff, sizeof(ans));
    for (int i = st; i <= n; i += 2) {
        int need = 计算曼哈顿距离之和;
        for (int j = 1; j <= m; j++) {
            if (!used[j] && len[j] == need) {
                used[j] = true;
                ans[i] = j;
                break;
            }
        }
        if (ans[i] == -1) return true;
    }
    // 输出逻辑...
}
```

---

### 关键思路总结
1. **环形结构处理**：通过模运算或显式复制首尾元素，处理钉子环形排列
2. **间隔验证策略**：折叠点必须间隔分布，只需验证奇偶两种分组方案
3. **贪心匹配算法**：对每个候选折叠点，顺序查找首个可用铁棒

---

### 拓展应用
1. 类似环形构造题：CF1110E Magic Stones
2. 曼哈顿距离应用：洛谷P1143 坐标转换问题
3. 奇偶分组策略：CF1353E Lights and Brackets

**推荐练习**：
1. [CF1110E Magic Stones](https://www.luogu.com.cn/problem/CF1110E)
2. [P1143 坐标转换](https://www.luogu.com.cn/problem/P1143)
3. [CF1353E Lights](https://www.luogu.com.cn/problem/CF1353E)

---
处理用时：59.62秒