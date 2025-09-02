# Palindromic Twist

## 题目描述

You are given a string $ s $ consisting of $ n $ lowercase Latin letters. $ n $ is even.

For each position $ i $ ( $ 1 \le i \le n $ ) in string $ s $ you are required to change the letter on this position either to the previous letter in alphabetic order or to the next one (letters 'a' and 'z' have only one of these options). Letter in every position must be changed exactly once.

For example, letter 'p' should be changed either to 'o' or to 'q', letter 'a' should be changed to 'b' and letter 'z' should be changed to 'y'.

That way string "codeforces", for example, can be changed to "dpedepqbft" ('c' $ \rightarrow $ 'd', 'o' $ \rightarrow $ 'p', 'd' $ \rightarrow $ 'e', 'e' $ \rightarrow $ 'd', 'f' $ \rightarrow $ 'e', 'o' $ \rightarrow $ 'p', 'r' $ \rightarrow $ 'q', 'c' $ \rightarrow $ 'b', 'e' $ \rightarrow $ 'f', 's' $ \rightarrow $ 't').

String $ s $ is called a palindrome if it reads the same from left to right and from right to left. For example, strings "abba" and "zz" are palindromes and strings "abca" and "zy" are not.

Your goal is to check if it's possible to make string $ s $ a palindrome by applying the aforementioned changes to every position. Print "YES" if string $ s $ can be transformed to a palindrome and "NO" otherwise.

Each testcase contains several strings, for each of them you are required to solve the problem separately.

## 说明/提示

The first string of the example can be changed to "bcbbcb", two leftmost letters and two rightmost letters got changed to the next letters, two middle letters got changed to the previous letters.

The second string can be changed to "be", "bg", "de", "dg", but none of these resulting strings are palindromes.

The third string can be changed to "beeb" which is a palindrome.

The fifth string can be changed to "lk", "lm", "nk", "nm", but none of these resulting strings are palindromes. Also note that no letter can remain the same, so you can't obtain strings "ll" or "mm".

## 样例 #1

### 输入

```
5
6
abccba
2
cf
4
adfa
8
abaazaba
2
ml
```

### 输出

```
YES
NO
YES
NO
NO
```

# 题解

## 作者：01Dragon (赞：1)

### 思路
题目说**给定一个字符串，判断其能否变成回文串**。要变成一个回文串，就要让字符串的每一个字符都与它的对应字符相同。字符 $a$ 和对应字符 $b$ 的关系分为 $4$ 种：
1. $a=b$。这时可以让 $a$ 和 $b$ 同时向前移动一格。
2. $a$ 和 $b$ 相差一格。这时 $a$ 和 $b$ 无法变相同。
3. $a$ 和 $b$ 相差两格。这时可以让 $a$ 和 $b$ 向相反方向移动。
4. $a$ 和 $b$ 的差距大于两格。这时 $a$ 和 $b$ 无法变相同。

所以只需要判断字符串前半段的每个字符即可。
### 代码
```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <string>
#include <cstdio>
#include <cmath>
using namespace std;
int t,n;
string s; 
int main()
{
	cin>>t;
	for(int i=0;i<t;i++)
	{
		cin>>n>>s;
		bool flag=true;
		for(int i=0;i<n/2;i++)
		{
			if(abs(s[i]-s[n-i-1])>2||abs(s[i]-s[n-i-1])==1)
			{
				flag=false;
				break;
			}
		}
		if(flag==false)
		{
			cout<<"NO"<<endl;
		}
		else
		{
			cout<<"YES"<<endl;
		}
	}
	return 0;
}
```


---

## 作者：Hughpig (赞：1)

为了叙述方便，这里定义 $S_i$ 为字符串 $S$ 中第 $i$ 个字符（由于实际代码中字符串下标从 $0$ 开始，所以需要把 $i$ 减 $1$），定义 $ch-1$ 为小写字母 $ch$ 的上一个字符，$ch+1$ 为小写字母 $ch$ 的下一个字符。

题目中说，要把 $S$ 变为一个回文串。即对于任何 $i$，都满足 $S_i=S_{n-i}$。

因此需要通过操作，把 $S_i$ 改为 $S_{n-i}$ 。如果不能做到，就要输出 `NO`。

我们对 $S_i$ 和 $S_{n-i}$ 的情况进行分类讨论。

1. $S_i=S_{n-i}$ 

因为这两者相等，根据等式的性质， $S_i+1=S_{n-i}+1$。所以可以通过操作把它们变得相等。

2. $S_i+1=S_{n-i}-1$

我们可以把 $S_i$ 减去 $1$，$S_{n-i}$ 加上 $1$。此时两者相等。

3. $S_i-1=S_{n-i}+1$

与第 $2$ 种情况同理。

4. 其他情况

因为对于每个字符都要进行一次操作，所以只有以上 $3$ 种情况可以满足，其他情况一律不行。

代码：

```cpp
#include<bits/stdc++.h>//头文件
using namespace std;

int t,n;//变量，意义如题意
string s;

int main()
{
    cin>>t;
    while(t--)//多组数据
    {
    	cin>>n>>s;
    	bool f=1;//定义一个是否可以达成条件的变量
    	for(int i=0;i<n;i++)
    	{
    		if(s[i]==s[n-i-1]||s[i]+1==s[n-i-1]-1||s[i]-1==s[n-i-1]+1)continue;//如果可以，继续
    		else f=0;//如果不行，把 f 设为 0
		}
		cout<<(f?"YES\n":"NO\n");//输出，记得换行
	}
	return 0;
}
```

---

## 作者：zhouzihe (赞：1)

## 1 观察题目
观察题目，不难发现这道题想要我们判断一个字符串能否通过他给定的操作变成一个回文字符串。  

## 2 如何求解
我们设 $s$ 为给定字符串，$n$ 为字符串的长度，此处注意 $s$ 的下标是从 $0$ 开始的。  

+ 当 $|s_i-s_{n-i-1}|=0$ 时，代表 $s_i=s_{n-i-1}$，可以使 $s_i$ 和 $s_{n-i-1}$ 一起变为下一个字母或者上一个字母。  

+ 当 $|s_i-s_{n-i-1}|=1$ 时，代表 $s_i$ 和 $s_{n-i-1}$ 差一个字母，因为**每个位置都应该恰好被执行一次该操作**，所以无解。  

+ 当 $|s_i-s_{n-i-1}|=2$ 时，代表 $s_i$ 和 $s_{n-i-1}$ 差两个字母，可以使 $s_i$ 和 $s_{n-i-1}$ 一个变为上一个字母，一个变为下一个字母。  

+ 当 $|s_i-s_{n-i-1}|>2$ 时，因为每个位置都应该**恰好**被执行一次该操作，所以无解。
## 3 code
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
string s;
bool f; 
int main(){
	cin>>t;
	while(t--){
		cin>>n>>s;
		f=true;
		for(int i=0;i<n;i++){
			if(abs(s[i]-s[n-i-1])>2||abs(s[i]-s[n-i-1])==1){
				cout<<"NO"<<endl;
				f=false;
				break;
			}
		}
		if(f){
			cout<<"YES"<<endl;
		}
	}
	return 0;
}
```


---

## 作者：Zq_water (赞：0)


对于每一个字符串，我们可以把每一个字符上与它相反的位置上进行讨论。

如果该字符与其相反的位置上的差等于 $0$，那么我们可以把他们同时往前或往后移一步，就可以满足回文串。若差为 $2$，那么我们可以一个往前移，一个往后移，也可以满足回文串。其余的方案，一律不可以。

```cpp
#include <bits/stdc++.h>
using namespace std;

int t,n;
string s; 

int main(){
	cin>>t;
	while(t--){
		cin>>n>>s;
		bool flag=1;
		for(int i=0;i<n/2;i++)
			if(abs(s[i]-s[n-i-1])>2||abs(s[i]-s[n-i-1])==1){
				flag=0;
				break;
			}
		if(!flag) cout<<"NO"<<endl;
		else cout<<"YES"<<endl;
	}
	return 0;
}
```

---

## 作者：hn_shw (赞：0)

简化题意：给你一个字符串 $s$，$s_i$ 可以变成 $s_i+1$ 或 $s_i-1$，请问字符串改变后是否为回文串？

显然我们先枚举字符串，那么回文串要满足的条件就是 $s_i=s_{n-i}$，此时又有四种情况：

1. $s_{i}$ 选其后面一个，$s_{n-i}$ 选其前面一个。
1. $s_{i}$ 选其前面一个，$s_{n-i}$ 选其后面一个。
1. $s_{i}$ 选其后面一个，$s_{n-i}$ 选其后面一个。
1. $s_{i}$ 选其前面一个，$s_{n-i}$ 选其前面一个。

以上 $3$,$4$ 点只要 $s_i=s_{n-i}$ 就都成立。

### 代码：
```
#include<bits/stdc++.h>
using namespace std;
void slove(){
	int n;
	cin>>n;
	string s;
	cin>>s;
	bool f=true;
	for(int i=0;i<n;i++){
		if(1+s[i]==s[n-1-i]-1||s[i]-1==1+s[n-1-i]||s[i]==s[n-1-i]) continue;       //四种情况判回文串
		else f=false;
	}
	if(f) puts("YES");
	else puts("NO");
}
int main(){
	int t;
	cin>>t;
	while(t--) slove();
	return 0;
}
```

---

## 作者：Neilchenyinuo (赞：0)

## 题目大意

给定一个字符串，判断其能否变成回文串。

## Solution

1. 当 $a=b$ 时，可以让 $a$ 和 $b$ 同时移动一格。

2. $a$ 和 $b$ 相差一格时，这时 $a$ 和 $b$ 没法相同。

3. 当 $a$ 和 $b$ 相差两格时，这时 $a$ 和 $b$ 可以反方向移动。

4. 当 $a$ 和 $b$ 差的超过两格时，也是无法相同的。

- 综上所述，我们只需判断前半段的字符差距即可。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
string s; 
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>n>>s;
		bool flag=0;
		for(int i=0;i<n/2;i++)
		{
			if(abs(s[i]-s[n-i-1])>2||abs(s[i]-s[n-i-1])==1)
			{
				flag=1;
				break;
			}
		}
		if(flag==1)
			cout<<"NO\n";
		else
			cout<<"YES\n";
	}
	return 0;
}
```


---

## 作者：_lgh_ (赞：0)

# 思路：
题目就是让你判断给出的字符串每个字母改变时能否变成回文串。直接进行模拟，直接特判 A 、Z 的情况，其余的情况直接判断对应位是否相差两位即可。
# AC CODE：
```cpp
#include<bits/stdc++.h>
#define NO {flag=0;break;}//我爱压行
using namespace std;
int main()
{
  int T;
  cin>>T;
  while(T--)
  {
    int n;
    string str;
    cin>>n>>str;
    bool flag=1;
    for(int i=0,j=n-1; i<n/2; i++,j--)
    {
      if(str[i]=='a')
        if(str[j]!='a'&&str[j]!='b'&&str[j]!='c')NO
      if(str[i]=='z')
        if(str[j]!='z'&&str[j]!='y'&&str[j]!='x') NO
      int temp=abs(str[i]-str[j]);
      if(temp>2||temp==1) NO
    }
    if(flag) puts("YES");
    else puts("NO");
  }

  return 0;
}
```


---

## 作者：sycqwq (赞：0)

__思路：__

我们可以考虑对于一个字符串 $S$，是一个回文串的条件是什么？

显然为 $s_i=s_{n-i+1}$。

这个时候，我们就可以考虑，对于一个 $i$，能否满足这个条件。

设 $a_i$ 为 $s_i$ 在字母表中的位置。

每一次操作就转化为使 $a_i$ 加一或者减一

显然有以下几种情况

$1°$ $|a_i-a_{n-i+1}|>2$

此时，显然答案为 `NO`。

$2°$ $|a_i-a_{n-i+1}|=2$

我们不妨设 $a_i<a_{n-i+1}$。

此时可以让 $a_i$ 加一并且让 $a_{n-i+1}$ 减一。

此时就可以满足条件。

$3°$ $a_i-a_{n-i+1}=1$

我们不妨设 $a_i<a_{n-i+1}$。

因为必须让每一个字母进行一次修改，所以此时无论怎么操作，都无法满足条件。

答案为 `NO`

$4°$ $a_i=a_{n-i+1}$

此时只要让 $a_i$ 和 $a_{n-i+1}$ 加一或者减一，就可以满足条件。

所以对于每一个 $i$，都满足 $2$ 和 $4$ 两个条件，答案就为 `YES` ，否则为 `NO`。

__代码__

```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
char a[100005];
int main()
{
    cin>>t;
    for(int i=1;i<=t;i++)
    {
        int n;
        cin>>n>>a+1;
        int k=0;
        for(int j=1;j<=n;j++)
        {
            if(abs(a[n-j+1]-a[j])!=0&&abs(a[n-j+1]-a[j])!=2)
            {
                puts("NO");
                k=1;
                break;
            }
        }    
        if(!k)
            puts("YES");
    }
    return 0;
}
```

---

## 作者：米奇奇米 (赞：0)

```cpp
#include<bits/stdc++.h>//万能头
#define ll long long
using namespace std;
ll n,m,ans,a[1000];
ll sum,T;
string s;
bool result;
int read()//快读，进行读入优化
{ 
  int v=0,f=1;
  char c=getchar();
  while(c<48||57<c) {if(c=='-') f=-1; c=getchar();}
  while(48<=c&&c<=57) v=(v<<3)+v+v+c-48,c=getchar();
  return v*f;
}
bool ac(string s,int n)//神奇的方法判断是否是回文字符串
{
  char* pre = &s[0];
  char* end = &s[n-1];
  while(pre < end)
  {
     if(abs((*pre)-(*end))==0 || abs((*pre)-(*end))==2)         
	 {
       pre ++;
       end --;//逐位进行判断
     }
      else
     {
       return false;
     }    
}
    return true;
}
 
 int main()
 {
     while(cin >> T)
     {
         while(T --)//一边输入，就开始判断
         {
             cin >> n;
             cin >> s;
              result = ac(s,n);
             if(result)
                 cout << "YES" << endl;
            else
                cout << "NO" << endl;         }//按照题意输出即可
     }
     return 0;
 }

```

---

## 作者：RoniZeng (赞：0)

这道题主要是考我们的组合/分类讨论的能力。
将首部和对应尾部分别改变看是否能够匹配，有如下四种情况：
1.首部+1 & 尾部+1
2.首部+1 & 尾部-1
3.首部-1 & 尾部+1
4.首部-1 & 尾部-1

然后正难则反，若以上四种情况若都不成立，那么一定输出NO。否则输出YES。

```cpp
#include<cstdio>
#include<string>
#include<cstdlib>
#include<cmath>
#include<iostream>
#include<cstring>
#include<set>
#include<queue>
#include<algorithm>
#include<vector>
#include<map>
#include<cctype>
#include<stack>
#include<sstream>
#include<list>
#include<assert.h>
#include<bitset>
#include<numeric>
#define debug() puts("++++")
#define gcd(a,b) __gcd(a,b)
#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1
#define fi first
#define se second
#define pb push_back
#define sqr(x) ((x)*(x))
#define ms(a,b) memset(a,b,sizeof(a))
#define sz size()
#define be begin()
#define pu push_up
#define pd push_down
#define cl clear()
#define lowbit(x) -x&x
#define all 1,n,1
#define mod(x) ((x)%M)
#define pi acos(-1.0)
#define rep(i,x,n) for(int i=(x); i<(n); i++)
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef pair<int,int> P;
const int INF = 0x3f3f3f3f;
const int maxn = 1e6+10;
const double eps = 1e-8;
const int dx[] = {-1,1,0,0,1,1,-1,-1};
const int dy[] = {0,0,1,-1,1,-1,1,-1};
int dir[2]={-1,1};
const int mon[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
const int monn[] = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int t,n;
string s;
int f;
bool check()
{
    f=1;
    char pre_sub,pre_add,suf_add,suf_sub;
    for(int i=0;i<n;i++)
    {
         pre_sub=s[i]-1;
         pre_add=s[i]+1;
         suf_sub=s[n-i-1]-1;
         suf_add=s[n-i-1]+1;
        if(pre_add!=suf_add
        && pre_add!=suf_sub
        && pre_sub!=suf_add
        && pre_sub!=suf_sub) f=0;
    }
    if(f) puts("YES");
    else puts("NO");
}
int main()
{
    cin>>t;
    while(t--)
    {

        cin>>n;
        cin>>s;
        check();
    }
    return 0;
}
/*
【题意】

【类型】

【分析】

【时间复杂度&&优化】

【trick】

【数据】
*/

```


---

## 作者：ys_kylin__ (赞：0)

## 题意
多组数据，每次给出一个字符串，判断字母表中全部 $+1$ 或 $-1$ ，是否能成为回文串。

## 思路
不难发现，两个字符若要相同，需要在字母表中相差 $0$ 或 $2$，因为 $0$ 的情况可以向相同方向走一格，$2$ 的情况就以相反方向走一格，剩下的都不行。然后就是基础的回文串判断。

## code
```cpp
#include<bits/stdc++.h>
using namespace std;
char s[105];
int main() {
	int t;
	scanf("%d",&t);
	while(t--) {
		int n;
		scanf("%d%s",&n,s);
		for(int i=0;i<n/2;i++)
			if(abs(s[i]-s[n-i-1])!=2 && abs(s[i]-s[n-i-1])!=0) {//原本的回文判断改了一下
				printf("NO\n");
				goto brk;//奇奇怪怪的goto,可以直接跳至目标点位
			}
		printf("YES\n");
		brk:;//目标点位
	}
	return 0;
}
```

---

