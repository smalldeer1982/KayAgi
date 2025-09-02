# 题目信息

# Flexible String

## 题目描述

You have a string $ a $ and a string $ b $ . Both of the strings have length $ n $ . There are at most $ 10 $ different characters in the string $ a $ . You also have a set $ Q $ . Initially, the set $ Q $ is empty. You can apply the following operation on the string $ a $ any number of times:

- Choose an index $ i $ ( $ 1\leq i \leq n $ ) and a lowercase English letter $ c $ . Add $ a_i $ to the set $ Q $ and then replace $ a_i $ with $ c $ .

For example, Let the string $ a $ be " $ \tt{abecca} $ ". We can do the following operations:

- In the first operation, if you choose $ i = 3 $ and $ c = \tt{x} $ , the character $ a_3 = \tt{e} $ will be added to the set $ Q $ . So, the set $ Q $ will be $ \{\tt{e}\} $ , and the string $ a $ will be " $ \tt{ab\underline{x}cca} $ ".
- In the second operation, if you choose $ i = 6 $ and $ c = \tt{s} $ , the character $ a_6 = \tt{a} $ will be added to the set $ Q $ . So, the set $ Q $ will be $ \{\tt{e}, \tt{a}\} $ , and the string $ a $ will be " $ \tt{abxcc\underline{s}} $ ".

You can apply any number of operations on $ a $ , but in the end, the set $ Q $ should contain at most $ k $ different characters. Under this constraint, you have to maximize the number of integer pairs $ (l, r) $ ( $ 1\leq l\leq r \leq n $ ) such that $ a[l,r] = b[l,r] $ . Here, $ s[l,r] $ means the substring of string $ s $ starting at index $ l $ (inclusively) and ending at index $ r $ (inclusively).

## 说明/提示

In the first case, we can select index $ i = 3 $ and replace it with character $ c = \tt{d} $ . All possible pairs $ (l,r) $ will be valid.

In the second case, we can't perform any operation. The $ 3 $ valid pairs $ (l,r) $ are:

1. $ a[1,1] = b[1,1] = $ " $ \tt{a} $ ",
2. $ a[1,2] = b[1,2] = $ " $ \tt{ab} $ ",
3. $ a[2,2] = b[2,2] = $ " $ \tt{b} $ ".

In the third case, we can choose index $ 2 $ and index $ 3 $ and replace them with the characters $ \tt{c} $ and $ \tt{d} $ respectively. The final set $ Q $ will be $ \{\tt{b}\} $ having size $ 1 $ that satisfies the value of $ k $ . All possible pairs $ (l,r) $ will be valid.

## 样例 #1

### 输入

```
6
3 1
abc
abd
3 0
abc
abd
3 1
xbb
xcd
4 1
abcd
axcb
3 10
abc
abd
10 3
lkwhbahuqa
qoiujoncjb```

### 输出

```
6
3
6
6
6
11```

# AI分析结果

### 题目内容
# Flexible String

## 题目描述

你有两个字符串 $a$ 和 $b$，它们的长度都是 $n$。字符串 $a$ 中最多有 $10$ 个不同的字符。你还有一个初始为空的集合 $Q$。你可以对字符串 $a$ 进行任意次数的操作，每次操作如下：

- 选择一个下标 $i$（$1\leq i \leq n$）和一个小写英文字母 $c$。将 $a_i$ 添加到集合 $Q$ 中，然后将 $a_i$ 替换为 $c$。

例如，假设字符串 $a$ 为 " $\tt{abecca}$ "。我们可以进行以下操作：

- 在第一次操作中，如果你选择 $i = 3$ 和 $c = \tt{x}$，字符 $a_3 = \tt{e}$ 将被添加到集合 $Q$ 中。因此，集合 $Q$ 将变为 $\{\tt{e}\}$，字符串 $a$ 将变为 " $\tt{ab\underline{x}cca}$ "。
- 在第二次操作中，如果你选择 $i = 6$ 和 $c = \tt{s}$，字符 $a_6 = \tt{a}$ 将被添加到集合 $Q$ 中。因此，集合 $Q$ 将变为 $\{\tt{e}, \tt{a}\}$，字符串 $a$ 将变为 " $\tt{abxcc\underline{s}}$ "。

你可以对 $a$ 进行任意次数的操作，但最终集合 $Q$ 中最多只能包含 $k$ 个不同的字符。在这个约束下，你需要最大化满足 $a[l,r] = b[l,r]$ 的整数对 $(l, r)$（$1\leq l\leq r \leq n$）的数量。其中，$s[l,r]$ 表示字符串 $s$ 从下标 $l$ 到下标 $r$ 的子串。

## 说明/提示

在第一个样例中，我们可以选择下标 $i = 3$ 并将其替换为字符 $c = \tt{d}$。所有可能的 $(l,r)$ 对都将有效。

在第二个样例中，我们无法进行任何操作。有效的 $(l,r)$ 对有：

1. $a[1,1] = b[1,1] = $ " $\tt{a}$ ",
2. $a[1,2] = b[1,2] = $ " $\tt{ab}$ ",
3. $a[2,2] = b[2,2] = $ " $\tt{b}$ "。

在第三个样例中，我们可以选择下标 $2$ 和 $3$ 并将它们分别替换为字符 $\tt{c}$ 和 $\tt{d}$。最终的集合 $Q$ 将是 $\{\tt{b}\}$，大小为 $1$，满足 $k$ 的约束。所有可能的 $(l,r)$ 对都将有效。

## 样例 #1

### 输入

```
6
3 1
abc
abd
3 0
abc
abd
3 1
xbb
xcd
4 1
abcd
axcb
3 10
abc
abd
10 3
lkwhbahuqa
qoiujoncjb```

### 输出

```
6
3
6
6
6
11```

### 算法分类
枚举、深度优先搜索 (DFS)

### 题解分析与结论
本题的核心在于如何通过操作字符串 $a$，使得最终 $a$ 和 $b$ 的相同子串数量最大化。由于字符串 $a$ 中最多只有 $10$ 个不同的字符，且 $k$ 的最大值也为 $10$，因此可以通过枚举或搜索的方式来处理。

### 精选题解
#### 题解1：作者：_acat_ (赞：2)
**星级：4星**
**关键亮点：**
- 使用 DFS 枚举所有可能的字符组合，确保集合 $Q$ 中的字符数不超过 $k$。
- 通过扫描字符串 $a$，计算每段与 $b$ 相等的子串长度，并利用组合数公式计算贡献。
- 代码结构清晰，逻辑严谨，时间复杂度为 $O(2^{10} \times n)$，能够通过题目要求。

**核心代码：**
```cpp
void solve(int pos,int cnt){
    if(cnt>k) return;
    if(pos==num){
        if(cnt==k) ans=max(ans,cal());
        return;
    }
    solve(pos+1,cnt);
    vis[valid[pos]-'a']=1;
    solve(pos+1,cnt+1);
    vis[valid[pos]-'a']=0;
}
```

#### 题解2：作者：ningago (赞：2)
**星级：4星**
**关键亮点：**
- 使用 bitset 维护每种字符的出现位置，优化了枚举的效率。
- 通过枚举字符是否被修改，计算每种情况下的最大贡献。
- 代码实现简洁，时间复杂度为 $O(n \cdot 2^k)$，适合处理多组测试数据。

**核心代码：**
```cpp
for(int t = 0;t < (1 << idx);t++){
    int cnt = 0;
    for(int i = 1;i <= idx;i++){
        if((1 << (i - 1)) & t) cnt++;
    }
    if(cnt > K) continue;
    now = tmp;
    for(int i = 1;i <= idx;i++){
        if((1 << (i - 1)) & t) now |= bs[i];
    }
    int last = 0;
    long long res = 0;
    for(int i = 1;i <= n + 1;i++){
        if(!now[i]){
            if(last){
                int p = i - 1;
                int len = p - last + 1;
                res += 1ll * len * (len + 1) / 2ll;
            }
            last = 0;
        }
        else if(!last) last = i;
    }
    ans = max(ans,res);
}
```

#### 题解3：作者：_Z_F_R_ (赞：1)
**星级：4星**
**关键亮点：**
- 通过 DFS 枚举字符是否被修改，确保集合 $Q$ 中的字符数不超过 $k$。
- 使用贪心策略，将字符修改为 $b$ 中对应字符，最大化贡献。
- 代码实现清晰，时间复杂度为 $O(2^{10} \times n)$，适合处理多组测试数据。

**核心代码：**
```cpp
void dfs(int nowi,int res,vector<bool> now){
    if(nowi > n) return;
    maxans = max(ans_check(now),maxans);
    if(res == 0) return;
    for(int i = nowi + 1;i <= re_size;i++)
        dfs(i,res - 1,change(now,represent[i]));
}
```

### 最优关键思路或技巧
1. **枚举与搜索**：由于字符种类有限，可以通过枚举或搜索的方式处理所有可能的字符组合，确保集合 $Q$ 中的字符数不超过 $k$。
2. **贪心策略**：在修改字符时，优先将字符修改为 $b$ 中对应字符，以最大化贡献。
3. **组合数计算**：通过计算连续相等子串的长度，利用组合数公式快速计算贡献。

### 可拓展之处
本题的枚举与搜索策略可以应用于其他类似的字符串处理问题，特别是当字符种类有限时。类似的题目可以通过枚举字符组合或使用贪心策略来优化解决方案。

### 推荐题目
1. [P1042 乒乓球](https://www.luogu.com.cn/problem/P1042)
2. [P1036 选数](https://www.luogu.com.cn/problem/P1036)
3. [P1028 数的计算](https://www.luogu.com.cn/problem/P1028)

---
处理用时：64.43秒