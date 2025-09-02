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

### 题目翻译
有 $N$ 种豆子，每种豆子各有 $1$ 粒。第 $i$ 种豆子的美味度为 $A_i$，颜色为 $C_i$。豆子混合在一起，只能通过颜色来区分。

你需要选择一种颜色的豆子，并吃下其中的 $1$ 粒。请通过巧妙地选择豆子的颜色，使得所吃豆子的美味度的最小值尽可能大。

### 综合分析与结论
这些题解的核心目标都是找出每种颜色豆子美味度的最小值，然后在这些最小值中取最大值。主要思路可以分为以下两类：
1. **使用 `map` 或 `unordered_map` 存储**：利用 `map` 或 `unordered_map` 的映射关系，记录每种颜色豆子的最小美味度，最后遍历找出最大值。这种方法简单直接，能有效处理颜色值范围大的问题。
2. **结构体排序**：定义结构体存储豆子的美味度和颜色，按照颜色排序，相同颜色的再按美味度排序。排序后遍历结构体，找出每种颜色的最小美味度，再取最大值。

难点在于颜色值范围达到 $10^9$，直接开数组会导致内存溢出，因此大部分题解使用 `map` 或 `unordered_map` 来解决这个问题。

### 所选题解
- **作者：Little_x_starTYJ（5星）**
    - **关键亮点**：提供了两种思路，思路清晰，代码实现完整，且对两种思路的优缺点进行了对比，具有很强的参考价值。
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
    if (a.c != b.c)
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
        if (b[i].c != b[i - 1].c)
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
    - **关键亮点**：使用 `map` 对颜色进行重新编码，将颜色值映射到较小的范围，再用优先队列找出每一种颜色的最小美味度，思路独特。
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
- **使用 `map` 或 `unordered_map`**：当数据范围较大，直接开数组会导致内存溢出时，可以使用 `map` 或 `unordered_map` 来存储数据，它们可以动态分配内存，有效解决内存问题。
- **结构体排序**：对于需要处理多个属性的数据，可以使用结构体来存储，通过自定义比较函数对结构体进行排序，方便后续的处理。

### 可拓展之处
同类型题目可能会有不同的属性和要求，但核心思路都是对数据进行分类处理，找出每一类的最小值或最大值。类似的算法套路包括使用哈希表、排序、优先队列等数据结构来解决问题。

### 推荐题目
1. [P1104 生日](https://www.luogu.com.cn/problem/P1104)：本题需要对学生的生日信息进行排序，与本题的结构体排序思路类似。
2. [P1093 奖学金](https://www.luogu.com.cn/problem/P1093)：需要根据学生的成绩信息进行排序和筛选，也可以使用结构体排序的方法。
3. [P1068 分数线划定](https://www.luogu.com.cn/problem/P1068)：根据考生的成绩和录取人数确定分数线，同样可以通过排序来解决。

### 个人心得摘录与总结
- **Ray0Regina**：第一次发题解很激动，感谢大佬的指点。提醒我们在学习过程中可以向他人请教，获得帮助和指导。
- **I_Love_DS**：这场比赛只做出了前 $3$ 题，认为本题比较简单。告诉我们要对自己有信心，遇到问题要勇于尝试。

---
处理用时：46.45秒