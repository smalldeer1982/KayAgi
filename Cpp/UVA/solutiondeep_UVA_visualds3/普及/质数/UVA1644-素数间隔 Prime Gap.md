# 题目信息

# 素数间隔 Prime Gap

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=825&page=show_problem&problem=4519

[PDF](https://uva.onlinejudge.org/external/16/p1644.pdf)

# AI分析结果



# 素数间隔 Prime Gap - 题解分析

## 唯一算法分类
**线性筛法（欧拉筛）**

---

## 题解思路与核心难点

### 核心算法流程
1. **预处理素数表**：用欧拉筛法在 O(n) 时间内筛出 [2, 1299709] 内的所有素数，存入数组。
2. **查询处理**：对每个输入 n：
   - 若 n 是素数 → 输出 0
   - 否则在素数数组中找到第一个大于 n 的素数 p，输出 p 与前一个素数的差值。

### 解决难点
- **筛法效率**：直接暴力判断素数会超时，必须用欧拉筛（线性筛）预处理。
- **快速查询**：遍历素数数组会导致 O(n) 查询时间，需用二分查找或 `lower_bound` 优化至 O(logn)。
- **输入处理**：需正确处理多组输入，避免死循环。

---

## 题解评分 (≥4星)

### 1. 珅肐的题解（5星）
- **亮点**：使用 `lower_bound` 直接定位，代码简洁高效。
- **关键代码**：
  ```cpp
  int o = lower_bound(prime+1, prime+cnt+1, n) - prime;
  printf("%d\n", prime[o] - prime[o-1]);
  ```

### 2. xixike的题解（4.5星）
- **亮点**：完整实现二分查找，逻辑清晰。
- **关键代码**：
  ```cpp
  int l=1, r=tot;
  while(l <= r) {
      int mid = (l + r) >> 1;
      if (p[mid] <= n) l = mid+1;
      else r = mid-1;
  }
  ```

### 3. 封禁用户的题解（4星）
- **亮点**：详细解释欧拉筛实现，但线性查找效率较低。
- **关键代码**：
  ```cpp
  for (int i=1; i<=ans; ++i)
      if (prime[i] > x) {
          printf("%d\n", prime[i] - prime[i-1]);
          break;
      }
  ```

---

## 最优思路提炼
1. **欧拉筛预处理**：避免重复标记合数，线性时间复杂度。
2. **二分查找优化**：利用素数数组有序性，快速定位相邻素数。
3. **边界处理**：特判 n=0 结束程序，正确处理多组输入。

---

## 同类型题目推荐
1. **P3383**（线性筛模板题）
2. **P1217**（回文素数，筛法+枚举）
3. **P3912**（统计素数个数，筛法应用）

---

## 可视化设计要点
### 欧拉筛过程动画
- **像素风格**：用 16 色网格表示数字，绿色为素数，红色为合数。
- **高亮操作**：当前筛选中，用黄色标记正在处理的数 i，蓝色标记被筛掉的 i*prime[j]。
- **音效**：筛掉合数时播放短促“滴”声，找到素数时播放上升音调。

### 二分查找演示
- **指针移动**：在素数数组上方显示左右指针 l 和 r，中间指针 mid 闪烁。
- **步进控制**：按空格键单步执行，显示比较的中间值。

### 复古 UI 示例（伪代码）
```javascript
// 初始化 Canvas
const canvas = document.getElementById("screen");
const ctx = canvas.getContext("2d");
const primes = [2, 3, 5, ...]; // 预处理数组

function drawStep(l, r, mid) {
    ctx.fillStyle = "#000";
    ctx.fillRect(0, 0, 640, 480); // 黑色背景
    primes.forEach((p, idx) => {
        if (idx >= l && idx <= r) ctx.fillStyle = "#0F0"; // 绿色区间
        if (idx === mid) ctx.fillStyle = "#FF0"; // 黄色中间点
        ctx.fillRect(idx*10, 100, 8, 8); // 绘制像素点
    });
}
```

---

## 核心代码实现
### 欧拉筛 + lower_bound（珅肐）
```cpp
bool is_not[1299807] = {1, 1};
int prime[100007], cnt;

void Prime() {
    for (int i=2; i<=1299709; ++i) {
        if (!is_not[i]) prime[++cnt] = i;
        for (int j=1; j<=cnt && i*prime[j] <= 1299709; ++j) {
            is_not[i*prime[j]] = 1;
            if (i % prime[j] == 0) break;
        }
    }
}

int main() {
    Prime();
    int n;
    while (scanf("%d", &n), n) {
        if (!is_not[n]) puts("0");
        else {
            int o = lower_bound(prime+1, prime+cnt+1, n) - prime;
            printf("%d\n", prime[o] - prime[o-1]);
        }
    }
    return 0;
}
```

---
处理用时：76.18秒