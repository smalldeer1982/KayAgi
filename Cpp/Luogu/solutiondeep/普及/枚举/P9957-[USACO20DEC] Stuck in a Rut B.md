# 题目信息

# [USACO20DEC] Stuck in a Rut B

## 题目描述

Farmer John 最近扩大了他的农场，从奶牛们的角度看来这个农场相当于是无限大了！奶牛们将农场上放牧的区域想作是一个由正方形方格组成的无限大二维方阵，每个方格中均有美味的草（将每个方格看作是棋盘上的一个方格）。Farmer John 的 $N$ 头奶牛（$1\le N\le 50$）初始时位于不同的方格中，一部分朝向北面，一部分朝向东面。

每一小时，每头奶牛会执行以下二者之一：

 - 如果她当前所在的方格里的草已经被其他奶牛吃掉了，则她会停下。
 - 吃完她当前所在的方格中的所有草，并向她朝向的方向移动一个方格。

经过一段时间，每头奶牛的身后会留下一条被啃秃了的轨迹。

如果两头奶牛在一次移动中移动到了同一个有草的方格，她们会分享这个方格中的草，并在下一个小时继续沿她们朝向的方向移动。

请求出每头奶牛吃到的草的数量。有些奶牛永远不会停下，从而吃到无限多的草。 

## 说明/提示

### 测试点性质

 - 测试点 $2-5$ 中，所有坐标不超过 $100$。
 - 测试点 $6-10$ 没有额外限制。

## 样例 #1

### 输入

```
6
E 3 5
N 5 3
E 4 6
E 10 4
N 11 2
N 8 1```

### 输出

```
5
3
Infinity
Infinity
2
5```

# AI分析结果

• 综合分析与结论：
    - 思路：这些题解思路大致相同，均是通过分析奶牛移动轨迹的交点来判断奶牛是否会停下。先将向北和向东的奶牛分别处理，再通过枚举不同方向奶牛对，比较它们到交点的距离，确定哪头奶牛会被阻拦。
    - 算法要点：利用结构体存储奶牛信息，通过排序优化枚举过程。排序方式主要有按横坐标、纵坐标或横纵坐标之和排序，排序后可减少不必要的比较，提高效率。
    - 解决难点：关键在于处理奶牛之间的相互阻拦关系，避免重复判断或错误判断。例如一头奶牛提前被阻拦后不应再影响其他奶牛的判断。
    - 整体来看，多数题解思路清晰，但在代码可读性和优化程度上有所差异。

所选的题解：
  - 作者：FZY_CZY (5星)
    - 关键亮点：思路阐述清晰，先提出最初想法，再讲解正解。利用结构体方便排序和处理数据，通过一次双循环同时处理两类奶牛，简化代码。
    - 个人心得：赛上未做出，赛后总结反思得出正解。
    - 重点代码核心实现思想：定义结构体存储奶牛信息，对向北和向东的奶牛分别按横坐标和纵坐标排序，通过双循环枚举两类奶牛，比较到交点距离确定阻拦关系，记录答案。
```cpp
#include<bits/stdc++.h>
#define maxn 55
using namespace std;
struct node{
    int x,y,id;
};//结构体方便排序和处理
node N[maxn],E[maxn];
int sum_n,sum_e,ans[55];
bool cmp1(node a, node b)
{
    return a.x<b.x;
}
bool cmp2(node a, node b)
{
    return a.y<b.y;
}
int main(){
    int n;
    scanf("%d",&n);
    for (int i=1;i<=n;i++)
    {
        char c;
        int x,y;
        scanf(" %c%d%d",&c,&x,&y);//输入
        if (c=='N') N[++sum_n]={x,y,i};
        else E[++sum_e]={x,y,i};
    }
    sort(N+1,N+sum_n+1,cmp1);
    sort(E+1,E+sum_e+1,cmp2);
    //排序后可以减时间复杂度并且简化代码
    for (int i=1;i<=sum_e;i++)
    {
        for (int j=1;j<=sum_n;j++)//双重for，没什么好说的
        {
            if (N[j].x<E[i].x) continue;//如果这两条射线不相交就不存在交点O
            if (N[j].y>E[i].y) continue;//同上
            int A=N[j].x-E[i].x;
            int B=E[i].y-N[j].y;
            if (ans[N[j].id]) continue;//如果N[j]已经有答案，那么这就是最优的了（排过序）
            if (A<B) ans[N[j].id]=B;//如果AO<BO则B是A的答案
            if (A>B)
            {
                ans[E[i].id]=A;//同理
                break;//第一个即最优解，没必要继续遍历
            }
        }
    }
    for (int i=1;i<=n;i++)
    {
        if (ans[i]) printf("%d\n",ans[i]);//奶牛会适量进食
        else printf("Infinity\n");//奶牛会吃撑死
    }
    return 0;
}
```
  - 作者：ABCDEFG12345NM (4星)
    - 关键亮点：详细分析解题思路，重点讲解如何分类讨论被截住时的长度，代码实现逻辑清晰。
    - 个人心得：起初少考虑条件，改正后代码量翻倍但最终做对。
    - 重点代码核心实现思想：定义结构体存储奶牛信息，通过两层循环枚举奶牛对，判断是否相交及比较到交点距离确定阻拦关系，记录最近被阻截位置，最后输出答案。
```cpp
#include <iostream>
#include <stdio.h>
#include <cmath>

using namespace std;

const int MAXN = 5e1 + 10;
struct node
{
    bool fx;
    long long x, y;
} fe[MAXN];
struct WZ
{
    long long x, y;
} wz[MAXN];
long long ans;

int main ()
{
    long long N;
    cin >> N;
    for (int i = 1; i <= N; i ++)
    {
        char sx;
        cin >> sx >> fe[i].x >> fe[i].y;
        if (sx == 'E') fe[i].fx = true;
        else fe[i].fx = false;
    }
    for (int i = 1; i <= N; i ++)
    {
        ans = 1e9 + 10;
        for (int j = 1; j <= N; j ++)
        {
            if (i == j || fe[i].fx == fe[j].fx) continue;
            if (fe[i].fx == true)
            {
                if (fe[i].x > fe[j].x || fe[i].y < fe[j].y) continue;
                if (abs (fe[i].x - fe[j].x) <= abs (fe[i].y - fe[j].y)) continue;
                else
                    if (ans > abs (fe[i].x - fe[j].x))
                    {
                        wz[i].x = fe[j].x, wz[i].y = fe[i].y;
                        ans = abs (fe[i].x - fe[j].x);
                    }
            }
            if (fe[i].fx == false)
            {
                if (fe[i].y > fe[j].y || fe[i].x < fe[j].x) continue;
                if (abs (fe[i].x - fe[j].x) >= abs (fe[i].y - fe[j].y)) continue;
                else
                    if (ans > abs (fe[i].y - fe[j].y))
                    {
                        wz[i].x = fe[i].x, wz[i].y = fe[j].y;
                        ans = abs (fe[i].y - fe[j].y);
                    }
            }
        }
    }
    for (int i = 1; i <= N; i ++)
        if (wz[i].x == 0 && wz[i].y == 0)
            wz[i].x = 1e9 + 10, wz[i].y = 1e9 + 10;
    for (int i = 1; i <= N; i ++)
    {
        ans = 1e9 + 10;
        for (int j = 1; j <= N; j ++)
        {
            if (i == j || fe[i].fx == fe[j].fx) continue;
            if (fe[i].fx == true)
            {
                if (fe[i].x > fe[j].x || fe[i].y < fe[j].y) continue;
                else if (abs (fe[i].x - fe[j].x) <= abs (fe[i].y - fe[j].y)) continue;
                else if (fe[i].y > wz[j].y) continue;
                else ans = min (ans, abs (fe[i].x - fe[j].x));
            }
            if (fe[i].fx == false)
            {
                if (fe[i].y > fe[j].y || fe[i].x < fe[j].x) continue;
                else if (abs (fe[i].x - fe[j].x) >= abs (fe[i].y - fe[j].y)) continue;
                else if (fe[i].x > wz[j].x) continue;
                else ans = min (ans, abs (fe[i].y - fe[j].y));
            }
        }
        if (ans == 1e9 + 10) cout << "Infinity" << endl;
        else cout << ans << endl;
    }
    return 0;
}
```
  - 作者：blankslpl (4星)
    - 关键亮点：详细解释排序的作用，通过两个不同的cmp函数排序，一个按$x + y$排序用于判断阻拦关系，另一个按$id$排序恢复初始顺序输出答案，思路新颖且清晰。
    - 重点代码核心实现思想：定义结构体存储奶牛信息，先按$x + y$排序，通过两层循环枚举奶牛，判断阻拦关系并记录移动方格数，最后按输入顺序输出答案。
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define _ read<int>()
template <class T>inline T read()
{
    T r=0,f=1;char c=getchar();
    while(!isdigit(c))
    {
        if(c=='-') f=-1;c=getchar();
    }
    while(isdigit(c)) r=(r<<1)+(r<<3)+(c^48),c=getchar();
    return f*r;
}
inline void out(int x)
{
    if(x<0) putchar('-'),x=-x;
    if(x<10) putchar(x+'0');
    else out(x/10),putchar(x%10+'0');
}
int inf=2e9;
struct fish
{
    long long id, x, y, z, d;//x,y是初始位置，d是走的方格数量 
    char fx;//方向 
}a[100];
int n; 
bool cmp1(fish m, fish n)//按行列坐标之和进行排序排序
{
    return m.z > n.z;
}
bool cmp2(fish m, fish n)//把顺序调整回输入时候的顺序 
{
    return m.id < n.id; 
}
signed main()
{
    n=_;
    for(int i=1;i<=n;i++)
    {
        int x,y;
        char c;
        cin>>c;//每头牛所在的x和y坐标不同 
        x=_,y=_;
        a[i]={i,x,y,x+y,inf,c};//无穷大 
    }
    sort(a+1,a+n+1,cmp1);
    for(int i=1;i<=n;i++)//遍历每一头牛 
    {
        for(int j=1;j<i;j++)//只有前面的点才有可能阻拦第i头牛
        {
            if(a[j].z == a[i].z || a[j].fx == a[i].fx) continue;//同一条斜线或者同一个方向的牛，肯定拦不住 
            if(a[i].fx == 'E' && a[j].fx == 'N')//i为向右的，j向上，然后找出最快拦住这条牛的步数 
            {
                if(a[i].y < a[j].y) continue;//i在j的下方，肯定拦不住 
                if(a[j].y+a[j].d > a[i].y) a[i].d = min(a[i].d, a[j].x-a[i].x);//j所在y加上移动步数如果大于i所在y，可以拦截 
            }
            else//i为向上，j为向右 
            {
                if(a[i].x < a[j].x) continue;//i在j的左方，肯定拦不住 
                if(a[j].x+a[j].d > a[i].x) a[i].d = min(a[i].d, a[j].y-a[i].y);//j所在x加上移动步数如果大于i所在x，可以拦截 
            }
        } 
    }
    sort(a+1,a+n+1,cmp2); 
    for(int i=1;i<=n;i++)
    {
        if(a[i].d==inf) puts("Infinity");
        else 
        {
            out(a[i].d);
            putchar('\n');
        }
    }
    return 0;
}
```

最优的关键思路或技巧：
    - **数据结构**：使用结构体存储奶牛的位置、方向及编号等信息，方便对奶牛数据进行管理和操作。
    - **算法优化**：通过对向北和向东的奶牛分别按合适的规则排序（如横坐标、纵坐标或横纵坐标之和），减少枚举奶牛对时不必要的比较，降低时间复杂度。在判断奶牛阻拦关系时，利用排序后的顺序，只考虑特定顺序的奶牛对（如前面的奶牛对后面奶牛的阻拦）。
    - **思维方式**：将奶牛的移动问题转化为射线交点问题，通过分析不同方向射线（奶牛移动轨迹）的交点以及奶牛到交点的距离，确定奶牛是否会被阻拦，简化问题求解过程。

可拓展之处：同类型题通常涉及物体在平面上的运动及相互影响，类似算法套路是先对物体按某种规则分类排序，再通过枚举不同类物体间的相互关系，利用距离、位置等条件判断相互影响结果。

推荐题目：
    - P1080 [NOIP2012 提高组] 国王游戏：涉及贪心算法，通过对数据排序后进行计算，与本题通过排序优化枚举过程类似。
    - P1199 [NOIP2010 普及组] 三国游戏：同样需要对数据进行分析和处理，通过合理的排序和枚举策略解决问题。
    - P1937 [USACO10MAR] Barn Allocation G：关于区间分配问题，与本题处理奶牛移动轨迹的交点问题类似，可通过排序和枚举解决。

个人心得摘录与总结：
    - FZY_CZY：赛上未做出该题，赛后经过思考得出正解，强调了赛后总结反思对提升能力的重要性。
    - ABCDEFG12345NM：起初因少考虑条件导致问题，经过改正虽然代码量翻倍但最终成功解决，提醒在解题时要全面分析题目条件，避免遗漏。 

---
处理用时：61.49秒