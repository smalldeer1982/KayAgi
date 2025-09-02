# Not simply beatiful strings

## 题目描述

如果一个字符串的字母可以重新排列成两组相等的符号（注意不同的组必须包含不同的符号），那么我们就称它为可爱的字符串。例如，字符串ababa是可爱的字符串（你可以把它转换成aaabb，其中前三个字母组成一组a-s，其他字母组成一组b-b-s），但c并不是因为在每一个可能的后续分区字母中这两组是重合的。


你得到了一个字符串s。检查是否可以将其拆分为两个非空子序列，以使这些子序列形成的字符串非常可爱。这里的子序列是字符串的任意索引集。

## 样例 #1

### 输入

```
ababa
```

### 输出

```
Yes
```

## 样例 #2

### 输入

```
zzcxx
```

### 输出

```
Yes
```

## 样例 #3

### 输入

```
yeee
```

### 输出

```
No
```

# 题解

## 作者：きりと (赞：5)

[题目传送门](https://www.luogu.com.cn/problem/CF955B)

### 题意转化：

给你一个字符串$s$，问你能不能把$s$分成两部分，使得每部分都有且只有两种字母

~~转化以后，题目似乎简单了不少呢~~

### 思路：

- 首先，要使每部分有且只有两个字母，所以$s$中的字母种数不能超过4，也不能少于2，而且$s$的长度也不能少于4

所以先判一下qwq

- 然后，分类讨论：

	1. 当$s$中有2种字母时，要满足条件，两种字母一定要都至少有两个

	2. 当$s$中有3种字母时，要满足条件，有一种字母至少有两个

	3. 当$s$中有4种字母时，无论如何都满足条件

所以开个桶，特判一下即可

### 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int num[27];
int main()
{
	string s;
	cin>>s;
	int cnt=0;
	if(s.size()<4)
	{
		cout<<"No"<<endl;
		return 0;
	}
	int w;
	for(int i=0;i<s.size();i++)
	{
		int w=s[i]-'a'+1;
		num[w]++;
		if(num[w]==1)
		{
			cnt++;
		}
	}
	if(cnt<2||cnt>=5)
	{
		cout<<"No"<<endl;
		return 0;
	}
	if(cnt==2)
	{
		bool flag=0;
		for(int i=1;i<=26;i++)
		{
			if(num[i]==1)
			{
				flag=1;
			}
		}
		if(flag)
		{
			cout<<"No"<<endl;
			return 0;
		}
	}
	if(cnt==3)
	{
		bool flag=0;
		for(int i=1;i<=27;i++)
		{
			if(num[i]>1)
			{
				flag=1;
			}
		}
		if(!flag)
		{
			cout<<"No"<<endl;
			return 0;
		}
	}
	cout<<"Yes"<<endl;
	return 0;
}
```


---

## 作者：Arrtan_73 (赞：1)

# 题目大意
[Link_Not simply beatiful strings](https://www.luogu.com.cn/problem/CF955B)
# 题目思路
首先我们先来思考一下两种不可能的情况：

- $\text{字母种类数}=1$，显而易见，不可能构造出每部分都有且只有两种字母的形式。
- $\text{字母种类数}>4$，同理，也不可能构造成功。

现在我们已经把范围缩得很小了，只需要对剩下 $3$ 类进行分类讨论即可。

- $\text{字母种类数}=2$，只有可能构造出 `ab` 与 `ba` 的形式，说明两种字母的个数都必须大于 $1$，否则不成立。

- $\text{字母种类数}=3$，只有可能构造出 `ab` 与 `bc` 的形式，说明至少一个字母的个数必须大于 $1$，否则不成立。

- $\text{字母种类数}=4$，必然成立。

所以最后只需要一连串判断即可。

PS：这里可以用 set 自动去重。

# Code
```cpp
#include <bits/stdc++.h>
using namespace std;
set<int> Q;
int b[200];

int main() {
	char c;
	while (cin >> c) {
		Q.insert(c);
		b[c]++;
	}
	if (Q.size() < 2 || Q.size() > 4) {//特判不可能
		cout << "No";
		return 0;
	}
	switch (Q.size()) {
		case 2: {//字母种类数=2
			for (int i = 'a'; i <= 'z'; i++)
				if (b[i] == 1) {
					cout << "No";
					return 0;
				}
			break;
		}
		case 3: {//字母种类数=4
			bool cnt = false;
			for (int i = 'a'; i <= 'z'; i++)
				if (b[i] > 1) {
					cnt = true;
					break;
				}
			if (!cnt) {
				cout << "No";
				return 0;
			}
			break;
		}
	}
	cout << "Yes";
	return 0;
}
```


---

## 作者：追梦之鲸 (赞：1)

[Link](https://www.luogu.com.cn/problem/CF955B)

###### ~~貌似还没有用 set 的，赶紧来水一发。~~

#### 题面描述

给你一个字符串 $s$，问能不能把这个字符串分成两组，使每组都有且只有两种字母。

#### 思路

首先，要使每组都有两种字母，$s$ 的长度不能小于 $4$，且其中字母的种类不能小于 $1$ 或大于 $4$。

然后再分类讨论 $s$ 的字母种类为 $2,3,4$ 的情况：

1. 当 $s$ 的字母种类为 $2$ 时，需要保证每种字母的数量必须大于 $2$，否则就会有一组只有一种字母。
2. 当 $s$ 的字母种类为 $3$ 时，需要保证至少有一种字母的数量大于 $1$，否则也会有一组只有一种字母。
3. 当 $s$ 的字母种类为 $4$ 时，没有要求。只需把两种字母分到一组，把剩下的两组字母分到二组即可。

好了，知道思路了，下面谈谈如何用代码实现上面的操作。

首先我选用的是 set 。因为它有自动去除的特性，利用这个特性我们可以直接求 $s$ 的字母的种类。

然后我又用了个桶装每种字母出现的次数，也就是它的数量。

对于不知道 set 是什么的朋友，请自行百度，不想百度的在代码里我也做了注释，直接看就行了。

#### Code
```c
#include<bits/stdc++.h>
using namespace std;
set<char > q;
//定义一个 set，存储类型为 char，名字为 q
int a[200];
int n;
signed main()
{
	string s;
	cin>>s;
	n=s.size();
	for(int i=0;i<n;i++)
	{
		q.insert(s[i]);
		//把 s[i] 放进 q 里
        a[s[i]]++;
		//这里的字符会自动转化为数字，例如`a`会被转化成 97（也就是它的ASCII码），当然这样写纯粹是因为懒
	}
	if(q.size()<2||q.size()>4||s.size()<4)//特判
    {
		return cout<<"No",0;
	}
    //，因为 set 有自动去除的属性，而 q.size() 是指 q 的里存储的字母的数量，所有这里的 q.size() 其实就是 s 的字符的种类数
	if(q.size()==2)
	{
		bool tag=false;
		for(int it='a';it<='z';it++)//从'a'的数量一直搜到'z'的数量
		{
			if(a[it]==1)
			{
				tag=true;
				break;
			}
		}
		if(tag)
		{
			return cout<<"No",0;
            //这里是一个压行，展开是：cout<<"No";return 0;
		}
	}
	else if(q.size()==3)
	{
		bool tag=false;
		for(int it='a';it<='z';it++)
		{
			if(a[it]>1)
			{
				tag=true;
				break;
			}
		}
		if(!tag)
		{
			return cout<<"No",0;
		}
	}
	cout<<"Yes";
	//没有错误输出"Yes"
	return 0;
}
```

---

## 作者：MuLinnnnn (赞：0)

[洛谷传送门](https://www.luogu.com.cn/problem/CF955B)

**题意：**

一个串到底可不可爱的定义是（自我理解）：有且仅有 $2$ 种字母。

本题要求判断输入的串是否可以拆分成两个子串，并且保证两个子串都为“可爱的子串”。我们一眼直接分类讨论。

首先，如果一个串可以被分为两部分且都“可爱”，那么那最小的长度一定是 $4$，也就是每个字母出现一次，只有四个字母，比如 $\texttt{abcd}$。那么也就是说，一个串如果长度小于 $4$，那么它一定不符合题意。

其次，可以看出，这个符合要求的串的不同种类字母数量一定在 $2$ 到 $4$ 中，所以直接判断。

- 如果字母数量为 $4$，那么是一定可以满足题意的。
- 如果字母数量为 $3$，那么必须有一个字母出现的次数 $\ge 2$ 的，这样它才可以被分到两个子串里。
- 如果字母数量为 $2$，那么这两个字母出现的次数必须都 $\ge 2$，因为这样也才能被分到两个子串里。

最后的问题来到了如何知道**到底有多少种字母**和**每种字母出现的次数**。因为题目要求只有小写字母，所以我用到了 Hash 表，以便在 $O(N)$ 预处理的时间内完成我们要做的内容。当然不太熟悉 Hash 表的也可以使用枚举计数，这里就不展示枚举的代码了。

**代码：**

```cpp
/*
	Name: CF655B
	Author: MuLin_Aptr
	Date: 03-03-24 20:25
	Description: Talk is cheap, show me the CODE!
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
#include <cstring>
typedef long long ll;
#define endl '\n'
#define NO cout << "No" << endl; exit(0)
#define YES cout << "Yes" << endl; exit(0)
using namespace std;
ll Hash[50];

void Check2() {
	ll chk = 0;
	for(ll i = 1; i <= 26; ++i) {
		if(Hash[i] >= 2) {
			chk++;
		}
	}
	if(chk == 2) {
		YES;
	} else {
		NO;
	}
	return ;
}

void Check3() {
	ll chk = 0;
	for(ll i = 1; i <= 26; ++i) {
		if(Hash[i] >= 2) {
			chk++;
		}
	}
	if(chk >= 1) {
		YES;
	} else {
		NO;
	}
	return ;
}

int main() {
	string s;
	cin >> s;
	if(s.length() < 4) {
		NO;
	}
	ll tot = 0;
	for(ll i = 0; i < s.length(); ++i) {
		ll hash = (ll)(s[i]) - 96;
		if(!Hash[hash]) {
			++tot;
		}
		++Hash[hash];
	}
	if(tot < 2 || tot > 4) {
		NO;
	}
	switch(tot) {
		case 2:
			Check2();
		case 3:
			Check3();
		case 4:
			YES;
	}
	NO;
	return 0;
}

```

有点丑陋，将就着看看吧。

[AC记录](https://www.luogu.com.cn/record/149239955)。

---

## 作者：_int123_ (赞：0)

## CF955B Not simply beatiful strings

### 题意：

给你一个字符串 $s$，问你能不能把 $s$ 分成两部分，使得每部分都有且仅有两种字母。

### 思路：

1. 根据题目，我们不难知道可以定义两个计数器，分别记录有几种字母以及其个数，由于是字符串，我们可以用 `map` 实现。

2. 不难看出如果总的字母数量小于 $4$ 了，就不可能满足两边都有两种字母。

3. 记录完字母种类以及其个数后，不难发现如果字母种类不是 $2$，$3$，$4$ 就不行。

4. 之后分情况讨论，如果有两种字母，那有一种只有一个那肯定不行；如果有三种字母，那没有数量大于一个的字母肯定不行；如果有四种字母，不难发现肯定是可以的。

### AC 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
map <char,int> m;//记录字母个数 
int cnt=0;//记录有几种字母 
int main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);//加速 
	cin>>s;
	if(s.size()<4)//如果字母数量小于 4 了，不可能满足两边都有两种字母 
	{
		cout<<"No";
		return 0;
	}
	for(int i=0;i<s.size();i++)//有几种字母与字母个数 
	{
		m[s[i]]++;
		if(m[s[i]]==1) cnt++;
	}
	if(cnt<=1||cnt>=5)//如果字母种类不是 2,3,4 就不行 
	{
		cout<<"No";
		return 0;
	}
	if(cnt==2)
	{
		for(auto x:m)
		{
			if(x.second==1)//如果有一种只有一个那肯定不行 
			{
				cout<<"No";
				return 0;
			}
		}
	}
	if(cnt==3)
	{
		bool flag=0;
		for(auto x:m)//如果没有大于一个的字母肯定不行 
			if(x.second>1)
				flag=1;
		if(flag==0)
		{
			cout<<"No";
			return 0;
		}
	}
	cout<<"Yes";
	return 0;
}
```

完结撒花！！！

---

## 作者：lol_qwq (赞：0)

# CF955B 题解

**简化题意**

给你一个字符串 $s$，问你能不能把 $s$ 分成两部分，使得每部分都有且只有两种字母。

**思路**

首先，要使每部分有且只有 $2$ 个字母，所以 $s$ 中的字母种数不能超过 $2 \times 2 = 4$，也不能少于 $2$，而且 $s$ 的长度也不能少于 $2 \times 2 = 4$。

**因此下面有几类**

当 $s$ 中有 $2$ 种字母时，要满足条件，仅需两种字母一定要都至少有两个。

当 $s$ 中有 $3$ 种字母时，要满足条件，只要有一种字母至少有两个。

当 $s$ 中有 $4$ 种字母时，只要把两个不同类分成 $1$ 组即可。

---

## 作者：rai1gun (赞：0)

### 1.解题思路
我们先判断字符串的长度，如果小于 $4$ 那么直接输出 ```No```。

接下来分情况讨论：

1.字符串的种类只有 2 种。如果是这样，那么；两种字符的个数必须要 $\geq 2$。

2.字符串的个数有 3 种，那么只需一个字符的数量 $\geq 2$ 即可。

3.字符串的数量大于 4 种，那么无论如何都能满足条件。

### 2.题目代码

```c++
#include<iostream>
#include<map> 
using namespace std;
map<char,int> mp; 
string s; 
int main(){
	cin>>s;
	int ls=s.size(),cnt=0;
	if(ls<4){
		puts("No");
		return 0;
	}
	for(int i=0;i<ls;i++){
		mp[s[i]]++;
		if(mp[s[i]]==1) cnt++; 
	}
	if(cnt<=1 || cnt>=5){
		puts("No");
		return 0;
	}
	if(cnt==2){
		bool flag=false;
		//先遍历小写 
		for(char i='a';i<='z';i++)
			if(mp[i]==1) flag=true;
		for(char i='A';i<='Z';i++)
			if(mp[i]==1) flag=true;
		if(flag){
			puts("No");
			return 0;
		}	
	}if(cnt==3){
		bool flag=false;
		for(char i='a';i<='z';i++)
			if(mp[i]>=2) flag=true;
		for(char i='A';i<='Z';i++)
			if(mp[i]>=2) flag=true;
		if(!flag){
			puts("No");
			return 0;
		}
	}
	puts("Yes"); 
	return 0;
}

```

---

## 作者：dddxrS (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF955B)

## 前言

qwq 第一篇题解耶

## 题意

给你一个字符串，问能否把字符串分成两份，使得每一份都可以分成由两组，这两组中的每一组都是一个字符的重复，且这两组重复字符不相同。可以输出 Yes，否则输出 No。

## 思路


### STL+判断

总之如果整个字符串只由一个字符构成或者字符串长度小于 4，必然不可以，输出 No；如果由 2 种字符构成，那么只要每种字符个数都大于等于 2 即可输出 Yes；由 3 种或者 4 种字符构成长度大于等于 4 的字符串必然是可以的；字符个数大于 4 必然是不行的，无法满足单个字符重复这个条件。综上只需要判断这 4 种情况就行了。

## 代码

```cpp
  #include<bits/stdc++.h>
  using namespace std;
  map<char,int>m;//用 map 记录每种字符出现的次数
  string s;
  int len,ans;
  int main(){
      while(cin>>s){
          len=s.size();
          ans=0;
          m.clear();
          for(int i=0;i<len;i++){
              if(m[s[i]]==0){
                  ans++;
              }
              m[s[i]]++;
          }
          if(len<=3||ans==1){//长度小于4或只有一种字符
              cout<<"No"<<endl;
          }
          else if(ans==2){
              bool flag=false;
              for(int i=0;i<len;i++){
                  if(m[s[i]]<2){//每种字符必须有两种才能满足要求
                      flag=true;
                      break;
                  }
              }
              if(flag==false){
                  cout<<"Yes"<<endl;	
              }
              else{
                  cout<<"No"<<endl;
              }
          }
          else if(ans>4){//种类大于4种
              cout<<"No"<<endl;
          }
          else{
              cout<<"Yes"<<endl;
          }
      }
      return 0;
  }
```


---

## 作者：myEnd (赞：0)

这道题好坑啊，竟然不是 beautiful 而是 beatiful！不愧是 CF。
#### 题目描述：

给你一个字符串 $s$，问能否把 $s$ 分成 $2$ 个子串，使得每个子串都**有且只有**两种字母。对于可以的，我们称之为“可爱的字符串”。

----

#### 解题思路：

按照题目描述，易得 $s$ 中的字母数不得小于 $2$ 或大于 $4$，所以可以只对 $2, 3, 4$ 这三种情况分类讨论，其他情况都不是“可爱的字符串”。

1. $2$ 种不同的字母：两种字母都应当个数大于 $2$ 个，否则无法令两个子串都有且只有两个不同的字母。
2. $3$ 种不同的字母：其中一种字母的个数应当大于 $2$ 个。原理同上。
3. $4$ 种不同的字母：无要求。把其中两个分给一个子串。另两个分给另外一个子串即可。

根据上述三种情况易想到本道题可以使用“桶”来解决。

#### 参考代码：



```cpp
#include <iostream>
#include <string>

using namespace std;

inline void quick_cppio(void)
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
}

int bucket[28];//全局变量默认全部初始为 0
string s;

int cnt = 0;//统计种数

inline int get_key(char c)
{
    if(c >= 'A' && c <= 'Z')
    {
        c -= 'A' - 'a';
    }
    return c - 'a';
}

int main()
{
    quick_cppio();
    cin >> s;
    for(int i = 0; i < s.size(); ++i)
    {
        bucket[get_key(s[i])]++;
    }
    for(int i = 0; i < 27; ++i)
    {
        if(bucket[i])
        {
            ++ cnt;
        }
    }
    if(cnt < 2 || cnt > 4)
    {
        cout << "No" << endl;
        return 0;//判断出结果, 结束程序
    }
    else
    {
        switch (cnt)
        {
        case 2:
        {
            int cnt1, cnt2;
            bool find = true;
            for(int i = 0; i < 27; ++i)
            {
                if(bucket[i] && find)
                {
                    cnt1 = bucket[i];
                    find = false;
                }
                else if(bucket[i] && (!find))
                {
                    cnt2 = bucket[i];
                }
            }
            if(cnt1 >= 2 && cnt2 >= 2)
            {
                cout << "Yes" << endl;
                return 0;//判断出结果, 结束程序
            }
            else
            {
                cout << "No" << endl;
                return 0;//判断出结果, 结束程序
            }
            break;
        }
        case 3:
        {
            bool can = false;
            for(int i = 0; i < 27; ++i)
            {
                if(bucket[i] >= 2)
                {
                    can = true;
                }
            }
            if(can)
            {
                cout << "Yes" << endl;
                return 0;//判断出结果, 结束程序
            }
            else
            {
                cout << "No" << endl;
                return 0;//判断出结果, 结束程序
            }
        }
        case 4:
            cout << "Yes" << endl;//判断出结果, 结束程序
            return 0;
        default://没有其余情况了, 前面 if 讨论过
            break;
        }
    }
    return 0;
}
```



---

