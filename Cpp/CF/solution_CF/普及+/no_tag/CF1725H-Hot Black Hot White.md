# Hot Black Hot White

## 题目描述

#### 题目大意
Dr. Chanek 有 $n$ 块魔法石，编号为 $1$ 至 $n$。第 Dr. Chanek 有 $n$ 块魔法石，编号为 $1$ 至 $n$。第 $i$ 块魔法石拥有 $a_i$ 的力量。Dr. Chanek 需要将 $n$ 块魔法石中的 $\frac{n}{2}$ 块染成黑色，另外 $\frac{n}{2}$ 块染成白色。

当第 $i$ 块魔法石和第 $j$ 块魔法石同时满足以下两个条件时，它们就会发生反应：

1. $color_i \ne color_j$（即两块石头颜色不同）

2. $\text{concat}(a_i,a_j) \times \text{concat}(a_j,a_i) + a_i \times a_j \equiv Z \mod 3$（即 $(\text{concat}(a_i,a_j) \times \text{concat}(a_j,a_i) + a_i \times a_j) \mod 3 = Z \mod 3$）

其中 $\text{concat}(x,y)$ 表示将十进制下的 $x$ 接在十进制下的 $y$ 的左边形成的新十进制数。例如，$\text{concat}(10,24) = 1024$。

因为魔法石发生反应时会很热很危险，所以你需要确定 $Z$ 的值和魔法石的染色方案，使任意一对魔法石之间都不产生反应。

## 样例 #1

### 输入

```
4
4 10 9 14```

### 输出

```
0
1001```

# 题解

## 作者：_•́へ•́╬_ (赞：7)

## 思路

$10\mod 3=1$，所以 $a\times 10+b\equiv a+b\pmod 3$，所以 $\operatorname{concat}(a,b)\equiv a+b\pmod 3$.

于是那一长串式子
$$
\operatorname{cancat}(A_i,A_j)\times\operatorname{concat}(A_j,A_i)+A_i\times A_j
$$

可以变成酱紫：
$$
(A_i+A_j)^2+A_i\times A_j
$$

研究 $A_i\%3$ 和 $A_j\%3$ 取所有可能取值时上面那个式子的值：

|       | **0** | **1** | **2** |
| :---: | :---: | :---: | :---: |
| **0** |   0   |   1   |   1   |
| **1** |   1   |   2   |   2   |
| **2** |   1   |   2   |   2   |

题目要求我们避开 $z$。

当 $A\%3$ 中的 $0$ 足够少时，我们吧 $0$ 都放在一组，这样运算之后就绝对不会出现 $0$。

当 $A\%3$ 中的 $0$ 足够多时，我们吧 $0$ 放满一组，这样运算之后就绝对不会出现 $2$。

## code

```cpp
#include<stdio.h>
#define N 100000
inline char nc()
{
	static char buf[99999],*l,*r;
	return l==r&&(r=(l=buf)+fread(buf,1,99999,stdin),l==r)?EOF:*l++;
}
inline void read(int&x)
{
	char c=nc();for(;c<'0'||'9'<c;c=nc());
	for(x=0;'0'<=c&&c<='9';x=(x<<3)+(x<<1)+(c^48),c=nc());
}
int n,a[N],cnt[3];
main()
{
	read(n);
	for(int i=0;i<n;read(a[i]),++cnt[a[i++]%3]);
	if(cnt[0]>n>>1)
	{
		printf("2\n");
		for(int i=0,j=n>>1;i<n;++i)
			if(!(a[i]%3))//【注意】
				if(j)putchar('0'),--j;
				else putchar('1');
			else putchar('1');
	}
	else
	{
		printf("0\n");
		for(int i=0,j=(n>>1)-cnt[0];i<n;++i)
			if(a[i]%3)
				if(j)putchar('0'),--j;
				else putchar('1');
			else putchar('0');
	}
}
/*     0     1    2
 *0    0     1    1
 *1    1     2    2
 *2    1     2    2
 */
```

标【注意】的那个地方，原来我漏加括号了，居然过了，但是赛时修改 checker 并重测吧我毙了。。。

---

## 作者：yingkeqian9217 (赞：4)

## 前言

还是比较简单的一道绿题，~~啥也不考验~~考验数学水平（？

## 分析

不难发现，根据 $\bmod 3$ 的性质（数位和），我们显然可以对产生反应的式子进行简化，具体来说，就是：

$\text{concat}(a_i,a_j) \times \text{concat}(a_j,a_i) + a_i \times a_j \equiv Z \bmod 3$

$\iff (a_i + a_j) \times (a_j + a_i) + a_i \times a_j \equiv Z \bmod 3$（数位和的性质）

$\iff (a_i + a_j)^2 + a_i \times a_j \equiv Z \bmod 3$

$\iff a_i^2 + a_j^2 + 3\times a_i\times  a_j \equiv Z \bmod 3$

$\iff a_i^2 + a_j^2 \equiv Z \bmod 3$

显然，我们只需要维护每个数 $x^2\bmod 3$ 的值即可。根据平方和的性质，我们会发现 $x^2\bmod 3\in [0,1]$。于是问题变成了：有 $n$ 个 01 数，要把它们分成相等的两堆，使得从两堆中任意各取一个，得到的和的情况 $\le 2$ 种（因为要存在一个合法的 Z）。

而情况数最少，肯定要有一堆全为一个数，那就是数量多的那个。不妨设多的那个是 0，那么另一堆就是全部的 1，加上部分的 0，和只能取到 0 或 1，Z 取 2 即可。1也是一样的，在此不再赘述。

```cpp
#include<bits/stdc++.h>
#define maxn 2900001
using namespace std;
int n,a[maxn],t[maxn],col[maxn];
signed main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		int x=0;
		while(a[i]) x+=a[i]%10,a[i]/=10;
		a[i]=x;//记录数位和
		t[(a[i]*a[i])%3]++;//记录0和1的个数
		col[i]=(a[i]*a[i])%3;//标记它是哪一种
	}
	if(t[0]>t[1]){//分讨
		printf("%d\n",2);
		int cnt=n/2-t[1];
		for(int i=1;i<=n;i++)
		 if(!col[i]&&cnt)
		  col[i]=1,cnt--;//将多余部分的1染为0即可
	}
	else{
		printf("%d\n",0);//同理
		int cnt=n/2-t[0];
		for(int i=1;i<=n;i++)
		 if(col[i]==1&&cnt)
		  col[i]=0,cnt--;
	}
	for(int i=1;i<=n;i++)
	 printf("%d",col[i]);//这里我把两种放在一起输出了
	return 0;
}
```

---

## 作者：FiraCode (赞：0)

考虑将 $a$ 和 $b$ 拼起来其实就是 $a \times 10^k + b$，$k$ 是多少不重要，因为在模 $3$ 的意义下，$10^k$ 恒等于 $1$。

所以原式就变成了 $(a_i + a_j)^2 + a_i \times a_j$。

然后由于在模 $3$ 意义下，$a_i$ 只有 $3$ 钟取值。

于是把他们一一列举出来：


|$0$|$0$|$0$|
|:-:|:-:|:-:|
|$0$|$1$|$1$|
|$0$|$2$|$1$|
|1|$1$|$2$|
|$1$|$2$|$2$|
|$2$|$2$|$2$|

我们发现对于 $Z=0$，那么只要保证所有的 $0$ 都在一组内即可。

设 $cnt_i$ 表示 $i$ 的出现次数。

那么只要 $cnt_0 \le \frac n2$ 即可。

否则对于 $Z=2$，只要让 $1,2$ 在同一组即可。

也就是 $cnt_1 + cnt_2 \le \frac n2$。

又由于 $cnt_0 + cnt_1 + cnt_2 = n$，所以上面那两个式子至少有一个成立，所以不会无解。

```cpp
#include <bits/stdc++.h>

using namespace std;

int n;
int a[100010];
bool st[100010];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
    int cnt = 0;
    for (int i = 1; i <= n; ++i) {
        if (a[i] % 3 == 0)
            st[i] = true, ++cnt;
    }
    
    if (cnt > n / 2) {
        memset(st, false, sizeof(st));
        cnt = 0;

        for (int i = 1; i <= n; ++i)
            if (a[i] % 3 == 1 || a[i] % 3 == 2) {
                ++cnt;
                st[i] = true;
            }

        for (int i = 1; i <= n; ++i) if (!st[i] && cnt < n / 2) {
            ++cnt;
            st[i] = true;
        }
    
        puts("2");
        for (int i = 1; i <= n; ++i) printf("%d", st[i]);
        return 0;
    }

    for (int i = 1; i <= n; ++i)
        if (!st[i] && cnt < n / 2) {
            ++cnt;
            st[i] = true;
        }
    
    puts("0");
    for (int i = 1; i <= n; ++i) printf("%d", st[i]);

    return 0;
}
```

---

## 作者：WaterSun (赞：0)

[更好的阅读体验](https://watersun.top/%5B%E9%A2%98%E8%A7%A3%5DCF1725H%20Hot%20Black%20Hot%20White)

# 思路

首先转化原式为：

$$
(a_i + a_j) \times (a_i + a_j + 1) \equiv z \pmod 3
$$

考虑对 $a_i \bmod 3,a_j \bmod 3$ 进行分讨：

|$a_i/a_j$|$0$|$1$|$2$|
|:-:|:-:|:-:|:-:|
|$0$|$0$|$1$|$1$|
|$1$|$1$|$2$|$2$|
|$2$|$1$|$2$|$2$|

发现，只有当 $a_i = a_j = 0$ 时，原式为 $0$。于是记 $a$ 中 $0$ 的数量为 $x$。

如果 $x \geq \frac{n}{2}$，令 $z = 2$，将 $\frac{n}{2}$ 的 $0$ 放在一组，其余放在另一组。

否则，令 $z = 0$，将所有 $0$ 都丢入同一组，其余随便分即可。

# Code

```cpp
#include <bits/stdc++.h>
#define re register

using namespace std;

const int N = 1e5 + 10;
int n,num;
int arr[N];

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

int main(){
    n = read();
    for (re int i = 1;i <= n;i++){
        arr[i] = read() % 3; num += (!arr[i]);
    }
    if (num * 2 >= n){
        int cnt = 0;
        puts("2");
        for (re int i = 1;i <= n;i++){
            if (!arr[i]){
                if (cnt < n / 2) putchar('0');
                else putchar('1');
                cnt++;
            }
            else putchar('1');
        }
    }
    else{
        int cnt = 0;
        puts("0");
        for (re int i = 1;i <= n;i++){
            if (!arr[i]) putchar('0');
            else{
                if (cnt + num < n / 2) putchar('0');
                else putchar('1');
                cnt++;
            }
        }
    }
    return 0;
}
```

---

## 作者：zct_sky (赞：0)

### Solution:
-----
我们知道 $a \equiv s(a) \pmod 3$，（$s(a)$ 表示 $a$ 的数位和）。

因此 $\operatorname{concat}(a_i,a_j) \equiv a_i+a_j \pmod 3$。

然后借此将题目中的式子化简：

$$\operatorname{concat}(a_i,a_j) \times \operatorname{concat}(a_j,a_i) + a_i \times a_j \equiv Z \pmod 3$$

$$(a_i+a_j) \times (a_j+a_i) + a_i \times a_j \equiv Z \pmod 3$$

$$(a_i+a_j)^2 + a_i \times a_j \equiv Z \pmod 3$$

$$a_i^2+a_j^2+2\times a_i \times a_j + a_i \times a_j \equiv Z \pmod 3$$

$$a_i^2+a_j^2 \equiv Z \pmod 3$$

$a_i^2 \bmod 3 \equiv (a_i \bmod 3)^2$，结果为 $0^2 \equiv 0,1^2 \equiv 1,2^2 \equiv 1 \pmod 3$。

而 $a_i^2 + a_j^2 \bmod 3$ 的结果 $\in \{0,1,2\}$。

显然，若将所有 $a_i^2 \equiv 1 \pmod 3$ 的进行染色（或不染色），则无法满足 $color_i \ne color_j,a_i^2+a_j^2 \equiv 2 \pmod 3$。

同理，若将所有 $a_i^2 \equiv 0 \pmod 3$ 的进行染色（或不染色），则无法满足 $color_i \ne color_j,a_i^2+a_j^2 \equiv 0 \pmod 3$。

因此，我们只需要将 $a_i^2 \equiv 0 \pmod 3$ 和 $a_i^2 \equiv 1 \pmod 3$ 中数量较少者全染色（或全不染色）即可，染完后若还有剩余，则随意染色。
### Code:
-----
```c++
#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline ll read(){
	ll x=0,y=1;
	char c=getchar();
	while(c>'9'||c<'0'){
		if(c=='-')y=-1;
		c=getchar();
	}
	while(c<='9'&&c>='0')x=(x<<3)+(x<<1)+c-'0',c=getchar();
	return x*y;
}
const int N=1e5+7;
int n,a[N],zero;
int main(){
	n=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		a[i]=(a[i]%3!=0); 
		zero+=!a[i];
	}
	bool flag=(zero>=n/2);
	int tmp=0;
	printf("%d\n",(flag)?2:0);
	for(int i=1;i<=n;i++){
		printf("%d",(tmp<n/2)?flag^a[i]:0);
		tmp+=(tmp<n/2)?flag^a[i]:0;
	}
	return 0;
}
```

---

## 作者：myEnd (赞：0)

原题链接：[戳我](https://www.luogu.com.cn/problem/CF1725H)

### 题解正文
对于 $c(A, B) \times c(B, A) + A \times B \equiv Z \pmod 3 $，从 $\operatorname{mod} \ 3$ 的性质入手，可以将这个式子转化为：$(A+B)^2 + A \times B \equiv Z \pmod 3$，即 $A^2 + B^2 \equiv Z \pmod 3$。

考虑 $A$ 和 $B$ 的 $\operatorname{mod} 3$ 的结果，与 $A^2+B^2$ 的 $\operatorname{mod} 3$ 的关系：

|                          | $B \equiv 0 \pmod 3$ | $B \equiv 1 \pmod 3$ | $B \equiv 2 \pmod 3$ |
| ------------------------ | -------------------- | -------------------- | -------------------- |
| **$A \equiv 0 \pmod 3$** | $0$                  | $1$                  | $1$                  |
| **$A \equiv 1 \pmod 3$** | $1$                  | $2$                  | $2$                  |
| **$A \equiv 2 \pmod 3$** | $1$                  | $2$                  | $2$                  |



注意到只有 $A \equiv B \equiv 0 \pmod 3$ 时，才能得到 $c(A, B) \times c(B, A) + A \times B \equiv 0 \pmod 3$ 的情况。

那么考虑 $0$ 的个数：

- 当 $0$ 放不满一种颜色的时候，全部放到一种颜色里，就不会有 $c(A, B) \times c(B, A) + A \times B \equiv 0 \pmod 3$ 的情况出现，置 $Z=0$ 即可。

- 当 $0$ 能放满的时候，让 $0$ 放满一种颜色，这样就不会有 $c(A, B) \times c(B, A) + A \times B \equiv 2 \pmod 3$ 的情况出现，置 $Z = 2$ 即可。

总上，不会有无解的情况，按 $\text{mod} \ 3 = 0$ 的 $a_i$ 的个数分类就 OK。

记得要注意一些小细节。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;

int ans[(int)3e5+17];

signed main()
{
	register vector<pair<int, int>> a[3];
	register int n, t;
	
	cin >> n;
	for(register int i=1; i<=n; ++i)
	{
		cin >> t;
		a[t%3].emplace_back(t, i);
	}
	
	t = a[0].size();
	register int Z;
	if(t >= n/2) // 能够放满一种颜色
	{
		
		for(register int i=0; i<n/2; ++i)
			ans[a[0][i].second] = 0;
		for(register int i=n/2; i<t; ++i)
			ans[a[0][i].second] = 1;
		for(register pair<int, int> x: a[1])
			ans[x.second] = 1;
		for(register pair<int, int> x: a[2])
			ans[x.second] = 1;
		Z = 2;
	}
	else // 放不满, 那就全部放到一组 
	{
		
		for(register pair<int, int> x: a[0])
			ans[x.second] = 0;
		t = n/2 - t;
		
		register int i = 0, e = a[1].size();
		for(; i < e; ++i, --t)
		{
			if(t == 0) { break; }
			ans[a[1][i].second] = 0;
		}
		
		if(t == 0)
		{
			for(; i<e; ++i) ans[a[1][i].second] = 1;
			i = 0, e = a[2].size();
			for(; i<e; ++i) ans[a[2][i].second] = 1;
		}
		else
		{
			i = 0, e = a[2].size();
			for(; t && i<e; --t, ++i)
				ans[a[2][i].second] = 0;
			for(; i<e; ++i)
				ans[a[2][i].second] = 1;
		}
		
		Z = 0;
	}
	
	cout << Z << "\n";
	for(register int i=1; i<=n; ++i) cout << ans[i];
	
	cout << endl;
	
	return 0;
} 
```

---

