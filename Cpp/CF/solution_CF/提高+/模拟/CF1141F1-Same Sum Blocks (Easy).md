# Same Sum Blocks (Easy)

## 题目描述

本题有两个版本，区别仅在于 $n$ 的取值范围。

给定一个整数数组 $a[1], a[2], \dots, a[n]$。一个“块”是指一段连续的元素 $a[l], a[l+1], \dots, a[r]$（$1 \le l \le r \le n$）。因此，一个块由一对下标 $(l, r)$ 唯一确定。

请你找出若干个块 $(l_1, r_1), (l_2, r_2), \dots, (l_k, r_k)$，使得：

- 这些块互不相交（即两两不重叠）。形式化地说，对于任意两个块 $(l_i, r_i)$ 和 $(l_j, r_j)$，若 $i \neq j$，则要么 $r_i < l_j$，要么 $r_j < l_i$。

- 每个块内所有元素的和都相等。形式化地说，
$$
a[l_{1}] + a[l_{1} + 1] + \dots + a[r_{1}] = a[l_{2}] + a[l_{2} + 1] + \dots + a[r_{2}] = \dots = a[l_{k}] + a[l_{k} + 1] + \dots + a[r_{k}]
$$

- 块的数量 $k$ 尽可能大。形式化地说，不存在另一组满足上述两个条件的块 $(l_1', r_1'), (l_2', r_2'), \dots, (l_{k'}', r_{k'}')$，使得 $k' > k$。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1141F2/a32038d691a8fef036434bed64856f1bff592dde.png)
上图对应第一个样例，蓝色框表示块。请编写程序，找出这样一组块。

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

## 作者：初雪_matt (赞：1)

$n$ 太小，可以预处理出所有区间的和，也可以存下所有区间和相等的区间们，所以你可以枚举和，然后转换成了线段覆盖。

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

## 作者：__LZH__ (赞：0)

# CF1141F1 Same Sum Blocks (Easy)

## 题意

[题面传送门](https://www.luogu.com.cn/problem/CF1141F1)。

## 思路

此题与加强版都挺简单，于是直接讲加强版解法。

首先，要找和为 $k$ 的段，可以直接枚举段然后用 `map<int, vector<pair<int, int>>>` 来存段（存的每个段都不相交），然后选选了最多段的即可。

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

## 作者：sgl654321 (赞：0)

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
int n, a[55], maxr;
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

