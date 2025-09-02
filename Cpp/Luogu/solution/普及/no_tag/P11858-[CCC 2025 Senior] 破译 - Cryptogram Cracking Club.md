# [CCC 2025 Senior] 破译 / Cryptogram Cracking Club

## 题目背景

译自 CCC 2025 Senior T2。本题满分为 $15$。

## 题目描述

给定一个小写字母组成的字符串 $s$ 和一个非负整数 $c$。你需要求出，将这个字符串无限重复后，第 $c$ 个位置上的字符是什么。注意字符串是 $\text{0}-\text{indexed}$ 的，也就是 $s_0$ 是第一个字符。

为了减少输入量，我们将字符串做了压缩：具体地，我们将一段连续的相同字母 $\underbrace{\texttt{aa}\cdots\texttt{aa}}_{k\text{ 个}}$ 压缩成字母+出现次数 $\texttt{a}k$ 的形式。例如，$\texttt{aaaabccdddd}$ 被压缩成 $\texttt{a4b1c2d4}$。


## 说明/提示


#### 样例解释

- 样例 $1$ 解释：$\texttt{r2d2}$ 压缩前是 $\texttt{rrdd}$。

重复无数多次即为 $\texttt{rrddrrdd\textcolor{red}{r}rdd}\cdots$。

- 样例 $2$ 解释：$\texttt{a4b1c2d10}$ 压缩前是 $\texttt{aaaabccdddddddddd}$。




#### 子任务

对于 $100\%$ 的数据，保证：

- $2\le |s'|\le 2\times10^5$；
- $s'$ 中出现的整数的范围是 $[1,10^{12}]$；
- $0\le c\le 10^{12}$。

---

- $\text{Subtask 0(0 points})$：样例。
- $\text{Subtask 1(6 points})$：
	- $0\le c\le 2\times 10^3$；
	- $s'$ 中出现的整数的范围是 $[1,9]$；
    - 压缩前，$s$ 的长度不超过 $2000$。
- $\text{Subtask 2(3 points})$：
	- $0\le c\le 10^6$；
    - 压缩前，$s$ 的长度不超过 $10^6$。
- $\text{Subtask 3(3 points})$：
    - 压缩前，$s$ 的长度不超过 $10^6$。
- $\text{Subtask 4(3 points})$：无特殊限制。

## 样例 #1

### 输入

```
r2d2
8```

### 输出

```
r```

## 样例 #2

### 输入

```
a4b1c2d10
100```

### 输出

```
d```

# 题解

## 作者：2011hym (赞：6)

## 问题分析
我们需要压缩后的字符串 $s'$ 和一个非负整数 $c$，找到**无限重复**字符串后的第 $c$ 个字符。压缩字符串的格式是字母后接重复次数，例如 `a4b2` 表示 `aaaabb`。由于字符串是无限重复的，我们可以通过计算字符串的总长度 $sum$，然后对 $c$ **取模**来简化问题。

## 解决思路
1. **解析字符串**：遍历压缩字符串，解析出每个字符及其对应的**重复次数**，并计算字符串的**总长度** $sum$。
2. **取模运算**：通过 $c\bmod sum$ 找到第 $c$ 个字符在原始字符串中的位置。
3. **查找字符**：再次遍历**压缩字符串**，累加字符的**重复次数**，直到找到第 $c\bmod sum$ 个字符。

## 代码实现
根据上文的思路，可以轻松实现，~s 组第二题也不是很难吗~。

```cpp
#include <bits/stdc++.h>
using namespace std;
long long sum, c, ans;
string s;
int main() {
    cin >> s >> c;
    // 第一次遍历
    for (size_t i = 0; i < s.length(); ) {
        char ch = s[i++];  // 当前字符
        long long cc = 0;  // 重复次数
        while (i < s.length() && isdigit(s[i])) {
            cc = cc * 10 + (s[i] - '0');  // 计算重复次数
            i++;
        }
        sum += cc;  // 累加
    }
    // 对 c 取模
    c %= sum;
    // 第二次遍历
    for (size_t i = 0; i < s.length(); ) {
        char ch = s[i++];  // 当前字符
        long long cc = 0;  // 重复次数
        while (i < s.length() && isdigit(s[i])) {
            cc = cc * 10 + (s[i] - '0');  // 计算重复次数
            i++;
        }
        if (ans + cc > c) {  // 如果累加后的长度超过 c，则当前字符就是答案
            cout << ch << endl;
            return 0;
        }
        ans += cc;  // 累加
    }
    return 0;
}
```

## 代码分析
只需要遍历**字符串长度**，复杂度为 $O(n)$，其中 $n$ 为字符串长度，因为 $n\le 10^5$，所以可以在预期时间内运行完毕。

---

## 作者：SerenityWay (赞：4)

题目要求处理一个压缩后的字符串，并将其无限重复后找到第 $c$ 个字符。
### 思路
压缩字符串的格式是字母+数字。例如 $\texttt{a4b1c2d4}$ 表示 $\texttt{aaaabccdddd}$。

将解压缩后的字符串无限重复，形成一个循环字符串。找到第 $c$ 个字符，可以通过模运算实现。由于 $c$ 和字符串长度较大（$10^{12}$），需要避免实际生成无限字符串，而是通过计算直接找到第 $c$ 个字符。

***

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
//找到第c个字符
char get(string s,ll c){
	ll l=0;//解压缩后的总长度
	int i=0;
	
	while(i<s.length()){
		char c=s[i++];//当前字符
		ll n=0;
		
		while(i<s.length()&&isdigit(s[i])){
			n=n*10+(s[i]-'0');//计算数字
			i++;
		}
		
		l+=n;//累加长度
	}
	
	//计算第c个字符的位置
	ll pos=c%l;
	
	//重新遍历字符串，找到第pos个字符
	i=0;
	ll l2=0;
	
	while(i<s.length()){
		char c=s[i++];//当前字符
		ll n=0;
		
		while(i<s.length()&&isdigit(s[i])){
			n=n*10+(s[i]-'0');//计算数字
			i++;
		}
		
		if(l2+n>pos)
			return c;//找到字符
		
		l2+=n;//累加长度
	}
	
	return '\0';//默认返回空字符
}

int main(){
	string str;
	ll c;
	cin>>str>>c;
	cout<<get(str,c)<<"\n";
	return 0;
}
```

***

$\operatorname{get}$ 函数第一次遍历字符串，计算解压缩后的总长度 $l$。通过模运算找到第 $c$ 个字符的位置 $pos$。第二次遍历字符串，找到第 $pos$ 个字符。

时间复杂度 $O(n)$，
空间复杂度为 $O(1)$。

---

## 作者：粥2414 (赞：3)

~~一道比较水的模拟题。~~
# 题目描述
以字母加连续出现次数的形式给你一个字符串，要求输出这个字符串无限循环之后，下标为 $c$ 的字母。
# 思路
直接模拟，利用小学二年级我们学到的知识可以明白，用 $c$ 模上单个字符串的长度 $sum$ 即可求出下标为 $c$ 的字母在单个字符串上的下标。然后我们只需要遍历一个字符串找出这个字母即可。  
注意下标从 $0$ 开始，所以 $c$ 模完 $sum$ 之后需要自加 $1$。
# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
string s;
ll c;
ll sum;
int main(){
	cin>>s;
	for(int i=0;i<s.end()-s.begin();i++){
		ll x=0;
		while(s[i]<='9'&&s[i]>='0'){
			x=x*10+s[i]-'0';
			i++;
		}
		sum+=x;
	}
	cin>>c;
	c%=sum;c++;
	for(int i=1;i<s.end()-s.begin();i++){
		ll ans=i-1,x=0;
		while(s[i]<='9'&&s[i]>='0'){
			x=x*10+s[i]-'0';
			i++;
		}
		if(c<=x&&s[ans]>='a'&&s[ans]<='z'){
			cout<<s[ans];return 0;
		}else c-=x;
	}
	return 0;
}
```

---

## 作者：cjx_AK (赞：3)

### 题目
给你一个压缩字符串，有若干个字节，格式为 a$k$，表示有 $k$ 个字符a，然后依次类推，之后成为一个循环节。然后给你一个位置，让你求这个位置是什么字符。

### 思路
是不是很像小学数学的一种气球问题，有几种不同的字符，可以把它看成气球来求解。

我们只需把循环节的字符数累加，再把位置取模，问题就解决了。

但还要注意，读入的时候是一个一个字符读入，所以碰到数字要读完才行。

code：

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct node{
	long long v;
	char c;
};
node a[2000005];
char s;
long long  x,k,t,cnt;
string S;
int tj(int x){
	int res=0;
for(int i=x;;i++){
	if(S[i]<'0'||S[i]>'9')break;
	res=res*10+(S[i]-'0');
}
	return res;
}
signed main(){
cin>>S;
	scanf("%lld",&k);
	for(int i=0;i<S.size();i++){
	if(S[i]>='a'&&S[i]<='z'){
			a[t].c=S[i];
			a[t].v=tj(i+1);
			cnt+=a[t].v;
			t++;
		}  
	}
	k++;
	k%=cnt;
	if(k==0){
		cout<<a[t-1].c<<endl;
		return 0;
	}
for(int i=0;i<t;i++){
	if(k-a[i].v<=0){
	printf("%c\n",a[i].c);
		return 0;
	}
	k-=a[i].v;
}
}
```

最后神犇（ben）们希望给可以给我点点关注，我会互关的！！

---

## 作者：yyycj (赞：1)

## 题目简述
一段连续的相同字母可以压缩成字母+出现次数 $ak$ 的形式。

给定压缩后的字符串 $s$ 和整数 $c$，求 $s$ 无限重复后的第 $c$ 个字符是什么，下标从 $0$ 开始。

## 主要思路
（虽然题目要求下标从 $0$ 开始，但题解中仍以下标从 $1$ 开始的方式描述字符串）


由于 $k$ 可能超过 $10^{12}$，所以不能将字符串展开。对于 $c$，由于下标从 $0$ 开始，也就是说假设 $c=10$ 时，求得是字符串无限重复后的第 $11$ 个字符。并且由于无限重复字符串是有周期性的，所以可以先 $c \to c+1$，再 $c \to (c-1) \bmod |s| + 1$。

我们可以维护一个 `pair<long long, char>` 前缀和数组 $pre$，$pre_{i}$ 的 `first` 表示字符串不无限重复时 $s_{pre_{i-1}+1} \sim s_{pre_{i}}$ 都为同一个字符 `second`。

维护好后，遍历 $pre$ 数组，当 $c \le pre_{i}$ 的 `first` 时，则表示 $c$ 在 $s_{pre_{i-1}+1} \sim s_{pre_{i}}$ 这个范围内，所以答案就为 $c \le pre_{i}$ 的 `second`，立即输出并结束循环。

## AC Code
```cpp
#include<map>
#include<set>
#include<queue>
#include<cmath>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<unordered_map>
#include<unordered_set>
using namespace std;

namespace IO {
	#ifdef ONLINE_JUDGE
	#define getchar getchar_unlocked
	#endif
	#define pc putchar
	#define gc getchar
	template<typename T> void read(T &x) { int f = 1; x = 0; char ch = gc(); while (!isdigit(ch)) { if (ch == '-')f = -1; ch = gc(); }while (isdigit(ch)) { x = (x << 1) + (x << 3) + (ch ^ 48); ch = gc(); }x *= f; }
	template<typename T, typename ...Args> void read(T &x, Args &...args) { read(x); read(args...); }
	template<typename T> void print(T x) { if (x < 0) { pc('-'); x = -x; }if (x > 9) { print(x / 10); }pc(char(x % 10 + 48)); }
	template<typename T, typename ...Args> void print(T &x, Args &...args) { print(x); pc(' '); print(args...); }
	inline void readstr(string& x) { x.clear(); char ch = gc(); while (isspace(ch)) ch = gc(); while (!isspace(ch) && ch != EOF) { x.push_back(ch); ch = gc(); } }
	inline void printstr(char* x) { for (int i = 0; i < (int)strlen(x); i++) pc(x[i]); }
	inline void printstr(string& x) { for (auto i = x.begin(); i != x.end(); i++) pc(*i); }
};
using namespace IO;

#define OUT 0
#define MAMBA return
typedef long long ll;
typedef long double db;
const int N = 1e5 + 10;
const int INT_INF = 0x3f3f3f3f;
int man();int main(){MAMBA man();}
const ll LL_INF = 0x3f3f3f3f3f3f3f3f;
inline int _abs(int a) { if (a < 0) return -a; return a; }
inline int _pow(int a, int b) { int x = 1, y = a; while(b > 0) {if (b & 1) x *= y; y *= y; b >>= 1; } return x; }
// ----------------------------

// ----------------------------
pair<ll, char> pre[N];
// ----------------------------


int man() {
	string s; readstr(s);
	ll c; read(c);
	// ----------------------------
	ll k, sum = 0;
	int j, cnt = 0;
	for (int i = 0; i < (int)s.length(); ) {
		k = 0;
		j = i + 1;
		while (j < (int)s.length() && isdigit(s[j])) {
			k = k * 10 + s[j] - '0';
			j++;
		}
		pre[cnt + 1] = make_pair(k + pre[cnt].first, s[i]);
		cnt++;
		sum += k;
		i = j;
	} 
	// ----------------------------
	c++;
	c = (c - 1) % sum + 1;
	for (int i = 1; i <= cnt; i++) {
		if (c <= pre[i].first) {
			pc(pre[i].second);
			break;
		}
	}
	MAMBA OUT;
}
/*
				 .-~~~~~~~~~-._       _.-~~~~~~~~~-.
			 __.'              ~.   .~              `.__
		   .'//   A    C    之   \./  之    真    理  \`.
		 .'//                     |                     \`.
	   .'// .-~"""""""~~~~-._     |     _,-~~~~"""""""~-. \`.
	 .'//.-"                 `-.  |  .-'                 "-.\`.
   .'//______.============-..   \ | /   ..-============.______\`.
 .'______________________________\|/______________________________`.
*/
```

---

## 作者：Doraeman (赞：1)

## 思路
观察到 $c$ 的数据范围过大，可以将 $c$ 对字符串 $s$ 的长度 $|s|$ 取模得到 $c'$，然后直接查询字符串 $s$ 的第 $c'$ 位即可。

## 实现
要想具体实现代码，有以下两个步骤。
1. 求字符串 $|s|$ 的长度。
2. 求字符串 $s$ 的第 $c'$ 个字符。

以下是这两个问题的回答。
1. 直接**将 $s'$ 中的每个整数相加**即可。
2. 枚举 $s'$ 中的每个整数并相加，**如果加上某个字符 $k$ 后，累计的长度总和达到了 $c'$**，说明**第 $c'$ 个字符一定是字符 $k$**。

接下来就可以开始快乐地写代码啦。

## 细节
### 获取整数
获取字符串 $s'$ 中的每一个整数（此处用数组 $a$ 保存）。

```cpp
string s;
int a[N], cnta = 0;
for(int i=0; i<s.size(); i++){
	ll t = 0;
	while('0' <= s[i] && s[i] <= '9'){
		t = t * 10 + (s[i] - '0');
		i++;
	}
	
	if(t) a[++cnta] = t;
	len += t;
}
```
### 字符与整数对应
我们需要将每个字符和其出现的次数一一对应，用于查询第 $c'$ 个字符是什么（详见“实现”中的第 $2$ 条）。

```cpp
for(int i=0; i<s.size(); i++){
	if(t) a[++cnt] = t;
	len += t;
		
	if('a' <= s[i] && s[i] <= 'z')
		b[++cntb] = s[i];
}
```
完成这个操作后，$a$ 和 $b$ 的元素完成对应，可以进行下一步。
### 求出 $c'$
接下来要求出 $c'$。

```cpp
cin >> c; c %= len;
```
### 查询第 $c'$ 个元素

```cpp
for(int i=1; i<=cnt; i++){
	if(sum + a[i] > c){
		cout << b[i];
		return 0;
	}
	sum += a[i];
}
```

注：部分变量名的定义没有展示在上述代码中。

## 代码
将上述所有步骤合在一起，就可以得出 AC 代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e6+5;

ll a[N]; int cnt;
char b[N]; int cntb;

int main(){
	ll len = 0, c; string s;
	cin >> s;
	for(int i=0; i<s.size(); i++){
		ll t = 0;
		while('0' <= s[i] && s[i] <= '9'){
			t = t * 10 + (s[i] - '0');
			i++;
		}
		
		if(t) a[++cnt] = t;
		len += t;
		
		if('a' <= s[i] && s[i] <= 'z')
			b[++cntb] = s[i];
	}
	cin >> c; c %= len;
	
	ll sum = 0;
	for(int i=1; i<=cnt; i++){
		if(sum + a[i] > c){
			cout << b[i];
			return 0;
		}
		sum += a[i];
	}
}
```

---

## 作者：guoshengyu1231 (赞：1)

## 题意简述
给定一个压缩字符串，求这个字符串重复若干遍后第 $c$ 个字符是什么？
## 初步思考
考虑到 $0\le c\le 10^{12}$ 那么暴力枚举显然是不可行的，那么我们该怎么办呢？ $\\$ 

既然 $c$ 太大了，那我们肯定是想办法让它变小。考虑到是将这个字符串重复若干遍，那么每一段都是相同的。所以我们只需要求第 $c$ 个字符在其中一段内是什么。 $\\$ 

到这里思路其实已经非常清晰了，最后只需暴力枚举即可。
## 具体步骤
读入字符串后，先将字符串中的字符列举出来，记录它们出现的次数。
### 示例：
> 输入:\
> a4b1c2d10
### 统计后：
> a b c d\
> 4 1 2 10

定义一个变量 $cnt$ 为压缩前字符串的长度，在将 $c$ 对 $cnt$ 取模。最后只需要求原字符串中第 $c$ 个字符就行啦！
## 代码

```cpp
#include<bits/stdc++.h> 
#define int long long  
using namespace std;
string s;
int i,k,cnt;
struct{
	char c;
	int num;
}w[200005];
int getnum()
{
	int num=0;
	while(i<s.size()&&s[i]>='0'&&s[i]<='9')
	 {
		num=num*10+s[i]-'0';
		i++;
	 }
	return num;
}
signed main()
{
	cin>>s;
	while(i<s.size())
	 {
		int ch=s[i++];k++;
		w[k].c=ch;
		w[k].num=getnum();
		cnt+=w[k].num;
	 }
	int t;
	cin>>t;
	t=t%cnt+1;
	for(i=1;w[i].num<t;i++) t-=w[i].num;
	cout<<w[i].c;
	return 0;
}
```

---

## 作者：corner_xiejunqi (赞：1)

#### 题目分析：
定义这个压缩后的字符串为 $str$，连续字母字符串 $s$，和连续字母的个数 $sum$。因为未压缩的字符串中只含有小写字母，所以只需在压缩字符串中寻找当前小写字母 $str[i]$，将它加入 $s$ 中，然后找到下一个小写字母 $str[j]$，那么当前小写字母的个数就为从 $str[i+1]$ 到 $str[j-1]$ 的数字，求出数字并加入 $sum$ 中，求出原有字符串字母个数 $tot$，然后 $c$ 取余 $tot$，即所求字符在原有字符串中的下标。然后在压缩后的字符串求出该字符即可。
#### 代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long//记得开long long
const int N=1e6+10; 
string str;
int num,tot=0;
int sum[N];
char s[N];
signed main(){
	cin.tie(0);cout.tie(0);
	ios::sync_with_stdio(false);
	cin>>str>>num;
	int len=str.size();
	for(int i=0;i<len;i++){
		char now=str[i];
		s[++tot]=now;
		if(now>='a' && now<='z'){
			i+=1;
			int start=i;
			for(;i<len;i++){
			    int now1=str[i+1];
				if(i+1==len || now1>='a' && now1<='z'){
					int t=1,ans=0;
					for(int j=i;j>=start;j--){
						ans+=(str[j]-'0')*t;
						t*=10; 
					}
					sum[tot]=ans;
					break;
				}
			}
		}
	}
	int sum1=0,sum2=0;
	//for(int i=1;i<=tot;i++) cout<<s[i]<<' '<<sum[i]<<'\n';
	for(int i=1;i<=tot;i++) sum1+=sum[i];
	int mod=num%sum1;
	for(int i=1;i<=tot;i++){
		sum2+=sum[i];
		if(sum2>mod){
			cout<<s[i];
			return 0;
		}
	}
    return 0;
}

```

---

## 作者：_Deer_Peach_ (赞：1)

题意已经很清晰了不再赘述。

思路：

$c$ 的范围很大，但是给出的字符串是无限循环的，所以可以先求出原字符串的长度，就算出了剩下的字符个数。

存下每个字符以及它的数量，再从第一个字符开始，用一个变量记录累加字符的数量，直到大于等于 $c$ 时，输出答案。

注意：
1. 字符串从 $0$ 开始标号，也就是第 $c$ 个位置上字符实际是第 $c+1$ 个字符；
2. 如果 $(c+1)$ 可以整除 $sum$，则直接输出最后一个字符。

这道题与周期问题类似。

代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
#define IOS ios::sync_with_stdio(false);cin.tie(0);cout.tie(0)
const int N=1e5+5;
int num[N],c;
char a[N];
string s;
int ncnt,acnt,sum;
signed main(){
    IOS;
	cin>>s>>c;c++;
	int len=s.size();
	int Num=0;
	for(int i=0;i<len;i++){//存数字和字符
		if(s[i]>='0'&&s[i]<='9')Num=Num*10+s[i]-'0';
		else a[++acnt]=s[i],num[ncnt]=Num,sum+=Num,Num=0,ncnt++;
	}num[ncnt]=Num;sum+=Num;
	c%=sum;sum=0;
	if(c==0){cout<<a[acnt];return 0;}//能整除
	for(int i=1;i<=ncnt;i++){
		sum+=num[i];
		if(sum>=c){
			cout<<a[i];
			return 0;
		}
	}
	return 0;
}
```

---

## 作者：MaiJingYao666 (赞：1)

# P11858 [CCC 2025 Senior] 破译 / Cryptogram Cracking Club 题解  
并不怎么难的一道模拟题？  
***
### 解题思路  
很朴素的输入，遇到一个字母就标记，然后一直遍历到下一个字母之前，把这些数读入，也就是 $k_i$，存进一个数组里，我们设存了 $n$ 组。  
然后看到是无限直接复制，根据小学学的周期问题，知道第 $c$ 个数也就是第 $c \bmod s$ 个数，其中 $s = \sum_{i=1}^{n} k_i$。  
接下来，由于数据不大，所以直接 $\mathcal O(n)$ 推过去就可以了。
***
注意下标从 0 开始。  
### AC 代码  
```cpp
#include<iostream>
#include<vector>
using namespace std;
string s;
long long c;
vector<pair<char,long long> > v;
long long su;
int main(){
	cin>>s;
	char tmp;
	long long k=0;
	for(int i=0;i<s.size();i++){
		if('a'<=s[i] && s[i]<='z'){
			tmp=s[i];
		}
		else{
			while('0'<=s[i] && s[i]<='9'){
				k=(k<<3)+(k<<1)+(s[i]-'0');
				i++;
			}
			v.push_back({tmp,k});
			su+=k;
			i--;
			k=0;
		}
	}
	cin>>c;
	c%=su;
	su=0;
	for(int i=0;i<v.size();i++){
		su+=v[i].second;
		if(su>c){
			cout<<v[i].first;
			return 0;
		}
	}
}
```

---

## 作者：chenyyy (赞：1)

很显然这题不能用模拟。
## Solution
我们得到一个 $c$，因为要求出将这个字符串无限重复后，第 $c$ 个位置上的字符是什么。所以，我们可以 $c \bmod n$ 来求出其余数 $c'$，然后因为序列是无限循环的，所以只用枚举什么时候字符串的字母到了 $c'$ 就可以了。
## Coding
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
string s;
int n,m;
vector<pair<char,int> > v;//v分别储存字符和它所占的个数
signed main(){
	cin >> s >> m;
	char c = s[0];//c代表上一个字符
	int a = 0;
	for(int i = 1;i < s.size();i++){
		if(s[i] <= 'z' && s[i] >= 'a'){
			v.push_back({c,a});
			n += a;
			c = s[i];
			a = 0;
		}
		else{
			a = (s[i] ^ '0') + (a << 1) + (a << 3);
		}
	}
	v.push_back({c,a});
	n += a;
	m %= n;//m%字符串长度
	auto i = v.begin();
	while(true){
		m -= (*i).second;
		if(m < 0){//m<0说明已经到了位置，直接输出
			cout << (*i).first;
			return 0;
		}
		i++;
	}
	return 0;
}
```
[AC记录](https://www.luogu.com.cn/record/206515383)

---

## 作者：FZY_CZY (赞：1)

赛时没仔细读题，不小心写成了二分。
# 思路
思路楼上楼下讲的都很清楚了，就是设立一个二元组，依照输入的形式，将一个字符和这个字符重复的次数捆绑在一起，将 $c$ 对于一整个字符串的重复次数取模，然后从前往后依次遍历，找到第一个前缀和大于 $c$ 的地方。

我的思路再次基础上略有改动，因为我们发现做完一次前缀和之后，整个数组是具有单调性的，所以我们可以通过二分更快的实现这一要求，时间复杂度 $O(len+\log n)$，$len$ 是字符串的长度，输入的时候我们处理数字和前缀和，就是线性的，然后进行二分，是 $\log$ 级的。

---
# 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=100010;
string s;
int n;
char c[N];
int num;
int op,t;
int a[N];
signed main(){
    cin>>s>>t;
    t++;
    int len=s.size();
    for (int i=0;i<len;i++)
    {
        if (!(s[i]>='0'&&s[i]<='9'))
        {
            if (num!=0)
            {
                a[n]=num,a[n]+=a[n-1],num=0;
            }
            c[++n]=s[i];
        }
        else num=num*10+(s[i]-'0');
    }
    a[n]=num,a[n]+=a[n-1];
    int l=0,r=n+1;
    t%=a[n];
    while (l<r)
    {
        int mid=l+r>>1;
        if (a[mid]>=t) r=mid;
        else l=mid+1;
    }
    cout<<c[r];
    return 0;
}
``````
注意，当 $t=0$ 的时候，应该是到达了数组的末尾，所以特判直接输出最后一组字符。

---

## 作者：chenxi2009 (赞：1)

## 思路
我们可以把 $s$ 转换成字符和数字的二元组序列，考虑先读入一个字符，然后仿照快读的标程读入一个数字，遇到的第一个非数字字符如果是换行符就结束，否则将其作为下一个二元组的字符继续读入。

然后将 $c$ 对 $s$ 的周期取模扫一遍就是了。

时间复杂度 $O(\vert s\vert)$。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
char s[300000],c;
long long a,num[300000],tot,sum,cnt;
int main(){
	s[cnt = 1] = getchar();//读入第一个字符 
	while(true){
		c = getchar();
		while(c >= '0' && c <= '9') num[cnt] = num[cnt] * 10 + c - '0',c = getchar();//类比快读理解 
		if(c == '\n') break;//如果读到的是换行就结束 
		s[++ cnt] = c;//否则读入下一个二元组 
	}
	for(int i = 1;i <= cnt;i ++) sum += num[i];//统计 s 的周期 
	scanf("%lld",&a);
	a = a % sum + 1;
	for(int i = 1;i <= cnt;i ++){
		tot += num[i];
		if(tot >= a){
			printf("%c",s[i]); 
			break;
		}
	}
	return 0;
}
```

---

## 作者：Besheep (赞：1)

「注意字符串是 $\text{0}-\text{indexed}$ 的，也就是 $s_0$ 是第一个字符。」
## Solution
由于 $0\le c\le 10^{12}$，我们无法去枚举每一个字符串，考虑让 $c$ 变小，注意到「字符串无限重复循环」，我们可以求出一次循环内字符串的字母数量 $cnt$，用 $c \bmod cnt$ 可以求出 $c$ 在该次循环的位置。

举例：

$$\texttt{rrdd|rrdd|\textcolor{red}{r}rdd}\cdots$$

此时 $c=8,cnt=4$，经过取模操作后 $c=0$，我们只需要求第 $0$ 个字符即可。

可以将 `r2d2` 存为 `[('r',2), ('d',2)]` 。我们称 `('r',2)` 为一个字符区间，维护一个当前累计的长度 $sum$。对于每个区间的字符 $zm$，次数 $k$：

- 如果 $sum + k > c$，则说明 $c$ 在这个区间内。输出 $zm$。

- 反之继续寻找下一个区间。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
string s;
ll c,temp;
char cc=0;
int main(){
    cin>>s>>c;
    vector<pair<char,ll>>b;
    for (char ch:s){
        if(isdigit(ch))temp=temp*10+(ch-'0');
        else{
            if(cc!=0){
                b.emplace_back(cc,temp);
                temp=0;
            }
            cc=ch;
        }
    }
    if(cc!=0)b.emplace_back(cc,temp);
    ll cnt=0;
    for (auto&[zm,k]:b)cnt+=k;
    c=c%cnt;
    ll sum=0;
    for(auto&[zm,k]:b){
        if(c<sum+k){
            cout<<zm;
            return 0;
        }
        sum+=k;
    }
    return 0;
}
```

---

## 作者：ZSYhaouuan (赞：1)

比较的模拟题，但是考虑的细节比较多。

读完题后，我们的大体思路就是：计算出一组循环的字母总数量，用 $c$ 对这个总数取余，再查找剩下的数字对应的是哪个字母即可。

很简单对吧？但是细节太多了！

首先，我们 $c$ 的范围是 $10^{12}$，注意变量的存储类型。

其次，它这道题是先输字母再输数字，所以要在每一次输入字母时把上一个字母的个数存进去。

然后，在输入完之后，还要把最后一个字母的个数单独存进去。

最后，我们查找是哪个字母的时候，不是循环到 $n$，而是循环字母的种数次。

代码展示：


```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll N = 2e5+100;
char c[N];
ll sum[N];
string s;
ll cnt, tot;
/*
s:输入的字符串
c[]:每一个字母
sum[]:每一个字母的个数
cnt:每一个字母在数组的下标
tot:一组的字母数量总和
*/
int main() {
	cin >> s;
	ll x = 0;
	//x:当前字母的数量
	for (ll i = 0; i < s.length(); i++) {
		if (s[i] < '0' || s[i] > '9') {
			sum[cnt] = x;
			tot += sum[cnt];
			c[++cnt] = s[i];
			x = 0;
		} else {
			x = x * 10 + (s[i] - '0');
			//字母的数量更改
		}
	}
	sum[cnt] = x;
	tot += sum[cnt];
	//a:题目中的c
	ll a;
	cin >> a;
	a %= tot;//取余
	//now:当前字母的数量，用来寻找答案是哪个字母
	ll now = 0;
	for (ll i = 1; i <= cnt; i++) {
		now += sum[i];
		if (now > a) {
			//若数量大于剩余的字母数量，则答案是c[i]
			cout << c[i];
			return 0;
		}
	}
	return 0;
}
```

这个题解总结容易错的地方，简单易懂。放我过题解吧！

---

## 作者：LiSA_OLiVE (赞：0)

~~来水题解了。~~
## 思路
原本的字符串太长，询问的 $n$ 也有 $10^{12}$，我们肯定是不能复原这个字符串的。那我们就不复原，遍历一遍，把每个字母和它后面对应的重复次数记下来，放进数组 $t$ 和 $a$ 里。然后 $a$ 数组的和 $sum$ 就是字符串原长。由于无限重复，所以我们实际上要找的就是原字符串中第 $n\bmod sum+1$ 个字符是什么。然后顺着找到就可以了。

有两点与要注意。
- $n\bmod sum+1$ 中不要忘了加一。
- 这道题很坑，题面写的 $2\le |s'|\le 10^5$，但是下载数据发现有长度不止 $10^5$ 的 $s'$ 存在。建议数组开大点。
## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
char s[1000020],t[1000020];
int a[1000020];
signed main(){
	cin>>s;
	int n;cin>>n;
	int tot=0;
	int sum=0;
	for(int i=0;i<strlen(s);i++){
		t[tot]=s[i];//记录下当前字母 
		int x=0;//处理后面紧跟着的数字是多少 
		i++;
		while(i<strlen(s) && (s[i]<'a'||s[i]>'z')){
			x=x*10+s[i]-'0';
			i++;
		}
		i--;//此时已经是下一个字母的位置了。别忘了退回一位，不然for循环会再加一次就出错了。 
		a[tot++]=x;sum+=x; 
	} 
	n=n%sum+1;
	int i=0;
	while(n){//找到第n%sum+1个数是谁 
		if(n<=a[i]) break; 
		n-=a[i];
		i++;
	}
	cout<<t[i];
	return 0;
}
```

---

## 作者：_d_h_f (赞：0)

## Solution

一眼思维题，剖析 $s'$，将它分成两个部分，$a$ 和 $ch$，$ch$ 存储每个字符，而 $a$ 存储每个字符的循环次数，求出 $\sum_{i = 1}^{n} a_i$，用 $tot$ 存储，对 $c$ 进行操作，取模 $tot$，再加一，然后对 $a$ 进行扫描累加，如果此时 $\sum_{j = 1}^{i} a_j \ge c$，则输出 $ch_i$，直接结束程序。

代码实现并不难，没有复杂的算法，只是需要一些思考即可解决。

## Code


```cpp
#include <bits/stdc++.h>

#define int long long

using namespace std;

const int N = 1e6 + 5;

int n, c;

vector<int> a;

char s[N];

vector<char> ch;

signed main() {
	
	scanf("%s", s + 1);
	
	scanf("%lld", &c);
	
	n = strlen(s + 1);
	
	for (int i = 1; i <= n; ) {
		
		int sum = 0, j = i;
		
		for (; s[j] >= '0' && s[j] <= '9' && j <= n; ++j)
			sum = sum * 10 + (s[j] - '0');
		
		i = j;
		
		a.push_back(sum);
		
		ch.push_back(s[i]);
		
		i++;
		
	}
	
	a.erase(a.begin());
	
	int every_turn = 0;
	
	for (auto x : a)
		every_turn += x;
		
	c %= every_turn;
	
	c ++;
	
	int tot = 0;
	
	for (int i = 0; i < a.size(); ++i) {
		
		tot += a[i];
		
		if (tot >= c) {
			
			cout << ch[i] << endl;
			
			exit(0);
			
		}
		
	}
	
	return 0;
	
}
```

---

## 作者：AnOIer (赞：0)

需要些许思考的模拟题。

### Solution

因为字符串是循环的，所以我们只需要知道无限字符串的第 $n$ 个字母在其所属的字符串的位置 $p$ 即可。

先把压缩字符串一个字母对应的出现次数处理出来。

因为位置 $p$ 只与一个字符串有关，所以可以每次用 $p$ 减去字母出现次数，当 $p \le 0$ 时说明第 $p$ 个字母在这一段字母中，输出次数对应的字母即可。
 
### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int sum=0;
int ston(string str) {
	int res=0,k=0;
	for(int i=str.size()-1;i>=0;i--) {
		res+=((str[i]-'0')*(pow(10,k)));
		++k;
	}
	return res;
}
string getsub(int begin,int end,string str){
	string res="";
	for(int i=begin;i<=end;i++){
		res+=str[i]; 
	}
	return res;
}
int tot=0;
struct inf{ //记录信息
	char ch; //字母
	int cnt; //字母对应次数
}a[1000000];
signed main() {
	string str,rr=" ";
	cin>>str;
	str+="z";
	int n,last=1;
	cin>>n;
	for(int i=0;i<str.size()+1;i++) {
		if(str[i]>='a'&&str[i]<='z') {
			if(i) {
				a[tot].cnt=ston(getsub(last,i-1,str)); //处理出次数
				last=i+1;
			}
			a[++tot].ch=str[i]; //处理字母
			continue;
		}
	}
	tot--;
	for(int i=1;i<=tot;i++) {
		sum+=a[i].cnt; //求整个字符串的长度
	}
	int p=n%sum+1; //求出位置
	for(int i=1;i<=tot;i++) {
		p-=a[i].cnt;
		if(p<=0) {
			cout<<a[i].ch<<"\n";
			return 0;
		}
	}
	return 0;
}
```

---

