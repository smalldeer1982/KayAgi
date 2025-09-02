# 题目信息

# Zmei Gorynich

## 题目描述

You are fighting with Zmei Gorynich — a ferocious monster from Slavic myths, a huge dragon-like reptile with multiple heads!

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1217B/7c3f181294cd1faa21453100051e900a119a772c.png)Initially Zmei Gorynich has $ x $ heads. You can deal $ n $ types of blows. If you deal a blow of the $ i $ -th type, you decrease the number of Gorynich's heads by $ min(d_i, curX) $ , there $ curX $ is the current number of heads. But if after this blow Zmei Gorynich has at least one head, he grows $ h_i $ new heads. If $ curX = 0 $ then Gorynich is defeated.

You can deal each blow any number of times, in any order.

For example, if $ curX = 10 $ , $ d = 7 $ , $ h = 10 $ then the number of heads changes to $ 13 $ (you cut $ 7 $ heads off, but then Zmei grows $ 10 $ new ones), but if $ curX = 10 $ , $ d = 11 $ , $ h = 100 $ then number of heads changes to $ 0 $ and Zmei Gorynich is considered defeated.

Calculate the minimum number of blows to defeat Zmei Gorynich!

You have to answer $ t $ independent queries.

## 说明/提示

In the first query you can deal the first blow (after that the number of heads changes to $ 10 - 6 + 3 = 7 $ ), and then deal the second blow.

In the second query you just deal the first blow three times, and Zmei is defeated.

In third query you can not defeat Zmei Gorynich. Maybe it's better to convince it to stop fighting?

## 样例 #1

### 输入

```
3
3 10
6 3
8 2
1 4
4 10
4 1
3 2
2 6
1 100
2 15
10 11
14 100
```

### 输出

```
2
3
-1
```

# AI分析结果

### 题目内容重写
#### 题目描述
你正在与斯拉夫神话中的凶猛怪物——多头龙Zmei Gorynich战斗！它是一条巨大的龙形爬行动物，拥有多个头。

最初，Zmei Gorynich有 $x$ 个头。你可以使用 $n$ 种攻击方式。如果你使用第 $i$ 种攻击，你将减少 Gorynich 的头数 $min(d_i, curX)$，其中 $curX$ 是当前的头数。但如果攻击后 Zmei Gorynich 仍然有至少一个头，它会长出 $h_i$ 个新头。如果 $curX = 0$，则 Gorynich 被击败。

你可以以任意顺序使用任意次数的攻击。

例如，如果 $curX = 10$，$d = 7$，$h = 10$，那么头数将变为 $13$（你砍掉了 $7$ 个头，但 Zmei 又长出了 $10$ 个新头）。但如果 $curX = 10$，$d = 11$，$h = 100$，那么头数将变为 $0$，Zmei Gorynich 被击败。

计算击败 Zmei Gorynich 所需的最少攻击次数！

你需要回答 $t$ 个独立的查询。

#### 说明/提示
在第一个查询中，你可以先使用第一次攻击（头数变为 $10 - 6 + 3 = 7$），然后使用第二次攻击。

在第二个查询中，你只需使用第一次攻击三次，Zmei 就被击败了。

在第三个查询中，你无法击败 Zmei Gorynich。也许最好说服它停止战斗？

#### 样例 #1
##### 输入
```
3
3 10
6 3
8 2
1 4
4 10
4 1
3 2
2 6
1 100
2 15
10 11
14 100
```

##### 输出
```
2
3
-1
```

### 算法分类
贪心

### 题解分析与结论
该题的核心在于如何通过贪心策略选择最优的攻击方式，以最小化攻击次数。所有题解都采用了类似的思路：首先判断是否存在一刀秒杀的情况，然后计算在无法一刀秒杀的情况下，如何通过最大化每次攻击的净减少头数来最小化攻击次数。

### 高星题解
#### 题解1：作者 knsg251 (4星)
**关键亮点**：代码简洁，思路清晰，直接计算最大净减少头数，并通过公式计算最小攻击次数。
**代码实现**：
```cpp
#include <bits/stdc++.h>
using namespace std;
int t,n,x,ans,maxn;
int d[105],h[105];
int main(){
    cin>>t;
    while(t--){
        scanf("%d%d",&n,&x);
        ans = -9999;
        maxn = -9999;
        for(int i=1;i<=n;i++){
            scanf("%d%d",&d[i],&h[i]);
            ans = max(ans,d[i] - h[i]);
            maxn = max(maxn,d[i]);
        }
        if(maxn >= x){
            cout<<"1"<<endl;
        }else if(ans <= 0){
            cout<<"-1"<<endl;
        }else{
            cout<<(x - maxn + ans - 1) / ans + 1<<endl;
        }
    }
    return 0;
}
```

#### 题解2：作者 qpzc (4星)
**关键亮点**：思路与题解1类似，但使用了更简洁的公式计算最小攻击次数，代码可读性高。
**代码实现**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int t; cin>>t;
    while(t--){
        int n,x,mx1=-1e9,mx2=-1e9;
        cin>>n>>x;
        while(n--){
            int d,h; cin>>d>>h;
            mx1=max(mx1,d),mx2=max(mx2,d-h);
        }
        if(mx1>=x){puts("1");continue;}
        if(mx2<1){puts("-1");continue;}
        cout<<ceil((x-mx1)*1.0/mx2)+1<<endl;
    }
    return 0;
}
```

#### 题解3：作者 Dreamerly (4星)
**关键亮点**：代码结构清晰，使用了`ceil`函数进行上取整计算，思路明确。
**代码实现**：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main(){
    int T=read();
    while(T--){
        int n=read(),x=read();
        int sk_max=-1, k_max=-1;
        for(int i=1;i<=n;i++){
            int a=read(),b=read();
            sk_max=max(sk_max,a);
            k_max=max(k_max,a-b);
        }
        if(sk_max>=x){
            write(1),printf("\n");
            continue;
        }
        if(k_max<=0) write(-1);
        else         write(ceil(1.0*(x-sk_max)/k_max)+1);
        printf("\n");
    }
    return 0;
}
```

### 最优关键思路
1. **贪心策略**：每次选择净减少头数最大的攻击方式，以最小化攻击次数。
2. **特判处理**：首先判断是否存在一刀秒杀的情况，若存在则直接输出1；若所有攻击的净减少头数小于等于0，则输出-1。
3. **公式计算**：在无法一刀秒杀的情况下，通过公式 $\lceil \frac{x - max(d_i)}{max(d_i - h_i)} \rceil + 1$ 计算最小攻击次数。

### 可拓展之处
该题的贪心策略可以应用于类似的优化问题，如资源分配、任务调度等。通过最大化每次操作的净收益，可以有效地减少操作次数或资源消耗。

### 推荐题目
1. [P1007 独木桥](https://www.luogu.com.cn/problem/P1007)
2. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
3. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)

---
处理用时：46.44秒