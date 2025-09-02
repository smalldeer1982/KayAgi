# Codehorses T-shirts

## 题目描述

**题目大意：**

$n$个字符串和$n$个模板串，在$1s$的时间内你可以选择一个字符串（不是模板串）修改任意多的字符，但是不能删除或增加字符，问至少需要多少s使得字符串变为模板串，注意不考虑串的顺序，即最后每个字符串出现次数=这个串在模板串中的出现次数

## 样例 #1

### 输入

```
3
XS
XS
M
XL
S
XS
```

### 输出

```
2
```

## 样例 #2

### 输入

```
2
XXXL
XXL
XXL
XXXS
```

### 输出

```
1
```

## 样例 #3

### 输入

```
2
M
XS
XS
M
```

### 输出

```
0
```

# 题解

## 作者：冰糖鸽子 (赞：3)

~~Codehorses珂海星2333~~

因为特殊题号见到的这题

----

字符串们 $\rightarrow$ 串组 $\text{A}$

模板串们 $\rightarrow$ 串组 $\text{B}$

发现几个小性质：

1. 一个串最多改变一次

1. 不管怎么改变，字符串的长度都不会变

1. 可以直接消去 $\text{A}$ 与  $\text{B}$ 中的相同字符串

1. 因为题目没有无解情况，所以若长度为 $x$ 的字符串在 $\text{A}$ 中出现了 $y$ 次，则 $\text{B}$ 中一定有且仅有 $y$ 个长度为 $x$ 的字符串

所以，根据 3 进行操作后，$\text{A}$（或 $\text{B}$） 中剩下多少字符串，答案即是多少。

AC代码：

```cpp

// Problem: CF1000A Codehorses T-shirts
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1000A
// Memory Limit: 250 MB
// Time Limit: 2000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <bits/stdc++.h>
using namespace std;
int n,rans;
string fs;
map<string,int>ans;
int main()
{
	cin>>n;rans=n;
	for(int i=1;i<=n;i++)
	{
		cin>>fs;
		ans[fs]++;
	}
	for(int i=1;i<=n;i++)
	{
		cin>>fs;
		if(ans[fs]){ans[fs]--;rans--;}
	}
	cout<<rans<<endl;
	return 0;
}
```

---

## 作者：xiaozeyu (赞：2)

[CF1000A Codehorses T-shirts](https://www.luogu.com.cn/problem/CF1000A)

题面不太舒服，这里解释一下这到底是怎样的一题。

题目会给出一些字符串，再给出同样多的另一些字符串。

可以理解为要求出至少在前一类串中改掉多少个串可以使两类串的所有字符串相同，不用考虑顺序，要一一对应不能重复用。

可以直接用 map 解决。

```cpp
map<string,int>m;

```

书名号里第一个可以称为关键字，每个关键字只能在 map 中出现一次。

第二个可称为该关键字的值。

简单而言第一个表示下标的类型。第二个表示存的值的类型。

我们之间用 string 来存读入，在 map 中加上这个值。

如何处理结果？

我们会发现将第一类的串改为与第二类相同，就是要统计第一类有多少已经满足和第二类中的一个串匹配了，然后算一下剩下没匹配的串数。

代码如下。

---

```cpp
#include<bits/stdc++.h>
#define int long long
#define For(i,a,b) for(int i=a;i<=b;i++)
#define Rep(i,a,b) for(int i=a;i>=b;i--)
#define f(a) ((a)*(a))
#define p(x) printf("%lld ",(x))
#define P() puts("")
using namespace std;
inline int read()
{
	char c=getchar();int x=0;bool f=0;
	while(!isdigit(c))f^=!(c^45),c=getchar();
	while(isdigit(c))x=(x<<1)+(x<<3)+(c^48),c=getchar();
	if(f)x=-x;return x;
}
const int maxn=110;
int n,ans;
string s;
map<string,int>m;
signed main()
{
	n=read();
	For(i,1,n)
	{
		cin>>s;
		m[s]++;
	}
	For(i,1,n)
	{
		cin>>s;
		if(m[s]>0) m[s]--;
		else ans++;
	}
	p(ans);
}
```
---

感谢管理员的审核。

---

## 作者：VenusM1nT (赞：2)

模拟。  
因为每次只能改一个字母，不能加减，而且 size 的 feature 决定了相同长度的两个 size 要么相同，要么相差一个字母，所以直接用 map 把相同的抵消一手，剩下多少个 size 就是答案。  
```cpp
#include<bits/stdc++.h>
#define MAXN 105
#define reg register
#define inl inline
using namespace std;
int n,tot;
map <string,int> m;
int main()
{
	ios::sync_with_stdio(0);
	cin>>n;
	for(reg int i=1;i<=n;i++)
	{
		reg string x;
		cin>>x;
		m[x]++;
	}
	for(reg int i=1;i<=n;i++)
	{
		reg string x;
		cin>>x;
		if(m[x]) m[x]--;
		else tot++;
	}
	printf("%d\n",tot);
	return 0;
}
```

---

## 作者：风浔凌 (赞：1)

因为只能每次转换一个字母，所以说开map将其存起来就好啦！list1每次扫到对应数组++，List2每次扫到--，最后因为题目保证可以实现转换，所以加起来一定为0，而我们将大于零的加起来就好啦~~
```c
#include<iostream>
#include<cstdio>
#include<cstring>
#include<map>
#include<algorithm>
using namespace std;
map<string,int>m;
string s;
int n,ans=0;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		cin>>s;
		m[s]++;
	}
	for(int i=1;i<=n;i++)
	{
		cin>>s;
		m[s]--;
	}
    
	for(map<string,int>::iterator it=m.begin();it!=m.end();it++)
	   ans+=max(0,it->second);
	   
	cout<<ans<<endl;
	
	return 0;
}
```

---

## 作者：Allanljx (赞：1)

 [洛谷题目传送门](https://www.luogu.com.cn/problem/CF1000A)
 
 [CF题目传送门](https://codeforces.com/problemset/problem/1000/A)
## 题意
给定去年和今年的衣服型号表，问修改多少次衣服型号可使两年的衣服型号一样

## 思路
因为衣服的型号数量是有限的，所以可以用 $c$ 数组记录去年每种型号的衣服出现的次数，$d$ 数组记录今年每种型号的衣服出现的次数。在用 $sum$ 记录 $|c[i][j]-d[i][j]|$ 的总和。最后除以$2$，因为每种都算了两次。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
string a,b;
int c[10][10],d[10][10];//i代表有多少个X，j=0代表S,j=1代表M,j=2代表L
int main()
{
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>a;
        if(a=="S") c[0][0]++;
        if(a=="M") c[0][1]++;
        if(a=="L") c[0][2]++;
        if(a=="XS") c[1][0]++;
        if(a=="XL") c[1][2]++;
        if(a=="XXS") c[2][0]++;
        if(a=="XXL") c[2][2]++;
        if(a=="XXXS") c[3][0]++;
        if(a=="XXXL") c[3][2]++;
    }
    for(int i=1;i<=n;i++)
    {
        cin>>a;
        if(a=="S") d[0][0]++;
        if(a=="M") d[0][1]++;
        if(a=="L") d[0][2]++;
        if(a=="XS") d[1][0]++;
        if(a=="XL") d[1][2]++;
        if(a=="XXS") d[2][0]++;
        if(a=="XXL") d[2][2]++;
        if(a=="XXXS") d[3][0]++;
        if(a=="XXXL") d[3][2]++;
    }
    int sum=0;
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<3;j++)
        {
            sum+=abs(c[i][j]-d[i][j]);
        }
    }
    cout<<sum/2<<endl;//因为每种都多算了一次
    return 0;
}
```



---

## 作者：Fa1thful (赞：0)

### 题意：
给定多个字符串，求把它们都变成目标串的最少次数，每个串一次只能变一个字母，不考虑顺序。
### 思路：
这题就是一个模拟，先排序，因为不考虑每个串变成目标串的顺序，也就是第一个串可以变为目标串中的任意一个，第二个串可以变为除第一个变成的目标串的其他目标串。再用一个数组记录原先串每个串的长度，最后三重循环判断不改变还是要改变，要改变的话改变多少个字母。

注：此题也可以用`map`个出现的次数再直接找
### 代码：
```cpp
# include <bits/stdc++.h>
using namespace std;
string s1[111], s2[111];
int n, b[10];
bool book[111];
int main()
{
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> s1[i];
	}
	for (int i = 1; i <= n; i++)
	{
		cin >> s2[i];
	}
	sort(s1 + 1, s1 + n + 1);           //排序 
	sort(s2 + 1, s2 + n + 1);
	int ans = 0;
	for (int i = 1; i <= n; i++) 
	{
		b[s1[i].size()]++;           //记录原先串的长度 
	}
	int p = 1;   //找的位置           
	for (int i = 1; i <= 4; i++)
	{
		memset(book, 0, sizeof(book)); 
		for (int j = p; j < p + b[i]; j++)
		{
			bool flag = 0;      //是否要改变 
			for (int k = p; k < p + b[i]; k++)
			{
				if (book[k]) continue; //以前有串变过 
				if (s1[j] == s2[k])     //相同 
				{
					book[k] = 1;   //这个不能再变了 
					flag = 1;     //不改变 
					break;
				}
			}
			if(!flag) ans++;      //要变 
		}
		p += b[i]; //从下一个位置开始找 
	}
	cout << ans << endl;
	return 0;
}
```


---

