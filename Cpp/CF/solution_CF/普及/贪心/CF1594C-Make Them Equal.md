# Make Them Equal

## 题目描述

Theofanis has a string $ s_1 s_2 \dots s_n $ and a character $ c $ . He wants to make all characters of the string equal to $ c $ using the minimum number of operations.

In one operation he can choose a number $ x $ ( $ 1 \le x \le n $ ) and for every position $ i $ , where $ i $ is not divisible by $ x $ , replace $ s_i $ with $ c $ .

Find the minimum number of operations required to make all the characters equal to $ c $ and the $ x $ -s that he should use in his operations.

## 说明/提示

Let's describe what happens in the third test case:

1. $ x_1 = 2 $ : we choose all positions that are not divisible by $ 2 $ and replace them, i. e. bzyx $ \rightarrow $ bzbx;
2. $ x_2 = 3 $ : we choose all positions that are not divisible by $ 3 $ and replace them, i. e. bzbx $ \rightarrow $ bbbb.

## 样例 #1

### 输入

```
3
4 a
aaaa
4 a
baaa
4 b
bzyx```

### 输出

```
0
1
2
2 
2 3```

# 题解

## 作者：智子 (赞：1)

## 题意

输入一个整数 $n$ ，一个字符 $c$ 和一个长度为 $n$ 的字符串 $s$。

选择若干个数 $x$，对于 $s$ 的第 $i$ 个字符 $s_i$，如果 $i$ 不能被 $x$ 整除，$s_i$ 就会被替换为 $c$。

求最少的操作次数和任意一种方案。

## 思路

本题的关键是，不论 $s$ 的内容如何，答案最多只为 $2$。因为选取了 $n$ 和 $n - 1$ 后肯定会将 $s$ 的所有字符全部变成 $c$，所以只需要考虑是否只需要一步就能解决问题即可，如果不能就直接输出 `2  ` 和 `n n - 1`。

对于只需要一步的情况，直接枚举即可，复杂度 $O(n \ln n)$。

## 代码

```cpp
#include<iostream>
using namespace std;

const int MAXN = 300000 + 5;

char c, s[MAXN];
int n, m;

int main() {
    int T;

    cin >> T;
    while(T--) {
        cin >> n >> c >> (s + 1);
        int cnt = 0;
        for(int i = 1; i <= n; i++) {
            if(s[i] != c) {
                cnt++;
            }
        }
        if(cnt == 0) {
            cout << 0 << endl;
            continue;
        }
        int ans = 0;
        bool p = false;
        for(int i = 1; i <= n; i++) {
            bool flag = true;
            for(int j = i; j <= n; j += i) {
                if(s[j] != c) {
                    flag = false;
                }
            }
            if(flag) {
                ans = i;
                p = true;
                break;
            }
        }
        if(p) {
            cout << 1 << endl;
            cout << ans << endl;
        } else {
            cout << 2 << endl;
            cout << n << " " << n - 1 << endl;
        }
    }

    return 0;
}
```

---

## 作者：Huami360 (赞：1)

首先如果所有字符已经是目标字符了，输出 $0$ 。

下面讨论答案不是 $0$ 的情况。

显然答案最多不超过 $2$， 因为可以选择 $n$ 和 $n-1$

所以我们的任务就是讨论什么时候答案是 $1$

把所有需要变的位置放入一个数组。

于是枚举从$2$ 到 $n$ 枚举 $i$ ， 如果数组里所有数都不是 $i$ 的倍数，那么答案就是 $1$， 这个 $i$ 就是我们要选的 $x$ 。

复杂度 $O(n\log n)$

```cpp
#include <bits/stdc++.h>
using namespace std;
int T;
int n, dfn;
char c, s[300010];
int f[300010], cnt;
int judge(int x){
	for(int i = x; i <= n; i += x)
		if(f[i] == dfn) 
			return 0;
	return 1;
}
int main(){
	scanf("%d", &T);
	while(T--){
		cin >> n >> c;
		scanf("%s", s+1);
		cnt = 0; ++dfn;
		for(int i = 1; i <= n; ++i)
			if(s[i] != c){
				f[i] = dfn;
				cnt++;
			}
		if(!cnt){ puts("0"); continue; }
		int flag = 0, ans;
		for(int i = 2; i <= n; ++i)
			if(judge(i)){
				flag = 1;
				ans = i;
				break;
			}
		if(flag) printf("%d\n%d\n", 1, ans);
		else printf("%d\n%d %d\n", 2, n-1, n);
	}
	return 0;
}
```

---

## 作者：respect_lowsmile (赞：1)

这是一道思维题，但是思路并不难想，只要想到之后代码实现非常容易。

## solution
首先，比较容易想到最小的操作次数最多为 $ 2 $ ，因为当我们取 $ n $ 为操作数时，除了字符串的最后一位以外，其他的每一位都不是 $ n $ 的倍数，然后我们再取 $ n-1 $ 就能包括字符串的所有位，所以我们只需要考虑 $0 $ 和 $ 1 $ 的情况即可。

$ 0 $ 的情况比较好想，当字符串的每一位都等于当前字符时，不需要任何操作，重点就是 $ 1 $ 的情况，我们枚举每一个数的倍数所在的字符是否都等于要求字符，如果存在这样的数，那我们只需要操作除了这个数倍数之外的位置就行了，此时的操作数是 $ 1 $ 。
 
 ## code
 
 ```cpp
 /*
	date:2022.7.10
	worked by respect_lowsmile
*/
#include<iostream>
#include<cstring>
using namespace std;
const int N=3e5+5;
char s[N],ch;
int t,cnt,flag,arr;
inline int read()
{
   int s=0,w=1;char ch=getchar();
   while(ch<'0'||ch>'9')
   {  if(ch=='-')  w=-1;  ch=getchar();}
   while(ch>='0'&&ch<='9')
   {  s=s*10+ch-'0'; ch=getchar();}
   return s*w;
}
int main()
{
	t=read();
	while(t--)
	{
		arr=0,cnt=0;
		int n;
		n=read();
		scanf(" %c",&ch);
		scanf("%s",s+1);
		for(int i=1;i<=n;++i)
	  		if(s[i]==ch) cnt++;
	  	//cout<<s+1<<"  "<<ch<<"  "<<n<<"  "<<cnt<<endl;
		if(cnt==n)
		{
			printf("0\n");
			continue;
		}
		for(int i=1;i<=n;++i)
		{
			for(int j=i;j<=n;j+=i)
			{
				if(s[j]!=ch) flag=1;
				break;
			}
			if(flag==0)
			{
				arr=1;
				printf("1\n%d\n",i);
				break;
			}
		}
		if(arr==0) printf("2\n%d %d\n",n-1,n);
	}
	return 0;
}
```


---

## 作者：Yulin_Wu (赞：0)

本人的第一篇 CF 题解。

求过。


---

[题目传送门（CF1594C）](https://www.luogu.com.cn/problem/CF1594C)


---
# **思路**
所有为偶数的下标都不能被奇数 $x$ 整除。

同理，所有为奇数的下标都不能被偶数 $x$ 整除。

显然，答案只有 $0$，$1$，$2$。

那么题目就变得很简单了。

输入时统计不为 $c$ 的数量和下标。

如果数量为 $0$，直接返回 $0$。

否则就循环枚举 $x$，看能不能一次全部变成 $c$。

若可以直接输出 $1$ 和循环遍历到的 $x$。

若不可以，就输出 $2$ 和 $n$ 和 $n-1$。因为 $n$ 和 $n-1$ 一奇一偶，不管什么字符串都能成立。

个人认为这是一道比较简单的思维题，代码也比较简单。

应该算比较弱的黄题了。


---
# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
char s[30010], c;
long long n;
int main() 
{
    long long T; 
	cin >> T;
    while (T--)    //多组询问 
	{
        cin >> n >> c >> (s + 1);
        bool flag = 1;
        for (int i = 2; i <= n; i++) //判断是否初始时全一样 
        {
        	if(s[i] != s[i-1]) flag=0; 
        	break;
		}
        if (flag) cout << 0 << endl; //全一样就不用进行操作 
        else 
		{
            flag = 0;
            for (i = 2; i <= n; i++) //枚举x，看能否只用一步 
			{
                bool now = 1;                     
                for (int j = i; j <= n; j += ans) 
				{
					if (s[j] != c) 
					{
						now = 0; 
						break;
					}
				}
                if (now==1)
				{
					flag = 1; 
					break;
				}
            }
            if (flag) cout <<"1" << endl << ans << endl;
            else cout << "2" << endl << n - 1 << " " << n << endl;
        }
    }
    return 0;
}
```


---



完结撒花！！！

还是求过啊！！

---

## 作者：Walrus (赞：0)

## 题意
一共有 $t$ 组测试数据。

给定一个长度为 $n$ 的字符串 $s$，再给你一个字符 $c$，求你最少需要经过几次操作将整个字符串全部替换为字符 $c$。

注意：字符串 $s$ 的下标为 $s_1 \sim s_n$。

- 操作的定义如下：每次你可以选择一个数 $x$，将字符串 $s$ 中不能整除 $x$ 的下标对应的字符改为 $c$。

## 分析
不难发现，从定义出发，可以发现一些性质。

- 假设你选择的 $x$ 为 $n$，则它会将 $s_1 \sim s_{n-1}$ 均替换为 $c$。
- 假设你选择的 $x$ 为 $n-1$，则它会将 $s_1 \sim s_{n-2}$ 以及 $s_n$ 均替换为 $c$。

这里给出证明：

假设选择的 $x$ 为 $n$，则 $1\sim n-1$ 都**小于** $n$，所以 $i \bmod n =i(1 \leq i < n)$。

假设选择的 $x$ 为 $n-1$，则 $1\sim n-2$ 都**小于** $n-1$，所以 $i\bmod n-1=i(1\leq i <n-1)$。又因为 $\gcd(i,i+1)=1(i \geq1)$，所以 $n$ 一定不会被 $n-1$ 整除，所以我们如果选择一次 $n$ 和一次 $n-1$，是一定能将整个字符串变为 $c$ 的。所以答案 $0\leq ans \leq2$。

但是这里答案可不一定都为 $2$，还有两种情况需要特判。

- 如果原来的字符串 $s$ 的字符**全都是 $c$**，则不需要进行任何修改，输出 $0$。
- 枚举每一个 $i(1\leq i \leq n)$，若一次选择 $x=i$ 就可以使字符串 $s$ 的每一位都变成 $c$，也就是 $s$ 的每一个能整除 $i$ 的对应位置上的字符都是 $c$，如果可以，标记 $i$，答案也就是 $i$。

以上两种情况如果都不满足，则答案依然输出两行，第一行输出 $2$，第二行输出 $n-1$ 和 $n$，记得按格式输出。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 3e5 + 5; 
bool flag1;//标记原来的字符串的每一位上的字符是否全为 c
bool flag2;//标记原来的字符串的偶数位上的字符是否全为 c
bool flag3; 
int t, n;
char c, s[N];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin >> t;
	while(t--) {
		flag1 = flag2 = flag3 = 0;
		cin >> n >> c;
		for(int i = 1;i <= n;i++) {
			cin >> s[i];
			if(s[i] != c)
				flag1 = 1;
		}
		if(!flag1) {
			cout << '0' << '\n';
			continue;
		} 
		for(int i = 1;i <= n;i++) {
			flag2 = 0;
			for(int j = i;j <= n;j += i) {
				if(s[j] != c) {
					flag2 = 1;
					break;
				}
			}
			if(!flag2) {
				flag3 = 1;
				cout << '1' << '\n' << i << '\n';
				break;
			}
		}
		if(flag3)
			continue;
		cout << '2' << '\n' << n - 1 << ' ' << n << '\n';
	}
	return 0;
} 
```

---

## 作者：feicheng (赞：0)

## C:Make Them Equal

### Description

给长度为 $n$ 的字符串 $s$ 和一个字符 $c$，每次可以选择一个 $x$，使得不是 $x$ 的倍数的位置变成 $c$，问要使所有字母都变成 $c$ 至少需要几次操作。

**限制**：$3\le n\le 3\times 10^5$ 

### Solution

首先容易发现答案一定不会超过 $2$，因为可以选择 $n,n-1$，这样子所有的一定都变成 $c$ 了，接下来考虑答案小于 $2$ 的情况。

-  如果都是 $c$，那么次数为 $0$。

然后对于 $2\le i\le n$，每个检验一下能否使别的都变成 $c$。

### Code

```cpp
inline void solve() {
    cin >> n >> c >> (s + 1) ;
    int f = 0 ;
    for (int i = 1; i <= n; ++i) 
        if (s[i] != c) {
            f = 1;
            break ;
        }
    if (!f) 
        return cout << "0\n",void() ;
    for (int i = 2; i <= n; ++i) {
        int f = 0;
        for (int j = i; j <= n; j += i) {
            if (s[j] != c) {
                f = 1;
                break ;
            }
        }
        if (f == 0) 
            return cout << "1\n" << i << '\n',void() ;
    }
    cout << 2 << "\n" << n << " " << n - 1 << '\n';
}
```

---

## 作者：XL4453 (赞：0)

### 解题思路：

~~怎么这一场 Cofeforces 这么多构造题。~~

考虑构造。

初步分析，对于题目中的操作，一般往后选优秀的，而且一旦位置超过了 $\dfrac{n}{2}$ 就只有这个位置本身不会被替换了。

根据这个性质，珂以分为三种情况讨论：

1. 所有的字符都不需要替换，直接输出 $0$。

2. 只要一个操作就可以实现。这一个位置一定是在  $\dfrac{n}{2}+1$ 以及之后的位置上出现了至少一个不需要替换的字符。，那么直接选定这个位置就行了 

3. 如果上面两种情况都不能实现，那么就需要用两次操作了，理论上来讲，任意选两种位置在 $\dfrac{n}{2}+1$ 及以后的进行操作都是可以的，因为这两个位置都会把除了当前位置以外的所有位置都替换要求字符。这里为了方便，直接选用 $n-1$ 和 $n$。


---
### 代码：

```cpp
#include<cstdio>
#include<cmath>
using namespace std;
int T,n,tot;
char c,s[300005];
char get(){
	char a=getchar();
	while(a>'z'||a<'a')a=getchar();
	return a;
}
bool check(){
	for(int i=n/2+1;i<=n;i++){
		if(s[i]==c){
			printf("1\n%d\n",i);
			return 1;
		}
	}
	return 0;
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		c=get();
		tot=0;
		for(int i=1;i<=n;i++){
			s[i]=get();
			if(s[i]!=c)++tot;
		}
		if(tot==0){
			printf("0\n");
			continue;
		}
		if(check())continue;
		printf("2\n%d %d\n",n-1,n);
	}
	return 0;
}
```


---

## 作者：清烛 (赞：0)

## Description
$T$ 组数据，每次给定一个长度为 $n$ 的字符串（$3\le n\le 3\times 10^5$）和一个字符 $c$，要求执行以下操作使得整个字符串都变为 $c$，最小化操作次数并输出方案。

- 在 $[1, n]$ 中选定一个下标 $x$，对于所有 $x$ 不能整除的下标 $i$，将 $s_i$ 变成 $c$。

## Solution
简单思考一下，发现最差的情况，我们先执行 $x = n$，则 $[1, n - 1]$ 就被覆盖了，再执行 $x = n - 1$，则 $s_n$ 也会被覆盖。最多就操作两次。

那有没有可能只操作一次呢？当然是可以的，设这一次操作为 $x_0$，则这一次操作不能操作到的位置即所有的 $s_{kx_0}$ 都必须已经是 $c$。枚举 $x_0$ 并直接判 $x_0$ 的倍数即可，复杂度调和 $O(n\log n)$。

如果找不到这样的 $x_0$，那么说明必须操作两次。当然如果一开始字符串就全是 $c$，那么答案为 $0$。

## Implementation
```cpp
#include <iostream>
const int maxn = 3e5 + 5;
char s[maxn], c;
int n;

using namespace std;

int main() {
    int T; cin >> T;
    while (T--) {
        cin >> n >> c >> (s + 1);
        bool flag = 1;
        for (int i = 1; i <= n; ++i) flag &= (s[i] == c);
        if (flag) cout << 0 << endl;
        else {
            int ans;
            flag = 0;
            for (ans = 2; ans <= n; ++ans) {//枚举操作一次的情况
                bool now = 1;
                for (int j = ans; j <= n; j += ans) if (s[j] != c) {now = 0; break;}
                if (now) {flag = 1; break;}
            }
            if (flag) cout << 1 << endl << ans << endl;
            else cout << 2 << endl << n - 1 << ' ' << n << endl;
        }
    }
    return 0;
}
```

---

## 作者：vectorwyx (赞：0)

如果答案 $>=2$，先来一次 $x=n$ 再来一次 $x=n-1$ 一定可行。于是只需要判掉答案 $<2$ 的情况。

若  $s$ 已经满足条件，则答案为 $0$；否则把所有 $s_i\not=c$ 的 $i$ 拎出来存到桶里，如果存在一个 $x\in[1,n]$ 使得 $\forall s_i\not=c,x\nmid i$ 则答案为 $1$。对于 $[1,n]$ 中的每个数暴力跳倍数即可，复杂度是调和级数 $O(n\log n)$。

代码如下：
```cpp
#include<bits/stdc++.h>
#define fo(i,x,y) for(int i=x;i<=y;++i)
#define go(i,x,y) for(int i=x;i>=y;--i)
#define sml(x,y) x=min(x,y)
#define big(x,y) x=max(x,y)
#define mk make_pair
#define pb push_back
#define ll long long
#define db double
using namespace std;
inline void out(int *a,int l,int r){fo(i,l,r) printf("%d ",*(a+i));puts("");}
inline int read(){ int x=0,f=1; char ch=getchar(); while(!isdigit(ch)){ if(ch=='-') f=-1; ch=getchar(); } while(isdigit(ch)){ x=(x<<1)+(x<<3)+(ch^48); ch=getchar(); } return x*f; }

const int N=3e5+5;
int t[N];
char s[N];

int main(){
	int T=read();
	while(T--){
		int n=read(),flg=1;char c=getchar();
		scanf("%s",s+1);
		fo(i,1,n) if(s[i]!=c) flg=0;
		if(flg) puts("0");
		else{
			fo(i,1,n) t[i]=0;
			fo(i,1,n) if(s[i]!=c) t[i]=1;
			fo(i,1,n){
				flg=1;
				fo(j,1,n/i) if(t[i*j]) flg=0;
				if(flg){
					printf("1\n%d\n",i);
					goto H;
				}
			}
			printf("2\n%d %d\n",n,n-1);
			H:;
		}
	}
	return 0;
}

```


---

## 作者：reailikezhu (赞：0)

考虑对于这个东西有个很显然的结论就是最多会操作两次。

因为有一个两次操作的通解就是 $n,n-1$。这是显然的。

然后考虑如果一次都不用操作，那就是字符串中的所有字符都是目标字符，这个很简单。

然后再看能否只操作一次。

设 $yes_i$ 表示第 $i$ 位是否是目标字符。然后遍历所有已经是目标字符的位置，看它的所有的倍数是否也是目标字符，如果是，那么只需要一次操作，操作 $i$ 位置。

否则如果所有的都不满足，那就操作两次，可以用通解 $n,n-1$。

```cpp
#include<stdio.h>
#include<string.h>
#include<iostream>

int t;
int n;
char c;
char s[300010];
bool yes[300010];

int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		std::cin>>c;
		scanf("%s",s+1);
		for(int i=1;i<=n;i++) yes[i]=0;
		bool flag=0;
		for(int i=1;i<=n;i++){
			if(s[i]!=c) flag=1;
			else yes[i]=1;
		}
		if(!flag){
			printf("0\n");
			continue;
		}
		bool flag1=0;
		for(int i=2;i<=n;i++){
			if(yes[i]==1){
				bool flag2=0;
				for(int j=i+i;j<=n;j+=i){
					if(!yes[j]){
						flag2=1;
						break;
					}
				}
				if(!flag2){
					flag1=1;
					printf("1\n%d\n",i);
					break;
				}
			}
		}
		if(!flag1) printf("2\n%d %d\n",n,n-1);
	}
	return 0;
}
```

---

## 作者：WitheredZeal (赞：0)

## 题意  

有一个字符串 $s$（下标从 $1$ 开始） 和一个字符 $c$，你希望用若干次操作使得 $s$ 中的字符全部变成 $c$，每次操作过程如下：  
- 选择一个数 $1 \le x \le n$。  
- 将 $s$ 中所有下标**不**被 $x$ 整除的字符替换成 $c$。

你需要最小化操作数，并给出构造。

## 题解  

首先一个结论，就是答案 $\le 2$。  
因为我们可以选择 $n$ 和 $n-1$。选择 $n$ 之后最多只有 $n$ 还不是 $c$，因为 $n \ge 3$ 所以选择 $n-1$ 就可以使得 $n$ 被消掉。  
那么只需检查一次操作行不行。我们直接枚举 $x$，然后看看是否合法。这个可以在 $O(\dfrac{n}{x})$ 的时间做到，总复杂度是 $n \log n$。  

## 代码

```cpp
void DOIT()
{
	ans=cnt=0;
	rd(n);c=getchar();scanf("%s",s+1);for (int i=1;i<=n;i++) v[i]=0;
	for (int i=1;i<=n;i++) if (s[i]!=c) v[i]=1,ans++;
	if (ans==0) {puts("0");return;}
	for (int i=1;i<=n;i++)
	{
		cnt=0;
		for (int j=i;j<=n;j+=i) if (v[j]) cnt++;
		if (cnt==0) {puts("1");cout<<i<<"\n";return;}
	}
	puts("2");
	cout<<n-1<<" "<<n<<endl;
}
```

---

