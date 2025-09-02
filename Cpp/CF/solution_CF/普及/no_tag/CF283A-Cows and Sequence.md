# Cows and Sequence

## 题目描述

Bessie and the cows are playing with sequences and need your help. They start with a sequence, initially containing just the number 0, and perform $ n $ operations. Each operation is one of the following:

1. Add the integer $ x_{i} $ to the first $ a_{i} $ elements of the sequence.
2. Append an integer $ k_{i} $ to the end of the sequence. (And hence the size of the sequence increases by 1)
3. Remove the last element of the sequence. So, the size of the sequence decreases by one. Note, that this operation can only be done if there are at least two elements in the sequence.

After each operation, the cows would like to know the average of all the numbers in the sequence. Help them!

## 说明/提示

In the second sample, the sequence becomes ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF283A/56857d21d773e19700b8e6f134c0c7d8dc59ae9f.png)

## 样例 #1

### 输入

```
5
2 1
3
2 3
2 1
3
```

### 输出

```
0.500000
0.000000
1.500000
1.333333
1.500000
```

## 样例 #2

### 输入

```
6
2 1
1 2 20
2 2
1 2 -3
3
3
```

### 输出

```
0.500000
20.500000
14.333333
12.333333
17.500000
17.000000
```

# 题解

## 作者：__UrFnr__ (赞：1)

**题目思路**：

这道题暴力显然行不通，我们可以换种思路进行操作：

* 对于操作一，我们可以重新定义一个标记数组 $fl$，进行操作时 $fl_x+y$，这样就相当于把 $a_1\sim a_x$ 都加上 $y$，这样可以优化一下。
* 操作二，在序列末尾加上 $x$，最后算平均值。
* 操作三，将序列数字总和减去最后一个数字及标记，再将 $fl_x$ 转移至 $fl_{x-1}$，再求出序列的平均值。

给一下核心代码：


```cpp
while (n --) {
	cin >> opt;
	if (opt == 1) {
		cin >> a >> b;
		fl[a] += b;
		ans += a * b;
	} else if (opt == 2) {
		cin >> a;
		a[++ top] = a;
		ans += a;
	} else {
		ans -= a[top] + fl[top];
		fl[top - 1] += fl[top];
		a[top] = 0, fl[top] = 0, top --;
	}
	printf ("%.10lf\n", ans * 1.0 / top);
} 
```

---

## 作者：wmrqwq (赞：1)

# 原题链接

[CF283A Cows and Sequence](https://www.luogu.com.cn/problem/CF283A)

# 题目简述

给定一个初始为空的序列 $a$，并给出 $3$ 种操作方式：

1. 将 $a_1 \sim a_x$ 均加上 $y$；

2. 将 $a$ 序列末尾增加一个正整数 $x$；

3. 将 $a$ 序列的最后一个数字给去掉；

现在要求你求出进行每一次操作后的序列 $a$ 的所有数的平均数。

# 解题思路

首先，这道题直接暴力模拟肯定是不行的，所以稍微思考一下，就会发现，这一道题可以通过标记的方法来做，并将每种操作的方法变通一下，所以，我们对于第 $i$ 种操作：

1. 重新定义一个标记数组 $pd$，将 $pd_x$ 加上 $y$，但如果第 $x$ 项被清除了该怎么办呢？其实，只需要将 $pd_x$ 转移至 $pd_{x-1}$ 就可以了，因为操作的时候，是将 $a_1 \sim a_x$ 均加上 $y$，所以，这样写的话，最终的结果是不会变化的；

2. 直接将序列末尾加上 $x$，然后计算平均数即可；

3. 对于这一步，我们可以先将序列数字总和减去最后一个数字的最初值以及标记，然后再将 $pd_x$ 转移至 $pd_{x-1}$，最后再求出整个序列的平均数即可。

# 参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define QwQ return 0;
long long gs=1,sz[1000010],pd[1000010],ans,n,opt,a,b;
int main()
{
	cin>>n;
	while(n--)
	{
		cin>>opt;
		if(opt==1)
			cin>>a>>b,pd[a]+=b,ans+=a*b;//将答案加上将每个数字加上的数字总和，注意，这里需要标记一下
		else if(opt==2)
			cin>>a,sz[++gs]=a,ans+=a;//这里直接模拟删除序列中的最后一个数字
		else
			ans-=sz[gs]+pd[gs],pd[gs-1]+=pd[gs],sz[gs]=0,pd[gs]=0,gs--;//这里注意要将最后一个数字的初始值以及标记归零
		cout<<fixed<<setprecision(10)<<1.0*ans/gs<<endl;//输出序列所有数字的平均数
	}
	QwQ;
} 
```


---

## 作者：OIerZhao_1025 (赞：0)

## [题目传送门]()

## 思路
因为你可以对这个序列进行 $n$ 次操作，每个操作都是下列三种类型之一：
- $1\ a\ x$ 表示将整数 $x$ 加到序列的前 $a$ 个元素中。
- $2\ k$ 表示在序列的末尾追加整数 $k$，使序列的元素个数增加 $1$。
- $3$ 表示删除序列的最后一个元素（当序列中至少有两个元素时）。

所以这道题明显不能暴力啊，直接就会 TLE 掉（别问我怎么知道的）。这里可以重新定义几个数组，用来优化一下，再求一下平均值。
## code
```cpp
        if(t==1)//操作1
        {
            f[a]+=x;
            sum+=a*x; 
   		}
    	else if(t==2)//操作2
    	{
            num[cnt++]=k; 
            sum+=k;
        }
        else if(t==3)//操作3
        {
            if(cnt>=2)
            {
                sum-=f[cnt]+num[cnt]; 
                f[cnt-1]+=f[cnt];
                f[tot--]=0;
            }
        }
```

---

## 作者：RioFutaba (赞：0)

## 题意
有 $n$ 次操作和初始只有一个 ${0}$ 的序列，每次给定 $t_i$ 代表操作编号，编号对应的操作如下：
1. 给序列的前 $a_i$ 个数加上 $x$。
2. 往序列尾端添加一个数 $x_i$。
3. 删除序列最后一个数（只有序列有至少 $2$ 个数时才能进行此操作）。

每次操作结束后输出序列中所有数的平均值（保留十位小数）。

数据范围：$1 \le n \le 2 \times 10^5$，$|x_i|,|k_i| \le 10^3$。
## 思路
思路参考 @QwQ_wangmarui_QwQ。

首先开一个数组 $num$ 模拟序列的添加和删减，再用一个变量 $sum$ 记录整个序列所有数的和。

对于加减操作，暴力处理会超时。那么可以开一个 $f$ 数组，$f_i$ 代表序列 $[1,i]$ 的加减情况。如将前 $3$ 个数加上 $5$，那么将 $f_3$ 加上 $5$ 即可。注意此时只需要保证 $num_{cnt}$ 的加减幅度正确即可（$cnt$ 为当前序列中数的数量），因为删除操作只会影响最后一个数。删除前需要将 $f_{cnt}$ 转移到 $f_{cnt-1}$。

转移方程为：$f_{cnt-1}=f_{cnt-1}+f_{cnt}$，代表将在 $[1,cnt]$ 内的加减操作加到 $num_{cnt-1}$ 内。
 
 理解思路后代码就很好写了：
 
 ```cpp
#include <bits/stdc++.h>
using namespace std;

const int maxn=2e5+5;
int n,f[maxn],tot,num[maxn];
double sum; //平均数有可能是小数
int main(){
	scanf("%d",&n);
	f[++tot]=0; //序列中有一个初始的0
	while(n--){
		int t;
		scanf("%d",&t); //操作序号
		if(t==1){
			int a,x;
			scanf("%d%d",&a,&x);
			f[a]+=x; //给1~a加上x，此时只给第a个做操作，必要时再转移到前面
			sum+=a*x; //sum更新
		}else if(t==2){
			int k;
			scanf("%d",&k);
			num[++tot]=k; //根据题意模拟
			sum+=k; //sum更新
		}else if(t==3){
			if(tot>=2){
				sum-=f[tot]+num[tot]; //删除一个数，sum要减去这个数本身和它的加减幅度
				f[tot-1]+=f[tot]; //转移
				f[tot--]=0; //把最后一个数的数据清零，tot减一
			}
		}
		printf("%.10f\n",sum/tot); //操作完后输出平均值，保留十位小数
	}
	return 0;
}
```

---

## 作者：MattL (赞：0)

[洛谷链接](https://www.luogu.com.cn/problem/CF283A) & [原题链接](https://codeforces.com/problemset/problem/283/A)

不是骗人，真的很水！

~~看到一周咕值掉9分暴躁了~~

---

**题意**

有三个操作，问你每次操作后的所有数字平均值。
1. 为前若干个增加某个数值
2. 删除最后一个数
3. 在最后增加一个数

---

**思考**

第一眼看到：这不就是树状数组吗？

想了想，好像更简单。

于是发现不同的特性：
1. 区间查询必定从1开始
2. 加数删数全在最后
不用树状数组！

---

**解题**

主要有4个值
1. `cnt` 数的总数
2. `num[]` 数的原始数值
3. `s[]` 每个数的标记（未叠加，只有最后一个叠加了）
4. `sum` 目前总和

切入点：由于区间修改必是前缀，所以标记可以永久往前传。

所以只用一边修改一边往前传标记即可。

---

**代码**

~~超短！~~

短的技巧见代码注释。

```cpp
#include<bits/stdc++.h>
using namespace std;


const int N=2e5+100;
long long cnt=1,num[N],s[N],sum,n,opt,x,y;
int main()
{
	cin>>n;
	while(n--)//直接这样作循环条件非常方便
	{
		cin>>opt;
		switch(opt)//多操作用switch!记住写break
		{
			case 1:cin>>x>>y,s[x]+=y,sum+=x*y;break;//修改
			case 2:cin>>x,num[++cnt]=x,sum+=x;break;//加数
			case 3:sum-=num[cnt]+s[cnt],s[cnt-1]+=s[cnt],num[cnt]=s[cnt--]=0;//删数，最后一个case不用写break
		}
		printf("%.6lf\n",1.0*sum/cnt);//其实可以直接用小数，但是.6lf更严谨，记住乘上1.0
	}
	return 0;
} 
```

---

## 作者：EAlivn (赞：0)

**题目**

唯一需要注意的是:

操作 $1$ 的区间修改，由于查询的时候只会查询最后一个元素并且区间总是从$1$开始

所以只需用一个 $s$ 数组进行维护就行

树状数组：

令 $c_i$ 为原数列，我们让 $s_i$ 为 $c_i$ 的差分数列即 $s_i=c_i-c_{i-1}$ 后 $s$ 的前 $i$ 项和为 $c_i$ 

对于区间 $x$ ~ $y $ 加 $w$ 的操作:

- update($x$,$w$);
- update($y+1$,$-w$);

仍不改变求和操作的正确性


```C++
#include<bits/stdc++.h>
using namespace std;
long long num[200010],s[200010];
long long sum=0,cnt=1;
long long read(){
	long long x;
	scanf("%lld",&x);
	return x;
}
int main() {
	num[1]=0;
	long long T=read();
	while(T--) {
		long long way=read();
		if(way==1) {
			long long x=read(),y=read();
			s[x]+=y;
			sum+=x*y;
		} else if(way==2) {
			long long x=read();
			sum+=x;
			cnt++;
			num[cnt]=x;
		} else {
			sum=sum-num[cnt]-s[cnt];
			num[cnt]=0;
			cnt--;
			s[cnt]+=s[cnt+1];
			s[cnt+1]=0;
		}
		printf("%.6f\n",1.0*sum/(1.0*cnt)); //printf %lf 默认输出6位小数，但是这样逻辑性更强 
	}
}

```




---

## 作者：E1_de5truct0r (赞：0)

## 前言 & 题外话

2022-07-22 20:22 upd：有个地方忘了加 LaTeX，还把 j 打成 i 了

---

这道题做得异常艰难，写一篇题解纪念一下。

- 一开始题目错了，然后粉兔光速回帖Orz

- 我总觉得这个有性质可以找，就一直在想一些特殊性质，比如 $1 \oplus 2 \oplus ... \oplus 2^m-1 = 0$ 这种，于是不出意外的没思路。（（

## 思路

>注明：本文中 $\oplus$ 表示异或，即 C++ 中的 `^` 符号。

不知怎么就突然想到了类似前缀和的“前缀异或”操作。即令 $c_i = \oplus_{j=1}^{i} a_j$。如果我们让 $a_l \oplus \cdots \oplus a_r = 0$，我们就直接让 $c_{l-1} \oplus c_r = 0$ 即可。

由此，得到一个结论：$c$ 数组中的数字**两两不同**。

而我们发现对于每一个 $c$ 数组，只要知道了 $c_{i-1}$ 和 $a_1 \cdots a_{i-1}$，$a_i$ 就是唯一的。所以我们递推地去找，一个 $c$ 数组**对应且只会对应一个 $a$ 数组**。
所以要求 $a$ 数组的个数，**转化为求 $c$ 数组个数**。

而 $c$ 数组个数很好求，因为要求各个数字两两不同，所以根据乘法原理我们得到方案数：

$$(2^m-1) \times (2^m-1-1) \times (2^m-1-2) \times \cdots \times (2^m-1-n)$$

这个其实就是 $A_{2^m-1}^{n}$（其实有了上面的式子就能做了）。用快速幂算出 $2^m-1$，然后 $O(n)$ 求解即可。时间复杂度 $O(\max(\log m,n)) \approx O(n)$。

## 代码

用了一个自己写的缺省源，有点长，只放核心代码：

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll mod=1e9+9;
ll pow1(ll b,int x) // 快速幂：求 b 的 x 次方
{
    ll base=b,ans=1;
    while(x) (ans*=((x&1)?base:1))%=mod,(base*=base)%=mod,x>>=1;
	return ans;
}
int main()
{
	// 快读快写省略了，有需要的可以去我小号 @Xaga 主页复制（实在是太长了……）
	int n,m,r; read(n,m);
	r=(pow1(2,m)-1+mod)%mod; // 算出 2 的 m 次方 -1
	ll ans1=1;
	for(int i=1;i<=n;i++) (ans1*=r--)%=mod; // 计算答案
	write(ans1);
	return flush(),0;
}
```

完结撒花~ qwq

---

