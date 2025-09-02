# 题目信息

# Recycling Bottles

## 题目描述

It was recycling day in Kekoland. To celebrate it Adil and Bera went to Central Perk where they can take bottles from the ground and put them into a recycling bin.

We can think Central Perk as coordinate plane. There are $ n $ bottles on the ground, the $ i $ -th bottle is located at position $ (x_{i},y_{i}) $ . Both Adil and Bera can carry only one bottle at once each.

For both Adil and Bera the process looks as follows:

1. Choose to stop or to continue to collect bottles.
2. If the choice was to continue then choose some bottle and walk towards it.
3. Pick this bottle and walk to the recycling bin.
4. Go to step $ 1 $ .

Adil and Bera may move independently. They are allowed to pick bottles simultaneously, all bottles may be picked by any of the two, it's allowed that one of them stays still while the other one continues to pick bottles.

They want to organize the process such that the total distance they walk (the sum of distance walked by Adil and distance walked by Bera) is minimum possible. Of course, at the end all bottles should lie in the recycling bin.

## 说明/提示

Consider the first sample.

Adil will use the following path: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF671A/9e150a5b7d96969b57a5b1f4dea00f000710a7e2.png).

Bera will use the following path: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF671A/3884532a18b9773dea1f2047e6bbd80cd6d12185.png).

Adil's path will be ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF671A/d2c02d2d4b61a9b8e78355ce9a7fbc852f71e66b.png) units long, while Bera's path will be ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF671A/da983b0763053dcb65ef9a22647e2063dd0571f6.png) units long.

## 样例 #1

### 输入

```
3 1 1 2 0 0
3
1 1
2 1
2 3
```

### 输出

```
11.084259940083
```

## 样例 #2

### 输入

```
5 0 4 2 2 0
5
5 2
3 0
5 5
3 5
3 3
```

### 输出

```
33.121375178000
```

# AI分析结果

### 题目内容
# 回收瓶子

## 题目描述
在可可兰（Kekoland）是回收日。为了庆祝这一天，阿迪尔（Adil）和贝拉（Bera）去了中央公园（Central Perk），在那里他们可以从地上捡起瓶子并放入回收箱。

我们可以将中央公园看作是一个坐标平面。地上有\(n\)个瓶子，第\(i\)个瓶子位于位置\((x_{i}, y_{i})\)。阿迪尔和贝拉每人一次只能拿一个瓶子。

对于阿迪尔和贝拉来说，整个过程如下：
1. 选择停止收集瓶子或者继续收集。
2. 如果选择继续，那么选择某个瓶子并走向它。
3. 捡起这个瓶子，然后走到回收箱。
4. 回到步骤1。

阿迪尔和贝拉可以独立行动。他们可以同时捡起瓶子，所有瓶子都可以被两人中的任意一人捡起，也允许其中一人静止不动，而另一人继续捡瓶子。

他们希望组织这个过程，使得他们行走的总距离（阿迪尔行走的距离与贝拉行走的距离之和）尽可能小。当然，最后所有瓶子都应该在回收箱中。

## 说明/提示
考虑第一个样例。

阿迪尔将使用以下路径：[此处应是对应路径的图片链接，但文本无法显示]。

贝拉将使用以下路径：[此处应是对应路径的图片链接，但文本无法显示]。

阿迪尔的路径长度将是[此处应是对应长度的图片链接，但文本无法显示]单位长，而贝拉的路径长度将是[此处应是对应长度的图片链接，但文本无法显示]单位长。

## 样例 #1
### 输入
```
3 1 1 2 0 0
3
1 1
2 1
2 3
```
### 输出
```
11.084259940083
```

## 样例 #2
### 输入
```
5 0 4 2 2 0
5
5 2
3 0
5 5
3 5
3 3
```
### 输出
```
33.121375178000
```

### 算法分类
贪心

### 综合分析与结论
这两道题解思路本质相似，均先算出所有瓶子从垃圾桶往返的总距离作为初始值，再考虑如何通过两人初始位置到瓶子的距离来优化总距离。
 - **思路**：都基于贪心思想，试图找出一种最优的捡瓶子分配方式，使得两人行走总距离最小。
 - **算法要点**：计算各瓶子到垃圾桶距离、两人到各瓶子距离，通过比较这些距离的差值来决定如何优化总距离。
 - **解决难点**：在于如何合理分配瓶子给两人，使总距离最优，关键是分析不同情况下距离的变化并找出最大优化值。

### 题解1
 - **星级**：4星
 - **关键亮点**：思路清晰，代码简洁。通过`pair`存储距离差值与对应瓶子编号，利用`sort`排序后直接通过比较差值大小确定优化值，逻辑连贯。
 - **重点代码**：
```cpp
double D(int x1,int y1,int x2,int y2) {
    return sqrt(1.0*(x1-x2)*(x1-x2)+1.0*(y1-y2)*(y1-y2));
}

int main() {
    scanf("%d %d %d %d %d %d %d",&ax,&ay,&bx,&by,&tx,&ty,&n);
    for(int i=1;i<=n;i++) {
        scanf("%d %d",&x[i],&y[i]);
        double dis = D(x[i],y[i],tx,ty);
        A[i] = make_pair(D(ax,ay,x[i],y[i]) - dis,i);
        B[i] = make_pair(D(bx,by,x[i],y[i]) - dis,i);
        t[i] = make_pair(dis * 2,i);
        ans += t[i].first;
    }
    sort(A+1,A+1+n);
    sort(B+1,B+1+n);

    tmp = min(A[1].first,B[1].first);
    if(A[1].second == B[1].second) 
        tmp = min(tmp,min(A[1].first + B[2].first, A[2].first +B[1].first));
    else 
        tmp = min(tmp,A[1].first + B[1].first);
    printf("%.15lf\n",ans + tmp);
    return 0;
}
```
核心实现思想：先计算每个瓶子到垃圾桶的往返距离累加到`ans`，同时计算两人到各瓶子距离与瓶子到垃圾桶距离的差值存于`A`和`B`数组，排序后根据两人是否捡同一个瓶子的情况取合适的差值组合更新优化值`tmp`，最后加到`ans`输出。

### 题解2
 - **星级**：3星
 - **关键亮点**：通过定义结构体存储瓶子坐标，代码结构较为清晰，但整体代码较冗长，有较多模板代码。
 - **重点代码**：
```cpp
double dis(double a, double b, double x, double y) {
    return sqrt(1.0*(a - x)*(a - x) + 1.0*(b - y)*(b - y))*1.0;
}

int main()
{
    rdlf(ax); rdlf(ay); rdlf(bx); rdlf(by); rdlf(tx); rdlf(ty);
    int n; rdint(n);
    double ans = 0.0;
    for (int i = 1; i <= n; i++) {
        rdlf(indx[i].x), rdlf(indx[i].y);
        dist[i] = 1.0*dis(indx[i].x, indx[i].y, tx, ty);
        disa[i] = 1.0*dis(ax, ay, indx[i].x, indx[i].y);
        disb[i] = 1.0*dis(bx, by, indx[i].x, indx[i].y);
        ans += 2.0*dist[i];
    }
    double Max = INF * 1.0;
    double Maxx = INF * 1.0;
    int posa, posb;

    for (int i = 1; i <= n; i++) {
        if (Max > disa[i] - dist[i]) {
            Max =1.0* disa[i] - 1.0*dist[i]; posa = i;
        }
        if (Maxx > disb[i] - dist[i]) {
            Maxx = 1.0*disb[i] - 1.0*dist[i]; posb = i;
        }
    }
    double sum = ans;
    if (Maxx < 0 && Max < 0) {
        if (posa!= posb) {
            sum = ans + Maxx * 1.0 + Max * 1.0;
        }
        else {
            for (int i = 0; i <= n; i++) {
                if (i!= posa) {
                    sum = min(sum, ans - dist[posa] + disa[posa] - dist[i] + disb[i]);
                }
            }
            for (int i = 0; i <= n; i++) {
                if (i!= posb) {
                    sum = min(sum, ans - dist[posb] + disb[posb] - dist[i] + disa[i]);
                }
            }
        }
    }
    else {
        if (Max < Maxx) {
            sum = ans + disa[posa] - dist[posa];
        }
        else {
            sum = ans + disb[posb] - dist[posb];
        }
    }
    printf("%.9lf\n", 1.0*sum);
    return 0;
}
```
核心实现思想：先计算每个瓶子到垃圾桶的往返距离累加到`ans`，同时计算两人到各瓶子距离与瓶子到垃圾桶距离的差值，找出两人差值最大的瓶子位置，根据差值正负及两人所选瓶子是否相同来更新总距离`sum`并输出。

### 最优关键思路或技巧
利用贪心策略，先计算所有瓶子从垃圾桶往返的基准距离，再通过比较两人初始位置到各瓶子距离与瓶子到垃圾桶距离的差值，选取最大差值组合来优化总距离。在代码实现上，合理利用数据结构（如`pair`）存储相关数据，简化逻辑判断。

### 拓展
同类型题可涉及多人在平面上收集物品并运输到指定地点求最短路径和的问题，类似算法套路是先确定一个基准距离，再通过分析各点间距离关系，利用贪心思想找出优化距离的方式。

### 洛谷题目推荐
 - [P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094)：贪心策略应用，通过合理分组使组数最少。
 - [P1199 三国游戏](https://www.luogu.com.cn/problem/P1199)：需分析双方策略，利用贪心思想找出最优解。
 - [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)：根据接水时间贪心排序，求总等待时间最小值。 

---
处理用时：91.61秒