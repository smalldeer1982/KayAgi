# 题目信息

# Divan and a New Project

## 题目描述

有 $n + 1$ 座的建筑，编号从 $0\sim n$。

有一个人从编号为 $0$ 的建筑出发， 分别要去编号为 $i$ 的建筑 $a_i$ 次。

设编号为 $i$ 的建筑坐标为 $x_i$， 这个人往返编号为 $i$ 的建筑一趟花费的时间为 $2 \times|x_i - x_0|$ 。

求如何安排这 $n + 1$ 座建筑的坐标， 使这个人在路上花费的总时间最小。

## 说明/提示

对于 $100\%$ 的数据，$1 \le t \le 10^3$，$1 \le n \le 2 \cdot 10^5$，$\sum n \le 2 \cdot 10^5$，$0 \le a_i \le 10^6$，$-10^6 \le x_i \le 10^6$。

## 样例 #1

### 输入

```
4
3
1 2 3
5
3 8 10 6 1
5
1 1 1 1 1
1
0```

### 输出

```
14
2 4 1 3
78
1 -1 0 2 3 4
18
3 6 1 5 2 4
0
1 2```

# AI分析结果

### 题目内容
# Divan和一个新项目

## 题目描述
有 \(n + 1\) 座建筑，编号从 \(0\sim n\) 。
有一个人从编号为 \(0\) 的建筑出发，分别要去编号为 \(i\) 的建筑 \(a_i\) 次。
设编号为 \(i\) 的建筑坐标为 \(x_i\) ，这个人往返编号为 \(i\) 的建筑一趟花费的时间为 \(2 \times|x_i - x_0|\) 。
求如何安排这 \(n + 1\) 座建筑的坐标，使这个人在路上花费的总时间最小。

## 说明/提示
对于 \(100\%\) 的数据，\(1 \le t \le 10^3\)，\(1 \le n \le 2 \cdot 10^5\)，\(\sum n \le 2 \cdot 10^5\)，\(0 \le a_i \le 10^6\)，\(-10^6 \le x_i \le 10^6\) 。

## 样例 #1
### 输入
```
4
3
1 2 3
5
3 8 10 6 1
5
1 1 1 1 1
1
0
```
### 输出
```
14
2 4 1 3
78
1 -1 0 2 3 4
18
3 6 1 5 2 4
0
1 2
```
### 算法分类
贪心

### 题解综合分析与结论
这些题解的核心思路均为贪心策略，即让访问次数 \(a_i\) 越多的建筑距离编号为 \(0\) 的建筑越近，从而使总时间最小。算法要点在于将建筑按访问次数从大到小排序，然后在编号为 \(0\) 的建筑两侧交替分配坐标（如 \(1, -1, 2, -2, \cdots\) ）。解决难点在于理解并证明这种贪心策略的正确性，部分题解通过反证法证明交换距离会使总时间增加，从而验证了该策略。在实现上，不同题解在细节处理和代码风格上略有差异，但整体逻辑一致。

### 所选的题解
- **作者：Otue (5星)**
    - **关键亮点**：思路阐述详细，通过模拟样例帮助理解贪心策略，代码实现清晰，对坐标分配过程有详细注释。
    - **个人心得**：无
    ```c++
    #include<bits/stdc++.h>
    using namespace std;
    #define int long long
    int T;
    int n;
    struct stu{
        int x,id;     //id是编号
    }ed[200005];
    int a[200005],ans;
    bool cmp(stu x,stu y){  //从大到小排序
        return x.x>y.x;
    }
    signed main(){
        cin>>T;
        while(T--){
            ans=0;
            memset(a,0,sizeof a);
            cin>>n;
            for(int i=1;i<=n;i++){
                cin>>ed[i].x;
                ed[i].id=i;
            }
            a[1]=0;     //不妨他总部为0，即x0
            sort(ed+1,ed+n+1,cmp);
            int tmp=1;
            for(int i=1;i<=n;i++){
                ans+=2*abs(tmp)*ed[i].x; //算答案
                a[ed[i].id]=tmp;
                if(tmp>0){//以下在模拟1,-1,2,-2,3....的过程
                    if(i%2==1) tmp=-tmp;
                    else if(i%2==0) tmp++;
                }
                else if(tmp<0){
                    if(i%2==1) tmp=-tmp;
                    else if(i%2==0) tmp--;
                }

            }
            cout<<ans<<endl;
            for(int i=0;i<=n;i++) cout<<a[i]<<' ';
            puts("");
        }
    }
    ```
- **作者：MeowScore (4星)**
    - **关键亮点**：简洁明了地阐述思路，代码结构清晰，变量命名有一定可读性。
    - **个人心得**：提醒要开 `long long`。
    ```c++
    #include<bits/stdc++.h>
    using namespace std;
    #define int long long
    struct Building{
        int id;
        int vis;
    }a[200010];
    int ans[200010];
    int cmp(Building aa,Building bb){
        return aa.vis>bb.vis;
    }
    signed main(){
        int T;
        cin>>T;
        while(T--){
            int n;
            cin>>n;
            for(int i=1;i<=n;i++){
                a[i].id=i;
                cin>>a[i].vis;
            }
            sort(a+1,a+n+1,cmp);
            int tot=0;
            int nw=1;
            for(int i=1;i<=n;i++){
                ans[a[i].id]=nw;
                tot+=(abs(nw)*2*a[i].vis);
                if(nw>0)
                    nw=-nw;
                else
                    nw=-nw+1;
            }
            cout<<tot<<endl;
            cout<<0<<' ';
            for(int i=1;i<=n;i++)
                cout<<ans[i]<<' ';
            cout<<endl;
        }
        return 0;
    }
    ```
- **作者：xiaomuyun (4星)**
    - **关键亮点**：对题意和题目分析清晰，代码实现中对左右放置建筑的逻辑处理明确。
    - **个人心得**：提醒开 `long long`，分享因未开 `long long` 导致错误的教训。
    ```cpp
    #include<algorithm>
    #include<cstring>
    #include<cstdio>
    using namespace std;
    struct node{
        long long val,id;
    }a[200010];
    long long t,n,ans[200010];
    bool cmp(const node &a,const node &b){
        return a.val>b.val;
    }
    int main(){
        scanf("%lld",&t);
        while(t--){
            scanf("%lld",&n);
            for(long long i=1;i<=n;++i){
                scanf("%lld",&a[i].val);
                a[i].id=i;
            }
            memset(ans,0,sizeof ans);
            sort(a+1,a+1+n,cmp);//从大到小排序
            long long lcnt=0,rcnt=0,res=0;
            for(long long i=1;i<=n;++i){
                if(lcnt==rcnt){//往右放建筑
                    res+=2*(rcnt+1)*a[i].val;//求出访问第i个建筑需要的时间
                    ans[a[i].id]=++rcnt;
                } else {//往左放建筑
                    res+=2*(lcnt+1)*a[i].val,ans[a[i].id]=0-lcnt-1,++lcnt;//和上面一样
                }//存答案
            }
            printf("%lld\n",res);
            for(long long i=0;i<=n;++i) printf("%lld ",ans[i]);
            putchar('\n');
        }
        return 0;
    }
    ```

### 最优关键思路或技巧
1. **贪心策略**：基于总时间的计算式 \(2\times |x_i - x_0|\times a_i\)，固定 \(a_i\) 后，让 \(|x_i - x_0|\) 随 \(a_i\) 的增大而减小，从而使总时间最小。
2. **交替分配坐标**：将 \(x_0\) 设为 \(0\) 后，对按 \(a_i\) 从大到小排序的建筑，在 \(0\) 两侧交替分配坐标 \(1, -1, 2, -2, \cdots\)，保证访问次数多的建筑离 \(0\) 号建筑更近。

### 拓展
同类型题通常围绕贪心策略展开，特点是存在某种可优化的目标函数，通过局部最优选择能达到全局最优。例如，在资源分配、任务调度等场景下，根据某个关键因素（如时间、成本等）对元素进行排序，然后按一定规则分配资源以达到最优结果。

### 相似知识点洛谷题目
1. [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)：通过对数据进行合理排序，运用贪心策略解决问题。
2. [P1199 三国游戏](https://www.luogu.com.cn/problem/P1199)：需要分析游戏规则，利用贪心思想找到最优策略。
3. [P2859 [USACO06DEC]Milk Patterns G](https://www.luogu.com.cn/problem/P2859)：结合字符串处理和贪心算法来解决问题。 

---
处理用时：51.79秒