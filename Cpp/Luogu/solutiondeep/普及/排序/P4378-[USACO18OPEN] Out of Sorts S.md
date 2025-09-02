# 题目信息

# [USACO18OPEN] Out of Sorts S

## 题目描述

留意着农场之外的长期职业生涯的可能性，奶牛 Bessie 开始在不同的在线编程网站上学习算法。

她到目前为止最喜欢的算法是“冒泡排序”。这是 Bessie 的对长度为 $N$ 的数组 $A$ 进行排序的奶牛码实现。

```
sorted = false
while (not sorted):
   sorted = true
   moo
   for i = 0 to N-2:
      if A[i+1] < A[i]:
         swap A[i], A[i+1]
         sorted = false
```
显然，奶牛码中的“moo”指令的作用只是输出“moo”。奇怪的是，Bessie 看上去执着于在她的代码中的不同位置使用这个语句。

给定一个输入数组，请预测 Bessie 的代码会输出多少次“moo”。

## 说明/提示

供题：Brian Dean

## 样例 #1

### 输入

```
5
1
5
3
8
2```

### 输出

```
4
```

# AI分析结果

### 综合分析与结论
本题要求计算冒泡排序中输出“moo”的次数，多数题解指出不能直接按伪代码模拟，需找出规律计算。核心思路是找出每个数左移的最大次数，再加上 1（代表最后一次检查数组是否有序的迭代）。各题解在实现上有所不同，部分使用模拟，部分借助树状数组、离散化、Treap 等数据结构和算法。

### 所选题解
- **作者：t14Zack（5 星）**
    - **关键亮点**：思路清晰，通过多个例子详细说明规律，代码简洁易懂。
    - **个人心得**：开始按伪代码实现只过了 5 个点，意识到要自己计算输出次数。
    - **核心代码**：
```cpp
struct node {
    int in;
    int zhi;
} a[100000];
bool cmp (const node &a, const node &b) {
    return a.zhi < b.zhi || (a.zhi == b.zhi && a.in < b.in);
}
int max(int a, int b) {return a < b? b : a;}
int main() {
    int n, ans = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i].zhi), a[i].in = i;
    std::sort(a, a+n, cmp);
    for (int j = 0; j < n; j++)
        ans = max(ans, a[j].in-j);
    printf("%d\n", ans+1);
}
```
    - **核心实现思想**：用结构体存储每个数及其原始位置，排序后计算每个数左移的最大次数，最后加 1 输出。

- **作者：ljc20020730（4 星）**
    - **关键亮点**：从逆序对角度解释本质，使用树状数组优化，复杂度为 $O(n log_2 n)$。
    - **核心代码**：
```cpp
const int N=1e5+10;
int a[N],tmp[N],c[N];
int n,T;
void update(int x){for (;x<=n;x+=x&-x)c[x]++;}
int query(int x){int ret=0;for (;x;x-=x&-x) ret+=c[x];return ret;}
int main()
{
    scanf("%d",&n); tmp[0]=n;
    for (int i=1;i<=n;i++) scanf("%d",&a[i]),tmp[i]=a[i];
    sort(tmp+1,tmp+tmp[0]+1);
    T=unique(tmp+1,tmp+1+tmp[0])-tmp-1;
    int ans=0;
    for (int i=1;i<=n;i++) {
        int w=lower_bound(tmp+1,tmp+1+T,a[i])-tmp;
        update(w);
        ans=max(i-query(w),ans);
    }
    printf("%d\n",ans+1);
    return 0;
}
```
    - **核心实现思想**：利用树状数组维护逆序对，离散化处理数据，找出每个位置逆序对的最大值加 1 得到结果。

- **作者：liuyanxi2（4 星）**
    - **关键亮点**：详细说明坑点，如排序时考虑重复元素的原始位置，代码规范且有注释。
    - **个人心得**：开始直接套伪代码只拿 10 分，意识到要自己计算；排序时未考虑重复元素原始位置只有 80 分。
    - **核心代码**：
```cpp
bool cmp(cow q,cow w)
{
    return q.num<w.num ||(q.num==w.num&&q.id<w.id);
}
int main ( )
{
    cin>>n;
    for(i=1;i<=n;i++)
        cin>>a[i].num,a[i].id=i;
    sort(a+1,a+n+1,cmp);
    for(i=1;i<=n;i++)
        ans=max(ans,a[i].id-i);
    cout<<ans+1;
    return 0 ;
}
```
    - **核心实现思想**：用结构体存储数和原始位置，按规则排序后计算左移最大次数加 1 输出。

### 最优关键思路或技巧
- **规律总结**：通过多个例子总结出“moo”次数等于往左移的最多的次数加 1。
- **离散化**：当数据范围大时，使用离散化将数据映射到较小范围，减少空间复杂度。
- **树状数组**：用于维护逆序对，优化时间复杂度到 $O(n log_2 n)$。

### 拓展思路
同类型题可考虑其他排序算法的迭代次数问题，或在不同数据结构上进行排序操作的次数计算。类似算法套路包括利用数据结构维护逆序对、离散化处理大数据范围等。

### 推荐题目
- [P1908 逆序对](https://www.luogu.com.cn/problem/P1908)
- [P6186 [NOI Online #1 提高组] 冒泡排序](https://www.luogu.com.cn/problem/P6186)
- [P1093 [NOIP2007 普及组] 奖学金](https://www.luogu.com.cn/problem/P1093)

### 个人心得总结
- t14Zack：直接按伪代码实现只能通过部分测试点，需自己总结规律计算输出次数。
- liuyanxi2：直接套伪代码得分低，排序时未考虑重复元素原始位置会导致部分测试点不通过。
- 封禁用户：使用树状数组求逆序对时，离散化要注意排序和去重，否则会出错。
- IL杰佣：判定时可能有相同数字，需同时考虑编号前后，否则会丢分。 

---
处理用时：42.22秒