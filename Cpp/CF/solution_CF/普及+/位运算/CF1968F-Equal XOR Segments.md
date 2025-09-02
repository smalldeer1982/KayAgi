# Equal XOR Segments

## 题目描述

Let us call an array $ x_1,\dots,x_m $ interesting if it is possible to divide the array into $ k>1 $ parts so that [bitwise XOR](http://tiny.cc/xor_wiki_eng) of values from each part are equal.

More formally, you must split array $ x $ into $ k $ consecutive segments, each element of $ x $ must belong to exactly $ 1 $ segment. Let $ y_1,\dots,y_k $ be the XOR of elements from each part respectively. Then $ y_1=y_2=\dots=y_k $ must be fulfilled.

For example, if $ x = [1, 1, 2, 3, 0] $ , you can split it as follows: $ [\color{blue}1], [\color{green}1], [\color{red}2, \color{red}3, \color{red}0] $ . Indeed $ \color{blue}1=\color{green}1=\color{red}2 \oplus \color{red}3\oplus \color{red}0 $ .

You are given an array $ a_1,\dots,a_n $ . Your task is to answer $ q $ queries:

- For fixed $ l $ , $ r $ , determine whether the subarray $ a_l,a_{l+1},\dots,a_r $ is interesting.

## 说明/提示

Explanation for the first test case:

The first query is described in the statement.

In the second query, we should divide $ [1,2,3] $ . A possible division is $ [1,2],[3] $ , since $ 1\oplus 2=3 $ .

It can be shown that for queries $ 3,4,5 $ , the subarrays are not interesting.

## 样例 #1

### 输入

```
4
5 5
1 1 2 3 0
1 5
2 4
3 5
1 3
3 4
5 5
1 2 3 4 5
1 5
2 4
3 5
1 3
2 3
7 4
12 9 10 9 10 11 9
1 5
1 7
2 6
2 7
11 4
0 0 1 0 0 1 0 1 1 0 1
1 2
2 5
6 9
7 11```

### 输出

```
YES
YES
NO
NO
NO

YES
NO
NO
YES
NO

NO
NO
NO
NO

YES
NO
YES
YES```

# 题解

## 作者：LEE114514 (赞：8)

## 思路

首先，$k$ 只有 $2,3$ 两种取值，因为假设存在相邻 $3$ 段区间异或和都为 $x$，把他们看成一段大序列后异或值为 $x \oplus x \oplus x = x$ 没有改变。记 $S_n=\bigoplus_{i=1}^na_i$，特别的，$S_0=0$。 


然后假设有两段异或值一样的，分别为 $[l,x]$ 和 $[x+1,r]$ 那么有 $S_x \oplus S_{l-1}=S_r \oplus S_{x}$，得 $S_{l-1}=S_{r}$，所以只要 $l\not=r$ 并且 $S_r=S_{l-1}$ 就一定可行，输出 `YES`。

如果不满足，再考虑有三段。类似的，可得 $S_x \oplus S_{l-1}=S_y \oplus S_x=S_r \oplus S_y$，其中 $x < y$。

整理一下，得

$$
\begin{cases}
S_{l-1}=S_y\\
S_r=S_x\\
x<y\\
\end{cases}
$$

那么，取最小 $x$ 和最大 $y$，如果 $x_{min} \ge y_{max}$，那么就无解，否则可行。

## Code

本来只是想测试一下，结果一不小心过了，写法比较逆天。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=2e5+5;
int T,n,m,x,y;
int a[maxn],b[maxn],c[maxn],len;
map<int,vector<int> > mp;
vector<int>::iterator posx,posy;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&m);
		mp.clear();
		for(int i=1;i<=n;++i) scanf("%d",a+i),a[i]^=a[i-1],mp[a[i]].emplace_back(i);
		while(m--){
			scanf("%d%d",&x,&y);
			if(a[y]==a[x-1]){
				puts("YES");
				continue;
			}
			posy=lower_bound(mp[a[x-1]].begin(),mp[a[x-1]].end(),y);
			posx=lower_bound(mp[a[y]].begin(),mp[a[y]].end(),x);
			if(posy==mp[a[x-1]].begin()||posx==mp[a[y]].end()) puts("NO");
			else --posy,puts(*posx<*posy&&*posx>=x&&*posy<=y?"YES":"NO");
		}
		putchar('\n');
	}
}
```

---

## 作者：Special_Tony (赞：8)

倒数第一分钟提交成功，同时带我在 CF 的第 $5$ 场比赛中上青，留念。![](https://cdn.luogu.com.cn/upload/image_hosting/dbty3357.png)
# 思路
异或的性质：
1. $x\oplus x=0$；
1. $a\oplus b=b\oplus a$；
1. 若 $x\oplus y=z$，则 $y\oplus z = x,x\oplus z=y$。

这题首先想到做一个前缀异或和，设 $s_i=a_1\oplus a_2\oplus\dots\oplus a_i,S=a_l\oplus a_{l+1}\oplus\dots\oplus a_{r-1}\oplus a_r=s_r\oplus s_{l-1}$，若 $S=0$，则一定有解，因为 $a_l$ 一组，剩下的数一组即可。不然就一定得是奇数组，且每组的异或和都是 $S$，若是偶数组 $S$ 就一定是 $0$ 了。

接下来我们证明若可以分为奇数组数，则一定可以分为 $3$ 组数：设 $a_l\sim a_r$ 可以分为 $x$ 组数，每组的异或和都是 $S$，则把任意 $3$ 组连续的数合并为一组，结果不变，依然成立。

此时我们只要寻找两个分界点即可。定义一些 vector 数组 $v$，$v_i$ 里存的是 $S_j=i$ 时，递增的所有 $j$。第一段 $a_l\sim a_{x_1}$，这一段的异或和是 $S$，所以 $s_{x_1}=s_{l-1}\oplus S=s_r$，我们贪心地在 $v_{s_r}$ 中二分找到第一个 $\ge l$ 的下标作为 $x_1$，若找不到或 $x_1\ge r$ 则无解；然后继续二分找第二三段的分界线，我们又在 $v_{s_{l-1}}$ 中找到第一个 $>x_1$ 的数作为 $x_2$，如果找不到或 $x_2\ge r$ 则无解（此处 $\ge r$ 而不是 $>r$ 是因为第三段不能为空）。其它情况就有解了！
# 代码
```cpp
# include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair <int, int> pii;
int t, n, q, l, r, x, tmp, a[200005], tot;
map <int, int> mp;
vector <int> v[200005];
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> t;
	while (t --) {
		cin >> n >> q;
		tot = 0, mp.clear ();
		for (int i = 1; i <= n; ++ i) {
			v[i].clear ();
			cin >> a[i], a[i] ^= a[i - 1];
			if (! mp[a[i]])
				mp[a[i]] = ++ tot;
			v[mp[a[i]]].emplace_back (i);
		}
		while (q --) {
			cin >> l >> r;
			if (! (a[r] ^ a[l - 1])) {
				cout << "YES\n";
				continue ;
			}
			tmp = mp[a[r]];
			x = lower_bound (v[tmp].begin (), v[tmp].end (), l) - v[tmp].begin ();
			if (x >= v[tmp].size () || v[tmp][x] >= r) {
				cout << "NO\n";
				continue ;
			}
			tmp = mp[a[l - 1]];
			x = lower_bound (v[tmp].begin (), v[tmp].end (), v[mp[a[r]]][x]) - v[tmp].begin ();
			if (x >= v[tmp].size () || v[tmp][x] >= r) {
				cout << "NO\n";
				continue ;
			}
			cout << "YES\n";
		}
		cout << '\n';
	}
	return 0;
}
```

---

## 作者：lin_er (赞：3)

# CF1968F题解
  说实话前面的题解已经讲得非常详细了，大致思路就是去讨论一下 $[l,r]$ 的区间异或和，如果是0，则一定可以分成偶数个相同区间，进一步讲也一定可以分成两个区间（~~事实上随便一分都是相同的两个区间~~，所以一旦这段区间异或和为零直接输出 `YES` 就完了。
  
  下面讨论区间异或和不为零的情况，显然如果能分成异或和相同区间则一定是奇数个，且一定能分成三段区间，并且任意的两段区间异或和都为零，所以如果我们能找到一段以 $a_l$  开始的异或和为零的区间，一段以 $a_r$ 结尾的异或和为零的区间，同时这两个区间能覆盖 $[l,r]$ 的话，就能将其分成三个异或和相同区间，便满足题目要求输出 `YES`，否则输出  `NO`。
  
  上文提到的多次求区间异或和的操作，自然能想到利用前缀异或和，依据 $x\oplus x=0$ 的特性，求 $[l,r]$ 的区间异或和就是前缀和 $q_r\oplus q_{l-1}$，查找异或和为零的区间就是在找两段异或和相同的前缀，即若 $q_x\oplus q_y=0$，则 $[y+1,x]$ 的区间异或和为零，于是我们可以用 ``vector`` 存储前缀和相同的位置，用二分查找。
  
  由于这题 $a_i$ 值较大，可以用离散化或 ``map`` 帮助进行存储（毕竟我们只用相等的条件）。
  
  最后附上代码（~~由于作者码风不好，听懂思路就不用看了~~）。
```cpp
#include"bits/stdc++.h"
using namespace std;
const int N=2e5+10;
struct zz{
	int x,id;
}a[N];
bool cmp(zz aa,zz bb){
	if(aa.x<bb.x){
		return true;
	}
	if(aa.x==bb.x){
		return aa.id<bb.id;
	}
	return false;
}

int p[N],T,n,q,b,d[N];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>T;
	for(int t=1;t<=T;t++){
	vector <int> v[N];
		cin>>n>>q;
		for(int i=1;i<=n;i++){
			cin>>p[i];
			p[i]^=p[i-1];
			a[i].x=p[i];
			a[i].id=i;
		}
		sort(a,a+n+1,cmp);
		int tot=0;
		for(int i=0;i<=n;i++){
			if(i==0||a[i].x!=a[i-1].x){
				tot++;
			}
			d[a[i].id]=tot;
			v[tot].push_back(a[i].id);
		}
		for(int i=1;i<=q;i++){
			int l,r,rmax,lmax;
			cin>>l>>r;
			if((p[r]^p[l-1])==0){
				cout<<"YES"<<'\n';
				continue;
			}
			int ll=0,rr=v[d[l-1]].size()-1;
			while(ll<rr){
				int mid=(ll+rr+1)>>1;
				if(v[d[l-1]][mid]>r){
					rr=mid-1;
				}
				else ll=mid;
			}
			rmax=v[d[l-1]][rr];
			ll=0,rr=v[d[r]].size()-1;
			while(ll<rr){
				int mid=(ll+rr)>>1;
				if(v[d[r]][mid]>=l-1){
					rr=mid;
				}
				else ll=mid+1;
			}
			lmax=v[d[r]][ll]+1;
			if(rmax>=lmax){
				cout<<"YES"<<'\n';
			}
			else cout<<"NO"<<'\n';
		}
		cout<<'\n';
	}
}
```
人生第一篇题解结束~~。

---

## 作者：ilibilib (赞：2)

## 分析：

先求得前缀异或和，记为 $s$ 数组。

我们发现，一个数列能被分为 $k$ 段时。

###### $k$ 为偶数时

那么前 $\frac{k}{2}$ 与后 $\frac{k}{2}$ 段的异或和肯定相等，也就是这个数列肯定能被分为 $2$ 段。

###### $k$ 为奇数时

前 $k-2$ 段合在一起，根据异或的性质，异或和不变，也就是这个数列肯定能被分为 $3$ 段。

所以我们只用考虑 $k=2$ 以及 $k=3$ 情况。

###### 若 $k=2$

存在一个位置 $x\in[l,r]$。

$$s[x] \oplus s[l-1] = s[r] \oplus s[x]$$

两边同时异或上 $s[x]$ 得：

$$s[r]=s[l-1]$$

即这一段异或和为 $0$，很容易判断。

###### 若 $k=3$

存在 $x\in[l,r],y\in[l,r],x\le y$。

$$s[x]\oplus s[l-1]=s[y]\oplus s[x-1]=s[r] \oplus s[y-1]$$

$$s[y]\oplus s[l-1]=s[r] \oplus s[x-1] = 0$$

即 $s[y]=s[l-1],s[x-1]=s[r]$，那么就在 $[l,r]$ 中找到第一个 $s[x-1]=s[r]$ 以及最后一个 $s[y]=s[l-1]$，判断 $x\le y$ 是否即可。

可以用桶轻松解决，但不知道为什么当初用了莫队，无伤大雅。

## code：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int a[N],b[N],s[N],last[N];
bool ans[N];
struct mask{int l,r,p,k;}ask[N];
inline bool mcmp(const mask &a,const mask &b){return a.r<b.r;}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int T;cin>>T;
	while(T--)
	{
		int n,m,l,r,fk;cin>>n>>m;
		for(int i=1;i<=n;++i) cin>>a[i],s[i]=s[i-1]^a[i],b[i]=s[i];sort(b+1,b+n+1);
		for(int i=1;i<=n;++i) s[i]=lower_bound(b+1,b+n+1,s[i])-b;
		if(b[1]==0) s[0]=1;else s[0]=0;
		for(int i=1;i<=m;++i)
		{
			ans[i]=0;
			cin>>ask[i].l>>ask[i].r;
			ask[i].p=i;
			ask[i].k=s[ask[i].r];
		}
		sort(ask+1,ask+m+1,mcmp);
		for(int r=-1,i=1;i<=m;++i)
		{
			while(r<ask[i].r) last[s[++r]]=r;
			ask[i].r=last[s[ask[i].l-1]];
		}

		for(int i=0;i<=n;++i) last[i]=0;

		sort(ask+1,ask+m+1,mcmp);
		for(int r=-1,i=1;i<=m;++i)
		{
			while(r<ask[i].r) last[s[++r]]=r;
			ask[i].k=last[ask[i].k];
		}
		for(int i=0;i<=n;++i) last[i]=0;
		for(int i=1;i<=m;++i) if(ask[i].k>=ask[i].l&&ask[i].k<=ask[i].r) ans[ask[i].p]=true;
		for(int i=1;i<=m;++i)
		{
			if(ans[i]) cout<<"YES\n";
			else cout<<"NO\n";
		}
		cout<<'\n';
		for(int i=0;i<=n;++i) s[i]=0;
	}
	return 0;
}
```

---

## 作者：Muse_Dash (赞：2)

关于区间和（子区间和）的问题，容易想到前缀和。我们令 $pre_i$ 表示 $\oplus_{i=1}^ia_i$，即前缀异或和。

注意到异或有自反性，所以当 $num\oplus num'=0$ 也就有 $num=num'$，$\oplus_{i=l}^ra_i=pre_r\oplus pre_{l-1}$。

当 $pre_r=pre_{l-1}$ 的时候，此时在区间内找到任意一个节点 $i,i\neq r$，那么 $[l,i]$ 和 $(i,r]$ 就是一组解（$[l,i]$ 和 $(i,r]$ 的异或和是 $0$，因为 $pre_r\oplus pre_{l-1}=\oplus_{i=l}^ra_i=0$，那么两个区间的异或和也是相同的），事实上这种情况直接判断正确即可。

当 $pre_r\neq pre_{l-1}$ 的时候，我们可以考虑找到区间内两个点 $i,i'$，使得 $[l,i],(i,i'],(i',r]$ 的异或和相同，显然因为 $[l,i],(i,i']$ 异或和相同，所以 $pre_{i'}=pre_{l-1}$，同理 $pre_r=pre_i$，可以对每个 $pre$ 的数值做映射 `vector`，在 `vector` 上面二分找到最左边的可能的 $i$ 和最右边的 $i'$，判断是否有 $i<i'$ 即可。映射 `vector` 的下标用 `map` 来做，因为 $pre$ 的值域达到了 $2^{30}$。

---

## 作者：Super_Cube (赞：1)

# Solution

记对 $a$ 做前缀异或和的结果为 $s$。假设区间 $l\sim r$ 中搞出了一个端点 $i$，那么有 $s_{l-1}\oplus s_i=s_i\oplus s_r$，提取出 $s_{l-1}=s_r$；假设有两个断点 $i,j$，那么有 $s_{l-1}\oplus s_i=s_i\oplus s_j=s_j\oplus s_r$，提取出 $s_{l-1}=s_j,s_i=s_r$；再多断点同理也能提取出类似的等式。首先特判 $l=r$，因为题目要求 $k>1$。剩下的情况根据前面的分析得出当 $s_{l-1}=s_r$ 区间一定能找到一个断点；否则若能在 $[l,r)$ 中找到一对 $i,j$ 满足 $s_{l-1}=s_i$，$s_r=s_j$ 且 $i\ge j$，则说明区间合法。至于找的方法可用二分，这部分并不是本题难点。

---

## 作者：_JF_ (赞：1)

[Link](https://www.luogu.com.cn/problem/CF1968F)

观察性质，然后摁做，做出来了。

题目要求各个部分异或和相等。自然联想到一个 $x \oplus x=0$。

分类讨论一下。

- 如果异或和恰好为 $0$，首先 $k$ 为偶数，且每段相同的话，一定满足这里的条件，但问题是，你这个必要性怎么说明？

很多题解都没有讲吧。我认为是，存在另外两种情况，是 $k$ 为偶数/奇数，但是每段不同。

我们目前的条件是异或和为 $0$，说明对于 $1$ 而言，只能出现偶数次。若 $k$ 为奇数，我们不妨把前 $x-1$ 个段合并。然后根据奇偶性分类讨论即可。

$k$ 为偶数同理。最后我们发现都能归并到“$k$ 为偶数，且每段相同”的条件上。

- 如果异或和不为 $0$，那么只能是，分成奇数段，然后每个段相同。

注意到每个段的异或和就是查询 $[l,r]$ 的异或和 $x$， 这里容易想到把连续区间的异或和转化成前缀的东西。记为 $s$。

那我们现在是知道了 $s[l-1]$ 和 $x$，相当于要找 $s_j=x\oplus s[l-1]$。

我们还注意到这个 $s_j$ 最好尽可能靠左。这样有利于我们后面的查找。（可能靠右也没有关系？因为往右还要合法，只能是新增的区间异或和为 $0$，但是这样就要特殊考虑 $[l,r]$ 异或和为 $0$ 的情况了。）

在区间里面找一个数有没有出现过，还是静态的，直接 `vec` 二分即可。

~~主播开始提出了对每个数进行一个动态开点线段树的做法，也是神人了。~~


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N =1e6+10;
#define int long long
#define DEBUG cout<<"how to fuck win";
vector<int> g[N];
map<int,int> mp;
int n,q,l,r,s[N],a[N],tot;
signed main(){
	int T;
	cin>>T;
	while(T--){
		
		cin>>n>>q;
		for(int i=1;i<=n;i++){
			cin>>a[i],s[i]=s[i-1]^a[i];
			if(mp[s[i]]==0)	mp[s[i]]=++tot;
			g[mp[s[i]]].push_back(i);
		}
		while(q--){
			cin>>l>>r;
			if(r-l+1==1)	{cout<<"NO"<<endl; continue;}
			if((s[r]^s[l-1])==0){cout<<"YES"<<endl; continue;}
			int Trusr=mp[s[r]];
			auto now=lower_bound(g[Trusr].begin(),g[Trusr].end(),l);
			int pre=(s[r]^s[l-1]);
			if(now==g[Trusr].end()||((*now)>=r))	{cout<<"NO"<<endl; continue;}
			int lst=(*now)+1,lst1=mp[pre^s[lst-1]];
	//		cout<<(pre^s[lst-1]);
	//		cout<<lst<<" "<<lst1<<endl;
			now=lower_bound(g[lst1].begin(),g[lst1].end(),lst);
			if(now==g[lst1].end()||((*now)>r))	{cout<<"NO"<<endl; continue;}
			cout<<"YES"<<endl; 
		}	 
		for(int i=1;i<=n;i++)	g[mp[s[i]]].clear(),s[i]=0,mp[s[i]]=0;
	}
	return 0;
}

```

---

## 作者：zhangxiaohan007 (赞：1)

## 思路
通过分析题目，我们不难发现，一个数列可能有偶数或奇数个元素。如果有偶数个元素，则它一定可以分成两个序列，输出```YES```；反之进行判断。
## 代码
```cpp
#include<bits/stdc++.h>
#define ll long long
#define db double
#define inf 2e9
using namespace std;
int n,q,sum[200005],a[200005],tot=1;
map<int,int>mp;
vector<int>s[200005];
void solve()
{
	mp.clear();
	
	cin>>n>>q;
	for(int i=1;i<=n;i++) s[i].clear();
	sum[0]=0;
	tot=1;
	pair<int,int>ss;
	ss.first=sum[0];
	ss.second=tot;
	tot++;
	if(mp.count(sum[0])==0)mp.insert(ss);
	s[mp[sum[0]]].push_back(0);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		sum[i]=sum[i-1]^a[i];
		pair<int,int>ss;
		ss.first=sum[i];
		ss.second=tot;
		tot++;
		if(mp.count(sum[i])==0)mp.insert(ss);
		s[mp[sum[i]]].push_back(i);
	}
	for(int i=1;i<=q;i++)
	{
		int u,v,wl,wr,ans1=-1,ans2=-1;
		scanf("%d%d",&u,&v);
		wl=mp[sum[u-1]];
		wr=mp[sum[v]];
		if((sum[v]^sum[u-1])==0)
		{
			cout<<"YES\n";
			continue;
		}
		int l=0,r=s[wr].size()-1,mid;
		while(l<=r)
		{
			mid=(l+r)/2;
			if(s[wr][mid]>=u)
			{
				ans1=mid;
				r=mid-1;
			}
			else l=mid+1;
		}
		if(ans1==-1||s[wr][ans1]>=v)
		{
			cout << "NO" << endl;
			continue;
		}
		l=0,r=s[wl].size()-1,mid;
		while(l<=r)
		{
			mid=(l+r)/2;
			if(s[wl][mid]>s[wr][ans1])
			{
				ans2=mid;
				r=mid-1;
			}
			else l=mid+1;
		}
		if(ans2==-1||s[wl][ans2]>v)cout<<"NO\n";
		else cout<<"YES\n";
	}
	cout<<"\n";
}
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		solve();
	}
	return 0;
}

```

---

## 作者：ran_qwq (赞：1)

设前缀异或和为 $s_i$，左端点为 $p_i$，右端点为 $q_i$（设 $q_0=l-1$）。因为要不重不漏地划分，所以 $q_k=r,p_i=q_{i-1}+1$。

则第 $i$ 段异或和 $y_i=s_{q_i}\operatorname{xor}s_{p_i-1}=s_{q_i}\operatorname{xor}s_{q_{i-1}}$。又 $t_1=t_2=\dots=t_k$，所以 $s_{q_1}\operatorname{xor}s_{q_0}=s_{q_2}\operatorname{xor}s_{q_1}=\dots=s_{q_k}\operatorname{xor}s_{q_{k-1}}$。

我们拆开来看，先看第一个等号两边。同时异或上 $s_{q_1}$，得到 $s_{q_2}=s_{q_0}$。类似的，得到 $s_{q_i}=s_{q_{i-2}}$。就是奇数项的 $s_{q_i}$ 相等，偶数项也相等。

因此我们可以消掉连续两个区间（因为异或和为 $0$）。于是，只需要考虑 $k=2$ 或 $3$ 的情况。

$k=2$ 的情况好办，其充要条件是 $s_{l-1}=s_{r}$。

$k=3$ 的情况就是找一个数对 $(i,j)$，令第一个区间为 $[l,i]$，第二个区间为 $[i+1,j]$，第三个区间为 $[j+1,r]$。

则需要满足 $s_j=s_{l-1},s_i=s_r$，并且 $l\le i<j<r$。

考虑贪心，使 $i$ 尽量小且 $i\ge l$，使 $j$ 尽量大且 $j<r$，尽量满足 $i<j$。

我们需要找 $l-1$ 右边第一个 $s_i=s_{l-1}$ 的 $i$，和 $r$ 左边第一个 $s_j=s_r$ 的 $j$。

这个可以用你喜欢的 STL（如 vector 和 set）存下标后二分。但是值域极大，需要离散化。

---

## 作者：沉石鱼惊旋 (赞：0)

# 题目翻译

给定 $n$ 个数 $a_1,a_2,\dots a_n$。有 $q$ 个询问。

每次询问给出 $l,r$，询问是否可以将 $a_l,a_{l+1},\dots a_r$ 分为 $k>1$ 段，使得每一段异或后相同。

$1\leq n,q\leq 2\times 10^5$。多测。$1\leq \sum n,\sum q\leq 2\times 10 ^5$。

# 题目思路

首先，如果分成 $2$ 段或者 $3$ 段合法，可以证明分成更多段一定合法。如果分成 $2$ 段和 $3$ 段不合法，可以证明分成更多段一定不合法。

因为拆分成更多段一定可以拆成一个 $2$ 段和 $3$ 段。证明显然，自己稍微试几个就懂了。

那么就有一个 $\mathcal O(qn^2)$ 的做法。枚举分割点 $p$ 和 $(p,q)$，则判断是否满足 $\bigoplus\limits_{i=l}^p=\bigoplus\limits_{i=p+1}^r$ 或 $\bigoplus\limits_{i=l}^p=\bigoplus\limits_{i=p+1}^q=\bigoplus\limits_{i=q+1}^r$。

那么可以用类似前缀和的方式优化这一段异或。写出来就是判断是否满足 $b_{l-1}\oplus b_p=b_r\oplus b_p$ 和 $b_{l-1}\oplus b_p=b_q\oplus b_p =b_r\oplus b_q$。

容易发现由于异或的性质 $b_{l-1}\oplus b_p=b_r\oplus b_p$ 也就是 $b_r=b_{l-1}$，分成两段很好处理，直接判断就完了。

分成三段需要稍微处理一下。类似于两段的做法，我们就是需要找到合法的 $p,q$ 满足 $l\leq p\lt q\lt r$ 且 $b_{l-1}=b_p \operatorname{and} b_r=b_q$。

那么我们考虑把相同的一个异或 $x$ 扔到一个 vector 叫 $have_x$ 里，存前缀异或为 $x$ 的位置，那么每次二分处理即可。

异或很大我们提前离散化一下。

时间复杂度 $\mathcal O(q\log n)$。

# 代码链接

写的有点丑。

注意不能每次拷贝一个 STL 容器，hack 杀疯了。

<https://codeforces.com/contest/1968/submission/259198233>

---

## 作者：DrAlfred (赞：0)

摘要：异或，贪心，莫队

[传送门：https://www.luogu.com.cn/problem/CF1968F](https://www.luogu.com.cn/problem/CF1968F)

本题解介绍一种本题的莫队做法。~~是谁赛时打了个贼长的莫队还挂了我不说。~~ 

## 题意

我们称一个数列 $x_1, x_2, \cdots, x_m$ 有意思，当且仅当它可以被分成 $k > 1$ 个部分，使得每个部分的异或和都相等。

现在给定一个长度为 $n$ 的数列 $a$，$q$ 次询问 $a$ 的子段 $a_l, a_{l + 1}, \cdots, a_r$ 是不是有意思。

## 分析思路

首先我们注意到一个性质：对于 $k > 3$ 的拆分，一定能够转化为 $k = 2$ 或 $k = 3$ 的拆分（读者可以自行思考原因）。

我们记 $s_i = a_1 \oplus a_2 \oplus \cdots \oplus a_i$，即异或前缀和。

对于 $k = 2$ 的拆分，因为两段的异或和相等，则最终两段异或起来是 $0$，有 $s_r = s_{l - 1}$，相反若 $s_r = s_{l - 1}$ 则 $[l, r]$ 一定能有一个 $k = 2$ 的拆分，对于这种情况我们特判直接输出 `YES` 即可。 

剩下的情况 $k = 3$。注意到在 $s$ 中我们一定需要找到两个位置 $l \leq x_1 \leq x_2 < r$，将原序列分为 $[l, x_1], [x_1 + 1, x_2], [x_2 + 1, r]$ 三部分，且这三部分的异或和相等。因为这三段总的异或起来是 $s_r \oplus s_{l - 1}$，中间有两段相等的抵消了，那么这三段的异或和也都是 $s_r \oplus s_{l - 1}$。

总结一下，我们有：

$$
s_{x_1} \oplus s_{l - 1} = s_{x_2} \oplus s_{x_1} = s_r \oplus s_{x_2} = s_{r} \oplus s_{l - 1} 
$$

于是我们可以得到：$s_{x_1} = s_r, s_{x_2} = s_{l - 1}$。

我们贪心地寻找在 $[l, r]$ 内最小的 $x_1$ 与 最大的 $x_2$，并且判断是否满足 $x_1 \leq x_2$ 即可。

找到这样两个位置的过程可以通过莫队完成。具体来说，我们用 `std::deque` 记录当前段内每个 $s$ 出现的位置的集合，取其 `front/back` 即可。

$s$ 数组可以提前离散化一下，减少一个 `std::map` 带来的 $O\left(\log n\right)$ 的复杂度。

注意可能最多有 $n + 1$ 个不同的 $s$，清空的时候注意多清空一个位置。

总时间复杂度 $O\left(n \log n + n \sqrt n\right)$，可以通过本题。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 200010;
template <class _Tp>
struct Mess {
    std::vector<_Tp> v;
    bool initialized = false;
    inline _Tp origin(int idx) { return v[idx - 1]; }
    inline void insert(_Tp x) { v.push_back(x); }
    template <typename T, typename... V>
    inline void insert(T x, V... v) { insert(x), insert(v...); }
    inline void init(void) {
        sort(v.begin(), v.end()), initialized = true;
        v.erase(unique(v.begin(), v.end()), v.end());
    }
    inline int query(_Tp x) {
        if (!initialized) init();
        return lower_bound(v.begin(), v.end(), x) - v.begin() + 1;
    }
};
struct Query {
    int l, r, idx;
} Q[N];
deque<int> pos[N];
int a[N], s[N], ms[N];
int t, n, m, l, r, ans1[N], ans2[N];
inline void solve(void) {
    Mess<int> M;
    cin >> n >> m, M.insert(0);
    for (int i = 1; i <= n; i++) {
        cin >> a[i], pos[i].clear();
        M.insert(s[i] = s[i - 1] ^ a[i]);
    }
    pos[n + 1].clear(); // 1. M 中可能有 n + 1 个元素！！！
    for (int i = 0; i <= n; i++) {
        ms[i] = M.query(s[i]);
    }
    for (int i = 1; i <= m; i++) {
        cin >> l >> r, Q[i] = {l, r, i};
    }
    const int B = sqrt(n);
    auto cmp = [=](Query a, Query b) -> bool {
        // 2. a.l / b != b.l / B！！ 不是等于！！
        if (a.l / B != b.l / B) return a.l < b.l;
        return (a.l / B) & 1 ? a.r < b.r : a.r > b.r;
    };
    l = 1, r = 0, sort(Q + 1, Q + 1 + m, cmp);
    auto add = [&](int x) -> void {
        if (pos[ms[x]].empty() || x < pos[ms[x]][0]) {
            pos[ms[x]].push_front(x);
        } else {
            pos[ms[x]].push_back(x);
        }
    };
    auto del = [&](int x) -> void {
        if (pos[ms[x]][0] == x) {
            pos[ms[x]].pop_front();
        } else {
            pos[ms[x]].pop_back();
        }
    };
    auto query1 = [&](int val) -> int { // last pos
        return pos[val].empty() ? -1 : pos[val].back();
    };
    auto query2 = [&](int val) -> int { // first pos
        return pos[val].empty() ? -1 : pos[val][0];
    };
    for (int i = 1; i <= m; i++) {
        while (Q[i].l < l) add(--l);
        while (r < Q[i].r) add(++r);
        while (l < Q[i].l) del(l++);
        while (Q[i].r < r) del(r--);
        ans1[Q[i].idx] = query1(ms[Q[i].l - 1]);
        ans2[Q[i].idx] = query2(ms[Q[i].r]);
    }
    for (int i = 1; i <= m; i++) {
        if (ans1[i] == -1 || ans2[i] == -1) {
            cout << "NO\n";
            continue;
        }
        cout << (ans2[i] <= ans1[i] ? "YES" : "NO") << '\n';
    }
    cout << '\n';
}
inline void optimizeIO(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
}
int main(int argc, char const *argv[]) {
    optimizeIO(), cin >> t;
    while (t--) solve();
    return 0;
}
```

---

## 作者：junee (赞：0)

# CF1968F 题解

## 题目分析

我们可以发现当 $k>3$ 时，我们可以将其转化为 $k=2$ 或者 $k=3$ 的情况，这个证明还是比较简单的。当 $k$ 是奇数时，我们可以将其拆分为 $x,x,x  \oplus x \oplus \dots x $，而我们知道 $x \oplus x \oplus x = x$。当 $k$ 是偶数时，我们可以将其拆分为两部分，而 $x \oplus x =0$。

然后我们考虑当什么时候可以将其拆成两部分，由于 $x \oplus x = 0$，所以我们可以想到用一个类似前缀和的思想存储前缀异或和，当满足异或和数组满足 $a_{l-1} = a_r$，显然是可以的。

当考虑拆成三部分 $\left[l,x\right],\left[x+1,y\right],\left[y+1,r\right]$，则我们需要满足 $a_x \oplus a_{l-1} = a_y \oplus a_x = a_r \oplus a_y$，然后考虑用二分查找最小的 $x,y$ 且 $ x \le y$。

## Code

```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<map>
#include<vector>
using namespace std;
const int N=2e5+10;
int a[N],T,n,q;
map<int,vector<int>> mp;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n>>q;
		mp.clear();
		mp[0].push_back(0);
		for(int i=1;i<=n;i++){
			cin>>a[i];
			a[i]^=a[i-1];
			mp[a[i]].push_back(i);
		}
		while(q--){
			int l,r;
			cin>>l>>r;
			if(a[l-1]==a[r])cout<<"YES"<<'\n';
			else{
				if(*--lower_bound(mp[a[l-1]].begin(),mp[a[l-1]].end(),r)>*lower_bound(mp[a[r]].begin(),mp[a[r]].end(),l))cout<<"YES"<<'\n';
				else cout<<"NO"<<'\n';
			}
		}
	}
	return 0;
}

```

---

