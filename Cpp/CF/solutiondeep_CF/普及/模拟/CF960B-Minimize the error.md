# 题目信息

# Minimize the error

## 题目描述

You are given two arrays $ A $ and $ B $ , each of size $ n $ . The error, $ E $ , between these two arrays is defined ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF960B/e950d33ee993b9f2e2ad61182c68b371192cc68e.png). You have to perform exactly $ k_{1} $ operations on array $ A $ and exactly $ k_{2} $ operations on array $ B $ . In one operation, you have to choose one element of the array and increase or decrease it by $ 1 $ .

Output the minimum possible value of error after $ k_{1} $ operations on array $ A $ and $ k_{2} $ operations on array $ B $ have been performed.

## 说明/提示

In the first sample case, we cannot perform any operations on $ A $ or $ B $ . Therefore the minimum possible error $ E=(1-2)^{2}+(2-3)^{2}=2 $ .

In the second sample case, we are required to perform exactly one operation on $ A $ . In order to minimize error, we increment the first element of $ A $ by $ 1 $ . Now, $ A=[2,2] $ . The error is now $ E=(2-2)^{2}+(2-2)^{2}=0 $ . This is the minimum possible error obtainable.

In the third sample case, we can increase the first element of $ A $ to $ 8 $ , using the all of the $ 5 $ moves available to us. Also, the first element of $ B $ can be reduced to $ 8 $ using the $ 6 $ of the $ 7 $ available moves. Now $ A=[8,4] $ and $ B=[8,4] $ . The error is now $ E=(8-8)^{2}+(4-4)^{2}=0 $ , but we are still left with $ 1 $ move for array $ B $ . Increasing the second element of $ B $ to $ 5 $ using the left move, we get $ B=[8,5] $ and $ E=(8-8)^{2}+(4-5)^{2}=1 $ .

## 样例 #1

### 输入

```
2 0 0
1 2
2 3
```

### 输出

```
2```

## 样例 #2

### 输入

```
2 1 0
1 2
2 2
```

### 输出

```
0```

## 样例 #3

### 输入

```
2 5 7
3 4
14 4
```

### 输出

```
1```

# AI分析结果

### 题目中文重写
# 最小化误差

## 题目描述
给定两个数组 $A$ 和 $B$，每个数组的大小均为 $n$。这两个数组之间的误差 $E$ 定义为 $\sum_{i = 1}^{n}(a_{i}-b_{i})^{2}$。你必须对数组 $A$ 恰好执行 $k_{1}$ 次操作，对数组 $B$ 恰好执行 $k_{2}$ 次操作。在一次操作中，你必须选择数组中的一个元素并将其加 1 或减 1。

输出在对数组 $A$ 执行 $k_{1}$ 次操作和对数组 $B$ 执行 $k_{2}$ 次操作后，误差的最小可能值。

## 说明/提示
在第一个样例中，我们不能对 $A$ 或 $B$ 执行任何操作。因此，最小可能误差 $E=(1 - 2)^{2}+(2 - 3)^{2}=2$。

在第二个样例中，我们需要对 $A$ 恰好执行一次操作。为了最小化误差，我们将 $A$ 的第一个元素加 1。现在，$A = [2, 2]$。此时误差为 $E=(2 - 2)^{2}+(2 - 2)^{2}=0$，这是可获得的最小误差。

在第三个样例中，我们可以使用对 $A$ 可用的全部 5 次操作将 $A$ 的第一个元素增加到 8。同样，使用对 $B$ 可用的 7 次操作中的 6 次，将 $B$ 的第一个元素减少到 8。现在 $A = [8, 4]$，$B = [8, 4]$。此时误差为 $E=(8 - 8)^{2}+(4 - 4)^{2}=0$，但我们对数组 $B$ 仍有 1 次操作可用。使用剩余的操作将 $B$ 的第二个元素增加到 5，我们得到 $B = [8, 5]$，误差 $E=(8 - 8)^{2}+(4 - 5)^{2}=1$。

## 样例 #1
### 输入
```
2 0 0
1 2
2 3
```
### 输出
```
2
```

## 样例 #2
### 输入
```
2 1 0
1 2
2 2
```
### 输出
```
0
```

## 样例 #3
### 输入
```
2 5 7
3 4
14 4
```
### 输出
```
1
```

### 综合分析与结论
- **思路**：所有题解均采用贪心算法，核心思路是将 $k_1$ 和 $k_2$ 合并为总操作次数，因为对 $A$ 数组的操作和对 $B$ 数组的相反操作效果等价。为使误差 $\sum_{i = 1}^{n}(a_{i}-b_{i})^{2}$ 最小，每次操作都应选择 $|a_{i}-b_{i}|$ 最大的元素进行加 1 或减 1 操作。
- **算法要点**：
    - 计算 $|a_{i}-b_{i}|$ 并存储。
    - 使用优先队列（大顶堆）维护 $|a_{i}-b_{i}|$ 的最大值。
    - 进行 $k_1 + k_2$ 次操作，每次取出队首元素进行调整后再放回队列。
    - 最后计算队列中元素的平方和作为结果。
- **解决难点**：
    - **操作等价性**：通过分析发现对 $A$ 数组和 $B$ 数组的操作可合并，简化问题。
    - **贪心策略**：证明每次选择 $|a_{i}-b_{i}|$ 最大的元素操作能使误差最小。
    - **边界情况**：当所有 $|a_{i}-b_{i}|$ 都为 0 时，仍需进行操作，此时将一个元素加 1。
    - **数据类型**：使用 `long long` 避免结果溢出。

### 高评分题解
- **作者：DarkShadow（5星）**
    - **关键亮点**：思路清晰，详细说明了贪心策略和注意事项，代码简洁易懂，注释丰富。
    - **核心代码**：
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
int n,A[1005],B[1005],k1,k2;
priority_queue<int> q;
int main(){
    int t;
    ll ans=0ll;
    scanf("%d%d%d",&n,&k1,&k2);
    k1+=k2;
    for(int i=1;i<=n;i++)
        scanf("%d",&A[i]);
    for(int i=1;i<=n;i++)
        scanf("%d",&B[i]);
    for(int i=1;i<=n;i++)
        q.push(abs(A[i]-B[i]));
    for(int i=1;i<=k1;i++){
        t=q.top();
        q.pop();
        if(t>0)  t--;
        else  t++;
        q.push(t);
    }
    for(int i=1;i<=n;i++){
        t=q.top();
        q.pop();
        ans+=(ll)(t)*(ll)(t);
    }
    printf("%lld",ans);
    return 0;
}
```
- **作者：w33z8kqrqk8zzzx33（4星）**
    - **关键亮点**：思路简洁明了，代码规范，使用了宏定义简化代码。
    - **核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;

#define iter(i, a, b) for(int i=(a); i<(b); i++)
#define rep(i, a) iter(i, 0, a)
#define rep1(i, a) iter(i, 1, (a)+1)
#define fi first
#define se second
#define pb push_back
 
#define ll long long
#define pii pair<int, int>

int a[1003], b[1003];
priority_queue<int, vector<int>> pq;

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n, k1, k2; cin >> n >> k1 >> k2;
    k1 += k2;
    rep(i, n) cin >> a[i];
    rep(i, n) {
        cin >> b[i];
        pq.push(abs(a[i]-b[i]));
    }
    while(k1--) {
        int t = pq.top(); pq.pop();
        if(t == 0) pq.push(1);
        else pq.push(t-1);
    }
    ll ans = 0;
    while(pq.size()) {
        ans = ans + 1ll * pq.top() * pq.top();
        pq.pop();
    }
    cout << ans << endl;
}
```
- **作者：Mzh2012（4星）**
    - **关键亮点**：思路清晰，代码简洁，对关键步骤有注释。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;

long long a[10005],b[10005];
priority_queue<long long> q;

int main(){
    long long n,k1,k2;
    cin>>n>>k1>>k2;
    for(long long i = 1;i<=n;i++) cin>>a[i];
    for(long long i = 1;i<=n;i++) cin>>b[i];
    for(int i = 1;i<=n;i++) q.push(abs(a[i]-b[i]));
    for(long long i = 1;i<=k1+k2;i++){
        long long tmp = q.top();
        q.pop();
        if(tmp>0) tmp--;
        else tmp++;
        q.push(tmp);
    }
    long long cnt = 0;
    while(!q.empty()){
        long long tmp = q.top();
        q.pop();
        cnt+=tmp*tmp;
    }
    cout<<cnt;
    return 0;
}
```

### 最优关键思路或技巧
- **贪心策略**：每次选择 $|a_{i}-b_{i}|$ 最大的元素进行操作，因为差值越大，其平方的变化对总和的影响越大。
- **优先队列**：使用优先队列（大顶堆）可以高效地维护 $|a_{i}-b_{i}|$ 的最大值，每次操作的时间复杂度为 $O(\log n)$。
- **操作合并**：将对 $A$ 数组和 $B$ 数组的操作合并为总操作次数，简化问题。

### 拓展思路
同类型题或类似算法套路：
- 其他涉及数组操作和最小化目标值的贪心问题，如通过有限次操作使数组元素的某种统计量最小。
- 利用优先队列维护最大值或最小值的问题，如哈夫曼编码问题。

### 推荐题目
- [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)：使用优先队列（小顶堆）解决合并果子的最小代价问题。
- [P1801 黑匣子](https://www.luogu.com.cn/problem/P1801)：使用优先队列动态维护第 $k$ 小的数。
- [P2085 最小函数值](https://www.luogu.com.cn/problem/P2085)：使用优先队列找出多个函数值中的最小值。

### 个人心得摘录与总结
- **作者：codeLJH114514**：最初提交代码出现 `WA`，错误信息显示结果为负数，发现是没有使用 `long long` 导致溢出，提醒在处理可能较大的结果时要注意数据类型。 

---
处理用时：53.77秒