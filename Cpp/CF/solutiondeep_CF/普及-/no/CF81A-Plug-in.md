# 题目信息

# Plug-in

## 题目描述

Polycarp thinks about the meaning of life very often. He does this constantly, even when typing in the editor. Every time he starts brooding he can no longer fully concentrate and repeatedly presses the keys that need to be pressed only once. For example, instead of the phrase "how are you" he can type "hhoow aaaare yyoouu".

Polycarp decided to automate the process of correcting such errors. He decided to write a plug-in to the text editor that will remove pairs of identical consecutive letters (if there are any in the text). Of course, this is not exactly what Polycarp needs, but he's got to start from something!

Help Polycarp and write the main plug-in module. Your program should remove from a string all pairs of identical letters, which are consecutive. If after the removal there appear new pairs, the program should remove them as well. Technically, its work should be equivalent to the following: while the string contains a pair of consecutive identical letters, the pair should be deleted. Note that deleting of the consecutive identical letters can be done in any order, as any order leads to the same result.

## 样例 #1

### 输入

```
hhoowaaaareyyoouu
```

### 输出

```
wre```

## 样例 #2

### 输入

```
reallazy
```

### 输出

```
rezy```

## 样例 #3

### 输入

```
abacabaabacabaa
```

### 输出

```
a```

# AI分析结果

### 题目翻译
# 插件

## 题目描述
波利卡普经常思考生命的意义。他无时无刻不在思考，即使是在编辑器中打字的时候也是如此。每当他开始沉思，就无法完全集中注意力，会反复按下那些本只需按一次的按键。例如，他本应输入 “how are you”，却可能会输入 “hhoow aaaare yyoouu”。

波利卡普决定将纠正这类错误的过程自动化。他打算为文本编辑器编写一个插件，用于删除文本中所有相同的连续字母对（如果有的话）。当然，这并非波利卡普真正需要的功能，但总得有个开始！

请帮助波利卡普编写插件的主要模块。你的程序应从字符串中删除所有连续的相同字母对。如果删除后出现新的字母对，程序也应将其删除。从技术上讲，其工作原理应等同于以下过程：只要字符串中存在连续的相同字母对，就将其删除。请注意，删除连续相同字母的顺序可以任意，因为任何顺序都会得到相同的结果。

## 样例 #1
### 输入
```
hhoowaaaareyyoouu
```
### 输出
```
wre
```

## 样例 #2
### 输入
```
reallazy
```
### 输出
```
rezy
```

## 样例 #3
### 输入
```
abacabaabacabaa
```
### 输出
```
a
```

### 算法分类
字符串

### 综合分析与结论
这些题解的核心思路都是使用栈来解决问题。由于删除连续相同字母对后可能会产生新的字母对，栈先进后出的特性非常适合处理这种情况。各题解的主要区别在于栈的实现方式（使用系统栈或手写栈）以及输出结果的方式。

### 所选题解
- **作者：Transparent (赞：3)，4星**
  - **关键亮点**：思路清晰，详细解释了使用栈的原因和具体操作过程，代码注释较详细，易于理解。
- **作者：xiaomuyun (赞：2)，4星**
  - **关键亮点**：选择手写栈，方便输出结果，代码简洁明了。
- **作者：sysong (赞：1)，4星**
  - **关键亮点**：手动开栈模拟，输出时将最后一位设为 `'\0'`，可直接输出整串，代码实现巧妙。

### 重点代码
#### 作者：Transparent
```cpp
#include<bits/stdc++.h>
using namespace std;
char str[200001],ans[200001];//str表示原串，ans为逆序的答案 
stack<char>sta;//栈 
int tot;//计数用 
int main()
{
    scanf("%s",str+1);//从第一位开始输入 
    int len=strlen(str+1);//同样从第一位求长度 
    for(register int i=1;i<=len;i++)
    {
        if(!sta.empty()&&sta.top()==str[i])//注意先判空 
            sta.pop();
        else
            sta.push(str[i]);
    }
    while(!sta.empty())
    {
        ans[++tot]=sta.top();
        sta.pop();
    }
    for(register int i=strlen(ans+1);i>=1;i--)
    {
        printf("%c",ans[i]);//逆序输出 
    }
    return 0;
}
```
**核心实现思想**：从头到尾遍历字符串，若当前字符与栈顶元素相等，则弹出栈顶元素；否则将当前字符压入栈顶。最后将栈中元素逆序输出。

#### 作者：xiaomuyun
```cpp
#include<iostream>
#include<cstdio>
#include<stack>

using namespace std;

string s;
int cnt[30],sz=0;
char st[200001];

int main(){
    cin>>s;
    int len=s.length();
    for(int i=0;i<len;++i){
        if(sz&&st[sz]==s[i]) --sz;//出栈
        else st[++sz]=s[i];//入栈
    }
    for(int i=1;i<=sz;++i) printf("%c",st[i]);//直接输出即可
    putchar('\n');
    return 0;
}
```
**核心实现思想**：手写栈，遍历字符串，若栈顶元素与当前字符相等，则栈顶指针减 1；否则将当前字符存入栈中。最后直接输出栈中元素。

#### 作者：sysong
```c++
#include <cstdio>
#define R register
#define gc() getchar()
using namespace std;

char st[200001];
int tp;

int main(){
    R char c=gc();
    while(c!='\n'){
        if(tp&&c==st[tp])--tp;
        else st[++tp]=c;
        c=gc();
    }
    st[tp+1]='\0';
    printf("%s\n",st+1);
    return 0;
}
```
**核心实现思想**：手动开栈模拟，逐个读取字符，若当前字符与栈顶元素相等，则栈顶指针减 1；否则将当前字符存入栈中。最后将栈顶下一位设为 `'\0'`，直接输出整串。

### 最优关键思路或技巧
使用栈来处理删除连续相同字符对的问题，利用栈先进后出的特性，能方便地处理删除后产生新字母对的情况。

### 可拓展之处
同类型题如处理括号匹配、表达式求值等问题，也可以使用栈来解决。类似算法套路是利用栈的特性，在遍历过程中根据条件进行入栈和出栈操作。

### 推荐题目
- [P1739 表达式括号匹配](https://www.luogu.com.cn/problem/P1739)
- [P1044 栈](https://www.luogu.com.cn/problem/P1044)
- [P4712 【模板】括号序列](https://www.luogu.com.cn/problem/P4712)

### 个人心得摘录与总结
- **sysong**：原来的翻译没有强调“连续”字符，可能会导致误解，提醒我们在做题时要仔细理解题意。

---
处理用时：42.09秒