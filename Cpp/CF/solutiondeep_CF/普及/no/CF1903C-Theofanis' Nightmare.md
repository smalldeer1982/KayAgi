# 题目信息

# Theofanis' Nightmare

## 题目描述

Theofanis easily gets obsessed with problems before going to sleep and often has nightmares about them. To deal with his obsession he visited his doctor, Dr. Emix.

In his latest nightmare, he has an array $ a $ of size $ n $ and wants to divide it into non-empty subarrays $ ^{\dagger} $ such that every element is in exactly one of the subarrays.

For example, the array $ [1,-3,7,-6,2,5] $ can be divided to $ [1] [-3,7] [-6,2] [5] $ .

The Cypriot value of such division is equal to $ \Sigma_{i=1}^{k} i \cdot \mathrm{sum}_i $ where $ k $ is the number of subarrays that we divided the array into and $ \mathrm{sum}_i $ is the sum of the $ i $ -th subarray.

The Cypriot value of this division of the array $ [1] [-3,7] [-6,2] [5] = 1 \cdot 1 + 2 \cdot (-3 + 7) + 3 \cdot (-6 + 2) + 4 \cdot 5 = 17 $ .

Theofanis is wondering what is the maximum Cypriot value of any division of the array.

 $ ^{\dagger} $ An array $ b $ is a subarray of an array $ a $ if $ b $ can be obtained from $ a $ by deletion of several (possibly, zero or all) elements from the beginning and several (possibly, zero or all) elements from the end. In particular, an array is a subarray of itself.

## 说明/提示

In the first test case, to get the maximum Cypriot value we divide the array into $ [1][-3][7][-6][2][5] $ which gives us: $ \Sigma_{i=1}^{k} i \cdot \mathrm{sum}_i = 1 \cdot 1 + 2 \cdot (-3) + 3 \cdot 7 + 4 \cdot (-6) + 5 \cdot 2 + 6 \cdot 5 = 32 $

Similarly, in the second test case we divide the array into $ [2][9,-5,-3] $ which gives us $ \Sigma_{i=1}^{k} i \cdot \mathrm{sum}_i = 1 \cdot 2 + 2 \cdot (9 + (-5) + (-3)) = 4 $ .

## 样例 #1

### 输入

```
4
6
1 -3 7 -6 2 5
4
2 9 -5 -3
8
-3 -4 2 -5 1 10 17 23
1
830```

### 输出

```
32
4
343
830```

# AI分析结果



# Theofanis的噩梦

## 题目描述

给定一个长度为 $n$ 的数组 $a$，将其划分为若干非空子数组，使得每个元素恰好属于一个子数组。Cypriot值为 $\sum_{i=1}^k i \cdot \mathrm{sum}_i$，其中 $k$ 是子数组个数，$\mathrm{sum}_i$ 是第 $i$ 个子数组元素和。求最大Cypriot值。

## 算法分类
贪心

## 题解分析与结论

### 题解对比
1. **动态规划解法**（引领天下，4星）
   - 从后向前递推，维护每个位置到末尾的最大值
   - 状态转移方程：$f_i = \max(f_{i+1}+a_i, f_{i+1}+s+a_i)$
   - 时间复杂度 $O(n)$，空间复杂度 $O(n)$

2. **贪心解法**（fish_shit，5星）
   - 核心思路：每个分割点产生的贡献等于其后缀和的正值
   - 总答案 = 数组总和 + 所有正的后缀和
   - 时间复杂度 $O(n)$，空间复杂度 $O(1)$
   - 代码简洁高效，直接遍历维护后缀和

3. **贪心优化版**（MhxMa，5星）
   - 维护当前后缀和，遇到正值立即累加
   - 边界处理巧妙，代码实现更为精简

### 最优思路
通过观察发现，每次分割产生的额外收益等于分割点之后所有元素的正值后缀和。最优策略是**从后向前遍历，累加所有正值后缀和**，最终结果为数组总和加上这些正值后缀和的总和。

## 推荐题解代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+10;
#define int long long
int a[maxn];
signed main(){
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        int ans=0;
        for(int i=1;i<=n;i++){
            cin>>a[i];
            ans+=a[i];
        }
        int cnt=0;
        for(int i=n;i>=2;i--){
            cnt+=a[i];
            if(cnt>0){
                ans+=cnt;
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}
```

## 拓展与心得
- **关键技巧**：将分割问题转化为后缀和的正值判定，避免显式维护分段结构
- **类似问题**：区间分割最优化（如CF1895B、P1220关路灯）
- **心得**：逆向思维在分段问题中效果显著，应优先考虑后缀和性质

## 推荐题目
1. [P1220 关路灯](https://www.luogu.com.cn/problem/P1220)（动态规划+区间处理）
2. [CF1895B](https://codeforces.com/contest/1895/problem/B)（贪心+数组分割）
3. [P2887 挤奶时间](https://www.luogu.com.cn/problem/P2887)（贪心+区间调度）

---
处理用时：127.50秒