# 题目信息

# Diverse Substring

## 题目描述

You are given a string $ s $ , consisting of $ n $ lowercase Latin letters.

A substring of string $ s $ is a continuous segment of letters from $ s $ . For example, "defor" is a substring of "codeforces" and "fors" is not.

The length of the substring is the number of letters in it.

Let's call some string of length $ n $ diverse if and only if there is no letter to appear strictly more than $ \frac n 2 $ times. For example, strings "abc" and "iltlml" are diverse and strings "aab" and "zz" are not.

Your task is to find any diverse substring of string $ s $ or report that there is none. Note that it is not required to maximize or minimize the length of the resulting substring.

## 说明/提示

The first example has lots of correct answers.

Please, restrain yourself from asking if some specific answer is correct for some specific test or not, these questions always lead to "No comments" answer.

## 样例 #1

### 输入

```
10
codeforces
```

### 输出

```
YES
code
```

## 样例 #2

### 输入

```
5
aaaaa
```

### 输出

```
NO
```

# AI分析结果

### 题目翻译
## 多样子串

### 题目描述
给定一个由 $n$ 个小写拉丁字母组成的字符串 $s$。

字符串 $s$ 的子串是 $s$ 中连续的一段字母。例如，“defor” 是 “codeforces” 的子串，而 “fors” 不是。

子串的长度是其中字母的数量。

如果一个长度为 $n$ 的字符串中没有任何一个字母出现的次数严格超过 $\frac{n}{2}$ 次，那么我们称这个字符串是多样的。例如，字符串 “abc” 和 “iltlml” 是多样的，而字符串 “aab” 和 “zz” 不是。

你的任务是找出字符串 $s$ 的任意一个多样子串，或者报告不存在这样的子串。注意，不需要最大化或最小化结果子串的长度。

### 说明/提示
第一个样例有很多正确答案。

请不要询问某个特定的答案对于某个特定的测试用例是否正确，这类问题的回答总是 “不予置评”。

### 样例 #1
#### 输入
```
10
codeforces
```
#### 输出
```
YES
code
```

### 样例 #2
#### 输入
```
5
aaaaa
```
#### 输出
```
NO
```

### 综合分析与结论
这些题解主要围绕寻找字符串中满足“任意字母出现次数不超过子串长度一半”的子串展开。思路可分为两类：
- **简单思路**：多数题解发现只需找到相邻且不同的两个字符，就能满足条件，时间复杂度为 $O(n)$。
- **暴力枚举思路**：通过枚举子串的两个端点，统计每个字母出现的次数，判断是否满足条件，时间复杂度为 $O(n^2)$。

### 所选题解
- **Annihilation_y（5星）**
    - **关键亮点**：思路清晰，代码简洁，直接使用万能头文件，避免使用 `flag` 变量，直接结束程序，提高代码效率。
    - **核心代码**：
```c++
#include <bits/stdc++.h>
using namespace std;
string s;
int len;
int main()
{
    scanf("%d",&len);
    cin>>s;
    s=" "+s;
    for (int i=2;i<=len;i++)
    {
        if(s[i]!=s[i-1])
        {
            printf("YES\n");
            cout<<s[i-1]<<s[i];
            return 0;
        }
    }
    printf("NO");
    return 0;
} 
```
- **decoqwq（4星）**
    - **关键亮点**：思路简单直接，代码简洁易懂。
    - **核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
char s[1010];
int n;
int main()
{
    cin>>n>>s;
    for(int i=1;i<n;i++)
    {
        if(s[i]!=s[i-1])
        {
            printf("YES\n%c%c",s[i-1],s[i]);
            return 0;
        }
    }
    cout<<"NO";
}
```
- **OoXiao_QioO（4星）**
    - **关键亮点**：思路详细，对长度为1和2的子串进行了分析，代码注释清晰。
    - **核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n,i;
    char s[1001];
    scanf("%d %s",&n,s);
    for (i=1;i<n;i++)
    {
        if (s[i]!= s[i-1])
        {
            printf("YES\n");
            printf("%c%c\n",s[i-1], s[i]);
            return 0;
        }
    }
    printf("NO\n");
    return 0;
}
```

### 最优关键思路或技巧
本题最优思路是通过观察发现，只要找到相邻且不同的两个字符，就能满足多样子串的条件，从而将时间复杂度从 $O(n^2)$ 优化到 $O(n)$。

### 拓展思路
同类型题目可能会改变子串的判断条件，例如要求子串中每个字母出现的次数不超过某个固定值，或者要求子串的长度在某个范围内等。解题时可以先分析简单情况，找到满足条件的最短子串，再进行遍历查找。

### 洛谷相似题目推荐
1. [P1308 统计单词数](https://www.luogu.com.cn/problem/P1308)
2. [P1598 垂直柱状图](https://www.luogu.com.cn/problem/P1598)
3. [P1957 口算练习题](https://www.luogu.com.cn/problem/P1957)

### 个人心得摘录与总结
- **happybob**：使用 `map` 统计字符出现数量时，要注意判断条件是“小于等于”子串长度的一半。总结：在处理这类计数和比较的问题时，要仔细理解题目条件，避免因边界条件判断错误导致出错。

---
处理用时：27.16秒