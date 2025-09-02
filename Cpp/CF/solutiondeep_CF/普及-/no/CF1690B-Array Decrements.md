# 题目信息

# Array Decrements

## 题目描述

Kristina has two arrays $ a $ and $ b $ , each containing $ n $ non-negative integers. She can perform the following operation on array $ a $ any number of times:

- apply a decrement to each non-zero element of the array, that is, replace the value of each element $ a_i $ such that $ a_i > 0 $ with the value $ a_i - 1 $ ( $ 1 \le i \le n $ ). If $ a_i $ was $ 0 $ , its value does not change.

Determine whether Kristina can get an array $ b $ from an array $ a $ in some number of operations (probably zero). In other words, can she make $ a_i = b_i $ after some number of operations for each $ 1 \le i \le n $ ?

For example, let $ n = 4 $ , $ a = [3, 5, 4, 1] $ and $ b = [1, 3, 2, 0] $ . In this case, she can apply the operation twice:

- after the first application of the operation she gets $ a = [2, 4, 3, 0] $ ;
- after the second use of the operation she gets $ a = [1, 3, 2, 0] $ .

Thus, in two operations, she can get an array $ b $ from an array $ a $ .

## 说明/提示

The first test case is analyzed in the statement.

In the second test case, it is enough to apply the operation to array $ a $ once.

In the third test case, it is impossible to get array $ b $ from array $ a $ .

## 样例 #1

### 输入

```
6
4
3 5 4 1
1 3 2 0
3
1 2 1
0 1 0
4
5 3 7 2
1 1 1 1
5
1 2 3 4 5
1 2 3 4 6
1
8
0
1
4
6```

### 输出

```
YES
YES
NO
NO
YES
NO```

# AI分析结果

### 题目内容
# 数组递减

## 题目描述
克里斯蒂娜（Kristina）有两个数组 $a$ 和 $b$，每个数组都包含 $n$ 个非负整数。她可以对数组 $a$ 执行以下操作任意次数：
- 对数组中的每个非零元素进行递减操作，即对于每个满足 $a_i > 0$ 的元素 $a_i$，将其值替换为 $a_i - 1$（$1 \leq i \leq n$）。如果 $a_i$ 为 $0$，其值不变。

判断克里斯蒂娜是否可以通过若干次操作（可能为零次）从数组 $a$ 得到数组 $b$。换句话说，对于每个 $1 \leq i \leq n$，她能否在经过若干次操作后使 $a_i = b_i$？

例如，设 $n = 4$，$a = [3, 5, 4, 1]$ 且 $b = [1, 3, 2, 0]$。在这种情况下，她可以执行两次操作：
- 第一次操作后，她得到 $a = [2, 4, 3, 0]$；
- 第二次操作后，她得到 $a = [1, 3, 2, 0]$。

因此，经过两次操作，她可以从数组 $a$ 得到数组 $b$。

## 说明/提示
第一个测试用例在题目描述中已分析。

在第二个测试用例中，对数组 $a$ 执行一次操作就足够了。

在第三个测试用例中，无法从数组 $a$ 得到数组 $b$。

## 样例 #1
### 输入
```
6
4
3 5 4 1
1 3 2 0
3
1 2 1
0 1 0
4
5 3 7 2
1 1 1 1
5
1 2 3 4 5
1 2 3 4 6
1
8
0
1
4
6
```
### 输出
```
YES
YES
NO
NO
YES
NO
```
### 算法分类
数学

### 题解综合分析与结论
这些题解的核心思路大多围绕判断数组 $a$ 能否通过特定操作转换为数组 $b$ 展开。要点在于：
1. **初始判断**：首先检查是否存在 $a_i < b_i$ 的情况，若有则直接判定为无法转换，输出“NO”。
2. **差值分析**：计算 $a_i - b_i$ 的值，多数题解通过找最大差值或者首个非零 $b_i$ 对应的差值作为基准，遍历数组检查其他位置的差值与基准的关系，同时考虑 $b_i = 0$ 的特殊情况。若所有非零 $b_i$ 对应的 $a_i - b_i$ 相等，且 $b_i = 0$ 时 $a_i$ 满足一定条件（如不大于最大差值），则可以转换，输出“YES”，否则输出“NO”。

各题解在实现细节上略有不同，但整体思路相似。

### 所选的题解
#### 作者：minVan (5星)
- **关键亮点**：思路清晰，代码简洁明了，通过两次遍历数组，第一次遍历检查 $a_i$ 是否小于 $b_i$ 并记录最大差值，第二次遍历根据最大差值判断能否从数组 $a$ 得到数组 $b$。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 50005;
int t, n;
int a[N], b[N];
int main() {
    cin >> t;
    while(t--) {
        cin >> n;
        for(int i = 1; i <= n; i++) {
            cin >> a[i];
        }
        for(int i = 1; i <= n; i++) {
            cin >> b[i];
        }
        bool flag = 1;
        int maxc = 0;
        for(int i = 1; i <= n; i++) {
            if(a[i] < b[i]) {
                flag = 0;
                break;
            }
            maxc = max(maxc, a[i] - b[i]);
        }
        if(!flag) {
            cout << "NO\n";
            continue;
        }
        for(int i = 1; i <= n; i++) {
            if(max(a[i] - maxc, 0)!= b[i]) {
                flag = 0;
                break;
            }
        }
        if(flag) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
    return 0;
}
```
核心实现思想：先遍历数组判断 $a_i$ 是否小于 $b_i$ 并找出最大差值 `maxc`，再遍历一次判断 `max(a[i] - maxc, 0)` 是否等于 $b_i$，以此确定能否转换。

#### 作者：liruixiong0101 (4星)
- **关键亮点**：思路直接，先处理 $b_i = 0$ 的情况，然后通过记录首个非零 $b_i$ 对应的 $a_i - b_i$ 的差值，遍历检查其他非零 $b_i$ 对应的差值是否与之相同，同时再次检查 $b_i = 0$ 时 $a_i$ 的条件。
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 5e4 + 5;
int T;
int main(){
    scanf("%d", &T);
    for(int n, a[N], b[N]; scanf("%d", &n) == 1 && T--;){
        for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
        int d = INT_MAX;
        bool flag = 1;
        for(int i = 1; i <= n; i++){
            scanf("%d", &b[i]);
            if(!b[i]) continue;
            if(a[i] < b[i]) flag = 0;
            if(d == INT_MAX) d = a[i] - b[i];
            if(a[i] - b[i]!= d) flag = 0;
        }
        for(int i = 1; i <= n; i++) if(!b[i]){
            if(a[i] > d) flag = 0;
        }
        if(flag) puts("YES");
        else puts("NO");
    }
    return 0;
}
```
核心实现思想：通过一次遍历处理非零 $b_i$ 的情况，记录差值并检查是否一致，再通过一次遍历检查 $b_i = 0$ 时 $a_i$ 是否满足条件。

#### 作者：LEle0309 (4星)
- **关键亮点**：同样是简洁的两次遍历，第一次遍历判断是否存在 $a_i < b_i$ 的情况，第二次遍历找出最大差值 `maxm`，然后根据最大差值判断能否从数组 $a$ 得到数组 $b$。
```cpp
#include<iostream>
using namespace std;
#define INF 0x7f7f7f7f
const int maxn=5e4+7;
int a[maxn],b[maxn],n,t,i,maxm=-INF;
int main()
{
    cin>>t;
    while(t--){
        cin>>n;bool flag=0;maxm=-INF;
        for(i=1;i<=n;i++)cin>>a[i];
        for(i=1;i<=n;i++)cin>>b[i];
        for(i=1;i<=n;i++)if(a[i]<b[i])flag=1;
        for(i=1;i<=n;i++)maxm=max(maxm,a[i]-b[i]);
        for(i=1;i<=n;i++)if(a[i]-maxm!=b[i]&&b[i]!=0)flag=1;
        if(flag)cout<<"NO\n";
        else cout<<"YES\n";
    }
    return 0;
}
```
核心实现思想：先检查是否存在 $a_i < b_i$，再找出最大差值 `maxm`，最后根据 `a[i] - maxm` 是否等于 $b_i$（$b_i$ 不为 $0$ 时）判断能否转换。

### 最优关键思路或技巧
最优的关键思路在于通过分析数组 $a$ 和 $b$ 对应元素差值的关系来判断能否转换。具体技巧为：先确定 $a_i$ 不小于 $b_i$，然后找出 $a_i - b_i$ 的最大差值（或首个非零 $b_i$ 对应的差值作为基准），根据这个基准去检查其他元素的差值是否满足条件，同时特别处理 $b_i = 0$ 的情况。

### 拓展
同类型题目通常围绕数组元素的特定操作和状态转换展开，类似算法套路是分析操作对数组元素的影响，通过找规律、确定关键条件来判断能否达到目标状态。

### 推荐题目
1. **洛谷 P1161 开灯**：通过对开关操作的分析，判断最终灯的状态，与本题类似在于分析操作对元素状态的影响。
2. **洛谷 P1909 买铅笔**：根据不同包装铅笔的价格和数量，选择最优购买方案，同样需要分析条件来确定结果。
3. **洛谷 P5723 【深基4.例13】质数口袋**：判断数字是否为质数并进行累加等操作，与本题类似，都需要根据一定规则对数据进行处理和判断。 

---
处理用时：61.81秒