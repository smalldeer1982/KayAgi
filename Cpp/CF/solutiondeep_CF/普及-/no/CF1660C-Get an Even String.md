# 题目信息

# Get an Even String

## 题目描述

A string $ a=a_1a_2\dots a_n $ is called even if it consists of a concatenation (joining) of strings of length $ 2 $ consisting of the same characters. In other words, a string $ a $ is even if two conditions are satisfied at the same time:

- its length $ n $ is even;
- for all odd $ i $ ( $ 1 \le i \le n - 1 $ ), $ a_i = a_{i+1} $ is satisfied.

For example, the following strings are even: "" (empty string), "tt", "aabb", "oooo", and "ttrrrroouuuuuuuukk". The following strings are not even: "aaa", "abab" and "abba".

Given a string $ s $ consisting of lowercase Latin letters. Find the minimum number of characters to remove from the string $ s $ to make it even. The deleted characters do not have to be consecutive.

## 说明/提示

In the first test case you can remove the characters with indices $ 6 $ , $ 7 $ , and $ 9 $ to get an even string "aabbddcc".

In the second test case, each character occurs exactly once, so in order to get an even string, you must remove all characters from the string.

In the third test case, you can get an even string "aaaabb" by removing, for example, $ 4 $ -th and $ 6 $ -th characters, or a string "aabbbb" by removing the $ 5 $ -th character and any of the first three.

## 样例 #1

### 输入

```
6
aabbdabdccc
zyx
aaababbb
aabbcc
oaoaaaoo
bmefbmuyw```

### 输出

```
3
3
2
0
2
7```

# AI分析结果

### 题目内容
# 获取偶数字符串

## 题目描述
字符串 $a = a_1a_2…a_n$ 被称为偶数字符串，如果它由长度为2且由相同字符组成的字符串连接而成。换句话说，当同时满足以下两个条件时，字符串 $a$ 是偶数字符串：
- 其长度 $n$ 为偶数；
- 对于所有奇数 $i$（$1 \leq i \leq n - 1$），都满足 $a_i = a_{i + 1}$。

例如，以下字符串是偶数字符串：""（空字符串）、"tt"、"aabb"、"oooo" 和 "ttrrrroouuuuuuuukk"。以下字符串不是偶数字符串："aaa"、"abab" 和 "abba"。

给定一个由小写拉丁字母组成的字符串 $s$。求从字符串 $s$ 中删除最少数量的字符，使其成为偶数字符串。删除的字符不必是连续的。

## 说明/提示
在第一个测试用例中，你可以删除索引为6、7和9的字符，得到偶数字符串 "aabbddcc"。

在第二个测试用例中，每个字符恰好出现一次，因此为了得到偶数字符串，你必须删除字符串中的所有字符。

在第三个测试用例中，例如，你可以通过删除第4个和第6个字符得到偶数字符串 "aaaabb"，或者通过删除第5个字符和前三个字符中的任意一个得到字符串 "aabbbb"。

## 样例 #1
### 输入
```
6
aabbdabdccc
zyx
aaababbb
aabbcc
oaoaaaoo
bmefbmuyw
```
### 输出
```
3
3
2
0
2
7
```

### 算法分类
贪心

### 题解综合分析与结论
这些题解大多采用贪心策略。核心思路是从前往后扫描字符串，利用数组记录字符出现次数，当某个字符出现两次时，认为这两个字符可匹配成一对，将记录数组清空（表示中间的字符无效），并更新可保留字符数（或需删除字符数）。不同题解在细节表述和代码实现上略有差异，但本质思路一致。

### 所选的题解
 - **作者：Dedaka (赞：16)  星级：5星 关键亮点：思路清晰简洁，直接阐述贪心策略及关键细节，代码简洁明了**
```cpp
#include<bits/stdc++.h>
#define mx 30
using namespace std;
int t,c[mx];
string s;
int main(){
    cin>>t;
    while(t--){
        cin>>s;
        int l=s.length(),cnt=l;
        for(int i=0;i<l;i++){
            int tmp=s[i]-'a';
            c[tmp]++;
            if(c[tmp]==2){//该字母已匹配 
                cnt-=2;
                memset(c,0,sizeof(c));//清空 awa 
            }
        }
        cout<<cnt<<endl;
        memset(c,0,sizeof(c));
    }
    return 0;
}
```
核心实现思想：遍历字符串，用数组 `c` 记录字符出现次数，当字符出现两次时，更新需删除字符数 `cnt` 并清空数组 `c`。

 - **作者：ajhuhe (赞：2)  星级：4星 关键亮点：先阐述初步贪心策略及问题，再引出正确贪心策略，分析过程详细**
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int t,len,cnt[27];
int main()
{
    cin>>t;
    while(t--)
    {
        int sum=0;
        memset(cnt,0,sizeof(cnt));
        cin>>s;
        len=s.length();
        for(int i=0;i<len;i++)
        {
            cnt[s[i]-'a'+1]++;//桶思想，统计次数 
            if(cnt[s[i]-'a'+1]==2)//每出现相同字符就清空 cnt 数组 
            {
                memset(cnt,0,sizeof(cnt));
                sum+=2;//记录数量 
            }
        }
        cout<<len-sum<<endl;//输出答案 
    }
    return 0;
}
```
核心实现思想：通过数组 `cnt` 统计字符出现次数，当字符出现两次，清空数组 `cnt` 并记录可保留字符数 `sum`，最后用总长度减去可保留字符数得到答案。

 - **作者：EtHereal_Algorithm (赞：1)  星级：4星 关键亮点：详细给出贪心过程及证明，使贪心策略更具说服力**
```cpp
#include <bits/stdc++.h>
#define up(i,l,r) for(int i=(l);i<=(r);i++)
#define down(i,r,l) for(int i=(r);i>=(l);i--)
typedef long long ll;
using namespace std;
inline int read(){
    int f = 1, x = 0;
    char ch;
    do{ch = getchar();if(ch == '-')f = -1;}while(ch < '0' || ch > '9');
    do{x = x * 10 + ch - '0';ch = getchar();}while(ch >= '0' && ch <= '9');
    return f * x;
}
void print(int x){
    if(x > 9) print(x / 10);
    putchar(x % 10 + '0');
}
int bins[128];//桶思想记录出现次数
void clb()
{
    up(i, 0, 127) bins[i] = 0;
}
int main()
{
    int t;
    cin >> t;
    while(t--)
    {
        string str;
        cin >> str;
        int n, ans; ans = n = str.size();
        clb();//初始化
        //由于最后的需要删掉不好处理，所以我们把答案初始化为 n，每次删除操作就-2。
        up(i, 0, n - 1)
            if(++bins[int(str[i])] == 2)//一旦到达 2 个，
            {
                ans -= 2;//删掉
                clb();//中间的都没用了
            }
        print(ans); puts("");
    }
    return 0;
}
```
核心实现思想：利用数组 `bins` 统计字符出现次数，当字符出现两次，更新需删除字符数 `ans` 并清空数组 `bins`。

### 最优关键思路或技巧
采用贪心策略，从前往后扫描字符串，利用桶数组记录字符出现次数，当某个字符出现两次时，认定这两个字符匹配，清空桶数组以保证中间字符无效，从而确定最少删除字符数。

### 可拓展之处
同类型题通常围绕字符串操作与特定规则满足，类似算法套路为根据题目规则设计合适的贪心策略，利用数组等简单数据结构辅助记录状态，通过遍历字符串做出局部最优选择以达到全局最优。

### 洛谷相似题目推荐
 - [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)
 - [P1248 加工生产调度](https://www.luogu.com.cn/problem/P1248)
 - [P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094)

### 个人心得摘录与总结
无。 

---
处理用时：57.78秒