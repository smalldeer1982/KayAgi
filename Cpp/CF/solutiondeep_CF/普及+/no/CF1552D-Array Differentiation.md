# 题目信息

# Array Differentiation

## 题目描述

You are given a sequence of $ n $ integers $ a_1, \, a_2, \, \dots, \, a_n $ .

Does there exist a sequence of $ n $ integers $ b_1, \, b_2, \, \dots, \, b_n $ such that the following property holds?

- For each $ 1 \le i \le n $ , there exist two (not necessarily distinct) indices $ j $ and $ k $ ( $ 1 \le j, \, k \le n $ ) such that $ a_i = b_j - b_k $ .

## 说明/提示

In the first test case, the sequence $ b = [-9, \, 2, \, 1, \, 3, \, -2] $ satisfies the property. Indeed, the following holds:

- $ a_1 = 4 = 2 - (-2) = b_2 - b_5 $ ;
- $ a_2 = -7 = -9 - (-2) = b_1 - b_5 $ ;
- $ a_3 = -1 = 1 - 2 = b_3 - b_2 $ ;
- $ a_4 = 5 = 3 - (-2) = b_4 - b_5 $ ;
- $ a_5 = 10 = 1 - (-9) = b_3 - b_1 $ .

In the second test case, it is sufficient to choose $ b = [0] $ , since $ a_1 = 0 = 0 - 0 = b_1 - b_1 $ .

In the third test case, it is possible to show that no sequence $ b $ of length $ 3 $ satisfies the property.

## 样例 #1

### 输入

```
5
5
4 -7 -1 5 10
1
0
3
1 10 100
4
-3 2 10 2
9
25 -171 250 174 152 242 100 -205 -258```

### 输出

```
YES
YES
NO
YES
YES```

# AI分析结果

### 题目翻译
## 数组差异

### 题目描述
给定一个包含 $n$ 个整数的序列 $a_1, \, a_2, \, \dots, \, a_n$。

是否存在一个包含 $n$ 个整数的序列 $b_1, \, b_2, \, \dots, \, b_n$ 满足以下性质？
- 对于每个 $1 \le i \le n$，存在两个（不一定不同）的索引 $j$ 和 $k$（$1 \le j, \, k \le n$），使得 $a_i = b_j - b_k$。

### 说明/提示
在第一个测试用例中，序列 $b = [-9, \, 2, \, 1, \, 3, \, -2]$ 满足该性质。实际上，以下等式成立：
- $a_1 = 4 = 2 - (-2) = b_2 - b_5$；
- $a_2 = -7 = -9 - (-2) = b_1 - b_5$；
- $a_3 = -1 = 1 - 2 = b_3 - b_2$；
- $a_4 = 5 = 3 - (-2) = b_4 - b_5$；
- $a_5 = 10 = 1 - (-9) = b_3 - b_1$。

在第二个测试用例中，选择 $b = [0]$ 就足够了，因为 $a_1 = 0 = 0 - 0 = b_1 - b_1$。

在第三个测试用例中，可以证明不存在长度为 $3$ 的序列 $b$ 满足该性质。

### 样例 #1
#### 输入
```
5
5
4 -7 -1 5 10
1
0
3
1 10 100
4
-3 2 10 2
9
25 -171 250 174 152 242 100 -205 -258
```
#### 输出
```
YES
YES
NO
YES
YES
```

### 算法分类
搜索

### 综合分析与结论
这些题解的核心思路都是将问题转化为在数组 $a$ 中寻找一个子集，使得该子集的部分元素取反后和为 $0$。不同题解采用了不同的实现方法，包括深度优先搜索、枚举子集、动态规划等。

### 所选题解
- **作者：灵茶山艾府（4星）**
    - **关键亮点**：思路清晰，通过简单的数学推导将问题转化为判断是否存在两个子集和相等，代码简洁易懂。
    - **核心实现思想**：使用位运算枚举所有子集，计算子集和并存储在集合中，最后判断集合大小是否小于子集总数。
    - **核心代码**：
```go
package main
import ."fmt"

func main() {
    var T, n int
    for Scan(&T); T > 0; T-- {
        Scan(&n)
        a := make([]int, n)
        for i := range a {
            Scan(&a[i])
        }
        set := map[int]bool{}
        for i := 0; i < 1<<n; i++ {
            sum := 0
            for j, v := range a {
                sum += i >> j & 1 * v
            }
            set[sum] = true
        }
        if len(set) < 1<<n { // 至少有两个子集和相同
            Println("YES")
        } else {
            Println("NO")
        }
    }
}
```
- **作者：SSerxhs（4星）**
    - **关键亮点**：从图论的角度分析问题，将问题转化为寻找图中的环，通过深度优先搜索来实现。
    - **核心实现思想**：将 $a$ 数组中的元素看作边权，通过深度优先搜索寻找是否存在一个环，使得环中边权和为 $0$。
    - **核心代码**：
```cpp
read(T);
while (T--)
{
    read(n);m=1<<n;
    read(a-1,n);
    sort(a,a+n);
    for (i=0;i<n;i++) if (a[i]==0) break;
    if (i<n) {puts("YES");continue;}
    for (i=0;i+1<n;i++) if (a[i]==a[i+1]) break;
    if (i+1<n) {puts("YES");continue;}q=0;
    dfs(0,0,0);
    sort(b,b+q);
    if (*lower_bound(b,b+q,0)==0) puts("YES"); else puts("NO");
}
```
- **作者：_ZML_（4星）**
    - **关键亮点**：提供了两种实现方法，一种是动态规划，另一种是枚举所有状态，思路清晰，代码实现完整。
    - **核心实现思想**：动态规划方法通过递推推出所有可以组成的和，判断是否存在两个和相同的子集；枚举状态方法则是遍历所有可能的状态，判断是否存在一个状态使得子集和为 $0$。
    - **核心代码（动态规划）**：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
int T,n,dp[N],a[20];

void solve(){
    for(int i=0;i<N;i++) dp[i]=0;
    cin>>n; dp[0]=1; bool flag=false;
    for(int i=0;i<n;i++){ cin>>a[i]; a[i]=a[i]<0?-a[i]:a[i]; }
    for(int i=0;i<n;i++)
        for(int j=N-1-a[i];j>=0;j--)
            if(dp[j]){
                if(dp[j+a[i]]==1) flag=true;
                else dp[j+a[i]]=1;
            }
    cout<<(flag?"YES\n":"NO\n");
}

signed main(){
    ios::sync_with_stdio(false);
    for(cin>>T;T;T--) solve();
}
```

### 最优关键思路或技巧
- 利用数学推导将问题转化为寻找子集和为 $0$ 的问题，简化了问题的复杂度。
- 使用位运算枚举子集，提高了代码的效率。
- 从图论的角度分析问题，将问题转化为寻找图中的环，为问题的解决提供了新的思路。

### 拓展思路
同类型题或类似算法套路：
- 子集和问题：给定一个数组和一个目标值，判断是否存在一个子集的和等于目标值。
- 0 - 1 背包问题：给定一组物品，每个物品有重量和价值，在限定的总重量内，选择一些物品使得总价值最大。
- 组合总和问题：给定一个无重复元素的数组和一个目标数，找出数组中所有可以使数字和为目标数的组合。

### 推荐洛谷题目
- P1049 [NOIP2001 普及组] 装箱问题
- P2871 [USACO07DEC]Charm Bracelet S
- P1164 小A点菜

### 个人心得
题解中未包含个人心得。

---
处理用时：50.73秒