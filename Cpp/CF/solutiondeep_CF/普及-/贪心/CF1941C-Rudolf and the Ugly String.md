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



# Rudolf and the Ugly String 中文翻译

## 题目描述

Rudolf 有一个长度为 $n$ 的字符串 $s$。当字符串 $s$ 包含子串 "pie" 或 "map" 时，Rudolf 认为这个字符串是丑陋的，否则认为是美丽的。

例如："ppiee"、"mmap"、"dfpiefghmap" 是丑陋的，而 "mathp"、"ppiiee" 是美丽的。

Rudolf 希望通过删除最少的字符使字符串变得美丽。你可以删除字符串中任意位置的字符。

## 输入输出样例

输入样例：
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
输出样例：
```
2
0
2
6
0
2
```

---

# 题解分析与结论

## 核心思路
**贪心遍历 + 重叠处理**：  
遍历字符串时，每发现一个 "map" 或 "pie" 子串，计数加 1，并向后跳 2 位（通过 `i += 2`），利用循环自增跳过后续可能重叠的子串。这种方法确保每个需要删除的子串只被计数一次，巧妙处理了如 "mapie" 的重叠情况。

## 关键技巧
1. **跳跃式遍历**：检测到子串后，跳过足够多的位置以避免重复计数。
2. **无需显式处理重叠**：通过指针跳跃自动规避 "mapie" 这类重叠场景。
3. **线性时间复杂度**：仅需单次遍历，时间复杂度为 $O(n)$。

---

# 精选题解

## 题解一（kczw，★★★★★）
**亮点**：  
- 简洁高效，通过指针跳跃隐式处理所有重叠情况。
- 代码仅用单层循环，逻辑清晰。

**核心代码**：
```cpp
for(int i=0; i<n-2; i++) {
    if (s[i]=='m' && s[i+1]=='a' && s[i+2]=='p') {
        ans++;
        i += 2; // 跳过后两位
    } else if (s[i]=='p' && s[i+1]=='i' && s[i+2]=='e') {
        ans++;
        i += 2;
    }
}
```

## 题解二（Weekoder，★★★★★）
**亮点**：  
- 1-based 索引处理，避免边界问题。
- 通过 `substr` 直接比较子串，代码可读性高。

**核心代码**：
```cpp
for (int i=1; i <= n-2; i++) {
    string tmp = s.substr(i, 3);
    if (tmp == "map" || tmp == "pie") {
        ans++;
        i += 2; // 跳过后两位
    }
}
```

---

# 同类题目推荐
1. [P1308 统计单词数](https://www.luogu.com.cn/problem/P1308) - 字符串匹配基础
2. [P3375 KMP字符串匹配](https://www.luogu.com.cn/problem/P3375) - 高效字符串匹配算法
3. [P1026 统计单词个数](https://www.luogu.com.cn/problem/P1026) - 动态规划处理字符串分割

---
处理用时：193.55秒