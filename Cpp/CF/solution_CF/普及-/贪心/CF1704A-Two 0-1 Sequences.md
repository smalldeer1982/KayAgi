# Two 0-1 Sequences

## 题目描述

你有两个 $01$ 串 $a$ 和 $b$，每次你可以对 $a$ 串进行以下两种操作（以下 $a_1$ 表示 $a$ 现在的第一个字符，$a_2$ 表示 $a$ 现在的第二个字符，以此类推）：

1. 若 $|a| \geq 2$，则可将 $a_2$ 改为 $\min(a_1,a_2)$，然后删除 $a_1$。
2. 若 $|a| \geq 2$，则可将 $a_2$ 改为 $\max(a_1,a_2)$，然后删除 $a_1$。

显然，删除 $a_1$ 后，原先的 $a_2$ 变成 $a_1$，$a_3$ 变成 $a_2$，$a$ 的长度减少 $1$。

试判断 $a$ 是否能够经过若干次操作（也可以不进行操作）变成 $b$。

## 样例 #1

### 输入

```
10
6 2
001001
11
6 2
110111
01
6 2
000001
11
6 2
111111
01
8 5
10000101
11010
7 4
1010001
1001
8 6
01010010
010010
8 4
01010101
1001
8 4
10101010
0110
7 5
1011100
11100```

### 输出

```
YES
YES
NO
NO
NO
YES
YES
NO
NO
YES```

# 题解

## 作者：Lyrella (赞：2)

# 题意

给你两个字符串 $a$ 和 $b$，$a$ 和 $b$ 只包含 $0$ 和 $1$。有两种关于 $a$ 的变化方式：

- 将 $a_1$ 变成 $\min(a_1,a_2)$，将 $a_2$ 到 $a_n$ 分别向前挪一位。

- 将 $a_1$ 变成 $\max(a_1,a_2)$，将 $a_2$ 到 $a_n$ 分别向前挪一位。

要判断能否将 $a$ 转换成 $b$。

# 思路

1. 要将 $a$ 变成 $b$，首先得保证长度一样。

2. 要知道 $a$ 只有最前面能动。

3. 设 $len_a = n$，$len_b = m$。则 $a$ 中只有 $a_1$ 到 $a_{n-m+1}$ 能动。

### 所以

先判断 $a_{n-m+2}$ 到 $a_n$ 与 $b_2$ 到 $b_m$ 是否匹配，再在 $a_1$ 到 $a_{n-m+1}$ 中判断是否存在 $b_1$ 即可。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int T, n, m;
char a[55], b[55];
signed main()
{
	scanf("%d", &T);
	while(T--)
	{
		bool fl = true;
		scanf("%d %d %s %s", &n, &m, a + 1, b + 1);
		if(n < m){puts("NO"); continue;}
		for(int i = strlen(a + 1), j = strlen(b + 1); j > 1; j--, i--)
		if(a[i] != b[j]){fl = false; break;}
		if(!fl){puts("NO"); continue;}
		fl = false;
		for(int i = 1; i <= strlen(a + 1) - strlen(b + 1) + 1; i++)
		if(a[i] == b[1]){fl = true; break;}
		if(fl)puts("YES");
		else puts("NO");
	}
	return 0;
}
```


---

## 作者：sunkuangzheng (赞：1)

## 题目描述
给定两个仅由 $0$ 和 $1$ 构成的字符串 $a$ 和 $b$，$a$ 的长度为 $n$，  $b$ 的长度为 $m$，当 $a$ 的长度 $ \ge 2$ 时可以对 $a$ 有如下操作：

- 将 $a_2$ 变为 $\min(a_1,a_2)$ 并删除 $a_1$。
- 将 $a_2$ 变为 $\max(a_1,a_2)$ 并删除 $a_1$。

问经过若干操作能否使 $a$ 与 $b$ 完全相同。

题目保证 $m \le n$。

## 思路

首先，只能对 $a$ 字符串的第一项进行改变，因此要想使 $a$ 和 $b$ 最终变得相同，必须使 $a_{n-m+2}$ 到 $a_n$ 的部分与 $b_2$ 到 $b_m$ 的部分完全相同。

然后对于 $a_1$ 到 $a_{n-m+1}$ 的部分，我们有以下结论：若区间内有任一个字符与 $b_1$ 相同，则可以使 $a$ 和 $b$ 变得完全相同。

若 $b_1 = 0$，$a_1$ 到 $a_{n-m+1}$ 的部分有一个字符为 $0$，则可以通过 $\min$ 操作使 $a_1$ 最终变成 $0$；反之如果 $b_1 = 1$，$a_1$ 到 $a_{n-m+1}$ 的部分有一个字符为 $1$，则可以通过 $\max$ 操作使 $a_1$ 最终变成 $1$。

## 完整代码
```cpp
#include <cstdio>
#include <iostream>
using namespace std;

int main(){
    char a[1005],b[1005];
    int t,n,m;
    cin >> t;
    while(t --){
    	bool ans = 1;
    	cin >> n >> m;
    	cin >> a >> b;
    	for(int i = 1;i < m;i ++){
    		if(a[i+n-m] != b[i]){
    			ans = 0;
    			cout << "haha";
			}
		}
		if(ans == 0){
			cout << "NO" << endl;
			continue;
		}
		ans = 0;
		for(int i = 0;i <= n - m;i ++){
			if(b[0] == a[i]){
				ans = 1;
			}
		}
		if(ans == 0){cout << "NO" << endl;}
		else{cout << "YES" << endl;}
	}
	return 0;
}
```

---

## 作者：Simclover (赞：0)

这道题很简单，因为判断 $a$ 能否通过操作转变为 $b$，我们需要判断 $a$ 有没有足够的字符来转变为 $b$。

怎么判断呢？如果 $a$ 可以转变为 $b$，那么 $a$ 需要满足以下两点：

+ $a_{n-m+2}$ 到 $a_n$ 的部分必须与 $b_2$ 到 $b_m$ 的部分相同。因为要保证 $a$ 与 $b$ 相同，所以操作后 $a$ 的长度必须等于 $m$，所以 $a_{n-m+2}$ 到 $a_n$ 的部分是不能动的，才能保证在长度上满足要求。

+ $a_1$ 到 $a_{n-m+1}$ 中至少要有一个字符等于 $b_1$。我们可以发现，在进行若干次操作后，任何一个位置上的元素，都可以变成这个元素位置的前面任何一个字符或者这个元素本身。因为 $b_2$ 到 $b_m$ 的部分固定下来了，所以我们需要判断 $a_1$ 到 $a_{n-m+1}$ 中是否有字符可以变为 $b_1$，也就是判断 $a_1$ 到 $a_{n-m+1}$ 中是否有字符等于 $b_1$。

按照上面的方式来写代码，最后输出结果即可。代码很好写就不放了。

---

## 作者：123rrc (赞：0)

## 题意

给你两个 $01$ 串 $a$ 和 $b$，可对 $a$ 进行以下两种操作：

1. 若 $|a| \geq 2$，则可将 $a_2$ 改为 $\min(a_1,a_2)$，然后删除 $a_1$。
2. 若 $|a| \geq 2$，则可将 $a_2$ 改为 $\max(a_1,a_2)$，然后删除 $a_1$。

试判断 $a$ 是否能够经过若干次操作（也可以不进行操作）变成 $b$。

以下记 $n=|a|$，$m=|b|$。

## 思路

显然，只有当 $a$ 的长度与 $b$ 的长度相等时，$a$ 才有可能与 $b$ 相同。因此，只能对 $n-m+1$ 个字符进行操作。因此，只有 $a_{n-m+2}$ 到 $a_n$ 都是动不了的，我们需要一一检验它们是否一致，只要有一处不一致就输出 ``NO``。

检验完后，我们再看字符 $b_1$ 是否存在于 $a_1 \sim a_{n-m+1}$ 中，若存在就输出 ``YES``，否则输出 ``NO``。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;
	cin>>t;
	while(t--){
		int n,m,cnt=0,flag=1;
		cin>>n>>m;
		string a,b;
		cin>>a>>b;
		a=" "+a; //便于处理（使下标从1开始）
		b=" "+b;
		if(a==b){ //显然a==b时绝对是YES
			cout<<"YES"<<endl;
			continue;
		}
		if(m==1){ //赛时加的特判，补下面代码的锅（虽然我不知道哪有锅）
			int flagggg=0;
			for(int i=1;i<=n;i++){
				if(a[i]==b[1]){
					flagggg=1;
					cout<<"YES"<<endl;
					break;
				}
			}
			if(!flagggg){
				cout<<"NO"<<endl;
			}
			continue;
		}
		for(int i=n;;i--){ //处理第n到第n-m+2个字符
			if(a[i]!=b[m-cnt]){
				cout<<"NO"<<endl;
				flag=0;
				break;
			}
			cnt++;
			if(cnt==m-1){
				break;
			}
		}
    	//第一重判断结束
		if(flag){
			int flag2=0;
			for(int i=1;i<=n-m+1;i++){
				if(a[i]==b[1]){
					flag2=1;
					break;
				}
			}
        	//第二重判断结束
			if(flag2){
				cout<<"YES"<<endl;
			}else{
				cout<<"NO"<<endl;
			}
		}
	}
	return 0;
}
```

---

## 作者：xzy090626 (赞：0)

# CF1704A 题解
## 题意
有两个 01 序列 $a,b$，长度分别为 $n,m$。你每次可以对 $a$ 进行以下操作中的任意一种：
- 如果 $a$ 的长度 $\ge 2$，那么使 $a_2 = \min(a_1,a_2)$，然后删去 $a_1$。
- 如果 $a$ 的长度 $\ge 2$，那么使 $a_2 = \max(a_1,a_2)$，然后删去 $a_1$。

请问，$a$ 有没有可能在若干次操作后变为 $b$？

多测，$1\le t \le 2000$，$1 \le n,m \le 50,m \le n$。
## 分析
这题其实颇具思维难度，评橙是合理的。

首先我们要确定一点：执行操作的次数必须为 $n-m$，因为 $a,b$ 的长度首先要相等。

这同时也可以告诉我们，对于 $a_{[n-m+2,n]}$，如果与对应的 $b_{[2,m]}$ 不同的话，一定不可能成功。

现在重点就来到了 $a_{m-n+1}$ 和 $b_1$ 上了。

因为 $a$ 可以改变，所以我们可以尝试让 $a_{m-n+1}$ 变为 $b_1$。

我们考虑贪心。

让 $a_{[2,m-n]}$ 都尽可能地变为 $b_1$，因为这样才能使得 $a_{m-n+1}$ 有可能变为 $b_1$。

那么如何判断是否可以修改 $a_i$ 呢？

很简单，当 $a_i$ 异于 $a_{i-1}$ 时，可以修改 $a_i$。

这道题就成功解决了。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
bool arr1[105],arr2[105];
void solve(){
	memset(arr1,0,sizeof(arr1));
	memset(arr2,0,sizeof(arr2));
	int a,b;
	char c;
	cin>>a>>b;
	c = getchar();
	while(!isdigit(c)) c = getchar();
	for(int i=1;i<=a;++i){
		if(c=='1') arr1[i] = 1;
		c = getchar();
	}
	while(!isdigit(c)) c = getchar();
	for(int i=1;i<=b;++i){
		if(c=='1') arr2[i] = 1;
		c = getchar();
	}
	for(int i=a-b+2,j=2;i<=a && j<=b;++i,++j){
		if(arr1[i]!=arr2[j]){
			cout<<"no\n";
			return ;
		}
	}
	if(arr1[a-b+1]==arr2[1]){
		cout<<"yes\n";
		return ;
	}
	for(int i=2;i<=a-b+1;++i){
		if(arr1[i]!=arr2[1] && arr1[i]!=arr1[i-1]) arr1[i] = arr2[1];
	}
	if(arr1[a-b+1]!=arr2[1]) cout<<"no\n";
	else cout<<"yes\n";
}
int main(){
	int T;
	cin>>T;
	while(T--) solve();
	return 0;
}
```

---

## 作者：hyc1026 (赞：0)

### 题意：

给你两个 $\tt{01}$ 串，问字符串 $a$ 能否通过以下操作变为字符串 $b$。

操作：如果现在的字符串的第一位字符不等于第二位字符，则可以将第二位字符变为 $\tt{0}$ 或 $\tt{1}$ 的任意一个，否则不变。

完成以上操作后将第一个字符删除。

### 思考与做法：

首先我们知道，如果字符串 $b$ 中**任意**一个字符的数量超过了字符串 $a$ 中的，那么不可能符合题意，输出 $\tt{NO}$。

其次我们可以想到，每次变化只能变化最前面的字符，也就是说，后面的字符是不会变的。如果 $a$ 的**最后** $m-1$ 个字符不完全等于字符串 $b$ 的**最后** $m-1$ 个字符，那么无法做到相同，输出 $\tt{NO}$。

在满足以上条件时，我们假设 $a$ 的**倒数**第 $m$ 个字符为 $x$。

若 $x$ 为 $\tt{0}$，从 $a$ 的**正数**第一位一直枚举到**倒数**第 $m+1$ 位，全都为 $\tt{1}$ 输出 $\tt{NO}$，否则输出 $\tt{YES}$。

若 $x$ 为 $\tt{1}$，从 $a$ 的**正数**第一位一直枚举到**倒数**第 $m+1$ 位，全都为 $\tt{0}$ 输出 $\tt{NO}$，否则输出 $\tt{YES}$。

到此为止，我们才完成了本题。

### AC Code:

注意记录时要使用字符类型保存。

此代码为赛时 AC 代码，可能因为各种原因较乱，请自行理解。

```cpp
#include <bits/stdc++.h>
using namespace std;
 
int a[55], b[55];
int c[55];
 
int main()
{
	int t;
	cin >> t;
	while(t--)
	{
		int n,m;
		cin >> n >> m;
		int a0 = 0, a1 = 0, b0 = 0, b1 = 0;
		for(int i=1; i<=n; i++)
		{
			char c;
			cin >> c;
			if(c == '0') a[i] = 0;
			else a[i] = 1;
			if(a[i] == 0) a0++;
			else a1++;
		}
		for(int i=1; i<=m; i++)
		{
			char c;
			cin >> c;
			if(c == '0') b[i] = 0;
			else b[i] = 1;
			if(b[i] == 0) b0++;
			else b1++; 
		}
		if(a0 < b0 || a1 < b1)
		{
			cout << "NO" << endl;
			continue;
		}
		bool flag = true;
		for(int i=n; i>=n-m+2; i--)
		{
			if(a[i] != b[i-n+m])
			{
				cout << "NO" << endl;
				flag = false;
				break;
			}
		}
		if(!flag) continue;
		flag = false;
		for(int i=1; i<=n-m+1; i++)
		{
			if(a[i] == b[1])
			{
				cout << "YES" << endl;
				flag = true;
				break;
			}
		}
		if(!flag) cout << "NO" << endl; 
	}
}
```

---

## 作者：OLE_OIer (赞：0)

# CF1704A Editorial

这道题是 CF Div.1+Div.2 的一道题。总体来说这套比赛的题都挺不错，个人认为对选手的代码能力及思维能力都可以有很大的提升。

好了，进入正题吧。题意不多说了，题面说的挺清楚了。

首先，题目给出的两种操作方式就很有意思。

我们看对于 $01$ 串的前两个字符，对它们是 $0$ 或 $1$ 的情况讨论：

第 $1$ 种情况：第 $1$ 个与第 $2$ 个字符都是 $0$，此时无论删最大的和删最小的都会删掉一个 $0$。

第 $2$ 种情况：第 $1$ 个与第 $2$ 个字符都是 $1$，与前面一种类似，无论删最大的和删最小的都会删掉一个 $1$。

第 $3$ 种情况：第 $1$ 个字符是 $0$，第 $2$ 个字符是 $1$，此时可以删去 $0$ 与 $1$ 中的一个。

第 $3$ 种情况：第 $1$ 个字符是 $1$，第 $2$ 个字符是 $0$，此时也可以删去 $0$ 与 $1$ 中的一个。

所以我们可发现其实题目就在说我们每次可以删去第 $1$ 个与第 $2$ 个字符中的任意一个。

题目就转换为了按照上面说的方法问能否将一个 $01$ 串转换为另一个 $01$ 串。

我们接下来这么想：要想把一个 $01$ 串转换为另一个 $01$ 串，就得把中间的一段或几段子串删掉。

可是一旦在一个子串的前面有超过 $1$ 个字符时，就不能操作了。

所以我们得出：一个 $01$ 串（称为初始串）可以转换为另一个 $01$ 串（称为结束串）的充分必要条件是：结束串的除去其第一个字符的子串在初始串的末尾存在，且结束串的首字符在除去上述初始串的子串的子串中存在。

开始读起来会有点绕，但是多回味回味就能理解了。

对于代码实现部分：在初始串长度小于结束串长度时要特判，否则会出问题。

附上代码实现：
```cpp
//CF1704A Two 0-1 sequences
#include<bits/stdc++.h>
#define int long long
#define elif else if
#define rd(i) fixed<<setprecision(i)
using namespace std;
void func(){
	int n,m;cin>>n>>m;
	string a,b;cin>>a>>b;
	if(n<m){//特判
		cout<<"NO\n";
		return;
	}
	int p,q;
	for(p=n-1,q=m-1;q>0;--p,--q){
		if(a[p]!=b[q]){//如果出现字符不匹配就输出 NO
			cout<<"NO\n";
			return;
		}
	}
	for(int i=0;i<=p;++i){
		if(a[i]==b[0]){//如果存在就输出 YES
			cout<<"YES\n";
			return;
		}
	}
	cout<<"NO\n";
	return;
}
signed main(){
	ios::sync_with_stdio(false);
	int n;cin>>n;
	for(int i=1;i<=n;++i) func();
	return 0;
}
```

---

## 作者：happy_dengziyue (赞：0)

### 1 视频题解

![](bilibili:BV1BU4y1Y7Tc)

### 2 思路

我们可以分两段看：$a_1$ 到 $a_{n-m+1}$（以下简称前一段）和 $a_{n-m+2}$ 和 $a_n$（以下简称后一段）。

其中，前一段要通过执行 $n-m$ 次操作的方式缩减为 $b_1$，后一段不可能变更。

可以发现，当 $b_1=0$ 时，执行 $n-m$ 次 $\min$ 操作总是最优的；否则执行 $\max$ 操作总是最优的。

我们可以发现，当且仅当前一段存在一个数等于 $b_1$，前面这一段可以缩减成 $b_1$。

然后，我们要看看后一段与 $b_2$ 到 $b_m$ 是否做到对应位置一一匹配。

满足上述两个条件就可以输出 `YES`，否则输出 `NO`。

### 3 代码与记录

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
int t;
int n;
char a[62];
int m;
char b[62];
bool ans;
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1704A_1.in","r",stdin);
	freopen("CF1704A_1.out","w",stdout);
	#endif
	scanf("%d",&t);
	while(t--){
		scanf("%d%d%s%s",&n,&m,a+1,b+1);
		ans=false;
		if(n<m){
			printf("NO\n");
			continue;
		}
		for(int i=1;i<=n-m+1;++i){
			if(a[i]==b[1]){
				ans=true;
				break;
			}
		}
		for(int i=n-m+2,j=2;i<=n;++i,++j){
			if(a[i]!=b[j]){
				ans=false;
				break;
			}
		}
		if(ans)printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/82186425)

By **dengziyue**

---

## 作者：yinhy09 (赞：0)

## 思路讲解：

我们要把一个长度 $n$ 的 $0,1$ 串变成另一个长度为 $m$ 的，每次操作删去一个，所以只能操作 $n-m$ 次，最终只会改变结束串的的第一位，所以我们只需要每一次删一下第一位，然后将原来的第二位同步成第二个串的第一位（当然得能同步的话），直到长度为 $m$。最终只需要比较两个串即可。

## AC Code:

```cpp
// Problem: A. Two 0-1 sequences
// Contest: CodeTON Round 2 (Div. 1 + Div. 2, Rated, Prizes!)
// URL: https://codeforces.com/contest/1704/problem/A
// Memory Limit: 256 MB
// Time Limit: 1000 ms
// Author: Luogu-yinhy09(575320),Codeforces-yinhy09
 
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
ll read()
{
	char c;
	ll x=0;
	ll f=1;
	c=getchar();
	while(c<'0'||c>'9')
	{
		if(c=='-')f*=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		x=(x<<1)+(x<<3)+(c^48);
		c=getchar();
	}
	return x*f;
}
ll T;
ll n,m;
string s,t;
void print(ll a)
{
	if(a==1)printf("YES\n");
	else printf("NO\n");
}
int main()
{
	T=read();
	while(T--)
	{
		n=read(),m=read();
		cin>>s>>t;
		for(int i=0;i<n-m;i++)
		{
			if(s[0]!=s[1])
			{
				s[1]=t[0];
				s.erase(s.begin());
			}
			else s.erase(s.begin());
		}
		if(s==t)print(1);
		else print(0);
	}
	return 0;
}
```

谢谢观看~

---

## 作者：Failure_Terminator (赞：0)

## Problem

给定一个长度为 $n$ 的 01 字符串 $a$ 和一个长度为 $m$ 的 01 字符串 $b$，问是否能通过以下两种（仅对于字符串 $a$ 的）操作，使字符串 $a$ 与 $b$ 完全相同。

- 操作 $1$：若 $|a| \ge 2$，则可以使 $a_2 =\max(a_1,a_2)$，并删除 $a_1$；

- 操作 $2$：若 $|a| \ge 2$，则可以使 $a_2 =\min(a_1,a_2)$，并删除 $a_1$。

## Solution

### Part 0

可以得知，有以下一种特殊情况：

- 若 $n < m$，由于 $b$ 无法对其使用任何操作，则 $a$ 无论如何都无法等于 $b$。

### Part 1

除去 **Part 0** 的情况后，我们也只能对前 $n-m+1$ 个字符进行操作，否则无论如何都会导致出现 **Part 0** 当中的情况。

因此 $a$ 无法操作的部分，也就是 $a_{n-m+2}$ 到 $a_n$，都必须保持与从 $b_2$ 到 $b_m$ 的字串相同。

就此，我们又得到了一种情况：

若有上述部分有任一字符不相同的情况，则不可能使 $a$ 变成 $b$。

### Part 2

而对于 $a$ 的前 $n-m+1$ 个字符，如果有任一字符与 $b_1$ 相等，则必然可以使 $a$ 变成 $b$。

否则不可能。

 _证明：_ 

若 $a$ 中有任一字符与 $b_1$ 相等，

- $b_1$ 等于 $0$ 时，则可以通过 $\min$ 操作使 $a$ 的前 $n-m+1$ 个字符得出的结果为 $0$。否则，即 $a$ 的前 $n-m+1$ 个字符都为 $1$，无法用任何操作使其变为 $0$。

- 同理，$b_1$ 等于 $1$ 时，则可以通过 $\max$ 操作使 $a$ 的前 $n-m+1$ 个字符得出的结果为 $1$。否则，即 $a$ 的前 $n-m+1$ 个字符都为 $0$，无法用任何操作使其变为 $1$。


_证毕。_ 

## AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m;
string a,b;
void solve(){
    bool f=true;
    cin>>n>>m>>a>>b;
    if(n<m){cout<<"NO\n";return ;}
    for(int i=1;i<m;i++)
        if(a[i+n-m]!=b[i]) f=false;
    if(!f){cout<<"NO\n";return ;}
    f=false;
    for(int i=0;i<n-m+1;i++)
        if(a[i]==b[0]) f=true;
    cout<<((f)?"YES\n":"NO\n");
}
int main()
{
    cin>>t;
    while(t--) solve();
    return 0;
}
```

Written by **haimo**

---

## 作者：Andrewzdm (赞：0)

首先不要看错题，只有 $a$ 序列是可以操作的，$b$ 序列是不会变的。而 $a$ 的操作又要删除元素，所以 $m\le n$ 才能使 $a$ **有可能** 变成 $b$。（赛时看题目浏览得比较匆忙，没注意到题目保证 $m \le n$，所以代码中有一处特判，删去不影响）

由于最后 $a$ 的长度从 $n$ 变为 $m$，而每次操作只能改变第一个元素，所以原序列 $a$ 和 $b$ 的后 $m-1$ 位必须相同。

$a$ 的两个操作可以达到的效果是，使删去前面 $x$ 位后得到的第一位可以取前 $x+1$ 位的任意值。因此只需要再 check 一下 $b$ 的第 $1$ 位在 $a$ 的前 $n-m+1$ 位中有没有出现就好了。

时间复杂度 $O(n)$，代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 55;
int n, m;
char a[maxn], b[maxn];

void work()
{
    scanf("%d%d", &n, &m);
    scanf("%s%s", a + 1, b + 1);
    if(n < m)  //前面提到的特判，删去不影响。
    {
        puts("No");
        return;
    }
    for(int i = n; i >= n - m + 2; --i)
        if(a[i] != b[m + i - n])
        {
            puts("No");
            return;
        }
    for(int i = n - m + 1; i >= 1; --i)
        if(a[i] == b[1])
        {
            puts("Yes");
            return;
        }
    puts("No");
    return;
}

int main()
{
    int T;
    cin >> T;
    while(T--) work();
    return 0;
}
```

---

