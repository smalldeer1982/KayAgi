# 题目信息

# Firecrackers

## 题目描述

Consider a long corridor which can be divided into $ n $ square cells of size $ 1 \times 1 $ . These cells are numbered from $ 1 $ to $ n $ from left to right.

There are two people in this corridor, a hooligan and a security guard. Initially, the hooligan is in the $ a $ -th cell, the guard is in the $ b $ -th cell ( $ a \ne b $ ).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1468D/09bf6496fc483fb53942bc6e21c9eb76729eb3aa.png)One of the possible situations. The corridor consists of $ 7 $ cells, the hooligan is in the $ 3 $ -rd cell, the guard is in the $ 6 $ -th ( $ n = 7 $ , $ a = 3 $ , $ b = 6 $ ).There are $ m $ firecrackers in the hooligan's pocket, the $ i $ -th firecracker explodes in $ s_i $ seconds after being lit.

The following events happen each second (sequentially, exactly in the following order):

1. firstly, the hooligan either moves into an adjacent cell (from the cell $ i $ , he can move to the cell $ (i + 1) $ or to the cell $ (i - 1) $ , and he cannot leave the corridor) or stays in the cell he is currently. If the hooligan doesn't move, he can light one of his firecrackers and drop it. The hooligan can't move into the cell where the guard is;
2. secondly, some firecrackers that were already dropped may explode. Formally, if the firecracker $ j $ is dropped on the $ T $ -th second, then it will explode on the $ (T + s_j) $ -th second (for example, if a firecracker with $ s_j = 2 $ is dropped on the $ 4 $ -th second, it explodes on the $ 6 $ -th second);
3. finally, the guard moves one cell closer to the hooligan. If the guard moves to the cell where the hooligan is, the hooligan is caught.

Obviously, the hooligan will be caught sooner or later, since the corridor is finite. His goal is to see the maximum number of firecrackers explode before he is caught; that is, he will act in order to maximize the number of firecrackers that explodes before he is caught.

Your task is to calculate the number of such firecrackers, if the hooligan acts optimally.

## 说明/提示

In the first test case, the hooligan should act, for example, as follows:

- second 1: drop the second firecracker, so it will explode on the $ 5 $ -th second. The guard moves to the cell $ 5 $ ;
- second 2: move to the cell $ 2 $ . The guard moves to the cell $ 4 $ ;
- second 3: drop the first firecracker, so it will explode on the $ 4 $ -th second. The guard moves to the cell $ 3 $ ;
- second 4: move to the cell $ 1 $ . The first firecracker explodes. The guard moves to the cell $ 2 $ ;
- second 5: stay in the cell $ 1 $ . The second firecracker explodes. The guard moves to the cell $ 1 $ and catches the hooligan.

## 样例 #1

### 输入

```
3
7 2 3 6
1 4
7 2 3 6
5 1
7 2 3 6
4 4```

### 输出

```
2
1
1```

# AI分析结果

### 题目中文重写
# 鞭炮

## 题目描述
考虑一条长长的走廊，它可以被分成 $n$ 个 $1×1$ 的正方形格子。这些格子从左到右依次编号为 $1$ 到 $n$。

走廊里有两个人，一个是小混混，一个是保安。初始时，小混混在第 $a$ 个格子，保安在第 $b$ 个格子（$a \ne b$）。

![一种可能的情况。走廊由 7 个格子组成，小混混在第 3 个格子，保安在第 6 个格子（$n = 7$，$a = 3$，$b = 6$）](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1468D/09bf6496fc483fb53942bc6e21c9eb76729eb3aa.png)

小混混的口袋里有 $m$ 个鞭炮，第 $i$ 个鞭炮在点燃后 $s_i$ 秒爆炸。

每秒会按以下顺序依次发生以下事件：
1. 首先，小混混可以移动到相邻的格子（从第 $i$ 个格子，他可以移动到第 $(i + 1)$ 个格子或第 $(i - 1)$ 个格子，且不能离开走廊），也可以停留在当前格子。如果小混混不移动，他可以点燃并扔下一个鞭炮。小混混不能移动到保安所在的格子。
2. 其次，一些已经扔下的鞭炮可能会爆炸。具体来说，如果鞭炮 $j$ 在第 $T$ 秒被扔下，那么它将在第 $(T + s_j)$ 秒爆炸（例如，如果一个 $s_j = 2$ 的鞭炮在第 4 秒被扔下，它将在第 6 秒爆炸）。
3. 最后，保安向小混混移动一个格子。如果保安移动到小混混所在的格子，小混混就会被抓住。

显然，由于走廊长度有限，小混混迟早会被抓住。他的目标是在被抓住之前看到最多的鞭炮爆炸，即他会采取行动使被抓住前爆炸的鞭炮数量最大化。

你的任务是计算如果小混混采取最优行动，会有多少个鞭炮爆炸。

## 说明/提示
在第一个测试用例中，小混混可以按以下方式行动：
- 第 1 秒：扔下第二个鞭炮，它将在第 5 秒爆炸。保安移动到第 5 个格子。
- 第 2 秒：移动到第 2 个格子。保安移动到第 4 个格子。
- 第 3 秒：扔下第一个鞭炮，它将在第 4 秒爆炸。保安移动到第 3 个格子。
- 第 4 秒：移动到第 1 个格子。第一个鞭炮爆炸。保安移动到第 2 个格子。
- 第 5 秒：停留在第 1 个格子。第二个鞭炮爆炸。保安移动到第 1 个格子并抓住小混混。

## 样例 #1
### 输入
```
3
7 2 3 6
1 4
7 2 3 6
5 1
7 2 3 6
4 4
```
### 输出
```
2
1
1
```

### 算法分类
二分

### 综合分析与结论
- **思路对比**：
    - ForwardStar 的题解采用二分答案的方法，通过 `check` 函数判断某个答案是否可行，核心是先扔够枚举的鞭炮数，再逃跑拖延时间，比较拖延时间和最后炸的鞭炮时间。
    - Fa1thful 的题解采用贪心策略，先尽可能多地放鞭炮，再跑路为鞭炮爆炸争取时间，且鞭炮按爆炸时间从高到低排序。
    - Chenyichen0420 的题解同样利用二分，预处理出每个鞭炮到最后一个鞭炮开始燃放的爆炸时间和所需等待时间，与最大等待时间对比。
- **算法要点对比**：
    - ForwardStar 主要是二分答案和 `check` 函数的实现，时间复杂度 $O(m\log m)$。
    - Fa1thful 是贪心策略的制定和实现，涉及排序和遍历。
    - Chenyichen0420 是二分和预处理，声称排除排序后时间复杂度略优。
- **解决难点对比**：
    - ForwardStar 解决了如何判断二分答案是否可行的问题，关键在于合理安排扔鞭炮和逃跑的顺序。
    - Fa1thful 解决了贪心策略的正确性问题，通过手推样例说明先放鞭炮再跑路的合理性。
    - Chenyichen0420 解决了如何预处理时间和利用二分找到最优解的问题。

### 题解评分与展示
- **ForwardStar 的题解（4星）**：
    - **关键亮点**：思路清晰，二分答案的方法逻辑明确，代码实现简洁，时间复杂度合理。
    - **核心代码**：
```cpp
bool check(int p){
    if(p>=dis)return false;
    int mx=0;
    for(int i=1;i<=p;i++){
        mx=max(mx,a[i]+p-i+1);
    }
    return mx<=ddis;
}
int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d%d%d%d",&n,&m,&x,&y);
        for(int i=1;i<=m;i++)scanf("%d",&a[i]);
        sort(a+1,a+1+m);
        int l=0,r=m;
        dis=abs(x-y);
        if(x>y)ddis=dis+n-x;
        else ddis=dis+x-1;
        while(l<r){
            int mid=(l+r+1)/2;
            if(check(mid))l=mid;
            else r=mid-1;
        }
        printf("%d\n",l);
    }
    return 0;
}
```
核心实现思想：`check` 函数用于判断枚举的鞭炮数 $p$ 是否可行，通过计算最后一个鞭炮爆炸的时间与最大拖延时间比较。主函数中进行二分查找，不断调整左右边界，直到找到最优解。

### 最优关键思路或技巧
- 二分答案的方法可以将问题转化为判断某个答案是否可行，降低问题的复杂度。
- 合理安排扔鞭炮和逃跑的顺序，先扔爆炸时间长的鞭炮，再逃跑拖延时间。

### 拓展思路
同类型题可能会改变人物的移动规则、鞭炮的爆炸规则或增加其他限制条件，但核心思路仍然是通过合理的策略和算法找到最优解。类似算法套路包括二分查找和贪心策略的结合，通过判断可行性来缩小答案范围。

### 推荐洛谷题目
- P1873 [COCI 2011/2012 #5] EKO / 砍树
- P2678 [NOIP2015 提高组] 跳石头
- P3853 [TJOI2007] 路标设置

---
处理用时：49.52秒