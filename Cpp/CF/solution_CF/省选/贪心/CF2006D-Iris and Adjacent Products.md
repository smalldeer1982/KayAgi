# Iris and Adjacent Products

## 题目描述

Iris has just learned multiplication in her Maths lessons. However, since her brain is unable to withstand too complex calculations, she could not multiply two integers with the product greater than $ k $ together. Otherwise, her brain may explode!

Her teacher sets a difficult task every day as her daily summer holiday homework. Now she is given an array $ a $ consisting of $ n $ elements, and she needs to calculate the product of each two adjacent elements (that is, $ a_1 \cdot a_2 $ , $ a_2 \cdot a_3 $ , and so on). Iris wants her brain to work safely, and in order to do that, she would like to modify the array $ a $ in such a way that $ a_i \cdot a_{i + 1} \leq k $ holds for every $ 1 \leq i < n $ . There are two types of operations she can perform:

1. She can rearrange the elements of the array $ a $ in an arbitrary way.
2. She can select an arbitrary element of the array $ a $ and change its value to an arbitrary integer from $ 1 $ to $ k $ .

Iris wants to minimize the number of operations of type $ 2 $  that she uses.

However, that's completely not the end of the summer holiday! Summer holiday lasts for $ q $ days, and on the $ i $ -th day, Iris is asked to solve the Math homework for the subarray $ b_{l_i}, b_{l_i + 1}, \ldots, b_{r_i} $ . Help Iris and tell her the minimum number of type $ 2 $ operations she needs to perform for each day. Note that the operations are independent for each day, i.e. the array $ b $ is not changed.

## 说明/提示

In the first test case, as Iris can always multiply $ 1 $ and $ 1 $ together, no operations are needed, so the answer is $ 0 $ .

In the second test case, the first day's homework is $ [1, 10, 9] $ . Iris can rearrange its elements to get $ [9, 1, 10] $ , so no operations of type $ 2 $ are needed. The second day's homework is $ [10, 9] $ , and she can change one element to get the array $ [1, 9] $ , so one operation of type $ 2 $ is needed.

## 样例 #1

### 输入

```
5
3 1 1
1 1 1
1 3
3 2 10
1 10 9
1 3
2 3
5 4 2
2 2 2 2 2
1 2
2 4
2 5
1 5
6 5 10
3 2 5 10 10 1
1 4
3 6
1 6
2 5
5 6
10 10 10
10 9 8 7 6 5 4 3 2 1
1 10
1 9
1 8
1 7
2 10
3 10
4 10
5 10
3 9
6 8```

### 输出

```
0 
0 1 
1 1 2 2 
1 1 1 1 0 
3 3 4 3 2 2 1 1 2 1```

# 题解

## 作者：IvanZhang2009 (赞：2)

这个题初始的 idea 是 irris 的（关于“可以重排使得邻项积不超过 $i$”的重排方案）。后来讨论了一下出到了序列上，做法是我给的。

这个题卡空间是因为开二维数组常数太大了，做法几乎不变的同时，隐形强制要求小常数避免卡常。当然莫队可以直接解决。

题意：对于一个序列，你可以做单点修改（任何时刻值域都是 $[1,k]$）或序列重排。定义权值为最小的单点修改次数使得任意相邻两个数的乘积不超过 $k$。区间查询权值。$1\le \sum n,\sum q\le 10^5,1\le k\le 10^6$。

解法：考虑最优的重排方式，先放最大值，然后最小值，然后次大值等等地交替放。于是序列合法当且仅当每个 $i$ 大值和 $i$ 小值的乘积都不超过 $k$（$\bf{1\le i\le \frac n2}$）。

> 上述结论的证明：
> 
> 先证明最大值放第一个更优。如果存在一个同样可行的方法最大值不在第一个，我们可以把以最大值结尾的这个前缀 reverse，直接达成不劣的效果。
>
> 再考虑最小值放第二个更优。如果存在一个同样可行的解最小值不在第二个，我们考虑当前的第二个和最小值，由于都可以放在 max 旁边，所以对于所有数都可以放它们旁边，是等价的。于是交换这两个数结果不变。
>
> 所有数都可以放到最小值旁边，于是变成 $n'=n-2$ 的子问题，于是得证。

设 $c(l,r)$ 表示值域在 $[l,r]$ 的值的个数。考虑转化：对于每个 $i\le \sqrt k$，都有 $cnt(1,i)\ge cnt(\frac{k}{i},k)$。这个 $cnt$ 本质不同只有 $2\sqrt k$ 个，暴力前缀和求出来，然后列个式子就好了（修改显然是把 $\max$ 改成 $1$，这是容易的），需要注意长度为奇数时最中间一项不需要考虑，也就是上面的 $cnt$ 需要和 $\frac n2$ 取 $\min$。推推式子就能算出来了，而且每个 $i$ 独立。

考虑卡空间，由于各 $i$ 独立，离线后枚举 $i$ 再枚举询问，空间 $O(n+q+\sqrt k)$。时间复杂度 $O((n+q)\sqrt k)$。莫队也是可以的，空间线性。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define MOD         998244353
#define speMOD      2933256077ll
#define pii         pair<int,int>
#define all(v)      v.begin(),v.end()
#define pb          push_back
#define REP(i,b,e)  for(int i=(b);i<(int)(e);++i)
#define over(x)     {cout<<(x)<<endl;return;}
#define lowbit(x)   ((x)&(-(x)))
#define cntbit(x)   __builtin_popcount(x)
#define rf(v)       shuffle(all(v),sd);
#define deal(v)     sort(all(v));v.erase(unique(v.begin(),v.end()),v.end())
#define lbound(v,x) lower_bound(all(v),x)-v.begin()
int n,q,r;
int a[300005];
int sum[300005];
int ql[300005],qr[300005];
int ans[300005];
int cnt[300005],cnt2[300005];
void Main() {
	cin>>n>>q>>r;
	REP(i,0,n)cin>>a[i];
	sum[0]=0;
	int B=sqrt(r);
	REP(i,0,n)sum[i+1]=sum[i]+(a[i]<=B);
	REP(i,0,q){
		int x,y;
		cin>>x>>y;
		--x,--y;
		ql[i]=x;qr[i]=y;
		ans[i]=0;
		if(sum[y+1]-sum[x]<(y-x+1)/2)ans[i]=(y-x+1)/2-sum[y+1]+sum[x];
	}
	REP(i,0,B){
		REP(j,0,n+1)cnt[j]=cnt2[j]=0;
		REP(j,0,n){
			cnt[j+1]=cnt[j]+(a[j]<=i);
			cnt2[j+1]=cnt2[j]+(a[j]<=r/(i+1));
		}
		REP(j,0,q){
			int x=ql[j],y=qr[j],l=y-x+1;
			int c1=cnt2[y+1]-cnt2[x],c2=cnt[y+1]-cnt[x];
			ans[j]=max(ans[j],min((l-c1-c2+1)/2,l/2-c2));
		}
	}
	REP(i,0,q)cout<<ans[i]<<' ';
	cout<<endl;
}
void TC() {
    int tc=1;
    cin>>tc;
	while(tc--){
		Main();
		cout.flush();
	}
}
signed main() {
	return cin.tie(0),cout.tie(0),ios::sync_with_stdio(0),TC(),0;
}
/*
1. CLEAR the arrays (ESPECIALLY multitests)
2. DELETE useless output
 */

```

---

## 作者：wrkwrkwrk (赞：1)

相关人员：验题人

---------
先考虑对于一次询问如何做。根据数论分块知识可以知道本质不同的数的种类是 $O(\sqrt k)$ 个。改变一个数一定是贪心地改成 $1$。

考虑模拟构造过程。倒数第 $i$ 类数旁边的数一定是正数第 $i$ 类数前。从最大和最小的数贪心连接。贪心取得最大的数在最前面，如果前面放下的最后一个数是大数，则将其放入这个周期处理。之后交替计算放入，小的数放完大的数变化，直到计算完成就是答案。

对于每次询问，只需要计算出每类数各有几个即可。

考虑到直接用前缀和计算答案也许会 MLE，故以大小为 $B$ 分块即可。

时间复杂度 $O(q(B+\sqrt R))$。

验题代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
namespace _wrk{;
#define int long long
int b[100005];
const int B=32;
signed p[101005/B][2503];
int re[2503];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	int t;
	cin>>t;
	while(t--){
		int n,q,R;
		cin>>n>>q>>R;
		for(int i=1;i<=n;i++){
			cin>>b[i];
		}
		vector<int>u;
		for(int l=1;l<=R;l=(R/(R/l))+1){
			u.push_back(l);
		}
		for(int i=B;i<=n;i+=B){
			int h=i/B;
			for(int j=1;j<=u.size();j++){
				p[h][j]=p[h-1][j];
			}
			for(int w=i-B+1;w<=i;w++){
				p[h][upper_bound(u.begin(),u.end(),b[w])-u.begin()]++;
			}
		}
		while(q--){
			int l,r;
			cin>>l>>r;
			for(int i=1;i<=u.size();i++)re[i]=0;
			for(;l%B!=1&&l<=r;l++){
				re[upper_bound(u.begin(),u.end(),b[l])-u.begin()]++;
			}
			for(;r%B&&l<=r;r--){
				re[upper_bound(u.begin(),u.end(),b[r])-u.begin()]++; 	
			}
			
			if(l<=r)for(int i=1;i<=u.size();i++){
				re[i]+=p[r/B][i]-p[(l-1)/B][i];
			}
			
			int a=0,ans=0;
			int h=0;
			int ll=1,rr=u.size();
			while(ll<rr){
				
				a+=re[ll];
				if((re[rr]||re[ll])){
					if(h){
						ans++;a++;h=0;
					}
					int w=re[rr];
					int c=min(a,w);
					a-=c;w-=c;
					int p=w/2;
					ans+=p;
					h=w-p*2;
				}
				ll++;rr--;
			}
			if(ll==rr){
				if(re[ll]&&h) ans++;
			}
			cout<<ans<<' '; 
			
		}
		cout<<'\n';
	}
	return 0;
}
}
signed main(){
	   return _wrk::main();
}
```

（注：本题原来空间限制 128MB，之后出题人看到我的代码想搞成32MB，但是上面的 $B=32$，正好卡进去。）

---

## 作者：DaiRuiChen007 (赞：0)

[Problem Link](https://www.luogu.com.cn/problem/CF2006D)

**题目大意**

> 定义一个数组是好的当且仅当可以重排该数组使得邻项乘积 $\le k$。
>
> 给定 $a_1\sim a_n$，$q$ 次询问某个子区间至少要修改多少个元素才是好的。
>
> 数据范围：$n,q\le 10^5,k\le 10^6$。

**思路分析**

先考虑什么样的数组是好的，对于所有 $>\sqrt  k$ 的数只能和 $\le \sqrt k$ 的数放一起，因此对于每个 $i$，$\le i$ 的元素数量要超过 $\ge k/i$ 的元素数量。

注意 $n=2t+1$ 的时候可以有 $t+1$ 个 $\ge k/i$ 的元素和 $t$ 个 $\le i$ 的元素，因此出现次数要和 $\left\lfloor\dfrac n2\right\rfloor$ 取 $\min $。

用莫队或分块等方式维护区间中元素的出现次数。

每次修改一定是把 $>\sqrt k$ 的元素变成 $1$，求答案对每个 $i$ 计算后求最大值。

时间复杂度 $\mathcal O(n+q(\sqrt n+\sqrt k))$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1e5+5;
int n,k,q,a[MAXN];
int lp[325],rp[325],bl[MAXN];
int x[325][1005],y[325][1005],c[1005],d[1005];
void solve() {
	cin>>n>>q>>k;
	for(int i=1;i<=n;++i) cin>>a[i];
	int B=sqrt(n),lim=sqrt(k);
	for(int i=1;(i-1)*B+1<=n;++i) {
		lp[i]=(i-1)*B+1,rp[i]=min(i*B,n);
		memcpy(x[i],x[i-1],sizeof(x[i]));
		memcpy(y[i],y[i-1],sizeof(y[i]));
		for(int j=lp[i];j<=rp[i];++j) {
			bl[j]=i;
			if(a[j]<=lim) ++x[i][a[j]];
			else ++y[i][k/a[j]];
		}
	}
	for(int l,r;q--;) {
		cin>>l>>r;
		memset(c,0,sizeof(c));
		memset(d,0,sizeof(d));
		if(bl[l]==bl[r]) {
			for(int j=l;j<=r;++j) {
				if(a[j]<=lim) ++c[a[j]];
				else ++d[k/a[j]];
			}
		} else {
			for(int j=l;j<=rp[bl[l]];++j) {
				if(a[j]<=lim) ++c[a[j]];
				else ++d[k/a[j]];
			}
			for(int j=lp[bl[r]];j<=r;++j) {
				if(a[j]<=lim) ++c[a[j]];
				else ++d[k/a[j]];
			}
			for(int j=1;j<=lim;++j) {
				c[j]+=x[bl[r]-1][j]-x[bl[l]][j];
				d[j]+=y[bl[r]-1][j]-y[bl[l]][j];
			}
		}
		int s=0;
		for(int j=1;j<=lim;++j) {
			c[j]+=c[j-1],d[j]+=d[j-1];
			s=max(s,min((d[j]-c[j]+1)/2,(r-l+1)/2-c[j]));
		}
		cout<<s<<" ";
	}
	cout<<"\n";
}
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int _; cin>>_;
	while(_--) solve();
	return 0;
}
```

---

