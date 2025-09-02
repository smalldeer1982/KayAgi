# Devu, the Dumb Guy

## 题目描述

Devu is a dumb guy, his learning curve is very slow. You are supposed to teach him $ n $ subjects, the $ i^{th} $ subject has $ c_{i} $ chapters. When you teach him, you are supposed to teach all the chapters of a subject continuously.

Let us say that his initial per chapter learning power of a subject is $ x $ hours. In other words he can learn a chapter of a particular subject in $ x $ hours.

Well Devu is not complete dumb, there is a good thing about him too. If you teach him a subject, then time required to teach any chapter of the next subject will require exactly 1 hour less than previously required (see the examples to understand it more clearly). Note that his per chapter learning power can not be less than 1 hour.

You can teach him the $ n $ subjects in any possible order. Find out minimum amount of time (in hours) Devu will take to understand all the subjects and you will be free to do some enjoying task rather than teaching a dumb guy.

Please be careful that answer might not fit in 32 bit data type.

## 说明/提示

Look at the first example. Consider the order of subjects: $ 1 $ , $ 2 $ . When you teach Devu the first subject, it will take him $ 3 $ hours per chapter, so it will take $ 12 $ hours to teach first subject. After teaching first subject, his per chapter learning time will be $ 2 $ hours. Now teaching him second subject will take $ 2×1=2 $ hours. Hence you will need to spend $ 12+2=14 $ hours.

Consider the order of subjects: $ 2 $ , $ 1 $ . When you teach Devu the second subject, then it will take him $ 3 $ hours per chapter, so it will take $ 3×1=3 $ hours to teach the second subject. After teaching the second subject, his per chapter learning time will be $ 2 $ hours. Now teaching him the first subject will take $ 2×4=8 $ hours. Hence you will need to spend $ 11 $ hours.

So overall, minimum of both the cases is $ 11 $ hours.

Look at the third example. The order in this example doesn't matter. When you teach Devu the first subject, it will take him $ 3 $ hours per chapter. When you teach Devu the second subject, it will take him $ 2 $ hours per chapter. When you teach Devu the third subject, it will take him $ 1 $ hours per chapter. In total it takes $ 6 $ hours.

## 样例 #1

### 输入

```
2 3
4 1
```

### 输出

```
11
```

## 样例 #2

### 输入

```
4 2
5 1 2 1
```

### 输出

```
10
```

## 样例 #3

### 输入

```
3 3
1 1 1
```

### 输出

```
6
```

# 题解

## 作者：sanjingshou14 (赞：6)

# 前言
~~抓住暑假的尾巴再来写一篇题解。~~

个人认为本题应评红或橙，算法标签应为贪心。

# 题目翻译
你要教 Devu 学习 $n$ 个章节。第 $i$ 个章节有 $c_{i}$ 节课。当你教了某个章节的其中一节课，你应该教完这个学科的所有章节。Devu 对每节课的初始学习时间为 $X$ 小时。

你每教完他一个章节，那么教下一个章节的任何一节课所需的时间将比以前所需的时间少 $1$ 个小时。（请参阅示例以更清楚地理解它）。他每章的学习时间不能低于 $1$ 小时。

你可以随意地安排教每个章节的顺序。找出 Devu 理解所有科目所需的最短时间。

# 思路
首先考虑贪心。

因为每学完一个章节，学习时间就会减少 $1$ 个小时。所以，只要让节数最多的章节学习时间最少，就可以使总时间最少。注意是每节课的初始学习时间为 $X$ 小时而不是每个章节。

所以只要对每个章节的课的数量进行排序，再进行计算即可。

不要忘记每上完一个章节学习时间就减少 $1$ 小时以及学习时间不能小于 $1$ 小时。

还有，这题我用了 unsigned long long 才过，用了 long long 就 WA 了。

最后只要根据上面的分析来写代码就可以了。

# 代码
如上。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long c[100010];
int main(){
	long long n,x;
	cin>>n>>x;
	for(int i=1;i<=n;i++){
		cin>>c[i];
	}
	sort(c+1,c+n+1);
	unsigned long long s=0;
	for(int i=1;i<=n;i++){
		s=s+c[i]*x;
		if(x>1) x--;
	}
	cout<<s;
	return 0; 
}
```


请勿抄袭，否则棕名！

---

## 作者：丧黑福造 (赞：3)

~~翻译具体看谷歌翻译~~

思路：较基础的**贪心**。将学习课程的章节数从小到大排序，然后依题意模拟即可。

注:要开**long long**

$code$:

```cpp

#include<iostream>
#include<algorithm>
using namespace std;
long long a[100005];
long long n,m,ans;
main(){
    
    cin>>n>>m;
    for(register int i=1;i<=n;i++) cin>>a[i];
    sort(a+1,a+n+1);//排序
    for(register int i=1;i<=n;i++){
        ans+=a[i]*k;//加上时间
        if(k!=1) k--;//每学一门课程就会减少一小时
    }
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：封禁用户 (赞：2)

## CF439B Devu, the Dumb Guy 题解
### 解题思路
此题应使用**贪心**的算法。

由于学习了任意一节课就可以使得后面的所有课时间变短，所以我们可以构造出一个序列，使得每一个数后面的剩余章节最多，即给这个数组排序。

这道题有两个坑，需要注意：

- 一定要开 **long long**，不然最多 $10^{5 \times 3}$ 的数据肯定爆 int。
- 不能一直减小 $x$，$x$ 的下限是 $1$，减至 $1$ 后就不减了。

### 代码：
```
#include<bits/stdc++.h>
using namespace std;
long long cnt = 0 , n , x , c[100005];
int main()
{
	ios::sync_with_stdio(0);
	cin >> n >> x;
	for(int i = 0 ; i < n ; i++)
	{
		cin >> c[i];
	}
	sort(c , c + n);
	for(int i = 0 ; i < n ; i++)
	{
		cnt += c[i] * x;
		if(x > 1)
		{
			x--;
		}
	}
	cout << cnt << endl;
	return 0;
}
```

### 优化：
现在的复杂度是 $O(n \log n)$，主要是由排序引起的。

看到数据范围中的 $c_{1},c_{2},...,c_{n} ( 1 \le c_{i} \le 10^{5} )$，顿时眼前一亮，这数据范围可以用桶排啊！
### 优化代码：
```
#include<bits/stdc++.h>
using namespace std;
long long cnt = 0 , n , x , c[100005] , tong[100005] , ctmp = 0;
int main()
{
	ios::sync_with_stdio(0);
	cin >> n >> x;
	for(int i = 0 ; i < n ; i++)
	{
		cin >> c[i];
	}
	for(int i = 0 ; i < n ; i++)
	{
		tong[c[i]]++;
	}
	for(int i = 0 ; i <= 100000 ; i++)
	{
		while(tong[i]--)
		{
			c[ctmp] = i;
			ctmp++;
		}
	}
	for(int i = 0 ; i < n ; i++)
	{
		cnt += c[i] * x;
		if(x > 1)
		{
			x--;
		}
	}
	cout << cnt << endl;
	return 0;
}
```
### 再次优化：
我们还可以找出 $c_i$ 中的最大值，进一步简化常数项。

还可以把不参与 long long 运算的都丢到 int 中，减少空间的使用。
### 最终代码：
```
#include<bits/stdc++.h>
using namespace std;
int  c[100005] , tong[100005] , ctmp = 0 , maxn = -1 , n;
long long cnt , x;
int main()
{
	ios::sync_with_stdio(0);
	cin >> n >> x;
	for(int i = 0 ; i < n ; i++)
	{
		cin >> c[i];
		maxn = max(maxn , c[i]);
		tong[c[i]]++;
	}
	for(int i = 0 ; i <= maxn ; i++)
	{
		while(tong[i]--)
		{
			c[ctmp] = i;
			ctmp++;
		}
	}
	for(int i = 0 ; i < n ; i++)
	{
		cnt += c[i] * x;
		if(x > 1)
		{
			x--;
		}
	}
	cout << cnt << endl;
	return 0;
}
```
$514\text{B}$ 代码成功拿下（虽然代码长度有亿点点臭）。

---

## 作者：Genshin_ZFYX (赞：2)

[原题传送门](https://www.luogu.com.cn/problem/CF439B)

这题目难度是真离谱。

## 解题思路

我们让课多的用少的时间，课少的用多的时间，就能使学习总时最短。也就是说，让大数乘小数，小数乘大数，而不是让大数乘大数，小数乘小数。

友情提示：**10 年 OI 一场空，不开 long long 见祖宗！**

AC 代码：
```
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define I return
#define love 0
#define FIRESTARS ;
int a[100005];
signed main()
{
    cin.tie(0)->sync_with_stdio(0);
    int n,x,t,sum=0;
	cin>>n>>x;
	t=x;
	for(int i=1;i<=n;i++)
	cin>>a[i];
	sort(a+1,a+1+n);
    for(int i=1;i<=n;i++)
    {
    	sum+=a[i]*t;
    	if(t>1)t--;
	}
	cout<<sum;
	I love FIRESTARS //我爱火星！
}
```

---

## 作者：Lsn0807 (赞：2)

# 题目思路

这题我们可以用贪心来写。由于在教 ``Devu`` 学习时，每教完他 $1$ 个章节，那么教下 $1$ 个章节的任何 $1$ 节课所需的时间将比以前所需的时间少 $1$ 个小时，且他每章的学习时间不能低于 $1$ 小时。所以可以先将每个章节的课程数进行从小到大排序。如果每章的学习时间不低于 $1$ 小时，则下 $1$  章的学习时间可以少 $1$ 个小时。可以看着代码理解。

# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
long long n,x,a[100100],ans;
int main()
{
	cin>>n>>x;
	for (int i=1;i<=n;i++) cin>>a[i];
	sort(a+1,a+n+1);
	for (int i=1;i<=n;i++)
	{
		ans=ans+a[i]*x;
		if (x>1) x--;
	}
	cout<<ans;
	return 0;
}
```
谢谢观看！

---

## 作者：wangqinyan (赞：2)

这题思路与代码实现其实都很简单。

# **题目思路**

这道题其实就是一道很简单的贪心。因为每学完一章时学习下一章所需的时间都会减一，所以我们可以将内容少的章节先学，内容多的章节后学，这样就能使学完所有章节的时间最短。具体可见代码。

# **注意点**

因为每章的学习时间不能低于 $1$ 小时，所以在循环每次做完，时间减一时，要对时间是否还能减一进行判断。

# **代码**
```
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x=0,b=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')b=-1;c=getchar();}
	while(isdigit(c)){x=x*10+c-'0';c=getchar();}
	return x*b;
}
inline void write(int x){
	if(x<0){putchar('-');x=-x;}
	if(x>9)write(x/10);
	putchar(x%10^48);
	return;
}
long long n,x,a[101000],s;
int main()
{
//    freopen(".in","r",stdin);
//    freopen(".out","w",stdout);
	cin>>n>>x;
	for(int i=1;i<=n;i++)cin>>a[i];
	sort(a+1,a+1+n);
	for(int i=1;i<=n;i++)
	{
		s+=a[i]*x;
		if(x>1)x--;
	 }
	 cout<<s;
//    fclose(stdin);
//    fclose(stdout);
	return 0;
}


 
```
感谢观看！

---

## 作者：The_jester_from_Lst (赞：1)

简易贪心题。

我们注意到，每学习一个章节，这个人的学习速度就会加快 $1$。那么为了更快地学完，那些课程多的章节我们自然要往后放，用更高的速度去学。所以我们的贪心策略就是将章节按课程数量从小到大排序，而后顺序遍历，计算时间总和。注意学习速度不能小于 $1$。循环时要特判。

附上代码：
```cpp
#include<bits/stdc++.h>
#define JYAAKIOI 0x8080
#define int long long
#define pii pair<int,int>
#define rg register
#define mk make_pair
#define il inline
#define fr front()
#define ep empty()
#define pp pop()
#define mod 1000000007
using namespace std;
il int rd(){
	int jya=0,tl=1;char jyt=getchar();
	while(!isdigit(jyt)){if(jyt=='-')tl=-1;jyt=getchar();}
	while(isdigit(jyt)){jya=jya*10+(jyt-'0');jyt=getchar();}
	return jya*tl;
}
il void wr(int jjy){
	if(jjy<0)putchar('-'),jjy=-jjy;
	if(jjy>9)wr(jjy/10);
	putchar(jjy%10+48);
}
int n,c[100086],x,ans;
signed main(){
	n=rd();x=rd();
	for(int i=1;i<=n;++i)c[i]=rd();
	sort(c+1,c+1+n);
	for(int i=1;i<=n;++i){
		ans+=c[i]*x;
		--x;
		if(x<1)x=1;
	}
	wr(ans);
	return 0;
}
```


---

## 作者：_txb_ (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF439B)

本题是一道下位橙， tag 建议写为贪心。
## 思路
我们首先需要把数组从大到小排序，每节课的时间会每次减少一小时，但是最少需要一小时。
### 最后提醒一句十年 oi 一场空，不开 longlong 见祖宗 
贴代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a,c[100005],sum=0;//十年oi一场空,不开longlong见祖宗 
int main()
{
	cin>>n>>a;
	for(int i=1;i<=n;i++) cin>>c[i];
	sort(c+1,c+n+1);//从小到大排序 
	for(int i=1;i<=n;i++)
	{
		sum+=c[i]*a;//每次按题目要求来计算 
		a=max(1ll,a-1);//因为每次至少一小时所以要取1和a-1的大值 
	}
	cout<<sum;
	return 0;
}
```

---

## 作者：a1a2a3a4a5 (赞：1)

# [题目：](https://www.luogu.com.cn/problem/CF439B)
#### 题目理解：
1. $n$ 是后面要输入的数，$x$ 学习一节课所用的时间，输入 $n$ 个数字，表示一章有多少节课。
2. 每学完一章德芙就变聪明一点，此后学习的每节课能少学习 $1$ 小时。
3. 等到德芙聪明到学习一节课所用的时间为 $1$ 时，德芙就不能更聪明了。
#### 解题思路：
1. 德芙学的章数越多越聪明，所以要更早地学习到更多的章数，优先找课最少的章数学习，就是从小到大排序学习。
#### 注释：
1. `x` 是德芙学习一节课所用的时间。
2. `c[i]`表示第 `i` 章有多少节课。
3. `x * c[i]` 指的是这一章学习所有课所用的时间。

4. `x = ( x == 1 ) ? x : x - 1` 是三目运算符，表示：`if(x==1) x=x; else x=x+1;`
#### 代码实现：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n , da , x , c[110000];
int main()
{
	cin >> n >> x;
	for(int i = 1;i < = n;i + +) cin >> c[i];
	sort(c + 1,c + n + 1);
	for(int i = 1;i <= n;i + +)
    	da += x * c [ i ],x = (x == 1)? x : x - 1;
	cout << da;
	return 0;
}
```

---

## 作者：weihaozhen2010 (赞：0)

# 题意：

[CF439B](https://www.luogu.com.cn/problem/CF439B)

# 思路：

- 这道题一眼就是是贪心的思路。

- 由于每一大章的学习后，会让学习时间，也就是 $x$ 减少 $1$ 个小时。因此我们应该用最多的耗时对付课节最少的大章，用最少的耗时对付课节最多的大章。这样下来，总用时才会最少。

- 综上，我们只需要对数组进行排序，然后从小到大遍历数组的同时，按上述的方式配对时间，再用计数器记录每个大章的用时的和即可。

- 注意，每章学习能力不能少于 $1$ 个小时。

# 参考代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,x,ans;
ll a[100005]; 
int main()
{
	cin>>n>>x;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++)
	{
		ans+=a[i]*x;
		if(x>1)
		{
			x--;
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Sammy_prime (赞：0)

[CF439B](https://www.luogu.com.cn/problem/CF439B)

# 思路

这题很明显是一道贪心的题目。

我们先对每节课的时间排一次降序，因为每节课的时间每次都会减少一个小时，所以最小需要一个小时。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e5+5;
int n,a[N]; ll x,sum;
int main(){
	scanf("%d%lld",&n,&x);
	for(int i=1;i<=n;i++) 
        scanf("%d",&a[i]);
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++)
		sum+=a[i]*x,x=max(1ll,x-1);
	printf("%lld\n",sum); 
	return 0;
}
```


---

## 作者：Tear_stains (赞：0)

贪心。

题意：给定章节数量 $n$，每个章节的课数 $c_i$ 和学习每节课需要的时间 $x$，求学完所有章节最短的时间。

因为每学完一个章节，以后就会少学一个小时，所以我们可以先将学习需要时间少的科目，将需要学习时间多的科目放在后面，就可以在最短时间内学完了。

Code：
```
#include<cstdio>
#include<algorithm>
#define int long long//十年OI一场空，不开long long见祖宗 
int n,x,c[100001],ans;
signed main()
{
    scanf("%lld %lld",&n,&x);
    for(int i=1;i<=n;++i)scanf("%lld",c[i]);
    std::sort(c+1,c+n+1);//将每一章所用时间从小到大排序 
    for(int i=1;i<=n;++i)
    {
        ans+=x*c[i];//计算花费的时间 
        if(x>1)x--;//如果时间大于1就减1 
    }
    printf("%lld",ans); 
    return 0;
}
```


---

## 作者：Fist_PROF (赞：0)



------------
# 1.题目翻译

你要教 Devu 学习 $n$ 个章节。第 $i$ 个章节有 $c_{i}$ 节课。当你教了某个章节的其中一节课，你应该教完这个学科的所有章节。Devu 对每节课的初始学习时间为 $X$ 小时。

你每教完他一个章节，那么教下一个章节的任何一节课所需的时间将比以前所需的时间少 $1$ 个小时。（请参阅示例以更清楚地理解它）。他每章的学习时间不能低于 $1$ 小时。

你可以随意地安排教每个章节的顺序。找出 Devu 理解所有科目所需的最短时间。


------------
# 2.解题思路

这道题可以作为一道贪心的练手好题。

题目说要让节数最多的章节学习时间最少，那么，我们只需要在那计算学习时间前排个序，从小的开始。

再看题目，我们还知道，如果说他每章的学习时间多于一小时的话，那么每学一章，他的下一章的所用时间就会减一。

注意！一定要开 long long ！

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long c[100005];
int main(){
	long long n,x;
	scanf("%lld%lld",&n,&x);
	for(long long i=1;i<=n;i++){
		cin>>c[i];
	}
	sort(c+1,c+n+1);
	long long ans=0;
	for(long long i=1;i<=n;i++){
		ans+=c[i]*x;
		if(x>1) x--;
	}
	printf("%lld",ans);
	return 0; 
}
```


---

## 作者：封禁用户 (赞：0)

***水题***

题目很好理解，直接讲思路。

既然每学一章，下一章的每一节课都能少学一个小时，这里要注意，每节课的学习时间是不能少于 $1$ 小时的，所以在累计时间的时候，要特判时间。

比如说 $x$ 为 $3$ 的 

$1$ $2$ $10$ $5$ $3$ $8$ 这个数据，如果我们先学课多的章节，那么按先后顺序，就是 $10$ $8$ $5$ $3$ $2$ $1$。

第一章所花费的时间：$10\times 3$ 分钟。

第二章所花费的时间：$8\times 2$ 分钟。

第三章所花费的时间：$5\times 1$ 分钟。

第四章所花费的时间：$3\times 1$ 分钟。

第五章所花费的时间：$2\times 1$ 分钟。

第六章所花费的时间：$1\times 1$ 分钟。

$$30 + 16 + 5 + 3 + 2 + 1 = 57$$

所以总共需要 $57$ 分钟。





如果我们先学课少的章节，那么按先后顺序，就是 $1$ $2$ $3$ $5$ $8$ $10$。

第一章所花费的时间：$1\times 3$ 分钟。

第二章所花费的时间：$2\times 2$ 分钟。

第三章所花费的时间：$3\times 1$ 分钟。

第四章所花费的时间：$5\times 1$ 分钟。

第五章所花费的时间：$8\times 1$ 分钟。

第六章所花费的时间：$10\times 1$ 分钟。

$$3 + 4 + 3 + 5 + 8 + 10 = 33$$

所以总共需要 $33$ 分钟。

明显是先看可少的章节时间用得少。

其实这很好理解，我们只需要先学课少的章节，那么课多的章节是不是每课学的时间就少了，那么总时间就少了。反之，课多的章节每课学的时间就多，课少的章节反而少了，那总时间就多了。所以要从小到大排序，再做贪心处理。

**Code**
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define re ra()
int n, x, a[100100], s;
inline int ra()
{
    int jjy = 0,txy = 1;
    char ch = getchar();
    while(!isdigit(ch)){if(ch == '-') txy = -1; ch = getchar(); }
    while(isdigit(ch)){jjy = jjy * 10 + ch - '0'; ch = getchar(); }

    return jjy * txy;
}
signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	n = re, x = re;
	for (int i = 1; i <= n; i ++) a[i] = re;
	sort(a + 1, a + 1 + n);//从小到大排序。
	for (int i = 1; i <= n; i ++)
	{
		if(x == 0) x = 1;//学的时间不能小于1，所以如果变0了就赋为1。 
		s += a[i] * x;
		x --;//每次学完一个章节，时间就减少1。
	}
	cout << s;
	return 0;
}


```



---

