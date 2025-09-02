# Divided Prime

## 题目描述

给定一个数字$A$，这个$A$由$a_1,a_2,\cdots,a_N$相乘得到。

给定一个数字$B$，这个$B$由$b_1,b_2,\cdots,b_M$相乘得到。

如果$\frac{A}{B}$是一个质数，请输出`YES`，否则输出`NO`。



## 说明/提示

$1 \le N \le 100000$

$0 \le M \le N$

$1 \le a_i,b_i \le 10^{12}$

$1 \le T \le 10$

$\sum N \le 100000$

## 样例 #1

### 输入

```
2
3 2
5 7 7
5 7
4 2
5 7 7 7
5 7```

### 输出

```
YES
NO```

# 题解

## 作者：Iowa_BattleShip (赞：33)

**这是一个不需要$STL$的方法**  
因为每个因子都很大，所以我们不可能直接乘起来再除~~（这不是废话）~~，而题目保证对于一个数字，其在$b_i$中出现的次数不多于在$a_i$中出现的次数，所以我们很容易想到要把$a$中的数用$b$里的约分掉，而众所周知，$a\land a=0$，于是我们就可以考虑利用**异或**来约分，主要细节看代码说吧。  
```cpp
#include<cstdio>
using namespace std;
typedef long long ll;
ll re()//快读
{
	ll x=0;
	char c=getchar();
	bool p=0;
	for(;c<'0'||c>'9';c=getchar())
		p=(c=='-'||p)?1:0;
	for(;c>='0'&&c<='9';c=getchar())
		x=x*10+(c-'0');
	return p?-x:x;
}
bool judge(ll x)//判断是否是质数
{
	int i;
	if(!x||x==1)//特判0和1
		return false;
	for(i=2;1LL*i*i<=x;i++)//朴素根号n试除法判断
		if(!(x%i))
			return false;
	return true;
}
int main()
{
	int i,n,m,t,s;
	ll x,y;
	t=re();
	while(t--)//多组数据
	{
		x=y=s=0;//初始化为0
		n=re();
		m=re();
		for(i=1;i<=n+m;i++)//因为异或的性质，我们可以一次性读完并异或
		{
			y=re();
			if(y!=1)//注意！因为无论有多少个1，都是不影响结果的，所以在异或时要把1排除
			{
				i>n?s--:s++;//显然（除去1后）只有当a里的数比b里的数多一个时才可能是质数，所以我们通过统计来判断
				x^=y;//将所有数异或起来，如果满足上述“多一个”的条件，则异或完所剩下的必是没有被约分的数
			}
		}
		if(s==1&&judge(x))//判断是否满足上述“多一个”的条件，且这个剩余的数是否质数
			printf("YES\n");
		else
			printf("NO\n");
	}
	return 0;
}
```
另外，我用下面这个数据，将一个题解卡掉了  
```cpp
1
5 2
1 1 1 2 3
1 2

正确输出：YES
```

---

## 作者：FlierKing (赞：17)

由于保证了任何一个数字在 $b$ 中的出现次数不大于在 $a$ 中的出现次数。

那么对于每个 $b$ 中的数字，我们只需要将其在 $a$ 中删去即可。

然后考虑如何判断 $a$ 剩下的数字是否为质数。

我们只需要检查每个数字由几个质数组成即可。

在判断质数时，发现当前已经有两个或以上的质数了需要马上退出，否则有可能会造成TLE。

值得一提的是，由 $0$ 个质数组成的数字（即 $1$ ）也不是质数。

复杂度 $O(n\ log\ n + \sqrt a_i )$

```cpp
#include <bits/stdc++.h>
#define ll long long
#define MAXN 100005
using namespace std;
	int T,n,m,cnt;
	ll a[MAXN],b[MAXN];
	bool u[MAXN];
ll inline read()
{
    ll x=0;char ch=getchar();
    while(ch<'0'||ch>'9')ch=getchar();
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x;
}
int check(int x)
{
	for (int i=2,to=sqrt(x);i<=to;i++)
		if (x%i==0) return 2;
	return 1;
}
bool cmp(int x,int y)
{
	return x>y;
}
int main()
{
	T=read();
	while (T--)
	{
		memset(u,0,sizeof(u));
		n=read(),m=read();
		for (int i=1;i<=n;i++)
			a[i]=read();
		sort(a+1,a+n+1,cmp);
		for (int i=1;i<=m;i++)
			b[i]=read();
		sort(b+1,b+m+1,cmp);
		for (int i=1,j=1;i<=m;i++)
		{
			while (b[i]<a[j]) j++;
			u[j]=true;j++;
		}
		cnt=0;
		for (int i=1;i<=n;i++)
			if (!u[i])
			{
				if (a[i]==1) continue;
				cnt+=check(a[i]);
				if (cnt>1) break;
			}
		puts(cnt==1?"YES":"NO");
	}
	return 0;
}
```

---

## 作者：Limerick (赞：6)

#### 写在前面的话:本题写给一个不会sort的z大佬
@ 幽界の冥神

儿歌三百首:找呀找呀找大佬,找到一个z大佬,sort排序都不会,你能AK和捧杯........

闲话少叙,下面开始讲题:

A=a1```*```a2```*```......```*```an

B=b1```*```b2```*```......```*```bn

求:A/B是否是个质数咧？

很明显大家都想到约分(广大蒟蒻就快打破直接算然后判断的美好梦想吧,这很明显是泡影,不然就不会绿了).

重点来了:怎么约分呢？由于一个数字在b中出现的次数不多于在a中出现的次数,所以不难想到把a数组中的数约掉b个即可(前提:a中出现的数b中也有).

显然,当n和m相等或n-m>2时,约分完剩下的数相乘一定是个合数.于是只剩下n-m=1这种情况

那么,首先,** sort排序！！！！！！**(z大佬就因为这个爆零了).之后i从1~n枚举i,找到a数组中约不掉的那个数,拎出来判断一下是否为质数就行了.

Code:

```#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<ctime>
using namespace std;
const int N=100005;
int t,n,m,a[N],b[N];
bool isprime(int x){//朴素质数判断
	if(x==1){
		return false;
	}
    for(int i=2;i*i<=x;i++){
        if(x%i==0){
            return false;
		}
	}
    return true;
}
int main(){
    scanf("%d",&t);
    while(t--){
		memset(a,0,sizeof(a));//注意每次清空
		memset(b,0,sizeof(b));//注意每次清空
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i]);
        }
        for(int i=1;i<=m;i++){
            scanf("%d",&b[i]);
        }
		if(n-m==0||n-m>1){//当n和m相等或n-m>2时,约分完剩下的数相乘一定是个合数,直接输出NO
            printf("NO\n");
            continue;
        }
        sort(a+1,a+1+n),sort(b+1,b+1+m);//排序！！！！！！
        for(int i=1;i<=n;i++){
			if(a[i]!=b[i]){//找到剩下的那个数
				if(isprime(a[i])){//判断是否为质数
                    printf("YES\n");
                }
                else{
                    printf("NO\n");
                }
                break;
			}
		}
    }
    return 0;
}
```
PS:写到朴素质数判断时,我突发奇想,想到一个神奇的算法:
Miller Rabbin质数判断(欧拉筛10的12次方就别想了)
于是,就有了.........
```#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<ctime>
#include<map>
using namespace std;
const int N=100005;
long long t,n,m,a[N],b[N];
map<long long,int> Map;//map比较方便
//Miller Rabbin,这里不再赘述
long long pow_mod(long long a,long long b,long long r){
    long long ans=1,buff=a;
    while(b){
        if(b&1)
            ans=(ans*buff)%r;
        buff=(buff*buff)%r;
        b>>=1;
    }
    return ans;
}
bool test(long long n,long long a,long long d){
    if(n==2){
		return true;
	}
    if(n==a){
		return false;
	}
    if(!(n&1)){
		return false;
	}
    while(!(d&1)){
		d>>=1;
	}
    long long t=pow_mod(a,d,n);
    while(d!=n-1&&t!=n-1&&t!=1){
        t=t*t%n;
        d<<=1;
    }
    return t==n-1||(d&1)==1;
}
bool isprime(long long n){
    int a[]={2,3,5,7};
    for(int i=0;i<=3;i++){
        if(n==a[i]){
			return true;
		}
        if(!test(n,a[i],n-1)){
			return false;
		}
    }
    return true;
}
int main(){
    scanf("%lld",&t);
    while(t--){
		Map.clear();//注意清空
		memset(a,0,sizeof(a));//注意清空
		memset(b,0,sizeof(b));//注意清空
        scanf("%lld%lld",&n,&m);
        for(int i=1;i<=n;i++){
            scanf("%lld",&a[i]);
			Map[a[i]]++;//这个数出现次数++
        }
        for(int i=1;i<=m;i++){
			scanf("%lld",&b[i]);
			Map[b[i]]--;//这个数出现次数--,相当于约分
        }
		if(n-m==0||n-m>1){//当n和m相等或n-m>2时,约分完剩下的数相乘一定是个合数,直接输出NO
            printf("NO\n");
            continue;
        }
        for(int i=1;i<=n;i++){
			if(Map[a[i]]==1){//找到了剩余的那个数
				if(a[i]==2){
					printf("YES\n");
				}
				else if(a[i]%2==0||a[i]<2){
					printf("NO\n");
				}
				else if(isprime(a[i])){
					printf("YES\n");
				}
				else{
					printf("NO\n");
				}
				break;
			}
		}
    }
    return 0;
}
```
#### z大佬万岁！！！

---

## 作者：Trinity (赞：6)

# 题目：P4752 Divided Prime 2018 洛谷7月月赛 T1
## 题目描述
给定一个数字 $A$ , 这个$A$由 $a_1$,$a_2$...$a_N$ 相乘得到。  
给定一个数字 $B$ , 这个$B$由 $b_1$,$b_2$...$b_N$ 相乘得到。  
如果$\frac{A}{B}$是一个质数，请输出 $YES$ , 否则输出 $NO$。  
**保证对于一个数字，其在** $b_i$ **中出现的次数不多于于** $a_i$ **中出现的次数。**  
## 分析
$1$ . 对于数据范围$1≤a_i$,$b_i≤10^{12}$, 很明显不能暴力乘积或用数组储存出现次数，都会超过$long \ long$。( 除非你想高精 , 但会加上复杂度 )  
$2$ . 注意题目 (黑体部分) , 感觉这句话有所玄机， 拿出笔好好模拟一下。  
$3$ . 有了基本思路，要优化，还要尽量避开算出乘积，否则会TLE。  
## 解答
$1$ .仔细推理一波，我们会发现，当 $n$ 等于 $m$时，$a$和 $b$ 数组(在没$1$的情况下 )绝对不可能满足相除为质数，即使当两者完全相同时都只能得到非质非合的 $1$ ; 当 $n$比 $m$大$2$及以上时，即使 $a$，$b$前 $n$项完全相同时（在没$1$的情况下),剩余两个数，乘积明显为合数,即：    
$\ \ \ \ \ \ \ \ \ \ \ \ \ \ \ n=m+1$ 时符合$YES$条件.    
$2$ .我们还需要比较两数组 ，将它们升序排列，设定 $l$ , $r$两数组的指针 ，当$a_l=b_r$时,上下可以消去，继续向后移动指针直到上下不相等，需要寻找新的$a_l$,使重新相等，将$l$指针单独向后移动 ，注意判定范围，不要越到 “TLE领域”（因为那里都是$0$，上下相等，停不下来）,即：  
$\ \ \ \ \ \ \ \ \ \ \ \ \ \ \ if(a_l=a_i)then\ inc(l\ and\ r)$  
$\ \ \ \ \ \ \ \ \ \ \ \ \ \ \ else\ inc(l)\ ...$  
$3$ .如何避免TLE呢，其核心是提前因某些充要条件跳出循环，当我们用 $sum$记录下 $a$ 数组中比 $b $多出数字的乘积，思考发现 ，如果 $sum$ 已经是合数了（或者说是多出了两个以上，这是大多数人的思路 ）就可以跳出循环打出 $NO$，即：
$\ \ \ \ \ \ \ \ \ \ \ \ \ \ \ sum=sum\times a_l$  
$\ \ \ \ \ \ \ \ \ \ \ \ \ \ \ if(sum\ not\ a\ prime\ or\ cnt=2)\ break$  
$4$ .当$r=m $时，最坏的情况是两数组之前完全相同 ，$a$ 数组可能还差最后一项没有判定是否为质数，就需要判定一下，在统计时乘上即可。  
$5$ .如果这一切你都没听懂，我模拟给你看：  
样例中$a={5,7,7,7}$  , $b={5,7}$;  
$5,7,7,    ->7,7->7(left)$  
$5,7\ \ \ \ \ \  ->5\  \ \ ->NO$  
上代码，其中有细节问题：
```cpp
inline bool judge(LL x)//判是否为质数。
{
  if(x==1||x==0)return false;
  if(x==2)return true;
  for(int i=2;i<=sqrt(x);i++)
    if(x%i==0)return false;
  return true;
}
LL t,n,m,l,r,sum,a[N],b[N],flag_1,flag_2;//sum:记下乘积，flag_1:判断是否是解答4的情况。
inline void inti()//多组数据，不要忘记。
{
  memset(a,0,sizeof(a));
  memset(b,0,sizeof(b));
  sum=l=r=1;
  flag_1=flag_2=false;
}
int main()
{
  t=read();
  while(t--)
  {
    inti();
    n=read(),m=read();
    for(int i=1;i<=n;i++)a[i]=read();
    for(int i=1;i<=m;i++)b[i]=read();
    if(n-m>=2||n==m){printf("NO\n");continue;}//解答1的情况（其实我偷懒了，没有判定数组中有1的情况。
    sort(a+1,a+n+1);
    sort(b+1,b+m+1);
    while(true)
    {
      if(l>n)break;
      else if(r>m){flag_1=true;break;}
      if(a[l]==b[r]){l++,r++;continue;}
      else sum*=a[l],l++;//其实这样可以避免数组中有1的情况，cnt记录次数就无法避免，还要写很多代码来判定。
      if(!judge(sum)){flag_2=true;break;}//解答3的情况。
    }
    if(flag_1)sum*=a[n];//循环外别忘了乘上最后一项。
    if(!judge(sum)||flag_2)printf("NO\n");
    else printf("YES\n");//注意，大写，大写，大写，我被坑了。
  }
  return 0;
}
```
## 总结  
$1$ .面对这种大数据，不要头铁，好好优化。  
$2$ .这个题我改了很久，在小细节上吃了不少亏，务必写好特判。  

感谢大观看题解，代码不是很简洁（某利益文同学说的），但是速度还可以，好歹暂时能进第二面，不喜勿喷，谢谢。

---

## 作者：dasxxx (赞：5)

# 洛谷七月月赛 T1 Divided Prime题解
#### 看不懂其他题解各位dalao为什么将本题做得这么复杂。
#### 首先题目里面有一句非常重要的话：

### **保证对于一个数字，其在 $b_i$ 中出现的次数不多于在 $a_i$ 中出现的次数。**

#### 根据这句话，我们可以得出：

#### **1.在a中没有出现的数字b中一定没有出现。**
#### **2.在b中出现的数字a中一定出现。**

#### 看到这里，就能够大概想到解法，因为a中乘积一定整除b中乘积（如上两条）。而如果m-n大于等于2，或者m=n时，剩下的乘积一定不是质数。

#### 所以只需要看a中多出来的数字即可。

#### 而多出来的数字怎么看？

#### 很简单，多出来最多只有一个，那么在b末尾塞一个-100.对两个数组分别排序以后，a中第一个不对应的数字就是那个多出来的数字，最后判断其是否为素数即可！

#### **特别注意！因为1对于乘积没有影响，所以应该过滤掉读入里面所有的1**

### ac程序

```c
#include <bits/stdc++.h>
using namespace std;
int n,m;
int a[100001],b[100001];
bool check(int tar){
	for (int i=2;i<=sqrt(tar);i++)
		if (tar%i==0)
			return false;
	return true;
}
int main(){
	int t;
	scanf("%d",&t);
	while (t--){
		scanf("%d%d",&m,&n);
		for (int i=1;i<=m;i++){
			scanf("%d",a+i);
			if (a[i]==1)
				i--,m--;
		}
		for (int i=1;i<=n;i++){
			scanf("%d",b+i);
			if (b[i]==1)
				i--,n--;
		}
		if (m-n>1||m-n==0){
			printf("NO\n");
			continue;
		}
		sort(a+1,a+1+m);
		sort(b+1,b+1+n);
		b[m]=-100;
		for (int i=1;i<=m;i++)
			if (a[i]!=b[i]){
				printf("%s",(check(a[i])?"YES\n":"NO\n"));
				break;
			}
	}
	return 0;
}
```


---

## 作者：Sai0511 (赞：3)

**此题的感想:**我个人感觉这道题绿的有点假。。不过实际上是大佬们的程序我没看懂。这里想给大家普及一个新的思路。                  
### 算法：            
①：我们知道，如果一个数的**非1因数个数减去第二个数的非一因数个数>1的话，那么这两个数相除就一定不是质数。**因为质数的因数除了1和本身就没有了，所以这是一种重要的条件，如果满足这种条件，就可以直接输出"No",然后退出循环。                 
②：如果不符合条件①的话，那么我们可以开两个数组$a$和$b$,并进行排序，因为**a和b的长度差一**肯定会有一个地方$a$和$b$的数字不同，那么这个时候我们就可以退出循环，并记录这个下标，进行判断此数是否为质数，即可。                         
#### 这样最差情况时间复杂度为$O(N)$,是可以通过此题的。我最慢一个点10ms。
### 话不多说,看代码：          
```cpp
#include<bits/stdc++.h>
#define MAXN 100010//定义最大值
using namespace std;
int n,i,j,x,m,t,t1,t2;
int a[MAXN],b[MAXN];
inline int read(){//快读
    int x=0;char c=getchar();
    while(!isdigit(c)) c=getchar();
    while(isdigit(c)) x=x*10+c-48,c=getchar();
    return x; 
}
inline void write(int x){//快写
    if(x/10>0) write(x/10);
    putchar(x%10+48);
    return;
}
inline void printno(){//输出"NO"
    putchar('N');putchar('O');
    return;
}
inline void printyes(){//输出"YES"
    putchar('Y');putchar('E');putchar('S');return;
}
inline bool ps(int x){//判断质数
    int p=2;
    while(p<=round(sqrt(x))){
        if(x%p==0) return 0;
        p++;
    }
    return 1;
}
int main(){
    t=read();
    for(i=1;i<=t;i++){
        n=read();m=read(); //输入n,m
        memset(a,0,sizeof(a));memset(b,0,sizeof(b));
        //将数组清0
        t1=0;t2=0;  //非一元素个数清0
        for(j=1;j<=n;j++){
            x=read();
            if(x!=1) t1++,a[t1]=x; //如果此数不为1，那么就将其加入数组
        }  
        for(j=1;j<=m;j++){
            x=read();
            if(x!=1) t2++,b[t2]=x;//和输入a数组是一样的原理，这里不再描述
        }
        if(t1-t2!=1){//非一元素个数之差不为1，不可能为质数，直接输出NO,退出循环
            printno();cout<<endl;continue; 
        }
        sort(a+1,a+t1+1);//排序
        sort(b+1,b+t2+1);
        for(j=1;j<=t1;j++){
            if(a[j]!=b[j]) break;//当a数组该元素与b数组该元素不相等时，退出循环
        }
        if(ps(a[j-1])&&a[j-1]!=0){
        //若此数为质数，注意，我使用的判断素数方法0也会误判，所以这里我要加个特判，否则会WA两个点
            printyes();
            cout << endl;
            continue;
        }
        else{
            printno();//输出NO
            cout << endl;
            continue;
        }
    }
} 
```


---

## 作者：hawa130 (赞：3)

数据范围中 $n$ 和 $m$ 都可以到达 $10^5$ 级别，而且单个的数 $a_i$ 和 $b_i$ 达到了 $10^{12}$ 的数量级，显然不能用朴素的方法做（即使自带高精的 Python 也存不下这么多位数吧）

我们发现输入的都是两个~~天文~~数字的因子，显然当一个数拥有除 1 以外的两个及以上的因子时不是质数。

怎么办呢？可以考虑拿 STL 自带的 map 构造映射，用来记录每个因子出现的次数，`map<long long, int> cnt` ，其中 `Key` 是输入的因子，`Value` 是这个因子出现的次数（`map<Key, Value>`）。输入第一个数$A$的时候，我们在统计时加上因子出现的次数，输入第二个数$B$的时候减去因子出现的个数（相当于约分了），这样 map 记录的应该是最终除法计算的结果的因子。

接下来就好办了。只要 map 的大小大于 1，那么说明它一定存在两个或以上的不同因子，一定不是质数，输出 `NO` 即可。
然后如果 map 的大小等于 1 的话，就看这个数出现的次数了，如果出现的次数大于 1，那么它一定也不是质数。
最后如果这个数只出现了一次，说明结果就是这个数，只要用 $O(\sqrt{N})$ 的算法判断这个数是否是质数就可以了。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxN = 1e5 + 3;
int T, n, m;
template<typename Tp> void read(Tp &x) {
	char c = getchar();
	x = 0;
	while (!isdigit(c)) c = getchar();
	do {
		x = (x * 10) + (c ^ 48);
		c = getchar();
	} while (isdigit(c));
}
bool isprime(long long x) {
	long long tmp = sqrt(x);
	for (long long i = 2; i <= tmp; i++)
		if (!(x % i)) return false;
	return true;
}
int main() {
	read(T);
	while (T--) {
		map<long long, int> cnt;
		read(n), read(m);
		for (int i = 1; i <= n; i++) {
			long long num;
			read(num);
			if (num == 1) continue; // 如果是 1 就跳过（1 有没有都一样）
			cnt[num]++;
		}
		for (int i = 1; i <= m; i++) {
			long long num;
			read(num);
			if (num == 1) continue;
			if(!(--cnt[num]))
				cnt.erase(num);
		}
		if (cnt.size() != 1) printf("NO\n");
		else {
			long long num = cnt.begin()->first;
			int sum = cnt.begin()->second;
			if (sum != 1) printf("NO\n");
			else if (isprime(num)) printf("YES\n");
			else printf("NO\n");
		}
	}
}
```

---

## 作者：AgOH (赞：2)

**保证对于一个数字，其在 $b_i$ 中出现的次数不多于在 $a_i$ 中出现的次数。**

这说明 $B$ 里的数 $A$ 里一定有。而且对于某个数据，它在 $B$ 中出现的次数肯定小于等于 $A$ 里的。

于是就有了一个思路：把 $A$ 中在 $B$ 里出现的数据全部删掉。

开两个 `multiset`，然后用 `set_difference` 求一下差集。若差集中非 $1$ 元素数量不等于 $1$，那必然不是质数，否则判断差集中唯一的数字是不是质数即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
bool is_prime(ll x)
{
    if(x==1) return false;
    for(ll i=2;i*i<=x;i++)
        if(x%i==0) return false;
    return true;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin>>t;
    while(t--)
    {
        int n,m;
        cin>>n>>m;
        multiset<ll> s1, s2, s3;
        copy_n(istream_iterator<ll>(cin), n, inserter(s1, s1.begin()));
        copy_n(istream_iterator<ll>(cin), m, inserter(s2, s2.begin()));
        ranges::set_difference(s1, s2, inserter(s3, s3.begin()));
        erase_if(s3, [](ll x) { return x==1; });
        if(s3.size()!=1||!is_prime(*s3.begin())) cout<<"NO"<<'\n';
        else cout<<"YES"<<'\n';
    }
    return 0;
}

```

---

## 作者：仁和_童博扬 (赞：2)

我是一个准初三的蒟蒻……

这次月赛我一开始一直在看T4，第一眼觉得这是个线段树，于是上模板，结果挂了……一直改了一个小时……放弃后去写T1，写到9:00终于A掉了，好开心~~~（我真的太菜了）

简单看了看题解，感觉我的代码相对来说还是比较简单的，因此来水一波。

其实我觉得这个题大概就是半个数学题，想通了就能对，对代码能力的考察不是很强。

我做这个题，一开始想到的是map+gcd再加上异或运算（我也不知道我的脑回路是怎么搞的），结果写了老半天也只能过前15个点……

于是改变思路，留下一个map，对于分母，在map里记录每个乘数的值出现的次数，并在读入分子的乘数时同时检验分母里是否有足够的数去约分，如果足够，map里的值减一，否则就去乘上这个数（分母根本不用存进数组）。

然后，再扫一遍分子的数组，将所有没有被约分的数全部乘起来，并定义一个ans存下约分后的分子除以分母的值，之后判断一下素数就可以啦~\(≧▽≦)/~（P.S.我这里判断素数的方法好像比较快诶，尽管没有必要）

这样下来，粗略地计算整体的时间复杂度约为$ O(tn) $（我没有管那个素数判断的时间复杂度）

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100001], b;
bool check(int num)
{
    if (num == 2 || num == 3 || num == 5)
    	return true;
    if (num % 2 == 0 || num % 3 == 0 || num % 5 == 0 || num == 1)
        return false;
    unsigned int c = 7;
    int maxc = int (sqrt (num));
    while (c <= maxc)
    {
        if (num % c == 0)	return false;
        c += 4;
        if (num % c == 0)	return false;
        c += 2;
        if (num % c == 0)	return false;
        c += 4;
        if (num % c == 0)	return false;
        c += 2;
        if (num % c == 0)	return false;
        c += 4;
        if (num % c == 0)	return false;
        c += 6;
        if (num % c == 0)	return false;
        c += 2;
        if (num % c == 0)	return false;
        c += 6;
    }
    return true;
}
int main()
{
    int t;
    scanf("%d",&t);
    for(int ii = 1; ii <= t; ii++)
    {
        int n, m;
        scanf("%d%d",&n,&m);
        map<int,int> wyj, xhz;
        int o = 1, p = 1;
        for(int i = 1; i <= n; i++)
        {
            scanf("%d",&a[i]);
            wyj[a[i]]++;
        }
        p = 1;
        for(int i = 1; i <= m; i++)
        {
        	
            scanf("%d",&b);
            if(wyj[b])
                wyj[b]--;
            else
            	p *= b;
        }
        for(int i = 1; i <= n; i++)
        	if(wyj[a[i]])
        		o *= a[i], wyj[a[i]]--;
        int ans = o / p;
        if(check(ans))	printf("YES\n");
        else	printf("NO\n");
    }
    return 0;
} 
```

---

## 作者：GK0328 (赞：2)

大质数判定，为什么不用**Miller_Rabin**算法呢？

首先，要使A/B是一个质数，前提条件是A中因子个数严格比B中的多1个（别忘了去除1）。

然后对剩下的那个数Miller_Rabin判定就好了。。。

Pascal Code：

```cpp
const prime:array[1..14]of longint=(2,3,5,7,11,13,17,19,37,43,67,73,97,101);
var
  a,b:array[0..200005]of int64;
  t,i,j,jn,jm,n,m:longint;
  x,s:int64;
procedure qsort1(l,r:longint);
var
  i,j,k:longint;
  t:int64;
begin
  i:=l;
  j:=r;
  k:=(i+j) div 2;
  t:=a[k];
  a[k]:=a[i];
  while i<j do
  begin
    while (i<j) and (a[j]>t) do
      dec(j);
    if i<j then
    begin
      a[i]:=a[j];
      inc(i);
    end;
    while (i<j) and (a[i]<t) do
      inc(i);
    if i<j then
    begin
      a[j]:=a[i];
      dec(j);
    end;
  end;
  a[i]:=t;
  if i-1>l then
    qsort1(l,i-1);
  if i+1<r then
    qsort1(i+1,r);
end;
procedure qsort2(l,r:longint);
var
  i,j,k:longint;
  t:int64;
begin
  i:=l;
  j:=r;
  k:=(i+j) div 2;
  t:=b[k];
  b[k]:=b[i];
  while i<j do
  begin
    while (i<j) and (b[j]>t) do
      dec(j);
    if i<j then
    begin
      b[i]:=b[j];
      inc(i);
    end;
    while (i<j) and (b[i]<t) do
      inc(i);
    if i<j then
    begin
      b[j]:=b[i];
      dec(j);
    end;
  end;
  b[i]:=t;
  if i-1>l then
    qsort2(l,i-1);
  if i+1<r then
    qsort2(i+1,r);
end;
function cf(n,m,p:int64):int64;//大整数乘+mod
var
  ans:int64;
begin
  ans:=0;
  while m<>0 do
  begin
    if m and 1<>0 then
      ans:=(ans+n) mod p;
    m:=m >> 1;
    n:=n << 1 mod p;
  end;
  exit(ans);
end;
function ksm(x,y,p:int64):int64;//快速幂
var
  zc:int64;
begin
  if y=1 then
    exit(x mod p);
  zc:=ksm(x,y div 2,p);
  if odd(y) then
    exit(cf(zc,zc,p) mod p*x mod p) else
    exit(cf(zc,zc,p) mod p);
end;
function Miller_Rabin(n:int64):boolean;//素数判定
var
  i,j,t:longint;
  now,res,u:int64;
begin
  Miller_Rabin:=true;
  if n=1 then
    exit(false);
  for i:=1 to 5 do
  begin
    if prime[i]=n then
      exit(true);
    if n mod prime[i]=0 then
      exit(false);
  end;
  u:=n-1;
  t:=0;
  while u mod 2=0 do
  begin
    u:=u >> 1;
    inc(t);
  end;
  for i:=1 to 5 do
  begin
    now:=ksm(prime[i],u,n);
    for j:=1 to t do
    begin
      res:=cf(now,now,n);
      if (res=1) and (now<>1) and (now<>n-1) then
        exit(false);
      now:=res;
    end;
    if now<>1 then
      exit(false);
  end;
end;
begin
  readln(t);
  for i:=1 to t do
  begin
    readln(jn,jm);
    n:=0;
    m:=0;
    for j:=1 to jn do
    begin
      read(x);
      if x<>1 then//去除1
      begin
        inc(n);
        a[n]:=x;
      end;
    end;
    readln;
    for j:=1 to jm do
    begin
      read(x);
      if x<>1 then//去除1
      begin
        inc(m);
        b[m]:=x;
      end;
    end;
    readln;
    if (n=0) or (n<>m+1) then
      writeln('NO') else
      begin
        qsort1(1,n);
        qsort2(1,m);
        s:=-1;
        for j:=1 to m do
        if a[j]<>b[j] then//找出数
        begin
          s:=a[j];
          break;
        end;
        if s=-1 then
          s:=a[n];
        if Miller_Rabin(s) then
          writeln('YES') else
          writeln('NO');
      end;
  end;
end.
```

---

## 作者：Manjusaka丶梦寒 (赞：2)

只有管理大大的题解，思路好像很奇特，感觉自己的解题思想比较好。
应该不会有bug。

戳这里阅读效果更棒哦：[luogu 7月月赛 #A 解读](https://www.cnblogs.com/rmy020718/p/9311785.html)

## 吐槽两句：

说好的难度从普及-到省选呢？普及-难度呢？最低的只有 普及+提高-的吧，然而我看着都想省选题。

## 体面解读解题分析：

题面简洁易懂，只是根据数据范围，貌似如果相乘的话long long 恐怕都盛不开。

然而细细读题目你会发现，有句很重要的话
(保证对于一个数字，其在 {bi}中出现的次数不多于在 {ai}中出现的数)

既然是A/B，那么 集合A 与 集合B中的元素可以先提前约分啊。

这句话说的数字在 B 中出现次数一定少于 A中的次数，那么这说明B中的数字可以在A中全部约去，那么B=1咯，所以A/B的值不就是A中所剩元素的乘积嘛。

少年，莫着急，等我把话说完。

A中元素的乘积难道就会小？绝对有数据会乘不开。

所以在约分完以后，需要一个比较有意思的判断。

你想A中元素的乘积，既然可以乘出来，那么一定就不是素数(prime).(emmm...说的在理)

还需要加一个判断，如果A中只剩下一个元素后，那么乘积就是这个数了，则需要判断一下这个数是否为素数。

1012大的数，用什么判断呢？

当然是 Miller_Rabin 算法判断了，下面给出了模板。

所以此题就解决完了。

所以代码就比较好写了，上边网址有 Miller_Rabin 板子。
```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>
#include <map>
using  namespace std;
#define N int(1e6+2)
#define M int(2e5+2)
#define ll long long
ll n,m,T;
ll a[N],b,c[N],tot;
map<ll,int> f;
bool vis[N];
ll sum;
ll add_mod(ll a,ll b,ll mod)
{
    ll ans=0;
    while(b)
    {
        if(b&1)
            ans=(ans+a)%mod;
        a=a*2%mod;
        b>>=1;
    }
    return ans;
}

ll pow_mod(ll a,ll n,ll mod)
{
    if(n>1)
    {
        ll tmp=pow_mod(a,n>>1,mod)%mod;
        tmp=add_mod(tmp,tmp,mod);
        if(n&1) tmp=add_mod(tmp,a,mod);
        return tmp;
    }
    return a;
}

bool Miller_Rabbin(ll n,ll a)
{
    ll d=n-1,s=0,i;
    while(!(d&1))
    {
        d>>=1;
        s++;
    }
    ll t=pow_mod(a,d,n);
    if(t==1 || t==-1)
        return 1;
    for(i=0; i<s; i++)
    {
        if(t==n-1)
            return 1;
        t=add_mod(t,t,n);
    }
    return 0;
}
bool is_prime(ll n)
{
    ll i,tab[4]= {3,4,7,11};
    for(i=0; i<4; i++)
    {
        if(n==tab[i])
            return 1;
        if(!n%tab[i])
            return 0;
        if(n>tab[i] && !Miller_Rabbin(n,tab[i]))
            return 0;
    }
    return 1;
}
int main()
{

    scanf("%lld",&T);
    while(T--)
    {
        sum=1;
        ll k=0,p;
        scanf("%lld%lld",&n,&m);
        for(int i=1; i<=n; i++)
        scanf("%lld",&a[i]),f[a[i]]++;;
        for(int i=1; i<=m; i++)scanf("%lld",&b),f[b]--;
        for(int i=1; i<=n; i++)
        {
            if(f[a[i]])k+=f[a[i]],f[a[i]]=0,p=a[i];
        }
        f.clear();
        if(k==1)
        {
            n=p;
            if(n<2) printf("NO\n");
            else if(n==2) printf("YES\n");
            else
            {
                if(!n%2) printf("NO\n");
                else if(is_prime(n))
                    printf("YES\n");
                else printf("NO\n");
            }
        }
        else printf("NO\n");
    }
}
```

---

## 作者：DrownedFish (赞：1)


### 这道题用优先队列既方便又容易理解！


------------

### 优先队列（priority_queue）

其实它就是 _自带排序功能的队列_ 。
```
和队列基本操作相同:
- top   访问队头元素 【不是 front】
- empty 队列为空返回 true ，否则返回 false
- size  返回队列内元素个数
- push  插入元素到队尾 【并排序】
- pop   弹出队头元素

```
网上看到了[这个](https://blog.csdn.net/weixin_36888577/article/details/79937886)介绍优先队列的，感觉很不错。

------------

### 思路

本题的思路楼顶的大佬们讲得十分清楚了，我就来简单总结一下。

很重要的一点： _保证对于一个数字，其在 $b_i$ 中出现的次数不多于在 $a_i$ 中出现的次数。_ 

- 所以对于题目说的 $\dfrac{A}{B}$ ，就是输入的两个数列排序后 **不重合部分之积**。~~还是看大佬们的理解一下吧~~

- 考虑到 $1$ **对乘积不影响**，可以**直接忽略**。

- 要求$\dfrac{A}{B}$是 **质数** ，去除了 $1$ 的干扰后，~~很显然~~输入的两个数列 **包含元素数量差不是 $1$** ，就可以直接输出“NO”。

- 否则判断 **不重合部分**（其实就只有一个数字，下文中我们叫它“特殊元素”）**是否是质数** 即可。

可以自己写两串数字模拟一下~


------------


### 代码：

```C++
#include<bits/stdc++.h>  //方便的 万能头 
#define ll long long     //方便的 宏定义 
using namespace std;     //方便的 命名空间 
priority_queue<ll> a,b;  //方便的 优先队列 
ll t,n,m,c,ans;          //朴素的 变量名 

//朴素的快读 
inline ll read() 
{
	ll x=0;
	char c=getchar();
	bool p=0;
	for(;c< '0'||c> '9';c=getchar()) p=(c=='-'||p)?1:0;
	for(;c>='0'&&c<='9';c=getchar()) x=x*10+(c-'0');
	return p?-x:x;
}
//朴素的质数判断 
inline bool prime(ll x) 
{
	if(x==0) return false;
	if(x==1) return false;
	if(x==2) return true;
	for(int i=2;i*i<=x;i++)
	if(x%i==0) return false;
	return true;
}

int main()
{
	t=read();
	while(t--)
	{
		//初始化 
		ans=-1;  //ans 初始化为 -1 因为下面判断要用 
		while(!a.empty()) a.pop();  //朴素地清空 a 队列
		while(!b.empty()) b.pop();  //朴素地清空 b 队列
		//读入部分 
		n=read();m=read();
		for(int i=1;i<=n;i++){c=read();if(c!=1) a.push(c);}  //读入的 1 不入队列，他是打酱油的 
		for(int i=1;i<=m;i++){c=read();if(c!=1) b.push(c);}  //优先队列的 push 自带排序功能 很方便 
		//判断部分 
		if(a.size()-b.size()!=1){cout<<"NO"<<endl;continue;} //size 返回队列内的元素数量 很方便 
		while(!b.empty())        //只要队列 b 不是空的 
		{
			if(b.top()==a.top()) //找到了重合的元素 
			{b.pop();a.pop();}   //一起弹出，就和普通的队列一样 
			else
		    {ans=a.top();break;} //找到了唯一的特殊元素，退出循环 
		}
		if(ans==-1) ans=a.top(); //特殊元素可能在队列 a 末尾，特判。我就是在这里卡了好几次 92 分www 
		if(prime(ans)) cout<<"YES"<<endl;
		else cout<<"NO"<<endl;
	}
	return 0;
}

```


------------

本蒟蒻写得不怎么好，有错误欢迎指出，希望大家多多包涵~

---

## 作者：绝顶我为峰 (赞：1)

~~这题被评成绿题真心觉得不妥~~

~~也就橙题吧。。。~~

咳咳，言归正传，首先我在月赛的时候看到这题，条件反射是：

### 我不要高精！！！$QWQ$

于是就一本正经的~~胡说八道~~找规律。。。

首先，$A,B$两个数肯定有许许多多能够约掉的因数的；

其次，直接乘起来会妥妥的爆炸$QAQ$；

但是要判断的过程其实写成一个算式是这样的：

$A/B=(a_1*a_2*a_3*...*a_n)/(b_1*b_2*b_3*...*b_m)$

打开括号，得：

$A/B=a_1*a_2*a_3*...*a_n/b_1/b_2/b_3/.../b_m$

现在应该做什么呢？

其实不难发现我们所欠缺的条件就是把数据全部乘起来再做除法会爆炸，如果能让中间数据变小，不就$OK$了？

所以再把式子变形：

$A/B=a_1/b_1*a_2/b_2*a_3/b_3*...*a_n$

漂亮！这样乘除交替，中间的数字就不会过大，可以直接运算。

但是有时$n≠m$，怎么办？

可以再实现程序时空位除以1，不影响结果。

现在可以打代码了，记得数组开大一点！$QWQ$

```cpp
#include<cstdio>
#include<cstring>
#include<cmath>
long long t,n,m,a[1000001],b[1000001];
double s;//A/B的结果
bool prime(long long x)//素数判断机器，不解释
{
    if(x<2)
        return false;
    if(x==2)
        return true;
    double p=sqrt(x)+0.5;
    for(register long long i=2;i<=p;i++)
        if(x%i==0)
            return false;
    return true;
}
int main()
{
    scanf("%d",&t);
    while(t--)
    {
        s=1.0000;//初始化为1，否则会WA
        scanf("%d%d",&n,&m);
        memset(a,0,sizeof(a));//别忘清零
        memset(b,0,sizeof(b));
        for(register long long i=1;i<=n;i++)
            scanf("%d",&a[i]);
        for(register long long i=1;i<=m;i++)
            scanf("%d",&b[i]);
        for(register long long int i=1;i<=n;i++)
            s*=a[i]*1.0/(b[i]==0? 1:b[i]);//乘除法交替求值，如果没有b[i]则除以1
        if(floor(s)!=s)//先判断s是否是整数
        {
            printf("NO\n");
            continue;//执行下一次循环
        }
        if(prime((long long)s))//再判断素数
            printf("YES\n");
        else
            printf("NO\n");
    }
    return 0;
}
```

---

## 作者：ztntonny (赞：0)

## 分析+解法
这题显然不能硬乘出来，于是考虑一种**记录因数**再比较的做法，但是注意这里可以**只用记录是质数的因子**，为什么？因为题目已经给出 $b\subseteq a$（因为每一个出现在 $b$ 中的数的出现次数都小于在 $a$ 中出现的次数，也就是说 $b$ 所有出现的都在 $a$ 里有**对应**，为 $b\subseteq a$），于是实际上 $\complement_ab$ 就**只能是一个质数**。所以如果有合数出现，不是正好约光、就是多出来，但是因为只能多出来质数所以合数就被否定了，可以忽略；下面说一下如何记录质数，首先先要**判定**是不是质数，就可以运用**线性筛质数+二分查找**来完成：

**线性筛质数**：运用**链表**，每一次枚举链表中的 $i$，对于每一个 $i$ 再枚举链表中的每一个 $h$， $i\times h$ 就**是一个合数**，把其从链表中**抹去**，这样能做到真正意义上的线性，因为每一个用 $i$ 枚举出来的合数都是以 $i$ 为**最小因子**的数，于是其实每一个数都会**不重不漏**的被枚举刚好一遍，最后扫一遍链表放到数组里去完成。

```cpp
for ( int i = 0; i < 1000005; i++ )	prime[i].bef = i - 1 , prime[i].aft = i + 1;
for ( int i = 2; prime[i].bef <= 1000000; i = prime[i].aft )
{
	cnt = 0;
	for ( int h = 2; i * h <= 1000000; h = prime[h].aft )	q[++cnt] = i * h;
	for ( int h = 1; h <= cnt; h++ )	aa = prime[q[h]].bef , bb = prime[q[h]].aft , prime[aa].aft = bb , prime[bb].bef = aa;
}
for ( int i = 2; i <= 1000000; i = prime[i].aft )	p[++cmp] = i;
```

**二分查找**：因为质数数组是**严格递增**的，于是可以运用二分查找的性质，以 $\log$ 级别的时间复杂度找到大于这个数的最小数对应数组内的**位置**，然后将这个位置代入数组找到**对应数字**，判断这个数字**是否等于**正在查找的数字，如果是那么这个数字就在数组里面，否则就不在。

```cpp
int fnd( ll x[] , ll y )
{
	if ( x[upper_bound( x , x + 202515 , y ) - x - 1] == y )	return 1;
	return 0;
}
```

下面我们就进入最后一个板块：判断是否**只多出来一个质数**。如何做？我们本应该很简单的运用桶排，但是无奈数据规模过于庞大，我们运用**优先队列**，找到质数都push到队列里去，最后扫一遍两个队列，如果出现了不一样的，也就是 $a$ 中比 $b$ 多出了一个质数，标记并**单独踢掉它**，如果下次又遇到了就直接**结束程序，输出** ```NO``` 。如果到最后**有且仅有一次**遇到不同的，就可以，否则就不可以。

下面是代码实现：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll p[202515] , cmp , q[1000005] , cnt , aa , bb , t;
int fnd( ll x[] , ll y )
{
	if ( x[upper_bound( x , x + 202515 , y ) - x - 1] == y )	return 1;
	return 0;
}
priority_queue<int> p1 , p2;
struct P
{
	int bef , aft;
	bool flag = true;
}prime[1000005];
ll m , n , a[100005] , b[100005];
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL) , cout.tie(NULL);
	for ( int i = 0; i < 1000005; i++ )	prime[i].bef = i - 1 , prime[i].aft = i + 1;
	for ( int i = 2; prime[i].bef <= 1000000; i = prime[i].aft )
	{
		cnt = 0;
		for ( int h = 2; i * h <= 1000000; h = prime[h].aft )	q[++cnt] = i * h;
		for ( int h = 1; h <= cnt; h++ )	aa = prime[q[h]].bef , bb = prime[q[h]].aft , prime[aa].aft = bb , prime[bb].bef = aa;
	}
	for ( int i = 2; i <= 1000000; i = prime[i].aft )	p[++cmp] = i;
	cin >> t;
	while ( t-- )
	{
		cin >> n >> m;
		for ( int i = 1; i <= n; i++ )
		{
			cin >> a[i];
			if ( fnd( p , a[i] ) )	p1.push( a[i] );
		}
		for ( int i = 1; i <= m; i++ )
		{
			cin >> b[i];
			if ( fnd( p , b[i] ) )	p2.push( b[i] );
		}
		bool flag = false , jug = true;
		if ( p1.size() <= p2.size() )	cout << "NO\n";
		else
		{
			while ( !p2.empty() )
			{
				if ( p1.top() != p2.top() && !flag )	flag = true , p1.pop();
				else	if ( p1.top() != p2.top() && flag )
				{
					cout << "NO\n" , flag = false , jug = false;
					break;
				}
				else	p1.pop() , p2.pop();
			}
			if ( flag || p1.size() == 1 && p2.size() == 0 )	cout << "YES\n";
			else	if ( jug )	cout << "NO\n";
		}
		while ( !p1.empty() )	p1.pop();
		while ( !p2.empty() )	p2.pop();
	}
	return 0;
}
```

---

## 作者：infinities (赞：0)

这是一道简单的(数论?)题，大致思路很简单，出题人大佬已经讲得很清楚，这里~~补充一点~~：

- 吐槽数据，本人没有加一些对一的特判都AC了本题，不得不说数据有一点水了（只是一部分特判没加）

先给出含有错误的代码：
```cpp
#include<bits/stdc++.h>//不加别的注释了，只指出错误部分
#define int long long
using namespace std;
bool prime(int a){
    if(a==2||a==3)return 1;if(a%2==0)return 0;
    for(int i=3;i*i<=a;i++)if(a%i==0)return 0;return 1;
}
signed main(){
    int t,a,b,n[101001],m[101001],l,ll,num,ooo;
    cin>>t;
    while(t--){
        l=0,ll=0,num=0,ooo=0;
        cin>>a>>b;
        for(int i=1;i<=a;i++)cin>>n[i];
        for(int i=1;i<=b;i++)cin>>m[i];
        sort(n+1,n+1+a),sort(m+1,m+1+b);
        while(l<=a&&ll<=b){
            if(n[l]>m[ll])ll++;
            if(n[l]<m[ll])l++;
            if(n[l]==m[ll])n[l]=-1,m[ll]=-1,l++,ll++;
        }
        for(int i=1;i<=a;i++){
            if(n[i]>1)ooo=n[i];
        }
        if(a-b>1)cout<<"NO\n";//这行code是有问题的，如果a里剩下的元素有一个质数，其余均为1，那么程序仍然会输出"NO"，而正解是"YES"
        else if(prime(ooo))cout<<"YES\n";
        else cout<<"NO\n";
    }
}
```

正解：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
bool prime(int a){
    if(a==2||a==3)return 1;if(a%2==0)return 0;
    for(int i=3;i*i<=a;i++)if(a%i==0)return 0;return 1;
}//朴素的判断质数
signed main(){
    int t,a,b,n[101001],m[101001],l,ll,num,ooo;
    cin>>t;
    while(t--){
        l=0,ll=0,num=0,ooo=0;
        cin>>a>>b;
        for(int i=1;i<=a;i++)cin>>n[i];
        for(int i=1;i<=b;i++)cin>>m[i];
        sort(n+1,n+1+a),sort(m+1,m+1+b);//排序
        while(l<=a&&ll<=b){
            if(n[l]>m[ll])ll++;
            if(n[l]<m[ll])l++;
            if(n[l]==m[ll])n[l]=-1,m[ll]=-1,l++,ll++;//剔除重复部分
        }
        for(int i=1;i<=a;i++){
            if(n[i]>1)ooo=n[i];//算出最后不是一的的数的值
            if(n[i]==1)a--;//将一剔除
        }
        if(a-b>1)cout<<"NO\n";//如果已经含>1个质数，那么显然要输出"NO"
        else if(prime(ooo))cout<<"YES\n";//符合要求
        else cout<<"NO\n";
    }//exit(0);
}
```

额，最后呢，本蒟蒻发现一些极其特殊的数据能够将两篇代码都卡掉，所以如果有大佬能知道为什么会错，麻烦私信告诉我一下

---

## 作者：昤昽 (赞：0)

# [P4752](https://www.luogu.org/problemnew/show/P4752)
时间复杂度 $O(N+$ $\sqrt{a_x}$)
基本思想:  
- 由题目中"保证对于一个数字，其在 ${b}$中出现的次数不多于在 $a$中出现的次数"可知，$a$和$b$可"约分"
- 若数列 $a$，$b$中都不含有 1 
   - 若 $n == m$ ,则一定有 $\Pi a_i$/$\Pi b_i$ == 1 
   - 若 $n - m \geq 2 $,则$\Pi a_i$ / $\Pi b_i$ $\neq$ 素数
   - 若 $n - m == 1 $,则 $\Pi a_i / \Pi b_i$ 一定只含有一个数,只需判断次数是否为质数  
   
> $ Q:$ 如何得到这个数?  
> $A:xor!  $

因为除了次数外的所有数字都是"两两对应",所以可以通过两遍 $xor$ 将其抵消,无需排序!

```cpp
#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;
const int MAXN=1e5+1;
ll a[MAXN],b[MAXN];
inline ll readll()
{
    ll f=1,x=0;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
    return f*x; 
}
bool is_prime(ll x)
{
    if(x==2)return true;
    if(!(x%2))return false; 
    ll m=sqrt(x+0.5);
    for(ll i=3;i<=m;i+=2)if(!(x%i))return false;
    return true;
}
int main()
{
    int T;scanf("%d",&T);
    while(T--)
    {
        int n,m;
        scanf("%d %d",&n,&m);
        for(int i=0;i<n;i++)a[i]=readll();
        for(int i=0;i<m;i++)b[i]=readll();
        ll x=0,cnt1=0,cnt2=0;
        for(int i=0;i<n;i++){
            x ^= a[i];
            if(a[i]==1)cnt1++;
        }
        for(int i=0;i<m;i++)
        {
            if(b[i]==1)cnt2++;
            x ^= b[i];
        }
        if((n-cnt1)-(m-cnt2)>=2){
            printf("NO\n");
            continue;
        }
        ll cnt=cnt1+cnt2;
        if(cnt%2)x ^= 1;
        if(x==0 || x==1 || !is_prime(x))printf("NO\n");
        else printf("YES\n");
    }
    return 0;
}
```

---

## 作者：henry_y (赞：0)

做法和标程略有不同，所以就来发一发题解

首先要注意到一点，题目中说到

保证对于一个数字，其在 $bi$ 中出现的次数不多于在 $ai$ 中出现的次数。

什么意思呢？就是b数组中出现的数全都是a数组里面有的，而且绝对不会超过在a数组里面出现的次数。

为什么？如果你在b中有一个a中没有出现的数，那么它在b中出现了一次，在a中出现了0次，显然违背了题目描述

看到标程那里不知道的人在问就顺便解答一下qwq

再回想一下素数的定义，只要一个数可以由除了1之外的任意两个数相乘得到，那么它就肯定不是一个素数

基于此，我们可以得到本题的解法，在a数组中把b数组中出现的数删去，同时把所有的1删去（1是对我们的结果没有任何影响的），剩下的数如果数量大于1，那就肯定不是素数，反之，如果数量为1，只要判断一下剩下的那个数是不是素数就可以了

与标程略有不同的是，在a数组中删除掉b数组时，我采用的是二分查找的方式

然后注意二分不要写挂就好了，我这题比赛时wa了9次..
```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll unsigned long long
#define inf 1<<30
#define il inline 
#define in1(a) readl(a)
#define in2(a,b) in1(a),in1(b)
#define in3(a,b,c) in2(a,b),in1(c)
#define in4(a,b,c,d) in2(a,b),in2(c,d)
il int max(int x,int y){return x>y?x:y;}
il int min(int x,int y){return x<y?x:y;}
il int abs(int x){return x>0?x:-x;}
il void swap(int &x,int &y){int t=x;x=y;y=t;}
il void readl(ll &x){
    x=0;ll f=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-f;c=getchar();}
    while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
    x*=f;
}
il void read(int &x){
    x=0;int f=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-f;c=getchar();}
    while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
    x*=f;
}
using namespace std;
/*===================Header Template=====================*/
#define N 100010
ll t,n,m,a[N],f[N][2];
//f数组记录a中每个数出现的次数
//f[i][0]为数的大小，f[i][1]为该数出现次数
bool isprime(ll x){//判断是否素数，是返回1，不是则返回0
    for(ll i=2;i*i<=x;i++){
        if(x%i==0)return 0;
    }return 1;
}
int main(){
    in1(t);
    while(t--){
        in2(n,m);
        for(ll i=1;i<=n;i++)in1(a[i]);
        sort(a+1,a+n+1);ll len=0;//记得排序
        for(ll i=1;i<=n;i++){
            if(a[i]==1)continue;
            if(a[i]!=f[len][0])f[++len][0]=a[i],f[len][1]=1;
            else f[len][1]++;
        }//将a数组存入f数组中，记录每个数出现的次数
        for(int i=1;i<=m;i++){//二分查找b中每个数在a中的位置，并抵消
            ll x;in1(x);
            if(x==1)continue;
            int l=1,r=len;
            while(l<=r){
                ll mid=(l+r)>>1;
                if(f[mid][0]>=x)r=mid-1;
                else if(f[mid][0]<=x)l=mid+1;
                else break;
            }
            f[l][1]--;
        }ll k=0,ans=1;
        for(int i=1;i<=len;i++)if(f[i][1])k+=f[i][1],ans*=f[i][0]*f[i][1];
        if(k==1&&isprime(ans)){puts("YES");continue;}
        //抵消后只剩下一个数且非素数，那么输出YES
        else puts("NO");
        //否则输出NO
    }
    return 0;
}
```

---

## 作者：LakeArcFox (赞：0)

题目中已经很明确了，在b中出现的次数少于在a中出现的次数，所以对于每一个bi，一定能找到和它相等的ai，也就是一定能把a中相同的一个数约掉。

------------
得出这个结论后就好办了。如果n比m大了2或以上，最后在约完后肯定至少留下了2个数，这几个数相乘不可能为质数，如果n等于m，也就是说最后全被约掉了，结果为1，也不是质数。

后来的补充:

要对1进行特殊考虑，具体方法就是把a和b数组中所有的1都拿掉，然后n和m都各自减去被拿掉的1的个数再进行判断。
(然而题目数据没有卡这一点)
可以在读入的时候完成，读取到1的时候就不读入，然后数量-1
具体修改方案
```
for(int i=1;i<=n;i++)
	scanf("%lld",&a[i]);
for(int j=1;j<=m;j++)
	scanf("%lld",&b[j]);
//修改前
//==========================
//修改后
int i=1,j=1;
while(i<=n)
{
	scanf("%lld",&a[i]);
	if(a[i]==1)
	{
		i--;
		n--;
	}
	i++;
} 
while(j<=m)
{
	scanf("%lld",&b[j]);
	if(b[j]==1)
	{
		j--;
		m--;
	}
	j++;
}

```

------------
综上得，只有n=m+1时结果才有可能为质数，只要判断a比b多出了哪一个数，然后判断多出来的这个数是不是质数就可以了。

------------
我的方法是读取a，b数组后对a，b升序排序，然后从第1个位置开始比较，相同则都比较后一个位置，不相同就标记并退出，此时标记的就是a数组中多出来的那个数。
代码实现：
```cpp
sort(a+1,a+n+1,Cmp);
sort(b+1,b+m+1,Cmp);//升序排序
mark=-1;
for(long long int j=1;j<=m;j++)
//我也不知道为什么用了long long
{
	if(a[j]!=b[j])
	{
		mark=j;
		break;
	}
}
if(mark==-1) mark=n;
//特殊情况，刚好a数组最后一个数是多出来的

//这时a[mark]就是多出来的这个数了，判断它是不是质数即可
```
完整代码(本萌新也不知道为什么我全用了long long，代码有欠缺还请dalao指正):
```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>

using namespace std;

long long int t,m,n;
long long int a[100010],b[100010];

bool Cmp(long long int x,long long int y)
{
	return x<y;
}

int prime(long long int x)
{
	if(x==1) return 0;
	long long int k=sqrt(x);
	for(long long int i=2;i<=k;i++)
	{
		if(x%i==0) return 0;
	}
	return 1;
}

int main()
{
	long long int mark;
	scanf("%d",&t);
	while(t--)
	{
		memset(a,0,sizeof(a));
		memset(b,0,sizeof(b));
		scanf("%d%d",&n,&m);
		int i=1,j=1;
		while(i<=n)
		{
			scanf("%lld",&a[i]);
			if(a[i]==1)
			{
				i--;
				n--;
			}
			i++;
		} 
		while(j<=m)
		{
			scanf("%lld",&b[j]);
			if(b[j]==1)
			{
				j--;
				m--;
			}
			j++;
		}
		if(n-m>=2||n==m)
		{
			printf("NO\n");
			continue;
		}
		sort(a+1,a+n+1,Cmp);
		sort(b+1,b+m+1,Cmp);
		mark=-1;
		for(long long int j=1;j<=m;j++)
		{
			if(a[j]!=b[j])
			{
				mark=j;
				break;
			}
		}
		if(mark==-1) mark=n;
		if(prime(a[mark])) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}

```

---

