# Exactly N points

## 题目描述

[problemUrl]: https://atcoder.jp/contests/cf16-final/tasks/codefestival_2016_final_b

ある年のCODE FESTIVALの決勝では $ N $ 問の問題が出題されました。

$ i\ (1≦i≦N) $ 番目の問題の配点は $ i $ 点です。

高橋くんは、このコンテストでちょうど $ N $ 点を取りたいと思い、そのために解く問題の集合をどうするかを考えています。

配点が高い問題は難しいので、解く問題の配点のうちの最大値が最小になるようにしようと考えました。

高橋くんが解くべき問題の集合を求めてください。

## 说明/提示

### 制約

- $ 1≦N≦10^7 $

### 部分点

- $ 1≦N≦1000 $ を満たすデータセットに正解した場合は、$ 200 $ 点が与えられる。
- 追加制約のないデータセットに正解した場合は、上記とは別に $ 100 $ 点が与えられる。

### Sample Explanation 1

$ 4 $ 番目の問題のみを解いた場合もちょうど $ 4 $ 点が得られますが、$ 1,3 $ 番目の問題を解く方が配点の最大値が小さくなります。

### Sample Explanation 2

$ \{3,4\} $ という集合も考えられます。

## 样例 #1

### 输入

```
4```

### 输出

```
1
3```

## 样例 #2

### 输入

```
7```

### 输出

```
1
2
4```

## 样例 #3

### 输入

```
1```

### 输出

```
1```

# 题解

## 作者：ZolaWatle (赞：9)

## AT2129题解

题目大意：给一个正整数，把它分解成若干个**互不相同**的正整数的和，并输出。

------------

### 思路

令$ S $为从$ 1 $到$ k $的**所有自然数之和**（相当于一个等差数列）。

即：

$$ S=\frac{k\cdot (k+1)}{2} $$

这里有一个结论就是（归纳能力不好请见谅）：

**任何一个数都可以被表示为上述的$ S $减去任意一个在闭区间$ [1,k] $的自然数。**

当然，这里的$ k $是要与$ S $对应的。

下面我就举几个例子来看看：

当$ k=2 $时：

$$ 1+2=3 $$

$$ \ \ \ \ \ \ 2=2 $$

$$ 1\ \ \ \ \ \ =1 $$

同理，当$ k=3 $时：

$$ 1+2+3=6 $$

$$ \ \ \ \ \ \ 2+3=5 $$

$$ 1\ \ \ \ \ \ +3=4 $$

$$ 1+2\ \ \ \ \ \ =3 $$

很显然，这一段“$ 1+2\ \ \ \ \ \ =3 $”已经从$ k=3 $回到了$ k=2 $。

这样一来，我们把$ 1,2,3,4,5,6 $这些值都构造了出来，可以推理得知当$ k $的值增大时，这一理论依然成立。

------------

### 代码实现

首先来确定$ S $的具体值，这个好办，只需要求出比$ n $大的最小的$ S $值就可以了。

例如样例中的$ n=4 $，那么对应的$ S $值就应该是$ 1+2+3=6 $。

那如果$ n=6 $呢？求$ S $的这一过程其实已经把这道题给做完了，直接输出即可。

这个过程的代码如下：

```cpp
int k=1;
while(k*(k+1)/2<=n)  //这个式子表示S的值 
{	
	k++;  //满足条件，继续往大试探 
	if(k*(k+1)/2==n)  //如果S恰好等于n 
	{
		for(re i=1;i<=k;i++)
			std::cout<<i<<endl;
		return 0;  //直接输出1~k 
	}
}
```

------------

好了，由于我们已经推得了上述结论：

**任何一个数都可以被表示为上述的$ S $减去任意一个在闭区间$ [1,k] $的自然数。**

所以我们令一个变量$ s $代表退出循环时的$ k $所对应的$ S $的值。

然后从$ 1 $到$ k $一次枚举，从$ s $中扣除枚举到的数字，如果扣除后恰好等于$ n $，就输出。

这个过程的代码如下：

```cpp
s=k*(k+1)/2;  //计算出s的值 	
for(re i=1;i<=k;i++)  //依次枚举 
	if(s-i==n)  //如果恰好等于n 
	{
		for(re j=1;j<=k;j++)
			if(j!=i)  //被减去的不能输出 
				std::cout<<j<<endl;
		return 0;
	}

```

------------

### 完整代码：

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#define re register int
using namespace std;

int n,s,k=1,ans[1001];

int main()
{
	std::cin>>n;
	
	while(k*(k+1)/2<=n)
	{	
		k++;
		if(k*(k+1)/2==n)
		{
			for(re i=1;i<=k;i++)
				std::cout<<i<<endl;
			return 0;
		}
	}
	
	s=k*(k+1)/2;
	
	for(re i=1;i<=k;i++)
		if(s-i==n)
		{
			for(re j=1;j<=k;j++)
				if(j!=i)
					std::cout<<j<<endl;
			return 0;
		}
}
```

------------

如果有锅，欢迎评论区或私信指正 $QwQ$

---

## 作者：喵仔牛奶 (赞：5)

这能蓝？恶评吧 qwq

首先我们知道最大值为 $x$ 的元素互不相同的序列和最大值是 $\frac{x(x+1)}{2}$ 。这个值显然是单调的，我们可以二分它。然后一个递归反向输出即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n, l, r, ans;
void print(ll i) {
	if (i >= n) cout << n << '\n';
	else n -= i, print(i - 1), cout << i << '\n';
}
int main() {
	cin >> n, l = 1, r = n;
	while (l <= r) {
		ll mid = (l + r) / 2;
		if (mid * (mid + 1) / 2 < n) l = mid + 1;
		else ans = mid, r = mid - 1;
	}
	print(ans);
	return 0;
}
```


---

## 作者：Leonid (赞：2)

个人认为这道题不至于评到蓝，顶多一个绿。

首先看到题目求任意不同正整数和，容易想到等差数列公式：

$$\operatorname{Sum}=\dfrac{n \times (n+1)}{2}$$

令 $\operatorname{Sum}$ 为题目中的 $n$ ，问题变为求下列方程的最大正整数值：

$$n=\dfrac{x \times (x+1)}{2}$$

$x$ 的最大正整数值即为原问题要求若干个正整数中的最大值的最小值。

因为 $n \le 10^7$，所以可以考虑暴力求解方程。

剩下的值保证与其他数不同且不大于 $x$ 即可。

```cpp
#include<cstdio>
#include<bitset>

using namespace std;

#define M 10000005

int n;
int ans[M],tot;

int find(int x){
	int res=0;
	while(res*(res+1)/2<x) ++res;
	return res;
}

int main(){
	scanf("%d",&n);
	ans[++tot]=find(n);
//	printf("%d\n\n",ans[1]);
	n-=ans[1];
	while(n>0){
		if(n<ans[tot]) {
			ans[++tot]=n;
			break;	
		}
		else {
			ans[tot+1]=ans[tot]-1;
			++tot;
			n-=ans[tot];
		}
	}
	for(int i=tot;i>=1;--i) printf("%d\n",ans[i]);
	return 0;
}
```


---

## 作者：Cuiyi_SAI (赞：1)

这题看起来有挺多解法的，这里再来分享一种

## 题目大意

给定一个数 $n\ (n\le10^7)$，将 $n$ 表示为多个正整数的和，要求这些正整数互不相同且使得它们最大值最小。

## 解题思路


我们设 和为 $n$ 的所求正整数序列的最大值为 $x$ ，显然有 

$$
\dfrac{x(x+1)}{2}\ge n
$$

这是一个一元二次不等式，解得

$$
x\in\{x\le\dfrac{-\sqrt{1+8n}-1}{2}\cup x\ge\dfrac{\sqrt{1+8n}-1}{2}\}
$$

根据题目，$x$ 只能取正整数，且要求最大值最小。因此目标序列中的最大值 $x$ 为

$$
x=\left\lceil\dfrac{\sqrt{8n+1}-1}{2}\right\rceil
$$

现在我们再来考虑如何得到所求序列中的第二大正整数 $y$，可以发现它其实就是和为 $n-x$ 的正整数序列中的最大数，也就是说我们可以根据同样的公式通过 $n-x$ 得到 $y$。

$$
y=\left\lceil\dfrac{\sqrt{8(n-x)+1}-1}{2}\right\rceil
$$

以此类推，这就是一个递归过程，我们求出了最大的数 $x$，就可以根据 $n-x$ 状态转移求出第二大的数 $y$，然后根据 $n-x-y$ 可得第三大的数 $z$……

于是我们就得到了题目所求的整个序列。

## CODE

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,ans[1000010],tot=0;
signed main()
{
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin>>n;
  while(n)
  {
    double t=(sqrt((8*n*1.0+1)*1.0)-1)/2*1.0;
    int s=ceil((double)t);
    ans[++tot]=s;  //利用公式逐步得到序列元素
    n-=s  //状态转移
  }
  for(int i=tot;i>=1;i--) cout<<ans[i]<<'\n';  //因为要从小到大，所以倒序输出
  return 0;
}
```

## 评价与总结

自我感觉还算是个不错的思路吧，复杂度是 $\Theta(n)$ 的，跑出了 $55ms$ 的成绩。~~其实多用点代数性数学思维去思考题目还是狠不戳的~~。


---

## 作者：lilong (赞：0)

根据题意，很容易得知要使得它们的最大值最小，就要从最小的 $1$ 开始用。转化一下题意，不难发现，我们只需求出最小的 $k$，使得 

$$\ \sum_{i=1}^k i\ \ge n$$ 

于是思路便产生了：对 $1$，$2$，$3$，⋯$k$ 求和，直到上述式子成立。可以很容易地看出来一个规律：
$$( \ \sum_{i=1}^k i\ ) - n<k+1$$

根据这个规律，我们知道多出来的那一部分就存在于 $1-k$ 当中，所以输出时判断是否为多出来的那个数就可以了。

代码如下：
```cpp
#include <iostream>
#include <cstdio>
using namespace std;
int main()
{
	int n,t=0,k=0;
	cin>>n;
	for(int i=1;k<n;i++)
		t++,k+=i;
	k=k-n;
	for(int i=1;i<=t;i++)
		if(i!=k)
			cout<<i<<endl;
	return 0;
}
```


---

## 作者：Helium_Ship (赞：0)

题意：用一连串的正整数的和（可以不连续）表示出 $n$，使数列中最大的数尽可能小。

我们考虑当数列中最大的数为 $n$ 时，能表示的最大的数 $\frac{n\times(n+1)}{2}$，当这个数大于 $x$ 且最小时，这个数与 $x$ 的差不超过 $n$，因此我们只需要把 $1 \cdots n$ 中的一个数，即 $\frac{n\times(n+1)}{2}-x$ 拿掉即可。

代码实现如下：

```c
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n;
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin>>n;
	int i=1;
	while ((1+i)*i/2<n)i++;
	int k=(1+i)*i/2-n;
	for (int j=1;j<=i;j++)
		if (j!=k)
			cout<<j<<'\n';
	return 0;
}
```


---

## 作者：Mine_King (赞：0)

## 题目大意：

给你一个正整数 $n$，请你把 $n$ 拆成若干个互不相同的整数之和。

## 题解

我们设 $m=\frac{k(k+1)}{2}(k \in \mathbb{N}+)$，也就事 $[1,k]$ 内所有整数的和。可以证明对于任意一个正整数 $n$，都有$n=m-x$，其中 $x$ 是$[1,k]$ 中的一个整数。  

证明：  
假设我们找到了大于 $n$ 的最小的 $m$，那么我们可以认为 $n$ 是这 $k$ 个数中剔除若干个数组成的。  
再回过来，如果只剔除 $0$ 或 $1$ 个数，则可以构成 $m-1,m-2,m-3,\cdots,m-k$。而 $n$ 一定大于等于 $m-k$，否则就会找到一个更小的（至少少了一个 $k$）的 $m$。而 $m-1,m-2,m-3,\cdots,m-k$ 这些数中一定有一个等于 $n$，因为它们是**连续**的正整数。  
得证.

## 代码

由于 $m$ 增长比较快，所以可以直接枚举 $m$，再枚举删哪个数。

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,k;
int main()
{
	scanf("%d",&n);
	for(k=1;k*(k+1)/2<n;k++);
	for(int i=1;i<=k;i++)
		if(k*(k+1)/2-n!=i) printf("%d\n",i);
	return 0;
}
```

---

## 作者：221B (赞：0)

见到还没有人来写题解，本蒟蒻来水一发（逃
```cpp
#include<bits/stdc++.h>//万能头 
using namespace std;
int a[10000001];//注意数组开大点，坑了我几个点 
inline int read(){//快速读入，比scanf和cin都要快 
    int X=0,w=0; char ch=0;
    while(!isdigit(ch)) {w|=ch=='-';ch=getchar();}
    while(isdigit(ch)) X=(X<<3)+(X<<1)+(ch^48),ch=getchar();
    return w?-X:X;
}
inline void write(int x){//快写，比cout和printf也要快 
     if(x<0) putchar('-'),x=-x;
     if(x>9) write(x/10);
     putchar(x%10+'0');
}
int main(){
	int n=read()/*读入n*/,s=0;
	for(int i=1;i<=n;i++){
		a[i]=i;//将i储存在a数组中 
		s+=i;//将1~n加起来 
		if(s>n)//如果和大于n，就代表要找的数字已经到齐了 ，break 
		break;
	}
	int t=s-n;//将和与n的差算出 
	for(int i=1;i<=n;i++){
		if(a[i]){//以防没有读入的数组变量，相当于a[i]!=0 
			if(a[i]!=t){//在a数组中将t删去  ，剩下的数的和刚好等于n 
				write(a[i]);//输出 
				printf("\n");//AT的题要换行 
			}
		}
	}
	return 0;//养成好习惯 
}
```
补充一点，将1~n中的每一个数字储存起来，每个数字刚好只出现一次，因此不会有数字重复的现象

---

