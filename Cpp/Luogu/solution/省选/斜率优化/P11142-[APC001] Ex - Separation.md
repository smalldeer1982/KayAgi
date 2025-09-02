# [APC001] Ex - Separation

## 题目描述

小 I 有 $n$ 个工厂，坐落在 $A$ 地到 $B$ 地，第 $i$ 个工厂距离 $A$ 地的距离为 $a_i$ 千米。加工厂位于 $B$ 地，距离 $A$ 地 $x$ 千米，小 I 要把这些工厂里的货物运送到 $B$ 地的加工厂。

但是这天下了暴雨，仓库里的货物受潮了，每份货物每在仓库中或小 I 的背包中存放 $1$ 分钟，价值就会减少 $m$ 元钱。已知今天晚上每个工厂会生产出 $b_i$ 份货物，也知道每份货物会在暴雨来临几分钟后生产出来。

小 I 的初始体力为 $c$，速度为每分钟 $1$ 千米，但是他每行走 $1$ 千米就会减少一点体力（当体力为 $0$ 时不允许行走）。每次出发小 I 都要从 $A$ 地前往 $B$ 地，再返回 $A$ 地，他**只**在从 $A$ 地前往 $B$ 地时会带走沿途的工厂的仓库内所有被生产出的货物。他到达 $A$ 地后可以立刻再次出发。特别的，他可以在**负数时间点**出发，假定他的背包是无限大的，且货物重量与体力消耗无关。

小 I 为了亏损更少，制造了一个分身制造器。这个机器可以制造无数个他的分身，但是每一次出发最多只能制造一个分身，制造的分身与本体共用体力，**完全遵循第 $3$ 段所描述的操作**。小 I 需要保证在任何时候，现有体力都能支持每一个分身（包括本体）返回 $A$ 地的家。

小 I 做完准备工作后，发现暴雨已经下了 $k$ 分钟了，他迫切想要知道他最少要亏损（即货物减少的价值）多少元。他不会这个问题，于是他向你求助，想让你给出一种方案。

## 说明/提示

**【样例解释】**

对于样例 $3$ 的第一组数据解释：

小 I 在暴雨来临后 $1$ 分钟向你求助，你给出的方案是在暴雨来临后 $3$ 分钟，小 I 出门，在 $4$ 分钟到达 $1$ 号仓库，在 $5$ 分钟到达 $B$ 地，在 $7$ 分钟回到家，亏损 $3$ 元。

**【数据范围】**

对于全部数据，保证 $1\leq t\leq 10$，$1\leq n\leq 2\times 10^5,1\leq m,k,x\leq 10^6$，$1\le a_i\le x$，$0\leq c\leq 200$，$1\leq b_i\leq 10^5$，$\sum b_i\leq 2\times 10^5$，$0\leq t_{i,j}\leq 10^6$。

**本题输入量较大，请使用较快的读入方式。**

本题题面已更新，[赛时原题面](https://www.luogu.com.cn/paste/iebvx9ko)

## 样例 #1

### 输入

```
1
1 2 2 5 1
1
2
3 4```

### 输出

```
6
2 0
-1 -1```

## 样例 #2

### 输入

```
1
1 1 1 5 1
1
2
3 4```

### 输出

```
0
1 0
2 1
-1 -1```

## 样例 #3

### 输入

```
4
1 1 2 5 1
1
2
3 4
1 1 4 8 2
1
2
5 8
2 2 3 9 9
1 2
2 1
3 7
5
1 1 2 8 4
1
3
1 2 3```

### 输出

```
3
2 0
-1 -1
9
5 0
-1 -1
24
-3 0
-1 -1
4
-3 0
-2 1
-1 -1```

# 题解

## 作者：ivyjiao (赞：6)

先考虑什么时候无解：当 $c<2\times x$ 时，ivyjiao 出不了门，取不了货物。有特例为 $\sum_{i=1}^{i\leq n}b_i=0$ 时，根本没有货物，此时要输出 $0$。

再考虑怎样能够让一份货物的亏损最少。由于一份货物的所处位置分为“在仓库中”和“在 ivyjiao 的背包中”，而第二段的时间是一定的，就是 $x-a_i$，$i$ 为这份货物在哪个工厂生产出来，所以第二段的亏损也是一定的，就是 $m\times(x-a_i)$。综上所述，可知这一段总的亏损也是一定的，就是：

$$\sum_{i=1}^{i\leq n}b_i\times m\times(x-a_i)$$

而第一段的时间是可控的，最小是 $0$，也就是这份货物刚被生产出来，就被 ivyjiao 取走了。接下来我们只考虑第一段的亏损。

由于有分身制造器，我们可以随意往返。接下来我们还能发现总共往返的次数也是一定的，因为初始体力不变，是 $c$，中途没有恢复体力的手段，往返一次消耗的体力也是一定的，是 $2\times x$，又因为需要保证在任何时候，现有体力都能支持每一个分身（包括本体）返回 $A$ 地，所以总共能往返 $\lfloor\dfrac{c}{2\times x}\rfloor$ 次。

由上述两个性质，我们可以看出每次往返必能正好取走至少一份货物，因为如果一份货物都不能正好取走，我们定能通过改变出发时间来让这次往返正好取走至少一份货物，而这样肯定是更优的。

为了方便计算，我们对于每份货物，计算出它在什么时间出发能被正好取走，并将其从小到大排序，这样在取走一份货物时，就能取走所有比它编号要小的货物，更容易计算。设对于排完序后的货物，在 $s_i$ 时间出发能够将其正好取走，$sum_i=\sum_{j=1}^{j\leq i} s_j$，如果上一次正好取走了第 $i$ 份货物，这一次正好取走了第 $j$ 份货物，那么从 $i+1$ 到 $j$ 这一段的货物的受潮时间就为：

$$s_j\times(j-i)-(sum_j-sum_i)$$

拆括号得到：

$$s_j\times j-s_j\times i-sum_j+sum_i$$

亏损的钱数就为：

$$m\times (s_j\times j-s_j\times i-sum_j+sum_i)$$

这时候有人可能会发现：$s_i$ 可能 $<k$。这时候就用到时光穿梭机了，容易发现这次时光穿梭机什么时候用都一样，不影响答案，只需要穿越到 $\min\{s_i\}$ 以前就行。

感觉很可以 $dp$。设 $dp_{i,j}$ 为只考虑在 $[1,j]$ 份货物中，往返第 $i$ 次正好取走排序后第 $j$ 份货物亏损的最小值，答案即为 $dp_{\lfloor\frac{c}{2\times x}\rfloor,\sum_{i=1}^{i\leq n} b_i}$。

再来推一下 $dp$ 式。根据上文亏损钱数可知：

$$dp_{i,j}=\min_{k=1}^{k\leq j}\{dp_{i-1,k}+m\times (s_j\times j-s_j\times k-sum_j+sum_k)\}$$

欸？$\min_{k=1}^{k\leq j}$？$s_j\times k$？这咋这么像斜率优化 $dp$ 啊？

接着推下去：

$$dp_{i,j}=\min_{k=1}^{k\leq j}\{dp_{i-1,k}+m\times s_j\times j-m\times s_j\times k-m\times sum_j+m\times sum_k\}$$

把 $\min$ 去掉，得：

$$dp_{i,j}=dp_{i-1,k}+m\times s_j\times j-m\times s_j\times k-m\times sum_j+m\times sum_k$$

化成斜率优化 $dp$ 的 $y=kx+b$ 形式，得：

$$dp_{i-1,k}+m\times sum_k=m\times s_j\times k+dp_{i,j}-m\times s_j\times j+m\times sum_j$$

标明一下：

$$dp_{i-1,k}+m\times sum_k~~~~=~~~~m\times s_j~~~~\times~~~~ k~~~~+~~~~dp_{i,j}-m\times s_j\times j+m\times sum_j$$

至此已化成 $y=kx+b$ 的形式。

注意因为我们求的是最小值，所以最开始的 $dp$ 数组要赋成极大值并把 $dp_{i,0}$ 清零，或者预处理出 $dp_1$ 里的每个值。

最后统计答案，答案即为：

$dp_{\lfloor\frac{c}{2\times x}\rfloor,\sum_{i=1}^{i\leq n} b_i}+\sum_{i=1}^{i\leq n}b_i\times m\times(x-a_i)$

最后就是输出方案了，在 $dp$ 的过程中记录一下每个值是由哪个地方转移而来，设 $dp_{i,j}$ 是由 $dp_{i-1,fa}$ 转移而来，那么我们就让 $fa_{i,j}=x$，输出时不断跳 $fa$ 数组，并用 set 记录，判断每次出发时是否有分身（或者本体）在家即可，别忘了 $-k$。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,m,x,c,k,a[200001],b[200001],sumb,d,s[500001],l,sum[500001],fa[201][500001],dp[201][500001],q[200001],f[201],r,now,ans;
set<int>st;
int X(int j){
    return j;
}
int Y(int j){
    return dp[now][j]+m*sum[j];
}
double query(int i,int j){
    return 1.0*(Y(j)-Y(i))/(X(j)-X(i));
}
void print(int k,int x){
    if(k-1&&fa[k][x]) print(k-1,fa[k][x]);
    f[++r]=x;
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>t;
    while(t--){
        sumb=0,l=0,r=0,ans=0;
        st.clear();
        cin>>n>>m>>x>>c>>k;
        for(int i=1;i<=n;i++) cin>>a[i];
        for(int i=1;i<=n;i++){
            cin>>b[i];
            sumb+=b[i];
            ans+=b[i]*m*(x-a[i]);
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=b[i];j++){
                cin>>d;
                s[++l]=d-a[i];
            }
        }
        if(!sumb){
            cout<<0<<'\n';
            cout<<-1<<" "<<-1<<'\n';
            continue;
        }
        if(!(c/(2*x))){
            cout<<-1<<'\n';
            continue;
        }
        sort(s+1,s+1+l);
        for(int i=1;i<=l;i++){
            sum[i]=sum[i-1]+s[i];
            dp[1][i]=m*(s[i]*i-sum[i]);
        }
        int h=1,t=1;
        for(int i=2;i<=c/(2*x);i++){
            h=1,t=1,now=i-1;
            memset(q,0,sizeof q);
            for(int j=1;j<=l;j++){
                while(h<t&&query(q[h],q[h+1])<=m*s[j]) h++;
                dp[i][j]=dp[i-1][q[h]]+m*((j-q[h])*s[j]-sum[j]+sum[q[h]]);
                fa[i][j]=q[h];
                while(h<t&&query(q[t-1],j)<=query(q[t-1],q[t])) t--;
                q[++t]=j;
            }
        }
        cout<<dp[c/(2*x)][l]+ans<<'\n';
        print(c/(2*x),l);
        for(int i=1;i<=r;i++){
            if(i==1){
                cout<<s[f[i]]-k<<" "<<0<<'\n';
                st.insert(s[f[i]]+2*x);
                continue;
            }
            if(!st.size()){
			    cout<<s[f[i]]-k<<" "<<1<<'\n';
                st.insert(s[f[i]]+2*x);
                continue;
            }
            bool sepa=1;
            if(*st.begin()<=s[f[i]]){
                st.erase(st.begin());
                sepa=0;
            }
			cout<<s[f[i]]-k<<" "<<sepa<<'\n';
            st.insert(s[f[i]]+2*x);
        }
        cout<<-1<<" "<<-1<<'\n';
    }
}

```

---

