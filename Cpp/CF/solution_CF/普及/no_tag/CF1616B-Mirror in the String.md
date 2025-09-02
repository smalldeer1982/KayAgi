# Mirror in the String

## 题目描述

You have a string $ s_1 s_2 \ldots s_n $ and you stand on the left of the string looking right. You want to choose an index $ k $ ( $ 1 \le k \le n $ ) and place a mirror after the $ k $ -th letter, so that what you see is $ s_1 s_2 \ldots s_k s_k s_{k - 1} \ldots s_1 $ . What is the lexicographically smallest string you can see?

A string $ a $ is lexicographically smaller than a string $ b $ if and only if one of the following holds:

- $ a $ is a prefix of $ b $ , but $ a \ne b $ ;
- in the first position where $ a $ and $ b $ differ, the string $ a $ has a letter that appears earlier in the alphabet than the corresponding letter in $ b $ .

## 说明/提示

In the first test case choose $ k = 1 $ to obtain "cc".

In the second test case choose $ k = 3 $ to obtain "cbaabc".

In the third test case choose $ k = 1 $ to obtain "aa".

In the fourth test case choose $ k = 1 $ to obtain "bb".

## 样例 #1

### 输入

```
4
10
codeforces
9
cbacbacba
3
aaa
4
bbaa```

### 输出

```
cc
cbaabc
aa
bb```

# 题解

## 作者：I_m_FW (赞：2)

观察样例，发现答案在镜面前都是非严格单调递减，为什么呢？ 

若当前字符不递减，且留了下来，那么它会代替上一个字符的镜像，例如：

``badaaaa`` 去掉 ``d`` 以后的字符并且镜面一下： ``baab``

``badaaaa`` 不去掉 ``d`` 以后的字符并且镜面一下： ``badaaaaaaaabab``

后面有再小的字典序都无济于事，因为第三位十分的大直接可以不考虑了。 

那么为什么非严格呢？

举个例子： 

``pyyyz`` 若严格递减：结果为 ``pyyp``
 
``pyyyz`` 若非严格递减：结果为 ``pyyyyyyp``
            
这样做的目的是让 $p$ 在镜像以后排在后面一点。 

但注意： ``aaaa`` 结果为 ``aa`` 而不需要全部镜像，因为它的全部字符都是一样的，要特判。 

代码： 

```
#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;cin>>t;
	while(t--){
		int n,pd=0;string s;cin>>n>>s;char last=s[0];
		string v,ans;v.push_back(last);
		for(int i=1;i<s.size();i++){
			if(s[i]!=s[0])pd=1;
			if(last>s[i]||(last==s[i]&&pd))v.push_back(s[i]),last=s[i];
			else break;
		}
		ans+=v;
		reverse(v.begin(),v.end());
		ans+=v;
		cout<<ans<<endl;
	}
}
```

---

## 作者：ArrogHie (赞：2)

## 题意

给定一个字符串 $s$，求出一个字典序最小的字符串 $t$ 满足以下条件：

- $t$ 是一个回文串且长度为偶数
- $t$ 的前半段为 $s$ 的前缀
- $t$ 的字典序小于 $s$

## 题解

结论：若 $s$ 的前两位相同则 $t$ 为 $s$ 的前两位。否则 $t$ 的前半段截止为第一次出现 $s_i<s_{i+1}$ 的 $i$ 处，即 $t$ 的构成为 $s_1s_2s_3\cdots s_is_i \cdots s_3s_2s_1$。

证明：

对于一个 $s_{i+1}\leq s_i$ 的 $i$ 处，选择截止至 $i+1$ 一定比 $i$ 更优，截止至 $i$ 处和 $i+1$ 处的字符串如下：

$s_1s_2s_3\cdots s_{i-1}s_is_is_{i-1} \cdots s_3s_2s_1$

$s_1s_2s_3\cdots s_{i-1}s_is_{i+1}s_{i+1}s_i \cdots s_3s_2s_1$

可以发现在第 $i+1$ 位上两个字符串第一次出现不同，因为 $s_{i+1}\leq s_i$，故下面个字符串更小。

---

## 作者：0xFF (赞：2)

#### 题目大意


------------
给定一个字符串 $s$，找出字典序最小的字符串 $t$ 满足 $t$ 是一个长度为偶数的回文串且其前一半是 $s$ 的前缀。

#### 题目思路


------------
观察样例不难看出要想使得 $t$ 的字典序最小一定要满足 $t$ 的前半部分即 $s$ 的前缀之一必定是一个未严格的单调递增区间。

考虑两种情况，如果 $t$ 中的元素都各不相同，那么只需要从左往右遍历，如果下一位比当前的这一位字典序小那么序列一定包含下一位。

再考虑如果 $t$ 中有重复元素的情况。

如果一个字符串是另一个字符串的前缀且两串不同时，前者较小。

例如样例 $3$ 的情况： ```aaa``` 中 ```a``` 是 ```aa``` 的前缀所以选择 ```a```，更进一步说，如果前两位相同，那么答案一定是第一位。

#### 代码实现


------------
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
using namespace std;
const int N = 200010;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	for(;!isdigit(ch);ch=getchar()) if(ch=='-') f=-1;
	for(; isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+ch-'0';
	return x*f;
}

char s[N];

int main(){
	int T = read();
	while(T--){
		int n = read();
		scanf("%s",s+1);
		bool flag = 0;
		int i;
		for(i=1;i<n;i++){
			if(s[i] > s[i+1]) flag=1;
			else if(s[i] < s[i+1] || (s[i] == s[i+1] && flag == 1)) break;
		}
		s[i+1] = 0;
		printf("%s",s+1);
		for(;i>=1;i--){
			putchar(s[i]);
		}
		printf("\n");
	}
	return 0;
}
```


---

## 作者：Chenyichen0420 (赞：1)

# 题目大意

给你 $t$ 个长度为 $n$ 的原字符串 $S$，现在希望你将这个字符串变为形如 $S_1S_2S_3\dots S_kS_kS_{k-1}S_{k-2}\dots S_1(1\leq k\leq n)$ 的字符串，请问这些字符串中字典序最靠前的是哪一个？

注：最中间的那个字符也有两遍，不要被骗了。

# 思路分析

这时候我们要仔细分析一下字典序的比较方式：

- 从头向后进行对比，也就是说前面的影响力更大，同等情况下才会参考后面的。

- 比对到某一方后面没有字符时再比对长度。

这时候这道题的解法其实已经基本明确了：

第一个字符默认添加到答案字符串的末尾。

从第二个字符开始向答案字符串末尾比对，如果这个字符大于原字符串末尾字符或者该字符与已选中字符的第一个字符相同，那么这种情况一定没有已选中的字符串更优，抛弃这个字符以及其后面的，将已选中的字符作为答案处理后输出。否则就将这个字符加入到答案字符串的末尾。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n; string s1,ans,tmp;
int main() {
    ios::sync_with_stdio(false);
    cin>>t;
    while(t--){
        cin>>n>>s1; ans=s1[0];
        for(register int i=1;i<n;++i)
            if(s1[i]>s1[i-1]||s1[i]==ans[0]) break;
            else ans+=s1[i];
        tmp=ans; reverse(ans.begin(),ans.end());
        tmp+=ans; cout<<tmp<<endl;
    }
}
```

---

## 作者：xiaozeyu (赞：1)

[CF1616B Mirror in the String](https://www.luogu.com.cn/problem/CF1616B)

一道水题，没看到有人上代码就自己写了写。

可以在一个字符的后面放一面镜子反着复制一遍前面的内容，代替掉镜子右边的字符，要想办法使得最终的字符串字典序最小。

从字典序的比较出发。

先考虑每个字符都不同的情况。比较时从左往右，当有一位更小时，就是字典序更小，比如 $\texttt {cb}$ 的字典序大于 $\texttt {ca}$。又比如 $\texttt{cbb}$ 大于 $\texttt{cba}$。

那我们再看样例，可以发现 $\texttt{cbbc}$ 的字典序 大于 $\texttt{cbaabc}$，可以发现，当前一半递减时一定更优，出现升高一定不是最优。

考虑完不同字符，再同字符。

当一个字符串是另一个的前缀且两串不同时，前者小。

就是说 $\texttt{bb}$ 比 $\texttt{bbbb}$ 以及 $\texttt{bbaabb}$ 等都小。

也就是说开头两个相同时，在第一个后面放镜子最优。

代码如下。

---

```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(int i=a;i<=b;i++)
#define Rep(i,a,b) for(int i=a;i>=b;i--)
using namespace std;
int read()
{
	char c=getchar();int x=0;bool f=0;
	while(!isdigit(c))f^=!(c^45),c=getchar();
	while(isdigit(c))x=(x<<1)+(x<<3)+(c^48),c=getchar();
	if(f)x=-x;return x;
}
const int maxn=200010;
int T,i,n,f;
char s[maxn];
int main()
{
	T=read();
	while(T--)
	{
		scanf("%d%s",&n,s+1);
		f=0;
		int i;
		for(i=1;i<n;i++)
			if(s[i]>s[i+1]) f=1;
			else if(s[i]<s[i+1]||(s[i]==s[i+1]&&!f))break;
		s[i+1]=0;
		printf("%s",s+1);
		for(;i>=1;i--) putchar(s[i]);
		puts("");
	}
}
```


---

## 作者：LCat90 (赞：1)

要使得得到的字符串字典序尽可能的小，所以，我们要让**越靠前的字母字典序尽可能的小**。因此，答案字符串肯定是一个字母 **字典序逐渐减小（或相等）** 的一个字符串。这样，我们只需要找到字典序不会逐渐减小的那个点，那个点就是放镜子的位置。

但还要注意特判：**当当前字符在开头且后面的字符等于当前字符，则将镜子放在这个字符后面。** 考试的时候就因为这个丢了60分。

例如：有这样一组样例：``bba``

有三种方案： ``bb``、``bbbb``、``bbaabb``

显然 ``bb`` 是最优解，即 ``b`` 在开头且与下一个字符 ``b`` 相等的情况。

另一组样例： ``baa`` 

同样有三种方案：``bb``、``baab``、``baaaab``

显然 ``baaaab`` 是最优解，即字典序逐渐减小（或相等）。

```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int Maxn = 1e5 + 5;
int t, n;
char c[Maxn];
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		scanf("%s", c + 1);
		bool flag = 0;
		for(int i = 1;i <= n - 1; ++i) {
			if(c[i] < c[i + 1] or (i == 1 and c[i] == c[i + 1])) {
				for(int j = 1;j <= i; ++j) putchar(c[j]);
				for(int j = i;j >= 1; --j) putchar(c[j]);
				flag = 1;
				break;
			}
		}
		if(!flag) {
			for(int i = 1;i <= n; ++i) putchar(c[i]);
			for(int i = n;i >= 1; --i) putchar(c[i]);	
		}
		putchar('\n');
	}
	return 0;
}
```


---

## 作者：cqbzhzf (赞：0)

[Luogu原题链接](https://www.luogu.com.cn/problem/CF1616B)
### 思路
这里用 $a_i$ 记录 $s_i$ 的字典序，题目求字典序最小，所以直接遍历一遍字符串 $s$，直到 $a_i > a_{i-1}$ 为止，于是打出了第一份代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
string s;
int t,a[N],id,n;
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--)
	{
		cin>>n>>s;
		id=n;
		memset(a,0,sizeof(a));
		for(int i=0;i<n;i++)
			a[i]=s[i]-'a'+1;//用a[i]记录s[i]的字典序
		for(int i=1;i<n;i++)
		{
			if(a[i]>a[i-1])
			{
				id=i;
				break;
			}
		}
		for(int i=0;i<id;i++)
			cout<<s[i];
		for(int i=id-1;i>=0;i--)
			cout<<s[i];	//输出回文串
		cout<<"\n";
	}
	return 0;
}
/*
hack数据：1 4 bbbb
hack数据答案：bb
代码输出答案：bbbbbbbb
*/
```
结果不出意料的错了。仔细思考一番，我们可以发现并不是所有的情况都可以取 $a_i=a_{i-1}$ 的答案，如代码注释里的 hack 数据，无论怎么取答案，都是由字符 $b$ 组成的字符串，也就是说在这种情况下，长度越短的字符串字典序越小。

由此推导，只有**当前面所取答案的字符串不是全部相等**的时候，当前位才能取 $a_i=a_{i-1}$ 的答案，只需要判断 $a_0$ 是否大于 $a_1$ 即可。
### 代码
```cpp
/*
AC 2024.7.17
*/
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
string s;
int t,n,a[N];
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--)
	{
		memset(a,0,sizeof(a));
		cin>>n>>s;
		int id=n;
		if(n==1)
		{
			cout<<s<<s<<"\n";
			continue;
		}//特判只有一个字母的情况，否则wa
		for(int i=0;i<s.size();i++)
			a[i]=s[i]-'a'+1;//用a[i]存储s[i]的字典序
		for(int i=1;i<n;i++)
		{
			int t1=a[i-1];
			int t2=a[i];
			if(t2>t1)
			{
				id=i;
				break;	
			}
			if(t2==t1&&a[0]==a[1])
			{
				id=i;
				break;
			}
		}
		for(int i=0;i<id;i++)
			cout<<s[i];
		for(int i=id-1;i>=0;i--)
			cout<<s[i];//输出答案
		cout<<"\n";
	}
	return 0;
}
```

---

## 作者：cqbzrjx (赞：0)

[原题传送门](http://codeforces.com/problemset/problem/1616/B)

# 题意

有一个字符串 $S_1,S_2,\dots,S_{n-1},S_n$ 和一面镜子，现在，你站在字符串的左边朝右看。你希望选择一个数字 $k (1 \le k \le n)$ 并在第 $k$ 个字母后放下这面镜子，这样你就可以得到一个对称的镜像字符串 $S_1,S_2, \dots ,S_k,S_k,S_{k-1},\dots,S_2,S_1$。现在，请你计算，你能得到的字典序最小的镜像字符串是多少？



# 分析

这道题其实算是一个**贪心和模拟**了。

存储一个**队列**，得到一个镜像的**数组**。仔细想一下，当我们的字符串的当前位的字典序**小于**下一位时，镜像翻转之后才能得到较小的字符串。

而对于字典序，我为大家简单讲述一下何为比较字典序。

- 从第一位一直往后比较每个字符的大小，字符小的字符串则字典序较小。如 ```codeforces``` 和 ```children```，则可知第二个字符串字典序较小。
- 在比较时，如果当前位为空，则说为空的字符串字典序较小。如 `a` 和 ```aaaaa```，则第一个字符串字典序较小。

# AC code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 200005;
int t,n,sum;//t,n见题目,sum为当前镜像字符串的长度
char c[maxn];//输入的字符串
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin>>t;//输入
	while(t--)//多组数据测试
	{
		sum = 0;//多测不清空
		queue<char> q;//见分析
		char c2[maxn];//存储镜像字符串
		cin>>n>>c;//输入
		if(c[0] <= c[1])//当第一位小于第二位的字典序时，需特判
		{
			cout<<c[0]<<c[0]<<endl;
			continue;
		}
		q.push(c[0]);//把第一位放置在队列里
		sum++;//总数+1
		for(int i = 0;i < n;i++)
		{
			if(c[i] >= c[i + 1] && c[i + 1] >= 'a' && c[i + 1] <= 'z')//遍历当前位的字典序与下一位，如果小于，直接结束得到最小镜像字符串
			{
				q.push(c[i + 1]);//把下一位放置在队列里
				sum++;//同上
			}
			else
			{
				break;//结束得到最小镜像字符串
			}
		}
		for(int i = 0;i < sum;i++)//先顺着输出
		{
			c2[i] = q.front();//赋值
			q.pop();//队列的值出队，得到清空
			cout<<c2[i];
		}
		for(int i = sum - 1;i >= 0;i--)//再倒着输出
		{
			cout<<c2[i];
		}
		cout<<endl;//记得换行
	}
	return 0;//完结，撒花
}
```

---

## 作者：L_shadow (赞：0)

## 思路：
这题主打一个**贪心**和**枚举**。

从 $i=0$ 开始，一直往后扫描。如果后面那个字符大于前面那个字符，就结束。为啥呢？因为本来在 $i+1$ 位置的是镜像后的 $i$ ，如果 $ch_{i+1}>ch_i$ ，那么加上 $ch_{i+1}$ 后的镜像字符串，无论后面的字符有多小，它的字典序是一定比不加 $ch_{i+1}$ 所得的镜像字符串小的。

### 注意：
输出的时候切忌一边处理一边输出，因为有一些字符串不能进入循环，因此无法输出。

正确的输出方法是处理完后一起输出，这样，无论字符串是否进入循环，都能得到相应的输出。最后再倒序输出。

## code：
```cpp
#include<bits/stdc++.h>
using namespace std;
char st[200005];
int main() {
	int T;
	cin>>T;
	while(T--) {
		int n;
		scanf("%d%s",&n,st+1);
		int i,s=0;
		for(i=1; i<n; i++) {
			if(st[i]>st[i+1]){
				s=1;
			}
			else if(st[i]<st[i+1]||(st[i]==st[i+1]&&!s)) {
				break;
			}
		}
		st[i+1]=0;
		printf("%s",st+1);//处理完后一起输出。
		for(;i>=1; i--) {//倒序输出。
			cout<<st[i];
		}
		cout<<endl;
	}
}
```


---

## 作者：liuzhongrui (赞：0)

## 思路

比较字符串 $s_1 s_2 … s_k s_{k-1} … s_2 s_1$ 和 $s_1 s_2 … s_{k+1} s_{k+1} s_k … s_1$。

它们具有一个长的共同前缀 $s_1 s_2 … s_k$。并且要比较的下一对字符是 $s_{k+1}$ 和 $s_k$。

因此，除非 $s_1 s_2 … s_k s_{k-1} … s_1$ 是 $s_1 s_2 … s_{k+1} s_{k+1} s_k … s_1$ 的前缀，否则如果 $s_{k+1} \le s_k$，则选择 $k+1$ 是最优的。

进一步推进这个思想，可以发现答案是 $s_1 s_1$ 或者是 $s_1 s_2 … s_k s_{k-1} … s_1$，其中 $k$ 是最大的满足 $s_k \le s_{k-1}$ 的值，这样整体思路就出来了。

## Code

```cpp
#include<bits/stdc++.h>
int T,i,n,f;
char s[200001];
int main() {
	scanf("%d",&T);
	while(T--) {
		scanf("%d%s",&n,s+1);
		f=0;
		for(i=1; i<n; i++) {
			if(s[i]>s[i+1]){
				f=1;
			}else if(s[i]<s[i+1]||(s[i]==s[i+1]&&!f)) {
				break;
			}
		}
		s[i+1]=0;
		printf("%s",s+1);
		for(; i>=1; i--) {
			putchar(s[i]);
		}
		puts("");
	}
	return 0;
}
```


---

## 作者：qwq___qaq (赞：0)

### Update
2022.5.5 更新了代码在一堆相同字符下会 T 的问题。
***
首先，我们要知道，对于一个字符串 $s_i$，它的第 $j$ 位 $s_{i,j}$，如果小于 $s_{i,j+1}$，那么肯定是放在 $j$ 的，因为 $s_{i,j}s_{i,j}<s_{i,j}s_{i,j+1}$。

此外，如果 $s_{i,j}=s_{i,j-1}$，如果此时在首位，那么 $s_{i,j}s_{i,j}<s_{i,j}s_{i,j+1}s_{i,j+1}s_{i,j}$，所以不取；否则 $s_{i,j-2}>s_{i,j}$，所以 $s_{i,j-2}s_{i,j-1}s_{i,j}s_{i,j}s_{i,j-1}s_{i,j-2}<s_{i,j-2}s_{i,j-1}s_{i,j-1}s_{i,j-2}$，此时要取。

综上，当 $s_{i,j}<s_{i,j-1}$ 或 $s_{i,j}=s_{i,j-1}$ 且 $j\ne1$ 时， $j$ 在镜中，时间复杂度 $O(n)$。
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n;
string s;
int main(){
    cin>>T;
	while(T--){
	    cin>>n>>s;
		int k=0;
		for(int i=1;i<n;++i){
			if(s[i]<s[i-1]||(s[i]==s[i-1]&&i!=1))
				k=i;
			else
			    break;
		}
		for(int i=0;i<=k;++i)
			putchar(s[i]);
		for(int i=k;i>=0;--i)
			putchar(s[i]);
		puts("");
	} 
	return 0;
}
```

---

