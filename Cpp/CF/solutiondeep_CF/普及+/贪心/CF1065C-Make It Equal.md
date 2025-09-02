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



# 题目中文翻译

## 题目描述

有一个由 $n$ 个塔组成的玩具建筑。每个塔由若干立方体堆叠而成，第 $i$ 个塔的高度为 $h_i$，表示它包含 $h_i$ 个立方体。

定义在高度 $H$ 的"切片"操作为：将所有高度大于 $H$ 的塔的顶部立方体移除，使其高度变为 $H$。单次操作的成本等于所有塔被移除的立方体总数。

若一个切片操作的成本不超过 $k$（保证 $k \ge n$），则称为"有效操作"。

求使所有塔高度相同所需的最小有效操作次数。

## 说明/提示

第一个样例的最优解是进行 2 次切片：第一次在高度 2（成本 3），第二次在高度 1（成本 4）。

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

# 题解综合分析

## 关键思路总结
1. **频率统计**：通过桶排序/差分数组统计每个高度对应的立方体数量
2. **分层处理**：从最高层开始向下扫描，贪心累加每层需要切割的立方体数
3. **剩余处理**：当累计值超过 k 时切割，并注意最后可能剩余的立方体需要额外操作
4. **复杂度优化**：使用差分数组将预处理复杂度降为 O(n)，整体复杂度 O(maxH)

## 高星题解推荐

### 1. Blunt_Feeling 题解（4⭐）
**核心亮点**：
- 使用桶统计高度频率，前缀和快速计算各层立方体数
- 从上至下扫描处理分层切割
- 特别注意最后剩余立方体的处理

**代码核心**：
```cpp
int sum[maxn] = {0}; // 前缀和数组
Rep(i,Max,Min) sum[i] = sum[i+1] + h[i]; 

int tot = 0, ans = 0;
Rep(i,Max,Min) {
    if(tot + sum[i] > k) {
        ans++;
        tot = 0;
    }
    tot += sum[i];
}
if(tot > 0) ans++; // 处理剩余
```

### 2. MY_Lee 题解（5⭐）
**核心亮点**：
- 差分数组高效预处理各高度立方体数
- 贪心扫描时动态计算可切割层数
- 代码简洁且时间复杂度最优

**代码核心**：
```cpp
// 差分预处理
for(int i=1;i<=n;i++) {
    tong[1]++;
    tong[a[i]+1]--; 
}
for(int i=1;i<=mx;i++) tong[i] += tong[i-1];

// 贪心扫描
int ans=0, cnt=0;
for(int i=MaxH;i>MinH;i--) {
    if(cnt + tong[i] > k) {
        ans++;
        cnt = tong[i];
    } else {
        cnt += tong[i];
    }
}
if(cnt > 0) ans++;
```

## 关键技巧总结
1. **差分数组**：快速统计各高度需要切割的立方体数
2. **逆向扫描**：从最高层向下处理，符合操作顺序
3. **贪心合并**：尽可能在一次操作中切割更多层
4. **边界处理**：特别注意最后剩余量的判断

## 同类题目推荐
1. P2678 跳石头（二分答案+贪心）
2. P1843 奶牛晒衣服（贪心+分层处理）
3. P5019 铺设道路（差分应用）

## 调试经验摘录
> "在第六个测试点WA是因为没有处理最后的剩余量，即使剩余量小于k，但只要大于0就需要一次操作" —— Blunt_Feeling

**教训**：贪心算法中必须考虑所有可能的剩余情况，即使剩余量很小也需要完整处理所有边界条件。

---
处理用时：67.06秒