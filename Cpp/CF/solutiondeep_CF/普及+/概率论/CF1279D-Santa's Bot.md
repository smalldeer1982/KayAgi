# 题目信息

# Santa's Bot

## 题目描述

Santa Claus has received letters from $ n $ different kids throughout this year. Of course, each kid wants to get some presents from Santa: in particular, the $ i $ -th kid asked Santa to give them one of $ k_i $ different items as a present. Some items could have been asked by multiple kids.

Santa is really busy, so he wants the New Year Bot to choose the presents for all children. Unfortunately, the Bot's algorithm of choosing presents is bugged. To choose a present for some kid, the Bot does the following:

- choose one kid $ x $ equiprobably among all $ n $ kids;
- choose some item $ y $ equiprobably among all $ k_x $ items kid $ x $ wants;
- choose a kid $ z $ who will receive the present equipropably among all $ n $ kids (this choice is independent of choosing $ x $ and $ y $ ); the resulting triple $ (x, y, z) $ is called the decision of the Bot.

If kid $ z $ listed item $ y $ as an item they want to receive, then the decision valid. Otherwise, the Bot's choice is invalid.

Santa is aware of the bug, but he can't estimate if this bug is really severe. To do so, he wants to know the probability that one decision generated according to the aforementioned algorithm is valid. Can you help him?

## 样例 #1

### 输入

```
2
2 2 1
1 1
```

### 输出

```
124780545
```

## 样例 #2

### 输入

```
5
2 1 2
2 3 1
3 2 4 3
2 1 4
3 4 3 2
```

### 输出

```
798595483
```

# AI分析结果

### 题目中文重写
# 圣诞老人的机器人

## 题目描述
圣诞老人在这一年里收到了 $n$ 个不同孩子的来信。当然，每个孩子都希望从圣诞老人那里得到一些礼物：特别是，第 $i$ 个孩子要求圣诞老人从 $k_i$ 个不同的物品中选一个作为礼物。有些物品可能被多个孩子索要。

圣诞老人非常忙碌，所以他想让新年机器人为所有孩子选择礼物。不幸的是，机器人选择礼物的算法有漏洞。为了给某个孩子选择礼物，机器人会进行以下操作：
- 从所有 $n$ 个孩子中随机等概率地选择一个孩子 $x$；
- 从孩子 $x$ 想要的所有 $k_x$ 个物品中随机等概率地选择一个物品 $y$；
- 从所有 $n$ 个孩子中随机等概率地选择一个孩子 $z$（这个选择与选择 $x$ 和 $y$ 无关）；得到的三元组 $(x, y, z)$ 被称为机器人的决策。

如果孩子 $z$ 将物品 $y$ 列为他们想要收到的物品之一，那么这个决策是有效的。否则，机器人的选择是无效的。

圣诞老人意识到了这个漏洞，但他无法估计这个漏洞是否真的很严重。为了做到这一点，他想知道根据上述算法生成的一个决策有效的概率。你能帮助他吗？

## 样例 #1
### 输入
```
2
2 2 1
1 1
```
### 输出
```
124780545
```

## 样例 #2
### 输入
```
5
2 1 2
2 3 1
3 2 4 3
2 1 4
3 4 3 2
```
### 输出
```
798595483
```

### 综合分析与结论
这些题解核心思路一致，都是先分析出每个选择步骤的概率，再根据概率的乘法原理和加法原理得到最终答案的表达式。不同题解在概率公式的推导形式、逆元的求解方法以及代码实现细节上存在差异。

### 所选的题解
- **Computer1828（5星）**
    - **关键亮点**：思路清晰，公式推导详细，代码简洁高效，使用快速幂求逆元。
    - **重点代码**：
```cpp
for(int i = 1;i<=n;++i){
    ll res = 0;
    for(int j = 0;j<si[i];++j) res = (res+sum[s[i][j]]*inv(n)%mod)%mod;
    ans = (ans+res*inv(si[i])%mod)%mod;
}
printf("%lld",ans*qpow(n,mod-2,mod)%mod);
```
    - **核心实现思想**：先统计每个物品出现的次数 `sum`，然后遍历每个孩子的物品列表，计算每个孩子对应的概率和，最后累加得到总概率，再除以 $n$ 并取模。

- **codeLJH114514（4星）**
    - **关键亮点**：思路严谨，对公式的推导和时间复杂度的分析详细，给出了代码实现的坑点提示。
    - **重点代码**：
```cpp
for (int i = 1; i <= n; i++) {
    for (auto j : sets[i]) {
        answer += appeared_sets[j] * power(n, mod - 2) % mod * power(n, mod - 2) % mod * power(sets[i].size(), mod - 2) % mod;
        answer %= mod;
    }
}
```
    - **核心实现思想**：先统计每个元素出现的集合数 `appeared_sets`，然后遍历每个集合中的元素，根据概率公式计算每个元素对答案的贡献并累加，最后取模。

- **IKUN314（4星）**
    - **关键亮点**：使用扩展欧几里得算法求逆元，对数据范围和代码实现的注意事项有详细说明。
    - **重点代码**：
```cpp
for(i=1;i<=n;i++){
    ll sum=0;
    for(auto j:a[i]){
        x=0;
        y=0;
        exgcd(n*n*k[i],mod);
        x=(x%mod+mod)%mod;
        (sum+=cnt[j]*x%mod)%=mod;
    }
    (ans+=sum%mod)%=mod;
}
```
    - **核心实现思想**：先统计每个元素出现的集合数 `cnt`，然后遍历每个集合中的元素，使用扩展欧几里得算法求逆元，计算每个集合对应的概率和，最后累加得到总概率并取模。

### 最优关键思路或技巧
- 概率分析：将复杂的概率问题拆分成多个简单步骤的概率，再根据概率的乘法原理和加法原理得到最终答案。
- 逆元求解：使用快速幂或扩展欧几里得算法求逆元，处理模运算下的除法。
- 数据存储：使用 `vector` 存储每个孩子想要的物品集合，避免数组空间的浪费。

### 可拓展之处
同类型题可能会改变选择步骤的条件或增加更多的选择步骤，解题思路仍然是分析每个步骤的概率，再进行组合计算。类似算法套路可用于解决其他概率相关的问题，如抽奖、随机事件等。

### 推荐洛谷题目
- P1593 因子和
- P2613 【模板】有理数取余
- P3811 【模板】乘法逆元

### 个人心得摘录与总结
- **codeLJH114514**：
    - **摘录**：本题每一个 $(x,y,z)$ 的出现概率都不一样，因为 $k_x$ 不同。本题在实现的时候千万不要写 `power(n*n, mod - 2)` 这样的东西，因为 $n\times n$ 最高可达 $10^{12}$ 所以可能爆 `long long`，否则会 `WA on #37`。勤取模。
    - **总结**：在处理概率问题时要注意每个事件的概率可能不同，在代码实现中要注意数据范围，避免溢出，同时要及时取模防止结果错误。 

---
处理用时：34.05秒