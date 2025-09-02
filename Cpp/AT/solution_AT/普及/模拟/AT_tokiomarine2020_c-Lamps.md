# Lamps

## 题目描述

# Lamps


[problemUrl]: https://atcoder.jp/contests/tokiomarine2020/tasks/tokiomarine2020_c

给定 $ N $ 个灯泡，其亮度分别为 $ A_i $。每个灯泡的作用范围为 $ i-A_i-0.5$ 到 $ i+A_i+0.5 $。

有 $ K $ 轮操作。

每轮操作使得每个灯泡的亮度更改为照亮它的灯泡的个数。

## 说明/提示

- $ 1\ \leqq\ N\ \leqq\ 2\ \times\ 10^5 $
- $ 1\ \leqq\ K\ \leqq\ 2\ \times\ 10^5 $
- $ 0\ \leqq\ A_i\ \leqq\ N $

### 样例1解释 

$ 1 $ 号数只有第 $ 1 $ 个数本身作用 ，第 $ 2 $ 个数有第 $ 1 $ 和 第 $ 2 $ 个数作用，以此类推。

## 样例 #1

### 输入

```
5 1
1 0 0 1 0```

### 输出

```
1 2 2 1 2```

## 样例 #2

### 输入

```
5 2
1 0 0 1 0```

### 输出

```
3 3 4 4 3```

# 题解

## 作者：Petit_Souris (赞：5)

目前题解区所有复杂度没有证明的题解已经全部撤下。

做法是很简单的，直接暴力做变换，每次用差分实现区间加，复杂度 $\mathcal O(nk)$。

我们可以加上一个剪枝：当整个序列所有数都变成 $n$ 了，序列就不再变化了，这样就可以通过了。我们证明这样做至多操作 $\mathcal O(\log n)$ 次：

首先，当所有 $a_i=0$ 时操作次数最多。

设 $b$ 为差分序列，则当 $\forall a_i\le a'_i$ 时，$b_i\le b'_i$，这就证明了上面这一点。


第一次操作后，每个数都 $\ge 1$，因为都被自己覆盖；

第二次操作后，两端都 $\ge 2$，因为会被自己以及左边或者右边的一个覆盖，而中间的数都 $\ge 3$，因为会被自己以及左右两边两个数覆盖；

第三次操作后，所有数都 $\ge 4$；第四次操作后，所有数都 $\ge 8$......直到中间出现了一个数，它变成了 $n$（这个时刻必然会出现，至多 $\mathcal O(\log n)$ 次后出现，因为每次 $\times 2$）。

此时，其他的数都 $\ge \frac{n}{2}$。第一次操作，第一个 $n$ 的左右两个变成 $n$；第二次操作，左右四个变成 $n$......依次类推，再经过 $\mathcal O(\log n)$ 次后所有数都会变成 $n$。因此复杂度为 $\mathcal O(n\log n)$。

写个程序也能验证，至多 $41$ 次后全部变成 $n$。

---

## 作者：DashZhanghanxu (赞：1)

# 解析
本题主要思路就是用前缀和差分降低时间复杂度。

代码中的灯泡数量为 $N$ 和操作轮数为 $K$ 以及初始亮度数组 $A$。

每轮操作使用差分数组 $diff$ 记录每个位置的覆盖次数。

通过前缀和将差分数组转换为每个位置的实际覆盖次数，生成新的亮度数组 $neww$。

检查新数组是否与旧数组相同，若相同则提前终止循环。

最后输出最终亮度数组。

该方法通过差分数组和前缀和优化，将每轮操作的时间复杂度降至O(N)，并通过减少不必要情况计算以降低时间复杂度。
# CODE
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(false);
    int N,K;
    cin>>N>>K;
    vector<int>A(N);
    for(int i=0;i<N;++i)cin>>A[i];
    for(int k=0;k<K;++k){
        vector<int>dif(N+1,0);
        for(int i=0;i<N;++i){
            int a=A[i];
            int cur=i+1;
            int L=max(1,cur-a);
            int R=min(N,cur+a);
            L--;R--;
            if(L>R) continue;
            dif[L]++;dif[R+1]--;
        }
        vector<int>neww(N);
        int sum=0;
        for(int i=0;i<N;++i){sum+=dif[i];neww[i]=sum;}
        if(neww==A) break;
        A.swap(neww);
    }
    for(int i=0;i<N;++i){cout<<A[i]<<(i==N-1?"\n":" ");}
    return 0;
}
```

---

