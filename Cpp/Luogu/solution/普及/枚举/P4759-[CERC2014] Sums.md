# [CERC2014] Sums

## 题目描述

## 题目大意

一共有 $T$ 组数据，每组数据给定一个数 $N$，请将 $N$ 分解为几个连续正整数的和，如果有多种情况，请输出最小数最大的情况。

## 样例 #1

### 输入

```
3
8
10
24
```

### 输出

```
IMPOSSIBLE
10 = 1 + 2 + 3 + 4
24 = 7 + 8 + 9
```

# 题解

## 作者：LLqm_rYZ (赞：33)

# P4759 ~~最良心~~
[这是题目](https://www.luogu.com.cn/problem/P4759)  

[配合博客使用效果更佳](https://www.luogu.com.cn/blog/heqzqmBLBL/solution-p4759)

## 大致题意
大致题意就是给定一个正整数n，求一个公差为1和为n的等差数列。
## 分析
这一道题我们可以用枚举来做。那么重点来了--枚举的量为什么呢？

我们在讨论这个问题前先要了解一个等差数列求和公式：**数列和=（首项+末项）×项数/2**

那么有了这个公式，数列和已知，那么未知的项数和首项我们要枚举的量为-----项数，因为首项和末项要用到公差（已知为1）和项数来得出

### **推公式**
在原公式中有两个未知量，但我们知道公差为1，所以可以把其中一个未知量--**末项**表示为**首相+项数-1**，公式可以表示为**和=（首项+首项+项数-1）×项数/2**

两边同时×2：**和×2=（首项+首项+项数-1）×项数**

两边同时/项数：**和×2/项数=首项+首项+项数-1**

两边同时+1：**和×2/项数+1=首项+首项+项数**

两边同时-项数：**和×2/项数-项数+1=首项×2**

枚举**项数**我们就可以得到**首项**，然后你会发现：
#### 这不就是我们要的么
## 代码
[评测记录](https://www.luogu.com.cn/record/40330798)

这是~~你们最喜欢的~~带注释的 _Code_ ：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,t;//声明 
int main() {
	scanf("%d",&t);
	while(t--) {//t组数据 
		scanf("%d",&n);
		n*=2;//先将和*2便于处理和判断 
		bool iss=0;//用来判断是否有解 
		for (int i=2; i*i<=n; i++) {//枚举项数 
			if(n%i!=0) continue;//只需要用和*2去除以项数即可判断合法 
			int x=(n/i-i+1)/2,y=x+i-1;//左右端点 
			if ((n/i-i+1)%2==0) {//判断首项是否为整数，也就是首项*2是否为偶数 
				printf("%d = %d",n/2,x);//先输出总和and首项 
				iss=true;//记录iss为真也就是有解 
				for(int l=x+1; l<=y; l++) cout<<" + "<<l;//从tmp+1输出数列因为左端点在15行输出过了 
				break;//跳出循环节省时间 
			}
		}
		if(!iss)/*如果iss=false也就是无解*/ printf("IMPOSSIBLE");
		printf("\n"); //换行
	}
	return 0;
}
```
最后是~~为了方便同学们复制~~的 _Code_ ：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,t;
int main() {
	scanf("%d",&t);
	while(t--) {
		scanf("%d",&n);
		n*=2;
		bool iss=0;
		for (int i=2; i*i<=n; i++) {
			if(n%i!=0) continue;
			int x=(n/i-i+1)/2,y=x+i-1;
			if ((n/i-i+1)%2==0) {
				printf("%d = %d",n/2,x);
				iss=true;
				for(int l=x+1; l<=y; l++) cout<<" + "<<l;
				break;
			}
		}
		if(!iss) printf("FANGCHAOXI");
		printf("\n");
	}
	return 0;
}
```
完（dian）结（ge）撒（zan）花（ba）~~

欢迎[来我的博客](https://www.luogu.com.cn/blog/heqzqmBLBL/#)看看

---

## 作者：说好不哭 (赞：7)

# 数论推理题
### 对于这种类型的题目，还有[P1147 连续自然数和](https://www.luogu.org/problemnew/show/P1147)
### 因为P1147这题数据范围不大，所以之前我用前缀和加二分水过了。这题数据有10位，数组根本存不下，所以这题
## 必须要用纯数论分析！！！

####  首先可以设(L)+(L+1)+(L+2)+...+(R)=n,所以$\frac{(L+R)*(L-R+1)}{2}$=n,所以(L+R)*(L-R+1)=2n。 可以设k1*k2=2n,其中假设k1是较小的数，所以k1=(L+R),k2=(L-R+1),所以可以解方程得L=$\frac{k2-k1+1}{2}$,R=$\frac{k2+k1-1}{2}$，且k1！=1。 并且可以由L,R均为自然数，得出k1,k2一定为一奇一偶。

####  到达这一步后，相信大家都知道可以通过枚举k1来得出L,R，也就是最终的答案了。因为设的k1<k2（其中，对于k1=k2的情况，大家可以通过计算，发现若k1=k2，则L=$\frac{1}{2}$,所以不存在）。 又因为k1*k2=2n,所以可得出k1<sqrt(2n),所以枚举k1为2到sqrt(2n)，对于这样k1,可以由2n%k1得出k2是否为自然数，若是，则继续判断k1,k2是否为一奇一偶，若均符合，则说明已找到符合题意的答案，输出退出即可。

### 一些细节会在题解中体现。

```cpp
#include <bits/stdc++.h>
using namespace std;
long long i,j,t,n,l,r,k1,k2; //注意输入的数都用long long 定义比较保险
bool jc;
int main(){
	scanf("%lld",&t);  
	for (i=1; i<=t; i++){
	scanf("%lld",&n);
	jc=false;  //标记是否能找到答案
	for (k1=2; k1<=sqrt(2*n); k1++) //从2到sqrt（2n）枚举k1
	if (2*n%k1==0 && (k1+2*n/k1)%2==1) { //判断此刻的k1,k2是否符合要求
	jc=true; 
	k2=2*n/k1;
	l=(k2-k1+1)/2;
	r=(k2+k1-1)/2;
	printf("%lld = ",n);
	for (j=l; j<r; j++) printf("%lld + ",j);
	printf("%lld\n",r);
	break;  //对于符合要求的k1,k2,求出L,R,输出答案
	}
---------------------------------------------------------------------
其中，对于k1的枚举，要强调一下。
题意中说是求出最大数最小的情况，但翻译有错，实际是输出最小数最大。
由于最小数是L，所以要使(k2-k1+1)/2最大，由于k2,k1为反比例关系，
所以当k1小时k2大，（k2-k1+1）/2大，所以k1从小到大枚举。
---------------------------------------------------------------------
if (jc==false) {printf("IMPOSSIBLE");puts(" ");} 
//若不能找到答案则按题意输出不可能
	
}
return 0;	
}

```

## 纯数论推理，这应该是一篇简洁易懂的良心题解了。
### 对于这一类问题，还能用伸缩区间做，O(n)复杂度，但这题不能。感谢大佬WZJ的新思路。
```cpp

//使用伸缩区间
#include<bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin>>n;
    int l=1,r=0,sum=0;
    while(l<n){
        while(sum<n){
            r++;sum+=r;	
        }
        if(sum==n){
            cout<<l<<" "<<r<<endl;
            sum-=l;l++;
        }
        while(sum>n){
            sum-=l;l++;
        }
    }
    return 0;
} 

```

---

## 作者：Temperature_automata (赞：6)

话不多说，我们直入正题              
这是一题数论题，主要考察等差数列知识。
### 【part 1】题意简述
给你T个数，请把每个数拆分成几个连续自然数相加，无法拆分输出IMPOSSIBLE。         
### 【part 2】算法&思路分析
首先，我们只考虑只有一个数的情况：       
设这个数为N，N = a + (a + 1) + (a + 2) + ...+ (a + n - 1)       
也就是说，起始数是a，共有n项。        
接下来，我们就有两个思路：

- 枚举a

	这是最容易想到的思路，可以发现一个性质：a<=n/2，所以我们要枚举n/2次，但还要继续拓展，所以时间复杂度为O(N/2*n)，肯定超时
- 枚举n

	这是本题正解。     
   N = (a+a+n-1)×n/2     
   因为a为正整数       
   所以2a+n-1>n        
   因此n<=sqrt(N×2)         
   N = (a+a+n-1)*n/2      
   2×N/n = 2a+n-1;       
   移项可以得出a = （2×N/n-n+1）/2        
   当a为正整数时有解。
   
   
   
   
### 【part 3】代码分析
```cpp
#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

int T , n;

int main() {
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	cin >> T;
	while(T --) {
		cin >> n;//输入
		bool found = 1;//判断是否能找到
		for(int i = 2; i <= sqrt(2 * n); i ++) {//n<sqrt（2*N）
			int a = ( (2 * n) / i - i + 1) / 2;
			if( (a * 2 ) == + 1 - i + ( (2 * n) / i )) {
				if( (a * 2 - 1 + i ) * i == 2 * n) {
					cout << n << " = ";
					for(int j = 1; j <= i-1; j ++)
						cout << a << " + " , a ++;
					cout << a << endl;
					found = 0;
					break;
				}//判断a是否为整数，若为整数则输出
			}//时刻注意double精度误差！
		}
		if(found)	cout << "IMPOSSIBLE" << endl;
	}
	return 0;//完结撒花
}
```


---

## 作者：BurningEnderDragon (赞：6)

**upd 2021-05-10：修改了小部分 Markdown 源码**

[题目链接：P4759 \[CERC2014\]Sums](https://www.luogu.com.cn/problem/P4759)

### 本题是一道简单的数论+枚举题。

设 $N$ 可以被分解为 $x(2 \le x \le N)$ 个正整数的和，则 $x$ 满足以下特点：

- 若 $x$ 为奇数，则$N$ 可以被 $x$ 整除（$\frac{N}{x}$ 即为 $N$ 个正整数中最中间的那个数）；

- 若 $x$ 为偶数，则 $N\ mod\ x = \frac{x}{2}$（即 $\frac{N}{x}$ 的小数部分为 $0.5$）。

题目中还有一句要求：

> 如果有多种情况，请输出最小数最大的情况。

显然，$x$ 最小时最小数最大。

所以，我们只需要从小到大枚举 $x$，找到的第一个符合题意的 $x$ 即为正确答案的 $x$。

那求出最小的 $x$ 后怎么做呢？经过一番计算，我们发现 $N$ 个正整数中的最小数 $l = \frac{N}{x} - \frac{x-1}{2}$，最大数 $r= \frac{N}{x} + \frac{x-1}{2}$。

所以，在求出最小的 $x$ 后，我们遍历输出闭区间 $[\frac{N}{x} - \frac{x-1}{2}\ ,\ \frac{N}{x} + \frac{x-1}{2}]$ 中的每一个正整数即可。

若枚举完毕后仍然没有找到符合题意的 $x$，则输出 `IMPOSSIBLE`。

（别忘了输出 $N$、空格、等号与加号）

```cpp
for(int j=2;j<=N;++j)//从小到大枚举 x 
{
    if(j%2==1)//x 为奇数的情况 
    {
        if(N%j==0)//若 N 能被 x 整除则符合题意 
        {
            cout<<N<<" = ";
            for(int l=(N/j)-(j/2);l<=(N/j)+(j/2)-1;++l)//遍历输出 N 个正整数 
            {
                cout<<l<<" + ";
            }
            cout<<(N/j)+(j/2)<<endl;
            goto Next;//跳出循环 
        }
    }
    else//x 为偶数的情况 
    {
        if(N%j==(j/2))//若 N mod x = x/2 则符合题意 
        {
            cout<<N<<" = ";
            for(int l=(N/j)-(j/2-1);l<=(N/j)+(j/2)-1;++l)//遍历输出 N 个正整数 
            {
                cout<<l<<" + ";
            }
            cout<<(N/j)+(j/2)<<endl;
            goto Next;//跳出循环 
        }
    }
}
cout<<"IMPOSSIBLE"<<endl;//若枚举完毕后仍然没有找到符合题意的 x，则输出 "IMPOSSIBLE"。
Next:;
```

但是在本题中 $N \le 10^{9}$，直接从 $2$ 枚举到 $N$ 会超时，所以我们还需要考虑缩小 $x$ 的取值范围。

$$ l \ge 1 $$
$$ r \le N  $$

即

$$ \frac{N}{x} - \frac{x-1}{2} \ge 1 $$
$$ \frac{N}{x} + \frac{x-1}{2} \le N $$

整理不等式 $1$ 得 $a^{2}+a \le 2N,\ \because a \ge 2,\ \therefore a^{2} < 2N,\ \therefore a < \sqrt{2N}$；

整理不等式 $2$ 得 $a \le 2N$。

综上所述，$a < \sqrt{2N}$。

当 $N = 10^{9}$ 时，$\sqrt{2N} = 44721.36$，在本题中处在可接受的范围内。所以我们只需要将枚举端点设为 $\sqrt{2N}$（将原始代码中最外层循环中的 `j <= N` 改为 `j < sqrt(2*N)` 即可。

完整AC代码如下：（由于代码中的 `/` 会向下取整，所以遍历输出 $N$ 个正整数的实际代码实现与推导出的公式有所不同）

```cpp
#include <iostream>
#include <cmath>
using namespace std;
int T,N;
int main()
{
	cin>>T;
	for(int i=1;i<=T;++i)
	{
		cin>>N;
		for(int j=2;j<sqrt(2*N);++j)//从小到大枚举 x 
		{
			if(j%2==1)//x 为奇数的情况 
			{
				if(N%j==0)//若 N 能被 x 整除则符合题意 
				{
					cout<<N<<" = ";
					for(int l=(N/j)-(j/2);l<=(N/j)+(j/2)-1;++l)//遍历输出 N 个正整数 
					{
						cout<<l<<" + ";
					}
					cout<<(N/j)+(j/2)<<endl;
					goto Next;//跳出循环 
				}
			}
			else//x 为偶数的情况 
			{
				if(N%j==(j/2))//若 N mod x = x/2 则符合题意 
				{
					cout<<N<<" = ";
					for(int l=(N/j)-(j/2-1);l<=(N/j)+(j/2)-1;++l)//遍历输出 N 个正整数 
					{
						cout<<l<<" + ";
					}
					cout<<(N/j)+(j/2)<<endl;
					goto Next;//跳出循环 
				}
			}
		}
		cout<<"IMPOSSIBLE"<<endl;//若枚举完毕后仍然没有找到符合题意的 x，则输出 "IMPOSSIBLE"。
		Next:;
	}
	return 0;
}
```

（我的代码中使用了 `goto`，因为 `goto` 在使用得当时可以很方便地实现跳出多层循环或跳过一些步骤）

---

## 作者：ztz11 (赞：5)

# 大水题。。。

解法很奇妙

因为要拆分成等差（差为1）数列，我们设这个数列一共有$x$项

那么这个数列可以表示为$(a+1)+(a+2)+……+(a+x)=n$

根据等差数列求和公式，上式可以化简为：$\frac{[(a+1)+(a+x)]*x}{2}$

进一步化简为$a*x+\frac{(x+1)*x}{2}$

这时，我们就可以愉快地枚举x了

如果$(n-\frac{(x+1)*x}{2})$%x=0

则成立

首项就是$\frac{(n-\frac{(x+1)*x}{2})}{x}+1$

输出就行

当然，如果枚举完了还不行，就跳出

### 注意：由于最大项尽可能小，所以项数要从小枚举

---

## 作者：zhanghzqwq (赞：2)

这道题跟[P5077](https://www.luogu.com.cn/problem/P5077)很像，只不过是要求最小数最大的情况，还加了个多组数据。

在连续自然数中项数越少，那么首项就越大，那我们循环就从大到小枚举它的长度，第一个找到的就是他最小数最大值的情况。

那么我们枚举从二枚举到几呢？让我们来看一看等差数列的求和公式吧。其中s是和，a为首项，b为末项，len等于项数。

$s = ( a + b ) \times len \div 2$

$\because a + b > len$

$\therefore len < \sqrt{2s}$

所以枚举到$\sqrt{2s}$可以了，详情见代码。

上AC代码：

```cpp
#include<cmath>
#include<iostream>
using namespace std;
int main(){
	int t;
	cin>>t;
	while(t--){//多组数据
		int n;
		cin>>n;
		bool found=0;
		for(int len=2;len<=sqrt(2*n);len++){//从2开始由小到大找首项最大值
			if(n*2%len!=0){//判合法
				continue;
			}
			if((n*2/len-len+1)%2!=0){//再次判合法
				continue;
			}
			found=1;//找到了
			int a=(n*2/len-len+1)/2;//算首项
			int b=a+len-1;//算末项
			cout<<n<<" = "<<a;//输出
			for(int i=a+1;i<=b;i++){//继续输出
				cout<<" + "<<i;
			}
			cout<<endl;
			break;
		} 
		if(!found){//没找到的情况
			cout<<"IMPOSSIBLE"<<endl;
		}
	}
	return 0;//完结撒花
}
```


---

## 作者：ryanright (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P4759)

**题意：**

一共有 $T$ 组数据，每组数据给定一个数 $N$，请将 $N$ 分解为几个连续正整数的和，如果有多种情况，请输出最小数最大的情况。

**题解：**

众所周知，这些连续的正整数为**等差数列**，而等差数列求和的公式为：
$$\frac{1}{2}(a+b)t$$  
其中 $a$ 为首项，$b$ 为末项，$t$ 为项数。在这道题，由于公差为 $1$，所以项数为 $(b-a+1)$。带进去就是
$$n=\frac{1}{2}(a+b)(b-a+1)$$  
$\frac{1}{2}(a+b)$ 就是从 $a$ 到 $b$ 的所有正整数的平均数。于是就可以得到一个结论：**一些连续正整数的和为这些数的平均数乘以这些数的数量。**

然而这道题知道的是和，现在求是哪些数。$(a+b)$ 有两种可能——奇数或者偶数，除以 $2$ 之后得出的平均数会是整数或是小数（小数部分为 $0.5$）。然后我们依次枚举项数，反向求出平均数，若为整数或是小数部分为 $0.5$ 的数（这里要注意前后匹配，即偶数个项要为整数，奇数个项要为小数部分为 $0.5$ 的数）则判为合法。

这里要讲一下，如何判定一个数小数部分为 $0.5$。直接减也许可以，但这里讲另一种方法，没有浮点误差。我们判定的时候使用的是被除数与除数，假设分别为 $x$ 和 $y$。假设商小数部分为 $0.5$，那么
$$\frac{x}{y}=\lfloor\frac{x}{y}\rfloor+0.5$$  
同时乘以 $2$，就变成了
$$\frac{2x}{y}=2\lfloor\frac{x}{y}\rfloor+1$$  
然后左右同时乘 $y$，
$$2x=2y\lfloor\frac{x}{y}\rfloor+y$$  
而 $\lfloor\frac{x}{y}\rfloor$ 是 C++ 中 int 的除法方式，因此没有浮点丢失。
```cpp
inline bool point5(int x,int y){return 2*x==2*y*(x/y)+y;}
```
检查完毕之后就要输出。奇数个项的范围为 $(\lfloor\frac{n}{i}\rfloor-\lfloor\frac{i}{2}\rfloor)\sim(\lfloor\frac{n}{i}\rfloor+\lfloor\frac{i}{2}\rfloor)$，偶数个项的范围为 $(\lfloor\frac{n}{i}\rfloor-\frac{i}{2}+1)\sim(\lfloor\frac{n}{i}\rfloor+\frac{i}{2})$。

最后再补充一下枚举。枚举项数的顺序为从小到大，从 $2$ 开始。枚举到 $n$ 那是不可能的，绝对 TLE。由于题目要求的是正整数，根据上面的范围可以知道，只要 $\lfloor\frac{n}{i}\rfloor-\lfloor\frac{i}{2}\rfloor<0$，就不用再枚举了，直接跳出循环。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
inline bool point5(int x,int y)
{
	return 2*x==2*y*(x/y)+y;
}
int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		int n;
		bool flag=0;
		scanf("%d",&n);
		for(int i=2;;i++)
		{
			if(n/i-i/2<0) break;
			if(n%i==0&&i%2)
			{
				printf("%d = ",n);
				for(int j=n/i-i/2;j<n/i+i/2;j++) printf("%d + ",j);
				printf("%d\n",n/i+i/2);
				flag=1;break;
			}
			else if(point5(n,i))
			{
				printf("%d = ",n);
				for(int j=n/i-i/2+1;j<n/i+i/2;j++) printf("%d + ",j);
				printf("%d\n",n/i+i/2);
				flag=1;break;
			}
		}
		if(!flag) printf("IMPOSSIBLE\n");
	}
	return 0;
}
```

---

## 作者：Eason_AC (赞：1)

## Content
给定 $t$ 组数据，每组数据给定一个数 $n$，判断 $n$ 是否能够分解成连续正整数和，能的话给出最小数最大的方案。

**数据范围：$1\leqslant n\leqslant 10^9$。**
## Solution
这道题如果暴力枚举的话，看数据范围就知道肯定会爆炸。因此我们要考虑推式子。

首先，我们设分解后的数列长度为 $k$，首项为 $a_1$。那么显然得到 $\text{(1)}$ 式：

$\begin{aligned}n&=\dfrac{(a_1+(a_1+k-1))k}2\\&=\dfrac{(2a_1+k-1)k}2\end{aligned}$

由于 $a_1,k>0$，在 $a_1>0$ 两边同时加上 $a_1+k-1$ 得：

$$2a_1+k-1>k$$

然后我们由 $\text{(1)}$ 式可得 $2a_1+k-1=\dfrac{2n}{k}$，代入不等式：

$$\begin{aligned}\dfrac{2n}{k}&>k\\k^2&<2n\\k&<\sqrt{2n}\end{aligned}$$

我们由样例可得 $k\geqslant 2$（读者自证不难），又因为 $k$ 是正整数，所以得到了 $k$ 的范围为：$k\in[2,\left\lfloor\sqrt{2n}\right\rfloor]$。

这样我们就可以考虑通过枚举 $k$ 来求得答案。现在看 $a_1$。

我们还是通过 $\text{(1)}$ 式求解：

$$\begin{aligned}2a_1+k-1&=\dfrac{2n}k\\2a_1&=\dfrac{2n-k^2+k}k\\a_1&=\dfrac{2n-k^2+k}{2k}\end{aligned}$$

又因为 $a_1$ 是正整数，所以只需要判断是否有下列条件成立即可：

- $2k\mid(2n-k^2+k)$。
- $\dfrac{2n-k^2+k}{2k}>0$

枚举出符合条件的方案我们就可以输出了，并且我们算一下不难发现，从 $2$ 枚举到 $\left\lfloor\sqrt{2n}\right\rfloor$ 第一个找出来的方案就是题目所要求的最小数最大的方案。注意输出的格式即可。如果枚举完了还是没有找到方案那就直接输出 `IMPOSSIBLE` 就好。

## Code
```cpp
int main() {
	MT {
		int n = Rint, flag = 1;
		F(len, 2, (int)sqrt(2 * n)) {
			if(!((2 * n - len * len + len) % (2 * len)) && (2 * n - len * len + len) / (2 * len) > 0) {
				int a1 = (2 * n - len * len + len) / (2 * len);
				printf("%d = ", n);
				F(i, a1, a1 + len - 1) {
					printf("%d ", i);
					if(i != a1 + len - 1) printf("+ ");
					else puts("");
				}
				flag = 0; break;
			}
		}
		if(flag) puts("IMPOSSIBLE");
	}
	return 0;
}
```

---

## 作者：sxtm12138 (赞：1)

之前没看讨论中的翻译订正导致我算了最大数最小的情况，结果最后显示OLE， 经过六、七次修改、提交都没过 ，所以特地先提醒大家：

# 做题前一定先好好读题！！！！！

在这之后，这道题目的难度就会大大下降。首先假设将n分成i项，由于这i项是连续自然数，故他们的平均数的小数部分为0或0.5（自己试试，会发现 _**它们的平均数等于中位数**_ ）。

**若i是奇数，则n/i必定为整数**（n/i为各项的平均数，0.5乘以奇数不可能为整数），**若i是偶数，则n/i的小数部分必定为0.5**（偶数个连续自然数的中位数为中间两个数的平均数），从而我们得出只要满足：
    **((i%2==1&&n%i==0)||(i%2==0&&n%i==i/2))**
就能将n分成连续i项，但如果要满足这i项是自然数，还要保证n/i-i/2（i项中的最小数，i为偶数要+1）>=0（i为奇数>=1），可列出以下算式：**n/i-i/2>=0 -> i/2<=n/i -> i^2<=2n -> i<=sqrt(2*n)**

同时题目要求找最小数最大的情况，而n/i-i/2随i的增大而减小，所以i要**从小到大枚举**。

------------
 _代码如下：_ 

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,p,a[30000000],c,i,f;//开大点不会错
int main()
{cin>>n;
 for(int i=1;i<=n;i++)cin>>a[i];//读入
 for(int t=1;t<=n;t++)
   {p=floor(sqrt(2*a[t]));//确定取值范围
    c=0;//c=0表示无解，c=1表示i为偶数，c=2表示i为奇数
    for(i=2;i<=p;i++)//本题i要从小到大枚举
    //若要求出最大数最小的情况，i要从大到小枚举（证明较复杂）
      {if ((a[t]%i==i/2)&&(i%2==0))//情况1：i为偶数
         {c=1;
          break;
         }//i一旦满足情况1就停止
       if ((i%2==1)&&(a[t]%i==0))//情况2：i为奇数
         {c=2;
          break;
         }//i一旦满足情况2就停止
	  }
    if(c==0) cout<<"IMPOSSIBLE"<<endl;//判断无解
    else 
      {cout<<a[t]<<" =";
       f=c>1? a[t]/i-i/2:a[t]/i-i/2+1;//三目运算符判断情况1或2
       for(int j=f;j<=a[t]/i+i/2-1;j++)cout<<" "<<j<<" +";
       //空格是本题的又一难点
       cout<<" "<<a[t]/i+i/2<<endl;
       //i为奇数或偶数时，最大值均为n/i+i/2（代个值就知道了）
      }
   }
return 0;
}
```

---

## 作者：杨岛主杨东润 (赞：0)

一道十分简单的黄题。

代码就三十几行诶！

### 题目解法：

先输入 $t$,作为循环。

接下来，对于每次循环，输入一个 $n$。

接下来，我们就开始枚举每一个 $n$,用奥数方法解决。

最后别忘了判断是否可行，如果不可行输出IMPOSSIBLE。

### 具体代码：

不要抄袭哦！

```cpp
#include<iostream>//头文件 
using namespace std;
int main(){
	int t;
	cin>>t;//读入 
	for(int i=1;i<=t;i++){
		int n;
		cin>>n;
		n*=2;//这里n要乘2，不然做不出来 
		int flag=0;//判断是否可行的变量 
		for(int j=2;j*j<=n;j++){//j也要平方 
			if(n%j!=0){//不可行就继续枚举 
				continue;
			}
			//如果可行 
			int a=(n/j-j+1)/2;
			int b=a+j-1;
			int c=n/j-j+1;
			if(c%2==0){//输出可行的情况 
				cout<<n/2<<" = "<<a;
				flag=1;//可行 
				while(1){
					//fangzhichaoxi
				}
				for(int p=a+1;p<=b;p++){
					cout<<" + "<<p;
				}
				cout<<endl;
				break;//直接结束循环 
			}
		}
		if(flag==0){//如果不可行，输出 
			cout<<"IMPOSSIBLE"<<endl;
		}
	}
	return 0;//这很重要 
}
```
谢谢观看！

---

## 作者：Origin0107 (赞：0)

# Problem
一共有 $T$ 组数据，每组数据给定一个数 $N$，请将 $N$ 分解为几个连续正整数的和，如果有多种情况，请输出最小数最大的情况。

简单来说：找到一个首项最大的公差为 $1$ 的等差数列，使得等差数列之和为 $N$ 。
# Solution
首先，枚举首项大小肯定是不可行的，时间复杂度不能接受，我们考虑枚举长度。

设这个长度为 $x$ ，则有一个等差数列 $a+(a+1)+......+(a+x-1)=n$。

根据等差数列求和公式可得 $n=\frac {(a+a+x-1)*x} {2}$ ，又因为 $a$ 为正整数，所以可以得到 $a+a+x-1>x$ ，即 $n=\frac {(a+a+x-1)*x} {2}>\frac {x^2}{2}$ ，所以 $x<=\sqrt{2n}$ ，只需要从 $1$ 开始正序枚举到 $\sqrt{2n}+1$ 就可以了（正序枚举保证首项最大）。

上述式子可以化简为 $a*x+\frac {x*(x-1)} {2}$ ，所以当 $n-\frac {x*(x-1)} {2} \bmod x=0$ 的时候，$\frac {n-\frac {x*(x-1)} {2}} {x}$ 即为首项的值。
# Code
```
#include<bits/stdc++.h>
using namespace std;
bool flag;
int ans;
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        flag=0;
        int n;
        cin>>n;
        int x=sqrt(2*n);
        for(int i=2;i<=x+1;i++)
        {
            if(n==1)
            {
                cout<<"IMPOSSIBLE"<<endl;
                flag=1;
                break;
            }
            if((n-((i-1)*i/2))%i==0)
            {
                cout<<n<<" = ";
                int ans=(n-((i-1)*i/2))/i;
                for(int j=1;j<=i-1;j++)
                {
                    cout<<ans<<" + ";
                    ans+=1;
                }
                cout<<ans<<endl;
                flag=1;
                break;
            }
        }
        if(!flag) cout<<"IMPOSSIBLE"<<endl;
    }
    return 0;
}
```



---

