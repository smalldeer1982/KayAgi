# Canine poetry

## 题目描述

After his wife's tragic death, Eurydice, Orpheus descended to the realm of death to see her. Reaching its gates was uneasy, but passing through them proved to be even more challenging. Mostly because of Cerberus, the three-headed hound of Hades.

Orpheus, a famous poet, and musician plans to calm Cerberus with his poetry and safely walk past him. He created a very peculiar poem for Cerberus. It consists only of lowercase English letters.

We call a poem's substring a palindrome if and only if it reads the same backwards and forwards. A string $ a $ is a substring of a string $ b $ if $ a $ can be obtained from $ b $ by deleting several (possibly zero or all) characters from the beginning and several (possibly zero or all) characters from the end.

Unfortunately, Cerberus dislikes palindromes of length greater than $ 1 $ . For example in the poem abaa the hound of Hades wouldn't like substrings aba and aa.

Orpheus can only calm Cerberus if the hound likes his poetry. That's why he wants to change his poem so that it does not contain any palindrome substrings of length greater than $ 1 $ .

Orpheus can modify the poem by replacing a letter at any position with any lowercase English letter. He can use this operation arbitrarily many times (possibly zero). Since there can be many palindromes in his poem, he may have to make some corrections. But how many, exactly? Given the poem, determine the minimal number of letters that have to be changed so that the poem does not contain any palindromes of length greater than $ 1 $ .

## 说明/提示

In the first test case, we can replace the third character with c and obtain a palindrome-less poem bacba.

In the second test case, we can replace the third character with d and obtain a palindrome-less poem abdac.

In the third test case, the initial poem already doesn't contain any palindromes, so Orpheus doesn't need to change anything there.

## 样例 #1

### 输入

```
7
babba
abaac
codeforces
zeroorez
abcdcba
bbbbbbb
a```

### 输出

```
1
1
0
1
1
4
0```

# 题解

## 作者：苏22 (赞：16)


## 前言
###### 看到了一道~~很水的题~~ ，而且可以做题解，就立刻做了题解。

## 正解

首先，我们要知道，什么是回文串。

>百度解释： 
>
>“回文串”是一个正读和反读都一样的字符串，比如 `level` 或者 `noon` 等等就是回文串。

我们举个栗子：`aba` 是一个回文串，`abcdefghihgfedcba` 是一个回文串。

那么，根据题目意思，就是让一个字符串里没有回文串。比如：`abcdcba` 里有一个回文字串。我们要改的话，不能瞎改。  
就像 `ebcdcba` 这样，改了跟没改一样，他还是有回文串 `bcdcb`。改的话要这样 `abedcba`。

这样的话，我们发现一个规律，只要改动里面的长度为 2 或 3 回文串，就行了！

字符长度为 $2$ 的回文串：`aa` $\to$ `ab`。

字符长度为 $3$ 的回文串：`aba` $\to$ `cba`。

怎么实现？
枚举每一个字符，然后看后面一个或两个的字符且看这个字符是否解决，判断是否相同：

如果相同，那么修改次数加一，不相同的话，就不用理他。
代码如下
```cpp
for(int j=0;j<len-1;j++)
{ 
	if(s[j]==s[j+1]&&tmp[j]==1)//如果相邻两字符相同（回文）
	{  
		tmp[j+1]=0; //判第二个数修改（表示已解决） 
		ans++; //修改次数++ 
	}
	if(s[j]==s[j+2]&&tmp[j]==1)//如果中间隔一字符（如ABA、EYE）
	{  
		tmp[j+2]=0; //判最后的数修改
		ans++; //修改次数++ 
	}
}
```
这样就可以了（**记得每次初始化哦**）。
## AC代码




```cpp
#include<bits/stdc++.h> //不要抄题解哦 
using namespace std;
int n,ans,len;
char s[100010];
bool tmp[100010];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		memset(s,0,sizeof s); //重置字符串 
		scanf("%s",s);
		len=strlen(s); //获取该字符串的长度 
		memset(tmp,1,sizeof tmp); //重置判重数组 
		ans=0; //重置修改次数 
		for(int j=0;j<len-1;j++)
		{ 
			if(s[j]==s[j+1]&&tmp[j]==1)//如果相邻两字符相同（回文）
			{  
				tmp[j+1]=0; //判第二个数修改（表示已解决） 
				ans++; //修改次数++ 
			}
			if(s[j]==s[j+2]&&tmp[j]==1)//如果中间隔一字符（如ABA、EYE）
			{  
				tmp[j+2]=0; //判最后的数修改
				ans++; //修改次数++ 
			}
		}
		printf("%d\n",ans); 
	}
}
```

有什么疑问评论哦，谢谢。

求求给孩子点个**赞**吧！！！！

---

## 作者：Locklink (赞：7)

只要寻找长度为 $3$ 和长度为 $2$ 的回文串就行了，因为任何长度的回文串都将包括 $3$ 个字符的回文串或 $2$ 个字符的回文串。

比如：`acabcbaca` 包含 `bcb` ； `cabbac` 包含 `bb`。

所以，只需要把长度为  $3$ 和长度为 $2$ 的回文串破坏，整个回文串就将被破坏。

如何破坏长度为 $3$ 和长度为 $2$ 的回文串？

3个字符的：把两边中的一个改掉，比如 `bab` -> `bac` .

2个字符的：随便改掉一个，比如 `bb` -> `ba` .

我们还需要做标记，避免重复修改。

code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int T;
	cin>>T;
	while(T--){
		string s;
		cin>>s;
		int n=s.size();
		bool v[5000]={};
		int ans=0;
		for(int i=0;i<n-1;i++){
			if(s[i]==s[i+2]&&!v[i]){
				ans++;
				v[i+2]=true;
			}
			if(s[i]==s[i+1]&&!v[i]){
				ans++;
				v[i+1]=true;
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：HoshizoraZ (赞：5)

这题的关键就在于**如何用最小的操作次数摧毁所有的回文子串**。

我们可以先手玩几个例子（这里的例子都只有一个对称中心）：

- `abcdcba`

这时很容易得出，如果把其中一个 `c` 改为 `e`，那么这个字符串就不存在回文子串。

- `abccba`

这种情况也一样，把其中一个 `c` 改为 `e` 即可。

我们暂时就可以得到一个策略：
- 若回文串长度为奇数，修改对称中心位置左右的两个字符**之一**。
- 若回文串长度为偶数，修改离对称轴最近的两个字符**之一**。

这个策略容易证明是正确的，因为字符串变为 `abcdeba` 后，原字符串的任意一个回文区间都会因为 `d` 左右两个字符不同而被摧毁。偶数情况同理。

--------

不过这个策略仍不尽完善，我们仍需考虑修改的字符问题。

如 `bcbeb`，如果我们将第二个 `b` 改为 `c`，那么区间 $[2,3]$ 又构成了回文串，我们也白忙活了。

所以修改字符的时候，一定要选择一个不会生成回文串的字符才能修改。

看看我们曾经的结论：

- 若回文串长度为奇数，修改对称中心位置左右的两个字符**之一**。

这个修改的直接目的是使得**对称中心左右的两个字符不同**。

同样对于长度偶数的情况，修改的目的是使得**离对称轴最近的两个字符不同**。

因此我们在修改位置为 $i$ 的字符的时候，应该保证它修改后的字符与位置 $i\pm 1,i\pm 2$ 的字符都不相同，才可以修改下去（边界情况特殊考虑）。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
 
int t, n, ans;
char s[100010];
 
int main(){
 
	cin >> t;
	while(t--){
		scanf("%s", s + 1), n = strlen(s + 1);
		ans = 0;
		s[n + 1] = s[n + 2] = 'A';		// 处理边界
		for(int i = 2; i <= n; i++){
			if(s[i] == s[i - 1] && i > 1){	// 存在长度为偶数的字符串
				for(char j = 'a'; j <= 'z'; j++)
					if(j != s[i + 1] && j != s[i - 1] && j != s[i - 2] && j != s[i + 2]){
                     			 // 保证修改不会对以后操作造成负担
						s[i] = j;
						break;
					}
				ans++;
			}
			if(s[i] == s[i - 2] && i > 2){	// 存在长度为奇数的字符串
				for(char j = 'a'; j <= 'z'; j++)
					if(j != s[i] && j != s[i - 1] && j != s[i + 1] && j != s[i + 2]){
						s[i] = j;
						break;
					}
				ans++;
			}
		}
		cout << ans << endl;
	}
 
	return 0;
}
```

---

## 作者：Fa1thful (赞：3)

### 题意：
给你一个字符串，求最小修改多少次能使得字符串内不存在长度超过`1`的回文串。
### 分析：
结论：只需判断字符串中没有长度不超过`2`和`3`的回文串要多少次才能修改完成即可。

因为每个长度超过`3`的回文串，里面一定包含长度为`2`或`3`的回文串，比如 `abba` 一定包含长度为`2`的 `bb` 。所以只需判断`2`和`3`回文串的情况了。
### 代码：
```cpp
# include <bits/stdc++.h>
using namespace std;
bool v[100000];
int main()
{
	int T;
	cin >> T;
	while (T--)
	{
		memset(v, false, sizeof(v));     //v用来确定是否含有23的回文串 
		string s;
		cin >> s;
		int n = s.size();
		int ans = 0;
		for (int i = 0; i < n - 1; i++)
		{
			if (s[i] == s[i + 2] && !v[i])      //长度为3的情况 
			{
				ans++;                         //只需改变一次 
				v[i + 2] = true;
			}
			if (s[i] == s[i + 1] && !v[i])        //长度为2的情况 
			{
				ans++;
				v[i + 1] = true;
			}
		}
		cout << ans << endl;
	}
}
```


---

## 作者：77777_1031 (赞：2)

### [题目传送门](https://www.luogu.com.cn/problem/CF1466C)
[更好的阅读体验——戳这](https://www.luogu.com.cn/blog/TSYgoon/solution-cf1466c)

##  Part 1 题意分析

首先来看两张图：
![](https://cdn.luogu.com.cn/upload/image_hosting/zr5czkuv.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/0vn9vflw.png)
###### 更多的不再列举······
我们可以发现，这些字符串都是由长度为2或3的回文子字符串和普通子字符串组成的。

这就意味着，只要不存在长度为2或3的子回文串，字符串中将不存在长度大于 1 的回文子串。

所以，图一的字符串 ${\texttt{ababc}}$ 即可改为 ${\texttt{abebc}}$。

图二的字符串 ${\texttt{abaac}}$ 即可改为 ${\texttt{abaec}}$。

那我们就可以总结规律：
#### 假设 $a_i$ 与 $a_i-1$ 相等，或者 $a_i$ 与 $a_i-2$ 相等，就是长度为2或3的回文子串，就修改 $a_i$ 为整个字符串都没有出现过的字符，我们可以把这个字符称之为神奇字符。

代码如下：
```c
             if(a[i]==a[i-1])ans++;
             if(a[i]==a[i-2])ans++;
```


------------

##  Part 2 注意事项
#### ~~dalao自动略过···~~
另外，我们还要设置一个 $flag$ 数组，记录这个字符是否被修改过。

我自己测试了一下，不加 $flag$ 数组的结果 [$\mathrm{ WA}$](https://www.luogu.com.cn/record/59217004)。
#### 事实上，样例都是错的。
```c
2
2
0
1
1
11
0
```
最后提醒一句，保险起见，$flag$ 数组要开到 $10^5$ 哦。 
![](https://cdn.luogu.com.cn/upload/image_hosting/m0kclx83.png)

------------

##  Part 3 代码
```c
#include<bits/stdc++.h>
using namespace std;
int n;
int ans=0;//存储修改次数。
int flag[100001];//见注意事项。
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        memset(flag,0,sizeof(flag));//每次都要清零。
        ans=0;//同上
        string a;
        cin>>a;
        int l=a.size();//.size() 为求字符串长度的函数。
        for(int i=0;i<l;i++){
            if(a[i]==a[i-1]&&flag[i-1]==0){ans++;flag[i]=1;}//如果没有修改过 且满足回文子串的条件，修改次数增加，标记。
            if(a[i]==a[i-2]&&flag[i-2]==0){ans++;flag[i]=1;}//同上。
        }
        cout<<ans<<endl;
    }
    return 0;//完结撒花～～
}
```
[AC](https://www.luogu.com.cn/record/59193697)

##### ~~我的第一篇题解，纪念一下。~~

[我的博客](https://tsygoon.blog.luogu.org)

最后的话：看都看了，不点个赞再走嘛？谢谢呐。

---

## 作者：opzc35 (赞：1)

## 题意

给你一个字符串，让你修改一些位置，使得这个字符串中不包含回文子串（一个字母的那种不算）

## 分析

这道题该怎么做呢？让我们思考一下。

先来考虑发现长度为 2 的回文子串。我们只需要改掉其中的一个字符就可以捣毁这个回文子串。

其次考虑长度为 3 的回文子串。如果发现一个字符和后面的第二个字符相等，那么就是一个回文子串，我们也只需要修改两侧的字符的其中一个就可以捣毁这个回文串。

如果更多的呢？我们已经捣毁了长度为 2，长度为 3 的回文子串，那么更长的回文子串中肯定包含这些子串，这些子串已经不是回文子串了，更长的回文子串肯定不能形成。

总结：我们只要找到长度为 2 和长度为 3 的回文子串，找到其中的一个字符改掉就可以了。

具体实现中，最好做一个标记，标记哪个字符有没有被改过更好。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
string s;
int main(){
	cin>>t;
	while(t--){
		cin>>s;
		int ans=0;
		bool vis[100005]={0};
		for(int j=0;j<s.size()-1;j++){
			if(s[j]==s[j+1]&&!vis[j]){
				ans++;
				vis[j+1]=1;
			}
			if(s[j]==s[j+2]&&!vis[j]){
				ans++;
				vis[j+2]=1;
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

## TIPS

记得清空上一次保留的数据（如果你是在循环中定义的变量，也可以不用，但是函数中定义的数组的初始值不好确定）

---

## 作者：_xEr_ (赞：0)

这题的关键就是如何去掉最少的字符串爆破最多的回文串。

众所周知，回文串有两种，一种中心只有一个字母，如：```abcba```。  
另一种有中心两个字母，如：```cbaabc```。

面对第一种，显而易见改掉 ```b``` 即可，面对第二种，改掉 ```a``` 即可。易得，我们只需要改掉**回文串的中心**就可以了。但由于第一种情况改掉中间没有什么用，要改掉他的两边。所以实际上是改掉长度为 $2$ 和 $3$ 的回文串，即第一种的两边和第二种的中间。

具体代码见下：
```cpp
#include<iostream>
#include<cstring>
#define clean() memset(f,0,sizeof f)
using namespace std;
int q;
string a;
bool f[100009];
int main(){
	cin>>q;
	while(q--){
		int ans=0;
		cin>>a; clean();
		for(int i=0;i<a.size()-1;i++){
			if(a[i]==a[i+1]&&!f[i]){
				f[i+1]=1; ans++;
			}
			if(a[i]==a[i+2]&&!f[i]){
				f[i+2]=1; ans++;
			}
		}
		cout<<ans<<endl;
	}
}
```

---

## 作者：baoziwu2 (赞：0)

看到最小异或值可以想到 `trie` 树，但是删除操作实现过于困难，正难则反，考虑求最大保留数。

设 $f_x$ 为在 `trie` 树 上以 $x$ 为根的合法子树可以保留的最大数量，转移方程如下。

$ f_x = \begin{cases}
1 & x\in leaf \\
f_{subtree} & \text{x has only one subtree}\\
\max\limits_{y \in subtree(x)}\{f_y\} + 1 & \text{otherwise}
\end{cases} $

当 $x$ 只有一颗子树时，答案显然为 $f_{subtree}$，当 $x$ 兼具左右子树时，保留一棵较大的子树，将另一棵子树的节点删到只剩一个，因为保留的子树答案是合法的，而另一颗子树上会且仅会产生一条边，所以新的答案也是合法的，即满足 $x$ 子树内只存在一对满足题目要求的 $(i,j)$。

```C++
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int const N = 3e7 + 5;

inline int read() {
	int res = 0, f = 1; char c = getchar();
	while(!isdigit(c)) {
		if(c == '-') f = -1;
		c = getchar();
	}
	while(isdigit(c)) {
		res = res * 10 + c - '0';
		c = getchar();
	}
	return res * f;
}

class Tire {
	int ch[N][2], tot;
public:
	inline void insert(int const &val) {
		int p = 0;
		for(int i = 30; ~i; -- i) {
			bool x = (val >> i) & 1;
			if(!ch[p][x]) ch[p][x] = ++ tot;
			p = ch[p][x];
		}
	}
	
	int dfs(int x) {
		if(!ch[x][0] and !ch[x][1]) return 1;
		if(!ch[x][0]) return dfs(ch[x][1]);
		if(!ch[x][1]) return dfs(ch[x][0]);
		return max(dfs(ch[x][0]), dfs(ch[x][1])) + 1;
	}
}t;

int main() {
	int n = read();
	
	for(int i = 1; i <= n; ++ i)
		t.insert(read());
	
	printf("%d\n", n - t.dfs(0));
	return 0;
}
```

---

## 作者：初星逝者 (赞：0)

### 题意

给你一个字符串 $s$，问最少要修改多少次，才可以使得串 $s$ 中不存在长度大于 1 的回文子串。

### 前传

什么是回文串呢？

举个例子：`abcdcba` 是一个回文串，而 `cdc` 是其中之一的回文子串，以此类推，还有 `bcdcb` , `abcdcba` 等。

很明显，都包含 `cdc` 这个字符串，但是修改 `d` 无意义，所以对于这个字符串，我们只需要更改 `c` 的为其他的字符就好了，可得到 `abzdcba` 或 `abcdzba`，显然就不是回文串了。

再举个例子，对于 `cbaabc` 这个字符串，我们只需要修改 `a` 为其他的字符就可以了。

#### 总结：

对于一个字符串，如果出现相邻两个字符相同或于后面于后面第二个字符相同，ans++，将后面的字符标记，以防重复标记，最后输出 ans。


### AC code：

```cpp
#include <bits/stdc++.h>
using namespace std;

int t;
string s;

int main(){
	cin >> t;
	while(t--){
		cin >> s;
		int ans=0;
		for(int i=0;i<s.length()-1;i++){
			if(s[i]==s[i+1]&&s[i]!='0')s[i+1]='0',ans++;
			if(s[i]==s[i+2]&&s[i]!='0')s[i+2]='0',ans++;
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

~~应该算的上是最短的了吧。~~

---

## 作者：OranJun (赞：0)

考虑回文串最小的单位长度是3或2，那么只要破坏了长度为2或3的串，就不可能会有更大的回文串了。所以就从前往后扫，看是否出现回文，如果出现并且之前的字符没被修改，那么这个字符就一定要修改，可以证明是最优的。

```cpp
/*Code by Codercjh*/
#include<bits/stdc++.h>
#define fr(i,a,b) for(int i=(a);i<=(b);++i)
#define rf(i,a,b) for(int i=(a);i>=(b);--i)
#define min(a,b) (a<b?a:b)
#define max(a,b) (a>b?a:b)
using namespace std;
typedef long long ll;
template<typename T>
inline void read(T &x){
	char c=getchar();T fh=0;bool f=false;
	while(!isdigit(c))f|=(c=='-'),c=getchar();
	while(isdigit(c))fh=(fh<<1)+(fh<<3)+(c^48),c=getchar();
	x=f?-fh:fh;
	return;
}
const int N=1e5+5;
char s[N];
int mod[N];
int main(){
	int T,n;
	read(T);
	while(T--){
		int ans=0;
		cin>>s+1;
		int n=strlen(s+1);
		fr(i,1,n)mod[i]=0;
		fr(i,2,n){
			if(s[i]==s[i-1]&&!mod[i-1])mod[i]=1;//记录修改点
			if(i>2&&s[i]==s[i-2]&&!mod[i-2])mod[i]=1;
			ans+=mod[i];
		}
		cout<<ans<<endl;
	}
	return 0;
}


---

## 作者：Coros_Trusds (赞：0)

[更好的阅读体验](https://www.cnblogs.com/Coros-Trusds/p/15374473.html)

# 题目大意

每组数据给出一个由小写字母组成的字符串 $\rm str$。

每次可以将串 $\rm str$ 中任意一个位置的字符修改为另一个小写字母。

问最少要修改多少次，才可以使得串 $\rm str$ 中 **不存在长度大于 $1$** 的回文子串。

# 题目分析

一个回文串的长度只会是奇数或偶数，那么回文串的类型也分两种（名字自己起的）：

* 奇串

* 偶串

## 奇串

这种情况中，回文串的中心地带一定是一个长度为 $3$ 的回文奇串。

那么把这个回文奇串随意破坏左右端的任一个即可；

## 偶串

这种情况中，回文串的中心地带一定是一个长度为 $2$ 的回文偶串。

那么把这个回文偶串随意破坏左右任一个即可。

那么我们如何处理 『破坏』 操作呢？可以手动更改，但更方便的方式是打个标记。

# 代码

```cpp
const int ma=100005;

bool vis[ma];
 
int main(void)
{
	std::ios::sync_with_stdio(false);
	
	int T;
	
	cin>>T;
	
	while(T--)
	{
		string str;
		
		cin>>str;
		
		int n=str.size();
		
		memset(vis,false,sizeof(vis));
		
		int ans=0;
		
		for(register int i=0;i<n-1;i++)
		{
			if(str[i]==str[i+2] && vis[i]==false)//3 - 情况 
			{
				vis[i+2]=true;
				
				ans++;
			}
			
			if(str[i]==str[i+1] && vis[i]==false)//2 - 情况
			{
				vis[i+1]=true;
				
				ans++;
			} 
		}
		
		printf("%d\n",ans); 
	}
	
	return 0;
}
```

---

