# 题目信息

# Buses

## 题目描述

Little boy Gerald studies at school which is quite far from his house. That's why he has to go there by bus every day. The way from home to school is represented by a segment of a straight line; the segment contains exactly $ n+1 $ bus stops. All of them are numbered with integers from $ 0 $ to $ n $ in the order in which they follow from Gerald's home. The bus stop by Gerald's home has number $ 0 $ and the bus stop by the school has number $ n $ .

There are $ m $ buses running between the house and the school: the $ i $ -th bus goes from stop $ s_{i} $ to $ t_{i} $ ( $ s_{i}&lt;t_{i} $ ), visiting all the intermediate stops in the order in which they follow on the segment. Besides, Gerald's no idiot and he wouldn't get off the bus until it is still possible to ride on it closer to the school (obviously, getting off would be completely pointless). In other words, Gerald can get on the $ i $ -th bus on any stop numbered from $ s_{i} $ to $ t_{i}-1 $ inclusive, but he can get off the $ i $ -th bus only on the bus stop $ t_{i} $ .

Gerald can't walk between the bus stops and he also can't move in the direction from the school to the house.

Gerald wants to know how many ways he has to get from home to school. Tell him this number. Two ways are considered different if Gerald crosses some segment between the stops on different buses. As the number of ways can be too much, find the remainder of a division of this number by $ 1000000007 $ ( $ 10^{9}+7 $ ).

## 说明/提示

The first test has the only variant to get to school: first on bus number one to the bus stop number one; then on bus number two to the bus stop number two.

In the second test no bus goes to the third bus stop, where the school is positioned. Thus, the correct answer is $ 0 $ .

In the third test Gerald can either get or not on any of the first four buses to get closer to the school. Thus, the correct answer is $ 2^{4}=16 $ .

## 样例 #1

### 输入

```
2 2
0 1
1 2
```

### 输出

```
1
```

## 样例 #2

### 输入

```
3 2
0 1
1 2
```

### 输出

```
0
```

## 样例 #3

### 输入

```
5 5
0 1
0 2
0 3
0 4
0 5
```

### 输出

```
16
```

# AI分析结果

### 题目内容
# 公交车

## 题目描述
小男孩杰拉尔德在一所离家很远的学校上学。这就是为什么他每天都得坐公交车去学校。从家到学校的路线用一条直线段表示；该线段上正好有 \(n + 1\) 个公交站。所有公交站都用从 \(0\) 到 \(n\) 的整数编号，编号顺序是它们在从杰拉尔德家出发的路线上的顺序。杰拉尔德家旁边的公交站编号为 \(0\)，学校旁边的公交站编号为 \(n\)。

在他家和学校之间有 \(m\) 辆公交车运行：第 \(i\) 辆公交车从站 \(s_i\) 开到 \(t_i\)（\(s_i < t_i\)），按线段上的顺序经过所有中间站。此外，杰拉尔德不傻，在公交车还能继续驶向学校时，他不会下车（显然，下车是完全没有意义的）。换句话说，杰拉尔德可以在编号从 \(s_i\) 到 \(t_i - 1\)（包括两端）的任何一站上第 \(i\) 辆公交车，但他只能在公交站 \(t_i\) 下第 \(i\) 辆公交车。

杰拉尔德不能在公交站之间步行，也不能朝从学校到家的方向移动。

杰拉尔德想知道他从家到学校有多少种方法。告诉他这个数字。如果杰拉尔德在不同的公交车上经过两站之间的某条线段，则这两种方法被认为是不同的。由于方法的数量可能太多，求出这个数字除以 \(1000000007\)（\(10^9 + 7\)）的余数。

## 说明/提示
第一个测试用例有唯一一种到达学校的方法：先乘坐 1 号公交车到 1 号公交站；然后乘坐 2 号公交车到 2 号公交站。

在第二个测试用例中，没有公交车开往学校所在的 3 号公交站。因此，正确答案是 \(0\)。

在第三个测试用例中，杰拉尔德可以选择乘坐或不乘坐前四辆公交车中的任何一辆来更接近学校。因此，正确答案是 \(2^4 = 16\)。

## 样例 #1
### 输入
```
2 2
0 1
1 2
```
### 输出
```
1
```

## 样例 #2
### 输入
```
3 2
0 1
1 2
```
### 输出
```
0
```

## 样例 #3
### 输入
```
5 5
0 1
0 2
0 3
0 4
0 5
```
### 输出
```
16
```

### 算法分类
动态规划

### 综合分析与结论
所有题解都采用动态规划思路解决该问题，核心难点在于状态表示与转移优化。多数题解设 \(dp[i]\) 表示乘坐第 \(i\) 趟公交车到达终点的方案数，答案为所有终点是 \(n\) 的 \(dp\) 值之和。转移时需枚举前一趟公交车，为优化时间复杂度，通过对公交车按终点排序，利用二分查找找到符合条件的前序公交车，并结合前缀和、线段树或树状数组等方式快速求和。

### 所选的题解
- **__Hacheylight__题解**：★★★★
  - **关键亮点**：思路清晰，详细阐述离散化、状态定义、转移方程及优化过程。利用 `lower_bound` 结合前缀和优化转移，代码简洁明了。
  - **重点代码核心思想**：先读入数据并对公交车按终点排序，初始化部分 \(dp\) 值，通过二分查找确定可转移的公交车范围，利用前缀和计算转移值并更新 \(dp\) 和前缀和数组，最后统计终点为 \(n\) 的 \(dp\) 值。
  - **核心代码片段**：
```cpp
int main() {
    scanf("%d%d", &n, &m);
    vector <pii> a(m); vi v(m);
    for (int i = 0, s, t; i < m; i++) {
        scanf("%d%d", &s, &t);
        a[i] = mp(t, s);
        v[i] = t;
    }
    sort(a.begin(), a.end()); sort(v.begin(), v.end());
    for (int i = 0; i < m; i++) {
        int f = a[i].se, t = a[i].fi;
        if (f == 0) dp[i] = 1;
        int S = lower_bound(v.begin(), v.end(), f) - v.begin();
        int T = lower_bound(v.begin(), v.end(), t) - v.begin();
        dp[i] = (dp[i] + sum[T] - sum[S] + MOD) % MOD;
        sum[i + 1] = (sum[i] + dp[i]) % MOD;
    }
    for (int i = 0; i < m; i++) if (a[i].fi == n) ans = (ans + dp[i]) % MOD;
    printf("%d\n", ans);
}
```
- **傅思维666题解**：★★★★
  - **关键亮点**：从常规状态表示的困难出发，引出以车次维护状态的思路，逻辑连贯。代码简洁，实现了状态转移和结果统计。
  - **重点代码核心思想**：读入数据后对公交车按终点排序，初始化部分 \(dp\) 值，通过二分查找结合前缀和计算转移值，更新 \(dp\) 和前缀和数组，最后统计终点为 \(n\) 的 \(dp\) 值。
  - **核心代码片段**：
```cpp
int main()
{
    scanf("%d%d",&n,&m);
    e.push_back(make_pair(0,0));
    f.push_back(0);
    for(int i=1;i<=m;i++)
    {
        int s,t;
        scanf("%d%d",&s,&t);
        e.push_back(make_pair(t,s));
        f.push_back(t);
    }
    sort(e.begin(),e.end());
    sort(f.begin(),f.end());
    for(int i=1;i<=m;i++)
    {
        int x=e[i].second,y=e[i].first;
        if(!x)
            dp[i]=1;
        int s=lower_bound(f.begin(),f.end(),x)-f.begin();
        int t=lower_bound(f.begin(),f.end(),y)-f.begin();
        dp[i]=(dp[i]+sum[t]-sum[s]+mod)%mod;
        sum[i+1]=(sum[i]+dp[i])%mod;
    }
    for(int i=1;i<=m;i++)
        if(e[i].first==n)
            ans=(ans+dp[i])%mod;
    printf("%d\n",ans);
    return 0;
}
```
- **tonyre题解**：★★★★
  - **关键亮点**：详细分析状态表示的难点及优化方向，给出清晰的状态转移方程和优化思路，代码注释详细。
  - **重点代码核心思想**：读入数据后对公交车按终点排序，初始化部分 \(dp\) 值，通过二分查找确定可转移的公交车范围，利用前缀和计算转移值并更新 \(dp\) 和前缀和数组，最后统计终点为 \(n\) 的 \(dp\) 值。
  - **核心代码片段**：
```cpp
signed main()
{
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=m;i++) cin>>a[i].s>>a[i].t;
    sort(a+1,a+m+1,cmp);
    for(int i=1;i<=m;i++)
    {
        if(!a[i].s) dp[i]=1;
        int l=1,r=i-1;
        int mid;
        int ans1=-1;
        while(l<=r)
        {
            mid=(l+r)>>1;
            if(a[mid].t>=a[i].s)
            {
                r=mid-1;
                ans1=mid;
            }
            else l=mid+1;
        }
        l=1,r=i-1;
        int ans2=-1;
        while(l<=r)
        {
            mid=(l+r)>>1;
            if(a[mid].t<a[i].t)
            {
                l=mid+1;
                ans2=mid;
            }
            else r=mid-1;
        }
        if(ans1!=-1&&ans2!=-1)
        {
            dp[i]+=sum[ans2]-sum[ans1-1];
            dp[i]=(dp[i]+MOD)%MOD;
        }
        sum[i]=(sum[i-1]+dp[i])%MOD;
    }
    int cnt=0;
    for(int i=1;i<=m;i++)
        if(a[i].t==n)
        {
            cnt+=dp[i];
            cnt=(cnt+MOD)%MOD;
        }
    cout<<cnt<<endl;
    return 0;
}
```

### 最优关键思路或技巧
1. **状态表示优化**：针对常规以车站位置表示状态转移困难的问题，转变思路以公交车车次表示状态，使状态转移更易实现。
2. **排序与二分查找**：对公交车按终点排序后，利用二分查找快速定位可转移的前序公交车，减少枚举时间复杂度。
3. **前缀和优化**：通过维护 \(dp\) 值的前缀和，快速计算一段区间内 \(dp\) 值之和，优化状态转移过程。

### 拓展
同类型题可关注涉及路径计数且状态转移复杂的动态规划题目，通常需根据题目条件灵活定义状态，结合排序、二分、数据结构优化转移。例如在一些网格路径计数问题中，可借鉴类似按某种顺序排序后利用数据结构优化转移的思路。

### 洛谷推荐题目
1. [P1002 过河卒](https://www.luogu.com.cn/problem/P1002)：经典的棋盘路径计数动态规划题，需考虑障碍物对路径的影响。
2. [P1216 数字三角形](https://www.luogu.com.cn/problem/P1216)：通过不同方向的状态转移求解数字三角形的最大路径和。
3. [P1434 [SHOI2002]滑雪](https://www.luogu.com.cn/problem/P1434)：结合记忆化搜索与动态规划，求解滑雪的最长路径长度。 

---
处理用时：82.43秒