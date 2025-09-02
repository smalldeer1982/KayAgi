# 题目信息

# Koa and the Beach (Hard Version)

## 题目描述

The only difference between easy and hard versions is on constraints. In this version constraints are higher. You can make hacks only if all versions of the problem are solved.

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

### 题目内容中文重写
# Koa与海滩（困难版本）

## 题目描述
简单版本和困难版本的唯一区别在于约束条件。在这个版本中，约束条件更严格。只有当所有版本的问题都被解决后，你才能进行hack操作。

树袋熊Koa正在海滩上！

海滩（从左到右）由一片海岸、$n + 1$米的海域和一个距离海岸$n + 1$米的岛屿组成。

她测量了距离海岸$1, 2, \dots, n$米处海域的深度，并将其存储在数组$d$中。$d_i$表示距离海岸$i$米处海域的深度，其中$1 \le i \le n$。

和其他海滩一样，这片海滩也有潮汐。潮汐的强度用参数$k$来衡量，从时间$t = 0$开始，潮汐会以以下方式影响所有深度：
- 在总共$k$秒内，每秒潮汐会使所有深度增加$1$。
- 然后，在总共$k$秒内，每秒潮汐会使所有深度减少$1$。
- 这个过程会不断重复（即深度先增加$k$秒，然后减少$k$秒，如此循环……）。形式上，定义一个从$0$开始索引的数组$p = [0, 1, 2, \ldots, k - 2, k - 1, k, k - 1, k - 2, \ldots, 2, 1]$，其长度为$2k$。在时间$t$（$0 \le t$）时，距离海岸$i$米处的深度等于$d_i + p[t \bmod 2k]$（$t \bmod 2k$表示$t$除以$2k$的余数）。请注意，每次秒数变化后，深度的变化是瞬间发生的，详见注释以更好地理解。

在时间$t = 0$时，Koa站在海岸上，她想前往岛屿。假设在某个时间$t$（$0 \le t$），她距离海岸$x$（$0 \le x \le n$）米：
- 在一秒内，Koa可以向远离海岸的方向游$1$米（$x$变为$x + 1$），或者不游动（$x$保持不变），在这两种情况下，$t$都会变为$t + 1$。
- 由于Koa游泳技术不佳，在整数时刻，她所在位置的海域深度不能超过$l$（否则她会溺水）。更正式地说，如果Koa在某个整数时刻$t$（$t \ge 0$）位于距离海岸$x$（$1 \le x \le n$）米的位置，那么该位置的海域深度$d_x + p[t \bmod 2k]$不能超过$l$。换句话说，必须始终满足$d_x + p[t \bmod 2k] \le l$。
- 一旦Koa到达距离海岸$n + 1$米的岛屿，她就会停下来休息。请注意，在Koa游泳时，潮汐对她没有影响（即她在游泳时不会溺水）。此外，Koa可以选择在海岸上停留任意长的时间，而且海岸和岛屿都不受潮汐影响（它们是坚实的地面，她在那里不会溺水）。

Koa想知道她是否能够从海岸到达岛屿。请帮助她！

## 说明/提示
在下面的内容中，$s$表示海岸，$i$表示岛屿，$x$表示Koa距离海岸的距离，下划线表示Koa的位置，数组中的值表示在距离海岸$1, 2, \dots, n$米处受潮汐影响的当前深度。

在测试用例1中，我们有$n = 2$，$k = 1$，$l = 1$，$p = [ 0, 1 ]$。

Koa想从海岸（$x = 0$）前往岛屿（$x = 3$）。让我们描述一个可能的解决方案：
- 最初在$t = 0$时，海滩的情况如下：$ [\underline{s}, 1, 0, i] $。
- 在$t = 0$时，如果Koa决定游到$x = 1$，那么在$t = 1$时，海滩的情况将变为：$ [s, \underline{2}, 1, i] $，由于$2 > 1$，她会溺水。因此，Koa选择等待$1$秒，在$t = 1$时，海滩的情况为$ [\underline{s}, 2, 1, i] $。
- 在$t = 1$时，Koa游到$x = 1$，在$t = 2$时，海滩的情况为$ [s, \underline{1}, 0, i] $。Koa没有溺水，因为$1 \le 1$。
- 在$t = 2$时，Koa游到$x = 2$，在$t = 3$时，海滩的情况为$ [s, 2, \underline{1}, i] $。Koa没有溺水，因为$1 \le 1$。
- 在$t = 3$时，Koa游到$x = 3$，在$t = 4$时，海滩的情况为$ [s, 1, 0, \underline{i}] $。
- 在$t = 4$时，Koa到达$x = 3$，她成功了！

我们可以证明，在测试用例2中，Koa无法到达岛屿。

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
贪心

### 综合分析与结论
这些题解的核心思路都是基于贪心策略来解决Koa能否从海岸到达岛屿的问题。不同题解的主要区别在于对潮汐变化和安全水位的处理方式，以及如何根据这些条件来决定Koa的行动。

1. **思路对比**
    - 多数题解都将位置分为特殊列（任何时间都安全）和普通列（有安全时间限制）。
    - 对于特殊列，一般选择等待合适的时机再前进；对于普通列，则尽量在安全的前提下尽快前进。
2. **算法要点**
    - 计算每个位置在不同时刻的水位，判断是否安全。
    - 根据当前位置和水位情况，决定是等待还是前进。
3. **解决难点**
    - 处理潮汐的周期性变化，确保在每个时刻Koa所处位置的水位不超过安全限制。
    - 找到最优的前进策略，避免陷入无法前进的情况。

### 所选题解
- **作者：_xinyu1113（4星）**
    - **关键亮点**：通过列表的方式直观地展示了水位变化情况，思路清晰，代码简洁。
    - **个人心得**：作者表示2200难度的题能在比赛时做出来是个奇迹，还提到B1题不会。
- **作者：Meatherm（4星）**
    - **关键亮点**：详细证明了贪心策略的正确性，逻辑严谨，代码规范。
    - **个人心得**：无。
- **作者：JWRuixi（4星）**
    - **关键亮点**：分析出特殊点和普通点的特点，给出了明确的前进策略，代码实现简单。
    - **个人心得**：作者对题目难度评级表示疑惑。

### 重点代码
#### 作者：_xinyu1113
```cpp
#include <bits/stdc++.h>
using namespace std;
long long a,n,k,l,m,las,p;
int main()
{
    cin>>a;
    for(int i=0;i<a;i++)
    {
        p=1;
        las=0;
        cin>>n>>k>>l;
        for(int j=0;j<n;j++)
        {
            cin>>m;
            if(m>l)//走不通
            {
                p=0;
            }
            else if(m+k<=l)//特殊列
            {
                las=0;
            }
            else if(las<k)//普通列
            {
                las=max(las+1,k-(l-m));
            }
            else
            {
                if(k+(l-m)<las+1)//走不通
                {
                    p=0;
                }
                else
                    las++;//往下一行，往前一列
            }
        }
        if(p==1)
            cout<<"Yes"<<endl;
        else
            cout<<"No"<<endl;
    }
    return 0;
}
```
**核心实现思想**：通过遍历每个位置，根据当前位置的深度和之前的状态，判断是否能继续前进。如果遇到深度大于安全水位的位置，则无法到达；如果是特殊列，则重置状态；对于普通列，更新状态并判断是否能继续前进。

#### 作者：Meatherm
```cpp
# include <bits/stdc++.h>
# define rr
# define int long long
const int N=300010,INF=0x3f3f3f3f;
int n,k,l;
int d[N];
std::vector <int> safe;
inline int read(void){
    int res,f=1;
    char c;
    while((c=getchar())<'0'||c>'9')
        if(c=='-')f=-1;
    res=c-48;
    while((c=getchar())>='0'&&c<='9')
        res=res*10+c-48;
    return res*f;
}
signed main(void){
    int T=read();
    while(T--){
        n=read(),k=read(),l=read();
        safe.resize(0);
        safe.push_back(0);
        bool flag=false;
        for(rr int i=1;i<=n;++i){
            d[i]=read();
            if(d[i]>l){
                flag=true;
            }else if(d[i]+k<=l){
                safe.push_back(i);
            }
        }
        if(flag){
            puts("No");
            goto End;
        }
        safe.push_back(n+1);
        d[0]=d[n+1]=0;
        for(rr int i=0;i<(int)safe.size()-1;++i){
            int now=k,down; // 离开 i 时的高度尽可能地高
            down=(now>0);
            for(rr int j=safe[i];j<safe[i+1];++j){
                if(j+1==n+1){ // 安全位置不受影响
                    puts("Yes");
                    goto End;
                }else if(j+1==safe[i+1]){
                    break;
                }else if(!down){ // 如果已经在上升 便不可能等待下降
                    if(now+1+d[j+1]>l){
                        puts("No");                        
                        goto End;
                    }
                    else
                        ++now;	
                }else{
                    now=std::min(now-1,l-d[j+1]); // 等待最早能通过的时间
                    if(!now){//到达 0 便开始上升
                        down=0;
                    }
                }
            }
        }
        End:;
    }
    return 0;
}
```
**核心实现思想**：先找出所有安全位置，然后从一个安全位置到下一个安全位置进行遍历。在每个区间内，根据潮汐的上升和下降情况，判断是否能安全到达下一个位置。

#### 作者：JWRuixi
```cpp
#include <bits/stdc++.h>
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2")
using namespace std;

namespace IO{
    char ibuf[(1 << 20) + 1], *iS, *iT;
    #if ONLINE_JUDGE
    #define gh() (iS == iT ? iT = (iS = ibuf) + fread(ibuf, 1, (1 << 20) + 1, stdin), (iS == iT ? EOF : *iS++) : *iS++)
    #else
    #define gh() getchar()
    #endif
    #define reg register
    inline long long read () {
        reg char ch = gh();
        reg long long x = 0;
        reg char t = 0;
        while (ch < '0' || ch > '9') t |= ch == '-', ch = gh();
        while (ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ 48), ch = gh();
        return t ? -x : x;
    }
    inline void write(long long x) {
        if (x < 0) {
            x = ~(x - 1);
            putchar('-');
        }
        if (x > 9)
            write(x / 10);
        putchar(x % 10 + '0');
    }
}

using IO::read;
using IO::write;

const int maxn(3e5 + 500);
int T, n, k, l, d[maxn];

int main () {
    T = read();
    while (T--) {
        n = read(), k = read(), l = read();
        for (int i = 1; i <= n; i++) d[i] = read();
        int pos = 0;
        for (int i = 1; i <= n; i++) {
            if (d[i] > l) {
                puts("No");
                goto end;
            }
            if (d[i] + k <= l) {
                pos = 0;
                continue;
            }
            pos = max(pos + 1, k + d[i] - l);
            if (pos > k + l - d[i]) {
                puts("No");
                goto end;
            }
        }
        puts("Yes");
        end:;
    }
}
```
**核心实现思想**：遍历每个位置，对于深度大于安全水位的位置，直接判定无法到达；对于特殊列，重置状态；对于普通列，更新状态并判断是否超出安全范围。

### 最优关键思路或技巧
- **分类讨论**：将位置分为特殊列和普通列，分别采用不同的策略，简化了问题的处理。
- **贪心策略**：在安全的前提下，尽量前进，避免不必要的等待，提高了到达岛屿的可能性。

### 可拓展之处
同类型题可能会有不同的场景，如多个起点和终点、不同的移动规则、更复杂的环境变化等。类似的算法套路包括根据条件进行分类讨论，采用贪心策略进行决策，处理周期性变化等。

### 推荐洛谷题目
1. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)：考察贪心策略的应用。
2. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)：需要运用贪心思想来解决合并问题。
3. [P2240 食草的奶牛](https://www.luogu.com.cn/problem/P2240)：涉及贪心和区间处理的问题。

### 个人心得总结
- _xinyu1113 对自己能在比赛中做出2200难度的题感到惊喜，同时表示不会B1题，反映出题目难度的挑战性。
- JWRuixi 对题目难度评级为绿色表示疑惑，说明题目难度的评估可能存在差异。

---
处理用时：104.88秒