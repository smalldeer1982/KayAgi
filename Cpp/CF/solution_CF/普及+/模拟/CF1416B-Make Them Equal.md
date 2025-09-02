# Make Them Equal

## 题目描述

You are given an array $ a $ consisting of $ n $ positive integers, numbered from $ 1 $ to $ n $ . You can perform the following operation no more than $ 3n $ times:

1. choose three integers $ i $ , $ j $ and $ x $ ( $ 1 \le i, j \le n $ ; $ 0 \le x \le 10^9 $ );
2. assign $ a_i := a_i - x \cdot i $ , $ a_j := a_j + x \cdot i $ .

After each operation, all elements of the array should be non-negative.

Can you find a sequence of no more than $ 3n $ operations after which all elements of the array are equal?

## 样例 #1

### 输入

```
3
4
2 16 4 18
6
1 2 3 4 5 6
5
11 19 1 1 3```

### 输出

```
2
4 1 2
2 3 3
-1
4
1 2 4
2 4 5
2 3 3
4 5 1```

# 题解

## 作者：AFOier (赞：16)

注意到$a[i]$减的数与$a[j]$加的数相同，所以序列之和不变.

取平均值，若不为整数，则输出-1.

因为$i=1$可以最细化每个数的变化，故考虑所有操作围绕$a[1]$进行.

有一种方案为（以下$i∈[2,n]$）：

1.将$a[i]$变为$i$的倍数.

2.将$a[i]$变为0.

对于每个i重复操作1,2（这两个操作可以使$a[1]+=a[i],a[i]=0$）.

3.将$a[1]$的值平均分给每个$a[i]$.

这样操作次数为$3(n-1)$，符合要求.

考虑正确性：

对于1操作，因为$a[i] \geqslant 1$，所以在处理到第$i$个数时，$a[1]=sum[1,i-1] \geqslant i-1$.

又因为$a[i] \bmod i \leqslant i-1$,所以将$a[i]$变为$i$的倍数时，$a[1]$一定非负.

其余操作的显然不会使序列中出现负数.

```
#include <bits/stdc++.h>
using namespace std;
int a[100011];
int n, sum;
void solve() {
    scanf("%d", &n); sum = 0;
    for(int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        sum += a[i];
    }
    if(sum % n) {
        printf("-1\n");
        return;
    }
    sum /= n;
    cout << 3 * (n-1) << endl;
    for(int i = 2; i <= n; i++) {
        int x = a[i] % i;
        cout << 1 << " " << i << " " << (i - x) % i << endl;
        a[1] -= (i - x) % i; a[i] += (i - x) % i;
        cout << i << " " << 1 << " " << a[i] / i << endl;
        a[1] += a[i]; a[i] = 0; 
    }
    for(int i = 2; i <= n; i++) {
        cout << 1 << " " << i << " " << sum << endl;
        a[1] -= sum; a[i] += sum;
    }
}
int main() {
    int T;
    scanf("%d", &T);
    while(T--) solve();
    return 0;
}
```

---

## 作者：Ezis (赞：3)

~~这是一道数学题~~

首先，我们可以发现只要求出任意一种方案即可。

于是我们通过模拟样例得出，有一种保证只要 $3*(n-1)$ 步求可以得出答案：

1. 先让 $a[i]$ 能被 $i$ 整除。
1. 把 $a[i]$ 转移到 $a[1]$ 上。
1. 再把 $a[1]$ 分成 $n$ 组

注意：当 $ \sum_{}a[i]$ 不能被 $n$ 整除时，应该直接输出 $-1$。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,t,sum,b[10005],a[10005];
int main(){
	scanf("%d",&t);
	while(t--){
		sum=0;
		memset(a,0,sizeof(a));
		memset(b,0,sizeof(b));
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
			scanf("%d",&a[i]),sum+=a[i],b[i]=a[i]%i;
		if(sum%n!=0){
			printf("-1\n");
			continue;
		}
		printf("%d\n",3*(n-1));
		for(int i=2;i<=n;i++){
			printf("1 %d %d\n",i,(i-b[i])%i);
			if(a[i]%i!=0){
				a[1]=a[1]-((i-b[i])%i);
				a[i]=a[i]+((i-b[i])%i);
			}
			printf("%d 1 %d\n",i,a[i]/i);
			a[1]=a[1]+a[i];
			a[i]=0;
		}
		for(int i=2;i<=n;i++){
			printf("1 %d %d\n",i,sum/n);
			a[1]-=sum/n;
			a[i]=sum/n;
		}
	}
	return 0;
}
```


---

## 作者：A_Đark_Horcrux (赞：2)

首先，每次操作不会改变数的总和，因此最终每个数都会变为它们的平均数。因此可以发现无法操作的情况：平均数不为整数（或所有数之和无法被数的个数整除）。

```cpp
for(i=1;i<=n;i++) scanf("%d",&a[i]),s+=a[i];//计算和
	if(s%n!=0) {puts("-1"); continue;}//判断无法操作。
```

接下来是算法部分。

考虑到第一个位置可以给其他任意位置转移任意大小，因此可以先把所有的数尽可能往第一个位置上面堆，然后再从第一个位置拿下来分回去。

但是有这样的情况：

```cpp
1 1 1 1 3 11
//第五个位置，无法转移给第一个位置
//第六个位置，转移给第一个位置后，大于最终的结果（平均数）
```

因此对于无法转移的位置要先凑整，使得 $a_i \bmod i=0$ 然后再转移回第一个位置。

总结起来三步：

- 1. 凑整

- 2. 给到 1
 
- 3. 给回去。

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
struct operation
{
	int l,r; long long z;
	void print() {printf("%d %d %d\n",l,r,z);}
}c[100010];
long long ans,a[10010];
void Just_do_it(int x,int y,int z)//转移用的函数，方便
{
	c[++ans]=operation{x,y,z};//记录操作
	a[x]-=z*x,a[y]+=z*x;//真实操作
}
int T,n,s,t,i; bool f;
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		s=0,ans=0; f=1;
		memset(c,0,sizeof(c));
		memset(c,0,sizeof(a));//先清零
		scanf("%d",&n);
		for(i=1;i<=n;i++) scanf("%d",&a[i]),s+=a[i];
		if(s%n!=0) {puts("-1"); continue;}//判不行的情况
		s/=n;//算平均数
		for(i=2;i<=n;i++)
		{
			if(a[i]%i) Just_do_it(1,i,i-a[i]%i);//如果除不干净，先凑整
			Just_do_it(i,1,a[i]/i);//给到1
		}
		for(i=2;i<=n;i++) Just_do_it(1,i,s);//给回去。
		printf("%lld\n",ans);
		for(i=1;i<=ans;i++) c[i].print();//输出
	}
	return 0;
}
//一组测试凑整是否正确的样例
/*
1
22
6 12 3 14 5 4 3 15 15 8 11 6 4 18 2 6 8 24 14 2 8 32
*/
```


---

## 作者：Imiya (赞：1)

[题目链接](https://www.luogu.com.cn/problem/CF1416B)

修改两个数时 $a[i]:=a[i]-i\times x,a[j]:=a[j]+i\times x$，他们分别加减相同的数，因此 $\sum a$ 不变，所以若 $\sum a\not\equiv0\mod(n)$，则一定无解。

由于 $i=1$ 时能更精确地操作，考虑操作 $a[1]$ 和 $a[j](j\in[2,n])$。

1.若 $a[j]\not\equiv0\mod(j)$，用 $a[1]$ 把 $a[j]$ 补成 $j$ 的倍数。

2.$a[1]:=a[1]+a[j],a[j]:=0$。

3.将 $a[1]$ 平均分配给 $a[j](j\in[2,n])$ 。

操作一和二遍历完数列后执行操作三即可。


正确性

- 对于操作一，$a[j]$ 向上补成 $j$ 的倍数，所以 $x$ 大于 $0$。遍历到 $j$ 时，因为原数组中每个数都是大于等于 $1$ 的，所以此时 $a[1]\ge j-1$，而设$a[j]$ 向上补 $y$ 成 $j$ 的倍数，则 $y\in[1,j-1]$，$\therefore a[1]\ge y$。所以进行操作一时能保证 $x\ge0$，数列 $a$ 时刻非负。
- 对于操作二，因为 $a[j]\equiv0\mod(j)$，所以存在三元组 $(j,1,x)$ 使得 $a[j]:=0,a[1]:=a[1]+a[j],x\ge 0$。
- 对于操作三，因为 $a[1]=\sum a,a[j]=0(j\in[2,n]),1\equiv0\mod(z)(z\in \mathbb{Z})$，
所以存在 $n-1$ 个三元组使得数列中每个数相同。
- 操作一最多执行 $n-1$ 次，操作二执行 $n-1$ 次，操作三执行 $1$ 次，总三元组个数不超过 $n\times3-3$。

代码
```cpp
#include<iostream>
using namespace std;
const int N=10100;
int n,a[N],sum;
void init(){
    cin>>n;
    sum=0;
    for(int i=1;i<=n;i++)cin>>a[i],sum+=a[i];
}
struct node {
    int i,j,x;
}res[N<<2];
int main(){
//    freopen("read.in","r",stdin);
    int t;
    cin>>t;
    while(t--){
        init();
        int k=0;
        if(sum%n){
            printf("-1\n");
            continue;
        }
        sum/=n;
        for(int i=2;i<=n;i++){
            if(a[i]%i){
                res[++k]={1,i,i-a[i]%i};
                a[1]-=i-a[i]%i;
                a[i]+=i-a[i]%i;
            }
            res[++k]={i,1,a[i]/i};
            a[1]+=a[i];
            a[i]=0;
        }
        for(int i=2;i<=n;i++)res[++k]={1,i,sum};
        cout <<k<< endl;
        for (int j = 1; j <= k; j++)printf("%d %d %d\n", res[j].i, res[j].j, res[j].x);
    }
    return 0;
}
```

---

## 作者：SSerxhs (赞：1)

构造思路：显然 $i=1$ 可以随意调整，然而由于不能出现负数可能 $a_1$ 不够用，那就先将所有数转移到 $a_1$，可以通过 $1\rightarrow i$ 调整 $a_i$ 使 $i|a_i$ 再全部转移到 $a_1$。

正确性：由于需要转移的量 $(i-a_i \mod i)\mod i< i$ ，而操作完 $i-1$ 个数的 $a_1$ 至少有 $i-1$，所以不会出现负数

```
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e4+2;
int a[N];
int n,c,fh,i,ans,anss,t,x,j,sum;
inline void read(int &x)
{
	c=getchar();fh=1;
	while ((c<48)||(c>57))
	{
		if (c=='-') {c=getchar();fh=-1;break;}
		c=getchar();
	}
	x=c^48;c=getchar();
	while ((c>=48)&&(c<=57))
	{
		x=x*10+(c^48);
		c=getchar();
	}
	x*=fh;
}
int main()
{
	read(t);
	while (t--)
	{
		read(n);sum=0;
		for (i=1;i<=n;i++) {read(a[i]);sum+=a[i];}
		if (sum%n) {puts("-1");continue;}
		ans=(n-1)*2;
		for (i=2;i<=n;i++) if (a[i]%i) ++ans;
		printf("%d\n",ans);
		for (i=2;i<=n;i++)
		{
			if (a[i]%i)
			{
				printf("%d %d %d\n",1,i,x=i-a[i]%i);
				a[i]+=x;a[1]-=x;
			}
			printf("%d %d %d\n",i,1,a[i]/i);
			a[1]+=a[i];a[i]=0;
		}
		for (i=2;i<=n;i++) printf("%d %d %d\n",1,i,a[1]/n);
	}
}
```

---

## 作者：Daniel_yao (赞：0)

# Solve

没有第一眼看出来解法。

先判断无解：由于每一次操作涉及 $+x\cdot i$ 与 $-x\cdot i$，所以序列的总和不变。因此最后想要每个数都一样必须让这 $n$ 个数的平均数填满 $n$ 个空，所以总和 $sum$ 不能被 $n$ 整除则无解。

然后发现 $i=1$ 的自由度是很高的（因为 $1$ 是所有自然数的因数，可以很轻松的被放与拿）。所以大致的思路就是每一次将 $a_i$ 转移至 $a_1$ 上，然后再平均分配给每一个数即可。

转移的过程很简单，就是对于 $a_i$ 先凑 $i$ 的倍数，凑的时候直接拿 $a_1$ 来用，凑完以后直接放回 $a_1$。如果 $a_i$ 本身就是 $i$ 的倍数了，直接放到 $a_1$ 即可。

而 $a_1$ 是一定够补的，因为第 $i$ 个空最多要补 $i-1$，而最坏的情况就是前 $i-1$ 个数都是 $1$，而它们现在都放在 $a_1$ 了，也就是正好能够补上 $i$ 的空。

发现最后操作数不会超过 $3(n-1)$，总时间复杂度 $O(n)$，符合题意，包能过。

# Code

```cpp
#include<bits/stdc++.h>
#define int long long
#define For(i,l,r) for(int i=l;i<=r;++i)
#define FOR(i,r,l) for(int i=r;i>=l;--i)

using namespace std;

const int N = 1e5 + 10;

struct Ans {
  int i, j, x;
};

int T, n, a[N];

void solve() {
  vector<Ans> ans;
  int sum = 0, cnt = 0;
  cin >> n;
  For(i,1,n) cin >> a[i], sum += a[i];
  if(sum % n != 0) {
    cout << "-1\n";
    return ; 
  }
  sum /= n;
  For(i,2,n) {
    if(a[i] % i == 0) {
      ans.push_back((Ans){i, 1, a[i] / i});
      continue;
    }
    int k = (int)(ceil(1.0 * a[i] / i) * i);
    ans.push_back((Ans){1, i, k - a[i]});
    ans.push_back((Ans){i, 1, k / i});
  }
  For(i,2,n) ans.push_back((Ans){1, i, sum});
  cout << ans.size() << '\n';
  for (int i = 0; i < ans.size(); ++i) cout << ans[i].i << ' ' << ans[i].j << ' ' << ans[i].x << '\n';
}

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  cin >> T;
  while(T--) solve();
  return 0;
}
```

---

## 作者：ben090302 (赞：0)

首先可以关注到，若干次操作后数组和是不会改变的，于是最后整个数组一定会变成平均数，只需要判断平均数是否为整数就可以判去无解。

考虑构造解。$1$ 有一个非常好的地方，我们从 $a_1$ 往别的地方输送数的时候不需要考虑倍数问题。于是我们有一个简单的思路：用 $a_1$ 把 $a_2$ 补成 $2$ 的倍数，然后全部拿回 $a_1$，再用 $a_1$ 补 $a_3$ 再拿回来，以此类推。

这样做之多需要 $3(n-1)$ 次的操作，但是有一个小问题就是：不会有负数吗？

没有！我们证明一下。

由于 $a$ 数组初始全部大于等于 $1$，而 $a_2$ 跟大于等于他的第一个 $2$ 的倍数的差为为 $0$ 或 $1$，而我们此时 $a_1$ 至少有 $1$，所以可以补上，然后 $a_1$ 就至少有 $2$ 了，类似这样归纳，我们发现再结束 $i$ 的拿去之后我们的 $a_1$ 至少有 $i$，而补充下一个至多只需要 $i$ 就够了，所以这样构造是合法的。

code：

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T;
int n;
int sum;
struct node{
    int i,j,x;
};
int a[100005];

void work(){
    cin>>n;    
    sum=0;
    for(int i=1;i<=n;i++){
        cin>>a[i];sum+=a[i];
    }
    if(sum%n!=0){
        cout<<"-1\n";
        return ;
    }
    sum/=n;
    vector<node> ans;
    for(int i=2;i<=n;i++){
        int x=(i-a[i]%i)%i;
        if(x!=0){
            ans.push_back({1,i,x});
            a[1]-=x,a[i]+=x;
        }
        ans.push_back({i,1,a[i]/i});
        a[1]+=a[i],a[i]=0;
    }
    
    for(int i=2;i<=n;i++){
        ans.push_back({1,i,sum-a[i]});
    }
    cout<<ans.size()<<"\n";
    for(int i=0;i<ans.size();i++){
        cout<<ans[i].i<<" "<<ans[i].j<<" "<<ans[i].x<<"\n";
    }
} 

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>T;
    while(T--){
        work();
    }
}
```

---

## 作者：UncleSam_Died (赞：0)

### 解题思路

观察可以发现，每次操作后序列元素之和不变，那么我们可以将每一次操作看作是 $a_i$ 向 $a_j$ 移动了 $i\times x$。由此可得，若序列和 $sum\bmod n\not=0$，那么一定无解，否则一定存在一个合法的操作方案。

因为每次移动时移动的数应为 $i$ 的倍数，所以 $a_1$ 可以向任意元素移动任意大小不超过 $a_1$ 的数，那么我们考虑先将所有数全部移动到 $a_1$，再由 $a_1$ 平分给 $a_2,\dots,a_n$。但是这种情况先可能存在一个 $a_j$ 使得 $a_j$ 不能整除 $j$，那么我们需要使用 $a_1$ 先将 $a_j$ 补为 $j$ 的倍数然后再全部移向 $a_1$。

### AC 代码
```cpp
#include<stdio.h>
#include<stdlib.h>
#include<vector>
#include<algorithm>
#include<set>
#define N 100005

int n,a[N],sum,mint[N];
struct ANS{
    int i,j,x;
};

struct Point{
    int cos;
    int val;
    int pos;
};
struct cmp{
    inline bool operator ()(
        const Point A,
        const Point B
    ) const {
        if(A.cos!=B.cos)
            return A.cos<B.cos;
        return A.val>B.val;
    }
};
inline void work(){
    scanf("%d",&n);sum=0;
    std::vector<ANS> ans;
    for(register int i=1;i<=n;++i)
        scanf("%d",&a[i]),sum+=a[i];
    if(sum%n!=0){puts("-1");return;}

    int Average=sum/n;
    
    for(register int i=2;i<=n;++i){
        int res=i-(a[i]%i);if(a[i]%i){
            ans.push_back({1,i,res});
            a[1]-=res,a[i]+=res;
        }ans.push_back({i,1,a[i]/i});
    }

    for(register int i=2;i<=n;++i)
        ans.push_back({1,i,Average});

    printf("%d\n",ans.size());
    for(auto now:ans){
        printf("%d ",now.i);
        printf("%d ",now.j);
        printf("%d\n",now.x);
    }
}
signed main(){
    int T;scanf("%d",&T);
    while(T--) work();
}
```

---

## 作者：STDquantum (赞：0)

首先呢，如果令 $i$ 等于 $1$，那么只要 $a_1$ 足够大，就可以给任意元素赋任何值。

那么我们有一个小小的想法：把所有下标不是一的元素用 $2n$ 次操作清零，这样就可以用 $n-1$ 次操作把所有平均数从 $a_1$ 搬过来。

怎么把下标不是一的元素清零呢？肯定是要做减法，但是减法只能减下标的倍数啊，所以我们就先把所有 $i\mid a_i$ 的挪到 $1$ 处（设不满足 $i\mid a_i$ 的个数为 $cnt$），步数 $n-1-cnt$。

现在只剩下那些不能整除的数了，我们可以从 $1$ 那里借一些数，借到 $i\mid a_i$ 为止，然后再用一步全挪回 $1$，每个数需要两步，总步数 $2\cdot cnt$。

于是当 $cnt=n-1$ 时，最大步数就是 $2\cdot cnt+n-1=3n-3$，可以通过本题。

注：代码中 $cnt$ 为操作个数，实际并不需要记录有多少数不能被下标整除，只是分析可行性会用到。

```cpp
const int N = 1e4 + 10;

int cnt; // 操作个数
struct O { // 记录操作
    int i, j, x;
} o[N << 2];
inline void operate(int i, int j, int x) { // 节省代码长度
    write(i), putchar(' ');
    write(j), putchar(' ');
    write(x), putchar('\n');
}

int n, t, a[N];
inline void main() {
    for (read(t); t--; cnt = 0) { // 记得清空cnt
        read(n);
        int sum = 0;
        for (int i = 1; i <= n; ++i) read(a[i]), sum += a[i]; // 记录一下序列和
        if (sum % n) { // 不能使所有元素相等
            puts("-1");
            goto school; // 节省bool变量，直接跳转
        }
        sum /= n; // 最后的平均值
        for (int i = 2; i <= n; ++i) {
            if (a[i] % i == 0) { o[++cnt] = (O){i, 1, a[i] / i}; } // 整除就一次全拿过去
        }
        for (int i = 2; i <= n; ++i) {
            if (a[i] % i) { // 不整除就先凑齐i的倍数再全拿到1
                o[++cnt] = (O){1, i, i - a[i] % i};
                o[++cnt] = (O){i, 1, a[i] / i + 1};
            }
        }
        for (int i = 2; i <= n; ++i) { o[++cnt] = (O){1, i, sum}; } // 分配
        write(cnt), putchar('\n');
        for (int i = 1; i <= cnt; ++i) {
            operate(o[i].i, o[i].j, o[i].x);
        }
    school:;
    }
}
```

# 

---

