# [Algo Beat Contest 001 B] Between Head and Tail

## 题目背景

|               Problem               | Score |                         Idea                          |                             Std                              |                      Data                       |                            Check                             |                           Solution                           |
| :---------------------------------: | :---: | :---------------------------------------------------: | :----------------------------------------------------------: | :---------------------------------------------: | :----------------------------------------------------------: | :----------------------------------------------------------: |
| $\text{B - Between Head and Tail}$  | $200$ |    [joe_zxq](https://www.luogu.com.cn/user/623577)    |       [joe_zxq](https://www.luogu.com.cn/user/623577)        | [joe_zxq](https://www.luogu.com.cn/user/623577) |    [remmymilkyway](https://www.luogu.com.cn/user/551981)     | [Link](https://www.luogu.com.cn/article/3wj351hw) by [joe_zxq](https://www.luogu.com.cn/user/623577) |

## 题目描述

小 Z 将一个正整数 $X$ 称为**首中尾相等数**，当且仅当它满足下面的条件：

- $X$ 有奇数个数位。
- $X$ 的首位、末位和最中间的数位上的数字相等。

例如，$12131$ 是**首中尾相等数**，但是 $121121$ 和 $12231$ 不是。特别地，一位数都是**首中尾相等数**。

小 Z 请你求出 $[L,R]$ 中所有的**首中尾相等数**。

## 说明/提示

#### 数据范围

对于 $100\%$ 的数据，保证 $1 \le T \le 10$，$1 \le L \le R \le 10^5$。

## 样例 #1

### 输入

```
3
1 100
10 46
114 514```

### 输出

```
1 2 3 4 5 6 7 8 9

222 333 444```

# 题解

## 作者：yuhaotian000 (赞：8)

又来写题解了。\
[题目传送门](https://www.luogu.com.cn/problem/P11680)

## 题目大意
如果 $X$ 是首中尾相等数，那么 $X$ 的数位应为奇数且 $X$ 的首位、末位和最中间的数位上的数字相等。\
求出 $[L,R]$ 中所有的首中尾相等数。

## 题目解法
我们注意到数据范围，$1 \le T \le 10,1 \le L \le R \le 10^5$，也就是我们最大的数也不会超过 $100000$。由于数位应该是奇数，所以仅有 $1\sim9$、$100\sim999$、$10000\sim99999$ 有可能是首中尾相等数。

接着，对于这三个区间，我们有：
* $1\sim9$ 一定为首中尾相等数。
* $100\sim999$ 仅有三个数位，所以只要这三个数位全部相同就是首中尾相等数。
* $10000\sim99999$ 仅有五个数位，所以只要第一个数位、第三个数位、第五个数位全部相同就是首中尾相等数。

这里我们用到一个在语法段就学过的知识。数字 $X$ 的最后一个数位的数是 $X\mod10$。那么，倒数第二个数位就是 $X\div10\mod10$。以此类推，每向左一个数位就将除的数乘 $10$。第一个数位的数是 $X\div10$。

对于每个 $[L,R]$，我们只需要循环枚举即可。
## AC code
```
#include <bits/stdc++.h>
using namespace std;
int main(){
    int t;
    cin>>t;
    while(t--){
        int l,r;
        cin>>l>>r;
        for(int i=l;i<=r;i++){
            if(1<=i&&i<=9){
                cout<<i<<" ";
            }else if(100<=i&&i<=999){
                if(i%10==i/10%10&&i/10%10==i/100){
                    cout<<i<<" ";
                }
            }else if(10000<=i&&i<=99999){
                if(i%10==i/100%10&&i/100%10==i/10000){
                    cout<<i<<" ";
                }
            }
        }
        cout<<endl;
      }
      return 0;
}
```

---

## 作者：封禁用户 (赞：6)

[题目传送门](https://www.luogu.com.cn/problem/P11680)

简单题。首先从题中可以得出，我们要判断一个数是否为首中尾相等数，可以先把它转换为字符串类型，如果长度是偶数，就不是首中尾相等数。其次，如果它的首位、末位和中位上的字符有不同，就也不是首中尾相等数，具体代码如下：

```cpp
bool Check(int x)
{
    string s = to_string(x); // 转换为字符串类型
    if (!((int)s.size() % 2)) return false; // 长度是偶数
    char a = s[0], b = s.back(), c = s[(int)s.size() / 2]; // 提取首位、末位和中位上的字符
    return (a == b && a == c && b == c); // 如果全部相同就是，否则就不是
}
```

然后，由于数据范围很小，我们可以直接枚举区间 $[l,r]$ 内的数，一一判断是不是首中尾相等数，如果是就输出，记得换行。

```cpp
int T;
cin >> T;
while (T--)
{
    int l, r;
    cin >> l >> r;
    FOR(i, l, r) // 枚举从 l 到 r
        if (Check(i)) cout << i << " ";
    cout << "\n";
}
```

---

## 作者：yedalong (赞：2)

## 前言

由于数据范围挺小的，直接暴力也能过，此篇题解将介绍一种特别简便的方法。

## 思路

此题对于首中尾相等数的判断用整数来写会有点麻烦，因此我们考虑将整数转化为字符串来写。\
介绍一个很好用的函数 `to_string(x)`，它能够将整型转化为字符串。于是就很简单了，我们只需判断字符串长度是否为奇数以及字符串首位末位和中间位是否相等即可。

## AC code:

```cpp
#include <bits/stdc++.h>
using namespace std;
int T,l,r;
bool check(string s){
    if(s.size()%2&&s[0]==s[s.size()-1]&&s[0]==s[s.size()/2]) return 1;
    return 0;
}
int main(){
    cin>>T;
    while(T--){
        cin>>l>>r;
        for(int i = l;i<=r;i++) if(check(to_string(i))) cout<<i<<' ';
        cout<<'\n';
    }
    return 0;
}
```

---

## 作者：M1__ (赞：2)

# 题解：P11680 [Algo Beat Contest 001 B] Between Head and Tail
[题目传送门](https://www.luogu.com.cn/problem/P11680)                    
挺好的模拟题。
## 题目思路
首先，我们要找到的数一定要满足以下条件：
- $X$ 有奇数个数位。
- $X$ 的首位、末位和最中间的数位上的数字相等。         

所以我们可以统计这个数的位数，并将它的每一位数都存进一个数组 $a$ 中。                  
这里的存储是倒着存的，因为不论这个数组是正序还是倒序，首尾和中间项都不变。               
我们显然可以发现这个数 $X$ 的第一位即为 $a_{n}$，最后一位即为 $a_1$，而中间一位即为 $a_{\frac{n+1}{2}}$。                
最后枚举每个区间 $[L,R]$，求出即可。注意对于输出空格的判断。
## 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
bool check(int a){
	int sum=0,ans[1001],i=1,temp,temp1,temp2,b;
	while(a>0){
		b=a%10,sum++,ans[i]=b,i++,a=a/10;
	}
	temp=ans[1],temp1=ans[sum],temp2=ans[(sum+1)/2];
	if(temp==temp1&&temp1==temp2&&temp==temp2&&sum%2!=0) return 1;
	else return 0;
}
int main(){
	int T,l,r;
	cin>>T;
	while(T--){
		cin>>l>>r;
		int ans1=0;
		for(int i=l;i<=r;i++){
			if(check(i)==1) cout<<i<<" ",ans1++;
		}
		if(ans1==0) cout<<"\n";
		else cout<<"\n";
	}
	return 0;
}
```

---

## 作者：jiqihang (赞：2)

### 题目链接
[P11680 [Algo Beat Contest 001 B] Between Head and Tail](https://www.luogu.com.cn/problem/P11680)
### 分析
对于每组数据，从 $L$ 枚举到 $R$，看看每个数是否满足。

给每个数先找个字符串替身（用 `to_string` 函数），然后用字符串做判断。

满足输出即可。

每组数据最后换行。
### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main() 
{
    int T;
    cin>>T;
    while(T--)
    {
    	int L,R;
    	cin>>L>>R;
    	for(int i=L;i<=R;i++)
    	{
    		string s=to_string(i);
    		if(s.size()%2==1&&s[0]==s[s.size()-1]&&s[0]==s[s.size()/2]) cout<<s<<" ";
		}
		cout<<endl;
	}
    return 0;
}
```

---

## 作者：Vct14 (赞：2)

$l,r$ 范围不大，考虑直接从 $l$ 遍历到 $r$ 判断是否是首中尾相等数。由于位数只可能是 $1,3,5$，可以直接 $O(1)$ 判断首中尾三位数是否相等。

```cpp
#include<bits/stdc++.h>
using namespace std;

bool check(int x){
	if(x<=9) return 1;
	if((x>=10 && x<=99) || (x>=1000 && x<=9999) || x==100000) return 0;
	if(x>=100 && x<=999){
		if(x%10==x/100 && x%10==x%100/10) return 1;
		else return 0;
	}
	if(x%10==x/10000 && x%10==x/100%10) return 1;
	else return 0;
}

int main(){
	int T;cin>>T;
	while(T--){
		int l,r;cin>>l>>r;
		for(int i=l; i<=r; i++) if(check(i)) cout<<i<<" ";
		cout<<"\n";
	}
	return 0;
}

```

---

## 作者：nightwatch.ryan (赞：1)

### Analysis
枚举 $[L,R]$ 中的每一个数，判断其是否为首中尾相等数，设当前枚举到的数为 $x$。

由于要得到 $x$ 的位数，以及其首位、中位、末位，我们可以考虑将 $x$ 转化为字符串。具体地，我们可以使用 `to_string` 函数。设转化后的字符串为 $S$。

有如下步骤：
1. 判断 $S$ 的长度是否为奇数。如果不是，则 $x$ 不是首中尾相等数。
2. 判断 $S$ 的长度是否为 $1$。如果是，则 $x$ 是首中尾相等数。
3. 判断 $S$ 的首位、中位、末位是否相等，即判断 $S_0$，$S_{\lfloor \frac{n}{2} \rfloor}$ 和 $S_{n - 1}$ 是否相等。如果不相等，则 $x$ 不是首中尾相等数。
4. 否则，$x$ 是首中尾相等数。
### Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

#define P(i, a, b) for(int i = a; i <= b; i++)
#define Q(i, a, b) for(int i = a; i >= b; i--)
const int maxn = 100005;
const int inf = 0x3f3f3f3f;

mt19937 rnd(chrono::duration_cast<chrono::nanoseconds>
           (chrono::system_clock::now().time_since_epoch()).count());
int randint(int L, int R) {
    uniform_int_distribution<int> dist(L, R);
    return dist(rnd);
}

bool check(string x){
    if(x.size() % 2 == 0) return 0;
    if(x.size() == 1) return 1;
    if(x[0] == x[x.size() - 1] && x[0] == x[x.size() / 2]){
        return 1;
    }
    return 0;
}

signed main(){

    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin >> t;
    while(t --){
        int l, r;
        cin >> l >> r;
        P(i, l, r){
            if(check(to_string(i))){
                cout << i << " ";
            }
        }
        cout << endl;
    }

}
```

---

## 作者：getchar_unlocked (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P11680)

### 思路

注意到 $L$ 和 $R$ 范围都很小，于是遍历从 $L$ 到 $R$ 找出所有的中尾相等数即可。

判断方法：先将数字 $X$ 转为字符串 $S$（下标从 $0$ 开始），其长度为 $N$，需满足：

- $N\bmod2=1$（条件 1）。
- $S_1=S_{N-1}$ 且 $S_0=S_{\lfloor\frac{N}{2}\rfloor}$（条件 2）。

**AC CODE**

```cpp
#include<bits/stdc++.h>
using namespace std;
int read(){int x=0;char f=1,ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();return x*f;}
bool check(int x){
	string s=to_string(x);
	int n=s.size();
	if(!(n&1))
		return false;
	return s[0]==s[n-1]&&s[0]==s[n/2];
}
int main(){
	int T=read();
	while(T--){
		int l=read(),r=read();
		for(int i=l;i<=r;++i)
			if(check(i))
				printf("%d ",i);
		printf("\n");
	}
	return 0;
}
```

---

## 作者：DashZhanghanxu (赞：0)

# 解析
一道枚举题。

输入测试样例数，循环输入区间左端点和右端点。枚举区间内所有数字，先判断是否为一位数，若是，则直接输出，若不是，循环求出数位，判断其是否为奇数，不是，则跳过循环，否则继续判断。循环得出其中间位，首位，末尾数字，并判断是否相等，若相等，则输出该数字。最后，在每个测试数据输出完后，输出换行。
# CODE
```cpp
#include<bits/stdc++.h>
using namespace std;
int l,r,_;
int main(){
	cin>>_;
	while(_--){
		cin>>l>>r;
		for(int i=l;i<=r;i++){
			if(i%10==i){
				cout<<i<<" ";
				continue;
			}
			int sw=0,t=i;
			while(t){
				t/=10;
				sw++;
			}if(sw%2==0)continue;
			int last=i%10,first,mid,now=0;
			t=i;
			while(t){
				t/=10; 
				now++;
				if(now==sw/2)mid=t%10;
				if(now==sw-1)first=t;
			}
			if(last==mid&&mid==first)cout<<i<<" ";
		}
		cout<<"\n";
	}
	return 0;
} 
```

---

## 作者：Camellia_Spoil (赞：0)

# 思路
简单题。对于每次询问给出的 $l$ 和 $r$，对于区间 $l$ 到 $r$ 之间的每一个数 $j$，先计算出 $j$ 的位数，看看否为奇数，再判断 $j$ 的首位，末位和最中间的数位上的数字是否相等，如果以上两个条件都满足则输出。

记得特判每一个一位数都满足条件。

# AC Code

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
using namespace std;
inline long long read()
{
	long  long x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int main(){
	int n,l,r;
	n=read();
	for(int i=1;i<=n;i++)
	{
		l=read();r=read();
		for(int j=l;j<=r;j++)
		{
			int x;
			if(j<=9) x=1;
			else if(j>=10&&j<=99) x=2;
			else if(j>=100&&j<=999) x=3;
			else if(j>=1000&&j<=9999) x=4;
			else if(j>=10000&&j<=99999) x=5;
			else if(j>=100000&&j<=999999) x=6;
			if(x%2!=1) continue;
			if(x==1)
			{
				cout<<j<<" ";
				continue;
			}
			if(x==3)
			{
				int a=j%10,b=j/100,c=j/10%10;
				if(a==b&&b==c&&a==c)
				{
					cout<<j<<" ";
				    continue;
				}
			}
			if(x==5)
			{
				int a=j%10,b=j/100%10,c=j/10000;
				if(a==b&&b==c&&a==c)
				{
				    cout<<j<<" ";
				    continue;
				}
			}
		}
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：guer_loser_lcz (赞：0)

# 题解
## 思路
让我们看看哪些数不行：

1. 有偶数位。
2. 首中尾不等。

有偶数位判否：

```cpp
int log10(int x){
	int y=0;
	while(x)y++,x/=10;//数x有多少位
	return y;
}
```
如果返回值为偶数判否。

首中尾不等判否：

```cpp
bool check(int x){
	int len=log10(x);
	if(x%10==x/(int)pow(10,len-1)&&x%10==(x/(int)pow(10,len/2))%10)return 1;
	return 0;
}
x%10为个位
x/(int)pow(10,len-1)为首位
(x/(int)pow(10,len/2))%10为中间
```
## 完整代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,l,r;
int log10(int x){
	int y=0;
	while(x)y++,x/=10;
	return y;
}
bool check(int x){
	int len=log10(x);
	if(x%10==x/(int)pow(10,len-1)&&x%10==(x/(int)pow(10,len/2))%10)return 1;
	return 0;
}
int main(){
	cin>>t;
	while(t--){
		cin>>l>>r;
		for(int i=l;i<=r;i++){
			if(log10(i)%2==0)continue;
			if(check(i))cout<<i<<" ";//如果可以输出
		}
		cout<<endl;
	}
}
```

---

## 作者：ny_123457 (赞：0)

## Part 1.思路
本题一看数据，$1 \le l \le r \le 10^5$，就可以知道对于所有数据只需要讨论 `a`，`aba` 和 `abaca` 这三种情况。  
设当前正在讨论数字 $i$，第一种情况只要 $i < 10$ 就行。第二种情况需要 $i \bmod 111=0$ 且 $i$ 为一个三位数（这两种情况打表也可以但不建议）。第三种情况就需要单独拆开 $i$ 的个位，百位和万位，如果这三位相等且 $i$ 是个五位数就输出 $i$。注意输出换行在这个 $l$ 和 $r$ 讨论完后输出，无论怎样都要输出，别写循环里了，[否则这就是后果](https://www.luogu.com.cn/record/201261821)。
## Part 2.代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,l,r,ans,x;
int main(){
	cin>>t;
	while(t--){
		cin>>l>>r;
		for(int i=l;i<=r;i++){
			if(i<10){
				cout<<i<<" ";
				continue;
			}
			if(i%111==0&&i<1000&&i>100){
				cout<<i<<" ";
				continue;
			}
			if(i/10000==(i%1000)/100&&i/10000==i%10&&i>10000&&i<100000){
				cout<<i<<" ";
				continue;
			}
		}
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：joe_zxq (赞：0)

考虑枚举 $[L,R]$ 之间的所有数，依次进行判断是否是满足条件的。

由于数的位数是不定的，可以把它转为字符串再进行判断。可以手写，也可以使用 C++ 自带的 `to_string` 函数。于是若字符串 $S$ 下标从 $0$ 开始，长度为 $n$，那么需要相等的即为 $S_0$，$S_{n-1}$ 和 $S_{\lfloor \frac{n}{2} \rfloor}$。需要判断偶数位的情况。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;

#define ll long long

bool chk(string s) {
	if ((ll)s.size() % 2 == 0) {
		return 0;
	}
	return (s[0] == s[(ll)s.size() - 1] && s[0] == s[(ll)s.size() / 2]);
}

void solve() {
	ll l, r, ans = 0;
	cin >> l >> r;
	for (ll i = l; i <= r; i++) {
		if (chk(to_string(i))) {
			cout << i << " ";
		}
	}
	cout << "\n";
}

int main() {

	ll tc;
	cin >> tc;
	while (tc--) {
		solve();
	}

	return 0;
}
```

---

## 作者：违规用户名^3Zj=Oha (赞：0)

## 一、思路分析
因为本题数据范围小，因此发现可以直接暴力，从 $L$ 枚举到 $R$，每个数进行判断。判断方法也很简单，将这个数一位位分解开，存入一个贮存器(如数组等)，最后输出即可。

虽然可以直接通过，但有一个显而易见的优化，每次遇到不符合的位数的时候，可以一个大跳，时间复杂度就会降低许多，但我没有实现到代码中(~~太懒了~~)

## 二、代码实现

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T,l,r;
bool check(int x){
	vector<int> q;
	while(x){
		q.push_back(x%10);
		x/=10;
	}
	int len=q.size();
	if(len%2==0) return 0;
	if(q[0]==q[len-1]&&q[0]==q[len/2]) return 1;
	return 0;
}
signed main(){
	cin>>T;
	while(T--){
		cin>>l>>r;
		for(int i=l;i<=r;i++){
			if(check(i)) cout<<i<<" ";
		}
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：SuyctidohanQ (赞：0)

### 思路分析

按照题目模拟即可。

暴力从 $L$ 枚举至 $R$，判断这个数是否满足条件：

- 这个数有奇数个数位。

- 这个数的首位、末位和最中间的数位上的数字相等。

我们可以将这个数字转化为字符串，然后令 $l$ 为字符串的**长度**，就判断 $s _ 0$ 是否等于 $s _ {\frac{l}{2}}$ 和 $s _ {l - 1}$ 是否等于 $s _ {\frac{l}{2}}$ 即可。

### 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;
bool check (int num) {
    string s = to_string (num);
    int len = s.length ();
    if (len % 2 == 0) return false;
    char first = s[0];
    char last = s[len - 1];
    char middle = s[len / 2 + 1];
    return (first == middle) && (middle == last);
}

void findans (int L, int R) {
    for (int i = L; i <= R; i ++) 
        if (check (i)) cout << i << " ";
    cout << endl;
}
void Main () {
    int L, R;
    cin >> L >> R;
    findans (L, R);
}
int main () {
	int T; cin >> T;
	while (T --) Main ();
	return 0;
}
```

---

## 作者：easy42 (赞：0)

难点在于把数字转化成字符串。

这里使用 `to_string` 函数，可以提供一个数字给它，他会返回一个字符串。所以可以直接把数字转化成字符串，剩下直接按下标来处理和模拟就好了。

代码：

```cpp

#include<bits/stdc++.h>
using namespace std;
#define int long long
int t,l,r;
bool check(string s){
	if(s.size()%2==1&&s[0]==s[s.size()-1]&&s[0]==s[s.size()/2]){
		return true;
	}
	return false;
}
signed main(){
	cin>>t;
	while(t--){
		cin>>l>>r;
		for(int i=l;i<=r;i++){
			string h=to_string(i);
			if(check(h)) cout<<h<<" ";
		}
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：yu1128_AKIOI (赞：0)

## 思路

按题意模拟即可。对于端点中的每个数，用 `while` 先求出数位。通过数位算出其首位，再用 `while` 求出中间的数位。

注意特判数位为偶数的情况。

## 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int main(){
	cin>>t;
	while(t--){
		int l,r;
		cin>>l>>r;
		for(int i=l;i<=r;i++){
			int x=i;
			int s=0,a=x,b=x,s2=0,c,d=x%10;
			while(x){
				s++;
				x/=10;
			}
			if(s%2==0) continue;
			a/=(int)(pow(10,s-1));
			while(b){
				s2++;
				if(s2==(s+1)/2) c=b%10;
				b/=10;
			}
			if(a==d&&d==c) cout<<i<<' ';
		}
		cout<<endl;
	}
}
```

---

