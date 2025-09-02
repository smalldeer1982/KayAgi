# 题目信息

# Binary Deque

## 题目描述

Slavic has an array of length $ n $ consisting only of zeroes and ones. In one operation, he removes either the first or the last element of the array.

What is the minimum number of operations Slavic has to perform such that the total sum of the array is equal to $ s $ after performing all the operations? In case the sum $ s $ can't be obtained after any amount of operations, you should output -1.

## 说明/提示

In the first test case, the sum of the whole array is $ 1 $ from the beginning, so we don't have to make any operations.

In the second test case, the sum of the array is $ 2 $ and we want it to be equal to $ 1 $ , so we should remove the first element. The array turns into $ [1, 0] $ , which has a sum equal to $ 1 $ .

In the third test case, the sum of the array is $ 5 $ and we need it to be $ 3 $ . We can obtain such a sum by removing the first two elements and the last element, doing a total of three operations. The array turns into $ [0, 1, 1, 1, 0, 0] $ , which has a sum equal to $ 3 $ .

## 样例 #1

### 输入

```
7
3 1
1 0 0
3 1
1 1 0
9 3
0 1 0 1 1 1 0 0 1
6 4
1 1 1 1 1 1
5 1
0 0 1 1 0
16 2
1 1 0 0 1 0 0 1 1 0 0 0 0 0 1 1
6 3
1 0 1 0 0 0```

### 输出

```
0
1
3
2
2
7
-1```

# AI分析结果

### 题目内容
# Binary Deque

## 题目描述
Slavic有一个长度为$n$的数组，数组中仅由$0$和$1$组成。在一次操作中，他可以移除数组的第一个元素或最后一个元素。

Slavic最少需要执行多少次操作，才能使数组所有元素的总和在执行完所有操作后等于$s$？如果在任何操作次数下都无法得到总和$s$，则应输出 -1。

## 说明/提示
在第一个测试用例中，数组的总和从一开始就是$1$，所以我们无需进行任何操作。

在第二个测试用例中，数组的总和为$2$，而我们希望它等于$1$，所以我们应该移除第一个元素。数组变为$[1, 0]$，其总和等于$1$。

在第三个测试用例中，数组的总和为$5$，而我们需要它为$3$。我们可以通过移除前两个元素和最后一个元素来得到这样的总和，总共进行三次操作。数组变为$[0, 1, 1, 1, 0, 0]$，其总和等于$3$。

## 样例 #1
### 输入
```
7
3 1
1 0 0
3 1
1 1 0
9 3
0 1 0 1 1 1 0 0 1
6 4
1 1 1 1 1 1
5 1
0 0 1 1 0
16 2
1 1 0 0 1 0 0 1 1 0 0 0 0 0 1 1
6 3
1 0 1 0 0 0
```
### 输出
```
0
1
3
2
2
7
-1
```

### 算法分类
贪心

### 综合分析与结论
这些题解主要围绕如何找到使数组和为$s$的最少操作次数展开。思路大多基于将问题转化为寻找和为$s$的最长子序列或区间。
1. **思路方面**：
    - 多数题解考虑通过双指针、前缀和、二分查找等方法来优化查找和为$s$的子序列或区间的过程。
    - 例如，有的题解用数组维护$1$的位置，通过双指针移动找到最长子序列；有的利用前缀和数组结合二分查找确定满足和为$s$的区间端点。
2. **算法要点**：
    - 预处理：如预处理前缀和、每个$1$的位置、连续$0$的长度等信息，为后续计算提供便利。
    - 指针移动策略：双指针题解中，根据当前子序列和与$s$的大小关系，合理移动左右指针。
    - 二分查找：利用前缀和数组的单调性，通过二分查找快速定位满足条件的区间端点。
3. **解决难点**：
    - 如何高效地找到和为$s$的最长子序列或区间是关键难点。不同题解通过不同的数据结构和算法优化来解决，如利用前缀和数组结合二分查找降低时间复杂度，通过维护$1$的位置数组并结合指针移动找到最长子序列。

### 所选的题解
- **作者：Dream_weavers（5星）**
    - **关键亮点**：思路清晰，将问题巧妙转化为求序列中和为$s$的最长子序列，通过维护$1$的位置数组，利用双指针法遍历寻找最长子序列，代码简洁明了。
    - **重点代码核心实现思想**：用`loc`数组记录$1$的位置，通过双指针`l`和`r`遍历`loc`数组，每次计算包含当前`l`到`r`之间$1$以及两端连续$0$的子序列长度，取最大长度，最后用数组总长减去最大长度得到操作次数。
```cpp
void solve(){
    memset(loc,0,sizeof(loc));
    tot=0,ans=0;
    scanf("%d%d",&n,&s);
    for(int i=1;i<=n;i++){
        scanf("%d",&x);
        if(x)loc[++tot]=i;
    }
    loc[0]=0,loc[tot+1]=n+1;
    if(tot<s){
        puts("-1");
        return;
    }
    for(int l=1,r=s;r<=tot;l++,r++){
        int sum=loc[r]-loc[l]+1;
        sum+=(loc[l]-loc[l-1]-1);
        sum+=(loc[r+1]-loc[r]-1);
        ans=max(ans,sum);
    }
    printf("%d\n",n-ans);
} 
```
- **作者：cyrxdzj（4星）**
    - **关键亮点**：直接使用双指针法，通过维护左右指针和当前子序列和，根据和与$s$的大小关系移动指针，直观易懂。
    - **重点代码核心实现思想**：初始化左右指针`l`、`r`和当前子序列和`sum`，在指针未越界时，根据`sum`与`s`的关系，决定指针移动方向并更新`sum`和答案`ans`。
```cpp
while(l<=n&&r<=n)
{
    if(sum==s)
    {
        ans=min(l-1+n-r,ans);
        r++;
        sum+=a[r];
    }
    else if(sum>s)
    {
        sum-=a[l];
        l++;
    }
    else
    {
        r++;
        sum+=a[r];
    }
}
```
- **作者：__vector__（4星）**
    - **关键亮点**：将问题转化为寻找最长满足和为$s$的区间，利用前缀和数组的单调性，通过二分查找优化寻找右端点的过程，同时考虑了右端点后连续$0$的情况以确保区间最长。
    - **重点代码核心实现思想**：先预处理前缀和数组`qzh`和记录每个位置后连续相同元素个数的数组`len`，枚举左端点`l`，通过`lower_bound`找到满足和为`s + qzh[l - 1]`的右端点`r`，并根据`len`数组调整`r`以包含右端点后的连续$0$，更新最大区间长度。
```cpp
for(int l=1;l<=n;l++)
{
    int r=lower_bound(qzh+l,qzh+n+1,s+qzh[l-1])-qzh;
    if(a[r+1]==0&&r<n)r=r+1+len[r+1]-1;
    if(r==n+1)
    {
        continue;
    }
    maxlen=max(maxlen,r-l+1);
}
```

### 最优关键思路或技巧
1. **问题转化**：将原问题转化为寻找和为$s$的最长子序列或区间，使得问题解决方向更明确。
2. **数据预处理**：通过预处理如前缀和、$1$的位置、连续$0$的长度等信息，为后续操作提供快速计算的基础。
3. **双指针与二分查找**：双指针法通过动态调整子序列范围，根据子序列和与目标和的关系进行移动；二分查找利用前缀和数组单调性快速定位满足条件的区间端点，有效降低时间复杂度。

### 可拓展之处
同类型题通常围绕数组元素的删除、保留操作，以满足特定的和、积等数值条件。类似算法套路包括利用前缀和、双指针、二分查找等优化查找满足条件子序列或区间的过程。例如，对于一些限制条件更复杂的数组操作问题，也可尝试通过预处理关键信息，结合双指针或二分查找来解决。

### 洛谷相似题目推荐
1. **P1886 滑动窗口**：通过维护单调队列来解决滑动窗口内的最值问题，与本题利用数据结构优化查找过程类似。
2. **P2824 [HEOI2016/TJOI2016]排序**：涉及对数组的操作和条件判断，可通过二分答案结合模拟操作来解决，与本题在问题解决思路上有相通之处。
3. **P3810 【模板】三维偏序（陌上花开）**：通过排序、树状数组等方法解决三维偏序问题，在利用数据结构优化算法方面与本题有相似点。 

---
处理用时：59.11秒