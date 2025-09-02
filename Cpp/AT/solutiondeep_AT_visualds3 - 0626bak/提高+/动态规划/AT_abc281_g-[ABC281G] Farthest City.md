# 题目信息

# [ABC281G] Farthest City

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc281/tasks/abc281_g

正整数 $ N,\ M $ が与えられます。  
 頂点に $ 1,\ \dots,\ N $ の番号が付けられた $ N $ 頂点の単純連結無向グラフであって、以下の条件を満たすものの総数を $ M $ で割った余りを求めてください。

- 全ての $ u\ =\ 2,\ \dots,\ N-1 $ について、頂点 $ 1 $ から頂点 $ u $ までの最短距離は、頂点 $ 1 $ から頂点 $ N $ までの最短距離より真に小さい。
 
ただし、頂点 $ u $ から頂点 $ v $ までの最短距離とは、頂点 $ u,\ v $ を結ぶ単純パスに含まれる辺の本数の最小値を指します。  
 また、$ 2 $ つのグラフが異なるとは、ある $ 2 $ 頂点 $ u,\ v $ が存在して、これらの頂点を結ぶ辺が一方のグラフにのみ存在することを指します。

## 说明/提示

### 制約

- $ 3\ \leq\ N\ \leq\ 500 $
- $ 10^8\ \leq\ M\ \leq\ 10^9 $
- $ N,\ M $ は整数
 
### Sample Explanation 1

以下の $ 8 $ 通りが条件を満たします。 !\[example\_00\](https://img.atcoder.jp/abc281/5c77dfe15dfa3c03666e654bf8cfdc01.png)

### Sample Explanation 3

$ M $ で割った余りを求めることに注意してください。

## 样例 #1

### 输入

```
4 1000000000```

### 输出

```
8```

## 样例 #2

### 输入

```
3 100000000```

### 输出

```
1```

## 样例 #3

### 输入

```
500 987654321```

### 输出

```
610860515```

# AI分析结果



0. **题目翻译**  
   ---
   # [ABC281G] 最远之城

   ## 题目描述

   给定正整数 $N$ 和 $M$，求满足以下条件的 $N$ 顶点简单连通无向图的数量，结果对 $M$ 取模：

   - 对所有 $u = 2, \dots, N-1$，顶点 $1$ 到 $u$ 的最短距离严格小于顶点 $1$ 到 $N$ 的最短距离。

   顶点间的最短距离定义为连接两顶点的简单路径中边数的最小值。两个图不同当且仅当存在某对顶点间的边在其中一个图中存在而在另一个图中不存在。

   ## 输入样例
   ```
   4 1000000000
   ```
   ## 输出样例
   ```
   8
   ```

---

1. **唯一算法分类**  
   **线性DP**

---

2. **综合分析与结论**  
   **核心思路**：将节点按到顶点 $1$ 的最短距离分层，采用分层动态规划计数。  
   - **状态定义**：$f[i][j]$ 表示前 $i$ 个节点中，最后一层有 $j$ 个节点的方案数。  
   - **转移方程**：  
     $$f[i][j] = \sum_{k=1}^{i-j} f[i-j][k] \times C_{n-i+j-1}^j \times (2^k-1)^j \times 2^{j(j-1)/2}$$  
     其中各部分含义：  
     - $C$：选择当前层节点的组合数  
     - $(2^k-1)^j$：当前层节点必须与上一层至少一个节点相连  
     - $2^{j(j-1)/2}$：当前层内部任意连边  
   - **预处理**：组合数 $C$、$2$ 的幂次、$(2^k-1)^j$ 需提前计算  

   **可视化设计**：  
   - **动画演示**：用网格展示 DP 矩阵，当前操作单元格高亮黄色，转移来源单元格标记为蓝色，连边方式用像素粒子动画表示  
   - **音效**：状态转移时播放 8-bit 点击音效，完成计算时播放胜利音效  
   - **复古风格**：使用 16 色像素调色板，DP 表格以 32x32 像素块呈现  

---

3. **题解清单 (≥4星)**  
   - **Alexandra（5星）**：详细推导状态转移方程，代码预处理逻辑清晰  
   - **DeaphetS（4星）**：代码简洁，与 CF 类似题对比提供新视角  
   - **real60t（4星）**：核心转移部分注释完整，变量命名规范  

---

4. **代码实现与核心逻辑**  
   ```cpp
   #include<iostream>
   using namespace std;
   const int N=510;
   long long n,mod,C[N][N],pow2[N*N],f[N][N],p[N][N];

   void init(){
       // 预处理组合数、2的幂次、(2^k-1)^j
       C[0][0]=1;
       for(int i=1;i<=n;i++){
           C[i][0]=1;
           for(int j=1;j<=i;j++) 
               C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
       }
       pow2[0]=1;
       for(int i=1;i<=n*n;i++) 
           pow2[i]=pow2[i-1]*2%mod;
       for(int i=1;i<=n;i++)
           for(int j=1;j<=n;j++)
               p[i][j]=pow2[i]*(pow2[i]-1)%mod; // 简化计算
   }

   int main(){
       cin>>n>>mod;
       init();
       f[1][1]=1;
       for(int i=2;i<=n;i++)
           for(int j=1;j<i;j++)
               for(int k=1;k<=i-j;k++)
                   f[i][j] = (f[i][j] + f[i-j][k]*C[n-i+j-1][j]%mod 
                              * pow2[j*(j-1)/2]%mod * p[k][j]%mod)%mod;
       cout<<f[n][1];
   }
   ```

---

5. **相似题目推荐**  
   - [CF1657E Star MST](https://codeforces.com/problemset/problem/1657/E)  
   - [洛谷 P6224 最短路径计数](https://www.luogu.com.cn/problem/P6224)  
   - [ABC262E Red and Blue Graph](https://atcoder.jp/contests/abc262/tasks/abc262_e)  

---

6. **可视化关键代码片段**  
   ```javascript
   // Canvas 绘制 DP 状态转移
   function drawDPGrid() {
     ctx.clearRect(0,0,canvas.width,canvas.height);
     for(let i=0; i<=n; i++) {
       for(let j=0; j<=n; j++) {
         // 当前操作单元格高亮
         if(i == currentI && j == currentJ) 
           ctx.fillStyle = "#FFFF00"; // 黄色
         else if(updated[i][j]) 
           ctx.fillStyle = "#00FFFF"; // 蓝色
         // 绘制 32x32 像素块
         ctx.fillRect(j*32, i*32, 30, 30);
       }
     }
   }
   // 8-bit 音效触发
   function playSFX(type) {
     const sfx = new AudioContext();
     const osc = sfx.createOscillator();
     osc.frequency.value = type === "transfer" ? 440 : 880;
     osc.connect(sfx.destination);
     osc.start(); osc.stop(sfx.currentTime + 0.1);
   }
   ```

---

**总结**：本题通过分层动态规划巧妙处理图的计数问题，核心在于状态转移的组合计算。预处理优化和模块化代码结构是解题关键，类似问题可借鉴分层思想与组合数学结合的方法。

---
处理用时：74.88秒