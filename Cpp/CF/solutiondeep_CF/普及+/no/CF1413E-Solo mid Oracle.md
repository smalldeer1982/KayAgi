# 题目信息

# Solo mid Oracle

## 题目描述

Meka-Naruto plays a computer game. His character has the following ability: given an enemy hero, deal $ a $ instant damage to him, and then heal that enemy $ b $ health points at the end of every second, for exactly $ c $ seconds, starting one second after the ability is used. That means that if the ability is used at time $ t $ , the enemy's health decreases by $ a $ at time $ t $ , and then increases by $ b $ at time points $ t + 1 $ , $ t + 2 $ , ..., $ t + c $ due to this ability.

The ability has a cooldown of $ d $ seconds, i. e. if Meka-Naruto uses it at time moment $ t $ , next time he can use it is the time $ t + d $ . Please note that he can only use the ability at integer points in time, so all changes to the enemy's health also occur at integer times only.

The effects from different uses of the ability may stack with each other; that is, the enemy which is currently under $ k $ spells gets $ k\cdot b $ amount of heal this time. Also, if several health changes occur at the same moment, they are all counted at once.

Now Meka-Naruto wonders if he can kill the enemy by just using the ability each time he can (that is, every $ d $ seconds). The enemy is killed if their health points become $ 0 $ or less. Assume that the enemy's health is not affected in any way other than by Meka-Naruto's character ability. What is the maximal number of health points the enemy can have so that Meka-Naruto is able to kill them?

## 说明/提示

In the first test case of the example each unit of damage is cancelled in a second, so Meka-Naruto cannot deal more than 1 damage.

In the fourth test case of the example the enemy gets:

- $ 4 $ damage ( $ 1 $ -st spell cast) at time $ 0 $ ;
- $ 4 $ damage ( $ 2 $ -nd spell cast) and $ 3 $ heal ( $ 1 $ -st spell cast) at time $ 1 $ (the total of $ 5 $ damage to the initial health);
- $ 4 $ damage ( $ 3 $ -nd spell cast) and $ 6 $ heal ( $ 1 $ -st and $ 2 $ -nd spell casts) at time $ 2 $ (the total of $ 3 $ damage to the initial health);
- and so on.

One can prove that there is no time where the enemy gets the total of $ 6 $ damage or more, so the answer is $ 5 $ . Please note how the health is recalculated: for example, $ 8 $ -health enemy would not die at time $ 1 $ , as if we first subtracted $ 4 $ damage from his health and then considered him dead, before adding $ 3 $ heal.

In the sixth test case an arbitrarily healthy enemy can be killed in a sufficient amount of time.

In the seventh test case the answer does not fit into a 32-bit integer type.

## 样例 #1

### 输入

```
7
1 1 1 1
2 2 2 2
1 2 3 4
4 3 2 1
228 21 11 3
239 21 11 3
1000000 1 1000000 1```

### 输出

```
1
2
1
5
534
-1
500000500000```

# AI分析结果

【题目内容（中文重写）】
# 中单神谕者

## 题目描述
Meka - Naruto 在玩一款电脑游戏。他的角色拥有如下技能：对一名敌方英雄造成 $a$ 点瞬间伤害，然后从使用技能的一秒后开始，在接下来的 $c$ 秒内，每秒为该敌方英雄恢复 $b$ 点生命值。也就是说，如果在时间 $t$ 使用该技能，敌方英雄的生命值会在时间 $t$ 减少 $a$，然后在时间点 $t + 1$、$t + 2$、...、$t + c$ 因该技能每秒增加 $b$ 点生命值。

该技能有 $d$ 秒的冷却时间，即如果 Meka - Naruto 在时间 $t$ 使用了该技能，那么他下一次可以使用该技能的时间是 $t + d$。请注意，他只能在整数时间点使用技能，因此所有对敌方英雄生命值的改变也都只发生在整数时间点。

不同次使用技能的效果可以叠加，即当前受到 $k$ 个技能效果影响的敌方英雄，在此时会每秒恢复 $k\cdot b$ 点生命值。此外，如果多个生命值变化在同一时刻发生，它们会同时被计算。

现在 Meka - Naruto 想知道，他是否可以通过每次技能冷却好就使用（即每 $d$ 秒使用一次）来击杀敌方英雄。当敌方英雄的生命值变为 0 或更低时，就会被击杀。假设敌方英雄的生命值不会受到除 Meka - Naruto 角色技能之外的任何影响。那么敌方英雄最多可以有多少生命值，使得 Meka - Naruto 能够击杀他们呢？

## 说明/提示
在样例的第一个测试用例中，每一点伤害都会在一秒后被抵消，所以 Meka - Naruto 最多只能造成 1 点伤害。

在样例的第四个测试用例中，敌方英雄会受到以下影响：
- 在时间 $0$ 受到 $4$ 点伤害（第一次释放技能）；
- 在时间 $1$ 受到 $4$ 点伤害（第二次释放技能）和 $3$ 点治疗（第一次释放技能），总共对初始生命值造成 $5$ 点伤害；
- 在时间 $2$ 受到 $4$ 点伤害（第三次释放技能）和 $6$ 点治疗（第一次和第二次释放技能），总共对初始生命值造成 $3$ 点伤害；
- 以此类推。

可以证明，没有任何时刻敌方英雄受到的总伤害能达到 6 点或更多，所以答案是 5。请注意生命值是如何重新计算的：例如，一个 8 生命值的敌方英雄在时间 1 不会死亡，因为我们应该先减去 4 点伤害，然后再加上 3 点治疗，而不是先减去 4 点伤害就判定其死亡。

在样例的第六个测试用例中，无论敌方英雄的生命值有多高，在足够长的时间后都可以被击杀。

在样例的第七个测试用例中，答案无法用 32 位整数类型表示。

## 样例 #1
### 输入
```
7
1 1 1 1
2 2 2 2
1 2 3 4
4 3 2 1
228 21 11 3
239 21 11 3
1000000 1 1000000 1
```

### 输出
```
1
2
1
5
534
-1
500000500000
```

【算法分类】
数学

【综合分析与结论】
这些题解主要围绕技能伤害与回血机制，通过数学分析来求解敌方英雄的最大生命值。大部分题解先判断是否能造成无限伤害（即 $a > b\times c$ 的情况），若不能，则进一步分析在有限时间内的最大伤害。不同题解的思路和计算方式大致相同，主要区别在于对最大伤害出现时刻的推导和表述略有差异。

【所选题解】
- dead_X（4星）
  - 关键亮点：思路清晰，先明确无限伤害的条件，再分析有限伤害时技能参与答案计算的时间范围，最后通过自定义函数计算结果。
- tommymio（4星）
  - 关键亮点：对思路的阐述详细，不仅给出了计算最大伤害的公式，还说明了公式的推导过程，代码简洁。
- lyhqwq（4星）
  - 关键亮点：将求最大生命转化为求最大伤害，逻辑清晰，代码实现简洁明了。

【重点代码】
- dead_X 的核心代码：
```cpp
long long f(int a,int b,int c,int d,int ll)
{
    return -ll*(ll+1)/2ll*b*d+a*(ll+1);
}
signed main()
{
    int n=read();
    for(int i=1; i<=n; i++) 
    {
        int a=read(),b=read(),c=read(),d=read();
        if(a>b*c) 
        {
            puts("-1");
            continue;
        }
        int t=((a-1)/b)/d;
        printf("%lld\n",f(a,b,c,d,t));
    }
    return 0;
}
```
核心实现思想：先判断是否能造成无限伤害，若不能，则计算在第 $\lfloor\frac{a - 1}{b\times d}\rfloor$ 次放技能时的最大伤害，通过自定义函数 $f$ 计算结果。

- tommymio 的核心代码：
```cpp
int main() {
    int T=read();
    while(T--) {
        int a=read(),b=read(),c=read(),d=read();
        int n=(a-1)/b/d;
        if(a>b*1ll*c) printf("-1\n");
        else printf("%lld\n",(n+1)*1ll*a-d*(1+n)*1ll*n/2*b);
    }
    return 0;
}
```
核心实现思想：同样先判断无限伤害的情况，若不是，则根据公式 $(\lfloor\frac{a - 1}{b\times d}\rfloor + 1)\times a - \sum_{i = 1}^{\lfloor\frac{a - 1}{b\times d}\rfloor} i\times d\times b$ 计算最大伤害。

- lyhqwq 的核心代码：
```cpp
signed main(){
    scanf("%lld",&_);
    while(_--){
        int a,b,c,d;
        scanf("%lld%lld%lld%lld",&a,&b,&c,&d);
        if(a>b*c) puts("-1");
        else{
            int t=(a-1)/(b*d);
            printf("%lld\n",(t+1)*a-b*d*t*(t+1)/2);
        }
    }
    return 0;
}
```
核心实现思想：先判断，若不是无限伤害，计算最大伤害，公式与上述类似。

【关键思路或技巧】
- 先判断 $a$ 与 $b\times c$ 的大小关系，确定是否能造成无限伤害。
- 分析一次攻击对总伤害产生非负贡献的时间点，从而确定最大伤害出现的时刻。
- 利用等差数列求和公式简化计算。

【拓展思路】
同类型题可能会改变技能的机制，如增加更多的技能效果、改变冷却时间的计算方式等，但核心思路仍然是分析伤害与回血的关系，通过数学计算求解。类似算法套路可用于解决其他涉及周期性变化和数值计算的问题，如资源的消耗与补充、游戏中的属性变化等。

【推荐题目】
- P1003 铺地毯
- P1047 校门外的树
- P1088 火星人

---
处理用时：52.01秒