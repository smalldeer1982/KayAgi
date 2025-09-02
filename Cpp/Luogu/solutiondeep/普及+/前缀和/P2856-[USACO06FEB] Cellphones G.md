# 题目信息

# [USACO06FEB] Cellphones G

## 题目描述

The cows have started using cellphones to cowmunicate with each other, but have found that the button layout doesn't suit their hooves very well. They are designing a special cellphone with fewer but larger buttons.


One feature they liked on the standard cellphones was predictive text. Each button has a few letters associated with it, and one types a word by pushing the associated buttons. Because there is more than one letter for each button, this can be ambiguous for some words.  However, most of the time the ambiguity can be resolved by using a dictionary to determine what word the user wanted.


Since the cows are designing a custom cellphone, they are also going to replace the English alphabet with the Cow alphabet. By an amazing coincidence, the cow alphabet is simply the first L (1 <= L <= 26) letters of the English alphabet, in the same order. They want to find out how to assign the letters of the Cow alphabet to the B buttons (1 <= B <= L) in such a way that the maximum number of words in their dictionary are unambiguous when entered with predictive text. Like normal cellphones, they want the letters on each button to be a contiguous section (one or more consecutive letters) of the alphabet.

奶牛的名字都是由英文字母表的前1(1 < K 26)个字母构成的.现在想设计一种手机， 有个按键.请你把这L个字母按顺序分配给B个按键，使能够通过按这些键而唯一确 定的奶牛数尽量多.


## 说明/提示

Explanation of the sample:




Button 1 contains AB, button two contains C-K, and button 3 contains LM. The words CELL, DILL, FILL and FILM are all entered as 2233, while the remaining 7 words are all entered uniquely.


## 样例 #1

### 输入

```
3 13
11
ALL
BALL
BELL
CALK
CALL
CELL
DILL
FILL
FILM
ILL
MILK```

### 输出

```
7
AB
CDEFGHIJK
LM```

# AI分析结果

### 综合分析与结论
该题要求将前L个英文字母按顺序分配给B个按键，使能唯一确定的奶牛名字数最多。各题解主要围绕如何枚举字母分配方案及判断名字的唯一性展开。

### 所选的题解
- **作者：HPXXZYY (5星)**
    - **关键亮点**：思路清晰，采用搜索算法枚举每个字母分配到的按键，通过将字符串视为B + 1进制数计算hash值来判断名字的唯一性，同时考虑了多种方案下的输出要求。
    - **个人心得**：无
    - **核心代码片段**：
```cpp
void updata_answer(){
    memset(num,0,sizeof(num));
    for(int i=1;i<=n;i++)
        for(int j=0;j<str[i].size();j++)
            num[i]=num[i]*(B+1)+ch[str[i][j]-'A'+1];//计算hash值
    sort(num+1,num+n+1);
    register int tot=0;
    for(int i=1;i<=n;i++)
        if (num[i]!=num[i-1]&&num[i]!=num[i+1]) tot++;//计算有多少个不同的字符串
    if (tot>=ans){//注意这样才保证了答案字典序最小
        ans=tot;
        memcpy(CH,ch,sizeof(ch));
    }
}
void dfs(int sub,int color){
    if (sub>L){
        if (color>=B)
            updata_answer();
        return;
    }
    if (sub>1&&color<B){
        ch[sub]=color+1;
        dfs(sub+1,color+1);
    }
    if (color+L-sub>=B){
        ch[sub]=color;
        dfs(sub+1,color);
    }
    ch[sub]=-1;
}
```
    - **核心实现思想**：`updata_answer`函数通过计算每个名字字符串的hash值并排序，统计唯一的hash值个数来确定可唯一确定的名字数，并更新最优答案。`dfs`函数使用深度优先搜索枚举每个字母的按键分配方案。

### 最优关键思路或技巧
1. **搜索算法**：利用深度优先搜索枚举所有可能的字母按键分配方案，保证不遗漏任何情况。
2. **进制转换思想**：将字符串看作B + 1进制数计算hash值，巧妙地将字符串转化为数值以便于比较和判断唯一性。

### 可拓展之处
同类型题可拓展到其他字符分配问题，类似算法套路是通过搜索枚举所有可能分配方案，再利用合适的数据结构或方法判断分配方案的优劣。例如可拓展到将字符分配到不同容器，使满足特定条件的组合数最多等问题。

### 洛谷相似题目推荐
1. [P1157 组合的输出](https://www.luogu.com.cn/problem/P1157)：考察搜索算法枚举组合情况。
2. [P1036 [NOIP2002 普及组] 选数](https://www.luogu.com.cn/problem/P1036)：同样通过搜索枚举数字组合，判断是否满足特定条件。
3. [P1219 [USACO1.5]八皇后 Checker Challenge](https://www.luogu.com.cn/problem/P1219)：深度优先搜索经典题目，与本题搜索思路类似。 

---
处理用时：21.94秒