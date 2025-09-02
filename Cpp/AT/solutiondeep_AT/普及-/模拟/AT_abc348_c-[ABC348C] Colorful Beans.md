# 题目信息

# [ABC348C] Colorful Beans

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc348/tasks/abc348_c

$ N $ 種類のビーンズが $ 1 $ 粒ずつあります。 $ i $ 種類目のビーンズはおいしさが $ A_i $ で色が $ C_i $ です。ビーンズは混ぜられており、色でしか区別することができません。

あなたはビーンズの色を $ 1 $ つ選び、その色のビーンズをどれか $ 1 $ 粒食べます。ビーンズの色をうまく選ぶことで、食べる可能性のあるビーンズのおいしさの最小値を最大化してください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^{5} $
- $ 1\ \leq\ A_i\ \leq\ 10^{9} $
- $ 1\ \leq\ C_i\ \leq\ 10^{9} $
- 入力は全て整数である。
 
### Sample Explanation 1

同じ色のビーンズは互いに区別がつかないことに注意してください。 選ぶことができる色は 色 $ 1 $ と 色 $ 5 $ です。 - 色 $ 1 $ のビーンズは $ 2 $ 種類あり、美味しさはそれぞれ $ 100,\ 40 $ です。よって、色 $ 1 $ を選んだときのおいしさの最小値は $ 40 $ です。 - 色 $ 5 $ のビーンズは $ 2 $ 種類あり、美味しさはそれぞれ $ 20,\ 30 $ です。よって、色 $ 5 $ を選んだときのおいしさの最小値は $ 20 $ です。 おいしさの最小値を最大化するには 色 $ 1 $ を選べばよいため、そのときの最小値である $ 40 $ を出力します。

## 样例 #1

### 输入

```
4

100 1

20 5

30 5

40 1```

### 输出

```
40```

## 样例 #2

### 输入

```
10

68 3

17 2

99 2

92 4

82 4

10 3

100 2

78 1

3 1

35 4```

### 输出

```
35```

# AI分析结果

### 题目内容翻译
有 $N$ 种豆子，每种豆子各有 1 粒。第 $i$ 种豆子的美味度为 $A_i$，颜色为 $C_i$。豆子混在一起，只能通过颜色来区分。

你需要选择一种颜色的豆子，然后吃一粒这种颜色的豆子。请通过巧妙选择豆子的颜色，使得所吃豆子美味度的最小值最大化。

### 综合分析与结论
这些题解的核心思路都是先找出每种颜色豆子的最小美味度，再从这些最小值中找出最大值。不过在具体实现上有所不同，主要分为两种方法：
- **使用 `map` 存储**：由于颜色 $C_i$ 的范围达到 $10^9$，直接使用数组会导致内存溢出，因此很多题解使用 `map` 来存储每种颜色豆子的最小美味度。这种方法代码简洁，实现起来较为容易。
- **结构体排序**：将豆子的信息存储在结构体中，按照颜色进行排序，使得相同颜色的豆子相邻。然后遍历排序后的结构体，找出每种颜色豆子的最小美味度。这种方法的时间复杂度主要取决于排序操作，为 $O(N \log N)$。

### 评分较高的题解
- **作者：Little_x_starTYJ（5星）**
    - **关键亮点**：提供了两种不同的思路和代码实现，思路清晰，代码可读性高，还对两种方法的优缺点进行了总结。
    - **核心代码**：
```cpp
// 第一种思路：使用桶的思想标记
#include <bits/stdc++.h>
using namespace std;
#define int long long
struct node {
    int a, c;
}b[200010];
map<int, int> m;
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> b[i].a >> b[i].c;
        if (m[b[i].c] == 0)
            m[b[i].c] = b[i].a;
        else 
            m[b[i].c] = min(m[b[i].c], b[i].a);
    }
    int ans = -1e9;
    for (int i = 1; i <= n ;i ++){
        ans = max(m[b[i].c], ans);
    }
    cout << ans;
    return 0;
} 

// 第二种思路：对于每一种的豆子按照美味度从大到小排序
#include <bits/stdc++.h>
using namespace std;
#define int long long
struct node {
    int a, c;
}b[200010];
map<int, int> m;
bool cmp(node a, node b){
    if (a.c!= b.c)
        return a.c < b.c;
    return a.a < b.a;
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> b[i].a >> b[i].c;
    sort(b + 1, b + 1 + n, cmp);
    int ans = -1e9;
    for (int i = 1; i <= n; i++)
        if (b[i].c!= b[i - 1].c)
            ans = max(ans, b[i].a);
    cout << ans;
    return 0;
}
```
- **作者：MinimumSpanningTree（4星）**
    - **关键亮点**：思路简洁明了，代码实现简单，使用 `unordered_map` 提高了程序的运行效率。
    - **核心代码**：
```cpp
#include<iostream>
#include<cstdio>
#include<unordered_map>
#include<algorithm>
#include<cmath>
using namespace std;
unordered_map<int,int> um;
int n,a,b,ans;
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d%d",&a,&b);
        if(!um.count(b)) um[b]=a;
        else um[b]=min(um[b],a);
    }
    for(unordered_map<int,int>::iterator it=um.begin();it!=um.end();it++) ans=max(ans,it->second);
    printf("%d",ans);
    return 0;
}
```
- **作者：__ATRI__（4星）**
    - **关键亮点**：考虑到颜色值可能很大，使用 `map` 对颜色进行重新编码，将 $N$ 种颜色改为 $1$ 到 $N$ 的值，然后用优先队列找出每一种颜色的最小美味度。
    - **核心代码**：
```cpp
#include <bits/stdc++.h>
#define endl '\n'

using namespace std;

using ll=long long;

int n,a[200005],c[200005],cnt,ans;
map<int,int>mp;
priority_queue<int,vector<int>,greater<int> >st[200005];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> n;
    for(int i=1;i<=n;++i){
        cin >> a[i] >> c[i];
        if(!mp.count(c[i]))mp[c[i]]=++cnt;
        c[i]=mp[c[i]];
        st[c[i]].push(a[i]);
    }
    for(int i=1;i<=cnt;++i)ans=max(ans,st[i].top());
    cout << ans << endl;
    return 0;
}
```

### 最优关键思路或技巧
- **使用 `map` 或 `unordered_map`**：当数据范围较大，直接使用数组会导致内存溢出时，可以使用 `map` 或 `unordered_map` 来存储数据，避免内存问题。
- **结构体排序**：对于具有多个属性的数据，可以使用结构体来存储，并通过自定义比较函数对结构体进行排序，方便后续处理。

### 可拓展之处
同类型的题目可能会有不同的约束条件或数据范围，例如豆子的数量可能会更多，或者需要考虑更多的属性。类似的算法套路包括使用哈希表存储数据、排序后遍历处理等。

### 推荐题目
- [P1102 A-B 数对](https://www.luogu.com.cn/problem/P1102)：使用哈希表存储数据，通过遍历和查找来解决问题。
- [P1991 无线通讯网](https://www.luogu.com.cn/problem/P1991)：涉及结构体排序和贪心算法，需要对数据进行排序和处理。
- [P2676 [USACO07DEC]Bookshelf B](https://www.luogu.com.cn/problem/P2676)：需要对数据进行排序和贪心选择，找出满足条件的最优解。

### 个人心得摘录与总结
- **作者：Ray0Regina**：第一次发题解很激动，感谢大佬的指点。在使用 `map` 时要记得判零，复杂度为 $O(n\log n)$。
- **作者：Elysian_Realme**：初看到题想到开桶记录，但看到数据范围后想到离散化，赛时懒得打离散化就用了 `map`，使用 `map` 时要特判初始值为 $0$ 的情况，离散化和 `map` 的复杂度都是 $O(n\log n)$。

总结：在解决这类数据范围较大的问题时，要注意数据结构的选择，避免内存溢出。同时，在使用 `map` 等数据结构时，要注意处理初始值和边界条件。

---
处理用时：55.22秒