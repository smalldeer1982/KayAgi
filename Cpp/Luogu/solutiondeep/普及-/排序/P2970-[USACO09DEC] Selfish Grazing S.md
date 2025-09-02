# 题目信息

# [USACO09DEC] Selfish Grazing S

## 题目描述

Each of Farmer John's N (1 <= N <= 50,000) cows likes to graze in a certain part of the pasture, which can be thought of as a large one-dimeensional number line. Cow i's favorite grazing range starts at location S\_i and ends at location E\_i (1 <= S\_i < E\_i; S\_i < E\_i <= 100,000,000).

Most folks know the cows are quite selfish; no cow wants to share any of its grazing area with another. Thus, two cows i and j can only graze at the same time if either S\_i >= E\_j or E\_i <= S\_j. FJ would like to know the maximum number of cows that can graze at the same time for a given set of cows and their preferences.

Consider a set of 5 cows with ranges shown below:

```cpp
  ... 1    2    3    4    5    6    7    8    9   10   11   12   13 ...
  ... |----|----|----|----|----|----|----|----|----|----|----|----|----
Cow 1:      <===:===>          :              :              :
Cow 2: <========:==============:==============:=============>:
Cow 3:          :     <====>   :              :              :
Cow 4:          :              :     <========:===>          :
Cow 5:          :              :     <==>     :              :
```
These ranges represent (2, 4), (1, 12), (4, 5), (7, 10), and (7, 8), respectively.

For a solution, the first, third, and fourth (or fifth) cows can all graze at the same time. If the second cow grazed, no other cows could graze. Also, the fourth and fifth cows cannot graze together, so it is impossible for four or more cows to graze.

约翰有N(1≤N≤50000)头牛，约翰的草地可以认为是一条直线．每只牛只喜欢在某个特定的范围内吃草．第i头牛喜欢在区间(Si，Ei)吃草，1≤Si<Ei≤1,000,000,00.

奶牛们都很自私，他们不喜欢和其他奶牛共享自己喜欢吃草的领域，因此约翰要保证任意

两头牛都不会共享他们喜欢吃草昀领域．如果奶牛i和奶牛J想要同时吃草，那么要满足：Si>=Ej或者Ei≤Sj．约翰想知道在同一时刻，最多可以有多少头奶牛同时吃草？


## 样例 #1

### 输入

```
5 
2 4 
1 12 
4 5 
7 10 
7 8 
```

### 输出

```
3 
```

# AI分析结果

### 综合分析与结论
这些题解核心思路一致，均为贪心算法，按区间右端点排序，遍历选取不重叠区间以获最大数量。部分题解思路阐述详细，部分代码简洁。各题解算法要点相同，但思路清晰度、代码可读性和优化程度有差异。

### 所选题解
- **作者：微香玉烛暗（5星）**
    - **关键亮点**：思路清晰，结合数据详细分析，代码规范易读。
    - **核心代码**：
```cpp
# include <cstdio>
# include <iostream>
# include <algorithm>
using namespace std;
const int N=50005;
int n,ans=1,now;

struct node {
    int x,y;
    friend bool operator < (const node &p,const node &q) {
        return p.y<q.y;
    }
}a[N];

int main () {
    scanf ("%d",&n);
    for (int i=1;i<=n;i++)
        scanf ("%d%d",&a[i].x,&a[i].y);
    sort (a+1,a+1+n);
    now=a[1].y;
    for (int i=2;i<=n;i++) {
        if (a[i].x>=now) {
            ans++;
            now=a[i].y;
        }
    }
    printf ("%d\n",ans);
    return 0;
}
```
    - **核心思想**：定义结构体存储区间，按右端点排序，遍历区间，若当前区间左端点大于等于上一区间右端点，则选取该区间并更新右端点。

- **作者：user48442（4星）**
    - **关键亮点**：思路详细，给出错误思路示例并证明正确思路，代码模块化。
    - **核心代码**：
```cpp
struct Node
{
    int s;
    int e;
}cow[50005];

bool cmp(Node a, Node b)
{
    if(a.e == b.e) return a.s > a.s;
    return a.e < b.e;
}

void init(void)
{
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
        scanf("%d %d", &cow[i].s, &cow[i].e);
    sort(cow + 1, cow + 1 + n, cmp);
    return;
}

void work(void)
{
    int ans = 1, last = cow[1].e;
    for(int i = 2; i <= n; i++)
    {
        if(cow[i].s >= last)
        {
            last = cow[i].e;
            ans++;
        }
    }
    printf("%d", ans);
    return;
}

int main(void)
{
    init();
    work();
    return 0;
}
```
    - **核心思想**：定义结构体存储区间，按右端点排序，从第二个区间开始遍历，若当前区间左端点大于等于上一区间右端点，则选取该区间并更新右端点。

### 最优关键思路或技巧
- **贪心策略**：按区间右端点排序，优先选择结束早的区间，为后续区间留更多空间。
- **结构体排序**：用结构体存储区间左右端点，自定义比较函数按右端点排序。

### 可拓展之处
同类型题如区间选点、区间覆盖问题，均可用贪心算法，按区间右端点排序求解。

### 洛谷相似题目推荐
- P1803 凌乱的yyy / 线段覆盖
- P2082 区间覆盖
- P1233 木棍加工

### 个人心得摘录与总结
- **user48442**：一开始按区间左端点排序思路错误，后转投按右端点排序并用贪心求解，提醒做题时多尝试不同思路并验证。 

---
处理用时：22.44秒