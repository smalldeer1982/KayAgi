# 题目信息

# Adding Powers

## 题目描述

Suppose you are performing the following algorithm. There is an array $ v_1, v_2, \dots, v_n $ filled with zeroes at start. The following operation is applied to the array several times — at $ i $ -th step ( $ 0 $ -indexed) you can:

- either choose position $ pos $ ( $ 1 \le pos \le n $ ) and increase $ v_{pos} $ by $ k^i $ ;
- or not choose any position and skip this step.

You can choose how the algorithm would behave on each step and when to stop it. The question is: can you make array $ v $ equal to the given array $ a $ ( $ v_j = a_j $ for each $ j $ ) after some step?

## 说明/提示

In the first test case, you can stop the algorithm before the $ 0 $ -th step, or don't choose any position several times and stop the algorithm.

In the second test case, you can add $ k^0 $ to $ v_1 $ and stop the algorithm.

In the third test case, you can't make two $ 1 $ in the array $ v $ .

In the fifth test case, you can skip $ 9^0 $ and $ 9^1 $ , then add $ 9^2 $ and $ 9^3 $ to $ v_3 $ , skip $ 9^4 $ and finally, add $ 9^5 $ to $ v_2 $ .

## 样例 #1

### 输入

```
5
4 100
0 0 0 0
1 2
1
3 4
1 4 1
3 2
0 1 3
3 9
0 59049 810```

### 输出

```
YES
YES
NO
NO
YES```

# AI分析结果

### 题目内容（中文重写）
# 累加幂次

## 题目描述
假设你正在执行以下算法。一开始有一个数组 $ v_1, v_2, \dots, v_n $，其所有元素都初始化为 0。对该数组执行若干次以下操作 —— 在第 $ i $ 步（从 0 开始索引），你可以：
- 要么选择一个位置 $ pos $（$ 1 \le pos \le n $），并将 $ v_{pos} $ 增加 $ k^i $；
- 要么不选择任何位置，跳过这一步。

你可以自行决定算法在每一步的行为以及何时停止。问题是：在经过若干步之后，能否使数组 $ v $ 等于给定的数组 $ a $（即对于每个 $ j $，都有 $ v_j = a_j $）？

## 说明/提示
在第一个测试用例中，你可以在第 0 步之前停止算法，或者多次不选择任何位置，然后停止算法。

在第二个测试用例中，你可以将 $ k^0 $ 加到 $ v_1 $ 上，然后停止算法。

在第三个测试用例中，你无法在数组 $ v $ 中得到两个 1。

在第五个测试用例中，你可以跳过 $ 9^0 $ 和 $ 9^1 $，然后将 $ 9^2 $ 和 $ 9^3 $ 加到 $ v_3 $ 上，跳过 $ 9^4 $，最后将 $ 9^5 $ 加到 $ v_2 $ 上。

## 样例 #1
### 输入
```
5
4 100
0 0 0 0
1 2
1
3 4
1 4 1
3 2
0 1 3
3 9
0 59049 810
```
### 输出
```
YES
YES
NO
NO
YES
```

### 算法分类
进制

### 综合分析与结论
这些题解的核心思路都是将数组中的每个数转换为 $k$ 进制，然后检查 $k$ 进制表示中每一位的计数是否超过 1。若超过 1，则无法通过给定操作得到目标数组；否则可以。

不同题解的主要区别在于代码实现细节，如有的使用递归进行进制转换，有的使用循环；有的提前处理特殊情况（如 $k = 1$），有的则在后续逻辑中处理。

### 所选题解
- **C C A（5星）**
    - **关键亮点**：思路清晰，详细阐述了错误原因和正确做法，通过对比错误代码和正确代码，让读者更易理解。
    - **个人心得**：作者提到参照转换二进制的写法出错，原因是二进制最大数字只有 1，而 $k$ 进制最大数可能为 $k - 1$，所以要取余数，提醒读者在处理不同进制问题时要注意细节。
- **Refined_heart（4星）**
    - **关键亮点**：考虑到数据范围小，采用暴力做法，思路直接，代码实现简洁，对无解情况的分析清晰。
    - **个人心得**：提醒读者别忘了清空指数记录数组，别忘了开 `long long`，避免常见错误。
- **yimuhua（4星）**
    - **关键亮点**：思路简洁明了，直接指出将数分解成 $k$ 进制后有值的位计数加一，若计数大于一，则无法变为目标数组，代码实现也很简洁。

### 重点代码
#### C C A 的正确代码
```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 100 + 10;
const long long inf = 1e16 + 10;

long long T , n , k , cnt , a[N] , vis[N] , fac[N];

int main(){
    scanf("%lld" , &T); while(T--){
        memset(vis , 0 , sizeof(vis));
        scanf("%lld %lld" , &n , &k);
        fac[0] = 1; for(int i = 1; fac[i - 1] < inf; i++)
            fac[i] = fac[i - 1] * k , cnt = i;
        for(int i = 1; i <= n; i++) scanf("%lld" , &a[i]);
        for(int i = 1; i <= n; i++){
            int j = 0; while(a[i]){
                vis[j] += a[i] % k;
                a[i] /= k , j++;
            }
        }
        bool flag = false;
        for(int i = 0; i <= cnt; i++)
            if(vis[i] > 1) flag = true;
        flag ? puts("NO") : puts("YES");
    }
    return 0;
}
```
**核心实现思想**：先预处理 $k$ 的幂次，然后将数组中的每个数转换为 $k$ 进制，统计每一位的计数，最后检查是否有计数超过 1 的位。

#### Refined_heart 的代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int T,n,k,a[200010];
int mp[2000];
bool work(int x){
    while(x){
        int r=0;
        int base=1;
        while(x>=base){
            r++;base*=k;
        }
        base/=k;r--;x-=base;mp[r]++;
        if(mp[r]>1)return 0;
    }
    return 1;
}
signed main(){
    scanf("%lld",&T);
    while(T--){
        scanf("%lld%lld",&n,&k);
        for(int i=1;i<=n;++i)scanf("%lld",&a[i]);
        if(k==1){puts("YES");continue;}int fg=0;
        for(int i=1;i<=n;++i){
            if(a[i]==0)continue;
            if(!work(a[i])){
                puts("NO");
                fg=1;break;
            }
        }
        if(!fg)puts("YES");
        for(int i=0;i<=200;++i)mp[i]=0;
    }
    return 0;
}
```
**核心实现思想**：对于每个数，将其分解为 $k$ 的幂次之和，同时记录指数的出现次数，若出现重复则返回 `false`。

#### yimuhua 的代码
```cpp
#include <bits/stdc++.h>
using namespace std;
long long t, n, k, tmp, a[105], cnt[105];
int main() {
    cin >> t;
    while(t--) {
        bool f = 1;
        cin >> n >> k, memset(cnt, 0, sizeof(cnt)), tmp = 0;
        for(long long i = 1, x; i <= n; i++) {
            cin >> x;
            for(long long j = 0; x;)
                cnt[j] += x % k, x /= k, tmp = max(tmp, ++j);
        }
        for(long long i = 0; i < tmp; i++)
            if(cnt[i] > 1)
                f = 0;
        cout << (f ? "YES\n" : "NO\n");
    }
    return 0;
}
```
**核心实现思想**：将每个数转换为 $k$ 进制，统计每一位的计数，最后检查是否有计数超过 1 的位。

### 最优关键思路或技巧
- **进制转换**：将数组中的每个数转换为 $k$ 进制，通过检查 $k$ 进制表示中每一位的计数来判断是否能得到目标数组。
- **计数统计**：使用数组记录 $k$ 进制每一位的计数，方便检查是否有重复。

### 拓展思路
同类型题可能会有不同的操作规则或限制条件，但核心思路仍然是将数转换为特定进制进行分析。例如，可能会限制操作次数，或者改变每次操作增加的数值。类似算法套路包括处理与进制相关的问题时，要注意不同进制的特点，以及如何通过进制转换来解决问题。

### 推荐洛谷题目
- P1143 进制转换
- P1604 B进制星球
- P2084 进制转换

---
处理用时：56.27秒