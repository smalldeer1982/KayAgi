# Windblume Ode

## 题目描述

A bow adorned with nameless flowers that bears the earnest hopes of an equally nameless person.

You have obtained the elegant bow known as the Windblume Ode. Inscribed in the weapon is an array of $ n $ ( $ n \ge 3 $ ) positive distinct integers (i.e. different, no duplicates are allowed).

Find the largest subset (i.e. having the maximum number of elements) of this array such that its sum is a composite number. A positive integer $ x $ is called composite if there exists a positive integer $ y $ such that $ 1 < y < x $ and $ x $ is divisible by $ y $ .

If there are multiple subsets with this largest size with the composite sum, you can output any of them. It can be proven that under the constraints of the problem such a non-empty subset always exists.

## 说明/提示

In the first test case, the subset $ \{a_2, a_1\} $ has a sum of $ 9 $ , which is a composite number. The only subset of size $ 3 $ has a prime sum equal to $ 11 $ . Note that you could also have selected the subset $ \{a_1, a_3\} $ with sum $ 8 + 2 = 10 $ , which is composite as it's divisible by $ 2 $ .

In the second test case, the sum of all elements equals to $ 21 $ , which is a composite number. Here we simply take the whole array as our subset.

## 样例 #1

### 输入

```
4
3
8 1 2
4
6 9 4 2
9
1 2 3 4 5 6 7 8 9
3
200 199 198```

### 输出

```
2
2 1
4
2 1 4 3
9
6 9 1 2 3 4 5 7 8
3
1 2 3```

# 题解

## 作者：Yizhixiaoyun (赞：7)

[本套题所有题解](https://www.luogu.com.cn/blog/yizhixiaoyun/cf1583-ti-xie)

由于笔者水平较弱，所以可能只能一路做到自己做不了的题，不保证能全部写完。

------------

一道弱智题，没删 ```freopen``` 调了好久。

这道题最难的地方在于看出所谓复合数实际上就是**合数**。

于是先把给出的所有数全部加起来，判断是否为合数。如果是，直接输出即可。

如果不是，不难发现大于 $2$ 的偶数均为合数，所以此数一定为奇，那么去掉任意一个奇数就可以了。

实现的时候没有想的这么多，写完之后理了一下，代码可能有点繁琐，仅供参考。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=110;
int T;
int n,a[maxn];
bool flag[maxn];
bool prime(int x){
	for(register int i=2;i*i<=x;++i){
		if(x%i==0) return false;
	}
	return true;
}
int main(){
//	freopen("test.out","w",stdout);
	cin>>T;
	while(T--){
		memset(flag,false,sizeof(flag));
		cin>>n;int ans=0,cnt=0;
		for(register int i=1;i<=n;++i){
			cin>>a[i];ans+=a[i];
		}
		if(prime(ans)==false){
			cout<<n<<endl;
			for(register int i=1;i<=n;++i) cout<<i<<" ";
			cout<<endl;	
			continue;
		}
		for(register int i=1;i<=n;++i){
			if(a[i]%2==1){
				ans-=a[i];flag[i]=true;
				if(prime(ans)==false) break;
			}
		}
		for(register int i=1;i<=n;++i){
			if(flag[i]==false) cnt++;
		}
		cout<<cnt<<endl;
		for(register int i=1;i<=n;++i){
			if(flag[i]==false) cout<<i<<" ";
		}
		cout<<endl;
	}
}
```

---

## 作者：许多 (赞：0)

不得不说，CF 的题确实考验思维。

定义一个正整数 $x$ 叫做复合数仅当存在一个正整数 $y$，使得 $1 < y < x$ 且 $y$ 整除 $x$。也就是 $x$ 有至少 $3$ 个因数。这不就是**合数**吗？

我们发现，除了 $2$ 以外，所有偶数都是合数，而 $n\geq3$，所以如果所有数的和不是合数的话，必定是一个奇数。~~通过小学数学可知~~，此时序列里必定有一个奇数，我们只要吧这个奇数去掉就可以了。

# 代码

```cpp
#include<bits/stdc++.h>
#include<cstdio>
#define N 1000
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();
	return x*f;
}
int T,n,a[N],sum;
bool prime(int x){
	for(int i=2;i*i<=x;i++)
		if(x%i==0) 
			return 0;
	return 1;
}
int main(){
	T=read();
	while(T--){
		n=read();sum=0;
		for(int i=1;i<=n;i++){
			a[i]=read();
			sum+=a[i];
		}
		if(!prime(sum)){
			printf("%d\n",n);
			for(int i=1;i<=n;i++)
				printf("%d ",i);
			printf("\n");
		}
		else {
			int l=1;
			printf("%d\n",n-1);
			for(int i=1;i<=n;i++){
				if(l&&a[i]%2==1)l=0;
				else printf("%d ",i);
			}
			printf("\n");
		}
	}
	return 0;
}
```


---

## 作者：cppcppcpp3 (赞：0)

### **题意：**
给出一个序列，在序列中选尽量多的数，使这些数的和为合数。~~数据保证不会出现最多选 $0$ 个数的情况。~~

### **思路：**
考虑先选所有数，如果此时和为合数，直接输出 $1$ 到 $n$。

如果和不为合数，因为大于 $2$ 的偶数都是合数，所以序列中必有奇数。找出任意一个奇数删去即可。

### **代码：**


```cpp
//CSP rp++

#include<bits/stdc++.h>
#define int long long
int T,n;
int a[105];
bool vis[20005];

void prime(){  //埃氏筛(本题可直接判素数)
	for(int i=2;i<=20001;++i){
		if(vis[i]) continue;
		for(int j=2;j*i<=20001;++j){
			vis[i*j]=1;
		}
	}
} 

inline int read(){
	int x=0,f=1;
	char c=getchar();
	while(!isdigit(c)){
		if(c=='-') f=-1;
		c=getchar();
	}
	while(isdigit(c)){
		x=x*10+c-48;
		c=getchar();
	}
	return x*f;
}


void write1(int n){
	printf("%lld\n",n);
	for(register int i=1;i<=n;++i) printf("%lld ",i);
	puts("");
}

void write2(int n,int p){	
	printf("%lld\n",n-1);
	for(register int i=1;i<=n;++i) if(i!=p) printf("%lld ",i);
	puts("");
} 

main(){
	prime();
	T=read();
	while(T--){
		n=read();
		int sum=0,p=0;
		for(register int i=1;i<=n;++i) a[i]=read(),sum+=a[i];
		
		if(vis[sum]){ //如果和为合数，直接输出
			write1(n);
			continue;
		}
		
		for(register int i=1;i<=n;++i){ //否则删去一个奇数
			if(a[i]&1){
				p=i;
				break;
			}
		}
		write2(n,p);
	} 
	return 0;
}
```

---

## 作者：gdf_yhm (赞：0)

[CF1583A](https://www.luogu.com.cn/problem/CF1583A)

思维题？

### 简要题意
对于一个序列，找出和为合数且元素最多的子集，输出所选子集元素在序列中的下标。“同数量的子集，输出任意一种即可”。

### 思路
求出序列的和 $sum$。

##### 1. $sum$ 为合数
符合条件，直接输出1-n。
##### 2. $sum$ 为素数
$a[i]$ 大于3，所以若 $sum$ 为素数，则 $sum$ 为奇数。所以，$a[i]$ 中必至少有一个奇数。显然，将任意一个奇数不选，选其他 $n-1$ 个数，和为偶数，符合条件。

### code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=100010;
int inline read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0' || ch>'9'){
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(ch>='0' && ch<='9'){
		x=(x<<3)+(x<<1)+(ch^48);
		ch=getchar();
	}
	return x*f;
}

int t;
int n,a[110],flag,sum;

bool check(int x){
	for(int i=2;i*i<=x;i++){
		if(x%i==0)return false;
	}
	return true;
}

signed main(){
	t=read();
	while(t--){
		n=read();sum=flag=0;
		for(int i=1;i<=n;i++){
			a[i]=read();
			if(a[i]&1)flag=i;
			sum+=a[i];
		}
		if(!flag || check(sum)==false){
			printf("%d\n",n);
			for(int i=1;i<=n;i++)printf("%d ",i);
		}
		else{
			printf("%d\n",n-1);
			for(int i=1;i<=n;i++){
				if(i==flag)continue;
				printf("%d ",i);
			}
		}
		printf("\n");
	}
}
```


---

## 作者：zhoujingxuan (赞：0)

 本蒟蒻的第一篇题解，如有不足之处请见谅。

------------
[题目传送门](https://www.luogu.com.cn/problem/CF1583A)

## 1. 题目意思
就是给你一些数，让你用尽可能多的数来组成合数，并输出下标。



## 2. 思路
我们可以先全部加起来，如果结果是偶数的话，则一定是合数（题目说 $ 3 \leq n \leq 100 $ ,且各位数字都不相同，则他们的和不可能为 $ 2 $ ），如果结果为奇数，则需要判断一下是否为合数，如果为质数，我们就需要从中减去一个奇数，将结果变为偶数，那么结果就必定为合数了。

## 3. 程序
那么话不多说，就直接上程序：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,t,a[110],b[110];
bool judge(int x)
{
	for(int i=2;i<=sqrt(x);i++)
	{
		if(x%i==0) return true;
	}
	return false;//判断是否为合数。
}
int main()
{   
    scanf("%d",&t);
    for(int r=1;r<=t;r++)
    {
    	scanf("%d",&n);
    	int sum=0,p=0; 
    	for(int i=1;i<=n;i++) scanf("%d",&a[i]),sum+=a[i];//累加和。
    	if(judge(sum)==true) {
    		printf("%d\n",n);
    		 for(int j=1;j<=n;j++) printf("%d ",j); //如果结果为合数，直接输出下标。
    	}
    	if(judge(sum)==false)//如不是合数。
    	{   
    	    printf("%d\n",n-1);
    		for(int j=1;j<=n;j++) 
			{
			  if(a[j]%2==1&&p==0) p=1;//找到第一个奇数，不输出。
			  else printf("%d ",j); //输出其他数
			}
    	}
    	printf("\n");
    }
	return 0;
} 
```
![](https://cdn.luogu.com.cn/upload/image_hosting/3iu3bgbx.png)
 这就AC了。~~这个题目真的是太逊了。~~
 
  华丽结束

---

## 作者：Jerrlee✅ (赞：0)

## 题意
有 $n$ 个数，选最多的数使其和为合数，输出它们的下标。
## 思路
设 $s$ 等于数组 $a$ 的和，如果 $s$ 是合数，那么 $a$ 就是它自身的最大合数子集。否则，既然 $3 \leq n$，$s$ 必须是大于 $2$ 的素数，意思 $s$ 必须是素数。现在注意，因为 $a$ 的所有元素都是素数，如果我们从 $a$ 中去掉任意一个数，剩下的和必须严格大于 $2$。这就引出了下面的解决方案：如果 $s$ 是质数，从 $a$ 中去掉任何素数都会得到大小为 $n-1$ 的复数子集。这是因为假设 $s$ 是素数，那么 $a$ 中一定存在素数，而且两个素数的差总是偶数。因为我们声称这个差至少是 $4$，新的和总是合数。
## 代码
```cpp
#include<cstdio>
using namespace std;
int t,n,sum,a[105],is_prime[20005];
void init(){
    is_prime[1]=1;
    for(int i=2;i*i<=20000;i++){
        if(!is_prime[i]){
            for(int j=i*i;j<=20000;j+=i) is_prime[j]=1;
        }
    }
} //判素数
int main(){
    init();
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        sum=0;
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i]);
            sum+=a[i]; //算和
        }
        if(is_prime[sum]){
            printf("%d\n",n);
            for(int i=1;i<=n;i++) printf("%d ",i);
        }
        else{
            printf("%d\n",n-1);
            for(int i=1;i<=n;i++){
                if(is_prime[sum-a[i]]){
                    for(int j=1;j<=n;j++)
                        if(i!=j) printf("%d ",j);
                    break;
                }
            }
        }
    }
}
```
[AC记录（洛谷）](https://www.luogu.com.cn/record/60501918)

[AC记录（CF）](https://codeforces.com/contest/1583/submission/132590007)

---

## 作者：_Clown_ (赞：0)

# A.Windblume Ode
这道题目我们可以分类讨论。

首先，如果所有的数的和本身就是合数，

显然答案就是将 $n$ 个全部取走。

反之，如果所有的数的和是质数，

那么这个和显然是一个奇数，

我们从而推得 $a_i(1\le i\le n)$ 中肯定有奇数。

那么我们只要不取某一个奇数，

另外 $n-1$ 个数的和就为合数，

显然是能取到的最优解。

代码就不难写出了。
```cpp
#include<bits/stdc++.h>
#define BetterIO ios::sync_with_stdio(false)
using namespace std;
int N,A[101];
int main(void)
{
	BetterIO;
	register int Case;cin>>Case;while(Case--)
	{
		register int i;cin>>N;
		for(i=1;i<=N;i++)cin>>A[i];
		register int Sum(0);
		for(i=1;i<=N;i++)Sum+=A[i];
		register bool Ret(false);
		for(i=2;i*i<=Sum;i++)if(!(Sum%i))Ret=true;
		if(Ret)
		{
			cout<<N<<endl;
			for(i=1;i<=N;i++)cout<<i<<' ';
			cout<<endl;
		}
		else
		{
			register bool Flag(false);cout<<N-1<<endl;
			for(i=1;i<=N;i++)
			{
				if(A[i]%2&&!Flag)Flag=true;
				else cout<<i<<' ';
			}
			cout<<endl;
		}
	}
	return 0;
}
```

---

## 作者：KSToki (赞：0)

# 题目大意
给定 $n$ 个数，选出尽可能多的数使这些数的和为合数，输出这些数的**下标**。
# 题目分析
首先 $n\geq3$ 且 $a_i$ 互不相同，那么选出的数字之和一旦是偶数一定是合数。于是先选出所有的数字，判定是否为合数，如果是质数那一定是个奇数，删掉选的一个奇数就行了。
# 代码
```cpp
#include<bits/stdc++.h>
#define YPC rubbish 
#define R register
#define I inline
#define ll long long
#define ull unsigned long long
#define LL __int128
#define db double
using namespace std;
#define pb push_back
#define pii pair<int,int>
#define pli pair<ll,int>
#define pll pair<ll,ll>
#define mp(x,y) make_pair(x,y)
#define piii pair<pair<int,int>,int>
#define mp3(x,y,z) make_pair(make_pair(x,y),z)
#define fi first
#define se second
#define putint(x) printf("%d\n",x)
#define putll(x) printf("%lld\n",x)
#define putull(x) printf("%llu\n",x)
#define lowbit(x) ((x)&(-(x)))
#define chkmin(x,y) (x=min(x,y))
#define chkmax(x,y) (x=max(x,y))
#define inv(x) ksm(x,mod-2)
#define inf (1e9)
#define INF (1e18)
#define eps (1e-8)
#define For(i,x,y) for(R int i=x;i<=y;++i)
#define For2(i,x,y,k) for(R int i=x;i<=y;i+=k)
#define Rof(i,x,y) for(R int i=x;i>=y;--i)
#define Rof2(i,x,y,k) for(R int i=x;i>=y;i-=k)
#define ForG(i,edge,x) for(auto i:edge[x])
I int read()
{
	char ch=getchar();
	int res=0,flag=1;
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
			flag=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		res=res*10+ch-'0';
		ch=getchar();
	}
	return res*flag;
}
int T,n,a[101];
int main()
{
	T=read();
	while(T--)
	{
		n=read();
		int sum=0;
		For(i,1,n)
		{
			a[i]=read();
			sum+=a[i];
		}
		bool bj=0;
		for(int i=2;i*i<=sum;++i)
			if(sum%i==0)
			{
				putint(n);
				For(i,1,n)
					printf("%d ",i);
				puts("");
				goto over;
			}
		putint(n-1);
		For(i,1,n)
		{
			if(a[i]%2==1&&!bj)
				bj=1;
			else
				printf("%d ",i);
		}
		puts("");
		over:;
	}
	return 0;
}

```

---

## 作者：tongyanmin (赞：0)

## 题目大意
- 给定一个长度为 $n(3≤n≤100)$ 的正整数数列，且数列中的元素各不相同。找出数列中最长的子序列，使其元素和为**合数**。

- 输出满足题意的最长子序列的长度以及子序列中每个数在原数列中的下标。

## 题目分析
考虑先对整个数列求和，若求得的和 $s$ 为合数，则原数列就是所求的子序列。

若 $s$ 为质数，则 $s$ 必然为**奇数**（由题意，$s≥6$）。又由奇偶性可知，数列中至少存在一个奇数，所以我们只需要去掉一个奇数，就能使得 $s$ 变成一个大于 $2$ 的偶数，满足题意。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
inline bool check(int x){
	for(int i=2;i*i<=x;i++)if(x%i==0)return 1;
	return 0;
}//判断质数 
int main(){
	cin>>t;
	while(t--){
		int n,a[205],s=0,ans[205],pos;
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			s+=a[i];
			if(a[i]&1)pos=i;
		}
		if(s%2==0||((s&1)&&check(s))){//s为合数 
			cout<<n<<endl;
			for(int i=1;i<=n;i++)cout<<i<<" ";//注意题目中要求输出每个数的下标 
		}
		else{//s为质数 
			cout<<n-1<<endl;
			for(int i=1;i<=n;i++)if(i!=pos)cout<<i<<" ";
		}
		cout<<endl;
	}
	return 0;
}
```


---

