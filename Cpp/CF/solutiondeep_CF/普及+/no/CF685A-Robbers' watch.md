# 题目信息

# Robbers' watch

## 题目描述

Robbers, who attacked the Gerda's cab, are very successful in covering from the kingdom police. To make the goal of catching them even harder, they use their own watches.

First, as they know that kingdom police is bad at math, robbers use the positional numeral system with base $ 7 $ . Second, they divide one day in $ n $ hours, and each hour in $ m $ minutes. Personal watches of each robber are divided in two parts: first of them has the smallest possible number of places that is necessary to display any integer from $ 0 $ to $ n-1 $ , while the second has the smallest possible number of places that is necessary to display any integer from $ 0 $ to $ m-1 $ . Finally, if some value of hours or minutes can be displayed using less number of places in base $ 7 $ than this watches have, the required number of zeroes is added at the beginning of notation.

Note that to display number $ 0 $ section of the watches is required to have at least one place.

Little robber wants to know the number of moments of time (particular values of hours and minutes), such that all digits displayed on the watches are distinct. Help her calculate this number.

## 说明/提示

In the first sample, possible pairs are: $ (0:1) $ , $ (0:2) $ , $ (1:0) $ , $ (1:2) $ .

In the second sample, possible pairs are: $ (02:1) $ , $ (03:1) $ , $ (04:1) $ , $ (05:1) $ , $ (06:1) $ .

## 样例 #1

### 输入

```
2 3
```

### 输出

```
4
```

## 样例 #2

### 输入

```
8 2
```

### 输出

```
5
```

# AI分析结果

### 题目内容
# 劫匪的手表

## 题目描述
袭击格尔达马车的劫匪，在躲避王国警察追捕方面非常成功。为了让警察更难抓住他们，他们使用自己的手表。

首先，由于他们知道王国警察数学不好，劫匪使用七进制计数系统。其次，他们将一天分为 $n$ 小时，每小时分为 $m$ 分钟。每个劫匪的个人手表分为两部分：第一部分具有显示从 $0$ 到 $n - 1$ 中任何整数所需的最小位数，而第二部分具有显示从 $0$ 到 $m - 1$ 中任何整数所需的最小位数。最后，如果小时或分钟的某个值在七进制中可以用比手表所具有的更少的位数显示，则在表示的开头添加所需数量的零。

请注意，为了显示数字 $0$，手表的该部分至少需要有一位。

小劫匪想知道一天中有多少个时间点（特定的小时和分钟值），使得手表上显示的所有数字都不同。帮她计算这个数量。

## 说明/提示
在第一个示例中，可能的时间对为：$(0:1)$，$(0:2)$，$(1:0)$，$(1:2)$。

在第二个示例中，可能的时间对为：$(02:1)$，$(03:1)$，$(04:1)$，$(05:1)$，$(06:1)$。

## 样例 #1
### 输入
```
2 3
```
### 输出
```
4
```

## 样例 #2
### 输入
```
8 2
```
### 输出
```
5
```

### 算法分类
枚举

### 综合分析与结论
这几道题解的核心思路基本一致，均利用了七进制下数字显示的特点。由于七进制每位数字取值为0 - 6，若小时和分钟的七进制表示总位数大于7，必然存在重复数字，可直接输出0。然后通过暴力枚举所有可能的小时和分钟组合，利用一个函数检查每个组合在七进制下各位数字是否重复，若不重复则计数加1。不同之处在于部分题解使用了状压、数位DP等方式，但在实现效率上未体现出优势，反而暴力枚举的方式思路和代码都更简洁清晰。

### 所选的题解
- **作者：zhang_kevin (5星)**
    - **关键亮点**：思路清晰，代码简洁明了，直接暴力枚举所有时间组合，利用check函数判断七进制下各位数字是否重复，并且对小时和分钟位数和大于7的情况做了提前判断优化。
    - **重点代码 - 核心实现思想**：通过`check`函数标记每个数字出现次数，若有数字出现次数大于1则返回`false`。在`main`函数中，先处理输入并判断总位数情况，再枚举所有时间组合调用`check`函数统计符合条件的数量。
```cpp
bool check(int x, int y){
    for(int i = 0; i <= 6; i++) vis[i] = 0;
    for(int i = 1; i <= tx; i++) vis[x%7]++,x /= 7;
    for(int i = 1; i <= ty; i++) vis[y%7]++,y /= 7;
    for(int i = 0; i <= 6; i++) if(vis[i]>1) return false;
    return true;
}
int main() {
    scanf("%d%d", &x, &y);
    x--;
    y--;
    if(1ll*x*y>6543210){
        printf("0");
        return 0;
    }
    for(int i = x; i; i /= 7){
        tx++;
    }
    for(int i = y; i; i /= 7){
        ty++;
    }
    tx = Max(tx, 1);
    ty = Max(ty, 1);
    int ans = 0;
    for(int i = 0; i <= x; i++){
        for(int j = 0; j <= y; j++){
            if(check(i, j)){
                ans++;
            }
        }
    }
    printf("%d", ans);
    return 0;
}
```
- **作者：_Execution_ (4星)**
    - **关键亮点**：同样采用暴力枚举思路，代码逻辑清晰，变量命名直观，对小时和分钟位数和大于7的情况判断条件明确。
    - **重点代码 - 核心实现思想**：`check`函数与上一题解类似，通过数组`k`记录数字出现次数判断是否重复。`main`函数中先处理输入并判断，再双重循环枚举所有时间组合统计符合条件的数量。
```cpp
bool check(int x, int y) {
    for (int i = 0; i <= 6; i++)
        k[i] = 0;
    for (int i = 1; i <= x0; i++) {
        k[x % 7]++;
        x /= 7;
    }
    for (int i = 1; i <= y0; i++) {
        k[y % 7]++;
        y /= 7;
    }
    for (int i = 0; i <= 6; i++)
        if (k[i] > 1)
            return 0;
    return 1;
}
signed main() {
    cin>>x>>y;
    x--, y--;
    if (x * y > 6725600) {  
        puts("0");
        return 0;
    }
    for (int i = x; i; i /= 7) x0++;
    for (int i = y; i; i /= 7) y0++;
    x0 = max(x0, 1ll), y0 = max(y0, 1ll);
    for (int i = 0; i <= x; i++)
        for (int j = 0; j <= y; j++)
            if (check(i, j))
                ans++;
    cout<<ans<<"\n";
}
```
- **作者：Ryan_Adam (4星)**
    - **关键亮点**：对题意分析清晰，先阐述难点在理解题意，接着分析出七进制下总位数限制，代码实现中`check`函数逻辑明确，整体结构完整。
    - **重点代码 - 核心实现思想**：`check`函数通过数组`vis`记录数字出现次数判断是否重复。`main`函数先处理输入并判断总位数情况，再枚举所有时间组合调用`check`函数统计数量。
```cpp
bool check(int x,int y)
{
    int a=x,b=y;
    for(int i=0;i<=6;i++)
        vis[i]=0;
    for(int i=1;i<=xx;i++)
    {
        vis[a%7]++;
        a/=7;
    }
    for(int i=1;i<=yy;i++)
    {
        vis[b%7]++;
        b/=7;
    }
    for(int i=0;i<=6;i++)
        if(vis[i]>=2)
            return 0;
    return 1;
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>m;
    if(n*m>6543210)
    {
        cout<<0<<endl;
        return 0;
    }
    int nn=n,mm=m;
    n--,m--;
    while(n)
    {
        xx++;
        n/=7;
    }
    while(m)
    {
        yy++;
        m/=7;
    }
    xx=max(xx,1ll);
    yy=max(yy,1ll);
    int ans=0;
    for(int i=0;i<nn;i++)
        for(int j=0;j<mm;j++)
            if(check(i,j))
                ans++;
    cout<<ans<<endl;
    return 0;
}
```

### 最优关键思路或技巧
1. **利用七进制特性提前判断**：因为七进制下数字只有0 - 6，所以小时和分钟的七进制表示总位数若大于7，必然有重复数字，可直接输出0，减少不必要的枚举。
2. **暴力枚举结合检查函数**：通过双重循环枚举所有可能的小时和分钟组合，利用一个专门的函数检查该组合在七进制下各位数字是否重复，实现简单直接。

### 拓展
同类型题目通常围绕特定进制下数字的特性进行设计，比如判断数字是否满足某种排列组合条件，或是计算满足特定条件的数字个数等。类似算法套路就是先分析进制特性，再通过枚举结合条件判断来解决问题。

### 洛谷题目推荐
1. **P1143 进制转换**：通过不同进制间转换，加深对进制概念理解。
2. **P2089 烤鸡**：利用枚举解决组合计数问题，与本题枚举思路类似。
3. **P1036 [NOIP2002 普及组] 选数**：结合枚举与简单数学运算，锻炼枚举算法应用能力。 

---
处理用时：92.14秒