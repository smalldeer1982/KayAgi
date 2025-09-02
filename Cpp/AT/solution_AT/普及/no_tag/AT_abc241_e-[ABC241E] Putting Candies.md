# [ABC241E] Putting Candies

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc241/tasks/abc241_e

给你一个长度为 $ N $ 的数列$A $， $ A=(A_0,A_1,\ldots,A_{N-1}) $。 
 最初是空盘，高桥君会执行$K $次以下操作。

- 设盘子里有$ X $ 颗糖。每次在盘中放入$ A_{(X\bmod\ N)} $ 颗糖。 $ X\bmod\ N $ 表示 $ X $ 除以 $ N $ 的余数。

求$K$次后盘子里糖的颗数。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\times\ 10^5 $
- $ 1\ \leq\ K\ \leq\ 10^{12} $
- $ 1\ \leq\ A_i\leq\ 10^6 $
- 输入都是整数

## 样例 #1

### 输入

```
5 3
2 1 6 3 1```

### 输出

```
11```

## 样例 #2

### 输入

```
10 1000000000000
260522 914575 436426 979445 648772 690081 933447 190629 703497 47202```

### 输出

```
826617499998784056```

# 题解

## 作者：如履薄冰 (赞：4)

# 题意
给你一个有 $n$ 个数的数列 $A$。你现在有一个空盘子，每次你都要往这个空盘子里放入 $A_g$ 颗糖。其中 $g$ 等于现在盘子里有的糖数除以 $n$ 所得到的余数，问执行 $k$ 次后盘子里的糖果数。
# 解法
## 初始化环节
我们先用一个变量 $first$ 维护第一次往盘子里放的糖果颗数，即 $A_0$。用变量 $cnt$ 维护一个周期里数的个数。
$cnt$ 初始为 $1$，因为 $first$ 已经是这个周期的第一项了。最后，我们用变量 $roundd$ 维护一个周期中所有数的和。
## 模拟环节
基本上照着题意做就行了，因此我只说一个较难点，就是如何算 $cnt$。每次模拟，我们都用一个变量维护这次该放入的糖果数。如果这个变量等于 $first$，则模拟结束。否则将 $cnt$ 加一，$roundd$ 加上这个变量。
## 鸽巢原理算答案
我们通过模拟算出一切数据之后，利用鸽巢原理变形公式算出答案并输出。此题结束。
# 代码
这是个好题，请大家自行写代码。
# 闲话
创作不易，希望管理员给我全站推荐，谢谢。

---

## 作者：Like_Amao (赞：2)

**前言**

[题目传送门](https://www.luogu.com.cn/problem/AT_abc241_e)

**题目大意**

有一个长度为 $N$ 的序列 $A$，$A$ 的下标从 0 开始，以及一个变量 $X$，初始时，$X$ 的值为 0，总共要执行 $K$ 此此操作：

* 将 $X$ 加上 $A _ {X \bmod N}$,其中 $X \bmod N$ 表示 $X$ 除以 $N$ 得到的余数。

**思路**

这是一道**周期问题**，我们可以先用暴力求出每一个周期的长度，然后用 $K$ 去除以这个周期的长度，再用每个周期里面的数字的和乘上周期的个数，然后加上不是周期的部分即可。

**注意事项**

要考虑 $K$ 不满一个周期的情况。

**代码**

谁说题解一定要有代码的？

---

## 作者：4041nofoundGeoge (赞：1)

## 思路

由于 $f^0(0),f^1(0),\dots,f^N(0)$ 为 $0$ 到 $n-1$ 之间所有整数，存在 $0\le k<k'\le N$ 使得 $f^k(0)=f^{k'}(0)$。在这里，我们取最小的 $t$，使存在 $0\le s<t$ 满足 $f^s(0)=f^t(0)$，并让 $p=t-s$，然后对于非负整数 $i$，$f^{t+i}(0)=f^i(f^t(0))= f^i(f^s(0))= f^{s+i}(0)$ 也就是说，对于任何满足 $k$ 的 $s≤k$，我们有 $f^{k+p}(0)=f^k(0)$，因此序列 ${f^i(0)}$ 在 $p$ 范围内具有周期性 $s≤i$。我们利用这个事实来找到答案。

对于 $K≤s$，我们有 $K≤s<t≤N$，因此可以天真地模拟糖果数量的转换。否则，对于小于 $p$ 的非负整数 $a$ 和 $b$，它可以表示为 $(K−1−s)=ap+b$ 。这里，对于非负整数 $i$，

$$
A_{f^{s+ip+b+1}(0)}+A_{f^{s+ip+b+2}(0)}+\dots+A_{f^{s+(i+1)p+b}(0)}=\sum^{t-1}_{i=s}A_{f^i(0)}
$$

通过定义 $X=\sum\limits^{t-1}_{i=s}A_{f^i}(0)$，可以得出 $\sum\limits^{K-1}_{i=0}A_{f^i}(0)=\sum\limits^{s+b+0p}_{i=0}A_{f^i}(0)+\sum\limits^{s+b+p}_{i=0}A_{f^i}(0)+\dots+\sum\limits^{s+b+(a-1)p}_{i=0}A_{f^i}(0)+\dots+A_{f^{s+ap+b}}(0)=(\sum\limits^{s+b}_{i=0}A_{f^i(0)})+aX$，其中 $\sum\limits^{s+b}_{i=0}A_{f^i(0)}$ 和 $X$ 均可在 $\{f^i(0)\}$ 的前 $N$ 项找到，故时间复杂度为 $O(N)$。

__记得开 long long。__

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
long long k;
long long A[200010];
long long S[200010];
int pre[200010];
int s, t, p, b;
long long a, X;
long long ans;
int main() {
	cin >> n >> k;
	for (int i = 0; i < n; i++)cin >> A[i];

	for (int i = 0; i < n; i++)pre[i] = -1;
	S[0] = 0;
	pre[0] = 0;

	for (int i = 0; i < n; i++) {
		S[i + 1] = S[i] + A[S[i] % n];
		if (pre[S[i + 1] % n] != -1) {
			s = pre[S[i + 1] % n];
			t = i + 1;
			break;
		}
		pre[S[i + 1] % n] = i + 1;
	}

	if (k <= s)ans = S[k];
	else {
		p = t - s;
		X = S[t] - S[s];
		a = (k - s - 1) / p;
		b = (k - s - 1) % p;
		ans = S[s + b + 1] + (a*X);
	}

	cout << ans << endl;
	return 0;
}
```

---

## 作者：guoxinda (赞：1)

## 思路
考虑构建抽屉。抽屉为 $0,1,2,\cdots,n-1$，一共 $n$ 个抽屉。\
根据抽屉原理，第 $n+1$ 次前一定会出现第一次周期并开始第二次周期，所以循环只需要进行 $\min(n+1,k)$ 次。\
由于 $A_0,A_1,A_2,\cdots,A_n$ 是有周期性的，我们只需要计算周期前的 $+$ 够周期的 $+$ 最后不够周期的。
## code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
map<int,int>ma;
int n,k,a[200010],b[200010],sum,l=1,r=1,s,c,NS;//sum用来记当前总和，l用来记左下标，r用来记右下标 
signed main(){	
	cin>>n>>k;
	for(int i=0;i<n;i++){//0~n-1
		cin>>a[i];
	}
	for(int i=1;i<=n;i++){
		if(ma[sum%n]!=0){//第二次周期开始 
			l=ma[sum%n];
			r=i-1;
			break;
		}else{
			ma[sum%n]=i;//记录余数第一次出现位置 
		}
		sum+=a[sum%n];
		b[i]=sum;
		if(i==k){//第k次，不用继续操作了 
			cout<<sum;
			return 0;
		}
	}
	s=k-l+1;//l~k
	c=s/(r-l+1)*(b[r]-b[l-1]);
	if(s%(r-l+1)!=0){
		c+=b[l+s%(r-l+1)-1];//l+s%(r-l+1)-1为剩下不够周期的
		c-=b[l-1];//减周期前的 
	}
	cout<<c+b[l-1];//b[l-1]是周期前的 
	return 0;
}
```

---

## 作者：CQ_Bob (赞：1)

## 分析

由于 $x \bmod n$ 的值只有 $n$ 个，所以在不超过 $n$ 次操作之后，必定会有长度不大于 $n$ 的循环周期。我们可以先找到这个周期，然后求出来 $k'$ 中周期数量，把周期里的和乘上周期数量再加上达不到一个周期的值的和即可。在这里，$k'$ 是 $k$ 减去第一个周期开始之前的非周期的数的数量。

注：要特别注意一下 $k$ 不满足一个周期的情况哦。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define PII pair<int,int>
#define x first
#define y second
const int N=1e6+10;
int n,k,a[N],b[N],idx,l,r,m;
int c[N],vis[N];
int ans;
void read(){
	cin>>n>>k;
	for(int i=0;i<n;i++)
		cin>>a[i];
}
void solve(){
	int now=0;
	while(1){//查找周期 
		int where=now%n;
		if(vis[where]){
			l=vis[where],r=idx;
			break;
		}
		vis[where]=++idx,b[idx]=where;
		now+=a[where];
	}
	if(k<=l){//没有一个周期 
		for(int i=1;i<=k;i++)
			ans+=a[b[i]];
		cout<<ans;
		return ;
	}
	int sum=0;
	for(int i=l;i<=r;i++)
		c[++m]=b[i],sum+=a[b[i]];
	for(int i=1;i<l;i++)
		ans+=a[b[i]];
	k=max(0LL,k-(l-1));
	int st=k/(r-l+1),md=k%(r-l+1);//st为周期数量,md为剩下不足一个周期的数量 
	ans+=st*sum;
	for(int i=1;i<=md;i++)
		ans+=a[c[i]];
	cout<<ans;return ; 
}
signed main(){
	read(),solve();return 0;
}
```


---

## 作者：OI_StarGod (赞：1)

首先我们知道，$x \bmod n < n$，也就是说，$x \bmod n$ 最终一定会形成一个不大于 $n$ 的循环。我们考虑先求出这个循环，然后再求出有几个循环，接着求出去掉所有循环后剩下的数的和，最终答案为循环大小 $\times$ 循环数量 $+$ 循环剩下的。最终时间复杂度 $O(n)$。

# AC CODE

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int unsigned long long
const int N = 2e7 + 5;
int n, k;
int a[N];
int vis[N];
int mod[N];
int op[N];
int sum = 0, cnt = 0;
int ans = 0;
signed main() {
	cin >> n >> k;
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
	}
	sum = a[0];
	cnt = 1;
	int l = 0, r = 0;
	while (1) { //求出循环节
		if (vis[sum % n]) { // 如果发现循环了
			l = vis[sum % n];
			r = cnt; // 记录循环开始的位置和循环结束的位置
			break; // 退出
		}
		++cnt;
		vis[sum % n] = cnt;
		mod[cnt] = sum % n;
		sum += a[sum % n];
	}
	if (k <= l) { // 注意有可能根本没有一个循环
		for (int i = 1; i <= k; ++i) {
			ans += a[mod[i]];
		}
		cout << ans;
		return 0;
	}
	cnt = 0;
	sum = 0;
	for (int i = l; i <= r; ++i) { // 一个循环的值
		op[++cnt] = mod[i];
		sum += a[mod[i]];
	}
	for (int i = 1; i < l; ++i) { // 循环前
		ans += a[mod[i]];
	}
	k -= l - 1;
	ans += k / (r - l + 1) * sum; // 循环
	for (int i = 1; i <= k % (r - l + 1); ++i) { // 循环后
		ans += a[op[i]];
	}
	cout << ans;
	return 0;
} 
```

---

## 作者：Tang_poetry_syndrome (赞：1)

## [ABC241E] Putting Candies
[洛谷题面](https://www.luogu.com.cn/problem/AT_abc241_e) [Atcoder 题面](https://atcoder.jp/contests/abc241/tasks/abc241_e)
### 题目大意
给你一个长度为 $N$ 的序列 $A=(A_0,A_1,\dots,A_N)$，最初是空盘，高桥会执行 $K$ 次操作。每次在盘中放入 $A_{(X\bmod N)}$ 颗糖。$X \bmod N$ 表示 $X$ 除以 $N$ 的余数。  
求 $K$ 次后盘子里糖的颗数。
### 思路
根据小奥的抽屉原理，变化将形成一个长度为 $X$ 的循环节。  
考虑用 $O(n)$ 的时间复杂度暴力查找循环节，用循环节处理整部分，剩下的部分额外维护。
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
int main() {
  int n;ll k;
  cin>>n>>k;
  vector<int> a(n);
  for(int i=0;i<n;i++) cin >> a[i];
  ll x = 0;
  map<int,int> mi;
  map<int,ll> mx;
  for(int i=0;i<k;i++) {
    int r=x%n;
    if(mi.count(r)) {
      int p=i-mi[r];
      if((k-i)%p==0) {
        x+=(x-mx[r])*((k-i)/p);
        break;
      }
    }
    mi[r]=i;mx[r]=x;
    x+=a[x%n];
  }
  cout<<x;
  return 0;
}
```
[提交记录](https://atcoder.jp/contests/abc241/submissions/45697611)

---

## 作者：Grace2022 (赞：0)

对为什么会产生循环产生疑问的同学可以看看这篇题解。
## 题目大意
题目链接：  
[[abc241] E - Putting Candies](https://atcoder.jp/contests/abc241/tasks/abc241_e)  
[[洛谷] AT_abc241_e [ABC241E] Putting Candies](https://www.luogu.com.cn/problem/AT_abc241_e)  
设糖果总数为 $X$，那么从 $X=0$ 开始执行 $K$ 次，每次对 $X$ 加上 $A_{X \bmod N}$，其中 $A$ 和 $N$ 均已在题中给出。  
## 思路分析
做这道题我们需要知道，在 $a$ 除以 $b$ 等于 $c$ 余 $d$ 中，一定有 $0 \le d \lt b$。也就是说，一定有 $0 \le X \bmod N \lt N$（$\bmod$ 即为取余或者取模运算）。所以 $x \bmod N$ 可能重复，当 $K \gt N$ 时一定重复，这就是其它题解所说的抽屉原理或者格巢原理。  

第一次重复时就会产生循环。为什么呢？请看以下解释，希望对您有所帮助。  

### 感性理解
当 $X \bmod N$ 重复时，$A_{X \bmod N}$ 就会重复，$(X + (A_{X \bmod N})) \bmod N$ 就会重复，就这么一直重复下去……这里您可能需要知道，$(a + b) \bmod c = ((a \bmod c) + (b \bmod c)) \bmod c$，这是取模的分配率，感兴趣的可以自行上网查阅。  
### 数学证明
叠甲：本人数学不好因此可能出现纰漏，如果出现请指出。  
#### 定义
设 $s_k$ 为第 $k$ 次操作后的总糖果数，$x_k = s_k \bmod N$。  
那么有 $s_k = s_{k-1} + A_{x_{k-1}}$，$x_k = (s_{k-1} + A_{x_{k-1}}) \bmod N$。  
#### 目标
证明存在 $i$ 和 $j(i \lt j)$ 且 $x_i=x_j$ 使得 $x_{i+1} = x_{j+1}$。
#### 证明
假设 $x_i = x_j$。
$$\because x_k = (s_{k-1} + A_{x_{k-1}}) \bmod N$$
$$\therefore x_{i+1} = (s_i + A_{x_i}) \bmod N$$
$$x_{j+1} = (s_j + A_{x_j}) \bmod N$$
$$\because x_i = x_j$$
$$\therefore x_{j+1} = (s_j + A_{x_i}) \bmod N$$
$$s_i \bmod N = s_j \bmod N$$
$$\therefore (s_j - s_i) \bmod N = 0$$
$$\therefore s_j = s_i + kN(k \in \mathbb{Z})$$
$$\therefore \begin{aligned} x_{j+1} &= (s_i + kN + A_{x_i}) \bmod N \\ &= (s_i+A_{x_i}) \bmod N \\ &= x_{i+1} \end{aligned}$$
$$\therefore x_{i+1} = x_{j+1}$$
证毕。
### 举个例子
假设 $N=3$，$A_0 = 1$，$A_1 = 2$，$A_2 = 3$。  
1. 第一次操作：$0 \bmod 3 = 0$，选择 $A_0$，拿到 1 颗糖果。此时总糖果数 $s_1 = 1$，$x_1 = 1$。
2. 第二次操作：$1 \bmod 3 = 1$，选择 $A_1$，拿到 2 颗糖果。此时总糖果数 $s_2 = 3$，$x_2 = 0$。
3. 第三次操作：$3 \bmod 3 = 0$，选择 $A_0$，拿到 1 颗糖果。此时总糖果数 $s_3 = 4$，$x_3 = 1$。
4. 第四次操作：$4 \bmod 3 = 1$，选择 $A_1$，拿到 2 颗糖果。此时总糖果数 $s_4 = 6$，$x_4 = 0$。

现在理解了吗？  
## 代码实现
请注意，循环节并不是从 1 开始的，还要注意细节加 1 减 1 的问题，最后不要忘了偏移，因为你的起点不是 1。这些您在实践中就能发现，希望您不要再踩我踩过的坑。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int a[200005],s[200005],mp[200005];
signed main(){
	int n,m,f=0;
	cin>>n>>m;
	for(int i=0;i<n;i++){
		cin>>a[i];
	}
	for(int i=0;i<n;i++){
		mp[i]=-1;//余数可能为0 
	}
	for(int i=1;i<=m;i++){
		s[i]=s[i-1]+a[s[i-1]%n];
		if(mp[s[i-1]%n]!=-1){
			f=i-1;
			break;
		}
		mp[s[i-1]%n]=i;
		//cout<<i<<endl;
	}
	if(f==0){
		cout<<s[m];
		return 0;
	}
	int q=mp[s[f]%n];
	cout<<s[q-1]+(s[f]-s[q-1])*((m-q+1)/(f-q+1))+(s[q-1+(m-q+1)%(f-q+1)]-s[q-1]);//循环不是从1开始，下标要注意偏移 
	return 0;
}
```

---

## 作者：lyh0217 (赞：0)

感觉评黄有点虚高了（？）

[题目传送门](https://www.luogu.com.cn/problem/AT_abc241_e)

### 题意

给定一个长度为 $n$ 的序列 $a$，有一个变量 $x$，初始为 $0$，之后每次变化为 $x+a_{(x\bmod n)}$，求 $x$ 变化了 $k$ 次之后的值。

### 思路

发现对于每个 $x$，下一次 $(x\bmod n)$ 是已知且固定的，就相当于一个 $n$ 个点 $n$ 条边的联通的有向图，发现只要有一个值重复出现了，就会形成一次循环，而循环长度是不大于 $n$ 的，所以可以求出循环，再求答案。

时间复杂度 $O(n)$。

#### 注意

$1\leq K\leq 10^{12}$，$1\leq A_i\leq 10^6$，记得开 ```long long```。

### code

```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[200005],fa[200005],p[200005];
bool vis[200005];
int main()
{
	long long n,k;
	cin>>n>>k;
	for(int i=0;i<n;i++) 
	{
		cin>>a[i];
		fa[i]=(a[i]+i)%n;//确定进行这一次变化后下一次的下标
	}
	int y=0,len=0;
	while(!vis[y])//求循环
	{
		p[++len]=y;
		vis[y]=1;
		y=fa[y];
	}
	int w=0;
	long long ans=0;
	for(int i=1;i<=len;i++)//去除不在循环中的部分，并统计答案
	{
		if(!k) break; 
		if(p[i]!=y)
		{
			ans+=a[p[i]];
			k--;
		}
		else
		{
			w=i;
			break;
		}
	}
	long long sum=0;
	for(int i=w;i<=len;i++)
	{
		sum+=a[p[i]];
	}
 //循环长度是len-w+1，整个循环的和是sum
	ans+=sum*(k/(len-w+1));
	k%=(len-w+1);
	for(int i=w;i<=len;i++)
	{
		if(!k) break;
		ans+=a[p[i]];
		k--;
	}
	cout<<ans;
	return 0;
}
```

[评测记录](https://atcoder.jp/contests/abc241/submissions/61941760)

---

## 作者：Miracle_1024 (赞：0)

## 题目大意
给你一个长度为 $N$ 的 $A$ 序列。
有一个空盘子。每次会在其中加入 $A_{X \bmod N}$ 颗糖果。（$X$ 代表盘子中糖果的数量）。

## 解题思路
就是小学数学的鸽巢原理。$A_{X \bmod N}$ 在 $N$ 次后必定出现周期，所以这道题就是一道简单的周期问题。

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=2e5+10;
const int INF=0x3f3f3f3f;
inline int read(){ll x=0,f=1;char ch=getchar();while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}return x*f;}
ll n,k,a[N],ans[N],cnt[N],t,sum; 
int main(){
	cin>>n>>k;
	for(int i=0;i<n;i++)cin>>a[i];
	memset(cnt,-1,sizeof cnt);
	cnt[0]=0;
	for(int i=0;i<n;i++){
		ans[i+1]=ans[i]+a[ans[i]%n];
		if(cnt[ans[i+1]%n]!=-1){
			sum=cnt[ans[i+1]%n];
			t=i+1;
			break;
		}
		cnt[ans[i+1]%n]=i+1;
	}
	if(k<=sum)cout<<ans[k]<<endl;
	else{
		ll MOD=t-sum,x=ans[t]-ans[sum],t=k-sum-1;
		cout<<ans[sum+t%MOD+1]+t/MOD*x<<endl;
	}
}


```

---

## 作者：Scean_Tong (赞：0)

## STL大法好

可以看出，盘子里的糖果数量是循环变化的。如果在某一步操作后，盘子里的糖果数量与之前出现过的某一个状态相同，那么说明在这一步之后，盘子里的糖果数量会形成一个循环。


如果余数已经出现过，说明我们找到了一个循环，计算循环的长度 `p = 当前操作次数 - 第一次出现该余数的操作次数`。

如果循环的长度整除剩余需要执行的次数，那么剩余次数直接跳过即可。

如果没有找到循环，则记录当前状态，更新 `x` 的值为当前状态下应该增加的糖果数量。

最后，输出最终的盘子里糖果数量 `x` 即为答案。

用两个 `map` 随便记一下状态应该不难吧。
```cpp
#include<bits/stdc++.h>
#define int long long
#define PII pair<int,int>
#define VI vector<int>
#define pb push_back
#define endl '\n'
#define inf 0x3f3f3f3f
#define mp(i,j) make_pair(i,j)
#define fi first
#define se second
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define repp(i,a,b) for(int i=a;i<b;i++)
#define il inline
#define per(i,a,b) for(int i=a;i>=b;i--)
using namespace std;
namespace IO{
	template<typename T> inline void read(T &x){
		bool f=1;x=0;char ch=getchar();
		while(ch<'0'||ch>'9'){if(ch=='-')f=0;ch=getchar();}
		while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch&15),ch=getchar();
		x=f?x:-x;
	}
	template<typename T> inline void write(T x){
		if(x<0) putchar('-'),x=-x;
	   	if(x>9) write(x/10);
	   	putchar(('0'+x%10));
	}
	template <typename T,typename ...Args> inline
	void read(T &x,Args &...args){read(x);read(args...);}
	template<typename T> inline void write(T x,char c){write(x),putchar(c);}
}
using namespace IO;
const int maxn=2e5+7;
signed main() {
    int n;
    int k;
    read(n,k);
    int a[maxn];
    for (int i=0;i<n;i++){
        read(a[i]);
    }
    int x=0;
    map<int, int> m1;
    map<int, int> m2;
    for (int i=0;i<k;i++){
        int r=x%n;
        if (m1.count(r)){
            int p=i-m1[r];
            if((k-i)%p==0){
                x+=(x-m2[r])*((k-i)/p);
                break;
            }
        }
        m1[r]=i;
        m2[r]=x;
        x+=a[r];
    }
    write(x,'\n');
    return 0;
}


```

---

## 作者：_qingshu_ (赞：0)

# 题意：

翻译给的挺清楚了，就不多赘述了。

# 思路：

看到模数，想到抽屉原理，考虑将所有的模后的 $X$ 列出来，查找循环节，循环节在前 $N$ 个中（最开始空盘有一个 $0$）。

处理完后记录循环节开始的前一个为 $st$，长度为 $len$。考虑分类讨论：

- 当 $k\le N$ 时：

	显而易见的，答案是 $X_k$。
    
- 当 $k > N$ 时：

	答案应为 循环节总贡献和 $\times$ 经历循环节个数 $+$ 从头开始到当前点的贡献。更替为数学公式为 $k\div len \times (X_{st+len}-X_{st})+X_{st+(k\mod len)}$。
    
总时间复杂度 $\mathcal{O}(n)$。

# Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long ck[5200010];
long long n,k,a[5200010],st,len;
bool flag=0;
map<long long,long long>check;
int main(){
    cin>>n>>k;
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    check[0]=INT_MAX;
    for(int i=1;i<=n;i++){
        ck[i]=ck[i-1]+a[ck[i-1]%n];
        if(check[ck[i]%n]&&!flag){
            if(check[ck[i]%n]==INT_MAX)check[ck[i]%n]=0;
            st=check[ck[i]%n];
            len=i-st;
            flag=1;
        }
        check[ck[i]%n]=i;
    }
    if(k<=n){
        cout<<ck[k]<<endl;
    }
    else{
        k-=st;
        cout<<ck[st+k%len]+k/len*(ck[st+len]-ck[st])<<endl;
    }
}
```

---

## 作者：Mingrui_Yang (赞：0)

## 题意

给你一个长度为 $N$ 的数列 $A$，$A=(A_0,A_1,\ldots,A_{N-1}) $。最初是空盘，高桥君会执行 $K$ 次以下操作。

- 设盘子里有 $X$ 颗糖。每次在盘中放入 $A_{(X\bmod N)}$ 颗糖。$X\bmod N$ 表示 $X$ 除以 $N$ 的余数。

求 $K$ 次后盘子里糖的颗数。

## 思路

> 遇到模，有很大的可能出现循环。   

观察数据范围 $2\leq N \leq 2\times 10^5 , 1 \leq K \leq 10^{12}$，操作次数 $K$ 比数列大小 $N$ 更大。所以一定会出现循环。

这是一个混循环，首先找到开始循环的位置，将中间的循环部分处理掉，最后会剩下一些小尾数，单独处理。

## CODE

```cpp
#include <bits/stdc++.h>
#define int long long  // 数据范围是longlong 
using namespace std;
const int N = 2e5 + 10;
int n, k;
int a[N];
int vis[N], book[N]; // vis标记和，book标记步数 
int num; // 存答案 
signed main() {
	cin >> n >> k;
	for (int i = 0; i < n; i ++ ) cin >> a[i];
	memset(vis, -1, sizeof vis);
	book[0] = 1;
	int sum, id, last = -1, len = 0;
	while (len < k) {
		if (vis[num % n] != -1) { // 已经被算过，说明这里是循环起点 
			sum = num - vis[num % n]; // 循环部分的和 
			id = num % n; // 记录循环起点 
			break;
		}
		else {
			if (num != 0) book[num % n] = book[last] + 1;
			last = num % n;
			vis[last] = num;
			num += a[last];
			len ++ ;
		}
	}
	if (len == k) { // 不存在中间循环部分 
		cout << num << endl;
		return 0;
	}
	num += (k - len) / (len - book[id] + 1) * sum; // len - book[id] + 1为循环长度   sum为循环部分的和 
	len += (k - len) / (len - book[id] + 1) * (len - book[id] + 1); // 长度也要增加 
	while (len < k) { // 处理小尾数 
		num += a[num % n];
		len ++ ;
	}
	cout << num << endl;
	return 0;
}
```

---

## 作者：Demons_Killer (赞：0)

# 思路：
本体就是一道很简单的周期问题，每次得到的余数出现了相同的情况，就成为了一个周期，可以先把周期给求出来，再用 $k$ 除以周期长度，用周期乘上这个数，加上剩余的周期以外的情况，就求出了最后的答案。注意要特判一下 $k$ 不满一个周期的情况。

# code：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
int n,k;
int a[N],b[N];
bool vis[N];
int ans,djd,L;
vector<int> q;
signed main(){
	cin>>n>>k;
	for(int i=0;i<n;i++) {
		cin>>a[i];
	}
	int cnt=0;
	while(true){
		//cout<<cnt<<endl;
		vis[cnt]=true;
		q.push_back(cnt);
		cnt=(cnt+a[cnt])%n;
		if(vis[cnt]){
			djd=cnt;
			break;
		}
	}
	int t=0;
	bool f=false;
	for(int i=0;i<q.size();i++){
		ans+=a[q[i]];
		if(q[i]==djd){
			f=true;
		}
		if(f){
			L++;
			t+=a[q[i]];
			//cout<<q[i]<<endl;
		}
		//cout<<q[i]<<endl;
	}
	int len=q.size();
	if(k>=len){
		k-=len;
	}
	else{
		ans=0;
		for(int i=0;i<k;i++){
			ans+=a[q[i]];
		}
		cout<<ans;
		return 0;
	}
	int s=k%L,b=k/L;
	//cout<<L<<" "<<len<<" "<<ans<<" "<<b<<" "<<s<<endl;
	t*=b;
	ans+=t;
	f=false;
	int arr=1;
	for(int i=0;i<q.size()&&arr<=s;i++){
		if(q[i]==djd) f=true;
		if(f) ans+=a[q[i]],arr++;
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：loser_seele (赞：0)

官方题解不是给人看的，给一个人话题解。

不难观察到 $ X \bmod N $ 只有最多 $ N $ 种不同的取值，所以数列显然有一个最多 $ N $ 项的周期。

于是暴力求出一个周期后，答案分为三段：周期前的部分，周期，一个周期的零散不分。前两段显然是最差 $ N $ 个数，周期可以暴力算出来之后直接用周期和乘上周期数即可。

显然总时间复杂度 $ \mathcal{O}(N) $，可以通过。

代码：

```cpp
#import <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main()
{
	ll n, k;
	cin>>n>>k;
	vector<ll> a(n);
	for(int i = 0; i < n; i++)
	cin>>a[i];
	map<ll, ll> mp;	
	vector<ll> dp(n);
	ll ans = 0;
	int cur = 0;
	for(ll i = 0; i < k; i++)
	{
		if(mp[ans % n] != 0)
		{
			dp[i] = dp[i-1] + a[ans % n];
			int lo = mp[ans % n];
			ans = (dp[i] - dp[lo - 1])*((k - lo) / (i - lo + 1)) + dp[(k - lo) % (i - lo + 1) + lo - 1];
			break;
		}
		mp[ans % n] = i + 1;
		ans += a[ans % n];
		dp[i] = ans;
	}
	cout<<ans;
}
```


---

## 作者：rzm120412 (赞：0)

题意给的很清楚，不在赘述。

### 暴力思路：

跑一遍 $k$ 强行模拟。

注意到 $ 1\ \leq\ K\ \leq\ 10^{12} $。显然超时。

### 正解：

数据很大所以多半是个周期问题。不难发现当一个数字出现两遍时就出现周期了，所以把周期找到后，这题就很简单了。

### 代码：


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int unsigned long long
int n,k;
vector<int> a;
map<int,int> ma,mb;
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		int x;
		cin>>x;
		a.push_back(x);
	}
	int x=0;
	for(int i=0;i<k;i++){
		int r=x%n;
		if(ma.count(r)>0){
			int p=i-ma[r];
			if((k-i)%p==0){
				x+=(x-mb[r])*((k-i)/p);
				break;
			}
		}
		ma[r]=i;
		mb[r]=x;
		x+=a[r];
	}
	cout<<x;
	return 0;
}
```

---

