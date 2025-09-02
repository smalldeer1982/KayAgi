# 题目信息

# Canine poetry

## 题目描述

After his wife's tragic death, Eurydice, Orpheus descended to the realm of death to see her. Reaching its gates was uneasy, but passing through them proved to be even more challenging. Mostly because of Cerberus, the three-headed hound of Hades.

Orpheus, a famous poet, and musician plans to calm Cerberus with his poetry and safely walk past him. He created a very peculiar poem for Cerberus. It consists only of lowercase English letters.

We call a poem's substring a palindrome if and only if it reads the same backwards and forwards. A string $ a $ is a substring of a string $ b $ if $ a $ can be obtained from $ b $ by deleting several (possibly zero or all) characters from the beginning and several (possibly zero or all) characters from the end.

Unfortunately, Cerberus dislikes palindromes of length greater than $ 1 $ . For example in the poem abaa the hound of Hades wouldn't like substrings aba and aa.

Orpheus can only calm Cerberus if the hound likes his poetry. That's why he wants to change his poem so that it does not contain any palindrome substrings of length greater than $ 1 $ .

Orpheus can modify the poem by replacing a letter at any position with any lowercase English letter. He can use this operation arbitrarily many times (possibly zero). Since there can be many palindromes in his poem, he may have to make some corrections. But how many, exactly? Given the poem, determine the minimal number of letters that have to be changed so that the poem does not contain any palindromes of length greater than $ 1 $ .

## 说明/提示

In the first test case, we can replace the third character with c and obtain a palindrome-less poem bacba.

In the second test case, we can replace the third character with d and obtain a palindrome-less poem abdac.

In the third test case, the initial poem already doesn't contain any palindromes, so Orpheus doesn't need to change anything there.

## 样例 #1

### 输入

```
7
babba
abaac
codeforces
zeroorez
abcdcba
bbbbbbb
a```

### 输出

```
1
1
0
1
1
4
0```

# AI分析结果

【题目内容】
# 犬类诗歌

## 题目描述

在他的妻子欧律狄刻悲剧性去世后，俄耳甫斯下到冥界去看她。到达冥界的大门并不容易，但通过它们却更加困难。主要是因为冥界的三头犬刻耳柏洛斯。

俄耳甫斯是一位著名的诗人和音乐家，计划用他的诗歌安抚刻耳柏洛斯，并安全地走过它。他为刻耳柏洛斯创作了一首非常独特的诗。它只由小写英文字母组成。

我们称诗的子串为回文串，当且仅当它正读和反读都一样。字符串 $a$ 是字符串 $b$ 的子串，如果 $a$ 可以通过从 $b$ 的开头删除若干（可能为零或全部）字符，并从 $b$ 的结尾删除若干（可能为零或全部）字符得到。

不幸的是，刻耳柏洛斯不喜欢长度大于 $1$ 的回文串。例如，在诗 `abaa` 中，冥界的三头犬不会喜欢子串 `aba` 和 `aa`。

俄耳甫斯只有在刻耳柏洛斯喜欢他的诗时才能安抚它。这就是为什么他想改变他的诗，使其不包含任何长度大于 $1$ 的回文子串。

俄耳甫斯可以通过将任意位置的字母替换为任何小写英文字母来修改诗。他可以任意多次使用此操作（可能为零）。由于他的诗中可能有许多回文串，他可能需要进行一些修改。但具体需要多少次呢？给定这首诗，确定需要更改的最小字母数，以使诗中不包含任何长度大于 $1$ 的回文子串。

## 说明/提示

在第一个测试用例中，我们可以将第三个字符替换为 `c`，得到一个没有回文的诗 `bacba`。

在第二个测试用例中，我们可以将第三个字符替换为 `d`，得到一个没有回文的诗 `abdac`。

在第三个测试用例中，初始诗已经没有任何回文，因此俄耳甫斯不需要进行任何更改。

## 样例 #1

### 输入

```
7
babba
abaac
codeforces
zeroorez
abcdcba
bbbbbbb
a```

### 输出

```
1
1
0
1
1
4
0```

【算法分类】贪心

【题解分析与结论】
该题的核心思路是通过贪心策略，破坏所有长度为2和3的回文子串，从而确保整个字符串中不存在任何长度大于1的回文子串。所有题解都基于这一思路，但实现细节有所不同。主要难点在于如何高效地检测并破坏回文子串，同时避免重复修改。

【评分较高的题解】

1. **作者：苏22 (赞：16)**  
   - **星级：4.5**  
   - **关键亮点**：代码简洁，思路清晰，通过标记数组避免重复修改，直接枚举长度为2和3的回文子串，修改次数统计准确。  
   - **核心代码**：
     ```cpp
     for(int j=0;j<len-1;j++) { 
         if(s[j]==s[j+1]&&tmp[j]==1) {  
             tmp[j+1]=0; 
             ans++; 
         }
         if(s[j]==s[j+2]&&tmp[j]==1) {  
             tmp[j+2]=0; 
             ans++; 
         }
     }
     ```

2. **作者：Locklink (赞：7)**  
   - **星级：4**  
   - **关键亮点**：思路与苏22类似，代码简洁，通过标记数组避免重复修改，直接破坏长度为2和3的回文子串。  
   - **核心代码**：
     ```cpp
     for(int i=0;i<n-1;i++) {
         if(s[i]==s[i+2]&&!v[i]) {
             ans++;
             v[i+2]=true;
         }
         if(s[i]==s[i+1]&&!v[i]) {
             ans++;
             v[i+1]=true;
         }
     }
     ```

3. **作者：HoshizoraZ (赞：5)**  
   - **星级：4**  
   - **关键亮点**：详细解释了如何通过修改字符破坏回文子串，并提供了修改字符时的注意事项，确保修改后不会生成新的回文子串。  
   - **核心代码**：
     ```cpp
     for(int i = 2; i <= n; i++) {
         if(s[i] == s[i - 1] && i > 1) {
             for(char j = 'a'; j <= 'z'; j++)
                 if(j != s[i + 1] && j != s[i - 1] && j != s[i - 2] && j != s[i + 2]) {
                     s[i] = j;
                     break;
                 }
             ans++;
         }
         if(s[i] == s[i - 2] && i > 2) {
             for(char j = 'a'; j <= 'z'; j++)
                 if(j != s[i] && j != s[i - 1] && j != s[i + 1] && j != s[i + 2]) {
                     s[i] = j;
                     break;
                 }
             ans++;
         }
     }
     ```

【最优关键思路】
通过贪心策略，破坏所有长度为2和3的回文子串，确保整个字符串中不存在任何长度大于1的回文子串。使用标记数组避免重复修改，确保修改次数最小化。

【可拓展之处】
类似的问题可以通过贪心策略解决，尤其是在需要破坏某种特定结构（如回文、对称等）时，贪心算法往往能提供高效的解决方案。

【推荐题目】
1. [P1217 [USACO1.5]回文质数 Prime Palindromes](https://www.luogu.com.cn/problem/P1217)
2. [P1435 [IOI2000]回文字串](https://www.luogu.com.cn/problem/P1435)
3. [P1466 [USACO2.3]集合 Subset Sums](https://www.luogu.com.cn/problem/P1466)

---
处理用时：42.52秒