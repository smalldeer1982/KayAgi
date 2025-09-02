# Toy Train

## 题目描述

Alice received a set of Toy Train™ from Bob. It consists of one train and a connected railway network of $ n $ stations, enumerated from $ 1 $ through $ n $ . The train occupies one station at a time and travels around the network of stations in a circular manner. More precisely, the immediate station that the train will visit after station $ i $ is station $ i+1 $ if $ 1 \leq i < n $ or station $ 1 $ if $ i = n $ . It takes the train $ 1 $ second to travel to its next station as described.

Bob gave Alice a fun task before he left: to deliver $ m $ candies that are initially at some stations to their independent destinations using the train. The candies are enumerated from $ 1 $ through $ m $ . Candy $ i $ ( $ 1 \leq i \leq m $ ), now at station $ a_i $ , should be delivered to station $ b_i $ ( $ a_i \neq b_i $ ).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1129A2/553bfb305c93eff18c75fbd09eed41cc245d82d0.png)The blue numbers on the candies correspond to $ b_i $ values. The image corresponds to the $ 1 $ -st example.The train has infinite capacity, and it is possible to load off any number of candies at a station. However, only at most one candy can be loaded from a station onto the train before it leaves the station. You can choose any candy at this station. The time it takes to move the candies is negligible.

Now, Alice wonders how much time is needed for the train to deliver all candies. Your task is to find, for each station, the minimum time the train would need to deliver all the candies were it to start from there.

## 说明/提示

Consider the second sample.

If the train started at station $ 1 $ , the optimal strategy is as follows.

1. Load the first candy onto the train.
2. Proceed to station $ 2 $ . This step takes $ 1 $ second.
3. Deliver the first candy.
4. Proceed to station $ 1 $ . This step takes $ 1 $ second.
5. Load the second candy onto the train.
6. Proceed to station $ 2 $ . This step takes $ 1 $ second.
7. Deliver the second candy.
8. Proceed to station $ 1 $ . This step takes $ 1 $ second.
9. Load the third candy onto the train.
10. Proceed to station $ 2 $ . This step takes $ 1 $ second.
11. Deliver the third candy.

Hence, the train needs $ 5 $ seconds to complete the tasks.

If the train were to start at station $ 2 $ , however, it would need to move to station $ 1 $ before it could load the first candy, which would take one additional second. Thus, the answer in this scenario is $ 5+1 = 6 $ seconds.

## 样例 #1

### 输入

```
5 7
2 4
5 1
2 3
3 4
4 1
5 3
3 5
```

### 输出

```
10 9 10 10 9 
```

## 样例 #2

### 输入

```
2 3
1 2
1 2
1 2
```

### 输出

```
5 6 
```

# 题解

## 作者：luo_shen (赞：1)

**题意**  
给定一个环，环上 $n$ 个点，$m$ 个糖，告诉你这个糖要从点 $x$ 拿到点 $y$，每次经过一个点只能拿一个糖，但可以放任意数量的糖。只能从点 $1$ 经过中间的点到点 $n$，再从点 $n$ 走一步到点 $1$。问将所有糖果运送完毕至少应经过多少步。  
**解析**  
贪心地考虑，如果一个点 $i$ 有 $sum_i$ 颗糖果，那么肯定先取要走步数多的，那么留到最后的那颗糖果自然是以该点为起点要走步数最少的，将其记为 $min_i$。那么对于每一个 $i$ 都有：
$$ans_i=\max\limits_{j=1,sum_j>0}^n(sum_j-1)\times n+min_j+(j-i+n)\%n$$  
**代码**  
```
#include<bits/stdc++.h>
using namespace std;
int n,m,x,y,mn[5010],sum[5010];
int main(){
    memset(mn,0x3f,sizeof(mn));
    cin>>n>>m;
    for(int i=1;i<=m;i++){//(i-j+n)%n表示在环上从x走到y所需步数
        cin>>x>>y;
        mn[x]=min(mn[x],(y-x+n)%n);
        sum[x]++;//处理出每个点的mn[i]和sum[i]
    }
    for(int i=1;i<=n;i++){
        int ans=0;
        for(int j=1;j<=n;j++){
            if(!sum[j])continue;
            int s=(sum[j]-1)*n+mn[j]+(j-i+n)%n;
            ans=max(ans,s);
        }
        cout<<ans<<' ';
    }
    return 0;
}
```

---

