# Taisia and Dice

## 题目描述

Taisia has $ n $ six-sided dice. Each face of the die is marked with a number from $ 1 $ to $ 6 $ , each number from $ 1 $ to $ 6 $ is used once.

Taisia rolls all $ n $ dice at the same time and gets a sequence of values $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 6 $ ), where $ a_i $ is the value on the upper face of the $ i $ -th dice. The sum of this sequence is equal to $ s $ .

Suddenly, Taisia's pet cat steals exactly one dice with maximum value $ a_i $ and calculates the sum of the values on the remaining $ n-1 $ dice, which is equal to $ r $ .

You only know the number of dice $ n $ and the values of $ s $ , $ r $ . Restore a possible sequence $ a $ that fulfills the constraints.

## 样例 #1

### 输入

```
7
2 2 1
2 4 2
4 9 5
5 17 11
3 15 10
4 4 3
5 20 15```

### 输出

```
1 1
2 2 
1 2 2 4
6 4 2 3 2
5 5 5
1 1 1 1
1 4 5 5 5```

# 题解

## 作者：__Allen_123__ (赞：7)

### 题意简述

- 有 $n$ 个六面骰子，其中第 $i$ 个骰子的点数为 $a_i$，这 $n$ 个骰子的点数之和为 $s$。
- 拿走一个点数最大的骰子，剩余 $n-1$ 个骰子的点数之和为 $r$。
- 给定 $n, s, r$，请输出任意一个可能的序列 $a$。
- 本题有 $t$ 组数据。
- $1\le t\le 1000, 2\le n \le 50, 1\le a_i\le 6, 1\le r < s \le 300$。

### 题目分析

我们拿走了一个点数最大的骰子，拿走之前点数之和为 $s$，拿走之后点数之和为 $r$，那么很明显地，这个骰子的点数就为 $s-r$，由于我们可以输出任意一个序列，所以可以首先输出 $s-r$。

那么如何输出剩下的 $n-1$ 个骰子呢？

我们可以尝试将点数平均分配到每一个骰子上，防止 $a_i$ 越界。首先，我们应该计算出 $\lfloor \frac{r}{n-1} \rfloor$ 的值，表示这 $n-1$ 个骰子的点数之和除以 $n-1$ 向下取整后的结果，那么假如我们输出了 $n-1$ 个这个值，点数之和就与 $r$ 相差 $r \bmod (n -1)$ 的结果（因为 $r-\lfloor \frac{r}{n-1} \rfloor \times (n-1)=r \bmod (n-1)$）。为了让这 $n-1$ 个骰子的点数之和刚好等于 $r$，我们就应该将其中 $r \bmod (n-1)$ 个骰子的点数加上 $1$，最后直接输出即可。

其他的小细节在代码注释内。

### 代码

```cpp
/*
 * Author: Allen_123
 * Name: CF1790B
 * Time: 2023/1/27
 * Lang: C++11
 */
#include <bits/stdc++.h>
using namespace std;
int t, n, r, s;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> t;
	while(t--){
		cin >> n >> s >> r;
		cout << s - r << " "; // 输出被拿走的那个骰子的点数
		n--; // n 在这里已经减 1，所以下一行计算不需要再让 n 减 1
		int av = r / n, num = r % n; // 计算平均值，和需要输出多少个比平均值多 1 的数
		for(int i = 1;i <= num;i++){ // 先输出 r % n 个平均值 + 1
			cout << av + 1 << " ";
		}
		for(int i = num + 1;i <= n;i++){ // 剩下的直接输出平均值即可
			cout << av << " ";
		}
		cout << "\n";
	}
	return 0;
}
```

---

## 作者：LegendaryGrandmaster (赞：4)

因为取走**一个**最大数后所有数的和都为 $r$ 了，而原本所有数的和为 $s$，所以最大数的值为 $s-r$。

除去**一个**最大值后，剩余的我们只需要跟剩余的数量 $n-1$ 均分即可。

但是不一定会正好整除，所以先把最后多出的值给最后一个数，如果大于最大值了，再依次分配给前面的几个数。

代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[1001];
int main()
{
	int t;
	cin>>t;
	while(t--){
		memset(a,0,sizeof(a));
		int n,s,r;
		cin>>n>>s>>r;
		int c=s-r;
		a[1]=c;
		n--;
		s-=c;
		for(int i=2;i<=n+1;i++){
			if(i==n+1&&s%n)a[i]=s/n+s%n;
			else a[i]=s/n;
		}
		int ans=a[n+1]-c,x=2;
		while(ans>0){
			a[n+1]--;
			ans--;
			a[x]++;
			x++;
			if(x>n+1)x=1;
		}
		for(int i=1;i<=n+1;i++)cout<<a[i]<<' ';
		puts("");
	}
}
```

---

## 作者：2011qiqi (赞：4)

### 题意：

有 $n$ 个数组，每个数有 $a_1,a_2,...,a_6$，然后从这 $n$ 个数组中，每个数组各选一个数，选出的这些数和是 $s$，去掉选出的最大值的和是 $r$。

让你求出这组选出的数，满足上面的条件即可。

---

### 思路：

首先考虑最大值，不难想出，最大值就是 $s-r$，所以先输出最大值。然后再考虑接下来的数，一定得小于等于最大值，数据保证一定存在，不拿相出剩下的数可以平均分，如果平均分没有余数，就输出 $n-1$ 个平均数。否则再从第一个开始把余数加上去。

还有一个就是，余数一定小于除数，所以不用判断是否要从头再来一轮。

### Code:

```cpp
#include<bits/stdc++.h>

using namespace std;

// ```
#define clog cout
#define plog printf
#define jd static
#define PII pair<int, int>
#define PLL pair<long long, long long>
#define M make_pair
#define x first
#define y second
#define E emplace
#define EB emplace_back
#define EF emplace_front
#define p putchar
// 小写p
#define re register
#define P printf(" ");
// 大写P
#define endl puts("")
#define Yes puts("Yes")
#define No puts("No")
#define YES puts("YES")
#define NO puts("NO")
#define error puts("error")
#define IMPOSSIBLE puts("IMPOSSIBLE")
#define Impossible puts("Impossible")
#define fuyi puts("-1")
#define ll long long
#define ull unsigned long long
// ```

// ```函数
inline int gcd(int a,int b){
    if(b) while((a%=b) && (b%=a));
    return a+b;
}

inline int read(){
	re int x=0,f=1;re char ch=getchar();
	while(!isdigit(ch)){if(ch=='-') f=~f+1;ch=getchar();}
	while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return x*f;
}


inline short read_s(){
	re short x=0,f=1;re char ch=getchar();
	while(!isdigit(ch)){if(ch=='-') f=~f+1;ch=getchar();}
	while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return x*f;
}

inline ll read_ll(){
	re ll x=0,f=1;re char ch=getchar();
	while(!isdigit(ch)){if(ch=='-') f=~f+1;ch=getchar();}
	while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return x*f;
}

inline ull read_ull(){
	re ull x=0,f=1;re char ch=getchar();
	while(!isdigit(ch)){if(ch=='-') f=~f+1;ch=getchar();}
	while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return x*f;
}

inline unsigned int read_u(){
	re unsigned int x=0,f=1;re char ch=getchar();
	while(!isdigit(ch)){if(ch=='-') f=~f+1;ch=getchar();}
	while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return x*f;
}

inline void print(ll x){
    jd ll b[40],top=0;
	if(x<0) p('-'),x=~x+1;
	while(x) b[++top]=x%10,x/=10;
	if(!top) b[++top]=0;
	while(top) p(b[top--]^48);
	P;   
}
// ```

inline void solve(){    
    re int n=read(),s=read(),r=read(),maxx=s-r,i;
    print(maxx);
    re int pj=(s-maxx)/(n-1);
    if(pj*(n-1)==(s-maxx)){// 如果没有余数就全输出平均数
    	while(--n) print(pj);
    	endl;
	}else{
		re int cha=(s-maxx)-pj*(n-1);// 余数
		vector<int> v;
		for(i=0;i<n-1;++i) v.EB(pj);
		i=0;
		while(cha>0){
			++v[i++];
			--cha;
		}
		for(i=0;i<n-1;++i) print(v[i]);
		endl;
	}
	return ;
}

int main(){
    re int t=read();                                                                                                                         
    while(t--) solve();
	return 0;
}
```

---

## 作者：Kevin_Mamba (赞：1)

### 题意

有一个长度为 $n$ 的数组 $a$，第 $i$ 个数为 $a_i(1\le a_i\le6)$。

设 $b=\max\limits_{i=1}^na_i$。

给定 $s=\sum\limits_{i=1}^na_i,r=s-b$。

请构造一组合法的 $a$，**数据保证有解**，以任意顺序输出任意一组方案即可。

### 解析

已经知道了 $a_1=b=s-r$。只需要求剩下的 $n-1$ 个数即可。

设 $aver=\lfloor \frac{r}{n-1} \rfloor,left=r \bmod (n-1)$。

因为保证有解，所以 $aver\le b$。

若不是这样，$n-1$ 个数中必定会有大于 $b$ 的，就会无解。

我们就考虑将 $left$ 分配给 $n-1$ 个数，使每个数都不能超过 $b$。

就可以循环，每次从 $left$ 中尽量取大的值 $v(v=\min(left,b-aver))$，直到取完。每次输出 $aver+v$ 即可。

### 代码

```
#include<bits/stdc++.h>
#define il inline
#define re register
using namespace std;

int main() {
	int t;
	scanf("%d",&t);
	while(t--) {
		re int n,s,r;
		scanf("%d%d%d",&n,&s,&r);
		re int b=s-r;
		printf("%d ",b);
		re int aver=(r)/(n-1),left=(r)%(n-1);
		for(re int i=2;i<=n;i++) {
			re int v=min(left,b-aver);
			left-=v;
			printf("%d ",aver+v);
		}
		putchar('\n');
	}
	return 0;
}
```

---

## 作者：minVan (赞：1)

**题目大意**

有一个长度为 $n$ 的数列 $a$，所有数的和为 $s$，去掉最大值后，所有数的和为 $r$，让你还原 $a$。

**解题思路**

首先最大的就是 $r-s$，然后其余的每个数赋值为 $[r\div(n-1)]$，最后任给 $r\bmod(n-1)$ 个人加 $1$。

**AC 代码，请勿抄袭**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 55;
int a[N];
int main() {
    int t;
    cin >> t;
    while(t--) {
        memset(a, 0, sizeof(a));
        int n, s, r;
        cin >> n >> s >> r;
        cout << s - r << ' ';
        for(int i = 1; i <= n - 1; i++) {
            a[i] = r / (n - 1);
        }
        for(int i = 1; i <= r % (n - 1); i++) {
            ++a[i];
        }
        for(int i = 1; i <= n - 1; i++) {
            cout << a[i] << ' ';
        }
        cout << '\n';
    }
    return 0;
}
```

---

## 作者：arrow_king (赞：0)

## 简化题意

给定三个变量 $n,s,r$，构造一个长度为 $n$ 的序列 $a_1,a_2,\dots,a_n$，使得 $\forall 1\le i\le n$，$1\le a_i\le6$，并且 $\sum\limits_{i=1}^{n}a_i=s$，$\max\{a_i\}=s-r$。

数据保证答案存在，$2\le n\le50$，$1\le r<s\le300$。

## 思路

首先这个骰子序列的最大值是可求的，为 $s-r$。

~~那不就好办了吗~~

接下来只要构造使得剩下的 $n-1$ 个元素的和等于 $r$ 就行了，让 $r\bmod (n-1)$ 个元素的值为 $\left\lceil \dfrac{r}{n-1}\right\rceil$，剩下的元素为 $\left\lfloor \dfrac{r}{n-1}\right\rfloor$ 就可以了。可以发现总和一定等于 $r$。

## 代码

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
#define ll long long
#define il inline
il ll read() {
	ll x=0,f=1;char c=getchar();
	while(c<'0'||c>'9') {if(c=='-') {f=-1;} c=getchar();}
	while(c>='0'&&c<='9') {x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x*f;
}
int t,n,s,r;
int main() {
	t=read();
	while(t--) {
		n=read(),s=read(),r=read();
		int maxn=s-r;
		printf("%d ",maxn);
		int p=r/(n-1);
		int q=r-p*(n-1);
		if(p==maxn&&q==0) for(int i=1;i<n;i++) printf("%d ",maxn);
		else {
			for(int i=1;i<=q;i++) printf("%d ",p+1);
			for(int i=q+1;i<n;i++) printf("%d ",p);
		}
		putchar('\n');
	}
	return 0;
}
```

---

