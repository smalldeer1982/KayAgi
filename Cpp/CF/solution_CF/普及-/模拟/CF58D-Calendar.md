# Calendar

## 题目描述

BerOilGasDiamondBank has branches in $ n $ cities, at that $ n $ is an even number. The bank management wants to publish a calendar with the names of all those cities written in two columns: the calendar should consist of exactly $ n/2 $ lines of strictly equal length, each of which contains exactly two names and exactly one separator character between them. The name of every city should be used in the calendar exactly once. For historical reasons the symbol $ d $ is used as the separator of words in the calendar.

The BerOilGasDiamondBank management wants to show that all its branches are equally important to it, that's why the order of their appearance in the calendar should be following: if we "glue"(concatinate) all the $ n/2 $ calendar lines (from top to bottom) to make a single line, then the lexicographically minimal line is obtained. No separator character will be used to separate calendar lines. For example, if the lines are "bertown!berville", "newberville!bera", then the resulting line is "bertown!bervillenewberville!bera". In some sense one has to find the lexicographically minimal calendar, where the comparison of calendars happens line by line.

Help BerOilGasDiamondBank and construct the required calendar.

## 样例 #1

### 输入

```
4
b
aa
hg
c
.
```

### 输出

```
aa.b
c.hg
```

## 样例 #2

### 输入

```
2
aa
a
!
```

### 输出

```
a!aa
```

## 样例 #3

### 输入

```
2
aa
a
|
```

### 输出

```
aa|a
```

# 题解

## 作者：N_z_ (赞：4)

## 思路
首先我们可以知道每一行的长度是输入的总长除以 $n$ 的一半再加一。

我们考虑将每个串后面加上一个插入字符。

然后对每个串向后搜如果有跟它加起来和为目标长度（输入的总长除以 $n$ 的一半再加一）的就输出这两个串然后清空它们。

具体见代码。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
string s[10001];
int main()
{
	int n,m=0;
	cin>>n;
	for(int x=1;x<=n;x++)cin>>s[x];
	char t;
	cin>>t;
	for(int x=1;x<=n;x++)s[x]+=t,m+=s[x].size();
	m/=n/2;
	sort(s+1,s+1+n);
	for(int x=1;x<=n;x++)
	for(int y=x+1;y<=n;y++)
	if(s[x].size()+s[y].size()==m)cout<<s[x],s[y]=s[y].substr(0,s[y].length()-1),cout<<s[y]<<endl,s[x]="",s[y]="",y=n+1;
}
```

---

## 作者：Soul_direction (赞：2)

[Link](https://www.luogu.com.cn/problem/CF58D)

[听说博客食用更佳呦](https://www.luogu.com.cn/blog/luogucodingjvruo/cf58d-calendar-ti-xie)

### 题目大意

给你 $n$ 个字符串，让你用一个字符连接 2 个字符串，总计构建 $\dfrac{n}{2}$ 个字符串，要求其字典序最小。

### 相关知识

这是一道很好的字符串练手题。让我们先了解一下 STL 的字符串连接操作：

#### 连接操作：

即将 2 个字符串连接。

```cpp
string a,b,c;
a="hello,";
b="world!";
c=a+b;
```

则：

```cpp
c="hello,world!";
```

#### 比较操作：

即比较 2 个字符串的字典序前后。

```cpp
string a="a",b="b",c,d;
c=min(a,b);
d=max(a,b);
```

则：

```cpp
c="a";
d="b";
```

### 主要思路

已知输出的字符串每行的长度为 $l \times 2 \div n$。可以发现，$1 \le n \le 10^4$，可以暴力枚举！这样，我们枚举二个字符串即可。

### AC Code:

```cpp
#include <iostream>
#include <algorithm>
#include <string>//STL的string标准库
#define maxn 10010
#define inf 2147483647
using namespace std;
int n,l,cnt;
bool flag[maxn];
string in[maxn],out[maxn];
char ch;
string bingo(string a,string b,char c){//合并函数
	return min(a+c+b,b+c+a);
}
inline int read(){//快读
    int x=0,f; char ch=0;
    while(!isdigit(ch)) f=(ch=='-'?-1:1),ch=getchar();
    while(isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    return x*f;
}
inline void print(int x){//快写
    if(x<0) x=-x,putchar('-');
    if(x>9) print(x/10);
    putchar(x%10+48);
}
inline void write(int x){print(x);putchar('\n');}
int main(){
	n=read();
	for(int i=1;i<=n;i++){
		cin>>in[i];
		l+=in[i].size();
	}
	cin>>ch;
	l/=n/2;
	sort(in+1,in+n+1);//排序
	for(int i=1;i<=n;i++){//暴力枚举
		if(flag[i])continue;
		for(int j=i+1;j<=n;j++){
			if(flag[i])break;
			if(flag[j])continue;
			if(in[i].size()+in[j].size()==l){//判断
				flag[i]=flag[j]=1;
				out[++cnt]=bingo(in[i],in[j],ch);//合并
			}
		}
	}
	sort(out+1,out+cnt+1);//排序
	for(int i=1;i<=cnt;i++)cout<<out[i]<<endl;
	return 0;
}
```

---

## 作者：xuan_gong_dong (赞：0)

~~我仍未知头几发究竟哪里错了~~。
## 题面
[Calendar](https://www.luogu.com.cn/problem/CF58D)
## 分析
这个题目有两个要求：一个是字典序最小，一个是长度固定，而这个长度是很容易确定的，在此就不赘述了。

而字典序最小，很好想到去用排序，我们知道 $\texttt{sort}$ 可以直接排序字符串，相当不错。排完序之后就直接去从下到达去匹配长度合适的，然后输出就好了。

时间复杂度为 $O(n \times n)$。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
string s[10010];
int n;
int book[10010];
int len[10010];
int main()
{
	ios::sync_with_stdio(0);
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>s[i];
	}
	char d;
	cin>>d;
	for(int i=1;i<=n;i++)
	{
		s[i]+=d;
	}
	sort(s+1,s+n+1);
	int le=0;
	for(int i=1;i<=n;i++)
	{
		len[i]=s[i].size();
		le+=len[i];
	}
	le=le/(n/2);
	for(int i=1;i<=n;i++)
	{
		for(int j=i+1;j<=n;j++)
		{
//			cout<<i<<' '<<j<<' '<<len[i]<<' '<<len[j]<<endl;
			if(s[i].size()+s[j].size()==le)
			{
//				cout<<i<<' '<<j<<':';
				cout<<s[i];
				s[j].pop_back();
				cout<<s[j]<<endl;
				s[i]="";
				s[j]="";
				break;
			}
		}
	}
}
```


---

## 作者：JimmyLee (赞：0)

# CF58D Calendar 题解

## 题目描述

[CF58D Calendar](https://www.luogu.com.cn/problem/CF58D)

## 题目解法

暴力题。

我们发现输出的字符串中除了每一行最后一个串没有分割字符，其余的都有。

并且每一行只会有两个字符串。

我们可以在每个输入的字符串后面加上分割字符后再进行排序，这样可以保证字典序最小。

每次枚举一个字符串，找到第一个可以和他组成符合条件的字符串，然后将他们输出。

C++ 的 `string` 是基于 `vector` 的，加上分割字符的操作可以 `push_back()`，输出时将第二个字符串 `pop_back()` 即可。

由于 $1\leq n\leq 10^4$，不需要使用二分，暴力枚举就能通过本题。

记得将使用过的字符串清空。

# Code

```c++
#include<bits/stdc++.h>
using namespace std;
#define maxn 10004

string m[maxn];

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    char c;
    int n,s=0;
    cin>>n;
    for(int i=1;i<=n;i++) 
        cin>>m[i];
    cin>>c;
    for(int i=1;i<=n;i++) 
        m[i].push_back(c), s+=m[i].size();
    int lrc=s*2/n;
    sort(m+1, m+n+1);
    for(int i=1;i<=n;i++)
        for(int j=i+1;j<=n;j++)
            if(m[i].size()+m[j].size()==lrc)
                cout<<m[i],
                m[j].pop_back(),
                cout<<m[j]<<'\n',
                m[i].clear(), m[j].clear();
}
```

---

## 作者：mgcjade (赞：0)

# CF58D Calendar 题解

看题目点[这里](https://www.luogu.com.cn/problem/CF58D)。

### 具体思路：
我们知道输出的每一行由两个串加一个分隔符组成，所以我们不妨假设这一个分隔符原本就处于字符串内（方便排序），然后组成了新字符串之后在去掉末尾的字符。

### 做题步骤：
1. ~~输入；~~

2. 将分隔符加入每一个字符串内；

3. 按字典序排序（tips：`sort(str+1,str+n+1)` 即可）；

4. 求答案；

5. ~~输出。~~

### 核心代码：
```cpp
for (int x = 1; x <= n; x++)
	s[x] += ch, m += s[x].size();
m /= n / 2;	//m为一个输出串的长度（末尾有分隔符）
```


```cpp
for (int x = 1; x <= n; x++)
	for (int y = x + 1; y <= n; y++)
		if (s[x].size() + s[y].size() == m)
		{
			s[y][s[y].size() - 1] = ' ';//去分隔符（由于文本比对忽略行末空格，所以可以将最后一位改为空格）
			ans[cnt++] = s[x] + s[y];
			s[x] = "", s[y] = "";
			break;
		}
```

温馨提示：

需要将变量定义为 `string` 类型。

[AC](https://vjudge.net/status#un=mgcjadae&OJId=CodeForces&probNum=58D&res=0&orderBy=run_id&language=)

---

## 作者：aaron0919 (赞：0)

[CF58D 的题解](https://www.luogu.com.cn/problem/CF58D)

先介绍几个 cstring 函数：

1. `strcmp(const char *str1, const char *str2)`：比较 `str1` 和 `str2`：如果小于返回负数；相等返回 0；大于返回正数。
2. `strcpy(char *dest, const char *src)`：将 `src` 的值附给 `dest`。
3. `strlen(const char *str)`：返回 `str` 的长度（不包含结束符）。

说明一下 `'\0'`：

`'\0'` 是 C/C++ 中字符串的结束标志，若一个字符数组没有结束标志，那就真的是一个数组了。

如果将字符串的某一位换成 `'\0'`，则把这个字符串截取到那。

---

然后就是正常思路：
1. 加上分隔符。
2. 排序（得手打）。
3. 枚举组合。

---

接着是代码：
```cpp
#include <stdio.h>
#include <string.h>

char s[10001][101];
char tmp[10001][101];
int n, m;

void msort(int l, int r)
{
    if (l == r)
    {
        return;
    }
    int mid = (l + r) >> 1, i = l, j = mid + 1, k = l;
    msort(l, mid);
    msort(mid + 1, r);
    while (i <= mid && j <= r)
    {
        if (strcmp(s[i], s[j]) < 1)
        {
            strcpy(tmp[k++], s[i++]);
        }
        else
        {
            strcpy(tmp[k++], s[j++]);
        }
    }
    while (i <= mid)
    {
        strcpy(tmp[k++], s[i++]);
    }
    while (j <= r)
    {
        strcpy(tmp[k++], s[j++]);
    }
    for (k = l; k <= r; k++)
    {
        strcpy(s[k], tmp[k]);
    }
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%s", s[i]);
    }
    char t = getchar() * 1 /*0*/ + getchar();
    for (int i = 1; i <= n; i++)
    {
        // 将末尾增加 t
        int len = strlen(s[i]);
        s[i][len] = t;        // 将结束标志改为 t
        s[i][len + 1] = '\0'; // 还得给末尾加上

        m += strlen(s[i]);
    }
    m /= n >> 1;
    msort(1, n);
    for (int i = 1; i <= n; i++)
    {
        for (int j = i + 1; j <= n; j++)
        {
            if (strlen(s[i]) + strlen(s[j]) == (size_t)m)
            {
                printf("%s", s[i]);
                s[j][strlen(s[j]) - 1] = '\0'; // 将最后一个字母删除
                printf("%s\n", s[j]);
                s[i][0] = '\0';
                s[j][0] = '\0'; // 整段删除
                j = n + 1;
            }
        }
    }
    return 0;
}
```

---

## 作者：_Wind_Leaves_ShaDow_ (赞：0)

## 题目分析

题目还是很容易理解，而且题目数据中没有出现无解的情况。

这一题里面有很多 string 基础而有趣的技巧，很适合初学者来学习 string，熟练运用这些技巧，可以让代码更简洁。

这一题其实很水，于是我们先看思路和技巧：

## 思路 & 做法

1. **如何将两个字符串合并？**

	STL 的 string 可以 **直接用加号连接两个字符串**，例如
	```cpp
	string a="this test ",b="is so easy";
	string c=a+b;
	```
	这个情况下，字符串 c 的值为 "this test is so easy"，即字符串 a 与字符串 b 的连接。并且，单个 char 类型的字符也可以通过这种方式连上字符串。

2. **字符串能进行大小比较吗？**

	可以的。字符串的大小比较是 **针对于字典序来** 比较的，即两个字符串首位比较，首位相同比二位……一直到有字符不同或者字符串截止。

	同理，字符串也可以进行 max 和 min 以及 sort 的比较。这在很多地方有很大的用处，比如本题判断哪个字符串应该在前和字符串排序时可以用到。

3. **本题的做法？**

- 先输入，然后进行第一轮排序，将无序的字符串数组排序成从大到小的有序数组。接下来求长度，即 **每个答案字符串除去分隔符** 应该有的长度。

- 进行双重循环寻找答案。第一层循环从首到尾，第二从循环从当前的首扫到尾，如果这两个字符串 **没有被用过** 并且相加长度相同即视为可行解。

- 对于可行解，我一开始的程序是直接输出，但很可惜没有通过，于是我把所有的可行解用答案数组记录下来，最后再进行一次排序输出——竟然离谱的 [通过](https://www.luogu.com.cn/record/103721123) 了！！！~~虽然并不知道为什么我的写法求的不是最可行解而是要进行二次排序，但是能过就好。~~

4. **为什么第二次循环从头扫到尾？这样的话有没有可能影响之后的字符串寻找最小值从而影响答案最优性？**

	这个是不会的。我之前也因为这个问题想了很久。为什么不会呢？因为我们一开始的数组是从小到大排序的，最小的字符串找了它后面最小的字符串，即为最优。并且这不会影响到后面的字符串寻找，因为只有和自己长度一样的字符串才能选择一样的字符串作搭档，而那一个字符串又没有这一个字符串大，不会成为最优解。
    
   感觉这里讲的不是很清楚，可以看看样例或者自己写几个数据辅助理解，这道题对于字符串真的很友好了。
    
5. **有一点需要注意：**
	对于一个字符串，有两种构造方法，可能会导致不同结果。详见样例 2 和样例 3。这里面因为分隔符的大小不一样，导致了两种结果的产生。

## 喜闻乐见的代码环节：

没有写多少注释，自己感觉讲得很清楚了。

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,len,cnt=0;
bool mark[10050];//mark 数组判重
string s[10050],ans[10050];//一个记录最开始的字符串，一个是答案数组
char d;
string make(string a,string b,char c){
	string aa=a+c+b,bb=b+c+a;
	return min(aa,bb);
}//将两个字符串连接并返回最小值
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>s[i];
		len+=s[i].size();
	}
	cin>>d;
	len=len*2/n;//求得长度
	sort(s+1,s+n+1);
	for(int i=1;i<=n;i++){
		if(mark[i])continue;//i被用过
		for(int j=i+1;j<=n;j++){
			if(mark[i])break;//在当前已经求出对于i的最优解了，退出循环
			if(mark[j])continue;//j被用过
			if(s[i].size()+s[j].size()==len){
				mark[i]=true;
				mark[j]=true;//标记
				ans[++cnt]=make(s[i],s[j],d);
			}
		}
	}
	sort(ans+1,ans+cnt+1);//答案数组排序
	for(int i=1;i<=cnt;i++)cout<<ans[i]<<endl;
	return 0;
} 
```


---

## 作者：Allanljx (赞：0)

## 题意
给定一个偶数 $n$，$n$ 个字符串，和一个分割字符 $d$。你要将所有 $n$ 个字符串放在 $n/2$ 行。每行两个字符串，两个字符串之间用一个分割字符 $d$ 隔开。这 $n/2$ 行的长度必须严格相等。

求所有合法方案中，字典序最小的一个。

## 思路
设字符串的总长度是 $l$。每一行的长度肯定是 $l/n*2$ 。因为要字典序最小，所以要先 $sort$ 一下，让其字典序最小。然后再 $O(n^2)$ 枚举两个字符串使它们的长度和为题目所要求。然后还要确定是第二个字符串在前面小还是第一个字符串在前面小，因为就像样例三 $d$ 的字典序有可能最小。最后还要将确定下来的每一行在一起 $sort$ 一下，确保字典序最小。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,sum,book[10005],top;
char c;
string s[10005],ss[10005];
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++) cin>>s[i];
	sort(s+1,s+n+1);
	for(int i=1;i<=n;i++)
	{
		sum+=s[i].size();//总长度
	}
	sum=sum/(n/2);//每一行的长度
	cin>>c;
	for(int i=1;i<=n;i++)
	{
		if(book[i]) continue;//用过了
		book[i]=1;
		for(int j=1;j<=n;j++)
		{
			if(book[j]) continue;
			if(s[i].size()+s[j].size()!=sum) continue;
			string s1,s2;
			s1=s[i]+c+s[j];
			s2=s[j]+c+s[i];
			ss[++top]=min(s1,s2);//确定哪个字符串在前面字典序小
			book[j]=1;
			break;
		}
	}
	sort(ss+1,ss+1+top);//排序
	for(int i=1;i<=top;i++) cout<<ss[i]<<endl;
}
```


---

