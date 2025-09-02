# Prefix Flip (Easy Version)

## 题目描述

This is the easy version of the problem. The difference between the versions is the constraint on $ n $ and the required number of operations. You can make hacks only if all versions of the problem are solved.

There are two binary strings $ a $ and $ b $ of length $ n $ (a binary string is a string consisting of symbols $ 0 $ and $ 1 $ ). In an operation, you select a prefix of $ a $ , and simultaneously invert the bits in the prefix ( $ 0 $ changes to $ 1 $ and $ 1 $ changes to $ 0 $ ) and reverse the order of the bits in the prefix.

For example, if $ a=001011 $ and you select the prefix of length $ 3 $ , it becomes $ 011011 $ . Then if you select the entire string, it becomes $ 001001 $ .

Your task is to transform the string $ a $ into $ b $ in at most $ 3n $ operations. It can be proved that it is always possible.

## 说明/提示

In the first test case, we have $ 01\to 11\to 00\to 10 $ .

In the second test case, we have $ 01011\to 00101\to 11101\to       01000\to 10100\to 00100\to 11100 $ .

In the third test case, the strings are already the same. Another solution is to flip the prefix of length $ 2 $ , which will leave $ a $ unchanged.

## 样例 #1

### 输入

```
5
2
01
10
5
01011
11100
2
01
01
10
0110011011
1000110100
1
0
1```

### 输出

```
3 1 2 1
6 5 2 5 3 1 2
0
9 4 1 2 10 4 1 2 1 5
1 1```

# 题解

## 作者：Little_x_starTYJ (赞：9)

### 解题思路
题目要求让字符串 $a$ 经过若干次操作后变成 $b$，就可以说成让字符串 $a,b$ 分别经过若干次操作后相等。

如果将字符串变为只包含 $1$ 或 $0$ 的字符串时是满足操作次数小于 $n$ 的，所以我们的策略就决定了：将字符串 $a,b$ 经过 $k$ 次操作全部变为 $000\dots0$ 或 $111\dots1$。

那我们怎么进行操作呢？

例如 $a=1100101$。

那么 $a$ 的变化过程为：

$1100101 \to 0000101 \to 0101111 \to 1101111 \to 0001111 \to 1111111$。

操作区间分别为 $(1,2),(1,7),(1,1),(1,3)$。

通过以上变换我们不难找到贪心策略，如果相邻的两个字符不相等，那么我们就需要一次操作使它们变得相等。即如果 $a_i \neq a_{i+1}$ 则 `ans++`。

说得更容易理解一点，就是我们需要满足 $a_1=a_2=\cdots =a_i$，这样的话我们可以保证这个字符串要么全是 $1$，要么全是 $0$，那么这个字符串从全是 $1$ 转化为全是 $0$ 或者反过来都只需要进行一次操作。

所以，我们单个字符串的操作次数最大为 $n-1$ 次，但我们最后需要判断两个字符串是否都为 $1$ 或 $0$，如果不同的话需要再进行一次操作将它们变得相同，所以两个字符串的总操作次数最大为 $2n-1$ 次，可以通过这道题目与[加强版](https://www.luogu.com.cn/problem/CF1381A2)。

CODE：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int num[200010];
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	int t;
	cin >> t;
	while (t--)	{
		int n, id = 0;
		string a, b;
		cin >> n >> a >> b;
		for (register int i = 0; i < n - 1; i++) {
			if (a[i] != a[i + 1])
				num[++id] = i + 1;
		}
		if (a[n - 1] != b[n - 1])
			num[++id] = n;
		for (register int i = n - 1; i; i--)
			if (b[i] != b[i - 1])
				num[++id] = i;
		cout << id << ' ';
		for (register int i = 1; i <= id; i++)
			cout << num[i] << ' ';
		cout << '\n';
	}
	return 0;
}
```

---

## 作者：gaozitao1 (赞：7)

**题目大意**：给定两个二进制字符串 $a$ 和 $b$，通过不超过 $3n$ 次操作，将字符串 $a$ 变成字符串 $b$；每一次操作将字符串 $a$ 的前 $p$ 个字符中 $0$ 变成 $1$，$1$ 变成 $0$，并将前 $p$ 个字符反转。

首先考虑暴力：**尝试所有的操作顺序，直到将 $a$ 变成 $b$。**

这样的话，时间复杂度特别大，通不过这一道题，需要优化。

经过分析，可以发现，这个操作有一个特点：**每一次操作只影响前 $p$ 个字符，对 $\left(p+1\right)\sim n$ 的字符没有影响。**

所以，可以考虑从最后一位开始，让 $a$ 的字符等于 $b$ 。

**具体方法**：从最后一位开始，如果 $a$ 与 $b$ 的最后一位不相等，那么进行操作。

操作之后，字符串 $a$ 的最后一位变成了与原字符串 $a$ 第一位不同的字符，所以交换之前应该判断字符串 $a$ 的第一位和字符串 $b$ 的最后一位是否相同。如果相同，就需要先对字符串 $a$ 的第一位进行操作，再对字符串 $a$ 进行操作。

这样从字符串 $a$ 的最后一位一直改到字符串 $a$ 的第一位即可。

**代码：**
```cpp
if(a[1]==b[i])
//如果a的第一个和b的最后一个一样，那么换完时候就不一样了
//所以，应该先把a的第一个换一下
{
	c[++k]=1;
	a[1]='0'+'1'-a[1];
}
c[++k]=i;//统计方案
for(j=1; j<=i; ++j)
	a[j]='0'+'1'-a[j];
reverse(a+1,a+i+1);//进行操作
```
这样，每到一位最多改变两次，一共有 $n$ 位，最多改变 $2n$ 次，符合要求。

时间复杂度为 $O\left(n^2\right)$ ，可以通过本题。

**代码：**
```cpp
#include<algorithm>
#include<cstdio>
#include<iostream>
using std::reverse;
const int N=1000;
char a[N+1],b[N+1];
int c[N*2+1];
int main()
{
	register int i,j,k,n,t;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%s%s",&n,a+1,b+1);
		k=0;
		for(i=n; i; --i)//从最后开始操作
			if(a[i]!=b[i])//如果a和b最后一个字符不相等
			{
				if(a[1]==b[i])
				//如果a的第一个和b的最后一个一样，那么换完时候就不一样了
				//所以，应该先把a的第一个换一下
				{
					c[++k]=1;
					a[1]='0'+'1'-a[1];
				}
				c[++k]=i;//统计方案
				for(j=1; j<=i; ++j)
					a[j]='0'+'1'-a[j];
				reverse(a+1,a+i+1);//进行操作
			}
		printf("%d ",k);
		for(i=1; i<=k; ++i)
			printf("%d ",c[i]);
		putchar('\n');
	}
	return 0;
}
```
虽然这一个方法可以通过本题，但是这一种方法并不是时间复杂度最优的，还可以继续优化。

如果修改的时候同时考虑两个字符串的话，是很麻烦的，所以，可以考虑**一次只修改一个字符串**。

如果每一个字符串中只有 $0$ 或只有 $1$，那么最多操作一次就可以了。

这可以给我们启发：**可以将每一个字符串变成只有一种字符的字符串**。

所以，接下来的任务就是如何将每一个字符串变成只有一个字符的字符串。

这个可以从前面开始遍历，如果这个位置与后一个位置不同，那么就对这一个位置之前的进行操作，一直到最后就可以了。

举个例子：$01010\to11010\to00010\to11110\to00000$。

而且，我们经过上面的操作之后，**每一个字符串的字符与原字符串最后一个字符相同**，所以我们就不需要在数组中修改了，这样就减少了许多时间复杂度。

最后，我们**要判断这两个字符串是否一样**，如果一个全是 $0$ ，另一个全是 $1$，那么就需要对整个字符串进行操作。

还有一个问题：题目中让我们输出操作字符串 $a$ 的方案，但是我们在处理的过程中操作字符串 $b$ 了，所以输出时对字符串 $b$ 的方案应该倒着输出。

对于每一个字符串，最多操作 $n-1$ 次，最后判断是否一样，最多操作 $1$ 次，这样，总共操作不超过 $2n-1$ 次，符合要求。

时间复杂度为 $O\left(n\right)$。

**代码：**
```cpp
#include<cstdio>
#include<iostream>
const int N=1000;
char a[N+1],b[N+1];
int c[N],d[N];//c和d分别记录a和b的操作
int main()
{
	register int i,j,k,n,t;//j和k分别统计a和b的方案数
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%s%s",&n,a+1,b+1);
		j=k=0;//注意清零
		for(i=1; i<n; ++i)
		{
			if(a[i]!=a[i+1])
				c[++j]=i;//将a变成只有一种字符的字符串
			if(b[i]!=b[i+1])
				d[++k]=i;//将b变成只有一种字符的字符串
		}
		if(a[n]!=b[n])//如果两个字符串不一样，那么就要对整个字符串操作一次
			c[++j]=n;
		printf("%d ",j+k);//输出方案数
		for(i=1; i<=j; ++i)
			printf("%d ",c[i]);//输出a的操作
		for(i=k; i; --i)
			printf("%d ",d[i]);//倒着输出b的操作
		putchar('\n');
	}
	return 0;
}
```

---

## 作者：liaoxingrui (赞：6)

## Content

你要在 $3 \times n$ 的操作次数中将字符串 $a$ 转化为字符串 $b$。

每次操作将前 $x$ 个字符顺序颠倒，然后将字符反转，即 $0$ 变成 $1$，$1$ 变成 $0$。

$a$ 和 $b$ 只含有 $0$ 和 $1$，[加强版](https://www.luogu.com.cn/problem/CF1381A2?contestId=183308)。

## Solution

这道题我们可以将两个字符串都转化为一个字符，需要 $2 \times n - 2$ 次操作，由于可能化为的字符不一样，还需要把全部字符再转化一遍，最多 $2 \times n - 1$ 次操作，时间复杂度 $O(n)$。

对于化为一个字符，我们可以判这个字符是否与后一个字符相等，不相等就进行一次操作，由于前面一定相等，所以成立，但要注意要倒着输出转化字符串 $b$ 的操作。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,len;
int a[1005],b[1005];
string s1,s2;
int main(){
	cin>>t;
	while(t--){
		cin>>len>>s1>>s2;
		s1=' '+s1;
		s2=' '+s2;
		int sum1=0,sum2=0;
		for(int i=1;i<len;i++){
			if(s1[i]!=s1[i+1]){
				sum1++;
				a[sum1]=i;
			}
			if(s2[i]!=s2[i+1]){
				sum2++;
				b[sum2]=i;
			}
		}
		if(s1[len]!=s2[len]){
			sum1++;
			a[sum1]=len;
		}
		cout<<sum1+sum2;
		for(int i=1;i<=sum1;i++)
			cout<<" "<<a[i];
		for(int i=sum2;i>=1;i--)
			cout<<" "<<b[i];
		putchar('\n');
	}
	return 0;
}
```

---

## 作者：FChang (赞：2)

可能更好的[阅读体验](https://www.cnblogs.com/DuckYa/p/18310808)

## 思路

~~这道题直接用下一题的代码就行了~~

$C1$：

注意到限制 $3n$ 很大，于是看每一位是不是一样的，再操作，如样例一：

转化第一位：$01 \to 11$。

转化第二位：$11 \to 00 \to 10$。

每次把当前位子提到第一位，然后翻转第一位，最后翻转回去，最多 $3n$ 次，不用暴力操作直接计答案时间复杂度 $O(n)$。

$C2$：

注意到限制 $2n$ 缩小了，考虑将每一位转化为相同的 $0/1$，如样例二：

转化第一个字符串：$01011 \to 11011 \to 00011 \to 11111$。

转化第二个字符串：$11100 \to 00000$。

这个可以从前面开始遍历，如果这个位置与后一个位置不同，那么就对这一个位置之前的进行操作，这样可以保证在处理这个位置时前面的位置上的数全部相同在转化第二个字符串时因为一、二、四位都在转化时满足要求，所以跳过了这几个步骤。

把两个字符串都进行上面的操作，会的到两个全是 $0/1$ 的字符串，如果不相同的话再整体翻转一次就行了，最多 $n-1+n-1+1$ 次，即 $2n - 1$ 次操作满足要求。

## Code
就只放 $C2$ 的代码了

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;

int n;

char a[N],b[N];

int ans1[N],ans2[N];

int main() {
	ios::sync_with_stdio(0);
	int T;
	cin>>T;
	while(T--) {
		cin>>n>>(a+1)>>(b+1);
		int res1 = 0,res2 = 0; 
		for(int i = 1; i < n; ++i) {
			if(a[i] != a[i+1]) ans1[++res1] = i;
			if(b[i] != b[i+1]) ans2[++res2] = i;
		}
		if(a[n] != b[n]) ans1[++res1] = n;
		cout<<res1 + res2<<"\n";
		for(int i = 1; i <= j; ++i)	cout<<ans1[i]<<" ";
		for(int i = k; i > 0; --i) cout<<ans2[i]<<" ";
		cout<<"\n";
	}
	return 0;
}
```

---

## 作者：Guess00 (赞：2)

## CF1381A1 Prefix Flip (Easy Version)
本题$1\leq n\leq 1000$，$n^2$能过，考虑模拟。

模拟的方法很多，这里说一下我的做法:

- 明显，在第$i$位进行操作不会对第$i$位之后产生影响。

- 所以，考虑从后往前使$a$与$b$相等。

- 如果在第$i$位进行操作，那么$a_i$就会变成$\neg a_1$,如果$b_i=\neg a_1$那么只在第$i$位进行操作；如果$b_i\neq\neg a_1$那么先在$1$进行操作，再在$i$进行操作。
- 每次操作时在$a$上进行模拟。

综上，时间复杂度$\Theta(n^2),$操作次数$\Theta(2n).$

$\mathbb{CODE:}$
```
#include <bits/stdc++.h>
const int MAXN=1005;
int T,n,i,j,cnt,ans[MAXN<<1];  //最多2n,注意乘2
bool a[MAXN],b[MAXN];
char c;
inline void read(int &x)   //快读
{
	short negative=1;
    x=0;
    char c=getchar();
    while(c<'0' || c>'9')
    {
    	if(c=='-')
			negative=-1;
		c=getchar();
	}
    while(c>='0' && c<='9')
        x=(x<<3)+(x<<1)+(c^48),c=getchar();
    x*=negative;
}
inline void print(int x)   //快输
{
    if (x<0)
        putchar('-'),x=-x;
    if (x>9)
        print(x/10);
    putchar(x%10+'0');
}
signed main(void)
{
	read(T);
	while (T--)
	{
		read(n);
		for (i=1;i<=n;i++)
		{
			c=getchar();
			while (c!='0' && c!='1')
				c=getchar();
			a[i]=(c=='1');
		}
		for (i=1;i<=n;i++)
		{
			c=getchar();
			while (c!='0' && c!='1')
				c=getchar();
			b[i]=(c=='1');
		}
		for (i=n,cnt=0;i>=1;i--)
		{
			if (a[i]==b[i]) //如果这位本身就相等就不用进行任何操作
				continue;
			if (a[1]==b[i])  //b[i]!=¬a[i]
				a[1]=!a[1],ans[++cnt]=1;
			ans[++cnt]=i;
			for (j=1;j<=i;j++)  //先负一下
				a[j]=!a[j];
			for (j=1;j<=(i+1)/2;j++)  //再换位置
				std::swap(a[j],a[i+1-j]);
		}
		print(cnt),putchar(' ');
		for (i=1;i<=cnt;i++)  //输出
			print(ans[i]),putchar(' ');
		putchar('\n');
	}
	return 0;
}
```

---

## 作者：lzy120406 (赞：1)

## [原题](https://codeforces.com/problemset/problem/1381/A1)
我们需要将二进制字符串 $a$ 转换为 $b$，每次操作可以选择一个前缀，翻转并反转该前缀的位。我们的目标是在最多 $3n$ 次操作内完成转换。

## 思路
为了表述方便，记字符串 $a$ 的第 $i$ 位为 $a_i$，字符串 $b$ 的第 $i$ 位为 $b_i$。

因为字符串中只有 `0` 和 `1`，因此考虑逐位确定二进制位。

题目每次操作可以选择一个前缀，翻转并反转该前缀的位，因此考虑**倒序枚举**：

- 从字符串的**末尾**开始，逐个比较 $a_i$ 和 $b_i$。

- 如果 $a_i \ne b_i$，则对前缀 $i + 1$ 进行操作，使得 $a_i = b_i$。

具体细节看代码。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
void solve() {
	int n;
	string a, b;
	cin >> n >> a >> b;
	vector<int> operations;
	for (int i = n - 1; i >= 0; --i) {
		if (a[i] == b[i]) {
			continue;
		}
		if (a[0] == b[i]) {
			operations.push_back(1);
			a[0] = (a[0] == '0') ? '1' : '0';
		}
		operations.push_back(i + 1);
		for (int j = 0; j <= i; ++j) {
			a[j] = (a[j] == '0') ? '1' : '0';
		}
		reverse(a.begin(), a.begin() + i + 1);
	}
	cout << operations.size() << " ";
	for (int op : operations) {
		cout << op << " ";
	}
	cout << '\n';
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
```
时间复杂度 $ \mathcal{O}(tn^2) $，本题中 $\sum{n} \leq 1000$，可以通过本题。

---

## 作者：rainbow_cat (赞：1)

给个 $2n$ 的写法，倒序枚举第 $i$ 位，如果 $a_i \ne b_i$ 则需要翻转，$a_1$ 与 $b_i$ 相同，额外翻转长度为 $1$ 的前缀，接着翻转长度为 $i$ 的前缀即可。

---

## 作者：nydry (赞：0)

由于对前缀操作，只对前面的一段有影响，对后面没有影响，所以考虑从后往前修改 $a$，使得 $a$ 与 $b$ 匹配。

若当前考虑第 $i$ 位，则后面的位置都已经匹配。如果 $a_i\ne b_i$，则考虑 $a_1$ 是否与 $b_i$ 相同，若相同，直接对长度为 $i$ 的前缀进行操作，否则需要先单独操作第 $1$ 个位置，使得 $a_1=b_i$，再进行操作。

按照上述流程做，最多进行 $2n$ 次操作，符合题意，时间复杂度为 $O(n^2)$。

```
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n;
char a[1010],b[1010];
vector<int>v;
void upt(int x){//对长度为x的前缀进行操作
	v.push_back(x);
	for(int i=1,j=x;i<j;i++,j--){
		swap(a[i],a[j]);
	}
	for(int i=1;i<=x;i++){
		a[i]='0'+'1'-a[i];
	}
}
void solve(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++)cin>>b[i];
	for(int i=n;i>=1;i--){//从后往前枚举
		if(a[i]==b[i])continue;
		if(a[1]!='1'+'0'-b[i]){
			upt(1);
		}
		if(a[i]==b[i])continue;
		upt(i);
	}
	cout<<v.size()<<" ";
	for(int i=0;i<v.size();i++){
		cout<<v[i]<<" ";
	}
	cout<<"\n";
	v.clear();
}
int main(){
	//freopen("1.txt","r",stdin);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int tt;
	cin>>tt;
	while(tt--)solve();
	return 0;
}
```

---

## 作者：xuyifei0302 (赞：0)

首先，我们看见步骤不超过 $3n$，所以我们考虑把步骤拉满。

对于第 $i$ 位，如果 $s_i$ 不等于 $s1_i$，则将这一位翻转到第 $1$ 位，再将它在第一位单独翻转一次，然后把它翻转回第 $i$ 位。

下面是代码环节：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t, n, ans[3005], cnt;
string s, s1;
signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> t;
	while (t --) {
		cin >> n >> s >> s1;
		s = " " + s;
		s1 = " " + s1;
		for (int i = 1; i <= n; i ++) {
			if (s[i] != s1[i]) {
				ans[++cnt] = i;
				ans[++cnt] = 1;
				ans[++cnt] = i;
			}
		}
		cout << cnt << " ";
		for (int i = 1; i <= cnt; i ++) {
			cout << ans[i] << " ";
		}
		cout << "\n";
		cnt = 0;
	}
	return 0;
}
```

---

## 作者：zhizhi_c (赞：0)

考虑倒着扫，这样不会对之前修改的产生影响。

如果 $a_i=b_i$，不需要执行操作。但 $a_i\ne b_i$ 时，我们可以考虑对长度为 $i$ 的前缀进行操作，也就是 $a_1$ 取反会赋给 $a_i$。但当 $a_1=b_i$ 时，就不合法，但我们对长度为 $1$ 的前缀进行操作，就能将 $a_1$ 取反，达成我们的目的。

所以我们就可以通过 A1 了。

```cpp
/**
 * 开始时间：2024-07-18 15:33:08
 * 预计完成时间：2024-07-18 HH:MM
 * 作者：zhizhi_c
 * 题目：Codeforces Round 658 (Div. 2) C1. Prefix Flip
 * 版本：0.0
 * 思路：倒着扫，同时进行操作
 */
#include <bits/stdc++.h>
#define rep(i, b, e) for (auto i(b); i <= (e); i++)
#define req(i, b, e) for (auto i(b); i >= (e); i--)
#define range(i, b, e) for (auto i(b); i != (e); i++)
using namespace std;

const int N = 1e5;
int T, n;
char a[N+5], b[N+5];
int path[N*2 + 5];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cin >> T;

	while (T--) {
		cin >> n >> a+1 >> b+1;
		path[0] = 0;
		l = 1, r = n; flag = false;

		req(i, n, 1) if (a[i] != b[i]) {
			if (a[1] != a[i]) path[++path[0]] = 1, a[1] ^= 1;
			path[++path[0]] = i;
			rep(j, 1, i) a[j] ^= 1;
			reverse(a+1, a + i+1);
		}

		cout << path[0];
		rep(i, 1, path[0]) cout << ' ' << path[i];
		cout << '\n';
	}

	return 0;
}
```

---

## 作者：Anita_Hailey (赞：0)

## 正文

**本文是 hard 版本的**，~~因为我只会 2 次的~~

一个构造题，考虑 hard 版本，他说了要不多于 2n 次。所以由于 cf 的惯例，我们一定可以两次搞出来一位，最多，于是考虑怎么 2 次出一位。

由于他给你的是前缀，所以我们考虑搞最后那一位，这样子之后的操作不会在影响它了。所以问题站变成了：考虑一个长度为n的串，按照题目的操作，要把它最后一位搞出来。


令 $h1$ 为初始串，$h2$ 为结果串。

分二种情况讨论

- 以第一次为例，这样的话，我们 $h1[1]$ 和 $h2[n]$ 要不一样才能进行一个 $n$ 翻转，那么事实上一样的话，如果我们先进行一个 $1$ 反转即可。

- 以第二次为例，我们要 $h1[n]$ 和 $h2[n-1]$ 一样才行，如果不一样的话，还是可以先进行 $1$ 反转，最后做一个 $n$ 反转即可。


那么，做好映射就很重要了，这里直接给出 了

假如之前的串是 abcdef 那么，我们最后的结果是 dcebfa, 不难观察出规律了。下边是代码，有兴趣可以看看
```cpp

namespace Solution
{
#define IOS std::ios::sync_with_stdio( false ), std::cin.tie( 0 ), std::cout.tie( 0 )
#define Rep( i, j, k ) for( int i = j; i >= k; --i )
#define rdi( ) read < int > ( )
#define rdl( ) read < long long > ( )
#define pti( i ) print < int > ( i ), putchar( '\n' )
#define ptl( i ) print < long long > ( i ), putchar( '\n' )
#define For( i, j, k ) for( int i = j; i <= k; ++i )
	using std::cin;
	using std::cout;
	using std::endl;
	using std::vector;
	using std::map;
	using std::queue;
	using std::deque;
	using std::set;
	using std::pair;
	const int Maxn = 204001;
	int t, n, s1[ Maxn ], s2[ Maxn ]; 
	inline char gck( )
	{
		char ch = gc( );
		while( ch == ' ' || ch == '\r' || ch == '\n' )
			ch = gc( );
		return ch;
	}
	void fakemain( )
	{
		t = rdi( );
		while( t-- )
		{
			n = rdi( );
			For( i, 1, n )
				s1[ i ] = gck( ) - '0';
			For( i, 1, n )
				s2[ i ] = gck( ) - '0';
			vector < int > ans;
			Rep( i, n, 1 )
			{
				int k = n - i;
				int a = s2[ i ];
				if( ( n - i ) & 1 )
				{
					int b = s1[ n - k / 2 ];
					if( b != a )
						ans.push_back( 1 );
					ans.push_back( i );
				}
				else
				{
					int b = s1[ k / 2 + 1 ];
					if( b == a )
						ans.push_back( 1 ); 
					ans.push_back( i );
				}
			}
			printf( "%d", ( int ) ans.size( ) ); 
			for( auto &to : ans )
				printf( " %d", to );
			pc( '\n' ); 
		}
		return;
	}

} // namespace Solution
```


---

## 作者：Lydia1010__ (赞：0)

## 本题思路：
这道题其实并不复杂，我们可以从后往前进行更改，因为 $n$ 的范围很小，我们就可以暴力翻转区间，看当前这一位一不一样，一样先翻一再翻他即可。
## 本题代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100005];
vector<int>ans;
int main(){
	int t;
	cin>>t;
	while(t--){
		int n;ans.clear();
		cin>>n;
		string s,t;
		cin>>s>>t;
		s=' '+s;t=' '+t;
		for(int i=1;i<=n;i++) s[i]-='0',t[i]-='0';
		for(int i=n;i>=1;i--){
			if(s[i]==t[i]) continue;
			else{
				if(s[1]!=t[i]) ans.push_back(i);
				else {
					ans.push_back(1),ans.push_back(i);
					s[1]=1-s[1];
				}
				for(int j=1;j<=i;j++){
					s[j]=1-s[j];
				}
				for(int j=1;j<=i/2;j++){
					swap(s[j],s[i-j+1]);
				}
//				for(int j=1;j<=n;j++) cout<<s[j];cout<<endl;
//				cout<<s;
			}
		}
		cout<<ans.size()<<" ";
		for(int i=0;i<ans.size();i++) cout<<ans[i]<<" ";
		cout<<endl;
	} 
	return 0;
}
```

---

