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

### 题目中文重写
## 多样化子串

### 题目描述
给定一个由 $n$ 个小写拉丁字母组成的字符串 $s$。

字符串 $s$ 的子串是 $s$ 中连续的一段字母。例如，“defor” 是 “codeforces” 的子串，而 “fors” 不是。

子串的长度是其中字母的数量。

如果一个长度为 $n$ 的字符串中没有任何一个字母出现的次数严格超过 $\frac{n}{2}$ 次，那么我们称这个字符串是多样化的。例如，字符串 “abc” 和 “iltlml” 是多样化的，而字符串 “aab” 和 “zz” 不是。

你的任务是找出字符串 $s$ 的任意一个多样化子串，或者报告不存在这样的子串。注意，不需要最大化或最小化结果子串的长度。

### 说明/提示
第一个样例有很多正确答案。

请不要询问某个特定的答案对于某个特定的测试用例是否正确，这类问题的回答通常是 “不予置评”。

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

### 题解综合分析与结论
这些题解主要围绕寻找字符串中满足“任意字母出现次数不超过子串长度一半”的子串展开。思路可分为两类：
- **简单思路**：多数题解发现只需找到相邻且不同的两个字符，就能满足要求，时间复杂度为 $O(n)$。
- **暴力思路**：通过 $\Theta(N^2)$ 的复杂度枚举子串的两个端点，统计每个字母出现次数来判断是否满足条件。

### 高评分题解
- **Annihilation_y（5星）**
    - **关键亮点**：思路清晰简洁，代码使用万能头文件，简化输入输出，直接判断相邻字符，不使用标记变量，代码可读性高。
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
    - **关键亮点**：思路清晰，代码简洁易懂，直接遍历字符串判断相邻字符。
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
    - **关键亮点**：思路详细，从子串长度分析入手，逐步推导得出结论，代码注释清晰。
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

### 最优关键思路与技巧
- **思维方式**：从简单情况入手，考虑子串长度，发现长度为 2 且字符不同的子串一定满足条件，避免复杂的枚举和统计。
- **代码实现**：直接遍历字符串判断相邻字符，减少不必要的操作，提高代码效率和可读性。

### 可拓展之处
同类型题目可能会改变子串的判断条件，如要求子串中字母出现次数的其他限制，或在不同类型的字符串（如数字串、大小写混合串）中寻找满足条件的子串。解题思路仍可从简单情况分析，尝试找到满足条件的最短子串。

### 洛谷相似题目推荐
- [P1308 统计单词数](https://www.luogu.com.cn/problem/P1308)：需要在字符串中查找特定单词的出现情况，涉及字符串的遍历和比较。
- [P1598 垂直柱状图](https://www.luogu.com.cn/problem/P1598)：处理字符串中字符的统计和输出，与本题中字符统计有一定相似性。
- [P1200 [USACO1.1]你的飞碟在这儿Your Ride Is Here](https://www.luogu.com.cn/problem/P1200)：对字符串进行处理和计算，通过字符的对应关系得到结果。

### 个人心得摘录与总结
- **happybob**：使用 `map` 统计字符数量时，要注意判断条件是“小于等于”，除法除以 2 可以用右移操作优化。总结：在使用数据结构和进行条件判断时要仔细，注意细节避免出错，同时可以运用位运算优化代码。 

---
处理用时：30.53秒