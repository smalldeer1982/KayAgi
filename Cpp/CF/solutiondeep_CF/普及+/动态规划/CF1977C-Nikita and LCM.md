# 题目信息

# Nikita and LCM

## 题目描述

Nikita is a student passionate about number theory and algorithms. He faces an interesting problem related to an array of numbers.

Suppose Nikita has an array of integers $ a $ of length $ n $ . He will call a subsequence $ ^\dagger $ of the array special if its [least common multiple (LCM)](https://en.wikipedia.org/wiki/Least_common_multiple) is not contained in $ a $ . The LCM of an empty subsequence is equal to $ 0 $ .

Nikita wonders: what is the length of the longest special subsequence of $ a $ ? Help him answer this question!

 $ ^\dagger $ A sequence $ b $ is a subsequence of $ a $ if $ b $ can be obtained from $ a $ by the deletion of several (possibly, zero or all) elements, without changing the order of the remaining elements. For example, $ [5,2,3] $ is a subsequence of $ [1,5,7,8,2,4,3] $ .

## 说明/提示

In the first test case, the LCM of any non-empty subsequence is contained in $ a $ , so the answer is $ 0 $ .

In the second test case, we can take the subsequence $ [3, 2, 10, 1] $ , its LCM is equal to $ 30 $ , which is not contained in $ a $ .

In the third test case, we can take the subsequence $ [2, 3, 6, 100\,003] $ , its LCM is equal to $ 600\,018 $ , which is not contained in $ a $ .

## 样例 #1

### 输入

```
6
5
1 2 4 8 16
6
3 2 10 20 60 1
7
2 3 4 6 12 100003 1200036
9
2 42 7 3 6 7 7 1 6
8
4 99 57 179 10203 2 11 40812
1
1```

### 输出

```
0
4
4
5
8
0```

# AI分析结果

### 题目内容重写

#### Nikita和LCM

##### 题目描述

Nikita是一个对数论和算法充满热情的学生。他遇到了一个与数字数组相关的有趣问题。

假设Nikita有一个长度为$n$的整数数组$a$。他将数组的一个子序列称为“特殊的”，如果该子序列的[最小公倍数（LCM）](https://en.wikipedia.org/wiki/Least_common_multiple)不在$a$中。空子序列的LCM等于$0$。

Nikita想知道：数组$a$中最长的特殊子序列的长度是多少？请帮助他回答这个问题！

$^\dagger$ 序列$b$是$a$的子序列，如果$b$可以通过删除$a$中的若干个（可能为零或全部）元素得到，且不改变剩余元素的顺序。例如，$[5,2,3]$是$[1,5,7,8,2,4,3]$的子序列。

##### 说明/提示

在第一个测试用例中，任何非空子序列的LCM都包含在$a$中，因此答案为$0$。

在第二个测试用例中，我们可以取子序列$[3, 2, 10, 1]$，它的LCM等于$30$，不在$a$中。

在第三个测试用例中，我们可以取子序列$[2, 3, 6, 100\,003]$，它的LCM等于$600\,018$，不在$a$中。

##### 样例 #1

###### 输入

```
6
5
1 2 4 8 16
6
3 2 10 20 60 1
7
2 3 4 6 12 100003 1200036
9
2 42 7 3 6 7 7 1 6
8
4 99 57 179 10203 2 11 40812
1
1
```

###### 输出

```
0
4
4
5
8
0
```

### 题解分析与结论

#### 综合分析

本题的核心在于找到数组$a$中最长的子序列，使得该子序列的LCM不在$a$中。多个题解都采用了类似的思路：首先计算整个数组的LCM，如果该LCM不等于数组中的最大值，则直接输出数组长度$n$；否则，枚举数组最大值的所有因数，判断这些因数是否可以作为子序列的LCM，并找到符合条件的最大子序列长度。

#### 最优关键思路

1. **LCM计算与判断**：首先计算整个数组的LCM，如果该LCM不等于数组中的最大值，则直接输出$n$，因为此时整个数组就是一个符合条件的子序列。
2. **因数枚举与验证**：如果LCM等于数组中的最大值，则枚举该最大值的所有因数，判断这些因数是否可以作为子序列的LCM，并找到符合条件的最大子序列长度。

#### 可拓展之处

1. **LCM与GCD的结合**：在计算LCM时，通常需要结合GCD的计算，因此熟练掌握GCD和LCM的计算方法对于解决此类问题非常重要。
2. **因数枚举的优化**：在枚举因数时，可以通过只枚举到$\sqrt{n}$来减少计算量，同时注意处理平方数的情况。

### 推荐题目

1. **P1029 [NOIP2001 提高组] 最大公约数和最小公倍数问题** - 考察GCD和LCM的计算及其应用。
2. **P1072 [NOIP2009 提高组] Hankson 的趣味题** - 涉及GCD和LCM的综合应用。
3. **P1069 [NOIP2009 提高组] 细胞分裂** - 考察LCM在生物学问题中的应用。

### 所选高分题解

#### 题解1：作者：phigy (赞：12)

##### 星级：5星

##### 关键亮点

- **思路清晰**：首先判断整个数组的LCM是否等于数组中的最大值，如果不等于则直接输出$n$，否则枚举最大值的所有因数，判断这些因数是否可以作为子序列的LCM。
- **代码简洁**：代码结构清晰，逻辑明确，易于理解。

##### 核心代码

```cpp
void update(int x)
{
    int all=1,cnt=0,i;
    for(i=1;i<=n;i++) 
    {
        if(x%a[i]==0) {cnt++;all=all/gcd(a[i],all)*a[i];}
    }
    for(i=1;i<=n;i++)
    {
        if(a[i]==all) {return ;}
    }
    ans=max(ans,cnt);
}
```

#### 题解2：作者：g1ove (赞：6)

##### 星级：4星

##### 关键亮点

- **动态规划**：使用动态规划的方法，通过map记录子序列的LCM，判断是否可以作为符合条件的子序列。
- **优化思路**：通过质因数分解和动态规划的结合，减少了状态数，提高了效率。

##### 核心代码

```cpp
void solve()
{
    st.clear();f.clear();vis.clear();
    res=0;
    st.insert(0);
    f[0]=0;
    for(int i=1;i<=n;++i)
    {
        g=f;
        vis[a[i]]=1;
        for(auto p:st)
        {
            ll x=glcm(p,a[i]);
            f[x]=max(f[x],g[p]+1);
            st.insert(x);
        }
    }
    for(auto p:st)
        if(!vis[p]) res=max(res,f[p]);
    printf("%d\n",res);
}
```

#### 题解3：作者：wmrqwq (赞：4)

##### 星级：4星

##### 关键亮点

- **因数枚举**：通过枚举整个数组的LCM的所有因数，判断这些因数是否可以作为子序列的LCM，并找到符合条件的最大子序列长度。
- **代码实现**：代码实现简洁，逻辑清晰，易于理解。

##### 核心代码

```cpp
ll query(ll x)
{
    ll LCM=1,sum=0;
    forl(i,1,n)
        if(x%a[i]==0)
            LCM=lcm(LCM,a[i]),sum++;
    if(mp[LCM]==0 && LCM==x)
        return sum;
    return 0;
}
```

### 总结

本题的核心在于理解LCM的性质，并通过枚举因数来找到符合条件的子序列。多个题解都采用了类似的思路，但在实现细节上有所不同。掌握LCM的计算方法以及因数枚举的技巧对于解决此类问题非常重要。

---
处理用时：51.53秒