# Submarine in the Rybinsk Sea (hard edition)

## 题目描述

这题与上一个题的不同之处仅在于存在使所有数字 $a_1,a_2,\dots,a_n$ 的无长度相等的约束。

$SIS$ 学生团队将乘坐潜水艇去旅游，他们的目标是位于大雷宾斯克 $(Rybinsk)$ 海底沉船中的古代宝藏。不幸的是，学生们不知道船的坐标，因此他们要求 $Meshanya$（一位世袭魔法师）来帮助他们。$Meshanya$ 同意帮助他们，但前提是他们得解决了 $Meshanya$ 的问题。

让我们用一个函数 $f(a_1a_2\dots a_{p-1}a_p,b_1b_2\dots b_{p-1}b_p)$ 来交替两个数字的各位数码，其中 $a_1,a_2,\dots,a_p$ 和 $b_1,b_2,\dots,b_p$ 是以十进制表示的两个整数的数码，不含前导零。

换句话说，函数 $f(x,y)$ 通过将数字 $x$ 和 $y$ 的各位数码从最低位数写到较高位数字，从数字 $y$ 开始，交替地插入数字 $x$ 和 $y$。该函数的结果也是从右到左构建的（即从较低的数字到较旧的数字）。如果其中一个参数（不妨设为 $x$）的数字已写完，则写下另一个参数（即 $y$）的剩余数字，下面我们来看几个例子熟悉一下。

$f(1111, 2222) = 12121212$

$f(7777, 888) = 7787878$

$f(33, 44444) = 4443434$

$f(555, 6) = 5556$

$f(111, 2222) = 2121212$

一般的，如果 $p \ge q$，那么 $f(a_1 \dots a_p, b_1 \dots b_q) = (a_1 a_2 \dots a_{p - q + 1} b_1 a_{p - q + 2} b_2 \dots a_{p - 1} b_{q - 1} a_p b_q)_{(10)}$
$Mishanya$ 为您提供一个由 $n$ 个整数组成的数组 $\{a_i\}$。你的任务是帮助学生们计算 $\sum\limits_{i = 1}^{n}\sum\limits_{j = 1}^{n} f(a_i, a_j) \mod 998244353$

## 样例 #1

### 输入

```
3
12 3 45
```

### 输出

```
12330```

## 样例 #2

### 输入

```
2
123 456
```

### 输出

```
1115598```

# 题解

## 作者：Leap_Frog (赞：3)

### Description.
$F(i,j)$ 表示从低到高不断间隔取 $j$ 和 $i$，连起来后得到的值，如果一个没了就跳过。  
求 $\sum_{i=1}^n\sum_{j=1}^nF(a_i,a_j)$  

### Solution.
$10^9$ 是 $10$ 位！$10^9$ 是 $10$ 位！$10^9$ 是 $10$ 位！  

对于每个数的每一位，我们发现它的贡献和其他数无关，仅和其他数长度有关。  
所以我们考虑对每个数的每一位分开考虑，开个桶记录长度为 $x$ 的数有多少个。  
然后统计贡献即可。  
注意 $F(a,b)\ne F(b,a)$，所以需要统计两次贡献。  

### Coding.
```cpp
const int P=998244353;int n,a[100005],ln[100005],pw[55],cn[15],rs=0;
inline int count(int x) {int r=0;while(x) x/=10,r++;return r;}
int main()
{
	read(n);for(int i=1;i<=n;i++) read(a[i]),ln[i]=count(a[i]);//长度
	pw[0]=1;for(int i=1;i<=50;i++) pw[i]=10ll*pw[i-1]%P;//10^k
	for(int i=1;i<=n;i++) cn[ln[i]]++;//长度为k的数的个数
	for(int i=1;i<=n;i++)
	{//对每个数的每一位，统计贡献
		int g[15],x=a[i],gt=0;while(x) g[gt++]=x%10,x/=10;
		//这边 k 表示其他数长度为 k，当前这个数的第 j 位
		for(int k=0;k<=10;k++) for(int j=0;j<ln[i];j++)
			rs=(rs+1ll*(pw[j+min(j,k)]+pw[j+min(j+1,k)])*g[j]%P*cn[k])%P;
	}
	return printf("%d\n",rs),0;
}
```

---

## 作者：Jerry_heng (赞：0)

（一）

虽说代码较长，但非常好理解，还是最优解（公开的就两个）。

考虑对每个数单独算贡献，循环枚举与它进行运算的数的长度，然后确定那个数的位置即可，再乘以出现的数位对应的贡献，如出现在倒数第二位就乘 $10$。

难度应该不到绿。

（二）

AC 代码。

```cpp
#include<bits/stdc++.h>
#define int long long//记得开 long long
using namespace std;
const int md=998244353;
int n,sum[21],mx,ans,a[100010],siz[100010];
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++){
		int x;
		scanf("%lld",&x);a[i]=x;
		while(x)siz[i]++,x/=10;
		sum[siz[i]]++;//统计数的位数
		mx=max(mx,siz[i]);
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=mx;j++){
			if(!sum[j])continue;
			int p1=siz[i],p2=j,d=1,s=0,x=a[i];
			bool flag=0;//flag 表示填的是当前数，还是进行运算的另一个数
			while(p1&&p2){
				if(!flag)s=(s+(x%10)*d)%md,p1--,x/=10;
				else p2--;
				flag^=1;
				d=d*10%md;
			}
			while(x){
				s=(s+(x%10)*d)%md;
				x/=10;
				d=d*10%md;
			}
			ans=(ans+sum[j]*s)%md;
		}
		for(int j=1;j<=mx;j++){
			if(!sum[j])continue;
			int p1=siz[i],p2=j,d=1,s=0,x=a[i];
			bool flag=1;
			while(p1&&p2){
				if(!flag)s=(s+(x%10)*d)%md,p1--,x/=10;
				else p2--;
				flag^=1;
				d=d*10%md;
			}
			while(x){
				s=(s+(x%10)*d)%md;
				x/=10;
				d=d*10%md;
			}
			ans=(ans+sum[j]*s)%md;
		}
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

