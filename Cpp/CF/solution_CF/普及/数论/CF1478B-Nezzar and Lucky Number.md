# Nezzar and Lucky Number

## 题目描述

Nezzar's favorite digit among $ 1,\ldots,9 $ is $ d $ . He calls a positive integer lucky if $ d $ occurs at least once in its decimal representation.

Given $ q $ integers $ a_1,a_2,\ldots,a_q $ , for each $ 1 \le i \le q $ Nezzar would like to know if $ a_i $ can be equal to a sum of several (one or more) lucky numbers.

## 说明/提示

In the first test case, $ 24 = 17 + 7 $ , $ 27 $ itself is a lucky number, $ 25 $ cannot be equal to a sum of lucky numbers.

## 样例 #1

### 输入

```
2
3 7
24 25 27
10 7
51 52 53 54 55 56 57 58 59 60```

### 输出

```
YES
NO
YES
YES
YES
NO
YES
YES
YES
YES
YES
YES
NO```

# 题解

## 作者：Loser_King (赞：6)

数学题（打表题）。

建议评级：普及- ~ 普及/提高-

## 简明题意

定义：如果一个数的十进制表示法中含有数字 $d\;(1\le d \le 9)$ ，那么其为幸运数。

现在给 $n\;(1\le n\le 10^5)$ （即题目中的 $t\times q$）个数 $a_i\;(1\le a_i\le 10^9)$，

判断其是否为几个幸运数之和。

## 解法

由数据范围可得，要做到 $\Omicron(1) $ 的时间来判断一个数是否满足条件。

手玩几个发现，当 $a_i\ge 10d$ 时，$a_i$ 一定为满足条件。

证：当 $10d\le a_i\le 11d$ 时，$a_i$ 的十位为 $d$ ，其本身为幸运数，满足条件。

当 $11d<a_i\le 12d$ 时， 有 $a_i=d+(a_i-d)$ ，而 $10d\le a_i-d\le 11d$，满足条件。

以此类推。

现在只需要处理 $a_i<10d$ 的情况了。而这种情况可以打表。

但是如果我们不想打表怎么办呢？其实也可以推式子。

如果 $a_i<10d$ ，那么和为它的幸运数各位必为 $d$。

那么 $a_i$ 一定可以表示成 $10k+bd(b\in N,k\in N^+)$ 的形式。即 $k=\frac{a_i-bd}{10}$

枚举 $b$ ，看是否有一个满足 $k\in N^+$ 即可。

## 代码

```c++
//CF1478B AC Code
//written by Loster_King(159686)
//1.40s / 4KB / 280B C++ O2
#include<bits/stdc++.h>
using namespace std;
int t,n,k,x;									//此处k相当于d
int check(int x,int k){
	if(x>=10*k)return 1;
	while(x>=0)if(x%10!=k)x-=k;else return 1;	//x-=k相当于枚举b,b++
	return 0;
}
int main(){
	cin>>t;
	while(t--){
		cin>>n>>k;
		while(n--)cin>>x,cout<<(check(x,k)?"yes\n":"no\n");
	}
} 
```



---

## 作者：Zzzzzzzm (赞：3)

## 首先我们来简要概述题意

$t$组数据，$1≤t≤9$。每组数据输入$q$、$n$，即每组的$q$个数以及喜爱的数$n$，$1≤q≤10000$，$1≤n≤9$，接下来输入q个数，判断该数能否为是否能是幸运数组成的数。
幸运数即十进制表示该数时(~~废话~~)这个数中有$n$。

## 分析
我们先思考什么数是幸运数？

拿$7$举例。

$7$，$17$，$27$，$37$，$47$，$57$，$67$，$70$，$71$，$72$，$73$，$74$，$75$，$76$，$77$，$78$，$79$，$87$，$97$。

那么一旦超过了$10×n$，那么一定能成为一个幸运数。因为$80=73+7$，$81=74+7$，$82=75+7$，$83=76+7$，$84=77+7$，$85=78+7$，$86=79+7$，$87=80+7×2$……因此只要该数超过了幸运数$n$的$10$倍，一定可以。

那么如果小于$10×n$呢？显然如果这个数$a$ $mod$ $n=0$，那么$a$就能由$a/n$个$a$组成。

那么如果不能整除呢？我们可以观察到除了$n$以外就是$n+10$，$n+20$……之类的数，所以如果这个数$a-10*i$，$1≤i≤9$能整除n，这个数也可以成为幸运数。

其他情况呢？我们可以发现无论如何这个数组成一定是$n*i+10*j$，所以如果不满足上三种，一定是不行的。

## CODE
```cpp
#include<bits/stdc++.h>
using namespace std;

int t, num, n, a;

template <typename T>				//快读快写，可以读入输出int,long long以及short
inline void read(T&x){
    x=0;char ch=getchar();bool f=false;
    while(!isdigit(ch)){if(ch=='-'){f=true;}ch=getchar();}
    while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    x=f?-x:x;
    return;
}

template <typename T>
inline void write(T x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10^48);
    return;
}

//**********************华丽的分割线**********************// 

int main(){
	read(t);
	while(t--){
		read(n), read(num);
		for(int i = 1; i <= n; ++i){
			read(a);
			bool flag = 0;
			if(a >= num*10){			//情况一：a>=n*10 
				printf("YES\n");
				continue;
			}
			while(a >= 0){				//情况二:a<n*10 
				a -= num;	
				if(a % 10 == 0){		//如果减少num后就可以被10整除了那么也成立 
					flag = 1;			//记录被整除过了，成立 
					printf("YES\n");
					break;
				}
			}
			if(!flag)					//如果flag未被更改 
				printf("NO\n");			//输出NO 
		}
	}
	return 0;
}
```


---

## 作者：FutaRimeWoawaSete (赞：1)

恶心，这才是真正的 E 吧。              

考虑在两位数 $dx$ 的时候，当 $1 \leq x \leq 9$ 时该数都是合法情况，用 $d$ 一个个转移即可保证后面的数都合法。            

当 $a_i \leq 10d - 1$ 时，我们发现我们的 $a_i$ 可以写成这个形式：               

$a_i = Xd + 10Y$ 

这个就相当于一些十位数不固定，个位数为 $d$ 的数相加而成，我们把个位的 $d$ 提出来，十位给提出来就可以变成这个形式， $X$ 可以理解成有多少个数相加。

其中 $1 \leq X \leq d - 1$ ，后面的 $Y$ 其实没有什么限制，这个可以用正整数拆分原理说明。               

```cpp
#include<bits/stdc++.h>
using namespace std;
const int Len = 1e4 + 5;
int n,m,d;
bool check(int x)
{
	if(x >= 10 * d) return 1;
	for(int i = 1 ; i * d <= x ; i ++) if((x - d * i) % 10 == 0) return 1;
	return 0;
}
int main()
{
	int t;scanf("%d",&t);
	while(t --)
	{
		scanf("%d %d",&m,&d);
		for(int i = 1 ; i <= m ; i ++)
		{
			int x;scanf("%d",&x);
			if(check(x)) puts("YES");
			else puts("NO"); 
		}
	}
	return 0;
}
```

---

## 作者：33aaron (赞：1)

## 题目大意
给定一组数，输入这组数的长度 $q$ ，针对每个数如果自身包含 $d$ 或是 $q$ 是几个含有 $d$ 的数和，输出```YES```，否则输出```NO```。
## 题目分析
#### 结论一：
首先我们可以发现 $10d$ 及以上的数均自身包含 $d$ 或是几个含有 $d$ 的数和。

我们可以发现一个 $10d + 10$ 以上的数都能分解成一个在 $[10d, 10d + 9]$ 中的数加上一个个位是 $d$ 的数，而且 $[10d, 10d + 9]$ 中的数十位上一定是 $d$，所以我们在输入时发现大于等于 $10d$ 的数都可以直接输出```YES```随后处理下一个数。
#### 结论二：
凡是 $d$ 的倍数的数一定是几个 $d$ 的和。

不多解释，乘法的意义就可以证明。
#### 结论三：
若一个数自身包含 $d$ 或是 $q$ 是几个含有 $d$ 的数和，则这个数一定是 $d$ 的倍数加上一个是 $10$ 的倍数的数。

举几个例子：
若$d = 7$

$24 = 7 + 17 = 7 + 7 + 10 = 2 × 7 + 10$

$59 = 7 + 7 + 7 + 7 + 7 + 7 + 17 = 7 + 7 + 7 + 7 + 7 + 7 + 7 + 10 = 7 × 7 + 10$

所以我们在写程序是就可以判断输入的数是不是 $d$ 的一个倍数加上一个 $10$ 的倍数。

把以上三个结论实现出来就AC了。

## AC Code
```Cpp
#include <iostream>
using namespace std;
int times, q, d;
int main() {
    cin >> times;
    while (times--) {
        cin >> q >> d;
        while (q--) {
            int in;
            cin >> in;
            if (in >= d * 10) cout << "YES\n"; //结论一
            else {
                if (in < 10) //小于10只判断结论二
                    if (in % d == 0) cout << "YES\n";
                    else cout << "NO\n";
                else {
                    if (in % d == 0) cout << "YES\n"; //结论二
                    else { //结论三
                    int flag = 0;
                    if (in % 10 != 0) { 
                        for (int i = 10; i <= in / 10 * 10; i += 10)
                            if ((in - i) % d == 0) { cout << "YES\n"; flag = 1; break; }
                    } else {
                        for (int i = 10; i <= (in - 1) / 10 * 10; i += 10)
                            if ((in - i) % d == 0) { cout << "YES\n"; flag = 1; break; }
                    }
                    if (!flag) cout << "NO\n";
                }}    
            }
        }
    }
    return 0;
}
```

---

## 作者：vectorwyx (赞：1)

如果 $a_{i}$ 能被 $d$ 整除，那么 $a_{i}$ 必定能表示为若干个幸运数之和。而如果一个数大于等于 $d\times10$，那么一定存在幸运数 $k\le a_{i},d|(a_{i}-k)$（从十位数为 $d$ 的两位数里找就行），故这个数必定满足要求。而如果这个数小于 $d\times10$，我们可以通过记忆化搜索/ dp 预处理出 $1\sim d\times 10-1$ 的答案（暴力拆分应该也行）。

代码如下：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define ll long long
#define fo(i,x,y) for(register int i=x;i<=y;++i)
#define go(i,x,y) for(register int i=x;i>=y;--i)
using namespace std;

inline int read(){
	int x=0,fh=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-') fh=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	return x*fh;
}

const int N=1e5+5;
int a[N],f[N],b[N];

bool dfs(int x){
	if(x==0) return 1;
	if(f[x]!=-1) return f[x];
	fo(i,0,10){
		if(b[i]>x) break;
		if(dfs(x-b[i])) return f[x]=1;
	}
	return f[x]=0;
}

void work(){
	int n=read(),d=read(),lim=d*10;
	b[0]=d;
	fo(i,1,10) b[i]=b[i-1]+10;
	fo(i,0,100) f[i]=-1;
	fo(i,0,lim-1) f[i]=dfs(i);
	//fo(i,0,lim-1) printf("f[%d]=%d ",i,f[i]);
	fo(i,1,n) a[i]=read();
	fo(i,1,n){
		if(a[i]>=lim) puts("YES");
		else puts(f[a[i]]?"YES":"NO");
	}
	//puts("");
}

int main(){
	int T=read();
	while(T--){
		work();
	}
	return 0;
}

```


---

## 作者：lndjy (赞：1)

由于数字 $0-9$ 的，所以可以**打表**。

我们设 $ans[d][x]$ 表示 $a_i\ mod\  d=x$ 时可以被 $d$ 表示的最小的 $a_i$。那么，只要 $a_i\ mod\  d=x$ 且 $a_i\ge ans[d][x]$,那么 $a_i$ 就可以被表示。因为 $a_i$ 可以用 $ans[d][x]$ 和一些 $d$ 表示。

$ans[d][x]$ 可以暴力打表，也可以手算，~~也可以让别人帮你算，我就是这么干的~~。然后就做完了。

最后，祝大家打表出省一。

```cpp
#include<iostream>
using namespace std;
int ans[15][15];
int main()
{
	for(int i=1;i<=9;i++) ans[i][0]=i;
	ans[2][1]=21;
	ans[3][1]=13,ans[3][2]=23;
	ans[4][1]=41,ans[4][2]=14,ans[4][3]=43;
	ans[5][1]=51,ans[5][2]=52,ans[5][3]=53,ans[5][4]=54;
	ans[6][1]=61,ans[6][2]=26,ans[6][3]=63,ans[6][4]=16,ans[6][5]=65;
	ans[7][1]=57,ans[7][2]=37,ans[7][3]=17,ans[7][4]=67,ans[7][5]=47,ans[7][6]=27;
	ans[8][1]=81,ans[8][2]=18,ans[8][3]=81,ans[8][4]=28,ans[8][5]=85,ans[8][6]=38,ans[8][7]=87;
	ans[9][1]=19,ans[9][2]=29,ans[9][3]=39,ans[9][4]=49,ans[9][5]=59,ans[9][6]=69,ans[9][7]=79,ans[9][8]=89;
	int T;
	cin>>T;
	while(T--)
	{
		int q,d;
		cin>>q>>d;
		for(int i=1;i<=q;i++)
		{
			int x;
			cin>>x;
			cout<<(x>=ans[d][x%d]?"YES\n":"NO\n");
		}
	}
 	return 0;
}


```


---

## 作者：Fa1thful (赞：0)

### 题意：
判断输入的每个数是否能由在数位上含有 $d$ 的几个数的和表示。
### 分析：
首先我想到的就是把所有小于每个数的幸运数都根据 $d$ 构造出来，再用搜索找出是否能够用这几个构造出来的数构造出每个数。可是看到题目的数据范围

$1\le q\le10^4$

$1\le a[i]\le10^9$

很显然这样的暴力是绝对不行的。那么我们可以考虑一件事情，每个幸运数都有什么特点？

我们可以从构造幸运数的思路出发，发现如果两个两位数都是幸运数，那么他们肯定个位或者是十位都有 $d$ 。所以说我们可以把一个幸运数一直减十，就能构造出新的幸运数。

### 代码：
```cpp
# include <bits/stdc++.h>
using namespace std;
int a[600000];
bool flag[600000];
int main()
{
	int T;
	cin >>T;
	while (T--)
	{
		memset(flag, false, sizeof(flag));    //记得初始化哦 
		int n, d;
		cin >> n >> d;
		for (int i = 1; i <= n; i++)
		{
			cin >> a[i];
			if (a[i] >= d * 10)             //如果它比十位是d个位是0的数大 
			{
				flag[i] = true;            //那么他一定能分解成幸运数 
				continue;
			}
			int tmp = a[i];                //找替身 
			while (tmp > 0)                
			{
				if (tmp % d == 0)         //如果个位一样 
				{
					flag[i] = true;      //是 
					break;
				}
				tmp -= 10;               //-10的操作 
			}
		}
		for (int i = 1; i <= n; i++)
		{
			if (flag[i] == true) cout << "YES" << endl;
			else cout << "NO" << endl;
		} 
	}
}
```


---

## 作者：Allanljx (赞：0)

### [洛谷题目传送门](https://www.luogu.com.cn/problem/CF1478B)
### [CF题目传送门](https://codeforces.com/problemset/problem/1478/B)
## 题意
给定一个数，若这个数可被拆分成若干个十进制表示法上有 $d$ 的正整数，输出：$YES$ ，否则，输出：$NO$ 。


## 思路
情况一：如果 $a[i]$ 大于等于 $d*10$ ，则一定可以满足条件；

情况二：如果 $a[i]$ 小于 $d*10$ 每次减$10$，如果除于 $d$ 等于$0$，就可以满足条件，因为 $d+10$ 并不影响个位；

情况三：否则就不满足条件。


## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,q,d,a;
int main()
{
	cin>>t;
	while(t--)
	{
		scanf("%d%d",&q,&d);
		while(q--)
		{
			scanf("%d",&a);
			if(a>=d*10) //情况一
			{
				printf("YES\n");
				continue;
			}
			bool f=1;
			while(a>0)
			{
				if(a%d==0)//情况二
				{
					printf("YES\n");
					f=0;
					break;
				}
				a-=10;
			}
			if(f!=0) printf("NO\n");//情况三
		}
	}
	return 0;
}
```



---

## 作者：black_trees (赞：0)


upd - 2021.8.8 ： 修正笔误。 


简单题。

---

题意不用说了。

首先第一眼能看出来：

对于一个数 $a$ 如果 满足 $a \ge d \times 10 $

那么很明显这个数是可以满足题目条件的（也就是输出 `YES`）。

考虑 $a < d\times10$ 的情况。

直接暴力拆分然后看能不能满足条件就好。

code:

```cpp
#include<bits/stdc++.h>
using namespace std;

int T,n,d;

int main(){
    #ifndef ONLINE_JUDGE
        freopen("out.txt","w",stdout);
    #endif
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&d);
        for(register int i=1;i<=n;++i){
            int input;
            scanf("%d",&input);
            if(input<d*10){
                bool f=false;
                while(input>=0){//暴力拆
                    input-=d;
                    if(input%10==0){//满足条件
                        f=true;
                        break;
                    }
                }
                if(f){puts("YES");}else{puts("NO");}
            }
            else{
                puts("YES");
            }//比d*10大一定可以
        }
    }
}
```

---

## 作者：奥特战士 (赞：0)

## 题面分析
~~哦没翻译啊nmsl~~

对于每一个$a$

不难发现，当$a>=10d$的时候，**$a$总能表示成幸运数字的和**

证明如下：

首先我们用$a$对$10d$**取模**，因为 **$10d$是幸运数字**

接下来我们用$a$对$d$**取模**，会剩下来一个**余数**，它$∈[0,d)$，因为$d∈[1,9]$，所以这个余数$<10$。

也就是说，**这个余数可以加到前面的任意一个$10d$里**，因为这样只会改变它的个位数，**它仍然是一个幸运数字**

所以，当$a>=10d$时， **$a$总能表示成幸运数字的和**

~~证毕~~

------------
那当$a<10d$的时候呢？

这个时候，能组成$a$的幸运数字一定是**个位数为$d$**

也就是$10k+d$

所以说$a$就可以表示成$10k+nd$

那么我们只需要用$a$不断$-10$，直到$d|a$

## 代码实现

AC代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,q,d,a;
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&q,&d);
		while(q--){
			scanf("%d",&a);
			if(a>=d*10){
				puts("YES");
				continue;
			}
			bool f=1;
			while(a>0){
				if(a%d==0){
					puts("YES");
					f=0;
					break;
				}
				a-=10;
			}
			if(f)puts("NO");
		}
	}
	return 0;
}
```


---

## 作者：_Anchor (赞：0)

# B题（性质/暴力）

## Problem

给定一个数$d$ $(d\in [1,9])$，我们定义一个正整数是$lucky$的当且仅当这个数在十进制表示下的某一位出现了数字$d$

现在给出$n$个询问以及$d$，每次询问一个数$a_i$可不可以表示成一些$lucky$数的和，（可以表示指$a_i$可以由任意多个$lucky$的数拼出来，同时一个$lucky$数可以出现多次）

是的话输出$YES$，否则输出$NO$

## Solution

观察可以得到，对于任意的$a_i\ge100$，不管$d$是多少都可以拼出来

因为我们可以这样考虑：

我们一定是会存在$10d+1,10d+2,10d+3，...，10d+9$这样的数，那么其实对于$mod$ $d$意义下，我们一定可以得到是$d$的倍数的数

而不能得到的，比如这个数$a_i \equiv k $ $(mod$ $d)$，那么我们就先减掉一个$10d+k$这个数，那么接下来$a_i$就变成了$d$的倍数，我们直接用$d$去拼就可以了

那么对于$a_i<100$的情况，我们可以每次取出当前最新一轮被更新的数$k$，然后更新$k+d$即可

直接暴力更新就行了

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
template <typename T>
inline void read(T &x){
	x=0;char ch=getchar();bool f=false;
	while(!isdigit(ch)){if(ch=='-'){f=true;}ch=getchar();}
	while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	x=f?-x:x;
	return ;
}
template <typename T>
inline void write(T x){
	if(x<0) putchar('-'),x=-x;
	if(x>9) write(x/10);
	putchar(x%10^48);
	return ;
}
template <typename T>
inline void print(T x){write(x),putchar(' ');}
#define ll long long
#define ull unsigned long long
#define inc(x,y) (x+y>=MOD?x+y-MOD:x+y)
#define dec(x,y) (x-y<0?x-y+MOD:x-y)
#define min(x,y) (x<y?x:y)
#define max(x,y) (x>y?x:y)
const int N=1e5+5,M=1e6+5,MOD=1e9+7;
int n,d,a[N];
bool vis[100][10];
bool check(int x,int w){
	while(x){
		if(x%10==w) return true;
		x/=10;
	}
	return false;
}
int main(){
	int t;
	read(t);
	for(int i=1;i<=9;i++){
		for(int j=1;j<=99;j++){
			if(check(j,i)) vis[j][i]=true;
			if(vis[j][i]) vis[j+i][i]=true;
		}
	}
	while(t--){
		read(n),read(d);
		for(int i=1;i<=n;i++) read(a[i]);
		if(d==1){
			for(int i=1;i<=n;i++) puts("YES");
			continue;
		}
		for(int i=1;i<=n;i++){
			if(a[i]>=100) puts("YES");
			else{
				if(vis[a[i]][d]) puts("YES");
				else puts("NO");
			}
		}
	}
	// system("Pause");
	return 0;
}
```

---

## 作者：Skies (赞：0)

这个题需要分析一下性质

首先

### 性质一
对于每个数当
$$a_i>=10*d$$

一定满足条件


因为这个数中的其中的一个加数十位为d其他位随便取，

所以一定可以构成另一个满足条件的整数

### 性质二

这个数一定可以写成
$$10*k_1+d*k_2$$

接下来就可以欢乐的打代码了
## code
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10,M=5e5+10;
#define inf 0x3f3f3f3f
#define ll long long
#define ull unsigned long long
#define PII pair<int,int>
inline int inc(int x,int v,int mod){x+=v;return x>=mod?x-mod:x;}
inline int dec(int x,int v,int mod){x-=v;return x<0?x+mod:x;}
inline int rd(){int x=0,f=1;char ch=getchar();while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}
inline void wr(int x){if(x==0){putchar(48);return;}int len=0,dg[20];while(x>0){dg[++len]=x%10;x/=10;}for(register int i=len;i>=1;i--)putchar(dg[i]+48);}
int a[N];
int n,q;
bool ch(int x)
{
	if(x>=10*q) return 1;
	int p=x;
	p%=10;
	if(p==0)p=10;
	while(p<=x)
	{
		if(p%q==0)return 1;
		p+=10;
	}
	return 0;
}
int main()
{
	//freopen("未命名1.in","r",stdin);
	//freopen("未命名1.out","w",stdout);
	int t;
	cin>>t;
	while(t--)
	{
		
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
		{
			a[i]=rd();
		}
		for(int i=1;i<=n;i++)
		{
			if(ch(a[i])) 
			{
				puts("YES");
			}else{
				puts("NO");
			}
		}
	}
    return 0;
}
```

---

## 作者：kradcigam (赞：0)

我的做法非常简单.

首先如果 $a_i \geq 100$，那肯定是 `Yes`。即我们只需要用十位为 $k$ 的两位数和 $k$ 就可以表示出所有大于等于 $100$ 的所有数。

然后如果小于 $100$ 的数，我们直接暴力递推已经即可以了

```cpp
#include<bits/stdc++.h>
using namespace std;
template<typename T>inline void read(T& FF){
    FF=0;T RR=1;char CH=getchar();
    for(;!isdigit(CH);CH=getchar())if(CH=='-')RR=-1;
    for(;isdigit(CH);CH=getchar())FF=(FF<<1)+(FF<<3)+(CH^48);
    FF*=RR;
}
int __;
bool h[1010];
int main(){
    for(read(__);__--;){
        int n,m;read(n);read(m);
        // memset(f,0x3f,sizeof(f));
        memset(h,0,sizeof(h));
        for(int i=0;i<=9;i++)h[i*10+m]=1;
        for(int i=0;i<=9;i++)h[m*10+i]=1;
        for(int i=0;i<=100;i++)
            if(h[i])
                for(int j=0;j<=100;j++)
                    if(h[j])
                        h[i+j]=true;
        // for(int i=1;i<=20;i++)f[(i*m)%10]=min(f[(i*m)%10],i);
        for(int i=1;i<=n;i++){
            int x;read(x);
            if(x<=100&&h[x]||x>100)puts("YES");
            else puts("NO");
        }
    }
    return 0;
}
```

---

## 作者：Meaninglessness (赞：0)

### B. Nezzar and Lucky Number

**题目大意:**

> 给定一个数 $d$,定义幸运数为数位中含有 $d$ 的数。
> 给你 $q$ 个数,询问这些书是否能分成多个幸运数的和。

---

**解题思路:**

没看懂题目意思?(不过我这个已经很清楚明白了好吧)

假设 $d=7$

$24=17+7$ 所以 $24$ 符合要求。

$104=70+27+7$ 所以 $104$ 符合要求。

注意必须分拆成的每一个数都为幸运数,比如$25=7+7+7+4$就不是了。

我们有结论:**如果查询的数 $\ge d*10$,那么满足要求。**

因为如果这个数 $\ge d*10+10$,那么一定可以将它拆出很多个 $d$ ,最后剩一个 $\overline{dx}$。

如果 $< d*10$,暴力分拆即可。

---

**代码实现:[Code](https://www.luogu.com.cn/paste/0mlxnkoi)　时间复杂度 $O(T)$**

---

## 作者：qinyihao (赞：0)

### 思路
对于任何给定的$d$，我们可以观察到如下信息：
- $10d$到$10d+9$中包含$d$作为它的一个数位。
- 定义$k=10d+9$是该种数字的最大值。对于任何大于$k$的$x$，我们可以持续用$d$减去$x$，$x$就会渐渐达到有$d$作为其数位的范围。

所以，对于任何大于$k$的$x$，他们总是可达到的。对于小于等于$k-10$的$x$，也就是$k \leq 109$时，我们可以运行标准的动态规划（即动规），$dp[x]$暗示了$x$是否可行。如果$dp[x]$可行，那么下面中有且仅有一条是对的：
- $x=0$
- 在某些$y<x$的情况下，$dp[y]$可行且$x-y$有$d$作为一个数位。

除了动规，单纯的暴力也能轻松通过本题。
### code1-动规版 时间复杂度$O((10d)^2)$
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=207;
int t,d,q;
bool dp[maxn];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin>>t;
    while (t--){
        memset(dp,0,sizeof(dp));
        dp[0]=1;
        cin>>q>>d;
        if (!d) d+=10;
        int mx=d*10;
        for (int i=0;10*i+d<=mx;++i){
            for (int j=0;10*i+d+j<=mx;++j){
                dp[10*i+d+j]|=dp[j];
            }
        }
        while (q--){
            int u;
            cin>>u;
            if (u>=mx||dp[u]) cout<<"YES"<<endl;
            else cout<<"NO"<<endl;
        }
    }
    return 0;
}
```
### code2-暴力版（没算时间复杂度）
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, cnt, m, a[100010], ans, flag;
bool p(int x, int k)
{
	while (x)
	{
		if (x % 10 == k)
			return 1;
		x /= 10;
	}
	return false;
}
bool pa(int x, int k)
{
	if (p(x, k) || x == 0)
		return true;
	for (int i = 1; i <= x; ++i)
	{
		if (p(i, k) && pa(x - i, k))
			return true;
	}
	return false;
}
int main()
{
	cin >> flag;
	while (flag--)
	{
		cin >> n >> m;
		for (int i = 1; i <= n; i++)
		{
			cin >> a[i];
			if (pa(a[i], m))
				puts("YES");
			else
				puts("NO");
		}
	}
	return 0;
}
```

---

## 作者：wcarry (赞：0)

#### 题目大意：
有一个幸运数字x，令含这个幸运数字的数是幸运数。求每个所询问的数能不能表示为几个幸运数相加。

#### 思路：
对于每个所询问的数，弄个$for$循环来减它，每$for$一遍，减一次幸运数字，直到该数是幸运数。（ps:幸运数和幸运数字要区分好）直到减到$0$,此时该数就不能分为多个幸运数相加。

#### 证明:

* 当$a_i\ge10k$,必然可以，它可以表示为$10*k+m*k+n$，$n$为常数且$0\le n<10$

* 其他的情况下，就可以直接开减，用幸运数字来枚举。比如：24=7+7+10。可发现将所有幸运数字减去后，赫然是一个$10$,其实经过大量计算可发现这样减下去，此数若是对的，最后应只剩10的倍数。那不就简单了，最后一个十的倍数与前面随便一个幸运数字相加就可以变成幸运数。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define re register
template<typename T>
inline void read(T &x){
	x=0;re char ch=getchar();re bool f=false;
	while(!isdigit(ch)){if(ch=='-')f=true;ch=getchar();}
	while(isdigit(ch)){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	x=f?-x:x;return;
}
template <typename T>
inline void write(T x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10^48);
    return ;
}
int const N=1e4+5;
int a[N];
bool check(int x,int d){
	while(x){
		int now=x%10;
		if(now==d) return true;
		x/=10;
	}
	return false;
}
bool calc(int x,int d){
	int now=x;
	if(check(now,d)) return true;
	for(int i=1;;i++){
		if(now<d) return false;
		now-=d;
		if(check(now,d)) return true;
	}
}
int main(){
	int t;read(t);
	while(t--){
		int q,d;read(q),read(d);
		for(int i=1;i<=q;i++){
			read(a[i]);
		}
		for(int i=1;i<=q;i++){
			if(calc(a[i],d)) puts("YES");
			else puts("NO");
		}
	}
}
```


---

