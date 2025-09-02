# Love Song

## 题目描述

Petya once wrote a sad love song and shared it to Vasya. The song is a string consisting of lowercase English letters. Vasya made up $ q $ questions about this song. Each question is about a subsegment of the song starting from the $ l $ -th letter to the $ r $ -th letter. Vasya considers a substring made up from characters on this segment and repeats each letter in the subsegment $ k $ times, where $ k $ is the index of the corresponding letter in the alphabet. For example, if the question is about the substring "abbcb", then Vasya repeats letter 'a' once, each of the letters 'b' twice, letter 'c" three times, so that the resulting string is "abbbbcccbb", its length is $ 10 $ . Vasya is interested about the length of the resulting string.

Help Petya find the length of each string obtained by Vasya.

## 说明/提示

In the first example Vasya is interested in three questions. In the first question Vasya considers the substring "aba", that transforms to "abba", so the answer is equal to $ 4 $ . In the second question Vasya considers "baca", that transforms to "bbaccca", so the answer is $ 7 $ . In the third question Vasya considers the string "abacaba",that transforms to "abbacccabba" of length $ 11 $ .

## 样例 #1

### 输入

```
7 3
abacaba
1 3
2 5
1 7```

### 输出

```
4
7
11```

## 样例 #2

### 输入

```
7 4
abbabaa
1 3
5 7
6 6
2 4```

### 输出

```
5
4
1
5```

## 样例 #3

### 输入

```
13 7
sonoshikumiwo
1 5
2 10
7 7
1 13
4 8
2 5
3 9```

### 输出

```
82
125
9
191
62
63
97```

# 题解

## 作者：BurningEnderDragon (赞：8)

[题目链接：CF1539B Love Song 题解](https://www.luogu.com.cn/problem/CF1539B)

## 题意解释

Petya 写了一首**仅包含英文小写字母**的 love song（一个字符串），在这首 love song 中，对于英文字母表中的第 $k$ 个字母，Petya 会把它读 $k$ 次。给定 $q$ 个区间 $\left[ l,r \right]$，求这首 love song 中 $\left[ l,r \right]$ 之间的字母总共被读了多少次。

## 结论

设 $a_{i}$ 为 love song 中的第 $i$ 个字母，$k_{i}$ 表示 $a_{i}$ 在字母表中的位置，$ans_{i}$ 表示 $a_{i}$ 被读的次数，显然 $ans_{i}=k_{i}$。

如果对于每一次询问都遍历区间 $\left[ l,r \right]$ 计算答案，则单次询问的时间复杂度为 $O \left( r-l+1 \right)$，如何优化？

维护 $ans_{i}$ 的前缀和即可。此时单次询问的时间复杂度为 $O \left( 1 \right)$，询问总时间复杂度为 $O \left( q \right)$。

## 代码

```cpp
#include <iostream>
#include <string>
using namespace std;
int n,q,l,r,ans[100001];
string song;
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>q>>song;
	for(int i=1;i<=n;++i)
	{
		ans[i]=ans[i-1]+song[i-1]-'a'+1;
	}
	for(int i=1;i<=q;++i)
	{
		cin>>l>>r;
		cout<<ans[r]-ans[l-1]<<endl;
	}
	return 0;
}
```



---

## 作者：可爱的小于 (赞：6)

本题让我们输入一个字符串，求这个字符串几组区间内的总和。

第一，我们可以把字符串里的每一个字符都赋值，存入一个数组中。

但第五个点时间超限了。

第二，我们也可以在累加时进行赋值。

第四个点也时间超限了。

第三，我们可以使用前缀和，用后一个位置减去前一个位置得到答案，终于对了。

~~代码太丑，就不贴了。~~

---

## 作者：ZBAA_MKC (赞：4)

这题不难，但如果暴力枚举的话在如此巨大的数据下是必然 TLE 的，所以我们要进行**前缀和优化**。

前缀和指的是一个数组中在区间 $[1,r]$ 的所有元素的和，但在此题中我们要求的是区间 $[l,r]$ 中所有元素的和，该怎么办呢？

其实也很简单，只需要一行代码就能搞定：`ans = p[r] - p[l - 1];`

注意在前缀和预处理时要按照题目要求把字母转换为对应的数字。

前缀和时间复杂度：预处理 $O(n)$，单次查询 $O(1)$。

朴素算法时间复杂度：读入 $O(n)$，单次查询：最好 $O(1)$,最坏 $O(n)$。

由此可以看出前缀和在处理静态问题上的表现是很突出的，但对于要对数组频繁更新的问题，前缀和的总时间复杂度会退化到 $O(n^2)$，需要使用效率更高的动态算法，这里就不多赘述了。

说了这么多，下面贴代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

int p[100005]; 
int main()
{
    int n, t;
    cin >> n >> t;
    for (int i = 1; i <= n; i++)
    {
    	char c;
    	cin >> c; //输入
    	p[i] = p[i - 1] + (c - 'a' + 1); //前缀和预处理
	}
	int l, r;
	while (cin >> l >> r)
	{
		
		cout << p[r] - p[l - 1] << endl; //查询并输出
	}
	return 0;
}
```

---

## 作者：123hh2 (赞：3)

--->[传送门](https://www.luogu.com.cn/problem/CF1539B)

---
### 前言

比赛的时候旁边的 CG_HeavenHealer 一眼就看出来了用前缀和，我直接%%%，~~顺便用前缀和过了这道水题~~

---

### 题目大意

给定一个全由小写字母构成的序列 $s(1 \le s \le 10^5)$，然后给定询问 $q(1 \le q \le 10^5)$ 次，对于每一次询问，给定两个数 $l$ $r$，要我们求出 $l$ 到 $r$ 的 **值**

值的定义为该询问区间的每一个字母的 ASCII 值减去 'a' 的 ASCII 值加 1 之和

---

### 思路

询问的是一堆区间，还是连续的区间的和，所以就用前缀和处理一遍原序列，然后 $O(1)$ 处理询问就好啦

---

### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
#define in inline
#define ri register
#define _123hh2 0
using namespace std;
in int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch>'9'||ch<'0') {if(ch=='-') f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') {x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
    return x*f;
}
in void write(int x)
{
    if(x<0) {x=-x;putchar('-');}
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
const int maxn=1e5+1;
int qzh[maxn];
signed main()
{
	cin.tie(NULL);
	cout.tie(NULL);
	int n=read(),q=read();
	string a;
	cin>>a;
	for(int i=1;i<=n;i++)//前缀和处理序列
	{
		qzh[i]=a[i-1]-'a'+1;
		qzh[i]+=qzh[i-1];
	}
	while(q--)//O(1)出答案
	{
		int ans=0;
		int x=read(),y=read();
		cout<<qzh[y]-qzh[x-1]<<endl;
	}
    return _123hh2;
}
```


---

## 作者：Harry_Hedwig (赞：2)

# 0x00 思路
先看题。
>给你一个长为 $n$ 的字符串和 $q$ 个区间 $[l,r]$ 。一个字符的**值定义为其在字母表中的序号**。对于每个区间，**输出这个区间字符的值的总和**。$1 \le n,t \le 100000,1 \le l \le r \le n$，保证字符串中都是**小写字母**。

暴力加一定会爆，算了，加优化吧。

那么怎么优化呢？由于我们所算的是某一个区间，那么我们只需要用以此区间 $r$ 为终点，以第 $1$ 个为起点的和减去以第 $l-1$ 个为终点，以第 $1$ 个为起点的和，剩下的就是区间 $[l,r]$ 的和了。上述操作初始化了 $[1,n]$ 的和，此方法结省了时间，叫作“**前缀和**”，这就是解题的关键。

那么这怎么办？
>一个字符的值定义为其在字母表中的序号。

很明显，由此字符减去 ' a ' 字符再加 $1$ 后值便得出了。（具体可见[ASCII码](https://baike.baidu.com/item/ASCII/309296?fromtitle=ascii%E7%A0%81&fromid=99077&fr=aladdin&ivk_sa=1024630g)。）

由于$n\le100000$，每一个字符值最大为 $26$，所以最大值为 $26000000$，小于 ```int``` 的最大值，因此可以放心大胆地用。
# 0x01 实现
```cpp
#include<bits/stdc++.h>
using namespace std;
char a[100005];
int main()
{
	int sum[100005]={},n,q,i,l,r;
	scanf("%d %d\n",&n,&q);∥过滤换行符！
	for(i=1;i<=n;i++)
	{
		scanf("%c",&a[i]);
		sum[i]=sum[i-1]+a[i]-'a'+1;//前已提过。
	}
	for(i=0;i<q;i++)
	{
		scanf("%d %d",&l,&r);
		printf("%d\n",sum[r]-sum[l-1]);
	}
	return 0;
} 
```

---

## 作者：sid_shi1 (赞：1)

题目：[CF1539B Love Song](https://www.luogu.com.cn/problem/CF1539B)

思路：

将原字符串每个元素转换成所代表的数字（如 $A$ 代表 $1$ ， $B$ 代表 $2$ )，并求出转换后的前缀和，否则用暴力会超时。

然后每次求 $x$ 和 $y$ 之间的和，就按照求前缀和区间的和的输出就行了。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,q,a[100001]={0},sum[100001]={0};
int main(){
	string s;
	cin>>n>>q>>s;
	for(int i=1;i<=n;i++) a[i]=s[i-1]-'a'+1,sum[i]=sum[i-1]+a[i];//转换并求前缀和
	for(int i=1;i<=q;i++){
		int x,y;
		cin>>x>>y;
		cout<<sum[y]-sum[x-1]<<endl;//输出x和y之间的和
	}
	return 0;
}
```


---

## 作者：xin700 (赞：0)

### 前缀和练手题

我们首先解决**字母取值**的问题，我们知道一个字母的ACSII码值并不与其字母顺序相匹配。

所以，对于每一个字母，其值就为 `s[i] - 'a' + 1`

这样我们就解决了取值的问题。

然后就是查询。

这就需要**前缀和优化**。

用 `he[i] = he[i-1] + (s[i] - 'a' + 1)` 实现。

之后我们就可以轻松写出代码。

```cpp
#include<bits/stdc++.h>
using std::cout; using std::endl;
#define debug cout<<"debug"<<endl;
namespace xin_io
{
	#define gec() p1 == p2 and (p2 = (p1 = buf) + fread(buf,1,1<<20,stdin),p1 == p2) ? EOF : *p1++
	#define gc() getchar()
	#define scanf eat1 = scanf
	#define freopen eat2 = freopen
	int eat1; FILE *eat2;
	inline void openfile() {freopen("t.txt","r",stdin);} inline void outfile() {freopen("o.txt","w",stdout);}
	char buf[1<<20],*p1 = buf,*p2 = buf;
	template<class type>inline type get()
	{
		type s = 0,f = 1; register char ch = gc();
		while(!isdigit(ch)) {if(ch == '-') f = -1; ch = gc();}
		while(isdigit(ch))  {s = s * 10 + ch - '0'; ch = gc();}
		return s * f;
	}
}
using namespace xin_io; static const int maxn = 1e6+10,maxb = 110,inf = 0x7f7f7f7f;
#define try(i,a,b) for(register signed i=a;i<=b;++i)
namespace xin
{
	int n,m,he[maxn];
	char s[maxn];
	inline short main()
	{
	#ifndef ONLINE_JUDGE
		openfile();
	#endif
		n = get<signed>(); m = get<signed>();
		scanf("%s",s+1);
		for(register int i=1;s[i];++i)
			he[i] = (s[i] - 'a' + 1) + he[i - 1];
		try(i,1,m)
		{
			register int l = get<signed>(),r = get<signed>();
			printf("%d\n",he[r] - he[l-1]);
		}
		return 0;
	}
}
signed main() {return xin::main();}
```

---

## 作者：张语诚ZYC (赞：0)

## 思路分析

先说一个朴素的想法，就是暴力，但是 ${(1 \times 10^{6})}^{2}$ 的数据规模不是吃素的（测评机的速度大概是 $1 \times 10^{8}$），所以只能另寻它法。~~WA、TLE，血的教训教会我们不用暴力。~~

由于只求区间和，所以可以使用这么一个方法，每次读入时计入这个字母和它之前所有字母的和，边读边处理，输出区间和时，用结尾的减开头的。

~~这里要提醒一下：这道题中，字母的值是它在字母表中的顺序，不是 ASCLL 值。~~

## $\texttt{AC Code}$
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=114514;
int data[MAXN];
inline int read_int() {
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {
		if(ch=='-') {
			w=-1;
		}
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		s=s*10+ch-'0';
		ch=getchar();
	}
	return s*w;
}
inline int read_char() {
	char ch=getchar();
	while(ch<'a'||ch>'z') {
		ch=getchar();
	}
	return ch-'a'+1;
}
int main() {
	int n=read_int();
	int q=read_int();
	for(int i=1;i<=n;i+=1){
		data[i]=data[i-1]+read_char();
	}
	for(int i=1;i<=q;i+=1){
		int l=read_int();
		int r=read_int();
		printf("%i \n",data[r]-data[l-1]);
	}
	return 0;
}
```


---

## 作者：Leo2020 (赞：0)

看见这有区间的题，就应该想到用前缀和预处理。
```
#include<bits/stdc++.h>
using namespace std;
int n,m,num[1000015];//定义n，m，前缀和数组 
string t;
int main(){
	cin >> n >> m >> t;
	for(int i=1;i<=t.size();i++)num[i]=num[i-1]+t[i-1]-'a'+1;//这里是前缀和预处理，当前的那一个等于上一个加上这一个字符串的和 
	for(int i=1;i<=m;i++){
		int x,y;//定义区间 
		cin >> x >> y;
		cout << num[y]-num[x-1] << endl;//从y到x都是区间的和，所以要写成-num[x-1] 
	}
	return 0;
}
```

---

## 作者：Eason_AC (赞：0)

## Content
有一个长度为 $n$ 的字符串，仅由小写英文字母组成。假设字母 $c$ 在字母表中排在第 $x_c$ 个。现在有 $q$ 组询问，每组询问给定 $l,r$，求 $\sum\limits_{i=l}^rx_{s_i}$。

**数据范围：$1\leqslant n,q\leqslant 10^5$。**
## Solution
这 Div.2B 还比 Div.2A 水就离谱![fd](https://cdn.luogu.com.cn/upload/pic/62250.png)

我们不妨用前缀和先处理一下 $sum_i=\sum\limits_{j=1}^ix_{s_j}$，然后询问的时候就可以直接 $\mathcal{O}(1)$ 得到结果了。像这种给定一个区间求区间某个什么权值加起来的和这种题目，一般都可用前缀和优化复杂度。
## Code
```cpp
string index = "abcdefghijklmnopqrstuvwxyz";
map<char, int> times;	//用 map 方便映射
int sum[100007];

int main() {
	int n = Rint, q = Rint;
	string s; cin >> s;
	F(int, i, 0, 25) times[index[i]] = i + 1;
	F(int, i, 1, n) sum[i] = sum[i - 1] + times[s[i - 1]];
	while(q--) {
		int l = Rint, r = Rint;
		println(sum[r] - sum[l - 1]);
	}
	return 0;
}
```

---

