# Robot Bicorn Attack

## 题目描述

Vasya plays Robot Bicorn Attack.

The game consists of three rounds. For each one a non-negative integer amount of points is given. The result of the game is the sum of obtained points. Vasya has already played three rounds and wrote obtained points one by one (without leading zeros) into the string $ s $ . Vasya decided to brag about his achievement to the friends. However, he has forgotten how many points he got for each round. The only thing he remembers is the string $ s $ .

Help Vasya to find out what is the maximum amount of points he could get. Take into account that Vasya played Robot Bicorn Attack for the first time, so he could not get more than 1000000 ( $ 10^{6} $ ) points for one round.

## 说明/提示

In the first example the string must be split into numbers 1, 2 and 34.

In the second example the string must be split into numbers 90, 0 and 0.

In the third example the string is incorrect, because after splitting the string into 3 numbers number 00 or 09 will be obtained, but numbers cannot have leading zeroes.

## 样例 #1

### 输入

```
1234
```

### 输出

```
37
```

## 样例 #2

### 输入

```
9000
```

### 输出

```
90
```

## 样例 #3

### 输入

```
0009
```

### 输出

```
-1
```

# 题解

## 作者：Rosmarinus (赞：1)

## 题意简述

给定一串长度 $\le 30$ 的字符串，要求将其分为无前导 $0$ 且 $\le 10^6$ 的三个数字，使它们的和最大，输出这个和。

## 思路分析

很明显，我们的代码要分为两部分：拆字符串 $+$ 化字符串为数字。

考虑到长度 $\le 30$，我们可以直接暴力拆字符串。

将字符串拆成三串，显然只需要枚举两个断点。

**Code**：

```cpp
cin >> s;
for(int i = 0; i < s.size(); i ++)
{
    for(int p = i + 1; p < s.size() - 1; p ++)
    {
        if((s[0] == '0' && i > 0) || (s[i + 1] == '0' && p > i + 1) || (s[p + 1] == '0' && p + 1 != s.size() - 1)) continue;// 判前导 0，注意单独的 0 不算
        ans = max(ans, f(0, i) + f(i + 1, p) + f(p + 1, s.size() - 1)); 
    }
}
```

接下来是函数 $f$ 的部分：

```cpp
int f(int l, int r)
{
    int t = 0;
    for(int i = l; i <= r; i ++)
    {
        t = t * 10 + s[i] - '0';
        if(t > 1000000) return - 99999999;//判不超过 1000000
    }
    return t;
}
```

**完整代码：**
```cpp
#include<iostream>
using namespace std;

string s;

int f(int l, int r)
{
    int t = 0;
    for(int i = l; i <= r; i ++)
    {
        t = t * 10 + s[i] - '0';
        if(t > 1000000) return - 99999999;
    }
    return t;
}

int main()
{
    int ans = -1;
    cin >> s;
    for(int i = 0; i < s.size(); i ++)
    {
        for(int p = i + 1; p < s.size() - 1; p ++)
        {
            if((s[0] == '0' && i > 0) || (s[i + 1] == '0' && p > i + 1) || (s[p + 1] == '0' && p + 1 != s.size() - 1)) continue;
            ans = max(ans, f(0, i) + f(i + 1, p) + f(p + 1, s.size() - 1)); 
        }
    }
    cout << ans << endl;
    return 0;
}
```

---

## 作者：Katsura_Hinagiku (赞：1)

暴力枚举题，注意细节

首先字符串长度小于3（无法分成三份）或大于21（肯定至少有一份大于1e6）直接输出-1

枚举割开的位置，若这种分割方式合法，ans取ans与这样分割的和的较大值

```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;
string s;
int maxn=-1;
bool steins(int l,int r)//是否有前导0
{
	if(s[l]=='0'&&l!=r)return 1;
	return 0;
}
int getval(int l,int r)//一段的值
{
	int tmp=0;
	for(int i=l;i<=r;++i)
	{
		tmp=tmp*10+s[i]-'0';
	}
	return tmp;
}
int check(int l,int r)
{
	if(steins(0,l)||steins(l+1,r)||steins(r+1,s.length()-1))return -1;
	if(getval(0,l)>1000000||getval(l+1,r)>1000000||getval(r+1,s.length()-1)>1000000)return -1;
	return getval(0,l)+getval(l+1,r)+getval(r+1,s.length()-1);
}
int main()
{
	cin>>s;
	if(s.length()>21||s.length()<3)
	{
		printf("-1\n");
		return 0;
	}
	for(int i=0;i<s.length()-2;++i)
	{
		for(int j=i+1;j<s.length()-1;++j)
		{
			if(i+1>7||j-i>7||s.length()-j-1>7)continue;
			maxn=max(maxn,check(i,j));
		}
	}
	printf("%d\n",maxn);
	return 0;
}
```

---

## 作者：billtun (赞：1)

## 题目大意：

给一个由数字构成的字符串（长度不超过 $30$），将其划分成三段小于 $10^6$ 的数字（不含前导零）。如果不能按照要求划分，输出负一。

## 注意：

小于 $10^6$ 的数字，不用写高精！

## 思路：暴力。

分成三段会出现两个断点，那么就枚举这两个断点，分别求出两两之间划分出来的数字，记录和比大小。

## 代码：

```cpp
#include<bits/stdc++.h>
#define ll long long // long long 不可少（调了2小时）

using namespace std;

ll maxl=-9223372036854775807;
string s;

ll change_to_Num(ll l, ll r){ // 取数
	if(l!=r && s[l]=='0'){ return -2147483647; } // 判断
	ll res=0;
	for(ll i=l;i<=r;i++){
		res=res*10+s[i]-'0';
		if(res>1000000){ return -2147483647; } // 返回负极大值，方便输出比较
	}
	return res;
} // O(6)

int main()
{
	cin>>s;
	
	if(s.size()<3){ // 特判（不加也可）
		cout<<-1;
		return 0;
	}
	
	for(ll l=0;l<(ll)s.size();l++){ // 枚举
		for(ll r=l+1;r<(ll)s.size()-1;r++){
			maxl=max(maxl, change_to_Num(0, l)+change_to_Num(l+1, r)+change_to_Num(r+1, s.size()-1));
		}
	} // O(30*30*6)
	
	cout<<(maxl>-1 ? maxl : -1); // 和不可能为负数，所以若为负数则无法划分
	return 0;
}
```

---

## 作者：ZBAA_MKC (赞：1)

### 题意

给定一个长度不大于 $30$ 的字符串，求出一种将这个整数划分为 $3$ 个不超过 $10^6$ 的正整数（不包含前导 $0$，但单独的一个 $0$ 是被允许的）输出这个最大的和。

### 思路分析

这题数据范围很小，枚举所有可能的划分情况就可以了。

但是在写求和函数时，一定要把超过 $10^6$ 的情况设为一个非常小的数（小于$-2\times10^6$)，否则有可能在测试点 $8$ 或 $12$ WA 掉。

### 代码实现

```cpp
#include <iostream>
#include <string>
using namespace std;

string s;
inline int sum(int l, int r) //求和
{
	int x = 0;
	for (int i = l; i <= r; i++)
	{
		x = x * 10 + s[i] - '0';
		if (x > 1000000)
		{
			return -19198100; //这里看好不要少打一个0（
		}
	}
	return x;
}

bool zero(int i, int j) //判前导0
{
	return ((s[0] == '0' && i > 0) || (s[i + 1] == '0' && j > i + 1) || (s[j + 1] == '0' && j + 1 != s.size() - 1));
}

int main()
{
	int ans = -1;
	cin >> s;
	int len = s.size();
	if (len <= 2)
	{
		puts("-1");
		return 0;
	}
	for (int i = 0; i < len; i++)
	{
		for (int j = i + 1; j < len - 1; j++)
		{
			if (!zero(i, j))
			{
				ans = max(ans, sum(0, i) + sum(i + 1, j) + sum(j + 1, len - 1)); //计算和
			}
		}
	}
	cout << ans;
	return 0;
}
```

---

## 作者：Lijunzhuo (赞：0)

[原题传送门](https://www.luogu.com.cn/problem/CF175A)  
这是一道**暴力枚举题**，做法：  
1. 输入数据。
2. 枚举分割点。
3. 判断是否满足要求。
4. 求最大值。
5. 输出结果。

代码：
```cpp
#include<bits/stdc++.h>//时间复杂度O(n^3)。
using namespace std;
string s;
long long len,l,a,b,c,maxn=-114514,ansa,ansb,ansc;
long long f(long long lf,long long r)
{
	if(s[lf]=='0'&&lf!=r) return -1;
	l=0;
	for(long long i=lf;i<=r;i++)
	{
		l=l*10+s[i]-'0';
		if(l>1000000) return -1;
	}//printf("%lld %lld\n",lf,r);
	return l;
}
int main()
{
	cin>>s;
	len=s.length();
	if(len>21||len<3)
	{
		printf("-1");
		return 0;
	}
	for(long long i=1;i<len;i++)
		for(long long j=i+1;j<len;j++)
		{
			a=f(0,i-1);
			b=f(i,j-1);
			c=f(j,len-1);
			if(a!=-1&&b!=-1&&c!=-1)
			{
				if(maxn<a+b+c)
				{
					maxn=a+b+c;
					ansa=a;ansb=b;ansc=c;
				}
			}
		}
	if(maxn!=-114514) printf("%lld\n",maxn);
	else printf("-1\n");
	//printf("%lld %lld %lld\n",ansa,ansb,ansc);
	return 0;
}
```
[134测试点的记录详情](https://www.luogu.com.cn/record/134020522)

---

## 作者：qingchenMC (赞：0)

# CF175A Robot Bicorn Attack 题解

[CF175A Robot Bicorn Attack](https://www.luogu.com.cn/problem/CF175A)

#### 题目大意

给定一个长度小于等于 $30$ 的字符串，把这个字符串分割成三段无前导零且不大于 $1000000$ 的非负整数，求这三个数的和的最大值。如果无法划分，输出 `-1`。

#### 解题思路

由于此题数据范围不大，只需要两层嵌套循环枚举两个割开的位置即可。但要注意：

1. 三个数均为无前导零且不大于 $1000000$ 的非负整数。

2. 如果无法划分，输出 `-1`。

补充一点，C++的 `stoll()` 函数可以将 `string` 类型转为 `long long` 类型的整数。

#### 代码

```cpp
#include<bits/stdc++.h>

using namespace std;

bool pd(string a){//判断是否在值域中（如果不在值域中，stoll()函数会Runtime Error）
	long long ans=0;
	for(auto i:a){
		ans*=10;
		ans+=i-'0';
		if(ans>1000000){
			return true;
		}
	}
	return false;
}

int main(){
	long long ans=-1;//初始为-1，如果没有符合条件的分割方式，输出为-1。
	string s;
	cin>>s;
	if(s.length()<3||s.length()>21){//长度超限
		cout<<"-1"<<endl;
		return 0;
	}
	for(int i=1;i<=s.length()-2;i++){//每段长度>=1
		for(int j=i+1;j<=s.length()-1;j++){//依次枚举两个分割点
			string a,b,c;
			for(int k=0;k<s.length();k++){//分割到三个字符串中
				if(k>=0&&k<=i-1){
					a+=s[k];
				}
				else if(k>=i&&k<=j-1){
					b+=s[k];
				}
				else{
					c+=s[k];
				}
			}
                        //判断有无前导0
			if(a[0]=='0'&&a.length()!=1){
				continue;
			}
			else if(b[0]=='0'&&b.length()!=1){
				continue;
			}
			else if(c[0]=='0'&&c.length()!=1){
				continue;
			}
			else if(pd(a)||pd(b)||pd(c)){//判断是否在值域内
				continue;
			}
			else{
				ans=max(ans,stoll(a)+stoll(b)+stoll(c));//ans取最大值
			}
		}
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：Dongliang1 (赞：0)

### 题意

~~首先谴责一下翻译没有点出字符串长度的范围。~~

给一个长度不大于 $30$ 的字符串，将其划分成三段无前导零且不超过 $10^6$ 的非负整数，使它们的和最大。如果无法这样划分，输出 `-1`。

### 思路

枚举所有字符串的拆分可能，算出所对应的数。分别校验这些拆分出来的数是否符合条件，即无前导零和不超过 $10^6$。

对于不满足第一个条件的，显然的，判断该数是否不为 $0$ 且这个数的第一项为 $0$ 即可。

对于不满足第二个条件的，我们首先可以想到暴力求出值后判断大小，但考虑到枚举时数的数位有可能达到字符串的长度，即约 $30$，这是 `long long` 存不下的，所以我们要边算当前对应的数的同时判断数是否超过范围。

枚举拆分可能非常简单，第一重循环枚举第一个数的末位，第二重循环枚举第二个数的末位，算对应的数的时候各种方法都可以，不多赘述。

```
#include<bits/stdc++.h>

using namespace std;

const int N=1e6+5;

int a[N];

int check(int l,int r)
{
	if(a[l]==0&&l!=r)
	{
		return -1;
	}
    int sum=0;
    for(int i=l;i<=r;i++)
    {
        sum*=10;
        sum+=a[i];
        if(sum>1e6)
		{
			return -1;
		}
    }
	return sum;
}


int main()
{
    string s;
    cin>>s;
    int n=s.size();
    for(int i=0;i<s.size();i++)
    {
        a[i+1]=s[i]-'0';
    }
    int ans=-1;
    for(int i=1;i<=n-2;i++)
    {
        for(int j=i+1;j<=n-1;j++)
        {
            int x1=check(1,i);
            int x2=check(i+1,j);
            int x3=check(j+1,n);
            if(x1!=-1&&x2!=-1&&x3!=-1)
            {
                ans=max(ans,x1+x2+x3);
            }
        }
    }
    cout<<ans<<"\n";
}

```

---

## 作者：IOI_AK_TLR (赞：0)

# 题意回顾

给定一个数字字符串，把它分割为三个连续的段，使得每段组成的数没有前导零且不超过 $10^{6}$，还要使得这三段和最大，输出最大和。


------------


# 题意分析

考虑两层循环枚举分割位置，再判断三个数是否符合条件，最后求和并更新答案。

------------

# 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;
string s,a,b,c;
int x,y,z;
int ans=-1;
const int MAX=1e6;
int main()
{
	cin>>s;
	for(int i=0;i<(int)s.size()-2;i++)
	{
		for(int j=i+1;j<(int)s.size()-1;j++)
		{
			a=s.substr(0,i+1);
			b=s.substr(i+1,j-i);
			c=s.substr(j+1);
			if(a.size()>7||b.size()>7||c.size()>7||(a[0]=='0'&&a.size()>1)||(b[0]=='0'&&b.size()>1)||(c[0]=='0'&&c.size()>1))	//过滤掉有前导零和位数过多的数（防止爆int） 
				continue;
			x=stoi(a);
			y=stoi(b);
			z=stoi(c);
			if(x>MAX||y>MAX||z>MAX)	//位数不超过7位的数不一定不超过1e6，因此要特判一下 。 
				continue;
			ans=max(ans,x+y+z);
		}
	}
	cout<<ans;
	return 0;
}

```


---

## 作者：VitrelosTia (赞：0)

这道题让我们在一个由数字组成的字符串中截出三段，将每段转为数字之后求和，要求这个和的最大值。由于字符串的长度很短，我们可以直接枚举第一个字符串的结尾和第三个字符串的开头，这样直接就截出了三个字符串。我们可以使用 `substr` 函数，再使用经典的拆位将字符串转数字，同时判断是否合法就可以了。

这里指出两个~~我踩了的~~坑点：一是由于字符串最长能达到 $30$ 位，开 `long long` 不够用，所以要在字符串转数字的时候边转边判断是否超过了值域。二是判断前导零的时候要考虑 `0` 也是合法的。

```
int f(string s) {
	if (s[0] == '0' && s.size() > 1) return -1;
	int ans = 0;
	for (auto ch : s) {
		ans = ans * 10 + ch - '0';
		if (ans > 1000000) return -1;
	}
	return ans;
}

void solve() {
    string s;
    cin >> s;
    for (int i = 1; i < s.size(); i++) {
    	for (int j = i + 1; j < s.size(); j++) {
    		string a = s.substr(0, i),
    			   b = s.substr(i, j - i),
    			   c = s.substr(j);
    		if (f(a) == -1 || f(b) == -1 || f(c) == -1) continue;
    		ll now = f(a) + f(b) + f(c);
    		ans = max(ans, now);
    	}
    }
    cout << ans;
}
```

---

## 作者：achjuncool (赞：0)

# 做法

首先，$s$ 的长度最大就到 $30$。

于是 $O(n^2)$ 暴力枚举。

枚举第一段的右端点与第二段的右端点，并检查三个数字是否都合法，合法就更新答案。

这里有用到函数 `substr`，用于切割字符串。

用法是 `s.substr(a, b)`，其中 $s$ 是原字符串，$a$ 是子串起始点下标，$b$ 是子串长度。

至于字符串转数字，见下面代码注释。（~~其实就是懒得写~~）

# Code

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define qwq ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define endl '\n'
string s;
ll len, ans = -1;
ll func(string a){ //将字符串转化成数字，并检查是否合法，不合法就返回 -1 
	if(a.length() > 6){ //切出来的数必须小于等于 1e6 
		if(a == "1000000") return 1000000;
		else return -1;
	}
	if(a[0] == '0' && a.length() > 1) return -1; //不能有前导 0，本身就是 "0" 是一种特殊情况 
	ll ret = 0;
	for(ll i = 0; i < a.length(); i++) ret = ret * 10 + a[i] - '0'; //从高到低逐位转化 
	return ret;
}
int main(){
	qwq; //是一个优化（
	cin >> s;
	len = s.length();
	s = " " + s; //个人习惯下标从 1 开始（ 
	for(ll i = 1; i <= len - 2; i++){ //i 表示第一刀切在第 i 个字符后面 
		for(ll j = i + 1; j <= len - 1; j++){ //j 表示第二刀切在第 j 个字符后面 
			ll a = func(s.substr(1, i)), b = func(s.substr(i + 1, j - i)), c = func(s.substr(j + 1, len - j));
			//上面一行将这种切法切出来的三个数求了出来 
			if(a == -1 || b == -1 || c == -1) continue; //不合法 
			else ans = max(ans, a + b + c); //合法就更新答案 
		}
	}
	cout << ans << endl;
	return 0;
}

```

---

## 作者：_Jonny_404 (赞：0)

[推荐博客阅读](https://www.luogu.com.cn/blog/662037/solution-cf175a#)

这是一道考验对字符串的使用的题。我们可以枚举其中 $2$ 个字符串的长度，并通过前 $2$ 个字符串的长度来确定第 $3$ 个字符串的长度，再通过枚举的长度来截取三个字符串。这里截取字符串的方法是：  
```cpp
s.substr(i,l);

```
其作用为：提取并返回字符串 $s$ 中下标 $i$ 开始长度为 $l$ 的一段，即 $s_i$ 至 $s_{i+l-1}$。

截取后是依次判断。如果有任意一个字符串的长度超过了 $7$，说明这个字符串表示的数的值一定 $\ge 10^{7}$。

接着就是判断前导 $0$ 了。判断前导 $0$ 时需要注意：

1. 为了防止这个字符串就是`0`而造成错误，可以令下标只从 $0$ 枚举到 $len-2$（$len$ 是字符串的长度），这样就可以只把前面多余的前导 $0$ 给查出来。
2. 如果直接写：  
```cpp
for(int i=0;i<=len-2;i++)
		if(s[i]=='0')
			return 0; 
```  
那么当遇到`12040`这样的字符串时会造成判断错误。其实，一旦在发现 $0$ 之前出现了某个 $1 \sim 9$ 之间的数，后面出现的 $0$ 就不算是前导 $0$ 了，直接`break`就行了。

当判断成功后，我们再把三个字符串表示的数依次求出来。最终结果，就是在每组合法的字符串的和中取最大值就行了。

总代码见下：
```cpp
#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

#define p 1000000

string s;
int ans=-2147483647;

bool ch(string s)
{
	int len=s.size();
	if(len>7)
		return 0;
	for(int i=0;i<len-1;i++)
		if(s[i]=='0')
			return 0;
		else
			break;
	int a=0;
	for(int i=0;i<len;i++)
		a=a*10+(s[i]-'0');
	if(a<=p)
		return 1;
	return 0;
}

int sh(string s)
{
	int len=s.size();
	int a=0;
	for(int i=0;i<len;i++)
		a=a*10+(s[i]-48);
	return a;
}

int main()
{
	cin>>s;
	int len=s.size();
	for(int d1=1;d1<=len-2;d1++)
		for(int d2=1;d2<=len-d1-1;d2++)
		{
			int d3=len-d1-d2;
			string s1=s.substr(0,d1);
			string s2=s.substr(d1,d2);
			string s3=s.substr(d1+d2,d3);
			if(ch(s1)&&ch(s2)&&ch(s3))
				ans=max(ans,sh(s1)+sh(s2)+sh(s3));//取max
		}
	if(ans!=-2147483647) cout<<ans<<endl;
	else cout<<-1<<endl;
	return 0;
}
```

---

## 作者：Edmundino (赞：0)

# 题意

给你一个字符串，让你将其分为三段使得每一段没有前导 $0$，且大小不超过 $10^6$。

# 分析

字符串的长度好像不超过 $30$ 。

所以，我们可以去枚举所有情况，

那么我们如何判断此情况符合条件呢？

首先，当它不止 $1$ 位时，它的第一位不能为 $0$。

同时，把它转换为整数后，它的大小不超过 $10^6$。

然后根据此情况求和，更新最大值即可。

# 代码

**判断部分**

```cpp
ll jc(int l,int r){
	if(l!=r&&c[l]=='0')return -1;
	long long res = 0;
    for(int i=l;i<=r;i++)
    {
        res=res*10+(c[i]-'0');
        if(res>1000000)
            return -1;
    }
    return res;
}
```


**枚举部分**

```cpp
for(int i=1;i<lon;i++){
	for(int j=i+1;j<lon;j++){
		s1=jc(0,i-1);s2=jc(i,j-1);s3=jc(j,lon-1);
		if(s1>=0&&s2>=0&&s3>=0){
				maxs=max(s1+s2+s3,maxs);s=1;
		}
	}
}
```


---

