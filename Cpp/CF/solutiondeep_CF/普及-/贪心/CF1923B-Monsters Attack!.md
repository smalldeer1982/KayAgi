# 题目信息

# Monsters Attack!

## 题目描述

You are playing a computer game. The current level of this game can be modeled as a straight line. Your character is in point $ 0 $ of this line. There are $ n $ monsters trying to kill your character; the $ i $ -th monster has health equal to $ a_i $ and is initially in the point $ x_i $ .

Every second, the following happens:

- first, you fire up to $ k $ bullets at monsters. Each bullet targets exactly one monster and decreases its health by $ 1 $ . For each bullet, you choose its target arbitrary (for example, you can fire all bullets at one monster, fire all bullets at different monsters, or choose any other combination). Any monster can be targeted by a bullet, regardless of its position and any other factors;
- then, all alive monsters with health $ 0 $ or less die;
- then, all alive monsters move $ 1 $ point closer to you (monsters to the left of you increase their coordinates by $ 1 $ , monsters to the right of you decrease their coordinates by $ 1 $ ). If any monster reaches your character (moves to the point $ 0 $ ), you lose.

Can you survive and kill all $ n $ monsters without letting any of them reach your character?

## 说明/提示

In the first example, you can act as follows:

- during the $ 1 $ -st second, fire $ 1 $ bullet at the $ 1 $ -st monster and $ 1 $ bullet at the $ 3 $ -rd monster. Then the $ 1 $ -st monster dies, the $ 2 $ -nd and the $ 3 $ -rd monster move closer;
- during the $ 2 $ -nd second, fire $ 2 $ bullets at the $ 2 $ -nd monster. Then the $ 2 $ -nd monster dies, the $ 3 $ -rd monster moves closer;
- during the $ 3 $ -rd second, fire $ 2 $ bullets at the $ 3 $ -rd monster. Then the $ 3 $ -rd monster dies.

In the second example, you can fire only $ 1 $ bullet, so you can kill only one of the two monsters during the $ 1 $ -st second. Then, the remaining monster moves closer and kills your character.

## 样例 #1

### 输入

```
5
3 2
1 2 3
-1 2 3
2 1
1 1
-1 1
4 10
3 4 2 5
-3 -2 1 3
5 3
2 1 3 2 5
-3 -2 3 4 5
2 1
1 2
1 2```

### 输出

```
YES
NO
YES
YES
NO```

# AI分析结果



# Monsters Attack! 怪物攻击！

## 题目描述

你正在玩一个电脑游戏。当前关卡可以建模为一条直线。你的角色位于这条直线的 $0$ 点。有 $n$ 个怪物试图杀死你的角色；第 $i$ 个怪物有 $a_i$ 点生命值，初始位于 $x_i$ 点。

每秒发生以下事件：
1. 首先，你向怪物发射最多 $k$ 颗子弹。每颗子弹精确命中一个怪物，使其生命值减少 $1$。你可以任意选择子弹的目标（例如所有子弹打一个怪物，或分散攻击等）；
2. 所有生命值 $0$ 或更低的存活怪物死亡；
3. 所有存活怪物向你移动 $1$ 点距离（左侧怪物坐标 $+1$，右侧怪物坐标 $-1$）。若有怪物移动到 $0$ 点，你失败。

问是否能存活并消灭所有怪物。

---

## 题解综合分析

### 算法核心
所有题解均采用**贪心策略**：按怪物距离绝对值排序，优先处理最近怪物。关键点：
1. **坐标转换**：将 $x_i$ 取绝对值，转化为单侧处理
2. **时间约束**：距离为 $d$ 的怪物必须在 $d$ 秒内消灭
3. **子弹累计**：维护累计可用子弹数，逐秒检查是否足够消灭当前距离的怪物

### 最优思路提炼
1. **桶计数法**：使用数组统计每个距离的总血量
2. **线性验证**：遍历距离 $1$ 到 $n$，累计子弹数并验证：
   ```
   总子弹数 += k
   if (总子弹数 < 当前距离总血量) 则失败
   总子弹数 -= 当前距离总血量
   ```

---

## 精选题解（评分≥4★）

### 题解1：2huk（5★）
**亮点**：
- 完整的问题建模，清晰解释时间约束关系
- 引入"剩余子弹传递"思想，代码简洁高效
- 使用 vector 存储，避免数组越界问题

**核心代码**：
```cpp
vector<PII> V; // 存储(距离, 血量)
sort(all(V));  // 按距离排序
int last=0, cnt=0;
for(auto it:V){
    if(it.fi!=last) cnt += (it.fi-last)*k; // 计算时间差对应的子弹
    last = it.fi;
    if(it.se > cnt) return false;
    cnt -= it.se;
}
```

### 题解2：N_zzz（4★）
**亮点**：
- 前缀和优化，将时间复杂度降至 O(n)
- 使用 sm[i] 记录距离 ≤i 的总血量，直接比较 i*k

**关键实现**：
```cpp
for(int i=1;i<=n;i++) sm[i] += sm[i-1]; // 前缀和
for(int i=1;i<=n;i++)
    if(i*k < sm[i]) return false; // 直接比较累计值
```

### 题解3：Hacker_Cracker（4★）
**亮点**：
- 最早提出桶计数法的实现方案
- 处理大数据范围时正确使用 long long

**代码片段**：
```cpp
for(int i=1;i<=n;i++){
    p[i] = abs(x);
    t[p[i]] += a[i]; // 桶计数
}
for(int i=1;i<=n;i++){
    sum += k - t[i]; // 累计可用子弹
    if(sum < 0) return false;
}
```

---

## 关键技巧总结
1. **绝对值转换**：将坐标问题转化为单侧处理，简化逻辑
2. **时间窗口计算**：距离 d 对应 d 秒的击杀时间窗口
3. **子弹累计机制**：允许将未用完的子弹转移到后续距离使用
4. **大数据处理**：必须使用 long long 避免溢出

---

## 相似题目推荐
1. [P1908 逆序对](https://www.luogu.com.cn/problem/P1908) - 同样需要处理线性序列的时序问题
2. [P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094) - 贪心策略与双指针结合
3. [CF1029C Maximal Intersection](https://codeforces.com/problemset/problem/1029/C) - 区间覆盖与极值处理的贪心思想

---

## 调试经验摘录
1. **不开 long long 见祖宗**：多个题解强调必须使用 long long 存储累加值
2. **坐标去重处理**：需合并相同距离的怪物血量，否则会错误计算时间窗口
3. **边界条件**：怪物距离为 1 时必须在第 1 秒消灭，不能拖延到后续处理

---
处理用时：49.74秒