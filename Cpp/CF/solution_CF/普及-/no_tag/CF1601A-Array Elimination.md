# Array Elimination

## 题目描述

有一个长度为 $n$ 的序列 $a_1,a_2,\dots,a_n$，每次操作选择 $k$ 个数，将这 $k$ 个数减去他们的与（二进制运算中的与）的和。求哪些 $k$ 可以在有限次操作内使所有数变成 $0$。

## 说明/提示

$1\le t\le10^4,1\le\sum n\le2\times10^5,0\le a_i<2^{30}$。

## 样例 #1

### 输入

```
5
4
4 4 4 4
4
13 7 25 19
6
3 5 3 1 7 1
1
1
5
0 0 0 0 0```

### 输出

```
1 2 4
1 2
1
1
1 2 3 4 5```

# 题解

## 作者：water_tomato (赞：4)

本文同步发表于个人博客：[Link](https://www.watertomato.com/cf1601a-array-elimination-%e9%a2%98%e8%a7%a3/)。

## 题意

[题目链接](https://www.luogu.com.cn/problem/CF1601A)。

有一个长度为 $n$ 的序列 $a_1,a_2,\dots,a_n$，每次操作选择 $k$ 个数，将这 $k$ 个数减去他们的与（二进制运算中的与）的和。求哪些 $k$ 可以在有限次操作内使所有数变成 $0$。

## 解析

蛮有趣的。把所有数化成二进制后，你考虑每一位。如果共有 $x$ 个数在某一位上为 $1$，那么考虑如果指定了一个 $k$，那么这一位显然每次只能减少 $k$ 个 $1$ 或 $0$ 个 $1$。换言之，如果想要让这一位上全部变为 $0$，需要满足 $k|x$。

发现在这个过程中，每一位是独立的，因为可行的 $k$ 为每一位的 $x$ 的因子，即我们只需要求出每一位上为 $1$ 的数的个数，再将这些个数求一个 $\gcd$，这个求得的 $\gcd$ 的所有因子即为可行的 $k$。

特别的，如果所有数均为 $0$，答案显然可以为 $1\sim n$ 的所有数。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int T,n,a[N],t[50];
inline int gcd(int a,int b){
	return b==0?a:gcd(b,a%b);
}
vector<int> ans;
inline void print(int x){//求答案
	ans.clear();
	for(int i=1;i<=sqrt(x);i++){
		if(x%i==0){
			ans.push_back(i);
			if(i*i!=x) ans.push_back(x/i);
		}
	}
	sort(ans.begin(),ans.end());
	for(auto x:ans) printf("%d ",x);
	printf("\n");
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);for(int i=0;i<=30;i++) t[i]=0;
		for(int i=1,x;i<=n;i++){
			scanf("%d",&x);
			for(int j=0;j<=30;j++){
				if(x&(1<<j)) t[j]++;//统计个数
			}
		}
		int g=0;
		for(int j=0;j<=30;j++) g=gcd(g,t[j]);//求 gcd
		if(g==0){for(int i=1;i<=n;i++) printf("%d ",i);printf("\n");}//特判全部为 0
		else print(g);
	}
}
```

---

## 作者：XL4453 (赞：1)

### 解题思路：

发现对于每一个二进制数位操作是独立的，那么不妨将其分解下来做。

对于每一个二进制数位，每一次操作相当于将其选 $k$ 个在这一位上都是 $1$ 的数消去这一位（将其变成 $0$）。那么，如果想要全部消去，$k$ 就必须是这个数位上的 $1$
 的个数的一个因数。
 
综合看，也就是要求最终的 $k$ 是所有数位的 $1$ 的个数的因数，直接统计一下然后暴力求就可以了。这里发现，当 $k$ 等于  $1$ 的时候，无论如何都是满足的，这也就回应了题目中的一定有解。

数出每一位上数的个数要 $O(n\log n)$ 的复杂度，算出因数个数最坏 $O(\sqrt n)$ 可以接受。

注意特判全是 $0$ 的情况。

---
### 代码：

注：本代码用 $O(n)$ 方法求因数，也是可以通过的。

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
#define int long long
int n,a[200005],T,cnt[50];
void calc(int num){
	for(int i=0;i<=32;i++)
	if((num>>i)&1)cnt[i]++;
}
int gcd(int a,int b){
	if(b==0)return a;
	return gcd(b,a%b);
}
signed main(){
	scanf("%I64d",&T);
	while(T--){
		scanf("%I64d",&n);
		memset(cnt,0,sizeof(cnt));
		for(int i=1;i<=n;i++){
			scanf("%I64d",&a[i]);
			calc(a[i]);
		}
		int GCD=-1;
		for(int i=0;i<=31;i++)
		if(cnt[i]!=0){
			if(GCD==-1)GCD=cnt[i];
			GCD=gcd(GCD,cnt[i]);
		}
		if(GCD!=-1){
			for(int i=1;i<=GCD;i++)
			if(GCD%i==0)printf("%I64d ",i);
		}
		else{
			for(int i=1;i<=n;i++)
			printf("%I64d ",i);
		}
		printf("\n");
	}
	return 0;
}
```


---

## 作者：xfrvq (赞：1)

[$\texttt{CF1601A Array Elimination}$](https://www.luogu.com.cn/problem/CF1601A)

---

有趣的思维题。

可以确定当有 $m$ 个数二进制第 $i$ 位为 $1$ 时，答案 $k$ 必须是 $m$ 的因数，不然不可能取完 $m$ 个。

于是我们只需要记录下所有二进制位的出现次数，然后求 $\gcd$ 就好。

如果所有数都为 $0$，答案就是 $1\sim n$ 的所有数

---

```cpp
#include<stdio.h>

int gcd(int x,int y){
	return y ? gcd(y,x % y) : x;
}

int c[32];

int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		int n;
		scanf("%d",&n);
		for(int i = 0;i <= 31;++i) c[i] = 0; // 多测清空
		for(int i = 1;i <= n;++i){
			int x;
			scanf("%d",&x);
			for(int j = 0;x;++j,x >>= 1) if(x & 1) ++c[j]; // 每位拆开
		}
		int x = 0;
		for(int i = 0;i <= 31;++i)
			x = gcd(c[i],x);
		for(int i = 1;i <= n;++i) // 当全部数都为0的时候，x=0，x%1~n的所有数也都等于0，就都会输出
			if(x % i == 0) printf("%d ",i);
		printf("\n");
	}
	return 0;
}
```

---

## 作者：摸鱼酱 (赞：1)

考虑每一位是独立的，设二进制下第 $i$ 位为 $1$ 的有 $c_i$ 个，则答案为非零的 $\gcd\{c_i\}$ 的所有因子。

特殊的，若序列全为 $0$，则答案为 $1$ 到 $n$ 的所有数。

因为显然每一步只能消掉恰好 $0$ 或 $k$ 个第 $i$ 位上的 $1$，只有 $k|c_i$ 才能恰好消完。时间复杂度 $O(n\log a_i)$。

[code](https://codeforces.com/contest/1601/submission/132992117)。

---

## 作者：tkdqmx (赞：0)

考虑什么时候 $t$ 是合法的：

对于位运算的题目，一般会转换成二进制来考虑。

我们设第 $2^x$ 位从 $a_1$ 到 $a_n$ 中共有 $cnt(x)$ 个 $1$。

如果 ${a_i}_1$ 到 ${a_i}_k$ 当中有一个数第 $2^x$ 位上是 $0$，则是没有意义的。

所以选中的 $k$ 个数当中必需第 $2^x$ 位上是 $1$。

那么对于当前的 $k$ 能被消完，则 $cnt(x) \equiv 0 \pmod k$。

且 $k$ 只能是 $cnt(0)$ 到 $cnt(29)$ 的 $\gcd$ 的因数。

特殊情况：当 $cnt(0)$ 到 $cnt(29)$ 的 $\gcd$ 为 $0$ 时，$1$ 到 $n$ 均是合法 $k$。

代码如下：

~~~cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,cnt,a[200005];
int main(){
	cin>>t;
	while(t--){
		cin>>n,cnt=0;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			if(a[i]&1)	cnt++;
		}
		for(int i=1,t=0;i<30;i++,t=0){
			for(int j=1;j<=n;j++){
				a[j]>>=1;
				if(a[j]&1)	t++;
			}
			cnt=__gcd(cnt,t);
		}
		if(cnt==0){
			for(int i=1;i<=n;i++)	cout<<i<<" ";
			cout<<"\n";
			continue;
		}
		for(int i=1;i<=cnt;i++)
			if(cnt%i==0)
				cout<<i<<" ";
		cout<<"\n";
	}
}
~~~

---

## 作者：MornStar (赞：0)

# CF1601A Array Elimination 题解

从与运算入手，可以发现其针对的是二进制位。

将样例中的数拆成二进制，不难发现如果一次可以选择的数 $x$ 如果不满足对于所有数第 $i$ 位 $a_i$ 有 $x\mid a_i$，那么最后参与运算的数至少有一个第 $i$ 位为 $0$。以至于整个运算无效，使得序列不能清零。

因此，对二进制每一位上 $1$ 的个数求最大公约数，再求出最大公约数所有的因子即为答案。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long gcd(long long a,long long b){return b==0?a:gcd(b,a%b);}
long long t,n,a[200005],sum[35],ans;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--){
		ans=0;
		cin>>n;
		for(int i=1;i<=n;i++)	cin>>a[i];
		for(int i=1;i<=30;i++){
			sum[i]=0;
			for(int j=1;j<=n;j++){
				sum[i]+=(a[j]&1);
				a[j]>>=1;
			}
		}
		for(int i=1;i<=30;i++){
			if(sum[i]&&ans==0)	ans=sum[i];
			if(sum[i]&&ans!=0)	ans=gcd(ans,sum[i]);
		}
		for(int i=1;i<=n;i++){
			if(ans%i==0)	cout<<i<<" ";
		}
		cout<<endl;
	}
}
```



---

## 作者：qscisQJing (赞：0)



~~相信大家都知道二进制与是什么吧，这里不讲了~~



------------
对所有二进制的题我们都有两个通法：

- 对异或，前缀和
- 对二进制与和或，分解每一位

我们可以试试第二个方法

看向 $ 13 $ , $ 7 $ , $25$ , $19$ 这几个数。把它们转换成二进制

变成了 $01101$ , $00111$ , $11001$ , $01011$.

好像和 $2$ 扯不上关系。

我们不妨看回题目：“让 $k$ 个数减去它们的与”

对于每一位来说，如果这 $k$ 个中有一个 $0$ ,这一位就不用减了。

反之，只有它们都是 $1$ 的时候这 $k$ 个数才能变成零。

想到这里，结论就很明显了：把每个数二进制取出来后，每一位的   $1$的数量的 $gcd$ 就是 $ans$ 。

然后把 $ans$ 的所有因数输出就可以了。


------------
# AC代码
```
#include<bits/stdc++.h>
using namespace std;
const int MAXN=2e5+5;
int a[MAXN];
int tr[31];//tr[i]代表第i位出现了几个1
void solve(int x)
{
	for(int i=0;x;x>>=1,i++)
		if(x&1)tr[i]++;
}
int gcd(int x,int y)
{
	if(x%y==0)return y;
	return gcd(y,x%y);
}
void out(int x)
{
	for(int i=1;i<=x;i++)
	{
		if(x%i==0)cout<<i<<" ";
	}
	cout<<endl;
	return;
}
int main()
{
	int t,n;
	cin>>t;
	while(t--)
	{
		cin>>n;
		for(int i=1;i<=n;i++)scanf("%d",a+i);
		for(int i=1;i<=n;i++)
			solve(a[i]);
		int sum=-1;
		for(int i=0;i<=30;i++)
		{
			if(tr[i])
			{
				if(sum==-1)sum=tr[i];
				else 
				{
					sum=gcd(sum,tr[i]);
				}
			}
		}
		if(sum==-1)//如果全是零就输出1~n
		{
			for(int i=1;i<=n;i++)cout<<i<<" ";
			cout<<endl;
			continue;
		}
		out(sum);
		memset(tr,0,sizeof tr);//一定要记得清零
	}
	return 0;//完结撒花
}
```



---

## 作者：little_sheep917 (赞：0)

> 给出一个自然数组成的序列 $a_1,a_2,\cdots ,a_n$ .
>
> 选定一个数 $k$ ，可以一次做以下的操作任意多次 .
>
> - 选择 $k$ 个互不相同的下表  , $1\leq i_1<i_2<\cdots<i_k\leq n$ .
> - 计算得到 $x=a_{i_1}\&a_{i_2}\&\cdots \&a_{i_k}$ . 
> - 对于 $a_{i_1},a_{i_2},\cdots,a_{i_k}$ 全部减 $x$ .
>
> 如果当前的 $k$ ，能在任意多次操作下使的 $a_1,a_2,\cdots,a_n$ 变为 $0$ ，则称 $k$ 是好的 .
>
> 求出所有好的 $k$ . 
>
> 多测，有 $t$ 个测试点 .
>
> $1\leq t\leq 10^4,1\leq n\leq 2\cdot 10^5,0\leq a_i<2^{30},\sum n\leq 2\cdot 10^5$ 

考虑什么情况下 $k$ 是合法的 .

对于位运算，常用的套路是拆开来考虑 .

对于 $2^x$ 的位，在 $a_1$ 到 $a_n$ 中 $2^x$ 上为 $1$ 的有 $cnt(x)$ 个 .

如果 $a_{i_1}$ 到 $a_{i_k}$ 中有一个数 $2^x$ 位上是 $0$ ，是没有意义的 . 

所以，选中的 $k$ 个数必须 $2^x$ 上为 $1$ . 那么，对于当前的 $k$ 能被消完，则必定是 $cnt(x)\equiv 0\pmod k$ .

所以，当前的 $k$ 必定对于所有的 $x=0$ 到 $29$ 都满足 $cnt(x)\equiv 0\pmod k$ .

此时 $k$ 必须是 $cnt(0)$ 到 $cnt(29)$ 的 $\gcd$ 的因数 .

还需要判断一种特殊情况，当 $cnt(0)$ 到 $cnt(29)$ 都是 $0$ 的时候，$k=1$ 到 $n$ 是都合法的 .

时间复杂度 : $O(n\log n+\log^2 n)$

空间复杂度 : $O(n)$

```c++
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	char ch=getchar();
	while(ch<'0'||ch>'9')ch=getchar();
	int res=0;
	while(ch>='0'&&ch<='9'){
		res=(res<<3)+(res<<1)+ch-'0';
		ch=getchar();
	}
	return res;
}
inline void print(int res){
	if(res==0){
		putchar('0');
		return;
	}
	int a[10],len=0;
	while(res>0){
		a[len++]=res%10;
		res/=10;
	}
	for(int i=len-1;i>=0;i--)
		putchar(a[i]+'0'); 
}
int t;
int n;
int a[200010];
inline int gcd(int a,int b){
	if(a%b==0)return b;
	return gcd(b,a%b);
}
void solve(){
	n=read();
	for(int i=0;i<n;i++)a[i]=read();
	bool ok=true;
	for(int i=0;i<n;i++)if(a[i])ok=false;
	if(ok){
		for(int i=1;i<=n;i++){
			print(i);
			putchar(' ');
		}
		putchar('\n');
		return;
	}
	int tmp=0;
	for(int k=0;k<30;k++){
		int cnt=0;
		for(int i=0;i<n;i++){
			if(a[i]&(1<<k))cnt++;
		}
		if(cnt==0)continue;
		if(tmp==0)tmp=cnt;
		else tmp=gcd(tmp,cnt);
	}	
	for(int i=1;i<=tmp;i++)if(tmp%i==0){
		print(i);
		putchar(' ');
	}
	putchar('\n');
}
int main(){
	t=read();
	while(t--){
		solve();
	}
	return 0;
}
/*inline? ll or int? size? min max?*/
```

写在最后，也可以来我的cnblog看一看哦
[link](https://www.cnblogs.com/suadwm/p/15509811.html)

---

