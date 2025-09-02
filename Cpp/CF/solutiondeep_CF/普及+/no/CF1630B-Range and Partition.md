# 题目信息

# Range and Partition

## 题目描述

Given an array $ a $ of $ n $ integers, find a range of values $ [x, y] $ ( $ x \le y $ ), and split $ a $ into exactly $ k $ ( $ 1 \le k \le n $ ) subarrays in such a way that:

- Each subarray is formed by several continuous elements of $ a $ , that is, it is equal to $ a_l, a_{l+1}, \ldots, a_r $ for some $ l $ and $ r $ ( $ 1 \leq l \leq r \leq n $ ).
- Each element from $ a $ belongs to exactly one subarray.
- In each subarray the number of elements inside the range $ [x, y] $ (inclusive) is strictly greater than the number of elements outside the range. An element with index $ i $ is inside the range $ [x, y] $ if and only if $ x \le a_i \le y $ .

Print any solution that minimizes $ y - x $ .

## 说明/提示

In the first test, there should be only one subarray, which must be equal to the whole array. There are $ 2 $ elements inside the range $ [1, 2] $ and $ 0 $ elements outside, if the chosen range is $ [1, 1] $ , there will be $ 1 $ element inside ( $ a_1 $ ) and $ 1 $ element outside ( $ a_2 $ ), and the answer will be invalid.

In the second test, it is possible to choose the range $ [2, 2] $ , and split the array in subarrays $ (1, 3) $ and $ (4, 4) $ , in subarray $ (1, 3) $ there are $ 2 $ elements inside the range ( $ a_2 $ and $ a_3 $ ) and $ 1 $ element outside ( $ a_1 $ ), in subarray $ (4, 4) $ there is only $ 1 $ element ( $ a_4 $ ), and it is inside the range.

In the third test, it is possible to choose the range $ [5, 5] $ , and split the array in subarrays $ (1, 4) $ , $ (5, 7) $ and $ (8, 11) $ , in the subarray $ (1, 4) $ there are $ 3 $ elements inside the range and $ 1 $ element outside, in the subarray $ (5, 7) $ there are $ 2 $ elements inside and $ 1 $ element outside and in the subarray $ (8, 11) $ there are $ 3 $ elements inside and $ 1 $ element outside.

## 样例 #1

### 输入

```
3
2 1
1 2
4 2
1 2 2 2
11 3
5 5 5 1 5 5 1 5 5 5 1```

### 输出

```
1 2
1 2
2 2
1 3
4 4
5 5
1 1
2 2
3 11```

# AI分析结果

### 题目翻译
## 范围与划分

### 题目描述
给定一个包含 $n$ 个整数的数组 $a$，找出一个值的范围 $[x, y]$（$x \le y$），并将 $a$ 恰好分成 $k$ （$1 \le k \le n$）个子数组，使得：
- 每个子数组由 $a$ 的若干连续元素组成，即对于某些 $l$ 和 $r$（$1 \leq l \leq r \leq n$），子数组等于 $a_l, a_{l + 1}, \ldots, a_r$。
- $a$ 中的每个元素恰好属于一个子数组。
- 在每个子数组中，位于范围 $[x, y]$ 内（包含边界）的元素数量严格大于范围外的元素数量。当且仅当 $x \le a_i \le y$ 时，索引为 $i$ 的元素位于范围 $[x, y]$ 内。

输出任何使 $y - x$ 最小化的解决方案。

### 说明/提示
在第一个测试中，应该只有一个子数组，它必须等于整个数组。如果选择的范围是 $[1, 2]$，则该范围内有 $2$ 个元素，范围外有 $0$ 个元素；如果选择的范围是 $[1, 1]$，则范围内有 $1$ 个元素（$a_1$），范围外有 $1$ 个元素（$a_2$），这样的答案是无效的。

在第二个测试中，可以选择范围 $[2, 2]$，并将数组划分为子数组 $(1, 3)$ 和 $(4, 4)$。在子数组 $(1, 3)$ 中，范围内有 $2$ 个元素（$a_2$ 和 $a_3$），范围外有 $1$ 个元素（$a_1$）；在子数组 $(4, 4)$ 中，只有 $1$ 个元素（$a_4$），且它在范围内。

在第三个测试中，可以选择范围 $[5, 5]$，并将数组划分为子数组 $(1, 4)$、$(5, 7)$ 和 $(8, 11)$。在子数组 $(1, 4)$ 中，范围内有 $3$ 个元素，范围外有 $1$ 个元素；在子数组 $(5, 7)$ 中，范围内有 $2$ 个元素，范围外有 $1$ 个元素；在子数组 $(8, 11)$ 中，范围内有 $3$ 个元素，范围外有 $1$ 个元素。

### 样例 #1
#### 输入
```
3
2 1
1 2
4 2
1 2 2 2
11 3
5 5 5 1 5 5 1 5 5 5 1
```
#### 输出
```
1 2
1 2
2 2
1 3
4 4
5 5
1 1
2 2
3 11
```

### 算法分类
构造

### 综合分析与结论
这些题解的核心思路都是先确定满足条件的范围 $[x, y]$，使得在该范围内的元素个数比范围外的元素个数至少多 $k$ 个，然后再根据这个范围构造出 $k$ 个子数组。

- **思路对比**：大部分题解通过排序后使用滑动窗口或二分法来确定最小的 $y - x$，部分题解采用双指针法。在构造子数组时，多数题解采用贪心策略，即当在范围内的元素个数大于范围外的元素个数时就划分一个子数组。
- **算法要点**：关键在于利用数学推导得出在范围内的元素个数至少为 $\left\lceil \frac{n + k}{2} \right\rceil$，以此来确定范围 $[x, y]$。同时，通过将范围内的元素标记为 $1$，范围外的元素标记为 $-1$，利用前缀和来判断子数组是否满足条件。
- **解决难点**：难点在于证明满足在范围内的元素个数比范围外的元素个数至少多 $k$ 个这个条件时，一定存在合法的划分方案。多数题解通过前缀和的性质，即前缀和序列的变化是连续的，只要 $sum_n \ge k$ 就一定能找到 $k$ 个上升的前缀和值，从而构造出 $k$ 个子数组。

### 所选题解
- **Morgen_Kornblume（5星）**
    - **关键亮点**：思路清晰，先推导性质，再给出具体做法，代码实现简洁明了。
    - **个人心得**：赛时把问题想复杂没有搞出来，提醒自己对于复杂问题要寻找背后的规律和性质。
- **XL4453（4星）**
    - **关键亮点**：详细推导了在范围内的元素个数的下限，对构造方案的可行性进行了证明，代码实现规范。
- **DarkMoon_Dragon（4星）**
    - **关键亮点**：对前缀和的性质分析透彻，通过数学公式推导得出满足条件的范围，代码实现有详细的注释。

### 重点代码
#### Morgen_Kornblume 的代码
```cpp
#include<bits/stdc++.h>
using namespace std;

int T;
int n,k;
const int maxn=200010;
int a[maxn];
int at[maxn];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);cout.tie(nullptr);
    
    cin>>T;
    
    while(T--){
        
        cin>>n>>k;
        
        for(int i=1;i<=n;i++){
            cin>>a[i];
            at[i]=a[i];
        }
        
        sort(a+1,a+1+n);
        
        int ans=0x7fffffff;
        int inc=n-(n-k)/2;
        int rx,ry;
        for(int i=1;i<=n&&i+inc-1<=n;i++){
            if(a[i+inc-1]-a[i]<ans){
                ans=a[i+inc-1]-a[i];
                rx=a[i],ry=a[i+inc-1];
            }
        }
        cout<<rx<<" "<<ry<<endl;
        int tot=0;
        int st=1;
        int cnt=1;
        for(int i=1;i<=n;i++){
            if(rx<=at[i]&&at[i]<=ry)tot++;
            else tot--;
            if(tot==1){
                cout<<st<<" ";
                if(cnt==k){
                    cout<<n<<endl;
                    break;
                }
                else{
                    cout<<i<<endl;
                    tot=0;cnt++;st=i+1;
                }
            }
        }
    }
    
    return 0;
}
```
**核心实现思想**：先对数组排序，用滑动窗口找到最小的 $y - x$，确定范围 $[x, y]$。然后遍历原数组，统计范围内和范围外的元素个数差，当差为 $1$ 时划分一个子数组。

#### XL4453 的代码
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int T,n,k,a[200005],b[200005],ans,l,r;
int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&k);
        int len=(n+k+1)/2;
        for(int i=1;i<=n;i++)scanf("%d",&a[i]),b[i]=a[i];
        
        ans=2147483647;
        sort(a+1,a+n+1);
        for(int i=len;i<=n;i++){
            if(a[i]-a[i-len+1]<ans){
                ans=a[i]-a[i-len+1];
                l=a[i-len+1];
                r=a[i];
            }
        }
        
        printf("%d %d\n",l,r);
        int cnt1=0,cnt2=0,last=1,cnt=0;
        for(int i=1;i<=n;i++){
            if(b[i]<=r&&b[i]>=l)cnt1++;
            else cnt2++;
            if(cnt1>cnt2&&cnt<k-1){
                printf("%d %d\n",last,i);
                last=i+1;cnt1=cnt2=0;cnt++;
            }
        }
        printf("%d %d\n",last,n);
    }
    return 0;
}
```
**核心实现思想**：计算出在范围内的元素个数至少为 $(n + k + 1) / 2$，排序后用滑动窗口找到最小的 $y - x$。然后遍历原数组，统计范围内和范围外的元素个数，当范围内元素个数大于范围外元素个数且划分的子数组个数小于 $k - 1$ 时，划分一个子数组。

#### DarkMoon_Dragon 的代码
```cpp
const int N = 2e5 + 56;
int sum[N], a[N], b[N];
int pos[N];
int main() {
    int T = read();
    while (T--) {
        int n = read(), k = read();
        int len = ceil(double(n + k) / 2);
        for (int i = 1; i <= n; ++i) {
            a[i] = b[i] = read();
            pos[i] = 0;
        }
        sort(b + 1, b + 1 + n);
        int minn = 1e9, x, y;
        for (int l = 1, r = l + len - 1; r <= n; l++, r = l + len - 1) {
            if (b[r] - b[l] < minn) {
                y = b[r];
                x = b[l];
                minn = b[r] - b[l];
            }
        }
        cout << x << ' ' << y << endl;
        for (int i = 1; i <= n; ++i) {
            sum[i] = sum[i - 1] + (x <= a[i] && a[i] <= y ? 1 : -1);
            if (sum[i] > 0 && !pos[sum[i]]) pos[sum[i]] = i;
        }
        pos[sum[n]] = n;
        int las = 1;
        for (int i = sum[n] - k + 1; i <= sum[n]; ++i) {
            cout << las << ' ' << pos[i] << endl;
            las = pos[i] + 1;
        }
    }
}
```
**核心实现思想**：计算出在范围内的元素个数至少为 $\lceil \frac{n + k}{2} \rceil$，排序后用滑动窗口找到最小的 $y - x$。然后计算前缀和，记录每个前缀和值第一次出现的位置，根据前缀和值构造出 $k$ 个子数组。

### 最优关键思路或技巧
- **数学推导**：通过数学推导得出在范围内的元素个数至少为 $\left\lceil \frac{n + k}{2} \right\rceil$，以此来确定范围 $[x, y]$。
- **前缀和的应用**：将范围内的元素标记为 $1$，范围外的元素标记为 $-1$，利用前缀和来判断子数组是否满足条件，同时利用前缀和的性质证明存在合法的划分方案。
- **贪心策略**：在构造子数组时，采用贪心策略，当在范围内的元素个数大于范围外的元素个数时就划分一个子数组。

### 拓展思路
同类型题或类似算法套路：
- 给定一个数组和一些条件，要求将数组划分为若干子数组，使得每个子数组满足特定条件。可以考虑使用类似的前缀和、贪心、构造等方法。
- 对于一些需要最小化某个值的问题，可以尝试使用二分法或滑动窗口来求解。

### 推荐题目
- [P1181 数列分段 Section I](https://www.luogu.com.cn/problem/P1181)
- [P2678 跳石头](https://www.luogu.com.cn/problem/P2678)
- [P1024 一元三次方程求解](https://www.luogu.com.cn/problem/P1024)

### 个人心得总结
- Morgen_Kornblume 提醒自己对于复杂问题要寻找背后的规律和性质，不要把问题想复杂。
- IvanZhang2009 感慨赛时没切出来，说明在比赛中要保持冷静，仔细分析问题。

---
处理用时：100.09秒