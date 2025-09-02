# Primes on Interval

## 题目描述

【题面】

你决定用素数定理来做一个调查. 众所周知, 素数又被称为质数，其含义就是除了数字一和本身之外不能被其他任何的数字除尽.

现在给定一个正整数序列 $a,a+1,\cdots,b$ $(a \le b)$, 请找出一个最小值 $l$, 使其满足对于任意一个长度为 $l$ 的子串, 都包含 $k$ 个质数.

找到并输出符合要求的最小值 $l$, 如果不存在符合要求的长度 $l$, 则输出 $-1$.

## 样例 #1

### 输入

```
2 4 2
```

### 输出

```
3
```

## 样例 #2

### 输入

```
6 13 1
```

### 输出

```
4
```

## 样例 #3

### 输入

```
1 4 3
```

### 输出

```
-1
```

# 题解

## 作者：灵光一闪 (赞：9)

这题其实最优复杂度不是O（nlogn），而是O（n）

这题看起来很难，其实我们要整理一下，你就会觉得肥肠简单
( •̀ ω •́ )

编一段对话哈：
```
出题人：现在给定一个正整数序列[a,b]请找出一个最小值 l,
使其满足对于任意一个长度为 l 的子串,
都至少包含 k 个质数.

你：什么？找最大值l，
让一个长度为l的在[a,b]区间的至少有k-1个质数……

出题人：不对！
是现在给定一个正整数序列[a,b]请找出一个最小值 l,
使其满足对于任意一个长度为 l 的子串,
都至少包含 k 个质数.

你：我还没说完呢！answer=l+1;

出题人：………………
******系统消息：出题人的std被爆踩了******
```

对鸭！要找包含至少k个质数的最短的区间比较难，但是找`包含至少k-1个质数的最长的区间`用queue就轻而易举了！然后这个区间两端都是质数所以再加一一定能包含至少k个质数。

```
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<cstdio>

#include<queue>
using namespace std;
bool prime[1000000+233];//素数
int main(){
	for(int i=0;i<1000010;i++){
		if(2<=i){
			prime[i]=true;
		}
	}
	for(int i=2;i*i<=1000500;i++){
		if(!prime[i]){
			continue;
		}
		for(int j=i*i;j<1000500;j+=i){
			prime[j]=false;
		}
	}//上面全是初始化，可以换成其他的（但是别一个个判断，那就TLE了!）筛法
	int a,b,k;
	cin>>a>>b>>k;
	queue<int> q;//队列
	int res=-1;
	q.push(a-1);
	for(int pos=a;pos<=b;pos++){
		if(prime[pos]){//这个队列只压素数
			q.push(pos);
		}
		while(k<q.size()){
			q.pop();
		}
		if(q.size()==k){//每等于一下就记录一下
			res=max(res,pos-q.front()+1);
		}
	}
	if(q.front()==a-1){//如果最前面的那个a-1没有被弹掉就说明没有任何一个符合要求的awa
		puts("-1");
	}
	else{//不然就输出最大值鸭awa
		cout<<res<<endl;
	}
	return 0;
}
```

## 因为这个算法每个数最多只进去过一次，所以是O(n)的( •̀ ω •́ )

The End.

---

## 作者：fjy666 (赞：3)

本题前置算法：**二分**+**线性筛**+**前缀和**  
不会线性筛的可以用普通筛法哦~  

------------
题目大意  
让你找出**最小**的`len`  
使得$a \sim b$中**每一个**长度为`len`的**子串**  
都有**至少**`k`个质数

------------
思路
1. 我们可以先用线性筛来选出$[a,b]$中的每一个质数  
2. 再用前缀和`sum`将它们**累加**起来
3. 最后用二分查找来找出最小的`len`值  
注意点：二分查找的范围是$[1,b-a+1]$

------------
Code:
```cpp
#include <bits/stdc++.h>
using namespace std;
bool pri[1000001];
int sum[1000001]; 
int ans[500001],len;
void InitPrime(int n)
{
	//欧拉筛 
	for(int i=2;i<=n;++i)
	{
		if(!pri[i])ans[++len]=i;
		for(int j=1;((i*ans[j])<=n)&&(j<=len);++j)
		{
			pri[i*ans[j]]=true;
			if(i%ans[j]==0)break;
		}	
	}
	//前缀和
	for(int i=2;i<=n;++i)
	{
		if(!pri[i])sum[i]=sum[i-1]+1;
		else sum[i]=sum[i-1];
	} 
}
int main()
{
	int a,b,k;
	scanf("%d%d%d",&a,&b,&k);
	InitPrime(b);
	const int MaxLength=b-a+1;
	int L=1,R=MaxLength;
	while(L<=R)
	{
		int i=(L+R)>>1;
		bool flag=true;
		for(int j=a;j<=b-i+1;++j)
		{
			if((sum[j+i-1]-sum[j-1])<k)
			{
				flag=false;
				break;
			}
		}
		if(!flag)L=i+1;
		else R=i-1;
	}
	if(L>MaxLength)printf("-1");
    //如果左区间比最大区间还大
    //就表明无解，所以输出-1
	else printf("%d",L);
	return 0;
}
```


---

## 作者：ForgetOIDuck (赞：2)

#### 思路：
考虑到素数的位置不会变，所以每两个素数之间相对位置也不变。

所以当某个数 $x(a\le x\le b)$ 作为左端点时，只需要找一个右端点使得 $l-r$ 中素数个数为 $k$。

可以通过前缀和维护，这东西是 $O(n)$ 的。

举个例子：

```1 7 3```

![](https://cdn.luogu.com.cn/upload/image_hosting/8vgqpcbr.png?x-oss-process=image)

图中打钩表示素数，箭头表示之后第一个能使区间中素数个数为 $k$ 的位置。

可以发现答案是 $5$，可以由 $1$ 或 $3$ 作为左端点时得来。

然而有时候会出现某种奇怪情况，举个例子：

```1 10 3```

![](https://cdn.luogu.com.cn/upload/image_hosting/iagmppcy.png?x-oss-process=image)

明显根据我们刚刚的做法答案还是 $5$，可 $6$ 作为左端点时就满足不了这个条件。

这是因为范围从 $7$ 加到 $10$，长度的增加使得 $6$ 可以成为一个长度为 $5$ 的区间的左端点，但是增加的 $8-10$ 部分没有素数所以无法满足。

为了防止这种情况，我们考虑再枚举右端点反向地来找左端点。这样就会把那些右边没有素数的地方也算进答案。

~~感性理解一下吧，不会正常的证明（逃~~

#### AC 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a, b, nb, k, l, s[1000002], p = 1, ans;
bool pr[1000002];
vector<int> pri;
int main() {
	cin >> a >> b >> k;
	for (int i = 2; i <= b; i ++ ) {
		if (! pr[i]) pri.push_back(i);
		for (int j = 0; j < pri.size() && i * pri[j] <= b; j ++ ) {
			pr[i * pri[j]] = 1;
			if (i % pri[j] == 0) break;
		}
		s[i] = s[i - 1] + 1 - pr[i];
	}  
	//for (int i = a; i <= b; i ++ ) cout << s[i] << ' ';
	if (s[b] - s[a - 1] < k) return puts("-1"), 0;
	for (int l = a, r = a; l <= b && r <= b; l ++ ) {
		while (s[r] - s[l - 1] < k && r <= b) r ++;
		ans = max(ans, r - l + 1);
	}
	for (int l = b, r = b; l >= a && r >= a; r -- ) {
		while (s[r] - s[l - 1] < k && l >= a) l --;
		ans = max(ans, r - l + 1);
	}
	cout << ans;
}
```

---

## 作者：ZMQ_Ink6556 (赞：2)

## CF237C Primes on Interval 题解
### 解题思路
这道题，我们可以先想最暴力的方法，枚举每一段的距离，打擂台统计答案，复杂度 $O((b-a)^2k)$。明显过不了。
#### 优化：
**二分**答案，找 $l$，复杂度 $O((b-a)^2\log k)$。
#### 再次优化：
**前缀和**记录质数出现次数，复杂度 $O((b-a)\log k+(b-a)\log(b-a))$。
### 参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a , b , k , q[1000005] , l , r , mid , ans;
bool p[1000005] = {1 , 1 , 0};
bool check(int t)
{
	for(int i = a + t - 1 ; i <= b ; i++)
	{
		if(q[i] - q[i - t] < k)
		{
			return 0;
		}
	}
	return 1;
}
int main()
{
	ios::sync_with_stdio(0);
	ios_base::sync_with_stdio(0);
	cin >> a >> b >> k;
	for(int i = 2 ; i <= b + 1 ; i++)
	{
		for(int j = i + i ; j <= b + 1 ; j += i)
		{
			p[j] = 1;
		}
	}
	for(int i = 1 ; i <= b + 1 ; i++)
	{
		q[i] = q[i - 1];
		if(!p[i])
		{
			q[i]++;
		}
	}
	if(q[b] - q[a - 1] < k)
	{
		cout << -1;
		return 0;
	}
	l = 1;
	r = b - a + 1;
	while(l <= r)
	{
		mid = (l + r) / 2;
		if(check(mid))
		{
			ans = mid;
			r = mid - 1;
		}
		else
		{
			l = mid + 1;
		}
	}
	cout << ans << endl;
	return 0;
}
```

---

## 作者：hongshixiaobai (赞：1)

# CF237C Primes on Interval 题解
[传送门](https://www.luogu.com.cn/problem/CF237C)
## 思路
显而易见，区间内质数数量具有单调性，考虑二分。

于是又想到预处理出 $[a,b]$ 中所有的质数，用前缀和 $O(1)$ 查询每一个长度为 $l$ 的区间中有多少个质数，枚举所有长度为 $l$ 的区间复杂度为 $O(n)$ 则总复杂度为 $O(n\log n)$。
## AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int i,j,a,b,l,ans = -1,r,k,m,cnt,p[1000006],v[1000006],mid,pre[1000006];
bool vis[1000006];
void get_p(int n)
{
	for(i = 2;i<=n;i++)
	{
		if(v[i] == 0)
		{
			v[i] = i;
			p[++m] = i;
			vis[i] = 1;
		}
		for(j = 1;j<=m;j++)
		{
			if(p[j]>v[i]||p[j]*i>n)break;
			v[i*p[j]] = p[j];
		}
	}
}
bool check(int x)
{
	for(i = a;i<=b-x+1;i++)
	{
		if(pre[i+x-1]-pre[i-1]<k)return 0;
	}
	return 1;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
	cin>>a>>b>>k;
	get_p(b);
	for(i = a;i<=b;i++)
	{
		pre[i] = pre[i-1];
		if(vis[i]) pre[i]++;
	}
	l = 1,r = b-a+1;
	while(l<=r)
	{
		mid = l+r>>1;
		if(check(mid))
		{
			ans = mid;
			r = mid-1;
		}
		else l = mid+1;
	}
	cout<<ans;
}
```

---

## 作者：SpringFullGarden (赞：1)

## 题意

在 $a, a + 1, \cdots, b$ 中求最小的 $x$ 满足任意一个长度为 $x$ 的子串都含有 $k$ 个质数。

## 思路

线性筛，前缀和，双指针。

线性筛（[P3383 【模板】线性筛素数](https://www.luogu.com.cn/problem/P3383)）求出质数。

前缀和储存每个数前（包括这个数）的质数个数。

当 $[a,b]$ 中没有 $k$ 个质数时无解。

双指针：

-   当 $[l, r]$ 中有 $k$ 个质数时，$l \gets l + 1$，$ans \gets \max(ans, r - l + 1)$。

-   当 $[l, r]$ 中没有 $k$ 个质数时，$r \gets r + 1$。

-   注：$[l,b]$ 之间也要有 $k$ 个质数，所以当 $[l, b]$ 中没有 $k$ 个质数时，$l\gets l - 1$。

时间复杂度 $O(n)$。

## 代码

```cpp
int p[1000006], vis[1000006], pre[1000006], tot;

signed main() {
	int a = rd(), b = rd(), k = rd();
	for(int i = 2; i <= b; i++) {
		pre[i] = pre[i - 1] + !vis[i];
		if(!vis[i]) p[++tot] = i;
		for(int j = 1; j <= tot; j++) {
			if(i * p[j] > b) break;
			vis[i * p[j]] = 1;
			if(i % p[j] == 0) break;
		}
	}
	if(pre[b] - pre[a - 1] < k) return puts("-1"), 0;
	int l = a, r = a, ans = 0;
	while(r <= b) {
		if(r < b) {
			if(pre[r] - pre[l - 1] >= k) ans = max(ans, r - l + 1), l++;
			else r++;
		}
		else {
			if(pre[r] - pre[l - 1] >= k) ans = max(ans, r - l + 1), r++;
			else l--;
		}
	}
	cout << ans;
	return 0;
}
```

---

## 作者：Fantasy_Segment_Tree (赞：1)

看到巨佬们到处线性做法，蒟蒻只会二分啊……

我们发现答案具有单调性，因为一个区间包含 $x + 1$ 个质数肯定包含 $x$ 个质数嘛！

所以想到二分 $l$。

首先筛出 $[1, b]$ 区间内的所有质数，但是这样我们仍然无法 $O(1)$ 地求出任意区间内的质数个数。

你想到了什么？对了，前缀和！

观察到 $b \leq 10^6$，首先建立 $prime$ 数组，$prime_i$ 代表 $i$ 是否是质数，是为 $1$，否为 $0$，然后开一个数组 $S$，$S_i$ 代表区间 $[1, i]$ 内的质数个数，即 $prime_1 + prime_2 + \cdots + prime_i$，这样就可以解决这个问题了。

不可行判断：如果$[1, b]$ 区间内质数个数都小于 $k$，那么肯定无法达到目标。

二分具体过程：设当前二分到的值为 $x$，则枚举长度为 $x$ 的区间，求出区间内的质数个数 $S_{u+x-1} - S_{u}(a \leq u \leq b - x + 1)$，如果所有区间的质数个数都大于等于 $k$，说明可行，把二分右端点设为 $x$，否则把二分左端点设为 $x + 1$。

输出一下，就结束了。

时间复杂度：$O(n \log n)$

代码如下。

```cpp
#include <iostream>
using namespace std;

int a, b, s, S[2000005], prime[2000005], lb[1000005], cnt;

bool check(int x) {
	for(int r = a; r <= b; r++) {
		if(r - x + 1 < a) continue;
		if(S[r] - S[r - x] < s) return 0;
	}
	return 1;
}

int main() {
	cin >> a >> b >> s;
	for(int i = 2; i <= b; i++) {
		if(!prime[i]) {
			lb[++cnt] = i;
		}
		for(int j = 1; i * lb[j] <= 1000000 && j <= cnt; j++) {
			prime[i * lb[j]] = 1;
		}
	}
	prime[1] = 1;
	for(int i = 1; i <= 1000000; i++) {
		prime[i] = prime[i] == 1 ? 0 : 1;
		S[i] = S[i - 1] + prime[i];
	}
	if(S[b] - S[a - 1] < s) {
		cout << -1;
		return 0;
	}
	int l = 1, r = 1000000;
	while(l < r) {
		int mid = (l + r) >> 1;
		if(check(mid)) r = mid;
		else l = mid + 1;
	}
	cout << l;
}
```

P.S. 由于这题的数据范围只有 $10^6$，所以埃氏筛/线性筛/我的奇葩筛法都可以过。

---

## 作者：Imiya (赞：1)

很显然答案符合比我大的不优，比我小的不行这一性质，所以我们想到二分答案。
#### 实现
`bool check(len)`表示每一个长度为 $len$ 的子区间中是否都有大于等于 $k$ 个质数，那么我们先用欧拉筛或线性筛求出每个数是否是质数，然后用尺取法即可在 $\mathcal{O}(n)$ 的时间内求出每一个长度为 $n$ 的子区间内的质数数量。那么总时间复杂度就是 $\mathcal{O}(n\times \log n)$。
#### 代码
```cpp
#include<iostream>
using namespace std;
int a,b,k;
bool prime[1000001];
void get_prime(){
    prime[1]=true;
    for(int i=2;i<=b;i++){
        if(prime[i])continue;
        for(int j=2;j*i<=b;j++)prime[i*j]=true;
    }
}
bool check(int len){
    int l=a,sum=0;
    for(int i=a;i<=b;i++){
        sum+=!prime[i];
        if(i-l>=len)sum-=!prime[l],l++;
        if(i-l+1==len&&sum<k)return false;
    }
    return true;
}
int bin_search(int l,int r){
    while(l<r){
        int mid=(l+r)>>1;
        if(check(mid))r=mid;
        else l=mid+1;
    }
    return l;
}
int main(){
//    freopen("read.in","r",stdin);
    cin>>a>>b>>k;
    get_prime();
    if(!check(b-a+1)){
        cout<<-1;
        return 0;
    }
    cout<<bin_search(1,b-a+1);
    return 0;
}
```

---

## 作者：weihaozhen2010 (赞：0)

# 题意：

[CF237C](https://www.luogu.com.cn/problem/CF237C)

#  思路：

- 题目中的区间长度具有单调性，因此可以采用二分答案。并使用欧拉筛，筛选出 $a$ 到 $b$ 的所有质数；再用前缀和进行优化，方便查找区间内的质数个数。

- 二分答案时，确定了区间的长度 $len$ 后，遍历下标 $a$ 到 $b-len+1$ 的每一个点，作为左端点，记为 $i$，再计算出右端点为 $i+len-1$。并用前缀和查询左端点到右端点的所有质数个数。只有遍历了所有的左端点，并且他们都大于或等于 $k$，这时才是一个符合的长度 $len$。最后用 $ans$ 打擂台求出最小值即可。



# 参考代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=1e6+5;
int a,b,k,m=0,ans=1e9+7;
int v[N],prime[N],f[N],sum[N];
void primes(int n)
{
	for(int i=2;i<=n;i++)
	{
		if(v[i]==0) 
		{
			v[i]=i;
			prime[++m]=i;	
		}	
		for(int j=1;j<=m;j++)
		{
			if(prime[j]>v[i]||prime[j]*i>n) break;
			v[i*prime[j]]=prime[j];
		}
	}
} 
bool check(int x)
{
	bool flag=1;
	for(int i=a;i<=b-x+1;i++)
	{
		if(sum[i+x-1]-sum[i-1]<k) flag=0;
	}
	if(flag==1) return true;
	else return false;
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>a>>b>>k;
	primes(b);
	for(int i=1;i<=m;i++) f[prime[i]]=1;
	for(int i=a;i<=b;i++) sum[i]=sum[i-1]+f[i];
	int l=1,r=b-a+1;
	while(l<=r)
	{
		int mid=(l+r)/2;
		if(check(mid))
		{
			ans=min(ans,mid);
			r=mid-1;
		}
		else
		{
			l=mid+1;
		}
	}
	if(ans==1e9+7) cout<<"-1";
	else cout<<ans;
	return 0;
}
```

---

## 作者：complete_binary_tree (赞：0)

[原题传送门](https://www.luogu.com.cn/problem/CF237C)

看到这题，一开始还没什么思路。

一看数据范围：$n\le10^6$，发现 $O(n\log n)$ 甚至都能过。

然后就想到了二分。

## 1.二分解法

首先，筛出 $[a-1,b]$（即 $[1,b]$）中所有的质数，把他们标记为 $1$，否则把它们标记为 $0$。

然后，对它求前缀和，设为数组 $pre$。那么第 $l$ 到 $r$ 个数中质数的个数就是 $pre_r-pre_{l-1}$。

接着，我们二分长度 $mid$，写一个 $check$：枚举右端点 $r$ 从 $n+mid-1$ 到 $m$，那么左端点就是 $l=r-mid+1$。用上述的方法求 $l$ 到 $r$ 之间的质数个数，然后判断，若大于 $k$ 说明合法。

最后，每次合法的时候都让 $ans=mid$，则 $ans$ 为最终答案。

记得特判不存在的时候，要输出 $-1$！

时间复杂度：$O(n\log n)$，代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;

vector<int> pr;
bool isp[N];
int pre[N];

int n, m, k;

void sss(int n){
	memset(isp, 1, sizeof isp); //赋初值
	isp[1] = 0;
	for(int i = 2; i <= n; ++i){
		if(isp[i]) pr.push_back(i); //是质数
		for(int j = 0; j < pr.size(); ++j){
			if(1ll * i * pr[j] > n) break; //大于 n 就退出
			isp[i * pr[j]] = 0; //这些都是合数
			if(!(i % pr[j])) break;
		}
	}
	for(int i = 1; i <= n; ++i) pre[i] = pre[i - 1] + isp[i];
	return ;
}

bool check(int len){
	int i = n + len - 1;
	for(; i <= m; ++i){
		if(pre[i] - pre[i - len] < k) return 0;
	}
	return 1;
}

int bs(){
	int l = 0, r = m - n + 1, mid, ans = 0;
	while(l <= r){
		mid = (l + r) >> 1;
		if(check(mid))
			r = mid - 1, ans = mid;
		else
			l = mid + 1;
	}
	return ans;
}

int main(){
	scanf("%d%d%d", &n, &m, &k);
	sss(m + 1);
	if(pre[m] - pre[n - 1] < k){
		printf("-1");
		return 0;
	}
	printf("%d", bs());
	return 0;
}
```

## 2.线性解法

然后，机房大佬看了我的代码，说：这题可以 $O(n)$ 做啊，为什么要 $O(n\log n)$？

然后他跟我讲了一通，具体是：

- 首先，这个问题可以转化为 **求最长的 $l$，使 $[a,b]$ 中长度为 $l$ 的子串至少有 $k-1$ 个质数**，最后 $l+1$ 就是答案。

- 那么，我们就可以维护 $r$ 和 $l$，让 $r$ 不断增加，此时如果 $[l,r]$ 有大于等于 $k$ 个质数，那就 ```l++``` 直到 $[l,r]$ 有的质数个数小于 $k$。最后，每次维护完后取 $\max$，最后再 $+1$ 就行了。

- 而 $[l,r]$ 的质数可以用上面的方法 $O(1)$ 维护。所以最终时间复杂度 $O(n)$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;

vector<int> pr;
bool isp[N];
int pre[N];

int n, m, k;

void sss(int n){
	memset(isp, 1, sizeof isp); //赋初值
	isp[1] = 0;
	for(int i = 2; i <= n; ++i){
		if(isp[i]) pr.push_back(i); //是质数
		for(int j = 0; j < pr.size(); ++j){
			if(1ll * i * pr[j] > n) break; //大于 n 就退出
			isp[i * pr[j]] = 0; //这些都是合数
			if(!(i % pr[j])) break;
		}
	}
	for(int i = 1; i <= n; ++i) pre[i] = pre[i - 1] + isp[i];
	return ;
}
int num, ans;

int main(){
	scanf("%d%d%d", &n, &m, &k);
	sss(m + 1);
	if(pre[m] - pre[n - 1] < k){
		printf("-1");
		return 0;
	}
	if(k == 0){
		printf("0");return 0;
	}
	for(int l = n, r = n; r <= m; ++r){
		if(pre[r] - pre[l - 1] >= k){
			while(pre[r] - pre[l - 1] >= k) ++l;
		}
		ans = max(ans, r - l + 1);
	}
	printf("%d", ans + 1);
	return 0;
}
```

~~但是这两个代码都只跑了 $\text{31ms}$，好像没什么差别。~~

---

## 作者：xvl_ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF237C)

一道二分题。

我们需要用二分在 $O(n\log n)$ 的时间复杂度内得到答案，也就是说我们的判断函数时间复杂度必须为 $O(n)$，因此考虑前缀和。

$sum_i$ 表示出现在区间 $\left[a,b \right]$ 内的前 $i$ 个数中质数的数量。

在二分的判断函数里，我们可以枚举左端点 $i$，用 $sum_{i-1+x} - sum_{i-1}$ 可以得到区间 $\left[i,i-1+x \right]$ 中质数的数量。其中，$x$ 为区间长度。

### Code

```cpp
#include <bits/stdc++.h>
#define ll long long
#define INF 1e9
using namespace std;
int a, b, k, ans;
int sum[1000005];
bool removed[1000005];
void init() {
    removed[1] = 1;
    for (int i = 2; i * i <= b; i++) {
        if (!removed[i]) {
            for (int j = i * i; j <= b; j += i) removed[j] = 1;
        }
    }
}   
bool check(int x) {
    for (int i = a; i - 1 + x <= b; i++) {
        if (sum[i - 1 + x] - sum[i - 1] < k) return 0;
    }
    return 1;
}
void f(int l, int r) {
    while (l <= r) {
        int mid = (l + r) / 2;
        if (check(mid)) {
            r = mid - 1;
            ans = mid;
        }
        else l = mid + 1;
    }
}
signed main() {
    ios :: sync_with_stdio(0);
    cin >> a >> b >> k;
    init();
    for (int i = a; i <= b; i++) {
        sum[i] = sum[i - 1];
        if (!removed[i]) sum[i]++;
    }
    f(1, 5000000);
    if (ans <= b - a + 1) cout << ans;
    else cout << -1;
    return 0;
}
```


---

## 作者：Toothless03 (赞：0)

~~来水一篇题解~~

由于这道题需要访问一个区间内的质数个数，所以我们可以先预处理，将质数线性筛出来，然后再前缀和一下，计算质数的数量。

由于答案满足“合法且最小”所以我们可以想到二分答案。check 的时候只需要使用尺取法 $O(n)$ 遍历一下，对于每个长度为 $l$ 的区间，计算质数的个数，并与 $k$ 比较一下即可。

复杂度 $\displaystyle T(n)=T(\frac{n}{2})+O(n)=O(n\log n)$，可以通过本题。

```cpp
int prime[1000010];
void ethra() {
	prime[0] = 0;
	prime[1] = 1;
	for (int i = 2; i <= 1000000; i++)
		if (!prime[i])
			for (int j = i + i; j <= 1000000; j += i)
				prime[j] = 1;
	for (int i = 1; i <= 1000000; i++)
		prime[i] = prime[i - 1] + !prime[i];
}
int k;
int a, b;
bool check(int l) {
	for (int i = a + l - 1; i <= b; i++)
		if (prime[i] - prime[i - l] < k)
			return false;
	return true;
}
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	ethra();
	cin >> a >> b >> k;
	int l = 0, r = b - a + 1;
	while (l < r) {
		int mid = (l + r) >> 1;
		if (check(mid, a, b))
			r = mid;
		else
			l = mid + 1;
	}
	if (l == b - a + 1) {
		if (check(l, a, b))
			cout << l << endl;
		else
			cout << "-1\n";
	}
	else
		cout << l << endl;
	return 0;
}


```

---

## 作者：bmatrix (赞：0)

~~我来水题解啦！！~~

首先这题和素数有关，我们就先需要一个线性筛：

```cpp
int prm[1000005],tot;
bool vis[1000005];
void init(){
    vis[1]=vis[0]=1;
    for(int i=2;i<=b;i++){
        if(!vis[i])prm[++tot]=i;
        for(int j=1;j<=tot;j++){
            if(i*prm[j]>b)break;
            vis[i*prm[j]]=1;
            if(i%prm[j]==0)break;
        }
    }
}
```

然后让我们分析一下这题的答案：

设最优解为 $ans$ ，其他答案为 $sol$ ，若 $sol<ans$ ，则这个 $sol$ 一定无法满足条件；若 $sol>ans$ ，则 $sol$ 可以满足条件，但是不是最优的。

那么显然，对于这种答案分布，我们可以利用二分法求解。这是一个二分答案的板子：

```cpp
int l=1,r=b-a+1;
while(l<r){
    int mid=(l+r)>>1;
    if(check(mid))r=mid;
    else l=mid+1;
}
cout<<r<<endl;
```

接下来我们考虑```check```函数：

其实很简单，我们只需要用 $l$ 和 $r$ 模拟一个区间，再利用一个 $num$ 表示区间内素数的个数，如果在某一时刻 $num<k$ ，则此答案无法满足要求，否则可以，代码：

```cpp
bool check(int len){
    int t=a,h=a-1,num=0;
    while(h-t+1<len){
        h++;
        if(!vis[h])num++;
    }
    while(h<=b){
        if(num<k)return 0;
        h++;if(!vis[h])num++;
        t++;if(!vis[t-1])num--;
        //模拟区间向前移动一个位置
    }
    return 1;
}
```

最后对于无解的判断：如果整个区间内的素数个数都不到 $k$ ，换句话说，就算是把整个区间覆盖住也无法满足需求，那么就是无解，特判代码：

```cpp
int num=0;
for(int i=a;i<=b;i++)if(!vis[i])num++;
if(num<k){cout<<-1<<endl;return 0;}
```

那么这题就愉快地结束了！~~好水啊~~

此题虽然 $a,b,k$ 范围都是百万，但是 $n\log n$ 做法完全可过。

$$\mathfrak{End.}$$

---

## 作者：开始新的记忆 (赞：0)

题目链接：http://codeforces.com/problemset/problem/237/C

**大致思路**：

这道题目要求在一个区间内满足任意长度为l的区间中都有k个素数，如果可以输出最小满足的区间长度，反之则输出-1.

为了更快的去找到一段区间里有多少素数，我们可以利用埃氏筛法和前缀和预处理来维护（~~蒟蒻不会欧拉筛~~）。1e6的大小，暴力枚举肯定是不行的，所以我想到了——二分，每次都枚举l的大小，只用nlogn的复杂度就可以求出最小满足的l。

**上代码**：


```cpp
#include<bits/stdc++.h>
using namespace std;
int ans[1000010],a,b,k;
bool su[1000010];

void AS()
{
	memset(su,1,sizeof(su));
	memset(ans,0,sizeof(ans));
	su[1]=0;
    for(int i=2;i<=1000000;++i)
        if(su[i])
            for(int j=i+i;j<=1000000;j+=i)
                su[j]=0;
    for(int i=1;i<=1000000;++i)
    {
    	ans[i]=ans[i-1];
    	if(su[i])
    	    ans[i]++;
	}
}

bool judge(int x)
{
	 for(int i=a;i<=b;++i)
    {
        if(i+x-1>b) 
		    break;
        if(ans[i+x-1]-ans[i-1]<k)
            return false;
    }
    return true;
}

int main()
{   int le,ri,mid,sum=-1;
    AS();
    cin>>a>>b>>k;
    le=k;ri=b-a+1;
    while(le<=ri)
    {
        mid=(ri+le)/2;
        if(judge(mid))
        {
            sum=mid;
            ri=mid-1;
        }
        else
            le=mid+1;
    }
	cout<<sum<<endl;
	return 0;
} 
```


---

