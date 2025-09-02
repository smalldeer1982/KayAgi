# 题目信息

# [USACO12NOV] Clumsy Cows S

## 题目描述

Bessie the cow is trying to type a balanced string of parentheses into her new laptop, but she is sufficiently clumsy (due to her large hooves) that she keeps mis-typing characters.  Please help her by computing the minimum number of characters in the string that one must reverse (e.g., changing a left parenthesis to a right parenthesis, or vice versa) so that the string would become balanced.

There are several ways to define what it means for a string of parentheses to be "balanced".  Perhaps the simplest definition is that there must be the same total number of ('s and )'s, and for any prefix of the string, there must be at least as many ('s as )'s.  For example, the following strings are all balanced:

() 
(()) 
()(()()) 

while these are not:

)( 
())( 
((()))) 

给出一个偶数长度的括号序列，问最少修改多少个括号可以使其平衡。


## 说明/提示

The last parenthesis must be toggled, and so must one of the two middle right parentheses.



## 样例 #1

### 输入

```
())( 
```

### 输出

```
2 
```

# AI分析结果

### 综合分析与结论
这些题解主要围绕如何通过最少修改括号使给定括号序列平衡展开，思路可归为两类：
 - **模拟栈思路**：包括使用栈数据结构（如作者Garrison、cellur925、ResidualNight用STL栈）和模拟栈的操作（如作者A_Big_Jiong、Berlin_Jacor）。遇到左括号入栈（或模拟入栈计数），遇到右括号时，若栈非空则出栈（或模拟出栈计数），若栈空则需修改括号并将其变为左括号入栈（或模拟入栈计数）。最后栈中剩余左括号数除以2（向上取整）就是还需修改的数量。
 - **贪心思路**：如作者微露点滴，先预处理删除相邻平衡括号，再对剩余单身括号贪心匹配，下标为奇数的左括号和下标为偶数的右括号需修改。

难点在于如何高效判断并处理不平衡的括号，以及如何确定最终需要修改的括号数量。多数题解思路清晰，但在代码可读性和优化程度上有差异。

### 所选题解
 - **作者A_Big_Jiong（4星）**
    - **关键亮点**：思路清晰，详细注释解释变量与操作，虽未优化但基础思路易理解。
    - **个人心得**：作者表示想不到与前缀和关系，疑惑自身为何想不到。
    ```cpp
    int ans,ls,num;
    scanf("%s",&str);
    ls=strlen(str);
    for(int i=0;i<ls;i++){
        if(str[i]=='(')  num++;
        else if(str[i]==')'&&num==0){
            ans++;num++;
        }else num--;
    }
    ans+=num/2;
    if(num%2!=0)  ans++;
    ```
    - **核心思想**：用num模拟栈顶，遍历字符串，左括号num加1，右括号在num为0时需修改且num加1，否则num减1。最后num为未匹配左括号数，一半需修改，若num为奇数则加1。
 - **作者Berlin_Jacor（4星）**
    - **关键亮点**：简洁模拟栈算法原理，代码简洁明了。
    ```cpp
    int ans,sum,i;
    string s;
    cin>>s;
    int lens=s.size();
    for(;i<lens;++i){
        if(s[i]=='(')sum++;
        else{
            if(sum)--sum;
            else ++ans,++sum;
        }
    }
    ans+=sum>>1;
    ```
    - **核心思想**：sum模拟栈，左括号sum加1，右括号若sum大于0则sum减1，否则ans加1且sum加1。最后sum为未匹配左括号数，右移一位（除以2）加到ans。
 - **作者ResidualNight（4星）**
    - **关键亮点**：提供栈和加减计数法两种方法，且对栈的操作讲解详细。
    ```cpp
    // 栈方法
    int ans=0;
    string s;
    stack<char> st;
    cin>>s;
    for(int i=0; i<s.size(); i++){
        if(s[i]=='(') st.push(s[i]);
        else{
            if(st.empty()){st.push('('); ans++;}
            else st.pop();
        }
    }
    if(!st.empty()) ans+=st.size()/2;

    // 加减计数法
    string s;
    int ans=0,p=0;
    cin>>s;
    for(int i=0; i<s.size(); i++){
        if(s[i]=='(') p++;
        else{
            if(p) p--;
            else ans++,p++;
        }
    }
    ans+=p/2;
    ```
    - **核心思想**：栈方法，左括号入栈，右括号若栈空则修改并将左括号入栈，否则出栈，最后栈非空则将栈元素数除以2加到ans。加减计数法类似，左括号计数加1，右括号若计数大于0则减1，否则修改并计数加1，最后计数除以2加到ans。

### 最优关键思路或技巧
模拟栈思路简洁高效，通过模拟栈的进出操作判断括号平衡情况，最后对未匹配括号进行处理。这种模拟栈的计数方式避免了实际使用栈的空间开销，在解决括号匹配及类似平衡问题上是一种实用技巧。

### 可拓展思路
此类题目可拓展到多种括号匹配（如大中小括号混合）或类似的平衡判断问题（如HTML标签匹配）。解题套路通常是利用栈或模拟栈的计数方式，根据不同符号的出现规则进行匹配和处理。

### 相似知识点洛谷题目
 - **P1449 后缀表达式**：通过栈实现后缀表达式计算，考察栈的应用。
 - **P1308 统计单词数**：在字符串处理中，可利用栈来辅助匹配单词边界等，与本题对字符串中符号处理有相似处。
 - **P2056 [ZJOI2007] 捉迷藏**：虽主要是树上问题，但在处理过程中可能会用到类似栈的思想来维护状态。 

---
处理用时：66.88秒