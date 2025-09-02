# Maxim and Biology

## 题目描述

Today in the scientific lyceum of the Kingdom of Kremland, there was a biology lesson. The topic of the lesson was the genomes. Let's call the genome the string "ACTG".

Maxim was very boring to sit in class, so the teacher came up with a task for him: on a given string $ s $ consisting of uppercase letters and length of at least $ 4 $ , you need to find the minimum number of operations that you need to apply, so that the genome appears in it as a substring. For one operation, you can replace any letter in the string $ s $ with the next or previous in the alphabet. For example, for the letter "D" the previous one will be "C", and the next — "E". In this problem, we assume that for the letter "A", the previous one will be the letter "Z", and the next one will be "B", and for the letter "Z", the previous one is the letter "Y", and the next one is the letter "A".

Help Maxim solve the problem that the teacher gave him.

A string $ a $ is a substring of a string $ b $ if $ a $ can be obtained from $ b $ by deletion of several (possibly, zero or all) characters from the beginning and several (possibly, zero or all) characters from the end.

## 说明/提示

In the first example, you should replace the letter "Z" with "A" for one operation, the letter "H" — with the letter "G" for one operation. You will get the string "ACTG", in which the genome is present as a substring.

In the second example, we replace the letter "A" with "C" for two operations, the letter "D" — with the letter "A" for three operations. You will get the string "ZACTG", in which there is a genome.

## 样例 #1

### 输入

```
4
ZCTH
```

### 输出

```
2```

## 样例 #2

### 输入

```
5
ZDATG
```

### 输出

```
5```

## 样例 #3

### 输入

```
6
AFBAKC
```

### 输出

```
16```

# 题解

## 作者：chenyuchenghsefz (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/CF1151A)

题意：

输入一个只包含大写字母的字符串。每修改一次就是将某一个字符 $+1$ 或 $-1$，例如 $Z+1\to A$，$A+1\to B$，$A-1\to Z$。求至少修改多少次可以使 $\texttt{ACTG}$ 是原串的子串。

其中 $4\le\left|S\right|\le50$。

------------
直接暴力算，把原来的字符和目标字符做差，做绝对值，然后再算出 $26-x$ 和 $x$ 哪个小，再加起来。最后把所有的结果求最小值。
```cpp
t+=min(abs(26-abs(s1[j-i]-s[j])),abs(s1[j-i]-s[j]));//s1="ACTG"
```
[AC 记录](https://www.luogu.com.cn/record/103384625)
# 上代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
	int n,m=1000;
	string s,s1="ACTG";
	cin>>n;
	cin>>s;
	for(int i=0;i<n-3;i++)
	{
		int t=0;
		for(int j=i;j<=i+3;j++)
		t+=min(abs(26-abs(s1[j-i]-s[j])),abs(s1[j-i]-s[j]));
		m=min(m,t);//求最小
	}
	cout<<m;
	return 0;
}
```

---

## 作者：GusyNight (赞：2)

```
题意：
给定一个字符串，
输出字符串中连续的四位转换成“ACTG”的最小操作次数。

题解：
用string进行操作，
首先用string a,
存储题目中给出的字符串，
接着输入字符串，进行比较。

注意：
与a比较的时候，
a的下标应该是j-i；
```
```cpp
#include<bits/stdc++.h>
#define TP int
#define Max 100009
using namespace std;
string a="ACTG",num;
using namespace std;
inline TP read(){
    char c=getchar();
    TP x=0;
    bool f=0;
    while(!isdigit(c))f^=!(c^45),c=getchar();
    while(isdigit(c))x=(x<<1)+(x<<3)+(c^48),c=getchar();
    if(f)x=-x;return x;
}
int main(){
    int n,ans=3000,number;
    n=read();
    cin>>num; 
    for(int i=0;i<n&&i+3<n;++i){
        number=0;
        for(int j=i;j<i+4;++j){
            number+=min(26-abs(a[j-i]-num[j]),abs(num[j]-a[j-i]));
        }
        ans=min(ans,number);
    }
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：pandaSTT (赞：1)

## [题目传送门](https://www.luogu.com.cn/problem/CF1151A)


## 思路

要清楚这道题首先得请清楚字串的概念：

子串：串中任意个**连续字符组成**的子序列称为该串的子串。

所以说我们只需要在原串中判断每个长度为 $ n $ 的子串转换成 "ACTG" 的最小次数就行了，而转换成另一个字符的最小修改次数应该为ASCLL 码较大的字符 减去ASCLL 码较小的字符，或用ASCLL 码较小的字符加上26再减去ASCLL 码较大的字符。

## 代码

```cpp
  #include<bits/stdc++.h>
  using namespace std;
  string s;
  int len,ans=INT_MAX;
  int main(){
      cin>>len>>s;
      for(int i=0;i<len-3;i++){
          int a,b,c,d;//存储这四个字符要变成"ACTG"的修改次数
          if(s[i]>'A'){
              a=min(s[i]-'A','A'+26-s[i]);
          }
          else{
              a=min('A'-s[i],s[i]+26-'A');
          }
          if(s[i+1]>'C'){
              b=min(s[i+1]-'C','C'+26-s[i+1]);
          }
          else{
              b=min('C'-s[i+1],s[i+1]+26-'C');
          }
          if(s[i+2]>'T'){
              c=min(s[i+2]-'T','T'+26-s[i+2]);
          }
          else{
              c=min('T'-s[i+2],s[i+2]+26-'T');
          }
          if(s[i+3]>'G'){
              d=min(s[i+3]-'G','G'+26-s[i+3]);
          }
          else{
              d=min('G'-s[i+3],s[i+3]+26-'G');
          }
          ans=min(ans,a+b+c+d);
      }
      cout<<ans;
      return 0;
  }
```


---

## 作者：xh39 (赞：1)

算法:模拟,暴力。

重点是算出他们的差值(即要变化多少次)

```cpp
int cha(char a,char b){
	if(a<b) swap(a,b); //设a是大的。
	return min(a-b,b+26-a); //b+26-a是因为'a'的前面是'z',就要加26。
}
```

接着每4个相邻的枚举一次,看其差值之和,取其最小。

```cpp
#include<bits/stdc++.h>
using namespace std;
int cha(char a,char b){
	if(a<b) swap(a,b);
	return min(a-b,b+26-a);
}
int main(){
	int n,i,Min=999999999; //初始值极大。
	string s;
	cin>>n>>s;
	for(i=0;i<n-3;i++){ //字符串下标从0开始。
		Min=min(Min,cha(s[i],'A')+cha(s[i+1],'C')+cha(s[i+2],'T')+cha(s[i+3],'G'));
	}
	cout<<Min;
	return 0;
}
```


---

## 作者：xuhanxi_dada117 (赞：1)

[题目传送门&题目大意](https://www.luogu.com.cn/problem/CF1151A)

# 解法

考虑枚举长度为 $4$ 的字串：
 
对单个字母：$\ $ ```dis=min(abs('A'-p[0]),26-abs('A'-p[0])) //对第1个```

这里

最后：扫一遍算最小值即可。

时间复杂度 $\Theta(n)$ 可以通过。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
string s;int ans=999999999;
int main(){
    int n;cin>>n>>s;
    for(int i=0;i<n-3;++i){
        string p=s.substr(i,4);
        int t=min(abs('A'-p[0]),26-abs('A'-p[0]))+min(abs('C'-p[1]),26-abs('C'-p[1]))+min(abs('T'-p[2]),26-abs('T'-p[2]))+min(abs('G'-p[3]),26-abs('G'-p[3]));
        ans=min(ans,t);
    }cout<<ans;
    return 0;
}
```

[$\color{Green}Accept!$](https://www.luogu.com.cn/record/103408454)


---

## 作者：OoXiao_QioO (赞：0)

# 前置知识

- 子串是字符串中任意个**连续字符**组成的子序列，而不是任意字符串中的几个字符。

# 思路

根据子串的定义，我们可以用循环变量 $i$ 来遍历字符串前 $n - 3$ 个字符，再来找出 $i,i+1,i+2,i+3$ 这几个字符分别与 $\verb!A,C,T,G!$ 的距离（应该可以这么称呼）。令 $\verb!c = s[i],c1 = s[i+1],c2 = s[i+2],c3 = s[i+3]!$，当前距离目标字符串的距离 $\verb!cnt!$ 就等于 $\verb!f(c,`A')+f(c1,`C')+f(c2,`T')+f(c3,`G')!$。其中 $\verb!f(a,b)!$表示字符变量 $a$ 到字符常量 $b$ 的距离，注意字符常量 $b$ 需要加引号，因为是一个字符，而不是变量，代码也会有所解释。再来比较 $\verb!cnt!$ 和找到的最小距离 $\verb!min!$，并做出是否替换的决定，最后输出一下 $\verb!min!$，此题就可以完成了。
# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int f(char a,char b) 
{
	//这个函数的意义是用来找出 a 与目标字符 b 在字母表（循环）中的距离。 
	int x = abs(a-b);//这里模拟的是不断 +1 的过程，注意要加 abs()取绝对值，不然就会减出负数。 
	int y = 26-abs(a-b);// 这里模拟的是不断 -1 的过程，因为这是 +1 的逆运算，所以注意最后要用 26 来减去，得出不断 -1 的答案。 
	return min(x,y);//返回最小值。 
}
int main()
{
	//定义
	 
	int i,cnt,mi = INT_MAX,l;//mi 表示最短距离，初值一个非常大的数。 
	char s[51];
	char c,c1,c2,c3;
	
	//输入
	 
	scanf("%d %s",&l,s);
	
	//处理，注意 i 只需跑到 l-3 就好了，不然就会越界。 
	for(i=0;i<l-3;i++)
	{
		c = s[i];
		c1 = s[i+1];
		c2 = s[i+2];
		c3 = s[i+3]; 
		cnt = f(c,'A')+f(c1,'C')+f(c2,'T')+f(c3,'G');//找出当前距离
		mi = min(mi,cnt);//比较两者大小 
	}
	cout<<mi<<endl;//输出 
	return 0;
}
```


---

## 作者：Erusel (赞：0)

因为字符串长度最多只有50

所以对于每一段长度为4的子串进行扫描

求出当前扫描到的子串转化成“ACTG”需要的步数

注意：转化时既可以+1，也可以-1

代码：

```
#include<bits/stdc++.h>

#define rd(x) x=read()

using namespace std;

int n;
string s;
int ans=100000;

inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}

inline void write(int x)
{
    if(x<0){putchar('-');x=-x;}
    if(x>=10)write(x/10);
    putchar(x%10+'0');
}

int calc(char c1,char c2){return min(abs(c1-c2),26-abs(c1-c2));}//计算转化步数

int main()
{
	rd(n);cin>>s;
	for(int i=0;i<=n-4;i++)
	{
		int sum=0;
		sum+=calc(s[i],'A')+calc(s[i+1],'C')+calc(s[i+2],'T')+calc(s[i+3],'G'); 
		ans=min(ans,sum);//求出最小的答案
	}
	cout<<ans<<endl;

    return 0;
}
```

---

## 作者：djh123 (赞：0)


直接枚举是哪四个字符变成``ACTG``，要注意$A,Z$的转化。

```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <bitset>
#include <set>
#include <map>
#include <queue>
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

typedef long long LL;
typedef unsigned long long ULL;
typedef unsigned int uint;
typedef double db;
typedef pair <int, int> pii;
typedef vector <int> vi;

#ifndef ONLINE_JUDGE
#define DEBUG
#endif

#define Fi first
#define Se second
#define pb push_back
#define mp make_pair
#define rep(x, a, b) for(int x = (a); x <= (b); ++ x)
#define per(x, a, b) for(int x = (a); x >= (b); -- x)
#define rop(x, a, b) for(int x = (a); x < (b); ++ x)
#define por(x, a, b) for(int x = (a); x > (b); -- x)
#define forE(x, a) for(int x = head[a]; x; x = nxt[x])

#ifdef DEBUG
#define debug(x) cerr << #x << ": " << x << '\n'
#else
#define debug(x)
#endif

void open(const char *s){
	#ifdef DEBUG
    char str[100];
	sprintf(str,"%s.in",s);
	freopen(str,"r",stdin);
	sprintf(str,"%s.my",s);
	freopen(str,"w",stdout);
	#endif
}

const db eps = 1e-8;
const int inf = 0x3f3f3f3f;
const int Minf = 0x7f7f7f7f;
const LL INF = 0x3f3f3f3f3f3f3f3fll;
const LL MINF = 0x7f7f7f7f7f7f7f7fll;

const int N = 1e5 + 50;

int n;
char s[N];
char t[N] = "ACTG";

int main() {
	scanf("%d", &n);
	scanf("%s", s + 1);
	int ans = inf;
	rep(i, 1, n - 3) {
		int tmp = 0;
		rep(j, 0, 3) {
			tmp += min({abs(s[i + j] - t[j]), 'Z' - t[j] + 1 + s[i + j] - 'A', 'Z' - s[i + j] + 1 + t[j] - 'A'});
		}
		ans = min(ans, tmp);
	}
	printf("%d\n", ans);
}
```

---

