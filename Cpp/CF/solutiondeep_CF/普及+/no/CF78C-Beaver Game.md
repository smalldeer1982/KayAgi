# 题目信息

# Beaver Game

## 题目描述

Two beavers, Timur and Marsel, play the following game.

There are $ n $ logs, each of exactly $ m $ meters in length. The beavers move in turns. For each move a beaver chooses a log and gnaws it into some number (more than one) of equal parts, the length of each one is expressed by an integer and is no less than $ k $ meters. Each resulting part is also a log which can be gnawed in future by any beaver. The beaver that can't make a move loses. Thus, the other beaver wins.

Timur makes the first move. The players play in the optimal way. Determine the winner.

## 说明/提示

In the first sample the beavers only have one log, of $ 15 $ meters in length. Timur moves first. The only move he can do is to split the log into $ 3 $ parts each $ 5 $ meters in length. Then Marsel moves but he can't split any of the resulting logs, as $ k=4 $ . Thus, the winner is Timur.

In the second example the beavers have $ 4 $ logs $ 9 $ meters in length. Timur can't split any of them, so that the resulting parts possessed the length of not less than $ 5 $ meters, that's why he loses instantly.

## 样例 #1

### 输入

```
1 15 4
```

### 输出

```
Timur```

## 样例 #2

### 输入

```
4 9 5
```

### 输出

```
Marsel```

# AI分析结果

### 题目内容
# 海狸游戏

## 题目描述
两只海狸，Timur和Marsel，玩以下游戏。
有$n$根原木，每根原木长度恰好为$m$米。海狸们轮流行动。每次行动，一只海狸选择一根原木，并将其啃成若干（多于一根）等长部分，每部分长度为整数且不小于$k$米。每个生成的部分也是一根原木，可供任意海狸在未来啃咬。无法行动的海狸输掉游戏，另一方获胜。
Timur先行动。玩家们以最优方式游戏。确定获胜者。

## 说明/提示
在第一个样例中，海狸们只有一根长度为15米的原木。Timur先行动。他唯一能做的移动是将原木分成3部分，每部分5米长。然后Marsel行动，但由于$k = 4$，他无法分割任何生成的原木。因此，获胜者是Timur。
在第二个例子中，海狸们有4根长度为9米的原木。Timur无法分割其中任何一根，使得生成部分的长度不小于5米，所以他立即输掉游戏。

## 样例 #1
### 输入
```
1 15 4
```
### 输出
```
Timur```

## 样例 #2
### 输入
```
4 9 5
```
### 输出
```
Marsel```

### 算法分类
数学（博弈论）

### 综合分析与结论
所有题解思路基本一致，均通过对博弈情况分类讨论来解决问题：
 - **情况一：$n$为偶数**：后手可以模仿先手的操作，后手必胜。
 - **情况二：$n$为奇数**：若先手能将多出来的那根原木分割为偶数根，即转化为第一种情况，先手胜；若先手不能分割，则后手胜。判断能否分割时，大部分题解利用枚举到$\sqrt{m}$的因子来优化，有一个题解使用Pollard - rho算法进一步优化时间复杂度。

### 所选的题解
 - **作者：partychicken（5星）**
    - **关键亮点**：思路清晰，代码简洁，将判断先手能否分割原木封装成函数，逻辑清晰，可读性强。
    - **重点代码**：
```cpp
inline bool swin(int a,int min)
{
    int k=sqrt(a)+1;
    for(register int i=1;i<k;++i)
    {
        if(a%i!=0)
        {
            continue;
        }
        if(i>=min&&a/i>1)
        {
            return 0;
        }
        else
        {
            if(i>1&&a/i>=min)
            {
                return 0;
            }
        }
    }
    return 1;
}

int main()
{
    ios::sync_with_stdio(0),cin.tie(0);
    int n,m,k;
    cin>>n>>m>>k;
    if(n%2==0)
    {
        cout<<"Marsel";
    }
    else
    {
        if(swin(m,k))
        {
            cout<<"Marsel";
        }
        else
        {
            cout<<"Timur";
        }
    }
}
```
核心实现思想：`swin`函数通过枚举$a$（原木长度$m$）从$1$到$\sqrt{a}$的因子$i$，判断是否存在满足条件（$i\geq min$且$a/i>1$ 或 $i>1$且$a/i\geq min$）的因子，若存在则返回$0$表示能分割，否则返回$1$表示不能分割。在`main`函数中根据原木数量$n$的奇偶性以及`swin`函数的结果判断并输出获胜者。

 - **作者：ncwzdlsd（4星）**
    - **关键亮点**：对思路分析详细，且在代码注释中提示优化点，帮助理解。
    - **重点代码**：
```cpp
    while(~scanf("%d%d%d",&n,&m,&k))
    {
        int flag=0;
        if(n&1)
        {
            for(int i=1;i*i<=m;i++)
                if(m%i==0)
                {
                    if(i>=k&&m/i>1||i>1&&m/i>=k)
                    {
                        flag=1;
                        break;
                    }
                }
        }
        printf("%s\n",flag?"Timur":"Marsel");
    } 
```
核心实现思想：通过循环读入数据，对于奇数根原木的情况，枚举$1$到$\sqrt{m}$的因子$i$，若存在满足条件（$i\geq k$且$m/i>1$ 或 $i>1$且$m/i\geq k$）的因子，则将`flag`置为$1$，最后根据`flag`的值输出获胜者。

 - **作者：Exiler（4星）**
    - **关键亮点**：对每种情况的证明和分析较为详细，代码注释清晰，对边界条件有清晰判断。
    - **重点代码**：
```cpp
int main()
{
    ios::sync_with_stdio(false);cin.tie(0);
    cin >> n >> m >> k;
    if(n&1 && k<=m)/*n为奇数且k≤m时 才有必胜态的存在可能*/
    {
        for(RI i=1,lim=(int)sqrt(m)+1;i<=lim/*也可以写成i*i<=m 但速度稍慢*/;++i)
            if(!(m%i) && ((i>=k && m/i>1) || (m/i>=k && i>1)))
            {
                /*对于m存在因子i满足i≠1且m/i≥k或i≥k 则Timur可以第一轮就将状态改变为偶数条木棍 即必败态*/
                puts("Timur");
                return 0;
            }
        puts("Marsel");    
    }
    else puts("Marsel");
    return 0;
}
```
核心实现思想：先判断$n$为奇数且$k\leq m$时，枚举$1$到$\sqrt{m}+1$的因子$i$，若$m$存在满足条件（$i\geq k$且$m/i>1$ 或 $m/i\geq k$且$i>1$）的因子，则输出`Timur`，否则输出`Marsel`；其他情况直接输出`Marsel`。

### 最优关键思路或技巧
 - **博弈策略分析**：通过对奇偶情况分类讨论，利用后手模仿先手以及状态转化的博弈思想，确定获胜者。
 - **因子枚举优化**：在判断原木能否分割时，利用数论知识，只枚举到$\sqrt{m}$，降低时间复杂度。

### 可拓展之处
此类博弈论题目通常可通过对不同状态下的操作和结果进行分类讨论，寻找必胜或必败状态的规律。类似题目常涉及到状态转移、模仿策略等思路。

### 相似知识点洛谷题目推荐
 - [P1288 取数游戏II](https://www.luogu.com.cn/problem/P1288)
 - [P2197 模板 nim游戏](https://www.luogu.com.cn/problem/P2197)
 - [P2252 取石子游戏](https://www.luogu.com.cn/problem/P2252)

### 个人心得摘录
无。

---
处理用时：60.23秒