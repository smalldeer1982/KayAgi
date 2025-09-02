# 题目信息

# Exact Neighbours (Easy)

## 题目描述

The only difference between this and the hard version is that all $ a_{i} $ are even.

After some recent attacks on Hogwarts Castle by the Death Eaters, the Order of the Phoenix has decided to station $ n $ members in Hogsmead Village. The houses will be situated on a picturesque $ n\times n $ square field. Each wizard will have their own house, and every house will belong to some wizard. Each house will take up the space of one square.

However, as you might know wizards are very superstitious. During the weekends, each wizard $ i $ will want to visit the house that is exactly $ a_{i} $ $ (0 \leq a_{i} \leq n) $ away from their own house. The roads in the village are built horizontally and vertically, so the distance between points $ (x_{i}, y_{i}) $ and $ (x_{j}, y_{j}) $ on the $ n\times n $ field is $  |x_{i} - x_{j}| + |y_{i} - y_{j}| $ . The wizards know and trust each other, so one wizard can visit another wizard's house when the second wizard is away. The houses to be built will be big enough for all $ n $ wizards to simultaneously visit any house.

Apart from that, each wizard is mandated to have a view of the Hogwarts Castle in the north and the Forbidden Forest in the south, so the house of no other wizard should block the view. In terms of the village, it means that in each column of the $ n\times n $ field, there can be at most one house, i.e. if the $ i $ -th house has coordinates $ (x_{i}, y_{i}) $ , then $ x_{i} \neq x_{j} $ for all $ i \neq j $ .

The Order of the Phoenix doesn't yet know if it is possible to place $ n $ houses in such a way that will satisfy the visit and view requirements of all $ n $ wizards, so they are asking for your help in designing such a plan.

If it is possible to have a correct placement, where for the $ i $ -th wizard there is a house that is $ a_{i} $ away from it and the house of the $ i $ -th wizard is the only house in their column, output YES, the position of houses for each wizard, and to the house of which wizard should each wizard go during the weekends.

If it is impossible to have a correct placement, output NO.

## 说明/提示

For the sample, the house of the 1st wizard is located at $ (4, 4) $ , of the 2nd at $ (1, 3) $ , of the 3rd at $ (2, 4) $ , of the 4th at $ (3, 1) $ .

The distance from the house of the 1st wizard to the house of the 1st wizard is $ |4 - 4| + |4 - 4| = 0 $ .

The distance from the house of the 2nd wizard to the house of the 1st wizard is $ |1 - 4| + |3 - 4| = 4 $ .

The distance from the house of the 3rd wizard to the house of the 1st wizard is $ |2 - 4| + |4 - 4| = 2 $ .

The distance from the house of the 4th wizard to the house of the 3rd wizard is $ |3 - 2| + |1 - 4| = 4 $ .

The view and the distance conditions are satisfied for all houses, so the placement is correct.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1970B1/9f9f415b711c20a1d43262d4b959c18fec467842.png)

## 样例 #1

### 输入

```
4
0 4 2 4```

### 输出

```
YES
4 4
1 3
2 4
3 1
1 1 1 3```

# AI分析结果

### 题目中文重写
# 精确邻居（简单版）

## 题目描述
本题与困难版的唯一区别在于所有的 $a_{i}$ 都是偶数。

在食死徒最近对霍格沃茨城堡发动几次袭击后，凤凰社决定在霍格莫德村派驻 $n$ 名成员。房屋将建在一个风景如画的 $n\times n$ 正方形区域上。每位巫师都将拥有自己的房子，并且每所房子都属于某一位巫师。每所房子将占据一个方格的空间。

然而，正如你可能知道的，巫师们非常迷信。在周末，每位巫师 $i$ 都想去距离自己房子恰好 $a_{i}$ $(0 \leq a_{i} \leq n)$ 远的房子拜访。村庄里的道路是水平和垂直修建的，因此在 $n\times n$ 区域上，点 $(x_{i}, y_{i})$ 和点 $(x_{j}, y_{j})$ 之间的距离为 $|x_{i} - x_{j}| + |y_{i} - y_{j}|$。巫师们相互了解并信任彼此，所以当第二位巫师不在家时，一位巫师可以去拜访另一位巫师的房子。要建造的房子足够大，能让所有 $n$ 位巫师同时拜访任何一所房子。

除此之外，每位巫师都被要求能看到北面的霍格沃茨城堡和南面的禁林，所以其他巫师的房子不能挡住视线。就村庄布局而言，这意味着在 $n\times n$ 区域的每一列中，最多只能有一所房子，即如果第 $i$ 所房子的坐标为 $(x_{i}, y_{i})$，那么对于所有 $i \neq j$，都有 $x_{i} \neq x_{j}$。

凤凰社还不知道是否有可能以满足所有 $n$ 位巫师拜访和视线要求的方式安置 $n$ 所房子，所以他们请求你帮忙设计这样一个方案。

如果有可能进行正确的安置，即对于第 $i$ 位巫师，有一所房子距离其房子为 $a_{i}$，并且第 $i$ 位巫师的房子是其所在列的唯一房子，则输出 `YES`，以及每位巫师房子的位置，还有每位巫师在周末应该去拜访哪位巫师的房子。

如果不可能进行正确的安置，则输出 `NO`。

## 说明/提示
对于样例，第一位巫师的房子位于 $(4, 4)$，第二位位于 $(1, 3)$，第三位位于 $(2, 4)$，第四位位于 $(3, 1)$。

第一位巫师的房子到第一位巫师的房子的距离为 $|4 - 4| + |4 - 4| = 0$。

第二位巫师的房子到第一位巫师的房子的距离为 $|1 - 4| + |3 - 4| = 4$。

第三位巫师的房子到第一位巫师的房子的距离为 $|2 - 4| + |4 - 4| = 2$。

第四位巫师的房子到第三位巫师的房子的距离为 $|3 - 2| + |1 - 4| = 4$。

所有房子的视线和距离条件都得到满足，所以这种安置是正确的。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1970B1/9f9f415b711c20a1d43262d4b959c18fec467842.png)

## 样例 #1

### 输入
```
4
0 4 2 4
```

### 输出
```
YES
4 4
1 3
2 4
3 1
1 1 1 3
```

### 综合分析与结论
- **思路**：各题解思路基本一致，由于所有的 $a_i$ 都是偶数，将所有房子放置在对角线上，能保证每列只有一个房子且房子间距离为偶数，满足视线和距离要求。
- **算法要点**：先输出 `YES`，接着输出对角线上房子的坐标 `(i, i)`，最后根据 $a_i$ 计算每位巫师要拜访的房子编号，通过 $a_i/2$ 与当前房子编号相加减，并判断是否越界。
- **解决难点**：主要难点在于处理距离计算时的越界情况，各题解通过判断 $i - a_i/2$ 是否大于等于 1 或 $i + a_i/2$ 是否小于等于 $n$ 来解决。

### 题解评分
- **ikunTLE**：4星。思路清晰，有图示辅助理解，但未给出代码。
- **JOE_ZengYuQiao_0928**：4星。思路清晰，代码简洁，使用了 `ios::sync_with_stdio(0)` 优化输入输出。
- **Tjl0427**：3星。思路正确，但代码注释较少，仅提醒数组要开大。
- **JYX0924**：3星。思路明确，代码实现基本正确，但未对越界判断的逻辑进行详细说明。
- **zjzx_wcj**：3星。使用 Python 实现，思路与其他题解一致，但代码中 `range(1, n + 1)` 结合 `a[i - 1]` 容易混淆。
- **Dream_Mr_li**：3星。思路正确，但代码中房子坐标输出顺序为倒序，未作必要说明。

### 所选题解
- **ikunTLE**：4星。关键亮点是通过图示清晰展示将房子放置在对角线上的思路。
- **JOE_ZengYuQiao_0928**：4星。关键亮点是代码简洁，使用 `ios::sync_with_stdio(0)` 优化输入输出。核心代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,a[200005]; 
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    cout<<"YES\n";
    for(int i=1;i<=n;i++)cout<<i<<" "<<i<<"\n";
    for(int i=1;i<=n;i++){
        if(i-a[i]/2>=1)cout<<i-a[i]/2<<" ";
        else cout<<i+a[i]/2<<" ";
    }
    return 0;
}
```
核心实现思想：先读取输入，输出 `YES`，再输出对角线上房子的坐标，最后根据 $a_i$ 计算并输出每位巫师要拜访的房子编号，处理越界情况。

### 最优关键思路或技巧
- **思维方式**：利用 $a_i$ 为偶数的条件，将房子放置在对角线上简化问题。
- **代码实现技巧**：通过 $a_i/2$ 与房子编号相加减处理距离计算，同时判断越界。

### 可拓展之处
同类型题可能会改变房子距离的计算方式、增加其他限制条件（如房子不能相邻等）。类似算法套路是通过分析题目条件找到一种满足所有条件的构造方式。

### 推荐题目
- [P1003 铺地毯](https://www.luogu.com.cn/problem/P1003)
- [P1047 校门外的树](https://www.luogu.com.cn/problem/P1047)
- [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)

### 个人心得
题解中未包含个人心得。 

---
处理用时：41.27秒