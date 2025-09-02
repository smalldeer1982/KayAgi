# 题目信息

# [ABC189E] Rotate and Flip

## 题目描述

给出 $N$ 个点，以及每个点得坐标 $(x_i,y_i)$，给出 $M$ 次操作，操作如下：

- 第一种操作：将所有点绕原点 $(0,0)$ 顺时针旋转 $90$ 度。

- 第二种操作：将所有点绕原点 $(0,0)$ 逆时针旋转 $90$ 度。

- 第三种操作：以 $x=p$ 为对称轴，将所有的点对称过去。

- 第四种操作：以 $y=p$ 为对称轴，将所有的点对称过去。

接着给出 $Q$ 组询问，每次询问在某次操作过后某个点的坐标。

## 样例 #1

### 输入

```
1

1 2

4

1

3 3

2

4 2

5

0 1

1 1

2 1

3 1

4 1```

### 输出

```
1 2

2 -1

4 -1

1 4

1 0```

## 样例 #2

### 输入

```
2

1000000000 0

0 1000000000

4

3 -1000000000

4 -1000000000

3 1000000000

4 1000000000

2

4 1

4 2```

### 输出

```
5000000000 4000000000

4000000000 5000000000```

# AI分析结果

### 题目内容重写
# [ABC189E] 旋转与翻转

## 题目描述

给出 $N$ 个点，以及每个点的坐标 $(x_i,y_i)$，给出 $M$ 次操作，操作如下：

- 第一种操作：将所有点绕原点 $(0,0)$ 顺时针旋转 $90$ 度。

- 第二种操作：将所有点绕原点 $(0,0)$ 逆时针旋转 $90$ 度。

- 第三种操作：以 $x=p$ 为对称轴，将所有的点对称过去。

- 第四种操作：以 $y=p$ 为对称轴，将所有的点对称过去。

接着给出 $Q$ 组询问，每次询问在某次操作过后某个点的坐标。

## 样例 #1

### 输入

```
1

1 2

4

1

3 3

2

4 2

5

0 1

1 1

2 1

3 1

4 1```

### 输出

```
1 2

2 -1

4 -1

1 4

1 0```

## 样例 #2

### 输入

```
2

1000000000 0

0 1000000000

4

3 -1000000000

4 -1000000000

3 1000000000

4 1000000000

2

4 1

4 2```

### 输出

```
5000000000 4000000000

4000000000 5000000000```

### 算法分类
模拟

### 题解分析与结论
本题的核心在于如何处理多次操作后的点坐标变化。由于每次操作都是对所有点进行的，因此可以通过维护一个全局的变换矩阵或变量来记录每次操作对点坐标的影响，而不是对每个点单独进行计算。这样可以大大减少计算量，提高效率。

### 所选题解
#### 作者：2011qiqi (4星)
**关键亮点**：
- 通过维护 $cnt_x/y$、$opt_x/y$、是否翻转横纵坐标等变量，简化了坐标变换的计算。
- 使用了离线处理的方法，先对询问进行排序，再按顺序处理操作，最后输出结果。

**代码核心实现**：
```cpp
re ll turn=0,x_opt=1,y_opt=1,x_cnt=0,y_cnt=0;
for(i=1;i<=m+1;++i){
    while(a[id[j]]==i-1){
        x_res[id[j]]=x_cnt+1LL*x_opt*x[b[id[j]]];
        y_res[id[j]]=y_cnt+1LL*y_opt*y[b[id[j]]];
        if(turn) swap(x_res[id[j]], y_res[id[j]]);
        ++j;
    }
    if(opt[i]==1){
        if(turn){
            y_opt=-y_opt;
            y_cnt=-y_cnt;
        }else{
            x_opt=-x_opt;
            x_cnt=-x_cnt;
        }
        turn^=1;
    }else if(opt[i]==2){
        if(turn){
            x_opt=-x_opt;
            x_cnt=-x_cnt;
        }else{
            y_opt=-y_opt;
            y_cnt=-y_cnt;
        }
        turn^=1;
    }else if(opt[i]==3){
        if(turn){
            y_cnt=2LL*p1[i]-y_cnt;
            y_opt=-y_opt;
        }else{
            x_cnt=2LL*p1[i]-x_cnt;
            x_opt=-x_opt;
        }
    }else{
        if(turn){
            x_cnt=2LL*p1[i]-x_cnt;
            x_opt=-x_opt;
        }else{
            y_cnt=2LL*p1[i]-y_cnt;
            y_opt=-y_opt;
        }
    }
}
```

#### 作者：wangjiajian (4星)
**关键亮点**：
- 将每个操作视为一个函数，通过复合函数的方式推导出最终的坐标变换表达式。
- 使用了 $change$、$digital_x$、$digital_y$、$pls_x$、$pls_y$ 五个变量来维护变换状态。

**代码核心实现**：
```cpp
inline void work(int i) {  // 递推符合函数表达式
    if(opt[i] == 1) {
        change = !change;
        tmp = digital_x;
        digital_x = digital_y;
        digital_y = !tmp;
        pls_tmp = pls_x;
        pls_x = pls_y;
        pls_y = -pls_tmp;
    } else if(opt[i] == 2) {
        change = !change;
        tmp = digital_x;
        digital_x = !digital_y;
        digital_y = tmp;
        pls_tmp = pls_x;
        pls_x = -pls_y;
        pls_y = pls_tmp;
    } else if(opt[i] == 3) {
        digital_x = !digital_x;
        pls_x = -pls_x + (p[i]<<1);
    } else {
        digital_y = !digital_y;
        pls_y = -pls_y + (p[i]<<1);
    }
}
```

### 最优关键思路
通过维护全局变量来记录每次操作对点坐标的影响，而不是对每个点单独进行计算。这种方法可以大大减少计算量，提高效率。

### 可拓展之处
类似的问题可以通过维护全局变换矩阵或变量来处理多次操作后的结果，例如在图形学中的坐标变换、物理模拟中的物体运动等。

### 推荐题目
1. [P1908 逆序对](https://www.luogu.com.cn/problem/P1908)
2. [P3374 【模板】树状数组 1](https://www.luogu.com.cn/problem/P3374)
3. [P3383 【模板】线性筛素数](https://www.luogu.com.cn/problem/P3383)

---
处理用时：37.25秒