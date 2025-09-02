# 题目信息

# Prefix-Suffix Palindrome (Easy version)

## 题目描述

This is the easy version of the problem. The difference is the constraint on the sum of lengths of strings and the number of test cases. You can make hacks only if you solve all versions of this task.

You are given a string $ s $ , consisting of lowercase English letters. Find the longest string, $ t $ , which satisfies the following conditions:

- The length of $ t $ does not exceed the length of $ s $ .
- $ t $ is a palindrome.
- There exists two strings $ a $ and $ b $ (possibly empty), such that $ t = a + b $ ( " $ + $ " represents concatenation), and $ a $ is prefix of $ s $ while $ b $ is suffix of $ s $ .

## 说明/提示

In the first test, the string $ s =  $ "a" satisfies all conditions.

In the second test, the string "abcdfdcba" satisfies all conditions, because:

- Its length is $ 9 $ , which does not exceed the length of the string $ s $ , which equals $ 11 $ .
- It is a palindrome.
- "abcdfdcba" $ = $ "abcdfdc" $ + $ "ba", and "abcdfdc" is a prefix of $ s $ while "ba" is a suffix of $ s $ .

It can be proven that there does not exist a longer string which satisfies the conditions.

In the fourth test, the string "c" is correct, because "c" $ = $ "c" $ + $ "" and $ a $ or $ b $ can be empty. The other possible solution for this test is "s".

## 样例 #1

### 输入

```
5
a
abcdfdcecba
abbaxyzyx
codeforces
acbba```

### 输出

```
a
abcdfdcba
xyzyx
c
abba```

# AI分析结果

### 题目内容中文重写
# 前缀 - 后缀回文串（简单版本）

## 题目描述
这是该问题的简单版本。不同之处在于字符串长度总和的限制以及测试用例的数量。只有当你解决了所有版本的任务后，才能进行 Hack 操作。

给定一个由小写英文字母组成的字符串 $s$。请找出满足以下条件的最长字符串 $t$：
- $t$ 的长度不超过 $s$ 的长度。
- $t$ 是一个回文串。
- 存在两个字符串 $a$ 和 $b$（可能为空），使得 $t = a + b$（“$+$” 表示字符串连接），并且 $a$ 是 $s$ 的前缀，$b$ 是 $s$ 的后缀。

## 说明/提示
在第一个测试用例中，字符串 $s =$ "a" 满足所有条件。

在第二个测试用例中，字符串 "abcdfdcba" 满足所有条件，原因如下：
- 它的长度为 $9$，不超过字符串 $s$ 的长度（$s$ 的长度为 $11$）。
- 它是一个回文串。
- "abcdfdcba" $=$ "abcdfdc" $+$ "ba"，其中 "abcdfdc" 是 $s$ 的前缀，"ba" 是 $s$ 的后缀。

可以证明不存在更长的满足条件的字符串。

在第四个测试用例中，字符串 "c" 是正确的，因为 "c" $=$ "c" $+$ ""，并且 $a$ 或 $b$ 可以为空。该测试用例的另一个可能的解是 "s"。

## 样例 #1
### 输入
```
5
a
abcdfdcecba
abbaxyzyx
codeforces
acbba
```
### 输出
```
a
abcdfdcba
xyzyx
c
abba
```

### 算法分类
字符串

### 综合分析与结论
这些题解的核心思路都是先找出互为反串的最长前后缀，然后在剩余的子串中找出最长的回文前缀或后缀。不同题解的区别在于实现剩余子串中最长回文前后缀查找的方法不同，主要有暴力枚举、Manacher 算法、哈希匹配、KMP 算法等。

### 所选题解
- StudyingFather（4星）
    - 关键亮点：思路清晰，使用 Manacher 算法将时间复杂度优化到 $O(n)$，代码实现完整。
- xht（4星）
    - 关键亮点：同样采用贪心和 Manacher 算法，代码简洁，逻辑清晰。
- AutumnKite（4星）
    - 关键亮点：详细分析了暴力解法的思路，并通过优化得到 $O(n)$ 的解法，对理解问题有很大帮助。

### 重点代码及核心实现思想
#### StudyingFather 的代码
```cpp
// 初始化字符串，插入分隔符 '#'
void init()
{
    t[0]=t[1]='#';
    int len=strlen(s);
    for(int i=0;i<len;i++)
    {
        t[2*i+2]=s[i];
        t[2*i+3]='#';
    }
    t[2*len+2]=0;
}

int main()
{
    int T;
    cin>>T;
    while(T--)
    {
        cin>>s;
        init();
        int len=strlen(t+1),l=1,r=len;
        // 找出互为反串的最长前后缀
        while(l<=r)
        {
            if(t[l]==t[r])l++,r--;
            else break;
        }
        int ans=0,nl=l,nr=l,maxr=l,mid=l;
        // Manacher 算法求剩余子串的最长回文串
        for(int i=l;i<=r;i++)
        {
            if(i<maxr)
                f[i]=min(f[mid]+(mid-i),f[mid*2-i]);
            else
                f[i]=1;
            while(t[i+f[i]]==t[i-f[i]]&&i+f[i]<=r&&i-f[i]>=l)
                f[i]++;
            if(f[i]+i>maxr)
            {
                maxr=f[i]+i;
                mid=i;
            }
            if((i-f[i]<l||i+f[i]>r)&&f[i]>ans)
            {
                nl=i-f[i]+1;
                nr=i+f[i]-1;
                ans=f[i];
            }
        }
        if(l>r)
        {
            cout<<s<<endl;
            continue;
        }
        // 输出结果
        for(int i=1;i<l;i++)
            if(t[i]!='#')cout<<t[i];
        for(int i=nl;i<=nr;i++)
            if(t[i]!='#')cout<<t[i];
        for(int i=r+1;i<=len;i++)
            if(t[i]!='#')cout<<t[i];
        cout<<endl;
    }
    return 0;
}
```
核心实现思想：先对字符串进行预处理，插入分隔符 '#'，然后使用双指针找出互为反串的最长前后缀，接着在剩余的子串中使用 Manacher 算法找出最长的回文串，最后将前后缀和最长回文串拼接输出。

#### xht 的代码
```cpp
// 计算字符串的最长回文前缀
inline int work(char *s, int n) {
    string ss = "$#";
    vi p;
    for (int i = 1; i <= n; i++) ss += s[i], ss += "#";
    p.pb(1);
    int mx = 0, id = 0, ans = 1;
    for (int i = 1; i < (int)ss.length(); i++) {
        p.pb(mx > i ? min(p[2*id-i], mx - i) : 1);
        while (i + p[i] < (int)ss.length() && ss[i+p[i]] == ss[i-p[i]]) ++p[i];
        if (i == p[i]) ans = max(ans, p[i]);
        if (i + p[i] > mx) mx = i + p[i], id = i;
    }
    return ans - 1;
}

inline void solve() {
    rds(s, n);
    int p = 1;
    // 找出互为反串的最长前后缀
    while (p <= n && s[p] == s[n+1-p]) ++p;
    if (p == n + 1) {
        for (int i = 1; i <= n; i++) putchar(s[i]);
        return puts(""), void();
    }
    m = 0;
    for (int i = p; i <= n + 1 - p; i++) t[++m] = s[i];
    // 计算剩余子串的最长回文前缀和后缀
    int l = work(t, m);
    reverse(t + 1, t + m + 1);
    int r = work(t, m);
    reverse(t + 1, t + m + 1);
    if (l < r) reverse(t + 1, t + m + 1), swap(l, r);
    // 输出结果
    for (int i = 1; i < p; i++) putchar(s[i]);
    for (int i = 1; i <= l; i++) putchar(t[i]);
    for (int i = p - 1; i; i--) putchar(s[i]);
    puts("");
}
```
核心实现思想：先找出互为反串的最长前后缀，然后将剩余的子串提取出来，分别计算其最长回文前缀和后缀，取较长的一个，最后将前后缀和最长回文串拼接输出。

#### AutumnKite 的代码
```cpp
// Manacher 算法
void manacher(int *d, char *s, int n){
    for (register int i = 1, m = 0, r = 0; i <= n; ++i){
        d[i] = i > r ? 0 : std::min(r - i + 1, d[m - (i - m)]);
        while (i - d[i] > 0 && i + d[i] <= n && s[i - d[i]] == s[i + d[i]]) ++d[i];
        if (i + d[i] - 1 > r) m = i, r = i + d[i] - 1;
    }
}

void solve(){
    n = reads(s + 1);
    for (register int i = n; i; --i) s[i << 1] = s[i], s[i << 1 | 1] = '#';
    s[1] = '#', n = n * 2 + 1;
    manacher(d, s, n);
    int len = 0;
    // 找出互为反串的最长前后缀
    for (register int i = 1; i <= n / 2; ++i)
        if (s[i] != s[n - i + 1]) break;
        else ++len;
    int d1 = 0, d2 = 0;
    // 计算剩余子串的最长回文前缀和后缀
    for (register int i = len + 1; i <= (n + 1) / 2; ++i)
        if (i - d[i] + 1 <= len + 1) d1 = std::max(d1, (i - len) * 2 - 1);
    for (register int i = (n + 1) / 2; i <= n - len; ++i)
        if (i + d[i] - 1 >= n - len) d2 = std::max(d2, (n - len - i + 1) * 2 - 1);
    // 输出结果
    if (d1 > d2){
        for (register int i = 1; i <= len + d1; ++i)
            if (s[i] != '#') putchar(s[i]);
        for (register int i = n - len + 1; i <= n; ++i)
            if (s[i] != '#') putchar(s[i]);
    }
    else{
        for (register int i = 1; i <= len; ++i)
            if (s[i] != '#') putchar(s[i]);
        for (register int i = n - len - d2 + 1; i <= n; ++i)
            if (s[i] != '#') putchar(s[i]);
    }
    putchar('\n');
}
```
核心实现思想：先对字符串进行预处理，插入分隔符 '#'，然后使用 Manacher 算法计算每个位置的回文半径，接着找出互为反串的最长前后缀，再根据回文半径计算剩余子串的最长回文前缀和后缀，最后将前后缀和最长回文串拼接输出。

### 最优关键思路或技巧
- 贪心策略：先找出互为反串的最长前后缀，减少后续处理的字符串长度。
- Manacher 算法：可以在 $O(n)$ 的时间复杂度内找出字符串的最长回文子串。

### 拓展思路
同类型题或类似算法套路：
- 求字符串的最长回文子串的变形问题，如带限制条件的最长回文子串。
- 字符串的前后缀匹配问题，可以使用 KMP 算法、哈希匹配等方法。

### 推荐洛谷题目
- P3805 【模板】manacher 算法
- P5446 [THUPC2018]绿绿和串串
- P1659 [国家集训队]拉拉队排练

### 个人心得摘录与总结
- oimaster：一开始想到 $O(N^3)$ 的暴力算法，发现超时后，通过思考将三重循环改成两个两重循环，关键在于处理开头、结尾已经成功配对的字符，将问题简化。总结：在面对复杂的枚举问题时，可以尝试简化问题，将多维度的枚举转化为单维度的枚举。

---
处理用时：74.12秒