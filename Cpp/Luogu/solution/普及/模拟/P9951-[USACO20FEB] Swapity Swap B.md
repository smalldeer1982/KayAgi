# [USACO20FEB] Swapity Swap B

## 题目描述

Farmer John 的 $N$ 头奶牛（$1\le N\le 100$）站成一排。对于每一个 $1\le i\le N$，从左往右数第 $i$ 头奶牛的编号为 $i$。

Farmer John 想到了一个新的奶牛晨练方案。他让她们重复以下包含两个步骤的过程 $K$（$1\le K\le 10^9$）次：

1. 当前从左往右数在位置 $A_1\ldots A_2$ 的奶牛序列反转她们的顺序（$1\le A1<A2\le N$）。
2. 然后，在当前从左往右数在位置 $B_1\ldots B_2$的奶牛序列反转她们的顺序（$1\le B_1<B_2\le N$）。

当奶牛们重复这一过程 $K$ 次后，请对每一个 $1\le i\le N$ 输出从左往右数第 $i$ 头奶牛的编号。 

## 说明/提示

### 样例解释 1

初始时，奶牛们的顺序从左往右为 $[1,2,3,4,5,6,7]$。在这一过程的第一步过后，顺序变为 $[1,5,4,3,2,6,7]$。在这一过程的第二步过后，顺序变为 $[1,5,7,6,2,3,4]$。再重复这两个步骤各一次可以得到样例的输出。 

### 测试点性质

- 测试点 $2-3$ 满足 $K\le 100$。
- 测试点 $4-13$ 没有额外限制。

## 样例 #1

### 输入

```
7 2
2 5
3 7```

### 输出

```
1
2
4
3
5
7
6```

# 题解

## 作者：Distorted_Fate_ (赞：4)

## 题解：P9951 [USACO20FEB] Swapity Swap B

找规律题。

题目分析：

给你一个序列，再给你两对起点和终点，把这两段先后反转，重复 $a$ 次。

如此，我们可以很快写出如下代码：
```cpp
while(k--) {//重复k次
	for(int i=a1,j=a2; i<=j; i++,j--) {
		swap(a[i],a[j]);//反转第一段
	}
	for(int i=b1,j=b2; i<=j; i++,j--) {
		swap(a[i],a[j]);//反转第二段
	}
}
```
然后你会发现超时了……
### 优化

多输出几个结果，观察一下。

![](https://cdn.luogu.com.cn/upload/image_hosting/7e7soarn.png)

可以清楚的发现，样例在循环四次后又回到原点，这就说明有大量无意义的循环导致程序时间超限。

知道问题就好解决了，找到数据的循环节，找到循环回到原点的次数，用 $k \bmod ok$ 即可。

```cpp
	while(f!=1) {//f用来判断是否相等，相等就结束
		f=1;
		for(int i=a1,j=a2; i<=j; i++,j--) {
			swap(a[i],a[j]);
		}
		for(int i=b1,j=b2; i<=j; i++,j--) {
			swap(a[i],a[j]);
		}
		for(int i=1; i<=n; i++) {
			if(a[i]!=b[i])f=0;
        		//这里其实还有一个方法，判断每个元素出现次数，然后求最小公倍数。
          		//不过比较麻烦，不做赘述
		}
		ok++;
	}
	k%=ok;//确保每步循环都是有意义的
	//代码可放心食用

```
然后你就 $AC$ 啦！

后记：这是我第一篇题解，有问题请大家指出，谢谢！

### 完结撒花！

---

## 作者：I_am_Tangser (赞：3)

这题就只是~~简单的~~找规律，为了不浪费广大管理员和读者的时间，我就直接说了——就是当转的次数达到一定的值的时候，就会变得跟原来一样，而题目中的样例的这个值，就是 $4$。所以我们可以先找到这个值（设这个值为 $c$），再计算一下 $k \bmod c$ 的值（也就是剔除多余的循环次数，保证剩下的每一次循环都是有价值的），最后再对剩下的有价值的循环次数进行模拟就可以了。

可是怎么证明这是正确的呢？

我们经过一次次的模拟可以发现，一个数字在转回到自己的位置是有一个周期的（各种各样，有 $1$、$2$、$3$ 等）那么想要每一个数字都转回到自己原来的位置，就一定需要一个数（也就是上文的那个一定的值 $c$），可以使得每一个数的周期刚好都到回到原来的位置上的时候，也就是使得 $c$ 是所有周期的公倍数，由于~~经过大量的枚举~~确定了每一个数字是一定有这样一个周期的，所以可以确定这样的 $c$ 一定存在，也就保证了这个序列一定可以在 $c$ 次操作后回到原来的样子（由于是根据周期的公倍数推的，所以其实也可以暴力枚举出每一个点的周期，再求出所有周期的最小公倍数，再取模）。

最后附上蒟蒻的正确代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,a1,a2,b1,b2,a[1919810],b[1919810],c,f=1;
int main(){
	for(int i=1;i<=100;i++)a[i]=i,b[i]=i;
	cin>>n>>k>>a1>>a2>>b1>>b2;
	while(f){
		c++;
		f=0;
		for(int i=a1,j=a2;i<j;i++,j--)swap(a[i],a[j]);
		for(int i=b1,j=b2;i<j;i++,j--)swap(a[i],a[j]);
		for(int i=1;i<=n;i++)if(b[i]!=a[i])f=1;
	}
	k%=c;
	while(k--){
		for(int i=a1,j=a2;i<j;i++,j--)swap(b[i],b[j]);
		for(int i=b1,j=b2;i<j;i++,j--)swap(b[i],b[j]);
	}
	for(int i=1;i<=n;i++)cout<<b[i]<<endl;
	return 0;
}
```

---

## 作者：Awatesolo (赞：1)

# Swapity Swap B 题解
总结：利用相同变换的**重复性**进行优化。
* 我们发现 $k\le10^9$，这表明暴力绝对过不了。
* 但如果某次变换成之前的样子，就表明已经完成了一个循环。
* 我们可以利用循环进行优化。
* 具体解释请看代码。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[105],b[105];
template<typename T>
inline void read(T &x) {
    x = 0;
    register char c = getchar();
    register short f = 1;
    while (c < '0' || c > '9') {
        if (c == '-') f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9') {
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }
    x *= f;
}
template <typename T, typename... Args>
inline void read(T &x, Args &...temps)
{
	read(x), read(temps...);
}
int n,m;
int a1,a2,b1,b2;
signed main(){
	read(n,m,a1,a2,b1,b2);
	for(int i=1;i<=n;i++) a[i]=b[i]=i;
	int op=0,f;
	for(int qw=1;qw<=m;qw++){
		reverse(a + a1, a + a2 + 1);//翻转函数
		reverse(a + b1, a + b2 + 1);
		f=1;
		for(int i=1;i<=n;i++){
			if(a[i]!=b[i]) f=0;//判断是否完成了一个循环
		}
		op++;
		if(f==1)
		{
			break;
		}
	}
	m=m%op;//把所有能走的循环一次走掉
	for(int qw=1;qw<=m;qw++){
		reverse(a + a1, a + a2 + 1);
		reverse(a + b1, a + b2 + 1);	
	}
	for(int i=1;i<=n;i++) cout<<a[i]<<endl;
	return 0;
}

```

---

## 作者：wwxxbb (赞：1)

当我第一次看到这个题目，想着每次翻转一下数组就好了，顺便用了`reverse`函数，注意区间是左开右闭，[结果](https://www.luogu.com.cn/record/149984734)~~超时了~~…
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,a1,a2,b1,b2;
int a[110];
int main(){
    cin>>n>>k>>a1>>a2>>b1>>b2;
    for(int i=1;i<=n;i++)a[i]=i;
    while(k--){
        reverse(a+a1,a+a2+1);
        reverse(a+b1,a+b2+1);
    }
    for(int i=1;i<=n;i++)cout<<a[i]<<'\n';
    return 0;
}
```
---
那我们该怎么办呢？在模拟的时候，我想到了，会不会经过多次翻转，使数组变回原数组。其实是会的，一个数字在转回它的原位置是有一个周期的，每个数都会。所以我们要求出满足每个数都能转回原位置的所有周期的最小公倍数 $t$，这样我们模拟的时候只需要将 $k\bmod t$ 即可。

怎么实现呢？只需要一个辅助数组，让它等于原数组，然后不断模拟直到两个数组相等为止。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,a1,a2,b1,b2,t,f;
int a[110],b[110];
int main(){
    cin>>n>>k>>a1>>a2>>b1>>b2;
    for(int i=1;i<=n;i++)a[i]=b[i]=i;
    while(!f){
        t++,f=1;
        reverse(a+a1,a+a2+1);
        reverse(a+b1,a+b2+1);
        for(int i=1;i<=n;i++)if(a[i]!=b[i])f=0;
    }
    k%=t;//优化
    while(k--){
        reverse(a+a1,a+a2+1);
        reverse(a+b1,a+b2+1);
    }
    for(int i=1;i<=n;i++)cout<<a[i]<<'\n';
    return 0;
}
```

---

## 作者：ni_ju_ge (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P9951)/[更好的阅读体验](https://www.cnblogs.com/ni-ju-ge/p/18593644)
## 思路
注意到 $1\le K\le 10^9$，暴力显然会超时。

将每次操作后的数列输出出来，发现会在一定次数的翻转后，重新回到初始数列。

$1\le N\le 100$，循环节一定不会太长，所以暴力处理循环节长度即可。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,lo,k,l1,l2,r1,r2,b[114];
bool fl;
int main() {
	cin>>n>>k;
	cin>>l1>>r1>>l2>>r2;
	for(int i=1; i<=n; i++)b[i]=i;//初始化
	while(!fl) {
		fl=true;
		for(int i=l1,j=r1; i<j; i++,j--)swap(b[i],b[j]);
		for(int i=l2,j=r2; i<j; i++,j--)swap(b[i],b[j]);
		for(int i=1; i<=n; i++) {
			if(b[i]!=i)fl=false;
		}
		lo++;//循环节长度加一
		if(lo==k)break;//循环节长度超过 k 时，继续计算已经没有意义了
	}
	k%=lo;
	while(k--) {
		for(int i=l1,j=r1; i<j; i++,j--)swap(b[i],b[j]);
		for(int i=l2,j=r2; i<j; i++,j--)swap(b[i],b[j]);
	}
	for(int i=1; i<=n; i++)cout<<b[i]<<endl;
}
```

---

## 作者：cly312 (赞：0)

奶牛的排列经过 $x$ 次后会回到原来的位置，理解以下：$[a_1,a_2]$ 的牛翻转两次就会回到原来的位置，$[b_1,b_2]$ 的牛翻转两次也会回到原来的位置，所以原来奶牛的排列经过一定次数的旋转后一定会回到原来位置。

我们只要先模拟得出多少次后第 $i$ 位的奶牛会回到原来的位置，然后用总次数取模后再进行模拟即可。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int N,K,A1,A2,B1,B2,res[101];

int nex(int x){
	if(A1<=x&&x<=A2) x=A1+A2-x;
	if(B1<=x&&x<=B2) x=B1+B2-x;
	return x;
}
int main(){
	cin>>N>>K>>A1>>A2>>B1>>B2;
	for(int i=1;i<=N;++i){
		int p=1,cur=nex(i);
		while(cur!=i){
			p++;
			cur=nex(cur);
		}
		int k=K%p;
		for(int j=0;j<k;++j)cur=nex(cur);
		res[cur]=i;
	}
	for(int i=1;i<=N;++i) cout<<res[i]<<'\n';
}
```

---

## 作者：__rnfmabj__ (赞：0)

## 题目大意
[题目传送门](https://www.luogu.com.cn/problem/P9951)

给定一段长度为 $n$ 的数组，其中 $x_i=i$，再给定 $a_1,a_2,b_1,b_2$，每次操作先将 $a_1\cdots a_2$ 区间翻转，再将 $b_1\cdots b_2$ 区间翻转，求 $k$ 次操作后数组的样子。
## 思路分析
比较显然的是，这个数组在经历过 $x$ 次操作后肯定会回到原来的状态。

可以感性理解一下，先将 $a_1\cdots a_2$ 翻转显然是一个循环的操作，循环两次就可以回到原来的状态，$b_1 \cdots b_2$ 显然也是循环两次的，两个循环的操作在经过这两次操作的最大公因数之后一定会回到原来的状态（就像阴历和阳历）。

知道这点之后，我们只需要将每次操作后得到的结果记录下来，然后设数组会循环 $x$ 次，则 $k \bmod x$ 就是我们要求的答案。
## code

```cpp
#include<bits/stdc++.h>
using namespace std;

int n,k,a1,a2,b1,b2;//作用如题面所说
int x,ans[10010][110];//ans是记录每次循环后数组的样子，x是会循环多少次
bool flag=1;//判断循没循环

int main(){
    cin>>n>>k>>a1>>a2>>b1>>b2;
    for (int i=1;i<=n;i++)ans[0][i]=i;//记录刚开始数组的样子
    while (flag){
        x++;//又循环了一次
        flag=0;
        for (int i=1;i<=n;i++)ans[x][i]=ans[x-1][i];//从上一次的数组的基础上再操作
        for (int i=0;i<(a2-a1+1)/2/*看不懂可以自己模拟一下*/;i++)swap(ans[x][a1+i],ans[x][a2-i]);//交换a1...a2
        for (int i=0;i<(b2-b1+1)/2;i++)swap(ans[x][b1+i],ans[x][b2-i]);交换b1...b2
        for (int i=1;i<=n;i++)if(ans[x][i]!=i){flag=1;break;}
        //如果和原数组一样，说明循环了，直接退出
        //如果和原数组不一样，说明每循环，继续操作
    }
    for (int i=1;i<=n;i++)cout<<ans[k%x][i]<<'\n';//输出答案
    return 0;
}
```

---

## 作者：ZettaByte (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P9951)

### 题意

数列 $x$ 共有 $n$ 个数，一开始 $x_i=i$，要对它进行 $k$ 组翻转，一组翻转包含两次区间翻转，第一次翻转区间 $[a_1,b_1]$，第二次翻转区间 $[a_2,b_2]$，最后请你输出数列 $x$。

### 解法

很明显我们无法直接暴力地翻转，因为这样复杂度为 $\Theta(nk)$，而 $k\le 10^9$，会 TLE。

经过对样例进行更多次的翻转，我们发现数列的翻转是存在周期的，而对于样例，我们进行 $4$ 组操作后就能将数列变回原样。

可以证明翻转一定存在周期。

#### AC CODE：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, a[110], b[110];
bool check()
{
	int flag = 1;
	for (int i = 1; i <= n; i++)
		if (a[i] != b[i]) flag = 0;
	return flag;
}

int main()
{
	int k, cnt = 0, l1, r1, l2, r2; scanf("%d%d%d%d%d%d", &n, &k, &l1, &r1, &l2, &r2);
	for (int i = 1; i <= n; i++) a[i] = b[i] = i;
	do reverse(b + l1, b + r1 + 1), reverse(b + l2, b + r2 + 1), cnt++; while (!check());
	k %= cnt; while (k--) reverse(a + l1, a + r1 + 1), reverse(a + l2, a + r2 + 1);
	for (int i = 1; i <= n; i++) printf("%d\n", a[i]);
	return 0;
}
```

---

## 作者：卷王 (赞：0)

## 思路

这是一道找规律题。

$k$ 是 $10^9$，是不可以暴力的，于是想到可以找循环节，直接模拟即可。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
//#define int long long
typedef long long ll;
typedef pair<int, int> pr;
#define up(i, l, r) for(int i = (l); i <= (r); i++)
#define down(i, r, l) for(int i = (r); i >= (l); i--)
const int mod = 1000000007;
const int base = 2333;
const double eps = 1e-6;

inline int read() {
	int x = 0, f = 1; char ch = getchar();
	while(ch < '0' || ch > '9') { if(ch == '-') f = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9') { x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar(); }
	return x * f;
}

int n, m, k, Q, T, _, ans = 0;
int l1, r1, l2, r2;
int a[107], b[107];

signed main() {
	n = read(), k = read();
	l1 = read(), r1 = read(), l2 = read(), r2 = read();
	int num = 0;
	for(int i = 1; i <= n; i++) a[i] = i, b[i] = i;
	while(1) {
		num++;
		reverse(a + l1, a + r1 + 1);
//		cout << "num : " << num << "\n";
//		for(int i = 1; i <= n; i++) cout << a[i] << " ";
//		cout << "\n";
		reverse(a + l2, a + r2 + 1);
//		cout << "num : " << num << "\n";
//		for(int i = 1; i <= n; i++) cout << a[i] << " ";
//		cout << "\n";
		if(num == k) {
			up(i, 1, n) {
				printf("%d\n", a[i]);
			}
			return 0;
		}
		bool flag = 1;
		for(int i = 1; i <= n; i++)
			if(a[i] != b[i]) flag = 0;
		if(flag) break;
	}
	k = k % num;
	while(k--) {
		reverse(b + l1, b + r1 + 1);
		reverse(b + l2, b + r2 + 1);
	}
	up(i, 1, n) printf("%d\n", b[i]);
	return 0;
}
```

---

## 作者：ymyctsz (赞：0)

[题目](https://www.luogu.com.cn/problem/P9951)

模拟题。

[暴力 58，试过了。](https://www.luogu.com.cn/record/142562184)
## 概要题意：
其实就是将长度为 $ N $ 且 $ N_i=i $ 的序列上的两段序列分别翻转，并重复 $ K $ 次，输出翻转后的序列。

## Part 1
思路：

假设 $ A_1 ...A_2 $ 与 $ B_1 ...B_2 $ 的中点分别为 $ mid_1 $ 与 $ mid_2 $，则有以下情况：
 
 - 设 $ A_1 ...A_2 $ 与 $ B_1 ...B_2 $ 范围为集合 $ A $ 与 $ B $，若 $ A\cap B=\varnothing $ 或 $ A\subseteq B $ 或 $ B\subseteq A $ 则每 $ 2 $ 次翻转序列恢复（为没有公共部分或者一个为另一个的子序列）。
 
 比较容易想，就不放图了。
 
 - $ mid_1\le B_1 $ 且 $ A_1\le mid_2 $ 则有如图：
 
![2.jpg](https://s2.loli.net/2024/01/13/xsgw6FoukOcaNQP.jpg)

 由于翻转可视为每个数与该序列到中点长度相同数进行交换，的我们则可以将他们分成 $ 5 $ 部分，即 $ x1,x2,x3,x4,x5 $（$ x1,x3,x5 $ 等长，为 $ A_1...A_2 $ 与 $ B_1 ...B_2 $ 的重叠部分长度 $ x2,x4 $ 为独立部分只受自身翻转影响）令其“位置”为 $ 1,2,3,4,5 $。 
 
如题意模拟：

![360截图20240114095837878.jpg](https://s2.loli.net/2024/01/14/nWtNmZLuyE147GX.jpg)

经过 $ 6 $ 次序列恢复。将各个部分拆分（图中 $ k1 $ 为题意中第一次翻转，$ k2 $ 为题意中第二次翻转后的位置以及头尾顺序结果）：

![360截图20240113214317657.jpg](https://s2.loli.net/2024/01/13/x5RIZM1oBKTQ7m6.jpg)

![360截图20240113214400968.jpg](https://s2.loli.net/2024/01/13/qJWjvTGSMmnKocQ.jpg)

![360截图20240113214744392.jpg](https://s2.loli.net/2024/01/13/QW7DH8uA2pYOm5z.jpg)

![360截图20240113214913913.jpg](https://s2.loli.net/2024/01/13/y1c7apX5PxI8zZq.jpg)

![360截图20240113215045144.jpg](https://s2.loli.net/2024/01/13/r7CNZKOGTgU59FB.jpg)


发现其每个部分经过一定次数必能回到原来“位置”。那么这个“结论”是否适用于其他情况？

- $ B_1<mid_1 $ 且 $ A_1<mid_2 $ 则有如图（其余假设与上相同）：

![360截图20240114095850916.jpg](https://s2.loli.net/2024/01/14/WYSIcRTHy2EloQv.jpg)

如题意模拟：

![360截图20240114104721651.jpg](https://s2.loli.net/2024/01/14/Cv9HpxVwZ78dq25.jpg)

经过 $ 12 $ 次序列恢复。各部分 $ 2 $ 或 $ 3 $ 或 $ 4 $ 次回到原来“位置”（$ x4 $ 两次，$ x1,x3,x5 $ 三次，$ x2,x6 $ 四次）。

可总结：
```
	if(B1>=mid_1&&A2<=mid_2) k%=6;//具有对称性，与 A1...A2，B1...B2 前后无关。
	else if((B1<=mid_1&&A2<=mid_2)||(A2>=mid_2&&B1>=mid_1)) k%=12;//重复的不用执行了。
```


- 但当 $ B_1<mid_1 $ 且 $ mid_2<A_1 $ 则有如图：

![360截图20240114103218693.jpg](https://s2.loli.net/2024/01/14/tSJjBMqOeLYFW4l.jpg)

如果按照上面的思路，会发现序列会产生很多的部分，这就导致结论没有普遍性（假了）。

[但是凭借如此可以拿 79。](https://www.luogu.com.cn/record/142558143)

## Part 2
但是！我们可以知道上面的序列恢复的次数，这个次数刚刚好是 $ A_1 ...A_2 $ 与 $ B_1 ...B_2 $ 中所有数回到原位置的最小次数的最小公倍数。

所以我们可以先每个数回到原位置的最小次数及最小公倍数算出来，再将 $ K $ 取模，减少重复次数，最后如题模拟，并输出。

[提交记录](https://www.luogu.com.cn/record/142727943)

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,r,l,z,y,k=1,tot,t=0,f[101],b[101];
void s(int x,int y) {for(int j=x,k=y;j<k;j++,k--) swap(f[j],f[k]);}//翻转操作。
void d() {for(int i=1;i<=n;i++) f[i]=i;}//初始化与还原序列。
int main() 
{
	scanf("%d%d%d%d%d%d",&n,&m,&l,&r,&z,&y);
	tot=r-l+y-z+2-max(0,r-z+1);d();
	if((z<=l&&y>=r)||(l<=z&&r>=y)) tot=max(r,y)-min(l,z)+1;//tot求的是A_1 ...A_2，B_1 ...B_2中有多少个数。
	for(int i=1;;i++)
	{
		s(l,r),s(z,y);
		for(int j=1;j<=n;j++) if(((j>=l&&j<=r)||(j>=z&&j<=y))&&f[j]==j&&b[j]==0)b[j]=i,tot--;//判断是否在 A_1 ...A_2，B_1 ...B_2 中，是否第一次翻转到原来位置。
		if(tot==0) break;//所有数回到原位置的最小次数都求出来了，退出。
	}
	for(int i=1;i<=n;i++) if(b[i]!=0) k=k*b[i]/__gcd(k,b[i]);//恢复序列的最小次数。
	m%=k;d();
	for(int i=1;i<=m;i++) s(l,r),s(z,y);
	for(int i=1;i<=n;i++) printf("%d\n",f[i]);
	return 0;
}
```
感谢管理员的付出！

有错请指出！
蒟蒻第一篇题解，求通过！

---

## 作者：FlyPancake (赞：0)

## [P9951 [USACO20FEB] Swapity Swap B](https://www.luogu.com.cn/problem/P9951) 题解

~~竟然还没人发过题解！！！~~

一道挺不错的思维题。

## Ideas

因为 $1 \le K \le 10^9$，所以暴力肯定过不了。

手推几个数据可以看出，重复反转 $cnt$ 次后一定可以回到原位。所以只要先求出 $cnt$ 的值，然后 $K \leftarrow K \bmod cnt$，也就是剔除重复操作，再执行 $K$ 次操作就行了。

## Code

```
#include <bits/stdc++.h>
using namespace std;

int t[105], now[105];
int a1, a2, b1, b2; 

bool is_ok(){
    for(int i=a1; i<=a2; i++)
        if(t[i] != now[i]) return false;
    for(int i=b1; i<=b2; i++)
        if(t[i] != now[i]) return false;
    return true;
}

int main(){
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int n, k; cin>>n>>k;
    for(int i=1; i<=n; i++) t[i] = i, now[i] = i;
    cin>>a1>>a2>>b1>>b2;
    int cnt = 0;
    while(cnt<=k){
        reverse(now+a1, now+a2+1);
        reverse(now+b1, now+b2+1);
        cnt++;
        if(is_ok()) break;
    }
    k %= cnt;
    while(k--){
        reverse(t+a1, t+a2+1);
        reverse(t+b1, t+b2+1);
    }
    for(int i=1; i<=n; i++) cout<<t[i]<<"\n";
    return 0;
}
```


---

