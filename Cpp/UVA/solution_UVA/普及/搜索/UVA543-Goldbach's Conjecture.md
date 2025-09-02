# Goldbach's Conjecture

## 题目描述

哥德巴赫猜想的内容如下：

任意一个大于 $4$ 的偶数都可以拆成两个奇质数之和。

比如：

$
\begin{aligned}
8&=3+5\\
20&=3+17=7+13\\
42&=5+37=11+31=13+29=19+23
\end{aligned}
$

你的任务是：验证小于 $10^6$ 的数满足哥德巴赫猜想。

## 样例 #1

### 输入

```
8
20
42
0```

### 输出

```
8 = 3 + 5
20 = 3 + 17
42 = 5 + 37```

# 题解

## 作者：傅天宇 (赞：7)

首先，我们来介绍一下欧拉筛。

欧拉筛：思想是避免重复筛。因为一个和数可以表示成最大的非自身因数x一个质数，所以我们让每个合数只在枚举到他最大的非自身因数时筛掉，这样就能保证复杂度为O(n）

来看这道题，明显是输出两个相差最大的质数
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
bool pd_prime[1000005];
int ans_prime[100005];
int tot;
void prime(ll x)  //欧拉筛
{
	memset(pd_prime,1,sizeof(pd_prime));//所有数都先定为1 ，如果是合数就为0
	pd_prime[1]=0;//1是合数，为0
	for(int i=2;i<=x;i++)
	{
		if(pd_prime[i]) ans_prime[++tot]=i;
		for(int j=1;j<=tot&&i*ans_prime[j]<=x;j++)
		{
			pd_prime[i*ans_prime[j]]=0;
			if(0==i%ans_prime[j]) break;//说明i不是最大的非自身因数，所以直接break
		}
	}
}
int n;
int main()
{
	prime(1000000);//筛1e6以内的质数
	while(cin>>n&&n!=0)//普通输入
	{
		for(int i=1;ans_prime[i]<=n/2;i++)
		{
			if(pd_prime[ans_prime[i]]==1&&pd_prime[n-ans_prime[i]]==1)//根据题意
			{
				printf("%d = %d + %d\n",n,ans_prime[i],n-ans_prime[i]);
				break;
			}
		}
	}
	return 0;//结束
}
```

---

## 作者：封禁用户 (赞：4)

好久好久没写题解了，今儿来水一发。

### 题意

题目的意思就是说给定一个$n$ ，若有两个奇素数之和等于$n$ ，输出两者（多种情况输出相差最大的一组），如果没有，输出`Goldbach's conjecture is wrong.` 。

### 思路

欧拉筛板子题。

因为$n≤10^6$ ，所以可以先用欧拉筛求出$1\sim 10^6$ 中所有的素数以及判断$i$ 是否为素数的$visit$ 数组。

>$visit_i$ 为false ，则$i$ 为素数，否则是合数。

筛好就暴力找答案。

这里的做法是找一个数$i$ ，若$i$ 是奇素数且$n-i$ 也是奇素数，那就是最终答案。

如果跑了一遍for 循环发现没有满足条件的$i$ ，则无解。

### Code

```cpp
#include<cstdio>
#include<iostream>
using namespace std;
int prime[1000001],n,ans;//prime数组用于记录素数
bool visit[1000001],flag;
int main()
{
	visit[1]=true;//1的情况勿忘
    for(register int i=2; i<=1000000; ++i)
	{
		if(!visit[i])
			prime[++ans]=i;
		for(register int j=1; prime[j]*i<=1000000&&j<=ans; ++j)
		{
			visit[i*prime[j]]=true;
			if(!(i%prime[j]))
				break;
		}
	}//欧拉筛
    while(cin>>n&&n!=0)
    {
        flag=false;
        for(int i=1;i<=n/2+1;++i)//因为n/2+1~n的情况实际就是1~n/2的情况，所以可以直接忽略不计
        {
            if(visit[i]||i%2==0)
                continue;//i不是奇素数
            if(!visit[n-i]&&(n-i)%2==1)//n-i和i都是奇素数
            {
                printf("%d = %d + %d\n",n,i,n-i);//输出结果
                flag=true;//标记
                break;//退出循环
            }
        }
        if(!flag)
            printf("Goldbach's conjecture is wrong.\n");//无解情况
    }
    return 0;
}
```

完结撒花qwq

---

## 作者：青梅轻道卿 (赞：2)

```
//这道题先跑一遍素数筛，把表打好。
//但是这个表是有特别之处的，是以0,1表示是否是素数
//这样的话，时间复杂度可以降低不少
//蒟蒻其实也不知道怎么算时间复杂度

#include<cstdio>
#include<cmath>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<queue>
#define MAXN 1000001
using namespace std;
int data[MAXN],n;
long long v[MAXN];
long long judge[MAXN];
void Eratosthenes(int n)//Eratosthenes素数筛(比线筛慢)
{//Eratosthenes是loglogn效率，线筛无限逼近O(n)
	
    memset(v,0,sizeof(v));
	for(int i=2;i<=n;i++)
	{
		if(v[i]==1) 
		{
			continue;
		}
		judge[i]=1;
		for(int j=1;j<=n/i;j++)
		{
			v[i*j]=1;
		}
	}
	return;
}
inline void get_goldbach(int n)//暴力搜索(其实是顺序查找)
{
	for(int i=3;i<=n;i++)
	{
		if(data[i]&&data[n-i])//都是质数，都是bool变量的1
		{
			printf("%d = %d + %d\n",n,i,n-i);
			return;//直接输出，头也不回
		}
	}
}
int main()
{
	Eratosthenes(1000000);//先跑一遍素数筛，打表
	for(int i=0;i<=1000000;i++)
	{
		if(judge[i]==1)
		{
			data[i]=1;
		}
		else
		{
			data[i]=0;
		}
	}//利用bool数组装载是否是质数
	while(scanf("%d",&n)&&n)
	{
		if(n&1)
		{
			printf("Goldbach's conjecture is wrong.\n");
            //好的，我证明了哥德巴赫猜想的错误2333
		}
		else
		{
			get_goldbach(n);
		}
	}
	return 0;
}
```

---

## 作者：Raw_Aya9285 (赞：1)

我来发题解攒rp了~

其实不用那么麻烦的，就打质数判断，然后搜索一波就完事了。（可能会有点慢但是能AC，90ms+0MB）

首先我们写一个质数判断：

```cpp
bool isprime(int n){
    for(int i=2;i<=int(sqrt(n));i++){  //只用搜到根号n
        if(n%i==0) return false;
    }
    return true;
}
```
这是常规操作，我也不多讲。

然后，我们把重点放在主函数部分：
```cpp
while(cin>>n&&n!=0){
    for(int i=2;i<=n/2;i++){  //只用搜到n/2
        if(isprime(i)&&isprime(n-i)){  //如果i和n-i都是质数
            cout<<n<<" = "<<i<<" + "<<n-i<<endl;  //满足条件，输出，注意格式
            break;  //及时退出循环
        }
    }
}
```
就没了！！！（超简单的）

完整代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,s=0;
bool isprime(int n){
    for(int i=2;i<=int(sqrt(n));i++){
        if(n%i==0) return false;
    }
    return true;
}
int main(){
    while(cin>>n&&n!=0){
        for(int i=2;i<=n/2;i++){
            if(isprime(i)&&isprime(n-i)){
                cout<<n<<" = "<<i<<" + "<<n-i<<endl;
                break;
            }
        }
    }
    return 0;
}
```

祝你们AC~QAQ

---

## 作者：失之_连心 (赞：1)

素数筛法，就是在原暴力求解素数代码的基础上，将算法变成线性的。
那么，怎么操作呢？？！！

代码：
```
#include <bits/stdc++.h>
using namespace std;
int n,w,ans[1000010],tot,s;
bool vis[100000010];
int main(){
    cin>>n>>w;
    for(int i=2;i<=n;i++){   
        if(vis[i]==false) 
           ans[++tot]=i;
        for(int j=1;j<=tot&&i*ans[j]<=n; j++) {
            vis[i*ans[j]]=true;
            if(i%ans[j]==0) 
               break;
        }
    }
    for(int i=1;i<=w;i++){
        cin>>s;
        int left=1,right=tot,mid;
        while(left<=right){ 
            mid=(left+right)/2;
            if(s==ans[mid]){ 
               cout<<"Yes"<<endl; 
               break; 
            }
            else if(s<ans[mid]) 
                right=mid-1;
            else 
                left=mid+1;
        }
        if(s!=ans[mid]) 
           cout<<"No"<<endl;
    }
    return 0;
}
```
这里显然就运用到了筛素数的进一步优化，就是将每一个质数以及它的倍数筛掉，比如说12就可以等于3*4，那么，12就显然不是质数，这样，将所有质数保存在一个数组里，最后只要查找一下就可以了，这真是太棒了！！！
那么，原题的进一步线性优化就是这样的：
```
#include <iostream>
#include <cstdio>
using namespace std;
const int maxn=1000+10,maxm=1000000+10;
int a[maxn],p[maxm],m;
void doing(){
    for(int i=2;i<=750;i++)
        if(!p[i]){
            a[++m]=i;
            for(int j=i*i;j<=maxm;j+=i)
                p[j]=1;
        }
}
int main(){
    int x;
    doing();
    while(1){
        cin>>x;
        if(x==0)
           return 0;
        for(int i=2;i<=x/2;i++)
            if(p[x-i]==0&&p[i]==0){
               cout<<x<<" = "<<i<<" + "<<x-i<<endl;
               break;
            }
    }
    return 0;
}
```
但是，这个程序还不是最优的，因为12既可以等于3*4也可以等于2*6，这样岂不是连续算了多遍？？！！

那么，我们可以在原代码上进行进一步优化，如果能将重复算的部分删掉就好了，其实，是可以这样的，代码如下：

```
#include<bits/stdc++.h> 
using namespace std;
const int maxn=10000000+5; 
int p[maxn],a[maxn]; 
int main(){ 
    int n,m=0,k; 
    cin>>n>>k; 
    for(int i=2;i<=n;i++){ 
        if(!p[i])
           a[m++]=i;  
        for(int j=0;j<m;j++){ 
            if(i*a[j]>n) 
              break; 
            p[i*a[j]]=1; 
            if(i%a[j]==0) //这里是关键，如果能除尽，就说明这个数能被更大的数构成，就直接跳出循环。
              break; 
        } 
    } 
    for(int i=1;i<=k;i++){ 
        int s; 
        cin>>s;
        if(s==1){
           cout<<"No"<<endl;
           continue;
        } 
        if(p[s])
           cout<<"No"<<endl;
        else 
           cout<<"Yes"<<endl;
    } 
    return 0; 
}
```

---

## 作者：mdzzzzzzzzzz (赞：1)

## 1.算素数的方法

因为题目中要求素数而且6<n<1000000

所以这道题用试除法就可以过

以下是试除法的代码

```cpp
int is_prime(int m)//判断m是不是素数
{
	for(int i=2;i<=sqrt(m);i++)//因为m的因数可以表示成若干素数相乘，而且每一个因数i都对应了另一个因数n/i，所以需要找的最大为sqrt(m)
		if(m%i==0)//如果不是质数（质数的因数只有1和它本身）
		return 0;//返回0
	return 1;//是质数返回1
}
```
## 2.找答案的方法

枚举就好了（~~题目过水~~）

## 以下是AC代码

```cpp
#include<bits/stdc++.h>
#define falg flag
using namespace std;
int n;
int is_prime(int m)
{
	for(int i=2;i<=sqrt(m);i++)
		if(m%i==0) return 0;
	return 1;
}
int main()
{
	while(1)
	{
		scanf("%d",&n);
		if(n==0)
		break;
		int vv=0;
		for(int j=2;j<=n/2;j++)//较小的那个数一定不会大于n
		{
			if(is_prime(j)==1&&is_prime(n-j)==1)//判断两个数都是素数就好了
			{
				printf("%d = %d + %d\n",n,j,n-j);//不要多输出空格！
				vv=1;//记录
				break;//因为第一个数要最小，所以找到就可以输出了
			}
		}
		if(vv==0)
		printf("Goldbach's conjecture is wrong.\n");//我怀疑这个没用但还是要加上
	}
	return 0;
}
```

#### 最后强调一点：不要在输出答案的时候多打一个或少打一个空格！！！

## ~~然后还是一样的结尾~~

不要直接抄，代码里面有坑（专门藏的）

# 你已经被警告过了

$\textsf{\color{#8B6914}\small{抄了我代码的你 }\color{white}\scriptsize{\colorbox{#8B6914}{ 作弊者 }}}$

---

## 作者：PHarr (赞：0)

这道题在[#10200. 「一本通 6.2 练习 3」Goldbach's Conjecture](https://loj.ac/problem/10200)也有。

先分析题，验证强哥德巴赫猜想。

首先我们发现要用到素数，而且是多个素数，所以显然要用筛法，因为想巩固一下欧拉筛，所以我直接写的欧拉筛，埃筛应该也可以。

呢么就是暴力枚举小于$\frac{n}{2}$的素数，因为两个素数一定是一个大于$\frac{n}{2}$、一个小于$\frac{n}{2}$，并且我们是从小到大枚举所以第一对符合的素数就是结果。

呢么枚举一个素数后另一个数也就确定了，我们只要判断是不是素数就行。因为已经有了素数表，所以只要在素数二分查找即可，但是我懒，直接用`lower_bound()`就过了。

对于`lower_bound()`我们只要判断二分出来的数是不是我们要找的数，就可以判断有没有这个数。

```cpp
#include <bits/stdc++.h>
using namespace std;


const int N = 1e6+5;
int n = 1e6,num,prime[N],cnt;
bool vis[N],flag;


inline int read()
{
	register int x = 0;
	register char ch = getchar();
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9')
	{
		x = (x<<3) + (x<<1) + ch-'0';
		ch = getchar();
	}
	return x;
}


inline void primes()
{
	for(register int i = 2;i <= n;i ++)
	{
		if(!vis[i]) prime[++cnt] = i;
		for(register int j = 1;j <= cnt &&i*prime[j] <= n;j ++)
		{
			vis[i*prime[j]] = i;
			if(i%prime[j] == 0) break;
		}
	}
}

int main()
{
	primes();
	
	while(1)
	{
		num = read();flag = 0;
		if(num == 0) break;
		for(register int i = 1;prime[i] <= num/2 && i <= cnt;i ++)
		{
			register int j = num - prime[i];
			if(j != *lower_bound(prime,prime+cnt,j)) continue;
			flag = 1;
			printf("%d = %d + %d\n",num,prime[i],j);
			break;
		}
		if(flag) continue;
		puts("Goldbach's conjecture is wrong.");
	}
}
```

---

