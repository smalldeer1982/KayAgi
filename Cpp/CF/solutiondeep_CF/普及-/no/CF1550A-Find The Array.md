# 题目信息

# Find The Array

## 题目描述

Let's call an array $ a $ consisting of $ n $ positive (greater than $ 0 $ ) integers beautiful if the following condition is held for every $ i $ from $ 1 $ to $ n $ : either $ a_i = 1 $ , or at least one of the numbers $ a_i - 1 $ and $ a_i - 2 $ exists in the array as well.

For example:

- the array $ [5, 3, 1] $ is beautiful: for $ a_1 $ , the number $ a_1 - 2 = 3 $ exists in the array; for $ a_2 $ , the number $ a_2 - 2 = 1 $ exists in the array; for $ a_3 $ , the condition $ a_3 = 1 $ holds;
- the array $ [1, 2, 2, 2, 2] $ is beautiful: for $ a_1 $ , the condition $ a_1 = 1 $ holds; for every other number $ a_i $ , the number $ a_i - 1 = 1 $ exists in the array;
- the array $ [1, 4] $ is not beautiful: for $ a_2 $ , neither $ a_2 - 2 = 2 $ nor $ a_2 - 1 = 3 $ exists in the array, and $ a_2 \ne 1 $ ;
- the array $ [2] $ is not beautiful: for $ a_1 $ , neither $ a_1 - 1 = 1 $ nor $ a_1 - 2 = 0 $ exists in the array, and $ a_1 \ne 1 $ ;
- the array $ [2, 1, 3] $ is beautiful: for $ a_1 $ , the number $ a_1 - 1 = 1 $ exists in the array; for $ a_2 $ , the condition $ a_2 = 1 $ holds; for $ a_3 $ , the number $ a_3 - 2 = 1 $ exists in the array.

You are given a positive integer $ s $ . Find the minimum possible size of a beautiful array with the sum of elements equal to $ s $ .

## 说明/提示

Consider the example test:

1. in the first test case, the array $ [1] $ meets all conditions;
2. in the second test case, the array $ [3, 4, 1] $ meets all conditions;
3. in the third test case, the array $ [1, 2, 4] $ meets all conditions;
4. in the fourth test case, the array $ [1, 4, 6, 8, 10, 2, 11] $ meets all conditions.

## 样例 #1

### 输入

```
4
1
8
7
42```

### 输出

```
1
3
3
7```

# AI分析结果

### 题目内容
# 寻找数组

## 题目描述
我们称一个由 $n$ 个正整数（大于 $0$）组成的数组 $a$ 是美丽的，如果对于从 $1$ 到 $n$ 的每个 $i$ 都满足以下条件：要么 $a_i = 1$，要么 $a_i - 1$ 和 $a_i - 2$ 这两个数中至少有一个也存在于该数组中。

例如：
- 数组 $[5, 3, 1]$ 是美丽的：对于 $a_1$，$a_1 - 2 = 3$ 存在于数组中；对于 $a_2$，$a_2 - 2 = 1$ 存在于数组中；对于 $a_3$，满足 $a_3 = 1$ 这个条件；
- 数组 $[1, 2, 2, 2, 2]$ 是美丽的：对于 $a_1$，满足 $a_1 = 1$ 这个条件；对于其他每个数 $a_i$，$a_i - 1 = 1$ 存在于数组中；
- 数组 $[1, 4]$ 不是美丽的：对于 $a_2$，$a_2 - 2 = 2$ 和 $a_2 - 1 = 3$ 都不存在于数组中，且 $a_2 \neq 1$；
- 数组 $[2]$ 不是美丽的：对于 $a_1$，$a_1 - 1 = 1$ 和 $a_1 - 2 = 0$ 都不存在于数组中，且 $a_1 \neq 1$；
- 数组 $[2, 1, 3]$ 是美丽的：对于 $a_1$，$a_1 - 1 = 1$ 存在于数组中；对于 $a_2$，满足 $a_2 = 1$ 这个条件；对于 $a_3$，$a_3 - 2 = 1$ 存在于数组中。

给定一个正整数 $s$。求元素和等于 $s$ 的美丽数组的最小可能大小。

## 说明/提示
考虑示例测试：
1. 在第一个测试用例中，数组 $[1]$ 满足所有条件；
2. 在第二个测试用例中，数组 $[3, 4, 1]$ 满足所有条件；
3. 在第三个测试用例中，数组 $[1, 2, 4]$ 满足所有条件；
4. 在第四个测试用例中，数组 $[1, 4, 6, 8, 10, 2, 11]$ 满足所有条件。

## 样例 #1
### 输入
```
4
1
8
7
42
```
### 输出
```
1
3
3
7
```

### 算法分类
贪心

### 综合分析与结论
这些题解主要围绕贪心和动态规划两种思路。贪心思路是为使美丽数组元素个数最少，每次放的数尽量大，即每个数比前一个数多 $2$，若最后一个数放不下，就把它减小到刚好放下，元素个数不变。动态规划则是通过状态转移方程 $dp_{i,j}=\min\begin{cases}dp_{i - j,j}+1&i - j≥j\\dp_{i - j,j - 1}+1&i - j≥j - 1\\dp_{i - j,j - 2}+1&i - j≥j - 2\end{cases}$ 来计算和为 $i$ 且最后放的数为 $j$ 的美丽数列最少需要的元素个数。贪心算法时间复杂度低，实现简单，动态规划虽能解决问题，但时间复杂度为 $O(N^2)$ 较高。整体来看，贪心算法更优。

### 所选的题解
- **作者：清清老大 (5星)**
    - **关键亮点**：思路清晰简洁，直接阐述贪心策略，代码实现简洁明了。
    ```cpp
    #include<bits/stdc++.h>

    using namespace std;

    int main()
    {
        int t;
        cin >> t;
        while(t --)
        {
            int s,ans = 0;
            cin >> s;
            int a = 1;
            while(s > 0)
            {
                s -= a;
                ans ++;
                a += 2;
            }
            cout << ans << endl;
        }
    }
    ```
    - **核心实现思想**：从1开始，每次让当前数 $a$ 增加2，用 $s$ 不断减去 $a$，同时记录操作次数 $ans$，直到 $s$ 减为0，此时 $ans$ 即为所求的最小元素个数。
- **作者：luckydrawbox (4星)**
    - **关键亮点**：不仅给出贪心思路及证明，还提供动态规划解法，内容全面。
    - **贪心代码**：
    ```cpp
    #include<bits/stdc++.h>
    using namespace std;
    int t,s,sum,ans;
    int main()
    {
        cin>>t;
        while(t--)
        {
            cin>>s;
            sum=ans=0;
            for(int i=1;sum<s;i+=2)
            {
                sum+=i;
                ans++;
            }
            cout<<ans<<endl;
        }
        return 0;
    } 
    ```
    - **核心实现思想**：与清清老大类似，从1开始每次增加2，累加当前数到 $sum$，并记录操作次数 $ans$，直到 $sum$ 不小于 $s$，$ans$ 即为结果。
    - **动态规划代码**：
    ```cpp
    #include<bits/stdc++.h>
    using namespace std;
    const int N=5010,inf=1e9;
    int t,s,dp[N][N],ans[N];
    int main()
    {
        cin>>t;
        //预处理 
        for(int i=0;i<5001;i++)
            for(int j=0;j<=i;j++)
                if(j==1)
                    dp[i][j]=i;
                else
                    dp[i][j]=inf;
        for(int i=1;i<5001;i++)//j为1时的答案 
            ans[i]=dp[i][1];
        for(int i=2;i<5001;i++)
        {
            for(int j=2;j<=i;j++)
            {
                //三种情况 
                if(i-j>=j)
                    dp[i][j]=min(dp[i-j][j]+1,dp[i][j]);
                if(i-j>=j-1)
                    dp[i][j]=min(dp[i-j][j-1]+1,dp[i][j]);
                if(i-j>=j-2)
                    dp[i][j]=min(dp[i-j][j-2]+1,dp[i][j]);
                ans[i]=min(ans[i],dp[i][j]);//对答案取最小值 
            }
        }
        while(t--)
        {
            cin>>s;
            cout<<ans[s]<<endl;
        }
        return 0;
    }
    ```
    - **核心实现思想**：先对 $dp$ 数组进行预处理，$dp_{i,1}=i$，其他设为无穷大。然后通过状态转移方程更新 $dp$ 数组，最后 $ans_i=\min_{j = 1}^idp_{i,j}$ 记录和为 $i$ 时的答案。
- **作者：xkcdjerry (4星)**
    - **关键亮点**：先分析出美丽数列排序后的特征，进而得出贪心策略，且指出时间复杂度。
    ```cpp
    /*
        Code by xkcdjerry
        Time: 2021-07-14
        Generated by cf-tools
    */
    #include <cstdio>
    /*
       显然，beautiful array排序后相邻项差<=2
       那么显然能让差=2时令其=2最好
       贪心直到太大，减掉即可
    */
    #define int long long
    void once()
    {
        int t;
        scanf("%lld",&t);
        int ans=0;
        int now=1;
        while(now<t)
        {
            t-=now;
            ans++;
            now+=2;
        }
        printf("%lld\n",ans+1);
    }
    #undef int


    int main()
    {
        int t;
        scanf("%d",&t);
        while(t--) once();
        return 0;
    }
    ```
    - **核心实现思想**：从1开始，每次当前数 $now$ 增加2，用 $t$ 不断减去 $now$ 并记录操作次数 $ans$，直到 $now$ 不小于 $t$，最后输出 $ans + 1$。

### 最优关键思路或技巧
贪心算法中，利用每次选择比前一个数大2的数来构造数组，能保证在满足美丽数组条件下使元素个数最少。这种基于问题特性直接选择局部最优解的贪心策略是解决本题的关键。

### 同类型题或类似算法套路
此类题目通常在给定某种条件限制下，求满足特定目标（如最小化、最大化某个值）的最优解。类似套路是分析问题特性找到局部最优策略，如本题根据美丽数组定义推出每次取尽量大的数且差值为2的贪心策略。

### 洛谷题目推荐
- [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)：通过对数据进行排序后贪心求解。
- [P1248 加工生产调度](https://www.luogu.com.cn/problem/P1248)：利用贪心思想优化生产调度顺序。
- [P2123 皇后游戏](https://www.luogu.com.cn/problem/P2123)：根据一定规则进行排序后贪心，与本题通过分析条件得出贪心策略类似。 

---
处理用时：81.60秒