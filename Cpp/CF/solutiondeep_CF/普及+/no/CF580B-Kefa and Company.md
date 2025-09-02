# 题目信息

# Kefa and Company

## 题目描述

Kefa 想要去餐馆庆祝一下，他有 $n$ 个朋友，每个朋友有一定的友谊值和工资。没人想觉得自己穷，所以 Kefa 邀请的朋友中两两工资差小于 $d$。现在给出朋友的信息，请求出最大友谊值是多少。

## 样例 #1

### 输入

```
4 5
75 5
0 100
150 20
75 1
```

### 输出

```
100
```

## 样例 #2

### 输入

```
5 100
0 7
11 32
99 10
46 8
87 54
```

### 输出

```
111
```

# AI分析结果

### 题目内容
# Kefa和伙伴们

## 题目描述
Kefa想要去餐馆庆祝一下，他有 $n$ 个朋友，每个朋友有一定的友谊值和工资。没人想觉得自己穷，所以Kefa邀请的朋友中两两工资差小于 $d$。现在给出朋友的信息，请求出最大友谊值是多少。

## 样例 #1
### 输入
```
4 5
75 5
0 100
150 20
75 1
```
### 输出
```
100
```

## 样例 #2
### 输入
```
5 100
0 7
11 32
99 10
46 8
87 54
```
### 输出
```
111
```

### 算法分类
贪心（结合前缀和与排序）

### 综合分析与结论
这些题解主要围绕如何高效地满足“两两工资差小于 $d$”的条件并求出最大友谊值。多数题解采用排序和前缀和的思路，其中又分为尺取法（双指针）和二分查找两种主要实现方式。尺取法通过移动左右指针，在线性时间 $O(n)$ 内找到满足条件的区间并更新最大友谊值；二分查找则是枚举左端点后，通过二分查找右端点，时间复杂度为 $O(n \log n)$。尺取法在时间复杂度上更优，代码实现也相对简洁直观。

### 所选的题解
- **作者：hank0402 (5星)**
  - **关键亮点**：思路清晰，详细阐述了尺取法的原理和优化点，对前缀和与排序的使用说明准确，代码简洁规范。
  - **个人心得**：强调必须先排序再做前缀和，否则数组下标不对应会WA。
  - **核心代码片段**：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long 
const int maxn = 1e5 + 10;
int n, d, ans, sum[maxn];
struct node {
    int x, y; 
}a[maxn]; 
bool cmp(node _x, node _y) {
    return _x.x < _y.x;
} 
signed main(){
    cin >> n >> d;
    for(int i = 1; i <= n; ++i) cin >> a[i].x >> a[i].y;
    sort(a + 1, a + n + 1, cmp);
    for(int i = 1; i <= n; ++i) sum[i] = sum[i - 1] + a[i].y; 
    int r = 1;
    for(int l = 1; l <= n; ++l) {
        while(r <= n && a[r].x - a[l].x < d) { 
            ans = max(ans, sum[r] - sum[l - 1]);
            r ++; 
        }
    }
    cout << ans;
    return 0;
}
```
  - **核心实现思想**：先对朋友按工资排序，再计算友谊值前缀和。通过尺取法，枚举左端点 $l$，当右端点 $r$ 与 $l$ 的工资差小于 $d$ 时，更新最大友谊值并右移 $r$；否则结束内层循环，移动左端点 $l$。

- **作者：信息向阳花木 (4星)**
  - **关键亮点**：以通俗易懂的语言解释滑动窗口（尺取法）的原理和正确性，代码简洁易懂。
  - **核心代码片段**：
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int n,d,l=1,r=1;
long long s[100010],ans;
struct node{
    int m,s;
}a[100010];
bool cmp(node x,node y){ 
    return x.m<y.m;
}
int main(){
    cin>>n>>d;
    for(int i=1;i<=n;i++){
        cin>>a[i].m>>a[i].s;
    }
    sort(a+1,a+n+1,cmp);
    for(int i=1;i<=n;i++){
        s[i]=s[i-1]+a[i].s;
    }
    while(l<=n&&r<=n){
        if(a[r].m-a[l].m<d){ans=max(ans,s[r]-s[l-1]);r++;}
        else l++;
    }
    cout<<ans;
    return 0;
}
```
  - **核心实现思想**：同样先排序和计算前缀和，通过尺取法，在 $l$ 和 $r$ 都不超过 $n$ 的情况下，根据工资差条件移动指针并更新最大友谊值。

- **作者：Dr_Gilbert (4星)**
  - **关键亮点**：清晰阐述双指针（尺取法）思路和时间复杂度分析，代码简洁规范，还提及二分法也可解题。
  - **核心代码片段**：
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
struct node{
    int m,f;
    bool operator <(const node& a) const{
        return m<a.m;
    }
}fri[N];
int s[N];
signed main(){
    int n,d;cin>>n>>d;
    for (int i=1;i<=n;i++){
        cin>>fri[i].m>>fri[i].f;
    }
    sort(fri+1,fri+1+n);
    fri[n+1].m=0x7f7f7f7f;
    int ans=0;
    for (int i=1;i<=n;i++) s[i]=s[i-1]+fri[i].f;
    for (int l=1,r=1;l<=n;l++){
        while (fri[r].m-fri[l].m<d) r++;
        r--;
        ans=max(ans,s[r]-s[l-1]);
    }
    cout<<ans;
    return 0;
}
```
  - **核心实现思想**：先对朋友按工资排序并计算友谊值前缀和，利用尺取法，枚举左端点 $l$，找到满足工资差条件的最靠右的右端点 $r$，更新最大友谊值。

### 最优关键思路或技巧
- **排序**：对朋友按工资排序，使得后续处理工资差条件更方便，能将问题转化为对有序数组的区间操作。
- **前缀和**：预先计算友谊值的前缀和，避免每次计算区间友谊值总和时的重复计算，大大提高效率。
- **尺取法**：通过同向移动左右指针，在线性时间内遍历所有可能的区间，高效地找到满足工资差条件的最大友谊值区间。

### 可拓展之处
同类型题常考察在满足一定区间条件下求最值的问题，类似算法套路是先对数据进行排序，再结合前缀和优化区间计算，最后利用尺取法或二分查找来遍历区间。

### 推荐洛谷题目
- [P1638 逛画展](https://www.luogu.com.cn/problem/P1638)：尺取法经典题目，求满足一定条件的最短区间。
- [P1147 连续自然数和](https://www.luogu.com.cn/problem/P1147)：同样可使用尺取法，寻找满足和条件的连续自然数区间。
- [P3957 [NOIP2017 普及组] 跳房子](https://www.luogu.com.cn/problem/P3957)：结合二分查找和前缀和，在满足一定距离条件下求最大得分。 

---
处理用时：64.59秒