# 题目信息

# Black and White Stripe

## 题目描述

You have a stripe of checkered paper of length $ n $ . Each cell is either white or black.

What is the minimum number of cells that must be recolored from white to black in order to have a segment of $ k $ consecutive black cells on the stripe?

If the input data is such that a segment of $ k $ consecutive black cells already exists, then print 0.

## 说明/提示

In the first test case, $ s $ ="BBWBW" and $ k=3 $ . It is enough to recolor $ s_3 $ and get $ s $ ="BBBBW". This string contains a segment of length $ k=3 $ consisting of the letters 'B'.

In the second test case of the example $ s $ ="BBWBW" and $ k=5 $ . It is enough to recolor $ s_3 $ and $ s_5 $ and get $ s $ ="BBBBB". This string contains a segment of length $ k=5 $ consisting of the letters 'B'.

In the third test case of the example $ s $ ="BBWBW" and $ k=1 $ . The string $ s $ already contains a segment of length $ k=1 $ consisting of the letters 'B'.

## 样例 #1

### 输入

```
4
5 3
BBWBW
5 5
BBWBW
5 1
BBWBW
1 1
W```

### 输出

```
1
2
0
1```

# AI分析结果

### 题目内容
# 黑白条纹

## 题目描述
你有一张长度为 $n$ 的方格纸。每个格子要么是白色，要么是黑色。
为了在这张纸上得到一段长度为 $k$ 的连续黑色格子，最少需要将多少个白色格子重新涂成黑色？
如果输入数据中已经存在一段长度为 $k$ 的连续黑色格子，那么输出0。

## 说明/提示
在第一个测试用例中，$s$ ="BBWBW" 且 $k = 3$。只需重新涂 $s_3$ ，得到 $s$ ="BBBBW"。这个字符串包含一段长度为 $k = 3$ 的由 'B' 组成的子串。
在示例的第二个测试用例中，$s$ ="BBWBW" 且 $k = 5$。只需重新涂 $s_3$ 和 $s_5$ ，得到 $s$ ="BBBBB"。这个字符串包含一段长度为 $k = 5$ 的由 'B' 组成的子串。
在示例的第三个测试用例中，$s$ ="BBWBW" 且 $k = 1$。字符串 $s$ 已经包含一段长度为 $k = 1$ 的由 'B' 组成的子串。

## 样例 #1
### 输入
```
4
5 3
BBWBW
5 5
BBWBW
5 1
BBWBW
1 1
W
```
### 输出
```
1
2
0
1
```

### 算法分类
前缀和

### 综合分析与结论
这些题解主要围绕如何高效找出长度为 $k$ 的子串中最少的白色格子数展开。多数题解采用前缀和算法，通过预处理记录前 $i$ 个字符中黑色或白色格子的数量，然后枚举长度为 $k$ 的子串，利用前缀和快速计算子串内白色格子数，从而得出最少需修改的白色格子数。部分题解提到了类似滑动窗口的思想，本质也是通过动态维护子串信息来优化计算。解决难点在于如何选择合适的数据结构和算法，高效地统计和比较不同子串中的白色格子数量。

### 所选的题解
- **作者：柳下惠 (5星)**
    - **关键亮点**：思路清晰，简洁明了地阐述前缀和的运用。先将字符转化为01数组，计算前缀和，通过枚举子串左端点，利用前缀和得到区间内黑色格子数，进而求出最少需修改的白色格子数。
    - **重点代码**：
```cpp
t=read();
while(t--)
{
    int cnt=0,tmp=0;
    int n=read(),m=read();
    string s;cin>>s;
    for(int i=0;i<n;i++)
    if(s[i]=='B') a[++cnt]=1;
    else a[++cnt]=0;    
    for(int i=1;i<=n;i++) sum[i]=sum[i-1]+a[i];
    for(int i=1;i<=n-m+1;i++)
        tmp=max(tmp,sum[i+m-1]-sum[i-1]);
    printf("%d\n",m-tmp);
}
```
    - **核心实现思想**：先将字符串转为01数组，计算前缀和数组 `sum`，通过 `sum[i+m-1]-sum[i-1]` 得到长度为 `m` 的子串内黑色格子数，用 `m` 减去该值得到需修改的白色格子数，取所有子串中的最小值输出。
- **作者：_djc_ (4星)**
    - **关键亮点**：提到类似滑动窗口的思想，代码实现清晰，通过维护一个长度为 `m` 的滑动窗口，动态更新窗口内黑色格子数，找到最大值，进而得出最少需修改的白色格子数。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
#define maxn 200005 
using namespace std;
inline int read(){
    int x = 0, f = 1 ; char c = getchar() ;
    while( c < '0' || c > '9' ) { if( c == '-' ) f = -1 ; c = getchar() ; } 
    while( c >= '0' && c <= '9' ) { x = x * 10 + c - '0' ; c = getchar() ; } 
    return x * f ;
} 
int n, m;
int T;
int a[maxn];
int win[maxn];
int main() {
    T = read();
    while(T--){
        memset(a, 0, sizeof(a)), memset(win, 0, sizeof(win));
        n = read(), m = read();
        for(int i = 1; i <= n; i++){
            char c; cin >> c;
            if(c == 'B') a[i] = 1; 
            else a[i] = 0;
        }
        for(int i = 1; i <= m; i++){
            win[m] += a[i];
        } 
        int ma = win[m];
        for(int i = m + 1; i <= n; i++){
            win[i] = win[i-1] - a[i-m] + a[i];
            ma = max(win[i], ma);
        }
        cout << max(0, m - ma) << endl; 
    }
}
```
    - **核心实现思想**：先将字符串转为01数组，初始化长度为 `m` 的窗口内黑色格子数，然后通过 `win[i] = win[i-1] - a[i-m] + a[i]` 动态更新窗口内黑色格子数，找到最大值 `ma`，用 `m - ma` 得到需修改的白色格子数。
- **作者：litachloveyou (4星)**
    - **关键亮点**：利用前缀和思想，代码简洁，逻辑清晰，通过前缀和记录每个长度为 `k` 的区间的黑色格子数量，枚举区间找到最小的需修改白色格子数。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
char s[2 * 100000 + 10];
void solve()
{
    int n, k;
    scanf("%d%d", &n, k);
    scanf("\n%s", s + 1);
    vector<int>a(n + 1);
    for (int i = 1; i <= n; i++)
    {
        if (s[i] == 'B')a[i] = 1;
        a[i] = a[i - 1] + a[i];
    }
    int ans = 1e9 + 10;
    for (int i = k, j = 0; i <= n; i++, j++)
    {
        ans = min(ans, k - (a[i] - a[j]));
    }
    printf("%d\n", ans);
}
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)solve();
    return 0;
}
```
    - **核心实现思想**：将字符串转为01数组并计算前缀和，通过 `k - (a[i] - a[j])` 计算长度为 `k` 的区间内白色格子数，枚举所有区间取最小值输出。

### 最优关键思路或技巧
使用前缀和数组来记录前 $i$ 个字符中黑色或白色格子的数量，这样在枚举长度为 $k$ 的子串时，能通过简单的数组运算（`sum[i+k-1] - sum[i-1]`）快速得到子串内黑色或白色格子的数量，从而高效地找出最少需要修改的白色格子数。

### 拓展
同类型题常围绕字符串子串统计问题，类似算法套路是利用前缀和、滑动窗口等优化对连续子区间的计算。例如给定字符串找特定字符组成的子串的最大/最小长度、满足条件的子串数量等。

### 推荐洛谷题目
- [P1387 最大正方形](https://www.luogu.com.cn/problem/P1387)：可通过前缀和优化计算矩阵子区域的和，进而找到最大正方形。
- [P3397 地毯](https://www.luogu.com.cn/problem/P3397)：需要利用二维前缀和解决矩形区域的统计问题。
- [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)：可利用前缀和思想优化暴力枚举，找到最大子段和。

### 个人心得摘录与总结
作者_djc_提到一开始认为是DP题，但发现状态设计不合理，看到题解区提示才想到用前缀和。总结出做题不能局限于固有思路，需灵活思考，多种算法尝试无果时，要从其他角度重新审视题目。 

---
处理用时：60.71秒