# 题目信息

# VIDEO - Video game combos

## 题目描述

 Bessie is playing a video game! In the game, the three letters 'A', 'B', and 'C' are the only valid buttons. Bessie may press the buttons in any order she likes. However, there are only N distinct combos possible (1 <= N <= 20). Combo i is represented as a string S\_i which has a length between 1 and 15 and contains only the letters 'A', 'B', and 'C'.

 Whenever Bessie presses a combination of letters that matches with a combo, she gets one point for the combo. Combos may overlap with each other or even finish at the same time! For example if N = 3 and the three possible combos are "ABA", "CB", and "ABACB", and Bessie presses "ABACB", she will end with 3 points. Bessie may score points for a single combo more than once.

 Bessie of course wants to earn points as quickly as possible. If she presses exactly K buttons (1 <= K <= 1,000), what is the maximum number of points she can earn?

## 样例 #1

### 输入

```
3 7
ABA
CB
ABACB```

### 输出

```
4```

# AI分析结果



## 算法分类
AC自动机+动态规划

## 题解思路与核心难点

### 算法要点
1. **AC自动机构建**：将所有模式串插入Trie树，构建fail指针形成自动机
2. **得分预处理**：每个节点保存从根到该节点路径上的所有匹配得分（包含fail链上的得分）
3. **动态规划**：
   - 状态定义：dp[i][j]表示按i次按钮后处于自动机节点j时的最高得分
   - 状态转移：枚举下一个按键(A/B/C)，转移到对应的子节点并累加得分

### 解决难点
1. **重叠匹配处理**：通过fail指针继承父节点的得分，避免重复计算
```cpp
// 在构建fail指针时累加得分
void build() {
    queue<int> q;
    for(int i=0; i<3; i++)
        if(tr[0][i]) q.push(tr[0][i]);
    while(!q.empty()) {
        int u = q.front(); q.pop();
        for(int i=0; i<3; i++) {
            int v = tr[u][i];
            if(v) {
                fail[v] = tr[fail[u]][i];
                cnt[v] += cnt[fail[v]]; // 关键得分累加
                q.push(v);
            } else {
                tr[u][i] = tr[fail[u]][i];
            }
        }
    }
}
```
2. **状态初始化**：必须将初始状态设为根节点，避免非法转移
```cpp
memset(dp, 0x80, sizeof(dp)); // 初始化为极小值
dp[0][0] = 0; // 仅根节点合法
```

## 最优思路提炼
1. **AC自动机预处理**：通过fail指针继承父节点得分，实现O(1)时间得分查询
2. **滚动数组优化**：使用i&1的位运算压缩空间到O(2*M)
```cpp
for(int i=1; i<=k; i++) {
    memset(f[i&1], 0x80, sizeof(f[i&1])); // 滚动数组
    for(int j=0; j<=tot; j++) 
        for(int c=0; c<3; c++)
            f[i&1][tr[j][c]] = max(f[i&1][tr[j][c]], f[(i-1)&1][j] + cnt[tr[j][c]]);
}
```

## 题解评分（≥4星）
1. **D_14134（★★★★☆）**：代码结构清晰，完整展示AC自动机与DP的结合，初始化处理正确
2. **ez_lcw（★★★★☆）**：使用结构体封装自动机节点，转移方程简洁易懂
3. **Engulf（★★★★★）**：代码最简练，状态转移使用位运算优化空间效率

## 同类型题目推荐
1. [P3041 [USACO12JAN] Video Game G](https://www.luogu.com.cn/problem/P3041)（双倍经验）
2. [P4052 [JSOI2007] 文本生成器](https://www.luogu.com.cn/problem/P4052)
3. [P2292 [HNOI2004] L语言](https://www.luogu.com.cn/problem/P2292)

## 可视化设计
**8位像素风格演示**：
1. **节点结构**：Trie节点显示为彩色方块，fail指针用箭头连接
2. **状态转移**：当前DP状态用闪烁光标标记，得分变化时播放"叮"音效
3. **自动运行模式**：
   - 按空格键逐步执行转移步骤
   - 按A键自动播放完整算法流程
   - 屏幕下方显示当前按键序列和累计得分

**核心动画逻辑**：
```javascript
// Canvas绘制示例
function drawNode(x, y, score) {
    ctx.fillStyle = '#FF69B4'; // 粉红节点
    ctx.fillRect(x*50, y*50, 40, 40);
    ctx.fillStyle = '#000';
    ctx.fillText(score, x*50+20, y*50+20);
}

// 转移动画示例
function animateStep(step, nodeFrom, nodeTo) {
    let x1 = nodeFrom.x*50 + 20, y1 = nodeFrom.y*50 + 20;
    let x2 = nodeTo.x*50 + 20, y2 = nodeTo.y*50 + 20;
    // 绘制光球移动动画
    drawGlowBall(x1, y1, x2, y2); 
    playSound('move'); // 播放移动音效
}
```

## 个人调试心得
1. **初始状态陷阱**：未初始化非根节点为-INF会导致错误答案，例如样例中误将未到达节点计入得分
2. **滚动数组优化**：需要及时清空旧状态，否则会残留前一轮数据
3. **fail指针构建顺序**：必须按BFS层级处理，否则节点得分无法正确继承

---

## 完整代码示例（D_14134题解核心部分）
```cpp
#include<iostream>
#include<queue>
#include<cstring>
using namespace std;

const int N=310, K=1010;
int tr[N][3], fail[N], cnt[N], dp[K][N], idx;

void insert(char *s) {
    int p = 0;
    for(int i=0; s[i]; i++) {
        int c = s[i]-'A';
        if(!tr[p][c]) tr[p][c] = ++idx;
        p = tr[p][c];
    }
    cnt[p]++;
}

void build() {
    queue<int> q;
    for(int i=0; i<3; i++)
        if(tr[0][i]) q.push(tr[0][i]);
    
    while(!q.empty()) {
        int u = q.front(); q.pop();
        for(int i=0; i<3; i++) {
            int &v = tr[u][i];
            if(v) {
                fail[v] = tr[fail[u]][i];
                cnt[v] += cnt[fail[v]];
                q.push(v);
            } else {
                v = tr[fail[u]][i];
            }
        }
    }
}

int main() {
    int n, k; 
    cin >> n >> k;
    for(int i=1; i<=n; i++) {
        char s[20]; cin >> s;
        insert(s);
    }
    build();
    
    memset(dp, 0x80, sizeof(dp));
    dp[0][0] = 0;
    
    for(int i=0; i<k; i++)
        for(int j=0; j<=idx; j++)
            for(int c=0; c<3; c++) {
                int v = tr[j][c];
                dp[i+1][v] = max(dp[i+1][v], dp[i][j] + cnt[v]);
            }
    
    int ans = 0;
    for(int i=0; i<=idx; i++)
        ans = max(ans, dp[k][i]);
    cout << ans;
}
```

---
处理用时：87.04秒