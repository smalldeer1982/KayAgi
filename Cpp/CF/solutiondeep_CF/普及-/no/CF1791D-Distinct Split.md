# 题目信息

# Distinct Split

## 题目描述

Let's denote the $ f(x) $ function for a string $ x $ as the number of distinct characters that the string contains. For example $ f(\texttt{abc}) = 3 $ , $ f(\texttt{bbbbb}) = 1 $ , and $ f(\texttt{babacaba}) = 3 $ .

Given a string $ s $ , split it into two non-empty strings $ a $ and $ b $ such that $ f(a) + f(b) $ is the maximum possible. In other words, find the maximum possible value of $ f(a) + f(b) $ such that $ a + b = s $ (the concatenation of string $ a $ and string $ b $ is equal to string $ s $ ).

## 说明/提示

For the first test case, there is only one valid way to split $ \texttt{aa} $ into two non-empty strings $ \texttt{a} $ and $ \texttt{a} $ , and $ f(\texttt{a}) + f(\texttt{a}) = 1 + 1 = 2 $ .

For the second test case, by splitting $ \texttt{abcabcd} $ into $ \texttt{abc} $ and $ \texttt{abcd} $ we can get the answer of $ f(\texttt{abc}) + f(\texttt{abcd}) = 3 + 4 = 7 $ which is maximum possible.

For the third test case, it doesn't matter how we split the string, the answer will always be $ 2 $ .

## 样例 #1

### 输入

```
5
2
aa
7
abcabcd
5
aaaaa
10
paiumoment
4
aazz```

### 输出

```
2
7
2
10
3```

# AI分析结果

### 题目内容
# 不同的拆分

## 题目描述
我们用函数 $f(x)$ 表示字符串 $x$ 中不同字符的数量。例如，$f(\texttt{abc}) = 3$，$f(\texttt{bbbbb}) = 1$，$f(\texttt{babacaba}) = 3$。

给定一个字符串 $s$，将其拆分为两个非空字符串 $a$ 和 $b$，使得 $f(a) + f(b)$ 尽可能大。换句话说，找到最大可能的 $f(a) + f(b)$ 的值，其中 $a + b = s$（字符串 $a$ 和字符串 $b$ 的拼接等于字符串 $s$）。

## 说明/提示
对于第一个测试用例，只有一种有效的方法将 $\texttt{aa}$ 拆分为两个非空字符串 $\texttt{a}$ 和 $\texttt{a}$，且 $f(\texttt{a}) + f(\texttt{a}) = 1 + 1 = 2$。

对于第二个测试用例，将 $\texttt{abcabcd}$ 拆分为 $\texttt{abc}$ 和 $\texttt{abcd}$，我们可以得到答案 $f(\texttt{abc}) + f(\texttt{abcd}) = 3 + 4 = 7$，这是最大可能值。

对于第三个测试用例，无论我们如何拆分字符串，答案始终是 $2$。

## 样例 #1
### 输入
```
5
2
aa
7
abcabcd
5
aaaaa
10
paiumoment
4
aazz
```
### 输出
```
2
7
2
10
3
```

### 算法分类
枚举

### 综合分析与结论
这些题解的核心思路都是通过枚举字符串的拆分位置，来计算不同拆分方式下 $f(a) + f(b)$ 的值，进而找到最大值。算法要点在于利用数组记录每个字符的出现次数，难点在于如何高效地在枚举拆分位置时更新两个子串中不同字符的数量。各题解本质思路相近，主要区别在于代码实现细节和变量命名等方面。

### 所选的题解
- **作者：WilliamFranklin (5星)**
    - **关键亮点**：思路清晰，代码简洁明了，通过两个数组分别记录前缀和总的字符出现次数，在枚举拆分位置时巧妙利用这两个数组计算不同字符数量，时间复杂度分析准确。
    - **重点代码**：
```cpp
int main() {
    int t;
    cin >> t;
    while (t--) {
        memset(cnt, 0, sizeof(cnt));
        memset(pre, 0, sizeof(pre));
        int n;
        string s;
        cin >> n >> s;
        for (int i = 0; i < n; i++) {
            cnt[s[i] - 'a'] ++;
        }
        int nans = 0;
        for (int i = 0; i < n; i++) {
            pre[s[i] - 'a']++;
            int ans = 0;
            for (int i = 0; i < 26; i++) {
                if (pre[i]) {
                    ans++;
                }
                if (cnt[i]!= pre[i]) {
                    ans++;
                }
            }
            nans = max(nans, ans);
        }
        cout << nans << endl;
    }
    return 0;
}
```
    - **核心实现思想**：先统计字符串中每个字符的总出现次数到 `cnt` 数组，然后在枚举拆分位置时，更新 `pre` 数组表示前缀中字符出现次数，通过判断 `pre` 数组和 `cnt` 数组的情况计算不同字符数量。

- **作者：BlackPanda (4星)**
    - **关键亮点**：解题思路阐述清晰，代码逻辑明确，利用两个数组 `c1` 和 `c2` 分别记录两个子串字符出现次数，通过遍历字符串动态更新数组并计算结果。
    - **重点代码**：
```cpp
void solve()
{
    res = 0;
    memset(c1, 0, sizeof(c1));
    memset(c2, 0, sizeof(c2));
    cin >> n >> s;
    for (int i = 0; i < n; i ++ )
        c1[s[i] - 'a' + 1] ++ ;
    for (int i = 0; i < n; i ++ )
    {
        c1[s[i] - 'a' + 1] -- ;
        c2[s[i] - 'a' + 1] ++ ;
        int s1 = 0, s2 = 0;
        for (int j = 1; j <= 26; j ++ )
        {
            if (c1[j])	s1 ++ ;
            if (c2[j])	s2 ++ ;
        }
        res = max(res, s1 + s2);
    }
    cout << res << endl;
    return ;
}
```
    - **核心实现思想**：先将字符串所有字符出现次数记录到 `c1` 数组，遍历字符串时，每次将当前字符从 `c1` 中减 1 并加到 `c2` 中，然后统计 `c1` 和 `c2` 中不为 0 的元素个数得到 `f(a) + f(b)` 的值。

### 最优关键思路或技巧
利用数组记录字符出现次数，在枚举拆分位置时动态更新数组，避免重复计算，从而高效地求出不同拆分方式下 $f(a) + f(b)$ 的值。

### 同类型题或类似算法套路拓展
此类题目属于字符串枚举类型，通常涉及对字符串的某种划分或组合操作，并根据特定规则计算结果。类似套路是先确定枚举的维度（如本题的拆分位置），然后利用合适的数据结构（如数组记录字符出现情况）在枚举过程中动态维护所需信息以计算目标值。

### 洛谷相似题目推荐
- [P1036 选数](https://www.luogu.com.cn/problem/P1036)：通过枚举不同数字组合来满足特定条件，与本题枚举拆分位置思路类似。
- [P1157 组合的输出](https://www.luogu.com.cn/problem/P1157)：同样是枚举组合情况，计算满足条件的结果，加深对枚举算法的理解。
- [P1433 吃奶酪](https://www.luogu.com.cn/problem/P1433)：通过枚举路径来寻找最优解，和本题枚举拆分方式找最优值思路相近。

### 个人心得摘录与总结
无。 

---
处理用时：51.67秒