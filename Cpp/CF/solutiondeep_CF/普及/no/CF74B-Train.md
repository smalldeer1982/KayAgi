# 题目信息

# Train

## 题目描述

A stowaway and a controller play the following game.

The train is represented by $ n $ wagons which are numbered with positive integers from $ 1 $ to $ n $ from the head to the tail. The stowaway and the controller are initially in some two different wagons. Every minute the train can be in one of two conditions — moving or idle. Every minute the players move.

The controller's move is as follows. The controller has the movement direction — to the train's head or to its tail. During a move the controller moves to the neighbouring wagon correspondingly to its movement direction. If at the end of his move the controller enters the $ 1 $ -st or the $ n $ -th wagon, that he changes the direction of his movement into the other one. In other words, the controller cyclically goes from the train's head to its tail and back again during all the time of a game, shifting during each move by one wagon. Note, that the controller always have exactly one possible move.

The stowaway's move depends from the state of the train. If the train is moving, then the stowaway can shift to one of neighbouring wagons or he can stay where he is without moving. If the train is at a station and is idle, then the stowaway leaves the train (i.e. he is now not present in any train wagon) and then, if it is not the terminal train station, he enters the train again into any of $ n $ wagons (not necessarily into the one he's just left and not necessarily into the neighbouring one). If the train is idle for several minutes then each such minute the stowaway leaves the train and enters it back.

Let's determine the order of the players' moves. If at the given minute the train is moving, then first the stowaway moves and then the controller does. If at this minute the train is idle, then first the stowaway leaves the train, then the controller moves and then the stowaway enters the train.

If at some point in time the stowaway and the controller happen to be in one wagon, then the controller wins: he makes the stowaway pay fine. If after a while the stowaway reaches the terminal train station, then the stowaway wins: he simply leaves the station during his move and never returns there again.

At any moment of time the players know each other's positions. The players play in the optimal way. Specifically, if the controller wins, then the stowaway plays so as to lose as late as possible. As all the possible moves for the controller are determined uniquely, then he is considered to play optimally always. Determine the winner.

## 样例 #1

### 输入

```
5 3 2
to head
0001001
```

### 输出

```
Stowaway```

## 样例 #2

### 输入

```
3 2 1
to tail
0001
```

### 输出

```
Controller 2```

# AI分析结果



# 题目中文翻译

## 题目描述

偷渡者和列车管理员进行如下游戏。

火车由 $n$ 节车厢组成，从车头到车尾编号为 $1$ 到 $n$。两人初始位于不同车厢。每分钟火车处于移动或停靠状态，玩家按如下规则移动：

**管理员移动规则**：
- 有固定移动方向（朝车头或车尾）
- 每分钟向方向移动一节车厢
- 当到达车头（1号）或车尾（n号）时立即调转方向

**偷渡者移动规则**：
- 火车运行时：可移动至相邻车厢或留在原地
- 火车停靠时：必须离开并重新进入任意车厢（终点站除外）
- 停靠多分钟时：每分钟都要重复此过程

**胜负判定**：
- 两人同处一节车厢时管理员立即胜出
- 偷渡者到达终点站后胜出

**行动顺序**：
- 火车运行时：偷渡者先动，管理员后动
- 火车停靠时：偷渡者下车→管理员移动→偷渡者重新上车

# 算法分类
模拟

# 题解综合分析

各题解均采用模拟法，核心难点在于：
1. 管理员转向逻辑的处理
2. 偷渡者最优策略的选择
3. 不同状态下移动顺序的模拟

关键优化点：偷渡者在运行时应始终朝管理员的反方向移动，停靠时应直接跳跃到端点位置。管理员到达端点时立即改变方向。

# 精选题解

## 1. 作者：linan04195（★★★★☆）
**关键亮点**：
- 清晰区分运行与停靠状态的处理
- 使用简洁的条件判断实现最优策略
- 通过方向标记 `pos` 简化管理员移动逻辑

**核心代码**：
```cpp
for(int i=0;i<len;i++){ // 遍历列车状态
    if(tmp==t){ // 两人相遇判定
        printf("Controller %d",ans);
        return 0;
    }
    ans++;
    
    if(str[i]=='1'){ // 停靠状态处理
        if(pos!=-1) tmp=1; // 管理员朝车尾则偷渡者去车头
        else tmp=n;         // 管理员朝车头则去车尾
    }
    else{ // 运行状态处理
        if(tmp<t) tmp=max(1,tmp-1); // 向车头移动
        if(tmp>t) tmp=min(n,tmp+1); // 向车尾移动
    }
    
    t+=pos; // 管理员移动
    if(t==1) pos=1;  // 车头转向
    if(t==n) pos=-1; // 车尾转向
}
```

## 2. 作者：keep_shining（★★★★☆）
**关键亮点**：
- 使用字符流处理简化输入
- 通过 max/min 函数处理边界值
- 统一处理终点相遇情况

**个人心得**：
> "注意没有比1号更小的车厢，所以需要在一号和当前位置的前一个车厢中取最大值"

**核心逻辑**：
```cpp
for(int i=0;i<s.size();i++) {
    if(m==k) { // 相遇检查
        cout<<"Controller "<<cnt;
        return 0;
    }
    cnt++;
    
    if(s[i]=='0') { // 运行状态
        if(m<k) m=max(1,m-1); // 向车头
        if(m>k) m=min(n,m+1); // 向车尾
    }
    else { // 停靠状态
        m = (dir ? 1 : n); // 跳跃到端点
    }
    
    k += dir; // 管理员移动
    if(k==1) dir=1;  // 转向处理
    if(k==n) dir=-1;
}
```

# 最优思路总结
1. **方向标记法**：用 ±1 表示管理员方向，简化转向逻辑
2. **端点跳跃策略**：停靠时直接让偷渡者占据远端车厢
3. **边界处理**：使用 max(1, x)/min(n, x) 确保位置合法
4. **状态分离**：独立处理运行与停靠两种状态

# 拓展思考
类似移动策略问题可考虑：
1. 双向移动中的最优路径选择
2. 周期性移动模式的数学建模
3. 对抗性博弈中的最优策略模拟

# 推荐练习题
1. [P1563 玩具谜题](https://www.luogu.com.cn/problem/P1563) - 方向标记与环形移动
2. [P1067 多项式输出](https://www.luogu.com.cn/problem/P1067) - 状态转移与边界处理
3. [P1036 选数](https://www.luogu.com.cn/problem/P1036) - 组合移动的模拟优化

---
处理用时：61.93秒