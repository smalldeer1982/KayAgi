# 题目信息

# Vasya and Robot

## 题目描述

Vasya has got a robot which is situated on an infinite Cartesian plane, initially in the cell $ (0, 0) $ . Robot can perform the following four kinds of operations:

- U — move from $ (x, y) $ to $ (x, y + 1) $ ;
- D — move from $ (x, y) $ to $ (x, y - 1) $ ;
- L — move from $ (x, y) $ to $ (x - 1, y) $ ;
- R — move from $ (x, y) $ to $ (x + 1, y) $ .

Vasya also has got a sequence of $ n $ operations. Vasya wants to modify this sequence so after performing it the robot will end up in $ (x, y) $ .

Vasya wants to change the sequence so the length of changed subsegment is minimum possible. This length can be calculated as follows: $ maxID - minID + 1 $ , where $ maxID $ is the maximum index of a changed operation, and $ minID $ is the minimum index of a changed operation. For example, if Vasya changes RRRRRRR to RLRRLRL, then the operations with indices $ 2 $ , $ 5 $ and $ 7 $ are changed, so the length of changed subsegment is $ 7 - 2 + 1 = 6 $ . Another example: if Vasya changes DDDD to DDRD, then the length of changed subsegment is $ 1 $ .

If there are no changes, then the length of changed subsegment is $ 0 $ . Changing an operation means replacing it with some operation (possibly the same); Vasya can't insert new operations into the sequence or remove them.

Help Vasya! Tell him the minimum length of subsegment that he needs to change so that the robot will go from $ (0, 0) $ to $ (x, y) $ , or tell him that it's impossible.

## 说明/提示

In the first example the sequence can be changed to LULUU. So the length of the changed subsegment is $ 3 - 1 + 1 = 3 $ .

In the second example the given sequence already leads the robot to $ (x, y) $ , so the length of the changed subsegment is $ 0 $ .

In the third example the robot can't end his path in the cell $ (x, y) $ .

## 样例 #1

### 输入

```
5
RURUU
-2 3
```

### 输出

```
3
```

## 样例 #2

### 输入

```
4
RULR
1 1
```

### 输出

```
0
```

## 样例 #3

### 输入

```
3
UUU
100 100
```

### 输出

```
-1
```

# AI分析结果



### 题目重写
# Vasya与机器人

## 题目描述

Vasya有一个位于无限笛卡尔平面上的机器人，初始位置为$(0, 0)$。机器人可执行四种操作：

- U：从$(x, y)$移动到$(x, y+1)$
- D：从$(x, y)$移动到$(x, y-1)$
- L：从$(x, y)$移动到$(x-1, y)$
- R：从$(x, y)$移动到$(x+1, y)$

现有一个包含$n$个操作的序列。Vasya希望修改其中某个连续子区间，使得机器人最终到达$(x, y)$，并要求修改的子区间长度（即最大修改下标与最小修改下标的差+1）最小。若无法达成目标，输出-1。

## 样例与提示
样例1：输入长度为5的操作序列"RURUU"，目标位置(-2,3)，输出最小修改长度3  
样例2：输入长度为4的序列"RULR"，目标位置(1,1)，原序列已满足要求，输出0  
样例3：输入序列"UUU"无法到达(100,100)，输出-1

---

### 题解分析与结论

#### 核心思路
1. **前缀和预处理**：预先计算每个操作后的坐标变化，快速获取任意区间外的坐标偏移  
2. **二分答案框架**：答案具有单调性（若长度k可行，则>k的均可行），通过二分查找最小可行长度  
3. **奇偶性判断**：需要满足`曼哈顿距离差 ≤ 区间长度`且两者奇偶性相同（允许往返消耗多余步数）

#### 最优题解（评分4.5⭐）

**作者：yeshubo_qwq**  
**关键亮点**：  
- 完整的前缀和预处理实现  
- 清晰的二分框架与check逻辑  
- 代码注释与条件判断解释明确  

**核心代码实现**：
```cpp
bool check(int len) {
    for(int i=1, j=i+len-1; j<=n; i++, j++) {
        int nx = total_x - (x[j] - x[i-1]); // 计算排除区间后的x坐标
        int ny = total_y - (y[j] - y[i-1]); // 计算排除区间后的y坐标
        int need = abs(target_x - nx) + abs(target_y - ny);
        return (len >= need) && ((len - need) % 2 == 0);
    }
}
```

---

### 关键技巧总结
1. **前缀和加速计算**：通过O(n)预处理，实现任意区间外坐标的O(1)查询  
2. **答案单调性应用**：二分法将O(n²)枚举优化为O(n logn)  
3. **曼哈顿距离特性**：结合奇偶性判断可行性，避免无效遍历  

---

### 相似题目推荐
1. [P1147 连续自然数和](https://www.luogu.com.cn/problem/P1147)（前缀和+滑动窗口）  
2. [CF1042D Petya and Array](https://www.luogu.com.cn/problem/CF1042D)（前缀和+二分/树状数组）  
3. [P3572 [POI2014]PTA-Little Bird](https://www.luogu.com.cn/problem/P3572)（单调队列优化DP）

---

### 题解心得摘录
- **调试经验**：需注意前缀和数组的索引对齐问题（操作序列下标从1开始）  
- **易错点**：未处理原序列已满足条件的情况（需特判len=0）  
- **优化启示**：二分的左边界应从0开始，包含无修改情况的判断

---
处理用时：54.68秒