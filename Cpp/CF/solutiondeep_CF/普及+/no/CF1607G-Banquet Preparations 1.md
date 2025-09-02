# 题目信息

# Banquet Preparations 1

## 题目描述

厨师为一次宴会准备了 $n$ 道菜品，出于某种原因，所有菜品都是由鱼肉和猪肉组成的。第 $i$ 道菜品中包含了 $a_i$ 单位的鱼肉和 $b_i$ 单位的猪肉。

晚宴的主办方定义晚会美食的平衡度为 $|\sum_{i=1}^n\ a_i\ - \ \sum_{i=1}^n\ b_i|$，并且希望这个值越小越好。为了达成这一点，主办方请来了一个吃客。此人会在每道菜中刚好吃下 $m$ 单位的食物，这会使得 $a_i,b_i$ 发生变化。

现在请你规划他在每道菜中该吃多少鱼肉，多少猪肉，使得最后的平衡值最小。

## 说明/提示

$1\le n \le 2\times 10^5,\ 0\le m\le 10^6$
保证对于 $\forall i$，满足 $m\le a_i+b_i$

## 样例 #1

### 输入

```
8

1 5
3 4

1 6
3 4

2 2
1 3
4 2

2 4
1 3
1 7

3 6
1 7
1 8
1 9

3 6
1 8
1 9
30 10

3 4
3 1
3 2
4 1

5 4
0 7
6 4
0 8
4 1
5 3```

### 输出

```
0
2 3
1
3 3
0
1 1
1 1
2
1 3
0 4
3
0 6
0 6
0 6
7
1 5
1 5
6 0
0
3 1
3 1
3 1
0
0 4
2 2
0 4
3 1
1 3```

# AI分析结果

【题目内容】
# 宴会准备 1

## 题目描述

厨师为一次宴会准备了 $n$ 道菜品，出于某种原因，所有菜品都是由鱼肉和猪肉组成的。第 $i$ 道菜品中包含了 $a_i$ 单位的鱼肉和 $b_i$ 单位的猪肉。

晚宴的主办方定义晚会美食的平衡度为 $|\sum_{i=1}^n\ a_i\ - \ \sum_{i=1}^n\ b_i|$，并且希望这个值越小越好。为了达成这一点，主办方请来了一个吃客。此人会在每道菜中刚好吃下 $m$ 单位的食物，这会使得 $a_i,b_i$ 发生变化。

现在请你规划他在每道菜中该吃多少鱼肉，多少猪肉，使得最后的平衡值最小。

## 说明/提示

$1\le n \le 2\times 10^5,\ 0\le m\le 10^6$
保证对于 $\forall i$，满足 $m\le a_i+b_i$

## 样例 #1

### 输入

```
8

1 5
3 4

1 6
3 4

2 2
1 3
4 2

2 4
1 3
1 7

3 6
1 7
1 8
1 9

3 6
1 8
1 9
30 10

3 4
3 1
3 2
4 1

5 4
0 7
6 4
0 8
4 1
5 3
```

### 输出

```
0
2 3
1
3 3
0
1 1
1 1
2
1 3
0 4
3
0 6
0 6
0 6
7
1 5
1 5
6 0
0
3 1
3 1
3 1
0
0 4
2 2
0 4
3 1
1 3
```

【算法分类】
构造

【综合分析与结论】
- **思路对比**：
    - HDWR 题解先化简平衡度公式，根据 $x_i$ 的取值范围确定 $\sum x_i$ 的范围，再通过对固定值和取值范围的分类讨论来求解。
    - Wuyanru 题解先计算鱼肉和猪肉的总重、最多能吃的量，然后分类讨论，根据不同情况构造吃的方案。
    - caizhetong 题解计算鱼和猪肉的总数量、最多吃的量、本次需要吃的量，通过差值和每道菜的最值来构造方案。
    - Valhalla_Is_Calling 题解分两种情况讨论，一种是两种肉差超过 $m$ 时的处理，另一种是先削平多的肉再等量减少的处理。
- **算法要点对比**：
    - HDWR 题解关键在于化简公式和利用不等式性质确定取值范围，然后贪心分配。
    - Wuyanru 题解主要是分类讨论和方程求解，根据结果构造方案。
    - caizhetong 题解重点是计算各种量，通过差值和最值构造方案。
    - Valhalla_Is_Calling 题解核心是分情况处理，通过调整吃的量来达到平衡。
- **解决难点对比**：
    - HDWR 题解的难点在于公式化简和对取值范围的理解与应用。
    - Wuyanru 题解的难点在于分类讨论的完整性和方程的求解与构造。
    - caizhetong 题解的难点在于各种量的计算和方案的构造逻辑。
    - Valhalla_Is_Calling 题解的难点在于分情况处理的逻辑和调整吃的量的方法。

【所选题解】
- HDWR 题解（5 星）
    - **关键亮点**：思路清晰，先化简公式，再利用不等式性质将问题转化，最后通过分类讨论和贪心分配求解，代码实现简洁明了。
- Wuyanru 题解（4 星）
    - **关键亮点**：通过分类讨论和方程求解来构造方案，逻辑较为清晰，代码实现较为完整。

【重点代码】
- **HDWR 题解核心代码**：
```cpp
const int MAXN = 2e5 + 10;

int n, m;
std::pair<lli, lli> dishes[MAXN];
std::pair<lli, lli> bounds[MAXN];
lli chosenx[MAXN];

void _main() {
    n = read(); m = read();
    lli s = 0;
    lli suml = 0, sumr = 0;
    rep (i, 1, n) {
        lli a = read(); lli b = read();
        dishes[i] = {a, b};
        s += (a - b + m);
        bounds[i].fi = std::max(m - b, 0ll);
        bounds[i].se = std::min((lli) m, a);
        suml += bounds[i].fi; sumr += bounds[i].se;
    }
    if (2ll * sumr <= s) {
        printf("%lld\n", s - 2ll * sumr);
        rep (i, 1, n) {
            lli x = bounds[i].se, y = m - x;
            printf("%lld %lld\n", x, y);
        }
    }
    else if (s <= 2ll * suml) {
        printf("%lld\n", 2ll * suml - s);
        rep (i, 1, n) {
            lli x = bounds[i].fi, y = m - x;
            printf("%lld %lld\n", x, y);
        }
    }
    else {
        printf("%lld\n", (s % 2));
        lli ns = (s >> 1) - suml;
        rep (i, 1, n) {
            chosenx[i] = bounds[i].fi;
            lli dtx = bounds[i].se - bounds[i].fi;
            if (ns >= dtx) {
                ns -= dtx; chosenx[i] += dtx;
            } else {
                chosenx[i] += ns; ns = 0;
            }
        }
        lli checksum = 0;
        rep (i, 1, n) {
            printf("%lld %lld\n", chosenx[i], m - chosenx[i]);
            checksum += chosenx[i];
        }
        assert(std::abs(checksum * 2 - s) <= 1);
    }
}
```
**核心实现思想**：先读取输入，计算固定值 $s$ 和取值范围的和 $suml$、$sumr$，然后根据 $s$ 与 $2suml$、$2sumr$ 的关系分类讨论，最后根据情况输出结果和方案。
- **Wuyanru 题解核心代码**：
```cpp
int a[200001];
int b[200001];
ll maxa,maxb;
ll suma,sumb;
int n,m;
ll ans;
signed main()
{
    int t=read();
    while(t--)
    {
        maxa=maxb=ans=suma=sumb=0;
        n=read(),m=read();
        for(int i=1;i<=n;i++)
        {
            a[i]=read(),b[i]=read();
            suma+=a[i],sumb+=b[i];
            maxa+=min(m,a[i]);
            maxb+=min(m,b[i]);
        }
        if(suma>=sumb)
        {
            if(suma-maxa>=sumb-((ll)m*n-maxa))
            {
                printf("%lld\n",suma-maxa-(sumb-((ll)m*n-maxa)));
                for(int i=1;i<=n;i++)
                    if(a[i]<=m) printf("%d %d\n",a[i],m-a[i]);
                    else printf("%d %d\n",m,0);
                continue;
            }
            ll flag=maxa-(suma-sumb+(ll)m*n)/2;
            printf("%lld\n",(suma-sumb+(ll)m*n)%2);
            for(int i=1;i<=n;i++)
            {
                int num=min(a[i],m),minn=m-min(m,b[i]);
                if(flag>num-minn) flag-=num-minn,num=minn;
                else num=num-flag,flag=0;
                printf("%d %d\n",num,m-num);
            }
        }
        else
        {
            if(sumb-maxb>=suma-((ll)m*n-maxb))
            {
                printf("%lld\n",sumb-maxb-(suma-((ll)m*n-maxb)));
                for(int i=1;i<=n;i++)
                    if(b[i]<=m) printf("%d %d\n",m-b[i],b[i]);
                    else printf("%d %d\n",0,m);
                continue;
            }
            ll flag=maxb-(sumb-suma+(ll)m*n)/2;
            printf("%lld\n",(sumb-suma+(ll)m*n)%2);
            for(int i=1;i<=n;i++)
            {
                int num=min(b[i],m),minn=m-min(m,a[i]);
                if(flag>num-minn) flag-=num-minn,num=minn;
                else num=num-flag,flag=0;
                printf("%d %d\n",m-num,num);
            }
        }
    }
    return 0;
}
```
**核心实现思想**：先读取输入，计算鱼肉和猪肉的总重、最多能吃的量，然后根据鱼肉和猪肉总重的大小关系分类讨论，再根据不同情况计算结果和构造方案。

【最优关键思路或技巧】
- 化简平衡度公式，将问题转化为更易处理的形式。
- 利用不等式性质确定取值范围，然后通过分类讨论和贪心分配来构造方案。

【拓展思路】
同类型题可能会有更多的约束条件或更复杂的场景，例如每道菜有不同的价格，在满足平衡度的同时还要考虑价格因素；或者有多个吃客，每个吃客的食量不同等。类似算法套路主要是通过数学公式化简和分类讨论来构造满足条件的方案。

【推荐题目】
- P1094 [NOIP2007 普及组] 纪念品分组
- P1223 排队接水
- P1048 [NOIP2005 普及组] 采药

【个人心得】
题解中未包含个人心得。

---
处理用时：84.16秒