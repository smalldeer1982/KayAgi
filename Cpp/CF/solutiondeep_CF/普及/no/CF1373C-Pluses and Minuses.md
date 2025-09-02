# 题目信息

# Pluses and Minuses

## 题目描述

You are given a string $ s $ consisting only of characters + and -. You perform some process with this string. This process can be described by the following pseudocode:

 ```
res = 0
for init = 0 to inf
    cur = init
    ok = true
    for i = 1 to |s|
        res = res + 1
        if s[i] == '+'
            cur = cur + 1
        else
            cur = cur - 1
        if cur < 0
            ok = false
            break
    if ok
        break
```


Note that the $ inf $ denotes infinity, and the characters of the string are numbered from $ 1 $ to $ |s| $ .

You have to calculate the value of the $ res $ after the process ends.

## 样例 #1

### 输入

```
3
--+-
---
++--+-```

### 输出

```
7
9
6```

# AI分析结果

### 题目内容重写（中文）

#### 题目描述

给定一个仅由字符 `+` 和 `-` 组成的字符串 $s$。你需要执行一个过程，该过程可以用以下伪代码描述：

```
res = 0
for init = 0 to inf
    cur = init
    ok = true
    for i = 1 to |s|
        res = res + 1
        if s[i] == '+'
            cur = cur + 1
        else
            cur = cur - 1
        if cur < 0
            ok = false
            break
    if ok
        break
```

注意，$inf$ 表示无穷大，字符串的字符编号从 $1$ 到 $|s|$。

你需要计算过程结束后 $res$ 的值。

#### 样例 #1

##### 输入

```
3
--+-
---
++--+-```

##### 输出

```
7
9
6```

### 算法分类
前缀和、模拟

### 题解分析与结论

本题的核心在于理解伪代码的执行逻辑，并优化其时间复杂度。伪代码的外层循环从 `init = 0` 开始，逐步增加 `init`，直到在遍历字符串时 `cur` 不再小于 0。直接模拟该过程会导致超时，因此需要通过分析前缀和来优化。

各题解的优化思路主要集中在通过前缀和来记录 `cur` 的变化，并利用这些信息快速计算 `res` 的值。以下是各题解的对比：

1. **Lyz09** 的题解通过记录 `l` 和 `g` 来模拟 `cur` 的变化，并在 `l == g` 时更新 `res`。该解法思路清晰，代码简洁，时间复杂度为 $O(n)$。
2. **Keith_2006** 的题解通过前缀和数组 `s` 和 `first` 数组来记录第一次出现负值的位置，并在这些位置更新 `res`。该解法同样具有较好的时间复杂度，但代码略显复杂。
3. **_jimmywang_** 的题解通过前缀和数组 `c` 来记录 `cur` 的变化，并在 `c[i] > mx` 时更新 `res`。该解法思路清晰，代码简洁，时间复杂度为 $O(n)$。
4. **cyh_toby** 的题解通过 `sum` 和 `cur` 来模拟 `cur` 的变化，并在 `sum + cur < 0` 时更新 `res`。该解法思路清晰，代码简洁，时间复杂度为 $O(n)$。
5. **b6e0_** 的题解通过 `sum` 和 `fi` 来模拟 `cur` 的变化，并在 `sum == fi` 时更新 `res`。该解法思路清晰，代码简洁，时间复杂度为 $O(n)$。

### 评分较高的题解

1. **Lyz09** (4星)
   - **关键亮点**：通过 `l` 和 `g` 来模拟 `cur` 的变化，代码简洁，思路清晰。
   - **核心代码**：
     ```cpp
     for(int i=0;i<len;i++) {
         if(s[i]=='-') l--;
         else l++;
         if(l==g) {
             g--;
             ans+=i+1;
         }
     }
     ```

2. **_jimmywang_** (4星)
   - **关键亮点**：通过前缀和数组 `c` 来记录 `cur` 的变化，并在 `c[i] > mx` 时更新 `res`，代码简洁。
   - **核心代码**：
     ```cpp
     f(i,0,s.size()-1) {
         if(s[i]=='-') c[i]=c[i-1]-1;
         else c[i]=c[i-1]+1;
     }
     f(i,0,s.size()-1) c[i]=max((ll)0,-c[i]);
     ll mx=0;
     f(i,0,s.size()-1) if(c[i]>mx) ans+=i+1, mx=c[i];
     ```

3. **cyh_toby** (4星)
   - **关键亮点**：通过 `sum` 和 `cur` 来模拟 `cur` 的变化，并在 `sum + cur < 0` 时更新 `res`，代码简洁。
   - **核心代码**：
     ```cpp
     for (int i = 1; i <= n; i++) {
         if (s[i] == '+') sum++;
         else sum--;
         if (sum + cur < 0) {
             ans += i;
             cur++;
         }
     }
     ```

### 最优关键思路或技巧

- **前缀和的应用**：通过前缀和来记录 `cur` 的变化，避免重复计算，从而优化时间复杂度。
- **模拟优化**：通过记录关键点（如 `l == g` 或 `sum + cur < 0`）来快速更新 `res`，避免直接模拟带来的高时间复杂度。

### 可拓展之处

- **类似题目**：可以拓展到其他需要模拟过程但时间复杂度较高的题目，通过分析过程的关键点来优化。
- **前缀和的应用**：前缀和在许多算法题中都有广泛应用，如子数组和问题、滑动窗口等。

### 推荐题目
1. [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)
2. [P1631 序列合并](https://www.luogu.com.cn/problem/P1631)
3. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)

---
处理用时：37.83秒