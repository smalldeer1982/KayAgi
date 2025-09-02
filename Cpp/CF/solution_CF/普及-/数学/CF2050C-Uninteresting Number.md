# Uninteresting Number

## 题目描述

给定一个数字 $n$，它的长度最多为 $10^5$。

你可以进行以下操作任意次数：选择它的某一位数字，将该数字平方，并将原来的数字替换成平方后的结果。新的数字必须是一个数字（即，如果你选择数字 $x$，那么 $x^2$ 必须小于 $10$）。

你的任务是判断，是否可以通过这些操作，将这个数字变成一个可以被 $9$ 整除的数字？

## 样例 #1

### 输入

```
9
123
322
333333333333
9997
5472778912773
1234567890
23
33
52254522632```

### 输出

```
NO
YES
YES
NO
NO
YES
NO
YES
YES```

# 题解

## 作者：alan1118 (赞：4)

## 题意

[【题目】](https://www.luogu.com.cn/problem/CF2050C)

题目里说的比较清楚了，这里就不再重复了。

## 思路

首先，题目里说平方要 $<10$，也就是说只能选择 $1,2,3$ 这三个数进行操作。

其中 $1^2=1$，并没有变化，所以并没有提供任何价值。那么我们就只需要从 $2,3$ 入手，将他们的数量分别记下来。

通过计算我们发现：$2^2=4$，增加了 $2$；$3^2=9$，增加了 $6$。所以我们只需要把 $n\bmod9$ 等于多少算出来（可以用 $9$ 的倍数的性质：各数位数字和相加是 $9$ 的倍数。 这样就可以避免记录 $n$ 本身。），然后看看它与 $9$ 相差多少，直接枚举选几个 $2$ 和几个 $3$ 可以凑出这个数，如果凑不出就输出 `No`。

以上就是大体思路，其他的一些细节可以看代码注释。

## Code

``` cpp
#include <iostream>
using namespace std;

int main()
{
	int t;
	cin >> t;
	while(t--)
	{
		string s;
		cin >> s;
		long long n = 0, a = 0, b = 0;
		for(int i = 0; i < s.size(); i++)
		{
			n += s[i]-'0';
			if(s[i] == '2') a++;
			if(s[i] == '3') b++;
		}
        if(n % 9 == 0) // 这里注意如果 n 本来就是 9 的倍数就直接输出。
        {
            cout << "Yes" << endl;
            continue;
        }
		int m = 9 - n%9;
        // 如果上面没有直接输出， m 需要这样计算：m = (n%9 == 0 ? 0 : 9-n%9)
		bool f = false;
		for(int i = 0; i <= a; i++) // 注意 i 和 j 要从 0 开始枚举
		{
			for(int j = 0; j <= b; j++)
				if((i*2+j*6)%9 == m) // 这里有可能加的超过 m，但超过部分是 9 的倍数，所以要 %9。
				{
					cout << "Yes" << endl;
					f = true;
					break;
				}
			if(f) break;
		}
		if(!f) cout << "No" << endl;
	}
	return 0;
}
```

---

## 作者：include13_fAKe (赞：2)

好久没写题解了，今天写一篇练练手。

## 题意

给定一个多位数，每一次可以将某一位上的数 $x$ 改为其平方（要求 $x^2\le 10$），询问能否经过若干次修改（也可以不修改）将这个数变为 $9$ 的倍数。

$T$ 组数据（$1\le T \le 10^4$）。设多位数在十进制下的位数为 $n$，保证 $\sum n\le10^5$。

## 思路

首先，只有 $\le 3$ 的数位可以改动。因为 $4^2=16$。

然后，修改 $1$ 是无意义的，因为 $1^2=1$。只能修改 $2$ 和 $3$。

在修改 $2$ 时，数会变为 $4$，增加了 $2$，且不可以被再次修改。

在修改 $3$ 时，数会变为 $9$，增加了 $6$，且不可以被再次修改。

设所有修改之前的数字和为 $st$，我们可以先将 $st$ 对 $9$ 取余。

设 $dp$ 数组表示数字和是否能达到 $i$，将原先的数字 $2$ 和数字 $6$ 拿进去跑背包即可。若存在任何一个 $i$ 满足 $i\equiv 0 \pmod{9}$ $dp_i=\texttt{true}$，则目标可以达成。

此处可以在跑暴力背包之前先将 $st$ 对 $9$ 取模再跑背包，当 $dp_0,dp_9,dp_{18},dp_{27},\dots$ 中有某一个为 $\texttt{true}$ 时，目标可以达成。实际上只需枚举到 $dp_{27}$ 即可。

还可以在跑暴力背包前先把多余的数字 $2$ 和数字 $6$ 去除掉。（其实我没这么做）

时间复杂度 $O(\sum n)$。我跑了 $\texttt{93 ms}$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

string s;
int dp[40];
int st=0;
int ptr=0;
int a[114514];
void solve(){
	ptr=0;
	st=0;
	memset(dp,0,sizeof(dp));
	cin>>s;
	int n=s.size();
	s=' '+s;
	for(int i=1;i<=n;i++){
		int now=s[i]-'0';
		st+=now;
		st%=9;
		if(now==2)	a[++ptr]=now;
		if(now==3)	a[++ptr]=6;
	}
	dp[st]=1;
	for(int i=1;i<=ptr;i++){
		for(int j=30;j>=a[i];j--){
			dp[j]=dp[j]|dp[j-a[i]];
		}
	}
	if(dp[0]||dp[9]||dp[18]||dp[27])	cout<<"YES"<<endl;
	else	cout<<"NO"<<endl;
	return;
}
int T;
int main(){
	cin>>T;
	while(T--)	solve();
	return 0;
}
```

---

## 作者：long_long__int (赞：2)

# 题目翻译

[这里](https://www.luogu.com.cn/paste/uq5aiofy)。
# 题目解法

让一个一位数的平方小于十，那么这个一位数 $\le 3$，而让 $1$ 变成 $1$ 没有意义，所以只用考虑 $2$ 和 $3$ 的情况。把 $2$ 变成 $2^2$ 即 $4$ 会把和增加 $2$，把 $3$ 变成 $3^2$ 即 $9$ 会把和增加 $6$，如果某个数的数字和等于 $9$，那么这个数可以被 $9$ 整除。

- $2$ 的情况：如果有超过 $8$ 个 $2$，那么通过改变这些 $2$，可以凑出所有模 $9$ 的余数，所以直接判定 `Yes`。
- $3$ 的情况：如果有超过 $2$ 个 $3$，且原数模 $3$ 的余数为 $0$，那么这几个 $3$ 也可以使余数为 $0$，判定 `Yes`。

接下来就是枚举了。

令 $a$ 为 $2$ 的个数，$b$ 为 $3$ 的个数，那么枚举改变 $1\sim a$ 个 $2$，$1\sim \min(b,2)$ 个 $3$，如果某时和对 $9$ 的余数为 $0$，那么也判定 `Yes`。

最后判定 `No`。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int T;
int n;
string s; 
bool flag=false;
void work(){
	flag=false;
	cin>>s;
	n=s.size();
	s=' '+s;
	int sum=0,a=0,b=0;
	for(int i=1;i<=n;i++){
		sum+=s[i]-'0';
		a+=(s[i]=='2');
		b+=(s[i]=='3');
	}
	if(!(sum%9) or a>=9 or b>=3 and !(sum%3)) return printf("Yes\n"),void();//最开始的特判
	for(int i=0;i<=a;i++){//枚举2
		int x=sum+i*2;
		if(!(x%9)) return printf("Yes\n"),void();
		for(int j=0;j<=min(b,2);j++){//枚举3
			int y=x+j*6;
			if(!(y%9)) return printf("Yes\n"),void();
		}
	}
	printf("No\n");
}

int main(){
	cin>>T;
	while(T--) work();
	return 0;
}
```

---

## 作者：Z_AuTwT (赞：1)

题意较为明了，故在此不做解释。

## 思路

由于一个数平方后仍是一位数，所以操作的数必须小于等于三，这是显然的。

根据平方的概念我们又可以得到一个显然的结论：对零和一进行操作是没有意义的。那么可以操作的范围就只有两个数了，这个范围显然是小的。

我们考虑九的倍数的特征：就是一个数如果是九的倍数，那么这个数的数位和一定也是九的倍数。

所以我们可以对这个数的数位和来操作，于是我们统计数位里有多少个二和三，然后枚举各操作多少个。

但这个范围显然是大的，所以考虑优化。因为是对九取模，所以最大只会操作到二和三与九的最小公倍数次。

## code

```c++
#include<bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
    int t;
    cin>>t;
    while(t--){
        string s;
        cin>>s;
        int n=s.size();
        s=" "+s;//将下标变成以一开头
        int Cnt2=0,Cnt3=0;
        long long Sum=0;
        for(int i=1;i<=n;i++){
            if(s[i]=='2') ++Cnt2;//统计2的个数
            if(s[i]=='3') ++Cnt3;//统计3的个数
            Sum+=s[i]-'0';//计算数位和
        }
        bool Flag=false;
        for(int i=0;i<=min(Cnt2,9);i++){//lcm(2,9)=18,18/2=9,所以最多操作9次
            for(int j=0;j<=min(Cnt3,3);j++){//lcm(3,9)=9,9/3=3,所以最多操作3次
                if((Sum+2*i+6*j)%9==0){//判断是否为9的倍数
                    Flag=true;
                }
            }
        }
        if(Flag) cout<<"YES\n";
        else cout<<"NO\n";
    }
}
```

---

## 作者：xuyifei0302 (赞：1)

# 大致题意
给定一个长度不超过 $10^5$ 的数字 $n$。

选择它的一个数字 $x$ 将它变为 $x^2$ ( $x^2 \le 9$ )。

通过任意次操作，是否可能获得一个能被 $9$ 整除的数字？

# 解法
  因为 $x^2 \le 9$，所以 $x \le 3$,但是 $0^2$ 为 $0$, $1^2$ 为 $1$。所以，所选的 $x$ 应从 $2$、 $3$ 中选择。且 $2^2$ 为 $4$, $3^3$ 为 $9$。对于 $2$， 每次只会增加 $2$，每 $9$ 次为 $9$ 的倍数。对于 $3$，每次只会增加 $6$，每 $3$ 次为 $9$ 的倍数，所以 $3$ 最多选 $2$ 个，不然没有意义。所以，我们可以考虑去枚举选 $2$ 和选 $3$ 的个数，因为 $2$ 至多选 $8$ 个， $3$ 至多选 $2$ 个，所以枚举的时间复杂度为一个小常数，不超过 $27$。判断是否是 $9$ 的倍数只需判断位数和是否为 $9$ 的倍数。所以代码的总时间复杂度为 $O(n)$。如果存在可行的情况输出 ```YES``` 否则输出 ```NO```。

**提示**：记得枚举不选的情况！

接下来是代码环节：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t, a[20];
string s;
signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> t;
	while (t --) {
		memset(a, 0, sizeof(a));
		cin >> s;
		int len = s.size();
		s = " " + s;
		int sum = 0;
		for (int i = 1; i <= len; i ++) {
			sum += s[i] - '0';
			a[s[i] - '0'] ++;
		}
		if (sum % 9 == 0) {
			cout << "YES\n";
			continue;
		}
		bool flag = false;
		for (int i = 0; i <= min(8, a[2]); i ++) {
			if ((sum + i * 2) % 9 == 0) {
				cout << "YES\n";
				flag = true;
				break;
			}
			for (int j = 0; j <= min(2, a[3]); j ++) {
				if ((sum + i * 2 + j * 6) % 9 == 0) {
					cout << "YES\n";
					flag = true;
					break;
				}
			}
			if (flag) {
				break;
			}
		}
		if (!flag) {
			cout << "NO\n";
		}
	}
	return 0;
}
```

---

## 作者：NEKO_Daze (赞：1)

[洛谷CF2050C](https://www.luogu.com.cn/problem/CF2050C) || [CodeForces 2050 C](https://codeforces.com/contest/2050/problem/C)

### 简要题意

给出 $t$ 个数。对于每个数 $a_i$，我们可以对其进行任意次操作：将一个数位上的数平方并替换。平方后的数**必须也是个位数**。回答这个数是否可以通过若干次操作变为 $9$ 的倍数。

### 思路

分类讨论 $+$ 暴力枚举。

因为要求平方后的数必须也是个位数，有不等式 $x^2<10,0\le x \le 9$，解得 $0\le x\le 3$。所以我们只能对 $0,1,2,3$ 进行操作。又因为 $0^2=0,1^2=1$，所以这两个数进行操作没有意义，我们只需要对 $2$ 和 $3$ 操作即可。

一个数能被 $9$ 整除的充要条件为**各数位之和能被 $9$ 整除**。对于每个 $2$，操作后各数位之和会增加 $2^2-2=2$，同理可得每次对 $3$ 操作都会增加 $3^2-3=6$。我们可以枚举每一种可能的操作（操作 $i$ 个 $2$ 和 $j$ 个 $3$），判断操作后的数位和是否可以被 $9$ 整除即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
int t;
void f(int cnt2, int cnt3, int m)
{
    for (int i = 0; i < min(10, cnt2+1); i++) //枚举
            for (int j = 0; j < min(10, cnt3+1); j++)
                if ((m + i * 2 + j * 6) % 9 == 0) {cout << "YES\n";return;} //判断
    cout << "NO\n";
}
int main()
{
    cin >>t;
    while (t--)
    {
        int cnt2, cnt3, m;cnt2=cnt3=m=0;string x;
        cin >> x;
        for(int k= 0; k < x.length();k++) //统计
        {
            int z = x[k]-'0';
            if (z == 2) cnt2++;
            if (z == 3) cnt3++;
            m+=z;
        }
        f(cnt2, cnt3, m);
    }
}
```

---

## 作者：linch (赞：0)

### 引理
一个数能被 $9$ 整除，当且仅当它各个数位上的数字之和能被 $9$ 整除。

该定理较为简单，此处不作证明。

## Solution
由于给定数字 $n$ 的长度小于等于 $10^5$，故不能直接计算。需要考虑 $9$ 的倍数的性质。容易发现，可以使用数位上数字和计算（见引理）。

首先，每次平方要求平方后的数字小于 $10$，那么原数字 $x$ 一定小于等于 $3$。

当被平方数 $x$ 取 $0$ 或 $1$ 时，平方后结果不变，那么就不需要考虑这两个数字。

当 $x=2$ 时，平方后为 $4$，此时数字增加 $2^2-2=2$。同理，当 $x=3$ 时，数字增加 $3^2-3=6$。

记 $a$ 为数字 $2$ 在 $n$ 中出现次数，$b$ 为数字 $2$ 在 $n$ 中出现次数。那么题目可以转化为：将 $n$ 至多加上 $a$ 次 $2$ 和 $b$ 次 $6$ 后，是否有可能变成 $9$ 的倍数。

容易的出一种做法：我们可以记录下这个数中数字 $2$ 和 $3$ 的个数。通过枚举两个数字各平方几次，计算总数字和，若总数字和是 $9$ 的倍数，即满足条件。

但是这样做复杂度明显过高，考虑优化。

容易发现，当 加上 $\frac{9}{\gcd(2,9)}=9$ 次 $2$ 时等价于不进行操作。也就是说，我们只需要枚举到 $\min\{9,a\}$ 次。对于加上 $3$ 也同理，容易发现，枚举到 $\min\{3,b\}$ 次即可。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
string n;
int main(){
	cin>>t;
	while(t--){
		bool flag=false;
		int a=0,b=0,sum=0;
		cin>>n;
		int len=n.length();
		for(int i=0;i<len;i++){
			sum+=n[i]-'0';
			if(n[i]=='2'){
				a++;
			}
			else if(n[i]=='3'){
				b++;
			}
		}
		for(int i=0;i<=min(9,a);i++){
			for(int j=0;j<=min(3,b);j++){
				int k=sum+i*2+j*6;
				if(k%9==0){
					flag=true;
				}
			}
		}
		if(flag) cout<<"YES\n";
		else cout<<"NO\n";
	}
	return 0;
}
```

[AC record](https://codeforces.com/contest/2050/submission/297596007)

---

## 作者：banglee (赞：0)

## CF2050C Uninteresting Number 题解
[洛谷传送门](https://www.luogu.com.cn/problem/CF2050C)

[Codeforces 传送门](https://codeforces.com/problemset/problem/2050/C)
## 前言
太多篇 C++ 题解了，我来篇 Python 题解。
## 思路
可以将 $0$ 变换为 $0$，将 $1$ 变换为 $1$，将 $2$ 变换为 $4$，将 $3$ 变换为 $9$。任何其他数字的平方都会超过 $9$，因此无法变换。得出结论，一共有两种可能的操作：将数字 $2$ 或数字 $3$ 平方。

规定当且仅当一个数字的数位之和能被 $9$ 整除时，这个数字才能被 $9$ 整除。如果对 $2$ 进行平方运算，数位之和将增加 $2^2 - 2 = 2$ ；如果对 $3$ 进行平方运算，数位之和将增加 $3^2 - 3 = 6$ 。

计算数字中 $2$ 的个数和数字中 $3$ 的个数。变换超过 $8$ 个 $2$ 和超过 $8$ 个 $3$ 的余数是没有意义的，因为它们的变换加到总和中的余数模 $9$ 会重复。

假设改变了 $x$ 个 $2$ 和 $y$ 个 $3$ ，那么这个数的个位数之和就增加了 $x \times 2 + y \times 6$ 。如果新的和能被 $9$ 整除，那么答案就为 `YES`。如果在迭代过程中从未出现过这种情况，则答案为 `NO`。
## Code
```python
T = int(input())
while T:
    s = [int(x) for x in list(input())]

    sm = sum(s)
    two = s.count(2)
    three = s.count(3)
    flag = False
    for i in range(min(10, two + 1)):
        if not flag:
            for j in range(min(10, three + 1)):
                if (sm + i * 2 + j * 6) % 9 == 0:
                    print('YES')
                    flag = True
                    break
        else:
            break
    if not flag:
        print('NO')
    T -= 1
```

---

## 作者：HYdroKomide (赞：0)

### 题意：

给定一个大数，每次可以对任意一个十进制位乘方然后放回原处，不允许增加位数，问随意操作后是否可以整除 $9$。

### 思路：

题目不允许增加位数，只有 $1,2,3$ 可以操作，而 $1$ 不会产生任何贡献，直接考虑 $2,3$。

当对 $2$ 进行乘方操作时，$2$ 会变成 $4$，对结果的贡献是 $2$。同理，$3$ 进行操作的贡献是 $6$。要使最终大数整除 $9$，必须使其数位之和整除 $9$。

不难发现实际的有效位数并不多，如果我们有足够的 $2$（多于 $9$ 个），必然可以直接判可行，选定其中一些 $2$ 乘方必然可以涵盖所有除以 $9$ 的余数情况。而对于 $3$，它对结果余数的贡献是 $6,3,0$ 的循环，实际最多需要考虑的有效位数只有 $3$ 位。

只需要考虑小于 $9$ 个 $2$ 和 $3$ 个 $3$，直接暴力。

### 程序如下：

```cpp
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
int T,n;
char ch[100005];
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%s",ch+1);
		n=strlen(ch+1);
		int tot=0,cnt2=0,cnt3=0;
		for(int i=1;i<=n;i++){
			tot+=ch[i]-'0';
			if(ch[i]=='2')cnt2++;
			if(ch[i]=='3')cnt3++;
		}
		if(cnt2>=9||tot%9==0||(tot%3==0&&cnt3>=3)){
			printf("YES\n");
			continue;
		}
		bool flag=false;
		int newtot=tot;
		for(int j=1;j<=cnt3&&j<=3;j++){
			newtot+=6;
			if(newtot%9==0){
				flag=true;
				break;
			}
		}
		for(int i=1;i<=cnt2;i++){
			tot+=2;
			if(tot%9==0){
				flag=true;
				break;
			}
			int newtot=tot;
			for(int j=1;j<=cnt3&&j<=3;j++){
				newtot+=6;
				if(newtot%9==0){
					flag=true;
					break;
				}
			}
			if(flag)break;
		}
		if(flag)printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
```

### THE END

---

## 作者：The_foolishest_OIer (赞：0)

给一种比较麻烦的做法。

首先要知道，一个数是 $9$ 的倍数，那么这个数的各个数位上的数字之和一定是 $9$ 的倍数。

统计开始的各个数位上的数字之和，然后对这个数模 $9$，就得到了 $9$ 种不同的情况。

观察可得，操作仅对数字 $2$ 和数字 $3$ 有效果，统计数字 $2$ 和数字 $3$ 的出现次数即可。

分讨手工推，这里不赘述，具体情况见代码。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
int T,n;
string s;
void close(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
}
void solve(){
	cin >> s;
	n = s.length();
	int cnt1 = 0,cnt2 = 0,sum = 0;
	for (int i = 0 ; i < n ; i++){
		if (s[i] == '2') cnt1++;
		if (s[i] == '3') cnt2++;
		sum += (s[i] - '0');
	}
	int x = sum % 9;
	if (x == 0) cout << "YES\n";
	else if (x == 1){
		if ((cnt1 >= 1 && cnt2 >= 1) || cnt1 >= 4) cout << "YES\n";
		else cout << "NO\n";
	}else if (x == 2){
		if ((cnt1 >= 2 && cnt2 >= 2) || (cnt1 >= 5 && cnt2 >= 1) || (cnt1 >= 8)) cout << "YES\n";
		else cout << "NO\n";
	}else if (x == 3){
		if (cnt1 >= 3 || cnt2 >= 1) cout << "YES\n";
		else cout << "NO\n";
	}else if (x == 4){
		if ((cnt1 >= 1 && cnt2 >= 2) || (cnt1 >= 4 && cnt2 >= 1) || (cnt1 >= 7)) cout << "YES\n";
		else cout << "NO\n";
	}else if (x == 5){
		if (cnt1 >= 2) cout << "YES\n";
		else cout << "NO\n";
	}else if (x == 6){
		if (cnt1 >= 6 || cnt2 >= 2 || (cnt1 >= 3 && cnt2 >= 1)) cout << "YES\n";
		else cout << "NO\n"; 
	}else if (x == 7){
		if (cnt1 >= 1) cout << "YES\n";
		else cout << "NO\n";
	}else if (x == 8){
		if (cnt1 >= 5 || (cnt1 >= 2 && cnt2 >= 1)) cout << "YES\n";
		else cout << "NO\n";
	}
}
signed main(){
	close();
	cin >> T;
	while (T--) solve();
	return 0;
}
```

---

## 作者：GeYang (赞：0)

# 题意

[翻译已经足够明确](https://www.luogu.com.cn/problem/CF2050C)。

# 思路

因为题目要求一个数字平方后不能大于 $10$ 且你每次只能对一个数字平方，所以这个数字必须小于 $\sqrt {10}$，符合要求的整数只有 $1$ 和 $2$ 和 $3$。

但是 $1^2=1$，平方后与原数值相等，所以我们可以不做考虑。

因为 $2^2-2=2$，$3^2-3=6$，所以我们只需要枚举 $2$ 和 $3$ 的个数，个数可以为零。

当某一时刻，整个数的数字和可以被 $9$ 整除时，输出 `YES`，如果无论怎么枚举都无法满足条件，那么输出 `NO`。

---

