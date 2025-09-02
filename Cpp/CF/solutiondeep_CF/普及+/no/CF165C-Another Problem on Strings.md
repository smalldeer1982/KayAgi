# 题目信息

# Another Problem on Strings

## 题目描述

A string is binary, if it consists only of characters "0" and "1".

String $ v $ is a substring of string $ w $ if it has a non-zero length and can be read starting from some position in string $ w $ . For example, string "010" has six substrings: "0", "1", "0", "01", "10", "010". Two substrings are considered different if their positions of occurrence are different. So, if some string occurs multiple times, we should consider it the number of times it occurs.

You are given a binary string $ s $ . Your task is to find the number of its substrings, containing exactly $ k $ characters "1".

## 说明/提示

In the first sample the sought substrings are: "1", "1", "10", "01", "10", "010".

In the second sample the sought substrings are: "101", "0101", "1010", "01010".

## 样例 #1

### 输入

```
1
1010
```

### 输出

```
6
```

## 样例 #2

### 输入

```
2
01010
```

### 输出

```
4
```

## 样例 #3

### 输入

```
100
01010
```

### 输出

```
0
```

# AI分析结果

### 题目内容
# 字符串的另一个问题

## 题目描述
如果一个字符串仅由字符“0”和“1”组成，那么它就是二进制字符串。
如果字符串 $v$ 长度非零且能从字符串 $w$ 的某个位置开始读出，那么 $v$ 就是 $w$ 的子串。例如，字符串“010”有六个子串：“0”、“1”、“0”、“01”、“10”、“010”。如果两个子串出现的位置不同，就认为它们是不同的。所以，如果某个字符串多次出现，我们应按其出现次数来计算。
给定一个二进制字符串 $s$ ，你的任务是找出其中恰好包含 $k$ 个字符“1”的子串的数量。

## 说明/提示
在第一个样例中，所求的子串为：“1”、“1”、“10”、“01”、“10”、“010”。
在第二个样例中，所求的子串为：“101”、“0101”、“1010”、“01010”。

## 样例 #1
### 输入
```
1
1010
```
### 输出
```
6
```

## 样例 #2
### 输入
```
2
01010
```
### 输出
```
4
```

## 样例 #3
### 输入
```
100
01010
```
### 输出
```
0
```

### 算法分类
字符串

### 综合分析与结论
这些题解主要围绕如何高效统计包含特定数量“1”的子串展开。Mine_King通过定义数组记录每个“1”右边连续“0”的个数，扫描字符串并结合乘法原理的变形来计算答案；_byta提出类似dp的思路，通过扫描字符串更新dp数组来统计子串个数；LRL65同样利用数组记录每个“1”后“0”的个数，从第k个“1”开始累加答案。GaryH提出双指针优化暴力枚举的思路，oimaster提出递推思路但未给出具体代码，Awa486按题意模拟实现。各题解思路各有特点，Mine_King、_byta和LRL65的题解相对更清晰简洁，实现较为直接。

### 所选的题解
- **作者：Mine_King (5星)**
    - **关键亮点**：巧妙利用乘法原理变形，将复杂的区间扩展计数转化为简单加法，通过数组记录“1”右边连续“0”的个数优化计算，代码简洁高效。
    ```cpp
    #include<cstdio>
    #include<cstring>
    #include<iostream>
    #include<algorithm>
    using namespace std;
    int k,f[1000005],onenumber;
    long long ans;
    int main()
    {
        scanf("%d",&k);
        memset(f,-1,sizeof(f));
        f[0]=0;
        for(int x;scanf("%1d",&x)!=EOF;)
        {
            onenumber+=x;
            if(onenumber>=k) ans+=f[onenumber-k]+1;
            f[onenumber]++;
        }
        cout<<ans<<'\n';
        return 0;
    }
    ```
    - **核心实现思想**：扫描字符串，遇到“1”时更新“1”的计数onenumber，当onenumber≥k时，利用数组f[onenumber - k]记录的左边连续“0”的个数，累加到答案ans中，同时更新f[onenumber]。
- **作者：_byta (4星)**
    - **关键亮点**：提出类似dp的思路，通过扫描字符串，简洁地更新dp数组来统计包含不同数量“1”的子串个数，从而得到包含k个“1”的子串个数。
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;
    long long k, ans, t, dp[1000002];
    string s;
    int main()
    {
        dp[0] = 1;
        cin >> k >> s;
        for(int i = 0 ; i < s.size() ; i++)
        {
            if(s[i] == '1') t ++;
            if(t >= k) ans += dp[t-k];
            dp[t] ++;
        }
        cout << ans;
    }
    ```
    - **核心实现思想**：扫描字符串，遇到“1”时t自增，当t≥k时，将dp[t - k]累加到答案ans中，同时更新dp[t]，dp数组记录了包含对应数量“1”的子串个数。
- **作者：LRL65 (4星)**
    - **关键亮点**：通过数组s0记录每个“1”后“0”的个数，初始化s0[0]=1，从第k个“1”开始累加答案，思路清晰，实现简单。
    ```cpp
    #include<bits/stdc++.h>
    using namespace std;
    #define MAXN 1000005
    int k,s0[MAXN]={1},s1=0;
    char s;
    long long ans=0;
    int main(){
        cin>>k;
        while(cin>>s) {
            if(s=='1')s1++;
            if(s1>=k)ans+=s0[s1-k];
            s0[s1]++;
        }
        cout<<ans<<endl;
    }
    ```
    - **核心实现思想**：扫描字符串，遇到“1”时s1自增，当s1≥k时，将s0[s1 - k]累加到答案ans中，同时更新s0[s1]。

### 最优关键思路或技巧
利用数组记录每个“1”右边（或后）连续“0”的个数，在扫描字符串过程中，结合当前“1”的计数，通过简单的加法操作高效统计包含特定数量“1”的子串个数，避免了暴力枚举的高时间复杂度。

### 拓展
同类型题可考察不同条件下子串的统计，如包含特定字符组合、满足某种长度限制等。类似算法套路为利用数组记录关键信息（如字符位置、连续字符个数等），通过扫描字符串结合这些信息进行高效计算。

### 推荐洛谷题目
- [P1308 统计单词数](https://www.luogu.com.cn/problem/P1308)：统计字符串中特定单词出现次数，涉及字符串查找与统计。
- [P1313 计算系数](https://www.luogu.com.cn/problem/P1313)：根据二项式定理计算多项式系数，与本题类似在于通过一定规则统计数量。
- [P1059 [NOIP2006 普及组] 明明的随机数](https://www.luogu.com.cn/problem/P1059)：对输入的随机数去重并排序后输出，可类比本题对字符串子串的处理与统计。 

---
处理用时：65.31秒