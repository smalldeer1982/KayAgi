# 题目信息

# Camp Schedule

## 题目描述

The new camp by widely-known over the country Spring Programming Camp is going to start soon. Hence, all the team of friendly curators and teachers started composing the camp's schedule. After some continuous discussion, they came up with a schedule $ s $ , which can be represented as a binary string, in which the $ i $ -th symbol is '1' if students will write the contest in the $ i $ -th day and '0' if they will have a day off.

At the last moment Gleb said that the camp will be the most productive if it runs with the schedule $ t $ (which can be described in the same format as schedule $ s $ ). Since the number of days in the current may be different from number of days in schedule $ t $ , Gleb required that the camp's schedule must be altered so that the number of occurrences of $ t $ in it as a substring is maximum possible. At the same time, the number of contest days and days off shouldn't change, only their order may change.

Could you rearrange the schedule in the best possible way?

## 说明/提示

In the first example there are two occurrences, one starting from first position and one starting from fourth position.

In the second example there is only one occurrence, which starts from third position. Note, that the answer is not unique. For example, if we move the first day (which is a day off) to the last position, the number of occurrences of $ t $ wouldn't change.

In the third example it's impossible to make even a single occurrence.

## 样例 #1

### 输入

```
101101
110
```

### 输出

```
110110```

## 样例 #2

### 输入

```
10010110
100011
```

### 输出

```
01100011
```

## 样例 #3

### 输入

```
10
11100
```

### 输出

```
01```

# AI分析结果

【题目内容（中文重写）】
# 营地日程安排

## 题目描述
全国知名的春季编程营即将开营。友好的辅导员和教师团队开始制定营地日程。经过持续讨论，他们制定出日程 $s$，可用二进制字符串表示，其中第 $i$ 个字符为 '1' 表示学生在第 $i$ 天参加竞赛，为 '0' 表示休息。

最后，Gleb 表示如果营地按照日程 $t$（格式与日程 $s$ 相同）进行，效率将最高。由于当前日程的天数可能与日程 $t$ 不同，Gleb 要求调整营地日程，使 $t$ 作为子串在其中出现的次数尽可能多。同时，竞赛日和休息日的数量不应改变，仅顺序可以调整。

你能以最佳方式重新安排日程吗？

## 说明/提示
在第一个示例中，有两个出现位置，一个从第一个位置开始，一个从第四个位置开始。

在第二个示例中，只有一个出现位置，从第三个位置开始。注意，答案不唯一。例如，如果我们将第一天（休息日）移到最后一天，$t$ 的出现次数不会改变。

在第三个示例中，甚至无法出现一次。

## 样例 #1
### 输入
```
101101
110
```
### 输出
```
110110
```

## 样例 #2
### 输入
```
10010110
100011
```
### 输出
```
01100011
```

## 样例 #3
### 输入
```
10
11100
```
### 输出
```
01
```

【算法分类】
构造

【综合分析与结论】
这些题解的核心思路都是利用贪心策略结合 KMP 算法来解决问题。首先统计字符串 $s$ 中 '0' 和 '1' 的个数，然后使用 KMP 算法求出字符串 $t$ 的 $next$ 数组（最长公共前后缀），接着尽可能多地使用 $t$ 来构造新的字符串，同时利用 $t$ 的公共前后缀部分减少字符的使用，最后将剩余的字符添加到结果字符串的末尾。

各题解的区别主要在于代码实现的细节和风格，如输入输出方式、$next$ 数组的计算方式等，但整体思路是一致的。

【所选的题解】
- Hughpig（5星）：思路清晰，直接指出了简单拼凑的错误原因，详细说明了利用 KMP 算法求最长公共前后缀并重复利用的方法，代码实现简洁明了。
- StudyingFather（4星）：先介绍了前置知识 KMP 算法，然后详细阐述了利用 KMP 思想解决本题的过程，包括贪心填充和指针的移动，代码结构清晰。
- qwqszxc45rtnhy678ikj（4星）：对题目的分析较为详细，明确指出了要构造的新串的性质和贪心策略，代码实现符合思路。

【重点代码】
以下是 Hughpig 题解的核心代码：
```cpp
#include<bits/stdc++.h>
using namespace std;

string s,t;
int n,m,cnt0,cnt1,cnt,nxt[500007];

int main()
{
    cin>>s>>t;
    n=s.size(),m=t.size();
    for(auto c:s){
        if(c=='0')++cnt0;
        else ++cnt1;
    }
    s=" "+s,t=" "+t;
    for(int i=2,j=0;i<=m;++i){
        while(j&&t[i]!=t[j+1])j=nxt[j];
        if(t[i]==t[j+1])++j;
        nxt[i]=j;
    }
    while(1){
        int precnt0=cnt0,precnt1=cnt1;
        if(cnt){
            for(int i=1+nxt[m];i<=m;++i){
                if(t[i]=='0')--cnt0;
                else --cnt1;
            }
        }
        else{
            for(int i=1;i<=m;++i){
                if(t[i]=='0')--cnt0;
                else --cnt1;
            }
        }
        if(cnt0<0||cnt1<0){
            cnt0=precnt0,cnt1=precnt1;
            break;
        }
        if(cnt)cout<<t.substr(nxt[m]+1);
        else cout<<t.substr(1);
        ++cnt;
    }
    while(cnt0>0)cout<<0,--cnt0;
    while(cnt1>0)cout<<1,--cnt1;
    return 0;
}
```
核心实现思想：先统计 $s$ 中 '0' 和 '1' 的个数，然后使用 KMP 算法求出 $t$ 的 $next$ 数组。接着不断尝试使用 $t$ 来构造新的字符串，每次使用时根据是否是第一次使用来决定是否需要输出 $t$ 的公共前后缀部分，直到剩余的字符不足以再构造一个 $t$ 为止。最后将剩余的字符输出。

【最优关键思路或技巧】
- **贪心策略**：尽可能多地使用 $t$ 来构造新的字符串，同时利用 $t$ 的公共前后缀部分减少字符的使用，以增加 $t$ 的出现次数。
- **KMP 算法**：用于求出 $t$ 的最长公共前后缀，从而实现字符的重复利用。

【拓展思路】
同类型题目可能会有不同的字符串操作要求，如改变字符的替换规则、增加更多的限制条件等，但核心思路仍然是利用贪心和字符串匹配算法。类似的算法套路包括利用 KMP 算法解决字符串匹配问题、利用贪心策略优化字符串构造等。

【推荐题目】
- P3375 【模板】KMP字符串匹配
- P5410 【模板】扩展 KMP（Z 函数）
- P1308 [NOIP2011 普及组] 统计单词数

【个人心得】
- mountain_k：提到扫描字符串的 for 循环千万不要用 `(i<strlen(s))` 当条件，否则会变成 $O(n^2)$ 的算法，可能会导致 TLE。这是一个需要注意的细节，避免因代码实现不当而导致时间复杂度增加。

---
处理用时：47.03秒