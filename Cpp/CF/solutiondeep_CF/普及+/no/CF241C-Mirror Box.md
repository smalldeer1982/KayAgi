# 题目信息

# Mirror Box

## 题目描述

Mirror Box is a name of a popular game in the Iranian National Amusement Park (INAP). There is a wooden box, $ 10^{5} $ cm long and $ 100 $ cm high in this game. Some parts of the box's ceiling and floor are covered by mirrors. There are two negligibly small holes in the opposite sides of the box at heights $ h_{l} $ and $ h_{r} $ centimeters above the floor. The picture below shows what the box looks like.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF241C/6424a01d70e5009585312ab434deff869a3c6956.png)In the game, you will be given a laser gun to shoot once. The laser beam must enter from one hole and exit from the other one. Each mirror has a preset number $ v_{i} $ , which shows the number of points players gain if their laser beam hits that mirror. Also — to make things even funnier — the beam must not hit any mirror more than once.

Given the information about the box, your task is to find the maximum score a player may gain. Please note that the reflection obeys the law "the angle of incidence equals the angle of reflection".

## 说明/提示

The second sample is depicted above. The red beam gets $ 10+50+5+35+8+2=110 $ points and the blue one gets $ 120 $ .

The red beam on the picture given in the statement shows how the laser beam can go approximately, this is just illustration how the laser beam can gain score. So for the second sample there is no such beam that gain score 110.

## 样例 #1

### 输入

```
50 50 7
10 F 1 80000
20 T 1 80000
30 T 81000 82000
40 T 83000 84000
50 T 85000 86000
60 T 87000 88000
70 F 81000 89000
```

### 输出

```
100
```

## 样例 #2

### 输入

```
80 72 9
15 T 8210 15679
10 F 11940 22399
50 T 30600 44789
50 F 32090 36579
5 F 45520 48519
120 F 49250 55229
8 F 59700 80609
35 T 61940 64939
2 T 92540 97769
```

### 输出

```
120
```

# AI分析结果

### 题目内容
# 镜像盒子

## 题目描述
“镜像盒子”是伊朗国家游乐园（INAP）一款热门游戏的名字。在这个游戏中有一个木箱，长$10^{5}$厘米，高$100$厘米。箱子的天花板和地板部分区域覆盖着镜子。箱子相对的两侧有两个极小的孔，距离地板高度分别为$h_{l}$和$h_{r}$厘米。下图展示了箱子的样子。

![镜像盒子](https://cdn.luogu.com.cn/upload/vjudge_pic/CF241C/6424a01d70e5009585312ab434deff869a3c6956.png)

在游戏中，你将获得一把激光枪进行一次射击。激光束必须从一个孔射入并从另一个孔射出。每个镜子都有一个预设数字$v_{i}$，表示玩家的激光束击中该镜子时获得的分数。并且，为了增加趣味性，激光束不能多次击中同一面镜子。

给定关于箱子的信息，你的任务是找出玩家可能获得的最大分数。请注意，反射遵循“入射角等于反射角”的定律。

## 说明/提示
第二个样例如下图所示。红色光束得分为$10 + 50 + 5 + 35 + 8 + 2 = 110$分，蓝色光束得分为$120$分。

题目中给出图片里的红色光束展示了激光束大致的行进路径，这只是说明激光束如何得分的示例。所以对于第二个样例，不存在得分为$110$的光束。

## 样例 #1
### 输入
```
50 50 7
10 F 1 80000
20 T 1 80000
30 T 81000 82000
40 T 83000 84000
50 T 85000 86000
60 T 87000 88000
70 F 81000 89000
```
### 输出
```
100
```

## 样例 #2
### 输入
```
80 72 9
15 T 8210 15679
10 F 11940 22399
50 T 30600 44789
50 F 32090 36579
5 F 45520 48519
120 F 49250 55229
8 F 59700 80609
35 T 61940 64939
2 T 92540 97769
```
### 输出
```
120
```

### 算法分类
搜索

### 综合分析与结论
题解通过将光线反射问题转化为光线沿直线传播且盒子镜子反复翻转的问题，简化了问题的求解。在确定反射次数后，通过计算光线直线解析式及与翻转后盒子交点来模拟光线传播过程，判断是否击中未使用过的镜子并计算得分，时间复杂度为$O(n^2)$。

### 所选的题解
- **recollect_i题解**：★★★★
  - **关键亮点**：巧妙地将光线反射转化为光线直走且盒子镜子翻转的模型，降低了模拟光线反射路径的难度。通过对反射次数的枚举，全面考虑所有可能的光线传播路径。
  - **核心代码片段**：
```cpp
void jxs(double ya, double yb)
{
    b = ya;
    k = (yb - ya) / 1e5;
}
void jd(double y)
{
    x = (y - b) / k;
}
void solve()
{
    for(int i = 1; i <= n; i ++ )
    {
        memset(usu, 0, sizeof usu);
        memset(usd, 0, sizeof usd);
        int cnt = 0;
        if(i & 1)
        {
            double pr = -r - 100 * (i - 1);
            jxs(l, pr);
            for(int j = 0; j < i; j ++ )
            {
                jd(-100 * j);
                if(j & 1)
                {
                    int k = upper_bound(up + 1, up + nu + 1, (node){x, 0, 0}) - up - 1;
                    if(x > up[k].r || usu[k]) cnt = -2e9;
                    else cnt += up[k].v;
                    usu[k] = true;
                }
                else
                {
                    int k = upper_bound(down + 1, down + nd + 1, (node){x, 0, 0}) - down - 1;
                    if(x > down[k].r || usd[k]) cnt = -2e9;
                    else cnt += down[k].v;
                    usd[k] = true;
                }
            }
        }
        else
        {
            double pr = r - 100 * i;
            jxs(l, pr);
            for(int j = 0; j < i; j ++ )
            {
                jd(-100 * j);
                if(j & 1)
                {
                    int k = upper_bound(up + 1, up + nu + 1, (node){x, 0, 0}) - up - 1;
                    if(x > up[k].r || usu[k]) cnt = -2e9;
                    else cnt += up[k].v;
                    usu[k] = true;
                }
                else
                {
                    int k = upper_bound(down + 1, down + nd + 1, (node){x, 0, 0}) - down - 1;
                    if(x > down[k].r || usd[k]) cnt = -2e9;
                    else cnt += down[k].v;
                    usd[k] = true;
                }
            }
        }
        res = max(res, cnt);
    }
}
```
  - **核心实现思想**：`jxs`函数计算光线直线的解析式，`jd`函数根据直线解析式计算给定$y$值对应的$x$值。`solve`函数枚举反射次数$i$，根据$i$的奇偶性确定右侧洞对应点坐标，进而计算光线直线解析式，然后在每次反射位置判断是否击中有效镜子并计算得分，最后更新最大得分。

### 最优关键思路或技巧
将光线反射问题转化为光线沿直线传播，通过翻转盒子和镜子来模拟光线反射路径，简化了光线反射路径的计算。同时，通过枚举反射次数全面考虑所有可能路径，利用二分查找（`upper_bound`）快速定位镜子位置。

### 可拓展之处
同类型题或类似算法套路：此类光线反射问题，常可通过将反射转化为直线传播简化问题，类似的还有台球在有边界反射的桌面上的运动轨迹等问题。在解决这类问题时，关键在于找到合适的变换方式将复杂的反射问题转化为易于处理的直线问题。

### 洛谷相似题目推荐
- [P1308 统计单词数](https://www.luogu.com.cn/problem/P1308)：字符串处理问题，考察字符串查找、统计等操作，与本题通过特定方法简化问题求解类似。
- [P1164 小A点菜](https://www.luogu.com.cn/problem/P1164)：动态规划问题，通过状态转移方程求解最优解，与本题通过枚举反射次数并计算得分求最优解思路类似。
- [P1249 最大乘积](https://www.luogu.com.cn/problem/P1249)：搜索问题，通过枚举不同的拆分方式求解最大乘积，与本题枚举反射次数求最大得分思路类似。 

---
处理用时：68.41秒