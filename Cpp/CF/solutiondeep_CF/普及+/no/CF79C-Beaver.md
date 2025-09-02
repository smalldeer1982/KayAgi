# 题目信息

# Beaver

## 题目描述

给定一个字符串s和n个字符串b，求s中最长的连续子串使得其中不包含任意b。

## 样例 #1

### 输入

```
Go_straight_along_this_street
5
str
long
tree
biginteger
ellipse
```

### 输出

```
12 4
```

## 样例 #2

### 输入

```
IhaveNoIdea
9
I
h
a
v
e
N
o
I
d
```

### 输出

```
0 0
```

## 样例 #3

### 输入

```
unagioisii
2
ioi
unagi
```

### 输出

```
5 5
```

# AI分析结果

### 题目内容
# 海狸

## 题目描述
给定一个字符串s和n个字符串b，求s中最长的连续子串使得其中不包含任意b。

## 样例 #1
### 输入
```
Go_straight_along_this_street
5
str
long
tree
biginteger
ellipse
```
### 输出
```
12 4
```

## 样例 #2
### 输入
```
IhaveNoIdea
9
I
h
a
v
e
N
o
I
d
```
### 输出
```
0 0
```

## 样例 #3
### 输入
```
unagioisii
2
ioi
unagi
```
### 输出
```
5 5
```

### 算法分类
字符串

### 综合分析与结论
题解利用字符串哈希在 $O(nk)$ 时间内找出原串里所有的限制串，然后记录每个匹配段开始位置对应的限制串中右端点最靠右的位置，最后通过倒序扫描维护当前答案段的右端点来得出结果。其核心思路围绕字符串哈希这一优化手段展开，解决了在原串中快速定位限制串的难点。代码实现上，通过结构体封装哈希相关操作，整体逻辑较为清晰，但代码中存在一些调试相关的冗余代码（如 `eprintf` 相关）。

### 所选的题解
 - **星级**：4星
 - **关键亮点**：使用字符串哈希优化查找限制串的时间复杂度，逻辑清晰，对每个匹配段的右端点处理巧妙。
 - **重点代码**：
```cpp
// 字符串哈希结构体
struct Hasher {
    ull h[100010], p[100010];
    int n;
    void initHash(string& s) {
        n = s.length();
        if (s.front()!= '%') s = "%" + s;
        p[0] = 1;
        repn(i, n) {
            h[i] = h[i - 1] * base + (s[i] - '0' + 1);
            p[i] = p[i - 1] * base;
        }
    }
    ull getRangeHash(int l, int r) { return h[r] - h[l - 1] * p[r - l + 1]; }
    ull getHash(void) { return getRangeHash(1, n); }
} H, h[11];
// 主函数中查找匹配位置及后续处理
repn(j, k) {
    repn(i, n) {
        if (i + len[j] - 1 > n) break;
        if (s[i]!= b[j][1]) continue;
        if (H.getRangeHash(i, i + len[j] - 1) == h[j].getHash()) {
            chmin(rightEnd[i], i + len[j] - 1);
        }
    }
}
int cur = n, ans = 0, ansi = 0;
repd(i, n, 1) {
    if (rightEnd[i] <= cur) cur = rightEnd[i] - 1;
    if (cur - i + 1 >= ans) {
        ans = cur - i + 1;
        ansi = i - 1;
    }
}
```
核心实现思想：`Hasher` 结构体通过预处理计算字符串的哈希值，方便快速比较子串是否相等。主函数中先利用哈希查找所有限制串在原串中的位置，并记录每个起始位置对应的最靠右端点。最后倒序遍历，根据记录的端点更新当前答案段，从而找到最长不包含限制串的子串。

### 最优关键思路或技巧
利用字符串哈希来优化查找子串的时间复杂度，通过记录每个匹配段的右端点信息，巧妙地在一次倒序扫描中得出结果，避免了暴力匹配带来的高时间复杂度。

### 拓展思路
此类题目属于字符串匹配与子串查找问题，类似套路还包括使用KMP算法、AC自动机等解决多模式串匹配问题。当限制串较多且长度较长时，AC自动机可能是更好的选择。

### 洛谷题目推荐
 - [P3375 【模板】KMP字符串匹配](https://www.luogu.com.cn/problem/P3375)
 - [P5357 【模板】AC自动机（简单版）](https://www.luogu.com.cn/problem/P5357)
 - [P2414 阿狸的打字机](https://www.luogu.com.cn/problem/P2414) 

---
处理用时：33.47秒