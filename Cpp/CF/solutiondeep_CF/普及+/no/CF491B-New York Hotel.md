# 题目信息

# New York Hotel

## 题目描述

Think of New York as a rectangular grid consisting of $ N $ vertical avenues numerated from $ 1 $ to $ N $ and $ M $ horizontal streets numerated $ 1 $ to $ M $ . $ C $ friends are staying at $ C $ hotels located at some street-avenue crossings. They are going to celebrate birthday of one of them in the one of $ H $ restaurants also located at some street-avenue crossings. They also want that the maximum distance covered by one of them while traveling to the restaurant to be minimum possible. Help friends choose optimal restaurant for a celebration.

Suppose that the distance between neighboring crossings are all the same equal to one kilometer.

## 样例 #1

### 输入

```
10 10
2
1 1
3 3
2
1 10
4 4
```

### 输出

```
6
2
```

# AI分析结果

### 题目内容
# 纽约酒店

## 题目描述
将纽约想象成一个矩形网格，由从1到N编号的N条垂直大道和从1到M编号的M条水平街道组成。C个朋友住在位于某些街道与大道交叉点的C家酒店里。他们打算在位于某些街道与大道交叉点的H家餐厅中的一家，庆祝其中一人的生日。他们还希望在前往餐厅时，其中一人所走的最大距离尽可能小。请帮助朋友们选择最佳的庆祝餐厅。

假设相邻交叉点之间的距离都相同，均为一公里。

## 样例 #1
### 输入
```
10 10
2
1 1
3 3
2
1 10
4 4
```
### 输出
```
6
2
```
### 算法分类
数学

### 综合分析与结论
这些题解主要围绕如何找到使与餐馆最远的酒店离它最近的餐馆这一核心问题展开。多数题解思路基于曼哈顿距离特性，即对于每个餐馆，离它最远的酒店大概率在其四个角落方向（左上方、右上方、左下方、右下方）。
1. **思路**：多数题解先找出酒店四个角落方向的代表酒店（通过坐标运算确定，如计算x + y、x - y等的最值），再遍历餐馆计算到这些代表酒店的距离并取最值，最终找出满足条件的餐馆。部分题解还涉及曼哈顿距离与切比雪夫距离的转化，或采用二分查找判断是否存在满足最大距离限制的餐馆。
2. **算法要点**：利用曼哈顿距离公式，通过坐标组合运算找出关键酒店坐标，遍历餐馆计算距离并更新最值。
3. **解决难点**：证明并确定距离餐馆最远的酒店在四个角落方向，以及如何高效计算并比较距离。

### 所选的题解
#### EternalHeart1314（5星）
- **关键亮点**：思路清晰，直接点明对于每个餐馆，离它最远的酒店在四个角落方向，通过记录四个角的酒店坐标特征（x + y、x - y等的最值），遍历餐馆计算距离并更新最小值和餐馆编号，代码简洁明了。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

int n, m, c, h, x, y, mi = 1e18, id, mx1 = -1e18, mx2 = -1e18, mx3 = -1e18, mx4 = -1e18;

signed main() {
    cin >> n >> m >> c;
    for(int i = 1; i <= c; i++) {
        cin >> x >> y;
        mx1 = max(mx1, x + y);
        mx2 = max(mx2, x - y);
        mx3 = max(mx3, y - x);
        mx4 = max(mx4, -x - y);
    }
    cin >> h;
    for(int i = 1; i <= h; i++) {
        cin >> x >> y;
        if(max({mx1 - x - y, mx2 - x + y, mx3 - y + x, mx4 + x + y}) < mi) {
            mi = max({mx1 - x - y, mx2 - x + y, mx3 - y + x, mx4 + x + y});
            id = i;
        }
    }
    cout << mi << endl << id << endl;
    return 0;
}
```
核心实现思想：先遍历酒店记录四个角酒店的坐标特征值（mx1 - mx4），再遍历餐馆，通过坐标运算判断餐馆到四个角酒店的距离，取最大值并与当前最小值比较，更新最小值和对应餐馆编号。

#### gcwixsxr（4星）
- **关键亮点**：先深入研究曼哈顿距离的分类讨论，明确距离公式在不同条件下的形式，再基于此记录酒店中x + y、x - y的最值，遍历餐馆计算到可能最远点的距离并取最值，思路严谨，代码实现清晰。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int inf=0x7fffffff;
int amax=-inf,bmax=-inf,amin=inf,bmin=inf;
int n,m,c,h;
int ans=inf,bestid; 
signed main(){
    cin>>n>>m;
    cin>>c;
    for(int i=1;i<=c;i++){
        int x,y;
        cin>>x>>y;
        amax=max(amax,x+y);
        amin=min(amin,x+y);
        bmax=max(bmax,x-y);
        bmin=min(bmin,x-y);
    }
    cin>>h;
    for(int i=1;i<=h;i++){
        int x,y;
        cin>>x>>y;
        int temp=0;
        temp=max(temp,max(abs(amin-(x+y)),abs(amax-(x+y))));
        temp=max(temp,max(abs(bmin-(x-y)),abs(bmax-(x-y))));
        if(ans>temp){
            ans=temp;
            bestid=i;
        }
    }
    cout<<ans<<endl<<bestid<<endl;
    return 0;
}
```
核心实现思想：先遍历酒店记录x + y、x - y的最值（amax、amin、bmax、bmin），再遍历餐馆，通过绝对值运算计算餐馆到可能最远点的距离，取最大值并与当前最小值比较，更新最小值和对应餐馆编号。

#### Barewalk（4星）
- **关键亮点**：提出将曼哈顿距离转化为切比雪夫距离的新思路，通过证明引理，将问题转化为求两个点集在新坐标系下的切比雪夫距离，进而通过找出点集横纵坐标的最值来解决问题，方法新颖，代码简洁高效。
```cpp
#include <algorithm>
#include <cstring>
#include <iostream>
#define maxN 100100
#define pii pair<int, int>
using ll = long long;
constexpr int inf = 0x7f7f7f7f, mod = 1e9 + 7;
using namespace std;
int n, m, c, h, ans = inf, id;
int minX = inf, maxX = -inf, minY = inf, maxY = -inf;
int max(int a, int b, int c, int d) {
    return max(max(a, b), max(c, d));
}
int main() {
    cin.tie(nullptr) -> sync_with_stdio(false);
    cin >> n >> m;
    cin >> c;
    for (int i = 1; i <= c; ++ i) {
        int a, b, x, y;
        cin >> a >> b;
        x = a + b, y = a - b;
        minX = min(minX, x), maxX = max(maxX, x);
        minY = min(minY, y), maxY = max(maxY, y);
    }
    cin >> h;
    for (int i = 1; i <= h; ++ i) {
        int a, b, x, y;
        cin >> a >> b;
        x = a + b, y = a - b;
        int s = max(abs(x - minX), abs(x - maxX), abs(y - maxY), abs(y - minY));
        if (s < ans) {
            ans = s, id = i;
        }
    }
    cout << ans << '\n' << id << '\n';
    return 0;
}
```
核心实现思想：先遍历酒店将坐标转化为新坐标系下的坐标并记录横纵坐标最值（minX、maxX、minY、maxY），再遍历餐馆转化坐标，计算到最值点的距离取最大值，与当前最小值比较更新最小值和对应餐馆编号。

### 最优关键思路或技巧
1. **利用曼哈顿距离特性**：通过分析曼哈顿距离在不同位置关系下的公式，确定距离餐馆最远的酒店大概率在四个角落方向，从而通过记录酒店坐标的特定组合（如x + y、x - y）的最值，简化距离计算。
2. **距离转化**：如将曼哈顿距离转化为切比雪夫距离，从新的角度看待问题，简化计算过程。

### 可拓展之处
同类型题常围绕曼哈顿距离、切比雪夫距离的特性展开，可能涉及点集间距离计算、位置优化等问题。类似算法套路包括利用坐标运算找出关键位置点，通过遍历比较距离来优化结果。

### 洛谷相似题目推荐
1. **P1452 城市环路**：涉及城市道路节点距离计算，可运用曼哈顿距离相关知识。
2. **P3964 [TJOI2013] 松鼠聚会**：同样是关于点集间距离优化问题，与本题思路类似。
3. **P1047 [NOIP2005 普及组] 校门外的树**：虽然形式不同，但核心也是通过坐标关系解决位置相关问题，可类比本题思路。 

---
处理用时：63.53秒