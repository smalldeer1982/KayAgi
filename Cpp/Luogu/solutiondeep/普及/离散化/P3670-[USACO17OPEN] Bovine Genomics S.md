# 题目信息

# [USACO17OPEN] Bovine Genomics S

## 题目描述

Farmer John 拥有 $N$ 头有斑点的牛和 $N$ 头没有斑点的牛。他刚刚完成了一门关于牛遗传学的课程，并确信他牛身上的斑点是由牛基因组中的突变引起的。

Farmer John 花费巨资对他的牛进行了基因组测序。每个基因组是一个由字符 A、C、G 和 T 组成的长度为 $M$ 的字符串。当他将牛的基因组排列起来时，会得到如下表格，这里展示的是 $N=3$ 的情况：

```
位置：1 2 3 4 5 6 7 ... M

斑点牛 1：A A T C C C A ... T  
斑点牛 2：G A T T G C A ... A  
斑点牛 3：G G T C G C A ... A  

普通牛 1：A C T C C C A ... G  
普通牛 2：A G T T G C A ... T  
普通牛 3：A G T T C C A ... T 
```

仔细观察这个表格后，他推测位置 2 和 4 足以解释斑点现象。也就是说，通过仅查看这两个位置的字符，Farmer John 可以预测哪些牛是有斑点的，哪些是没有斑点的（例如，如果他看到 G 和 C，这头牛一定是有斑点的）。

Farmer John 确信，斑点现象不仅仅可以通过基因组中的一个或两个位置来解释，而是可以通过查看三个不同的位置来解释。请帮助他计算能够解释斑点现象的三个不同位置集合的数量。

## 样例 #1

### 输入

```
3 8
AATCCCAT
GATTGCAA
GGTCGCAA
ACTCCCAG
ACTCGCAT
ACTTCCAT```

### 输出

```
22```

# AI分析结果

### 综合分析与结论
这些题解核心思路一致，均是先枚举三个位置的三元组，再判断该三元组是否能区分有斑点和无斑点的牛。不同题解在存储和判断字符组合时采用了不同方法，如哈希表、三维数组、`set` 等。

### 所选题解
- **作者：YBaggio（5星）**
    - **关键亮点**：思路清晰，详细阐述了从暴力解法到优化的过程，代码注释丰富，可读性强。
    - **核心代码**：
```cpp
void hashS(int fir,int sec,int thi){
    memset(HashS,0,sizeof(HashS));
    for(int i=1;i<=n;i++){
        int tmp=(S[i][fir]-'A'+1)+(S[i][sec]-'A'+1)*26+(S[i][thi]-'A'+1)*26*26;
        HashS[tmp]=1;
    }
    return;
}
void hashP(int fir,int sec,int thi){
    memset(HashP,0,sizeof(HashP));
    for(int i=1;i<=n;i++){
        int tmp=(P[i][fir]-'A'+1)+(P[i][sec]-'A'+1)*26+(P[i][thi]-'A'+1)*26*26;
        HashP[i]=tmp;
    }
    return;
}
```
    - **核心思想**：通过自定义哈希函数将三个位置的字符组合映射为一个整数，存储在哈希数组中，方便后续判断。

- **作者：Lolierl（4星）**
    - **关键亮点**：思路简洁，使用三维数组打钩的方式判断字符组合是否重复，代码简单易懂。
    - **核心代码**：
```cpp
int get(char x)
{
    if(x=='A')return 1;
    if(x=='C')return 2;
    if(x=='G')return 3;
    if(x=='T')return 4;
}
int t[5][5][5];
for(int i=1;i<=m-2;i++)
    for(int j=i+1;j<=m-1;j++)
        for(int k=j+1;k<=m;k++)
        {
            bool f=true;
            memset(t,0,sizeof(t));
            for(int x1=1;x1<=n;x1++)
                t[a[x1][i]][a[x1][j]][a[x1][k]]=1;
            for(int x2=1;x2<=n;x2++)
                if(t[b[x2][i]][b[x2][j]][b[x2][k]]){f=false;break;}
            if(f)ans++;
        }
```
    - **核心思想**：将字符映射为数字，使用三维数组记录有斑点牛的字符组合，再检查无斑点牛的字符组合是否重复。

- **作者：foryou_（4星）**
    - **关键亮点**：详细分析题意，代码结构清晰，将字符映射为数字存储，方便后续操作。
    - **核心代码**：
```cpp
bool check(int x,int y,int z){
    memset(vis,0,sizeof(vis));
    for(int i=1;i<=n;i++)
        vis[a[i][x]][a[i][y]][a[i][z]]=1;
    for(int i=1;i<=n;i++)
        if(vis[b[i][x]][b[i][y]][b[i][z]])
            return 0;
    return 1;
}
for(int i=1;i<=m;i++)
    for(int j=i+1;j<=m;j++)
        for(int k=j+1;k<=m;k++)
            if(check(i,j,k)) ans++;
```
    - **核心思想**：定义 `check` 函数判断三元组是否合法，通过标记数组记录有斑点牛的字符组合，再检查无斑点牛的字符组合是否重复。

### 最优关键思路或技巧
- **字符映射**：将字符 `A`、`C`、`G`、`T` 映射为数字，方便存储和比较。
- **哈希优化**：使用哈希表或三维数组记录字符组合，将判断重复的时间复杂度优化到 $O(1)$。

### 拓展思路
同类型题可考察从多个字符串中找出满足特定条件的位置组合，如判断多个字符串在某些位置上的字符组合是否唯一等。类似算法套路为枚举位置组合，使用合适的数据结构记录和判断字符组合是否重复。

### 推荐题目
- [P1008 三连击](https://www.luogu.com.cn/problem/P1008)：枚举组合并判断是否满足条件。
- [P1217 [USACO1.5]回文质数 Prime Palindromes](https://www.luogu.com.cn/problem/P1217)：枚举数字并判断是否满足回文和质数的条件。
- [P1618 三连击（升级版）](https://www.luogu.com.cn/problem/P1618)：枚举组合并判断是否满足特定比例关系。

### 个人心得摘录与总结
- **作者：45dino**：使用 `map` 存储字符组合时出现 TLE，改用 `scanf` 并吸氧后通过。总结：在处理大数据输入时，`scanf` 比 `cin` 效率更高，必要时可使用吸氧优化。
- **作者：Kalium**：题面理解花费 1 小时，代码编写仅需 15 分钟。总结：做题前需仔细理解题意，避免因理解错误浪费时间。 

---
处理用时：36.14秒