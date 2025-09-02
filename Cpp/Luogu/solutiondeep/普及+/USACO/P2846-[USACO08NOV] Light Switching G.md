# 题目信息

# [USACO08NOV] Light Switching G

## 题目描述

Farmer John tries to keep the cows sharp by letting them play with intellectual toys. One of the larger toys is the lights in the barn. Each of the $N (2 \le N \le 10^5)$ cow stalls conveniently numbered $1\ldots N$ has a colorful light above it.

At the beginning of the evening, all the lights are off. The cows control the lights with a set of N pushbutton switches that toggle the lights; pushing switch i changes the state of light i from off to on or from on to off.

The cows read and execute a list of $M(1\le M \le 10^5)$ operations expressed as one of two integers ( $0 \le$ operation $\le 1$ ).

The first kind of operation (denoted by a $0$ command) includes two subsequent integers $S_i$ and $E_i (1 \le S_i \le E_i \le N)$ that indicate a starting switch and ending switch. They execute the operation by pushing each pushbutton from $S_i$ through $E_i$ inclusive exactly once.

The second kind of operation (denoted by a $1$ command) asks the cows to count how many lights are on in the range given by two integers $S_i$ and $E_i (1 \le S_i \le E_i \le N)$ which specify the inclusive range in which the cows should count the number of lights that are on.

Help FJ ensure the cows are getting the correct answer by processing the list and producing the proper counts.

农夫约翰试图让奶牛玩智力玩具来保持它们的敏锐。谷仓里的灯是较大的玩具之一。$N (2 \le N \le 10^5)$ 个牛栏编号为 $1 \ldots N$，每个牛栏上面都有一盏灯。起初所有的灯都关着。

共有 $M$ 次操作，分为两种。
1. 指定一个区间 $[S_i,E_i]$，然后改变编号在这个区间内的灯的状态（把开着的灯关上，关着的灯打开）；
2. 指定一个区间 $[S_i,E_i]$，要求你输出这个区间内有多少盏灯是打开的。







## 说明/提示

| 数据点编号 | $N$ | $M$ |
| :----------: | :----------: | :----------: |
| $1\sim 2$ | $\le 100$ | $\le 100$ |
| $3\sim 4$ | $\le 1000$ | $\le 1000$ |
| $5\sim 6$ | $\le 10000$ | $\le 10000$ |
| $7\sim 8$ | $\le 10^5$ | $\le 100$ |
| $9\sim 10$ | $\le 100$ | $\le 10^5$ |
| $11\sim 12$ | $\le 1000$ | $\le 10^5$ |
| $13\sim 14$ | $\le 10^5$ | $\le 1000$ |
| $15\sim 16$ | $\le 10000$ | $\le 10000$ |
| $17\sim 18$ | $\le 10$ | $\le 10^5$ |
| $19\sim 20$ | $\le 2000$ | $\le 10^6$ |


## 样例 #1

### 输入

```
4 5
0 1 2
0 2 4
1 2 3
0 2 4
1 1 4```

### 输出

```
1
2```

# AI分析结果

### 综合分析与结论
本题主要涉及区间修改和区间查询操作，数据范围较大，需采用合适的数据结构和算法来避免超时。题解主要采用了模拟（纯暴力）、线段树、树状数组、珂朵莉树、分块等方法。

模拟（纯暴力）方法简单直接，但时间复杂度高，在数据量较大时会超时；线段树是解决此类问题的常用方法，通过懒标记优化区间修改操作，能有效降低时间复杂度；树状数组结合差分思想，可在一定程度上解决问题；珂朵莉树适用于数据随机的情况；分块则是将区间分成若干块，对整块和不完整块分别处理。

### 所选题解
- **作者：Liu_zj（5星）**
    - **关键亮点**：思路清晰，详细阐述了异或操作在本题中的应用，对线段树的各个操作（如更新、标记下传等）解释到位，代码实现简洁明了，还给出了双倍经验题目。
    - **个人心得**：无

### 重点代码
```cpp
void update(int now)
{
    sum[now]=sum[now<<1]+sum[now<<1|1];//大区间的亮灯和等于左右区间的亮灯和的和。。。
}
void pushdown(int now,int l,int r)//标记下传
{
    int mid=(l+r)>>1;
    if(lz[now]==1)
    {
        lz[now<<1]^=1;//lz的改变用异或
        lz[now<<1|1]^=1;
        sum[now<<1]=(mid-l+1-sum[now<<1]);//区间灯数-亮灯数
        sum[now<<1|1]=(r-mid-sum[now<<1|1]);
        lz[now]=0;
    }
}
void change(int now,int l,int r,int lgo,int rgo)//区间修改
{
    if(l>=lgo&&r<=rgo)//如果当前区间（l,r）在修改区间（lgo,rgo）中
    {
        lz[now]^=1;//lz异或
        sum[now]=(r-l+1-sum[now]);
        return ;
    }
    int mid=(l+r)>>1;
    pushdown(now,l,r);//别忘了标记下传
    if(lgo<=mid)
        change(now<<1,l,mid,lgo,rgo);
    if(rgo>mid)
        change(now<<1|1,mid+1,r,lgo,rgo);
    update(now);//修改后更新
}
long long find(int now,int l,int r,int lgo,int rgo)//区间查询
{
    long long ans=0;
    if(l>=lgo&&r<=rgo)//如果当前区间（l,r）在查询区间（lgo,rgo）中
        return sum[now];//返回值
    int mid=(l+r)>>1;
    pushdown(now,l,r);//标记下传double
    if(lgo<=mid)
        ans+=find(now<<1,l,mid,lgo,rgo);
    if(rgo>mid)
        ans+=find(now<<1|1,mid+1,r,lgo,rgo);
    return ans;
}
```
**核心实现思想**：
- `update` 函数：用于更新父节点的亮灯总数，即左右子节点亮灯数之和。
- `pushdown` 函数：标记下传操作，将懒标记传递给子节点，并更新子节点的亮灯数。
- `change` 函数：区间修改操作，若当前区间完全包含在修改区间内，则直接更新懒标记和亮灯数；否则，先下传标记，再递归修改左右子区间，最后更新父节点。
- `find` 函数：区间查询操作，若当前区间完全包含在查询区间内，则直接返回亮灯数；否则，先下传标记，再递归查询左右子区间，最后返回查询结果之和。

### 最优关键思路或技巧
- **异或操作**：利用异或操作实现灯状态的切换和懒标记的更新，简洁高效。
- **线段树懒标记**：通过懒标记优化区间修改操作，避免不必要的更新，降低时间复杂度。

### 可拓展之处
同类型题或类似算法套路：
- 区间加减、乘除等操作的线段树问题，可根据具体操作修改懒标记和更新逻辑。
- 树状数组结合差分思想可解决更多区间修改和单点查询问题。
- 珂朵莉树适用于数据随机的区间操作问题。
- 分块算法可用于解决一些复杂的区间操作问题，可根据具体问题调整块的大小和处理方式。

### 推荐题目
- [P3372 【模板】线段树 1](https://www.luogu.com.cn/problem/P3372)
- [P3870 [TJOI2009]开关](https://www.luogu.com.cn/problem/P3870)
- [P2574 XOR的艺术](https://www.luogu.com.cn/problem/P2574)

### 个人心得摘录与总结
- **作者：mxr已死**：提到树状数组理解难、支持操作少，线段树码量大、调试困难，而分块虽然复杂度高，但能维护的东西多，且有时比分块跑的快，强调了分块算法的优势。
总结：不同算法有各自的优缺点，在实际应用中需根据问题特点选择合适的算法。 

---
处理用时：42.75秒