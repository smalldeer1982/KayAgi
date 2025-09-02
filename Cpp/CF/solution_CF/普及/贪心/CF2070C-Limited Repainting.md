# Limited Repainting

## 题目描述

给定一个由 $n$ 个单元格组成的条带，所有单元格初始均为红色。

在一次操作中，你可以选择一个连续的单元格段并将其涂成蓝色。涂色前，所选单元格可以是红色或蓝色（注意不能将其涂成红色）。你最多可以进行 $k$ 次操作（可以是零次）。

对于每个单元格，指定了所有操作完成后期望的颜色：红色或蓝色。

显然，有时无法在 $k$ 次操作内满足所有要求。因此，对于每个单元格，还指定了一个惩罚值，当该单元格在所有操作后呈现错误颜色时应用此惩罚。对于第 $i$ 个单元格，其惩罚值为 $a_i$。

最终涂色的总惩罚值定义为所有错误颜色单元格的惩罚值的最大值。如果没有错误颜色的单元格，总惩罚值为 $0$。

求可以达到的最小总惩罚值是多少？

## 说明/提示

第一个测试用例中，你可以将 $1$ 到 $3$ 号的单元格涂色。最终涂色为 BBBR。只有第 $2$ 号单元格颜色错误，因此总惩罚值为 $3$。

第二个测试用例中，若涂色为 BBBR 则总惩罚值为 $5$。但如果仅涂色 $1$ 号单元格得到 BRRR，则只有第 $3$ 号单元格颜色错误，总惩罚值为 $3$。

第三个测试用例中，可以分别涂色 $1$ 号单元格和 $3$ 号单元格。所有单元格颜色均正确，总惩罚值为 $0$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
5
4 1
BRBR
9 3 5 4
4 1
BRBR
9 5 3 4
4 2
BRBR
9 3 5 4
10 2
BRBRBBRRBR
5 1 2 4 5 3 6 1 5 4
5 5
RRRRR
5 3 1 2 4```

### 输出

```
3
3
0
4
0```

# 题解

## 作者：zzldd (赞：6)

求最大值的最小值，常见的二分答案题。\
进行 $check$ 时，我们使用 $lst$ 记录上一个 $a_i>x$ 的 $s_i$，初始值为 $R$。对 $a$ 进行遍历，如果 $a_i \le x$，可以直接忽略，当 $a_i>x$ 时，如果 $s_i$ 为 $B$ 且 $lst\ne s_i$，则需要进行一次涂色，使用 $cnt$ 记录。之后将 $lst$ 值更新为 $s_i$。最后 $cnt$ 的值即为答案为 $x$ 时所需的最少涂色次数。\
使用 $ans$ 记录答案，二分结束后，输出 $ans$。
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int T,n,k,a[300005];
bool check(int x){
	int cnt=0;char lst='R';
	for(int i=0;i<n;i++){
		if(a[i]>x){
			if(s[i]=='B'&&lst!=s[i]) cnt++;
			lst=s[i];
		}
	}return cnt<=k;
}
int main(){
	cin>>T;
	while(T--){
		cin>>n>>k>>s;int l=0,r=0,mid,ans;
		for(int i=0;i<n;i++){
			cin>>a[i];
			r=max(r,a[i]);
		}
		while(l<=r){
			mid=(l+r)/2;
			if(check(mid)) r=mid-1,ans=mid;
			else l=mid+1;
		}cout<<ans<<"\n";
	}
	
}
```

---

## 作者：shiyilang0910 (赞：1)

## 思路
本题要使用二分和贪心通过此题。我们可以先二分总惩罚值，再去一遍一遍去找，如果遇到小于等于惩罚值的元素，可以跳过它，因为如果它涂错了也没有关系。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t,n,k,a[300005];
string s;
bool check(int x){//判断是否可行
	string s1="";
	for(int i=0;i<n;i++){
		if (a[i+1]<=x){
			s1+='3';
		}else if (s[i]=='R'){
			s1+='2';
		}else{
			s1+='1';
		}
	}
	int l=0,ans=0;
	while(l<n&&(s1[l]=='2'||s1[l]=='3')){
		l++;
	}
	for(;l<n;){
		while(l<n&&(s1[l]=='1'||s1[l]=='3')){
			l++;
		}
		while(l<n&&(s1[l]=='2'||s1[l]=='3')){
			l++;
		}
		ans++;
	}
	return ans<=k;
}
signed main(){
	cin>>t;
	while(t--){
		cin>>n>>k;
		cin>>s;
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
        //二分
		int l=0,r=1e9,res=0;
		while(l<=r){
			int mid=(l+r)/2;
			if (check(mid)){//如果可以
				res=mid;//记录答案
				r=mid-1;
			}else{
				l=mid+1;
			}
		}
		cout<<res<<endl;//输出
	}
	return 0;//表示完美结束
}
```

---

## 作者：e_mei_mountain_704 (赞：0)

#### 思路
 本题是一道二分加贪心题。我们可以先二分算总惩罚值，再慢慢一遍一遍去找，如果遇到小于等于惩罚值的量，可以跳过它，因为如果它涂错了也没啥关系。
#### 代码实现

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int N=300036;
int t,n,k,ar[N];
string s;

bool check (int x)
{
	string s1="";
	for (int i=0; i<n; i++)
	{
		if (ar[i+1]<=x)
			s1+='3';
		else if (s[i]=='R')
			s1+='2';
		else
			s1+='1';
	}
	int l=0,ans=0;
	while (l<n && (s1[l]=='2' || s1[l]=='3'))
		l++;
	for ( ; l<n; )
	{
		while (l<n && (s1[l]=='1' || s1[l]=='3'))
			l++;
		while (l<n && (s1[l]=='2' || s1[l]=='3'))
			l++;
		ans++;
	}
	return ans <= k;
}

signed main ()
{
	cin>>t;
	while (t--)
	{
		cin>>n>>k;
		cin>>s;
		for(int i=1; i<=n; i++)
			cin>>ar[i];
		int l=0,r=1e9,res=0;
		while (l<=r)
		{
			int mid=(l+r)/2;
			if (check(mid))
			{
				res=mid;
				r=mid-1;
			}
			else l=mid+1;
		}
		cout<<res<<endl;
	}
	return 0;
}
```

---

## 作者：The_foolishest_OIer (赞：0)

省流：赛时读错题目被卡半小时。

经典二分答案。

二分惩罚值，然后标记不能删除的点和必须删除的点，如果段数 $\le k$ 就是合法的。


```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
const int N = 3e5 + 10;
const int inf = 1e16;
const int mod = 1e9 + 7;
int T,n,k;
string s;
int a[N],vis[N];
void close(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
}
bool P (int x){
	for (int i = 1 ; i <= n ; i++) vis[i] = 0;
	for (int i = 1 ; i <= n ; i++){
		if (a[i] > x){
			if (s[i] == 'R') vis[i] = -1; // 不能删除
			else vis[i] = 1; // 必须删除
		}
	}
	int cnt = 0;
	bool is_run = 0; // 是否存在需要删除的
	for (int i = 1 ; i <= n ; i++){
		if (vis[i] == 1){
			if (is_run) continue; // 如果这一段要删除，那么直接删除
			cnt++; // 否则新开一段
			is_run = 1;
		}else if (vis[i] == -1){ // 遇到不能删除的点
			if (is_run) is_run = 0; // 这一段停止
		}
	}
	return (cnt <= k); 
}
void solve(){
	cin >> n >> k;
	cin >> s;
	s = " " + s;
	for (int i = 1 ; i <= n ; i++) cin >> a[i];
	int mx = 0;
	for (int i = 1 ; i <= n ; i++) mx = max(mx,a[i]);
	int L = 0,R = mx,ans = mx; // 二分答案
	while (L <= R){
		int mid = (L + R) >> 1;
		if (P(mid)){
			ans = mid;
			R = mid - 1;
		}else{
			L = mid + 1;
		}
	}
	cout << ans << endl;
}
signed main(){
	close();
	T = 1;
	cin >> T;    
	while (T--) solve();
	return 0;
}
```

---

## 作者：lw393 (赞：0)

看见最大值最小，想到二分。然后题目中限制蓝色段的数量不能超过 $k$ 段，这个就当作 check 判断的条件。

然后就没了？

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 5e5 + 5;
 
int a[N];
 
void solve(){
    int n, m;
    cin >> n >> m;
    string s;
    cin >> s;
    s = ' ' + s;
    for(int i = 1; i <= n; i++) cin >> a[i];
    int l = 0, r = 1e9, ans = r + 1;
    while(l <= r){
        int mid = (l + r) >> 1;
        int t = 0, w = 0;
        for(int i = 1; i <= n; i++){
            if(a[i] > mid) {
                if(s[i] == 'B') { if(w == 0) w = 1, ++t; }
                else w = 0;
            }
        }
        if(t <= m) ans = mid, r = mid - 1;
        else l = mid + 1;
    }
    cout << ans << '\n';
}
 
signed main(){
    int t;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}
```
时间复杂度 $O(n\log (\max_{i=1}^n a_i))$

为什么赛时没过呢？这下子不得不批判一下 cf better 的翻译了，把最小最大值翻译成了最小总惩罚值。。。

---

## 作者：AstaVenti_ (赞：0)

# $\mathbf{0x00}$ 启

蒟蒻的第 $\color{red}\mathbf{47}$ 篇题解。

# $\mathbf{0x01}$ 承

你可以用之多 $k$ 次给一条红色带子的某个区间涂成蓝色，求涂错的格子的代价 $\Sigma a_i$ 的最小值。

# $\mathbf{0x02}$ 转

考虑二分。若某个单元格的惩罚必须不超过 $m$，则所有 $a[i]>m$ 的单元格必须正确着色，否则会导致总惩罚超过 $m$。

因此我们可以钦定一个 $m$，检查是否能在 $k$ 次操作内满足所有 $a[i]>m$ 的单元格正确着色。具体地，目标为蓝色且 $a[i] > m$ 的格子必须被覆盖，目标为红色且 $a[i] > m$：必须保持不覆盖。

我们可以将那些必须保持红色的单元格将整个数组分割为多个区间，每个区间内的必须涂蓝的单元格需用最少操作覆盖。这里可以用双指针法优化。

每个分割后的区间只需一次操作即可覆盖所有必须涂蓝的单元格，因此只需统计所有需操作的区间数是否不超过 $k$ 即可。

时间复杂度 $\Theta(n\log\max(a))$。

# $\mathbf{0x03}$ 合


```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN=3e5+5;
ll T,n,k,a[300005];
string s;
bool check(ll m) {
	vector<int>b,g(n+1,0);
  // b 是须保留红色的位置，g是前缀和，前缀和，记录必须涂蓝的单元格数量
	for(int i=1; i<=n; i++) {
		g[i]=g[i-1]+((s[i-1]=='B')&&(a[i]>m));
		if(s[i-1]=='R'&&a[i]>m)b.push_back(i);
	}
	sort(b.begin(),b.end());
	int req=0,lst=0;// 需要的操作数 和 上一个分割点
	for(int i:b) {
		int l=lst+1,r=i-1;
		if(l<=r&&g[r]-g[l-1]>0)req++;
		lst=i;
	}
  // 特判一下最后一个区间
	int l=lst+1,r=n;
	if(l<=r&&g[r]-g[l-1]>0)req++;
	return req<=k;
}

int main() {
	cin>>T;
	while(T--) {
		cin>>n>>k>>s;
		vector<ll>a2;
		for(int i=1; i<=n; i++) {
			cin>>a[i];
			a2.push_back(a[i]);
		}
		sort(a2.begin(),a2.end(),greater<ll>());
		ll l=0,r=a2.empty()?0:a2[0],ans=r;
		while(l<=r) {
			ll m=(l+r)>>1;
			if(check(m))ans=m,r=m-1;
			else l=m+1;
		}
		cout<<ans<<"\n";
	}
}

```

---

