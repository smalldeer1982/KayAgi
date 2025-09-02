# Smaller

## 题目描述

Alperen has two strings, $ s $ and $ t $ which are both initially equal to "a".

He will perform $ q $ operations of two types on the given strings:

- $ 1 \;\; k \;\; x $ — Append the string $ x $ exactly $ k $ times at the end of string $ s $ . In other words, $ s := s + \underbrace{x + \dots + x}_{k \text{ times}} $ .
- $ 2 \;\; k \;\; x $ — Append the string $ x $ exactly $ k $ times at the end of string $ t $ . In other words, $ t := t + \underbrace{x + \dots + x}_{k \text{ times}} $ .

After each operation, determine if it is possible to rearrange the characters of $ s $ and $ t $ such that $ s $ is lexicographically smaller $ ^{\dagger} $ than $ t $ .

Note that the strings change after performing each operation and don't go back to their initial states.

 $ ^{\dagger} $ Simply speaking, the lexicographical order is the order in which words are listed in a dictionary. A formal definition is as follows: string $ p $ is lexicographically smaller than string $ q $ if there exists a position $ i $ such that $ p_i < q_i $ , and for all $ j < i $ , $ p_j = q_j $ . If no such $ i $ exists, then $ p $ is lexicographically smaller than $ q $ if the length of $ p $ is less than the length of $ q $ . For example, $ \texttt{abdc} < \texttt{abe} $ and $ \texttt{abc} < \texttt{abcd} $ , where we write $ p < q $ if $ p $ is lexicographically smaller than $ q $ .

## 说明/提示

In the first test case, the strings are initially $ s =  $ "a" and $ t =  $ "a".

After the first operation the string $ t $ becomes "aaa". Since "a" is already lexicographically smaller than "aaa", the answer for this operation should be "YES".

After the second operation string $ s $ becomes "aaa", and since $ t $ is also equal to "aaa", we can't arrange $ s $ in any way such that it is lexicographically smaller than $ t $ , so the answer is "NO".

After the third operation string $ t $ becomes "aaaaaa" and $ s $ is already lexicographically smaller than it so the answer is "YES".

After the fourth operation $ s $ becomes "aaabb" and there is no way to make it lexicographically smaller than "aaaaaa" so the answer is "NO".

After the fifth operation the string $ t $ becomes "aaaaaaabcaabcaabca", and we can rearrange the strings to: "bbaaa" and "caaaaaabcaabcaabaa" so that $ s $ is lexicographically smaller than $ t $ , so we should answer "YES".

## 样例 #1

### 输入

```
3
5
2 1 aa
1 2 a
2 3 a
1 2 b
2 3 abca
2
1 5 mihai
2 2 buiucani
3
1 5 b
2 3 a
2 4 paiu```

### 输出

```
YES
NO
YES
NO
YES
NO
YES
NO
NO
YES```

# 题解

## 作者：_Aniya_ (赞：8)

### 题意
给你两个字符串 $s$ 和 $t$，一开始 $s=t=$```a```，接下来一共有 $t$ 组数据，每一组数据都会有 $n$ 个操作，操作 $1$ $k$ $x$ 表示在 $s$ 后面加入 $k$ 次字符串 $x$， $2$ $k$ $x$ 表示在 $t$ 后面加入 $k$ 次字符串 $x$， 求每次操作结束后，是否可以对 $s$ 和 $t$ 进行排序，使得 $s$ 的字典序小于 $t$？

### 思路

不难发现，如果 $t$ 中有一个字符不是 ```a```，那么只要把那个字符移到第一位，就可以满足 $s$ 的字典序小于 $t$，而如果两个字符串中都只有 ```a``` 的话，那就只要比较两个字符串的大小就好了

而且在一组数据中，如果已经输出了一个 ```YES``` 且此时 $t$ 不是纯 ```a```，那接下来就都输出 ```YES```

### 代码

```cpp
#include<bits/stdc++.h>
#define ll long long//要开long long
using namespace std;
ll t;
ll n;
ll a,b;//a,b 是每次操作输入的两个整数
ll q1,q2;//q1表示s是否为纯a，q2表示t是否为纯a
ll len1,len2;//len1表示s中纯a的长度,len2表示t中的
string s;
bool doushia(string s){//判断是不是纯a
	for(ll i=0;i<s.length();i++){
		if(s[i]!='a') return 0;
	}
	return 1;
}
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		r=0;
		q1=0；
		q2=0;
		len1=0;
		len2=0;
      //以上是初始化
		while(n--){
			
			cin>>a>>b>>s;
			if(a==2&&(!doushia(s))){//如果t不是纯a了
				q2=1;
			}else if(a==1&&(!doushia(s))){//如果s不是纯a了
				q1=1;
			}
			if(q2==1) cout<<"YES\n";//t不是纯a就直接YES
			else if(q1==1&&q2==0) cout<<"NO\n";//如果s不是纯a但是t是纯a就输出NO
			else if(q1==0&&q2==0){//都是纯a时比较长度
				if(a==1) len1+=(b*s.length());
				if(a==2) len2+=(b*s.length());
				if(len1<len2) cout<<"YES\n";
				else cout<<"NO\n";
			}
		}
	}
	return 0;
}
```

---

## 作者：what_can_I_do (赞：4)

[传送门](https://www.luogu.com.cn/problem/CF1742F)

其实我们只要判断 $t$ 是不是纯为 `a`，如果不是，那我们就可以把 $t$ 的第一个字符不为 `a`，让 $s$ 的第一个字符为 `a`。

但是如果 $t$ 不是纯 `a`，那么我们判断 $s$ 是否为纯 `a`，如果不是，那么 $s$ 的字典序一定会比 $t$ 大。如果是，那么就比较两者的字符串长度，如果 $t\ge s$ 则输出 `NO`，否则为 `YES`。

# CODE:
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,op,x;
char a[1000000];
signed main()
{
	scanf("%lld",&t);
	while(t--)
	{
		int slen=0,tlen=0,flag1=0,flag2=0;
		scanf("%lld",&n);
		while(n--)
		{
			scanf("%lld%lld",&op,&x);
			cin>>a;
			if(op==1)
			{
				for(register int i=0;i<strlen(a);i++) if(a[i]!='a') flag2=1;
				slen+=x*strlen(a);
			}
			else
			{
				for(register int i=0;i<strlen(a);i++) if(a[i]!='a') flag1=1;
				tlen+=x*strlen(a);
			}
			if(!flag1&&flag2) cout<<"NO"<<endl;
			else if(flag1) cout<<"YES"<<endl;
			else if(slen<tlen) cout<<"YES"<<endl;
			else cout<<"NO"<<endl;
		}
	}
	return 0;
}
```

---

## 作者：HNOIRPplusplus (赞：1)

## 题意
+ 你有两个字符串 $s$ 和 $t$，初始都为 `a`。
+ 每次在其中一个后面加上 $x$ 个字符串 $k$。
+ 求能否让 $s$ 和 $t$ 重新排列以后使得 $s$ 的**字典序**(lexicographically)比 $t$ 要小。

## 做法
可能有的人觉得这个题只能硬性完全贴着题目来做，但是那就到了 $O(n^4)$ 级别的算法，而且很繁杂，绝对不推荐。  
但是为什么初始会有一个 `a` 存放在字符串里面呢？因为，剩下的字母都比 `a` 要大。所以只要 $t$ 中有一个不是 `a` 的字母就可以把它放到第一位，那么 $s$ 的字典序绝对能比 $t$ 小。  
然而，别忘了有可能 $t$ 中间只有 `a`，这个时候当且只当 $s$ 中只有 `a` 并且比 $t$ 短才能符合题意。  

## 代码
```
#include <iostream>

using namespace std;

int main() {
  int t;
  cin >> t;
  while(t--) {
    string s, t;
    int q;
    cin >> q;
    string k;
    int x, f;
    long long sl = 1, tl = 1; // 字符串的长度直接存储下来将更快捷
    bool sa = 1, ta = 1; // 字符串是否全部都为 a 
    while(q--) {
      cin >> f >> x >> k;
      if(!ta) { // t 里面有非 a 字符将永远可行，在这里节省时间
        cout << "YES\n";
        continue;
      }
      if(f == 1) {
        for(int i = 0; i < k.length(); i++) {
          if(k[i] != 'a') {
            sa = 0;
            break;
          }
        }
        sl += k.length() * x;
      } else {
        for(int i = 0; i < k.length(); i++) {
          if(k[i] != 'a') {
            ta = 0;
            break;
          }
        }
        tl += k.length() * x;
      }
      if(!ta) { // t 里面有非 a 字符
        cout << "YES\n";
      } else if(sa && sl < tl) { // s 和 t 都只有 a，但是 s 更短
        cout << "YES\n";
      } else { // 可怜不能成功
        cout << "NO\n";
      }
    }
  }
  return 0;
}

```

---

## 作者：Allanljx (赞：1)

## 思路
由于初始两个字符串各有一个 `a`，所以只要 $t$ 加入了一个不为 `a` 的字母那么 $s$ 的字典序一定可以比 $t$ 的字典序小，其他情况只有当 $s$ 中只有 `a` 并且 `a` 的数量比 $t$ 中 `a` 的数量少时才能使 $s$ 的字典序小于 $t$。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n;
int to[3][30];
signed main()
{
	ios::sync_with_stdio(0);
	cin>>t;
	while(t--)
	{
		cin>>n;
		int f=0,f1=0;
		int s1=0,s2=0;
		while(n--)
		{
			int op;
			cin>>op;
			int x;
			string s;
			cin>>x>>s;
			for(int i=0;i<s.length();i++)
			{
				if(s[i]!='a')
				{
					if(op==2) f=1;
					else f1+=x;
				}
				else
				{
					if(op==1) s1+=x;
					else s2+=x;
				}
			}
			if(f||s1<s2&&!f1) cout<<"YES\n";
			else cout<<"NO\n";
		}
	}
}
```

---

## 作者：zibenlun (赞：0)

## 题面翻译

你有两个字符串 $s$ 和 $t$，它们初始都为 `a`，你会对字符串进行 $q$ 次操作两种类型的操作：  
操作一：在 $s$ 末尾添加字符串 $k$ 恰好 $x$ 次  
操作二：在 $t$ 末尾添加字符串 $k$ 恰好 $x$ 次  
求每次操作之后，是否可以重新排列 s 和 t 的字符，使 s 字典序比 t 小，如果可以，则 `cout<<"YES";` ，否则 `cout<<"NO";`。

## 知识点

字符串的字典序比较与正常的数字不同，它比较的主要是每一个字符的大小，只有当两个字符串较短部分完全相等时才会比较长度，而比较符号只会判断字符的大小，并不会比较长度所以长度需要单独判断。

## 题目做法

首先我们知道 `a` 是小写字母中最小的字符，所以我们可以发现，只要去维护 $s$ 的开头为 `a` 就是最有机会成立的，同时我们也要维护 $t$ 的开头不为 `a` 就可以使 $s$ 的字典序比 $t$ 小。当两者不能通过开头比较时，在比较全文或长度。

之后你提交代码就会发现超时了，那就再考虑剪枝，我们可以发现其实只要 $t$ 的开头不是 `a` 并且比 $s$ 小时那么之后一定是成立的。

---

## 作者：alex_liu (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1742F)

题意请自行看翻译。

## 分析

首先可以想到如果字符串 $t$ 中有出现非 $a$ 的字符，那么 $s$ 的字典序可以保证比 $t$ 小（由于 $s$ 一定有一个字符 $a$，让 $t$ 的非 $a$ 字符放在第一个就好）。

那么如果 $t$ 都是字符 $a$，但 $s$ 出现了非 $a$ 的字符，那么 $s$ 的字典序一定比 $t$ 大。

再考虑两个字符串的所有字符均为 $a$，则直接比较字符串长度即可。

注意统计长度的变量要开 `long long`！不然 WA on #13（本人亲测踩坑）。

给个代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n;
signed main(){
	cin>>t;
	while(t--){
		cin>>n;int f1=0,f2=0,len1=1,len2=1;
		for(int i=1,opt,k;i<=n;i++){
			string s;
			cin>>opt>>k>>s;
			if(opt==1){
				len1+=k*s.size();
				if(!f1)for(int i=0;i<s.size();i++)if(s[i]!='a'){f1=1;break;}
			}else{
				len2+=k*s.size();
				if(!f2)for(int i=0;i<s.size();i++)if(s[i]!='a'){f2=1;break;}
			}
			if(f2)puts("YES");
			else if(f1&&!f2)puts("NO");
			else puts(len1<len2?"YES":"NO");
		}
	}
	return 0;
}
```


---

## 作者：Symbolize (赞：0)

# 思路
突破口在 $s,t$ 的初始值为一个字符 `a`。显然字典序最小，`a` 肯定排首位，那如果 $t$ 不是全为 `a` 那 $s$ 的字典序就一定能小于 $t$ 的。那反之如果 $s$ 不是纯 `a`但 $t$ 是，那显然 $s$ 的字典序一定大于 $t$ 的。最后一种情况，如果都是纯 `a`，比长度就行了嘛。

# Code
下面附上 AC 代码！！！
```cpp
//简单写点注释
#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define x first
#define y second
#define rep1(i,l,r) for(int i=l;i<=r;i++)
#define rep2(i,l,r) for(int i=l;i>=r;i--)
const int N=1e6+10;
using namespace std;
int t,q,opt,x,l1,l2;
bool s1,s2;
string k;
bool check(string s)//判断全a
{
	rep1(i,0,s.length()-1) if(s[i]!='a') return 0;
	return 1;
}
void getans()
{
	cin>>q;
	while(q--)//t次询问
	{
		cin>>opt>>x>>k;
		if(opt==2&&(!check(k))) s2=1;
		else if(opt==1&&(!check(k))) s1=1;		
		if(s2==1) //t不是全a
		{
			puts("YES");
			continue;
		}
		if(s1==1&&s2==0)//t为全a，s不是
		{
			puts("NO");
			continue;
		}//下面是都为全a
		if(opt==1) l1+=(x*k.length());
		if(opt==2) l2+=(x*k.length());
		if(l1<l2) puts("YES");
		else puts("NO");
	}
	s1=s2=l1=l2=0;
	return;
}
signed main()
{
	cin>>t;
	while(t--) getans();//循环要答案
	return 0;
}
/*
思路：
只要t中有一个不是a，那就输出YES
若t是全a，但s不是，输出NO
若都是全a，判断长度。 

样例：
3
5
2 1 aa
1 2 a
2 3 a
1 2 b
2 3 abca
2
1 5 mihai
2 2 buiucani
3
1 5 b
2 3 a
2 4 paiu
*/ 
```

---

## 作者：WaterSun (赞：0)

# 思路

分类讨论即可。

一共可分为 $4$ 种情况：

1. 如果 $t$ 全为 `a`，并且 $s$ 不全为 `a`，那么输出 `NO`。

因为 $t$ 全为 `a`，$s$ 不全为 `a`，你无论怎么对 $t,s$ 排序，永远都有 $t < s$。

2. 如果 $t$ 不全为 `a`，那么输出 `YES`。

因为如果 $t$ 不全为 `a`，那么可以将其他任意一个不为 `a` 的字母放在 $t$ 的最前面，再将 `a` 放在 $s$ 的最前面即可满足条件。（注意：$s,t$ 初始状态均为 `a`）

3. 如果 $t$ 和 $s$ 都全为 `a` 或者都不全为 `a`，那么如果 $t$ 的长度小于或等于 $s$ 的长度，输出 `NO`。

 - 如果 $t$ 和 $s$ 均全为 `a`，那么字符数少的字典序小。
 
 - 如果 $t$ 和 $s$ 均不全为 `a`，这种情况是不会出现的，因为，我们条件二已经判断过了。

4. 否则输出 `YES`。

# code

```cpp
#include <bits/stdc++.h>
#define int long long
#define re register

using namespace std;

int T,n;

inline int read(){
	int r = 0,w = 1;
	char c = getchar();
	while (c < '0' || c > '9'){
		if (c == '-') w = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9'){
		r = (r << 3) + (r << 1) + (c ^ 48);
		c = getchar();
	}
	return r * w;
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> T;
	while (T--){
		int lena = 0,lenb = 0;
		bool falg1 = false,falg2 = false;
		cin >> n;
		while (n--){
			int op,x;
			string s;
			cin >> op >> x >> s;
			if (op == 1){//输入的时候处理一下 
				int len = s.length();
				for (re int i = 0;s[i];i++){
					if (s[i] != 'a'){
						falg1 = true;
						break;
					}
				}
				lena += x * len;
			}
			else{
				int len = s.length();
				for (re int i = 0;s[i];i++){
					if (s[i] != 'a'){
						falg2 = true;
						break;
					}
				}
				lenb += x * len;
			}
			if (falg1 && !falg2) cout << "NO" << endl;//四种情况判断一下 
			else if (falg2) cout << "YES" << endl;
			else if (lena >= lenb) cout << "NO" << endl;
			else cout << "YES" << endl;
		}
	}
	return 0;
}
```

---

