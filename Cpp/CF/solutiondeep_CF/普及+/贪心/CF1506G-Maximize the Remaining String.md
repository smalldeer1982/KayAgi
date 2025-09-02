# 题目信息

# Maximize the Remaining String

## 题目描述

给你一个由小写英文字母组成的字符串 $s$，你需要去掉一部分字符，使得操作后得到的字符串 $t$ 满足在 $s$ 中出现的字母每种只保留一个并且最大化 $t$ 的字典序。

## 样例 #1

### 输入

```
6
codeforces
aezakmi
abacaba
convexhull
swflldjgpaxs
myneeocktxpqjpz```

### 输出

```
odfrces
ezakmi
cba
convexhul
wfldjgpaxs
myneocktxqjpz```

# AI分析结果



### 中文题目重写
#### 题目描述
给定一个由小写字母组成的字符串 $s$，你需要删除部分字符，使得操作后得到的字符串 $t$ 满足以下条件：
1. $t$ 中每个在 $s$ 中出现的字符恰好保留一个
2. $t$ 的字典序尽可能大

#### 样例输入与输出
（与原文样例一致，此处省略）

---

### 题解综合分析
所有题解均采用**贪心+单调栈**的核心思路，差异主要体现在实现细节和数据结构选择。关键难点在于保证删除字符后仍能保留所有字符，同时通过局部最优达到全局最大字典序。

---

### 精选题解与评分
#### 1. 题解作者：liangbowen（★★★★★）
**关键亮点**：
- 使用标准单调栈实现，代码结构清晰
- 用 `cnt[]` 数组动态维护字符剩余次数
- 正确处理多测试用例清空问题
- 包含详细的代码注释

**核心代码**：
```cpp
stack<int> stk;
for (int i = 0; i < len; i++) {
    int x = s[i] - 'a';
    if (!instk[x]) {
        // 维护单调性：栈顶可删且当前字符更大时弹出
        while (!stk.empty() && cnt[stk.top()] && x > stk.top()) 
            instk[stk.top()] = false, stk.pop();
        stk.push(x), instk[x] = true;
    }
    cnt[x]--; // 关键：无论是否入栈都减少计数
}
```

#### 2. 题解作者：SpeedStar（★★★★☆）
**关键亮点**：
- 预处理最后出现位置，优化判断逻辑
- 使用字符串直接模拟栈操作
- 明确关联LeetCode原题（316.去除重复字母）

**核心逻辑**：
```cpp
map<char, int> last; // 记录字符最后出现的位置
while (stk.size() && stk.back() < s[i] && last[stk.back()] > i) {
    ins[stk.back()] = false;
    stk.pop_back();
}
stk += s[i];
```

#### 3. 题解作者：Helloworldwuyuze（★★★★☆）
**独特技巧**：
- 使用双端队列便于正向输出
- 数组下标直接映射字符ASCII码
- 精简的条件判断逻辑

**核心实现**：
```cpp
deque<char> q;
while (q.size() && cnt[q.front()] > 1 && s[i] >= q.front()) {
    flag[q.front()] = -1;
    q.pop_front();
}
q.push_front(s[i]);
```

---

### 关键思路总结
1. **贪心策略**：从前往后扫描，确保每个位置选择可能的最大字符
2. **单调栈维护**：栈中保持字典序递减，弹出条件需同时满足：
   - 栈顶字符后续仍会出现（`cnt[top] > 0` 或 `last[top] > i`）
   - 当前字符比栈顶大
3. **状态记录**：
   - `cnt[]` 动态记录字符剩余可用次数
   - `instk[]` 标记字符是否已入栈

**调试技巧**：
- 多测试用例务必清空全局数组
- 栈的输出顺序需反向（使用双端队列可优化）
- ASCII码与字母转换注意±'a'的细节

---

### 相似题目推荐
1. [P2870 [USACO07DEC]Best Cow Line G](https://www.luogu.com.cn/problem/P2870)（贪心+双指针）
2. [P1090 [NOIP2004 提高组] 合并果子](https://www.luogu.com.cn/problem/P1090)（贪心策略）
3. [P4059 [Code+#1]找爸爸](https://www.luogu.com.cn/problem/P4059)（动态规划与字典序结合）

---

### 个人心得摘录
> "WA了两次才意识到多测要清空instk数组，血的教训！" —— liangbowen  
> "发现用deque比stack更方便，因为最终要正向输出结果" —— EternalHeart1314  
> "贪心策略的证明是关键，必须确保局部最优能推导全局最优" —— SpeedStar

总结：此类问题的核心在于贪心策略的正确性证明，以及实现时对数据状态的精准维护。调试时需特别注意边界条件和全局变量的清空。

---
处理用时：49.69秒