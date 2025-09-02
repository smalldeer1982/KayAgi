# String Game

## 题目描述

Little Nastya has a hobby, she likes to remove some letters from word, to obtain another word. But it turns out to be pretty hard for her, because she is too young. Therefore, her brother Sergey always helps her.

Sergey gives Nastya the word $ t $ and wants to get the word $ p $ out of it. Nastya removes letters in a certain order (one after another, in this order strictly), which is specified by permutation of letters' indices of the word $ t $ : $ a_{1}...\ a_{|t|} $ . We denote the length of word $ x $ as $ |x| $ . Note that after removing one letter, the indices of other letters don't change. For example, if $ t= $ "nastya" and $ a=[4,1,5,3,2,6] $ then removals make the following sequence of words "nastya" ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF778A/355fee5161a1808ee95ea5dc6d815d4071657131.png) "nastya" ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF778A/355fee5161a1808ee95ea5dc6d815d4071657131.png) "nastya" ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF778A/355fee5161a1808ee95ea5dc6d815d4071657131.png) "nastya" ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF778A/355fee5161a1808ee95ea5dc6d815d4071657131.png) "nastya" ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF778A/355fee5161a1808ee95ea5dc6d815d4071657131.png) "nastya" ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF778A/355fee5161a1808ee95ea5dc6d815d4071657131.png) "nastya".

Sergey knows this permutation. His goal is to stop his sister at some point and continue removing by himself to get the word $ p $ . Since Nastya likes this activity, Sergey wants to stop her as late as possible. Your task is to determine, how many letters Nastya can remove before she will be stopped by Sergey.

It is guaranteed that the word $ p $ can be obtained by removing the letters from word $ t $ .

## 说明/提示

In the first sample test sequence of removing made by Nastya looks like this:

"ababcba" ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF778A/355fee5161a1808ee95ea5dc6d815d4071657131.png) "ababcba" ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF778A/355fee5161a1808ee95ea5dc6d815d4071657131.png) "ababcba" ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF778A/355fee5161a1808ee95ea5dc6d815d4071657131.png) "ababcba"

Nastya can not continue, because it is impossible to get word "abb" from word "ababcba".

So, Nastya will remove only three letters.

## 样例 #1

### 输入

```
ababcba
abb
5 3 4 1 7 6 2
```

### 输出

```
3```

## 样例 #2

### 输入

```
bbbabb
bb
1 6 3 4 2 5
```

### 输出

```
4```

# 题解

## 作者：lixiao189 (赞：6)

## 题目大意：
如果有两个字符串 $ p ,t $ 和一个删除的顺序，按照这个顺序删除 $ p $ 中的字符，删几个的时候我们就无法通过剩下的字符得到 $ t $ , 或是 $ p $ 剩下的字符刚好为 $ t $ ，求删掉的字符的数量。
## 思路：
这个题目的思路大致的思路就是一个二分。首先我们考虑一个长度为 $ len $ 删除序列，我们按照这个删除序列删掉 $ n $ 个字符的时候的情况。此时我们还剩下 $ len-n $ 个字符没有被删除，那么如果剩下的字符中的子序列中存在一个子序列等于 $ t $ 那么就说明我们删掉 $ n $ 按照这个删除序列删掉 $ n $ 个字符的时候剩下的字符一定可以得到 $ t $ ，如果剩下的字符中的子序列中没有等于字符串 $ t $ 的话，那么就说明删掉 $ n $ 个字符后剩下的字符是不会的到字符串 $ t $ 的。所以我们就可以以这个依据去二分。

首先我们先二分一个右端点 $ mid $ ，意思是我们删除了下标为删除序列中的前 $ 1 \sim mid $ 个数的字符，然后对于剩下的字符，然后我们判断剩下的那些字符中是不是有子序列为 $ t $ 如果有那么说明右端点可以更大，那么我们去 $ mid+1 \sim n $ b中所求的答案，如果不可以那么说明我们要删更少的数那么我们就要去 $ l \sim mid-1 $ 中找右端点。

至于如何判断剩下的字符中是不是有子序列为 $ t $ 就看我的代码中的 `check()` 函数好了，这个比较简单我就不讲了。

## 代码：
```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 2e5+5;

int n=1,len1,len2,ans;
int operation[N]; //存储操作 
bool book[N]; //标记第二个字符串中出现过的字符 
char s1[N],s2[N];
vector <int> num; //后缀的编号 

bool check(int x){
	num.clear();
	for(register int i=x+1;i<=n;i++) 
		if(book[s1[operation[i]]]) num.push_back(operation[i]);
	sort(num.begin(),num.end()); //对编号进行排序 
	register int i=0,j=1;
	while(i<(int)num.size() && j<=len2){
		if(s1[num[i]]==s2[j]) i++,j++;
		else i++;
	}
	if(j==len2+1) return true;
	else return false;
}

inline void fuc(int l,int r){
	if(l>r) return;
	int mid=(l+r)>>1; //二分出右端点 
	if(check(mid)) ans=mid,fuc(mid+1,r);
	else fuc(l,mid-1);
}

int main(){
	scanf("%s",s1+1);
	scanf("%s",s2+1);
	//获取两个字符串的长度 
	len1=strlen(s1+1);
	len2=strlen(s2+1);
	while(scanf("%d",&operation[n])!=EOF){ ++n; } n--; 
	for(register int i=1;i<=len2;i++) book[int(s2[i])]=true;
	fuc(1,n);
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：jianhe (赞：4)

[CF778A String Game](https://www.luogu.com.cn/problem/CF778A)
题解

### 算法：二分
二分枚举什么？我们可以枚举**删除的元素个数**。

可行性？假设删去  $ x $ 个元素可行，那么删去 $ x - 1 $ 个元素也肯定可行。因此二分的序列有单调性，该二分成立。

`check` 函数怎么写？判断删掉 $ x $ 个元素后是否包含序列 $ t $ 即可。


### 代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll N=2e6+10;
ll n,nt,a[N],l,r,mid,ans;
string p,t;
bool check(ll x){
	string k=p;
	ll ct=0;
	for(int i=1;i<=x;i++) k[a[i]-1]=' ';
	for(int i=0;i<n;i++){
		if(k[i]==t[ct]) ct++;
		if(ct==nt) return 1; 
	}		
	return 0;
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>p>>t;
	n=p.size(),nt=t.size();
	for(int i=1;i<=n;i++) cin>>a[i];
	r=n;
	while(l<=r){
		mid=l+r>>1;
		if(check(mid)) ans=mid,l=mid+1;
		else r=mid-1;
	}
	cout<<ans;
	return 0;
}

```

---

## 作者：zhangqiuyanAFOon2024 (赞：2)

我们先读题，看到题目，我们的反应一定是二分。

二分什么？当然是二分答案，二分之后，可以根据数组删去，判断一下是否满足题意即可。

数据是 $200000$ 显然可以过。

思路简单，看代码吧。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int a[N],la,ls;
string ans,s;
bool check(int n){
	string t=s;
	for(int i=0;i<n;i++)
		t[a[i]-1]=' ';
	int id=0;
	for(int i=0;i<ls;i++)
		if(t[i]==ans[id]) id++;
	if(id==la) return 1;
	return 0;
}//判断是否满足题意
int main(){
	cin>>s>>ans;
	ls=s.size(),la=ans.size();
	for(int i=0;i<ls;i++)
		cin>>a[i];
	int l=1,r=ls,cnt=0;
	while(l<=r){
		int mid=(l+r)/2;
		if(check(mid)){
			cnt=mid;
			l=mid+1;
		}
		else r=mid-1;
	}//简单二分
	cout<<cnt;//输出答案
	return 0;
}
```

---

## 作者：Uuuuuur_ (赞：1)

二分练手题

不难看出，当删除次数越少时，$t$ 越有可能是 $p$ 的子序列，而我们要求最大的删除次数，所以，只要二分删除次数，然后判断 $t$ 是不是删除后的 $p$ 的子序列，时间复杂度 $O(n \log n)$

代码里有些细节：
```cpp
#include <bits/stdc++.h>
using namespace std;
string t, p;
int a[200005];
int ans;

bool check(int x) {
	string now = p;
	int pos = 0; //pos记录比对到t的哪个位置
	for (int i = 0; i < x; i++) {
		now[a[i] - 1] = ' '; 
	}
	for (int i = 0; i < p.size(); i++) {
		if (now[i] == t[pos]) {
			pos++; //比对成功，下一位
		}
	}
	if (pos == t.size()) return 1; //这里的pos注意，虽然最多比对到下标｜t｜- 1，但最后一位比对成功后，pos还会再加一
	return 0;
}
int main() {
	cin >> p >> t;
	for (int i = 0; i < p.size(); i++) {
		cin >> a[i];
	}
	int l = 0, r = p.size(); //最多删除次数是全删掉，所以上界就是｜p｜，最坏情况下一个也不能删，所以下界是0
	while (l <= r) {
		int mid = (l + r) >> 1;
		if (check(mid)) {
			ans = mid;
			l = mid + 1; //提升下界来尝试更大的删除次数
		} else {
			r = mid - 1; 
		}
	}
	cout << ans;
	return 0;
}
```


---

## 作者：Adolfo_North (赞：1)

二分答案的练手题，虽然很淼，但本题解提供一种清爽的解。

1. 首先，二分什么：

当然是二分可以删除的次数，并使用 `check` 函数判断该值是否合法。这点毋庸置疑。

2. `check` 怎么写。

首先，我们假设可以删除 $m$ 次。使用标记数组将 $a_1$ 到 $a_m$，所表示的字符串下标，置为不可使用。

然后拟定一个字符串 $b$ 的下标 $c$，遍历字符串 $a$，若 $b_c$ 与字符串 $a$ 当前位置上的字符相同，则 `c++`。

若 `c=b.size` 则该 $m$ 是合法的。反之，不合法。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
string a,t;
int b[200001];
bool f[200001];
int sizea,sizet;
bool check(int m){
	memset(f,0,sizeof f);//一定要清零。
	for(int i=1;i<=m;i++) f[b[i]-1]=1;//题中给出的下标是从1开始的，但字符串的下标是从0开始的，所以要-1。
	int cnt=0;
	for(int i=0;i<sizea;i++){
		if(!f[i]&&a[i]==t[cnt]) cnt++;//若相等，个数加一
		if(cnt==sizet) return 1;//合法。
	}
	return 0;
}
int main()
{
	cin>>a>>t;
	sizea=a.size();
	sizet=t.size();
	for(int i=1;i<=sizea;i++){
		cin>>b[i];
	}
	int l=0,r=sizea,mid,ans=0;
	while(l<=r){
		mid=(l+r)/2;
		if(check(mid)){
			ans=mid;
			l=mid+1;
		}
		else r=mid-1;
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：BLX32M_10 (赞：1)

## 题目概述

有一个字符串 $p$，又给出一个长度与 $p$ 相等的下标序列 $a$，删除字符串 $p$ 中的第 $a_1, a_2, a_3\cdots a_i$ $(1 \le i \le |p|)$ 个字符，求 $i$ 最多是多少，使得字符串 $p$ 中包含字符串 $t$。

## 题解

由于 $p$ 和 $t$ 的长度最多是 $200,0001$，所以 $\mathcal{O}(n^2)$ 暴力枚举肯定 TLE。

如何优化算法复杂度呢？ **二分！**

由于过于繁琐，以下部分中 $|p|$ 就用 $n$ 来表示啦

二分中，$l$ 的初始值是 $0$，$r$ 的初始值是 $n$，而中间值 $mid$ 则是从 $p$ 删除下标为 $a_1$ 到 $a_{mid}$ 的字符后还包含字符串 $t$，求 $mid$ 的最大值。

这样一来，原本枚举 $i$ 的部分时间复杂度复杂度 $\mathcal{O}(n)$ 就能变成 $\mathcal{O}(\log_2 n)$，总时间复杂度就是 $\mathcal{O}(n \log_2n)$，数据范围 $2 \times 10^6$ 就能过了。

值得一提的是，因为在二分内部枚举字符的过程中需要判断数组 $a$ 中是否有某一个值，并知道其在数组 $a$ 中的位置。为了提高效率，就需要用到映射。因为数据范围较小，可以直接用一个映射数组解决问题。

AC 代码如下：

```cpp
#include <string>
#include <iostream>
std::string a, b;
int hnum[200005], x;
//   ^映射数组
int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cin >> a >> b;
    for (int i = 0; i < a.size(); i++)
    	 std::cin >> x, hnum[x - 1] = i;
    int l = 0, r = a.size(), m;
    while (l + 1 < r)
    {
    	 m = (l + r) / 2, x = 0;
    	 for (int i = 0; i < a.size(); i++)
    		 if (a[i] == b[x] && m <= hnum[i])
    		 	x++;
    	 if (x == b.size())
    		 l = m;
    	 else
    		 r = m;
    }
    std::cout << l;
    return 0;
}
```

---

## 作者：yaaaaaan (赞：0)

### 思路
这道题是个二分练手题，首先二分删的次数 $x$，把数组前 $x$ 个位置对应的字符删掉，再与字符串进行对比，检查是否可行。可行就继续寻找有没有比 $x$ 大的答案，不可行就缩小范围寻找有没有比 $x$ 小的答案。

### code

```
#include <bits/stdc++.h>
#define int long long
#define endl "\n"
using namespace std;
string s,t;
int a[2000005];
bool check(int x)
{
	string ss=s;
	for(int i=0;i<x;i++)
	{
		ss[a[i]-1]=' ';
	}
//	cout<<ss<<"\n";
	int j=0;
	for(int i=0;i<ss.size()&&j<t.size();i++)
	{
//		cout<<x<<" "<<j<<" "<<t[j]<<" "<<ss[i]<<"\n";
		if(t[j]==ss[i]) 
		{
			j++;
		}
		
	}
//	cout<<"a="<<(j==t.size())<<"\n";
	return j==t.size();
}
signed main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>s>>t;
	for(int i=0;i<s.size();i++)
	{
		cin>>a[i];
	}
	int l=0,r=s.size()-t.size(),ans=0;
//	cout<<l<<" "<<r<<"\n";
	while(l<=r)
	{
		int mid=(l+r)>>1;
//		cout<<l<<" "<<r<<" "<<mid<<"\n";
		if(check(mid)) 
		{
			ans=mid;
//			cout<<"mid="<<mid<<"\n";
			l=mid+1;
		}
		else{
			r=mid-1;
		}
	}
	cout<<ans<<"\n";
	return 0;
}
```

---

## 作者：DecemberFox (赞：0)

# CF778A 题解

## 题目分析

本题的大致意思是给出两个字符串 $p$ 和 $t$，并将依次删除字符串 $p$ 的某一个字符，求解最多能够删除多少次并且保证字符串 $p$ 中包含字符串 $t$。

注意到删除一个字符后其后面的字符串位置仍然不变。

## 解法分析

首先考虑暴力解决，从全部删除开始向不删除依次查找，直到找到删除字符数量最多且仍然包含字符串 $t$ 的删除方式。最终复杂度为 $O(n^2)$，会超时，所以考虑优化。

我们发现，如果字符串 $p$ 在删除前 $k$ 个数仍然包含字符串 $t$，那么删除前 $k-1$ 个数字一定也包含字符串 $t$，因此就可以使用二分 $k$ 进行优化。

再考虑 `check` 函数的写法，我们可以将每个字符的删除次序记录下来，如果该字符的删除次序小于等于 $k$ 则表示该字符是被删除的，用此就可以 $O(n)$ 判断字符串 $p$ 是否包含 $t$ 了。

因为需要执行 $\log_2\,n$ 次 `check` 函数，所以总的时间复杂度为 $O(n\,\log_2\,n)$。

## 代码
```cpp
#include<iostream>
#include<cstdio>
#include<string>
namespace io
{
	void read()
	{
		return;
	}
	template<typename nowtype,typename ...nexttype>
	void read(nowtype &now,nexttype &...next)
	{
		register char c=getchar();
		register int n(1);
		now=0;
#define isdigit(c) ((c)>='0'&&(c)<='9')
		while(!isdigit(c)){if(c=='-') n=-1;c=getchar();}
		while(isdigit(c)){now=(now<<1)+(now<<3)+(c^48);c=getchar();}
#undef isdigit
		now*=n;
		read(next...);
	}
	template<typename nowtype>
	void write(nowtype num,char end='\n')
	{
		register unsigned long long unum(0);
		if(num<0) putchar('-'),unum=-num;
		else unum=num;
		register int c[35],top(0);
		do c[top++]=unum%10,unum/=10;while(unum);
		while(top) putchar(c[--top]+48);
		putchar(end);
	}
	template<typename nowtype,typename ...nexttype>
	void write(nowtype num,char end,nexttype ...next)
	{
		register unsigned long long unum(0);
		if(num<0) putchar('-'),unum=-num;
		else unum=num;
		register int c[35],top(0);
		do c[top++]=unum%10,unum/=10;while(unum);
		while(top) putchar(c[--top]+48);
		putchar(end);
		write(next...);
	}
}
using namespace io;
//以上为快读和快写
namespace SOLVE
{
	typedef long long ll;
	typedef unsigned long long ull;
	typedef __int128 lll;
	typedef unsigned __int128 ulll;
	const int const1=2e6+10;
	std::string p,t;
	int del[const1];
	bool check(int pos) //判断字符串 p 是否包含字符串 t
	{
		int i,j(0),l=p.size(),r=t.size();
		for(i=0;i<r;++i)
		{
			while(j<l&&(p[j]!=t[i]||del[j+1]<=pos)) ++j;
			if(j==l) return false; //将字符串 p 找完了但仍不包含字符串 t
			++j;
		}
		return true;
	}
	void solve()
	{
		std::cin>>p>>t;
		int i,n,l(1),r=p.size(),ans(0);
		for(i=1;i<=r;++i)
		{
			read(n);
			del[n]=i;
		}
		while(l<=r) //二分
		{
			int mid=(l+r)>>1;
			if(check(mid)) ans=mid,l=mid+1;
			else r=mid-1;
		}
		write(ans);
	}
}
int main()
{
	SOLVE::solve();
	return 0;
}
```

---

## 作者：xvl_ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF778A)

一道二分题。

$|p|\le2\times10^6$，考虑 $O(n\log n)$ 的算法，而又要输出最大值，不难想到二分答案。

二分删除字母的数量，用一个数组将删掉的字母的下标存起来，然后判断删除字符后的 $t$ 是否是 $p$ 的子序列即可。

### Code

```cpp
#include <bits/stdc++.h>
#define ll long long
#define INF 1e9
using namespace std;
string t, p;
int ans;
int a[200005];
bool removed[200005]; // removed[i] 表示 i 下标上的字母已被删除
bool check(int x) {
    if (x > t.size()) return 0;
    int cnt = 0;
    memset(removed, 0, sizeof(removed));
    for (int i = 1; i <= x; i++) removed[a[i]] = 1;
    for (int i = 0; i < t.size(); i++) {
        if (removed[i + 1]) continue; 
        if (t[i] == p[cnt]) cnt++;
    }
    if (cnt == p.size()) return 1; 
    return 0;
}
void f(int l, int r) {
    while (l <= r) {
        int mid = (l + r) / 2;
        if (check(mid)) {
            l = mid + 1;
            ans = mid; // 求最大值
        }
        else r = mid - 1;
    }
}
signed main() {
    ios :: sync_with_stdio(0);
    cin >> t >> p;
    for (int i = 1; i <= t.size(); i++) cin >> a[i];
    f(1, 200000);
    cout << ans;
    return 0;
}
```


---

## 作者：SUNCHAOYI (赞：0)

删除字母的个数显然越多越好，再看题目中的 `Note that after removing one letter, the indices of other letters don't change.` 这句话，意思是**删除一个字母后，其他字母的索引不会更改**。因此可以二分可以删除的字母的个数，最后输出最大值。

首先确定二分的范围，由数据范围可知，$p$ 串最少删除的字母数量为 $0$。又因为再删除若干个字母后的长度一定不比 $t$ 串的长度小，那么设两个串的长度分别为 $lenp,lent$，则最多删除的字母数量为 $lenp - lent$。

其次再来思考删除字母后判断 $p$ 串中是否仍存在 $t$ 串的方式。先计算出被删除若干个字母的新 $p$ 串，然后利用两个指针 $dx,dy$，分别表示新 $p$ 串与 $t$ 串的匹配状态。通过 `while` 循环，逐一判断，显然能成功匹配的条件是 $dy = lent$，即表示 $t$ 串中的所有字母都在新 $p$ 串中按顺序出现。

通过二分答案，大大地减少了搜索的次数，时间复杂度也变为 $O(n \log n)$，$n$ 表示 $p$ 串的长度。完整代码如下：

```
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#define init(x) memset (x,0,sizeof (x))
#define ll long long
#define ull unsigned long long
#define INF 0x3f3f3f3f
using namespace std;
const int MAX = 2e5 + 5;
const int MOD = 1e9 + 7;
inline int read ();
int lena,lenb,cnt,num[MAX];
char a[MAX],b[MAX],str[MAX];
bool del[MAX];
bool check (int x);
int main ()
{
	//freopen (".in","r",stdin);
	//freopen (".out","w",stdout);
	scanf ("%s%s",a,b);
	lena = strlen (a);lenb = strlen (b);
	for (int i = 1;i <= lena;++i) num[i] = read ();
	int l = 0,r = lena - lenb;//确定范围
	while (l <= r)//二分答案
	{
		int mid = (l + r) >> 1;
		if (check (mid)) l = mid + 1;
		else r = mid - 1;
	}
	printf ("%d\n",l - 1);
	return 0;
}
inline int read ()
{
    int s = 0;int f = 1;
    char ch = getchar ();
    while ((ch < '0' || ch > '9') && ch != EOF)
	{
        if (ch == '-') f = -1;
        ch = getchar ();
    }
    while (ch >= '0' && ch <= '9')
	{
        s = s * 10 + ch - '0';
        ch = getchar ();
    }
    return s * f;
}
bool check (int x)
{
	for (int i = 1;i <= lena;++i) del[i] = 0;//初始化
	for (int i = 1;i <= x;++i) del[num[i]] = 1;//删除的字母的下标标记为 1
	cnt = 0;
	for (int i = 0;i < lena;++i)
		if (!del[i + 1]) str[++cnt] = a[i];//构成新字符串 p
	int dx = 1,dy = 0;
	while (dx <= cnt && dy < lenb)//循环逐一比较
	{
		if (str[dx] == b[dy]) ++dx,++dy;
		else ++dx;
	}
	if (dy != lenb) return 0;//没有完全匹配
	else return 1;//能完全匹配
}
```

---

