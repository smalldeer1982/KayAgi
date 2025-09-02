# 题目信息

# [ABC091B] Two Colors Card Game

## 题目描述

有两组字符串，一组蓝色，一组红色，各有n、m个字符串。你可以随便说一个字符串：



如果你在蓝色的字符串组中找到了这个字符串，就加一分；如果在红色的字符串组中找到了，就扣一分。



现在让你输出得分的最大值，且只有得分非负时才输出。

## 样例 #1

### 输入

```
3

apple

orange

apple

1

grape```

### 输出

```
2```

## 样例 #2

### 输入

```
3

apple

orange

apple

5

apple

apple

apple

apple

apple```

### 输出

```
1```

## 样例 #3

### 输入

```
1

voldemort

10

voldemort

voldemort

voldemort

voldemort

voldemort

voldemort

voldemort

voldemort

voldemort

voldemort```

### 输出

```
0```

## 样例 #4

### 输入

```
6

red

red

blue

yellow

yellow

red

5

red

red

yellow

green

blue```

### 输出

```
1```

# AI分析结果

【题目内容】
# [ABC091B] Two Colors Card Game

## 题目描述

有两组字符串，一组蓝色，一组红色，各有n、m个字符串。你可以随便说一个字符串：

如果你在蓝色的字符串组中找到了这个字符串，就加一分；如果在红色的字符串组中找到了，就扣一分。

现在让你输出得分的最大值，且只有得分非负时才输出。

## 样例 #1

### 输入

```
3

apple

orange

apple

1

grape```

### 输出

```
2```

## 样例 #2

### 输入

```
3

apple

orange

apple

5

apple

apple

apple

apple

apple```

### 输出

```
1```

## 样例 #3

### 输入

```
1

voldemort

10

voldemort

voldemort

voldemort

voldemort

voldemort

voldemort

voldemort

voldemort

voldemort

voldemort```

### 输出

```
0```

## 样例 #4

### 输入

```
6

red

red

blue

yellow

yellow

red

5

red

red

yellow

green

blue```

### 输出

```
1```

【算法分类】
模拟

【题解分析与结论】
本题的核心是通过模拟字符串的匹配过程来计算得分，并找出最大得分。两个题解都采用了遍历和统计的方法，但实现方式有所不同。

1. **Ninelife_Cat的题解**：使用`map`数据结构来统计每个字符串的得分，简洁高效。通过遍历蓝组和红组的字符串，直接在`map`中更新得分，最后取最大值。这种方法利用了`map`的自动排序和快速查找特性，代码简洁且易于理解。

2. **LucasXu80的题解**：通过双重循环遍历蓝组和红组的字符串，手动计算每个字符串的得分。虽然思路清晰，但代码复杂度较高，且效率不如使用`map`的方法。

【所选题解】
1. **Ninelife_Cat的题解**（5星）
   - 关键亮点：使用`map`数据结构简化了字符串的统计和查找过程，代码简洁高效。
   - 核心代码：
     ```cpp
     map<string,int> cnt;
     for(ri int i=1;i<=n;++i)
         cin>>s[i],++cnt[s[i]];
     for(ri int i=1;i<=m;++i)
         cin>>t,--cnt[t];
     for(ri int i=1;i<=n;++i)
         ans=max(ans,cnt[s[i]]);
     ```

【最优关键思路】
使用`map`数据结构来统计字符串的得分，可以简化代码并提高效率。`map`的自动排序和快速查找特性使得字符串的统计和查找操作更加高效。

【可拓展之处】
类似的问题可以使用`map`或`unordered_map`来统计和查找元素，如统计单词频率、查找重复元素等。

【推荐题目】
1. P3370 【模板】字符串哈希
2. P3371 【模板】KMP字符串匹配
3. P3372 【模板】Trie树

【个人心得】
Ninelife_Cat的题解中提到了`map`的使用方法，强调了数据结构在简化代码和提高效率方面的重要性。通过使用`map`，可以避免手动遍历和统计的复杂操作，使代码更加简洁和易于维护。

---
处理用时：22.31秒