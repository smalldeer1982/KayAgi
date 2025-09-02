# 题目信息

# Two-gram

## 题目描述

Two-gram is an ordered pair (i.e. string of length two) of capital Latin letters. For example, "AZ", "AA", "ZA" — three distinct two-grams.

You are given a string $ s $ consisting of $ n $ capital Latin letters. Your task is to find any two-gram contained in the given string as a substring (i.e. two consecutive characters of the string) maximal number of times. For example, for string $ s $ = "BBAABBBA" the answer is two-gram "BB", which contained in $ s $ three times. In other words, find any most frequent two-gram.

Note that occurrences of the two-gram can overlap with each other.

## 说明/提示

In the first example "BA" is also valid answer.

In the second example the only two-gram "ZZ" can be printed because it contained in the string "ZZZAA" two times.

## 样例 #1

### 输入

```
7
ABACABA
```

### 输出

```
AB
```

## 样例 #2

### 输入

```
5
ZZZAA
```

### 输出

```
ZZ
```

# AI分析结果

### 题目翻译
## 双字母组合

### 题目描述
双字母组合是由大写拉丁字母组成的有序对（即长度为 2 的字符串）。例如，"AZ"、"AA"、"ZA" 是三个不同的双字母组合。

给定一个由 $n$ 个大写拉丁字母组成的字符串 $s$。你的任务是找出在给定字符串中作为子串（即字符串中连续的两个字符）出现次数最多的双字母组合。例如，对于字符串 $s$ = "BBAABBBA"，答案是双字母组合 "BB"，它在 $s$ 中出现了三次。换句话说，找出出现次数最多的双字母组合。

注意，双字母组合的出现可以相互重叠。

### 说明/提示
在第一个样例中，"BA" 也是有效的答案。

在第二个样例中，唯一的双字母组合 "ZZ" 可以被输出，因为它在字符串 "ZZZAA" 中出现了两次。

### 样例 #1
#### 输入
```
7
ABACABA
```
#### 输出
```
AB
```

### 样例 #2
#### 输入
```
5
ZZZAA
```
#### 输出
```
ZZ
```

### 综合分析与结论
这些题解主要围绕找出字符串中出现次数最多的长度为 2 的子串展开，思路可分为以下几类：
1. **使用 `map` 统计**：将长度为 2 的子串作为键，出现次数作为值存入 `map`，最后遍历 `map` 找出最大值。如 WinterRain208、happybob、GusyNight、封禁用户（思路 2）、Eason_AC 的题解。
2. **二维数组统计**：利用字母的 ASCII 码或相对位置作为二维数组的下标，统计子串出现次数，再找出最大值。如 Cult_style、judgejudge、Pkixzx、静静是我的，（方案二）的题解。
3. **暴力枚举**：枚举每个长度为 2 的子串，再遍历字符串统计其出现次数。如 cyrxdzj、UperFicial、Aehnuwx、静静是我的，（方案一）的题解。

### 所选题解
- **WinterRain208（5星）**
    - **关键亮点**：思路清晰，使用 `map` 解决问题，详细介绍了 `map` 的使用方法和 `cpp11` 的遍历方式，还给出了扩展情况。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
#define F(i,j,r) for(int i=j;i<=r;++i)

using namespace std;

string a;
string ans;
int M=-1;

map <  string, int > m; 
int main(){
    cin>>a;
    cin>>a;
    F(i,0,a.size()-2)
        m[a.substr(i,2)]++;
    for( auto && p : m )
        if(p.second>M){
            M=p.second;
            ans=p.first.c_str();
        }
    cout<<ans<<endl;
    return 0;
}
```
核心思想：枚举所有长度为 2 的子串，存入 `map` 统计出现次数，最后遍历 `map` 找出出现次数最多的子串。

- **Cult_style（4星）**
    - **关键亮点**：使用二维数组统计子串出现次数，代码简洁，思路清晰。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int k[30][30];
char a[105];
int ma;
int main(){
    scanf("%d",&n);
    cin>>a;
    for(int i=0;i<n-1;i++){
        int x=a[i]-'A',y=a[i+1]-'A';
        k[x][y]++;
        if(k[x][y]>ma) ma=k[x][y];	
    }
    for(int i=0;i<26;i++){
        for(int j=0;j<26;j++){
            if(k[i][j]==ma){
                printf("%c%c",i+'A',j+'A');
                return 0;
            }
        }
    }
    return 0;
}
```
核心思想：将字母转换为数字作为二维数组的下标，统计子串出现次数，找出出现次数最多的子串并输出。

- **cyrxdzj（4星）**
    - **关键亮点**：采用暴力枚举的方法，对代码中的关键问题给出了思考题及答案，有助于理解。
    - **核心代码**：
```cpp
#include<iostream>
#include<string>
using namespace std;
int len;
string input;
int ans_cnt;
int ans_i;
int main()
{
    cin>>len>>input;
    for(int i=0;i<len-2;i++)
    {
        int cnt=1;
        for(int j=i+1;j<len-1;j++)
        {
            if(input[i]==input[j]&&input[i+1]==input[j+1])
            {
                cnt++;
            }
        }
        if(cnt>ans_cnt)
        {
            ans_cnt=cnt;
            ans_i=i;
        }
    }
    cout<<input[ans_i]<<input[ans_i+1]<<endl;
    return 0;
}
```
核心思想：枚举每个长度为 2 的子串，再遍历字符串统计其出现次数，使用打擂台的方法找出出现次数最多的子串。

### 最优关键思路或技巧
- **数据结构选择**：使用 `map` 可以方便地统计字符串的出现次数，适用于字符范围较大的情况；二维数组则更适合字符范围较小的情况，能减少空间开销和查找时间。
- **代码实现技巧**：使用 `substr` 函数可以方便地截取字符串的子串；利用字母的 ASCII 码或相对位置作为数组下标，可以简化代码。

### 可拓展之处
同类型题可以是找出字符串中出现次数最多的长度为 $k$ 的子串，或者找出多个字符串中共同出现次数最多的子串。类似算法套路可以是使用哈希表或字典树来统计字符串的出现次数。

### 推荐题目
1. [P1059 明明的随机数](https://www.luogu.com.cn/problem/P1059)：考察去重和排序，可使用 `map` 或 `set` 实现。
2. [P1217 [USACO1.5]回文质数 Prime Palindromes](https://www.luogu.com.cn/problem/P1217)：需要判断质数和回文数，可使用筛选法和字符串处理。
3. [P1598 垂直柱状图](https://www.luogu.com.cn/problem/P1598)：需要统计字符出现次数并输出柱状图，可使用数组统计。

### 个人心得摘录与总结
- **封禁用户**：在调试过程中遇到了 `set` 的问题，说明使用 `set` 时容易出错，需要注意。
- **静静是我的，**：提醒大家注意大小写问题，避免因粗心导致错误。

---
处理用时：35.74秒