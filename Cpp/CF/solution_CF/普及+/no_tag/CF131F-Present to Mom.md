# Present to Mom

## 题目描述

求一个 $n\times m$ 的字符矩阵内，有多少个不同的矩形包含不少于 $k$ 个下述图形：

```
 1
111
 1
```

注意，这些图形可以相互重叠，但是不能完全重叠。

## 样例 #1

### 输入

```
4 6 2
111000
111100
011011
000111
```

### 输出

```
6
```

## 样例 #2

### 输入

```
5 5 4
11111
11111
11111
11111
11111
```

### 输出

```
9
```

# 题解

## 作者：__2009 (赞：3)

### Topic
第一行三个正整数，$n,m,k$。  
接下来 $n$ 行，每行 $m$ 个字符描述矩阵。这些字符只可能是 $0$ 或 $1$ 。  
求一个 $n \times m$ 的**字符矩阵内**，有多少个不同的矩形**包含不少于 $k$ 个**下述图形：

```
 1
111
 1
```

### Solution
首先考虑暴力：  
枚举长、宽、左上角顶点，然后对于每个矩阵进行遍历，统计目标图形的数量
时间复杂度大概是 $O(m^2n^4)$ ~~不想算~~  
明显过不了。

下面考虑使用前缀和优化使 $s(i,j)$ 的值为一当且仅当以它为中心是一个目标图形。  
此时的时间复杂度大概是 $O(m^2n^2)$，显然还是很悬的  。

接下来，我们继续考虑优化：  
很容易发现，当以 $(i,j)$ 为顶点，长 $a$ ，宽 $b$ 时，若四元组 $(i,j,a,b)$ 满足条件，则四元组 $(i,j,a,k) (b \le k \le n)$ 也一定满足条件。

### Code
```cpp
#include<iostream>
using namespace std;
int const N=505;
int n,m,k,s[N][N];
long long ans;
char a[N][N];
int sum(int ax,int ay,int bx,int by){
    return s[bx][by]-s[ax-1][by]-s[bx][ay-1]+s[ax-1][ay-1];
}
int main(){
    cin>>n>>m>>k;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            cin>>a[i][j];
    for(int i=2;i<n;i++){
        for(int j=2;j<m;j++){
            s[i][j]=(a[i][j]&1&&a[i-1][j]&1&&a[i][j-1]&1&&a[i+1][j]&1&&a[i][j+1]&1)+s[i-1][j]+s[i][j-1]-s[i-1][j-1];//前缀和
        }
    }
    for(int l=2;l<n;l++){//l -> 长
        for(int r=l;r<n;r++){//r -> 宽
            for(int i=2,j=2;i<m;i++){//i,j -> 顶点
                 while(j<m&&sum(l,i,r,j)<k)j++;
                    if(j==m)break;
                    ans+=m-j;
                }
        }
    }
    cout<<ans<<"\n";
}
```


---

## 作者：Zbcxcj (赞：1)

介绍一下双指针做法，复杂度 $O(n^3)$。

### 提示
- 首先这一题预处理所有星的位置是很显然的，接下来要做的就是找到一个子矩阵，使其包含的星的数量 $\ge k$，尤其注意，矩阵边缘的星是不计数的！
- 注意，如果一个矩阵已经满足条件了，那么它的所有父矩阵也都是满足条件的，所以我们可以固定矩阵的三条边，计算最后一条边有多少种取值。

### 实现
我们可以预处理每一行的前缀和，先确定矩阵的左右两条边，然后上下两条边双指针模拟即可。

最终复杂度是 $O(m^2n)$。

```cpp
#include <bits/stdc++.h>

using namespace std;
int dir[] = {1, 0, -1, 0, 1};
typedef long long ll;

void solve() {
    int n, m, k; cin >> n >> m >> k;
    vector<string> g(n);
    for (int i = 0; i < n; ++i) cin >> g[i];

    if (n < 3 || m < 3) {
        cout << "0\n";
        return;
    }

    auto check = [&](int i, int j) {
        if (g[i][j] == '0') return 0;
        for (int k = 0; k < 4; ++k) {
            int x = i + dir[k];
            int y = j + dir[k + 1];
            if (g[x][y] == '0') return 0;
        }
        return 1;
    };

    // 每一行的前缀和
    vector<vector<int>> c(n, vector<int>(m));
    for (int i = 1; i < n - 1; ++i) {
        for (int j = 1; j < m - 1; ++j) {
            int x = check(i, j);
            c[i][j] = c[i][j - 1] + x;
        }
    }

    // 枚举左右边界
    ll ans = 0;
    for (int l = 0; l < m - 2; ++l) {
        for (int r = l + 2; r < m; ++r) {
            vector<int> a(n);
            for (int i = 0; i < n; ++i) a[i] = c[i][r - 1] - c[i][l];  // 注意边缘是不算在内的
            for (int i = 1; i < n; ++i) a[i] += a[i - 1];  // 为方便计算，上下边界依然做前缀和处理
            int i = 0, j = 1;
            while (true) {
                while (j < n && a[j - 1] - a[i] < k) ++j;
                if (j == n) break;
                ans += (n - j);  // j 及其下面的边都满足条件
                i += 1;
            }
        }
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    solve();
    return 0;
}

```

---

