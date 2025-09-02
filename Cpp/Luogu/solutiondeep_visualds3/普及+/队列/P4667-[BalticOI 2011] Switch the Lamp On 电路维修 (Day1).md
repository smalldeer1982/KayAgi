# 题目信息

# [BalticOI 2011] Switch the Lamp On 电路维修 (Day1)

## 题目描述

Casper 正在设计电路。有一种正方形的电路元件，在它的两组相对顶点中，有一组会用导线连接起来，另一组则不会。有 $N\times M$ 个这样的元件，你想将其排列成 $N$ 行，每行 $M$ 个。 电源连接到板的左上角。灯连接到板的右下角。只有在电源和灯之间有一条电线连接的情况下，灯才会亮着。为了打开灯，任何数量的电路元件都可以转动 90°（两个方向）。

![](https://cdn.luogu.com.cn/upload/pic/1286.png)

![](https://cdn.luogu.com.cn/upload/pic/1285.png)

在上面的图片中，灯是关着的。如果右边的第二列的任何一个电路元件被旋转 90°，电源和灯都会连接，灯被打开。现在请你编写一个程序，求出最小需要多少旋转多少电路元件。

## 样例 #1

### 输入

```
3 5
\\/\\
\\///
/\\\\```

### 输出

```
1```

# AI分析结果

要解决**电路维修**问题（求从左上角到右下角的最少旋转次数），核心思路是将问题转化为**边权为0-1的最短路问题**，并通过**双端队列BFS（0-1 BFS）**高效求解。以下是对题解的关键分析和总结：


### **一、问题建模**
将电路板的**格点（交叉点）**视为图的节点，**每个格子的斜线**视为连接两个对角节点的边：
- 若斜线方向与当前格子的斜线一致（不需要旋转），边权为**0**；
- 若斜线方向与当前格子的斜线不一致（需要旋转），边权为**1**。

例如，格子(i,j)的斜线为`\`时，连接节点(i,j)和(i+1,j+1)的边权为0，连接节点(i+1,j)和(i,j+1)的边权为1；若斜线为`/`，则相反。


### **二、核心算法：双端队列BFS（0-1 BFS）**
由于边权只有0和1，双端队列BFS是最优选择。其核心思想是：
- **边权为0**的节点**入队头**（优先处理，保证最短路径）；
- **边权为1**的节点**入队尾**（后续处理）。

这种方法保证了队列的**单调性**（队列中节点的距离是非递减的），因此**第一次访问到终点时，距离即为最短路径**。


### **三、关键实现步骤**
#### 1. 节点编号
将二维格点(i,j)转换为一维编号，方便存储和处理。例如：
```cpp
int point(int i, int j) { return i * (m + 1) + j; } // (m+1)是每行的格点数
```
其中，`i`和`j`是格点的坐标（从0开始），`m`是列数。


#### 2. 建边
遍历每个格子，根据斜线方向建立边：
```cpp
for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
        char ch;
        cin >> ch;
        if (ch == '\\') {
            // 连接(i,j)和(i+1,j+1)，边权0
            add_edge(point(i,j), point(i+1,j+1), 0);
            add_edge(point(i+1,j+1), point(i,j), 0);
            // 连接(i+1,j)和(i,j+1)，边权1
            add_edge(point(i+1,j), point(i,j+1), 1);
            add_edge(point(i,j+1), point(i+1,j), 1);
        } else {
            // 连接(i,j)和(i+1,j+1)，边权1
            add_edge(point(i,j), point(i+1,j+1), 1);
            add_edge(point(i+1,j+1), point(i,j), 1);
            // 连接(i+1,j)和(i,j+1)，边权0
            add_edge(point(i+1,j), point(i,j+1), 0);
            add_edge(point(i,j+1), point(i+1,j), 0);
        }
    }
}
```
其中，`add_edge`函数用于建立无向边（因为旋转格子不影响双向通行）。


#### 3. 双端队列BFS
初始化距离数组`dis`为无穷大，起点`(0,0)`的距离为0，入队。然后循环处理队列中的节点：
```cpp
deque<pair<int, int>> q; // 存储节点坐标
vector<int> dis((n+1)*(m+1), INT_MAX);
dis[point(0,0)] = 0;
q.push_back({0, 0});

while (!q.empty()) {
    auto [x, y] = q.front();
    q.pop_front();
    int u = point(x, y);
    // 遍历四个方向（根据边权处理）
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i]; // dx/dy是方向数组，如{1,1}, {-1,-1}, {1,-1}, {-1,1}
        int ny = y + dy[i];
        if (nx < 0 || nx > n || ny < 0 || ny > m) continue;
        int v = point(nx, ny);
        int w = get_weight(x, y, nx, ny); // 根据当前格子的斜线方向计算边权
        if (dis[v] > dis[u] + w) {
            dis[v] = dis[u] + w;
            if (w == 0) {
                q.push_front({nx, ny}); // 边权0，入队头
            } else {
                q.push_back({nx, ny}); // 边权1，入队尾
            }
        }
    }
}
```
其中，`dx`和`dy`是方向数组，用于遍历当前节点的四个对角节点；`get_weight`函数根据当前格子的斜线方向计算边权（0或1）。


#### 4. 边界条件判断
由于每步移动**横纵坐标之和的奇偶性不变**（例如，从(i,j)到(i+1,j+1)，和增加2，奇偶性不变），起点`(0,0)`的和为0（偶数），因此终点`(n,m)`的和必须为偶数。若`n + m`为奇数，直接输出`NO SOLUTION`。


### **四、常见优化技巧**
1. **输入优化**：使用`getchar()`代替`cin`，避免输入量大时超时。例如：
   ```cpp
   inline char get_char() {
       static char buf[100000], *p1 = buf, *p2 = buf;
       return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1++;
   }
   ```

2. **多组数据初始化**：每次处理新数据时，清空队列、距离数组和邻接表，避免残留上次数据。


### **五、题解对比与总结**
- **双端队列BFS**：是题解中最常用的方法，效率高（O(R*C)），代码简洁。例如“2c_s”、“Yukhoi”、“XY_cpp”的代码均采用此方法。
- **Dijkstra（堆优化）**：适用于边权非负的情况，但效率略低（O(M log N)）。例如“z3475”的代码使用了堆优化的Dijkstra，但不如双端队列高效。
- **SPFA（加优化）**：例如“Sino_E”的代码使用了SLF+LLL优化，但双端队列BFS更直接且效率更高。


### **六、常见错误点**
1. **节点编号错误**：将格子编号当成点编号，或坐标转换错误（如忘记`m+1`）。
2. **边权处理反**：将需要旋转的边权设为0，不需要旋转的设为1。
3. **忘记边界条件**：未判断`n + m`的奇偶性，导致不必要的搜索。
4. **多组数据初始化不全**：队列、距离数组或邻接表未清空，导致结果错误。


### **七、结论**
**双端队列BFS**是解决该问题的最优方法，其核心是将问题转化为0-1边权的最短路问题，并通过双端队列保证效率。关键步骤包括节点建模、边权设置、双端队列处理和边界条件判断。


**示例代码（双端队列BFS）**：
```cpp
#include <iostream>
#include <deque>
#include <vector>
#include <climits>
using namespace std;

const int dx[] = {1, 1, -1, -1};
const int dy[] = {1, -1, 1, -1};
const int pos_x[] = {0, 0, -1, -1};
const int pos_y[] = {0, -1, 0, -1};
const char val[] = {'\\', '/', '\\', '/'};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    while (T--) {
        int n, m;
        cin >> n >> m;
        vector<string> grid(n);
        for (int i = 0; i < n; i++) {
            cin >> grid[i];
        }
        if ((n + m) % 2 != 0) {
            cout << "NO SOLUTION\n";
            continue;
        }
        vector<vector<int>> dis(n+1, vector<int>(m+1, INT_MAX));
        deque<pair<int, int>> q;
        dis[0][0] = 0;
        q.push_back({0, 0});
        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop_front();
            for (int i = 0; i < 4; i++) {
                int nx = x + dx[i];
                int ny = y + dy[i];
                if (nx < 0 || nx > n || ny < 0 || ny > m) continue;
                int gx = x + pos_x[i];
                int gy = y + pos_y[i];
                if (gx < 0 || gx >= n || gy < 0 || gy >= m) continue;
                char c = grid[gx][gy];
                int w = (c != val[i]) ? 1 : 0;
                if (dis[nx][ny] > dis[x][y] + w) {
                    dis[nx][ny] = dis[x][y] + w;
                    if (w == 0) {
                        q.push_front({nx, ny});
                    } else {
                        q.push_back({nx, ny});
                    }
                }
            }
        }
        if (dis[n][m] == INT_MAX) {
            cout << "NO SOLUTION\n";
        } else {
            cout << dis[n][m] << "\n";
        }
    }
    return 0;
}
```


**代码解释**：
- **方向数组**：`dx`和`dy`遍历当前节点的四个对角节点；`pos_x`和`pos_y`计算当前格子的坐标；`val`存储每个方向对应的斜线方向。
- **双端队列**：处理节点时，边权0的节点入队头，边权1的节点入队尾。
- **边界条件**：判断`n + m`的奇偶性，避免无效搜索。

该代码高效解决了电路维修问题，符合题目的时间和空间要求。

---
处理用时：160.24秒