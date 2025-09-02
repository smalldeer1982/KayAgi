# 题目信息

# Kill 'Em All

## 题目描述

Ivan plays an old action game called Heretic. He's stuck on one of the final levels of this game, so he needs some help with killing the monsters.

The main part of the level is a large corridor (so large and narrow that it can be represented as an infinite coordinate line). The corridor is divided into two parts; let's assume that the point $ x = 0 $ is where these parts meet.

The right part of the corridor is filled with $ n $ monsters — for each monster, its initial coordinate $ x_i $ is given (and since all monsters are in the right part, every $ x_i $ is positive).

The left part of the corridor is filled with crusher traps. If some monster enters the left part of the corridor or the origin (so, its current coordinate becomes less than or equal to $ 0 $ ), it gets instantly killed by a trap.

The main weapon Ivan uses to kill the monsters is the Phoenix Rod. It can launch a missile that explodes upon impact, obliterating every monster caught in the explosion and throwing all other monsters away from the epicenter. Formally, suppose that Ivan launches a missile so that it explodes in the point $ c $ . Then every monster is either killed by explosion or pushed away. Let some monster's current coordinate be $ y $ , then:

- if $ c = y $ , then the monster is killed;
- if $ y < c $ , then the monster is pushed $ r $ units to the left, so its current coordinate becomes $ y - r $ ;
- if $ y > c $ , then the monster is pushed $ r $ units to the right, so its current coordinate becomes $ y + r $ .

Ivan is going to kill the monsters as follows: choose some integer point $ d $ and launch a missile into that point, then wait until it explodes and all the monsters which are pushed to the left part of the corridor are killed by crusher traps, then, if at least one monster is still alive, choose another integer point (probably the one that was already used) and launch a missile there, and so on.

What is the minimum number of missiles Ivan has to launch in order to kill all of the monsters? You may assume that every time Ivan fires the Phoenix Rod, he chooses the impact point optimally.

You have to answer $ q $ independent queries.

## 说明/提示

In the first test case, Ivan acts as follows:

- choose the point $ 3 $ , the first monster dies from a crusher trap at the point $ -1 $ , the second monster dies from the explosion, the third monster is pushed to the point $ 7 $ ;
- choose the point $ 7 $ , the third monster dies from the explosion.

In the second test case, Ivan acts as follows:

- choose the point $ 5 $ , the first and fourth monsters die from the explosion, the second monster is pushed to the point $ 1 $ , the third monster is pushed to the point $ 2 $ ;
- choose the point $ 2 $ , the first monster dies from a crusher trap at the point $ 0 $ , the second monster dies from the explosion.

## 样例 #1

### 输入

```
2
3 2
1 3 5
4 1
5 2 3 5
```

### 输出

```
2
2
```

# AI分析结果

### 题目内容
# 全部消灭

## 题目描述
伊万在玩一款名为《异教徒》的经典动作游戏。他被困在了游戏的最后几关之一，因此在消灭怪物方面需要一些帮助。

关卡的主要部分是一条宽阔的走廊（它非常宽阔且狭窄，可被视为一条无限的坐标线）。走廊被分为两部分，我们假设点\(x = 0\)是这两部分的交汇处。

走廊的右侧部分布满了\(n\)只怪物，对于每只怪物，都给出了它的初始坐标\(x_i\)（由于所有怪物都在右侧部分，所以每个\(x_i\)都是正数）。

走廊的左侧部分布满了碾压陷阱。如果有任何怪物进入走廊的左侧部分或原点（即其当前坐标小于或等于\(0\)），它会立即被陷阱杀死。

伊万用来消灭怪物的主要武器是凤凰之杖。它可以发射一枚导弹，导弹撞击后会爆炸，消灭所有处于爆炸范围内的怪物，并将其他所有怪物从爆炸中心推开。正式地说，假设伊万发射一枚导弹，使其在点\(c\)爆炸。那么每只怪物要么被爆炸消灭，要么被推开。设某只怪物的当前坐标为\(y\)，则：
 - 如果\(c = y\)，那么怪物被消灭；
 - 如果\(y < c\)，那么怪物被向左推\(r\)个单位，所以它的当前坐标变为\(y - r\)；
 - 如果\(y > c\)，那么怪物被向右推\(r\)个单位，所以它的当前坐标变为\(y + r\)。

伊万打算按照以下方式消灭怪物：选择某个整数点\(d\)并向该点发射一枚导弹，然后等待导弹爆炸，所有被推到走廊左侧部分的怪物会被碾压陷阱杀死，然后，如果至少还有一只怪物存活，选择另一个整数点（可能是已经使用过的点）并在那里发射导弹，依此类推。

伊万为了消灭所有怪物，最少需要发射多少枚导弹？你可以假设每次伊万发射凤凰之杖时，他都会最优地选择爆炸点。

你需要回答\(q\)个独立的查询。

## 说明/提示
在第一个测试用例中，伊万的行动如下：
 - 选择点\(3\)，第一只怪物在点\(-1\)被碾压陷阱杀死，第二只怪物死于爆炸，第三只怪物被推到点\(7\)；
 - 选择点\(7\)，第三只怪物死于爆炸。

在第二个测试用例中，伊万的行动如下：
 - 选择点\(5\)，第一只和第四只怪物死于爆炸，第二只怪物被推到点\(1\)，第三只怪物被推到点\(2\)；
 - 选择点\(2\)，第一只怪物在点\(0\)被碾压陷阱杀死，第二只怪物死于爆炸。

## 样例 #1
### 输入
```
2
3 2
1 3 5
4 1
5 2 3 5
```
### 输出
```
2
2
```

### 算法分类
贪心

### 题解综合分析与结论
所有题解均采用贪心策略解决该问题。核心思路是每次选择当前坐标最大的怪物开炮，这样能使每次开炮的伤害最大化，尽可能多的让怪物向左移动到原点左侧从而被消灭。各题解在实现细节上略有不同，有的通过排序后从大到小枚举怪物并判断是否已死在原点左侧来计数开炮次数；有的在排序后去重，再模拟开炮过程；还有的通过等价变换，将怪物坐标变化转化为原点右移来实现。

### 所选的题解
- **作者：微香玉烛暗（5星）**
    - **关键亮点**：思路清晰，详细阐述贪心策略，代码实现简洁明了，变量命名规范，对循环中的条件判断处理得当。
    - **个人心得**：针对评论区反馈修改代码，强调不应抄袭题解。
    - **核心代码**：
```cpp
bool cmp (int x,int y) {
    return x>y;
}

int main () {
    scanf ("%d",&t);
    while (t--) {
        ans=num=0; now=-1e9;
        scanf ("%d%d",&n,&m);
        for (int i=1;i<=n;i++) {
            scanf ("%d",&a[i]);
        }
        sort (a+1,a+1+n,cmp);
        for (int i=n;i>=1;i--) {
            if(a[i]==now) continue;
            if(a[i]-num<=0) break;
            ans++; num+=m; now=a[i];
        }
        printf("%d\n",ans);
    }
    return 0;
}
```
核心实现思想：先对怪物坐标从大到小排序，然后从最大坐标怪物开始枚举，若当前怪物坐标与上一个不同且未因左移到原点左侧死亡，则开炮并更新已开炮次数和怪物左移的总距离，若当前怪物已死在原点左侧则结束枚举，输出开炮次数。

- **作者：HoshizoraZ（4星）**
    - **关键亮点**：对题意分析透彻，详细说明了去重的原因及贪心策略的推导过程，逻辑连贯。
    - **核心代码**：无完整代码，但思路清晰可依此实现。
核心实现思想：先对怪物坐标去重，然后每次选择当前剩余怪物中最右边的进行消灭，通过判断“点的初始坐标 - \(r\) * 已经炮轰次数 ≤ 0”来确定是否所有怪物已被消灭，统计炮轰次数。

- **作者：zgy_123（4星）**
    - **关键亮点**：提出将怪物坐标变化等价为原点右移的巧妙思路，优化了模拟过程，降低时间复杂度。
    - **核心代码**：
```cpp
int main(){
    int T,n,r;
    cin>>T;
    while(T--){
        memset(b,0,sizeof(b));
        cin>>n>>r;
        for(int i=1;i<=n;i++) cin>>a[i];
        int t=0;
        sort(a+1,a+n+1);
        while(1){
            int x=a[n];
            if(x<=t) break;
            while(a[n]==x) n--;
            t+=r;
        }
        cout<<t/r<<endl;
    }
    return 0;
}
```
核心实现思想：对怪物坐标排序后，每次取最后一个怪物，若其坐标小于等于原点右移的距离则已死，否则将原点右移\(r\)个单位，循环直到所有怪物死亡，输出原点右移总距离除以\(r\)得到开炮次数。

### 最优关键思路或技巧
1. **贪心策略**：每次选择当前坐标最大的怪物开炮，最大化每次开炮的效果，使更多怪物向左移动到陷阱区域。
2. **等价变换**：如将怪物坐标变化转化为原点右移，简化模拟过程，优化时间复杂度。

### 可拓展之处
同类型题通常围绕在类似的场景设置下，通过某种操作使目标达到最优。类似算法套路是分析每次操作如何能使结果最优，确定贪心策略。例如在一些物品放置、资源分配等场景下，通过合理选择每次操作的对象来达到最小步数、最大收益等目标。

### 洛谷相似题目推荐
1. [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)：通过合理排序确定分配顺序，利用贪心策略解决问题。
2. [P1248 加工生产调度](https://www.luogu.com.cn/problem/P1248)：涉及任务调度，需分析如何贪心选择任务顺序以达到最优时间。
3. [P1106 删数问题](https://www.luogu.com.cn/problem/P1106)：通过贪心思想删除数字，使剩下数字组成的数最小。 

---
处理用时：80.54秒