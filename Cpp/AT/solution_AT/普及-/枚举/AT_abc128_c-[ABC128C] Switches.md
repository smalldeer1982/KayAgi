# [ABC128C] Switches

## 题目描述

有 $n$ 个开关和 $m$ 个灯泡，每个开关都处于“开”和“关”状态中的一种。开关从 $1$ 到 $n$ 编号，灯泡从 $1$ 到 $m$ 编号。

$i$ 号灯泡连接着 $k_i$ 个开关：开关 $s_{i,1}$，$s_{i,2}$，...，$s_{i,k_i}$。当这些开关中，处于“开”状态的开关数量之和模 2 余 $p_i$ 时，这个灯泡就会被点亮。

有多少“开”和“关”的组合，可以点亮所有灯泡？

## 说明/提示

* $1\le N,M \le 10$

* $1 \le k_i \le N$

* $1 \le s_{i,j} \le N$

* $s_{i,a} \neq s_{i,b} (a \neq b)$

* $p_i$ 只能是 $0$ 或 $1$

* 上述所有值都是整数

#### 样例 1/样例 4

* 灯泡 $1$ 当以下开关里开着的总数是偶数时会亮：开关 $1$ 和 $2$。

* 灯泡 $2$ 当以下开关里开着的总数是奇数是会亮：开关 $2$。

开关 $1$ 和 $2$ 一共组成了四种组合：(开，开)，（开，关），（关，开）和（关，关）。其中只有（开，开）满足要求，所以输出 $1$。

#### 样例 2/样例 5

* 灯泡 $1$ 当以下开关里开着的总数是偶数时会亮：开关 $1$ 和 $2$。

* 灯泡 $2$ 当以下开关里开着的总数是偶数时会亮：开关 $1$。

* 灯泡 $3$ 当以下开关里开着的总数是奇数时会亮：开关 $2$。

为了点亮灯泡 $2$，开关 $1$ 必须是关着的；为了点亮灯泡 $3$，开关 $2$ 必须是开着的。但这样灯泡 $1$ 就不能被点亮了。所以，没有组合能让所有灯泡亮起来，故输出 $0$。

## 样例 #1

### 输入

```
2 2
2 1 2
1 2
0 1```

### 输出

```
1```

## 样例 #2

### 输入

```
2 3
2 1 2
1 1
1 2
0 0 1```

### 输出

```
0```

## 样例 #3

### 输入

```
5 2
3 1 2 5
2 2 3
1 0```

### 输出

```
8```

# 题解

## 作者：lkjzyd20 (赞：2)

### [题目传送门](https://www.luogu.com.cn/problem/AT4299)
___

### 思路

灯有两种形式：一种是开，一种是关，我们自然而然的想到了二进制：用 $1$ 代表开，用 $0$ 代表关。这样我们就可以用 `bool` 类型来存下一个灯的状态。

由于这道题数据范围小，$1 \leq N,M \leq 10$，我们可以考虑 Dfs。

怎么 Dfs 呢，可以考虑枚举每个灯泡，求出对应开关中灯的数量和，再直接算 $\%2$ 的值。

Dfs 枚举灯泡的时间复杂度是 $O(2^{n})$，每一次枚举灯泡中有 $m\times n$的循环，时间复杂度是 $O({n\times m})$，所以总的时间复杂度是 $O(2^nmn)$，极限情况为 $2^{10}\times10\times10=102400$，~~洛谷的评测姬跑的飞快！~~
___
### 代码如下
```cpp
//#include<bits/stdc++.h>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int INF=0x3f3f3f3f,MOD=1e9+7;
#define pu putchar
#define endl puts("")
//#define int __int128
//#define int long long
#define rep(i,l,r) for(int i=l;i<=r;++i)
#define per(i,r,l) for(int i=r;i>=l;--i)
#define me0(a); memset(a,0,sizeof a);
#define me3(a); memset(a,0x3f,sizeof a);
#define PII pair<int,int>
void read(int &n){char c,w=1;for(;48>c||c>57;c=getchar())
w=c==45?-1:1;for(n=0;47<c&&c<58;c=getchar())n=n*10+c-48;n*=w;
}void write(int x){if(x<0)pu(45),x=-x;char c[41],s=0;
for(;x;)c[s++]=x%10,x/=10;if(!s)pu(48);for(;s--;)pu(c[s]+48);
}void debug(int n){printf("\tdebug:\t"); write(n); pu('\t');}
const int MAXN=12;
int n,m;
int ans;
int num[MAXN];
int p[MAXN];
int v[MAXN][MAXN];
bool flag[MAXN];
// 进行 Dfs。
void dfs(int step){
	//如果 step 大于 n，说明已经选完了。 
	if(step>n){
		// 遍历灯泡。
		rep(i,1,m){
			int sum=0;
			rep(j,0,num[i]){
				// 如果开关亮，++sum。
				if(flag[v[i][j]]) {
					++sum;
				}
			}if(sum%2!=p[i]){// 判断满不满足条件。
				return;
			}
		}++ans;// 满足条件，++ans。
		return;
	}flag[step]=1; dfs(step+1); // 枚举灯泡的状态。
	flag[step]=0; dfs(step+1);
}main(){
	// 输入。
	read(n); read(m);
	rep(i,1,m){
		read(num[i]);
		rep(j,1,num[i]){
			read(v[i][j]);
		}
	}rep(i,1,m){
		read(p[i]);
	}dfs(1); // Dfs。
	write(ans); // 输出。
}
```

[$AC$ 记录(全洛谷第一最优解，欢迎打破)。](https://www.luogu.com.cn/record/85819803)

### 完结撒花 $\sim\sim\sim$

---

## 作者：阿丑 (赞：1)

[传送门](https://www.luogu.com.cn/problem/AT4299)

#### 题意：

* 有 $n$ 个开关，每个开关都只可能是“开”或“关”中的一种。

* 有 $m$ 个灯泡，第 $i$ 灯泡连接着若干个开关，当这些开关中“开”的数量模 $2$ 余 $p_i$ 时，可以电亮这个灯泡。

* 问有多少种“开”“关”的组合可以点亮所有灯泡。

* $1 \le n,m \le 10$

#### 分析：

注意到 $n \le 10$，可以考虑枚举。不妨设“开”状态为 $1$，“关”为 $0$，那么我们可以开一个数组 $a$ 来存每个开关的状态。

检查一个状态是否可行时，可以考虑枚举所有灯泡，每一个灯泡求出对应开关中“开”着的数量之和，再直接判断模 $2$ 的值。复杂度是 $\Theta(2^nmn)$，~~惊人地~~可行。

#### 思路：

1. 枚举开关状态。

2. 对于每一个状态，枚举每个灯泡，判断是否亮着。如果所有灯泡都亮着，答案加一。

---

具体实现参考代码。

---

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, ans, a[12];
int p[12];
int k[12], s[12][12];
void dfs(int x) {	//定义了一个行为 dfs，表示选择第 x 个灯泡的状态。 
	if(x>n) {	//如果 x 大于 n，那么说明已经选完了。 
		for(int i=1; i<=m; i++) {	//枚举灯泡 
			int sum=0;
			for(int j=1; j<=k[i]; j++) {
				if(a[s[i][j]]==1) sum++;	//如果开关开着，那么 sum++ 
			}
			if(sum%2!=p[i]) return;	//这表示有灯泡没亮，所以对答案没有贡献，直接返回上一层 
		}
		ans++;	//所有灯泡都开亮着，ans++ 
		return;
	}
	a[x]=0, dfs(x+1);	//枚举 x 的状态，并开始选下一个开关。 
	a[x]=1, dfs(x+1);
}
int main() {
	cin>>n>>m;	//输入部分。k,s,p 数组的意义如题。 
	for(int i=1; i<=m; i++) {
		cin>>k[i];
		for(int j=1; j<=k[i]; j++) {
			cin>>s[i][j];
		}
	}
	for(int i=1; i<=m; i++) cin>>p[i];
	dfs(1);	//选择第一个开关的状态。 
	cout<<ans<<endl;
	return 0;
}
```

抄代码可耻 qwq

---

##### update: 

5.27 修改了几处笔误。

---

## 作者：COsm0s (赞：0)

### 题目简述
+ 有 $n$ 个开关， $m$ 盏灯，每盏灯有 $k_i$ 个开关控制。
+ 对于第 $i$ 盏灯，它的开关开的数量模 $2$ 余 $p_i$ 时，这盏灯才会被打开。
+ 求有多少种开关“开”、“关”的方案，使得所有的灯都被打开。
+ $1≤n,m≤10$

### 思路

* 一盏灯只有两种状态，即“开”或“关”。那我们就可以设“开”为真，“关”为假，即 bool 类型的 true 和 false，这样我们可以用一个 bool类型的数组去保存状态。

* 再看数据范围，$n\leq10$，这是完全可以用 dfs 爆搜枚举开关状态，再依次判断各个灯泡的。

* 时间复杂度方面，dfs枚举是 $O(2^n)$，在dfs里枚举所有灯泡，每一个灯泡求出开关中“开”着的数量之和是 $O(m\times n)$,合在一起就是 $O(2^nmn)$，对于 $n=10$ 的数据来说，也是绰绰有余的。

### 代码
```cpp
#pragma GCC optimize(3)
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ll long long
inline int read() {//快读 
	int k = 0, m = 1;
	char ch = getchar();
	while(!isdigit(ch)) {
		if(ch == '-') m = -1;
		ch = getchar();
	}
	while(isdigit(ch)) {
		k = k * 10 + ch - 48;
		ch = getchar();
	}
	return k * m;
}
ll n, m, ans;//n,m如题意，ans表示方案数 
ll p[200];//p数组如题意 
ll sum[200], cnt[200][200];//sum数组表示每个灯泡有sum[i]个开关控制，cnt表示 sum[i]个开关 
bool f[200];//当前灯的状态 
void dfs(ll k) {
	if(k>n) {//选完了 
		for(int i=1; i<=m; i++) {
			ll s=0;
			for(int j=1; j<=sum[i]; j++) {
				if(f[cnt[i][j]]==1) ++s;
			}//枚举各个灯泡 
			if(s%2!=p[i]) return ;//如果有灯泡没好，直接结束 
		}
		++ans;//方案数++ 
		return ;
	}
	f[k]=1;//当前开着 
	dfs(k+1);
	f[k]=0;//当前关着 
	dfs(k+1);
}
signed main() {
	n=read(),m=read();
	for(int i=1; i<=m; i++) {
		sum[i]=read();
		for(int j=1; j<=sum[i]; j++)
			cnt[i][j]=read();
	}
	for(int i=1; i<=m; i++) p[i]=read();
	dfs(1);
	cout<<ans;
	return 0;
}
```


---

## 作者：luo_shen (赞：0)

**题意**  
其实题解里已经有大佬讲明白了，我就再复述一遍吧。  
- 有 $n$ 个开关， $m$ 盏灯，每盏灯有若干个开关控制。  
- 对于第 $i$ 只有当控制它的开关开的数量模 $2$ 余 $p_i$ 时，这盏灯才会被打开。
- 求有多少种开关“开”、“关”的方案，使得所有的灯都被打开。

**分析**  
开关只有“开”和“关”两种状态，那么我们就会~~很自然~~地想到每个数位只有 $0$ 和 $1$ 两种状态的二进制数了。

对于每一个不超过 $10$ 位的二进制数，第 $i$ 位代表着第 $i+1$ 个开关的“开”和“关”的情况。若该位为 $0$ 则代表该开关为“关”的状态，若该位为 $1$ ，则代表该开关为“关”的状态。

因为 $1\ \leq\ N,\ M\ \leq\ 10 $ ,所以我们可以直接暴力枚举。

**代码**
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,p[20],a[20][20],num[20],ans;
bool check(int x){//判断该二进制数所代表的开关状态能否打开所有灯
                                    //能就返回true,不能返回false
    for(int i=1;i<=m;i++){
        int s=0;
        for(int j=1;j<=num[i];j++){
            if(x&(1<<a[i][j])){//判断控制第i盏灯的第j个开关的“开”或“关”的情况
                s++;
            }
        }
        if(s%2!=p[i])return false;
    }
    return true;
}
int main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cin>>num[i];
        for(int j=1;j<=num[i];j++){
            cin>>a[i][j];
            a[i][j]--;//将开关编号指向对应的二进制数位
        }
    }
    for(int i=1;i<=m;i++){
        cin>>p[i];
    }
    for(int i=0;i<1<<n;i++){//暴力枚举并判断
              //因为最多只会有2^n种情况，所以我们从0枚举到2^n-1就行了
        if(check(i)){
            ans++;
        }
    }
    cout<<ans<<endl;
    return 0;
}
```

完结撒花

---

## 作者：Obviathy (赞：0)

## 解题思路：
由于本题数据范围比较小，所以，我们只需要枚举每一种开关的开闭情况，在通过遍历每一盏灯，来判断是否都被点亮，如果都被点亮，那么就统计一次。

显然，判断是否所有灯被点亮很好实现，只需要两层循环即可，代码如下：
```cpp
for(int j = 1;j <= m;j ++){//遍历每一盏灯
	int cnt = 0;
	f = 0;
	for(int t = 1;t <= k[j];t ++){
		if(pp[sk[j][t]]==1)cnt ++;//如果开关为开，计数器+1
	}
	if(cnt % 2 == p[j]){//如果打开的开关个数满足条件，标记一下
		f = 1;	
	}else break;
}
if(f==1)ans++;
```

那么，怎样去枚举开关的开闭情况呢？我们有两种思路：
- 第一种，递归调用。递归虽然很好，但对于一个不太善用递归的蒟蒻我来说，自认为比较麻烦，所以不再赘述。

- 第二种，二进制法。二进制是个好东西，所以下面我们好好说说二进制。

#### 二进制法：
通过题意，我们可以发现，开关的状态只有两种——开和关，那么，我们不妨定义开为 $1$，关为 $0$，与计算机中的通电断电相似。则 $n$ 个开关的开闭情况可以用一个 $n$ 位二进制表示（有点像状态压缩）。

举个例子：$5$ 个开关的一种开闭情况为：$01011$,其表示的就是第 $2,4,5$ 个开关打开，其余关闭。

所以，我们可以从 $0$ 开始循环，一直循环到二进制下的      $\begin{matrix}\underbrace{1111\cdots1111}\\n\end{matrix}$。 

#### 转换代码如下：
```cpp
int work(int x){//计算二进制下x个1的十进制数
	int s = 0;
	for(int i = 0;i < x;i ++){
		s = s*2+1;
	}
	return s;
}
void task(int x){//十进制转二进制
	memset(pp,0,sizeof pp);
	int i = n;
	while(x!=0){
		pp[i] = x % 2;
		x /= 2;
		i --;
	}
}
```
终于到完整代码了：
## code：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,ans;
int k[20],sk[20][20],p[20],pp[20];
int work(int x){
	int s = 0;
	for(int i = 0;i < x;i ++){
		s = s*2+1;
	}
	return s;
}
void task(int x){
	memset(pp,0,sizeof pp);
	int i = n;
	while(x!=0){
		pp[i] = x % 2;
		x /= 2;
		i --;
	}
}
int main(){
	cin >> n >> m;
	for(int i = 1;i <= m;i ++){
		cin >> k[i];
		for(int j = 1;j <= k[i];j ++)
			cin >> sk[i][j];
	}
	for(int i = 1;i <= m;i ++)
		cin >> p[i];
	int l = work(n);
	for(int i = 0;i <= l;i ++){
		task(i);
		int f = 0;
		for(int j = 1;j <= m;j ++){
			int cnt = 0;
			f = 0;
			for(int t = 1;t <= k[j];t ++){
				if(pp[sk[j][t]]==1)cnt ++;
			}
			if(cnt % 2 == p[j]){
				f = 1;	
			}else break;
		}
		if(f==1)ans++;
	}
	cout<<ans<<endl;
	return 0;
}


```
### 位运算优化：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,ans;
int k[20],sk[20][20],p[20],pp[20];
int main(){
    cin >> n >> m;
    for(int i = 1;i <= m;i ++){
        cin >> k[i];
        for(int j = 1;j <= k[i];j ++)
            cin >> sk[i][j];
    }
    for(int i = 1;i <= m;i ++)cin >> p[i];
    for(int i = 0;i <= (1<<n)-1;i ++){
        int f = 0;
        for(int j = 1;j <= m;j ++){
            int cnt = 0;
            f = 0;
            for(int t = 1;t <= k[j];t ++)if((i>>sk[j][t]-1)&1)cnt ++;
            if(cnt % 2 == p[j])f = 1;  
            else break;
        }
        if(f==1)ans++;
    }
    cout<<ans<<endl;
    return 0;
}
```



---

## 作者：Coros_Trusds (赞：0)

[更好的阅读体验](https://www.cnblogs.com/Coros-Trusds/p/15547583.html)

# 题目大意

有 $n$ 个开关和 $m$ 个灯泡，每个开关都处于“开”和“关”状态中的一种。开关从 $1$ 到 $n$ 编号，灯泡从 $1$ 到 $m$ 编号。

$i$ 号灯泡连接着 $k_i$ 个开关：开关 $s_{i,1},s_{i,2},\cdots,s_{i,k_i}$。当这些开关中，处于“开”状态的开关数量之和模 $2$ 余 $p_i$ 时，这个灯泡就会被点亮。

有多少“开”和“关”的组合，可以点亮所有灯泡？

# 题目分析

考虑 $\rm dfs$。

我们令 $1$ 表示“开”，$0$ 表示“关”，我们照常开一个 $\rm a$ 数组来记录枚举的状态。

如果状态枚举到最后了，已经枚举完一个完整的状态了，我们对枚举的状态进行一次检验即可。如果有一个灯泡不满足条件，那么直接回溯；如果全部满足条件，方案数加一并回溯继续枚举。

时间复杂度 $\operatorname{O}(2^n nm)$。

极限情况 $2^{10}\times 10\times 10=102400$，一秒内可以跑过。

# 代码

```cpp
//2021/11/13

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

#include <cstdio>

#include <climits>//need "INT_MAX","INT_MIN"

#define enter() putchar(10)

#define debug(c,que) cerr<<#c<<" = "<<c<<que

#define cek(c) puts(c)

#define blow(arr,st,ed,w) for(register int i=(st);i<=(ed);i++)cout<<arr[i]<<w;

#define speed_up() std::ios::sync_with_stdio(false)

namespace Newstd
{
	inline int read()
	{
		char c;
		bool flag=false;
		while((c=getchar())<'0' || c>'9')
		{
		    if(c=='-') flag=true;
		}
		int res=c-'0';
		while((c=getchar())>='0' && c<='9')
		{
		    res=(res<<3)+(res<<1)+c-'0';
		}
		return flag?-res:res;
	}
	inline void print(int x)
	{
		if(x<0)
		{
			putchar('-');x=-x;
		}
		if(x>9)
		{
			print(x/10);
		}
		putchar(x%10+'0');
	}
}

using namespace Newstd;

using namespace std;

const int ma=15;

int a[ma],p[ma],k[ma];

int mp[ma][ma];

int n,m;

int ans;

inline void dfs(int step)
{
	if(step>n)
	{
		for(register int i=1;i<=m;i++)
		{
			int tmp=0;
			
			for(register int j=1;j<=k[i];j++)
			{
				tmp+=a[mp[i][j]];
			}
			
			if(tmp%2!=p[i])
			{
				return;
			}
		}
		
		ans++;
		
		return;
	}
	
	a[step]=1;
	
	dfs(step+1);
	
	a[step]=0;
	
	dfs(step+1);
}

int main(void)
{
	n=read(),m=read();
	
	for(register int i=1;i<=m;i++)
	{
		k[i]=read();
		
		for(register int j=1;j<=k[i];j++)
		{
			mp[i][j]=read();
		}
	}
	
	for(register int i=1;i<=m;i++)
	{
		p[i]=read();
	}
	
	dfs(1);
	
	printf("%d\n",ans);
	
	return 0;
}
```

---

