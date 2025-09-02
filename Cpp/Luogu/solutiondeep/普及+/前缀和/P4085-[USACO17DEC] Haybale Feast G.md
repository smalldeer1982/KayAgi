# 题目信息

# [USACO17DEC] Haybale Feast G

## 题目描述

农夫约翰正在为他的奶牛准备一顿美味的晚餐！在他的谷仓里，他有 $N$ 个干草捆 $(1 \le N \le 10^5)$ 。第 $i$ 个干草捆有一定的风味 $F_i(1 \le F_i \le 10^9)$ 和一定的辣度 $S_i(1 \le S_i \le 10^9)$ 。

这顿饭将由一道菜组成，是一个连续的区间，包含一个或多个连续的干草捆(农夫约翰不能改变干草捆的顺序)。这顿饭的总体的风味是这段区间里风味的总和。这顿饭的总体辣度是区间中所有草包的最大辣度。

农夫约翰想确定他的这道菜所能达到的最小辣度，但是这道菜的总风味必须至少为 $M(1 \le M \le 10^{18})$ 。

## 样例 #1

### 输入

```
5 10
4 10
6 15
3 5
4 9
3 6```

### 输出

```
9```

# AI分析结果

• 综合分析与结论：
    - 思路方面：多数题解围绕寻找满足风味总和至少为M的区间，并在此基础上求区间辣度最大值的最小值。部分题解采用二分答案思路，二分辣度最大值，检查是否存在满足风味和条件的区间；部分通过枚举左端点，二分查找右端点，结合RMQ相关数据结构（如ST表、线段树等）求区间辣度最大值；还有尺取法结合单调队列或RMQ数据结构来解题。
    - 算法要点：前缀和用于快速计算区间风味总和；RMQ相关数据结构用于快速查询区间辣度最大值；二分查找优化寻找满足风味和条件的区间端点；尺取法利用区间端点单调性优化查找过程。
    - 解决难点：核心是在满足风味总和条件下，高效找到辣度最大值最小的区间。不同解法通过不同数据结构和算法优化来平衡时间复杂度和实现难度。

    - 综合质量看，wheneveright、白鲟、Del_Your_Heart的题解相对较好。

  - wheneveright题解（5星）：
    - 关键亮点：思路清晰简洁，明确指出本题是二分答案的板子题，利用辣度最大值大时可选风味和更大的单调性进行二分，代码实现简洁明了。
    - 个人心得：无
    - 核心代码（check函数及二分部分）：
```cpp
bool check (int maxs) {
    sum = 0;
    for (int i = 1; i <= N; i++) {
        if (S[i] > maxs) sum = 0;
        else sum += F[i];
        if (sum >= M) return true;
    }
    return false;
}

int main () {
    cin >> N >> M;
    for (int i = 1; i <= N; i++) {
        cin >> F[i] >> S[i];
        R = max (R, S[i]);
    }   
    L = 1;
    while (L <= R) check (mid = ((L + R) >> 1))? R = mid - 1, res = mid : L = mid + 1;
    printf ("%lld\n", res);
    return 0;
}
```
    - 核心实现思想：check函数用于检查给定辣度最大值maxs下，是否存在连续区间风味和达到M。二分部分通过不断调整辣度最大值范围，找到满足条件的最小值。

  - 白鲟题解（5星）：
    - 关键亮点：详细拆解问题为两个子问题，先分析贪心选择最靠前满足风味和条件的右端点，再针对RMQ问题提出多种解法，并指出前缀和性质可利用尺取法优化查找右端点，最终给出时间复杂度为O(n)的优秀解法。
    - 个人心得：无
    - 核心代码（解法2的主函数部分）：
```cpp
int main()
{
    scanf("%lld%lld",&n,&m);
    for(long long i=1;i<=n;++i)
        scanf("%lld%lld",&f[i],&s[i]);
    for(long long i=1,j=0;i<=n;++i)
    {
        sum-=f[i-1];
        while(head<=tail&&que[head]<i)
            ++head;
        while(sum<m&&j<n)
        {
            sum+=f[++j];
            while(head<=tail&&s[que[tail]]<=s[j])
                --tail;
            que[++tail]=j;
        }
        if(sum<m)
            break;
        ans=min(ans,s[que[head]]);
    }
    printf("%lld",ans);
    return 0;
}
```
    - 核心实现思想：利用尺取法，通过移动左右端点，同时用单调队列维护区间辣度最大值，找到满足风味和条件下的最小辣度最大值。

  - Del_Your_Heart题解（4星）：
    - 关键亮点：思路全面，分析了前缀和预处理、二分查找右端点以及多种用于查询区间辣度最大值的数据结构（ST表、普通线段树、zkw线段树），并给出三种数据结构实现的代码及实际运行时间对比。
    - 个人心得：无
    - 核心代码（zkw线段树部分）：
```cpp
int n,sum[100005],s[100005],m,ans=0x7fffffffffffffff,d=1,zkw[400005];
inline int query(int l,int r){int ans=0;for(l+=d-1,r+=d+1;l^r^1;l>>=1,r>>=1){if(~l&1)ans=max(ans,zkw[l^1]);if(r&1)ans=max(ans,zkw[r^1]);}return ans;}
signed main(){
    n=read();m=read();while(d<=n+1)d<<=1;
    for(register int i=1;i<=n;++i)sum[i]=sum[i-1]+read(),zkw[i+d]=s[i]=read();
    for(register int i=d-1;i;--i)zkw[i]=max(zkw[i<<1],zkw[i<<1|1]);
    for(register int i=1;i<=n;++i){
        int l=i,r=n,mid;
        if(sum[r]-sum[i-1]<m)break;
        while(l<r){mid=l+r>>1;if(sum[mid]-sum[i-1]>m)r=mid;else l=mid+1;}
        ans=min(ans,query(i,r));
    }
    cout<<ans;
}
```
    - 核心实现思想：利用zkw线段树非递归特性建树并查询区间辣度最大值，通过二分查找右端点，找到满足风味和条件下的最小辣度最大值。

• 最优关键思路或技巧：
    - 二分答案：利用答案的单调性，通过二分快速缩小答案范围，减少搜索空间。
    - 尺取法：基于区间端点单调性，线性扫描优化查找满足条件区间的过程，降低时间复杂度。
    - RMQ数据结构：如ST表、线段树等，高效查询区间最值，与其他算法结合解决问题。

• 可拓展之处：同类型题常涉及在满足某种区间和或其他条件下，求区间最值相关问题。类似算法套路包括二分答案结合条件检查、利用数据结构优化区间查询、利用单调性优化查找过程等。

• 相似知识点洛谷题目：
    - P3865 [模板] ST 表
    - P3372 【模板】线段树 1
    - P1886 滑动窗口 /【模板】单调队列 

---
处理用时：42.70秒