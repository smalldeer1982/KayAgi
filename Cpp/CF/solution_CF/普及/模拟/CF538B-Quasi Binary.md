# Quasi Binary

## 题目描述

给出一个数 $n$，你需要将 $n$ 写成若干个数的和，其中每个数的十进制表示中仅包含 $0$ 和 $1$。

问最少需要多少个数。

## 样例 #1

### 输入

```
9
```

### 输出

```
9
1 1 1 1 1 1 1 1 1 
```

## 样例 #2

### 输入

```
32
```

### 输出

```
3
10 11 11 
```

# 题解

## 作者：OItby (赞：17)

> PS: 大家都好强呀，发的题解对于像我一样的蒟蒻一点都不友好呀（太长了，不容易看懂

蒟蒻今天发个简单的做法

很显然，最少需要多少个数取决于$max$(一个数的每一位)，下面举个例子：

$12321$，组成这个数的最大的数字是$3$，因此最少$3$个满足条件的数就可以构成$12321$，

分别为$11111$，$1110$，$100$

这样我们可以将每一位分别处理，这里我是从个位开始处理的

其实这也可以这样理解，$12321$是由$2321$转移过来的，同理，…

在结合代码其实不是很难

~~代码精简，码分丑陋，大佬勿喷~~

```cpp
#include<iostream>
#include<cstdio>
using namespace std;

int Ans,num[100];//其实这里定义10就够了，因为最多9个数就一定可以构成n

int main()
{
	int n,Res;
	scanf("%d",&n);
	for(int bit=1;bit<=n;bit*=10)
	{
		Res=(n/bit)%10;//每一位的数值
		Ans=max(Ans,Res);
		for(int i=1;i<=Res;++i) num[i]+=bit;
	}
	printf("%d\n",Ans);
	for(;Ans;--Ans) printf("%d ",num[Ans]);//倒序输出，从小到大
	putchar('\n');
	return 0;
}
```

---

## 作者：ioker (赞：3)

## [题目传送门](https://www.luogu.com.cn/problem/CF538B)

## 题目大意：
给出一个数 $n$，你需要将 $n$ 写成若干个数的和，其中每个数的十进制表示中仅包含 0 和 1。

问最少需要多少个数，及这个序列

思路：

把这个数拆成多个位，若当前位为 $m$，那么序列中 $m$ 个数字当前位都是 1 才满足条件，而最大的 $m$ 就是最少需要的个数，例如 $\texttt{114514}$，最大是 $\texttt{5}$，答案就是 5，分成 $\texttt{111111},\texttt{1101},\texttt{1101},\texttt{1101},\texttt{100}$。

具体可以看代码的注释：

```cpp
#include <stdio.h>
#include <ctype.h>
#include <algorithm>
#include <iostream>
using namespace std;
namespace stream {
template <typename T> inline T read() {
    T n = 0, m = 0;
    char c = getchar();

    while (!isdigit(c)) {
        m |= c == '-';
        c = getchar();
    }

    while (isdigit(c)) {
        n = (n << 1) + (n << 3) + c - '0';
        c = getchar();
    }

    return m ? -n : n;
}
template <typename T> inline void write(T n, char c) {
    int tot = 0, a[101];

    if (n < 0)
        n = -n, putchar('-');

    while (n)
        a[++tot] = n % 10, n /= 10;

    if (!tot)
        putchar('0');

    while (tot)
        putchar(a[tot--] + 48);

    if (c)
        putchar(c);
}
template <typename T> inline void print(T n, char c) {
    printf("%d", n);

    if (c)
        putchar(c);
}
}
using namespace stream;
#define read read<int>()
#define int long long
#define N 10001
int min(int n, int m) {
    return n > m ? m : n;
}
int max(int n, int m) {
    return n > m ? n : m;
}
int intabs(int n) {
    return n < 0 ? -n : n;
}
int power(int n, int m) {
    int ans = 1;

    while (m) {
        if (m & 1)
            ans = ans * n;

        m >>= 1;
        n = n * n;
    }

    return ans;
}
int n, a[N], m, ans, i;//i 是记录当前是第几位
signed main() {
    n = read, m = n;

    while (m) {//有 m 位
        int k = m % 10;//将他们分离，序列中要有 k 个数这一位为为1
        ans = max(k, ans);//更新答案

        for (int j = 1; j <= k; j++)
            a[j] += power(10, i);//序列中的 k 个数第 i 位变成 1，使它们之和是 k

        i++;//计数器加 1
        m /= 10;//准备处理下一位
    }

    write<int>(ans, 10);

    for (int j = 1; j <= ans; j++)
        write<int>(a[j], 32);

    putchar(10);
    return 0;
}
```

---

## 作者：Aw顿顿 (赞：3)

很显然的结论啊……

------

由于每一位最大是 $1$，所以对于一个数的某一位的值为 $a$，就至少需要 $a$ 个数来填满这个位置。由于一个填充位置的数同时可以多个位置是 $1$，因此答案就是所有位数中最大的那一位的值。

能够确认有几个数，那就每一位去构造了，每一位从前往后进行判断即可，由于 $1\le n\le 10^6$，时间可以接受。如果觉得描述有点抽象，那就看代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,res=-1,a[99]; 
int main(){
	cin>>n;
	for(int i=1;i<=n;i*=10){
		res=max(res,(n/i)%10);
		for(int j=1;j<=((n/i)%10);j++)
			a[j]+=i;
	}cout<<res<<endl;
	for(int i=1;i<=res;i++)
		cout<<a[i]<<' ';
	return 0;
}
```

---

## 作者：aakennes (赞：2)

感觉黄题评高了，但应该是入门构造题

# 题目大意：
把一个数$n$拆分成只由十进制下01组成的数，问最小个数并输出方案

# 思路：

类似填坑的思想，整体加减

记十进制下$01$组成的数为$01$数

原数每一位为坑的深度，$01$数中$0$代表不填，$1$代表填

那么问题就转化为有若干个坑，每次可以选取若干坑深度$-1$，问最少填坑次数使每个坑都为$0$

那地一个答案就很显然了，就是原数中每一位中最大的一位数

构造方案：每一个$01$数就是每一次填的坑的位置，即所有不为0的坑

举例：

$3$  $2$  $4$ 表示当前坑的深度分别为 $3$ $2$ $4$

第一次填1，2，3号坑，深度变为$2$ $1$ $3$，$01$数表示为：$111$

第二次填1，2，3号坑，深度变为$1$ $0$ $2$，$01$数表示为：$111$

第三次发现2号坑深度为$0$,只能填1，3号坑，深度变为$0$ $0$ $1$，$01$数表示为：$101$

第四次发现只能填1号坑，深度变为$0$ $0$ $0$，$01$数表示为：$001$

# 代码：
```
int x=read(),tot=0,ans=0,sum=0;
	while(x){
		a[++tot]=x%10;sum=max(sum,a[tot]);
		x/=10;
	}
	for(int i=1;i<=tot;++i)ans+=a[i];
	cout<<sum<<endl;
	while(1){
		int pre=0;
		for(int i=tot;i>=1;i--){
			if(!a[i]&&pre)putchar('0');
			if(a[i])putchar('1'),pre=1,a[i]--;
		}
		puts("");
		if(!pre)break;
	}
```

---

## 作者：what_can_I_do (赞：1)

[传送门](https://www.luogu.com.cn/problem/CF538B)

这道题一眼 dp。

这一题感觉跟[这一题](https://www.luogu.com.cn/problem/P1679)有点像。我们可以先预处理出所有只包含 $0$ 和 $1$ 且不大于 $n$ 的数，存在数组 $v$。接下来就是 dp。我们先想好 $dp_i$ 表示什么，很容易想到，$dp_i$ 表示加到 $i$ 时使用的数的最少数量。这一题就是一个选与不选的问题。是否要选择加上 $v_j$ 这个数来使其从 $i-v_j$ 变为 $i$，代价为 $1$。那么这一题的状态转移方程就可以推出了：$dp_i=min(dp_i,dp_{i-v_j}+1)$。接下来想 $dp$ 数组的初始状态。由于是最小值，所以先把 $dp_i$ 设成一个很大的数。接下来我们想，$0$ 怎么加才能实现变为 $0$，很明显，不用加，所以 $dp_0=0$。那么最后要输出的答案呢，明显的，是 $dp_n$。

接下来想怎么样实现输出构造方案。可以用一个 `vector<int> pe[1000010]` 来实现。其中每个 $pe_i$ 表示加到 $i$ 的最优方案。为什么不用数组，因为数组的方案转移要 $O(n)$ 的时间复杂度，但是 vector 只要 $O(1)$，只需要写成 `pe[i]=pe[i-v[j]]` 就行了。

现在我们要稍微改一下状态转移方程。我们要把 `dp_i=min(dp_i,dp_{i-v_j}+1)` 改成 `if(dp[i]>dp[i-v[j]]+1)` 接下来再跟上 `dp[i]=dp[i-v[j]]+1;`，然后再将方案转移，`pe[i]=pe[i-v[j]]`，最后在后面放入新的选择 `pe[i].push_back(v[j])` 就行了。

还有，预处理就不用我讲了吧，直接模拟。

# CODE:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,v[200],l=0,dp[1000010]={0};
vector<int> pe[1000010];
int main()
{
	scanf("%d",&n);
	for(register int now=0;now<=n;)
	{
		v[l]=now,l++;
		now++;
		int s=1;
		while((now%(int(pow(10,s))))/(int(pow(10,s-1)))==2) s++,now=now-2*int(pow(10,s-2)),now+=int(pow(10,s-1));
	}
	l--;
	for(register int i=1;i<=n;i++) dp[i]=999999999;
	for(register int i=0;i<=n;i++)
		for(register int j=0;j<=l;j++)
			if(i>=v[j])
				if(dp[i]>dp[i-v[j]]+1)
				{
					dp[i]=dp[i-v[j]]+1;
					pe[i]=pe[i-v[j]];
					pe[i].push_back(v[j]);
				}
	printf("%d\n",dp[n]);
	for(register int i=0;i<=pe[n].size()-1;i++) printf("%d ",pe[n][i]);
	return 0;
}
```

---

## 作者：alvis (赞：1)

## 题意
给出一个数 $\text{n}$，输出一些由 $\text{1}$ 和 $\text{0}$ 所组成的数字，使这些数字之和等于 $\text{n}$ ，并使得数字最少，并且输出数字个数。

## 思路
真·思维题。

假定给出一个数 $\text{n}$。由题意可知，最少输出的数字个数一定为 $\text{n}$ 中的最大数。

如何解释？

假设当前位上的数为 $\text{k}$。

显而易见，我们把当前位置的值~~瞎搞~~处理完毕（即把其变为$\text{0}$ ）的最优方案一定是**选择 $\text{1}$，即直接减去 $\text{1}$。**而不是从当前位置的上一位加上 $\text{10}$ 次 $\text{1}$来进位。

因此，最少输出的数字个数，一定是这个 $\text{n}$ 中的最大值（即最多减几次 $\text{1}$）。

那么我们基本已经搞清楚了这道题的思路：记录每位数上的值  $\operatorname{k_i}$，并进行整合输出。

## 代码

```cpp
#include <iostream>
using namespace std;
int n;
int dep[100001]={};
int main() {
	cin >> n;
	int t=0;
	//记录n每位的最大值
	int num_loc = 0;
	while (n != 0){
		//记录每位上的数值
		dep[++t] = n%10; 
		if(dep[t] > num_loc) num_loc = dep[t];
		n/=10;
	}
	cout << num_loc << endl;
	for(int i=1;i <= num_loc;i ++){
		int k = 0;
		//进行整合输出（由于存数时的顺序，现在我们要倒序输出）
		for(int j = t;j >= 1;j --){
			if(dep[j] != 0){
				k = 1;
				cout << 1;
				dep[j] --;
			}else if(k) cout << 0;
		}
		cout << " ";
	}
	return 0;
}
```


---

## 作者：Bandit (赞：1)

**很荣幸成为Luogu第一位A了这道(shui)题的人**


题解如下(含详细注释）

```cpp
// <CF538B.cpp> 2019/07/23 11:08:48
// This file is created by Bandit.
// Copyright (C) 2019 S.F.L.S , Inc.
// I don't know what this program is. 
#include<bits/stdc++.h>
using namespace std;
#define N 1000001
#define ll long long

inline int read()  //快读 初学者可视作cin>> 
{
    int x=0,f=1; char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}

int n;
int ans;
int q[N];
int a[N];

int makeQb(int x)  //构造当前最优01串 
{
    int Qb=0;
    int cnt=0;  //cnt记录01串长度 
    while (x>0)
    {
       if (x%10>=1)  //如果当前数位>=1 则有01串对应数位是1 否则是0 
         q[++cnt]=1;
       else
         q[++cnt]=0;  
        x/=10;
    }
    int base=1;  //通过base变量模拟高低位 
    for (int i=1;i<=cnt;i++)
    {
        if (q[i]) Qb+=base;  //若当前01串数位是1 累加入Qb中 
        base*=10;  //base自乘10 为处理下一位做准备 
    }
    return Qb;  //返回最优01串 
}

int main()
{
    n=read();
    while (n!=0)
    {
        a[ans+1]=makeQb(n);   //记录取到的01串 注意下标是ans+1 
		n-=makeQb(n);  //n减去当前01串 
        ans++;  //ans累加记录01串累计个数 
    }
    cout<<ans<<endl;  //先输出01串总个数 
    for (int i=ans;i>1;i--)  //倒序输出各01串(由题意) 
      cout<<a[i]<<" ";
    cout<<a[1]<<endl;
    return 0;
}
```



---

## 作者：Texas_the_Omertosa (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF538B)

### 0x01 思路

我们可以先想想：如果一个数要分解为若干个只由 0 或 1 组成的数，那么所有分解出来的数的个位和不就是被分解数的个位吗？分解出来的数的十位和不就是被分解数的十位吗？分解出来的数的百位和不就是被分解数的百位吗……以此类推

那么分解出来数的数量就是被分解数所有位中最大的数。而对于每一个分解出来数，只要被分解数此位仍大于 0，那就把此位变为 1 就行了。

我实现的方法是：控制变量 `i` 在小于被分解数 `n` 时不断乘 `10`，储存分解出来的数的数量的变量 `answer` 看 `(n/i)%10` 是否大于 `answer` ，是则更新，否则跳过。然后把储存答案数组 `ans` 中下标为 `1` 到 `(n/i)%10` 加上 `i` ，最后排序输出（其实也可以倒序输出）就可以了。

### 0x02 AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,answer;
int ans[11];
int main()
{
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin>>n;
  for(int i=1;i<=n;i*=10)
    {
      answer=max(answer,(n/i)%10);
      for(int j=1;j<=(n/i)%10;j++)
        {
          ans[j]+=i;
        }
    }
  sort(ans+1,ans+answer+1);
  cout<<answer<<'\n';
  for(int i=1;i<=answer;i++)
    {
      cout<<ans[i]<<' ';
    }
  cout<<'\n';
  return 0;
}
```

---The End of the Solution---

---

## 作者：happy_dengziyue (赞：0)

### 1 思路

##### 1.1 大体思路

输入 $n$ 后，我们先把 $n$ 的每一位存在数组里。

然后循环，如果遇到一位上的数不为 $0$，就记录进去，并且让这一位数自减。直到全为 $0$。

然后输出就可以了。

##### 1.2 示例

我们以 $n=12324$ 为示范。

首先，设**从右到左**第 $i$ 位的数为 $a[i]$。

第一步：

$$a[1......5]=4,2,3,2,1$$

发现所有位置上的数都大于 $0$，于是答案增加一个：$11111$。

第二步：

$$a[1......5]=3,1,2,1,0$$

发现 $1$ 到 $4$ 位大于 $0$，于是答案增加一个：$1111$。

第三步：

$$a[1......5]=2,0,1,0,0$$

发现第 $1$ 位和第 $3$ 位大于 $0$，于是答案增加一个：$101$。

第四步：

$$a[1......5]=1,0,0,0,0$$

仅有第 $1$ 位大于 $0$，于是答案增加一个：$1$。

修改后，$a$ 中全为 $0$。结束。

综上所述：

对于 $n=12324$，最少需要 $4$ 个数，可以表示为：

$$12324=11111+1111+101+1$$

### 2 代码与记录

```cpp
#include<cstdio>
using namespace std;
int n;//原数
int a[12];//十进制表示
int ai=0;//下标
int cnt=0;//分解数
int ans[1000002];//答案
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF0538B_1.in","r",stdin);
	freopen("CF0538B_1.out","w",stdout);
	#endif
	scanf("%d",&n);
	for(int k=n;k;k/=10)a[++ai]=k%10;
	for(int k;;){
		k=0;
		for(int i=ai;i>=1;--i){
			k*=10;
			if(a[i]){
				++k;
				--a[i];
			}
		}
		if(!k)break;
		ans[++cnt]=k;
	}
	printf("%d\n",cnt);
	for(int i=cnt;i>=1;--i)printf("%d ",ans[i]);
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/57683805)

By **dengziyue**

---

## 作者：Vocanda (赞：0)

# 题目
[题目链接](https://www.luogu.com.cn/problem/CF538B)


# 分析
作为一道思维题，算是挺好想的了。

题意很好理解，把给定的一个数拆分成许多每一位只有 $0$ 和 $1$ 的数，方案肯定是唯一的，因为原数上每一位的值是固定的。第一问的能拆成最少多少个数，我们贪心的想一下，肯定是能取就取，所以第一问答案就是每一位中最大的那个。那么我们接下来考虑如何确定每个值。

假设一开始当前数是 $n$ 位，那么一定至少有一个由 $n$ 个 $1$ 组成的数，这个数有几个呢，容易得到应该是这个数 $n$ 位中最小的那一位的数。

举个例子，比如 $489198$ ，这里边最小一位的值是 $1$ ，那么 $6$ 位的就只有 $1$ 个，然后用贪心的思想，一位一位地取，直到最后取成 $0$ ，把整个数每一位存到数组里，如果当前位大于 $1$ ，就取，否则输出 $0$ ，注意一下判前导 $0$ 即可。

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 10;
int jl[maxn];
int main(){
	int n;
	scanf("%d",&n);
	int ans1 = 0;
	int x = n;
	int cnt = 0;
	int tot = 0;
	while(x){//把每一位的数存到数组里
		ans1 = max(ans1,x % 10);//最大的一位一定是能拆成多少个数
		cnt += x % 10;
		jl[++tot] = x % 10;
		x /= 10;
	}
	printf("%d\n",ans1);
	while(cnt){//当这个数还有没被取完的
		bool jud = 0;
		for(int i = tot;i >= 1;--i){//从高到低枚举每一位
			if(jl[i])putchar('1'),cnt--,jl[i]--,jud = 1;//判前导0
			else if(jud) putchar('0');
		}
		putchar(' ');
	}
	return 0;
}
```

---

## 作者：Gary818 (赞：0)

啊这  
名副其实思维题？  
前几天写了  
今天同机房大佬要个思维题  
然后随手来写一下  


第一问很显然也好理解吧  
答案为**各个数位上的数字的最大值**  
第二问的话  
只需要按照数位扫一遍  
每次当前数位上有值的话，贡献为当前数位乘上一  
然后给这个数位上的贡献$-1$直到所有数位为$0$  
想明白思路，代码实现没有任何难点，非常短  
博主在分离每个数位的时候用了一下类似数位$dp$的思想  
不过随便搞一下就行  
看个人习惯了

```cpp
#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;

inline int read(){
    int x = 0, w = 1;
    char ch = getchar();
    for(; ch > '9' || ch < '0'; ch = getchar()) if(ch == '-') w = -1;
    for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + ch - '0';
    return x * w;
}

int a[15], ans, res[15];
int cnt, id;

inline void change(register int x){
    while(x){
        a[++cnt] = x % 10;
        x /= 10;
    }
    reverse(a + 1, a + 1 + cnt);
}

signed main(){
	register int n = read();
	change(n);
	for(register int i = 1; i <= cnt; i++) ans = max(ans, a[i]);
	cout << ans << '\n';
	while(1){
		bool flag = 1;
		for(register int i = 1; i <= cnt; i++) if(a[i] != 0) flag = 0;
		if(flag) break;
		register int tmp = 0;
		for(register int i = 1; i <= cnt; i++){
			tmp *= 10;
			if(a[i]) tmp += 1, a[i]--;
		}
		res[++id] = tmp;
	}
	for(register int i = 1; i <= id; i++)
		cout << res[i] << " ";
	puts("");
	return 0;
}
```

---

## 作者：MrFish (赞：0)

#### 主要思路：最少需要的数为这个数最大的数字，例如：1532最大的数字就为5。然后从头枚举，如果该为大于0，则输出1，否则如果已经输出过1的话，就输出0。
奉上我的AC代码：
```cpp
#include<iostream>
#include<cstring>
#include<cmath>

using namespace std;

int num[10]; //数字，按位存储。

int main()
{
    int ans=-1;
    string s;
    cin>>s;
    for(int i=0;i<s.size();i++)
    {
        num[i]=s[i]-'0';
        ans=max(ans,num[i]); //得到最大的数字
    }
    cout<<ans<<endl; //先输出ans，因为后面要变它。
    bool flag;
    while(ans--)  //枚举
    {
        flag=false; //已经输出过1吗？
        for(int i=0;i<s.size();i++)
        {
            if(num[i]>0)  //大于0
            {
                flag=true;  //flag改为true
                cout<<1;   //输出1
                num[i]--;  //这一位减一
            }
            else
            {
                if(flag)  //已经输出过1了
                {
                    cout<<0;  //输出0
                }
            }
        }
        cout<<' ';  //一个空格
    }
    return 0;
}

```
拜拜！

---

