# 题目信息

# Epidemic in Monstropolis

## 题目描述

There was an epidemic in Monstropolis and all monsters became sick. To recover, all monsters lined up in queue for an appointment to the only doctor in the city.

Soon, monsters became hungry and began to eat each other.

One monster can eat other monster if its weight is strictly greater than the weight of the monster being eaten, and they stand in the queue next to each other. Monsters eat each other instantly. There are no monsters which are being eaten at the same moment. After the monster $ A $ eats the monster $ B $ , the weight of the monster $ A $ increases by the weight of the eaten monster $ B $ . In result of such eating the length of the queue decreases by one, all monsters after the eaten one step forward so that there is no empty places in the queue again. A monster can eat several monsters one after another. Initially there were $ n $ monsters in the queue, the $ i $ -th of which had weight $ a_{i} $ .

For example, if weights are $ [1,2,2,2,1,2] $ (in order of queue, monsters are numbered from $ 1 $ to $ 6 $ from left to right) then some of the options are:

1. the first monster can't eat the second monster because $ a_{1}=1 $ is not greater than $ a_{2}=2 $ ;
2. the second monster can't eat the third monster because $ a_{2}=2 $ is not greater than $ a_{3}=2 $ ;
3. the second monster can't eat the fifth monster because they are not neighbors;
4. the second monster can eat the first monster, the queue will be transformed to $ [3,2,2,1,2] $ .

After some time, someone said a good joke and all monsters recovered. At that moment there were $ k $ ( $ k<=n $ ) monsters in the queue, the $ j $ -th of which had weight $ b_{j} $ . Both sequences ( $ a $ and $ b $ ) contain the weights of the monsters in the order from the first to the last.

You are required to provide one of the possible orders of eating monsters which led to the current queue, or to determine that this could not happen. Assume that the doctor didn't make any appointments while monsters were eating each other.

## 说明/提示

In the first example, initially there were $ n=6 $ monsters, their weights are $ [1,2,2,2,1,2] $ (in order of queue from the first monster to the last monster). The final queue should be $ [5,5] $ . The following sequence of eatings leads to the final queue:

- the second monster eats the monster to the left (i.e. the first monster), queue becomes $ [3,2,2,1,2] $ ;
- the first monster (note, it was the second on the previous step) eats the monster to the right (i.e. the second monster), queue becomes $ [5,2,1,2] $ ;
- the fourth monster eats the mosnter to the left (i.e. the third monster), queue becomes $ [5,2,3] $ ;
- the finally, the third monster eats the monster to the left (i.e. the second monster), queue becomes $ [5,5] $ .

Note that for each step the output contains numbers of the monsters in their current order in the queue.

## 样例 #1

### 输入

```
6
1 2 2 2 1 2
2
5 5
```

### 输出

```
YES
2 L
1 R
4 L
3 L
```

## 样例 #2

### 输入

```
5
1 2 3 4 5
1
15
```

### 输出

```
YES
5 L
4 L
3 L
2 L
```

## 样例 #3

### 输入

```
5
1 1 1 3 3
3
2 1 6
```

### 输出

```
NO```

# AI分析结果



# Epidemic in Monstropolis（怪物城的疫情）

## 题目描述

怪物城爆发疫情后，所有怪物排成一列看病。饥饿的怪物会吃掉相邻且严格比自己轻的怪物，被吃掉的怪物消失，吃怪的怪物重量增加，队列长度减一。最终需要判断能否通过一系列吃怪操作，将初始队列变为目标队列，并给出操作步骤。

## 算法分类
构造、贪心

## 题解分析与结论

### 核心思路
1. **可行性校验**：检查初始队列与目标队列的总重量是否相等，否则直接无解。
2. **分段匹配**：将初始队列分割为连续段，每段重量和对应目标队列的每个元素。若无法分段或某段无法合并成单个元素，则无解。
3. **合并策略**：对每个段，找到最大值作为核心，优先向左右扩展合并较小元素。若段内全相同且长度>1则无法合并。

### 最优题解亮点

#### 题解1：Soul_Love（4星）
- **亮点**：分段后实时维护数组结构，通过贪心合并确保最大值主导。
- **关键代码**：
```cpp
int work(int l,int r,int e) {
    while(l<r) {
        int maxx=-INF, ff=0;
        for(int i=l;i<=r;i++) maxx=max(maxx,a[i]);
        for(int i=l;i<=r;i++) {
            if(a[i]==maxx) {
                if(i>l && a[i]>a[i-1]) { // 向左合并
                    ans[++k] = {i-R[e-1]+e-1, 'L'};
                    a[i-1] += a[i];
                    for(int j=i;j<r;j++) a[j]=a[j+1];
                    r--; ff=1; break;
                }
                if(i<r && a[i]>a[i+1]) { // 向右合并
                    ans[++k] = {i-R[e-1]+e-1, 'R'};
                    a[i] += a[i+1];
                    for(int j=i+1;j<r;j++) a[j]=a[j+1];
                    r--; ff=1; break;
                }
            }
        }
        if(!ff) return 0;
    }
    return 1;
}
```
- **核心思想**：动态调整数组，每次合并后压缩数组，保证后续操作正确性。

#### 题解2：Darling_ZX（4星）
- **亮点**：预处理分段，记录每段边界和最大值位置，通过数学计算生成步骤索引。
- **关键代码**：
```cpp
for(int i=1;i<=m;i++) {
    int nm = ans[i].maxx - ans[i-1].id;
    for(int j=ans[i].maxx; j>ans[i-1].id+1; j--) {
        printf("%d L\n", i-1 + j - ans[i-1].id);
    }
    for(int j=ans[i].maxx+1; j<=ans[i].id; j++) {
        printf("%d R\n", nm + i-1);
    }
}
```
- **核心思想**：通过前缀和快速定位段边界，根据最大值位置分左右合并，避免实时修改数组。

### 关键优化点
- **前缀和分段**：快速验证每段和的正确性。
- **贪心合并方向**：以段内最大值为核心，优先合并较小侧，确保合并路径可行。
- **索引动态计算**：根据原始分段位置计算实时队列中的索引，避免操作冲突。

### 心得与拓展
- **调试教训**：合并后实时队列索引变化需精确计算，否则步骤输出错误。
- **同类题目**：类似分段构造问题，如合并石子、区间划分等。
- **举一反三**：若要求不同合并顺序（如字典序最小），需调整最大值选择策略。

### 推荐练习
1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090) - 贪心合并策略
2. [P1880 石子合并](https://www.luogu.com.cn/problem/P1880) - 区间动态规划
3. [P1496 火烧赤壁](https://www.luogu.com.cn/problem/P1496) - 区间合并与离散化

---
处理用时：175.42秒