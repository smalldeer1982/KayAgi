# MDIGITS - Counting Digits

## 题目描述

给定两个整数 $a$ 和 $b$，我们在列表中写出 $a$ 和 $b$ 之间的数字。您的任务是计算每个数字的出现次数。

例如，如果 $a = 1024$ 且 $b = 1032$，则列表将为 $\begin{bmatrix} 1024 &1025& 1026& 1027& 1028& 1029& 1030& 1031& 1032 \end{bmatrix}$，列表中有 $10$ 个 $0$，$10$ 个 $ 1$，$7$ 个 $2$，$3$ 个 $3$ 等。

# 题解

## 作者：linyuhao (赞：5)

纯暴力数学法且时间最慢只要 $4ms$。
## 思路
先贴上主代码。
```cpp
while(xt){
	xt=xt/10;
	ws1++;//求位数
}
for(int i=1;i<=ws1;i++){
	if(i<ws1) a1[0]+=9*i*shi,nmd1+=9*shi;//处理数字0	
	k=x%10;//当前数字
	x/=10;//前部分数字
	if(k!=0) a1[k]+=q+1; 
	for(int p=1;p<k;p++) a1[p]+=shi;
	for(int j=1;j<10;j++) {
		a1[j]+=x*shi;
	}
	q+=k*shi;//后部分数字
	shi=shi*10;//十进制，相当于第几位
}
```

以 $46$ 这个数字为例子。先看个位，$1$ 到 $6$ 都加上 $1$，$1$ 到 $9$ 都加上 $4$。再看十位，$4$ 加上 $(6+1)$。$1$ 到 $3$ 加上 $10$。  
也就是把这个数拆成两份进行操作。由于数学方法对数字 $0$ 难处理，就选择**正难则反**，可以求出所有数字出现次数，再减去其它数字出现的次数。  
### 注意点  
求的是区间内，我们可以求出第一个数字减一后各数字出现次数，第二个数字各数字出现次数，再进行相减。提醒，如果第一个数字小于第二个数字要进行交换。
## 附上 AC 代码  
```cpp
#include <bits/stdc++.h>
using namespace std;
long long x,y,z,ws1=0,a1[200],a2[200],k,q=0,shi=1,nmd1=0,mod=1e9+7;
int main(){
	while(cin>>z>>y){
		if(z==0&&y==0) return 0;
		ws1=0;
		memset(a1,0,sizeof(a1)),shi=1,nmd1=0,q=0;
		long long s=0;
		if(z>y){
			int a=z;
			z=y;
			y=a;
		}
		x=z-1;
		long long xt=x,xx=x;
		while(xt){
			xt=xt/10;
			ws1++;
		}
		for(int i=1;i<=ws1;i++){
			if(i<ws1) a1[0]+=9*i*shi,nmd1+=9*shi;	
			k=x%10;
			x/=10;
			if(k!=0) a1[k]+=q+1; 
			for(int p=1;p<k;p++) a1[p]+=shi;
			for(int j=1;j<10;j++) {
				a1[j]+=x*shi;
			}
			q+=k*shi;
			shi=shi*10;
		}
		a1[0]+=(xx-nmd1)*ws1;
		for(int i=1;i<=9;i++){
			a1[0]-=a1[i];
		}
		long long nmd2=0;
		ws1=0,k,q=0,shi=1; 
		long long yt=y,yy=y;
		memset(a2,0,sizeof(a2));
		while(yt){
			yt=yt/10;
			ws1++;
		}
		for(int i=1;i<=ws1;i++){
			if(i<ws1) a2[0]+=9*i*shi,nmd2+=9*shi;
			k=y%10;
			y/=10;
			if(k!=0)a2[k]+=q+1;
			for(int p=1;p<k;p++) a2[p]+=shi;
			for(int j=1;j<10;j++) a2[j]+=y*shi;
			q+=k*shi;
			shi=shi*10;
		}
		a2[0]+=(yy-nmd2)*ws1;
		for(int i=1;i<=9;i++){
			a2[0]-=a2[i];
		}
		for(int i=0;i<=8;i++){
			cout<<a2[i]-a1[i]<<" ";
		}
		cout<<a2[9]-a1[9];
		cout<<endl;
	}
	return 0;
} 
```



---

## 作者：Liweiang (赞：5)

**题目：**[https://www.luogu.com.cn/problem/SP3928](https://www.luogu.com.cn/problem/SP3928)

----------------
一道经典的数位 DP，这里用记忆化搜索实现。

$f(i,j)$ 表示当前位数为 $i$，当前数码个数为 $j$ 时的状态。

从高到低枚举每一位，考虑每一位都可以填哪些数字。

如果当前位正好是要查询的数码，$sum$ 就加一。

还要考虑有前导零的情况，所以要加上一个判断前导零的参数 $lead$。如果有前导零，且当前数码正好为 0，$sum$ 不变，然后接着扫下去。即 `sum+(((!lead)||i)&&(i==digit))`。

剩下的就是套数位 DP 的模板了：


## AC code：

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
long long a[20],f[20][20000],l,r;
long long dfs(int pos,int digit,long long sum,bool lead,bool limit){
	//pos:当前数位; digit:要找的数码; sum:要找的数码的总和; lead:判断前导零; limit:判断限制位 
    if(pos==0) return sum;
    if(!limit&&!lead&&f[pos][sum]!=-1) return f[pos][sum];
    int up=limit?a[pos]:9; 
    long long ans=0; 
    for(int i=0;i<=up;i++)
        ans+=dfs(pos-1,digit,sum+(((!lead)||i)&&(i==digit)),lead&&!i,limit&&(i==up));  
    if(!limit&&!lead) f[pos][sum]=ans; 
    return ans; 
}
long long handle(long long num,int digit){
    int pos=0;
    while(num)
        a[++pos]=num%10,num/=10;
    return dfs(pos,digit,0,1,1);
}
signed main(){
    memset(f,-1,sizeof(f));
    while(scanf("%lld %lld",&l,&r)==2&&l&&r){
        if(r<l) swap(l,r); //注意：r有可能小于l 
        for(int i=0;i<=9;i++)
            cout<<handle(r,i)-handle(l-1,i)<<" ";
        puts("");
    }
    return 0;
} 
```



---

## 作者：火箭升空 (赞：3)

**- 这道题作为数位DP的典型题，还是很有必要仔细研究吃透的~**

这道数位DP难就难在找到递推公式，乍一看似乎没有什么规律，因为每个数的位数可能不一样...那怎么办呢？我们可以在每个数前面补上**前导零**！这样一看，似乎就可以写一写递推公式了！

我们设f[i]为i位数字，每个数字的个数。。（很容易，我们可以证得，不考虑前导零的情况下，每个数字的个数是相同的）
 
### 于是就有了f[i]=f[i-1]*10+10^(i-1)。

接下来，实现起来就很容易啦。举个例子：

对于三位数ABC，我们首先看A00，那么从0到A00每位数字出现的个数都是A*f[2]次（不考虑第一位），再考虑首位，则0~A-1 又分别出现了100次。现在，就差首位的A没有处理了！！怎么处理呢？首位的A其实出现了BC+1次！很简单对不对！然后只需对BC，C进行相同操作。

这样，我们就基本处理完了！但是，别忘了减去前导零...~~（千万别忘记，别问我是咋知道的...）~~

OK！现在！上代码喽！

```cpp
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
using namespace std;
long long cnt1[15], cnt2[15], f[15], mi[15], num[15];
long long a, b;
void solve(long long x, long long *cnt) {
  long long len = 0;
  memset(num, 0, sizeof(num));
  while (x) {
    num[++len] = x % 10;
    x /= 10;
  }
  for (int i = len; i >= 1; i--) {
    for (int j = 0; j <= 9; j++) {
      cnt[j] += f[i - 1] * num[i];
    }
    for (int j = 0; j < num[i]; j++) {
      cnt[j] += mi[i - 1];
    }
    long long res = 0;
    for (int j = i - 1; j >= 1; j--) {
      res *= 10;
      res += num[j];
    }
    cnt[num[i]] += res + 1;
    cnt[0] -= mi[i - 1];
  }
}
void init() {
  memset(cnt1, 0, sizeof(cnt1));
  memset(cnt2, 0 ,sizeof(cnt2));
}
int main() {
  while (cin >> a >> b) {
    if (a == 0 && b == 0) return 0;
    if (a > b) swap(a, b);
    init();
    mi[0] = 1;
    for (int i = 1; i <= 13; i++) {
      f[i] = f[i - 1] * 10 + mi[i - 1];
      mi[i] = 10 * mi[i - 1];
    }
    solve(a - 1, cnt1); solve(b, cnt2);
    for (int i = 0; i <= 8; i++) {
      cout << cnt2[i] - cnt1[i] << ' ';
    }
    cout << cnt2[9] - cnt1[9];
    cout << endl;
  }

  return 0;
}
```

~~好啦，看完别忘给个赞~~~

求求管理员给过吧www

---

## 作者：旋转卡壳 (赞：2)

```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int maxn=10;

int n,m;
char s[maxn];
int a[maxn],b[maxn];
//s[]数字转字符 b[] 对0~r各个位出现的次数 a[] 对0~l各个位出现的次数

inline void cul(char s[],int num[])
//如423 策略是分成423 23 3
//对每个数的最高位 考虑完全
//对其他位 只在0~400 0~20 0~3里讨论
//这样子就可以把0~423内全部数字的位数全部讨论
{	int len=strlen(s),t=1; //t数量级
    for(register int i=0;i<len-1;++i) t*=10,num[0]-=t;
    //消除前导零 i位数字减 sigma([2,len])(10^(i-1)) 2位-10 3位-110
    for(register int i=0;i<len;++i,t/=10) //缩小数量级
    {	int tmp=s[i]-'0'; //从最高位往低 该位的数字tmp
        //以下为一定是目前位数的对最高位的统计
        for(register int j=0;j<tmp;++j) num[j]+=t; //该数字出现次数+=数量级
        //如100~400中的1 在100~199中出现了100次
        num[tmp]+=atoi(s+i+1)+1; //除了该位数字的剩下数字+1
        //如423在400~423中出现了23+1次
        //以下为一定是目前位数的对其它位的统计
        for(register int j=0;j<10;++j) num[j]+=tmp*((len-i-1)*t/10);
        //各个数字出现的次数+=该位数字*下一级数量级*剩余数字长度
        //如423的1 在001~391中出现了10*4次 在010~319中出现了10*4次
        //0有些情况因为是前导零就被删掉了
    }
}

int main()
{	while(~scanf("%d %d",&n,&m) && (n||m))
    {	memset(a,0,sizeof(a));memset(b,0,sizeof(b));
        if(n>m) n^=m^=n^=m;
        sprintf(s,"%d",n-1);cul(s,a); //s='(int)(n-1)'
        sprintf(s,"%d",m);cul(s,b);
        for(register int i=0;i<maxn-1;++i)
            printf("%d ",b[i]-a[i]);
        printf("%d\n",b[9]-a[9]);
    }return 0;
}
```

---

## 作者：Exschawasion (赞：1)

本题是比较经典的数位 $\texttt{dp}$ 题。

***

诸如本题这一类求某个区间内**在外形上**符合条件的数的个数，需要使用这种 $\texttt{dp}$ 来解决。

数位 $\texttt{dp}$ 的一个基础思想就是把完全枚举区间内的数改成了枚举在**对应进制**下的各个位置的状态，例如本题的对应进制就是十进制。若进制数为 $k$（本题中 $k=10$），则完全枚举 $[1, n]$ 对应的时间复杂度为 $O(n)$，而数位 $\texttt{dp}$ 由于是按位置枚举的，时间复杂度可以降低到 $O(k \cdot \log_kn)$ 。

对于本题，可以看出，对于一个数 $x$，它对答案的贡献只与它的各个数位有关系，这和字符串相差不大，因此按位枚举是可行的；同时数据规模较大，$O(n)$ 的算法是无法通过的，所以需要使用数位 $\texttt{dp}$。

形式化地讲，当前添加的是**从左往右**的第 $p$ 位、当前状态（即当前的数）记作 $\text{cur}$、需要寻找的**数位**记作 $d$，数位 $\texttt{dp}$ 遵循以下流程：

- 如果 $p=n$ 在 $k$ 进制下的位数，也就是到达了终点（最后一位），此时应当返回；
- 往 $\text{cur}$ 后面依次加入数位 $i$，往下 $\texttt{dp}$，并记录返回值。如果 $i=d$，返回值需要 $+1$；
- 当 $i$ 大于 $n$ 的第 $p$ 位时**并且 $\text{cur}$ 的前 $p$ 位等于 $n$ 的前 $p$ 位时**，计算上面的总和，返回。因为如果添加入 $i$，不论之后如何添加，总会使得 $\text{cur}>n$ 导致答案错误.

举例来说，假设 $n=11223344$、$k=10$、当前状态 $\text{cur}=112233$、$d=1$、$p=7$；则 $\texttt{dp}$ 过程如下：

- $p$ 并不等于 $n$ 的位数 $8$，可以继续计算；
- 往 $\text{cur}$ 后面添加**数位** $0$ 变为 $1122330$，往下 $\texttt{dp}$；
- 往 $\text{cur}$ 后面添加数位 $1$ 变为 $1122331$，往下 $\texttt{dp}$，由于添加的这个数位 $=d$，**返回值** $+1$；
- （以此类推）……
- 往 $\text{cur}$ 后面添加数位 $4$ 变为 $1122334$，往下 $\texttt{dp}$；
- 由于 $5$ 大于 $n$ 的第 $p$ 位且 $\text{cur}$ 的前 $p$ 位等于 $n$ 的前 $p$ 位，**停止**，计算出上面所有项的总和并返回。

**需要注意前导零**。这可以在递归 $\texttt{dp}$ 时维护一个变量来记录状态，具体可看下面的核心代码：

```
// 这里的 p 是指剩下多少位还没有 dp，所以边界并不是 p=n 的位数；
// small 表示前 p 位是否等于 n 的前 p 位，true 表示可以往下递归；
// sum 表示 cur 中已有的 d 的数量；
// zero 表示目前是否都是前导零（d=0 时需要它）
long long dp(int p, bool small, int sum, bool zero) {
	long long ret = 0;
	if(-1 != f[p][small][sum][zero]) return f[p][small][sum][zero]; //  已经搜索过
	if(!p) return sum; // 到达边界
	int lim;
	if(small) lim = 9; // 下一位能填的最大数，如果前面已经严格小于了后面就可以任意填写
	else lim = a[p]; // 否则只能填写到和 n 的第 p 位相同的数，a[p] 表示 n 的第 p 位
	for(int i = 0; i <= lim; i++) {
		ret += dp(
			p - 1,
			small || i < lim, // 是否严格小于
			sum + ((!zero || i != 0) && i == d), // 前导 0 需要注意
			zero && (i == 0) 
		);
	}
	return f[p][small][sum][zero] = ret;
}
```

以上就是数位 $\texttt{dp}$ 的基本思路与框架。

这个框架其实很灵活，可以加入更多的限制条件（比如限制某一位只能放某个或某些数位），也可以改变进制 $k$ 的值来适配具体题目情景内容。

最后，由于题目要求的是 $[L, R]$ 区间中符合条件的数的数量，答案应当是 $[1, R]$ 区间所含数量减去 $[1, L-1]$ 区间所含数量。这里给出剩余部分的代码（头文件、数组的声明等已经省略）：

```
long long Yureta(long long x) {
	int pos = 0;
	while(x) { // 分离 x 的每一位
		a[++pos] = x % 10, x /= 10;
	}
	memset(f, -1, sizeof(f));
	return dp(pos, false, 0, true);
}

int main() {
	long long a, b;
	while(cin >> a >> b && a && b) {
		if(a > b) swap(a, b);
		for(d = 0; d <= 9; d++) { // 考虑 d 的每一种情况
			cout << Yureta(b) - Yureta(a - 1) << ' ';
		}
		cout << endl;
	}
	return 0;
}
```

数位 $\texttt{dp}$ 的应用场景较为丰富，若想要继续练习，可以接着尝试 [$\texttt{P2657}$](https://www.luogu.com.cn/problem/P2657)、[$\texttt{P2602}$](https://www.luogu.com.cn/problem/P2602)、[$\texttt{P4124}$](https://www.luogu.com.cn/problem/P4124) 等题。




---

## 作者：xqh07 (赞：1)

# 题型：
一道**数位dp**的裸题。

# 题目大意：

给出多组 $l$ 与 $r$，在列表中写出每个 $l$ 与 $r$ 间的数，求 $0$ ~ $9$ 每个数字在列表中出现的次数并输出。注意 $l$ 不一定小于 $r$。

# 思路：

我们可以用**记忆化搜索**解决这道题。

考虑参数 $y,p,q,r,s$，分别表示**搜索的数字**，**枚举到哪位**，**y的个数**，**是否处于前导零状态**以及**是否有进位限制**。

分别搜索 $0$ ~ $9$ 即可，详见代码。

# 注意：

1：$l$ 不一定小于 $r$

2：排除前导零

# code :

```cpp
#include <bits/stdc++.h>
using namespace std;
int a[15];
long long x, y, f[15][15][20][2];
long long dfs(int y, int p, int s, int q, int r)
{
	if(!p)
		return s;
	
	if(f[p][s][q][r] != -1)
		return f[p][s][q][r];
		
	long long res = 0;
	int k = r ? a[p] : 9;
	
	for(int i = 0; i <= k; i++)
	{
		res += dfs(y, p - 1, s + ((!q || i) && (i == y)), q && !i, r && (i == k));
	}
	return f[p][s][q][r] = res;
}
long long divide(int y, long long x)
{
	int len = 0;
	while(x)
	{
		a[++len] = x % 10;
		x /= 10;
	}
	memset(f, -1, sizeof(f));
	return dfs(y, len, 0, 1, 1);
}
int main()
{
	cin >> x >> y;
	while(x || y)
	{
		if(x > y)swap(x, y);
		for(int i = 0; i <= 9; i++)
			cout << divide(i, y) - divide(i, x - 1) << " ";
		cout << endl;
		cin >> x >> y;
	}
	
	return 0;
}
```


---

## 作者：bzzltl (赞：1)

容易发现应该用到数位dp，考虑 $f_{i,j,k}$ 表示一个 $i$ 位数的最高位上的数字为 $j$，其中 $k$ 的出现次数。

### 初始化：

对一位数进行初始化，显然 $f_{1,i,j}=1\times[i==j]$。

（$[x]$表示若 $x$ 为真，则这个式子的值为 $1$，否则为  $0$。）

### 递推公式：

首先考虑最高位上的数字 $j$ 等于数位 $k$ 的情况。

 $f_{i,j,k}\pm10^{i-1}$。

举个例子，比如说如果 $i=2$,$j=3$,$k=3$ 的话，$f_{i,j,k}$ 的实际意义表示一个二位数，最高位上的数是  $3$，求 $3$ 的出现次数。

光满足 $i$，$j$ 的条件的话，有 $30\sim39$ 共 $10$ 个数字，其中 $f_{i,j,k}\pm10^{i-1}$ 就是指的这个最高位 $3$ 可以出现的次数。

然后考虑 $j$ 与 $k$ 不相等的情况。

用 $4$ 层循环，$i$ 表示几位数，$j$ 表示要更新的数的最高位，$k$ 表示用来更新的数的最高位，$l$ 表示统计哪个数位的答案。

将上面两步稍微合并一下就是以下函数：


```
void init()
{
	p[0]=1;
	for(int i=1;i<=9;i++) p[i]=p[i-1]*10;
	for(int i=0;i<=9;i++) f[1][i][i]=1;
	for(int i=2;i<=9;i++)
		for(int j=0;j<=9;j++)
		{
			f[i][j][j]+=p[i-1];
			for(int k=0;k<=9;k++)
				for(int l=0;l<=9;l++)
					f[i][j][l]+=f[i-1][k][l];
		}
}
```
题目求的是区间内各个数位的出现次数，可以用前缀和来维护答案。

考虑维护答案，可以分为三个部分：

1.位数小于 $i$ 的。

2.位数等于 $i$ 的，但是最高位小于要求的 $j$ 的。

3.剩余的部分。

```
void qiu(int k,int id)
{
	int cnt=0;
	while(k)
	{
		a[++cnt]=k%10;
		k/=10;
	}
	for(int i=1;i<cnt;i++) for(int j=1;j<=9;j++) for(int k=0;k<=9;k++) b[k][id]+=f[i][j][k];
	//小于要求位数的           枚举最高位是j       k这个数字的数量
	for(int j=1;j<a[cnt];j++) for(int k=0;k<=9;k++) b[k][id]+=f[cnt][j][k];
	//等于要求位数，但是最高位比要求的小 k这个数字的数量
	int tot=0;
	sum[++tot]=a[cnt];
	for(int i=cnt-1;i>=1;i--)
	{
		for(int j=0;j<a[i];j++) for(int k=0;k<=9;k++) b[k][id]+=f[i][j][k];//√
		for(int j=1;j<=tot;j++) b[sum[j]][id]+=a[i]*p[i-1];
		sum[++tot]=a[i];//统计一下需要更新的前缀
	}
}
```

举例解释一下第三个部分。

假设要求 $4315$ 这个数字。

通过第一步和第二步我们已经得到了 $0\sim 3999$ 这个范围。

在第一次循环里面，$sum_1=4$。

`
for(int j=0;j<a[i];j++) for(int k=0;k<=9;k++) b[k][id]+=f[i][j][k];`

这一步中，可以更新 $4000\sim4299$里的 $000\sim 299$。

`for(int j=1;j<=tot;j++) b[sum[j]][id]+=a[i]*p[i-1];`

这个是更新 $4000\sim4299$ 里面的所有的 $4$。

`sum[++tot]=a[i];`

统计一下需要更新的前缀。

以此往后类推，即可完成本题。

完整代码：

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=20;
const int IM=2147483647;
const long long LLM=9223372036854775807;

inline int read()
{
	int x=0,y=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-') y=-y;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+(c^'0');c=getchar();}
	return x*y;
}

int n,m,a[N],b[N][2],p[N],sum[N],f[N][N][N];

void init()
{
	p[0]=1;
	for(int i=1;i<=9;i++) p[i]=p[i-1]*10;
	for(int i=0;i<=9;i++) f[1][i][i]=1;
	for(int i=2;i<=9;i++)
		for(int j=0;j<=9;j++)
		{
			f[i][j][j]+=p[i-1];
			for(int k=0;k<=9;k++)
				for(int l=0;l<=9;l++)
					f[i][j][l]+=f[i-1][k][l];
		}
}

void qiu(int k,int id)
{
	int cnt=0;
	while(k)
	{
		a[++cnt]=k%10;
		k/=10;
	}
	for(int i=1;i<cnt;i++) for(int j=1;j<=9;j++) for(int k=0;k<=9;k++) b[k][id]+=f[i][j][k];
	//小于要求位数的           枚举最高位是j       k这个数字的数量
	for(int j=1;j<a[cnt];j++) for(int k=0;k<=9;k++) b[k][id]+=f[cnt][j][k];
	//等于要求位数，但是最高位比要求的小 k这个数字的数量
	int tot=0;
	sum[++tot]=a[cnt];
	for(int i=cnt-1;i>=1;i--)
	{
		for(int j=0;j<a[i];j++) for(int k=0;k<=9;k++) b[k][id]+=f[i][j][k];
		for(int j=1;j<=tot;j++) b[sum[j]][id]+=a[i]*p[i-1];
		sum[++tot]=a[i];//统计一下需要更新的前缀
	}
}

signed main()
{
	init();
	int l=read(),r=read();
	while(l||r)
	{
		if(l>r) swap(l,r);
		memset(b,0,sizeof b);
		qiu(r+1,0);
		qiu(l,1);
		for(int i=0;i<=9;i++)
		{
			printf("%lld ",b[i][0]-b[i][1]);
			if(i!=9) printf("");
			else puts("");
		}
		l=read(),r=read();
	}
	return 0;
}
```

---

## 作者：fls233666 (赞：1)

首先注意到 $0 < a,b < 10^8$，对于每个测试点最多有 $500$ 组数据的情况，用暴力肯定是过不去的。但是进一步考虑可以发现，对于每个数字，我们只要统计它在每个数位上出现的次数即可。于是我们转向考虑**数位DP**。

由于数字之间位数不同的原因，我们在设计状态时还要考虑前导 $0$ 的问题【不能把前导 $0$ 当作数字中的 $0$ 统计进去】。因此，我们设 $dp(i,j,0/1,0/1)$ 表示当前处理到第 $i$ 位，出现了 $j$ 个要统计的数字，当前是否为前导 $0$，是否比上限的数字小。设计完成状态后，我们仍然使用最简单直接的处理方法：**记忆化搜索**。于是我们得到了以下搜索函数：

```cpp
ll dpwork(int di,int cnt,int num,bool fake0,bool pmax){

	if(di>lmax)
		return cnt;  //搜索到达边界，返回统计的值
        
	if(dp[di][cnt][fake0][pmax]!=-1)
		return dp[di][cnt][fake0][pmax];  //当前状态搜过了，直接使用
        
	int top=pmax?9:maxnum[di];  //判断上界
	dp[di][cnt][fake0][pmax]=0;
	for(rgt i=0;i<=top;i++){
		if(!fake0||i)  //判断前导 0，分别处理状态
			dp[di][cnt][fake0][pmax]+=dpwork(di+1,i==num?cnt+1:cnt,num,false,i<top||pmax);
		else
			dp[di][cnt][fake0][pmax]+=dpwork(di+1,cnt,num,true,i<top||pmax);
	}
    
	return dp[di][cnt][fake0][pmax];  //返回统计结果
}
```

接下来就是以 $0$ 到 $9$ 所有数字作为要统计的数字分别跑一遍搜索了。

值得注意的是，通过观察样例可以发现，输入的数据中存在 $a>b$ 的情况。这时候需要将 $a$ 与 $b$ 交换才能得到正确答案。

另外，上述搜索函数得到的结果是 $[1,max]$ 之间数字 $num$ 出现的次数。利用前缀和的思想，我们先搞出 $[1,b]$ 的所有数字的统计结果，再搞出 $[1,a-1]$ 的所有数字的统计结果，两者相减即可。

完整代码如下：

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#define ll long long
#define rgt register int
using namespace std;

ll dp[12][12][2][2]; 
ll a,b,lmax;
ll maxnum[12];
ll ans[12];

ll dpwork(int di,int cnt,int num,bool fake0,bool pmax){

	if(di>lmax)
		return cnt;  //搜索到达边界，返回统计的值
        
	if(dp[di][cnt][fake0][pmax]!=-1)
		return dp[di][cnt][fake0][pmax];  //当前状态搜过了，直接使用
        
	int top=pmax?9:maxnum[di];  //判断上界
	dp[di][cnt][fake0][pmax]=0;
	for(rgt i=0;i<=top;i++){
		if(!fake0||i)  //判断前导 0，分别处理状态
			dp[di][cnt][fake0][pmax]+=dpwork(di+1,i==num?cnt+1:cnt,num,false,i<top||pmax);
		else
			dp[di][cnt][fake0][pmax]+=dpwork(di+1,cnt,num,true,i<top||pmax);
	}
    
	return dp[di][cnt][fake0][pmax];  //返回统计结果
}

int main(){
	scanf("%lld%lld",&a,&b);
	while(a&&b){
    
		if(a>b){
			a^=b;
			b^=a;
			a^=b;
		}  //交换a,b
        
		a--;
		lmax=0;
		while(b){
			lmax++;
			maxnum[lmax]=b%10;
			b/=10;
		}
		reverse(maxnum+1,maxnum+1+lmax);
        //按数位拆分b
        
		for(rgt fi=0;fi<10;fi++){
			for(rgt i=0;i<12;i++)
				for(rgt j=0;j<12;j++)
					for(rgt k=0;k<2;k++)
						for(rgt l=0;l<2;l++) 
							dp[i][j][k][l]=-1;
			ans[fi]=dpwork(1,0,fi,true,false);
		}  //统计[1,b]的答案
        
		lmax=0;
		while(a){
			lmax++;
			maxnum[lmax]=a%10;
			a/=10;
		}
		reverse(maxnum+1,maxnum+1+lmax);
        //按位拆分 a-1
        
		for(rgt fi=0;fi<10;fi++){
			for(rgt i=0;i<12;i++)
				for(rgt j=0;j<12;j++)
					for(rgt k=0;k<2;k++)
						for(rgt l=0;l<2;l++) 
							dp[i][j][k][l]=-1;
			ans[fi]-=dpwork(1,0,fi,true,false);
		}//统计[1,a-1]的答案，并直接相减得到[a,b]的答案
        
		for(rgt i=0;i<10;i++)
			printf("%lld ",ans[i]);	
		printf("\n");  //输出结果
		scanf("%lld %lld",&a,&b);
	}
	return 0;
}

```


---

## 作者：Link_Space (赞：1)


看到这道题的第一眼就知道这是一道毫无悬念的数位DP题，写法与大多数位DP写法都相同，总的思路就是先用一个三维dp[i][j][k]来预处理出所有以j为最高位的i位数中所含的k数码的数量，然后用一个数位dp分别求出每一个数码的区间内的出现次数然后输出即可，详情请见代码内解释


以下是AC代码
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
typedef unsigned long long ll;
const int N = 25;
ll dp[N][10][10];
ll ksm(ll a,ll b)
{
	ll res=1;
	while(b)
	{
		if(b&1)
			res*=a;
		a*=a;
		b >>= 1;
	}
	return res;
}
void init()
{
	for (ll i = 0; i <= 9;i++)
		dp[1][i][i] = 1;
	for (ll i = 2; i < N;i++)
	{
		for (ll j = 0; j <= 9;j++)
		{
			for (ll k = 0; k <= 9;k++)
			{
				for (ll r = 0; r <= 9;r++)
				{
					dp[i][j][r] += dp[i - 1][k][r];
				}
			}
			dp[i][j][j] += ksm(10, i - 1);//每次加完之后最高位的数字都忘了加，所以要在加完之后把最高位的数字出现次数也加上
		}
	}
}
ll make(ll n,ll search)//寻找0-n的数中search数码的出现数量
{
	ll digit[N];
	ll len = 0;
	while(n)
	{
		digit[++len] = n % 10;
		n/=10;
	}
	ll res = 0;
	for (int i =1;i<len;i++)
	{
		for (int j = 1; j <= 9;j++)
		{
			res += dp[i][j][search];
		}
	}//枚举位数不足len的数中含有多少个search数码
	for (int i = 1; i < digit[len];i++)
	{
		res += dp[len][i][search];//加上位数为len的数中的search数码
	}
	for (int i = len-1; i >= 1;i--)
	{
		int x = digit[i];
		for (int j = 0; j < x;j++)
			res += dp[i][j][search];
		for (int j = len; j > i ;j--)
		{
			if(digit[j]==search)
				res += digit[i] * ksm(10, i - 1);//数位DP的基本套路，具体思路和上面的预处理思路相同
		}
	}
	return res;//返回所有search数码的数量
}
int main()
{
	init();
	ll l,r;
	scanf("%llu%llu", &l, &r);
	for (ll i = 0; i <= 9;i++)
	{
		printf("%llu ", make(r+1, i) - make(l, i));//直接输出每一位数码的出现个数即可
	}
}
```


---

## 作者：HHYQ_07 (赞：0)

# 题解

## [题目链接](https://www.luogu.com.cn/problem/SP3928)

## 多倍经验

[P1239](https://www.luogu.com.cn/problem/P1239) [SP17247](https://www.luogu.com.cn/problem/SP17247) [P2602](https://www.luogu.com.cn/problem/P2602) [P1836](https://www.luogu.com.cn/problem/P1836) [P4999](https://www.luogu.com.cn/problem/P4999)

## 思路

一道经典的[数位 dp](https://oi.wiki/dp/number/)，我们考虑递推实现。

### 定义状态

读者不妨在纸上写一些数，我们会发现对于满 $i$ 位的数，所有数码出现的次数都是相同的，也就是说 $\underbrace{999...9}_{i}$ 中 $0-9$ 出现的次数相同。那么令 $f_i$ 代表在满 $i$ 位数字的情况下，每种数码有多少个；$mi_i$ 表示 $10^{i-1}$。

### 转移方程

$$f_i=f_{i-1}\times10+mi_{i-1}$$

$$mi_i=10\times mi_{i-1}$$

### 转化答案

其实数位 dp 的难点不在于递推部分，而是如何转化出最后的答案。首先我们会发现区间 $[a,b]$ 中各个数码出现的次数是区间 $[1,b]$ 中各个数码出现的次数减去区间 $[1,a-1]$ 中各个数码出现的次数。于是问题就被转化成为了求区间 $[1,i]$ 中各个数码出现的次数。我们发现一个数可以拆分成 $A\underbrace{000...0}_{i}+B\underbrace{000...0}_{i-1}+...+Z$ 的形式，那么小于 $A\underbrace{000...0}_{i}$ 的数各个的数码的数量为 $f_{i}$ 个，首位 $A$ 出现了 $BC...Z$ 次，到这里首位 $A$ 的贡献处理完了。就这样一位一位拆分、处理，最后减去前导零就是答案了。

## 注意事项

1. $a,b$ 在数据中不一定是 $a\leq b$，也有可能是 $a>b$，要注意判断。
2. 数据是多测，别忘了清空。

## AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long 
const int N=20;
int t,l,r,f[N],mi[N],a[N],ans1[N],ans2[N],anss;
void solve(int n,int *ans)
{
	int tmp=n,len=0;
	while(n)
	{
		a[++len]=n%10;
		n/=10;
	}
	for(int i=len;i;i--)
	{
		for(int j=0;j<=9;j++)ans[j]+=f[i-1]*a[i];
		for(int j=0;j<a[i];j++)ans[j]+=mi[i-1];
		tmp-=mi[i-1]*a[i];
		ans[a[i]]+=tmp+1;
		ans[0]-=mi[i-1];
	}
}
signed main()
{
	ios::sync_with_stdio(false);
	mi[0]=1ll;
	for(int i=1;i<=20;i++)
	{
		f[i]=f[i-1]*10ll+mi[i-1];
		mi[i]=10ll*mi[i-1];
	}
	cin>>l>>r;
	while(l)
	{
		anss=0;
		memset(ans1,0,sizeof(ans1));
		memset(ans2,0,sizeof(ans2));
		solve(max(l,r),ans1);solve(min(l,r)-1,ans2);
		for(int i=0;i<=9;i++)
			cout<<ans1[i]-ans2[i]<<" ";
		cout<<endl;
		cin>>l>>r;
	}
    return 0;
}
```

---

## 作者：Hisaishi_Kanade (赞：0)

数位 dp 复健中。

我们发现对于每个数字 $0\sim 9$ 其实是互相独立。

那么就是 $10$ 个几乎相同子问题并列。只需要解决其中一个即可。

设 $f_{i,j,k}$ 表示处理前 $i$ 个数位，已经有 $j$ 个数位上的数与 $k$ 相等。

那么接下来枚举第 $i+1$ 个数位，如果前面的数位都“顶格”，这个数位只能枚举到限制，否则可以从 $0$ 枚举到 $9$。

如果 $k\not = 0$ 或者这个数位之前已经有非零的数位，那么当枚举出来的下一位和 $k$ 相同则 $j$ 可以加一，即 $f_{i,j,k}\gets f_{i,j,k}+f_{i+1,j+1,k}$。

反之，则这一位枚举对 $j$ 没有贡献。$f_{i,j,k}\gets f_{i+1,j,k}$。

这个过程中，我们需要记录前面是不是都“顶格”、前面有没有非零（也就是这一位会不会成为前导零）、及 $i,j,k$ 三个值。

接下来使用记忆化搜索实现就可以了。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define rep(i,l,r) for(i=l;i<=r;++i)
int f[15][15],lg[15];
int ret;
inline int dp(bool limit,bool lzero,int dep,int fl,int sum)
{
//	printf("%d %d %d %d %d\n",limit,lzero,dep,fl,sum);
	if(dep==0)
		return sum;
	if(!limit && !lzero && f[dep][sum]!=-1)return f[dep][sum];
	int ret=0,i,nxt=limit?lg[dep]:9;
	rep(i,0,nxt)ret+=dp(limit&&(i==lg[dep]),lzero&&(i==0),dep-1,fl,sum+(!(lzero&&(i==0))&&i==fl));//,printf("%d\n",i);//,printf("%d\n",ret);
	if(!limit && !lzero)f[dep][sum]=ret;
	return ret;
}
inline int solve(int v,int fl)
{int cnt,i,j;
	rep(i,0,12)rep(j,0,12)f[i][j]=-1;
	cnt=0;while(v)
	{
		lg[++cnt]=v%10;
		v/=10;
	}
	return dp(1,1,cnt,fl,0);
}
int main()
{int i,j,l,r;
//	printf("%d\n",solve(10,2));
	while(cin>>l>>r && (l||r))
	{if(l>r)swap(l,r);
		rep(i,0,8)printf("%d ",solve(r,i)-solve(l-1,i));
		printf("%d\n",solve(r,9)-solve(l-1,9));
	}
	return 0;
}
```

---

## 作者：封禁用户 (赞：0)

一道模板题。

## 分析

**【总体思路】**

题目是让我们求在 $l$ 到 $r$ 中每个数字出现的次数，我们不妨将 $f[i][j][k]$ 定义为：在第 $i$ 位，前一个数字为 $j$，且目前已经出现了 $k$ 个指定数字时，最终的答案。不难发现，这是一种只能查找某一个指定数字在区间内出现的次数的数组。所以，我们在写记忆化搜索的时候，需要把 $0$ 到 $9$ 都找一遍。

**【记忆化搜索】**

首先，在搜索函数中，我们需要定义以下几个变量：目前寻找的是第几位；上一位选定的值； 是否有前导零； 能选择的数是否有上界； 目前找到的指定数字的数量； 指定数字的值。

函数如：
```
int dfs(int now,int last,bool if_z,bool if_l,int ans,int x)
```

其次，在特判一些情况时，我们直接套模板就行了，只需注意在最后一位时，我们返回的值是目前找到的指定数字的数量，而不是零或一。

最后，在枚举这一位选择的所有情况时，我们不仅要判断是否含有前导零，还要判断一下这一位目前选择的数是不是指定数字。

最终函数如下：

```cpp
int dfs(int now,int last,bool if_z,bool if_l,int ans,int x)
{
	if(!now) return ans;
	else
	{
		if(!if_z&&!if_l&&f[now][last][ans]!=-1) return f[now][last][ans];//已经找过了 
		else
		{
			int ans_s=0,up=if_l?a[now]:9;
			for(int i=0;i<=up;i++)
				if(if_z&&!i) ans_s+=dfs(now-1,i,1,if_l&&i==up,ans,x);//有前导零 
				else ans_s+=dfs(now-1,i,0,if_l&&i==up,ans+(i==x?1:0),x);//i=x，即这一位选定的正好是指定数字 
			return if_l?ans_s:(if_z?ans_s:f[now][last][ans]=ans_s);
		}
	}
}
```

**【主函数】**

在找每一位的时候，我们也是按照前缀和的思想进行寻找。注意的是，题目给定的 $l$ 和 $r$ 顺序不一定，我们需要判断一下谁是 $l$ 谁是 $r$。同时，在输出的时候，我们不能输出多余的空格，不然就会判错。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=15;
int a[N],f[N][N][N];
int l,r;
int dfs(int now,int last,bool if_z,bool if_l,int ans,int x)
{
	if(!now) return ans;
	else
	{
		if(!if_z&&!if_l&&f[now][last][ans]!=-1) return f[now][last][ans]; 
		else
		{
			int ans_s=0,up=if_l?a[now]:9;
			for(int i=0;i<=up;i++)
				if(if_z&&!i) ans_s+=dfs(now-1,i,1,if_l&&i==up,ans,x);
				else ans_s+=dfs(now-1,i,0,if_l&&i==up,ans+(i==x?1:0),x);
			return if_l?ans_s:(if_z?ans_s:f[now][last][ans]=ans_s);
		}
	}
}
int check(int x,int y)
{
	memset(f,-1,sizeof(f));
	int len=0;
	while(x) a[++len]=x%10,x/=10;
	return dfs(len,0,1,1,0,y);
}
signed main()
{
	while(cin>>l>>r&&l&&r)
	{
		if(l>r) swap(l,r);
		for(int i=0;i<=9;i++)
			cout<<check(r,i)-check(l-1,i)<<(i!=9?" ":"\n");		
	}
	return 0;
}
```


---

## 作者：sunkuangzheng (赞：0)

**【题目分析】**

从多倍经验看过来的，~~惊讶的发现可以水题解。~~

这道题是数位 dp 模板题之一，我们边看代码边讲。

首先确定总体思路：一次性统计出十个数字的出现频率较难，因此我们分开处理每一个数字的出现次数。

- 第一部分 搜索

采取搜索的方式，`pos` 代表搜到了哪一位，`numi` 代表这一次选定的数字（参数 `k`）出现的次数，`lim` 表示当前位是否有限制（$1$ 表示有限制），`pre` 表示当前位是否为前导零（$1$ 表示是）。

```cpp
int dfs(int pos,int numi,bool lim,bool pre,int k){
	if(pos == 1) return numi;
	int up = lim ? num[pos-1]:9;
	int ans = 0;
	for(int i = 0;i <= up;i ++){
		ans += dfs(pos-1,numi + (k == 0?(!pre && i == k):(i == k)),(lim && i == up),(pre && i == 0),k);
	}
	return ans;
}
```
`up` 的含义是**当前枚举位的最高限制**，是为了让枚举的数字不超过给定数字。

`numi + (k == 0?(!pre && i == k):(i == k))` 的意思是如果我们在统计 $0$ 的数量，那么如果是前导零计数器就不能增加；否则只要这一位与统计的数字相等，计数器自增。

`(lim && i == up)` 是指如果之前有限制，并且这一位还与上界相等，那么限制依然存在。为什么用与运算而不用或运算？举个例子，我们的枚举上限是 $114514$，目前枚举到的是 $1045$，此时虽然 $5$ 这一位相等，但是不论以后怎么枚举，我们枚举的数字一定小于 $114514$。

`(pre && i == 0)` 是指如果这一位是前导零，并且枚举的还是 $0$，那么前导零状态就要延续。

至此本题的重点——搜索部分就写完了。

但是纯暴力搜索复杂度是不优的，因此我们需要采用**记忆化搜索**。

- 第二部分 记忆化搜索

我们直接选取 `dfs` 函数的参数当作状态，设 `f[pos][numi][lim][pre]` 表示艘至第 `pos` 位，当前数字出现了 `numi` 次，限制和前导零状态分别为 `lim` 和 `pre` 时的答案，初始化为 `-1`。在搜索函数中添加判断语句，如果当前状态下 $f \ne -1$，则直接返回该值。每次搜索完毕后，将答案赋给 $f$ 数组。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int f[15][15][2][2],num[15],n,l,r;
int dfs(int pos,int numi,bool lim,bool pre,int k){
	if(f[pos][numi][lim][pre] != -1) return f[pos][numi][lim][pre];
	if(pos == 1) return numi;
	int up = lim ? num[pos-1]:9;
	int ans = 0;
	for(int i = 0;i <= up;i ++){
		ans += dfs(pos-1,numi + (k == 0?(!pre && i == k):(i == k)),(lim && i == up),(pre && i == 0),k);
	}
	return f[pos][numi][lim][pre] = ans;
}
int work(int x,int k){
	memset(f,-1,sizeof(f));
	int u = 0;
	while(x){
		num[++u] = x % 10;
		x /= 10;
	}
	n = u;
	return dfs(n+1,0,1,1,k);
}

```

输出时，枚举 $0\sim 9$ 的数字，每一次询问运用前缀和思想，输出 `work(r)-work(l-1)` 即可。

---

## 作者：Jasper08 (赞：0)

首先有一个想法：$[a,b]$ 中数字 $i$ 出现的次数，等于 $[1,b]$ 中数字 $i$ 出现的次数减去 $[1,a-1]$ 中数字 $i$ 出现的次数。现在问题转化为求 $[1,b]$ 中数字 $i$ 出现的个数。

假设当前考虑到 $b$ 从右往左数第 $j$ 位，令 $l=\dfrac{n}{10^j}$（即 $l$ 是 $b$ 中在第 $j$ 位左边的部分），$r=n\bmod 10^{j-1}$（即 $r$ 是 $b$ 中在第 $j$ 位右边的部分）。我们分情况讨论：

1. 新数第 $j$ 位左边的部分小于 $l$：
   - $i\ne 0$：此时第 $j$ 位右边的部分可以随便取，数量为 $l\times 10^{j-1}$； 
   - $i=0$ 且 $l\ne 0$：此时第 $j$ 位右边的部分不能全为 $0$，数量为 $(l-1)\times 10^{j-1}$。
2. 新数第 $j$ 位左边恰好等于 $l$（$l\ne 0$ 或 $i\ne 0$）：
   - $b$ 中第 $j$ 位的数小于 $i$：数量为 $0$；
   - $b$ 中第 $j$ 位的数恰好为 $i$：数量为 $r+1$；
   - $b$ 中第 $j$ 位的数大于 $i$：后面的部分可以随便取，数量为 $10^{j-1}$。

由此计算即可。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>

using namespace std;

int a, b;

int get_digit(int n) {
    int s = 0;
    while (n) n /= 10, s ++;
    return s;
}

int count(int n, int i) {
    int cnt = 0, d = get_digit(n);
    for (int j = 1; j <= d; ++j) {
        int p = pow(10, j-1), l = n / (p*10), r = n % p;
        // 第j位左边小于l
        if (i) cnt += l * p;
        else if (l) cnt += (l-1) * p;
        // 第j位左边等于l
        int t = n / p % 10;
        if (t == i && (i || l)) cnt += r+1;
        else if (t > i && (i || l)) cnt += p;
    }
    return cnt;
}

int main() {
    while (cin >> a >> b, a || b) {
        if (a > b) swap(a, b);
        for (int i = 0; i <= 9; ++i) 
            printf("%d ", count(b, i)-count(a-1, i));
        puts("");
    }
    return 0;
}
```

---

## 作者：SunsetSamsara (赞：0)

## 题意

给定两个整数 $a$ 和 $b$，在 $a$ 和 $b$ 之间的数字中求每个数字的出现次数。

## 分析

这是一道数位 $\text{dp}$ 的经典题目。乍看上去，每个数的位数不一样，分开一位位算又太繁琐。但是，不难发现，受位数影响的只有数字 $0$ 的规律而已。这样的话，就可以在数字前先补上前导零，最后再用区间所有数的位数之和减去从 $1$ 到 $9$ 的位数来计算 $0$ 的个数了。

先算一下所有数的位数之和吧。计算一下 $a$ 和 $b$ 的位数 $len1$ 和 $len2$，接下来如果 $len1 = len2$ 就判掉，否则分以下 $3$ 段算出结果：

1. 算出 $10^{len2 - 1}$ 到 $r$ 的位数和，即为 $(10^{len2 - 1} - r + 1)\times len2$；
2. 算出 $l$ 到 $10^{len1} - 1$ 的位数和，即为 $(10^{len1} - r) \times len1$；
3. 算出 $10^{len1}$ 到 $10^{len2 - 1} - 1$ 的位数和，就是 $\sum\limits_{i = len1}^{len2 - 1}10^{i - 1} \times 9i$

接下来考虑差分，算出从 $1$ 到 $x$ 的 $y$ 的出现次数。令 $dp_{i, j, k}$ 表示前 $i$ 位中最前一位的值为 $j$ 的时候数字 $k$ 的出现次数（奇怪的方法），那么有：

若 $l = k$，则 $dp_{i + 1, k, l}$ 要加上 $dp_{i, j, l} + 10^{i - 1}$（容易理解，$10^{i - 1}$ 是第一位的 $k$ 贡献的）

否则，$dp_{i + 1, k, l}$ 要加上 $dp_{i, j, l}$ （一样容易理解，$l$ 的个数只能靠后面的 $i$ 位来贡献）

有了这些之后，就可以枚举每一位与当前这一位一个个加上这一位的值（方法和求 $dp$ 一模一样）来求出答案了。

## 代码

```cpp
#include <stdio.h> 
#include <string.h>
#define lld long long 
lld dp[30][10][10];
lld pow10[20];
lld ans[10];
lld calc(lld x, lld y) {
	if (x < 0) return 0; else if (x == 0) return 0; // 判掉奇奇怪怪的特殊情况
	int len; for (len = 0; pow10[len] <= x; ++ len); // x 的位数即为 len
	lld ans = 0, bit;
	for (int i = 1; i <= len; ++ i) {
		bit = x / pow10[len - i] % 10;
		for (lld j = 0; j < bit; ++ j) ans += dp[len - i + 1][j][y]; // 加上这些dp值
		if (bit == y) ans += x % pow10[len - i]; // 特判最后部分
	}
//	printf("%lld %lld: %lld\n", x, y, ans);
	return ans;
}
lld AllDigits(lld l, lld r) {
	int lenl, lenr;
	for (lenl = 0; pow10[lenl] <= l; ++ lenl);
	for (lenr = 0; pow10[lenr] <= r; ++ lenr);
	if (lenl == lenr) return (r - l + 1) * lenl; // 判掉特殊情况
	lld ans = (r - pow10[lenr - 1] + 1) * lenr + (pow10[lenl] - l) * lenl;
	for (int i = lenl + 1; i < lenr; ++ i) ans += pow10[i - 1] * 9 * i;
	return ans;
}
int main() {
	pow10[0] = 1;
	for (int i = 1; i <= 12; ++ i) pow10[i] = pow10[i - 1] * 10;
	for (int i = 0; i <= 9; ++ i) dp[1][i][i] = 1;
	for (int i = 1; i <= 12; ++ i)
		for (int j = 0; j <= 9; ++ j)
			for (int k = 0; k <= 9; ++ k)
				for (int l = 0; l <= 9; ++ l)
					if (l == k) dp[i + 1][k][l] += dp[i][j][l] + pow10[i - 1];
					else dp[i + 1][k][l] += dp[i][j][l]; // 前文所述的dp
	lld a, b;
	for(; ~scanf("%lld%lld", & a, & b); ) {
		if (!a && !b) return 0;
		memset(ans, 0, sizeof(ans));
		if (a > b) a ^= b ^= a ^= b;
		for (int i = 1; i <= 9; ++ i) ans[i] = calc(b + 1, i) - calc(a, i); // 差分
		ans[0] = AllDigits(a, b); for (int i = 1; i <= 9; ++ i) ans[0] -= ans[i]; // 算出所有的，减去其他的
		for (int i = 0; i <= 9; ++ i) printf("%lld ", ans[i]);
		puts("");
	}
}
```

---

## 作者：年华天地 (赞：0)

这题一看就是数位dp的裸题，我们需要维护什么呢？首先必须要有的一个pos表示到了第几位，二是这一位有没有限制也就是这一位的上限是多少，三是记录前导零，然后是记录当前要算的是哪一个数字(1~9)，最后我们要记录一下sum值来计算答案，要注意的是如果有前导零，sum是不能加的。

具体看代码吧
```
#include<cstdio>  
#include<cstring>  
#define int long long
using namespace std;  
long long l=1,r=1,dp[100][100];
int a[100];
long long ans;
long long dfs(int pos,int sum,bool lead,bool limit,int num)
{
	if(pos==-1)return sum;
	if(dp[pos][sum]!=-1&&!limit)return dp[pos][sum];
	long long tmp=0;
	int up=limit?a[pos]:9;
	for(int i=0;i<=up;i++)
	{
		tmp+=dfs(pos-1,sum+(i==num&&(lead||i)),i!=0||lead,limit&&i==a[pos],num);
	}
	if(lead&&!limit)dp[pos][sum]=tmp;
	return tmp;
}
long long solve(long long x,int num)
{
	int pos=0;
	while(x)
	{
		a[pos++]=x%10;
		x/=10;
	}
	memset(dp,-1,sizeof(dp));
	return dfs(pos-1,0,0,1,num);
}
signed main()
{
	
	while(1)
	{
		ans=0;
		scanf("%lld%lld",&l,&r);
		if (l==0&&r==0)break;
		if (l>r)
		{
			long long tmp=l;l=r;r=tmp;
			
		}
	
		for(int i=0;i<=9;i++)printf("%lld ",solve(r,i)-solve(l-1,i));
		printf("\n");
	}
	
}
```


---

