# Array Reodering

## 题目描述

You are given an array $ a $ consisting of $ n $ integers.

Let's call a pair of indices $ i $ , $ j $ good if $ 1 \le i < j \le n $ and $ \gcd(a_i, 2a_j) > 1 $ (where $ \gcd(x, y) $ is the greatest common divisor of $ x $ and $ y $ ).

Find the maximum number of good index pairs if you can reorder the array $ a $ in an arbitrary way.

## 说明/提示

In the first example, the array elements can be rearranged as follows: $ [6, 3, 5, 3] $ .

In the third example, the array elements can be rearranged as follows: $ [4, 4, 2, 1, 1] $ .

## 样例 #1

### 输入

```
3
4
3 6 5 3
2
1 7
5
1 4 2 4 1```

### 输出

```
4
0
9```

# 题解

## 作者：住在隔壁小莘 (赞：8)

## 题目分析
在题目中问 $\gcd(a_i,2\times a_j)$，他这给的而倍一定有用，并且跟最大公约数有关，当任意一个 $a_j (a_j<0)$ 乘上 $2$ 时**它都会变成一个偶数**，所以它都会与任意一个偶数存在 $\gcd$ 大于 $1$ 的情况

所以为了个数最多，我们要让**偶数都排在奇数的前面**，而在这里偶数这一类中的位置便不重要，奇数这一类中各个奇数的位置也不重要，所以我们不用在意

1. 偶数处理：设一个 $num$ 记录有几个偶数
我们可以在输入的时候就判断这个数是否为偶数，如果是那么 $num$ 加一，那么它必然与 $n-num$ 个数都有 $\gcd>1$ 的情况，$ans$ 加上 $n-num$

2. 奇数处理：如果是奇数，则单独放在一个数组中，然后用两个 $for$ 循环来求与其他数存在 $\gcd>1$ 的情况的个数，最后输出

## Code：
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int t,n,a[10010],ans,b[10010],num,num2;
int gcd(int a,int b)
{
    int n=a%b;
    while(n!=0)
    {
        a=b;
        b=n;
        n=a%b;
    }
        return b; 
}
int main(){
	cin>>t;
	for(int i=1;i<=t;i++){
		num=0,num2=0,ans=0;
		cin>>n;
		for(int j=1;j<=n;j++){
			cin>>a[j];
			if(a[j]%2==0){
				num2++;
				ans+=n-num2;
			}else{
				num++;
				b[num]=a[j];
			}
		}
		sort(b+1,b+num+1);//这里排不排序无所谓了
		for(int j=1;j<=num;j++){
			for(int k=j+1;k<=num;k++){
				if(gcd(b[j],b[k])>1){//求奇数中gdc>1的个数
					ans++;
				}
			}
		}
		cout<<ans<<endl;
	}
}
```

---

## 作者：HerikoDeltana (赞：3)

这个题没想到是暴力能过......

## 题意简述

给你一个长度为 n 的序列 a ，定义 "好数对" 如下：

若有 i 和 j 满足

$$
1 \le i < j \le n \ , \ gcd(a_i,2a_j) > 1
$$

那么则称 $(i,j)$ 是一对好数对。

现在给你这个序列 a ，并且这个序列你可以随意排序，求在你排序之后的 a 中有多少好数对。

## 思路简述

我个人是用的一种瞎搞的做法，咱也不知道是怎么想到的。

大约就是能被 2 整除（也就是偶数）的放在队首，否则放在队尾，

根据我自己口胡，这样做原因大概是是二的倍数的放在前面能够有效的增加好数对的个数。

可能是数据太水了吧，这完全瞎搞的做法能过（ 249ms ），下面贴上代码。

## Code

```cpp
#include <bits/stdc++.h>
#define Heriko return
#define Deltana 0
#define Romano 1
#define S signed
#define U unsigned
#define LL long long
#define R register
#define I inline
#define D double
#define LD long double
#define mst(a, b) memset(a, b, sizeof(a))
#define ON std::ios::sync_with_stdio(false)
using namespace std;
I void fr(LL & x)
{
    LL f = 1;
    char c = getchar();
    x = 0;
    while (c < '0' || c > '9') 
    {
        if (c == '-') f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9') 
    {
        x = (x << 3) + (x << 1) + c - '0';
        c = getchar();
    }
    x *= f;
}
I void fw(LL x)
{
    if(x<0) putchar('-'),x=-x;
    static LL stak[35];
    LL top=0;
    do
    {
        stak[top++]=x%10;
        x/=10;
    }
    while(x);
    while(top) putchar(stak[--top]+'0');
    putchar('\n');
}
LL gcd(LL x,LL y)
{
    Heriko ! y ? x : gcd(y,x%y);
}
LL t;
S main()
{
    fr(t);
    while(t--)
    {
        LL n,a[2001],b[2001],hd=0,tl,ans=0;
        fr(n);
        tl=n+1;
        for(R LL i=1;i<=n;++i) fr(a[i]);
        for(R LL i=1;i<=n;++i)
        {
            if(a[i]&1) b[--tl]=a[i];
            else b[++hd]=a[i];
        }
        for(R LL i=1;i<=n;++i)
            for(R LL j=i+1;j<=n;j++)
                if(gcd(b[i],b[j]*2)!=1) ans++;
        fw(ans);
    }
    Heriko Deltana;
}
```
于是乎这题就水过去了！

---

## 作者：StayAlone (赞：3)

### 题意

给定一个长度为 $n$ 的数组 $a$，现在称 `good pair` 是指：$1 \leqslant i < j \leqslant n \land gcd(a_i, 2a_j) > 1$ 的一对数。请你随意安排这个数组中数的位置，使得它 `good pair` 的数量最多。每一行输出这个最多的数量。  

### 思路

由于 $gcd(even,even) \geqslant 2$，而 `good pair` 的第二个数会乘上 $2$，因此我们把所有偶数放到前面，所有奇数放到后面，奇数乘 $2$ 后变成偶数，故此时 `good pair` 数量最多。  

时间复杂度 $O(n^2 \log a_i)$。  

[AC code记录](https://www.luogu.com.cn/record/51488456)  

```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n, a[2010], b[2010], idx, cnt;

int gcd(int a, int b)
{
	return b ? gcd(b, a % b) : a;
}

int main()
{
	scanf("%d", &t);
	while (t--)
	{
		scanf("%d", &n); idx = 1, cnt = 0;
		for (int i = 1; i <= n; ++i) scanf("%d", a + i);
		for (int i = 1; i <= n; ++i)
			if (a[i] % 2 == 0) b[idx++] = a[i];
		for (int i = 1; i <= n; ++i)
			if (a[i] % 2) b[idx++] = a[i];
		for (int i = 1; i <= n; ++i)
			for (int j = i + 1; j <= n; ++j)
				if (gcd(b[i], 2 * b[j]) > 1) cnt++;
		printf("%d\n", cnt);
	}
	return 0;
}
```

---

## 作者：LinkZelda (赞：3)

- **题意**：

$t$ 组询问，每次给定一个长度为 $n$ 的序列 $a$。定义数对 $(i,j)$ 是优美的当且仅当 $1\leq i<j\leq n,\gcd(a_i,2\times a_j)>1$。请求出将原序列重排后可以产生的优美数对个数的最大值。

$t\leq 1000,2\leq n\leq 2000,\sum n\leq 2000,1\leq a_i\leq 10^5$。

- **题解**：

考虑贪心，$2\times a_i$ 必定为一个偶数，容易发现偶数两两之间的 $\gcd$ 必定 $>1$ 。因此我们应该把所有的偶数放在所有奇数的前面，这样后面的奇数和前面的偶数必定不互质，比把奇数放在偶数前面要优。

于是我们直接把偶数放前，奇数放后，然后按照题意计算答案即可，时间复杂度为 $O(n^2\log a_i)$。

- [代码](https://www.luogu.com.cn/paste/xb3iey2p)

---

## 作者：zhengjh2818 (赞：2)

## 闲话多说
暴力题可为黄题，蒟蒻亦可成大佬
## 题目介绍
[题目传送门](https://www.luogu.com.cn/problem/CF1535B)
## 解题思路
题目要求在 $i<j$ 的前提下，求符合条件 $\gcd(a_i,2 \times a_j)>1$ 的个数。

要知道，想要满足这个表达式 $\gcd(a_i,2 \times a_j)>1$ 条件，需要尽可能的使 $a_i,2 \times a_j$ 为偶数。（因为两个偶数的最大公因数一定为偶数）

所以我们需要对输入的元素进行判断：如果为偶数，则放入数组开头；为奇数则放入数组末尾。（因为 $i<j$，且 $a_j$ 会被乘以 $2$，**一定为偶数**）

最后套用两个循环，找出符合条件 $\gcd(a_i,2 \times a_j)>1$ 的个数，输出即可。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n;
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> t;
	while (t--) {
		cin >> n;
		int a[n + 10] = {}, b[n + 10] = {};
		int sum, alen, blen;
		sum = alen = blen = 0;
		for (int i = 1; i <= n; i++) {
			int x;
			cin >> x;
			if (x % 2 == 0) {
				a[++alen] = x;
			} else {
				b[++blen] = x;
			}
		}
		for (int i = alen + 1; i <= alen + blen; i++) {
			a[i] = b[i - alen];
		}
		for (int i = 1; i < alen + blen; i++) {
			for (int j = i + 1; j <= alen + blen; j++) {
				if (__gcd(a[i], a[j] * 2) > 1) {
					sum++;
				}
			}
		}
		cout << sum << "\n";
	}
	return 0;
}
```
**~~蒟蒻的第二篇题解一审，望审核员大人通过~~**

---

## 作者：OptimisticForever (赞：2)

## 简要题意
给一个长度为 $n$ 序列 $a$。求重组后能产生形如 $(i,j),1\le i<j\le n,(a_i,a_j\times 2)>1$ 数对，数量的最大值。
## 具体分析

考虑贪心。

因为看到了 $\times 2$，所以想到了**奇数和偶数**。

- 偶数和偶数的一定是贡献。
- 偶数和奇数是不一定有贡献的，要使贡献存在，我们就让奇数乘以 $2$，河阳就是两个偶数了。
- 奇数和奇数的贡献不会因为乘以 $2$ 而改变，所以我们不需要管奇数。

因此我们把奇数放在后面，偶数放在前面，顺序随便。暴力算一遍答案即可。
## 时间复杂度分析
因为$\sum n\leq2000$，所以$\sum n^2\leq(\sum n)^2=4000000$，不会超时。

code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[2005],b[2005];
int cmp(int x,int y){
	return x>y;
}
int main(){
	int t;
	scanf("%d",&t);
	while (t--){
		scanf("%d",&n);
		for (int i=1;i<=n;i++) scanf("%d",&a[i]);
		int k=0;
		for (int i=1;i<=n;i++)
			if (!(a[i]&1))
				b[++k]=a[i];
		for (int i=1;i<=n;i++)
			if (a[i]&1)
				b[++k]=a[i];
		int ans=0;
		for (int i=1;i<=n;i++){
			for (int j=i+1;j<=n;j++){
				if (__gcd(b[i],b[j]*2)>1){
					ans++;
				}
			}
		}
		printf("%d\n",ans);
	}
}
```

---

## 作者：奥特战士 (赞：1)

# 题面分析
~~感谢翻译大哥~~
>每次给定一个长度为 $n$ 的序列 $a$。定义数对 $(i,j)$ 是优美的当且仅当 $1\leq i<j\leq n,\gcd(a_i,2\times a_j)>1$。请求出将原序列重排后可以产生的优美数对个数的最大值。

不难发现，任意两个偶数之间的**最大公因数**肯定大于 $1$

所以说我们应该把奇数放在后面

利用 $\times2$ 来**把奇数变成偶数**

然后暴力求 $\gcd$ 就行了
# 代码实现
~~有误，勿抄~~
```cpp
#include<bits/stdc++.h>
using namespace std;
#define RG register
const int N=2e3+5;
int n,T,ans;
int a[N];
inline int read(){
	RG int w=0;RG char ch=getchar();
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch)){w=(w<<3)+(w<<1)+(ch^48);ch=getchar();}
	return w;
} 
inline void write(int x){
	if(x>9)write(x/10);
	putchar(x%10^48);
}
inline bool cmp(int x,int y){
	return x&1<y&1;
}
inline int gcd(int x,int y){
	if(!y)return x;
	return gcd(y,x%y);
}
int main(){
	T=read();
	while(T--){
		n=read();
		ans=0;
		for(RG int i=1;i<=n;++i)
			a[i]=read();
		sort(a+1,a+n+1,cmp);
		for(RG int i=1;i<n;++i){
			for(RG int j=i+1;j<=n;++j){
				if(gcd(a[i],a[j]<<1)>1)
					++ans;
			}
		}
		write(ans);
		putchar(10);
	}
	return 0;
}
```

---

## 作者：Shunpower (赞：1)

## 题目大意

首先，**本题含有多组数据**。

对于每组数据，考虑两个下标 $i,j$ 在一个长度为 $n$ 的序列 $a$ 中，若 $1\leqslant i < j \leqslant n \land gcd(a_i,2a_j)>1$ 则称这对 $(i,j)$ 是**优美的数对**，请问怎样安排这个序列使得有最多的**优美的数对**，输出这个最大值。

## 思路分析

很显然，$2a_j$ 是本题的突破口。

根据简单的数学我们知道，如果 $a_j$ 为奇数，$2a_j$ 就是偶数，同时又有 $a_i$ 为偶数，那偶数和偶数之间的 $gcd$ 肯定是大于 $1$ 的。

为了既可以把 $a_j$ 变成偶数，又能使前面的 $a_i$ 为偶数，可以考虑把偶数放在奇数前面，让后面的奇数占掉下标 $j$ ，偶数占掉下标 $i$ ，不但使得 $i<j$ ，同时也造出了一大堆合法的数对。

## 代码解析

### 第一步：把偶数放前面，奇数放后面

在读入的时候，用两个数组，**一个数组存偶数，一个数组存奇数**。

```
for(int i=0;i<n;i++){
	cin>>a[i];
	if(a[i]%2==1){
		b[tot]=a[i];//tot是指针，指向奇数数组的下一位。
		tot++;//指针后移
	}
	else{
		c[tnt]=a[i];//tnt也是指针，指向偶数数组的下一位。
  		tnt++;//指针后移
	}
}
```
所以现在我们就把偶数和奇数分离了出来。

**指针的另外一个作用其实是记录奇数和偶数各有多少**。因此现在我们可以把前 $tnt$ 个 $a_i$ 变成 $c_i$，而剩下的数都变成 $b_{i-tnt}$。

```
//我用的两个for循环可以变成一个，但是这样更加直观。
for(int i=0;i<tnt;i++){
		a[i]=c[i];//把a序列中的前面tnt个数变成偶数。
}
for(int i=tnt;i<n;i++){
	a[i]=b[i-tnt];//把a序列中剩下的数变成奇数。
}
```
**注意：在将奇数赋值回序列 $a$ 中时，$b$ 数组的下标要减去一个 $tnt$ 。**

### 第二步：做暴力

 首先先写一个 $gcd$ 函数。
 
 ```
int gcd(int x,int y){
	if(y==0){
		return x;
	}
	else{
		return gcd(y,x%y);//辗转相除法求gcd
	}
}
//这是速度较快而且写法简单的gcd方法。
//甚至还可以用三目运算符压行成一行。
```

然后做一个大暴力就可以了。

```
for(int i=0;i<n;i++){
	for(int j=i+1;j<n;j++){ //因为i<j，所以可以直接从i+1开始暴力。
		if(gcd(a[i],2*a[j])>1){//我们的快速gcd
			cnt++;//记录个数
		}
	}
}
```

## 注意事项
- $tnt,\ tot,\ cnt$ 每组数据结束后一定**要清零**！
- 要搞**多组数据**。


## AC code

各部分在文中已经拆分提供代码。

[AC记录](https://www.luogu.com.cn/record/51497543)

---

## 作者：Chenyichen0420 (赞：0)

# 解法：

首先，题面中 $\gcd(a_i,2\times a_j)$ 中的 $2\times$ 引起了我们的注意。

我们会发现，在不考虑 $2\times$ 的情况下，先后顺序其实是无用处的。然而加了之后会有一种影响：任意一个偶数放在一个奇数前面都一定会是一对优美数对。

所以，我们将所有的偶数放在所有的奇数前面一定更优。而其内部顺序并不重要。毕竟只产生了上面的那一种影响。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[2005],ans;
inline bool cmp(int l,int r){
	return (l&1)<(r&1);
}
int main(){
	ios::sync_with_stdio(0);
	cin>>t;
	while(t--){
		cin>>n; ans=0;
		for(int i=1;i<=n;++i) cin>>a[i];
		sort(a+1,a+n+1,cmp);
		for(int i=1;i<=n;++i)
			for(int j=i+1;j<=n;++j)
				ans+=(bool)(__gcd(a[i],a[j]*2)!=1);
		cout<<ans<<endl;
	}
	return 0;
} 
```

---

## 作者：Zzzzzzzm (赞：0)

## 题目分析：

对于任意的一对数 $i, j,i>j$ ，若 $a_i\mod2 = 0$ ，则 $\gcd(a_i ,a_j) \not=1$。
$\therefore$ 只要将 $a_i \mod 2 = 0$ ，就可以将他前置。
$\therefore$ 只需将所有的奇数枚举即可。

我们假设有 $odd$ 个奇数，$even$ 个偶数。则已有 $ans=even\times(even-1)/2+odd\times even$，此外再一次枚举奇数即可。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
 
int t, a[2005], n;
int odd[2005], even[2005], num1, num2;
int ans;
 
template<typename T>
inline void read(T&x){
    x=0; char q; bool f=1;
    while(!isdigit(q = getchar()))  if(q == '-')    f = 0;
    while(isdigit(q)){
        x = (x<<1)+(x<<3)+(q^48);
        q = getchar();
    }
    x = f?x:-x;
}
 
template<typename T>
inline void write(T x){
    if(x<0){
        putchar('-');
        x = -x;
    }
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
 
int gcd(int x, int y){
	if(x % y == 0)	return y;
	gcd(y, x%y);
}
 
int main(){
	read(t);
	while(t--){
		ans = 0, num1 = 0, num2 = 0;
		read(n);
		for(register int i = 1; i <= n; ++i){
			read(a[i]);
			if(a[i] % 2 == 1)	odd[++num1] = a[i];	//记录奇数
			else	even[++num2] = a[i];			//记录偶数
		}
		ans += num2*(num2-1)/2;						//预处理出偶数产生的ans
		ans += num1*num2;
		for(register int i = 1; i <= num1; ++i)		//枚举奇数
			for(register int j = 1; j < i; ++j)
				if(gcd(odd[i], odd[j]) != 1)
					ans++;
		write(ans);
		cout << endl;
	}
    return 0;
}
```


---

## 作者：Skies (赞：0)

## CF1535B Array Reodering题解


### 题目分析

**贪心**：

因为**每两个数**都会被求一遍 $\gcd$，所以不同排列的区别就在于谁 $\times 2$。

这里分情况讨论这两个数的**奇偶性**。

- 奇数，奇数

  谁 $\times2$  都没有关系，反正也**不会改变**他们的 $\gcd$。

- 偶数，偶数

   他们的 $gcd$ 一定 $>1$ (因为至少是 $2$)，所以一定会被答案统计，谁  $\times2$ 也都一样会被答案统计。

- 奇数，偶数
 
  这里我们让奇数  $\times2$，就可以使答案统计到。

   反之，如果让偶数 $\times2$，就不一定会被统计到。




所以我们就让**奇数排在后边**(这里用 sort 实现)，然后暴力统计即可。

## 代码


```cpp
#include <bits/stdc++.h>
using namespace std;
#define inf 0x3f3f3f3f
#define ll long long
#define ull unsigned long long
#define PII pair<int,int>
#define fori for(int i=1;i<=n;i++)

int T;
const int N=1e5+10;
int a[N],n,b[N];
int gcd(int x,int y)
{
	if(y==0)return x;
	return gcd(y,x%y);
}
bool cmp(int x,int y)
{
	return x%2>y%2;
}
int main()
{
	cin>>T;
	while(T--)
	{
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&a[i]);
		}
		sort(a+1,a+n+1,cmp);
		int ans=0;
		for(int i=1;i<=n;i++)
		for(int j=1;j<i;j++)
		{
			if(gcd(a[i],2*a[j])>1)
			ans++;
		}
		printf("%d\n",ans);
	}
    return 0;
}

```





---

