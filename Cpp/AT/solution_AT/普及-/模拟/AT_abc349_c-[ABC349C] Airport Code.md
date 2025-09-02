# [ABC349C] Airport Code

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc349/tasks/abc349_c

英大文字からなる長さ $ 3 $ の文字列 $ T $ が、英小文字からなる文字列 $ S $ の **空港コード** であるとは、 $ T $ が $ S $ から次のいずれかの方法により得られることとします。

- $ S $ の長さ $ 3 $ の（連続とは限らない）部分列をとり、それを英大文字に変換したものを $ T $ とする
- $ S $ の長さ $ 2 $ の（連続とは限らない）部分列をとり、それを英大文字に変換したものの末尾に `X` を追加したものを $ T $ とする
 
文字列 $ S $, $ T $ が与えられるので、 $ T $ が $ S $ の空港コードであるか判定してください。

## 说明/提示

### 制約

- $ S $ は英小文字からなる長さ $ 3 $ 以上 $ 10^5 $ 以下の文字列
- $ T $ は英大文字からなる長さ $ 3 $ の文字列
 
### Sample Explanation 1

`narita` の部分列 `nrt` を英大文字に変換した文字列 `NRT` は、 `narita` の空港コードです。

### Sample Explanation 2

`losangeles` の部分列 `la` を英大文字に変換した文字列 `LA` の末尾に `X` を追加したもの `LAX` は、 `losangeles` の空港コードです。

## 样例 #1

### 输入

```
narita
NRT```

### 输出

```
Yes```

## 样例 #2

### 输入

```
losangeles
LAX```

### 输出

```
Yes```

## 样例 #3

### 输入

```
snuke
RNG```

### 输出

```
No```

# 题解

## 作者：MinimumSpanningTree (赞：5)

[原题链接](https://www.luogu.com.cn/problem/AT_abc349_c)

一道简单的模拟题。

$T$ 分为两种情况，一种是完全属于 $S$ 的子串，另一种是前 $2$ 个字符是 $S$ 的子串，第 $3$ 个字符是 `X`。

于是我们可以分这两种情况判断。为了方便判断子串我们先把 $S$ 全部转为大写字母，再遍历判断 $T$ 是否是 $S$ 的子串。如果 $T$ 的第 $3$ 个字符是 `X`，就可以再判断一遍 $T $ 的前 $2$ 个字符是否是 $S$ 的子串。

时间复杂度 $O(n)$，可以轻松通过本题。

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
string s,t;
int n,p=0;
bool flag;
int main()
{
	cin>>s>>t;
	n=s.size();
	for(int i=0;i<n;i++) s[i]+='A'-'a';
	if(t[2]=='X')
	{
		for(int i=0;i<n;i++)
		{
			if(p<=1&&s[i]==t[p]) p++;
		}
		if(p>1) flag=true;
	}
	p=0;
	for(int i=0;i<n;i++)
	{
		if(p<=2&&s[i]==t[p]) p++;
	}
	if(p>2) flag=true;
	flag?printf("Yes"):printf("No");
	return 0;
} 
```

---

## 作者：XXh0919 (赞：4)

### 题目翻译

一个字符串 $S$ 的机场代码 $T$ 可以用以下方式导出：
- 从 $S$ 中取一个长度为 $3$ 的子序列(不一定是连续的)并将其转换为大写字母以形成 $T$。

- 从 $S$ 中取出长度为 $2$ 的子序列(不一定是连续的)，将其转换为大写字母，并将 $\texttt{X}$ 附加到末尾以形成 $T$。

给定字符串 $S$ 和 $T$，请确定 $T$ 是否是 $S$ 的机场代码。

### 解法

很简单的一道题。

我们只需要枚举 $S$ 的每一个字符 $c$，判断 $c$ 转换成大写字符后是否是当前的 $T$ 中的字符，若是就将当前判断的串 $T_1$ 的长度加 $1$，否则就继续判断，最后看这个长度是不是 $T$ 的长度，若是就输出 $\texttt{Yes}$，否则输出 $\texttt{No}$。

注意：要特判 $T$ 末尾是 $\texttt{X}$ 的情况。

```cpp
#include<bits/stdc++.h>
#define int long long
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define per(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int N=4e6+15;

string s,t;
bool flag;

bool check(string s,string t){
	int i=0;
	for(auto e:s){
		if(i<t.size()&&e+'A'-'a'==t[i]){
			++i;	
		}
	}	
	return i==t.size();
}

void solve(){
	cin>>s>>t;
	if(check(s,t))flag=1;
	if(t[2]=='X')
		t.pop_back(),flag|=check(s,t);
	if(flag)puts("Yes");
	else puts("No");
}

signed main(){
	ios::sync_with_stdio(0);
	int T=1;
//	cin>>T;
    while(T--)solve();
	return 0;
}
```

---

## 作者：liaoxingrui (赞：3)

## Content

一个长度为 $3$ 的，由大写英文字母组成的字符串 $T$，满足以下两种条件的一种，则输出 `Yes`，否则输出 `No`。

1. 将字符串 $T$ 转成小写英文字母后，字符串 $T$ 为 $S$ 的子序列；

1. 将字符串 $T$ 转成小写英文字母后，若字符串 $T$ 的最后一个字符为 x，则只需 $T$ 的其他两个字符所构成的子串为 $S$ 的子序列即可。

## Solution

首先根据题目描述，将字符串 $T$ 转成小写英文字母。可以通过 ASCII 码来转化，以下是一张 ASCII 码的对照图：

![ASCII](https://cdn.luogu.com.cn/upload/image_hosting/yt5tf5ij.png)

其中可以发现大写字母 A 的 ASCII 码为 $65$，小写字母 a 的  ASCII 码为 $97$，因此只需要将大写字母的 ASCII 码加上 $32$ 即可转化成小写字母，~~虽然可以用系统函数~~来做。

变成小写后，判断 $T$ 的最后一个字符是否为 x，若是，则只需要判断前面两个字符所构成的字符串是否为 $S$ 的子序列，否则全部判断。

然后要判断一个字符串 $A$ 是否为另一个字符串 $B$ 的子序列。注意**子序列可能是不连续的**，所以对于字符串 $A$，定义一个下标 $t$ 为 $1$，然后遍历 $B$ 的每一个字符，若字符 $b_i$ 与字符 $A_t$ 相同，则将下标加 $1$；如果下标已经超过 $A$ 的长度，则说明 $A$ 中的所有字符都在 $B$ 中顺次出现，故字符串 $A$ 为字符串 $B$ 的子序列。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int tot,len;
bool bj;
string s,t;
int main(){
	cin>>s>>t;
	len=s.size();
	//先算出s的长度方便计算
	for(int i=0;i<3;i++)
		t[i]+=32;
	//将大写字母转成小写字母
	if(t[2]=='x')
		bj=1;
	//如果最后一个字符是x，就不判断这个字符
	for(int i=0;i<len;i++){
		if(s[i]==t[tot])
			tot++;
		if(tot==3-bj){
		//tot超过t的下标时，结束并输出Yes，注意字符串的下标从0开始
			cout<<"Yes";
			return 0;
		}
	}
	cout<<"No";
	//如果没结束，就输出No
	return 0;
}
```

---

## 作者：I_Love_DS (赞：3)

## 前言

虽然做出 $4$ 道题，但是~~这题我踩了多少坑也不知道呜呜呜~~。。。

## 思路

这题就是一个纯模拟题，按照题意写就行了。

但是，我写的时候，遇到了几个坑点：

### 1：纯模拟瞎搞

```cpp
#include <bits/stdc++.h>
using namespace std;
char s[100050],t[5];
int cnt[5],n,ct = 0;
bool flag = true;
int main(){
	scanf("%s%s",s + 1,t + 1);
	n = strlen(s + 1);
	for (int i = 1; i <= n; i++) 
		for (int j = 1; j <= 3; j++) 
			if (cnt[j] == 0 && s[i] - 'a' + 'A' == t[j]) 
				cnt[j] = ++ct;
	for (int i = 1; i <= 3; i++) 
		if (cnt[i] != i) 
			flag = false;
	if (flag) {
		printf("Yes");
		return 0;
	}
	if (t[3] != 'X') {
		printf("No");
		return 0;
	}
	memset(cnt,0,sizeof(cnt));
	ct = 0;
	flag = true;
	for (int i = 1; i <= n; i++) 
		for (int j = 1; j <= 2; j++) 
			if (cnt[j] == 0 && s[i] - 'a' + 'A' == t[j]) 
				cnt[j] = ++ct;
	for (int i = 1; i <= 2; i++) 
		if (cnt[i] != i) 
			flag = false;
	if (flag) printf("Yes");
	else printf("No");
	return 0;
}
```

然后 WA 了……

发现有这样一组数据：

```
oior
IOR
```

我却输出了 `No`。我发现，原来是读到第一个 `o` 的时候已经把 `O` 标记掉了，导致后面第二个 `o` 就标记不了了，就输出了 `No`。

### 2：dfs 乱搞。

```cpp
#include <bits/stdc++.h>
using namespace std;
char s[100050],t[5];
int n,ss = 3;
bool flag = false;
int st[5];
void dfs(int k,int step){
	if (step > ss) {
		flag = true;
		return;
	}
	for (int i = k; i <= n; i++) 
		if (s[i] - 'a' + 'A' == t[step]) 
			dfs(i + 1,step + 1);
	return;
}
int main(){
	scanf("%s%s",s + 1,t + 1);
	n = strlen(s + 1);
	dfs(1,1);
	if (flag == true) {
		printf("Yes");
		return 0;
	}
	if (t[3] == 'X') {
		ss = 2;
		dfs(1,1);
		if (flag == true) {
			printf("Yes");
			return 0;
		}
	}
	printf("No");
	return 0;
}
```

TLE 了呜呜呜。

我发现这组数据似乎能够卡掉这个程序：

```
100000 个 a
AAA
```

结果 `A` 每遇到一个 `a` 就会进入下一层递归，尽管已经有了可行解。被卡到了 $n^3$。所以再优化一句：

```cpp
if (flag) return;
```

放在循环里。

### 3：还有点问题的代码

```cpp
#include <bits/stdc++.h>
using namespace std;
char s[100050],t[5];
int n,ss = 3;
bool flag = false;
int st[5];
void dfs(int k,int step){
	if (step > ss) {
		flag = true;
		return;
	}
	for (int i = k; i <= n; i++) {
		if (flag) return;//这里
		if (s[i] - 'a' + 'A' == t[step]) dfs(i + 1,step + 1);
	}
	return;
}
int main(){
	scanf("%s%s",s + 1,t + 1);
	n = strlen(s + 1);
	dfs(1,1);
	if (flag == true) {
		printf("Yes");
		return 0;
	}
	if (t[3] == 'X') {
		ss = 2;
		dfs(1,1);
		if (flag == true) {
			printf("Yes");
			return 0;
		}
	}
	printf("No");
	return 0;
}
```

### 4.又被卡了。

这是在赛后传上去的数据（#49 没过看这里）（我自己想的数据）

```
50000 个 a 和 50000 个 b
ABC
```

还是不行啊，被卡到了 $O(n^2)$。

实际上，当循环到最后一个位置的时候，已经说明是不可行解了。

看这张图（作图粗糙请原谅）

![](https://cdn.luogu.com.cn/upload/image_hosting/8b806owa.png)

当下标为 $n + 1$ 时，表明目标字符串中的 $T_i$ 在 $S$ 中第一个 $T_{i - 1}$ 后没有出现 $T_i$，那么说明无解，输出 `No`。

```cpp
#include <bits/stdc++.h>
using namespace std;
char s[100050],t[5];
int n,ss = 3;
bool flag = false;
bool can = true;//标记
int st[5];
void dfs(int k,int step){
	if (step > ss) {
		flag = true;
		return;
	}
	for (int i = k; i <= n; i++) {
		if (flag) return;
		if (!can) return;//退出
		if (s[i] - 'a' + 'A' == t[step]) dfs(i + 1,step + 1);
	}
	can = false;//到最后一个位置时就不行了
	return;
}
int main(){
	scanf("%s%s",s + 1,t + 1);
	n = strlen(s + 1);
	can = true;
	dfs(1,1);
	if (flag == true) {
		printf("Yes");
		return 0;
	}
	if (t[3] == 'X') {		
		can = true;
		flag = false;//别忘了改回来
		ss = 2;
		dfs(1,1);
		if (flag == true) {
			printf("Yes");
			return 0;
		}
	}
	printf("No");
	return 0;
}
```

### 后记

我真蒻啊，赛时差不多把所有的坑都踩了一遍。

要是有什么问题或 Hack 数据，我会尽量回复的！

---

## 作者：CQBZ_ZJYjoe (赞：2)

[题目传送门](https://atcoder.jp/contests/abc349/tasks/abc349_c)

## 题目思路
看到本题，可以轻易发现，本题分为两种构成情况
- 当 $T$ 的最后一个字符为 `X`，则需要在 $S$ 中找出与 $T$ 前两个字符匹配的子序列。
- 否则，在 $S$ 中找出与 $T$ 匹配的子序列。

再结合数据范围可以发现暴力匹配即可。

**注意输入内容大小写**！

## 代码实现
```cpp
#include<bits/stdc++.h>
#define fast_io ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define lowbit(x) x&-x
#define endl '\n'
#define ve vector
#define pq priority_queue
#define dq deque
#define mk make_pair
using namespace std;
using ll=long long;using db=double;using ull=unsigned long long;using ldb=long double;using fl=float;using bo=bool;using i128=__int128_t;using uint128=__uint128_t;
string s,t;
int main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	fast_io;
	cin>>s>>t;
	t[0]=t[0]-'A'+'a';
	t[1]=t[1]-'A'+'a';
	t[2]=t[2]-'A'+'a';//将大写转小写 
	if (t[2]=='x')//分情况讨论
	{
		int tx=0,ls=s.size(),xt;//tx来判断是否匹配，xt来保存匹配到了第几个字符
		for (int i=0;i<ls;i++)
			if (s[i]==t[0])
			{
				tx++;
				xt=i+1;
				s[i]='A';
				break;
			}
		if (!tx)//不匹配则停止
		{
			cout<<"No";//输出不符合
			return 0;
		}
		tx=0;
		for (int i=xt;i<ls;i++)
			if (s[i]==t[1])
			{
				tx++;
				s[i]='A';
				xt=i+1;
				break;
			}
		if (!tx)
		{
			cout<<"No";
			return 0;
		}//同上
	}
	else //需要匹配三个字符
	{
		int tx=0,ls=s.size(),xt;//同上
		for (int i=0;i<ls;i++)
			if (s[i]==t[0])
			{
				tx++;
				xt=i+1;
				s[i]='A';
				break;
			}
		if (!tx)
		{
			cout<<"No";
			return 0;
		}
		tx=0;
		for (int i=xt;i<ls;i++)
			if (s[i]==t[1])
			{
				tx++;
				s[i]='A';
				xt=i+1;
				break;
			}
		if (!tx)
		{
			cout<<"No";
			return 0;
		}
		tx=0;
		for (int i=xt;i<ls;i++)
			if (s[i]==t[2])
			{
				tx++;
				s[i]='A';
				break;
			}
		if (!tx)
		{
			cout<<"No";
			return 0;
		}
	}
	cout<<"Yes";//匹配成功
	return 0;
}
```

---

## 作者：Harrylzh (赞：2)

对于第一种情况，依次看“机场代码”对应的小写字母有没有在原字符串中出现。第二种情况，如果末尾有 $\texttt X$，就把 $\texttt X$ 去掉后再找就可以了。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
string s,t;
long long dq=0;
int main()
{
	cin>>s>>t;
	for(long long i=0;i<s.size();i++)
	{
		if(s[i]==t[dq]+32) dq++;
		if(dq==3) break;
	}
	if(dq==3)//第一种
	{
		printf("Yes\n");
	}
	else if(dq==2&&t[2]=='X') printf("Yes\n");//第二种
	else printf("No\n");//都不满足
	return 0;
}
```

---

## 作者：qhr2023 (赞：1)

## 思路

直接模拟即可。

先转换大小写，如果 $T_2$ 是 `x`，在 $s$ 的末尾加上 `x`，省去特判。

我们用 $f$ 表示现在匹配完了 $f$ 位，当匹配完 3 位时，输出 `Yes`，循环结束都没输出说明不能匹配，输出 `No`。

```cpp
#include<bits/stdc++.h>
using namespace std;
string s, T;
int main(){
	cin >> s >> T;
	for(int i=0; i<3; i++) T[i]=T[i]-'A'+'a';
	if(T[2]=='x') s+='x';
	int f=0;
	for(int i=0; i<(int)s.size(); i++){
		if(s[i]==T[f]) f++;
		if(f==3){ 
			puts("Yes"); 
			return 0; 
		}
	}
	puts("No");
	return 0;
} 
```

---

## 作者：ckjiojojiojoiwj (赞：1)

# [题目传送门](https://www.luogu.com.cn/problem/AT_abc349_c)
这道题有一种最简单的办法**暴力枚举**！！！

------------
这道题的号码有可能是三位也有可能是两位，这是就是特判的魅力所在了。之后我们就用贪心去暴力即可。

------------
代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
string s,t;//字符串s与t对应题目中的S与T
ll f,tf;//t的下标以及这是第几位
int main(){
	cin>>s>>t;//输入
	if(t[2]=='X'){//特判：有可能号码只有两位最后一位是用来填充的
		tf=1; 
	}
	for(int i=0;i<s.size();i++){
		if(tf==3){//满足就退出
			cout<<"Yes";
			return 0;
		}
		if(s[i]==t[f]-'A'+'a'){//可以匹配一位
			tf++;
			f++;
		}
	}
	if(tf==3){//特判：有可能t的最后一个号码是s的最后一位
		cout<<"Yes";
		return 0;
	}
	cout<<"No";
    return 0;
}
```

---

## 作者：SkyLines (赞：1)

## 前言

![](https://cdn.luogu.com.cn/upload/image_hosting/ps3qw9xn.png)

## 思路

模拟，两种情况分开讨论，这里将字符串 $T$ 的第一个字符表示为 $T_1$，字符串 $S$ 的第一个字符表示为 $S_1$。

对于第一种情况：

设 $ans_1,ans_2,ans_3$ 分别为在 $S$ 中找到 $T_1,T_2,T_3$ 的编号。

1. 如果 $S_i$ 与 $T_3$ 只有大小写之分，并且 $ans_3=0$。此方案顺序正确，更新 $ans_3$，否则重新选择一种方案。

2. 如果 $S_i$ 与 $T_1$ 只有大小写之分，并且 $ans_1=0$ 或要重新选择一种方案，则更新 $ans_1$。

3. 如果 $S_i$ 与 $T_2$ 只有大小写之分，并且 $ans_2=0$，$ans_1 \ge 1$，$ans_1$ 是此方案的，则更新 $ans_2$。

对于第二种情况：

设 $ans_1,ans_2$ 分别为在 $S$ 中找到 $T_1,T_2$ 的编号。

同理可得。

答案就很显然了。

如果 $S$ 中找到一组合法的 $ans_1,ans_2,ans_3$，即 $ans_1 \ge 1$ 且 $ans_2 \ge 1$ 且 $ans_3 \ge 1$，符合第一种情况。

如果 $S$ 中找到一组合法的 $ans_1,ans_2$，即 $ans_1 \ge 1$ 且 $ans_2 \ge 1$ 且 $T_3$ 为 ``X``，符合第二种情况。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int max_(int aa, int bb){
	return aa > bb ? aa : bb;
}
int min_(int aa, int bb){
	return aa < bb ? aa : bb;
}
int abs_(int aa){
	return aa > 0 ? aa : -aa;
}
int pow_(int aa, int bb, int cc){
	int ans = 1;
	while(bb){
		if(bb & 1) ans = ans * aa % cc;
		aa = aa * aa % cc;
		bb >>= 1;
	}
	return ans;
}
int ls, ans, ans2, ans3, ans4, ans5;
bool flg;
string s, t;
int main(){
	cin >> s >> t;
	ls = s.length();
	for(int i = 0; i < ls; i++){
		if(s[i] == t[0] - 'A' + 'a' && ((!ans) || flg)){
			ans = i + 1;
			flg = 0;
		}
		if(s[i] == t[1] - 'A' + 'a' && !ans2){
			if(ans < i + 1 && ans) ans2 = i + 1;
		}
		if(s[i] == t[2] - 'A' + 'a' && !ans3){
			if(ans2 < i + 1 && ans2) ans3 = i + 1;
			else flg = 1;
		}
		if(s[i] == t[0] - 'A' + 'a' && (!ans4)){
			ans4 = i + 1;
		}
		if(s[i] == t[1] - 'A' + 'a' && !ans5){
			if(ans4 < i + 1 && ans4) ans5 = i + 1;
		}
	}
	if((ans && ans2 && ans3) || (ans4 && ans5 && t[2] == 'X')) printf("Yes");
	else printf("No");
	return 0;
}
```

---

## 作者：ZRZ0818 (赞：1)

~~一道简单的字符串遍历问题~~。

对于末尾不是 `X` 的 $T$，我们需要从 $S$ 中找到字符串 $T$ 所有三个字符对应的小写字母。

否则，仅需找到前两个，再加一个	`X` 即可。

如果找不到，输出 `No`，反之输出 `Yes`。

**注意：可以不连续，但顺序不能变。**

 _完整 code:_ 
 
 ```cpp
#include<bits/stdc++.h>
#define MAXN 100005

using namespace std;

int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	
	string s1,s2;  cin >>s1 >>s2;
	char add ='a'-'A';
	int len =s1.length(),sum1 =0,sum2 =0,sum3 =0,ind1 =0,ind2 =0,ind3 =0;	
	for ( int i=0; i<len; i++) {
		if ( s1[i]-add ==s2[0]) {
			++sum1,ind1 =i; break;
		}
	}
	for ( int i=ind1+1; i<len; i++) {
		if ( s1[i]-add ==s2[1]) {
			++sum2,ind2 =i; break;
		}
	}
	for ( int i=ind2+1; i<len; i++) {
		if ( s1[i]-add ==s2[2]) {
			++sum3,ind3 =i; break;
		}
	}
	
//	cout <<sum1 <<" "<<sum2 <<' '<<sum3 <<'\n';
	if ( s2[2] =='X' && sum1 && sum2) puts("Yes");
	else if ( sum1 && sum2 && sum3) puts("Yes");
	else puts("No");
	
//	system("pause");
	return 0;
}
/******
narita
NRT

losangeles
LAX

snuke
RNG

*******/	
```

---

## 作者：Pink_Cut_Tree (赞：1)

# AT_abc349_c [ABC349C] Airport Code 题解

### 解析

观察题目可以发现：若 $t$ 的最后一位为 `X`，则可以将这个 `X` 删掉。

然后判断 $s$ 中与 $t$ 匹配的子序列即可。

这里正着匹配或倒着都可以，我选择了倒着。

```cpp
#include<bits/stdc++.h>
using namespace std;
string s,t;
int pos;
int main(){
	cin.tie(0)->sync_with_stdio(0);
	cin>>s>>t;
	if(t[2]=='X'){
		pos=1;
	}
	else{
		pos=2;
	}
	for(int i=s.size()-1;i>=0;i--){
		s[i]=s[i]-'a'+'A';
		if(s[i]==t[pos]){ //往前一位
			pos--;
			if(pos==-1){ //全都匹配完了
				cout<<"Yes"; return 0;
			}
		}
	}
	cout<<"No"; 
return 0;
}
```

---

## 作者：Igallta (赞：1)

这道题我的思路比较简单。

先把 $T$ 串全部转成小写。

然后判断如果 $T$ 串有 `x` 就删掉（只删 $1$ 个）。

接下来记录所有字母出现的位置。

以下 $T$ 串第 $i$ 个字符出现的位置是 $a_i$。

然后判断 $T$ 串是三位还是两位，如果是三位就判断 $a_1 < a_2 <a_3$ 即可，两位同理（$a_1 < a_2$），如果满足以上任意条件就输出 `Yes`。

循环完后还没有输出 `Yes` 就输出 `No`。

代码：

```cpp
#include<bits/stdc++.h>
#define LL k<<1
#define RR k<<1|1
#define int long long

using namespace std;
string x, y;
vector<int>vec[256];
signed main() {
	ios::sync_with_stdio(0);
	cin >> x >> y;
	for (int i = 0; i < y.size(); i++) {
		y[i] = tolower(y[i]);
	}
	if (y[y.size() - 1] == 'x') {
		y.pop_back();
	}
	for (int i = 0; i < x.size(); i++) {
		vec[x[i]].push_back(i);
	}
	if (y.size() == 2) {
		for (auto u : vec[y[0]]) {
			for (auto v : vec[y[1]]) {
				if (u < v) {
					cout << "Yes";
					return 0;
				}
			}
		}
		cout << "No";
	} else {
		for (auto u : vec[y[0]]) {
			for (auto v : vec[y[1]]) {
				for (int w : vec[y[2]]) {
					if (u < v && v < w) {
						cout << "Yes";
						return 0;
					}
				}
			}
		}
		cout<<"No";
	}
	return 0;
}
```

---

## 作者：unordered_yao (赞：0)

## 思路

1. 题目中的字符串 $T$ 只有三个大写英文字母，且第一条规则和第二条规则均可以将其中的一些字母改为大写字母。第二条规则还可以在末尾添加 ```X```。所以我们只需要分类讨论两种情况，第一种情况，字符串 $T$ 的最后一个字符为 ```X```。第二种情况，最后一个字符不是 ```X``` 的字符串 $T$。

2. 由上可得出，如果字符串 $T$ 最后一个字符为 ```X```，我们就可以将这个字符删除。判断前两个字符是否为字符串 $S$ 的子序列即可。如果没有 ```X```，直接判断该字符串是否为 $S$ 的子序列即可。

## 代码

```cpp
#include<bits/stdc++.h>

using namespace std;
string s,t;
bool panduan(){
  int m = s.size(),n = t.size();
	int i=0, j=0;
	while (i < n){
		if (s[j] == t[i]){
			i++,j++;
			if (i != n&&j == m) return 0;
		}
		else{
			j++;
			if (j == m) return 0;
		}
	}
	return 1;
}
int main(){
    cin >> s >> t;
    for(auto& m : s){
        if(m>='a'&&m<='z') m-=32;
    }
    if(t[2] == 'X') t = t.substr(0,2);
    if(panduan()) puts("Yes");
    else puts("No");
    return 0;
}
```

---

## 作者：xu_zhihao (赞：0)

### 题目理解：
- 简单贪心分析题。分两种情况讨论：
1. 如果 $T$ 末尾为 ``X`` 的话，就只用在 $S$ 的依次寻找 $T_0,T_1$。
1. 如果 $T$ 末尾不为 ``X`` 的话，就只用在 $S$ 的依次寻找 $T_0,T_1,T_2$。

- 注：依次寻找是指比如 $T_0$ 在 $S$ 的第 $i$ 位找到了，那么在 $i+1$ 位开始寻找 $T_1$。

### AC 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	string s;
	string t;
	cin>>s>>t;
	int l1=s.size();
	for(int i=0;i<l1;i++)
	{
		if(s[i]>='A' && s[i]<='Z')
		{
			s[i]=(s[i]-'A')+'a';
		}
	}
	for(int i=0;i<3;i++)
	{
		if(t[i]>='A' && t[i]<='Z')
		{
			t[i]=(t[i]-'A')+'a';
		}
	}
	if(t[2]=='x')
	{
		int l=0;
		int y=0;
		while(y<l1 && l<2)
		{
			if(s[y]==t[l])
			{
				l++;
			}
			y++;
		}
		if(l==2)
		{
			cout<<"Yes"; 
		}
		else
		{
			cout<<"No";
		}
	}
	else
	{
		int l=0;
		int y=0;
		while(y<l1 && l<3)
		{
			if(s[y]==t[l])
			{
				l++;
			}
			y++;
		}
		if(l==3)
		{
			cout<<"Yes"; 
		}
		else
		{
			cout<<"No";
		}
	}
}
```
[AC 记录](https://atcoder.jp/contests/abc349/submissions/52650463)

---

## 作者：_anll_ (赞：0)

### 大体思路
从前往后扫一次进行 $S$ 串与 $T$ 串的子序列匹配，之后分类讨论：

- 如果完全被匹配，则直接输出 `Yes`。

- 如果前两个被匹配且 $T$ 串的最后一个字符为 `X` 则输出 `Yes`。

- 其它均输出 `No`。

### 代码演示
~~真的还需要演示吗~~大体思路就是这样，如果还有不清晰的地方请结合代码理解。
```
#include<iostream>
#define int long long
using namespace std;
int vu[10];
string a,b;
signed main(){
	cin>>a>>b;
	vu[0]=1;
	for(int i=0;i<a.size();i++){
		for(int j=0;j<b.size();j++){
			if(a[i]-'a'+'A'==b[j]&&vu[j]&&!vu[j+1]){
				vu[j+1]=1;
				break;
			}
		}
	}
	if(vu[1]&&vu[2]&&vu[3])
		cout<<"Yes"<<endl;
	else if(vu[1]&&vu[2]&&b[2]=='X')
		cout<<"Yes"<<endl;
	else cout<<"No"<<endl;
	return 0;
}
```

---

## 作者：_ayaka_ (赞：0)

### 思路
其实很简单，先将所有的 $s$ 中字母转为大写，然后循环一边查找 $s$ 与 $t$ 的相同字母，具体是这样的：

- 求出 $t$ 的长度 $n$（当然等于 $3$）；

- 定义一个 $cnt$，表示目前已匹配到了 $t_{cnt}$；

- 循环比对 $s_i$ 与 $t_{cnt}$，若相同就让 $cnt=cnt+1 $；

- 若 $cnt = n+1$，说明所有字母都被找到，跳出循环，输出 `Yes`，否则输出 `No`。

当然值得注意的是，若 $t$ 的结尾是 X，则应让 $n=n-1$。

### 代码
```
#include<bits/stdc++.h>
using namespace std;
#define int long long
string s, t;
int n = 3, cnt = 1;
signed main() {
	cin >> s >> t;
	transform(s.begin(), s.end(), s.begin(), ::toupper);//将字母转换成小写
	s = ' ' + s;
	t = ' ' + t;
	if (t[3] == 'X') n = 2;
	for (int i = 1; i <= s.length()-1; i++) {
		if (s[i] == t[cnt]) {
			cnt++;
			if (cnt == n+1) {
				cout << "Yes";
				return 0;
			}
		}
	}
	cout << "No";
	return 0;
}
```

---

## 作者：nxd_oxm (赞：0)

# 题意
给你两个字符串 $s,t$。其中 $s$ 为小写字符串， $t$ 为大写字符串。设 $t$ 转为对应小写后为 $p$，若 $p$ 是 $s$ 的子序列，或 $p$ 前两位为 $s$ 的子序列，第三位为 `x`，就将 $t$ 称为 $s$ 的机场代码。

如果 $t$ 为 $s$ 的机场代码，输出 `Yes`。反之，输出 `No`。
# 思路
用 vector 记录每个字符在 $s$ 中出现的位置。挨个计算 $t$  中字符，取当前字符 $t_i$ 转为小写后在 $s$ 中出现的最早位置，并记录，因为要求是子序列，所以下一次 $t_{i+1}$ 取的位置就必须在这之后了。

注意特判 $t$ 的最后一位是 `x` 的情况。
## AC code
```cpp
#include<bits/stdc++.h>
#define f(i,j,n) for(int i=j;i<=n;i++)
#define int long long
using namespace std;
string a,b;
vector<int>mp[151];
vector<int>mp1[151];
vector<int>mp2[151];
signed main(){
	cin>>a>>b;
	f(i,0,a.size()-1){
		mp[a[i]-'a'+'A'].push_back(i);
	}
	if(mp[b[0]].size()>=1){
		f(i,mp[b[0]][0]+1,a.size()-1){
			mp1[a[i]-'a'+'A'].push_back(i);
		}
	}else{
		cout<<"No";
		return 0;
	}
	if(mp1[b[1]].size()>=1){
		f(i,mp1[b[1]][0]+1,a.size()-1){
			mp2[a[i]-'a'+'A'].push_back(i);
		}
	}else{
		cout<<"No";
		return 0;
	}
	if(mp2[b[2]].size()||b[2]=='X'){
//		mp[b[2]]--;
		cout<<"Yes";
	}else{
		cout<<"No";
		return 0;
	}
	cout<<endl;
	return 0;
}
```

---

## 作者：T_TLucas_Yin (赞：0)

首先肯定要先把 $S$ 的每一位都转成大写字母。遍历 $S$，如果一个字符与 $T$ 中的某字符相同，且 $T$ 中对应位以前的每一个字符都已经标记上了，就标记这一位。最后，$T$ 的最后一位如果有标记，就说明可行。如果 $T$ 的最后一位是 `X` 的话，那么倒数第二位有标记就可行。否则不可行。

```cpp
#include<bits/stdc++.h>
using namespace std;
string s,t;
bool flag[3];
int main(){
	cin>>s>>t;
	for(int i=0;i<s.size();i++){
		s[i]-=32;
		if(flag[0]){
			for(int j=1;j<=2;j++){
				if(s[i]==t[j]&&flag[j-1]){
					flag[j]=1;
					break;
				}
			}
		}
		else if(s[i]==t[0]) flag[0]=1;
	}
	if(flag[2]||(flag[1]&&t[2]=='X')) cout<<"Yes";
	else cout<<"No";
	return 0;
}
```

---

## 作者：wfirstzhang (赞：0)

# ABC349C
[原题链接](https://www.luogu.com.cn/problem/AT_abc349_c)
## 思路
本质是找子序列，考虑遍历 $S$。
- 输入字符串 $S$ 和 $T$，遍历 $S$，如果发现 $T$ 中**按顺序**有对应字母就标记（如果是已经标记了就不能再次标记）。

- 判断时分两种情况：

1. $T$ 末尾有 `X`：只需要判断前面两个标记是否存在，如果存在，就输出 `Yes`， 否则输出 `No`。

1. $T$ 末尾没有 `X`：如果三个标记都存在，输出 `Yes`， 否则输出 `No`。

注意是**有序**的子序列，第一遍踩坑 `WA` 了 12 个点。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
string s, t;
bool a, b, c; // 标记
int main() {
    cin >> s >> t;
    for(int i = 0; i < s.size(); i++)
    {
        s[i] -= 32; //转换成大写字母
        if((a == 0 && b == 0 && c == 0) && s[i] == t[0])    a = 1;
        else if(a && c == 0 && s[i] == t[1]) b = 1;
        else if(a && b && s[i] == t[2])    c = 1;
      	 // 如果符合条件就标记
    }
    if((a && b && c) || (a && b && t[2] == 'X'))   cout << "Yes" << endl;
  	//  判断两种情况，有其中一种就输出Yes
    else cout << "No" << endl;
    return 0;
}
```

---

## 作者：CuteForces (赞：0)

### 思路：
暴力枚举 $S$ 的每一位，如果这一位和 $T$ 的当前位相等，将 $T$ 要匹配的位下标 $+1$，最后判断结尾是否有 `X` 即可。    
code:
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
string a ,b;
int j; 
signed main(){
	cin >> a >> b;
	for (int i = 0; i < a.size(); i++) {
		if (toupper(a[i]) == b[j] && j < 3) j++;
	}
	if (b[2] == 'X' && j == 2) cout << "Yes";
	else if (j == 3) cout << "Yes";
	else cout << "No";
	return 0;
}
```

---

## 作者：__xsy2013__ (赞：0)

~~AT&你谷通过这场比赛名字颜色成功一样~~

在支持正则表达式库的语言中，可以轻松实现判断字符串 $T$ 是否是字符串 $S$ 的子串。例如，要确定 `NRT` 是否是字符串 $S$ 的子串，相当于检查 `N.*R.*T` 是否出现在 $S$ 中。

此外，如果将 `X` 追加到给定的 $S$ 中，就可以忽略问题陈述中提到的两种方法中的第二种。

示例实现（Python）：

```python
import re

S = input().upper() + "X"
T = input()
print("Yes" if re.search(".*".join(T), S) else "No")

```

---

## 作者：haokee (赞：0)

在此提供一个题解区代码最短的简单解法。

## 题目大意

现在给你两个字符串 $S$ 和 $T$，你可以选择两种方式来完全匹配 $T$：

- 在 $S$ 里面取出一个长度为 $3$ 的子序列（可以不连续）；
- 在 $S$ 里面取出一个长度为 $2$ 的子序列（同理），并在末尾加上 `X`。

输出能否完全匹配 $T$。

## 思路

首先，如果 $T$ 的末尾是 $X$，那么第二种方式才是有用的，在这种情况下我们只需要将 $T$ 的最后一个字符删掉来匹配就行了。

然后考虑取子序列，我们可以使用一个指针 $p$ 来描述字符串 $T$ 我们已经匹配到了多少位。遍历 $S$，如果当前字符能够继续匹配 $T$ 的话，那么就将指针右移，最后看一看有没有匹配完全即可。

## 代码

```kotlin
import java.util.*

val cin = Scanner(System.`in`)

val s = cin.next()
var t = cin.next()
var p = 0

fun main() {
  if (t.last() == 'X') {                   // 如果末尾为 X
    t = t.substring(0, t.length - 1)       // 删掉最后一个
  }
  for (c in s) {                           // 遍历 S
    if (p < t.length && c - 32 == t[p]) {  // 如果没有超出限制并能继续匹配
      p++                                  // 多匹配一个
    }
  }
  // 最后判断一下匹没匹配完就行了
  println(if (p == t.length) "Yes" else "No")
}
```

---

## 作者：int_stl (赞：0)

这道题虽然简单，但是坑点很多，让我吃了 $4$ 罚时。

刚开始我们先将 $S$ 的所有字母变成大写的，接下来考虑用 $p$ 来表示当前寻找的是第几个字母，如果 $T_p \in S$，将 $p$ 加 $1$。

接下来考虑 $p$ 的值：
- 当 $p=3$（$p$ 刚开始为 $0$），这说明 $T$ 的所有字符都能**按顺序**在 $S$ 中找到，那么输出 `Yes`。
- 当 $p=2$，如果 $T_2$ 为 `X`，那么输出 `Yes`。
- 否则，输出 `No`。

代码如下：
```cpp
#include <iostream>
#include <string>
using namespace std;
int main() {
	string s;
	cin >> s;
	string code;
	cin >> code;
	for (int i = 0; i < code.size(); i++) code[i] = code[i] - 'A' + 'a';
	int ps = 0;
	int cnt = 0;
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == code[ps]) {
			ps++;
		}
	}
	if (ps == 3) {
		cout << "Yes";
	}
	else if (ps == 2 && code[2] == 'x') {
		cout << "Yes";
	}
	else cout << "No";
}
```

---

## 作者：nightwatch.ryan (赞：0)

### 思路
有两种情况：
- 从 $S$ 中取出长度为 $3$ 的子序列（不一定连续），并将其转换为大写英文字母，形成 $T$。
- 从 $S$ 取长度为 $2$ 的子序列（不一定连续），将其转换为大写字母，并在末尾添加 `X` 以形成 $T$。

对于第一种情况，判断 $T$ 的每个字符是否在 $S$ 里出现过，注意是从左往右判断。

对于第二种情况，判断 $T$ 的前两个字符是否在 $S$ 里出现过（和上面一样，也是要从左往右判断的），并且 $T$ 的最后一个字符没有在 $S$ 里出现过而且 $T$ 的最后一个字符是 `X`。

记得要将 $T$ 转换为小写。
### 代码
```cpp
#include<iostream>
#include<map>
int main(){
	std::string s,t;std::cin>>s>>t;
	for(int i=0;i<t.size();i++)t[i]=tolower(t[i]);
	bool f[3]={0};int idx=0;
	for(int i=0;i<s.size();i++)
		if(!f[idx]&&s[i]==t[idx])f[idx]=1,idx++;
	if((f[0]&&f[1]&&f[2])||(t[2]=='x'&&f[0]&&f[1]&&!f[2])){
		puts("Yes");
		return 0;
	}
	puts("No");
}
```

---

## 作者：__Cby___ (赞：0)

## 解题思路
直接模拟即可，我们用变量 $l$ 记录匹配到了 $T$ 的第几个字符。然后将两种变换方式都试一下就行了。  
## 代码
```cpp
#include <iostream>
using namespace std;
int main() {
	string s;
	string t;
	cin >> s >> t;
	int l = 0;
	for (int i = 0; i < s.length(); i++) {
		if (s[i]-'a'+'A' == t[l])l++;
	}
	if (l == 3) {
		cout << "Yes" << endl;
		return 0;
	}
	if (l == 2 && t[2] == 'X') {
		cout << "Yes" << endl;
		return 0;
	}
	cout << "No" << endl;
	return 0;
}
```

---

## 作者：joe_zxq (赞：0)

# 思路

我们遍历一遍 $S$，将它的字符依次与 $T$ 的三个字符进行匹配。我们定义三个 bool，表示每一个字符是否匹配成功，若发现一个字符相同，将对应的 bool 设置为 $1$，去匹配下一个字符。若**三个字符匹配成功**或者**匹配了前两个字符但 $T$ 的第三个字母是 `X`**，那么输出 `Yes`。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

#define ll long long

int main() {

	string s, t;
	cin >> s >> t;
	for (ll i = 0; i < (ll)t.size(); i++) {
		t[i] += 32;
	}
	bool f1 = 0, f2 = 0, f3 = 0;
	for (ll i = 0; i < (ll)s.size(); i++) {
		if (!f1) {
			if (s[i] == t[0]) {
				f1 = 1;	
			}
		} else if (!f2) {
			if (s[i] == t[1]) {
				f2 = 1;
			}
		} else if (!f3) {
			if (s[i] == t[2]) {
				f3 = 1;
			}
		} else {
			break;
		}
	}
	if (f3) {
		cout << "Yes";
	} else if (f2 && t[2] == 'x') {
		cout << "Yes";
	} else {
		cout << "No";
	}

	return 0;
}

```

---

## 作者：CEFqwq (赞：0)

因为有两种编码方法：

1. 选出一个三位子序列，转大写。

2. 选出一个二位子序列，转大写然后在末尾加 `X`。

所以考虑贪心。如果给定的编码末尾有 `X`，如果满足条件 $1$，一定满足条件 $2$。

所以先把编码转**小写**，然后判断末尾是不是 `x`（因为转小写了），如果是，依次找两位；如果否，依次找三位，暴力模拟即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
string s, t;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin >> s >> t;
	t[0] += 32;
	t[1] += 32;
	t[2] += 32;//转小写
	if (t[2] == 'x'){//依次找两位
		int fd = 0, fdd = 0, fddd = 0;
		for (int i = 0; i < s.size(); i++){
			if (!fd && s[i] == t[0])
				fd = 1;
			else if (fd && !fdd && s[i] == t[1])
				fdd = 1;
		}
		if (fd && fdd)//依次找到了两个字符
			cout << "Yes";
		else
			cout << "No";
		return 0;
	}
	int fd = 0, fdd = 0, fddd = 0;
	for (int i = 0; i < s.size(); i++){
		if (!fd && s[i] == t[0])
			fd = 1;
		else if (fd && !fdd && s[i] == t[1])
			fdd = 1;
		else if (fd && fdd && !fddd && s[i] == t[2])
			fddd = 1;
	}
	if (fd && fdd && fddd)//依次找到了三个字符
		cout << "Yes";
	else
		cout << "No";
}
```

---

## 作者：xxboyxx (赞：0)

### 翻译

给一个长度为 $3$ 的由大写英文字母组成的字符串 $T$ 和由小写英文字母组成的字符串 $S$，问 $T$ 是否可以通过以下方法之一从 $S$ 推导出来：

- 从 $S$ 中提取长度为 $3$ 的子序列（不一定连续），并将其转换为大写英文字母，形成 $T$。
- 从 $S$ 取长度为 $2$ 的子序列（不一定连续），将其转换为大写字母，并在末尾添加 `X` 以形成 $T$。

### 思路

按照题意模拟即可，可以先将字符串 $T$ 全部转换为小写。

若要用第一种方法将 $S$ 变为 $T$，要分别寻找到与 $T$ 中相同的字符，这里肯定选择找到的第一个，因为这样可以为后面的寻找多出一些选择。

若要用第二种方法将 $S$ 变为 $T$，首先 $T$ 的第三位必须为 `x`，接下来与第一种方法相似，只不过是寻找前两位。

### 注意

因为我们把 $T$ 全部转换为小写，所以在判断第三位是否为 `x` 时 `x` 应为小写。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
string a,b;
int x=-1,y=-1,z=-1;
int xx=-1,yy=-1;
int main()
{
	cin>>a>>b;
	int l=a.length();
	for (int i=0;i<3;i++)
		b[i]=b[i]-'A'+'a';
	for (int i=0;i<l;i++)
	{
		if (a[i]==b[0] && x==-1)//寻找第一个 
			x=i;
		else if (a[i]==b[1] && x!=-1 && y==-1)
			y=i;
		else if (a[i]==b[2] && x!=-1 && y!=-1 && z==-1)
			z=i;
	}
	if (x!=-1 && y!=-1 && z!=-1)//三个都找到了 
	{
		cout<<"Yes";
		return 0;
	}
	if (b[2]!='x')//第三位为X 
	{
		cout<<"No";
		return 0;
	}
	for (int i=0;i<l;i++)//同上 
	{
		if (a[i]==b[0] && xx==-1)
			xx=i;
		else if (a[i]==b[1] && xx!=-1 && yy==-1)
			yy=i;
	}
	if (xx!=-1 && yy!=-1)
	{
		cout<<"Yes";
		return 0;
	}
	cout<<"No";
	return 0;
}
```

---

## 作者：Liuliuliuliuliu (赞：0)

[题目](https://www.luogu.com.cn/problem/AT_abc349_c)

# 题目大意

给定一个小写字符串 $S$ 及一个长度为 $3$ 的大写字符串 $T$，判断 $T$ 是否是 $S$ 的 Airport Code。

$T$ 为 $S$ 的 Airport Code 要满足以下两个条件中的一个：
- 从 $S$ 中取长度为 $3$ 的子序列，并将其转换为大写字母，形成 $T$。

- 从 $S$ 中取长度为 $2$ 的子序列，将其转换为大写字母，并在结尾加上 `X`，形成 $T$。

# 解题思路

根据题目中形成 $T$ 的两个条件，我们可以分别判断，分别求解。

当 $T$ 的最后一个字符为 `X` 的时候，由于 $T$ 的长度为三，所以可以从前向后遍历一遍找到 $T$ 中第一个字符，再从后向前遍历一遍找到 $T$ 中第二个字符，最后判断它们的位置关系。

如果不是以上的情况，那么依旧可以延用上述方法，依次找到 $T$ 中第一个字符、$T$ 中第二个字符、$T$ 中第三个字符，并判断它们的位置。

# 代码
```
#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<vector>
#include<algorithm>
#include<cstdlib>
using namespace std;
#define int long long
#define INF 0x3f3f3f3f 
inline int Read(){
    int x=0,f=1;
    char c=getchar();
    while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
    while(isdigit(c)){x=x*10+c-48;c=getchar();}
    return x*f;
}
inline void Write(int x){
	if(x<0) {putchar('-');x=-x;}
	if(x>9) Write(x/10);
	putchar(x%10+'0');
}

const int N=1e5+10;
string s,t;
int n;

bool tp(){
	if(t[2]!='X') return 0;//特判 
	int a=0,b=0;
	for(int i=1;i<=n;i++){
		if(s[i]==t[0]) {
			a=i;
			break;
		}
	}
	for(int i=n;i>=1;i--){
		if(s[i]==t[1]) {
			b=i;
			break;
		}
	}
	if(a&&b&&a<b) puts("Yes");
	else puts("No");
	return 1;//这里 return 1 是为了在主函数里方便判断结束程序。 
}

signed main(){
	getline(cin,s);getline(cin,t);
	s=" "+s;//下标从 1 开始
	n=s.length()-1;
	for(int i=1;i<=n;i++){
		if(s[i]>='a'&&s[i]<='z') s[i]=s[i]-32;
	}
	if(tp()) return 0;
	int a=0,b=0,c=0;
	for(int i=1;i<=n;i++){
		if(s[i]==t[0]) {
			a=i;
			break;
		}
	}
	for(int i=n;i>=1;i--){
		if(s[i]==t[2]){
			c=i;
			break;
		}
	}
	if(c==0||a==0||c<a) {
		puts("No");
		return 0;
	}
	for(int i=a+1;i<c;i++){
		if(s[i]==t[1]) {
			puts("Yes");
			return 0;
		}
	}
	puts("No");
	return 0;
}
```

---

## 作者：_colin1112_ (赞：0)

* 一道简单的模拟题。但吃了 4 次罚时。
  
输入两个字符串 $S,T$，然后分两种情况判断：

1. 末尾有 $x$：

将字符串 $T$ 上末尾的字符 $x$ 去掉然后两次 `for` 循环，判断前两个字符是否全部出现在字符串 $S$ 上，且两个字符在 $S$ 字符串的顺序是相同的，如果两个条件都满足，输出 `Yes`，否则输出 `No`。

2. 末尾没有 $x$：

三次 `for` 循环，判断三个字符是否全部出现在字符串 $S$ 上，且三个字符在 $S$ 字符串的顺序是相同的，如果两个条件都满足，输出 `Yes`，否则输出 `No`。

## AC Code

```c++
#include <bits/stdc++.h>
#define endl '\n'
#define ll long long

using namespace std;
const int E = 1e6 + 5;
string x, y;
inline char to_big(char x)
{
    if (x >= 'a' && x <= 'z')
        return x - 32;
    return x;
}
int main()
{
    cin >> x >> y;
    ll len = x.length(), len1 = y.length();
    if (y[2] == 'X')//第一个情况
    {
        ll id = 0;
        bool flag = 1, flag1 = 1;
        for (int i = 0; i < len; i++)
            if (to_big(x[i]) == (y[0]))
            {
                x[i] = 0;
                id = i;
                flag1 = 0;
                break;
            }
        for (int i = id + 1/*要顺序*/; i < len; i++)
            if (to_big(x[i]) == (y[1]))
            {
                x[i] = 0;
                flag = 0;
                break;
            }
        cout << ((!flag && !flag1) ? "Yes" : "No");
        return 0;
    }
  	  //第二种情况
    ll id = 0, id1 = 0;
    bool flag = 1, flag1 = 1, flag2 = 1;
    for (int i = 0; i < len; i++)
        if (to_big(x[i]) == (y[0]))
        {
            x[i] = 0;
            id = i;
            flag = 0;
            break;
        }
    for (int i = id + 1/*要顺序*/; i < len; i++)
        if (to_big(x[i]) == (y[1]))
        {
            x[i] = 0;
            id1 = i;
            flag1 = 0;
            break;
        }
    for (int i = id1 + 1; i < len; i++)
        if (to_big(x[i]) == (y[2]))
        {
            x[i] = 0;
            flag2 = 0;
            break;
        }
    cout << ((!flag && !flag1 && !flag2) ? "Yes" : "No");//是否成立
    return 0;
}
```

---

## 作者：Ivan422 (赞：0)

题目大意：在 $S$ 中选出一个长度 $3$ 的子序列，转为大写字母，要是子序列为 $T$ 或前 $2$ 个字符与 $T$ 的前 $2$ 个字符相等，最后一个为 $X$ 都被称作机场代码。

思路：直接模拟复杂度太大。按照顺序匹配，找到匹配就用 $T$ 的下一个字符去匹配。这样的复杂度是 $O(n)$ 的，不会超时。
```cpp
#include<bits/stdc++.h>
using namespace std;
//#define int long long
//#define double long double
//#define map unordered_map
//#pragma GCC optimize(2,3,"Ofast","inline")
const int N=129,M=1010,P=1e9+7,MOD=998244353;
const double PI=3.1415926,EPS=0.00001;
string s,t;
char bg;
int cur;
signed main(){
    cin>>s>>t;
    for(auto v:s){
        bg=v;if(bg>'Z')bg=(bg+'A'-'a');
        if(bg==t[cur]&&cur<3)cur++;
    }
    if(cur==3)cout<<"Yes";
    else if(cur==2&&t[cur]=='X')cout<<"Yes";
    else cout<<"No";
    return 0;
}
```

---

## 作者：2c_s (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc349_c)

## 思路

读入后循环遍历。用一个变量记录当前要从 $S$ 中寻找的 $T_i$，如果找到了（记得**大小写转换**）就令 $i+1$，找下一个字符。如果 $i$ 已经等于 $|T|$（$T$ 的长度）说明遍历完成，那么输出 ``Yes`` 结束程序。

如果遍历完 $S$ 之后 $i=|T|-1$，说明就差最后一位没有匹配上。这时候我们依照题意判断 $T$ 的最后一个字符是否为 ``X``，如果是就说明这是“附加字符”，输出 ``Yes``。

如果上面两部都不符合条件，输出 ``No``。

## AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
string s,t;
int pos;
signed main(){
	cin>>s>>t;
	for(int i=0;i<s.size();++i){
		if(s[i]+('A'-'a')==t[pos])++pos;
		if(pos==t.size()){//判断 1.
			cout<<"Yes";
			return 0;
		}
	}
	if(t[t.size()-1]=='X'&&pos==t.size()-1)cout<<"Yes";//判断 2.
	else cout<<"No";
	return 0;
}
```

[AC 记录](https://atcoder.jp/contests/abc349/submissions/52310294)

---

## 作者：qinmingze (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/AT_abc349_c)

## 思路

- 本题先要将两个字符串都统一成大写字母或者小写字母，然后遍历一遍字符串 $s$。判断最后的结果与字符串 $t$ 的长度相同即可。

- 因为本题的字符串 $t$ 最后一位可能是 X。所以对于这种情况**需要特判**。

## 代码

```cpp
#include<bits/stdc++.h>

using namespace std;

int main(){
	string s, t;
	cin >> s >> t;
   //统一转换。
	for(int i = 0; i < s.size(); i++){
		if(s[i] >= 'a' && s[i] <= 'z') s[i] -= 32;
	}
	for(int i = 0; i < t.size(); i++){
		if(t[i] >= 'a' && t[i] <= 'z') t[i] -= 32;
	}
	int tmp = 0;
   //对字符串 s 进行遍历。
	for(int i = 0; i < s.size(); i++){
		if(tmp == t.size()){//找到了
			puts("Yes");
			return 0;
		}
		if(s[i] == t[tmp]) tmp++;//找到一个，寻找下一个。
	}
	if(tmp == t.size() || tmp == t.size() - 1 && t[t.size() - 1] == 'X') puts("Yes");//符合要求的所有情况
	else puts("No");
	return 0;
}
```

---

## 作者：OIer_Tan (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc349_c)

## 题意

长度为 $3$ 的由大写英文字母组成的字符串 $T$ 是由小写英文字母组成的字符串 $S$ 的 Airport Code，当且仅当 $T$ 可以通过以下方法之一从 $S$ 得到：

- 从 $S$ 中取长度为 $3$ 的子序列（不一定连续），并将其转换为大写字母，形成 $T$。
- 从 $S$ 中取长度为 $2$ 的子序列（不一定连续），将其转换为大写字母，并在 $T$ 后追加 `X`，形成 $T$。

给定字符串 $S$ 和 $T$，判断 $T$ 是否是 $S$ 的 Airport Code。

## 思路

显然，可以做分讨，但其本质都是找子序列。

以第一种方式为例，显然可以直接使用 `s.find ( t [0] )` 来找到第一个出现 $t$ 的首个字母的位置。假设我们用 $k$ 来存储上一步找到的位置，接下来，可以通过 `s.find ( t [1] ， k + 1)` 来找到下一个字母的位置。\
第二种情况思路同上。

当然，你也可以通过在 $s$ 后添加一个字符 `X` 来将两个问题转化成一个。

## 代码

```cpp
#include<bits/stdc++.h>

#ifndef CRT
#define endl '\n' 
#endif

using namespace std ;

typedef long long ll ;
typedef unsigned long long ull ;
typedef long double ld ;

int main ()
{
	// freopen ( ".in" , "r" , stdin ) ;
	// freopen ( ".out" , "w" , stdout ) ;
	ios::sync_with_stdio ( 0 ) ;
	cin.tie ( 0 ) ;
	cout.tie ( 0 ) ;
	string s , t ;
	cin >> s >> t ;
	if ( t.back () == 'X' )
	{
		ll place1 = s.find ( tolower ( t [0] ) ) ;
		if ( place1 != string::npos )
		{
			ll place2 = s.find ( tolower ( t [1] ) , place1 + 1 ) ;
			if ( place2 != string::npos )
			{
				cout << "Yes" << endl ;
				return 0 ;
			}
			else
			{
				cout << "No" << endl ; 
				return 0 ;
			}
		}
		else
		{
			cout << "No" << endl ;
			return 0 ;
		}
	}
	else
	{
		ll place1  = s.find ( tolower ( t [0] ) ) ;
		if ( place1 != string::npos )
		{
			ll place2 = s.find ( tolower ( t [1] ) , place1 + 1 ) ;
			if ( place2 != string::npos )
			{
				ll place3 = s.find ( tolower ( t [2] ) , place2 + 1 ) ;
				if ( place3 != string::npos )
				{
					cout <<"Yes" << endl ;
					return 0 ;
				}
				else
				{
					cout << "No" << endl ;
					return 0 ;
				}
			}
			else
			{
				cout << "No" << endl ;
				return 0 ;
			}
		}
		else
		{
			cout << "No" << endl ;
			return 0 ;
		}
	}
	return 0 ;
}
```

---

