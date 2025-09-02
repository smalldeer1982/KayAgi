# [GCJ 2017 Qualification] Bathroom Stalls

## 题目描述

某间洗手间有 $N + 2$ 个隔间排成一排，最左端和最右端的隔间被洗手间管理员永久占用。其余 $N$ 个隔间供用户使用。

每当有人进入洗手间时，他们会尽量选择距离其他人最远的隔间。为避免混淆，他们遵循如下确定性规则：对于每一个空隔间 $S$，计算两个值 $L_S$ 和 $R_S$，分别表示 $S$ 到其左侧最近被占用隔间之间的空隔间数，以及到其右侧最近被占用隔间之间的空隔间数。然后，他们会考虑那些最近邻距离最远的隔间，即使得 $\min(L_S, R_S)$ 最大的所有 $S$。如果只有一个这样的隔间，则选择它；否则，在这些隔间中选择 $\max(L_S, R_S)$ 最大的那个。如果仍有多个隔间并列，则选择这些隔间中最靠左的一个。

有 $K$ 个人即将依次进入洗手间；每个人都会在下一个人到来前选择好自己的隔间。没有人会离开。

当最后一个人选择隔间 $S$ 时，对于他所选隔间，$\max(L_S, R_S)$ 和 $\min(L_S, R_S)$ 的值分别是多少？

## 说明/提示

**样例解释**

在样例 1 中，第一个人占据了中间两个隔间中最左边的一个，剩下的状态为（O 表示已占用，. 表示空）：`O.O..O`。然后，第二个人（也是最后一个人）占据了紧挨着右侧的隔间，此时一侧有 1 个空隔间，另一侧没有空隔间。

在样例 2 中，第一个人占据了中间的隔间，状态变为 `O..O..O`。然后，第二个人占据了最左边的隔间。

在样例 3 中，第一个人占据了两个中间隔间中最左边的一个，状态为 `O..O...O`。第二个人随后占据了连续三个空隔间中间的那个。

在样例 4 中，最后所有隔间都被占满，无论选择顺序如何。

在样例 5 中，唯一一个人选择了最左边的中间隔间。

**数据范围**

- $1 \leq T \leq 100$。
- $1 \leq K \leq N$。

**小数据集 1（5 分，测试点 1 - 可见）**

- $1 \leq N \leq 1000$。

**小数据集 2（10 分，测试点 2 - 可见）**

- $1 \leq N \leq 10^{6}$。

**大数据集（15 分，测试点 3 - 隐藏）**

- $1 \leq N \leq 10^{18}$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
5
4 2
5 2
6 2
1000 1000
1000 1```

### 输出

```
Case #1: 1 0
Case #2: 1 0
Case #3: 1 1
Case #4: 0 0
Case #5: 500 499```

# 题解

## 作者：__CuSO4__ (赞：2)

## 题解

可以发现，每次选择的隔间会将当前最大空隔间分成两部分，这两部分的长度分别为 $\lceil \frac{L-1}{2} \rceil$ 和 $\lfloor \frac{L-1}{2} \rfloor$。

我们可以维护每一个长度对应的区间个数，每次操作时找出长度最大的区间进行分裂，把子区间对应的个数更新，并将 $K$ 减去区间个数。

在 C++ 中，我们可以使用 STL 中的 `map` 来维护这样的内容，每次操作复杂度为 $O(\log_{2}{N})$。

总时间复杂度：$O(\log_{2}{NK})$。

注意：$1 \leq N \leq 10^{18}$，需要开 `long long`。

---
Code:
``` cpp
#include <iostream>
#include <map>
#include <cmath>
#define ll long long
using namespace std;

void solve(ll n, ll k, int t)
{
    map<ll, ll> a;
    a[n] = 1;
    ll maxn = 0, minn = 0;
    while (k > 0) 
	{
		//找出当前长度最大的区间，并删除 
        auto it = a.end();
        --it;
        ll len = it->first;
        ll num = it->second;
        a.erase(it);
		
        ll half1 = (len - 1) / 2;//保证在偶数情况下的正确性 
        ll half2 = len - 1 - half1;

        maxn = max(half1, half2);
        minn = min(half1, half2);

        if (half1 > 0) a[half1] += num;
        if (half2 > 0) a[half2] += num;

        k -= num;
    }
    cout << "Case #" << t << ": " << maxn << " " << minn << endl;
}

int main()
{
    int T;
    cin >> T;
    for (int t = 1; t <= T; t++)
	{
        ll n, k;
        cin >> n >> k;
        solve(n, k, t);
    }
    return 0;
}
```

---

## 作者：Frozen_Ladybug (赞：1)

经典数据结构题，使用映射和优先队列即可完成。

### 策略解释

本题中 $k$ 个人的位置选择策略为一个固定方案，可以等价地视作如下选择方式：

1. 对于第 $i$ 个人选择位置，必定是选择连续最长的无人座位区间 $[l,r]$；

2. 如果存在多个长度相等的区间 $[l,r]$，选择其中 $l$ 最小的那个；

3. 若区间 $[l,r]$ 的长度为 $N$，则：

    - 若 $N$ 为偶数，选择的座位为 $\lfloor\frac{l+r}{2}\rfloor$，区间被划分成新的区间 $[l,\frac{l+r-3}{2}]$ 和 $[\frac{l+r+1}{2},r]$；
   
    - 若 $N$ 为奇数，选择的座位为 $\frac{l+r}{2}$，区间被划分成新的区间 $[l,\frac{l+r}{2}-1]$ 和 $[\frac{l+r}{2}+1,r]$。
  
### 思路

问题只考虑求第 $k$ 个人选择的位置的最左端和最右端，故不需要具体考虑该位置的坐标，只需要知道该人选择的位置的区间长度即可。

然后用一个 ```map``` 建立映射，每次将查询的结果取出，进行累加即可。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,k,idx,ansm,ansM;
map<long long,long long> mp;
void solve(){
    long long p,q,t,cnt;
    idx=0;
    mp.clear();
    priority_queue<long long> que;
    que.push(n);
    mp[n]=1;
    while(!que.empty()){
        p=que.top();que.pop();
        cnt=mp[p];
        idx+=cnt;
        if(p%2){t=p/2;q=p/2;}
        else{t=p/2-1;q=p/2;}
        if(mp[q]) mp[q]+=cnt;
        else{mp[q]=cnt;que.push(q);}
        if(mp[t]) mp[t]+=cnt;
        else{mp[t]=cnt;que.push(t);}
        if(idx>=k){
            ansm=t;ansM=q;
            return;
        }
    }
}
int main(){
    int T;
    scanf("%d",&T);
    for(int i=1;i<=T;i++){
        scanf("%lld%lld",&n,&k);
        solve();
        printf("Case #%d: %lld %lld\n",i,ansM,ansm);
    }
    return 0;
}
```

---

