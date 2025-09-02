# 题目信息

# Pseudorandom Sequence Period

## 题目描述

Polycarpus has recently got interested in sequences of pseudorandom numbers. He learned that many programming languages generate such sequences in a similar way: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF172B/02c4eeecb957768b3b96e1481a979d6934aab656.png) (for $ i>=1 $ ). Here $ a $ , $ b $ , $ m $ are constants, fixed for the given realization of the pseudorandom numbers generator, $ r_{0} $ is the so-called $ randseed $ (this value can be set from the program using functions like RandSeed(r) or srand(n)), and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF172B/99fd5677ca5c02520be7595d9b1eaf3e9972e601.png) denotes the operation of taking the remainder of division.

For example, if $ a=2,b=6,m=12,r_{0}=11 $ , the generated sequence will be: $ 4,2,10,2,10,2,10,2,10,2,10,... $ .

Polycarpus realized that any such sequence will sooner or later form a cycle, but the cycle may occur not in the beginning, so there exist a preperiod and a period. The example above shows a preperiod equal to 1 and a period equal to 2.

Your task is to find the period of a sequence defined by the given values of $ a,b,m $ and $ r_{0} $ . Formally, you have to find such minimum positive integer $ t $ , for which exists such positive integer $ k $ , that for any $ i>=k $ : $ r_{i}=r_{i+t} $ .

## 说明/提示

The first sample is described above.

In the second sample the sequence is (starting from the first element): $ 0,3,4,1,0,3,4,1,0,... $

In the third sample the sequence is (starting from the first element): $ 33,24,78,78,78,78,... $

## 样例 #1

### 输入

```
2 6 12 11
```

### 输出

```
2
```

## 样例 #2

### 输入

```
2 3 5 1
```

### 输出

```
4
```

## 样例 #3

### 输入

```
3 6 81 9
```

### 输出

```
1
```

# AI分析结果



# 伪随机序列周期

## 题目重述
**题目描述**  
Polycarpus 最近对伪随机数序列产生了兴趣。他了解到许多编程语言以相似的方式生成此类序列：  
对于 $i \geq 1$，有 $r_i = (a \cdot r_{i-1} + b) \mod m$。其中 $a, b, m$ 是固定的常数，$r_0$ 是初始种子值。  
任务要求找出给定参数下生成序列的最小周期长度 $t$，使得存在某个 $k$，当 $i \geq k$ 时 $r_i = r_{i+t}$。

**样例说明**  
例如输入 `2 6 12 11`，生成序列为 `4,2,10,2,10...`，输出周期 2。  
输入 `3 6 81 9` 时，序列快速进入 `78` 的无限循环，输出周期 1。

---

**算法分类**  
模拟

---

## 题解对比与结论

### 关键思路总结
所有题解均采用**状态记录法**：  
1. 利用数组或哈希表记录每个数值首次出现的索引位置  
2. 当重复数值出现时，当前索引与首次索引的差值即为周期  
3. 数组实现（时间复杂度 O(1) 访问）相比 map（O(log n)）更高效，但需注意数据范围

### 高分题解推荐
#### 1. 作者：ZhanPJ (5星)
**核心亮点**  
- 提前记录初始值位置，正确处理边界情况  
- 数组实现高效且代码规范  
```cpp
int vis[100005];
int main(){
    int a,m,b,x,i=1;
    scanf("%d%d%d%d",&a,&b,&m,&x);
    vis[x]=1; // 初始值记录
    while(1){
        x=(a*x+b)%m;
        i++;
        if(vis[x]) return !printf("%d",i-vis[x]);
        vis[x]=i;
    }
}
```

#### 2. 作者：FQR_ (4星)
**核心亮点**  
- 使用 map 实现通用性，适合大范围数据  
- 代码简洁，思路清晰  
```cpp
map<int,int>k;
int main(){
    int a,b,m,x;
    cin>>a>>b>>m>>x;
    for(int i=1;;i++){
        x=(a*x+b)%m;
        if(k[x]) { cout<<i-k[x]; break; }
        k[x]=i;
    }
}
```

#### 3. 作者：Bla_Bla (4星)
**核心亮点**  
- 数组直接寻址，效率极高  
- 代码直观易懂，适合小数据范围  
```cpp
int Bla[100000];
int main(){
    int i=1,a,b,m,x;
    cin>>a>>b>>m>>x;
    while(1){
        x=(a*x+b)%m;
        if(Bla[x]!=0) { cout<<i-Bla[x]; return 0; }
        Bla[x]=i++;
    }
}
```

---

## 拓展与应用
### 类似题目推荐
1. [P1464 Function](https://www.luogu.com.cn/problem/P1464) - 状态记忆化存储  
2. [CF1110E Magic Stones](https://www.luogu.com.cn/problem/CF1110E) - 序列变换规律分析  
3. [P1319 压缩技术](https://www.luogu.com.cn/problem/P1319) - 循环节检测

### 关键调试技巧
- **初始值处理**：ZhanPJ 的初始值记录方式可避免首项即循环的边界情况  
- **空间预估**：当 $m \leq 1e5$ 时数组法最优，否则改用 unordered_map 实现哈希表

---
处理用时：120.75秒