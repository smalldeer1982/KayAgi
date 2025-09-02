# 题目信息

# Mex Master

## 题目描述

You are given an array $ a $ of length $ n $ . The score of $ a $ is the MEX $ ^{\dagger} $ of $ [a_1+a_2,a_2+a_3,\ldots,a_{n-1}+a_n] $ . Find the minimum score of $ a $ if you are allowed to rearrange elements of $ a $ in any order. Note that you are not required to construct the array $ a $ that achieves the minimum score.

 $ ^{\dagger} $ The MEX (minimum excluded) of an array is the smallest non-negative integer that does not belong to the array. For instance:

- The MEX of $ [2,2,1] $ is $ 0 $ , because $ 0 $ does not belong to the array.
- The MEX of $ [3,1,0,1] $ is $ 2 $ , because $ 0 $ and $ 1 $ belong to the array, but $ 2 $ does not.
- The MEX of $ [0,3,1,2] $ is $ 4 $ because $ 0 $ , $ 1 $ , $ 2 $ , and $ 3 $ belong to the array, but $ 4 $ does not.

## 说明/提示

In the first test case, it is optimal to rearrange $ a $ as $ [0,0] $ , the score of this array is the MEX of $ [0+0]=[0] $ , which is $ 1 $ .

In the second test case, it is optimal to rearrange $ a $ as $ [0,1,0] $ , the score of this array is the MEX of $ [0+1,1+0]=[1,1] $ , which is $ 0 $ .

## 样例 #1

### 输入

```
3
2
0 0
3
0 0 1
8
1 0 0 0 2 0 3 0```

### 输出

```
1
0
1```

# AI分析结果

### 题目内容
# Mex 大师

## 题目描述
给定一个长度为 $n$ 的数组 $a$ 。$a$ 的分数是 $[a_1 + a_2, a_2 + a_3, \ldots, a_{n - 1} + a_n]$ 的 MEX$^{\dagger}$ 。如果允许你以任意顺序重新排列 $a$ 的元素，求 $a$ 的最小分数。注意，你不需要构造出能达到最小分数的数组 $a$ 。

$^{\dagger}$ 一个数组的 MEX（最小排除值）是不属于该数组的最小非负整数。例如：
 - $[2, 2, 1]$ 的 MEX 是 $0$，因为 $0$ 不属于该数组。
 - $[3, 1, 0, 1]$ 的 MEX 是 $2$，因为 $0$ 和 $1$ 属于该数组，但 $2$ 不属于。
 - $[0, 3, 1, 2]$ 的 MEX 是 $4$，因为 $0$、$1$、$2$ 和 $3$ 属于该数组，但 $4$ 不属于。

## 说明/提示
在第一个测试用例中，将 $a$ 重新排列为 $[0, 0]$ 是最优的，该数组的分数是 $[0 + 0] = [0]$ 的 MEX，即 $1$ 。

在第二个测试用例中，将 $a$ 重新排列为 $[0, 1, 0]$ 是最优的，该数组的分数是 $[0 + 1, 1 + 0] = [1, 1]$ 的 MEX，即 $0$ 。

## 样例 #1
### 输入
```
3
2
0 0
3
0 0 1
8
1 0 0 0 2 0 3 0
```
### 输出
```
1
0
1
```

### 算法分类
数学

### 综合分析与结论
这些题解的核心思路都是通过分类讨论来确定最小的 MEX 值，主要依据数组中 $0$ 和 $1$ 的数量与数组长度的关系进行分析。各题解的思路本质相似，差异在于具体的分类方式和细节表述。解决该问题的难点在于全面且准确地分析不同情况下如何排列数组元素以使相邻元素和的 MEX 值最小。

### 所选的题解
- **作者：lichenzhen (5星)**
    - **关键亮点**：思路清晰，分类明确，定义了 $a_0$（$0$ 的数量）、$a_1$（$1$ 的数量）和 $b = (n + 1) \div 2$，通过比较它们之间的关系得出不同情况下的最小 MEX 值，代码简洁明了。
    - **重点代码核心实现思想**：统计数组中 $0$ 和 $1$ 的个数，根据不同条件输出对应的最小 MEX 值。
    ```cpp
    #include<bits/stdc++.h>
    using namespace std;
    int T,n,a0,a1,s;
    int main()
    {
        cin>>T;
        while(T--){
            a0=a1=0;
            cin>>n;
            for(int i=1;i<=n;i++){
                cin>>s;
                if(s==1) a1++;
                if(s==0) a0++;
            }
            if(a0==n) puts("1");
            else if(a0<=(n+1)/2) puts("0");
            else if(a0+a1==n) puts("2");
            else puts("1");
        }
        return 0;
    }
    ```
- **作者：Jorisy (5星)**
    - **关键亮点**：从 $0$ 的情况入手，通过定义 $s$ 统计 $0$ 的个数，分 $s\leq\lceil\dfrac{n}{2}\rceil$ 和 $s>\lceil\dfrac{n}{2}\rceil$ 两种大情况，再对后者细分，逻辑连贯，代码可读性强。
    - **重点代码核心实现思想**：先统计 $0$ 的个数，根据 $0$ 个数与数组长度的关系，以及是否存在大于 $1$ 的数等条件，输出对应的最小 MEX 值。
    ```cpp
    #include<bits/stdc++.h>
    using namespace std;

    int a[200005];

    void sol()
    {
        int n,s=0;
        cin>>n;
        for(int i=1;i<=n;i++) cin>>a[i],s+=!a[i];//统计 0 个数
        if(n%2==0&&s<=n/2||n%2&&s<=(n+1)/2) puts("0");//0 个数少
        else 
        {
            if(s==n) puts("1");//全 0
            else
            {
                for(int i=1;i<=n;i++)
                {
                    if(a[i]>1)
                    {
                        puts("1");
                        return;
                    }
                }
                puts("2");//01 序列
            }
        }
    }

    int main()
    {
        int t;
        cin>>t;
        while(t--) sol(); 
        return 0;
    }
    ```
- **作者：0zhouyq (4星)**
    - **关键亮点**：思路直接，强调尽量不把两个 $0$ 挨在一起，以 $0$ 的个数为主要分类依据，结合是否有大于 $1$ 的数以及是否全为 $0$ 或 $1$ 来确定最小 MEX 值，代码简洁高效。
    - **重点代码核心实现思想**：统计 $0$ 和大于 $1$ 的数的个数，依据不同条件输出对应的最小 MEX 值。
    ```cpp
    #include<bits/stdc++.h>
    using namespace std;
    #define ll long long
    int main(){
        ll t;
        scanf("%lld",&t);
        while(t--){
            ll n;
            scanf("%lld",&n);
            ll cnt=0,cnt2=0;
            for(ll i=1;i<=n;i++){
                ll x;
                scanf("%lld",&x);
                if(x==0) cnt++;//计算0的个数
                if(x>1) cnt2++;//计算>1的数的个数
            }
            if(cnt<=(n+1)/2) printf("0\n");
            else if(cnt2>0||cnt==n) printf("1\n");
            else printf("2\n");
        }
        return 0;
    }
    ```

### 最优关键思路或技巧
通过统计数组中特殊数字（$0$ 和 $1$）的数量，并结合数组长度进行分类讨论，利用不同数字组合排列后相邻元素和的特点来确定最小 MEX 值。这种基于数字特性和数量关系的分类讨论思维方式是解决此类问题的关键。

### 拓展
同类型题通常围绕数组元素的特定运算结果的某种极值（如最小未出现值、最大公约数等），通过对数组元素的排列组合来求解。类似算法套路是先分析特殊元素（如本题的 $0$ 和 $1$）对结果的影响，再根据元素数量与数组整体的关系进行分类讨论。

### 推荐题目
 - **P1147 连续自然数和**：通过枚举和数学推导来解决连续自然数和的问题，与本题分类讨论和利用数字关系的思路类似。
 - **P2678 [NOIP2015 普及组] 跳石头**：运用二分查找和贪心策略，与本题通过分析条件得出结论的思维方式有相通之处。
 - **P1083 [NOIP2012 提高组] 借教室**：同样涉及分类讨论和条件判断，根据不同情况进行决策，与本题解题思路类似。 

---
处理用时：50.37秒