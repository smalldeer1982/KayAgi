# Accordion

## 题目描述

题意简述

给出一个字符串，试在其中删除一些字符，使得最后的串变为满足以下条件的串且长度最大：

长度大于等于$4$；第一个字符为$'['$；最后一个字符为$']'$；第二个字符和倒数第二个字符为$':'$；其余字符全部为$'|'$．

## 样例 #1

### 输入

```
|[a:b:|]
```

### 输出

```
4
```

## 样例 #2

### 输入

```
|]:[|:]
```

### 输出

```
-1
```

# 题解

## 作者：Micnation_AFO (赞：12)

[原题链接](https://www.luogu.com.cn/problem/CF1101B)

大致思路：用`deque`对字符串进行维护：
1. 将队头元素出队直到队头元素为`[`。
1. 将尾头元素出队直到队尾元素为`]`。
1. 判断是否合法（即队列长度是否大于 $4$）。
1. 将队头、队尾的`[`与`]`分别出队。
1. 此时用相同方法处理`:`即可。
1. 最后统计队列中`|`的个数并输出。

AC 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long
deque<char> q;
string s;
int ans = 0;

signed main() {
    getline(cin, s);
    //处理'['
    for (int i = 0; i < s.size(); i++) q.push_back(s[i]);
    while (!q.empty() && !(q.front() == '[')) q.pop_front();
    while (!q.empty() && !(q.back() == ']')) q.pop_back();
    if (q.size() < 4) { cout << -1 << endl; return 0; }
    q.pop_front(), q.pop_back();
    //处理':'
    while (!q.empty() && !(q.front() == ':')) q.pop_front();
    while (!q.empty() && !(q.back() == ':')) q.pop_back();
    if (q.size() < 2) { cout << -1 << endl; return 0; }
    //统计答案
    for (; !q.empty(); q.pop_back())
        if (q.back() == '|') ans++;
    cout << ans + 4 << endl;//输出的时候别忘了加上首尾的'['、']'和两个':'
    return 0;
}

```

---

## 作者：zhy12138 (赞：6)

无脑模拟题~~

思路：

- 找出最左边的[:子串
- 找出最右边的:]子串
- 在中间找|的个数

ps:588个绿框看得人是真的舒服，信心受创时可以来做这道题

```cpp
#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cmath>
#include<iomanip>
#include<cstring>
#include<algorithm>
#include<ctime>
using namespace std;
string s;
int len,l=-1,r=-1,bj;
int main()
{
	cin>>s;
	len=s.length();
	for(register int i=0;i<len;++i)
		if(s[i]=='[')
		{
			l=i;
			break;
		}
	if(l==-1)
	{
		puts("-1");
		return 0;
	}
	bj=l;
	for(register int i=l+1;i<len;++i)
		if(s[i]==':')
		{
			l=i;
			break;
		}
	if(l==bj)
	{
		puts("-1");
		return 0;
	}
	for(register int i=len-1;i>=0;--i)
		if(s[i]==']')
		{
			r=i;
			break;
		}
	if(r==-1)
	{
		puts("-1");
		return 0;
	}
	bj=r;
	for(register int i=r-1;i>=0;--i)
		if(s[i]==':')
		{
			r=i;
			break;
		}
	if(r==bj)
	{
		puts("-1");
		return 0;
	}
	if(l>=r)
	{
		puts("-1");
		return 0;
	}
	int ans=4;
	for(register int i=l+1;i<r;++i)
		if(s[i]=='|')
			++ans;
	printf("%d\n",ans);
	return 0;
}

```

---

## 作者：HoshizoraZ (赞：6)

$Codeforces$ 的 $hacker$ 真是 $tql$，测试数据就有将近 $600$ 个，即便在原网站评测也花了5分多钟

这一题其实就是大模拟

蒟蒻的思路：

- 从头开始找出第一个左括号的位置，没有就把位置标记为字符串末
- 从结尾开始找出第一个右括号的位置，没有就把位置标记为 字符串首

- 冒号也同如上思路

- 如果第一个左括号（标记的）位置大于等于第一个右括号（标记的）位置，就输出 $-1$

- 如果两个中括号里面没有两个冒号（也就是从左括号向右开始搜索的第一个冒号的位置大于等于从右括号向左搜索到的冒号的第一个位置），也输出 $-1$

- 如果都合法，就统计冒号之间的 $"|"$ 的数量，在把数量加四输出

代码：
```
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

int i,j,k,l,len,ans;
char c[500010];			//定义一个字符数组 

int main()
{
	gets(c);
	len = strlen(c);	//字符串长度
	
	for(i=0;c[i]!='['&&i<len;i++);	//第一个左括号的位置 
	
	for(j=len-1;c[j]!=']'&&j>=0;j--);	//第一个右括号的位置 
	
	for(k=i+1;c[k]!=':'&&k<len-1;k++);	//在括号间从左搜索的第一个冒号的位置 
	
	for(l=j-1;c[l]!=':'&&l>k;l--);	//在括号间从右搜索的第一个冒号的位置 
	
	if(i>=j||l<=k)		//不合法就输出 -1 
		printf("-1\n");
	else
	{
		for(int x=k+1;x<l;x++)	//枚举区间
			if(c[x]=='|') ans++;  //统计数量 
            
		printf("%d\n",ans+4);	 //要加上两边各两个的符号 
	}
	return 0;
}
```

---

## 作者：decoqwq (赞：4)

让你求一个字符串是否包含一个子串$[::]$，$:$之间可以有无数多的$|$，求出子串最长长度，否则输出$-1$

从左到右先找一遍$[$，再从右到左找$]$，$:$同理，注意$]$在$[$右边，$::$在$[]$之间

```cpp
#include <bits/stdc++.h>
using namespace std;
char s[500010];
int main()
{
    cin>>s;
    int fir=-1,las=-1;
    int firr=-1,lass=-1;
    int qaq=strlen(s); 
    for(int i=0;i<qaq;i++)
    {
        if(s[i]=='[')
        {
            fir=i;
            break;
        }
    }
    for(int i=qaq-1;i>=0;i--)
    {
        if(s[i]==']')
        {
            las=i;
            break;
        }
    }
    if(fir==-1||las==-1)
    {
        cout<<"-1";
        return 0;
    }
    for(int i=0;i<qaq;i++)
    {
        if(s[i]==':'&&i>fir)
        {
            firr=i;
            break;
        }
    }
    for(int i=qaq-1;i>=0;i--)
    {
        if(s[i]==':'&&i<las&&i>firr)
        {
            lass=i;
            break;
        }
    }
    if(firr==-1||lass==-1)
    {
        cout<<"-1";
        return 0;
    }
    int ans=4;
    for(int i=firr+1;i<lass;i++)
    {
        if(s[i]=='|')
        {
            ans++;
        }
    }
    cout<<ans;
} 
```

---

## 作者：⚡小林子⚡ (赞：4)

这是目前题解中 `for` 使用最少的代码（一个）

久闻[此题](https://www.luogu.com.cn/problem/CF1101B)青青草原的美景，今天我就来瞅一瞅。

### 今天的前置芝士：

1. `string` 中的 `find` 函数：

```
string中find()返回值是字母在母串中的位置（下标记录），
如果没有找到，那么会返回一个特别的标记npos。
（返回值可以看成是一个int型的数）

```

摘自[这位大佬](https://www.cnblogs.com/wkfvawl/p/9429128.html)的博客。

2. `reverse` 函数

```
reverse函数功能是逆序（或反转），多用于字符串、数组、容器。头文件是#include <algorithm>

reverse函数用于反转在[first,last)范围内的顺序（包括first指向的元素，不包括last指向的元素），reverse函数无返回值
```

摘自[这位大佬](https://www.cnblogs.com/yuanch2019/p/11591995.html)的博客。

3. `string` 中的 `substr` 函数

```
返回一个新建的初始化为string对象的子串的拷贝string对象。

子串是，在字符位置pos开始，跨越len个字符（或直到字符串的结尾，以先到者为准）对象的部分。
```

摘自[这位大佬](https://blog.csdn.net/sunshihua12829/article/details/50484966)的博客。

### 正文：

期望的字符串中至少得有 `[::]` 这四个字符，而且得按顺序排列。

然后才是 `|` 的问题。

1. `[` 字符：

要找最靠前的，直接 `find` 即可。

Code：

```cpp
if(str.find('[')!=string::npos)
    bz=str.find('[');
else
    codefinish;
```

注： `codefinish` 是我自定义的宏，长这样：

```cpp
#define codefinish {cout<<-1;return 0;}
```

2. `]` 字符：

要找最靠后的，但是 `find` 找的是第一个啊？

这时 `reverse` 就有用了，用一个 `rstr` 存储原字符串的倒序即可。

Code：

```cpp
if(rstr.find(']')!=string::npos)
    ez=rstr.find(']');
else
    codefinish;
```

但是还是得注意一点，搜出来的是 `rstr` 的位置，要将其转换成 `str` 的性相对位置。

Code：

```cpp
ez=str.size()-1-ez;
```


3. 细节处理：

特判这两个结果的位置的顺序：

Code：

```cpp
if(bz>ez)
    codefinish;
```

4. 第一个 `:` 字符：

要求满足在两个中括号之间，且首次出现。

第一个操作用到了 `substr` 函数。

第二个正常 `find` 处理。

Code：

```cpp
str=str.substr(bz,ez-bz+1);
rstr=str;
reverse(rstr.begin(),rstr.end()); 
if(str.find(':')!=string::npos)
    bm=str.find(':');
else
    codefinish;
```

5. 第二个 `:` 字符：

要求满足在两个中括号之间，且最后一次出现。

用在 4 中处理好的 `rstr` 查找即可。

注意在 2 中讲到的相对位置的处理。

Code：

```cpp
if(rstr.find(':')!=string::npos)
		em=rstr.find(':');
	else
		codefinish;
	em=str.size()-1-em;
```

6. 细节处理

注意要特判两个位置相同的情况。

Code：

```cpp
if(bm>=em)
    codefinish;
```

7. 找 `|`

在两个 `:` 之间 `for` 即可。

还有：如果前面挺过来了， `ans` 要 `=4` 。

Code：

```cpp
ans=4;
for(int i=bm+1;i<=em-1;i++)
    if(str[i]=='|')
        ans++;
```

这道题到这里重点就讲完了，还有就是输入输出和变量定义了。

代码不贴了，因为每一个重点都给了代码。

AC记录：[R33041767](https://www.luogu.com.cn/record/33041767)

做题解不易，麻烦给个赞呗！

---

## 作者：StayAlone (赞：2)

此题青青草原的美誉真不是白来的，绿色果然让眼睛舒适~

我的微压行代码 15 行，不压行也不超 20 行。

### 思路

找到最左边的 `[` 和最右边的 `]`，再找到这两个符号之间的两个 `:`，然后输出两个 `:` 之间 `|` 的数量加 $4$。  

如果**有某个字符找不到或数量不够**，输出 $-1$；

### 前置知识

1. $\texttt{reverse}$ 函数。  
该函数无返回值，其作用是将某个字符串翻转。  
用法：``reverse(s.begin(), s.end());``
1. $\texttt{find}$ 函数。  
该函数有两个参数，会返回字符串中某个位置之后的**第一个**要找的字符串或字符的位置，如果**不存在**，返回 $-1$，若第二个参数不填，默认为 $0$。  
用法：``s.find(':', 3);`` 将会返回下标 $3$ 开始**第一个**出现的 `:` 的下标，不存在返回 $-1$(string :: npos 亦可)。

### 代码细讲

输入后，我们就能进行第一个判断：注\*1
```cpp
cin >> s; int len = s.length();
if (len < 4 || !~s.find('[') || !~s.find(']') || !~s.find(':'))
	return puts("-1"), 0;
```
如果 $len < 4$ 或找不到 `:`、`[`、`]`、`:` 中的任意一个，直接输出 $-1$ 并返回 $0$。

接下来拿另一个字符串存储翻转后的字符串。这里我的处理是这样的：  
``s2 = s, reverse(s.begin(), s.end()); swap(s, s2);``   

**这样 $s$ 还是输入的原字符串，$s2$ 是翻转后的字符串。**  

现在我们用 $l$ 表示最左边的 `[`，$r$ 表示最右边的 `]`。但我们知道，$\texttt{find}$ 函数只会返回最左边的，这时候翻转的字符串的作用就是：**翻转后的字符串最左边的那个就是翻转前最右边的。**  

``int l = s.find('['), r = len - s2.find(']') - 1;``

而找到后要用 ``len - s2.find(']') - 1`` 才能得到这个位置在原字符串中的位置。  

接下来我们用 $l2$ 表示 `:` 在 $l$ 之后的第一个位置，$r2$ 表示 `:` 在 $r$ 之前的最右的一个位置。 

``int l2 = s.find(':', l), r2 = len - s2.find(':', -r - 1 + len) - 1;``  

为什么 $\texttt{s2.find}$ 函数的第二个参数是 $-r - 1 + len$ 呢？这个参数不该是 $\texttt{s2.find(']'))}$ 吗？  
我们来看看：``r = len - s2.find(']') - 1``，看到这里就明了了：``s2.find(']') = -r - 1 + len``。我们不用**浪费 $O(n)$ 的时间复杂度**去重复计算。  

现在迎来第二个判断：  
``if (l > r || !~l2 || !~(-r2+len-1) || l2 >= r2) return puts("-1"), 0;``  

如果 $l > r$ 或在 $l$ 之后找不到 `:` 或在 $r$ 之前找不到 `:` 或 $l2 \geqslant r2$，直接输出 $-1$ 并返回 $0$。  

$l$ 不可能等于 $r$，因为这两个符号不一样，不会在同一个位置出现。  

$l2 = r2$ 时说明两个中括号之间**有且仅有**一个 `:`；$l2 > r2$ 时说明两个 `:` 中**至少有一个**在两个中括号外。  

判断 $-r2+len-1 \neq -1$ 相当于 $\texttt{s2.find(':', -r - 1 + len)} \ne -1$，其道理前面已经解释过。  

到现在，这个串就**一定是合法的**了。那就寻找两个 `:` 之间有多少 `|`，用 $cnt$ 表示，再将 $cnt + 4$ 输出即可。  

#### 注：判断中写到的符号，`!~x` $\Leftrightarrow$ `x == -1`。

[AC code记录](https://www.luogu.com.cn/record/51430454)

```cpp
#include <bits/stdc++.h>
using namespace std;
string s, s2; int cnt;

int main()
{
	cin >> s; int len = s.length();
	if (len < 4 || !~s.find('[') || !~s.find(']') || !~s.find(':')) return puts("-1"), 0;
	s2 = s, reverse(s.begin(), s.end()); swap(s, s2);
	int l = s.find('['), r = len - s2.find(']') - 1,
		l2 = s.find(':', l), r2 = len - s2.find(':', -r - 1 + len) - 1;
	if (l > r || !~l2 || !~(-r2+len-1) || l2 >= r2) return puts("-1"), 0;
	for (int i = l2; i <= r2; ++i) cnt += s[i] == '|';
	return printf("%d", cnt + 4), 0;
}
```

---

## 作者：_Harrisonwhl_ (赞：2)

## 本人第一道AC的RemoteJudge题。
这道题很明显是一道大模拟,$s$ 的长度 $≤5\times10^5$,可以放心  `for` 循环枚举或模拟，枚举（模拟）思路：

从左边依次循环遍历找 " [ " 和 " $:$ ",再从右边找 " ] " 和 " $:$ ",如果过了开头或结尾的符号的位置限制（即左侧的 $:$ 占用了右侧 " $:$ " 的最右侧位置），可以不用继续寻找，直接输出 $-1$ 并 `return 0` 跳出主函数。

这题唯一的坑：" [ " 和 " $:$ " 不一定相邻。

枚举 " [ " 的代码：

```cpp
  bool flag = 0;
  int frpos;
  for (int i = 0;i < s.size() - 3;i++)
  {
      if (s[i] == '[')
      {
          frpos = i;//记录位置。
          flag = 1;//标记找到了。
          break;
      }
  }
  if (!flag)//如果没找到。
  {
      cout << -1;
      return 0;//直接离开。
  }
```
枚举右侧 " ] "
```cpp
	int bkpos;
	flag = 0;
    for (int i = s.size() - 1;i >= 3;i--)
    {
        if (s[i] == ']')
        {
            bkpos = i;
            flag = 1;
            break;
        }
    }
    if (!flag)
    {
        cout << -1;
        return 0;
    }
```
枚举右侧 " $:$ "
```cpp
	int bk2;
	flag = 0;
    for (int i = bkpos - 1;i >= frpos + 2;i--)
    {
        if (s[i] == ':')
        {
            bk2 = i;
            flag = 1;
            break;
        }
    }
    if (!flag)
    {
        cout << -1;
        return 0;
    }
```
枚举左侧 " $:$ "
```cpp
	int fr2;
	flag = 0;
    for (int i = frpos + 1;i <= bk2 - 1;i++)
    {
        if (s[i] == ':')
        {
            fr2 = i;
            flag = 1;
            break;
        }
    }
    if (!flag)
    {
        cout << -1;
        return 0;
    }
```
检查中间是否全是 " $|$ ",如果不是，应减长度,也就是模拟删去的步骤。
```cpp
	int l = bk2 - fr2 + 3;
    for (int i = fr2 + 1;i <= bk2 - 1;i++)
    {
        if (s[i] != '|') l--;
    }
```
完整代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
string s;
int main()
{
	cin >> s;
    bool flag = 0;
    int frpos,bkpos,fr2,bk2;
    for (int i = 0;i < s.size() - 3;i++)
    {
        if (s[i] == '[')
        {
            frpos = i;
            flag = 1;
            break;
        }
    }
    if (!flag)
    {
        cout << -1;
        return 0;
    }
    flag = 0;
    for (int i = s.size() - 1;i >= 3;i--)
    {
        if (s[i] == ']')
        {
            bkpos = i;
            flag = 1;
            break;
        }
    }
    if (!flag)
    {
        cout << -1;
        return 0;
    }
    flag = 0;
    for (int i = bkpos - 1;i >= frpos + 2;i--)
    {
        if (s[i] == ':')
        {
            bk2 = i;
            flag = 1;
            break;
        }
    }
    if (!flag)
    {
        cout << -1;
        return 0;
    }
    flag = 0;
    for (int i = frpos + 1;i <= bk2 - 1;i++)
    {
        if (s[i] == ':')
        {
            fr2 = i;
            flag = 1;
            break;
        }
    }
    if (!flag)
    {
        cout << -1;
        return 0;
    }
    int l = bk2 - fr2 + 3;//计算长度
    for (int i = fr2 + 1;i <= bk2 - 1;i++)
    {
        if (s[i] != '|') l--;//如果中间有不是｜的，长度-1
    }
    cout << l;
    return 0;
}
```

---

## 作者：Mistybranch (赞：2)

[传送门](https://www.luogu.com.cn/problem/CF1101B)

题目大概意思是：给你一个长度不超过 $5 \times 10^5$ 的字符串，求这个字符串中长度最大的形如$\texttt{[:||...||:]}$的字符串的长度。

因为字符串长度只有 $5 \times 10^5$，所以用几个 for 模拟即可。下面是具体思路：

- 从左往右找出现在字符串中的第一个$\texttt{[}$字符的位置 $l_1$，如果找不到则无解。

```cpp
for (l = 1; l <= strlen(s + 1); l++) {
	if (s[l] == '[') {
		break;
	}
}

//printf("%d\n", l);

if (l == strlen(s + 1) + 1) {
	printf("-1\n");
    return 0;
}
```

- 从右往左找出现在字符串中的第一个$\texttt{]}$字符的位置 $r_1$，如果找不到则无解。**注意 $l_1 < r_1$。**

```cpp
for (r = strlen(s + 1); r > l; r--) {
	if (s[r] == ']') {
		break;
	}
}

//printf("%d\n", r);

if (r == 0) {
	printf("-1\n");
    return 0;
}
```

- 从左往右找出现在字符串中的第一个$\texttt{:}$字符的位置 $l_2$，如果找不到则无解。**注意 $l_1 < l_2 < r_1$。**

```cpp
for ( ; l < r; l++) {
	if (s[l] == ':') {
		break;
	}
}

//printf("%d\n", l);

if (l == r) {
	printf("-1\n");
    return 0;
}
```

- 从右往左找出现在字符串中的第一个$\texttt{:}$字符的位置 $r_2$，如果找不到则无解。**注意 $l_2 < r_2 < r_1$。**

```cpp
for ( ; r > l; r--) {
	if (s[r] == ':') {
		break;
	}
}

//printf("%d\n", r);

if (r == l) {
	printf("-1\n");
    return 0;
}
```

- 现在最终的字符串已经有四个字符了，接着从 $l_2$ 到 $r_2$ 之间看有多少个字符$\texttt{|}$，每查询到一个字符结果字符串长度加一。

```cpp
ans = 4;

for (int i = l; i <= r; i++) {
	if (s[i] == '|') {
		ans++;
	}
}
```
完整代码：
```cpp


#include <bits/stdc++.h> 

char s[500010];
int ans;

int main () {
	scanf("%s", s + 1);

	int l, r;
	
	for (l = 1; l <= strlen(s + 1); l++) {
		if (s[l] == '[') {
			break;
		}
	}
	
//	printf("%d\n", l);
	
	if (l == strlen(s + 1) + 1) {
		printf("-1\n");
        return 0;
	}
	
	for (r = strlen(s + 1); r > l; r--) {
		if (s[r] == ']') {
			break;
		}
	}
	
//	printf("%d\n", r);
	
	if (r == 0) {
		printf("-1\n");
        return 0;
	}
	
	for ( ; l < r; l++) {
		if (s[l] == ':') {
			break;
		}
	}
	
//	printf("%d\n", l);
	
	if (l == r) {
		printf("-1\n");
        return 0;
	}
	
	for ( ; r > l; r--) {
		if (s[r] == ':') {
			break;
		}
	}
	
//	printf("%d\n", r);
	
	if (r == l) {
		printf("-1\n");
        return 0;
	}
	
	ans = 4;
	
	for (int i = l; i <= r; i++) {
		if (s[i] == '|') {
			ans++;
		}
	}

    printf("%d\n", ans);
	
	return 0;
}
```


---

## 作者：tribool4_in (赞：1)

思路很显然，分三步：

1. 首先找到第一个 ```[``` 和最后一个 ```]``` ；
2. 再在它们之间找第一个 ```:``` 和 最后一个 ```:``` ；
3. 最后再在两个冒号之间找有多少个 ```|``` 然后加 4 即可。

当然，如果第一、二步没找到，可以直接输出 ```-1```。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
char s[500010];
int main() {
	scanf("%s", s + 1);
	int len = strlen(s + 1);
	int l, r, ll, rr;
	for (l = 1; (l <= len) && (s[l] != '['); l++);
	for (r = len; (r > 0) && (s[r] != ']'); r--);
	for (ll = l + 1; (ll < r) && (s[ll] != ':'); ll++);
	for (rr = r - 1; (rr > ll) && (s[rr] != ':'); rr--);
	if (l >= r || ll >= rr) {
		printf("-1\n");
		return 0;
	}
	int cnt = 4;
	for (int i = ll + 1; i < rr; i++) {
		if (s[i] == '|') cnt++;
	}
	printf("%d\n", cnt);
	return 0;
}

```


---

## 作者：hanyuchen2019 (赞：1)

## xxs发题解 第 $8$弹

发现了一件奇奇怪怪的事情：全场**清一色**的C++题解！

所以我要来一篇C语言题解！

---

思路：

1.从左边开始遍历先找 `[`，再找 `:`  

2.从右边开始遍历先找 `:`，再找 `]`

3.遍历两个 `:` 之间有多少个 `|`，+4输出。

做做看吧！

注意：**这题有超多坑点**！

---

如果你样例过了，但WA了，来看看我的自造 Hack 数据：

\#1

input: `[:]`

ans: `-1`

\#2

input: `:]:|:[:`

ans: `-1`

\#3

input: `|[|:|:|]|`

ans: `5`

\#4

input: `[|[|:|:|:|:|]|]`

ans: `7`

---

### 现在是讲解时间~

直接上代码，讲解都在注释里
```
#include<stdio.h>//不解释
char a[500005];//字符串数组
int l,r,m1,m2,length;//变量，分别对应'[',']'和两个冒号的位置
#define OVER {printf("-1");return 0;}//一个宏，作用是输出无解并结束程序
int main()
{
	scanf("%s",a);//输入（不要“&”！）
	
	for(length=0;length<500001&&a[length]!=0;length++);//寻找'\0'(结束位置，刚好也是字符串长度)
	
	for(l=0;l<length&&a[l]!='[';l++);//找左括号
	
	if(l>=length)OVER//判断边界，后面的同理
	
	for(m1=l+1;m1<length&&a[m1]!=':';m1++);//找第一个冒号
	
	if(m1>=length)OVER
	
	for(r=length-1;r>=m1&&a[r]!=']';r--);//找右括号 
	
	if(r<m1)OVER//位置错乱，再见
	
	for(m2=r-1;m2>m1&&a[m2]!=':';m2--);//找第二个冒号
	
	if(m2<=m1)OVER//注意：两个冒号一定不能在一起！
	
	int ans=4;//先把[::]四个字符算上
	
	for(int i=m1+1;i<m2;i++)if(a[i]=='|')ans++;//找两个冒号直接有多少'|'
	
	printf("%d",ans);//输出
	
	return 0;
}
```
如果你AC了，记得点个赞再走8~

---

## 作者：SIXIANG32 (赞：1)

久闻此题青青草原的美誉，今天才AC掉。  


------------
  
这道题可以分析成一个个子问题：  
- 子问题1：把“\[”变成第一个字符。  
- 子问题2：把“\]”变成最后一个字符。
- 子问题3：把一个“:”变成第二个字符。
- 子问题4：把一个“:”变成倒数第二个字符。  
- 子问题5：统计两个“:”之间的“|”的数量。


分析完了这些问题，我们要解决它们：  

- 子问题1：得到第一个“\[”的位置，删除前面的字符。查找我们可以用```string```类型中的```find_first_of('[')```来实现，删除就用```erase```函数即可。
- 子问题2：得到最后一个“\]”的位置，删除前后的字符。为什么是最后呢因为防止中间就有“\]”。查找我们可以用```string```类型中的```find_last_of(']')```来实现，删除同上。 
- 子问题3：与第一个相同，只不过找的是第一个“：”并不删除。
- 子问题4：与第二个相同，只不过找的是最后一个“：”并不删除。  
- 子问题5：从第一个“：”到最后一个“：”遍历字符串，如果是“|”答案+1。

注意最后输出答案要+4（加上“\[”、“\]”、“:”、“:”）。  
还有一些小小的细节，比如子问题4的查找需要截取从第一个“:”到最后的子串查找不然会有bug，最后遍历要加上第一个“:” 的位置再加上1。  
最后代码实现：  
```cpp
#include<iostream>
#include<string>
#define goodbye {cout<<-1;return 0;}
using namespace std;
int main()
{
	int sum=2;//我这本来就是2代表“[”和“]”
	string str;
	cin>>str;
	if(str.find_first_of('[')!=string::npos)str.erase(0,str.find_first_of('['));//子问题1
    else goodbye
    if(str.find_last_of(']')!=string::npos)str.erase(str.find_last_of(']')+1,str.size()-1);//子问题2
    else goodbye
    int posf,posl;
    if(str.find_first_of(':')!=string::npos)posf=str.find_first_of(':');//子问题3，posf是第一个“:”出现的位置
    else goodbye
    if(str.substr(posf+1,str.size()-1).find_last_of(':')!=string::npos)posl=posf+1+str.substr(posf+1,str.size()-1).find_last_of(':');//子问题4，posl是最后一个“:”出现的位置
    else goodbye
    sum+=2;//再+2
    for(int p=posf;p<=posl;p++)//遍历
    	if(str[p]=='|')sum++;
    if(sum>=4)cout<<sum<<endl;//输出
    else goodbye
    return 0;
}
```

---

## 作者：Lish_Xizse (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1101B)

### 初始想法
第一阶段：不断从左往右找 ```[``` ，如果有的话，就进入第二阶段，没有的话就输出 ```-1``` 。

第二阶段：不断从右往左找 ```]``` ，如果有的话，就进入第三阶段，没有的话就输出 ```-1``` 。

第三阶段：不断从左往右找 ```:``` ，如果有的话，就进入第四阶段，没有的话就输出 ```-1``` 。

第五阶段：不断从右往左找 ```:``` ，如果有的话，就进入第六阶段，没有的话就输出 ```-1``` 。

第六阶段：从第三阶段的结束部分，到第四阶段的结束部分，不断寻找 ```|``` ，然后将 ```|``` 的数量加 ```4``` 后输出（因为还要包括首末那四个字符，所以要加上 ```4``` ）。

代码实现：
```
#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
char ch[500010];
int sum;
int main()
{
    scanf("%s",&ch);
    int len=strlen(ch);
    for(int i=0;i<len;i++){
        if(ch[i]=='['){
            for(int j=len-1;j>=0;j--){
                if(ch[j]==']'){
                    for(int k=i+1;k<len-1;k++){
                        if(ch[k]==':'){
                            for(int l=j-1;l>k;l--){
                                if(ch[l]==':'&&!(i>=j||l<=k)){
                                    for(int m=k+1;m<l;m++){
                                        if(ch[m]=='|')sum++;
                                    }
                                    printf("%d",sum+4);
                                    return 0;
                                }
                            }
                        }
                    }
                }
            }  
        }
    }
    printf("-1");
    return 0;
}
```
五重循环，不[T](https://www.luogu.com.cn/record/57897548)掉才怪呢。

看来我们得想另外的办法了。


------------

### 分析和思路
如果我们把每次循环的找到后终止位置记下来，岂不是省了很多麻烦？

我们来看一下：

1. 从左往右直到找到 ```[``` 或者到达了字符串末，标记所在位置。
1. 从右往左直到找到 ```]``` 或者到达了字符串首，标记所在位置。
1. 从左往右直到找到 ```:``` 或者到达了字符串末，标记所在位置。
1. 从右往左直到找到 ```:``` 或者到达了字符串首，标记所在位置。
1. 判断是 ```[``` 小于 ```]``` 或者左边的 ```:``` 小于右边的 ```:``` ，那么就从左边的 ```:``` 一直寻找到右边的 ```:``` ，统计 ```|``` 的个数，加 ```4``` 后输出。否则输出 ```-1``` 。

思路都理清了，一步一步去模拟就好了。



------------

### 完整 ```AC``` 代码：
```
#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
int i,j,k,l;
int sum;
char ch[500010];
int main(){
    scanf("%s",&ch);
    int len=strlen(ch);
    for(i=0;ch[i]!='['&&i<len;i++);
    for(j=len-1;ch[j]!=']'&&j>=0;j--);
    for(k=i+1;ch[k]!=':'&&k<len-1;k++);
    for(l=j-1;l>k;l--){
        if(ch[l]==':'){
            break;
        }
    }
    if(!(i>=j||l<=k)){
        for(int i=k+1;i<l;i++){
            if(ch[i]=='|')sum++; 
        }
        printf("%d",sum+4);	
    }else{
        printf("-1");
    }
    return 0;
}
```


---

## 作者：Iam1789 (赞：0)

~~为了看青青草原来做了这个题~~

一个很水的模拟题，建议降橙/红。

对于这道题，我们先从右往左依次找到 `]` 和 `:`，记录下 `:` 的位置。再依次从左往右寻找 `[`，`:` 和 `|`, 到上次搜索时 `:` 的位置停止，期间记录他们的长度。如果长度没达到 $4$ 直接输出 $-1$ 即可。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
string s;
int main()
{
	cin>>s;
	int len=s.length();
	long long n=0;
	int jd=0;
	int jl=0;
	for(register int i=len-1;i>=0;--i)
	{
		if(jd==0&&s[i]==']')
		{
			++jd;
			++n;
		}
		else if(jd==1&&s[i]==':')
		{
			++jd;
			++n;
			jl=i;
			break;
		}
	}
	if(jd<2)
	{
		cout<<-1;
		return 0;
	}
	jd=0;
	for(register int i=0;i<len;++i)
	{
		if(i==jl)
		break;
		if(jd==0&&s[i]=='[')
		{
			++jd;
			++n;
		}
		else if(jd==1&&s[i]==':')
		{
			++jd;
			++n;
		}
		else if(jd==2&&s[i]=='|')
		{
			++n;
		}
	}
	if(jd<2)
	cout<<-1;
	else
	cout<<n;
	return 0;
}
```


---

## 作者：billzd (赞：0)

这题只需要一次大模拟就好了。

前往后遍历找 $[$，后往前找 $]$。

再次前往后遍历找 $:$ ，后往前找 $:$ 。

判断是否合法，输出答案即可。
### 代码：
```c
#include<string.h>
#include<stdio.h>
int i,j,k,l,x,ans=4,p;//ans=4因为必须有一个[::]的情况，中间才能插入|。
char ch[500010];
int main(){
	gets(ch);
	x=strlen(ch);
	for(i=0;i<x&&ch[i]!='[';i++);//找[。
	for(j=x-1;~j&&ch[j]!=']';j--);//找]。
	for(k=i+1;k<j&&ch[k]!=':';k++);//找第一个:。
	for(l=j-1;l>k&&ch[l]!=':';l--);//找第二个:。
	if(i>=j||l<=k){//判断是否合法
		puts("-1");
		return 0;
	}
	for(p=k+1;p<l;p++)
		if(ch[p]=='|') ans++;//加上能加上的|。
	printf("%d\n",ans); //输出答案。
	return 0;//华丽的结束。
}
```


---

## 作者：Starw (赞：0)

[青青草原](https://www.luogu.com.cn/record/54669388)名不虚传。

### 思路：

模拟即可，坑也不多，但要注意以下几点：

1. 从前往后和从后往前找 `:` 的时候,要先找到过 `[` 或 `]` 后再找到的，才算是合法的。

2. 最后答案要加 $4$（原因注释中有详细解释）。

### 代码：

```cpp
#include<bits/stdc++.h>//万能头 
#define re register int//宏定义register int为re
using namespace std;
char s[500005];
int main(){
	int l,fz=-1,fm=-1,lz=-1,lm=-1,ans=0;
	cin>>s;
	l=strlen(s);
	for(re i=0;i<l;i++){//从前往后遍历 
		if(s[i]=='['&&fz==-1)fz=i;
		//如果找到了'['且之前没有找到过它,就说明找到了第一个它,储存它的位置 
		if(s[i]==':'&&fm==-1&&fz!=-1)fm=i;
		//如果找到了':'且之前没有找到过合法的它,且之前已经找到了第一个'[',就说明找到了第一个合法的它,储存它的位置 
		if(fz!=-1&&fm!=-1)break;//如果都找到了,就退出循环 
	}
	if(fz==-1||fm==-1){//如果没有找到'['或合法的':'就输出-1,结束程序 
		printf("-1");
		return 0;
	}
	for(re i=l-1;i>=0;i--){//从后往前遍历
		if(s[i]==']'&&lz==-1&&i!=fz)lz=i;
		//如果找到了'['且之前没有找到过它,就说明找到了最后一个它,储存它的位置 
		if(s[i]==':'&&lm==-1&&i!=fm&&lz!=-1)lm=i;
		//如果找到了':'且之前没有找到过合法的它,且之前已经找到了最后一个']',就说明找到了最后一个合法的它,储存它的位置
		if((lz!=-1&&lm!=-1)||i<=fz)break;//如果都找到了或i已经小于第一个'[',就退出循环
	}
	if(lz==-1||lm==-1){//如果没有找到最后一个的']'或非第一个的合法的':'就输出-1,结束程序
		printf("-1");
		return 0;
	}
	for(re i=fm+1;i<lm;i++)//在第一个合法的':'和最后一个合法的':'中间找'|' 
		if(s[i]=='|')ans++;
	printf("%d",ans+4);//输出找到的'|'的个数加4(第一个'['和最后一个']'还有第一个和最后一个合法的':') 
	return 0;//好习惯 
}``


---

## 作者：fls233666 (赞：0)

想要符合要求的串最长，我们可以**贪心**一下。大致思路是：找到最左边的 $\texttt{"[:"}$ 与最右边的 $\texttt{":]"}$，这一对方括号距离最远，能包括的 $\texttt{"|"}$ 显然最多，而其它的方括号对构成的串显然没有最远的这一对优。

基于这个思想，我们来实现代码。代码大致分为三个部分：

1. 从左到右先扫一遍输入的字符串，确定第一个 $\texttt{"[:"}$ 出现的位置，记为 $l$。如果找不到 $\texttt{"[:"}$ 输出 $-1$；
2. 从右到左扫一遍 $[l,|s|]$ 之间的字符，确定第一个 $\texttt{":]"}$ 出现的位置，记为 $r$。如果找不到 $\texttt{":]"}$；
3. 扫一遍 $[l,r]$ 之间的字符，统计 $\texttt{"|"}$ 出现的次数，记为 $cnt$，则最终答案为 $cnt+1$。

至此，此题得解。下面放上代码：

```cpp
#include<iostream>
#include<cstdio>
#include<string>
#include<vector>
#define rgt register int
using namespace std;

const int mxn = 5e5+5;

string str;
int ls,l,r,cnt;

int main(){
	bool fk;
	cin>>str;
	ls=str.size();
    
	fk=false;
	for(rgt i=0;i<ls;i++){
		if(str[i]=='['&&!fk)
			fk=true;
		if(str[i]==':'&&fk){
			l=i;  //找到最左边的 [:，标记位置
			break; 
		}
	}
    
	if(!l){
		printf("-1");
		return 0;
	}  //未找到，无解
    
	fk=false;
	for(rgt i=ls-1;i>l;i--){
		if(str[i]==']'&&!fk)
			fk=true;
		if(str[i]==':'&&fk){
			r=i;  //找到最右边的 :]，标记位置
			break; 
		}
	}
    
	if(!r){
		printf("-1");
		return 0;
	}  //未找到，无解
    
	for(rgt i=l;i<=r;i++)
		if(str[i]=='|')
			cnt++;
	cout<<cnt+4;  //统计 [l,r] 之间的 | 数量，加 4 得到答案
	return 0;
}
```


---

## 作者：封禁用户 (赞：0)

题目传送>>[CF1101B](https://www.luogu.com.cn/problem/CF1101B)  
### 题意简述：  
- 给定一个字符串，求在删除一些字符后最长的符合以下条件的串长:  
  1. 长度大于等于 $4$；  
  1. 第一个字符为 "\["，最后一个字符为 "\]"；  
  1. 第二个字符和倒数第二个字符为 ":"；  
  1. 其余字符全部为 "|"；  
- $1 \le|s| \le 500000$；  
- 若无符合条件的串，输出 $-1$；  

### 题目分析：  
对于求串，我们只需对于输入的串先分别从串两端向中推进寻找其最靠端的 "\[" 和 "\]"，并记录其位置，然后再分别以之前得的 "\[" 和 "\]" 为端向中推进寻找其最靠两端的 ":"，随后再在之前求得的两个 ":" 间枚查留 "|" 即可。当然，对于符合条件的串不存在的情况，如果给定的串无前后 "\[" 和 "\]" 匹配（无 "\[" 或 "\]" 、求得 "\[" 的位置大于 "\]" 的位置），或无前后 ":" 和 ":" 匹配（无 ":" 或 无两个 ":"），则无符合条件的串。  
### Code：  
```cpp
#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
using namespace std;
int find();    //声明找对象函数
string s;   //定义给定串
int len, qk, hk, qm, hm, ans = 0;   //定义给定串长，前括号位置，后括号位置，前冒号位置，后冒号位置，符合条件的串长
int find(int b, int e, int op, char o)   //找对象函数，参数为：起始位置，结束位置，找对象方式，对象
{
	int r = -1;   //初始化返回值，以便判断后续判断是否存在对象
	if (op == 1)   //找对象方式为从前向中推进
	{
		for (int i = b; i < e; i++)
		{
			if (s[i] == o)
			{
				r = i;   //找到对象，记录位置
				break;
			}
		}
	}
	else if (op == 2)   //找对象方式为从后向中推进
	{
		for (int i = e - 1; i >= b; i--)
		{
			if (s[i] == o)
			{
				r = i;   //找到对象，记录位置
				break;
			}
		}
	}
	return r;   //返回对象状态
}
int main()
{
	ios::sync_with_stdio(0);   //关同步流加速cin输入和cout输出
	cin >> s;
	len = s.length();   //计算给定串的长
	qk = find(0, len, 1, '[');   //找前括号得状态
	hk = find(0, len, 2, ']');   //找后括号得状态
	if (qk > hk || qk == -1 || hk == -1)   //已不符条件
	{
		cout << "-1";
		return 0;   //输出－1，直接结束整个程序
	}
	qm = find(qk + 1, hk, 1, ':');   //找前冒号得状态
	hm = find(qk + 1, hk, 2, ':');   //找后冒号得状态
	if (qm == hm || qk == -1 || hk == -1)   //已不符条件
	{
		cout << "-1";
		return 0;   //输出－1，直接结束整个程序
	}
	for (int i = qm + 1; i < hm; i++)
	{
		if (s[i] == '|')   //枚查留|并加入符合条件的串长
		{
			ans++;
		}
	}
	ans += 4;   //不要忘记前后括号和冒号长
	cout << ans;
	return 0;   //结束整个程序
}
```
### 结果(未吸氧)($588$个测试点，场面一度震惊！):  
![JieGuo](https://cdn.luogu.com.cn/upload/image_hosting/xyhypnn0.png)  
企鹅的题解到此结束，祝各位 OIets 进步 ++

---

## 作者：Insouciant21 (赞：0)

因为这题有 $588$ 个测试点所以就来做了 ~~好水的题~~

直接模拟

先将字符串前面的非 `[` 字符删除，如果没有 `[` 字符即输出 $-1$

同样的，再次处理 `]`，在没有 `]` 字符的情况下输出 $-1$

而对于一对 `:` 要注意最终字符串长度 $|ans|\geq4$ ，即 `:` 不重复计算

从第二个和倒数第二个字符开始判断，直到遇见 `:` 或者是字符串只剩下 `[` 和 `]` 时停止

最后统计从第三个字符开始到倒数第三个字符有多少个非 `|` 字符，直接减去即可

AC代码

``` cpp
#include <bits/stdc++.h>

using namespace std;

string q;

int main() {
    cin >> q;
    int len = q.size();
    int rem = 0;
    while (q.size() && q.front() != '[') { // 去除第一个 [ 前的字符
        q.erase(0, 1);
        rem++;
    }
    if (q.empty()){ // 字符串无 [ 字符
        puts("-1");
        return 0;
    }
    while (q.size() && q.back() != ']') { // 去除最后一个 ] 后面的字符
        q.pop_back();
        rem++;
    }
    if (q.empty()) { // 字符串无 ] 字符
        puts("-1");
        return 0;
    }
    while (q.size() != 2 && q[1] != ':') { 
        q.erase(1, 1); // 下标为 1 的第二个字符
        rem++;
    }
    if (q.size() == 2) { // 即字符串无 : ，只剩下[]
        puts("-1");
        return 0;
    }
    while (q.size() != 3 && *(q.end() - 2) != ':') { // 倒数第二个
        q.erase(q.size() - 2, 1);
        rem++;
    }
    if (q.size() == 3) { // 无第二个 : ，只剩下 [:]
        puts("-1");
        return 0;
    }
    for (int i = 2; i < q.length() - 2; i++) {
        if (q[i] != '|') // 加上需要去除的非 | 字符
            rem++;
    }
    cout << len - rem << endl;
    return 0;
}
```

---

## 作者：Mars_Dingdang (赞：0)

写在前面：这题的测试点真的很棒。。。一共588个AC，太爽了^\_^

[588个AC……](https://www.luogu.com.cn/record/36035727)

好了，言归正传。
### 题目大意
给出一个字符串，试在其中删除一些字符，使得最后的串变为满足以下条件的串且长度最大：
- 长度大于等于 $4$；
- 第一个字符为 `[`；
- 最后一个字符为 `]`；
- 第二个字符和倒数第二个字符为 `:`；
- 其余字符全部为 `|`

### 大体思路
上述第一个条件只要满足条件2~4就自然满足。

**对于条件2~4**

首先我想到的是做了一个字符串 `string a="[::]"` ，用STL中的`s.find(a)`来寻找。然而连样例都没有过。原来是`[::]`可能不连续。因此只能乖乖的用循环去找了qaq

代码如下：
```cpp
	cin>>s;//输入
	int a,b,f1=0,f2=0;//记录第一个‘[’，最后一个‘]’的位置。
	for(int i=0;i<s.length();i++){
		if(s[i]=='['){
			a=i;
            f1=1;
			break;
		}
	}//从头开始找第一个‘[’
	for(int i=s.length()-1;i>=0;i--){
		if(s[i]==']'){
			b=i;
            f2=1;
			break;
		}
	}//从尾开始找最后一个‘[’
	if(a>=b || f1*f2==0) {
		cout<<-1;
		return 0;;
	}
    //相等表示a=b=0，未找到
    //大于表示'['在']'后面，无法配对
	else {//否则找‘：’
		int c=0;
		for(int i=a+1;i<b;i++){
			if(s[i]==':') c++;
			if(c==2) break;
		}//只需在【】之间找两个：即可
		if(c<2){
			cout<<-1;
			return 0;//如果少于两个说明不符合条件
		}
	}
```
**对于条件5**

先初始化长度为4，然后再两个冒号之间找 `|`的个数，找到一个长度加一。注意两个冒号必须在【】之间（找冒号的步骤也可以合并到上方）

代码如下：
```cpp
	int x,y,flag=0;//记录冒号位置
    //flag判断冒号是否在【】之间
	for(int i=0;i<s.length();i++){
		if(s[i]=='[') flag=1;
		if(s[i]==':' && flag==1){
			x=i;
			break;
		}
	}
	flag=0;
	for(int i=s.length()-1;i>=0;i--){
		if(s[i]==']') flag=1;
		if(s[i]==':' && flag==1){
			y=i;
			break;
		}
	}//确定位置
	for(int i=x;i<=y;i++){
		if(s[i]=='|') ans++;
	}//在冒号之间找|，增加长度
```
最后输出即可。
### 完整代码
```cpp
#include<bits/stdc++.h>//头文件
using namespace std;
string s;//字符串
int main(){
	cin>>s;//输入
	int ans=4;//确定长度
	int a,b;
	for(int i=0;i<s.length();i++){
		if(s[i]=='['){
			a=i;
			break;
		}
	}
	for(int i=s.length()-1;i>=0;i--){
		if(s[i]==']'){
			b=i;
			break;
		}
	}
	if(a>=b) {
		cout<<-1;
		return 0;;
	}
	else {
		int c=0;
		for(int i=a+1;i<b;i++){
			if(s[i]==':') c++;
			if(c==2) break;
		}
		if(c<2){
			cout<<-1;
			return 0;
		}
	}//是否满足条件
	int x,y,flag=0;
	for(int i=0;i<s.length();i++){
		if(s[i]=='[') flag=1;
		if(s[i]==':' && flag==1){
			x=i;
			break;
		}
	}
	flag=0;
	for(int i=s.length()-1;i>=0;i--){
		if(s[i]==']') flag=1;
		if(s[i]==':' && flag==1){
			y=i;
			break;
		}
	}//确定冒号位置
	for(int i=x;i<=y;i++){
		if(s[i]=='|') ans++;
	}//计算长度
	cout<<ans;//输出
	return 0;//完美
}
```
~~看得这么认真，不点个赞再走嘛qaq~~


---

