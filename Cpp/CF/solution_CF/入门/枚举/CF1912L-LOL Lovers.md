# LOL Lovers

## 题目描述

有 $n$ 个食物依次排成一行放在一张长桌上。每个食物要么是一个面包（用大写字母 'L' 表示，ASCII 码为 76），要么是一个洋葱（用大写字母 'O' 表示，ASCII 码为 79）。桌上至少有一个面包和至少一个洋葱。

你和你的朋友想要分这些食物：你将取这个序列的一个前缀（即最左边的若干个物品），你的朋友取剩下的部分。但有以下几个限制：

1. 每个人至少要有一个物品。
2. 你拥有的面包数量与朋友拥有的面包数量必须不同。
3. 你拥有的洋葱数量与朋友拥有的洋葱数量必须不同。

请找出任意一种满足条件的分法，并输出你拿的物品数量。如果无解，输出 $-1$。

## 说明/提示

在第一个样例中，无论如何分割，左边和右边部分都各有一个面包。

在第二个样例中，可以分成 'L' 和 'O'，这两部分中面包数不同（1 和 0），洋葱数也不同（0 和 1）。

在第三个样例中，1、2 或 3 都是正确答案。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
LOL```

### 输出

```
-1```

## 样例 #2

### 输入

```
2
LO```

### 输出

```
1```

## 样例 #3

### 输入

```
4
LLLO```

### 输出

```
1```

## 样例 #4

### 输入

```
4
OLOL```

### 输出

```
-1```

## 样例 #5

### 输入

```
10
LLOOOOLLLO```

### 输出

```
5```

# 题解

## 作者：xiaoshumiao (赞：3)

**注：笔者由于没有 CF 账号，于是在 Virtual Judge 上提交了此题并通过了。因此在洛谷没有 AC 记录。**

[题目传送门](https://www.luogu.com.cn/problem/CF1912L)

我们可以枚举左序列的右端点 $i$，每次统计 $\left[1,i\right]$ 和 $\left[i+1,n\right]$ 区间内的 `L` 和 `O` 个数，判断是否满足题意。时间复杂度为 $\Theta(n^2)$，通过前缀和优化可以使时间复杂度降为 $\Theta(n)$。下面给出前缀和优化版本的代码：
```cpp
#include<cstdio>
using namespace std;
const int MAXN=205;
char s[MAXN];
int a[MAXN],b[MAXN];
int main() {
  int n;
  scanf("%d",&n);
  getchar();
  scanf("%s",s+1);
  for(int i=1;i<=n;i++) {//预处理前缀和数组。
  	a[i]=a[i-1]+(s[i]=='L');
  	b[i]=b[i-1]+(s[i]=='O');
  }
  for(int i=1;i<n;i++)//枚举左序列的右端点 i。
  	if(a[i]!=a[n]-a[i]&&b[i]!=b[n]-b[i]) {//判断是否满足题目要求。
  	  printf("%d",i);
  	  return 0;
  	}
  printf("-1");//无解。
  return 0;
}
```

---

## 作者：_fallen_leaves_ (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1912L)

## 思路
我用了前缀和，把第一个到第 $i$ 个数中的 O 和 L 的数量统计出来，在遍历中找前面的 O 和 L 数量和后面 O 和 L 数量，如果两个都不一样就输出 $i$ 的值，否则到了最后就输出 -1，也就代表不行。

贴代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,l[205],o[205];
string s;
int main()
{
    cin>>n>>s;
    for(int i=0;i<s.size();i++)
    {
    	l[i]=l[i-1]; 
    	o[i]=o[i-1];
    	if(s[i]=='L') l[i]++;
		else o[i]++; 
	}//前缀和的思路
    for(int i=0;i<s.size()-1;i++)
    {
    	if((l[i]!=l[s.size()-1]-l[i])&&(o[i]!=o[s.size()-1]-o[i]))//如果满足条件 
		{
			cout<<i+1;//就输出 
			return 0;//因题目只要输出一种答案，所以直接return 0; 
		}
	}
	cout<<-1;//不行输出-1 
    return 0;
}
```

---

## 作者：Virtual_Character (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1912L)

对于这道题，无非就是统计左序列和右序列中 `L` 和 `O` 出现的次数，然后进行比较。慢慢增加分割的左序列的长度，直到遇见使得左部分的 `O` 数量不等于右部分的 `O` 数量，且左部分的 `L` 数量不等于右部分的 `L` 数量的情况，否则输出 $-1$。

这里用到了一个 `count` 函数，用来获取给定范围中中指定字符出现的次数。

```cpp
#include<bits/stdc++.h>
using namespace std;
string str;
int main(){
    int n;
    cin>>n;
    cin>>str;
    
    int Lcntr = count(str.begin() + 1, str.end(), 'L');
    int Ocntr = count(str.begin() + 1, str.end(), 'O');
    if((str[0]=='L'&&Lcntr==1)||(str[0]=='O'&&Ocntr==1));
	else{
		cout<<1;
		return 0;
	}
    for(int i=1;i<n-1;i++){
        int Lcntl=count(str.begin(),str.begin()+i,'L');
        int Ocntl=count(str.begin(),str.begin()+i,'O');
        Lcntr=count(str.begin()+i+1,str.end(),'L');
        Ocntr=count(str.begin()+i+1,str.end(),'O');
        if(Lcntl!=Lcntr&&Ocntl!=Ocntr){
            cout<<i+1;
            return 0;
        }
    }
    cout<<-1;
    return 0;
}
```

需要注意的一点是：如果 $i$ 等于 $0$，`count(str.begin(), str.begin() + i, 'L')` 将返回 $0$，因为该函数的第二个参数是表示范围的迭代器，`str.begin() + i` 等于 `str.begin()`。因此，这个范围是空的，`count` 函数在空范围内查找字符 `L`，自然返回 $0$，因为没有找到任何匹配项。所以将其放在前面单独判定。



---

## 作者：Big_Dinosaur (赞：1)

使用前缀和和后缀和，定义 $4$ 个数组，$qL[i]$ 表示前 $i$ 个字符中 `L` 个数，$qO[i]$ 表示前 $i$ 个字符中 `O` 个数，$hL[i]$ 表示后 $i$ 个字符中 `L` 个数，$hO[i]$ 表示后 $i$ 个字符中 `O` 个数。

如果存在 $i$，使得 $qL[i]\ne hL[i]$ 且 $qO[i]\ne hO[i]$，则 $i$ 就是一个解，输出。如果没有 $i$，无解。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
namespace Dino{
inline int r(){
int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+ch-48;ch=getchar();}return x*f;
}
int n,qO[300],qL[300],hO[300],hL[300];string s;
inline void _(){
  n=r();cin>>s;for(int i=1;i<=n;++i){
  	qO[i]=qO[i-1],qL[i]=qL[i-1];if(s[i-1]=='O')++qO[i];else ++qL[i];
  }
  for(int i=n;i;--i){
  	hO[i]=hO[i+1],hL[i]=hL[i+1];if(s[i-1]=='O')++hO[i];else ++hL[i];
  }
  for(int i=1;i<n;++i)if(qO[i]!=hO[i+1]&&qL[i]!=hL[i+1]){cout<<i;return;}
  cout<<-1;
}
}
signed main(){Dino::_();}
```

---

## 作者：ccjjxx (赞：1)

# CF1912L LOL Lovers 题解

题目数据范围是 $2\le n\le200$，直接循环分割点，然后再向两头分别记录 `L` 和 `O` 的个数即可。

时间复杂度 $O(n^2)$

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
char c[10000]; 
int ans=-1;
int main()
{
	int n;
	cin>>n>>(c+1);
	for(int i=1;i<n;i++)
	{
		int ll=0,lo=0,rl=0,ro=0;
		for(int j=1;j<=i;j++)
		{
			if(c[j]=='L') ll++;
			else lo++;
		}
		for(int j=i+1;j<=n;j++)
		{
			if(c[j]=='L') rl++;
			else ro++;
		}
		if(ll!=rl&&lo!=ro)
		{
			ans=i;
			break;
		}
	}
	cout<<ans;
 } 
```
---
---

或者，可以开两个数组预处理一下 `L` 和 `O` 的个数前缀和，这样就可以得到 $O(n)$ 的做法。

因为数据强度不够，所以二者时间上相差不大。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans=-1;
char c[10010];
int l[100010],o[100010];
int main()
{
	cin>>n>>(c+1);
	for(int i=1;i<=n;i++)
	{
		if(c[i]=='L')
			l[i]=l[i-1]+1,o[i]=o[i-1];
		else
			l[i]=l[i-1],o[i]=o[i-1]+1;
	}
	for(int i=1;i<n;i++)
	{
		int ll=l[i],lo=o[i];
		int rl=l[n]-l[i],ro=o[n]-o[i];
		if(ll!=rl&&lo!=ro)
		{
			ans=i;break;
		}
	}
	cout<<ans;
}
```


---

## 作者：_little_Cabbage_ (赞：0)

# CF1912L LOL Lovers 题解
~~[博客食用体验更佳](https://www.luogu.com.cn/blog/958804/solution-cf1912l)~~

这是一道字符串的暴力枚举题。

我们可以从 $1$ 遍历到 $len-1$，以第 $i$ 个位置为分割线，统计 $[0,i-1]$ 与 $[i,len-1]$ 的 l 和 o 的个数，判断是否不相等，如果不相等，输出 $i$，然后退出即可。

如果到最后一直没有输出，就输出 $-1$。

时间复杂度 $O(n^2)$。

AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int len;
	cin>>len;
	string s;
	cin>>s;
	for(int i=1;i<len;i++)
	{
		int l=0,o=0;
		for(int j=i-1;j>=0;j--)
		{
			if(s[j]=='L')
			{
				l++;
			}
			else
			{
				o++;
			}
		}
		int l1=0,o1=0;
		for(int j=i;j<len;j++)
		{
			if(s[j]=='L')
			{
				l1++;
			}
			else
			{
				o1++;
			}
		}
		if(l!=l1&&o!=o1)
		{
			printf("%d",i);
			return 0;
		}
	}
	printf("-1");
}
```
~~AC 记录因 rmj 炸了是在 cf 官网提交的~~

[AC 记录](https://codeforces.com/contest/1912/submission/238332494)

---

## 作者：very_easy (赞：0)

发现一道水红题，赶紧来写题解。

~~数据已经说明了一切，当然直接打暴力啊。~~

题目的意思已经很明确了，就是让你分一个字符串，使左边和右边 `O` 和 `L` 数量不一样就好了。

我们可以先预处理出字符串中 `O` 和 `L` 的数量，然后暴力枚举左区间的右端点，双重循环求左区间中 `O` 和 `L` 的数量，再用总数量减去左区间中的数量就可以得到右区间的数量，最后比较一下就好了。

## 代码

```c++
#include<bits/stdc++.h>
using namespace std;
int n,o,l;
string a; 
int main(){
	cin>>n;
	getchar();//注意这个细节，一定要用getchar读掉刚刚输入整数时遗留下的换行 
	cin>>a;
	for(int i=0;i<a.size();i++){//预处理出O和L的数量 
		if(a[i]=='O') o++;
		if(a[i]=='L') l++;
	}
	for(int i=1;i<a.size();i++){//暴力枚举左区间的右端点 
		int to=0,tl=0;
		for(int j=0;j<i;j++){//计算左区间中O和L的数量 
			if(a[j]=='O') to++;
			if(a[j]=='L') tl++;
		}
		if(o-to!=to&&l-tl!=tl){//判断 
			cout<<i;
			return 0;//满足条件直接结束程序 
		}
	}
	cout<<-1;//找不到输出-1 
	return 0;
}

```

---

## 作者：cloud2764scallop_eve (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1912L)

## 题目大意

给定一个长度为 $n$ 的、只有 `O` 和 `L` 组成的字符串，求出一个 $i$，使得 $i$ 左侧和右侧 `O`、`L` 的数量互不相等且每侧至少有一个 `O` 和一个 `L`。

## 思路

注意 $n$ 的范围是 $2 \le n \le 200$，数据范围很小，暴力的时间复杂度是可以接受的。

暴力的想法很简单，就是预处理出 $i$ 为任意值时字符串左侧 `O` 和 `L` 的数量，再用一个循环做判断即可。

对于求右侧 `O` 和 `L` 的数量，可以用 $i = n$ 时的数量减去 $i$ 的数量。

## 代码

```cpp
#include <bits/stdc++.h>
#define il inline
using namespace std;
const int N = 205;
int n, ocnt[N], lcnt[N];
char s[N];
int main() {
	scanf("%d%s", &n, s + 1);
	ocnt[0] = lcnt[0] = 0;
	for (int i = 1; i <= n; i++) {
		ocnt[i] = ocnt[i - 1], lcnt[i] = lcnt[i - 1];
		if (s[i] == 'O') ocnt[i]++;
		if (s[i] == 'L') lcnt[i]++;
	}
	for (int i = 1; i <= n; i++) {
		int ot = ocnt[n] - ocnt[i], lt = lcnt[n] - lcnt[i];
		if (ocnt[i] != ot && lcnt[i] != lt && (ot != 0 || lt != 0) && (ocnt[i] != 0 || lcnt[i] != 0)) {
			printf("%d\n", i);
			return 0;
		}
	}
	printf("-1\n");
	return 0;
}
```

> 注意在做判断时不要忘记判两侧的字符串是否都至少有一个 `O` 和一个 `L`。

---

## 作者：SMall_X_ (赞：0)

[原题传送门](https://www.luogu.com.cn/problem/CF1912L)


---
## 题目大意

有一个仅有 `0` 和 `L` 构成的序列，求出一种方案，使得左部分的 `0` 数量不等于右部分的 `O` 数量，且左部分的 `L` 数量不等于右部分的 `L` 数量，若不存在输出 `-1`。

## 思路分析

首先看题目范围，$2≤n≤200$，数据很小，考虑暴力。

可以使用字符串截取函数 `s.substr()`。

本题我们使用其两种使用方法：

- `s.substr(idx,len)` 截取下标为 $idx$ 之后（包括 $idx$）的 $len$ 位元素。

- `s.substr(idx)` 截取下标为 $idx$ 一直到字符串最后的所有元素。

针对此题，第一种方法可截取左部分，第二种方法可截取有部分，按照题意模拟即可。

该思路的时间复杂度为 $\mathcal{O(n^2)}$。

代码：
```cpp
/*Written by smx*/
#include<bits/stdc++.h>
using namespace std;
bool check(string a,string b){
	int La=0,Lb=0,ZEROa=0,ZEROb=0;
	for(int i=0;i<a.size();i++){
		if(a[i]=='L'){
			La++;
		}
		else{
			ZEROa++;
		}
	}
	for(int i=0;i<b.size();i++){
		if(b[i]=='L'){
			Lb++;
		}
		else{
			ZEROb++;
		}
	}
	return La!=Lb&&ZEROa!=ZEROb;
}
int main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int len;
	string s;
	cin>>len>>s;
	for(int i=0;i<s.size()-1;i++){//枚举分割位置
		string strl,strr;
		strl=s.substr(0,i+1);
		strr=s.substr(i+1);
		if(check(strl,strr)){
			cout<<i+1;
			return 0;
		}
	}
	cout<<"-1";
	return 0;
}
```

---

## 作者：lraM41 (赞：0)

题意：分配 $n$ 个食物（仅有两种食物-面包和洋葱）。要满足每个人应该至少有一个食物；你的面包数量应该与你朋友的面包数量不同；你的洋葱数量应该与你朋友的洋葱数量不同三个条件，输出你分配的食物数或 $-1$（无解）。

思路：前缀和。

```
#include<bits/stdc++.h>
using namespace std;
int n,ans=-1,a[205],b[205];
string s;
signed main(){
	cin>>n>>s;
	s='.'+s;
	for(int i=1;i<=n;i++) a[i]=a[i-1]+(s[i]=='L'),b[i]=b[i-1]+(s[i]=='O');
	for(int i=1;i<n;i++){
		if(a[i]!=a[n]-a[i]&&b[i]!=b[n]-b[i]){
			ans=i;
			break;
		}
	}
	return cout<<ans,0;
}

---

## 作者：myyyIisq2R (赞：0)

## [CF1912L - LOL Lovers](https://www.luogu.com.cn/problem/CF1912L)
## 翻译
- 对于一个仅由 `O` 和 `L` 构成的序列，给出序列长度 $n$，分割序列成为左右两部分。
- 求出一种分割方案使得左部分的 `O` 数量不等于右部分的 `O` 数量，且左部分的 `L` 数量不等于右部分的 `L` 数量
- 输出任意一种可能方案的左序列长度，若方案不存在，输出 $-1$。

保证 `O` 与 `L` 至少各有一个。

$2 \le n \le 200$
## Sol1
因为 $n$ 实在太小，所以我们可以暴力枚举左部分长度搜索。
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int getO(string s);
int getL(string s);
signed main()
{
	int n;
	cin>>n;
	string str;
	cin>>str;
	str = "="+str;
	for(int i{1};i<n;i++)
	{
		string s1 = str.substr(1,i);
		string s2 = str.substr(i+1,n-i);
		//cout<<s1<<" "<<s2<<endl;
		if(getO(s1)!=getO(s2) && getL(s1) != getL(s2))
		{
			cout<<i<<endl;
			return 0;
		}
	}
	cout<<-1<<endl;
	return 0;
	// =LOL
}
int getO(string s)
{
	int ans{};
	for(int i{};i<s.length();i++) if(s[i] == 'O') ans++;
	return ans;
}
int getL(string s)
{
	int ans{};
	for(int i{};i<s.length();i++) if(s[i] == 'L') ans++;
	return ans;
}

```
# Sol2
当我们将最左端第一个拆出来，由于它的唯一性，使得它必定满足 `L` 或者 `O` 的数量与右部分不同，同理拆开右端第一个。

这样我们只需要判断拆出来的这一个，和另外一部分的这个字符的个数相不相同。

举个例子，对于 `OOOL`，拆出来最左端一个是 `O`，那么 `L` 的个数必定不相同，则我们只需要比对 `O` 和 `OOL` 中 `O` 的个数，很明显不相同，那么这种情况便成立，输出。

但是要进行特判，如果出现 `OOLL` 或者 `LLOO` 的情况，分开中间部分。

$O(n)$

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
string str;
signed main()
{
	int n; cin>>n>>str;
	str = "="+str;
	int cntO{},cntL{};
	for(int i{1};i<=n;i++)
	{
		if(str[i] == 'O') cntO++;
		if(str[i] == 'L') cntL++;
	} 
    bool ok = false;
	if(cntO != 2)
	{
		if(str[1] == 'O') cout<<1<<endl,ok = true;
		else if(str[n] == 'O') cout<<n-1<<endl,ok = true;
		if(ok) return 0;  
	}
	if(cntL != 2)
	{
		if(str[1] == 'L') cout<<1<<endl,ok = true;
		else if(str[n] == 'L') cout<<n-1<<endl,ok = true;
		if(ok) return 0;  
	}
	
	if(str == "=LLOO" || str == "=OOLL") cout << 2;
	else cout<<-1<<endl;
	return 0;
	// =LOL
}

```


---

## 作者：czxQQQ (赞：0)

## 思路

数据小，暴力，统计一下两个字符串 `L` 和 `O` 的个数即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,sum;
string a;
int main(){
	cin>>n>>a;
	for(int i=0;i<a.length()-1;i++){
		string b,c;
		for(int j=0;j<=i;j++) b+=a[j];//前缀 
		for(int j=i+1;j<=a.length()-1;j++) c+=a[j];
		int bl=0,bo=0,cl=0,co=0;
		for(int j=0;j<b.length();j++){
			if(b[j]=='L') bl++;
			else bo++;
		}
		for(int j=0;j<c.length();j++){
			if(c[j]=='L') cl++;
			else co++;
		}
		if(bl!=cl&&bo!=co){//如果符合直接输出 
			cout<<i+1;
			return 0;
		}
	}
	cout<<-1;
	return 0;
}
```


---

## 作者：Creative_sad_yosgic (赞：0)

# **CF1912L题解**
### 题意
给一个字符串，把字符串分割成两部分，使得一个部分 $L$，$R$ 的出现次数都与另一部分不同。
### 题解
这里数据范围很小，暴力 $O(n^2)$ 肯定是能过的，但假如给一个 $2 \leq n \leq 2 \times 10^5$ 的数据呢？

这里给定一种 $O(n)$ 做法，定义两个前缀和数组，分别统计 $L$，$R$ 到每个点时的的出现次数，然后直接枚举割点，用前缀和数组比较即可。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=205;
int s;string str;
int flag;
int a[maxn],b[maxn];
int main(){
	cin>>s>>str;
	for(int i=1;i<=s;i++){
		if(str[i-1]=='L') a[i]=a[i-1]+1,b[i]=b[i-1];
		else b[i]=b[i-1]+1,a[i]=a[i-1];//统计前缀和
	}
	for(int i=1;i<=s-1;i++){
		if((a[i]!=a[s]-a[i])&&(b[i]!=b[s]-b[i])){//比较 L,R 出现次数是否相同
		    flag=1;
			cout<<i<<'\n';
			break;//因为题目只需要一个答案 输出后退出循环就行
		}
	}
	if(!flag) cout<<-1<<'\n';
	return 0;
}
```


---

