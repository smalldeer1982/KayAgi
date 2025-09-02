# 题目信息

# Filling the Grid

## 题目描述

Suppose there is a $ h \times w $ grid consisting of empty or full cells. Let's make some definitions:

- $ r_{i} $ is the number of consecutive full cells connected to the left side in the $ i $ -th row ( $ 1 \le i \le h $ ). In particular, $ r_i=0 $ if the leftmost cell of the $ i $ -th row is empty.
- $ c_{j} $ is the number of consecutive full cells connected to the top end in the $ j $ -th column ( $ 1 \le j \le w $ ). In particular, $ c_j=0 $ if the topmost cell of the $ j $ -th column is empty.

In other words, the $ i $ -th row starts exactly with $ r_i $ full cells. Similarly, the $ j $ -th column starts exactly with $ c_j $ full cells.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1228B/718cfa57d80806dbeecabcc145703169da7deb79.png)These are the $ r $ and $ c $ values of some $ 3 \times 4 $ grid. Black cells are full and white cells are empty.You have values of $ r $ and $ c $ . Initially, all cells are empty. Find the number of ways to fill grid cells to satisfy values of $ r $ and $ c $ . Since the answer can be very large, find the answer modulo $ 1000000007\,(10^{9} + 7) $ . In other words, find the remainder after division of the answer by $ 1000000007\,(10^{9} + 7) $ .

## 说明/提示

In the first example, this is the other possible case.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1228B/9d1150639137da10f3c33f0f1362034ed19afeb9.png)In the second example, it's impossible to make a grid to satisfy such $ r $ , $ c $ values.

In the third example, make sure to print answer modulo $ (10^9 + 7) $ .

## 样例 #1

### 输入

```
3 4
0 3 1
0 2 3 0
```

### 输出

```
2
```

## 样例 #2

### 输入

```
1 1
0
1
```

### 输出

```
0
```

## 样例 #3

### 输入

```
19 16
16 16 16 16 15 15 0 5 0 4 9 9 1 4 4 0 8 16 12
6 12 19 15 8 6 19 19 14 6 9 16 10 11 15 4
```

### 输出

```
797922655
```

# AI分析结果

### 题目内容
# 填充网格

## 题目描述
假设有一个$h \times w$的网格，由空单元格或满单元格组成。我们给出一些定义：
- $r_{i}$是第$i$行中与左侧相连的连续满单元格的数量（$1 \le i \le h$）。特别地，如果第$i$行最左侧的单元格为空，则$r_i = 0$。
- $c_{j}$是第$j$列中与顶端相连的连续满单元格的数量（$1 \le j \le w$）。特别地，如果第$j$列最顶端的单元格为空，则$c_j = 0$。

换句话说，第$i$行恰好以$r_i$个满单元格开始。类似地，第$j$列恰好以$c_j$个满单元格开始。

![示例](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1228B/718cfa57d80806dbeecabcc145703169da7deb79.png)
这是某个$3 \times 4$网格的$r$和$c$值。黑色单元格为满，白色单元格为空。
你已知$r$和$c$的值。最初，所有单元格都是空的。求填充网格单元格以满足$r$和$c$值的方法数量。由于答案可能非常大，求答案对$1000000007\,(10^{9} + 7)$取模的结果。换句话说，求答案除以$1000000007\,(10^{9} + 7)$后的余数。

## 说明/提示
在第一个示例中，这是另一种可能的情况。

![示例](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1228B/9d1150639137da10f3c33f0f1362034ed19afeb9.png)
在第二个示例中，不可能构造出满足这样$r$、$c$值的网格。

在第三个示例中，确保输出答案对$(10^9 + 7)$取模的结果。

## 样例 #1
### 输入
```
3 4
0 3 1
0 2 3 0
```
### 输出
```
2
```

## 样例 #2
### 输入
```
1 1
0
1
```
### 输出
```
0
```

## 样例 #3
### 输入
```
19 16
16 16 16 16 15 15 0 5 0 4 9 9 1 4 4 0 8 16 12
6 12 19 15 8 6 19 19 14 6 9 16 10 11 15 4
```
### 输出
```
797922655
```

### 算法分类
组合数学

### 综合分析与结论
这些题解的核心思路一致，都是先根据给定的$r$和$c$值对网格进行填充，在填充过程中检查是否存在冲突，若有冲突则方案数为$0$；若无冲突，统计未被限制的格子数量$k$，利用组合数学知识，这些未限制格子每个都有两种填充状态，所以满足要求的方案数为$2^k$ 。不同题解在实现细节上略有差异，如标记方式、幂运算实现等。

### 所选的题解
- **作者：Katsura_Hinagiku (5星)**
    - **关键亮点**：思路清晰，代码简洁明了，通过一次遍历完成对网格的填充与冲突检查，使用快速幂函数高效计算$2^k$。
    - **重点代码 - 核心实现思想**：用二维数组`mp`表示网格，先按行填充，再按列填充并检查冲突，最后统计未染色格子并通过快速幂计算方案数。
```cpp
ll ksm(ll basic,ll mi)
{
    ll tmp=1;
    while(mi)
    {
        if(mi&1)tmp=tmp*basic%MOD;
        mi>>=1;
        basic=basic*basic%MOD;
    }
    return tmp;
}
int main()
{
    memset(mp,-1,sizeof(mp));
    scanf("%d%d",&h,&w);
    for(int i=1;i<=h;++i)
    {
        int kk;
        scanf("%d",&kk);
        for(int j=1;j<=kk;++j)mp[i][j]=1;
        mp[i][kk+1]=0;
    }
    for(int i=1;i<=w;++i)
    {
        int kk;
        scanf("%d",&kk);
        for(int j=1;j<=kk;++j)
        {
            if(mp[j][i]==0)
            {
                printf("0\n");
                return 0;
            }
            mp[j][i]=1;
        }
        if(mp[kk+1][i]==1)
        {
            printf("0\n");
            return 0;
        }
        mp[kk+1][i]=0;
    }
    for(int i=1;i<=h;++i)
    {
        for(int j=1;j<=w;++j)
        {
            if(mp[i][j]==-1)++cnt;
        }
    }
    printf("%d\n",ksm(2,cnt));
    return 0;
}
```
- **作者：andyli (4星)**
    - **关键亮点**：代码逻辑清晰，通过`vis`数组标记单元格是否处理过，`m`数组记录单元格状态，在填充过程中及时检查冲突。
    - **重点代码 - 核心实现思想**：按行和列的要求依次填充并检查冲突，最后遍历未处理的单元格计算方案数。
```cpp
bool vis[maxn][maxn], m[maxn][maxn];
int main()
{
    int h, w;
    io.read(h, w);
    for (int i = 0; i < h; i++) {
        int t;
        io.read(t);
        for (int j = 0; j <= t; j++) {
            if (j < t) 
                if (vis[i][j] &&!m[i][j]) 
                    ns();
                else
                    vis[i][j] = true, m[i][j] = true;
            else if (vis[i][j] && m[i][j]) 
                ns();
            else
                vis[i][j] = true;
        }
    }
    for (int i = 0; i < w; i++) {
        int t;
        io.read(t);
        for (int j = 0; j <= t; j++) {
            if (j < t) 
                if (vis[j][i] &&!m[j][i]) 
                    ns();
                else
                    vis[j][i] = true, m[j][i] = true;
            else if (vis[j][i] && m[j][i]) 
            else
                vis[j][i] = true;
        }
    }
    int ans = 1;
    for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++)
            if (!vis[i][j]) 
                ans = (ans << 1) % MOD;
    writeln(ans);
    return 0;
}
```
- **作者：Steven_Meng (4星)**
    - **关键亮点**：代码简洁，通过`memset`初始化数组，在填充过程中直接检查冲突，最后统计未染色格子计算方案数。
    - **重点代码 - 核心实现思想**：按行和列要求填充网格，检查冲突，遍历未染色格子计算$2^k$。
```cpp
int main(){
    int h=read(),w=read();
    memset(a,-1,sizeof(a));
    for (register int i=1;i<=h;++i){
        int len=read();
        for (register int j=1;j<=len;++j){
            if (a[i][j]==0){
                puts("0");
                return 0;
            }
            a[i][j]=1;
        }
        if (a[i][len+1]==1){
            puts("0");
            return 0;
        }
        a[i][len+1]=0;
    }
    for (register int i=1;i<=w;++i){
        int len=read();
        for (register int j=1;j<=len;++j){
            if (a[j][i]==0){
                puts("0");
                return 0;
            }
            a[j][i]=1;
        }
        if (a[len+1][i]==1){
            puts("0");
            return 0;
        }
        a[len+1][i]=0;
    }
    long long ans=1;
    for (register int i=1;i<=h;++i){
        for (register int j=1;j<=w;++j){
            if (a[i][j]==-1) ans=(ans*2ll)%((long long)1e9+7);
        }
    }
    printf("%lld\n",ans);
}
```

### 最优关键思路或技巧
1. **利用组合数学原理**：认识到未被限制的格子每个都有两种填充状态，从而得出方案数为$2$的未限制格子数幂次方。
2. **按行和列顺序填充检查**：先按行的要求填充并标记，再按列的要求填充，在填充过程中及时检查是否存在冲突，这种顺序处理方式简洁高效。

### 拓展思路
同类型题通常围绕网格填充、条件限制下的方案计数等。类似算法套路是先根据给定条件对目标对象进行初步构建，在构建过程中检查冲突，然后对未被条件完全限制的部分，利用组合数学知识计算方案数。

### 洛谷相似题目
1. **P1313 计算系数**：涉及二项式定理相关的组合数学计算，与本题利用组合数学原理计算方案数类似。
2. **P2822 [NOIP2016 提高组] 组合数问题**：通过预处理组合数并结合模运算解决问题，与本题计算方案数并取模有相似之处。
3. **P3807 【模板】卢卡斯定理**：考查卢卡斯定理在组合数取模计算中的应用，和本题在计算方案数时对大数取模有一定关联。 

---
处理用时：96.80秒