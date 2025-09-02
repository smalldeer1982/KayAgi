# 「Cfz Round 1」Dead Cells

## 题目背景

Cidoai 上完生物课后，突发奇想出了这么一道题。

太水了……吧。Cidoai 说着把这道题送给了你，让你去发掘这道题的快乐。

## 题目描述

有一天，在第 $0$ 个小时，一个细胞生成了，每过 $a$ 小时，细胞的数量就变成当前的两倍，每过 $b$ 小时，细胞的数量就变成当前的一半（向上取整）。

假如当前时间是 $a$ 和 $b$ 的公倍数，则细胞数量不变。问经过了 $k$ 小时后，细胞个数为多少，答案对 $998244353$ 取模。

## 说明/提示

#### 【样例解释 #1】

第 $1 \sim 6$ 小时的细胞的数量分别为 $1,1,2,1,1,2$。

#### 【数据范围】

对于所有数据，$1 \le a,b,k \le 10^6$。

**本题采用捆绑测试。**

|子任务编号|分值|$k \le$|特殊性质|
|:---:|:---:|:---:|:---:|
|$1$|$15$|$10^6$|保证 $a=b$|
|$2$|$20$|$10^6$|保证 $a\gt b$|
|$3$|$25$|$20$|无|
|$4$|$40$|$10^6$|无|

#### 【提示】

$\dfrac{a}{2} \equiv a \times 499122177 \pmod {998244353}$，即在对 $998244353$ 取模的情况下，您可以用 $a \times 499122177$ 代替 $a \div 2$。

## 样例 #1

### 输入

```
3 4 6```

### 输出

```
2```

## 样例 #2

### 输入

```
4 7 16```

### 输出

```
4```

## 样例 #3

### 输入

```
3 2 5```

### 输出

```
1```

## 样例 #4

### 输入

```
114 5141 919810```

### 输出

```
62166352```

# 题解

## 作者：Defy_HeavenS (赞：15)

## 题意
最开始有一个细胞。小时数是 $a$ 的倍数时 $\text{细胞数} \times 2$，小时数是 $b$ 的倍数时 $\left\lceil \text{细胞数} \div 2 \right\rceil$。

## 思路

**注意看提示！**

由于 $k$ 比较小，只有 $10^6$，所以可以直接模拟每一个小时。

如果小时数是 $a$ 的倍数时 $\text{细胞数} \times 2 \pmod {998244353}$，如果小时数是 $b$ 的倍数时 $\text{细胞数}\times 499122177 \pmod {998244353}$ 即可。

但是要注意，如果 $\text{细胞数}=1$，且小时数仅是 $b$ 的倍数时不能将 $\text{细胞数}\times 499122177$，因为 $1\times 499122177$ 取模去不掉，所以不用操作（由于是向上取整，所以 $\text{细胞数}=1$ 时不用操作）。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long a,b,k,ans=1;//赛时为了保守开了long long，实际只用int就可以
int main(){
	cin>>a>>b>>k;
	for(int i=1;i<=k;i++){	
		if(i%a==0){
			ans*=2; 
			ans%=998244353;
		}
		if(i%b==0){
			if(ans>1){
				ans*=499122177;
			    ans%=998244353;
			}
		}
	}
	cout<<ans;
    return 0;
}
```

---

## 作者：Star_F (赞：13)

# 题目大意：

有一个数值 $x$ 初值等于 $1$，每过 $a$ 小时乘以 $2$，每过 $b$ 小时除以 $2$，求操作 $k$ 小时后 $x$ 对 $998244353$ 取模的值。

# 题目分析：

对 $x$ 乘以 $2$ 不会发生错误，而对 $x$ 除以 $2$ 可能会发生精度错误，所以 根据同余定理：$\dfrac{a}{2} \equiv a \times 499122177 \pmod {998244353}$，即在对 $998244353$ 取模的情况下，可以用 $a \times 499122177$ 代替 $a \div 2$。

本体还是有一些细节的，如果只按照题目描述模拟会 WA。

# Code:
```cpp
#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a);i<=(b);++i)
#define ROF(i,a,b) for(int i=(a);i>=(b);--i)
#define end cout<<endl;
#define en cout<<" ";
#define LL long long
#define U unsigned
using namespace std;
template<class T>
inline void read(T &a){ register U LL x=0,t=1; register char ch=getchar(); while(ch<'0'||ch>'9'){ if(ch=='-') t=-1; ch=getchar();} while(ch>='0'&&ch<='9'){ x=(x<<1)+(x<<3)+(ch^48); ch=getchar(); } a=x*t;}
inline void print(LL x){if(x<0)putchar('-'),x=-x;if(x>9) print(x/10);putchar(x%10+'0');}
void sovle(){
	long long ans=1,a,b,k;
	read(a);read(b);read(k);    //读入数据
	for(int i=1;i<=k;i++){
		if(i%a==0){         //每过去 a 小时
			ans*=2;			//乘以2并对998244353取模
			ans%=998244353;
		} 
		if(i%b==0&&ans>1){		//每过去 b 小时
			ans*=499122177;	//同余定理，除以2可以看作乘以499122177
			ans%=998244353;	//对998244353取模
		}
	}
	print(ans);			//输出答案
}

signed main(){
    sovle();
 	return 0;
}

```

---

## 作者：Su777 (赞：4)

## 题意简述

有一个数值 $x$ 一开始等于 $1$，每过 $a$ 小时乘以 $2$，每过 $b$ 小时除以 $2$，问 $k$ 小时后 $x$ 对 $998244353$ 取模的值。

## 解题思路

因为答案要对 $998244353$ 取模，所以需要用到**同余定理**。众所周知，同余定理只满足加、减、乘三种运算，**不满足除法**！

咋办呢？没事，提示里说 $\dfrac{a}{2} \equiv a \times 499122177 \pmod {998244353}$，所以我们可以用乘法来代替除法，这样就可以使用同余定理了。

但是，这种方法并不适用与 $a=1$ 的情况。在这种情况下，按照题意结果应该还是 $1$，但是按照这种方法答案就会变成 $499122177$。因此，我们加上 $a ≠ 1$ 的特判就可以通过本题了。

代码非常简单，就不附了。

---

## 作者：玄学OIER荷蒻 (赞：3)

发现这样一道水题还没有多少题解，现在来补一个。

发现记录指数做法的现在还没有题解。

我们可以直接模拟，如果翻倍就让指数增加，反之指数减小，最后直接模拟求得答案即可。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	long long a,b,k;
	cin>>a>>b>>k;
	long long ans=1,wei=0;
	for (int i=1;i<=k;i++){
		if (i%a==0) wei++;
		if (i%b==0) wei=max(wei-1,0ll);
	}
	for (int i=1;i<=wei;i++){
		ans=(ans*2)%998244353;
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：BenRheinz (赞：2)

## 思路简述
直接根据题意模拟就行了。有一些小坑，看代码。

注意除法可能出现借位的情况，直接模拟十分麻烦，所以记得不要耍小聪明，老老实实听题目的把 $\div 2$ 换成 $\times 499122177$ 。
## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=998244353;
int main(){
	long long now=1;//在计算过程中now的最大值可能达到998244353*499122177，远超int范围，需要开long long.
	int a,b,k;
	scanf("%d %d %d",&a,&b,&k);
	for(int i=1;i<=k;i++){
    	//a,b的公倍数会被处理两次，所以不用管了
		if(i%a==0) now<<=1,now%=mod;//是a的倍数，乘2
		if(i%b==0&&now>1) now*=499122177,now%=mod;//是b的倍数，除以2。注意当now=1时结果为1而非499122177，需要特判。
	}
	printf("%lld",now);
	return 0;
}
```

---

## 作者：qpzc (赞：1)

## 思路：
假设 $t$ 是一个常量，$cnt$ 是当前时刻的细胞数量。
- 对于第 $t[a,b]$ 小时，因为 $cnt \times 2 \div 2=cnt$，可以不用管。
- 对于第 $ta$ 小时，直接将 $cnt \times 2$ 再取模即可。
- 对于第 $tb$ 小时，除法并不满足同余定理，但是题目给出 $\dfrac{cnt}{2} \equiv cnt \times 499122177 \pmod {998244353}$，所以可以将 $cnt \div 2$ 转换为 $cnt \times 499122177$ 再取模。但是如果此时 $cnt$ 为 $1$，并不满足此条件，需要特判将其变为 $\lceil 1\div 2 \rceil=1$，也就是不变。
## Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	    int a,b,k;
	    cin>>a>>b>>k;
	    long long cnt=1;
	    for(int i=1;i<=k;i++){
		    if(i%a==0)cnt=cnt*2%998244353;
		    if(cnt>1&&i%b==0)cnt=cnt*499122177%998244353;
	    }
	    cout<<cnt;
	    return 0;
}
```

---

## 作者：Null_h (赞：1)

## 思路

看到提示以为要求逆元呢。

很多大佬用分类讨论来做，其实看一眼数据范围就知道纯模拟完全可以。只要在模拟时当心除的精度问题以及特判 $1$ 的情况，乖乖按照提示走就能过了。

在简单明了代码短的基础上，我们再寻求一些优化。按照总时间一个个模拟显然会造成很大的时间浪费，于是新的优化出现了，不断在 $a$ 和 $b$ 中叠加表示当前时间，超出就跳出，一个循环就可以解决。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long 
int a,b,c,d=1,e,f;
signed main() {    
    cin>>a>>b>>c;
    e=a;
    f=b;
    while(e<=c||f<=c){
		if(e<=c&&e==min(e,f)){
			d*=2;
			e+=a;
		}else {
			if(d!=1){
				d*=499122177;
			}	
			f+=b;
		}
		d%=998244353;
	}
	cout<<d;
    return 0;
}

---

## 作者：Moon_Wind (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P9577)



------------
**题意简述**：

有一个数，它的初始值为 $1$，每 $a$ 个小时，它就会变成原来的 $2$ 倍，每 $b$ 个小时，它就会变成原来的二分之一（**向上取整**），如果当前时间是 $a$ 和 $b$ 的公倍数，就不进行任何操作。求 $k$ 个小时后，这个数变成了多少。

**算法分析**：

很明显，这道题我们要进行一下分类讨论，讨论 $a\ge b$ 和 $a<b$ 时的情况。

**情况一**：

当 $a\ge b$ 时，很明显，$\left\lfloor\dfrac{k}{a}\right\rfloor$ 是会小于等于 $\left\lfloor\dfrac{k}{b}\right\rfloor$ 的。想必有很多人像我一样，想到这里，便认为当 $a\ge b$ 时，答案是 $1$。

可是交上去，却是一片红色。因为，当 **$k$ 除以 $a$ 的余数**大于 **$k$ 除以 $b$ 的余数**时，在最后还会进行一次把原来的数翻倍的操作。也就是会把 $1$ 变成 $2$。这里一定要进行一次特判。

**情况二**：

当 $a\le b$ 时，$\left\lfloor\dfrac{k}{a}\right\rfloor$ 会大于等于 $\left\lfloor\dfrac{k}{b}\right\rfloor$，而每一次操作后，乘 $2$ 的操作次数一定大于等于除以 $2$ 的操作次数。而一次乘 $2$ 的操作正好可以与一次除 $2$ 的操作相抵消，所以我们只需要求出乘 $2$ 的操作与除 $2$ 的操作进行抵消后，还剩下多少次，然后把剩下的操作次数操作完即可。记得要取余。

**代码部分**：



------------


```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,k,op=0,op1=0,cnt=1;
int main(){
	cin>>a>>b>>k; 
	if(a>b){
	    if(k%a<k%b) cout<<2;//特判。
	    else cout<<1;
	    return 0;
	} //当a大于等于b时的情况。
	op=k/a;
	op1=k/b;
	op-=op1;//抵消后剩下的次数。
	while(op--){
		cnt*=2;
		cnt%=998244353; //取余
	}
	cout<<cnt;
	return 0;
} 
```


------------
本人只是一名蒟蒻，若有错误请多多包涵，谢谢大家。



---

## 作者：SY_nzwmb83 (赞：0)

### 题意

最初只有一个细胞，然后每过 $a$ 小时，细胞个数变为原来两倍，每过 $b$ 小时，细胞个数变为原来一半（**向上取整**）。求 $k$ 小时后细胞的数量。

下文把这两种变化简称为“两倍操作”和“一半操作”。

### 分析

先解决本题最坑的情况。当 $a>b$ 时，两倍操作的次数比一半操作的次数要少，又因为向上取整，所以最终答案可能是 $1$。但是，两倍操作和一半操作分布的位置很重要，可以发现当 $k \bmod a < k \bmod b$ 时，最后的操作是两倍操作，所以此时答案是 $2$，其余时候答案为 $1$。这种情况需要特判。

其余的情况比较简单。由于每过 $a$ 小时才会有一次两倍操作，所以执行两倍操作的次数就是 $\lfloor \frac{k}{a} \rfloor$。同理，执行一半操作的次数就是 $\lfloor \frac{k}{b} \rfloor$。这种情况只需要循环计算（注意一半操作不能直接用除法，需要改成乘 $499122177$，因为题目要求对 $998244353$ 取模）。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a,b,k,ans=1;
signed main()
{
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	cin>>a>>b>>k;
	if(a>b)//特判
	{
		if(k%a<k%b)cout<<2;
		else cout<<1;
		return 0;
	}
	for(int i=1;i<=k/a;i++)//两倍操作
	{
		ans=ans*2%998244353;
	}
	for(int i=1;i<=k/b;i++)//一半操作
	{
		ans=ans*499122177%998244353;
	}
	cout<<ans;
	return 0;
}
```

---

