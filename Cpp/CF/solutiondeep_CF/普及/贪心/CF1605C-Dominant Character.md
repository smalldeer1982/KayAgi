# 题目信息

# Dominant Character

## 题目描述

Ashish has a string $ s $ of length $ n $ containing only characters 'a', 'b' and 'c'.

He wants to find the length of the smallest substring, which satisfies the following conditions:

- Length of the substring is at least $ 2 $
- 'a' occurs strictly more times in this substring than 'b'
- 'a' occurs strictly more times in this substring than 'c'

Ashish is busy planning his next Codeforces round. Help him solve the problem.

A string $ a $ is a substring of a string $ b $ if $ a $ can be obtained from $ b $ by deletion of several (possibly, zero or all) characters from the beginning and several (possibly, zero or all) characters from the end.

## 说明/提示

Consider the first test case. In the substring "aa", 'a' occurs twice, while 'b' and 'c' occur zero times. Since 'a' occurs strictly more times than 'b' and 'c', the substring "aa" satisfies the condition and the answer is $ 2 $ . The substring "a" also satisfies this condition, however its length is not at least $ 2 $ .

In the second test case, it can be shown that in none of the substrings of "cbabb" does 'a' occur strictly more times than 'b' and 'c' each.

In the third test case, "cacabccc", the length of the smallest substring that satisfies the conditions is $ 3 $ .

## 样例 #1

### 输入

```
3
2
aa
5
cbabb
8
cacabccc```

### 输出

```
2
-1
3```

# AI分析结果

### 题目内容重写
# 主导字符

## 题目描述

Ashish有一个长度为$n$的字符串$s$，其中只包含字符'a'、'b'和'c'。

他希望找到一个满足以下条件的最小子串的长度：

- 子串的长度至少为$2$
- 在该子串中，'a'的出现次数严格大于'b'
- 在该子串中，'a'的出现次数严格大于'c'

Ashish正忙于准备他的下一场Codeforces比赛，请你帮助他解决这个问题。

字符串$a$是字符串$b$的子串，如果$a$可以通过从$b$的开头和结尾删除若干个（可能为零或全部）字符得到。

## 说明/提示

考虑第一个测试用例。在子串"aa"中，'a'出现了两次，而'b'和'c'出现了零次。由于'a'的出现次数严格大于'b'和'c'，子串"aa"满足条件，答案为$2$。子串"a"也满足这个条件，但其长度不至少为$2$。

在第二个测试用例中，可以证明在字符串"cbabb"的所有子串中，没有子串满足'a'的出现次数严格大于'b'和'c'。

在第三个测试用例中，字符串"cacabccc"中满足条件的最小子串长度为$3$。

## 样例 #1

### 输入

```
3
2
aa
5
cbabb
8
cacabccc```

### 输出

```
2
-1
3```

### 题解分析与结论

这些题解大多采用了分类讨论的思路，通过枚举可能的子串模式来寻找满足条件的最短子串。常见的模式包括`aa`、`aba`、`aca`、`abca`、`acba`、`abbacca`和`accabba`。题解的主要难点在于如何高效地判断这些模式是否存在于字符串中，并找到最短的满足条件的子串。

### 评分较高的题解

#### 题解作者：zhaoyp (赞：9)
**星级：5星**
**关键亮点：**
- 详细分析了子串中两个'a'之间的距离，并基于此进行了分类讨论。
- 提供了严格的数学证明，解释了为什么某些情况下无法找到满足条件的子串。
- 代码简洁，逻辑清晰。

**核心代码：**
```cpp
if(s.find("aa")!=string::npos) cout<<2<<endl;
else if(s.find("aba")!=string::npos||s.find("aca")!=string::npos) cout<<3<<endl;
else if(s.find("abca")!=string::npos||s.find("acba")!=string::npos) cout<<4<<endl;
else if(s.find("abbacca")!=string::npos||s.find("accabba")!=string::npos) cout<<7<<endl;
else cout<<-1<<endl;
```

#### 题解作者：Jerrlee✅ (赞：6)
**星级：4星**
**关键亮点：**
- 直接枚举了所有可能的子串模式，并通过`find`函数快速判断是否存在。
- 代码简洁，易于理解。

**核心代码：**
```cpp
if(s.find("aa")!=string::npos) cout<<2<<endl;
else if(s.find("aba")!=string::npos||s.find("aca")!=string::npos) cout<<3<<endl;
else if(s.find("abca")!=string::npos||s.find("acba")!=string::npos) cout<<4<<endl;
else if(s.find("abbacca")!=string::npos||s.find("accabba")!=string::npos) cout<<7<<endl;
else cout<<-1<<endl;
```

#### 题解作者：_cpp (赞：0)
**星级：4星**
**关键亮点：**
- 详细解释了为什么只需要考虑以'a'开头和结尾的子串。
- 代码简洁，逻辑清晰。

**核心代码：**
```cpp
if(a.find("aa") != -1) cout << "2\n";
else if(a.find("aba") != -1 || a.find("aca") != -1) cout << "3\n"; 
else if(a.find("abca") != -1 || a.find("acba") != -1) cout << "4\n";
else if(a.find("abbacca") != -1 || a.find("accabba") != -1) cout << "7\n";
else cout <<"-1\n";
```

### 最优关键思路与技巧
1. **分类讨论**：通过枚举可能的子串模式，快速判断是否存在满足条件的子串。
2. **字符串查找**：使用`find`函数高效判断子串是否存在。
3. **数学证明**：通过数学分析，排除不可能的情况，减少不必要的计算。

### 可拓展之处
- 类似的问题可以通过枚举可能的模式来解决，尤其是当问题的解空间有限时。
- 可以扩展到包含更多字符的字符串，或者更复杂的条件。

### 推荐题目
1. [P3375 【模板】KMP字符串匹配](https://www.luogu.com.cn/problem/P3375)
2. [P3805 【模板】Manacher算法](https://www.luogu.com.cn/problem/P3805)
3. [P3376 【模板】AC自动机（简单版）](https://www.luogu.com.cn/problem/P3376)

### 个人心得摘录
- **zhaoyp**：通过分析两个'a'之间的距离，能够有效地缩小解空间，减少不必要的计算。
- **Jerrlee✅**：直接枚举所有可能的子串模式，虽然简单，但在实际应用中非常有效。
- **_cpp**：解释了为什么只需要考虑以'a'开头和结尾的子串，这种思维方式可以帮助解决类似的问题。

---
处理用时：40.94秒