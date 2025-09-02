# 题目信息

# Valhalla Siege

## 题目描述

Ivar the Boneless is a great leader. He is trying to capture Kattegat from Lagertha. The war has begun and wave after wave Ivar's warriors are falling in battle.

Ivar has $ n $ warriors, he places them on a straight line in front of the main gate, in a way that the $ i $ -th warrior stands right after $ (i-1) $ -th warrior. The first warrior leads the attack.

Each attacker can take up to $ a_i $ arrows before he falls to the ground, where $ a_i $ is the $ i $ -th warrior's strength.

Lagertha orders her warriors to shoot $ k_i $ arrows during the $ i $ -th minute, the arrows one by one hit the first still standing warrior. After all Ivar's warriors fall and all the currently flying arrows fly by, Thor smashes his hammer and all Ivar's warriors get their previous strengths back and stand up to fight again. In other words, if all warriors die in minute $ t $ , they will all be standing to fight at the end of minute $ t $ .

The battle will last for $ q $ minutes, after each minute you should tell Ivar what is the number of his standing warriors.

## 说明/提示

In the first example:

- after the 1-st minute, the 1-st and 2-nd warriors die.
- after the 2-nd minute all warriors die (and all arrows left over are wasted), then they will be revived thus answer is 5 — all warriors are alive.
- after the 3-rd minute, the 1-st warrior dies.
- after the 4-th minute, the 2-nd warrior takes a hit and his strength decreases by 1.
- after the 5-th minute, the 2-nd warrior dies.

## 样例 #1

### 输入

```
5 5
1 2 1 2 1
3 10 1 1 1
```

### 输出

```
3
5
4
4
3
```

## 样例 #2

### 输入

```
4 4
1 2 3 4
9 1 10 6
```

### 输出

```
1
4
4
1
```

# AI分析结果

### 题目内容重写
# Valhalla Siege

## 题目描述

无骨伊瓦尔是一位伟大的领袖。他正试图从拉格塔手中夺取卡特加特。战争已经开始，一波接一波的伊瓦尔战士在战斗中倒下。

伊瓦尔有 $n$ 个战士，他把他们放在正门前的一条直线上，第 $i$ 个战士站在第 $i-1$ 个战士的后面。第一个战士带头进攻。

每个攻击者最多可以承受 $a_i$ 支箭，然后他会倒下，其中 $a_i$ 是第 $i$ 个战士的强度。

拉格塔命令她的战士在第 $i$ 分钟内射出 $k_i$ 支箭，箭一支接一支地射中第一个仍然站立的战士。在所有伊瓦尔的战士倒下并且所有正在飞行的箭飞过之后，托尔打碎了他的锤子，所有伊瓦尔的战士都会恢复之前的强度并重新站起来战斗。换句话说，如果所有战士在第 $t$ 分钟内死亡，他们将在第 $t$ 分钟结束时重新站起来战斗。

战斗将持续 $q$ 分钟，每分钟后你应该告诉伊瓦尔他还有多少战士仍然站立。

## 说明/提示

在第一个例子中：

- 在第 1 分钟后，第 1 和第 2 个战士倒下。
- 在第 2 分钟后，所有战士倒下（所有剩余的箭都被浪费了），然后他们会复活，因此答案是 5 —— 所有战士都活着。
- 在第 3 分钟后，第 1 个战士倒下。
- 在第 4 分钟后，第 2 个战士受到一次攻击，他的强度减少 1。
- 在第 5 分钟后，第 2 个战士倒下。

## 样例 #1

### 输入

```
5 5
1 2 1 2 1
3 10 1 1 1
```

### 输出

```
3
5
4
4
3
```

## 样例 #2

### 输入

```
4 4
1 2 3 4
9 1 10 6
```

### 输出

```
1
4
4
1
```

### 算法分类
二分、前缀和

### 题解分析与结论
本题的核心在于如何高效地处理大量战士和攻击次数的问题。由于战士的复活机制，每次攻击后需要快速计算仍然站立的战士数量。大多数题解都采用了前缀和与二分查找的方法来优化时间复杂度。

### 所选高分题解
1. **作者：superballll (5星)**
   - **关键亮点**：详细解释了二分查找的应用，如何处理伤害遗留问题，并提供了清晰的代码实现。
   - **代码核心思想**：使用前缀和数组存储战士的血量，通过二分查找确定每次攻击后仍然站立的战士数量，并处理战士复活的情况。
   - **核心代码片段**：
     ```cpp
     if(k>=b[n]-kk)  //全军覆没
     {
         kk=0,x=1; 
         cout<<n<<endl; 
         continue;
     } 
     if(k<b[x]-kk)  //不能破防 
     {
         kk+=k;
         cout<<n-x+1<<endl;
         continue;  
     }
     l=x,r=n;
     while(r-l>=1)
     {
         mid=(l+r)/2;
         if(k>=b[mid]-kk)  l=mid+1; //mid阵亡 
         else r=mid; // mid未阵亡 
     }
     x=l,kk+=k; 
     cout<<n-x+1<<endl;
     ```

2. **作者：__Watcher (4星)**
   - **关键亮点**：使用了STL的`upper_bound`函数进行二分查找，代码简洁且高效。
   - **代码核心思想**：通过前缀和数组和`upper_bound`函数快速定位每次攻击后仍然站立的战士数量。
   - **核心代码片段**：
     ```cpp
     p+=x;
     long long* r=upper_bound(a+1,a+n+1,p);//二分，注意返回类型
     if(r-a==n+1){//全倒了
         printf("%d\n", n);
         p=0;//前缀和重置
     }
     else printf("%d\n", n-(r-a-1));
     ```

3. **作者：xvl_ (4星)**
   - **关键亮点**：同样使用了`upper_bound`函数，代码简洁且易于理解。
   - **代码核心思想**：通过前缀和数组和`upper_bound`函数快速定位每次攻击后仍然站立的战士数量，并处理战士复活的情况。
   - **核心代码片段**：
     ```cpp
     d += x;
     ll loc = upper_bound(sum + 1, sum + n + 1, d) - sum; // 查找第一个血量大于伤害的武士的位置  
     loc--; // 死了多少个武士 
     if (loc >= n) { // 全死了的情况
         d = 0; // 伤害清零
         cout << n << "\n"; // 全部复活，所以有 n 个武士
     }
     else cout << n - loc << "\n"; // 剩余的武士
     ```

### 最优关键思路
1. **前缀和与二分查找**：通过前缀和数组快速计算战士的血量总和，结合二分查找高效定位每次攻击后仍然站立的战士数量。
2. **处理战士复活**：当所有战士倒下时，重置伤害计数和战士状态，模拟战士复活的过程。

### 可拓展之处
- **类似问题**：可以拓展到其他需要快速计算区间和并处理大量查询的问题，如区间最小值、区间最大值等。
- **算法套路**：前缀和与二分查找的结合在解决区间查询问题时非常有效，可以应用于多种场景。

### 推荐题目
1. [P3374 【模板】树状数组 1](https://www.luogu.com.cn/problem/P3374)
2. [P3368 【模板】树状数组 2](https://www.luogu.com.cn/problem/P3368)
3. [P3382 【模板】线段树 1](https://www.luogu.com.cn/problem/P3382)

### 个人心得
- **调试经历**：在处理战士复活时，需要特别注意伤害计数的重置，否则会导致计算结果错误。
- **顿悟感想**：前缀和与二分查找的结合在解决区间查询问题时非常高效，能够显著降低时间复杂度。

---
处理用时：39.81秒