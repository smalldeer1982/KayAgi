# [ABC200D] Happy Birthday! 2

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc200/tasks/abc200_d

$ N $ 個の正整数からなる数列 $ A\ =\ (A_1,\ A_2,\ \dots,\ A_N) $ が与えられます。 以下の条件を全て満たす $ 2 $ つの数列 $ B\ =\ (B_1,\ B_2,\ \dots,\ B_x),\ C\ =\ (C_1,\ C_2,\ \dots,\ C_y) $ が存在するか判定し、存在する場合はひとつ出力してください。

- $ 1\ <\ = x,\ y\ <\ =\ N $
- $ 1\ \le\ B_1\ <\ B_2\ <\ \dots\ <\ B_{x}\ \le\ N $
- $ 1\ \le\ C_1\ <\ C_2\ <\ \dots\ <\ C_{y}\ \le\ N $
- $ B $ と $ C $ は、異なる数列である。
  - $ x\ ≠\ y $ のとき、または、ある整数 $ i\ (1\ <\ = i\ <\ = \min(x,\ y)) $ が存在して $ B_i\ ≠\ C_i $ であるとき、$ B $ と $ C $ は異なるものとする。
- $ A_{B_1}\ +\ A_{B_2}\ +\ \dots\ +\ A_{B_x} $ を $ 200 $ で割った余りと $ A_{C_1}\ +\ A_{C_2}\ +\ \dots\ +\ A_{C_y} $ を $ 200 $ で割った余りが等しい。

## 说明/提示

### 制約

- 入力はすべて整数
- $ 2\ \le\ N\ \le\ 200 $
- $ 1\ \le\ A_i\ \le\ 10^9 $

### Sample Explanation 1

$ B=(1),C=(3,4) $ とすると、$ A_1\ =\ 180,\ A_3\ +\ A_4\ =\ 380 $ となり、この $ 2 $ つを $ 200 $ で割った余りは等しくなります。 他にも、以下のような出力も正答として扱われます。 ``` yEs 4 2 3 4 5 3 1 2 5 ```

### Sample Explanation 3

条件を満たす数列の組が存在しない場合、$ 1 $ 行に `No` と出力してください。

## 样例 #1

### 输入

```
5
180 186 189 191 218```

### 输出

```
Yes
1 1
2 3 4```

## 样例 #2

### 输入

```
2
123 523```

### 输出

```
Yes
1 1
1 2```

## 样例 #3

### 输入

```
6
2013 1012 2765 2021 508 6971```

### 输出

```
No```

# 题解

## 作者：loser_seele (赞：8)

有一个人类智慧的结论：在 $ 201 $ 个序列中必定有两个对 $ 200 $ 取模的余数相同，这个用抽屉原理显然可以证明。

具体证明：假设前 $ 200 $ 个序列两两余数不同，则第 $ 201 $ 个一定与之前的某个序列余数相同。

于是观察到 $ n \leq 8 $ 的时候可以构造出 $ 256 $ 个集合，考虑对于 $ n \leq 8 $ 的情况暴力枚举所有可能的集合判断是否有解，$ n \geq 9 $ 的情况由上述情况可知必然有解，于是可以同 $ n \leq 8 $ 的办法处理即可。

时间复杂度 $ \mathcal{O}(\bmod) $，其中 $ \bmod=200 $，可以通过。

代码：

```cpp
#import <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
int w[N];
unordered_map<int,vector<int>>md;
void print(vector<int>d)
{
cout<<d.size()<<' ';
for(auto x:d)
cout<<x<<' ';
cout<<'\n';
}
main()
{
    int n;
    cin>>n;
    int mins=min(n, 8);
    for(int i=0;i<n;i++)
    cin>>w[i];
    for(int i=1;i<(1<<mins);i++)
    {
    	int sum=0;
        vector<int>tmp;
    	for(int j=0;j<mins;j++)
    	if(i>>j&1) 
    	sum=(sum+w[j])%200,tmp.push_back(j+1);
    	if(md[sum].size())
    	{
    		cout<<"Yes"<<endl;
    		print(tmp);
            print(md[sum]);
            return 0;
    	}
    	else 
    	md[sum]=tmp;
    }
    cout<<"No";
}
```


---

## 作者：xianxi (赞：2)

# 经历

学校拿来当考试题，第一眼看到这题，觉得是数学结论题，想了一会公式，结果脑子烧了，决定打个暴搜。

事实上，我似乎打出了正解：数学结论加暴搜，只是没有结合。

# 简单题意

给你 $N$ 个数，要求选出两个序列，使两个序列和模 $200$ 同余，输出任意满足解即可。

# 思路

暴搜用一次搜索同时处理两个序列容易超时，且不易编码，所以，用一个搜索只搜一个序列，每一次记录序列模值，遇见重复的模值即可输出。

怎么证明此暴搜不超时呢？

我们可以这样理解：搜到一种解，我们会将它模 $200$ 的值记录到一个数组内。假设最坏情况下，前 $200$ 次搜索得到的序列值都不同，那么，第 $201$ 次搜索一定会有一个之前搜过的与当前序列不同的序列模 $200$ 值相同，即抽屉原理或鸽巢原理。也就是搜索只用搜至少 $201$ 次即可得出答案。

我用状态压缩处理搜索，学过状态压缩的，可知 $2$ 的 $8$ 次方等于 $256$ 大于 $201$，足以搜索出有解情况，当然，如果 $N$ 小于 $8$ 就要用 $N$ 去状压。

# 代码实现

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std; 
const int maxn=2005;
int n,m,a[maxn];
vector<int>v[maxn];
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;++i)cin>>a[i];
	n=min(n,(long long) 8);
	for(int i=1;i<=(1<<n);++i)
	{
		int p[maxn],len=0;
		int j=i,cnt=1,ans=0;
		while(j)
		{
			if(j&1)
			{
				ans+=a[cnt];
				p[++len]=cnt;
			}
			cnt++;
			j>>=1;
		}
		if(v[ans%200].size()!=0)
		{
			cout<<"Yes"<<"\n";
			cout<<len<<" ";
			for(int i=1;i<=len;++i)cout<<p[i]<<" ";
			cout<<"\n";
			cout<<v[ans%200].size()<<" ";
			for(int i=0;i<v[ans%200].size();++i)cout<<v[ans%200][i]<<" ";
			return 0;
		}
		else
		{
			for(int i=1;i<=len;++i)
			{
				v[ans%200].push_back(p[i]);
			}
		}
	}
	cout<<"No";
	return 0;
}
```

最后，感谢您的留步与观看。

---

## 作者：FreedomKing (赞：2)

[Atcoder Beginning Contest Virtual Participation 计划](https://www.luogu.com.cn/blog/FreedomKing/ABCVP)。

### 思路

注意到此题模数十分的小，仅仅只有 $200$，然后我们便可以考虑题目的一个性质：不管是对于 $A$ 序列还是 $C$ 序列，对于任何一个序列的元素和 $sum$，都有 $sum \bmod 200<200$。然后我们最多只需要枚举 $201$ 种不同的序列，其中必然会有两个序列的和在对 $200$ 取模的情况下相等。

对于序列的枚举，我们可以记一个 $i\le\min(8,n)$，这里取 $\min(8,n)$ 是因为 $2^8=256>200$。然后就可以通过 $i$ 的二进制位下的 $0,1$ 来决定选不选择当前位的元素了，可以证明对于 $i$ 不等于 $i_0$，$i$ 与 $i_0$ 的二进制形式必定不同。

### AC Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+5,xN=1e7+5,mN=1e4+5,mod=200;
namespace FreedomKing_qwq{};
using namespace FreedomKing_qwq;
namespace FreedomKing_qwq{
	inline int qread(){
#define qr qread()
		int x=0,c=getchar(),t=1;
		while(c<'0'||c>'9'){
			t^=(c=='-');
			c=getchar();
		}
		while(c>='0'&&c<='9'){
			x=(x<<3)+(x<<1)+c-'0';
			c=getchar();
		}
		return (t?x:-x);
	}
	inline void qwrite(int x){
#define qw(_) qwrite(_)
#define qws(_) qw(_),putchar(' ')
#define qwe(_) qw(_),putchar('\n')
		if(x<0) x=-x,putchar('-');
		if(x>9) qwrite(x/10);
		putchar(x%10+'0');
		return;
	}
	inline int qpow(int x,int p,int mod){
		x=(p?x:1);
		mod=(mod?mod:LONG_LONG_MAX);
		int t=1;
		while(p>1){
			if(p&1) t=(t*x)%mod;
			x=(x*x)%mod;
			p>>=1;
		}
		return (x*t)%mod;
	}
	inline int gcd(int x,int y){return (x%y==0?y:gcd(y,x%y));}
	inline int lcm(int x,int y){x/=gcd(x,y);return (x*y);}
	inline int max(int x,int y){return (x>y?x:y);}
	inline int min(int x,int y){return (x<y?x:y);}
	inline int abs(int x){return (x>0?x:-x);}
}
int a[N],n,m,t,k,ans;
map<int,vector<int>>mp;
signed main(){
	n=qr;
	int minn=min(n,8);
	for(int i=0;i<n;i++) a[i]=qr;
	for(int i=1;i<(1<<minn);i++){
		int sum=0;
		vector<int>tmp;
		for(int j=0;j<n;j++){
			if((i>>j)&1){
				sum=(sum+a[j])%mod;
				tmp.push_back(j+1);
			}
		}
		if(!mp[sum].empty()){
			puts("Yes");
			qwe(tmp.size());
			for(int j=0;j<tmp.size();j++) qws(tmp[j]);
			putchar('\n');
			qwe(mp[sum].size());
			for(int j=0;j<mp[sum].size();j++) qws(mp[sum][j]);
			return 0;
		}
		mp[sum]=tmp;
	}
	puts("No");
	return  0;
}
```

---

## 作者：Unnamed114514 (赞：2)

思维不够，暴力来凑。

$n=200$ 所以可以考虑 $O(n^3)$ 的暴力线性 dp：

设 $dp_{i,j,k}$ 表示前 $i$ 个元素在 $B$ 中 $\bmod 200$ 的值为 $j$，在 $C$ 中 $\bmod 200$ 的值为 $k$ 是否可行。

在 dp 过程中，我们可以这样考虑：

若 $B,C$ 都取了同一个元素，那么这个元素在两边都删掉这个元素，这样是对 $B,C$ 之间在 $\bmod200$ 之后的关系是没有影响的，所以在 dp 过程中我们可以不考虑重复的部分。

在 dp 的同时，我们记录一个数组 $pos$，$pos_{i,j,k}$ 表示为在 $(i,j,k)$ 这个状态下 $i$ 属于的集合，$0$ 表示 $i$ 一个集合都不属于，$1$ 表示 $i$ 属于第一个集合，$2$ 表示 $i$ 属于第二个集合。

那么这时，我们就可以求出方案：假设 $B$ 集合长度为 $tot_1$，$C$ 集合长度为 $tot_2$。注意到 $B,C$ 均不为空，所以在 $tot_1=0$ 或 $tot_2=0$ 的时候舍掉。

但是，此时仍然不能 AC，因为我们的想法不全面，比如下面这组数据：

input

```
3
100 100 2
``` 

output

```
Yes
1 3
3 1 2 3
```

为什么过不去呢？因为 $3$ 号元素在两个集合中均有出现。而我们上面的考虑并没有考虑重复的元素，如果我们删去重复的 $3$，那么此时集合 $B$ 为空，就会被舍掉。

所以，我们还要在此处特判一下：当一个集合为空，且另一个集合不为空时，若另一个集合没有取满，我们将任意一个未加入集合的元素同时加入 $2$ 个集合即可。

注意加入了集合后就不满足有序性了，所以还要再排个序。

时空复杂度 $O(n^3)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[205],pos[205][205][205],flg[205],a1[205],tot1,a2[205],tot2;
bool dp[205][205][205];
void dfs(int i,int j,int k){
	if(!i)
		return;
	if(pos[i][j][k]==1){
		dfs(i-1,(j-a[i]+200)%200,k);
		a1[++tot1]=i;
		flg[i]=1;
	} else if(pos[i][j][k]==2){
		dfs(i-1,j,(k-a[i]+200)%200);
		a2[++tot2]=i;
		flg[i]=2;
	} else
		dfs(i-1,j,k);
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		scanf("%d",&a[i]);
		a[i]%=200;
	}
	dp[0][0][0]=1;
	for(int i=1;i<=n;++i)
		for(int j=0;j<=200;++j)
			for(int k=0;k<=200;++k){
				if(dp[i-1][(j-a[i]+200)%200][k]){
					dp[i][j][k]=1;
					pos[i][j][k]=1;
				} else if(dp[i-1][j][(k-a[i]+200)%200]){
					dp[i][j][k]=1;
					pos[i][j][k]=2;
				} else if(dp[i-1][j][k]){
					dp[i][j][k]=1;
					pos[i][j][k]=0;
				} else{
					dp[i][j][k]=0;
					pos[i][j][k]=-1;
				}
			}
	for(int i=0;i<=200;++i)
		if(dp[n][i][i]){
			tot1=tot2=0; 
			memset(flg,0,sizeof(flg));
			dfs(n,i,i);
			if(!tot1){
				if(!tot2||tot2==n)
					continue;
				for(int j=1;j<=n;++j)
					if(!flg[j]){
						a2[++tot2]=j;
						a1[++tot1]=j;
						break;
					}
			}
			if(!tot2){
				if(!tot1||tot1==n)
					continue;
				for(int j=1;j<=n;++j)
					if(!flg[j]){
						a1[++tot1]=j;
						a2[++tot2]=j;
						break;
					}
			}
			sort(a1,a1+tot1+1);
			sort(a2,a2+tot2+1);
			puts("Yes");
			printf("%d ",tot1);
			for(int j=1;j<=tot1;++j)
				printf("%d ",a1[j]);
			puts("");
			printf("%d ",tot2);
			for(int j=1;j<=tot2;++j)
				printf("%d ",a2[j]);
			return 0;
		}
	puts("No");
	return 0;
}
```

---

## 作者：Phoenix114514 (赞：1)

# AT_abc200_d Happy Birthday! 2
[AT_abc200_d原题](https://atcoder.jp/contests/abc200/tasks/abc200_d)

[in洛谷](https://www.luogu.com.cn/problem/AT_abc200_d)
## 思路
众所周知，把三个苹果放进两个盘子里，那么必定有一个盘子里有两个苹果，这就是抽屉原理。
### 分析
本题若暴力，时间复杂度 $O(2^N)$，肯定会超时。
但模 $200$ 的余数有两百种可能。假设前 $200$ 个序列模 $200$ 的余数两两不同，那么第 $201$ 个序列模 $200$ 的余数定于前 $200$ 个中的一个模 $200$ 的余数相同。观察发现，可以构建 $256$ 个 vector。
优化后时间复杂度 $O( mod )$，其中 $mod=200$，一定不会超时。

[个人提交记录](https://atcoder.jp/contests/abc200/submissions/53753894)
### $Code$
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;//与#define ll long long 语句作用相同
ll n,a[10];
bool ok;
vector<ll> v[256],tmp;
void dfs(ll k){//深度优先搜索
	if (ok) return;
	if (k==n+1) {
		if (tmp.empty())return;//长度为0，返回
		ll sum=0;
		for (ll i:tmp) {
			sum+=a[i];
			sum%=200;
		}
		if (!v[sum].empty()) {
			cout<<"Yes\n";
			cout<<(ll)v[sum].size()<<" ";
			for (ll i:v[sum])cout<<i<<" ";
			cout<<"\n"<<(ll)tmp.size()<< " ";
			for (ll x:tmp)cout<<x<< " ";
			cout << "\n";
			ok=1;
			return;
		}
		v[sum]=tmp;
		return;
	}
	dfs(k+1);
	tmp.push_back(k);
	dfs(k+1);
	tmp.pop_back();//回溯
}

int main() {
    cin>>n;
	n=min(n,8ll);//处理
	for (ll i=1;i<=n;i++)cin>>a[i];
	dfs(1);
	if (!ok) cout<<"No";
	return 0;
}
```

---

## 作者：joe_zxq (赞：1)

# 思路

众所周知，抽屉原理：如果 $n$ 个物体要放入 $m$ 个抽屉中，且 $n>m$，那么至少有一个抽屉中放有超过一个的物体。

那么，我们转化一下问题。若存在 $201$ 个序列，那么一定其中有两个序列和对 $200$ 取模相等。

那么，我们可以枚举这么多的序列，即可求出一组答案。于是，我们只需要关心序列的前 $8$ 位。我们用二进制枚举（我习惯用 dfs 写二进制枚举），枚举 $2^8=256$ 种情况，算出答案绰绰有余。需要特别注意，序列不能为空。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

#define ll long long

ll n, a[10];
bool ok;
vector<ll> v[256];

vector<ll> tmp;

void dfs(ll k) {
	if (ok) {
		return;
	}
	if (k == n + 1) {
		if (tmp.empty()) {
			return;
		}
		ll sum = 0;
		for (ll x : tmp) {
			sum += a[x];
			sum %= 200;
		}
		if (!v[sum].empty()) {
			cout << "Yes\n";
			cout << (ll)v[sum].size() << " ";
			for (ll x : v[sum]) {
				cout << x << " ";
			}
			cout << "\n" << (ll)tmp.size() << " ";
			for (ll x : tmp) {
				cout << x << " ";
			}
			cout << "\n";
			ok = 1;
			return;
		}
		v[sum] = tmp;
		return;
	}
	dfs(k + 1);
	tmp.push_back(k);
	dfs(k + 1);
	tmp.pop_back();
}

int main() {

	cin >> n;
	n = min(n, 8ll);
	for (ll i = 1; i <= n; i++) {
		cin >> a[i];
	}
	dfs(1);
	if (!ok) {
		cout << "No"; 
	}

	return 0;
}

```

---

## 作者：ZH_qaq (赞：0)

## AT_abc200_d [ABC200D] Happy Birthday! 2 的题解
#### [洛谷传送门](https://www.luogu.com.cn/problem/AT_abc200_d)
#### [AT传送门](https://atcoder.jp/contests/abc200/tasks/abc200_d)
### 思路
我们可以证明，只要 $N\ge 8$，那么就一定有解。

证明如下：

- $8$ 个元素能组成的子序列有 $2^8-1=255$ 种。（每个元素可以选或不选，去掉全不选的情况）

- 根据抽屉原理，我们将这 $255$ 种子序列按照他们除以 $200$ 的余数分别放入抽屉中，则至少有两个子序列在一个抽屉中，即必定有合法的 $A$ 和 $B$。

当 $N<8$ 时，我们暴力枚举所有可能；

当 $N \ge 8$ 时，我们暴力枚举其中任意 $8$ 个元素组成的所有可能即可找到解。

### 代码
```cpp
#include <bits/stdc++.h>
#define lowbit(x) x & (-x)
#define endl "\n"
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
namespace fastIO {
	inline int read() {
		register int x = 0, f = 1;
		register char c = getchar();
		while (c < '0' || c > '9') {
			if(c == '-') f = -1;
			c = getchar();
		}
		while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
		return x * f;
	}
	inline void write(int x) {
		if(x < 0) putchar('-'), x = -x;
		if(x > 9) write(x / 10);
		putchar(x % 10 + '0');
		return;
	}
}
inline void print(const vector<int>& v) {
	printf("%llu", v.size());
	for(int x: v) {
		printf(" %d", x + 1);
	}
	putchar('\n');
}
using namespace fastIO;
int a[15];
vector<int> bkt[200];
int main() {
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	int n;
	n = read();
	if(n > 8) {
		n = 8;	
	}
	for(int i = 0; i < n; i ++) {
		scanf("%d", a + i);
	}
	int lim = 1 << n;
	for(int st = 0; st < lim; st ++) {
		int s = 0;
		vector<int> pos;
		for(int i = 0; i < n; i ++) {
			if(st >> i & 1) {
				s = (s + a[i]) % 200;
				pos.push_back(i);
			}
		}				
		if(!bkt[s].empty()) {
			puts("Yes");
			print(bkt[s]);
			print(pos);
			return 0;
		}
		else bkt[s] = pos;
	}
	puts("No");
	return 0;
}
```

---

## 作者：Handezheng (赞：0)

# 题解：[ABC200D] Happy Birthday! 2
最朴素、最暴力的做法是枚举 $N$ 的全排列，但是因为有 $ N \le 200$，所以这种方法无疑会超时。

这时候我们可以用**容斥**的思路进行优化。引入[抽屉原理](https://oi-wiki.org/math/combinatorics/drawer-principle/)：
>将 $n+1$ 个物体，划分为 $n$ 组，那么有至少一组有两个（或以上）的物体。
>
因为模数是 200，所以我们只要有 201 个互异的序列，就一定会有两个序列的和同余。而对于长度为 $N$ 的序列，我们可以构造出 $2^N$ 种不同序列。对于 $N\le8$，我们可以暴力取得答案；而对于 $N>8$，因为 $2^8=256>200$，所以一定有答案，我们只需要用**前八个元素**构造序列，然后用桶存储和判断即可。

代码如下：
```cpp
#include<bits/stdc++.h>
#include<vector>
#include<map>
using namespace std;
#define int long long
#define F(i,l,r) for(int i = l;i <= r;i++)

int n,a[205];
map<int,vector<int> > mp;

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	
	cin>>n;
	F(i,1,n){
		cin>>a[i];
		a[i]%=200;
	}
	n=min(n,8ll);
	for(int i=1;i<1<<n;i++){
		vector <int> t;
		int sum=0;
		for(int j=1;j<=n;j++){
			if(i>>(j-1) & 1){
				t.push_back(j);
				sum=(sum+a[j])%200;
			}
		}
		sum%=200;
		if(mp.find(sum)!=mp.end()){
			cout<<"Yes\n"<<mp[sum].size()<<' ';
			for(auto e:mp[sum])	cout<<e<<' ';
			cout<<'\n'<<t.size()<<' ';
			for(auto e:t) cout<<e<<' ';
			return 0;
		}
		mp[sum]=t;
	}
	cout<<"No\n";

	return 0;
}
```
$2024.9.18$ 完稿

---

## 作者：high_sky (赞：0)

## 正题
明显的，二进制枚举方案数组 $B,C$ 的组合方案。

显然，时间复杂度为 $O(2^{N})$，明显超时，考虑优化。

看到模数是像 $200$ 如此之小的数之后，我们就可以引入一个数学原理：

> 对于 $N+1$ 个物品放在 $N$ 个抽屉里，至少有一个抽屉有两个物品。

根据这个原理，我们知道，我们又行了。

我们的选择数组方案总数总是为 $2^N-1$，可以知道，此表达式大于等于 $200$ 的 $N$ 最小正整数为 $8$，也就是说，我们每次二进制枚举方案数组的次数最多为 $2^8$，不用担心超时问题，时间复杂度也就 $O(2^{\min\{N,8\}})$。

## Code+注释
```cpp
#include <iostream>
#include <vector>
using namespace std;
#define int long long
int n;
void out(vector<int>&a){//输出数组
	cout<<a.size();
	for(auto j:a)cout<<" "<<j;
	cout<<endl;
}
vector<vector<int>>bj(200,vector<int>(0));
signed main(){
	cin>>n;
	vector<int> a(n);
	for(auto &v:a)cin>>v;
	int m=min(8ll,n);
	for (int i=0;i<(1<<m);i++) {//枚举方案
		vector<int> b;
		int cnt=0;
		for (int j=0;j<m;j++)
			if(i&(1<<j))//符合条件
				b.push_back(j+1),cnt=(cnt+a[j])%200;
		if(bj[cnt].size()){//有同余的输出
			cout<<"Yes\n";
			out(bj[cnt]);
			out(b);
			return 0;
		}
		bj[cnt]=b;//存下方案
	}
	cout<<"No";
	return 0;
}
```

---

## 作者：iamjcer (赞：0)

这道题理清题意后，我们发现题目最难的就是序列元素的枚举。这里我们可以采用暴力枚举，枚举每个点可不可以选择。

因为每次枚举的序列都是不一样的，所以不用担心会有重复，那么最多枚举多少次呢？

这个就需要涉及到抽屉原理。首先我们要知道，模的数是 $200$，那么通过抽屉原理就可以明白，最多最多枚举 $201$ 个不一样的数，其中一定有一个模数有两种不同的数。

回到本题，同理：我们暴力枚举 $201$ 次不同的序列后，一定有 $2$ 个序列模数相同。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[205];
vector<int> tmp;
vector<int> v[205];
bool fla=false;
void dfs(int k){
	if(fla){
		return;
	}
	if(k==n+1){
		if(tmp.empty()) return;
		int sum=0;
		for(int j=0;j<tmp.size();j++){
			sum+=a[tmp[j]];
			sum%=200;
		}
		if(!v[sum].empty()){
			fla=true;
			cout<<"Yes\n";
			cout<<v[sum].size()<<' ';
			for(int j=0;j<v[sum].size();j++){
				cout<<v[sum][j]<<' ';
			}
			cout<<endl<<tmp.size()<<' ';
			for(int j=0;j<tmp.size();j++){
				cout<<tmp[j]<<' ';
			}
			return;
		}
		v[sum]=tmp;
		return;
	}
	tmp.push_back(k);
	dfs(k+1);
	tmp.pop_back(); 
	dfs(k+1);
}
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	dfs(1);
	if(fla==false){
		cout<<"No\n";
	}
	return 0;
}
```

---

## 作者：max666dong123 (赞：0)

## 题意
给定一个长为 $n$ 的序列 $a$，在 $a$ 中选择两个序列 $b$ 和 $c$。满足：
+ 令 $x$ 为 $b$ 的长度，$y$ 为 $b$ 的长度。
+ $$\sum_{i=1}^{x}{A_{b_i}}\equiv\sum_{i=1}^{y}A_{c_i}(\bmod  \ 200)$$

## 思路
小学的时候应该都学过抽屉原理，抽屉原理说的是把 $n+1$ 个苹果放进 $n$ 个抽屉中，一定有一个抽屉里至少有 $2$ 个苹果。

所以在一个长度为 $200$ 以上的序列，$\bmod \ 200$ 一定有重复的。

由于 $2^8 \geqslant 200 $ 所以我们状态压缩时只用枚举到 $\min(8,n)$ 就行了。

时间复杂度 $O(n)$。

## 代码(AC)
```cpp
#include<bits/stdc++.h>
//#include<tr1/unordered_map>
#define int long long
#define IOS ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
using namespace std;
//using namespace tr1;
const int N=2e2+10;
int n;
int a[N];
unordered_map<int,vector<int> >mp;//注意空格
void print(vector<int>v){
	cout<<v.size()<<" ";
	for(int i=0;i<v.size();i++){
		cout<<v[i]<<" ";
	}
	cout<<endl;
}
signed main(){
	IOS;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	int cn=min(n,8ll);
	for(int i=0;i<(1<<cn);i++){//状态压缩
		vector<int>t;
		int sum=0;
		for(int j=0;j<cn;j++){//枚举状态i的每一位
			if(i>>j & 1){
				sum+=a[j+1];//注意+1
				sum%=200;
				t.push_back(j+1);
			}
		}
		if(mp[sum].size()){//说明重复
			cout<<"Yes"<<endl;
			print(t);		
			print(mp[sum]);		
			return 0;
		}
		else{
			mp[sum]=t;
		}
		
	}
	cout<<"No"<<endl;
	return 0;
}
```

---

