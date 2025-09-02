# Lucky Permutation Triple

## 题目描述

Bike is interested in permutations. A permutation of length $ n $ is an integer sequence such that each integer from 0 to $ (n-1) $ appears exactly once in it. For example, $ [0,2,1] $ is a permutation of length 3 while both $ [0,2,2] $ and $ [1,2,3] $ is not.

A permutation triple of permutations of length $ n $ $ (a,b,c) $ is called a Lucky Permutation Triple if and only if ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF303A/bd0aa9c2cfa6e7dfc9681d8813c19703f16dbc42.png). The sign $ a_{i} $ denotes the $ i $ -th element of permutation $ a $ . The modular equality described above denotes that the remainders after dividing $ a_{i}+b_{i} $ by $ n $ and dividing $ c_{i} $ by $ n $ are equal.

Now, he has an integer $ n $ and wants to find a Lucky Permutation Triple. Could you please help him?

## 说明/提示

In Sample 1, the permutation triple $ ([1,4,3,2,0],[1,0,2,4,3],[2,4,0,1,3]) $ is Lucky Permutation Triple, as following holds:

- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF303A/6124807a627fcd49ae8fab0d91c9fa90239af12b.png);
- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF303A/598c5f3180986ca384de6df51e7cb84d8ea4e757.png);
- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF303A/66b44a153ea212b6a13d195278ac6715ce383457.png);
- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF303A/dd4f61ae15bc4151613d0da9fe47b466aa949e1e.png);
- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF303A/0ea0fc069d3b3e3451d396fd4b6ef6f3d9456398.png).

In Sample 2, you can easily notice that no lucky permutation triple exists.

## 样例 #1

### 输入

```
5
```

### 输出

```
1 4 3 2 0
1 0 2 4 3
2 4 0 1 3
```

## 样例 #2

### 输入

```
2
```

### 输出

```
-1
```

# 题解

## 作者：_Chjich_ (赞：2)

# 题目大意
从 $0$ 到 $n-1$ 中找出能满足 
$a_i+b_i=c_i\bmod n$ 的三个序列。
# 解题思路
不难发现 $a_i+b_i=i\times2$ 则 $c_i=i\times2\bmod n$ 。

所以前两行直接输出 $0$ 到 $n-1$ 的数，第三行输出 $i\times2\bmod n$ 就行。

但如果找不到就输出 $-1$ 。 

首先 $a_i+b_i$ 不能是 $n$ 的倍数，因为：
$$0≡a_i+b_i\pmod n$$ 
不然 $c_i$ 就不能成立，所以 $i\times2$ 也不能是 $n$ 的倍数，并且 $i\times2$ 一定是偶数，所以 $n$ 也不是偶数。

# 上代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n;
	cin>>n;
	if(n%2==0){//排除偶数，因为无解。
	   cout<<-1;
	   return 0;
	}
	for(int i=0;i<n;i++) 
      cout<<i<<" ";
	cout<<endl;
	for(int i=0;i<n;i++) 
      cout<<i<<" ";
    cout<<endl;
	for(int i=0;i<n;i++) 
      cout<<i*2%n<<" ";
	return 0;
}
```

---

## 作者：DL_Lingkong (赞：2)

# CF303A Lucky Permutation Triple 题解

[题目传送门](https://www.luogu.com.cn/problem/CF303A)

一道很好的数学题。

别看这题很难，~~其实一点也不简单~~，其实很简单。

## 题目

bike 认为 $[0,n-1]$ 中的每个数出现一次为一个数列（长度为 $n$），三个长度为 $n$ 的数列，且![条件](https://codeforces.com/predownloaded/10/4a/104a8a429d0985a2c14e7bf3482a92b9c849276c.png)叫做幸运排列三元组，要你找出这样的三元组，若没有输出 $-1$，若有多种答案输出其中一个答案。

## 思路

首先思考：什么时候没有（输出 $-1$）？

当 $n$ 偶数的时候。

简单证明如下。

当 $n$ 为偶数时：

$$0 + 0 \equiv 0 \pmod {n}$$

$$\frac {n}{2} + \frac {n}{2} \equiv 0 \pmod {n}$$

得出：

$$x + x \equiv \frac {n}{2} + x + \frac {n}{2} + x \pmod {n}$$

有重复，必然不能涵盖 $[0,n - 1]$ 中的每个数，所以输出 $-1$。

而奇数就不一样了。

当 $n$ 为奇数时，$n - 1$ 和 $n + 1$ 必为偶数。

$$0 + 0 \equiv 0 \pmod {n}$$

$$1 + 1 \equiv 2 \pmod {n}$$

$$\cdots$$

$$\frac {n - 1}{2} + \frac {n - 1}{2} \equiv n - 1 \pmod {n}$$

$$\frac {n + 1}{2} + \frac {n + 1}{2} \equiv 1 \pmod {n}$$

可以看到，刚好把之前 $0,2,\dots$ 的“空缺”$1,3,\dots$ 补上了。

所以 $n$ 为奇数时一定有解。

接下来就是按照上面这些算式将 $i$ 带进去遍历 $[0,n - 1]$ 再计算 $(i + i) \bmod n$ 结果就好了。

## 上代码！

```cpp
#include <iostream>
using namespace std;
int n;
void be() // init & input
{
	cin >> n;
	return ;
}
void kin() // programming
{
	return ;
}
void ei() // output
{
	if(!(n & 1)) // 是偶数，无解
	{
		puts("-1");
		return ;
	}
	for(int i = 0;i < n;i++) // 如上所述，把i带进[0,n - 1]遍历
	{
		cout << i << " \n"[i == n];
	}
	for(int i = 0;i < n;i++)
	{
		cout << i << " \n"[i == n];
	}
	for(int i = 0;i < n;i++) // 计算 (i + i) % n
	{
		cout << (i * 2 % n) << " \n"[i == n];
	}
	return ;
}
int main()
{
	be();
	kin();
	ei();
	return 0;
}
```

---

## 作者：SpeedStar (赞：2)

#### 算法分析

首先$n$为偶数时必然无解，因为$n*(n-1)$与$n*(n-1)/2$模$n$不同余。

其次$n$为奇数时，$a$序列可以是$0,1,2,\cdots,n-1$，$b$序列可以是$1,2,3,\cdots,n-1,0$，而$c$序列可以通过$(a_i + b_i) \% n$算出来。


#### C++ 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

int main() {
	int n;
	cin >> n;
	
	if (~n & 1) {
		cout << "-1\n";
		return 0;
	}
	
	vector<int> a(n + 1), b(n + 1), c(n + 1);
	for (int i = 1; i <= n; ++i) a[i] = i - 1;
	for (int i = 1; i < n; ++i) b[i] = i;
	b[n] = 0;
	for (int i = 1; i <= n; ++i) c[i] = (a[i] + b[i]) % n;
	
	for (int i = 1; i <= n; ++i) cout << a[i] << " \n"[i == n];
	for (int i = 1; i <= n; ++i) cout << b[i] << " \n"[i == n];
	for (int i = 1; i <= n; ++i) cout << c[i] << " \n"[i == n];
	
	return 0;
}
```


---

## 作者：damage (赞：2)

# 题解

### 很容易注意到是```Special Judge```（不然怎么做）

~~好像输出一样的都可以~~

~~其实就是打表~~

注意到其实不管怎样都会只有三行输出，于是（前两行一样）

输出如下：

1. 第一行：$0$~$n$-$1$

2. 第二行：$0$~$n$-$1$，跟第一行一样

3. 第三行：对于第$i$个数（下标从$0$开始），输出为$2i\%n$，注意因为数字范围为$0$~$n$-$1$，所以记得$\%n$

但是很容易发现当$n$为偶数时肯定无解，所以代码就出来了

---

# 代码

```cpp
#include<stdio.h>
int n;
int main()
{
	scanf("%d",&n);
	if(!(n&1)) printf("-1\n"); //特判偶数，这里用的是位运算
	else
	{
		for(register int i=0;i<n;++i) printf("%d ",i); //输出0~n-1
		putchar('\n'); //记得回车
		for(register int i=0;i<n;++i) printf("%d ",i); //输出0~n-1
		putchar('\n'); //记得回车
		for(register int i=0;i<n;++i) printf("%d ",(i<<1)%n); //按上面第三步输出
	}
	return 0;
}
```

---

## 说明

关于本篇涉及到的位运算的讲解（其实就一个）

#### ```x&1```的返回值只有两种

1. 当$x$为奇数时，返回$1$

2. 否则返回$0$

此处就等于$x\%2$（或$x\%2==1$）

其实任何$x\%2^{i}$都可以转化为$x\&(2^{i}-1)$

---

## 作者：GreenMelon (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF303A)

这是一道很简单的橙题。

前两行只需从 $0$ 到 $n-1$ 逐个输出就行。而第三行，考虑如果 $n$ 为偶数，则：
$$ 0+0\equiv0\pmod n$$
$$ 1+3\equiv0\pmod n$$
$$\dots$$
$$ x+y\equiv0\pmod n$$
_注：在这里，$x$ 和 $y$ 都是偶数。_

会产生重复，所以要输出 `-1`。

而当 $n$ 为奇数，则：
$$0+0\equiv0\pmod {n}$$
$$1+1\equiv2\pmod n$$
$$\dots$$
$$(n-1)+(n-1)\equiv2(n-1)\ (\bmod\ n)$$
不会产生重复。

所以，如果 $n$ 为奇数，则 $c_i=(a_i+b_i)\bmod\ n$。

AC 代码：
```cpp
#include<iostream>
using namespace std;
int main(){
	int n;
	cin>>n;
	if(n%2==0){cout<<-1;return 0;}//特判
	for(int i=0;i<n;i++)cout<<i<<" ";
	cout<<endl;
	for(int i=0;i<n;i++)cout<<i<<" ";
	cout<<endl;
	for(int i=0;i<n;i++)cout<<(i+i)%n<<" ";
    return 0;
}
```


---

## 作者：_txb_ (赞：1)

## 思路
首先我们看 $n$ 为偶数时，一定不可以完成。然后我们就思考如何输出奇数的答案，第一二两行直接输出 0 到 $n-1$，因为 $n$ 是奇数，所以我们把一二两行加起来，也一定不会有重复，但答案会超过 $n$ 的值，所以我们要把一二两行加起来对 $n$ 取模。

贴代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n;
	cin>>n;
	if(n%2==0) cout<<-1;//偶数不行输出-1 
	else
	{
		//接下来就是打表 
    	for(int i=0;i<n;i++) cout<<i<<" ";//第一行 
    	cout<<endl;//换行 
    	for(int i=0;i<n;i++) cout<<i<<" ";//第二行
    	cout<<endl; 
    	for(int i=0;i<n;i++) cout<<i*2%n<<" ";//第三行
    	cout<<endl; 
	}
	return 0;
}
```


---

## 作者：very_easy (赞：1)

大水题。

## 思路
首先肯定有 Special Judge(?) 不然似乎没法做。

先考虑一下简单的情况，首先考虑前两个数，最简单的情况当然是两数相等啦，所以之接从 $0 \sim n$ 输出就行了。

之后来考虑第 $3$ 个数是什么。

先拿第一组样例举例，前两行依次应为：

```
0 1 2 3 4
0 1 2 3 4
```

先看第一组：

```
0
0
```
这个明显是 $0$。

第二组为：

```
1
1
```
$1+1$ 还没达到 $5$ 因此答案为 $1+1=2$。

第三组为：

```
2
2
```
$2+2$ 也没达到 $5$ 因此答案为 $2+2=4$。

之后是第四组：

```
3
3
```

和超过了 $5$ 先不管取余的事， $3+3=6$。

前几组答案为 $0,2,4,6$。

是不是看出规律了？

很明显，就是 $0 \times 2,1 \times 2,2 \times 2,3\times 2$，然后再对 $n$ 求余就可以。

再来看看无解的情况，来看看第二组样例。

还是一样的，前几组答案为：

```
0 1
0 1
```

直接看第二组，$1+1=2,2 \bmod 2=0$。

可见如果 $n$ 为偶数则无解。

那这道题就快乐的写完啦！

## 代码

```
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n;
	cin>>n;
	if(n%2==0){
		cout<<-1;
		return 0;
	}
	for(int i=0;i<n;i++) cout<<i<<" ";
	cout<<endl;
	for(int i=0;i<n;i++) cout<<i<<" ";
	cout<<endl;
	for(int i=0;i<n;i++) cout<<i*2%n<<" ";
	return 0;
}
```

---

## 作者：XL4453 (赞：1)

### 解题思路：

先大胆猜测一下，当且仅当 $n$ 为奇数的时候有解。~~然后交了一发过了，于是下一题。~~

-----

给出一个感性的证明：

首先证明充分性，也就是 $n$ 为奇数的时候有解。考虑这样构造，第一组数和第二组数都是从 $0$ 直接排到 $n-1$，第三组数则是前两组的和取模。第一组和第二组显然满足条件，只要证明第三组也是 $0$ 到 $n-1$ 的一个就行了。

发现第三组数其实是一个从零开始，公差为 $2$ 的等差序列，则对于第 $i$ 个数，有：$a_i=2\times (i-1)$，这样的话，对于第 $\dfrac{n+1}{2}+1$ 个数，其值为 $n+1$，对于 $n$ 取余后得到 $1$，结合之前提到的公差为 $2$ 就行了。 

----
然后证明必要性，即 $n$ 为偶数时一定无解。设 $k=\dfrac{n}{2}$，则上面两列的和为 $2k\times(2k+1)$，对于 $n$ 取余为 $0$，而下面一列的和为 $k\times (2k+1)=2k\times k +k$，对于 $2k$ 取模的结果为 $k$，两者显然不等。


-----
### 代码：

```cpp
#include<cstdio>
using namespace std;
int n;
int main(){
	scanf("%d",&n);
	if(!(n&1)){
		printf("-1");
		return 0;
	}
	for(int i=0;i<=n-1;i++)
	printf("%d ",i);
	printf("\n");
	for(int i=0;i<=n-1;i++)
	printf("%d ",i);
	printf("\n");
	for(int i=0;i<=n-1;i++)
	printf("%d ",(i*2)%n);
	return 0;
}
```


---

## 作者：hexuchen (赞：0)

无人区写题解的第五天

[题目传送门](https://www.luogu.com.cn/problem/CF303A)

[更好的阅读体验？](https://www.luogu.com.cn/blog/945742/solution-cf303a)

## 题目意思

给出一个数 $n$，求能不能产生 $3$ 个排列。排列要求是第一个排列加第二个排列除以 $n$ 的余数要等于第三个排列除以 $n$ 的余数。

## 思路分析

很容易发现 $n$ 为偶数的时候无解。


接着，我们仔细分析就会发现：前两个排列怎么样好像都可以（只要大于 $0$ 而且小于 $n$），只要第三个排序是前两者之和 $\bmod  n$ 的余数就好了。

所以我们可以将前两个排序设为 $0$ 到 $n - 1$，第三个排序设为前两者之和 $\bmod n$ 就好了。

## AC 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
int main(){
	cin>>n;
	if(n%2==0){ //如果为奇数则无解
		cout<<-1;
		return 0;
	}
	for(int i=1;i<=3;i++){ //枚举三列
		for(int j=0;j<n;j++){ 
			if(i!=3) //如果不是第三列
				cout<<j<<" ";
			else
				cout<<j*2%n<<" "; //第三列的情况
		}
		cout<<endl; //记得换行
	}
	return 0;
}
```

---

## 作者：fish_love_cat (赞：0)

可以发现 $n \bmod 2=0$ 时一定无解。

在保证 $n$ 是奇数的前提下，第一行和第二行都只需要输出 $0$ 到 $n-1$ 的序列，第三行就输出两者的和取余 $n$ 后的结果。因为 $n$ 是奇数，所以第三行不会出现重复。

**代码：**

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n;cin>>n;
	if(!(n&1)) puts("-1");//无解
	else{//方案
    	for(int i=0;i<=n-1;i++) cout<<i<<' ';
    	puts("");
    	for(int i=0;i<=n-1;i++) cout<<i<<' ';
    	puts("");
    	for(int i=0;i<=n-1;i++) cout<<i*2%n<<' ';
    	puts("");
	}
	return 0;
}
```

---

## 作者：Francium_ (赞：0)

# 题目大意  
有三个数列 $a$，$b$，$c$，构造出，$a$，$b$，$c$，使得对于每一个 $i$，都有 $a_i + b_i = c_i$。
# 思路
既然题目说每个元素都在 $0$到$n-1$ 的范围内，那就很容易构造出 $a$ 和 $b$（就是顺序输出，手动模拟一下，可以得到 $a_i+b_i=i \times 2$，还可以得到 $c_i=i \times 2  \bmod n$（$i$ 从 $0$ 开始）,首先，$a_i+b_i$ 一定是偶数，那 $n$ 就一定不是偶数，因为如果 $n$ 为偶数，那么 $c_i$ 就会全部为 $0$ ,不符合题意。然后根据前面提到的 $c_i=i \times 2  \bmod n$，就可以构造出 $c$。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
	int n;
	cin >> n;
	if (n % 2 == 0) { //n为偶数，无解。
		cout << -1;
		return 0;
	}
	for (int t = 1; t <= 2; t++) { //输出a，b
		for (int i = 0; i < n; i++)
			cout << i << " ";
		cout << endl;
	}
	for (int i = 0; i < n; i++) //注意！！！i要从0开始！！
		cout << i * 2 % n << " "; //模拟
	return 0;
}
```

---

