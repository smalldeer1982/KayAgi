# Colorful Hats 2

## 题目描述

[problemUrl]: https://atcoder.jp/contests/sumitrust2019/tasks/sumitb2019_e

$ N $ 人の人が一列に並んでおり、前から順に $ 1,\ 2,\ 3,\ ...,\ N $ と番号が付けられています。それぞれの人は、赤色・青色・緑色のいずれかの帽子を被っています。

さて、番号 $ i $ の人は以下の発言をしました。

- 「自分より前に、自分と同じ色の帽子を被っている人はちょうど $ A_i $ 人いる。」

すべての人の発言が正しいとして、$ N $ 人の人の帽子の色の組合せとして考えられるものが何通りあるか求めてください。

ただし、答えがとても大きくなる場合があるので、代わりに $ 1000000007 $ で割った余りを計算してください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 100000 $
- $ 0\ \leq\ A_i\ \leq\ N-1 $
- 入力中の値はすべて整数

### Sample Explanation 1

以下の $ 3 $ 通りの組合せが考えられます。 - 赤, 赤, 赤, 赤, 赤, 赤 - 青, 青, 青, 青, 青, 青 - 緑, 緑, 緑, 緑, 緑, 緑

## 样例 #1

### 输入

```
6
0 1 2 3 4 5```

### 输出

```
3```

## 样例 #2

### 输入

```
3
0 0 0```

### 输出

```
6```

## 样例 #3

### 输入

```
54
0 0 1 0 1 2 1 2 3 2 3 3 4 4 5 4 6 5 7 8 5 6 6 7 7 8 8 9 9 10 10 11 9 12 10 13 14 11 11 12 12 13 13 14 14 15 15 15 16 16 16 17 17 17```

### 输出

```
115295190```

# 题解

## 作者：_Haoomff_ (赞：3)

题目不难。

每次输入一个数，我们与一个数组的前三个维度做比较，这三个维度表示的是在第 $i$ 个人前面戴三种颜色帽子的人数。

如果当前输入的数和其中一个维度相同，那么就将这个维度再加 $1$，表示戴这个颜色帽子的人又多了一个。在这个过程中，每次都要讲计数器加 $1$，最后将统计出来的数乘到总方案中。

注意：别忘了取模！
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int p=1e9+7;
ll n,a[4],cnt=1;//a数组表示有多少人戴不同颜色的帽子，cnt表示总方案数 
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(;n--;){
		ll b,res=0,i;
		cin>>b;
		if(b==a[1]){
			i=1;
			++res;
		}
		if(b==a[2]){
			i=2;
			++res;
		}
		if(b==a[3]){
			i=3;
			++res;
		}
		cnt=cnt*res%p;++a[i];
	}
	cout<<cnt%p;
	return 0;
}
```


---

## 作者：shengyeqi (赞：2)

## 题面

$N$ 个人站成一列，每个人都戴着一顶帽子，颜色为红、黄、绿的一种。第 $i$ 个人前面有 $a_i$ 个人戴着和他颜色相同的帽子。求出 $N$ 个人帽子颜色的所有组合方案。

答案对 $10^9+7$ 取模。

- $1\leq N \leq 100000$
- $0\leq a_i \leq N-1$
- $N$ 和 $a_i$ 均为整数。

## 思路

这是一道小学的奥数题。

只要把每次输入的 $x$ 跟数组进行对比只要一样就把 $y$ 加 $1$，$z$ 变成对应数组的下标，最后把 $s$ 和 $y$ 相乘把 $a_z$ 加 $1$ 然后再把 $s$ 对 $10^9+7$ 进行取模。循环结束后，再输出 $s$ 就行了（别忘了 AT 的换行）。

注意，本题要开 ``long long``。

## 代码

```
#include <bits/stdc++.h>
using namespace std;
const long long N=1e9+7;
long long n,s=1,a[4];
int read()
{
    int f=1,x=0;
    char c=getchar();
    while(c<'0'||c>'9')
	{
        if(c=='-')f=-f;
        c=getchar();
    }
    while(c>='0'&&c<='9')
	 {
        x=x*10+c-'0';
        c=getchar();
    }
    return f*x;
}
int main()
{
    n=read();
    for(long long i=1;i<=n;i++)
    {
        long long x,y=0,z=0;
        x=read();
        if(x==a[0]) y++,z=0;
        if(x==a[1]) y++,z=1;
        if(x==a[2]) y++,z=2;
        s*=y;s=s%N;a[z]++;
    }
    cout<<s<<'\n';
    return 0;
}
```

注：主要出自[这篇题解](https://www.luogu.com.cn/blog/zhaohongxu/colorful-hats-2-ti-xie) @zhaohongxu本人同意。

---

## 作者：封禁用户 (赞：0)

## 前言：
竟然有如此水的黄题。

## 思路：

根据题目我们可以知道，每种颜色的前置相同颜色数目一定是逐渐增大。

由于这道题需要考虑到所有的组合方案，因此对于 $n$，若其之前存在多个尚未被匹配的 $n−1$，则可以存在多种方案。

最后输出 $ans$ 即可。

## AC Code：

```cpp
#include <bits/stdc++.h>
using namespace std;
const long long mod=1000000007;
const long long N=100010;
const long long P=5;
long long n,x,a[N];
long long b[P],sum=0,ans=1;
int main()
{
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	std::ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin >> n;
	for(long long i=1;i<=n;i++)
	{
		cin >> a[i];
	}
	for(long long i=1;i<=n;i++)
	{
		sum=0;
		if(a[i]==b[0])
		{
		    sum++;
			x=0;
		}
		if(a[i]==b[1])
		{
			sum++;
			x=1;
		}
		if(a[i]==b[2])
		{
			sum++;
			x=2;
		}
		ans*=sum;
		ans%=mod;
		b[x]++;
	}
	cout << ans << endl;
	return 0;
}
``````

---

## 作者：cosf (赞：0)

## [Colorful Hats 2](https://www.luogu.com.cn/problem/AT_sumitb2019_e)

这一题可以在线。显然，假设我们处理了 $a_1, \dots, a_i$，那么每一种颜色有多少个是可以算出来的（当然，颜色之间是有顺序的）。

我们具体可以维护三个变量 $s_r, s_h, s_g$，表示当前每一种颜色对应有多少顶帽子。

那么考虑加进 $i + 1$。显然，$i + 1$ 能够加进来当且仅当有一个 $s$ 等于 $a_{i + 1}$，而且，无论你选哪个满足 $s = a_{i + 1}$ 的颜色，它的影响都是一样的。

所以，$i + 1$ 的贡献就是 $s$ 中等于 $a_{i + 1}$ 的个数。

处理完后要将一个 $s$ 加上 $1$。

最后将所有贡献乘起来就可以了。

具体实现有很多方法，可以开桶，可以开 map，可以维护三个变量，等等，都是可以的。

## 代码

```cpp
#include <iostream>
#include <set>
using namespace std;

#define MOD 1000000007

using ll = long long;

multiset<int> s;

int main()
{
    s.insert(-1);
    s.insert(-1);
    s.insert(-1);
    ll res = 1;
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        int x;
        cin >> x;
        res = res * s.count(x - 1) % MOD;
        if (res == 0)
        {
            cout << 0 << endl;
            return 0;
        }
        s.erase(s.find(x - 1));
        s.insert(x);
    }
    cout << res << endl;
    return 0;
}

```

---

## 作者：lqsy002 (赞：0)

## 题目大意

[题目链接](https://www.luogu.com.cn/problem/AT_sumitb2019_e)。

## 解题思路

由题意可得，每种颜色的前置相同颜色数目一定是逐渐增大的。

由于本题需要考虑到所有的组合方案，因此对于 $n$，若其之前存在多个尚未被匹配的 $n-1$，则可以存在多种方案。

十年 OI 一场空，不开 longlong 见祖宗。

## 参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const long long mod=1000000007;
int n,a[100010],x;
long long m[5],cnt,ans=1;
int main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;++i)
        cin>>a[i];
    for(int i=1;i<=n;++i){
        cnt=0;
        if(a[i]==m[0]){
            cnt++;
            x=0;
        }
        if(a[i]==m[1]){
            cnt++;
            x=1;
        }
        if(a[i]==m[2]){
            cnt++;
            x=2;
        }
        ans*=cnt;
        ans%=mod;
        m[x]++;
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：skyskyCCC (赞：0)

## 前言。
组合数学和乘法原理。

用到了简单的递归思路，线性实现方法。
## 分析。
题目很明显是一道排列数学问题，然后因为 $n$ 的范围是 $10^5$ 所以我们考虑线性解决。首先我们考虑状态，我们定义当我们遍历到第 $i$ 个的时候，与前面有 $c_i$ 个不同的组合方法。然后考虑如何准确地描述一个状态。这个状态必须使得可以遍历到每个新的元素时，可以转移到当前的状态并且可以确定这个元素能够和哪几个相互组合。

定义状态为 $\left(x_i,y_i,z_i\right)$ 代表我们考虑当遍历到第 $i$ 个元素的时候某种排列的可能情况，具体来说，其中的 $x_i$ 表示遍历到第 $i$ 个元素的时候能达到的最多的相同的元素的个数。然后 $y_i$ 表示遍历到第 $i$ 个元素的时候第二大多的相同的元素的个数。最后的 $z_i$ 表示遍历到第 $i$ 个元素的时候最少的元素的个数。

那么我们每次遍历一个元素时，我们就可以遍历整个状态，然后将和当前状态对应的元素相同的元素个数加上，表示我们现在有一种可能情况：这个队列在第 $i$ 个位置的人排在他的后面。所以如果有 $x$ 个相同的元素，那么乘上 $x$ 即可。

代码如下，仅供参考：
```
#include<iostream>
#include<vector>
using namespace std;
const long long mod=1e9+7;
long long n;
long long ans=1,sum,num;
long long a[100005];
vector<long long> c(3,0);
int main(){
	cin>>n;
	for(int i=0;i<n;i++){
	    cin>>a[i];
	}
	for(int i=0;i<n;i++){
		sum=0,num=-1;
		for(int j=0;j<3;j++){
		    if(a[i]==c[j]){
			    sum++;
				num=j;
			}
		}
		if(num==-1){
			cout<<"0\n";
			return 0;
		}
		c[num]++;
	    ans=ans*sum%mod;
	}
	cout<<ans<<"\n";
	return 0;
}
```
## 后记。
大家如有疑问，可以在评论区提出，我会尽力解答的。

---

## 作者：MuLinnnnn (赞：0)

[洛谷题面](https://www.luogu.com.cn/problem/AT_sumitb2019_e) & [ATcoder 题面](https://atcoder.jp/contests/sumitrust2019/tasks/sumitb2019_e)

**题意：**

给定每个人有几个和他属性（颜色）一样的人数，询问合法的排列数量。其中属性恒定为 $i$(1~3)。

**思路：**

这其实是一道数学题，每次询问贡献，并将贡献累加进答案中维护下一次计算贡献。每次查询贡献时找出三种状态中和当前数量一致的，将贡献加上一，并记录当前位置。最后改变当前状态的数值加一。记得每次 $ans$ 取模。

注意：不开`long long`见祖宗。

**Accept Code：**

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#define int long long
#define FAST ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
using namespace std;
int hat[4];
const int Mod = 1000000007;

signed main(){
	FAST; 

	int n;
    cin >> n;
    int ans = 1;
    for(int i = 1; i <= n; ++i){
    	int num;
    	cin >> num;
    	int x = 0, pos = 0;
    	if(num == hat[1]){
    		x++;
    		pos = 1;
		}
    	if(num == hat[2]){
    		x++;
    		pos = 2;
		}
		if(num == hat[3]){
			x++;
			pos = 3;
		}
		ans *= x;
		ans %= Mod;
		hat[pos]++;
	}
	cout << ans;
	return 0;
}

```

---

## 作者：mz2022 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_sumitb2019_e)

AC 背景:
--------
队测时出了这题，但很可惜没写出来，后面想了想就过了，决定顺便来洛谷淼一发题解。


思路：
--------
简单小学奥数题

可以发现，只用把输入的帽子数与前面的 $3$ 种帽子数量比较，如果相同就 $ans + 1$ 最后累乘即可。并给这种帽子颜色数量加 $1$。

别忘了取模！！！

AC Code:
--------
```cpp
#include<bits/stdc++.h>
using namespace std;
#define mod 1000000007
#define int long long
int n,s=1,t=0,red=0,yellow=0,green=0;
signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		int x,ok=0;
		cin>>x;
		t=0;
		if(x==red)
		{
			if(ok==0)red++,ok=1;
			t++;
		}
		if(x==yellow)
		{
			if(ok==0)yellow++,ok=1;
			t++;
		}
		if(x==green)
		{
			if(ok==0)green++,ok=1;
			t++;
		}
		s*=t;
		s%=mod;
	}
	cout<<s<<endl;
	return 0;
}
```

---

## 作者：felixshu (赞：0)

[我是传送门](https://www.luogu.com.cn/problem/AT_sumitb2019_e#submit)

## 题目大意

$N$ 个人站成一列，每个人都戴着一顶帽子，颜色为红、黄、绿的一种。第 $i$ 个人前面有 $a_i$ 个人戴着和他颜色相同的帽子。求出 $N$ 个人帽子颜色的所有组合方案。答案对  $10^9+7$ 取模。
 
- $1\le N\le 100000$。

- $0\le a_i\le N-1$。

- $N$ 和 $a_i$ 均为整数。

## 分析
看到 $n$ 的范围，知道要 $O(n)$ 复杂度解决。

可以发现，只用把输入的与前面的 $3$ 种帽子数量比较，如果相同就 $s+1$，最后累乘即可。然后给这种帽子颜色加一。

要与 $10^9+7$ 取摸。

注意，本题要开 ```long long```。

## 下面是 AC 代码
```
#include <bits/stdc++.h>
using namespace std;
const long long N=1e9+7;
long long a[4];
int main()
{
	long long n,ans=1;
    cin>>n;
    for(long long i=1;i<=n;i++)
    {
        long long b,s=0,z=0;
        cin>>b;
        if(b==a[0])
		{
			s++;
			z=0;
		 } 
        if(b==a[1]) 
		{
			s++;
			z=1;
		}
        if(b==a[2])
		{
			s++;
			z=2;
		 } 
        ans*=s;
		ans=ans%(1000000007);
		a[z]++;
    }
    cout<<ans<<endl;
    return 0;
}

```

---

## 作者：Krimson (赞：0)

非常巧妙的一道题目,虽然用到的知识点非常简单,却不太容易想到  


------------
看到题目,不难想出一个$dp$:  
设$f[i][x][y][z]$表示到了第$i$个人,有$x$个戴红帽,$y$个戴蓝帽,$z$个戴绿帽  
若当前的第$i$个人说有$k$个人和他帽子颜色一样,那么有以下转移方程:
$$
f[i][k][y][z]+=f[i-1][k-1][y][z]\\
f[i][x][k][z]+=f[i-1][x][k-1][z]\\
f[i][x][y][k]+=f[i-1][x][y][k-1]
$$  
发现满足$x+y+z=i$,那么可以优化掉一维,而第一维又是可以滚掉的  
时空复杂度均为$O(n^2)$  

 _Coder_ 
------------
```cpp
#include<bits/stdc++.h>
using namespace std;
#define il inline
#define ri register int
#define ll long long
#define ui unsigned int
il ll read(){
    bool f=true;ll x=0;
    register char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-') f=false;ch=getchar();}
    while(ch>='0'&&ch<='9') x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
    if(f) return x;
    return ~(--x);
}
il int read(char *s){
    int len=0;
    register char ch=getchar();
    while(ch==' '||ch=='\n') ch=getchar();
    while(ch!=' '&&ch!='\n'&&ch!=EOF) s[++len]=ch,ch=getchar();
    return len;
}
il void write(const ll &x){if(x>9) write(x/10);putchar(x%10+'0');}
il void print(const ll &x) {x<0?putchar('-'),write(~(x-1)):write(x);putchar('\n');}
il ll max(const ll &a,const ll &b){return a>b?a:b;}
il ll min(const ll &a,const ll &b){return a<b?a:b;}
int n;
const int MAXN=2000;
const ll mod=1e9+7;
ll f[2][MAXN][MAXN],ans;
struct node
{
    int u,v;
};
node sta[MAXN<<2];
int top;
int main(){
    n=read();
    f[0][0][0]=1;
    sta[++top]=(node){0,0};
    for(ri i=1,g=1;i<=n;++i,g^=1){
        // memset(f[g],0,sizeof(f[g])); 不能用memset,不然复杂度会变成O(n^3),应该用一个栈把修改过的位置记录下来,手动清空
        int x=read();
        if(x>=i){
            puts("0");
            break;
        }
        for(ri j=0;j<=i-x-1;++j){
            f[g][x+1][j]=(f[g][x+1][j]+f[g^1][x][j])%mod;
            f[g][j][x+1]=(f[g][j][x+1]+f[g^1][j][x])%mod;
            f[g][j][i-x-1-j]=(f[g][j][i-x-1-j]+f[g^1][j][i-x-1-j])%mod;
        }
        while(top) f[g^1][sta[top].u][sta[top].v]=0,top--;
        for(ri j=0;j<=i-x-1;++j){
            sta[++top]=(node){x+1,j};
            sta[++top]=(node){j,x+1};
            sta[++top]=(node){j,i-x-1-j};
        }
    }
    for(ri i=0;i<=n;++i){
        for(ri j=0;j<=n;++j){
            ans=(ans+f[n&1][i][j])%mod;
        }
    }
    print(ans);
    return 0;
}
```


------------      
$O(n^2)$并不能过,考虑换一种做法

可以发现到了位置$i$,帽子个数的$x,y,z$(排序后)其实是一定的  
这里给出一个简单的证明  

如果$x,y,z$三者当中只有一个等于$k$,不妨设其为$x$  
那么到了$i+1$的时候,帽子的个数就变成了$i+1,y,z$,是确定的。

如果$x,y,z$中有两个相同,都为$k$,不妨设两者为$x,y$那么到了$i+1$时就变成了$k,k+1,z$或$k+1,k,z$,排序之后是一个同一个序列,而且方案数是原来的两倍  

三个均为$k$的情况也可以一样推得,且方案数变成原来的三倍  

设第$i$个位置有$cnt$个帽子个数为$k$,那么可以得到$ans_i=cnt\times ans_{i-1}$  

其实仔细思考就会发现上面这个过程其实就是在推导乘法原理  

 _Coder_   
------------
```cpp
#include<bits/stdc++.h>
using namespace std;
#define il inline
#define ri register int
#define ll long long
#define ui unsigned int
il ll read(){
    bool f=true;ll x=0;
    register char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-') f=false;ch=getchar();}
    while(ch>='0'&&ch<='9') x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
    if(f) return x;
    return ~(--x);
}
il int read(char *s){
    int len=0;
    register char ch=getchar();
    while(ch==' '||ch=='\n') ch=getchar();
    while(ch!=' '&&ch!='\n'&&ch!=EOF) s[++len]=ch,ch=getchar();
    return len;
}
il void write(const ll &x){if(x>9) write(x/10);putchar(x%10+'0');}
il void print(const ll &x) {x<0?putchar('-'),write(~(x-1)):write(x);putchar('\n');}
il ll max(const ll &a,const ll &b){return a>b?a:b;}
il ll min(const ll &a,const ll &b){return a<b?a:b;}
ll num[3],ans=1;
int n=read();
const ll mod=1e9+7;
int main(){
    for(ri i=1,x,id=0,cnt;i<=n;++i){
        x=read(),cnt=0;//本来id初值应该设为-1,但是ans为0之后无论id为多少都是0了,就不用设了
        for(ri j=0;j<3;++j)
            if(num[j]==x) id=j,++cnt;
        num[id]++;
        ans=ans*cnt%mod;
    }
    print(ans); 
    return 0;
}
```


---

## 作者：lkjzyd20 (赞：0)

### 思路
一道数学智力题。

因为 $n$ 的范围是 $10^5$，所以我们考虑 $O(n)$ 解决。

统计现在总共有多少个红，蓝，绿的帽子，再判断有多少种颜色的帽子个数是和输入的数相等的，表示当前有多少种方案，最后累乘一下即可。

### 代码如下

```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long 
#define rep(i, l, r) for(int i = l; i <= r; ++ i)
#define per(i, r, l) for(int i = r; i >= l; -- i)
#define me0(a); memset(a, 0, sizeof a);
#define me3(a); memset(a, 0x3f, sizeof a);
#define PII pair<int, int>
#define il inline

const int INF = 0x3f3f3f3f, MOD = 1e9 + 7;

il void read(int &n)
{
    bool w = 0;
    char c = getchar();
    for(; c < 48 || c > 57; c = getchar())
        w = c == 45;
    for(n = 0; c >= 48 && c <= 57; c = getchar())
        n = n * 10 + c - 48;
    n = w ? -n : n;
}

il void write(int x, char a)
{
    char c[40], s = 0;
    if(x < 0) putchar(45), x = -x;
    for(; x ;) c[s ++] = x % 10, x /= 10;
    if(!s) putchar(48);
    for(; s -- ;) putchar(c[s] + 48);
    putchar(a);
}

const int MAXN = 100000;

int n;
int ans = 1;
int m[4];
main()
{
    read(n);
    rep(i, 1, n)
    {
        int x;
        read(x);
        int sum = 0, t = 0;
        if(x == m[1]) ++ sum, t = 1;
        if(x == m[2]) ++ sum, t = 2;
        if(x == m[3]) ++ sum, t = 3;
        ans *= sum;
        ans %= MOD;
        ++ m[t];
    }
    cout << ans << '\n';

    return 0;
}
```

---

## 作者：_zhx (赞：0)

# 题目大意

有 $N$ 个人站成一列，每个人都戴着一顶帽子，颜色为红、黄、绿的一种，第 $i$ 个人前面有 $a_i$ 个人戴着和他颜色相同的帽子。求出 $N$ 个人帽子颜色的所有组合方案。

## 题目做法

其实这就是一道小学奥数题，代码上没有什么难点，主要是思路上的问题。只要把每次输入的数 $x$ 和三个数组对比，只要一样就把 $y$ 加一，$z$ 变成对应数组的下标，最后把 $s$ 和 $y$ 相乘，把 $a_z$ 加一，然后再把 $s$ 和 $10^9+7$ 取模。循环结束后，再输出 $s$。

### 题目代码

AC code
```cpp
#include <bits/stdc++.h>
using namespace std;
const long long N=1e9+7;
long long n,s=1,a[4];
int read()
{
    int f=1,x=0;
    char c=getchar();
    while(c<'0'||c>'9')
	{
        if(c=='-')f=-f;
        c=getchar();
    }
    while(c>='0'&&c<='9')
	 {
        x=x*10+c-'0';
        c=getchar();
    }
    return f*x;
}
int main()
{
    n=read();
    for(long long i=1;i<=n;i++)
    {
        long long x,y=0,z=0;
        x=read();
        if(x==a[0]) y++,z=0;
        if(x==a[1]) y++,z=1;
        if(x==a[2]) y++,z=2;
        s*=y;s=s%N;a[z]++;
    }
    cout<<s<<'\n';
    return 0;
}
```


---

