# 【MX-X7-T2】[LSOT-3] 姬誉蛙

## 题目背景

原题链接：<https://oier.team/problems/X7C>。

姬誉蛙——每十六年在陆地上出现一次的 奇迹般的青蛙

呱…呱呱呱呱…

快把门打开啊 呱呱

## 题目描述

Ringo 为了解除姬誉蛙的诅咒需要做出由 Tabuki 出的一道题。

定义一个 $01$ 串的权值为这个串中 $0$ 的数量与 $1$ 的数量的乘积。

给你一个长度为 $n$ 的 $01$ 串。你想知道将整个串恰好划分为 $k$ 个连续子串后，这 $k$ 个子串的最大权值最小可以是多少。

## 说明/提示

**【样例解释 #1】**

分成的两段分别为 `10000` 和 `0001`。第一段的权值为 $4\times 1=4$，第二段的权值为 $3\times 1=3$，最大值为 $4$。

可以证明不存在使得最大权值更小的方案。需要注意的是，`1000` 和 `00001` 也是一个最大权值为 $4$ 的方案。

**【样例解释 #2】**

可以分成三段 `1000000`、`10101`、`001000`，最大权值为第二段的 $2\times 3=6$。

**【数据范围】**

对于 $15\%$ 的数据，$n\le 20$。

对于 $40\%$ 的数据，$n\le 5000$。

对于另外 $10\%$ 的数据，串中仅含有 $0$。

对于全部的数据，$1\le k\le n\le 10^6$，串中仅含 $0$ 或 $1$。

## 样例 #1

### 输入

```
9 2
100000001```

### 输出

```
4```

## 样例 #2

### 输入

```
18 3
100000010101001000```

### 输出

```
6```

# 题解

## 作者：jinhangdong (赞：12)

二分答案，每次看看至少需要分成几块 $\le k$ 就移右端点，否则移左端点。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int l,r=1e18,n,k;
string s;
bool check(int x)
{
	int cnt=1,c1=0,c0=0;
	for(int i=1;i<=n;++i)
	{
		if(s[i]=='1') c1++;
		else c0++;
		if(c1*c0>x)//说明需要新的块
		{
			cnt++;
			c1=0,c0=0;
			if(s[i]=='1') c1++;
			else c0++;
		}
	}
	return cnt<=k;
}
signed main()
{
	cin>>n>>k;
	cin>>s;
	s=" "+s;
	while(l<r)
	{
		int mid=(l+r)/2;
		if(check(mid)) r=mid;
		else l=mid+1;
	}
	cout<<r;
	return 0;
}
```

---

## 作者：FamousKillerconan (赞：5)

看到最大值最小，直接使用二分，对于判断函数，使用贪心思路，直接算区间权值是否超过“最大值”，超过就重开一段，最后看是不是小于或等于 $k$。


以免计算 0 的数量和 1 的数量而导致代码复杂度变高，我这里用了一下前缀和~~其实不用也可以~~。


AC 代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define PII pair<int,int>
using namespace std;
const int N=1e6+5;
const int INF=0x3f3f3f3f;
const double EPS=10e-6;
string s;
ll n,k,sum0[N],sum1[N],ans;
ll calc(int x,int y){
	return (sum0[y]-sum0[x-1])*(sum1[y]-sum1[x-1]);
}
bool check(ll x){
	ll cnt=0,st=1;
	for(int i=1;i<=n;i++){
		if(calc(st,i)>x){
			cnt++;
			st=i;
		}
	}
	return cnt+1<=k;
}
void solve(){
	cin>>n>>k>>s;
	s=' '+s;
	for(int i=1;i<=n;i++){
		sum0[i]=sum0[i-1]+(s[i]=='0');
		sum1[i]=sum1[i-1]+(s[i]=='1');
	}
	ll l=0,r=1e12;//
	while(l<=r){
		ll mid=l+r>>1;
		if(check(mid)){
			ans=mid;
			r=mid-1;
		}
		else l=mid+1;
	}
	cout<<ans;
} 
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	int T=1;
//	cin>>T;
	while(T--)solve();
	return 0;
}
```

---

## 作者：XCDRF_ (赞：4)

# P11561 【MX-X7-T2】\[LSOT-3] 姬誉蛙

[原题传送门](https://www.luogu.com.cn/problem/P11561)

[更好的阅读体验](https://www.luogu.com.cn/article/tfugrj9d)

## 解题思路

看到最大值最小，首先想到二分答案。

二分这个最大值，每次 check 的时候将整个串遍历一遍，如果发现当前段的权值已经超过了二分到的最大值，就再开一段。如果这样分完段数不超过 $k$ 段，则该最大值可行。

## 参考代码

```cpp
#include<iostream>
#define int long long
#define mid (l+r>>1)
using namespace std;
const int N=1e6+5;
int n,k;
char s[N];
bool check(int x){
	int cnt=1,cnt0=0,cnt1=0;
	for(int i=0;i<n;i++){
		if(s[i]=='0') cnt0++;
		else cnt1++;
		if(cnt0*cnt1>x){
            cnt++; 
			cnt0=(s[i]=='0');
			cnt1=(s[i]=='1');
            if(cnt>k) return 0;
        }
	}
	return 1;
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>n>>k>>s;
	int l=0,r=1e18;
	while(l<r){
		if(check(mid)) r=mid;
		else l=mid+1;
	}
	cout<<r;
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/197727817)

---

## 作者：_Jocularly_ (赞：3)

用二分答案先二分出答案，再贪心的取得每一段区间，如果不成立看看比当前更大的，否则看看有没有更小的，直接输出答案即可。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,k;
string s;
int ans;
bool check(int mid) {
    int cnt0 = 0, cnt1 = 0;
    int sum = 1;
    for(int i=0;i<n;i++){
        if(s[i] == '0') cnt0 ++;
        else cnt1 ++;
        int num = cnt0 * cnt1;
        if(num > mid){
            sum ++;
            cnt0 = cnt1 = 0;
            if(s[i] == '0') cnt0 ++;
            else cnt1 ++;
        }
        if(sum > k) return 0;
    }
    return 1;
}
signed main() {
    cin >> n >> k;
    cin >> s;
    int l = 0,r = pow(n,2);
    while(l <= r){
        int mid = (l + r) / 2;
        if(check(mid)){
            ans = mid;
            r = mid - 1;
        }else l = mid + 1;
    }
    cout << ans;
    return 0;
}

```

---

## 作者：zlqwq (赞：3)

二分答案题，但赛事由于太废物导致没过。

我们可以考虑一下，check 函数应该判断什么，显然是当我们设 $mid$ 为分割的最大答案时，需要切成几段。然后我们遍历字符串算贡献，然后求出来用几段即可。


```cpp
#include<iostream>
#define int long long
using namespace std;
char ch[1000005]; 
int n,k;
bool check(int mid){
	int cnt=0,c1=0,c0=0;
	for(int i=1;i<=n;i++){
		if(ch[i]=='1')c1++;
		else c0++;
		if(c0*c1>mid){
			cnt++;
			c0=(ch[i]=='0'?1:0);
			c1=(ch[i]=='0'?0:1);
		}
	}
	return cnt+1<=k;
}
signed main(){
	cin>>n>>k;
	cin>>(ch+1);
	int l=0,r=n*n;
	int best;
	while(l<=r){
		int mid=l+r>>1;
		if(check(mid)){
			best=mid;
			r=mid-1;
		}
		else l=mid+1;
	}
	cout<<best;
	return 0;
}
```

---

## 作者：XiaoHongChong (赞：2)

这道题可以用二分解决。  
设 `check(i)` 表示答案是 `i` 可行不可行。  
注意：  
开 `long long`，不然只有 $95$ 分。
```cpp
#include <iostream>
#define ll long long
using namespace std;
int n, k;
ll l, r, mid, ans;
string s;
bool check(ll m)
{
  //还没有分之前就是1段，所以 cnt 初始为 1
	ll cnt = 1, a = 0, b = 0;
	for (int i = 0; i < n; i++)
	{
		(s[i] == '1' ? a : b)++;
		if (a * b > m)
		{
			cnt++;
			a = 0, b = 0;
			(s[i] == '1' ? a : b)++;
		}
	}
	return cnt <= k;
}
int main()
{
	cin >> n >> k >> s;
	l = 0, r = 1e18;
	while (l <= r)
	{
		mid = (l + r) / 2;
		if (check(mid))
			ans = mid, r = mid - 1;
		else
			l = mid + 1;
	}
	cout << ans << endl;
	return 0; 
}
```

---

## 作者：anke2017 (赞：1)

## P11561 题解

容易发现，答案具有**单调性**。

然后，如果确定了最大权值，那么可以用**贪心**，线性求解最少要分成几段。  
具体的，如果现在加上这个数字后超过了权值，肯定要新开一段，否则，肯定尽可能放在当前段。

由于最大权值是 $O(n^2)$ 的，二分复杂度为 $O(n\log{n})$。

代码：
```cpp
#include<bits/stdc++.h>

using namespace std;

char x[1000001];

int check(int n,long long maxn)//确定最大权值，返回最少几段
{
    long long ma=0,mb=0;
    int ans=0;
    for(int i=0;i<n;i++)
    {
        if(x[i]&1)ma++;//这里用了 0 和 1 的 ascll 码特性
//如果为 '0'，就会让 mb 加一，否则 ma 加一。
        else mb++;
        if(ma*mb>maxn)
        {
            ans++,ma=0,mb=0;
            if(x[i]&1)ma++;
            else mb++;
        }
    }
    ans++;//最后一段
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);cin.tie(0);
    int n,t;cin>>n>>t;
    cin>>x;
    long long l=-1,r=1e15;//r 大于 n^2，够用了
    while(l<r-1)
    {
        long long mid=(l+r)>>1;
        if(check(n,mid)>t)l=mid;
        else r=mid;
    }
    cout<<r;
    return 0;
}
```

---

