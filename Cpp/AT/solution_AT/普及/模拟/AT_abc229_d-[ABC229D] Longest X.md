# [ABC229D] Longest X

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc229/tasks/abc229_d

`X` と `.` からなる文字列 $ S $ が与えられます。

$ S $ に対して、次の操作を $ 0 $ 回以上 $ K $ 回以下行うことができます。

- `.` を `X` に置き換える

操作後に、`X` を最大で何個連続させることができますか？

## 说明/提示

### 制約

- $ 1\ \leq\ |S|\ \leq\ 2\ \times\ 10^5 $
- $ S $ の各文字は `X` または `.` である
- $ 0\ \leq\ K\ \leq\ 2\ \times\ 10^5 $
- $ K $ は整数である

### Sample Explanation 1

$ S $ の $ 7 $ 文字目と $ 9 $ 文字目の `.` を `X` に置き換えて `XX...XXXXX.` とすると、$ 6 $ 文字目から $ 10 $ 文字目で `X` が $ 5 $ 個連続しています。 `X` を $ 6 $ 個以上連続させることはできないので、答えは $ 5 $ です。

### Sample Explanation 2

操作を行う回数は $ 0 $ 回でも構いません。

## 样例 #1

### 输入

```
XX...X.X.X.
2```

### 输出

```
5```

## 样例 #2

### 输入

```
XXXX
200000```

### 输出

```
4```

# 题解

## 作者：syzxzqy (赞：6)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc229_d)  
#### 题目大意：  
在字符串中，最多可以将.替换为 X 的操作后，X 最多可以连续几个？  
#### 题目分析： 
很显然，较长的串能够在满足条件的情况下存在，那么较短的串也能够满足条件存在，符合单调性，可以用二分解决。  
因为 X 这个字符是要连续的，所以判断时就可以提前前缀和‘.’,枚举起始位置，二分找到最后满足条件的位置，计算出长度，求最大值。
总时间复杂度：$O(n\log(n))$。
#### 代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=200001;
int i,k,n,l,r,bao,mid,f[N];
char s[N];
bool pd(int x){
	int i;
	for(i=x;i<=n;i++)//枚举尾，头就是i-x+1 
		if(f[i]-f[i-x+1-1]<=k) return 1;//如果有1个长度符合，就返回1
	return 0; 
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin>>s+1>>k;n=strlen(s+1);
    for(i=1;i<=n;i++)
    	f[i]=f[i-1]+(s[i]=='.');//前缀和 
	l=0;r=n;//二分 
	while(l<=r){
		mid=(l+r)>>1;
		if(pd(mid)) bao=mid,l=mid+1;//单调递增
		else r=mid-1; 
	} 
	cout<<bao;
}
```


---

## 作者：Tang_poetry_syndrome (赞：2)

## [ABC229D] Longest X 
[洛谷题面](https://www.luogu.com.cn/problem/AT_abc229_d) [Atcoder题面](https://atcoder.jp/contests/abc229/tasks/abc229_d)
### 题目大意
给定一个含有 $X$ 和 $.$ 的字符串 $s$，求把 $k$ 个 $.$ 替换成 $X$ 后，最长的连续 $X$ 串。
### 思路
一开始想到前缀和与二分的思路，考虑用前缀和维护 $X$ 的数量，二分求区间长，并遍历可否构成长度为 $l$ 的子串即可，结果为	$l-1$。时间复杂度为 $O(n\,log\,n)$。  
讲题时同机房大佬又给出了双指针的做法，这里也介绍一下。  
枚举，在当前字符为 $.$ 时，记录 $.$ 数量加一。当 $.$ 的数量大于 $k$，则左端点右移，时间复杂度为 $O(n)$。
### 代码
#### 双指针
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int k,cnt,ans;
int main()
{
	cin>>s>>k;
	s=' '+s;
	for(int i=1,j=0;i<s.size();i++){
		while(cnt<=k&&j<s.size())if(s[++j]=='.')cnt++;
		ans=max(ans,j-i);
		if(s[i]=='.')cnt--;
	}
	cout<<ans;
	return 0;
}
```
#### 二分+前缀和
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int a[200010],k;
bool check(int x){
	for(int i=x-1;i<s.size();i++)
		if(a[i+1]-a[i-x+1]<=k) return true;
	return false;
}
int main(){
	cin>>s>>k;
	for(int i=0;i<s.size();i++){
		if(s[i]=='.') a[i+1]++;
		a[i+1]+=a[i];
	}
	int l=1,r=s.size();
	while(l<=r){
		int mid=(l+r)/2;
		if(check(mid)) l=mid+1;
		else r=mid-1;
	}
	printf("%d",l-1);
	return 0;
}
```
[提交记录 二分+前缀和](https://atcoder.jp/contests/abc229/submissions/45521378)  
[提交记录 双指针](https://atcoder.jp/contests/abc229/submissions/45521276)

---

## 作者：loser_seele (赞：2)

双指针法好题，场上没想出来。感谢 [霖ux](https://www.luogu.com.cn/user/520914) 的代码援助。

实际上我们可以枚举每个区间 $ [l,r] $，如果这个区间内点的个数 $ \leq K $ 则是符合条件的区间，更新答案。但这样做太慢，于是考虑更优的方案。

因为题目维护的区间满足单调性，发现当 $ l $ 固定的时候只需要不断增加 $ r $ 的值直到区间内点的个数不符合条件，则 $ r $ 即为符合条件的最大值，然后不断地增加 $ l $ 即可。

可以发现每次操作都会增加 $ l,r $ 当中的至少一个，所以时间复杂度为 $ \mathcal{O}(n) $，可以通过。当然这题也可以用二分或者滑动窗口一类的东西实现，不扩展。

考场代码：

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=2e5+10;
char s[maxn];
int k,n;
int r[maxn];
int main(){
	scanf("%s%d",s+1,&k);
	n=strlen(s+1);
	int cnt=0;
	for(int i=1,j=0;i<=n;i++){
		while(cnt<=k&&j<=n)if(s[++j]=='.')cnt++;
		r[i]=j;
		if(s[i]=='.')cnt--;
	}
	int ans=0;
	for(int i=1;i<=n;i++)ans=max(ans,r[i]-i);
	return printf("%d",ans),0;
}
```


---

## 作者：qianyuzhe (赞：2)

## 题意简述

给定一个含有 $X$ 和 $.$ 的字符串 $s$，每次操作可以将任意一个 $.$ 变为 $X$，求最多 $k$ 次操作后字符串最长全部为 $X$ 的连续子串长度。

## 题目分析

本题实际上是让我们找出字符串中一个最长的区间，使得该区间内 $.$ 的个数不超过 $k$。

考虑暴力枚举每一个区间，时间复杂度为 $O(n^2)$，对于 $1\leq n\leq 2\times 10^5$ 的数据范围显然过不了。

然后考虑用二分优化。如果我们先用一个数组 $q$ 存储从字符串开头到当前下标的 $.$ 的个数，然后二分答案找到最多 $k$ 次操作后字符串最长全部为 $X$ 的连续子串长度并输出即可，时间复杂度为 $O(n\log m)$，其中 $m$ 为 $s$ 的长度，可以通过。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int k,l=1,r,m,n,i,q[200005];
bool f;
int main(){
	ios::sync_with_stdio(false);
	cin>>s>>k;
	r=s.size();
	s=" "+s;//为了便于后续的计算，可以让s的下标从1开始 
	for(i=1;i<=s.size();i++)q[i]=q[i-1]+bool(s[i]=='.');//计算前缀和
	while(l<=r){//二分答案 
		m=l+r>>1;
		f=false;
		for(i=1;i+m-1<s.size();i++){
			if(q[i+m-1]-q[i-1]<=k){//判断区间中'.'的个数是否小于等于k 
				f=true;
				break;
			}
		}
		if(f)l=m+1;
		else r=m-1;
	}
	cout<<l-1<<endl;//换行是个好习惯 
}

```

---

## 作者：zhoukaixiang (赞：1)

# 题目分析

该题是一个双指针的问题，我们可以枚举每个区间，区间大于等于 $l$ ，小于等于 $r$ , 如果这个区间内点的个数比 $K$ 小或者相等，则是符合条件的区间，更新答案 $max$ 。否则使 $l$ 向右移动，直至区间内点的个数小于等于 $K$ 。枚举完毕后 $max$ 即为所求。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
  string s;
  int k, maxi = -1;
  cin >> s >> k;
  int l, r, dots = 0, L = s.size();
  l = r = 0;
  while(r < s.size()) {
    if(s[r] == '.')  dots ++;
    //使 l 向右移动，直至区间内点的个数小于等于K
    while(dots > k) {
      if(s[l] == '.')  dots --;
      l ++;
    }
    maxi = max(maxi, r- l + 1);
    r ++;
  }
  cout << maxi;
  return 0;
}

```

---

## 作者：skyskyCCC (赞：0)

## 前言。
一个喜闻乐见的日本字符串题。
## 分析。
如果我们没有找到 $X$ 并且 $k=0$ 即不允许改变字符，则无解。

然后我们去找两个 $X$ 且相邻，注意相邻指忽略其中的所有点，然后分别作为左右端点，如果其中点的数量比 $K$ 大，那么左指针右移，去找右端点，这个区间的长度便是当前的修改结果，取最大值，然后进行不断模拟即可。

代码如下，仅供参考：
```
#include<iostream>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
string s;
int k;
int t,sum,ans;
int main(){
	cin>>s>>k;
	for(int i=0;i<s.size();i++){
		if(s[i]=='X'){
		    t=1;
		    break;
		}//找到了X故至少答案为1，所以退出。
	}
	if(t==0&&k==0){
		cout<<"0\n";
		return 0;
	}//特判。
	int j=0;
	for(int i=0;i<s.size();i++){
		if(s[i]=='.'){
		    sum++;
		}
		while(sum>k&&j<i){
			if(s[j]=='.'){
			    sum--;
			}//进行右移操作。
			j++;
		}
		ans=max(ans,i-j+1);//取区间长度最大值。
	}
	cout<<ans<<"\n";
	return 0;
}
```
## 后记。
大家如有疑问，可以在评论区提出，我会尽力解答的。

---

## 作者：Luxingguang (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P1763)

## 一、简述题意
------------
给定一个以 $X$ 和 $.$ 组成的的字符串 $S$。
你可以对 $S$ 进行 $0∼K$ 以下操作 (包含 $0$ 和 $K$ 次)。把 $S$ 中的一个 $.$ 替换成 $X$。求操作之后，$S$ 中连续 $X$ 的最大数量为多少？
## 二、思路分析
------------
这是一道不错的尺取法，首先我们定义一个左端点与右端点。然后再计算其中 $.$ 的个数，若 $.$ 的数量大于 $K$ ，则移动左端点。
## 二、构造代码
------------
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int n,k,l,cnt,ans;
string s;
bool p;
signed main(){
	cin>>s>>k;
	for(int i=0;i<s.size();i++){
		if(s[i]=='X') p=1;
	}
	if(p==0&&k==0) {
		puts("0");
		return 0;
	}
	for(int r=0;r<s.size();r++){
		if(s[r]=='.') cnt++;
		while(cnt>k&&l<r){
			if(s[l]=='.') cnt--;
			l++;
		}ans=max(ans,r-l+1);
	}printf("%d",ans);
	return 0;
}
```

---

## 作者：zyn_ (赞：0)

# [ABC229D] Longest X

## 题面大意

给定一个以 `X` 和 `.` 组成的字符串 $S$ 和一个自然数 $k$。将 $S$ 中不超过 $k$ 个 `.` 替换为 `X`，使 $S$ 中连续的 `X` 的数量最大。求这个最大值。

## 题目分析

令 $n=|S|$。（$n$ 为 $S$ 的长度）

设 $a_i$ 为最大的 $p$ 的值，使 $S$ 的第 $i$ 到 $p$ 个字符中，字符 `.` 不超过 $k$ 个。

此时，答案即为 $\max_{1\le i\le n}\{a_i-i+1\}$。

易得 $a_i$ 单调不降，可使用双指针求 $a_i$。

维护双指针 $l$ 和 $r$，初始 $r$ 为 $0$。将 $l$ 从 $1$ 到 $n$ 遍历。在 $r\le n$ 的前提下不断右移 $r$，直到 $S$ 的第 $l$ 到 $r$ 个字符中字符 `.` 的个数超过 $k$。此时，左移 $r$，$a_l$ 的值就为 $r$。这样即可依次求出 $a_1,a_2,..,a_n$，并顺带记录答案。

时间复杂度当然是 $O(n)$ 的。

## AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,l,r,ans,cnt;
char s[200009];
int main(){
	scanf("%s%d",s+1,&k);
	for(n=1;s[n];++n);--n;  //获取S的长度
	for(l=1;l<=n;++l){
		while(cnt<=k&&r<=n)cnt+=(s[++r]=='.');
		ans=max(ans,r-l); //r还没左移，a[l]为r-1
        			  //所以a[l]-l+1=r-1-l+1=r-l
		cnt-=(s[r--]=='.');  //不要忘记减掉多算的贡献
		cnt-=(s[l]=='.');
	}
	printf("%d",ans);
	return 0;
}
```


---

## 作者：Symbolize (赞：0)

# $\tt{Solution}$
首先思考一下暴力点的情况，枚举最后答案是哪一个区间是很容易想到的，用一下前缀和记录 `.` 的个数，就可以快速求出把某一区间全部变成 `X` 需要的代价了。深入思考，不难发现答案具备单调性，所以考虑二分答案，最终的答案即为区间的长度，所以每次枚举右端点，就做完了。

```cpp
/*
	Luogu name: Symbolize
	Luogu uid: 672793
*/
#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define x first
#define y second
#define rep1(i,l,r) for(register int i=l;i<=r;++i)
#define rep2(i,l,r) for(register int i=l;i>=r;--i)
#define rep3(i,x,y,z) for(register int i=x[y];~i;i=z[i])
#define rep4(i,x) for(auto i:x)
#define debug() puts("----------")
const int N=2e5+10;
const int inf=0x3f3f3f3f3f3f3f3f;
using namespace std;
int n,sum[N],len;
string s;
int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return f*x;
}
bool check(int x)
{
	rep1(i,x,len) if(sum[i]-sum[i-x]<=n) return 1;
	return 0;
}
signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	cin>>s;
	len=s.length();
	s=" "+s;
	n=read();
	rep1(i,1,len) sum[i]=sum[i-1]+(s[i]=='.');
	int l=0,r=len,ans;
	while(l<=r)
	{
		int mid=l+r>>1;
		if(check(mid)) l=mid+1,ans=mid;
		else r=mid-1;
	}
	cout<<ans<<endl;
	return 0;
}

```

---

