# 题目信息

# [USACO20OPEN] Haircut G

## 题目描述

Farmer John 由于对整理他难以整平的头发感到疲惫，于是决定去理发。他有一排 $N$ 缕头发，第 $i$ 缕头发初始时长度为 $A_i$ 微米（$0\le A_i\le N$）。理想情况下，他想要他的头发在长度上单调递增，所以他定义他的头发的“不良度”为逆序对的数量：满足 $i < j$ 及 $A_i > A_j$ 的二元对 $(i,j)$。  
对于每一个 $j=0,1,\ldots,N-1$，Farmer John 想要知道他所有长度大于 $j$ 的头发的长度均减少到 $j$ 时他的头发的不良度。

-----

（有趣的事实：人类平均确实有大约 $10^5$ 根头发！）

## 说明/提示

#### 样例解释：

输出的第四行描述了 Farmer John 的头发长度减少到 $3$ 时的逆序对数量。   
$A=[3,2,3,3,0]$ 有五个逆序对：$A_1>A_2,\,A_1>A_5,\,A_2>A_5,\,A_3>A_5,$ 和 $A_4>A_5$。

----

对于 $100\%$ 的数据，$1\le N\le 10^5$。

共 $13$ 个测试点，其中 $1$ 为样例，其余性质如下：
  
测试点 $2$ 满足 $N\le 100$。  
测试点 $3\sim 5$ 满足 $N\le 5000$。  
测试点 $6\sim 13$ 没有额外限制。  

-----


出题人：Dhruv Rohatgi


## 样例 #1

### 输入

```
5
5 2 3 3 0```

### 输出

```
0
4
4
5
7```

# AI分析结果

### 综合分析与结论
这些题解主要围绕树状数组和线段树等数据结构解决求逆序对问题。核心思路是将原问题转化为计算每个元素对逆序对的贡献，再通过枚举长度 $j$ 统计不同情况下的逆序对数量。部分题解采用排序、倒推、正向枚举等不同策略辅助计算。

### 所选题解
- **作者：ghostdoglzd（5星）**
    - **关键亮点**：思路清晰，详细阐述了将序列排序后计算每个元素对不同 $j$ 的贡献，并用树状数组优化复杂度。代码注释丰富，可读性高。
    - **核心代码**：
```cpp
struct node{
    int a,num;
}nd[100010];
bool operator <(const node& x,const node& y){
    return (x.a==y.a)?x.num<y.num:x.a<y.a;
}
int n,tree[100010];
inline void change(int x,int c){
    while(x<=n){
        tree[x]+=c;
        x+=lowbit(x);
    }
}
inline int query(int x){
    int ans=0;
    while(x>0){
        ans+=tree[x];
        x-=lowbit(x);
    }
    return ans;
}
signed main(){
    n=rread();
    for(int i=1;i<=n;i++){
        nd[i].a=rread();
        nd[i].num=i;
        change(nd[i].num,1);
    }
    sort(nd+1,nd+1+n);
    int ans=0;
    int in=1;
    for(int i=0;i<n;i++){
        cout<<ans<<'\n';
        int t=in;
        while(i==nd[t].a){
            ans+=query(nd[t].num-1);
            change(nd[t].num,-1);
            t++;
        }
        in=t;
    }
    return 0;
}
```
    - **核心实现思想**：先将元素和其位置存入结构体并排序，用树状数组维护元素位置的存在情况。遍历排序后的元素，计算每个元素对逆序对的贡献，更新答案和树状数组。
- **作者：UltiMadow（4星）**
    - **关键亮点**：采用倒推思路，将剪头发问题转化为种头发问题，便于理解。代码简洁，直接利用树状数组维护逆序对。
    - **核心代码**：
```cpp
int n,a[MAXN];
class tarray
{
private:
    int tree[MAXN];
    int lowbit(int x){return x&(-x);}
public:
    void update(int x,int y){while(x<=n){tree[x]+=y;x+=lowbit(x);}}
    int query(int x){int ret=0;while(x){ret+=tree[x];x-=lowbit(x);}return ret;}
}t;
int s[MAXN],ans;
signed main()
{
    scanf("%lld",&n);
    for(int i=1;i<=n;i++)scanf("%lld",&a[i]),a[i]++;
    for(int i=1;i<=n;i++){
        int x=n-a[i]+2;
        s[a[i]]+=t.query(x-1);
        t.update(x,1);
    }
    printf("0");
    for(int i=2;i<=n;i++){
        ans+=s[i-1];
        printf("\n%lld",ans);
    }
    return 0;
}
```
    - **核心实现思想**：将问题转化为种头发，统计每个元素对逆序对的贡献并存入数组 $s$，最后通过累加 $s$ 数组得到不同长度下的逆序对数量。
- **作者：Lonely_NewYear（4星）**
    - **关键亮点**：分析剪头发时逆序对的变化情况，通过树状数组求逆序对并维护 $cnt$ 数组，思路清晰，代码简洁。
    - **核心代码**：
```cpp
long long s[100001],t[100001];
int n,a[100001];
int lowbit(int i)
{
    return i&-i;
}
long long query(int i)
{
    long long sum=0;
    while(i>0)
    {
        sum+=s[i];
        i-=lowbit(i);
    }
    return sum;
}
void change(int i,long long x)
{
    while(i<=n+1)
    {
        s[i]+=x;
        i+=lowbit(i);
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)
    {
        a[i]++;
        t[a[i]]+=i-1-query(a[i]);
        change(a[i],1);
    }
    long long ans=0;
    for(int i=1;i<=n;i++)
    {
        printf("%lld\n",ans);
        ans+=t[i];
    }
    return 0;
}
```
    - **核心实现思想**：在树状数组求逆序对时，维护 $t$ 数组记录每个元素对逆序对的贡献，最后输出 $t$ 数组的前缀和。

### 最优关键思路或技巧
- **转化问题**：将剪头发问题转化为种头发问题，或分析逆序对的变化情况，使问题更易理解和处理。
- **排序辅助**：对序列排序后计算元素贡献，简化计算过程。
- **树状数组优化**：利用树状数组维护区间和，将计算逆序对的复杂度降为 $O(\log n)$。

### 可拓展之处
同类型题如求区间逆序对数量、动态逆序对问题等。类似算法套路包括用树状数组或线段树维护区间信息，结合排序、枚举等策略解决问题。

### 推荐题目
- [P1908 逆序对](https://www.luogu.com.cn/problem/P1908)：基础的逆序对问题，可使用树状数组或归并排序求解。
- [P3374 【模板】树状数组 1](https://www.luogu.com.cn/problem/P3374)：树状数组的模板题，用于熟悉树状数组的基本操作。
- [P3368 【模板】树状数组 2](https://www.luogu.com.cn/problem/P3368)：涉及树状数组的区间修改和单点查询，进一步加深对树状数组的理解。

### 个人心得摘录与总结
- **作者：UltiMadow**：提到考场上看到题懵了，通过输出方式得到提示采用倒推思路，还表示这个赛季 USACO 卡在 G 组，下赛季加油。总结：在解题时可从输出方式等方面寻找思路，同时要不断努力提升自己。 

---
处理用时：42.77秒