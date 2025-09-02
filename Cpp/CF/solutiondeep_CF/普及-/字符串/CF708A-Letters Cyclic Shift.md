# 题目信息

# Letters Cyclic Shift

## 题目描述

You are given a non-empty string $ s $ consisting of lowercase English letters. You have to pick exactly one non-empty substring of $ s $ and shift all its letters 'z' ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF708A/355fee5161a1808ee95ea5dc6d815d4071657131.png) 'y' ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF708A/355fee5161a1808ee95ea5dc6d815d4071657131.png) 'x' ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF708A/23d27bb9cf2cd76a0555d2babeb08bc9315530bc.png) 'b' ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF708A/355fee5161a1808ee95ea5dc6d815d4071657131.png) 'a' ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF708A/355fee5161a1808ee95ea5dc6d815d4071657131.png) 'z'. In other words, each character is replaced with the previous character of English alphabet and 'a' is replaced with 'z'.

What is the lexicographically minimum string that can be obtained from $ s $ by performing this shift exactly once?

## 说明/提示

String $ s $ is lexicographically smaller than some other string $ t $ of the same length if there exists some $ 1<=i<=|s| $ , such that $ s_{1}=t_{1},s_{2}=t_{2},...,s_{i-1}=t_{i-1} $ , and $ s_{i}&lt;t_{i} $ .

## 样例 #1

### 输入

```
codeforces
```

### 输出

```
bncdenqbdr
```

## 样例 #2

### 输入

```
abacaba
```

### 输出

```
aaacaba
```

# AI分析结果

### 题目内容重写（中文）

#### 题目描述

给定一个由小写英文字母组成的非空字符串 $s$。你需要选择 $s$ 中的一个非空子串，并将该子串中的每个字母进行循环移位：'z' 变为 'y'，'y' 变为 'x'，……，'b' 变为 'a'，'a' 变为 'z'。换句话说，每个字符被替换为英文字母表中的前一个字符，'a' 被替换为 'z'。

问：通过执行一次这样的移位操作，可以得到字典序最小的字符串是什么？

#### 说明/提示

字符串 $s$ 的字典序小于另一个相同长度的字符串 $t$，当且仅当存在某个 $1<=i<=|s|$，使得 $s_{1}=t_{1},s_{2}=t_{2},...,s_{i-1}=t_{i-1}$，且 $s_{i}&lt;t_{i}$。

#### 样例 #1

##### 输入

```
codeforces
```

##### 输出

```
bncdenqbdr
```

#### 样例 #2

##### 输入

```
abacaba
```

##### 输出

```
aaacaba
```

---

### 题解综合分析与结论

#### 思路总结

1. **字典序最小化**：为了得到字典序最小的字符串，应尽量从字符串的最左侧开始进行字符的循环移位操作，因为左侧字符对字典序的影响更大。
2. **避免改变 'a'**：由于 'a' 变为 'z' 会增加字典序，因此应尽量避免改变 'a'，除非整个字符串都是 'a'。
3. **特殊情况处理**：如果整个字符串都是 'a'，则必须改变一个字符，通常选择最后一个 'a' 变为 'z'，以最小化字典序的影响。

#### 难点对比

- **确定移位范围**：难点在于如何确定需要移位的子串范围。大多数题解通过遍历字符串，找到第一个非 'a' 的字符开始移位，直到遇到下一个 'a' 或字符串结束。
- **特殊情况处理**：处理全 'a' 字符串的情况是另一个难点，需要确保至少有一个字符被移位。

#### 最优关键思路

- **从第一个非 'a' 字符开始移位**：这是所有题解的共同思路，确保字典序最小化。
- **提前终止移位**：当遇到 'a' 时，立即停止移位，避免不必要的字典序增加。
- **全 'a' 字符串的特殊处理**：将最后一个 'a' 变为 'z'，确保字典序最小。

#### 代码实现技巧

- **使用标志变量**：通过标志变量（如 `flag`）来记录是否已经开始移位，确保只移位一次。
- **提前返回**：在遇到 'a' 时，如果已经开始移位，则立即输出结果，避免继续遍历。

---

### 评分较高的题解

#### 题解1：作者 q779 (评分：4星)

**关键亮点**：
- 清晰地从第一个非 'a' 字符开始移位，直到遇到下一个 'a'。
- 处理了全 'a' 字符串的特殊情况，将最后一个 'a' 变为 'z'。

**核心代码**：
```cpp
for(R int i=0; i<s.size(); i++)
    if(s[i]^97) { // s[i] != 'a'
        s[i]--; flag=1;
    }
    else if(flag) return cout<<s,0;
if(!flag) s[s.size()-1]='z'; // 特判
cout<<s;
```

#### 题解2：作者 Yi_Fan (评分：4星)

**关键亮点**：
- 通过标志变量 `a` 来控制移位范围，确保只移位一次。
- 处理了全 'a' 字符串的特殊情况。

**核心代码**：
```cpp
for(int i = 0 ; i < s.length(); i ++){
    if(s[i] != 'a'){
        if(a == false) a = true;
        s[i]--;
    }
    else if(s[i] == 'a' && a == true) break;
}
if(a == false) s[s.length()-1]='z';
cout<<s;
```

#### 题解3：作者 Sternenlicht (评分：4星)

**关键亮点**：
- 使用 `flag` 变量控制移位，确保只移位一次。
- 处理了全 'a' 字符串的特殊情况。

**核心代码**：
```cpp
for (int i=0;i<s.size();i++)
    if (s[i]!='a') s[i]--,flag=1;
    else if (flag) return cout<<s<<endl,0;
if (!flag) s[s.size()-1]='z';
cout<<s<<endl;
```

---

### 推荐题目

1. **P1003 铺地毯**：考察字符串处理与模拟操作。
2. **P1042 乒乓球**：涉及字符串的遍历与条件判断。
3. **P1055 ISBN号码**：字符串处理与校验码计算。

---

### 个人心得摘录

- **调试经历**：在处理全 'a' 字符串时，容易忽略必须改变一个字符的要求，导致程序错误。
- **顿悟感想**：从第一个非 'a' 字符开始移位，可以确保字典序最小化，这一思路在类似问题中具有通用性。

---
处理用时：35.70秒