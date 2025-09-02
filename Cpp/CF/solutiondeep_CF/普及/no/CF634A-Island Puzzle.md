# 题目信息

# Island Puzzle

## 题目描述

A remote island chain contains $ n $ islands, labeled $ 1 $ through $ n $ . Bidirectional bridges connect the islands to form a simple cycle — a bridge connects islands $ 1 $ and $ 2 $ , islands $ 2 $ and $ 3 $ , and so on, and additionally a bridge connects islands $ n $ and $ 1 $ . The center of each island contains an identical pedestal, and all but one of the islands has a fragile, uniquely colored statue currently held on the pedestal. The remaining island holds only an empty pedestal.

The islanders want to rearrange the statues in a new order. To do this, they repeat the following process: First, they choose an island directly adjacent to the island containing an empty pedestal. Then, they painstakingly carry the statue on this island across the adjoining bridge and place it on the empty pedestal.

Determine if it is possible for the islanders to arrange the statues in the desired order.

## 说明/提示

In the first sample, the islanders can first move statue $ 1 $ from island $ 1 $ to island $ 2 $ , then move statue $ 2 $ from island $ 3 $ to island $ 1 $ , and finally move statue $ 1 $ from island $ 2 $ to island $ 3 $ .

In the second sample, the islanders can simply move statue $ 1 $ from island $ 1 $ to island $ 2 $ .

In the third sample, no sequence of movements results in the desired position.

## 样例 #1

### 输入

```
3
1 0 2
2 0 1
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
2
1 0
0 1
```

### 输出

```
YES
```

## 样例 #3

### 输入

```
4
1 2 3 0
0 3 2 1
```

### 输出

```
NO
```

# AI分析结果



### 题目重写
# 岛屿谜题

## 题目描述

一个偏远岛屿链包含 $n$ 个岛屿，编号为 $1$ 到 $n$。双向桥梁将这些岛屿连接成一个简单环——岛屿 $1$ 和 $2$ 相连，岛屿 $2$ 和 $3$ 相连，依此类推，最后岛屿 $n$ 和 $1$ 相连。每个岛屿中心都有一个相同的基座，除一个岛屿外，其余岛屿的基座上都放置了独特颜色的易碎雕像，剩余的一个岛屿只有空基座。

岛民希望通过以下操作重新排列雕像：每次选择与空基座所在岛屿直接相连的岛屿，将该岛屿上的雕像移动到空基座上。判断能否通过这种操作将雕像排列成目标状态。

## 样例 #1

### 输入
```
3
1 0 2
2 0 1
```

### 输出
```
YES
```

---

### 算法分类
数学（循环同构判断）

---

### 题解对比与结论

#### 核心思路
所有题解均基于以下观察：移动空位（0）不会改变非零元素的相对顺序，只可能通过环状移位改变整体排列。因此只需判断去掉0后的初始序列与目标序列是否构成循环同构。

#### 最优解法关键点
1. **过滤0元素**：将初始和目标数组中的0去除，得到两个长度为n-1的序列
2. **循环同构判定**：在目标序列中找到初始序列首元素的位置，验证后续元素是否按环状顺序完全匹配
3. **模运算处理环结构**：使用取模运算实现环状索引的遍历

---

### 推荐题解

#### 1. 封禁用户（4星）
**亮点**：代码简洁，逻辑清晰，利用取模运算高效处理循环匹配  
**核心代码**：
```cpp
// 过滤0后的数组a和b
for(int i=0;i<n-1;i++)
    if(a[i]!=b[(i+sum)%(n-1)]){
        printf("NO");
        return 0;
    }
```

#### 2. Vct14（4星）
**亮点**：通过复制数组构造虚拟双倍序列，简化循环匹配逻辑  
**核心代码**：
```cpp
for(int i=1;i<n-1;i++) b[i+n-1] = b[i]; // 构造双倍数组
for(int i=1;i<n-1;i++)
    if(b[p+i-1] != a[i]){ // 直接遍历双倍数组段
        puts("NO");
        return 0;
    }
```

#### 3. yangzd（4星）
**亮点**：同步遍历两个环，通过双指针实时比较  
**核心代码**：
```cpp
for(int i=p1,j=p2,k=0; k<n; i=(i+1)%n,j=(j+1)%n,k++){
    if(a[i]==0) i=(i+1)%n; // 动态跳过0的位置
    if(b[j]==0) j=(j+1)%n;
    if(a[i]!=b[j]) { ... }
}
```

---

### 关键技巧总结
1. **环结构处理**：通过取模运算或数组复制实现循环索引访问
2. **相对顺序不变性**：基于移动操作不改变非零元素相对顺序的重要观察
3. **高效匹配**：通过首元素定位快速缩小验证范围

---

### 类似题目推荐
1. [P1368 工艺](https://www.luogu.com.cn/problem/P1368) - 最小循环表示法
2. [P1709 隐藏口令](https://www.luogu.com.cn/problem/P1709) - 环形字符串处理
3. [CF1095D Circular Dance](https://www.luogu.com.cn/problem/CF1095D) - 环形结构逻辑推理

---
处理用时：95.45秒