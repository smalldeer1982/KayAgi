# 题目信息

# Moamen and k-subarrays

## 题目描述

Moamen has an array of $ n $ distinct integers. He wants to sort that array in non-decreasing order by doing the following operations in order exactly once:

1. Split the array into exactly $ k $ non-empty subarrays such that each element belongs to exactly one subarray.
2. Reorder these subarrays arbitrary.
3. Merge the subarrays in their new order.

A sequence $ a $ is a subarray of a sequence $ b $ if $ a $ can be obtained from $ b $ by deletion of several (possibly, zero or all) elements from the beginning and several (possibly, zero or all) elements from the end.

Can you tell Moamen if there is a way to sort the array in non-decreasing order using the operations written above?

## 说明/提示

In the first test case, $ a = [6, 3, 4, 2, 1] $ , and $ k = 4 $ , so we can do the operations as follows:

1. Split $ a $ into $ \{ [6], [3, 4], [2], [1] \} $ .
2. Reorder them: $ \{ [1], [2], [3,4], [6] \} $ .
3. Merge them: $ [1, 2, 3, 4, 6] $ , so now the array is sorted.

In the second test case, there is no way to sort the array by splitting it into only $ 2 $ subarrays.

As an example, if we split it into $ \{ [1, -4], [0, -2] \} $ , we can reorder them into $ \{ [1, -4], [0, -2] \} $ or $ \{ [0, -2], [1, -4] \} $ . However, after merging the subarrays, it is impossible to get a sorted array.

## 样例 #1

### 输入

```
3
5 4
6 3 4 2 1
4 2
1 -4 0 -2
5 1
1 2 3 4 5```

### 输出

```
Yes
No
Yes```

# AI分析结果

### 题目内容
# Moamen和k子数组

## 题目描述
Moamen有一个包含n个不同整数的数组。他想通过按顺序执行以下操作，将该数组按非递减顺序排序：
1. 将数组恰好拆分为k个非空子数组，使得每个元素恰好属于一个子数组。
2. 任意重新排列这些子数组。
3. 按新顺序合并这些子数组。

序列a是序列b的子数组，如果a可以通过从b的开头删除若干（可能为零个或全部）元素，以及从b的末尾删除若干（可能为零个或全部）元素而得到。

你能告诉Moamen是否有一种方法可以使用上述操作对数组进行排序吗？

## 说明/提示
在第一个测试用例中，a = [6, 3, 4, 2, 1]，k = 4，所以我们可以按如下方式执行操作：
1. 将a拆分为{ [6], [3, 4], [2], [1] }。
2. 重新排列它们：{ [1], [2], [3,4], [6] }。
3. 合并它们：[1, 2, 3, 4, 6]，此时数组已排序。

在第二个测试用例中，不存在将数组拆分为仅2个子数组来进行排序的方法。

例如，如果我们将其拆分为{ [1, -4], [0, -2] }，我们可以将它们重新排列为{ [1, -4], [0, -2] }或{ [0, -2], [1, -4] }。然而，在合并子数组后，不可能得到一个已排序的数组。

## 样例 #1
### 输入
```
3
5 4
6 3 4 2 1
4 2
1 -4 0 -2
5 1
1 2 3 4 5
```
### 输出
```
Yes
No
Yes
```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路较为一致，都是先对原数组按数值从小到大排序，同时记录每个元素在原数组中的位置信息。然后通过遍历排序后的数组，判断相邻元素在原数组中的位置是否连续，若不连续则说明需要新增一个子数组，统计这样的子数组数量，与给定的k进行比较，若子数组数量小于等于k则输出Yes，否则输出No。不同题解在具体实现细节和代码风格上有所差异。

### 所选的题解
- **作者：Eason_AC (5星)**
    - **关键亮点**：思路清晰，代码简洁高效，通过自定义比较函数对元素编号进行排序，利用简洁的循环统计子数组数量。
    - **重点代码**：
```cpp
namespace Solution {
    int a[100007], id[100007];
    ib cmp(int ida, int idb) {return a[ida] < a[idb];}
    iv Main() {
        MT {
            int n = Rint, k = Rint, cnt = 1;
            F(int, i, 1, n) a[i] = Rint, id[i] = i;
            sort(id + 1, id + n + 1, cmp);
            F(int, i, 2, n) if(id[i]!= id[i - 1] + 1) cnt++;
            cnt > k? No : Yes;
        }
        return;
    }
}
```
    - **核心实现思想**：先读入数组元素和编号，通过自定义比较函数cmp对编号按对应元素值从小到大排序，然后遍历排序后的编号数组，若相邻编号不连续则子数组数量加1，最后根据子数组数量与k的比较结果输出。
- **作者：LRL65 (5星)**
    - **关键亮点**：代码逻辑清晰易懂，直接使用结构体存储元素值和编号，排序后直观地通过遍历结构体数组统计子数组数量。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int n,k;
struct node {
    int name,x;
}a[100005];
bool cmp(node a,node b) {
    return a.x<b.x;
}
int main() {
    cin>>t;
    while(t--) {
        cin>>n>>k;
        for(int i=1;i<=n;i++)cin>>a[i].x,a[i].name=i;
        sort(a+1,a+n+1,cmp);
        int cnt=1;
        for(int i=2;i<=n;i++)
            if(a[i].name!=a[i-1].name+1)cnt++;
        if(cnt>k)cout<<"No"<<endl;
        else cout<<"Yes"<<endl;
    }
}
```
    - **核心实现思想**：定义结构体node存储元素值x和编号name，读入数据后按元素值排序，遍历排序后的结构体数组，若相邻元素编号不连续则子数组数量加1，根据子数组数量与k的比较输出结果。
- **作者：Zachary_Cloud (4星)**
    - **关键亮点**：代码结构完整，使用了结构体和标准库函数，注释详细，便于理解。先对结构体数组按值排序，再通过辅助数组记录元素在排序后的位置，从而统计子数组数量。
    - **重点代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0)
int T,n,k,a[100010];
struct node {
    int val,id;
} b[100010];
bool cmp(node a,node b) {
    return a.val<b.val;
}
signed main() {
    IOS; cin>>T;
    while (T--) {
        cin>>n>>k; int ans=1;
        for (int i=1;i<=n;++i) cin>>b[i].val,b[i].id=i;
        sort(b+1,b+n+1,cmp);
        for (int i=1;i<=n;++i) a[b[i].id]=i;
        for (int i=2;i<=n;++i) if (a[i]!=a[i-1]+1) ++ans;
        if (ans<=k) cout<<"Yes"<<endl;
        else cout<<"No"<<endl;
    }
    return 0;
}
```
    - **核心实现思想**：定义结构体node存储元素值val和编号id，读入数据后按值排序，通过循环将排序后的元素位置存入辅助数组a，再遍历a数组，若相邻位置不连续则子数组数量加1，根据子数组数量与k的比较输出结果。

### 最优关键思路或技巧
通过对原数组元素值排序并结合元素在原数组中的位置信息，利用贪心思想，以相邻元素在原数组位置是否连续来确定子数组划分，从而判断能否通过给定的k个子数组操作实现排序。

### 可拓展之处
同类型题可关注涉及数组划分、排序后满足特定条件的问题，类似算法套路是在处理数组相关问题时，结合排序和元素位置信息，利用贪心策略解决。

### 洛谷题目推荐
- [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
- [P1248 加工生产调度](https://www.luogu.com.cn/problem/P1248)
- [P2123 皇后游戏](https://www.luogu.com.cn/problem/P2123)

### 个人心得摘录与总结
无。 

---
处理用时：51.82秒