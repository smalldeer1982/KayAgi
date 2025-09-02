# 题目信息

# [ABC045D] すぬけ君の塗り絵

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc045/tasks/arc061_b

縦 $ H $ 行、横 $ W $ 列のマス目からなる盤があります。最初、どのマス目も白く塗られています。

すぬけ君が、このうち $ N $ マスを黒く塗りつぶしました。$ i $ 回目 ( $ 1\ \leq\ i\ \leq\ N $ ) に塗りつぶしたのは、 上から $ a_i $ 行目で左から $ b_i $ 列目のマスでした。

すぬけ君がマス目を塗りつぶした後の盤の状態について、以下のものの個数を計算してください。

- 各整数 $ j $ ( $ 0\ \leq\ j\ \leq\ 9 $ ) について、盤の中に完全に含まれるすべての $ 3 $ 行 $ 3 $ 列の連続するマス目のうち、黒いマスがちょうど $ j $ 個あるもの。

## 说明/提示

### 制約

- $ 3\ \leq\ H\ \leq\ 10^9 $
- $ 3\ \leq\ W\ \leq\ 10^9 $
- $ 0\ \leq\ N\ \leq\ min(10^5,H×W) $
- $ 1\ \leq\ a_i\ \leq\ H $ $ (1\ \leq\ i\ \leq\ N) $
- $ 1\ \leq\ b_i\ \leq\ W $ $ (1\ \leq\ i\ \leq\ N) $
- $ (a_i,\ b_i)\ \neq\ (a_j,\ b_j) $ $ (i\ \neq\ j) $

### Sample Explanation 1

!\[\](https://atcoder.jp/img/arc061/30326702be007759dce81231012a8353.png) この盤に含まれる $ 3×3 $ の正方形は全部で $ 6 $ 個ありますが、これらのうち $ 2 $ 個の内部には黒いマスが $ 3 $ 個、残りの $ 4 $ 個の内部には黒いマスが $ 4 $ 個含まれています。

## 样例 #1

### 输入

```
4 5 8

1 1

1 4

1 5

2 3

3 1

3 2

3 4

4 4```

### 输出

```
0

0

0

2

4

0

0

0

0

0```

## 样例 #2

### 输入

```
10 10 20

1 1

1 4

1 9

2 5

3 10

4 2

4 7

5 9

6 4

6 6

6 7

7 1

7 3

7 7

8 1

8 5

8 10

9 2

10 4

10 9```

### 输出

```
4

26

22

10

2

0

0

0

0

0```

## 样例 #3

### 输入

```
1000000000 1000000000 0```

### 输出

```
999999996000000004

0

0

0

0

0

0

0

0

0```

# AI分析结果

### 中文题目重写

#### 题目描述

有一个 $H$ 行 $W$ 列的矩形网格，初始时所有格子都是白色的。すぬけ君将其中 $N$ 个格子涂成了黑色。第 $i$ 次（$1 \leq i \leq N$）涂黑的格子是第 $a_i$ 行第 $b_i$ 列的格子。

在涂黑所有 $N$ 个格子后，需要计算以下内容：

- 对于每个整数 $j$（$0 \leq j \leq 9$），计算网格中完全包含的所有 $3 \times 3$ 的连续子网格中，恰好有 $j$ 个黑色格子的子网格数量。

#### 说明/提示

##### 约束条件

- $3 \leq H \leq 10^9$
- $3 \leq W \leq 10^9$
- $0 \leq N \leq \min(10^5, H \times W)$
- $1 \leq a_i \leq H$ （$1 \leq i \leq N$）
- $1 \leq b_i \leq W$ （$1 \leq i \leq N$）
- $(a_i, b_i) \neq (a_j, b_j)$ （$i \neq j$）

##### 样例解释

样例 1 的输入输出如下：

输入：
```
4 5 8
1 1
1 4
1 5
2 3
3 1
3 2
3 4
4 4
```

输出：
```
0
0
0
2
4
0
0
0
0
0
```

### 算法分类

**模拟**

### 题解分析与结论

本题的核心难点在于如何处理 $H$ 和 $W$ 的极大范围（$10^9$），而 $N$ 的范围相对较小（$10^5$）。直接开二维数组模拟会超出内存限制，因此需要采用更高效的数据结构和算法。

大多数题解都采用了**贡献法**，即每个黑色格子只对其周围的 $3 \times 3$ 子网格产生影响。通过使用 `map` 或 `unordered_map` 来记录每个子网格的黑色格子数量，从而避免了直接模拟整个网格。

### 精选题解

#### 题解1：作者：Withers (赞：7)

**星级：5星**

**关键亮点：**
- 使用 `map` 记录每个 $3 \times 3$ 子网格的黑色格子数量。
- 初始化时计算所有可能的 $3 \times 3$ 子网格数量。
- 每次涂黑一个格子时，更新其影响的 $9$ 个子网格的黑色格子数量。

**代码实现：**
```cpp
#include<bits/stdc++.h>
using namespace std;
long long ans[10];
typedef pair<int,int> pii;
map<pii,int> mp;
int main() {
    long long h,w;
    int n;
    cin>>h>>w>>n;
    ans[0]=(h-2)*(w-2);
    for(int i=1;i<=n;i++) {
        int a,b;
        scanf("%d%d",&a,&b);
        for(int j=-1;j<=1;j++) {
            for(int k=-1;k<=1;k++) {
                int x=a+j,y=b+k;
                if(x>1&&x<h&&y>1&&y<w) {
                    int now=++mp[{x,y}];
                    ans[now]++, ans[now-1]--;
                }
            }
        }
    }
    for(int i=0;i<10;i++) cout<<ans[i]<<endl;
}
```

#### 题解2：作者：KarmaticEnding (赞：2)

**星级：4星**

**关键亮点：**
- 使用 `unordered_map` 记录每个 $3 \times 3$ 子网格的黑色格子数量。
- 自定义哈希函数来处理 `pair` 类型的键。
- 通过遍历 `unordered_map` 统计每个 $j$ 的答案。

**代码实现：**
```cpp
#include<cstdio>
#include<unordered_map>
using namespace std;
unordered_map<long long,int> cnt;
int dx[9]={-1,-1,-1,0,0,0,1,1,1};
int dy[9]={-1,0,1,-1,0,1,-1,0,1};
int n;
int H,W;
long long ans[10];
inline long long hsh(int x,int y) {
    return (long long)(x)*1000000007ll+(long long)(y);
}
int main() {
    scanf("%d%d%d",&H,&W,&n);
    ans[0]=(long long)(H-2)*(W-2);
    for(int r=1,x,y;r<=n;++r) {
        scanf("%d%d",&x,&y);
        for(int i=0;i<=8;++i) {
            if(x+dx[i]>1&&y+dy[i]>1&&x+dx[i]<=H-1&&y+dy[i]<=W-1) {
                ++cnt[hsh(x+dx[i],y+dy[i])];
            }
        }
    }
    for(auto iter=cnt.begin();iter!=cnt.end();++iter) {
        ++ans[iter->second];
    }
    ans[0]=(long long)(H-2)*(long long)(W-2);
    for(int i=1;i<=9;++i) {
        ans[0]-=ans[i];
    }
    for(int i=0;i<=9;++i) {
        printf("%lld\n",ans[i]);
    }
    return 0;
}
```

#### 题解3：作者：Acc_Robin (赞：3)

**星级：4星**

**关键亮点：**
- 使用 `map` 记录每个 $3 \times 3$ 子网格的黑色格子数量。
- 通过遍历每个黑色格子的影响范围，更新答案数组。
- 代码简洁，易于理解。

**代码实现：**
```cpp
#include<bits/stdc++.h>
using namespace std;
namespace Acc {
    int dx[9]={-1,-1,-1,0,0,0,1,1,1};
    int dy[9]={1,0,-1,1,0,-1,1,0,-1};
    int n,w,h,x,y,xx,yy,z,i,j;
    long long r[10];
    map<pair<int,int>,int>mp;
    void work() {
        cin>>h>>w>>n,r[0]=(h-2)*1ll*(w-2);
        for(i=1;i<=n;++i) {
            cin>>x>>y;
            for(j=0;j<9;++j) if(1<(xx=x+dx[j])&&xx<h&&1<(yy=y+dy[j])&&yy<w) {
                if(!mp.count({xx,yy})) mp[{xx,yy}]=z=1;
                else z=++mp[{xx,yy}];
                r[z]++,r[z-1]--;
            }
        }
        for(int i=0;i<10;++i) cout<<r[i]<<'\n';
    }
}
int main() {
    return Acc::work(),0;
}
```

### 最优关键思路与技巧

1. **贡献法**：每个黑色格子只对其周围的 $3 \times 3$ 子网格产生影响，避免了直接模拟整个网格。
2. **高效数据结构**：使用 `map` 或 `unordered_map` 来记录每个子网格的黑色格子数量，处理大规模数据。
3. **边界处理**：在更新子网格时，确保子网格的中心在合法范围内。

### 可拓展之处

- 类似的问题可以扩展到更大的子网格（如 $5 \times 5$ 或 $7 \times 7$），但需要注意计算复杂度和内存使用。
- 可以使用更高效的数据结构（如哈希表）来进一步优化性能。

### 推荐题目

1. [P3372 【模板】线段树 1](https://www.luogu.com.cn/problem/P3372)
2. [P3383 【模板】线性筛素数](https://www.luogu.com.cn/problem/P3383)
3. [P3384 【模板】树链剖分](https://www.luogu.com.cn/problem/P3384)

---
处理用时：53.99秒