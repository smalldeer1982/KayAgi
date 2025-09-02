# 题目信息

# Painting Pebbles

## 题目描述

There are $ n $ piles of pebbles on the table, the $ i $ -th pile contains $ a_{i} $ pebbles. Your task is to paint each pebble using one of the $ k $ given colors so that for each color $ c $ and any two piles $ i $ and $ j $ the difference between the number of pebbles of color $ c $ in pile $ i $ and number of pebbles of color $ c $ in pile $ j $ is at most one.

In other words, let's say that $ b_{i,c} $ is the number of pebbles of color $ c $ in the $ i $ -th pile. Then for any $ 1<=c<=k $ , $ 1<=i,j<=n $ the following condition must be satisfied $ |b_{i,c}-b_{j,c}|<=1 $ . It isn't necessary to use all $ k $ colors: if color $ c $ hasn't been used in pile $ i $ , then $ b_{i,c} $ is considered to be zero.

## 样例 #1

### 输入

```
4 4
1 2 3 4
```

### 输出

```
YES
1
1 4
1 2 4
1 2 3 4
```

## 样例 #2

### 输入

```
5 2
3 2 4 1 3
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
5 4
3 2 4 3 5
```

### 输出

```
YES
1 2 3
1 3
1 2 3 4
1 3 4
1 1 2 3 4
```

# AI分析结果

### 题目内容
# 涂石子

## 题目描述
桌上有 $n$ 堆石子，第 $i$ 堆有 $a_{i}$ 个石子。你的任务是用给定的 $k$ 种颜色之一为每个石子涂色，使得对于每种颜色 $c$ 以及任意两堆 $i$ 和 $j$，颜色 $c$ 在第 $i$ 堆中的石子数量与在第 $j$ 堆中的石子数量之差至多为 $1$。

换句话说，设 $b_{i,c}$ 是第 $i$ 堆中颜色为 $c$ 的石子数量。那么对于任意的 $1 \leq c \leq k$，$1 \leq i, j \leq n$，都必须满足 $|b_{i,c} - b_{j,c}| \leq 1$。不一定要使用所有的 $k$ 种颜色：如果颜色 $c$ 没有在第 $i$ 堆中使用，那么 $b_{i,c}$ 视为 $0$。

## 样例 #1
### 输入
```
4 4
1 2 3 4
```
### 输出
```
YES
1
1 4
1 2 4
1 2 3 4
```

## 样例 #2
### 输入
```
5 2
3 2 4 1 3
```
### 输出
```
NO
```

## 样例 #3
### 输入
```
5 4
3 2 4 3 5
```
### 输出
```
YES
1 2 3
1 3
1 2 3 4
1 3 4
1 1 2 3 4
```

### 算法分类
贪心

### 综合分析与结论
所有题解均采用贪心策略解决该问题。思路要点在于先找出石子数量最少的堆，设其数量为 $mina$ （不同题解命名略有不同），然后将每堆的前 $mina + 1$ 个石子染成一种颜色（通常为颜色1），后续石子按顺序染成 $2$ 至 $k$ 颜色。判断无解的条件为石子数量最多的堆与最少的堆数量差大于 $k$ 。各题解在实现细节上略有不同，如输入方式、判断无解的写法以及染色具体实现等。

### 所选的题解
 - **作者：yu__xuan (5星)**
    - **关键亮点**：思路清晰，代码简洁明了，直接在主函数中实现整个逻辑，通过简单的循环和条件判断完成输入、判断和输出。
    - **重点代码**：
```cpp
int main() {
    read(n),read(k);
    int minn=0x7fffffff,maxx=0;
    for(int i=1;i<=n;++i) {
        read(a[i]);
        if(a[i]>maxx) maxx=a[i];
        if(a[i]<minn) minn=a[i];
    }
    if(maxx-minn>k) {
        puts("NO");
        return 0;
    }
    puts("YES");
    for(int i=1;i<=n;++i) {
        for(int j=1;j<=a[i];++j) {
            if(j<=minn+1) printf("1 ");
            else printf("%d ",j-minn);
        }
        puts("");
    }
    return 0;
}
```
    - **核心实现思想**：先读入 $n$ 和 $k$，找出 $a[i]$ 中的最大值 $maxx$ 和最小值 $minn$，判断 $maxx - minn > k$ 时输出 “NO” 并结束程序；否则输出 “YES”，然后按规则染色输出每堆石子颜色。

 - **作者：damage (5星)**
    - **关键亮点**：代码结构清晰，将染色过程封装成函数 `paint`，逻辑更模块化，便于理解和维护。
    - **重点代码**：
```cpp
void paint(int num,int id)
{
    for(register int i=1;i<=n;++i)
    {
        times=num;
        for(;used[i]<a[i]&&times;++used[i],--times) res[i][used[i]+1]=id;
    }
    return ;
}
int main()
{
    scanf("%d%d",&n,&k);
    for(register int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
        if(a[i]<mina) mina=a[i];
    }
    paint(mina+1,1);
    for(register int i=2;i<=k;++i) paint(1,i);
    for(register int i=1;i<=n;++i)
    {
        if(used[i]!=a[i])
        {
            printf("NO\n");
            return 0;
        }
    }
    printf("YES\n");
    for(register int i=1;i<=n;++i)
    {
        for(register int j=1;j<=a[i];++j) printf("%d ",res[i][j]);
        putchar('\n');
    }
    return 0;
}
```
    - **核心实现思想**：定义 `paint` 函数实现染色，`num` 表示要染的石子数量，`id` 表示颜色。主函数中先读入数据并找到最小值 `mina`，调用 `paint` 函数先将前 `mina + 1` 个石子染成颜色1，再依次将剩余石子染成其他颜色，最后检查是否所有石子都被染色，按要求输出结果。

 - **作者：Purple_Circle (4星)**
    - **关键亮点**：代码简洁，使用 `bits/stdc++.h` 头文件简化了代码编写，在染色输出部分使用简洁的三元运算符。
    - **重点代码**：
```cpp
int main() {
    n=rd,k=rd;
    for(int i=1;i<=n;i++) {
        a[i]=rd;
        maxn=max(maxn,a[i]);
        minn=min(minn,a[i]);
    }
    if(maxn-minn>k) {
        cout<<"NO\n";
        return 0;
    }
    cout<<"YES\n";
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=a[i];j++){
            cout<<(j-1<=minn?1:j-minn)<<" ";
        }
        endl(cout);
    }
    return 0;
}
```
    - **核心实现思想**：读入数据并找到最大最小值，判断无解情况，输出 “NO” 或 “YES”，通过循环和三元运算符按规则染色输出每堆石子颜色。

### 最优关键思路或技巧
采用贪心策略，优先将每堆石子中尽量多的部分染成同一种颜色，以满足题目中对不同堆间相同颜色石子数量差的限制。通过找出石子数量最少的堆，以此为基准进行染色，简化了问题求解过程。

### 可拓展之处
此类题目属于贪心策略在分配问题上的应用。类似套路是先确定一个基准值（如本题中的最少石子堆数量），然后基于这个基准值进行后续操作，保证每一步决策都是当前最优，从而达到全局最优。同类型题目通常会在条件限制和数据规模上有所变化，但核心贪心思路不变。

### 洛谷相似题目推荐
 - [P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094)
 - [P1199 [NOIP2010 普及组] 三国游戏](https://www.luogu.com.cn/problem/P1199)
 - [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)

### 个人心得摘录与总结
暂无。 

---
处理用时：52.59秒