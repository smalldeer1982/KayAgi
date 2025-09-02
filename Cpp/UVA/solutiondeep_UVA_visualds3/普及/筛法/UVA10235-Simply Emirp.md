# 题目信息

# Simply Emirp

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=14&page=show_problem&problem=1176

[PDF](https://uva.onlinejudge.org/external/102/p10235.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10235/b3b8ea0ca3590b5800fc5123b088be54c52be882.png)

## 样例 #1

### 输入

```
17
18
19
179
199```

### 输出

```
17 is emirp.
18 is not prime.
19 is prime.
179 is emirp.
199 is emirp.```

# AI分析结果



**唯一算法分类**  
筛法

---

### **题解思路、算法要点与解决难点**  
**核心思路**  
1. **质数预处理**：使用筛法（线性筛或埃氏筛）预处理 1~1e6 的质数表，实现 O(1) 查询。  
2. **数字反转**：将数字逐位分解，逆序重组为反转数。  
3. **条件判断**：  
   - 原数非质数 → 输出 `not prime`。  
   - 原数是质数但反转数非质数或与原数相同 → 输出 `prime`。  
   - 原数和反转数均为质数且不相等 → 输出 `emirp`。  

**解决难点**  
- **高效质数判断**：筛法预处理将质数判断复杂度从 O(√n) 降至 O(1)。  
- **回文数处理**：需额外判断反转数与原数是否相等（如 11、101 等回文质数不算 `emirp`）。  

**算法对比**  
| 方法       | 时间复杂度 | 空间复杂度 | 适用场景         |  
|------------|------------|------------|------------------|  
| 线性筛     | O(n)       | O(n)       | 大规模质数预处理 |  
| 埃氏筛     | O(n log n) | O(n)       | 实现简单         |  
| 直接试除法 | O(√n)      | O(1)       | 单次小规模查询   |  

---

### **题解评分 (≥4星)**  
1. **BqtMtsZDnlpsT（5星）**  
   - 使用线性筛高效预处理，条件判断逻辑清晰。  
   - 代码简洁，注释明确，处理回文数直接。  
   - 亮点：线性筛实现严谨，避免重复标记。  

2. **SnapYust（4星）**  
   - 线性筛+反转函数分步分解数字。  
   - 代码结构清晰，反转逻辑直观。  
   - 个人心得：强调筛法与反转函数的正确性验证。  

3. **zesqwq（4星）**  
   - 预处理反转数优化查询，结合筛法提高效率。  
   - 创新点：递推计算反转数，减少运行时计算量。  

---

### **最优思路或技巧提炼**  
1. **线性筛优化**：仅用 O(n) 时间预处理质数，适合大规模数据。  
2. **回文数快速排除**：反转后与原数比较，避免字符串处理。  
3. **分步判断逻辑**：  
   ```cpp  
   if (!质数) → not prime  
   else if (反转数质数且非回文) → emirp  
   else → prime  
   ```  

---

### **同类型题或类似算法套路**  
- **质数预处理**：POJ 2262（哥德巴赫猜想）、LeetCode 204（统计质数个数）。  
- **数字操作**：LeetCode 7（整数反转）、LeetCode 9（回文数）。  

---

### **推荐题目**  
1. **洛谷 P3383**：线性筛模板题。  
2. **LeetCode 204**：统计质数个数（筛法应用）。  
3. **POJ 2262**：质数判断与组合。  

---

### **可视化与算法演示**  
**动画设计**  
1. **筛法过程**：  
   - **像素风格**：数字块按质数（绿色）/合数（红色）动态标记。  
   - **高亮操作**：当前筛的质数及其倍数标记为红色。  
   - **音效**：质数发现时播放清脆音效，合数标记时低沉音效。  

2. **反转数生成**：  
   - **分步展示**：原数逐位分解，反转后重组为独立数字块。  
   - **颜色标记**：原数（蓝色）、反转数（黄色）、质数验证（绿色/红色）。  

**交互功能**  
- **步进控制**：可暂停/继续观察筛法或反转步骤。  
- **自动演示**：AI模式自动运行筛法，带8-bit背景音乐。  

---

### **核心代码实现（线性筛+反转）**  
```cpp  
#include <iostream>
using namespace std;
const int MAX = 1e6 + 5;
bool isPrime[MAX];
int primes[MAX], cnt;

void sieve() {
    fill(isPrime, isPrime + MAX, true);
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; i < MAX; i++) {
        if (isPrime[i]) primes[cnt++] = i;
        for (int j = 0; j < cnt && i * primes[j] < MAX; j++) {
            isPrime[i * primes[j]] = false;
            if (i % primes[j] == 0) break;
        }
    }
}

int reverseNum(int n) {
    int rev = 0;
    while (n) {
        rev = rev * 10 + n % 10;
        n /= 10;
    }
    return rev;
}

int main() {
    sieve();
    int n;
    while (cin >> n) {
        if (!isPrime[n]) {
            cout << n << " is not prime.\n";
        } else {
            int rev = reverseNum(n);
            if (isPrime[rev] && rev != n) {
                cout << n << " is emirp.\n";
            } else {
                cout << n << " is prime.\n";
            }
        }
    }
    return 0;
}
```

---
处理用时：167.88秒