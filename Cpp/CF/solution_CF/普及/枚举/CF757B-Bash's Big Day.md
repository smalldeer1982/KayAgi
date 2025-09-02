# Bash's Big Day

## 题目描述

Bash 已经踏上了成为最伟大的口袋妖怪大师的旅程。为了得到他的第一个口袋妖怪，他去了 Zulu 教授的实验室。由于 Bash 是 Zulu 教授最喜欢的学生，Zulu 允许他从实验室里取出任意数量的口袋妖怪。

但是 Zulu 警告他，每个小精灵都有一个力量值，例如 $k(k>1)$ 个小精灵在一起，它们的力量值为 $s_1,s_2,\dots,s_k$，如果 $\gcd(s_1,s_2,\dots s_k)=1$（见 $\gcd$ 的定义注释），它们之间就会互相打架。

Bash 作为一个聪明的人，不希望他的口袋妖怪互相斗争。然而，他也想最大化他从实验室里带走的神奇宝贝的数量。你能帮 Bash 找出他能带走的最大数量的口袋妖怪吗？

**注意：口袋妖怪不能与自己战斗。**

## 样例 #1

### 输入

```
3
2 3 4
```

### 输出

```
2
```

## 样例 #2

### 输入

```
5
2 3 4 6 7
```

### 输出

```
3
```

# 题解

## 作者：Cutest_Junior (赞：13)

## 题解 CF757B 【Bash's Big Day】

### 题意
+ 给出 $n$ 个数 $s_1,\dots,s_n$；
+ 选部分数组成集合，使集合大小为 $1$ 或集合内所有元素的最大公因数大于 $1$；
+ 求集合的最大大小；
+ $n\le10^5,1\le s_i\le10^5$。

### 做法

如果集合大小大于 $1$，必有一个数 $num>1$，满足集合内每个数都能被 $num$ 整除。

----

枚举每个 $num$，对于每个 $num$，判断有多少个数能被 $num$ 整除。

总复杂度 $O(n\max{s_i})$。

无法通过。

----

考虑建一个桶 $cou$，大小为 $\max{s_i}$，$cou_i$ 表示能整除 $i$ 的数的个数。

先把每个数的所有因数处理出来，放在桶里，每个数可以只用 $O(\sqrt{n})$ 的时间。

遍历桶，找出最大值。

总复杂度 $O(\sqrt{n}\max{s_i})$。

### 代码

```cpp
#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 1e5 + 5;
int cou[N];

int main() {
	int n;
	scanf("%d", &n);
	
	for (int i = 1; i <= n; ++i) {
		int x;
		scanf("%d", &x);
		
		for (int j = 1; j * j<= x; ++j) {
			if (x % j == 0) {
				++cou[j];
				if (j * j != x) {
					++cou[x / j];
				}
			}
		}
	}
	
	int ans = 1;
	for (int i = 2; i < N; ++i) {
		ans = max(ans, cou[i]);
	}
	
	printf("%d", ans);
}
```

upd：评论指出处理因数的复杂度应为 $O(\sqrt{n})$。

---

## 作者：李尧 (赞：12)

看到这题没有题解

打算来发一个

没什么难度，就是统计数列中有公因子的数的最大数目

逆向思维，枚举质数，找数列中该质数倍数的数的数目

注意：1.可能有重复战斗值，不能用bool型
（否则会一直卡第三个点）

2.至少有一个数，也就是mx初始1而非0
（否则会一直卡第十二个点）

以下代码

```
#include <bits/stdc++.h>
using namespace std;
int a,ans,mx=1,n,vis[100007];
bool v[100007];
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&a);
        vis[a]++;
    }
    for(int i=2;i<=100000;i++){
        if(v[i]) continue;
        ans=vis[i];
        for(int j=2;j<=100000/i;j++){
            v[i*j]=true;
            ans+=vis[i*j];
        }
        mx=max(mx,ans);
    }
    printf("%d",mx);
    return 0;
}
```

祝大家AC，不要复制

---

## 作者：andyli (赞：4)

题意：  
给定$n$个正整数$\{a_i\}$  
求一个子集$S$，满足$\gcd(S_1,...,S_k)>1$，同时$|S|$尽可能大。  
$1\leq n, a_i\leq 10^5$。  

$\gcd>1$，说明存在一个正整数$d>1$，满足$d$整除$S$内的所有元素。  
枚举$d=2..max{a_i}$并统计答案。  
设$V=max{a_i}$，则时间复杂度为$O(V\ln V)$。  

代码如下（[快读模板](https://andyli.blog.luogu.org/read-template)）：  
```cpp
const int maxn = 100000;

int cnt[maxn + 5];
bool p[maxn + 5];
int main()
{
    int n;
    io.read(n);
    for (int i = 1; i <= n; i++) {
        int s;
        io.read(s);
        cnt[s]++;
    }
    memset(p, 1, sizeof(p));
    p[0] = p[1] = false;
    int ans = 1;
    for (int i = 2; i <= maxn; i++) {
        if (!p[i])
            continue;
        int t = cnt[i];
        for (int j = 2; j <= maxn / i; j++)
            t += cnt[i * j], p[i * j] = false;
        ans = max(ans, t);
    }
    writeln(ans);
    return 0;
}
```

---

## 作者：18lxxrz (赞：3)

这道题的意思嘛：
在n个数中，选出k个数，使得这k个数满足：
①若k=1，~~木有任何限制条件~~


②若k>1,则gcd($a_{1}$,$a_{2}$,$a_{3}$……$a_{k}$)$\neq$1 

求k的最大值

------------
这道题~~不是太难~~，关键是思路：将每一个数分解，求出它的各个因数，最终哪个因数（不为1）数量最多，答案就是这个因数的数量



------------

```cpp
#include<bits/stdc++.h>
using namespace std;

int n,maxnum;//n表示口袋妖怪个数，maxnum记录口袋妖怪的最大力量值
map<int,int> cnt;//STL大法，有map模拟一位数组

int main ()
{
	cnt.clear();//初始化操作
	
	scanf("%d",&n);
	
	for(register int i=1;i<=n;++i)
	{
		int num;
		scanf("%d",&num);
		maxnum=max(maxnum,num);//maxnum开始记录口袋妖怪的最大力量值
		
		for(register int i=1;i<=sqrt(num);++i)//这个循环是分解num的质因数的步骤
		{
			if(num%i==0)
			{
				cnt[i]++;
				if(num/i!=i)
				{
					cnt[num/i]++;
				}
			}
		}
	}
	
	int ans=1;//只是一个坑点，如果力量值都是1的话，那么可以取1个，否则会WA
	for(register int i=2;i<=maxnum;++i)//暴力查找最大值
		ans=max(ans,cnt[i]);
	
	printf("%d",ans);//输出ans
	return 0*puts("");
}
```


---

## 作者：RemiliaScar1et (赞：2)

## CF757B Bash's Big Day

给一个正整数可重集 $S$，选出最大的子可重集 $S^{\prime}$ 使得集合中所有的元素的最大公因数不为 $1$。

---

#### 解析

显然枚举集合取法是不现实的，我们可能需要枚举最大公因数来倒着选择集合中的元素。

要使得集合最大我们肯定要选被拥有数最多的因子。这让我们很容易想起质数。

事实上，**质数中一定有最优解，合数一定不比质数更优**。

不严谨证明：

设两个质数 $p_1,p_2$ 它们能选择到的集合为 $S_1,S_2$，那么可以得到 $p_1\times p_2$ 选到的集合为 $S_1\cap S_2$，显然 $|S_1\cap S_2|\le |S_1|$ 且 $|S_1\cap S_2|\le |S_2|$。

所以，我们只需要枚举所有质数，再枚举质数的倍数统计质数的倍数在原可重集中出现的次数，次数总和就是这个质数的贡献。

答案是所有质数的贡献最大值。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N=1e5+10;

int pr[N],tot=0;
bool mp[N];

void init(int n)
{
	for(int i=2;i<=n;i++)
	{
		if(!mp[i]) pr[++tot]=i;
		for(int j=1;i*pr[j]<=n;j++)
		{
			mp[pr[j]*i]=1;
			if(i%pr[j]==0) break;
		}
	}
}
int n;
int arr[N],vis[N];

int main()
{
	scanf("%d",&n);
	int maxn=0;
	for(int i=1;i<=n;i++)
		scanf("%d",&arr[i]),maxn=max(maxn,arr[i]),vis[arr[i]]++;
	init((int)maxn+1);
	int ans=1;
	for(int i=1;i<=tot;i++)
	{
		int res=0;
		for(int j=1;pr[i]*j<=maxn;j++)
			res+=vis[pr[i]*j];
		ans=max(ans,res);
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：0x3F (赞：2)

## 前面的话

翻题单时发现了几道水题，只有这一道可以交题解，于是就有了这篇题解。

## 题意描述

大概是这样的：已知 $s_1, s_2, \cdots, s_n$ 共 $n$ 个数，从其中挑选**尽可能多的数**，使得它们的 $\gcd \ne 1$，求**最多可以挑选的个数**。

## 算法一

既然 $\gcd \ne 1$，我们就把这个 $\gcd$ **设出来**，设为 $g (g > 1)$。

于是在原数组中**无论取多少个 $g$ 的倍数**，则 $g$ 一定是它们的**公约数**，一定不超过它们的**最大**公约数。

枚举 $g \in (1, max_s]$，找出原数组中 $g$ 的**倍数的个数**，取**最大值**即可。

但是这个算法的复杂度是 $\Theta(n^2) \approx \Theta(10^{10})$，会**超时**。

## 算法二

我们发现，如果 $p$ 是 $g$ 的一个质因子，且 $g \mid s_i$，则必有 $p \mid s_i$。

所以，**选一个合数永远不会比选它的任何一个质因子要来得划算**。

我们枚举时**只取 $g$ 为素数**的情况。

但是 $1$ 到 $n$ 之间的素数个数约为 $\dfrac{n}{\ln(n)}$，最终复杂度为 $\Theta(\dfrac{n^2}{\ln(n)}) \approx 8.7 \times 10^8$，**仍然超时**。

## 算法三

我们发现**同一个数的素因子个数**并**不会很多**。

我们求出**数组中每一个数的所有素因子**，计入**计数器**中，最后再统计**每一个素数各出现了多少遍**。

请注意一点：求一个数所有素因子的复杂度因数而异：

当该数**没有大的素因子**时，复杂度会降至 $\Theta(\ln(n))$ 附近。

而当该数**为素数**时，复杂度会飙升至 $\Theta(\sqrt{n})$。

考虑**最坏情况**：给出的每一个数都是素数，则复杂度为 $\Theta(n\sqrt{n}) \approx 3.2 \times 10^7$， 有点危险，但**应该能过**。

## 特判

注意：$\color{red}{\texttt{口袋妖怪不能与自己战斗。}}$

也就是说，如果**存在** $s_i = 1$，那么它可以**独立成组**。

在程序中可以用短短的一句话解决：

`if (ans == 0) ans = 1;`

意思就是说，如果由于**数组中所有数均为** $1$ 导致了**没有素因子**，从而**算出** $0$，此时**实际答案**应为 $1$。

好了，上代码：

（我这里素数**没有专门筛出来**，所以数组中**下标为合数或** $1$ 的都**未使用**，**浪费了亿些空间**，但只要**能过就行**）

## 代码


```cpp
#include <bits/stdc++.h>
using namespace std;
int n, s, m, ans;
int cnt[100010];
int main() {
	cin >> n;
	while (n--) {
		cin >> s;
		m = max(m, s);
		for (int i = 2; i * i <= s; i++) {
			if (!(s%i)) {
				cnt[i]++;
				while (!(s%i)) s /= i;
			}
		}
		if (s != 1) cnt[s]++;
	}
	for (int i = 1; i <= m; i++) {
		ans = max(ans, cnt[i]);
	}
	if (ans == 0) ans = 1;
	cout << ans << endl;
	return 0;
}
```

## 后面的话

$$\color{white}{\texttt{求过，求赞}}$$

---

## 作者：Timon080923 (赞：1)

1.要求选出一个元素尽可能多的集合，里面的数有共同的质因子。  
2.可以先质因数分解，然后计数统计。  
3.因为数据范围较小，所以直接对每一个因子统计也可。
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100000],n,m=1;
int main(){
	cin>>n;
	for(int i=0,x;i<n;i++){
		cin>>x;
		for(int j=1;j*j<=x;j++){
			if(x%j==0){
				a[j]++;
				if(j*j!=x)a[x/j]++;
			}
		}
	}
	for(int i=2;i<100000;i++)m=max(m,a[i]);
	cout<<m;
	return 0;
}
```

---

## 作者：lxzy_ (赞：1)

本蒟蒻本来写的是一个$O(N \times \sqrt{N})$的普遍算法，但写着写着发现了另外一种奇奇怪怪的解法。

---

$\text{解法1：暴力枚举}$

这个想必大家都会。必定存在一个正整数$p$使得$p=gcd(s_1,s_2,s_3...s_k)$，将$p$从$2$到$\max(s_i)$枚举一遍，再在每个$p$对应有多少个Pokemon可以选中取一个最大的即可。

算法复杂度：$O(N \times \max(s_i))$

结果：$\color{blue}\text{TLE}$

---

$\text{解法2：求出约数直接统计}$

我们可以开一个数组$num$，表示可以被$i$整除的数有$num[i]$个，设$s_i$的 __不同的约数__ （相同的只算一遍，否则会出锅）为$q_1,q_2,q_3......$将$num[q_1]$、$num[q_2]$、$num[q_3]$ $......$ 全部加一。然后我们枚举$p$从$2$到$\max(s_i)$，找出$\max(num[p])$即可。

不过有一点要注意特判：当序列中所有数都为$1$时，答案也为$1$，因为Pokemon不会跟自己打架。用上面的方法会自动过滤掉$num[1]$。

PS：$num[i]$ 其实就相当于以$i$为最大公约数的最长序列长度。

只需要枚举到$\sqrt{N}$ 即可求出$N$的所有约数。

算法复杂度：$O(N*\sqrt{N})$

结果：$\color{green}\text{AC}$

$\huge Code:$

```cpp
#include<cstdio>
#include<cmath>
#include<iomanip>
using namespace std;
const int N=1e5+50;
int s[N];
int num[N];
int n;
int ans;
int maxn;
void get_ys(int x)//标记所有约数，复杂度O(sqrt(N)) 
{
	int ed=sqrt(x);
	for(int i=2;i<=ed;i++)
	{
		if(x%i==0)//如果当前数是它的一个约数 
		{
			num[i]++;//标记 
			if(x/i!=i)//只要没有标记过与他相对的另一个约数 
			{
				num[x/i]++;//把相对的另一个约数也标记了（约数是成对出现的） 
			}
		}
	}
}
int main()
{
	scanf("%d",&n);
	bool Is_one=true;//判断序列中的数是否全为1 
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&s[i]);
		if(s[i]!=1)
		{
			Is_one=false;//如果有一个不等于1，则标记 
		}
		num[s[i]]++;//每一个数也会被它自身整除 
		get_ys(s[i]);//标记所有约数 
		maxn=max(maxn,s[i]);//找到最大的s[i] 
	}
	if(Is_one)//如果序列中全部为1，则输出1 
	{
		printf("1");
		return 0;
	}
	for(int i=2;i<=maxn;i++)//找到最大的num[p] 
	{
		ans=max(ans,num[i]);
	}
	printf("%d",ans);//完美~ 
	return 0;
}
```

大佬轻D

---

## 作者：BotDand (赞：0)

# $\text{Problems}$

给定 $n$ 个正整数 $\{a_{i}\}$。

求一个子集 $s$，满足 $\operatorname{gcd}(s_{1},\cdots,s_{k})>1$，同时 $|s|$ 尽可能大。


# $\text{Answer}$

要使 $\operatorname{gcd}(s_{1},\cdots,s_{k})>1$，则说明存在一个数 $d$，满足 $d$ 整除 $s$ 内的所有元素。

不妨枚举 $d$，且不难证明 $d$ 必为素数。

于是可以线性筛出范围内的素数，然后找出包含因子 $d$ 的最大数即可。

查找时可用一个数组 $t$ 统计 $a_{i}$ 出现次数，方便统计。

# $\text{Code}$

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int x,ma;
int t[100002],a[10002];
bool f[100002];
int ans=1;
int m,s;
inline int read()
{
    int s=0,w=1;
    char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-')w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
    return s*w;
}
inline void write(int x)
{
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
inline void print(int x)
{
    write(x);
    putchar('\n');
}
int main()
{
    n=read();
    for(int i=1;i<=n;++i)
    {
        x=read();
        t[x]++;
        ma=max(ma,x);
    }
    for(int i=2;i<=ma;++i)
    {
        if(!f[i])
        {
            m++;
            a[m]=i;
        }
        for(int j=1;j<=m&&i*a[j]<=ma;++j)
        {
            f[i*a[j]]=1;
            if(a[j]!=0) if(i%a[j]==0) break;
        }
    }
    for(int i=1;i<=m;++i)
    {
        s=0;
        for(int j=a[i];j<=ma;j+=a[i]) s+=t[j];
        ans=max(ans,s);
    }
    print(ans);
    return 0;
}
```

---

## 作者：fls233666 (赞：0)

仔细观察可以发现，此题的难点在于如何确定在选出最多小精灵时的最大公约数。

注意到**小精灵的力量值范围很小** $(1 \le s_i \le 10^5)$ ,考虑对每个 $s_i$ 用 $O(\sqrt {s_i})$ 的时间**暴力拆因数，把拆得的因数统计**，出现最多次的比一大的因数就是最后选出最多小精灵时的最大公约数。此时这个因数的出现次数就是答案。

值得注意的是，**在只选一个小精灵时，不用考虑最大公约数**。如果仅按照上述方法操作，在数据只有一个力量值为 $1$ 的小精灵时就会出错。因此，需要把最终答案 $\texttt{ans}$ 的初始值设置为 $1$。

代码如下：

```cpp
#include<iostream>
#include<cstdio>
#define ll long long
#define rgt register int
#define qmx(a,b) a>b?a:b
using namespace std;

const int mxn = 1e5+5;

int gcd[mxn],n,ans=1,smx;
// gcd[i] 记录了当最终的公约数为 i 时能选的小精灵数量

int main(){
	scanf("%d",&n);
	for(rgt s,i=1;i<=n;i++){
		scanf("%d",&s);  //读入一个力量值
		smx=qmx(s,smx);
		for(rgt j=1;j*j<=s;j++){  //暴力拆因数
			if(s%j==0){
				gcd[j]++;  //统计
				if(s/j!=j)
					gcd[s/j]++;
			}
		}
	}
	for(rgt i=2;i<=smx;i++)
		ans=qmx(ans,gcd[i]);  //找最优方案
	printf("%d",ans);
	return 0;
}
```


---

