# 题目信息

# [USACO16OPEN] Field Reduction S

## 题目描述

Farmer John 的 $N$ 头奶牛（$5 \leq N \leq 50,000$）都位于他二维牧场中的不同位置。FJ 希望用一个边平行于 $x$ 轴和 $y$ 轴的矩形围栏围住所有的奶牛，并且他希望这个围栏尽可能小，以便能够包含每头奶牛（允许奶牛位于边界上）。

不幸的是，由于上个季度牛奶产量低，FJ 的预算非常紧张。因此，他希望如果可能的话，建造一个更小的围栏，并且他愿意从他的牛群中出售最多三头奶牛来实现这一目标。

请帮助 FJ 计算在从他的牛群中移除最多三头奶牛后，他可以用围栏围住的最小可能面积（然后为剩余的奶牛建造最紧密的围栏）。

对于这个问题，请将奶牛视为点，将围栏视为四条线段的集合（即不要将奶牛视为“单位正方形”）。请注意，答案可能为零，例如如果所有剩余的奶牛最终站在一条共同的垂直线或水平线上。

## 样例 #1

### 输入

```
6
1 1
7 8
10 9
8 12
4 100
50 7```

### 输出

```
12```

# AI分析结果

• 综合分析与结论：所有题解均基于暴力枚举思路，利用“最多卖三头牛”这一条件，通过枚举删除横、纵坐标最大或最小的牛来计算最小矩形面积。主要差异在于实现细节，如去重方式、枚举方式及代码组织。
- 思路：均考虑删除位于最外圈的牛，通过枚举删除的牛来计算剩余牛形成的最小矩形面积，矩形面积通过计算横纵坐标的最值差相乘得到。
- 算法要点：对牛的坐标按横、纵坐标分别排序，找出横、纵坐标最大和最小的若干头牛（通常是3 - 4头），然后通过循环或DFS等方式枚举删除三头牛的所有组合，计算每种组合下剩余牛的矩形面积并取最小值。
- 解决难点：处理可能出现的重复点问题，避免重复计算；准确设定无穷大值以防止结果溢出。

以下是各题解评分：
1. **作者：Unordered_OIer**：3星。思路清晰，详细解释了暴力枚举的思路及注意事项，但代码实现稍显复杂，可读性一般。
2. **作者：ikunTLE**：3星。思路简洁明了，但代码未给出，对新手理解实现细节有困难。
3. **作者：Zenith_Yeh**：3星。详细阐述暴力枚举步骤，代码实现完整，但整体表述稍显繁琐。
4. **作者：Violet___Evergarden**：4星。思路清晰，通过预先记录横、纵坐标最大和最小的12头牛编号，减少枚举范围，并详细说明了手算枚举的注意点，代码简洁易懂。
5. **作者：mysterys**：3星。思路和时间复杂度分析清晰，代码实现了去重等操作，但整体代码结构相对复杂。
6. **作者：Victorique**：3星。提出暴力枚举思路并注意到重复点问题，但代码实现采用DFS，逻辑较复杂，可读性欠佳。
7. **作者：Orion_Rigel**：3星。思路简单直接，但代码通过位运算枚举，对初学者不太友好，且未详细说明思路。
8. **作者：D23lhc**：3星。分析了取点方式，但代码实现中对边界情况处理及整体逻辑稍显混乱。
9. **作者：羚羊WANG**：3星。采用搜索方式枚举删除的牛，思路较清晰，但代码实现细节较多，可读性一般。
10. **作者：Andy1101**：3星。思路清晰，代码实现完整，但对unique函数使用说明较突兀，整体表述常规。
11. **作者：zmnjkl**：3星。详细描述思路，但代码实现中DFS部分逻辑复杂，且对重复点处理代码冗长。

所选4星及以上题解：
- **作者：Violet___Evergarden**：4星。
  - 关键亮点：预先记录横、纵坐标最大和最小的12头牛编号，缩小枚举范围；手算枚举各种删除组合，逻辑清晰，代码简洁明了。
  - 个人心得：无。
  - 核心代码：
```cpp
#include<bits/stdc++.h>
#include<algorithm>
#define int long long
#define RE register
#define IN inline
using namespace std;
const int kMaxN=5e4+1;
int n,ans=LLONG_MAX;
int maxx[4],minx[4],maxy[4],miny[4];
struct COW
{
  int x,y;
  int num;
}cow[kMaxN];
bool cmp1(COW i,COW j)
{
  if(i.x!=j.x)return i.x<j.x;
  return i.y<j.y;
}
bool cmp2(COW i,COW j)
{
  if(i.y!=j.y)return i.y<j.y;
  return i.x<j.x;
}
IN void solve(int a,int b,int c)
{
  int maxx=-1,minx=LLONG_MAX,maxy=-1,miny=LLONG_MAX;
  for(RE int i=1;i<=n;i++)
  {
    if(cow[i].num==a||cow[i].num==b||cow[i].num==c)continue;
    maxx=max(maxx,cow[i].x);
    minx=min(minx,cow[i].x);
    maxy=max(maxy,cow[i].y);
    miny=min(miny,cow[i].y);
  }
  ans=min(ans,(maxx-minx)*(maxy-miny));
}
signed main()
{
cin>>n;
for(RE int i=1;i<=n;++i)
{
  cin>>cow[i].x>>cow[i].y;
  cow[i].num=i;
}
sort(cow+1,cow+n+1,cmp1);
maxx[1]=cow[n].num;
maxx[2]=cow[n-1].num;
maxx[3]=cow[n-2].num;
minx[1]=cow[1].num;
minx[2]=cow[2].num;
minx[3]=cow[3].num;
sort(cow+1,cow+n+1,cmp2);
maxy[1]=cow[n].num;
maxy[2]=cow[n-1].num;
maxy[3]=cow[n-2].num;
miny[1]=cow[1].num;
miny[2]=cow[2].num;
miny[3]=cow[3].num;
solve(maxx[1],maxx[2],maxx[3]);
solve(maxx[1],maxx[2],minx[1]);
solve(maxx[1],minx[1],minx[2]);
solve(minx[1],minx[2],minx[3]);
solve(maxx[1],maxy[1],maxy[2]);
solve(maxx[1],maxy[1],miny[1]);
solve(maxx[1],miny[1],miny[2]);
solve(maxx[1],maxx[2],maxy[1]);
solve(maxx[1],maxx[2],miny[1]);
solve(maxx[1],minx[1],maxy[1]);
solve(maxx[1],minx[1],miny[1]);
solve(minx[1],maxy[1],maxy[2]);
solve(minx[1],maxy[1],miny[1]);
solve(minx[1],miny[1],miny[2]);
solve(minx[1],minx[2],maxy[1]);
solve(minx[1],minx[2],miny[1]);
solve(maxy[1],maxy[2],maxy[3]);
solve(maxy[1],maxy[2],miny[1]);
solve(maxy[1],miny[1],miny[2]);
solve(miny[1],miny[2],miny[3]);
cout<<ans;
return 0;
}
```
核心实现思想：先按横、纵坐标分别排序，记录横、纵坐标最大和最小的牛的编号，然后通过手算枚举删除三头牛的所有组合，调用solve函数计算每种组合下剩余牛形成的矩形面积，取最小值。

最优关键思路或技巧：提前筛选出可能影响结果的边界点（横、纵坐标最大和最小的点），缩小枚举范围，减少计算量；在枚举过程中，根据几何性质合理排除不可能影响结果的点组合，如未选择横坐标最大点时，不会选择次大、第三大的横坐标点。

可拓展之处：此类问题可拓展到更高维度或限制删除更多点的情况，思路上依然是通过分析几何性质确定关键影响点，然后进行枚举计算。类似算法套路是对数据进行预处理，找出关键数据子集，减少暴力枚举范围。

推荐洛谷题目：
1. P1157 组合的输出：通过DFS枚举组合，与本题枚举删除点思路类似。
2. P1036 [NOIP2002 普及组] 选数：同样是通过枚举不同数字组合来求解问题，锻炼枚举类问题的思维。
3. P2241 统计方形（数据加强版）：通过枚举矩形的边界来统计满足条件的矩形数量，与本题确定矩形边界计算面积思路有相通之处。

个人心得摘录与总结：
- **作者：Unordered_OIer**：设无穷大值时要精确，因本题面积计算可能导致值较大，设2e10可避免结果溢出问题。总结为在处理涉及较大数值计算时，要合理预估结果范围，准确设定边界值。 

---
处理用时：40.67秒