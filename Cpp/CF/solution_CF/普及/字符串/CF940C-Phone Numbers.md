# Phone Numbers

## 题目描述

And where the are the phone numbers?

You are given a string $ s $ consisting of lowercase English letters and an integer $ k $ . Find the lexicographically smallest string $ t $ of length $ k $ , such that its set of letters is a subset of the set of letters of $ s $ and $ s $ is lexicographically smaller than $ t $ .

It's guaranteed that the answer exists.

Note that the set of letters is a set, not a multiset. For example, the set of letters of abadaba is $ {a,b,d} $ .

String $ p $ is lexicographically smaller than string $ q $ , if $ p $ is a prefix of $ q $ , is not equal to $ q $ or there exists $ i $ , such that $ p_{i}<q_{i} $ and for all $ j<i $ it is satisfied that $ p_{j}=q_{j} $ . For example, abc is lexicographically smaller than abcd , abd is lexicographically smaller than abec, afa is not lexicographically smaller than ab and a is not lexicographically smaller than a.

## 说明/提示

In the first example the list of strings $ t $ of length 3, such that the set of letters of $ t $ is a subset of letters of $ s $ is as follows: aaa, aab, aac, aba, abb, abc, aca, acb, $ ... $ . Among them, those are lexicographically greater than abc: aca, acb, $ ... $ . Out of those the lexicographically smallest is aca.

## 样例 #1

### 输入

```
3 3
abc
```

### 输出

```
aca
```

## 样例 #2

### 输入

```
3 2
abc
```

### 输出

```
ac
```

## 样例 #3

### 输入

```
3 3
ayy
```

### 输出

```
yaa
```

## 样例 #4

### 输入

```
2 3
ba
```

### 输出

```
baa
```

# 题解

## 作者：yaolibo (赞：6)

[题目链接](https://www.luogu.com.cn/problem/CF940C)
## 题意解释：
给定一个长度为 $n$ 的字符串 $s$，需要使用 $s$ 中出现过的字母组成一个长度为 $k$ 的新字符串 $T$，要求 $T$ 是所有字典序大于 $s$ 且长度为 $k$ 的字符串中字典序最小的字符串。
## 思路 & 方法：贪心
这道题的突破口在于 $n$ 和 $k$ 的大小关系，于是我们先将 $s$ 中的字母从大到小排序，将其存入数组 $t$ 中，然后对于 $n$ 和 $k$ 的三种情况进行分类讨论：
### ① $n < k$ :
这貌似是最简单的一种情况，要使 $T > s$ ,使其字典序最小的方式便是先原封不动地输出 $s$ （这样就保证了 $T$ 一定大于 $s$ ），而后面 $n - k$ 个字符肯定是越小越好，于是就全部输出 $s$ 中最小的字母（即 $t_n$）就可以了。**(详见样例4)**  
**以下是该部分的代码（ $t$ 已是 $s$ 从大到小排序后的字符串）：**  
```
for (i = 1; i <= n; i++)
	printf("%c", s[i]); //原封不动输出s
for (i = n + 1; i <= k; i++)
	printf("%c", t[n]); //剩下的字符输出s中最小的字符，即t[n]。
```
### ② $n > k$ :
因为字符串的大小是从左至右依次比较的，所以最好的贪心策略则是从 $k$ 开始从右至左依次考虑每一位是否可以替换为比它大一点点的字符，这时会遇到两种情况：  
1. 当前字符是 $s$ 串中最大的字符，即没有比它大的字符可以替换，这时就需要考虑前一位，依次遍历，直到找到可替换的字符就退出。
2. 当前字符不是 $s$ 串中最大的字符，于是就在 $t$ 串中找第一个比它大的字符来替换（贪心），随后同①，剩下的字符全部用 $t_n$ 替换。  

**举个例子：**  
$n = 5, k = 4, s = abdda$ ，此时 $t$ 应为 $"ddbaa"$ ，从第 $k$ 位开始找：
- $i = 4$ ，此时 $s_4 = 'd'$ 为 $s$ 中最大的字符，所以往下遍历；
- $i = 3$ ，此时 $s_3 = 'd'$ 依然为 $s$ 中最大的字符，继续往下遍历；
- $i = 2$ ，此时 $s_2 = 'b'$ 不是最大的字符，可以找到 $t$ 中第一个比 'b' 大的字符 'd'，所以 $s_2 = 'd'$ ，跳出循环；
- 先输出 $i$ 位字符，即 $"ad"$ ，然后剩下 $k - i$ 位字符全部输出 $t_n$ ，即 $'a'$ ，所以最终答案为 $"adaa"$ 。

**以下是该部分的代码（ $t$ 已是 $s$ 从大到小排序后的字符串）：**  
```
for (i = k; i >= 1; i--) { //从第k位开始遍历
	for (j = 1; j <= n; j++) //找到第一个大于s[i]的字符 
		if (t[j] <= s[i])
			break;
	if (j != 1) { //说明当前字符不是最大字符，于是替换，退出
		s[i] = t[j - 1]; //注意第j位是第一个小于等于s[i]的字符，第j-1位才是第一个大于s[i]的字符
		break;
	} //否则就继续往下遍历
}
for (j = 1; j <= i; j++)
	printf("%c", s[j]); //输出前i位
for (j = i + 1; j <= k; j++)
	printf("%c", t[n]); //剩下的全部输出t[n]（贪心）
```
### ③ $n = k$ ：
这种情况和 $n > k$ 的情况差不多，思路和②几乎相同 **（详见样例1、样例3）**，这里就不再赘述，上代码：
```
for (i = k; i >= 1; i--) {
	for (j = 1; j <= n; j++) 
		if (t[j] <= s[i])
			break;
	if (j != 1) { 
		s[i] = t[j - 1]; 
		break;
	}
}
for (j = 1; j <= i; j++)
	printf("%c", s[j]); 
for (j = i + 1; j <= n; j++)
	printf("%c", t[n]); 
```
大家可以发现，②和③的代码几乎一致，只是倒数第2行的循环终止条件不同，但实际上它们是完全相同的，因为在③中， $n$ 本身就是等于 $k$ 的，所以可以把这两种情况合并。

------------
### Code：
```
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
#define N 110000
using namespace std;
int n, k, i, j;
char s[N], t[N];
bool cmp(char e, char f) { //从大到小排序
	return e > f;
}
int main() {
	scanf("%d%d%s", &n, &k, s + 1); //s + 1 可以让字符数组下标从1开始
	for (i = 1; i <= n; i++)
		t[i] = s[i]; //先复制字符数组s中的字符到t
	sort(t + 1, t + 1 + n, cmp); //将t从大到小排序
	if (n < k) { //第①种情况
		for (i = 1; i <= n; i++)
			printf("%c", s[i]); //原封不动输出s
		for (i = n + 1; i <= k; i++)
			printf("%c", t[n]); //剩下的字符输出s中最小的字符，即t[n]。
	}
	else { //第②③种情况
		for (i = k; i >= 1; i--) { //从第k位开始遍历
			for (j = 1; j <= n; j++) //找到第一个大于s[i]的字符
				if (t[j] <= s[i])
					break;
			if (j != 1) { //说明当前字符不是最大字符，于是替换，退出
				s[i] = t[j - 1]; //注意第j位是第一个小于等于s[i]的字符，第j-1位才是第一个大于s[i]的字符
				break;
			} //否则就继续往下遍历
		}
		for (j = 1; j <= i; j++)
			printf("%c", s[j]); //输出前i位
		for (j = i + 1; j <= k; j++)
			printf("%c", t[n]); //剩下的全部输出t[n]（贪心）
	}
	return 0;
}
```
### 结束~Over~

---

## 作者：__int127 (赞：1)

## CF940C Phone Numbers 题解

[**题目传送门**](https://www.luogu.com.cn/problem/CF940C)

### 题目大意

给定一个长度为 $n$ 的字符串 $s$，求出字典序最小的字符串 $t$，满足：

- $|t|=k$

- $t$ 的字典序大于 $s$

- 对于任意的字符 $x$，$s$ 和 $t$ 均包含 $x$

保证有解。

$1\le n,k\le10^5$

### 思路

此题需分类讨论。

#### 1.$n<k$

这也是最简单的一个，先输出 $s$，这样可以保证 $t>s$，再输出和 $n-k$ 个 $\min\limits^n_{i=1}s_i$ 就好了，这样可以保证 $t$ 的字典序最小。

#### 2.$n=k$

可以从后向前遍历 $s$，当 $s_i\neq\max\limits^n_{i=1}s_i$，就将 $s_i$ 替换为满足以下条件的字符：

- ASCII 码大于 $s_i$

- ASCII 码最小

- 包含在 $s$ 里

这样就结束了吗，我们举个例子。

令 $n=3,k=3,s=\texttt{abc}$（即样例 $1$）。

按照刚才的思路，$s$ 会变成 $\texttt{acc}$，可正确答案应该是 $\texttt{aca}$，为什么呢？

因为后面将 $s$ 照抄了下来，并不是字典序最小，这需要将后面变成 $s$ 中最小的字符，即将 $s_{i+1},s_{i+2},s_{i+3},\cdots,s_{n-1},s_n$ 变为 $\min\limits^n_{i=1}s_i$。

#### 3.$n>k$

思路和 $n=k$ 的情况差不多，只不过变成了 $s_i\neq\max\limits^k_{i=1}s_i$ 的情况才替换，并且为了防止输出不是 $k$ 个，后面需要补 $k\,-$ 输出字符的个数个 $\min\limits^n_{i=1}s_i$。

### 代码+注释

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, k;
char minn = 'z' + 1, t[100005];
string s;
bool cmp(char x, char y) {
	return x > y;
}
char find(int i){// 寻找比 s[i]“大一点”的字符
	for (int j = n - 1; j >= 0; j--){
		if (t[j] > s[i]){
			return t[j];
			break;
		}
	}
}
int main(){
	cin >> n >> k;
	cin >> s;
	for (int i = 0; i < n; i++){
		t[i] = s[i];
        minn = min(minn, s[i]);// 查找 s 中最小的字符
	}
	sort(t, t + n, cmp);// 排序，方便查找
	if (k > n){// n<k
		cout << s;
		for (int i = 1; i <= k - n; i++){
			cout << minn;
		}
	} else if (k == n){//n=k
		for (int i = n - 1; i >= 0; i--){
			if (s[i] != t[0]){
				for (int j = 0; j < i; j++){
					cout << s[j];
				}
				cout << find(i);
				for (int j = i + 1; j < n; j++){
					cout << minn;
				}
				break; 
			}
		}
	} else {//n>k
		int num = 0;
		for (int i = k - 1; i >= 0; i--){
			if (s[i] != t[0]){ 
				for (int j = 0; j < i; j++, num++){
					cout << s[j];
				}
				cout << find(i);
				num++;
				break;
			}
		} 
		if (num < k){
			for (int i = 1; i <= k - num; i++){
				cout << minn;
			}
		} 
	}
	// 上面判断语句的讲解已在「思路」中给出。
	return 0;
}
```

### 最后

本题题解到此结束，希望大家能看懂、有思路。

---

## 作者：codeLJH114514 (赞：1)

[$\colorbox{#5898db}{\color{white}返回题目}$](https://www.luogu.com.cn/problem/CF940C)

## 题目大意

给你一个长度为 $n$ 的字符串 $s$，让你求出一个字符串 $t$，使得：

- $t > s$（字典序）
- $\vert t \vert = k$
- 对于任意字符 $c$，如果它在 $t$ 中出现过则一定在 $s$ 中也出现过。

如果有多种答案，输出最小的。

## 数据范围

数据保证有解。

$1 \leq n \leq 10^5$

$1 \leq k \leq 10^5$

## 解题思路

考虑分类讨论：

1. $n \geq k$

思路：贪心。

在字符串的前 $k$ 个字符里面枚举。

如果它不是最大的字符，那么就把它加上一点点（把他改成比它大的最小的字符。），并将后面的字符都改成最小的字符（贪心）。否则不管。（因为如果是最大的字符的话，就没有更大的字符了，也就不能让新字符串更大了。）

然后只需把更改后的字符串的大小设为 $k$ 即可。（这里可以使用字符串内置函数 $\texttt{resize}$）

2. $n < k$

这种很简单，直接向原字符串中加入 $k - n$ 个最小的字符即可。

这里求最大最小字符可以使用 $\texttt{min\_element}$ 和 $\texttt{max\_element}$，找它大的最小的字符可以使用 $\texttt{upper\_bound}$（切记先排序，排序用 $\texttt{sort}$ 就行。）。

## 完整代码

```cpp
#include <algorithm>
#include <iostream>
using namespace std;
int n, k;
string s;
int main() {
    cin >> n >> k >> s;
    if (n >= k) { // 第一种情况。
        char mx = *max_element(s.begin(), s.end());
        char mi = *min_element(s.begin(), s.end()); // 找出最大最小字符。
        // 注意：min_element && max_element 返回值均为迭代器（可以理解为指针），所以还需要再解引用。
        for (int i = k - 1; i >= 0; i--) // 枚举字符。
            if (s[i] != mx) {
                string r = s;
                sort(r.begin(), r.end()); // 使用 upper_bound 之前先排序。
                s[i] = *upper_bound(r.begin(), r.end(), s[i]);
                for (int j = i + 1; j < k; j++)
                    s[j] = mi;
                s.resize(k); // 重新设置大小。
                cout << s;
                break;
            }
    } else if (n < k) { // 第二种情况。
        string ns = s;
        char ch = *min_element(ns.begin(), ns.end()); // 同理。
        for (int i = 1; i <= k - n; i++)
            ns += ch;
        cout << ns;
    }
    return 0;
}
```

---

## 作者：TLMPEX (赞：1)

这道题的主要思路就是贪心。

代码：

```c
#include<iostream>
#include<cstring>
#include<cmath>
#include<cstdio>

using namespace std;

const int maxn = 100005;
int n,k;
int vis[30];
char s[100005];
char ans[100005];

int main(){
    scanf("%d%d",&n,&k);
    scanf("%s",s);
    for(int i=0;i<n;i++)
        vis[s[i]-'a']=1;
    if(k>n){
        printf("%s",s);
        for(int i=0;i<26;i++){
            if(vis[i]){
                int kk=k-n;
                while(kk--) 
					printf("%c",i+'a');
                puts("");
                break;
            }
        }
    }
    else{
        strcpy(ans,s);
        ans[k]='\0';
        char Min='z';
        char Max='a';
        for(int i=0;i<26;i++){
            if(vis[i]){
                Min=i+'a';
                break;
            }
        }
        for(int i=25;i>=0;i--){
            if(vis[i]){
                Max=i+'a';
                break;
            }
        }
        for(int i=k-1;i>=0;i--){
            if(ans[i]!=Max){
                for(int j=ans[i]-'a'+1;j<26;j++){
                    if(vis[j]){
                        ans[i]=j+'a';
                        break;
                    }
                }
                printf("%s\n",ans);
                return 0;
            }
            else
                ans[i]=Min;
        }
        puts(ans);
    }
}
```


---

## 作者：封禁用户 (赞：0)

为了 $t$ 的字典序最小，考虑从串首开始贪心。

看完样例之后应该能很容易想到 $k>n$ 的做法：

对于 $1\sim n$ 位，最优情况为全部和 $s$ 取相同字符，此时 $t$ 与 $s$ 的字典序一样，不管后面填什么字符都满足题目要求。于是一直填 $s$ 中最小的字符确保字典序最小。

然后对于剩下情况，使得字典序最小，那我们的贪心策略就是：

* 如果 $t_i$ 能与 $s_i$ 取相同字符则取。
* 如果不能则选就取 $>s_i$ 中最小的一个字符填上去，此时 $t$ 的字典序已经大于 $s$ 了。然后后面一直加最小字符来确保字典序最小就行了。

如何判断 $t_i$ 能否与 $s_i$ 取一样？显然如果 $t_{i+1}\sim t_{k}$ 能有一位使得 $t$ 的字典序大于 $s$ 就可行。

显然，除 $s$ 后面字符都为最大值的情况外，$t_{i+1}\sim t_k$ 都至少有一位能够使得 $t$ 的字典序大于 $s$。

具体实现用后缀和。

```cpp
#include<bits/stdc++.h>
#define sd std::
//#define int long long
#define inf 0x3f3f3f3f
#define linf 1e18
#define il inline
#define db double
#define ldb long double
#define F(i,a,b) for(int i=(a);i<=(b);i++)
#define f(i,a,b) for(int i=(a);i>=(b);i--)
#define MIN(x,y) (x<y?x:y)
#define MAX(x,y) (x>y?x:y)
#define me(x,y) memset(x,y,sizeof x)
#define pii sd pair<int,int>
#define umap(x,y) sd unordered_map<x,y>
#define pque(x) sd priority_queue<x>
#define X first
#define Y second
#define kg putchar(' ')
#define Fr(a) for(auto it:a)
#define dbg(x) sd cout<<#x<<": "<<x<<sd endl
il int read(){int w=1,c=0;char ch=getchar();for(;ch>'9'||ch<'0';ch=getchar()) if(ch=='-') w=-1;for(;ch>='0'&&ch<='9';ch=getchar()) c=(c<<3)+(c<<1)+ch-48;return w*c;}
void printt(int x){if(x>9) printt(x/10);putchar(x%10+48);}
il void print(int x){if(x<0) putchar('-'),printt(-x);else printt(x);}
il void put(int x){print(x);putchar('\n');}
il void printk(int x){print(x);kg;}
const int N=1e5+10;
char c[N];
sd set<int> s;
int n,k,a[N],b[N];
il void solve()
{
	n=read(),k=read();
	scanf("%s",c+1);
	int mi=inf,ma=0;
	F(i,1,n) mi=MIN(mi,c[i]-'a'),ma=MAX(ma,c[i]-'a'),s.insert(c[i]-'a');
	if(k>n)
	{
		F(i,1,n) printf("%c",c[i]);
		F(i,n+1,k)printf("%c",mi+'a');
		return;
	}
	F(i,1,n) a[i]=((c[i]-'a')==ma);//是否为最大
	f(i,k,1) b[i]=b[i+1]+a[i];//后缀和
	F(i,1,k)
	{
		if(b[i+1]==k-i)
		{
			F(j,1,i-1) printf("%c",c[j]);
			printf("%c",char(*s.upper_bound(c[i]-'a')+'a'));
			F(j,i+1,k) printf("%c",mi+'a');
			return;
		}
	}
	
}
int main()
{
	int T=1;
//	T=read();
	while(T--) solve();
    return 0;
}
 
```

---

