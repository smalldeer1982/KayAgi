# 题目信息

# Bracket Sequence

## 题目描述

A bracket sequence is a string, containing only characters "(", ")", "\[" and "\]".

A correct bracket sequence is a bracket sequence that can be transformed into a correct arithmetic expression by inserting characters "1" and "+" between the original characters of the sequence. For example, bracket sequences "()\[\]", "(\[\])" are correct (the resulting expressions are: "(1)+\[1\]", "(\[1+1\]+1)"), and "\](" and "\[" are not. The empty string is a correct bracket sequence by definition.

A substring $ s[l...\ r] $ $ (1<=l<=r<=|s|) $ of string $ s=s_{1}s_{2}...\ s_{|s|} $ (where $ |s| $ is the length of string $ s $ ) is the string $ s_{l}s_{l+1}...\ s_{r} $ . The empty string is a substring of any string by definition.

You are given a bracket sequence, not necessarily correct. Find its substring which is a correct bracket sequence and contains as many opening square brackets «\[» as possible.

## 样例 #1

### 输入

```
([])
```

### 输出

```
1
([])
```

## 样例 #2

### 输入

```
(((
```

### 输出

```
0

```

# AI分析结果

### 题目内容
# 括号序列

## 题目描述
一个括号序列是一个仅包含字符“(”、“)”、“[”和“]”的字符串。

一个正确的括号序列是指可以通过在原序列字符之间插入字符“1”和“+”，将其转换为一个正确算术表达式的括号序列。例如，括号序列“()[]”、“([])”是正确的（得到的表达式分别为：“(1)+[1]”，“([1 + 1]+1)”），而“](”和“[”则不正确。根据定义，空字符串是一个正确的括号序列。

字符串 $s = s_{1}s_{2}...s_{|s|}$（其中 $|s|$ 是字符串 $s$ 的长度）的子串 $s[l...r]$  $(1 \leq l \leq r \leq |s|)$ 是指字符串 $s_{l}s_{l + 1}...s_{r}$。根据定义，空字符串是任何字符串的子串。

给定一个括号序列，不一定正确。找出它的一个子串，该子串是一个正确的括号序列，并且包含尽可能多的左方括号“[”。

## 样例 #1
### 输入
```
([])
```
### 输出
```
1
([])
```

## 样例 #2
### 输入
```
(((
```
### 输出
```
0
```

### 算法分类
动态规划

### 综合分析与结论
这几道题解主要围绕如何找到给定括号序列中包含最多“[”的合法子串。核心思路都是先判断括号序列的合法性，再统计“[”的数量。不同点在于具体实现方法，有的使用动态规划结合栈来记录匹配位置和统计“[”的数量，有的采用搜索的方式从相邻合法括号对出发扩展合法子串。

### 所选的题解
- **作者：卷王 (赞：8) - 5星**
    - **关键亮点**：思路清晰，明确指出题目本质与CF5C类似，详细解释数组和变量含义。利用栈匹配括号，通过动态规划计算以每个位置结尾的合法子串中“[”的最大数量，最后反推答案子串的起始位置。
    - **个人心得**：无
    ```cpp
    // 核心代码片段
    for(int i=1;i<=n;i++){
        if(s[i]=='('||s[i]=='[') {
            st.push(i);
            l[i]=-1;
            continue;
        }
        if(s[i]==')'){
            if(!st.empty()&&s[st.top()]=='('){
                l[i]=st.top(); st.pop();
            }
            else{
                l[i]=-1;
                while(!st.empty()) st.pop();
            }
        }
        else if(s[i]==']'){
            if(!st.empty()&&s[st.top()]=='['){
                l[i]=st.top(); st.pop();
            }
            else{
                l[i]=-1;
                while(!st.empty()) st.pop();
            }
        }
    }
    for(int i=1;i<=n;i++) sum[i]=sum[i-1]+(s[i]=='[');
    int maxx=0,x=-1;
    for(int i=1;i<=n;i++){
        if(s[i]=='('||s[i]=='['||l[i]==-1) dp[i]=0;
        else dp[i]=dp[l[i]-1]+sum[i]-sum[l[i]-1];
        if(dp[i]>maxx){
            maxx=dp[i];
            x=i;
        }
    }
    if(maxx==0){
        cout<<"0\n";
        return 0;
    }
    int L=l[x];
    while(1){
        if(L==1||l[L-1]==-1) break;
        L=l[L-1];
    }
    cout<<maxx<<"\n";
    for(int i=L;i<=x;i++) cout<<s[i];
    cout<<"\n";
    ```
    - **核心实现思想**：首先用栈匹配括号，记录每个右括号匹配的左括号位置。然后通过前缀和数组 `sum` 统计“[”的数量。接着利用动态规划，根据匹配关系和前缀和计算每个位置的最大“[”数量，最后反推答案子串的起始位置并输出。

- **作者：_outcast_ (赞：5) - 4星**
    - **关键亮点**：采用BFS搜索思路，从相邻的合法括号对出发，通过包含型和连接型两种方式扩展合法子串，同时记录子串信息和“[”的数量，找到最优解。
    - **个人心得**：无
    ```cpp
    // 核心代码片段
    void push(int l,int r,int c){//核心，入队操作，记录边界并更新答案 
        v[l]=r; v[r]=l;
        val[l]=val[r]=c;
        q.push(l);
        q.push(r);
    }
    void bfs(){
        memset(v,-1,sizeof v);
        for(n=0;s[n];n++){//取出相邻的合法括号 
            if(s[n]=='('&&s[n+1]==')'){
                push(n,n+1,0);
                continue;
            }
            if(s[n]=='['&&s[n+1]==']'){
                push(n,n+1,1);
                continue;
            }
        }
        if(!q.size()) puts("0"),exit(0);//没有相邻的合法括号，无解 
        for(ans=-1;q.size();){
            int l=q.front();q.pop();
            int r=q.front();q.pop();
            
            if(v[l]==-1||v[r]==-1) continue;//如果当前节点不是边界，跳过 
            
            if(ans<val[l]) ans=val[l],al=l,ar=r;//记录答案 
            
            if(l>0&&r<n-1){//包含型 
                if(s[l-1]=='('&&s[r+1]==')'){
                    v[l]=v[r]=-1,push(l-1,r+1,val[l]);
                    continue;
                }
                if(s[l-1]=='['&&s[r+1]==']'){
                    v[l]=v[r]=-1,push(l-1,r+1,val[l]+1);
                    continue;
                }
            }
            
            if(l>0&&v[l-1]!=-1){//连接型 
                push(v[l-1],r,val[l-1]+val[l]),v[l]=v[l-1]=-1;
                continue;
            }
            if(r<n-1&&v[r+1]!=-1){
                push(l,v[r+1],val[r]+val[r+1]),v[r]=v[r+1]=-1;
                continue;
            }
        }
        s[ar+1]=0;
        cout<<ans<<'\n'<<s+al;
    }
    ```
    - **核心实现思想**：通过 `push` 函数将相邻合法括号对的信息入队，`bfs` 函数中从队列取出节点，根据包含型和连接型两种情况扩展子串并更新答案，最后输出结果。

- **作者：Melo_DDD (赞：1) - 4星**
    - **关键亮点**：指出题目与CF5C做法相似，用栈匹配括号记录匹配位置，利用动态规划结合前缀和统计“[”的数量，清晰解释转移方程。
    - **个人心得**：分享了因栈数组类型设置错误导致RE的调试经历。
    ```cpp
    // 核心代码片段
    cin >> ch + 1 ;
    int len = strlen (ch + 1) ;
    f (i,1,len,1) {
        if (ch[i] == '(' || ch[i] == '[')
            stk[++ stop] = i ;
        else if (ch[i] == ')') {
            if (stop && ch[stk[stop]] == '(') {
                inf[i] = stk[stop --] ;
            }
            else 
                stop = 0 ;
        } else {
            if (stop && ch[stk[stop]] == '[') 
                inf[i] = stk[stop --] ;
            else 
                stop = 0 ;
        }
    }
    f (i,1,len,1) 
        sum[i] = sum[i - 1] + (ch[i] == '[') ;
    int maxx = 0 ;
    f (i,1,len,1) {
        if (inf[i])
            dp[i] = dp[inf[i] - 1] + sum[i] - sum[inf[i] - 1] ;
        if (dp[maxx] <= dp[i]) 
            maxx = i ;
    }
    cout << dp[maxx] << '\n' ;
    if (! maxx)
        return 0 ;
    int loc ; 
    for (loc = maxx ;inf[loc] ;loc = inf[loc] - 1) ;
    f (i,loc + 1,maxx,1) 
        cout << ch[i] ;
    cout << '\n' ;
    ```
    - **核心实现思想**：先通过栈匹配括号记录每个右括号匹配的左括号位置，再用前缀和数组 `sum` 统计“[”的数量，利用动态规划根据匹配位置和前缀和计算每个位置的最大“[”数量，最后反推答案子串的起始位置并输出。

### 最优关键思路或技巧
利用栈来匹配括号是判断合法性的有效方法。动态规划结合前缀和的方式能高效统计合法子串中“[”的数量。通过记录每个右括号匹配的左括号位置，方便后续动态规划的状态转移和答案子串的查找。

### 同类型题或类似算法套路拓展
此类题目通常围绕括号匹配展开，常见套路是利用栈判断合法性，结合动态规划或搜索来解决更复杂的要求，如统计特定字符数量、求最长合法子串等。

### 推荐洛谷题目
- [P1144 最短路计数](https://www.luogu.com.cn/problem/P1144)：涉及图论中的最短路计数问题，与本题类似之处在于都需要记录状态并进行动态更新。
- [P1002 过河卒](https://www.luogu.com.cn/problem/P1002)：典型的递推问题，通过记录每个位置的状态来求解，和本题动态规划记录每个位置信息的思路类似。
- [P1216 数字三角形](https://www.luogu.com.cn/problem/P1216)：利用动态规划求解最优路径问题，与本题利用动态规划求最优子串有相似的思维方式。

### 个人心得摘录与总结
作者Melo_DDD分享了因栈数组类型设置为字符型导致RE的调试经历，提醒在编程中数据类型的选择至关重要，一个小错误可能浪费大量调试时间。 

---
处理用时：82.36秒