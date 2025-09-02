# 题目信息

# Rudolf and the Ugly String

## 题目描述

Rudolf has a string $ s $ of length $ n $ . Rudolf considers the string $ s $ to be ugly if it contains the substring $ ^\dagger $ "pie" or the substring "map", otherwise the string $ s $ will be considered beautiful.

For example, "ppiee", "mmap", "dfpiefghmap" are ugly strings, while "mathp", "ppiiee" are beautiful strings.

Rudolf wants to shorten the string $ s $ by removing some characters to make it beautiful.

The main character doesn't like to strain, so he asks you to make the string beautiful by removing the minimum number of characters. He can remove characters from any positions in the string (not just from the beginning or end of the string).

 $ ^\dagger $ String $ a $ is a substring of $ b $ if there exists a consecutive segment of characters in string $ b $ equal to $ a $ .

## 说明/提示

In the first test case, for example, you can delete the $ 4 $ th and $ 9 $ th characters to make the string beautiful.

In the second test case, the string is already beautiful.

## 样例 #1

### 输入

```
6
9
mmapnapie
9
azabazapi
8
mappppie
18
mapmapmapmapmapmap
1
p
11
pppiepieeee```

### 输出

```
2
0
2
6
0
2```

# AI分析结果

### 题目翻译
## 鲁道夫与丑陋的字符串

### 题目描述
鲁道夫有一个长度为 $n$ 的字符串 $s$。如果字符串 $s$ 包含子串 $ ^\dagger $ “pie” 或子串 “map”，鲁道夫就认为该字符串是丑陋的，否则该字符串将被认为是美丽的。

例如，“ppiee”、“mmap”、“dfpiefghmap” 是丑陋的字符串，而 “mathp”、“ppiiee” 是美丽的字符串。

鲁道夫想通过删除一些字符来缩短字符串 $s$，使其变得美丽。

主角不喜欢费力，所以他请你通过删除最少数量的字符来使字符串变得美丽。他可以从字符串的任何位置删除字符（不仅仅是从字符串的开头或结尾）。

$ ^\dagger $ 如果字符串 $a$ 等于字符串 $b$ 中的一个连续字符段，则称字符串 $a$ 是字符串 $b$ 的子串。

### 说明/提示
在第一个测试用例中，例如，你可以删除第 4 个和第 9 个字符，使字符串变得美丽。

在第二个测试用例中，字符串已经是美丽的。

### 样例 #1
#### 输入
```
6
9
mmapnapie
9
azabazapi
8
mappppie
18
mapmapmapmapmapmap
1
p
11
pppiepieeee
```

#### 输出
```
2
0
2
6
0
2
```

### 综合分析与结论
- **思路**：各题解核心思路一致，均是遍历字符串，当遇到 “map” 或 “pie” 时，答案加 1，并跳过该子串。同时都考虑到了 “mapie” 这种特殊情况，避免重复计数。
- **算法要点**：通过枚举字符串中的连续三个字符来判断是否为 “map” 或 “pie”，遇到特殊情况 “mapie” 单独处理。
- **解决难点**：主要难点在于处理 “mapie” 这种特殊情况，避免重复统计删除次数。各题解通过不同方式处理该情况，如直接特判、跳过子串等。

### 所选题解
- **作者：kczw（5星）**
    - **关键亮点**：思路清晰，对各种情况分析详细，代码简洁高效，通过手写暴力匹配查找，避免了使用 `find` 函数可能导致的超时问题。
    - **核心代码**：
```cpp
for(int i=0;i<n-2;i++){
    if(s[i]=='m'&&s[i+1]=='a'&&s[i+2]=='p')ans++,i+=2;
    else if(s[i]=='p'&&s[i+1]=='i'&&s[i+2]=='e')ans++,i+=2;
}
```
核心实现思想：遍历字符串，当遇到 “map” 或 “pie” 时，答案加 1，并将索引向后移动 2 位，跳过该子串。

- **作者：CJKZS（4星）**
    - **关键亮点**：思路明确，对 “mapie” 特殊情况进行了清晰的特判，代码逻辑清晰。
    - **核心代码**：
```cpp
while(i<=k-2){
    if(s[i]=='m'&&s[i+1]=='a'&&s[i+2]=='p'&&s[i+3]=='i'&&s[i+4]=='e'){
        ans++;
        i+=5;
    }else if(s[i]=='m'&&s[i+1]=='a'&&s[i+2]=='p'){
        ans++;
        i+=3;
    }else if(s[i]=='p'&&s[i+1]=='i'&&s[i+2]=='e'){
        ans++;
        i+=3;
    }else{
        i++;
    }
}
```
核心实现思想：使用 `while` 循环遍历字符串，遇到 “mapie” 时答案加 1 并跳过 5 个字符，遇到 “map” 或 “pie” 时答案加 1 并跳过 3 个字符，否则索引加 1。

- **作者：yhylivedream（4星）**
    - **关键亮点**：代码简洁，对特殊情况和正常情况的处理逻辑清晰，通过在字符串前加空格避免边界问题。
    - **核心代码**：
```cpp
for (int i = 1; i + 2 <= n; i ++) {
    if (i + 4 <= n && s[i] == 'm' && s[i + 1] == 'a' && s[i + 2] == 'p' && s[i + 3] == 'i' && s[i + 4] == 'e') {
        cnt ++, i += 4;
    } else if (s[i] == 'm' && s[i + 1] == 'a' && s[i + 2] == 'p') {
        cnt ++, i += 2;
    } else if (s[i] == 'p' && s[i + 1] == 'i' && s[i + 2] == 'e') {
        cnt ++, i += 2;
    }
}
```
核心实现思想：遍历字符串，遇到 “mapie” 时答案加 1 并跳过 4 个字符，遇到 “map” 或 “pie” 时答案加 1 并跳过 2 个字符。

### 最优关键思路或技巧
- 采用贪心策略，每次遇到 “map” 或 “pie” 时，只删除一个字符（通常是中间字符），保证删除字符数最少。
- 对于 “mapie” 这种特殊情况进行特判，避免重复计数。
- 手动枚举字符串中的连续字符进行匹配，避免使用 `find` 函数可能带来的超时问题。

### 可拓展之处
同类型题可能会给出更多的丑陋子串，或者要求删除字符后满足其他条件，解题思路依然是遍历字符串，对特殊情况进行特判，同时根据具体条件调整删除策略。

### 洛谷相似题目推荐
- [P1308 统计单词数](https://www.luogu.com.cn/problem/P1308)：考察字符串匹配和计数。
- [P5733 【深基6.例1】自动修正](https://www.luogu.com.cn/problem/P5733)：涉及字符串的替换和处理。
- [P1598 垂直柱状图](https://www.luogu.com.cn/problem/P1598)：需要对字符串进行统计和输出处理。

### 个人心得摘录与总结
- **作者：kczw**：使用 `find` 函数做题意外 TLE，改为手写暴力匹配查找解决问题。总结是在处理字符串匹配问题时，要注意 `find` 函数可能带来的性能问题，必要时采用手动枚举匹配。 

---
处理用时：31.77秒