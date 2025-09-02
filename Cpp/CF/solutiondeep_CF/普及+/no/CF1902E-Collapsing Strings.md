# 题目信息

# Collapsing Strings

## 题目描述

You are given $ n $ strings $ s_1, s_2, \dots, s_n $ , consisting of lowercase Latin letters. Let $ |x| $ be the length of string $ x $ .

Let a collapse $ C(a, b) $ of two strings $ a $ and $ b $ be the following operation:

- if $ a $ is empty, $ C(a, b) = b $ ;
- if $ b $ is empty, $ C(a, b) = a $ ;
- if the last letter of $ a $ is equal to the first letter of $ b $ , then $ C(a, b) = C(a_{1,|a|-1}, b_{2,|b|}) $ , where $ s_{l,r} $ is the substring of $ s $ from the $ l $ -th letter to the $ r $ -th one;
- otherwise, $ C(a, b) = a + b $ , i. e. the concatenation of two strings.

Calculate $ \sum\limits_{i=1}^n \sum\limits_{j=1}^n |C(s_i, s_j)| $ .

## 样例 #1

### 输入

```
3
aba
ab
ba```

### 输出

```
20```

## 样例 #2

### 输入

```
5
abab
babx
xab
xba
bab```

### 输出

```
126```

# AI分析结果

### 题目重写

#### 题目描述

给定 $n$ 个由小写拉丁字母组成的字符串 $s_1, s_2, \dots, s_n$。设 $|x|$ 为字符串 $x$ 的长度。

定义两个字符串 $a$ 和 $b$ 的折叠操作 $C(a, b)$ 如下：

- 如果 $a$ 为空，则 $C(a, b) = b$；
- 如果 $b$ 为空，则 $C(a, b) = a$；
- 如果 $a$ 的最后一个字母等于 $b$ 的第一个字母，则 $C(a, b) = C(a_{1,|a|-1}, b_{2,|b|})$，其中 $s_{l,r}$ 表示字符串 $s$ 从第 $l$ 个字母到第 $r$ 个字母的子串；
- 否则，$C(a, b) = a + b$，即两个字符串的拼接。

请计算 $\sum\limits_{i=1}^n \sum\limits_{j=1}^n |C(s_i, s_j)|$。

#### 样例 #1

##### 输入

```
3
aba
ab
ba
```

##### 输出

```
20
```

#### 样例 #2

##### 输入

```
5
abab
babx
xab
xba
bab
```

##### 输出

```
126
```

### 算法分类
字符串

### 题解分析与结论

本题的核心在于如何高效计算所有字符串对的折叠操作后的长度之和。由于直接枚举所有字符串对的时间复杂度为 $O(n^2)$，无法通过大规模数据，因此需要优化。

大多数题解采用了 Trie 树（字典树）来优化计算过程。具体思路是将所有字符串的反转形式插入到 Trie 树中，然后通过查询每个字符串与 Trie 树中的字符串的最长公共前缀来快速计算折叠操作后的长度。这种方法将时间复杂度降低到 $O(\sum |s_i|)$，能够有效处理大规模数据。

### 高星题解推荐

#### 题解1：作者：__Floze3__ (赞：5)

**星级：5星**

**关键亮点：**
- 使用 Trie 树存储字符串的反转形式，并通过查询最长公共前缀来优化计算。
- 代码清晰，逻辑严谨，时间复杂度低。

**核心代码：**
```cpp
inline void insert(string w){
    int p = 0, len = w.length();
    for (int i = 0; i < len; i++){
        int c = w[i] - 'a';
        if (!trie[p][c])
            trie[p][c] = ++idx;
        p = trie[p][c];
        ++cnt[p];
    }
    return ;
}

inline int query(string w){
    int p = 0, len = w.length(), res = sum + len * n;
    for (int i = len - 1; i >= 0; i--){
        int c = w[i] - 'a';
        if (!trie[p][c])
            return res;
        p = trie[p][c];
        res -= 2 * cnt[p];
    }
    return res;
}
```

#### 题解2：作者：under_the_time (赞：4)

**星级：4星**

**关键亮点：**
- 同样使用 Trie 树优化计算，思路清晰，代码简洁。
- 详细解释了如何通过 Trie 树计算最长公共前缀。

**核心代码：**
```cpp
void insert(string s) {
    int len = s.size(), now = 1;
    for (int i = len - 1;i >= 0;i --) { // 反串
        if (!tr[now][s[i] - 'a'])  
            tr[now][s[i] - 'a'] = ++ cnt;
        now = tr[now][s[i] - 'a'], tot[now] ++;
    }
}
ll query(string s) {
    int len = s.size(), now = 1; ll res = 0;
    for (int i = 0;i < len;i ++) {
        if (!tr[now][s[i] - 'a'])
            return res;
        now = tr[now][s[i] - 'a'], res += tot[now];
    }
    return res;
}
```

#### 题解3：作者：Iniaugoty (赞：4)

**星级：4星**

**关键亮点：**
- 使用 Trie 树优化计算，代码简洁，逻辑清晰。
- 强调了多开 `long long` 的重要性，避免了潜在的溢出问题。

**核心代码：**
```cpp
void Insert(string s) {
	int u = 0;
	for (auto ch : s) {
		++t[u].cnt;
		if (!t[u].s[ch - 'a'])
			t[u].s[ch - 'a'] = ++tot;
		u = t[u].s[ch - 'a'];
	}
	++t[u].cnt;
	return ;
}
LL Query(string s) {
	LL res = sum + n * (LL) s.size(), len = 0, u = 0;
	for (auto ch : s) {
		if (!t[u].s[ch - 'a'])
			t[u].s[ch - 'a'] = ++tot;
		LL cnt = t[u].cnt - t[t[u].s[ch - 'a']].cnt;
		res -= cnt * len * 2;
		u = t[u].s[ch - 'a'];
		++len;
	}
	res -= t[u].cnt * len * 2;
	return res;
}
```

### 最优关键思路或技巧
- **Trie 树的应用**：通过将字符串的反转形式插入 Trie 树，可以高效地查询与目标字符串的最长公共前缀，从而快速计算折叠操作后的长度。
- **时间复杂度优化**：将时间复杂度从 $O(n^2)$ 降低到 $O(\sum |s_i|)$，能够处理大规模数据。
- **避免溢出**：在处理大规模数据时，使用 `long long` 类型避免整数溢出。

### 可拓展之处
- **类似问题**：可以应用于其他需要高效计算字符串对之间关系的题目，如最长公共子串、字符串匹配等。
- **数据结构**：Trie 树在处理字符串问题时非常有用，可以扩展到其他字符串相关的算法中。

### 推荐题目
1. [P3375 【模板】KMP字符串匹配](https://www.luogu.com.cn/problem/P3375)
2. [P3808 【模板】AC自动机（简单版）](https://www.luogu.com.cn/problem/P3808)
3. [P4551 最长异或路径](https://www.luogu.com.cn/problem/P4551)

---
处理用时：49.86秒