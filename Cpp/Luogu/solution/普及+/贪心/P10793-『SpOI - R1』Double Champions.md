# 『SpOI - R1』Double Champions

## 题目描述

**本题包含多组数据。**

现在有若干个格子排在一行上。

再给出 $n$ 个区间，每个区间 $i$ 可以覆盖 $[l_i,r_i]$ 这个区间中的每一个格子（例如，区间 $[1,2]$ 可以覆盖格子 $1,2$）。

现在需要把这些区间分组，每个组带来的贡献为所有其旗下的区间的交的总长度。

你需要求出最少把这些区间分成多少组，才能使得每一组的贡献都 $\geq w$。如果不存在任何方案满足条件，输出 `No`。

## 说明/提示

#### 样例 #1 解释

按照输入顺序将输入的区间依次编号为 $①,②,③,④,⑤$。

可以将 $5$ 个区间分为以下 $3$ 组：$\{①,④\},\{②\},\{③⑤\}$。这样每一组的贡献即交集大小分别为 $3,3,3$，符合对每组贡献 $\geq 3$ 的要求。可以证明，$3$ 组是所有符合条件的区间划分方案中组数最少的。

### 数据范围

**请注意常数因子对程序效率的影响。**

**本题开启捆绑测试和子任务依赖。**

对于 $100\%$ 的数据，$1\leq T\leq 20$，$1\leq n\leq 2\times 10^5$，$0\leq w\leq 10^6$，$1\leq l_i\leq r_i\leq 10^6$。

| Subtask | $n\leq$ | $w,l_i,r_i\leq$ | 得分 | 子任务依赖 |
| :----------: | :----------: | :----------: | :----------: | :----------: |
| 1 | $8$ | $15$ | $10$ | 无 |
| 2 | $11$ | $20$ | $10$ | 1 |
| 3 | $1.5\times 10^3$ | $10^4$ | $25$ | 1,2 |
| 4 | $2\times 10^5$ | $10^6$ | $55$ | 1,2,3 |

## 样例 #1

### 输入

```
2
5 3 
6 10
6 8 
3 5 
7 9 
1 9
5 5
5 10
3 8
6 10
4 10
5 9```

### 输出

```
3
3```

# 题解

## 作者：takanashi_mifuru (赞：9)

容易发现这个区间交就两个信息比较有用，一个是右端点的最小值，另一个是左端点的最大值。

那我们按照右端点从小到大排序，然后就能确定右端点的最小值在哪了，而如果一个区间如果取走之后可用就直接拿走，否则就直接不要，这样就是对的。

为什么？

首先因为这个点和前面不匹配，所以这个必须要选，而一个区间能不能被当作一个匹配的区间这件事情具有单调性因为右端点单调不降，所以左端点的限制只会越来越宽，不存在前面能用后面开了新段就没法用的段，所以没问题。

$w=0$ 要特判。

```cpp
#include<bits/stdc++.h>
using namespace std;
int T;
int n,w;
struct node{
    int lt,rt;
    bool friend operator < (const node &a,const node &b){
        return a.rt<b.rt;
    }
}A[200005];
int main(){
    // freopen("test.in","r",stdin);
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&w);
        bool tag=true;
        for(int i=1;i<=n;i++){
            scanf("%d%d",&A[i].lt,&A[i].rt);
            if(A[i].rt-A[i].lt+1<w)tag=false;
        }
        if(!tag){
            puts("No");
            continue;
        }
        if(!w){
            puts("1");
            continue;
        }
        sort(A+1,A+1+n);
        int Max=-1;
        int pos=0;
        for(int i=1;i<=n;i++){
            if(Max<A[i].lt){
                pos++;
                Max=A[i].rt-w+1;
            }
        }
        printf("%d\n",pos);
    }
    return 0;
}
```

---

## 作者：X____ (赞：6)

## 题解：P10793 『SpOI - R1』Double Champions
### 题目大意

给出 $n$ 个区间，求最少将这些区间分成多少组，要求每组的区间的并长度大于 $w$。

### 思路

无解的情况显然，这里不讨论了。

注意到如果有一个大区间包含一个小区间，把这两个区间扔到一组是最优的。

我们把这些有包含关系的区间分到同一组之后，每组的贡献显然就是小区间的长度，容易看出这些小区间要么相交一部分，要么完全分离。

为了让组数尽可能的少，应该让这些小区间尽可能的成为同一组，考虑对这些小区间一端进行排序，从前往后扫，并且维护当前的贡献是否合法即可。

自认为是本题最简洁的代码。

```cpp
#define F(i, l, r) for(int (i)((l)); (i) <= (r); ++ (i))
struct Node{
	int x, y;
}e[N];
bool cmp(Node a, Node b) {
	return a.x < b.x;
}
void Work() {
	read(n);
	read(w);
	F(i, 1, n) {
		read(e[i].x);
		read(e[i].y);
		if(e[i].y - e[i].x + 1 < w) flg = 1;
	}
	if(flg) {
		puts("No");
		return;
	}
	if(!w) { 
		puts("1");
		return;
	}
	//因为按照一端排序后，这些大区间并不会对当前的维护产生影响，所以不用对大区间进行特殊处理 
	sort(e+1, e+n+1, cmp);
	int l = 0, r = 1e9, ans = 1;
	F(i, 1, n) {
		l = max(l, e[i].x), r = min(r, e[i].y);
		//维护当前这一组的并，如果不合法就重新开一组 
		if(r-l+1 < w) {
			l = e[i].x;
			r = e[i].y;
			ans ++;
		}
	}
	write(ans);
}
```

---

## 作者：水星湖 (赞：3)

给出一个与官方题解不同的贪心做法。

首先还是和官方题解一样排序去重，原因和方法再官方题解都有，就不赘述了。

去重后，我们可以对剩下的区间按照左端点升序排序，设剩下 $n'$ 个区间，则剩下的区间序列一定满足 $\forall i \in [1,n'),l_i<l_{i+1},r_i<r_{i+1}$，考虑贪心，如果 $i$ 能和 $j(j>i)$ 分到同一组，那么 $i\sim j$ 之间的所有区间都可以和区间 $i$ 分到同一组，所以只需要从第一个区间开始，一直往后遍历直到当前区间不能和第一个分到同一组（即与第一个区间的交集长度小于 $w$），那么就把当前区间作为下一组的第一个区间，之后遍历到的区间就和当前区间比较。

然后就做完了。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 2e5 + 5;
int t, n, w;
struct qu {
    int l, r;
    friend bool operator < (qu a, qu b) {
        if(a.l != b.l) return a.l > b.l;
        return a.r < b.r;
    } 
} a[N];
vector<qu> b;
void solve() {
    b.clear();
    cin >> n >> w;
    for(int i = 1; i <= n; i++) cin >> a[i].l >> a[i].r;
    sort(a + 1, a + n + 1);
    b.push_back({0, 0});
    int last = 0;
    for(int i = 1; i <= n; i++) {
        if(a[i].r - a[i].l + 1 < w) {
            cout << "No" << endl;
            return;
        }
        if(last && a[i].r >= a[last].r) continue;
        b.push_back(a[i]);
        last = i;
    }
    sort(b.begin(), b.end(), [](qu a, qu b){return a.l < b.l;});
    int now = 1, ans = 1;
    if(w == 0) w = -2e9;
    for(int i = 2; i < b.size(); i++) {
        if(b[now].r - b[i].l + 1 < w) ans++, now = i;
    }
    cout << ans << endl;
}


signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> t; 
    while(t--) solve();

    return 0;
}
```

---

## 作者：Shunpower (赞：2)

出题人题解。

显然无解当且仅当存在一个区间本身长度就 $<w$。

考虑区间之间的包含关系，很容易发现一对包含关系的区间，大区间被分进其他组可能会导致其他组的贡献减少到 $<w$，导致那一组被迫拆开增加组数，所以一对包含关系的区间一定大区间跟随小区间，组数总是不劣的。

容易用一次排序，维护区间右端点最小值的办法去掉包含其他区间的区间。所以接下来我们只考虑去掉了这些包含其他区间的区间的情况。

考虑按照区间左端点排序，由于排除了包含关系所以右端点也一定单调。考虑证明一定存在一个方案，每一组一定都是连续的。

> 必要性证明：假设现在存在一个每一组都不连续的方案，那么对于不连续方案中的每一组，都可以将它们交换为连续，很明显排序之后交换为连续时每一组的交集单调不递减。因此构造出了一种每一组都是连续的方案。这说明，只要有方案，就一定有每一组都连续的方案。

> 充分性证明：假设不存在一个每一组都连续的方案，那么对于连续方案中的每一组，很明显在排序之后交换为不连续时每一组的交集单调不递增，因此无法构造出不连续的方案。这说明，只要没有每一组都连续的方案，就没有方案。

设 $dp_{i}$ 表示前 $i$ 个区间且 $i$ 区间分在最后一组的的最少分组数，则转移容易得到为 $dp_i\gets \min\{dp_i,dp_j\times[(j,i]\text{ is valid}]\}$。很明显有效连续区间（即 $i$ 左侧最长的交集 $\geq w$ 的连续段）的左端点位置具有单调性，因此容易用队列维护（只需要维护连续区间的交集即可。在所有区间已经互不包含且排序的情况下，这是容易求的）。

转移时，拿出左侧最远的转移点（队列头）转移。因为区间数量越多分组越多（决策单调性），所以直接从队列队头转移即可。

答案即为 $dp_n$。复杂度 $\mathcal O(n\log n)$，瓶颈在于排序。

------

下面是 std：

```cpp
int n,w;
pii seg[N];
vector <pii> valid;
queue <int> tf;
int dp[N];
int check(int l,int r){
    return max(0,valid[l].se-valid[r].fi+1);
}
void solve(){
    read(n),read(w);
    valid.clear();
    while(!tf.empty()) tf.pop();
    bool flg=0;
    fr1(i,1,n){
        read(seg[i].fi),read(seg[i].se);
        if(seg[i].se-seg[i].fi+1<w) flg=1;
    }
    if(flg) return puts("No"),void();
    sort(seg+1,seg+n+1,[](pii &x,pii &y){
        if(x.fi==y.fi) return x.se<y.se;
        return x.fi>y.fi;
    });
    int minn=V+1;
    fr1(i,1,n){
        if(minn<=seg[i].se) continue;
        minn=min(minn,seg[i].se);
        valid.pb(seg[i]);
    }
    sort(valid.begin(),valid.end());
    fr1(i,1,valid.size()){
        tf.push(i);
        while(check(tf.front()-1,i-1)<w) tf.pop();
        dp[i]=dp[tf.front()-1]+1;
    }
    write(dp[valid.size()]);
    putchar('\n');
}
```

---

## 作者：封禁用户 (赞：1)

题目思路：按照右端点从小到大排序，可以确定右端点的最小值位，如果一个区间如果取走之后可用就直接拿走，否则就直接不要。正确性证明：因为排序后，多选一个区间，交集大小一定不会增加，选择区间是不劣的，即这样同一组的区间一定会在一起，因此得出上述贪心策略。

代码：
```
#include<bits/stdc++.h>
using namespace std;
struct Node{
    int l,r;
}a[200005];
inline bool cmp(Node x1,Node x2){
    return x1.l<x2.l;
}
signed main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int t;
    cin>>t;
    while(t--){
        int n,w;
        cin>>n>>w;
        bool bj=0;
        for(int i=1;i<=n;i++){
            cin>>a[i].l>>a[i].r;
            if(a[i].r-a[i].l+1<w){
                bj=1;
            }
        }
        if(bj){
            cout<<"No\n";
            continue;
        }
        sort(a+1,a+n+1,cmp);
        int ans=0;
        int mi=1000005;
        for(int i=1;i<=n;i++){
            mi=min(a[i].r,mi);
            if(mi-a[i].l+1<w&&w!=0){
                ans++;
                mi=a[i].r;
            }
        }
        cout<<ans+1<<'\n';
    }
}

---

## 作者：ziyanlin2013 (赞：1)

**题目传送门**：https://www.luogu.com.cn/problem/P10793  
# 简要题意
- 给出一个 $n$ 个**区间**。
- 求至少分成几组，使其每组内，区间交集**大于等于** $w$。
- 无解输出 **No**。

# 解题思路
首先，有一个区间长度小于 $w$ 无解（读者自证）。

其次，考虑交集与右端点最小值和左端点最大值相关，将区间按左端点排序，这样同一组的区间一定会在一起（这样是最优的），依次判断当前区间能否与上一个区间合并为一组，贪心即可。  

正确性证明：因为排序后，多选一个区间，交集大小一定不会增加，选择区间是不劣的，即这样同一组的区间一定会在一起，因此得出上述贪心策略。  
复杂度 $O(n\log n)$。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N=2e5+5;
int t,n,w;
struct T{
	int l,r;
}a[N];
int flag;
bool cmp(T a,T b){return a.l<b.l;}
int minn,ans;
void _(){
	scanf("%d%d",&n,&w);
	flag=0;//注意初始化
	for (int i=1;i<=n;i++){
		scanf("%d%d",&a[i].l,&a[i].r);
		if(a[i].r-a[i].l+1<w) flag++;
	}
	if(w==0){printf("1\n");return ;}
	if(flag){printf("No\n");return ;}
	sort(a+1,a+n+1,cmp);
	ans=1,minn=INT_MAX;//INT_MAX 表示 int 最大值
	for (int i=1;i<=n;i++){
		minn=min(minn,a[i].r);
		if(minn-a[i].l+1<w){//排序后交集左端点就是 a[i].l 
			ans++;
			minn=a[i].r;
		}
	}
	printf("%d\n",ans);
}
int main(){
	cin>>t;
	while(t--) _();
	return 0;
}
```

---

## 作者：xiaoliebao1115 (赞：1)

前言：这篇题解对于贪心实现的正确性做了更加简单易懂的证明。
## 思路
先特判所有区间中有长度小于 $w$ 的情况，直接输出不行即可。

我们可以知道，影响区间交集的只有右端点最小值和左端点最大值。于是对于每一个区间按照右端点进行排序，排序后进行贪心。若一个区间可以加入当前组别，则加入，否则新建一个组别，将其加入，之后的区间也只会去尝试加入这个新组别。

正确性：能加入就加，这个很好理解，因为他的加入不会影响后面的区间，后面的区间在他加入之前能加的还能加，否则依然不能加。当不能加入时，因为所有区间都要分组，所以这个数只能另起一组，可以保证，这一组的右端点一定大于等于之前组的右端点，且在加入新的区间时右端点将会保持不变，于是左端点就可以更加靠右，相比于将区间加入之前的组别，显然加入当前的一定不劣，于是做法就得到了证明。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int nn=2e5+5;
int t,n,w;
struct node{
	int l,r;
};
node x[nn];
bool cmp(node l1,node l2){
	return l1.r<l2.r;
}
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>t;
	while(t--){
		int n,w;
		cin>>n>>w;
		bool p=true;
		for(int i=1;i<=n;i++){
			cin>>x[i].l>>x[i].r;
			if(x[i].r-x[i].l+1<w) p=false; 
		}
		if(!p){
			cout<<"No"<<endl;
			continue;
		}
		if(!w){ 
		    cout<<1<<endl;
		    continue;
	    }
		sort(x+1,x+n+1,cmp);
		int rmin,lmax,sum=1;
		rmin=x[1].r,lmax=x[1].l;
		for(int i=2;i<=n;i++){
			if(rmin-x[i].l+1>=w){
				lmax=max(lmax,x[i].l);
			}
			else{
				rmin=x[i].r,lmax=x[i].l;
				sum++;
			}
		}
		cout<<sum<<endl;
	}
	return 0;
}
```
需要注意的是，还需要特判 $w$ 是否等于 $0$，直接输出 $1$。若不特判，会导致在循环运算过程中出现负数时错误的将答案增加，实际上所有区间一定能够分为 $1$ 组。如果不进行对拍的话，这个东西实在是天坑。

---

## 作者：ycy1124 (赞：1)

### 题意
有 $n$ 个区间和一个值 $w$，现在要将这 $n$ 个区间分成 $m$ 组，使得每组内所有区间的交集的大小大于等于 $w$，求 $m$ 的最小值。
### 思路
考虑贪心。首先我们很容易就可以发现，对于每一组区间，他们的交集的大小等组内区间的 $r_i$ 的最小值减去 $l_i$ 的最大值。此时我们可以将区间按他们的 $l_i$ 从小到大排个序。这样做有什么好处呢，此时我们从第 $x$ 个区间连续选到第 $y$ 个区间，如果再选第 $y+1$ 个区间，那么他的交集大小一定是不增的。此时我们可以采用一个贪心的策略，从前面往后面枚举，当到一个区间交际大小小于 $w$ 是就增加答案。

注意当 $w=0$ 是直接输出 $1$ 即可。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
struct Node{
    int l,r;
}a[200005];
inline bool cmp(Node x1,Node x2){
    return x1.l<x2.l;
}
signed main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int t;
    cin>>t;
    while(t--){
        int n,w;
        cin>>n>>w;
        bool bj=0;
        for(int i=1;i<=n;i++){
            cin>>a[i].l>>a[i].r;
            if(a[i].r-a[i].l+1<w){
                bj=1;
            }
        }
        if(bj){
            cout<<"No\n";
            continue;
        }
        sort(a+1,a+n+1,cmp);
        int ans=0;
        int mi=1000005;
        for(int i=1;i<=n;i++){
            mi=min(a[i].r,mi);
            if(mi-a[i].l+1<w&&w!=0){
                ans++;
                mi=a[i].r;
            }
        }
        cout<<ans+1<<'\n';
    }
    return 0;
}
```
[AC 记录。](https://www.luogu.com.cn/record/194453802)

---

## 作者：Caged_Bird (赞：0)

# P10793 解题报告

## 题目大意

给出 $n$ 个区间 $[l_i,r_i]$ 和一个限制 $w$，现将这些区间分组，使每个组别内区间的交长度 $>w$，求最少组数。

## 解题思路

一看就很贪心。

如果有一个区间长度 $<w$，它跟谁分组区间交都 $<w$，显然无解。  
其余情况可以每个区间单独成组，就可以满足条件，不存在无解。

要求区间的交，有用的信息就是同组里的最大左端点和最小右端点。  
首先对区间按左端点从小到大进行排序，因为这样就确定了最大左端点。

接着遍历序列，动态维护当前组别的最小右端点 $r_{\min}$。每次加入第 $i$ 个区间，将 $r_{\min}$ 与 $r_i$ 取较小值。然后判断加入后是否不满足条件，因为我们已经确定了最大左端点是 $l_i$，所以只要判断是否 $r_{\min}-l_i+1<w$ 即可。

如果加入后区间交 $<w$，那么说明这个区间只能再单开一组了，因为将它放进当前组已经是最优解，不可能把它丢进之前的其他组里了。于是新开一组，统计答案加一，并将 $r_{\min}$ 重置为 $r_i$。  
否则就什么都不动，把这个区间丢进当前组，继续判断下个区间。

注意特判 $w=0$ 的情况，否则可能喜获 $0$ pts 的好成绩。

## Code

```cpp
#include<bits/stdc++.h>
#define int long long
#define N 200005
using namespace std;
inline void print(int n){if(n<0){putchar('-');print(-n);return;}if(n>9)print(n/10);putchar(n%10+'0');}
inline int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch==EOF)return 0;if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();if(ch==EOF)break;}return x*f;}
int n,w,mn,mr,tot,T;
struct node{
    int l,r;
}a[N];
bool cmp(node a,node b){
    return a.l<b.l;
}
signed main(){
    T=read();
    while(T--){
        tot=0;
        n=read();w=read();mn=w,mr=1145141919810;
        for(int i=1;i<=n;i++){
            a[i].l=read();
            a[i].r=read();
            mn=min(mn,a[i].r-a[i].l+1);
        }
        if(w==0){cout<<"1\n";continue;}
        if(mn<w){cout<<"No\n";continue;}
        sort(a+1,a+1+n,cmp);
        for(int i=1;i<=n;i++){
            mr=min(mr,a[i].r);
            if(mr-a[i].l+1<w)tot++,mr=a[i].r;
        }
        cout<<tot+1<<'\n';
    }
    return 0;
}
```

---

## 作者：hexz01 (赞：0)

# 题解：P10793 『SpOI - R1』Double Champions

这篇题解写给像我一样的蒟蒻。

## 题意

给定一些**闭区间**以及 $n$ 和 $w$，求最少可以把这些区间分成几组，使得每组的区间交长度 $\ge w$。

## 思路

首先思考有没有无解。显然如果每个区间长度都 $\ge w$，那么答案最大是 $n$。所以无解的情况就是存在区间长度 $< m$ 的情况。

接下来往区间交的计算方式上想，发现区间交的长度取决于组内左端点的最大值和右端点的最小值。

栗子：

```
1 2 3 4 5 6 7 8 9 10
-----------------
      -----------
    ---------
        ---
```

上述栗子中右端点的最小值为 6，左端点的最大值为 5。所以区间交的长度为 $6-5+1=2$。

于是考虑算法，看到分组，想到 DP 和贪心。这里使用更方便的贪心。将区间按 $r_i$ 为第一关键字，$l_i$ 为第二关键字排序。则每一组的区间一定是连续的，如样例：

```
1 2 3 4 5 6 7 8 9 10
    -----
          -----
-----------------
            -----
          ----------
```

### 贪心证明：

设当前组别的左端点最大值为 $maxl$，右端点最小值为 $minr$，当前区间 $l_i, r_i$，后面有一组区间要加入当前组别中，区间交的左右端点为 $L,R$，而当前区间不加。

如果当前区间能加且后面那组要加，则 $\min(r_i, R, maxr)-\max(l_i, L, maxl)+1 \ge w$，那么加上当前区间后仍满足要求，与其不加不如加上，至少不会更差。

## 关于 DP

发现 DP 加单调队列跟贪心本质是一样的。

## Code:

``` cpp
#include <iostream>
#include <algorithm>
using namespace std;
const int N=2e5+7;
int n, w;
struct node{
	int l, r;
}a[N];
bool cmp(node x, node y){
	return (x.r!=y.r?x.r<y.r:x.l<y.l);
}
int main(){
	ios::sync_with_stdio(0);
	int T;
	cin>>T;
	while(T--){
		cin>>n>>w;
		bool pd=0;
		for(int i=1;i<=n;i++){
			cin>>a[i].l>>a[i].r;
			if(a[i].r-a[i].l+1<w)
				pd=1;
		}
		if(pd){
			cout<<"No"<<endl;
			continue;
		}
		if(w==0){//防止变负
			cout<<1<<endl;
			continue;
		}
		sort(a+1, a+n+1, cmp);
		int ans=0, nowl=1919810, nowr=0;
		for(int i=1;i<=n;i++){
			if(min(nowr, a[i].r)-max(nowl, a[i].l)+1<w){
				nowl=a[i].l;nowr=a[i].r;
				ans++;
			}else{
				nowl=max(nowl, a[i].l);
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：是青白呀 (赞：0)

不难观察到下面两个性质：

1. 当两个区间为包含关系时，仅有被包含的区间是有效的，大区间一定跟随小区间分到同一组，从而对答案不产生任何影响。我们可以据此对所有区间去重，使得排序后区间左右端点均递增。
2. 按上文方式处理并排序后，每一组选择的区间一定是一个连续段，因为多个区间的交仅由最左侧和最右侧的两个区间决定，中间所有区间都可以分到同一组，而对答案不产生影响。

从而可以设计 dp：设 $dp_i$ 表示考虑了前 $i$ 个区间的最小分组数，有 $dp_i=dp_j+1$，其中 $j$ 需要满足第 $j+1$ 个区间和第 $i$ 个区间的交的长度至少为 $w$。不难发现满足条件的 $j$ 是一个区间，且端点随 $i$ 的增大而右移，直接单调队列维护即可。

复杂度瓶颈在对区间的预处理，为 $O(Tn\log n)$。

```cpp
#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=j;i<=k;i++)
#define repp(i,j,k) for(int i=j;i>=k;i--)
#define ls(x) x*2
#define rs(x) x*2+1
#define lowbit(x) x&(-x)
#define pii pair<int,int>
#define mp make_pair
#define fir first
#define sec second
#define qingbai 666
using namespace std;
typedef long long ll;
const int N=1e6+10,M=1005,mo=1e9+7,inf=1e9+7,bs=19491001;
const double eps=1e-8;
inline void read(int &p){
	int x=0,w=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-')w=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	p=x*w;
}
int T;
int n,w,dp[N],cntv;
pii a[N],vld[N];
bool vis[N];
bool cmp(pii x,pii y){
	if(x.fir!=y.fir)return x.fir>y.fir;
	return x.sec<y.sec;
}
int interv(int x,int y){
	return max(0,vld[x].sec-vld[y].fir+1);
}
void solve(){
	read(n),read(w);
	rep(i,1,n)
	    dp[i]=inf,vis[i]=0;
	cntv=0;
	rep(i,1,n)
	    read(a[i].fir),read(a[i].sec);
	sort(a+1,a+n+1,cmp);
	int la=0;
	rep(i,1,n){
		if(la&&a[i].sec>=a[la].sec)continue;
		else vld[++cntv]=a[i],la=i;
	}
	sort(vld+1,vld+cntv+1);
	deque<int>q;
	q.push_back(0);
	dp[0]=0;
	rep(i,1,cntv){
		while(!q.empty()&&interv(q.front()+1,i)<w)
		    q.pop_front(); 
		if(q.empty())continue;
		dp[i]=min(dp[i],dp[q.front()]+1);
		while(!q.empty()&&dp[q.back()]>=dp[i])
		    q.pop_back();
		q.push_back(i);
	}
	if(dp[cntv]>=inf)puts("No");
	else printf("%d\n",dp[cntv]);
}
int main(){
	read(T);
	while(T--)
	    solve();
	return 0;
}
```

---

