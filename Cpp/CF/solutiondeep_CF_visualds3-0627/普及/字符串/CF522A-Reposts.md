# 题目信息

# Reposts

## 题目描述

One day Polycarp published a funny picture in a social network making a poll about the color of his handle. Many of his friends started reposting Polycarp's joke to their news feed. Some of them reposted the reposts and so on.

These events are given as a sequence of strings "name1 reposted name2", where name1 is the name of the person who reposted the joke, and name2 is the name of the person from whose news feed the joke was reposted. It is guaranteed that for each string "name1 reposted name2" user "name1" didn't have the joke in his feed yet, and "name2" already had it in his feed by the moment of repost. Polycarp was registered as "Polycarp" and initially the joke was only in his feed.

Polycarp measures the popularity of the joke as the length of the largest repost chain. Print the popularity of Polycarp's joke.

## 样例 #1

### 输入

```
5
tourist reposted Polycarp
Petr reposted Tourist
WJMZBMR reposted Petr
sdya reposted wjmzbmr
vepifanov reposted sdya
```

### 输出

```
6
```

## 样例 #2

### 输入

```
6
Mike reposted Polycarp
Max reposted Polycarp
EveryOne reposted Polycarp
111 reposted Polycarp
VkCup reposted Polycarp
Codeforces reposted Polycarp
```

### 输出

```
2
```

## 样例 #3

### 输入

```
1
SoMeStRaNgEgUe reposted PoLyCaRp
```

### 输出

```
2
```

# AI分析结果



## 算法分类
图论（最长路径问题 / 树形DP）

---

## 题解思路与核心分析

### 题目核心
构建转发关系的树形结构，求从根节点（Polycarp）出发的最长链长度。关键点在于：
1. 转发关系构成内向树（每个节点只有一个父节点）
2. 保证无环（题目条件中name1首次转发）

### 解决难点
1. **字符串映射**：将大小写混合的字符串映射为唯一ID（需统一转为小写）
2. **树形结构建模**：正确建立父-子关系（注意输入顺序是name1转发name2，实际应为name2→name1的边）
3. **最长路径计算**：通过DFS或树形遍历快速求解深度

### 题解对比
| 题解           | 亮点                          | 缺点                          |
|---------------|-------------------------------|-------------------------------|
| 封禁用户       | 利用优先队列处理路径          | Dijkstra本非最长路径最优解     |
| _FILARET_      | 完整展示Floyd实现             | O(n³)复杂度，效率低           |
| Southern_Dynasty | 发现内向树性质，O(n)复杂度     | 需正确处理树形遍历方向         |

---

## 最优思路提炼
**内向树最大深度法**：
1. **映射节点**：使用哈希表将大小写统一后的字符串映射为数字ID
2. **建树**：对每个转发关系建立反向边（name2→name1）
3. **计算深度**：从根节点（Polycarp）出发，递归或迭代计算每个节点的深度（当前深度=父节点深度+1）
4. **维护最大值**：遍历所有节点深度取最大值

**关键代码片段**：
```cpp
// 建立映射
map<string, int> id_map;
int get_id(string s) {
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    if (!id_map.count(s)) id_map[s] = id_map.size()+1;
    return id_map[s];
}

// 计算深度
vector<int> depth(n+1, 1);
for (auto [child, parent] : edges) {
    depth[child] = depth[parent] + 1;
}
cout << *max_element(depth.begin(), depth.end());
```

---

## 同类型题推荐
1. P1352 没有上司的舞会（树形DP基础）
2. P3379 【模板】最近公共祖先（LCA树形结构处理）
3. P4017 最大食物链计数（DAG最长路径）

---

## 可视化设计（树形展开动画）
**动画方案**：
1. **像素风格树**：根节点Polycarp显示为金色方块，子节点按层展开
2. **动态生长**：每层节点以0.5秒间隔从父节点方向延伸绿色连线
3. **深度标记**：当前最深节点闪烁红色边框，右侧实时更新最大深度值
4. **音效配合**：
   - 节点展开："哔"声（8-bit短音）
   - 更新最大值：上升音阶

**交互控制**：
```javascript
// 伪代码示例
class RepostTree {
    constructor() {
        this.speed = 500; // 动画速度
        this.maxDepth = 1; // 当前最大深度
    }
    
    async buildTree(edges) {
        for (const [child, parent] of edges) {
            // 绘制父子节点及连线
            await sleep(this.speed); 
            this.updateMaxDepth(child.depth);
        }
    }
}
```

---

## 题解评分（≥4星）

### Southern_Dynasty（⭐⭐⭐⭐⭐）
- **亮点**：发现内向树性质，O(n)时间复杂度
- **关键实现**：通过入度/出度快速定位叶子节点
- **代码参考**：[CF Submission](https://codeforces.com/contest/522/submission/207563158)

### 封禁用户（⭐⭐⭐⭐）
- **亮点**：完整展示字符串映射与图论结合
- **优化点**：改用最大堆优化Dijkstra

### ifyml（⭐⭐⭐⭐）
- **亮点**：简洁的Floyd实现，适合小规模数据
- **注意点**：邻接矩阵初始化为极大值

---

## 核心算法演示
```python
# 树形DFS示例（伪代码）
def max_depth(node):
    if not node.children: 
        return 1
    return 1 + max(max_depth(child) for child in node.children)

# 输入转换示例
edges = [
    ("tourist", "polycarp"),
    ("petr", "tourist"),
    ("wjmzbmr", "petr")
]

# 构建树形结构
tree = defaultdict(list)
for child, parent in edges:
    tree[parent].append(child)

print(max_depth("polycarp"))  # 输出4
```

---
处理用时：68.79秒