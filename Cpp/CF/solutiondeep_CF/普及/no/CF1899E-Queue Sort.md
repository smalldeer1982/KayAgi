# 题目信息

# Queue Sort

## 题目描述

Vlad found an array $ a $ of $ n $ integers and decided to sort it in non-decreasing order.

To do this, Vlad can apply the following operation any number of times:

- Extract the first element of the array and insert it at the end;
- Swap that element with the previous one until it becomes the first or until it becomes strictly greater than the previous one.

Note that both actions are part of the operation, and for one operation, you must apply both actions.

For example, if you apply the operation to the array \[ $ 4, 3, 1, 2, 6, 4 $ \], it will change as follows:

- \[ $ \color{red}{4}, 3, 1, 2, 6, 4 $ \];
- \[ $ 3, 1, 2, 6, 4, \color{red}{4} $ \];
- \[ $ 3, 1, 2, 6, \color{red}{4}, 4 $ \];
- \[ $ 3, 1, 2, \color{red}{4}, 6, 4 $ \].

Vlad doesn't have time to perform all the operations, so he asks you to determine the minimum number of operations required to sort the array or report that it is impossible.

## 样例 #1

### 输入

```
5
5
6 4 1 2 5
7
4 5 3 7 8 6 2
6
4 3 1 2 6 4
4
5 2 4 2
3
2 2 3```

### 输出

```
2
6
-1
-1
0```

# AI分析结果



# Queue Sort

## 题目描述

弗拉德发现了一个包含 $n$ 个整数的数组 $a$，并决定将其按非递减顺序排序。

每次操作包含两个步骤：
1. 将数组的第一个元素移到末尾
2. 将该元素与前一个元素交换，直到它成为第一个元素或严格大于前一个元素

求将数组排序所需的最小操作次数，若不可能则返回 -1。

## 输入样例与输出样例见原题

**算法分类**：贪心

---

### 题解综合分析

所有题解均基于以下核心思路：
1. 找到第一个最小值的位置 $pos$
2. 检查 $pos$ 之后子数组是否有序
3. 若有序则返回 $pos-1$，否则返回 -1

关键点在于：当最小值到达首位后，后续操作无法改变其后的元素顺序。若此时后续元素无序，则无法完成排序。

---

### 高分题解推荐

#### 1. lailai0916（4.5星）
**核心思路**：
- 使用 `is_sorted` 直接验证后续有序性
- 代码简洁，时间复杂度 $O(n)$
```cpp
int main() {
    // 核心代码段
    int k = 1;  // 最小值位置
    for(int i=1;i<=n;i++) if(a[i]<a[k]) k=i;
    if(is_sorted(a+k,a+n+1)) cout<<k-1;
    else cout<<-1;
}
```

#### 2. FireRain（4星）
**亮点**：
- 手动实现有序性检查
- 变量命名清晰，逻辑直观
```cpp
for(int i=id+1;i<=n;i++) 
    if(arr[i]<arr[i-1]) puts("-1");
printf("%d",id-1);
```

#### 3. zct_sky（4星）
**优化点**：
- 使用 `LLONG_MAX` 处理大数
- 提前终止最小值查找
```cpp
for(int i=1;i<=n;i++) 
    if(a[i]==minn) { ans=i-1; break; }
```

---

### 关键思路总结
1. **最小值定位**：数组的第一个最小值是操作停止的关键节点
2. **有序性验证**：必须保证最小值后的子数组本身已有序
3. **时间复杂度**：最优解为 $O(n)$，不可使用排序等 $O(n\log n)$ 操作

---

### 拓展思考
类似问题可参考：
1. 洛谷 P1090 [合并果子] - 贪心策略应用
2. 洛谷 P1908 [逆序对] - 数组有序性判断
3. 洛谷 P1177 [快速排序] - 分治与有序性验证

---

### 调试经验摘录
- **严格比较**：多个题解强调必须使用严格小于（`a[i] < minn`）而非小于等于，防止多个最小值干扰
- **位置索引**：注意数组下标从 1 开始还是 0 开始，原题样例显示应使用 1-based

---
处理用时：43.39秒