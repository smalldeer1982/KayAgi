# 题目信息

# Hot Black Hot White

## 题目描述

#### 题目大意
Dr. Chanek 有 $n$ 块魔法石，编号为 $1$ 至 $n$。第 Dr. Chanek 有 $n$ 块魔法石，编号为 $1$ 至 $n$。第 $i$ 块魔法石拥有 $a_i$ 的力量。Dr. Chanek 需要将 $n$ 块魔法石中的 $\frac{n}{2}$ 块染成黑色，另外 $\frac{n}{2}$ 块染成白色。

当第 $i$ 块魔法石和第 $j$ 块魔法石同时满足以下两个条件时，它们就会发生反应：

1. $color_i \ne color_j$（即两块石头颜色不同）

2. $\text{concat}(a_i,a_j) \times \text{concat}(a_j,a_i) + a_i \times a_j \equiv Z \mod 3$（即 $(\text{concat}(a_i,a_j) \times \text{concat}(a_j,a_i) + a_i \times a_j) \mod 3 = Z \mod 3$）

其中 $\text{concat}(x,y)$ 表示将十进制下的 $x$ 接在十进制下的 $y$ 的左边形成的新十进制数。例如，$\text{concat}(10,24) = 1024$。

因为魔法石发生反应时会很热很危险，所以你需要确定 $Z$ 的值和魔法石的染色方案，使任意一对魔法石之间都不产生反应。

## 样例 #1

### 输入

```
4
4 10 9 14```

### 输出

```
0
1001```

# AI分析结果

【题目内容】
# 热黑热白

## 题目描述

#### 题目大意
陈博士（Dr. Chanek）有 $n$ 块魔法石，编号为 $1$ 至 $n$。第 $i$ 块魔法石拥有 $a_i$ 的力量。陈博士需要将 $n$ 块魔法石中的 $\frac{n}{2}$ 块染成黑色，另外 $\frac{n}{2}$ 块染成白色。

当第 $i$ 块魔法石和第 $j$ 块魔法石同时满足以下两个条件时，它们就会发生反应：

1. $color_i \ne color_j$（即两块石头颜色不同）

2. $\text{concat}(a_i,a_j) \times \text{concat}(a_j,a_i) + a_i \times a_j \equiv Z \mod 3$（即 $(\text{concat}(a_i,a_j) \times \text{concat}(a_j,a_i) + a_i \times a_j) \mod 3 = Z \mod 3$）

其中 $\text{concat}(x,y)$ 表示将十进制下的 $x$ 接在十进制下的 $y$ 的左边形成的新十进制数。例如，$\text{concat}(10,24) = 1024$。

因为魔法石发生反应时会很热很危险，所以你需要确定 $Z$ 的值和魔法石的染色方案，使任意一对魔法石之间都不产生反应。

## 样例 #1

### 输入
```
4
4 10 9 14
```

### 输出
```
0
1001
```

【算法分类】
数学

【综合分析与结论】
- **思路对比**：各位大神的题解核心思路一致，都是先利用模 3 的性质化简反应条件式子，再根据 $a_i \bmod 3$ 中 0 的数量来确定 $Z$ 的值和染色方案。当 0 的数量较少时，将 0 都放在一组，$Z$ 取 0；当 0 的数量较多时，让 0 放满一组，$Z$ 取 2。
- **算法要点**：关键在于化简式子和对 $a_i \bmod 3$ 结果的分类讨论。通过分析 $a_i \bmod 3$ 和 $a_j \bmod 3$ 取不同值时反应式子的结果，来确定避免反应的策略。
- **解决难点**：难点在于式子的化简，需要利用模运算和数位和的性质将复杂的拼接运算转化为简单的加法和乘法运算。同时，要准确根据 0 的数量进行分类讨论，以找到合适的 $Z$ 值和染色方案。

【所选的题解】
- **作者：_•́へ•́╬_ (赞：7)，4星**
    - **关键亮点**：思路清晰，通过表格直观展示不同取值下式子的结果，方便理解分类讨论的依据。代码实现简洁，使用了快速读入优化。
    - **个人心得**：提到赛时漏加括号仍能通过，但重测时被毙掉，提醒大家注意代码的规范性。
- **作者：yingkeqian9217 (赞：4)，4星**
    - **关键亮点**：详细推导了式子的化简过程，逻辑严谨。对问题的转化描述清晰，将问题转化为 01 数的分组问题，便于理解。
- **作者：myEnd (赞：0)，4星**
    - **关键亮点**：代码结构清晰，使用 `vector` 存储不同余数的魔法石信息，方便后续处理。对分类讨论的情况处理详细，注释清晰。

【重点代码】
- **作者：_•́へ•́╬_**
```cpp
read(n);
for(int i=0;i<n;read(a[i]),++cnt[a[i++]%3]);
if(cnt[0]>n>>1)
{
    printf("2\n");
    for(int i=0,j=n>>1;i<n;++i)
        if(!(a[i]%3))
            if(j)putchar('0'),--j;
            else putchar('1');
        else putchar('1');
}
else
{
    printf("0\n");
    for(int i=0,j=(n>>1)-cnt[0];i<n;++i)
        if(a[i]%3)
            if(j)putchar('0'),--j;
            else putchar('1');
        else putchar('0');
}
```
**核心实现思想**：先统计 $a_i \bmod 3$ 中 0、1、2 的数量，再根据 0 的数量进行分类讨论，确定 $Z$ 的值和染色方案。

- **作者：yingkeqian9217**
```cpp
scanf("%d",&n);
for(int i=1;i<=n;i++){
    scanf("%d",&a[i]);
    int x=0;
    while(a[i]) x+=a[i]%10,a[i]/=10;
    a[i]=x;
    t[(a[i]*a[i])%3]++;
    col[i]=(a[i]*a[i])%3;
}
if(t[0]>t[1]){
    printf("%d\n",2);
    int cnt=n/2-t[1];
    for(int i=1;i<=n;i++)
        if(!col[i]&&cnt)
            col[i]=1,cnt--;
}
else{
    printf("%d\n",0);
    int cnt=n/2-t[0];
    for(int i=1;i<=n;i++)
        if(col[i]==1&&cnt)
            col[i]=0,cnt--;
}
for(int i=1;i<=n;i++)
    printf("%d",col[i]);
```
**核心实现思想**：先计算每个数的数位和，再统计 $x^2 \bmod 3$ 中 0 和 1 的数量，根据数量关系确定 $Z$ 的值和染色方案。

- **作者：myEnd**
```cpp
cin >> n;
for(register int i=1; i<=n; ++i)
{
    cin >> t;
    a[t%3].emplace_back(t, i);
}
t = a[0].size();
register int Z;
if(t >= n/2)
{
    for(register int i=0; i<n/2; ++i)
        ans[a[0][i].second] = 0;
    for(register int i=n/2; i<t; ++i)
        ans[a[0][i].second] = 1;
    for(register pair<int, int> x: a[1])
        ans[x.second] = 1;
    for(register pair<int, int> x: a[2])
        ans[x.second] = 1;
    Z = 2;
}
else
{
    for(register pair<int, int> x: a[0])
        ans[x.second] = 0;
    t = n/2 - t;
    register int i = 0, e = a[1].size();
    for(; i < e; ++i, --t)
    {
        if(t == 0) { break; }
        ans[a[1][i].second] = 0;
    }
    if(t == 0)
    {
        for(; i<e; ++i) ans[a[1][i].second] = 1;
        i = 0, e = a[2].size();
        for(; i<e; ++i) ans[a[2][i].second] = 1;
    }
    else
    {
        i = 0, e = a[2].size();
        for(; t && i<e; --t, ++i)
            ans[a[2][i].second] = 0;
        for(; i<e; ++i)
            ans[a[2][i].second] = 1;
    }
    Z = 0;
}
cout << Z << "\n";
for(register int i=1; i<=n; ++i) cout << ans[i];
```
**核心实现思想**：使用 `vector` 存储不同余数的魔法石信息，根据余数为 0 的魔法石数量进行分类讨论，确定 $Z$ 的值和染色方案。

【最优关键思路或技巧】
- **式子化简**：利用模 3 的性质和数位和的特点，将复杂的拼接运算转化为简单的加法和乘法运算，简化问题。
- **分类讨论**：根据 $a_i \bmod 3$ 中 0 的数量进行分类讨论，确定合适的 $Z$ 值和染色方案，避免魔法石之间发生反应。

【可拓展之处】
同类型题可能会改变模的数值或反应条件的式子，解题思路类似，关键在于对式子的化简和分类讨论。可以参考其他涉及模运算和分类讨论的数学问题，如一些数论相关的题目。

【推荐题目】
- [P1045 麦森数](https://www.luogu.com.cn/problem/P1045)：涉及高精度和数论知识，需要对指数运算和模运算有深入理解。
- [P1306 斐波那契公约数](https://www.luogu.com.cn/problem/P1306)：结合斐波那契数列和数论知识，需要运用数学推导和性质来解决问题。
- [P2613 有理数取余](https://www.luogu.com.cn/problem/P2613)：主要考察模运算和有理数的处理，需要掌握相关的数学知识和算法。

【个人心得摘录与总结】
- **作者：_•́へ•́╬_**：赛时漏加括号仍能通过，但重测时被毙掉。这提醒我们在编写代码时要注意代码的规范性和严谨性，避免因小错误导致不必要的失分。

---
处理用时：61.22秒