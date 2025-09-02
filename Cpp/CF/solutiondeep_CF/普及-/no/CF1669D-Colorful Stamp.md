# 题目信息

# Colorful Stamp

## 题目描述

A row of $ n $ cells is given, all initially white. Using a stamp, you can stamp any two neighboring cells such that one becomes red and the other becomes blue. A stamp can be rotated, i.e. it can be used in both ways: as $ \color{blue}{\texttt{B}}\color{red}{\texttt{R}} $ and as $ \color{red}{\texttt{R}}\color{blue}{\texttt{B}} $ .

During use, the stamp must completely fit on the given $ n $ cells (it cannot be partially outside the cells). The stamp can be applied multiple times to the same cell. Each usage of the stamp recolors both cells that are under the stamp.

For example, one possible sequence of stamps to make the picture $ \color{blue}{\texttt{B}}\color{red}{\texttt{R}}\color{blue}{\texttt{B}}\color{blue}{\texttt{B}}\texttt{W} $ could be $ \texttt{WWWWW} \to \texttt{WW}\color{brown}{\underline{\color{red}{\texttt{R}}\color{blue}{\texttt{B}}}}\texttt{W} \to \color{brown}{\underline{\color{blue}{\texttt{B}}\color{red}{\texttt{R}}}}\color{red}{\texttt{R}}\color{blue}{\texttt{B}}\texttt{W} \to \color{blue}{\texttt{B}}\color{brown}{\underline{\color{red}{\texttt{R}}\color{blue}{\texttt{B}}}}\color{blue}{\texttt{B}}\texttt{W} $ . Here $ \texttt{W} $ , $ \color{red}{\texttt{R}} $ , and $ \color{blue}{\texttt{B}} $ represent a white, red, or blue cell, respectively, and the cells that the stamp is used on are marked with an underline.

Given a final picture, is it possible to make it using the stamp zero or more times?

## 说明/提示

The first test case is explained in the statement.

For the second, third, and fourth test cases, it is not possible to stamp a single cell, so the answer is "NO".

For the fifth test case, you can use the stamp as follows: $ \texttt{WWW} \to \texttt{W}\color{brown}{\underline{\color{red}{\texttt{R}}\color{blue}{\texttt{B}}}} \to \color{brown}{\underline{\color{blue}{\texttt{B}}\color{red}{\texttt{R}}}}\color{blue}{\texttt{B}} $ .

For the sixth test case, you can use the stamp as follows: $ \texttt{WWW} \to \texttt{W}\color{brown}{\underline{\color{red}{\texttt{R}}\color{blue}{\texttt{B}}}} \to \color{brown}{\underline{\color{red}{\texttt{R}}\color{blue}{\texttt{B}}}}\color{blue}{\texttt{B}} $ .

For the seventh test case, you don't need to use the stamp at all.

## 样例 #1

### 输入

```
12
5
BRBBW
1
B
2
WB
2
RW
3
BRB
3
RBB
7
WWWWWWW
9
RBWBWRRBW
10
BRBRBRBRRB
12
BBBRWWRRRWBR
10
BRBRBRBRBW
5
RBWBW```

### 输出

```
YES
NO
NO
NO
YES
YES
YES
NO
YES
NO
YES
NO```

# AI分析结果

### 题目内容
# 彩色印章

## 题目描述
给定一排 $n$ 个单元格，初始时均为白色。使用一个印章，你可以对任意两个相邻单元格进行盖章，使得其中一个变为红色，另一个变为蓝色。印章可以旋转，即它可以以两种方式使用：$\color{blue}{\texttt{B}}\color{red}{\texttt{R}}$ 和 $\color{red}{\texttt{R}}\color{blue}{\texttt{B}}$。
在使用过程中，印章必须完全覆盖给定的 $n$ 个单元格（不能部分在单元格外部）。印章可以多次应用于同一单元格。每次使用印章都会重新为印章覆盖的两个单元格上色。
例如，要得到 $\color{blue}{\texttt{B}}\color{red}{\texttt{R}}\color{blue}{\texttt{B}}\color{blue}{\texttt{B}}\texttt{W}$ 这一图案，一种可能的印章使用顺序为 $\texttt{WWWWW} \to \texttt{WW}\color{brown}{\underline{\color{red}{\texttt{R}}\color{blue}{\texttt{B}}}}\texttt{W} \to \color{brown}{\underline{\color{blue}{\texttt{B}}\color{red}{\texttt{R}}}}\color{red}{\texttt{R}}\color{blue}{\texttt{B}}\texttt{W} \to \color{blue}{\texttt{B}}\color{brown}{\underline{\color{red}{\texttt{R}}\color{blue}{\texttt{B}}}}\color{blue}{\texttt{B}}\texttt{W}$ 。这里 $\texttt{W}$，$\color{red}{\texttt{R}}$ 和 $\color{blue}{\texttt{B}}$ 分别代表白色、红色或蓝色单元格，并且使用印章的单元格用下划线标记。
给定一个最终图案，是否可以通过零次或多次使用印章来实现它？

## 说明/提示
第一个测试用例在题目描述中有解释。
对于第二、第三和第四个测试用例，无法对单个单元格盖章，所以答案是“NO”。
对于第五个测试用例，你可以按如下方式使用印章：$\texttt{WWW} \to \texttt{W}\color{brown}{\underline{\color{red}{\texttt{R}}\color{blue}{\texttt{B}}}} \to \color{brown}{\underline{\color{blue}{\texttt{B}}\color{red}{\texttt{R}}}}\color{blue}{\texttt{B}}$ 。
对于第六个测试用例，你可以按如下方式使用印章：$\texttt{WWW} \to \texttt{W}\color{brown}{\underline{\color{red}{\texttt{R}}\color{blue}{\texttt{B}}}} \to \color{brown}{\underline{\color{red}{\texttt{R}}\color{blue}{\texttt{B}}}}\color{blue}{\texttt{B}}$ 。
对于第七个测试用例，根本无需使用印章。

## 样例 #1
### 输入
```
12
5
BRBBW
1
B
2
WB
2
RW
3
BRB
3
RBB
7
WWWWWWW
9
RBWBWRRBW
10
BRBRBRBRRB
12
BBBRWWRRRWBR
10
BRBRBRBRBW
5
RBWBW
```
### 输出
```
YES
NO
NO
NO
YES
YES
YES
NO
YES
NO
YES
NO
```

### 算法分类
字符串

### 题解综合分析与结论
三道题解思路本质相同，均是利用每次盖章操作针对两个相邻单元格且能产生“R”和“B”的特性，将给定字符串按“W”分割成若干子串，判断每个子串是否同时包含“R”和“B”，若所有子串都满足则有解，否则无解。

不同点在于实现细节，“GI录像机”通过遍历字符串统计“R”和“B”的数量及连续性来判断；“0xFF”和“happy_dengziyue”先找出由“W”分隔的子串，再分别判断子串内是否同时有“R”和“B”，后两者思路更直观清晰。

### 所选的题解
- **作者：0xFF (4星)**
    - **关键亮点**：代码逻辑清晰，通过`read`函数读取输入，利用数组`arr`记录“W”的位置来划分由“R”和“B”组成的子串，然后遍历子串判断是否同时包含“R”和“B”。
    - **核心代码**：
```cpp
int T = read();
while(T--){
    int n = read();
    scanf("%s",str+1);
    cnt=0;
    arr[++cnt]=0;
    for(int i=1,nw=0;i<=n;i++){
        if(str[i]=='W') arr[++cnt]=i;
    }
    bool flag = 1;
    arr[++cnt] = n+1;
    for(int i=1;i<cnt;i++){
        bool r = 0,b = 0;
        if(arr[i] + 1 > arr[i+1] - 1) continue;
        for(int j=arr[i]+1;j<=arr[i+1]-1;j++){
            if(str[j] == 'R') r = 1;
            if(str[j] == 'B') b = 1; 
        }
        if(!r ||!b) flag = 0;
        if(flag==0) break;
    }
    if(flag==0) printf("NO\n");
    else printf("YES\n");
}
```
    - **核心实现思想**：先记录“W”位置划分出子串，再遍历每个子串判断是否同时存在“R”和“B”，根据结果输出“YES”或“NO”。

- **作者：happy_dengziyue (4星)**
    - **关键亮点**：提出“极大子串”概念，逻辑清晰。代码简洁明了，通过`a`数组记录“W”位置划分极大子串，然后判断每个极大子串是否同时包含“R”和“B”。
    - **核心代码**：
```cpp
scanf("%d",&t);
while(t--){
    scanf("%d%s",&n,s+1);
    a[ai=1]=0;
    for(int i=1;i<=n;++i){
        if(s[i]=='W')a[++ai]=i;
    }
    a[++ai]=n+1;
    ans=true;
    for(int i=1;i<ai;++i){
        if(a[i+1]-a[i]<=1)continue;
        ansr=false;
        ansb=false;
        for(int j=a[i]+1;j<a[i+1];++j){
            if(s[j]=='R')ansr=true;
            if(s[j]=='B')ansb=true;
        }
        if((!ansr)||(!ansb)){
            ans=false;
            break;
        }
    }
    if(ans)printf("YES\n");
    else printf("NO\n");
}
```
    - **核心实现思想**：与“0xFF”类似，记录“W”位置划分极大子串，遍历判断极大子串是否同时有“R”和“B”来确定结果。

### 最优关键思路或技巧
将原字符串按“W”分割成子串的方式简化了问题，聚焦于子串内部的字符组成判断，避免了对整体复杂字符串的直接处理，使得问题解决思路更加清晰直观。

### 同类型题或类似算法套路拓展
此类题目通常围绕字符串特定操作和状态判断，套路是分析操作对字符串特征的影响，通过划分、统计等手段找出可解的条件。例如对于一些字符串变换问题，可先分析每次变换对字符分布、位置等的影响，再据此设计判断方法。

### 洛谷相似题目推荐
- [P1308 统计单词数](https://www.luogu.com.cn/problem/P1308)：涉及字符串查找与统计，与本题类似需对字符串进行特定分析。
- [P1593 因子和阶乘](https://www.luogu.com.cn/problem/P1593)：虽涉及数学运算，但同样需对输入数据（可看作特殊字符串）进行分析处理。
- [P1914 小书童——密码](https://www.luogu.com.cn/problem/P1914)：字符串加密解密问题，需分析字符串操作规则来实现功能。 

---
处理用时：64.45秒