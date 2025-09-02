# 题目信息

# All Possible Digits

## 题目描述

A positive number $ x $ of length $ n $ in base $ p $ ( $ 2 \le p \le 10^9 $ ) is written on the blackboard. The number $ x $ is given as a sequence $ a_1, a_2, \dots, a_n $ ( $ 0 \le a_i < p $ ) — the digits of $ x $ in order from left to right (most significant to least significant).

Dmitry is very fond of all the digits of this number system, so he wants to see each of them at least once.

In one operation, he can:

- take any number $ x $ written on the board, increase it by $ 1 $ , and write the new value $ x + 1 $ on the board.

For example, $ p=5 $ and $ x=234_5 $ .

- Initially, the board contains the digits $ 2 $ , $ 3 $ and $ 4 $ ;
- Dmitry increases the number $ 234_5 $ by $ 1 $ and writes down the number $ 240_5 $ . On the board there are digits $ 0, 2, 3, 4 $ ;
- Dmitry increases the number $ 240_5 $ by $ 1 $ and writes down the number $ 241_5 $ . Now the board contains all the digits from $ 0 $ to $ 4 $ .

Your task is to determine the minimum number of operations required to make all the digits from $ 0 $ to $ p-1 $ appear on the board at least once.

## 样例 #1

### 输入

```
11
2 3
1 2
4 2
1 1 1 1
6 6
1 2 3 4 5 0
5 2
1 0 1 0 1
3 10
1 2 3
5 1000
4 1 3 2 5
3 5
2 3 4
4 4
3 2 3 0
1 3
2
5 5
1 2 2 2 4
3 4
1 0 1```

### 输出

```
1
1
0
0
7
995
2
1
1
1
2```

# AI分析结果

### 题目内容中文重写
# 所有可能的数字

## 题目描述
黑板上写着一个 $p$ 进制（$2 \le p \le 10^9$）的正数 $x$，其长度为 $n$。数字 $x$ 以序列 $a_1, a_2, \dots, a_n$（$0 \le a_i < p$）的形式给出，即 $x$ 的各位数字从左到右（从最高位到最低位）依次排列。

德米特里非常喜欢这个数制中的所有数字，所以他希望每个数字至少出现一次。

在一次操作中，他可以：
- 选取黑板上的任意一个数字 $x$，将其加 $1$，然后把新的值 $x + 1$ 写在黑板上。

例如，当 $p = 5$ 且 $x = 234_5$ 时：
- 最初，黑板上有数字 $2$、$3$ 和 $4$；
- 德米特里将数字 $234_5$ 加 $1$，并写下数字 $240_5$。此时黑板上有数字 $0$、$2$、$3$、$4$；
- 德米特里将数字 $240_5$ 加 $1$，并写下数字 $241_5$。现在黑板上包含了从 $0$ 到 $4$ 的所有数字。

你的任务是确定使从 $0$ 到 $p - 1$ 的所有数字至少在黑板上出现一次所需的最少操作次数。

## 样例 #1

### 输入
```
11
2 3
1 2
4 2
1 1 1 1
6 6
1 2 3 4 5 0
5 2
1 0 1 0 1
3 10
1 2 3
5 1000
4 1 3 2 5
3 5
2 3 4
4 4
3 2 3 0
1 3
2
5 5
1 2 2 2 4
3 4
1 0 1
```

### 输出
```
1
1
0
0
7
995
2
1
1
1
2
```

### 算法分类
模拟

### 题解分析与结论
本题的核心是给定一个 $p$ 进制数，通过不断对其加 $1$ 的操作，使得 $0$ 到 $p - 1$ 的所有数字都至少出现一次，求最少的操作次数。各题解的思路主要围绕分进位和不进位两种情况讨论，或者利用二分查找最小操作次数。

### 评分较高的题解
- **linyihdfj（5星）**
    - **亮点**：思路清晰，对进位和不进位的情况分类讨论详细，代码实现简洁明了，注释清晰。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 5e6+5;
int a[N];
map<int,bool> vis;
int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        int n,p;scanf("%d%d",&n,&p);
        for(int i=1; i<=n; i++) scanf("%d",&a[i]);
        for(int i=1; i<=n; i++) vis[a[i]] = true;
        reverse(a+1,a+n+1);
        bool flag = true;
        for(int i=a[1]; i>=max(a[1]-300,0); i--){
            if(!vis[i]){
                flag = false;
            }
        }
        set<int> st;
        int ans = 0;
        int limit = p - 1;
        if(!flag){  //必须进位 
            ans += p - 1 - a[1] + 1;
            limit = a[1] - 1;a[1] = 0;
            a[2]++;
            for(int i=2; i<=n; i++){
                if(a[i] == p) a[i] = 0,a[i+1]++;
            }
        }
        for(int i=1; i<=n; i++) vis[a[i]] = true;
        if(a[n+1]) vis[a[n+1]] = true;
        for(int i=limit; i>=max(limit-300,0); i--){
            if(!vis[i]){
                ans = ans + i - a[1]; 
                break;
            }
        }
        printf("%d\n",ans);
        vis.clear();
        for(int i=1; i<=n+1; i++) a[i] = 0;
    }
    return 0;
}
```
    - **核心实现思想**：先标记所有出现过的数字，然后判断是否需要进位。若需要进位，模拟进位过程并更新数字，再找到最大未出现的数字，计算操作次数。

- **Exschawasion（4星）**
    - **亮点**：思路严谨，对两种情况的分析清晰，代码简洁，有对疑问的解释。
    - **核心代码**：
```cpp
void sol(){
    set<int>s;
    cin>>n>>p;
    for(int i=n;i;i--)cin>>a[i],s.insert(a[i]);
    a[n+1]=0;
    if(s.size()==p)return cout<<0<<endl,void();
    int L=0,R=p-1;
    while(s.count(R))R--;
    while(s.count(L))L++;
    if(a[1]<L)return cout<<R-a[1]<<endl,void();
    int ans=0,v=a[1];
    ans+=p-a[1],a[1]=p;
    for(int i=1;i<=n;i++){
        if(a[i]>=p){
            a[i+1]+=a[i]/p,a[i]%=p;
        }
        s.insert(a[i]);
    }
    if(a[n+1])s.insert(a[n+1]);
    while(s.count(v))v--;
    cout<<ans+max(v,0)<<endl;
}
```
    - **核心实现思想**：先统计出现的数字，找到最大和最小未出现的数字。根据个位数字的情况判断是否需要进位，若需要进位则模拟进位过程，更新数字集合，最后计算操作次数。

### 最优关键思路或技巧
- **分类讨论**：分进位和不进位两种情况讨论，能更清晰地处理问题。
- **标记数字**：使用 `map` 或 `set` 标记出现过的数字，方便判断某个数字是否出现。
- **模拟进位**：当需要进位时，模拟高精度进位的过程，更新数字。

### 可拓展之处
同类型题可能会改变操作规则，如每次可以加一个固定的数，或者改变数字的表示方式等。类似算法套路可用于处理其他需要模拟操作过程的题目，如模拟游戏过程、模拟数据更新等。

### 推荐洛谷题目
- P1003 [铺地毯](https://www.luogu.com.cn/problem/P1003)
- P1047 [校门外的树](https://www.luogu.com.cn/problem/P1047)
- P1098 [字符串的展开](https://www.luogu.com.cn/problem/P1098)

### 个人心得摘录与总结
- **honglan0301**：提到没看懂题卡了半天，说明理解题意对解题的重要性。在遇到复杂题目时，要仔细研读题目条件和要求，确保理解正确。

---
处理用时：50.26秒