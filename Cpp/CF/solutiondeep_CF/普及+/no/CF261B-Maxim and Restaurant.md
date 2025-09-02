# 题目信息

# Maxim and Restaurant

## 题目描述

Maxim has opened his own restaurant! The restaurant has got a huge table, the table's length is $ p $ meters.

Maxim has got a dinner party tonight, $ n $ guests will come to him. Let's index the guests of Maxim's restaurant from 1 to $ n $ . Maxim knows the sizes of all guests that are going to come to him. The $ i $ -th guest's size ( $ a_{i} $ ) represents the number of meters the guest is going to take up if he sits at the restaurant table.

Long before the dinner, the guests line up in a queue in front of the restaurant in some order. Then Maxim lets the guests in, one by one. Maxim stops letting the guests in when there is no place at the restaurant table for another guest in the queue. There is no place at the restaurant table for another guest in the queue, if the sum of sizes of all guests in the restaurant plus the size of this guest from the queue is larger than $ p $ . In this case, not to offend the guest who has no place at the table, Maxim doesn't let any other guest in the restaurant, even if one of the following guests in the queue would have fit in at the table.

Maxim is now wondering, what is the average number of visitors who have come to the restaurant for all possible $ n! $ orders of guests in the queue. Help Maxim, calculate this number.

## 说明/提示

In the first sample the people will come in the following orders:

- $ (1,2,3) $ — there will be two people in the restaurant;
- $ (1,3,2) $ — there will be one person in the restaurant;
- $ (2,1,3) $ — there will be two people in the restaurant;
- $ (2,3,1) $ — there will be one person in the restaurant;
- $ (3,1,2) $ — there will be one person in the restaurant;
- $ (3,2,1) $ — there will be one person in the restaurant.

In total we get $ (2+1+2+1+1+1)/6 $ = $ 8/6 $ = $ 1.(3) $ .

## 样例 #1

### 输入

```
3
1 2 3
3
```

### 输出

```
1.3333333333
```

# AI分析结果

### 题目内容
# 马克西姆和餐厅

## 题目描述
马克西姆开了一家自己的餐厅！餐厅里有一张巨大的桌子，桌子长\(p\)米。

今晚马克西姆有一场晚宴，\(n\)位客人会来。我们将马克西姆餐厅的客人从\(1\)到\(n\)进行编号。马克西姆知道所有即将到来的客人的体型大小。第\(i\)位客人的体型大小（\(a_{i}\)）表示如果他坐在餐厅桌子旁，将会占用的米数。

在晚宴开始很久之前，客人在餐厅前按某种顺序排成一队。然后马克西姆依次让客人进入餐厅。当餐厅桌子没有位置给队列中的下一位客人时，马克西姆就停止让客人进入。如果餐厅里所有客人的体型大小总和加上队列中这位客人的体型大小大于\(p\)，那么队列中的下一位客人就没有位置了。在这种情况下，为了不得罪没有位置的客人，马克西姆不会再让队列中的其他客人进入餐厅，即使队列中后面的某位客人实际上是有位置可以坐下的。

马克西姆现在想知道，对于所有\(n!\)种客人排队的可能顺序，平均有多少位客人会来到餐厅。请帮助马克西姆计算这个数字。

## 说明/提示
在第一个样例中，人们会以以下顺序到来：
 - \((1,2,3)\) - 餐厅里会有两个人；
 - \((1,3,2)\) - 餐厅里会有一个人；
 - \((2,1,3)\) - 餐厅里会有两个人；
 - \((2,3,1)\) - 餐厅里会有一个人；
 - \((3,1,2)\) - 餐厅里会有一个人；
 - \((3,2,1)\) - 餐厅里会有一个人。

总共我们得到\((2 + 1 + 2 + 1 + 1 + 1) / 6 = 8 / 6 = 1.(3)\)。

## 样例 #1
### 输入
```
3
1 2 3
3
```
### 输出
```
1.3333333333
```

### 算法分类
概率论、组合数学

### 题解综合分析与结论
这几道题解都围绕背包模型结合期望和组合数来解决问题。思路核心都是通过状态表示和转移来计算不同情况下客人进入餐厅的方案数，进而得出期望。不同点在于状态表示的维度以及具体计算方案数的方式略有差异。

### 所选的题解
 - **作者：Stream月 (5星)**
    - **关键亮点**：思路清晰，状态表示明确，先确定背包状态\(f[i][j][k]\)，再通过枚举第一个不能进去的人来统计方案数，计算过程逻辑严谨，代码实现详细且有注释辅助理解。
    - **重点代码**：
```cpp
void pre() {	//计算阶乘
    fac[0] = 1;
    for(int i = 1; i <= n; ++i) {
        fac[i] = 1.0 * i * fac[i - 1];
    }
}
double ans =0;
int sum = 0;
int main(){
    //freopen("testdata.in", "r", stdin);
    //freopen("ans.out", "w", stdout);
    n = read();
    $(i, 1, n) a[i] = read(), sum += a[i];
    p = read();
    if(sum <= p) {	//这种情况需要特判一下，所有人都可以进去
        printf("%.6lf\n", 1.0 * n);
        return 0;
    } 
    pre();
    for(int x = 1; x <= n; ++x) {
        memset(f, 0, sizeof f);
        f[0][0][0] = 1;
        for(int i = 1; i <= n; ++i) {
            for(int j = 0; j <= i; ++j) {
                for(int k = 0; k <= p; ++k) {
                    if(i == x) {	//当前第x个人无法进入，所以直接跳过x
                        f[i][j][k] = f[i - 1][j][k]; continue;
                    }
                    f[i][j][k] = f[i - 1][j][k];
                    if(k >= a[i] && j > 0) f[i][j][k] += f[i - 1][j - 1][k - a[i]];
                }
            }
        }
        for(int j = 1; j < n; ++j) {
            for(int k = max(0, p - a[x] + 1); k <= p; ++k) {
                ans += j * fac[j] * fac[n - j - 1] * f[n][j][k];
            }
        }
    }
    printf("%.6lf\n", ans/fac[n]);
    return 0;
}
```
    - **核心实现思想**：先预处理阶乘。对于所有人能进入的情况特判。否则枚举第一个不能进入的人\(x\)，在计算背包状态\(f\)时跳过\(x\)，最后根据不同情况的方案数和排列数计算期望。
 - **作者：QwQ蒟蒻wjr (4星)**
    - **关键亮点**：同样采用背包DP结合期望的思路，代码简洁明了，状态转移方程清晰，还提到可以优化掉一维空间。
    - **重点代码**：
```cpp
int main()
{
    read(n);
    for(re int i=1; i<=n; ++i)
    {
        read(a[i]);
        sum+=a[i];
        fac[i]=fac[i-1]*i;
    }
    read(p);
    if(sum<=p)
    {
        printf("%lf\n",(double)n);
        return 0;
    }
    dp[0][0]=1;
    for(re int i=1; i<=n; ++i)
        for(re int j=i; j>=1; --j)
            for(re int k=p; k>=a[i]; --k)
                dp[j][k]+=dp[j-1][k-a[i]];
    for(re int i=1; i<=n; ++i)
    {
        for(re int j=0; j<=p; ++j)
            printf("%lld ",dp[i][j]);
        putchar('\n');
    }
    for(re int i=1; i<=n; ++i)
        for(re int j=0; j<=p; ++j)
            ans+=(double)dp[i][j]*fac[i]*fac[n-i];
    printf("%lf\n",ans/fac[n]);
    return 0;
}
```
    - **核心实现思想**：先读入数据并预处理阶乘，特判所有人能进入的情况。通过三层循环进行背包状态转移，最后根据状态和排列数计算期望。
 - **作者：spli (4星)**
    - **关键亮点**：思路简洁，直接考虑每个\(i\)对答案的贡献，通过背包转移计算方案数，再结合排列数和总排列数计算期望。
    - **重点代码**：无（未给出完整代码）
    - **核心实现思想**：通过背包转移方程\(f[i][j][k]+=f[i - 1][j][k]+[k\geq a[i]]\cdot f[i - 1][j - 1][k - a[i]]\)计算方案数，乘以前后排列数后除以\(n!\)得到期望。

### 最优关键思路或技巧
利用背包模型来表示客人进入餐厅的不同状态组合，通过状态转移方程计算方案数。在计算期望时，巧妙结合组合数学中的排列数知识，根据不同情况分别计算方案数对期望的贡献。

### 可拓展思路
此类问题属于结合背包模型与概率期望的问题，类似的题目套路通常围绕如何合理定义背包状态以及如何根据题目条件准确计算方案数和期望。可以拓展到其他涉及资源分配（如空间、时间等）并计算期望的场景。

### 洛谷推荐题目
 - [P1280 尼克的任务](https://www.luogu.com.cn/problem/P1280)：通过动态规划解决任务安排问题，与本题类似在于需要合理定义状态并进行状态转移。
 - [P2704 [NOI2001] 炮兵阵地](https://www.luogu.com.cn/problem/P2704)：利用状态压缩动态规划解决放置问题，与本题都涉及到状态表示和转移来解决复杂问题。
 - [P1850 换教室](https://www.luogu.com.cn/problem/P1850)：结合概率与动态规划，计算最优期望，与本题在结合概率期望方面有相似之处。

### 个人心得
无。

---
处理用时：76.91秒