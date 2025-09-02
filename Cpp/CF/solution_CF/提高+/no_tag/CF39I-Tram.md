# Tram

## 题目描述

In a Berland city S\*\*\* there is a tram engine house and only one tram. Three people work in the house — the tram driver, the conductor and the head of the engine house. The tram used to leave the engine house every morning and drove along his loop route. The tram needed exactly $ c $ minutes to complete the route. The head of the engine house controlled the tram’s movement, going outside every $ c $ minutes when the tram drove by the engine house, and the head left the driver without a bonus if he was even one second late.

It used to be so. Afterwards the Berland Federal Budget gave money to make more tramlines in S\*\*\*, and, as it sometimes happens, the means were used as it was planned. The tramlines were rebuilt and as a result they turned into a huge network. The previous loop route may have been destroyed. S\*\*\* has $ n $ crossroads and now $ m $ tramlines that links the pairs of crossroads. The traffic in Berland is one way so the tram can move along each tramline only in one direction. There may be several tramlines between two crossroads, which go same way or opposite ways. Every tramline links two different crossroads and for each crossroad there is at least one outgoing tramline.

So, the tramlines were built but for some reason nobody gave a thought to increasing the number of trams in S\*\*\*! The tram continued to ride alone but now the driver had an excellent opportunity to get rid of the unending control of the engine house head. For now due to the tramline network he could choose the route freely! Now at every crossroad the driver can arbitrarily choose the way he can go. The tram may even go to the parts of S\*\*\* from where it cannot return due to one way traffic. The driver is not afraid of the challenge: at night, when the city is asleep, he can return to the engine house safely, driving along the tramlines in the opposite direction.

The city people were rejoicing for some of the had been waiting for the tram to appear on their streets for several years. However, the driver’s behavior enraged the engine house head. Now he tries to carry out an insidious plan of installing cameras to look after the rebellious tram.

The plan goes as follows. The head of the engine house wants to install cameras at some crossroads, to choose a period of time $ t $ and every $ t $ minutes turn away from the favourite TV show to check where the tram is. Also the head of the engine house wants at all moments of time, divisible by $ t $ , and only at such moments the tram to appear on a crossroad under a camera. There must be a camera on the crossroad by the engine house to prevent possible terrorist attacks on the engine house head. Among all the possible plans the engine house head chooses the plan with the largest possible value of $ t $ (as he hates being distracted from his favourite TV show but he has to). If such a plan is not unique, pick the plan that requires the minimal possible number of cameras. Find such a plan.

## 样例 #1

### 输入

```
4 5
1 2
2 3
3 4
4 1
1 4
```

### 输出

```
2
2
1 3
```

# 题解

## 作者：wosile (赞：2)

首先不要去管那个阴间原题面在说什么，我根本看不懂。看洛谷翻译的题面就行了。

不能从 $1$ 开始到达的点直接丢掉就好了。我们只考虑能从 $1$ 到达的点。

注意到一个 $t$ 是合法的当且仅当，我们可以给每个点 $i$ 一个值 $a_i$，使得对于原图中的一条边 $(u,v)$，有 $a_u+1 \equiv a_v \pmod t$。

我们先令 $a_1=0$，然后随便选一个以 $1$ 为根的 dfs 树，在不取模的情况下标出每个点的 $a_i$（也就是从 $1$ 开始随便 dfs，对于每一条边 $(u,v)$，直接令 $a_v=a_u+1$）。

这时候非树边不一定满足 $a_v=a_u+1$，那我们就需要选取一个合适的 $t$ 使得 $a_u+1 \equiv a_v \pmod t$，也就是 $t \mid a_v-a_u-1$。

那么只要让 $t$ 是所有 $a_v-a_u-1$ 的公约数即可。

容易证明，所有 $a_v-a_u-1$ 的最大公约数就是图中所有环的大小的最大公约数，也就是本题的答案。所以所求的 $t_{\max}=\gcd\limits_{(u,v)\in E}(a_v-a_u-1)$。

输出点集的时候，把所有 $a_i\equiv 0 \pmod t$ 的点 $i$ 加入点集就可以了。

时间复杂度 $O(n+m)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
vector<int>G[100005];
int n,m;
int a[100005];
void dfs(int x){
    for(int v:G[x])if(a[v]==-1){
        a[v]=a[x]+1;
        dfs(v);
    }
}
vector<int>ans;
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
        int u,v;
        scanf("%d%d",&u,&v);
        G[u].push_back(v);
    }
    memset(a,-1,sizeof(a));
    a[1]=0;
    dfs(1);
    int t=0;
    for(int i=1;i<=n;i++)for(int j:G[i])if(a[i]!=-1 && a[j]!=-1)t=__gcd(t,abs(a[i]+1-a[j]));
    printf("%d\n",t);
    for(int i=1;i<=n;i++)if(a[i]!=-1 && a[i]%t==0)ans.push_back(i);
    printf("%d\n",(int)ans.size());
    for(int x:ans)printf("%d ",x);
    return 0;
	// quod erat demonstrandum
}
```

---

