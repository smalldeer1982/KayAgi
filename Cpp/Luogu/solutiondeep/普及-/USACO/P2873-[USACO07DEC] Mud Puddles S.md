# 题目信息

# [USACO07DEC] Mud Puddles S

## 题目描述

Farmer John is leaving his house promptly at 6 AM for his daily milking of Bessie. However, the previous evening saw a heavy rain, and the fields are quite muddy. FJ starts at the point (0, 0) in the coordinate plane and heads toward Bessie who is located at (X, Y) (-500 ≤ X ≤ 500; -500 ≤ Y ≤ 500). He can see all N (1 ≤ N ≤ 10,000) puddles of mud, located at points (Ai, Bi) (-500 ≤ Ai ≤ 500; -500 ≤ Bi ≤ 500) on the field. Each puddle occupies only the point it is on.

Having just bought new boots, Farmer John absolutely does not want to dirty them by stepping in a puddle, but he also wants to get to Bessie as quickly as possible. He's already late because he had to count all the puddles. If Farmer John can only travel parallel to the axes and turn at points with integer coordinates, what is the shortest distance he must travel to reach Bessie and keep his boots clean? There will always be a path without mud that Farmer John can take to reach Bessie.

## 样例 #1

### 输入

```
1 2 7
0 2
-1 3
3 1
1 1
4 2
-1 1
2 2```

### 输出

```
11```

# AI分析结果



### 综合分析与结论
各题解均采用BFS解决最短路径问题，核心思路为坐标偏移处理负数范围（+500转非负坐标），通过队列实现层序遍历。关键差异点在于队列实现方式（STL/手写）、访问标记策略（复用泥坑数组/独立vis数组）及剪枝优化。最优解法应具备清晰的坐标偏移处理、即时终止条件和高效的状态标记。

---

### 高星题解推荐

#### 1. Steinway（★★★★☆）
**关键亮点**  
- 代码规范简洁，使用STL队列与方向数组  
- 终点判断内联在方向循环中，直接返回确保最短路径  
- 边界检查函数`legal`提升可读性  
**核心代码**  
```cpp
while(!q.empty()) {
    Node x = q.front(); q.pop();
    for(int i=0; i<4; i++) {
        int nx = x.x + dx[i], ny = x.y + dy[i];
        if(nx == ex+500 && ny == ey+500) { 
            printf("%d\n",x.sum+1); 
            return 0; 
        }
        if(legal(nx,ny) && Map[nx][ny]==0) {
            Map[nx][ny] = 1;
            q.push({nx,ny,x.sum+1});
        }
    }
}
```

#### 2. Leaved_（★★★★☆）
**关键亮点**  
- 强调BFS首次到达即最优解的性质  
- 手写队列减少STL开销，适合大范围数据  
- 独立vis数组避免状态冲突  
**核心代码**  
```cpp
void Bfs() {
    while(head<=tail) {
        int now_x=que[head][0], now_y=que[head][1], sum=que[head][2];
        head++;
        for(i=0; i<4; i++) {
            int tx=now_x+go[i][0], ty=now_y+go[i][1];
            if(tx==endx && ty==endy) {
                p(sum+1); return;
            }
            if(can_bfs(tx,ty) && !map_t[tx][ty] && !vis[tx][ty]) {
                que[++tail][0]=tx; 
                que[tail][1]=ty; 
                que[tail][2]=sum+1;
                vis[tx][ty]=1;
            }
        }
    }
}
```

#### 3. 啃丁狗（★★★★☆）
**关键亮点**  
- 结构体队列与方向增量分离，逻辑清晰  
- 泥坑数组与访问标记分离，增强可维护性  
- 显式坐标偏移注释强调关键步骤  
**代码片段**  
```cpp
q.push({500,500,0});
while(front<=rear) {
    node f=q[front++];
    for(int i=0; i<4; i++) {
        int nx=f.x+dx[i], ny=f.y+dy[i];
        if(nx==ex+500 && ny==ey+500) { 
            printf("%d",f.step+1); 
            return 0; 
        }
        if(!mud[nx][ny] && !vis[nx][ny]) {
            q[++rear] = {nx, ny, f.step+1};
            vis[nx][ny] = true;
        }
    }
}
```

---

### 最优思路提炼
1. **坐标偏移法**：将坐标+500转为非负值，避免负数下标问题（核心技巧）。  
2. **即时终止**：在方向扩展时立即判断终点，直接返回步数+1。  
3. **状态复用**：利用原泥坑数组或独立vis数组标记访问状态，减少内存开销。  

---

### 拓展与同类题推荐
**同类题目**  
1. [P1443 马的遍历](https://www.luogu.com.cn/problem/P1443)  
2. [P1135 奇怪的电梯](https://www.luogu.com.cn/problem/P1135)  
3. [P1141 01迷宫](https://www.luogu.com.cn/problem/P1141)  

**调试心得摘录**  
- **Horizon20182201**：初始坐标未加500导致WA，强调偏移重要性。  
- **hensier**：对比map与数组效率，指出竞赛中优先数组偏移。  
- **Leaved_**：手写队列避免STL常数问题，适合大规模数据场景。

---
处理用时：55.67秒