# GCD Compression

## 题目描述

Ashish has an array $ a $ of consisting of $ 2n $ positive integers. He wants to compress $ a $ into an array $ b $ of size $ n-1 $ . To do this, he first discards exactly $ 2 $ (any two) elements from $ a $ . He then performs the following operation until there are no elements left in $ a $ :

- Remove any two elements from $ a $ and append their sum to $ b $ .

The compressed array $ b $ has to have a special property. The greatest common divisor ( $ \mathrm{gcd} $ ) of all its elements should be greater than $ 1 $ .

Recall that the $ \mathrm{gcd} $ of an array of positive integers is the biggest integer that is a divisor of all integers in the array.

It can be proven that it is always possible to compress array $ a $ into an array $ b $ of size $ n-1 $ such that $ gcd(b_1, b_2..., b_{n-1}) > 1 $ .

Help Ashish find a way to do so.

## 说明/提示

In the first test case, $ b = \{3+6, 4+5\} = \{9, 9\} $ and $ \mathrm{gcd}(9, 9) = 9 $ .

In the second test case, $ b = \{9+10\} = \{19\} $ and $ \mathrm{gcd}(19) = 19 $ .

In the third test case, $ b = \{1+2, 3+3, 4+5, 90+3\} = \{3, 6,       9, 93\} $ and $ \mathrm{gcd}(3, 6, 9, 93) = 3 $ .

## 样例 #1

### 输入

```
3
3
1 2 3 4 5 6
2
5 7 9 10
5
1 3 3 4 5 90 100 101 2 3```

### 输出

```
3 6
4 5
3 4
1 9
2 3
4 5
6 10```

# 题解

## 作者：liuyi0905 (赞：3)

## 题意：
将 $a$ 数组中先去除两个元素，然后两两求和，另存为 $b$ 数组，要使
$$\gcd\{b_1,b_2,b_3,\dots,b_{n-1}\}\ge2$$
最后输出 $a$ 中要删的两个数的下标。
## 思路：
$b$ 数组的最大公约数先从 $2$ 下手，正整数非奇即偶，要买能被 $2$ 整除，要么不能。所以我们考虑将 $a$ 数组分为奇偶两类。

即：
```cpp
for(int i=1;i<=2*n;i++){
	cin>>a;
	if(a%2)ad[++n1]=i;
	else ev[++n2]=i;
}
```
**注意**：
1. 要放入奇偶数组的是 $a_i$ 的下标 $i$，而不是 $a_i$ 本身。
2. 要读入 $2n$ 个数。

最后只需要按题意输出即可：
```cpp
for(int i=1;i<n1;i+=2)
	if(v<n-1)cout<<ad[i]<<" "<<ad[i+1]<<"\n",v++;
for(int i=1;i<n2;i+=2)
	if(v<n-1)cout<<ev[i]<<" "<<ev[i+1]<<"\n",v++;
```
不要忘记循环次数要减一，防止输出时越界。

___Thank you for watching.___

---

## 作者：rouxQ (赞：2)

## 题意简述
有一个长度为 $2n$ 的数组 $a$。每次从 $a$ 中删除两个数，并把这两个数的和插入到数组 $b$，且保证 $\gcd(b_i)>1$，操作重复 $n-1$ 次。要求给出其中一种合法的操作方法。
## $\operatorname{Solution}$
先考虑这么一句话：$\gcd(b_i)>1$，一般来说 $\gcd$ 越小就越好考虑，所以我们不妨设 $\gcd(b_i)=2$。

也就是说，这时候 $b$ 中的全部元素都是偶数，所以可以知道，每次从 $a$ 中所选的两个数，**要么全是奇数，要么全是偶数**。所以在 $a$ 中所选的 $2n-2$ 个数中，奇数和偶数的**个数**都必须是偶数（有点绕）。

再看条件，因为 $a$ 的大小是偶数，所以其中偶数和奇数的个数，要么是奇、奇；要么是偶，偶。对于第一种情况，我们把奇数和偶数各不计入一个即可；对于第二种情况，我们任选一种不计入两个即可（当然如果一种个数为零就不能选这个了）。
 ## $\operatorname{Code}$
 ```cpp
 #include <bits/stdc++.h>
using namespace std;
vector<int> v1, v2;//v1存偶数的下标，v2存奇数的下标
int main (){
    int T;
    scanf("%d", &T);
    while(T--){
        v1.clear(); v2.clear();
        int n, ch;
        scanf("%d", &n);
        for (int i = 1; i <= 2 * n; i++){
            scanf("%d", &ch);
            if (ch % 2 == 0)v1.push_back(i);
            else v2.push_back(i);
        }
        if (v1.size() % 2 == 1)v1.pop_back(), v2.pop_back();//大小都是奇数
        else if (v1.size() >= 2)v1.pop_back(), v1.pop_back();
        else v2.pop_back(), v2.pop_back();
        for (int i = 0; i < v1.size(); i += 2)
            printf("%d %d\n", v1[i], v1[i + 1]);
        for (int i = 0; i < v2.size(); i += 2)
            printf("%d %d\n", v2[i], v2[i + 1]);
    }
    return 0;
}
 
 ```

---

## 作者：LeavingZzz (赞：2)

# Solution For CF1370B  
本题究极脑筋急转弯QAQ  
（我还是被提醒才知道/wq）  


------------
## $\mathsf{Description}$  
题意为：从一个长度为 $2n$ 的数列 $a$ 中选取两个数字丢掉，然后从接下来的 $2n-2$ 个数字中选择 $n-1$ 对，将每一对的和添加到一个新数列 $b$ 中，需要满足 $\gcd(b_1,b_2,b_3....b_{n-1})>1$，你需要输出你选择的 $n-1$ 对数字的**下标**  



## $\mathsf{Analysis}$
本题看起来很复杂但是本题对最后得到的数列 $b$ 的 $\gcd$ 只是要求大于 $1$。  
解法很简单，我们在读入的时候记录下奇数的下标和偶数的下标，分别存在一起，然后将奇数下标两个一组输出，再将偶数下标两个一组输出即可/cy  
这样最后得到的数列 $b$ 一定有一个公共因子 $2$（奇数加奇数等于偶数，偶数加偶数等于偶数，都是偶数的时候一定有公因子 $2$）  

为啥是对的呢  
首先本题的数列长度是 $2n$，我们设奇数的个数为 $od$，偶数的个数为 $ev$，那么 $ev$ 和 $od$ 只有两种情况：要么两个都是偶数，要么两个都是奇数。  
在两个都是偶数的时候比较简单，直接配对输出，但是略略注意一下本题最开始就要丢弃两个数字，也就是配对只能配对 $n-1$ 次，要注意控制。  
在两个数都是奇数的时候，两两配对最后会多出来一个奇数和一个偶数，刚好丢掉/cy  

所以这种方法能保证答案合法的同时还能保证一定有解。  

$\large\mathsf{Code:}$  
```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
typedef long long LL;
const int maxn=2007;
int ev[maxn],od[maxn],t1,t2;
int T,N;
inline int R()
{
	char c;
	int re;
	while((c=getchar())>'9'||c<'0');
	re=c-48;
	while((c=getchar())>='0'&&c<='9')
	re=re*10+c-48;
	return re;
}
int main()
{
	T=R();
	while(T--)
	{
		memset(ev,0,sizeof(ev));
		memset(od,0,sizeof(od));
		t1=t2=0;
		N=R();int x;
		for(register int i=1;i<=2*N;i++)
		{
			x=R();
			if(x&1) od[++t1]=i;
			else ev[++t2]=i;
		}
		while(t1>1&&N>1)
		{
			printf("%d %d\n",od[t1],od[t1-1]);
			t1-=2;N--;
		}
		while(t2>1&&N>1)
		{
			printf("%d %d\n",ev[t2],ev[t2-1]);
			t2-=2;N--;
		}
	}
	return 0;
}
```
~~萌新上分，越上越昏~~  
$\huge\mathcal{The\text{ }End}$  
谢谢管理大大审核^_^

---

## 作者：liuyongle (赞：0)

#### 思路分析

总是可以形成 $n-1$ 对元素，以使它们的 $\gcd$ 被 $2$ 整除。

我们可以分别将奇数和偶数配对，以使每对数字之和可被 $2$ 整除。注意，总是可以按上述方式形成 $n-1$ 对，因为在最坏的情况下，将从 $a$ 中丢弃一个奇数和一个偶数。如果我们丢弃多个偶数或奇数，则可以改为形成另一对偶数和。

时间复杂度为 $O(n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
 
#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl "\n"
#define int long long

const int N = 2e5 + 5;

int n;
int a[N];

signed main()
{
	IOS;
	int t;
	cin >> t;
	while(t--)
	{
		cin >> n;
		vector< int > even, odd;
		for(int i = 1; i <= 2 * n; i++)
		{
			cin >> a[i];
			if(a[i] % 2)
				odd.push_back(i);
			else
				even.push_back(i);
		}
		vector< pair< int, int > > ans;
		for(int i = 0; i + 1 < odd.size(); i += 2)
			ans.push_back({odd[i], odd[i + 1]});
		for(int i = 0; i + 1 < even.size(); i += 2)
			ans.push_back({even[i], even[i + 1]});
		for(int i = 0; i < n - 1; i++)
			cout << ans[i].first << " " << ans[i].second << endl;
	}
	return 0;
}
```

---

## 作者：_Fontainebleau_ (赞：0)

一道贪心。

珂以使 $gcd$ 为 $2$ 这样，只需要将奇偶分开，奇数存一个数组，偶数存一个数组，到时成对输出即可，要注意，**输出的数据是在数列中的序号**，第一次提交 $WA$ 在这里。

然后就是代码

------------
```cpp
#include<bits/stdc++.h>
#define FOR(i,j,k)  for(int i=(j);i<=(k);i++)
using namespace std;
int t,n;
int a[2001];
int O[2001],E[2001];//Odd存奇数,Even存偶数
int cnt,cnt1,CNT;
int main()
{
	scanf("%d",&t);
	while(t--)//T组
	{
		cnt=0,cnt1=0;
		scanf("%d",&n);
		for(int i=1;i<=2*n;i++)
		{
			scanf("%d",&a[i]);
			if(a[i]%2==1)	O[++cnt]=i;//奇数
			else	E[++cnt1]=i;//偶数
		}
		CNT=0;
		for(int i=1;i<=cnt-1;i+=2)//先成对输出奇数，cnt之所以-1是因为担心cnt为奇数，就会越界
			if(CNT<n-1)	printf("%d %d\n",O[i],O[i+1]),CNT++;//进行n-1次操作所以摆个CNT计数
		for(int i=1;i<=cnt1-1;i+=2)
			if(CNT<n-1)	printf("%d %d\n",E[i],E[i+1]),CNT++;
	}
	return 0;//结束
}

```
$The$ $End.$ ❀


---

## 作者：lingfunny (赞：0)

## 大致题意
有$2n$个数，可以随意从中去掉$2$个数，把剩下的$2(n-1)$个数分成$n-1$组，每组两个数$(a_i,b_i)$，最后要使任意的$(a_i+b_i)$都不互质，即：
$$\gcd(a_1+b_1,a_2+b_2,a_3+b_3,...,a_{n-1}+b_{n-1})>1$$
## 分析
既然要大于$1$，可以考虑最容易凑成的$2$。就是让$a_i+b_i=2k(k\text{为正整数})$。这样一想就简单多了，假设这$2n$个数中有`cnt1`个奇数，`cnt2`个偶数，就可以把每两个奇数混成一组，每两个偶数混成一组。如果`cnt1`能被$2$整除（显然`cnt2`也可以），就可以刚好分出$n$个偶数，最后输出$n-1$组就好了。如果`cnt1`不能被$2$整除，那就同时剔除一个`cnt1`和`cnt2`，最后又可以整除了。

不过这题要求的是输出编号，而且和数本身也没什么关系，所以随便离散一下就好了
## Code
```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
#define min(a,b) (a) < (b) ? (a):(b)
const int maxn = 1005;
int T;
int main(){
	std::cin >> T;
	while(T--){
		int n,A[maxn<<1],X1[maxn<<1],X2[maxn<<1],N1,N2,cnt;
		memset(A,0,sizeof(A));memset(X1,0,sizeof(X1));memset(X2,0,sizeof(X2));
		N1=N2=cnt=0;
		std::cin >> n;
		for(int i=1;i<=n*2;++i)
		std::cin >> A[i];
		for(int i=1;i<=n*2;++i)
		if(A[i]&1)X1[++N1]=i;
		else X2[++N2]=i;
		for(int i=1;i<N1 && cnt!=n-1;i+=2)
		printf("%d %d\n",X1[i],X1[i+1]),++cnt;
		for(int i=1;i<N2 && cnt!=n-1;i+=2)
		printf("%d %d\n",X2[i],X2[i+1]),++cnt;
	}
	return 0;
}
```

---

## 作者：Jay142753869 (赞：0)

打完比赛之后赶紧来发一波题解。  
这题是构造题，那么最好的思路就是使得 $\text{gcd}=2$ ，那么通过小学学的知识可以知道奇数加奇数等于偶数，偶数加偶数等于偶数，那么我们保证数列删去两个数之后有偶数个奇数和偶数个偶数即可。  
 _Code_
 ```cpp
#include<iostream>
#include<cstring>
#include<string>
#include<cstdio>
#include<algorithm>
#include<cstdio>
#define ll long long
using namespace std;
int t,a[100010],n;//不知道为什么1010RE了，开大就A了
bool vis[100010];
int main(){
    scanf("%d",&t);
    while(t--){
    	scanf("%d",&n);
		int odd=0,uodd=0;
		int cnt=0;
    	for(int i=1;i<=2*n;i++){
    		scanf("%d",&a[i]);
    		if(a[i]%2==0)
    			odd++;//偶数
			if(a[i]%2==1)
    			uodd++;//奇数
		}
		if(odd%2==0){//保证有偶数个奇数和偶数个偶数
			int cntt=0;
			for(int i=1;i<=2*n&&cntt<2;i++){
				if(a[i]%2==0&&cntt<2){
					vis[i]=true;
					cntt++;
				}
			}
		}
		else{
			int cnta=0,cntb=0;
			for(int i=1;i<=2*n;i++){
				if(a[i]%2==0&&!cnta){
					vis[i]=true;
					cnta++;
				}
				if(a[i]%2==1&&!cntb){
					vis[i]=true;
					cntb++;
				}
				if(cnta&&cntb)break;
			}
		}
		for(int i=1;cnt<2*n-2;i++){//求解
			if(vis[i])
				continue;
			vis[i]=true;
			for(int j=1;j<=2*n;j++){
				if(!vis[j]&&(a[i]+a[j])%2==0){
					vis[j]=true;
					printf("%d %d\n",i,j);
					cnt+=2;
					break;
				}
			}
		}
		memset(vis,0,sizeof(vis));
	}
    return 0;
}
 ```

---

## 作者：wimg6_ (赞：0)

## CF1370B 题解

> 没有思路怎么办？读题！

于是，我们回到题目，发现这样一句话：$b$ 数组必须满足

$$gcd\{ b_1,b_2,b_3,…,b_{n-1}\}>1$$

即

$$gcd\{ b_1,b_2,b_3,…,b_{n-1}\}\geq2$$

于是我们可以直接从 $2$ 入手，因为自然数非奇即偶，较好考虑。

对于每组数据中的 $a_i$，我们分类存放。

如果 $a_i$ 能被 $2$ 整除，则放入专门存放偶数的数组里；反之，同理。即：

```
       	for(int i=1;i<=2*n;i++)
		{
			int qwq;
           	scanf("%d",&qwq);
           	if(qwq%2==0) p1.push_back(i);
           	else p2.push_back(i);
      	}
```

**细节**：读入 $2 \times n$ 个数。

接着考虑“舍弃 $a$ 中的两个数”这句话。分四种情况讨论。

### 情况一

若 $p1$ 中有偶数个元素，$p2$ 中有奇数个元素，我们可以令 $p1$ 弹出两个元素或 $p2$ 弹出两个元素达到平衡。**但是**，如果 $p1$ 空，则不能弹出 $p1$ 中的元素，反之同理。但是不存在 $p1$ 与 $p2$ 皆空的情况，因为 $n\geq 1$，那么 $a$ 中至少有两个元素。

```
if(p1.size()>=2) p1.pop_back(),p1.pop_back();
else p2.pop_back(),p2.pop_back();
```

### 情况二

若 $p1$ 中有奇数个元素，$p2$ 中有偶数个元素，我们可以令 $p1$ 弹出一个元素，$p2$ 弹出一个元素达到平衡。

```
p1.pop_back(),p2.pop_back();
```


### 情况三

若 $p1$ 中有奇数个元素，$p2$ 中有偶数个元素，则与“总共 $2 \times n$ 个数”相背，故不考虑。

### 情况四

若 $p1$ 中有偶数个元素，$p2$ 中有奇数个元素，则与“总共 $2 \times n$ 个数”相背，故也不考虑。

至此，四种情况全部处理完毕，按照题意输出即可。

**细节**，注意每组数据间要有初始化。

参考程序如下。

```
#include <bits/stdc++.h>
using namespace std;
int t;
int main()
{
	scanf("%d",&t);
   	while(t--)
   	{
       	int n;
   		vector<int> p1,p2;
       	p1.clear(); 
		p2.clear();
       	scanf("%d",&n);
       	for(int i=1;i<=2*n;i++)
		{
			int qwq;
           	scanf("%d",&qwq);
           	if(qwq%2==0) p1.push_back(i);
           	else p2.push_back(i);
      	}
       	if(p1.size()%2==1) p1.pop_back(),p2.pop_back();
       	else 
	   		if(p1.size()>=2) p1.pop_back(),p1.pop_back();
       		else p2.pop_back(),p2.pop_back();
        for(int i=0;i<p1.size();i+=2)
        	printf("%d %d\n",p1[i],p1[i+1]);
        for(int i=0;i<p2.size();i+=2)
        	printf("%d %d\n",p2[i],p2[i+1]);
   	}
   	return 0;
}
```

------------


## The solution of CF1370B

First, we need to go back to the problem, and then we find a sentence: $b$ must array that

$$gcd\{ b_1,b_2,b_3,…,b_{n-1}\}>1$$

so

$$gcd\{ b_1,b_2,b_3,…,b_{n-1}\}\geq2$$

Then we can deal with the special number: $2$.

Why? It is because natural numbers are odd or even.

But how to deposit $a_i$? Don't worry about it! We can deposit it with two classification.

If $a_i$ can mod with $2$, then we can put it in a digit group called $p1$, and we also can put others in $p2$.


```
       	for(int i=1;i<=2*n;i++)
		{
			int qwq;
           	scanf("%d",&qwq);
           	if(qwq%2==0) p1.push_back(i);
           	else p2.push_back(i);
      	}
```

We need to read $2 \times n$ numbers. If we don't care about that, it is wrong.

Then, we need to deal with the problem: Remove any two elements from $a$.

We need to discussed it in four cases. 

### Situation one

If $p1$ has even several elements and $p2$ has odd several elements, we can let two elements in $p1$ pop out. But if $p1$ doesn't have any elements, we can't pop it.On the contrary, the same is true. But we don't have a situation that $p1$ and $p2$ are both empty, because $n\geq 1$, then we have elements that are more than $2$ in $a$.

```
if(p1.size()>=2) p1.pop_back(),p1.pop_back();
else p2.pop_back(),p2.pop_back();
```

### Situation two

If $p1$ has odd several elements and $p2$ has even several elements. we can pop a number from $p1$ and pop another one in $p2$.


```
p1.pop_back(),p2.pop_back();
```


### Situation three

If $p1$ has odd several elements but $p2$ has even several elements, it is go against that: We have $2 \times n$ numbers.

### Situation four

If $p1$ has even several elements but $p2$ has odd several elements, it is go against that: We have $2 \times n$ numbers.

Now we can print it out.

Details: we need to clear the elements is every testlib.

This is the programme.

```
#include <bits/stdc++.h>
using namespace std;
int t;
int main()
{
	scanf("%d",&t);
   	while(t--)
   	{
       	int n;
   		vector<int> p1,p2;
       	p1.clear(); 
		p2.clear();
       	scanf("%d",&n);
       	for(int i=1;i<=2*n;i++)
		{
			int qwq;
           	scanf("%d",&qwq);
           	if(qwq%2==0) p1.push_back(i);
           	else p2.push_back(i);
      	}
       	if(p1.size()%2==1) p1.pop_back(),p2.pop_back();
       	else 
	   		if(p1.size()>=2) p1.pop_back(),p1.pop_back();
       		else p2.pop_back(),p2.pop_back();
        for(int i=0;i<p1.size();i+=2)
        	printf("%d %d\n",p1[i],p1[i+1]);
        for(int i=0;i<p2.size();i+=2)
        	printf("%d %d\n",p2[i],p2[i+1]);
   	}
   	return 0;
}
```


---

