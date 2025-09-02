# 题目信息

# [USACO20OPEN] Cowntact Tracing B

## 题目描述

由于高传染性的牛传染病 COWVID-19 的爆发，Farmer John 非常担忧他的奶牛们（编号为 $1\ldots N$）的健康。

最近，Farmer John 对他的所有奶牛进行了检测，发现有一部分奶牛对该疾病的检测结果呈阳性。利用牛棚内的视频监控，他得以查看最近的奶牛之间的互动行为，结果发现奶牛们互相打招呼时，她们会握蹄，不幸的是这是一种会将疾病从一头奶牛传播给另一头奶牛的行为。Farmer John 汇总了一个添加了时间戳的清单，每条数据的形式为 $(t,x,y)$，表示在时间 $t$，奶牛 $x$ 与奶牛 $y$ 握了蹄。Farmer John 同时还知道以下信息：

（一）他的农场上恰有一头奶牛最初带有携带疾病（我们将这头奶牛称为“零号病人”）。

（二）一旦一头奶牛被感染，她会在接下来的 $K$ 次握蹄中传染疾病（可能会与同一头奶牛握蹄多次）。握蹄 $K$ 次后，她不再在此后的握蹄中传染疾病（因为此时她意识到了她会传染疾病，于是会仔细地洗蹄）。

（三）一旦一头奶牛被感染，她会持续处于被感染状态。

不幸的是，Farmer John 不知道他的 $N$ 头奶牛中的哪一头是零号病人，也不知道 $K$ 的值！基于他的数据，请帮助他缩小这些未知量的范围。保证至少有一种可能的情况。 

## 说明/提示

### 样例解释 1

唯一可能是零号病人的是奶牛 $1$。对于所有的 $K>0$，奶牛 $1$ 在时刻 $7$ 感染奶牛 $2$，而奶牛 $3$ 和奶牛 $4$ 均不会被感染。 

## 样例 #1

### 输入

```
4 3
1100
7 1 2
5 2 3
6 2 4```

### 输出

```
1 1 Infinity```

# AI分析结果

• 综合分析与结论：
    - 思路：所有题解均基于暴力枚举思路，由于题目给定数据范围较小（$N \leq 100$，$T \leq 250$），通过枚举零号病人（$1$到$N$）和$K$值（$1$到$T + 1$），再按时间顺序模拟奶牛握手传染疾病过程，判断是否与给定的感染结果字符串一致，从而确定可能的零号病人数量及$K$的范围。
    - 算法要点：排序时间戳数据，双重循环枚举零号病人和$K$值，在模拟过程中根据规则更新奶牛感染状态及传染次数。
    - 解决难点：主要难点在于准确模拟疾病传播规则，包括初始感染、传染次数限制及感染状态保持，同时要注意每次模拟时状态的初始化。
    - 整体来看，各题解思路相似，质量差异主要体现在代码清晰度和实现细节上。

所选的题解：
  - 作者：mengleo (5星)
    - 关键亮点：思路清晰，代码简洁明了，对$K$上限判断及输出处理得当，时间复杂度分析准确。
    - 核心代码片段：
```cpp
bool cmp(lst_t x, lst_t y)
{
    return x.t < y.t;
}

signed main()
{
    cin >> n >> t >> s;
    for(int i = 1; i <= t; i++)
    {
        cin >> lst[i].t >> lst[i].x >> lst[i].y;
    }
    sort(lst + 1, lst + 1 + t, cmp);
    for(int z = 1; z <= n; z++)
    {
        bool f = 0;
        for(int k = 0; k <= t + 1; k++)
        {
            bool f2 = 1;
            int cs[n + 5] = {};
            memset(cs, -1, sizeof(cs));
            cs[z] = k;
            for(int i = 1; i <= t; i++)
            {
                if(cs[lst[i].x] == -1 && cs[lst[i].y] > 0)
                {
                    cs[lst[i].y]--;
                    cs[lst[i].x] = k;
                }
                else if(cs[lst[i].y] == -1 && cs[lst[i].x] > 0)
                {
                    cs[lst[i].x]--;
                    cs[lst[i].y] = k;
                }
                else if(cs[lst[i].x] >= 0 && cs[lst[i].y] >= 0)
                {
                    cs[lst[i].x] = max(0ll, cs[lst[i].x] - 1);
                    cs[lst[i].y] = max(0ll, cs[lst[i].y] - 1);
                }
            }
            for(int i = 1; i <= n; i++)
            {
                if((s[i - 1] == '1' && cs[i] == -1) || (s[i - 1] == '0' && cs[i]!= -1))
                {
                    f2 = 0;
                }
            }
            if(f2)
            {
                mx = max(mx, k);
                mn = min(mn, k);
                f = 1;
            }
        }
        cnt += f;
    }
    cout << cnt << " " << mn;
    if(mx == t + 1)
    {
        cout << " Infinity";
    }
    else
    {
        cout << " " << mx;
    }
    
    return 0;
}
```
    - 核心实现思想：先对时间戳数据按时间排序，然后枚举零号病人$z$和$K$值$k$，每次模拟初始化奶牛感染状态数组$cs$，在遍历时间戳模拟感染过程中，根据奶牛感染状态更新传染次数及感染状态，最后检查模拟结果与输入字符串是否一致，统计符合条件的零号病人数量及$K$的范围。

  - 作者：XiaoWhy (4星)
    - 关键亮点：代码结构清晰，变量命名有一定可读性，对模拟过程和结果判断逻辑清晰。
    - 核心代码片段：
```cpp
void check(int x){
    bool yes=false;
    for(int k=0;k<=t+1;k++){
        memset(st,false,sizeof st);
        memset(cnt,0,sizeof cnt);
        cnt[x]=k,st[x]=true;
        bool ok=true;
        for(int i=1;i<=t;i++){
            int x=tr[i].x,y=tr[i].y;
            if(cnt[x]>0||cnt[y]>0){
                cnt[x]--,cnt[y]--;
                if(s[x]=='0'||s[y]=='0'){
                    ok=false;
                    break;
                }else{
                    if(!st[x]) st[x]=true,cnt[x]=k;
                    if(!st[y]) st[y]=true,cnt[y]=k;
                }
            }
        }
        for(int i=1;i<=n;i++){
            if(st[i]==true&&s[i]=='0') ok=false;
            if(st[i]==false&&s[i]=='1') ok=false;
        }
        if(ok) mi=min(mi,k),mx=max(mx,k),yes=true;
    }
    if(yes) ans++;
}
```
    - 核心实现思想：`check`函数用于检查以$x$为零号病人时不同$K$值的情况，每次初始化奶牛感染状态数组`st`和传染次数数组`cnt`，在模拟感染过程中，根据传染条件更新状态，最后检查模拟结果与输入字符串是否一致，更新符合条件的$K$值范围并统计零号病人数量。

  - 作者：huhangqi (4星)
    - 关键亮点：对状态设置及$K$为$0$的特殊情况有考虑，逻辑较为完整。
    - 核心代码片段：
```cpp
for(int i=1;i<=n;i++){
    memset(f,0,sizeof(f));
    f[i]=1;
    bool fl=false;
    for(int k=1;k<=n;k++){
        if(f[k]&&!vis[k]||!f[k]&&vis[k]){
            fl=true;
            break;
        }
    }
    if(!fl){
        if(!to[i]){
            to[i]=1;
            ans++;
        }
        ans2=min(ans2,0ll);
        ans3=max(ans3,0ll);
    }
    for(int j=1;j<=t;j++){
        memset(f,0,sizeof(f));
        f[i]=j;
        for(int k=1;k<=t;k++){
            int x=f[a[k].x],y=f[a[k].y];
            if(x>0){
                f[a[k].x]--;
                if(!f[a[k].x])f[a[k].x]=-1;
                if(y==0)f[a[k].y]=j;
            }
            if(y>0){
                f[a[k].y]--;
                if(!f[a[k].y])f[a[k].y]=-1;
                if(x==0)f[a[k].x]=j;
            }
        }
        bool fl=false;
        for(int k=1;k<=n;k++){
            if(f[k]&&!vis[k]||!f[k]&&vis[k]){
                fl=true;
                break;
            }
        }
        if(!fl){
            if(!to[i]){
                to[i]=1;
                ans++;
            }
            ans2=min(ans2,j);
            ans3=max(ans3,j);
        }
    }
}
```
    - 核心实现思想：外层循环枚举零号病人$i$，先检查$K = 0$时的情况，再枚举$K$值$j$，每次初始化感染状态数组$f$，在模拟感染过程中根据奶牛感染状态更新传染次数及感染状态，最后检查模拟结果与输入字符串是否一致，统计符合条件的零号病人数量及$K$的范围。

最优关键思路或技巧：利用题目数据范围小的特点，采用暴力枚举的方法，通过合理的数据结构和清晰的模拟逻辑解决问题。在实现过程中，注意状态的初始化和对特殊情况（如$K = 0$）的处理。

可拓展之处：此类题目属于模拟与枚举结合的类型，类似套路可用于解决一些状态有限且数据范围小的问题，如一些简单的传染病传播模型、资源分配方案枚举等。

推荐洛谷题目：
  - P1162 填涂颜色
  - P1036 选数
  - P1433 吃奶酪

个人心得：无。 

---
处理用时：39.22秒