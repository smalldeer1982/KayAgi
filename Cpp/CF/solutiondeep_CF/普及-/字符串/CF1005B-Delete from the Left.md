# 题目信息

# Delete from the Left

## 题目描述

You are given two strings $ s $ and $ t $ . In a single move, you can choose any of two strings and delete the first (that is, the leftmost) character. After a move, the length of the string decreases by $ 1 $ . You can't choose a string if it is empty.

For example:

- by applying a move to the string "where", the result is the string "here",
- by applying a move to the string "a", the result is an empty string "".

You are required to make two given strings equal using the fewest number of moves. It is possible that, in the end, both strings will be equal to the empty string, and so, are equal to each other. In this case, the answer is obviously the sum of the lengths of the initial strings.

Write a program that finds the minimum number of moves to make two given strings $ s $ and $ t $ equal.

## 说明/提示

In the first example, you should apply the move once to the first string and apply the move once to the second string. As a result, both strings will be equal to "est".

In the second example, the move should be applied to the string "codeforces" $ 8 $ times. As a result, the string becomes "codeforces" $ \to $ "es". The move should be applied to the string "yes" once. The result is the same string "yes" $ \to $ "es".

In the third example, you can make the strings equal only by completely deleting them. That is, in the end, both strings will be empty.

In the fourth example, the first character of the second string should be deleted.

## 样例 #1

### 输入

```
test
west
```

### 输出

```
2
```

## 样例 #2

### 输入

```
codeforces
yes
```

### 输出

```
9
```

## 样例 #3

### 输入

```
test
yes
```

### 输出

```
7
```

## 样例 #4

### 输入

```
b
ab
```

### 输出

```
1
```

# AI分析结果

### 题目内容重写（中文）

**题目描述**

给定两个字符串 $s$ 和 $t$。在每次操作中，你可以选择其中一个字符串并删除其最左边的字符。操作后，字符串的长度减少 $1$。如果字符串为空，则不能选择它。

例如：

- 对字符串 "where" 进行操作后，结果为 "here"，
- 对字符串 "a" 进行操作后，结果为空字符串 ""。

要求通过最少的操作次数使两个字符串相等。最终，两个字符串可能都为空字符串，此时它们相等。在这种情况下，答案显然是两个字符串初始长度的和。

编写一个程序，找到使两个给定字符串 $s$ 和 $t$ 相等所需的最少操作次数。

**说明/提示**

在第一个例子中，你应该对第一个字符串进行一次操作，对第二个字符串进行一次操作。结果，两个字符串都变为 "est"。

在第二个例子中，应该对字符串 "codeforces" 进行 $8$ 次操作。结果，字符串变为 "codeforces" $ \to $ "es"。对字符串 "yes" 进行一次操作。结果，字符串变为 "yes" $ \to $ "es"。

在第三个例子中，你只能通过完全删除字符串使它们相等。即最终两个字符串都为空。

在第四个例子中，应该删除第二个字符串的第一个字符。

**样例 #1**

### 输入

```
test
west
```

### 输出

```
2
```

**样例 #2**

### 输入

```
codeforces
yes
```

### 输出

```
9
```

**样例 #3**

### 输入

```
test
yes
```

### 输出

```
7
```

**样例 #4**

### 输入

```
b
ab
```

### 输出

```
1
```

### 题解综合分析与结论

所有题解的核心思路都是从字符串的末尾开始比较，找到最长的公共后缀，然后通过总长度减去两倍的公共后缀长度得到需要删除的字符数。这种方法的时间复杂度为 $O(\min(len_a, len_b))$，非常高效。

### 所选高星题解

#### 题解1：清小秋ovo (5星)
**关键亮点**：
- 思路清晰，直接从字符串末尾开始比较，找到最长公共后缀。
- 代码简洁，逻辑明确，易于理解。

**核心代码**：
```cpp
int count=0; 
int i=a.length()-1; // 创建两个指针
int j=b.length()-1;
while(i>=0&&j>=0){ //从后往前扫
    if(a[i]==b[j]) count++;
    else break; //如果不一样退出扫描
    i--,j--;
}
cout<<a.length()+b.length()-2*count<<endl;
```

#### 题解2：xzllll07 (4星)
**关键亮点**：
- 使用 `reverse` 函数反转字符串，从开头开始比较，逻辑清晰。
- 代码结构良好，注释详细，易于理解。

**核心代码**：
```cpp
reverse(s1.begin(),s1.end()); //反转，对齐
reverse(s2.begin(),s2.end());
for (int i=0;i<=min(len1,len2)-1;i++) {
    if (s1[i]==s2[i]) {
        counter++;
    }
    else break;//不同就终止循环
}
cout<<len1+len2-counter*2;
```

#### 题解3：happybob (4星)
**关键亮点**：
- 直接从后往前比较，逻辑简单，代码简洁。
- 使用了 `register` 关键字优化循环变量，提升性能。

**核心代码**：
```cpp
for(register int i = lena - 1, j = lenb - 1; i >= 0, j >= 0; --i, --j){
    if(a[i] == b[j])
        sum++;
    else break;
}
cout << lena + lenb - sum * 2;
```

### 最优关键思路或技巧

1. **从后往前比较**：通过从字符串末尾开始比较，找到最长的公共后缀，可以快速确定需要删除的字符数。
2. **反转字符串**：通过反转字符串，可以从开头开始比较，逻辑更加直观。
3. **优化循环变量**：使用 `register` 关键字优化循环变量，提升性能。

### 可拓展之处

- **类似题目**：可以扩展到处理多个字符串的最长公共后缀问题。
- **算法套路**：从后往前比较的思路可以应用于其他字符串匹配问题，如最长公共子串、最长回文子串等。

### 推荐相似题目

1. **洛谷 P3375 【模板】KMP字符串匹配** - 考察字符串匹配算法。
2. **洛谷 P3805 【模板】Manacher算法** - 考察最长回文子串算法。
3. **洛谷 P3376 【模板】AC自动机（简单版）** - 考察多模式串匹配算法。

### 个人心得摘录

- **清小秋ovo**：直接想到从后往前比较，逻辑清晰，代码简洁。
- **xzllll07**：使用 `reverse` 函数反转字符串，从开头开始比较，逻辑更加直观。
- **happybob**：使用 `register` 关键字优化循环变量，提升性能，代码简洁。

这些心得展示了不同作者在解决同一问题时的不同思路和优化技巧，值得借鉴。

---
处理用时：33.63秒