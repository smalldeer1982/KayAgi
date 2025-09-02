# NY10A - Penney Game

## 题目描述

Penney’s game is a simple game typically played by two players. One version of the game calls for each player to choose a unique three-coin sequence such as **HEADS TAILS HEADS (HTH)**. A fair coin is tossed sequentially some number of times until one of the two sequences appears. The player who chose the first sequence to appear wins the game.

For this problem, you will write a program that implements a variation on the Penney Game. You willread a sequence of 40 coin tosses and determine how many times each three-coin sequence appears. Obviously there are eight such three-coin sequences: **TTT**, **TTH**, **THT**, **THH**, **HTT**, **HTH**, **HHT** and **HHH**. Sequences may overlap. For example, if all 40 coin tosses are heads, then the sequence HHH appears 38 times.

## 样例 #1

### 输入

```
\n4\n1\nHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH\n2\nTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT\n3\nHHTTTHHTTTHTHHTHHTTHTTTHHHTHTTHTTHTTTHTH\n4\nHTHTHHHTHHHTHTHHHHTTTHTTTTTHHTTTTHTHHHHT\n\n```

### 输出

```
\n1 0 0 0 0 0 0 0 38\n2 38 0 0 0 0 0 0 0\n3 4 7 6 4 7 4 5 1\n4 6 3 4 5 3 6 5 6```

# 题解

## 作者：A350_ti (赞：5)

### 1.题面
给定小于一个长度小于 $40$ 、只含"H" "T"的字符串，求其中含有的 TTT,TTH,THT,THH,HTT,HTH,HHT,HHH 的数量。

### 2.solution
使用 $ans$ 数组记录答案，我们可以枚举每个位置从当前位置开始的子串，在 $ans$ 数组中对应位置累加。时间复杂度 $O(n\times p)$。

### 3.一些坑
- 需要按照题目所给顺序输出子串数目。
- 在输出每组答案之前要先输出这是第几组。
- ans 数组记得清零。
```cpp
#include<bits/stdc++.h>
using namespace std;
int P,n;
string ch;
string mode[9]={"","TTT","TTH","THT","THH","HTT","HTH","HHT","HHH"}; 
int ans[10],len;
string c;
int main(){
	scanf("%d",&P);
	while(P--){
		memset(ans,0,sizeof(ans));
		scanf("%d",&n);
		cin>>ch;
		len=ch.length();
		for(int i=0;i<len-2;i++){
			c="";
			c+=ch[i];
			c+=ch[i+1];
			c+=ch[i+2];
			for(int j=1;j<=8;j++){
				if(c==mode[j]) ans[j]++; 
			}
		}
		printf("%d ",n);
		for(int i=1;i<=8;i++)
			printf("%d ",ans[i]);
		putchar('\n');
	}
	return 0;
}
```


---

## 作者：hj23308 (赞：4)

[题目传送门](/problem/SP8612)  
### 1.题意 
给定一个 $n$ 个长度为 $\text{40}$ 的字符串，里面只有 $\text{H}$ 和 $\text{T}$。  
你要求出所有长度为 $\text{3}$ 的子串中，三个字符为 $\text{TTT,TTH,THT,THH,HTT,HTH,HHT}$ 和 $\text{HHH}$ 的数量。
### 2. 分析
枚举所有长度为 $\text{3}$ 的字串，用 $ans$ 数组纪录答案。  
时间复杂度 $\text{O}(n \cdot p)$。
### 3. 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
	std::ios::sync_with_stdio(false);
	cin.tie(0);

	string str1, str2[8] = {"TTT", "TTH", "THT", "THH", "HTT", "HTH", "HHT", "HHH"};
	int t, n, ans[8];
	cin >> t;
	while (t--) {
		cin >> n >> str1;
		memset(ans, 0, sizeof ans);
		for (int i = 0; i < (int)str1.length() - 2; i++) {
			string t = str1.substr(i, 3);
			for (int j = 0; j < 8; j++)
				ans[j] += t == str2[j] ? 1 : 0;
		}
		cout << n << ' ';
		for (int i = 0; i < 8; i++)
			cout << ans[i] << ' ';
		cout << '\n';
	}

	return 0;
}
```

---

## 作者：ttq012 (赞：2)

**Solution**

简单题。

可以使用一个 `map` 来记录一下都有哪一些字符串出现过，然后枚举的时候将当前字符和当前字符后头的两个字符放到一个字符串中，在 `map` 查找即可。

注意是多组数据。

**AC Code**

```cpp
#include <bits/stdc++.h>

using namespace std;

map <string, int> mp = {
    {"TTT", 0}, 
    {"TTH", 1}, 
    {"THT", 2}, 
    {"THH", 3}, 
    {"HTT", 4}, 
    {"HTH", 5}, 
    {"HHT", 6}, 
    {"HHH", 7}, 
};

set <string> vs = {"TTT", "THT", "TTH", "HTT", "THH", "HHT", "HHH", "HTH"};

int sq(string k) {
    if (vs.count(k))
        return mp[k];
    else
        return 8;
}

void solve() {
    int id;
    cin >> id;
    int cnt[10] = {0};
    string s;
    cin >> s;
    int n = s.size();
    for (int i = 0; i < n - 2; i ++) {
        int j = i + 1, k = i + 2;
        string u;
        u += s[i];
        u += s[j];
        u += s[k];
        cnt[sq(u)] ++;
    }
    cout << id << ' ';
    for (int i = 0; i < 8; i ++)
        cout << cnt[i] << ' '; cout << '\n';
}

signed main() {
    int T;
    cin >> T;
    while (T --)
    solve();
    return 0;
}

```


---

## 作者：Anonymous__user (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/SP8612)。

**本题的大意**是输入一个长度为 40 的字符串，求该字符串中 TTT, TTH , THT , THH , HTT , HTH , HHT 和 HHH 的数目。

**注意事项**

1. 输入 t  组数据，每组一个字符串。
 
2. 输出时，每组答案前输出数据编号。

**分析**

1. 这是一道大水题， 2 个循环， 8 个判断，枚举情况即可。

2. 答案记得清零。

**代码**
```c
#include<bits/stdc++.h>
using namespace std;
long long t,n[10010],ans1,ans2,ans3,ans4,ans5,ans6,ans7,ans8;
string s;
int main(){
	cin>>t;
	for(int i=1;i<=t;i++){
		cin>>s;
		 n[i]=s.size();
		 for(int j=0;j<n[i];j++){
		 	if(s[j]=='T'&&s[j+1]=='T'&&s[j+2]=='T')
		 	    ans1++; 
			if(s[j]=='T'&&s[j+1]=='T'&&s[j+2]=='H')
		 	    ans2++;
		 	if(s[j]=='T'&&s[j+1]=='H'&&s[j+2]=='T')
		       ans3++;
			if(s[j]=='T'&&s[j+1]=='H'&&s[j+2]=='H')
		 	    ans4++;
			if(s[j]=='H'&&s[j+1]=='T'&&s[j+2]=='T')
		 	    ans5++;	 
			if(s[j]=='H'&&s[j+1]=='T'&&s[j+2]=='H')
		 	    ans6++;	 	 	
		 	if(s[j]=='H'&&s[j+1]=='H'&&s[j+2]=='T')
		 	    ans7++;
		 	if(s[j]=='H'&&s[j+1]=='H'&&s[j+2]=='H')
		 	    ans8++;	
		 }
		 cout<<t<<" "<<ans1<<" "<<ans2<<" "<<ans3<<" "<<ans4<<" "<<ans5<<" "<<ans6<<" "<<ans7<<" "<<ans8<<endl;
		 ans1=0;ans2=0;ans3=0;ans4=0;ans5=0;ans6=0;ans7=0;ans8=0;
	}
	return 0;
}
```


---

## 作者：jxbe6666 (赞：0)

看见大佬们都用的 $\text{if}$，其实先用数组记录下来会更快。
### 题意
给定小于一个长度小于 $40$ 、只含 $\text{H,T}$ 的字符串，求其中含有的 $\text{TTT,TTH,THT,THH,HTT,HTH,HHT,HHH}$ 的数量。

-----

### 思路
枚举所有长度为 $3$ 的字串，用 ans 数组纪录答案。

-----

### 代码

-----

```c++
#include <bits/stdc++.h>
#define I return
#define AK 0
#define IOI ;
#define ll long long
using namespace std;
const ll N = 1e6 + 5;
const ll M = 1e3 + 5;
ll a[N], b[N], c[N], n, m, x, y, z, k, l, r, t, cnt, s, ans, v[N], w[N], dp[N], V, W;
ll f[N], father[N];
string s1, s2;
stack<int> _s;
queue<int> _q;
map<int, int> _m;
ll quickpower(ll x, ll y, ll mod)
{ // 快速幂
    if (y)
    {
        ll div = quickpower(x, y >> 1, mod);
        if (y & 1)
            return (div * div) % mod * x % mod;
        else
            return div * div % mod;
    }
    return 1;
}
inline ll read()
{ // 快读
    ll x = 0, y = 1;
    char c = getchar();
    while (!isdigit(c))
    {
        y = (c == '-') ? -1 : 1;
        c = getchar();
    }
    while (isdigit(c))
    {
        x = (x << 1) + (x << 3) + c - '0';
        c = getchar();
    }
    return x * y;
}
inline void out(ll x)
{
    if (x < 0)
    {
        x = ~(x - 1);
        putchar('-');
    }
    if (x > 9)
        out(x / 10);
    putchar(x % 10 + '0');
}
inline void write(ll x, char ch)
{ // 快输
    out(x);
    putchar(ch);
}
int find(ll x)
{
    return (father[x] == x) ? x : father[x] = find(father[x]);
}
int main()
{
    string str1, str2[10] = {"TTT", "TTH", "THT", "THH", "HTT", "HTH", "HHT", "HHH"};
    int t, n, ans[10];
    cin >> t;
    while (t--)
    {
        cin >> n >> str1;
        memset(ans, 0, sizeof(ans));
        for (int i = 0; i < 38; i++)// 40-2=38
        {
            string t = str1.substr(i, 3);
            for (int j = 0; j < 8; j++)
                ans[j] += (t == str2[j]);
        }
        cout << n << ' ';
        for (int i = 0; i < 8; i++)
            cout << ans[i] << ' ';
        cout << '\n';
    }

    I AK IOI
}
```


---

## 作者：ShanCreeperPro (赞：0)

## SP8612 NY10A - Penney Game 題解

直接暴力判断字符串中的字串。

- 判断字串 $\texttt{TTT}$，如果 $s_i=s_{i+1}=s_{i+2}=T$，答案加 $1$：

```cpp
inline int findttt(string s){
	ans=0;
	fore(i,0,39){
		if(s[i]=='T'&&s[i+1]=='T'&&s[i+2]=='T') ans++;
	}
	return ans;
}
```

- $\texttt{TTH, THT, THH, HTT, HTH, HHT, HHH}$ 方法相同：

```cpp
inline int findtth(string s){
	ans=0;
	fore(i,0,39){
		if(s[i]=='T'&&s[i+1]=='T'&&s[i+2]=='H') ans++;
	}
	return ans;
}
inline int findtht(string s){
	ans=0;
	fore(i,0,39){
		if(s[i]=='T'&&s[i+1]=='H'&&s[i+2]=='T') ans++;
	}
	return ans;
}
inline int findthh(string s){
	ans=0;
	fore(i,0,39){
		if(s[i]=='T'&&s[i+1]=='H'&&s[i+2]=='H') ans++;
	}
	return ans;
}
inline int findhtt(string s){
	ans=0;
	fore(i,0,39){
		if(s[i]=='H'&&s[i+1]=='T'&&s[i+2]=='T') ans++;
	}
	return ans;
}
inline int findhth(string s){
	ans=0;
	fore(i,0,39){
		if(s[i]=='H'&&s[i+1]=='T'&&s[i+2]=='H') ans++;
	}
	return ans;
}
inline int findhht(string s){
	ans=0;
	fore(i,0,39){
		if(s[i]=='H'&&s[i+1]=='H'&&s[i+2]=='T') ans++;
	}
	return ans;
}
inline int findhht(string s){
	ans=0;
	fore(i,0,39){
		if(s[i]=='H'&&s[i+1]=='H'&&s[i+2]=='H') ans++;
	}
	return ans;
}
```

记得将 $\texttt{ans}$ 归零。

- 最后读入 $t$ 组数据，读入一组就把所有函数调用一次并输出，不要忘了换行：

```cpp
writesp(findttt(s));
writesp(findtth(s));
writesp(findtht(s));
writesp(findthh(s));
writesp(findhtt(s));
writesp(findhth(s));
writesp(findhht(s));
writesp(finghhh(s));
puts("");
```



---

## 作者：708151_qwq (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/SP8612)

# 题意简述

输入一个长度为 $40$ 的字符串。

输出该字符串中 ```TTT```, ```TTH```, ```THT```, ```THH```, ```HTT```, ```HTH```, ```HHT``` 和 ```HHH``` 的数目 ，中间以空格隔开。

输入 $t$ 组数据，每组一个字符串。

输出时，每组答案前输出数据编号。

# Solution

用  ```TTT```, ```TTH```, ```THT```, ```THH```, ```HTT```, ```HTH```, ```HHT``` 和 ```HHH``` 八个字符串作为它们对应的计数器的变量名，遍历输入的字符串，找到一个就对应的计数器加一，eg:

```cppif(s[i]=='T'&&s[i+1]=='T'&&s[i+2]=='T') TTT++;//s数组为输入的 string 类型字符串，TTT 为计数器```
最后输出所有计数器。

# 一些小坑：
输出之前要写输出的是第几组；

输出完一组后要清空所有计数器；

输出要按题目给的顺序。

# AC _Code_
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int t,n,TTT=0,TTH=0,THT=0,THH=0,HTT=0,HTH=0,HHT=0,HHH=0;
    string s;
    cin>>t;
    for(int j=1;j<=t;j++){
        cin>>n;
        cin>>s;
        for(int i=0;i<=37;i++)//枚举子串
        if(a[i]=='T'&&a[i+1]=='T'&&a[i+2]=='T')
        TTT++;
        else if(a[i]=='T'&&a[i+1]=='T'&&a[i+2]=='H')
        TTH++;
        else if(a[i]=='T'&&a[i+1]=='H'&&a[i+2]=='T')
        THT++;
        else if(a[i]=='T'&&a[i+1]=='H'&&a[i+2]=='H')
        THH++;
        else if(a[i]=='H'&&a[i+1]=='T'&&a[i+2]=='T')
        HTT++;
        else if(a[i]=='H'&&a[i+1]=='T'&&a[i+2]=='H')
        HTH++;
        else if(a[i]=='H'&&a[i+1]=='H'&&a[i+2]=='T')
        HHT++;
        else if(a[i]=='H'&&a[i+1]=='H'&&a[i+2]=='H')
        HHH++;
        printf("%d ",j);
        printf("%d %d %d %d %d %d %d %d\n",TTT,TTH,THT,THH,HTT,HTH,HHT,HHH);
        TTT=0,TTH=0,THT=0,THH=0,HTT=0,HTH=0,HHT=0,HHH=0;
    }
    return 0;
}
```

by 2022.4.29 蒟蒻的第一篇题解

---

## 作者：77777_1031 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/SP8612)

[更好的阅读体验](https://tsygoon.blog.luogu.org/solution-sp8612)

### 题意

给出一个字符串，判断其中子串的出现次数。

### 题目分析

暴力枚举每一个长度为 $3$ 的子串，判断是否等于 $8$ 个子串其中一个，等于哪个哪个就 $+1$。

注意有多组数据，最后还要输出数据的编号。

### 我丑陋的代码

```
#include<bits/stdc++.h>
using namespace std;
int n;
int a[40];//存储01串
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        int cnt;//编号
        string s;
        int ttt=0,tth=0,tht=0,thh=0,htt=0,hth=0,hht=0,hhh=0;//存储出现的每个字串的个数
        cin>>cnt>>s;
        memset(a,0,sizeof(a));//注意每次要清零，要不然会出现错误。
        //将字符串转成01串。（可能有点多此一举了）个人比较喜欢这么做。
        if(s[0]-'A'==19)a[0]=1;
        if(s[1]-'A'==19)a[1]=1;
        for(int i=2;i<40;i++){//枚举每个字串
            if(s[i]-'A'==19)a[i]=1;
            //判断
            if(a[i-2]==1&&a[i-1]==1&&a[i]==1)ttt++;
            if(a[i-2]==1&&a[i-1]==1&&a[i]==0)tth++;
            if(a[i-2]==1&&a[i-1]==0&&a[i]==1)tht++;
            if(a[i-2]==1&&a[i-1]==0&&a[i]==0)thh++;
            if(a[i-2]==0&&a[i-1]==1&&a[i]==1)htt++;
            if(a[i-2]==0&&a[i-1]==1&&a[i]==0)hth++;
            if(a[i-2]==0&&a[i-1]==0&&a[i]==1)hht++;
            if(a[i-2]==0&&a[i-1]==0&&a[i]==0)hhh++;
        }
        cout<<cnt<<" "<<ttt<<" "<<tth<<" "<<tht<<" "<<thh<<" "<<htt<<" "<<hth<<" "<<hht<<" "<<hhh<<endl;
    }
    return 0;
}
```
by 2022.03.26 我的第七篇题解。


---

## 作者：tgs9311 (赞：0)

题意：
给出长度为40的只含T和H的序列，求其中TTT, TTH, THT, THH, HTT, HTH, HHT ,HHH出现的次数

解析：
遍历并暴力统计即可，可以使用stl中的map（其实直接用数组也可以），注意有多组数据

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
namespace FAST_IO
{
	template<typename T> void read(T &a)
	{
		a=0;
		int f=1;
		char c=getchar();
		while(!isdigit(c))
		{
			if(c=='-')
			{
				f=-1;
			}
			c=getchar();
		}
		while(isdigit(c))
		{
			a=a*10+c-'0';
			c=getchar();
		}
		a=a*f;
	}
	template <typename T> void write(T a)
	{
		if(a<0)
		{
			a=-a;
			putchar('-');
		}
		if(a>9)
		{
			write(a/10);
		}
		putchar(a%10+'0');
	}
	template <typename T> void writeln(T a)
	{
		write(a);
		puts("");
	}
}
int n,cnt;
string a,db[9]={"","TTT","TTH","THT", "THH", "HTT", "HTH", "HHT","HHH"};
int main()
{
	cin>>n;
	while(n--)
	{
		int tmp;
		map<string,int> q;
		cin>>tmp>>a;
		for(int i=0;i<38;i++)
		{
			string tmp="";
			tmp+=a[i];
			tmp+=a[i+1];
			tmp+=a[i+2];
			q[tmp]++;
		}
		cout<<tmp<<" "; 
		for(int i=1;i<=8;i++)
		{
			cout<<q[db[i]]<<" ";
		}
		cout<<endl;
	}
}

```


---

