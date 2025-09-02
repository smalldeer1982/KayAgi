# 题目信息

# 「KDOI-04」XOR Sum

## 题目背景

凯文一眼秒了这题。

![](https://cdn.luogu.com.cn/upload/image_hosting/lh1xvu75.png)

## 题目描述

给定一个正整数 $n$，请构造一个长度为 $n$ 的**非负整数**序列 $a_1,a_2,\dots,a_n$，满足：

+ 对于所有 $1\le i\le n$，都有 $0\le a_i\le m$。
+ $a_1\oplus a_2\oplus\dots\oplus a_n=k$。其中 $\oplus$ 表示[按位异或](https://baike.baidu.com/item/%E5%BC%82%E6%88%96/10993677)运算。

或者判断不存在这样的序列。

## 说明/提示

**【样例解释】**

对于第 $1$ 组测试数据，有且仅有一个序列满足条件。

对于第 $2$ 组测试数据，由于 $4\oplus 7=3$ 且 $4,7\le10$，所以这是一个合法的答案。同样地，序列 $(2,1)$ 也是一个合法的答案。

对于第 $4$ 组测试数据，可以证明不存在满足要求的序列。

**【数据范围】**

记 $\sum n$ 为单个测试点中所有 $n$ 的值之和。

对于所有测试数据，保证 $1\le T\le 1~000$，$1\le n\le 2\cdot10^5$，$0\le m,k\le 10^8$，$\sum n\le 2\cdot10^5$。

**【子任务】**

**本题开启捆绑测试。**

+ Subtask 1 (18 pts)：$k\le m$。
+ Subtask 2 (82 pts)：没有额外的约束条件。

## 样例 #1

### 输入

```
5
1 2 2
2 3 10
2 11 8
20 200000 99999
11 191 9810```

### 输出

```
2 
4 7 
8 3 
-1
191 191 191 191 191 191 191 191 191 191 191 ```

# AI分析结果

### 综合分析与结论
这些题解主要围绕构造满足特定异或和条件的序列展开。思路上，都先考虑了 $k$ 和 $m$ 的大小关系，以及 $k$ 与 $m$ 二进制位数的比较来判断是否有解。算法要点在于利用异或的性质，如任何数异或 $0$ 等于其本身，以及异或不进位等特性。解决难点在于当 $k > m$ 时如何构造满足条件的序列。

各题解质量参差不齐，部分题解思路清晰、代码简洁，部分题解代码可读性较差或思路阐述不够详细。

### 所选的题解
- **作者：JuRuoOIer（5星）**
  - **关键亮点**：思路清晰，详细阐述异或性质及解题思路，代码注释详细，通过自定义函数计算二进制长度，逻辑严谨。
  - **个人心得**：无
  ```cpp
  ll log2(ll x){//用不断除以 2 的方式求二进制长度（仅比转换成二进制少了取余，因此很明显正确） 
      ll ans=0;
      while(x){
          ans++;
          x/=2;
      }
      return ans;
  }
  int main(){
      cin>>t;
      while(t--){
          cin>>n>>k>>m;
          if(log2(m)<log2(k)){//m 的二进制长度小于 k，无解 
              cout<<"-1\n";
          }
          else if(m<k){//m<k 的情况，见 Part2-2 
              if(n==1)cout<<"-1\n";//一项不够，无解 
              else{
                  cout<<(1ll<<log2(k)-1)<<' '<<k-(1ll<<log2(k)-1);//左移，1<<k 结果为 2^k 
                  for(int i=0;i<n-2;i++){//补 0 
                      cout<<" 0";
                  }
                  cout<<endl;
              }
          }
          else{
              cout<<k;
              for(int i=0;i<n-1;i++){//补 0 
                  cout<<" 0";
              }
              cout<<endl;
          }
      }
      return 0;
  }
  ```
  - **核心实现思想**：先通过自定义的 `log2` 函数判断 $m$ 和 $k$ 的二进制长度，若 $m$ 的二进制长度小于 $k$ 则无解；若 $m \geq k$，直接输出 $k$ 和 $n - 1$ 个 $0$；若 $m < k$ 且 $n > 1$，将 $k$ 拆分为 $2^{\lfloor\log_2k\rfloor}$ 和 $k - 2^{\lfloor\log_2k\rfloor}$ 输出，再补 $n - 2$ 个 $0$。

- **作者：佬头（4星）**
  - **关键亮点**：对无解情况和构造序列的分析较为详细，给出两种判断是否存在可构造序列的方法，并对比复杂度，代码简洁。
  - **个人心得**：感谢管理指出错误，完善了对二进制数位个数的表示。
  ```cpp
  int check(int &k, int &m){
      int i;
      for(i = 0; (1 << i) <= k; ++ i) if((1 << i) > m) return 0;
      return 1 << (i - 1);
  }
  int main(){
      for(int _ = read(); _ >= 1; _ --){
          n = read(), k = read(), m = read();
          if(k <= m){
              for(int i = 1; i < n; ++ i) fputs("0 ", stdout);
              write(k), putchar('\n');
          }
          else if((m ^ k) <= m && n > 1){
              for(int i = 2; i < n; ++ i) fputs("0 ", stdout);
              write(m), putchar(' ');
              write(m ^ k), putchar('\n');
          }
          else fputs("-1\n", stdout);
      }
      return 0;
  }
  ```
  - **核心实现思想**：`check` 函数用于判断是否有解，若 $k \leq m$，直接输出 $k$ 和 $n - 1$ 个 $0$；若 $k > m$，判断 $m \oplus k \leq m$ 且 $n > 1$ 时，输出 $m$ 和 $m \oplus k$ 以及 $n - 2$ 个 $0$，否则输出 `-1`。

- **作者：_O_v_O_（4星）**
  - **关键亮点**：思路简洁明了，直接根据 $k$ 和 $m$ 的关系以及 $k$ 的二进制位数进行构造，代码简洁易懂。
  - **个人心得**：无
  ```cpp
  signed main(){
      ios::sync_with_stdio(0);
      cin.tie(nullptr);
      cin>>T;
      while(T--){
          cin>>n>>k>>m;
          int logk=ceil(log2(k));
          if((int)(log2(m))<(int)(log2(k))){
              cout<<-1<<endl;
          }
          else if(m<k){
              if(n==1){
                  cout<<-1<<endl;
              }
              else{
                  cout<<(1ll<<(logk-1))<<' '<<k-(1ll<<(logk-1))<<' ';
                  for(int i=1;i<n-1;i++) cout<<0<<' ';
                  cout<<endl;
              }
          }
          else{
              cout<<k<<' ';
              for(int i=1;i<n;i++) cout<<0<<' ';
              cout<<endl;
          }
      }
      return 0;
  }
  ```
  - **核心实现思想**：先计算 $k$ 的二进制位数 `logk`，若 $m$ 的二进制位数小于 `logk` 则无解；若 $m \geq k$，输出 $k$ 和 $n - 1$ 个 $0$；若 $m < k$ 且 $n > 1$，输出 $2^{\lfloor\log_2k\rfloor}$ 和 $k - 2^{\lfloor\log_2k\rfloor}$ 以及 $n - 2$ 个 $0$。

### 最优关键思路或技巧
利用异或的基本性质，如 $a \oplus 0 = a$ 和异或不进位特性，通过比较 $k$ 和 $m$ 的大小以及二进制位数来判断是否有解并构造序列。在 $k > m$ 时，将 $k$ 拆分成合适的两部分（如 $2^{\lfloor\log_2k\rfloor}$ 和 $k - 2^{\lfloor\log_2k\rfloor}$）来满足条件。

### 可拓展思路
此类题目可拓展到更复杂的位运算构造问题，或者结合其他数据结构和算法进行综合考察。类似算法套路是先分析目标值与限制条件的关系，利用位运算的特性进行构造或判断无解。

### 相似知识点洛谷题目
- [P1514 引水入城](https://www.luogu.com.cn/problem/P1514)：涉及位运算和图的搜索。
- [P1876 开灯](https://www.luogu.com.cn/problem/P1876)：通过位运算模拟开关灯操作。
- [P2141 珠心算测验](https://www.luogu.com.cn/problem/P2141)：利用位运算优化枚举判断。 

---
处理用时：34.72秒