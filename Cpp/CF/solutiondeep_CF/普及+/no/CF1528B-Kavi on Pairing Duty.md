# 题目信息

# Kavi on Pairing Duty

## 题目描述

Kavi has $ 2n $ points lying on the $ OX $ axis, $ i $ -th of which is located at $ x = i $ .

Kavi considers all ways to split these $ 2n $ points into $ n $ pairs. Among those, he is interested in good pairings, which are defined as follows:

Consider $ n $ segments with ends at the points in correspondent pairs. The pairing is called good, if for every $ 2 $ different segments $ A $ and $ B $ among those, at least one of the following holds:

- One of the segments $ A $ and $ B $ lies completely inside the other.
- $ A $ and $ B $ have the same length.

Consider the following example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1528B/41a58a6a051949b924acfc162dd6465703f68210.png) $ A $ is a good pairing since the red segment lies completely inside the blue segment.

 $ B $ is a good pairing since the red and the blue segment have the same length.

 $ C $ is not a good pairing since none of the red or blue segments lies inside the other, neither do they have the same size.

Kavi is interested in the number of good pairings, so he wants you to find it for him. As the result can be large, find this number modulo $ 998244353 $ .

Two pairings are called different, if some two points are in one pair in some pairing and in different pairs in another.

## 说明/提示

The good pairings for the second example are:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1528B/26cefe71c208095e0e610c498701d052b950b5a2.png)In the third example, the good pairings are:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1528B/4bfe3f3beac587d75fee5d30f6490c2823b90e1d.png)

## 样例 #1

### 输入

```
1```

### 输出

```
1```

## 样例 #2

### 输入

```
2```

### 输出

```
3```

## 样例 #3

### 输入

```
3```

### 输出

```
6```

## 样例 #4

### 输入

```
100```

### 输出

```
688750769```

# AI分析结果

### 题目翻译
Kavi 有 $2n$ 个位于 $OX$ 轴上的点，第 $i$ 个点位于 $x = i$ 处。

Kavi 考虑将这些点分成 $n$ 对的所有方式。在这些方式中，他对“好的配对”感兴趣，其定义如下：

考虑对应配对中点所构成的 $n$ 条线段。如果对于其中任意两条不同的线段 $A$ 和 $B$，至少满足以下条件之一，则该配对被称为“好的配对”：
- 线段 $A$ 和 $B$ 中的一条完全位于另一条内部。
- $A$ 和 $B$ 的长度相同。

考虑以下示例：
![示例图](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1528B/41a58a6a051949b924acfc162dd6465703f68210.png)
$A$ 是一个好的配对，因为红色线段完全位于蓝色线段内部。
$B$ 是一个好的配对，因为红色和蓝色线段长度相同。
$C$ 不是一个好的配对，因为红色和蓝色线段都不位于对方内部，且它们的长度也不相同。

Kavi 想知道好的配对的数量，所以他希望你帮他找到这个数量。由于结果可能很大，需要将这个数量对 $998244353$ 取模。

如果在一种配对中某些两个点在一对中，而在另一种配对中它们在不同的对中，则这两种配对被认为是不同的。

### 算法分类
动态规划

### 综合分析与结论
这些题解大多采用动态规划的思路来解决问题。核心在于分析出满足条件的配对情况，进而推导出状态转移方程。不同题解在具体分析情况和实现细节上有所差异，但总体围绕着约数个数和之前状态的累加来构建状态转移方程。

### 所选题解
- **KaisuoShutong（5星）**
    - **关键亮点**：思路清晰，先通过分析图形特点得出规律，进而推导出状态转移方程，代码实现简洁，使用了快速读入优化。
    - **个人心得**：无
- **iMya_nlgau（4星）**
    - **关键亮点**：思路明确，通过图形示例辅助说明两种情况对答案的贡献，状态转移方程推导清晰。
    - **个人心得**：无
- **Erica_N_Contina（4星）**
    - **关键亮点**：详细分析了问题的性质，通过图形展示两种转移情况，状态转移方程推导合理。
    - **个人心得**：无

### 重点代码
#### KaisuoShutong
```cpp
const int maxn = 1e6+10, mod = 998244353;
int n,f[maxn];
signed main() {
    n=read();
    for(int i=1;i<=n;i++)
        for(int j=i;j<=n;j+=i) ++f[j];
    f[1]=1;for(int i=2;i<=n;i++) f[i]=(1ll*(f[i-1]<<1)+f[i])%mod;
    cout<<(f[n]-f[n-1]+mod)%mod<<'\n';
    return 0;
}
```
**核心实现思想**：先预处理每个数的约数个数，然后根据状态转移方程 $f_i=\sigma_i+\sum^{i - 1}_{j = 1}f_j$ 进行递推，最后输出结果。

#### iMya_nlgau
状态转移方程为 $f_i=\sigma_0(i)+\sum\limits_{0<j<i}f_j$，边界 $f_1 = 1$。

#### Erica_N_Contina
```C++
const int N=1e6+5,MOD=998244353;
int n,a,b,x,y,ans,res,idx,cnt[N],dp[N];
signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        for(int j=i;j<=n;j+=i){
            cnt[j]++;//预处理约数的个数
            cnt[j]%=MOD;
        }
    }
    dp[1]=1;
    for(int i=1;i<=n;i++){
        dp[i]=cnt[i];
        for(int k=1;k<=i-1;k++)dp[i]+=dp[k],dp[i]%=MOD;
    }
    cout<<dp[n]<<endl;
    return 0;
}
```
**核心实现思想**：先预处理每个数的约数个数，然后根据状态转移方程 $dp_i=\sigma (i) + \sum\limits_{k = 1}^{i - 1} dp_{k}$ 进行递推，最后输出结果。

### 关键思路或技巧
- **状态定义**：设 $f_i$ 或 $dp_i$ 表示有 $2i$ 个点时的答案。
- **情况分析**：分析出两种满足条件的配对情况，一种是将点分组，组数为 $n$ 的约数；另一种是从外往内包围，由之前的状态转移而来。
- **约数预处理**：通过两层循环预处理每个数的约数个数。

### 拓展思路
同类型题或类似算法套路通常围绕动态规划展开，通过分析问题的性质和状态转移情况来构建方程。例如在一些组合计数问题中，需要根据题目条件分析出不同的情况，然后利用之前的状态来计算当前状态的答案。

### 推荐题目
- [P1048 采药](https://www.luogu.com.cn/problem/P1048)
- [P1216 [USACO1.5][IOI1994]数字三角形 Number Triangles](https://www.luogu.com.cn/problem/P1216)
- [P1434 [SHOI2002]滑雪](https://www.luogu.com.cn/problem/P1434)

---
处理用时：46.90秒