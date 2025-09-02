# All the Vowels Please

## 题目描述

Tom loves vowels, and he likes long words with many vowels. His favorite words are vowelly words. We say a word of length $ k $ is vowelly if there are positive integers $ n $ and $ m $ such that $ n\cdot m = k $ and when the word is written by using $ n $ rows and $ m $ columns (the first row is filled first, then the second and so on, with each row filled from left to right), every vowel of the English alphabet appears at least once in every row and every column.

You are given an integer $ k $ and you must either print a vowelly word of length $ k $ or print $ -1 $ if no such word exists.

In this problem the vowels of the English alphabet are 'a', 'e', 'i', 'o' ,'u'.

## 说明/提示

In the second example, the word "agoeuioaeiruuimaeoieauoweouoiaouimae" can be arranged into the following $ 6 \times 6 $ grid:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1166B/7d474325157104f047038dc9401e0f23cf51cf99.png)It is easy to verify that every row and every column contain all the vowels.

## 样例 #1

### 输入

```
7
```

### 输出

```
-1
```

## 样例 #2

### 输入

```
36
```

### 输出

```
agoeuioaeiruuimaeoieauoweouoiaouimae```

# 题解

## 作者：世末OIer (赞：3)

水题啊

找规律即可。

我们可以把它错开来：

aeiouae...

eiouaei...

iouaeio...

ouaeiou...

uaeioua...

aeiouae...

若 string s="aeiou"

则 c[i][j]=s[(i+j)%5]

```cpp

#include<bits/stdc++.h>
#pragma GCC diagnostic error "-std=c++11"
#define ll long long
#define mp make_pair
using namespace std;
string s="aeiou";
inline void fill(int x,int y){
	int i,j;
	for(i=0;i<x;++i) for(j=0;j<y;++j)
		cout<<s[(i+j)%5];
}
int main(){
	int i,j;
	int k;
	cin>>k;
	if(k<25){
		cout<<-1<<endl;
		return 0;
	}
	for(int i=5;i*i<=k;++i){
		if(k%i==0 and k/i>=5){
			fill(i,k/i);
			return 0;
		}
	}
	cout<<-1<<endl;
	return 0;
}

```

---

## 作者：yhx0322 (赞：0)

## Description
找到恰好有 $k$ 个格子的矩阵，满足：每一行每一列都包含了所有的元音字母。

如果不能找到，输出 $-1$。

$1 \le k \le 10 ^ 4$。

## Solution
可以推导，找出规律。

首先，特判。
- 当 $k < 5$ 时，一定不能满足，因为每一行每一列至少需要 $5$ 个字符。
- 当 $n$ 个字符无法构成 $5 \times 5$ 的矩阵时，不满足。

剩下的情况，经过分析可知：

**答案就是循环出现的元音字母。**

根据这一规律，即可写出代码。

## Code
```cpp
#include <bits/stdc++.h>

using namespace std;

int n;
string s = "aeiou";

bool isprime(int x) {
	for (int i = 5; i <= sqrt(x); i ++) {
		if (x % i == 0) return true;
	}
	return false;
}

int main () {
	scanf("%d", &n);
	if (n < 25 || !isprime(n)) {
		printf("-1");
		return 0;
	}

	if (n % 5 != 0) { 
		for (int i = 0; i < n; i ++) {
			printf("%c", s[i % 5]);
		}
	} else {
		int k = n / 5, t = 0;
		for (int i = 0; i < k; i ++) {
			for (int j = 0; j < 5; j ++) {
				printf("%c", s[(t++) % 5]);
			}
			t++;
		}
	}
	return 0;
}

```

---

## 作者：封禁用户 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1166B)

[CF链接](https://codeforces.com/problemset/problem/1166/B)
## 思路
不难发现，在矩阵大小不足 $25$ 时，或者矩阵字符数量无法凑出边长为 $5$ 的正方形矩阵时，无法边长为 $5$ 的字符矩阵，这时候直接输出 $-1$ 即可。


剩下的情况找规律即可。

举个例子：
```
a e i o u * ……
* a e i o u ……
u * a e i o ……
o u * a e i ……
i o u * a e ……
e i o u * a ……
…… …… …… ……
```
将空缺的字符按元音字母顺序填入后可以得到一组解法： 
```
a e i o u a ……
e a e i o u ……
u i a e i o ……
o u o a e i ……
i o u u a e ……
e i o u a a ……
…… …… …… ……
```
可以发现，答案就是循环出现元音字母。

**注意**：
- 换行
- 字符之间的空格

**切记！否则答案就变成了如下所示：**
```
aeiouaeiouaeiou……
```
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
char s[] ="aeiou";
bool p(int n){//判断函数
	for(int i=5;i*i<=n;i++)
		if(n%i==0) return false;
	return true;
}
int main(){
	cin >> n;
	if(n<25||p(n)==true){
		cout<<-1<<endl;
		exit(0);
	}//特判
	if(n%5)
		for(int i=0;i<n;i++) cout<<s[i%5];//正常输出
	else{
		int q=n/5,t=0;
		for(int i=0;i<q;i++){
			for(int j=0;j<5;j++){
				cout<<s[t%5];
				t++;
			}
			t++;
		}//细节输出
	}
	return 0;//结束啦
}
```

---

## 作者：linbaicheng2022 (赞：0)

## All the Vowels Please 题解

[题目传送门](https://www.luogu.com.cn/problem/CF1166B)

## 思路

### Step 1：

乍一看似乎发不现规律，但是可以先想到两种特判的情况：

+ $n < 25$，根本无法达到每行每列都有 $5$ 个字符，直接输出 $-1$；

+ 用 $n$ 个字符无法凑出每行每列都至少有 $5$ 个字符的矩阵，同理。

### Step 2：

先画图找一找规律，例如 $n = 30$：

```cpp
a e i o u 0
0 a e i o u
u 0 a e i o
o u 0 a e i
i o u 0 a e
```

其中 $0$ 为暂时不确定的字符，然后我们把它填出来，找到一组解为：

```cpp
a e i o u a
e a e i o u
u i a e i o
o u o a e i
i o u u a e
```

如果我们要输出这个矩阵的话，就会变成这样：

`aeiouaeiouaeiouaeiouaeiouaeiou`

然后我们发现，其实答案就是不停输出 $aeiou$。。。

但是还要注意一个点，比如一个 $5 \times 5$ 的矩阵，如果我们循环输出五遍元音，矩阵的每一列都会变成同样的字符。

也就是说，这个算法不能对五的倍数自动换行，而实际上的答案是：

```cpp
a e i o u
e i o u a 
i o u a e
o u a e i
u a e i o 
```

所以我们每次输出完一行，都要跳过一个字符。

## 代码

```cpp
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

int n;
char a[5] = {'a', 'e', 'i', 'o', 'u'};

int check (int x) { //判断是否能凑出每行每列都至少有 5 个字符的矩阵
	for (int i = 5; i * i <= x; i ++) {
		if (x % i == 0) {
			return 1;
		}
	}
	return 0;
}

int main () {
	cin >> n;
	if (n < 25 || !check (n)) {
		cout << -1 << endl;
		return 0;
	} //特判 -1

	if (n % 5 != 0) { //如果不是 5 的倍数，就正常输出
		for (int i = 0; i < n; i ++) {
			cout << a[i % 5];
		}
	} else { //否则每行跳过一个字符
		int k = n / 5, t = 0;
                //k 指行数，t 指当前用到了元音中的第 t 个字符
		for (int i = 0; i < k; i ++) {
			for (int j = 0; j < 5; j ++) {
				cout << a[t ++ % 5];
			}
			t ++; //输出完这一行，将 t 加一
		}
	}
	return 0; //完结撒花
}
```

---

## 作者：T21C06 (赞：0)

## 思路


这道题 $k$ 虽然很大，但我们可以把它“缩小”成一个 $5 \times 5$ 的矩阵，也就是把每个元音都错开来，如下图所示：
![](https://cdn.luogu.com.cn/upload/image_hosting/5zns0qw9.png)

可以发现每行每列都满足题目要求，但数据不可能只是 $5 \times 5$ 的，如果是样例二的 $6 \times 6$ 的矩阵呢？我们只需要增加一行和一列。由此我们可以发现规律：

![](https://cdn.luogu.com.cn/upload/image_hosting/8edp6alq.png)

每一列按照 $5 \times 5$ 矩阵的 $5$ 列循环；每一行按照 $5 \times 5$ 矩阵的 $5$ 行循环。

也就是说如果把 $5 \times 5$ 矩阵的每一行看做一个字符串，$N \times N$ 矩阵的第 $i$ 行就是 $5 \times 5$ 矩阵的 
 $(i-1)\bmod 5+1$ 行循环。						

然后就可以愉快地打代码啦！

## AC 代码

```cpp
#include<bits/stdc++.h>
#include<string>
using namespace std;
int n;
string st[10];
void Out(int x,int y){ //注意是 void 类型 
	int tx=0,ty=-1;
	for(int i=1;i<=x;i++){
		tx++;
		if(tx==6) tx=1;//行循环（超出 5 行归 1） 
		ty=-1; //记得初始化！！！ 
		for(int j=1;j<=y;j++){
			ty++;
			if(ty==5) ty=0;//列循环（超出 4 列归 0，因为字符串从 0 开始） 
			cout<<st[tx][ty];
		}
	}
}
int main(){
	cin>>n;
	//5*5小矩阵 
	st[1]="aeiou";
	st[2]="eioua";
	st[3]="iouae";
	st[4]="ouaei";
	st[5]="uaeio";
	//从 5 开始（有 5 个元音） 
	for(int i=5;i<=n;i++){
		//除得下并且列大于 5（有 5 个元音）
		if(n%i==0&&n/i>=5){
			Out(i,n/i);
			return 0;
		}
	}
	//如果 if 一次也没走进去，就说明没有满足题意的矩阵 
	cout<<"-1";
	return 0;
} 
```

## 其他

- 本人才疏学浅，如有错误欢迎指出。
- 祝看了这篇题解的人本题 AC！

---

## 作者：xiaofeng_and_xiaoyu (赞：0)

分几个步骤判断此题。

步骤一：

这道题有一个特点：$5$ 个元音在每行每列中不能不出现。

所以说，最小的矩阵为 $5\times5=25$。

第一个步骤完毕。

```cpp
if(s<25){
		cout<<-1;
		return 0;
	}
```
步骤二：

同步骤一的分析，他必须有两个比 $5$ 大的因数，做函数制造。

```cpp
bool BGT5(int s){//bigger than 5的简称 
	for(int i=5;i<=sqrt(s);i++){//大于等于五 
		if(s%i==0){
			return 1;
		}
	}
	return 0;
}
```


步骤三：

很明显矩阵中要叉开所有元音，所以先把元音存储一下。

画个矩阵寻找规律，先岔开一列（$\verb!x!$ 为不确定）：

| a | e | i | o | u | x |
| -----------: | -----------: | -----------: | -----------: | -----------: | -----------: |
| x | a | e | i | o | u |
| u | x | a | e | i | o |
| o | u | x | a | e | i |
| i | o | u | x | a | e | 

第一列少了个 $\verb!e!$，把第二行的 $\verb!e!$ 往前移，变成了

| a | e | i | o | u | a |
| -----------: | -----------: | -----------: | -----------: | -----------: | -----------: |
| e | i | o | u | x | x |
| u | x | a | e | i | o |
| o | u | x | a | e | i |
| i | o | u | x | a | e | 

接着发现，第二行少一个 $\verb!a!$，而第二行前面已经固定，把第三行移上去。

| a | e | i | o | u | a |
| -----------: | -----------: | -----------: | -----------: | -----------: | -----------: |
| e | i | o | u | a | e |
| i | o | u | x | x | x |
| o | u | x | a | e | i |
| i | o | u | x | a | e | 

然后按照上面的规律，移动第四行：

| a | e | i | o | u | a |
| -----------: | -----------: | -----------: | -----------: | -----------: | -----------: |
| e | i | o | u | a | e |
| i | o | u | a | e | i |
| o | u | x | x | x | x |
| i | o | u | x | a | e | 

第五行的前两个字母也固定了：

| a | e | i | o | u | a |
| -----------: | -----------: | -----------: | -----------: | -----------: | -----------: |
| e | i | o | u | a | e |
| i | o | u | a | e | i |
| o | u | x | x | x | x |
| u | a | x | x | x | x | 
然后可以发现，缺的字母正好对应一、二行的前四列。

直接复制过来。

| a | e | i | o | u | a |
| -----------: | -----------: | -----------: | -----------: | -----------: | -----------: |
| e | i | o | u | a | e |
| i | o | u | a | e | i |
| o | u | a | e | i | o | 
| u | a | e | i | o | u |

最后输出就可以了。

但是每一个都要向上面这样操作的话，先不说会不会爆，反正实现很难（至少对我而言）。

不过有更简单的规律：输出后发现每个正好是 $\verb!aeiou!$ 的顺序。

也就是说，按照 $\verb!aeiou!$ 的顺序输出，就可以了。

```cpp
if(BGT5(s)&&s%5!=0){
		for(int i=0;i<s;i++){
			cout<<a[i%5];
		}
	}
```
步骤四：
可以发现上面加了个对 $5$ 特判，为什么呢？

还是造数据寻找规律：

按照上面的代码，打个 $25$，输出的是

| a | e | i | o | u |
| -----------: | -----------: | -----------: | -----------: | -----------: |
| a | e | i | o | u |
| a | e | i | o | u |
| a | e | i | o | u | 
| a | e | i | o | u |

原来，当他为 $5$ 的倍数时，他无法进行自动岔行。

这种情况只需要加一个手动岔行就可以了。
```cpp
else if(BGT5(s)&&s%5==0){
		int k=s/5,t=0;
		for(int i=0;i<k;i++){
			for(int j=0;j<5;j++){
				cout<<a[t%5];
				t++;
			}
			t+=1;
		} 
	}
```
代码已经以片段形式给出，不再重新汇总。

---

## 作者：Buried_Dream (赞：0)

一道很水的构造题。



一开始我们先构造一个 $5 \times 5$ 的合法矩阵。

这个合法矩阵自己用手画出来然后打表就行了。

然后

![](https://cdn.luogu.com.cn/upload/image_hosting/u63l90vo.png)

在蓝色部分全部构造 `a e i o u ` 即可。

这样就可以保证每行每列都合法了。

无解的情况就是无法构造出一个长为 $n$，宽为 $m$ 的矩阵，满足 $n \ge 5, m\ge5$。

```cpp
/**
 *	author: TLE_Automation
 *	creater: 2022.11.12
 **/
#include<map>
#include<cmath>
#include<queue>
#include<cstdio>
#include<vector>
#include<bitset>
#include<cstring>
#include<iostream>
#include<algorithm>
#define gc getchar
using namespace std;
typedef long long ll;
const int N = 1e6 + 10;
const int mod = 998244353;
const ll inf = 0x3f3f3f3f3f3f3f3f;
#define debug cout << "i ak ioi" << "\n"
inline void print(int x) {if (x < 0) putchar('-'), x = -x; if(x > 9) print(x / 10); putchar(x % 10 + '0');}
inline char readchar() {static char buf[100000], *p1 = buf, *p2 = buf; return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1++;}
inline int read() { int res = 0, f = 0; char ch = gc();for (; !isdigit(ch); ch = gc()) f |= (ch == '-'); for (; isdigit(ch); ch = gc()) res = (res << 1) + (res << 3) + (ch ^ '0'); return f ? -res : res;}

bool is_Prime(int x) {
	for(int i = 2; i * i <= x; i++) 
		if(x % i == 0) return false;
	return true;
}

int a[2000][2000] = {{0, 0, 0, 0, 0, 0}, {0, 1, 2, 3, 4, 5}, {0, 4, 3, 2, 5, 1}, {0, 5, 4, 1, 2, 3}, {0, 3, 5, 4, 1, 2}, {0, 2, 1, 5, 3, 4}};

map <int, char> mp;

signed main()
{
	mp[1] = 'a', mp[2] = 'e', mp[3] = 'i', mp[4] = 'o', mp[5] = 'u';
	int k = read(); 
	if(is_Prime(k)) return puts("-1"), 0;
	for(int qwq = 5; ; qwq++) {
		if(qwq > k) return puts("-1"), 0;
		if(k % qwq == 0 && k / qwq >= 5) {
			int n = qwq, m = k / qwq;
			for(int j = 6; j <= m; j++) {
				for(int i = 1; i <= 5; i++) a[i][j] = i;
			}
			for(int i = 6; i <= n; i++) {
				for(int j = 1; j <= 5; j++) a[i][j] = j;
			}
			for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) if(!a[i][j]) a[i][j] = 1;
			for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) cout << mp[a[i][j]]; 
			return 0;
		}
	}
	puts("-1");
	return (0 - 0);
}

```

---

## 作者：皇家海盗 (赞：0)

一道不算太水的水题

用画图画的，丑，体谅一下。。。

如图，这是个8×6的栗子，5种彩色块对应5种元音字母，灰色区域可以随便乱填字母，这种方法就可以实现题意。

![](https://cdn.luogu.com.cn/upload/pic/68143.png)

```cpp
#include<bits/stdc++.h>
#define aa 'a'
#define ee 'e'
#define ii 'i' 
#define oo 'o'
#define uu 'u'
using namespace std;
int k,h=-1,l=-1;			//h为列数，l为行数 
char chara[10001][10001]={0};
void cf()					//暴力求行数与列数，取行数小于列数 
{
	for(int i=1;i<=sqrt(k);i++)
	{
		if(k%i==0)
		{
			h=i;l=k/i;
		}
	}
	int hh=h,ll=l;
	h=max(hh,ll);l=min(hh,ll);
}
int pig(int f,int t)	//使任意正整数f与t取模后取1~t之间的值 
{
	if(f%t==0) return t;
	return f%t;
}
int main()
{
	srand((unsigned int) time(0));
	cin>>k;
	cf();
	if(h<5||l<5) return cout<<"-1",0;//如果行或列数不足5，则直接结束程序 
	for(int i=1;i<=l;i++)	//spj真好，行列不分也能过
	{
		for(int j=1;j<=h;j++)//精髓，枚举5种元音出现的位置 
		{
			if(i==pig(j,l)) chara[i][j]=aa;		
			if(i==pig(j+1,l)) chara[i][j]=ee;
			if(i==pig(j+2,l)) chara[i][j]=ii;
			if(i==pig(j+3,l)) chara[i][j]=oo;
			if(i==pig(j+4,l)) chara[i][j]=uu;
		}
	}
	for(int i=1;i<=l;i++)
	{
		for(int j=1;j<=h;j++)
		{
			if(!chara[i][j]) chara[i][j]=rand()%25+'a';//将随机字母填入未填元音的格子里，spj大法好 
			cout<<chara[i][j];
		}
	//	cout<<endl;						//这里害我WA了一次 
	}
}
```


---

## 作者：AC_Dolphin (赞：0)

有一点恶意评分吧

这道题主要还是在构造上，如果$k$可以分成$n*m$，且$n>=5,m>=5$（元音个数），那么这种情况肯定可以构造出一种符合题意的方格

那么如何构造呢？（下面方格原谅我不会$Markdown$）

a e i o u a

e i o u a e

i o u a e i

o u a e i o

u a e i o u

这是$n=6,m=5$的一种符合题意的情况（这里假设$n>=m$），构造方法就是每一行都与上一行错开填入，这对于任意的$n,m$都是可行的

然而，输出不需要换行，我们再看刚刚那个方格，输出就是:
$aeiouaeiou...aeiou$（几个$aeiou$），如果$k \%5!=0$，那么再多输出几个元音就可以了

于是$WA$了。

为什么呢？我们看对于$n=m=5$的方格，按上面的填法就是：

a e i o u

a e i o u

a e i o u

a e i o u

a e i o u

这不符合每一列都有不同元音的要求，因为当$n$是$5$的倍数的时候，不能错开填入字符，这时候我们需要特判，填法如下：

a e i o u

e i o u a

i o u a e

o u a e i

u a e i o

这样就满足要求了

$Code$:
```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
	int k;
	cin>>k;
	for(int i=1;i<=sqrt(k);i++){
		if(k%i!=0) continue;
		int j=k/i;
		if(i<5||j<5) continue;
		//cout<<i<<" "<<j<<endl;
		if(j%5){
			for(int s=1;s<=k/5;s++) cout<<"aeiou";
			switch(k%5){
				case 1:cout<<"a";break;
				case 2:cout<<"ae";break;
				case 3:cout<<"aei";break;
				case 4:cout<<"aeio";break;
			}
			return 0;
		}
		else{
			int m=j/5;
			for(int s=1;s<=i/5;s++){
				for(int l=1;l<=m;l++) cout<<"aeiou";
				for(int l=1;l<=m;l++) cout<<"eioua";
				for(int l=1;l<=m;l++) cout<<"iouae";
				for(int l=1;l<=m;l++) cout<<"ouaei";
				for(int l=1;l<=m;l++) cout<<"uaeio";
			}
			switch(j%5){
				case 1:for(int l=1;l<=m;l++) cout<<"aeiou";break;
				case 2:{
				for(int l=1;l<=m;l++) cout<<"aeiou";
				for(int l=1;l<=m;l++) cout<<"eioua";
					break;
				}
				case 3:{
					for(int l=1;l<=m;l++) cout<<"aeiou";
					for(int l=1;l<=m;l++) cout<<"eioua";
					for(int l=1;l<=m;l++) cout<<"iouae";
					break;
				}
				case 4:{
					for(int l=1;l<=m;l++) cout<<"aeiou";
					for(int l=1;l<=m;l++) cout<<"eioua";
					for(int l=1;l<=m;l++) cout<<"iouae";
					for(int l=1;l<=m;l++) cout<<"ouaei";
					break;
				}
			}
			return 0;
		}
	}
	cout<<-1<<endl;
	return 0;
}
```

---

