# 题目信息

# The Monster

## 题目描述

As Will is stuck in the Upside Down, he can still communicate with his mom, Joyce, through the Christmas lights (he can turn them on and off with his mind). He can't directly tell his mom where he is, because the monster that took him to the Upside Down will know and relocate him.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF917A/4c119b489e29bab2fd3dc778221019b04c8209ba.png)Thus, he came up with a puzzle to tell his mom his coordinates. His coordinates are the answer to the following problem.

A string consisting only of parentheses ('(' and ')') is called a bracket sequence. Some bracket sequence are called correct bracket sequences. More formally:

- Empty string is a correct bracket sequence.
- if $ s $ is a correct bracket sequence, then $ (s) $ is also a correct bracket sequence.
- if $ s $ and $ t $ are correct bracket sequences, then $ st $ (concatenation of $ s $ and $ t $ ) is also a correct bracket sequence.

A string consisting of parentheses and question marks ('?') is called pretty if and only if there's a way to replace each question mark with either '(' or ')' such that the resulting string is a non-empty correct bracket sequence.

Will gave his mom a string $ s $ consisting of parentheses and question marks (using Morse code through the lights) and his coordinates are the number of pairs of integers $ (l,r) $ such that $ 1<=l<=r<=|s| $ and the string $ s_{l}s_{l+1}...\ s_{r} $ is pretty, where $ s_{i} $ is $ i $ -th character of $ s $ .

Joyce doesn't know anything about bracket sequences, so she asked for your help.

## 说明/提示

For the first sample testcase, the pretty substrings of $ s $ are:

1. "(?" which can be transformed to "()".
2. "?)" which can be transformed to "()".
3. "((?)" which can be transformed to "(())".
4. "(?))" which can be transformed to "(())".

For the second sample testcase, the pretty substrings of $ s $ are:

1. "??" which can be transformed to "()".
2. "()".
3. "??()" which can be transformed to "()()".
4. "?()?" which can be transformed to "(())".
5. "??" which can be transformed to "()".
6. "()??" which can be transformed to "()()".
7. "??()??" which can be transformed to "()()()".

## 样例 #1

### 输入

```
((?))
```

### 输出

```
4
```

## 样例 #2

### 输入

```
??()??
```

### 输出

```
7
```

# AI分析结果

### 题目中文重写
# 怪物

## 题目描述
由于威尔被困在了颠倒世界，他仍然可以通过圣诞灯与他的妈妈乔伊斯交流（他可以用意念打开和关闭这些灯）。他不能直接告诉他妈妈自己在哪里，因为把他带到颠倒世界的怪物会知道并转移他的位置。

![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF917A/4c119b489e29bab2fd3dc778221019b04c8209ba.png)

因此，他想出了一个谜题来告诉他妈妈自己的坐标。他的坐标是以下问题的答案。

仅由括号（`(` 和 `)`）组成的字符串称为括号序列。有些括号序列被称为正确的括号序列。更正式地说：
- 空字符串是一个正确的括号序列。
- 如果 $s$ 是一个正确的括号序列，那么 $(s)$ 也是一个正确的括号序列。
- 如果 $s$ 和 $t$ 是正确的括号序列，那么 $st$（$s$ 和 $t$ 的连接）也是一个正确的括号序列。

一个由括号和问号（`?`）组成的字符串当且仅当有一种方法可以将每个问号替换为 `(` 或 `)`，使得得到的字符串是一个非空的正确括号序列时，该字符串被称为漂亮的。

威尔通过灯光用摩尔斯电码给他妈妈一个由括号和问号组成的字符串 $s$，他的坐标是满足 $1\leq l\leq r\leq |s|$ 且字符串 $s_{l}s_{l + 1}\cdots s_{r}$ 是漂亮的整数对 $(l, r)$ 的数量，其中 $s_{i}$ 是 $s$ 的第 $i$ 个字符。

乔伊斯对括号序列一无所知，所以她向你寻求帮助。

## 说明/提示
对于第一个样例测试用例，$s$ 的漂亮子串有：
1. `(?` 可以转换为 `()`。
2. `?)` 可以转换为 `()`。
3. `((?` 可以转换为 `(())`。
4. `(?))` 可以转换为 `(())`。

对于第二个样例测试用例，$s$ 的漂亮子串有：
1. `??` 可以转换为 `()`。
2. `()`。
3. `??()` 可以转换为 `()()`。
4. `?()?` 可以转换为 `(())`。
5. `??` 可以转换为 `()`。
6. `()??` 可以转换为 `()()`。
7. `??()??` 可以转换为 `()()()`。

## 样例 #1
### 输入
```
((?))
```
### 输出
```
4
```

## 样例 #2
### 输入
```
??()??
```
### 输出
```
7
```

### 综合分析与结论
这些题解主要围绕判断由 `(`, `?`, `)` 组成的字符串的子串是否能通过替换 `?` 成为合法括号序列，进而统计合法子串的数量。

#### 思路对比
- **枚举+模拟**：多数题解采用此思路，枚举子串的起点和终点，模拟括号匹配过程，根据左右括号和问号的情况调整状态，判断子串是否合法。
- **正反枚举**：laeva 的题解通过正反两次枚举处理 `)` 在 `(` 前的情况。
- **动态规划**：ZSYZSYZSYZSY 的题解尝试用动态规划判断子串合法性，但实际代码实现还是枚举+模拟。

#### 算法要点
- **状态记录**：用变量记录左右括号数量差、可转换为右括号的问号数量等。
- **问号处理**：根据左右括号数量决定问号转换为左括号还是右括号。
- **合法性判断**：若左右括号数量差为负且无可用问号则子串不合法；数量差为 0 则合法。

#### 解决难点
- **问号转换**：根据当前状态决定问号转换方向。
- **提前终止**：当子串不合法时及时跳出循环，减少不必要计算。

### 评分较高的题解
- **SpXace（5星）**
    - **关键亮点**：思路清晰，代码简洁，详细说明了每个步骤的作用，易于理解。
    - **核心代码**：
```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
char s[5050];
int tot = 0,Ans = 0,num = 0; 
int main()
{
    cin >> s;
    int len = strlen(s);
    for(int i = 0; i < len; ++i)	
    {
        tot = 0; num = 0; 
        for(int j = i; j < len; ++j)
        {
            if(s[j] == '(')  tot++;
            if(s[j] == ')')  tot--;
            if(s[j] == '?')
            {
                if(tot > 0)
                    tot--,num++;
                else
                    tot++;
            } 
            if(tot < 0 && num) tot += 2,num--;
            if(tot < 0 &&!num) break; 
            if(tot == 0) Ans++;	
        }	 
    }	 
    cout << Ans;
    return 0;
}
```
核心实现思想：枚举子串的起点和终点，用 `tot` 记录左右括号数量差，`num` 记录可转换为右括号的问号数量，根据字符情况更新状态，判断子串合法性并统计合法子串数量。

- **linan04195（4星）**
    - **关键亮点**：思路清晰，代码简洁，详细阐述了每个步骤的逻辑。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;

string s;
int cnt=0,num=0,ans=0;
 
int main(){
	
    cin>>s;
    int len=s.size();
    
    for(int i=0;i<len;i++){ 
    	
        cnt=0,num=0; 
        for(int j=i;j<len;j++){
        	
            if(s[j]==')') cnt--; 
            if(s[j]=='(') cnt++; 
            
            if(s[j]=='?'){
                if(cnt>0) cnt--,num++;
                else cnt++;
            } 
            
            if(cnt==0) ans++; 
            if(cnt<0&&num>0) cnt+=2,num--; 
            if(cnt<0&&num==0) break; 
        }	 
    }	
	
    cout<<ans; 
    return 0;
}
```
核心实现思想与 SpXace 的题解类似，枚举子串，根据字符更新状态，判断合法性并统计答案。

- **naroto2022（4星）**
    - **关键亮点**：思路清晰，对每个步骤的逻辑解释详细，代码规范。
    - **核心代码**：
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;
char s[5005];
int sum,ans,num,len;
int main(){
    cin>>s;
    len=strlen(s);
    for(int i=0; i<len; i++){
        sum=0,num=0;
        for(int j=i; j<len; ++j){
            if(s[j]=='(') sum++;
            if(s[j]==')') sum--;
            if(s[j]=='?'){
                if(sum>0) sum--,num++;
                else sum++;
            } 
            if(sum<0&&num) sum+=2,num--;
            if(sum<0&&!num) break;
            if(sum==0) ans++;
        }	 
    }	 
    cout<<ans;
    return 0;
}
```
核心实现思想同样是枚举子串，模拟括号匹配过程，判断合法性并统计答案。

### 最优关键思路或技巧
- **枚举+模拟**：通过枚举子串的起点和终点，模拟括号匹配过程，根据状态及时终止不合法子串的判断，减少不必要的计算。
- **问号处理**：根据左右括号数量差决定问号转换为左括号还是右括号，巧妙处理不确定字符。

### 可拓展之处
同类型题：
- 包含更多字符类型的括号匹配问题，如 `[`, `]`, `{`, `}` 等。
- 要求输出具体合法子串的问题。

类似算法套路：
- 对于包含不确定元素的序列匹配问题，可通过记录状态和动态调整来解决。

### 推荐题目
- [P1739 表达式括号匹配](https://www.luogu.com.cn/problem/P1739)
- [P1449 后缀表达式](https://www.luogu.com.cn/problem/P1449)
- [P5788 【模板】单调栈](https://www.luogu.com.cn/problem/P5788)

### 个人心得摘录与总结
题解中未包含个人心得内容。

---
处理用时：49.40秒