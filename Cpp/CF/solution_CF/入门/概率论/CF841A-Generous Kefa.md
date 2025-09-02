# Generous Kefa

## 题目描述

读入一个字符串（都是小写字母），让你求出里边最多的一种字母的个数是否小于等于 $k$。，若大于输出"NO",否则输出"YES"。   
第二行为一个字符串。

## 样例 #1

### 输入

```
4 2
aabb
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
6 3
aacaab
```

### 输出

```
NO
```

# 题解

## 作者：piggymichael (赞：3)

~~CF的红题总是很水。~~

这道题嘛，只有小写字母，26个，每个的数量都统计一下，和k比一比就行了，边输入边统计，一发现超过k了就输出NO，结束程序。思路也是挺简单的。

看代码：
```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;
int n,k,a[30];
char x;
int main()
{
	cin>>n>>k;
	for(int i=1;i<=n;++i)
	{
		cin>>x;
		a[x-'a']++;//每个字母对应一个数组记录这个字母出现的次数。
		if(a[x-'a']==k+1)//如果超了就输出，注意题目是<=k输出YES，所以这里是k+1。
		{
			cout<<"NO"<<endl;
			return 0;
		}
	}
	cout<<"YES"<<endl;一直到循环的最后一次都没有超，说明是YES了。
	return 0;
}
```

简单的题目，要争取一遍过。看懂题目的意思，不要掉坑，就快乐地AC啦！

---

## 作者：goodlearndaydayup (赞：2)

题意如下
给出一个长度为N的字符串（均小写字母），若其中一个字母出现次数大于K，则输出NO
否则输出YES
代码如下，直接数组计数求出现次数
```cpp
#include<iostream>
#include<fstream>
#include<algorithm>
using namespace std;
int n,k;
char s[999];
int ans[28];
int main()
{
     cin>>n>>k;
     for(int i=1;i<=n;i++)
	 {
		 cin>>s[i],ans[s[i]-'a']++;
		 if(ans[s[i]-'a']>k)//如果当前字符大于K，直接输出Rutern
		 {
			 cout<<"NO"<<endl;
			 return 0;
		 }
	 } 
	 cout<<"YES"<<endl;//前面都没有大于K的，输出YES
    return 0;
}
```
END

---

## 作者：lxyzlmx (赞：1)

本题考查的是字符串的简单应用。下面来简单讲讲思路。

#### 思路：首先读入n，k，然后读入字符串a，记录每个字母的个数，最后判断是否超过k，最后输出。

详见代码。

```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<string>
#include<algorithm>
using namespace std;
char a[105];//定义字符串，也可用string。
int d[26];//定义统计数组。

int main()
{
	int i,n,k,x;
	bool z=false;//判断是否输出。
	cin>>n>>k;
	scanf("%s", a);//读入字符串
	for (i=0; i<n; i++)//下标从0开始，因为n是长度，直接用。
	{
		x=a[i]-'a';//转整型。
		d[x]++;//统计字符
		if (d[x]>k)//判断
		{
			z=true;//防止多输出
            cout<<"No"<<endl; 
            break;
		}
	}
	if (z==false) cout<<"Yes"<<endl;//输出
	return 0;
}
```

最后感谢管理员大大审核。

---

## 作者：wpy233 (赞：1)

题意：给定一个字符串，求其中出现最多次数的字母的出现次数是否$ \leq k$。

对于这个问题，很显然能想到**桶排序**。扫一遍字符串，把每个字母的下标减去$96$（因为$a$的$ASCLL$码为$97$）之后存入一个数组，最后进行排序，再来一遍翻转，$a[1]$的值就是答案啦~

一些知识：

$sort$：**除非有comp函数**，一般都是**从小到大排序**，时间复杂度$O(n log n)$，极端情况$O(n^2)$。

$reverse$：将某一段数组中的数进行翻转。
```
#include <bits/stdc++.h>
using namespace std;
int a[30];//“桶”
string b;//字符串
int main()
{
	int n,k;
	cin>>n>>k;//输入
	cin>>b;
	for(int i=0;i<b.size();i++)
		a[b[i]-96]++;//计数，把每个字母存进“桶”
	sort(a+1,a+27);//从小到大排序
	reverse(a+1,a+27);//翻转
	if(a[1]<=k) cout<<"YES";//<=k，输出“YES”
	else cout<<"NO";//>k，输出“NO”
	return 0;
}
```

---

## 作者：RioBlu (赞：1)

我想对楼上的大佬说一句：同样是红名，为何我俩的差距这么大？
___
本题只需一个小小的桶，$n[30]$就差不多了。

时间复杂度：O(N)
```
#include<bits/stdc++.h>
using namespace std;
long long a,b,n[30];
char k;
int main()
{
	cin>>a>>b;
	while(a--)cin>>k,n[k-'a']++;//这样我不知道为什么能用
	for(int s=0;s<26;s++)
	{
		if(n[s]>b)
		{
			cout<<"NO"<<endl;return 0;
		}
	}
	cout<<"YES"<<endl;
}
```

---

## 作者：ShineEternal (赞：0)

## 题目链接：
https://www.luogu.org/problem/CF841A
## 分析：
看到没有用map做的，补充一下。

map的好处就是可以适应的类型多，数组下标作为查询再也不用愁。

但是作为一个STL就会比较慢。

不过一般的题目用一用还是没有问题的。

---

本题每读入一个字符，就在其作为下标所对应的map里++；顺便更新一下ans就行了。

```cpp
#include<cstdio>
#include<map>
#include<iostream>
using namespace std;
map<char,int>m;
int main()
{
	int n,k;
	char ch;
	int ans=0;
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
	{
		cin>>ch;
		m[ch]++;
		ans=max(ans,m[ch]);
	}
	if(ans<=k)
	{
		printf("YES\n");
	}
	else
	{
		printf("NO\n");
	}
	return 0;
} 
```

---

## 作者：Victory_Defeat (赞：0)

这道题很简单，只需一个小小的**统计**，统计**每个字符出现次数**，如果有$>k$的，输出$NO$即可，否则输出$YES$即可

具体见代码：
```cpp
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cctype>
#include<cstring>
#include<queue>
#include<iostream>
#include<map>
using namespace std;
typedef long long ll;
typedef double lf;
typedef unsigned un;
typedef int in;
#define mian main
#define _(a) read(a)
#define non void
#define inf 2147483647
#define bre break
#define con continue
#define prq priority_queue
#define Re register
#define bu bool
#define cz char
#define cst const
#define ope operator
#define inl inline
#define upp upper_bound
#define low lower_bound
#define next_pre next_premutation
template<typename T>inl T Max(T a,T b){return a>b?a:b;}
template<typename T>inl T Min(T a,T b){return a<b?a:b;}
template<typename T>inl T Abs(T a){return a<0?-a:a;}
template<typename T>inl non read(T &a){a=0;T k=1;char c=getchar();while(c<'0'||c>'9')k=c=='-'?-1:k,c=getchar();while(c>='0'&&c<='9')a=a*10+(c^48),c=getchar();a*=k;}
template<typename T>non write(T a,cz t=' '){if(a==0){putchar(48),putchar(t);return;}if(a<0){a=-a;putchar('-');}cz c[30];in le=0;while(a){c[++le]=a%10+48;a/=10;}for(Re in i=le;i>=1;--i)putchar(c[i]);putchar(t);}
//此前请自行忽略
cz a[105];
in n,k,s[26];
in main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	read(n),read(k),cin>>a;
    //输入
	for(Re in i=0;i<n;++i)++s[a[i]-'a'];
    //统计
	for(Re in i=0;i<=25;++i)if(s[i]>k){printf("NO");return 0;}
	printf("YES");
    //判断并输出
}
```

---

## 作者：人间凡人 (赞：0)

这是一道**计数**的题目。

用$f[i]$表示$'a'+i$这个字符出现的次数，最后在$f[0]$至$f[25]$中去一个最大值与$k$比较即可。

如果小于等于$k$，输出$YES$。否则输出$NO$。

时间复杂度：$O(n)$


$Code:$

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,k,ans;
string s;
int f[35];
int main() {
	scanf("%d%d",&n,&k);
	cin>>s;
	for(int i=0;i<n;i++){
		f[s[i]-'a']++;
		if(f[s[i]-'a']>ans)ans=f[s[i]-'a'];
      //计数
	}
	if(ans<=k)cout<<"YES\n";
	else cout<<"NO\n";
	return 0;
}

```


---

