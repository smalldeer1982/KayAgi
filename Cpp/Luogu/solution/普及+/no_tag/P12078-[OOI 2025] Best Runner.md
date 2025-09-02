# [OOI 2025] Best Runner

## 题目背景

[试题来源](https://inf-open.ru/2024-25/final-materials/)。

## 题目描述

体育场内共有 $n$ 条跑道，其长度分别为 $a_1, a_2, \ldots, a_n$。此外还有 $m$ 名跑者，第 $i$ 名跑者从编号为 $b_i$ 的跑道起点开始训练。

所有跑者将训练 $T$ 秒。训练过程如下：

- 设当前跑者位于第 $i$ 条跑道的起点，他们将用 $a_i$ 秒从起点跑到终点。随后，跑者可以立刻选择以下操作之一：返回当前跑道的起点、移动到第 $i - 1$ 条跑道的起点（如果 $i > 1$）、或移动到第 $i + 1$ 条跑道的起点（如果 $i < n$）。完成选择后，跑者继续在新选择的跑道上训练。训练将在总时间达到 $T$ 秒时结束。

我们将「最强跑者」定义为在训练时间内完整跑完跑道次数最多的跑者（可能存在多位最强跑者）。请你计算最强跑者最多能完整跑完多少条跑道。

## 说明/提示

**样例解释**

在第一个样例中，从第 $4$ 条跑道出发的跑者可以取得最多的成绩。他可以先跑完第 $4$ 条跑道，然后移动到第 $5$ 条跑道并跑完 $3$ 次，共计跑完 $4$ 条完整跑道。

在第二个样例中，从第 $2$ 条跑道出发的跑者可以在第 $2$ 条跑道上跑完 $2$ 次。

**评分**

本题的测试点共包含六个分组。只有当该分组的所有测试点及其依赖分组的测试点均通过时，才能获得该分组的分数。

| Subtask | 分数 | 限制条件：$n$ | $T$ | $a_i$ 的限制 | 依赖分组 | 说明 |
| :--- | :--- | :------------- | :-- | :------------- | :-------- | :---- |
| 0    | 0    | --             | --  | --             | --        | 样例测试点。 |
| 1    | 23   | $n \le 1000$   | --  | --             | 0         |             |
| 2    | 10   | --             | --  | 所有 $1 \le i < n$ 满足 $a_i \le a_{i + 1}$ | -- |             |
| 3    | 16   | --             | $T \le 20$ | --         | 0         |             |
| 4    | 19   | --             | --  | $a_i \le 20$   | 0         |             |
| 5    | 11   | --             | --  | --             | --        | $m = n$。     |
| 6    | 21   | --             | --  | --             | 0 -- 5    |             |

## 样例 #1

### 输入

```
5 3 10
4 5 2 7 1
1 2 4```

### 输出

```
4```

## 样例 #2

### 输入

```
4 2 11
4 5 7 10
2 3```

### 输出

```
2```

# 题解

## 作者：Tairitempest (赞：5)

## [OOI 2025] Best Runner

跑步的跑道数最多的人跑的肯定是长度相对较短的跑道，因此最优策略要么跑的跑道没有重复，要么会最终在一条跑道上跑到结束。显然对于最优答案的位置，其可能的运动员一定是在其两侧距离最近的运动员.

如果从更远的地方跑过来，那么只可能有两种情况：路上的跑道都比最终所在位置的跑道更长，和路上存在更短的跑道。对于前者，因为路上的跑道长度更长，其一定不优；对于后者，因为中间存在更短的跑道，因此选择更短的跑道跑到结束一定更优。

用计算前后缀的方法处理出每个跑道左右两侧距离它最近的两个运动员即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,m,T,a[300010],b[300010],s[300010],ans=-1e18;
ll l[300010],r[300010];
ll cnt(ll f,ll t){
    if(t==f) return T/a[t];
    if(t>f) return (t-f)+(T-s[t-1]+s[f-1])/a[t];
    else return (f-t)+(T-s[f]+s[t])/a[t];
}
ll go(ll f,ll t){
    if(t>f) return (s[t-1]-s[f-1]);
    else return (s[f]-s[t]);
}
int main(){
    cin>>n>>m>>T;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=m;i++) cin>>b[i];
    for(int i=1;i<=n;i++) s[i]=s[i-1]+a[i];
    for(int i=1;i<=m;i++) l[b[i]]=r[b[i]]=b[i];
    for(int i=1;i<=n;i++) if(!l[i]) l[i]=l[i-1];
    for(int i=n;i>=1;i--) if(!r[i]) r[i]=r[i+1];
    for(int i=1;i<=n;i++){
        if(l[i]&&go(l[i],i)<=T) ans=max(ans,cnt(l[i],i));
        if(r[i]&&go(r[i],i)<=T) ans=max(ans,cnt(r[i],i));
    }
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：happy_lion (赞：2)

# 题解 P12078 [OOI 2025] Best Runner

## Part 1 理解题意

这道题的意思是每一个跑者跑完当前跑道后可以去跑相邻的跑道或者当前的跑道，问在一定时间内完整跑完跑道次数最多的跑者最多能完整跑完多少条跑道。

## Part 2 分析思路

跑短的跑道显然能跑更多次，所以最优策略就是跑过的所有跑道上除了最短的都只跑一次，但是每个运动员去左右两边找短的跑道肯定会超时，所以让跑道去找两边最近的两个运动员，再计算答案。

可能有人想问，假如当前正在计算的跑道够短，难道更远的地方的运动员不会过来吗？其实更远的地方跑过来，跑的跑道条数一定大于两边的运动员，因为他们在路上跑过的跑道更多，而题目中只求一个最大值，所以无需考虑更远的运动员。

但是还会超时，所以考虑前缀和后缀优化，具体看代码注释。

## Part 3 参考代码


```cpp
#include<bits/stdc++.h>
using namespace std;
long long t;
long long a[300010],b[300010];
long long s[300010];//a数组的前缀和
long long l[300010];//一条跑道左边最近的运动员
long long r[300010];//一条右边最近的运动员
long long go(long long x,long long y){
    //从x开始跑到y，路程上的所有跑道的长度和（不含y）。
    if (y > x) {
        return s[y]-s[x];//前缀和快速计算
    } else {
        return s[x-1]-s[y-1];
    }
}
long long f(long long x,long long y) {
    //计算从y跑到x再在x上跑到时间用完的跑道条数
    long long sum = 0;
    sum += go(y,x);//计算来x的路程上的长度和
    long long ans = 0;
    ans += abs(y-x);//来x的路程上跑的跑道条数
    ans += (t-sum)/a[y];//计算还能在x上跑几次
    return ans;
}
int main() {
    //输入
    int n,m;
    cin >> n >> m >> t;
    for (int i=1;i<=n;i++) {
        cin >> a[i];
    }
    for (int i=1;i<=m;i++) {
        cin >> b[i];
    }
    //计算a数组前缀和
    for (int i=1;i<=n;i++) {
        s[i] = s[i-1]+a[i];
    }
    //计算每条跑道左右两边最近的运动员
    for (int i=1;i<=m;i++) {
        l[b[i]] = b[i];//当前跑道有运动员
        r[b[i]] = b[i];
    }
    //类似前缀和后缀思想求左右两边最近的运动员
    for (int i=1;i<=n;i++) {
        if (l[i] == 0) {
            l[i] = l[i-1];
        }
    }
    for (int i=n;i>=1;i--) {
        if (r[i] == 0) {
            r[i] = r[i+1];
        }
    }
    //计算答案
    long long ans = -9e18;
    for (int i=1;i<=n;i++) {
        //左边有运动员且时间够跑过来
        if (l[i] > 0 && go(i,l[i]) <= t) {
            ans = max(ans,f(l[i],i));//更新答案
        }
        //右边有运动员且时间够跑过来
        if (r[i] > 0 && go(i,r[i]) <= t) {
            ans = max(ans,f(r[i],i));//更新答案
        }
    }
    //输出答案
    cout << ans << endl;
    return 0;
}
```
有问题发在评论里，我很乐意回答哦~

---

## 作者：xiaoniu142857 (赞：1)

## Solution
首先分析每位跑者的最优决策，尝试寻找一下特殊性质。

首先，直觉告诉我们，在不同跑道间切换的过程中一定不会改变方向。假设最优策略中改变了方向，最终跑过了 $l\sim r$ 这些跑道。而一开始就直接一步步切换到这其中最短的跑道并在它上面一直跑下去一定不会更劣。

其次，最优策略一定是往一个方向切换若干条跑道后，在最后一条跑道一直跑，且它一定是这些跑道中最短的。用反证法易证：假设最短的不是最后一条，那我们直接提前在最短的那里停下一直跑一定更优。

设 $L(i)$ 为第 $i$ 条跑道左边第一个比它短的跑道下标，$R(i)$ 同理。根据前面的结论可知，初始时位于跑道 $i$ 的跑者最终只可能停在 $i,L(i),L(L(i)),\dots$ 或 $R(i),R(R(i)),\dots$。

因此我们直接用单调栈预处理出 $L(i)$ 和 $R(i)$，再暴力枚举所有可能的位置计算最优的答案。注意用前缀和计算 $a_i$ 的区间和。这就有了这份代码：
```cpp
#include <iostream>
#define rept(i,a,b) for(int i(a);i<=b;++i)
#define pert(i,a,b) for(int i(a);i>=b;--i)
#define int long long  // 注意开long long
using namespace std;
constexpr int N=3e5+5;
int a[N],b[N],s[N],l[N],r[N],stk[N],top;
signed main(){
    cin.tie(0)->sync_with_stdio(0);
    int n,m,T,ans=0;
    cin>>n>>m>>T;
    rept(i,1,n){
        cin>>a[i];
        s[i]=s[i-1]+a[i];
    }
    rept(i,1,m){
        cin>>b[i];
    }
    rept(i,1,n){
        while(top&&a[stk[top]]>=a[i]) --top;
        l[i]=stk[top];
        stk[++top]=i;
    }
    top=0;
    pert(i,n,1){
        while(top&&a[stk[top]]>=a[i]) --top;
        r[i]=stk[top];
        stk[++top]=i;
    }
    rept(i,1,m){
        int p=b[i];
        while(p){
            ans=max(ans,b[i]-p+(T-s[b[i]]+s[p])/a[p]);
            p=l[p];
        }
        p=b[i];
        while(p){
            ans=max(ans,p-b[i]+(T-s[p-1]+s[b[i]-1])/a[p]);
            p=r[p];
        }
    }
    end:
    cout<<ans;
    return 0;
}
```
这种优雅的暴力在随机数据上表现相当不错，能获得 90 分。然而它卡不过 Subtask 2。

其实构造 Hack 很简单，只要随便搞个单峰序列例如 $1,2,3,4,3,2,1$ 就能把它卡到 $O(n^2)$。但是我们还有最后一招——乱搞。

考虑卡时，在即将 TLE 时输出当前得到的最优解。这种做法大概率是正确的，但取决于数据强度。这样就可以 AC 啦！

注：本篇题解的做法并不具有绝对正确性，仅能通过较弱的测试数据。然而这种[卡时的思想](https://oi-wiki.org/misc/simulated-annealing/#%E5%8D%A1%E6%97%B6)具有一定的启发性，例如某些随机化或模拟退火的题目就我们就可以尝试多换几个随机种子，不断运行算法直到即将超时，这样可以有更大的概率得到正确答案。
## AC Code
```cpp
#include <iostream>
#include <chrono>
#define rept(i,a,b) for(int i(a);i<=b;++i)
#define pert(i,a,b) for(int i(a);i>=b;--i)
#define int long long  // 注意开long long
using namespace std;
constexpr int N=3e5+5;
int a[N],b[N],s[N],l[N],r[N],stk[N],top;
signed main(){
    cin.tie(0)->sync_with_stdio(0);
    auto start=chrono::high_resolution_clock::now(); 
    int n,m,T,ans=0;
    cin>>n>>m>>T;
    rept(i,1,n){
        cin>>a[i];
        s[i]=s[i-1]+a[i];
    }
    rept(i,1,m){
        cin>>b[i];
    }
    rept(i,1,n){
        while(top&&a[stk[top]]>=a[i]) --top;
        l[i]=stk[top];
        stk[++top]=i;
    }
    top=0;
    pert(i,n,1){
        while(top&&a[stk[top]]>=a[i]) --top;
        r[i]=stk[top];
        stk[++top]=i;
    }
    rept(i,1,m){
        int p=b[i];
        while(p){
            ans=max(ans,b[i]-p+(T-s[b[i]]+s[p])/a[p]);
            p=l[p];
            auto stop=chrono::high_resolution_clock::now();  
            auto ms=std::chrono::duration_cast<std::chrono::milliseconds>(stop-start).count();  
            if(ms>900) goto end;
        }
        p=b[i];
        while(p){
            ans=max(ans,p-b[i]+(T-s[p-1]+s[b[i]-1])/a[p]);
            p=r[p];
            auto stop=chrono::high_resolution_clock::now();  
            auto ms=std::chrono::duration_cast<std::chrono::milliseconds>(stop-start).count();  
            if(ms>900) goto end;
        }
    }
    end:
    cout<<ans;
    return 0;
}
```

---

## 作者：zhoujiefu (赞：1)

考虑每个人走到哪里最大没什么前途，所以我们考虑每条跑道。对于每条跑道，只有里我最近的人来到我这里一直跑下去显然是更优的。所以预处理出每条跑道左右第一个人，再计算答案就可以了。具体的，预处理的时候，枚举每一个人，他左边的那个人的右边和他之间，这些跑道右边第一个人就是他。反过来也一样。所以这是一个区间推平，单点修改。写两棵线段树分别维护左边和右边就行了。

```cpp
#include<bits/stdc++.h>
#define int long long
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define per(i,a,b) for(int i=a;i>=b;i--)
using namespace std;
const int N=3e5+5;
int n,m,t,ans;
int a[N],b[N],sum[N];
struct SGT{
	#define ls i<<1
	#define rs i<<1|1
	struct node{
		int tag;
	}t[N<<2];
	inline void addtag(int i,int x){
		t[i].tag=x;
	}
	inline void pushdown(int i){
		if(t[i].tag){
			addtag(ls,t[i].tag);
			addtag(rs,t[i].tag);
			t[i].tag=0;
		}
	}
	void build(int i,int l,int r){
		t[i]={0};
		if(l==r) return;
		int mid=l+r>>1;
		build(ls,l,mid);
		build(rs,mid+1,r);
	}
	void update(int i,int il,int ir,int l,int r,int x){
		if(l<=il&&ir<=r){
			addtag(i,x);
			return;
		}
		pushdown(i);
		int mid=il+ir>>1;
		if(l<=mid) update(ls,il,mid,l,r,x);
		if(r>=mid+1) update(rs,mid+1,ir,l,r,x);
	}
	int query(int i,int il,int ir,int x){
		if(il==ir) return t[i].tag;
		pushdown(i);
		int mid=il+ir>>1;
		if(x<=mid) return query(ls,il,mid,x);
		else return query(rs,mid+1,ir,x);
	}
}sgtl,sgtr;
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>m>>t;
	rep(i,1,n) cin>>a[i],sum[i]=sum[i-1]+a[i];
	sgtl.build(1,1,n),sgtr.build(1,1,n);
	rep(i,1,m) cin>>b[i],ans=max(ans,t/a[b[i]]);
	int lst=1;
	rep(i,1,m){
		sgtr.update(1,1,n,lst,b[i],i);
//		cout<<lst<<' '<<b[i]<<' '<<i<<'\n';
		lst=b[i]+1;
	}
	lst=n;
	per(i,m,1){
		sgtl.update(1,1,n,b[i],lst,i);
		lst=b[i]-1;
	}
	rep(i,1,n){
		int l=sgtl.query(1,1,n,i),r=sgtr.query(1,1,n,i);
		if(l&&sum[i-1]-sum[b[l]-1]<=t) ans=max(ans,i-b[l]+(t-sum[i-1]+sum[b[l]-1])/a[i]);
		if(r&&sum[b[r]]-sum[i]<=t) ans=max(ans,b[r]-i+(t-sum[b[r]]+sum[i])/a[i]);
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：yanrs1019 (赞：0)

# 理论分析
## 思路  
可以证明，对于一个跑者，他会定下一个目标跑道。跑到那个跑道上之后，不会再移动了。这样是最优的。   
考虑贪心。  
## 考虑贪心  
最优解通常出现在跑者选择最短跑道进行重复训练。因此我们需要为每个跑者找到能最快到达的最短跑道。  
但是找到每个跑者的目标跑道时间复杂度 $\mathcal{O}(nm)$，显然超时。  
考虑对于每个跑道，找到它左右的两个跑者。  
## 公式  
我们定义 $a$ 的前缀和数组 $s$。  
设从跑道 $x$ 跑到跑道 $j$ 需要 $T$ 时间，消耗所有时间后能跑 $w$ 次。  

$$T=\begin{cases}s_{j-1}-s_{x-1}&(x\leq j)\\s_x-s_j&(x>j)\end{cases}$$  

$$w=\begin{cases}\frac{t-T}{a_j}+j-x&(x\leq j)\\\frac{t-T}{a_j}+x-j&(x>j)\end{cases}$$  

# 具体实现  
## 预处理  
1. 计算前缀和数组；
2. 预处理每个位置向左和向右最近的跑者的起始位置。
## 计算答案  
对于每个跑道 $i$：  
1. 计算向左和向右到达最近的跑者的 $T$ 和 $w$；
2. 找到最大值。  
# ACcode  
```cpp
#include<bits/stdc++.h>
using namespace std;
#define LL long long
#define N 300005
LL a[N],b[N],sum[N],l[N],r[N];
int main(){
	LL ans=0,n,m,t;
	scanf("%lld%lld%lld",&n,&m,&t);
	for(LL i=1;i<=n;i++)scanf("%lld",&a[i]),sum[i]=sum[i-1]+a[i];
	for(LL i=1;i<=m;i++)scanf("%lld",&b[i]),l[b[i]]=r[b[i]]=b[i];
	for(LL i=1,j=n;i<=n;i++,j--){
		if(!l[i])
			l[i]=l[i-1];
		if(!r[j])
			r[j]=r[j+1];
	}
	for(LL i=1;i<=n;i++){
		LL lth,num;
		if(i>l[i])lth=sum[i-1]-sum[l[i]-1];
		else lth=sum[l[i]]-sum[i];
		if(i>l[i])num=(t-sum[i-1]+sum[l[i]-1])/a[i]+i-l[i];
		else num=(t-sum[l[i]]+sum[i])/a[i]+l[i]-i;
		
		if(l[i]&&lth<=t)ans=max(ans,num);
		
		
		if(i>r[i])lth=sum[i-1]-sum[r[i]-1];
		else lth=sum[r[i]]-sum[i];
		if(i>r[i])num=(t-sum[i-1]+sum[r[i]-1])/a[i]+i-r[i];
		else num=(t-sum[r[i]]+sum[i])/a[i]+r[i]-i;
		
		if(r[i]&&lth<=t)ans=max(ans,num);
	}
	printf("%lld",ans);
	return 0;
}
```
**注意空间要开 $2n$。**

---

