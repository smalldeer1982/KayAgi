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
本题要求将英文字母表的前 $L$ 个字母按顺序分配给 $B$ 个按键，使得能通过按这些键唯一确定的奶牛名字数量最多。题解采用暴力枚举结合搜索算法，通过 $dfs$ 枚举每个字母分配给哪个按键，再用 $hash$ 计算每个名字对应的键值，统计唯一确定的名字数量。

### 所选题解
- **星级**：4星
- **关键亮点**：思路清晰，详细说明了搜索和 $hash$ 计算的过程，代码注释较详细，且考虑了答案字典序最小的情况。
- **个人心得**：无

### 重点代码及核心实现思想
```cpp
// 计算 hash 值
void updata_answer(){
    memset(num,0,sizeof(num));
    for(int i=1;i<=n;i++)
        for(int j=0;j<str[i].size();j++)
            num[i]=num[i]*(B+1)+ch[str[i][j]-'A'+1];//计算 hash 值
    sort(num+1,num+n+1);
    register int tot=0;
    for(int i=1;i<=n;i++)
        if (num[i]!=num[i-1]&&num[i]!=num[i+1]) tot++;//计算有多少个不同的字符串
    if (tot>=ans){//注意这样才保证了答案字典序最小
        ans=tot;
        memcpy(CH,ch,sizeof(ch));
    }
}

// 深度优先搜索枚举字母分配
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
核心实现思想：
- `updata_answer` 函数：计算每个名字对应的 $hash$ 值，将名字视为 $B + 1$ 进制数。对 $hash$ 值排序后，统计只出现一次的 $hash$ 值数量，更新最大唯一确定名字数量和最佳分配方案。
- `dfs` 函数：通过深度优先搜索枚举每个字母分配给哪个按键，确保字母按顺序分配且使用的按键数不超过 $B$。

### 可拓展之处
同类型题或类似算法套路：
- 此类问题可拓展到其他分配问题，如将物品按顺序分配到不同组，使满足某种条件的组合最优。
- 搜索算法可结合剪枝优化，减少不必要的枚举。

### 推荐题目
- [P1036 选数](https://www.luogu.com.cn/problem/P1036)：通过搜索枚举组合，判断满足条件的组合数量。
- [P1135 奇怪的电梯](https://www.luogu.com.cn/problem/P1135)：使用广度优先搜索解决状态转移问题。
- [P1433 吃奶酪](https://www.luogu.com.cn/problem/P1433)：通过搜索枚举路径，找到最短路径。 

---
处理用时：19.36秒