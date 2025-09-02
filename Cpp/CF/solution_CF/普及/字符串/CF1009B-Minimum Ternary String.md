# Minimum Ternary String

## 题目描述

给定一个由 '0', '1', '2' 组成的字符串  $S$ 。可以交换相邻'0', '1'或'1', '2'的位置（例如：'12' - '21'  $\;$  '01' - '10'）请输出原字符串经过任意转换后字典序最小的字符串。原字符串长度不超过  $10^5$ 。

## 样例 #1

### 输入

```
100210
```

### 输出

```
001120
```

## 样例 #2

### 输入

```
11222121
```

### 输出

```
11112222
```

## 样例 #3

### 输入

```
20
```

### 输出

```
20
```

# 题解

## 作者：shurongwang (赞：9)


只模拟可能是会超时的。

通过仔细地读题我们可以知道，``0`` 和 ``1`` 可以交换，``1`` 和 ``2`` 可以交换，而 ``0`` 和 ``2`` 不可以交换。

也就是说 ``1`` 可以交换到整个字符串中任何一个位置。

那么，我们可以把所有的 ``1`` 取出，只剩下由 ``0`` 和 ``2`` 组成的字符串。

由于 ``0`` 和 ``2`` 不能交换，且要得到字典序最小的字符串，我们要把所有的 ``1`` 放在第一个 ``2`` 前。

然后要记得特判一下没有 ``2`` 的字符串。

```

#include <bits/stdc++.h>

#define loop(i, to)  for (num i = 0; i < to; ++i)

using namespace std;

int n, cnt, pos;
string dat, ans;

int main() {
    cin >> dat;
    loop (i, dat.size()) {
        if (dat[i] == '1') {
            ++cnt;
            continue;
        }
        ans += dat[i];
    }
    pos = ans.size();
    loop (i, ans.size()) {
        if (ans[i] == '2') {
            pos = i;
            break;
        }
    }
    loop (j, cnt) {
        ans.insert(ans.begin() + pos, '1');
    }
    cout << ans << endl;
}

```

以上。


---

## 作者：帅到报警 (赞：2)

### 【题意描述】
给出一串由 0, 1, 2 组成的数字串，现在要进行一些操作，使得他们的字典序最小。但只有两种可以选择的操作，一是交换相邻的 0 与 1，二是交换相邻的 "'1 与 2。求出操作完成后的序列。

### 【分析】
这道 B 题整整想了半个小时才想出来！！！

~~（是不是恐怖至极）~~

~~（是不是我太菜了）~~

首先我们知道这串数字只有 0， 1， 2， 而且 1 可以任意交换。那么我们先将 1 提出来，然后又因为 0 的字典序是最小的，所以只要在提出 1 后的数字串中找到第一个 2，在其前面插入一串的 1，那么字典序肯定是最小的。当然了，对于只有 1 或 0 或 2 的情况需要特判（可能没什么用，节省几个点的时间，~~毕竟 CF 的数据大家懂的~~~）

### 【核心代码】
1、先提取出 1，我是将 0 和 2 存进数组中，这样方便找
```cpp
for(int i = 0; i < len; i++)
{
	a[i + 1] = s[i] - '0';
	if(a[i + 1] != 1)
		b[++t] = a[i + 1];
}

```

2、小特判，如果只有 0 和 2 不能改变，直接输出；如果都是 1，也不用变，输出原字串
```cpp
if(t == len)
{
	cout << s;
	return 0;
}
else if(t == 0)
{
	cout << s;
	return 0;
}
```

3、先找到第一个 2，（本来我用 upper_bound 找第一个大于 1 的，结果炸了QwQ），然后如果没有 2，就是 pos 未找到，先输出提取出的 t 个 0，再输出剩下的 1；
```cpp
for(int i = 1; i <= t; i++)
	if(b[i] == 2)
	{
		pos = i;
		break;
	}
if(b[pos] < 1)
{
	for(int i = 1; i <= t; i++)
		printf("0");
	for(int i = 1; i <= len - t; i++)
		printf("1");
	return 0;
}
```

4、0， 1， 2 都有的情况：先前 pos - 1 个 0，再输出剩余的 1，最后输出 pos 到 t 的剩余数字。
```cpp
else
{
	for(int i = 1; i <= pos - 1; i++)
		printf("0");
	for(int i = 1; i <= len - t; i++)
		printf("1");
	for(int i = pos; i <= t; i++)
		printf("%d", b[i]);
}
```

### 【正解】
```cpp
#include <bits/stdc++.h>
#define N 1000010
using namespace std;

int len, pos, t;
int a[N], b[N];
string s;

int main()
{
// 	freopen("2335.in", "r", stdin);
// 	freopen("2335.out", "w", stdout);
	cin >> s;
	len = s.size();
	for(int i = 0; i < len; i++)
	{
		a[i + 1] = s[i] - '0';
		if(a[i + 1] != 1)
			b[++t] = a[i + 1];
	}
	if(t == len)
	{
		cout << s;
		return 0;
	}
	else if(t == 0)
	{
		cout << s;
		return 0;
	}
	for(int i = 1; i <= t; i++)
		if(b[i] == 2)
		{
			pos = i;
			break;
		}
	if(b[pos] < 1)
	{
		for(int i = 1; i <= t; i++)
			printf("0");
		for(int i = 1; i <= len - t; i++)
			printf("1");
		return 0;
	}
	else
	{
		for(int i = 1; i <= pos - 1; i++)
			printf("0");
		for(int i = 1; i <= len - t; i++)
			printf("1");
		for(int i = pos; i <= t; i++)
			printf("%d", b[i]);
	}
	
}
```

---

## 作者：Fearliciz (赞：1)

根据题目，我们可以得知以下两点：

+ `0` 和 `2` 的相对位置不会改变，因为只能交换 `1` 和 `0` 或者是 `1` 和 `2`。

+ `1` 的位置可以随意挪动。

那么，如何构造字典序最小的序列呢？

因为 `0` 和 `2` 的相对位置不变，所以我们可以不看他们，又因为 `1` 可以随意挪动，所以我们可以讲所有的 `1` 堆在字符串中的第一个 `2` 前面，让大的数尽可能往后挪，以确保字典序最小。

特别的，如果整个数列中没有 `2` 那么将所有的 `1` 放到最后即可。

代码部分：

这应该是最短小精悍的代码了。

```cpp
#include<bits/stdc++.h>
using namespace std;
string c; bool flag=1; //flag用来记录是否是第一个"2"
int main()
{
	cin>>c; int len=c.length(),cnt1=0;
	for(int i=0;i<len;i++) if(c[i]=='1') cnt1++;
	for(int i=0;i<len;i++){
		if(c[i]=='1') continue; //如果为"1"，直接跳过
		if(c[i]=='2'&&flag){ for(int j=1;j<=cnt1;j++) cout<<"1"; cout<<"2"; flag=0;} //在第一个"2"之前将所有的"1"输出
		else cout<<c[i];
	}
	if(flag) for(int j=1;j<=cnt1;j++) cout<<"1"; //特殊情况：没有"2"
}
```


---

## 作者：zengzhijie54188 (赞：1)

## 这道题最重要的是明确你的解题方法
#### 思路：
这道题就是让你把一窜字符串转化成字典序最小的字符串，并且题目给出的是只有三个数字成的，所以这道题我们可以先思考一下，想要字典序最小，也就是让Ascll顺序最小，所以我们可以把小的数尽量放前面，大的尽量放后面。我们先输入字符串，然后我们可以先把里面的$1$的个数先找出来，让$2$之前的$0$都先输出，有人可能会问，2之后的$0$怎么办呢，因为$2$不能和$0$调换，所以$2$之后的$0$只能原地不动。在前面依次输出$0$后遇到了$2$后，要使字典序最小，我们可以再把所有的$1$依次输出来，再来输出$2$，如果$2$后面有$0$，依然输出。

模拟以上做法，这道题就迎刃而解啦！
#### 提示
返回字符串长度属性（整数）： $s.length()$

进入下一重循环： $continue$

上AC代码（ c++ ）
```cpp
#include<bits/stdc++.h>
using namespace std ;
int ans ;
int k ;
int main()
{
	string s ;  
	cin >> s ; //输入字符串 
	for ( int i = 0 ; i < s.length() ; i++ )
	{
		if ( s[i] == '1' ) //统计字符串内1的个数 
	    {
            ans++ ;
        }
     }  
	for ( int i = 0 ; i < s.length() ; i++ )
    {			
		if ( s[i] == '0' ) //如果是0直接输出 
        {
        	cout << 0 ;
        	continue ; //不必往下走了 
 		} 
        if ( s[i] == '1' ) //如果是1直接进入下一重循环 
        {
            continue ;
        }
        if( s[i] == '2' ) //判断是否是2 
        {
             if ( k == false ) //再判断是否是第一个2 
            {
                for ( int j = 1 ; j <= ans ; j++ ) //如果是的话就把所有的1输出来 
                {
                	cout << 1 ;
                }
                k = true ; //记录下来 
            }
            cout << 2 ; //然后再直接输出2 
        }
    }
    if ( k == false ) //如果字符串中没有2，那就直接把所有的1输出来，不要漏掉这一步 
    {
        for ( int i = 1 ; i<=ans ; i++ )
        {
			cout << 1 ;
        }
	}
	return 0 ; //好习惯 
}
```
真心希望能帮助到大家！

---

## 作者：TRZ_2007 (赞：0)

**[题解 【CF1009B Minimum Ternary String】](https://www.luogu.com.cn/problem/CF1009B)**    
# Solution  

首先明确题目要你干什么：**原字符串经过任意转换后字典序最小的字符串**，那么就是让小的尽量排在前面，观察可行的交换方式，发现只有 ``0`` 不能和 ``2`` 交换，也就是说，这两个数字之间的**相对位置和顺序**是固定的，那么只需要考虑数字 ``1`` 的位置，显然，``1``应当放在``2``的前面``0``的后面。这题就做完了。  
但是如果你这样做，会 WA #6，为什么？因为这样子的话，如果你这字符串中没有 ``2``，那么你的 ``1`` 就不会被输出来，特判一下就可通过。

# Code  
```cpp
#include <cstdio>
#include <cctype>
#include <cstring>
using namespace std;

const int N = 1e5 + 9;

char ch[N],bt[N];
int len,p,flag;

int main() {
	scanf("%s",ch + 1); len = strlen(ch + 1);
	for(int i = 1;i <= len;i++) {
		if(ch[i] == '0' || ch[i] == '2') {
			bt[++p] = ch[i];
		}
	}
	for(int i = 1;i <= p;i++) {
		if(bt[i] == '2' && !flag) {
			for(int j = 1;j <= len - p;j++) putchar('1');
			flag = 1;
		}
		putchar(bt[i]);
	}
	for(int i = 1;i <= len;i++) {
		if(ch[i] == '2') flag = 114514;
	}
	if(flag != 114514) for(int i = 1;i <= len - p;i++) putchar('1');
	return 0;
}
```

---

## 作者：zxqwq (赞：0)

思路好像和大家的不一样，我先说我的结论：

1.如果这个序列没有同时出现 $0$ 与 $2$ 那就直接按照字典序排序

2.否则，我们记第一个 $2$ 出现的位置为 $k$  在这之前可以按字典序排序，在这之后一定是形如 `111112....2...2` ( `.` 表示的是 $0$ )

首先证明 $1$ ，这个是显然的一定满足字典序最小的贪心

然后我们证明 $2$ ，因为序列出现了 $2$ ，因此将它放在最后才是最优的，另外 $1$ 是可以和 $0,2$ 自由交换，因此我们一定可以把 $2$与$0$ 放在最后

```cpp
#include<headfile.h>

using namespace std;

const int maxn=100100;

char s[maxn];
int ans[maxn];
int n,m,bj=0,lk=0;

int main()
{
	register int i,j;
	scanf("%s",s+1);
	n=strlen(s+1);
	memset(ans,-1,sizeof(ans));
	for(i=1;i<=n;i++) 
	{
		if(s[i]=='2'&&!bj) 
		{
			bj=i; 
		}
		if(s[i]=='0'&&bj)
		{
			lk=i;
		}
	}
	int target=n;
	for(i=n;i>=bj;i--) 
	{
		if(s[i]=='0'||s[i]=='2') ans[target--]=s[i]-'0';
	}
	if(bj&&lk)
	{
		sort(s+1,s+bj);
		for(i=1;i<bj;i++) printf("%c",s[i]);
		for(i=bj;i<=n;i++) if(ans[i]==-1) printf("1"); else printf("%d",ans[i]);
		return 0;
	}
	else if(!(bj&&lk))
	{
		sort(s+1,s+n+1);
		for(i=1;i<=n;i++) printf("%c",s[i]);
		return 0;
	}
	return 0;
}

```


---

## 作者：HPXXZYY (赞：0)

首先我们来看一个**贪心**的思路：只要交换后能使原字符串的字典序更小，我们就交换，直到不能交换为止，比如这样：

```cpp
const int N=1e5+100;
char s[N];int n;bool flag;
int main(){
// 	freopen("t1.in","r",stdin);
	scanf("%s",s+1);
	n=strlen(s+1);
	do{
		flag=false;
		for(int i=1;i<n;i++)
			if (s[i]-s[i+1]==1){
				swap(s[i],s[i+1]);
				flag=true;
			}
	}while(flag);
	printf("%s",s+1);
	return 0;
}
```

然而这样做是有反例的：

比如原字符串是`201`，我们通过肉眼的模拟可以知道答案应该是`120`，但是在第一步交换`1`和`0`时，我们的程序认为它使得原字符串的字典序变大了，以至于没有交换而退出了程序。

所以，我们只能另寻思路。我们发现`1`是可以到达天涯海角的，所以我们把`1`全部提出来，剩下一个只有`0`和`2`的字符串，它是不可以交换的。但是我们可以把所有的`1`全部插入第一个`2`以前，这样得出来的答案一定是字典序最小的。

```cpp
string s,s1,r;int l,n;
int main(){
	freopen("t1.in","r",stdin);
	cin>>r;n=r.size();
	for(int i=0;i<n;i++)
		if (r[i]=='1') s1+=r[i];
		else s+=r[i];
	l=s.find('2');
	if (l==s.npos) cout<<s+s1<<endl;
	else{
		s.insert(l,s1);
		cout<<s<<endl;
	}
	return 0;
}
```

在我的第二个代码中用到了$STL$，这里解释一下一些函数，大家可以通过类比的思想知道它们的用途：

- `s.find('2')`：在字符串$s$中寻找第一个`2`的位置，若没有，则返回`string::npos`，即`s.npos`。

- `s.insert(l,s1)`：在$s$的第$l$个字符前插入$s1$。

- `s+s1,s+r[i]`：第一个语句相当于把$s1$插入在$s$的末尾，第二个语句相当于把$r[i]$插入在$s$的末尾，由此可见，如果要把一个字符串或字符插入在另一个字符串的末尾，就可以使用字符串的加法运算。但请注意，单单写`s+s1`并没有完成真正的插入操作，`s=s+s1`才完成了插入的操作。

最后，我给大家一个第一个程序无法通过但第二个程序可以通过的样例：

输入：`2010`，输出：`1200`

---

## 作者：小闸蟹 (赞：0)

```cpp
// 本题就是用的贪心，道理跟楼上几位dalao说的一样，因为'1'可以随意动，所以'1'是一个可以被放到任意地方的字符
// 我们首先对该字符串遍历一遍，这一遍主要统计字符'1'的个数以及该字符串内是否存在'2'
// 然后我们遵循如下的贪心策略：
// 对该字符串进行遍历，遇到'0'就输出'0'，遇到'1'就跳过，直到遇到第一个'2'，我们就将所有的'1'输出，然后再输出一个'2'
// 再接着（先前已经把所有的'1'都输出了），遇到'0'就输出'0'，遇到'1'就跳过，遇到'2'就输出'2'
#include <iostream>
#include <string>

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::string Str;
    std::cin >> Str;

    int One = 0, Zero = 0;
    bool HasTwo = false;
    for (const auto &c : Str)
    {
        if (c == '0')   // 统计'0'的个数
        {
            ++Zero;
        }
        else if (c == '1')   // 统计'1'的个数
        {
            ++One;
        }
        else if (c == '2')  // 统计是否有'2'
        {
            HasTwo = true;
        }
    }

    if (!HasTwo)    // 如果没有'2'，那么就先输出所有的'0'，再输出所有的'1'，然后直接退出程序
    {
        for (int i = 0; i < Zero; ++i)
        {
            std::cout << 0;
        }
        for (int i = 0; i < One; ++i)
        {
            std::cout << 1;
        }
        std::cout << std::endl;

        return 0;
    }

    bool Met = false;   // 标记是否第一次遇见'2'
    for (const auto &c : Str)
    {
        if (c == '0')   // 遇到'0'则输出
        {
            std::cout << 0;
        }
        else if (c == '1')  // 遇到'1'则跳过
        {
            continue;
        }
        else if (c == '2')
        {
            if (!Met)   // 第一次遇到'2'，则输出所有的'1'，再输出一个'2'
            {
                Met = true;

                for (int i = 0; i < One; ++i)
                {
                    std::cout << 1;
                }
                std::cout << 2;
            }
            else       // 不是第一次遇到'2'，则直接输出'2'
            {
                std::cout << 2;
            }
        }
    }
    std::cout << std::endl;

    return 0;
}
```

---

