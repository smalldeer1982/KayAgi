# 题目信息

# Pinkie Pie Eats Patty-cakes

## 题目描述

Pinkie Pie has bought a bag of patty-cakes with different fillings! But it appeared that not all patty-cakes differ from one another with filling. In other words, the bag contains some patty-cakes with the same filling.

Pinkie Pie eats the patty-cakes one-by-one. She likes having fun so she decided not to simply eat the patty-cakes but to try not to eat the patty-cakes with the same filling way too often. To achieve this she wants the minimum distance between the eaten with the same filling to be the largest possible. Herein Pinkie Pie called the distance between two patty-cakes the number of eaten patty-cakes strictly between them.

Pinkie Pie can eat the patty-cakes in any order. She is impatient about eating all the patty-cakes up so she asks you to help her to count the greatest minimum distance between the eaten patty-cakes with the same filling amongst all possible orders of eating!

Pinkie Pie is going to buy more bags of patty-cakes so she asks you to solve this problem for several bags!

## 说明/提示

For the first bag Pinkie Pie can eat the patty-cakes in the following order (by fillings): $ 1 $ , $ 6 $ , $ 4 $ , $ 7 $ , $ 1 $ , $ 6 $ , $ 4 $ (in this way, the minimum distance is equal to $ 3 $ ).

For the second bag Pinkie Pie can eat the patty-cakes in the following order (by fillings): $ 1 $ , $ 4 $ , $ 6 $ , $ 7 $ , $ 4 $ , $ 1 $ , $ 6 $ , $ 4 $ (in this way, the minimum distance is equal to $ 2 $ ).

## 样例 #1

### 输入

```
4
7
1 7 1 6 4 4 6
8
1 1 4 6 4 6 4 7
3
3 3 3
6
2 5 2 3 1 4```

### 输出

```
3
2
0
4```

# AI分析结果

### 题目中文重写
# Pinkie Pie 吃小蛋糕

## 题目描述
Pinkie Pie 买了一袋不同馅料的小蛋糕！但结果发现，并非所有小蛋糕的馅料都彼此不同。换句话说，袋子里有一些馅料相同的小蛋糕。

Pinkie Pie 一个接一个地吃小蛋糕。她喜欢找乐子，所以她决定不简单地吃小蛋糕，而是尽量不频繁地吃馅料相同的小蛋糕。为了实现这一点，她希望吃的馅料相同的小蛋糕之间的最小距离尽可能大。在这里，Pinkie Pie 把两个小蛋糕之间的距离定义为它们之间严格吃掉的小蛋糕的数量。

Pinkie Pie 可以按任何顺序吃小蛋糕。她迫不及待地想把所有小蛋糕都吃完，所以她请你帮她计算在所有可能的吃法中，吃的馅料相同的小蛋糕之间的最大最小距离！

Pinkie Pie 打算再买几袋小蛋糕，所以她请你为几袋小蛋糕解决这个问题！

## 说明/提示
对于第一袋小蛋糕，Pinkie Pie 可以按以下顺序（按馅料）吃小蛋糕：$ 1 $ , $ 6 $ , $ 4 $ , $ 7 $ , $ 1 $ , $ 6 $ , $ 4 $（这样，最小距离等于 $ 3 $）。

对于第二袋小蛋糕，Pinkie Pie 可以按以下顺序（按馅料）吃小蛋糕：$ 1 $ , $ 4 $ , $ 6 $ , $ 7 $ , $ 4 $ , $ 1 $ , $ 6 $ , $ 4 $（这样，最小距离等于 $ 2 $）。

## 样例 #1

### 输入
```
4
7
1 7 1 6 4 4 6
8
1 1 4 6 4 6 4 7
3
3 3 3
6
2 5 2 3 1 4
```

### 输出
```
3
2
0
4
```

### 算法分类
数学

### 综合分析与结论
这些题解主要围绕如何计算吃的馅料相同的小蛋糕之间的最大最小距离展开，主要有两种思路。一种是数学方法，通过统计出现次数最多的数的次数和个数，利用公式计算答案；另一种是二分答案结合贪心的方法，通过不断二分距离，用贪心策略判断该距离是否可行。

数学方法的思路清晰，直接通过公式计算，时间复杂度低，为 $O(\sum n)$；二分答案结合贪心的方法思路巧妙，但实现相对复杂，时间复杂度为 $O(n\log^2 n)$。

### 所选题解
- **奇米（4星）**
    - **关键亮点**：思路清晰，直接给出数学公式计算答案，代码简洁。
- **huayucaiji（4星）**
    - **关键亮点**：提供了二分答案的思路，详细分析了错误的贪心策略并给出正确的贪心思路，有具体的代码实现。
- **RyexAwl（4星）**
    - **关键亮点**：同样采用二分答案结合贪心的方法，对贪心算法的错误原因进行了理性分析，并使用调整法证明了正确贪心算法的正确性。

### 重点代码
#### 奇米的数学方法
```cpp
int main()
{
    io.read(Q);
    for (;Q--;)
    {
        io.read(n);
        int MX=0,S=0;
        For(i,1,n) 
        {
            io.read(a[i]);
            MX=max(MX,++b[a[i]]);
        }
        For(i,1,n) 
        {
            S+=(b[i]==MX);
            b[i]=0;
        }
        io.write((n-MX*S)/(MX-1)+S-1);
        puts("");
    }
}
```
**核心实现思想**：先统计出出现次数最多的数的次数 $MX$ 和出现次数为 $MX$ 的数的个数 $S$，然后根据公式 $(n - MX * S) / (MX - 1) + S - 1$ 计算答案。

#### huayucaiji 的二分答案结合贪心方法
```cpp
bool check(int x) {
    fill(b+1,b+n+1,0);
    priority_queue<pair<int,int> > q;
    
    for(int i=1;i<=n;i++) {
        if(cnt[i])
            q.push(make_pair(cnt[i],i));
    }
    
    for(int i=1;i<=n;i++) {
        if(i>x+1) {
            if(cnt[b[i-x-1]])
                q.push(make_pair(cnt[b[i-x-1]],b[i-x-1]));//把重新“合法”的这个数加回堆中。
        }
        if(q.empty()) {
            return 0;//此时无解
        }
        
        pair<int,int> pr=q.top();
        q.pop();
        cnt[pr.second]--;//剩余出现次数减1
        b[i]=pr.second;
    }
    return 1;
}

void clear() {
    fill(cnt+1,cnt+n+1,0);
    for(int i=1;i<=n;i++) {
        cnt[a[i]]++;
    }
}

signed main() {
    int t=read();
    
    while(t--) {
        n=read();
        
        for(int i=1;i<=n;i++) {
            a[i]=read();
            cnt[a[i]]++;
        }
        
        int l=0,r=n-2;
        
        while(l+1<r) {
            int mid=(l+r)>>1;
            clear();//恢复cnt数组
            
            if(check(mid)) {
                l=mid;
            }
            else {
                r=mid;
            }
        }
        clear();//恢复cnt数组
        if(check(r)) {
            printf("%d\n",r);
        }
        else {
            printf("%d\n",l);
        }
        fill(cnt+1,cnt+n+1,0);
    }
    return 0;
}
```
**核心实现思想**：二分答案 $x$，对于每个 $x$，用优先队列维护每个数的剩余出现次数，从左到右依次填充序列，若某个位置没有可填充的数则该 $x$ 不可行。

### 最优关键思路或技巧
- 数学方法中，通过分析问题的本质，将出现次数最多的数合并成一块，利用公式直接计算答案，简单高效。
- 二分答案结合贪心的方法中，通过不断二分距离，用贪心策略判断该距离是否可行，巧妙地解决了问题。

### 拓展思路
同类型题或类似算法套路：
- 对于求最大值最小或最小值最大的问题，可以考虑二分答案的方法。
- 对于一些可以通过构造来解决的问题，可以先分析问题的本质，找到最优的构造方式。

### 推荐洛谷题目
- [P1824 进击的奶牛](https://www.luogu.com.cn/problem/P1824)
- [P2678 跳石头](https://www.luogu.com.cn/problem/P2678)
- [P3853 [TJOI2007]路标设置](https://www.luogu.com.cn/problem/P3853)

### 个人心得摘录与总结
- **RyexAwl**：在分析贪心算法错误原因时，通过具体的例子和理性分析，指出了错误贪心算法的问题所在，提醒我们在使用贪心算法时要考虑操作对后续的影响。
- **KSToki**：比赛时忘了特判，导致 system test 爆了，提醒我们在做题时要注意边界情况的处理。

---
处理用时：47.14秒