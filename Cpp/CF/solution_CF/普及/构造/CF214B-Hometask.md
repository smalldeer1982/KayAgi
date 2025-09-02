# Hometask

## 题目描述

给定 $n$ 个范围在 $[0,9]$ 的整数，求用这 $n$ 个数能拼出的被 $2,3,5$ 同时整除且没有前导 $0$ 的最大整数是多少？（可以不用完所有数字）

## 样例 #1

### 输入

```
1
0
```

### 输出

```
0
```

## 样例 #2

### 输入

```
11
3 4 5 4 5 3 5 3 4 4 0
```

### 输出

```
5554443330
```

## 样例 #3

### 输入

```
8
3 2 5 1 5 2 2 3
```

### 输出

```
-1
```

# 题解

## 作者：L_zaa_L (赞：5)

## 分析
题目链接在[这里](https://www.luogu.com.cn/problem/CF214B)。

他给了我们 $n$ 个数，叫我们求由这些数组成的能被 2 3 5 整除的最大数。（可以不用完所有数字）

所以由题意我们可以得出最大数的末尾一定是 0——因为能被 2 整除的数末尾是二的倍数，能被 5 整除的数，末尾是五的倍数。

而三的倍数的变换规律是：各个数位上的和为三的倍数。

####  **输出 -1 的情况**
当给出的数没有 0 时，直接输出 ```-1```。其他情况就要输出最大值。

### 求最大值
这是本道题的最难之处，但是，当所有数字之和为三的倍数时，可以直接将这些数从大到小输出（0 就自动排在最后）。而不为三的倍数时，我们要删除一个数（要是最小的）使和成为三的倍数，当都没有时，只能删除两个数（只用两个即可）（要是最小的）使和成为三的倍数。

为什么只要两个呢？

假如当各个数字之和取余三之后为 1，那么只用删除一个对三取余为 1 的数，当如果没有这样的数时，可以找两个对三取余为 2 的数。（必须有 2 个，不然各个数字之和取余三之后不会为 1）。而当各个数字之和取余三之后为 2 时，同上，只不过最多找两个对三取余为 1 的数。

## Code
终于说到了代码了
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[100001],lin,sum;
int main(){
	cin>>n;
	int m=n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		if(a[i]==0) lin++;//求零的个数
		sum+=a[i];//求各个数之和
	}
	if(lin==0){//如果没有零，输出-1
		cout<<"-1";
		return 0;
	}
	sort(a+1,a+n+1);//排序，为求最大值铺垫
	if(sum%3!=0){
		int t=INT_MAX,s=0;
		for(int i=1;i<=n;i++){
			if(a[i]<t&&a[i]%3==sum%3){
				t=a[i];
				a[i]=-1; 
				m--;
				break;
			}
		}//删除一个数（最小），使全部数之和能被三整除
		if(t==INT_MAX){//如果不能删除一个数，那么删除两个数。
			for(int i=1;i<=n;i++){
				if(s==2) break;
				if(a[i]%3!=sum%3&&a[i]%3!=0){
					a[i]=-1;
					m--;
					s++;
				}
			}
		}
	}
	if(m==lin) cout<<"0";//当全部都为零时，要输出0
	else for(int i=n;i>=1;i--) if(a[i]!=-1) cout<<a[i];//要倒着输出，因为sort是从小到大排序
	return 0;
}
```

不知道为什么，我这个代码要加上许多无用的注释（没有任何字）才能过，不然一直 ```waiting```。

---

## 作者：Lovely_Chtholly (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/CF214B)

### 【分析】

知周所众，若 $1$ 个数可以同时被 $2,3,5$ 整除，那么它最后一位是 $0$ 且各位数之和为 $3$ 的倍数。

这里有 $2$ 种无解的情况：

1. 所给的数里没有 $0$。

1. 无法用所给数字组成 $3$ 的倍数。

第 $1$ 种无解的情况很容易判断，只需用桶存下数字个数，看看有没有 $0$ 即可。

第 $2$ 种无解情况的判断：每次需要删除一些使剩下数的和不是 $3$ 的倍数的数，而本身就是 $3$ 的倍数的数因为并不影响第 $2$ 种情况的判断，所以可以忽略，但是需要注意：

1. 删除尽量小的、尽量少的数可以使剩下的数更大。

1. 如果剩下的数无法组成 $3$ 的倍数，那就是无解。

### 【AC 代码】

```cpp
#include<stdio.h>
#include<iostream>
#include<stack>
using namespace std;
const int N=1e5+10;
inline int read(char ch=getchar(),int n=0,int m=1)
{
	while(ch<'0' or ch>'9')
	{
		if(ch=='-')m=-1;
		ch=getchar();
	}
	while(ch>='0' and ch<='9')n=(n<<3)+(n<<1)+ch-'0',ch=getchar();
	return n*m;
}
ostream& operator <<(ostream& o,__uint128_t &a)
{
	__uint128_t x=a;
	stack<int>s;
	while(x)s.push(x%10),x/=10;
	while(!s.empty())o<<s.top(),s.pop();
	return o;
}
int n=read(),a[N],sum,b[N];
signed main()
{
	for(int i=1;i<=n;i++)a[i]=read(),b[a[i]]++,sum+=a[i];
	if(!b[0])return puts("-1"),0;
	if(sum%3==1)
	{
		if(b[1])b[1]--,sum--;
		else if(b[4])b[4]--,sum-=4;
		else if(b[7])b[7]--,sum-=7;
		else if(b[2]>=2)b[2]-=2,sum-=4;
		else if(b[2]and b[5])b[2]--,b[5]--,sum-=7;
		else if(b[2]and b[8])b[2]--,b[8]--,sum-=10;
		else if(b[5]>=2)b[5]-=2,sum-=10;
		else if(b[5]and b[8])b[5]--,b[8]--,sum-=13;
		else if(b[8]>=2)b[8]-=2,sum-=16;
		else return puts("-1"),0;
	}
	else if(sum%3==2)
	{
		if(b[2])b[2]--,sum-=2;
		else if(b[5])b[5]--,sum-=5;
		else if(b[8])b[8]--,sum-=8;
		else if(b[1]>=2)b[1]-=2,sum-=2;
		else if(b[1]and b[4])b[1]--,b[4]--,sum-=5;
		else if(b[1]and b[7])b[1]--,b[7]--,sum-=8;
		else if(b[4]>=2)b[4]-=2,sum-=8;
		else if(b[4]and b[7])b[4]--,b[7]--,sum-=11;
		else if(b[7]>=2)b[7]-=2,sum-=14;
		else return puts("-1"),0;
	}
	if(!sum)return puts("0"),0;
	for(int i=9;i>=0;i--)
		for(int j=1;j<=b[i];j++)cout<<i;
	return 0;
}
```

ps：当我输出无解或特殊情况时，如果用 `return !puts("-1");` 就会 RE，但是用 `return puts("-1"),0;` 就不会。

---

## 作者：shuqiang (赞：2)

首先，整除的特征有:

- 当一个数能被 $2$ 整除时，它的末尾是 $0,2,4,6,8$。
- 当一个数能被 $3$ 整除时，这个数的各个位上的数的和是 $3$ 的倍数。
- 当一个数能被 $5$ 整除时，它的末尾是 $0,5$。

综上所述，一个数能同时被 $2,3,5$ 整除，它的末尾只能是 $0$ 且各个位上的数的和是 $3$ 的倍数。

由此得出，只要输入的数中没有 $0$，就无解，直接输出 $-1$。

求答案可以考虑用贪心算法，有以下步骤：
1. 用桶排序计数，同时求这些数字的和。
2. 如果输入的数字没有 $0$，直接输出 `-1`。
3. 分类讨论：
- 当数字和是 $3$ 的倍数时，直接从大到小输出数字。
- 当数字和不是 $3$ 时，优先删除小且的只需删 $1$ 个的数字的数来满足条件，如果无法满足条件，考虑删除 $2$ 个数字。
4. 如果删除到只剩下 $0$，就只能输出 $1$ 个 $0$。

AC 代码：
```cpp
#include<iostream>

using namespace std;

int n, t, c[10], s = 0;
bool f = 0;

int main(){
	cin >> n;
	for(int i = 0; i < n; i++){
		cin >> t;
		s += t;
		c[t]++;
	}
	if(c[0] == 0){
		cout << -1;
		return 0;
	}
	if(s % 3 == 1){
		if(c[1] > 0) c[1]--;
		else if(c[4] > 0) c[4]--;
		else if(c[7] > 0) c[7]--;
		else if(c[2] + c[5] + c[8] > 1){
			if(c[2] > 0) c[2]--;
			else if(c[5] > 0) c[5]--;
			else if(c[8] > 0) c[8]--;
			if(c[2] > 0) c[2]--;
			else if(c[5] > 0) c[5]--;
			else if(c[8] > 0) c[8]--;
		}
		else{
			cout << 0;
			return 0;
		}	
	}
	else if(s % 3 == 2){
		if(c[2] > 0) c[2]--;
		else if(c[5] > 0) c[5]--;
		else if(c[8] > 0) c[8]--;
		else if(c[1] + c[4] + c[7] > 1){
			if(c[1] > 0) c[1]--;
			else if(c[4] > 0) c[4]--;
			else if(c[7] > 0) c[7]--;
			if(c[1] > 0) c[1]--;
			else if(c[4] > 0) c[4]--;
			else if(c[7] > 0) c[7]--;
		}
		else{
			cout << -1;
			return 0;
		}
	}
	for(int i = 9; i >= 1; i--){
		if(c[i] > 0) f = 1;
		while(c[i]--) cout << i;
	}
	if(f) while(c[0]--) cout << 0;
	else cout << 0;
	return 0;
} 
```

---

## 作者：封禁用户 (赞：2)

## 题解：CF214B Hometask

### 解题思路

一道简单的数学题。

小奥就学过，很多数的倍数都有一些特殊性质：

- $2$ 的倍数末尾一定是：$2,4,6,8$ 或 $0$。
- $3$ 的倍数的所有数位之和为 $3$ 的倍数。
- $5$ 的倍数末尾一定是：$5$ 或 $0$。

由此，我们可以总结出可行的数一定有以下性质：

- 末尾一定是 $0$。
- 各位数字之和为 $3$ 的倍数。

我们可以用贪心的思路，优先填充较大的数字，得到最终的结果。

### 参考代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int n , a , b[15] , cnt;
int main()
{
    ios::sync_with_stdio(0);
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);//输入输出优化
    cin >> n;
    for(int i = 1 ; i <= n ; i++)
    {
    	cin >> a;
    	b[a]++;
	}
	if(b[0] == 0)
	{
		cout << "-1";
		return 0;
	}
	if(b[0] && !b[1] && !b[2] && !b[3] && !b[4] && !b[5] && !b[6] && !b[7] && !b[8] && !b[9])
	{
		cout << '0';
		return 0; 
	}
	for(int i = 1 ; i < 10 ; i++)
	{
		cnt += i * b[i];
	}
	if(cnt % 3 == 0)
	{
		for(int i = 9 ; i >= 0 ; i--)
		{
			while(b[i]--)
			{
				cout << i;
			}
		}
		return 0;
	}
	for(int i = 1 ; i < 10 ; i++)
	{
		if((cnt - i) % 3 == 0 && b[i])
		{
			b[i]--;
			if(b[0] && !b[1] && !b[2] && !b[3] && !b[4] && !b[5] && !b[6] && !b[7] && !b[8] && !b[9])
			{
				cout << '0';
				return 0; 
			}
			for(int j = 9 ; j >= 0 ; j--)
			{
				while(b[j]--)
				{
					cout << j;
				}
			}
			return 0;
		}
	}
	for(int i = 1 ; i < 10 ; i++)
	{
		for(int j = 1 ; j < 10 ; j++)
		{
			if((cnt - i - j) % 3 == 0)
			{
				if(i != j && b[i] && b[j])
				{
					b[i]--;
					b[j]--;
					if(b[0] && !b[1] && !b[2] && !b[3] && !b[4] && !b[5] && !b[6] && !b[7] && !b[8] && !b[9])
					{
						cout << '0';
						return 0; 
					}
					for(int k = 9 ; k >= 0 ; k--)
					{
						while(b[k]--)
						{
							cout << k;
						}
					}
					return 0;
				}
				if(i == j && b[i] >= 2)
				{
					b[i] -= 2;
					if(b[0] && !b[1] && !b[2] && !b[3] && !b[4] && !b[5] && !b[6] && !b[7] && !b[8] && !b[9])
					{
						cout << '0';
						return 0; 
					}
					for(int k = 9 ; k >= 0 ; k--)
					{
						while(b[k]--)
						{
							cout << k;
						}
					}
					return 0;
				}
			}
		}
	}
	cout << "-1";
    return 0;
}
```

---

## 作者：JackyBayer (赞：2)

思路：我们先把这一串数从大到小排序，保证最终的结果是最大的。

这题会涉及到整除的判断:

- 当一个数的末尾为 $0,2,4,6,8$ 的时候，可以被 $2$ 整除。

- 当一个数的数位和为 $3$ 的倍数的时候，可以被 $3$ 整除，不知道为什么的到文章的结尾看证明过程。

- 当一个数的末尾为 $0,5$ 的时候，可以被 $5$ 整除。

综上可得，只有末尾为 $0$ 才可以同时被 $2,5$ 整除。

所以我们需要判断末尾是否有 $0$，没有直接结束判断，再判断满不满足被 $3$ 整除，不可以整除 $3$ 的时候删掉适量的数。

**不懂？下面让我们来详细展开讲解：**

### 先判断是否可以整除 $10$

怎么做呢？看末尾有没有 $0$ 就行了，而且这题还可以自行排序！我们只需要判断有没有给你 $0$ 就行了，没有的话可以直接输出并结束程序。

### 再判断是否可以整除 $3$，此时我们有三种情况

我们可以开一个变量存数字和来判断是否可以整除 $3$。

#### 第一种情况：整除

此时直接把所有数字从大到小输出就行了，因为可以自行排序，我们可以让大的数字在前面，让小的数字在后面。

#### 第二种情况：除以 $3$ 余 $1$

这种情况下，我们最多删除 $2$ 个数字就可以满足整除 $3$，我们可以用反证法：

当需要删除 $3$ 个数才可以满足的情况（$0,1,2$ 表示除以 $3$ 的余数)：

- $1,1,1$：只用删一个 $1$。

- $1,1,2$：只用删一个 $1$。

- $1,2,2$：只用删一个 $1$。

- $2,2,2$：要删两个 $2$。

综上所述，最多删除两个数就可以满足整除 $3$，如条件不满足，直接输出 $0$。

所以我们可以删除一个 $1$ 或删除两个 $2$：

情况 $1$ 是删除一个 $1$，可以删：$1,4,7$。

情况 $2$ 是删除两个 $2$，可以删：$22,25,28,55,58,88$。

#### 第三种情况：除以 $3$ 余 $2$

这种情况下，我们也是最多删除 $2$ 个数字就可以满足整除 $3$，同理：

- $1,1,1$：要删两个 $1$。

- $1,1,2$：只用删一个 $2$。

- $1,2,2$：只用删一个 $2$。

- $2,2,2$：只用删一个 $2$。

同样的，最多删除两个数就可以满足整除 $3$，如条件不满足，直接输出 $0$。

所以我们可以删除一个 $1$ 或删除两个 $2$：

情况 $1$ 是删除一个 $2$，可以删：$2,5,8$。

情况 $2$ 是删除两个 $1$，可以删：$11,14,17,44,47,77$。

**一点要优先删小的数！！！**

**切记！一定要特判前导零，有可能 $1\sim9$ 全被删了！**

为了避免这种情况，我们可以再次用上之前开的存数字和的变量，将删除的数字减去，判断是否为 $0$，就知道有没有前导 $0$ 了，通俗点就是 $0$ 前面的数字是不是全被删了。

### 下面奉上完整代码

```cpp
#include<bits/stdc++.h>
using namespace std;

int a[10];

int main(){
	int n,sum=0;
	cin>>n;
	for(int i=1,x;i<=n;i++)cin>>x,sum+=x,a[x]++;
	if(!a[0])return cout<<"-1",0;
	if(sum%3==1){
		if(a[1])a[1]--,sum-=1;
		else if(a[4]) a[4]--,sum-=4;
		else if(a[7])a[7]--,sum-=7;
		else if(a[2]>=2)a[2]-=2,sum-=4;
		else if(a[2]&&a[5])a[2]--,a[5]--,sum-=7;
		else if(a[2]&&a[8])a[2]--,a[8]--,sum-=10;
		else if(a[5]>=2)a[5]-=2,sum-=10;
		else if(a[5]&&a[8])a[5]--,a[8]--,sum-=13;
		else if(a[8]>=2)a[8]-=2,sum-=16;
		else return cout<<"-1",0;
	}
	if(sum%3==2){
		if(a[2])a[2]--,sum-=2;
		else if(a[5])a[5]--,sum-=5;
		else if(a[8])a[8]--,sum-=8;
		else if(a[1]>=2)a[1]-=2,sum-=2;
		else if(a[1]&&a[4])a[1]--,a[4]--,sum-=5;
		else if(a[1]&&a[7])a[1]--,a[7]--,sum-=8;
		else if(a[4]>=2)a[4]-=2,sum-=8;
		else if(a[4]&&a[7])a[4]--,a[7]--,sum-=11;
		else if(a[7]>=2)a[7]-=2,sum-=14;
		else return cout<<"-1",0;
	}
	if(!sum)return cout<<"0",0;
	for(int i=9;i>=0;i--){
		for(int j=1;j<=a[i];j++)cout<<i;
	}
	return 0;
}

```

#### 证明：当一个数的数位和为 $3$ 的倍数的时候，可以被 $3$ 整除

对于任何一个被除 $3$ 取余的整数 $A$，我们将它的第 $i$ 高位记为 $A_i$，
那么我们可以将 $A$ 看成 $(10^{n-1}\times A_1+10^{n-2}\times A_2+10^{n-3}\times A_3+...+10^1\times A_{n-1}+10^0\times A_n)\bmod3$，已知 
$10\equiv 1\pmod{3}$，根据余数的加减性，我们可以得知原数 $A \bmod3$ 等于 $(1^{n-1}\times A_1+1^{n-2}\times A_2+10^{n-3}\times A_3+...+1^1\times A_{n-1}+1^0\times A_n)\bmod3$，化简得 $( A_1+A_2+...+A_{n-1}+A_n)\mod3$，也就是 $A$ 的数字和除 $3$ 求余。

---

## 作者：smydahaoren (赞：1)

### **思路分析**：

题目给定一些数字，要求拼出一个数 $n$，使得：

- $n$ 可以被 $2$，$3$，$5$ 整除。

求 $n$ 的最大值。

根据 $n$ 可以被 $2$，$5$ 整除，得知 $n$ 最后一位必须是 $0$，其次 $n$ 所有数字之和是 $3$ 的倍数。

#### 不成立条件：

- 给定数字中没有 $0$。

对于没有 $0$ 的情况直接输出 $-1$。

然后统计题目给定所有数的和，来确定要删去几个数，什么数才能满足 $n$ 所有数字之和是 $3$ 的倍数，有两种情况。


- 当数字和是 $3$ 的倍数时，直接从大向小输出得到最大值。
- 当数字和除以 $3$ 有余数时，先从小到大尝试去掉一个数，如果都不行，继续尝试尽可能优先去掉小的数，然后去尽可能小的数，来满足要求。这样操作可以保证数位最长，数最大，从而确定取到的是最大值。

如此操作可以让 $n$ 取到最大值。



------------
### **AC 代码：**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=100009;
int a,k[10],cnt,n;//a用来输入 ，k统计每个数字的个数 
void print(){
		if(cnt<=0) {
			cout<<"0";
			return;
		}
		for(int i=9;i>=0;i--){
		for(int j=1;j<=k[i];j++)cout<<i;
		}
		return;
}
int main(){
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>a;
		cnt+=a;
		k[a]++; 
	}
	if(k[0]==0){
		cout<<"-1";
		return 0;
	}
	if(cnt%3==0){
		print();
	}
	if(cnt%3==1){
		if(k[1]>=1) k[1]--,cnt--,print();
		else if(k[4]>=1) k[4]--,cnt-=4,print();
		else if(k[7]>=1) k[7]--,cnt-=7,print();
		else if(k[2]>=2) k[2]-=2,cnt-=4,print();
		else if(k[2]>=1&&k[5]>=1) k[2]--,k[5]--,cnt-=7,print();
		else if(k[2]>=1&&k[8]>=1) k[2]--,k[8]--,cnt-=10,print();
		else if(k[5]>=2) k[5]-=2,cnt-=10,print();
		else if(k[5]>=1&&k[8]>=1) k[5]--,k[8]--,cnt-=13,print();
		else if(k[8]>=2) k[8]-=2,cnt-=16,print();
	}
	if(cnt%3==2){
		if(k[2]>=1) k[2]--,cnt-=2,print();
		else if(k[5]>=1) k[5]--,cnt-=5,print();
		else if(k[8]>=1) k[8]--,cnt-=8,print();
		else if(k[1]>=2) k[1]-=2,cnt-=2,print();
		else if(k[1]>=1&&k[4]>=1) k[1]--,k[4]--,cnt-=5,print();
		else if(k[1]>=1&&k[7]>=1) k[1]--,k[7]--,cnt-=8,print();
		else if(k[4]>=2) k[4]-=2,cnt-=8,print();
		else if(k[4]>=1&&k[7]>=1) k[4]--,k[7]--,cnt-=11,print();
		else if(k[7]>=2) k[7]-=2,cnt-=14,print();
	}
	return 0;
}
```


---

## 作者：Furina_Hate_Comma (赞：1)

题目要求：

给定 $n$ 个整数，求通过组合来得到的最大的可以被 $2,3,5$ 整除的数字。

题目分析：

被 $2,5$ 整除非常容易，我们知道：如果 $k$ 可以 $a,b$ 整除，则 $k$ 可以被 $a \times b$ 整除。

而被 $3$ 整除的数的各位数字和为 $3$。

于是如果其中没有 $0$，就是 $-1$，因为只要有 $0$，就有这个可行解。

而如果无法整除 $3$ 可以删除一个或者两个。

然后贪心思路：

能删一个**绝不**删两个。

能删小的**绝对**不删大的。

最后结果大的能放前面就**绝对不放**后面。

code

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[10000000];
int main(){
	int n,sum=0;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		sum+=a[i];
	}
	sort(a+1,a+1+n);
	if(a[1]!=0){
		cout<<-1;
		return 0;
	}if(sum%3==1){
		int tot=0;
		for(int i=1;i<=n;i++){
			if(a[i]%3==1){
				a[i]=-1;
				tot++;
				break;
			}
		}
		if(!tot){
			tot=0;
			for(int i=1;i<=n;i++){
				if(tot==2)break;
				if(a[i]%3==2){
					a[i]=-1;
					tot++;
				}
			} 
		}
	}else{
		int tot=0;
		for(int i=1;i<=n;i++){
			if( a[i]%3==2){
				a[i]=-1;
				tot++;
				break;
			}
		}
		if(!tot){
			tot=0;
			for(int i=1;i<=n;i++){
				if(tot==2)break;
				if(a[i]%3==1){
					a[i]=-1;
					tot++;
				}
			} 
		}
	}
	queue<int>q;
	int i=n;
	for(;i>=1;i--)if(a[i]!=-1)q.push(a[i]);
	while(!q.empty()&&q.front()==0)
			q.pop();
	if(q.empty())cout<<0;
	while(!q.empty()){
		cout<<q.front();
		q.pop();
	}
	return 0;
}
```

---

## 作者：liuzhongrui (赞：0)

## 思路

题目中说要能拼出能被 $2,3,5$ 整除，为了满足被 $2,5$ 同时整除，拼出的数末尾要有个 $0$，因为 $2 \times 5 = 10$。因此我们在读入的时侯统计一下，看看有没有 $0$，如果没有那说明不存在满足条件的数，此时输出 ```-1``` 即可。

接下来看满足能被 $3$ 整除的数，应满足各个数位上的数之和能被 $3$ 整除，如果能就进入下一步操作，若不能，找到最小的数，满足删除它之后能满足条件，此时所组成的数就是最大的。

可以用桶计数来解决，输出时只需从大的数开始输出，先把大的数输出完，再输出小的数，输出每个数的个数就是它在操作完后桶里这个数的个数。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,d[10],a,sum;
int main() {
	cin>>n;
	while(n--) {
		cin>>a,++d[a],sum+=a;
	}
	if(sum%3) {
		for(int i=1; i<10; i++) {
			if(i%3==sum%3 && d[i]) {
				--d[i];
				sum-=i;
				i=10;
			}
		}
	}
	for(n=0; n<2; n++) {
		for(int i=1; i<10; i++) {
			if(sum%3 && i%3 && d[i]) {
				--d[i];
				sum-=i;
				i=10;
			}
		}
	}
	if(!sum) {
		d[0] = 1;
	} else if(!d[0]) {
		cout<<-1;
		return 0;
	}
	for(int i=9; i>=0; i--) {
		while(d[i]--) {
			cout<<i;
		}
	}
	return 0;
}
```

---

## 作者：QWQ_123 (赞：0)

考虑由于可以被 $2,5$ 整除，所以这个数一定是 $10$ 的倍数，也就是说这个数列中若合法一定至少有 $1$ 个 $0$。

然后考虑被 $3$ 整除，因为被 $3$ 整除的数字各个数位上的数字之和是 $3$ 的倍数，那么先将 $\bmod 3=0$ 的数加入序列。

然后对于 $\bmod 3= 1$ 和 $\bmod 3 = 2$ 的数字，设有 $sz1,sz2$ 个，不妨设 $sz1 > sz2$。

若 $sz1 \bmod 3 = sz2 \bmod 3$，那么都可以取完，都加入序列即可。

若 $(sz1-sz2) \bmod 3=2$，那么显然要 $sz2$ 少取一个，让 $sz1$ 全取完，否则若让 $sz2$ 取完，则只有 $sz1+sz2-2$ 个数，但是若是让 $sz2$ 少取一个，则是 $sz1+sz2-1$ 个数。

若 $(sz1-sz2) \bmod 3=1$，那么就是直接取即可，因为这样让 $sz2$ 去凑 $sz1$ 的整除显然不优（因为要耗费 $2$ 个 $sz2$，只能获得 $1$ 个 $sz1$）。

对于 $sz2 =0$ 时特殊考虑一下（因为这样 $sz2$ 没法补 $sz1$），就直接在 $sz1$ 中三个三个取即可。

在 $sz2 \ge sz1$ 时同理。

```cpp
#include <bits/stdc++.h>

using namespace std;

int n;
vector<int> t;
vector<int> v1, v2;

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		int v; scanf("%d", &v);
		if (v % 3 == 0) t.push_back(v);
		else if (v % 3 == 1) v1.push_back(v);
		else v2.push_back(v);
	}

	if (v1.size() < v2.size()) swap(v1, v2);

	if ((int)v1.size() % 3 == (int)v2.size() % 3) {
		for (auto v : v1) t.push_back(v);
		for (auto v : v2) t.push_back(v);
	} else {
		if (v1.size() >= 3 && v2.size() != 0) {
			int p = (v1.size() - v2.size()) % 3;

			if (p == 2) {
				sort(v2.begin(), v2.end());
				for (auto v : v1) t.push_back(v);
				for (int i = 1; i < (int)v2.size(); ++i) t.push_back(v2[i]);
			} else {
				sort(v1.begin(), v1.end());
				for (int i = 1; i < (int)v1.size(); ++i) t.push_back(v1[i]);
				for (auto v : v2) t.push_back(v);
			}
		} else if (v2.size() == 0) {
			for (int i = 0; i + 2 < (int)v1.size(); i += 3) {
				t.push_back(v1[i]);
				t.push_back(v1[i + 1]);
				t.push_back(v1[i + 2]);
			}
		}
	}

	sort(t.begin(), t.end(), greater<int>());

	if (t.back() != 0) {
		puts("-1");
		return 0;
	}

	if (t[0] == 0) puts("0");
	else {
		for (auto v : t) printf("%d", v);
	}

	return 0;
}
```

---

## 作者：Mu_tr (赞：0)

# 题目大意
给定你 $n$ 个整数数字，范围在 $[0,9]$，问用这 $n$ 个数字拼起来的最大且这个数字没有前导 $0$ 不是 $0$，还能够被 $2,3,5$ 整除的数是多少？

# 题目思路
因为最后拼出来的数必须能被 $2,3,5$ 整除，所以最后一位数一定是 $0$，且各位数字之和是 $3$ 的倍数。
## 无解情况
1. 因为末尾必须是 $0$，所以如果一个 $0$ 都没有必定无解。
2. 因为各位数字之和必定是 $3$ 的倍数，所以如果怎么删数字都做不到 $3$ 的倍数，一定无解。

## 贪心寻找最大数
首先 $0,3,6,9$ 这四个数字跟无解情况的第二种没有关系可以不看，如果这 $n$ 个数字之和，不为 $3$ 的倍数，我们就要贪心地选取一些数删掉。这里有三条定则。

1. 删相同数量的数，删小的数必定比删大的数优。 
2. 删一个数必定比删两个数优。
3. 如果怎么删都删不成 $3$ 的倍数，那一定是无解。

依据这三条我们就可以写出下面的 $AC$ 代码了。

注意各种情况的分类讨论

# AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a,vis[10],sum;
bool flag=1;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') f=-1;
		ch=getchar(); 
	}
	while(ch>='0'&&ch<='9'){
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x*f;
}
int main(){
	n=read();
	for(int i=1;i<=n;i++){
		a=read();
		vis[a]++;
		sum+=a;
	}
	if(!vis[0]){
		puts("-1");
		return 0;
	}
	if(sum%3==1){
		if(vis[1]||vis[4]||vis[7]){
			if(vis[1]) vis[1]--,sum--;
			if(sum%3==1&&vis[4]) vis[4]--,sum-=4;
			if(sum%3==1&&vis[7]) vis[7]--,sum-=7;
		}
		else if((vis[2]+vis[5]+vis[8])>=2){
			if(vis[2]>=2) vis[2]-=2,sum-=4;
			else if(vis[2]==1){
				vis[2]--,sum-=2;
				if(vis[5]) vis[5]--,sum-=5;
				if(sum%3==2&&vis[8]) vis[8]--,sum-=8;
			} 
			else if(vis[5]>=2) vis[5]-=2,sum-=10;
			else if(vis[5]==1){
				vis[5]--,sum-=5;
				if(vis[8]) vis[8]--,sum-=8;
			}
			else if(vis[8]>=2) vis[8]-=2,sum-=16;
			else{
				puts("-1");
				return 0;
			}
		}
		else{
			puts("-1");
			return 0;
		}
	}
	if(sum%3==2){
		if(vis[2]||vis[5]||vis[8]){
			if(vis[2]) vis[2]--,sum--;
			if(sum%3==2&&vis[5]) vis[5]--,sum-=5;
			if(sum%3==2&&vis[8]) vis[8]--,sum-=8;
		}
		else if((vis[1]+vis[4]+vis[7])>=2){
			if(vis[1]>=2) vis[1]-=2,sum-=2;
			else if(vis[1]==1){
				vis[1]--,sum-=1;
				if(vis[4]) vis[4]--,sum-=4;
				if(sum%3==1&&vis[7]) vis[7]--,sum-=7;
			} 
			else if(vis[4]>=2) vis[4]-=2,sum-=8;
			else if(vis[4]==1){
				vis[4]--,sum-=4;
				if(vis[7]) vis[7]--,sum-=7;
			}
			else if(vis[7]>=2) vis[7]-=2,sum-=14;
			else{
				puts("-1");
				return 0;
			}
		}
		else{
			puts("-1");
			return 0;
		}
	}
	for(int i=0;i<=9;i++) if(i>0&&vis[i]>0) flag=0;
	if(flag){
		puts("0");
		return 0;
	}
	for(int i=9;i>=0;i--) for(int j=1;j<=vis[i];j++) putchar(i+'0');
	return 0;
}
```


---

## 作者：Transparent (赞：0)

### 题目大意：
给你一组数字，
把它们组合成一个数，
可以有部分数字不使用。
让这个数可以被 $2$ 、 $3$ 、 $5$ 同时整除，
你需要找出符合条件的最大的数，
这个数不应有前导 $0$ ，
若无论如何也不可能满足条件，
就输出 $-1$ 。

### 方法：贪心+数学
~~为什么CF上还有暴力的标签……~~

对于一个可以被 $2$ 和 $5$ 同时整除的数，
它一定可以被 $10$ 整除，
因此最后一位必须为 $0$ 。
所以如果所有数字中没有一个 $0$ ，
那么一定不可能满足条件。

对于一个可以被 $3$ 整除的数，
它的各位数字之和一定能被 $3$ 整除，
反之亦然。

所以可以先计算出数字和，

- 若正好可以被 $3$ 整除，
那就不管。

- 若 $\operatorname{mod} 3 = 1$ ，
就需要从所有数字中去掉 $1$ 个
最小的$\operatorname{mod} 3 = 1$ 的数字。
如果没有这样的数字，
还可以去掉 $2$ 个 $\operatorname{mod} 3 = 2$ 的数字，
如果还没有，
那就证明不可能满足条件。

- 若 $\operatorname{mod} 3 = 2$ ，
就需要从所有数字中去掉 $1$ 个
最小的$\operatorname{mod} 3 = 2$ 的数字。
如果没有这样的数字，
还可以去掉 $2$ 个 $\operatorname{mod} 3 = 1$ 的数字，
如果还没有，
那也证明不可能满足条件。

为了让结果最大，
就应该降序输出，
而没有 $0$ 的情况已经排除，
并且 $0$ 是数字中最小的一个（注意是数字，不是数），
所以 $0$ 一定在最后，
这样输出的数也就一定满足条件。
~~其实也就这么点儿是贪心……~~

### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1000001],n,sum,m1,m2,cant1,cant2,Mod;
bool f;
int main()
{
	scanf("%d",&n);
	for(register int i=1;i<=n;i++)
	{
		scanf("%d",a+i);
		sum+=a[i];//处理数字和 
		if(a[i]%3==1)
		m1++;//记录余数为1的数的个数，便于之后的统计判断 
		if(a[i]%3==2)
		m2++;//记录余数为2的数的个数
	}
	sort(a+1,a+n+1);//从小到大排序 
	if(a[1]!=0)//最小的数都不是0，证明数列中没有0 
	{
		printf("-1\n");
		return 0;
	}
	Mod=sum%3;//简化一下代码 
	if(Mod==1&&m1==0&&m2<2)//没有足够的数来填余数的坑 
	{
		printf("-1\n");
		return 0;
	}
	if(Mod==2&&m2==0&&m1<2)//同上 
	{
		printf("-1\n");
		return 0;
	}
	if(Mod==1)//余数为1的情况 
	{
		if(m1==0)//没有余数为1的数字 
		{
			for(register int i=1;i<=n;++i)
			{
				if(a[i]%3==2)
				{
					if(!cant1)
					cant1=i;
					else
					cant2=i;
				}
				if(cant2)
				break;
			}//取2个余数为2的数字 
		}
		else//有余数为1的数字 
		{
			for(register int i=1;i<=n;++i)
			{
				if(a[i]%3==1)
				{
					if(!cant1)
					{
						cant1=i;
						break;
					}
				}
			}//取走一个余数为1的数字 
		}
	}
	else if(Mod==2)//余数为2的情况 
	{
		if(m2==0)//没有余数为2的数字 
		{
			for(register int i=1;i<=n;++i)
			{
				if(a[i]%3==1)
				{
					if(!cant1)
					cant1=i;
					else
					cant2=i;
				}
				if(cant2)
				break;
			}//取走2个余数为1的数字 
		}
		else//有余数为2的数字 
		{
			for(register int i=1;i<=n;++i)
			{
				if(a[i]%3==2)
				{
					if(!cant1)
					{
						cant1=i;
						break;
					}
				}
			}//取走1个余数为2的数字 
		}
	}
	//统一说明：因为数组是有序的，所以以上的操作会优先取走较大的数字 
	for(register int i=n;i>=1;--i)
	{
		if(cant1!=i&&cant2!=i)
		{
			if(a[i]==0&&f)//f标记防止前导0 
			printf("%d",a[i]);
			if(a[i]!=0)//有非0的数字了 
			{
				printf("%d",a[i]);
				f=1;//之后的0就不是前导0了 
			}
		}
	}
	if(!f)//自始至终没有一个非0的数字 
	printf("0");//补上0 
	printf("\n");//结尾换行，不换也行吧
	return 0;
}
```


---

