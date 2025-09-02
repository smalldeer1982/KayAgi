# Nikita and LCM

## 题目描述

Nikita is a student passionate about number theory and algorithms. He faces an interesting problem related to an array of numbers.

Suppose Nikita has an array of integers $ a $ of length $ n $ . He will call a subsequence $ ^\dagger $ of the array special if its [least common multiple (LCM)](https://en.wikipedia.org/wiki/Least_common_multiple) is not contained in $ a $ . The LCM of an empty subsequence is equal to $ 0 $ .

Nikita wonders: what is the length of the longest special subsequence of $ a $ ? Help him answer this question!

 $ ^\dagger $ A sequence $ b $ is a subsequence of $ a $ if $ b $ can be obtained from $ a $ by the deletion of several (possibly, zero or all) elements, without changing the order of the remaining elements. For example, $ [5,2,3] $ is a subsequence of $ [1,5,7,8,2,4,3] $ .

## 说明/提示

In the first test case, the LCM of any non-empty subsequence is contained in $ a $ , so the answer is $ 0 $ .

In the second test case, we can take the subsequence $ [3, 2, 10, 1] $ , its LCM is equal to $ 30 $ , which is not contained in $ a $ .

In the third test case, we can take the subsequence $ [2, 3, 6, 100\,003] $ , its LCM is equal to $ 600\,018 $ , which is not contained in $ a $ .

## 样例 #1

### 输入

```
6
5
1 2 4 8 16
6
3 2 10 20 60 1
7
2 3 4 6 12 100003 1200036
9
2 42 7 3 6 7 7 1 6
8
4 99 57 179 10203 2 11 40812
1
1```

### 输出

```
0
4
4
5
8
0```

# 题解

## 作者：phigy (赞：13)

考虑从小到大排序，如果 $\operatorname{lcm}(a_1,a_2…a_n)\neq a_n$ 那么结果就是 $n$。

考虑一种算答案方式，比如找一个数列中未出现的 $X$ 使得 $\operatorname{lcm}(a_{p_1},a_{p_2}…a_{p_m})= X$ 且 $m$ 最大。

但是我们难以做到让最小公倍数是 $X$，因此我们考虑改写成找一个 $X$ 使得数列内是 $X$ 的因数的数的最小公倍数没有在数列中出现，要使 $X$ 在数列内的因数的个数最多。

考虑数列的最小公倍数是 $a_n$ 因此我们只需要计算 $X|a_n$ 的 $X$ 即可，那么复杂度就是 $O(nd(a_n))$。

```cpp
int T;
int n,a[MAXN];
int gcd(int a,int b) {return a==0?b:gcd(b%a,a);}
int ans;
void update(int x)
{
    int all=1,cnt=0,i;
    for(i=1;i<=n;i++) 
    {
        if(x%a[i]==0) {cnt++;all=all/gcd(a[i],all)*a[i];}
    }
    for(i=1;i<=n;i++)
    {
        if(a[i]==all) {return ;}
    }
    ans=max(ans,cnt);
}
 
signed main()
{
    int i,j,k;
    T=read();
    while(T--)
    {
        n=read();ans=0;
        for(i=1;i<=n;i++) {a[i]=read();} sort(a+1,a+n+1);
        int all=1,fl=0;
        for(i=1;i<=n;i++)
        {
            int gc=gcd(all,a[i]);
            if((long double)a[i]/(long double) gc *(long double) all>1e9) {fl=1;}
            else {all=all/gc*a[i];}
        }
        if(all!=a[n]||fl) {cout<<n<<'\n';continue;}
        for(i=1;i*i<=a[n];i++) 
        {
            if(a[n]%i==0) 
            {
                update(i);
                update(a[n]/i);
            }
        }
        cout<<ans<<'\n';
    }
    return 0;
}
```

---

## 作者：g1ove (赞：6)

记 $M=\max_{i=1}^n a_i$。

首先，如果 $\text{lcm}(a_1,a_2,a_3...a_n)>M$ 的话，直接输出 $n$ 即可。

然后就是一种情况：$\text{lcm}(a_1,a_2,a_3...a_n)=M$。

我们知道，对 $M$ 进行质因数分解，有 $M=p_1^{x_1}p_2^{x_2}...p_q^{x_q}$。这个时候，对于任意一个子序列，令 $t=\text{lcm}(a_{x_1},a_{x_2},a_{x_3}...a_{x_m})$，对 $t$ 进行质因数分解，有 $t=p_1^{y_1}p_2^{y_2}...p_q^{y_q}$。其中 $\forall i\in[1,q],y_i\le x_i$。

为什么呢？因为 $\text{lcm}(a_1,a_2,a_3...a_n)=M$。

所以我们可以直接进行 dp，像找最长上升子序列那样，由于上面的性质，可以保证状态数不会太大。状态最大值 $w\le 350$。

dp 我们使用 map 即可。

时间复杂度 $O(nw\log w)$。

注意计算 $\text{lcm}$ 时可能会爆 `long long`。

Code
```
#include<bits/stdc++.h>
#define ll long long
#define N 2005
using namespace std;
const ll M =1e9;
const ll inf=1e18;
int T;
int n;
ll a[N];
ll lcm,maxx;
ll glcm(ll x,ll y)
{
	if(x>M||y>M) return inf;
	if(x==0||y==0) return x+y;
	return x*y/__gcd(x,y);
}
set<ll>st;
map<ll,int>f,vis,g;
int res=0;
void solve()
{
	st.clear();f.clear();vis.clear();
	res=0;
	st.insert(0);
	f[0]=0;
	for(int i=1;i<=n;++i)
	{
		g=f;
		vis[a[i]]=1;
		for(auto p:st)
		{
			ll x=glcm(p,a[i]);
			f[x]=max(f[x],g[p]+1);
			st.insert(x);
		}
	}
	for(auto p:st)
		if(!vis[p]) res=max(res,f[p]);
	printf("%d\n",res);
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		lcm=maxx=0;
		for(int i=1;i<=n;i++)
			scanf("%lld",&a[i]),lcm=glcm(lcm,a[i]),maxx=max(maxx,a[i]);
		if(maxx!=lcm)
		{
			printf("%d\n",n);
			continue;
		}
		solve();
	}
	return 0;
}
```

---

## 作者：wmrqwq (赞：4)

# 题目链接

[CF1977C (luogu)](https://www.luogu.com.cn/problem/CF1977C)

[CF1977C (codeforces)](https://codeforces.com/problemset/problem/1977/C)

# 解题思路

首先我们将这个问题拆分成这个序列的 LCM 大于 $a_n$ 和这个序列的 LCM 小于等于 $a_n$ 时的两种情况，当这个序列的 LCM 大于 $a_n$ 时，显然取所有数字是合法且最优的。

然后我们接下来考虑这个序列的 LCM 小于等于 $a_n$ 的情况。

发现这种情况 LCM 很小，且有一个简单的结论，就是你在序列中任选一个子序列，这个子序列的 LCM 一定是整个序列的 LCM 的因数，因此我们直接查询整个序列的 LCM 的所有因数可达成的最大答案即可，总时间复杂度 $O(n \sqrt{V}\log_2(V))$，其中 $V$ 为值域。

# 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
//#define map unordered_map
#define forl(i,a,b) for(register long long i=a;i<=b;i++)
#define forr(i,a,b) for(register long long i=a;i>=b;i--)
#define forll(i,a,b,c) for(register long long i=a;i<=b;i+=c)
#define forrr(i,a,b,c) for(register long long i=a;i>=b;i-=c)
#define lc(x) x<<1
#define rc(x) x<<1|1
#define mid ((l+r)>>1)
#define cin(x) scanf("%lld",&x)
#define cout(x) printf("%lld",x)
#define lowbit(x) (x&-x)
#define pb push_back
#define pf push_front
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
#define endl '\n'
#define QwQ return 0;
#define ll long long
#define ull unsigned long long
#define lcm(x,y) x/__gcd(x,y)*y
#define Sum(x,y) 1ll*(x+y)*(y-x+1)/2
#define aty cout<<"Yes\n";
#define atn cout<<"No\n";
#define cfy cout<<"YES\n";
#define cfn cout<<"NO\n";
#define xxy cout<<"yes\n";
#define xxn cout<<"no\n";
#define printcf(x) x?cout<<"YES\n":cout<<"NO\n";
#define printat(x) x?cout<<"Yes\n":cout<<"No\n";
#define printxx(x) x?cout<<"yes\n":cout<<"no\n";
ll t;
ll n,a[2010],ans;
ll LCM;
map<ll,ll>mp;
ll query(ll x)
{
    ll LCM=1,sum=0;
	forl(i,1,n)
        if(x%a[i]==0)
        	LCM=lcm(LCM,a[i]),sum++;
    if(mp[LCM]==0 && LCM==x)
    	return sum;
    return 0;
}
void solve()
{
	ans=0,LCM=1;
	cin>>n;
	forl(i,1,n)
		cin>>a[i];
    sort(a+1,a+n+1);
    forl(i,1,n)
    {
        LCM=lcm(a[i],LCM);
        if(LCM>a[n])
        {
        	cout<<n<<endl;
        	return ;
		}
    }
	forl(i,1,n)
		mp[a[i]]=1;
    forl(i,1,sqrt(LCM))
    	if(LCM%i==0)
    		ans=max({ans,query(i),query(LCM/i)});
    cout<<ans<<endl;
	mp.clear();
}
int main()
{
	IOS;
	t=1;
	cin>>t;
	while(t--)
		solve();
    /******************/
	/*while(L<q[i].l) */
	/*    del(a[L++]);*/
	/*while(L>q[i].l) */
	/*    add(a[--L]);*/
	/*while(R<q[i].r) */
	/*	  add(a[++R]);*/
	/*while(R>q[i].r) */
	/*    del(a[R--]);*/
    /******************/
	QwQ;
}
```

---

## 作者：sbno333 (赞：3)

感觉题目质量很高。

我们首先确定这些数最大公因数答案大于 $10^9$ 时答案显然为 $n$。

接着对于小于 $10^9$，显然最终答案为其因数，考虑确定了最小公倍数，发现很好处理，所有它的因数加进来只会使最小公倍数大，且不会超过我们期望的最小公倍数，其他数加进来显然不能得到我们希望的。

所以我们考虑贪心加，判断是否和我们期望一样，此时长度肯定最大，如果一样，那我们就处理答案，因为这是合法的。

注意因数不能是序列中的数。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int a[1000009];
map<int,bool> p;
int n;
int ck(int x){
	int z;
	z=1;
	int s;
	s=0;
	for(int i=1;i<=n;i++){
		if(x%a[i]==0){
			int g;
			g=__gcd(a[i],z);
			z*=a[i];
			z/=g;
			s++;
		}
	}
	if(z==x){
		return s;
	}
	return 0;
}
void _main(){
	cin>>n;
	p.clear();
	for(int i=1;i<=n;i++){
		cin>>a[i];
		p[a[i]]=1;
	}
	int z;
	z=1;
	for(int i=1;i<=n;i++){
		int g;
		g=__gcd(a[i],z);
		z*=a[i];
		z/=g;
		if(z>1e9){
			cout<<n<<endl;
			return;
		}
	}
	if(!p[z]){
		cout<<n<<endl;
		return;
	}
	int ans;
	ans=0;
	for(int i=1;i<=sqrt(z);i++){
		if(z%i==0){
			if(!p[i]){
			ans=max(ans,ck(i));
		}
		if(!p[z/i]){
			ans=max(ans,ck(z/i));
		}
		}
		
	}
	cout<<ans<<endl;
}
signed main(){
	std::ios::sync_with_stdio(0);
	int t;
	cin>>t;
	while(t--){
		_main();
	} 
	return 0;
}
```

---

## 作者：封禁用户 (赞：1)

### 思路
显然，所有子序列的 $\operatorname{lcm}$ 都是整体 $\operatorname{lcm}$ 的因数。然后我们就可以直接枚举 $\operatorname{lcm}$ 的因数然后判断。

判断因数 $K$ 符合的条件具体为：

- 所有 $a_i \ne K$。
- 所有 $a_i<K$ 且 $K\bmod a_i=0$ 的最小公倍数等于 $K$。
（update：语序写错了一丢丢，感谢同机房大佬们指出。）
### 代码
```cpp
#include<bits/stdc++.h>
#define int long long 
#define Maxn 2005 
using namespace std;
int a[Maxn],e[1000005],tot;
map<int,int> mp;
bool cmp(int it,int is) {
    return it>is;
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t,n;
    cin>>t;
    while(t--) {
        cin>>n;
        int lcm;
        tot=0;
        mp.clear();
        for(int i=1;i<=n;i++)
            cin>>a[i],mp[a[i]]++;
        lcm=a[1];
        for(int i=2;i<=n;i++) {
            lcm=a[i]*lcm/__gcd(a[i],lcm);
            if (lcm>2000000000)
                break;
        }
        sort(a+1,a+1+n);
        if(lcm!=a[n]||!mp.count(lcm)) {
            cout<<n<<"\n";
            continue;
        }
        int ans=0;
        for(int i=1;i*i<=lcm;i++)
            if(lcm%i==0)e[++tot]=i,i*i!=lcm?e[++tot]=lcm/i:1;
        for(int i=tot;i>=0;i--) {
            if(mp.count(e[i]))continue;
            int res=0;
            queue<int> P;
            for(int k=1;k<=n;k++) {
                if(e[i]%a[k]==0&&a[k]<=e[i])
                    res++,P.push(a[k]);
            } if(P.empty())continue;
            int sg=P.front();P.pop();
            while(!P.empty()) {
                sg=sg*P.front()/__gcd(sg,P.front()),
                P.pop();
            } if(sg==e[i])ans=max(ans,res);
        } cout<<ans<<"\n";
    }
    return 0;
}
```

---

## 作者：ttq012 (赞：1)

$20\text{min}$ 速通 $1900$，祭之。

有一个很显然的结论就是：若 $\text{lcm}(a_1,a_2,a_3,\ldots,a_n)\neq a_n$ 那么可以全选上。

然后有一个更显然的结论：一定存在解。因为 $a_i\neq 0$，所以可以选一个空的子序列满足 $\text{lcm}$ 的值为 $0$，符合条件。

考虑不能全选的情况，此时 $a_n=\text{lcm}(a_1,a_2,a_3,\ldots,a_n)$。也就是说不论选取的集合 $S$ 怎么选择，值都一定是 $a_n$ 的因数。所以只需要枚举 $a_n$ 的所有因数，判断是否合法，然后再求一下最多可以选择多少个数即可。代码有一些细节。

```cpp
#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define int long long
#define pb push_back
#define em emplace_back
#define F(i,x,y) for(int i=x;i<=y;i++)
#define G(i,x,y) for(int i=x;i>=y;i--)
#define W(G,i,x) for(auto&i:G[x])
#define W_(G,i,j,x) for(auto&[i,j]:G[x])
#define add(x,y) z[x].em(y)
#define add_(x,y) add(x,y),add(y,x)
#define Add(x,y,d) z[x].em(y,d)
#define Add_(x,y,z) Add(x,y,z),Add(y,x,z);
#ifdef int
#define inf (7611257611378358090ll/2)
#else
#define inf 0x3f3f3f3f
#endif
using namespace std;
const int N = 1000100;
int a[N];
int ll(int a, int b) {
    return a / __gcd(a, b) * b;
}
auto main() [[O3]] -> signed {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        F(i, 1, n) cin >> a[i];
        int _l = a[1];
        F(i, 2, n) {
            _l = ll(_l, a[i]);
            if (_l > 2000000000) {
                break;
            }
        }
        set<int> se;
        F(i, 1, n) se.insert(a[i]);
        if (!se.count(_l)) cout << n << '\n';
        else {
            sort(a + 1, a + n + 1);
            if (_l != a[n]) cout << n << '\n';
            else {
                int mx = 0;
                vector<int> div;
                for (int i = 1; i * i <= a[n]; i++) {
                    if (a[n] % i == 0) {
                        div.pb(i);
                        if (i * i != a[n]) div.pb(a[n] / i);
                    }
                }
                sort(div.begin(), div.end());
                for (auto &x : div) {
                    if (!se.count(x)) {
                        int cnt = 0;
                        vector<int> chaofeng;
                        F(i, 1, n) {
                            if (x % a[i] == 0) {
                                cnt++;
                                chaofeng.pb(a[i]);
                            }
                        }
                        if (chaofeng.size()) {
                            int l1 = chaofeng[0];
                            F(i, 1, (int)chaofeng.size() - 1) {
                                l1 = ll(l1, chaofeng[i]);
                            }
                            if (l1 == x) {
                                mx = max(mx, cnt);
                            }
                        }
                    }
                }
                cout << mx << '\n';
            }
        }
    }
}
```

---

## 作者：CaoSheng_zzz (赞：1)

### 题目大意

给你一个数组 $ a $，令 $ t $ 为 $ a $ 的子序列且 $ t $ 中所有数的最小公倍数 $ \notin a $ 求 $ t $ 数组中最多有多少个数。

### 思路
非常明显这是一道数学题，对于数组 $ a $ 我们首先从小到大拍一个序，然后我们可以求出 $ a $ 中所有数的最大公倍数，如果这个公倍数 $ \not= a_n $ 所以答案为 $ n $，否者可以证明 $ a_1,a_2,\dots,a_n $  都为 $ a_n $ 的因子。

我们可以枚举 $ a_n $ 的每一个因子 $ d $ 如果 $ d $ 没有在 $ a $ 数组中出现过，那么我们就去 Check $ d $，而 Check 的内容为判断 $ a $ 数组里面的数是否能组成 $ d $，思路大致就是这样，小细节就看代码了。

Code：
```cpp
#include <algorithm>
#include <iostream>
#include <math.h>
#include <string.h>
#include <queue>
#include <stdio.h>
#include <map>
#define ll long long
#define prt printf
#define int long long
#define sc(ppt) scanf("%lld" , &ppt)
using namespace std;

int t , n , ans = 0 , a[2005];
map<int , int> G;

int lcm(int a , int b){
	return a * b / __gcd(a , b);
}

void check(int d){
	int cnt = 0 , res = 1;
	for(int i=1 ; i<=n ; i++){
		if(a[i] == a[n]) break;
		if(d % a[i] == 0){
			++ cnt;
			res = lcm(res , a[i]);
		}
	}
	if(res == d) ans = max(ans , cnt); // 打一个擂台 
}

void solve(){
	int res = 1;
	for(int i=1 ; i<=n ; i++){
		res = lcm(res , a[i]);
		if(res > a[n]){
			ans = n ;
			break;
		}
	}
	if(ans != n && !G.count(res)) ans = n;
	for(int i=1 ; i*i<=a[n] ; i++){
		if(a[n] % i != 0) continue;
		if(!G.count(i)){ check(i);}
		if(i * i != a[n] && !G.count(a[n] / i)) check(a[n] / i);
	}
}	

signed main(){
	sc(t) ; while(t --){
		ans = 0 ; G.clear() ;	
		sc(n) ; for(int i=1 ; i<=n ; i++){
			sc(a[i]) ; G[a[i]] =  1;
		}
		sort(a + 1 , a + n + 1) ; solve() ;
		prt("%lld\n" , ans); 
	}
	return 0;
}
```

---

