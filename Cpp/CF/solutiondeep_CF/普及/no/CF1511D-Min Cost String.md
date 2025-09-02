# 题目信息

# Min Cost String

## 题目描述

Let's define the cost of a string $ s $ as the number of index pairs $ i $ and $ j $ ( $ 1 \le i < j < |s| $ ) such that $ s_i = s_j $ and $ s_{i+1} = s_{j+1} $ .

You are given two positive integers $ n $ and $ k $ . Among all strings with length $ n $ that contain only the first $ k $ characters of the Latin alphabet, find a string with minimum possible cost. If there are multiple such strings with minimum cost — find any of them.

## 样例 #1

### 输入

```
9 4```

### 输出

```
aabacadbb```

## 样例 #2

### 输入

```
5 1```

### 输出

```
aaaaa```

## 样例 #3

### 输入

```
10 26```

### 输出

```
codeforces```

# AI分析结果

### 题目翻译

#### 题目描述

定义一个字符串 $s$ 的**成本**为满足 $1 \le i < j < |s|$ 且 $s_i = s_j$ 且 $s_{i+1} = s_{j+1}$ 的数对 $(i, j)$ 的个数。

给定两个正整数 $n$ 和 $k$，在所有长度为 $n$ 且仅包含前 $k$ 个小写字母的字符串中，找到一个成本最小的字符串。如果有多个这样的字符串，输出其中任意一个即可。

#### 样例 #1

##### 输入

```
9 4
```

##### 输出

```
aabacadbb
```

#### 样例 #2

##### 输入

```
5 1
```

##### 输出

```
aaaaa
```

#### 样例 #3

##### 输入

```
10 26
```

##### 输出

```
codeforces
```

### 算法分类
构造

### 题解分析与结论

本题的核心在于构造一个长度为 $n$ 的字符串，使得其成本最小。成本的定义是字符串中相邻字符对 $(s_i, s_{i+1})$ 的重复次数。为了最小化成本，我们需要尽量减少相邻字符对的重复出现。

#### 关键思路
1. **构造无重复字符对的字符串**：当 $n \le k^2 + 1$ 时，可以构造一个字符串，使得所有相邻字符对都不重复。具体构造方法为：依次遍历字符集，生成所有可能的相邻字符对，并确保每个字符对只出现一次。
2. **循环构造**：当 $n > k^2 + 1$ 时，无法避免相邻字符对的重复。此时，可以通过循环使用之前构造的字符串，使得每个字符对的出现次数尽可能均匀，从而最小化成本。

#### 最优关键思路
- **构造无重复字符对的字符串**：通过遍历字符集，生成所有可能的相邻字符对，确保每个字符对只出现一次。这种方法在 $n \le k^2 + 1$ 时能够保证成本为 0。
- **循环构造**：当 $n > k^2 + 1$ 时，循环使用之前构造的字符串，使得每个字符对的出现次数尽可能均匀，从而最小化成本。

### 所选高星题解

#### 题解1：Warriors_Cat (5星)
**关键亮点**：
- 详细解释了构造无重复字符对的字符串的方法。
- 通过循环构造的方式处理 $n > k^2 + 1$ 的情况，确保成本最小。
- 代码简洁且高效，时间复杂度为 $O(n + k^2)$。

**核心代码**：
```cpp
int n, k, len; char s[M * M];
inline int num(int x){
    return x % len == 0 ? len : x % len;
} 
inline void mian(){
    n = read(); k = read();
    len = 0;
    rep(j, 1, k){
        s[++len] = j + 'a' - 1;
        rep(i, 1, k - j){
            s[++len] = j + 'a' - 1;
            s[++len] = j + i + 'a' - 1;
        }
    }
    rep(i, 1, n) printf("%c", s[num(i)]);
}
```

#### 题解2：zhongcy (4星)
**关键亮点**：
- 提供了构造无重复字符对的字符串的具体例子。
- 通过循环构造的方式处理 $n > k^2 + 1$ 的情况，确保成本最小。
- 代码简洁且易于理解。

**核心代码**：
```cpp
int n,k,l=0;
char s[901];
cin>>n>>k;
for(int i=1;i<=k;i++){
    s[++l]=i+'a'-1;
    for(int j=i+1;j<=k;j++){
        s[++l]=i+'a'-1;
        s[++l]=j+'a'-1;
    }
}
for(int i=1;i<=n;i++)
    cout<<s[i%l==0?l:i%l];
```

#### 题解3：沉石鱼惊旋 (4星)
**关键亮点**：
- 详细解释了构造无重复字符对的字符串的方法。
- 通过循环构造的方式处理 $n > k^2 + 1$ 的情况，确保成本最小。
- 代码简洁且高效。

**核心代码**：
```cpp
int n, k;
string s;
int main(){
    cin >> n >> k;
    for (int i = 0; i < k; i++){
        s += char(i + 'a');
        for (int j = i + 1; j < k; j++)
            s += char(i + 'a'), s += char(j + 'a');
    }
    for (int i = 0; i < n; i++)
        cout << s[i % s.size()];
    cout << endl;
    return 0;
}
```

### 可拓展之处
- **类似题目**：可以扩展到其他需要构造字符串或序列的题目，如构造无重复子序列的字符串、构造特定模式的字符串等。
- **算法套路**：构造法在字符串问题中非常常见，掌握构造无重复字符对的技巧可以解决类似问题。

### 推荐题目
1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
2. [P1068 分数线划定](https://www.luogu.com.cn/problem/P1068)
3. [P1028 数的计算](https://www.luogu.com.cn/problem/P1028)

---
处理用时：36.38秒