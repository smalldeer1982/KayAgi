# 题目信息

# MEX Game 1

## 题目描述

Alice and Bob play yet another game on an array $ a $ of size $ n $ . Alice starts with an empty array $ c $ . Both players take turns playing, with Alice starting first.

On Alice's turn, she picks one element from $ a $ , appends that element to $ c $ , and then deletes it from $ a $ .

On Bob's turn, he picks one element from $ a $ , and then deletes it from $ a $ .

The game ends when the array $ a $ is empty. Game's score is defined to be the MEX $ ^\dagger $ of $ c $ . Alice wants to maximize the score while Bob wants to minimize it. Find game's final score if both players play optimally.

 $ ^\dagger $ The $ \operatorname{MEX} $ (minimum excludant) of an array of integers is defined as the smallest non-negative integer which does not occur in the array. For example:

- The MEX of $ [2,2,1] $ is $ 0 $ , because $ 0 $ does not belong to the array.
- The MEX of $ [3,1,0,1] $ is $ 2 $ , because $ 0 $ and $ 1 $ belong to the array, but $ 2 $ does not.
- The MEX of $ [0,3,1,2] $ is $ 4 $ , because $ 0 $ , $ 1 $ , $ 2 $ and $ 3 $ belong to the array, but $ 4 $ does not.

## 说明/提示

In the first test case, a possible game with a score of $ 2 $ is as follows:

1. Alice chooses the element $ 1 $ . After this move, $ a=[0,0,1] $ and $ c=[1] $ .
2. Bob chooses the element $ 0 $ . After this move, $ a=[0,1] $ and $ c=[1] $ .
3. Alice chooses the element $ 0 $ . After this move, $ a=[1] $ and $ c=[1,0] $ .
4. Bob chooses the element $ 1 $ . After this move, $ a=[\,] $ and $ c=[1,0] $ .

At the end, $ c=[1,0] $ , which has a MEX of $ 2 $ . Note that this is an example game and does not necessarily represent the optimal strategy for both players.

## 样例 #1

### 输入

```
3
4
0 0 1 1
4
0 1 2 3
2
1 1```

### 输出

```
2
1
0```

# AI分析结果



### 题目中文重写

**题目名称**：MEX游戏1

**题目描述**：  
Alice和Bob在一个大小为$n$的数组$a$上进行游戏。Alice从一个空数组$c$开始，两人轮流操作，Alice先手。

- **Alice的回合**：从$a$中选取一个元素，将其追加到$c$末尾，然后从$a$中删除该元素。  
- **Bob的回合**：从$a$中选取一个元素，直接删除它（不加入$c$）。  

游戏在$a$为空时结束，最终得分为$c$的$\text{MEX}$（最小未出现的非负整数）。Alice希望最大化得分，Bob希望最小化得分。求双方最优策略下的最终得分。

**输入输出样例**：  
输入样例1：  
```
3
4
0 0 1 1
4
0 1 2 3
2
1 1
```  
输出样例1：  
```
2
1
0
```

**说明/提示**：  
游戏得分由$c$的$\text{MEX}$决定。例如，当$c$为$[1,0]$时，$\text{MEX}$为2，因为0和1存在，2未出现。

---

### 算法分类  
**贪心**

---

### 题解分析与结论  

#### 核心思路总结  
1. **出现次数≥2的元素**：若某数出现次数≥2，Alice总能确保至少取到一次（Bob删一次，Alice取另一次）。  
2. **出现次数=1的元素**：Alice作为先手只能取第一个这样的数，Bob会优先删第二个出现次数=1的数。  
3. **答案的确定**：遍历从小到大的非负整数，找到第一个出现次数为0的数，或第二个出现次数为1的数，取其中较小者。  

#### 最优题解对比  
1. **题解作者：cute_overmind（4星）**  
   - **关键亮点**：直接统计出现次数，顺序遍历判断条件，代码简洁高效。  
   - **代码核心**：  
     ```cpp
     for(int i = 0; i <= n; i++){
         if(b[i] == 1 && flag == 0) flag = 1;
         else if(b[i] == 1 && flag){
             cout << i << '\n';
             return;
         }
         else if(b[i] == 0){
             cout << i << '\n';
             return;
         }
     }
     ```  
   - **实现思想**：用桶统计每个数的出现次数，遍历时记录第一个出现次数=1的数，遇到第二个或出现次数=0时输出。

2. **题解作者：Alex_Wei（4星）**  
   - **关键亮点**：逻辑清晰，指出答案由“第一个出现次数=0的数”或“至少两个出现次数=1的数”决定。  
   - **总结性结论**：若所有数的出现次数≥1，则答案是最小的出现次数=1的数的第二小值。

3. **题解作者：Accepted_Error（3星）**  
   - **个人心得**：强调出现次数≥2的数对结果无影响，需关注0和1次出现的数。  

---

### 关键实现技巧  
- **桶计数**：统计每个数的出现次数，避免重复计算。  
- **贪心遍历**：按非负整数顺序遍历，优先处理出现次数为0的情况，其次统计出现次数=1的数的顺序。  

---

### 拓展与举一反三  
- **类似题目**：  
  1. [CF1943B MEX Game 2](https://codeforces.com/contest/1943/problem/B)（进阶博弈与MEX结合）  
  2. [洛谷 P1247 取火柴游戏](https://www.luogu.com.cn/problem/P1247)（博弈论+贪心）  
  3. [洛谷 P2123 皇后游戏](https://www.luogu.com.cn/problem/P2123)（贪心策略排序）  

---

### 核心代码模板  
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5+5;
int cnt[N];

void solve() {
    int n; cin >> n;
    memset(cnt, 0, sizeof(int)*(n+2)); // 清空桶
    for(int i=0; i<n; i++) {
        int x; cin >> x;
        if(x <= n) cnt[x]++; // 统计出现次数
    }
    int flag = 0;
    for(int i=0; ; i++) {
        if(cnt[i] == 0) {
            cout << i << '\n';
            return;
        } else if(cnt[i] == 1) {
            if(flag) {
                cout << i << '\n';
                return;
            }
            flag = 1;
        }
    }
}

int main() {
    int t; cin >> t;
    while(t--) solve();
    return 0;
}
```  
**代码说明**：  
- 使用桶数组`cnt`统计每个数的出现次数。  
- 遍历时优先检查`cnt[i]==0`，其次处理第二个`cnt[i]==1`的情况。  
- 时间复杂度$O(n)$，空间复杂度$O(n)$。

---
处理用时：56.51秒