# Simply Emirp

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=14&page=show_problem&problem=1176

[PDF](https://uva.onlinejudge.org/external/102/p10235.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10235/b3b8ea0ca3590b5800fc5123b088be54c52be882.png)

## 样例 #1

### 输入

```
17
18
19
179
199```

### 输出

```
17 is emirp.
18 is not prime.
19 is prime.
179 is emirp.
199 is emirp.```

# 题解

## 作者：BqtMtsZDnlpsT (赞：5)

传送门[UVA10235 Simply Emirp](https://www.luogu.com.cn/problem/UVA10235)

题意简述：
- 如果一个质数（`prime`），它翻转后还是质数（翻转就是 $1234\rightarrow 4321$），则把它称为（`emirp`）。
- 现在给你一个整数 $n$，请判断它是否是 `emirp`
	- 若是，输出 `n is emirp.`。
    - 若不是 `emirp`，但是是质数，输出`n is prime.`。
    - 否则，输出 `n is not prime.`。

思路：
- $1<n<10^6$ 所以使用线性筛。
- 筛完后使用判断是否是质数的布尔数组来判断，把查找复杂度降为 $O(1)$。
- 每个 $n$ 进行翻转判断，注意先判断不是质数的情况。
- 注意类似 $2\rightarrow2$，$11\rightarrow11$ 的回文数不是`emirp`。

代码：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<algorithm>
using namespace std;
int p[100005],t;
bool q[1000005];
void P(int u)//线性筛
{
	q[0]=q[1]=1;
	for(int i=1;i<=u;i++)
	{
		if(!q[i])p[++t]=i;
		for(int j=1;j<=t&&i*p[j]<=u;j++)
		{
			q[i*p[j]]=1;
			if(!(i%p[j]))break;
		}
	}
}
int K(int u)//翻转
{
	int x=u,s=0;
	while(x)s*=10,s+=x%10,x/=10;
	return s;
}
int main()
{
	int n;
	P(1000000);
	while(scanf("%d",&n)!=EOF)
	{
		if(q[n])printf("%d is not prime.",n);
		else if(!q[K(n)]&&n!=K(n))printf("%d is emirp.",n);//注意不是回文数
		else printf("%d is prime.",n);
		puts("");
	}
	return 0;
}
```
附：
- #### 	线性筛（欧拉筛）
	- 埃氏筛 ：时间复杂度 $O(n\;\log\;\log \;n)$
      
      从 $2$ 开始，将每个质数的倍数都标记成合数，以达到筛选素数的目的。

	- 线性筛（欧拉筛） ：时间复杂度 $O(n)$
    
      在埃氏筛的基础上，让每个合数只被它的最小质因子筛选一次，以达到不重复的目的。

---

## 作者：saixingzhe (赞：1)

# 题意
输入一个数 $n$，如果 $n$ 与其翻转后的数都是质数，那么 $n$ 是一个 `emirp`；如果 $n$ 是质数且其翻转后的数不是质数，那么 $n$ 是一个 `prime`；否则 $n$ 就是 `not prime`。

# 分析

直接用埃式筛筛出所有的质数，然后求每个数的相反数，按题意判断即可。

**坑点：回文数不是 `emirp`。**

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a;
bool pri[1000005]; 
int main(){
	for(long long i=2;i<=1000000;i++)
		if(!pri[i]) for(long long j=i*i;j<=1000000;j+=i) pri[j]=1;
	while(cin>>a){
		if(pri[a]) printf("%d is not prime.\n",a);
		else{
			int s=a,c=0;
			while(a){
				c=c*10+a%10;
				a/=10;
			}
			if(!pri[c]&&s!=c) printf("%d is emirp.\n",s);
			else printf("%d is prime.\n",s);
		}
	}
	return 0;
}
```

---

## 作者：guozhetao (赞：1)

看到大佬写了一篇线性筛[题解](https://www.luogu.com.cn/blog/cjnFreedomKingblog/solution-uva10235)。本蒟蒻就补充了一篇埃氏筛的。

## 题意

如果一个质数（`prime`），它翻转后还是质数（翻转就是 $1234 \rightarrow 4321$），则把它称为（`emirp`）。
现在给你一个整数 $n$，请判断它是否是 `emirp`。

若是，输出 `n is emirp.`。

若不是 `emirp`，但是是质数，输出 `n is prime.`。

否则，输出 `n is not prime.`。

## 思路

就先用埃氏筛筛出 $1000000$ 以内的质数，再判断翻转后是否为质数，最后输出。我们可以用一个布尔数组来春每个数是否为质数。

## 注意

回文质数不是 `emirp`。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a;
bool v[1000005];//在本篇题解中0为是，1为不是
int main() {
	//freopen("checkin.txt","r",stdin);
	//freopen("checkout1.txt","w",stdout);
	v[1] = 1;
	v[0] = 0;
    //埃氏筛
	for(long long i = 2;i <= 1000000;i++) {
		if(v[i]) {
			continue;
		}
		for(long long j = i * i;j <= 1000000;j += i) {
			v[j] = 1;
		}
	}
    //输入输出
	while(cin>>a) {
		if(v[a]) {
			printf("%d is not prime.\n",a);
		}
		else{
			int b = a;
			int c = 0;
			while(b) {
				c *= 10;
				c += b % 10;
				b /= 10;
			}
			if(!v[c] and a != c) {
				printf("%d is emirp.\n",a);
			}
			else{
				printf("%d is prime.\n",a);
			}
		}
	}
}

```


---

## 作者：SnapYust (赞：0)

## 题目传送门

[Simply Emirp](https://www.luogu.com.cn/problem/UVA10235)

没有翻译，反正打 AtCoder 习惯了。

## 思路

首先我们要会质数筛，不会的可以 baidu 或 csdn 去学一下，不难，也可以理解一下以下代码：

```cpp
inline void init()
{
    for (int i = 2; i <= m; i++)
    {
        if (!mark[i]) prime[++cnt] = i;
        for (int j = 1; j <= cnt && i * prime[j] <= m; j++)
        {
            mark[i * prime[j]] = 1;
            if (i % prime[j] == 0) break;
        }
    }
}
```
这个函数可以筛出从 $1$ 到 $m$ 的质数，$cnt$ 存的是质数总个数，$prime$ 是质数数组，$mark$ 可以用来判断 $i$ 是不是质数。

正确地，若 $mark_i=1$，则 $i$ 不是质数，反之亦然。

然后我们还要学会翻转数字，以下程序：

```cpp
inline void re(int x)
{
    int ct = 0, a[10], k = 0;
    while (x)
    {
        a[++ct] = x % 10;
        x /= 10;
    }
    for (int i = 1; i <= ct; i++)
        k *= 10, k += a[i];
}
```
处理完后 $k$ 即为 $x$ 的翻转数。

然后这道题就做完了，时间复杂度 $O(m+q\sum\text{len}(n_i))$

## Code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n, m = 1000000, cnt = 0, prime[1000005];
bool mark[1000005] = {0};

inline void init()
{
    for (int i = 2; i <= m; i++)
    {
        if (!mark[i]) prime[++cnt] = i;
        for (int j = 1; j <= cnt && i * prime[j] <= m; j++)
        {
            mark[i * prime[j]] = 1;
            if (i % prime[j] == 0) break;
        }
    }
}

inline bool check(int x)
{
    int ct = 0, a[10], k = 0;
    while (x)
    {
        a[++ct] = x % 10;
        x /= 10;
    }
    for (int i = 1; i <= ct; i++)
        k *= 10, k += a[i];
    if (mark[k]) return 0;
    return 1;
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    init();
    while (cin >> n)
    {
        if (mark[n]) cout << n << " is not prime." << endl;
        else
        {
            if (!check(n)) cout << n << " is prime." << endl;
            else cout << n << " is emirp." << endl;
        }
    }
    return 0;
}
```


---

## 作者：Elairin176 (赞：0)

[传送门](https://www.luogu.com.cn/problem/UVA10235)      
水题。    
我们先筛出 $1$ 到 $10^6$ 之间的所有素数，再对每一个输入的数据进行判断：   
- 如果是合数，输出 `x is not prime.`。    
- 如果是质数，并且把它反转过来也是质数，两个数不相等就输出 `x is emirp.`。    
- 否则输出 `x is prime.`。     
CODE：   
```cpp
#include <iostream>
using namespace std;
int n,prime[1000001],ps,r;
bool b[1000001];
void init(){//线性筛
	for(int i=2;i<=1000000;i++){
		if(!b[i]){
			prime[++ps]=i;
		}
		for(int j=1;j<=ps&&i*prime[j]<=1000000;j++){
			b[i*prime[j]]=true;
			if(i%prime[j]==0){
				break;
			}
		}
	}
}
int rev(int x){//反转数字
	int ans=0;
	while(x){
		ans*=10;
		ans+=x%10;
		x/=10;
	}
	return ans;
}
int main(void){
	init();
	while(~scanf("%d",&n)){
		r=rev(n);
		if(b[n]){//是合数
			printf("%d is not prime.\n",n);
		}else if((!b[n])&&(!b[r])&&(n!=r)){//emirp的情况
			printf("%d is emirp.\n",n);
		}else{//否则肯定为质数
			printf("%d is prime.\n",n);
		}
	}
}
```


---

## 作者：zesqwq (赞：0)

# UVA10235 Simply Emirp 题解

[题目传送门](https://www.luogu.com.cn/problem/UVA10235)

在其它题解中，几乎都提到了质数可以用筛法筛出，本篇题解中就不讲解此部分内容，但是实际上一个数反过来读是啥也可以用类似于筛的方法求出来！

首先，所有一位数反过来读还是它本身。

然后我们引入 $2$ 个数组，我们用 $inv_i$ 表示 $i$ 反过来读的值，用 $len_i$ 表示一个数的位数。

那么对于所有 $i \geq 10,len_i = len_{\lfloor i/10 \rfloor} + 1$。然后考虑如何反转一个数。比若说 $54321$ 其实就是在 $5432$ 的反转的值 $2345$ 开头添了一个 $1$。也就是对于 $i \geq 10,inv_i = inv_{\lfloor i/10 \rfloor} + (i \bmod 10) \times 10^{len_i}$。然后预处理 $10$ 的 $x$ 次方就可以递推出 $inv$ 数组力。

然后这题再加一个素数筛就 $\text{AC}$ 了。

$\text{Code:}$

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 10;
int prime[N], cnt, rev[N], len[N], pw[N];
bool vis[N];
void sieve(int n) {
    for (int i = 0; i <= 9; i++) rev[i] = i;
    for (int i = 10; i <= n; i++) len[i] = len[i / 10] + 1;
    pw[0] = 1;
    for (int i = 1; i <= len[n]; i++) pw[i] = pw[i - 1] * 10;
    for (int i = 10; i <= n; i++) rev[i] = rev[i / 10] + i % 10 * pw[len[i]];
    vis[1] = 1;
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) prime[++cnt] = i;
        for (int j = 1; j <= cnt && i * prime[j] <= n; j++) {
            vis[i * prime[j]] = 1;
            if (i % prime[j] == 0) break;
        }
    }
}
int main() {
    sieve(1000000);
    int n;
    while (~scanf("%d", &n)) {
        if (vis[n]) {
            printf("%d is not prime.\n", n);
            continue;
        }
        if (rev[n] == n || vis[rev[n]])
            printf("%d is prime.\n", n);
        else
            printf("%d is emirp.\n", n);
    }
    return 0;
}
```

---

## 作者：xmkevin (赞：0)

## part 1 题目大意

如果一个数 $n$ 是素数，并且 $n$ 反过来也是素数，那么称这个数为“emirp”。

现在输入一个数 $n$，如果它符合上面说的条件，输出 `n is emirp.`；

如果 $n$ 是素数但是它翻转后不是素数，那么输出 `n is prime.`；

如果 $n$ 不是素数，那么输出 `n is not prime.`。

## part 2 方法

首先，因为 $1 \le n \le 1000000$，所以如果使用常规因数判断法，必定T飞。

所以，我们可以用埃氏筛来解决这道题。

具体思路：

- $1$. 把 $1$ ~ $10000000$ 的所有数筛一遍，判断是否是素数。

- $2$. 把 $n$ 反过来，按照题目中的要求判断。

P.S.:回文质数不算emirp。

## part 3 代码(含注释)：

```cpp
#include <iostream>
using namespace std;
typedef long long ll;
ll a, n;
bool vis[1000005];

int main() {
	vis[0] = 0, vis[1] = 1;
	for(long long i = 2; i <= 1000000; i++) {//素数筛
		if(vis[i] != 0) continue;//已经被筛
		for(long long j = i * i; j <= 1000000; j += i) {//把这个素数的倍数筛掉
			vis[j] = 1;
		}
	}
	while(cin >> n) {
		if(vis[n] == 1) {
			cout << n << " is not prime.\n";//不是素数
		} else {
			long long tmp = n;
			long long m = 0;
			while(tmp > 0) {
				m = m * 10 + tmp % 10;
				tmp /= 10;
			}//反转
			if(vis[m] == 0 && n != m) {
				cout << n <<" is emirp.\n";//翻转后还是素数
			} else {
				cout << n << " is prime.\n";//素数
			}
		}
	}
}
```

---

## 作者：cmk666 (赞：0)

[题目链接](/problem/UVA10235)

~~怎么其它题解都喜欢筛啊~~

题目大意：定义 Emirp 为「从右往左读与本身不同且仍是质数」的质数，判断 $n$ 是否是质数或 Emirp。

直接根据定义做即可。用 $O(\sqrt n)$ 的时间复杂度检验一个数是否是质数：
```cpp
inline bool isprime(int x)
{
	for ( int i = 2 ; i * i <= x ; i++ ) if ( !( x % i ) ) return false;
	return true;
} // 这里没有判 1，但题面说了 n>1，因此没关系
```
再写一个 $O(\log n)$ 反转一个数的函数：
```cpp
inline int rev(int x)
{
	int y = 0;
	while ( x ) y = y * 10 + x % 10, x /= 10;
	return y;
}
```
然后就顺着题面的意思写即可。注意反过来与原数相同的数不是 Emirp，判断一下即可。剩余核心代码如下：
```cpp
int n;
int main()
{
	while ( scanf("%d", &n) != EOF )
		if ( isprime(n) )
			if ( rev(n) != n && isprime(rev(n)) )
				printf("%d is emirp.\n", n);
			else printf("%d is prime.\n", n);
		else printf("%d is not prime.\n", n);
	return 0;
}
```

---

