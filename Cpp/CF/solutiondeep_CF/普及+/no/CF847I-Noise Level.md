# 题目信息

# Noise Level

## 题目描述

The Berland's capital has the form of a rectangle with sizes $ n×m $ quarters. All quarters are divided into three types:

- regular (labeled with the character '.') — such quarters do not produce the noise but are not obstacles to the propagation of the noise;
- sources of noise (labeled with an uppercase Latin letter from 'A' to 'Z') — such quarters are noise sources and are not obstacles to the propagation of the noise;
- heavily built-up (labeled with the character '\*') — such quarters are soundproofed, the noise does not penetrate into them and they themselves are obstacles to the propagation of noise.

A quarter labeled with letter 'A' produces $ q $ units of noise. A quarter labeled with letter 'B' produces $ 2·q $ units of noise. And so on, up to a quarter labeled with letter 'Z', which produces $ 26·q $ units of noise. There can be any number of quarters labeled with each letter in the city.

When propagating from the source of the noise, the noise level is halved when moving from one quarter to a quarter that shares a side with it (when an odd number is to be halved, it's rounded down). The noise spreads along the chain. For example, if some quarter is located at a distance $ 2 $ from the noise source, then the value of noise which will reach the quarter is divided by $ 4 $ . So the noise level that comes from the source to the quarter is determined solely by the length of the shortest path between them. Heavily built-up quarters are obstacles, the noise does not penetrate into them.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF847I/0a8ce4c074a103c21f7e8facf314824c3efeff45.png)The values in the cells of the table on the right show the total noise level in the respective quarters for $ q=100 $ , the first term in each sum is the noise from the quarter 'A', the second — the noise from the quarter 'B'.The noise level in quarter is defined as the sum of the noise from all sources. To assess the quality of life of the population of the capital of Berland, it is required to find the number of quarters whose noise level exceeds the allowed level $ p $ .

## 说明/提示

The illustration to the first example is in the main part of the statement.

## 样例 #1

### 输入

```
3 3 100 140
...
A*.
.B.
```

### 输出

```
3
```

## 样例 #2

### 输入

```
3 3 2 8
B*.
BB*
BBB
```

### 输出

```
4
```

## 样例 #3

### 输入

```
3 4 5 4
..*B
..**
D...
```

### 输出

```
7
```

# AI分析结果

### 题目内容
# 噪音等级

## 题目描述
伯兰的首都呈一个 $n×m$ 街区的矩形形状。所有街区分为三种类型：
- 普通街区（用字符 '.' 标记）—— 此类街区不产生噪音，但对噪音传播没有阻碍；
- 噪音源街区（用大写拉丁字母 'A' 到 'Z' 标记）—— 此类街区是噪音源，且对噪音传播没有阻碍；
- 高楼密集街区（用字符 '*' 标记）—— 此类街区是隔音的，噪音无法穿透，且它们本身是噪音传播的障碍物。

标记为字母 'A' 的街区产生 $q$ 单位的噪音。标记为字母 'B' 的街区产生 $2·q$ 单位的噪音。以此类推，标记为字母 'Z' 的街区产生 $26·q$ 单位的噪音。城市中每个字母标记的街区数量可以是任意的。

噪音从噪音源传播时，当从一个街区移动到与之共享一条边的街区时，噪音等级减半（当要减半的数字为奇数时，向下取整）。噪音沿链条传播。例如，如果某个街区与噪音源的距离为 $2$，那么到达该街区的噪音值将除以 $4$。因此，从源头传播到街区的噪音等级仅由它们之间的最短路径长度决定。高楼密集街区是障碍物，噪音无法穿透它们。

![示例图](https://cdn.luogu.com.cn/upload/vjudge_pic/CF847I/0a8ce4c074a103c21f7e8facf314824c3efeff45.png)
右边表格单元格中的值显示了在 $q = 100$ 时各个街区的总噪音等级，每个和中的第一项是来自街区 'A' 的噪音，第二项是来自街区 'B' 的噪音。街区的噪音等级定义为所有噪音源产生的噪音之和。为了评估伯兰首都居民的生活质量，需要找出噪音等级超过允许水平 $p$ 的街区数量。

## 说明/提示
第一个示例的图示在题目主体部分。

## 样例 #1
### 输入
```
3 3 100 140
...
A*.
.B.
```
### 输出
```
3
```

## 样例 #2
### 输入
```
3 3 2 8
B*.
BB*
BBB
```
### 输出
```
4
```

## 样例 #3
### 输入
```
3 4 5 4
..*B
..**
D...
```
### 输出
```
7
```

### 算法分类
模拟

### 题解综合分析与结论
目前仅提供了一份题解，该题解思路是对每个噪音源进行广度优先搜索（BFS），计算其对各个可达街区的噪音贡献，最后统计噪音等级超过允许水平 $p$ 的街区数量。算法要点在于利用 BFS 遍历每个噪音源，根据传播规则更新每个可达街区的噪音值，难点在于正确实现 BFS 过程中的噪音传播逻辑，如减半操作及对障碍物的处理。

### 所选的题解
- **星级**：3 星
- **关键亮点**：采用 BFS 模拟噪音传播过程，逻辑较为清晰，代码基础且易理解。
- **重点代码**：
```cpp
void bfs(int a,int b,int energy){
    vvis.clear();queue<pair<int,int> > Q;
    Q.push(mp(a,b));dist[a][b]=energy;
    while (!Q.empty()){
        pair<int,int> x=Q.front();Q.pop();
        if (dist[x.first][x.second]<=1) continue;
        for (int i=0;i<4;i++){
            int X=x.first+d1[i],Y=x.second+d2[i];
            if (X>=0 && Y>=0 && X<n && Y<m && dist[X][Y]==0 && c[X][Y]!='*'){
                dist[X][Y]=dist[x.first][x.second]/2;
                Q.push(mp(X,Y));
                vvis.pb(mp(X,Y));
            }
        }
    }
    vvis.pb(mp(a,b));
    for (int i=0;i<vvis.size();i++){
        noise[vvis[i].first][vvis[i].second]+=dist[vvis[i].first][vvis[i].second];
        dist[vvis[i].first][vvis[i].second]=0;
    }
}
```
核心实现思想：以给定的噪音源坐标 $(a,b)$ 为起点进行 BFS，`dist` 数组记录每个街区从噪音源获取的噪音值，在 BFS 过程中，若当前街区噪音值大于 1，则向四个方向传播，传播时噪音值减半。最后将所有可达街区的噪音值累加到 `noise` 数组中，并重置 `dist` 数组。

### 通用建议与扩展思路
通用建议：在处理此类模拟题时，要清晰梳理逻辑，确保对每个条件和规则的实现准确无误。对于 BFS 过程，可以进一步优化空间使用，比如使用更紧凑的数据结构记录已访问状态。
扩展思路：同类型题可考虑增加噪音传播的复杂规则，如噪音在某些特殊街区会增强而非减弱；类似算法套路可用于模拟其他具有传播性质的场景，如传染病传播、信号扩散等，关键在于准确模拟传播规则和处理障碍物。

### 洛谷相似题目推荐
 - [P1032 字串变换](https://www.luogu.com.cn/problem/P1032)：通过模拟字符串变换规则求解，涉及到对规则的准确应用和搜索过程。
 - [P1162 填涂颜色](https://www.luogu.com.cn/problem/P1162)：利用类似 BFS 的思路，对图形进行填充和状态更新，与本题模拟传播过程有相似之处。
 - [P1339 热浪](https://www.luogu.com.cn/problem/P1339)：虽然是最短路问题，但同样涉及到状态的更新和传播，可类比本题噪音传播的方式进行思考。 

---
处理用时：45.52秒