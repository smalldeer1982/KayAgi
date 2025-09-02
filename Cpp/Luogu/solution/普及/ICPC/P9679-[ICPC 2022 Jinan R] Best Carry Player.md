# [ICPC 2022 Jinan R] Best Carry Player

## 题目描述

### 简要题面

这里我们定义一个电脑运行 $a+b$ 的速度是 $a+b$ 中出现的进位的次数。

给定一个数组 $a_1,a_2,...,a_n$，请找出正确的排序使得计算这个数组的和时运行的速度最短，请找出最少的进位次数。

## 说明/提示

对于 $100 \%$ 的数据： $1 \leq \sum n \leq 10^5$， $1 \leq a_i \leq 10^9$

## 样例 #1

### 输入

```
2
3
9 99 999
1
12345```

### 输出

```
5
0```

# 题解

## 作者：suyi1111 (赞：3)

**Update 2024.7.28 13:50**  
不小心把正确性证明里的除以写成了取模

### 题意翻译

$T$ 组数据，每组 $n$ 个，要求每组 $n$ 个数字重排后相加，求出进位次数最少要进位几次

### 做法

按多个数字高精度相加来计算，但是不进位。

最后统计答案的时候从个位开始，一边进位一边统计每一位的进位次数

### 正确性证明（重点）

由于个位无论怎么排他们的答案相加相同，都会产生 ( 个位相加 ${}\div 10$ )次进位

由于十位无论怎么排他们的答案相加相同，都会产生 ( ( 十位相加+个位的进位) ${}\div 10$ ) 次进位

由于百位无论怎么排他们的答案相加相同，都会产生 ( ( 百位相加+十位的进位 ) ${} \div 10$ ) 次进位

……

所以进位次数一定相同

---

## 作者：Magus (赞：1)

# P9679 [ICPC2022 Jinan R] Best Carry Player 题解

纯诈骗水题。

## 题意

给定一个式子，让你把他们排列使得这个式子的进位次数最少。

## 题解

然后你会发现排列顺序与进位次数无关，直接做就行了。

## Code：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=1e7+10;
int t,n,x,y,ans,arr[maxn];
int jw(int x,int y)
{
	int num=0,n=0;
	while(x!=0 or y!=0)
	{
		if(x%10+y%10+num>=10)
		{
			num=1;
			n++;
		}
		else
		{
			num=0;
		}
		x/=10,y/=10;
	}
	return n;
}
signed main()
{
	cin>>t;
	while(t--)
	{
		cin>>n;
		x=0,y=0;
		for(int i=1;i<=n;i++)
		{
			cin>>arr[i];
			x+=jw(y,arr[i]);
			y+=arr[i];
		}
		cout<<x<<endl;
	}
	return 0;
}
```

---

## 作者：HFanGDoDM (赞：1)

# 题意简述

给定 $n$ 个数 $a_1,\dots,a_n$。按照以下过程计算这 $n$ 个数的和：

- 令 $s=0$。

- 对于每个数 $a_i$，$s\leftarrow s+a_i$。

试对序列 $a$ 重排，使得在这一过程中，产生的 **十进制进位** 数量最小，求出对应的最小的十进制进位数量。

### 数据范围

**有多组测试数据**。数据组数 $T$ 满足 $1\leqslant T\leqslant 10^5$。对于每组测试数据，$1\leqslant n\leqslant 10^5,1\leqslant a_i\leqslant 10^9$。对于所有测试数据，$\sum n\leqslant 10^5$。

# 解题思路

我们直接按照题意模拟求和过程，通过模拟，计算出按照原序列顺序进行求和的进位数量。

总的进位数量即为答案。

### 正确性证明

设 $x_k$ 表示数 $x$ 从低往高数的第 $k$ 位，$y_k$ 表示数 $y$ 从低往高数的第 $k$ 位，$s_k$ 表示表示 $s$ 从低往高数的第 $k$ 位，$c_k$ 表示相加时第 $k$ 位上产生的进位数值。

对于一次相加的第 $k$ 位，实际上是执行了 $x_k+y_k+c_{k-1}$ 的过程。考虑将形如这样的相加拆成：
$$x_k+\underbrace{1+1+1+1+\cdots+1}_{(y_k+c_{k-1})\times 1}$$

的形式，可以发现，可能存在其中几次的 $+1$，使得第 $k$ 位产生了进位。

注意到，原序列是给定的，因此，无论怎么重排，原序列的和是固定不变的 $\implies$ 在上述的过程中，**产生进位的 $+1$ 数量是恒定的**。并且，每个 $+1$ 属于且仅属于 $y_k,c_{k-1}$ 中的一个 $\implies$ **无论如何重排，加的过程中，产生进位的总数是相等的**。

因此，我们就证明了这一思路的正确性。

### 具体实现

模拟求和过程，具体地，从两个数的最低位向最高位分别执行相加。若这一位的和大于或等于 $10$，则产生一个进位，对答案加 $1$。注意相加时，要将前一位的进位一起加上。

取十进制数 $x$ 的第 $i$ 位，可以使用 $\lfloor\dfrac{x}{10^{i-1}}\rfloor \bmod 10$。

### 时间复杂度分析

每一次模拟加的过程，复杂度是 $O(\log_{10}S)$ 的，其中 $S=\displaystyle\sum_{i=1}^na_i$。需要执行 $n$ 次该操作，因此复杂度为 $O(n\log_{10}S)$。

总时间复杂度 $O((\log_{10}S)\sum n)$，可以通过本题。

### 参考核心代码

```cpp
void Add(long long a,long long b){
	long long carr=0,cnt=0,now=1;
	while(1){
		if(now>a&&now>b)
			break;
		long long w1=a/now%10,w2=b/now%10,tmp=w1+w2+carr;
		if(tmp>=10)
			cnt++;
		carr=tmp/10;
		now*=10;
	}
	ans+=cnt;
}
......
	for(i=1;i<n;i++){
		Add(a[i],a[i+1]);
		a[i+1]+=a[i];
	}
	printf("%lld\n",ans);

---

## 作者：Acheron_Styx (赞：0)

这题可以用高精度加法的思路。

用 $cnt$ 来记录答案，如 $cnt_1$ 记录第一位等等。

接下来就很简单了，直接模拟即可。

讲讲为什么可以直接模拟：

- 原数列无论怎么变，进位数是不变的，因为加法每次最多可进一位。

所以模拟即可。

```cpp
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		for(int i=1;i<=15;i++)
		{
			cnt[i]=0;
		}
		ret=0;
		int q;
		cin>>q;
		for(int i=1;i<=q;i++)
		{
			int n;
			cin>>n;
			for(int j=1;n>0;j++)//数位分解 
			{
				cnt[j]+=n%10;//相加同位 
				n/=10;
			}
		}
		for(int i=1;i<=15;i++)
		{
			ret+=cnt[i]/10;//进位 
			cnt[i+1]+=cnt[i]/10;
		}
		cout<<ret<<"\n";
	}
	return 0;
}
```

---

## 作者：Chenyichen0420 (赞：0)

# 题目大意

给你 $n$ 个数 $a_1,a_2,a_3,\dots,a_n$，问你怎样相加进位次数最小。

# 解法分析

这道题真的值得评黄吗？

我们知道一件事情，原数不论怎样排列，每一个位的进位的数量不变。又有加法每次最多进位一个，所以进位次数无论怎样排列也不会变。

下面附上代码：

```cpp
#include<iostream>
#include<cstring>
#include<bitset>
using namespace std;
int t, n, a, sly[16];
inline int read() {
	register int r = 0; register char c = getchar();
	while (c<'0' || c>'9') c = getchar();
	while (c >= '0' && c <= '9') r = (r << 3) + (r << 1) + (c ^ 48), c = getchar();
	return r;
}
inline void write(int x) {
	if (x > 9) write(x / 10);
	putchar(x % 10 + '0');
	return;
}
inline void slyp() {
	for (int i = 1; i <= 15; ++i)
		sly[i] += a % 10, a /= 10;
}
inline int cntt() {
	int tmp = 0;
	for (int i = 1; i <= 15; ++i)
		tmp += sly[i] / 10, sly[i + 1] += sly[i] / 10;
	return tmp;
}
int main() {
	t = read();
	while (t--) {
		n = read(); memset(sly, 0, sizeof sly);
		for (int i = 1; i <= n; ++i) a = read(), slyp();
		cout << cntt() << endl;
	}
}
```

---

## 作者：TruchyR (赞：0)

## Part 1 题意
求把 $n$ 个数排列后相加产生进位的最小次数。
## Part 2 思路
容易发现把这些数排列后：  
- 个位产生的和总数和进位总数是相同的。
- 由此，十位产生的和总数和进位总数是相同的。
- 由此，白位产生的和总数和进位总数是相同的。
- ……

那么，只需要直接计算进位次数就可以了。
## Part 3 代码
这里采用了一种比较抽象的计算方式。  
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,a,ans,jw;
string s,p;
int o(char oo){return int(oo-'0');}//字符转数字
int u(int oo){return char(oo+'0');}//数字转字符
signed main(){
	cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n;ans=0;p="00000000000000000000";
		while(n--){
			cin>>s;jw=0;
			s="00000000000000000000"+s; 
			for(int i=0;i<18;i++){
				int l=o(p[i])+o(s[s.size()-1-i])+jw;
				if(l>9){
					jw=1;ans++;
					p[i]=u(l-10);
				}else{
					p[i]=u(l);jw=0;
				}
			}
		}cout<<ans<<'\n';
	}
    return 0;
}
```


---

## 作者：tiger2008 (赞：0)

### 题解

这题小丑题。

随便找几个数来试试就可以发现，这 $n$ 个数的顺序和最终的进位次数无关。

所以直接从 $1$ 到 $n$ 扫一遍计算它的总进位次数即可。

### Code

```cpp
#include <iostream>
#include <cstdio>
#define int long long
using namespace std;
int T;
int arr[100005];
int add(int a,int b){
	int ans=0;
	int x=0;
	while(a || b){
		if(a%10+b%10+x>=10){
			x=1;
			ans++;
		}else x=0;
		a/=10;
		b/=10;
	}
	return ans;
}
signed main(){
	cin>>T;
	while(T--){
		int n;
		cin>>n;
		int ans=0;
		int tmp=0;
		for(int i=1;i<=n;i++){
			cin>>arr[i];
			ans+=add(tmp,arr[i]);
			tmp+=arr[i];
		}
		cout<<ans<<"\n";
	}
	return 0;
}

```


---

