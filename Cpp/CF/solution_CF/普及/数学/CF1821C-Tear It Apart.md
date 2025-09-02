# Tear It Apart

## 题目描述

You are given a string $ s $ , consisting of lowercase Latin letters.

In one operation, you can select several (one or more) positions in it such that no two selected positions are adjacent to each other. Then you remove the letters on the selected positions from the string. The resulting parts are concatenated without changing their order.

What is the smallest number of operations required to make all the letters in $ s $ the same?

## 说明/提示

In the first testcase, you can select positions $ 2, 4 $ and $ 6 $ and remove the corresponding letters 'b', 'c' and 'b'.

In the third testcase, the letters in the string are already the same, so you don't have to make any operations.

In the fourth testcase, one of the possible solutions in $ 2 $ operations is the following. You can select positions $ 1, 4, 6 $ first. The string becomes "bce". Then select positions $ 1 $ and $ 3 $ . The string becomes "c". All letters in it are the same, since it's just one letter.

## 样例 #1

### 输入

```
5
abacaba
codeforces
oooooooo
abcdef
mewheniseearulhiiarul```

### 输出

```
1
3
0
2
4```

# 题解

## 作者：spider_oyster (赞：6)

枚举要保留的字符 $c$，把每个 $c$ 看为分界点（不删），会把原串分成若干段。

删除步数最多的显然是长度最大的段。

设区间长度 $x$，则删除次数为 $\log_2x+1$。

因为每次错位删，$x=\lceil \frac{x}{2} \rceil$。

```cpp
#include<bits/stdc++.h>
using namespace std;
 
const int N=2e5+5;
string s;
 
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int t;cin>>t;
    while(t--)
    {
        cin>>s;
        int ans=1e9;
        for(int c='a';c<='z';c++)
        {
            int res=0,len=0;
            for(int i=0;i<s.size();i++)
                if(s[i]!=c) len++;
                else res=max(res,len),len=0;
            res=max(res,len);
            if(res==0) {ans=0;break;}
            ans=min(ans,(int)log2(res)+1);
        }
        cout<<ans<<'\n';
    }
}
```


---

## 作者：Lovely_Chtholly (赞：6)

[题目传送门](https://www.luogu.com.cn/problem/CF1821C)

### 【分析】

枚举 $26$ 个小写字母（分界点），把字符串分成若干段。不难发现，若有一段长度为 $len$ 的字符串，因为每次删不相邻的字符，所以 $len$ 每次会变成原来的 $\frac{1}{2}$，所以删除长度为 $len$ 的字符串需要 $\log_{2}{len} + 1$ 步。

### 【AC 代码】

```cpp
#include<cmath>
#include<stdio.h>
#include<iostream>
#include<stack>
using namespace std;
const int INF=0x3f3f3f3f;
inline int read(char ch=getchar(),int n=0,int m=1)
{
	while(ch<'0' or ch>'9')
	{
		if(ch=='-')m=-1;
		ch=getchar();
	}
	while(ch>='0' and ch<='9')n=(n<<3)+(n<<1)+ch-'0',ch=getchar();
	return n*m;
}
ostream& operator <<(ostream& o,__uint128_t &a)
{
	__uint128_t x=a;
	stack<int>s;
	while(x)s.push(x%10),x/=10;
	while(!s.empty())o<<s.top(),s.pop();
	return o;
}
int t=read();
signed main()
{
	next:
	while(t--)
	{
		int minn=INF;
		string s;
		cin>>s;
		for(char i='a';i<='z';i++)
		{
			int len=0,sum=0;
			for(int j=0;j<s.size();j++)
			{
				if(i==s[j])len=max(len,sum),sum=0;
				else sum++;
			}
			len=max(len,sum);
			if(len)minn=min(minn,(int)(log2(len))+1);
			else
			{
				puts("0");
				goto next;
			}
		}
		cout<<minn<<"\n";
	}
	return 0;
}
```

~~鲁迅说过：~~

>~~莫抄袭，棕了你的名，空悲切！~~

---

## 作者：Night_sea_64 (赞：2)

跟其他大佬一样，可以选择枚举剩下的那个字符。要把字符串进行一次操作的时候，只要这个字符不是剩下的而且跟上一个删掉的不相邻，就把它删掉就好了。这样一定能保证一次删除的字符最多，操作次数也一定最少。

因为直接调用 `s.erase()` 会比较麻烦，所以我想的是直接弄个数组 $flag$ 标记一个位置是不是被删掉了。记录一个 $f$ 表示从上次删除到当前还有没有没有删除的字符，就可以知道这个字符是否跟上一个删掉的字符不相邻了。剩下的就是注意 $flag$ 数组以及其它变量的初始化就可以了。

```cpp
#include<iostream>
#include<cstring>
using namespace std;
int t;
bool flag[200010];
int main()
{
    cin>>t;
    while(t--)
    {
        string s;
        cin>>s;
        int minn=1e9;
        for(char c='a';c<='z';c++)
        {
            int cnt=0;
            memset(flag,1,sizeof(flag));
            while(1)
            {
                bool f=1;
                for(int i=0;i<s.size();i++)
                    if(flag[i]&&s[i]!=c)f=0;
                if(f)break;
                cnt++;
                f=0;
                for(int i=0;i<s.size();i++)
                {
                    if(!f&&s[i]!=c&&flag[i])flag[i]=0,f=1;
                    else if(flag[i])f=0;
                }
            }
            minn=min(minn,cnt);
        }
        cout<<minn<<endl;
    }
    return 0;
}
```

---

## 作者：arrow_king (赞：2)

题意很清楚了。

# 思路

由于长度 $n\le2\times10^5$，同时小写字母一共只有 $26$ 个，所以考虑枚举最后剩下的那个字母。

这样可以发现这些字母将整个字符串切成了若干段，同时每段中都不包含最后留下的那个字母。

可以发现对于一个长度（比如说 $k$）确定的字符串，用给定操作删除所需的最少次数是一定的。稍微找一找规律可以发现对于长度为 $k$ 的字符串，删除所需要的最少次数为 $\left\lfloor\log_2 k\right\rfloor+1$。

如果当前保留字符为 $c$，一共分成 $x$ 段，每段长度为 $l_1,l_2,\dots,l_x$，则删掉整个字符串的最少次数就是

$$\max\limits_{i=1}^x\left\lfloor\log_2l_x\right\rfloor+1$$

然后，就没有然后了。

# 代码

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
#define ll long long
#define il inline
il ll read() {
	ll x=0,f=1;char c=getchar();
	while(c<'0'||c>'9') {if(c=='-') {f=-1;} c=getchar();}
	while(c>='0'&&c<='9') {x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x*f;
}
int t,n,ans=0,last,tot,oper[200005];
char s[200005];
il int change(int x) {
	if(x<=2) return x;
	return 2;
}
int main() {
	oper[1]=1;
	for(int i=2;i<=200000;i++) oper[i]=oper[i/2]+1;    //预处理操作次数
	t=read();
	while(t--) {
		scanf("%s",s+1);
		n=strlen(s+1);
		ans=1e9;
		for(int now='a';now<='z';now++) {
			last=0,tot=0;
			for(int i=1;i<=n;i++) {
				if(s[i]==now) {
					tot=max(tot,oper[i-last-1]);
					last=i;
				}
			}
			tot=max(tot,oper[n-last]);
			ans=min(ans,tot);
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：zeekliu (赞：1)

一眼看，挨个枚举 $26$ 个字母。

设枚举的字母为 $c$，每次将其分割成若干个不含 $c$ 的连续子串，然后根据每一段的长度可以求出答案。

至于如何求，我们不妨模拟一下：

比如现在字符串的长度为 $9$，那它的删除过程如下：

第 $1$ 次：删除第 $1,3,5,7,9$ 位，此时剩下第 $2,4,6,8$ 位。

第 $2$ 次：删除第 $2,6$ 位（因为此时 $2,4$ 等为相邻位，所以只能删除 $2,6$ 位），还剩下第 $4,8$ 位。

第 $3$ 次：删除第 $4$ 位（$4,8$ 位为相邻位，不能同时删除），还剩下第 $8$ 位。

第 $4$ 次，删除第 $8$ 位，删除完成。

可以看出，每次字符串长度为除以 $2$ 并且下取整，这不就是 $\log$ 吗？但要注意，最后一个字符也要删除，所以还要加 $1$。

因此，$ans=\max\limits_{i=1}^{m}(\lfloor\log(r_i-l_i+1)\rfloor)$，其中 $l,r$ 表示每个区段的左右位置，$m$ 表示总共分出的段数。

举个例子：

比如字符串为 `abcacbba`，现在枚举 `a`，然后我们可以将整个字符串根据 `a` 的位子分割成若干个连续的不含 `a` 的子序列：`a | bc | a | ccb | a`。其中，`bc` 的长度为 $2$，`ccb` 的长度为 $3$，$\lfloor\log(2)\rfloor+1=2$，$\lfloor\log(3)\rfloor+1=2$，而最大值即为 $2$。枚举 `b` 和 `c` 也可发现，答案都为 $2$。

代码：

```cpp
//CF1821C 23.04.28 *?
#include <bits/stdc++.h>
#define int long long
using namespace std;
int _;
string s;

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin>>_;
    while (_--)
    {
        cin>>s;
        int mn=1e9;
        for (char c='a';c<='z';c++)
        {
            int t=0,mx=0,cnt=0;
            while (t<s.length())
            {
                cnt=0;
                if (s[t]==c) t++;
                else while (s[t]!=c && t<s.length()) t++,cnt++;
                mx=max(mx,cnt);
            }
            if (mx==0) mx=0;
            else mx=log2(mx)+1;
            mn=min(mn,mx);
        }
        cout<<mn<<endl;
    }
    exit(0);
}
```

---

## 作者：M00R (赞：1)

# CF1821C Tear It Apart

题目大意：给定一个由小写字母组成的字符串，每次可以删去字符串中任意数量个不相邻的字符，问：最少需要几次操作才能将原字符串删为只由一个字母组成的串？

可以这么想：要将原字符串中的字母删至只剩一种，那么剩下的这些字母在原字符串中“包夹”的字母都要删去。例如：$abca$ 这个字符串，要将原串删至只剩 $aa$，那在这两个字母间夹着的 $b$ 和 $c$  都必须删去。每种字母只需要取最长的区间距离即可，因为在处理最长的区间时，其它夹着“异类”的区间可以同时处理。$26$ 个字母每个都可能成为最后剩下的那种，所以暴力枚举就可以了。

```
#include<bits/stdc++.h>
using namespace std;
int n,f[30],g[30],ans,m;
char a[1000001];
int main()
{
	scanf("%d",&n);
	while(n--)
	{
		scanf("%s",a+1);
		ans=1e8;
		m=strlen(a+1);
		for(int i=1;i<=m;i++)
		{
			f[a[i]-'a']=max((int)ceil(log2(i-g[a[i]-'a'])),f[a[i]-'a']);//取最大要处理的次数 
			g[a[i]-'a']=i;//记录上次出现的位置 
		}
		for(int i=0;i<=25;i++)
		{
			f[i]=max(f[i],(int)ceil(log2(strlen(a+1)-g[i]+1)));
//			printf("%c:%d\n",i+'a',f[i]);
			ans=min(ans,f[i]);//在所有字母中取处理次数最小的 
			f[i]=g[i]=0;
		}
		printf("%d\n",ans);
	}
}
```



---

## 作者：aeiouaoeiu (赞：1)

### 题意
给你一个字符串 $s$，你可以删去字符串里的任意个不连续的字符，删去字符后，$s$ 中剩下的字符会拼接起来，问最少要多少次操作，使得 $s$ 里的字符一样。
### 解法
先看看删去一段字符最少要进行多少次操作，我们把第 $i$ 个字符最少将在第几次删除操作中被删除记作 $a_i$，手玩一下，发现 $a$ 长这个样子：$1,2,1,3,1,2,1,4,1,2,1,3,1,2,1,\ldots$ 我们再令 $b_i=\max_{j=1}^{i}{a_j}$，发现 $b$ 长这个样子：$1,2,2,3,3,3,3,4,4,4,4,4,4,4,4,\ldots$ 又知道 $b_i$ 是删去 $i$ 个字符所需的最少次数，结合数列，我们有 $b_i=\lfloor{\log_2i}\rfloor+1$。

接下来，我们考虑枚举最后留下来哪个字符，设留下来的字符为 $c$。由于一串 $c$ 左边的字符和右边的字符互不干扰，所以我们可以对要删除的区间取最长长度，对于不同的 $c$ 取最小值计算所需最少次数即可。
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=200005;
ll n;
string s;
ll solve(void){
	ll ans=1145141,mx,cnt;
	for(char p='a';p<='z';p++){
		mx=cnt=0;
		for(int i=1;i<=n;i++){
			if(s[i]==p) mx=max(mx,cnt),cnt=0;
			else cnt++;
		}
		if(cnt==n) continue;
		mx=max(mx,cnt),ans=min(ans,mx);
	}
	return (ans==0?0:(ll)log2(ans)+1);
}
int main(void){
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	ll T=1;
	cin>>T;
	for(int tcs=1;tcs<=T;tcs++){
		cin>>s;
		n=s.length(),s=" "+s;
		cout<<solve()<<"\n";
	}
	return 0;
}
```

---

## 作者：Wf_yjqd (赞：1)

23.4.29	修了一点点小语病。

不是很难想吧，虽然调了好久。。（可能是目前原理方面最详细的一篇）

------------

显然，可以考虑暴力枚举最终相同的字母。

那么，我们可以维护两个相同字母中间隔了几个别的。

考虑一个序列，第 $i$ 个元素表示第 $i$ 个选定字母和第 $i+1$ 个中间长度。

每次操作可以把当前所有非 $0$ 的元素同时减去一个数。

问题变成了，如何用最少次操作把一个序列全变成 $0$。

那么只用把每个元素都化成二进制的，每次操作将所有的消掉一位即可（第 $i$ 次减去 $2^{i-1}$）。

那么最多要消几次呢？

答案就是最大元素二进制下的位数啊。（即 $\lceil\log_2^{x}\rceil$）

处理一些细节好了。

------------

没人看的代码。。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+84;
int T,n,ans,len,last[26],cnt[26];
char s[maxn];
int main(){
    scanf("%d",&T);
    while(T--){
        memset(last,0,sizeof(last));
        memset(cnt,0,sizeof(cnt));
        scanf("%s",s+1);
        len=strlen(s+1);
        for(int i=1;i<=len;i++){
            cnt[s[i]-'a']=max(cnt[s[i]-'a'],i-last[s[i]-'a']-1);
            last[s[i]-'a']=i;
        }
        ans=0x7f7f7f7f;
        for(int i=0;i<26;i++){
            cnt[i]=max(cnt[i],len-last[i]);
            ans=min(ans,cnt[i]);
        }
        if(ans==0)
            puts("0");
        else
            printf("%d\n",int(log2(ans))+1);
    }
    return 0;
}
```


---

## 作者：Miyamizu_Mitsuha (赞：0)

关键在于，可以枚举 $26$ 个字母，将每个字符看作是一个分界点，然后将原字符串分割成若干段。然后在这些分割段中找到一个最长的段，因为删除一个段的代价是 $\log_2l+1$，其中 $l$ 是段的长度。每次删除操作都会将字符段错位删，也就是长度减半，因此每次删的长度都是 $\lceil \frac{l}{2} \rceil$。这个其他题解也有讲过，不再多说。

用一个变量记录当前字符段的长度，然后再记录当前段的长度，初始值都设为 $0$。枚举 $26$ 个字母，设为 $m$。然后遍历一下输入的每个字符，如果字符不等于 $m$，长度自增，否则更新字符段的长度，然后当前段的长度归零。最后再更新一遍字符段的长度来处理最后一段。如果字符段的长度等于 $0$，说明整个字符串就是 $m$，那么答案就是 $0$。否则的话更新答案为 $\min(\text{答案},\log_2(\text{当前字符段的长度})+1)$。

```
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define inf 1e18
int ms(string str) {
    int rt = inf;
    for (char m = 'a'; m <= 'z'; m++) {
        int maxy = 0, l = 0;
        for (int i = 0; i < str.size(); i++) {
            if (str[i] != m) l++;
            else {
              maxy = max(maxy, l);
              l = 0;
            }
        }
        if (!max(maxy, l)) return maxy;
        rt = min(rt, (int)log2(max(maxy, l)) + 1);
    }

    return rt;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    int t;
    cin >> t;

    while (t--) {
        string s;
        cin >> s;
        cout << ms(s) << endl;
    }

    return 0;
}

```


---

## 作者：yuanruiqi (赞：0)

## 题目分析

先枚举字母并找到最大的间隔长度。

因为每次可以去除这个间隔内的一半（上取整），所以直接计算对数即可。

## 代码

```cpp
void solve()
{
    string s;
    cin >> s;
    int ans = s.size() - 1;
    for (char c='a';c<='z';++c)
    {
        int lst = -1, cnt = 0, ok = 0;
        for (int i=0;i<s.size();++i)
            if (s[i] == c)
            {
                ok = 1;
                cnt = max(cnt, i - lst - 1);
                lst = i;
            }
        cnt = max(cnt, (int)s.size() - lst - 1);
        if (ok) ans = min(ans, cnt);
    }
    int tot = 0;
    while (ans) ++tot, ans >>= 1;
    cout << tot << '\n';
}
```


---

