# 题目信息

# Archaeology

## 题目描述

Alice bought a Congo Prime Video subscription and was watching a documentary on the archaeological findings from Factor's Island on Loch Katrine in Scotland. The archaeologists found a book whose age and origin are unknown. Perhaps Alice can make some sense of it?

The book contains a single string of characters "a", "b" and "c". It has been pointed out that no two consecutive characters are the same. It has also been conjectured that the string contains an unusually long subsequence that reads the same from both sides.

Help Alice verify this by finding such subsequence that contains at least half of the characters of the original string, rounded down. Note that you don't have to maximise the length of it.

A string $ a $ is a subsequence of a string $ b $ if $ a $ can be obtained from $ b $ by deletion of several (possibly, zero or all) characters.

## 说明/提示

In the first example, other valid answers include "cacac", "caac", "aca" and "ccc".

## 样例 #1

### 输入

```
cacbac
```

### 输出

```
aba
```

## 样例 #2

### 输入

```
abc
```

### 输出

```
a
```

## 样例 #3

### 输入

```
cbacacacbcbababacbcb
```

### 输出

```
cbaaacbcaaabc```

# AI分析结果

【题目内容（中文重写）】
# 考古学

## 题目描述
爱丽丝购买了刚果Prime视频订阅服务，正在观看一部关于苏格兰卡特琳湖上因子岛考古发现的纪录片。考古学家们发现了一本年代和出处不明的书。也许爱丽丝能从中看出些什么？

这本书包含一个由字符 "a"、"b" 和 "c" 组成的字符串。已经指出，没有两个连续的字符是相同的。也有人推测，这个字符串包含一个异常长的从两边读都相同的子序列。

通过找到一个至少包含原始字符串一半（向下取整）字符的这样的子序列，来帮助爱丽丝验证这一点。注意，你不必使它的长度最大化。

如果字符串 $a$ 可以通过删除字符串 $b$ 中的几个（可能是零个或全部）字符得到，那么字符串 $a$ 就是字符串 $b$ 的一个子序列。

## 说明/提示
在第一个示例中，其他有效的答案包括 "cacac"、"caac"、"aca" 和 "ccc"。

## 样例 #1
### 输入
```
cacbac
```
### 输出
```
aba
```

## 样例 #2
### 输入
```
abc
```
### 输出
```
a
```

## 样例 #3
### 输入
```
cbacacacbcbababacbcb
```
### 输出
```
cbaaacbcaaabc
```

【算法分类】
构造

【综合分析与结论】
这几道题解的核心思路都是利用字符串仅由 'a'、'b'、'c' 组成且相邻字符不同的特性，通过双指针从字符串两端向中间遍历，每次选取首两位与末两位中的相同字符作为回文子序列的一部分，抛弃不同的字符，不断缩小范围，最终得到满足长度要求的回文子序列。

各题解思路和实现细节略有不同：
- tXX_F 的题解直接存储回文子序列的前半部分，最后再反向输出后半部分。
- _soul_ 的题解分别存储回文子序列的前后两部分，最后合并输出。
- mraymes 的题解使用布尔数组标记哪些字符被选入回文子序列，最后按顺序输出被标记的字符。
- 封禁用户的题解通过优先队列存储被选入回文子序列的字符的坐标，最后按坐标顺序输出字符。

【所选的题解】
- tXX_F（4星）：关键亮点在于思路清晰，代码简洁，直接存储回文子序列的前半部分，最后反向输出后半部分，减少了额外的存储和处理。
- _soul_（3星）：思路与 tXX_F 类似，但代码中分别存储前后两部分，最后合并输出，相对复杂一些。
- mraymes（3星）：使用布尔数组标记被选入的字符，能保证选出的子序列尽量长，但代码中判断无解的部分实际上是多余的，因为根据算法一定存在解。

【重点代码】
tXX_F 的核心代码：
```cpp
inline void work() {
    cin >> s + 1;
    for (l = 1, r = strlen(s + 1); r - l + 1 >= 4; l += 2, r -= 2) {
        if (s[l] == s[r]) {
            ans[len++] = s[l];
        } else if (s[l + 1] == s[r]) {
            ans[len++] = s[l + 1];
        } else if (s[l] == s[r - 1]) {
            ans[len++] = s[l];
        } else if (s[l + 1] == s[r - 1]) {
            ans[len++] = s[l + 1];
        }
    }
    for (int i = 0; i < len; i++) {
        cout << ans[i];
    }
    if (l < r) {
        cout << s[l];
    }
    for (int i = len - 1; i >= 0; i--) {
        cout << ans[i];
    }
}
```
核心实现思想：从字符串两端向中间遍历，每次取首两位与末两位，找到相同的字符存入 `ans` 数组，最后按顺序输出前半部分，中间剩余字符（如果有），再反向输出后半部分。

【关键思路或技巧】
- 利用双指针从字符串两端向中间遍历，每次选取首两位与末两位中的相同字符，保证了回文子序列的性质。
- 由于每次操作抛弃两个字符，而选取的字符数至少为两个，所以能保证最终得到的回文子序列长度至少为原字符串长度的一半。

【拓展思路】
同类型题可能会改变字符种类或增加其他限制条件，但核心思路仍然可以是通过构造的方式，利用字符的特性和双指针来寻找满足条件的子序列。类似算法套路还可以应用于其他字符串处理问题，如寻找特定模式的子串等。

【推荐题目】
- [P1057 传球游戏](https://www.luogu.com.cn/problem/P1057)
- [P1060 开心的金明](https://www.luogu.com.cn/problem/P1060)
- [P1064 金明的预算方案](https://www.luogu.com.cn/problem/P1064)

【个人心得】
_soul_：“这题放在E题着实不合适啊。。但是比赛的时候还想了好久，zbl”，总结：作者认为该题难度与题目序号不匹配，且自己在比赛时思考时间较长。 

---
处理用时：37.33秒