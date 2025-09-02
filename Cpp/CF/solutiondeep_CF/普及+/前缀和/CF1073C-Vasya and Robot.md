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



# Vasya and Robot

## 题目描述

Vasya 有一个机器人，初始位于笛卡尔平面的 $(0, 0)$ 点。机器人可以执行四种操作：
- U：从 $(x, y)$ 移动到 $(x, y+1)$
- D：从 $(x, y)$ 移动到 $(x, y-1)$
- L：从 $(x, y)$ 移动到 $(x-1, y)$
- R：从 $(x, y)$ 移动到 $(x+1, y)$

给定长度为 $n$ 的操作序列，要求修改一个连续子序列，使得机器人最终到达 $(x, y)$。修改代价定义为被修改子序列的最大索引与最小索引之差加一。求最小修改代价，若无法实现输出 $-1$。

## 样例分析
样例1：修改索引1-3的操作，代价3  
样例2：无需修改  
样例3：无法到达  

---

## 题解分析与最优思路

### 关键算法：二分答案 + 前缀和优化
1. **单调性证明**：若长度为L的修改可行，则更长的修改必然可行
2. **前缀和预处理**：计算每个位置的前缀坐标变化，实现$O(1)$查询任意区间的位移
3. **可行性判断**：设修改区间为$[l,r]$，总位移差为$d$，需满足：
   - 修改长度 ≥ 曼哈顿距离差
   - 多余步数为偶数（可折返抵消）

---

## 精选题解（评分≥4★）

### 题解1：yeshubo_qwq（4.5★）
**亮点**：
1. 完整的前缀和预处理实现
2. 清晰的奇偶性判断逻辑
3. 二分模板简洁规范

```cpp
bool check(int l){
    for(int i=1,j=i+l-1; j<=n; i++,j++){
        int n2 = x[n] - x[j] + x[i-1];
        int m2 = y[n] - y[j] + y[i-1];
        int p = abs(n1-n2) + abs(m1-m2);
        if(l == p || (l > p && (l-p)%2 == 0)) 
            return true;
    }
    return false;
}
```

### 题解2：JMercury（4★）
**亮点**：
1. 变量命名清晰易读
2. 包含完整的前缀和初始化过程
3. 边界条件处理完善

```cpp
bool check(int len){
    for(int l=1, r=len; r<=n; l++,r++){
        int nx = frtx[n] - (frtx[r]-frtx[l-1]);
        int ny = frty[n] - (frty[r]-frty[l-1]);
        if(len >= abs(x-nx)+abs(y-ny) 
          && (len - abs(x-nx) - abs(y-ny))%2 == 0)
            return true;
    }
    return false;
}
```

### 题解3：eb0ycn（4★）
**亮点**：
1. 创新的尺取法实现（$O(n)$复杂度）
2. 动态维护区间位移差
3. 实时更新最小答案

```cpp
for(int r=1; r<=n; ++r){
    // 动态扣除右端点影响
    while(l<=r && 条件满足){
        // 更新答案并恢复左端点影响
        l++;
    }
}
```

---

## 关键实现技巧
1. **坐标差计算**：`总位移 - 区间位移 = x[n] - (x[r]-x[l-1])`
2. **奇偶性判断**：`(剩余步数 - 曼哈顿差) % 2 == 0`
3. **二分边界**：初始左边界0对应无需修改的情况

---

## 同类题目推荐
1. [P1083 借教室](https://www.luogu.com.cn/problem/P1083) 二分答案+差分数组
2. [P2678 跳石头](https://www.luogu.com.cn/problem/P2678) 二分答案经典题
3. [P1281 书的复制](https://www.luogu.com.cn/problem/P1281) 二分答案+贪心验证

---
处理用时：45.79秒