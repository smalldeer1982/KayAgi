# awoo's Favorite Problem

## 题目描述

### 翻译


你会得到两个长度为 $n$ 的字符串 $s$ 和 $t$。 两个字符串中的每个字符都是`a`、`b`或`c`。

在一个操作中，您可以执行其中之一：

选择 $s$ 中出现的 `ab` 并将其替换为 `ba` ；

选择 $s$ 中出现的 `bc` 并将其替换为    `cb`。

您可以执行任意数量的移动（可能为零）。 您可以更改字符串 $s$ 以使其等于字符串 $t$ 吗？

## 样例 #1

### 输入

```
5
3
cab
cab
1
a
b
6
abbabc
bbaacb
10
bcaabababc
cbbababaac
2
ba
ab```

### 输出

```
YES
NO
YES
YES
NO```

# 题解

## 作者：linyuhuai (赞：10)



[题目传送门](https://codeforces.com/contest/1697/problem/C) & [前往 blog 获得更好的阅读体验](https://by505244.github.io/oi_blogs/2022/06/18/CF1697C题解)

upd：增加~~貌似无关紧要~~的证明。

题目：

- `ab` 可以转化为 `ba`。

- `bc` 可以转化为 `cb`。

因此，`a` 只能往后移动，`c` 只能向前移动。

进一步观察发现，对于每次调换，只调换 `a,b` 或 `b,c` 的前后位置，并不调换 `a,c` 的前后位置。因为字符串呈现为 `ac` 或 `ca` 时是无法调动位置的。

综上所述，如果 $s$ 能调换成 $t$：

因为不论怎么调换都无法改变 `a,c` 的前后位置关系。

- 所以把 $s$ 和 $t$ 中全部的 `b` 都删掉 则 $s=t$。

由于 `a` 只能向后移动，`c` 只能向前移动。

- 所以在 $t$ 中，相同的 `a` 一定在 $s$ 中原来的地方或后面，相同的 `c` 一定在 $s$ 中原来的地方或前面。

其余情况则不能调换成 $t$。

~~这几个字写了我一个小时。~~

```cpp
#define INF 0x7fffffff
#define DEBUG puts("shsyyds");

void solve(){
    int n;
    scanf("%d",&n);
    std::string s,t;
    std::cin>>s;
    std::cin>>t;
    int j=0;
    int sb=0,sb2=0;//sum of 'b'
    for(int i=0;i<n;i++){
        while(t[j]=='b')sb2++,j++;
        if(s[i]=='b'){sb++;continue;}
        if(s[i]!=t[j]||s[i]=='a'&&i>j||s[i]=='c'&&i<j){
            puts("NO");
            return;
        }
        j++;
    }
    while(t[j]=='b')sb2++,j++;
    if(sb!=sb2){
        puts("NO");
        return;
    }
    puts("YES");
    return;
}
```

---

## 作者：alex_liu (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/CF1697C)

## 思路：

首先观察题面：

```
在一个操作中，您可以执行其中之一：

选择 s 中出现的 ab 并将其替换为 ba ；

选择 s 中出现的 bc 并将其替换为 cb 。
```

从操作一中可以发现，$a$ 字符的位置只能向后移动；从操作二可以发现，$c$ 字符的位置只能向前移动

那么假如我们忽略掉字符 $b$，举样例为例，即：
```
1：
s: ca_
t: ca_

2:
s: a
t: _

3:
s: a__a_c
t: __aac_

4:
s: _caa_a_a_c
t: c__a_a_aac

5:
s: _a
t: a_
```

再根据输出的结果，你会发现：只要字符 $a$ 和字符 $c$ 的相对位置不变，则可以将字符串 $s$ 转化为字符串 $t$ 

但是我们再看样例 5，虽然字符 $a$ 的相对位置没有变化，那为什么答案是 NO 呢？

如果再回去看我们之前得出来的结论（ $a$ 的位置只能向后移动），就可以得出这个答案了（当然  $c$ 同理）。

## AC CODE:

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n;
inline int read(){//快读优化 
	int x=0,f=1;
	char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
	return x*f;
}
signed main(){
	n=read();
	while(n--){
		string s1,s2;
		int len=read(),cnt1=0,cnt2=0;
		cin>>s1>>s2;//读入 s t 串 
		for(int i=0;i<len;i++){
			if(!(s1[i]^'b'))cnt1++;//记录 s 串中 b 字符的个数 
			if(!(s2[i]^'b'))cnt2++;//记录 t 串中 b 字符的个数 	
		}
		if(cnt1^cnt2)puts("NO");//当两个字符串的 b 字符个数不相同，则直接输出 NO 
		else{
			int x=0,f=0;
			for(int i=0;i<len;i++){
				if(!(s1[i]^'b'))continue;//只处理当前字符为 a,c 的情况 
				while(!(s2[x]^'b'))x++;//找到下一个不为 b 的字符 
				if(s1[i]^s2[x]||(!(s1[i]^'a')&&i>x)||(!(s1[i]^'c')&&i<x)){f=1;puts("NO");break;}//当相对位置不相同，或者 s 串中的 a 在 t 串中的 a 后面（ a 的相对位置相同 ），或者 s 串中的 c 在 t 串中的 c 前面（ c 的相对位置相同 ），则标记无解，输出 NO 并跳出循环 
				x++;
			}
			if(!f)puts("YES");//有解则输出 YES  
		}
	}
	return 0;
}
```


---

## 作者：Acerkaio (赞：2)

### 题

[Link](https://www.luogu.com.cn/problem/CF1697C)

### 思路

可以将 $\verb!ab!$ 替换成 $\verb!ba!$，也可以将 $\verb!bc!$ 替换为 $\verb!cb!$。

这里就告诉了我们 $a$ 只可能往前移动，$c$ 只可能往后移动，如果遇到 $\verb!ac!$ 或 $\verb!ca!$ 的情况则不能移动。

所以如果有解，那么两个序列去掉 $b$ 之后一定相同。

但要注意，如果 $s$ 串的 $a$ 的位置在与之对应的 $t$ 串的 $a$ 的位置的前面，或如果 $s$ 串的 $c$ 的位置在与之对应的 $t$ 串的 $c$ 的位置的后面，则无解！

### CODE

```cpp
#include <bits/stdc++.h>
using namespace std;
signed main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		string s, t;
		int len, sums = 0, sumt = 0;
		scanf("%d", &len);
		cin >> s >> t;
		for (int i = 0; i <s.size(); i++) {
			if (s[i] == 'b') sums++;
			if (t[i] == 'b') sumt++;
		}
		if (sums != sumt) {
			printf("NO\n");
			continue;
		}
		int js = 0;
		bool flag = 1;
		for (int i = 0; i < s.size(); i++) {
			if (s[i] == 'b') continue;
			while (t[js] == 'b') {
				js++;
			}
			if (s[i] != t[js] || (s[i] == 'a' && i > js) || (s[i] == 'c' && i < js)) {
				printf("NO\n");
				flag = 0;
				break;
			}
			++js;
		}
		if (flag) {
			printf("YES\n");
			continue;
		}
	}
	return 0;
}
```


---

## 作者：fast_photon (赞：2)

**0. 前言**  
CF [题](https://www.luogu.com.cn/problem/CF1697C)越来越像脑筋急转弯了。  

**1. 分析**  
`ab` 替换为 `ba`，也就是 `b` 在左边紧挨着是 `a` 的条件下向左移动了一格。  
`bc` 替换为 `cb`，也就是 `b` 在右边紧挨着是 `c` 的条件下向右移动了一格。  
然后你就会发现，三种字母的总个数不变，并且 `a` 和 `c` 之间是没有位置交换的。  
第一个约束条件~~横空~~出世：  
> $s$ 串和 $t$ 串中 `b` 的个数相同  
> 去掉所有的 `b` 之后两个串相等  

我们再来看，第一个替换可以想成 `a` 向右跳过一个 `b`，第二个可以想成 `c` 向左跳过一个 `b`，那么也就是 `a` 只能往右，`c` 只能往左。对于 $s$ 串中的一个 `b`（因为 `b` 与 `b` 之间是没有位置交换的，所以可以通过看分别是两个串里的第几个 `b` 来判断是否是同一个），它左边的 `a` 只能比 $t$ 串中的多，同理，它左边的 `c` 只能比 $t$ 串中的少。  

**2. 代码**  
这题实现起来还是有点恶心的，需要借助类似前缀和的思想来保证不超时，如果不会可以参考一下我的代码是怎么统计的。  
```cpp
#include<cstdio>
#include<string>
#include<queue>
#include<algorithm>
#include<iostream>
#define maxn 100005

using namespace std;

string s, t, ss, tt; //ss 和 tt 这两个串记录 s 和 t 里面不是b的字符，保留原顺序 
int T, n, a, c;
queue<int> A, C; //用队列分别记录每一个 b 前面的 a 和 c 数量 

void solve() {
	while(!A.empty()) A.pop(); //多测不清空，原地见祖宗 
	while(!C.empty()) C.pop(); 
	ss = tt = "";
	a = c = 0; //分别统计 a 的个数和 c 的个数 
	cin >> n;
	cin >> s >> t;
	for(int i = 0; i < n; i++) {
		if(s[i] == 'a') a++, ss += 'a'; 
		if(s[i] == 'c') c++, ss += 'c';
		if(s[i] == 'b') {
			A.push(a);
			C.push(c);
		}
	}
	a = c = 0; //这里一定要清空一次不然统计t的时候就会叠加s的结果 
	for(int i = 0; i < n; i++) {
		if(t[i] == 'a') a++, tt += 'a';
		if(t[i] == 'c') c++, tt += 'c';
		if(t[i] == 'b') {
			if(A.empty()) { //如果A空了，但是此时 t 串还有 b 没有考虑到，那么意味着两个字符串的 b 个数不一样，所以输出 NO 
				printf("NO\n");
				return ;       //每次输出完NO一定要记得 return
			}
			if(!(A.front() >= a && C.front() <= c)) { 
				printf("NO\n");
				return ;
			}
			A.pop();
			C.pop();
		}
	}
	if(ss != tt) {
		printf("NO\n");
		return ;
	}
	printf("YES\n");
}

int main() {
	cin >> T;
	while(T--) {
		solve();
	}
}
```

---

## 作者：liyp (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1697C)
[纯享版](https://www.luogu.com.cn/article/6f4pui50)
## 思路
### 对于字符的位置（部分代码中的代码一）
如果研究题意就可以发现，对于 $s$ 中任意一个为 `a` 的字符，它只能与位置位于它后面且与它相邻的 `b` 交换位置。也就是说，**`a` 经交换后在 $t$ 中的位置只可能在 $s$ 中原位置的后面或原位置**。

同理，经过推理我们也可以发现，**$s$ 中的任意一个 `c` 经过交换后在 $t$ 中的位置只可能在原位置的前面或原位置**。

### 对于数组的元素顺序（部分代码中的代码二）
根据题意我们不难发现，`a` 只能与 `b` 换位置，`c` 只能与 `b` 换位置，但 `a` 与 `c` 之间不能换位置。因此，如果 $s$ 可以在经过操作后变成 $t$，那么**在把 $s$ 与 $t$ 中的字符 `b` 全部去掉后 $s$ 和 $t$ 应该是相同的**。

### 总结
经过如上的推理我们可以知道，如果 $s$ 数组可以经过操作变成 $b$ 数组，那么必须满足一下三个条件：

1. $t$ 数组中的任意一个 `a` 的位置不应该在这个 `a` 原位置之前；

2. $t$ 数组中的任意一个 `c` 的位置不应该在这个 `c` 原位置之后；

3. 在把 $s$ 与 $t$ 中的字符 `b` 全部去掉后 $s$ 和 $t$ 应该是相同的。

## 部分代码
### 代码一
```cpp
vector<int>sva, svc; //记录 s 数组中 a 出现的位置和 c 出现的位置
vector<int>tva, tvc; //记录 t 数组中 a 出现的位置和 c 出现的位置

for (int i = 0; i < n; i++) {
	// 记录 s 与 t 数组中 a 与 c 出现的位置
	if (s[i] == 'a') {
		sva.push_back(i);
	}
	if (s[i] == 'c') {
		svc.push_back(i);
	}
	if (t[i] == 'a') {
		tva.push_back(i);
	}
	if (t[i] == 'c') {
		tvc.push_back(i);
	}
}

for (int i = 0; i < sva.size(); i++) { 
	if (tva[i] < sva[i]) {NO} // 对比 s 与 t 数组中 a 的位置
}
for (int i = 0; i < svc.size(); i++) {
	if (tvc[i] > svc[i]) {NO} // 对比 s 与 t 数组中 c 的位置
}
```
### 代码二
```cpp
string delb(string s) { // 删掉数组中的 b
	string ns = "";
	for (int i = 0; i < n; i++) {
		if (s[i] == 'b') { // 如果该位置是 b 就跳过
			continue;
		}
		else ns += s[i]; // 剩下的加入答案数组 ns
	}
	// cout << ns<<endl;
	return ns; // 返回
}

s = delb(s); // 删掉 s 数组中的字符 b
t = delb(t); // 删掉 t 数组中的字符 t
if (s != t) {NO} // 如果操作完的 s 与 t 不相同，则输出 NO
```
## 完整代码
```cpp
#include <bits/stdc++.h> // 万能头文件
#define LL long long
#define NO write("NO");putchar('\n');return; // 输出 NO
#define YES write("YES");putchar('\n'); // 输出 YES
using namespace std; 
int n, m; // 定义
inline int read() // 快读
{
	int x = 0, f = 1;
	char ch = getchar();
	while (ch<'0' || ch > '9')
	{
		if (ch == '-')
			f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
		x = x * 10 + ch - '0', ch = getchar();
	return x * f;
}
void write(string x)// 快写
{
	for (auto v : x) {
		putchar(v);
	}
	return;
}
// /*
// queue<int>q;
string delb(string s) { // 删掉数组中的 b
	string ns = "";
	for (int i = 0; i < n; i++) {
		if (s[i] == 'b') { // 如果该位置是 b 就跳过
			continue;
		}
		else ns += s[i]; // 剩下的加入答案数组 ns
	}
	// cout << ns<<endl;
	return ns; // 返回
}
// */
vector<int>sva, svc; //记录 s 数组中 a 出现的位置和 c 出现的位置
vector<int>tva, tvc; //记录 t 数组中 a 出现的位置和 c 出现的位置
void solve() { // 对于每一组数据
	// 初始化（防止上一组数据有残留）
	sva.clear(); svc.clear(); 
	tva.clear(); tvc.clear();

	// 输入
	string s, t; // 题面已给出
	n = read();
	cin >> s >> t;

	//处理
	for (int i = 0; i < n; i++) {
		// 记录 s 与 t 数组中 a 与 c 出现的位置
		if (s[i] == 'a') {
			sva.push_back(i);
		}
		if (s[i] == 'c') {
			svc.push_back(i);
		}
		if (t[i] == 'a') {
			tva.push_back(i);
		}
		if (t[i] == 'c') {
			tvc.push_back(i);
		}
	}
	s = delb(s); // 删掉 s 数组中的字符 b
	t = delb(t); // 删掉 t 数组中的字符 t
	if (s != t) {NO} // 如果操作完的 s 与 t 不相同，则输出 NO
	for (int i = 0; i < sva.size(); i++) { 
		if (tva[i] < sva[i]) {NO} // 对比 s 与 t 数组中 a 的位置
	}
	for (int i = 0; i < svc.size(); i++) {
		if (tvc[i] > svc[i]) {NO} // 对比 s 与 t 数组中 c 的位置
	}
	YES // 全部条件都满足，输出YES
	return;
}
signed main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	int T;
	T = read(); // 输入数据数
	while (T--) {
		solve(); //每一组数据
	}
	return 0;
}

```
警告：题解仅供参考用，严禁抄袭题解

---

## 作者：TH讠NK (赞：0)

考虑题目给的两种转换方法，我们可以做到：


1. aaab $\rightarrow$ baaa

1. abbb $\rightarrow$ bbba

1. bbbc $\rightarrow$ cbbb

1. bccc $\rightarrow$ cccb



其实 $12$ 同理，$34$ 同理，都可以通过同一种方法实现。

所以我们直接从左往右扫描，遇到不一样的就尝试改变，从后面找一个字母过来代替，如果成功就继续往后扫。

以 $\texttt{aaab}$ 为例，我们遇到 $\texttt{a}$ 之后（假设另一个字符串这个位置为 $\texttt{b}$，其他情况都不用进入这个分支），我们尝试从后面找一个 $\texttt{b}$ 过来跟这个 $\texttt{a}$ 交换，中途如果遇到了 $\texttt{c}$，那么就失败了。

细节见代码。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define il inline
il int read(){
	int x=0; char c=getchar();
	while(c<'0' || c>'9') c=getchar();
	while(c>='0' && c<='9') x=x*10+c-48, c=getchar();
	return x;
}
const int maxn=100050;
int T,n;
bool flag;//flag判断是否可行
char s[maxn],t[maxn];
int main(){
	T=read();
	while(T--){
	n=read();flag=1;
	cin>>s>>t;
	if(n==1 && s[0]!=t[0]) flag=0;
	for(int i=0;i<n && flag;i++){
		if(s[i]!=t[i]){//不一样就开始尝试改变
			if(s[i]=='c') flag=0;//如果是c就没救了
			else if(s[i]=='a'){
				if(t[i]=='c') flag=0;//a只能变b
				else for(int j=i+1;j<=n && flag;j++){
					if(j==n || s[j]=='c') flag=0;//若中途出现c则失败
					else if(s[j]=='b') {swap(s[i],s[j]); break;}//终于找到一个b，就换过去
				}
			}
			else{
				if(t[i]=='a') flag=0;//b只能变c
				else for(int j=i+1;j<=n && flag;j++){
					if(j==n || s[j]=='a') flag=0;//若中途出现a则失败
					else if(s[j]=='c') {swap(s[i],s[j]); break;}//终于找到一个c，就换过去
				}
			}
		}
	}
	cout<<(flag? "YES":"NO")<<endl;
	}
	return 0;
}
```


---

