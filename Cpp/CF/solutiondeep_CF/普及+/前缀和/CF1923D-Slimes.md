# 题目信息

# Slimes

## 题目描述

There are $ n $ slimes placed in a line. The slimes are numbered from $ 1 $ to $ n $ in order from left to right. The size of the $ i $ -th slime is $ a_i $ .

Every second, the following happens: exactly one slime eats one of its neighbors and increases its size by the eaten neighbor's size. A slime can eat its neighbor only if it is strictly bigger than this neighbor. If there is no slime which is strictly bigger than one of its neighbors, the process ends.

For example, suppose $ n = 5 $ , $ a = [2, 2, 3, 1, 4] $ . The process can go as follows:

- first, the $ 3 $ -rd slime eats the $ 2 $ -nd slime. The size of the $ 3 $ -rd slime becomes $ 5 $ , the $ 2 $ -nd slime is eaten.
- then, the $ 3 $ -rd slime eats the $ 1 $ -st slime (they are neighbors since the $ 2 $ -nd slime is already eaten). The size of the $ 3 $ -rd slime becomes $ 7 $ , the $ 1 $ -st slime is eaten.
- then, the $ 5 $ -th slime eats the $ 4 $ -th slime. The size of the $ 5 $ -th slime becomes $ 5 $ , the $ 4 $ -th slime is eaten.
- then, the $ 3 $ -rd slime eats the $ 5 $ -th slime (they are neighbors since the $ 4 $ -th slime is already eaten). The size of the $ 3 $ -rd slime becomes $ 12 $ , the $ 5 $ -th slime is eaten.

For each slime, calculate the minimum number of seconds it takes for this slime to be eaten by another slime (among all possible ways the process can go), or report that it is impossible.

## 样例 #1

### 输入

```
4
4
3 2 4 2
3
1 2 3
5
2 2 3 1 1
7
4 2 3 6 1 1 8```

### 输出

```
2 1 2 1 
1 1 -1 
2 1 -1 1 2 
2 1 1 3 1 1 4```

# AI分析结果



# Slimes

## 题目描述

有 $n$ 只史莱姆排成一列。史莱姆按从左到右的顺序编号为 $1$ 到 $n$。第 $i$ 只史莱姆的大小为 $a_i$。

每秒会发生以下事件：恰好一只史莱姆吃掉它的一个邻居，并将其大小增加被吃掉的邻居的大小。只有当一只史莱姆严格大于其邻居时才能吃掉该邻居。如果不存在严格大于任一邻居的史莱姆，则过程结束。

例如，假设 $n = 5$，$a = [2, 2, 3, 1, 4]$。过程可能如下：
- 第3只史莱姆吃掉第2只，大小变为5
- 第3只吃掉第1只，大小变为7
- 第5只吃掉第4只，大小变为5  
- 第3只吃掉第5只，大小变为12

对于每个史莱姆，计算其被吃掉所需的最短时间（所有可能情况中的最小值），若无法被吃掉则输出 `-1`。

---

## 题解综合分析与结论

### 核心思路
所有题解均基于以下观察：
1. **相邻直接吞噬**：若相邻史莱姆可直接吞噬当前史莱姆，答案直接为1
2. **区间合并条件**：非相邻吞噬需要通过合并区间达成，必须满足两个条件：
   - 区间和严格大于当前史莱姆
   - 区间元素不全相同（否则无法合并）
3. **预处理优化**：利用前缀和快速计算区间和，预处理相同元素边界加速区间合法性判断
4. **二分查找**：在左右两侧二分查找最短合法区间

### 最优思路提炼
1. **预处理前缀和数组**（pr[]/su[]）快速计算任意区间和
2. **预处理左右第一个不同元素位置**（l[]/r[]）判断区间是否可合并
3. **二分查找最短区间**，结合上述两个条件验证
4. **特判相邻元素直接吞噬情况**

---

## 高星题解亮点

### 题解1：Luzhuoyuan（⭐⭐⭐⭐⭐）
**关键亮点**：
- 预处理左右连续相同元素的边界（l[i]/r[i]），将区间合法性判断复杂度降至O(1)
- 使用反向单调性处理二分边界（greater<int>()优化查找）
- 代码简洁高效（25行核心逻辑）

**核心代码解析**：
```cpp
for(int i=1;i<=n;i++){
    int ans=INF;
    if(a[i-1]>a[i]||a[i+1]>a[i]){printf("1 ");continue;} // 特判相邻
    if(pr[i-1]>a[i]&&l[i-1]<i-1) // 左侧查找
        ans = max(l[i-1]+1, i - (lower_bound(su+1,su+1+n,su[i]+a[i],greater<int>())-su-1));
    if(su[i+1]>a[i]&&r[i+1]<n-i) // 右侧查找
        ans = min(ans, max(r[i+1]+1, (upper_bound(pr+1,pr+1+n,pr[i]+a[i])-pr)-i));
    printf("%lld ",ans==INF?-1ll:ans);
}
```

### 题解2：AtomAlpaca（⭐⭐⭐⭐）
**关键亮点**：
- 使用ST表预处理区间全相同判断，提升查询效率
- 结合前缀和与ST表查询，二分时同时验证两个条件
- 代码模块化清晰，易维护

**ST表构建**：
```cpp
void build(){
    for(int i=1;i<=n;i++)st[i][0] = a[i];
    for(int j=1;j<=20;j++)
        for(int i=1;i+(1<<j)-1<=n;i++)
            st[i][j] = (st[i][j-1]==st[i+(1<<(j-1))][j-1] ? st[i][j-1] : 0);
}
```

### 题解3：linyuhuai（⭐⭐⭐⭐）
**关键亮点**：
- 预处理极长相同元素区间，通过块编号快速判断区间合法性
- 详细数学推导验证解法的正确性
- 对边界条件处理全面，逻辑严谨

**区间合法性判断**：
```cpp
bool check(int l, int r){
    if(l > r) return false;
    return (bl[l] != bl[r]); // 块编号不同说明存在不同元素
}
```

---

## 关键实现技巧

1. **反向单调性处理**：  
   由于右侧前缀和数组是单调递减的，使用`greater<int>()`适配器进行二分：
   ```cpp
   lower_bound(su+1, su+1+n, su[i]+a[i], greater<int>())
   ```

2. **极值预处理优化**：  
   预处理每个位置向左/右第一个不同元素的位置，避免每次二分时重复计算：
   ```cpp
   l[i] = (a[i] == a[i-1] ? l[i-1] : i);
   r[i] = (a[i] == a[i+1] ? r[i+1] : i);
   ```

3. **ST表区间查询**：  
   通过预处理区间最大/最小值或块编号，快速判断区间元素是否全相同：
   ```cpp
   int qry(int l, int r){
       int k = log2(r-l+1);
       return (st[l][k] != st[r-(1<<k)+1][k]); // 返回是否全相同
   }
   ```

---

## 拓展与相似题目

1. **区间合并问题**  
   - [P3143 钻石收藏家](https://www.luogu.com.cn/problem/P3143)：双指针维护极值区间
   - [P1638 逛画展](https://www.luogu.com.cn/problem/P1638)：滑动窗口维护区间属性

2. **前缀和+二分**  
   - [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)：经典前缀和变形
   - [P3406 海底高铁](https://www.luogu.com.cn/problem/P3406)：差分与前缀和综合应用

3. **元素分组处理**  
   - [P2008 大朋友的数字](https://www.luogu.com.cn/problem/P2008)：连续区间分组处理
   - [P2949 工作调度](https://www.luogu.com.cn/problem/P2949)：贪心+优先队列维护区间

---
处理用时：58.37秒