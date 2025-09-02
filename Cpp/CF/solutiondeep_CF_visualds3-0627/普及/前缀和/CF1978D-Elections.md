# 题目信息

# Elections

## 题目描述

Elections are taking place in Berland. There are $ n $ candidates participating in the elections, numbered from $ 1 $ to $ n $ . The $ i $ -th candidate has $ a_i $ fans who will vote for him. Additionally, there are $ c $ people who are undecided about their favorite candidate, let's call them undecided. Undecided people will vote for the candidate with the lowest number.

The candidate who receives the maximum number of votes wins the elections, and if multiple candidates receive the same maximum number of votes, the candidate with the lowest number among them wins.

You found these elections too boring and predictable, so you decided to exclude some candidates from them. If you do not allow candidate number $ i $ to participate in the elections, all $ a_i $ of his fans will become undecided, and will vote for the candidate with the lowest number.

You are curious to find, for each $ i $ from $ 1 $ to $ n $ , the minimum number of candidates that need to be excluded from the elections for candidate number $ i $ to win the elections.

## 说明/提示

In the first test case:

- If all candidates are allowed, candidate number $ 1 $ will receive $ 3 $ votes ( $ 1 $ undecided person will vote for him), candidate number $ 2 $ will receive $ 0 $ votes, and candidate number $ 3 $ will receive $ 3 $ votes. Therefore, candidate number $ 1 $ wins (he received the same number of votes as candidate $ 3 $ , but his number is lower), so the answer for him is $ 0 $ .
- If candidate number $ 1 $ is not allowed, his $ 2 $ fans will become undecided. Then candidate number $ 2 $ will receive $ 3 $ votes ( $ 3 $ undecided people will vote for him) and candidate number $ 3 $ will receive $ 3 $ votes. Therefore, candidate number $ 2 $ wins (he received the same number of votes as candidate $ 3 $ , but his number is lower), so the answer for him is $ 1 $ .
- If candidates with numbers $ 1 $ and $ 2 $ are not allowed, candidate number $ 3 $ wins, so the answer for him is $ 2 $ .

In the second test case, candidate number $ 1 $ will win if candidate number $ 2 $ is not allowed to participate.

## 样例 #1

### 输入

```
5
3 1
2 0 3
2 3
0 10
5 3
5 4 3 2 1
4 5
3 10 7 1
6 0
2 2 2 3 3 3```

### 输出

```
0 1 2
1 0
0 1 2 3 4
1 0 2 3
1 1 2 0 4 5```

# AI分析结果



### 算法分类
贪心、前缀和与后缀极值

### 题解思路、算法要点与解决难点
**核心思路**：  
对于每个候选人i，若其要获胜，必须排除所有编号更小的候选人（确保其获得所有未决定票），此时总票数为前缀和sum[i]。若sum[i]仍不足，则需再排除后续最大值候选人。

**算法要点**：  
1. **预处理**：将初始的c加到第一个候选人的票数，保证后续计算包含初始未决定票。
2. **前缀和数组sum**：sum[i]表示前i个候选人的总票数（含初始c）。
3. **后缀最大值数组hou**：hou[i]表示从i到n中的最大票数。
4. **决策逻辑**：
   - 若i是初始最大值，答案为0。
   - 否则，必须排除前i-1人，此时i的总票数为sum[i]。若sum[i] >= 后续最大值hou[i+1]，答案为i-1；否则需再排除一个最大值，答案为i。

**解决难点**：  
- **正确性验证**：需确保排除前i-1人后，后续的最大值不会影响i的胜利。通过后缀最大值数组快速判断后续是否存在更大票数。
- **复杂度优化**：前缀和和后缀极值均为O(n)预处理，每个候选人的判断为O(1)，整体复杂度O(n)。

---

### 题解评分（≥4星）
1. **hh弟中弟（5星）**  
   - 思路清晰，代码简洁，正确使用前缀和与后缀极值。
   - 关键变量命名明确（sum为前缀和，max为后缀最大值）。
   - 高效处理边界条件，如初始最大值判断。

2. **szh_AK_all（5星）**  
   - 逻辑完整，逐步累加前i-1人的票数（变量qian），实现与前缀和等价。
   - 后缀极值处理与比较逻辑正确，可读性高。

3. **Lu_xZ（4星）**  
   - 代码正确，使用后缀数组suf比较后续最大值。
   - 变量名suf更直观，但缺少对初始最大值的显式查找。

---

### 最优思路提炼
1. **预处理技巧**：将初始c加到第一个候选人，简化后续计算。
2. **极值预处理**：通过后缀极值数组快速获取后续最大值。
3. **贪心决策**：排除前i-1人后，仅需比较一次后续最大值即可确定是否需排除更多候选人。

---

### 同类型题与类似算法套路
- **类似问题**：分界点问题（如左边满足某条件，右边满足另一条件）。
- **通用解法**：前缀和+后缀极值预处理，快速判断分界点后的状态。

**推荐题目**：  
1. [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)  
2. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)  
3. [P1440 求m区间内的最小值](https://www.luogu.com.cn/problem/P1440)  

---

### 代码片段（核心逻辑）
```cpp
// 预处理前缀和与后缀最大值
a[1] += c;
for (int i = 1; i <= n; ++i) sum[i] = sum[i-1] + a[i];
for (int i = n; i >= 1; --i) hou[i] = max(hou[i+1], a[i]);

// 判断每个候选人的答案
for (int i = 1; i <= n; ++i) {
    if (i == initial_max_idx) {
        cout << 0 << " ";
    } else {
        int ans = i-1;
        if (sum[i] < hou[i+1]) ans++;
        cout << ans << " ";
    }
}
```

---

### 可视化与算法演示
**动画方案**：  
1. **初始化**：显示候选人队列，第一个候选人票数高亮（含c）。
2. **排除前i-1人**：灰色标记被排除的候选人，蓝色标记当前候选人i。
3. **票数对比**：红色高亮后续最大值候选人，动态比较sum[i]与hou[i+1]。
4. **结果反馈**：若sum[i]足够，绿色标记i；否则排除后续最大值（红色候选人消失，i的票数增加）。

**复古像素风格**：  
- 候选人用16x16像素块表示，票数以8位字体显示。
- 音效设计：排除时播放“哔”声，成功时播放“胜利”音效，失败后播放“错误”音效。
- **自动演示**：按i从1到n逐步执行，用户可暂停/调整速度。

**交互控制**：  
- **步进按钮**：手动触发每一步操作。
- **速度滑块**：调节动画速度（0.5x~2x）。
- **高亮开关**：切换是否显示后续最大值。

---

### 个人心得摘录
> "在正确理解题意的情况下，D题的关键思路较为直接，但需注意后缀极值的预处理方向。" —— hh弟中弟  
> "比赛时因后缀极值计算方向错误导致WA，深刻教训！" —— CarroT1212

---

### 总结
本题通过前缀和与后缀极值的结合，高效处理了每个候选人的最优排除策略。正确预处理和极值比较是解题核心，代码实现简洁且高效。

---
处理用时：414.22秒