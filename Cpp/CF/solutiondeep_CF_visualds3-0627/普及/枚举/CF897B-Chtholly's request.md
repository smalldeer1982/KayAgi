# 题目信息

# Chtholly's request

## 题目描述

 — Thanks a lot for today.— I experienced so many great things.

— You gave me memories like dreams... But I have to leave now...

— One last request, can you...

— Help me solve a Codeforces problem?

— ......

— What?





Chtholly has been thinking about a problem for days:

If a number is palindrome and length of its decimal representation without leading zeros is even, we call it a zcy number. A number is palindrome means when written in decimal representation, it contains no leading zeros and reads the same forwards and backwards. For example 12321 and 1221 are palindromes and 123 and 12451 are not. Moreover, 1221 is zcy number and 12321 is not.

Given integers $ k $ and $ p $ , calculate the sum of the $ k $ smallest zcy numbers and output this sum modulo $ p $ .

Unfortunately, Willem isn't good at solving this kind of problems, so he asks you for help!

## 说明/提示

In the first example, the smallest zcy number is $ 11 $ , and the second smallest zcy number is $ 22 $ .

In the second example, ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF897B/8301f23cf6a6ac38a43acd044c106b422734f787.png).

## 样例 #1

### 输入

```
2 100
```

### 输出

```
33
```

## 样例 #2

### 输入

```
5 30
```

### 输出

```
15
```

# AI分析结果



1. **算法分类选择**  
   - **构造**

2. **题解思路、算法要点与解决难点**  
   - **核心思路**：所有 zcy 数均可通过将自然数 i 与其数字反序拼接生成（如 i=10 → 1001）。  
   - **实现关键**：  
     - 计算 i 的反转数（如 12 → 21）  
     - 构造回文数 = i × 10^d + 反转数（d 为 i 的位数）  
   - **难点突破**：正确处理含末尾零的 i（如 i=100 → 100001），需用原数位数而非反转数位数计算 10^d。

3. **题解评分 (≥4星)**  
   - **fjy666 (5星)**：高效计算位数与反转，数学推导清晰，代码简洁。  
   - **XL4453 (5星)**：直接逐位构造回文数，代码高效无冗余。  
   - **Sai0511 (4星)**：正确但实现稍复杂，通过 j 变量计算位数，本质同前两种。

4. **最优思路或技巧提炼**  
   - **构造公式**：zcy(i) = i × 10^d + reverse(i)，其中 d 是 i 的位数。  
   - **优化技巧**：用循环计算位数（d = floor(log10(i)) + 1），避免字符串操作。

5. **同类型题或类似算法套路**  
   - 回文数构造类问题（如 P1217 回文质数）  
   - 数字拼接与反转（如 P1307 数字反转）

6. **推荐洛谷题目**  
   - P1015（回文数）  
   - P1217（回文质数）  
   - P1307（数字反转）

7. **个人心得摘录**  
   - **fjy666**：强调位数计算需用原数，避免反转后丢失前导零。  
   - **chengni**：调试输出可能导致 TLE，需删除无关打印。

8. **可视化与算法演示**  
   - **动画设计**：  
     - **步骤分解**：展示 i=12 → 反转 21 → 拼接为 1221。  
     - **高亮元素**：i 的每一位（红色）、反转过程（蓝色箭头）、拼接结果（绿色）。  
   - **复古像素风格**：用 8-bit 字体显示数字，拼接时播放「拼接音效」，成功累加后触发「金币音效」。  
   - **交互控制**：允许调整 i 的值，实时查看构造过程与总和变化。

---

**代码片段（核心逻辑）**  
```cpp
// fjy666 题解核心代码
int Reverse(int x) {
    int ans = 0;
    while (x) {
        ans = ans * 10 + x % 10;
        x /= 10;
    }
    return ans;
}

int Log10_(int x) {
    int ans = 1;
    while (x) {
        ans *= 10;
        x /= 10;
    }
    return ans;
}

int main() {
    int k, p, ans = 0;
    scanf("%d%d", &k, &p);
    for (int i = 1; i <= k; ++i) {
        int d = Log10_(i); // 计算 10^d（d为i的位数）
        int rev = Reverse(i);
        ans = (ans + (i * d + rev)) % p;
    }
    printf("%d", ans);
}
```

---

**可视化实现要点**  
- **像素风格**：用 Canvas 绘制 16x16 像素数字块，i 的每位用不同颜色区分。  
- **音效触发**：  
  - 反转数字时播放「blip」音效（每次取模）。  
  - 完成一个 zcy 数时播放「ding」音效。  
- **自动演示**：按固定时间间隔递增 i，实时更新构造过程与总和。

---
处理用时：135.07秒