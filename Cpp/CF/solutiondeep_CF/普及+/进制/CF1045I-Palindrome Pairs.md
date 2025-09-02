# 题目信息

# Palindrome Pairs

## 题目描述

After learning a lot about space exploration, a little girl named Ana wants to change the subject.

Ana is a girl who loves palindromes (string that can be read the same backwards as forward). She has learned how to check for a given string whether it's a palindrome or not, but soon she grew tired of this problem, so she came up with a more interesting one and she needs your help to solve it:

You are given an array of strings which consist of only small letters of the alphabet. Your task is to find how many palindrome pairs are there in the array. A palindrome pair is a pair of strings such that the following condition holds: at least one permutation of the concatenation of the two strings is a palindrome. In other words, if you have two strings, let's say "aab" and "abcac", and you concatenate them into "aababcac", we have to check if there exists a permutation of this new string such that it is a palindrome (in this case there exists the permutation "aabccbaa").

Two pairs are considered different if the strings are located on different indices. The pair of strings with indices $ (i,j) $ is considered the same as the pair $ (j,i) $ .

## 说明/提示

The first example:

1. aa $ + $ bb $ \to $ abba.

The second example:

1. aab $ + $ abcac $ = $ aababcac $ \to $ aabccbaa
2. aab $ + $ aa $ = $ aabaa
3. abcac $ + $ aa $ = $ abcacaa $ \to $ aacbcaa
4. dffe $ + $ ed $ = $ dffeed $ \to $ fdeedf
5. dffe $ + $ aade $ = $ dffeaade $ \to $ adfaafde
6. ed $ + $ aade $ = $ edaade $ \to $ aeddea

## 样例 #1

### 输入

```
3
aa
bb
cd
```

### 输出

```
1
```

## 样例 #2

### 输入

```
6
aab
abcac
dffe
ed
aa
aade
```

### 输出

```
6
```

# AI分析结果

### 题目中文重写
# 回文对

## 题目描述
在学习了很多关于太空探索的知识后，一个名叫安娜的小女孩想换个话题。

安娜是一个喜欢回文串（正读和反读都相同的字符串）的女孩。她已经学会了如何检查给定的字符串是否是回文串，但很快她就对这个问题感到厌倦了，于是她想出了一个更有趣的问题，她需要你的帮助来解决这个问题：

给你一个字符串数组，这些字符串仅由小写字母组成。你的任务是找出数组中有多少个回文对。回文对是指这样一对字符串，满足以下条件：这两个字符串连接后的字符串的至少一种排列是回文串。换句话说，如果你有两个字符串，比如 "aab" 和 "abcac"，将它们连接成 "aababcac"，我们需要检查这个新字符串是否存在一种排列使其成为回文串（在这种情况下，存在排列 "aabccbaa"）。

如果两个字符串位于不同的索引位置，则认为这两个对是不同的。索引为 $(i,j)$ 的字符串对与 $(j,i)$ 对被视为相同。

## 说明/提示
第一个示例：
1. aa + bb → abba。

第二个示例：
1. aab + abcac = aababcac → aabccbaa
2. aab + aa = aabaa
3. abcac + aa = abcacaa → aacbcaa
4. dffe + ed = dffeed → fdeedf
5. dffe + aade = dffeaade → adfaafde
6. ed + aade = edaade → aeddea

## 样例 #1
### 输入
```
3
aa
bb
cd
```
### 输出
```
1
```

## 样例 #2
### 输入
```
6
aab
abcac
dffe
ed
aa
aade
```
### 输出
```
6
```

### 综合分析与结论
这些题解的核心思路都是利用回文串的性质，即一个字符串重排后能成为回文串的条件是出现奇数次的字符至多有一种。为了处理这个问题，大部分题解采用状态压缩的方法，将每个字符串中字符出现次数的奇偶性用一个 26 位的二进制数表示。

- **思路对比**：多数题解是遍历每个字符串，对于当前字符串，在已处理的字符串中查找能与之组成回文串的字符串数量。部分题解通过哈希表（如 `unordered_map` 或 `map`）记录二进制状态的出现次数，以快速查找匹配的状态；还有题解使用排序和二分查找（`upper_bound` 和 `lower_bound`）来统计匹配的数量。
- **算法要点**：状态压缩是关键，将每个字符串转换为 26 位二进制数，然后根据二进制数的性质判断两个字符串能否组成回文串。具体判断条件为两个二进制数相等或仅有一位不同。
- **解决难点**：主要难点在于如何高效地统计满足条件的字符串对数量。通过哈希表或排序二分查找可以将时间复杂度控制在可接受的范围内，避免了 $O(n^2)$ 的暴力枚举。

### 所选题解
- **yijan（5星）**
    - **关键亮点**：思路清晰，详细阐述了如何将字符串转换为二进制数，以及如何根据二进制数的性质判断回文对。代码实现简洁，使用 `unordered_map` 进行哈希计数，复杂度为 $O(nlogn)$。
    - **核心代码**：
```cpp
#pragma GCC optimize ("O3")
#include "iostream"
#include "algorithm"
#include "cstring"
#include "cstdio"
#include "unordered_map"
using namespace std;
typedef long long ll;
unordered_map<ll,ll> S;
#define MAXN 1000007
ll num[MAXN];
ll n;ll A[26],res;
int main(){
    cin >> n;getchar();
    for(ll i=0;i<n;++i){
        static char ch;
        memset(A,0,sizeof A);
        while(ch = getchar())
            if(ch!='\n')++A[ch-'a'];
            else break;
        for(ll j=0;j<26;++j)
            num[i] |= ((A[j]%2)<<j);
    }
    sort(num,num+n);
    for(ll i=0;i<n;++i){
        res += S[num[i]];
        for(ll j=0;j<26;++j)
            if((num[i]>>j)&1) res += S[num[i]^(1<<j)];
        ++S[num[i]];
    }
    cout << res;
}
```
- **mrsrz（4星）**
    - **关键亮点**：思路简洁明了，直接指出回文串的性质并进行状态压缩。代码简短，使用 `map` 进行状态计数，虽然时间复杂度多一个 $\log$，但实现简单。
    - **核心代码**：
```cpp
#include<map>
#include<cstdio>
#include<iostream>
std::map<int,int>b;
int a[100005],n;
char s[1000005];
long long ans=0;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;++i){
        scanf("%s",s);
        int&f=a[i];
        for(int t=0;s[t];++t)f^=1<<(s[t]-'a');
    }
    b[a[1]]=1;
    for(int i=2;i<=n;++i){
        ans+=b[a[i]];
        for(int j=0;j<26;++j)ans+=b[a[i]^(1<<j)];
        ++b[a[i]];
    }
    std::cout<<ans;
    return 0;
}
```
- **lzyqwq（4星）**
    - **关键亮点**：清晰地分析了问题，指出使用 26 位二进制数描述字符串状态的方法，并说明了状态的结合性。时间复杂度和空间复杂度分析准确。
    - **核心代码**：未给出完整代码，但思路清晰，关键思路为枚举 $j$，枚举可以和 $s_j$ 构成回文串的状态 $S$，开一个桶 $mp$ 维护当前每个状态有多少种，则 $S$ 与 $j$ 的贡献为 $mp_S$。

### 最优关键思路或技巧
- **状态压缩**：将每个字符串中字符出现次数的奇偶性用 26 位二进制数表示，大大减少了数据的存储和处理量。
- **哈希表**：使用哈希表（如 `unordered_map` 或 `map`）记录二进制状态的出现次数，能够快速查找匹配的状态，将时间复杂度从 $O(n^2)$ 降低到 $O(nlogn)$ 或接近线性复杂度。

### 可拓展之处
同类型题或类似算法套路：
- 处理字符串的组合问题，当问题涉及字符的出现次数和奇偶性时，可以考虑使用状态压缩的方法。
- 对于需要快速查找和计数的问题，可以使用哈希表来优化时间复杂度。

### 推荐洛谷题目
1. [P1311 选择客栈](https://www.luogu.com.cn/problem/P1311)：涉及字符串和计数问题，需要对数据进行合理的处理和统计。
2. [P1169 [ZJOI2007] 棋盘制作](https://www.luogu.com.cn/problem/P1169)：需要对棋盘上的元素进行状态分析和处理，与本题的状态压缩思路有一定的相似性。
3. [P2678 [NOIP2015 提高组] 跳石头](https://www.luogu.com.cn/problem/P2678)：涉及二分查找和状态判断，与本题中使用二分查找统计匹配数量的思路有一定关联。

### 个人心得摘录与总结
- **yijan**：提到这题难度被高估，实际大概是黄 +/绿 - 水平，强调代码实现有细节需要注意，但未具体说明细节内容。总结：在解决问题时，不要被题目难度标签吓倒，同时要注重代码实现的细节。

---
处理用时：51.01秒