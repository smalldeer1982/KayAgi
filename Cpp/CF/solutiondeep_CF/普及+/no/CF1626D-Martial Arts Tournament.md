# 题目信息

# Martial Arts Tournament

## 题目描述

Monocarp is planning to host a martial arts tournament. There will be three divisions based on weight: lightweight, middleweight and heavyweight. The winner of each division will be determined by a single elimination system.

In particular, that implies that the number of participants in each division should be a power of two. Additionally, each division should have a non-zero amount of participants.

 $ n $ participants have registered for the tournament so far, the $ i $ -th of them weighs $ a_i $ . To split participants into divisions, Monocarp is going to establish two integer weight boundaries $ x $ and $ y $ ( $ x < y $ ).

All participants who weigh strictly less than $ x $ will be considered lightweight. All participants who weigh greater or equal to $ y $ will be considered heavyweight. The remaining participants will be considered middleweight.

It's possible that the distribution doesn't make the number of participants in each division a power of two. It can also lead to empty divisions. To fix the issues, Monocarp can invite an arbitrary number of participants to each division.

Note that Monocarp can't kick out any of the $ n $ participants who have already registered for the tournament.

However, he wants to invite as little extra participants as possible. Help Monocarp to choose $ x $ and $ y $ in such a way that the total amount of extra participants required is as small as possible. Output that amount.

## 说明/提示

In the first testcase of the example, Monocarp can choose $ x=2 $ and $ y=3 $ . Lightweight, middleweight and heavyweight divisions will have $ 2 $ , $ 1 $ and $ 1 $ participants, respectively. They all are powers of two, so no extra participants are required.

In the second testcase of the example, regardless of the choice of $ x $ and $ y $ , one division will have $ 1 $ participant, the rest will have $ 0 $ . Thus, Monocarp will have to invite $ 1 $ participant into both of the remaining divisions.

In the third testcase of the example, Monocarp can choose $ x=1 $ and $ y=2 $ . Lightweight, middleweight and heavyweight divisions will have $ 0 $ , $ 3 $ and $ 3 $ participants, respectively. So an extra participant is needed in each division.

In the fourth testcase of the example, Monocarp can choose $ x=8 $ and $ y=9 $ . Lightweight, middleweight and heavyweight divisions will have $ 8 $ , $ 0 $ and $ 0 $ participants, respectively. Middleweight and heavyweight division need an extra participant each.

## 样例 #1

### 输入

```
4
4
3 1 2 1
1
1
6
2 2 2 1 1 1
8
6 3 6 3 6 3 6 6```

### 输出

```
0
2
3
2```

# AI分析结果

### 题目中文重写
# 武术锦标赛

## 题目描述
Monocarp 计划举办一场武术锦标赛。比赛将根据体重分为三个级别：轻量级、中量级和重量级。每个级别的冠军将通过单淘汰制产生。

特别地，这意味着每个级别的参赛人数应该是 2 的幂次方。此外，每个级别都应该有非零数量的参赛人员。

到目前为止，已经有 $n$ 名选手报名参加锦标赛，第 $i$ 名选手的体重为 $a_i$。为了将选手划分到不同级别，Monocarp 打算设定两个整数体重界限 $x$ 和 $y$（$x < y$）。

所有体重严格小于 $x$ 的选手将被视为轻量级选手。所有体重大于或等于 $y$ 的选手将被视为重量级选手。其余选手将被视为中量级选手。

可能出现的情况是，这样的划分并不能使每个级别的参赛人数都是 2 的幂次方，也可能导致某些级别没有选手。为了解决这些问题，Monocarp 可以邀请任意数量的选手加入每个级别。

请注意，Monocarp 不能淘汰任何已经报名参加锦标赛的 $n$ 名选手。

然而，他希望邀请的额外选手数量尽可能少。请帮助 Monocarp 选择 $x$ 和 $y$，使得所需的额外选手总数尽可能少，并输出这个数量。

## 说明/提示
在示例的第一个测试用例中，Monocarp 可以选择 $x = 2$ 和 $y = 3$。轻量级、中量级和重量级别的参赛人数分别为 2、1 和 1。它们都是 2 的幂次方，因此不需要额外的选手。

在示例的第二个测试用例中，无论 $x$ 和 $y$ 如何选择，一个级别将有 1 名选手，其余级别将有 0 名选手。因此，Monocarp 必须邀请 1 名选手加入其余两个级别。

在示例的第三个测试用例中，Monocarp 可以选择 $x = 1$ 和 $y = 2$。轻量级、中量级和重量级别的参赛人数分别为 0、3 和 3。因此，每个级别都需要额外邀请 1 名选手。

在示例的第四个测试用例中，Monocarp 可以选择 $x = 8$ 和 $y = 9$。轻量级、中量级和重量级别的参赛人数分别为 8、0 和 0。中量级和重量级别的每个级别都需要额外邀请 1 名选手。

## 样例 #1
### 输入
```
4
4
3 1 2 1
1
1
6
2 2 2 1 1 1
8
6 3 6 3 6 3 6 6
```

### 输出
```
0
2
3
2
```

### 算法分类
枚举

### 综合分析与结论
这些题解的核心思路都是通过枚举不同的划分方式，计算每个划分下需要额外邀请的选手数量，最后取最小值。不同题解的区别在于枚举的方式和计算额外选手数量的方法。

dottle 的题解通过预处理 $f$ 和 $g$ 数组，快速计算出每个划分下各段的人数；XL4453 的题解使用前缀和和二分查找，在枚举前两个组别的人数后，计算出最后一个组需要的人数；daniEl_lElE 的题解通过排序和离散化，枚举每一段的长度，二分查找最优划分；AlicX 的题解枚举第一个断点，再枚举离第二段人数最近的 $2^j$，二分找出断点；徐天乾的题解枚举两个 2 的幂次表示前后两段的人数，再计算中间段的人数。

### 所选题解
- **dottle 的题解（5星）**：
    - **关键亮点**：思路清晰，通过预处理 $f$ 和 $g$ 数组，在枚举 2 的幂次作为各段长度时，能快速计算出各段原有的选手数量，时间复杂度为 $O(n)$。
- **XL4453 的题解（4星）**：
    - **关键亮点**：从反面出发，枚举前两个组别的人数，利用前缀和和二分查找计算最后一个组需要的人数，贪心策略合理。
- **daniEl_lElE 的题解（4星）**：
    - **关键亮点**：观察到 2 的幂次增长速度快，通过枚举每段的长度并二分查找，将复杂度优化到 $O(\log^3n)$。

### 重点代码
#### dottle 的题解
```cpp
void solve(){
    int n;cin>>n;
    vector<int> a(n+1),f(n+1),g(n+1);
    for(int i=1;i<=n;i++){
        int x;cin>>x;a[x]++;
    }
    for(int i=1,s=0;i<=n;i++){
        for(int j=s;j<s+a[i];j++)f[j]=s;
        s+=a[i];
    }f[n]=n;
    for(int i=n,s=0;i;i--){
        for(int j=s;j<s+a[i];j++)g[j]=s;
        s+=a[i];
    }g[n]=n;
    int ans=1e9;
    for(int a=1;a<=n;a<<=1)	
        for(int b=1;b<=n;b<<=1){
            int x=f[a],y=g[b];
            int ac=1;while(ac<n-x-y)ac<<=1;
            ans=min(ans,a+b+ac);
        }
    cout<<ans-n<<endl;
}
```
**核心实现思想**：先统计每个体重的人数，然后预处理 $f$ 和 $g$ 数组，分别表示选出至多 $i$ 个最小的数和最大的数时，能选出的实际人数。接着枚举 2 的幂次作为第一、三段的长度，利用 $f$ 和 $g$ 数组计算出第一、三段原有的选手数量，从而得到第二段原有的选手数量，再计算出第二段需要补充到 2 的幂次的人数，最后取所有情况的最小值。

#### XL4453 的题解
```cpp
int calc(int num){
    int now=1;
    while(now<num)now*=2;
    return now;
}
signed main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        for(int i=1;i<=n;i++)t[i]=0;
        for(int i=1;i<=n;i++){
            scanf("%d",&x);
            t[x]++;
        }
        for(int i=1;i<=n;i++)
            t[i]+=t[i-1];
        ans=2147483647;
        for(int i=1;i<=n;i=i<<1){
            for(int j=1;j<=n;j=j<<1){
                int p1=upper_bound(t+1,t+n+1,i)-t;p1--;
                int p2=upper_bound(t+1,t+n+1,t[p1]+j)-t;p2--;
                ans=min(ans,i+j+calc(n-t[p2])-n);
            }
        }
        printf("%I64d\n",ans);
    }
    return 0;
}
```
**核心实现思想**：先统计每个体重的人数，然后求前缀和。枚举前两个组别的人数，通过二分查找找到能放置的最大位置，计算出最后一个组需要的人数，取所有情况的最小值。

#### daniEl_lElE 的题解
```cpp
signed main(){
    cin.tie();
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        int a[n+2];
        for(int i=1;i<=n;i++){
            cin>>a[i];
        }
        int b[n+2],k=0;
        sort(a+1,a+n+1);
        b[0]=0;
        a[n+1]=998244353;
        for(int i=1;i<=n;i++){
            int j=i;
            while(a[i]==a[i+1]){
                i++;
            }
            k++;
            b[k]=i-j+1;
            b[k]+=b[k-1];
        }
        b[0]=0;
        b[k+1]=1145141919810;
        int minv=1145141919810;
        for(int i=0;i<=20;i++){
            for(int j=0;j<=20;j++){
                for(int ll=0;ll<=20;ll++){
                    int l=(1<<i);
                    int pos=upper_bound(b+1,b+k+2,l)-b-1;
                    int cha=l-b[pos];
                    int l2=(1<<j);
                    int pos2=upper_bound(b+1,b+k+2,l2+b[pos])-b-1;
                    cha+=(l2+b[pos]-b[pos2]);
                    int l3=(1<<ll);
                    int pos3=upper_bound(b+1,b+k+2,l3+b[pos2])-b-1;
                    cha+=(l3+b[pos2]-b[pos3]);
                    if(pos3==k){
                        minv=min(minv,cha);
                    }
                }
            }
        }
        cout<<minv<<endl;
    }
    return 0;
}
```
**核心实现思想**：先对选手体重排序并离散化，然后枚举每一段的长度，通过二分查找找到最优划分，计算出需要补充的人数，取所有情况的最小值。

### 最优关键思路或技巧
- 利用枚举 2 的幂次来减少枚举量，避免直接枚举断点导致的高复杂度。
- 预处理数组（如前缀和数组、$f$ 和 $g$ 数组），快速计算各段的人数。
- 运用二分查找来确定最优划分位置。

### 拓展思路
同类型题可能会有不同的分组规则或限制条件，但核心思路仍然是通过枚举和计算来找到最优解。类似算法套路包括枚举不同的状态，利用数据结构（如前缀和、二分查找）来优化计算过程。

### 推荐洛谷题目
- P1002 [NOIP2002 普及组] 过河卒
- P1216 [USACO1.5] [IOI1994] 数字三角形 Number Triangles
- P1434 [SHOI2002] 滑雪

### 个人心得摘录与总结
daniEl_lElE 的题解中提到“当然比赛时我没有时间继续优化，写了一个 $O(\log^4n)$ 的算法，速度同样十分优秀”，总结为在比赛中如果时间有限，可先实现一个复杂度稍高但能解决问题的算法，后续再考虑优化。 

---
处理用时：67.27秒