# 题目信息

# Minimal string

## 题目描述

Petya recieved a gift of a string $ s $ with length up to $ 10^{5} $ characters for his birthday. He took two more empty strings $ t $ and $ u $ and decided to play a game. This game has two possible moves:

- Extract the first character of $ s $ and append $ t $ with this character.
- Extract the last character of $ t $ and append $ u $ with this character.

Petya wants to get strings $ s $ and $ t $ empty and string $ u $ lexicographically minimal.

You should write a program that will help Petya win the game.

## 样例 #1

### 输入

```
cab
```

### 输出

```
abc
```

## 样例 #2

### 输入

```
acdb
```

### 输出

```
abdc
```

# AI分析结果



# Minimal string

## 题目描述

Petya 收到一个长度不超过 $10^5$ 的字符串 $s$ 作为生日礼物。他拿着两个空字符串 $t$ 和 $u$ 玩游戏，游戏有两种操作：

1. 取出 $s$ 的第一个字符并追加到 $t$ 的末尾。
2. 取出 $t$ 的最后一个字符并追加到 $u$ 的末尾。

Petya 希望最终 $s$ 和 $t$ 都为空，且 $u$ 的字典序尽可能小。请编写程序帮助他完成游戏。

## 样例 #1

### 输入

```
cab
```

### 输出

```
abc
```

## 样例 #2

### 输入

```
acdb
```

### 输出

```
abdc
```

---

**算法分类**：贪心、栈

---

### 题解综合分析

本题需要构造字典序最小的出栈序列，核心思路是预处理后缀最小值数组，利用贪心策略判断何时弹出栈顶元素。所有题解均采用以下步骤：
1. **预处理后缀最小值数组**：从后向前遍历字符串，记录每个位置到末尾的最小字符。
2. **栈模拟操作**：逐个压入字符，若栈顶元素≤后续字符的最小值，则持续弹出。
3. **处理剩余元素**：遍历结束后将栈中剩余字符弹出。

---

### 高分题解推荐

#### 题解作者：Xdl_rp（评分：5星）
**关键亮点**：
- 清晰的预处理逻辑，单独处理最后一个字符避免越界。
- 代码结构简洁，索引处理严谨。
```cpp
char p[100005]; // 预处理后缀最小值数组
int main() {
    string s;
    cin >> s;
    int n = s.size();
    p[n-1] = s[n-1];
    for (int i = n-2; i >= 0; i--)
        p[i] = min(p[i+1], s[i]);
    stack<char> stk;
    for (int i = 0; i < n-1; i++) {
        stk.push(s[i]);
        while (!stk.empty() && stk.top() <= p[i+1]) {
            cout << stk.top();
            stk.pop();
        }
    }
    stk.push(s[n-1]); // 单独处理最后一个字符
    while (!stk.empty()) {
        cout << stk.top();
        stk.pop();
    }
}
```

#### 题解作者：Dws_t7760（评分：4星）
**关键亮点**：
- 预处理数组末尾设置哨兵值 127，简化边界判断。
- 循环结束后统一处理栈中剩余元素，逻辑紧凑。
```cpp
char minn[114514]; // 预处理数组含哨兵
int main() {
    string t;
    cin >> t;
    int n = t.length();
    minn[n] = 127; // 哨兵值
    for (int i = n-1; i >= 0; i--)
        minn[i] = min(t[i], minn[i+1]);
    stack<char> st;
    for (int i = 0; i < n; i++) {
        st.push(t[i]);
        while (st.size() && st.top() <= minn[i+1]) {
            cout << st.top();
            st.pop();
        }
    }
    // 隐含处理剩余元素的循环
}
```

#### 题解作者：sunyizhe（评分：4星）
**个人心得**：
- 强调贪心策略中必须包含等号判断，否则会导致错误。
- 通过错误案例模拟验证策略正确性，深入解释算法原理。
```cpp
while (!s.empty() && s.top() <= Min[i+1]) { // 必须包含等于判断
    cout << s.top();
    s.pop();
}
```

---

### 最优思路总结
1. **后缀最小值预处理**：倒序遍历字符串，计算每个位置的最小字符。
2. **贪心弹出条件**：栈顶元素≤后续未处理的最小值时立即弹出。
3. **栈操作模拟**：压入字符后循环检查弹出条件，最后清空栈。

---

### 拓展应用
- **类似题目**：构造最小字典序序列的题目常结合贪心和栈，例如：
  1. [P1106 删数问题](https://www.luogu.com.cn/problem/P1106)
  2. [P2870 最佳牛线](https://www.luogu.com.cn/problem/P2870)
  3. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)（优先队列优化）

---

### 核心代码实现
预处理后缀最小值后，主循环逻辑：
```cpp
for (int i = 0; i < n; i++) {
    st.push(s[i]);
    while (!st.empty() && st.top() <= minn[i+1]) {
        cout << st.top();
        st.pop();
    }
}
while (!st.empty()) { // 处理剩余元素
    cout << st.top();
    st.pop();
}
```

---
处理用时：93.55秒