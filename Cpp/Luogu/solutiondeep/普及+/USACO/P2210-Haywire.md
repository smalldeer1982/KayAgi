# 题目信息

# Haywire

## 题目描述

Farmer John有 $N$ 只奶牛（$4 \leq N \leq 12$，$N$ 是偶数）。

他们建立了一套原生的系统，使得奶牛与他的朋友可以通过由干草保护的线路来进行对话交流。


每一头奶牛在这个牧场中正好有 $3$ 个朋友，并且他们必须把自己安排在一排干草堆中。


一条长 $L$ 的线路要占用刚好 $L$ 堆干草来保护线路。


比如说，如果有两头奶牛分别在草堆 $4$ 与草堆 $7$ 中，并且他们是朋友关系，那么我们就需要用 $3$ 堆干草来建造线路，使他们之间能够联系。


假设每一对作为朋友的奶牛都必须用一条单独的线路来连接，并且我们可以随便地改变奶牛的位置，请计算出我们建造线路所需要的最少的干草堆。


## 说明/提示

样例解释： 奶牛最好的排列是 `6, 5, 1, 4, 2, 3`, 这个时候我们只需要 $17$ 个单位的干草堆。


## 样例 #1

### 输入

```
6
6 2 5
1 3 4
4 2 6
5 3 2
4 6 1
1 5 3```

### 输出

```
17```

# AI分析结果

### 综合分析与结论
这些题解提供了多种解决奶牛排列以最小化线路干草堆数量问题的方法，涵盖了暴力枚举、随机化算法、模拟退火、启发式搜索、状态压缩 DP 等。暴力枚举简单直接但时间复杂度高，随机化算法通过多次随机排列找到较优解，模拟退火在随机基础上以一定概率接受较差解来跳出局部最优，启发式搜索和状态压缩 DP 则从不同角度对问题进行优化。

### 所选题解
- **ArachnidaKing（4星）**
    - **关键亮点**：对模拟退火算法的讲解详细，变量命名通俗易懂，代码注释丰富，方便初学者理解。
    - **个人心得**：提到模拟退火参数的调整是精髓所在，考试时可卡时限调整参数。
- **Ciyang（4星）**
    - **关键亮点**：对模拟退火的原理解释清晰，配有示意图，代码实现规范，有读入输出优化。
    - **个人心得**：指出模拟退火的三个重要参数（起始温度、终止温度、温度变化速度）需自己设置，本题较水，参数设置差不多就能过。
- **HNFMS_tomoo（4星）**
    - **关键亮点**：提供了多种解法，包括暴力枚举、启发式搜索和状态压缩 DP，并对每种解法的复杂度和优化过程进行了分析。
    - **个人心得**：发现暴力枚举在本题数据下得分比预期高，启发式搜索在教练出的数据中会超时，需进一步优化到状态压缩 DP 才能 AC。

### 重点代码
#### ArachnidaKing（模拟退火）
```cpp
inl tni qh();//用于一次退火中每次循环求出当前解的优劣情况
inl void exc(tin x,tni y);//交换函数，用于交换两头牛位置
inl tni sj(tni a,tni b);//随机函数，用于生成随机数

tni mian()
{
    srand(time(NULL));
    scanf("%d",&n);
    fora(i,1,n)
    {
        fora(j,1,3)
        {
            scanf("%d",&f[i][j]);
        }
        p[i]=i;
        pp[i]=i;
    }
    rc=qh();
    while((clock()/(1.0*CLOCKS_PER_SEC))<=zhongzhishijian)
    {
        lsc=rc;
        fora(i,1,n)
        {
            pp[i]=p[i];
        }
        for(re double T=chushiwendu;T>=zhongzhiwendu;T*=dertT)
        {
            do
            {
                x=sj(1,n);
                y=sj(1,n);
            }
            while(x==y);
            exc(x,y);
            lsc=qh();
            if(lsc<=rc)
            {
                rc=lsc;
            }
            else if((1.0*exp(rc-lsc))/T>(1.0*rand()/RAND_MAX))
            {
                exc(x,y);
            }
        }
    }
    printf("%d\n",rc/2);
    return 0;
}
```
**核心思想**：通过模拟退火算法，不断随机交换两头牛的位置，计算当前排列的花费，以一定概率接受较差解，最终找到最小花费。

#### Ciyang（模拟退火）
```cpp
int get_cost() {
    int tmp_ans= 0;
    for(int i= 1; i <= n; i++) {
        for(int j= 0; j < 3; j++) {
            tmp_ans+= absi(pos[i] - pos[f[i][j]]);
        }
    }
    return tmp_ans;
}

const double BeginT= 10000, EndT= 1e-12, ChangeT= 0.99;
void SA(int times) {
    int x, y, tmp_ans;
    while(times--) {
        for(double T= BeginT; T > EndT; T*= ChangeT) {
            do {
                x= rand() % n + 1;
                y= rand() % n + 1;
            } while(x == y);
            swap(pos[x], pos[y]);
            tmp_ans= get_cost();
            if(tmp_ans <= best_ans) {
                best_ans= tmp_ans;
            }
            else if(exp((best_ans - tmp_ans) / T) > (double)rand() / RAND_MAX) {
                swap(pos[x], pos[y]);
            }
        }
    }
    return;
}
```
**核心思想**：定义计算花费的函数 `get_cost`，模拟退火函数 `SA` 中不断随机交换两头牛的位置，根据花费和概率决定是否接受新解，更新最优答案。

#### HNFMS_tomoo（状态压缩 DP）
```cpp
int dp[1 << NMAX];
int main() {
    int n;
    scanf("%d", &n);
    int nbr[13][3];
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &nbr[i][0], &nbr[i][1], &nbr[i][2]);
        nbr[i][0]--;	nbr[i][1]--;	nbr[i][2]--;
    }
    dp[0] = 0;
    for (int subset = 1; subset < (1 << n); subset++) {
        int pending_links = 0;
        for (int i = 0; i < n; i++) {
            if (subset & (1<<i)) {
                pending_links += 3-(((subset >> nbr[i][0]) & 1) +
                                 ((subset >> nbr[i][1]) & 1) +
                                 ((subset >> nbr[i][2]) & 1));
            }
        }
        dp[subset] = infinite;
        for (int i = 0; i < n; i++) {
            if (subset & (1 << i)) {
                int cost = pending_links - 3 + 2 * (((subset >> nbr[i][0]) & 1) +
                                           ((subset >> nbr[i][1]) & 1) +
                                           ((subset >>  nbr[i][2]) & 1));
                dp[subset] = min(dp[subset], dp[subset & ~(1<<i)] + cost);
            }
        }
    }
    printf("%d\n", dp[(1 << n) - 1]);
}
```
**核心思想**：使用状态压缩 DP，通过枚举子集，计算每个子集的出边数量和加入一个点的代价，更新状态数组 `dp`，最终得到最优解。

### 最优关键思路或技巧
- **模拟退火**：通过随机交换元素位置，以一定概率接受较差解，跳出局部最优，找到更优解。
- **状态压缩 DP**：利用二进制表示集合状态，将问题的状态空间进行压缩，减少时间和空间复杂度。
- **随机化算法**：多次随机生成排列，通过大量尝试找到较优解，在数据范围较小时是一种简单有效的方法。

### 可拓展之处
同类型题或类似算法套路：
- 旅行商问题（TSP）：求经过所有城市且每个城市仅经过一次的最短路径，可使用模拟退火、状态压缩 DP 等算法。
- 背包问题的变种：如多维背包问题、带限制条件的背包问题，可尝试状态压缩 DP 求解。
- 图的最小生成树变种：如求满足某些条件的最小生成树，可结合启发式搜索或随机化算法。

### 推荐题目
- [P1337 [JSOI2004]平衡点 / 吊打XXX](https://www.luogu.org/problemnew/show/P1337)：模拟退火经典题目。
- [P3959 宝藏](https://www.luogu.org/problem/P3959)：可使用随机化算法或状态压缩 DP 求解。
- [P2704 [NOI2001] 炮兵阵地](https://www.luogu.org/problem/P2704)：状态压缩 DP 经典题目。

### 个人心得总结
- **模拟退火**：参数调整是关键，不同题目需要根据实际情况调整起始温度、终止温度和温度变化速度。可通过卡时限来多次运行模拟退火，提高找到最优解的概率。
- **暴力枚举与优化**：暴力枚举在数据范围较小时可作为基础解法，通过分析复杂度，可逐步优化到启发式搜索、状态压缩 DP 等更高效的算法。
- **随机化算法**：虽然是一种“乱搞”的方法，但在数据范围较小时，通过大量随机尝试，有很大概率找到较优解。 

---
处理用时：66.33秒