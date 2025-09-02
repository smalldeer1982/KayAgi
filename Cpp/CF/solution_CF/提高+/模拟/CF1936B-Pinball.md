# Pinball

## 题目描述

There is a one-dimensional grid of length $ n $ . The $ i $ -th cell of the grid contains a character $ s_i $ , which is either '&lt;' or '&gt;'.

When a pinball is placed on one of the cells, it moves according to the following rules:

- If the pinball is on the $ i $ -th cell and $ s_i $ is '&lt;', the pinball moves one cell to the left in the next second. If $ s_i $ is '&gt;', it moves one cell to the right.
- After the pinball has moved, the character $ s_i $ is inverted (i. e. if $ s_i $ used to be '&lt;', it becomes '&gt;', and vice versa).
- The pinball stops moving when it leaves the grid: either from the left border or from the right one.

You need to answer $ n $ independent queries. In the $ i $ -th query, a pinball will be placed on the $ i $ -th cell. Note that we always place a pinball on the initial grid.

For each query, calculate how many seconds it takes the pinball to leave the grid. It can be shown that the pinball will always leave the grid within a finite number of steps.

## 说明/提示

In the first test case, the movement of the pinball for $ i=1 $ is shown in the following pictures. It takes the pinball $ 3 $ seconds to leave the grid.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1936B/9b874ab4c5ee491df87b5d2616ead8d797821647.png)The movement of the pinball for $ i=2 $ is shown in the following pictures. It takes the pinball $ 6 $ seconds to leave the grid.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1936B/b4fdbd3674e32422b13cf88676e6ccbb2eef3a53.png)

## 样例 #1

### 输入

```
3
3
><<
4
<<<<
6
<><<<>```

### 输出

```
3 6 5 
1 2 3 4 
1 4 7 10 8 1```

# 题解

## 作者：wosile (赞：6)

我想写简单题题解。所以就随便 vp 了一场 div2。

手动模拟一下样例。

在向左走碰到 `>` 或者向右走碰到 `<` 的时候会改变方向，并且已经走过的格子不会出现这样的情况。

对于每个 $i$，会变向的关键点就是它左边的 $s_j=$ `>`，和它右边的 $s_j=$ `<`。如果前者比后者少，那么最后就是向左走出了边界，否则就是向右。

关键点个数可以前缀和差分计算。

显然，在每一侧变向的次数是两侧关键点数量的较小值 $x=\min(l,r)$。也就是说我们需要考虑 $i$ 两侧各 $x$ 个关键点带来的贡献。

以开始就向左走，最后向左走出边界为例，设 $r_j$ 为第 $j$ 个 $i$ 右侧的关键点位置，$l_j$ 同理。

那么走过的总路程就是 $(i-l_1)+(r_1-l_1)+(r_1-l_2)+(r_2-l_2)+...+(r_x-l_x)+(r_x-0)=i+2\sum_{j=1}^xr_j-2\sum_{j=1}^xl_j$。$\sum r_j$ 和 $\sum l_j$ 都可以通过前缀和差分快速求出。

分类讨论一下开头和结尾分别朝什么方向即可。

时间复杂度 $O(n)$。

下面是代码，但是不要照搬代码里的式子，自己算一遍比较好，又没什么难的。

~~被细节恶心到了，你们也来自己推一下细节。~~

```cpp

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
char s[500005];
int cntl[500005],cntr[500005];
ll suml[500005],sumr[500005];
int sign(char c){
	if(c=='>')return -1;
	return 1;
}
int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		int n;
		scanf("%d",&n);
		scanf("%s",s+1);
		int pl=0,pr=0;
		for(int i=1;i<=n;i++){
			if(s[i]=='<'){
				cntl[i]=cntl[i-1]+1,cntr[i]=cntr[i-1];
				suml[pl+1]=suml[pl]+i;
				++pl;
			}
			else{
				cntl[i]=cntl[i-1],cntr[i]=cntr[i-1]+1;
				sumr[pr+1]=sumr[pr]+i;
				++pr;
			}
		}
		for(int i=1;i<=pl;i++)printf("%lld ",(suml[i]-suml[cntl[i]]-sumr[cntr[i-1]])*2+sign(s[i])*i);
		for(int i=pl+1;i<=n;i++)printf("%lld ",n+1+(suml[pl]-suml[cntl[i]]-sumr[cntr[i-1]]+sumr[i-1-pl])*2+sign(s[i])*i);
		printf("\n");
	}
	return 0;
}
// quod erat demonstrandum
```

---

## 作者：inc1ude_c (赞：5)

提供一种比较好写的做法。

显然的，如果球的初始方向为右，则其路径一定是往右碰到第一个 `<`，随后往左碰到初始位置左边第一个 `>`，再往右碰到初始位置右边第二个 `<`……直到出界。

![](https://cdn.luogu.com.cn/upload/image_hosting/nwgjli7f.png)

现在我们考虑分别算出从左出来的球的路程，和从右出来的球的路程。

现在考虑求从左出来的球的答案。

注意到从左出来的球满足右边的 `<` 不少于左边的 `>`，所以它们一定构成一段前缀，考虑我们已经知道位置 $i-1$ 的答案为 $f_{i-1}$，那么怎么推算出位置 $i$ 的答案呢，现在给出关系式：

$$
f_{i}=f_{i-1}+2\times (p-i)+1
$$

其中 $p$ 是位置 $i$ 最后一次碰到的右边的 `<` 的位置，可以走指针算出。

为什么这个式子是对的？首先，增量 $2\times (p-i)+1$ 相当于蓝色路径：

![](https://cdn.luogu.com.cn/upload/image_hosting/ls6ok18t.png)

注意到不属于增量的路径（橙色路径）经过平移可以得到上一位置的路径。

![](https://cdn.luogu.com.cn/upload/image_hosting/0jjhwd94.png)

更精确地说，要计算的位置 $i$ 往右移一个后，多出的一小段（浅绿色部分）刚好补到了折返的路径上。

![](https://cdn.luogu.com.cn/upload/image_hosting/11cfv2wh.png)

故原式成立。

从右出来的球的答案求法是对称的。

```cpp
#include<bits/stdc++.h>
using namespace std;
#ifndef ONLINE_JUDGE
#include "debug.h"
#else
#define debug(...)
#define debugArr(...)
#endif
#define db double
#define ll long long
#define ull unsigned long long
#define per(i,a,b) for(int i=(a);i>=(b);i--)
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
const int N=5e5+5;
int n;string s;
ll ans[N];
void solve(){
    cin>>n>>s;
    int ps=1;ll sum=0;
    rep(i,1,n){
        while(ps<=n&&s[ps-1]!='<')ps++;
        if(ps<=n){sum+=2ll*(ps-i)+1;ans[i]=sum;}
        else break;
        ps++;
    }
    ps=n;sum=0;
    per(i,n,1){
        while(ps>=1&&s[ps-1]!='>')ps--;
        if(ps>=1){sum+=2ll*(i-ps)+1;ans[i]=sum;}
        else break;
        ps--;
    }
    rep(i,1,n)printf("%lld ",ans[i]);puts("");
}
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int T;cin>>T;
    while(T--)solve();
    return 0;
}
```

---

## 作者：Wf_yjqd (赞：5)

赛时通过人数让我高估了他的难度。

鉴定为普及 T2 难度的小模拟。

------------

我们可以发现，有且仅有在出发点左边的所有 `>` 和右边的所有 `<` 可能改变方向，且每个最多改变一次方向。

我们可以想象成一个小球遇到障碍反弹，那么一开始他会在左右各反弹两边障碍较小值次。

接下来，若初始方向上的障碍较多，则会在初始方向上多反弹一次，且最终离开方向与初始方向相反；否则，离开方向与初始方向相同。

我们需要维护前缀 `>` 个数，前缀 `>` 坐标和，后缀 `<` 个数，后缀 `<` 坐标和。

复杂度 $\operatorname{O}(n)$。

------------

细节可参考代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=5e5+26;
int T,n,cntz[maxn],cnty[maxn];
ll hzz[maxn],qzy[maxn],ans;
char s[maxn];
int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d%s",&n,s+1);
        for(int i=1;i<=n;i++){
            cnty[i]=cnty[i-1];
            if(s[i-1]=='>'){
                cnty[i]++;
                qzy[cnty[i]]=qzy[cnty[i]-1]+i-1;
            }
        }
        cntz[n]=0;
        for(int i=n-1;i>=1;i--){
            cntz[i]=cntz[i+1];
            if(s[i+1]=='<'){
                cntz[i]++;
                hzz[cntz[i]]=hzz[cntz[i]-1]+i+1;
            }
        }
        for(ll i=1,cnt;i<=n;i++){
            cnt=min(cntz[i],cnty[i]);
            ans=(hzz[cntz[i]]-hzz[cntz[i]-cnt]-qzy[cnty[i]]+qzy[cnty[i]-cnt])*2;
            if(s[i]=='<'){
                if(cnty[i]>cntz[i])
                    ans+=(i-qzy[cnty[i]-cnt]+qzy[cnty[i]-cnt-1])*2+n-i+1;
                else
                    ans+=i;
            }
            else{
                if(cntz[i]>cnty[i])
                    ans+=(hzz[cntz[i]-cnt]-hzz[cntz[i]-cnt-1]-i)*2+i;
                else
                    ans+=n-i+1;
            }
            printf("%lld ",ans);
        }
        puts("");
    }
    return 0;
}
```

---

## 作者：Pursuewind (赞：0)

以从左边走出为例，走的过程大致是这个样子，从 $i$ 走到 $i$ 左侧第一个 `>`，然后往后遇到第一个 `<`，然后往左再遇到 `>` 再往右，如此往复直到左边没有 `>`。

不妨设当前点左侧有 $x$ 个 `>` 位置分别为 $l_1,l_2,\ldots, l_x$，那么我们需要在右侧找到 $x$ 个 `<` 位置分别为 $r_1, r_2,\ldots r_x$。

然后路径就是 $i \to l_x \to r_1 \to l_{x-1} \to r_2 \to \dots$。

然后画一下式子可以发现最终答案是 $2(\sum r_j - \sum l_j) + i$。

对于从右侧出去的情况只需要翻转原串再做一遍即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int INF = 1e18;
int n;
string s;
vector <int> get(){
    vector <int> ans(n, INF);
    int cnt1 = 0, cnt2 = 0;
    int s1 = 0, s2 = 0;
    if (s[0] == '<'){
        cnt2 ++;
        s2 += 0;
    }
    int last = -1;
    for (int i = 0, j = 0; i < n; i++){
        if (s[i] == '>'){
            cnt1 ++;
            s1 += i;
            if (last == -1) last = i;
        }
        if (s[i] == '<'){
            cnt2 -= 1;
            s2 -= i;
        }
        while (cnt1 > cnt2 && j < n){
            j ++;
            if (s[j] == '<'){
                cnt2 ++;
                s2 += j;
            }
        }
        if (cnt1 > cnt2) break;
        if (last == -1) ans[i] = i + 1;
        else ans[i] = 2 * s2 - 2 * s1 + i + 1;
    }
    return ans;
}
void solve(){
    cin >> n;
    cin >> s;
    auto ans1 = get();
    reverse(s.begin(), s.end());
    for (auto &c : s){
        if (c == '<') c = '>';
        else c = '<';
    }
    auto ans2 = get();
    for (int i = 0; i < n; i ++){
        cout << min(ans1[i], ans2[n - 1 - i]) << " ";
    }
    cout << "\n";
}
signed main(){
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int t;
    cin >> t;
    while (t --) solve();
    return 0;
}
```

---

## 作者：MoyunAllgorithm (赞：0)

首先手模样例，你将得到一个重要的结论：

**相邻两次转向之间的间隔将越来越长**（且初始也算作一次转向）。

如样例中：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1936B/b4fdbd3674e32422b13cf88676e6ccbb2eef3a53.png)

图 $1 \sim 2$ 方向不变；图 $2 \sim 4$ 方向不变；图 $4 \sim 7$ 方向不变。每次“方向不变”的跨度都增加了。

为什么呢？不妨设球向左移动。设球左侧的第一个 `>` 的位置是 $p$，球上一次转向的位置是 $q$，球的位置是 $b$。有 $p \le b \le q$。由于球向左移动，故 $[b,q]$ 内的箭头向右。则当球到 $p$ 时，将开始向右移动，此时 $[p+1,q]$ 内的箭头均向右，则球会到达一处 $>q$ 的位置。因此这一结论是正确的。

从中我们可以轻松得到另一结论：引起球变向的，是左侧的 `>` 和右侧的 `<`。

假设球初始向左。则：

- 若左侧的右箭头多于右侧的左箭头，球会从右边离开；

- 若左侧的右箭头少于等于右侧的左箭头，球会从左边离开。

考虑情况一。设球初始位置是 $b$，右侧的箭头从左到右依次为 $q_1,q_2,\cdots,q_k$，左侧的箭头从右到左依次为 $p_1,p_2,\cdots$，则球的走向为：

$b \to p_1 \to q_1 \to p_2 \to q_2 \to \cdots \to q_k \to p_{k+1} \to $ 右外侧。

则它的路程是 $b-p_1+q_1-p_1+q_2-p_2+\cdots -p_{k+1}+N+1-p_{k+1}$（认为右侧是 $N+1$），化简得 $b+N+1+2\sum_{i=1}^{k} (q_i-p_i)-2p_{k+1}$。用前缀和可以快速得出。

情况二中，球的走向则是：

$b \to p_1 \to q_1 \to p_2 \to q_2 \to \cdots \to p_k \to q_k \to $ 左外侧。

路程为 $b+2\sum_{i=1}^{k} (q_i-p_i)$。

初始向右的情况同理。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <vector>
#include <queue>
#include <cstring>
#define LL long long
using namespace std;
const int MAXN=5e5+5;
int N,T;
char s[MAXN];
int pl[MAXN],pr[MAXN],L=0,R=0;
LL suml[MAXN],sumr[MAXN];
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&N);
        scanf("%s",s+1);
        L=0,R=0;
        for(int i=1;i<=N;i++)
        {
            if(s[i]=='>') pl[++L]=i;
            else pr[++R]=i;
        }
        for(int i=1;i<=L;i++) suml[i]=suml[i-1]+pl[i];
        for(int i=1;i<=R;i++) sumr[i]=sumr[i-1]+pr[i];
        for(int i=1;i<=N;i++)
        {
            if(s[i]=='<')
            {
                int cl=lower_bound(pl+1,pl+L+1,i)-pl-1;
                int cr=upper_bound(pr+1,pr+R+1,i)-pr;
                if(R+1-cr>=cl)
                {
                    int cnt=cl;
                    LL ans=2ll*(sumr[cr+cnt-1]-sumr[cr-1]-(suml[cl]-suml[cl-cnt]));
                    ans=ans+i;
                    printf("%lld ",ans);
                }
                else
                {
                    int cnt=R-cr+2;
                    if(cr==0&&R==0) cnt=1;
                    LL ans=2ll*(sumr[R]-sumr[cr-1]-(suml[cl]-suml[cl-cnt]));
                    ans=ans+i+N+1;
                    printf("%lld ",ans);
                }
            }
            if(s[i]=='>')
            {
                int cl=lower_bound(pl+1,pl+L+1,i)-pl-1;
                int cr=upper_bound(pr+1,pr+R+1,i)-pr;
                if(R+1-cr<=cl)
                {
                    int cnt=R+1-cr;
                    LL ans=2ll*(sumr[R]-sumr[cr-1]-(suml[cl]-suml[cl-cnt]));
                    ans=ans-i+N+1;
                    printf("%lld ",ans);
                }
                else
                {
                    int cnt=cl+1;
                    LL ans=2ll*(sumr[cr+cnt-1]-sumr[cr-1]-suml[cl]);
                    ans=ans-i;
                    printf("%lld ",ans);
                }
            }
        }
        puts("");
    }
    return 0;
}
```

---

