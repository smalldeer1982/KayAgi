# [ARC098E] Range Minimum Queries

## 题目描述

你有一个长度为 $n$ 的整数序列 $A$，以及一个整数 $K$。你会进行 $Q$ 次操作，一次操作如下：

- 选择序列中一个长度为 $K$ 的区间，并且删除区间中的最小元素。如果有多个，你可以选择任何一个。   
   
现在，设 $X$ 是你删除了的元素中最大的一个，$Y$ 是最小的一个，请找出在最优情况下，$X-Y$ 的最小值。

## 样例 #1

### 输入

```
5 3 2
4 3 1 5 2```

### 输出

```
1```

## 样例 #2

### 输入

```
10 1 6
1 1 2 3 5 8 13 21 34 55```

### 输出

```
7```

## 样例 #3

### 输入

```
11 7 5
24979445 861648772 623690081 433933447 476190629 262703497 211047202 971407775 628894325 731963982 822804784```

### 输出

```
451211184```

# 题解

## 作者：是青白呀 (赞：4)

### 方法简述
本题需要求得删去序列的最大值和最小值的差，考虑枚举删去序列的最小值，进而用**优先队列**求出删去序列最大值最小的情况。

### 具体说明
枚举以 $a_i$ 为最小值的情况，容易得知选择长度为 $k$ 的区间时，我们不能选择区间内有任意元素小于 $a_i$ 的区间，而针对内部无元素小于 $a_i$ 且元素个数不小于 $k$ 个的区间 $f(x,y)$，可以删去至多 $y-x-k+2$ 个元素。我们考虑找出所有最长的这样的区间，并选择其中最小的 $Q$ 个元素删除。

### 实现方法
当枚举 $a_i$ 为最小值时，扫描原数组，并将每一个大于等于 $a_i$ 的元素存入一个优先队列 $p$。当 $a_j≤a_i$ 且 $a_{j+1}>a_i$ 时，优先队列 $p$ 内存储的恰好是一个最长的、元素均不小于 $a_i$ 的区间。此时，弹出队列顶的若干个元素存入另一个优先队列 $ans$ 中去，直至优先队列 $p$ 中剩余元素小于 $k$ 个时直接清空队列 $p$。原数组扫描完毕后，若队列 $ans$ 中的元素不小于 $q$ 个，则查找队列 $ans$ 中第 $q$ 小的元素值，该元素值与 $a_i$ 的差即为 $a_i$ 为最小值时极差的最小值。最后比较所有情况下极差的最小值即可。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2005;
int n,k,q;
int a[N],minn=0x3f3f3f3f;//minn存储极差最小值 
struct cmpp{
	bool operator()(int a,int b){
		return a>b;
	}
};
int main(){
	cin>>n>>k>>q;
	for(int i=1;i<=n;i++)
	    scanf("%d",&a[i]);
	for(int i=1;i<=n;i++){
		priority_queue<int,vector<int>,cmpp>p,ans;
		for(int j=1;j<=n;j++){
			if(a[j]>=a[i])p.push(a[j]);
			if(a[j]<a[i]||j==n){
            //注意1：当扫描结束时应判断最后一个区间 
				while(!p.empty()){
					if(p.size()>=k)ans.push(p.top());
					p.pop();
				}
			}
		}
		int cnt=0,maxn;
		if(ans.size()>=q){
        //注意2：在某些情况下ans内存储的答案不足q个，此时不能更新minn的值 
			while(cnt<q&&!ans.empty()){
		    	maxn=ans.top();
		    	ans.pop();
		    	cnt++;
	    	}
	    	minn=min(minn,maxn-a[i]);
		}
	}
	printf("%d",minn);
	return 0;
}
```


---

## 作者：Day_Tao (赞：2)

看题发现我们似乎不方便很好地构建 $x,y$ 的直接关系，而且允许的时间复杂度又是 $\mathcal{O}(n^2)$ 或者再带只 $\log$ 的，所以我们考虑去枚举一个数去确定另一个数。这里我选择去枚举 $y$，然后找到最小的 $x$。

既然现在确定了 $y$，那么显然就不能再去取比 $y$ 更小的数了，所以我们先把不能取的数都挖掉，剩下了若干个独立的区间。

继续观察，发现对于一个区间，在长度 $\ge k$ 的时候你可以用一次包含区间最小值的操作去将区间最小值取出。这就能保证取出来的数最小，符合我们寻找的 $x$ 的特征。

但是具体要取多少呢？由于我们对于 $x$ 仍然没有一个清晰的认知，所以这个数量是没法很好地确定的。不难发现合法的 $x$ 是存在单调性的，所以直接二分 $x$ 去 $\text{check}$。这样我们就能对于一个具体的 $x$ 去做了。

$\text{check}$ 的时候就将一个区间 $[l,r]$ 中满足值域在 $[x,y]$ 的数取出，并且一个区间取的数不能多于 $r-l+1-(k-1)$ 个。最后判断一下取出来的数的总数与 $q$ 的大小关系即可。

时间复杂度：$\mathcal{O}(n^2\log n)$。

**code：**

```cpp
int n,q,k,a[N],ans=INF,mx;
inline bool chk(int x,int y){
    int ct=0,t=0,pr=1;F(i,1,n){if(y<=a[i]&&a[i]<=x)++t;
        if(a[i]<y||i==n)ct+=max(min(i-pr-(k-1)+1-(a[i]<y),t),0ll),t=0,pr=i+1;}
    return ct>=q;
}
inline void SOLVE(){
    n=rd(),k=rd(),q=rd();F(i,1,n)a[i]=rd(),cmx(mx,a[i]);
    F(i,1,n){int y=a[i],x=-1,l=y,r=mx;
        while(l<=r)if(chk(mid,y))x=mid,r=mid-1;else l=mid+1;
        if(x!=-1)cmn(ans,x-y);
    }printf("%lld\n",ans);
    return ;
}
```

---

## 作者：zac2010 (赞：2)

考虑枚举 $Y$。

根据 $Y$ 的定义，有：序列中比 $Y$ 小的数都不能被选到长为 $K$ 的区间内。所以我们不妨用那些 $<Y$ 的数把序列分割成几个连续段去处理。

有了连续段的性质之后，我们暴力处理出每个元素所处的连续段以及连续段的长度。之后再从小到大枚举 $X$，每次看看所有 $A_i=X$ 的 $i$ 所在的连续段长度是否 $\geq k$。假若是，说明这里可以贡献一个长为 $k$ 的区间，同时把 $X$ 从序列中删去（注：这里不需要真正的删去，只要把其所在连续段长度 $-1$ 即可），否则无事发生。

假若记 $Y=i$ 时，最小的 $X$ 为 $x_i$。那么答案就是 $\min_{i=1}^n x_i-i$。

```cpp
#include <bits/stdc++.h>
#define FL(i, a, b) for(int i = (a); i <= (b); i++)
#define FR(i, a, b) for(int i = (a); i >= (b); i--)
using namespace std;
const int N = 2010;
int n, k, q, r, tot, cnt, ans = 1e9;
int a[N], id[N], rk[N], d[N], len[N];
int cmp(int i, int j){return a[i] < a[j];}
int main(){
    scanf("%d%d%d", &n, &k, &q);
    FL(i, 1, n) scanf("%d", &a[id[i] = i]);
    sort(id + 1, id + n + 1, cmp);
    FL(i, 1, n) rk[id[i]] = i;
    FL(i, 1, n){
        cnt = tot = 0, fill(d + 1, d + n + 1, 0);
        FL(j, 1, n) if(rk[j] >= i){
            if(j == 1 || rk[j - 1] < i) len[++tot] = 0;
            len[d[j] = tot]++;
        }
        for(r = i; r <= n && cnt < q; r++){
            cnt += (len[d[id[r]]]-- >= k);
        }
        if(cnt < q) break; ans = min(ans, a[id[r - 1]] - a[id[i]]);
    }
    printf("%d\n", ans);
    return 0;
}
```


---

## 作者：Naganorhara_Yoimiya (赞：1)

## 题解：AT_arc098_c [ARC098E] Range Minimum Queries
好像是一道很奶龙的题目，又好像不是很奶龙。

注意到 $n \le 2000$，所以 $O(n^2)$ 以上的解法。

所以我们考虑先钦定一个数字为上界，原问题转化为求出最小值的最大值。

这时候你一定会想到二分答案。

考虑如何编写 ``check`` 函数，注意到针对一个长度为 $L$ 的区间中，只要没有一个数字比当前钦定的最小值要小，那么就可以删除 $\max \{ 0,L-k+1,cnt\}$ 个数字，其中 $cnt$ 表示区间中比钦定的最大值大的数字的数量。

因此，我们可以以每一个比当前钦定最小值小的数字为分界，在每一个区间判断可删除数字的数量，最后判断是否可以删除 $q$ 个数字即可。

时间复杂度 $O(n^2 \log (\max\{A_i\}))$，顺利拿下全机房最劣解。

其实离散化一下可以做到 $O(n^2 \log n)$，不过我懒得写。

~~学校模拟赛为了防止骗分改成多测了，题解放洛谷上不是很想改输入了。~~

```cpp
#include <bits/stdc++.h>
#define inf 1e12
#define int long long
#define Yoimiya using
#define is namespace
#define my std
#define wife ;
Yoimiya is my wife
const int maxn = 2e4+100;
int n,k,q,a[maxn+100],ans = inf;
int l,r,x,mi,cnt,pre,t;

bool check(int p){
	cnt = pre = t = 0;
	for(int i = 1;i <= n;i++){
		if(a[i] < p){
			cnt += max((long long)0,min(i-pre-k,t));
			pre = i,t = 0;
		} else if(a[i] <= x) t++;
	} 
	cnt += max((long long)0,min(n+1-pre-k,t));
	return cnt >= q ? 1 : 0;
}

signed main(){
	//ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	while(cin >> n >> k >> q){
		ans = mi = inf;
		for(int i = 1;i <= n;i++) {
			cin >> a[i];
			mi = min(a[i],mi);
		} 
		for(int i = 1;i <= n;i++){
			x = a[i],l = mi,r = a[i];
			while(l < r){
				int mid = (l+r+1) >> 1;
				if(check(mid) == 1) l = mid;
				else r = mid - 1;
			}
			//cout << x << " " << l << '\n'; 
			if(check(l)) ans = min(ans,x - l);
		}
		cout << ans << '\n';
	} 
	return 0;
}
```

---

## 作者：StayAlone (赞：1)

直接做不容易，考虑先枚举 $X$。自然可以想到二分最大的 $Y$。

考虑如何 check。

设二分的值为 $p$，那么以所有 $a_i<p$ 的位置为分界点，可以得到极长的很多段。对任何不包含分界点的区间进行一次操作，删去的数都一定大于等于 $p$。

那么对于区间 $[l,r]$，做出的操作次数贡献就是 $\max(0, \min(r - l + 1 - k + 1,cnt))$，其中 $cnt$ 表示这个区间内小于等于 $X$ 的数的数量（因为如果这个区间的最小值大于 $X$，不符合枚举的『最大值为 $X$』的要求）。

若总贡献次数大于等于 $Q$，返回真。

时间复杂度可以做到 $\mathcal O(n^2\log n)$。写的是 $\mathcal O(n^2\log v)$。

[AC record](https://www.luogu.com.cn/record/124803601)

```cpp
int n, k, q, ans = inf, a[2010];
int x;

il bool check(int p) {
	int cnt = 0, lst = 0, t = 0;
	rep1(i, 1, n + 1) {
		if (a[i] < p) {
			cnt += max(0, min(i - lst - k, t));
			lst = i; t = 0;
		} else t += a[i] <= x;
	} return cnt >= q;
}

int main() {
	read(n, k, q); rer(i, 1, n, a);
	a[n + 1] = -1;
	rep1(i, 1, n) {
		x = a[i];
		int l = 0, r = x;
		while (l ^ r) {
			int mid = l + r + 1 >> 1;
			if (check(mid)) l = mid;
			else r = mid - 1;
		} if (check(l)) ans = min(ans, x - l);
	} printf("%d", ans);
	rout;
}
```

---

## 作者：uid_310801 (赞：1)

容易发现答案上界是第 $Q$ 小的数减去最小的数。

从小到大枚举最小的数是什么。之后再选数的时候挑选的区间就不能包含比枚举的数小的数了。这样序列就被分成了若干段区间。

然后从小往大贪心选数，如果数所在的区间长度 $\geq k$，我们就将它选上，然后该区间长度减 $1$，若最后能选出来 $Q$ 个数，就看看能不能对 $ans$ 作贡献。如果不能选出来，那么再分下去也不可能再有解了。直接 break。

时间复杂度 $O(n^2)$。

```cpp
/********************
  *	author:Spouter_27
  *	place:spst Alego
  * with:marmoreal_777
  ******************/
#include<bits/stdc++.h>
using namespace std;
//#define int long long
#define deb(x) cerr<<"Line: "<<__LINE__<<", val= "<<x<<"; \n"
typedef long long ll;
#define pii pair<ll,ll>
#define mp make_pair
#define fi first
#define se second
const ll N=2e3+10;
ll n,k,q,b[N],ans,d[N],p[N];
pii a[N];
ll lt[N],bel[N];
signed main(){
	scanf("%lld %lld %lld",&n,&k,&q);
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i].fi);
		a[i].se=i;
		b[i]=a[i].fi;
	}
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++){
		d[a[i].se]=i;//第i个数的排名 
	}
	ans=a[q].fi-a[1].fi;
	for(int i=1;i<=n;i++){
		ll nw=1,cnt=0;
		ll minn=-1,maxn=-1;
		for(int j=1;j<=n;j++){
			if(d[j]<=i){
				nw++;continue;
			}
			lt[nw]++;
			bel[j]=nw;
		}
		for(int j=i+1;j<=n;j++){
			if(lt[bel[a[j].se]]>=k){
				cnt++;
				lt[bel[a[j].se]]--;
				if(minn==-1)	minn=a[j].fi;
				maxn=a[j].fi;
			}
			if(cnt==q)	break;
		}
		for(int j=1;j<=nw;j++){
			lt[j]=0;
		}
		for(int j=1;j<=n;j++){
			bel[j]=0;
		}
		if(cnt<q)	break;
		ans=min(ans,maxn-minn);
	}
	printf("%lld\n",ans);
	return 0;
}
/*
exSample:
10 2 4
1 4 9 3 2 5 5 9 9 9
*/

```


---

## 作者：AC_love (赞：0)

枚举 $X$，找最大的 $Y$。

最小值最大化，二分答案，考虑如何 check。

显然小于 $Y$ 的数不能出现在区间中。把小于 $Y$ 的数当做分割点，可以把整个序列分成很多段。

每一段我们都尽可能多的删，看看最后总共的操作次数是否超过了 $Q$ 即可。

[code](https://atcoder.jp/contests/arc098/submissions/59637592)

---

## 作者：shinkuu (赞：0)

发现最多只有 $n$ 个不同的最小值。考虑从小到大枚举最小值。

因为已知最小值，所以全部小于最小值的都不能被包含在任意一个区间内。相当于是把原序列分成了若干个区间，对于每个区间，如果其长度 $len<m$，则它是无法对答案产生贡献的。否则其中就最多有 $len-m+1$ 个数能产生贡献。贪心地取最小的 $len-m+1$ 个。

最后所有取出来的数的第 $Q$ 个即为当前最大值。每个最小值对应的极差的最小值即为答案。

时间复杂度 $O(n^2\log n)$。

code：

```cpp
int n,m,q,e[N];
bool vis[N];
vector<int> v,u;
void solve(){
	scanf("%d%d%d",&n,&m,&q);
	for(int i=1;i<=n;i++){
		scanf("%d",&e[i]);
	}
	int ans=inf;
	for(int i=1;i<=n;i++){
		v.clear();
		for(int j=1;j<=n;j++){
			if(vis[j]){
				continue;
			}
			u.clear();
			int k=j;
			u.push_back(e[k]);
			while(k<n&&!vis[k+1]){
				k++;
				u.push_back(e[k]);
			}
			if((int)u.size()<m){
				continue;
			}
			sort(u.begin(),u.end());
			for(int p=0;p<=(int)u.size()-m;p++){
				v.push_back(u[p]);
			}
			j=k+1;
		}
		sort(v.begin(),v.end());
		if((int)v.size()<q){
			break;
		}
		ans=min(ans,v[q-1]-v[0]);
		int mn=inf,pos=0;
		for(int j=1;j<=n;j++){
			if(!vis[j]&&(!pos||e[j]<mn)){
				mn=e[j];
				pos=j;
			}
		}
		vis[pos]=true;
	}
	printf("%d\n",ans);
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)solve();
}
```

---

