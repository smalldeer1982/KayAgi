# 题目信息

# エターナルスタティックファイナル

## 题目描述

## 题意
小A通过组合他所学的短语来吟唱咒语。

同一个短语可以在诵读咒语的过程中使用多次。

例如，如果你记住了 $aaa$、$bbb$ 和 $ccc$ 三个短语，你就可以念出 $aaaccc$、$aaabbb$ 和 $cccaaaaaa$ 这样的咒语。

小A不确定他是否能够通过组合他所记住的短语来吟唱他所要学习的新咒语。

为小A创建一个程序，计算有多少种短语的排列组合可以构建他所要学习的新咒语。

变化的数量可能很大，所以输出对 $10^9+7$ 取模后的结果。

## 样例 #1

### 输入

```
3

eternalstaticfinal

eternal

static

final```

### 输出

```
1```

## 样例 #2

### 输入

```
5

eternalstaticfinal

eternal

static

final

fin

al```

### 输出

```
2```

## 样例 #3

### 输入

```
5

abcdef

abc

def

abcdef

d

ef```

### 输出

```
3```

## 样例 #4

### 输入

```
5

aaaa

a

aa

aaa

aaaa

b```

### 输出

```
8```

## 样例 #5

### 输入

```
10

aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa

a

aa

aaa

aaaa

aaaaa

aaaaaa

aaaaaaa

aaaaaaaa

aaaaaaaaa

aaaaaaaaaa```

### 输出

```
146491918```

# AI分析结果



# エターナルスタティックファイナル

## 题目描述

### 题意
小A通过组合他所学的短语来吟唱咒语。同一个短语可以在诵读咒语的过程中使用多次。例如，若记住 $aaa$、$bbb$、$ccc$ 三个短语，可以念出 $aaaccc$、$aaabbb$ 等咒语。给定新咒语和短语列表，计算有多少种短语排列组合能构建新咒语，结果对 $10^9+7$ 取模。

---

## 分类
动态规划

---

## 题解分析与结论

### 核心思路
所有题解均采用动态规划思路：
1. **状态定义**：`dp[i]` 表示构造主串前 `i` 个字符的方案数
2. **状态转移**：遍历每个短语 `t`，若 `t` 能匹配主串末尾，则 `dp[i] += dp[i-len(t)]`
3. **边界条件**：`dp[0] = 1`（空串方案数为1）

### 解决难点
- **子串匹配判断**：通过 `substr` 或逐字符比较判断短语是否匹配
- **多短语叠加**：每个位置需累加所有可能短语的贡献
- **边界处理**：需确保 `i >= len(t)` 时才进行转移

---

## 优质题解推荐

### 题解1：CheZiHe929（4星）
**亮点**：
- 代码结构清晰，变量命名规范
- 使用 `substr` 直观处理子串匹配
- 完整处理取模运算和边界条件

**核心代码**：
```cpp
int dp[1005] = {0};
dp[0] = 1;
for(int i=1; i<=s.size(); i++) 
    for(int j=1; j<=n; j++) {
        int len = t[j].size();
        if(i >= len && t[j] == s.substr(i-len, len)) {
            dp[i] = (dp[i] + dp[i-len]) % MOD;
        }
    }
```

### 题解2：Specthraimn（4星）
**亮点**：
- 代码简洁，适合快速理解核心逻辑
- 使用标准库函数处理字符串操作
- 注释明确，突出状态转移逻辑

**核心代码**：
```cpp
vector<string> phrases(n);
dp[0] = 1;
for(int i=1; i<=s.size(); i++) {
    for(auto& t : phrases) {
        if(i >= t.size() && s.substr(i-t.size(), t.size()) == t) {
            dp[i] = (dp[i] + dp[i - t.size()]) % MOD;
        }
    }
}
```

### 题解3：HotWood（3星）
**亮点**：
- 引入字符串哈希优化匹配效率
- 预处理主串哈希值加速比较
- 自然溢出法实现快速哈希计算

**核心优化点**：
```cpp
// 预处理主串哈希前缀和
hash[i] = hash[i-1] * BASE + s[i];
// 计算子串哈希值
ULL sub_hash = hash[r] - hash[l-1] * pow(BASE, r-l+1);
```

---

## 举一反三
1. **相似题目推荐**：
   - [P1255 数楼梯](https://www.luogu.com.cn/problem/P1255)（斐波那契数列的DP思想）
   - [P4591 字符串划分](https://www.luogu.com.cn/problem/P4591)（多模式串匹配的动态规划）
   - [P1435 回文字串](https://www.luogu.com.cn/problem/P1435)（字符串操作的动态规划）

2. **优化技巧**：
   - **哈希预处理**：适用于长字符串多次匹配场景
   - **字典树优化**：当短语数量极大时，可用字典树加速匹配
   - **滚动数组**：空间优化，适用于超长主串场景

3. **调试心得**：
   - 子串截取位置需仔细验证（例如 `substr(start, len)` 的参数含义）
   - 取模运算需在每次累加后立即执行，防止溢出
   - 空串边界条件易遗漏，需特别注意 `dp[0]` 的初始化

---
处理用时：62.90秒