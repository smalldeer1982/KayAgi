# 题目信息

# Dress'em in Vests!

## 题目描述

The Two-dimensional kingdom is going through hard times... This morning the Three-Dimensional kingdom declared war on the Two-dimensional one. This (possibly armed) conflict will determine the ultimate owner of the straight line.

The Two-dimensional kingdom has a regular army of $ n $ people. Each soldier registered himself and indicated the desired size of the bulletproof vest: the $ i $ -th soldier indicated size $ a_{i} $ . The soldiers are known to be unpretentious, so the command staff assumes that the soldiers are comfortable in any vests with sizes from $ a_{i}-x $ to $ a_{i}+y $ , inclusive (numbers $ x,y>=0 $ are specified).

The Two-dimensional kingdom has $ m $ vests at its disposal, the $ j $ -th vest's size equals $ b_{j} $ . Help mobilize the Two-dimensional kingdom's army: equip with vests as many soldiers as possible. Each vest can be used only once. The $ i $ -th soldier can put on the $ j $ -th vest, if $ a_{i}-x<=b_{j}<=a_{i}+y $ .

## 说明/提示

In the first sample you need the vests' sizes to match perfectly: the first soldier gets the first vest (size 1), the third soldier gets the second vest (size 3). This sample allows another answer, which gives the second vest to the fourth soldier instead of the third one.

In the second sample the vest size can differ from the desired size by at most 2 sizes, so all soldiers can be equipped.

## 样例 #1

### 输入

```
5 3 0 0
1 2 3 3 4
1 3 5
```

### 输出

```
2
1 1
3 2
```

## 样例 #2

### 输入

```
3 3 2 2
1 5 9
3 5 7
```

### 输出

```
3
1 1
2 2
3 3
```

# AI分析结果

### 题目重写
# 穿上防弹背心！

## 题目描述
二维王国正经历艰难时期…… 今天早上，三维王国向二维王国宣战。这场（可能是武装的）冲突将决定直线的最终归属。

二维王国有一支正规军，共有 $n$ 人。每个士兵都进行了登记，并表明了所需防弹背心的尺寸：第 $i$ 个士兵表明的尺寸为 $a_{i}$ 。已知士兵们并不挑剔，所以指挥人员认为，只要背心尺寸在 $a_{i}-x$ 到 $a_{i}+y$ （包括两端值，$x,y\geq0$ 为给定值）之间，士兵们就会感到舒适。

二维王国现有 $m$ 件背心可供调配，第 $j$ 件背心的尺寸为 $b_{j}$ 。请协助二维王国动员军队：为尽可能多的士兵配备背心。每件背心只能使用一次。如果 $a_{i}-x\leq b_{j}\leq a_{i}+y$ ，则第 $i$ 个士兵可以穿上第 $j$ 件背心。

## 说明/提示
在第一个示例中，需要背心尺寸完全匹配：第一个士兵拿第一件背心（尺寸为1），第三个士兵拿第二件背心（尺寸为3）。此示例还有另一种答案，即把第二件背心给第四个士兵而不是第三个士兵。

在第二个示例中，背心尺寸与所需尺寸的差异最多为2个单位，所以所有士兵都能配备上。

## 样例 #1
### 输入
```
5 3 0 0
1 2 3 3 4
1 3 5
```
### 输出
```
2
1 1
3 2
```
## 样例 #2
### 输入
```
3 3 2 2
1 5 9
3 5 7
```
### 输出
```
3
1 1
2 2
3 3
```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路均为贪心算法，即让每个士兵穿上在其可接受尺寸范围内尽可能小的背心，这样能使后续士兵有更多机会穿上合适的背心。算法要点在于使用双指针法遍历士兵需求数组 `a` 和背心尺寸数组 `b` 。解决难点主要是如何保证每次找到的背心尺寸是当前士兵可接受范围内最小的，以及处理边界条件，如数组遍历结束等情况。不同题解在代码实现细节上有所差异，如记录答案的方式、边界条件的判断顺序等。

### 所选的题解
- **作者：lsy_41 (5星)**
  - **关键亮点**：思路清晰，对输入输出、思路、实现和细节都有详细解释，代码注释丰富，可读性强。
  - **个人心得**：无
  - **重点代码**：
```cpp
#include <bits/stdc++.h>
#define maxn 100005
using namespace std;
int n, m, x, y, cnt; 
int A[maxn], B[maxn]; 
int ansx[maxn], ansy[maxn]; 
int main() {
    cin >> n >> m >> x >> y;
    for (int i = 1; i <= n; i++)
        cin >> A[i];
    for (int i = 1; i <= m; i++)
        cin >> B[i];
    int ia = 1, ib = 1; 
    while (ia <= n && ib <= m) { 
        while (B[ib] + x < A[ia]) 
            ib++;
        if (ia <= n && ib <= m && A[ia] - x <= B[ib] && A[ia] + y >= B[ib]) {
            ansx[++cnt] = ia; 
            ansy[cnt] = ib;
            ib++;
        }
        ia++;
    }
    cout << cnt << endl;
    for (int i = 1; i <= cnt; i++)
        cout << ansx[i] << " " << ansy[i] << endl; 
    return 0;
}
```
  - **核心实现思想**：用双指针 `ia` 和 `ib` 分别遍历数组 `A` 和 `B` ，对于每个 `A[ia]` ，找到满足条件的最小 `B[ib]` ，若找到则记录答案并移动指针，否则继续寻找。

- **作者：Erinyes (4星)**
  - **关键亮点**：对思路和求解过程有清晰的分步阐述，代码简洁明了，使用结构体记录答案，逻辑清晰。
  - **个人心得**：无
  - **重点代码**：
```cpp
#include<bits/stdc++.h>
#define maxn 100005
using namespace std;
struct node{int x,y;}ans[maxn];
int n,m,cnt;
int x,y;
int a[maxn],b[maxn];
int main(){
    scanf("%d %d %d %d",&n,&m,&x,&y);
    for(int i=1;i<=n;i++) scanf("%d",a+i);
    for(int i=1;i<=m;i++) scanf("%d",b+i);
    int pa=1,pb=1;
    while(pa<=n && pb<=m){
        while(b[pb]<a[pa]-x) pb++;
        if(pa<=n && pb<=m && b[pb]>=a[pa]-x && b[pb]<=a[pa]+y){ 
            ans[++cnt]=(node){pa,pb}; 
            pb++; 
        }
        pa++;
    }
    printf("%d\n",cnt);
    for(int i=1;i<=cnt;i++) printf("%d %d\n",ans[i].x,ans[i].y);
    getchar(); getchar();
    return 0;
}
```
  - **核心实现思想**：通过双指针 `pa` 和 `pb` 遍历两个数组，先跳过不可匹配的 `b[pb]` ，若找到可匹配的则记录答案并移动指针。

- **作者：huhaoming2011 (4星)**
  - **关键亮点**：分析部分点明贪心策略的本质，代码简洁，对边界条件处理得当。
  - **个人心得**：提到要注意判断衣服尺寸太大的情况，避免不合法。
  - **重点代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 + 100;
int n, m, x, cnt, y, t1, t2, a[MAXN], b[MAXN];
pair <int, int > ans[MAXN];
int main()
{
    t1 = t2 = 1;
    scanf("%d %d %d %d", &n, &m, &x, &y);
    for(int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    for(int i = 1; i <= m; i++)
        scanf("%d", &b[i]);
    while(t1 <= n and t2 <= m)
    {
        while(a[t1] - x > b[t2] and t2 <= m)
            t2++;
        if(t2 > m or t1 > n)
            break;
        if(a[t1] - x <= b[t2] and a[t1] + y >= b[t2])
        {
            ans[++cnt].first = t1;
            ans[cnt].second = t2;
            t2++;
        }
        t1++;
    }
    printf("%d\n", cnt);
    for(int i = 1; i <= cnt; i++)
        printf("%d %d\n", ans[i].first, ans[i].second);
    return 0;
}
```
  - **核心实现思想**：双指针遍历数组，跳过不可匹配的 `b[t2]` ，找到可匹配的则记录答案并移动指针，同时注意边界条件的判断。

### 最优关键思路或技巧
采用贪心策略，利用双指针法遍历两个有序数组，每次为当前士兵选择可接受范围内最小尺寸的背心，以保证整体能匹配更多士兵。这种方法时间复杂度为 $O(n + m)$ ，高效地解决了问题。

### 可拓展思路
同类型题通常涉及资源分配、任务调度等场景，核心是在满足一定条件下最大化或最小化某个目标。类似算法套路是在面对两个有序序列的匹配问题时，优先考虑双指针法结合贪心策略，通过合理移动指针来寻找最优解。

### 洛谷题目推荐
- [P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094)
- [P1182 数列分段 Section II](https://www.luogu.com.cn/problem/P1182)
- [P2672 推销员](https://www.luogu.com.cn/problem/P2672)

---
处理用时：76.05秒