# 题目信息

# Switches and Lamps

## 题目描述

You are given $ n $ switches and $ m $ lamps. The $ i $ -th switch turns on some subset of the lamps. This information is given as the matrix $ a $ consisting of $ n $ rows and $ m $ columns where $ a_{i,j}=1 $ if the $ i $ -th switch turns on the $ j $ -th lamp and $ a_{i,j}=0 $ if the $ i $ -th switch is not connected to the $ j $ -th lamp.

Initially all $ m $ lamps are turned off.

Switches change state only from "off" to "on". It means that if you press two or more switches connected to the same lamp then the lamp will be turned on after any of this switches is pressed and will remain its state even if any switch connected to this lamp is pressed afterwards.

It is guaranteed that if you push all $ n $ switches then all $ m $ lamps will be turned on.

Your think that you have too many switches and you would like to ignore one of them.

Your task is to say if there exists such a switch that if you will ignore (not use) it but press all the other $ n-1 $ switches then all the $ m $ lamps will be turned on.

## 样例 #1

### 输入

```
4 5
10101
01000
00111
10000
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
4 5
10100
01000
00110
00101
```

### 输出

```
NO
```

# AI分析结果



**算法分类**：枚举与统计

---

### **题解思路与难点分析**
- **核心思路**：每个灯必须被至少一个非忽略的开关控制。若某个开关控制的灯中存在仅能被该开关控制的灯（`cnt[j] == 1`），则该开关不可忽略。否则，可以忽略。
- **解决难点**：通过预处理每个灯被控制的次数（`cnt`数组），快速判断每个开关是否可忽略。时间复杂度优化至 `O(nm)`，避免暴力枚举的高复杂度。
- **关键变量**：`cnt[j]` 表示灯 `j` 被多少开关控制。

---

### **题解评分（≥4星）**
1. **AutumnKite（5星）**  
   - 思路清晰，详细分析时间复杂度优化，代码规范。
   - 使用 `cnt` 数组统计每个灯的覆盖次数，直接判断开关是否可忽略。
2. **Zq_water（4星）**  
   - 代码简洁，直接统计并判断，逻辑清晰。
3. **xvl_（4星）**  
   - 变量命名规范，注释明确，代码可读性强。

---

### **最优思路提炼**
1. **预处理统计**：统计每个灯被控制的次数 `cnt[j]`。
2. **开关筛选**：遍历每个开关，检查其控制的灯是否全有 `cnt[j] ≥ 2`。若存在，则该开关可忽略。

---

### **同类型题与算法套路**
- **覆盖问题**：判断某元素是否为必要覆盖点（如必须存在的开关）。
- **类似题目**：
  1. CF984B Minesweeper（矩阵覆盖条件判断）
  2. P2587 [ZJOI2008]泡泡堂（策略选择）
  3. P1155 双栈排序（覆盖可行性分析）

---

### **推荐题目**
1. [CF984B](https://codeforces.com/problemset/problem/984/B)
2. [P2587](https://www.luogu.com.cn/problem/P2587)
3. [P1155](https://www.luogu.com.cn/problem/P1155)

---

### **可视化与算法演示**
- **动画设计**：
  - **网格展示**：用矩阵表示开关与灯的连接关系，灯用颜色区分覆盖次数（如红色表示 `cnt=1`，绿色表示 `cnt≥2`）。
  - **开关遍历**：高亮当前检查的开关，标记其控制的灯。若存在红色灯，标记该开关不可忽略；否则标记为可忽略。
  - **音效与反馈**：成功时播放胜利音效，失败时播放提示音。
- **复古像素风格**：
  - **颜色方案**：8位色调，开关为蓝色方块，灯为圆形像素点。
  - **交互控制**：支持步进执行，显示当前开关判断逻辑。

---

### **核心代码实现**
```cpp
#include <cstdio>
#include <cctype>
const int N = 2005;
int n, m, cnt[N];
char a[N][N];

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) {
            while (!isdigit(a[i][j] = getchar()));
            cnt[j] += a[i][j] ^ '0';
        }
    for (int i = 1; i <= n; ++i) {
        bool valid = true;
        for (int j = 1; j <= m; ++j)
            if (a[i][j] == '1' && cnt[j] == 1) valid = false;
        if (valid) return printf("YES"), 0;
    }
    printf("NO");
    return 0;
}
```

---

### **个人心得**
- **调试经验**：确保输入的字符处理正确，避免因空格或换行符导致错误。
- **优化关键**：预处理 `cnt` 数组避免重复计算，是降低时间复杂度的核心。

---
处理用时：127.58秒