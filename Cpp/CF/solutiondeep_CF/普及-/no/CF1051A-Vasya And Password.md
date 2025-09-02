# 题目信息

# Vasya And Password

## 题目描述

Vasya came up with a password to register for EatForces — a string $ s $ . The password in EatForces should be a string, consisting of lowercase and uppercase Latin letters and digits.

But since EatForces takes care of the security of its users, user passwords must contain at least one digit, at least one uppercase Latin letter and at least one lowercase Latin letter. For example, the passwords "abaCABA12", "Z7q" and "3R24m" are valid, and the passwords "qwerty", "qwerty12345" and "Password" are not.

A substring of string $ s $ is a string $ x = s_l s_{l + 1} \dots s_{l + len - 1} (1 \le l \le |s|, 0 \le len \le |s| - l + 1) $ . $ len $ is the length of the substring. Note that the empty string is also considered a substring of $ s $ , it has the length $ 0 $ .

Vasya's password, however, may come too weak for the security settings of EatForces. He likes his password, so he wants to replace some its substring with another string of the same length in order to satisfy the above conditions. This operation should be performed exactly once, and the chosen string should have the minimal possible length.

Note that the length of $ s $ should not change after the replacement of the substring, and the string itself should contain only lowercase and uppercase Latin letters and digits.

## 说明/提示

In the first example Vasya's password lacks a digit, he replaces substring "C" with "4" and gets password "abcD4E". That means, he changed the substring of length 1.

In the second example Vasya's password is ok from the beginning, and nothing has to be changed. That is the same as replacing the empty substring with another empty substring (length 0).

## 样例 #1

### 输入

```
2
abcDCE
htQw27
```

### 输出

```
abcD4E
htQw27
```

# AI分析结果



### 题目重写
#### Vasya And Password

**题目描述**

Vasya 想出了一个密码用于注册 EatForces，该密码是一个由大小写拉丁字母和数字组成的字符串 $s$。EatForces 要求用户密码必须至少包含一个数字、一个大写字母和一个小写字母。例如，"abaCABA12"、"Z7q" 和 "3R24m" 是有效密码，而 "qwerty"、"qwerty12345" 和 "Password" 则无效。

Vasya 的密码可能不满足条件。他希望通过**恰好替换一个子串**（即选择一个连续区间替换为等长的字符串）来使密码符合要求。请找出替换子串长度最小的方案。

**输入格式**
- 第一行输入测试用例数 $t$
- 接下来 $t$ 行，每行一个字符串 $s$

**输出格式**
- 对每个测试用例，输出修改后的字符串

**样例 #1**
输入：
```
2
abcDCE
htQw27
```
输出：
```
abcD4E
htQw27
```

**说明**
- 第一个样例替换长度为 1 的子串 "C" 为 "4"，使密码包含数字
- 第二个样例本身符合条件，无需修改（相当于替换空子串）

---

### 算法分类
**贪心**

---

### 题解分析与结论

#### 思路对比与核心要点
所有题解均采用**统计字符类型+贪心替换**的核心思路：
1. **统计缺失类型**：遍历字符串，记录数字、小写字母、大写字母的出现次数
2. **替换策略**：
   - **缺 1 种类型**：在出现次数≥2 的类型中选择一个字符替换为缺失类型
   - **缺 2 种类型**（原字符串仅含一种类型）：必须替换两个字符为其他两种类型
3. **实现技巧**：
   - 记录字符最后两次出现位置，避免替换后破坏其他类型条件
   - 优先选择出现次数多的类型进行替换，保证替换后仍有剩余

#### 最优思路总结
**关键步骤**：
1. 统计三种字符类型的存在情况，确定缺失类型
2. 根据缺失数量选择替换策略：
   - 缺 1 类：找到出现次数≥2 的字符类型进行替换
   - 缺 2 类：直接修改前两个字符（因原字符串仅含一种类型）
3. 通过记录字符位置确保替换后剩余数量≥1

**代码实现技巧**：
- 用变量存储最后两次出现位置，便于快速定位可替换字符
- 分类讨论时优先处理出现次数多的类型，减少条件判断

---

### 推荐题解

#### 题解作者：xhhhh36（4.5星）
**亮点**：
1. 记录字符最后两次出现位置，保证替换后仍有剩余
2. 完整处理三种缺失情况，逻辑清晰
3. 代码结构紧凑，利用变量复用减少冗余判断

**核心代码**：
```cpp
int a=0, b=0, c=0, a1, a2, b1, b2, c1, c2;
// 统计字符出现次数及最后两个位置
for(int i=0; s[i]; i++){
    if(isdigit(s[i])) a++, a2=a1, a1=i;
    else if(islower(s[i])) b++, b2=b1, b1=i;
    else c++, c2=c1, c1=i;
}
// 处理缺数字的情况
if(a == 0){
    if(b >= 2) s[b1] = '0', b--; 
    else s[c1] = '0', c--;
}
```

#### 题解作者：KobeBeanBryantCox（4星）
**亮点**：
1. 分三次独立处理缺失类型，避免逻辑嵌套
2. 使用循环查找可替换位置，代码可读性强
3. 动态更新字符计数，确保后续处理正确

**核心代码**：
```cpp
if(!cnt1){ // 缺数字
    for(int i=0; i<s.size(); i++){
        if(islower(s[i]) && cnt2 >=2){
            s[i] = '0'; break;
        } else if(isupper(s[i]) && cnt3 >=2){
            s[i] = '0'; break;
        }
    }
}
```

---

### 相似题目推荐
1. [CF12B Correct Solution?](https://www.luogu.com.cn/problem/CF12B) - 贪心构造最小数
2. [P1781 宇宙总统](https://www.luogu.com.cn/problem/P1781) - 字符串比较与贪心
3. [CF999A Mishka and Contest](https://www.luogu.com.cn/problem/CF999A) - 贪心策略选择操作顺序

---
处理用时：65.81秒