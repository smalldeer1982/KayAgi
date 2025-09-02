# 题目信息

# Beautiful IP Addresses

## 题目描述

The problem uses a simplified TCP/IP address model, please read the statement carefully.

An IP address is a 32-bit integer, represented as a group of four decimal 8-bit integers (without leading zeroes), separated by commas. For example, record 0.255.1.123 shows a correct IP address and records 0.256.1.123 and 0.255.1.01 do not. In the given problem an arbitrary group of four 8-bit integers is a correct IP address.

Our hero Polycarpus still works as a system administrator in some large corporation. He likes beautiful IP addresses. To check if some IP address is beautiful, he should do the following:

1. write out in a line four 8-bit numbers of the IP address, without the commas;
2. check if the resulting string is a palindrome.

Let us remind you that a palindrome is a string that reads the same from right to left and from left to right.

For example, IP addresses 12.102.20.121 and 0.3.14.130 are beautiful (as strings "1210220121" and "0314130" are palindromes), and IP addresses 1.20.20.1 and 100.4.4.1 are not.

Polycarpus wants to find all beautiful IP addresses that have the given set of digits. Each digit from the set must occur in the IP address at least once. IP address must not contain any other digits. Help him to cope with this difficult task.

## 样例 #1

### 输入

```
6
0 1 2 9 8 7
```

### 输出

```
6
78.190.209.187
79.180.208.197
87.190.209.178
89.170.207.198
97.180.208.179
98.170.207.189
```

## 样例 #2

### 输入

```
1
4
```

### 输出

```
16
4.4.4.4
4.4.4.44
4.4.44.4
4.4.44.44
4.44.4.4
4.44.4.44
4.44.44.4
4.44.44.44
44.4.4.4
44.4.4.44
44.4.44.4
44.4.44.44
44.44.4.4
44.44.4.44
44.44.44.4
44.44.44.44
```

# AI分析结果

### 题目内容重写（中文）

#### 美丽的IP地址

##### 题目描述

本题使用了一个简化的TCP/IP地址模型，请仔细阅读题目描述。

一个IP地址是一个32位的整数，通常表示为四个用逗号分隔的十进制8位整数（没有前导零）。例如，记录`0.255.1.123`表示一个正确的IP地址，而记录`0.256.1.123`和`0.255.1.01`则不正确。在本题中，任意四个8位整数组成的IP地址都是合法的。

我们的主角Polycarpus仍然在一家大公司担任系统管理员。他喜欢美丽的IP地址。要检查某个IP地址是否美丽，他需要做以下操作：

1. 将IP地址中的四个8位数字写在一行中，去掉逗号；
2. 检查生成的字符串是否是回文。

回文是指从左到右和从右到左读都相同的字符串。

例如，IP地址`12.102.20.121`和`0.3.14.130`是美丽的（因为字符串`"1210220121"`和`"0314130"`是回文），而IP地址`1.20.20.1`和`100.4.4.1`则不是。

Polycarpus想要找到所有美丽的IP地址，这些地址必须包含给定的数字集合。每个数字集合中的数字必须在IP地址中至少出现一次。IP地址不能包含任何其他数字。请帮助他完成这个困难的任务。

##### 样例 #1

###### 输入

```
6
0 1 2 9 8 7
```

###### 输出

```
6
78.190.209.187
79.180.208.197
87.190.209.178
89.170.207.198
97.180.208.179
98.170.207.189
```

##### 样例 #2

###### 输入

```
1
4
```

###### 输出

```
16
4.4.4.4
4.4.4.44
4.4.44.4
4.4.44.44
4.44.4.4
4.44.4.44
4.44.44.4
4.44.44.44
44.4.4.4
44.4.4.44
44.4.44.4
44.4.44.44
44.44.4.4
44.44.4.44
44.44.44.4
44.44.44.44
```

### 题解分析与结论

本题的核心是生成所有符合条件的回文IP地址，并且每个给定的数字必须至少出现一次。题解中主要采用了DFS（深度优先搜索）来枚举可能的回文串，并通过位运算来记录和检查数字的使用情况。此外，题解中还涉及到了IP地址的合法性检查，包括前导零和数值范围（0-255）的判断。

### 评分较高的题解

#### 题解1：作者：jdsb (赞：4)

**星级：4.5**

**关键亮点：**
- 使用DFS暴力枚举前一半的数字，利用回文性质生成后一半。
- 使用位运算记录数字的使用情况，确保所有给定数字都被使用。
- 通过合法性检查（前导零和数值范围）来筛选合法的IP地址。

**核心代码：**
```cpp
void dfs(int k, int maxk, string s, int use) {
    if(k == maxk) {
        if(use == flag) solve(s);
        return;
    }
    if(k * 2 > maxk - 1) {
        if(use != flag) return;
        dfs(k + 1, maxk, s + s[maxk - k - 1], use);
        return;
    }
    for(int i = 0; i <= 9; i++)
        if(flag & (1 << i))
            dfs(k + 1, maxk, s + char(i + '0'), use | (1 << i));
}
```

**个人心得：**
- 通过位运算来记录数字的使用情况，简化了代码逻辑。
- 在DFS中直接生成回文串的后半部分，减少了不必要的枚举。

#### 题解2：作者：HaneDaniko (赞：3)

**星级：4.0**

**关键亮点：**
- 通过枚举回文串的前半部分，利用回文性质生成后半部分。
- 使用vector存储合法答案，并在最后进行排序输出。
- 通过合法性检查确保生成的IP地址符合要求。

**核心代码：**
```cpp
void dfs(int len, int pla, int last) {
    if(pla == (len + 1) / 2) {
        if(cnt == n) ans += devide(len & 1);
        return;
    }
    for(int i = 1; i <= n; i++) {
        p.push_back(a[i]);
        if(!vis[i]) {
            vis[i] = 1; cnt++;
            dfs(len, pla + 1, i);
            vis[i] = 0; cnt--;
        }
        else {
            dfs(len, pla + 1, i);
        }
        p.pop_back();
    }
}
```

**个人心得：**
- 通过枚举回文串的前半部分，减少了搜索空间。
- 使用vector存储答案，方便后续排序和输出。

#### 题解3：作者：MC小萌新 (赞：3)

**星级：4.0**

**关键亮点：**
- 使用DFS枚举回文串的前半部分，并通过回文性质生成后半部分。
- 通过合法性检查确保生成的IP地址符合要求。
- 使用全局变量记录每一段地址的长度，简化了代码逻辑。

**核心代码：**
```cpp
void dfs(int l, int t) {
    if(t > (l + 1) / 2) {
        if(use != n) return;
        for(int i = 1; i < t; i++) ip[l + 1 - i] = ip[i];
        int cnt = 0;
        int x[10] = {0};
        for(int i = 1; i <= 4; i++) {
            for(int j = 0; j < s[i]; j++) {
                cnt++;
                if(ip[cnt] == 0 && s[i] > 1 && j == 0) return;
                x[i] = x[i] * 10 + ip[cnt];
            }
            if(x[i] > 255) return;
        }
        k++;
        for(int i = 1; i <= 4; i++) ans[k][i] = x[i];
        return;
    }
    for(int i = 1; i <= n; i++) {
        ip[t] = a[i];
        if(v[i]) dfs(l, t + 1);
        else {
            use++; v[i] = 1;
            dfs(l, t + 1);
            use--; v[i] = 0;
        }
    }
}
```

**个人心得：**
- 通过全局变量记录每一段地址的长度，简化了代码逻辑。
- 在DFS中直接生成回文串的后半部分，减少了不必要的枚举。

### 最优关键思路或技巧

1. **DFS + 回文性质**：通过DFS枚举回文串的前半部分，利用回文性质生成后半部分，减少了搜索空间。
2. **位运算记录数字使用情况**：使用位运算记录数字的使用情况，确保所有给定数字都被使用，简化了代码逻辑。
3. **合法性检查**：通过合法性检查（前导零和数值范围）来筛选合法的IP地址，确保生成的IP地址符合要求。

### 可拓展之处

- **类似题目**：可以扩展到其他需要生成回文串或特定格式的字符串的题目，如生成回文电话号码、回文日期等。
- **优化思路**：可以考虑使用剪枝策略进一步优化DFS，减少不必要的枚举。

### 推荐题目

1. **P1020 导弹拦截**（题号：P1020）：考察动态规划和搜索算法。
2. **P1040 加分二叉树**（题号：P1040）：考察树形DP和搜索算法。
3. **P1059 明明的随机数**（题号：P1059）：考察排序和去重算法。

### 个人心得总结

- **调试经历**：在DFS中生成回文串的后半部分时，需要注意边界条件的处理，避免生成不合法的回文串。
- **踩坑教训**：在合法性检查中，前导零的判断容易被忽略，需要特别注意。
- **顿悟感想**：通过位运算记录数字的使用情况，不仅简化了代码逻辑，还提高了代码的可读性和执行效率。

---
处理用时：65.53秒