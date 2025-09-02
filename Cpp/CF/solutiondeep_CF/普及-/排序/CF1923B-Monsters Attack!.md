# 题目信息

# Monsters Attack!

## 题目描述

You are playing a computer game. The current level of this game can be modeled as a straight line. Your character is in point $ 0 $ of this line. There are $ n $ monsters trying to kill your character; the $ i $ -th monster has health equal to $ a_i $ and is initially in the point $ x_i $ .

Every second, the following happens:

- first, you fire up to $ k $ bullets at monsters. Each bullet targets exactly one monster and decreases its health by $ 1 $ . For each bullet, you choose its target arbitrary (for example, you can fire all bullets at one monster, fire all bullets at different monsters, or choose any other combination). Any monster can be targeted by a bullet, regardless of its position and any other factors;
- then, all alive monsters with health $ 0 $ or less die;
- then, all alive monsters move $ 1 $ point closer to you (monsters to the left of you increase their coordinates by $ 1 $ , monsters to the right of you decrease their coordinates by $ 1 $ ). If any monster reaches your character (moves to the point $ 0 $ ), you lose.

Can you survive and kill all $ n $ monsters without letting any of them reach your character?

## 说明/提示

In the first example, you can act as follows:

- during the $ 1 $ -st second, fire $ 1 $ bullet at the $ 1 $ -st monster and $ 1 $ bullet at the $ 3 $ -rd monster. Then the $ 1 $ -st monster dies, the $ 2 $ -nd and the $ 3 $ -rd monster move closer;
- during the $ 2 $ -nd second, fire $ 2 $ bullets at the $ 2 $ -nd monster. Then the $ 2 $ -nd monster dies, the $ 3 $ -rd monster moves closer;
- during the $ 3 $ -rd second, fire $ 2 $ bullets at the $ 3 $ -rd monster. Then the $ 3 $ -rd monster dies.

In the second example, you can fire only $ 1 $ bullet, so you can kill only one of the two monsters during the $ 1 $ -st second. Then, the remaining monster moves closer and kills your character.

## 样例 #1

### 输入

```
5
3 2
1 2 3
-1 2 3
2 1
1 1
-1 1
4 10
3 4 2 5
-3 -2 1 3
5 3
2 1 3 2 5
-3 -2 3 4 5
2 1
1 2
1 2```

### 输出

```
YES
NO
YES
YES
NO```

# AI分析结果

### 题目中文重写
# 怪物来袭！

## 题目描述
你正在玩一款电脑游戏。当前游戏关卡可以建模为一条直线。你的角色位于这条直线的 0 点处。有 n 个怪物试图杀死你的角色；第 i 个怪物的生命值为 $a_i$，初始位置在 $x_i$ 点。

每秒会发生以下事件：
- 首先，你最多可以向怪物发射 k 发子弹。每发子弹恰好攻击一个怪物，使其生命值减 1。对于每发子弹，你可以任意选择攻击目标（例如，你可以将所有子弹都攻击一个怪物，也可以将所有子弹分别攻击不同的怪物，或者选择其他任意组合）。任何怪物都可以成为子弹的攻击目标，无论其位置或其他因素如何。
- 然后，所有生命值小于等于 0 的存活怪物死亡。
- 接着，所有存活的怪物向你移动 1 个单位（位于你左侧的怪物坐标加 1，位于你右侧的怪物坐标减 1）。如果有任何怪物到达你的角色所在位置（移动到 0 点），你就输了。

你能否在不让任何怪物到达你的角色的情况下存活并杀死所有 n 个怪物？

## 说明/提示
在第一个样例中，你可以按以下方式行动：
- 在第 1 秒，向第 1 个怪物发射 1 发子弹，向第 3 个怪物发射 1 发子弹。然后第 1 个怪物死亡，第 2 个和第 3 个怪物向你靠近。
- 在第 2 秒，向第 2 个怪物发射 2 发子弹。然后第 2 个怪物死亡，第 3 个怪物向你靠近。
- 在第 3 秒，向第 3 个怪物发射 2 发子弹。然后第 3 个怪物死亡。

在第二个样例中，你每秒只能发射 1 发子弹，因此在第 1 秒你只能杀死两个怪物中的一个。然后，剩下的怪物会向你靠近并杀死你的角色。

## 样例 #1
### 输入
```
5
3 2
1 2 3
-1 2 3
2 1
1 1
-1 1
4 10
3 4 2 5
-3 -2 1 3
5 3
2 1 3 2 5
-3 -2 3 4 5
2 1
1 2
1 2
```

### 输出
```
YES
NO
YES
YES
NO
```

### 综合分析与结论
这些题解的核心思路都是采用贪心算法来解决问题。由于怪物从两个方向向原点移动，且左右两边距离相同的怪物本质相同，所以可将怪物坐标取绝对值。主要通过两种方式实现：一是用桶记录每个位置的怪物总血量，然后从近到远遍历，维护剩余子弹数，若某位置的怪物总血量大于剩余子弹数则失败；二是将怪物按距离排序后逐个处理，计算击杀每个怪物所需时间，若怪物在击杀前到达原点则失败。

### 通用建议与扩展思路
- **思路方面**：遇到类似有多个对象按一定规则移动和交互的问题，可考虑贪心策略，优先处理最关键或最紧急的对象。同时，对于具有对称性的问题，可通过取绝对值等方式简化处理。
- **代码实现**：使用桶来统计和记录信息是一种常见且有效的方法，能避免复杂的排序和查找操作。在处理多组数据时，注意数组的初始化，防止数据冲突。
- **拓展**：同类型题目可能会增加更多的条件或规则，如怪物有不同的移动速度、有特殊技能等。类似的算法套路包括区间贪心、活动选择问题等，可通过对问题进行建模和抽象，找到最优的处理顺序。

### 推荐题目
1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)：考察贪心算法，每次选择最小的两个果子合并。
2. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)：通过排序实现贪心策略，使总等待时间最短。
3. [P2240 部分背包问题](https://www.luogu.com.cn/problem/P2240)：贪心选择单位价值最高的物品。

### 重点代码及核心思想
#### 桶计数实现
```cpp
// 以Hacker_Cracker的题解为例
#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;
typedef long long ll;
const int N = 3e5 + 10;
ll t[N] , a[N] , p[N];
int abs_read (void) {
    int f = 1 , res = 0;
    char ch = getchar ();
    while (ch < '0' || ch > '9') {
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        res = res * 10 + (ch - '0');
        ch = getchar();
    }
    return res;
}
int main() {
    ll __T = abs_read() ;
    while (__T --) {
        int n = abs_read() , k = abs_read(), f = 1;
        ll sum = 0;
        for (int i = 1 ; i <= n ; i ++) t[i] = 0 , a[i] = abs_read();
        for (int i = 1 ; i <= n ; i ++) {
            p[i] =  abs_read();
            t[p[i]] += a[i];
        }
        for (int i = 1 ; i <= n ; i ++) {
            sum = sum + k - t[i];
            if (sum >= 0) f = 1;
            else {
                f = 0;
                break;
            }
        }
        if (f) puts ("YES");
        else puts ("NO");
    }
    return 0;
}
```
核心思想：用桶 `t` 记录每个位置的怪物总血量，从近到远遍历，维护剩余子弹数 `sum`，若 `sum` 小于 0 则失败。

#### 排序后逐个处理实现
```cpp
// 以jiangjiangQwQ的题解为例
#include<iostream>
#include<algorithm>
using namespace std;
const int N=3e5+5;
int T,n,k;
struct Node{
    int a,x;
}inp[N];
bool cmp(Node x,Node y){
    if(x.x!=y.x) return x.x<y.x;
    else return x.a<y.a;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n>>k;
        for(int i=1;i<=n;i++){
            cin>>inp[i].a;
        }
        for(int i=1;i<=n;i++){
            cin>>inp[i].x;
            inp[i].x=abs(inp[i].x);
        }
        stable_sort(inp+1,inp+n+1,cmp);
        int bullet=k,diff=0,flag=1;
        for(int i=1;i<=n;i++){
            if(bullet>=inp[i].a){
                bullet-=inp[i].a;
            }else{
                inp[i].a-=bullet;
                bullet=0;
                int t=(inp[i].a-1)/k+1;
                bullet=t*k-inp[i].a;
                diff+=t;
                if(inp[i].x-diff<=0){
                    flag=0;
                    break;
                }
            }
        }
        puts(flag==1?"YES":"NO");
    }
    return 0;
}
```
核心思想：将怪物按距离排序，逐个处理，计算击杀每个怪物所需时间，若怪物在击杀前到达原点则失败。

### 个人心得摘录
- **QoQ_**：提示不开 `long long` 见祖宗，强调了数据范围大时使用合适数据类型的重要性。 

---
处理用时：48.76秒