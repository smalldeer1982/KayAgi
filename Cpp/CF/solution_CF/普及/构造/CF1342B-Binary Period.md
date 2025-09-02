# Binary Period

## 题目描述

假设有一个字符串$s$，如果它的第$i$ 个字符和第$i+k$ 个字符相等$(1\le i\le|s|-k)$ ，那么这个字符串的周期为$k$ 。其中，$|s|$ 表示字符串$s$ 的长度。

现在给你一个字符串$t$ ，$t$ 内只包括```0```和```1```，请你找出这个$s$ ，使其满足如下条件：
1. 字符串$s$ 也只包括```0```和```1```。
2. $|s|\le 2\times|t|$（$s$ 的长度不能超过$t$ 的长度的两倍）。
3. $t$ 是$s$ 的子串。
4. 在满足上面3个条件的情况下，$s$ 需要有最小的周期$k$ 。

$t$ 是$s$ 的子串就是说当$s$ 删除$0$个或更多个字符后（不能改变顺序），$s$ 就变成了$t$ 。例如```011```就是```10101```的子串。

## 样例 #1

### 输入

```
4
00
01
111
110```

### 输出

```
00
01
11111
1010```

# 题解

## 作者：SpeedStar (赞：5)

### 算法分析
我们可以先考察周期为1和2的字符串是怎样的。周期为1的字符串有$000000\cdots$和$111111\cdots$两种类型；周期为2的字符串有$010101\cdots$和$101010\cdots$两种类型。

不难发现所给字符串$t$中若只有0或只有1，那么直接输出$t$即可，因为它的周期是1。否则，很显然任何$t$都是长度为$2|t|$的字符串$0101\cdots01(1010\cdots10)$的子列。


### C++代码
```cpp
#include <iostream>

using namespace std;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	int T;
	cin >> T;
	
	while (T--) {
		string t;
		cin >> t;
		int n = t.size();
		if (t == string(n, '0') || t == string(n, '1')) cout << t << '\n';
		else {
			string s(2 * n, '0');
			for (int i = 0; i < n; i++) s[2 * i] = '1';
			cout << s << '\n';
		}
	}
	
	return 0;
}
```


---

## 作者：wangqinyan (赞：4)

这题思路与代码实现其实都很简单。

# **题目思路**

这道题就是给定一个字符串 $t$，寻找一个字符串 $s$ 使其在满足 $t$ 是 $s$ 的子串的情况下，$s$ 的周期最小（具体周期定义见题目描述）。

这个时候我们可以考虑两种情况。第一种，输入的字符串 $t$ 中全是 $1$ 或全是 $0$。这种情况 $s$ 的最小周期就是 $1$。我们只需要直接输出原字符串 $t$ 即可。第二种，输入的字符串 $t$ 中既有 $1$ 又有 $0$。这种情况下 $s$ 的周期就不可能为 $1$ 了。这时候我们可以考虑让 $s$ 的周期为 $2$。那这时，字符串 $s$ 的一个周期中的字符就有两种可能。第一种就是一个 $1$ 加一个 $0$，第二种就是一个 $0$ 加一个 $1$。当 $s_i$ 后面为 $1$ 时，我们可以在 $s_i$ 后面加一个 $0$。反之，在 $s_i$ 后面加一个 $1$。

所以这题只需要判断输入的字符串 $t$ 中是否全是 $1$ 或全是 $0$。如果是，就直接输出原字符串。如果不是，就在每两个同为 $1$ 或同为 $0$ 的字符之间插入一个不同的字符即可。具体可见代码。


# **代码**
```cpp

#include<bits/stdc++.h>
using namespace std;
long long t;
string s,s1;
int main()
{
    cin>>t;
    while(t--)
    {
        cin>>s;
        s1="";
        if(s[0]=='1')
        for(int i=0;i<s.size();i++)s1+='1';
        else
        for(int i=0;i<s.size();i++)s1+='0';
        if(s1==s)cout<<s<<endl;
        else
        {
            for(int i=0;i<s.size();i++)
            if(s[i]==s[i+1])
            {
                cout<<s[i];
                if(s[i]=='1')cout<<0;
                else
                cout<<1;
            }
            else
            cout<<s[i];
            cout<<endl;
        }
    }
    return 0;
}
 
```
感谢观看！

---

## 作者：Big_Dinosaur (赞：1)

$t$ 可以看做 $s$ 加字符构成，分两种情况处理。
### 第一种：只有 `0` 或只有 `1`。
此时原字符串就是最佳选择，周期为 $1$。$t=s$。
### 第二种：有 `0` 也有 `1`。
显然周期无法为 $1$，考虑是否可以为 $2$。若周期为 $2$，只可能为 `01` 或 `10`。对于 $s_i$，若为 `0`，显然后加 `1` 可构成 `01`；若为 `1`，显然前加 `0` 可构成 `01`。这样周期为 $2$，且 $s$ 是答案 $t$ 的子串。答案 $t$ 就是由 $|s|$ 个 `01` 构成。

判断是哪一种情况后分类讨论即可。

---

## 作者：Novelist_ (赞：1)

~~这道题比较水。~~

这道题分两种情况，分别为 $t$ 由一种字符构成和由两种字符构成两种情况。

1. $t$ 只有 $0$ 或 $1$。  
此时的 $k$ 就是 $1$，直接输出 $t$ 就是最好的选择。

2. $t$ 既有 $0$ 又有 $1$。  
此时的 $k$ 为 $2$，字符串由 `01` 或 `10` 构成。我们设 $a_i$ 为字符串的第 $i$ 个字符，且它为 $0$。如果 $a_{i+1}$ 也是 $0$，那么就在 $a_i$ 后面加上 $1$，否则不变。当 $a_i$ 为 $1$ 时也是同样的套路。

下面是代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  string t;
  int n,i,j,len;
  cin>>n;
  while(n--)
  {
    cin>>t;
    len=t.size();
    for(i=0;i<len-1;++i)
    if(t[i]!=t[i+1])break;
    if(i==len-1)
    {
      cout<<t<<'\n';
      continue;
	}//第一种情况
	for(i=0;i<len-1;++i)
	{
	  cout<<t[i];
	  if(t[i]==t[i+1])
	  cout<<'1'-t[i];
     //不同就补上一个，是整型还是字符都无所谓
	}
	cout<<t[len-1]<<'\n';//第二种情况
  }
  return 0;
}
```

---

## 作者：lutaoquan2012 (赞：0)

### 题目大意：
给定一个字符串 $t$，让你构造一个字符串 $s$，使得 $s$ 的长度不超过 $t$ 的长度，并且 $t$ 是 $s$ 的子串，让 $s$ 的周期最小。
### 题目思路：
如果周期是 $1$ 的话，$s=11111…111$ 或者 $s=00000…000$。

如果周期是 $2$ 的话，$s=101010…1010$ 或者 $s=010101…0101$。

1. 如果 $t$ 全是 $1$ 或全是 $0$，直接让 $s=t$，周期为 $1$。
2. 否则考虑构造周期为 $2$，如果 $t_i$ 不等于 $t_{i+1}$ 那么不用管，否则要在 $t_i$ 的后面加上和 $t_i$ 相反的数字，因为每一次最多只会在 $t_i$ 的后面加 $1$ 个字符，所以满足长度要求。
### 代码：
```cpp
#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
ll T;
string t,s;
int main() {
    cin>>T;
    while(T--){
        cin>>t;
        s="";//记得清空
        bool flag=false;//判断如果 t 全是 0 或者全是 1
        for(int i=1;i<t.size();i++)
            if(t[i]!=t[i-1]) flag=true;
        if(!flag){cout<<t<<endl;continue;}
        for(int i=0;i<t.size();i++){
            s+=t[i];
            if(t[i]!=t[i+1]) continue;
            s+=((1-(t[i]-'0'))+'0');//在 t[i] 的后面加上和 t[i] 相反的数字
        }cout<<s<<endl;
    }
    return 0;
}
```

---

## 作者：Qiering (赞：0)

# CF1342B Binary Period
## 题目描述
对于 $t_i(1 \le i \le n)$ 构造 $s_i(1 \le i \le n)$ 使 $t_i$ 为 $s_i$ 子串，$s_i$ 循环节 $k$ 最小且 $|s_i| \le 2 \times |t_i|$。
## 题目分析
考虑 $k$ 的值：

* $k=1$ 当且仅当 $t_i$ 为全 $1$ 或全 $0$，答案为 $t_i$。
* $k=2$ 假定循环节为 $01$，$t_i$ 的每一位都可以补全为一个循环节，$|s_i|=2\times|t_i|$ 合法。

显然任意 $t_i$ 可以用以上两种方法构造出对应 $s_i$。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#define ll long long
#define re register
int T;
string st;
signed main()
{
	IOS;
	cin>>T;
	while(T--)
	{
		cin>>st;
		int len=st.length();
		bool flag=0;
		for(re int i=1;i<len;++i)
		{
			if(st[i]!=st[i-1])//全1 or 全0
			{
				flag=1;
				break;
			}
		}
		if(!flag)
		{
			cout<<st<<'\n';
			continue;
		}
		for(re int i=0;i<len;++i)//补全
		{
			if((st==‘1’) cout<<0<<st[i];
			else cout<<st[i]<<1;
		}
		cout<<'\n';
	}
	return 0;
}
```

---

## 作者：copper_ingot (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1342B)

简单思维题。

当 $t$ 为全 $0$ 或全 $1$ 串时，它本身就有长度为 $1$ 的最短周期，直接输出 $t$ 即可。

接下来讨论 $t$ 中即有 $0$ 又有 $1$ 的情况，此时 $s$ 的周期不可能是 $1$。

首先可以证明 $t$ 必然为长度为 $2|t|$ 的字符串 $s = 01010101\dots0101$ 的子序列。因为 $t_i$ 必然和 $s_{2i-1}$ 与 $s_{2i}$ 其中之一相同且对应，所以 $t$ 是 $s$ 的子序列。

然后发现 $s$ 的周期是 $2$。因为周期不可能是 $1$，所以 $2$ 是最短周期，直接输出 $s$ 即可。

$\mathbb{H} \varepsilon \text{r} \epsilon ' \mathfrak{s}\ \mathcal{M} \mathsf{y}\ \complement o\texttt{d}\mathbf{e}$：

```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n, flag; string s;
int main(){
	scanf("%d", &t);
	while (t--){
		cin >> s;
		n = s.length(), flag = 1;
		for (int i = 0; i < n; i++)
			if (s[i] != s[0]){flag = 0; break;}
		if (flag) cout << s << '\n';
		else{
			for (int i = 1; i <= n; i++) cout << "01";
			puts("");
		}
	}
	return 0;
}
```

---

## 作者：HUANGRUI11 (赞：0)

比较好想的一道构造题。

题意是构造字符串 $s$ 使得字符串 $t$ 既是 $s$ 的非连续性子串，又要周期最小（即将字符串分成 $k$ 段，每一段一样）。

很容易想到进行特判，如果 $t$ 全为 $1$ 或 $0$，就直接输出 $t$，$s$ 的周期为 $1$。

否则考虑 $s$ 的周期为 $2$，即 $s$ 的每 $k$ 段为 $01$ 或 $10$，可以在 $t$ 的每两个字符中穿插一个不同字符，以此将 $s$ 构造成每 $k$ 段都是 $01$ 或 $10$ 的子串。

代码较为简易，就不展示了。

---

## 作者：king_xbz (赞：0)

一道不错的构造题。

首先，考虑如果串全是$0$或者全是$1$，那么显然我们只需要输出原串即可，这样的周期$k=1$

那么如果不是这样的话，周期应该会至少是$2$，因为此时周期为$1$显然会让$1$和$0$对位，这是不匹配的！

怎么弄？那就让串变成$01010101$或者$10101010$，这些字符倒是可以随便加，但前提是必须加的字符数量小于$len_T$.

我们选择将字符串全变成$101010$的形式（当然，另一种形式也可以）

按照这样的规则构造即可：

代码：

```cpp
#include<bits/stdc++.h>
#define fint register int
#define H 5001
#define N 4379844
using namespace std;
int main()
{
	int n;
	cin>>n;
	string a;
	while(n--)
	{
		cin>>a;
		for(fint i=1;i<a.size();i++)
		if(a[i]!=a[i-1])
		goto lb;
		cout<<a<<endl;
		continue;
		lb:
		for(fint i=0;i<a.size();i++)
		if(a[i]=='1'&&a[i+1]!='0')
		cout<<'1'<<'0';
		else
		if(a[i]=='0'&&a[i-1]!='1')
		cout<<'1'<<'0';
		else
		cout<<a[i];
		cout<<endl;
	}
	return 0;
}
```



---

## 作者：lingfunny (赞：0)

# 题目翻译
~~刚提交了一个翻译，不知道过没过~~
### 题目描述
假设有一个字符串$s$，如果它的第$i$ 个字符和第$i+k$ 个字符相等$(1\le i\le|s|-k)$ ，那么这个字符串的周期为$k$ 。其中，$|s|$ 表示字符串$s$ 的长度。

现在给你一个字符串$t$ ，$t$ 内只包括```0```和```1```，请你找出这个$s$ ，使其满足如下条件：

- 字符串$s$ 也只包括```0```和```1```。
- $|s|\le 2\times|t|$（$s$ 的长度不能超过$t$ 的长度的两倍）。
- $t$ 是$s$ 的子串。
- 在满足上面3个条件的情况下，$s$ 需要有最小的周期$k$ 。

这里的$t$ 是$s$ 的子串就是说当$s$ 删除$0$个或更多个字符后（不能改变顺序），$s$ 就变成了$t$ 。例如```011```就是```10101```的子串。


### 输入格式
第一行是一个正整数$T$，表示数据的组数。

接下来$T$行，每行有一个只包含```0```和```1```的字符串$t$ $(1\le|t|\le100)$。
### 输出格式
如果有多种解，输出一个符合条件的字符串$s$ 即可。
# 题目分析
这题比较棘手的可能就是这个最小周期$k$了。但仔细看样例，就会发现，这个周期不是$1$就是$2$，当周期为$1$的时候更是有一个规律：整个字符串只包含```0```或只包含```1```。

其实也的确如此，当整个字符串$t$ 只包含```0```或只包含```1```时，就可以构造出一个字符串$s$ 使得$t=s$ ，那么这就是第一种可能了。

如果字符串$t$ 有```0```有```1```的话，周期肯定不可能是$1$了，那就要想办法把周期变为$2$。问题就可以转化为将字符串$t$ 拓展为形如```010101010......```的字符串。如果能做到，周期为$2$，自然是最优解。如果做不到，那就要看其他方法了。

巧了，还真就做得到！
如果$t$ 的第1个字符是```1```，那就在```1```屁股后面加个```0```。那接下来的第$2,3...n$个字符，如果跟当前构造的$s$ 的最后一个字符的不一样，就可以直接放上去，然后再补一个和自己不一样的。如果一样，就先补一个和自己不一样的，在把自己放上去。这样就可以构造一个为```010101...```的字符串了。那么在输出的时候就可以不用这么麻烦，只需要看前面的是```0```还是```1```，是```1```就补上```01```，是```0```就补上```10```。
# 上代码
```cpp
#include <cstdio>
#include <iostream>
#include <string>
using std::string;
using std::cin;

int T;
string t,str;

char fun(char ch){if(ch=='1')return '0';return '1';}
inline int read();

int main(){
	T=read();
	while(T--){
		t.clear();str.clear();
		cin>>t;
		if(t.find('1')==string::npos || t.find('0')==string::npos){printf("%s\n",t.c_str());continue;}//如果只包含0(找不到1)或只包含1(找不到0)，就直接输出原字符串
		str+=t[0];str+=fun(t[0]);	//先构造第一个字符串t[0]
		for(int i=1;i<t.size();++i)	//i从1开始（t[1]）
		if(str[str.size()-1]=='0'){	//如果前一个是0
			str+='1';
			str+='0';				//补上10
		} else {					//如果前一个是1
			str+='0';
			str+='1';				//补上01
		}
		printf("%s\n",str.c_str());	//输出
	}
    return 0;
}

inline int read(){
    int x=0,f=1;char ch=getchar();
    while(ch>'9' || ch<'0'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    return x*f;
}
```

---

## 作者：do_while_true (赞：0)

如果原数列全为 $1$ 或 $0$ ，输出全 $1$ 或 $0$ 就可以。

如果不是的话，如果出现 $01$，就输出 $0101010101...$（即如果出现一个 $1$ ，前面加一个 $0$，如果出现一个 $0$ ，后面加上一个 $1$ ）

如果出现 $10$ ，就输出$1010101010...$，理由同上。

后两种情况具体长度为 $2|t|$。

### $\mathcal{Code:}$
```cpp
#include<iostream>
#include<cstdio>
#include<string>
using namespace std;
int T;
string str;
int main()
{
	cin>>T;
	while(T--)
	{
		bool l=0,y=0;
		int yl=-1,ly=-1;
		cin>>str;
		int len=str.size();
		for(int i=0;i<len;i++)
			if(str[i]=='0') l=1;
			else y=1;
		if(l&&!y||y&&!l)
			for(int i=0;i<len;i++)
				printf("%c",str[i]);
		else {
			for(int i=0;i<len-1;i++){
				if(str[i]=='0'&&str[i+1]=='1'&&ly==-1) ly=i;
				if(str[i]=='1'&&str[i+1]=='0'&&yl==-1) yl=i;
			}
			bool f=0;
			if(yl==-1) f=1;
			for(int i=0;i<len;i++)
			{
				if(!f) {
					if(i==yl||i==yl+1) printf("%c",str[i]);
					else  printf("10");
				}
				else {
					if(i==ly||i==ly+1) printf("%c",str[i]);
					else  printf("01");
				}
			}
		}
		puts("");
	}
	return 0;
}
```


---

