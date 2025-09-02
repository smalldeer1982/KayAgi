# Equivalent Strings

## 题目描述

Today on a lecture about strings Gerald learned a new definition of string equivalency. Two strings $ a $ and $ b $ of equal length are called equivalent in one of the two cases:

1. They are equal.
2. If we split string $ a $ into two halves of the same size $ a_{1} $ and $ a_{2} $ , and string $ b $ into two halves of the same size $ b_{1} $ and $ b_{2} $ , then one of the following is correct: 
  1. $ a_{1} $ is equivalent to $ b_{1} $ , and $ a_{2} $ is equivalent to $ b_{2} $
  2. $ a_{1} $ is equivalent to $ b_{2} $ , and $ a_{2} $ is equivalent to $ b_{1} $

As a home task, the teacher gave two strings to his students and asked to determine if they are equivalent.

Gerald has already completed this home task. Now it's your turn!

## 说明/提示

In the first sample you should split the first string into strings "aa" and "ba", the second one — into strings "ab" and "aa". "aa" is equivalent to "aa"; "ab" is equivalent to "ba" as "ab" = "a" + "b", "ba" = "b" + "a".

In the second sample the first string can be splitted into strings "aa" and "bb", that are equivalent only to themselves. That's why string "aabb" is equivalent only to itself and to string "bbaa".

## 样例 #1

### 输入

```
aaba
abaa
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
aabb
abab
```

### 输出

```
NO
```

# 题解

## 作者：ljk8886 (赞：7)

## 题目分析
很容易发现这题能用分治解决，如果字符串长度是偶数时，就将它分成两个字符串 $a1$ 和 $a2$，另一个字符串同理，分成 $b1$ 和 $b2$。接下来分别判断两种情况：

1. $a1$ 和 $b1$ 相等且 $a2$ 和 $b2$ 相等。

2. $a1$ 和 $b2$ 相等且 $a2$ 和 $b1$ 相等。

如果满足任意一种情况，就返回 `true`，否则返回 `false`。

给到代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
string a, b;
bool dfs(string a, string b)
{
	int l = a.size();
	if (l & 1) return a == b;
	string a1 = a.substr(0, l / 2), a2 = a.substr(l / 2, l / 2);
	string b1 = b.substr(0, l / 2), b2 = b.substr(l / 2, l / 2);
	bool f1 = dfs(a1, b1) && dfs(a2, b2);
	bool f2 = dfs(a1, b2) && dfs(a2, b1);
	return f1 || f2;
}
int main()
{
	cin >> a >> b;
	if (a.size() != b.size()) cout << "NO" << endl;
	else if (dfs(a, b)) cout << "YES" << endl;
	else cout << "NO" << endl;
	return 0;
}
```

结果发现愉快超时了，为什么呢？

我们看一下数据范围，$|s| \le 2 \times 10^5$，约等于 $2^{21}$。而时间复杂度是 $\mathcal{O}(4^{\log n})$，所以肯定超时。

那怎么办呢？

我们发现想通过此题，时间复杂度至多是 $\mathcal{O}(2^{\log n})$，所以递归里的分支最多只能有两个。于是考虑将两个字符串分开处理，我们可以发现按题目中给的规则将两个字符串最小化或最大化即可。

下面给到正确代码：

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
string a, b;
string minstr(string s)
{
	int l = s.size();
	if (l & 1) return s; //长度如果是奇数，就直接返回这个字符串 
	string s1 = s.substr(0, l / 2), s2 = s.substr(l / 2, l / 2); //长度如果是偶数，就先把它分成两份 
	s1 = minstr(s1), s2 = minstr(s2); //把这两个字符串最小化 
	return (s1 < s2 ? s1 + s2 : s2 + s1); //把小的字符串放前面，上面我说过了 
}
int main()
{
	cin >> a >> b;
	if (a.size() != b.size()) cout << "NO" << endl; //长度不相等，直接 NO 
	else if (minstr(a) == minstr(b)) cout << "YES" << endl; //如果两个字符串最小化后一样，那就直接 YES 
	else cout << "NO" << endl; //否则 NO 
	return 0;
}
```

---

## 作者：allenchoi (赞：2)

首先吐槽一下，题意翻译不全，结果走了弯路。
### 科技：哈希、递归搜索（剪枝）
### 题意：  
有两个相同长度（设为 $n$ ）的字符串 $a,b$ ，判断是否等价。  
等价的定义如下：  
1.若 $a = b$ ，则 $a,b$ 等价。  
2.将 $a$ 分为两半 $s1,s2$ ， $b$ 分为两半 $s3,s4$ （两半长度相等），若 $s1,s3$ 等价且 $s2,s4$ 等价，或 $s1,s4$ 等价且 $s2,s3$ 等价，则 $a,b$ 等价。  
### 思路：  
我最先想到的解法是哈希加递归。写一个函数 $cmp(l1,r1,l2,r2)$ ，判断 $a[l1,r1]$ 与 $b[l1,r2]$ 是否等价。首先判断两个子串是否相等，再递归。就是说，搜索树上的每个节点有 $4$ 个儿子，最多有 $\log n$ 约等于 $17$ 层。提交后在第 $91$ 个点 T 了。  
考虑优化：  
根据题意易得，两个字符串等价，那么它们所包含的字符构成的可重集合必然相等。于是，我们预处理一个统计字符个数的前缀数组，在 $n$ 较大时（这里取   $5000$ ，再大就有 T 的可能，可以用计算器抠一下），每层递归多判断 $26$ 次检查各个字母出现的次数是否相等。事实证明这是一个很有效的剪枝。  
### 代码：
```cpp
#include <cstdio>
#include <cstring>
using namespace std;
const int N = 2e5 + 5,K = 131,mod = 200026627;
//随即弄出来的一个质数模数
int n,base[N],hash1[N],hash2[N],sum1[N][K],sum2[N][27];
char a[N],b[N];
bool cmp(int l1,int r1,int l2,int r2)
{
	int len = r1 - l1 + 1,mid1,mid2; 
	if((hash1[r1] - 1LL * hash1[l1 - 1] * base[len] % mod + mod) % mod
	 == (hash2[r2] - 1LL * hash2[l2 - 1] * base[len] % mod + mod) % mod) //哈希判断是否相等
	 	return true;
	if(n > 5000) for(int i = 0;i <= 25;i++) if(sum1[r1][i] - sum1[l1 - 1][i] != sum2[r2][i] - sum2[l2 - 1][i]) return false;
    //判断集合是否相等的剪枝
	if(len % 2 == 0)
	{
		mid1 = l1 + len / 2 - 1,mid2 = l2 + len / 2 - 1; 
		if(cmp(l1,mid1,l2,mid2) && cmp(mid1 + 1,r1,mid2 + 1,r2)) return true;
		if(cmp(l1,mid1,mid2 + 1,r2) && cmp(mid1 + 1,r1,l2,mid2)) return true;
	}//四个儿子的搜索树，贼大
	return false;
}
int main()
{
	scanf("%s%s",a + 1,b + 1);
	n = strlen(a + 1);
	base[0] = 1;
	for(int i = 1;i <= n;i++)
	{
		base[i] = 1LL * base[i - 1] * K % mod;
		hash1[i] = (1LL * hash1[i - 1] * K % mod + a[i]) % mod;
		hash2[i] = (1LL * hash2[i - 1] * K % mod + b[i]) % mod;
		for(int j = 0;j <= 25;j++)
		{
			sum1[i][j] = sum1[i - 1][j];
			sum2[i][j] = sum2[i - 1][j];
		}
		sum1[i][a[i] - 'a']++;
		sum2[i][b[i] - 'a']++;
	}//处理前缀、k的次幂、哈希值
	if(cmp(1,n,1,n)) printf("YES\n");
	else printf("NO\n");
	return 0;//华丽收场
}
```
总的来说，这是一道不错的搜索题目，运用了字符串算法。希望这篇题解对大家能有所帮助！  
~~某初二菜狗趁网课时偷偷写的，求求审核过吧TvT~~

---

## 作者：DennyQi (赞：2)

根据定义，任意一个字符串对应着一个`与它等价的字符串集合`。两个字符串如果等价，他们的等价集合就一定完全相同。如果两个字符串的等价集合中有任意两个字符串相同，那么这两个字符串就是等价的。我们不妨去找两个集合中字符串最小的（当然最大的也是没有问题的），如果最小的那两个相等，那么就等价。

于是，问题转化为如何找到与一个字符串等价的最小字典序字符串。这个可以根据定义直接递归解决。

```cpp
/*DennyQi 2019*/
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#include <iostream>
#include <string>
using namespace std;
const int N = 200010;
inline int read(){
    int x(0),w(1); char c = getchar();
    while(c^'-' && (c<'0' || c>'9')) c = getchar();
    if(c=='-') w = -1, c = getchar();
    while(c>='0' && c<='9') x = (x<<3)+(x<<1)+c-'0', c = getchar(); 
    return x*w;
}
string s1,s2;
string minstring(string s){
	if(s.size() & 1) return s;
	string S1 = s.substr(0,s.size()/2);
	string S2 = s.substr(s.size()/2,s.size()/2);
	S1 = minstring(S1);
	S2 = minstring(S2);
	if(S1 < S2) return S1 + S2;
	return S2 + S1;
}
int main(){
	// freopen("file.in","r",stdin);
	cin >> s1 >> s2;
	if(s1.size() != s2.size()){
		printf("NO");
		return 0;
	}
	if(minstring(s1) != minstring(s2)){
		printf("NO");
	}else printf("YES");
	return 0;
}
```

---

## 作者：Ryan_Adam (赞：0)

## CF559B Equivalent Strings 题解
### 题目描述
吐槽一下，题目翻译有歧义。

### 思路分析
你会发现，当你需要判断字符串 $a,b$ 是否等价时，如果长度为偶数，需要继续判断字符串 $a$ 拆分的字串。
### 所用知识
```cpp
s.substr(i,j)//在字符串s中，从位置i开始截取长度为j的字串
```

### 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;
namespace Raiden
{
	bool check(string a,string b)//判断a、b是否等价 
	{
		int lena=a.size();
		if(lena%2)// 如果长度为奇数 
		{
			return a==b;// a、b等价即为字符串相等 
		} 
		else//否则长度为偶数 
		{
			//a分成两段 
			string s1=a.substr(0,lena/2);//前半段 
			string s2=a.substr(lena/2,lena/2);//后半段
			//b分成两段
			string s3=b.substr(0,lena/2);//前半段
			string s4=b.substr(lena/2,lena/2);//后半段
			
			return (check(s1,s4)&&check(s2,s3))||(check(s1,s3)&&check(s2,s4));
		}
	}
    int work()
    {
		string a,b;
		cin>>a>>b;
		cout<<(check(a,b)?"YES":"NO")<<endl;
        return 0;
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return Raiden::work();
}

```

---

## 作者：_shine_ (赞：0)

直接递归模拟即可，即偶数继续往下分别对应两种情况搜索，到奇数直接从左到右扫一遍两段是否相等。

注意不要使用 ```|&``` 这两个运算符（会超时），直接用 ```if``` 或 ```&&||```，同时注意长度的计算。。
#### code

```cpp
// LUOGU_RID: 168728244
#include<bits/stdc++.h>
using namespace std;
string a,b;
int check(int l1,int r1,int l2,int r2){
//	cout << l1 << " " << r1 << " " << l2 << " " << r2 << endl;
	if((r1-l1+1)%2==1){//长度为奇数。
		for(int i=0;i<r1-l1+1;++i)if(a[l1+i]!=b[l2+i])return 0;
		return 1;
	}else{
		int cnt1=l1+(r1-l1+1)/2-1,cnt2=l2+(r2-l2+1)/2-1;
		return (check(l1,cnt1,l2,cnt2) && check(cnt1+1,r1,cnt2+1,r2)) || (check(l1,cnt1,cnt2+1,r2) && check(cnt1+1,r1,l2,cnt2));//分两种情况讨论：(l1&r1,l2&r2)以及(l1&r2,l2&r1)。
	}
}
signed main(){
	cin >> a >> b;
	if(check(0,a.size()-1,0,b.size()-1)==1)puts("Yes");
	else puts("No"); 
	return 0;
} 
```

---

## 作者：_zqh_ (赞：0)

[更佳的阅读体验](https://www.luogu.com.cn/blog/Tengmax-blog/solution-cf559b)，[原题传送门](https://www.luogu.com.cn/problem/CF559B)。

# 思路简述

本题题目要求求出 $a$ 是否能够通过若干次操作变成 $b$。

不妨将 $a$ 所有能变换出来的所有字符串放进一个集合 $\text {S}$；

同理将 $b$ 所有能变换出来的所有字符串放进一个集合 $\text {T}$；

那么集合 $\text {S}$ 中的字典序最小的字符串 $\text {S}_{\min}$ 若与 $\text {T}_{\min}$ 相同，那么 $a$ 一定能通过若干次变换变成 $b$；
证明略。

因此只需要求出集合 $\text {S}$ 以及集合 $\text {T}$ 即可。

更进一步的，或许我们只需要求出 $\text {S}_{\min}$ 和 $\text {T}_{\min}$ 即可。

这里采用 **分治** 的思想。

**思路部分完结**。

下面是算法部分。

递归传入一个字符串 $\text {str}$，若 $|\text {str}| $ 为奇数，即无法再次进行操作，直接返回。

否则，将 $\text {str}$ 的左半部分和右半部分分别送进递归迭代，最后得到的两个迭代后的字符串按字典序拼起来即可。

**算法部分完结**。

# Code

```cpp
#include <bits/stdc++.h>
#define ios                  \
    ios::sync_with_stdio(0); \
    cin.tie(0);              \
    cout.tie(0)
// #pragma GCC optimize(2)
#define ll long long
#define pll pair<ll, ll>
#define pii pair<int, int>
#define il inline
using namespace std;

string SubString(string a, int Left, int Right) {//截取字符串
    string ans = "";
    for (int i = Left; i <= Right; i++) {
        ans.push_back(a[i]);
    }
    return ans;
}

/*
下面这个函数可以不用写返回，
直接在字符串所在的地址进行操作即可。
*/
void MakeDictionary(string& a) {//构造Smin，Tmin。
    if (a.size() & 1) {
        return;
    }
    string aLeft = SubString(a, 0, (a.size() >> 1) - 1);
    string aRight = SubString(a, a.size() >> 1, a.size() - 1);
    MakeDictionary(aLeft), MakeDictionary(aRight);
    if (aLeft < aRight)
        a = aLeft + aRight;
    else
        a = aRight + aLeft;
}

string a, b;

int main() {
    ios;
    cin >> a >> b;
    MakeDictionary(a);
    MakeDictionary(b);
    if (a == b) {
        cout << "YES";
    } else
        cout << "NO";
    return 0;
}
```

---

## 作者：BigJoker (赞：0)

# 0x00 分析

根据题目讲述的规则打，题目描述中将字符串分成两半可以用递归来实现。因为在判断过程中可能需要将字符串分成两半，所以我们可以用四个下标 $l1$，$r1$ 表示第一个字符串的开头和结尾，$l2$，$r2$ 表示第二个字符串的开头和结尾（两者都是截取）。然后照着题目规则打即可。

# 0x01 实现思路

先考虑这个截取部分的长度 $len$ 的奇偶性，如果为奇数，那么只能逐字符判断，因为已经是奇数，不能再分成两半了。如果为偶数，虽然依然会遇到逐字符判断相等的情况，但是可以这么想：如果两个字符串都已经相等了，那么把它们分成两半照样会相等，所以为了~~偷懒~~节约代码量，我们可以直接打递归。

# 0x02 具体实施

对于为奇数的情况不需要多讲。

对于是偶数的情况，先将两个字符串的中点算出来。

然后讨论两种情况。

第一种情况，第一个字符串的前、后段分别与第二个字符串的前、后段相似。

第一种情况，第一个字符串的后、前段分别与第二个字符串的前、后段相似。

两个条件满足其中任意一个都可以，上代码。

# 0x03 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
string a,b;
int len;
bool check(int l,int r,int l1,int r1){
	if((r-l+1)%2==1){
		for(int o=0;o<=r-l;o++)
			if(a[l+o]!=b[l1+o]) return 0;
		return 1;
	}
	else{
		int mid1=(l+r)/2,mid2=(l1+r1)/2;
		if((check(l,mid1,l1,mid2) && check(mid1+1,r,mid2+1,r1)) || (check(l,mid1,mid2+1,r1) && check(mid1+1,r,l1,mid2))) return 1;
		return 0;
	}
}
int main(){
	int t;t=1;
	while(t--){
		cin>>a>>b;len=a.size();
		if(check(0,len-1,0,len-1)) puts("YES");
		else puts("NO");
	}
	return 0;
}
```


---

## 作者：Liynw (赞：0)

### 前言

[题目传送门](https://www.luogu.com.cn/problem/CF559B)

**正解：模拟，递归。**

考试的 T4，还是想复杂了 qwq。

**这题不要用 STL，容易 $\texttt{TLE}$！！**

***

### 题意简述

~~翻译够简了。~~

对了给一下样例解释的翻译：

第一个样例的第一组测试数据中，对于 $a=aaba$ 和 $b=abaa$，可以分成 $a1=aa,a2=ba,b1=ab,b2=aa$；其中 $a1$ 和 $b2$ 全等。对于 $a=ba$ 和 $b=ab$，可以分成 $a1=b,a2=a,b1=a,b2=b$；其中 $a1$ 和 $b2$ 全等，$a2$ 和 $b1$ 全等。所以 $aaba$ 和 $abaa$ 相似。

第一个样例的第二组测试数据中，$aabb$ 和 $abab$ 不满足相似。

```LaTeX
第一个样例的第一组测试数据中，对于 $a=aaba$ 和 $b=abaa$，可以分成 $a1=aa,a2=ba,b1=ab,b2=aa$；其中 $a1$ 和 $b2$ 全等。对于 $a=ba$ 和 $b=ab$，可以分成 $a1=b,a2=a,b1=a,b2=b$；其中 $a1$ 和 $b2$ 全等，$a2$ 和 $b1$ 全等。所以 $aaba$ 和 $abaa$ 相似。

第一个样例的第二组测试数据中，$aabb$ 和 $abab$ 不满足相似。
```

***

### 分析

鉴于数据的特殊性 ~~（简称水）~~，我们可以直接按照题意递归即可。

因为输入的是两个字符串，而每次递归都需要两个新的字符串，而这两个新的字符串都是在以前的字符串上**截取一段**形成的。所以，我们根本不需要传字符串，只需要传在输入的字符串中**截取的部分开始、结束的下标**即可。

当然，因为每次判断都要传两个字符串，所以需要有两对参数，这里，$l1,r1$ 代表第一个字符串（从输入的第一个字符串中截取），$l2,r2$ 代表第二个字符串（从输入的第二个字符串中截取）。

首先，两个不同的判断条件打成两个函数 $\operatorname{f1}$ 和 $\operatorname{f2}$，分别判断奇数和偶数字符串长度的相似判定。

$\operatorname{f1}$ 的实现是很简单的，只需要逐字判断是否相等即可。

不过需要**注意细节**，在计算字符串的长度时，**不需要** $+1$。具体原因：本来计算长度的时候是要 $+1$ 的，但是因为 $l1$ 和 $l2$ 已经提供了字符串开始的地方，所以我们在这两个数的基准上**加的数**就是从 $0\sim r1-l1$ 共 $r1-l1+1$ 个数字，就不需要 $+1$ 了。

具体函数如下：

```cpp
bool f1(int l1,int r1,int l2,int r2){
	int t=r1-l1; //计算需要枚举判断的长度
	for(int i=0;i<=t;i++) if(a[l1+i]!=b[l2+i]) return 0; //不一样直接返回
	return 1; //所有的都一样
}
```

接着分析较难的递归函数 $\operatorname{f2}$。这个函数也是我们在主函数中调用的函数。

首先看传过来的字符串长度是奇数还是偶数。如果是奇数，直接返回 $\operatorname{f1}$ 的判断就可以了。

如果是偶数，那么就需要判断一分为二之后是否相似。定义两个变量 $mid1,mid2$ 分别表示两个字符串中间的下标，也就是分开的地方（注意这两个变量表示的是分开后前面那个字符串的最后一个元素），接着根据题意模拟即可，因为有两组配对，所以两组都要判断。注意先 `&&` 再 `||`。

这个地方容易打错，记得好好检查。

（对了提醒大家一定要记得**不要把函数名给打掉了**，我就是这么错的 qwq。）

$\operatorname{f2}$ 的代码如下（别在意多余的空格，因为放一个框框里怕是有点不美观，我格式化了一下代码）：

```cpp
bool f2(int l1, int r1, int l2, int r2) {
    if ((r1 - l1 + 1) & 1)
        return f1(l1, r1, l2, r2);
    int mid1 = (l1 + r1) >> 1, mid2 = (l2 + r2) >> 1;
    return f2(l1, mid1, l2, mid2) && f2(mid1 + 1, r1, mid2 + 1, r2) ||
           f2(l1, mid1, mid2 + 1, r2) && f2(mid1 + 1, r1, l2, mid2);
}
```

最后写好主函数，就可以把这道题切了 qwq。

***

不要做一些不道德的行为，洛谷的管理员会让你挂上牌子/xyx。

### $Code$

```cpp
//格式化了下代码哈 
#include <bits/stdc++.h>
using namespace std;
char a[200005], b[200005];
int len;
bool f1(int l1, int r1, int l2, int r2) {
    int t = r1 - l1;
    for (int i = 0; i <= t; i++)
        if (a[l1 + i] != b[l2 + i])
            return 0;
    return 1;
}
bool f2(int l1, int r1, int l2, int r2) {
    if ((r1 - l1 + 1) & 1)
        return f1(l1, r1, l2, r2);
    int mid1 = (l1 + r1) >> 1, mid2 = (l2 + r2) >> 1;
    return f2(l1, mid1, l2, mid2) && f2(mid1 + 1, r1, mid2 + 1, r2) ||
           f2(l1, mid1, mid2 + 1, r2) && f2(mid1 + 1, r1, l2, mid2);
}
int main() {
    scanf("%s %s", a + 1, b + 1);
    len = strlen(b + 1);
    if (f2(1, len, 1, len))
        printf("YES\n");
    else
        printf("NO\n");
    return 0;
}
```

***

### 写在最后

题目不难，细节有点 duliu。**大家打代码一定一定要注意细节啊 awa。**

---

## 作者：Harry_Hedwig (赞：0)

# 0x00 思路
先看题。
>给定两个字符串 $a,b$，询问它们是不是等价的。

>关于等价的定义：

>1.$a$ 和 $b$ **逐字符**相等

>2.若 $|a|$，$|b|$ **为偶数**，则将 $a$，$b$ **平分成两半**：$a_1$，$a_2$ 与 $b_1$，$b_2$。若满足：**$a_1$ 与 $b_1$ 等价且 $a_2$ 与 $b_2$ 等价或 $a_1$ 与 $b_1$ 等价且 $a_2$ 与 $b_1$ 等价，则 $a$ 和 $b$ 等价**。

~~哇这一看就是递归吗还需要看吗啊这~~

题目里有很明显的暗示，等价定义里套等价~~一看就俄罗斯套娃~~，所以会想到递归。递到最后若是等价那么 $a$ 和 $b$ 等价，否则不然。

# 0x01 递归
那么就按照题目的要求来做，即他说什么我做什么。

他说逐字符相等，安排：
```c
bool x=1;
for(i=la,j=lb;i<=ra&&j<=rb;i++,j++)//la,ra分别为a字符串的左右端点，lb,rb同上
{
	if(a[i]!=b[j])
	{
		x=0;
		break;
	}
}
if(x)//逐字符相等就不用再判断了
	return 1;
```
他说把偶数字符串分两半看，安排：（有一点长，耐心看完）
```c
bool xs(int la,int ra,int lb,int rb)
{
	
	if((ra-la+1)%2)
		return 0;
	return ((xs(la,(ra+la)/2,lb,(rb+lb)/2)&&xs((ra+la)/2+1,ra,(rb+lb)/2+1,rb))||(xs(la,(ra+la)/2,(rb+lb)/2+1,rb)&&xs((ra+la)/2+1,ra,lb,(rb+lb)/2)));//两种情况分别考虑
}
```
# code
```c
#include<bits/stdc++.h>
using namespace std;
char a[200005],b[200005];
bool xs(int la,int ra,int lb,int rb)
{
	int i,j;
	bool x=1;
	if(la==ra&&lb==rb)
		return (a[la]==b[lb]);
	for(i=la,j=lb;i<=ra&&j<=rb;i++,j++)
	{
		if(a[i]!=b[j])
		{
			x=0;
			break;
		}
	}
	if(x)
		return 1;
	if((ra-la+1)%2)
		return 0;
	//为了更好的阅读体验，此行超长的代码省去。（仅仅只是 return 而已）
	
}
int main()
{
	int n,i,j;
	scanf("%s",&a);
	scanf("%s",&b);
	int la=strlen(a),lb=strlen(b);
	if(xs(0,la-1,0,lb-1))//不要忘了换行哟~
		printf("YES\n");
	else
		printf("NO\n");
	return 0;
}
```

---

## 作者：agicy (赞：0)

# 题意

给定两个字符串$a,b$，询问它们是不是等价的（$Equivalent$，等效的，等价的）。

关于等价的定义：（以字符串$s$为例）

1. 如果$|s|$为奇数，那与$s$等价的字符串为它本身；
2. 如果$|s|$为偶数，那把$s$平分为两份，记作$s_{1},s_{2}$，与$s$等价的字符串为$s_{1}s_{2}$或$s_{2}s_{1}$

$|s|≤200000$

## 题面源代码

```
给定两个字符串$a,b$，询问它们是不是等价的（$Equivalent$，等效的，等价的）。

关于等价的定义：（以字符串$s$为例）

1. 如果$|s|$为奇数，那与$s$等价的字符串为它本身；
2. 如果$|s|$为偶数，那把$s$平分为两份，记作$s_{1},s_{2}$，与$s$等价的字符串为$s_{1}s_{2}$或$s_{2}s_{1}$

$|s|≤200000$
```

# 思路

显然当字符串$a,b$等价，$b,c$等价时$a,c$等价，所以我们只要求出原题中两个字符串对应的字典序最小的字符串进行比较即可。

# 代码

代码如下。

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
using std::cin;
#include<algorithm>
using std::min;
#include<string>
using std::string;

string a,b;

string sort(string);

int main(void){
    cin>>a>>b;
    puts(sort(a)==sort(b)?"YES":"NO");
    return 0;
}


string sort(string str){
    if(str.length()&1)
        return str;
    else{
        string k=sort(str.substr(0,str.length()>>1));
        string l=sort(str.substr(str.length()>>1));
        return min(k+l,l+k);
    }
}
```

## [我的评测记录](https://www.luogu.org/record/show?rid=13946768)


---

## 作者：66xyyd (赞：0)

## 题意

给出两个长度相等的字符串 $a,b$，定义“等价”（equivalent）关系如下。

1. 如果 $a$ 的长度为奇数，$a$ 与 $b$ 等价当且仅当 $a$ 与 $b$ 字典序相同。

2. 如果 $a$ 的长度为偶数，将 $a$ 从正中间（长度的一半）切开成两个字符串 $a_1,a_2$，将 $b$ 从正中间切成两个字符串 $b_1,b_2$，$a$ 与 $b$ 等价当且仅当：$a_1$ 与 $b_1$ 等价，$a_2$ 与 $b_2$ 等价；$a_1$ 与 $b_2$ 等价，$a_2$ 与 $b_1$ 等价。

## 题解

直接递归判断为 $O(n^2)$，附上一些奇奇怪怪的优化可以通过此题。但作者要介绍的是一种 $O(n\log n)$ 的做法。

首先这种等价关系有传递性。也就是说，如果 $a=b,b=c$，那么 $a=c$（这里的 $=$ 均表示题目中的等价关系，后文不加说明均默认为题目中的等价关系）。原因也很简单，因为按照定义，如果 $a=b$，那么 $a$ 可以通过一系列交换的操作得到 $b$。而 $b$ 又可以通过一系列操作得到 $c$，因此 $a$ 可以先得到 $b$ 又得到 $c$，$a$ 与 $c$ 等价。在这里“操作”的意思是：如果有一个字符串 $s$，且将 $s$ 从正中间（长度的一半）切开得到 $s_1,s_2$。那么我们把 $s \to s_1s_2$ 或 $s \to s_2s_1$ 的过程称为一次操作。根据定义，这些字符串是两两等价的。

根据这个性质，我们可以选取一个恰当的 $s$，使得 $a=s,b=s$。这样就可以得到 $a=b$。一种方案是，设置一个函数 $f(s)$，使得 $f(s)$ 是所有与 $s$ 等价的字符串中字典序最小的那个。这样我们只需要判断 $f(a)$ 是否与 $f(b)$ 字典序相同。证明略。

至于 $f(s)$，我们可以这样得到。如果 $s$ 长度是奇数，那么直接返回；否则将 $s$ 分半为 $s_1,s_2$，得到 $f(s_1),f(s_2)$ 并把字典序小的放前面。

```cpp
#include<iostream>
using namespace std;
string mindnc(const string &str){//题解中的函数f(s)
	if(str.size()&1)	return str;
	else{
		string s1=mindnc(string(str.begin(),str.begin()+(str.size()>>1)));
		string s2=mindnc(string(str.begin()+(str.size()>>1),str.end()));
		if(s1<s2)	return s1+s2;
		else	return s2+s1;
	}
}
int main(){
	string a,b;
	cin >> a >> b;
	if(mindnc(a)==mindnc(b))	cout << "YES";
	else	cout << "NO";
	return 0;
}
```

## 注释

1. 函数 $f(s)$ 返回的字符串确实为所有与 $s$ 等价的字符串中字典序最小的那个，证明：先假设 $f(s)$ 为所有与 $s$ 等价的字符串中字典序最小的那个。如果 $s$ 的长度为奇数，那么只有 $s$ 本身与自己等价，直接返回即可。将 $s$ 从正中间（长度的一半）切开得到 $s_1,s_2$。根据 $f(s)$ 的定义，我们有 $s_1$ 的字典序不比 $f(s_1)$ 的字典序更小，$s_2$ 的字典序不比 $f(s_2)$ 的字典序更小。因此我们有 $f(s_1)f(s_2) \le s_1s_2,f(s_2)f(s_1) \le s_2s_1$（这里的 $\le$ 指的是字典序小于等于）。考虑 $f(s)$ 与 $s$ 等价，因此与 $s$ 等价的字符串中字典序最小的要么为 $f(s_1)f(s_2)$ 要么为 $f(s_2)f(s_1)$，直接判断哪个字典序更小，放前面返回即可。因此 $f(s)$ 的做法确实成立。

---

