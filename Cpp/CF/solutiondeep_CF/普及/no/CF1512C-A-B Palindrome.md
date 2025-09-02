# 题目信息

# A-B Palindrome

## 题目描述

You are given a string $ s $ consisting of the characters '0', '1', and '?'. You need to replace all the characters with '?' in the string $ s $ by '0' or '1' so that the string becomes a palindrome and has exactly $ a $ characters '0' and exactly $ b $ characters '1'. Note that each of the characters '?' is replaced independently from the others.

A string $ t $ of length $ n $ is called a palindrome if the equality $ t[i] = t[n-i+1] $ is true for all $ i $ ( $ 1 \le i \le n $ ).

For example, if $ s= $ "01?????0", $ a=4 $ and $ b=4 $ , then you can replace the characters '?' in the following ways:

- "01011010";
- "01100110".

For the given string $ s $ and the numbers $ a $ and $ b $ , replace all the characters with '?' in the string $ s $ by '0' or '1' so that the string becomes a palindrome and has exactly $ a $ characters '0' and exactly $ b $ characters '1'.

## 样例 #1

### 输入

```
9
4 4
01?????0
3 3
??????
1 0
?
2 2
0101
2 2
01?0
0 1
0
0 3
1?1
2 2
?00?
4 3
??010?0```

### 输出

```
01011010
-1
0
-1
0110
-1
111
1001
0101010```

# AI分析结果

### 题目内容重写

**A-B 回文串**

#### 题目描述

给定一个由字符 '0'、'1' 和 '?' 组成的字符串 $s$。你需要将字符串中的所有 '?' 替换为 '0' 或 '1'，使得最终的字符串是一个回文串，并且恰好包含 $a$ 个 '0' 和 $b$ 个 '1'。注意，每个 '?' 的替换是独立的。

一个长度为 $n$ 的字符串 $t$ 被称为回文串，当且仅当对于所有的 $i$（$1 \le i \le n$），$t[i] = t[n-i+1]$ 成立。

例如，若 $s= \text{"01?????0"}$，$a=4$ 且 $b=4$，则你可以将 '?' 替换为以下方式之一：

- "01011010";
- "01100110".

对于给定的字符串 $s$ 和数字 $a$、$b$，请将所有的 '?' 替换为 '0' 或 '1'，使得字符串成为回文串，并且恰好包含 $a$ 个 '0' 和 $b$ 个 '1'。

#### 样例 #1

##### 输入

```
9
4 4
01?????0
3 3
??????
1 0
?
2 2
0101
2 2
01?0
0 1
0
0 3
1?1
2 2
?00?
4 3
??010?0
```

##### 输出

```
01011010
-1
0
-1
0110
-1
111
1001
0101010
```

### 算法分类
**构造**

### 题解分析与结论

这道题的核心是通过构造回文串，并且满足 '0' 和 '1' 的个数限制。题解的主要思路是先通过回文性质确定部分 '?' 的取值，然后根据剩余的 '0' 和 '1' 的数量进行填充。难点在于处理字符串长度为奇数时的中间字符，以及确保最终的 '0' 和 '1' 的数量符合要求。

### 精选题解

#### 题解1：作者：xh001 (赞：4)

**星级：4.5**

**关键亮点：**
1. 通过回文性质确定部分 '?' 的取值，减少后续处理的复杂度。
2. 特判字符串长度为奇数时中间字符的处理，确保回文性质。
3. 从两端开始枚举，优先使用 '0'，确保 '0' 和 '1' 的数量符合要求。

**代码核心思想：**
```cpp
for(ll i=0;i<len;i++) {
    if((s[len-i-1]=='0' || s[len-i-1]=='1') && s[i]=='?') s[i]=s[len-i-1];
    if(s[i]!=s[len-i-1] && s[len-i-1]!='?') { f=1; break; }
    if(s[i]=='0') a--;
    else if(s[i]=='1') b--;
}
```

#### 题解2：作者：rui_er (赞：4)

**星级：4**

**关键亮点：**
1. 先根据对称性填充已知字符，减少后续处理的复杂度。
2. 枚举不能确定的位置，优先使用 '0'，确保 '0' 和 '1' 的数量符合要求。
3. 特判字符串长度为奇数时中间字符的处理，确保回文性质。

**代码核心思想：**
```cpp
rep(i, 1, k) if(s[i] == '?') {
    if(n > 1) s[i] = s[k+1-i] = '0', n -= 2;
    else s[i] = s[k+1-i] = '1', m -= 2;
}
```

#### 题解3：作者：StayAlone (赞：2)

**星级：3.5**

**关键亮点：**
1. 先判断当前字符串是否合法，减少后续处理的复杂度。
2. 通过回文性质确定部分 '?' 的取值，减少后续处理的复杂度。
3. 枚举不能确定的位置，优先使用 '0'，确保 '0' 和 '1' 的数量符合要求。

**代码核心思想：**
```cpp
for (int i = 0; i < l / 2; ++i) {
    if (s[i] != '?' && s[l-i-1] == '?') s[l-i-1] = s[i];
    else if (s[i] == '?' && s[l-i-1] != '?') s[i] = s[l-i-1];
}
```

### 最优关键思路或技巧
1. **回文性质的应用**：通过回文性质确定部分 '?' 的取值，减少后续处理的复杂度。
2. **优先使用 '0'**：在填充 '?' 时，优先使用 '0'，确保 '0' 和 '1' 的数量符合要求。
3. **特判奇数长度**：处理字符串长度为奇数时的中间字符，确保回文性质。

### 可拓展之处
1. **类似题目**：可以扩展到其他需要构造特定性质字符串的题目，如构造特定模式的字符串、构造特定长度的回文串等。
2. **算法优化**：可以进一步优化填充 '?' 的策略，减少时间复杂度。

### 推荐题目
1. [P1217 [USACO1.5]回文质数](https://www.luogu.com.cn/problem/P1217)
2. [P1435 [IOI2000]回文字串](https://www.luogu.com.cn/problem/P1435)
3. [P1739 [NOI1999]回文数](https://www.luogu.com.cn/problem/P1739)

---
处理用时：44.03秒