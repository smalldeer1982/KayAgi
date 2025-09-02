# 题目信息

# Many Equal Substrings

## 题目描述

You are given a string $ t $ consisting of $ n $ lowercase Latin letters and an integer number $ k $ .

Let's define a substring of some string $ s $ with indices from $ l $ to $ r $ as $ s[l \dots r] $ .

Your task is to construct such string $ s $ of minimum possible length that there are exactly $ k $ positions $ i $ such that $ s[i \dots i + n - 1] = t $ . In other words, your task is to construct such string $ s $ of minimum possible length that there are exactly $ k $ substrings of $ s $ equal to $ t $ .

It is guaranteed that the answer is always unique.

## 样例 #1

### 输入

```
3 4
aba
```

### 输出

```
ababababa
```

## 样例 #2

### 输入

```
3 2
cat
```

### 输出

```
catcat
```

# AI分析结果

### 题目中文重写
# 多个相同子串

## 题目描述
给定一个由 $n$ 个小写拉丁字母组成的字符串 $t$ 和一个整数 $k$。

我们将字符串 $s$ 中从索引 $l$ 到 $r$ 的子串定义为 $s[l \dots r]$。

你的任务是构造一个长度尽可能小的字符串 $s$，使得恰好有 $k$ 个位置 $i$ 满足 $s[i \dots i + n - 1] = t$。换句话说，你的任务是构造一个长度尽可能小的字符串 $s$，使得 $s$ 中恰好有 $k$ 个子串等于 $t$。

保证答案总是唯一的。

## 样例 #1
### 输入
```
3 4
aba
```
### 输出
```
ababababa
```

## 样例 #2
### 输入
```
3 2
cat
```
### 输出
```
catcat
```

### 综合分析与结论
这些题解主要围绕如何构造一个长度最小的字符串 $s$，使其包含 $k$ 个与给定字符串 $t$ 相同的子串。大部分题解使用了 KMP 算法来找出字符串 $t$ 的最长相同前后缀，以此来减少拼接时的重复部分，从而使构造的字符串 $s$ 长度最小；也有部分题解使用暴力匹配或哈希的方法。

### 各题解要点提炼、难点对比及评分
|作者|思路|算法要点|解决难点|评分|
| ---- | ---- | ---- | ---- | ---- |
|Acapplella|利用 KMP 算法的 next 数组，找到字符串 $t$ 的最长相同前后缀，先输出完整的 $t$，再循环 $k - 1$ 次输出 $t$ 中除去最长相同前缀后的部分|KMP 算法求 next 数组|理解 next 数组含义及如何利用其减少字符串拼接长度|4星|
|CreeperK|用 KMP 算法求最长前缀和后缀相同的长度，输出时跳过重叠部分|KMP 算法求最长相同前后缀|确定输出起始位置|4星|
|Yaha|使用 KMP 算法，让字符串 $t$ 的前缀在构造新串时同时作为下一个串的前缀，减少重复|KMP 算法找最长相同前后缀|理解如何利用重复子串构造新串|4星|
|sc84bbs|使用暴力匹配的方法，找到字符串 $t$ 中最多能省略的位数，然后输出|双重循环匹配字符串|确定省略位数|2星|
|zheysq_147|用 KMP 算法找到字符串 $t$ 的最长相同前后缀，先输出完整的 $t$，再输出 $k - 1$ 个残缺字符串|KMP 算法求 next 数组|理解 next 数组与字符串拼接的关系|3星|
|codesonic|用 KMP 算法求出前缀与后缀相同的长度，略去重叠部分输出|KMP 算法求最长相同前后缀|确定输出范围|3星|
|Fraction|按照 KMP 初始化步骤求出最长相同前后缀，先输出完整字符串，再循环输出剩余部分|KMP 算法求最长相同前后缀|KMP 算法的实现|3星|
|让风忽悠你|用 KMP 算法找到首尾的最长公共部分，先输出前 $k - 1$ 次部分，最后输出完整字符串|KMP 算法求最长相同前后缀|输出顺序和范围的确定|3星|
|苏打青柠水|使用 Java 的哈希方法计算字符串的哈希值，找到前缀和后缀最大的重叠部分|哈希算法计算字符串哈希值|哈希算法的应用和边界判断|2星|
|TechZ|用 KMP 算法求出最长相同前后缀，先输出整个字符串，再循环 $k - 1$ 次从特定位置开始输出|KMP 算法求最长相同前后缀|确定输出起始位置|3星|
|oneman233|求出 KMP 的前缀数组，每次从最后一位的前缀值位置往后输出|KMP 算法求前缀数组|理解前缀数组的使用|3星|
|Leap_Frog|求出字符串的前缀数组，根据前缀数组输出结果|求前缀数组|前缀数组的应用|2星|
|ljk_Elaina|暴力扫描字符串，记录最长相同子串的长度，重复 $k - 1$ 遍，最后输出原字符串|双重循环暴力匹配|确定最长相同子串长度|2星|

### 所选题解
- **Acapplella（4星）**
    - 关键亮点：思路清晰，代码简洁，对 KMP 算法的 next 数组应用解释明确。
    - 重点代码：
```cpp
#include<iostream>
using namespace std;
int n, k;
char a[53];
int ne[53];
int main()
{
    cin >> n >> k;
    cin >> a + 1;
    for (int i = 2, j = 0;i <= n;i++)
    {
        while (a[j + 1]!= a[i] && j)   j = ne[j];
        if (a[j + 1] == a[i])     j++;
        ne[i] = j;
    }
    for (int i = 1;i <= n;i++)
        cout << a[i];
    int ans = k - 1;
    while (ans--)
        cout << a+ne[n]+1;
    return 0;
}
```
    - 核心实现思想：先使用 KMP 算法求出 next 数组（这里用 ne 表示），然后输出完整的字符串 $t$，最后循环 $k - 1$ 次输出 $t$ 中除去最长相同前缀后的部分。

- **CreeperK（4星）**
    - 关键亮点：对输出部分的解释结合样例，易于理解。
    - 重点代码：
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int f[60],n,k;
char s[60];
void Cal_Next(){
    f[0]=f[1]=0;
    for(int i=1;i<n;i++){
        int j=f[i];
        while(j>0 && s[i]!=s[j])j=f[j];
        if(s[i]==s[j])f[i+1]=j+1;
        else f[i+1]=0;
    }
}
int main(){
    scanf("%d%d",&n,&k);
    scanf("%s",s);
    Cal_Next();
    printf("%s",s);
    for(int i=1;i<k;i++){
        for(int j=f[n];j<n;j++)printf("%c",s[j]);
    }
}
```
    - 核心实现思想：通过 `Cal_Next` 函数求出最长相同前后缀的长度，先输出完整的字符串 $t$，再循环 $k - 1$ 次从最长相同前后缀的下一个位置开始输出。

- **Yaha（4星）**
    - 关键亮点：通过具体例子解释如何利用重复子串构造新串，思路清晰。
    - 重点代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
char a[51];
int kmp[51],n,k;
int main(){
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)
        cin>>a[i];
    int i=2,j=0;
    while(i<=n)
    {
        while(j&&a[i]!=a[j+1]) j=kmp[j];
        if(a[i]==a[j+1]) kmp[i++]=++j;
        else kmp[i++]=j;
    }
    for(int i=1;i<=n;i++)
        cout<<a[i];
    for(int i=2;i<=k;i++)
        for(int j=kmp[n]+1;j<=n;j++)
            cout<<a[j];
    return 0;
}
```
    - 核心实现思想：使用 KMP 算法求出最长相同前后缀的长度，先输出完整的字符串 $t$，再循环 $k - 1$ 次从最长相同前后缀的下一个位置开始输出。

### 最优关键思路或技巧
使用 KMP 算法求出字符串 $t$ 的最长相同前后缀，在拼接 $k$ 个字符串 $t$ 时，利用这个最长相同前后缀减少重复部分，从而使构造的字符串 $s$ 长度最小。

### 拓展思路
同类型题或类似算法套路：
- 字符串匹配问题，如求一个字符串在另一个字符串中出现的次数。
- 字符串拼接问题，要求拼接后的字符串长度最小，可利用最长相同前后缀减少重复。

### 洛谷推荐题目
- P3375 【模板】KMP字符串匹配
- P5410 【模板】扩展 KMP（Z 函数）
- P1368 【模板】最小表示法

### 个人心得摘录与总结
- zheysq_147：做完此题对 $next$ 数组的意义理解更深刻，认识到暴力做法会超时，强调了学习 KMP 算法的重要性。
- Acapplella：第一次写题解，提醒注意 $next$ 数组名可能与库函数重名的问题。 

---
处理用时：49.68秒