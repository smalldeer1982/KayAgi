# 题目信息

# Fox And Names

## 题目描述

Fox Ciel is going to publish a paper on FOCS (Foxes Operated Computer Systems, pronounce: "Fox"). She heard a rumor: the authors list on the paper is always sorted in the lexicographical order.

After checking some examples, she found out that sometimes it wasn't true. On some papers authors' names weren't sorted in lexicographical order in normal sense. But it was always true that after some modification of the order of letters in alphabet, the order of authors becomes lexicographical!

She wants to know, if there exists an order of letters in Latin alphabet such that the names on the paper she is submitting are following in the lexicographical order. If so, you should find out any such order.

Lexicographical order is defined in following way. When we compare $ s $ and $ t $ , first we find the leftmost position with differing characters: $ s_{i}≠t_{i} $ . If there is no such position (i. e. $ s $ is a prefix of $ t $ or vice versa) the shortest string is less. Otherwise, we compare characters $ s_{i} $ and $ t_{i} $ according to their order in alphabet.

## 样例 #1

### 输入

```
3
rivest
shamir
adleman
```

### 输出

```
bcdefghijklmnopqrsatuvwxyz
```

## 样例 #2

### 输入

```
10
tourist
petr
wjmzbmr
yeputons
vepifanov
scottwu
oooooooooooooooo
subscriber
rowdark
tankengineer
```

### 输出

```
Impossible
```

## 样例 #3

### 输入

```
10
petr
egor
endagorion
feferivan
ilovetanyaromanova
kostka
dmitriyh
maratsnowbear
bredorjaguarturnik
cgyforever
```

### 输出

```
aghjlnopefikdmbcqrstuvwxyz
```

## 样例 #4

### 输入

```
7
car
care
careful
carefully
becarefuldontforgetsomething
otherwiseyouwillbehacked
goodluck
```

### 输出

```
acbdefhijklmnogpqrstuvwxyz
```

# AI分析结果



### 唯一算法分类  
**拓扑排序**

### 综合分析与结论  
#### 核心思路与难点  
1. **核心逻辑**：  
   - 将字符视为图的节点，相邻字符串第一个不同的字符对构成有向边（前驱→后继）。  
   - 若后一个字符串是前一个的前缀且长度更短，直接判为 `Impossible`。  
   - 通过拓扑排序检测环，并生成合法字符顺序。  

2. **关键难点**：  
   - 正确构建字符间的顺序约束（边的方向）。  
   - 特判前缀情况（如样例 1 中的 `car` 和 `care`）。  
   - 处理拓扑排序结果不足 26 字母的情况（存在环或矛盾）。  

#### 可视化设计思路  
- **动画方案**：  
  1. **字符节点与边**：用像素方块表示字符（颜色区分不同字符），箭头表示顺序约束。  
  2. **拓扑队列**：以队列形式展示当前入度为 0 的字符（动态更新颜色）。  
  3. **步进控制**：高亮当前处理的字符对（如 `r→s`），伴随“滴答”音效。  
  4. **失败检测**：检测到环时，用红色闪烁提示相关节点，播放失败音效。  

- **复古游戏化**：  
  - **像素风格**：使用 8-bit 字体，字符节点用 16x16 像素块表示。  
  - **音效设计**：入队时播放“收集”音效，弹出时播放“完成”音效，失败时用经典 8-bit 错误音。  
  - **自动演示**：模拟贪吃蛇 AI 路径，自动遍历相邻字符串构建边。  

---

### 题解清单（≥4星）  
1. **杨誉yy（4.5星）**  
   - **亮点**：清晰的邻接表实现，特判前缀的逻辑简洁。  
   - **代码可读性**：变量命名清晰，注释到位。  
   - **优化点**：通过 `pas=now` 优化内存，避免存储全部字符串。  

2. **Juanzhang（4星）**  
   - **亮点**：DFS 拓扑排序实现，代码短小精悍。  
   - **优化点**：递归回溯检测环，输出逆序结果。  

3. **Clay_L（4星）**  
   - **亮点**：使用 `vector` 存储边，入度数组处理直观。  
   - **优化点**：字符转换时处理偏移（`-96` 简化计算）。  

---

### 最优思路与代码片段  
#### 核心代码（杨誉yy）  
```cpp  
// 相邻字符串比较建图  
string pas, now;  
for (int i=2; i<=n; i++) {  
    cin >> now;  
    int len = min(pas.length(), now.length());  
    for (int j=0; j<=len; j++) { // 注意 j<=len  
        if (j == len) {  
            if (pas.length() > now.length()) {  
                printf("Impossible");  
                return 0;  
            }  
            break;  
        }  
        if (pas[j] != now[j]) {  
            int u = pas[j]-'a', v = now[j]-'a';  
            l[u][++cnt[u]] = v; // 邻接表存边  
            num[v]++; // 入度统计  
            break;  
        }  
    }  
    pas = now;  
}  
```

#### 关键技巧  
- **前缀特判**：遍历到 `j==len` 时检查字符串长度差异。  
- **拓扑排序队列**：优先处理入度 0 的节点，动态更新入度。  

---

### 相似题目推荐  
1. **P1113 杂务**（拓扑排序应用）  
2. **P1347 排序**（拓扑排序检测环）  
3. **P3183 食物链**（拓扑排序计数）  

---

### 个人心得摘录  
- **杨誉yy**：  
  > “不要漏掉 `j<=len` 中的等号，否则无法捕获前缀特判条件。”  
- **kdy20100729**：  
  > “WA 的第 13 个点教会我：必须严格判断前缀情况，即使其他字符相同。”  

---

### 可视化实现（JavaScript 伪代码）  
```javascript  
// 像素风格拓扑排序动画  
class TopoVisualizer {  
    constructor() {  
        this.canvas = document.getElementById("pixelCanvas");  
        this.ctx = this.canvas.getContext('2d');  
        this.nodes = {}; // {char: {x, y, color}}  
        this.edges = []; // [{from, to}]  
        this.queue = [];  
    }  

    drawNode(char, x, y) {  
        this.ctx.fillStyle = '#8B00FF'; // 复古紫  
        this.ctx.fillRect(x*20, y*20, 16, 16); // 16x16 像素块  
        this.ctx.fillStyle = '#FFF';  
        this.ctx.fillText(char, x*20+4, y*20+12);  
    }  

    highlightEdge(from, to) {  
        this.edges.forEach(edge => {  
            if (edge.from === from && edge.to === to) {  
                this.ctx.strokeStyle = '#FFD700'; // 高亮金色  
                this.ctx.beginPath();  
                this.ctx.moveTo(...this.nodes[from]);  
                this.ctx.lineTo(...this.nodes[to]);  
                this.ctx.stroke();  
            }  
        });  
    }  
}  

// 触发音效  
function playSound(effect) {  
    const audio = new Audio(`sfx/${effect}.wav`); // 8-bit 音效  
    audio.play();  
}  
```

---
处理用时：85.82秒