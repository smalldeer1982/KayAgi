# 题目信息

# Collective Mindsets (easy)

## 题目描述

Tonight is brain dinner night and all zombies will gather together to scarf down some delicious brains. The artful Heidi plans to crash the party, incognito, disguised as one of them. Her objective is to get away with at least one brain, so she can analyze the zombies' mindset back home and gain a strategic advantage.

They will be $ N $ guests tonight: $ N-1 $ real zombies and a fake one, our Heidi. The living-dead love hierarchies as much as they love brains: each one has a unique rank in the range $ 1 $ to $ N-1 $ , and Heidi, who still appears slightly different from the others, is attributed the highest rank, $ N $ . Tonight there will be a chest with brains on display and every attendee sees how many there are. These will then be split among the attendees according to the following procedure:

The zombie of the highest rank makes a suggestion on who gets how many brains (every brain is an indivisible entity). A vote follows. If at least half of the attendees accept the offer, the brains are shared in the suggested way and the feast begins. But if majority is not reached, then the highest-ranked zombie is killed, and the next zombie in hierarchy has to make a suggestion. If he is killed too, then the third highest-ranked makes one, etc. (It's enough to have exactly half of the votes – in case of a tie, the vote of the highest-ranked alive zombie counts twice, and he will of course vote in favor of his own suggestion in order to stay alive.)

You should know that zombies are very greedy and sly, and they know this too – basically all zombie brains are alike. Consequently, a zombie will never accept an offer which is suboptimal for him. That is, if an offer is not strictly better than a potential later offer, he will vote against it. And make no mistake: while zombies may normally seem rather dull, tonight their intellects are perfect. Each zombie's priorities for tonight are, in descending order:

1. survive the event (they experienced death already once and know it is no fun),
2. get as many brains as possible.

Heidi goes first and must make an offer which at least half of the attendees will accept, and which allocates at least one brain for Heidi herself.

What is the smallest number of brains that have to be in the chest for this to be possible?

## 样例 #1

### 输入

```
1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
4
```

### 输出

```
2
```

# AI分析结果

### 题目翻译
# 集体思维（简单）

## 题目描述
今晚是大脑晚宴之夜，所有僵尸都会聚集在一起大快朵颐美味的大脑。机智的海蒂计划伪装成其中一员混入派对。她的目标是至少带走一个大脑，这样她就可以回家分析僵尸的思维方式，从而获得战略优势。

今晚将有 $N$ 位客人：$N - 1$ 个真正的僵尸和一个假冒的，即海蒂。这些行尸走肉和他们热爱大脑一样热爱等级制度：每个僵尸都有一个在 $1$ 到 $N - 1$ 范围内的唯一等级，而看起来与其他僵尸略有不同的海蒂被赋予了最高等级 $N$。今晚将有一个装有大脑的箱子展示出来，每个与会者都能看到里面有多少大脑。然后，这些大脑将按照以下程序在与会者之间分配：

等级最高的僵尸提出一个关于谁得到多少大脑的建议（每个大脑都是不可分割的实体）。随后进行投票。如果至少一半的与会者接受这个提议，大脑就会按照建议的方式分配，盛宴开始。但如果没有达到多数，那么等级最高的僵尸将被杀死，等级次高的僵尸必须提出一个建议。如果他也被杀死，那么等级第三高的僵尸提出一个建议，依此类推。（只要有恰好一半的选票就足够了——在平局的情况下，等级最高的存活僵尸的投票计为两票，而且他当然会投票支持自己的建议以保住性命。）

你要知道，僵尸非常贪婪和狡猾，而且他们也知道这一点——基本上所有僵尸的想法都是一样的。因此，僵尸永远不会接受对他来说不是最优的提议。也就是说，如果一个提议不比潜在的后续提议严格更好，他就会投票反对。别搞错了：虽然僵尸平时看起来可能很迟钝，但今晚他们的智力是完美的。每个僵尸今晚的优先级按降序排列如下：
1. 熬过今晚（他们已经体验过一次死亡，知道那并不好玩）。
2. 尽可能多地获得大脑。

海蒂先提出建议，她必须提出一个至少一半与会者会接受的提议，并且这个提议要给海蒂自己至少分配一个大脑。

箱子里至少要有多少个大脑才能做到这一点？

## 样例 #1
### 输入
```
1
```
### 输出
```
1
```

## 样例 #2
### 输入
```
4
```
### 输出
```
2
```

### 算法分类
数学

### 综合分析与结论
这些题解都围绕僵尸分大脑问题展开，核心是找到满足条件的最少大脑数。各题解思路相似，均从分析不同僵尸的决策出发，得出让一半人（向上取整）分到 1 个大脑的结论，即最少需要 $\lceil\frac{N}{2}\rceil$ 个大脑。

### 所选题解
- **Confringo（4星）**
    - **关键亮点**：思路清晰，从最后一个提出方案的僵尸开始逐步推导，详细分析了不同僵尸的决策过程，逻辑严谨。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin>>n;
    cout<<int(ceil(n/2.0));
    return 0;
}
```
核心实现思想：通过 `ceil` 函数对 $n/2.0$ 向上取整，得到最少需要的大脑数。

- **断清秋（4星）**
    - **关键亮点**：指出这是经典的海盗分金币问题的变种，分析了与经典模型的不同点，并说明分配规律与经典模型一致，简洁明了。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
#define ll long long
#define back return
#define ri register int
#define ull unsigned ll
using namespace std;
int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
    {
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    back x*f;
}
ll t,n,s;
int main()
{
    n=read();
    cout<<(n+1)/2<<"\n";
    back 0;
}
```
核心实现思想：通过 `(n + 1) / 2` 实现向上取整，得到最少需要的大脑数。

- **Yyxxxxx（4星）**
    - **关键亮点**：通过枚举得出规律，进而归纳出答案公式，方法简单直接。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){int x;scanf("%d",&x);printf("%d",x+1>>1);}
```
核心实现思想：通过 `x + 1 >> 1` 实现向上取整，得到最少需要的大脑数。

### 最优关键思路或技巧
- 采用逆向思维，从最后一个提出方案的僵尸开始分析，逐步推导前面僵尸的决策，这种思维方式有助于简化问题。
- 利用数学方法，通过归纳总结得出最少大脑数的计算公式，避免了复杂的模拟过程。

### 可拓展之处
同类型题如经典的海盗分金币问题，类似算法套路是从简单情况开始分析，逐步推导复杂情况，找出规律和决策的最优策略。

### 推荐题目
- [P2123 皇后游戏](https://www.luogu.com.cn/problem/P2123)
- [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)
- [P1247 取火柴游戏](https://www.luogu.com.cn/problem/P1247)

### 个人心得
无

---
处理用时：37.39秒