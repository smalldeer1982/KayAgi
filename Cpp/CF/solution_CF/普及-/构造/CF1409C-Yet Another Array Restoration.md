# Yet Another Array Restoration

## 题目描述

We have a secret array. You don't know this array and you have to restore it. However, you know some facts about this array:

- The array consists of $ n $ distinct positive (greater than $ 0 $ ) integers.
- The array contains two elements $ x $ and $ y $ (these elements are known for you) such that $ x < y $ .
- If you sort the array in increasing order (such that $ a_1 < a_2 < \ldots < a_n $ ), differences between all adjacent (consecutive) elements are equal (i.e. $ a_2 - a_1 = a_3 - a_2 = \ldots = a_n - a_{n-1}) $ .

It can be proven that such an array always exists under the constraints given below.

Among all possible arrays that satisfy the given conditions, we ask you to restore one which has the minimum possible maximum element. In other words, you have to minimize $ \max(a_1, a_2, \dots, a_n) $ .

You have to answer $ t $ independent test cases.

## 样例 #1

### 输入

```
5
2 1 49
5 20 50
6 20 50
5 3 8
9 13 22```

### 输出

```
1 49 
20 40 30 50 10
26 32 20 38 44 50 
8 23 18 13 3 
1 10 13 4 19 22 25 16 7```

# 题解

## 作者：EternalHeart1314 (赞：4)

### [题目传送门](https://www.luogu.com.cn/problem/CF1409C)

# 思路

令 $s$ 为 $x$ 和 $y$ 的差，则我们要找到一个尽可能大的 $ans$，满足 $s\bmod ans=0,s\div ans+1\le n$，这个 $ans$ 即为 $a_2-a_1$。

得到了序列中两两的差后，便可以构造出 $a$ 序列了。

# Code
```
#include<bits/stdc++.h>
using namespace std;

int t, n, x, y, s, ans;

int main() {
	cin >> t;
	while(t --) {
		cin >> n >> x >> y;
		s = abs(x - y);
		for(int i(1); i <= s; ++ i) {
			if(!(s % i) && s / i + 1 <= n) {
				ans = i;
				break;
			}
		}
		for(int i(min(x, y)), ed(max(x, y)); i <= ed; i += ans) {
			cout << i << ' ';
			-- n;
		}
		s = min(x, y);
		while(n --) {
			if((s -= ans) <= 0) {
				++ n;
				break;
			}
			cout << s << ' ';
		}
		s = max(x, y);
		while(n -- > 0) {
			cout << (s += ans) << ' ';
		}
		cout << '\n';
	}
	return 0;
}
```

### 珍惜生命，远离抄袭

---

## 作者：Carotrl (赞：4)

### 题意：

> 构造一个 $n$ 个数的序列 $a$，使得 $x,y$ 在这个 序列中且排序后 $a_2-a_1=a_3-a_2=...=a_n-a_{n-1}$。请问当 $\max(a_1,a_2,a_3,...,a_n)$ 最小时，这个序列是什么样的，可以任意顺序输出。

### 题解：

由于序列中要包含 $x,y$ 两个元素，还要求是等差数列，所以直接从大到小枚举从 $x$ 到 $y$ 共有多少个元素，找出差值，并依次输出。

如果元素个数不到 $n$ 个，便由此公差从 $x$ 继续向下输出，直到满 $n$ 个元素或到 $1$ 为止。

如果元素个数还不满 $n$ 个，便由此公差从 $y$ 继续向上输出，直到满 $n$ 个元素即可。

可以保证这种情况使得$\max(a_1,a_2,a_3,...,a_n)$ 最小。

### 代码：

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<string> 
using namespace std;
int t,n,x,y;
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d%d%d",&n,&x,&y);
		int a=y-x;
		for(int i=n;i>=1;i--){
			if(a%(i-1)==0){
				int p=a/(i-1),j;
				for(j=1;j<=n;j++){
					if(x+(j-1)*p>y)break;
					printf("%d ",x+(j-1)*p);
				} 
				j--;
				j=n-j;
				for(int k=x-p;k>0&&j;k-=p)printf("%d ",k),j--;
				for(int k=y+p;j;k+=p)printf("%d ",k),j--;
				break;
			}
		}
		printf("\n");
	}
}
```


---

## 作者：huyangmu (赞：4)

因为数据很小，最大只有 $50$，所以可以直接枚举首项和公差，通过公式计算出最后一项，如果最后一项比目前答案小，就更新答案，并记录首项和公差。

但还要判断首项和公差是否满足要求，设首项为 $i$，公差为 $j$，则 $i$ 到 $x$ 的项数为 $(x - i) \div j + 1$，$i$ 到 $y$ 的项数为 $(y - i) \div j + 1$。如果这两个数为小数或小于 $0$ 或超过 $n$ 就不可以。

### AC Code
```cpp

#include <bits/stdc++.h>
#define int long long 
using namespace std;
int T,n,x,y;
bool check (int i,int j){
	double tmp = (x - i) * 1.0 / j;
	if (floor(tmp) != tmp || (int)(tmp) > n - 1 || (int)(tmp) < 0){
		return 0;
	}
	tmp = (y - i) * 1.0 / j;
	if (floor(tmp) != tmp || (int)(tmp) > n - 1 || (int)(tmp) < 0){
		return 0;
	}
	return 1;
}
signed main (){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin >> T;
	while (T --){
		cin >> n >> x >> y;
		int maxn = 0x3f3f3f3f, sum = 0, sum2 = 0;
		for (int i = 1; i <= 51; ++i){
			for (int j = 1; j <= 51; ++j){
				if (check(i,j) && maxn > i + (n - 1) * j){
					maxn = i + (n - 1) * j;
					sum = i;
					sum2 = j; 
				}
			}
		}
		for (int i = sum; i <= maxn; i +=sum2) cout << i << ' ';
		cout << '\n'; 
	}
	return 0;
}


---

## 作者：Z_AuTwT (赞：3)

## 形式化题意
求出长度为 $n$ 一个等差数列，使得 $x$ 与 $y$ 处于这个等差数列内，且要使得 $\max_{i=1}^n a_i$ 最小。
## 思路
既然是等差数列，就要先寻找公差。

那公差怎么找呢？

可以发现如果要包含 $x$ 与 $y$ 的话，这个公差的值一定要是 $x-y$ 的因数。

找到这个合适的公差之后，因为要求最小所以先往小的靠。
## 代码：
```c++
#include<bits/stdc++.h>
using namespace std;
int main(){
    int t;
    cin>>t;
    while(t--){
        int n,x,y;
        cin>>n>>x>>y;
        int cz=y-x;//求差值
        for(int i=1;i<=y;i++){//枚举因子
            if(cz%i==0&&cz/i+1<=n){//判定是否合法(注意有可能x~y在这个公差下就已经超过了n)
                int dt=y;
                while(dt>0&&n){//先往小数找
                    cout<<dt<<" ";
                    n--;
                    dt-=i;
                }
                if(n){//如果往小不足n个
                    int dt1=y+i;
                    while(n--){//往大数占位
                        cout<<dt1<<" ";
                        dt1+=i;
                    }
                }
                break;
            }
        }
        cout<<"\n";
    }
}
```
### 无注释版:
```c++
#include<bits/stdc++.h>
using namespace std;
int main(){
    int t;
    cin>>t;
    while(t--){
        int n,x,y;
        cin>>n>>x>>y;
        int cz=y-x;
        for(int i=1;i<=y;i++){
            if(cz%i==0&&cz/i+1<=n){
                int dt=y;
                while(dt>0&&n){
                    cout<<dt<<" ";
                    n--;
                    dt-=i;
                }
                if(n){
                    int dt1=y+i;
                    while(n--){
                        cout<<dt1<<" ";
                        dt1+=i;
                    }
                }
                break;
            }
        }
        cout<<"\n";
    }
}
```
~~第一次写题解，求过。~~

---

## 作者：xuchuhan (赞：3)

## 形式化题意

不难发现，题意可以转化为如下描述。

> 给你三个数 $n,x,y$，请构造出一个 $\max_{i=1}^n a_i$ 最小的等差数列 $a_1,a_2,\cdots,a_n$（$1 \leq a_i \leq 10^9$），使得 $x,y \in \{a_i\}$。

## 思路

要想让 $x,y \in \{a_i\}$，那么等差数列 $a$ 的公差一定为 $x$ 和 $y$ 的差的因数。

枚举所有的 $y-x$ 的因数，即枚举可能的公差，若存在以当前数为公差，且长度为 $n$ 的等差数列，则直接输出以当前数为公差，长度为 $n$，且 $\max_{i=1}^n a_i$ 最小的数列。这个数列一定是所有合法序列中 $\max_{i=1}^n a_i$ 最小的。

如何判断是否存在以当前数为公差，且长度为 $n$ 的等差数列呢？设当前的公差为 $d$，且因为要包含 $x,y$，所以 $a$ 中至少有 $cnt=\frac{y-x}{d}+1$ 个元素。若 $cnt>n$，则无法构造。

若可以构造，则求出数列 $a$ 的起点最少是几，然后输出起点及其之后 $n$ 个数即可。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T;
signed main(){
	cin>>T;
	while(T--){
		int n,x,y;
		cin>>n>>x>>y;
		int t=y-x; 
		vector<int>v;
		for(int i=1;i<=t;i++)
			if(t%i==0)
				v.push_back(i);//枚举因数 
		for(int i=0;i<v.size();i++){
			int cnt=t/v[i]+1;
			if(cnt>n)
				continue;
			//不符条件 
			int ans=min(n-cnt,x/v[i]);//ans:x前最多有几个数
			int st=x-ans*v[i];//算出起点 
			if(st==0)
				st+=v[i];
			//注意：题目要求1<=a[i]<=1e9,所以起点不能为0,应该再加上一个公差 
			int k=v[i];
			for(int i=st;i<=st+(n-1)*k;i+=k)
				cout<<i<<" ";
			//输出合法序列 
			break;
		}
		cout<<"\n";
	}
	return 0;
}
```

---

## 作者：Suuon_Kanderu (赞：1)

这题还是比较简单的，算是个模拟。

做这种题最重要的是思路清晰，现在真是颓废刷这种毫无思维含量的题还要 WA 一次。

思路：

1. 题目要求一个等差数列，我的思路是枚举公差。因为 $x,y  \in {a_i}$ ，公差的取值范围是 $[1 , y - x]$ ， 超过 $y-x$ 肯定无法同时包含 $x$ 和 $y$。
2. 如果公差 $d$ 不是 $y-x$ 的因数，显然不满足条件。直接排除。然后我们假设现在的序列为  $ x ~,~ x + d ~,~ x + 2 \cdot d \cdots ~, ~y~$,此时序列长度 $len$ 为 $\frac{y-x}  d + 1$。
3. 如果此时的 $len$ 已经超过了 $n$ 项，直接跳过。

3. 此时分情况讨论哪些满足条件，并记录答案：

   1. 按照贪心，我们先向左边扩展一些,变成 $\cdots x - 2 \cdot d ~,~ x-d,~ x ~,~ x + d ~,~ x + 2 \cdot d \cdots ~, ~y~$。发现左边最多能够扩展 $\frac{x-1}{d}$ 个数。如果只要左边扩展或者不扩展就有 $\mathcal {n}$ 项，即 $len = \frac{y-x}  d + 1 + \frac{x-1}{d} \ge n$。此时数列中的最大值为 $y$。
   2. 如果还不够，我们只好向右扩展了。向右扩展 $n-len$项。此时数列中最大值为 $y + (n - cnt) \cdot d $ 。
   
代码就很简单了，理顺逻辑即可，细节较多。

```cpp
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <cstring>
typedef long long ll;
const int N = 200000+100;
void work(int x , int y , int n) {
	int ans = 0x7fffffff , d;
	for(int i = 1; i <= y - x; i++) {
		if(!((y - x) % i == 0))continue;
		int cnt = 0;//即为 len
		cnt += (y - x) / i + 1;
		if(cnt > n)continue; 
		cnt += (x - 1) / i;
		if( cnt >= n) {
			if(y < ans)ans = y , d = i;			
		}else {
			if(y + (n - cnt) * i < ans)
				ans = y + (n - cnt) * i , d = i;
		}
	}
	for(int i = 1; i <= n; i++)printf("%d " , ans) , ans -= d;
	puts("");
}
int main() {
	int t;scanf("%d" , &t);
	while(t--) {
		int x , y , n;
		scanf("%d%d%d" , &n , &x , &y);
		work(x , y , n);
	}return 0;
} 
```


---

## 作者：江户川·萝卜 (赞：1)

### 题意
求一个长度为N的、且包含x,y的等差数列，且使数列的最大值最小。

### 解法
设等差数列公差为 $k$ ，则x,y可表示为：
$$x=ik+a_1$$
$$y=jk+a_1$$
$$y-x=(j-i)k$$
说明 k 是 $y-x$ 的因数。

因为该数列的最大值最小不能低于y（因为该数列是一定有y的），所以我们要把数列尽量压缩在y以下，所以要让公差尽量小。

但是公差也不能太小，当$\dfrac{(y-x)}{k}>n-1$ 时，剩下$n-2$个数就不足以填x,y之间的空，这样整个数列就不是一个等差数列了。

所以枚举$\dfrac{y-x}{k}$，找到在 $[1,n-1]$ 区间内最大的且能将$y-x$整除的值。

接下来就是输出问题了，因为顺序无关紧要，所以怎么输出都行。~~（顺着输，倒着输，跳着输，随机输都行~~

首先输出x和y，再输出 $(x,y)$ 区间内的，然后输出 $<x$ 的，最后输出 $>y$ 的。用`tot`控制总数，每输出1个`tot--`,`tot<=0`时停止输出。

下面是代码。
```cpp
#include<cstdio>
#include<iostream>
using namespace std;
int t,n,x,y,c,maxx,tot;
int main(){
	scanf("%d",&t);
	for(int k=1;k<=t;k++){
		scanf("%d%d%d",&n,&x,&y);
		c=y-x;
		for(int i=n-1;i>=1;i--)
			if(c%i==0){
				maxx=c/i;
				break;
			}
		tot=n;
		c=c/maxx;
		printf("%d %d",x,y);//输出x,y
		tot-=2;
		for(int i=x+maxx;i<=y-maxx;i+=maxx,tot--) printf(" %d",i);//输出(x,y)区间内的
		for(int i=x-maxx;i>0&&tot>0;i-=maxx,tot--) printf(" %d",i);//输出<x的
		for(int i=y+maxx;tot>0;i+=maxx,tot--) printf(" %d",i);//输出>y的
		printf("\n");
	}
	return 0;
}
```


---

## 作者：LeavingZzz (赞：1)

## $\mathsf{Solution\space For \space CF1409C}$  
### $\mathsf{Description}$  
给出一个等差**正项**整数数列的两项（位置未定），找出所有可能的数列中最大值最小的一种数列并输出。
### $\mathsf{Solution}$  
由于是个等差数列，且给出的两项 $x<y$ ，如果确定了 $x,y$ 的位置 $j,i$，那么这个数列的公差 $d=\dfrac{y-x}{i-j}$，由于数列是整数数列，所以必须满足 $(i-j)\mid(y-x)$，这里假设 $j<i$，那么这个数列的最小项即为 $a_1=x-d\times(j-1)$，必须保证这一项为正。  

这里直接枚举 $x,y$ 的位置 $j,i$，倒序枚举 $i$ 正序枚举 $j$，如果有解了可以立即记录首项 $a_1$ 及公差 $d$ 并且退出枚举（贪心的思想，保证较大的 $y$ 尽量靠后，这样最大值会相对较小，确定 $y$ 的位置之后最小化 $d$ 所以要把 $x$ 放在尽量前的位置）  
### $\mathsf{Code}$  
```
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cctype>
using namespace std;
typedef long long LL;
const int maxn=57;
int T;
int N,x,y;
int a1,d;
int A[maxn];
void solve()
{
    for(int i=N;i>0;i--)
    {
        for(int j=1;j<i;j++)
        {
            if((y-x)%(i-j)) continue;//公差必须为整数
            d=(y-x)/(i-j);
            a1=x-d*(j-1);
            if(a1>0) return ;//首项必须大于0才是合法解
        }
    }
}
int main()
{
    #ifndef ONLINE_JUDGE
    freopen("1.in","r",stdin);
    #endif
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d%d",&N,&x,&y);
        solve();
        A[1]=a1;
        printf("%d",A[1]);
        for(int i=2;i<=N;i++)
            printf(" %d",A[i]=A[i-1]+d);//输出等差数列
        puts("");
    }
    return 0;
}
```  


---

## 作者：jun头吉吉 (赞：1)

## 题意
给定$n,x,y(y>x)$，请构造出一个序列$a_1,a_2,\ldots,a_n$，使$x,y\in\{a_i\}$，且排序后$a_2-a_1=a_3-a_2=\ldots=a_n-a_{n-1}$，并且使$\max_{i=1}^na_i$最小，请求出这个序列

## 题解

由于 $2\le n\le50,1 \le x < y \le50$，那肯定是枚举$a_2-a_1=a_3-a_2=\ldots=a_n-a_{n-1}$啊

那么假如我们现在找到了$a_2-a_1=a_3-a_2=\ldots=a_n-a_{n-1}=i$，那么我们先不停给$x$减去$i$直到它还是正整数，得到了$x^\prime$，那么可以进行分类讨论

- 若$y-x^\prime\le (n-1)\times i$，那么就从$x^\prime$开始向后不断加
- 否则，就从$y$开始不断减少

在这个过程中不断更新最小值就可以了

## 代码
```cpp
 //#pragma GCC optimize(3,"Ofast","inline")
#include<bits/stdc++.h>
namespace in{
	char buf[1<<21],*p1=buf,*p2=buf;
	inline int getc(){
	    return p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++;
	}
	template <typename T>inline void read(T& t){
	    t=0;int f=0;char ch=getc();
	    while (!isdigit(ch)){
	        if(ch=='-')f = 1;
	        ch=getc();
	    }
	    while(isdigit(ch)){
   	    	t=t*10+ch-48;
   	    	ch = getc();
   		}
		if(f)t=-t;
	}
	template <typename T,typename... Args> inline void read(T& t, Args&... args){
	    read(t);read(args...);
	}
}
namespace out{
	char buffer[1<<21];
	int p1=-1;
	const int p2 = (1<<21)-1;
	inline void flush() {
		fwrite(buffer,1,p1+1,stdout),
		p1=-1;
	}
	inline void putc(const char &x) {
		if(p1==p2)flush();
		buffer[++p1]=x;
	}
	template <typename T>void write(T x) {
		static char buf[15];
		static int len=-1;
		if(x>=0){
			do{
    			buf[++len]=x%10+48,x/=10;
    		}while (x);
		}else{
    		putc('-');
			do {
    			buf[++len]=-(x%10)+48,x/=10;
			}while(x);
		}
		while (len>=0)
			putc(buf[len]),--len;
	}
}
using namespace std;
int t,n,x,y,A;
int ans[1000];
signed main(){
	in::read(t);
	while(t--){
		in::read(n,x,y);A=0x3f3f3f3f;
		for(int i=0;i<=y-x;i++){
			if((i==0&&x!=y)||(y-x)%i||(y-x)/i>(n-1))continue;
			int xx=x,yy=y;
			while(xx-i>=1)xx-=i;
			if(yy-xx<=i*(n-1)){
				int tmp=xx+i*(n-1);
				if(tmp<A){
					for(int w=1;w<=n;w++)
						ans[w]=xx+(w-1)*i;
					A=tmp; 
				}
			}else{
				int tmp=yy;xx=yy-i*(n-1);
				if(tmp<A){
					for(int w=1;w<=n;w++)
						ans[w]=xx+(w-1)*i;
					A=tmp; 
				}
			}
		}
		for(int i=1;i<=n;i++)
			out::write(ans[i]),out::putc(' ');
		out::putc('\n');
	}
	out::flush();
	return 0;
}
```

---

## 作者：smallfang (赞：1)

我们发现、 $x、y、A、B$ 的值均小于 $50$ ， 并且 $x ≤ y$ 所以我们可以直接暴力枚举起始地点、间隔. 运算次数最大为 $100 * 50 ^ 3$ 次 另外、需要注意、不能存在 $ai > ai-1$ 所以、范围间隔需要从 $1$ 开始（不能从 $0$ 开始）。起始地点从 $0$ 到 $x$，因为大于x就不可能包含 $x$ 了。范围间隔结束于 $y - x + 1$ 否则无法同时选中起点和终点。

这里我们如果过了 $x$ 但是 $x$ 并没有被选中。直接退出即可。

$y$也同理

最后我们找到包含 $x$ 、$y$ 并且最大值最小的数即可。

Code:

```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>

using namespace std;

const int N = 1e5, INF = 1e9;

int a[N], n, x, y, res = 0;

int main()
{
    int t;
    ios::sync_with_stdio(false);
    cin >> t;
    while (t -- )
    {
        cin >> n >> x >> y;
        int res = INF;
        int rs = 0, rc = 0;
        for (int i = 1; i <= x; i ++ )
        {
            for (int j = 1; j <= y - x + 1; j ++ )
            {
                int c = i;
                bool flag = true;
                bool fa = false, fb = false;
                for (int k = 1; k <= n; k ++ )
                {
                    if (c == x)
                    {
                        fa = true;
                    }
                    if (c == y)
                    {
                        fb = true;
                    }
                    if (c > x && fa == false)
                    	break;
                    if (c > y && fb == false)
                    	break;
                    c += j;
                }
                if (fa && fb)
                {
                    if (c < res)
                    {
                        res = c;
                        rs = i;
                        rc = j;
                    }
                }
            }
        }
        int cnt = 1;
        for (int i = rs; cnt <= n; cnt ++, i += rc )
        {
            cout << i << " ";
        }
        cout << endl;
        
    }
    return 0;
}
```

---

## 作者：_maple_leaf_ (赞：1)

### [原题链接](https://www.luogu.com.cn/problem/CF1409C)
### 题意
让你构造一个排序后各相邻元素之间差值相同，且最大值最小。
### 思路
- 可以发现，最后构造的数组排序后其实是一个等差数列；
- 同时，公差绝对是 $y-x$ 的因数，且 $(y-x)/i<n$（$i$ 为 $y-x$ 的因数）
- 还可以发现，$i$ 越小，最后最大值也越小；
- 因此我们可以枚举 $y-x$ 的因数 $i$，从 $1$ 开始一直到 $y-x$（一个数的最大因数是它本身，最小因数是 $1$）；
- 然后又出现一种情况（其实绝大部分都是），$x \sim y$ 之间的数不够 $n$ 个，与是考虑贪心；
- 可以发现，如果我们往比 $x$ 小的扩展，不会让最大值变大，因此贪心策略为尽可能多的往比 $x$ 小的扩展，实在再扩展就 $\le0$ 了就往比 $y$ 大的扩展；
- 然后输出即可（详细见代码）。
### code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,x,y,t;
signed main(){
	cin>>t;
	while(t--){
		cin>>n>>x>>y;
		int x1=y-x;//因数，这里用x1,与上文不同
		for(int i=1;i<=y-x;i++){//枚举因数
			if((y-x)%i==0&&floor((y-x)/double(i))<n){//判断是否为因数且x到y之间的数是否超过n
				x1=i;
				break;
			}
		}
		for(int i=x;i<=y;i+=x1){//输出x到y之间的数
			cout<<i<<" ";
			n--;//记录还剩多少个数没输出
		}
		for(int i=x-x1;i>=1&&n;i-=x1){//往比x小的数扩展
			cout<<i<<" ";
			n--;
		}
		for(int i=y+x1;i<=1e9&&n;i+=x1){//往比y大的数扩展
			cout<<i<<" ";
			n--;
		}
		cout<<endl;//换行
	}
	return 0;//完结撒花
}
```
~~管理大大，求过~~

---

## 作者：YangXiaopei (赞：0)

## Solution：

很简单的一题。

可以发现，最后要我们构造一个等差数列。

而 $x$ 和 $y$ 的差一定是多个公差。

那我们就分解 $x - y$ 的因数作为公差记为 $m$。

排除掉不可行的情况 $x + (n - 1) \times i < y$。

最后在不比 $1$ 小的情况下往小扩展，余下的往大扩展即可。

代码变量与本篇题解描述变量有所出入，请以代码为准。

## Code:

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t, n, x, y;
signed main(){
	cin >> t;
	while(t--){
		cin >> n >> x >> y;
		if(x > y){
			swap(x, y);
		}
		int sum = y - x;
		int pos = 0, minn = 1e9;
		for(int i = 1; i <= sum; i++){
			if(sum % i){
				continue;
			}
			if(i * (n - 1) < sum){
				continue;
			}
			for(int j = 50; j >= 0; j--){
				int a = x - j * i;
				int b = a + (n - 1) * i;
				if(a >= 1 && b >= y && (y - a) % i == 0){
					if(minn > b){
						minn = b;
						pos = i;
					}
				}
			}
		}
		for(int i = minn, j = 1; j <= n; j++, i -= pos){
			cout << i << " ";
		}
		cout << "\n";
	}
	return 0;
}
```

---

## 作者：uniqueharry (赞：0)


## **题意简述**

给出 ${n,x,y}$ 要求构造一个 ${n}$ 项的包含 ${x,y}$ 的等差数列，并使得数列中的最大值最小，可以乱序。

根据题目给出的数据规定我们发现${x<y}$，设该等差数列的公差为 ${d}$ ,其中数列的最大值一定满足${max(a_1,a_2,…,a_n)}={y+kd}$（$k$ 为整数）。那么既然要使最大值最小，只需找到最小的满足条件的公差 $d$ 即可。又知道 ${x,y}$ 是等差数列的两项，则必然满足${d\,|(y-x)}$，则可以从1开始枚举 $(y-x)$ 的约数。枚举的时候需要结合项数设置一个判断条件，当 ${(y-x)/d>n}$ 时，在 $n$ 项之内是构造不出这个数列的，一找到在最小的公差就退出。

然后因为题目不要求输出顺序，可以先从 $y$ 向前输出，当项数为 $n$ 或者下一项会小于1就退出，再设置一个变量标记一下，如果还没找齐 $n$ 项就再从 $y$ 向后输出即可。

最后贴一下代码：
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int main()
{
	int t,n,x,y,flag=0;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d%d",&n,&x,&y);
		int diff = y-x,dif,cnt=1;
		for(int i=1;i<=diff;i++)
		{
			if(diff%i==0)
			{
				if((diff/i)+1<=n)
				{
					dif = i;
				    break;
				}
			}
		}
		for(int i=y;cnt<=n;i-=dif,cnt++)
		{
			printf("%d ",i);
			if(i-dif<1&&cnt<n)
			{
				flag=1;
				break;
			}
		}
		if(flag==1)
		{
			for(int i=y;cnt<=n;i+=dif,cnt++)
			{
				if(i!=y) printf("%d ",i);
			}
		}
		printf("\n");
	}
	return 0; 
}
```


---

## 作者：SSerxhs (赞：0)

不妨设 $x\le y$

考虑枚举 $x,y$ 之间有 $i$ 个数，可以计算出数列公差进而推出最大值的最小值

几个注意点：$i<n$，$y$ 的存在导致数列最大值必定大于等于 $y$ 

```
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int c,n,t,x,y,i,j,mx,k;
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
int main()
{
	read(t);
	while (t--)
	{
		read(n);read(x);read(y);mx=1e9;
		for (i=1;i<=y-x;i++) if (((y-x)%i==0)&&(i<n))
		{
			c=(y-x)/i;
			k=x%c;if (k==0) k=c;
			if (max(k+(n-1)*c,y)<mx) 
			{
				mx=max(k+(n-1)*c,y);j=i;
			}
		}
		c=(y-x)/j;
		k=x%c;if (k==0) k=c;
		if (k+(n-1)*c<y) k=y-(n-1)*c;
		for (i=1;i<=n;i++) printf("%d ",k+(i-1)*c);puts("");
	}
}

---

## 作者：Ryo_Yamada (赞：0)

> 你需要构造一个 $n$ 个数的数列 $a$，排序后有 $a_2 - a_1 = a_3 - a_2 = \dots = a_n - a_{n-1}$。给你两个数 $x, y$ 是序列 $a$ 中的两个数，问使得 $\max(a_1, a_2, \dots , a_n)$ 最小时这个序列是什么？可以任意顺序输出。

首先，因为要包含 $x, y$ ，所以这个等差数列的公差 $t$ 一定有 $(y-x) \!\mod t = 0$ 且 $\dfrac{y - x}{i} + 1 \leq n$，从 $1$ 到 $y-x$ 枚举 $t$，希望 $t$ 最小。

之后向 $<x$ 扩展，若可以有 $n$ 项（即 $\dfrac{y - x}{t} + \dfrac{x - 1}{i} + 1 \geq n$），则不需要向上扩展，直接从 $y$ 输出 $n$ 项即可。

若还不够 $n$ 项，向上扩展。扩展的个数是 $n - (\dfrac{y - x}{t} + \dfrac{x - 1}{i} + 1)$。

$\text{Code}$：

```cpp
#include <bits/stdc++.h>

using namespace std;

int main() {
	int T;
	cin >> T;
	while(T--) {
		int n, x, y;
		scanf("%d%d%d", &n, &x, &y);
		int tmp = y - x;
		int lst = -1;
		for(int i = 1; i <= tmp; i++) {
			if(tmp % i == 0 && tmp / i + 1 <= n) {
				lst = i;
				break;
			}//找到最小公差
		}
		if(tmp / lst + (x - 1) / lst + 1 >= n) {
			for(int i = 1; i <= n; i++) {
				printf("%d ", y);
				y -= lst;
			}
		}//若不需要向上扩展，每次输出 y 并将 y 减去公差
		else {
			int k = tmp / lst + (x - 1) / lst + 1;
			int now = y;
			for(int i = 1; i <= k; i++) {
				printf("%d ", now);
				now -= lst;
			}//≤y的有 k 个，全部输出
			for(int i = 1; i <= n - k; i++) {
				y += lst;
				printf("%d ", y);
			}向上扩展
		}
		puts("");
	}
	return 0;
}

```


---

## 作者：InversionShadow (赞：0)

模拟赛 $10$ 分钟没有过，原来是记答案的时候 $k$ 的下标错了。/fn

观察到数据很小，考虑暴力。

我们默认 $x\le y$，设 $p=y-x$，那么公差就一定是 $1\sim p$ 中的一个数，所以第一重循环枚举公差。

第二层循环枚举开头的数，即 $1\sim x$ 中的一个数。显然，第三层循环就是算出每个数了。

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

int t, n, x, y, minn, a[10001], tot;
bool vis[100001];

signed main() {
  cin >> t;
  while (t--) {
    cin >> n >> x >> y;
    minn = 1000000;
    if (n == 2) {
      cout << x << ' ' << y << endl;
      continue;
    }
    if (x > y) {
      swap(x, y);
    }
    memset(a, 0, sizeof(a));
    int p = y - x;
    for (int i = 1; i <= p; i++) {
      for (int j = 1; j <= x; j++) {
        memset(vis, 0, sizeof(vis));
        int maxx = 0;
        for (int k = 0; k < n; k++) {
          vis[j + k * i] = 1;
          maxx = max(maxx, j + i * k);
        }
        if (vis[x] && vis[y]) {
          if (minn > maxx) { 
            minn = maxx;
            tot = 0;
            for (int k = 0; k < n; k++) { // 就是这里写成了 1 ~ n
              a[++tot] = j + k * i;
            }
          }
        }
      }
    }
//    cout << minn << endl;
    for (int i = 1; i <= tot; i++) {
      cout << a[i] << ' ';
    }
    cout << '\n';
  }
  return 0;
}
```

---

