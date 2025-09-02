# AND Reconstruction

## 题目描述

给定一个由 $ n - 1 $ 个整数组成的数组 $ b $。

一个数组 $ a $ 被称为是“好的”当且仅当对于 $ 1 \le i \le n-1 $，都有 $ b_i = a_i \, \& \, a_{i + 1} $ 其中$ \& $ 表示[按位与运算](https://en.wikipedia.org/wiki/Bitwise_operation#AND)。

你的任务是构造一个“好的”数组，或输出 `-1` 表示不存在“好的”数组。

## 说明/提示

对于第一组样例，$ b = [1] $。一个可能的"好的"数组是 $ a=[5, 3] $。因为 $ a_1 \, \& \, a_2 = 5 \, \& \, 3 = 1 = b_1 $。

对于第二组样例，$ b = [2, 0] $。一个可能的"好的"数组是 $ a=[3, 2, 1] $。因为 $ a_1 \, \& \, a_2 = 3 \, \& \, 2 = 2 = b_1 $ and $ a_2 \, \& \, a_3 = 2 \, \& \, 1 = 0 = b_2 $。

对于第三组样例，$ b = [1, 2, 3] $。可以证明不存在"好的"数组，所以输出 `-1`。

对于第四组样例，$ b = [3, 5, 4, 2] $。一个可能的"好的"数组是 $ a=[3, 7, 5, 6, 3] $。

## 样例 #1

### 输入

```
4
2
1
3
2 0
4
1 2 3
5
3 5 4 2```

### 输出

```
5 3
3 2 1
-1
3 7 5 6 3```

# 题解

## 作者：白鲟 (赞：6)

要使得 $a_i\operatorname{and} a_{i+1}=b_i$，将二进制表示视作集合，$b_i\operatorname{or}b_{i-1}$ 一定是 $a_i$ 的子集。贪心地，即令 $a_i = b_i\operatorname{or}b_{i-1}$，则 $a_i$ 的二进制表示中 $1$ 的个数最少，有利于与运算的进行，可以使得答案不劣。最后判断对于每个 $b_i$ 是否满足条件即可。

一个小坑是 $b_{n}$ 需要清零，因为这个吃了一发罚时。

代码中 $a,b$ 与题设相反。

```cpp
#include <algorithm>
#include <cstdio>
const int maxn = 1e5;
int T, n, a[maxn + 1], b[maxn + 1];
bool flag;
int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        flag = true;
        for (int i = 1; i < n; ++i) {
            scanf("%d", &a[i]);
        }
        a[n] = 0;
        b[1] = a[1];
        for (int i = 2; i <= n; ++i) {
            b[i] = a[i] | a[i - 1];
        }
        for (int i = 1; i < n; ++i) {
            if ((b[i] & b[i + 1]) != a[i]) {
                flag = false;
            }
        }
        if (flag) {
            for (int i = 1; i <= n; ++i) {
                printf("%d ", b[i]);
            }
            puts("");
        }
        else {
            puts("-1");
        }
    }
    return 0;
}
```

---

## 作者：zhouchuer (赞：2)

## [题目传送门](https://www.luogu.com.cn/problem/CF1991B)
### 题意
给定一个共有 $n-1$ 个元素的数组 $b$，问你能否构造一个数组 $a$，且 $a$ 是一个“好的”数组，一个数组 $a$ 被称为“好的”当且仅当对于 $1 \le i \le n-1$，都满足 $b_i = a_i \operatorname{and} a_{i+1}$。

### 思路
根据按位与运算的性质可知，只有当 $a_i$ 与 $a_{i+1}$ 的第 $j$ 位都为 $1$ 时，$b_i$ 第 $j$ 位的结果才为 $1$，$j$ 最大为 $30$，所以我们就在 $i \le n-1$ 的循环里面开一层循环，如果 $b_i$ 的第 $j$ 位为 $1$ 就将 $a_i$ 与 $a_{i+1}$ 的第 $j$ 位设置为 $1$。最后遍历一遍，如果发现 $b_i \ne a_i \operatorname{and} a_{i+1}$ 就输出 $-1$，否则输出数组 $a$，注意多测要清空数组。[代码](https://www.luogu.com.cn/paste/wi5cf1ik)。

---

## 作者：donnieguo (赞：2)

## 题意简述

给定一个有 $n - 1$ 个数的数列 $b$，要求构造一个数列 $a$，使得 $a_i \; \& \; a_{i + 1} = b_i$。

其中 $\&$ 表示位运算中的按位与。

## 思路

根据按位与的运算方法我们可以知道，只有当 $a_i$ 和 $a_{i + 1}$ 的第 $j$ 为上都是 $1$ 的时候，$b_i$ 的第 $j$ 位上才会是 $1$。

那么构造方法就很简单了，对于每一个 $b_i$，如果在二进制下第 $j$ 位上是 $1$，那么 $a_i$ 和 $a_{i + 1}$ 的第 $j$ 位就都是 $1$，否则为 $0$。最后判断一下组成的序列是否满足要求即可。

## AC code
```cpp
#include <iostream>
#include <cstring>
#define N 100010
using namespace std;

int T, n, a[N], b[N];
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin >> T;
	while (T--)
	{
		memset(a, 0, sizeof(a)); //多测记得清空
		cin >> n;
		for (int i = 1; i < n; i++) cin >> b[i];
		for (int i = 1; i < n; i++)
			for (int j = 0; j <= 30; j++)
				if (b[i] >> j & 1) a[i] |= 1 << j, a[i + 1] |= 1 << j;
		bool flag = 1;
		for (int i = 1; i < n; i++) if ((a[i] & a[i + 1]) != b[i]) {flag = 0; break;}
		if (flag) {
			for (int i = 1; i <= n; i++) cout << a[i] << ' ';
			cout << '\n';
		}
		else cout << -1 << '\n';
	}
	return 0;
}
```

---

## 作者：qfy123 (赞：2)

# CF1991B
[传送门](https://www.luogu.com.cn/problem/CF1991B)
## 思路
根据按位与运算的性质，我们可以得出，在二进制表示下，**当且仅当** $a_i$ 与 $a_{i+1}$ 的第 $j$ 位均为 $1$ 的时候，$b_i$ 的第 $j$ 位才为 $1$。根据上述结论，构造方法就出来了（具体见代码）。最后再判断是否合法即可。 
## 代码
```cpp
#include<bits/stdc++.h>
#define ll long long
#define ull unsigned ll
#define r(x) scanf("%d",&x)
#define rl(x) scanf("%lld",&x)
#define rs(x) scanf("%s",x+1)
#define pr(x) printf("%d ",x)
#define pl(x) printf("%d\n",x)
#define prl(x) printf("%lld ",x)
#define pll(x) printf("%lld\n",x)
using namespace std;
const int N = 1e5 + 10;
int a[N],b[N],T,n;
bool chk(){//检查答案是否合法
	for(int i=1;i<n;i++) if((a[i] & a[i+1]) != b[i]) return 0;
	return 1;
}
void solve(){
	memset(a,0,sizeof(a));//多测别忘记清空
	r(n);
	for(int i=1;i<n;i++) r(b[i]);
	for(int i=1;i<n;i++) for(int j=0;j<=30;j++)  if(b[i] >> j & 1) a[i] |= 1 << j , a[i+1] |= 1 << j;
  //如果b[i]的第j位为1，那么就将a[i]和a[i+1]的第j位设为1
	if(chk()) for(int i=1;i<=n;i++) pr(a[i]);	
	else pr(-1);
	puts(""); 
}
int main(){
	r(T);
	while(T--) solve();
	return 0;
}
```

---

## 作者：Trubiacy_ (赞：1)

### 赛时思路

这道题卡了我很久，~~位运算实在是太阴间了~~，我们可以想到，$a_i$ 既参与到 $b_i$ 的计算中，也参与到了 $b_{i-1}$ 的计算中，既然要通过与运算计算出 $b_i$ 和 $b_{i-1}$ 的值， $b_i$ 和  $b_{i-1}$ 的每一位`1`都会出现在 $a_i$ 中，结合对样例的观察可以得出，对于 $1<i<n-1$ ,  $a_i=b_i | b_{i-1}$ ，同时我们可以得知，为了得到 $b_1$ 与 $b_{n-1}$ 的值，$a_1=b_1$, $a_n=b_{n-1}$。

这里还存在一个问题，最后的答案可能会输出 `-1` ，我的解决方式是模拟题目中的情况从头到尾跑一遍看是否符合题目描述。

### 赛时代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define x first
#define y second
#define MAXN 0x3f3f3f3f3f3f3f3f
#define MINN -0x3f3f3f3f3f3f3f3f
#define Trubiacy ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
using namespace std;

const int N=1e5+29;
int n,a[N],ans[N];//代码中数组命名有点乱，a数组为原题中b数组（使用a是因为我习惯输入的数组是a数组），ans为原题中a数组（使用ans是因为此数组为最终需要输出的数组）

signed main(){
    Trubiacy;
    // int Tracy=1;
    int Tracy; cin>>Tracy;
    while(Tracy--){
        cin>>n;
        for(int i=1;i<n;i++){
            cin>>a[i];
        }
        ans[1]=a[1];
        for(int i=1;i<n-1;i++){
            ans[i+1]=(a[i]|a[i+1]);
        }
        ans[n]=a[n-1];
        
        //判断是否成立（即有无可能输出-1）
        bool f=true;
        for(int i=1;i<n;i++){
            // cout<<(ans[i]&ans[i+1])<<" ";
            if((ans[i]&ans[i+1])!=a[i]){//不符合题目描述，即答案不存在
                f=false;
                break;
            }
        }
        if(!f) cout<<-1;
        else{
            for(int i=1;i<=n;i++){
                cout<<ans[i]<<" ";
            }
        }
        cout<<endl;
    }
    return 0;
}
```

---

## 作者：yyz1005 (赞：1)

注意到若 $b_{i-1}=a_{i-1} \& a_i,b_i = a_i \& a_{i+1}$，也就是说 $a_i \& b_{i-1}=b_{i-1},a_i \& b_i = b_i$，由此有 $a_i \& (b_{i-1}|b_i) = (b_{i-1}|b_i)$。

又注意到取 $a_1 = b_1,a_n = b_n$，$a_i = b_{i-1} | b_i,2 \le i \le n-1$ 时若不成立则一定无解，这是因为对于所有的 $a_i$ 都在此时取到了最小值。

[Code](codeforces.com/contest/1991/submission/273263323)

---

## 作者：Dioretsa (赞：1)

注意到 $a_{i-1} \& a_{i} = b_{i-1}$ 且 $a_{i} \& a_{i+1} = b_i$，则 $b_{i-1}$ 和 $b_i$ 的二进制数为 $1$ 的位置，$a_i$ 相应二进制数的位置上也必为 $1$。因此可以令 $a_i = b_{i-1} | b_i$，最后检查一下构造出来的 $a$ 序列是否合法即可。


```cpp
#include<bits/stdc++.h>
#define MAXN 100005
using namespace std;
inline int read() {
	int x=0,f=1;
	char ch=getchar();
	while (ch<'0'||ch>'9') {
		if (ch=='-') f=-1;
		ch=getchar();
	}
	while (ch>='0'&&ch<='9') {
		x=x*10+ch-48;
		ch=getchar();
	}
	return x*f;
}
int T,n,b[MAXN],a[MAXN];
int main() {
	T=read();
	while(T--){
		n=read();
		for(int i=1;i<=n-1;i++){
			b[i]=read();
			a[i]=b[i]|b[i-1];
		}
		a[n]=b[n-1];
		bool check=true;
		for(int i=1;i<=n-1;i++){
			if(b[i]!=(a[i]&a[i+1])){
				check=false;
				break;
			}
		}
		if(!check){
			printf("-1\n");
			continue;
		}
		for(int i=1;i<=n;i++) printf("%d ",a[i]);
		printf("\n");
	}	
	return 0;
}

```

---

## 作者：JXR_Kalcium (赞：0)

## 题目大意

给定一个长度为 $n-1$ 的数组 $b$，要构建一个数组 $a$ 使得对于每个 $1\le i\le n-1$ 都有 $a_i~\textrm{and}~a_{i+1}=b_i$，若不存在这个序列则输出 $-1$。

## 解题思路

其实手玩几把样例就可以发现，就拿最后一个样例来说，我们试试把相邻两个数按位或一下，就可以得到 $7,5,6$，而这刚好是除了第一个和最后一个之外的答案。再看对于第一个答案来说，此时 $3~\textrm{and}~7=3$，对于最后一个答案，$6~\textrm{and}~2=2$，所以最后的答案就是 $3,7,5,6,2$（虽然与样例不同，但也是对的）。实际上根据这一条公式：

$$
a_i~\textrm{and}~a_{i+1}=(b_{i-1}~\textrm{or}~b_i)~\textrm{and}~(b_i~\textrm{or}~b_{i+1})=b_i~\textrm{or}~(b_{i-1}~\textrm{and}~b_{i+1})
$$

就可总结出下列转移公式：

$$
a_i=\left\{\begin{aligned}&b_1~\textrm{and}~(b_1~\textrm{or}~b_2),\textrm{if}~i=1\\&b_{i-1}~\textrm{or}~b_i,\textrm{if}~2\le i\le n-1\\&b_{n-1}~\textrm{and}~(b_{n-1}~\textrm{or}~b_{n-2}),\textrm{if}~i=n\end{aligned}\right.
$$

代入求解即可，至于 $-1$ 的情况只需要再验算一遍我们刚才得到的 $a$ 数组就可以了。

## AC 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
#define endl putchar(10)
#define spc putchar(32)
using namespace std;

inline ll read()
{
    ll x=0,f=1; char c=getchar();

    while(c<48 || c>57)
    {
        if(c=='-') f=-1;
        c=getchar();
    }

    while(c>47 && c<58)
    x=(x<<1)+(x<<3)+c-48, c=getchar();
    return x*f;
}

inline void write(ll x)
{
    if(x<0) putchar('-'), x=-x;
    if(x>9) write(x/10);
    putchar(x%10+48); return;
}

ll t,n,a[100001],p[100001],bz;

int main()
{
    t=read();

    while(t--)
    {
        n=read(); bz=1;
        for(int i=1; i<n; ++i) a[i]=read();
        p[1]=a[1]&(a[1]|a[2]);
        for(int i=2; i<n; ++i) p[i]=a[i]|a[i-1]; 
        p[n]=a[n-1]&(a[n-1]|a[n-2]);

        for(int i=2; i<=n; ++i)
        {
            if((p[i]&p[i-1])!=a[i-1])
            {write(-1); bz=0; break;}
        }

        if(bz)
        {
            for(int i=1; i<=n; ++i)
            write(p[i]), spc;
        }

        endl;
    }

    return 0;
}
```

---

## 作者：wht_1218 (赞：0)

[题目传送门（洛谷）](https://www.luogu.com.cn/problem/CF1991B)

[题目传送门（CF）](https://codeforces.com/contest/1991/problem/B)

---

位与运算的结果 $b_i$ 的二进制位若是 $1$，则 $a_i,a_{i+1}$ 的二进制位必须是 $1$，$b_i$ 的二进制位是 $0$ 就无所谓了，只要**不都是 $1$ 就可**。

构造完后可以模拟一遍，如果不符就输出 `-1`。

懒得贴代码了。

~~怎么橙题题解还有空？~~

---

2024.8.24 改一下错字，麻烦请管理员过一下。

---

## 作者：zg_ji (赞：0)

## CF1991B题解

根据题目我们已经知道了 $b$ 数组是由 $a$ 数组按位或来的。那么我们由此可以反向推出 $a$ 数组，将其构造出来。

按位或运算规则为有 $1$ 为 $1$，全 $0$ 为 $0$。所以要构造 $a$ 数组，我们就可以用按位与，因为在好数组运算的过程中 $b_{i}$ 和 $b_{i+1}$ 的 $1$ 都会出现在 $a_{i}$ 身上。但是我们构造出来之后要去判断这个 $a$ 数组是不是好的数组。判断完之后就可以输出了。

### AC记录

![](https://cdn.luogu.com.cn/upload/image_hosting/2jmewcpx.png)

## AC代码

```
#include<bits/stdc++.h>
#define int long long
const int N=1e5+100; 
using namespace std;

int T;
int n;
int a[N],b[N];

signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--)
	{
		memset(a,0,sizeof(a));//多测不清空,徒留两行泪 
		cin>>n;
		bool f=true;
		for(int i=1;i<n;i++)
			cin>>b[i];
		a[1]=b[1],a[n]=b[n-1];
		for(int i=1;i<n-1;i++)
			a[i+1]=(b[i]|b[i+1]);//构造 
		for(int i=1;i<n;i++)
			if((a[i]&a[i+1])!=b[i])//判断 
				f=false;
		if(f)
		{
			for(int i=1;i<=n;i++) cout<<a[i]<<' ';
			cout<<'\n';
		}
		else cout<<-1<<'\n';
	}
	
	return 0;
	
}
```

---

## 作者：__XU__ (赞：0)

# CF1991B 题解

### 题目大意

给定一个长度为 $n-1$ 的数组 $b$， 要求构造一个长度为 $n$ 的序列 $a$ 使得对于每个位置 $i$ , 让 $a_i$ 和 $a_{i+1}$ 进行与运算,使其等于 $b_i$。

### 思路

与运算的性质：同 $1$ 则 $1$ 不同则 $0$。

若要满足题意，如果 $b_i$ 二进制下第 $j$ 位为 $1$, 那么对于二进制下的 $a_i,a_{i+1}$ 也因为 $1$ , 其它情况则随便。

我们就可以对此性质构造一个 $b$ 数组，最后再变例一遍 $b$ 数组判断是否满足条件即可。

#### 特别的

刚开始用了 `STL` 自带的 `__lg` 函数，结果 TLE 了， 感谢 [**xuweiyi**](https://www.luogu.com.cn/user/756805) 的帮助。

#### AC 记录

<https://codeforces.com/contest/1991/submission/275667717>

### code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
const int M=50+5;
using ll=long long;
int T;
ll sum[N][M];
ll a[N],c[N];
int k=0;
inline int lg(ll x){
    int ct=0;
    while(x>0) ct++,x/=2;
    return ct;
}
void solve(){
    int n;
    for(int i=1;i<=k;i++){
        for(int j=0;j<M;j++){
            sum[i][j]=0;
        }
        a[i]=c[i]=0;
    }
    cin>>n;
    k=n;
    for(int i=1;i<n;i++){
        cin>>a[i];
    }
    for(int i=1;i<n;i++){
        for(int j=0;j<=lg(a[i]);j++){
            if((a[i]>>j)&1==1){
                sum[i][j]=sum[i+1][j]=1;
            }
        } 
    }
    for(int i=1;i<=n;i++){
        ll ans=0;
        for(int j=0;j<M;j++){
            if(sum[i][j]==1){
                ans+=(1ll<<j);
            }
        }
        c[i]=ans;
    }
    for(int i=1;i<n;i++){
        if((c[i]&c[i+1])!=a[i]){
            cout<<-1<<'\n';
            return;
        }
    }
    for(int i=1;i<=n;i++){
        cout<<c[i]<<' ';
    }
    cout<<'\n';
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}
```
谢谢观看。

---

## 作者：Rubedo_N (赞：0)

# CF1991B AND Reconstruction 题解
## 思路
因为 $b_i=a_i\otimes a_{i+1}$，所以当 $a_i$ 和 $a_{i+1}$ 的第 $j$ 位上都是 $1$ 时，$b_i$ 的第 $j$ 位上会是 $1$。

将每一个 $b_i$ 转成二进制，如果在二进制下第 $j$ 位上是 $1$，那么 $a_i$ 和 $a_{i+1}$ 的第 $j$ 位就应该是 $1$，反之为 $0$。以此方法构造 $a$ 数组。
## AC Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T,n;
int ans[10010],b[10010];
signed main(){
	cin>>T;
	while(T--){//多测 
		memset(ans,0,sizeof(ans));//初始化 
		cin>>n;
		for(int i=1;i<n;i++)cin>>b[i];//数组b长为n-1 
		for(int i=1;i<n;i++){ 
			for(int j=0;j<=30;j++){ //a最长为30位
				if(b[i]>>j&1){
					ans[i]|=1<<j;
					ans[i+1]|=1<<j;
				}
			}
		}
		bool flag=true;
		for(int i=1;i<n;i++){
			if((ans[i]&ans[i+1])!=b[i]){//见上文 
				flag=0;//不存在好数组 
				break;
			}
		}
		if(flag){//存在好数组 
			for(int i=1;i<=n;i++)cout<<ans[i]<<" ";
			cout<<endl;
		}
		else cout<<-1<<endl;//不存在好数组 
	}
	return 0;
}
```

---

## 作者：postpone (赞：0)

提供一个较为朴素的思路。

由于 $a_i$ 由 $b_i$ 与 $b_{i + 1}$ 用和运算构成，那么对于 $a_i$ 每一位二进制为 $1$ 的位置，$b_i$ 和 $b_{i + 1}$ 在对应的位置上必然是 $1$。

举个例子，如果 $a_i = (5)_{10} = (101)_2$，则 $b_i$ 和 $b_{i + 1}$ 一定形如 $(1\rm{X}1)_2$，其中 $\rm{X}$ 表示不确定是什么，容易发现，当一个 $\rm{X}$ 确定为 $1$，另一个也就确定为 $0$ 了。

那 $X$ 在什么时候可以确定呢？接着上面的例子，如果 $a_{i + 1} = (3)_{10} = (010)_2$，则 $b_{i + 1} = (111)_2$，由此上述 $\rm{X}$ 就确定了，确定了 $b_{i + 1}$，也就确定了 $b_i$。

不妨以 $-1$ 表示已确定的 $0$，以 $0$ 表示不确定的数位，从前到后扫一遍即可。

```cpp
#include <bits/stdc++.h>
#define endl "\n"
using namespace std;
using ll = long long;

void solve() {
    int n;
    cin >> n;
    n--;

    vector<ll> a(n), b(n + 1);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector p(n, vector<int>(33));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 33; j++) {
            if (a[i] & (1LL << j))
                p[i][j] = 1;
        }
    }

    vector q(n + 1, vector<int>(33));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 33; j++) {
            if (p[i][j]) {
                // 若一个位置已经确定为 0，则不可能再确定为 1
                if (q[i][j] == -1) {
                    cout << -1 << endl;
                    return;
                }
                q[i][j] = q[i + 1][j] = 1;
            } else if (q[i][j] == 1) {
                // 若 b[i] 在这一位是 1，则 b[i + 1] 确定为 0
                q[i + 1][j] = -1;
            }
        }
    }
    // 默认 X 为 0，因为 0 & 0 = 0，1 & 0 = 0，取 0 肯定是合法的
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j < 33; j++) {
            if (q[i][j] == 1) {
                b[i] += (1LL << j);
            }
        }
    }
    for (auto i : b)
        cout << i << " ";
    cout << endl;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int _;
    cin >> _;
    while (_--)
        solve();
    return 0;
}
```

---

## 作者：Floating_Trees (赞：0)

## 题意
有一个长度为 $n-1$ 的序列 $b$，现在请你求出一个长度为 $n$ 的序列 $a$，使得对于每一个 $i(1\leq i < n )$ 都有 $a_i \operatorname{and} a_{i+1} = b_i$。
## 思路
我们观察一下样例，当 $b = \{1,2,3\}$ 是没有 $a$ 能满足条件的，我们将其转换为二进制观察：
$$
b_1 = 1 = (01)_2 \\
b_2 = 2 = (10)_2 \\
b_3 = 3 = (11)_2
$$
我们发现由于 $a_3$ 对于 $b_3$ 来说需要满足二进制最后一位应为 $1$，而对于 $b_2$ 来说需要为 $0$（因为 $a_2$ 二进制的最后一位要为 $1$），那么这样的话就矛盾了，显然是无解的。

那么我们可以发现如果 $b_i$ 的二进制的第 $j$ 位是 $1$ 的话，$a_i$ 和 $a_{i+1}$ 的二进制的第 $j$ 位也必须是 $1$，如果是 $0$ 的话那就尽量为 $0$，然后再按上面的来判断是否矛盾即可。

## 代码
```cpp
// Problem: B. AND Reconstruction
// Contest: Codeforces - Pinely Round 4 (Div. 1 + Div. 2)
// URL: https://codeforces.com/contest/1991/problem/B
// Memory Limit: 256 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)
 
#include <bits/stdc++.h>
//#include <bits/extc++.h>
#define ll long long
#define endl '\n'
 
using namespace std;
 
const int N = 1e5 + 10;
int n, b[N][40], a[N];
 
int to_int(int x)
{
	int res = 0;
	for (int i = 0;i <= 30;i++)
		if (b[x][i])
			res = res + (1 << i);
	return res;
}
 
void solve()
{
	cin >> n;
//	memset(b, 0, sizeof(b));
//	memset(a, 0, sizeof(a));
	for (int i = 1;i < n;i++)
	{
		a[i] = 0;
		cin >> a[0];
		for (int j = 0;j <= 30;j++)
			if (a[0] & (1 << j)) b[i][j] = 1;
			else b[i][j] = 0;
	}
//	cout << "yes" << '\n';
	a[1] = to_int(1), a[n] = to_int(n-1);
	for (int i = 2;i < n;i++)
	{
		for (int j = 0;j <= 30;j++)
		{
			if (b[i][j] == 1 && b[i-1][j] == 0 && (a[i-1] & (1 << j)))
			{
				cout << -1 << '\n';
				return ;
			}
			if (b[i][j] == 1 || b[i-1][j] == 1) a[i] = a[i] + (1 << j);
		}
	}
	for (int i = 1;i <= n;i++)
		cout << a[i] << " \n"[i == n];
}
 
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	
	int T; cin >> T;
	while (T--)
		solve();
	
	return 0;
}
```

---

## 作者：_ZHONGZIJIE0608_ (赞：0)

给你一个长度为 $N-1$ 的整数序列 $B$，要你构造一个长度为 $N$ 的序列 $A$ 使得 $A_i \& A_{i+1}=B_i$。$\&$ 表示按位与。

考虑 $A_1=B_1,A_n=B_{n-1}$。

对于中间的数，$B_i =A_i \& A_{i+1},B_{i+1}=A_{i+1}\& A_{i+2}$，所以 $A_i$ 要有 $B_{i-1}$ 和 $B_i$ 相同的二进制位上的 $1$，对于两者进行或运算取结果。

可以证明，如果这样构造的序列不合法就是无解的，输出 $-1$。

单组时间复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
int b[N],n,c[N];
signed main(){
	ios::sync_with_stdio(false);cin.tie(0),cout.tie(0);
	int T;cin>>T;while(T--){
		cin>>n;
		for(int i=1;i<n;++i)cin>>b[i];
		c[1]=b[1];
		for(int i=2;i<n;++i)c[i]=(b[i]|b[i-1]);
		c[n]=b[n-1];bool f=1;
		for(int i=1;i<n;++i){
			if((c[i]&c[i+1])!=b[i]){
				f=0;cout<<"-1\n";break;
			}
		}
		if(f){
			for(int i=1;i<=n;++i)cout<<c[i]<<' ';cout<<'\n';
		}
	}
	return 0;
}
```
[**Record**](https://codeforces.com/contest/1991/submission/273173106)

---

## 作者：Link_Cut_Y (赞：0)

拆位，考虑二进制的第 $x$ 位。如果 $b_i$ 的第 $x$ 位是 $1$ 则需要 $a_i$ 和 $a_{i + 1}$ 的第 $x$ 位全是 $1$。这样做完一遍再 check 答案是否合法。[submission](https://codeforces.com/contest/1991/submission/273295326)。

---

## 作者：OrinLoong (赞：0)

题意简述：给定一个长为 $N-1$ 的正整数序列 $B$ ，试构造一个正整数序列 $A$，使对于每一个 $B_i$ 都有 $B_i=A_i\operatorname{and}A_{i+1}$ 

做法：见到按位与，按位与是不用考虑进位的，因此按位考虑。  
根据与运算的性质，若 $B_i$ 某一位为 $1$，则 $A_i\operatorname{and}A_{i+1}$ 这一位也都要是 $1$，因此如果构造存在，那么这一部分 $1$ 是已经确定的。标记出这些 $1$ 后我们再反观那些这一位为 $0$ 的 $B_i$，如果此时它对应的 $A_i\operatorname{and}A_{i+1}$ 这一位都是 $1$，那么构造就失败了。否则，将除必要 $1$ 之外的其它这一位都填成 $0$，构造可以成功。

代码：
```cpp
#include <cstdio>
#include <cstring>
#include <bitset>
using namespace std;
const int MAXN=1e5+5,MAXD=31;
int T,N,A[MAXN],B[MAXN];
bool flag;
bitset<MAXN> isone;
int get_digit(int a,int k){return (a>>k)&1;}
int main(){
    scanf("%d",&T);
    while(T--){
        flag=1;
        memset(A,0,sizeof(A));
        scanf("%d",&N);
        for(int i = 1;i < N;i++)scanf("%d",&B[i]);
        for(int k = 0;k < MAXD;k++){
            isone.reset();
            for(int i = 1;i < N;i++)if(get_digit(B[i],k))isone[i]=isone[i+1]=1;
            for(int i = 1;i < N;i++)if(!get_digit(B[i],k)&&isone[i]&&isone[i+1]){flag=0;break;}
            for(int i = 1;i <= N;i++)if(isone[i])A[i]+=(1<<k);
            if(!flag)break;
        }
        if(flag)for(int i = 1;i <= N;i++)printf("%d ",A[i]);
        else printf("-1");
        printf("\n");
    }
    

    return 0;
}
```

---

