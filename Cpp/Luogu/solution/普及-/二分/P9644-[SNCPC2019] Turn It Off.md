# [SNCPC2019] Turn It Off

## 题目描述

现在已经是 21:30 了，宝宝该上床睡觉了。为了确保他的睡眠质量，宝宝决定关掉卧室里的所有灯。

宝宝的卧室里有 $n$ 盏灯，从1到 $n$ 排成一排。每次宝宝可以选择一个整数 $i$，并将从第 $i$ 盏灯到第 $(i+L-1)$ 盏灯（包括两端）之间的所有灯关掉，其中 $L$ 是一个预定义的正整数。注意，每次操作的 $L$ 值必须相同。

给定所有灯的初始状态，请帮助宝宝确定可能的最小 $L$ 使得他能在 $k$ 次操作内关掉所有的灯。

## 样例 #1

### 输入

```
2
10 4
0101011111
3 1
010```

### 输出

```
3
1```

# 题解

## 作者：Dws_t7760 (赞：7)

一道二分题。

由于数据保证至少有一个盏灯是开的，我们可以在 $1$ 和 $n$ 之间二分查找答案。

二分思路：假设每次操作可以将连续的 $L$ 盏灯关掉，我们从左到右依次遍历所有灯，如果是关的，就跳过，否则如果操作次数没有达到 $k$，将从这盏灯开始的连续 $L$ 盏灯关掉。最后如果所有的灯都关掉了，那么这个 $L$ 就满足条件。我们在 $1$ 和 $n$ 之间二分查找答案，最后找出最小的满足条件的 $L$ 作为答案。

AC 代码：

```
#include<bits/stdc++.h>
using namespace std;
int t,n,k,l,r,mid,ans;
string a;
bool check(int ll) {
	string temp=a;
	int s=0,i=0;
	while(i<n) {
		if(temp[i]=='0') {
			i++;
			continue;
		}
		for(int j=i;j<min(i+ll,n);j++) temp[j]='0';
		i+=ll,s++;
		if(s>=k) break;
	}
	for(i=0;i<n;i++) if(temp[i]=='1') return 0;
	return 1;
}
int main() {
	ios::sync_with_stdio(0),cin.tie(0),cout.tie();
	cin>>t;
	for(int i=0;i<t;i++) {
		cin>>n>>k;
		cin>>a;
		l=1,ans=r=n;
		while(l<=r) {
			mid=(l+r)/2;
			if(check(mid)) ans=mid,r=mid-1;
			else l=mid+1;
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：sfqxx1 (赞：5)

这是一篇 python 题解。

一道关于二分查找的问题。我们要找到一个最小的 $L$，使得我们可以用长度为 $L$ 的区间来覆盖所有的 "1"，并且做这个操作的次数不超过 $k$。

我们可以观察，如果一盏灯已经被关掉了，我们就可以忽略它，因为我们无论如何操作都不会影响到它。所以我们可以首先将所有的 "0" 都去掉，只考虑 "1" 的位置。

然后，我们可以利用二分查找来寻找最小的 $L$。我们知道，如果某个 $L$ 可以在 $k$ 次操作内关掉所有的灯，那么任何大于 $L$ 的数都可以做到这一点。因此，我们可以将 $L$ 设定为可能的最大值（即所有 "1" 的数量），然后每次尝试把它减半，直到找到最小的 $L$。

Python代码：

```python
import bisect
T = int(input())
for _ in range(T):
    n, k = map(int, input().split())
    s = input().strip()
    a = [i for i in range(n) if s[i] == '1']
    l = 1
    r = n
    while l < r:
        m = (l + r) // 2
        i = 0
        cnt = 0
        while i < len(a):
            j = bisect.bisect_right(a, a[i] + m - 1)#使用了bisect_right函数来找到最大的不超过$L$的位置
            cnt += 1         
            i = j            
        if cnt <= k:
            r = m            
        else:        
            l = m + 1
    print(l)
```

蒟蒻的第一篇题解，希望能过 QWQ。



---

## 作者：myyyIisq2R (赞：2)

# [P9644 SNCPC2019 Turn It Off](https://www.luogu.com.cn/problem/P9644)
## Solution
考虑二分答案，二分的是小于 $\text{k}$ 的最大段数，使得包含所有的 $1$。
设枚举的段数为 $\text{x}$，在 $\text{check}$ 函数中，通过枚举找到第一个 $\text{1}$，接着向后累加 $\text{x}$，直到覆盖完该序列，若符合题意中条件即段数小于 $\text{k}$，继续向下二分，否则向上二分，直到找到答案。

注意边界条件，细节在注释里。

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,k;		
string s;
bool check(int x)
{
	int p;
	for(int i{1};i<=n;i++)
	{
		if(s[i] == '1') 
		{
			p = i; //找到第一个1
			break;
		}
	}
	int cnt{};//记录段数
	while(p<=n) //边界
	{
		p += x;
		cnt++; 
		if(p>n) break; //控制边界
		while(s[p]=='0')++p; //若是0则无需覆盖
		
	}
	if(cnt<=k) return true; //符合条件
	return false;
}
int main()
{
	int T;
	cin>>T;
	while(T--)
	{

		cin>>n>>k;

		cin>>s;
		s = " "+s; //使下标从1开始
		int l = 1; //左端点设为1
		int r = n/k+1;
		while(l<r) //二分答案
		{
			int mid = (l+r)>>1;
			if(check(mid)) r = mid; 
			else l = mid+1;
		}
		cout<<l<<endl;
	}
}
```

---

## 作者：封禁用户 (赞：1)

## [题面传送门](https://www.luogu.com.cn/problem/P9644)

## 题面翻译

现在已经是晚上 21:30 了，宝宝该上床睡觉了。为了确保他的睡眠质量，宝宝决定关闭卧室里的所有灯。

卧室里有 $n$ 盏灯，从 $1$ 到 $n$ 编号，排成一排。每次宝宝可以选择一个整数 $i$，并关闭从 $i$ 到 $(i+L-1)$ 编号的所有灯（包括这两盏），其中 $L$ 是一个预先定义的正整数。请注意，每次选择的 $L$ 必须相同。

给定所有灯的初始状态，请帮助宝宝确定最小可能的 $L$，以便他可以在 $k$ 次内关闭所有灯。

## 输入格式

有多个测试用例。输入的第一行包含一个整数 $T$，表示测试用例的数量。对于每个测试用例：

第一行包含两个整数 $n$ 和 $k$（$1 \le k \le n \le 2 \times 10^5$）。

第二行包含一个字符串 $s$（$|s| = n$，$s \in \{\text{0}, \text{1}\}$），表示灯的初始状态。如果 $s_i = \text{1}$，则表示第 $i$ 盏灯最初是开着的，否则它最初是关着的。保证 $s$ 中至少有一个 `1`。

保证所有测试用例的 $n$ 之和不超过 $2 \times 10^6$。

## 输出格式

对于每个测试用例，输出一行，包含一个整数，表示最小可能的 $L$。

# 题目大意

输入 $T$ 组数据，每组两个整数一个 $01$ 字符串。然后有一个从 $1$ 到 $n$ 编号的数组，求 $L$ 最少是多少可以让宝宝在 $k$ 次内关掉所有灯。

# 题目解法

考虑二分答案，再用一个函数判断，每次找到之后直接调用函数，因此时间复杂度会很低。具体：先二分 $L$，然后贪心能关多少关多少。因为题目保证每个字符串都有一个 $1$ 所以不用特判全为 $0$ 的情况

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;

bool pdISok(int l,int k,string &str){
	int len=str.size(),cnt=0;
	for(int i=0;i<len;){
		int dy=i;
		while(dy<len&&str[dy]=='0')dy++;
		if(dy==len)break;
		i=dy+l,cnt++;
	}
	if(cnt<=k)return true;
	else return false;
}
int main(){
	int T;cin>>T;
	while(T!=0){
		T--;
		int n,k;cin>>n>>k;
		string str;cin>>str;
		int left=1,right=n;
   		while(left<right){
        	int mid=(left+right)/2;
        	if(pdISok(mid,k,str))right=mid;
        	else left=mid+1;
    	}
        cout<<left<<endl;
	}
	return 0;
}


```

---

## 作者：InversionShadow (赞：1)

## 题意：

给定长度为 $n$ 的字符串 $s$，如果 $s_i$ 为 `1`，则第 $i$ 个地方的灯是开的，否则是关的。你可以确定一个 $l$，每次确定一个 $i$，关闭 $i \sim (i + l - 1)$ 的灯，且关闭次数要小于 $k$，求最小的 $l$。

## 思路：

看到“求最小的”就要想到二分。

我们可以去二分这个 $l$，那么 `check` 函数怎么写呢？

贪心的去思考，每次关闭的左端点肯定要满足 $s_i=1$，因为这样有可能可以覆盖到下一个 $s_j=1$ 的地方，所以这个方案是最优的。

```cpp
#include <bits/stdc++.h> 

using namespace std;

const int MAXN = 2e6 + 100;

int t, n, k;
string s;
bool vis[MAXN];

bool check(int mid) {
  memset(vis, 0, sizeof(vis)); // 多组数据清空
  int sum = 0;
  for (int i = 0; i < n; i++) {
    if (!vis[i] && s[i] == '1') { // 左端点且没有被覆盖
      for (int j = i; j < i + mid; j++) { // 暴力修改 i ~ i + mid - 1
        vis[j] = 1;
      }
      sum++;
    }
  }
  return sum <= k;
}

void solve() {
  cin >> n >> k >> s;
  int l = 1, r = n;
  while (l < r) {
    int mid = l + r >> 1;
    if (check(mid)) {
      r = mid;
    } else {
      l = mid + 1;
    }
  }
  cout << l << endl;
}

int main() {
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}
```

---

## 作者：zhaohanwen (赞：1)

## 题目分析

简单分析可知 $L$ 是单调的，并且题目让我们找到最小的 $L$，所以二分答案。

因为保证 $s$ 中肯定有至少 $1$ 个 `1` 所以无需特判。

二分 $L$，每次检查时贪心即可。


```cpp
#include <bits/stdc++.h>
using namespace std;
bool check(int mid,int k,int n,string s)
{
	int cnt=0;
	for (int i=0;i<n;)
	{
		if (s[i]=='1')
		{
			cnt++;
			i+=mid;
		}
		else
		{
			i++;
		}
	}
	return cnt<=k;
}
int solve(int n,int k,string s)
{
	int L=1,R=n;
	while (L<R)
	{
		int mid=(L+R)/2;
		if (check(mid,k,n,s)) R=mid;
		else L=mid+1;
	}
	return L;
}
int main()
{
	int T;
	cin>>T;
	while(T--)
	{
		int n,k;
		string s;
		cin>>n>>k>>s;
		cout<<solve(n,k,s)<<endl;
	}
	return 0;
}
```


---

## 作者：Crasole (赞：0)

## 思路

直接枚举 $L$，由于 $n \le 2 \times 10 ^ 5$，会超时，所以考虑使用二分来求解 $L$。对于每次的灯 $s_i$，有如下两种情况：

- 如果当前的灯 $s_i$ 没有关，那么就把 $i$ 向后移动 $L$ 个单位，就是 $i = i + L$，代表 $i$ 至 $i + L - 1$ 的都被关了。

- 如果当前的灯 $s_i$ 关了，直接 `i++` 即可，因为关着的灯不用处理。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e6 + 10;
int T, n, k;
int a[N];
bool check(int x, int k, int a[]) {
	int s = 0;
	for(int i = 1; i <= n;)
		if(a[i] == 1)
			s++, i += x;
		else i++;
	return s <= k;
}
void solve(int n, int k, int a[]) {
	int l = 1, r = n, ans;
	while(l <= r) {
		int mid = (l + r) >> 1;
		if(check(mid, k, a)) ans = mid, r = mid - 1;
		else l = mid + 1;
	}
	cout << ans << endl;
}
int main(){
	ios::sync_with_stdio(false);
	cin >> T;
	while(T--) {
		cin >> n >> k;
		for(int i = 1; i <= n; i++) {
			char ch;
			cin >> ch, a[i] = ch ^ 48;
		}
		solve(n, k, a);
	}
	return 0;
} 
```

---

## 作者：WhitD (赞：0)

## 思路
要求一次连续关灯数量 $L$ 的最小值，考虑二分答案。

一个显然的性质是：每次关灯我们一定会从还所有没关的灯的最左边的那个灯开始关（这样可以保证一次至少关一个灯，并且可能会有额外的收获）。因此我们就二分 $L$ 的值，并利用上述性质进行检验，不难看出 $L$ 的取值就在 $[1,n]$ 中，因此总时间复杂度是 $O(n \log n)$ 的。
## AC 代码
```cpp
#include<bits/stdc++.h>
#define mid ((l+r)/2)
using namespace std;
string s;
int T,n,k;
int chk(int x)
{
	int cnt=0;
	for(int i=0;i<n;)
	{
		if(s[i]-'0')
			cnt++,i+=x;
		else
			i++;
	}
	return (cnt<=k);
}
int main()
{
	cin>>T;
	while(T--)
	{
		cin>>n>>k>>s;
		int l=1,r=n;
		while(l<r)
		{
			if(chk(mid))
				r=mid;
			else 
				l=mid+1;
		}
		cout<<l<<endl;
	}
	return 0;
}
```


---

## 作者：tang_mx (赞：0)

题目要求让操作次数最小化，并且 $L$ 的长度有单调性（若 $L$ 可行，比 $L$ 大的必然可行）。因为操作之后原先关着的灯状态不会改变，所以只需要考虑开着的灯，直接无脑二分即可。

都是 $0$ 的情况可以特判一下。

代码

```cpp
#include<bits/stdc++.h>
#define ull unsigned long long
#define ll long long

using namespace std;

inline int read(){
	int x=0,y=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-') y=-y;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+(c^'0');c=getchar();}
	return x*y;
}

const int N=2e5+10;

int t,n,k;
string s;

bool check(int x){
	int cnt=0;
	for(int i=0;i<n;i++){
		if(s[i]=='1'){
			cnt++;
			i=i+x-1;
		}
	}
	return cnt<=k;
}

void solve(){
	n=read(),k=read();
	cin>>s;
	int len=s.length();
	int cnt=count(s.begin(),s.end(),'0');
	if(cnt==len){
		printf("0\n");return ;
	}
	int l=1,r=n;
	while(l<r){
		int mid=(l+r)>>1;
		if(check(mid))r=mid;
		else l=mid+1;
	}
	printf("%d\n",l);
}

int main(){
	t=read();
	while(t--){
		solve();
	}
	return 0;
}
```


---

## 作者：luan341502 (赞：0)

赛时还挂了一发，原因是字符串上下界搞错了。

对于这题的答案，越大的 $L$ 越能在更小的次数能完成操作，因此我们考虑二分答案，每次 check 时贪心选择即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k;
string s,str;
bool check(int x,int k){
	str='0'+s;
	int i=1,ans=0;
	while(i<=n){
		if(str[i]=='1') i+=x,ans++;
		else i++;
	}
	return ans<=k;
}
int main(){
	int t;
	cin>>t;
	while(t--){
		scanf("%d%d",&n,&k);
		cin>>s;
		int l=1,r=n;
		while(l<r){
			int mid=(l+r)>>1;
			if(check(mid,k)) r=mid;
			else l=mid+1;
		}
		printf("%d\n",r);
	}
	return 0;
}
```


---

## 作者：SDLTF_凌亭风 (赞：0)

来自某不愿意透露姓名的队友。

---
性质比较签到，虽然一开始把题目看错了的说。

首先我们发现如果 $L$ 可以那么比 $L$ 大的必然可以，具有单调性，所以很明显二分答案。

至于检查的话可以直接贪心，也即如果有一个没关的灯就直接把以它开始的一段全部关掉。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef int ll;
typedef long long int li;
const ll MAXN=2e5+51;
ll test,n,kk,l,r,mid,res;
char ch[MAXN];
inline ll read()
{
	register ll num=0,neg=1;
	register char ch=getchar();
	while(!isdigit(ch)&&ch!='-')
	{
		ch=getchar();
	}
	if(ch=='-')
	{
		neg=-1;
		ch=getchar();
	}
	while(isdigit(ch))
	{
		num=(num<<3)+(num<<1)+(ch-'0');
		ch=getchar();		
	}
	return num*neg;
}
inline ll check(ll mid)
{
	ll cur=0;
	for(register int i=1;i<=n;i++)
	{
		ch[i]&1?(cur++,i+=mid-1):1;
	}
	return cur<=kk;
}
inline void solve()
{
	n=read(),kk=read(),l=1,r=n,res=0,scanf("%s",ch+1);
	while(l<=r)
	{
		mid=(l+r)>>1;
		check(mid)?r=mid-1,res=mid:l=mid+1;
	}
	printf("%d\n",res);
}
int main()
{
	test=read();
	for(register int i=1;i<=test;i++)
	{
		solve();
	}
}
```


---

