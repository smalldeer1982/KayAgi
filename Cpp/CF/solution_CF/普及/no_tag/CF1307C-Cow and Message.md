# Cow and Message

## 题目描述

贝茜刚刚截取了来自约翰发送出去的讯息！但是，贝茜很肯定里面一定有隐藏的讯息。

讯息是一个字符串 $s$ ，全部都是由小写拉丁字母字符构成。她认为一个字符串 $t$ 是隐藏的当且仅当 $t$ 是 $s$ 的子序列且 $t$ 在 $s$ 中出现的下标构成了一个等差数列（公差必须为一个**正整数**）。

例如，字符串`aab`是隐藏在字符串`aaabb`因为`aab`出现在$s$的下标$1,3,5$，这刚好构成了一个等差数列，而公差是 $2$。贝茜觉得秘密讯息讯息一定是隐藏最多次的那一个字符串。两个 $s$ 中的子序列是不同的当且仅当两个字符串在 $s$ 中出现的下标是不同的。 请帮贝茜找出秘密讯息在 $s$ 中出现的次数吧。

例如，在字符串`aaabb`中，

`a`隐藏了 $3$ 次，

`b`隐藏了 $2$ 次，

`ab`隐藏了 $6$ 次，

`aa`隐藏了 $3$ 次，

`bb`隐藏了 $1$ 次，

`aab`隐藏了 $2$ 次，

`aaa`隐藏了 $1$ 次，

`abb`隐藏了 $1$ 次，

`aaab`隐藏了 $1$ 次，

`aabb`隐藏了 $1$ 次，

`aaabb`隐藏了 $1$ 次，

秘密讯息出现的次数是 $6$ 次。

## 样例 #1

### 输入

```
aaabb```

### 输出

```
6```

## 样例 #2

### 输入

```
usaco```

### 输出

```
1```

## 样例 #3

### 输入

```
lol```

### 输出

```
2```

# 题解

## 作者：Reanap (赞：6)

这道题实际上是一道贪心猜结论题 
~~本次比赛的第三道贪心题~~

根据经验猜到以下结论：

结论：秘密信息必然是由长度为$1$或长度为$2$的子序列构成。

~~先猜再证，讲究~~

证明：

因为题目中要求等差，所以在同一长度的序列中，确定了前两个字符的位置，整个序列便已经确定（即两个字母就能代表很多个串）。假设长度大于$2$的序列是秘密信息，那么我们取这种序列的前两个字符，同样可以构成数量相等的长度为$2$的子序列。

因此长度为$2$的序列的最优解必然包含了长度大于$2$的最优解。但还有一种情况不要漏掉哦，就是长度为$1$的子序列哦。

剩下的就是一个模拟了。

我们先维护一个后缀和$suf_{i,j}$表示第$i$个位置到最后一个位置共有多少个$j$字母。然后从前到后枚举每一个字母，根据乘法原理，将组合出来的序列放入一个答案数组中，最后统计一波结果。

还不太明白的小伙伴可以看一看代码：

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN = 1e5 + 5;
char s[MAXN];
int suf[MAXN][30];
long long ans[30][30];//统计答案，由i,j组成的字符序列的个数
int main() {
	scanf("%s" , s + 1);
	int len = strlen(s + 1);
	for (int i = len; i >= 1; --i) {
		suf[i][s[i] - 'a'] ++;
		for (int j = 0; j < 26; ++j) {
			suf[i][j] += suf[i + 1][j];//后缀和
		}
	}
	for (int i = 1; i < len; ++i) {
		for (int j = 0; j < 26; ++j) {
			ans[s[i] - 'a'][j] += suf[i + 1][j];
            //当前是字母s[i],他之后有26种字母可以与他组合，加上这些同种组合
		}
	}
	long long res = -1;
	for (int i = 0; i < 26; ++i) {
		for (int j = 0; j < 26; ++j) {
			res = max(res , ans[i][j]);
		}
		res = max(res , (long long)suf[1][i]);
	}
	
	printf("%lld" , res);
	return 0;
}


```

---

## 作者：流绪 (赞：3)

### 贪心模拟！

给一个字符串，求其出现次数最多的子字符串出现了几次。

我们可以发现这个子字符串一定小于等于两个字母。如果是三个字母，那么他一定可以看做是两个字母再加上一个字母，三个字母的出现次数小于等于两个字母，因为三个字母的出现了，两个字母也出现了，两个字母出现了，三个字母不一定出现。

两个字母和一个字母的情况无法取最优，比如第一个字母 a 有 x 个,第二个字母b 有 y 个。

那么一个字母的答案是 max(x,y)

两个字母的答案是 max(1*a1+1*a2+...+1*ax,1*b1+1*b2+...+1*by) ax，by为第一个字母后面出现了几次第二个字母。上下两式在未算出结果前，无法明确比较大小。（证明很粗糙，大佬勿喷...）

所以我们把两个字母和一个字母的情况算出来，取最大值即可。

一个字母的很好算，输入时计数即可。

两个字母的我们输入的时候先预处理每个字母的前缀和，然后后面查询计算即可。

下面是 AC 代码，细节注释代码里了。
```cpp
#include<bits/stdc++.h>
#define ll long long
#define ld long double
#define inf 0x7f7f7f7f
#define maxn 100010
#define mod 10
using namespace std;
char a[maxn];
int cnt[200]={0};
ll f[maxn][30]={0};
int main()
{
	ios::sync_with_stdio(false);
	cin >> (a+1);
	int len = strlen(a+1);
	int cc = 0;
//	cout << len <<endl;
	for(int i=1;i<=len;i++)
	{
		cnt[a[i]]++;				//计数处理
		for(int j=0;j<26;j++)
			if(a[i]-'a' == j)
				f[i][j] = f[i-1][j]+1;
			else
				f[i][j] = f[i-1][j];//预处理前缀和
	}
	ll s1=0,s2=0;
	for(int i='a';i<='z';i++)
	{
		if(cnt[i] > s1)
			s1=cnt[i];				//取单个字母出现的最大值
	}
	ll ans = 0,sum=0;
	for(int i='a';i<='z';i++)		//枚举第一个字母
	{	
		for(int k=0;k<26;k++)		//枚举第二个字母
		{
			s2 = i;
			ans = 0;
			for(int j=1;j<=len;j++)//遍历字符串
			{
				if(a[j]==(char)s2)//若当前是第一个字母,计算他与后面的
				{				  //第二个字母有几种可能
					ll p = 0;	
					p = max(f[len][k]-f[j][k],p);
					ans +=p;
				}
			} 
			sum = max(ans,sum);	//计算所有第一个字母的情况和
		}
	}
	sum = max(sum,s1);取一个字母和两个字母的最大值
	cout << sum;
	return 0; 
} 
```


---

## 作者：朝夕 (赞：3)

## 解题思路
我们对字符串进行分析可以发现，隐藏次数最多的只可能是由两个字母或一个字母所组成的子串。

为什么？

假设有一由三个字母组成的子串abc，则每当其出现1次时，子串ab和ac必然也出现1次。同理，当多个字母组成的子串出现1次时，该子串内任意两个字母组成的子串也会出现1次。所以我们只需要考虑由两个以下字母组成的子串的隐藏次数。

之所以需要考虑一个字母所组成的子串，是因为字符串长度可能为1，所以必须要考虑。

至于如何计算隐藏次数，我们可以开一个26*26的二维数组，用于记录。

PS:这题和1311的C处理方法有点类似。

## 参考代码
```cpp
#include <bits/stdc++.h>
using namespace std;
string s;
long long vis[200];
long long occ[200][200];
int main()
{
    ios::sync_with_stdio(false);
    cin>>s;
    int len=s.size();
    long long ans=0;
    memset(vis,0,sizeof(vis));
    memset(occ,0,sizeof(occ));
    for(int i=0;i<len;i++)//对于在位置n的字母，位置1~n-1的字母与其组成的子串，隐藏次数都会+1
    {
        for(int j=97;j<=122;j++)//对应26个小写字母
        {
            if(vis[j])//如果在此之前出现了x次
            {
                occ[j][s[i]]+=vis[j];//则组成子串隐藏次数多了x次
                ans=max(ans,occ[j][s[i]]);
            }
        }
        vis[s[i]]++;
        ans=max(ans,vis[s[i]]);
    }
    printf("%lld\n",ans);
    return 0;
}
```


---

## 作者：LJQ0808 (赞：2)

[传送门](https://www.luogu.com.cn/problem/CF1307C)


题解

我们观察到，如果出现次数最多的隐藏字符串的长度大于 $2$，那么一定存在一个出现次数恰好为 $2$ 的隐藏字符串。

这是真的，因为我们总是可以只取前两个字母；不可能有任何碰撞。因此，我们只需要检查长度为 $1$ 和 $2$ 的字符串。检查长度为 $1$ 的字符串很容易。

为了检查长度为 $2$ 的字符串，我们可以从左到右遍历 $s$，并更新我们看到每个长度为 $1$ 的字符串的次数
 $2$ 个使用 DP。

AC code:

```
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=26;
string s;
ll a[N+5],b[N+5][N+5];
signed main(){
	//HAPPY!
	cin.tie(0);
	cout.tie(0);
	ios_base::sync_with_stdio(0);
	cin>>s;
	int len=s.size();
	for(int i=0;i<len;i++){
		int num=s[i]-'a';
		for(int j=0;j<N;j++){
			b[j][num]+=a[j];
		}
		a[num]++;
	}
	ll ans=0;
	for(int i=0;i<N;i++){
		ans=max(ans,a[i]);
		for(int j=0;j<N;j++){
			ans=max(ans,b[i][j]);
		}
	}
	cout<<ans<<"\n";
	return 0;
}
```

thanks for "FieryPhoenix"

---

## 作者：_Ad_Astra_ (赞：1)

[博客](https://www.luogu.com.cn/blog/ycxblogtijie/solution-cf1307c)食用效果更佳。

一道贪心~~水~~题。

可以证明出现次数最多的答案一定是一个或者两个字符，因为如果有三个或以上个字符，必定包含了两个字符的情况，所以不可能比两个字符的更优。

所以我们只用找两个或一个字符的总共出现次数，并且取$max$ 就行了。

很容易想到当字符数为$1$ 时，最大值只要取出现次数的$max$ 就行了。

当字符数为$2$ 时，可以枚举每一个$1 \le i \le |s|$ ，统计它前面所有字符的出现次数，然后增加前面字符和$s_i$ 组成的两个字符的子序列的数量就行了。

整体复杂度大约$O(n)$ 左右。
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;//不开long long见祖宗
string s;
ll book[26],ans[90010],Max;
int main()
{
    cin>>s;
    for(ll i=0;i<s.size();i++)
    {
        for(ll j=0;j<26;j++)
            ans[j*26+s[i]-'a']+=book[j];
        //统计两个字符时
        book[s[i]-'a']++;
        //统计一个字符时
    }//统计
    for(ll i=0;i<=90000;i++)
        Max=max(Max,ans[i]);
    for(ll i=0;i<26;i++)
        Max=max(Max,book[i]);
    //取最大值
    cout<<Max;
    return 0;
}  
```
~~完结撒花~~

---

## 作者：The_foolishest_OIer (赞：0)

贪心。

可以发现，最优的子序列长度肯定不大于 $2$。

然后分别统计长度为 $1$ 和长度为 $2$ 的最大值。

长度为 $1$ 的最大值就是出现次数最多的字母的出现字数。

长度为 $2$ 时枚举这两个字符，然后扫一遍字符串，前缀和优化即可。


```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
const int N = 1e5 + 10;
string s;
int n;
int t[N],f[N][35];
void close(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
}
signed main(){
	close();
	cin >> s;
	n = s.size();
	s = " " + s;
	for (int i = 1 ; i <= n ; i++)
		t[s[i] - 'a' + 1]++;
	for (int i = 1 ; i <= 26 ; i++){
		for (int j = 1 ; j <= n ; j++){
			if (s[j] != i + 'a' - 1) f[j][i] = f[j - 1][i];
			else f[j][i] = f[j - 1][i] + 1; // 表示 1 - j 个字符一共出现了第 i 个小写字母的次数
		}
	}
	int ans = 0;
	for (int i = 1 ; i <= 26 ; i++)
		ans = max(ans,t[i]); // 长度为 1 的最大值
	for (int fi = 1 ; fi <= 26 ; fi++){
		for (int se = 1 ; se <= 26 ; se++){
			int sum = 0;
			for (int i = 1 ; i <= n ; i++)
				if (s[i] == fi + 'a' - 1) sum += (f[n][se] - f[i][se]); // 如果第一个字符符合要求，累加答案
			ans = max(ans,sum);
		}
	} // 长度为 2 的最大值
	cout << ans;
	return 0;
}
```

---

## 作者：_zqh_ (赞：0)

不难想到，对于任意的字符串 $s$，一定有长为 $1$ 或 $2$ 的出现次数最多的隐藏的讯息串；

简单来说就是只需要考虑长度为 $1$ 或 $2$。

---

### 证明：

- 引理 1：任意两个数都可以构成等差数列；

假设有一个长度大于 $2$ 的出现次数最多的隐藏的讯息串 $t$；

根据引理 1，此时所有 $t$ 的长度为 $2$ 的子串都都是隐藏的讯息串。

那么就一定存在长度小于等于 $2$ 的出现频率大于等于 $t$ 的隐藏的讯息串。

证毕。
 
[code](https://codeforces.com/contest/1307/submission/262358848)。

---

## 作者：qw1234321 (赞：0)

贪心主要猜结论。

于是，结论：秘密讯息必然是长度为 $1$ 或 $2$ 的子序列。

证明：

假定一个长度 $\gt 2$ 的字符串 $S$，则每当 $S$ 出现一次，**$S$ 中每两个字母组成的子序列也会出现一次，故 $S$ 一定不为秘密讯息**。

还有，不要漏掉秘密讯息长度为 $1$ 的情况。

然后就是模拟了，详见代码。

code：

```cpp
#include<bits/stdc++.h>
#define int long long
#define il inline
namespace things{
	il int rd(){
		int f = 1, x = 0;
		char ch = getchar();
		while(ch < '0' || ch > '9'){
			if (ch == '-') f = -1;
			ch = getchar();
		}
		while(ch >= '0' && ch <= '9'){
			x = x * 10 + ch - '0';
			ch = getchar();
		}
		return x * f;
	}
	il int max(int x, int y, int z){
		return std::max(x, std::max(y, z));
	}
	il int min(int a, int b, int c){
		return std::min(a, std::min(b, c));
	}
}
using namespace things;
using namespace std;

const int N = 27, M = 1e5 + 5;
string s;
int ans[N][N], h[M][N];

void work(){
	cin >> s;
	int n = s.size();
	s = " " + s;
	for (int i = n; i >= 1; i--){
		h[i][s[i] - 'a']++;
		for (int j = 0; j < 26; j++) h[i][j] += h[i + 1][j];
	}
	for (int i = 1; i < n; i++){
		for (int j = 0; j < 26; j++) ans[s[i] - 'a'][j] += h[i + 1][j];
	}
	int res = 0;
	for (int i = 0; i < 26; i++){
		for (int j = 0; j < 26; j++) res = max(res, ans[i][j]);
		res = max(res, h[1][i]);
	}
	cout << res;
}

signed main(){
	int t = 1;
	//	cin >> t;
	while(t--) work();
	return 0;
}
```

---

