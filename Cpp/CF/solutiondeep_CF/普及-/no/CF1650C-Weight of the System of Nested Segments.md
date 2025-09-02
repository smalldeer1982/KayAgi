# 题目信息

# Weight of the System of Nested Segments

## 题目描述

On the number line there are $ m $ points, $ i $ -th of which has integer coordinate $ x_i $ and integer weight $ w_i $ . The coordinates of all points are different, and the points are numbered from $ 1 $ to $ m $ .

A sequence of $ n $ segments $ [l_1, r_1], [l_2, r_2], \dots, [l_n, r_n] $ is called system of nested segments if for each pair $ i, j $ ( $ 1 \le i < j \le n $ ) the condition $ l_i < l_j < r_j < r_i $ is satisfied. In other words, the second segment is strictly inside the first one, the third segment is strictly inside the second one, and so on.

For a given number $ n $ , find a system of nested segments such that:

- both ends of each segment are one of $ m $ given points;
- the sum of the weights $ 2\cdot n $ of the points used as ends of the segments is minimal.

For example, let $ m = 8 $ . The given points are marked in the picture, their weights are marked in red, their coordinates are marked in blue. Make a system of three nested segments:

- weight of the first segment: $ 1 + 1 = 2 $
- weight of the second segment: $ 10 + (-1) = 9 $
- weight of the third segment: $ 3 + (-2) = 1 $
- sum of the weights of all the segments in the system: $ 2 + 9 + 1 = 12 $

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1650C/5aeab71f3d5a716d6e18fda5439622dc4cd35cbc.png)System of three nested segments

## 说明/提示

The first test case coincides with the example from the condition. It can be shown that the weight of the composed system is minimal.

The second test case has only $ 6 $ points, so you need to use each of them to compose $ 3 $ segments.

## 样例 #1

### 输入

```
3

3 8
0 10
-2 1
4 10
11 20
7 -1
9 1
2 3
5 -2

3 6
-1 2
1 3
3 -1
2 4
4 0
8 2

2 5
5 -1
3 -2
1 0
-2 0
-5 -3```

### 输出

```
12
2 6
5 1
7 8

10
1 6
5 2
3 4

-6
5 1
4 2```

# AI分析结果

### 题目内容
# 嵌套线段系统的权重

## 题目描述
在数轴上有 $m$ 个点，第 $i$ 个点具有整数坐标 $x_i$ 和整数权重 $w_i$ 。所有点的坐标都不同，并且这些点从 $1$ 到 $m$ 编号。

一个由 $n$ 条线段 $[l_1, r_1], [l_2, r_2], \dots, [l_n, r_n]$ 组成的序列被称为嵌套线段系统，如果对于每一对 $i, j$（$1 \leq i < j \leq n$）都满足条件 $l_i < l_j < r_j < r_i$ 。换句话说，第二条线段严格在第一条线段内部，第三条线段严格在第二条线段内部，依此类推。

对于给定的数字 $n$ ，找到一个嵌套线段系统，使得：
- 每条线段的两个端点都是 $m$ 个给定点中的一个；
- 用作线段端点的 $2 \cdot n$ 个点的权重之和最小。

例如，设 $m = 8$ 。给定的点在图中标记，它们的权重用红色标记，它们的坐标用蓝色标记。构建一个由三条嵌套线段组成的系统：
- 第一条线段的权重：$1 + 1 = 2$
- 第二条线段的权重：$10 + (-1) = 9$
- 第三条线段的权重：$3 + (-2) = 1$
- 系统中所有线段的权重之和：$2 + 9 + 1 = 12$

![嵌套线段系统示例](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1650C/5aeab71f3d5a716d6e18fda5439622dc4cd35cbc.png) 三条嵌套线段的系统

## 说明/提示
第一个测试用例与题目条件中的示例一致。可以证明所构建系统的权重是最小的。

第二个测试用例只有 $6$ 个点，因此你需要使用它们中的每一个来构建 $3$ 条线段。

## 样例 #1
### 输入
```
3

3 8
0 10
-2 1
4 10
11 20
7 -1
9 1
2 3
5 -2

3 6
-1 2
1 3
3 -1
2 4
4 0
8 2

2 5
5 -1
3 -2
1 0
-2 0
-5 -3
```
### 输出
```
12
2 6
5 1
7 8

10
1 6
5 2
3 4

-6
5 1
4 2
```

### 算法分类
贪心

### 题解综合分析与结论
所有题解思路基本一致，均基于贪心策略。要点为：
 - **确定连线方式唯一性**：一旦选定 $2n$ 个点，必然存在唯一连线方式满足嵌套要求，即每次选取最左边和最右边的点相连。
 - **贪心选择**：为使权重和最小，选择权重最小的 $2n$ 个点。
 - **实现步骤**：先按权重对所有点排序，选出前 $2n$ 个点，再按位置对这 $2n$ 个点排序，之后依次输出最左和最右点的编号作为线段端点。

各题解在代码实现上有差异，如输入输出方式、结构体定义、排序函数写法等，但核心思路相同。

### 所选的题解
 - **作者：xhhhh36 (5星)**
    - **关键亮点**：思路清晰，代码简洁明了，结构体定义合理，两次排序逻辑清晰，符合常规解题思路。
    - **重点代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
int t,n,m;
long long ans;
struct node {
    int x,w,no;
}a[200001];
bool cmp(node x,node y) {
    if (x.w==y.w) return x.no<y.no;
    return x.w<y.w;
}
bool cmp1(node x,node y) {
    return x.x<y.x;
}
int main() {
    cin>>t;
    while (t--) {
        cin>>n>>m;
        ans=0;
        for (int i=1;i<=m;i++) {
            cin>>a[i].x>>a[i].w;
            a[i].no=i;
        }
        sort(a+1,a+1+m,cmp);
        for (int i=1;i<=2*n;i++) {
            ans+=a[i].w;
        }
        cout<<ans<<endl;
        sort(a+1,a+1+2*n,cmp1);
        for (int i=1;i<=n;i++) {
            cout<<a[i].no<<" "<<a[2*n-i+1].no<<endl;
        }
        cout<<endl;
    }
    return 0;
}
```
核心实现思想：定义结构体存储点的坐标、权重和编号。第一次按权重排序选取前 $2n$ 个点并求和输出，第二次按位置排序后按顺序输出配对端点编号。

 - **作者：DaiRuiChen007 (4星)**
    - **关键亮点**：对题目分析详细，代码注释清晰，使用宏定义简化代码书写，排序函数定义明确。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=2e5+1;
struct node {
    int id,pos,val;
}a[MAXN];
inline bool Compare_Val(const node &x,const node &y) {
    return x.val<y.val;
}
inline bool Compare_Pos(const node &x,const node &y) {
    return x.pos<y.pos;
}
inline void solve() {
    int n,m,ans=0;
    scanf("%lld%lld",&n,&m);
    for(register int i=1;i<=m;++i) {
        scanf("%lld%lld",&a[i].pos,&a[i].val);
        a[i].id=i;
    }
    sort(a+1,a+m+1,Compare_Val);
    for(register int i=1;i<=2*n;++i) ans+=a[i].val;
    printf("%lld\n",ans);
    sort(a+1,a+2*n+1,Compare_Pos);
    for(register int i=1;i<=n;++i) {
        printf("%lld %lld\n",a[i].id,a[2*n+1-i].id);
    }
    return ;
}
signed main() {
    int T;
    scanf("%lld",&T);
    while(T--) solve();
    return 0;
}
```
核心实现思想：通过定义结构体存储点的编号、位置和权值，先按权值排序选取点并计算权重和输出，再按位置排序输出配对端点编号。

 - **作者：cyrxdzj (4星)**
    - **关键亮点**：思路阐述简洁，代码结构清晰，使用结构体和两个比较函数分别实现按权值和位置排序。
    - **重点代码**：
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
struct point_object {
    int x,w;
    int id;
}point[200005];
int t;
int n,m;
bool cmp1(point_object a,point_object b) {
    return a.w<b.w;
}
bool cmp2(point_object a,point_object b) {
    return a.x<b.x;
}
int main() {
    scanf("%d",&t);
    while(t--) {
        int ans=0;
        scanf("%d%d",&n,&m);
        for(int i=1;i<=m;i++) {
            scanf("%d%d",&point[i].x,&point[i].w);
            point[i].id=i;
        }
        sort(point+1,point+1+m,cmp1);
        sort(point+1,point+1+2*n,cmp2);
        for(int i=1;i<=2*n;i++) {
            ans+=point[i].w;
        }
        printf("%d\n",ans);
        for(int i=1;i<=n;i++) {
            printf("%d %d\n",point[i].id,point[2*n-i+1].id);
        }
        printf("\n");
    }
    return 0;
}
```
核心实现思想：定义结构体存储点的坐标、权重和编号，先按权值排序，再对前 $2n$ 个点按位置排序，计算权重和并输出配对端点编号。

### 最优关键思路或技巧
关键在于发现只要选定 $2n$ 个点，连线方式就唯一确定，从而将问题转化为贪心选择权重最小的 $2n$ 个点。利用结构体存储点的多种属性，通过两次排序分别满足选取最小权重点和确定线段端点顺序的需求。

### 可拓展之处
此类题目属于贪心策略在几何或数轴相关问题中的应用。类似套路是先分析问题找到可贪心的方向，比如本题根据连线方式固定从而选择最小权重的点。同类型题通常围绕在满足特定条件下求最值，可能涉及不同的几何形状或数据关系，但都可尝试从贪心角度思考。

### 推荐题目
 - [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)
 - [P1248 加工生产调度](https://www.luogu.com.cn/problem/P1248)
 - [P2123 皇后游戏](https://www.luogu.com.cn/problem/P2123)

### 个人心得摘录与总结
无个人心得相关内容。 

---
处理用时：62.88秒