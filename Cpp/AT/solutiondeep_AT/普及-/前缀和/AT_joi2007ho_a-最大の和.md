# 题目信息

# 最大の和

## 题目描述

[problemUrl]: https://atcoder.jp/contests/joi2007ho/tasks/joi2007ho_a



## 样例 #1

### 输入

```
5 3
2
5
-4
10
3```

### 输出

```
11```

# AI分析结果

### 题目内容重写
#### 最大の和

**题目描述**

给定一个长度为 $n$ 的整数序列 $a_1, a_2, \dots, a_n$，以及一个整数 $k$，要求找到一个长度为 $k$ 的连续子序列，使得该子序列的和最大。

**输入格式**

第一行包含两个整数 $n$ 和 $k$，分别表示序列的长度和子序列的长度。

第二行包含 $n$ 个整数，表示序列 $a_1, a_2, \dots, a_n$。

**输出格式**

输出一个整数，表示最大的子序列和。

**样例输入**

```
5 3
2
5
-4
10
3
```

**样例输出**

```
11
```

---

### 题解分析与结论

#### 题解整理与对比
1. **前缀和法**：大多数题解采用了前缀和的方法，通过预处理前缀和数组，可以在 $O(1)$ 时间内计算任意区间的和，时间复杂度为 $O(n)$。
2. **滑动窗口法**：部分题解使用了滑动窗口的思想，通过维护一个窗口的和，每次移动窗口时只需减去窗口最左端的元素并加上窗口最右端的元素，时间复杂度同样为 $O(n)$。
3. **线段树/树状数组**：少数题解使用了线段树或树状数组来求解区间和，虽然时间复杂度为 $O(n \log n)$，但代码复杂度较高，适用于需要动态更新区间和的场景。

#### 最优思路总结
- **前缀和法**是最简洁且高效的解决方案，适用于静态区间和查询问题。
- **滑动窗口法**在空间复杂度上更优，适合对空间要求较高的场景。

#### 拓展与举一反三
- 类似问题可以扩展到二维数组中的子矩阵和问题，使用二维前缀和或二维滑动窗口。
- 动态区间和问题可以使用线段树或树状数组来解决。

#### 推荐题目
1. [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)
2. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)
3. [P3374 【模板】树状数组 1](https://www.luogu.com.cn/problem/P3374)

---

### 高星题解推荐

#### 题解1：前缀和法
**作者：zhangyuhan**  
**星级：5星**  
**关键亮点**：思路清晰，代码简洁，时间复杂度低。  
**核心代码**：
```cpp
#include <iostream>
using namespace std;

int sum[100010],n,a[100010],k,ans;

int main(){
    cin>>n>>k;
    for(int i=1;i<=n;i++){    
        cin>>a[i];
        sum[i]=sum[i-1]+a[i];
    }
    for(int i=k;i<=n;i++)
        ans=max(ans,sum[i]-sum[i-k]);
    cout<<ans<<endl;
    return 0;
}
```

#### 题解2：滑动窗口法
**作者：Blue_wonders**  
**星级：4星**  
**关键亮点**：空间复杂度低，代码简洁。  
**核心代码**：
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
const int maxn = 100009;
int n,k,A[maxn];
int main(){
    int s=0,ans=0;
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;++i){
        scanf("%d",&A[i]);s+=A[i];
        if(i>k){
            s-=A[i-k];
            ans=max(ans,s);
        }
    }printf("%d\n",ans);
}
```

#### 题解3：树状数组
**作者：shame_djj**  
**星级：4星**  
**关键亮点**：介绍了树状数组的应用，适合动态区间和查询。  
**核心代码**：
```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#define int long long

using namespace std;

int ans;

struct Tree {
    int c[100010], n, k;
    void update (int i, int x) {
        for (; i <= n; i += i & -i)
            c[i] += x;
    }
    int s (int i) {
        int ans = 0;
        for (; i; i -= i & -i)
            ans += c[i];
        return ans;
    }
    int sum (int l, int r) {
        return s (r) - s (l - 1);
    }
} t;

void init () {
    t.n = read (), t.k = read ();
    for (register int i = 1; i <= t.n; i ++)
        t.update(i, read ()); 
}

void solve () {
    for (register int i = 1; i + t.k - 1 <= t.n; i ++)
        ans = max (ans, t.sum(i, i + t.k - 1));
}

void print () {
    printf ("%lld\n", ans);
}

signed main () {
    init ();
    solve ();
    print ();
    return 0;
}
```

---

### 个人心得摘录
- **zhangyuhan**：前缀和法简单高效，适合静态区间和查询问题。
- **Blue_wonders**：滑动窗口法在空间复杂度上更优，适合对空间要求较高的场景。
- **shame_djj**：树状数组适合动态区间和查询，但代码复杂度较高。

---
处理用时：44.00秒