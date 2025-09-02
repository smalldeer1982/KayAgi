# 题目信息

# Robot Vacuum Cleaner

## 题目描述

Pushok the dog has been chasing Imp for a few hours already.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF922D/829d42ff73514382387680ad82853edceea77a87.png)Fortunately, Imp knows that Pushok is afraid of a robot vacuum cleaner.

While moving, the robot generates a string $ t $ consisting of letters 's' and 'h', that produces a lot of noise. We define noise of string $ t $ as the number of occurrences of string "sh" as a subsequence in it, in other words, the number of such pairs $ (i,j) $ , that $ i<j $ and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF922D/f1a56c1d084d739e6652be99271753eea487f10e.png) and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF922D/1c020fe0ca945d3f2fc54f71a604c6ab2188fcee.png).

The robot is off at the moment. Imp knows that it has a sequence of strings $ t_{i} $ in its memory, and he can arbitrary change their order. When the robot is started, it generates the string $ t $ as a concatenation of these strings in the given order. The noise of the resulting string equals the noise of this concatenation.

Help Imp to find the maximum noise he can achieve by changing the order of the strings.

## 说明/提示

The optimal concatenation in the first sample is $ ssshhshhhs $ .

## 样例 #1

### 输入

```
4
ssh
hs
s
hhhs
```

### 输出

```
18
```

## 样例 #2

### 输入

```
2
h
s
```

### 输出

```
1
```

# AI分析结果



---

**唯一算法分类**：贪心

---

### **题解思路、算法要点与解决难点**

**核心问题**：如何排列多个字符串，使得拼接后的总字符串中“sh”子序列数目最大化。

**关键思路**：
1. **内部贡献固定**：每个字符串自身的“sh”数目在任意顺序下不变。
2. **交叉贡献最大化**：相邻字符串的排列顺序影响它们之间的“sh”数目。设字符串A有`s_a`个s和`h_a`个h，字符串B有`s_b`个s和`h_b`个h，当且仅当`s_a * h_b > s_b * h_a`时，A应排在B前。
3. **贪心排序**：将字符串按上述条件排序，确保相邻字符串的交叉贡献最大。

**解决难点**：
- **排序条件推导**：需证明按`s_i/h_i`降序排列最优（等价于比较`s_i * h_j > s_j * h_i`）。
- **高效计算总贡献**：利用前缀和累加交叉贡献，避免拼接大字符串。

---

### **题解评分 (≥4星)**

1. **MattL（★★★★★）**  
   - 思路清晰，直接推导排序条件，代码简洁高效。  
   - 预处理每个字符串的s/h数目，排序后遍历一次计算总贡献。  
   - 强调`long long`避免溢出，实践性强。

2. **chlchl（★★★★☆）**  
   - 详细解释贪心策略和贡献计算。  
   - 代码拼接字符串后统一计算贡献，直观但稍显冗余。  
   - 提供“小技巧”优化统计过程。

3. **JK_LOVER（★★★★☆）**  
   - 明确贡献拆分（内部+交叉），代码逻辑清晰。  
   - 结构体存储s/h数目，排序条件与核心思路一致。

---

### **最优思路提炼**

1. **贪心排序策略**：  
   - 比较两个字符串A和B的排序条件为 `A.s * B.h > B.s * A.h`。
2. **前缀和优化**：  
   - 维护前缀s的总数，遍历时累加当前字符串的h数目乘以前缀和。
3. **分步贡献计算**：  
   - 先统计每个字符串内部的“sh”数目，再处理交叉贡献。

---

### **可视化与算法演示设计**

**核心流程动画**：
1. **字符串排序过程**：  
   - 以网格形式显示每个字符串的s/h数目，用箭头表示比较和交换操作。  
   - 高亮当前比较的字符串对，动态显示条件判断结果（如绿色通过，红色不通过）。
2. **贡献累加演示**：  
   - 遍历排序后的字符串时，逐步显示前缀和`cnt`的更新和交叉贡献的计算。  
   - 每步用颜色标记当前处理的字符串和对应的前缀s总数。

**复古像素风格设计**：
- **界面**：8位像素风格，字符串显示为方格块，s为蓝色方块，h为红色方块。  
- **音效**：比较时播放“滴”声，交换时播放“咔嚓”声，贡献累加时播放金币音效。  
- **自动演示模式**：模拟排序过程，逐步展示最优排列的生成。

---

### **代码实现（核心逻辑）**

```cpp
#include <bits/stdc++.h>
using namespace std;
struct Node { long long s, h; };
vector<Node> strs;

bool cmp(Node &a, Node &b) {
    return a.s * b.h > b.s * a.h; // 核心排序条件
}

int main() {
    int n; cin >> n;
    long long ans = 0, prefix_s = 0;
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        Node node{0, 0};
        for (char c : s) {
            if (c == 's') node.s++;
            else node.h++, ans += node.s; // 内部贡献
        }
        strs.push_back(node);
    }
    sort(strs.begin(), strs.end(), cmp); // 贪心排序
    for (auto &node : strs) {
        ans += prefix_s * node.h; // 交叉贡献
        prefix_s += node.s;       // 更新前缀s总数
    }
    cout << ans << endl;
    return 0;
}
```

---

### **相似题目推荐**

1. **P1090 [NOIP2004 提高组] 合并果子**  
   - 贪心策略：每次合并最小的两堆。
2. **P1233 木棍加工**  
   - 贪心排序后动态规划。
3. **CF1132F Clear the String**  
   - 区间DP，考虑子串删除顺序的影响。

---

### **个人心得摘录**

- **MattL**：“十年OI一场空，忘开`long long`见祖宗” —— 强调数据范围的重要性。  
- **chlchl**：“五年OI一场空” —— 多次提醒溢出风险，体现调试经验。  
- **Xdl_rp**：通过`cal(x+y)`隐式推导排序条件，代码简洁但效率略低。

---
处理用时：96.78秒