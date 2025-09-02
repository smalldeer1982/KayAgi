# 题目信息

# Adjust The Presentation (Easy Version)

## 题目描述

This is the easy version of the problem. In the two versions, the constraints on $ q $ and the time limit are different. In this version, $ q=0 $ . You can make hacks only if all the versions of the problem are solved.

A team consisting of $ n $ members, numbered from $ 1 $ to $ n $ , is set to present a slide show at a large meeting. The slide show contains $ m $ slides.

There is an array $ a $ of length $ n $ . Initially, the members are standing in a line in the order of $ a_1, a_2, \ldots, a_n $ from front to back. The slide show will be presented in order from slide $ 1 $ to slide $ m $ . Each section will be presented by the member at the front of the line. After each slide is presented, you can move the member at the front of the line to any position in the lineup (without changing the order of the rest of the members). For example, suppose the line of members is $ [\color{red}{3},1,2,4] $ . After member $ 3 $ presents the current slide, you can change the line of members into either $ [\color{red}{3},1,2,4] $ , $ [1,\color{red}{3},2,4] $ , $ [1,2,\color{red}{3},4] $ or $ [1,2,4,\color{red}{3}] $ .

There is also an array $ b $ of length $ m $ . The slide show is considered good if it is possible to make member $ b_i $ present slide $ i $ for all $ i $ from $ 1 $ to $ m $ under these constraints.

However, your annoying boss wants to make $ q $ updates to the array $ b $ . In the $ i $ -th update, he will choose a slide $ s_i $ and a member $ t_i $ and set $ b_{s_i} := t_i $ . Note that these updates are persistent, that is changes made to the array $ b $ will apply when processing future updates.

For each of the $ q+1 $ states of array $ b $ , the initial state and after each of the $ q $ updates, determine if the slideshow is good.

## 说明/提示

For the first test case, you do not need to move the members as both slides are presented by member $ 1 $ , who is already at the front of the line.

For the second test case, the following is a possible way to move members so that the presentation is good:

1. $ [1,2,3] $ , do not move member $ 1 $ .
2. $ [1,2,3] $ , move member $ 1 $ after member $ 3 $ .
3. $ [2,3,1] $ , move member $ 2 $ after member $ 3 $ .
4. $ [3,2,1] $ , do not move member $ 3 $ .
5. $ [3,2,1] $ , move member $ 3 $ after member $ 1 $ .
6. $ [2,1,3] $ , do not move member $ 2 $ .

## 样例 #1

### 输入

```
3
4 2 0
1 2 3 4
1 1
3 6 0
1 2 3
1 1 2 3 3 2
4 6 0
3 1 4 2
3 1 1 2 3 4```

### 输出

```
YA
YA
TIDAK```

# AI分析结果



### 题目翻译
题目已为中文，无需翻译。

---

### 题解分析与结论

#### 核心思路
**关键观察**：每个元素的第一次出现顺序必须严格遵循其在初始排列中的顺序。具体来说，若元素在数组 `a` 中的位置为 `k`，则其在 `b` 中的第一次出现必须满足：
1. 所有比 `k` 小的位置对应的元素在 `a` 中的第一次出现必须在 `k` 之前。
2. 每次新出现的元素的位置必须是当前已处理元素的最大位置加1。

**解决方法**：
1. 预处理每个元素在 `a` 中的位置。
2. 遍历 `b` 数组，维护当前已处理元素的最大位置 `maxn`。
3. 对于每个元素的第一次出现，若其位置超过 `maxn+1`，则无法满足条件。

---

### 精选题解

#### 1. Colinxu2020 的题解（5星）
**亮点**：代码简洁，直接遍历 `b` 数组并维护最大位置，逻辑清晰。
```cpp
#include<iostream>
using namespace std;
const int maxn=2e5+10;
int t,n,m,q,ai[maxn],bi[maxn],mp[maxn];
int main(){
    cin>>t;
    while(t--){
        cin>>n>>m>>q;
        for(int i=1;i<=n;i++) cin>>ai[i],mp[ai[i]]=i;
        for(int i=1;i<=m;i++) cin>>bi[i],bi[i]=mp[bi[i]];
        int mx=0; bool flag=0;
        for(int i=1;i<=m&&!flag;i++){
            if(bi[i]>mx+1) flag=1; // 检查位置是否合法
            mx=max(mx, bi[i]);
        }
        cout<<(flag?"TIDAK":"YA")<<endl;
    }
}
```

#### 2. kanzaki 的题解（5星）
**亮点**：使用 `map` 记录位置，逻辑与代码均直观。
```cpp
#include <bits/stdc++.h>
using namespace std;
#define maxn 200005
int t,n,m,b[maxn];
map<int,int> mp;
void solve(){
    cin>>n>>m>>q;
    for(int i=1,x;i<=n;i++) cin>>x,mp[x]=i;
    for(int i=1,x;i<=m;i++) cin>>x,b[i]=mp[x];
    int mx=0;
    for(int i=1;i<=m;i++){
        if(b[i]>mx+1) { cout<<"TIDAK\n"; return; }
        mx=max(mx,b[i]);
    }
    cout<<"YA\n";
}
int main(){
    cin>>t;
    while(t--) solve();
}
```

#### 3. chenxi2009 的题解（4星）
**亮点**：理论推导完整，深入解释合法条件与 `a` 数组前缀的关系。

---

### 关键技巧总结
- **首次出现顺序验证**：只需检查每个元素的第一次出现是否形成连续的递增序列。
- **位置维护**：通过维护最大位置 `maxn`，确保中间无未处理的元素。

---

### 类似题目推荐
1. [P1966 火柴排队](https://www.luogu.com.cn/problem/P1966)  
   **考察点**：元素顺序调整的贪心策略。
2. [P1155 双栈排序](https://www.luogu.com.cn/problem/P1155)  
   **考察点**：合法操作序列的判断。
3. [P1233 木棍加工](https://www.luogu.com.cn/problem/P1233)  
   **考察点**：基于双重条件的贪心排序。

---
处理用时：298.36秒