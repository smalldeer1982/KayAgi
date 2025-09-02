# 题目信息

# Astrophysicists

## 题目描述

In many, many years, far, far away, there will be a launch of the first flight to Mars. To celebrate the success, $ n $ astrophysicists working on the project will be given bonuses of a total value of $ k $ gold coins.

You have to distribute the money among the astrophysicists, and to make it easier, you have to assign bonuses in silver coins. Each gold coin is worth $ g $ silver coins, so you have to distribute all $ k \cdot g $ silver coins among $ n $ people.

Unfortunately, the company has some financial troubles right now. Therefore, instead of paying the number of silver coins written on the bonus, they decided to round this amount to the nearest integer number of gold coins.

The rounding procedure is as follows. If an astrophysicist has bonus equal to $ x $ silver coins, and we denote $ r = x \bmod g $ , then:

- If $ r \geq \lceil \frac{g}{2} \rceil $ , the astrophysicist receives $ x + (g - r) $ silver coins;
- Otherwise, an astrophysicists receives $ x - r $ silver coins.

 Note that due to rounding, the total sum of actually paid money is not, in general, equal to $ k \cdot g $ silver coins. The operation $ a \bmod b $ denotes the remainder of the division of $ a $ by $ b $ . Sum of values before rounding has to be equal to $ k \cdot g $ silver coins, but some workers can be assigned $ 0 $ silver coins.You aim to distribute the bonuses so that the company saves as many silver coins due to rounding as possible. Please note that there is always a distribution in which the company spends no more than $ k \cdot g $ silver coins.

## 说明/提示

In the first test case, one of the optimal assignments could be the following:

- First person: $ x = 30 $ silver coins: company pays $ 0 $ , saves $ 30 $ silver coins,
- Second person: $ x = 140 $ silver coins: company pays $ 100 $ , saves $ 40 $ silver coins,
- Third person: $ x = 130 $ silver coins: company pays $ 100 $ , saves $ 30 $ silver coins.

In the second test case, we could have the following assignment:

- First person: $ x = 8 $ silver coins: company pays $ 14 $ , spends extra $ 6 $ silver coins,
- Second person: $ x = 6 $ silver coins: company pays $ 0 $ , saves $ 6 $ silver coins.

If the bonuses are assigned to $ 7 $ silver coins for both astrophysicists, then the company would have to pay an additional gold coin to cover the bonuses.

## 样例 #1

### 输入

```
5
3 3 100
2 1 14
91 2 13
36 16 6
73 8 22```

### 输出

```
100
0
26
72
176```

# AI分析结果

### 题目内容中文重写
# 天体物理学家

## 题目描述
在很久很久以后，在非常非常遥远的地方，将首次发射前往火星的飞行任务。为了庆祝这一成功，参与该项目的 $n$ 位天体物理学家将获得总价值为 $k$ 枚金币的奖金。

你需要在这些天体物理学家中分配这笔钱，为了方便起见，你需要以银币为单位分配奖金。每枚金币价值 $g$ 枚银币，所以你需要将总共 $k \cdot g$ 枚银币分配给 $n$ 个人。

不幸的是，公司目前面临一些财务问题。因此，公司没有按照奖金上标明的银币数量支付，而是决定将这个金额四舍五入到最接近的整数金币数。

四舍五入的规则如下。如果一位天体物理学家的奖金为 $x$ 枚银币，我们记 $r = x \bmod g$，那么：
- 如果 $r \geq \lceil \frac{g}{2} \rceil$，这位天体物理学家将获得 $x + (g - r)$ 枚银币；
- 否则，这位天体物理学家将获得 $x - r$ 枚银币。

请注意，由于四舍五入，实际支付的总金额通常不等于 $k \cdot g$ 枚银币。$a \bmod b$ 运算表示 $a$ 除以 $b$ 的余数。四舍五入前的奖金总和必须等于 $k \cdot g$ 枚银币，但有些员工的奖金可以为 $0$ 枚银币。你的目标是分配奖金，使公司通过四舍五入节省尽可能多的银币。请注意，总是存在一种分配方式，使公司的支出不超过 $k \cdot g$ 枚银币。

## 说明/提示
在第一个测试用例中，一种最优的分配方案可能如下：
- 第一个人：$x = 30$ 枚银币：公司支付 $0$ 枚银币，节省 $30$ 枚银币；
- 第二个人：$x = 140$ 枚银币：公司支付 $100$ 枚银币，节省 $40$ 枚银币；
- 第三个人：$x = 130$ 枚银币：公司支付 $100$ 枚银币，节省 $30$ 枚银币。

在第二个测试用例中，我们可以有如下分配方案：
- 第一个人：$x = 8$ 枚银币：公司支付 $14$ 枚银币，多支出 $6$ 枚银币；
- 第二个人：$x = 6$ 枚银币：公司支付 $0$ 枚银币，节省 $6$ 枚银币。

如果给两位天体物理学家都分配 $7$ 枚银币，那么公司将不得不额外支付一枚金币来支付奖金。

## 样例 #1
### 输入
```
5
3 3 100
2 1 14
91 2 13
36 16 6
73 8 22
```
### 输出
```
100
0
26
72
176
```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路都是贪心策略，即尽可能让每个人分配的银币数在四舍五入时能让公司节省最多的银币。通常考虑先让前 $n - 1$ 个人的银币数达到向下舍入的最大值 $\lceil\frac{g}{2}\rceil - 1$，再处理最后一个人的银币数。不同题解在处理特殊情况（如银币未发完、节省的银币数超过总数）的方式上略有不同，但整体思路一致。

### 所选题解
- **qwq___qaq（5星）**：
  - **关键亮点**：思路清晰，证明了贪心策略的正确性，代码简洁高效。
  - **核心实现思想**：先计算出最后一个人的银币数，再根据其舍入情况计算公司节省的银币数。
  - **核心代码**：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T,n,k,g;
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n>>k>>g;
        int t=max(0ll,k*g-(n-1)*((g-1)/2));
        if(t%g>=(g+1)/2)
            cout<<(k-(t+g-1)/g)*g<<endl;
        else
            cout<<(k-t/g)*g<<endl;
    }
    return 0;
}
```
- **_Only_this（4星）**：
  - **关键亮点**：思路明确，对特殊情况的处理清晰，代码可读性高。
  - **核心实现思想**：先判断是否能让所有人都达到理想的舍入值，再处理剩余银币的分配。
  - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int T;
ll n,k,g;
inline ll Solve(){
    ll mx=(g+1>>1)-1,res=0;
    if(k*g<=mx*n){
        return k*g;
    }
    ll d=k*g-mx*n;
    d%=g;
    if(!d){
        res+=mx*n;
    }
    else{
        if(mx+d<g){
            res-=g-mx-d;
        }
        else{
            res+=(mx+d)%g;
        }
        res+=mx*(n-1);
    }
    return res;
}
int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%lld%lld%lld",&n,&k,&g);
        printf("%lld\n",Solve());
    }
    return 0;
}
```
- **Natori（4星）**：
  - **关键亮点**：思路简洁，对贪心策略的解释清晰，能快速得出结果。
  - **核心实现思想**：先判断是否能让所有员工工资都不超过理想值，再确定最后一个人的工资。
  - **核心代码**：未给出完整代码，但思路为尽量让所有人工资为 $\left\lceil\dfrac{g}{2}\right\rceil - 1\pmod g$，最后一个人取 $k\times g-(n - 1)\times \left\lceil\dfrac{g}{2}\right\rceil$，若 $n\times(\left\lceil\dfrac{g}{2}\right\rceil - 1)\ge k\times g$，答案为 $k\times g$。

### 最优关键思路或技巧
- **贪心策略**：先让前 $n - 1$ 个人的银币数达到向下舍入的最大值 $\lceil\frac{g}{2}\rceil - 1$，再处理最后一个人的银币数，使公司节省的银币数最多。
- **特殊情况处理**：考虑银币未发完和节省的银币数超过总数的情况，避免错误结果。

### 可拓展之处
同类型题可能会有不同的分配规则和限制条件，但贪心的思想可以应用，即先找到局部最优解，再考虑整体最优。类似的算法套路如在资源分配、任务调度等问题中，先满足部分条件以达到最优效果，再处理剩余部分。

### 推荐洛谷题目
- P1094 [NOIP2007 普及组] 纪念品分组
- P1223 排队接水
- P1803 凌乱的yyy / 线段覆盖

### 个人心得摘录与总结
- **Jeefy**：自己做 Virtual Contest 时这道题打表打了半天（20min）才搞定。总结：当开始没有思路时，打表是一个很好的方法，可以帮助发现规律。 

---
处理用时：46.16秒