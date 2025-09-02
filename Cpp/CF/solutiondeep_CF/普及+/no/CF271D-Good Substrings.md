# 题目信息

# Good Substrings

## 题目描述

You've got string $ s $ , consisting of small English letters. Some of the English letters are good, the rest are bad.

A substring $ s[l...r] $ ( $ 1<=l<=r<=|s| $ ) of string $ s=s_{1}s_{2}...s_{|s|} $ (where $ |s| $ is the length of string $ s $ ) is string $ s_{l}s_{l+1}...s_{r} $ .

The substring $ s[l...r] $ is good, if among the letters $ s_{l},s_{l+1},...,s_{r} $ there are at most $ k $ bad ones (look at the sample's explanation to understand it more clear).

Your task is to find the number of distinct good substrings of the given string $ s $ . Two substrings $ s[x...y] $ and $ s[p...q] $ are considered distinct if their content is different, i.e. $ s[x...y]≠s[p...q] $ .

## 说明/提示

In the first example there are following good substrings: "a", "ab", "b", "ba", "bab".

In the second example there are following good substrings: "a", "aa", "ac", "b", "ba", "c", "ca", "cb".

## 样例 #1

### 输入

```
ababab
01000000000000000000000000
1
```

### 输出

```
5
```

## 样例 #2

### 输入

```
acbacbacaa
00000000000000000000000000
2
```

### 输出

```
8
```

# AI分析结果

### 题目重写
# 好子串

## 题目描述
你有一个由小写英文字母组成的字符串 $s$ 。其中一些英文字母是好的，其余是坏的。
字符串 $s = s_{1}s_{2}...s_{|s|}$ （其中 $|s|$ 是字符串 $s$ 的长度）的子串 $s[l...r]$ （$1 \leq l \leq r \leq |s|$ ）是字符串 $s_{l}s_{l + 1}...s_{r}$ 。
如果在字母 $s_{l}, s_{l + 1},..., s_{r}$ 中最多有 $k$ 个坏字母，那么子串 $s[l...r]$ 就是好的（查看示例的解释可以更清楚地理解）。
你的任务是找出给定字符串 $s$ 中不同的好子串的数量。如果两个子串 $s[x...y]$ 和 $s[p...q]$ 的内容不同，即 $s[x...y] \neq s[p...q]$ ，则认为它们是不同的。

## 说明/提示
在第一个示例中，有以下好子串：“a”，“ab”，“b”，“ba”，“bab”。
在第二个示例中，有以下好子串：“a”，“aa”，“ac”，“b”，“ba”，“c”，“ca”，“cb”。

## 样例 #1
### 输入
```
ababab
01000000000000000000000000
1
```
### 输出
```
5
```

## 样例 #2
### 输入
```
acbacbacaa
00000000000000000000000000
2
```
### 输出
```
8
```

### 算法分类
字符串

### 题解综合分析与结论
这些题解主要围绕如何高效地找出满足条件（最多 $k$ 个坏字母）且本质不同的子串展开。不同题解采用了不同的数据结构和算法思路，如暴力枚举结合哈希判重、Trie树、后缀数组（SA）、后缀自动机（SAM）等。各题解的主要差异在于去重方式和对合法子串的判断效率上。暴力枚举结合哈希判重简单直接但时间复杂度较高；Trie树通过建树过程判断子串是否重复；后缀数组和后缀自动机利用其特性优化了子串的统计过程。

### 所选的题解
- **作者：fuqingchen（5星）**
    - **关键亮点**：思路清晰，代码简洁。采用 $n^2$ 枚举每个子串，在枚举过程中实时判断子串是否合法，不合法则直接退出，减少无效枚举。同时使用哈希（`set` 结合自定义哈希函数）判断子串是否重复。
    - **重点代码核心实现思想**：外层循环枚举子串起点 $i$，内层循环枚举子串终点 $j$，在枚举过程中计算子串的哈希值并判断其是否合法（坏字母个数是否超过 $k$ ），合法且未出现过的子串哈希值加入 `set` 中。
```cpp
signed main() {
    cin >> s + 1 >> str + 1 >> q;
    for(int i = 1; i <= 26; ++i)
        a[i] = str[i] - '0';
    n = strlen(s + 1);
    for (int i = 1; i <= n; ++i) {
        ull x = 0;
        for (int j = i; j <= n; ++j) {
            x = x * B + (s[j] - 96);
            x %= mod;
            if (!a[s[j] - 96]) ++h[i];
            if (h[i] > q) break;
            if (st.find(x) == st.end()) st.insert(x);
        }
    }
    printf("%d", (int)st.size());
    return 0;
}
```
- **作者：muyang_233（4星）**
    - **关键亮点**：提供了 Trie 树的做法，通过枚举子串起点 $i$ 和终点 $j$，在 Trie 树上构建子串并判断是否重复。在构建过程中，实时统计坏字母个数，超过 $k$ 则停止枚举该起点的后续子串。
    - **重点代码核心实现思想**：外层循环枚举子串起点 $i$，内层循环枚举终点 $j$，判断当前字符是否为坏字符，若是则坏字符计数 `cnt` 增加。若 `cnt` 超过 $k$ 则跳出内层循环。否则在 Trie 树上尝试插入当前子串，若该子串对应的节点未被标记，则标记并计数。
```cpp
int main(){
    scanf("%s",ch+1);
    scanf("%s",sp+1);
    scanf("%d",&k);
    n=strlen(ch+1);
    for (int i=1;i<=n;i++){
        int now=0,cnt=0; 
        for (int j=i;j<=n;j++){
            if (sp[ch[j]-'a'+1]=='0'){ 
                ++cnt;
            }
            if (cnt>k){ 
                break;
            }
            if (!TRIE[now][ch[j]-'a'+1]){ 
                TRIE[now][ch[j]-'a'+1]=(++tot);
            }
            now=TRIE[now][ch[j]-'a'+1]; 
        }
    }
    printf("%d",tot); 
    return 0;
}
```
- **作者：天命之路（4星）**
    - **关键亮点**：提出了基于后缀数组（SA）的 $O(n\log{n})$ 解法。利用 good substring 的性质，确定以每个位置开头的最大 good substring 长度，再通过后缀数组和 height 数组去重，计算本质不同的好子串数量。
    - **重点代码核心实现思想**：先通过 `get_sa` 和 `get_hi` 函数求出后缀数组 `sa` 和 height 数组 `height`。利用前缀和数组 `sum` 快速判断子串中坏字母个数。通过递推计算出 `f[i]` 表示以 $i$ 开头的最大 good substring 长度。最后通过公式 `ans += f[i]` 累加所有可能的好子串长度，并减去重复部分 `ans -= min(lcp(sa[i],sa[i+1]),min(f[sa[i]],f[sa[i+1]]))` 得到最终答案。
```cpp
int main()
{
    scanf("%s",s+1);
    string tmp;
    cin>>tmp;
    for(int i = 0;i < 26;i++) good[i] = (tmp[i] - '0');
    scanf("%d",&k);
    n = std::strlen(s+1);
    get_sa(s,sa,n,256);
    get_hi(s,n);

    lg[0] = -1;
    for(int i = 1;i <= n;i++)
        lg[i] = lg[i >> 1] + 1,
        ST[i][0] = height[i];
    for(int j = 1;j <= 19;j++)
        for(int i = 1;i + (1 << j) - 1 <= n;i++)
            ST[i][j] = min(ST[i][j-1],ST[i+(1<<j-1)][j-1]);
    for(int i = 1;i <= n;i++) sum[i] = sum[i-1] + (!good[s[i] - 'a']);
    for(int i = 1;i <= n;i++)
    {
        f[i] = max(f[i-1] - 1,0);
        while(i + f[i] <= n && Qry(i,i+ f[i]) <= k) ++f[i];
    }
    int ans = 0;
    for(int i = 1;i <= n;i++) ans += f[i];
    for(int i = 1;i < n;i++) ans -= min(lcp(sa[i],sa[i+1]),min(f[sa[i]],f[sa[i+1]]));
    printf("%d\n",ans);
    return 0;
}
```

### 最优关键思路或技巧
在这些题解中，后缀数组（SA）和后缀自动机（SAM）的方法在处理大规模数据时具有更好的时间复杂度。后缀数组利用子串的有序性和 height 数组来高效地统计本质不同的子串，减少重复计算。后缀自动机则通过构建状态转移图，直接统计从根节点出发满足条件的路径数量，避免了重复子串的枚举。

### 可拓展之处
同类型题目通常围绕字符串子串的各种性质展开，如子串的最值、出现次数、不同子串的统计等。类似算法套路包括利用字符串数据结构（如后缀数组、后缀自动机、Trie 树）优化子串的处理过程，以及结合哈希等方法进行快速判重。

### 推荐洛谷题目
- [P2408 不同子串个数](https://www.luogu.com.cn/problem/P2408)：同样是关于统计字符串中不同子串的数量，可通过后缀数组或后缀自动机解决。
- [P3804 【模板】后缀自动机 (SAM)](https://www.luogu.com.cn/problem/P3804)：后缀自动机的模板题，可加深对后缀自动机原理和应用的理解。
- [P4051 [JSOI2007]字符加密](https://www.luogu.com.cn/problem/P4051)：涉及到对字符串的循环移位和子串相关操作，后缀数组可作为一种解题思路。

### 个人心得摘录与总结
无。 

---
处理用时：77.63秒