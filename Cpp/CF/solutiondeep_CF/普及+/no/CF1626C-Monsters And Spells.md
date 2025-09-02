# 题目信息

# Monsters And Spells

## 题目描述

Monocarp is playing a computer game once again. He is a wizard apprentice, who only knows a single spell. Luckily, this spell can damage the monsters.

The level he's currently on contains $ n $ monsters. The $ i $ -th of them appears $ k_i $ seconds after the start of the level and has $ h_i $ health points. As an additional constraint, $ h_i \le k_i $ for all $ 1 \le i \le n $ . All $ k_i $ are different.

Monocarp can cast the spell at moments which are positive integer amounts of second after the start of the level: $ 1, 2, 3, \dots $ The damage of the spell is calculated as follows. If he didn't cast the spell at the previous second, the damage is $ 1 $ . Otherwise, let the damage at the previous second be $ x $ . Then he can choose the damage to be either $ x + 1 $ or $ 1 $ . A spell uses mana: casting a spell with damage $ x $ uses $ x $ mana. Mana doesn't regenerate.

To kill the $ i $ -th monster, Monocarp has to cast a spell with damage at least $ h_i $ at the exact moment the monster appears, which is $ k_i $ .

Note that Monocarp can cast the spell even when there is no monster at the current second.

The mana amount required to cast the spells is the sum of mana usages for all cast spells. Calculate the least amount of mana required for Monocarp to kill all monsters.

It can be shown that it's always possible to kill all monsters under the constraints of the problem.

## 说明/提示

In the first testcase of the example, Monocarp can cast spells $ 3, 4, 5 $ and $ 6 $ seconds from the start with damages $ 1, 2, 3 $ and $ 4 $ , respectively. The damage dealt at $ 6 $ seconds is $ 4 $ , which is indeed greater than or equal to the health of the monster that appears.

In the second testcase of the example, Monocarp can cast spells $ 3, 4 $ and $ 5 $ seconds from the start with damages $ 1, 2 $ and $ 3 $ , respectively.

In the third testcase of the example, Monocarp can cast spells $ 4, 5, 7, 8 $ and $ 9 $ seconds from the start with damages $ 1, 2, 1, 1 $ and $ 2 $ , respectively.

## 样例 #1

### 输入

```
3
1
6
4
2
4 5
2 2
3
5 7 9
2 1 2```

### 输出

```
10
6
7```

# AI分析结果

### 题目内容中文重写
# 怪物与法术

## 题目描述
Monocarp 又在玩一款电脑游戏了。他是一名巫师学徒，只会一个法术。幸运的是，这个法术可以对怪物造成伤害。

他当前所在的关卡中有 $n$ 个怪物。第 $i$ 个怪物在关卡开始后的 $k_i$ 秒出现，拥有 $h_i$ 点生命值。此外，对于所有 $1 \le i \le n$，都有 $h_i \le k_i$，且所有的 $k_i$ 都不同。

Monocarp 可以在关卡开始后的正整数秒时刻释放法术，即 $1, 2, 3, \dots$ 法术的伤害计算方式如下：如果他在上一秒没有释放法术，那么此次法术的伤害为 $1$；否则，假设上一秒法术的伤害为 $x$，那么他可以选择此次法术的伤害为 $x + 1$ 或 $1$。释放一次伤害为 $x$ 的法术需要消耗 $x$ 点法力值，且法力值不会自动恢复。

为了杀死第 $i$ 个怪物，Monocarp 必须在怪物出现的精确时刻 $k_i$ 释放一次伤害至少为 $h_i$ 的法术。

注意，即使当前时刻没有怪物出现，Monocarp 也可以释放法术。

释放法术所需的法力值总量是所有释放法术消耗法力值的总和。请计算 Monocarp 杀死所有怪物所需的最少法力值。

可以证明，在题目给定的约束条件下，总是可以杀死所有怪物的。

## 说明/提示
在样例的第一个测试用例中，Monocarp 可以在关卡开始后的第 $3$、$4$、$5$ 和 $6$ 秒分别释放伤害为 $1$、$2$、$3$ 和 $4$ 的法术。在第 $6$ 秒释放的法术伤害为 $4$，确实大于或等于此时出现的怪物的生命值。

在样例的第二个测试用例中，Monocarp 可以在关卡开始后的第 $3$、$4$ 和 $5$ 秒分别释放伤害为 $1$、$2$ 和 $3$ 的法术。

在样例的第三个测试用例中，Monocarp 可以在关卡开始后的第 $4$、$5$、$7$、$8$ 和 $9$ 秒分别释放伤害为 $1$、$2$、$1$、$1$ 和 $2$ 的法术。

## 样例 #1
### 输入
```
3
1
6
4
2
4 5
2 2
3
5 7 9
2 1 2
```
### 输出
```
10
6
7
```

### 算法分类
贪心

### 综合分析与结论
这些题解主要围绕如何在满足杀死所有怪物的条件下，最小化法力消耗展开。大部分题解的核心思路是将每个怪物转化为一个时间区间，即从需要开始积累伤害的时刻到怪物出现的时刻，然后根据区间的相交情况进行合并，最后计算合并后区间的法力消耗（通常是等差数列求和）。不同题解在具体实现和细节处理上有所差异。

### 所选题解
- **feicheng（5星）**：
    - **关键亮点**：思路清晰，先指出简单贪心的缺陷，然后引入动态规划思想，通过状态转移方程 $f_i=\max\{h_i,f_{i+1}-\Delta k\}$ 计算每个怪物所需的法力值，再根据不同情况计算花费，代码实现简洁明了。
- **_Diu_（4星）**：
    - **关键亮点**：将问题转化为区间合并问题，通过排序和暴力合并区间的方式，最后计算合并后区间的答案，思路直观易懂，代码实现简单。
- **Argon_Cube（4星）**：
    - **关键亮点**：同样采用区间合并的思路，使用 `vector` 存储区间，通过排序和合并操作，最后计算总消耗，代码逻辑清晰。

### 重点代码与核心思想
#### feicheng 的代码
```cpp
inline void solve() {
  clear();
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> k[i];
  }
  for (int i = 1; i <= n; ++i) {
    cin >> h[i];
  } 
  f[n] = h[n];
  for (int i = n - 1; i >= 1; --i) {
    auto delta = k[i + 1] - k[i];
    f[i] = std::max(f[i + 1] - delta, h[i]);
  }
  long long ans = calc(1, f[1], f[1]), d = f[1];
  for (int i = 1; i < n; ++i) {
    auto delta = k[i + 1] - k[i];
    if (f[i + 1] <= delta) {
      ans += calc(1, f[i + 1], f[i + 1]);
      d = f[i + 1];
    }
    else {
      ans += calc(d + 1, d + delta, delta);
      d += delta;
    }
  }
  cout << ans <<  '\n';
}
```
**核心思想**：先从后往前计算每个怪物所需的法力值 $f_i$，然后根据相邻怪物之间的时间间隔和下一个怪物所需的法力值，判断是否可以将伤害归为 $1$，并计算相应的花费，最后得到总花费。

#### _Diu_ 的代码
```cpp
signed main(){
  scanf("%lld",&t);
  for(;t--;){
    scanf("%lld",&n);
    for(int i=1;i<=n;i++)scanf("%lld",&k[i]);
    for(int i=1;i<=n;i++){
      scanf("%lld",&h[i]);
      e[i]={k[i]-h[i]+1,k[i]};
    }
    sort(e+1,e+n+1,cmp);
    int ans=0,hei=0;
    for(int i=2;i<=n;i++){
      if(e[i].l<=e[i-1].r)e[i-1].r=max(e[i-1].r,e[i].r),del(i),--i;
    }
    for(int i=1;i<=n;i++)ans+=(e[i].r-e[i].l+1)*(e[i].r-e[i].l+2)/2;
    printf("%lld\n",ans);
  }
}
```
**核心思想**：将每个怪物转化为一个区间，按区间左端点排序，然后合并相交的区间，最后计算合并后区间的法力消耗（等差数列求和）。

#### Argon_Cube 的代码
```cpp
int main(int argc,char* argv[],char* envp[])
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int testcnt;
  cin>>testcnt;
  while(testcnt--)
  {
    ranges.clear();
    int cnt,last_t=0,last_h=0,cur,cur_t,cur_h;
    long long ans=0;
    cin>>cnt;
    for(int i=0;i<cnt;i++)
      cin>>timeps[i];
    for(int i=0;i<cnt;i++)
      cin>>healths[i];
    for(int i=0;i<cnt;i++)
      ranges.push_back(make_pair(timeps[i]-healths[i]+1,timeps[i]));
    sort(ranges.begin(),ranges.begin()+cnt);
    for(int i=0;i<ranges.size()-1;i++)
      if(ranges[i+1].first<=ranges[i].second)
        ranges[i].second=max(ranges[i+1].second,ranges[i].second),ranges.erase(ranges.begin()+i+1),--i;
    for(int i=0;i<ranges.size();i++)
    {
      long long len=ranges[i].second-ranges[i].first+1;
      ans+=len*(len+1)/2;
    }
    cout<<ans<<'\n';
  }
  return 0;
}
```
**核心思想**：将每个怪物转化为一个区间，存储在 `vector` 中，排序后合并相交的区间，最后计算合并后区间的法力消耗（等差数列求和）。

### 最优关键思路或技巧
- **区间转化**：将每个怪物的出现时间和生命值转化为一个时间区间，方便处理和合并。
- **区间合并**：通过合并相交的区间，避免重复计算法力消耗，从而得到最小的总消耗。

### 可拓展之处
同类型题可能会改变怪物的属性（如出现时间、生命值的计算方式）、法术的规则（如伤害增长方式、法力恢复规则）或增加其他限制条件（如法力上限、法术冷却时间）。类似的算法套路可以应用于任务调度、资源分配等问题中，通过将任务或资源需求转化为区间，然后进行合并和优化。

### 推荐洛谷题目
- [P1803 凌乱的yyy / 线段覆盖](https://www.luogu.com.cn/problem/P1803)
- [P2082 区间覆盖](https://www.luogu.com.cn/problem/P2082)
- [P1250 种树](https://www.luogu.com.cn/problem/P1250)

### 个人心得
部分题解提到简单贪心算法存在缺陷，如在判断相邻怪物之间是否可以归零伤害时，不能只考虑当前两个怪物的情况，还需要考虑后续怪物的信息。这提示我们在解决问题时，要全面考虑各种情况，避免局部最优导致全局非最优。

---
处理用时：60.10秒