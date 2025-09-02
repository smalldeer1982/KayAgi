# [USACO15OPEN] Bessie Goes Moo S

## 题目描述

Farmer John 和奶牛 Bessie 喜欢在空闲时间互相出数学谜题。

上一次 FJ 给 Bessie 出的谜题非常难，她没能解出来。

现在，她想通过给 FJ 出一个有挑战性的谜题来报复他。

Bessie 给 FJ 的表达式是 $(B+E+S+S+I+E)(G+O+E+S)(M+O+O)$，其中包含七个变量 $B,E,S,I,G,O,M$（"$O$" 是一个变量，不是零）。对于每个变量，她给 FJ 提供了一个最多包含 500 个整数值的列表，表示该变量可能取的值。

她要求 FJ 计算有多少种不同的方式可以为这些变量赋值，使得整个表达式的值是 7 的倍数。

注意，这个问题的答案可能太大，无法用 32 位整数表示，因此你可能需要使用 64 位整数（例如，C 或 C++ 中的 "long long"）。

## 说明/提示

两种可能的赋值方式是：

$(B,E,S,I,G,O,M) = (2, 5, 7, 9, 1, 16, 19)$ -> 51,765

$(B,E,S,I,G,O,B) = (2, 5, 7, 9, 1, 16, 2)$ -> 34,510

## 样例 #1

### 输入

```
10
B 2
E 5
S 7
I 10
O 16
M 19
B 3
G 1
I 9
M 2```

### 输出

```
2```

# 题解

## 作者：Expecto (赞：10)

啊这道题首先读入的时候膜一下，记录每个数出现的次数，然后7^7暴力枚举下，方案数乘起来。

```cpp
[/color][codec ]#include<bits/stdc++.h>
using namespace std;
int g[10][10];
int x[10];long long ans=0;
int v[233][8]={0};
void dfs(int now){
    if (now==7){
        long long sum=1ll*(x[0]+x[1]+x[2]+x[2]+x[3]+x[1])*(x[4]+x[5]+x[1]+x[2])*(x[6]+x[5]*2);
        if (sum%7==0){
            long long tmp=1;
            for (int i=0;i<7;i++)
                tmp*=g[i][x[i]];
            ans+=tmp;
        }
        return ;
    }
    for (int i=0;i<7;i++){
        if (!g[now][i]) continue;
        x[now]=i;
        dfs(now+1);
    }
}
int main(){
    int n;
    cin>>n;
    for (int i=1;i<=n;i++){
        char c;int l;
        cin>>c>>l;
        l=(l%7+7)%7;
        if (c=='B') g[0][l]++;
        if (c=='E') g[1][l]++;
        if (c=='S') g[2][l]++;
        if (c=='I') g[3][l]++;
        if (c=='G') g[4][l]++;
        if (c=='O') g[5][l]++;
        if (c=='M') g[6][l]++;        
    }
    dfs(0);
    cout<<ans;
    return 0;
}[/codec ]
```

---

## 作者：Ofnoname (赞：4)

#### 为什么标签里有“DP”?
#### 为什么标签里有“动态规划”？

由于我们只需要判断一个数能否被7整除，所以每个变量的取值都可以先`%7`，所以虽然每个变量有500种取值，但是对7模数相同的可以看做一个数，所以每个数只有7种选择。

接下来枚举每个变量选什么，判断是否被7整除，并累加答案即可。需要注意的是，取模后，同一个变量（如2,9,16...）虽然本质相同，但是答案应该计算多次，由乘法原理可知，答案应该是每一个数等效的数个数的乘积。

```cpp
#include <bits/stdc++.h>
#define long long long
using namespace std;

char t[3], c[7] = {'B', 'E', 'S', 'I', 'G', 'O', 'M'};

int N, x, f[7], a[7][7];
long ans;

map <char, int> M;

void DFS(int x)
{
	if (x == 7)
	{
		long sum = (f[0]+(f[1]+f[2])*2+f[3]) * (f[1]+f[2]+f[4]+f[5]) * (f[6]+f[5]*2);
		if (!(sum % 7))
		{
			sum = 1;
			for (int i = 0; i < 7; i++)
				sum *= a[i][f[i]];//乘法原理计算答案
			ans += sum;
		}return;
	}
	for (int i = 0; i < 7; i++)
		if (a[x][i]) f[x] = i, DFS(x+1);//枚举所有可能的取值
}

int main()
{
	scanf("%d", &N);
	for (int i = 0; i < 7; i++)
		M[c[i]] = i;//将字母离散化为0~6
	
	while (N--)
	{
		scanf("%s%d", t, &x);
		a[M[t[0]]][(x%7+7)%7]++;//这里使用桶来存储次数
	}
	DFS(0);
	printf("%lld\n", ans);
}
```

---

## 作者：Wangchenxin (赞：4)

好吧
很普通的一种做法

```cpp
#include<cstdio>
#define LL long long
using namespace std;
int N,x;
char ch;
LL ans,hsh[95][7];
inline int read(){//快读
	int ret=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-')f=-f;ch=getchar();}
	while (ch>='0'&&ch<='9') ret=ret*10+ch-'0',ch=getchar();
	return ret*f;
}
int main(){
    N=read();
    for (int i=0;i<N;i++){
        ch=getchar(),x=read();
        hsh[ch][(x%7+7)%7]++;//因为是7的倍数,所以分成7类（分别是%7=0,1,2,3,4,5,6）,其实只需要判断他们除以7的余数相加是否为7的倍数
    }
    for(int B=0;B<7;B++)
    for(int E=0;E<7;E++)
    for(int S=0;S<7;S++)
    for(int I=0;I<7;I++)
    for(int G=0;G<7;G++)
    for(int O=0;O<7;O++)
    for(int M=0;M<7;M++) 
      if (((B+E+S+S+I+E)*(G+O+E+S)*(M+O+O))%7==0){
          ans+=hsh['B'][B]*hsh['E'][E]*hsh['S'][S]*hsh['I'][I]*hsh['G'][G]*hsh['O'][O]*hsh['M'][M];//判断%7后的余数是否为7的倍数，如果是ans++;
      }
    printf("%lld\n",ans);
    return 0;
}
```


---

## 作者：Eismcs (赞：3)

独门的dfs，源于数据范围的小，暴力即可。

所谓数据范围的小，就在于模数小，只有7，变量少，也是7，于是dfs便能开心的水过。

但这道题也包容了不少算法思路，如注释所述。
```cpp
#include<cstdio>
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<queue>
#include<map>
using namespace std;
#define re register int
inline int read(){
    int x=0,ff=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')ff=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
    return x*ff;
}
int b[10][10];
//b[i][j]表示第i个变量（自定义）可取数的模数为的j有几个
int a[10];
//dfs记录变量
long long ss;
void dfs(int i,long long s){
	if(i>7){
		if((a[1]+2*a[2]+2*a[3]+a[4])%7==0||(a[2]+a[3]+a[5]+a[6])%7==0||(a[7]+2*a[6])%7==0){
        //因为7为质数，所以3个因数中比要有一个整除7
			ss+=s;return;
        //加上方案
		}
	}
	for(int j=0;j<7;j++){
		if(b[i][j]){
			a[i]=j;dfs(i+1,s*b[i][j]);
        //枚举，搜索
        //s*b[i][j]表示方案数（乘法原理）
		}
	}
}
int main(){
	int n=read(),x;
	char c;
	while(n--){
		cin>>c;x=read();
		x=(x%7+7)%7;
     //取模，因为同余性质，所以不影响求解，这便相当离散化了
		if(c=='B'){
			b[1][x]++;
		}
		if(c=='E'){
			b[2][x]++;
		}
		if(c=='S'){
			b[3][x]++;
		}
		if(c=='I'){
			b[4][x]++;
		}
		if(c=='G'){
			b[5][x]++;
		}
		if(c=='O'){
			b[6][x]++;
		}
		if(c=='M'){
			b[7][x]++;
		}
     //以上是取模后的存储，字母读入够毒瘤的。
	}
	dfs(1,1);
	cout<<ss<<endl;

    return 0;
}

```


---

## 作者：SIXIANG32 (赞：1)

随机跳题跳到了这个题。  
闲话少说，切入正题——  

---
题目让我们求多少种方案让式子得数成为 $7$ 的倍数，也就是说模 $7$ 为 $0$。  
既然是取余运算，每个数是没有太大意义了，我们完全可以把每个数值变成这个数对 $7$ 取余的数字，这对结果取余 $7$ 没有任何影响。  
$7$ 的余数必然小于 $7$，只有 $0\sim 6$ 这 $6$ 种，每个字母有 $7$ 中取值，有 $7$ 个字母，组合起来只有 $7^7$ 种情况。  
只要计算一下就好了。    
唯一要注意的一点：数值可能是负数！  
```cpp
#include <iostream> 
#define MAXN 100000
#define QWQ cout << "QWQ" << endl;
using namespace std;
long long sum[10][10];
int id(char ch) {
	if(ch == 'B') return 1;
	else if(ch == 'E') return 2;
	else if(ch == 'S') return 3;
	else if(ch == 'I') return 4;
	else if(ch == 'G') return 5;
	else if(ch == 'O') return 6;
	else if(ch == 'M') return 7;
}
int main() {
	int n; cin >> n; char ch;
	long long ans = 0;
	for(int p = 1, x; p <= n; p++)
		cin >> ch >> x, sum[id(ch)][(x + 2486750) % 7]++;
	for(int B = 0; B < 7; B++)
		for(int E = 0; E < 7; E++)
			for(int S = 0; S < 7; S++)
				for(int I = 0; I < 7; I++)
					for(int G = 0; G < 7; G++)
						for(int O = 0; O < 7; O++)
							for(int M = 0; M < 7; M++)
								if((B+E+S+S+I+E) * (G+O+E+S) * (M+O+O) % 7 == 0)
									ans += sum[1][B] * sum[2][E] * sum[3][S] * sum[4][I] * sum[5][G] * sum[6][O] * sum[7][M];
	cout << ans << endl;
}
```

---

## 作者：Violet___Evergarden (赞：1)

开一个 $v$ 数组将每个字母与 $7$ 取余之后的值的个数，再通过枚举 $7$ 个数的余数算出答案。

需要注意的是，我们需要将复数取余后的余数存为复数。自己可以拿 $-1$ 和 $6$ 这两个数举例。
```cpp
#include<iostream>
#define RE register
using namespace std;
const int kj=6;
unsigned long long dp;
long long v[8][13];
int n;
int G(char a)
{
  if(a=='B')return 1;
  if(a=='E')return 2;
  if(a=='S')return 3;
  if(a=='I')return 4;
  if(a=='G')return 5;
  if(a=='O')return 6;
  if(a=='M')return 7;
}
int main()
{
//freopen("bgm.in","r",stdin);
//freopen("bgm.out","w",stdout);
cin>>n;
for(RE int i=1;i<=n;++i)
{
  char a;
  int b;
  cin>>a>>b;
  ++v[G(a)][b%7+kj];//将每个数%7的余数算出来
}
for(RE int b=0;b<=12;++b)
{
  if(v[1][b]==0)continue;
  for(RE int e=0;e<=12;++e)
  {
    if(v[2][e]==0)continue;
    for(RE int s=0;s<=12;++s)
    {
      if(v[3][s]==0)continue;
      for(RE int i=0;i<=12;++i)
      {
        if(v[4][i]==0)continue;
        for(RE int g=0;g<=12;++g)
        {
          if(v[5][g]==0)continue;
          for(RE int o=0;o<=12;++o)
          {
            if(v[6][o]==0)continue;
            for(RE int m=0;m<=12;++m)
            {
              if(v[7][m]==0)continue;
              if((b-kj+e-kj+s-kj+s-kj+i-kj+e-kj)%7==0||(g-kj+o-kj+e-kj+s-kj)%7==0||(m-kj+o-kj+o-kj)%7==0)//判断是否可行
              {
                dp+=v[1][b]*v[2][e]*v[3][s]*v[4][i]*v[5][g]*v[6][o]*v[7][m];//统计答案
              }
            }
          }
        }
      }
    }
  }
}
cout<<dp;
return 0;
//fclose(stdin);
//fclose(stdout);
}

---

## 作者：Usada_Pekora (赞：1)

### 简单的思路

因为数据较小，所以可以进行暴力枚举

用一个变量记录每个字母出现的次数

但是要记住对输入的数进行取余7的操作，节省数组的空间

在记录好了以后，就可以进行枚举了

代码并不难写，难点在于思考到如何节省时间与空间

在取余处理后，时间复杂度：$O(7^7)$
### Code:
```cpp
#include<iostream>
#include<cstdio>
#define FOR(i) for(int i=0;i^7;i++)
using namespace std;
typedef long long LL;
int n;
LL ans,a[105][10];
inline int read(){
	int ret=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-f;ch=getchar();}
	while (ch>='0'&&ch<='9')ret=ret*10+ch-'0',ch=getchar();
	return ret*f;
}
inline char fchar(){
	char ch=getchar();
	while (ch!='B'&&ch!='E'&&ch!='S'&&ch!='I'&&ch!='G'&&ch!='O'&&ch!='M') ch=getchar();
	return ch;
}
int main(){
	scanf("%d",&n);
	for (int i=1;i<=n;i++)a[fchar()][(read()%7+7)%7]++;
	FOR(B) FOR(E) FOR(S) FOR(I) FOR(G) FOR(O) FOR(M)
	  if ((B+2*E+2*S+I)*(G+O+E+S)*(M+2*O)%7==0)
		ans+=a['B'][B]*a['E'][E]*a['S'][S]*a['I'][I]*a['G'][G]*a['O'][O]*a['M'][M];
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：Seanq (赞：1)

**P3123 [USACO15OPEN]贝茜说哞Bessie Goes Moo**     
题意很简单：给一个代数式填数，使代数式的值%7等于0     
很容易想到，三个一次多项式中的一个%7等于0即可   
于是我们把每个输入数据%7后存下来   
令f[i][j]表示第i个字母取值%7为j时的方案数   
我们O(7^7)枚举每个字母可能的%7的取值，再判断即可   
判断只需将三个式子各算出，并%7一下即可    
# 优化们：    
1.dfs搜索   
2.如果一个取值没出现便不做     
（本题最xx代码，无优化）    
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int f[8][8]={0};
typedef long long ll;
ll ans=0;
int change(char c){
	if(c=='B') return 1;
	else if(c=='E') return 2;
	else if(c=='S') return 3;
	else if(c=='I') return 4;
	else if(c=='G') return 5;
	else if(c=='O') return 6;
	else return 7; 
}
int main(){
	cin>> n;
	for(int i=1;i<=n;i++){
		char c;
		int t;
		cin>>c>>t;
		f[change(c)][(t%7+7)%7]++;
	}
	int a[10];
	for(a[1]=0;a[1]<=6;a[1]++){for(a[2]=0;a[2]<=6;a[2]++){for(a[3]=0;a[3]<=6;a[3]++){for(a[4]=0;a[4]<=6;a[4]++){for(a[5]=0;a[5]<=6;a[5]++){for(a[6]=0;a[6]<=6;a[6]++){for(a[7]=0;a[7]<=6;a[7]++){
		if((a[1]+2*a[2]+2*a[3]+a[4])%7==0||(a[2]+a[3]+a[5]+a[6])%7==0||(2*a[6]+a[7])%7==0){
		ll sum=1;
		for(int i=1;i<=7;i++) sum*=(ll)f[i][a[i]];
		ans+=sum; 
	}
	}
	}
	}
	}
	}
	}
	}
	cout<<ans<<endl;
	return 0;
} 
```

---

## 作者：Fading (赞：1)

首先同余有一个性质：

$\text{若}x≡a(mod\ p),y≡b(mod\ p),\text{则有}xy≡ab(mod\ p)$

所以我们把读入的数先对$7$取膜，问题就比较简单了。

我们设$\texttt{B,E,S,I,G,O,M}$分别为$1,2,3,4,5,6,7$

然后暴力枚举下就好了。复杂度$O(7^8)$
```
#include<bits/stdc++.h>
#define gc getchar 
using namespace std;
int has[8][8],n;
long long ans;
inline int getch(){
	char x=gc();
	while (!isalpha(x)) x=gc();
	if (x=='B') return 1;
	if (x=='E') return 2;
	if (x=='S') return 3;
	if (x=='I') return 4;
	if (x=='G') return 5;
	if (x=='O') return 6;
	if (x=='M') return 7;
}
//BESIGOM
inline int read(){
    int x=0,f=1;char ch=gc();
    while(ch<'0'||ch>'9') {if (ch=='-') f=-1;ch=gc();}
    while(ch<='9'&&ch>='0') x=x*10+ch-'0',ch=gc();
    return x*f;
}
int main(){
	n=read();
	for (int i=1;i<=n;i++){
		int ch=getch(),x=read();
		has[ch][(x%7+7)%7]++;
	}
	for (int iB=0;iB<=6;iB++){
		for (int iE=0;iE<=6;iE++){
			for (int iS=0;iS<=6;iS++){
				for (int iI=0;iI<=6;iI++){
					for (int iG=0;iG<=6;iG++){
						for (int iO=0;iO<=6;iO++){
							for (int iM=0;iM<=6;iM++){
								if ((iB+iE+2*iS+iI+iE)*(iG+iO+iE+iS)*(iM+iO+iO)%7) continue;
                                //判断是否满足条件
								long long tmp=1;
								tmp*=has[1][iB];	
								tmp*=has[2][iE];
								tmp*=has[3][iS];
								tmp*=has[4][iI];
								tmp*=has[5][iG];
								tmp*=has[6][iO];
								tmp*=has[7][iM];
								ans+=tmp;
							}
						}
					}
				}
			}
		}
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：Parat_rooper (赞：0)

# 解题思路：
首先我们观察题中所给式子：

$$(B+E+S+S+I+E)(G+O+E+S)(M+O+O)$$

很容易发现其中只有加法和乘法运算，故联系题中要求被七整除的要求可以想到将所有可能取值对七取模，而题目又保证没有两个取值相同，所以直接枚举每个数的值对于七的余数，在使式子被七整除时计算方案数即可。

代码如下：
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

int n, x;
char c;
long long ans1, ans2, ans3, ans, ans4, ans5, ans6, ans7;

struct bian {
  int a[7], s;
}b[7];

int main() {
  ios_base::sync_with_stdio(0);//一个优化cin，cout的东西
  cin.tie(NULL), cout.tie(NULL);
  cin >> n;
  for (register int i = 1; i <= n; ++i) {
    cin >> c >> x;//B0, E1, S2, I3, G4, O5, M6
    if (c == 'B') {
      ++b[0].a[(x % 7 + 7) % 7], ++b[0].s;
    } if (c == 'E') {
      ++b[1].a[(x % 7 + 7) % 7], ++b[1].s;
    } if (c == 'S') {
      ++b[2].a[(x % 7 + 7) % 7], ++b[2].s;
    } if (c == 'I') {
      ++b[3].a[(x % 7 + 7) % 7], ++b[3].s;
    } if (c == 'G') {
      ++b[4].a[(x % 7 + 7) % 7], ++b[4].s;
    } if (c == 'O') {
      ++b[5].a[(x % 7 + 7) % 7], ++b[5].s;
    } if (c == 'M') {
      ++b[6].a[(x % 7 + 7) % 7], ++b[6].s;
    }
  }
  for (register int i = 0; i <= 6; i++) { //枚举b的值除七的余数
    if(b[0].a[i]){//避免出现一些没用的状态
      for (register int j = 0; j <= 6; ++j) { //枚举e的值除七的余数
      if(b[1].a[j]){
        for (register int k = 0; k <= 6; ++k) { //枚举s的值除七的余数
        if(b[2].a[k]) {
        for (register int l = 0; l <= 6; ++l) { //枚举i的值除七的余数
        if(b[3].a[l]) {
          for (register int s = 0; s <= 6; ++s) { //枚举g的值除七的余数
          if(b[4].a[s]){
            for (register int p = 0; p <= 6; ++p) { //枚举o的值除七的余数
            if(b[5].a[p]){
              for (register int q = 0; q <= 6; ++q) {//枚举m的值除七的余数
                if (((i + 2 * j + 2 * k + l) * (j + k + s + p) * (q + 2 * p)) % 7 == 0) {
                  ans7 += 1ll * b[0].a[i] * b[1].a[j] * b[2].a[k] * b[3].a[l] * b[4].a[s] * b[5].a[p] * b[6].a[q];//累加方案数
                }
              }}
            }}
          }}
        }}
      }}
    }}
  }
  cout << ans7;
  return 0;
}
```


---

## 作者：abandentsky (赞：0)

题意：代码下面有很多，我只来说一下题目啥意思。
      B,E,S,I,G,O,M这几个字母。
      第一行给你给出一个正整数n，下面n行，每行一个字母，一个数字，表示
      那个字母是哪个值。现在问你有多少种B,E,S,I,G,O,M字母组合使得他们
      能满足(B+E+S+S+I+E)(G+O+E+S)(M+O+O)取余7为0.其中这几个字母是可以
      重复的。
思路：我们需要记录B,E,S,I,G,O,M这几个字母分别有几种，每种个有多少个。
      每种就是在模7下。然后直接暴力掉就好了。
AC代码：（和楼下大佬的代码差不多）
```c
#include<bits/stdc++.h>
#pragma GCC optimize(2)
#define MAXN 20
#define MAXP 55
#define maxnode 50010
#define sigma_size 26
#define mod 1000000007
#define INF 0x3f3f3f3f
#define lc  (id<<1)
#define rc  (id<<1|1)
using namespace std;
typedef long long LL;

LL num[100][8];
char str[10],ch;
int n,pop;
LL ans;

int main()
{
    scanf("%d",&n);
    ans=0;
    for(int i=1;i<=n;i++)
    {
        scanf("%s",str);
        scanf("%d",&pop);
        ch=str[0];
        num[ch][(pop%7+7)%7]++;
    }
    for(int B=0;B<7;B++)
    {
        for(int E=0;E<7;E++)
        {
            for(int S=0;S<7;S++)
            {
                for(int I=0;I<7;I++)
                {
                  for(int G=0;G<7;G++)
                  {
                     for(int O=0;O<7;O++)
                     {
                         for(int M=0;M<7;M++)
                         {
                             if(((B+E+S+S+I+E)*(G+O+E+S)*(M+O+O))%7==0)
                             {
                                ans+=num['B'][B]*num['E'][E]*num['S'][S]*num['I'][I]*num['G'][G]*num['O'][O]*num['M'][M];
                             }
                         }
                     }
                 }
             }
          }
        }
    }
    printf("%lld\n",ans);
    return 0;
}

```


---

## 作者：Pjenorsheet (赞：0)

**题目描述**

七个变量B,E,S,I,G,O,M;使得(B+E+S+S+I+E)(G+O+E+S)(M+O+O)被7整除的方案有多少种.

**输入格式**

第一行一个整数N

接下来N行，每行包含一个变量和其可能的一个值。输入数据保证同一个变量可能的取值各不相同，且都在-10^5 到 10^5之间

**输出格式**

一个整数，表示方案数。

**输入输出样例**

**输入**

```
10
B 2
E 5
S 7
I 10
O 16
M 19
B 3
G 1
I 9
M 2
```

**输出 **

```
2
```

**说明/提示**

The two possible assignments are

(B,E,S,I,G,O,M) = (2, 5, 7, 9, 1, 16, 19) -> 51,765

= (2, 5, 7, 9, 1, 16, 2 ) -> 34,510



> 简单思路

如果将可能的取值模7，并不影响统计的结果，所以我们在输入的时候将每个取值模7后的结果出现的次数保存下来，则每个变量取值只有七种情况，再带入表达式暴力枚举，统计答案。



```cpp
#include<cmath>
#include<cctype>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
inline char getc(){
	static const int len=1<<19;static char buf[len],*p1=buf,*p2=buf;
	return p1==p2 and (p2=(p1=buf)+fread(buf,1,len,stdin),p1==p2)?EOF:*p1++;
}
inline bool blank(char c){return c==' ' or c=='\n' or c=='\r' or c=='\t';}
template <typename T> inline void rd(T &x){
	x=0;bool f=false;char c=getc();
	while(!isdigit(c)) f=(c=='-'),c=getc();
	while(isdigit(c)) x=x*10+c-'0',c=getc();
	if(f) x=-x;
}
inline void rdb(double &x){
	x=0;bool f=false;char c=getc();
	while(!isdigit(c)) f=(c=='-'),c=getc();
	while(isdigit(c)) x=x*10+c-'0',c=getc();
	if(c=='.') {double tmp=1;c=getc();while(isdigit(c)) tmp/=10.0,x+=tmp*(c-'0'),c=getc();}
	if(f) x=-x;
}
inline int rds(char *s){
	int len=0;char c=getc();
	for(;blank(c);c=getc());
	for(;!blank(c);c=getc()) *s++=c,len++;
	*s=0;return len;
}
#define hh puts("")
#define int long long
#define DB double
#define mod(x) (x%7+7)%7
#define documents(x); freopen(x".in","r",stdin);freopen(x".out","w",stdout);
using namespace std;

int n,ans,mo[10][10],curr[10];

void dfs(int x);

signed main(){
	//documents("math");
	rd(n);
	for(int i=1,x;i<=n;i++){
		char c=getc();
		while(blank(c)) c=getc();
		if(isalpha(c)){
			switch(c){
				case 'B': {rd(x);mo[1][mod(x)]++;break;}
				case 'E': {rd(x);mo[2][mod(x)]++;break;}
				case 'S': {rd(x);mo[3][mod(x)]++;break;}
				case 'I': {rd(x);mo[4][mod(x)]++;break;}
				case 'G': {rd(x);mo[5][mod(x)]++;break;}
				case 'O': {rd(x);mo[6][mod(x)]++;break;}
				case 'M': {rd(x);mo[7][mod(x)]++;break;}
			}
		}
	}
	dfs(1);
	printf("%lld",ans);
	return 0;
}

void dfs(int step){
	if(step>7){
		if((curr[1]+2*curr[2]+2*curr[3]+curr[4])*(curr[5]+curr[6]+curr[2]+curr[3])*(curr[7]+2*curr[6])%7==0){
			int tmp=1;
			for(int i=1;i<=7;i++){
				tmp*=mo[i][curr[i]];
			}
			ans+=tmp;
			return ;
		}
		return ;
	}
	for(int i=0;i<7;i++){
		if(!mo[step][i]) continue;
		curr[step]=i;
		dfs(step+1);
	}
}
```



---

