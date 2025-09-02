# 题目信息

# Koa and the Beach (Easy Version)

## 题目描述

The only difference between easy and hard versions is on constraints. In this version constraints are lower. You can make hacks only if all versions of the problem are solved.

Koa the Koala is at the beach!

The beach consists (from left to right) of a shore, $ n+1 $ meters of sea and an island at $ n+1 $ meters from the shore.

She measured the depth of the sea at $ 1, 2, \dots, n $ meters from the shore and saved them in array $ d $ . $ d_i $ denotes the depth of the sea at $ i $ meters from the shore for $ 1 \le       i \le n $ .

Like any beach this one has tide, the intensity of the tide is measured by parameter $ k $ and affects all depths from the beginning at time $ t=0 $  in the following way:

- For a total of $ k $ seconds, each second, tide increases all depths by $ 1 $ .
- Then, for a total of $ k $ seconds, each second, tide decreases all depths by $ 1 $ .
- This process repeats again and again (ie. depths increase for $ k $ seconds then decrease for $ k $ seconds and so on ...). Formally, let's define $ 0 $ -indexed array $ p = [0, 1, 2,           \ldots, k - 2, k - 1, k, k - 1, k - 2, \ldots, 2, 1] $ of length $ 2k $ . At time $ t $ ( $ 0 \le t $ ) depth at $ i $ meters from the shore equals $ d_i + p[t \bmod 2k] $ ( $ t \bmod 2k $ denotes the remainder of the division of $ t $ by $ 2k $ ). Note that the changes occur instantaneously after each second, see the notes for better understanding.

At time $ t=0 $ Koa is standing at the shore and wants to get to the island. Suppose that at some time $ t $ ( $ 0 \le t $ ) she is at $ x $ ( $ 0 \le x \le n $ ) meters from the shore:

- In one second Koa can swim $ 1 $ meter further from the shore ( $ x $ changes to $ x+1 $ ) or not swim at all ( $ x $ stays the same), in both cases $ t $ changes to $ t+1 $ .
- As Koa is a bad swimmer, the depth of the sea at the point where she is can't exceed $ l $ at integer points of time (or she will drown). More formally, if Koa is at $ x $ ( $ 1 \le x         \le n $ ) meters from the shore at the moment $ t $ (for some integer $ t\ge 0 $ ), the depth of the sea at this point — $ d_x + p[t \bmod 2k] $ — can't exceed $ l $ . In other words, $ d_x + p[t \bmod 2k] \le l $ must hold always.
- Once Koa reaches the island at $ n+1 $ meters from the shore, she stops and can rest. Note that while Koa swims tide doesn't have effect on her (ie. she can't drown while swimming). Note that Koa can choose to stay on the shore for as long as she needs and neither the shore or the island are affected by the tide (they are solid ground and she won't drown there).

Koa wants to know whether she can go from the shore to the island. Help her!

## 说明/提示

In the following $ s $ denotes the shore, $ i $ denotes the island, $ x $ denotes distance from Koa to the shore, the underline denotes the position of Koa, and values in the array below denote current depths, affected by tide, at $ 1, 2,       \dots, n $ meters from the shore.

In test case $ 1 $ we have $ n = 2, k = 1, l = 1, p = [ 0, 1 ] $ .

Koa wants to go from shore (at $ x = 0 $ ) to the island (at $ x = 3 $ ). Let's describe a possible solution:

- Initially at $ t = 0 $ the beach looks like this: $ [\underline{s}, 1, 0, i] $ .
- At $ t = 0 $ if Koa would decide to swim to $ x = 1 $ , beach would look like: $ [s, \underline{2}, 1, i] $ at $ t =         1 $ , since $ 2 > 1 $ she would drown. So Koa waits $ 1 $ second instead and beach looks like $ [\underline{s}, 2, 1,         i] $ at $ t = 1 $ .
- At $ t = 1 $ Koa swims to $ x = 1 $ , beach looks like $ [s, \underline{1}, 0, i] $ at $ t = 2 $ . Koa doesn't drown because $ 1 \le 1 $ .
- At $ t = 2 $ Koa swims to $ x = 2 $ , beach looks like $ [s, 2, \underline{1}, i] $ at $ t = 3 $ . Koa doesn't drown because $ 1 \le 1 $ .
- At $ t = 3 $ Koa swims to $ x = 3 $ , beach looks like $ [s, 1, 0, \underline{i}] $ at $ t = 4 $ .
- At $ t = 4 $ Koa is at $ x = 3 $ and she made it!

We can show that in test case $ 2 $ Koa can't get to the island.

## 样例 #1

### 输入

```
7
2 1 1
1 0
5 2 3
1 2 3 2 2
4 3 4
0 2 4 3
2 3 5
3 0
7 2 3
3 0 2 1 3 0 1
7 1 4
4 4 3 0 2 4 2
5 2 3
1 2 3 2 2```

### 输出

```
Yes
No
Yes
Yes
Yes
No
No```

# AI分析结果

### 题目内容（中文重写）
# Koa与海滩（简单版本）

## 题目描述
简单版本和困难版本的唯一区别在于约束条件。在这个版本中，约束条件更宽松。只有当所有版本的问题都被解决后，你才能进行 hack 操作。

树袋熊 Koa 正在海滩上！

海滩（从左到右）由一片海岸、$n + 1$ 米的海域和一个距离海岸 $n + 1$ 米的岛屿组成。

她测量了距离海岸 $1, 2, \dots, n$ 米处的海水深度，并将其存储在数组 $d$ 中。$d_i$ 表示距离海岸 $i$ 米处的海水深度，其中 $1 \le i \le n$。

和其他海滩一样，这片海滩也有潮汐，潮汐的强度用参数 $k$ 来衡量，并且从时间 $t = 0$ 开始就会对所有深度产生如下影响：
- 在总共 $k$ 秒的时间内，每秒潮汐会使所有深度增加 $1$。
- 然后，在总共 $k$ 秒的时间内，每秒潮汐会使所有深度减少 $1$。
- 这个过程会不断重复（即深度先增加 $k$ 秒，然后减少 $k$ 秒，如此循环……）。形式上，定义一个从 $0$ 开始索引的数组 $p = [0, 1, 2, \ldots, k - 2, k - 1, k, k - 1, k - 2, \ldots, 2, 1]$，其长度为 $2k$。在时间 $t$（$0 \le t$），距离海岸 $i$ 米处的深度等于 $d_i + p[t \bmod 2k]$（$t \bmod 2k$ 表示 $t$ 除以 $2k$ 的余数）。请注意，每次秒数变化后，深度的变化是瞬间发生的，查看注释可以更好地理解。

在时间 $t = 0$ 时，Koa 站在海岸上，她想前往岛屿。假设在某个时间 $t$（$0 \le t$），她距离海岸 $x$（$0 \le x \le n$）米：
- 在一秒内，Koa 可以向远离海岸的方向游 $1$ 米（$x$ 变为 $x + 1$），或者不游动（$x$ 保持不变），在这两种情况下，$t$ 都会变为 $t + 1$。
- 由于 Koa 游泳技术不佳，在整数时刻，她所在位置的海水深度不能超过 $l$（否则她会溺水）。更正式地说，如果 Koa 在某个整数时刻 $t$（$t \ge 0$）位于距离海岸 $x$（$1 \le x \le n$）米的位置，那么该位置的海水深度 $d_x + p[t \bmod 2k]$ 不能超过 $l$。换句话说，必须始终满足 $d_x + p[t \bmod 2k] \le l$。
- 一旦 Koa 到达距离海岸 $n + 1$ 米的岛屿，她就会停下来休息。请注意，在 Koa 游泳时，潮汐对她没有影响（即她在游泳时不会溺水）。此外，Koa 可以选择在海岸上停留任意长的时间，并且海岸和岛屿都不受潮汐影响（它们是坚实的地面，她在那里不会溺水）。

Koa 想知道她是否能够从海岸到达岛屿。请帮助她！

## 说明/提示
在下面的描述中，$s$ 表示海岸，$i$ 表示岛屿，$x$ 表示 Koa 距离海岸的距离，下划线表示 Koa 的位置，数组中的值表示在距离海岸 $1, 2, \dots, n$ 米处受潮汐影响的当前深度。

在测试用例 1 中，我们有 $n = 2$，$k = 1$，$l = 1$，$p = [0, 1]$。

Koa 想从海岸（$x = 0$）前往岛屿（$x = 3$）。下面描述一个可能的解决方案：
- 初始时，在 $t = 0$ 时，海滩的情况如下：$[\underline{s}, 1, 0, i]$。
- 在 $t = 0$ 时，如果 Koa 决定游到 $x = 1$，那么在 $t = 1$ 时，海滩的情况将变为：$[s, \underline{2}, 1, i]$，由于 $2 > 1$，她会溺水。因此，Koa 选择等待 1 秒，在 $t = 1$ 时，海滩的情况为 $[\underline{s}, 2, 1, i]$。
- 在 $t = 1$ 时，Koa 游到 $x = 1$，在 $t = 2$ 时，海滩的情况为 $[s, \underline{1}, 0, i]$。Koa 不会溺水，因为 $1 \le 1$。
- 在 $t = 2$ 时，Koa 游到 $x = 2$，在 $t = 3$ 时，海滩的情况为 $[s, 2, \underline{1}, i]$。Koa 不会溺水，因为 $1 \le 1$。
- 在 $t = 3$ 时，Koa 游到 $x = 3$，在 $t = 4$ 时，海滩的情况为 $[s, 1, 0, \underline{i}]$。
- 在 $t = 4$ 时，Koa 到达了 $x = 3$，她成功了！

我们可以证明，在测试用例 2 中，Koa 无法到达岛屿。

## 样例 #1
### 输入
```
7
2 1 1
1 0
5 2 3
1 2 3 2 2
4 3 4
0 2 4 3
2 3 5
3 0
7 2 3
3 0 2 1 3 0 1
7 1 4
4 4 3 0 2 4 2
5 2 3
1 2 3 2 2
```

### 输出
```
Yes
No
Yes
Yes
Yes
No
No
```

### 算法分类
动态规划

### 综合分析与结论
这些题解主要围绕判断 Koa 是否能从海岸游到岛屿展开，多数采用动态规划的思路，也有使用深度优先搜索的方法。

- **思路对比**：大部分动态规划题解通过定义状态 $dp_{i,j}$ 表示在第 $i$ 个位置、$j$ 时刻的状态是否可实现，依据潮汐和深度的关系进行状态转移；深度优先搜索题解则通过模拟 Koa 的每个可能动作，对每个状态和动作进行 dfs 来判断是否能到达岛屿。
- **算法要点对比**：动态规划题解的关键在于确定状态定义、转移方程和时间上限；深度优先搜索题解的关键在于定义合适的状态和动作，并利用集合记录已访问状态避免重复计算。
- **解决难点对比**：动态规划题解的难点在于确定合理的时间上限；深度优先搜索题解的难点在于状态的定义和避免重复搜索。

### 所选题解
- **strange757（4星）**
    - **关键亮点**：思路清晰，详细阐述了动态规划的状态定义和转移方程，代码实现规范，对时间上限的分析较为合理。
- **liuyongle（4星）**
    - **关键亮点**：采用深度优先搜索的方法，通过定义合适的状态和动作进行模拟，代码简洁，利用集合记录已访问状态避免重复计算。
- **ys_kylin__（4星）**
    - **关键亮点**：动态规划思路明确，对潮汐的判断和状态转移的处理较为清晰，代码实现简单易懂。

### 重点代码
#### strange757 的动态规划代码
```cpp
const int N = 205;
int t, n, k, l, d[N], p[N], mod;
int f[N * N][105];
int main(){
    scanf("%d", &t);
    while(t--){
        scanf("%d%d%d", &n, &k, &l);
        mod = 2 * k;
        bool f1 = 0;
        for(int i = 1; i <= n; i++) scanf("%d", &d[i]);
        for(int i = 0; i <= k; i++) p[i] = i;
        for(int i = 2 * k - 1; i >= k + 1; i--) p[i] = 2*k - i;
        for(int i = 0; i <= k * n + n; i++) f[i][0] = 1;
        for(int i = 1; i <= k * n + n; i++){
            for(int j = 1; j <= n; j++){
                f[i][j] = 0;
                if(d[j] + p[i%mod] <= l) f[i][j] = f[i - 1][j]|f[i - 1][j - 1];
            }
            if(f[i][n]) {
                printf("Yes\n"), f1 = 1;
                break;
            }
        }
        if(!f1)printf("No\n");
    }
    return 0;
}
```
**核心实现思想**：定义 $dp$ 数组 $f[i][j]$ 表示时间 $i$ 时是否能游到 $j$ 位置，根据潮汐和深度的关系进行状态转移，当 $d[j] + p[i\%mod] \le l$ 时，$f[i][j] = f[i - 1][j]|f[i - 1][j - 1]$，并通过循环枚举时间和位置，判断是否能到达最后一个位置。

#### liuyongle 的深度优先搜索代码
```cpp
int main() {
    int test;
    cin>>test;
    while(test--) {
        int n,k,l;
        cin>>n>>k>>l;
        vector<int> d(n+2,-k);
        for(int i=1;i<=n;++i)
            cin>>d[i];
        set<tuple<int,int,bool>> mark;
        function<bool(int,int,bool)> go=[&](int pos,int tide,bool down) {
            if(pos>n)
                return true;
            if(mark.find({pos,tide,down})!=mark.end())
                return false;
            mark.insert({pos,tide,down});
            tide+=down?-1:+1;
            if(!tide)
                down=false;
            if(tide==k)
                down=true;
            if(d[pos]+tide<=l && go(pos,tide,down))
                return true;
            if(d[pos+1]+tide<=l && go(pos+1,tide,down))
                return true;
            return false;
        };
        if(go(0,0,false))
            cout<<"Yes\n";
        else cout<<"No\n";
    }
    return 0;
}
```
**核心实现思想**：定义状态 $\{pos,tide,down\}$ 表示 Koa 的当前位置、当前潮汐的增量和潮汐是否正在减小，通过深度优先搜索对每个状态和动作进行模拟，利用集合 `mark` 记录已访问状态，避免重复计算，若能到达岛屿则返回 `true`。

#### ys_kylin__ 的动态规划代码
```cpp
int d[105];
int f[105][1005];
int main() {
    int t;
    scanf("%d",&t);
    while(t--) {
        memset(f,0,sizeof f);
        int n,k,l;
        scanf("%d%d%d",&n,&k,&l);
        for(int i=1;i<=n;i++) scanf("%d",&d[i]);
        for(int i=0;i<=1000;i++) f[0][i]=1;
        for(int i=1;i<=n;i++) {
            for(int j=1;j<=1000;j++) {
                int tmp=j,cx=0;
                tmp%=(2*k);
                if(tmp>k) cx=2*k-tmp;
                else cx=tmp;
                cx+=d[i];
                if(cx>l) f[i][j]=0;
                else {
                    if(f[i-1][j-1]==1 || f[i][j-1]==1) f[i][j]=1;
                }
            }
        }
        for(int i=1;i<=1000;i++) {
            if(f[n][i]==1) {
                printf("Yes\n");
                goto brk;
            }
        }
        printf("No\n");
        brk:
            ;
    }
    return 0;
}
```
**核心实现思想**：定义 $dp$ 数组 $f[i][j]$ 表示在 $i$ 这个点 $j$ 时刻能否在这里，根据潮汐和深度的关系判断是否会被淹，若不会被淹则根据上一个时刻的状态进行转移，最后判断是否能到达最后一个位置。

### 最优关键思路或技巧
- 动态规划中合理定义状态和转移方程，通过枚举时间和位置来判断是否能到达目标位置。
- 深度优先搜索中定义合适的状态和动作，利用集合记录已访问状态避免重复计算。

### 拓展思路
同类型题或类似算法套路：可以考虑增加更多的限制条件，如不同位置有不同的游泳速度限制；或者改变潮汐的变化规律，如潮汐变化不是简单的周期性变化，而是更复杂的函数关系。

### 推荐洛谷题目
- P1048 [NOIP2005 普及组] 采药
- P1216 [USACO1.5] 数字三角形 Number Triangles
- P1002 [NOIP2002 普及组] 过河卒

### 个人心得摘录与总结
- ys_kylin__：提到这是比赛赛题，当时做出来了，觉得挺简单的，说明对这类动态规划题目有一定的掌握和自信。 

---
处理用时：83.97秒