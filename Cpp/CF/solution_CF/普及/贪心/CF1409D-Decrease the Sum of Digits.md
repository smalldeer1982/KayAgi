# Decrease the Sum of Digits

## 题目描述

You are given a positive integer $ n $ . In one move, you can increase $ n $ by one (i.e. make $ n := n + 1 $ ). Your task is to find the minimum number of moves you need to perform in order to make the sum of digits of $ n $ be less than or equal to $ s $ .

You have to answer $ t $ independent test cases.

## 样例 #1

### 输入

```
5
2 1
1 1
500 4
217871987498122 10
100000000000000001 1```

### 输出

```
8
0
500
2128012501878
899999999999999999```

# 题解

## 作者：江户川·萝卜 (赞：8)

### 题意：
给定n,求一个最小的x，使$n+x$的各位数之和小于等于s。
### 解法
加着加着各位数之和变小了，我们就想到了进位。

我们就可以：从低位一位一位往高位进位，直到满足条件为止。

原因:

- 低位进位需要的代价远比高位进位需要的代价小。
- 假设本来高位加一次需要 $10^k$ ，如果从低位往上进位的话，就用了 $<10^k$ 的代价，而且还让各位数之和更少。

应该是很好理解的。

代码：
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
unsigned long long n,ans,r;
int t,s,tot;
int main(){
	scanf("%d",&t);
	for(int i=1;i<=t;i++){
		scanf("%lld%d",&n,&s);
		tot=ans=0;
		r=n;
		while(r){
			tot+=r%10;
			r/=10;
		}//求出n的各位数之和
		if(tot<=s){
			printf("0\n");
			continue;
		}//一开始n的各位数之和就小于等于s
		for(unsigned long long res=1;tot>s&&res<n;res*=10){
			int c=n/res%10;
			if(c==0) continue;
			ans+=(10-c)*res;
			n+=(10-c)*res;
			tot=0;
			r=n;
			while(r){
				tot+=r%10;
				r/=10;
			}//求各位数之和
		}//模拟从低位往高位进位
		printf("%lld\n",ans);
	}
	return 0;
}
```


---

## 作者：三点水一个各 (赞：5)

找到第一个大于 $n$ 且各位数字之和小于等于 $s$ 的数 $k$，输出 $k-n$。

数 $k$ 比 $n$ 大，想要数位之和更小，只能采取进位，即变成形如 $\texttt{XX}\dots\texttt{XX000}\dots\texttt{000}$（$\texttt{X}$ 为任意个位数，其中第一位不为 $0$） 的形式。

设 $n$ 的位数为 $p$。

从高位 $p$ 到低位 $0$，算出将第 $im$ 位进位（因为各数位之和要尽量小，故令比 $im$ 位低的各个数位上的数均为 $0$）时各位数字之和 $cnt$，找到最小的满足 $cnt\le s$ 的 $im$。

将第 $im$ 位进位，算出 $k$，输出 $k-n$。

~~因为蒟蒻的方法太烂~~，要特判 $k=n$ 的情况。并且注意当 $im$ 大于总数位时，意味着只能再开一位使各位之和最小，即 $10^{p+1}$，答案为 $10^{p+1}-n$。

举个例子：

$n=217871987498122,s=10$，求得 $p=15$。

当 $im=15$ 时，$cnt=(2+1)=3\le10$，符合条件，继续判断。

当 $im=14$ 时，$cnt=2+(1+1)=4\le10$，符合条件，继续判断。

当 $im=13$ 时，$cnt=2+1+(7+1)=11>10$，不符合条件。

故求得 $im=14$，$k=220000000000000,k-n=2128012501878$。

$\texttt{Code}$

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll t,d[20]={0,10,100,1000,10000,100000,1000000,10000000,100000000,1000000000,10000000000,100000000000,1000000000000,10000000000000,100000000000000,1000000000000000,10000000000000000,100000000000000000,1000000000000000000}; //在CF评测时用pow莫名WA，请忽略。
int main()
{
	scanf("%lld",&t);
    for(ll kkk=1;kkk<=t;++kkk)
    {
    	ll n,s,sum=0,k,p,im,w,x,y,a[20],cnt=0,ans=0;
		memset(a,0,sizeof(a));
		scanf("%lld%lld",&n,&s);
		k=n;p=0;
		while(k>0) //求位数 p 及每一位上的数字
		{
			a[p++]=k%10;
			sum+=a[p-1];
			k=k/10;
		}
		if(sum<=s) //特判本身就符合，即k=n
		{
			printf("0\n");
			continue;
		}
		p--; im=p;
		while(cnt<s&&im>=0) //求最小的进位位im。
		{
			cnt=0;
			if(a[im]==9) //该位为9，进位特殊
			{
			    w=1;
			    for(int i=im;i<=p;++i)
			    {
			        if(a[im]+w==10) w=1;
			        else 
				    {
				        cnt+=a[im];
						break;
			        }
		        }
		        if(w==1) cnt++;
		    }
		    else //普通进位
		    {
		    	for(int i=p;i>=im;--i)
		    	  cnt+=a[i];
			}
			im--;
		}
		im+=2; a[im]++; //im减过量，稍作处理
		if(im==p+1) //需要再开一位
		{
			printf("%lld\n",d[p+1]-n);
			continue;
		}
		for(ll i=p;i>=im;i--) //普通情况，求得k
		  ans+=a[i]*d[i];
		printf("%lld\n",ans-n);
	}
	return 0;
} 
```

---

## 作者：EternalHeart1314 (赞：4)

### [题目传送门](https://www.luogu.com.cn/problem/CF1409D)

# 思路

把 $n$ 看成一个字符串，从前往后遍历，边遍历边累加。

设当前遍历到第 $i$ 位，前面的和为 $sum$：

如果 $sum>s$，直接退出。

如果 $sum=s$，则：

$\qquad$ 如果 $i$ 后面全是 $0$，继续遍历，否则退出。

然后将 $n$ 一直加到第 $i$ 位进位。

# Code
```
#include<bits/stdc++.h>
#define int long long
using namespace std;

int t, n, k, sum, i;
string s;

signed main() {
	cin >> t;
	while(t --) {
		cin >> s >> k;
		n = sum = 0;
		for(i = 0; s[i]; ++ i) {
			n = (n << 3) + (n << 1) + (s[i] ^ 48);
		}
		for(i = 0; s[i]; ++ i) {
			if(sum + (s[i] ^ 48) > k) {
				-- i;
				break;	//sum > k 
			} else if(sum + (s[i] ^ 48) >= k) {
						//sum == k
				bool flag(false);
				for(int j(i + 1); s[j]; ++ j) {
					if(s[j] ^ 48) {
						flag = true;
						break;
					}
				}		//i 后面全是 0 
				if(flag) {
					-- i;
					break;
				}
			}
			sum += (s[i] ^ 48);
		}
		i = s.size() - i - 1;
		if(i == -1) {
			cout << 0 << '\n';
			continue;
		}
		sum = (n / (int)pow(10, i) + 1) * pow(10, i);
						//将 n 一直加到第 i 位进位。 
		cout << sum - n << '\n';
	}
	return 0;
}
```

### 珍惜生命，远离抄袭

---

## 作者：SSerxhs (赞：3)

显然当且仅当进位时可以减少数码和，而对于 $x0000$ 这种形式必定需要 $x$ 所在位也进位才能相对减少数码和（否则后面几位数码和必定不小于$x$），所以最终得到的数字必定是前 $k$ 位不变、第 $k+1$ 位进一、第 $k+2$ 位及以后都是 $0$ 的数字，直接枚举这个 $k$ 即可。注意最终数字可能超过 long long 的范围，需要开 unsigned long long（但答案并不会超过，依然可以用 lld 输出）

```
#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ll;
ll n,j,ans,k;
int t,s,i;
int c,tot;
inline void read(int &x)
{
	c=getchar();
	while ((c<48)||(c>57)) c=getchar();
	x=c^48;c=getchar();
	while ((c>=48)&&(c<=57))
	{
		x=x*10+(c^48);
		c=getchar();
	}
}
inline void read(ll &x)
{
	c=getchar();
	while ((c<48)||(c>57)) c=getchar();
	x=c^48;c=getchar();
	while ((c>=48)&&(c<=57))
	{
		x=x*10+(c^48);
		c=getchar();
	}
}
int main()
{
	read(t);
	while (t--)
	{
		read(n);read(s);tot=0;
		for (i=j=1;j<=n;i++,j*=10) tot+=n/j%10;
		if (tot<=s) {puts("0");continue;}
		for (i=j=1;j<=n;i++,j*=10)
		{
			tot-=n/j%10-(i==1);
			if (tot<=s)
			{
				j*=10;
				printf("%lld\n",ll((n/j+1)*j-n));
				break;
			}
		}
	}
}

---

## 作者：45dino (赞：3)

一个比较基本的题目。

设原本的数为 $\overline{abcd\dots}$，易知最后的数肯定是 $\overline{abc(d+1)00000\dots}$ 这样的数（表示可能有些不标准）。

所以先特判原数是否满足题意，再枚举 $i$，规定第 $i$ 位以左为原本的数，第 $i$ 位为原本的数加 $1$，第 $i$ 位以右为 $0$。

建议：
- 用数组表示 $n$。

- 手写快速幂，而不是使用 ```pow()```。

---

## 作者：Hu_Tao (赞：2)

# ~~这道题真的不麻烦...~~

事实上,这道题解法很多,这里列举一些:

1.暴力循环(真的能AC!)

2.DFS(代码也不是很难)

3.数位DP(难度较大)

鉴于写题解的这个蒟蒻太弱了,他决定写循环.

主要思路也非常显然:

如果单纯让一个数+1,没进位的话肯定是数字和+1,只有进位了才会减少数字和.

那么具体思路就是->

对于一个数n,我们从最后一位开始,假设现在循环改到第i位.如果n不满足条件,那么就把n的第i位变成0,把i的上一位变成(上一位+1).

注意!!!n是用long long存的!!!所以不用考虑进位之后再进位的情况!!!

比如99999,末尾变0,倒数第二位+1后会产生进位,然后就连锁反应了.不过用longlong存了,直接加上10^(当前位)就行了.

先上代码吧.

```cpp
#include<bits/stdc++.h>

#define all(x) x.begin(),x.end()
#define pb push_back
#define mp make_pair
#define Unique(x) x.erase(unique(all(x)),x.end());

using namespace std;

const int dx[]={-1,0,1,0};
const int dy[]={0,-1,0,1};

const int Days[]={-1,31,28,31,30,31,30,31,31,30,31,30,31};

inline int read()
{
	#define gc getchar
	int ans=0;
	bool f=1;
	char ch=gc();
	
	while(!isdigit(ch))f^=ch=='-',ch=gc();
	
	while(isdigit(ch))ans=((ans<<2)+ans<<1)+(ch^48),ch=gc();
	
	return f?ans:-ans;
	
	#undef gc
}

typedef long long ll;

ll n,digitsum;

ll calcdigitsum(ll x)
{
	ll ret=0,t=x;
	
	while(t)ret+=t%10,t/=10;
	
	return ret;
}

bool ok(ll x){return(calcdigitsum(x)<=digitsum);}

int main(int argc, char const *argv[])
{
	ios::sync_with_stdio(false);
	
	int t;cin>>t;while(t--)
	{
		cin>>n>>digitsum;
		
		ll curdigit=10ll,t=n;
		
		while(!ok(t))
		{
			t+=curdigit-(t%curdigit);
			
			curdigit*=10ll;
			
			//cout<<t<<endl;
		}
		
		cout<<t-n<<endl;
	}
	
	//printf("Time used = %.12f",(double)(clock())/CLOCKS_PER_SEC);
	return 0;
}

/*  GOD BLESS  */

```

相信各位dalao都能看得懂,虽然变量名重复不过问题应该不大(狗头保命)

t表示改动之后的数,curdigit是指当前多少位.比如第10位上的9实际值是9*(1e10),那么这个时候就直接用curdigit就行了.


---

## 作者：InversionShadow (赞：1)

分情况讨论。

+ 如果当前的数码和大于 $s$，显然，答案为 $0$。

+ 如果第一位的数码和大于等于 $s$，即无论后面 $n-1$ 位怎么弄都不行，所以只能进位。

+ 如果第一位的数码和小于 $s$，那我们可以找到第一个和大于 $s$ 的地方，把这个地方之前的位保留（需进位），后面全部为 $0$，这样的答案显然是最小的，算出答案即可。

```cpp
#include <bits/stdc++.h>
#define int unsigned long long

using namespace std;

int t, k, j;
string s;

signed main() {
  cin >> t;
  while (t--) {
    cin >> s >> k;
    int sum = 0;
    j = 0;
    for (int i = 0; i < s.size(); i++) {
      sum += s[i] - '0';
      j = 10 * j + s[i] - '0';
    }
    if (sum <= k) {
      cout << "0\n";
    } else {
      if (s[0] - '0' >= k) {
        int p = 1ull;
        for (int i = s.size() - 1; i >= 1; i--) {
          s[i] = '0';
          p = p * 10ull;
        }
        p = p * 10ull;
        if (s.size() == 1) {
          p = 10;
        }
        cout << p - j << endl;
      } else {
        int p = 0, o = 0;
        while (o < k) {
          o += s[p] - '0';
          p++;
        }
        p -= 2;
        int h = 0;
        for (int i = 0; i < s.size(); i++) {
          if (i == p) {
            s[i]++;
          } else if (i > p) {
            s[i] = '0';
          }
          h = h * 10 + s[i] - '0';
        }
        cout << h - j << endl;
      }
    }
  }
  return 0; 
} 
```

---

## 作者：shaozhehan (赞：1)

[原题链接](https://www.luogu.com.cn/problem/CF1409D)

[CodeForces 链接](https://codeforces.com/problemset/problem/1409/D)

题目大意：

给定两个数 $n$ 和 $s$，求最小的大于等于 $n$ 且数码和小于等于 $s$ 的数，输出 $n$ 与这个数的差。本题有 $t$ 组数据。

思路：

我们可以使用贪心算法。我们用 $S(k)$ 来表示 $k$ 在十进制中的数码和。首先，我们可以发现所有的数 $k$ 都可以表示为 $x\cdot10^y$，我们可以考虑每一次把 $y$ 增大直到 $S(x)\leq s$。

下面考虑如何将 $y$ 增大。我们以 $k=12340000$ 举例：$12340000=1234\cdot10^4$。此时，$\begin{cases}x=1234\\y=4\end{cases}$。我们执行如下操作：$k\leftarrow10^{y+1}(\left\lfloor\dfrac{x}{10}+1\right\rfloor)$，在例子中 $k$ 就变成了 $12400000$，我们就成功地把末尾的 $0$ 多填了一个且新数是比原数大的最小数。

最终，我们可以一直重复上述操作直到 $S(k)\leq s$。最终输出 $k-n$ 就可以了。

坑点：

1. 全程开 ```long long```，否则会炸精度！
1. 执行数的变换操作时，不要忘记最后乘 $10$，也就是 ```return (temp / 10 + 1) * 10 * mul;```！（具体细节见代码）
1. 本题有 $t$ 组数据！
1. 输出答案与 $n$ 的差，不是输出答案！

上代码：
```cpp
#include <iostream>
using namespace std;

inline int calc(const long long &x){// 计算数码和
    long long temp = x;
    int ans = 0;
    while (temp){
        ans += temp % 10;
        temp /= 10;
    }
    return ans;
}

inline long long nxt(const long long &n){// 上文提到的操作
    long long temp = n, mul = 1;// 备份数据、准备累乘器
    while (temp % 10 == 0){
        temp /= 10;// 去掉 temp 后面的 0，同时把 mul 乘上 10
        mul *= 10;
    }
    return (temp / 10 + 1) * 10 /*此时 temp 没有了 0，除以 10 再加上 1 时需要乘以 mul 再乘以 10，以防返回值没有足够的 0*/ * mul;
}

int main(){
    cin.tie(NULL);
    cout.tie(NULL);
    ios::sync_with_stdio(false);// cin、cout 加速
    int t;
    cin >> t;
    while (t--){
        long long n;
        int s;
        cin >> n >> s;
        long long temp = n;// 注意将数据备份
        while (calc(n) > s){// 一直更新直到 S(n)<=s
            n = nxt(n);// 更新
        }
        cout << n - temp << "\n";// 注意输出的是什么
    }
    return 0;
}
```

---

## 作者：Suuon_Kanderu (赞：1)

看到这个题首先可以暴力枚举 $k$,不过复杂度感人。

显然只有在进位时才会减小 $n$，所以我们只要枚举能够使 $n$ 进位的数就 ok 了。

- 枚举时这样枚举，假设 $n = 12345$,我们枚举 $k = 10 - 5 = 5~,~k = 10^2 - 45 = 55 ~,~k = 10^3-345 = 655 ~,~k = 10^4 - 2345 = 7655 ~,~ k = 10^5 - 12345 = 67655$ 。

- 显然，$k$ 单调递增，所以说如果满足条件直接输出。

- 注意特判 $n$ 的数码和已经比 $s$ 小的情况。

- 还有就是使用 `unsigned long long`。因为可能会爆 `long long`。


```
#include<bits/stdc++.h>
typedef unsigned long long ll;
ll digit(ll k) {// 获得一个数的数码
	ll cnt = 0;
	while(k)cnt += k % 10 ,k  /= 10;
	return cnt;
}
ll work(ll n , ll s) {
	if(digit(n) <= s)return 0;
	ll k = 1 , cnt = 0 , t = n;
	
	while(t)cnt++ , t /= 10;
	for(ll i = 1; i <= cnt; i++) {
		k *= 10;
		if(digit(k - n % k + n) <= s)
			return k - n%k;
	}
}
int main() {
	int t = 0;
	scanf("%d" , &t);
	while(t--) {
		ll n , s;
		std::cin >> n >> s;
		std::cout << work(n , s) << "\n";
	}
}
```


---

## 作者：LeavingZzz (赞：0)

## $\mathsf{Solution\space For\space CF1409D}$  
### $\mathsf{Description}$
给出两个正整数 $n,s$（$1\le n\le 10^{18};1\le s\le162$）  
求最少进行多少次 `n++` 可以让 $n$ 的数码之和小于等于 $s$。  
### $\mathsf{Solution}$  
可以发现，如果给出 $n$ 的数码之和大于 $s$ 的话，那么之后只有把 $n$ 加到进位的时候才可能出现 $n$ 的数码之和小于等于 $s$ 的情况，例如 $12$ 要小于等于 $2$ 的话，在加到 $20$ 之前其数码和一定是越来越大的  

再举个例子：$42$ 要小于等于 $1$ 的话，你发现加到个位进位到十位的时候仍然不够用，所以要考虑进位到更高位的情况  

这就启发我们枚举将数字 $n$ 的后 $i$ 位全部进到第 $i+1$ 位上时的答案，实际上就相当于将后 $i$ 位的数码全部变成 $0$，而在第 $i+1$ 位上加个 $i$ （通过 $1$ 换多的方式降低数码之和）  

将 $n$ 的后 $i$ 位全部变成 $0$ 并且在第 $i+1$ 位加上 $1$ 的结果为  
$$n-n\bmod10^{i+1}+10^{i+1}$$  
枚举这个 $i$ 并统计每个 $i$ 的答案是否满足条件即可  
从小到大枚举 $i$ ，如果途中发现有满足条件的结果就输出结果结束循环（贪心思想，从小到大枚举 $i$，先出的解一定比后出的更小，差值自然更小）  
### $\mathsf{Code}$
```
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cctype>
using namespace std;
typedef long long LL;
const int maxn=20;
int T;
LL N,s;
int calc(LL x)//统计各位数码之和
{
    int re=0;
    while(x)
    {
        re+=x%10;
        x/=10;
    }
    return re;
}
int main()
{
    #ifndef ONLINE_JUDGE
    freopen("1.in","r",stdin);
    #endif
    scanf("%d",&T);
    LL t;
    while(T--)
    {
        scanf("%lld%lld",&N,&s);
        int sum=calc(N);
        if(sum<=s) puts("0");//不需要任何操作
        else
        {
            for(LL p10=10;p10/10<=N;p10*=10)//枚举i(就是10的若干次幂)
            {
                t=N-N%p10+p10;
                sum=calc(t);
                if(sum<=s) {printf("%lld\n",t-N);break;}//发现答案直接输出并break
            }
        }
    }
    return 0;
}
```  

---

## 作者：minVan (赞：0)

**解题思路**

想到对于 $n\gets n+1$，如果没有进位，数码和一定是 $+1$，所以最后的 $n+k_{\min}$ 一定是 $10$ 的倍数。

所以若 $n=\overline{a_1a_2\cdots a_p}$，则 $n+k_{\min}$ 为 $\overline{a_1a_2\cdots (a_i+1)00\cdots0}$。

于是可以直接枚举 $i$，时间复杂度为 $\mathcal{O}(T|n|)$。

**AC 代码，请勿抄袭**

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int qpow(int a, int b) {
  int ans = 1;
  while(b--) {
    ans *= a;
  }
  return ans;
}
inline int f(string s) {
  int ans = 0;
  for(int i = 0; i < (int)s.size(); i++) {
    ans = ans * 10 + s[i] - '0';
  }
  return ans;
}
inline int solve(int x) {
  int ans = 0;
  while(x) {
    ans += x % 10;
    x /= 10;
  }
  return ans;
}
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  int t;
  cin >> t;
  while(t--) {
    string n;
    int s;
    cin >> n >> s;
    if(solve(f(n)) <= s) {
      cout << 0 << '\n';
      continue;
    }
    int p = 0, q = 0, t = n.size();
    for(int i = 0; i < (int)n.size(); i++) {
      if(p + n[i] - '0' >= s) {
        ++q;
        break;
      }
      --t;
      p += n[i] - '0';
      q = q * 10 + n[i] - '0';
    }
    cout << q * qpow(10, t) - f(n) << '\n';
  }
	return 0;
}
```

---

## 作者：chichichichi (赞：0)

翻了翻机房dalao的提交记录，本来想找另一题的代码，但是看到了这道题~~发现可以水题解~~……

### 关于本题解

因为这道题很简单，本题解主要目的在于贡献一份比较~~平易近人~~的代码。题解区dalao的码风~~奇奇怪怪~~，自认为自己的思路和代码比较好理解。

### 思路

将 $n$ 加上一个数 $k$ ，使得到的数**各位数之和**小于 $s$。

先特判 $n$ 的各位数之和是否小于 $s$ ，若是则输出 $0$.

正如其他题解分析的一样，设 $n$ 的**各位数之和**为 $p$，如果做不进位加法，$n+k$的**各位数之和**必然大于 $p$。



将 $n$ 各位数看做一个序列，如：$n=100$，看做一个长度为 $3$ 的序列 $a$，其中 $a_3=1$。那么做进位加法，我们能保留的是从 $n$ 的最高位开始的一段区间 $T$（长度可为零），$T$区间的**右一位**为原数加 $1$，之后到序列尾都变为 $0$.根据题意，我们应使$T$区间的长度尽量长，这样我们的加数$k$就会尽量小。

假设 $T$ 区间长度为 $t$，$n$的位数为 $h$，最高位为第 $h$ 位，按照题意进行进位加法之后应该有 $h-t-1$个零。那么答案就为 $n\bmod 10^{h-t}- (a[h-t]+1) \times 10^{h-t-1}$

### Before the Code
看文字似乎挺难理解……代码的实现我采用了一种简单粗暴的方式，注释也比较详细，可以作为参考。如果发现本题解有错误或有疑问欢迎评论或私信！

### Enjoy the Code
```cpp
#include<cstdio>
#include<iostream>
using namespace std;
const int maxn=50;
long long n,s,w,k=1,p;
int a[maxn],cnt,sum,f;
int main(){
	int T;
	scanf("%d",&T);
	while(T)//多组数据
	{
		T--;
        //初始化
		cnt=0;
		p=0,sum=0;
		int flag=0;
        
		scanf("%lld%lld",&n,&s);
		w=n;
		while(w)//取出n的每一位
		{
			cnt++;//相当于文中的h
			sum+=w%10;//记录n的各位数之和
			a[cnt]=w%10;
			w/=10;		
		}
		if(sum>s)//需要做进位加法
		flag=1;
		if(flag)
		{
			sum=0;//重复利用很环保
			f=cnt+1;//f相当于文中的h-t
			for(int i=cnt;i>=1;i--)//从最高位开始向后找，因为T区间要从最高位开始
			{
				if(sum+a[i]+1<=s)//使t尽量大，f就尽量小
					f=i;
				sum+=a[i];
			}
			k=a[f]+1;
			for(int i=1;i<f;i++)//结合文字食用
			k*=10;
			for(int i=f;i>=1;i--)//n mod 10^f就是将n的后f位取出来
			p*=10,p+=a[i];
			printf("%lld\n",k-p);
		}
		else
			printf("0\n");
	}
	return 0;
}
```
### See Ya！

---

## 作者：king_xbz (赞：0)

整场CF肝最久的一道，最后因为数组开太大TLE遗憾爆零
## 题目简述
给你1个数n，每次可以给n+1，问最少经过多少次操作使n的各位数字之和小于等于s。
## 思路分析
很轻易的，我们可以想到一个$O(n)$的算法：枚举递增，在第一次各位数之和≤s时退出。然而对于$n≤1e18$的数据，这显然行不通。

那么很显然，这是一道**偏向结论的高精度构造题**。

那么我们该如何得到呢？**进位**。

怎么进呢？我们可以知道，在n每次+1的操作中，对于n的每一位是单调递增%10的，也就是说。**如果当前位是1的情况无法使n各位和为s，那么末尾是2~9的情况同样无法满足条件**。但是，如果往前进一位的话，**各位的和就有可能变小**（当前位变为0，前一位+1）.所以，我们倒着**从第len位到第2位分别变成0，往前进位即可**。

PS：该算法需要通过字符串进行操作，类似于高精.最终答案需要用long long处理
## 代码实现
**读入字符串，并倒着将其各位转化位一个整数**
```cpp
scanf("%s",aa);
int s;
cin>>s;
int len=strlen(aa);
int cnt=0;
for(fint i=len-1;i>=0;i--)
a[++cnt]=aa[i]-'0';
```
**统计当前各位数字之和，累加当前位进位的修改次数，并进行进位。**
```cpp
for(fint i=1;i<=cnt;i++)
{
	int tot=0;
	for(fint j=1;j<=cnt+10;j++)
	tot+=a[j];
	int now=i;
	if(tot>s&&a[now])
	{
		ans+=(10-a[now])*cheng;
		a[now]=0,a[now+1]+=1;
		now+=1;
		while(a[now]==10)
		a[now+1]+=1,a[now]=0,now++;
	}
	if(tot<=s)
	break;//在第一次各位数字和小于等于s时退出
	cheng*=10;
}
```
然后输出ans即可

最后，记得数组别开太大，1e18的数据开20左右足矣，不然就要像我一样爆零两行泪辽！；

祝大家AC愉快

---

## 作者：10circle (赞：0)

#### 题意

给你正整数 $n$ 和 $s$，每一次操作可以将 $n$ 变为 $n+1$，求最小的操作数使 $n$ 的各个数位之和小于等于 $s$。

#### 分析

如果要加一，在不进位的情况下是会使数位和变大的，所以要加就要加到进位。

从低位到高位算，如果数位和小于等于 $s$，那就停止。如果大于 $s$，那就把这一位加到进位。

#### 代码

```cpp
#include<bits/stdc++.h>
#define itn int
#define ll long long
using namespace std;

int read(){
	int a=0,b=1;char c=getchar();
	while(c>'9'||c<'0'){if(c=='-')b=-1;c=getchar();}
	while(c>='0'&&c<='9')a=a*10+c-48,c=getchar();
	return a*b;
}

string c;
int a[30],n,s;
ll p10[30]={1};
ll ans;

int main(){
	for(int i=1;i<=18;i++)p10[i]=p10[i-1]*10;//预处理出10的i次幂
	int t=read();
	while(t--){
		memset(a,0,sizeof(a));//多组数据清空
		cin>>c;
		n=c.size(),s=read(),ans=0;
		for(int i=0;i<n;i++)a[n-i]=c[i]-'0';//字符串转数字，低位在前，高位在后
		n++;//最后可能会增大一位
		for(int i=1;i<=n;i++){//第i-1位到个位都是0
			int sum=0;
			for(int j=i;j<=n;j++)sum+=a[j];
			if(sum<=s)break;//满足条件，停止循环
			//不满足就增加
			ans=ans+(10-a[i])*p10[i-1];//10-a[i]这一位要增加的个数，乘10的i-1次幂是因为这是第i位
			a[i]=0,a[i+1]++;//如果要加上，就一定要加到进一位
			for(int j=i+1;j<=n;j++)a[j]+=a[j-1]/10,a[j-1]%=10;//进位
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：YangXiaopei (赞：0)

## Solution:

一道不难的贪心。

很明显，想要在加的最小的情况下使数字和不大于 $s$，肯定是让最后几位一位位变为 $0$，直到数字和不大于 $s$。

那最后变成的数必然是 $k \times 10 ^ {m}$。其中 $k$ 为原数的一个前缀 $f + 1$。

这个 $1$ 是由进位得来的。

而 $m + f \text{的位数} = \text{原数的位数}$。

也就是说 $10 ^ {m}$ 是在最后进行补 $0$。

我的方法与其他题解较有不同。不是一位一位往前推，而是直接枚举前缀 $f$，算出最后的数再减去原来的数。

而 $f$ 的位数从大到小枚举，这样能保证所增加最少。

注意：`long long` 有炸的风险，而本题没有负数，建议使用 `unsigned long long` 或 `__int128`。

代码变量与本篇题解描述变量和题目给出变量有所出入，请以代码为准。

## Code:

```cpp
#include<bits/stdc++.h>
#define int unsigned long long
using namespace std;
int t, b, sum, tot, a[25], f[25];
string s;
signed main(){
	cin >> t;
	while(t--){
		cin >> s >> b;
		sum = 0;
		memset(a, 0, sizeof(a));
		tot = 0;
		for(int i = 0; i < s.size(); i++){
			a[i + 1] = s[i] - '0';
			tot *= 10;
			tot += a[i + 1];
			sum += a[i + 1];
		}
		if(sum <= b){
			cout << 0 << "\n";
			continue;
		}
		int n = s.size();
		for(int i = n; i >= 0; i--){
			memset(f, 0, sizeof(f));
			int num = 0;
			for(int j = 1; j <= i; j++){
				f[j] = a[j];
				num += f[j];
			}
			f[i]++;
			num++;
			int pos = i;
			while(f[pos] == 10){
				num -= 9;
				f[pos] = 0;
				f[pos - 1]++;
				pos--;
			}
			for(int j = i + 1; j <= n; j++){
				f[j] = 0;
			}
			if(num <= b){
				int ans = 0;
				if(f[0]){
					ans += f[0];
				}
				for(int i = 1; i <= n; i++){
					ans *= 10;
					ans += f[i];
				}
				cout << ans - tot;
				break;
			}
		}
		cout << "\n";
	}
	return 0;
}
```

---

## 作者：Super_Builder (赞：0)

## 思路
因为数据较大，使用字符串读入。

考虑使用贪心。

先统计出当前数码之和。然后从低位往高位枚举，看一下把当前位改了之后是否小于等于 $s$。如果小于的话，则统计出把当前位往后所有位都改为 0，$k$ 为多少，求出的 $k$ 就是最优解。

说明一下为什么要从低位往高位枚举，这样如果成功改好，那么答案一定是最小的。

注意：

- 进位的地方可能有些麻烦，可以根据个人写法改变。

- 注意判断前导 0。

## AC CODE
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
vector<int>ans;
signed main(){
	int T;
	cin>>T;
	while(T--){
		string s;
		long long f=0;
		cin>>s>>f;
		long long sum=0;
		for(int i=0;i<s.size();i++){
			sum+=s[i]-'0';
		}
		if(sum<=f){
			cout<<0<<endl;
			continue;
		}
		for(int i=s.size()-1;i>=0;i--){
			if(s[i]=='0')continue;
			sum-=(s[i]-'0');
			if(sum+1<=f){
				int tmp=9;
				if(s[s.size()-1]!='0')ans.push_back(10-(s[s.size()-1]-'0'));
				else ans.push_back(0),tmp=10;
				for(int j=s.size()-2;j>=i;j--){
					if(s[j]=='0'&&tmp==10)ans.push_back(0),tmp=10;
					else ans.push_back(tmp-(s[j]-'0')),tmp=9;
				}
				break;
			}
		}
		bool ok=1;
		reverse(ans.begin(),ans.end());
		for(auto x:ans){
			if(x==0&&ok)continue;
			cout<<x;
			ok=0;
		}
		cout<<endl;
		ans.clear();
	}
	return 0;
}

```

---

