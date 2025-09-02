# You're Given a String...

## 题目描述

You're given a string of lower-case Latin letters. Your task is to find the length of its longest substring that can be met in the string at least twice. These occurrences can overlap (see sample test 2).

## 样例 #1

### 输入

```
abcd
```

### 输出

```
0```

## 样例 #2

### 输入

```
ababa
```

### 输出

```
3```

## 样例 #3

### 输入

```
zzz
```

### 输出

```
2```

# 题解

## 作者：Jsxts_ (赞：8)

# 题解 CF23A

[传送门](https://www.luogu.com.cn/problem/CF23A)

## 题意

求一个字符串中出现至少两次的子串的最长长度。

## 题解

这道题可以从大到小枚举子串长度，再枚举起点，最后判断子串是否符合要求。

**如何判断是否符合要求?**

我们可以用两个函数，一个叫 `substr`，一个叫 `find`。

`s.substr(i,j)` 可以求出字符串 s 从下标 i 开始，长度为 j 的字符串。

`s.find(s2,j)` 可以查找字符串 s 中从下标 j 开始，有没有出现字符串 s2。如果出现，返回它第一次出现的长度，否则返回 `s.npos`。

先取出子串，再用 `find` 函数找子串有没有出现两次，如果有就直接输出长度。

剩下细节在代码里说明（总共也就 19 行）。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
	string s;
	cin >> s;//输入字符串 
	int l = s.size();
	for (int i = l - 1;i >= 1;i -- ) {//从大到小枚举长度 
		for (int j = 0;j < l - i;j ++ ) {//枚举子串的起点
			string tmp = s.substr(j,i);//用s.substr取出子串 
			if (s.find(tmp,j+1) != s.npos) {//如果从 j+1 开始找到第二个字符串，就代表这个子串出现了两次，原因自己想
				printf("%d",i);//输出，结束程序 
				return 0;
			}
		}
	}
	putchar('0');//如果都没找到，就输出零 
	return 0;
}
```

用时：1.02s

---

## 作者：ZJKAW (赞：2)

因为题目说的是要输出位数，所以我们可以直接枚举位数。截取子串，在寻找原串里是否有2个及以上相同的子串。
```pascal
Var
     s1,s:ansistring; 
     i,j,ans:longint;
Function _pos(x:ansistring):boolean;//_pos函数用来寻找和截取出来的子串一样的字符串
var z,ans:longint;
begin
       ans:=0;
       for z:=1 to length(s)-i+1 do
         begin
         if copy(s1,z,i)=x then  inc(ans);
         if ans=2 then exit(true);//如果有相同的就返回true
         end;
       exit(false);
end;
Begin
  readln(s);
  for i:=1 to length(s)-1 do//枚举位数(当然不可能有和原串长度一样的两个子串)
    begin
      s1:=s;
     for j:=1 to length(s)-i+1 do//枚举子串的起点
          if _pos(copy(s,j,i)){截取子串并寻找} then begin ans:=i;break;end;
    end;
    writeln(ans);
End.
```


---

## 作者：happybob (赞：1)

 _Update：2021.1.14，发现了几个错误_ 

暴力就完了！

这里我们很明显可以用接近 $\large O(n^4)$ 的暴力枚举，那么对于匹配两次出现我们可以用 `find`。

每次 `erase`？

不对，`erase` 的坏处是会直接破坏原来字符串，并且也不是 $\large O(1)$ 的删除，我们可以用 `find` 的另一个重载函数去做：

```cpp
find(string, int);
```

第一个还是存要找的字符串，第二个是一个下标，代表搜索范围从这个下标到最后一个字符。

代码，996ms：

```cpp
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

inline bool check(string&);

string s;

int main()
{
	cin >> s;
	int len = s.size() - 1, ans = 0;
	for (register int i = len; i >= 0; i--)
	{
		for (register int j = 0; j <= i; j++)
		{
			string x = s.substr(j, i - j + 1);
			if (check(x))
			{
				ans = max(ans, i - j + 1);
			}
		}
	}
	cout << ans << endl;
	system("pause");
	return 0;
}

inline bool check(string& x)
{
	string v = s;
	int cnt = 0, last = -1;
	while (v.find(x, last + 1) != string::npos && cnt < 2)
	{
		cnt++;
		last = v.find(x, last + 1);
	}
	return cnt >= 2;
}
```


---

## 作者：EuphoricStar (赞：0)

## 枚举 + 暴力
### 基本思路
创建一个集合用来存放子串并判重。

从大到小枚举子串的长度 $i$ 和子串开始的位置 $j$，将相应子串添加进集合。（注意每次循环要清空集合）

如果集合长度小于 $j+1$ 表示该子串出现了两次，则打印长度并直接退出程序。
### 代码
**注：`s.substr(pos, n)` 表示从索引 `pos` 截取长度为 `n` 的子串。**

```cpp
#include <bits/stdc++.h>
using namespace std;

set<string> ss;
string s;

int main()
{
    ios::sync_with_stdio(0);
    cin >> s;
    for (int i = s.size() - 1; i > 0; --i)
    {
        ss.clear();
        for (int j = 0; j <= s.size() - i; ++j)
        {
            ss.insert(s.substr(j, i));
            if (ss.size() < (j + 1))
            {
                cout << i;
                goto END;
            }
        }
    }
    cout << 0;
    END: return 0;
}
```


---

## 作者：Eason_AC (赞：0)

## Content
给定一个长度为 $n$ 的字符串，求出至少出现两次的最长子串的长度。

**数据范围：$1\leqslant n\leqslant 100$。**
## Solution
我们直接暴力求出每个子串，然后统计它的出现次数（可以直接用 $\texttt{map}$ 映射），最后将出现次数 $\geqslant 2$ 的所有子串的长度取个最大值即可。
## Code
```cpp
string s, ss[10007];
map<string, int> vis;

int main() {
	cin >> s;
	int len = s.size(), ans = 0, cnt = 0;
	_for(i, 0, len - 1) {
		_for(j, 0, i) {
			cnt++;
			_for(k, j, i)
				ss[cnt] += s[k];
			vis[ss[cnt]]++;
		}
	}
	_for(i, 1, cnt) {
		int len = ss[i].size();
		if(vis[ss[i]] >= 2)	ans = max(ans, len);
	}
	writeint(ans);
	return 0;
}
```

---

## 作者：SIXIANG32 (赞：0)

这道题很简单，直接模拟即可。用双重循环构造查找串然后查找出最大的长度即可。是不是很正常？  
**但是——  
我们阔以用STL！！！！**   
STL给予了我们神奇的string的find函数，所以我们不用一个个去枚举咯。时间复杂度比巨硬暴力快得多。用find函数1.36ms左右，不用find函数2.2ms左右。 
下面是简单的代码
```cpp
#include<iostream>
#include<string>
using namespace std;
int main()
{
	string s,f="";//f是构造匹配串
   	int max=0;/最大值
	cin>>s;//输入字符串
	for(int p=0;p<=s.size()-1;p++)//以s[p]开头的匹配串
	{
		for(int i=p;i<=s.size()-1;i++)//继续往后构造匹配串
		{
		    f+=s[i];//匹配串增加一个
		    if(s.find(f,p+1)!=string::npos)//找到咯！这个s.find(f,p+1)的意思是指在p+1后的范围内查找f字符串，如果找不到就会返回npos，否则会返回最早出现的位置
		    {
		        if(max<f.size())max=f.size();//比较
		    }
		}
		f="";//匹配串清空
	}
	cout<<max;//输出
	return 0;//华丽结束
}
```

---

## 作者：char32_t (赞：0)

# 题解 CF23A 【You're Given a String...】
------------
需要在所给字符串中找出最少出现两次的最长子串的长度，所以两层for循环遍历字符串可直接得出。
```cpp
#include<cstdio>
#include<cstring>
char str[110];//字符数组 
int main() {
	int len, t, _max=0;
	scanf("%s", str);//读入字符串 
	len=strlen(str);//测出字符串长度 
	for(int i=0; i<len; i++)//枚举字符 
		for(int j=i+1; j<len; j++) {//向后比较 
			t=0;
			while(str[i+t]==str[j+t]) t++;//找到第一个，后移一位 
			if(t>_max) _max=t;//保存将当前至少2次重复的最长字串长度 
		}
	printf("%d", _max);//输出 
	return 0;
}
```

---

## 作者：动态WA (赞：0)

这里提供一种$O(nlogn)$的方法。

首先看到题目，发现有“最少出现”“最长子串”这样的字眼，于是决定用二分枚举答案长度，复杂度为$O(logn)$，二分时注意特判0。

下一步则是想check函数判断是否成立，我们可以用到map，将每个子串都判断一下是否重复，如果没有则塞进map，否则直接返回true。

代码如下：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<queue>
#include<algorithm>
#include<ctime>
#include<map>
using namespace std;
string s;
int n;
bool check(int mid){
	map<string,bool> m;
	for (int i=1;i<=n-mid+1;i++){
		string s1=s.substr(i,mid);
		if (m[s1]) return 1;
		else m[s1]=1;
	}
	return 0;
}
int main(){
	cin>>s;
	n=s.size();
	s=' '+s;
	int l=1,r=n-1;
	while (l<r){
		int m=(l+r+1)/2;
		if (check(m)) l=m;
		else r=m-1;
	}
	if (r==1)
		if (check(1)) putchar('1');
		else putchar('0');
	else
		printf("%d",r);
}
```


---

## 作者：CrTsIr400 (赞：0)

我们先来看看题

**因为$1 \leq n \leq 100$**

所以使用**暴力**算法就可以解决。

时间复杂度$O(n^3)$。

先**枚举**第**一**个字串的**左**端点，再**枚举**第**二**个字串的**左**端点，最后**判断**相等，$3$个$O(n)$的解法乘起来，一秒之内也能跑出。

```cpp
#include<bits/stdc++.h>
#define inf (1<<30-1)
#define linf ((1<<62)ll-1)
#define Fu(i,a,b) for(register int i=a;i<=b;i++)
#define Fd(i,a,b) for(register int i=a;i>=b;i--)
#define Fn(i,a) for(register int i=las[a];i;i=nex[i])
int Fl,Pn,SI=100;char mch=' ',ch,Bf[21];
template<typename t>void in(t&a){a=0;ch=getchar();Fl=1;while((ch<'0')||(ch>'9'))Fl=(ch=='-')?-Fl:Fl,ch=getchar();while((ch>='0')&&(ch<='9'))a=a*10+ch-'0',ch=getchar();a*=Fl;}
template<typename t>void out(t a){if(a<0)putchar('-'),a=-a;if(a==0)putchar('0');while(a)Bf[++Pn]=a%10+'0',a/=10;while(Pn)putchar(Bf[Pn]),--Pn;putchar(mch);}
template<typename t,typename ...ARGS>void in(t&a,ARGS&...args){in(a);in(args...);}
template<typename t,typename ...ARGS>void out(t a,ARGS... args){out(a);out(args...);}
using namespace std;
int maxlen,len,n=1;char c[101]; 
int main()
{
	while(!isalpha(c[1]=getchar()));
	while(isalpha(c[++n]=getchar()));
	n--;
	Fu(i,1,n-1)//串1的左端点保证不为n，如果为n，右端点就不能枚举了
	Fu(j,i+1,n)//串2的左端点保证要比串1的大
	{
		len=1;
		while(c[i+len-1]==c[j+len-1])len++;//暴力求解最长公共长度
		maxlen=max(len-1,maxlen);//更新最长公共长度
	}
	cout<<maxlen;
	return 0;
}

```

**注意细节**。

---

