# 题目信息

# Summation Game

## 题目描述

Alice and Bob are playing a game. They have an array $ a_1, a_2,\ldots,a_n $ . The game consists of two steps:

- First, Alice will remove at most $ k $ elements from the array.
- Second, Bob will multiply at most $ x $ elements of the array by $ -1 $ .

Alice wants to maximize the sum of elements of the array while Bob wants to minimize it. Find the sum of elements of the array after the game if both players play optimally.

## 说明/提示

In the first test case, it is optimal for Alice to remove the only element of the array. Then, the sum of elements of the array is $ 0 $ after the game is over.

In the second test case, it is optimal for Alice to not remove any elements. Bob will then multiply $ 4 $ by $ -1 $ . So the final sum of elements of the array is $ 3+1+2-4=2 $ .

In the fifth test case, it is optimal for Alice to remove $ 9, 9 $ . Bob will then multiply $ 5, 5, 3 $ by $ -1 $ . So the final sum of elements of the array is $ -5-5-3+3+3+2=-5 $ .

## 样例 #1

### 输入

```
8
1 1 1
1
4 1 1
3 1 2 4
6 6 3
1 4 3 2 5 6
6 6 1
3 7 3 3 32 15
8 5 3
5 5 3 3 3 2 9 9
10 6 4
1 8 2 9 3 3 4 5 3 200
2 2 1
4 3
2 1 2
1 3```

### 输出

```
0
2
0
3
-5
-9
0
-1```

# AI分析结果

### 题目内容中文重写
# 求和游戏

## 题目描述

爱丽丝和鲍勃正在玩一个游戏。他们有一个数组 $ a_1, a_2,\ldots,a_n $ 。游戏由两个步骤组成：

- 首先，爱丽丝最多可以从数组中移除 $ k $ 个元素。
- 其次，鲍勃最多可以将数组中的 $ x $ 个元素乘以 $ -1 $ 。

爱丽丝希望最大化数组元素的总和，而鲍勃希望最小化它。如果两个玩家都采取最优策略，求游戏结束后数组元素的总和。

## 说明/提示

在第一个测试用例中，爱丽丝最优的做法是移除数组中唯一的元素。然后，游戏结束后数组元素的总和为 $ 0 $ 。

在第二个测试用例中，爱丽丝最优的做法是不移除任何元素。然后鲍勃会将 $ 4 $ 乘以 $ -1 $ 。所以数组元素的最终总和是 $ 3+1+2-4=2 $ 。

在第五个测试用例中，爱丽丝最优的做法是移除 $ 9, 9 $ 。然后鲍勃会将 $ 5, 5, 3 $ 乘以 $ -1 $ 。所以数组元素的最终总和是 $ -5-5-3+3+3+2=-5 $ 。

## 样例 #1

### 输入
```
8
1 1 1
1
4 1 1
3 1 2 4
6 6 3
1 4 3 2 5 6
6 6 1
3 7 3 3 32 15
8 5 3
5 5 3 3 3 2 9 9
10 6 4
1 8 2 9 3 3 4 5 3 200
2 2 1
4 3
2 1 2
1 3
```

### 输出
```
0
2
0
3
-5
-9
0
-1
```

### 算法分类
枚举

### 综合分析与结论
这些题解的核心思路都是基于贪心和枚举的思想。由于鲍勃要使总和最小，他会优先选择将较大的数取反；而爱丽丝为了让总和最大，会优先删除较大的数，但不清楚删除多少个最优，所以需要枚举爱丽丝删除的个数。

各题解的算法要点主要包括对数组进行排序，以便确定数的大小顺序，部分题解使用前缀和优化计算总和的过程，提高效率。

解决的难点在于如何确定爱丽丝的最优删除策略，通过枚举所有可能的删除个数，计算出每种情况下的最终总和，然后取最大值得到最终结果。

### 所选题解
- **作者：ThySecret（4星）**
  - 关键亮点：思路清晰，详细推导了公式，使用前缀和优化，代码可读性高。
  - 个人心得：无
- **作者：kczw（4星）**
  - 关键亮点：思路简洁明了，代码实现较为简洁。
  - 个人心得：无
- **作者：_smart_stupid_（4星）**
  - 关键亮点：使用滑动窗口的思想维护总和，思路独特。
  - 个人心得：注意答案初始化为负无穷。

### 重点代码
#### ThySecret 的题解
```c++
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> PII;

const int N = 2e5 + 9;
const int INF = 0x3f3f3f3f;

int a[N], pre[N], maxn;

void solve()
{
    maxn = -INF;        // 多测注意还原

    int n, k, x; cin >> n >> k >> x;
    for (int i = 1; i <= n; i ++) cin >> a[i];
    sort(a + 1, a + 1 + n, greater<>());    // 从大到小排序
    for (int i = 1; i <= n; i ++) pre[i] = pre[i - 1] + a[i];    // 预处理前缀和数组

    for (int i = 0; i <= k; i ++)         // i 指的是 Alice 要删除元素的个数
    {
        int res = 0;
        res = pre[n] - 2 * pre[min(i + x, n)] + pre[i];
        maxn = max(maxn, res);
    }
    cout << maxn << '\n';
}

signed main()
{
    int T; cin >> T;
    while (T --) solve();

    return 0;
}
```
核心实现思想：先对数组从大到小排序，然后预处理前缀和数组。通过枚举爱丽丝删除的元素个数 $i$，利用前缀和计算出每种情况下的最终总和，取最大值作为结果。

#### kczw 的题解
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int t,n,k,x,a[400005];
bool cmp(int c,int d){return c>d;}
int main(){
    scanf("%d",&t);
    while(t--){
        int sum=0,an=0,s;
        scanf("%d%d%d",&n,&k,&x);
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i]);
            sum+=a[i];
        }
        sort(a+1,a+n+1,cmp);
        int l=1,r=x;
        for(int i=1;i<=x;i++)an+=-2*a[i];
        s=an;
        for(;l<=k;l++,r++){
            s=s+a[l]-a[r+1<=n?r+1:0]*2;
            an=max(an,s);
        }
        printf("%d\n",sum+an);
    }
    return 0;
}
```
核心实现思想：先计算数组的总和，对数组从大到小排序。先计算鲍勃对前 $x$ 个数取反后的变化量，然后枚举爱丽丝删除的个数，更新变化量，取最大值，最后加上初始总和得到最终结果。

#### _smart_stupid_ 的题解
```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
#include <stack>
#include <cmath>
#include <list>
#include <set>
#include <map>
using namespace std;
int t;
int n, k, x, a[200100];
int sum;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> t;
    while (t --) {
        cin >> n >> k >> x;
        for (int i = 1; i <= n; i ++) cin >> a[i];
        sort (a + 1, a + n + 1);
        sum = 0;
        for (int i = 1; i <= n; i ++) sum += a[i];
        int ans = 0;
        int tmp = 0;
        for (int i = n; i >= max(n - x + 1, 1); i --) {
            tmp += a[i];
        }
        ans = -0x3f3f3f3f;
        for (int i = 0; i <= k; i ++) {
            ans = max(ans, sum - tmp * 2);
            sum -= a[n - i];
            tmp -= a[n - i];
            if (n - i - x >= 1) tmp += a[n - i - x];
        }
        cout << ans << "\n";
    }
    return 0;
}
```
核心实现思想：先对数组从小到大排序，计算数组总和。计算鲍勃对最大的 $x$ 个数取反后的变化量，然后枚举爱丽丝删除的个数，使用滑动窗口的思想更新变化量，取最大值作为结果。

### 最优关键思路或技巧
- **贪心策略**：鲍勃优先选择较大的数取反，爱丽丝优先删除较大的数。
- **枚举思想**：枚举爱丽丝删除的个数，找出最优解。
- **前缀和优化**：使用前缀和数组可以在 $O(1)$ 时间内计算部分和，提高效率。
- **滑动窗口**：部分题解使用滑动窗口的思想维护总和，减少重复计算。

### 可拓展之处
同类型题或类似算法套路：这类涉及多个玩家博弈，每个玩家有不同操作目标的题目，通常可以先分析每个玩家的最优策略，然后通过枚举、贪心等方法找出最终的最优解。例如一些涉及资源分配、策略选择的博弈问题。

### 推荐洛谷题目
- P1007 独木桥
- P1223 排队接水
- P2123 皇后游戏

---
处理用时：49.91秒