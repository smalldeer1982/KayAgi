# 题目信息

# Points and Minimum Distance

## 题目描述

You are given a sequence of integers $ a $ of length $ 2n $ . You have to split these $ 2n $ integers into $ n $ pairs; each pair will represent the coordinates of a point on a plane. Each number from the sequence $ a $ should become the $ x $ or $ y $ coordinate of exactly one point. Note that some points can be equal.

After the points are formed, you have to choose a path $ s $ that starts from one of these points, ends at one of these points, and visits all $ n $ points at least once.

The length of path $ s $ is the sum of distances between all adjacent points on the path. In this problem, the distance between two points $ (x_1, y_1) $ and $ (x_2, y_2) $ is defined as $ |x_1-x_2| + |y_1-y_2| $ .

Your task is to form $ n $ points and choose a path $ s $ in such a way that the length of path $ s $ is minimized.

## 说明/提示

In the first testcase, for instance, you can form points $ (10, 1) $ and $ (15, 5) $ and start the path $ s $ from the first point and end it at the second point. Then the length of the path will be $ |10 - 15| + |1 - 5| = 5 + 4 = 9 $ .

In the second testcase, you can form points $ (20, 20) $ , $ (10, 30) $ , and $ (10, 30) $ , and visit them in that exact order. Then the length of the path will be $ |20 - 10| + |20 - 30| + |10 - 10| + |30 - 30| = 10 + 10 + 0 + 0 = 20 $ .

## 样例 #1

### 输入

```
2
2
15 1 10 5
3
10 30 20 20 30 10```

### 输出

```
9
10 1
15 5
20
20 20
10 30
10 30```

# AI分析结果

### 题目内容（中文重写）
# 点与最小距离

## 题目描述
给定一个长度为 $2n$ 的整数序列 $a$。你需要将这 $2n$ 个整数分成 $n$ 对，每一对将表示平面上一个点的坐标。序列 $a$ 中的每个数都应恰好成为一个点的 $x$ 或 $y$ 坐标。注意，有些点可能相同。

在形成这些点之后，你需要选择一条路径 $s$，该路径从这些点中的一个开始，在这些点中的一个结束，并且至少访问所有 $n$ 个点一次。

路径 $s$ 的长度是路径上所有相邻点之间距离的总和。在这个问题中，两点 $(x_1, y_1)$ 和 $(x_2, y_2)$ 之间的距离定义为 $|x_1 - x_2| + |y_1 - y_2|$。

你的任务是形成 $n$ 个点并选择一条路径 $s$，使得路径 $s$ 的长度最小。

## 说明/提示
在第一个测试用例中，例如，你可以形成点 $(10, 1)$ 和 $(15, 5)$，并从第一个点开始路径 $s$，在第二个点结束。那么路径的长度将是 $|10 - 15| + |1 - 5| = 5 + 4 = 9$。

在第二个测试用例中，你可以形成点 $(20, 20)$、$(10, 30)$ 和 $(10, 30)$，并按这个确切的顺序访问它们。那么路径的长度将是 $|20 - 10| + |20 - 30| + |10 - 10| + |30 - 30| = 10 + 10 + 0 + 0 = 20$。

## 样例 #1

### 输入
```
2
2
15 1 10 5
3
10 30 20 20 30 10
```

### 输出
```
9
10 1
15 5
20
20 20
10 30
10 30
```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路都是通过贪心策略来解决问题。由于要使路径长度最小，而两点间距离为曼哈顿距离，所以将 $2n$ 个数排序后，前 $n$ 个数作为横坐标，后 $n$ 个数作为纵坐标，这样能保证相邻点间的距离和最小。

各题解的算法要点基本一致，都是先对数组排序，然后计算前 $n$ 个数和后 $n$ 个数相邻元素的差值之和作为最小路径长度，并输出对应的点坐标。

解决的难点在于理解为什么这样分配横纵坐标能得到最小路径长度，部分题解通过理论证明或举例说明来解释。

### 所选的题解
- **作者：DFbd（4星）**
  - 关键亮点：思路清晰，代码简洁易懂，直接阐述了排序分组求相邻元素差值和的核心思想。
- **作者：xinruian（4星）**
  - 关键亮点：对题意和解题思路的分析较为详细，从曼哈顿距离的性质出发，逐步推导出排序分组的结论。
- **作者：UncleSam_Died（4星）**
  - 关键亮点：不仅给出了解题思路，还对算法的正确性进行了详细证明，逻辑严谨。

### 重点代码
#### 作者：DFbd
```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n, a[205], ans;
int main() {
  cin >> t;
  while (t--) {
    cin >> n;
    for (int i = 1; i <= 2 * n; i++) {
      cin >> a[i];
    }
    sort(a + 1, a + 2 * n + 1);
    ans = 0;
    for (int i = 1; i < n; i++) {
      ans += a[i + 1] - a[i];
    }
    for (int i = n + 1; i < 2 * n; i++) {
      ans += a[i + 1] - a[i];
    }
    cout << ans << "\n";
    for (int i = 1; i <= n; i++) {
      cout << a[i] << " " << a[i + n] << "\n";
    }
  }
  return 0;
}
```
核心实现思想：先读取输入，对数组排序，然后分别计算前 $n$ 个数和后 $n$ 个数相邻元素的差值之和得到最小路径长度，最后输出路径长度和对应的点坐标。

#### 作者：xinruian
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 10;
int a[N];
void solve() {
    int n;
    cin >> n;
    for (int i = 1; i <= 2 * n; i ++)
        cin >> a[i];
    sort(a + 1, a + 1 + 2 * n);
    int tmp = n;
    int ans = 0;
    for (int i = 2; i <= n; i ++)
        ans += a[i] - a[i-1] + a[tmp + i] - a[tmp+i-1];
    cout << ans << endl;
    for (int i = 1; i <= n; i ++)
        cout << a[i] << ' ' << a[tmp + i] << endl;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t --)
        solve();
    return 0;
}
```
核心实现思想：在 `solve` 函数中处理每个测试用例，排序数组后计算相邻元素差值和，输出结果。

#### 作者：UncleSam_Died
```cpp
#include<stdio.h>
#include<math.h>
#include<algorithm>
#define N 205
int n,a[N];
int x[N],y[N];
inline void work(){
    scanf("%d",&n);
    for(register int i=1;i<=n<<1;++i)
        scanf("%d",&a[i]);
    std::sort(a+1,a+2*n+1);int ans=0;
    for(register int i=1;i<=n;++i)
        x[i]=a[i],y[i]=a[i+n];
    for(register int i=1;i<n;++i)
        ans+=x[i+1]-x[i]+y[i+1]-y[i];
    printf("%d\n",ans);
    for(register int i=1;i<=n;++i)
        printf("%d %d\n",x[i],y[i]);
}
signed main(){
    int T;scanf("%d",&T);
    while(T--) work();
} 
```
核心实现思想：在 `work` 函数中处理每个测试用例，排序数组后将前 $n$ 个数存为 $x$ 坐标，后 $n$ 个数存为 $y$ 坐标，计算相邻元素差值和并输出结果。

### 最优关键思路或技巧
- **贪心策略**：通过排序将数组分成两部分，分别作为横纵坐标，使得相邻点间的曼哈顿距离和最小。
- **排序优化**：利用排序使数组有序，方便计算相邻元素的差值。

### 拓展思路
同类型题或类似算法套路：
- 其他涉及坐标和距离计算的贪心问题，如在平面上安排点的位置以满足某种距离相关的最优条件。
- 一些需要通过排序和分组来优化结果的贪心问题。

### 推荐题目
- [P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094)
- [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)
- [P1803 凌乱的yyy / 线段覆盖](https://www.luogu.com.cn/problem/P1803)

### 个人心得
本次题解中大部分作者未提及个人心得，部分作者首次写题解希望大家提建议，体现了对自身成长的追求和对知识分享的积极态度。 

---
处理用时：44.83秒