# 题目信息

# Phoenix and Socks

## 题目描述

To satisfy his love of matching socks, Phoenix has brought his $ n $ socks ( $ n $ is even) to the sock store. Each of his socks has a color $ c_i $ and is either a left sock or right sock.

Phoenix can pay one dollar to the sock store to either:

- recolor a sock to any color $ c' $ $ (1 \le c' \le n) $
- turn a left sock into a right sock
- turn a right sock into a left sock

The sock store may perform each of these changes any number of times. Note that the color of a left sock doesn't change when it turns into a right sock, and vice versa.

A matching pair of socks is a left and right sock with the same color. What is the minimum cost for Phoenix to make $ n/2 $ matching pairs? Each sock must be included in exactly one matching pair.

## 说明/提示

In the first test case, Phoenix can pay $ 2 $ dollars to:

- recolor sock $ 1 $ to color $ 2 $
- recolor sock $ 3 $ to color $ 2 $

 There are now $ 3 $ matching pairs. For example, pairs $ (1, 4) $ , $ (2, 5) $ , and $ (3, 6) $ are matching.In the second test case, Phoenix can pay $ 3 $ dollars to:

- turn sock $ 6 $ from a right sock to a left sock
- recolor sock $ 3 $ to color $ 1 $
- recolor sock $ 4 $ to color $ 1 $

 There are now $ 3 $ matching pairs. For example, pairs $ (1, 3) $ , $ (2, 4) $ , and $ (5, 6) $ are matching.

## 样例 #1

### 输入

```
4
6 3 3
1 2 3 2 2 2
6 2 4
1 1 2 2 2 2
6 5 1
6 5 4 3 2 1
4 0 4
4 4 4 3```

### 输出

```
2
3
5
3```

# AI分析结果

### 题目翻译
# 菲尼克斯与袜子

## 题目描述
为了满足他对配对袜子的喜爱，菲尼克斯带着他的 $n$ 只袜子（$n$ 为偶数）来到了袜子店。他的每只袜子都有一个颜色 $c_i$，并且要么是左袜，要么是右袜。

菲尼克斯可以向袜子店支付一美元来进行以下操作之一：
- 将一只袜子重新染色为任意颜色 $c'$（$1 \le c' \le n$）
- 将一只左袜变成右袜
- 将一只右袜变成左袜

袜子店可以任意次数地执行这些更改。请注意，当一只左袜变成右袜时，其颜色不会改变，反之亦然。

一双匹配的袜子是指一只左袜和一只右袜且颜色相同。菲尼克斯要组成 $n/2$ 双匹配的袜子，最小的花费是多少？每只袜子必须恰好包含在一双匹配的袜子中。

## 说明/提示
在第一个测试用例中，菲尼克斯可以支付 2 美元来：
- 将袜子 1 重新染色为颜色 2
- 将袜子 3 重新染色为颜色 2

现在有 3 双匹配的袜子。例如，配对 (1, 4)、(2, 5) 和 (3, 6) 是匹配的。
在第二个测试用例中，菲尼克斯可以支付 3 美元来：
- 将袜子 6 从右袜变成左袜
- 将袜子 3 重新染色为颜色 1
- 将袜子 4 重新染色为颜色 1

现在有 3 双匹配的袜子。例如，配对 (1, 3)、(2, 4) 和 (5, 6) 是匹配的。

## 样例 #1
### 输入
```
4
6 3 3
1 2 3 2 2 2
6 2 4
1 1 2 2 2 2
6 5 1
6 5 4 3 2 1
4 0 4
4 4 4 3
```
### 输出
```
2
3
5
3
```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路都是先将已配对的袜子去除，然后通过贪心策略来减少操作次数，使总花费最小。各题解的主要区别在于贪心的具体实现方式和细节处理上。

大部分题解都采用了以下步骤：
1. 去除原本就配对的袜子。
2. 统计左右袜子的数量和奇数堆数。
3. 根据左右袜子数量关系进行分类讨论，优先处理能以较低代价配对的情况，尽量减少需要花费 2 元配对的情况。

### 所选题解
- **Gokix（5星）**
    - **关键亮点**：思路清晰，对不同情况的分类讨论详细且有条理，代码实现简洁明了，易于理解。
- **water_tomato（4星）**
    - **关键亮点**：对操作次数的分析有小证明，逻辑严谨，代码注释详细，便于阅读。
- **Echo_Long（4星）**
    - **关键亮点**：明确指出时间复杂度，对特殊情况有特判，代码结构清晰。

### 重点代码
#### Gokix 的题解
```cpp
for(i=1;i<=n;i++){//去除本来就配对的
    if(a[i]>b[i]){
        a[i]-=b[i];
        b[i]=0;
    }
    else{
        b[i]-=a[i];
        a[i]=0;
    }
}
u=v=conu=conv=0;
for(i=1;i<=n;i++){
    u+=a[i];
    conu+=a[i]%2;
    v+=b[i];
    conv+=b[i]%2;
}
if(u==v){//没有情况3
    ans=u;
}
else if(u>v){
    if(v>=conu){//也没有情况3
        ans=(u+v)/2;
    }
    else{//必然有情况3
        ans=(u+conu)/2;
    }
}
else{//v>u与u>v同理
    if(u>=conv){
        ans=(u+v)/2;
    }
    else{
        ans=(v+conv)/2;
    }
}
```
**核心实现思想**：先去除已配对的袜子，然后统计左右袜子的总数和奇数堆数，根据左右袜子数量关系进行分类讨论，得出最小花费。

#### water_tomato 的题解
```cpp
ans=abs(l-r)/2;//更改左右性的操作数
for(int i=1;i<=n;i++){
    if(tl[i]>0&&tr[i]>0){
        int t=min(tl[i],tr[i]);
        tl[i]-=t;
        tr[i]-=t;//这里是去除已配对的袜子
    }
}
int x=ans;
if(l>r){//找袜子多的那边，进行操作
    for(int i=1;i<=n&&x>0;i++){
        while(x>0&&tl[i]>=2){//如果有不少于 2 只的，选它
            x--;
            tl[i]-=2;//一只左右性换了，一只匹配上了，故未匹配的直接减 2
        }
    }
    for(int i=1;i<=n&&x>0;i++){
        while(x>0&&tl[i]>=1){//处理剩余的操作次数
            x--;
            tl[i]-=1;//未匹配的袜子数只能减 1
        }
    }
    for(int i=1;i<=n;i++){
        ans+=tl[i];//答案加上未匹配的袜子数
    }
}
else{//同上
    for(int i=1;i<=n&&x>0;i++){
        while(x>0&&tr[i]>=2){
            x--;
            tr[i]-=2;
        }
    }
    for(int i=1;i<=n&&x>0;i++){
        while(x>0&&tr[i]>=1){
            x--;
            tr[i]-=1;
        }
    }
    for(int i=1;i<=n;i++){
        ans+=tr[i];
    }
}
```
**核心实现思想**：先确定更改左右性的操作数，去除已配对的袜子，然后在袜子多的那边优先处理有不少于 2 只同色的袜子，最后加上未匹配的袜子数得到答案。

#### Echo_Long 的题解
```cpp
for ( int i = 1 ; i <= n ; i ++ )
{
    if ( a[i] >= b[i] ) a[i] -= b[i] , b[i] = 0;
    else if ( a[i] < b[i] ) b[i] -= a[i] , a[i] = 0;
}
int cntl = 0 , cntr = 0;
for ( int i = 1 ; i <= n ; i ++ ) cntl += a[i] , cntr += b[i];
if ( cntl < cntr )
{
    for ( int i = 1 ; i <= n ; i ++ ) swap ( a[i] , b[i] );
    swap ( cntl , cntr );
}
for ( int i = 1 ; i <= n ; i ++ )
{
    if ( a[i] >= 2 )
    {
        if ( a[i] > ( cntl - cntr ) ) ans += ( cntl - cntr ) / 2 , cntl = cntr;
        else ans += a[i] / 2 , cntl -= a[i] / 2 * 2;
    }
    if ( cntl == cntr ) break;
}
if ( cntl == cntr ) cout << ans + ( cntl + cntr ) / 2 << endl;
else cout << ans + ( cntl + cntr ) / 2 + ( cntl - cntr ) / 2 << endl;
```
**核心实现思想**：先去除已配对的袜子，让左袜子数量不少于右袜子数量，然后处理左袜子中数量不少于 2 的情况，最后根据左右袜子数量关系计算答案。

### 最优关键思路或技巧
- 先去除已配对的袜子，简化问题。
- 优先处理能以较低代价配对的情况，如将同色同左右的袜子通过改变左右属性配对，将不同色不同左右的袜子通过改变颜色配对，尽量减少需要花费 2 元配对的情况。
- 对左右袜子数量关系进行分类讨论，根据不同情况计算最小花费。

### 可拓展之处
同类型题可能会有更多的操作限制或条件变化，例如增加不同的操作代价、限制操作次数等。类似的算法套路是先对初始状态进行预处理，然后根据贪心策略逐步优化，使目标达到最优。

### 推荐题目
1. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)
2. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
3. [P2240 部分背包问题](https://www.luogu.com.cn/problem/P2240)

### 个人心得摘录与总结
- **Echo_Long**：“$*1500$ 调了一个小时”，说明该题有一定的难度，调试过程可能会花费较多时间，需要耐心和细心。
- **FutaRimeWoawaSete**：“如果不是晚上打说不定真的是随便切”，暗示在状态不佳时可能会影响解题效率，提醒我们要保持良好的状态解题。

---
处理用时：66.93秒