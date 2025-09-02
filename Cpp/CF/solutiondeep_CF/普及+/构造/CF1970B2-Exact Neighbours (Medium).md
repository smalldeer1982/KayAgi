# 题目信息

# Exact Neighbours (Medium)

## 题目描述

The only difference between this and the hard version is that $ a_{1} = 0 $ .

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

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1970B2/9f9f415b711c20a1d43262d4b959c18fec467842.png)

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

## 样例 #2

### 输入

```
4
0 1 3 1```

### 输出

```
YES
1 1
2 1
4 1
3 1
1 1 1 3```

# AI分析结果

### 题目内容中文重写
# 精确邻居（中等）

## 题目描述
本题与困难版本的唯一区别在于 $ a_{1} = 0 $。

在食死徒最近对霍格沃茨城堡发动几次袭击后，凤凰社决定在霍格莫德村安置 $ n $ 名成员。房屋将建在一个风景如画的 $ n\times n $ 正方形区域内。每位巫师都将拥有自己的房子，并且每栋房子都属于某位巫师。每栋房子将占据一个方格的空间。

然而，正如你所知，巫师们非常迷信。在周末，每位巫师 $ i $ 都想去距离自己房子恰好 $ a_{i} $ $ (0 \leq a_{i} \leq n) $ 远的房子。村庄里的道路是水平和垂直修建的，因此 $ n\times n $ 区域上点 $ (x_{i}, y_{i}) $ 和 $ (x_{j}, y_{j}) $ 之间的距离为 $  |x_{i} - x_{j}| + |y_{i} - y_{j}| $。巫师们相互了解并信任彼此，所以当第二位巫师不在家时，一位巫师可以去拜访另一位巫师的房子。要建造的房子足够大，所有 $ n $ 位巫师可以同时拜访任何一栋房子。

除此之外，每位巫师都被要求能看到北面的霍格沃茨城堡和南面的禁林，所以其他巫师的房子不能挡住视线。就村庄布局而言，这意味着在 $ n\times n $ 区域的每一列中，最多只能有一栋房子，即如果第 $ i $ 栋房子的坐标为 $ (x_{i}, y_{i}) $，那么对于所有 $ i \neq j $，都有 $ x_{i} \neq x_{j} $。

凤凰社还不知道是否有可能以满足所有 $ n $ 位巫师的拜访和视线要求的方式安置 $ n $ 栋房子，所以他们请求你帮忙设计这样一个方案。

如果有可能进行正确的安置，即对于第 $ i $ 位巫师，有一栋房子距离其房子为 $ a_{i} $，并且第 $ i $ 位巫师的房子是其所在列的唯一房子，则输出 `YES`、每位巫师房子的位置，以及每位巫师在周末应该去拜访哪位巫师的房子。

如果不可能进行正确的安置，则输出 `NO`。

## 说明/提示
对于样例，第一位巫师的房子位于 $ (4, 4) $，第二位位于 $ (1, 3) $，第三位位于 $ (2, 4) $，第四位位于 $ (3, 1) $。

第一位巫师的房子到第一位巫师的房子的距离为 $ |4 - 4| + |4 - 4| = 0 $。

第二位巫师的房子到第一位巫师的房子的距离为 $ |1 - 4| + |3 - 4| = 4 $。

第三位巫师的房子到第一位巫师的房子的距离为 $ |2 - 4| + |4 - 4| = 2 $。

第四位巫师的房子到第三位巫师的房子的距离为 $ |3 - 2| + |1 - 4| = 4 $。

所有房子的视线和距离条件都得到满足，所以这种安置是正确的。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1970B2/9f9f415b711c20a1d43262d4b959c18fec467842.png)

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

## 样例 #2

### 输入
```
4
0 1 3 1
```

### 输出
```
YES
1 1
2 1
4 1
3 1
1 1 1 3
```

### 综合分析与结论
- **思路对比**：三位作者思路本质相同，均利用 $a_1 = 0$ 的特性，从左到右按列构造房子位置。通过比较 $a_i$ 与 $i$ 的大小关系，确定当前房子的位置和目标房子。
- **算法要点**：以第一个房子为基础，根据 $a_i - i + 1$ 或 $a_i - i$ 的值来确定后续房子的坐标和目标房子。当该值为 0 时，房子在第 1 行；大于 0 时，房子向上移动；小于 0 时，找到距离合适的前面的房子并与其在同一行。
- **解决难点**：核心难点在于根据距离条件和每列仅一栋房子的限制，合理安排房子位置。三位作者均通过分类讨论解决了该问题。

### 所选题解
- **作者：0tAp（5星）**
    - **关键亮点**：思路清晰，代码注释详细，逻辑表达明确，便于理解。
    - **核心代码**：
```cpp
void solve(){
    int n;
    scanf("%d",&n);
    vector<int>a(n+10),x(n+10),y(n+10),ans(n+10);
    rep(i,1,n)scanf("%d",&a[i]);
    if(a[1]){cout<<"NO";return;}
    x[1]=1,y[1]=1;
    ans[1]=1;
    rep(i,2,n){
        if(!a[i]){x[i]=i,y[i]=1,ans[i]=i;continue;}
        int now=a[i]-i+1;
        if(now==0){x[i]=i,y[i]=1;ans[i]=1;continue;}
        if(now>0){x[i]=i,y[i]=now+1;ans[i]=1;continue;}
        else{x[i]=i,y[i]=y[-now+1],ans[i]=-now+1;continue;}
    }
    puts("YES");
    rep(i,1,n)printf("%d %d\n",x[i],y[i]);
    rep(i,1,n)printf("%d ",ans[i]);return;
}
```
    - **核心实现思想**：先处理第一个房子，将其放在 $(1, 1)$ 位置。然后从第二个房子开始，根据 $a[i] - i + 1$ 的值分情况讨论，确定当前房子的坐标 $(x[i], y[i])$ 和目标房子编号 $ans[i]$。

### 最优关键思路或技巧
- **利用特殊条件**：利用 $a_1 = 0$ 的条件，将第一个房子固定在 $(1, 1)$ 位置，以此为基础构造其他房子的位置。
- **分类讨论**：通过比较 $a_i$ 与 $i$ 的大小关系，分情况确定房子的位置和目标房子，简化问题求解。

### 可拓展之处
同类型题目可能会改变地图形状、距离计算方式或增加其他限制条件。类似算法套路是利用特殊条件作为突破口，通过分类讨论逐步构造满足条件的解。

### 推荐题目
- [P1003 铺地毯](https://www.luogu.com.cn/problem/P1003)：涉及坐标和位置的构造问题。
- [P1047 校门外的树](https://www.luogu.com.cn/problem/P1047)：需要考虑区间和位置的关系。
- [P1059 明明的随机数](https://www.luogu.com.cn/problem/P1059)：可锻炼分类处理数据的能力。

### 个人心得
题解中未包含个人心得。 

---
处理用时：38.41秒