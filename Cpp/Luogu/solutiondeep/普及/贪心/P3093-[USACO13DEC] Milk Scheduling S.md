# 题目信息

# [USACO13DEC] Milk Scheduling S

## 题目描述

Farmer John has N cows that need to be milked (1 <= N <= 10,000), each of which takes only one unit of time to milk.

Being impatient animals, some cows will refuse to be milked if Farmer John waits too long to milk them.  More specifically, cow i produces g\_i gallons of milk (1 <= g\_i <= 1000), but only if she is milked before a deadline at time d\_i (1 <= d\_i <= 10,000).  Time starts at t=0, so at most x total cows can be milked prior to a deadline at time t=x.

Please help Farmer John determine the maximum amount of milk that he can obtain if he milks the cows optimally.

FJ有N(1 <= N <= 10,000)头牛要挤牛奶，每头牛需要花费1单位时间。


奶牛很厌烦等待，奶牛i在它的截止时间d\_i (1 <= d\_i <= 10,000)前挤g(1 <= g\_i <= 1000)的奶，否则将不能挤奶。时间t开始时为0，即在时间t=x时，最多可以挤x头奶牛。


请计算FJ的最大挤奶量。


## 说明/提示

There are 4 cows.  The first produces 10 gallons of milk if milked by time 3, and so on.


Farmer John milks cow 3 first, giving up on cow 4 since she cannot be milked by her deadline due to the conflict with cow 3.  Farmer John then milks cows 1 and 2.


## 样例 #1

### 输入

```
4 
10 3 
7 5 
8 1 
2 1 
```

### 输出

```
25 
```

# AI分析结果

### 综合分析与结论

本题的核心是贪心算法，目标是在有限的时间内最大化挤奶量。各题解主要围绕如何排序和选择奶牛展开，常见的思路包括按价值排序、按截止时间排序、使用优先队列（小根堆）优化选择过程等。部分题解还引入了并查集、动态规划等数据结构或算法来进一步优化时间复杂度。

### 所选高星题解

#### 1. 作者：llzzxx712 (赞：18) - 5星
**关键亮点**：
- 使用小根堆（优先队列）优化选择过程，确保每次选择都是当前最优解。
- 通过“退流思想”动态替换低价值任务，保证全局最优。
- 代码结构清晰，注释详细，易于理解。

**核心代码**：
```cpp
priority_queue < int > q;
int n,ans,t;
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        read(a[i].g),read(a[i].d);
    }
    sort(a+1,a+1+n,cmp);
    for(int i=1,t=1;i<=n;i++){
        if(a[i].d<t){
            int x=-q.top();
            if(x<a[i].g){
                q.pop();q.push(-a[i].g);
                ans+=a[i].g-x; 
            }
        }
        if(a[i].d>=t){
            q.push(-a[i].g); 
            ans+=a[i].g;t++;
        }
    }
    cout<<ans;
}
```
**个人心得**：
- 通过小根堆实现动态替换，确保每次选择都是当前最优解，避免了贪心算法的局部最优问题。

#### 2. 作者：空气树 (赞：11) - 4星
**关键亮点**：
- 引入并查集优化时间分配，时间复杂度降至O(n)。
- 通过并查集快速找到最近的可用时间点，避免重复搜索。

**核心代码**：
```cpp
int find(int x){
    if(f[x]==x)return x;
    return f[x]=find(f[x]);
}
int main(){
    int n,r;in(n);
    for(int i=1;i<=n;i++){
        in(a[i].u);in(a[i].x);mx=max(mx,a[i].x);
    }
    for(int i=0;i<=mx;i++)f[i]=i;
    sort(a+1,a+n+1,cmp);
    for(int i=1;i<=n;i++){
        r=find(a[i].x);
        if(r<1&&r<=a[i].x)continue;
        ss+=a[i].u;f[r]=find(r-1);
    }
    cout<<ss<<endl;
}
```
**个人心得**：
- 并查集的使用大大减少了时间分配的复杂度，使得算法在较大数据规模下依然高效。

#### 3. 作者：吃瓜群众syc (赞：1) - 4星
**关键亮点**：
- 使用小根堆动态维护当前选择的任务，确保每次选择都是最优解。
- 通过堆的调整，避免了贪心算法的局部最优问题。

**核心代码**：
```cpp
priority_queue<int>q;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)	scanf("%d%d",&a[i].num,&a[i].tim);
    sort(a+1,a+n+1,cmp);
    q.push(a[1].num*(-1)),tot=1,ans=a[1].num;
    for(int i=2;i<=n;i++){
        if(a[i].tim>tot){
            tot++,ans+=a[i].num;
            q.push(a[i].num*(-1));
        }	
        else{
            int now=(-1)*(q.top());
            if(a[i].num>now){
                ans+=a[i].num-now;
                q.pop();
                q.push(a[i].num*(-1));
            }
        }
    }
    printf("%d",ans);
}
```
**个人心得**：
- 通过小根堆动态调整选择，确保每次选择都是当前最优解，避免了贪心算法的局部最优问题。

### 最优关键思路与技巧
1. **小根堆优化**：通过小根堆动态维护当前选择的任务，确保每次选择都是最优解，避免了贪心算法的局部最优问题。
2. **并查集优化时间分配**：通过并查集快速找到最近的可用时间点，避免重复搜索，大大减少了时间分配的复杂度。
3. **退流思想**：在时间不够时，动态替换低价值任务，保证全局最优。

### 可拓展之处
- **同类型题**：类似的任务调度问题，如任务截止时间与奖励的优化选择，可以参考本题的贪心+堆优化思路。
- **类似算法套路**：贪心算法结合优先队列、并查集等数据结构，适用于需要动态调整选择的优化问题。

### 推荐题目
1. [P2949 工作调度](https://www.luogu.com.cn/problem/P2949)
2. [P1233 木棍加工](https://www.luogu.com.cn/problem/P1233)
3. [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)

---
处理用时：43.17秒