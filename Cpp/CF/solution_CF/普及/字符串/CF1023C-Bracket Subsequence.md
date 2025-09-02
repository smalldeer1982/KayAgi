# Bracket Subsequence

## 题目描述

A bracket sequence is a string containing only characters "(" and ")". A regular bracket sequence is a bracket sequence that can be transformed into a correct arithmetic expression by inserting characters "1" and "+" between the original characters of the sequence. For example, bracket sequences "()()" and "(())" are regular (the resulting expressions are: "(1)+(1)" and "((1+1)+1)"), and ")(", "(" and ")" are not.

Subsequence is a sequence that can be derived from another sequence by deleting some elements without changing the order of the remaining elements.

You are given a regular bracket sequence $ s $ and an integer number $ k $ . Your task is to find a regular bracket sequence of length exactly $ k $ such that it is also a subsequence of $ s $ .

It is guaranteed that such sequence always exists.

## 样例 #1

### 输入

```
6 4
()(())
```

### 输出

```
()()
```

## 样例 #2

### 输入

```
8 8
(()(()))
```

### 输出

```
(()(()))
```

# 题解

## 作者：__CrossBow_EXE__ (赞：1)

# 前言

我对此题的评判如下：

- 建议降红；
- 建议增加翻译，参考下方。

# 题意

给定一个长度为 $n$ 的括号序列 $s$，让你在 $s$ 中找到一个长度为 $k$ 的合法括号子序列 $t$。

数据范围：$2 \le k \le n \le 2 \times 10^5$。

# 分析

首先，输入一个字符数组，这是简单的部分。

接着，扫一遍字符数组，如果有左括号就输出左括号，直到左括号的数量达到了 $\frac{k}{2}$；如果有右括号，先判断一下右括号有没有比左括号多，如果右括号的数量小于左括号的数量，就输出，否则不输出。

最后，时刻注意输出的字符的数量有没有达到 $k$，如果达到了就可以快乐退出啦！

把上面的步骤 $2$，$3$ 整理一下：

- 有左括号就输出左括号；
- 有右括号得先判断数量再输出；
- 如果输出的括号数量达到标准，程序结束。

# 代码

```cpp
#include<iostream>
using namespace std;
char a[200005];//定义字符数组 
int main() {
	//输入 
	int n,k;
	cin>>n>>k;
	for(int i=1; i<=n; i++) {
		cin>>a[i];
	}
	//进行处理
	int l=0,r=0;
	for(int i=1;i<=n;i++){
		if(a[i]=='('&&l<k/2){
			l++;//多了一个左括号 
			cout<<'(';//取出 
		}
		if(a[i]==')'&&r<l){
			r++;//多了一个右括号 
			cout<<')';//取出 
		}
		if((l+r)==k) return 0;//如果满足条件就可以退出啦！ 
	} 
	return 0;
}
```

AC 图片：

![](https://i.postimg.cc/D0jVJzgN/2023-11-18-181842.png)

---

## 作者：_xxxxx_ (赞：1)

### 题意

给出 $n$，$k$，和一个长 $n$ 的字符串 $S$。现在要在 $S$ 中找出一个长为 $k$ 的字符串 $ans$ ，使得 $ans$ 中的括号是匹配的。

### 分析

做题好习惯，先看数据范围，$n\le 10^5$，考虑 $O(n)$ 算法。

既然 $ans$ 的长度为 $k$，且括号都是匹配的，那么就说明 `(` 有 $k \div 2$ 个，同时，`)` 也有 $k \div 2$ 个。

另外，在所有时间，`)` 的个数都不能超过 `(` 的个数，因为 `)` 多了就**匹配不到前面**的了。

由上，我们可以知道：

1. 有 `(` 就拿，一直拿到 $k \div 2$。

2. 当 `)` 的个数比 `(` 的个数少的话，可以拿，与前面 `(` 的匹配。

### 代码

将上面两点改为代码的形式，就是本题的代码了。

```
#include <iostream>
#include <cmath>
#include <queue>
#include <stdio.h>
#include <cstdio>
#include <algorithm>
#define LL long long
using namespace std;
const int N = 2e5 + 10;
const int INF = 0x3f3f3f3f;
int n, k;
string s;
int numl, numr, cnt = 0;
string ans;
signed main()
{
	cin >> n >> k;
	cin >> s;
	for(int i = 0; i < n; i++)
	{
		if(s[i] == '(' && numl < (k / 2))//左边一半 
		{
			ans += '(';
			numl++;
		}
		else if(s[i] == ')' && numl > numr /*)不能大于(*/&& numr < (k / 2))//右边一半 
		{
			ans += ')';
			numr++;
		}
		else if(numl + numr == k)//已经有k个了，直接退出 
		{
			break;
		}
	}
	cout << ans << endl;
	return 0;
}
```

---

## 作者：StudyingFather (赞：1)

由于刚开始给出的字符串一定合法，所以刚开始给出的字符串一定有左括号和右括号各 $ n/2 $ 个。当然，我们生成的字符串也必须有 $ k/2 $ 个左括号和右括号。

我们可以扫描一遍原字符串，如果遇到左括号，且左括号的数量$ <= k/2 $ ，就可以把左括号放入答案序列。

如果是右括号，我们需要确保在当前左括号数量小于右括号数量的情况下（左括号数量等于右括号的话，就不能再添加右括号了），在满足右括号数量$ <= k/2 $ 的情况下，将右括号放入答案序列。

显然，这样的做法不会破坏原来括号的相对顺序，因而这样的做法是合法的。

```cpp
#include <stdio.h>
char s[200005],res[200005];
int main()
{
 int n,k;
 scanf("%d%d",&n,&k);
 scanf("%s",s);
 if(n==k)printf("%s",s);
 else
 {
  int cntl=0,cntr=0,tot=0;
  for(int i=0;i<n;i++)
   if(s[i]=='(')
   {
   	if(cntl!=k/2)
   	{
   	 cntl++;
   	 res[tot++]='(';
   	}
   }
   else
   {
   	if(cntr!=k/2&&cntl>cntr)
   	{
   	 cntr++;
   	 res[tot++]=')';
   	}
   }
  printf("%s",res);
 }
 return 0;
}
```

---

## 作者：Mickey_snow (赞：1)

[CF1023C](http://codeforces.com/contest/1023/problem/C) _Bracket Subsequence_ : 贪心

题目大意：给你一个正则括号序列 $s$ ,让你在当中选择一个长度正好为 $t$ 的子串，使得 $t$ 恰好也是一个正则括号序列。

由于我们已经知道了 $s$ 是合法的，所以 $s$ 中的东西我们能用则用，将 $s$ 扫一遍，记录一下当前处于括号的哪一层（也就是前面有多少个'('没有')'与之对应）。如果当前 $s$ 中字符为 '('而且长度没有达到需要的一半，就将它加入 $t$ 中。如果是 ')',则当前层数减一(如果不在最外层），加入 $t$ 中。

时间复杂度为 $O(N)$.

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
string a, b;
int main()
{
	int totLen, need; cin >> totLen >> need >> a;

	need >>= 1; int cnt = 0;
	for (int i = 0; i < totLen; i++) {
		if (a[i] == '(' && need > 0) { need--; b += '('; cnt++; }
		if (a[i] == ')'&&cnt > 0) { b += ')'; cnt--; }
	}
	cout << b << endl;
	//system("pause");
	return 0;
}
```



---

## 作者：weihaozhen2010 (赞：0)

# **传送门**

[CF1023C](https://www.luogu.com.cn/problem/CF1023C)

# **思路：**

- 贪心的思想。

- 给定的字符串中 `(` 有 $k/2$ 个。

- 同样的 `)` 也有 $k÷2$ 个。

- 因此我们可以从左向右扫一遍：

- 如果是 `(` 且目前 `(` 的个数小于 $k÷2$，存储下来。

- 如果是 `)` 且目前 `)` 的个数小于 $k÷2$，以及目前 `)` 的个数小于 `(` 的个数，存储下来。

- 输出存储的数组即可。

# **参考代码：**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int main()
{
	int n,k,cnt=0,z=0,y=0;
	char a[200005],ans[200005];
	cin>>n>>k>>a;
	int s=k/2;
	for(int i=0;i<n;i++)
	{
		if(cnt==k)
		{
			break;
		}
		if(a[i]=='('&&z<s)
		{
			z++;
			ans[++cnt]=a[i];
		}
		if(a[i]==')'&&y<z&&y<s)
		{
			ans[++cnt]=a[i];
			y++;
		}
	}
	for(int i=1;i<=cnt;i++)
	{
		cout<<ans[i];
	}
	return 0;
}
```

---

## 作者：King_duck (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1023C)

由于这道题没有给出翻译，我就先解释一下题意。输入 $n$ 和 $k$ 两个整数，再输入一个长度为 $n$ 的由 `(` 和 `)` 组成的字符串 $str$，最后让你在 $str$ 中找到一串长度为 $k$ 的字符串，使在它之中的括号是匹配的。

接下来讲我的思路，首先 `(` 和 `)` 的数量肯定是 $\frac{k}{2}$，这样才能匹配，所以我们在取 `(` 的时候记录一下数量，如果它的数量大于了 $\frac{k}{2}$ 就不取了。然后我们在取 `)` 的时候也记录一下数量，只要 `)` 的数量不大于目前 `(` 的数量就可以取（不然前面的括号会不匹配）。

有了前面的思路，直接上代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,k,l,r;
string a;
int main() 
{
	cin>>n>>k>>a;
	for(long long i=0;i<n;i++)
	{
		if(l<k/2&&a[i]=='(')
		{
			cout<<'(';
			l++;
		}
		if(r<l&&a[i]==')')
		{
			cout<<')'; 
			r++;
		}
		if((l+r)==k) 
		{
			return 0;
		}
	}
	return 0;
}
```

---

## 作者：我梦见一片焦土 (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/CF1023C)

------------

# 题意：

给有 $n$ 个字符的括号序列（括号匹配），输出含 $k$ 个字符的括号序列（括号匹配）。

------------

# 思路：

水题。输出第 $k \div 2$ 个 ```(``` 前的序列，然后补齐 ```)``` 即可。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+10;
const int INF=0x3f3f3f3f;
int n,m,s,ss;
char c[N];
signed main(){
    cin>>n>>m>>c;
    for(int i=0;i<n;i++){
        ss++;
        if(c[i]=='('){
            cout<<"(";
            s++;
            if(s==m/2){
				break;
			}
        }else{
            cout<<")";
        }
    }
    for(int i=ss+1;i<=m;i++){
		cout<<")";
	}
    cout<<endl;
    return 0;
}
```
完结撒花~

---

## 作者：_UniqueGirl_ (赞：0)

来水一道黄。

乍一看会吓到不少人(~~包括我~~），但其实也就是红题难度。

## 分析：

#### 输入

首先输入 $n$ 和 $k$,然后是一串字符（只会由 $'('$ 和 $')'$ 组成。

#### 过程

其实很简单，模拟就可以了。

两个变量 $l$、$r$，分别记录左括号和右括号的数量。

然后去遍历一遍。如果有左括号并且没有达到 $\frac{k}{2}$ 个，那么就可以输出，然后标记一下。如果是右括号，那么判断一下 $r$ 是否小于 $l$，小于的话就输出。

最后记得判断一下是否够长了。



## 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
char a[200005];
int main(){
    int n,k;
    int l=0,r=0;
    cin>>n>>k;
    for(int i=1;i<=n;i++){
	    cin>>a[i];//输入部分
	    if(r+l==k)
	        break;//字符够了就可以快乐的结束程序水一道题了
	    if(a[i]=='('&&l*2<k){cout<<a[i];l++;}//判断左括号，一定，一定是小于！！！
	    if(a[i]==')'&&r<l){cout<<a[i];r++;}//判断右括号
    }
    return 0;
}
```

 AC 的瞬间真的好养眼。
 
![](https://cdn.luogu.com.cn/upload/image_hosting/upjxdmv4.png)

---

## 作者：kingho11 (赞：0)

这一道题乍一看很难，但是我们仔细阅读题目之后，其实是很简单的

### 题目分析

首先先分析一下题目：

**①输入一个长度为 $n$ 的字符串，要从里面截取一段长度为 $k$ 的合法的括号序列**

**②输入的字符串只会由 '('和')'组成**

**③输入的字符串保证是合法的括号序列**

那么其实这道题目就很简单了，模拟就可以了。

###  思路：

直接从原字符串中找 $k\div2$ 个左括号和 $k\div2$ 个右括号，遇见一个左括号就输出，同时记录左括号有几个的计数器 $+1$。同理，遇见一个右括号就输出，同时记录右括号有几个的计数器 $+1$。这样子就可以保证输出的字符串一定是有序的。

### AC Code：
```
#include<bits/stdc++.h>
using namespace std;
int main()
{
	long long n,k;
	cin>>n>>k;
	long long cntl=0,cntr=0;//cntl是左括号的计数器，cntr是右括号的计数器 
	string s;
	cin>>s;
	for(long long i=0;i<n;i++)
	{
		if(s[i]=='(')//如果是左括号 
		{
			if(cntl<k/2)//如果左括号的数量还没有到k/2，就可以直接输出左括号 
			{
				cntl++; 
				cout<<"(";
			}
		}else//如果是右括号 
		{
			if(cntr<k/2)//如果右括号的数量还没有到k/2，就可以直接输出右括号 
			{
				cntr++;
				cout<<")";
			}
		}
	}
}
```

---

## 作者：FutureThx (赞：0)

每日~~打卡~~题解心情好

## 题意
题面：[传送门](https://www.luogu.com.cn/problem/CF1023C)

$ $
**大致意思**：给定一个长度为 $n$ 且仅有左右括号的字符串，保证字符串中括号完全匹配，请去除一些括号，让这个字符串长度变成 $k$ ,并且其中括号仍然是完全匹配的。

$ $

## 思路
我们可以定义两个数组 $a$ 和 $b$,其中 $a$ 数组可以用来读入数据，经过处理保存到 $b$ 数组里面，那么问题来了：怎么处理呢？ 
$ $

$1$. 让一个长度为 $n$ 的字符串变成长度为 $k$，简单来说就是删除 $t = n - k$ 个字符，让字符串仍然合法

$2$. 我们可以一个一个字符进行处理：

$ $
$\ \ \ \ $  $2.1$ 若需要删除的字符计数器 $t$ 为 $0$ ,**直接读入并保存在 $b$ 数组**

$ $
$\ \ \ \ $  $2.2$ 否则判断当前处理字符是否为左括号，如果是，**同上，直接保存**

$ $
$\ \ \ \ $  $2.3$ 如果以上两个条件都不满足，**将 $b$ 数组顶端的数据删除，同时将计数器 $t$ 减去 $2$**

$3$.输出数组 $b$

## 代码
思路理清了后我们就可以快乐的开始敲代码了，一个小提醒：用 $STL$ 中的 $stack$ 会导致严重超时。

$100pts:$
```cpp
#include <iostream>
using namespace std;

int main()
{
    int n,k,t,bt = 0;
    cin >> n >> k;
    t = n - k;
    char a[200001],b[200001];
    cin >> a;
    for(int i = 0;i < n;i++){
        if(t == 0){
            bt++;
            b[bt] = a[i];
        }
        else if(a[i] == '('){
            bt++;
            b[bt] = a[i];
        }
        else{
            b[bt] = '\0';
            bt--;
            t-=2;
        }
    }
    for(int i = 1;i <= k;i++)
        cout << b[i];
    return 0;
}
```
完结撒花

## 后记
$Updata \ \ 2020.8.19 \ \  13:30:$ 完成题解，求管理员给个通过

---

## 作者：开始新的记忆 (赞：0)

题目大意:现在有n个括号（保证匹配），要你留下k个（k，n为偶数）括号，使得它们也匹配。

大致思路：不难发现，留下k个就是删掉（n-k）个，那么就是左右括号各删掉(n-k)/2个，左括号从右往左扫，右括号从左往右扫即可。

code：

```
#include<bits/stdc++.h>
using namespace std;
int n,k,a[200010],ha[200010],t,pos=1;

int main()
{	cin>>n>>k;
	t=(n-k)/2;
	memset(ha,1,sizeof(ha));
	for(int i=1;i<=n;++i)
	{
		char hh[2];
		cin>>hh[0];
		if(hh[0]==')')
			a[i]=0;
		else
			a[i]=1;
	}
	while(t>0)
	{
		if(a[pos]==0)
			--t,ha[pos]=0;
		++pos;
	}
	pos=n;
	t=(n-k)/2;
	while(t>0)
	{
		if(a[pos]==1)
			--t,ha[pos]=0;
		--pos;
	}
	for(int i=1;i<=n;++i)
		if(ha[i])
		{
			if(a[i]==0)
				cout<<')';
			else
				cout<<'(';
		}
	cout<<endl;
	return 0;
} 
```


---

## 作者：MorsLin (赞：0)

$b$为答案字符串，我们枚举$a$数组中的每一个括号，每扫到一个括号，就把它加入$b$里，如果为左括号，$cnt{+}{=}1$，当$cnt==m/2$就跳出循环，然后从后面补右括号就行了

没初始化$b$数组，FST了…… QAQ

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int main(){
	int n,m; cin>>n>>m; m/=2;
	char a[200010],b[200010]; cin>>a;
	memset(b,0,sizeof(b));
	int len=strlen(a)-1,tot=0,cnt=0;
	for(int i=0;i<=len;i++){
		if(a[i]=='('){
			b[tot++]='(';
			cnt++;
		}
		if(cnt==m) break;
		if(a[i]==')'){
			b[tot++]=')';
		}
	}
	for(int i=tot;i<m*2;i++) b[i]=')';
	cout<<b;
	return 0;
}
```


---

## 作者：小闸蟹 (赞：0)

```cpp
// 因为我们可以通过浪费掉一些"()"对来达到题目所说的要求，目前的目标就是如何去浪费
#include <iostream>
#include <string>

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, k;
    std::cin >> n >> k;

    std::string s;
    std::cin >> s;

    if (n == k) // 如果所需序列的长度和原序列相等，则直接输出，这里可以特判掉
    {
        std::cout << s << std::endl;
    }
    else
    {
        int Delta = n - k;  // 还需要浪费多少个"()"对

        std::string Ans;
        for (int i = 0; i < n; ++i)
        {
            if (s[i] == '(')    // 遇到左括号直接用掉
            {
                Ans.push_back('(');
            }
            else    // 遇到右括号要分情况讨论
            {
                if (Delta != 0) // 还有要浪费的名额
                {
                    Ans.pop_back(); // 退掉一个括号
                    Delta -= 2;     // 因为浪费一次会少两个
                }
                else    // 没有要浪费的名额了，可以直接加入右括号了
                {
                    Ans.push_back(')');
                }
            }
        }
        std::cout << Ans << std::endl;
    }

    return 0;
}
```

---

## 作者：Sai_t (赞：0)

本题为贪心。

显而易见，答案一定包含 $\dfrac{k}{2}$个左括号和右括号。所以，只需求出这样的合法左右括号即可。贪心的思想是：

- 只要是左括号且当前左括号数不足 $\dfrac{k}{2}$个，则将其加入答案序列。

- 如果是右括号，则还需要考虑在合法括号序列的前缀中，左括号总数大于右括号总数。

AC Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,l,r;
string s,ans;
int main(){
	cin>>n>>k>>s;
	for(int i=0;i<n;i++){
		if(s[i]=='('){
			if(l*2<k){//保证总数
				ans+='(';
				l++;
			}
		}
		else{
			if(r*2<k&&r<l){//前缀中，左括号>右括号
				ans+=')';
				r++;
			}
		}
	}
	cout<<ans<<endl;
	return 0;
}
```


---

