# Interesting Story

## 题目描述

Stephen Queen wants to write a story. He is a very unusual writer, he uses only letters 'a', 'b', 'c', 'd' and 'e'!

To compose a story, Stephen wrote out $ n $ words consisting of the first $ 5 $ lowercase letters of the Latin alphabet. He wants to select the maximum number of words to make an interesting story.

Let a story be a sequence of words that are not necessarily different. A story is called interesting if there exists a letter which occurs among all words of the story more times than all other letters together.

For example, the story consisting of three words "bac", "aaada", "e" is interesting (the letter 'a' occurs $ 5 $ times, all other letters occur $ 4 $ times in total). But the story consisting of two words "aba", "abcde" is not (no such letter that it occurs more than all other letters in total).

You are given a sequence of $ n $ words consisting of letters 'a', 'b', 'c', 'd' and 'e'. Your task is to choose the maximum number of them to make an interesting story. If there's no way to make a non-empty story, output $ 0 $ .

## 说明/提示

In the first test case of the example, all $ 3 $ words can be used to make an interesting story. The interesting story is "bac aaada e".

In the second test case of the example, the $ 1 $ -st and the $ 3 $ -rd words can be used to make an interesting story. The interesting story is "aba aba". Stephen can't use all three words at the same time.

In the third test case of the example, Stephen can't make a non-empty interesting story. So the answer is $ 0 $ .

In the fourth test case of the example, Stephen can use the $ 3 $ -rd and the $ 4 $ -th words to make an interesting story. The interesting story is "c bc".

## 样例 #1

### 输入

```
6
3
bac
aaada
e
3
aba
abcde
aba
2
baba
baba
4
ab
ab
c
bc
5
cbdca
d
a
d
e
3
b
c
ca```

### 输出

```
3
2
0
2
3
2```

# 题解

## 作者：NXYorz (赞：6)

[题目链接](https://www.luogu.com.cn/problem/CF1551C)

--------
### 题目大意
有 $n$ 个字符串，每个字符串只包含 ```a```,```b```,```c```,```d```,```e``` 五个字符。

现在从这 $n$ 个字符串里选择若干个，组成一个新的字符串。在满足某个字符出现的次数大于其他字符加起来出现次数的情况下，最大化新字符串的长度。

--------
### 分析
以分析字符 $x$ 为例。

对于每个字符串 $i$ ，只需要统计出字符 $x$ 出现的次数 $cnt_1$ 和 其他字符出现的次数 $cnt_2$, 令 $w_i=cnt_1-cnt_2$, 这是 $x$ 比其他字符多出现的次数，有可能为负数，最后排序一下 $w$， 维护一个前缀和使其大于0即可。

最后比较一下即可 qwq

----
### $Code$
```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;

const int N = 2e5 + 10;

int t,n,ans,prt;
string s[N];

struct El
{
	int w;
	int size;
	bool operator < (const El &B) const{
		return w > B.w;
	}
}a[N];

void judge(char x)
{
	memset(a , 0 , sizeof(a)); ans = 0; 
	for(int i = 1; i <= n; i++)
	{
		int cnt = 0; int len = s[i].length();
		for(int j = 0; j < len; j++)
			if(s[i][j] == x) cnt++;
		a[i].w = cnt - (len - cnt);a[i].size = len;
	}
	sort(a + 1 , a + 1 + n);
	int sum = 0;
	for(int i = 1; i <= n; i++)
	{
		if(sum + a[i].w <= 0) break;
		sum += a[i].w; ans ++;
	}
	prt = max(prt , ans);
}

void work()
{
	scanf("%d",&n);prt = ans = 0;
	for(int i = 1; i <= n; i++)
		cin >> s[i];
	judge('a');judge('b');judge('c');judge('d');judge('e');
	printf("%d\n",prt);
}

int main()
{
//	freopen("aa.in","r",stdin);
	scanf("%d",&t);
	while(t--)
		work();

}
```

---

## 作者：ncwzdlsd (赞：2)

统计每一种字母在每个字符串中出现的次数和其他种类的字母的出现次数的差值。

考虑贪心。对于选择每种字母分别进行讨论，按差值从大到小选择字符串，直到选择字母的出现次数小于其他字母的出现总次数。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;

const int maxn=2e5+5;
int cnt[5][maxn],dif[5][maxn];

void solve()
{
    int n;cin>>n;
    for(int i=1;i<=n;i++) for(int j=0;j<5;j++) cnt[j][i]=0;
    for(int i=1;i<=n;i++)
    {
        string s;cin>>s;
        for(int j=0;j<s.length();j++) cnt[s[j]-'a'][i]++;
        for(int j=0;j<5;j++) dif[j][i]=cnt[j][i]*2-s.length();
    }
    int ans=0;
    for(int i=0;i<5;i++)
    {
        sort(dif[i]+1,dif[i]+n+1);
        int now=0,tmp=0;
        int j=n;
        while(now+dif[i][j]>0&&j) now+=dif[i][j],tmp++,j--;
        ans=max(ans,tmp);
    }
    cout<<ans<<'\n';
}

int main()
{
    int t;cin>>t;
    while(t--) solve();
    return 0;
}
```

---

## 作者：KSToki (赞：2)

# 题目大意
给定 $n$ 个只含 a 到 e 的字符串，求最多能选出多少个字符串，使得存在某个字母出现次数严格大于其它字母。
# 题目分析
由于字符集大小仅为 $5$，则可以枚举是哪个字母最多。之后就可以贪心，计算出每个字符串的当前字母与其它字母的差值，从大到小选，直到和为非整数，注意需要严格大于。答案取最大值即可。
# 代码
```cpp
#include<bits/stdc++.h>
#define R register
#define I inline
#define ll long long
#define ull unsigned long long
#define db double
using namespace std;
#define pii pair<int,int>
#define mp(x,y) make_pair(x,y)
#define piii pair<pair<int,int>,int>
#define mp3(x,y,z) make_pair(make_pair(x,y),z)
#define fi first.first
#define se first.second
#define th second
#define putint(x) printf("%d\n",x)
#define putll(x) printf("%lld\n",x)
#define putull(x) printf("%llu\n",x)
#define lowbit(x) ((x)&(-(x)))
#define inf (1e9)
#define INF (1e18)
#define eps (1e-8)
I int read()
{
	char ch=getchar();
	int res=0,flag=1;
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
			flag=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		res=res*10+ch-'0';
		ch=getchar();
	}
	return res*flag;
}
int T,n,cnt[200001][5],a[5][200001],ans;
string s;
int main()
{
	T=read();
	while(T--)
	{
		n=read();
		for(R int i=1;i<=n;++i)
			for(R int j=0;j<5;++j)
				cnt[i][j]=0;
		for(R int i=1;i<=n;++i)
		{
			cin>>s;
			for(R int j=0,up=s.length();j<up;++j)
				++cnt[i][s[j]-'a'];
			for(R int j=0;j<5;++j)
				a[j][i]=2*cnt[i][j]-s.length();
		}
		ans=0;
		for(R int i=0;i<5;++i)
		{
			sort(a[i]+1,a[i]+n+1);
			int res=0,now=0;
			for(R int j=n;j;--j)
				if(now+a[i][j]>0)
				{
					now+=a[i][j];
					++res;
				}
			ans=max(ans,res);
		}
		putint(ans);
	}
	return 0;
}

```


---

## 作者：UperFicial (赞：1)

$\huge{}\text{Sol}$

题意楼下说的很清楚了，这里不再赘述。

赛时写到一半没时间了，直接裂开。

发现只有 $5$ 个字符，字符集很小，考虑枚举哪一个字符是故事中出现次数最多的字符。

然后我们对于字符串 $j$，我们设 $cnt[i][j]$ 表示字符 $i$ 在字符串 $j$ 中比其它字符多出现几次。

然后枚举字符 $i$，假设它在某一个故事中出现次数最多。我们就对 $cnt[i]$ 从大到小排序，贪心的选择字符 $i$ 出现次数多的字符串，然后做前缀和，一旦发现不大于 $0$ 则退出，因为这是从大到小排序的。

把这 $5$ 个答案取个最大值即可。

---

## 作者：Ghosty_Neutrino (赞：0)

## 题意
有 $n$ 个字符串，每个字符串只包含 $a$，$b$，$c$，$d$，$e$ 五个字符。

现在从这 $n$ 个字符串里选择若干个，组成一个新的字符串。在满足某个字符出现的次数大于其他字符加起来出现次数的情况下，最大化新字符串的长度。
## 分析
答案无非就是这五个字母，所以我们直接枚举当答案为这五个字母的情况取最大值即可。~~很简单是吧。~~

在求得过程中，我们发现对于每一个字符串来说他的贡献就是该字母的数量，减去其他字母的数量，例如 $aaabc$ 中 $a$ 的贡献就是 $1$，那么我们依次将每个字符串的贡献求出来，并保存下来，从大到小的依次相加，什么时候小于等于 $0$ 则说明我们的条件无法成立，那么我们的答案也就得出来了。
## 代码

```cpp
#include<bits/stdc++.h>
#define pi 3.1415926535
#define me(a,b,c) memset(a,b,sizeof c)
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
typedef pair<int, int> pii;
const int N = 1e6 + 10;
int t;
int mp[N];
int n;
bool cmp(int x, int y) {
	return x > y;
}
string a[N];
int res(char xx){
	for(int i = 1; i <= n; i++)mp[i] = 0;
	for (int i = 1; i <= n; i++) {
		for(int j = 0; a[i][j]; j++)
			if (a[i][j] == xx)mp[i]++;
			else mp[i]--;
	}
	sort(mp + 1, mp + 1 + n, cmp);
	int sum = 0;
	for(int i = 1; i <= n; i++) {
		sum += mp[i];
		if (sum <= 0)return i-1;
	}
	return n;
}
int main() {
	cin>>t;
	while(t--){
		cin >> n;
		for (int i = 1; i <= n; i++)cin>>a[i];
		int ans = 0;
		for(int i = 0; i <= 4; i++) ans=max(ans, res('a' + i));
		cout << ans << endl;
	}
	return 0;
}

```

---

