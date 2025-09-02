# Zuhair and Strings

## 题目描述

Given a string $ s $ of length $ n $ and integer $ k $ ( $ 1 \le k \le n $ ). The string $ s $ has a level $ x $ , if $ x $ is largest non-negative integer, such that it's possible to find in $ s $ :

- $ x $ non-intersecting (non-overlapping) substrings of length $ k $ ,
- all characters of these $ x $ substrings are the same (i.e. each substring contains only one distinct character and this character is the same for all the substrings).

A substring is a sequence of consecutive (adjacent) characters, it is defined by two integers $ i $ and $ j $ ( $ 1 \le i \le j \le n $ ), denoted as $ s[i \dots j] $ = " $ s_{i}s_{i+1} \dots s_{j} $ ".

For example, if $ k = 2 $ , then:

- the string "aabb" has level $ 1 $ (you can select substring "aa"),
- the strings "zzzz" and "zzbzz" has level $ 2 $ (you can select two non-intersecting substrings "zz" in each of them),
- the strings "abed" and "aca" have level $ 0 $ (you can't find at least one substring of the length $ k=2 $ containing the only distinct character).

Zuhair gave you the integer $ k $ and the string $ s $ of length $ n $ . You need to find $ x $ , the level of the string $ s $ .

## 说明/提示

In the first example, we can select $ 2 $ non-intersecting substrings consisting of letter 'a': "(aa)ac(aa)bb", so the level is $ 2 $ .

In the second example, we can select either substring "a" or "b" to get the answer $ 1 $ .

## 样例 #1

### 输入

```
8 2
aaacaabb
```

### 输出

```
2
```

## 样例 #2

### 输入

```
2 1
ab
```

### 输出

```
1
```

## 样例 #3

### 输入

```
4 2
abab
```

### 输出

```
0
```

# 题解

## 作者：wuyixiang (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF1105B)

给你一个长度为 $n$ 的字符串 $s$，请问最多能找到几个长度为 $k$ 的字串，它们互不重叠且它们都只有同一种字符构成。 

**思路**

首先我们必须枚举那 $k$ 个字符串都属于哪个字母。然后从这个字母依次去枚举。如果下一个字母不为所选的字母了，则直接结算能分成几个长度为 $k$ 的子串（即连续的长度除以 $k$），然后再往下枚举。最后取 $\max$ 即可。代码如下:

```cpp
    for(int j = 1;j <= 26;j ++){
        int num = 0;
        for(int i = 1;i <= s.size();i ++)
        {
            if(s[i] != char(j + 96))//判断
            {
                num += (u / k);
                u = 0;//记得初始化
            }
            else u ++;
        }
        ans = max(ans,num);//取结果的最大值
    }
    cout << ans;
```


---

## 作者：hsfzLZH1 (赞：2)

## 题目大意

给出一个长度为 $n$ 的字符串 $s$ 和一个整数 $k$ ，找到最多的长度为 $k$ 的互不重叠的子串，使得这些子串 ** 全部由一个相同的字符组成 ** ，输出这个最大值。字符串全部由小写的拉丁字母组成。

$1\le k\le n\le 2\times 10^5$

## 解题思路

用一个长度为 $26$ 的计数器计数。

从左到右，每次找出一段由相同字符构成的最长的子串，假设这个子串的长度为 $l$ ，那么就可以分解成 $\lfloor \frac l k\rfloor$ 个长度为 $k$ 的互不重叠的子串，将这个答案加入其组成字符的计数器。

注意最后一个子串也要加入计数器。

最后的答案就是计数器中的最大值。

时间复杂度 $O(n)$ ，空间复杂度 $O(n)$ ，甚至可以优化到 $O(1)$ 。

## 代码展示

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=200010;
typedef long long ll;
int n,k,ans[30],nww,maxx;
char s[maxn];
int main()
{
	scanf("%d%d%s",&n,&k,s+1);
	for(int i=1;i<=n;i++)
	{
		if(i!=1&&s[i]!=s[i-1])ans[s[i-1]-'a']+=nww/k,nww=0;
		nww++;
	}
	ans[s[n]-'a']+=nww/k;
	for(int i=0;i<26;i++)maxx=max(maxx,ans[i]);
	printf("%d\n",maxx);
	return 0; 
}
```

---

## 作者：Rachel_in (赞：1)

此题要我们求连续的序列，我们可以设置数组f,f[i]表示到i这个位置最长连续序列的长度.所以如果s[i]=s[i-1],那么f[i]=f[i-1]+1,否则f[i]=1.然后大力扫一遍用桶记录答案取最大值。

代码如下


```cpp
#include<bits/stdc++.h>
using namespace std;
char s[200005],c;
int n,k,m;
int f[200005];
int ans[26];
int main()
{
	scanf("%d%d",&n,&m);
	scanf("%s",s);
	f[0]=1;
	for(int i=1;i<n;i++)
	{
		if(s[i]==s[i-1])
		f[i]=f[i-1]+1;
		else
		f[i]=1;
	}
	for(int i=0;i<n;i++)
	{
		if(f[i]!=0&&f[i]%m==0) //注意是%m而不是等于m，因为连续的长度可能是m的倍数
		ans[(int)s[i]-'a']++;
	}
	int maxx=0;
	for(int i=0;i<=25;i++)
	maxx=max(maxx,ans[i]);
	printf("%d\n",maxx);
}
```

---

## 作者：IAKIOI__ (赞：0)

## 前置知识

贪心。

# 题意

给你一个长度为 $n$ 的字符串 $s$，请问最多能找到几个长度为 $k$ 且由同一小写字母组成的不重叠子串。

# 思路

思路很简单，统计每个小写字母最多能分成的符合条件子串的个数，最后输出能构成符合条件的子串个数最多的那个字母对应的个数。

# 代码

```cpp
#include<bits/stdc++.h>
#define _ 0
using namespace std;
int n,k,t[30];
string s;
void lnit(){//处理字符
	int fl=s[0]-'a';
	int l=1;
	for(int i=1;i<n;i++){
		if(s[i]-'a'!=fl){
			t[fl]+=l/k;
			fl=s[i]-'a';
			l=1;
		}else{
			l++;
		}
	}
	t[fl]+=l/k;//注意最后的一次统计
}
int main(){
	cin>>n>>k>>s;
	lnit();
	int MAX=0; 
	for(int i=0;i<26;i++){
		MAX=max(MAX,t[i]);//寻找最大值
	}
	cout<<MAX;
	return ~~(0^_^0);
}
```

---

## 作者：HEzzz (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1105B)

## 解析

因为题目要求的子串必须由同一种拉丁字符组成，所以我们不妨去枚举子串中的字符是哪一种。然后去遍历整个字符串，找出连续的 $k$ 个与枚举字符相同的连续的字符串，其中可能会找出连续大于 $k$ 个的，那为了最优解和互不重叠，我们贪心地把它拆出来，即是对答案产生的贡献为 $\left \lfloor \frac{len}{k}  \right \rfloor $ 个，其中的 $len$ 表示连续与枚举字符相同的数量。

具体的细节可以看代码，时间复杂度也是 $O(n)$。

## code

```cpp
#include<bits/stdc++.h>
#define _rep(i,a,b) for(int i=(a);i<=(b);i++)
#define _antirep(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
typedef long long LL;
typedef double db;
const int N=2e5+5,SN=1e3+5,Mod=998244353; 
int n,k,ans;
char s[N];
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0); 
	cin>>n>>k>>(s+1);s[n+1]='&';
	for(char t='a';t<='z';++t)
	{
		int res=0,now=0;
		_rep(i,1,n+1)
		{
			if(s[i]!=t) res+=now/k,now=0; 
			else now++;
		}
		ans=max(ans,res);
	}
	cout<<ans<<'\n';
	return 0;
}

```

---

## 作者：Zechariah (赞：0)

给一个O(n)解法  
直接遍历整个字符串，图中记录一下当前字符有多少个连续的，统计每个字符有多少段长度等于k，最终答案取段数最多的那个字符
```cpp
#include <bits/stdc++.h>
#define jh(x,y) x^=y^=x^=y
#define rg register
#define inl inline
typedef long long ll;
const int N = 2e5 + 5;
using namespace std;
namespace fast_IO {
    inl ll read()
    {
        rg ll num = 0;
        rg char ch;
        rg bool flag = false;
        while ((ch = getchar()) == ' ' || ch == '\n' || ch == '\r');
        if (ch == EOF)return ch; if (ch == '-')flag = true; else num = ch ^ 48;
        while ((ch = getchar()) != ' '&&ch != '\n'&&ch != '\r'&&~ch)
            num = (num << 1) + (num << 3) + (ch ^ 48);
        if (flag)return -num; return num;
    }
    inl ll max(rg ll a, rg ll b) { if (a > b)return a; return b; }
    inl ll min(rg ll a, rg ll b) { if (a < b)return a; return b; }
    void write(rg long long x) { if (x < 0)putchar('-'), x = -x; if (x >= 10)write(x / 10); putchar(x % 10 ^ 48); }
};
char s[N];
int num[300], a[300];

int main(void)
{
    rg int n = fast_IO::read(), k = fast_IO::read();
    scanf("%s", s + 1);
    for (rg int i = 1; i <= n; ++i)
    {
        if (++num[s[i]] == k)
        {
            num[s[i]] = 0;
            ++a[s[i]];
        }
        else if (s[i] != s[i - 1])num[s[i - 1]] = 0;
    }
    rg int maxn = 0;
    for (rg int i = 'a'; i <= 'z'; ++i)maxn = fast_IO::max(maxn, a[i]);
    fast_IO::write(maxn);
    return 0;
}

```

---

