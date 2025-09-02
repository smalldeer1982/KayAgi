# [ARC176A] 01 Matrix Again

## 题目描述

给定一个 $N \times N$ 的矩阵，你需要向其中填入 $0$ 或 $1$，使其满足以下条件：

- $(A_1,B_1),(A_2,B_2),...,(A_M,B_M)$ 处的值为 $1$。
- 第 $i$ 行的所有数字之和为 $M$ $(1 \le i \le N)$。
- 第 $i$ 列的所有数字之和为 $M$ $(1 \le i \le N)$。

## 样例 #1

### 输入

```
4 2
1 4
3 2```

### 输出

```
8
1 2
1 4
2 1
2 4
3 2
3 3
4 1
4 3```

## 样例 #2

### 输入

```
3 3
3 1
2 3
1 3```

### 输出

```
9
1 1
1 2
1 3
2 1
2 2
2 3
3 1
3 2
3 3```

## 样例 #3

### 输入

```
7 3
1 7
7 6
6 1```

### 输出

```
21
1 6
2 4
4 1
7 3
3 6
4 5
6 1
1 7
7 6
3 5
2 2
6 3
6 7
5 4
5 2
2 5
5 3
1 4
7 1
4 7
3 2```

# 题解

## 作者：XYQ_102 (赞：5)

## 思路
行列从 $0$ 开始，以 $(i+j) \mod n$ 的值给每个格子编号，就像这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/13gn2jmh.png)

我们发现任选其中 $m$ 种编号的位置填上 $1$，得到的矩阵一定满足条件。那么具体在哪些编号上填 $1$ 呢？

- 首先，输入给定的格子所在的编号一定要填。
- 其次，只按照第 $1$ 条，可能凑不够 $m$ 种，这种情况，就要在非输入给定的格子编号中任意挑选若干个，能凑成 $m$ 种编号就行。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int main(){
	cin>>n>>m;
	vector<bool> vis(n);
	for(int i=1;i<=m;i++){
		int x,y;
		cin>>x>>y;
		x--,y--;
		vis[(x+y)%n]=1;
	}
	vector<int> ans;
	for(int i=0;i<n;i++) if(vis[i]) ans.push_back(i);
	for(int i=0;i<n;i++) if(!vis[i]&&ans.size()<m) ans.push_back(i);
	cout<<n*m<<endl;
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			int x=i,y=(ans[j]-i+n)%n;
			cout<<x+1<<" "<<y+1<<endl;
		}
	}
	return 0;
}
```

---

## 作者：Creeper_l (赞：4)

> 题意：给定 $n$，以及 $m$ 对 $(a_i,b_i)$，你需要构造一个 $n \times n$ 的 $01$ 矩阵使得每行每列都恰好有 $m$ 个数为 $1$，且 $(a_i,b_i)$ 的位置上的数必须为 $1$。

首先我们考虑 $m=1$ 的情况，会发现最终的 $1$ 的分布一定是形如一条斜线。

进而我们会发现如果选满足 $i+j \equiv k \pmod{n}$ 的所有 $(i,j)$（$k$ 为一个定值，即形如一条斜线的点）填上 $1$，那么恰好满足每行每列都有一个数为 $1$。因为题目要求每行每列都恰好有 $m$ 个数为 $1$，于是我们选 $m$ 个不同的 $k$ 即可。但是题目还要求了 $(a_i,b_i)$ 必须为 $1$，所以对于每一个 $k=(a_i+b_i) \bmod n$ 都必须选。因为输入的 $(a_i,b_i)$ 为 $m$ 个，所以必须选的 $k$ 不超过 $m$ 个，一定有解。其余的 $k$ 随便选即可。时间复杂度 $O(nm)$。

```
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2e5 + 10;
int n,m,sum;
bool vis[MAXN];
signed main() {
	cin >> n >> m;
	for(int i = 1,a,b;i <= m;i++) {
		cin >> a >> b;
		if(!vis[(a + b) % n])
			vis[(a + b) % n] = 1,sum++;
	} printf("%lld\n",n * m);
	for(int i = 0;i < n;i++) {
		if(vis[i] || sum < m) {
			if(vis[i] == false) sum++;
			for(int j = 1;j <= n;j++)
				printf("%lld %lld\n",j,(i - j + 2 * n - 1) % n + 1);
		}
	} return 0;
}
```

---

## 作者：未来姚班zyl (赞：3)

没怎么做过构造题，导致这道构造题卡了我 40 min，别人打假算都能速通，导致我 perf 没上橙。

## 题目大意

你需要构造一个大小 $n\times n$ 的 $01$ 矩阵，使得每行、每列上 $1$ 的个数都等于 $m$，其中已经钦定了 $m$ 个点是 $1$。



## 题目分析

这题有个很有暗示性的特征：钦定的点数和最后要求的和一样。

如果抓住这个特征，构造就很简单，否则就会浪费时间在各种胡思乱想上。

这个特征暗示我们将矩阵中的位置分成若干不相交的组，使得总可以选择当中的任意 $m$ 组来构造答案。

所以我们可以选对角线 $x=y$，与其循环上下移动得到的 $n$ 条斜线。每一条这样的线都可以使每一行、每一列的和 $+1$，任意选 $m$ 根即可，钦定的点相当于钦定了对角线。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define int ll
#define L x<<1
#define R L|1
#define mid (l+r>>1)
#define lc L,l,mid
#define rc R,mid+1,r
#define OK Ll<=l&&r<=Rr
#define Root 1,1,n
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define repn(x) rep(x,1,n)
#define repm(x) rep(x,1,m)
#define pb push_back
#define e(x) for(int i=h[x],y=to[i];i;i=nxt[i],y=to[i])
#define E(x) for(auto y:p[x])
#define Pi pair<int,int>
#define ui unsigned ll
inline int read(){int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57)s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
inline void pf(ll x){if(x<0) putchar('-'),x=-x;if(x>9)pf(x/10);putchar(x%10+48);}
using namespace std;
const int N =1e5+5,M=4e6+5,inf=(1LL<<31)-1,mod=998244353;
const ll llf=1e18;
inline void add(int &a,int b){((a+=b)>=mod) and (a-=mod);}
inline int Add(int a,int b){return add(a,b),a;}
inline int mul(int a,int b){return 1LL*a*b%mod;}
inline void Mul(int &a,int b){a=mul(a,b);}
inline void red(int &a,int b){add(a,mod-b);}
inline int Red(int a,int b){return red(a,b),a;}
inline int qp(int a,int b){if(!b)return 1;int c=qp(a,b>>1);Mul(c,c);if(b&1)Mul(c,a);return c;}
inline int INV(int x){return qp(x,mod-2);}
int n,m;
struct node{
	int x,y;
}a[N];
vector<node>ans;
vector<int>p;
bool v[N];
inline void Main(){
	n=read(),m=read();
	repm(i){
		a[i].x=read(),a[i].y=read();
		int w;
		if(a[i].x>=a[i].y)w=a[i].x-a[i].y;
		else w=a[i].x+n-a[i].y;
		if(!v[w])p.pb(w),v[w]=1;
	}
	repn(i){
		if((int)p.size()==m)break;
		if(!v[i])p.pb(i);
	}
	for(auto k:p){
		repn(i)ans.pb({(i+k-1)%n+1,i});
	}
	cout <<n*m<<'\n';
	for(auto y:ans)cout <<y.x<<' '<<y.y<<'\n';
}
signed main(){
	int T=1;
	while(T--)Main(); 
	return 0;
}
```

---

## 作者：Shadow_T (赞：2)

### 题目分析

一看到这一题我们可以很容易想到一个假思路：

先将一定要加的点加入矩阵，对于矩阵我用两个数组 $h$，$l$ 维护第 $i$ 行数值和，第 $i$ 列数值和。

然后我们统计出来每行每列为了达到目标还差多少。然后我们发现组合一次就可以某行数值和加 $1$，某列数值和加 $1$。那么我们把这些不够行列组合一遍，注意不要重复点。

但是我们发现，样例 $3$ 过不去。原因是按顺序组合有可能让后面的行列无论怎么组合都已经重复过了。

那么我们考虑随机化和前面的置换，先把后面已经无法组合的统计出来，然后和前面的随机化找一个判断可不可以交换一下其中的行或列，如果可以就交换，否则在查找一遍。

一开始我在赛时写了最多随机 $15$ 次，但其实这是不必要的，导致我赛时过了，后来过不去 **after_contest**，换成直接置换到查找到合适的交换对象为止，就过了。

[赛时 AC](https://atcoder.jp/contests/arc176/submissions/52658734) | [赛后被卡](https://atcoder.jp/contests/arc176/submissions/52749861) | [更改后通过](https://atcoder.jp/contests/arc176/submissions/52754914)

所以这个赛后数据好像也没卡掉随机化数据。其实这个算法应该是卡不掉的。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+10;
vector<int> ans1,ans2;
int h[maxn],l[maxn];
map<pair<int,int>,bool> mp;
//int ans[1001][1001];
signed main()
{
	srand(time(0));
	int n,m;
	cin>>n>>m;
	int ym=m;
	while(m--)
	{
		int x,y;
		cin>>x>>y;
		h[x]++,l[y]++;
		ans1.push_back(x);
		ans2.push_back(y);
		mp[{x,y}]=true;
	}
	for(int i=1;i<=n;i++)
	h[i]=ym-h[i];
	for(int i=1;i<=n;i++)
	l[i]=ym-l[i];
	int pos=1;
	for(int i=1;i<=n;i++)
	{
		while(l[pos]==0) pos++;
		for(int j=pos;j<=n;j++)
		{
			if(h[i]>0&&l[j]>0&&!mp[{i,j}])
			ans1.push_back(i),ans2.push_back(j),h[i]--,l[j]--,mp[{i,j}]=true;
			if(h[i]==0) break;
		}
	}
	vector<int> ca,cb;
	for(int i=1;i<=n;i++)
	while(h[i]>0) ca.push_back(i),h[i]--;
	for(int i=1;i<=n;i++)
	while(l[i]>0) cb.push_back(i),l[i]--;
	for(int i=0;i<ca.size();i++)
	{
		while(true)
		{
			int r=rand()%ans2.size();
			if(r<=ym) continue;
			if(mp[{ca[i],ans2[r]}]) continue;
			if(mp[{ans1[r],cb[i]}]) continue;
			mp[{ans1[r],ans2[r]}]=false;
			mp[{ca[i],ans2[r]}]=true;
			mp[{ans1[r],cb[i]}]=true;
			swap(cb[i],ans2[r]);
			ans1.push_back(ca[i]);
			ans2.push_back(cb[i]);
			break;
		}
	}
	cout<<ans1.size()<<"\n";
	for(int i=0;i<ans1.size();i++)
	cout<<ans1[i]<<" "<<ans2[i]<<"\n";
}
```

---

## 作者：aeiouaoeiu (赞：1)

考虑当 $m=1$ 时如何构造。在没有强制格时，我们从小到大贪心地确定给每一行涂黑格子的列号（形如 $(i,i)$），不妨将这些格子叫做“主格子”。

有强制格时，我们标记强制格的列号已经被使用，用一样的方法确定“主格子”。

如何拓展到 $m>1$？在没有强制格时,我们贪心给每个“主格子”都向左延一格（超出边界就从另一头开始）。

有强制格时，我们要额外记录一行中强制点与“主格子”的列间距，保证强制格都被涂黑；在涂完所有出现的列间距对应的格子后，如果还没有到 $m$，我们可以简单地从小到大找还没有涂过的列间距涂。

```cpp
#include<bits/stdc++.h>
#define pb emplace_back
#define pob pop_back
#define mp make_pair
using namespace std;
typedef long long ll;
typedef double db;
const ll maxn=100007,ee=1000000000000000007ll,p=998244353;
ll n,m,a[maxn],b[maxn],ma[maxn],lid[maxn],vis[maxn],cnt[maxn];
vector<ll> vec[maxn],ld;
vector<pair<ll,ll> > ans;
int main(void){
	//freopen("data.in","r",stdin);
	//freopen("data.out","w",stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	ll Tccs=1;
	//cin>>Tccs;
	for(int tcs=1;tcs<=Tccs;tcs++){
		cin>>n>>m;
		for(int i=1;i<=m;i++){
			cin>>a[i]>>b[i];
			vec[a[i]].pb(b[i]);
		}
		for(ll i=1,l=1;i<=n;i++){
			sort(vec[i].begin(),vec[i].end());
			for(auto x:vec[i])if(!vis[x]){ma[i]=x,vis[x]=1; break;}
		}
		for(ll i=1,l=1;i<=n;i++){
			if(!ma[i]){
				for(;vis[l];l++);
				ma[i]=l,vis[l]=1;
			}
			for(auto x:vec[i]){
				if(x<ma[i]) lid[n-ma[i]+x]=1;
				else if(x>ma[i]) lid[x-ma[i]]=1;
			}
		}
		for(int i=1;i<=n;i++)if(lid[i]) ld.pb(i);
		if((ll)ld.size()<m-1)for(int i=1;i<n;i++){
			if(!lid[i]) ld.pb(i);
			if((ll)ld.size()>=m-1) break;
		}
		for(int i=1;i<=n;i++){
			ans.pb(i,ma[i]);
			for(auto x:ld) ans.pb(i,(ma[i]+x)%n);
		}
		cout<<ans.size()<<"\n";
		for(auto x:ans){
			cout<<x.first<<" "<<(x.second?x.second:n)<<"\n";
			//cnt[(x.second?x.second:n)]++;
		}
		//sort(cnt+1,cnt+1+n);
		//for(int i=1;i<n;i++)if(cnt[i]!=cnt[i+1]) cout<<"qwq\n",exit(0); cout<<"awa\n";
		//for(int i=1;i<=n;i++) cout<<ma[i]<<"\n"; cout<<"\n";
	}
	return 0;
}
```

---

## 作者：I_will_AKIOI (赞：1)

考虑贪心。

我们按行考虑，每行都要放置 $m$ 个数。我们需要防止发生冲突，也就是不出现有 $1$ 没法放的情况。

所以我们就看列的数量来确定第 $i$ 行的 $m$ 个数放哪里。最好的方法是放在和最小的那一列，这样可以有更多的列可以放其他数，选择性更多，产生冲突的可能性就更小。至于和最小，我们可以使用 set 维护。

但是我们同时发现，有一些格子必须为 $1$。这时候这些格子所在的行的选择性就越小，所以我们可以优先处理。


```
#include<bits/stdc++.h>
#pragma GCC optimize("O3")
using namespace std;
int n,m,ans,a[100005],b[100005],vis[100005];
map<int,int>v[100005];
vector<pair<int,int> >op,del;
set<pair<int,int> >s;
int main()
{
  ios::sync_with_stdio(0);
  cin>>n>>m;
  ans=m;
  for(int i=1;i<=m;i++)
  {
    int x,y;
    cin>>x>>y;
    op.push_back({x,y});
    v[x][y]=1;
    a[x]++;
    b[y]++;
    vis[x]=1;//记录是否需要优先处理
  }
  for(int i=1;i<=n;i++) s.insert({b[i],i});
  for(int i=1;i<=n;i++)
  {
    if(vis[i]==0) continue;
    del.clear();
    for(auto it=s.begin();it!=s.end();it++)//不断选择和最小的一列
    {
      if(a[i]>=m) break;//填写a[i]个数
      auto w=*it;
      int x=w.first,y=w.second;
      if(v[i][y]==0)//已经填了，跳过
      {
        ans++;
        op.push_back({i,y});
        del.push_back({x,y});
        a[i]++;
      }
      
    }
    for(int j=0;j<del.size();j++) s.erase(del[j]),s.insert({del[j].first+1,del[j].second});
  }
  for(int i=1;i<=n;i++)
  {
    if(vis[i]) continue;
    del.clear();
    for(auto it=s.begin();it!=s.end();it++)
    {
      auto w=*it;
      int x=w.first,y=w.second;
      if(v[i][y]==0)
      {
        ans++;
        op.push_back({i,y});
        del.push_back({x,y});
        a[i]++;
      }
      if(a[i]>=m) break;
    }
    for(int j=0;j<del.size();j++) s.erase(del[j]),s.insert({del[j].first+1,del[j].second});
  }
  cout<<ans<<"\n";
  for(int i=0;i<op.size();i++) cout<<op[i].first<<" "<<op[i].second<<"\n";
  return 0;
}
```

---

## 作者：ben090302 (赞：0)

考虑斜线构造，一条斜线可以做到给每行每列一个 $1$，这是非常好的，而且两条斜线互相不会干扰，当然这个斜线实际是环状的：每次往左上走一步放 $1$，到达边界就飞到另一边，从左边界到右边界，上到下。

从每个给定点出发去跑斜线，如果经过了别的给定点就说明还要额外再找点出发，这样肯定是可以的，但是实现可能有点复杂。

我们可以考虑对于每个给定点 $O(n)$ 的找出其对应的在第一行的点，从这些点跑即可，如果少了就顶多 $O(n)$ 的扫一遍底端点补到 $m$ 个即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=100005;
int n,m;
int x,y;
bool ok[N];
int main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cin>>x>>y;
        while(x>1){
            x--,y++;
            if(y==n+1) y=1;
        }
        ok[y]=1;
    } 
    int sum=0;
    for(int i=1;i<=n;i++){
        if(ok[i]) sum++;
    }
    int pos=1;
    while(sum<m){
        while(ok[pos]) pos++;
        ok[pos]=1,sum++;
    }
    cout<<n*m<<endl;
    for(int i=1;i<=n;i++){
        if(ok[i]){
            int x=1,y=i;
            while(x<=n){
                cout<<x<<" "<<y<<endl;
                x++,y--;
                if(y==0) y=n;
            }
        }
    }
}
```

---

