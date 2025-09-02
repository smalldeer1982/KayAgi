# 题目信息

# New Game Plus!

## 题目描述

Wabbit is playing a game with $ n $ bosses numbered from $ 1 $ to $ n $ . The bosses can be fought in any order. Each boss needs to be defeated exactly once. There is a parameter called boss bonus which is initially $ 0 $ .

When the $ i $ -th boss is defeated, the current boss bonus is added to Wabbit's score, and then the value of the boss bonus increases by the point increment $ c_i $ . Note that $ c_i $ can be negative, which means that other bosses now give fewer points.

However, Wabbit has found a glitch in the game. At any point in time, he can reset the playthrough and start a New Game Plus playthrough. This will set the current boss bonus to $ 0 $ , while all defeated bosses remain defeated. The current score is also saved and does not reset to zero after this operation. This glitch can be used at most $ k $ times. He can reset after defeating any number of bosses (including before or after defeating all of them), and he also can reset the game several times in a row without defeating any boss.

Help Wabbit determine the maximum score he can obtain if he has to defeat all $ n $ bosses.

## 说明/提示

In the first test case, no resets are allowed. An optimal sequence of fights would be

- Fight the first boss $ (+0) $ . Boss bonus becomes equal to $ 1 $ .
- Fight the second boss $ (+1) $ . Boss bonus becomes equal to $ 2 $ .
- Fight the third boss $ (+2) $ . Boss bonus becomes equal to $ 3 $ .

Thus the answer for the first test case is $ 0+1+2=3 $ .

In the second test case, it can be shown that one possible optimal sequence of fights is

- Fight the fifth boss $ (+0) $ . Boss bonus becomes equal to $ 5 $ .
- Fight the first boss $ (+5) $ . Boss bonus becomes equal to $ 4 $ .
- Fight the second boss $ (+4) $ . Boss bonus becomes equal to $ 2 $ .
- Fight the third boss $ (+2) $ . Boss bonus becomes equal to $ -1 $ .
- Reset. Boss bonus becomes equal to $ 0 $ .
- Fight the fourth boss $ (+0) $ . Boss bonus becomes equal to $ -4 $ .

Hence the answer for the second test case is $ 0+5+4+2+0=11 $ .

## 样例 #1

### 输入

```
3 0
1 1 1```

### 输出

```
3```

## 样例 #2

### 输入

```
5 1
-1 -2 -3 -4 5```

### 输出

```
11```

## 样例 #3

### 输入

```
13 2
3 1 4 1 5 -9 -2 -6 -5 -3 -5 -8 -9```

### 输出

```
71```

# AI分析结果

### 题目翻译
# 新游戏+！

## 题目描述
兔子正在玩一款有 $n$ 个编号从 $1$ 到 $n$ 的 Boss 的游戏。这些 Boss 可以按任意顺序挑战，且每个 Boss 必须且仅需被击败一次。有一个名为 Boss 奖励的参数，初始值为 $0$。

当击败第 $i$ 个 Boss 时，当前的 Boss 奖励会被加到兔子的分数中，然后 Boss 奖励的值会增加分数增量 $c_i$。注意，$c_i$ 可能为负数，这意味着击败其他 Boss 获得的分数会减少。

然而，兔子发现了游戏中的一个漏洞。在游戏的任何时刻，他都可以重置游戏进度，开启一个“新游戏+”的游戏周目。这会将当前的 Boss 奖励重置为 $0$，而已被击败的 Boss 仍然保持已击败状态。当前的分数也会被保存，不会在重置操作后归零。这个漏洞最多可以使用 $k$ 次。他可以在击败任意数量的 Boss 后（包括在击败所有 Boss 之前或之后）进行重置，也可以连续多次重置而不击败任何 Boss。

请帮助兔子确定，如果他必须击败所有 $n$ 个 Boss，他能获得的最大分数是多少。

## 说明/提示
在第一个测试用例中，不允许进行重置操作。一个最优的挑战顺序是：
- 挑战第一个 Boss（$+0$），Boss 奖励变为 $1$。
- 挑战第二个 Boss（$+1$），Boss 奖励变为 $2$。
- 挑战第三个 Boss（$+2$），Boss 奖励变为 $3$。

因此，第一个测试用例的答案是 $0 + 1 + 2 = 3$。

在第二个测试用例中，可以证明一种可能的最优挑战顺序是：
- 挑战第五个 Boss（$+0$），Boss 奖励变为 $5$。
- 挑战第一个 Boss（$+5$），Boss 奖励变为 $4$。
- 挑战第二个 Boss（$+4$），Boss 奖励变为 $2$。
- 挑战第三个 Boss（$+2$），Boss 奖励变为 $-1$。
- 重置游戏，Boss 奖励变为 $0$。
- 挑战第四个 Boss（$+0$），Boss 奖励变为 $-4$。

因此，第二个测试用例的答案是 $0 + 5 + 4 + 2 + 0 = 11$。

## 样例 #1
### 输入
```
3 0
1 1 1
```
### 输出
```
3
```

## 样例 #2
### 输入
```
5 1
-1 -2 -3 -4 5
```
### 输出
```
11
```

## 样例 #3
### 输入
```
13 2
3 1 4 1 5 -9 -2 -6 -5 -3 -5 -8 -9
```
### 输出
```
71
```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路都是贪心算法，将 $k$ 次清零操作看作把所有 Boss 分成 $k + 1$ 组。主要步骤包括先对 $c_i$ 数组从大到小排序，以保证每组内元素单调不增，因为大数在前能使前缀和的贡献最大化。然后，每次选择当前和最大的组加入新的元素，这样能使本次操作的贡献和操作后的总和最优。实现时，多数题解使用优先队列（堆）来动态维护每组的和，以高效地找到当前和最大的组。

不同题解在具体处理负数元素和计算答案的方式上略有差异，但整体思路一致。部分题解还给出了贪心策略的证明，增强了算法的可靠性。

### 所选题解
- **gyh20（5星）**
    - **关键亮点**：思路清晰，直接点明是贪心算法，通过堆维护分组信息，代码实现简单且无细节问题，注释规范。
    - **个人心得**：无
- **IceKylin（4星）**
    - **关键亮点**：详细分析了贪心思路，给出了不严谨但易理解的证明，代码规范，有复杂度分析和数据范围提示。
    - **个人心得**：指出使用 DP 算法会有后效性且会 TLE，从而自然地想到贪心算法。
- **yuzhuo（4星）**
    - **关键亮点**：通过形象的“栈”的比喻解释分组问题，给出了感性的证明，代码简洁。
    - **个人心得**：无

### 重点代码
#### gyh20 的代码
```cpp
#include<bits/stdc++.h>
#define re register
#define int long long
using namespace std;
inline int read(){
    re int t=0,f=0;re char v=getchar();
    while(v<'0')f|=(v=='-'),v=getchar();
    while(v>='0')t=(t<<3)+(t<<1)+v-48,v=getchar();
    return f?-t:t;
}
priority_queue<int>q;
int n,m,t,a[1000002],h[1000002];
long long ans,sum;
signed main(){
    n=read(),m=read();
    for(re int i=1;i<=n;++i)a[i]=read();
    sort(a+1,a+n+1),reverse(a+1,a+n+1);
    for(re int i=1;i<=m+1;++i)q.push(0);
    for(re int i=1;i<=n;++i){
        int xx=q.top();
        q.pop();
        ans+=xx;
        xx+=a[i];
        q.push(xx);
    }
    printf("%lld",ans);
}
```
**核心实现思想**：先读取输入，对数组从大到小排序，将 $k + 1$ 个 $0$ 放入优先队列。然后遍历数组，每次从队列中取出最大值，累加到答案中，再将该值加上当前元素后放回队列。

#### IceKylin 的代码
```cpp
//By IceKylin
#include<bits/stdc++.h>
#define ll long long
#define il inline
#define maxn 1000050
using namespace std;
priority_queue<ll>q;
ll n,k,ans,a[maxn];

il bool cmp(ll x,ll y){
    return x>y;
}

int main(){
    ios::sync_with_stdio(false);
    cin>>n>>k;
    for(int i=1;i<=n;++i)cin>>a[i];
    sort(a+1,a+n+1,cmp);
    for(int i=1;i<=k+1;++i)q.push(0); 
    for(int i=1;i<=n;++i){
        ll val=q.top();
        q.pop();
        ans+=val;
        q.push(val+a[i]);
    }
    cout<<ans;
    return 0;
}
```
**核心实现思想**：读取输入后，对数组按从大到小排序，将 $k + 1$ 个 $0$ 放入优先队列。遍历数组，每次从队列中取出最大值，累加到答案中，再将该值加上当前元素后放回队列。

#### yuzhuo 的代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 5e5 + 7;
int n, k, a[N], sum;
priority_queue<int> q;
signed main() {
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    sort(a + 1, a + n + 1, greater<int>());
    for (int i = 1; i <= k + 1; ++i) q.push(0);
    for (int i = 1; i <= n; ++i) {
        int val = q.top(); q.pop();
        sum += val;
        val += a[i];
        q.push(val);
    }
    cout << sum << endl;
}
```
**核心实现思想**：读取输入，对数组从大到小排序，将 $k + 1$ 个 $0$ 放入优先队列。遍历数组，每次从队列中取出最大值，累加到答案中，再将该值加上当前元素后放回队列。

### 最优关键思路或技巧
- **贪心策略**：将问题转化为分成 $k + 1$ 组，每次选择当前和最大的组加入新元素，保证局部最优以达到全局最优。
- **数据结构**：使用优先队列（堆）动态维护每组的和，能在 $O(\log n)$ 时间内找到最大值，使整体时间复杂度为 $O(n\log n)$。

### 拓展思路
同类型题或类似算法套路通常涉及资源分配、任务调度等问题，解题关键在于找到合适的贪心策略，通过排序和合适的数据结构（如堆、优先队列）来实现。

### 推荐题目
- [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)：经典的贪心问题，使用优先队列实现。
- [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)：排队问题，通过排序实现贪心策略。
- [P2240 部分背包问题](https://www.luogu.com.cn/problem/P2240)：贪心算法解决背包问题。

### 个人心得摘录与总结
- **IceKylin**：提到使用 DP 算法会有后效性且会 TLE，从而自然地想到贪心算法。总结为在遇到有后效性或状态过多导致 TLE 的问题时，可以考虑贪心算法。 

---
处理用时：63.46秒