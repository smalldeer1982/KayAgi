# [GCJ 2018 #1A] Bit Party

## 题目描述

如今，机器人已经能够驾驶汽车，但它们能举办一场精彩的派对吗？Code Jam 团队对此的研究还处于初级阶段。我们刚刚派遣了 $\mathbf{R}$ 个机器人购物者到本地超市，为我们在多伦多举办的世界总决赛采购派对用品，但它们对加拿大派对的第一印象非常简单：它们只买了 $\mathbf{B}$ 个“bit”（bit 是当地一种小型甜甜圈状点心）。我们以后会继续改进它们的人工智能，但现在，我们希望帮助它们尽快购买完所有的 bit。

超市有 $\mathbf{C}$ 个收银员可以为顾客结账。第 $i$ 个收银员有如下特点：
- 每位顾客最多接受 $\mathbf{M}_{\mathbf{i}}$ 个商品
- 扫描每个商品需要 $\mathbf{S}_{\mathbf{i}}$ 秒
- 还需要额外花费 $\mathbf{P}_{\mathbf{i}}$ 秒用于收款和打包 bit

也就是说，一个顾客如果带着 $\mathrm{N}$ 个 bit 找到第 $i$ 个收银员（其中 $\mathrm{N}$ 必须不超过 $\mathbf{M}_{\mathbf{i}}$），则与该收银员的总交互时间为 $\mathbf{S}_{\mathbf{i}} \times \mathrm{N}+\mathbf{P}_{\mathbf{i}}$ 秒。

在机器人和收银员交互之前，你可以任意分配 bit 给机器人（bit 必须保持完整，不能拆分成小数部分！）。任何没有分到 bit 的机器人将无法与收银员交互，并会失望地离开。

接下来，对于每个至少分到一个 bit 的机器人，你需要为其选择一个不同的收银员。（两个机器人不能使用同一个收银员，一个机器人也不能使用多个收银员。）所有机器人会在时间 0 同时开始与各自的收银员交互。注意，一旦某个机器人完成了与收银员的交互，它不能再获得更多 bit，也不能与其他收银员交互。

如果你帮助机器人做出最优选择，所有机器人最早能在什么时候全部完成与收银员的交互？

## 说明/提示

**样例解释**

在样例 1 中，有两个机器人、两个 bit 和两个收银员，每个收银员最多只能处理一个商品。因此，必须给每个机器人分配一个 bit。收银员 1 需要 5 秒，收银员 2 需要 3 秒，所以所需时间为 5 秒。

样例 2 与前一个类似，但现在收银员 2 最多可以处理 2 个商品。因此，最优做法是将所有 bit 都分配给一个机器人，并让该机器人使用收银员 2。这样总共需要 $1$ 秒每个商品加上 $2$ 秒，共 $4$ 秒。

在样例 3 中，最优策略是让一个机器人带着 2 个 bit 去找收银员 2，另外两个机器人各带 1 个 bit 去找其他任意收银员。

**数据范围**

- $1 \leqslant \mathbf{T} \leqslant 100$。
- 对所有 $i$，$1 \leqslant \mathbf{M}_{\mathbf{i}} \leqslant 10^{9}$。
- 对所有 $i$，$1 \leqslant \mathbf{S}_{\mathbf{i}} \leqslant 10^{9}$。
- 对所有 $i$，$1 \leqslant \mathbf{P}_{\mathbf{i}} \leqslant 10^{9}$。
- $\mathbf{M}_{\mathbf{i}}$ 中最大的 $\mathbf{R}$ 个数之和 $\geqslant \mathbf{B}$。（即至少存在一组 $\mathbf{R}$ 个收银员可以处理所有 bit。）

**测试点 1（11 分，公开）**

- $1 \leqslant \mathbf{R} \leqslant \mathbf{C} \leqslant 5$。
- $1 \leqslant \mathbf{B} \leqslant 20$。

**测试点 2（21 分，隐藏）**

- $1 \leqslant \mathbf{R} \leqslant \mathbf{C} \leqslant 1000$。
- $1 \leqslant \mathbf{B} \leqslant 10^{9}$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
2 2 2
1 2 3
1 1 2
2 2 2
1 2 3
2 1 2
3 4 5
2 3 3
2 1 5
2 4 2
2 2 4
2 5 1```

### 输出

```
Case #1: 5
Case #2: 4
Case #3: 7```

# 题解

## 作者：tuxiaolai (赞：0)

# 1 说明
这题的细节很多，很容易错。~~也可能只有我错了。~~
# 2 审题
题意很简单，这里不再多说了。我们要找出一个最小的时间 $t$，并在 $c$ 个收营员中选择 $R$ 个，满足 $\max (N_i \times S_i + P_i) = t$，其中 $1 \le i \le R \le c,N_i \le m_i$。
# 3 二分
由于 $t$ 的范围非常大，因此我们可以用二分答案。  
对于一个 $t$，要遍历每个收营员，计算得第 $i$ 个收营员在 $t$ 秒内最多能够操作 $\max(0,\min(m_i,\lfloor \frac{t-p_i}{s_i} \rfloor))$ 个 bit。然后我们将每个收营员能够操作的 bit 数排序，并选出最大的 $R$ 个，与所需量 $b$ 比较即可。  
另外，也可以用优先队列，还可以省去 $O(R)$ 的复杂度。
# 4 AC CODE
```cpp
#include <bits/stdc++.h>
using namespace std;
long long T;
long long R,b,c;
long long m[1010],s[1010],p[1010];
long long ans;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>T;
    for(long long ca=1; ca<=T; ca++) {
        ans=0;
        cin>>R>>b>>c;
        for(long long i=1; i<=c; i++) {
            cin>>m[i]>>s[i]>>p[i];
        }
        long long l=1,r=LLONG_MAX;
        while(l<=r) {
            long long mid=l+(r-l)/2;
            priority_queue<long long,vector<long long>,greater<long long>> pq;
            long long sum=0;
            for(long long i=1;i<=c;i++){
                long long res=max(0,(int)min((long long)m[i],(mid-p[i])/s[i]));
                if(pq.size()<R){
                    pq.push(res);
                    sum+=res;
                }else{
                    if(pq.top()<res){
                        sum-=pq.top();
                        pq.pop();
                        pq.push(res);
                        sum+=res;
                    }
                }
            }
            if(sum<b){
                l=mid+1;
            }else{
                r=mid-1;
                ans=mid;
            }
        }
        cout<<"Case #"<<ca<<": "<<ans<<'\n';
    }
    return 0;
}
```
# 5 警告！！！
1. 如果你像我一样设 $r$ 的初始值为 `LLONG_MAX`，那一定要写 `mid=l+(r-l)/2`，而非 `mid=(l+r)/2`。
2. 注意 $\lfloor \frac{t-p_i}{s_i} \rfloor$ 可能是负数。
3. 如果你样例的第 3 个一直输出 6，那你可能没把题目中的 $R$ 与二分的 $r$ 区分开。

---

