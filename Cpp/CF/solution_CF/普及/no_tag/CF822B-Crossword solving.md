# Crossword solving

## 题目描述

Erelong Leha was bored by calculating of the greatest common divisor of two factorials. Therefore he decided to solve some crosswords. It's well known that it is a very interesting occupation though it can be very difficult from time to time. In the course of solving one of the crosswords, Leha had to solve a simple task. You are able to do it too, aren't you?

Leha has two strings $ s $ and $ t $ . The hacker wants to change the string $ s $ at such way, that it can be found in $ t $ as a substring. All the changes should be the following: Leha chooses one position in the string $ s $ and replaces the symbol in this position with the question mark "?". The hacker is sure that the question mark in comparison can play the role of an arbitrary symbol. For example, if he gets string $ s $ ="ab?b" as a result, it will appear in $ t $ ="aabrbb" as a substring.

Guaranteed that the length of the string $ s $ doesn't exceed the length of the string $ t $ . Help the hacker to replace in $ s $ as few symbols as possible so that the result of the replacements can be found in $ t $ as a substring. The symbol "?" should be considered equal to any other symbol.

## 样例 #1

### 输入

```
3 5
abc
xaybz
```

### 输出

```
2
2 3 
```

## 样例 #2

### 输入

```
4 10
abcd
ebceabazcd
```

### 输出

```
1
2 
```

# 题解

## 作者：Dream__Sky (赞：3)

以下所用的变量名，除有特殊说明，均与题目含义相同。

可以发现，两个字符串长度均不超过 $1000$，考虑暴力枚举。

因为要把 $s$ 用问号改成 $t$ 的字串，那我们可以在 $t$ 上，枚举每一个字串的开头 $i$，从 $i$ 往下找 $n$ 位，求出当 $t_i$ 作为开头时需要的问号数量，即对应位置字符不同的数量。每次更新最小值，别忘了要记录位置。时间复杂度为 $O(n^2)$。

要注意开头位置，即 $i$ 的取值范围为 $1 \le i \le m-n+1$。即字串的右端不能超过 $m$。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,daan=2e9;
string s,t;
vector<int> v;
int main()
{
	cin>>n>>m;
	cin>>s>>t;
	s=" "+s;
	t=" "+t;//为了方便处理，将字符串下标从一开始。
	for(int i=1;i<=m-n+1;i++)//重点，枚举开头，注意i的范围
	{
		int sum=0;
		for(int j=1,k=i;j<=n;j++,k++)
			if(s[j]!=t[k]) sum++;//求问号个数
		if(sum<daan)
		{
			daan=sum;
			v.clear();
			for(int j=1,k=i;j<=n;j++,k++)
				if(s[j]!=t[k]) v.push_back(j);
		}//更新最小值
	}
	cout<<daan<<'\n';
	for(auto i:v) cout<<i<<" ";
	return 0;
}


```



---

## 作者：The_jester_from_Lst (赞：2)

# 考虑暴力枚举。

由于两个字符串 $s$，$t$ 长度皆不超过 $1000$，我们直接暴力枚举字符串 $t$ 的每一位，让它往下搜索 $n$ 位，对于这 $n$ 位，每一个与 $s$ 的对应位不一样的我们都用一个数组 $c$ 把它的位置存起来，并统计总数。当该总数小于目前最小值时，我们更新最小值并把数组 $c$ 中的内容复制到答案数组 $a$，注意，此时要**清空数组 $c$**。

最后输出即可。

附上代码：
```cpp
#include<bits/stdc++.h>
#define int long long
#define mod 1e9+7
using namespace std;
inline int rd(){
	int jya=0,ysc=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')ysc=-1;ch=getchar();}
	while(isdigit(ch)){jya=jya*10+(ch-'0');ch=getchar();}
	return jya*ysc;
}
inline void wr(int x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)wr(x/10);
	putchar(x%10+'0');
}
int n,m,a[1086],minn=INT_MAX,c[1086];
char s[1086],t[1086];
signed main(){
	n=rd();m=rd();
	for(int i=1;i<=n;++i)cin>>s[i];
	for(int i=1;i<=m;++i)cin>>t[i];
	for(int i=1;i<=m-n+1;++i){
		int sum=0;
		for(int j=i;j<=i+n-1;++j)if(s[j-i+1]!=t[j])c[++sum]=j-i+1;
		if(sum<minn){
			minn=sum;
			for(int i=1;i<=minn;++i)a[i]=c[i];
			memset(c,0,sizeof c);
		}
	}
	wr(minn);
	putchar('\n');
	for(int i=1;i<=minn;++i)wr(a[i]),putchar(' ');
	return 0;
}
```


---

## 作者：封禁用户 (赞：1)

~~第一篇是我们机房巨佬写的，大家点点赞。~~

题意很简单，直接上思路。

我们可以用双层循环来做。外层循环从 $i$ 开始枚举，表示枚举到 $s2$ 这个字符串的第 $i$ 个位置。**然后我们可以截取从当前的第 $i$ 位到第 $i+s$ 位，然后与 $s1$ 字符串比较，把不相同的字母个数记录下来，同时记录下位置，再进行比较就可以了。**

***Code***
```cpp
#include <bits/stdc++.h>
using namespace std;
int s, t, minn = 1e9, k, b[100100];//minn要赋值为较大值
string s1, s2;
int main()
{
	cin >> s >> t;
	cin >> s1 >> s2;
	for(int i = 0; i < t - s; i ++)
	{
		int sum = 0, a[100100], t = 0;//sum为要改变字母的个数，t为a数组的长度。
		memset(a, 0, sizeof a);//a数组表示记录要改变字母的位置
		for(int j = i, l = 0; j < i + s; j ++, l ++) 
		if(s2[j] != s1[l]) sum ++, a[++ t] = l + 1;
		if(sum < minn)//判断
		{
			minn = sum;
			for(int j = 1; j <= t; j ++) b[j] = a[j];
			k = t;
		}
	}
	cout << k << endl;
	sort(b + 1, b + 1 + k);
	for(int i = 1; i <= k; i ++) cout << b[i] << ' ';
	return 0;
}
```

---

## 作者：LouYiYang1 (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/CF822B)
## 思路
因为此题样例较小，所以可以暴力，先求出不同的地方的个数，再跟最小值比较，如果小于最小值就更新。
# AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,as=1e9,sum;
string a,b;
int ans[1005];
int main(){
	cin>>n>>m>>a>>b;
	a="#"+a;
	b="#"+b;
	for(int i=1;i<=m-n+1;i++){
		int cnt=0;
		for(int j=1,k=i;j<=n;j++,k++)if(a[j]!=b[k])cnt++;
		if(as>cnt){
			as=cnt;
			memset(ans,0,sizeof ans);
			sum=0;
			for(int j=1,k=i;j<=n;j++,k++)if(a[j]!=b[k])ans[++sum]=j;
		}
	}
	cout<<as<<'\n';
	for(int i=1;i<=sum;i++)cout<<ans[i]<<' ';
	return 0;
}
```

---

## 作者：Hutao__ (赞：0)

## 思路
我们看到 $n \le m \le 1000$，由此我们考虑暴力。

先求出不同的地方的个数，在跟最小值比较，如果小于最小值就更新。

## 代码


```cpp
//lgRMJ坏了，此代码不能保证通过此题
#include<bits/stdc++.h>
using namespace std;
int n,m,as=1e9,kkk;
string a,b;
int ans[1005];
int main(){
	cin>>n>>m>>a>>b;
	a="#"+a;
	b="#"+b;
	for(int i=1;i<=m-n+1;i++){
		int kk=0;
		for(int j=1,k=i;j<=n;j++,k++)if(a[j]!=b[k])kk++;//统计不同的个数
		if(as>kk){
			as=kk;//更新最小值
			memset(ans,0,sizeof ans);
			kkk=0;
			for(int j=1,k=i;j<=n;j++,k++)if(a[j]!=b[k])ans[++kkk]=j;//更新答案
		}
	}
	cout<<as<<'\n';
	for(int i=1;i<=kkk;i++)cout<<ans[i]<<' ';
}
```

---

## 作者：HUANGRUI11 (赞：0)

我爱暴力我自豪！

由于 $1 \le n,m \le 1000$，所以直接考虑暴力枚举。
用 $i$ 枚举 $t$ 中子串的开头，然后从 $i$ 循环到 
$i+n-1$，而 $1 \le i \le m-n+1$，将 $t_i$ 与 $s_j$ 不同的个数统计出来，并用 $a$ 数组储存下来，再与 $ma$ 打个擂台，如果比 $ma$ 小，将 $b$ 数组的值都赋成 $a$，最后输出即可。

代码就不展示了。

---

## 作者：Linzijun_0607 (赞：0)

### 思路

看数据范围 $1 \le n\le m \le 1000$，很容易想到暴力枚举。

先枚举 $s_1$ 对应的 $t_i$ 的第一个字符，然后往后看改需要多少字符能让字符串 $s$ 成为字符串 $t$ 已 $t_i$ 为第一个字符的子串，最后取最大即可。

注意，$s_i$ 的下标 $i$ 不能在枚举时超过 $m$。

### 代码:
```cpp
#include<bits/stdc++.h>
using namespace std;
bool change[1005],ans[1005];
int main(){
	int n,m;
	string s,t;
	cin>>n>>m;
	cin>>t>>s;
	s=" "+s;
	t=" "+t;
	int mn=0x3f3f3f3f;
	for(int i=1;i<=m;++i){ // 枚举s第一个字符
		int sum=0;
		for(int j=1;j<=n;++j){ //往后查需要改多少个字符
			if(j+i-1>m){ //下标出范围了
				sum=1e9;
				break;
			}
			if(s[j+i-1]!=t[j]) change[j]=1,++sum; 
		}
		if(mn>sum){
			mn=sum;
			for(int j=1;j<=n;j++) ans[j]=change[j];//保存修改的位置
		}
		memset(change,0,sizeof change); //重置
	}
	printf("%d\n",mn);
	for(int i=1;i<=n;i++) if(ans[i]) printf("%d ",i);
}
```

---

## 作者：_xxxxx_ (赞：0)

### 题意

给出两个字符串 $s$ 和 $t$，现在想使得 $s$ 成为 $t$ 的字串。可以将 $s$ 中的一个字符变成 `?`，问号可以变成任意字符，问最少需要改动多少个字符。

### 分析

对于 `?`，其实就是**不匹配的字母个数**，发现 $n \le 1000$，考虑暴力。

在 $t$ 中枚举每一个点将 $s$ 匹配上，看 $s$ 中有多少的字符与 $t$ 当前不同，维护一个最小值，比最小值小时就更新答案。此时最小值就是答案。时间复杂度 $O(n^2)$。

想要进一步优化，也可以自行尝试，可以有更优秀的复杂度。对于数据范围接受时，就可以使用暴力解决。

### 代码
```cpp
#include <bits/stdc++.h>
const int N = 1e3 + 10;
using namespace std;
string s, t;
int ls, lt;
//ls (lens): s 的长度
//lt (lent): t 的长度
int ans[N], now[N];
//ans:答案
//now:目前的不匹配位置 
signed main()
{
	cin >> ls >>lt;
	cin >> s;
	cin >> t;
	s = "!" + s, t = "!" + t;//下标改从1开始 
	int minn = ls;//最小值 
	for(int i = 1; i <= lt - ls + 1; i++)//不要遍历出t 
	{
		int cnt = 0;//不相同的个数 
		for(int j = 1; j <= ls; j++)
		{
			//找出不相同的字母 
			if(t[i + j - 1] != s[j])
			{
				cnt++;
				now[cnt] = j; 
			}
		}
		if(cnt > minn) continue;
		minn = min(minn, cnt);//更少？ 
		for(int j = 1; j <= cnt; j++) ans[j] = now[j];
		//换成答案 
	}
	cout <<minn <<endl;
	for(int i = 1; i <= minn; i++) cout <<ans[i] <<" ";
	return 0;
}
/*
4 6
abcd
abcfgf
*/
```

---

## 作者：xuduang (赞：0)

## 题目大意

给两个字符串 $s$ 及 $t$，问将 $s$ 修改成 $t$ 最少需要改多少个字符，并输出它们在 $s$ 中的位置。

## 解题

$n \le 10^3$ 可以放心的使用 $O(n^2)$ 的暴力。

从 $t$ 的每个点开始找长度与 $s$ 相同的一个串，则这个串是 $t$ 的子串，最后看将 $s$ 修改成这个串需要多少次操作即可。每次更新记录下答案输出。

## code

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m;
string s,t;
int a[1005],cnt;
int main()
{
	cin>>n>>m;
	cin>>s>>t;
	s=" "+s,t=" "+t;
	int ans;
	cnt=1e9;
	for(int i=1;i<=m-n+1;i++)
	{
		ans=0;
		for(int j=0;j<n;j++)
		{
			if(s[j+1]!=t[i+j])ans++;//找不同 
		}
		if(ans<cnt)
		{
			cnt=ans;
			ans=0;
			for(int j=0;j<n;j++)
			{
				if(s[j+1]!=t[i+j])a[++ans]=j+1;//记录下答案 
			}
		}
	}
	cout<<cnt<<endl;
	for(int i=1;i<=cnt;i++)cout<<a[i]<<" ";
	return 0;
}
```

---

## 作者：LaDeX (赞：0)

## 题意

给定字符串 $S,T$，可将 $S$ 中的字符修改为 $\mathtt{?}$。

若一个字符为 $\mathtt{?}$，则这个字符可代替任何一个字符。

问最少修改 $S$ 中的几个字符，可将 $S$ 变为 $T$ 的字串。

## 解法

由于 $n,m\leq 1000$，所以可以朴素枚举 $S$ 在 $T$ 中字串的开头位置，再判断有几个字符不同，不同的字符存入 `tmp` 数组中，最后取最小值，如果比当前答案长度优，不仅更新答案长度，还要 _更新更改的下标数组_ 。

**要注意枚举开头位置是从 $1$ 枚举到 $m-n+1$（字符串第一个字符下标为 $1$），不然第 $27$ 个点会炸掉**。

## Code

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
#define Fcin \
	ios :: sync_with_stdio(0);\
	cin.tie(0);cout.tie(0);
const LL N = 1010;
LL n, m, Len = 1e18, Ans[N], tmp[N];
string S, T;
int main(){
	Fcin;
	cin >> n >> m >> S >> T;
	S = '#' + S;
	T = '#' + T;
	for (LL i = 1; i <= m - n + 1; i ++){
		LL cnt = 0;
		memset(tmp, 0, sizeof(tmp));
		for (LL j = 1; j <= n; j ++){
			if (T[i + j - 1] != S[j])
				tmp[++ cnt] = j;
		}
		if (Len > cnt){
			Len = cnt;
			memset(Ans, 0, sizeof(Ans));
			for (LL i = 1; i <= cnt; i ++)
				Ans[i] = tmp[i];
		}
	}
	cout << Len << "\n";
	for (LL i = 1; i <= Len; i ++)
		cout << Ans[i] << " ";
	return 0;
}
```


---

## 作者：FiraCode (赞：0)

## 题解思路：
枚举 $t$ 的每一个字母作为开头，然后再和 $s$ 比较，记录一下哪里不一样就要改，最后对这些修改的序列取长度最小的就可以了，长度一样的话，随便一个就可以了。

## AC Code
```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdio>
#include <vector>
#include <string>
using namespace std;
int n , m;
string a , b;
int main(){
	//freopen ("temp.in" , "r" , stdin);
	scanf ("%d%d" , &n , &m);
	cin >> a >> b;
	vector <int> ans(114514 , 1);//因为要取min，所以先把长度设成很大的值。
	for (int i = 0; i < m - n + 1; ++ i) {//枚举每一个t里的字母
		vector <int> temp;
		for (int j = 0; j < n; ++ j) 
			if (a[j] != b[i + j]) //只要不一样就要是 ？
				temp.push_back (j);//那么操作就加上j
		if (temp.size() < ans.size()) //更新答案
			ans = temp;
	}
	printf ("%d\n" , ans.size());
	for (int i = 0; i < ans.size(); ++ i)//输出
		printf ("%d " , ans[i] + 1);
	puts("");
	return 0;
}
```

---

## 作者：SUNCHAOYI (赞：0)

对于输入的两个字符串 $s,t$，要修改 $s$ 中尽可能少的字符，使其能在字符串 $t$ 中被查找到。

直接想到最朴素的枚举算法，枚举字符串 $t$ 的左端点，因字符串 $s$ 的长度不变，所以右端点也能够同时被确定。然后每次判断当字符串 $s$ 修改为字符串 $t$ 中等长的某一段时，需要修改的字符数量，也就是两者不相同的字符的数量。当答案有更新的时候，同时记录下需要修改的每一个位置。

核心代码如下：

```cpp
for (int i = 1;i <= m - n + 1;++i)//枚举左端点，注意范围
{
	int tot = 0;//计数器的初始化
	for (int j = 1,k = i;j <= n;++j,++k)
		if (a[j] != b[k]) ++tot;//两者不同的数量
	if (tot < ans)//出现更优的答案
	{
		cnt = 0;ans = tot;//更新答案
		for (int j = 1,k = i;j <= n;++j,++k)//依次记录每一个位置
			if (a[j] != b[k]) num[++cnt] = j;
	}
}
```

---

## 作者：AC_love (赞：0)

字符串近似匹配问题。

其实有很多专门解决字符串近似匹配问题的算法，但是那些算法在 OI 界中并不常见。不过观察此题数据范围只有 $1000$，所以可以直接暴力匹配，复杂度为 $O(nm)$。

不妨暴力枚举 $t$ 的左端点，然后拿 $s$ 直接暴力对应 $t$ 的每一个部分。

可以加一些最优性剪枝，例如如果当前不匹配的字符个数已经大于 `ans` 就直接 `break` 掉，但是似乎没必要，亲测加了之后一毫秒都没变快。

还有两点需要注意：

1. 这道题里字符串下标从 $1$ 开始。
2. 如果发现更优解，那么在更新答案的同时，也要更新修改的位置。

需要注意的是，如果你使用了 ``char`` 数组，那么像这样的写法在最新版 C++ 里已经不再支持：

```cpp
  cin >> s + 1;
```

在最新版 C++ 里使用这样的语句会 CE，在国内比赛的时候应该不会出问题，但是如果线上赛没注意选择的语言这么交上去可能就会寄掉，在一些赛制里会吃到罚时（别问我怎么知道的，问就是踩过雷）。

我推荐使用这样的读入（我自己就是这么写的）：

```cpp
for(int i = 1; i <= n; i = i + 1)
	while(s[i] < 'a' || s[i] > 'z')
		s[i] = getchar();
```

代码实现如下：

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1114;
int n, m;
char s[N], t[N];
int ans;
vector <int> v;

int main()
{
	cin >> n >> m;
	ans = n + 1;
	for(int i = 1; i <= n; i = i + 1)
		while(s[i] < 'a' || s[i] > 'z')
			s[i] = getchar();
	for(int i = 1; i <= m; i = i + 1)
		while(t[i] < 'a' || t[i] > 'z')
			t[i] = getchar();
	for(int i = 1; i + n - 1 <= m; i = i + 1)
	{
		int tot = 0;
		for(int j = 1; j <= n; j = j + 1)
			if(t[i + j - 1] != s[j])
			{
				tot += 1;
				if(tot >= ans)
					break;
			}
		if(tot < ans)
		{
			v.clear();
			ans = tot;
			for(int j = 1; j <= n; j = j + 1)
				if(t[i + j - 1] != s[j])
					v.push_back(j);
		}
	}
	cout << ans << "\n";
	for(int i = 0; i < v.size(); i = i + 1)
		cout << v[i] << " "; 
	return 0;
}
```

---

