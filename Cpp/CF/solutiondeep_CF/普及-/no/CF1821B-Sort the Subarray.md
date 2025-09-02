# 题目信息

# Sort the Subarray

## 题目描述

Monocarp had an array $ a $ consisting of $ n $ integers. He has decided to choose two integers $ l $ and $ r $ such that $ 1 \le l \le r \le n $ , and then sort the subarray $ a[l..r] $ (the subarray $ a[l..r] $ is the part of the array $ a $ containing the elements $ a_l, a_{l+1}, a_{l+2}, \dots, a_{r-1}, a_r $ ) in non-descending order. After sorting the subarray, Monocarp has obtained a new array, which we denote as $ a' $ .

For example, if $ a = [6, 7, 3, 4, 4, 6, 5] $ , and Monocarp has chosen $ l = 2, r = 5 $ , then $ a' = [6, 3, 4, 4, 7, 6, 5] $ .

You are given the arrays $ a $ and $ a' $ . Find the integers $ l $ and $ r $ that Monocarp could have chosen. If there are multiple pairs of values $ (l, r) $ , find the one which corresponds to the longest subarray.

## 样例 #1

### 输入

```
3
7
6 7 3 4 4 6 5
6 3 4 4 7 6 5
3
1 2 1
1 1 2
3
2 2 1
2 1 2```

### 输出

```
2 5
1 3
2 3```

# AI分析结果

### 题目翻译
# 对子数组进行排序

## 题目描述
Monocarp 有一个由 $n$ 个整数组成的数组 $a$。他决定选择两个整数 $l$ 和 $r$，使得 $1 \le l \le r \le n$，然后将子数组 $a[l..r]$（子数组 $a[l..r]$ 是数组 $a$ 中包含元素 $a_l, a_{l + 1}, a_{l + 2}, \dots, a_{r - 1}, a_r$ 的部分）按非降序排序。排序子数组后，Monocarp 得到了一个新数组，我们将其记为 $a'$。

例如，如果 $a = [6, 7, 3, 4, 4, 6, 5]$，并且 Monocarp 选择了 $l = 2, r = 5$，那么 $a' = [6, 3, 4, 4, 7, 6, 5]$。

给定数组 $a$ 和 $a'$。请找出 Monocarp 可能选择的整数 $l$ 和 $r$。如果有多个 $(l, r)$ 值对，请找出对应最长子数组的那一对。

## 样例 #1

### 输入
```
3
7
6 7 3 4 4 6 5
6 3 4 4 7 6 5
3
1 2 1
1 1 2
3
2 2 1
2 1 2
```

### 输出
```
2 5
1 3
2 3
```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路都是先找出原数组和排序后数组中元素不同的最左和最右位置，确定必须排序的区间，然后根据非降序的性质向左右扩展该区间，以得到最长的排序区间。
- **思路对比**：大部分题解思路一致，先找不同元素确定初始区间，再扩展；yuanruiqi 的题解在确定右边界时记录最大值及其数量，逻辑稍复杂。
- **算法要点**：确定初始区间是通过遍历数组找到元素不同的位置；扩展区间是根据非降序条件（左边界前元素小于等于左边界元素，右边界后元素大于等于右边界元素）进行。
- **解决难点**：主要难点在于准确找到必须排序的区间，并正确地向左右扩展该区间，同时要注意边界条件的处理。

### 题解评分与选择
- **Czy_Lemon（5星）**：思路清晰，代码简洁易懂，详细解释了题意和解题思路，关键步骤有明确说明。
- **Loser_Syx（4星）**：思路正确，代码规范，给出了 Hack 数据，有助于理解边界情况。
- **cff_0102（4星）**：思路简洁明了，代码实现简单，有 AC 记录。

### 关键思路与技巧
- 先通过比较两个数组元素找出必须排序的区间，这是问题的关键切入点。
- 利用非降序的性质向左右扩展区间，以得到最长的排序区间，体现了贪心的思想。

### 拓展思路
同类型题目可能会有不同的排序规则或条件限制，例如降序排序、部分元素固定等。解题思路仍然是先确定必须处理的区间，再根据具体规则进行扩展或调整。

### 洛谷相似题目推荐
- P1177 【模板】快速排序
- P1059 [NOIP2006 普及组] 明明的随机数
- P1093 [NOIP2007 普及组] 奖学金

### 个人心得摘录与总结
Loser_Syx 给出 Hack 数据 `1 3 3 1 3 3`，指出自己一开始错误输出 `1 2`，提醒要注意边界情况，在扩展区间时要确保左右边界的判断条件正确。

### 重点代码
#### Czy_Lemon 的题解
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2*1e5+10;
int t,n,a[N],b[N];
int main(){
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        for(int i=1;i<=n;i++) scanf("%d",&a[i]);
        for(int i=1;i<=n;i++) scanf("%d",&b[i]);
        int l,r;
        for(int i=1;i<=n;i++)
            if(a[i]!=b[i]){
                l=i;
                break;
            }
        for(int i=n;i>=1;i--)
            if(a[i]!=b[i]){
                r=i;
                break;
            }
        for(int i=l;i>=1;i--){
            if(b[i]>b[i+1]) break;
            l=i;
        }
        for(int i=r;i<=n;i++){
            if(b[i-1]>b[i]) break;
            r=i;
        }
        printf("%d %d\n",l,r);
    }
    return 0;
}
```
核心实现思想：先找到两个数组元素不同的最左和最右位置，确定初始区间，然后向左和向右扩展该区间，直到不满足非降序条件为止。

#### Loser_Syx 的题解
```cpp
namespace SyxQwQ{
    inline int qwq(){
        return 0;
    }
    int a[114514<<1], b[114514<<1];
    inline int main(){
        int T = read();
        while(T--){
            int n = read();
            f(i, 1, n, 1) a[i] = read();
            f(i, 1, n, 1) b[i] = read();
            int Left = 0, Right = 0;
            f(i, 1, n, 1){
                if(a[i] != b[i]){
                    if(Left == 0) Left = i;
                    Right = i;
                }
            }
            while(Left > 1 && b[Left] >= b[Left-1]) Left--;
            while(Right < n && b[Right] <= b[Right+1]) Right++;
            write(Left, ' ');
            write(Right, '\n');
        }
        return qwq();
    }
}
```
核心实现思想：同样先确定必须排序的区间，然后根据非降序条件向左右扩展区间。

#### cff_0102 的题解
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[200010];
int b[200010];
int main(){
    ios::sync_with_stdio(0);
    int t;cin>>t;
    while(t--){
        int n;cin>>n;
        for(int i=1;i<=n;i++){
            cin >> a[i];
        }for(int i=1;i<=n;i++){
            cin >> b[i];
        }
        int l,r;
        for(int i=1;i<=n;i++){
            if(a[i]!=b[i]){
                l=i;
                break;
            }
        }
        for(int i=n;i>=1;i--){
            if(a[i]!=b[i]){
                r=i;
                break;
            }
        }
        while(b[l-1]<=b[l]&&l>1){
            l--;
        }
        while(b[r+1]>=b[r]&&r<n){
            r++;
        }
        cout<<l<<" "<<r<<endl;
    }
    return 0;
}
```
核心实现思想：先找出元素不同的最左和最右位置，再向左右扩展区间，满足非降序条件则继续扩展。

---
处理用时：45.43秒