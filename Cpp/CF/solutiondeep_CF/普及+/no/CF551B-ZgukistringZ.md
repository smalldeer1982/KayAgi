# 题目信息

# ZgukistringZ

## 题目描述

Professor GukiZ doesn't accept string as they are. He likes to swap some letters in string to obtain a new one.

GukiZ has strings $ a $ , $ b $ , and $ c $ . He wants to obtain string $ k $ by swapping some letters in $ a $ , so that $ k $ should contain as many non-overlapping substrings equal either to $ b $ or $ c $ as possible. Substring of string $ x $ is a string formed by consecutive segment of characters from $ x $ . Two substrings of string $ x $ overlap if there is position $ i $ in string $ x $ occupied by both of them.

GukiZ was disappointed because none of his students managed to solve the problem. Can you help them and find one of possible strings $ k $ ?

## 说明/提示

In the third sample, this optimal solutions has three non-overlaping substrings equal to either $ b $ or $ c $ on positions $ 1–2 $ ( $ ab $ ), $ 3–4 $ ( $ ab $ ), $ 5–7 $ ( $ aca $ ). In this sample, there exist many other optimal solutions, one of them would be $ acaababbcc $ .

## 样例 #1

### 输入

```
aaa
a
b
```

### 输出

```
aaa```

## 样例 #2

### 输入

```
pozdravstaklenidodiri
niste
dobri
```

### 输出

```
nisteaadddiiklooprrvz```

## 样例 #3

### 输入

```
abbbaaccca
ab
aca
```

### 输出

```
ababacabcc```

# AI分析结果

### 题目内容
# ZgukistringZ

## 题目描述
GukiZ教授并不接受字符串原本的样子。他喜欢通过交换字符串中的一些字母来得到一个新的字符串。

GukiZ有字符串 $a$、$b$ 和 $c$ 。他想通过交换 $a$ 中的一些字母来得到字符串 $k$，使得 $k$ 包含尽可能多的不重叠子串，这些子串要么等于 $b$ ，要么等于 $c$ 。字符串 $x$ 的子串是由 $x$ 中连续的字符段组成的字符串。字符串 $x$ 的两个子串如果在字符串 $x$ 中有一个位置 $i$ 同时被它们占据，那么这两个子串就是重叠的。

GukiZ很失望，因为他的学生中没有一个人能解决这个问题。你能帮助他们并找到一个可能的字符串 $k$ 吗？

## 说明/提示
在第三个样例中，这个最优解在位置 $1 - 2$（$ab$）、$3 - 4$（$ab$）、$5 - 7$（$aca$）有三个不重叠的子串，它们要么等于 $b$ ，要么等于 $c$ 。在这个样例中，还有许多其他最优解，其中一个是 $acaababbcc$ 。

## 样例 #1
### 输入
```
aaa
a
b
```
### 输出
```
aaa```

## 样例 #2
### 输入
```
pozdravstaklenidodiri
niste
dobri
```
### 输出
```
nisteaadddiiklooprrvz```

## 样例 #3
### 输入
```
abbbaaccca
ab
aca
```
### 输出
```
ababacabcc```

### 算法分类
枚举

### 综合分析与结论
该题解首先尝试贪心算法，但未通过测试数据。正解思路是通过枚举数量较多的子串（$b$ 或 $c$）的个数，再计算剩余字符能组成另一个子串的数量，从而找到最多非重叠子串的组合方式。其要点在于通过统计字符数量来确定可组成子串的个数，并通过枚举和更新答案找到最优组合。解决难点在于合理的枚举策略，优先枚举数量多的子串以避免特殊情况（如 $ans1 = 0, ans2 \neq 0$ 时枚举 $b$ 会出错）。

### 所选的题解
 - **星级**：3星
 - **关键亮点**：通过先统计各字符数量，再合理枚举子串数量来寻找最优解，逻辑较为清晰。
 - **个人心得**：作者尝试贪心算法失败，发现直接贪心（先满足所有 $b$ 或先满足所有 $c$）无法通过所有测试数据，从而转向正解思路。

### 重点代码核心实现思想
通过数组 `mp1`、`mp2`、`mp3` 分别统计字符串 $a$、$b$、$c$ 中各字符出现的次数，进而计算出能组成 $b$ 和 $c$ 的最大数量 `ans1` 和 `ans2`。根据 `ans1` 和 `ans2` 的大小关系，枚举数量多的子串个数，在每次枚举中，更新剩余字符数量，再计算剩余字符能组成另一个子串的数量，通过比较更新最大子串总数 `ans` 以及对应的 `tot1` 和 `tot2`（分别表示 $b$ 和 $c$ 的个数）。最后输出由 `tot1` 个 $b$、`tot2` 个 $c$ 以及剩余字符组成的字符串。

### 核心代码片段
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
string a,b,c;
int ans1=1e9,ans2=1e9,ans,tot1,tot2,mp1[26],mp2[26],mp3[26],cnt[26];
int main(){
    cin>>a>>b>>c;
    int n1=a.length(),n2=b.length(),n3=c.length();
    for(int i=0;i<n1;i++)mp1[a[i]-'a']++;
    for(int i=0;i<n2;i++)mp2[b[i]-'a']++;
    for(int i=0;i<n3;i++)mp3[c[i]-'a']++;
    for(int i=0;i<26;i++){
        if(mp2[i])ans1=min(ans1,mp1[i]/mp2[i]);
        if(mp3[i])ans2=min(ans2,mp1[i]/mp3[i]);
    }
    if(ans1>ans2){
        for(int i=1;i<=ans1;i++){
            int res=1e9;
            for(int j=0;j<26;j++)cnt[j]=mp1[j];
            for(int j=0;j<26;j++)cnt[j]-=i*mp2[j];
            for(int j=0;j<26;j++)
                if(mp3[j])res=min(res,cnt[j]/mp3[j]);
            if(i+res>ans){
                ans=i+res;
                tot1=i,tot2=res;
            }
        }
    }
    else{
        for(int i=1;i<=ans2;i++){
            int res=1e9;
            for(int j=0;j<26;j++)cnt[j]=mp1[j];
            for(int j=0;j<26;j++)cnt[j]-=i*mp3[j];
            for(int j=0;j<26;j++)
                if(mp2[j])res=min(res,cnt[j]/mp2[j]);
            if(i+res>ans){
                ans=i+res;
                tot2=i,tot1=res;
            }
        }
    }
    for(int i=0;i<26;i++){
        if(mp2[i])mp1[i]-=tot1*mp2[i];
        if(mp3[i])mp1[i]-=tot2*mp3[i];
    }
    for(int i=1;i<=tot1;i++)cout<<b;
    for(int i=1;i<=tot2;i++)cout<<c;
    for(int i=0;i<26;i++)
        for(int j=1;j<=mp1[i];j++)cout<<char('a'+i);
    return 0;
}
```

### 通用建议与扩展思路
对于此类字符串组合问题，在尝试贪心策略失败后，可考虑枚举等暴力策略，并通过合理的优化（如本题中优先枚举数量多的子串）来降低时间复杂度。可以拓展到更多子串的情况，或者对子串匹配规则进行更复杂的设定，解题思路依然可以从统计字符、枚举组合等方向入手。

### 洛谷相似题目推荐
 - [P1036 选数](https://www.luogu.com.cn/problem/P1036)
 - [P1157 组合的输出](https://www.luogu.com.cn/problem/P1157)
 - [P1219 八皇后](https://www.luogu.com.cn/problem/P1219) 

---
处理用时：60.30秒