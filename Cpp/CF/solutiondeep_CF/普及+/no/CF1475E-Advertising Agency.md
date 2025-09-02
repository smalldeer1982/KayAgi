# 题目信息

# Advertising Agency

## 题目描述

Masha works in an advertising agency. In order to promote the new brand, she wants to conclude contracts with some bloggers. In total, Masha has connections of $ n $ different bloggers. Blogger numbered $ i $ has $ a_i $ followers.

Since Masha has a limited budget, she can only sign a contract with $ k $ different bloggers. Of course, Masha wants her ad to be seen by as many people as possible. Therefore, she must hire bloggers with the maximum total number of followers.

Help her, find the number of ways to select $ k $ bloggers so that the total number of their followers is maximum possible. Two ways are considered different if there is at least one blogger in the first way, which is not in the second way. Masha believes that all bloggers have different followers (that is, there is no follower who would follow two different bloggers).

For example, if $ n=4 $ , $ k=3 $ , $ a=[1, 3, 1, 2] $ , then Masha has two ways to select $ 3 $ bloggers with the maximum total number of followers:

- conclude contracts with bloggers with numbers $ 1 $ , $ 2 $ and $ 4 $ . In this case, the number of followers will be equal to $ a_1 + a_2 + a_4 = 6 $ .
- conclude contracts with bloggers with numbers $ 2 $ , $ 3 $ and $ 4 $ . In this case, the number of followers will be equal to $ a_2 + a_3 + a_4 = 6 $ .

Since the answer can be quite large, output it modulo $ 10^9+7 $ .

## 说明/提示

The test case is explained in the statements.

In the second test case, the following ways are valid:

- conclude contracts with bloggers with numbers $ 1 $ and $ 2 $ . In this case, the number of followers will be equal to $ a_1 + a_2 = 2 $ ;
- conclude contracts with bloggers with numbers $ 1 $ and $ 3 $ . In this case, the number of followers will be equal to $ a_1 + a_3 = 2 $ ;
- conclude contracts with bloggers with numbers $ 1 $ and $ 4 $ . In this case, the number of followers will be equal to $ a_1 + a_4 = 2 $ ;
- conclude contracts with bloggers with numbers $ 2 $ and $ 3 $ . In this case, the number of followers will be equal to $ a_2 + a_3 = 2 $ ;
- conclude contracts with bloggers with numbers $ 2 $ and $ 4 $ . In this case, the number of followers will be equal to $ a_2 + a_4 = 2 $ ;
- conclude contracts with bloggers with numbers $ 3 $ and $ 4 $ . In this case, the number of followers will be equal to $ a_3 + a_4 = 2 $ .

In the third test case, the following ways are valid:

- concludes a contract with a blogger with the number $ 2 $ . In this case, the number of followers will be equal to $ a_2 = 2 $ .

## 样例 #1

### 输入

```
3
4 3
1 3 1 2
4 2
1 1 1 1
2 1
1 2```

### 输出

```
2
6
1```

# AI分析结果

### 题目中文重写
玛莎在一家广告公司工作。为了推广新品牌，她想与一些博主签订合同。玛莎总共认识 $n$ 位不同的博主。编号为 $i$ 的博主有 $a_i$ 个粉丝。

由于玛莎的预算有限，她只能与 $k$ 位不同的博主签订合同。当然，玛莎希望尽可能多的人看到她的广告。因此，她必须聘请粉丝总数最多的博主。

请帮助她，找出选择 $k$ 位博主的方法数，使得他们的粉丝总数尽可能大。如果第一种选择方式中至少有一位博主不在第二种选择方式中，则这两种方式被认为是不同的。玛莎认为所有博主的粉丝都是不同的（即没有一个粉丝会关注两位不同的博主）。

例如，如果 $n = 4$，$k = 3$，$a = [1, 3, 1, 2]$，那么玛莎有两种选择 3 位博主的方法，使得粉丝总数最大：
 - 与编号为 1、2 和 4 的博主签订合同。在这种情况下，粉丝数将等于 $a_1 + a_2 + a_4 = 6$。
 - 与编号为 2、3 和 4 的博主签订合同。在这种情况下，粉丝数将等于 $a_2 + a_3 + a_4 = 6$。

由于答案可能非常大，输出时对 $10^9 + 7$ 取模。

### 算法分类
组合数学

### 综合分析与结论
这些题解的核心思路都是先确定要使粉丝总数最大，应优先选择粉丝数多的博主（贪心策略），然后找出导致方案数不同的关键在于最后选择的相同粉丝数的博主的组合情况，通过计算组合数来得到最终答案。

不同题解的差异主要体现在组合数的计算方法上，有的使用杨辉三角预处理组合数，有的使用卢卡斯定理，还有的通过逆元直接计算组合数。

### 所选题解
- **Carotrl（4星）**
    - **关键亮点**：思路清晰，代码简洁易懂，使用杨辉三角预处理组合数，对于数据范围较小的本题很合适。
    - **个人心得**：认为本题非常简单，甚至比 D 题还简单。
- **冰糖鸽子（4星）**
    - **关键亮点**：详细分析了问题，将问题转化为组合数问题，同样使用杨辉三角递推计算组合数，代码实现规范。
    - **个人心得**：不小心写成排列数，提醒注意区分组合数和排列数。
- **sochiji（4星）**
    - **关键亮点**：对问题分析详细，通过数组计数优化了计算并列粉丝最多博主数量的时间复杂度，使用组合数数组存储结果。
    - **个人心得**：无

### 重点代码
#### Carotrl 的代码
```cpp
// 杨辉三角预处理组合数
for(int i=1;i<=1000;i++){
    for(int j=0;j<=i;j++){
        if(i==j||j==0)c[i][j]=1;
        else c[i][j]=(c[i-1][j-1]+c[i-1][j])%N;
    }
}
// 主逻辑
while(t--){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    sort(a+1,a+1+n,cmp);
    memset(b,0,sizeof b);
    for(int i=1;i<=n;i++)b[a[i]]++;
    int sum=0;
    for(int i=n;i>=1;i--){
        if(sum+b[i]<m)sum+=b[i];
        else{
            int k=m-sum;
            k=min(k,b[i]-k);
            ans=c[b[i]][k];	
            break; 
        }
    }
    printf("%lld\n",ans);
} 
```
**核心实现思想**：先使用杨辉三角预处理组合数，然后对输入的博主粉丝数数组进行排序，统计每个粉丝数的博主数量，从大到小遍历，当剩余要选的博主数量小于等于当前粉丝数的博主数量时，计算组合数得到答案。

#### 冰糖鸽子的代码
```cpp
// 杨辉三角递推组合数
void Re()
{
    c[0][0]=1;
    for(int i=1;i<=1000;i++)
    {
        c[i][0]=1;
        for(int j=1;j<=i;j++)
        {
            c[i][j]=c[i-1][j]+c[i-1][j-1];
            c[i][j]%=p;
        }
    }
}
// 主逻辑
while(T--)
{
    Reset();
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
    }
    sort(a+1,a+1+n,cmp);
    for(int i=1;i<=n;i++)
    {
        if(a[i]==a[m])
        {
            cnt++;
        }
        if(a[i]==a[m]&&i<=m)
        {
            cnt2++;
        }
    }
    cout<<c[cnt][cnt-cnt2]<<endl;
}
```
**核心实现思想**：通过杨辉三角递推计算组合数，对输入数组排序后，统计与第 $m$ 大的数相等的博主数量以及在前 $m$ 个数中与第 $m$ 大的数相等的博主数量，最后根据组合数数组得到答案。

#### sochiji 的代码
```cpp
// 初始化组合数存储 
void initial_comb(int max_border)
{
    comb[0][0] = 1;
    for (int i = 1; i <= max_border; i++)
    {
        comb[i][0] = 1;
        for (int j = 1; j <= i; j++)
            comb[i][j] = (comb[i - 1][j] + comb[i - 1][j - 1]) % MODNUM;
    }
}
// 主逻辑
for (int i = 1; i <= t; i++)
{
    memset(rec, 0, sizeof(rec));
    int n, k;
    scanf("%d%d", &n, &k);
    for (int j = 1; j <= n; j++)
    {
        int tmp;
        scanf("%d", &tmp);
        rec[tmp]++;
    }
    for (int j = n; j > 0; j--)
        if (rec[j] < k)
            k -= rec[j];
        else
        {
            printf("%d\n", comb[rec[j]][k]);
            break;
        }
}
```
**核心实现思想**：先初始化组合数数组，然后对输入的博主粉丝数进行计数，从大到小遍历粉丝数，当剩余要选的博主数量小于等于当前粉丝数的博主数量时，根据组合数数组输出答案。

### 最优关键思路或技巧
- **贪心策略**：优先选择粉丝数多的博主，以保证粉丝总数最大。
- **组合数计算**：对于数据范围较小的情况，使用杨辉三角预处理组合数可以避免复杂的计算和取模问题。
- **数组计数**：通过数组记录每个粉丝数的博主数量，优化了查找并列粉丝最多博主数量的时间复杂度。

### 可拓展之处
同类型题可以是从多个元素中选择一定数量的元素，使得某个指标（如价值、重量等）最大，并且需要计算选择方案数。类似算法套路可以是先使用贪心策略确定选择的大致方向，然后分析导致方案数不同的关键因素，通过组合数学的方法计算方案数。

### 推荐洛谷题目
- [P1873 砍树](https://www.luogu.com.cn/problem/P1873)：涉及贪心和二分查找。
- [P1047 校门外的树](https://www.luogu.com.cn/problem/P1047)：简单的模拟和差分问题。
- [P1060 开心的金明](https://www.luogu.com.cn/problem/P1060)：典型的 0 - 1 背包问题，使用动态规划解决。

### 个人心得总结
- Carotrl 认为本题简单，提醒我们对于数据范围较小的题目可以采用简单直接的方法。
- 冰糖鸽子不小心写成排列数，提醒我们在解决组合数学问题时要注意区分组合数和排列数。
- Cutest_Junior 因代码中 `nth_element` 函数参数写错而暴毙，提醒我们在使用库函数时要注意参数的正确性。

---
处理用时：61.52秒