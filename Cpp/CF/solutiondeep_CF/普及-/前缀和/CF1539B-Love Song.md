# 题目信息

# Love Song

## 题目描述

Petya once wrote a sad love song and shared it to Vasya. The song is a string consisting of lowercase English letters. Vasya made up $ q $ questions about this song. Each question is about a subsegment of the song starting from the $ l $ -th letter to the $ r $ -th letter. Vasya considers a substring made up from characters on this segment and repeats each letter in the subsegment $ k $ times, where $ k $ is the index of the corresponding letter in the alphabet. For example, if the question is about the substring "abbcb", then Vasya repeats letter 'a' once, each of the letters 'b' twice, letter 'c" three times, so that the resulting string is "abbbbcccbb", its length is $ 10 $ . Vasya is interested about the length of the resulting string.

Help Petya find the length of each string obtained by Vasya.

## 说明/提示

In the first example Vasya is interested in three questions. In the first question Vasya considers the substring "aba", that transforms to "abba", so the answer is equal to $ 4 $ . In the second question Vasya considers "baca", that transforms to "bbaccca", so the answer is $ 7 $ . In the third question Vasya considers the string "abacaba",that transforms to "abbacccabba" of length $ 11 $ .

## 样例 #1

### 输入

```
7 3
abacaba
1 3
2 5
1 7```

### 输出

```
4
7
11```

## 样例 #2

### 输入

```
7 4
abbabaa
1 3
5 7
6 6
2 4```

### 输出

```
5
4
1
5```

## 样例 #3

### 输入

```
13 7
sonoshikumiwo
1 5
2 10
7 7
1 13
4 8
2 5
3 9```

### 输出

```
82
125
9
191
62
63
97```

# AI分析结果



# Love Song

## 题目描述

Petya 写了一首悲伤的情歌并分享给 Vasya。这首歌是一个由小写英文字母组成的字符串。Vasya 提出了 $q$ 个关于这首歌的问题。每个问题涉及歌曲中从第 $l$ 个字母到第 $r$ 个字母的子段。Vasya 将这段子字符串中的每个字母重复 $k$ 次，其中 $k$ 是该字母在字母表中的位置（例如，'a' 对应 1，'b' 对应 2，依此类推）。例如对于子段 "abbcb"，转换后的字符串为 "abbbbcccbb"，其长度为 10。请帮助 Petya 计算每个问题对应的字符串长度。

## 样例 #1

### 输入

```
7 3
abacaba
1 3
2 5
1 7
```

### 输出

```
4
7
11
```

---

### 综合分析与结论
所有题解均采用**前缀和**算法，将字母转换为对应数值后预处理前缀和数组。查询时直接通过区间和差值得出结果，时间复杂度从暴力解法的 $O(qn)$ 优化至 $O(n+q)$。这是处理静态区间和查询问题的标准解法。

### 优质题解推荐
#### 1. BurningEnderDragon（★★★★★）
**亮点**：清晰的问题转化思路，完整代码模板，时间复杂度分析  
**核心代码**：
```cpp
int ans[100001];
string song;
for(int i=1;i<=n;++i) {
    ans[i] = ans[i-1] + song[i-1] - 'a' + 1;
}
cout << ans[r] - ans[l-1];
```
**实现思想**：  
1. 将字符转换为对应数值（'a'→1，'b'→2）  
2. 预处理前缀和数组  
3. 通过差值公式计算区间和

#### 2. ZBAA_MKC（★★★★☆）
**亮点**：详细讲解前缀和适用场景，对比暴力解法优劣  
**核心代码**：
```cpp
int p[100005];
char c;
p[i] = p[i-1] + (c - 'a' + 1);
```
**实现思想**：  
- 强调静态区间和场景下前缀和的效率优势  
- 使用更紧凑的输入处理方式

#### 3. 张语诚ZYC（★★★★☆）
**亮点**：包含输入优化技巧，完整代码模板  
**核心代码**：
```cpp
inline int read_char() {
    return ch - 'a' + 1;
}
data[i] = data[i-1] + read_char();
```
**实现思想**：  
- 通过自定义输入函数加速字符处理  
- 直接构建前缀和数组

### 关键技巧总结
1. **字符数值转换**：`char_value = c - 'a' + 1`  
2. **前缀和预处理**：`sum[i] = sum[i-1] + char_value`  
3. **区间和公式**：`sum[r] - sum[l-1]`

### 拓展应用
此解法可推广至所有**静态区间和**问题（如子数组求和）。对于动态更新的场景，需改用树状数组或线段树。

### 推荐练习题
1. P1115 最大子段和（前缀和变形）  
2. P3131 [USACO16JAN] Subsequences Summing to Sevens S（模数前缀和）  
3. P3406 海底高铁（差分数组应用）  

### 题解心得摘录
> "暴力加一定会爆，算了，加优化吧" —— Harry_Hedwig  
> "比赛时一眼看出前缀和" —— 123hh2  
> **总结**：区间和问题优先考虑前缀和预处理，避免暴力遍历。

---
处理用时：46.03秒