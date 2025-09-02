# 题目信息

# [POI 2008] KUP-Plot purchase

## 题目描述

Byteasar is going to buy an industrial plot.

His fortune is estimated at $k$ bythalers and this is exactly the amount    Byteasar would like to spend on the parcel.

Finding a parcel worth exactly $k$ bythalers, however, is not an easy task.

For this reason Byteasar is ready to buy a more expensive plot.

He considers taking out a loan. The Byteotian Credit Bank will grant him    a loan of up to $k$ bythalers. Thus, Byteasar can spend no more than $2k$    bythalers on the parcel and he would like to spend no less than $k$ bythalers.

The area in which Byteasar wants to buy his parcel is a square with side    length of $n$ metres. The current landlords have set up various prices per square metre. Byteasar has spoken to each one of them and has then prepared a price map    of the area. The map depicts the price of every metre by metre square. Clearly, there    are $n^2$ such squares. Now is the time to find the dream parcel. It has to be rectangular and consist of whole unit squares. Byteasar has already started looking for the plot on the map,    but after many hours he was still unable to find a suitable one. Be a chap and help him!

<Task> 

Write a programme that:

reads the numbers $k$ and $n$ from the standard input,  along with the price map of the area, determines a parcel with price in the interval $[k,2k]$ or states that no such parcel exists, writes out the result to the standard output.



## 说明/提示


给定 $k,n$ 和 $n\times n$ 的矩阵，求一个子矩形满足权值和在 $[k,2k]$ 之间。

$n<2000$，$1\le k\le10^9$，每个价格都是不大于$2 \times 10^9$ 的非负整数。

感谢@cn：苏卿念 提供的spj

## 样例 #1

### 输入

```
8 4
1 2 1 3
25 1 2 1
4 20 3 3
3 30 12 2```

### 输出

```
2 1 4 2```

# AI分析结果



## 算法分类
**悬线法/单调栈**

---

## 题解思路与核心难点

### 核心思路
1. **特判条件**  
   - 单个元素在 [k, 2k] 时直接输出
   - 单个元素 >2k 时标记为障碍点
2. **极大子矩形搜索**  
   - 使用悬线法或单调栈找到全部由 <k 元素构成的最大子矩形
   - 若该矩形总和 <k 则无解
3. **切割调整**  
   - 当矩形总和 >2k 时，逐行/逐列切割，每次切割保证剩余部分总和 ≥k
   - 切割时优先处理整行/整列，若某行总和 >2k 则在该行内逐个元素调整

### 解决难点
1. **数学证明**  
   - 总和 ≥k 的矩形必然存在解（连续调整不会跳过 [k,2k] 区间）
2. **高效计算极大子矩形**  
   - 悬线法：维护每个点向上延伸的最大高度、左右边界
   - 单调栈：逐行处理，维护高度递增栈计算最大矩形
3. **坐标转换**  
   - 输出时需将矩阵行列转换为题目要求的坐标系

---

## 题解评分 ≥4星

### kczno1（★★★★★）
- **亮点**：悬线法直接处理极大子矩形，切割逻辑简洁高效
- **核心代码**：
  ```cpp
  while(S(li,lj,i,rj)>2*k) {
    if(S(li,lj,li+1,rj)>2*k) ++lj;
    else ++li;
  }
  ```

### i207M（★★★★☆）
- **亮点**：详细注释切割时的边界处理，使用单调栈维护柱状图
- **心得**：强调单调栈入栈条件应为 >= 而非 >

### 奇米（★★★★☆）
- **亮点**：完整注释坐标转换问题，切割时优先处理整行
- **核心代码**：
  ```cpp
  while(y11<y2) {
    mid=(y11+y2)/2;
    if(p1<=2*k) y11=mid+1;
    else y2=mid;
  }
  ```

---

## 关键思路与技巧

### 核心算法流程
1. **悬线法预处理**  
   ![悬线法示意图](https://i.imgur.com/5gQ9yN0.png)  
   - `h[i][j]`: 点 (i,j) 向上延伸的最大高度
   - `l[i][j]`: 向左第一个比当前高度小的位置
   - `r[i][j]`: 向右第一个比当前高度小的位置

2. **切割策略**  
   ```python
   def cut_rect(x1,y1,x2,y2):
       while sum > 2k:
           if row_sum > 2k:  # 切割行
               remove rightmost column
           else:             # 切割列
               remove bottom row
       return (x1,y1,x2,y2)
   ```

---

## 类似题目推荐
1. **P4147 玉蟾宫**（悬线法模板题）
2. **P2733 家的范围**（极大子矩形计数）
3. **P1191 矩形**（二维前缀和+滑动窗口）

---

## 可视化设计

### 复古像素风格演示
```html
<canvas id="demo" width="800" height="600"></canvas>
<script>
// 初始化 Canvas
const ctx = document.getElementById('demo').getContext('2d');
const COLORS = ['#000','#F00','#0F0','#00F','#FF0','#F0F']; // 8-bit调色板

// 悬线法动画
function drawHLine(i, j, h) {
    ctx.fillStyle = COLORS[1];
    ctx.fillRect(j*10, i*10 - h*10, 10, h*10); // 绘制悬线
    playSound('beep'); // 触发音效
}

// 音效系统
function playSound(type) {
    const audioCtx = new AudioContext();
    const oscillator = audioCtx.createOscillator();
    oscillator.type = 'square';
    oscillator.frequency.setValueAtTime(type=='cut' ? 880 : 440, audioCtx.currentTime);
    oscillator.connect(audioCtx.destination);
    oscillator.start();
    oscillator.stop(audioCtx.currentTime + 0.1);
}

// 自动演示模式
let autoStep = setInterval(() => {
    if(!nextAlgorithmStep()) clearInterval(autoStep); 
}, 500);
</script>
```

### 交互设计
- **颜色标记**：当前处理的悬线用红色，已确定的极大矩形用绿色
- **音效提示**：悬线扩展时播放低音，切割成功时播放高音
- **步进控制**：空格键暂停/继续，方向键单步执行

---

## 核心代码实现

### 悬线法关键片段
```cpp
// 计算每个点的悬线高度
for(int i=1; i<=n; i++) {
    for(int j=1; j<=n; j++) {
        if(a[i][j] < k) h[i][j] = h[i-1][j] + 1;
        else h[i][j] = 0;
    }
}

// 单调栈求最大矩形
stack<int> st;
for(int j=1; j<=n+1; j++) {
    while(!st.empty() && h[i][j] < h[i][st.top()]) {
        int cur = st.top(); st.pop();
        int area = h[i][cur] * (j - st.top() - 1);
        if(area > max_area) update_max_rect();
    }
    st.push(j);
}
```

### 切割逻辑
```cpp
void cut(int x1, int y1, int x2, int y2) {
    while(sum > 2*k) {
        int row_sum = getRowSum(x1, y1, y2);
        if(row_sum > 2*k) {  // 切割行
            for(int y=y2; y>=y1; y--) {
                row_sum -= a[x1][y];
                if(row_sum <= 2*k) return (x1,y1,x1,y);
            }
        } else {             // 切割列
            sum -= row_sum;
            x1++;
        }
    }
}
```

通过结合悬线法与逐步切割策略，该算法在O(n²)时间内高效解决问题，并通过可视化手段直观展示关键步骤。

---
处理用时：87.03秒