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

• 综合分析与结论：这些题解思路大致相同，均利用题目数据范围小的特点，通过 $O(m^3)$ 的三重循环枚举三个位置，再用 $O(n)$ 的时间判断该三元组是否合法，即判断斑点牛和无斑点牛在这三个位置的字符组合是否重复。判断重复的方法主要有哈希表、三维数组标记、map 等方式。在代码实现上，部分题解在输入处理、优化等方面略有差异。

所选的题解：
  - **作者：YBaggio (5星)**
    - **关键亮点**：思路清晰，从时间复杂度分析入手，先考虑暴力判断的方法，再优化到使用哈希数组判断，对哈希的使用讲解详细。
    - **重点代码 - 核心实现思想**：通过两个函数 `hashS` 和 `hashP` 分别计算斑点牛和无斑点牛在三个位置的哈希值，并存入对应的哈希数组，最后通过判断无斑点牛的哈希值是否在斑点牛的哈希数组中出现过，来确定三元组是否合法。
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
//...
for(fir=1;fir<=m;fir++){
    for(sec=fir+1;sec<=m;sec++){
        for(thi=sec+1;thi<=m;thi++){
            bool flag=0;
            hashS(fir,sec,thi);
            hashP(fir,sec,thi);
            for(int i=1;i<=n;i++){
                if(HashS[HashP[i]]){flag=1;break;}
            }
            if(flag)continue;
            B[fir][sec][thi]=1;
        }
    }
}
```
  - **作者：Lolierl (4星)**
    - **关键亮点**：提出用类似离散化的方式打钩，即使用三维数组标记的方法，代码简洁明了，空间换时间，在数据范围允许的情况下是一种高效做法。
    - **重点代码 - 核心实现思想**：利用 `get` 函数将字符转化为数字，通过三重循环枚举三个位置，在内部循环中对斑点牛的三个位置字符组合进行标记，再检查无斑点牛的对应组合是否被标记，若未被标记则答案加一。
```cpp
int get(char x)
{
    if(x=='A')return 1;
    if(x=='C')return 2;
    if(x=='G')return 3;
    if(x=='T')return 4;
}
//...
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
  - **作者：foryou_ (4星)**
    - **关键亮点**：分析详细，对题意理解准确，代码结构清晰，通过建立标记数组 `vis` 来判断三元组是否合法，逻辑清晰易懂。
    - **重点代码 - 核心实现思想**：先将字符映射为数字，存入整数矩阵 `a` 和 `b`。通过 `check` 函数检查三元组，先标记斑点牛的字符组合，再检查无斑点牛的组合是否已被标记，若未被标记则三元组合法。
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
//...
for(int i=1;i<=m;i++) 
    for(int j=i+1;j<=m;j++)
        for(int k=j+1;k<=m;k++)
            if(check(i,j,k)) ans++; 
```

• **最优关键思路或技巧**：利用数据范围小的特点采用暴力枚举三元组位置，通过哈希表、三维数组标记等方式快速判断斑点牛和无斑点牛在这些位置的字符组合是否重复，以确定三元组是否合法。

• **可拓展之处**：同类型题可考虑数据范围增大的情况，此时暴力枚举可能不再适用，可探索更高效的算法，如利用前缀和、二分查找等优化判断过程。类似算法套路为枚举可能的组合，再快速判断组合是否满足特定条件。

• **推荐洛谷题目**：
  - [P1118 数字三角形](https://www.luogu.com.cn/problem/P1118)：涉及简单的动态规划和枚举思想，与本题枚举判断思路类似。
  - [P1036 [NOIP2002 普及组] 选数](https://www.luogu.com.cn/problem/P1036)：同样需要枚举组合并判断是否满足条件，锻炼枚举与判断的能力。
  - [P1433 吃奶酪](https://www.luogu.com.cn/problem/P1433)：通过枚举路径并计算距离来寻找最优解，与本题枚举判断的思维方式相似。

• **个人心得摘录与总结**：部分作者提到题面理解花费时间，强调了仔细审题的重要性。还有作者遇到代码超时问题，通过改用 `scanf` 等方式优化，说明在做题时要注意输入输出方式对效率的影响，以及代码优化的重要性。 

---
处理用时：30.91秒