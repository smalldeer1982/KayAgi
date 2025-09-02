# 题目信息

# Computer Game

## 题目描述

Vova is playing a computer game. There are in total $ n $ turns in the game and Vova really wants to play all of them. The initial charge of his laptop battery (i.e. the charge before the start of the game) is $ k $ .

During each turn Vova can choose what to do:

- If the current charge of his laptop battery is strictly greater than $ a $ , Vova can just play, and then the charge of his laptop battery will decrease by $ a $ ;
- if the current charge of his laptop battery is strictly greater than $ b $ ( $ b<a $ ), Vova can play and charge his laptop, and then the charge of his laptop battery will decrease by $ b $ ;
- if the current charge of his laptop battery is less than or equal to $ a $ and $ b $ at the same time then Vova cannot do anything and loses the game.

Vova wants to complete the game (Vova can complete the game if after each of $ n $ turns the charge of the laptop battery is strictly greater than $ 0 $ ). Among all possible ways to complete the game, Vova wants to choose the one where the number of turns when he just plays is the maximum possible. It is possible that Vova cannot complete the game at all.

Your task is to find out the maximum possible number of turns Vova can just play or report that Vova cannot complete the game.

You have to answer $ q $ independent queries.

## 说明/提示

In the first example query Vova can just play $ 4 $ turns and spend $ 12 $ units of charge and then one turn play and charge and spend $ 2 $ more units. So the remaining charge of the battery will be $ 1 $ .

In the second example query Vova cannot complete the game because even if he will play and charge the battery during each turn then the charge of the notebook battery will be $ 0 $ after the last turn.

## 样例 #1

### 输入

```
6
15 5 3 2
15 5 4 3
15 5 2 1
15 5 5 1
16 7 5 2
20 5 7 3
```

### 输出

```
4
-1
5
2
0
1
```

# AI分析结果

【题目内容】
# 电脑游戏

## 题目描述

Vova正在玩一款电脑游戏。游戏总共有$n$个回合，Vova非常想玩完所有的回合。他的笔记本电脑电池的初始电量（即游戏开始前的电量）为$k$。

在每一回合中，Vova可以选择以下操作：

- 如果当前笔记本电脑电池的电量严格大于$a$，Vova可以直接玩游戏，然后电池电量会减少$a$；
- 如果当前笔记本电脑电池的电量严格大于$b$（$b<a$），Vova可以玩游戏并给笔记本电脑充电，然后电池电量会减少$b$；
- 如果当前笔记本电脑电池的电量同时小于或等于$a$和$b$，那么Vova无法进行任何操作并输掉游戏。

Vova希望完成游戏（如果Vova在每一回合结束后电池电量都严格大于$0$，那么他就可以完成游戏）。在所有可能的完成游戏的方式中，Vova希望选择直接玩游戏的回合数最多的一种方式。有可能Vova根本无法完成游戏。

你的任务是找出Vova可以直接玩游戏的最大回合数，或者报告Vova无法完成游戏。

你需要回答$q$个独立的查询。

## 说明/提示

在第一个示例查询中，Vova可以直接玩$4$个回合，消耗$12$单位的电量，然后在一个回合中玩游戏并充电，消耗$2$单位的电量。因此，电池的剩余电量将为$1$。

在第二个示例查询中，Vova无法完成游戏，因为即使他在每个回合中都玩游戏并充电，笔记本电池的电量在最后一个回合后将为$0$。

## 样例 #1

### 输入

```
6
15 5 3 2
15 5 4 3
15 5 2 1
15 5 5 1
16 7 5 2
20 5 7 3
```

### 输出

```
4
-1
5
2
0
1
```

【算法分类】
数学

【题解分析与结论】
本题的核心在于通过数学推导找到Vova可以直接玩游戏的最大回合数。大多数题解都采用了类似“鸡兔同笼”的思路，通过计算每回合直接玩游戏和充电玩游戏的耗电差异，推导出最大直接玩游戏的回合数。难点在于如何处理边界条件，确保最终电量严格大于0。

【评分较高的题解】
1. **作者：wucstdio (5星)**
   - **关键亮点**：简洁明了地推导出公式，直接通过数学计算得出结果，时间复杂度为$O(1)$。
   - **代码实现**：
     ```cpp
     #include<cstdio>
     #include<algorithm>
     #include<cstring>
     #define ll long long
     using namespace std;
     ll t,k,n,a,b;
     int main()
     {
         scanf("%I64d",&t);
         while(t--)
         {
             scanf("%I64d%I64d%I64d%I64d",&k,&n,&a,&b);
             k-=b*n;
             if(k<=0)
             {
                 printf("-1\n");
                 continue;
             }
             printf("%I64d\n",min((k-1)/(a-b),n));
         }
         return 0;
     }
     ```

2. **作者：WydnksqhbD (4星)**
   - **关键亮点**：通过方程组推导出结果，代码简洁，时间复杂度为$O(q)$。
   - **代码实现**：
     ```cpp
     #include<bits/stdc++.h>
     #define int long long
     #define endl '\n'
     using namespace std;
     int q,k,n,a,b;
     signed main()
     {
         ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
         cin>>q;
         while(q--)
         {
             cin>>k>>n>>a>>b;k--;
             if(b*n>k)puts("-1");
             else printf("%lld",min(n,(k-b*n)/(a-b)));
             putchar('\n');
         }
         return 0;
     }
     ```

3. **作者：lbh666 (4星)**
   - **关键亮点**：通过假设法推导出结果，代码清晰，时间复杂度为$O(q)$。
   - **代码实现**：
     ```cpp
     #include<bits/stdc++.h>
     #define ll long long
     using namespace std;
     ll t;
     int main(){
         cin>>t;
         for(ll i=1;i<=t;++i){
             ll k,n,a,b,ans;
             cin>>k>>n>>a>>b;
             if(n*b>=k){
                 cout<<"-1\n";
             }else{
                 ans=min(n,(k-n*b-1)/(a-b));
                 cout<<ans<<"\n";
             }
         }
         return 0;
     }
     ```

【最优关键思路】
通过数学推导，计算出每回合直接玩游戏和充电玩游戏的耗电差异，最终得出最大直接玩游戏的回合数。公式为：$\min\left(n,\left\lfloor\frac{(k-nb-1)}{a-b}\right\rfloor\right)$。

【拓展思路】
类似的问题可以通过数学推导来解决，尤其是在涉及到资源分配和优化的情况下。可以通过建立方程组或不等式来找到最优解。

【推荐题目】
1. [CF1183C - Computer Game](https://www.luogu.com.cn/problem/CF1183C)
2. [P1020 导弹拦截](https://www.luogu.com.cn/problem/P1020)
3. [P1007 独木桥](https://www.luogu.com.cn/problem/P1007)

---
处理用时：35.33秒