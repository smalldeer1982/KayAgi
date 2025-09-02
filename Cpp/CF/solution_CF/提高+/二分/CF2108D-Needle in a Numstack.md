# Needle in a Numstack

## 题目描述

这是一个交互式问题。

你在阁楼中发现了数字 $k$ 和 $n$，但丢失了两个数组 $A$ 和 $B$。

你记得以下信息：
- $|A| + |B| = n$，即两个数组的总长度为 $n$。
- $|A| \geq k$ 且 $|B| \geq k$，即每个数组的长度至少为 $k$。
- 数组中的元素只包含 $1$ 到 $k$ 的数字。
- 如果从数组 $A$ 中任取 $k$ 个连续元素，它们都互不相同。同样，如果从数组 $B$ 中任取 $k$ 个连续元素，它们也互不相同。

幸运的是，阁楼里的一个善良精灵找到了这两个数组，并将它们连接成一个长度为 $n$ 的数组 $C$。也就是说，数组 $C$ 的前半部分是 $A$ 的元素，后半部分是 $B$ 的元素。

你可以向精灵最多提出 $250$ 次询问。每次询问提供一个索引 $i$（$1 \leq i \leq n$），精灵会返回数组 $C$ 的第 $i$ 个元素。

你的任务是确定数组 $A$ 和 $B$ 的长度，或者报告无法唯一确定它们的长度。

## 说明/提示

考虑第一个例子。我们查询了数组 $C$ 的前 $3$ 个元素（共 $5$ 个）。现在我们知道了数组 $C$ 的前三个元素为 $[1, 2, 2, ?, ?]$。根据条件，数组 $A$ 中的任意 $k$（$k=2$）个连续元素必须互不相同，因此第三个元素 $2$ 不可能属于数组 $A$，它必定属于数组 $B$。由此可以确定数组 $A$ 的长度为 $2$，数组 $B$ 的长度为 $3$。

图中展示了所有测试用例的数组。被查询的元素用黄色标记。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2108D/3a898b9f4f0ed20651c865ecf957d0078f46a581.png)

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
6
5 2

1

2

2

18 4

2

4

1

1

4

3 1

10 5

9 3

3

3

2

12 4

1

3

1

3

1

3```

### 输出

```
? 1

? 2

? 3

! 2 3

? 9

? 13

? 10

? 14

? 6

! 9 9

! -1

! 5 5

? 3

? 6

? 9

! 6 3

? 1

? 2

? 5

? 6

? 9

? 10

! -1```

# 题解

## 作者：yyrwlj (赞：2)

因为在数组 $A$ 和 $B$ 中取出任意连续 $k$ 个数都不重复，并且取值为 $1$ 到 $k$，所以知道一个数组中的连续 $k$ 个数后就能知道这个数组中的其它数，且值相同当且仅当下标在模 $k$ 意义下相同。

因为两个数组的长度都至少为 $k$，所以前 $k$ 个数肯定属于数组 $A$，最后 $k$ 个数肯定属于数组 $B$，我们花费 $2k$ 次询问就可以得出每个位置的两种情况的取值。

容易发现如果一个数最后出现的位置和第一次出现的位置模 $k$ 意义下相同，那么这个数在整个数组 $C$ 里面的出现位置都模 $k$ 同余，即不能作为分割 $A$ 和 $B$ 的凭证。

那么我们要找到一个最后出现的位置和第一次出现的位置模 $k$ 意义下不同的数，然后花费 $\log\frac{n}{k}$ 次询问用二分找到它第一个与第一次出现的位置模 $k$ 意义下相同的且不是这个数的位置，分割线肯定在这个位置之前，且在上一个出现位置之后，即这个位置往后肯定都属于数组 $B$，上一个出现位置往前肯定都属于数组 $A$。

设这个位置的数为 $x$，根据限制，它在数组 $B$ 最多是第 $k$ 个数，且这个数的上一个出现位置最少是第 $|A|-k+1$ 个数，即它们的距离不会超过 $2k$，我们往前问 $2k$ 个数即可得出它的上一个数的出现位置。

这个时候我们已经知道了整个数组的内容，并且把分割线的取值控制在了 $2k$ 种，枚举所有取值然后再 $O(k^2)$ 判定即可。

总询问次数 $4k + \log\frac{n}{k}$ 次，时间复杂度 $O(T(k^3 + \log\frac{n}{k}))$。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef pair<int, int> PII;
typedef pair<LL, LL> PLL;
const int N = 1000005;
const int mod = 1e9+7;
const int inf = 0x3f3f3f3f;
const LL INF = 2e18;
int a[N], b1[55], b2[55], n, k, last, pos;
int st[55];
bool check(int p)
{
	cout << "? " << p << endl;
	int x;
	cin >> x;
	return x != b1[p % k];
}
bool chk(int l,int r)
{
	for (int i=1;i<=k;i++)
		st[i] = 0;
	for (int i=l;i<=r;i++)
		if (i < last)
			st[b1[i % k]] ++;
		else if (i > pos)
			st[b2[i % k]] ++;
		else
			st[a[i]] ++;
	for (int i=1;i<=k;i++)
		if (st[i] > 1)
			return false;
	return true;
}
void work()
{
	cin>>n>>k;
	if (n==k*2)
	{
		cout<<"! "<<k<<' '<<k<<endl;
		return;
	}
	if (k==1)
	{
		cout << "! -1" << endl;
		return;
	}
	for (int i=1;i<=k;i++)
	{
		cout << "? " << i << endl;
		cin >> b1[i % k];
		a[i] = b1[i % k];
	}
	int num, cnt1 = 0;
	for (int i=k,j=n;i;i--)
	{
		j = i + (n / k - 1) * k;
		while (j > n)
			j -= k;
		while (j + k <= n)
			j += k;
		cout << "? " << j << endl;
		cin >> b2[j % k];
		if (b1[i % k] != b2[j % k])
			num = i, cnt1 ++;
	}
	if (cnt1 <= 1)
	{
		cout << "! -1" << endl;
		return;
	}
	int l = 1, r = n / k - 1;
	pos = -1;
	while (num + r * k > n)
		r --;
	while (num + r * k + k <= n)
		r ++;
	while (l <= r)
	{
		int mid = (l + r) >> 1;
		int p = num + mid * k;
		if (p > n)
			p -= k;
		if (check(p))
			pos = p, r = mid - 1;
		else
			l = mid + 1;
	}
	for (int i=max(k+1,pos-k*2);i<=pos;i++)
	{
		cout << "? " << i << endl;
		cin >> a[i];
	}
	last = -1;
	for (int i=pos-1;i;i--)
		if (a[i] == a[pos])
		{
			last = i;
			break;
		}
	int ans = 0, cnt = 0;
	for (int i=last;i<pos;i++)
	{
		// [1, i] and [i + 1, n]
		if (i < k || n - i < k)
			continue;
		bool flag = true;
		for (int j=i+1;j<=pos;j++)
			flag &= chk(j, min(j + k - 1, n));
		for (int j=max(1,i-2*k);j<=i;j++)
			flag &= chk(j, min(j + k - 1, i));
		if (flag)
		{
			ans = i;
			cnt ++;
		}
	}
	if (cnt > 1)
		cout << "! -1" << endl;
	else
		cout << "! " << ans << ' ' << n - ans << endl;
}
signed main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int _T = 1;
    cin >> _T;
    while (_T--)
    	work();
    return 0;
}
```

---

## 作者：Unnamed114514 (赞：1)

给个 $2k+\log n$ 的做法，而且比较自然。

如果 $n=2k$ 直接返回 `k k`，免谈。

注意到显然有 $a_{i}=a_{i-k}$，因此我们先通过 $2k$ 次询问得到 $a,b$。

同时，我们为了分辨 $a,b$，显然需要把 $a,b$ 不同的位置搞出来，记作 $p$。

如果 $|p|=0$，那么显然无法分辨；否则我们二分找到属于 $a$ 的最后一个 $p$，然后只需要看它和下一个 $p$ 是否相邻即可，注意边界的判断。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
int T,n,k,a[N],b[N];
vector<int> p;
void solve(){
	if(n==2*k){
		cout<<'!'<<' '<<k<<' '<<k<<endl;
		return;
	}
	if(p.empty()){
		cout<<'!'<<' '<<-1<<endl;
		return;
	}
	int l=0,r=p.size()-1,res;
	cout<<'?'<<' '<<p[0]<<endl;
	cin>>res;
	if(res==b[p[0]]){
		if(p[0]==k+1) cout<<'!'<<' '<<k<<' '<<n-k<<endl;
		else cout<<'!'<<' '<<-1<<endl;
		return;
	}
	while(l<r){
		int mid=l+r+1>>1;
		cout<<'?'<<' '<<p[mid]<<endl;
		cin>>res;
		if(res==a[p[mid]]) l=mid;
		else r=mid-1;
	}
	if(r==p.size()-1){
		if(p[r]==n-k) cout<<'!'<<' '<<n-k<<' '<<k<<endl;
		else cout<<'!'<<' '<<-1<<endl;
		return;
	}
	if(p[r]+1==p[r+1]) cout<<'!'<<' '<<p[r]<<' '<<n-p[r]<<endl;
	else cout<<'!'<<' '<<-1<<endl;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n>>k;
		for(int i=1;i<=k;++i) cout<<'?'<<' '<<i<<endl,cin>>a[i];
		for(int i=n-k+1;i<=n;++i) cout<<'?'<<' '<<i<<endl,cin>>b[i];
		for(int i=k+1;i<=n;++i) a[i]=a[i-k];
		for(int i=n-k;i;--i) b[i]=b[i+k];
		p.clear(),p.shrink_to_fit();
		for(int i=k+1;i<=n-k;++i) if(a[i]!=b[i]) p.emplace_back(i);
		solve();
	}
	return 0;
}
```

---

## 作者：aeiouaoeiu (赞：1)

观察 $A,B$ 的形式，可以发现必然存在长度为 $k$ 的循环节，通过询问 $C$ 的前后 $k$ 个元素可以分别得到这些循环节，操作次数为 $2k$。

可以发现寻找 $A,B$ 分界点，实际上就是寻找一个点使得这个点及其左边只能用 $A$ 循环节描述，右边只能用 $B$ 循环节描述。

将 $B$ 循环节摆正，也就是得到数组 $b$ 使得 $C$ 中下标为 $i$ 且属于 $B$ 的值为 $b_{i\bmod k}$，$A$ 同理。设 $v_i=[a_{i}=b_{i}]$，那么这个分界点 $c$ 除了位于 $k,n-k$ 这两种特殊情况外，其必然满足 $v_c=v_{(c+1)\bmod k}=1$，否则会有多种划分情况。

将这些可能的分界点抽离出来，显然这些点要么就是分界点，要么只位于 $A,B$ 中一个，满足单调性。于是可以二分分界点，操作次数在 $2\log n$ 左右。也可以使用倍增。

特判掉 $n=2k$ 的情况，对于剩下的情况，如果 $C$ 可以使用 $A$ 的循环节描述（也就是 $B$ 的循环节摆正后和 $A$ 相同），显然会有多种解。

总操作次数在 $2k+2\log n$ 左右，完全可以接受。

```cpp
#include<bits/stdc++.h>
#define pb emplace_back
#define mp make_pair 
#define pob pop_back
using namespace std;
typedef long long ll;
typedef double db;
const ll maxn=200007,ee=1e18,p=998244353;
ll n,k,m,a[maxn],b[maxn],c[maxn],vis[maxn],C[maxn],ansg;
vector<ll> vec;
void ask(ll x,ll &RR){
	cout<<"? "<<x<<endl;
	cin>>RR;
}
int main(void){
	//freopen("data.in","r",stdin); 
	//freopen("data.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0);
	ll T=1; cin>>T;
	for(;T--;){
		cin>>n>>k;
		if(n==2*k){
			cout<<"! "<<k<<" "<<k<<endl;
			continue;
		}
		for(int i=1;i<=k;i++){
			if(i!=k) ask(i,a[i]);
			else ask(i,a[0]);
		}
		for(int i=1;i<=k;i++){
			ask(n-k+i,b[i]);
			c[(n-k+i)%k]=b[i];
		}
		vec.clear();
		for(int i=0;i<k;i++) vis[i]=0;
		ll cnt=0,r1,r2,cur=-1;
		for(int i=0;i<k;i++)if(a[i]!=c[i]) vis[i]=1,cnt++;
		for(int i=0;i<k;i++)if(vis[i]==1&&vis[(i+1)%k]==1) vec.pb(i);
		m=vec.size();
		if(vis[1]==1){
			ask(k+1,r1);
			if(r1==c[1]){cout<<"! "<<k<<" "<<n-k<<endl; continue;}
		}
		if(vis[(n-k)%k]==1){
			ask(n-k,r1);
			if(r1==a[(n-k)%k]){cout<<"! "<<n-k<<" "<<k<<endl; continue;}
		}
		if(cnt==0||vec.empty()){cout<<"! -1"<<endl; continue;}
		for(ll i=20,x,id;i>=0;i--){
			x=cur+(1<<i);
			id=((x/m)+1)*k+vec[x%m];
			if(id<n-k){
				ask(id,r1),ask(id+1,r2);
				if(r1==a[id%k]&&r2==a[(id+1)%k]) cur=x;
			}
		}
		cur=((cur+1)/m+1)*k+vec[(cur+1)%m];
		if(cur>=n-k){cout<<"! -1"<<endl; continue;}
		ask(cur,r1),ask(cur+1,r2);
		if(r1!=a[cur%k]||r2!=c[(cur+1)%k]){cout<<"! -1"<<endl; continue;}
		cout<<"! "<<cur<<" "<<n-cur<<endl;
	}
	return 0;
}
```

---

## 作者：Hell0_W0rld (赞：1)

注意到根据题目限制，$A,B$ 数组都有一个长度为 $k$ 的循环节，且每个循环节中的数互不相同。

那我们可以先询问数组 $C$ 的前 $k$ 位和后 $k$ 位，这样我们可以得到 $A,B$ 的循环节，记为 $S,T$。若 $S=T$，则无法判断。

考虑找到 $S$ 和 $T$ 不一样的一位（记为 $j$），对这个进行二分，可以找到：$x\times k+j$ 是 $A$ 中的一位，$(x+1)\times k+j$ 是 $B$ 中的一位。再对这个区间内的每个数查询，可以得到前一部分属于 $A$，后一部分属于 $B$。

如果这两个部分并起来恰好等于原区间，结束。否则 $-1$。

总查询数 $3k+\log_2(\frac{n}{k})$。

[赛时提交](https://codeforces.com/contest/2108/submission/317996633)

---

