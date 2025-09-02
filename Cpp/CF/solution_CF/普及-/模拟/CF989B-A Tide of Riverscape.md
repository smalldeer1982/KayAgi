# A Tide of Riverscape

## 题目描述

**题目大意：**

给定一个由'0','1','.'构成的字符串，问可不可能无论'.'是什么，这个字符串都存在长度为$p$的周期

## 样例 #1

### 输入

```
10 7
1.0.1.0.1.
```

### 输出

```
1000100010
```

## 样例 #2

### 输入

```
10 6
1.0.1.1000
```

### 输出

```
1001101000
```

## 样例 #3

### 输入

```
10 9
1........1
```

### 输出

```
No
```

# 题解

## 作者：ChenZQ (赞：2)

首先**简化题意**：

其实就是通过将"."改成‘0’或‘1’来使字符串不会以 $p$ 为一个循环节循环。

那么接下来讲**思路**

其实我们只需要让有一个字符能不等于他往后的 $p$ 个字符就好了。

首先假设所有的'.'都为‘0’，如果发现当前字符等于了往后 $p$ 个字符，就修改它，如果能在修改了这个字符之后使这个字符不等于往后 $p$ 个字符，那么其实就可以说明，这个序列可以改成满足要求的样子。因为已经有一个字符不等于往后 $p$ 个字符了，以长度为 $p$ 的一个循环节循环当然不会成立。

所以我们可以定义一个 $flag$ 变量表示是否出现上述情况，如果等于 1，就输出，等于 0 就输出"No"。

思路部分就讲完啦！

### AC CODE
```
#include<bits/stdc++.h>
using namespace std;

string s;
int n,p;
bool flag=0;

int main()
{
	
	scanf("%d%d",&n,&p);
	cin>>s;
	for(int i=0;i<n;i++)
	{
		if(s[i]=='.')
		{
			s[i]='0';
			if(i+p<n && s[i+p]=='0' || i-p>=0 && s[i-p]=='0') s[i]='1';
		}
		if(i+p<n && s[i]!=s[i+p]) flag=1;
	}
	if(flag) cout<<s;
	else puts("No");
}

```

---

## 作者：Spir1t (赞：1)

## [题目传送门](https://www.luogu.com.cn/problem/CF989B)

### 非原创！非原创！非原创！

看到题解区的做法都比较麻烦，在这推荐一种更为简便的方法。

其实此题，我们可以进行构造，首先把所有点都变为 $0$ 或 $1$，然后判断 $i-p$ 与 $i+p$ 的点是否相同，相同的话就就换为 $01$ 中的另外一个字符，最后判断存不存在一组周期 $p$  即可。

#### [代码](https://www.luogu.com.cn/paste/18l8mtd0)

---

## 作者：_zhx (赞：0)

#  CF989B A Tide of Riverscape 题解

## 题目大意

把 ‘$.$’ 改成 $0$ 或 $1$ 使字符串不会以 $p$ 为一个循环节循环。

### 大致做法

我们可以进行构造。

首先把所有 ‘$.$’ 都变为 $1$，然后判断 $i-p$ 与 $i+p$ 的点是否相同，相同的话就就换为 $0$，最后判断存不存在一组周期 $p$。最后根据 $f$ 来判断输出什么。

code:

```cpp
#include<bits/stdc++.h>
using namespace std;
string s;int n,p;bool f=0;
int main()
{	
	cin>>n>>p>>s;
	for(int i=0;i<n;i++)
	{
		if(s[i]=='.')
		{
			s[i]='1';
			if((i+p<n&&s[i+p]=='1')||(i-p>=0&&s[i-p]=='1')) s[i]='0';
		}
		if(i+p<n&&s[i]!=s[i+p]) f=1;
	}
	if(f) cout<<s<<"\n";
	else cout<<"No\n";
	return 0;//代码没什么难点，主要是构造的思维
}
```


---

## 作者：20120511qhc (赞：0)

## 思路

题目大意是给你一个字符串 $s$ ,让你构造一个字符串 $t$，使得 $t$ 不以 $p$ 为周期且每一个字符均与 $s$ 相同（`.`可以用 $0$ 或 $1$ 代替）。

不难发现，只要不是所有的 $s_i = s_{i + m} \ne$ `.`，那么 $t$ 一定能被构造出来。

我们可以先构造前 $m$ 个字符，使 $s_i \ne s_{i + m}$ , 再使后边的所有 $s_i \ne s_{i - m}$ 就可以了。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, f[2], fl;
string s;
int main(){
    cin >> n >> m >> s;
    for(int i = 0; i < s.size() - m; i++){
        if(s[i] == s[i + m] && s[i] != '.') continue;
        if(s[i] == s[i + m] && s[i] == '.'){
            fl = 1;
        }else if(s[i + m] == '.') f[!(s[i] - 48)]++, fl = 1;
        else if(s[i] == '.')f[!(s[i + m] - 48)]++, fl = 1;
        else if(s[i] != s[i + m]){
            fl = 1;
        }
    }
    if(!fl){
        cout << "No";
        return 0;
    }
    int u = (f[0] ? 0 : 1);
    for(int i = 0; i < m; i++){
        if(s[i] == '.'){
            if(i + m < s.size() && s[i + m] != '.'){
                s[i] = !(s[i + m] - 48) + 48;
            }
            else s[i] = '0';
        }
    }
    for(int i = m; i < s.size(); i++){
        if(s[i] == '.') s[i] = !(s[i - m] - 48) + 48;
    }
    cout << s;
    return 0;
}
```


---

## 作者：ylch (赞：0)

# CF989B A Tide of Riverscape 题解

[-题目传送门-](https://www.luogu.com.cn/problem/CF989B)

## 题目提示

注意本题是持续输入，不光输入一组。

## 题目简述

这道题翻译得有些不清楚，其实就是让你求出字符串每个位置与后 $k$ 个位置是否相等。即 $s_i=s_{i+k}$（保证 $i+k$ 在 $s$ 长度以内，不越界）。

## 解题思路

我们可以依次遍历 $s_i$，判断是不是与 $s_{i+k}$ 相等。

如果不想等的话先改变 $s_i$ 和 $s_{i+k}$ 的值，接下来按照题目的要求，为 `.` 输出 `0`，否则输出原数。

如果都相等的话就按照题意输出 `No`。

提示：注意数组下标越界的问题。

## 补充：字符的改变方式：

当前字符为 $s_i$，则再过 $k$ 个字符为 $s_{i+k}$。

以下情况 $1$ 根据样例推导，其余为必然现象。

| 情况 | $s_i$ | $s_{i+k}$ |
| :----------: | :----------: | :----------: |
| $s_i=s_{i+k}$ | $0$ | $1$ |
| $s_i=0$ | $0$ | $1$ |
| $s_i=1$ | $1$ | $0$ |
| $s_{i+k}=0$ | $1$ | $0$ |
| $s_{i+k}=1$ | $0$ | $1$ |


## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int n,k;
string s;

char change(char &a, char &b)
{
	if (a == b)
		a = '0', b = '1';
	else
	{
		if (a == '0')	b = '1';
		else if (a == '1')	b = '0';
		else
		{
		    if(b == '0')	a = '1';
		    else	a = '0';
		}
	}
}

int main()
{
	while (cin >> n >> k >> s)
	{
		for (int i=0; i<s.size(); i++)
		{
			if (i+k >= s.size())	break;
			if ((s[i] != s[i+k]) || (s[i] == '.'))
			{
				change(s[i], s[i+k]);
				for (int j=0; j<s.size(); j++)
				{
					if (s[j] == '.')	cout << "0" ;
					else	cout << s[j];
				}
				puts("");
				goto abc;
			}
		}
		puts("No");
		abc:;
	}
	return 0;
}
```

End
------------

管理员大大辛苦啦~

谢谢大家！我们一起进步，一起 $rp++$！

---

## 作者：_lgh_ (赞：0)

# 思路：
其实题目就是问你一个字符串每隔 $p$ 个后是否仍然左右相等。根据题意模拟就行了。
# 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
int main()
{
  ll n,k;
  while(cin>>n>>k)
  {
    string s;
    cin>>s;
    ll num;
    bool flag=0;//用来判断
    for(ll i=0; i<s.size(); i++)
    {
      if(i+k<s.size())
        if(s[i]!=s[i+k]||(s[i]==s[i+k]&&s[i]=='.'))//判断满不满足对称
        {
          if(s[i]==s[i+k]) s[i]='0',s[i+k]='1';
          else
          {
            if(s[i]=='0') s[i+k]='1';//
            else if(s[i]=='1') s[i+k]='0';
            else
            {
              if(s[i+k]=='0') s[i]='1';
              else s[i]='0';
            }
          }
          flag=1;
          break;
        }
    }
    if(flag)
      for(ll i=0; i<s.length(); i++)
        if(s[i]=='.') cout<<"0";
        else cout<<s[i];
    else cout<<"No";
    puts("");
  }
  return 0;
}
```


---

## 作者：jkrj02 (赞：0)

这题还没题解 我就来写篇

看这提交量感觉没几个人做。。

这题就是一道模拟，要考虑的方面还是挺多的，坑。。也挺多的

附上代码，讲解在代码里

这题因为是输出随意一种所以有很多种做法，我的方法可能比较麻烦因为是错了几遍改了几遍后AC的

【仅供参考】
```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <string>
#include <cmath>
using namespace std;
char s[2101];
int main()
{
	long long n,p,m=1,x;
	bool t=0,y=0;
	cin>>n>>p;
	for(int i=1;i<=n;i++)
	{
		cin>>s[i];
	}
	if(n==p)//如果长度和周期一样那就肯定没有不同的可能性了 
	{
		cout<<"No";
		return 0;
	}
	for(int i=1;i<=p;i++)//只循环一个周期就行，因为后面都是一样的 
	{
		m=i;//m表示判断位置，判断该位置有没有可能是那个不同的 
		while(m<=n&&(m+p<=n||m>p))//位置要比总长度小，m+p是下一个周期该位置，&&后面那一串表示m位置不能只有一个周期有，不然影响后面判断 
		{
			if(m+p<=n&&s[m+p]!=s[i]&&s[m+p]!='.'&&s[i]!='.')//如果不同周期相同位置不同，那总串肯定有不同的 
			{
				t=1;//t表示有不同的可能性 
				y=1;//这里设个旗帜，说明是这种方式判断有可能的 
				break;
			}
			else if(s[m]=='.')//如果多个周期里有一个问题有".",那就代表可以自由发挥了~~ 
			{
				t=1;//同上 
				x=m;//这里是记录一下在哪个位置判断有可能性，后面有用 
				break;
			}
			m+=p;//下一个周期相同位置 
		}
		if(t==1)//已经判断出来有可能性了，就不用继续循环了 
		{
			break;
		}
	}
	if(t==0)//循环一遍没判断出可能性 
	{
		cout<<"No";
		return 0;
	}
	else if(t==1&&y==0)//如果是用"."判断出有可能性的 
	{
		m=x;
		if(x+p<=n)//往后找，找不同的 
		{
			while(m<=n)
			{
				if(s[m]!='.')//找到一个不是点的，只要修改标记过的点让它跟后面的不一样就行 
				{
					if(s[m]=='1') 
					{
						s[x]='0';
						break;
					}
					else if(s[m]=='0')
					{
						s[x]='1';
						break;
					}
				}
				m+=p;
				if(m>n)//找了一圈没找到不是点的，说明所有周期这个位置都是点，那只要确保两个周期相同位置不同就行 
				{
					s[x]='0';
					s[x+p]='1';
				}
			}
		}
		else if(x+p>n)//如果这个"."在最后一个周期，就往前循环找 
		{             //这种情况判断很重要！我就曾经挂过这样一个点！ 
			while(m>=1)
			{
				if(s[m]!='.')
				{
					if(s[m]=='1')
					{
						s[x]='0';
						break;
					}
					else if(s[m]=='0')
					{
						s[x]='1';
						break;
					}
				}
				m-=p;
			}
		}
	}
	for(int i=1;i<=n;i++)//前面已经确保有不同的了，剩下的点就用0填充就行，想用1也可以 
	{
		if(s[i]=='.')
		{
			s[i]='0';
		}
		cout<<s[i];
	}
	return 0;//模拟完毕 
}
```

---

