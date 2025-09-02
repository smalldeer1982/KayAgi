# 题目信息

# The Corridor or There and Back Again

## 题目描述

You are in a corridor that extends infinitely to the right, divided into square rooms. You start in room $ 1 $ , proceed to room $ k $ , and then return to room $ 1 $ . You can choose the value of $ k $ . Moving to an adjacent room takes $ 1 $ second.

Additionally, there are $ n $ traps in the corridor: the $ i $ -th trap is located in room $ d_i $ and will be activated $ s_i $ seconds after you enter the room $ \boldsymbol{d_i} $ . Once a trap is activated, you cannot enter or exit a room with that trap.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1872B/4c6bb8cafdaa97d3491d04295a1aa2f558037158.png) A schematic representation of a possible corridor and your path to room $ k $ and back.Determine the maximum value of $ k $ that allows you to travel from room $ 1 $ to room $ k $ and then return to room $ 1 $ safely.

For instance, if $ n=1 $ and $ d_1=2, s_1=2 $ , you can proceed to room $ k=2 $ and return safely (the trap will activate at the moment $ 1+s_1=1+2=3 $ , it can't prevent you to return back). But if you attempt to reach room $ k=3 $ , the trap will activate at the moment $ 1+s_1=1+2=3 $ , preventing your return (you would attempt to enter room $ 2 $ on your way back at second $ 3 $ , but the activated trap would block you). Any larger value for $ k $ is also not feasible. Thus, the answer is $ k=2 $ .

## 说明/提示

The first test case is explained in the problem statement above.

In the second test case, the second trap prevents you from achieving $ k\ge6 $ . If $ k\ge6 $ , the second trap will activate at the moment $ 3+s_2=3+3=6 $ (the time you enter room $ 4 $ plus $ s_2 $ ). In the case of $ k\ge6 $ , you will return to room $ 4 $ at time $ 7 $ or later. The trap will be active at that time. It can be shown that room $ k=5 $ can be reached without encountering an active trap.

In the third test case, you can make it to room $ 299 $ and then immediately return to room $ 1 $ .

## 样例 #1

### 输入

```
7
1
2 2
3
2 8
4 3
5 2
1
200 200
4
1 20
5 9
3 179
100 1
2
10 1
1 18
2
1 1
1 2
3
1 3
1 1
1 3```

### 输出

```
2
5
299
9
9
1
1```

# AI分析结果

### 题目翻译
# 走廊，来而复返

## 题目描述
你身处一条向右无限延伸的走廊，走廊被划分成一个个方形房间。你从 1 号房间出发，前往 $k$ 号房间，然后再返回 1 号房间。你可以自行选择 $k$ 的值。每移动到相邻的房间需要 1 秒。

此外，走廊上有 $n$ 个陷阱：第 $i$ 个陷阱位于 $d_i$ 号房间，且会在你进入 $d_i$ 号房间 $s_i$ 秒后被激活。一旦陷阱被激活，你就无法进入或离开设有该陷阱的房间。

![走廊及路径示意图](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1872B/4c6bb8cafdaa97d3491d04295a1aa2f558037158.png) 这是一个可能的走廊以及你前往 $k$ 号房间并返回的路径示意图。

请确定 $k$ 的最大值，使得你能够安全地从 1 号房间前往 $k$ 号房间，然后再返回 1 号房间。

例如，如果 $n = 1$ 且 $d_1 = 2$，$s_1 = 2$，你可以前往 $k = 2$ 号房间并安全返回（陷阱将在 $1 + s_1 = 1 + 2 = 3$ 秒时激活，这不会阻止你返回）。但如果你试图前往 $k = 3$ 号房间，陷阱将在 $1 + s_1 = 1 + 2 = 3$ 秒时激活，从而阻止你返回（你在返回途中会在第 3 秒尝试进入 2 号房间，但激活的陷阱会阻挡你）。任何更大的 $k$ 值也都不可行。因此，答案是 $k = 2$。

## 说明/提示
第一个测试用例在上述问题描述中已有解释。

在第二个测试用例中，第二个陷阱阻止你达到 $k \geq 6$。如果 $k \geq 6$，第二个陷阱将在 $3 + s_2 = 3 + 3 = 6$ 秒时激活（你进入 4 号房间的时间加上 $s_2$）。在 $k \geq 6$ 的情况下，你将在第 7 秒或更晚返回 4 号房间。此时陷阱已经激活。可以证明，能够到达 5 号房间而不会遇到激活的陷阱。

在第三个测试用例中，你可以到达 299 号房间，然后立即返回 1 号房间。

## 样例 #1
### 输入
```
7
1
2 2
3
2 8
4 3
5 2
1
200 200
4
1 20
5 9
3 179
100 1
2
10 1
1 18
2
1 1
1 1
3
1 3
1 1
1 3
```
### 输出
```
2
5
299
9
9
1
1
```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路都是围绕如何安全通过陷阱来确定最大的 $k$ 值。大部分题解通过计算每个陷阱允许到达的最远房间，然后取最小值得到最终结果；部分题解采用枚举或二分的方法来寻找答案。

### 所选题解
- **作者：guozhe6241（4星）**
    - **关键亮点**：思路简洁，直接通过计算 `d[i]+(s[i]+1)/2` 并取最小值得到结果，代码实现简单。
- **作者：Natori（4星）**
    - **关键亮点**：详细分析了如何计算每个陷阱限制的最远可到达点，对偶数情况的处理有清晰的说明，时间复杂度低。
- **作者：abensyl（4星）**
    - **关键亮点**：思路清晰，对贪心策略的解释明确，代码简洁，时间复杂度为 $O(n)$。

### 重点代码
- **作者：guozhe6241**
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+10;
int t,n;
int d[maxn],s[maxn];
int main(){
    cin>>t;
    for(int i=t;i>0;i--){
        int minn=0x3f3f3f3f;
        cin>>n;
        for(int j=1;j<=n;j++){
            cin>>d[i]>>s[i];
            minn=min(d[i]+(s[i]+1)/2,minn);
        }
        cout<<minn-1<<endl;
    }
    return 0;
}
```
**核心实现思想**：对于每个陷阱，计算 `d[i]+(s[i]+1)/2` 得到该陷阱允许到达的最远房间，取所有最远房间的最小值减 1 即为答案。

- **作者：Natori**
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=108,oo=1e9+8;
int n,a[N];
void solve(){
    n=read();
    int ans=oo;
    for(int i=1;i<=n;i++){
        int d=read(),s=read();
        if(s%2==0)
            s--;
        ans=min(ans,d+s/2);
    }
    write(ans),putchar('\n'); 
}
int main(){
    int testnum=read();
    while(testnum--)
        solve();	
    return 0;
}
```
**核心实现思想**：对于每个陷阱，若 $s_i$ 为偶数则减 1，然后计算 `d+s/2` 得到该陷阱允许到达的最远房间，取所有最远房间的最小值即为答案。

- **作者：abensyl**
```cpp
#include <bits/stdc++.h>
using namespace std;
void solve() {
    int n;
    cin>>n;
    int res=0x3fffffff;
    for(int i=1;i<=n;++i) {
        int d,s;
        cin>>d>>s;
        int tp=d+(s-1)/2;
        res=min(res,tp);
    } cout<<res<<'\n';
}
signed main() {
    int T;
    cin>>T;
    while(T--) {
        solve();
    }
    return 0;
}
```
**核心实现思想**：对于每个陷阱，计算 `d+(s-1)/2` 得到该陷阱允许到达的最远房间，取所有最远房间的最小值即为答案。

### 关键思路或技巧
- **贪心策略**：计算每个陷阱允许到达的最远房间，取最小值作为最终答案。
- **奇偶处理**：在计算最远房间时，需要考虑 $s_i$ 的奇偶性，确保在陷阱激活前能安全返回。

### 拓展思路
同类型题可能会增加陷阱的种类、移动规则的复杂度等，但核心思路仍然是考虑如何安全通过陷阱。类似算法套路可以应用于其他需要在限制条件下寻找最优解的问题。

### 推荐题目
- [P1007 独木桥](https://www.luogu.com.cn/problem/P1007)
- [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)
- [P1803 凌乱的yyy / 线段覆盖](https://www.luogu.com.cn/problem/P1803)

### 个人心得
- **作者：wanghaoran00**：提到在输出一堆奇奇怪怪的情况后总结出了针对偶数情况 `ans - 1` 的奇怪方法，说明在调试过程中需要不断尝试和总结。 

---
处理用时：47.54秒