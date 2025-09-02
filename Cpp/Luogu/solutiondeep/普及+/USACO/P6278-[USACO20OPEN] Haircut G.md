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
这些题解主要围绕如何利用树状数组、线段树、主席树等数据结构来解决逆序对计数问题。大部分题解思路都是将原问题转化为逆序对的统计，通过对数据的处理和数据结构的运用，计算出不同长度下的逆序对数量。

树状数组是最常用的数据结构，通过维护区间和来高效计算逆序对。部分题解采用了正难则反的思维方式，将剪头发问题转化为植发问题，便于理解和计算。

### 所选题解
- **作者：ghostdoglzd (赞：21)，4星**
  - **关键亮点**：思路清晰，先对序列排序，利用树状数组维护每个元素对不同长度下逆序对的贡献，代码实现规范，注释详细。
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
- **作者：UltiMadow (赞：17)，4星**
  - **关键亮点**：采用倒推的思维方式，将剪头发问题转化为植发问题，便于理解新增逆序对的计算，代码简洁。
  - **核心代码**：
```cpp
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
- **作者：Lonely_NewYear (赞：13)，4星**
  - **关键亮点**：分析逆序对在剪发过程中的变化，通过树状数组求逆序对时维护每个长度对应的逆序对变化量，最后输出前缀和，思路巧妙。
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

### 最优关键思路或技巧
- **数据结构**：树状数组是解决逆序对问题的常用数据结构，通过维护区间和可以高效计算逆序对。
- **思维方式**：正难则反，将剪头发问题转化为植发问题，便于理解和计算新增逆序对。
- **算法优化**：对序列排序后，依次计算每个元素对不同长度下逆序对的贡献，避免重复计算。

### 可拓展之处
同类型题或类似算法套路：
- 其他逆序对相关问题，如求逆序对数量的变形问题，或在不同条件下的逆序对计算。
- 利用树状数组、线段树、主席树等数据结构解决区间统计问题。

### 推荐题目
- P1908 逆序对
- P3374 【模板】树状数组 1
- P3368 【模板】树状数组 2

### 个人心得摘录与总结
- **作者：UltiMadow**：考场上看到题懵了，输出方式给了提示，想到倒推，将剪头发转化为植发问题，这个赛季usaco卡在G组，下赛季加油。总结：输出方式等题目细节可能提供解题思路，遇到困难要积极转换思维。
- **作者：yf最qhhh**：做了几十分钟才看题解知道是树状数组。总结：对算法的敏感度需要通过多做题来提高。

---
处理用时：43.85秒