# 题目信息

# Intercepted Message

## 题目描述

Hacker Zhorik wants to decipher two secret messages he intercepted yesterday. Yeah message is a sequence of encrypted blocks, each of them consists of several bytes of information.

Zhorik knows that each of the messages is an archive containing one or more files. Zhorik knows how each of these archives was transferred through the network: if an archive consists of $ k $ files of sizes $ l_{1},l_{2},...,l_{k} $ bytes, then the $ i $ -th file is split to one or more blocks $ b_{i,1},b_{i,2},...,b_{i,mi} $ (here the total length of the blocks $ b_{i,1}+b_{i,2}+...+b_{i,mi} $ is equal to the length of the file $ l_{i} $ ), and after that all blocks are transferred through the network, maintaining the order of files in the archive.

Zhorik thinks that the two messages contain the same archive, because their total lengths are equal. However, each file can be split in blocks in different ways in the two messages.

You are given the lengths of blocks in each of the two messages. Help Zhorik to determine what is the maximum number of files could be in the archive, if the Zhorik's assumption is correct.

## 说明/提示

In the first example the maximum number of files in the archive is 3. For example, it is possible that in the archive are three files of sizes $ 2+5=7 $ , $ 15=3+1+11=8+2+4+1 $ and $ 4+4=8 $ .

In the second example it is possible that the archive contains two files of sizes $ 1 $ and $ 110=10+100=100+10 $ . Note that the order of files is kept while transferring archives through the network, so we can't say that there are three files of sizes $ 1 $ , $ 10 $ and $ 100 $ .

In the third example the only possibility is that the archive contains a single file of size $ 4 $ .

## 样例 #1

### 输入

```
7 6
2 5 3 1 11 4 4
7 8 2 4 1 8
```

### 输出

```
3
```

## 样例 #2

### 输入

```
3 3
1 10 100
1 100 10
```

### 输出

```
2
```

## 样例 #3

### 输入

```
1 4
4
1 1 1 1
```

### 输出

```
1
```

# AI分析结果



---

**唯一算法分类**：双指针/前缀和

---

### **综合分析与结论**

**核心思路**：  
题目要求在两个数组中找到最多的分割点，使得每个分割点的前缀和相等。通过预处理前缀和数组，使用双指针同步遍历，每次移动总和较小的指针，直至找到相等点，统计这样的点数目即为最大文件数。

**解决难点**：  
- 如何高效找到所有满足条件的分割点？  
  维护两个前缀和数组，通过双指针同步遍历，保证每次比较的总是当前可能的相等点，避免重复计算。  
- 如何保证顺序正确？  
  双指针的移动确保分割点的前缀和严格递增，从而保证顺序一致。

**可视化设计**：  
- **动画方案**：  
  - 用两个横向条形图表示两数组的前缀和，指针 `i` 和 `j` 分别移动。  
  - **颜色标记**：当前比较的前缀和用红色高亮，相等时绿色闪烁并计数。  
  - **步进控制**：用户可调整速度或手动点击步进，观察指针移动逻辑。  
- **复古像素风格**：  
  - 用 8-bit 像素块表示数组元素，指针移动时播放“滴”声，找到相等点时播放“叮”声。  
  - 背景音乐为循环的芯片音乐，增加沉浸感。

---

### **题解清单 (≥4星)**

1. **信守天下（5星）**  
   - **亮点**：  
     - 代码简洁，直接遍历前缀和数组，用双指针同步移动。  
     - 时间复杂度 `O(n + m)`，高效且易理解。  
     - 通过注释明确逻辑，可读性极佳。  
   - **代码片段**：  
     ```cpp
     int j = 1, ans = 0;
     for (int i = 1; i <= n; i++) {
         while (j <= m && a[i] > b[j]) j++;
         ans += (a[i] == b[j] && j <= m);
     }
     ```

2. **某某x（4星）**  
   - **亮点**：  
     - 与信守天下思路一致，代码风格略有不同。  
     - 使用宏简化循环，代码紧凑。  
   - **代码片段**：  
     ```cpp
     _rep(1, n, i) {
         while(j <= m && a[i] > b[j]) j++;
         ans += (a[i]==b[j]&&j<=m);
     }
     ```

---

### **最优思路提炼**

**关键步骤**：  
1. 预处理两数组的前缀和数组 `a` 和 `b`。  
2. 初始化指针 `i=1`, `j=1`，从头遍历。  
3. 每次比较 `a[i]` 和 `b[j]`：  
   - 若 `a[i] < b[j]`，则 `i++`（增大 `a` 的前缀和）。  
   - 若 `a[i] > b[j]`，则 `j++`（增大 `b` 的前缀和）。  
   - 若相等，则计数加一，`i++`, `j++`。  

**技巧总结**：  
- 利用前缀和将问题转化为双指针同步遍历。  
- 贪心思想：每次尽可能匹配最小可能的相等点，避免遗漏。  

---

### **同类型题与算法套路**

**类似题目**：  
- **最长公共子数组**：要求连续子数组和相等。  
- **分割数组为相等部分**：如 LeetCode 548. Split Array with Equal Sum。  

**通用套路**：  
- 前缀和预处理，将区间和问题转化为前缀和差值。  
- 双指针用于有序或部分有序序列的同步遍历。

---

### **推荐题目**

1. **洛谷 P1115**：最大子段和（前缀和与贪心）。  
2. **LeetCode 88**：合并两个有序数组（双指针）。  
3. **Codeforces 978C**：Letters（前缀和+二分查找）。

---

### **个人心得摘录**

- **信守天下**：  
  “注意两个数组的前缀和必须严格递增，才能保证双指针的正确性。”  
- **某某x**：  
  “遍历第一个数组，同时在第二个数组中动态调整指针，避免暴力匹配。”  

---

### **代码实现（信守天下）**

```cpp
#include <iostream>
using namespace std;
const int kMaxN = 1e5 + 1;
int a[kMaxN], b[kMaxN], n, m, ans, j = 1;

int main() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    a[i] += a[i - 1];
  }
  for (int i = 1; i <= m; i++) {
    cin >> b[i];
    b[i] += b[i - 1];
  }
  for (int i = 1; i <= n; i++) {
    while (j <= m && a[i] > b[j]) j++;
    ans += (a[i] == b[j] && j <= m);
  }
  cout << ans;
  return 0;
}
```

---
处理用时：222.91秒