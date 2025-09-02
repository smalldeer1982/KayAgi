# [AGC016B] Colorful Hats

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc016/tasks/agc016_b

$ N $ 匹の猫がいます。 猫には $ 1 $ から $ N $ まで番号が振られています。

各猫はある色の帽子を被っています。 猫 $ i $ は「自分を除く $ N-1 $ 匹の猫が被っている帽子の色の種類数はちょうど $ a_i $ である」と言っています。

すべての猫の発言と矛盾しないような帽子の色の組合せが存在するか判定してください。

## 说明/提示

### 制約

- $ 2\ <\ =\ N\ <\ =\ 10^5 $
- $ 1\ <\ =\ a_i\ <\ =\ N-1 $

### Sample Explanation 1

例えば、猫 $ 1 $, $ 2 $, $ 3 $ の帽子の色がそれぞれ赤、青、青ならば、すべての猫の発言と矛盾しません。

### Sample Explanation 2

猫 $ 1 $ の発言から、猫 $ 2 $, $ 3 $ の帽子の色は同一です。 また、猫 $ 2 $ の発言から、猫 $ 1 $, $ 3 $ の帽子の色は同一です。 よって、猫 $ 1 $, $ 2 $ の帽子の色は同一ですが、これは猫 $ 3 $ の発言に矛盾します。

## 样例 #1

### 输入

```
3
1 2 2```

### 输出

```
Yes```

## 样例 #2

### 输入

```
3
1 1 2```

### 输出

```
No```

## 样例 #3

### 输入

```
5
4 3 4 3 4```

### 输出

```
No```

## 样例 #4

### 输入

```
3
2 2 2```

### 输出

```
Yes```

## 样例 #5

### 输入

```
4
2 2 2 2```

### 输出

```
Yes```

## 样例 #6

### 输入

```
5
3 3 3 3 3```

### 输出

```
No```

# 题解

## 作者：Ebola (赞：13)

### 题意

有n个人，每个人头顶上有一个某种颜色帽子，所有人都能看到除自己之外所有人的帽子颜色。现在所有人都告诉了你他们看到了几种颜色，请问是否存在一种扣帽子的方案，满足所有人的观察结果

### 题解

我们让每个人分别看到多少种颜色构成序列A，设min为A中的最小值，max为A中的最大值，cnt为A中min值出现的次数

**结论一：若$max-min>1$，则不存在合法构造方案**

证明：假设甲看到了$x$种颜色，乙看到了$y$种颜色。若甲的帽子是独一无二的，乙的帽子也是独一无二的，则$x=y$；若甲的帽子是独一无二的，乙的帽子不是独一无二的，则$y=x+1$；若甲的帽子不独一无二的，乙的帽子是独一无二的，则$x=y+1$；若甲的帽子不是独一无二的，乙的帽子也不是独一无二的，则$x=y$。所以$x$与$y$的差值必然不能超过。而$1$由于甲和乙是对于任意两人而言的，所以为了让任意两人都满足这个性质，必然有$max-min>1$

**结论二：若$max=min$，则要么$cnt=n-1$，要么$2\times cnt\leq n$，否则不存在合法构造方案**

证明一：当且仅当所有人的帽子都是独一无二时，有$cnt=n-1$，此时$max=min$

证明二：若甲的帽子是独一无二的，乙的帽子不是独一无二的，那么甲必然比乙少看到一种颜色，不满足$min=max$，所以甲和乙的帽子状态不能不同。由于甲和乙是对任意两人而言的，故如果他们的帽子都是独一无二的，那么情况与“证明一”相同。如果他们的帽子都不是独一无二的，那么每种颜色的帽子必然多于两顶，所以必然要满足$2\times cnt\leq n$，才能有合法构造方案

**结论三：若$max=min+1$，则要么$min<cnt$，要么$n-cnt<2(max-cnt)$，否则都存在合法构造方案**

证明一：考虑$cnt$的本质含义。每个人的帽子只有两种可能：“独一无二”和“不独一无二”。假如在$max=min+1$的情况下，一个人看到的颜色是$min$个，那么说明他的帽子是独一无二的。所以$cnt$实质上是独一无二帽子的数量。而在这种情况下，必然存在至少一对不独一无二的帽子，所以对于一个拥有独一无二帽子的人来说，他能看到除自己以外的所有独一无二的颜色，这里有$cnt-1$种，同时他还能看到至少一种不独一无二的颜色，所以他至少应该看到$cnt$种颜色。根据上述推导，此时的合法构造应该满足$min\geq cnt$

证明二：因为$cnt$是独一无二的帽子数量，同时也是拥有独一无二帽子的人数，所以$n-cnt$是拥有不独一无二帽子的人数。一个拥有不独一无二帽子的人，可以看到当前的所有颜色，所以此时$max$是颜色总数，那么$max-cnt$就是不独一无二颜色的数量。因为帽子要不独一无二，所以每种颜色至少要有两个，那么此时显然需要满足$n-cnt\geq 2(max-cnt)$才有合法方案

**根据上述三个结论直接做即可**

```cpp
#include<bits/stdc++.h>
#define good {puts("No");return 0;}
#define Hao {puts("Yes");return 0;}
using namespace std;

const int S=(1<<20)+5;
char buf[S],*H,*T;
inline char Get()
{
	if(H==T) T=(H=buf)+fread(buf,1,S,stdin);
	if(H==T) return -1;return *H++;
}
inline int read()
{
	int x=0;char c=Get();
	while(!isdigit(c)) c=Get();
	while(isdigit(c)) x=x*10+c-'0',c=Get();
	return x;
}

inline void upmin(int &x,const int &y){if(y<x) x=y;}
inline void upmax(int &x,const int &y){if(y>x) x=y;}

int a[100010],n;

int main()
{
	n=read();
	int mn=n+1,mx=0;
	for(int i=1;i<=n;i++)
	{
		a[i]=read();
		upmin(mn,a[i]);
		upmax(mx,a[i]);
	}
	if(mx>mn+1) good
	if(mx==mn)
	{
		if(mn==n-1) Hao
		if(2*mn<=n) Hao
		else good
	}
	else
	{
		int cnt=0;
		for(int i=1;i<=n;i++) cnt+=(a[i]==mn);
		if(mn<cnt) good
		if(n-cnt<2*(mx-cnt)) good
		else Hao
	}
	return 0;
}
```

---

## 作者：critnos (赞：7)

第一道老老实实做出的 AGC 思维题 get。

分析：

使用上帝视角观察，会看到什么？

看到的是颜色的不同种类数，设为 $x$。

此时代进一只猫的视角，会看到什么？

若这只猫头上的颜色不是唯一的，则仍会看到 $x$；否则会看到 $x-1$。

所以整个序列只由 $n-s$ 个 $x$ 和 $s$ 个 $x-1$ 组成。

序列极差 $>1$ 的情况答案就是 No。

一般的，先考虑 $0<s<n$ 的情况。

既然有 $s$ 只猫代进去看到的颜色数会减 $1$，

就说明有 $s$ 个唯一的颜色。

那么可以倒推出有 $x-s$ 个不唯一的颜色。

既然不唯一，那么每个颜色至少要两个。

除掉那些唯一的颜色，我们还有 $n-s$ 个帽子可以用。

就是说 $2(x-s)\le n-s$。

然后 $x-s$ 要 $>0$。

不能 $=0$ 的原因是，若 $x-s=0$ 则表示没有不唯一的颜色。此时不符合 $0<s<n$ 的前提。

特别的，需要讨论 $s=0$ 的情况（你也可以说是 $s=n$），此时序列由 $n$ 个 $p$ 组成。

此时没有猫看到的颜色比别的猫少，只有两种情况：

要么是每个帽子的颜色都是唯一的，要么没有唯一的颜色。

若每个帽子的颜色都是唯一的，那么 $p=n-1$；

若没有唯一的颜色，那么这时 $p=x$，就是说有 $p$ 种颜色。

每种颜色至少要两个，即 $2p\le n$。

做完了。不做文字总结了，看代码比较方便：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n,mn=1e9,mx=-1e9,x,i,s=0;
	scanf("%d",&n);
	for(i=1;i<=n;i++)
	{
		scanf("%d",&x);
		if(x<mn)
		{
			s=1;
			mn=x;
		}
		else s+=x==mn;
		mx=max(mx,x);
	}
	if(mx-mn>1)
		cout<<"No";	
	else if(mx==mn)
	{
		if(mn==n-1||mn*2<=n)
			cout<<"Yes";
		else
			cout<<"No";
	}
	else if(mx-s>0&&(mx-s)*2<=n-s)
		cout<<"Yes";
	else
		cout<<"No";
}
```


---

## 作者：ModestCoder_ (赞：6)

手摸几个样例之后我们可以发现，每个人看到的帽子数之差必然<=1

然后我们根据$a_1...a_n$排序

然后

- $a_1=a_n$，意思是，每个人看到的帽子个数相同，那么有两种情况，一种是所有人都不相同，那么$a_i$必须满足$a_i=n-1$；或者是帽子情况被分成了几段，每段的个数>1，就是$2a_i<=n$。以上两种情况都是yes，否则no
- $a_1+1=a_n$，然后$a_i=a_1$的话，那么$i$的帽子是独一无二的，$a_i=a_n$的话，那么$i$存在另一个人与$i$帽子颜色相同，所以令$a_i=a_1$的个数为$cnt$，满足$cnt<a_n且2(a_n-cnt)<=n-cnt$就是yes，否则no
- $a_1+1<a_n$，直接no

Code：

```cpp
#include <bits/stdc++.h>
#define maxn 100010
using namespace std;
int a[maxn], n;

inline int read(){
	int s = 0, w = 1;
	char c = getchar();
	for (; !isdigit(c); c = getchar()) if (c == '-') w = -1;
	for (; isdigit(c); c = getchar()) s = (s << 1) + (s << 3) + (c ^ 48);
	return s * w;
}

int main(){
	n = read();
	for (int i = 1; i <= n; ++i) a[i] = read();
	sort(a + 1, a + 1 + n);
	if (a[n] > a[1] + 1) return puts("No"), 0;
	if (a[1] == a[n]){
		if (a[1] * 2 <= n || a[1] + 1 == n)
			puts("Yes");
		else puts("No");
	} else{
		int cnt = 0;
		for (int i = 1; i <= n; ++i)
			if (a[i] == a[1])
				++cnt;
			else break;
		if (cnt < a[n] && (a[n] - cnt) * 2 <= (n - cnt))
			puts("Yes");
		else puts("No");
	}
	return 0;
}
```


---

## 作者：ycy1124 (赞：3)

### 题意
有 $n$ 只猫，每只猫有一顶一种颜色的帽子。现在给出每只猫能看到的其它猫的帽子的颜色种数，试问有没有一种构造方案能使它满足。
### 思路
首先观察样例，很容易将输入分成两类去判断。第一种是所有猫看到的帽子颜色的数量全部相等，另一种是不相等。

先考虑第一种：此时发现，如果所有猫能看到的都等于 $n-1$ 是可以的。接着继续考虑不等于 $n-1$ 的情况。在这种情况中，一定是有一种颜色的帽子的个数大于等于 $2$ 的。我们更进一步去考虑，如果在这种情况下有一种颜色的帽子的数量为 $1$，那么戴着这个帽子的猫看到的颜色数量一定不等于那些帽子颜色出现多次的猫看到的颜色数量。于是是不存在帽子的颜色只出现一次的。而一种颜色的出现次数大于等于 $2$ 的时候，再多一些其实对答案并无影响，因为无论哪只猫都一定能看到这个颜色。于是我们只需要判断这个数是不是等于 $n-1$ 或小于等于 $\frac{n}{2}$ 即可。

接下来考虑第二种情况：不难得出如果看到颜色最多的猫看到的颜色比看到颜色最少的猫看到的颜色多超过一种，那么是不满足的。因为一只猫的帽子只有一种颜色，所以每只猫最多只会看不到自己的帽子的颜色，不可能大于 $1$。并且那些看到的颜色数少的那一类猫，他们的帽子颜色出现次数等于 $1$。此时可以得到第一个判断：看到的颜色数少的猫的个数一定小于等于他们看到的颜色数。因为后面看的颜色数多的猫的帽子的颜色至少一种，而看的少的的颜色数等于看的少的猫的数量，如果这个数大于他们所能看到的颜色数加一那么就一定不能构造出来了。并且由于所有看的颜色数多的猫的帽子颜色的出现次数一定大于等于 $2$，我们可以得到第二个判断：看的颜色数少的猫的个数加看的颜色数多的猫的个数除以二向下取整一定大于等于看的颜色数多的猫看到的颜色数。因为最多就这么多种颜色，如果看的多的猫看的比这个还多就一定构造不出来了。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[100005];
int main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    sort(a+1,a+n+1);
    if(a[1]==a[n]&&(a[1]==n-1||a[1]<=n/2)){
        cout<<"Yes";
        return 0;
    }
    else if(a[n]-a[1]==1){
        int tmp=1;
        for(tmp;a[tmp]==a[tmp+1];tmp++){}//找到两种猫的分界处
        if((n-tmp)/2+tmp>=a[n]&&tmp<=a[1]){//满足条件
            cout<<"Yes";
            return 0;
        }
    }
    cout<<"No";
    return 0;
}
```
[AC 记录](https://www.luogu.com.cn/record/203034542)。

---

## 作者：_acat_ (赞：3)

解封后第一篇题解，写的太烂的话勿喷。/kk
## 题目大意

有 $n$ 个人，每个人带着一个印有数字帽子，给出每个人能看到的帽子（即其他 $n-1$ 个人的帽子）的数字种数 $a_i$，问是否可以构造出合法的情况。


## 思路
我们发现不同人的 $a$ 最多只会相差 $1$，而产生差别的原因在于一个人的帽子是否是独一无二的。我们按照这个思路去讨论判断即可。

- 如果 $a$ 相差大于 $1$，则不合法。

- 如果 $a$ 全相等：
1. 一种情况是每个人的帽子都是独一无二的，那 $a=n-1$ 合法。

2. 一种情况是每个人的帽子都不是独一无二的：
> - $a \ge 1$，大家帽子都一样取等；
> - $a \le n \div 2$ 大家帽子两两相同取等，如果是奇数那就有一种三人相等的帽子。

如果 $a$ 恰好相差 $1$：设 $x$ 表示独一无二帽子的人数，$y$ 表示非独一无二帽子的人数，$ct$ 表示读入的帽子数（取 $a$ 较大的那个）。

$ct \ge x+1$，$y$ 个人的帽子都相同取等。

$ct \le x+y \div 2$，$y$ 个人的帽子两两相同取等，奇数同上。

---

## 作者：ttq012 (赞：2)

+ 任意两只猫看到的帽子的不同颜色的数量的差值的绝对值一定不会超过 $1$。
  + 原因：最多只会减少一个帽子。一定不会出现减少两个颜色的帽子的情况。

然后考虑按照 $a$ 数组从小到大排序。

+ 如果 $a_1 = a_n$，那么有可能出现下面的几种情况：
  + 所有人的帽子都相同。那么满足 $i\in [1,n]$，$a_i=n-1$。也就是 $a_1 = n - 1$。
  + 每一种颜色的帽子都至少出现了两次。那么满足 $i\in [1,n]$，$a_i = d$。其中 $d$ 为有多少个不同的颜色。那么满足 $i\in [1,n]$，$2\times a_i \le n$，也就是 $2\times a_n\le n$。
+ 如果 $a_1 + 1 = a_n$，那么设 $i$ 为满足条件 $a_1 = a_i$ 且 $i$ 最大的 $i$。
  + 有 $n-i$ 个人少看见一种颜色的帽子，那么一定有 $n-i$ 种颜色满足这个颜色的帽子有且只有一个。另外的 $i$ 个人头上戴的帽子一定满足至少还有一个人和它带的帽子的颜色一样。
  + 如果 $a_1-i+1<1$ 那么明显无解。
  + 如果 $(a_1 - i + 1)\times 2 + i\le n$ 那么是有解的。
  + 否则无解。

```cpp
#include <bits/stdc++.h>

using namespace std;

int a[1010010];

int main()
{
  int n;
  cin >> n;
  for (int i = 1; i <= n; i ++)
    cin >> a[i];
  sort (a + 1, a + n + 1);
  int abs = a[n] - a[1];
  if (abs > 1)
    cout << "No\n";
  else if (abs == 0)
  {
    if (a[1] == n - 1)
      cout << "Yes\n";
    else if (2 * a[n] <= n)
      cout << "Yes\n";
    else
      cout << "No\n";
  }
  else
  {
    int p;
    for (p = 2; p <= n; p ++)
      if (a[p] != a[1])
        break;
    int i = p - 1;
    int fd = i, d = n - i;
    int t = a[1] - i + 1;
    if (t < 1)
      cout << "No\n";
    else if (t * 2 + i <= n)
      cout << "Yes\n";
    else
      cout << "No\n";
  }
  return 0;
}

```



---

## 作者：_Life_ (赞：1)

第一道自己做的AGC，发篇题解纪念一下（大雾）

### 题意
有 $n$ 只猫，每只猫带着某种颜色的帽子，给出每只猫能看到（其他 $n-1$ 只猫）的帽子颜色种数 $a_i$，问是否可以构造出合法帽子种类序列。

$2 \leq n \leq 10^5$，$1 \leq a_i \leq n-1$

### 题解

不难发现只存在 $\min(a)=\max(a)$ 或 $\min(a)+1=\max(a)$ 两种情况，否则无解。

为了叙述方便，我们称独一无二的帽子为奇异帽子，这种颜色存在两顶以上的为平凡帽子。

- $\min(a)=\max(a)$，要么所有人都带奇异帽子，要么所有人都带平凡帽子。
	- 所有人都带奇异帽子：每个人都会看到 $n-1$ 种不同的帽子。
	- 所有人都带平凡帽子：至少需要 $2*\min(a)$ 顶帽子。
	- 否则无解
- $\min(a)+1=\max(a)$，看到 $\min(a)$ 种帽子的人肯定带奇异帽子，看到 $\max(a)$ 种帽子的人肯定带平凡帽子。记 $\operatorname{num}(\min)$ 为看到 $\min(a)$ 种帽子的人数，$\operatorname{num}(\max)$ 为看到 $\max(a)$ 种帽子的人数。
	- 如果所有带平凡帽子的人帽子颜色都一样，帽子种类数取到最小值 $\operatorname{num}(\min)+1$。
	- 如果所有带平凡帽子的人帽子每种只有两顶，帽子种类数取到最大值 $\operatorname{num}(\min)+\lfloor \dfrac{\operatorname{num}(\max)}{2}\rfloor$。
	- 不难发现此时 $\max(a)$ 为帽子种类数量，如果帽子种类数量在区间 $[\operatorname{num}(\min)+1,\operatorname{num}(\min)+\lfloor \dfrac{\operatorname{num}(\max)}{2}\rfloor]$ 内，则有解。

### 代码
```cpp
#include<bits/stdc++.h>
//#define int long long
//#define mod 1000000007
#define rep(i,j,k) for(int i=j;i<=k;i++)
#define per(i,j,k) for(int i=j;i>=k;i--)
using namespace std;
inline void chkmax(int &a,int b){a=max(a,b);}
inline void chkmin(int &a,int b){a=min(a,b);}
typedef pair<int,int> pii;
inline int read()
{
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+(c^'0');c=getchar();}
	return x*f;
}
inline void read(int &x){x=read();}
inline void write(int x)
{
	if(x<0){putchar('-');x=-x;}
	if(x>9){write(x/10);}putchar(x%10+'0');
}
inline void write(int x,char c){write(x),putchar(c);}
int n;
vector <int> vec;
#define yes return puts("Yes"),0
#define no return puts("No"),0;
signed main()
{
	read(n);
	rep(i,1,n)vec.push_back(read());
	sort(vec.begin(),vec.end());
	int minx=vec.front(),maxx=vec.back();
	if(minx==maxx)
	{
		if(minx==n-1)yes;
		if(2*minx<=n)yes;
		no;
	}
	else if(minx+1==maxx)
	{
		int mintot=count(vec.begin(),vec.end(),minx);
		int maxtot=count(vec.begin(),vec.end(),maxx);
		int ansmin=mintot+1;
		int ansmax=mintot+maxtot/2;
		if(ansmin<=maxx&&maxx<=ansmax)yes;
		else no;
	}
	else no;
}
```

---

## 作者：断清秋 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT2386)

AGC 的思维题我真是一道都不会做啊……

感觉其他题解或多或少有点小问题 qwq，于是自己来写一篇。

题意比较清楚，直接观察一下性质，发现序列顺序无所谓，因此首先排序。

排序后，可以发现符合题意的序列必须满足 $a_n-a_1 \le 1$。

这是显然的，因为每个人能看到其他所有人的颜色，所以两两之间最多差 $1$。

于是分类讨论，分别讨论 $a_1=a_n$ 和 $a_1+1=a_n$ 的情况。

下记 $a_1$ 在序列中出现的次数为 $s$。

若 $a_1=a_n$，则说明所有人看到的颜色数相同。那么只有两种可能：

1、所有人的颜色都唯一，这种情况显然 $a_1=a_n=n-1$。

2、所有人颜色都不唯一，即每个人都能看到所有颜色，这种情况下一共有 $a_1$ 种颜色，每种颜色至少出现两次，因此有 $2a_1 \le n$。

可以证明没有其他可能，因为如果一个人颜色唯一，另一个人颜色不唯一，那么他们两个人看到的颜色数肯定不同。

若 $a_1+1=a_n$，那么可以知道有 $s$ 个人的颜色唯一，$n-s$ 个人的颜色不唯一。（这 $s$ 个人看到的颜色数比其他人少 $1$）

那么所有颜色唯一的人看到的颜色数量必然 $\ge s$，因为他们都能看到 $s-1$ 种唯一颜色，和所有不唯一的颜色，两者之和必然 $\ge s$，所以有 $a_1 \ge s$。

同时，这种情况下颜色不唯一的人能看到所有颜色，因此颜色种数一共有 $a_n$ 种。于是不唯一的颜色数有 $a_n-s$ 种。有 $n-s$ 个人的颜色不唯一，而不唯一的颜色至少要出现两次，因此有 $2(a_n-s) \le n-s$，移项可得 $n+s \ge 2a_n$。

这两个条件必须同时满足才符合题意。

这样就做完了，直接判断即可。

---

## 作者：lytqwq (赞：0)

每只猫能看到其他 $N-1$ 只猫的颜色种数，就是说看除了自己有多少种颜色，自己对答案的影响只有 $1$ 或 $0$ 两种情况，分别是 $\text{没有和自己一个颜色的猫时}$ 和 $\text{有和自己一个颜色的猫时}$ 的两种情况。

我们得到的数组 $a$ 也会最多只有两种数并且相差为 $1$ ，每个小的 $a_i$ 代表 $\text{没有和自己一个颜色的猫}$ ，大的 $a_i$ 代表 $\text{有和自己一个颜色的猫}$ 。

观察样例 $2$

```cpp
3
1 1 2

No
```

因为已经有两只猫颜色独特，剩下的第三只猫不会有猫和它颜色相同，就是说如果有猫颜色不是独特，那么这样的猫的数量一定 $\ge 2$

观察样例 $3$ 

```cpp
5
4 3 4 3 4

No
```

因为已经有 两 只猫颜色独特，剩下三只猫可以组成 $k$ 种颜色 $(1\le k \le \lfloor \frac{3}{2}\rfloor )$ 。


就是说，如果有 $s1$ 只猫颜色独特，剩下 $s2$ 只猫可以组成 $k$ 种颜色 $(1\le k \le \lfloor \frac{s2}{2}\rfloor )$ 。 （要特判 $s2=0$ ）

总共会有 $S$ 种颜色 $(1+s1\le S \le \lfloor \frac{s2}{2}\rfloor +s1 )$ 。

观察样例 $4$ 

```cpp
3
2 2 2

Yes
```

只有一种 $a_i$ 我们把它当作颜色独特和不独特都试一遍就完了



综合前面的分析，把

1. 得到的数组 $a$ 有两种以上的数或两种数相差不为 $1$
1. 恰好有一只猫颜色不是独特
1. 不独特的猫的 $a$ 不满足$(1+s1\le a \le \lfloor \frac{s2}{2}\rfloor +s1 )$ 的

全部输出 $No$ 就完了

剩下的输出 $Yes$ 

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=100010;
int n,a[N],b,s=1e9,bs,ss;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		b=max(b,a[i]);
		s=min(s,a[i]);
	}
	for(int i=1;i<=n;i++){
		if(b==a[i])bs++;
		else ss++;
	}
	if(b-s>1){
		printf("No\n");
		return 0;
	}
	if(bs==1){
		printf("No\n");
		return 0;
	}
	int ml=1+ss,mr=ss+(bs/2);
	
	if(b>mr||b<ml){
		if(s==b){
			bs=0;
			ss=n;
			ml=ss;mr=ss+(bs/2);
			if(b+1>mr||b+1<ml)printf("No\n");
			else printf("Yes\n");
		}
		else printf("No\n");
	}
	else printf("Yes\n");
	return 0;
}
```





---

