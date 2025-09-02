# 题目信息

# Napoleon Cake

## 题目描述

This week Arkady wanted to cook some pancakes (to follow ancient traditions) and make a problem about that. But then he remembered that one can't make a problem about stacking pancakes without working at a specific IT company, so he decided to bake the Napoleon cake instead.

To bake a Napoleon cake, one has to bake $ n $ dry layers first, and then put them on each other in one stack, adding some cream. Arkady started with an empty plate, and performed the following steps $ n $ times:

- place a new cake layer on the top of the stack;
- after the $ i $ -th layer is placed, pour $ a_i $ units of cream on top of the stack.

When $ x $ units of cream are poured on the top of the stack, top $ x $ layers of the cake get drenched in the cream. If there are less than $ x $ layers, all layers get drenched and the rest of the cream is wasted. If $ x = 0 $ , no layer gets drenched.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1501B/d2a848de33f21319239069b9694ee652ecb320b0.png)The picture represents the first test case of the example.Help Arkady determine which layers of the cake eventually get drenched when the process is over, and which don't.

## 样例 #1

### 输入

```
3
6
0 3 0 0 1 3
10
0 0 0 1 0 5 0 0 0 2
3
0 0 0```

### 输出

```
1 1 0 1 1 1 
0 1 1 1 1 1 0 0 1 1 
0 0 0```

# AI分析结果

### 题目内容
# 拿破仑蛋糕

## 题目描述
这周，阿尔卡季想做些煎饼（遵循古老传统）并以此出一道题。但随后他想起，如果不在特定的 IT 公司工作，就没法出一道关于堆叠煎饼的题目，所以他决定改为烤制拿破仑蛋糕。

要烤制一个拿破仑蛋糕，首先必须烤制 $n$ 层干面饼，然后将它们叠放在一起形成一个堆叠，并加入一些奶油。阿尔卡季从一个空盘子开始，执行以下步骤 $n$ 次：
- 将一个新的蛋糕层放在堆叠的顶部；
- 在放置第 $i$ 层之后，在堆叠顶部倒入 $a_i$ 单位的奶油。

当在堆叠顶部倒入 $x$ 单位的奶油时，蛋糕的顶部 $x$ 层会被奶油浸湿。如果层数少于 $x$ 层，所有层都会被浸湿，其余的奶油会被浪费。如果 $x = 0$，则没有层会被浸湿。

![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1501B/d2a848de33f21319239069b9694ee652ecb320b0.png)
该图片展示了示例中的第一个测试用例。
帮助阿尔卡季确定在这个过程结束时，蛋糕的哪些层最终会被浸湿，哪些不会。

## 样例 #1
### 输入
```
3
6
0 3 0 0 1 3
10
0 0 0 1 0 5 0 0 0 2
3
0 0 0
```
### 输出
```
1 1 0 1 1 1 
0 1 1 1 1 1 0 0 1 1 
0 0 0
```

### 算法分类
差分

### 题解综合分析与结论
- **思路**：多数题解采用差分的思路，通过对每次倒入奶油所影响的区间进行差分标记，最后通过前缀和还原得到每层是否被浸湿的结果。部分题解采用倒序模拟的方式，从后往前遍历，根据每层倒入的奶油量更新能浸湿的层数，从而判断每层是否被浸湿。
- **算法要点**：差分法要点在于明确每次操作影响的区间，对区间起点增加标记，区间终点后一位减少标记；倒序模拟则需记录当前剩余可浸湿层数，并动态更新。
- **解决难点**：难点在于避免暴力解法的超时问题，通过合理运用差分或倒序模拟优化时间复杂度。暴力解法时间复杂度为 $O(n^2)$，而差分和倒序模拟的时间复杂度为 $O(n)$。

### 所选的题解
#### 作者：Silence_water（5星）
- **关键亮点**：思路清晰，对题意简化准确，直接采用差分算法求解，代码简洁明了，逻辑严谨。
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int M=2e5+5;
int T,n,a[M];
ll p[M];
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        memset(p,0,sizeof(p));
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
        {
            scanf("%d",&a[i]);
            int pre=max(i-a[i]+1,1);
            p[pre]++,p[i+1]--;
        }
        for(int i=1;i<=n;i++)
        {
            p[i]+=p[i-1];
            if(p[i])printf("1 ");
            else printf("0 ");
        }
        printf("\n");
    }
    return 0;
}
```
核心实现思想：利用差分数组 `p` 记录每层的变化量，根据每层倒入奶油量确定影响区间，对区间起点和终点后一位进行标记，最后通过前缀和得到每层是否被浸湿。

#### 作者：Daidly（4星）
- **关键亮点**：采用倒序模拟的方法，思路独特，代码简单易懂，能有效避免暴力解法的超时问题。
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[200005],b[200005],tmp;
int main(){
    cin>>t;
    while(t--){
        cin>>n;tmp=0;
        for(int i=1;i<=n;++i)cin>>a[i],b[i]=0;
        for(int i=n;i>=1;--i){
            tmp=max(tmp,a[i]);
            if(tmp>0){
                b[i]=1;
                tmp--;
            }
        }
        for(int i=1;i<=n;++i)cout<<b[i]<<" ";
        cout<<endl;
    }
    return 0;
}
```
核心实现思想：从后往前遍历每层，用 `tmp` 记录剩余可浸湿层数，根据每层奶油量更新 `tmp`，并判断当前层是否被浸湿。

#### 作者：EuphoricStar（4星）
- **关键亮点**：明确指出是差分模板题，对差分思路解释清晰，代码规范，易于理解。
```cpp
#include <bits/stdc++.h>
using namespace std;

int t, n, ans[200100], a[200100];

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i) {
            ans[i] = 0;
        }
        for (int i = 1; i <= n; ++i) {
            int x;
            scanf("%d", &x);
            ++ans[max(1, i - x + 1)];
            --ans[i + 1];
        }
        for (int i = 1; i <= n; ++i) {
            a[i] = a[i - 1] + ans[i];
            printf("%d ", a[i] > 0);
        }
        putchar('\n');
    }
    return 0;
}
```
核心实现思想：与其他差分法类似，利用 `ans` 数组记录每层变化量，通过对每层倒入奶油影响区间的标记，最后通过前缀和判断每层是否被浸湿。

### 最优关键思路或技巧
差分算法是本题最优解法，通过对区间操作的巧妙标记，将 $O(n^2)$ 的暴力区间修改优化为 $O(n)$ 的时间复杂度。利用差分数组记录区间变化，最后通过前缀和还原结果，有效避免了重复计算，提高了效率。

### 可拓展之处
同类型题目常涉及区间修改与查询问题，类似算法套路如树状数组也可解决此类问题，但差分更适用于简单的区间修改后求最终状态的场景。树状数组则在支持区间修改和单点查询上更具优势。

### 洛谷推荐题目
- [P1083 借教室](https://www.luogu.com.cn/problem/P1083)：同样是区间修改问题，可通过差分求解。
- [P3372 【模板】线段树 1](https://www.luogu.com.cn/problem/P3372)：涉及区间修改和查询，可与差分算法对比学习。
- [P1972 [SDOI2009]HH的项链](https://www.luogu.com.cn/problem/P1972)：通过离散化和前缀和思想解决问题，与本题差分思想有一定关联。 

---
处理用时：67.08秒