# 题目信息

# Gold Transfer

## 题目描述

You are given a rooted tree. Each vertex contains $ a_i $ tons of gold, which costs $ c_i $ per one ton. Initially, the tree consists only a root numbered $ 0 $ with $ a_0 $ tons of gold and price $ c_0 $ per ton.

There are $ q $ queries. Each query has one of two types:

1. Add vertex $ i $ (where $ i $ is an index of query) as a son to some vertex $ p_i $ ; vertex $ i $ will have $ a_i $ tons of gold with $ c_i $ per ton. It's guaranteed that $ c_i > c_{p_i} $ .
2. For a given vertex $ v_i $ consider the simple path from $ v_i $ to the root. We need to purchase $ w_i $ tons of gold from vertices on this path, spending the minimum amount of money. If there isn't enough gold on the path, we buy all we can.

If we buy $ x $ tons of gold in some vertex $ v $ the remaining amount of gold in it decreases by $ x $ (of course, we can't buy more gold that vertex has at the moment). For each query of the second type, calculate the resulting amount of gold we bought and the amount of money we should spend.

Note that you should solve the problem in online mode. It means that you can't read the whole input at once. You can read each query only after writing the answer for the last query, so don't forget to flush output after printing answers. You can use functions like fflush(stdout) in C++ and BufferedWriter.flush in Java or similar after each writing in your program. In standard (if you don't tweak I/O), endl flushes cout in C++ and System.out.println in Java (or println in Kotlin) makes automatic flush as well.

## 说明/提示

Explanation of the sample:

At the first query, the tree consist of root, so we purchase $ 2 $ tons of gold and pay $ 2 \cdot 2 = 4 $ . $ 3 $ tons remain in the root.

At the second query, we add vertex $ 2 $ as a son of vertex $ 0 $ . Vertex $ 2 $ now has $ 3 $ tons of gold with price $ 4 $ per one ton.

At the third query, a path from $ 2 $ to $ 0 $ consists of only vertices $ 0 $ and $ 2 $ and since $ c_0 < c_2 $ we buy $ 3 $ remaining tons of gold in vertex $ 0 $ and $ 1 $ ton in vertex $ 2 $ . So we bought $ 3 + 1 = 4 $ tons and paid $ 3 \cdot 2 + 1 \cdot 4 = 10 $ . Now, in vertex $ 0 $ no gold left and $ 2 $ tons of gold remain in vertex $ 2 $ .

At the fourth query, we add vertex $ 4 $ as a son of vertex $ 0 $ . Vertex $ 4 $ now has $ 1 $ ton of gold with price $ 3 $ .

At the fifth query, a path from $ 4 $ to $ 0 $ consists of only vertices $ 0 $ and $ 4 $ . But since no gold left in vertex $ 0 $ and only $ 1 $ ton is in vertex $ 4 $ , we buy $ 1 $ ton of gold in vertex $ 4 $ and spend $ 1 \cdot 3 = 3 $ . Now, in vertex $ 4 $ no gold left.

## 样例 #1

### 输入

```
5 5 2
2 0 2
1 0 3 4
2 2 4
1 0 1 3
2 4 2```

### 输出

```
2 4
4 10
1 3```

# AI分析结果

### 题目内容中文重写
# 黄金转移

## 题目描述
给定一棵有根树。每个顶点包含 $a_i$ 吨黄金，每吨黄金的成本为 $c_i$。初始时，树仅由编号为 $0$ 的根节点组成，该根节点有 $a_0$ 吨黄金，每吨价格为 $c_0$。

有 $q$ 个查询。每个查询有以下两种类型之一：
1. 将顶点 $i$（其中 $i$ 是查询的索引）作为某个顶点 $p_i$ 的子节点添加；顶点 $i$ 将有 $a_i$ 吨黄金，每吨价格为 $c_i$。保证 $c_i > c_{p_i}$。
2. 对于给定的顶点 $v_i$，考虑从 $v_i$ 到根的简单路径。我们需要从这条路径上的顶点购买 $w_i$ 吨黄金，花费最少的钱。如果路径上没有足够的黄金，我们就购买我们能买到的所有黄金。

如果我们在某个顶点 $v$ 购买了 $x$ 吨黄金，该顶点剩余的黄金量将减少 $x$（当然，我们不能购买超过该顶点当前拥有的黄金量）。对于每个第二种类型的查询，计算我们购买的黄金量和我们应该花费的钱数。

请注意，你应该以在线模式解决这个问题。这意味着你不能一次性读取整个输入。你只能在为最后一个查询写出答案后读取每个查询，所以在打印答案后不要忘记刷新输出。你可以在 C++ 中使用 `fflush(stdout)` 函数，在 Java 中使用 `BufferedWriter.flush` 或类似的函数在每次写入程序后刷新输出。在标准模式下（如果你不调整输入输出），在 C++ 中 `endl` 会刷新 `cout`，在 Java 中 `System.out.println`（或在 Kotlin 中 `println`）也会自动刷新输出。

## 说明/提示
示例解释：
在第一个查询中，树仅由根节点组成，所以我们购买 $2$ 吨黄金并支付 $2 \cdot 2 = 4$。根节点中还剩下 $3$ 吨黄金。
在第二个查询中，我们将顶点 $2$ 作为顶点 $0$ 的子节点添加。顶点 $2$ 现在有 $3$ 吨黄金，每吨价格为 $4$。
在第三个查询中，从 $2$ 到 $0$ 的路径仅由顶点 $0$ 和 $2$ 组成，由于 $c_0 < c_2$，我们购买顶点 $0$ 中剩余的 $3$ 吨黄金和顶点 $2$ 中的 $1$ 吨黄金。所以我们购买了 $3 + 1 = 4$ 吨黄金，支付了 $3 \cdot 2 + 1 \cdot 4 = 10$。现在，顶点 $0$ 中没有黄金了，顶点 $2$ 中还剩下 $2$ 吨黄金。
在第四个查询中，我们将顶点 $4$ 作为顶点 $0$ 的子节点添加。顶点 $4$ 现在有 $1$ 吨黄金，每吨价格为 $3$。
在第五个查询中，从 $4$ 到 $0$ 的路径仅由顶点 $0$ 和 $4$ 组成。但是由于顶点 $0$ 中没有黄金，顶点 $4$ 中只有 $1$ 吨黄金，我们在顶点 $4$ 中购买 $1$ 吨黄金，花费 $1 \cdot 3 = 3$。现在，顶点 $4$ 中没有黄金了。

## 样例 #1
### 输入
```
5 5 2
2 0 2
1 0 3 4
2 2 4
1 0 1 3
2 4 2
```
### 输出
```
2 4
4 10
1 3
```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路都是利用题目中 $c_i > c_{p_i}$ 的条件，采用贪心策略，优先购买靠近根节点的黄金。不同题解的主要区别在于实现方式，部分题解使用了倍增算法来快速找到路径上最靠上的非空节点，以优化查找效率，而部分题解采用递归的方式从根节点开始处理。

### 所选题解
- 忘怀星的题解（4星）
  - 关键亮点：思路清晰，详细解释了贪心策略和倍增算法的使用，代码实现简洁明了。
- wfc284的题解（4星）
  - 关键亮点：对时间复杂度的分析较为清晰，代码结构合理。
- wrzSama的题解（4星）
  - 关键亮点：对题意和思路的阐述详细，代码中包含了输入输出的优化。

### 重点代码
#### 忘怀星的题解
```cpp
int get(int u)
{
    for(int i = 19;i >= 0;i --) if(a[fa[u][i]]) u = fa[u][i];
    return u;
}
signed main()
{
    n = read(),a[1] = read(),c[1] = read();
    for(int i = 2;i <= 1+n;i ++) {
        int op = read();
        if(op == 1) {
            fa[i][0] = read()+1,a[i] = read(),c[i] = read();
            for(int j = 1;j < 20;j ++) fa[i][j] = fa[fa[i][j-1]][j-1];
        } else {
            int v = read()+1,tmp , w = read(),ans = 0;
            tmp = w;while(a[v] && w) {
                int x = get(v);
                if(w > a[x]) {
                    w -= a[x],ans += a[x]*c[x];
                    a[x] = 0;
                } else {
                    a[x] -= w,ans += w*c[x];
                    w = 0;
                }
            }
            printf("%lld %lld\n",tmp-w,ans);
        }
        fflush(stdout);
    }
    return 0;
}
```
核心实现思想：`get` 函数使用倍增算法找到路径上最靠上的非空节点。在处理查询时，不断调用 `get` 函数，根据剩余黄金量和需要购买的黄金量的关系进行处理。

#### wfc284的题解
```cpp
int get(int u) {
    for(re int k = 19; k >= 0; --k)
        if(a[anc[u][k]]) u = anc[u][k];
    return u;
}

signed main() {
    cin >> q >> a[1] >> c[1];
    for(re int i = 2, opt, p, u, w; i <= q+1; ++i) {
        scanf("%lld", &opt);
        if(opt == 1) {
            scanf("%lld%lld%lld", &p, &a[i], &c[i]), ++p;
            anc[i][0] = p;
            for(re int c = 1; c <= 19; ++c) anc[i][c] = anc[anc[i][c-1]][c-1];
        }
        else {
            scanf("%lld%lld", &u, &w), ++u;
            int tot = 0, tot_price = 0;
            while(a[u] && w) {
                int x = get(u);
                if(a[x] < w) {
                    tot += a[x], tot_price += a[x] * c[x];
                    w -= a[x], a[x] = 0;
                }
                else {
                    tot += w, tot_price += w * c[x];
                    a[x] -= w;
                    break;
                }
            }
            printf("%lld %lld\n", tot, tot_price);
            fflush(stdout);
        }
    }
    return 0;
}
```
核心实现思想：`get` 函数同样使用倍增算法找到最靠上的非空节点。在处理查询时，根据节点的黄金量和需要购买的黄金量的大小关系更新购买量和花费。

#### wrzSama的题解
```cpp
inline int find(int x,int len)
{
    for(int i=19;i>=0;--i)
    {
        if(len&(1<<i))
        {
            len^=(1<<i);
            x=fa[x][i];
        }
    }
    return x;
}
int main()
{
    q=read();
    a[1]=read();
    c[1]=read();
    for(int i=2;i<=q+1;++i)
    {
        int op=read();
        if(op==1)
        {
            fa[i][0]=read()+1;
            d[i]=d[fa[i][0]]+1;
            for(int j=1;j<20;++j) fa[i][j]=fa[fa[i][j-1]][j-1];
            a[i]=read();
            c[i]=read();
        }
        else
        {
            int v=read()+1,w=read(),x=v,y=w;
            for(int j=19;j>=0;--j) if(a[fa[x][j]]) x=fa[x][j];
            int tmp=min(w,a[x]);
            ll ans=tmp*c[x];
            w-=tmp;
            a[x]-=tmp;
            while(w&&x!=v)
            {
                x=find(v,d[v]-d[x]-1);
                tmp=min(w,a[x]);
                w-=tmp;
                a[x]-=tmp;
                ans+=tmp*c[x]; 
            }
            write(y-w);
            putchar(' ');
            write(ans);
            cout<<'\n';
            fflush(stdout);
        }
    }
    return 0;
}
```
核心实现思想：`find` 函数用于根据深度差找到指定节点。在处理查询时，先找到最靠上的非空节点，然后根据剩余黄金量和需要购买的黄金量的关系进行处理，不断更新节点和黄金量。

### 最优关键思路或技巧
- 利用 $c_i > c_{p_i}$ 的条件，采用贪心策略，优先购买靠近根节点的黄金。
- 使用倍增算法快速找到路径上最靠上的非空节点，将查找复杂度从 $O(n)$ 优化到 $O(\log n)$。

### 可拓展之处
同类型题或类似算法套路：
- 树上的其他贪心问题，如树上的资源分配问题，可根据节点的某些属性（如权值、优先级等）进行贪心选择。
- 其他需要在线处理的问题，可借鉴本题的在线处理思路，在处理每个查询后再读取下一个查询。

### 推荐洛谷题目
- P1090 [NOIP2004 提高组] 合并果子
- P1223 排队接水
- P2240 【深基12.例1】部分背包问题

### 个人心得
题解中未包含个人心得。

---
处理用时：68.73秒