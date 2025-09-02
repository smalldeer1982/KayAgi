# Same Sum Blocks (Hard)

## 题目描述

本题有两个版本，区别仅在于 $ n $ 的取值范围。

给定一个整数数组 $ a[1], a[2], \dots, a[n] $。一个区块（block）指的是一段连续的元素 $ a[l], a[l+1], \dots, a[r] $（$ 1 \le l \le r \le n $）。因此，一个区块由一对下标 $(l, r)$ 定义。

请找出一组区块 $(l_1, r_1), (l_2, r_2), \dots, (l_k, r_k)$，使得：

- 这些区块互不相交（即两两不重叠）。形式化地，对于任意两个区块 $(l_i, r_i)$ 和 $(l_j, r_j)$，若 $i \neq j$，则要么 $r_i < l_j$，要么 $r_j < l_i$。

- 每个区块内元素的和都相等。形式化地，有
$$
a[l_{1}] + a[l_{1} + 1] + \dots + a[r_{1}] = a[l_{2}] + a[l_{2} + 1] + \dots + a[r_{2}] = \dots = a[l_{k}] + a[l_{k} + 1] + \dots + a[r_{k}]
$$

- 区块的数量 $k$ 最大。形式化地，不存在另一组满足上述两个条件的区块集合 $(l_1', r_1'), (l_2', r_2'), \dots, (l_{k'}', r_{k'}')$，使得 $k' > k$。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1141F2/a32038d691a8fef036434bed64856f1bff592dde.png)
上图对应第一个样例，蓝色框表示区块。请编写程序，找出这样一组区块。

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
7
4 1 2 2 1 5 3
```

### 输出

```
3
7 7
2 3
4 5
```

## 样例 #2

### 输入

```
11
-5 -4 -3 -2 -1 0 1 2 3 4 5
```

### 输出

```
2
3 4
1 1
```

## 样例 #3

### 输入

```
4
1 1 1 1
```

### 输出

```
4
4 4
1 1
2 2
3 3
```

# 题解

## 作者：Austin0116 (赞：7)

# 分析
首先，我们可以发现 $n \le 1500$，$O(n^2)$ 左右时间复杂度完全可过。

我们可以先预处理出所有区间的和，然后对每个和处理出区间和等于它的区间 $[l,r]$。然后就可以转化为经典的[线段覆盖](https://www.luogu.com.cn/problem/P1803)问题，最后处理出最多的区间即为答案。时间复杂度为 $O(n^2 \log n)$。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,a[1505],sum[1505],l,r,s,summ;
struct ha{
	int x,l,r;
	inline bool operator < (const ha &o) const{//排序
		if(x!=o.x) return x<o.x;
		if(r!=o.r) return r<o.r;
		return l<o.l;
	}
};
vector<ha> b; 
vector<pair<int,int>> c,d;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		sum[i]=sum[i-1]+a[i];
	}
	for(int l=1;l<=n;l++) for(int r=l;r<=n;r++) b.push_back(ha{sum[r]-sum[l-1],l,r});//处理出各个区间和
	sort(b.begin(),b.end());
	for(int i=0;i<(int)b.size();i++){
		if(!i) l=i;
		else if(b[i].x!=b[i-1].x){
			r=i-1;
			s=summ=0;
			c.clear();
			for(int j=l;j<=r;j++) if(s<b[j].l){//处理线段覆盖问题
				summ++;
				s=b[j].r;
				c.push_back({b[j].l,b[j].r});
			} 
			l=i;
			if(summ>(int)d.size()){
				d.clear();
				for(pair<int,int> x:c) d.push_back(x);
			}
		}
	}
	r=(int)b.size()-1;
	s=summ=0;
	c.clear();
	for(int j=l;j<=r;j++) if(s<b[j].l){
		summ++;
		s=b[j].r;
		c.push_back({b[j].l,b[j].r});
	} 
	if(summ>(int)d.size()){
		d.clear();
		for(pair<int,int> x:c) d.push_back(x);
	}
	printf("%d\n",(int)d.size());
	for(pair<int,int> x:d) printf("%d %d\n",x.first,x.second);
	return 0;
}

```

---

## 作者：OcTar (赞：6)


[题目传送门](https://www.luogu.com.cn/problem/CF1141F2)
# 思路
预处理出数列的前缀和，然后枚举每一段区间。由于区间和可能很大，所以不能直接开桶数组记录，对可能的区间和离散化（在此题的 Easy 版本中，似乎可以不用）。

于是我们先做前缀和，再用两层循环枚举区间，用一个 vector 记录左右端点和区间数量，找到区间数量最多的和，再进行结构体排序，于是问题就变成了简单的贪心问题（前置芝士：[线段覆盖问题](https://www.luogu.com.cn/problem/P1803)）
# 代码
```cpp
#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <cstdio>
using namespace std;
const int maxn = 1510;//注意数据范围
struct node {
    int l, r;
    bool operator < (const node &p) const { //结构体排序
        return r < p.r;
    }
} ;
map<int, int> T;
vector<node> S[maxn * maxn]; //离散化
vector<node> ans[maxn * maxn];  //记录答案
int n, tot = 0;
int a[maxn];
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", a + i);
        a[i] += a[i - 1];  //可以直接在原数组上预处理前缀和
        for (int j = 1; j <= i; j++) { //枚举每段区间
            int tmp = a[i] - a[j - 1];
            //离散化过程
            if (T[tmp] == 0) {
                T[tmp] = ++tot;
            }
            S[T[tmp]].push_back(node{j, i});
        }
    }
    //贪心部分：线段覆盖问题
    for (int i = 1; i <= tot; i++) {
        sort(S[i].begin(), S[i].end());
        int r = 0;
        for(int j = 0; j < S[i].size(); j++) {
            if (S[i][j].l > r) {
                ans[i].push_back(node{S[i][j].l, S[i][j].r});
                r = S[i][j].r;
            }
        }
    }
    //找到区间最多的和
    int pos = 0;
    for (int i = 1; i <= tot; i++) {
        if (ans[pos].size() < ans[i].size()) {
            pos = i;
        }
    }
    printf("%d\n", ans[pos].size());
    for (int i = 0; i < ans[pos].size(); i++) {
        printf("%d %d\n", ans[pos][i].l, ans[pos][i].r);
    }
    return 0;
}
```
祝大家 NOIP 2023 rp++ ！

---

## 作者：Tx_Lcy (赞：4)

[更差的阅读体验](https://www.cnblogs.com/tx-lcy/p/16851409.html)

[题目传送门](https://www.luogu.com.cn/problem/CF1141F2)

## 思路

简单题。

不妨先预处理出每一个区间的 $\sum$，然后离散化 $\sum$，对于每个 $\sum$ 开一个 $\verb!vector!$ 记录所有区间的左右端点。

然后枚举每个 $\sum$，求最多的区间，这是一个简单的贪心问题，可以用 $\verb!set!$ 轻松完成。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int const N=3e6+10;
int a[N],lsh[N];
vector< pair<int,int> >qans,anss;
struct node{int l,r,val;}q[N];
vector< pair<int,int> >ins[N];
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int n;cin>>n;int k=0;
    for (int i=1;i<=n;++i) cin>>a[i];
    for (int i=1;i<=n;++i){
        int res=0;
        for (int j=i;j<=n;++j){
            res+=a[j];lsh[++k]=res;
            q[k]={i,j,res};
        }
    }
    sort(lsh+1,lsh+k+1);int l=unique(lsh+1,lsh+k+1)-lsh-1;
    for (int i=1;i<=k;++i) ins[lower_bound(lsh+1,lsh+l+1,q[i].val)-lsh].push_back({q[i].l,q[i].r});
    for (int i=1;i<=l;++i) sort(ins[i].begin(),ins[i].end());
    for (int i=1;i<=l;++i){
        int len=(int)ins[i].size(),l=0;
        set< pair<int,int> >s;
        for (int j=0;j<len;++j) s.insert({ins[i][j].second,ins[i][j].first});
        int res=0;qans.clear();
        while (s.size()){
            while (s.size() && (*s.begin()).second<=l) s.erase(s.begin());
            if (!s.size()) break;
            l=(*s.begin()).first;
            qans.push_back({(*s.begin()).second,(*s.begin()).first});
            s.erase(s.begin());
        }
        if (qans.size()>anss.size()) anss=qans;
    }
    cout<<(int)anss.size()<<'\n';
    for (auto i:anss) cout<<i.first<<' '<<i.second<<'\n';
    return 0;
}
```


---

## 作者：Zisyhfollower (赞：2)

## 前言：

同学搞了一场 CF VP，然后这个题就在其中，于是来写一下题解。（虽然由于我晚打了没场切，但是我认为这顶多黄）

## 分析：

这里假定读者没有任何前置知识，但会熟练使用 STL。

首先没有和的限制的话，是一个简单的贪心。

我们考虑一下如何贪心：按照区间右端点大小排序，相同则按照左端点。

考虑这样为什么是对的。

为了让取到的区间尽可能多，于是我们希望右端点越左边越好，可以留出更多空间。

那么假设我现在按照这个策略选出来 $k$ 个区间，设最优解为 $r$，如果 $r>k$ 的话，那么这个策略是错的。但是按照此策略选出来的区间右端点是最多的（留的空间最多），所以 $r=k$，与上文矛盾，所以是对的。

然后现在加了和的限制，我们可以考虑把所有和相等的区间提出来，这个可以用 ```map```存储，然后搞一遍上面的贪心，这题就做完了。

至于时间复杂度，注意到每个区间只会出现一次，因此时间复杂度是 $\mathcal{O(n^2 \log n)}$ 的。

```cpp
# include <bits/stdc++.h>
# define int long long
# define pb push_back
using namespace std;
const int N = 2005;
int a[N],n,sum[N],ans;
map < int , vector< pair<int,int> > > sm;
vector < pair<int,int> > czzl;
int zy[N * N]  , cnt;
signed main () {
    ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
    cin >> n;
    for (int i = 1;i <= n;++i) cin >> a[i],sum[i] = sum[i - 1] + a[i];
    for (int l = 1;l <= n;++l) {
        for (int r = l;r <= n;++r) {
           sm[sum[r] - sum[l - 1]].pb({r,l});
           zy[++cnt] = sum[r] - sum[l - 1];
        }
    }
    sort (zy + 1,zy + cnt + 1);
    int len = unique(zy + 1,zy + cnt + 1) - zy - 1;
    cnt = len;
    for (int i = 1;i <= cnt;++i) {
        sort (sm[zy[i]].begin(),sm[zy[i]].end());
        int nl = sm[zy[i]][0].second,nr = sm[zy[i]][0].first,cnt = 1;
        vector < pair<int,int> > czl;
        czl.pb({nl,nr});
        for (int j = 1;j < sm[zy[i]].size();++j) {
            pair<int,int> now = sm[zy[i]][j];
            if (now.second > nr) nl = min(nl,now.second),nr = max(nr,now.first),++cnt,czl.pb({now.second,now.first});
        }
        if (cnt > ans) {
            ans = cnt;
            czzl.clear();
            for (auto x : czl) czzl.pb({x.first,x.second});
        }
    }
    cout << ans << "\n";
    for (auto x : czzl) cout << x.first << " " << x.second << "\n";
    return 0;
}
```

---

## 作者：sgl654321 (赞：2)

我的算法可能不是最优秀的，但是仍能够通过 F1 与 F2 两题。

## 题目大意
给定一个序列 $a$，请在其中取出尽可能多的不相交区间 $[l_i, r_i]$，使得所有区间的 $\sum_{k=l_i}^{r_i} a_k$ 相等。$n\le 1500$。

## 解题思路
显然我们可以用 $O(n^2)$ 拿出所有的 $[i,j]$，利用前缀和计算它们的和。我们把相同的和的 $[i,j]$ 放入同一个 `vector` 中。

那么对于每一个 `vector` 里面都有一些 $[i,j]$，其区间和相等。我们就是要在这个 `vector` 中取得尽可能多的不相交区间。

假如有两个区间 $[i_1,j_1]$ 和 $[i_2,j_2]$ 满足 $i_1\le  i_2\le j_2\le j_1$。那么这个包含别人的区间 $[i_1,j_1]$ 显然我们不会选。

为什么？因为会与 $[i_2,j_2]$ 相交的区间，与 $[i_1,j_1]$ 也一定相交。换句话说，选择 $[i_2,j_2]$ 一定更优秀。

我们去除了这些包含了其他区间的区间，就得到一串两两不包含的区间。放到另一个 `vector` 中。把这些区间按左端点从小到大排序之后，右端点也是从小到大递增的。

然后我们在这个新 `vector` 上跑 dp，用 $f_i$ 表示前 $i$ 个区间中最多能取出多少个。

转移很显然，$f_i=\max_{k=1}^{i - 1} f_k+1$，其中 $k$ 这个区间的右端点，要小于 $i$ 这个区间的左端点。这个转移就可以使用二分解决了，因为 $f_k$ 也是随着 $k$ 的变大而变大的。

因此总时间复杂度为 $O(n^2\log n)$。

### 参考代码
```cpp
#include<bits/stdc++.h>
#define maxn 2500010
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;

map<ll, ll> mp;
ll n, a[1510], x, cnt, m, now, f[maxn], las[maxn];
vector<pll> ve[maxn], c;
ll l, r, mid, pos, tot, ans;
pll as[maxn];

int main(){ 
	cin >> n;
	for(int i = 1; i <= n; i++) cin >> x, a[i] = a[i - 1] + x;
	for(int i = 1; i <= n; i++)
		for(int j = i; j <= n; j++){
			x = a[j] - a[i - 1];
			if(mp.find(x) == mp.end()) mp[x] = ++cnt;
			x = mp[x];
			ve[x].push_back(make_pair(i, j));
		}// 相同区间和的放入同一个 vector 中。
	for(int i = 1; i <= cnt; i++){
		sort(ve[i].begin(), ve[i].end());
		m = (ll)ve[i].size(); c.clear(); 
		
		c.push_back(make_pair(0, 0));
		c.push_back(ve[i][0]);
		now = ve[i][0].second;
		for(int j = 1; j < m; j++){
			while(c.size() > 1 && ve[i][j].second <= c[c.size() - 1].second) c.pop_back();
			c.push_back(ve[i][j]); now = ve[i][j].second;
		}
		// 去除包含别的区间的区间。
		m = (ll)c.size() - 1; 
		
		f[1] = 1; las[1] = 0; 
		for(int j = 2; j <= m; j++){
			l = 1; r = j - 1; pos = 0;
			while(l <= r){
				mid = (l + r) >> 1;
				if(c[mid].second < c[j].first){
					pos = mid;
					l = mid + 1;
				}else r = mid - 1;
			}
			f[j] = f[pos] + 1;
			las[j] = pos;
		} // 通过二分进行 dp 转移。
		if(f[m] > ans){
			ans = f[m]; now = m; tot = 0; 
			while(1){
				if(now == 0) break;
				as[++tot] = c[now];
				now = las[now];
			}
		}// 更新并记录答案。
	}
	cout << ans << endl;
	for(int i = 1; i <= ans; i++)
		cout << as[i].first << ' ' << as[i].second << endl;
	return 0;
}
```

---

## 作者：small_john (赞：2)

## 思路

简单题。

考虑维护出每种和的区间。发现值域比较大，但是最多只有 $n^2$ 种不同的值，离散化即可。

然后枚举每种和，问题就变成了给你很多个区间，求在满足选出的区间不交的情况下最多能选几个区间。这就是简单的贪心问题了（[P1803](https://www.luogu.com.cn/problem/P1803)），按右端点从小到大排序即可。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

template<typename T> inline void read(T &x)
{
	x = 0;
	T f = 1;char ch = getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
		{
			f = -1,ch = getchar();
			break;
		}
		ch = getchar();
	}
	while(ch>='0'&&ch<='9')
		x = (x<<3)+(x<<1)+ch-48,ch = getchar();
	x*=f;
}
template<typename T = int> inline T read()
{
	T x;read(x);return x;
}
template<typename T> void write(T x)
{
    if(x<0) x = -x,putchar('-');
    if(x>9) write(x/10);
    putchar(x%10+48);
}
template<typename T> inline void writen(T x)
{
    write(x);
    putchar(10);
}
const int N = 1505;
int n,m,a[N],s[N],b[N*N];
vector<pair<int,int>> v[N*N],ans;
signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	read(n);
	for(int i = 1;i<=n;i++)
		read(a[i]),s[i] = s[i-1]+a[i];
	for(int i = 1;i<=n;i++)
		for(int j = i;j<=n;j++)
			b[++m] = s[j]-s[i-1];
	sort(b+1,b+m+1),m = unique(b+1,b+m+1)-b-1;
	for(int i = 1;i<=n;i++)
		for(int j = i;j<=n;j++)
		{
			int w = lower_bound(b+1,b+m+1,s[j]-s[i-1])-b;
			v[w].push_back({j,i});
		}
	for(int i = 1;i<=m;i++)
	{
		sort(v[i].begin(),v[i].end());
		vector<pair<int,int> > now;
		int p = 0;
		for(auto j:v[i])
			if(j.second>p) now.push_back({j.second,j.first}),p = j.first;
		if(now.size()>ans.size()) ans = now;
	}
	writen(ans.size());
	for(auto i:ans) write(i.first),putchar(32),writen(i.second);
	return 0;
}
```

---

## 作者：Elairin176 (赞：2)

[传送门](https://www.luogu.com.cn/problem/CF1141F2)   
简单题。   
## 题意
选出 $k$ 个不相交区间，使得这 $k$ 个区间和都相等。要求输出最大的一个 $k$ 和 $k$ 取到最大时的一种方案。   
## 解法
观察到 $1\le n\le 1500$，所以我们可以枚举每个区间。   
我们先预处理出每个区间的和，再用 vector 建桶维护每个和的区间就可以实现预处理操作。   
因为我们要让 $k$ 最大，所以我们可以扫一遍所有可能的和，再贪心地选取区间使得当前 $k$ 最大，之后统计答案即可。    
注意预处理和的时候需要离散化。    
[CODE](https://www.luogu.com.cn/paste/t7fr8ql3)

---

## 作者：lijinghui (赞：1)

# CF1141F
## 题意
给一个序列，让你找到最多个无交集子串，使各个字串的和相同，输出子串个数及各段位置。

## 思路
CF1141F1：$dp_{i,j}$ 表示前 $i$ 个元素中每个区间和为 $j$ 的答案，那么有转移式：
$$dp_{i,j}=\max(dp_{i-1,j},dp_{k,j}[(\sum^i_k a) =j] )$$
但发现空间出现问题，将 $a$ 的所有可能的区间和进行离散化即可。

时间复杂度：$\Theta(n^3)$。

CF1141F2：因刚才的时间复杂度及空间复杂度不再适用，所以考虑贪心，我们可以直接枚举每个区间的和，将他们进行分类，然后可以发现该问题有点像 2024 CSP-S-T3。问题转化为在一堆区间中选择区间，使得区间无交集。首先若一区间包含另一区间，很明显选小的不劣于选大的，之后就是去掉这些包含小区间的大区间，让后优先靠左贪心选择即可。

因区间个数为 $n^2$ 级别的，再加离散化，平摊时间复杂度为为 $\Theta(n^2\log n^2)$，在 $5\times10^7$ 左右，若用 unordered_map 应该可以更优秀。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
// #define int long long
const int N=1.5e3+10;
vector< pair<int,int> >v[N*N];
map<int,int>mp;
int a[N];
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(NULL);cout.tie(NULL);
    int n,ans=0,txt=0;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        int cnt=0;
        for(int j=i;j;j--)
        {
            cnt+=a[j];
            if(!mp[cnt])mp[cnt]=++txt;
            if(v[mp[cnt]].empty()||j>v[mp[cnt]][v[mp[cnt]].size()-1].second)v[mp[cnt]].push_back(make_pair(j,i));
        }
    }
    for(int i=1;i<=txt;i++)
    {
        ans=max(ans,(int)v[i].size());
    }
    cout<<ans<<endl;
    for(int i=1;i<=txt;i++)
    {
        if((int)v[i].size()==ans)
        {
            for(int j=0;j<(int)v[i].size();j++)
            {
                cout<<v[i][j].first<<' '<<v[i][j].second<<endl;
            }
            return 0;
        }
    }
    return 0;
}
```

---

## 作者：初雪_matt (赞：1)

$n$ 很小，可以预处理出所有区间的和，也可以存下所有区间和相等的区间们，所以你可以枚举和，然后转换成了线段覆盖。

```cpp
#include<bits/stdc++.h>
#define int long long
#define N 1550
using namespace std;
int n,m,a[N],k;
set<int> res;
typedef pair<int,int> PII;
unordered_map<int,int> id;
vector<PII> mp[N*N];
signed main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++){
        int sum=0;
        for(int j=i;j<=n;j++){
            sum+=a[j];
            res.insert(sum);
            if(!id[sum]) id[sum]=++k;
            mp[id[sum]].push_back({j,i});
        }
    }
    int ans=0,pos=0;
    for(auto sum:res){
        sort(mp[id[sum]].begin(),mp[id[sum]].end());
        int now=0,sm=0;
        for(auto seg:mp[id[sum]]){
            if(seg.second>now) now=seg.first,sm++;
        }
        if(sm>ans){
            ans=sm;
            pos=sum;
        }
    }
    cout<<ans<<"\n";
    int now=0,sm=0;
    for(auto seg:mp[id[pos]]){
        if(seg.second>now){
            now=seg.first;
            cout<<seg.second<<" "<<seg.first<<"\n";
        }
    }
}
```

---

## 作者：tiaotiao (赞：1)

# 暴力预处理 + 贪心
总时间复杂度$ O(n^2) $
## 预处理
__首先$O(n^2)$预处理出所有的小块__
```cpp
    struct blk{
		int l;//左端点
		int r;//右端点
		int sum;//小块内的和
		void input(int a,int b,int c)
        	{l = a;r = b;sum = c;}
	
    }sb[MAXN*MAXN]; 
```

这里使用结构体存储小块的左端点、右端点和小块内的数字和
```cpp
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n-i+1;++j)
			sb[++sz].input(j,i+j-1,s[j+i-1]-s[j-1]);
```
这是预处理，s数组是原始数据的前缀和

## 贪心部分
接下来统计对于每种数值的不相交的最大块数量，并计入答案

首先对于块进行排序，以sum为第一关键字升序，对于sum相同的以r为第二关键字升序

对于数值相同的块，只需要贪心选取r最小的块，便可以选到最多不相交的块

__为什么？对于每一个块，我们希望它在右边留出尽量多的空间留给剩下的块，因此选择r小的。如果两个块有重叠，r小的块也能在右侧留出较小的空间__

sort比较函数
```cpp
	bool cmp(const blk &a,const blk &b){
		if(a.sum != b.sum)
			return a.sum < b.sum;
		else if(a.r != b.r)
			return a.r < b.r;
		else
			return (a.r - a.l) < (b.r - b.l);
	}

	sort(sb+1,sb+1+sz,cmp);
	int cnt = 0,lr = 0;
    //cnt统计贪心当前已经取的数量
    //lr记录贪心时上一个选择的块的右端点
	for(int i=1;i<=sz;++i){
		if(sb[i].sum == sb[i-1].sum){
			if(sb[i].l > lr){//当前块不与上一个块相交
				++cnt;
				lr = sb[i].r;
			}
		}
		else {
			if(cnt > acnt){
				acnt = cnt;//记录最多的块的个数
				asum = sb[i-1].sum;//记录最多的块的数值
			}
			cnt = 1;
			lr = sb[i].r;
		}
	}
	if(cnt > acnt){
		acnt = cnt;
		asum = sb[sz].sum;
	}
```
最后只需要输出就行

## AC代码
```cpp
	#include <bits/stdc++.h>
	using namespace std;
	typedef long long ll;
	#define pow(x) ((x)*(x))
	const int inf = 0x3f3f3f3f;
	ll rd(){register ll r=0,fh=1;register char c=getchar();while((c<'0'||c>'9')&&c!='-')c=getchar();if(c=='-')fh=-1,c=getchar();while(c>='0'&&c<='9')r=r*10+c-'0',c=getchar();return r*fh;}
	
	#define MAXN 1505
	
	struct blk{
		int l;
		int r;
		int sum;
		void input(int a,int b,int c)
        	{l = a;r = b;sum = c;}
	}sb[MAXN*MAXN];
	
	bool cmp(const blk &a,const blk &b){
		if(a.sum != b.sum)
			return a.sum < b.sum;
		else if(a.r != b.r)
			return a.r < b.r;
		else
			return (a.r - a.l) < (b.r - b.l);
	}
	
	int n;
	int a[MAXN],s[MAXN];
	int sz;
	int acnt,asum;
	int p;
	
	int main()
	{
		n = rd();
		for(int i=1;i<=n;++i)
		{
			a[i] = rd();
			s[i] = s[i-1] + a[i];
		}
		
		for(int i=1;i<=n;++i)
			for(int j=1;j<=n-i+1;++j)
				sb[++sz].input(j,i+j-1,s[j+i-1]-s[j-1]);
		sort(sb+1,sb+1+sz,cmp);
		int cnt = 0,lr = 0;
		for(int i=1;i<=sz;++i){
			if(sb[i].sum == sb[i-1].sum){
				if(sb[i].l > lr){
					++cnt;
					lr = sb[i].r;
				}
			}
			else {
				if(cnt > acnt){
					acnt = cnt;
					asum = sb[i-1].sum;
				}
				cnt = 1;
				lr = sb[i].r;
			}
		}
		if(cnt > acnt){
			acnt = cnt;
			asum = sb[sz].sum;
		}	
		
		printf("%d\n",acnt);
		for(int i=1;i<=sz;++i)
			if(sb[i].sum == asum){p = i;break;}
		printf("%d %d\n",sb[p].l,sb[p].r);
		lr = sb[p].r;
		++p;
		while(sb[p].sum == asum && p <= sz){
			if(sb[p].l > lr){
				printf("%d %d\n",sb[p].l,sb[p].r);
				lr = sb[p].r;	
			}
			++p;
		}
		return 0;
	}
```

---

## 作者：heyx0201 (赞：0)

# 题意
给出一个数列，求一个最大值 $k$，使得在原序列中找到 $k$ 个不相交的子段，且这些子段的和相等。
# 思路
考虑到 $n$ 实在是有点小，题目要求的是 $k$ 个不相交的和相等的子段，可以对于每个子段和存储对应的子段左右端点，然后贪心的对每个子段和选择最多子段，再取最大值，贪心策略与[此题](https://www.luogu.com.cn/problem/P1803)类似。

考虑到 $n \times \sum \limits_{i = 1}^n a_i$ 实在是有点大，所以要使用 `map` 来存储。
# 代码
```cpp
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 15e2 + 10;

#define pii pair<int, int>

int n, a[MAXN], s[MAXN];
map<int, vector<pii>> mp;
vector<pii> ans;

bool cmp(const pii &i, const pii &j) {
  return i.second < j.second;
}

int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    s[i] = s[i - 1] + a[i];
  }
  for (int i = 1; i <= n; i++) {
    for (int j = i; j <= n; j++) {
      mp[s[j] - s[i - 1]].push_back({i, j});
    }
  }
  int k = 0;
  for (auto it : mp) {
    sort(it.second.begin(), it.second.end(), cmp);
    vector<pii> v;
    for (pii x : it.second) {
      if (v.empty() || x.first > v.back().second) {
        v.push_back(x);
      }
    }
    if (v.size() > k) {
      k = v.size();
      ans = v;
    }
  }
  cout << k << '\n';
  for (pii x : ans) {
    cout << x.first << ' ' << x.second << '\n';
  }
  return 0;
}
```

---

## 作者：__LZH__ (赞：0)

# CF1141F2 Same Sum Blocks (Hard)

## 题意

[题面传送门](https://www.luogu.com.cn/problem/CF1141F2)。

## 思路

首先，要找合为 $k$ 的段，可以直接枚举段然后用 `map<int, vector<pair<int, int>>>` 来存段（存的每个段都不相交），然后选选了最多段的即可。

## 时空复杂度

时间：枚举 + `map` $O(n ^ 2 \log n)$。

空间：$O(n ^ 2)$。

## 代码：

```cpp
#include<bits/stdc++.h>

#define int long long

using namespace std;

using vpi = vector<pair<int, int>>;

int n, a[55];
map<int, vpi> mp;

signed main(){
  cin >> n;
  for(int i = 1; i <= n; i++){
    cin >> a[i];
  }
  vpi ans;
  for(int i = 1; i <= n; i++){
    int sum = 0;
    for(int j = i; j >= 1; j--){//必须倒着枚举右端点才能保证正确性
      sum += a[j];
      if(mp[sum].empty() || j > mp[sum].back().second){
        mp[sum].push_back({j, i});
      }
      if(mp[sum].size() > ans.size()){
        ans = mp[sum];
      }
    }
  }
  cout << ans.size() << '\n';
  for(auto i : ans){
    cout << i.first << ' ' << i.second << '\n';
  }
  return 0;
}

```

---

## 作者：Vitamin_B (赞：0)

# 思路
首先我们可以利用前缀和暴力算出所有 $a_i\sim a_j$ 的和，把相同的的数存进同一个 vector（因为这个和可能比较大而且可能是负数，所以可以用 map 套 vector）。枚举每个**可能的**总和，然后贪心取个不相交的线段即可。

如何贪心取不相交的线段？首先可以按右端点排序，然后依次枚举每条线段，若左端点比之前取到的右端点大，那就选上。最后以能取条数最多的那个方案就行。
# 代码
```cpp
# include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair <int, int> pii;
int n, a[1505], maxr;
vector <pii> now, ans;
map <int, vector <pii>> v;
bool cmp (const pii& x, const pii& y) {
	return x.second < y.second;
}
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> n;
	for (int i = 1; i <= n; ++ i) {
		cin >> a[i];
		a[i] += a[i - 1];
		for (int j = 1; j <= i; ++ j)
			v[a[i] - a[j - 1]].emplace_back (j, i);
	}
	for (map <int, vector <pii>> :: iterator i = v.begin (); i != v.end (); ++ i) {
		now.clear ();
		sort (i->second.begin (), i->second.end (), cmp);
		maxr = 0;
		for (pii& j : i->second)
			if (j.first > maxr)
				maxr = j.second, now.emplace_back (j);
		if (now.size () > ans.size ())
			ans = now;
	}
	cout << ans.size () << '\n';
	for (pii i : ans)
		cout << i.first << ' ' << i.second << '\n';
	return 0;
}
```

---

