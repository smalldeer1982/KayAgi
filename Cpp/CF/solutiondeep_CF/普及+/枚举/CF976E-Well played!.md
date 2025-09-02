# 题目信息

# Well played!

## 题目描述

Max 最近沉迷于一款打怪游戏《赛某号》。现在，他正在参加赛某号的春季联赛。

他有 $n$ 只精灵。每只精灵都有对应的生命值 $hp_i$ 和攻击值 $dmg_i$。在比赛过程中，Max 可以借助巴拉拉小魔仙之力，说出这两种咒语：

1. “乌卡拉！血量！加倍！“意即将当前精灵的生命值加倍。（使得 $hp_i \gets 2\times hp_i$）

2. “乌卡拉！生命之力！”意即将当前精灵的生命值赋给当前精灵的攻击值。（使得 $dmg_i\gets hp_i$）

Max 当然不能无限使用这两种咒语。在一局游戏中，他可以使用第一种咒语 $a$ 次，第二次咒语 $b$ 次。由于Max 购买了超级 Nono，所以这两种咒语都可以被多次用在同一精灵身上，且咒语的使用顺序没有限制。Max 可以不用完所有的咒语。

Max 非常希望通过使用这些咒语使得自己的精灵战斗群的攻击值达到最大。现在，Max 想知道这个最大值。


输入第 $2$ 行到第 $n+1$ 行，每行两个整数 $hp$，$dmg$。第 $i$ 行表示第 $i-1$ 个精灵的生命值和攻击值。

## 样例 #1

### 输入

```
2 1 1
10 15
6 1
```

### 输出

```
27
```

## 样例 #2

### 输入

```
3 0 3
10 8
7 11
5 2
```

### 输出

```
26
```

# AI分析结果

### 题目内容
# 干得漂亮！

## 题目描述
Max最近沉迷于一款打怪游戏《赛某号》。现在，他正在参加赛某号的春季联赛。

他有 $n$ 只精灵。每只精灵都有对应的生命值 $hp_i$ 和攻击值 $dmg_i$ 。在比赛过程中，Max可以借助巴拉拉小魔仙之力，说出这两种咒语：
1. “乌卡拉！血量！加倍！“意即将当前精灵的生命值加倍。（使得 $hp_i \gets 2\times hp_i$ ）
2. “乌卡拉！生命之力！”意即将当前精灵的生命值赋给当前精灵的攻击值。（使得 $dmg_i\gets hp_i$ ）

Max当然不能无限使用这两种咒语。在一局游戏中，他可以使用第一种咒语 $a$ 次，第二次咒语 $b$ 次。由于Max购买了超级Nono，所以这两种咒语都可以被多次用在同一精灵身上，且咒语的使用顺序没有限制。Max可以不用完所有的咒语。

Max非常希望通过使用这些咒语使得自己的精灵战斗群的攻击值达到最大。现在，Max想知道这个最大值。

输入第 $2$ 行到第 $n + 1$ 行，每行两个整数 $hp$，$dmg$ 。第 $i$ 行表示第 $i - 1$ 个精灵的生命值和攻击值。

## 样例 #1
### 输入
```
2 1 1
10 15
6 1
```
### 输出
```
27
```
## 样例 #2
### 输入
```
3 0 3
10 8
7 11
5 2
```
### 输出
```
26
```

### 综合分析与结论
这些题解的核心思路均为贪心算法。
 - **思路**：都证明或直观得出将所有“生命值加倍”操作（$a$次）集中用于一只精灵可使结果最优，同时按$hp - dmg$的值从大到小排序，对前$b$个精灵执行“生命之力”操作（如果可以的话）也是最优策略。
 - **算法要点**：排序后遍历精灵数据，根据$a$、$b$的次数计算可能的最大攻击值总和。
 - **解决难点**：主要难点在于证明贪心策略的正确性，不同题解通过数学推导或直观解释进行了证明。

### 所选的题解
 - **作者：Echidna (赞：2) - 5星**
    - **关键亮点**：通过严谨的数学证明，详细阐述了将所有生命值加倍机会集中于一人的最优性，思路清晰，代码实现简洁明了，注释合理。
    - **重点代码**：
```cpp
sort(s+1,s+1+n,[](PII a,PII b){
    return a.first-a.second>b.first-b.second;
});
int cont=0;
int lst=0;
for(int now=1;now<=min(b,n);now++){
    if(s[now].first>s[now].second){
        cont+=s[now].first-s[now].second;
        lst=now;
    }else break;
}
for(int i=1;i<=n;i++)
    if(i<=lst)
        delta[i]=cont-(s[i].first-s[i].second);
    else delta[i]=(lst==b)?(cont-(s[lst].first-s[lst].second)):cont;
int ans=0;
for(int i=1;i<=n;i++)
    delta[i]=delta[i]+(1ll<<a)*s[i].first-s[i].second,ans=max(ans,delta[i]);
cout<<max(ans+sum,sum)<<endl;
```
    - **核心思想**：先按$hp - dmg$排序，统计前$b$个$hp > dmg$的差值总和`cont`，并记录最后一个满足条件的位置`lst`。后续通过`delta`数组计算对每个精灵使用$a$次生命值加倍操作后的攻击值变化，最终得出最大攻击值。
 - **作者：JWRuixi (赞：1) - 5星**
    - **关键亮点**：代码简洁高效，利用重载运算符和结构体封装数据，逻辑清晰，对贪心策略的证明简洁明了。
    - **重点代码**：
```cpp
struct Node {
    int hp, d;
    inline int mx () {
        return max(hp, d);
    }
    inline bool operator < (const Node &rhs) const {
        return hp - d > rhs.hp - rhs.d;
    }
} q[maxn];
//...
sort(q + 1, q + n + 1);
for (int i = 1; i <= n; i++) {
    if (i <= b) ans += q[i].mx();
    else ans += q[i].d;
}
if (!b) return write(ans), 0;
const int x = (1 << a), sum = q[b].d - q[b].mx(), tmp = ans;
for (int i = 1; i <= n; i++) {
    if (i <= b) {
        int res = tmp - q[i].mx() + q[i].hp * x;
        ans = max(ans, res);
    } else {
        int res = tmp - q[i].d + q[i].hp * x + sum;
        ans = max(ans, res);
    }
}
```
    - **核心思想**：定义`Node`结构体存储精灵数据并重载`<`运算符用于排序。先计算未使用$a$次生命值加倍操作时的攻击值总和`ans`，然后遍历每个精灵，计算对其使用$a$次生命值加倍操作后的攻击值变化，考虑前后不同部分的计算方式，得出最大攻击值。
 - **作者：UncleSam_Died (赞：1) - 4星**
    - **关键亮点**：解题思路清晰，给出两个贪心结论并分别进行证明，代码实现考虑了多种细节情况。
    - **重点代码**：
```cpp
inline bool cmp(QWQ A,QWQ B){
    if(A.hp-A.dmg==B.hp-B.dmg)
        return A.hp>B.hp;
    return A.hp-A.dmg>B.hp-B.dmg;
}
//...
std::sort(s+1,s+n+1,cmp);
int replace=0,maxt1=-1,res=0;
for(register int i=1;i<=n;++i)
    res+=s[i].dmg,d[i]=s[i].dmg;
if(b==0){printf("%lld",res);return 0;}
if(b){for(register int i=1;i<=n;++i){
        int sub=s[i].dmg;
        int now=(1ll<<a)*s[i].hp-sub;
        maxt1=std::max(maxt1,now);
    }res=res+maxt1;
}for(register int i=1;i<=n;++i){
    if(s[i].hp<=s[i].dmg||!b) break;
    s[i].dmg=s[i].hp;--b;++replace;
}
```
    - **核心思想**：先按$hp - dmg$排序，初始化总和`res`。若$b = 0$直接输出。否则，先计算对所有精灵使用$a$次生命值加倍操作后的最大收益`maxt1`并加到`res`中。然后遍历精灵，对$hp > dmg$且$b$有剩余的精灵执行“生命之力”操作。

### 最优关键思路或技巧
 - **贪心策略**：通过证明得出将“生命值加倍”操作集中于一只精灵，以及按$hp - dmg$排序对前$b$个执行“生命之力”操作的贪心策略。
 - **排序优化**：利用排序简化计算最大攻击值的过程，通过一次遍历和合理的条件判断，计算出各种情况下的最大攻击值。

### 可拓展之处
此类题目属于贪心策略应用类型，类似套路是分析操作对结果的影响，找到能使结果最优的分配方式，常涉及对不同操作次数的限制和多种属性值的综合考量。例如在资源分配、任务调度等场景下的优化问题。

### 洛谷相似题目
 - [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)：通过合理排序贪心解决分配问题。
 - [P2859 [USACO06DEC]Milk Patterns G](https://www.luogu.com.cn/problem/P2859)：利用贪心思想结合字符串处理。
 - [P1937 [USACO10MAR]Barn Allocation G](https://www.luogu.com.cn/problem/P1937)：涉及区间分配的贪心策略。 

---
处理用时：36.73秒