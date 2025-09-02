# [ABC071D] Coloring Dominoes

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc071/tasks/arc081_b

$ 2\ \times\ N $ のマス目があります． すぬけ君は，このマス目に $ N $ 個のドミノを，重ならないように敷き詰めました． ここで，ドミノは，$ 1\ \times\ 2 $ または $ 2\ \times\ 1 $ のマス目を覆うことができます．

すぬけ君は，赤色，水色，緑色の $ 3 $ 色を使って，これらのドミノを塗ることにしました． このとき，辺で接しているドミノは異なる色で塗るようにします． ここで，必ずしも $ 3 $ 色すべてを使う必要はありません．

このような塗り方が何通りあるかを mod $ 1000000007 $ で求めてください．

ただし，ドミノの敷き詰め方は，文字列 $ S_1,\ S_2 $ を用いて，次のようにして与えられます．

- 各ドミノは，それぞれ異なる英小文字または英大文字で表される．
- $ S_i $ の $ j $ 文字目は，マス目の上から $ i $ 番目，左から $ j $ 番目のマスにどのドミノがあるかを表す．

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 52 $
- $ |S_1|\ =\ |S_2|\ =\ N $
- $ S_1,\ S_2 $ は英小文字または英大文字からなる
- $ S_1,\ S_2 $ は正しいドミノの敷き詰め方を表している

### Sample Explanation 1

次の $ 6 $ 通りあります． !\[\](https://atcoder.jp/img/arc081/899673bd23529f4fb5e41c6e7d5bc372.png)

### Sample Explanation 2

必ずしもすべての色を使わなくてもよいことに注意してください．

## 样例 #1

### 输入

```
3
aab
ccb```

### 输出

```
6```

## 样例 #2

### 输入

```
1
Z
Z```

### 输出

```
3```

## 样例 #3

### 输入

```
52
RvvttdWIyyPPQFFZZssffEEkkaSSDKqcibbeYrhAljCCGGJppHHn
RLLwwdWIxxNNQUUXXVVMMooBBaggDKqcimmeYrhAljOOTTJuuzzn```

### 输出

```
958681902```

# 题解

## 作者：installb (赞：4)

dp都不用 直接一步一步推过去就行了  
**在已知当前列左边一列的情况下 推出当前列有多少种上色的方法**  
推到底  
第一列特别处理

一共会出现以下几种情况:  
(^)指当前列
1.
```cpp
AB
AB
 ^
```
A的颜色确定 B的颜色不确定  
B颜色与A不同，所以有2种方法 遇到这样的样式 答案$\times2$  
2.
```cpp
AAC
BBC
  ^
```
A B的颜色确定 C的颜色不确定  
C颜色与A和B都不同，所以有2种方法 遇到这样的样式 答案$\times1$  
3.
```cpp
ABB
ACC
 ^
```
A的颜色确定 B C的颜色不确定  
B C颜色都与A不同，B C颜色不同，所以有2种方法 遇到这样的样式 答案$\times2$  
4.
```cpp
AACC
BBDD
  ^
```
A B的颜色确定 C D的颜色不确定  
C颜色与A不同，D颜色与B不同 CD颜色也要不同  
(C先随意取一种 D再随意取一种 去掉CD都选(非A非B的颜色)的颜色的情况)
所以有3种方法 遇到这样的样式 答案$\times3$  

考虑完一种情况后直接直接跳到下一个骨牌处理 遇到横着的骨牌直接当前处理位置+2 不然会重复计算  
```cpp
ABBCC
ADDEE
 ^ ^
 i j // 当前处理i 判断出来是横着放的 直接跳到i+2(j)继续处理
```

最后注意预处理  
第一列的骨牌没有左边列的限制  
竖着摆3种(任意一颜色)  
横着摆6种($2\times3$)

乘法原理都懂吧

**code:**
```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <map>
using namespace std;
typedef long long LL;
const LL N = 1e9 + 7;

LL n,ans = 1,s;
string a;
string b;
 
int main(){
	cin >> n; cin >> a; cin >> b;
	if(a[0] == b[0]){ ans = 3; s = 1; }
	if(a[0] != b[0]){ ans = 6; s = 2; }
    
	for(LL i = s;i < n;){
		if(a[i] == b[i] && a[i - 1] == b[i - 1]) ans *= 2;
		if(a[i] == b[i] && a[i - 1] != b[i - 1]) ans *= 1;
		if(a[i] != b[i] && a[i - 1] == b[i - 1]) ans *= 2;
		if(a[i] != b[i] && a[i - 1] != b[i - 1]) ans *= 3;
        // 分别对应情况 1~4
		if(a[i] != b[i]) i += 2; // 竖着放 处理i+2位
		else i ++; // 竖着放 处理下一位
		ans %= N; // 别忘了mod
	}
	cout << ans << endl;
	return 0;
}
```

对了 题目中N=52只是因为字母不够用 时间复杂度是线性的

---

## 作者：watcher_YBH (赞：2)

# 思路：
这道题的思路十分简单。我们可以先将整个序列按照一个竖着的或两个横着的分组。

我们来看一种最简单的情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/lf7jcns1.png)

这是一个竖着的与两个横着的并在一起的情况：

对于每一个方块，我们只用考虑它左边和上面与它相邻的方块，右边和下面与它相邻的方块我们暂时可以不用考虑（不是不考虑，只是在下一次考虑右边和下面与它相邻的方块时，考虑两者的关系）。而有几个左边和上面与它相邻的方块有几种不同的颜色，那么它可选的颜色变减少几种。

对于上面那种情况，方块 $A$ 左边没有方块，所以它有三种颜色的选择；方块 $B$ 左边有一个方块 $A$ ，因为方块 $A$ 已经有了一种颜色，所以方块 $B$ 有
两种颜色可以选择；方块 $C$ 需要考虑的有方块 $A,B$ ，而方块 $A,B$ 都有一种不同的颜色，所以方块 $C$ 只有一种颜色可以选择，如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/2t03qedm.png)

我们再将这种情况拆成两组：一个竖着的和两个横着的。再用乘法原理将每组的方块的选择数乘起来，就是这组方块总的方案数。于是，我们可以得到两个结论：

1. 如果第一个位置是一个竖着的那么它有 $3$ 种情况。

2. 如果前一个位置是一个竖着的，此位置是两个横着的，那么它有 $2$ 种情况。

同理，我们可以得到以下结论：

1. 如果第一个位置是两个横着的那么它有 $6$ 种情况。

2. 如果前一个位置是一个竖着的，此位置是一个竖着的，那么它有 $2$ 种情况。

3. 如果前一个位置是两个横着的，此位置是一个竖着的，那么它有 $1$ 种情况。

当然，会有一个特殊情况：前一个位置是两个横着的，此位置是两个横着。如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/gnd8ho53.png)

因为方块 $C,D$ 的颜色可以相同，所以我们分情况讨论：

1. 方块 $C,D$ 的颜色不同：

![](https://cdn.luogu.com.cn/upload/image_hosting/sypnf7zj.png)

则，方块 $D$ 只有一种颜色可以选择。

2. 方块 $C,D$ 的颜色相同：

![](https://cdn.luogu.com.cn/upload/image_hosting/sbg5emnq.png)

则，方块 $D$ 只有两种颜色可以选择。

所以，前一个位置是两个横着的，此位置是两个横着的情况有三种方案数。

所以我们可以得到以下结论：

1. 如果前一个位置是两个横着的，此位置是两个横着的那么它有 $3$ 种情况。

然后再用乘法原理将所有满足结论的情况的方案数全部乘起来就可以了。

# 代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
#define max(a,b) ((a>b)?a:b)
#define min(a,b) ((a<b)?a:b)
using namespace std;
const int MAX = 1e5+5;
const int mod = 1e9+7;
int n,c[MAX];
string s,s1;
ll ans = 1;
int main(){
	cin>>n>>s>>s1;
	int cnt = 0;
	for(int i = 0; i<s.size(); i++){//分组
		if(s[i] == s[i+1] && s1[i] == s1[i+1]) c[++cnt] = 2,i+=1;
		else if(s[i] == s1[i]) c[++cnt] = 1;
	}
	for(int i = 1; i<=cnt; i++){
		if(c[i] == 2){//如果是两个横着的
			if(i == 1) ans *= 6,ans %= mod;//如果是第一个
			else if(c[i-1] == 1) ans *= 2,ans %= mod;//前面是竖着的
			else if(c[i-1] == 2) ans *= 3,ans %= mod;//前面是横着的
		}
		else if(c[i] == 1){//如果是一个竖着的
			if(i == 1) ans *= 3,ans %= mod;//如果是第一个
			else if(c[i-1] == 1) ans *= 2,ans %= mod;//前面是竖着的
			else if(c[i-1] == 2) ans *= 1,ans %= mod;//前面是横着的
		}
	}
	cout<<ans%mod<<endl;
	return 0;
}
```


---

## 作者：Sirkey (赞：1)

## 这道题哪像个蓝题啊？

题目有个地方没讲清楚，其实给的两个字符：就是把规划的方式进行了用字母抽象的表达。

对于两个字符串，如果在 $a$ 中有两个连续相等那么，在 $b$ 中也会相等。显然，因为他只给了两行。那么不相等，$a$ 和 $b$ 中对于这个点就相等了。

那我们可以把这一块一块的把横的用 $1$，竖的用 $2$ 来表示一下，依次排起来，方便讨论。

```
aa
bb
```

的情况下我们把它看在一块，避免产生一下不必要的麻烦。

```
ab
ab
```


在上面这种情况下，我们涂颜色的方案数 $\times2$。


```
abb
acc
```


方案数也应当 $\times2$。

还有一种情况：

```
aabb
ccdd
```


像以上的这种情况，涂色方案数应当 $\times3$。

其他的情况还有，我不一一赘述，因为都不会改变方案数。

我直接把代码奉上，因为实在太简单了。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define FOR(i,a,b) for(ll i=(a); i<=(b); ++i)
#define ROF(i,a,b) for(ll i=(a); i>=(b); --i)
#define tell(ans) out(ans),printf("\n");
#define say(ans) out(ans),printf(" ");
#define pb push_back
//
//
//
using namespace std;
const int mod=1000000007;
inline ll read() {
	ll f=0,t=0;
	char c=getchar();
	while(!isdigit(c)) t|=(c=='-'),c=getchar();
	while(isdigit(c)) f=(f<<3)+(f<<1)+c-48,c=getchar();
	return t?-f:f;
}
inline void out(ll x) {
	if(x<0) putchar('-');
	if(x>9) out(x/10);
	putchar('0'+x%10);
}
string a,b;
ll ans,k[100];
int main() {
	int n=read();
	cin>>a>>b;
	FOR(i,0,n-1) {
		if(a[i]==b[i])  k[i]=1;
		else i++,k[i]=2,k[i-1]=2;
	}
	ans=3;
	int s=0;
	if(k[0]==2) ans=ans*2,s=1;
	FOR(i,s,n-1) {
		if(k[i]==1 && k[i+1]==1) ans*=2%mod;
		if(k[i]==1 && k[i+1]==2) ans*=2%mod;
		if(k[i]==2 && k[i+1]==2) ans*=3%mod;
		if(k[i+1]==2) i++;
	}
	cout<<ans%mod;
	return 0;
}

```

——end——



---

## 作者：_AyachiNene (赞：0)

# 思路：
因为这道题的 $n=2$，所以每个位置只有两种摆法：

![](https://cdn.luogu.com.cn/upload/image_hosting/64syy7qg.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

![](https://cdn.luogu.com.cn/upload/image_hosting/auu7ypg1.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

所以我们可以分情况讨论。先特判第一个位置，如果是横着的就有六种可能，竖着的就只有三种（可参考的一，二个样例）。当遇到一个单独的竖着摆的且前面是横着的就有一种可能，因为前面两个肯定是两种不同颜色，否则就是两种可能性。如果是横着的且前面是竖着的，那么就只有两种情况，否则是三种（建议画个图）。根据小学数学知识把每个位置的可能性乘起来就行了。
# Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7;
int n,k;
long long ans=1;
bool flag;
char a[114][514];
int main()
{
	cin>>n;
	for(int i=1;i<=2;i++)
		for(int j=1;j<=n;j++)
			cin>>a[i][j];
	if(a[1][1]==a[1][2])
		ans=6,k=3;
	else
		ans=3,k=2;
	for(int i=k;i<=n;i++)
	{
		if(a[1][i]==a[1][i+1])    //是横着的 
		{
			if(a[1][i-1]==a[1][i-2])           //前面是横着的 
				ans=(ans*3)%mod;
			else
				ans=(ans*2)%mod;      //前面是竖着的 
			i++;
		}
		else
		{
			if(a[1][i-1]==a[2][i-1])	//前面是竖着的 
				ans=(ans*2)%mod;
		}
	}
	cout<<ans;
}
```


---

## 作者：STARSczy (赞：0)

# 思路：
这道题就是个递推。我们分四种情况：

#### 第一种：
```
ac
ac
```
其中，当 aa 的颜色已经确定，易得 cc 有 $2$ 种情况。

#### 第二种：
```
abb
acc
```
其中，当 aa 的颜色已经确定，则 bb 有 $2$ 种情况，此时 cc 只有 $1$，总情况为 $2 \times 1 = 2$ 种。

#### 第三种：
```
aac
bbc
```
其中，aa 和 bb 的颜色已经确定，则 cc 只有 $1$ 种情况。

#### 第四种：

```
aacc
bbdd
```

其中，aa 和 bb 的颜色已经确定，且互不相同。设 aa 与 cc 颜色相同，则 dd 有 $2$ 种情况；若 aa 与 cc 颜色不相同，则 dd 只有 $1$ 种情况。共 $2 + 1 = 3$ 种情况。

因此，我们就可以开始排列组合来递推了。

# 代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int mod=1e9+7;
int ans,n,k,al[100000],bl[100000];
char a[100000],b[100000];

signed main(){
	cin>>n>>a>>b;
	for(int i=0;a[i];++i){
		if(a[i]!=b[i]){
			if(i==0) ans=6;
			else if(a[i-1]==b[i-1]) ans=ans*2%mod;
			else ans=ans*3%mod;
			++i;
		}
		else{
			if(i==0) ans=3;
			else if(a[i-1]==b[i-1]) ans=ans*2%mod;
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：daniEl_lElE (赞：0)

## 思路

考虑 $dp_{i,j,k}$，表示看到第 $i$ 位，$s_{0,i}$ 填的是 $j$ 号颜色，$s_{1,i}$ 填的是 $k$ 号颜色的方案数，其中 $j,k$ 都是小于 $3$ 的非负整数。

考虑如何转移，枚举第 $i$ 和 $i+1$ 上的四个数，如果相邻两个的 $s_{x,y}$ 是相等的，那么判断枚举的是否合法，否则强制要求不相等。

复杂度是 $\Theta(n\times3^4)$，可以通过。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define double long double
#define mid ((l+r)>>1)
using namespace std;
const int mod=1e9+7;
int qp(int a,int b){
	int ans=1;
	while(b){
		if(b&1) ans=(ans*a)%mod;
		a=(a*a)%mod;
		b>>=1;
	}
	return ans;
}
int fac[10000005],inv[10000005];
void init(){
	fac[0]=1;
	for(int i=1;i<=10000000;i++) fac[i]=fac[i-1]*i%mod;
	inv[10000000]=qp(fac[10000000],mod-2);
	for(int i=9999999;i>=0;i--) inv[i]=inv[i+1]*(i+1)%mod;
}
int C(int i,int j){
	if(i<0||j<0||i<j) return 0;
	return fac[i]*inv[i-j]%mod*inv[j]%mod;
}
int dp[10005][3][3];
signed main(){
	init();
	int n;
	cin>>n;
	string s[2];
	cin>>s[0]>>s[1];
	if(s[0][0]==s[1][0]) dp[0][0][0]=dp[0][1][1]=dp[0][2][2]=1;
	else dp[0][0][1]=dp[0][1][2]=dp[0][2][0]=1,dp[0][0][2]=dp[0][1][0]=dp[0][2][1]=1;
	for(int i=1;i<n;i++){
		for(int j=0;j<3;j++){
			for(int k=0;k<3;k++){
				for(int l=0;l<3;l++){
					for(int m=0;m<3;m++){
						int ok=1;
						ok&=((s[0][i-1]!=s[0][i])^(j==l));
						ok&=((s[1][i-1]!=s[1][i])^(k==m));
						ok&=((s[0][i-1]!=s[1][i-1])^(j==k));
						ok&=((s[0][i]!=s[1][i])^(l==m));
						dp[i][l][m]=(dp[i][l][m]+dp[i-1][j][k]*ok)%mod;
					}
				}
			}
		}
	}
	int ans=0;
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			if(s[0][n-1]==s[1][n-1]&&i==j) ans=(ans+dp[n-1][i][j])%mod;
			if(s[0][n-1]!=s[1][n-1]&&i!=j) ans=(ans+dp[n-1][i][j])%mod;
		}
	}
	cout<<ans;
	return 0;
}

```

---

