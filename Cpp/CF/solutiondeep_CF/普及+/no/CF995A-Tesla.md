# 题目信息

# Tesla

## 题目描述

Allen dreams of one day owning a enormous fleet of electric cars, the car of the future! He knows that this will give him a big status boost. As Allen is planning out all of the different types of cars he will own and how he will arrange them, he realizes that he has a problem.

Allen's future parking lot can be represented as a rectangle with $ 4 $ rows and $ n $ ( $ n \le 50 $ ) columns of rectangular spaces, each of which can contain at most one car at any time. He imagines having $ k $ ( $ k \le 2n $ ) cars in the grid, and all the cars are initially in the second and third rows. Each of the cars also has a different designated parking space in the first or fourth row. Allen has to put the cars into corresponding parking places.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF995A/34279eda6e70545a7bbf8d625eb53e7d26a4b91d.png)Illustration to the first example.However, since Allen would never entrust his cars to anyone else, only one car can be moved at a time. He can drive a car from a space in any of the four cardinal directions to a neighboring empty space. Furthermore, Allen can only move one of his cars into a space on the first or fourth rows if it is the car's designated parking space.

Allen knows he will be a very busy man, and will only have time to move cars at most $ 20000 $ times before he realizes that moving cars is not worth his time. Help Allen determine if he should bother parking his cars or leave it to someone less important.

## 说明/提示

In the first sample test case, all cars are in front of their spots except car $ 5 $ , which is in front of the parking spot adjacent. The example shows the shortest possible sequence of moves, but any sequence of length at most $ 20000 $ will be accepted.

In the second sample test case, there is only one column, and the cars are in the wrong order, so no cars can move and the task is impossible.

## 样例 #1

### 输入

```
4 5
1 2 0 4
1 2 0 4
5 0 0 3
0 5 0 3
```

### 输出

```
6
1 1 1
2 1 2
4 1 4
3 4 4
5 3 2
5 4 2
```

## 样例 #2

### 输入

```
1 2
1
2
1
2
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
1 2
1
1
2
2
```

### 输出

```
2
1 1 1
2 4 1
```

# AI分析结果

### 题目内容
# Tesla

## 题目描述
艾伦梦想着有一天能拥有一支庞大的电动汽车车队，这可是未来的汽车！他知道这会大大提升他的地位。当艾伦规划着他将拥有的各种不同类型的汽车以及如何停放它们时，他意识到了一个问题。

艾伦未来的停车场可以表示为一个矩形，有4行和n（n≤50）列的矩形停车位，每个停车位在任何时候最多只能停放一辆车。他设想在这个矩形网格中有k（k≤2n）辆车，并且所有车最初都停在第二行和第三行。每辆车在第一行或第四行也都有一个不同的指定停车位。艾伦必须将这些车停到相应的停车位上。

![示例图](https://cdn.luogu.com.cn/upload/vjudge_pic/CF995A/34279eda6e70545a7bbf8d625eb53e7d26a4b91d.png) 第一个示例的图示。然而，由于艾伦从不放心把他的车交给别人，所以一次只能移动一辆车。他可以将一辆车从任意四个基本方向中的一个方向开到相邻的空车位。此外，艾伦只有在某个车位是某辆车的指定停车位时，才能将该车移动到第一行或第四行的这个车位上。

艾伦知道自己会是个大忙人，在意识到移动车辆不值得他花费时间之前，他最多只会有时间移动车辆20000次。请帮助艾伦判断他是否应该费心去停车，还是把这件事留给不那么重要的人去做。

## 说明/提示
在第一个示例测试用例中，除了车5停在相邻的停车位前，所有车都停在它们的车位前。该示例展示了最短的可能移动序列，但任何长度不超过20000的序列都将被接受。

在第二个示例测试用例中，只有一列，并且车辆的顺序不对，所以没有车可以移动，任务是不可能完成的。

## 样例 #1
### 输入
```
4 5
1 2 0 4
1 2 0 4
5 0 0 3
0 5 0 3
```
### 输出
```
6
1 1 1
2 1 2
4 1 4
3 4 4
5 3 2
5 4 2
```
## 样例 #2
### 输入
```
1 2
1
2
1
2
```
### 输出
```
-1
```
## 样例 #3
### 输入
```
1 2
1
1
2
2
```
### 输出
```
2
1 1 1
2 4 1
```
### 算法分类
构造

### 题解综合分析与结论
这三道题解思路本质相似，都是先处理能直接停入车位的车，之后通过中间两行车辆的循环移动，创造停车机会，且都证明了操作次数满足要求。
1. **思路**：均先考虑直接能停入车位的车，然后通过让中间两行车辆按特定顺序循环移动，使车能到达其停车位前，再停入。
2. **算法要点**：确定车辆循环移动顺序，如顺时针或逆时针；记录车辆位置与目标停车位；记录移动步骤。
3. **解决难点**：需保证在有限次数内让所有车停入车位，通过分析中间两行车辆移动规律，证明最多移动$2nk + k$次，远小于20000次，满足题目要求。同时要处理好车辆移动过程中的各种边界情况，如循环交界处车辆的移动。

### 所选的题解
- **作者：rui_er（5星）**
    - **关键亮点**：代码结构清晰，模块化程度高，通过多个函数分别实现获取下一个位置、检查车位、车辆旋转等功能，逻辑清晰易懂。
    - **核心代码片段**：
```cpp
tuple<int, int> getNext(const tuple<int, int>& pos) {
    int x = get<0>(pos), y = get<1>(pos);
    if(x == 2) {
        if(y == n) return make_tuple(3, n);
        return make_tuple(2, y+1);
    }
    if(y == 1) return make_tuple(2, 1);
    return make_tuple(3, y-1);
}
bool isEmpty(const tuple<int, int>& pos) {
    return!a[get<0>(pos)][get<1>(pos)];
}
bool checkPark(const int& id) {
    if(abs(get<0>(s[id])-get<0>(t[id])) == 1 && get<1>(s[id]) == get<1>(t[id])) {
        ans.push_back(make_tuple(id, get<0>(t[id]), get<1>(t[id])));
        a[get<0>(s[id])][get<1>(s[id])] = a[get<0>(t[id])][get<1>(t[id])] = 0;
        return 1;
    }
    return 0;
}
bool rotateR() {
    bool ok = 0;
    rep(i, 2, 3) {
        rep(j, 1, n) {
            if(!a[i][j]) continue;
            tuple<int, int> nxt = getNext(make_tuple(i, j));
            if(checkPark(a[i][j])) ok = 1;
            else if(isEmpty(nxt)) {
                int id = a[i][j];
                ans.push_back(make_tuple(id, get<0>(nxt), get<1>(nxt)));
                a[i][j] = 0;
                a[get<0>(nxt)][get<1>(nxt)] = id;
                s[id] = nxt;
                ok = 1;
            }
        }
    }
    return ok;
}
```
    - **核心实现思想**：`getNext`函数获取车辆下一个位置，`isEmpty`检查位置是否为空，`checkPark`判断车能否停入车位并记录操作，`rotateR`实现车辆旋转移动并尝试停车，通过这些函数协作完成车辆移动与停车操作。
- **作者：Karry5307（4星）**
    - **关键亮点**：代码简洁，通过预处理数组`prvx`、`prvy`、`nxtx`、`nxty`记录车辆移动方向，方便实现车辆循环移动。
    - **核心代码片段**：
```cpp
inline void move() {
    for(register int i = 1; i <= n; i++) {
        g[1][i] == g[2][i] && g[1][i]? s.push_back((Item){g[1][i], 1, i}), g[2][i] = 0 : 1;
        g[3][i] == g[4][i] && g[3][i]? s.push_back((Item){g[4][i], 4, i}), g[3][i] = 0 : 1;
    }
}
inline void rotate() {
    ll tx = cx, ty = cy, u, v;
    ll px = prvx[tx][ty], py = prvy[tx][ty];
    for(register int i = px, j = py; i!= tx || j!= ty; i = u, j = v) {
        if(g[i][j]) {
            s.push_back((Item){g[i][j], nxtx[i][j], nxty[i][j]});
            swap(g[i][j], g[nxtx[i][j]][nxty[i][j]]);
        }
        u = prvx[i][j], v = prvy[i][j];
    }
    cx = nxtx[tx][ty], cy = nxty[tx][ty];
}
```
    - **核心实现思想**：`move`函数将能直接停入车位的车停入并记录操作，`rotate`函数利用预处理数组实现车辆循环移动并记录操作，通过这两个函数实现车辆移动与停车。
- **作者：DJRzjl（4星）**
    - **关键亮点**：在代码实现上对车辆移动的各种情况考虑细致，如循环交界处车辆移动的特殊处理，保证车辆按顺序移动且不重复移动。
    - **核心代码片段**：
```cpp
while(cnt < k) {
    if(old == tot || tot >= 12000) return puts("-1")&0;
    old = tot;
    for(int j = 1; j <= n; j++) {
        if(mp[2][j] && mp[1][j] == mp[2][j]) mp[2][j] = 0, insert(mp[1][j], 1, j), ++cnt;
        if(mp[3][j] && mp[4][j] == mp[3][j]) mp[3][j] = 0, insert(mp[4][j], 4, j), ++cnt;
    }
    op = 0;
    if(mp[2][1] &&!mp[3][1]) swap(mp[2][1], mp[3][1]), insert(mp[3][1], 3, 1), op = 1;
    for(int j = 2; j <= n; j++) if(mp[2][j] &&!mp[2][j - 1]) swap(mp[2][j], mp[2][j - 1]), insert(mp[2][j - 1], 2, j - 1);
    if((n!= 1 ||!op) && mp[3][n] &&!mp[2][n]) swap(mp[3][n], mp[2][n]), insert(mp[2][n], 2, n);
    for(int j = n - 1; j > 0 + op; j--) if(mp[3][j] &&!mp[3][j + 1]) swap(mp[3][j], mp[3][j + 1]), insert(mp[3][j + 1], 3, j + 1);
}
```
    - **核心实现思想**：在循环中，先处理能直接停车的情况，然后按顺序处理中间两行车辆的移动，包括循环交界处车辆移动的特殊处理，通过不断循环实现所有车辆的停放。

### 最优关键思路或技巧
通过分析中间两行车辆的移动规律，构造出一种循环移动方式，使每辆车都能在有限次数内到达其停车位前，且通过理论计算证明总操作次数满足题目限制。同时，在代码实现中要处理好车辆移动的顺序及边界情况。

### 同类型题或类似算法套路拓展
此类题目属于构造类问题，通常需要根据题目条件，构造出满足要求的方案。类似套路是先分析特殊情况（如本题中能直接停入车位的车），然后通过一定规律的操作（如本题车辆循环移动）来解决一般情况。同类型题目通常会给出一些限制条件，要求在这些条件下构造出可行方案。

### 洛谷相似题目推荐
- [P1036 选数](https://www.luogu.com.cn/problem/P1036)：通过枚举和组合的方式解决问题，与本题构造方案思路有一定相似性。
- [P1219 八皇后](https://www.luogu.com.cn/problem/P1219)：需要构造出满足条件的皇后摆放方案，与本题构造车辆移动方案类似。
- [P1433 吃奶酪](https://www.luogu.com.cn/problem/P1433)：通过合理构造路径来解决问题，与本题构造车辆移动路径思路相仿。 

---
处理用时：55.53秒