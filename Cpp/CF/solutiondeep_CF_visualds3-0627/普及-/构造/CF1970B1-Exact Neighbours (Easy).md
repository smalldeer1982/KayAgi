# 题目信息

# Exact Neighbours (Easy)

## 题目描述

The only difference between this and the hard version is that all $ a_{i} $ are even.

After some recent attacks on Hogwarts Castle by the Death Eaters, the Order of the Phoenix has decided to station $ n $ members in Hogsmead Village. The houses will be situated on a picturesque $ n\times n $ square field. Each wizard will have their own house, and every house will belong to some wizard. Each house will take up the space of one square.

However, as you might know wizards are very superstitious. During the weekends, each wizard $ i $ will want to visit the house that is exactly $ a_{i} $ $ (0 \leq a_{i} \leq n) $ away from their own house. The roads in the village are built horizontally and vertically, so the distance between points $ (x_{i}, y_{i}) $ and $ (x_{j}, y_{j}) $ on the $ n\times n $ field is $  |x_{i} - x_{j}| + |y_{i} - y_{j}| $ . The wizards know and trust each other, so one wizard can visit another wizard's house when the second wizard is away. The houses to be built will be big enough for all $ n $ wizards to simultaneously visit any house.

Apart from that, each wizard is mandated to have a view of the Hogwarts Castle in the north and the Forbidden Forest in the south, so the house of no other wizard should block the view. In terms of the village, it means that in each column of the $ n\times n $ field, there can be at most one house, i.e. if the $ i $ -th house has coordinates $ (x_{i}, y_{i}) $ , then $ x_{i} \neq x_{j} $ for all $ i \neq j $ .

The Order of the Phoenix doesn't yet know if it is possible to place $ n $ houses in such a way that will satisfy the visit and view requirements of all $ n $ wizards, so they are asking for your help in designing such a plan.

If it is possible to have a correct placement, where for the $ i $ -th wizard there is a house that is $ a_{i} $ away from it and the house of the $ i $ -th wizard is the only house in their column, output YES, the position of houses for each wizard, and to the house of which wizard should each wizard go during the weekends.

If it is impossible to have a correct placement, output NO.

## 说明/提示

For the sample, the house of the 1st wizard is located at $ (4, 4) $ , of the 2nd at $ (1, 3) $ , of the 3rd at $ (2, 4) $ , of the 4th at $ (3, 1) $ .

The distance from the house of the 1st wizard to the house of the 1st wizard is $ |4 - 4| + |4 - 4| = 0 $ .

The distance from the house of the 2nd wizard to the house of the 1st wizard is $ |1 - 4| + |3 - 4| = 4 $ .

The distance from the house of the 3rd wizard to the house of the 1st wizard is $ |2 - 4| + |4 - 4| = 2 $ .

The distance from the house of the 4th wizard to the house of the 3rd wizard is $ |3 - 2| + |1 - 4| = 4 $ .

The view and the distance conditions are satisfied for all houses, so the placement is correct.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1970B1/9f9f415b711c20a1d43262d4b959c18fec467842.png)

## 样例 #1

### 输入

```
4
0 4 2 4```

### 输出

```
YES
4 4
1 3
2 4
3 1
1 1 1 3```

# AI分析结果



**算法分类**  
构造

---

### **题解思路、算法要点与解决难点**
**核心思路**  
题目要求每个巫师的房子位于不同列，且每个巫师需找到曼哈顿距离为偶数 \(a_i\) 的目标。所有 \(a_i\) 均为偶数，构造方法如下：  
1. **坐标构造**：将每个巫师的房子放在对角线上，即坐标为 \((i, i)\)。此时，不同列的条件自动满足。  
2. **目标选择**：对于巫师 \(i\)，其目标为坐标 \((j, j)\)，满足曼哈顿距离 \(2|i-j| = a_i\)。解得 \(j = i \pm a_i/2\)，需确保 \(j\) 在合法范围 \([1, n]\) 内。  

**解决难点**  
- 确保所有 \(a_i\) 均为偶数，从而 \(a_i/2\) 是整数，使得曼哈顿距离为偶数的条件成立。  
- 通过构造对角线坐标，避免复杂的列冲突检测。  

**关键步骤**  
- 坐标生成：直接输出 \((i, i)\)。  
- 目标计算：根据 \(a_i/2\) 的值，选择 \(j = i + a_i/2\) 或 \(j = i - a_i/2\)，优先选择不越界的方案。  

---

### **题解评分（≥4星）**
1. **JOE_ZengYuQiao_0928（4星）**  
   - 思路清晰：直接构造对角线坐标，简化问题。  
   - 代码简洁：通过简单条件判断处理越界，可读性高。  
   - 优化程度：时间复杂度 \(O(n)\)，空间复杂度 \(O(n)\)。  

2. **Tjl0427（4星）**  
   - 实现一致：与上题解思路相同，代码逻辑清晰。  
   - 代码规范：注释和输入输出处理良好。  

3. **zjzx_wcj（4星）**  
   - 思路明确：Python 实现同样采用对角线构造。  
   - 代码简洁：输入处理直接，逻辑清晰。  

---

### **最优思路或技巧提炼**
1. **对角线构造**：利用坐标 \((i, i)\) 确保列唯一性，简化曼哈顿距离计算。  
2. **偶数距离拆分**：将 \(a_i\) 拆分为 \(2|i-j|\)，避免复杂坐标搜索。  
3. **越界处理**：优先判断 \(i - a_i/2\) 是否合法，否则取反向操作。  

---

### **同类型题或类似算法套路**
- **构造类问题**：通过特定坐标或排列方式满足条件（如网格布局、唯一性约束）。  
- **曼哈顿距离优化**：利用对称性或特殊位置（如对角线）简化距离计算。  

---

### **推荐相似题目**
1. **CF1970B2**：同一题的困难版本（需处理奇数 \(a_i\)）。  
2. **洛谷P1005**：矩阵取数游戏，构造动态规划策略。  
3. **洛谷P1219**：八皇后问题，需满足行、列、对角线唯一性。  

---

### **个人心得摘录**
- **构造优先**：对于约束条件较多的题目，优先考虑特殊构造（如对角线）简化问题。  
- **边界处理**：注意 \(i \pm a_i/2\) 的越界判断，确保合法性。  

---

### **可视化与算法演示**
**动画设计**：  
1. **像素风格**：使用 8-bit 网格，每个巫师表示为彩色方块，对角线坐标用高亮色标记。  
2. **目标连线**：点击巫师后，动态显示其目标路径（红色连线），距离数值浮动显示。  
3. **音效触发**：成功放置时播放“成功音效”，越界操作触发“错误音效”。  

**关键步骤高亮**：  
- **坐标生成**：对角线方块逐个出现，颜色渐变。  
- **目标计算**：动态计算 \(a_i/2\)，箭头指示 \(j = i \pm a_i/2\) 的方向。  

---

### **代码实现（核心逻辑）**
```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    
    // 输出坐标
    cout << "YES\n";
    for (int i = 1; i <= n; i++) 
        cout << i << " " << i << "\n";
    
    // 输出目标
    for (int i = 1; i <= n; i++) {
        int delta = a[i] / 2;
        if (i - delta >= 1) cout << i - delta << " ";
        else cout << i + delta << " ";
    }
    return 0;
}
```

---
处理用时：354.23秒