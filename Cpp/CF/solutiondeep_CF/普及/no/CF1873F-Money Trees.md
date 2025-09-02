# 题目信息

# Money Trees

## 题目描述

Luca is in front of a row of $ n $ trees. The $ i $ -th tree has $ a_i $ fruit and height $ h_i $ .

He wants to choose a contiguous subarray of the array $ [h_l, h_{l+1}, \dots, h_r] $ such that for each $ i $ ( $ l \leq i < r $ ),  $ h_i $ is divisible $ ^{\dagger} $ by $ h_{i+1} $ . He will collect all the fruit from each of the trees in the subarray (that is, he will collect $ a_l + a_{l+1} + \dots + a_r $ fruits). However, if he collects more than $ k $ fruits in total, he will get caught.

What is the maximum length of a subarray Luca can choose so he doesn't get caught?

 $ ^{\dagger} $ $ x $ is divisible by $ y $ if the ratio $ \frac{x}{y} $ is an integer.

## 说明/提示

In the first test case, Luca can select the subarray with $ l=1 $ and $ r=3 $ .

In the second test case, Luca can select the subarray with $ l=3 $ and $ r=4 $ .

In the third test case, Luca can select the subarray with $ l=2 $ and $ r=2 $ .

## 样例 #1

### 输入

```
5
5 12
3 2 4 1 8
4 4 2 4 1
4 8
5 4 1 2
6 2 3 1
3 12
7 9 10
2 2 4
1 10
11
1
7 10
2 6 3 1 5 10 6
72 24 24 12 4 4 2```

### 输出

```
3
2
1
0
3```

# AI分析结果

### 题目内容重写

Luca 面前有一排 $n$ 棵树。第 $i$ 棵树有 $a_i$ 个果实，高度为 $h_i$。

他想要选择一个连续的子树数组 $[h_l, h_{l+1}, \dots, h_r]$，使得对于每个 $i$（$l \leq i < r$），$h_i$ 能被 $h_{i+1}$ 整除。他将从子树中的每棵树收集所有果实（即他将收集 $a_l + a_{l+1} + \dots + a_r$ 个果实）。然而，如果他总共收集的果实超过 $k$ 个，他就会被抓住。

Luca 可以选择的最长子数组长度是多少，以确保他不会被抓到？

### 算法分类
双指针、前缀和

### 题解分析与结论

1. **双指针与贪心思想**：大多数题解都采用了双指针的方法，通过维护一个滑动窗口来寻找满足条件的最长子数组。这种方法的核心在于通过贪心思想，尽可能地扩展右端点，同时通过调整左端点来确保子数组的和不超过 $k$。

2. **前缀和优化**：为了快速计算子数组的和，题解中普遍使用了前缀和数组。这使得在调整窗口大小时，能够快速判断当前子数组的和是否超过 $k$。

3. **分段处理**：部分题解提到，可以将数组分成若干段，每段内满足相邻元素之间的整除关系。然后在这些段内分别寻找满足条件的最长子数组。这种方法虽然增加了预处理步骤，但在某些情况下可以简化后续的双指针操作。

4. **二分查找**：少数题解采用了二分查找的方法，通过枚举可能的子数组长度，然后验证是否存在满足条件的子数组。这种方法虽然时间复杂度较高，但在某些情况下可能更容易理解和实现。

### 评分较高的题解

#### 题解1：作者：yszkddzyh (赞：13)
- **星级**：5星
- **关键亮点**：双指针与贪心思想的完美结合，代码简洁高效，使用了前缀和优化，思路清晰。
- **个人心得**：作者提到这是一道很好的双指针题目，建议先完成类似的题目（如 P1147）以熟悉双指针的使用。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;
int t, n, k, a[N], b[N], s[N];

int main(){
    scanf("%d", &t);
    while(t--){
        int ans = 0;
        scanf("%d %d", &n, &k);
        for(int i = 1; i <= n; i++)
            scanf("%d", a + i),
            s[i] = s[i - 1] + a[i];
        for(int i = 1; i <= n; i++)
            scanf("%d", b + i);
        for(int i = 1, l = 1, r; i <= n; i++){
            r = i;
            if(b[i - 1] % b[i]) l = r;
            while(s[r] - s[l - 1] > k) l++;
            ans = max(ans, r - l + 1);
        }
        printf("%d\n", ans);
    }
    return 0;
}
```

#### 题解2：作者：ArcherHavetoLearnWhk (赞：2)
- **星级**：4星
- **关键亮点**：双指针与前缀和的结合，代码简洁，思路清晰，适合初学者理解。

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,k,a[200005],h[200005],s[200005];
int main(){
    cin>>t;
    while(t--){
        cin>>n>>k;
        for(int i=1;i<=n;i++){
            cin>>a[i];
            s[i]=s[i-1]+a[i];
        }
        for(int i=1;i<=n;i++)cin>>h[i];
        int ma=0,l,r;
        l=r=1;
        while(r<=n){
            if(h[r-1]%h[r])l=r;
            while(s[r]-s[l-1]>k)l++;
            ma=max(ma,r-l+1);
            r++;
        }
        cout<<ma<<'\n';
    }
    return 0;
}
```

#### 题解3：作者：phigy (赞：0)
- **星级**：4星
- **关键亮点**：双指针与分段处理的结合，代码简洁，思路清晰，适合有一定基础的读者。

```cpp
#include <csignal>
#include <iostream>
#define int long long
using namespace std;
int T;
int n;
int a[2000005];
int h[2000005];
signed main()
{
    int i,j,k;
    cin>>T;
    while(T--)
    {
        cin>>n>>k;
        for(i=1;i<=n;i++) cin>>a[i];
        for(i=1;i<=n;i++) cin>>h[i];
        int res=0;
        int maxx=0;
        h[0]=h[1];
        for(j=1,i=1;i<=n;i++)
        {
            if(h[i-1]%h[i]!=0) j=i,res=0;
            res+=a[i];
            while(res>k)res-=a[j],j++;
            if(res<=k) maxx=max(maxx,i-j+1);
        }
        cout<<maxx<<endl;
    }
    return 0;
}
```

### 最优关键思路与技巧
- **双指针与贪心思想**：通过维护一个滑动窗口，尽可能地扩展右端点，同时通过调整左端点来确保子数组的和不超过 $k$。
- **前缀和优化**：使用前缀和数组快速计算子数组的和，提高效率。
- **分段处理**：将数组分成若干段，每段内满足相邻元素之间的整除关系，简化后续的双指针操作。

### 可拓展之处
- **类似题目**：可以尝试解决其他需要双指针和前缀和的题目，如最大子数组和、最小覆盖子串等。
- **算法优化**：可以进一步优化双指针的实现，减少不必要的计算，提高代码效率。

### 推荐题目
1. P1147 连续子数组的最大和
2. P2096 最小覆盖子串
3. P2303 最长无重复字符子串

---
处理用时：35.76秒