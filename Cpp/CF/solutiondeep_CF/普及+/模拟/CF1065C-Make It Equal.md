# 题目信息

# Make It Equal

## 题目描述

There is a toy building consisting of $ n $ towers. Each tower consists of several cubes standing on each other. The $ i $ -th tower consists of $ h_i $ cubes, so it has height $ h_i $ .

Let's define operation slice on some height $ H $ as following: for each tower $ i $ , if its height is greater than $ H $ , then remove some top cubes to make tower's height equal to $ H $ . Cost of one "slice" equals to the total number of removed cubes from all towers.

Let's name slice as good one if its cost is lower or equal to $ k $ ( $ k \ge n $ ).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1065C/658a593f32bf5073d4f1a1a7bd7987feaeb4f838.png)Calculate the minimum number of good slices you have to do to make all towers have the same height. Of course, it is always possible to make it so.

## 说明/提示

In the first example it's optimal to make $ 2 $ slices. The first slice is on height $ 2 $ (its cost is $ 3 $ ), and the second one is on height $ 1 $ (its cost is $ 4 $ ).

## 样例 #1

### 输入

```
5 5
3 1 2 2 4
```

### 输出

```
2
```

## 样例 #2

### 输入

```
4 5
2 3 4 5
```

### 输出

```
2
```

# AI分析结果



# 题目内容

## 题目描述

有一个由 $n$ 座塔组成的玩具建筑。每座塔由若干立方体堆叠而成，第 $i$ 座塔的高度为 $h_i$。

定义在高度 $H$ 处的"切片"操作为：对于所有高度大于 $H$ 的塔，移除顶部立方体使其高度变为 $H$。每次操作的成本等于所有塔被移除的立方体总数。

若一次切片操作的成本不超过 $k$（$k \ge n$），则称其为"好操作"。求使所有塔高度相同所需的最少"好操作"次数。

## 样例 #1

### 输入
```
5 5
3 1 2 2 4
```

### 输出
```
2
```

## 样例 #2

### 输入
```
4 5
2 3 4 5
```

### 输出
```
2
```

---

# 题解分析与结论

## 综合题解对比

### 共同思路
1. **高度分层统计**：通过差分或前缀和预处理各高度需要切割的立方体数
2. **贪心累加**：从最高高度向最低遍历，贪心累加切割量，超过 $k$ 时触发新操作
3. **边界处理**：最后处理剩余未切割的立方体

### 最优解法关键点
1. **差分预处理**：用差分数组高效统计每个高度需要切割的立方体数
2. **分层贪心**：从高到低切割，确保每次操作尽可能多切割层数
3. **复杂度优化**：将预处理复杂度从 $O(nh)$ 优化到 $O(n)$

---

## 精选题解（评分≥4星）

### 1. MY_Lee 的差分法（★★★★★）
**核心思路**：
1. 使用差分数组统计每个高度对应的立方体数
2. 前缀和预处理各层立方体总数
3. 贪心累加切割量，分段计数

**关键代码**：
```cpp
for(int i=1;i<=n;i++){
    scanf("%d",&x);
    mx = max(mx, x);
    tong[1]++;          // 差分起点
    tong[x+1]--;        // 差分终点
}
for(int i=1;i<=mx;i++)  // 前缀和得到各高度立方体数
    tong[i] += tong[i-1];

int ans=0, sum=0;
for(int h=mx; h>mn; h--){
    if(sum + tong[h] > k){
        ans++;
        sum = tong[h];  // 新切割操作
    }else{
        sum += tong[h]; // 累积当前切割量
    }
}
if(sum > 0) ans++;      // 处理剩余
```

**亮点**：
- 差分预处理将复杂度优化到 $O(n)$
- 清晰的贪心分段逻辑
- 完整处理所有边界情况

---

### 2. Blunt_Feeling 的前缀和法（★★★★）
**核心思路**：
1. 桶统计各高度塔的数量
2. 前缀和预处理每个高度的立方体总数
3. 倒序贪心累加切割层数

**关键代码**：
```cpp
for(int i=Max; i>=Min; i--)
    sum[i] = sum[i+1] + cnt[i]; // 前缀和

int total=0, ans=0;
for(int h=Max; h>=Min; h--){
    if(total + sum[h] > k){
        ans++;
        total = 0;  // 重置累加器
    }
    total += sum[h];
}
if(total > 0) ans++; // 处理剩余
```

**亮点**：
- 桶排序思想简化高度统计
- 前缀和预处理逻辑直观
- 代码结构简洁易维护

---

## 关键技巧总结
1. **差分预处理**：适用于区间批量增减操作，将 $O(nh)$ 优化为 $O(n)$
2. **分层贪心**：将三维切割问题转化为二维层数累积问题
3. **边界处理**：必须单独处理最后剩余的切割量

---

## 类似题目推荐
1. [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115) - 前缀和与贪心思想
2. [P1904 天际线](https://www.luogu.com.cn/problem/P1904) - 高度分层处理
3. [P3406 海底高铁](https://www.luogu.com.cn/problem/P3406) - 差分数组应用

---

## 个人心得摘录
1. **Blunt_Feeling**：在测试点6因未处理剩余切割量导致WA，强调边界检查的重要性
2. **MY_Lee**：通过差分将暴力 $O(nh)$ 优化为线性复杂度，展示算法优化的典型思路
3. **Z_drj**：尝试线段树实现后转向更优解法，体现解题过程中的迭代优化思维

---
处理用时：82.76秒