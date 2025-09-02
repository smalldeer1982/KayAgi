# Chemistry

## 题目描述

You are given a string $ s $ of length $ n $ , consisting of lowercase Latin letters, and an integer $ k $ .

You need to check if it is possible to remove exactly $ k $ characters from the string $ s $ in such a way that the remaining characters can be rearranged to form a palindrome. Note that you can reorder the remaining characters in any way.

A palindrome is a string that reads the same forwards and backwards. For example, the strings "z", "aaa", "aba", "abccba" are palindromes, while the strings "codeforces", "reality", "ab" are not.

## 说明/提示

In the first test case, nothing can be removed, and the string "a" is a palindrome.

In the second test case, nothing can be removed, but the strings "ab" and "ba" are not palindromes.

In the third test case, any character can be removed, and the resulting string will be a palindrome.

In the fourth test case, one occurrence of the character "a" can be removed, resulting in the string "bb", which is a palindrome.

In the sixth test case, one occurrence of the characters "b" and "d" can be removed, resulting in the string "acac", which can be rearranged to the string "acca".

In the ninth test case, one occurrence of the characters "t" and "k" can be removed, resulting in the string "aagaa", which is a palindrome.

## 样例 #1

### 输入

```
14
1 0
a
2 0
ab
2 1
ba
3 1
abb
3 2
abc
6 2
bacacd
6 2
fagbza
6 2
zwaafa
7 2
taagaak
14 3
ttrraakkttoorr
5 3
debdb
5 4
ecadc
5 3
debca
5 3
abaac```

### 输出

```
YES
NO
YES
YES
YES
YES
NO
NO
YES
YES
YES
YES
NO
YES```

# 题解

## 作者：All_Unluck_Beginning (赞：2)

### [原题传送门](https://www.luogu.com.cn/problem/CF1883B)

## 思路：
如"aba","abba"这样的回文字符串,

每个字符的出现次数有以下两种情况： 

1:全部是偶数（abba） 

2:只有一个为奇数（aba） 

于是只要字符出现个数为奇数的个数小于等于k+1即可 

否则无解
# AC code：
```
#include<bits/stdc++.h>
using namespace std;
int t,n,k,number[50];
string s;
int main() {
	cin>>t;
	while(t--) {
		cin>>n>>k>>s;
		int y=0;
		for(int i=0; i<n; i++) number[s[i]-'a'+1]++;//字符出现数量 
		for(int i=1; i<=26; i++){ 
			if(number[i]%2==1) ++y;//若为奇数 
			number[i]=0; //
		} 
		if(y-1<=k) cout<<"YES"<<endl;
		else cout<<"NO"<<endl;
	}
	return 0;
}
```
[AC记录](https://www.luogu.com.cn/record/133228653)

~~虽然思路和第一篇差不多，但是感觉比第一篇好理解~~

---

## 作者：One_JuRuo (赞：2)

## 思路

性质题，因为可以随便排序，所以只需要考虑数量满不满足条件即可。

一个回文串，应该满足所有的字符的数量都是偶数或者其中一个字符的数量是奇数。

所以可以直接扫一遍字符串，统计每个字符的数量，然后再统计数量是奇数的个数，如果这个个数大于 $k+1$ 就无解，否则有解。

## AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,m,num[50],ans;
char s[100005];
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d%s",&n,&m,s+1),ans=0;
		for(int i=1;i<=n;++i) ++num[s[i]-'a'];
		for(int i=0;i<26;++i)
		{
			if(num[i]%2==1) ans++;
			num[i]=0;
		}
		if(ans-1<=m) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
```

---

## 作者：rain_dew (赞：0)

原题传送门：[CF1883B](https://www.luogu.com.cn/problem/CF1883B)

数学模拟，建议评橙。

### 题意

对于长度为 $n$ 的字符串，经过**重新排序**与删减 $k$ 个字符，使之成为回文串，

### 思路

很容易能知道回文串的特点：当其字符为**偶数个**时，**一定**可以为成为回文串服务；当其字符为**奇数**个时，只有**最中间的一个字符**可以构成回文串，其余的**都要被删除**。

设计一个数组，记录每个字符出现次数后，对出现奇数次进行记录后，与最多可删除字符次数进行比较，输出最后答案。

注意本题多测并清空。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int t,a[30];
char ch[200005];
int main()
{
	scanf("%d",&t);
	while (t--)
	{
		int m=0,n,k;
		memset(a,0,sizeof(a));
		scanf(" %d %d %s",&n,&k,ch+1);
		for (int i=1;i<=n;i++)
			a[ch[i]-'a'+1]++;
		for (int i=1;i<=26;i++)
			if (a[i]%2)
				m++;
		if (m-1<=k)
			puts("YES");
		else
			puts("NO");
	}
	return 0;
}
```

---

## 作者：LITFLYR (赞：0)

# CF1883B — 题解
## [题目传送门](https://www.luogu.com.cn/problem/CF1883B)
### 题意
共 $T$ 组数据，每组给定一个字符串 $S$，它的长度 $n$，和要删除的字母数量 $k$。问能否在删除 $k$ 个字符后对字符串重新排序使得其成为回文字符串。

ps:我觉得题面翻译不是很好所以自己重新解释一下。
### 数据范围
$ 1 \le T \le 10^3$，$ 0 \le k < n \le 10^5$。
### 基本思路
一个回文串如果由偶数个字母组成，则每个字母出现的次数必然是偶数个。

一个回文串如果由奇数个字母组成，则除了最中间的字母，每个字母出现的次数必然是偶数个。

也就是说如果一坨字母可以通过组合构成一个回文串，这坨字母中只能有一个或零个字母出现了奇数次。因为我们可以删去 $k$ 个字母，所以在题目给出的字符串中出现奇数次的字母最多有 $k+1$ 个。

通过这个~~非常水~~的数据范围。我们可以直接扫一遍整个字符串，那正解就有了，请各位看代码。
# code

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,k,n;
int num[30];
string s;
int main(){
	cin >> t;
	while(t--){
		cin >> n >> k >> s;
		for (int i=0;i<n;i++){
			num[s[i]-'a']++;
		}
		int cnt=0;
		for (int i=0;i<26;i++){
			if (num[i]%2==1) cnt++;
			num[i]=0;
		}
		if (cnt<=k+1) cout << "YES" << endl;
		else cout << "NO" << endl;
	}
	return 0;
}
```

---

## 作者：FireRain (赞：0)

# 思路

首先如果一个串是回文的，一定满足各个字符出现次数最多只有一个奇数。

所以对于每一个出现奇数次数的字符都需要操作一次。

令这个数为 $x$，如果 $x - 1 \leq k$ 说明可以；否则不行。

# Code

```cpp
#include <bits/stdc++.h>
#define re register

using namespace std;

const int N = 50;
int T,n,k;
int num[N];
string s;

inline void solve(){
	memset(num,0,sizeof(num));
	int ans = 0;
	cin >> n >> k >> s;
	for (auto c:s) num[c - 'a']++;
	for (re int i = 0;i <= 25;i++){
		if (num[i] & 1) ans++;
	}
	if (ans - 1 <= k) cout << "YES\n";
	else cout << "NO\n";
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> T;
	while (T--) solve();
	return 0;
}
```

---

## 作者：Falling_Sakura (赞：0)

# 思路

我们其实就是要用 $s$ 里的字符来构造一个长度为 $n-k$ 的字符串，所以我们用桶记录一下每个字符出现的次数。

假如要构造的回文串长度为偶数，那么我们就把回文串长度除以二，设为 $len$，那么我么就找一下有没有 $len$ 对字符即可（两个相同的字符为一对）。

假如要构造的回文串长度为奇数，那么和偶数的处理方法一样，最后往回文中心随便放个字符即可。

注意特判一下回文串长度为 $1$ 或者为负数的情况。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 7;

char a[N];
int c[27];

int main()
{
    int t;
    scanf("%d", &t);
    while(t--)
    {
        int n, k;
        memset(c, 0, sizeof(c));
        scanf("%d%d", &n, &k);
        scanf("%s", a);
        for(int i = 0; i < n; i++)
        {
            c[a[i] - 'a']++;
        }
        if(k == n - 1)
        {
            cout << "yes" << endl;
            continue;
        }
        else if(k > n - 1)
        {
            cout << "no" << endl;
            continue;
        }
        int len = n - k;
        len /= 2;
        int cnt = 0;
        for(int i = 0; i <= 25; i++)
        {
            cnt += c[i] / 2;
        }
        if(cnt >= len)
        {
            cout << "yes" << endl;
        }
        else cout << "no" << endl;
    }
    return 0;
}
```

---

