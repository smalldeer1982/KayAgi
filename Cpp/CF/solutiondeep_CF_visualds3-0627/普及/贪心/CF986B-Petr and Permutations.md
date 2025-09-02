# 题目信息

# Petr and Permutations

## 题目描述

Petr likes to come up with problems about randomly generated data. This time problem is about random permutation. He decided to generate a random permutation this way: he takes identity permutation of numbers from $ 1 $ to $ n $ and then $ 3n $ times takes a random pair of different elements and swaps them. Alex envies Petr and tries to imitate him in all kind of things. Alex has also come up with a problem about random permutation. He generates a random permutation just like Petr but swaps elements $ 7n+1 $ times instead of $ 3n $ times. Because it is more random, OK?!

You somehow get a test from one of these problems and now you want to know from which one.

## 说明/提示

Please note that the sample is not a valid test (because of limitations for $ n $ ) and is given only to illustrate input/output format. Your program still has to print correct answer to this test to get AC.

Due to randomness of input hacks in this problem are forbidden.

## 样例 #1

### 输入

```
5
2 4 5 1 3
```

### 输出

```
Petr
```

# AI分析结果



### 综合分析与结论

**核心思路**：通过排列的交换次数或逆序对奇偶性判断生成方式。由于 `3n` 与 `7n+1` 的奇偶性不同，只需比较奇偶性即可确定答案。

**贪心策略**：每次将元素归位，统计交换次数的奇偶性。关键点在于每次交换必改变奇偶性，总次数奇偶性与 `3n` 或 `7n+1` 一致。

**难点与解决**：
1. **奇偶性推导**：每次交换改变奇偶性，总交换次数的奇偶性由 `3n` 和 `7n+1` 决定。
2. **高效实现**：贪心法以 O(n) 时间恢复排列，统计交换次数；逆序对法需高效计算奇偶性。

### 题解评分（≥4星）

1. **pufanyi（5星）**  
   - **亮点**：O(n) 贪心策略，直接统计交换次数奇偶性，代码简洁高效。  
   - **实现**：通过循环交换元素归位，每一步操作直观。  
   - **代码可读性**：清晰易懂，无复杂数据结构。

2. **Mr_Wu（4星）**  
   - **亮点**：利用树状数组计算逆序对奇偶性，逻辑严谨。  
   - **实现**：通过区间查询与单点修改高效维护逆序对数。  
   - **复杂度**：O(n log n)，适合熟悉树状数组的选手。

3. **大菜鸡fks（4星）**  
   - **亮点**：结合树状数组的逆序对计算，代码简洁。  
   - **优化**：直接记录奇偶性，减少内存占用。  

### 最优思路提炼

- **贪心策略**：每次交换当前元素至正确位置，统计总交换次数。  
- **奇偶性判断**：交换次数奇偶性与 `3n` 相同则为 Petr，否则为 Alex。  
- **实现关键**：  
  ```cpp
  for (int i = 1; i <= n; ++i) {
      while (a[i] != i) {
          swap(a[a[i]], a[i]);
          ans++;
      }
  }
  ```

### 同类型题目与算法套路

- **逆序对奇偶性**：适用于交换次数奇偶性问题（如排列生成、排序步骤判断）。  
- **贪心恢复排列**：用于最小交换次数统计或排列合法性验证。  

### 推荐题目

1. **P1908 逆序对**（树状数组/归并排序基础）  
2. **P1966 火柴排队**（逆序对应用，最小交换次数）  
3. **P1774 最接近神的人**（逆序对与排列性质）  

### 个人心得摘录

- **调试教训**：贪心法中需注意元素归位时的交换顺序，避免死循环。  
- **优化技巧**：逆序对奇偶性只需记录奇偶，无需具体数值。  

---

### 算法可视化设计

**贪心策略动画演示**：  
1. **像素风格界面**：用方格表示排列，元素值显示在格内。  
2. **高亮当前元素**：红色标记当前处理的 `i`，蓝色标记目标位置 `a[i]`。  
3. **交换动画**：元素飞向目标位置，计数器同步更新。  
4. **奇偶性提示**：右侧面板显示当前交换次数奇偶性，与 `3n` 对比。  

**复古游戏化效果**：  
- **音效**：交换时播放“哔”声，奇偶性匹配时播放胜利音效。  
- **自动模式**：AI 逐步执行交换，用户可调速或暂停观察。  

```javascript
// 示例：Canvas绘制排列（伪代码）
function drawArray(ctx, arr, highlightIdx) {
    arr.forEach((val, i) => {
        ctx.fillStyle = i === highlightIdx ? '#FF0000' : '#FFFFFF';
        ctx.fillRect(i * 50, 0, 48, 48);
        ctx.fillText(val, i * 50 + 10, 25);
    });
}
```

---

### 核心代码实现

**贪心法（pufanyi）**  
完整代码：  
```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 1e6+5;
int aa[maxn];

int main() {
    int n, ans = 0;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d", &aa[i]);
    for (int i = 1; i <= n; ++i) {
        while (aa[i] != i) {
            swap(aa[aa[i]], aa[i]);
            ans++;
        }
    }
    printf("%s", (n & 1) == (ans & 1) ? "Petr" : "Um_nik");
    return 0;
}
```

**树状数组逆序对（Mr_Wu）**  
关键片段：  
```cpp
for (i = 1; i <= n; i++) {
    ans = (ans + query(n) - query(a[i] - 1)) % 2; 
    insert(a[i], 1);
}
if ((ans - 3 * n) % 2 == 0) printf("Petr");
```

---
处理用时：84.99秒