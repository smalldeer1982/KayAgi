# 题目信息

# Xenia and Colorful Gems

## 题目描述

Xenia is a girl being born a noble. Due to the inflexibility and harshness of her family, Xenia has to find some ways to amuse herself.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1336B/f1c62b7a1a43a6f38201f883bcf9e45e175e9eca.png)Recently Xenia has bought $ n_r $ red gems, $ n_g $ green gems and $ n_b $ blue gems. Each of the gems has a weight.

Now, she is going to pick three gems.

Xenia loves colorful things, so she will pick exactly one gem of each color.

Xenia loves balance, so she will try to pick gems with little difference in weight.

Specifically, supposing the weights of the picked gems are $ x $ , $ y $ and $ z $ , Xenia wants to find the minimum value of $ (x-y)^2+(y-z)^2+(z-x)^2 $ . As her dear friend, can you help her?

## 说明/提示

In the first test case, Xenia has the following gems:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1336B/2487fca86bd28d2bebb967f33db75171edb995c7.png)

If she picks the red gem with weight $ 7 $ , the green gem with weight $ 6 $ , and the blue gem with weight $ 4 $ , she will achieve the most balanced selection with $ (x-y)^2+(y-z)^2+(z-x)^2=(7-6)^2+(6-4)^2+(4-7)^2=14 $ .

## 样例 #1

### 输入

```
5
2 2 3
7 8
6 3
3 1 4
1 1 1
1
1
1000000000
2 2 2
1 2
5 4
6 7
2 2 2
1 2
3 4
6 7
3 4 1
3 2 1
7 3 3 4
6```

### 输出

```
14
1999999996000000002
24
24
14```

# AI分析结果

### 题目翻译
Xenia 是一个出身贵族的女孩。由于家庭的刻板和严苛，Xenia 不得不寻找一些自娱自乐的方式。

最近，Xenia 买了 $n_r$ 颗红色宝石、$n_g$ 颗绿色宝石和 $n_b$ 颗蓝色宝石。每颗宝石都有一个重量。

现在，她打算挑选三颗宝石。

Xenia 喜欢色彩丰富的东西，所以她会恰好每种颜色各选一颗宝石。

Xenia 喜欢平衡，所以她会尽量挑选重量差异小的宝石。

具体来说，假设挑选的宝石重量分别为 $x$、$y$ 和 $z$，Xenia 想要找到 $(x - y)^2 + (y - z)^2 + (z - x)^2$ 的最小值。作为她亲爱的朋友，你能帮助她吗？

### 算法分类
枚举

### 综合分析与结论
这些题解的核心思路都是要让 $(x - y)^2 + (y - z)^2 + (z - x)^2$ 的值尽可能小，$x$、$y$、$z$ 三个值就要尽可能接近。主要通过枚举其中一个数，再从另外两个数组中找到与之最接近的数来计算答案。各题解的差异主要体现在实现方式上，如使用二分查找（`lower_bound`、`upper_bound`）或双指针来查找最接近的数，以及枚举的具体细节。

### 所选题解
- **作者：huayucaiji (赞：8)  4星**
    - **关键亮点**：思路清晰，详细解释了为什么枚举 $y$ 以及如何通过枚举 $x$、$y$、$z$ 的顺序来找到最优解，代码实现使用了 `lower_bound` 和 `upper_bound` 函数，简洁明了。
- **作者：Andrewzdm (赞：6)  4星**
    - **关键亮点**：同样清晰地阐述了思路，使用双指针的方法来查找最接近的数，时间复杂度分析准确，代码结构清晰，将枚举和计算过程封装到函数中，提高了代码的可读性。
- **作者：wsyhb (赞：6)  4星**
    - **关键亮点**：对枚举 $y$ 的原因进行了数学证明，逻辑严谨。代码使用双指针实现，常数较小，且代码注释详细，便于理解。

### 重点代码
#### huayucaiji 的代码
```cpp
int calc(int x,int y,int z) {
    return (x-y)*(x-y)+(y-z)*(y-z)+(x-z)*(x-z);
}

signed main() {
    int t=read();
    while(t--) {
        for(int i=0;i<3;i++) {
            n[i]=read();
        }
        for(int i=0;i<3;i++) {
            for(int j=1;j<=n[i];j++) {
                c[i][j]=read();
            }
            sort(c[i],c[i]+n[i]+1);
        }
        int ans=inf;
        for(int i=0;i<3;i++) {
            for(int j=0;j<3;j++) {
                for(int k=0;k<3;k++) {
                    if(i!=j&&j!=k&&i!=k) {
                        for(int q=1;q<=n[i];q++) {
                            int p1=lower_bound(c[j],c[j]+n[j]+1,c[i][q])-c[j];
                            int p2=upper_bound(c[k],c[k]+n[k]+1,c[i][q])-c[k];
                            if(p1!=n[j]+1&&p2!=1) {
                                p2--;
                                ans=min(ans,calc(c[i][q],c[j][p1],c[k][p2]));
                            }
                        }
                    }
                }
            }
        }
        printf("%lld\n",ans);
    }
    return 0;
}
```
**核心实现思想**：先对三个数组进行排序，然后枚举 $x$、$y$、$z$ 的顺序，对于每个枚举到的数，使用 `lower_bound` 和 `upper_bound` 函数找到另外两个数组中最接近的数，计算 $(x - y)^2 + (y - z)^2 + (z - x)^2$ 的值并更新答案。

#### Andrewzdm 的代码
```cpp
long long calc(long long x, long long y, long long z)
{
    return (x-y)*(x-y)+(y-z)*(y-z)+(x-z)*(x-z);
}

void solve(long long *x, long long *y, long long *z, int nx, int ny, int nz)
{
    int p1 = 0, p2 = 0;
    for(int i = 1; i <= nx; i++)
    {
        while(p1 <= ny && y[p1] <= x[i]) p1++;  //找最接近的较小值
        while(p2 <= nz && z[p2] < x[i]) p2++;  //找最接近的较大值
        if(p1 - 1 != 0 && p2 != nz + 1)  //较小值和较大值都能找到
            ans = min(ans, calc(x[i], y[p1 - 1], z[p2]));
    }
    return;
}

void work()
{
    ans = 0x7fffffffffffffff;
    int nr, ng, nb;
    scanf("%d%d%d", &nr, &ng, &nb);
    for(int i = 1; i <= nr; i++) scanf("%lld", r + i);
    for(int i = 1; i <= ng; i++) scanf("%lld", g + i);
    for(int i = 1; i <= nb; i++) scanf("%lld", b + i);
    sort(r + 1, r + nr + 1);
    sort(g + 1, g + ng + 1);
    sort(b + 1, b + nb + 1);
    solve(r, g, b, nr, ng, nb);
    solve(r, b, g, nr, nb, ng);
    solve(g, r, b, ng, nr, nb);
    solve(g, b, r, ng, nb, nr);
    solve(b, r, g, nb, nr, ng);
    solve(b, g, r, nb, ng, nr);
    printf("%lld\n", ans);
    return;
}
```
**核心实现思想**：先对三个数组进行排序，然后将枚举和计算过程封装到 `solve` 函数中，使用双指针的方法找到最接近的较小值和较大值，计算 $(x - y)^2 + (y - z)^2 + (z - x)^2$ 的值并更新答案。

#### wsyhb 的代码
```cpp
inline long long get_ans(int a[],int na,int b[],int nb,int c[],int nc)//上述的 x 属于 a，y 属于 b，z 属于 c 
{
    long long res=4e18;//初始化为 inf，注意答案最大可能为 2e18，要开 long long 
    int i=1,j=1;//i 指向 a，j 指向 c 
    for(int k=1;k<=nb;++k)
    {
        int y=b[k];
        while(i<=na&&a[i]<=y)
            ++i;
        if(i==1)//说明 a 中没有 <=y 的数 
            continue;
        int x=a[i-1];
        while(j<=nc&&c[j]<y)
            ++j;
        if(j>nc)//说明 c 中没有 >=y 的数 
            break;
        int z=c[j];
        res=min(res,1ll*(x-y)*(x-y)+1ll*(y-z)*(y-z)+1ll*(z-x)*(z-x));//更新答案，记得加上 1ll 
    }
    return res;
}

int main()
{
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int nr,ng,nb;
        scanf("%d%d%d",&nr,&ng,&nb);
        for(int i=1;i<=nr;++i)
            scanf("%d",r+i);
        sort(r+1,r+nr+1);//记得先排序 
        for(int i=1;i<=ng;++i)
            scanf("%d",g+i);
        sort(g+1,g+ng+1);
        for(int i=1;i<=nb;++i)
            scanf("%d",b+i);
        sort(b+1,b+nb+1);
        long long ans=get_ans(r,nr,g,ng,b,nb);
        ans=min(ans,get_ans(r,nr,b,nb,g,ng));
        ans=min(ans,get_ans(g,ng,r,nr,b,nb));
        ans=min(ans,get_ans(g,ng,b,nb,r,nr));
        ans=min(ans,get_ans(b,nb,r,nr,g,ng));
        ans=min(ans,get_ans(b,nb,g,ng,r,nr));//枚举六种情况 
        printf("%lld\n",ans);
    }
    return 0;
}
```
**核心实现思想**：先对三个数组进行排序，将枚举和计算过程封装到 `get_ans` 函数中，使用双指针的方法找到最优的 $x$ 和 $z$，计算 $(x - y)^2 + (y - z)^2 + (z - x)^2$ 的值并更新答案。

### 最优关键思路或技巧
- **排序**：先对三个数组进行排序，使得后续查找最接近的数可以使用二分查找或双指针的方法，提高查找效率。
- **枚举顺序**：由于 $x$、$y$、$z$ 的大小关系不确定，需要枚举它们的 $6$ 种大小关系，确保不遗漏任何情况。
- **双指针或二分查找**：使用双指针或二分查找（`lower_bound`、`upper_bound`）来找到最接近的数，时间复杂度为 $O(\log n)$。

### 可拓展之处
同类型题或类似算法套路：
- 从多个数组中各选一个数，使得某个函数值最小或最大的问题，都可以考虑使用枚举和二分查找或双指针的方法。
- 对于需要在有序数组中查找最接近的数的问题，二分查找或双指针是常用的方法。

### 推荐题目
- [P1102 A-B 数对](https://www.luogu.com.cn/problem/P1102)
- [P1824 进击的奶牛](https://www.luogu.com.cn/problem/P1824)
- [P2678 跳石头](https://www.luogu.com.cn/problem/P2678)

### 个人心得摘录与总结
- **Meatherm**：花了一个多小时才做出来这题，读错题了一个半小时。总结是做题前一定要仔细读题，避免因读错题而浪费大量时间。
- **1saunoya**：赛时秒了这题，但是结论没怎么好好证明，写完之后发现有个样例没对。总结是即使有思路，也需要对结论进行严谨的证明，并且要多测试样例，确保代码的正确性。

---
处理用时：75.75秒