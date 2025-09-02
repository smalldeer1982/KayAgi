# LR-remainders

## 题目描述

给定一个长度为 $n$ 的数组 $a$，一个正整数 $m$，以及一个长度为 $n$ 的命令字符串。每个命令要么是字符 `L`，要么是字符 `R`。

按照字符串 $s$ 中写入的顺序处理所有 $n$ 个命令。处理命令的步骤如下：

首先，输出数组 $a$ 中所有元素的乘积除以 $m$ 的余数。
然后，如果命令是 `L`，则从数组 $a$ 中移除最左边的元素；如果命令是 `R`，则从数组 $a$ 中移除最右边的元素。
请注意，每次移动后，数组 $a$ 的长度减少 $1$，并且在处理所有命令后，数组将为空。

编写一个程序，按照字符串 $s$ 中写入的顺序从左到右处理所有命令。

## 样例 #1

### 输入

```
4
4 6
3 1 4 2
LRRL
5 1
1 1 1 1 1
LLLLL
6 8
1 2 3 4 5 6
RLLLRR
1 10000
10000
R```

### 输出

```
0 2 4 1 
0 0 0 0 0 
0 0 0 4 4 4 
0```

# 题解

## 作者：xiaorunrun520 (赞：4)

# CF1932C
## 题意
给定长度为 $n$ 的数组 $a$ 和 $n$ 个命令，每个命令会删除最左边或最右边的一个元素，每次求出数组中所有剩余元素的乘积关于 $m$ 的余数。
## 思路
由于数据范围肯定会爆 long long，所以不能直接相乘。
我们可以找到最后被删除的两个元素 $last$ 和 $last+1$，先分别取模 $m$ ，再分别向左和向右求出下一个数的与自己相乘的后的余数，结果记录在数组 $rec$ 中。访问时，用两个变量 $l$ 和 $r$ 记录剩余区间的左右端点，每次输出 $rec[l] \times rec[r] \bmod m $ 的结果。特别的，当 $l = r$ 时，直接输出 $rec[l]$ 并换行即可。 
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,rec[200005],a[200005],m,last,l,r;
char com[200005];
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&n,&m);
		l=1,r=n,last=0;
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
		}
		for(int i=1;i<=n;i++){
			scanf("%1s",&com[i]);
			if(r-l+1==2) last=l;
			if(com[i]=='L') l++;
			else r--;
		}
		l=1,r=n;
		rec[last]=a[last]%m; 
		rec[last+1]=a[last+1]%m; 
		for(int i=last-1;i>=1;i--) rec[i]=(a[i]*rec[i+1])%m;
		for(int i=last+2;i<=n;i++) rec[i]=(a[i]*rec[i-1])%m;
		for(int i=1;i<=n;i++){
			if(l!=r) printf("%d ",(rec[l]*rec[r])%m);
			else printf("%d\n",rec[l]);
			if(com[i]=='L') l++;
			else if(com[i]=='R')r--;
		}
	}
	return 0;
}
```


---

## 作者：SY_nzwmb83 (赞：2)

### 题意

给定长为 $n$ 的数组 $a$ 和字符串 $s$，每次删去 $a$ 最左边或最右边的数，删前求出 $a$ 中所有数的积并模 $m$。

### 分析

因为 $a$ 和 $s$ 长度相等，那最后 $a$ 必然被删完，也就是说输出的最后一个数时 $a$ 只剩下一个数了。

那么就可以先根据 $s$ 求出最后剩下的那个数，然后再倒序遍历 $s$，还原被删的数，同时统计答案，最后要把答案再倒序输出。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int tt,v[2000005],ans[2000005];
char s[2000005];
void solve()
{
	int n,m,cnt=0;
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cin>>v[i];
		v[i]=v[i]%m;
	}
	for(int i=1;i<n;i++)
	{
		cin>>s[i];
		if(s[i]=='L')cnt++;//统计左边一共删了几个，就可以求出最后剩下的
	}
	cin>>s[n];//最后一个输入L和R等效，不单独处理反而影响L的个数
	int l=cnt+1,r=cnt+1,now=v[cnt+1]%m;//l和r记录区间边界，now统计答案
	cnt=1;
	ans[cnt++]=now;
	for(int i=n-1;i>=1;i--)//此时最后一个也要忽略
	{
		if(s[i]=='L')//还原左边被删掉的数
		{
			l--;
			now=now*v[l]%m;
			ans[cnt++]=now;
		}
		if(s[i]=='R')//还原右边被删掉的数
		{
			r++;
			now=now*v[r]%m;
			ans[cnt++]=now;
		}
	}
	for(int i=n;i>=1;i--)
	{
		cout<<ans[i]<<' ';
	}
	cout<<'\n';
	return;
}
signed main()
{
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	cin>>tt;
	while(tt--)
	{
		solve();
	}
	return 0;
}
```

---

## 作者：文瀚哲 (赞：2)

# 题意
给你一个长度为 $n$ 的数组和一个长度为 $n$ 的字符串，根据字符串中 $L$ 和 $R$ 的指示取出当前数组内最左或最右的元素，输出每次取出元素前数组内剩余元素的乘积除以 $m$ 的余数。

# 思路
第一眼，简单的模拟，然后寄了。![](https://cdn.luogu.com.cn/upload/image_hosting/0hyhvym3.png)

这时候发现数据范围 $1\le a_i\le10^4$，$1\le n \le 2\times10^5$ 很好，爆 int 了。

但是不要紧，我会取模，可是，取模后除以要取出的元素，再模 $m$ 的答案就不对了，既然除不行，那就可以试试把要取出的元素按倒序乘起来！

代码如下：

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<string>
using namespace std;
const int maxn=200001;
int n,m;
struct node
{
	int a,num;//用num记下这个元素第几个被取出。
}ljq[maxn];//%%%ljq
int ans[maxn],cur;
bool cmp(node x,node y)
{
	return x.num>y.num;
}
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		memset(ans,0,sizeof(ans));//多测不清空，十年OI一场空！
		cur=0;
		memset(ljq,0,sizeof(ljq));
		scanf("%d%d",&n,&m);
		long long cnt=1;
		string s;
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&ljq[i].a);
		}
		cin>>s;
		int l=0,r=n+1;
		for(int i=0;i<=n;i++)
		{
			if(s[i]=='L')
			{
				l++;
				ljq[l].num=i+1;
			}
			else if(s[i]=='R')
			{
				r--;
				ljq[r].num=i+1;
			}
		}
		sort(ljq+1,ljq+n+1,cmp);
		for(int i=1;i<=n;i++)
		{
			cnt*=ljq[i].a;
			cnt%=m;
			ans[++cur]=cnt;
		}//按倒序把元素乘起来
		for(int i=cur;i>=1;i--)
		{
			cout<<ans[i]<<" ";//输出自然也要是倒序。
		}
		cout<<endl;
	}
	return 0;
}
```


AC记录：
![AC记录](https://cdn.luogu.com.cn/upload/image_hosting/kauz128q.png)

---

## 作者：Cute__yhb (赞：2)

## 思路
显然的，这题让你求一个区间的乘积取模一个数。

而区间乘积可以用线段树维护。

由于这个是静态的，懒标记都不用写。

然后这题就结束了。

正解：

既然每次操作是去掉一个数，我们可以反过来，一开始序列为空，每次往序列里加入一个数，然后求出答案即可，时间复杂度仅有 $O(n)$。

## 代码

（由于赛时没想出正解来，故只贴线段树的代码。）

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ls x<<1
#define rs x<<1|1
#define mid (l+r)/2
int n;
ll m,a[200005];
struct node{//线段树
	ll sum;
}tree[800005];
void pushup(int x){//向上更新
	tree[x].sum=(tree[ls].sum*tree[rs].sum)%m;
}
void build(int x,int l,int r){//建树
	if(l==r){
		tree[x].sum=a[l];
		return ;
	}
	build(ls,l,mid);
	build(rs,mid+1,r);
	pushup(x);
}
ll query(int x,int l,int r,int L,int R){//查询
	if(L<=l&&r<=R){//被答案的区间覆盖
		return tree[x].sum;
	}
	ll sum=1;
	if(L<=mid){
		sum*=query(ls,l,mid,L,R);
		sum%=m;
	}
	if(R>mid){
		sum*=query(rs,mid+1,r,L,R);
		sum%=m;
	}
	return sum%m;
}
void solve(){
	string s;
	cin>>n>>m;
	for(int i=1;i<=n;i++){//输入
		cin>>a[i];
	}
	build(1,1,n);//建树
	cin>>s;
	int l=1,r=n;
	cout<<query(1,1,n,1,n)%m<<' ';//输出一开始所有数的乘积
	for(int i=0;i<s.size();i++){
		if(s[i]=='L') l++;//更新左右端点
		else r--;
		if(r<l) break;//序列为空
		cout<<query(1,1,n,l,r)<<' ';//输出
	}
	cout<<'\n';
}
int main(){
	int t;
	cin>>t;
	while(t--) solve();
    return 0;
}
```


---

## 作者：NEKO_Daze (赞：1)

洛谷题目传送门：[CF1932C](https://www.luogu.com.cn/problem/CF1932C)   | |  CF原题传送门：[1932C](https://codeforces.com/contest/1932/problem/C)

#### 简要题意

给你一个序列，按照 `L` 和 `R` 的指令对序列操作，删除序列左边或右边的数。输出删除前序列里数的乘积 $\bmod m$ 的结果。

#### 思路

模拟题。只不过要注意数据范围为 $1\leq n \leq 2 ·10^5 ,1 \leq m \leq 10^4$，乘积可能爆 int，所以每次做乘法就先 $\bmod m$ 一次。

代码如下：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int T,n,m,a[200005],p[200005],ans[200005],l,r,mul;
string s;
signed main()
{
    cin>>T;
    while(T--)
    {
    	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i];
	cin>>s;
	l=1;r=n;mul=1;
	for(int i=0;i<n;i++)
	{
            if(s[i]=='L'){p[i+1]=l;l++;} else{p[i+1]=r;r--;}
	}
	for(int i=n;i>=1;i--) {mul=mul*a[p[i]]%m;ans[i]=mul;}
	for(int i=1;i<=n;i++) cout<<ans[i]<<" ";
	cout<<"\n";
    }
    return 0;
}
```

---

## 作者：xxr___ (赞：1)

### 思路：
首先不难发现由 `L` 到 `R` 组成的区间是一段连续区间，所以可以想到线段树，本题我们用线段树解决。
#### 细节处理：
由于要相乘所以可能会爆 `long long` 因此我们在更新某个节点的信息时不要忘记取模，赛时我就是因为这个吃了两发罚时。
### 代码：
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<map>
using namespace std;
#define f(i,n) for(int (i)=1;(i)<=(n);(i)++)
#define int long long 
typedef long long ll;
const int N=2e5+5;
ll a[N];
ll t[N<<2];
ll mod;
int ls(int p){
	return p<<1;
}
int rs(int p){
	return p<<1|1;
}
void pushup(int p){
	t[p]=t[ls(p)]*t[rs(p)];
	t[p]=t[p]%mod; 
}
void build(int p,int l,int r){
	if(l==r){
		t[p]=a[l]%mod;
		return;
	}
	int mid=(l+r)>>1;
	build(ls(p),l,mid);
	build(rs(p),mid+1,r);
	pushup(p);
}
ll query(int p,int l,int r,int L,int R){
	if(L<=l&&r<=R){
		return t[p]%mod;
	}
	ll s=1;
	int mid=(l+r)>>1;
	if(L<=mid){
		s*=query(ls(p),l,mid,L,R);
		s%=mod;
	}
	if(mid+1<=R){
		s*=query(rs(p),mid+1,r,L,R);
		s%=mod;
	}
	return s%mod;
}
void solve(){
	int n;
	cin>>n>>mod;
	for(int i=1;i<=(n<<2);i++)t[i]=0;
	for(int i=1;i<=n;i++)cin>>a[i];
	build(1,1,n);
	int l=1,r=n;
	string s;
	cin>>s;
	int len=s.size();
	for(int i=0;i<len;i++){
		cout<<query(1,1,n,l,r)%mod<<' ';
		if(s[i]=='L')l++;
		if(s[i]=='R')r--;
		if(l>r)break;
	}
	cout<<'\n';
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);cout.tie(nullptr);
	int T;
	cin>>T;
	while(T--){
		solve();
	}
	return 0;
}
```

---

## 作者：2huk (赞：1)

### Description

给定一个长度为 $n$ 的数组 $a$ 和 $n$ 个指令，每条指令为 $\texttt{L,R}$ 中的一种。

依次处理每个指令：

- 首先，输出 $a$ 中所有元素的乘积除以 $m$ 的余数。
- 然后，如果当前指令为 $\texttt L$，则移除数组 $a$ 中最左边的元素；如果当前指令为 $\texttt R$，则移除数组 $a$ 中最右边的元素。

### Solution

首先不难发现每次操作是求一段区间的乘积模 $m$。不难想到用数据结构（比如线段树、ST 表）维护。注意如果维护前缀积是不合法的，因为有可能 $s_{l - 1} = 0$，除法 $\dfrac{s_r}{s_{l - 1}}$ 就假了。

数据结构维护的复杂度是 $\mathcal O(n \log n)$ 的。因为不想写线段树所以写了个 $\mathcal O(n)$ 的做法。

我们可以倒序处理每个操作，原来的删除操作转化成加数操作。这样我们维护的答案每次操作会将它乘上一个数而非除以一个数，这样就避免了取模后为 $0$ 的数。

具体的，我们维护当前剩余的没有被删除的数构成的区间 $[l, r]$，并维护当前答案。初始时按照读入顺序求出 $l, r$ 所在位置，并令答案为 $1$。

倒序处理每一个操作：

- 如果当前操作为 $\texttt L$，将 $l \gets l - 1$，将答案乘上 $a_l$；
- 如果当前操作为 $\texttt R$，将 $r \gets r + 1$，将答案乘上 $a_r$；

然后再倒序输出答案即可。

### Code

```cpp
void solve() {
	int n = read(), m = read();
	vector<int> a(n), res(n, 0);
	res[0] = 1;
	for (int &t : a) t = read(), (res[0] *= t) %= m;
	
	int l = 0, r = n - 1;
	string s = "";
	for (int i = 0; i < n; ++ i ) {
		char c;
		cin >> c;
		if (c == 'L') ++ l;
		else -- r;
		
		s.push_back(c);
	}
	
	int x = 1;
	for (int i = n - 1; i; -- i ) {
		if (s[i] == 'L') {
			-- l;
			(x *= a[l]) %= m;
		}
		else {
			++ r;
			(x *= a[r]) %= m;
		}
		res[i] = x;
	}
	
	for (int &t : res) wsp(t);
}
```

---

## 作者：_299817_ (赞：1)

## Part 1：思路
由于题目中有模数，所以我们不能先全部乘起来再一个个除。

由于模数不一定为质数，所以我们不能通过逆元的方式解决。

但是我们可以观察到题目中并没有要求强制在线，于是我们可以考虑离线算法。

离线算法很好想，就是求出每个数会第几个被删除，接着按顺序模拟一个个乘最后存下答案后输出即可。

## Part 2：代码
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<cstdlib>
#include<cmath>
#include<iomanip>
#include<cstring>
#include<unordered_map>
#include<map>
#include<queue>
#include<stack>
#include<bitset>
#include<list>
#define rep(i, l, r) for(int i = signed(l); i <= signed(r); i++)
#define per(i, l, r) for(int i = signed(l); i >= signed(r); i--)
#define sort stable_sort
using namespace std;
typedef long long ll;

int T;
int n, mod;
int a[200010];
vector<int> v; // 储存被删的数
int ans = 0;
vector<int> aans; // 储存答案

int main(){
    #ifdef QwQ_ATM
        freopen("input.in", "r", stdin);
        freopen("output.out", "w", stdout);
    #endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> T;
    while(T--){
        cin >> n >> mod;
        rep(i, 1, n) cin >> a[i];
        int l = 1, r = n; // 记录当前区间
        rep(i, 1, n){
            char c;
            cin >> c;
            if(c == 'L'){
                l++;
                v.push_back(l - 1);
            }else{
                r--;
                v.push_back(r + 1);
            }
        }
        ans = 1;
        per(i, n, 1){
            ans *= a[v[i - 1]];
            ans %= mod;
            aans.push_back(ans);
        }
        per(i, n, 1) cout << aans[i - 1] << " ";
        cout << endl;
        v.clear(), aans.clear(); // 多测清空
    }
    return 0;
}
```


---

## 作者：apiad (赞：0)

正着做不好做，那么我们反着做。

我们将每一个左还是右存进一个 stack 中。然后操作就变成了每一次加了右边一个点，然后或者加了左边一个点。然后我们直接按照题意模拟一遍即可。

```cpp
// LUOGU_RID: 148050577
//Author: gsczl71
//Copyright (c) 2024 gsczl71 All rights reserved.

#include<bits/stdc++.h>
#define ll long long
#define i128 __int128
#define ull unsigned long long
#define pii pair<int,int>
#define pll pair<long long, long long>
#define fs first
#define sc second
#define endl '\n'
#define debug puts("AK IOI")
#define re register
#define pb push_back
#define mem(a,x) memset((a),(x),sizeof(a))
#define vi vector<int>
using namespace std;
#define int long long
const int mod = 1e9+7;
//const int mod = 998244353;
const int inf = 0x3f3f3f3f,N = 2e5+5,M = 2e5+5;
const ll linf = 0x3f3f3f3f3f3f3f3f;
int n,m;
int a[N];
string s;
int sum=0;
int b[N];
void solve(){
	cin>>n>>m;for(int i=1;i<=n;i++)cin>>a[i];
	cin >> s;
	stack<int> st;int l = 1,r = n;
	for(int i = 0 ;i < s.size();i++){
		if(s[i]=='L') st.push(l++);
		else st.push(r--);
	}
	stack<int> ans;
	int x = 1;
	while(!st.empty()){
		x = (a[st.top()] * x) % m;st.pop();
		ans.push(x);
	}while(!ans.empty()){
		cout<<ans.top()<<" ";ans.pop();
	}cout<<endl;
}
signed main(){
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	int T=1;
	cin >> T;
	while(T--) solve();
	return 0;
}
 
 ```

---

## 作者：_smart_stupid_ (赞：0)

## [题目](https://www.luogu.com.cn/problem/CF1932C)

某些人看到了就会用线段树做，但是这个题不是线段树，它有更好的方法。

我们倒着处理答案，先找到结束时我们进行 `L` 操作时取的数字和 `R` 操作时取的数字，让第 $n+1$ 次操作的答案为 $1$，然后倒着遍历操作，每取出一个数，就将这个数乘到答案里。再模上 $m$ 即可。

## AC Code：

```cpp
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
int t;
int n, m;
int a[200100];
int ans[200100];
char s[200100];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> t;
	while (t--) {
		cin >> n >> m;
		for (int i = 1; i <= n; i ++) cin >> a[i];
		int l = 0, r;
		for (int i = 1; i <= n; i ++) cin >> s[i];
		for (int i = 1; i <= n; i ++) {
			if (s[i] == 'L') l++;
		}
		ans[n + 1] = 1;
		r = l + 1;
		for (int i = n; i >= 1; i --) {
			ans[i] = ans[i + 1];
			if (s[i] == 'L') {
				ans[i] *= a[l];
				ans[i] %= m;
				l--;
			}
			else {
				ans[i] *= a[r];
				ans[i] %= m;
				r++;
			}
		}
		for (int i = 1; i <= n; i ++) cout << ans[i] << ' ';
		cout << '\n';
	}
	return 0;
}
```

---

## 作者：jiangjiangQwQ (赞：0)

### 思路
题目要求当前剩下的数的乘积除以 $m$ 的余数，给定一个命令序列，删掉当前最左边或最右边的那个数。思路就是直接上线段树无脑模拟。用 $sum$ 变量储存当前区间的乘积，在更新时记得取模，防止溢出，然后输出答案弄个区间查询就好了。
### 代码
```cpp
#include<iostream>
using namespace std;
const int N=2e5+5;
#define ls(c) c<<1
#define rs(c) c<<1|1
int T,n,m,a[N];
//标准板子
struct Node{
    int l,r;
    long long sum;
}t[N<<2];
inline void push_up(int c){
    t[c].sum=t[ls(c)].sum%m*t[rs(c)].sum%m;
}
inline void build(int c,int l,int r){
    t[c].sum=1;t[c].l=l;t[c].r=r;
    if(l==r) return;
    int mid=(l+r)>>1;
    build(ls(c),l,mid);
    build(rs(c),mid+1,r);
    push_up(c);
    return;
}
inline void update(int c,int x,int k){
    if(t[c].l==t[c].r){
        t[c].sum=k;
        return;
    }
    int mid=(t[c].l+t[c].r)>>1;
    if(x<=mid) update(ls(c),x,k);
    if(x>mid) update(rs(c),x,k);
    push_up(c);
    return;
}
int query(int c,int l,int r){
    if(l<=t[c].l&&r>=t[c].r) return t[c].sum%m;
    int mid=(t[c].l+t[c].r)>>1,res=1;
    if(l<=mid) res=res*query(ls(c),l,r)%m;
    if(r>mid) res=res*query(rs(c),l,r)%m;
    return res;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n>>m;
        build(1,1,n);
        for(int i=1;i<=n;i++){
            cin>>a[i];
            update(1,i,a[i]%m);
            //提前取模
            // cout<<query(1,i,i)<<' ';
        }
        int l=1,r=n;
        //弄个双指针移动区间
        string s;cin>>s;
        for(int i=0;i<s.size();i++){
            char c=s[i];
            // cout<<l<<' '<<r<<'\n';
            cout<<query(1,l,r)<<' ';
            //输出当前区间乘积
            if(c=='L') l++;
            else r--;
        }
        cout<<'\n';
    }
    return 0;
}
```

---

## 作者：RyanLi (赞：0)

传送门：洛谷 [LR-remainders](https://www.luogu.com.cn/problem/CF1932C) | Codeforces [C. LR-remainders](https://codeforces.com/contest/1932/problem/C)

更佳的阅读体验：[CF1932C 题解](https://blog.ryanli.top/index.php/archives/36/)

---

**简要题意**：给定序列 $a$ 以及一个操作序列，操作前求区间 $[l, r]$ 每个元素的积，当前操作为 $\texttt{L}$ 则给左端点 $l$ 加一，为 $\texttt{R}$ 则给右端点 $r$ 减一。

需要多次求不同区间中元素的积，考虑维护区间左右端点的位置，用线段树维护区间积即可。

```cpp
#include <iostream>
#define ls p << 1
#define rs p << 1 | 1
#define mid (l + r >> 1)
using namespace std;
using ll = long long;

const int N = 2e5 + 10, M = 8e5 + 10;
int t, n, l, r;
ll a[N];
string s;
struct seg_tree {
    ll s[M], m;

    void pushup(int p) {
        s[p] = s[ls] * s[rs] % m;
    }

    void build(int p, int l, int r) {
        if (l == r) return s[p] = a[l], void();
        build(ls, l, mid);
        build(rs, mid + 1, r);
        pushup(p);
    }

    ll query(int p, int l, int r, int L, int R) {
        if (l > R || r < L) return 1;
        if (l >= L && r <= R) return s[p];
        return query(ls, l, mid, L, R) * query(rs, mid + 1, r, L, R) % m;
    }
} tree;

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    for (cin >> t; t; --t) {
        cin >> n >> tree.m;
        l = 1, r = n;
        for (int i = 1; i <= n; ++i) cin >> a[i], a[i] %= tree.m;
        tree.build(1, 1, n);
        cin >> s;
        for (auto p : s) {
            cout << tree.query(1, 1, n, l, r) << ' ';
            p == 'L' ? ++l : --r;
        } cout << '\n';
    } return 0;
}
```


---

## 作者：Infinite_Loop (赞：0)

# CF1932C
## 题意
给定一个长度为 $n$ 的数组 $a$ 和 $n$ 个命令，每个命令可以取出当前数组最左或最右的元素，在每次命令前输出当前剩余元素的积除以 $m$ 的余数。
## 思路
由于已经提前知道每个命令是什么，我们只要用栈把数组内元素的先后顺序排好，然后依次算余数就行了。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int t,n,m,a[N];
string str;
int main(){
	cin>>t;
	while(t--){
		cin>>n>>m;
		for(int i=1;i<=n;i++)cin>>a[i];
		cin>>str;
		str="#"+str;
		stack<int>q;
		int l=1,r=n;
		for(int i=1;i<=n;i++){
			if(str[i]=='L'){
				q.push(a[l]);
				l++;
			}else{
				q.push(a[r]);
				r--;
			}
		}
		vector<int>vec;
		int sum=1;
		while(!q.empty()){
			int x=q.top();
			q.pop();
			sum*=x;
			sum%=m;
			vec.push_back(sum);
		}
		reverse(vec.begin(),vec.end());
		for(int i=0;i<vec.size();i++)cout<<vec[i]<<" ";
		cout<<endl;
	}
	return 0;
}
```


---

## 作者：Cure_Wing (赞：0)

[CF1932C LR-remainders](https://www.luogu.com.cn/problem/CF1932C)

### 思路

如果正着做，这就意味着每次都要除以一个数，但是 $m$ 不是质数，无法使用逆元快速求解。

我们希望每次做的是乘法。看到数是只删不加，考虑将操作倒序完成，化除为乘。我们先正着找出最后剩下的那个数，然后依次将上一个操作删除的数乘进答案就可以了。

时间复杂度 $O(\sum n)$。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using std::cin;using std::cout;
constexpr int N=200005;
int t,n,m,a[N],mul,u,v,ans[N];
std::string s;
inline void down(int l,int r,int k){
	if(k==n+1) return ;
	if(s[k]=='L') down(l+1,r,k+1);//先找出最后一个数
	else down(l,r-1,k+1);
	if(s[k]=='L') mul=1ll*mul*a[l]%m;
	else mul=1ll*mul*a[r]%m;//把上一次删的数依次乘回去
	ans[k]=mul;
}
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);cout.tie(nullptr);
	for(cin>>t;t--;cout<<'\n'){
		cin>>n>>m;mul=1;
		for(int i=1;i<=n;++i) cin>>a[i];
		cin>>s;s=" "+s;
		down(1,n,1);
		for(int i=1;i<=n;++i) cout<<ans[i]<<' ';
	}
	return 0;
}
```

---

## 作者：fengziyi (赞：0)

### 题意

依照 $n$ 次指令，删除给定数列最左侧或最右侧的一个数，求剩余数之积对 $m$ 的模。

### 思路

给定的模数不一定是质数。所以逆元不可行。

这是 Div.3 C 题所以应该不需要一些高级的数学技巧。

考虑反向计算，预处理最后一个被删掉的数，然后逐步加入数并求模。即从后往前计算答案。

```cpp
// a[i] 值序列
// p[i] 操作序列
l = r = the_last_number_position; // 最后剩下的数的下标
prv = a[l];
for (int i = n - 1; i; --i)
{
	pos = (p[i] == 'L') ? --l : ++r;
	res[i] = prv * a[pos] % mod;
	prv = prv * a[pos] % mod;
}
```

### Tips

注意本题多测。

---

## 作者：eb0ycn (赞：0)

## 题意

给你一个长度为 $n$ 的数列 $a$ 和字符串 $s$，按顺序执行 $s$ 的操作：

- 当 $s_i=\texttt{L}$ 时，查询区间左端点右移一位；
- 当 $s_i=\texttt{R}$ 时，查询区间右端点左移一位。

初始时查询区间为 $[1,n]$，求每次操作之前查询区间内的所有数的乘积对 $m$ 取模的结果。

## 思路

不言而喻，一目了然。

$m$ 不一定是质数，所以快速幂逆元肯定不行。由于我太菜，不会大神们的“正难则反”，上来就满脑子线段树，所以我就献上线段树板子啦。时间复杂度 $O(n \log n)$，能过就行。

膜拜 $O(n)$ 大佬。

## 场上代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int t,n,qqql,qqqr,a[200001],s[800000],m;
char op[200002];
void build(int l,int r,int root){
	if(l==r){s[root]=a[l];return;}
	int mid=l+r>>1;
	build(l,mid,root<<1),build(mid+1,r,root<<1|1),s[root]=s[root<<1]*s[root<<1|1]%m;
}
int query(int l,int r,int root,int ql,int qr){
	if(ql<=l&&r<=qr)return s[root];
	int mid=l+r>>1,ret=1;
	if(mid>=ql)ret=ret*query(l,mid,root<<1,ql,qr)%m;
	if(mid<qr)ret=ret*query(mid+1,r,root<<1|1,ql,qr)%m;
	return ret;
}
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&n,&m);for(int i=1;i<=n;++i)scanf("%d",a+i),a[i]%=m;
		scanf("%s",op+1),build(1,n,1),qqql=1,qqqr=n;
		for(int i=1;i<=n;++i){
			printf("%d ",query(1,n,1,qqql,qqqr));
			if(op[i]=='L')++qqql;
			else --qqqr;
		}printf("\n");
	}
	return 0;
}
```


---

## 作者：I_will_AKIOI (赞：0)

题目大意：给定一个长度为 $n$ 的数组 $a$ 和字符串 $s$。接下来你进行 $n$ 次操作。

开始时 $l=1,r=n$，首先输出 $\displaystyle\prod \limits_{i=l}^ra_i \bmod m$，
接着若 $s_i=0$，则 $l\leftarrow l+1$，若 $s_i=1$，则 $r\leftarrow r-1$。

暴力枚举 $l\sim r$ 肯定是不行的，如果你聪明一点用逆元，但是积可能和 $m$ 不互质，是无解的。

我们发现序列的数量不断减少的，我们可以反过来，使序列长度不断增加。每次的结果可以由上一次的推出来。先按照操作求出 $l,r$，找到最后剩下的数，接下来再从最后的结果倒推。

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,m,a[200005],ans[200005];
char c[200005];
signed main()
{
  ios::sync_with_stdio(0);
  cin>>t;
  while(t--)
  {
	cin>>n>>m;
	int l=1,r=n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) cin>>c[i];
	for(int i=1;i<n;i++)
	{
	  if(c[i]=='L') l++;
	  else r--;
    }
    ans[n]=a[l]%m;//求出最后一次操作的值
    for(int i=n-1;i>=1;i--)
    {
      if(c[i]=='L') l--,ans[i]=ans[i+1]*a[l]%m;
      else r++,ans[i]=ans[i+1]*a[r]%m;//由结果倒推
	}
	for(int i=1;i<=n;i++) cout<<ans[i]<<" ";
	cout<<"\n";
  }
  return 0;
}
```

---

## 作者：No_Rest (赞：0)

## 思路

巧妙的倒推。~~考场上没想到然后暴力打线段树（~~

发现暴力显然超时，利用前缀和或正着做在除时会遇到麻烦，而当除数与模数不互质时又无法求出逆元。

考虑~~线段树~~倒着做。这时我们只用记录一个 $sum$，然后一点点乘回去并在答案数组里记录即可。

时间复杂度 $\mathcal O(Tn)$。

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll maxn = 2e5 + 5;
ll read(){
	char ch;
	ll f = 0, r = 0;
	ch = getchar();
	while(ch > '9' || ch < '0') f |= ch == '-', ch = getchar();
	while(ch <= '9' && ch >= '0') r = (r << 3) + (r << 1) + (ch ^ 48), ch = getchar();
	return f ? -r : r;
}
ll t = read(), n, m, sum, a[maxn], ans[maxn], l, r;
string s;
void solve(){
	n = read(), m = read(), l = 1, r = n;
	for(ll i = 1; i <= n; ++i) a[i] = read();
	cin >> s, s = ' ' + s;
	for(ll i = 1; i < n; ++i)
		if(s[i] == 'L') l++;
		else r--;
	ans[n] = sum = a[l] % m;
	for(ll i = n - 1; i; --i)
		if(s[i] == 'L') ans[i] = sum = sum * a[--l] % m;
		else ans[i] = sum = sum * a[++r] % m;
	for(ll i = 1; i <= n; ++i) printf("%lld ", ans[i]);
	putchar('\n');
}
int main(){	
	for(; t; --t) solve();
    return 0;
}
```

---

