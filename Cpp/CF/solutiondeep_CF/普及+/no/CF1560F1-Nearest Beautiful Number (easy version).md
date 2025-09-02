# 题目信息

# Nearest Beautiful Number (easy version)

## 题目描述

It is a simplified version of problem F2. The difference between them is the constraints (F1: $ k \le 2 $ , F2: $ k \le 10 $ ).

You are given an integer $ n $ . Find the minimum integer $ x $ such that $ x \ge n $ and the number $ x $ is $ k $ -beautiful.

A number is called $ k $ -beautiful if its decimal representation having no leading zeroes contains no more than $ k $ different digits. E.g. if $ k = 2 $ , the numbers $ 3434443 $ , $ 55550 $ , $ 777 $ and $ 21 $ are $ k $ -beautiful whereas the numbers $ 120 $ , $ 445435 $ and $ 998244353 $ are not.

## 样例 #1

### 输入

```
4
1 1
221 2
177890 2
998244353 1```

### 输出

```
1
221
181111
999999999```

# AI分析结果

### 题目内容中文重写
# 最近的漂亮数（简单版本）

## 题目描述
这是问题 F2 的简化版本。它们之间的区别在于约束条件（F1：$ k \le 2 $，F2：$ k \le 10 $）。

给定一个整数 $ n $。找到最小的整数 $ x $，使得 $ x \ge n $ 且数字 $ x $ 是 $ k $ 漂亮数。

如果一个数的十进制表示没有前导零，并且包含不超过 $ k $ 个不同的数字，那么这个数就被称为 $ k $ 漂亮数。例如，如果 $ k = 2 $，数字 $ 3434443 $、$ 55550 $、$ 777 $ 和 $ 21 $ 是 $ k $ 漂亮数，而数字 $ 120 $、$ 445435 $ 和 $ 998244353 $ 不是。

## 样例 #1

### 输入
```
4
1 1
221 2
177890 2
998244353 1
```

### 输出
```
1
221
181111
999999999
```

### 算法分类
枚举

### 综合分析与结论
这些题解主要围绕如何找出大于等于给定整数 $n$ 的最小 $k$ 漂亮数展开，由于本题 $k \le 2$，满足条件的数数量有限，所以大部分题解采用了枚举的思路。各题解的主要思路和方法有：
1. **预处理 + 二分**：先预处理出所有 $1$-漂亮数和 $2$-漂亮数，再对每次查询进行二分查找，时间复杂度较低。
2. **分类讨论 + 枚举**：分 $k = 1$ 和 $k = 2$ 两种情况讨论，分别枚举满足条件的数。
3. **搜索**：使用深度优先搜索（DFS）来构造满足条件的数，通过剪枝优化搜索过程。
4. **数位 DP**：使用动态规划和状态压缩来解决问题。

各题解的难点在于如何高效地枚举和构造满足条件的数，以及处理前导零和边界情况。

### 所选题解
- **Miraik（4星）**
  - **关键亮点**：思路清晰，通过预处理所有 $1$-漂亮数和 $2$-漂亮数，再利用二分查找，时间复杂度低，代码实现简洁明了。
- **_JF_（4星）**
  - **关键亮点**：不仅给出了 F1 的暴力枚举解法，还对 F2 的构造方法进行了分析，思路全面，代码实现有一定的细节处理。
- **Jr_Zlw（4星）**
  - **关键亮点**：对满足条件的数的数量进行了合理估计，通过预处理打表和二分查找解决问题，代码实现较为完整。

### 重点代码
#### Miraik 的代码
```cpp
// 生成 2 - beautiful 数的 DFS 函数
void dfs(int k,int x,int y,int res){
    b[++cntb]=res;
    if(k>9)return;
    if(k>1||x>0)dfs(k+1,x,y,res*10+x);
    dfs(k+1,x,y,res*10+y);
}
// 预处理函数
void init(){
    for(int i=1;i<=9;i++)
        for(int j=1,k=i;j<=9;j++)a[++cnta]=k,k=k*10+i;
    a[++cnta]=1111111111;
    for(int i=0;i<=9;i++)
        for(int j=i+1;j<=9;j++)dfs(1,i,j,0);
    b[++cntb]=1e9; 
    sort(a+1,a+cnta+1);
    sort(b+1,b+cntb+1);
}
// 二分查找函数
while(l<=r){
    mid=l+r>>1;
    if(a[mid]>=n)ans=min(ans,a[mid]),r=mid-1;
    else l=mid+1;
}
```
**核心实现思想**：先通过 `init` 函数预处理出所有 $1$-漂亮数和 $2$-漂亮数，分别存储在数组 `a` 和 `b` 中并排序。对于每次查询，根据 $k$ 的值选择对应的数组进行二分查找，找到第一个大于等于 $n$ 的数。

#### _JF_ 的代码
```cpp
// 解决问题的函数
void Slove(int n,int k){
    for(int i=0;i<=9;i++) vis[i]=vis1[i]=false;
    int dis=n,len=0;
    while(dis>0) sta.push(dis%10),dis/=10;
    tot=0;
    while(!sta.empty()) a[++tot]=sta.top(),sta.pop();
    int ans=0,now=0;
    for(int i=1;i<=tot;i++) ans=ans*10+9;
    for(int i=1;i<=tot+1;i++){
        int dus=0;
        for(int j=0;j<=9;j++) dus+=vis[j];
        if(i==tot+1){
            if(dus<=k) ans=n;
            break;
        }
        if(a[i]==9){
            vis[a[i]]=true,now=now*10+a[i];	
            continue;	
        }
        if(dus>k) continue;
        for(int j=0;j<=9;j++) vis1[j]=vis[j];
        int lst=k-dus,predus,nowans=now;
        bool f0=false;
        if(vis1[a[i]+1]==true) predus=a[i]+1;
        else{
            if(lst>0){
                predus=a[i]+1,vis1[a[i]+1]=true,lst--;	
            }
            else{
                predus=-1;
                for(int j=0;j<=9;j++){
                    if(vis1[j]==true&&j>a[i]){
                        predus=j;break;
                    }
                }
                if(predus==-1){
                    f0=true;
                }
            }
        }
        if(f0){
            vis[a[i]]=true,now=now*10+a[i];
            continue;
        }
        nowans=nowans*10+predus;
        int lstU;
        if(lst>0) lstU=0;
        else{
            for(int j=0;j<=9;j++){
                if(vis1[j]==true) {lstU=j; break;}
            }
        }
        for(int j=i+1;j<=tot;j++) nowans=nowans*10+lstU;
        ans=min(ans,nowans);
        vis[a[i]]=true,now=now*10+a[i];
    }
    cout<<ans<<endl;
}
```
**核心实现思想**：将 $n$ 的每一位存储在数组 `a` 中，然后枚举数位 $i$，钦定它是第一个大于 $a_i$ 的位置，根据不同情况构造满足条件的数，最后取最小值。

#### Jr_Zlw 的代码
```cpp
// 记录满足条件的数的函数
inline void rcd(int s,int b,int n)
{
    rep(0,(1<<n)-1,i)
    {
        int tmp=i;++cnt;
        rep(1,n,i)lis[cnt]=lis[cnt]*10+((tmp&1)?s:b),tmp=tmp>>1;
    }
}
// 解决问题的函数
inline void Solve()
{
    int n=read(),k=read();
    if(k==1)
    {
        int l=1,r=m1,res,mid;
        while(l<=r)lis1[mid=(l+r)>>1]<n?(l=mid+1):(r=mid-1,res=mid);
        printf("%lld\n",lis1[res]);return;
    }
    int l=1,r=m,res,mid;
    while(l<=r)lis[mid=(l+r)>>1]<n?(l=mid+1):(r=mid-1,res=mid);
    printf("%lld\n",lis[res]);return;
}
```
**核心实现思想**：通过 `rcd` 函数生成满足条件的数，分别存储在数组 `lis` 和 `lis1` 中并排序去重。对于每次查询，根据 $k$ 的值选择对应的数组进行二分查找，找到第一个大于等于 $n$ 的数。

### 最优关键思路或技巧
- 预处理所有满足条件的数，再利用二分查找，时间复杂度较低。
- 分类讨论 $k = 1$ 和 $k = 2$ 的情况，分别进行枚举。
- 利用深度优先搜索（DFS）构造满足条件的数，通过剪枝优化搜索过程。

### 可拓展之处
同类型题或类似算法套路：
- 数位相关的计数问题，如求某个区间内满足特定条件的数的个数。
- 状态压缩动态规划问题，通过状态压缩来减少空间复杂度。
- 搜索剪枝问题，在搜索过程中通过剪枝来减少不必要的计算。

### 推荐题目
- [P1833 樱花](https://www.luogu.com.cn/problem/P1833)：涉及枚举和二分查找。
- [P2678 跳石头](https://www.luogu.com.cn/problem/P2678)：二分查找的经典应用。
- [P1182 数列分段 Section II](https://www.luogu.com.cn/problem/P1182)：二分查找和贪心算法的结合。

### 个人心得摘录与总结
- **_JF_**：认为 F1 是一个暴力枚举题，不理解为什么难度有 ***1900**，体现了对题目难度的个人看法。

---
处理用时：113.31秒