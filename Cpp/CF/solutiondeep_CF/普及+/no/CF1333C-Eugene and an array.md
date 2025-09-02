# 题目信息

# Eugene and an array

## 题目描述

Eugene likes working with arrays. And today he needs your help in solving one challenging task.

An array $ c $ is a subarray of an array $ b $ if $ c $ can be obtained from $ b $ by deletion of several (possibly, zero or all) elements from the beginning and several (possibly, zero or all) elements from the end.

Let's call a nonempty array good if for every nonempty subarray of this array, sum of the elements of this subarray is nonzero. For example, array $ [-1, 2, -3] $ is good, as all arrays $ [-1] $ , $ [-1, 2] $ , $ [-1, 2, -3] $ , $ [2] $ , $ [2, -3] $ , $ [-3] $ have nonzero sums of elements. However, array $ [-1, 2, -1, -3] $ isn't good, as his subarray $ [-1, 2, -1] $ has sum of elements equal to $ 0 $ .

Help Eugene to calculate the number of nonempty good subarrays of a given array $ a $ .

## 说明/提示

In the first sample, the following subarrays are good: $ [1] $ , $ [1, 2] $ , $ [2] $ , $ [2, -3] $ , $ [-3] $ . However, the subarray $ [1, 2, -3] $ isn't good, as its subarray $ [1, 2, -3] $ has sum of elements equal to $ 0 $ .

In the second sample, three subarrays of size 1 are the only good subarrays. At the same time, the subarray $ [41, -41, 41] $ isn't good, as its subarray $ [41, -41] $ has sum of elements equal to $ 0 $ .

## 样例 #1

### 输入

```
3
1 2 -3```

### 输出

```
5```

## 样例 #2

### 输入

```
3
41 -41 41```

### 输出

```
3```

# AI分析结果

### 题目翻译
# 尤金和数组

## 题目描述
尤金喜欢处理数组。今天，他需要你帮忙解决一个具有挑战性的任务。

如果数组 $ c $ 可以通过从数组 $ b $ 的开头删除若干（可能为零个或全部）元素，以及从结尾删除若干（可能为零个或全部）元素得到，那么数组 $ c $ 就是数组 $ b $ 的一个子数组。

如果一个非空数组的每个非空子数组的元素和都不为零，那么我们称这个非空数组是“好的”。例如，数组 $ [-1, 2, -3] $ 是好的，因为所有子数组 $ [-1] $、$ [-1, 2] $、$ [-1, 2, -3] $、$ [2] $、$ [2, -3] $、$ [-3] $ 的元素和都不为零。然而，数组 $ [-1, 2, -1, -3] $ 不是好的，因为它的子数组 $ [-1, 2, -1] $ 的元素和为 $ 0 $。

请帮助尤金计算给定数组 $ a $ 中“好的”非空子数组的数量。

## 说明/提示
在第一个样例中，以下子数组是好的：$ [1] $、$ [1, 2] $、$ [2] $、$ [2, -3] $、$ [-3] $。然而，子数组 $ [1, 2, -3] $ 不是好的，因为它本身的元素和为 $ 0 $。

在第二个样例中，三个长度为 $ 1 $ 的子数组是仅有的好子数组。同时，子数组 $ [41, -41, 41] $ 不是好的，因为它的子数组 $ [41, -41] $ 的元素和为 $ 0 $。

## 样例 #1
### 输入
```
3
1 2 -3
```
### 输出
```
5
```

## 样例 #2
### 输入
```
3
41 -41 41
```
### 输出
```
3
```

### 算法分类
前缀和

### 综合分析与结论
这些题解主要围绕前缀和的思路来解决问题。核心逻辑是利用前缀和判断子数组的和是否为 0，进而确定“好的”子数组的数量。大部分题解通过枚举右端点，维护左端点的范围来计算答案。

不同题解的差异主要体现在代码实现细节和对 `unordered_map` 的使用上。部分题解提到了 `unordered_map` 可能被卡的问题，并给出了自定义哈希函数的解决方案。

### 所选题解
- **AutumnKite（5星）**
    - **关键亮点**：思路清晰，代码简洁，详细阐述了前缀和与合法区间的关系，通过维护 `lst` 数组的前缀最大值来计算答案。
- **Lskkkno1（4星）**
    - **关键亮点**：不仅给出了常规的解题思路，还针对 `unordered_map` 可能被卡的问题，提供了自定义哈希函数的解决方案，具有一定的实用性。
- **PDAST（4星）**
    - **关键亮点**：代码简洁，采用贪心策略，每次加上右端点减左端点作为答案，易于理解。

### 重点代码
#### AutumnKite 的代码
```cpp
const int N = 200005;

int n, lst[N];
long long a[N];
std::map<long long, int> M;

void solve() {
    read(n);
    for (int i = 1; i <= n; ++i) {
        read(a[i]);
        a[i] += a[i - 1];
    }
    for (int i = 0; i <= n; ++i) { // 用 std::map 计算 lst 数组
        if (!M.count(a[i])) {
            lst[i] = -1;
        } else {
            lst[i] = M[a[i]];
        }
        M[a[i]] = i;
    }
    int mx = -1;
    long long ans = 0;
    for (int i = 0; i <= n; ++i) {
        mx = std::max(mx, lst[i]);
        ans += i - mx - 1;
    }
    print(ans);
}
```
**核心实现思想**：先计算前缀和数组 `a`，再用 `map` 计算 `lst` 数组，记录上一个与当前前缀和相同的位置。最后枚举右端点，维护 `lst` 数组的前缀最大值 `mx`，计算答案。

#### Lskkkno1 的代码
```cpp
struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x ^= x << 13;
        x ^= x >> 7;
        x ^= x << 17;
        return x; 
    }
    size_t operator () (uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count(); // 时间戳
        return splitmix64(x + FIXED_RANDOM);
    }
};

unordered_map<uint64_t, int, custom_hash> safe_map;

// 主代码部分
int main() {
    scanf("%d", &n);
    p[0] = 0;
    long long psum = 0;
    for(int i = 1, x; i <= n; ++i) {
        scanf("%d", &x);
        psum += x;
        if(p.count(psum))
            rig[i] = p[psum] + 1;
        p[psum] = i;
    }
    long long ans = 0;
    for(int i = 1, rigMost = 0; i <= n; ++i) {
        rigMost = max(rigMost, rig[i]);
        ans += i - rigMost;
    }
    printf("%lld\n", ans);
    return 0;
}
```
**核心实现思想**：自定义哈希函数 `custom_hash`，用于防止 `unordered_map` 被卡。计算前缀和 `psum`，记录每个前缀和第一次出现的位置，更新 `rig` 数组。最后枚举右端点，维护 `rigMost`，计算答案。

#### PDAST 的代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int ans,sum,x,n,l;
map<int,int>mp;
signed main(){
    cin>>n;
    mp[0]=0;
    for(int i=1;i<=n;i++){
        cin>>x;
        sum+=x;
        if(mp.count(sum))l=max(l,mp[sum]+1);
        ans+=i-l;
        mp[sum]=i;
    }
    cout<<ans;
    return 0;
}
```
**核心实现思想**：使用 `map` 记录前缀和第一次出现的位置。计算前缀和 `sum`，如果当前前缀和已经出现过，更新左端点 `l`。每次枚举右端点，计算答案。

### 最优关键思路或技巧
- **前缀和的运用**：通过计算前缀和，可以快速判断子数组的和是否为 0，将问题转化为判断前缀和是否相等。
- **枚举右端点**：固定右端点，维护左端点的范围，避免了对所有子数组的枚举，降低了时间复杂度。
- **使用 `map` 记录**：使用 `map` 记录每个前缀和第一次出现的位置，方便快速查找和更新。

### 拓展思路
同类型题或类似算法套路：
- 求数组中满足特定和条件的子数组数量，如和为某个定值、和大于某个值等。
- 求数组中最长的满足特定条件的子数组长度。

### 推荐题目
- [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)
- [P2671 [NOIP2015 普及组] 求和](https://www.luogu.com.cn/problem/P2671)
- [P3156 [CQOI2011] 分金币](https://www.luogu.com.cn/problem/P3156)

### 个人心得摘录与总结
- **Lskkkno1**：提到很多用 `unordered_map` 的题解被卡，原因是 CF 上的大神会根据 STL 源代码构造 hack 数据，导致 `unordered_map` 单次复杂度劣化成 $O(n)$。解决方法是自定义哈希函数，让哈希函数与时间戳有关，防止被卡。

---
处理用时：55.51秒