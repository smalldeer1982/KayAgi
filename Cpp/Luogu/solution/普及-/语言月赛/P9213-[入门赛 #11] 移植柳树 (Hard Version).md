# [入门赛 #11] 移植柳树 (Hard Version)

## 题目背景

**本题与 Easy Version 题意完全相同，不同的地方仅在于数据范围和单个测试点内含有的测试组数量。**

HG 在上学的路上无聊的走着，看着这马路边的一排柳树，他的脑子里突然冒出了个奇怪的问题……

## 题目描述

假设总共有 $n$ 棵柳树，每一棵间隔都为 $x$。

现在他需要对这些树做一些操作，使得在「这 $n$ 棵树的起点不变」的同时，任意两棵树的间隔都为 $y$（$y > x$）。

他被允许做的操作如下；


- 移植树木：将一个位置的树木移到另一个位置上。

如果对「起点不变」这个概念有疑惑，可以参照「样例解释」中的图例。

显然操作是需要体力的，HG 想要让尽可能多的树维持原状。现在 HG 想知道，为了达成「任意两棵树的间隔都为 $y$」这个目标，他最多可以让多少棵树保持在原来的位置。

请你帮帮他吧！

## 说明/提示

### 样例 1 解释

![](https://cdn.luogu.com.cn/upload/image_hosting/6uguqush.png)

图中的方块代表树。第一行为调整前，第二行为调整后的情况。标出的三个绿色的方块是不需要移动的树，除此之外其他树都需要移动。

### 数据规模与约定

对于 $100\%$ 的数据，保证 $1 \leq T \leq 10 ^ 5$，$1 \leq n \leq 10 ^ {18}$，$1 \leq x < y \leq 10 ^ 9$。  

## 样例 #1

### 输入

```
1
8 2 3```

### 输出

```
3```

# 题解

## 作者：zzx114514 (赞：6)

# [题目传送门](https://www.luogu.com.cn/problem/P9213)
## 题目大意
一条道路上有 $n$ 棵树，间隔为 $x$，现在要将这些树重新移植，使它们之间的间隔为 $y$，求共有多少棵树能留在原地不动。
## 解题思路
由小学数学知识可知，除第一棵树以外，其余的不动树必定是原来间隔 $x$ 和现在间隔 $y$ 的公倍数，否则一定会被移动，只需求出小于原先栽树的长度的 $x$ 和 $y$ 的公倍数个数即可。
## 注意事项
此题坑点在于 $n$ 的范围为 $10^{18}$，$x$ 和 $y$ 的范围为 $10^9$，两者相乘求种树的总长必定会超出 `long long` 的范围，这时我们可以掏出神器：`__int128`，这样就不会见祖宗了。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int t;
__int128 n,x,y,l;
__int128 read()
{
	__int128 res=0;
	char c[1005];
	scanf("%s",c);
	for(int i=0;i<strlen(c);i++)
	{
		res*=10;
		res+=c[i]-'0';
	}
	return res;
}
void print(__int128 num)
{
	if(num>9) 
		print(num/10);
	putchar(num%10+'0');
}
//注意使用__int128必须使用快读快输，不能使用cin,cout或scanf,printf 
__int128 lcm(__int128 a,__int128 b)
{
	return a*b/__gcd(a,b);//求最小公倍数，其中__gcd(a,b)是自带函数，表示最大公因数，可以直接调用 
}
int main()
{
	cin>>t;
	while(t--)
	{
		n=read(),x=read(),y=read();
		l=(n-1)*x;//求原来种树总长度 
		print(l/lcm(x,y)+1);//注意求完小于l的公倍数后要加回开头的那棵树 
		puts("");//一种换行的方法 
	}
	return 0;//华丽的结尾 
}
```
本蒟蒻第一篇题解，如有不足之处请指出QWQ

---

## 作者：cff_0102 (赞：5)

明显的，能够保持不变的树的位置必然同时是 $x$ 和 $y$ 的倍数。所以实际上要求的是在 $0$ 到 $(n-1)\times x$ 之间有几个 $x$ 和 $y$ 的公倍数。

$ans=\lfloor\frac{(n-1)\times x}{\operatorname{lcm}(x,y)}\rfloor+1=\lfloor\frac{(n-1)\times x}{\frac{x\times y}{\gcd(x,y)}}\rfloor+1=\lfloor\frac{(n-1)\times\gcd(x,y)}{y}\rfloor+1$。

注意数据范围。当 $n$ 取到 $10^{18}$，$2x=y=10^9$ 时，计算 $ans$ 的值在乘法数值最大时可以达到 $5\times10^{26}$。为了避免溢出，题解和讨论区好像都在说使用 `__int128`。但是，使用 `__int128` 还需要快读，这十分的麻烦。实际上，`long double` 表示的范围可达 $10^{4932}$，用来存 $ans$ 可以说绰绰有余了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	ios::sync_with_stdio(false);
	int t;cin>>t;
	while(t--){//读入 t 组数据 
		long long n,x,y;
		cin>>n>>x>>y;
		long double ans=1;//定义一个 long double 变量用来存储答案
		ans*=(n-1);//先乘 (n-1)
		ans*=__gcd(x,y);//再乘 gcd(x,y)
		ans/=y;//再除以 y（见上面推的公式）
		cout<<(long long)ans+1<<endl; //强转 long long 可以向下取整，注意答案是有可能达到 int 不能表示的范围的
	}
	return 0;
}
```

注意，强转 `long long` 那里不能改成 `int`，因为当 $x=5\times10^8,y=10^9$ 时，$ans=\lfloor\frac{n-1}{2}\rfloor+1$。当 $n\ge2^{32}$ 时就会爆 `int`。

[提交通过记录](https://www.luogu.com.cn/record/116111287)。

---

## 作者：liuliucy (赞：2)

显然的，如果要让一棵树位置不变，就是要求有多少组 $(a,b)$ 要使得 $ax=by$，其中 $x$ 表示原来树之间的距离，$y$ 表示变换后的距离。当然要加上限制条件 $0 \le b \le (n-1)$ 且四个数都为整数。显然，$ax=by=k\operatorname{lcm(x,y)}$，所以一共有 $\left \lfloor \frac{(n-1)x}{\operatorname{lcm(x,y)}} \right \rfloor +1$ 组解（还有 $(0,0)$ 的情况）。但看数据范围，显然会爆精度，我们消去一些数：
$$\left \lfloor \frac{(n-1)x}{\operatorname{lcm(x,y)}} \right \rfloor +1=\left \lfloor \frac{(n-1)x}{\frac{xy}{\gcd(x,y)}} \right \rfloor+1=\left \lfloor \frac{(n-1)}{\frac{y}{\gcd(x,y)}} \right \rfloor +1$$
先计算分母部分，即可求出正确答案。
### CODE
```cpp
#include<bits/stdc++.h>
using namespace std;
int T;
long long gcd(long long a,long long b){
	while(b^=a^=b^=a%=b);
    return a;
}
long long x,y,n;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%lld%lld%lld",&n,&x,&y);
		printf("%lld\n",(n-1)/(y/gcd(x,y))+1); 
	}
} 
```


---

## 作者：_Emperorpenguin_ (赞：1)

## 题意简述：


一条路上有 $n$ 棵树，相邻两数间距离为 $x$，现要移动这些树，使其间隔扩大为 $y$，若起点树木不动，求无需移动的树木数量的最大值。 


## 思路：

由题意易得，除起点树木外，其它所有无需移动的树的位置都应该是 $x$ 和 $y$ 的最小公倍数。

所以我们只需求出原植树长度中 $x$ 和 $y$ 的最小公倍数的个数即可。 

- 注意：若 $n$，$x$ 均为极限值，那么下面程序中 $len$ 的值就会非常非常大，别说  ```int```  了，就算开了 ```long long```  都得让你见祖宗。
- 因为在求种树的总长度时和求最小公倍数是都要乘 $x$，而后在计算答案时又要将 $len$ 和 $f$ 相除，所以我们可以在计算 $len$ 和 $f$ 时直接将 $x$ 除去，这样就不会爆   ```long long```  了。

## Code：

```cpp
#include<bits/stdc++.h>
#pragma G++ optimize(2)
using namespace std;

int t;
long long n,x,y;
long long len;
long long f; 
long long ans;

signed main(){
//	freopen("test.in","r",stdin);
//	freopen("test.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin>>t;
	while(t--){//多组数据 
		cin>>n>>x>>y;
		len=(n-1);//原来的种树长度除以x 
		f=y/__gcd(x,y);//最小公倍数除以x。最小公倍数=两数之积/最大公因数。__gcd(a,b)是系统函数，可以直接调用 
		//上面两项因为要相除，所以两项可以同除以x。否则会爆long long 
		ans=len/f+1;//不用移动的树的数目。long long 型自动向下取整。+1是为了加上起点的那棵树，原题中说「起点不变」 
		cout<<ans<<endl;
	}
	return 0;
}
```


---

## 作者：ssSSSss_sunhaojia (赞：0)

[**原题传送门**](https://www.luogu.com.cn/problem/P9213)

因为题目中说起点不变，所以每经过 $x$ 和 $y$ 的最小公倍数的距离，就会有一棵树不用动。于是就有了下面的代码:
```
#include <bits/stdc++.h>
using namespace std;
#define in inline
#define re register
#define IOS ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
typedef long long LL;
typedef unsigned long long ULL;
typedef long double LD;
LL T, n, x, y, s; 
int main(){
	IOS;
	cin >> T; 
	while(T --) {
		cin >> n >> x >> y; 
		s = (n - 1) * x; //初始的总长度
		cout << 1 + s / (x * y / __gcd(x, y)) << "\n"; //加1是因为起点还有一棵树不用动 
	}
	return 0;
}

```
但是交上去后发现不对，原来是爆 ```long long``` 了。仔细观察代码可发现，$x$ 与 $y$ 的最小公倍数和 $s$ 有共同的因数 $x$，所以都可以消掉一个 $x$，这样就可以了。 
# AC Code:
```
#include <bits/stdc++.h>
using namespace std;
#define in inline
#define re register
#define IOS ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
typedef long long LL;
typedef unsigned long long ULL;
typedef long double LD;
LL T, n, x, y, s; 
int main(){
	IOS;
	cin >> T; 
	while(T --) {
		cin >> n >> x >> y; 
		s = (n - 1); 
		cout << 1 + s / (y / __gcd(x, y)) << "\n";  
	}
	return 0;
}

```

---

