# 题目信息

# [USACO21DEC] Bracelet Crossings G

## 题目描述

奶牛 Bessie 喜欢手工艺。在她的空闲时间，她制作了 $N$（$1\le N\le 50$）个手链，编号为 $1 \ldots N$。第 $i$ 个手链涂有颜色 $i$，是 $N$ 种不同的颜色之一。制作完手链后，Bessie 将它们放在桌子上进行展示（我们可以将其视为二维平面）。她精心布置这些手链，以满足以下三个条件：

- 每个手链是一个简单闭合折线——一组顶点（点）依次用线段连接，并且第一个点和最后一个点相同（欢迎查阅维基百科页面了解更多详情：[Polygonal_chain](https://en.wikipedia.org/wiki/Polygonal_chain)，或百度百科：[折线](https://baike.baidu.com/item/%E6%8A%98%E7%BA%BF/486302)），

- 没有手链与自身相交（这对应「简单」折线）；

- 以及没有两条手链相交。

不幸的是，就在 Bessie 如此小心翼翼地布置好手链之后，Farmer John 开着拖拉机经过，桌子晃动起来，导致手链四处移动甚至可能断成了多个（不一定是闭合的或简单的）折线！在那之后，Bessie 还是想检查以上三个条件是否仍然成立。然而，天色已暗，她现在无法看清手链。

幸好 Bessie 有一个手电筒。她选择了 $M$（$1\le M\le 50$）条垂直线 $x=1, x=2, \ldots, x=M$，并且对于每条线，她用手电筒的光沿着那条线从 $y=-\infty$ 扫至 $y=\infty$，按照出现的顺序记录她看到的所有手链的颜色。幸运的是，没有光束穿过任何折线的顶点或同时穿过两条线段。此外，对于每一束光，所有出现的颜色都恰好出现了两次。

你能帮助 Bessie 使用此信息来确定手链是否仍然满足上述所有三个条件吗？

## 说明/提示

【样例解释】

对于第一个子测试用例，一组可行的手链位置为：

![](https://cdn.luogu.com.cn/upload/image_hosting/q3mohld2.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

对于第四个子测试用例，一组可行的手链位置为：

![](https://cdn.luogu.com.cn/upload/image_hosting/8m2hcgbb.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

【数据范围】

- 测试点 2 满足 $N = 1$。
- 测试点 3-5 满足 $N=2$。
- 测试点 6-8 满足 $M=1$。
- 测试点 9-14 满足 $M=2$。
- 测试点 15-20 没有额外限制。

## 样例 #1

### 输入

```
5

1 2
2 1 1
2 1 1

1 3
2 1 1
0
2 1 1

2 1
4 1 2 1 2

4 2
6 1 2 2 3 3 1
6 1 2 4 4 2 1

2 2
4 1 1 2 2
4 2 2 1 1```

### 输出

```
YES
NO
NO
YES
NO```

# AI分析结果

### 综合分析与结论
这些题解的核心思路都是通过分析手链颜色出现的位置和顺序，判断手链是否满足简单闭合折线、不与自身相交、不与其他手链相交这三个条件。具体做法是先判断手链是否连续，再判断手链之间的位置关系（包含、相离等）来确定是否相交。

各题解在实现细节上有所不同，但整体思路相似。部分题解通过记录颜色出现的上下端、最左最右行等信息来辅助判断，部分题解则从不同的不合法情况入手进行判断。

### 所选题解
- **作者：Eibon (赞：3)  4星**
  - 关键亮点：思路清晰，代码结构合理，通过定义多个函数分别处理不同的判断逻辑，提高了代码的可读性和可维护性。
- **作者：XL4453 (赞：2)  4星**
  - 关键亮点：详细列举了多种不合法情况，包括链子断掉、链子相交等，并分别实现了对应的判断函数，逻辑严谨。
- **作者：Purslane (赞：0)  4星**
  - 关键亮点：采用两两检查的思路，将判断相交问题转化为判断包含或相离，简化了问题的处理。

### 重点代码及核心实现思想
#### Eibon 的题解
```cpp
bool in(int i,int j)
{
    if(!(l[i]<=l[j]&&r[j]<=r[i])){
        return 0;
    }
    for(int x=l[j];x<=r[j];x++){
        if(!(c1[x][i]<c1[x][j]&&c2[x][j]<c2[x][i])){
            return 0;
        }
    }
    return 1;
}
bool ud(int i,int j)
{
    for(int x=1;x<=m;x++){
        int xi=c2[x][i],xj=c1[x][j];
        if(xi&&xj&&xi>xj){
            return 0;
        }
    }
    return 1;
}
bool VIP()
{
    for(int i=1;i<=n;i++){
        if(!l[i]){
            continue;
        }
        for(int j=l[i];j<=r[i];j++){
            if(!c1[j][i]){
                return 0;
            }
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<i;j++){
            if(!in(i,j)&&!in(j,i)&&!ud(i,j)&&!ud(j,i)){
                return 0;
            }
        }
    }
    return 1;
}
```
核心实现思想：`in` 函数判断颜色 $i$ 是否包含颜色 $j$，`ud` 函数判断颜色 $i$ 是否在颜色 $j$ 的上方，`VIP` 函数先判断手链是否连续，再判断手链之间是否相交。

#### XL4453 的题解
```cpp
int check(int x,int y){
    for(int i=max(fi[x],fi[y]);i<=min(la[x],la[y]);i++){
        if(x1[i][x]>x1[i][y]&&x1[i][x]<x2[i][y]&&!(x2[i][x]>x1[i][y]&&x2[i][x]<x2[i][y]))return 1;
        if(x2[i][x]>x1[i][y]&&x2[i][x]<x2[i][y]&&!(x1[i][x]>x1[i][y]&&x1[i][x]<x2[i][y]))return 1;
    }
    return 0;
}
int IN(int x,int y){
    for(int i=max(fi[x],fi[y]);i<=min(la[x],la[y]);i++){
        if(x1[i][x]>x1[i][y]&&x1[i][x]<x2[i][y]&&x2[i][x]>x1[i][y]&&x2[i][x]<x2[i][y]){
            if(fi[x]<fi[y]||la[x]>la[y])return 2;
            return 1;//x in y
        }
    }
    return 0;
}
int UP(int x,int y){
    for(int i=max(fi[x],fi[y]);i<=min(la[x],la[y]);i++){
        if(x1[i][x]>x2[i][y])return 1;
    }
    return 0;
}
```
核心实现思想：`check` 函数判断是否出现一个链子一段在另一个链子中间，另一段在外面的情况，`IN` 函数判断是否存在一个链子包含另一个链子的情况，`UP` 函数判断是否存在一个链子在另一个链子上方的情况。

#### Purslane 的题解
```cpp
int contain(int x,int y) {
    if(!(fst[x]<=fst[y]&&lst[x]>=lst[y])) return 0;
    ffor(i,fst[y],lst[y]) if(!(pl1[i][x]<=pl1[i][y]&&pl2[i][x]>=pl2[i][y])) return 0;
    return 1;
}
int diff(int x,int y) {
    ffor(i,1,m) if(pl1[i][y]&&!(pl2[i][x]<=pl1[i][y])) return 0;
    return 1;
}
```
核心实现思想：`contain` 函数判断颜色 $x$ 是否包含颜色 $y$，`diff` 函数判断颜色 $x$ 和颜色 $y$ 是否相离。

### 最优关键思路或技巧
- **正难则反**：直接判断相交比较困难，考虑判断包含和相离的情况，通过排除包含和相离的情况来确定是否相交。
- **两两检查**：由于相交是两两相交，所以可以对每对手链进行检查，简化问题的处理。

### 可拓展之处
同类型题或类似算法套路：判断几何图形的相交、包含等关系，如判断线段相交、多边形相交等。可以使用类似的思路，通过记录图形的位置信息，判断图形之间的位置关系。

### 推荐题目
- [P1196 银河英雄传说](https://www.luogu.com.cn/problem/P1196)：考察并查集的应用，判断元素之间的关系。
- [P1892 [BOI2003]团伙](https://www.luogu.com.cn/problem/P1892)：同样考察并查集，处理元素之间的朋友和敌人关系。
- [P2024 [NOI2001] 食物链](https://www.luogu.com.cn/problem/P2024)：利用并查集解决复杂的元素关系判断问题。

### 个人心得
这些题解中均未包含个人心得（调试/顿悟）相关内容。

---
处理用时：45.08秒