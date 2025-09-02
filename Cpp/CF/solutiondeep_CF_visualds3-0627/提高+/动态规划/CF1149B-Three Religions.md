# 题目信息

# Three Religions

## 题目描述

During the archaeological research in the Middle East you found the traces of three ancient religions: First religion, Second religion and Third religion. You compiled the information on the evolution of each of these beliefs, and you now wonder if the followers of each religion could coexist in peace.

The Word of Universe is a long word containing the lowercase English characters only. At each moment of time, each of the religion beliefs could be described by a word consisting of lowercase English characters.

The three religions can coexist in peace if their descriptions form disjoint subsequences of the Word of Universe. More formally, one can paint some of the characters of the Word of Universe in three colors: $ 1 $ , $ 2 $ , $ 3 $ , so that each character is painted in at most one color, and the description of the $ i $ -th religion can be constructed from the Word of Universe by removing all characters that aren't painted in color $ i $ .

The religions however evolve. In the beginning, each religion description is empty. Every once in a while, either a character is appended to the end of the description of a single religion, or the last character is dropped from the description. After each change, determine if the religions could coexist in peace.

## 说明/提示

In the first example, after the 6th evolution the religion descriptions are: ad, bc, and ab. The following figure shows how these descriptions form three disjoint subsequences of the Word of Universe:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1149B/d2161037f06cd41962d7459e510bbcc1eef61be4.png)

## 样例 #1

### 输入

```
6 8
abdabc
+ 1 a
+ 1 d
+ 2 b
+ 2 c
+ 3 a
+ 3 b
+ 1 c
- 2
```

### 输出

```
YES
YES
YES
YES
YES
YES
NO
YES
```

## 样例 #2

### 输入

```
6 8
abbaab
+ 1 a
+ 2 a
+ 3 a
+ 1 b
+ 2 b
+ 3 b
- 1
+ 2 z
```

### 输出

```
YES
YES
YES
YES
YES
NO
YES
NO
```

# AI分析结果



# 三宗教

## 题目描述

在中东的考古研究中，你发现了三个古代宗教的踪迹：第一宗教、第二宗教和第三宗教。你整理了每个信仰的演化信息，现在想知道这些宗教的信徒能否和平共处。

宇宙之语是一个仅包含小写英文字母的长单词。每个时刻，三个宗教的描述都可以用由小写英文字母组成的单词来表示。

当且仅当三个宗教的描述能构成宇宙之语的不相交子序列时，三个宗教可以和平共处。更正式地说，存在一种给宇宙之语的部分字符染三种颜色（1、2、3）的方式，使得每个字符至多染一种颜色，且第i个宗教的描述可以通过移除所有非i色的字符得到。

宗教的演化会不断发生。初始时每个宗教的描述为空字符串。每次操作会在某个宗教的描述末尾追加字符，或删除最后一个字符。每次操作后，请判断是否满足共存条件。

## 说明/提示

第一个样例中，第6次演化后的宗教描述分别为：ad、bc、ab。下图展示了这些描述如何构成三个不相交子序列：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1149B/d2161037f06cd41962d7459e510bbcc1eef61be4.png)

## 样例 #1

### 输入

```
6 8
abdabc
+ 1 a
+ 1 d
+ 2 b
+ 2 c
+ 3 a
+ 3 b
+ 1 c
- 2
```

### 输出

```
YES
YES
YES
YES
YES
YES
NO
YES
```

## 样例 #2

### 输入

```
6 8
abbaab
+ 1 a
+ 2 a
+ 3 a
+ 1 b
+ 2 b
+ 3 b
- 1
+ 2 z
```

### 输出

```
YES
YES
YES
YES
YES
NO
YES
NO
```

---

**唯一算法分类**  
线性DP

---

## 综合分析与结论

### 核心思路
采用三维动态规划`f[i][j][k]`表示三个子序列分别匹配到第i、j、k个字符时所需的最短母串前缀。预处理`nxt[i][c]`数组快速定位字符c在位置i后的首次出现位置，将单次状态转移优化至O(1)。通过增量更新策略，在每次操作时仅重新计算受影响的状态，将时间复杂度从O(q·250³)优化至O(q·250²)。

### 状态转移方程
$$
f_{i,j,k} = \min\begin{cases}
nxt[f_{i-1,j,k}+1][s_1[i]] \\
nxt[f_{i,j-1,k}+1][s_2[j]] \\
nxt[f_{i,j,k-1}+1][s_3[k]]
\end{cases}
$$

### 关键难点
1. **三维状态维护**：传统三维DP在q次操作下无法承受时间复杂度
2. **增量更新优化**：通过分析操作类型，仅重新计算受影响的子立方体区域
3. **预处理技巧**：`nxt`数组的逆向预处理极大加速状态转移

### 可视化设计
- **像素风格矩阵**：采用16色系像素块表示三维DP数组切片，不同亮度表示状态值大小
- **动态高亮**：红色闪烁标记当前更新的状态，绿色箭头指示转移来源
- **音效反馈**：成功转移时播放8-bit上升音效，超出母串长度时触发警报音
- **自动演示模式**：按操作顺序自动播放状态更新过程，支持0.5x-3x倍速调节

---

## 题解清单（≥4星）

### 1. yuzhechuan（★★★★★）
**亮点**：  
- 预处理逻辑清晰，nxt数组边界处理严谨  
- 增量更新采用三目表达式限定更新范围  
- 代码结构紧凑，关键注释到位  

**核心代码**：
```cpp
void doit(){
    char ch;cin>>ch;
    int id;read(id);
    if(ch=='+'){
        cin>>ch;
        s[id][++len[id]]=ch-'a';
        for(int i=(id==1?len[1]:0);i<=len[1];i++) 
            for(int j=(id==2?len[2]:0);j<=len[2];j++)
                for(int k=(id==3?len[3]:0);k<=len[3];k++){
                    int &now=f[i][j][k];
                    now=n+1; 
                    if(i) now=min(now,nxt[f[i-1][j][k]+1][s[1][i]]);
                    if(j) now=min(now,nxt[f[i][j-1][k]+1][s[2][j]]);
                    if(k) now=min(now,nxt[f[i][j][k-1]+1][s[3][k]]);
                }
    }
    else len[id]--;
}
```

### 2. djh123（★★★★☆）
**亮点**：  
- 独立维护三个字符串数组  
- 删除操作时主动清空无效状态  
- 变量命名规范易读  

**优化点**：  
- 更新范围控制稍显冗余  
- 缺少nxt数组初始化细节注释  

### 3. allqpsi（★★★★☆）
**亮点**：  
- 采用字符串偏移量处理  
- 状态转移公式数学化表达  
- 包含调试经验说明  

**注意点**：  
- 字符串存储从0开始易产生偏移错误  

---

## 最优技巧提炼

1. **增量维度锁定**  
插入宗教1字符时，只需更新i维度最大值对应的平面（i=len1时所有j,k组合）

2. **nxt数组逆向预扫**  
```cpp
for(int i=n;i>=1;i--)
    for(int j=0;j<26;j++)
        nxt[i][j] = (p[i]==j+'a') ? i : nxt[i+1][j];
```

3. **无效状态剪枝**  
删除操作后直接减少长度，旧状态自动失效无需清零

---

## 同类型题目

1. **交错字符串**（LeetCode 97）  
   二维DP判断字符串交错合并

2. **最长公共子序列变体**（CF 266E）  
   三维LCS问题

---

## 推荐习题

1. **P1944 最长括号匹配**  
   线性DP处理特殊子序列

2. **P1439 最长公共子序列**  
   线性DP+离散化优化

3. **CF 1183H**  
   子序列删除代价问题

---

## 个人心得摘录

> "预处理nxt数组时，nxt[n+1][]和nxt[n+2][]都要赋为n+1，这个边界条件在样例2中会触发，调试了2小时才找到"  
> —— yuzhechuan

> "三维循环中的三目表达式(id==1?len[1]:0)是优化的精髓，将O(n³)降为O(n²)"  
> —— 匿名用户

---

## 可视化代码片段

```javascript
// 8-bit风格渲染器核心逻辑
class DPVisualizer {
    constructor(canvas) {
        this.ctx = canvas.getContext('2d');
        this.palette = ['#000000','#1D2B53','#7E2553','#008751',
                       '#AB5236','#5F574F','#C2C3C7','#FFF1E8'];
    }

    renderSlice(f, len1, len2, len3) {
        const scale = 8; // 8x8像素块
        // 投影到i-j平面（固定k=len3）
        for(let i=0; i<=len1; i++) {
            for(let j=0; j<=len2; j++) {
                const val = Math.min(f[i][j][len3], 255);
                const color = this.palette[Math.floor(val/32)];
                this.ctx.fillStyle = color;
                this.ctx.fillRect(i*scale, j*scale, scale, scale);
            }
        }
    }

    playSound(freq) {
        const osc = audioCtx.createOscillator();
        osc.frequency.value = freq;
        osc.connect(audioCtx.destination);
        osc.start(); osc.stop(0.1);
    }
}
```

---
处理用时：91.72秒