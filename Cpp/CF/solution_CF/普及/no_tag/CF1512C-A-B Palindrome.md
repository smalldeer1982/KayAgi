# A-B Palindrome

## 题目描述

You are given a string $ s $ consisting of the characters '0', '1', and '?'. You need to replace all the characters with '?' in the string $ s $ by '0' or '1' so that the string becomes a palindrome and has exactly $ a $ characters '0' and exactly $ b $ characters '1'. Note that each of the characters '?' is replaced independently from the others.

A string $ t $ of length $ n $ is called a palindrome if the equality $ t[i] = t[n-i+1] $ is true for all $ i $ ( $ 1 \le i \le n $ ).

For example, if $ s= $ "01?????0", $ a=4 $ and $ b=4 $ , then you can replace the characters '?' in the following ways:

- "01011010";
- "01100110".

For the given string $ s $ and the numbers $ a $ and $ b $ , replace all the characters with '?' in the string $ s $ by '0' or '1' so that the string becomes a palindrome and has exactly $ a $ characters '0' and exactly $ b $ characters '1'.

## 样例 #1

### 输入

```
9
4 4
01?????0
3 3
??????
1 0
?
2 2
0101
2 2
01?0
0 1
0
0 3
1?1
2 2
?00?
4 3
??010?0```

### 输出

```
01011010
-1
0
-1
0110
-1
111
1001
0101010```

# 题解

## 作者：xh001 (赞：4)

# 题意
首先给定一个整数 $t$ 表示有 $t$ 组数据，每组数据包含两个数 $a$，$b$ 和一个字符串，每个字符串由 $0$，$1$ 和 $?$ 构成,求将 $?$ 全部换成 $1$ 或 $2$ 且 $1$ 的数量恰好为 $a$，$2$ 的数量恰好为 $b$ 的字符串。
# 思路
在输入的同时通过回文串的性质来确定部分 $?$ 的取值，如串`10?1`可确定为`1001`，并记录下 $1$，$2$ 的个数。

输入后先特判一下串的长度为奇数且中间是 $?$ 的情况，把中间分配给还差奇数个数字的数字。

最后从两端开始枚举，若 $0$ 没用完就用 $0$，否则用 $1$。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;//好习惯。 
ll t,a,b;
string s;
inline ll read()
{
	ll k=0,f=0;char c=getchar();
	for(;!isdigit(c);c=getchar()) f|=c=='-';
	for(;isdigit(c);c=getchar()) k=(k<<1)+(k<<3)+(c^48);
	return f?-k:k;
}
int main()
{
	t=read();
	while(t--)
	{
		bool f=0;
		a=read();
		b=read();//a记录0的个数，b记录1的个数。 
		cin>>s;
		ll len=s.size();
		for(ll i=0;i<len;i++)
		{
			if((s[len-i-1]=='0' || s[len-i-1]=='1') && s[i]=='?') s[i]=s[len-i-1];//回文串的性质可以确定部分数字。 
			if(s[i]!=s[len-i-1] && s[len-i-1]!='?')
			{
				f=1;
				break; 
			}
			if(s[i]=='0') a--;
			else if(s[i]=='1') b--;
		}
		if(f)//本来就不是回文串。 
		{
			cout<<-1<<endl;
			continue;
		}
		if(len&1 && s[len/2]=='?')//特判长度为奇数的情况。 
		{
			if(a&1) s[len/2]='0',a--;
			else if(b&1) s[len/2]='1',b--;
			else
			{
				cout<<-1<<endl;
				continue;
			}
			sum--;
		}
		ll l=0,r=len-1;//从两端开始构造。 
		while(l<r)
		{
			if(s[l]!='?')//填好的就不用填了。 
			{
				l++;
				r--;
				continue;
			}
			if(a>0)
			{
				a-=2;
				s[l]=s[r]='0';
			}
			else if(b>0)
			{
				b-=2;
				s[l]=s[r]='1';
			}
			else break;
			l++;
			r--;
		}
		if(a!=0 || b!=0 || l<r) cout<<-1<<endl;//没填完就输出-1。 
		else cout<<s<<endl;
	}
	return 0;
}
```


---

## 作者：rui_er (赞：4)

给定一个长度为 $a+b$ 的由 `01?` 组成的字符串 $s$，在每个问号处填入 $0$ 或者 $1$，使得 $s$ 包含 $a$ 个 $0$ 和 $b$ 个 $1$，且 $s$ 回文。

首先，如果 $n,m$ 均为奇数，显然无解；并检验一遍已经填好的 $0$ 和 $1$ 是否有矛盾，有矛盾也无解。

然后开始构造过程。

先根据对称性把已经确认的位置填上，然后枚举不能确定的位置，如果可以填 $0$ 就填 $0$，否则（即 $0$ 用光了）就填 $1$，最后判一下 $0$ 和 $1$ 的个数是否符合即可。

代码：

```cpp
//By: Luogu@rui_er(122461)
#include <bits/stdc++.h>
#define loop while(true)
#define rep(x,y,z) for(int x=y;x<=z;x++)
#define per(x,y,z) for(int x=y;x>=z;x--)
#define fil(x,y) memset(x, y, sizeof(x))
#define mulT0 int T; for(scanf("%d", &T);T;T--)
#define mulT1 int T, rnds; for(scanf("%d", &T),rnds=1;rnds<=T;rnds++)
using namespace std;
typedef long long ll;
const int N = 4e5+5;

int n, m, k;
char s[N]; 

int main() {
	mulT0 {
		scanf("%d%d", &n, &m);
		scanf("%s", s+1); k = n + m;
		int ok = 1;
		if((n & 1) && (m & 1)) {puts("-1"); continue;}
		rep(i, 1, k) if(s[i] == '1' && s[k+1-i] == '0' || s[i] == '0' && s[k+1-i] == '1') {puts("-1"); ok = 0; break;}
		if(!ok) continue;
		rep(i, 1, k) if(s[i] != '?') s[k+1-i] = s[i];
		rep(i, 1, k) {
			if(s[i] == '0') --n;
			if(s[i] == '1') --m;
		}
		if(n < 0 || m < 0) {puts("-1"); continue;}
		rep(i, 1, k/2) if(s[i] == '?') {
			if(n > 1) s[i] = s[k+1-i] = '0', n -= 2;
			else s[i] = s[k+1-i] = '1', m -= 2;
		}
		if(k & 1) if(s[k/2+1] == '?') {
			if(n > 0) s[k/2+1] = '0', --n;
			else s[k/2+1] = '1', --m;
		}
		if(!n && !m) printf("%s\n", s+1);
		else puts("-1");
	}
	return 0;
}
```

---

## 作者：StayAlone (赞：2)

### 题意

给定 $t$ 组测试数据。每组有两行。  
第一行有两个正整数 $a$ 和 $b$。  

第二行有一个仅含有 ``0``、``1``、``?`` 的字符串，请将 ``?`` 替换成 ``0`` 或 ``1`` 使得最后的字符串是回文且恰好有 $a$ 个 ``0`` 和 $b$ 个 ``1``。  
无解则输出 $-1$。

### 思路

先判断： 
- 如果当前的字符串 ``0`` 的数量已经大于 $a$ 或 ``1`` 的数量已经大于 $b$，输出 $-1$ 并结束当前测试数据。
- 如果字符串完整：
	- 如果不合题意，输出 $-1$ 并结束当前测试数据。
   - 如果符合题意，输出字符串并结束当前测试数据。

再把**一定**的位置填上。

不难想到，由于字符串最终是回文的，所以如果一个字符存在而这个字符的另一半是 ``?``，则可以把另一半填上。  

$\otimes$**注意，上面提到的存在的字符不一定在左半边，如果左边不存在，而右边存在，同样也要把左边填上。**

```cpp
int l = s.length();
for (int i = 0; i < l / 2; ++i)
	if (s[i] != '?' && s[l-i-1] == '?') s[l-i-1] = s[i];  // 左边存在
	else if (s[i] == '?' && s[l-i-1] != '?') s[i] = s[l-i-1];  // 右边存在
```
感性理解：**如果有解，此时字符串必定回文**。而不回文的情况只有一种，就是原来输入的字符串即使不考虑 $a$ 和 $b$ 也无法回文。  
例如： $\texttt{111?011}$

这时候又可以判断：
- 如果当前字符串不回文或当前的字符串``0``的数量已经大于 $a$ 或``1``的数量已经大于 $b$，输出 $-1$ 并结束当前测试数据。
- 如果字符串完整：
	- 如果不合题意，输出 $-1$ 并结束当前测试数据。
   - 如果符合题意，输出字符串并结束当前测试数据。

最后再来判断一波：  
用 $\texttt{anum}$ 表示还需要放置的 ``0`` 的数量， $\texttt{bnum}$ 表示还需要放置的 ``1`` 的数量， $\texttt{qnum}$ 表示还有的 ``?`` 的数量。**在下面操作的过程中，值会随之而变化。**

- 如果 $anum + bnum \ne qnum$，输出 $-1$ 并结束当前测试数据。
- 如果 $anum$ 是奇数且 $bnum$ 是奇数，此时无论如何也没有解(无法回文)，输出 $-1$ 并结束当前测试数据。

到现在，程序如果还没结束，就说明**一定有解**。那现在处理起来就方便许多了。

每一次我都填两个数，以保证回文。如果最后 $\texttt{anum}$ 和 $\texttt{bnum}$ 中**某一个**等于 $1$，则说明该字符串最中间的字符是其对应字符。
而先填哪个无所谓，但要保证在填的时候那个字符所需的数量 $\geqslant 2$。

$\otimes \texttt{anum}$ 和 $\texttt{bnum}$ 最后不可能都是 $1$，因为这表示 $\texttt{anum}$ 和 $\texttt{bnum}$ 之前**均为奇数**，而这种情况一定无解，且在之前已经**跳出程序**。

[AC code记录](https://www.luogu.com.cn/record/50388694)

```cpp
#include <bits/stdc++.h>
using namespace std;
int t, a, b; string s;

int fn(char k) // 返回字符串中字符k的出现次数
{
	int ans = 0;
	for (int i = 0; i < s.length(); ++i)
		if (s[i] == k) ans++;
	return ans;
}

bool ih(string s) // 返回字符串是否回文
{
	int l = s.length();
	for (int i = 0; i < l / 2; ++i)
		if (s[i] != s[l-i-1]) return false;
	return true;
}

int main()
{
	scanf("%d", &t);
	while (t--)
	{
		scanf("%d%d", &a, &b);
		cin >> s;
		if (fn('0') > a || fn('1') > b) {puts("-1"); continue;}	
		else if (!fn('?'))
		{
			if (!ih(s)) puts("-1");
			else
				if (fn('0') == a && fn('1') == b) cout << s << endl;
				else puts("-1");
			continue;
		}
		int l = s.length();
		for (int i = 0; i < l / 2; ++i)
			if (s[i] != '?' && s[l-i-1] == '?') s[l-i-1] = s[i]; // 左边存在
			else if (s[i] == '?' && s[l-i-1] != '?') s[i] = s[l-i-1]; // 右边存在
		if (!ih(s) || fn('0') > a || fn('1') > b) {puts("-1"); continue;}	
		else if (!fn('?'))
		{
			if (!ih(s)) puts("-1");
			else
				if (fn('0') == a && fn('1') == b) cout << s << endl;
				else puts("-1");
			continue;
		}
		else
		{
			int qnum = fn('?'), anum = a - fn('0'), bnum = b - fn('1'); // 意义题解中已经阐述
			if (anum + bnum != qnum) {puts("-1"); continue;}
			if (anum % 2 && bnum % 2) {puts("-1"); continue;}	
			if (!(anum % 2) && !(bnum % 2) && qnum % 2) {puts("-1"); continue;}
			if (anum > 1)
				for (int i = s.find('?'); i < s.length()/2 && anum >= 2; ++i)
						if (s[i] == '?') s[i] = s[s.length()-i-1] = '0', anum -= 2;
			if (bnum > 1)
				for (int i = s.find('?'); i < s.length()/2 && bnum >= 2; ++i)
					if (s[i] == '?') s[i] = s[s.length()-i-1] = '1', bnum -= 2;
			if (bnum) s[s.length()/2] = '1';
			else if (anum) s[s.length()/2] = '0';
			cout << s << endl;
		}
	}
	return 0;
}
```

---

## 作者：wheneveright (赞：2)

## 题意

一句话题意，给出
 $T$ 个由 `0`、`1`、`?` 组成的字符串，以及这个字符串由 $a$ 个 `0` 和 $b$ 个 `1` 组成，要求将字符串中的 `?` 替换成 `0` 或 `1` 之后是一个回文串并且恰好有 $a$ 个 `0` 和 $b$ 个 `1`。
 
## 分析
 
这道题是细节题，有好几个小细节没思考到位就挂了。

第一个细节就是当 $a + b \not = len$，$len$ 代表字符串长时直接无解。经 @y_kx_b 提醒不存在这种情况。

首先尝试将已经可以确定的 `?` 去掉，也就是说将那些在回文串的另一边是 `0` 或 `1` 的 `?` 改成对应的数，然后观察串，将当前串内有几个 `0` 和几个 `1` 的 $a$ 和 $b$ 的值减去。

```cpp
for (int i = 1; i <= N; i++) if (s[i] != '?') {
	if (s[N - i + 1] != s[i] && s[N - i + 1] != '?') {check = true; break;}
	if (s[N - i + 1] == '?') s[N - i + 1] = s[i]; // 消除问号
}
for (int i = 1; i <= N; i++) {if (s[i] == '0') a--; if (s[i] == '1') b--;}
 
```

这里有一个判断是将回文串两边不为问号且不同的情况找出来，这种情况直接无解。

在两次循环结束后判断一下是否无解。

```cpp
if (a < 0 || b < 0 || check) {printf ("-1\n"); continue;}
```

这里用 continue 是因为是放在一个 while 循环里的。

然后再随便构造，要注意的一个细节就是当 $len$ 是单数时中间的那个数应该让 $a$ 和 $b$ 中单数的那个种类来填，如果 $a$ 和 $b$ 两个单或者两个双则无解。

## 代码

```cpp
# include <bits/stdc++.h>
using namespace std;

int T, N, a, b;
char s[400005];
bool check;

int main () {
	cin >> T;
	while (T--) {
		cin >> a >> b >> s + 1; N = strlen (s + 1); check = false;
		for (int i = 1; i <= N; i++) if (s[i] != '?') {
			if (s[N - i + 1] != s[i] && s[N - i + 1] != '?') {check = true; break;}
			if (s[N - i + 1] == '?') s[N - i + 1] = s[i];
		}
		for (int i = 1; i <= N; i++) {if (s[i] == '0') a--; if (s[i] == '1') b--;}
		if (a < 0 || b < 0 || check) {printf ("-1\n"); continue;}
		for (int i = 1; i <= N; i++) if (s[i] == '?') {
			if (N - i + 1 == i) {
				if (a & 1) {a--; s[i] = '0'; continue;}
				if (b & 1) {b--; s[i] = '1'; continue;}
				check = true; continue;
			}// 这里用 a-- 是因为只有最中间的一个字符要修改
			if (a >= 2) {a -= 2; s[i] = s[N - i + 1] = '0'; continue;}
			if (b >= 2) {b -= 2; s[i] = s[N - i + 1] = '1'; continue;}
			// 这里用 a -= 2 是因为一次修改左右两个字符而不是单个修改。
			check = true;
		}
		if (check) {printf ("-1\n"); continue;} // 无解情况抢先一步 continue
		cout << s + 1 << endl; // 将构造好的字符串输出
	}
	return 0;
}

```

---

## 作者：InversionShadow (赞：1)

硬生生被我写了 2.53 KB /kk。

首先分为几步：

+ 判断 `-1` 情况，如果 $a,b$ 均为奇数时，肯定不能组成回文串。

+ 先要判断原串是否是回文串，再统计原串中已有的 `1` 和 `0` 的数量，因为要组成回文串，所以要把原串中没有配对的不好。

+ 最后情况肯定是对应位上均为 `?`，那么如果剩余 `0` 的数量可以的话（$\ge 2$），优先两位全部变成 `0`，`1` 的情况同理。

+ 要注意 $|S|$ 为奇数的情况。

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

int t, a, b;
string s;

signed main() {
  //freopen("1.out", "w", stdout);
  cin >> t;
  while (t--) {
    cin >> a >> b >> s;
    bool flag = 1;
    for (int i = 0, j = s.size() - 1; i <= j; i++, j--) {
      if (s[i] != '?' && s[j] != '?' && s[i] != s[j]) {
        cout << "-1\n";
        flag = 0;
        break;
      }
    }
    if (!flag) {
      continue;
    }
    int n = s.size();
    if (n == 1 && a + b == 1) {
      if (s[0] == '?') {
        cout << (a == 1 ? "0\n" : "1\n");
        continue;
      } else {
        if (a == 1 && s[0] == '0') {
          cout << "0\n";
          continue; 
        } else if (b == 1 && s[0] == '1') {
          cout << "1\n";
          continue;
        } else {
          cout << "-1\n";
          continue;
        }
      }
    }
    if ((a & 1) && (b & 1) || a + b != n) {
      cout << "-1\n";
      continue;
    }
    for (int i = 0, j = n - 1; i < j; i++, j--) {
      if (s[i] == '?' && s[j] != '?') {
        s[i] = s[j];
      } else if (s[i] != '?' && s[j] == '?') {
        s[j] = s[i];
      }
    }
    for (int i = 0; i < n; i++) {
      if (a < 0 || b < 0) {
        flag = 0;
        break;
      }
      if (s[i] == '0') {
        a--;
      } else if (s[i] == '1') {
        b--;
      }
    }
    if (!flag) {
      cout << "-1\n";
      continue;
    }
    for (int i = 0; i < n / 2; i++) {
      if (a < 0 || b < 0) {
        flag = 0;
        break;
      }
      if (s[i] != '?' && s[n - i - 1] == '?') {
        if (s[i] == '0') {
          s[n - i - 1] = s[i];
          a--;
        } else {
          s[n - i - 1] = s[i];
          b--;
        }
      } 
    }
    if (!flag) {
      cout << "-1\n";
      continue;
    }
    for (int i = 0, j = n - 1; i < j; i++, j--) {
      if (a < 0 || b < 0) {
        flag = 0;
        break;
      }
      if (s[i] == '?' && s[j] == '?') {
        if (a >= 2) {
          s[i] = s[j] = '0';
          a -= 2;
        } else if (b >= 2) {
          s[i] = s[j] = '1';
          b -= 2;
        }
      }
    }
    if (n % 2 == 1 && s[n / 2] == '?' && a + b == 1) {
      s[n / 2] = (b == 1 ? '1' : '0');
    }
    if (!flag) {
      cout << "-1\n";
      continue;
    }
    for (int i = 0; i < n; i++) {
      if (s[i] == '?') {
        cout << "-1\n";
        flag = 0;
        break;
      }
    }
    if (!flag) {
      continue;
    }
    cout << s << endl;
  }
  return 0;
}
```

---

## 作者：我梦见一片焦土 (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/CF1512C)

------------

# 思路：
暴力模拟！

先把能确定的先确定，不能确定的再根据 $0$ 和 $1$ 确定，$n$ 分两种，$n$ 为偶数，$n$ 为奇数，当 $n$ 为奇数的时候，会出现 $i$ 和 $j$ 相等的情况，所以要考虑 $0$ 的个数是加 $1$ 还是加 $2$。

------------
思路：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2*1e5+10;
char s[maxn];
int main(){
    int t;
    scanf("%d",&t);
    int a,b,n,s0,s1;
    while(t--){
        s0=0,s1=0;
        scanf("%d%d",&a,&b);
        n=a+b;
        getchar();
        for(int i=1; i<=n; i++)scanf("%c",&s[i]);
        if(n==1){
            if(s[1]=='?'){
                if(a==1){
                    s[1]='0';
                    s0++;
                }else{
                    s[1]='1';
                    s1++;
                }
            }else{
                if(s[1]=='0')s0++;
                else s1++;
            }
            if(s0==a&&s1==b)printf("%c\n",s[1]);
            else printf("-1\n");
            continue;
        }
        int flag=0;
        if(n%2==0){
            int k=n/2;
            for(int i=1,j=n; i<=k; i++,j--){
                if(s[i]!='?'&&s[j]!='?'){
                    if(s[i]!=s[j]){
                        flag=1;
                        break;
                    }else{
                        if(s[i]=='0')s0+=2;
                        else s1+=2; 
                    }
                }else if(s[i]=='?'&&s[j]!='?'){
                    s[i]=s[j];
                    if(s[j]=='0')s0+=2;
                    else s1+=2;
                }else if(s[i]!='?'&&s[j]=='?'){
                    s[j]=s[i];
                    if(s[i]=='0')s0+=2;
                    else s1+=2;
                }else continue;
            }
            for(int i=1,j=n; i<=k; i++,j--){
                if(s[i]=='?'&&s[j]=='?'){
                    if((s0+2)<=a){
                        s[i]='0',s[j]='0';
                        s0+=2;
                    }else{
                        s[i]='1',s[j]='1';
                        s1+=2;
                    }
                }
                if(s1>b){
                    flag=1;
                    break;
                }
            }
        }else{
            int k=(n/2)+1;
            for(int i=1,j=n; i<=k; i++,j--){
                if(s[i]!='?'&&s[j]!='?'){
                    if(s[i]!=s[j]){
                        flag=1;
                        break;
                    }else{
                        if(i==j){
                            if(s[i]=='0')s0++;
                            else s1++;
                        }else{
                            if(s[i]=='0')s0+=2;
                            else s1+=2;
                        }
                    }
                }else if(s[i]=='?'&&s[j]!='?'){
                    s[i]=s[j];
                    if(s[j]=='0')s0+=2;
                    else s1+=2;
                }else if(s[i]!='?'&&s[j]=='?'){
                    s[j]=s[i];
                    if(s[i]=='0')s0+=2;
                    else s1+=2;
                }else continue;
            }
            for(int i=1,j=n; i<=k; i++,j--){
                if(s[i]=='?'&&s[j]=='?'){
                    if(i==j){
                        if((s0+1)<=a){
                            s[i]='0';
                            s0++;
                        }else{
                            s[i]='1';
                            s1++;
                        }
                        if(s1>b){
                            flag=1;
                            break;
                        }
                    }else{
                        if((s0+2)<=a){
                            s[i]='0',s[j]='0';
                            s0+=2;
                        }else{
                            s[i]='1',s[j]='1';
                            s1+=2;
                        }
                        if(s1>b){
                            flag=1;
                            break;
                        }
                    }
                }
            }
        }
        if(flag==1)printf("-1\n");
        else if(s0==a&&s1==b){
            for(int i=1; i<=n; i++)printf("%c",s[i]);
            printf("\n");
        }else printf("-1\n");
    }
    return 0;
}
```

---

## 作者：scp020 (赞：0)

### 题目大意

给定一个字符串（长度为 $a+b$），给定 $a$，$b$。

$a$ 表示字符串里有几个 $0$，$b$ 表示字符串里有几个 $1$。

**并且要求字符串回文。**

让你把字符串中的 $?$ 替换成 $0$ 或 $1$。

### 关于解法

首先判断原字符串是否合法。

然后暴力枚举每一个元素，如果是 $?$ 就给填上。

**中间位置要特判！**

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define I return
#define AK 0
#define IOI ;
int t,a,b,f;
string s;
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>a>>b>>s,f=0;
		if(a%2==1 && b%2==1)
		{
			cout<<-1<<endl;
			continue;
		}
		for(int i=0;i<s.size();i++)
		{
			if(s[s.size()-i-1]!=s[i] && s[i]!='?' && s[s.size()-i-1]!='?')//不满足回文 
			{
				f=1;
				break;
			}
			if(s[i]!='?' && s[s.size()-i-1]=='?') s[s.size()-i-1]=s[i];//如果一方已知就补全回文
		}
		for(int i=0;i<s.size();i++) a-=s[i]=='0',b-=s[i]=='1';//判断到底是a减还是b减，懒得用if
		if(a<0 || b<0 || f)//f在这里一起判断，可以压行 
		{
			cout<<-1<<endl;
			continue;
		}
		for(int i=0;i<s.size() && !f;i++)
		{
			if(s[i]!='?') continue;//s[i]有值就不用管
			if(i==s.size()/2)//在中间 
			{
				if(a%2==1)
				{
					s[i]='0',a--;
					continue;
				}
				if(b%2==1)
				{
					s[i]='1',b--;
					continue;
				}
				f=1;
			}
			if(f) continue;
			if(a>=2)
			{
				s[i]=s[s.size()-i-1]='0',a-=2;
				continue;
			}
			if(b>=2)
			{
				s[i]=s[s.size()-i-1]='1',b-=2;
				continue;
			}
			f=1;
		}
		if(f)
		{
			cout<<-1<<endl;
			continue;
		}else cout<<s<<endl;
	}
	I AK IOI
}
```


---

## 作者：封禁用户 (赞：0)

## 思路
先把整个数组扫一遍，如果给定的字符中有不回文的直接是无解，然后把能确定的先填上，比如 $s_i$ 是 ```?```，而 $s_{n-i+1}$ 不是，则直接 $s_{n-i+1}=s_i$。

如果出现两个都是 ```?``` 的情况，我们可以采取贪心的策略，能填 $0$ 的就填 $0$，如果不够了就换成 $1$。

最后记得再扫一遍数组，如果有不匹配的地方也是无解。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=4e5+100;
int t,x,y;
char s[N];
int main(){
	cin>>t;
	while(t--){
		cin>>x>>y>>s+1;
		bool flag=false;
		if((x&1)&&(y&1)){
			cout<<-1<<endl;continue;
		}
		int n=strlen(s+1);
		for(int i=1;i<=n;i++){
			if(s[i]!='?') {
				if(s[n-i+1]!='?'&&s[n-i+1]!=s[i]){
					flag=true;break;
				}else if(s[n-i+1]=='?'){
					s[n-i+1]=s[i];//查看已经给定的字符是否回文
				}
			}
		}
		if(flag){
			cout<<-1<<endl;continue;
		}
		for(int i=1;i<=n;i++){
			if(s[i]=='0')x--;
			else if(s[i]=='1')y--;//查看给定字符是否占满
		}
		if(x<0||y<0){
			cout<<-1<<endl;continue;
		}
		for(int i=1;i<=n;i++) {
			if(s[i]=='?'){
				if(i==n-i+1){
					if(x&1){
						x--;s[i]='0';
					}else if(y&1){
						y--;s[i]='1';
					}else{
						flag=true;break;
					}
				}else{
					if(x>=2){
						x-=2;s[i]=s[n-i+1]='0';
					}else if(y>=2){
						y-=2;s[i]=s[n-i+1]='1';
					}else{
						flag=true;break;
					}
				}
			}//填充
		}
		if(flag){
			cout<<-1<<endl;continue;
		}
		cout<<s+1<<endl;
	}
	return 0;
}

```


---

## 作者：Zhangikun (赞：0)

## 思路：
由于题目中字符串中字符 $\verb!0!$ 和 $\verb!1!$ 的个数都做了限制，而且有空位需要填，并且要求回文，所以：
- 输入的时候，$s_i$ 如果是字符 $\verb!1!$，那么 $b-1$；$s_i$ 如果是字符 $\verb!0!$，那么 $a-1$。中途如果减成了 $-1$，说明无解。

- 双指针，如果 $s_i$ 或 $s_j$ 之中有且只有一个是字符 $\verb!?!$，那么将是 $\verb!?!$ 的字符设为另一个指针的字符，然后减去 $1$ 就可以了。中途如果减成了 $-1$，说明无解。

- 第二次双指针，如果 $s_i$ 和 $s_j$ 都为 $\verb!?!$，那么填 $\verb!0!$，如果 $b=0$，那么填 $\verb!1!$，如果都不够，说明无解。填完后，如果 $i=j$ 就减去 $1$，否则减去 $2$。
## 完整代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
void help()//干脆写成函数，方便一些，不需要flag
{
  int _0,_1;
  string s;
  cin>>_0>>_1>>s;//输入
  for(int i=0;i<s.size();i++)//第一步
  {
    if(s[i]='1')_1--;
    if(s[i]='0')_0--;
  }
  //从两边往中间扫
  for(int i=0,j=s.size()-1;i<=j;i++,j--)//第二步
  {
    if(s[i]=='?'&&s[j]=='?')continue;
    if(s[i]!='?'&&s[j]!='?')continue;
    if(s[i]=='?')
    {
      if(s[j]='1')
      {
        if(_1>=1)
        {
          s[i]='1';
          _1--;
        }
        else
        {
          return void(cout<<"-1\n");
        }
      }
      if(s[j]=='0')
      {
        if(_0>=1)
        {
          s[i]='0';
          _0--;
        }
        else
        {
          return void(cout<<"-1\n");
        }
      }
    }
    if(s[j]=='?')
    {
      if(s[i]=='1')
      {
        if(_1>=1)
        {
          s[j]='1';
          _1--;
        }
        else
        {
          return void(cout<<"-1\n");
        }
      }
      if(s[i]=='0')
      {
        if(_0>=1)
        {
          s[j]='0';
          _0--;
        }
        else
        {
          return void(cout<<"-1\n");
        }
      }
    }
  }
  for(int i=0,j=s.size()-1;i<=j;i++,j--)//第三步
  {
    if(s[i]!=s[j])
    {
      return void(cout<<"-1\n");
    }
    if(s[i]=='?'&&s[j]=='?')
    {
      int cnt=2;
      if(i==j)cnt=1;
      if(_0>=cnt)
      {
        s[i]=s[j]='0';
        _0-=cnt;
      } 
      else if(_1>=cnt)
      {
        s[i]=s[j]='1';
        _1-=cnt;
      }
      else
      {
        return void(cout<<"-1\n");
      }    
    }
  }
  cout<<((_0==0||_1==0)?s:"-1")<<"\n";
}
int mian()
{
  int t;
  cin>>t;
  while(t--)//多组数据
  {
    help();
  }
  return 114514;
}
```
### 温馨提示：你如果直接复制了代码，会死得很惨。


---

