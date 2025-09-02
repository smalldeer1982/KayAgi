# Make A Equal to B

## 题目描述

You are given two arrays $ a $ and $ b $ of $ n $ elements, each element is either $ 0 $ or $ 1 $ .

You can make operations of $ 2 $ kinds.

- Pick an index $ i $ and change $ a_i $ to $ 1-a_i $ .
- Rearrange the array $ a $ however you want.

Find the minimum number of operations required to make $ a $ equal to $ b $ .

## 说明/提示

In the first case, we need only one operation: change $ a_1 $ to $ 1-a_i $ . Now $ a = [0, 0] $ which is equal to $ b $ .

In the second case, the optimal way is to rearrange $ a $ to get the array $ [0, 1, 11 $ . Now $ a = [0, 0, 1] $ which is equal to $ b $ .

In the second case, one of optimal ways would be to first change $ a_3 $ to $ 1 - a_3 $ , then rearrange $ a $ .

In the third case, no operation is needed.

In the fourth case, the optimal way is to rearrange $ a $ to get the array $ [0, 1, 1, 0] $ .

## 样例 #1

### 输入

```
5
3
1 0 1
0 0 1
4
1 1 0 0
0 1 1 1
2
1 1
1 1
4
1 0 0 1
0 1 1 0
1
0
1```

### 输出

```
1
2
0
1
1```

# 题解

## 作者：0zhouyq (赞：7)

## CF1736A 题解

[传送门](https://www.luogu.com.cn/problem/CF1736A)

### 思路：

我们可以分两种情况讨论：如果要使用排序操作，那我们只要把 $a$ 数列中 $0$ 与 $1$ 的个数调整成与 $b$ 序列一样就好了。操作次数就是 $a$ 中 $1$ 的个数减去 $b$ 中 $1$ 的个数的绝对值再加 $1$。如果不使用排序操作，那我们就把 $a$ 中与 $b$ 不同的地方逐一调整即可。操作次数就是 $a$ 与 $b$ 中不同的地方的个数。

两种情况取最小值就好。

### AC Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int a[101],b[101];
signed main(){
	int t;
	scanf("%lld",&t);
	while(t--){
		int n;
		scanf("%lld",&n);
		int bt=0,aa=0,bb=0;//bt是a与b中不同的个数，aa是a中1的个数，bb是b中1的个数。
		for(int i=1;i<=n;i++) scanf("%lld",&a[i]);	
		for(int i=1;i<=n;i++) scanf("%lld",&b[i]);
		for(int i=1;i<=n;i++){
			if(a[i]!=b[i]) bt++;
			if(a[i]) aa++;
			if(b[i]) bb++;
		}
		printf("%lld\n",min(bt,abs(aa-bb)+1));//取最小值
	}
	return 0;
}
```

---

## 作者：L_zaa_L (赞：4)

## 分析
既然题目给了两种条件，我们就可以得出两种方式使得变换（最小的两种情况）：

- 直接看看两个序列每个位置相不相同，并记录下来，再将每个地方不同的直接变换。
- 看看每个数出现了多少次（这里只有两个数，所以只需要记录一个，另一个数就是总共有多少个再减去前一个数出现的次数），并记录两个序列同一个数的差值（只用记录差值，因为另一个数也差这么多，将多的那一个数多出来的变为另一个数就恰好得到了序列 $b$），最后加上变换一次的操作（将变换留到最后，可以最小化答案）。

于是只用记录：$0$ 在序列 $a$ 出现的次数 $s1$，$0$ 在序列 $b$ 出现的次数 $s2$，两个序列在同一个位置上的数不同的次数 $x$。那么答案就是 $\min(x,abs(s1-s2)+1)$

## Code

```
#include<bits/stdc++.h>
using namespace std;
int b[100005];
int main(){
    int t;
    cin>>t;
    for(int i=1;i<=t;i++){
    	int n;
    	cin>>n;
    	int s1=0,s2=0;//s1记录0在序列a中出现的次数，s2记录0在序列b中出现的次数。
    	int a;
    	int x=0;//记录不同之处
    	for(int j=1;j<=n;j++){
    		cin>>b[j];
    		if(b[j]==0) s1++;
		}
    	for(int j=1;j<=n;j++){
    		cin>>a;
    		if(a!=b[j]) x++;
    		if(a==0) s2++;//统计
		}
		cout<<min(x,abs(s1-s2)+1)<<endl;//求出两种方法的最小值
	}
    return 0;
}
```


---

## 作者：Dangerous_system (赞：1)

[【题目传送门】](https://www.luogu.com.cn/problem/CF1736A)

----
## 思路：
其中改变有直接修改和任意排序，则可以比较任意排序后需要修改的次数和直接全部修改的次数，其中排序后修改为原先数组 $1$ 的个数减去改变后数组 $1$ 的个数加 $1$，直接修改则一个去比较，计算次数。

----
## CODE
```cpp
#include <bits/stdc++.h>
using namespace std;
int t,n,a[maxn],b[maxn];
signed main(){
	cin>>t;
	while(t--){
		int k=0,k2=0,ans=0;
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			if(a[i]==1) k++;
		}
		for(int i=1;i<=n;i++){
			cin>>b[i];
			if(b[i]==1) k2++;
			if(a[i]!=b[i]) ans++;
		}
		cout<<min(abs(k2-k)+1,ans)<<endl;
	}
}

```

---

## 作者：YH_Eternally (赞：1)

## 题意
给定有 $n$ 个 $0$ 或 $1$ 的数列 $a,b$，进行以下操作：

- 选择任意一个 $i$，将 $a_i$ 变为 $0$ 或 $1$。
- 将 $a$ 数列任意排序

求将数列 $a$ 变成数列 $b$ 的最小操作数。

## 思路
十分简单，开两个变量 $ans1$ 和 $ans2$ 分别记录不排序时将 $a$ 变成 $b$ 的最小操作数与排序后将 $a$ 变成 $b$ 的最小操作数。最后，输出 $\min(ans1,ans2)$ 即可。

**注意：由于排序也算一次操作，所以要将 $ans2$ 的值初始化为 $1$。**

另外，**多测清空**！

## 代码
```cpp
#include <bits/stdc++.h>

using namespace std;

int t, n, a[200], b[200], ans1, ans2;

inline int read() {
	int x = 0, f = 1;
	char ch = getchar();
	while(ch < '0' || ch > '9') {
		if(ch == '-') f = 0;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9') {
		x = (x << 3) + (x << 1) + (ch ^ 48);
		ch = getchar();
	}
	return f ? x : -x;
}

int main() {
	t = read();
	while(t --) {
		ans1 = 0, ans2 = 1;//多测清空
		n = read();
		for(int i = 1; i <= n; i ++) a[i] = read();
		for(int i = 1; i <= n; i ++) b[i] = read();
		for(int i = 1; i <= n; i ++) {
			if(a[i] != b[i]) ans1 ++;//不排序
		}
		stable_sort(a + 1, a + n + 1);
		stable_sort(b + 1, b + n + 1);
		for(int i = 1; i <= n; i ++) {
			if(a[i] != b[i]) ans2 ++;//排序
		}
		printf("%d\n", min(ans1, ans2));
	}
    return 0;
}
```


---

## 作者：Larryyu (赞：1)

## _Description_
给定 $a_1,a_2\dots a_n,b_1,b_2\dots b_n$，保证 $a_i,b_i$ 为 $0$ 或 $1$，求将 $a$ 数组转变为 $b$ 数组的最小次数。

转变方式：
1. 将 $0$ 变为 $1$，将 $1$ 变为 $0$；
2. 对 $a$ 数组随意排序；
## _Solution_
分类讨论：
1. 不排序，直接转变，在输入 $b$ 时，计算 $a_i \neq b_i$ 的个数。
2. 排序，计算 $a$ 与 $b$ 中 $0$ 个数之差（$1$ 也可以），再加一即可（排序那一次）。

输出两方案中较小的次数即可。
## _Code_
```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int n;
int a[110],b[110];
int cnt1,cnt2,cnt3;
int read(){
    int x=0,f=1;
    char ch;
    ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+ch-'0';
        ch=getchar();
    }
    return x*f;
}
int main(){
    t=read();
    while(t--){
    	cnt1=0;
        cnt2=0;
        cnt3=0;
        n=read();
        for(int i=1;i<=n;i++){
            a[i]=read();
            if(a[i]==0) cnt1++;
        }
        for(int i=1;i<=n;i++){
            b[i]=read();
            if(b[i]==0) cnt2++;  //方案2，计算0之差
            if(b[i]!=a[i]) cnt3++;  //方案1，计算两数不同数量
        }
        cout<<min(abs(cnt1-cnt2)+1,cnt3)<<endl;
    }
    return 0;
}
```
#### _完结撒花！！_

---

## 作者：guozhetao (赞：1)

## 题目大意
$t(t \leq 400)$ 组数据，每组数据两个数组，长度都为 $n(n \leq 100)$，分别叫做数组 $a$ 与数组 $b$。你可以进行如下操作：

- 将 $a_i $ 变成 $a_j$，其中 $1 \leq i,j \leq n$。
- 将数组 $a$ 按需要排序。

求最少需要几次操作才能变成数组 $b$。
## 思路
[类似的题目](https://www.luogu.com.cn/problem/P8537)

现在要求最少操作几次。首先操作二最多操作一次，毕竟操作两次第一次就被覆盖了。

所以我们计算直接一个一个更改和排序后更改所需要的步数，取最小值即可。
## 代码
[AC](https://www.luogu.com.cn/record/89673545)
```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
	int a;
	scanf("%d",&a);
	while(a--) {
		int b;
		int c1 = 0,d1 = 0;
		scanf("%d",&b);
		int ans1 = 0;
		int e[505],f[505];
		for(int i = 1;i <= b;i++) {
			scanf("%d",&e[i]);
			if(e[i]) c1++;
		}
		for(int i = 1;i <= b;i++) {
			scanf("%d",&f[i]);
			if(f[i]) d1++;
			if(e[i] != f[i]) {
				ans1++;
			}
		}
		printf("%d\n",min(ans1,abs(c1 - d1) + 1));
	}
} 
```


---

## 作者：GI录像机 (赞：1)

## 思路

很容易想到我们排序最多排一次，于是分两种情况考虑：

1. 不进行排序，这样答案就是满足 $a_i\neq b_i$ 的 $i$ 的个数。
2. 进行排序，考虑统计 $a$ 与 $b$ 中 $1$ 的个数相差的数量，相差多少就要改变多少次。因为要排序，所以答案加一。

## 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int read() {
	int f = 1, x = 0;
	char c = getchar();
	while (c < '0' || c > '9') {
		if (c == '-')f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		x = x * 10 + c - '0';
		c = getchar();
	}
	return f * x;
}
void write(int x) {
	if (x < 0) {
		putchar('-');
		x = -x;
	}
	if (x > 9)write(x / 10);
	putchar(x % 10 + '0');
}
const int N = 110, MOD = 1e9 + 7, INF = 0x3f3f3f3f;
int t = read();
signed main() {
	while (t--) {
		int n = read(), a[N], b[N], ans = 0, o = 0, z = 0;
		for (int i = 1; i <= n; i++)a[i] = read();
		for (int i = 1; i <= n; i++)b[i] = read();
		for (int i = 1; i <= n; i++) {
			if (a[i] != b[i])ans++;
			if (a[i])o--;
			if (b[i])o++;
		}
		write(min(ans, abs(o) + 1));
		putchar('\n');
	}
	return 0;
}


```


---

## 作者：sunkuangzheng (赞：0)

**【题目分析】**

首先可以证明的是，排序操作只能进行一次。那我们可以分两种情况讨论：

1. 不进行排序。此时需要修改的次数为长度减去两串对应位置相等的数量。
1. 进行排序。由于可以任意排序，所以我们只需要使两串中字符 $\texttt{1}$ 的数量相等。因此，答案就是两串中字符 $\texttt{1}$ 的数量差 $+1$。

据此，我们可以写出代码。

**【完整代码】**

```cpp
#include <bits/stdc++.h>
using namespace std;
int x,n1,n2,n,t,a[10005];//n1 记录字符'1'的差值，n2记录对应位置相等的数量
int main(){
    cin >> t;
    while(t--){
    	n1 = n2 = 0;
    	cin >> n;
    	for(int i = 1;i <= n;i ++){
		    cin >> a[i];
		    if(a[i]) n1 ++;
	    }
	    for(int i = 1;i <= n;i ++){
	    	cin >> x;
	    	if(x == a[i]) n2 ++;
	    	if(x) n1 --;
		}
		cout << min(n-n2,abs(n1)+1) << endl;
	}
	
	return 0;
}
```

---

## 作者：RAVE_LOVEo_O (赞：0)

简单的模拟题

思路：
-

分类讨论
1. 不进行排序：直接找不相同的个数。

1. 排序：很明显排序只会排一次，所以是排完序后找不相同的个数，排序也算一个操作，所以算完后要加一。

最后两种情况取最小值就好了。

注意：
-

两个统计前置零。


## AC Code：


```cpp
#include<bits/stdc++.h>
using namespace std;
int n,t,b[105],a[105],s1,s2,i;//定义变量
namespace IO{
	char ibuf[(1<<20)+1],*iS,*iT;
	#if ONLINE_JUDGE
	#define gh() (iS==iT?iT=(iS=ibuf)+fread(ibuf,1,(1<<20)+1,stdin),(iS==iT?EOF:*iS++):*iS++)
 	#else
	#define gh() getchar()
	#endif
	#define reg register
	inline long long read(){
		reg char ch=gh();
		reg long long x=0;
		reg char t=0;
		while(ch<'0'||ch>'9')   t|=ch=='-',ch=gh();
		while(ch>='0'&&ch<='9') x=x*10+(ch^48),ch=gh();
		return t?-x:x;
	}
}
using IO::read;//跑的超快的快读
void write(int x) {
	if(x<0){
		putchar('-');
		write(-x);
		return;
	}
	if(x>=10)write(x/10);
	putchar(x%10+'0');
}
int main()
{
   t=read();
   while(t--)
   {
      s1=s2=0;//用前赋初值
      n=read();//输入
      for(i=1;i<=n;i++)a[i]=read();
      for(i=1;i<=n;i++)b[i]=read(),s1+=(a[i]!=b[i]);//边输入边统计
      sort(a+1,a+n+1);
      sort(b+1,b+n+1);//排序
      for(i=1;i<=n;i++)s2+=(a[i]!=b[i]);//重新统计
      write(min(s1,s2+1));//比较最小值
      puts("");//换行
   }
   return 0;//完结撒花！
}
```


---

## 作者：隐仞Mrsu (赞：0)

# 题目大意
给定两个长度都为 $n$ 的 $01$ 串 $a$ 和 $b$。

可以做的操作有：
- 在 $a$ 串中选择任一位置进行 $0$ 和 $1$ 的转换；
- 将 $a$ 按任意的顺序排列一次。

问最少操作几次能使 $a$ 和 $b$ 相同。

# 分析

### 当两串相同时
显然，不用进行操作，答案为 $0$。

### 当两串 $0$ 和 $1$ 的个数分别相等时
此时，对 $a$ 进行操作二，即按照串 $b$ 的顺序重新排列一次，即可使得两串相等，答案为 $1$。

### 当不满足上两个条件时
```
5
1 0 0 0 0
0 1 1 1 0
```
对于这个例子，我们发现 $a$ 串只需用操作一把两个 $0$ 改成 $1$ 使得两串 $1$ 的个数相等，然后用操作二排列一次即可。答案是 $2+1=3$。

由此得到思路，只需记录两串值为 $1$ 的元素个数的差，该差值就是操作一的次数；然后加一次操作二也就是排序的操作，就得到答案。

但是对于下面的例子：
```
4
1 1 0 1
1 1 1 1
```
当我们把 $a$ 串中的 $0$ 转化为 $1$ 后，两串已经相同，没有必要再加一次操作二排序的操作数。因此答案也可能是两串相同编号对应元素不同的个数。

综上，我们用变量 $wa$ 和 $wb$ 记录两串值为 $1$ 的个数，用 $f$ 记录两串相同编号对应元素不同的个数。输出答案为 $\min\{f,\lvert wa-wb\rvert+1\}$。

# 代码
```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const int N = 1e5+5;
LL _,n,a[N],b[N];
int main(){
	ios::sync_with_stdio(false);
	cin>>_;
	while(_--){
		LL wa=0,wb=0,f=0;
		cin>>n;
		for(LL i=1;i<=n;i++){
			cin>>a[i];
			wa+=a[i];
		}
		for(LL i=1;i<=n;i++){
			cin>>b[i];
			wb+=b[i];
			if(a[i]!=b[i])f++;
		}
		if(wa==wb){
			if(f)
				cout<<"1\n";
			else cout<<"0\n";
			continue;
		}
		cout<<min(f,abs(wa-wb)+1)<<'\n';
	}
} 
```


---

## 作者：Texas_the_Omertosa (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1736A)

### 0x01 思路

此题与洛谷月赛某题很像。

分两种：一种是不排序，一种是排序。分别记录其操作次数，取最小值即可。

注意：排序也算一次操作。

### 0x02 AC Code
```cpp
#include <bits/stdc++.h>
#define int long long
#define N 100005
#define M 100005
#define mod 10000007
#define iinf INT_MAX
#define linf LLONG_MAX
#define ios ios::sync_with_stdio(0);cin.tie(0);
using namespace std;
int a[N];
int b[N];
signed main()
{
	ios;
	int t;
	cin >> t;
	for (int asdf = 1; asdf <= t; asdf ++)
	{
		int n, ans = 1, ans1 = 0;
		cin >> n;
		for (int i = 1; i <= n; i ++)
		{
			cin >> a[i];
		}
		for (int i = 1; i <= n; i ++)
		{
			cin >> b[i];
		}
		for (int i = 1; i <= n; i ++)
		{
			if (a[i] != b[i])
			{
				ans1 ++;
			}
		}//记录不排序操作次数
		sort(a + 1, a + n + 1);
		sort(b + 1, b + n + 1);//可以理解为将 a 数列排序成与 b 数列一样
		for (int i = 1; i <= n; i ++)
		{
			if (a[i] != b[i])
			{
				ans ++;
			}
		}//记录排序操作次数
		cout << min(ans, ans1) << '\n';
	}
	return 0;
}
```

---

