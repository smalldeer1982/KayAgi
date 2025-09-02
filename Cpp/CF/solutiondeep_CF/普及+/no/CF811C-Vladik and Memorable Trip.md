# 题目信息

# Vladik and Memorable Trip

## 题目描述

Vladik often travels by trains. He remembered some of his trips especially well and I would like to tell you about one of these trips:

Vladik is at initial train station, and now $ n $ people (including Vladik) want to get on the train. They are already lined up in some order, and for each of them the city code $ a_{i} $ is known (the code of the city in which they are going to).

Train chief selects some number of disjoint segments of the original sequence of people (covering entire sequence by segments is not necessary). People who are in the same segment will be in the same train carriage. The segments are selected in such way that if at least one person travels to the city $ x $ , then all people who are going to city $ x $ should be in the same railway carriage. This means that they can’t belong to different segments. Note, that all people who travel to the city $ x $ , either go to it and in the same railway carriage, or do not go anywhere at all.

Comfort of a train trip with people on segment from position $ l $ to position $ r $ is equal to XOR of all distinct codes of cities for people on the segment from position $ l $ to position $ r $ . XOR operation also known as exclusive OR.

Total comfort of a train trip is equal to sum of comfort for each segment.

Help Vladik to know maximal possible total comfort.

## 说明/提示

In the first test case best partition into segments is: $ [4,4] $ $ [2,5,2] $ $ [3] $ , answer is calculated as follows: $ 4+(2 $ $ xor $ $ 5)+3=4+7+3=14 $

In the second test case best partition into segments is: $ 5 $ $ 1 $ $ [3] $ $ 1 $ $ 5 $ $ [2,4,2] $ $ 5 $ , answer calculated as follows: $ 3+(2 $ $ xor $ $ 4)=3+6=9 $ .

## 样例 #1

### 输入

```
6
4 4 2 5 2 3
```

### 输出

```
14
```

## 样例 #2

### 输入

```
9
5 1 3 1 5 2 4 2 5
```

### 输出

```
9
```

# AI分析结果

### 题目内容
# 弗拉迪克和难忘的旅行

## 题目描述
弗拉迪克经常坐火车旅行。他对一些旅行记忆尤为深刻，现在我想给你讲其中一次旅行：

弗拉迪克在起始火车站，现在有\(n\)个人（包括弗拉迪克）想上火车。他们已经按某种顺序排好了队，并且对于他们每个人，都知道其目的地城市的代码\(a_{i}\) 。

火车负责人会选择原始人员序列中的一些不相交的区间（不一定要用区间覆盖整个序列）。处于同一区间的人会在同一节火车车厢。选择区间的方式需满足：如果至少有一个人前往城市\(x\)，那么所有要去城市\(x\)的人都应该在同一节火车车厢。这意味着他们不能属于不同的区间。注意，所有前往城市\(x\)的人，要么都在同一节车厢前往该城市，要么都不去。

从位置\(l\)到位置\(r\)的区间内人员的火车旅行舒适度等于该区间内所有不同城市代码的异或值。异或操作也称为按位异或。

火车旅行的总舒适度等于每个区间的舒适度之和。

帮助弗拉迪克求出最大可能的总舒适度。

## 说明/提示
在第一个测试用例中，最佳的区间划分是：\([4,4]\)  \([2,5,2]\)  \([3]\)，答案计算如下：\(4+(2 \text{ xor } 5)+3=4 + 7+3=14\)

在第二个测试用例中，最佳的区间划分是：\(5\)  \(1\)  \([3]\)  \(1\)  \(5\)  \([2,4,2]\)  \(5\)，答案计算如下：\(3+(2 \text{ xor } 4)=3 + 6=9\) 。

## 样例 #1
### 输入
```
6
4 4 2 5 2 3
```
### 输出
```
14
```
## 样例 #2
### 输入
```
9
5 1 3 1 5 2 4 2 5
```
### 输出
```
9
```

### 算法分类
动态规划

### 综合分析与结论
三道题解均采用动态规划算法解决问题，核心思路都是通过枚举区间并判断区间合法性来进行状态转移，以求出最大总舒适度。不同之处在于对区间合法性判断的处理方式以及状态转移方程的具体实现。hwk0518通过预处理和特定的区间DP转移方式优化了计算过程；lgx57利用set数据结构来优化区间合法性判断；猪小屁则采用较为直接的暴力枚举和判断方式。

### 所选的题解
- **作者：hwk0518 (5星)**
    - **关键亮点**：通过定义\(g[i][j]\)和\(f[i][j]\)进行区间DP，利用预处理数组\(l\)、\(r\)、\(cnt\)优化区间合法性判断和舒适度计算，整体思路清晰，代码结构完整，优化程度高。
    - **重点代码核心思想**：`init`函数用于初始化输入数据并预处理每个城市代码的出现次数、最左和最右位置；`calc`函数计算合法区间的舒适度并填充\(f\)数组；`work`函数通过区间DP和最终的状态转移计算最大总舒适度。
    - **核心代码片段**：
```cpp
void init()
{
    int i,j;
    scanf("%d",&n);
    for(i=1;i<=n;++i)
        scanf("%d",&a[i]),++cnt[a[i]];
    for(i=n;i;--i) l[a[i]]=i;
    for(i=1;i<=n;++i) r[a[i]]=i; 
}

void calc(int lpos)
{
    int i,nowri=0,nowcnt=0;
    for(i=5000;~i;--i) used[i]=0;
    int now=0;
    for(i=lpos;i<=n;++i)
        if(!used[a[i]])
        {
            used[a[i]]=1;now^=a[i];
            if(l[a[i]]<lpos) return;
            nowri=max(nowri,r[a[i]]);
            nowcnt+=cnt[a[i]];
            if(nowri-lpos+1==nowcnt) f[lpos][nowri]=now;
        }
}

void work()
{
    int i,j,len,l,r;
    for(i=1;i<=n;++i) calc(i);
    for(len=2;len<=n;++len)
        for(l=1;l<=n-len+1;++l)
        {
            r=l+len-1;
            f[l][r]=max(f[l][r],max(f[l][r-1],f[l+1][r]));
        }
        
    for(i=1;i<=n;++i)
        for(j=0;j<i;++j)
            dp[i]=max(dp[i],dp[j]+f[j+1][i]);
    
    int ans=0;
    for(i=1;i<=n;++i) ans=max(ans,dp[i]);
    printf("%d\n",ans);
}
```
- **作者：lgx57 (4星)**
    - **关键亮点**：利用set数据结构优化区间合法性判断，在判断区间合法时，将已判断过的合法元素从set中删除，减少后续判断次数，代码简洁明了。
    - **重点代码核心思想**：通过`num`数组统计每个城市代码的总出现次数，在枚举区间时，将区间内元素插入set，遍历set判断每个元素在区间内出现次数是否等于总次数，以确定区间合法性并进行状态转移。
    - **核心代码片段**：
```cpp
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n;
    cin>>n;
    for (int i=1;i<=n;i++) cin>>a[i];
    for (int i=1;i<=n;i++) num[a[i]]++,ma=max(ma,a[i]);
    for (int i=1;i<=n;i++){
        for (int _=0;_<=ma;_++) cnt[_]=0;
        int sum=0;
        set<int> s;
        for (int j=i;j>=1;j--){
            bool f=1;
            if (!cnt[a[j]]) sum^=a[j],s.insert(a[j]);
            cnt[a[j]]++;
            vector<int> v;
            for (int x:s){
                if (cnt[x]!=num[x]){
                    f=0;
                    break;
                }
                else v.pb(x);
            }
            for (int x:v) s.erase(x);
            if (f) dp[i]=max(dp[j-1]+sum,dp[i]);
        }
        dp[i]=max(dp[i],dp[i-1]);
    }
    cout<<dp[n];
    return 0;
}
```

### 最优关键思路或技巧
1. **预处理优化**：如hwk0518通过预处理每个城市代码的出现次数、最左和最右位置，在后续判断区间合法性和计算舒适度时减少重复计算。
2. **数据结构优化**：lgx57利用set数据结构，在判断区间合法性时，动态删除已确认合法的元素，避免重复判断，提高效率。

### 可拓展思路
此类题目属于动态规划中区间相关问题，类似套路包括通过预处理减少重复计算、利用合适的数据结构优化判断过程。同类型题目通常围绕区间划分、合并等操作，在满足一定条件下求最优值。

### 洛谷相似题目推荐
1. P1880 [石子合并](https://www.luogu.com.cn/problem/P1880)
2. P3146 [USACO16OPEN]248 G](https://www.luogu.com.cn/problem/P3146)
3. P1063 [能量项链](https://www.luogu.com.cn/problem/P1063)

### 个人心得摘录与总结
无

---
处理用时：58.11秒