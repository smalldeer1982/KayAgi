# 题目信息

# Decode

## 题目描述

In a desperate attempt to obtain your waifu favorite character, you have hacked into the source code of the game. After days of struggling, you finally find the binary string that encodes the gacha system of the game. In order to decode it, you must first solve the following problem.

You are given a binary string $ s $ of length $ n $ . For each pair of integers $ (l, r) $ $ (1 \leq l \leq r \leq n) $ , count the number of pairs $ (x, y) $ $ (l \leq x \leq y \leq r) $ such that the amount of $ \mathtt{0} $ equals the amount of $ \mathtt{1} $ in the substring $ s_xs_{x+1}...s_y $ .

Output the sum of counts over all possible $ (l, r) $ modulo $ 10^9+7 $ .

## 样例 #1

### 输入

```
4
0000
01010101
1100111001
11000000111```

### 输出

```
0
130
147
70```

# AI分析结果



**唯一算法分类**  
前缀和与哈希表

---

**综合分析与结论**  
本题要求统计所有父区间中包含等量0/1的子区间的总贡献。核心思路是将0视为-1，1视为1，计算前缀和。若两位置前缀和相等，则中间区间合法。通过哈希表动态维护每个前缀和的历史出现次数及左端点贡献总和，遍历时累加右端点贡献。

**可视化设计思路**：  
- **动画方案**：以网格展示字符串各字符，动态显示前缀和数值。当遇到相同sum值时，高亮当前i与前缀位置j，并显示贡献计算式 `(j+1)*(n-i+1)`。  
- **颜色标记**：当前字符高亮为橙色，sum值变化用不同色块标记。匹配时触发绿色闪光，贡献数值弹出显示。  
- **步进控制**：支持暂停/继续，单步观察哈希表更新过程。  
- **复古风格**：采用8位像素风，前缀和数值以复古字体显示，音效使用短促电子音（如匹配时“哔”声）。

---

**题解清单 (≥4星)**  
1. **ZhaoV1（5星）**：代码简洁高效，利用map维护前缀和，直接累加贡献。  
2. **PineappleSummer（4星）**：思路清晰，通过偏移数组优化时间复杂度。  
3. **yemuzhe（4星）**：详细推导贡献公式，数组处理负数更高效。  

---

**最优思路与代码片段**  
**核心逻辑**：遍历时维护前缀和sum，用哈希表记录各sum对应的左端点贡献总和。贡献公式为 `sum_occurrences * (n - i +1)`，更新哈希表时累加 `i+1`。  
**代码实现**：  
```cpp
int sum = 0, res = 0;
map<int, int> mp;
mp[0] = 1;
for (int i = 1; i <= n; i++) {
    sum += (s[i] == '1' ? 1 : -1);
    res = (res + mp[sum] * (n - i + 1)) % MOD;
    mp[sum] = (mp[sum] + i + 1) % MOD;
}
```

---

**同类型题与算法套路**  
- **前缀和+哈希表**：适用于区间统计问题（如和为k的子数组、最长平衡子串）。  
- **贡献拆分**：将复杂统计转化为每个元素的独立贡献。  

**推荐题目**  
1. P1863 统计全为1的子矩阵（前缀和+哈希表）  
2. CF977E 周期子串（平衡计数）  
3. LeetCode 525 连续数组（等量0/1最长子数组）  

---

**个人心得摘录**  
- **ZhaoV1**：强调前缀和相等时的贡献拆分，避免暴力枚举。  
- **yemuzhe**：推导贡献公式时注意左端点需+1，易错点提醒。  

---

**可视化与复古效果实现**  
```javascript
// 示例：Canvas绘制前缀和变化与贡献计算
ctx.fillStyle = '#8B00FF'; // 复古紫色
ctx.fillRect(x, y, 16, 16); // 像素块
// 音效触发
function playBeep() {
    const osc = audioCtx.createOscillator();
    osc.frequency.setValueAtTime(800, audioCtx.currentTime);
    osc.connect(audioCtx.destination);
    osc.start(); osc.stop(0.1);
}
// 自动演示循环
setInterval(() => {
    if (autoPlay) stepAlgorithm();
}, 1000 / speed);
```  
**游戏化规则**：每正确匹配一次sum得10分，连击（连续匹配）触发额外奖励音效。

---
处理用时：81.34秒