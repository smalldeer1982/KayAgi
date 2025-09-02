# 题目信息

# Monsters

## 题目描述

Monocarp is playing yet another computer game. And yet again, his character is killing some monsters. There are $ n $ monsters, numbered from $ 1 $ to $ n $ , and the $ i $ -th of them has $ a_i $ health points initially.

Monocarp's character has an ability that deals $ k $ damage to the monster with the highest current health. If there are several of them, the one with the smaller index is chosen. If a monster's health becomes less than or equal to $ 0 $ after Monocarp uses his ability, then it dies.

Monocarp uses his ability until all monsters die. Your task is to determine the order in which monsters will die.

## 说明/提示

In the first example, the health points change as follows: $ [1, 2, \underline{3}] \rightarrow [1, \underline{2}, 1] \rightarrow [\underline{1}, 0, 1] \rightarrow [-1, 0, \underline{1}] \rightarrow [-1, 0, -1] $ . The monster that is going to take damage the next time Monocarp uses his ability is underlined.

In the second example, the health points change as follows: $ [\underline{1}, 1] \rightarrow [-2, \underline{1}] \rightarrow [-2, -2] $ .

In the third example, the health points change as follows: $ [2, \underline{8}, 3, 5] \rightarrow [2, \underline{5}, 3, 5] \rightarrow [2, 2, 3, \underline{5}] \rightarrow [2, 2, \underline{3}, 2] \rightarrow [\underline{2}, 2, 0, 2] \rightarrow [-1, \underline{2}, 0, 2] \rightarrow [-1, -1, 0, \underline{2}] \rightarrow [-1, -1, 0, -1] $ .

## 样例 #1

### 输入

```
3
3 2
1 2 3
2 3
1 1
4 3
2 8 3 5```

### 输出

```
2 1 3 
1 2 
3 1 2 4```

# AI分析结果

### 题目翻译
Monocarp 正在玩另一款电脑游戏。再一次，他的角色正在击杀一些怪物。有 $n$ 个怪物，编号从 $1$ 到 $n$，第 $i$ 个怪物最初有 $a_i$ 点生命值。

Monocarp 的角色有一种技能，可以对当前生命值最高的怪物造成 $k$ 点伤害。如果有多个这样的怪物，则选择编号较小的那个。如果使用技能后怪物的生命值小于或等于 $0$，那么它就会死亡。

Monocarp 使用他的技能直到所有怪物都死亡。你的任务是确定怪物死亡的顺序。

### 算法分类
排序

### 综合分析与结论
这些题解的核心思路都是利用怪物血量模 $k$ 的结果来确定死亡顺序。因为在所有怪物血量跌到 $k$ 及以下之前没有怪物会死，而在所有怪物的血量小于等于 $k$ 之后，玩家是一击必杀的，所以可以通过初始血量模 $k$ 的余数求出最终血量，进而确定死亡顺序。

不同题解的区别在于处理余数为 $0$ 的情况和排序的具体实现方式。部分题解直接将余数为 $0$ 的情况特殊处理，优先输出；部分题解将余数为 $0$ 的值设为 $k$ 再进行排序。

### 所选题解
- 作者：船酱魔王 (赞：3)，4星
    - 关键亮点：思路清晰，代码简洁，详细解释了通过血量模 $k$ 确定死亡顺序的原理。
- 作者：__Aaaaaaaa (赞：3)，4星
    - 关键亮点：使用可并堆模拟过程，虽然代码复杂，但提供了另一种解题思路。
- 作者：PikachuQAQ (赞：1)，4星
    - 关键亮点：通过手玩样例详细验证了阶段性状态的结论，思路清晰，代码规范。

### 重点代码
#### 船酱魔王的代码
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
const int N = 3e5 + 5;
int T;
int n, k;
struct node {
    int id;
    int val;
} a[N];
bool operator<(node p1, node p2) {
    if(p1.val != p2.val) {
        return p1.val > p2.val;
    }
    return p1.id < p2.id;
}
int main() {
    scanf("%d", &T);
    for(int ti = 1; ti <= T; ti++) {
        scanf("%d%d", &n, &k);
        for(int i = 1; i <= n; i++) {
            scanf("%d", &a[i].val);
            a[i].id = i;
            if(a[i].val % k == 0) {
                a[i].val = k;
            } else {
                a[i].val = a[i].val % k;
            }
        }
        sort(a + 1, a + n + 1);
        for(int i = 1; i <= n; i++) {
            printf("%d ", a[i].id);
        }
        printf("\n");
    }
    return 0;
}
```
核心实现思想：定义结构体存储怪物的编号和血量模 $k$ 的值，对结构体数组进行排序，排序规则是血量模 $k$ 的值从大到小，若相等则编号从小到大。最后按顺序输出编号。

#### __Aaaaaaaa 的代码
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N=3e5+10;
struct number{
    int num,ti,id;
    bool operator<(const number &t)const{
        return ti>t.ti;
    }
}a[N];
// 其他代码省略
int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&k);
        for(int i=1;i<=n;++i)
            scanf("%d",&a[i].num);
        for(int i=1;i<=n;++i)
            a[i].ti=(a[i].num+k-1)/k,a[i].id=i,l[i]=r[i]=dist[i]=0,p[i]=i;
        sort(a+1,a+1+n);
        for(int i=1;i<=n;++i){
            v[a[i].id]=a[i].num;
            if(i!=1){
                if(a[i].ti<a[i-1].ti)
                    trans(find(a[i-1].id),-(a[i-1].ti-a[i].ti)*k);
                Merge(a[i-1].id,a[i].id);
            }
        }
        int rt=find(1);
        while(rt){
            printf("%d ",rt);
            remove(rt),rt=find(rt);
        }
        printf("\n");
    }
    return 0;
}
```
核心实现思想：记录每个怪物被砍死的次数，用大根可并堆模拟过程。先对砍死次数排序，对于砍的次数不同的，下放一个 $lazytag$ 使得目前枚举到的怪物距离死亡的次数相同，然后不断合并，最后挨个弹出。

#### PikachuQAQ 的代码
```cpp
#include <algorithm>
#include <iostream>
using namespace std;
const int kMaxN = 3e5 + 7;
struct E {
    int id, x;
    bool operator < (const E &b) const {
        return (x < b.x) ? 0 : (x == b.x ? (id < b.id) : 1);
    }
} a[kMaxN];
int t, n, k, tmp, id;
int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    for (cin >> t; t; t--) {
        cin >> n >> k;
        for (int i = 1, x; i <= n; i++) {
            cin >> a[i].x;
            a[i].x %= k, a[i].id = i;
            if (a[i].x == 0) {
                cout << i << ' ';
            }
        } 
        sort(a + 1, a + n + 1);
        for (int i = 1; i <= n; i++) {
            if (a[i].x != 0) {
                cout << a[i].id << ' ';
            }
        }
        cout << '\n';
    }
    return 0;
}
```
核心实现思想：将每个怪物的血量模 $k$，余数为 $0$ 的直接输出编号，其余的按余数从大到小排序，若余数相等则按编号从小到大排序，最后输出排序后的编号。

### 关键思路或技巧
- 利用数学性质，通过怪物血量模 $k$ 的结果确定死亡顺序，避免了暴力模拟的高时间复杂度。
- 对于余数为 $0$ 的情况，不同题解采用了不同的处理方式，如直接输出或设为 $k$ 再排序。

### 拓展思路
同类型题可能会改变攻击规则或增加其他条件，但核心思路可能仍然是通过数学分析找到关键状态，再进行排序或模拟。类似算法套路可以应用于其他需要确定顺序的题目，通过分析问题的性质，找到影响顺序的关键因素，然后进行排序。

### 推荐题目
- [P1177 【模板】排序](https://www.luogu.com.cn/problem/P1177)
- [P1093 奖学金](https://www.luogu.com.cn/problem/P1093)
- [P1271 【深基9.例1】选举学生会](https://www.luogu.com.cn/problem/P1271)

### 个人心得
- __Aaaaaaaa：比赛的时候脑抽，高估了 T2，写了个可并堆。
总结：在比赛时要准确评估题目难度，避免使用过于复杂的算法。 

---
处理用时：48.84秒