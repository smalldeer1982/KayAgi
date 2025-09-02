# 题目信息

# Slava and tanks

## 题目描述

Slava plays his favorite game "Peace Lightning". Now he is flying a bomber on a very specific map.

Formally, map is a checkered field of size $ 1×n $ , the cells of which are numbered from $ 1 $ to $ n $ , in each cell there can be one or several tanks. Slava doesn't know the number of tanks and their positions, because he flies very high, but he can drop a bomb in any cell. All tanks in this cell will be damaged.

If a tank takes damage for the first time, it instantly moves to one of the neighboring cells (a tank in the cell $ n $ can only move to the cell $ n-1 $ , a tank in the cell $ 1 $ can only move to the cell $ 2 $ ). If a tank takes damage for the second time, it's counted as destroyed and never moves again. The tanks move only when they are damaged for the first time, they do not move by themselves.

Help Slava to destroy all tanks using as few bombs as possible.

## 样例 #1

### 输入

```
2
```

### 输出

```
3
2 1 2 ```

## 样例 #2

### 输入

```
3
```

### 输出

```
4
2 1 3 2 ```

# AI分析结果



### 题目重写
# Slava and tanks

## 题目描述

Slava 正在玩他最喜欢的游戏"和平闪电"。现在他驾驶轰炸机在一个特殊地图上空飞行。

该地图是一个 $1×n$ 的网格，格子编号从 $1$ 到 $n$，每个格子可能有若干坦克。Slava 可以在任意格子投掷炸弹，该格子的所有坦克会受到伤害：

- 若坦克第一次受伤，会立即移动到相邻格子（1号格只能右移，n号格只能左移）
- 若坦克第二次受伤，则被彻底摧毁

请帮助 Slava 用最少炸弹摧毁所有坦克。

## 样例 #1

### 输入
```
2
```

### 输出
```
3
2 1 2
```

## 样例 #2

### 输入
```
3
```

### 输出
```
4
2 1 3 2
```

### 算法分类
构造

---

### 题解分析与结论
所有题解均基于**奇偶性覆盖**思想，通过三次轰炸确保每个坦克被命中两次。核心思路为：
1. 首轮轰炸偶数格 → 所有目标进入奇数格
2. 次轮轰炸奇数格 → 原偶数格目标被摧毁，原奇数格目标进入偶数格
3. 末轮轰炸偶数格 → 剩余目标被摧毁

该方案总炸弹数为 $\lfloor n/2 \rfloor + n$，已被数学证明为最优解。

---

### 精选题解
#### 1. Wsy_flying_forever（5星）
**亮点**：详细推导奇偶性逻辑，阐明三次轰炸的必然性  
**代码核心**：
```cpp
for(int i=2;i<=n;i+=2) cout<<i<<" ";  // 炸偶数
for(int i=1;i<=n;i+=2) cout<<i<<" ";  // 炸奇数
for(int i=2;i<=n;i+=2) cout<<i<<" ";  // 再炸偶数
```
**心路总结**：通过对称性分析证明三次操作的充分性，避免"显然成立"式断言

#### 2. BYWYR（4星）
**亮点**：最简代码实现，直击问题本质  
**代码核心**：
```cpp
cout<<n+n/2<<endl;  // 计算总炸弹数
// 三段式循环输出轰炸序列
```

#### 3. ___wa___（4星）
**亮点**：图示辅助理解移动过程  
**关键图示**：
```
初始：E(ven) O(dd)
炸E后：O+E的坦克
炸O后：E的坦克被摧毁，O→E
炸E后：所有残留清除
```

---

### 核心代码实现
```cpp
int main() {
    int n; cin >> n;
    cout << n + n/2 << endl;
    // 生成轰炸序列
    auto bomb = [](int start, int step) {
        for(int i=start; i<=n; i+=step) cout << i << " ";
    };
    bomb(2,2); bomb(1,2); bomb(2,2);  // 偶→奇→偶
}
```

---

### 拓展应用
此类构造问题常用技巧：
1. 状态转换跟踪（如奇偶交替）
2. 覆盖周期分析（本例的三次操作周期）
3. 对称性利用

推荐练习：
1. [P1007 独木桥](https://www.luogu.com.cn/problem/P1007) - 碰撞状态转换
2. [CF1118A Water Buying](https://codeforces.com/problemset/problem/1118/A) - 奇偶优化购买策略
3. [P1515 旅行家的预算](https://www.luogu.com.cn/problem/P1515) - 贪心覆盖加油站

---
处理用时：58.04秒