# [ABC055D] Menagerie

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc055/tasks/arc069_b

すぬけくんは動物が好きなので動物園を作りました。

この動物園では $ 1,2,3,\ ...,\ N $ の番号を割り振られた $ N $ 匹の動物が円環状に並べられています。 $ i\ (2≦i≦N-1) $ 番の動物は $ i-1 $ 番の動物と $ i+1 $ 番の動物と隣り合っています。また、$ 1 $ 番の動物は $ N $ 番の動物と $ 2 $ 番の動物と隣り合っており、$ N $ 番の動物は $ N-1 $ 番の動物と $ 1 $ 番の動物と隣り合っています。

動物園には本当のことしか言わない正直者の羊と、嘘しか言わない嘘つきの狼の 2 種類の動物がいます。

すぬけくんには羊と狼の区別がつかないので、それぞれの動物に両隣の動物が同じ種類かどうかを訪ねたところ、$ i $ 番目の動物は $ s_i $ と答えました。$ s_i $ が `o` ならば両隣の動物が同じ種類であると、`x` ならば異なる種類であると $ i $ 番の動物が言ったことを示します。

より形式的には、羊は両隣の動物がどちらも羊あるいはどちらも狼のとき `o` と答え、そうでないとき `x` と答えます。 狼は両隣の動物がどちらも羊あるいはどちらも狼のとき `x` と答え、そうでないとき `o` と答えます。

これらの回答結果と矛盾しないような各動物の種別の割り当てが存在するか、すぬけくんは気になっています。存在するならば一例を示し、存在しないならば `-1` を出力しなさい。

## 说明/提示

### 制約

- $ 3\ ≦\ N\ ≦\ 10^{5} $
- $ s $ は `o` と `x` のみからなる長さ $ N $ の文字列

### Sample Explanation 1

例えば $ 1,2,3,4,5,6 $ 番の動物がそれぞれ羊、羊、羊、狼、狼、羊であるとき発言と矛盾しません。その他、狼、羊、狼、羊、狼、狼であるようなときも矛盾しません。 両隣が同じ種類の動物のとき羊は `o` と発言し、狼は `x` と発言すること、 両隣が異なる種類の動物のとき羊は `x` と発言し、狼は `o` と発言することに注意してください。 !\[b34c052fc21c42d2def9b98d6dccd05c.png\](https://atcoder.jp/img/arc069/b34c052fc21c42d2def9b98d6dccd05c.png)

### Sample Explanation 2

存在しない場合は `-1` を出力してください。

## 样例 #1

### 输入

```
6
ooxoox```

### 输出

```
SSSWWS```

## 样例 #2

### 输入

```
3
oox```

### 输出

```
-1```

## 样例 #3

### 输入

```
10
oxooxoxoox```

### 输出

```
SSWWSSSWWS```

# 题解

## 作者：STARSczy (赞：4)

# 思路：
只有两种动物，羊说真话，狼说假话。那就只需枚举第 $1$ 和第 $2$ 只动物，根据前两只动物所说的话，判断第三只动物是什么。最后判断第 $n$，第 $1$、$2$ 只动物说的话是否都成立，如果成立，直接输出这种情况，否则往下枚举，如果都不行，就输出 $-1$。
# 代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int maxn=1e5+10;
int n,a[maxn],t[maxn];

bool f(int x,int y){
	t[1]=x,t[2]=y;
	for(int i=3;i<=n;++i) t[i]=(a[i-1]+t[i-1]+t[i-2])%2;//向下推算是那种动物
	if((t[n]+t[1]+t[2])%2==a[1]&&(t[n-1]+t[n]+t[1])%2==a[n]) return 1;//判断这种情况是否成立
	return 0;
}

void out(){//输出
	for(int i=1;i<=n;++i) if(!t[i]) printf("S");
	else printf("W");
}

signed main(){
	scanf("%lld\n",&n);
	for(int i=1;i<=n;++i) a[i]=(getchar()=='x');//如果相邻两只动物相同就记录为1
	if(f(0,0)) out();//枚举前两只动物
	else if(f(0,1)) out();
	else if(f(1,0)) out();
	else if(f(1,1)) out();
	else cout<<"-1";//都不行输出-1
	return 0;
}
```

---

## 作者：songzhixin (赞：2)

## 题目大意

有一些动物围成了一个圆圈，这些动物只有可能是狼或羊。

羊是诚实的，如果这个地方是 `o`，则左右两边的动物是相同的；如果是 `x`，则左右两边的动物是不同的。

羊是不诚实的，如果这个地方是 `o`，则左右两边的动物是不同的；如果是 `x`，则左右两边的动物是相同的。

## 解题思路

我们如果把它当做环来考虑，不太容易想到思路，所以我们考虑破环成链，但是我们其实不需要把它复制两倍，后面说原因。

我们可以发现这一个链具有传导性，即我们知道连续的两个是羊还是狼，就可以知道这条链上剩下的是什么动物了。因此，我们可以枚举链上前两个动物是羊还是狼，则一共有四种情况，如下：

$$ \begin{cases} SS \\ SW \\ WS \\ WW \end{cases} $$

具体怎么传导呢？

根据题目我们可以发现，我们先从 $2$ 到 $n-1$ 遍历一遍，对于每一个 $i$，必是一下情况之一：

$$ \begin{cases} b_{i+1}=b{i-1} & b_i=S且S_i=o \\ b_{i+1}=b{i-1} \oplus 1 & b_i=S且S_i=x \\ b_{i+1}=b{i-1} \oplus 1 & b_i=W且S_i=o \\ b_{i+1}=b{i-1} & b_i=W且S_i=x \end{cases} $$

最后怎么判断合不合法呢，我们可以用到上面破环成链没有复制的位置，即 $1$ 即 $n$。如果满足以下条件之一就不合法：

$$ \begin{cases} s_1=o且b_1=S且b_2\ne b_n \\ s_1=o且b_1=W且b_2 = b_n \\ s_1=x且b_1=S且b_2=b_n \\ s_1=x且b_1=W且b_2\ne b_n \\ s_n=o且b_n=S且 b_1 \ne b_{n-1} \\ s_n=o且b_n=W且 b_1 = b_{n-1} \\ s_n=x且b_n=S且 b_1 = b_{n-1} \\ s_n=x且b_n=W且 b_1 \ne b_{n-1} \end{cases} $$

所以如果不满足以上任意一条件，就是一个合法的序列，直接输出即可。

## 正确代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
char a[N];
int b[N];
int n;
void dfs(int x,int y) {
	b[1]=x;
	b[2]=y;
	for(int i=2; i<n; i++) {
		if(b[i]==0&&a[i]=='o') {
			b[i+1]=b[i-1];
		}
		if(b[i]==1&&a[i]=='o') {
			b[i+1]=b[i-1]^1;
		}
		if(b[i]==0&&a[i]=='x') {
			b[i+1]=b[i-1]^1;
		}
		if(b[i]==1&&a[i]=='x') {
			b[i+1]=b[i-1];
		}
	}
	if(a[1]=='o'&&b[1]==0){
		if(b[2]!=b[n]){
			return;
		}
	}
	if(a[1]=='x'&&b[1]==0){
		if(b[2]==b[n]){
			return;
		}
	}
	if(a[1]=='o'&&b[1]==1){
		if(b[2]==b[n]){
			return;
		}
	}
	if(a[1]=='x'&&b[1]==1){
		if(b[2]!=b[n]){
			return;
		}
	}
	if(a[n]=='o'&&b[n]==0){
		if(b[n-1]!=b[1]){
			return;
		}
	}
	if(a[n]=='x'&&b[n]==0){
		if(b[n-1]==b[1]){
			return;
		}
	}
	if(a[n]=='o'&&b[n]==1){
		if(b[n-1]==b[1]){
			return;
		}
	}
	if(a[n]=='x'&&b[n]==1){
		if(b[n-1]!=b[1]){
			return;
		}
	}
	for(int i=1;i<=n;i++){
		if(b[i]==0){
			printf("S");
		}
		else{
			printf("W");
		}
	}
	exit(0);
}
int main() {
	scanf("%d",&n);
	scanf("%s",a+1);
	dfs(0,0);
	dfs(1,0);
	dfs(0,1);
	dfs(1,1);
	printf("-1\n");
	return 0;
}
```

---

## 作者：shitingjia (赞：2)

[传送门](https://www.luogu.com.cn/problem/AT_arc069_b)

### 前言
此篇题解中，不带有递推式、异或等一系列~~我看不懂~~需要推理的操作，纯逻辑，但是代码较长，可以把思路梳理一遍，自行练习。

### 题目思路
$3 \le N \le 10^5$，搜索肯定是行不通的。但是仔细看题目条件，其实并不需要把所有动物都枚举一次。

当我们知道第 $1$ 只动物和第 $2$ 只动物是什么的时候，再根据它们说的话，就可以知道第 $3$ 只、第 $4$ 只一直到第 $N$ 只动物是什么。有点多米诺骨牌的感觉。

现在只要枚举前两只动物（四种情况），每次推出剩下所有动物的种类，然后检验是否合法。

检验处一：第 $N-1$ 只、第 $N$ 只和第 $1$ 只之间的关系。

检验处二：第 $N$ 只、第 $1$ 只和第 $2$ 只之间的关系。

两处判断只要有一处不合法，立即返回 $0$，否则返回 $1$。

**警告：代码很长，慎看**

### AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int n;
char c[N];
bool ans[N];
bool hs(int x,int y){
	memset(ans,0,sizeof(ans));
	ans[1]=x;ans[2]=y;
	for(int i=3;i<=n;i++){//推出剩下所有动物
		if(c[i-1]=='o'){
			if(!ans[i-1])	ans[i]=ans[i-2];
			else ans[i]=!ans[i-2];
		}
		else{
			if(!ans[i-1])	ans[i]=!ans[i-2];
			else ans[i]=ans[i-2];
		}
	}
	bool g=1;
	if(!ans[n]){//第n只动物是羊
		if(c[n]=='o'&&ans[n-1]==ans[1])	g=1;
		else if(c[n]=='x'&&ans[n-1]!=ans[1])	g=1;
		else g=0;
		if(!g)	return 0;//注意这里不能忘！
		if(!ans[1]){//第1只动物是羊
			if(c[1]=='o'&&!ans[2])	g=1;
			else if(c[1]=='x'&&ans[2])	g=1;
			else g=0;
		}
		else{//第1只动物是狼
			if(c[1]=='o'&&ans[2])	g=1;
			else if(c[1]=='x'&&!ans[2])	g=1;
			else g=0;
		}
		return g;
	}
	else{//第n只动物是狼
		if(c[n]=='o'&&ans[n-1]!=ans[1])	g=1;
		else if(c[n]=='x'&&ans[n-1]==ans[1])	g=1;
		else g=0;
		if(!g)	return 0;
		if(!ans[1]){//第1只动物是羊
			if(c[1]=='o'&&ans[2])	g=1;
			else if(c[1]=='x'&&!ans[2])	g=1;
			else g=0;
		}
		else{//第1只动物是狼
			if(c[1]=='o'&&!ans[2])	g=1;
			else if(c[1]=='x'&&ans[2])	g=1;
			else g=0;
		}
		return g;
	}
}
void ed(){//输出答案
	for(int i=1;i<=n;i++){
		if(ans[i])	cout<<"W";
		else cout<<"S";
	}
	cout<<"\n";
	exit(0);
}
int main(){
	ios::sync_with_stdio(false);
	cin>>n;
	for(int i=1;i<=n;i++)	cin>>c[i];
	//0是羊，1是狼 
	if(hs(0,0))	ed();
	if(hs(0,1))	ed();
	if(hs(1,0))	ed();
	if(hs(1,1))	ed();
	cout<<"-1";
	return 0;
}
```

---

## 作者：Krimson (赞：2)

轻松就可以发现只要确定了序列中任意连续的两个就可以确定整个序列。  
简单证明一下    

假设目前已知$a_{i-1},a_{i}$那么根据$a_{i}$是否是狼或者羊、$a_i$ 说左右是否相等就能判断出$a_{i+1}$   

于是只要去枚举开头的1和2分别是狼和羊，就可以得到整个序列了,分别去枚举,因为是环状，所以最后判断一下$a_1,a_2,a_{n-1},a_{n}$是否矛盾就好了  
这里提供一种比较方便的写法,就不用写很多if和else了(注释懒得写了,应该很好了解,因为第i位是狼或羊与第i位是o还是x满足异或的关系,在知道这一点之后去理解代码就行了)  

------------
以下用$kd[i]$表示第$i$位是否是$o$,如果是$o$则为1，否则为0  
$wh[i]$表示第$i$位是狼还是羊，如果是狼则为1，否则为0  
$x \ xor \ y=0$,当且仅当$x=y$  
1.如何递推  
```cpp
 if(kd[i-1]^wh[i-1]) wh[i]=wh[i-2];
 else wh[i]=wh[i-2]^1;
```  
2.如何判断
```cpp
if(!((wh[1]==wh[n-1])^(kd[n])^wh[n])&&!((wh[n]==wh[2])^kd[1]^wh[1])){
        for(ri i=1;i<=n;++i) wh[i]?putchar('W'):putchar('S');
        return 0;
    }
```
~~如果没看懂的话就自己举几个例子手模一下~~


------------
以下是AC代码  
```cpp
#include<bits/stdc++.h>
using namespace std;
#define il inline
#define ri register int
#define ll long long
il ll read(){
    bool f=true;ll x=0;
    register char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-') f=false;ch=getchar();}
    while(ch>='0'&&ch<='9') x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
    if(f) return x;
    return ~(--x);
}
il void write(const ll &x){if(x>9) write(x/10);putchar(x%10+'0');}
il void print(const ll &x) {x<0?putchar('-'),write(~(x-1)):write(x);putchar('\n');}
il int max(const int &a,const int &b){return a>b?a:b;}
il int min(const int &a,const int &b){return a<b?a:b;}
/*
其实这个序列只需要开头两个就能确定下来
*/
const int MAXN=1e5+7;
int kd[MAXN];
// vector f[MAXN][2];
int wh[MAXN];
int main(){
    int n=read();
    for(ri i=1;i<=n;++i) if(getchar()=='o') kd[i]=1;
    wh[1]=wh[2]=1;//1是狼，0是羊
    for(ri i=3;i<=n;++i){
        if(kd[i-1]^wh[i-1]) wh[i]=wh[i-2];
        else wh[i]=wh[i-2]^1;
    }
    if(!((wh[1]==wh[n-1])^(kd[n])^wh[n])&&!((wh[n]==wh[2])^kd[1]^wh[1])){
        for(ri i=1;i<=n;++i) wh[i]?putchar('W'):putchar('S');
        return 0;
    }
    wh[1]=1,wh[2]=0;
    for(ri i=3;i<=n;++i){
        if(kd[i-1]^wh[i-1]) wh[i]=wh[i-2];
        else wh[i]=wh[i-2]^1;
    }
    if(!((wh[1]==wh[n-1])^(kd[n])^wh[n])&&!((wh[n]==wh[2])^kd[1]^wh[1])){
        for(ri i=1;i<=n;++i) wh[i]?putchar('W'):putchar('S');
        return 0;
    }
    wh[1]=0,wh[2]=1;
    for(ri i=3;i<=n;++i){
        if(kd[i-1]^wh[i-1]) wh[i]=wh[i-2];
        else wh[i]=wh[i-2]^1;
    }
    if(!((wh[1]==wh[n-1])^(kd[n])^wh[n])&&!((wh[n]==wh[2])^kd[1]^wh[1])){
        for(ri i=1;i<=n;++i) wh[i]?putchar('W'):putchar('S');
        return 0;
    }
    wh[1]=wh[2]=0;
    for(ri i=3;i<=n;++i){
        if(kd[i-1]^wh[i-1]) wh[i]=wh[i-2];
        else wh[i]=wh[i-2]^1;
    }
    if(!((wh[1]==wh[n-1])^(kd[n])^wh[n])&&!((wh[n]==wh[2])^kd[1]^wh[1])){
        for(ri i=1;i<=n;++i) wh[i]?putchar('W'):putchar('S');
        return 0;
    }
    puts("-1");
    return 0;
}
```


---

## 作者：ny_jerry2 (赞：1)

### 思路
纯模拟题。

只需要去枚举一下前两只动物的状态，然后可以顺势推出以后所有动物的状态。

枚举的串可能不合法，因此需要判断。  
具体就是看一下第一个和最后一个，检查一下他们的左右动物的状态，以及他自己的反应（就是输入的字符串）。

如果合法那就是一个可行解。

这道题可能有多个可行解，但答案只有一个，因此我被坑了 $16$ 分（只不过是在其他网站上）。

### 代码
```cpp
#include<iostream>
using namespace std;
int n;
const int N=5e5+10;
char s[N];
char ans[N];
void f1(){
	ans[1]='S',ans[2]='S';
	for(int i=3;i<=n;i++){
		if(s[i-1]=='o'){
			if(ans[i-1]=='S'){
				ans[i]=ans[i-2];
			}else{
				if(ans[i-2]=='S'){
					ans[i]='W';
				}else{
					ans[i]='S';
				}
			}
		}else{
			if(ans[i-1]=='S'){
				if(ans[i-2]=='W'){
					ans[i]='S';
				}else{
					ans[i]='W';
				}
			}else{
				ans[i]=ans[i-2];
			}
		}
	}
	if(ans[1]=='S'){
		if((s[1]=='o'&&ans[2]!=ans[n])||(s[1]=='x'&&ans[2]==ans[n])){
			return;
		}
	}else{
		if((s[1]=='o'&&ans[2]==ans[n])||(s[1]=='x'&&ans[2]!=ans[n])){
			return;
		}
	}
	if(ans[n]=='W'){
		if((s[n]=='o'&&ans[n-1]==ans[1])||(s[n]=='x'&&ans[n-1]!=ans[1])){
			return;
		}
	}else{
		if((s[n]=='o'&&ans[n-1]!=ans[1])||(s[n]=='x'&&ans[n-1]==ans[1])){
			return;
		}
	}
	for(int i=1;i<=n;i++){
		cout<<ans[i];
	}
	exit(0);
}
void f2(){
	ans[1]='S',ans[2]='W';
	for(int i=3;i<=n;i++){
		if(s[i-1]=='o'){
			if(ans[i-1]=='S'){
				ans[i]=ans[i-2];
			}else{
				if(ans[i-2]=='S'){
					ans[i]='W';
				}else{
					ans[i]='S';
				}
			}
		}else{
			if(ans[i-1]=='S'){
				if(ans[i-2]=='W'){
					ans[i]='S';
				}else{
					ans[i]='W';
				}
			}else{
				ans[i]=ans[i-2];
			}
		}
	}
	if(ans[1]=='S'){
		if((s[1]=='o'&&ans[2]!=ans[n])||(s[1]=='x'&&ans[2]==ans[n])){
			return;
		}
	}else{
		if((s[1]=='o'&&ans[2]==ans[n])||(s[1]=='x'&&ans[2]!=ans[n])){
			return;
		}
	}
	if(ans[n]=='W'){
		if((s[n]=='o'&&ans[n-1]==ans[1])||(s[n]=='x'&&ans[n-1]!=ans[1])){
			return;
		}
	}else{
		if((s[n]=='o'&&ans[n-1]!=ans[1])||(s[n]=='x'&&ans[n-1]==ans[1])){
			return;
		}
	}
	for(int i=1;i<=n;i++){
		cout<<ans[i];
	}
	exit(0);
}
void f3(){
	ans[1]='W',ans[2]='W';
	for(int i=3;i<=n;i++){
		if(s[i-1]=='o'){
			if(ans[i-1]=='S'){
				ans[i]=ans[i-2];
			}else{
				if(ans[i-2]=='S'){
					ans[i]='W';
				}else{
					ans[i]='S';
				}
			}
		}else{
			if(ans[i-1]=='S'){
				if(ans[i-2]=='W'){
					ans[i]='S';
				}else{
					ans[i]='W';
				}
			}else{
				ans[i]=ans[i-2];
			}
		}
	}
	if(ans[1]=='S'){
		if((s[1]=='o'&&ans[2]!=ans[n])||(s[n]=='x'&&ans[2]==ans[n])){
			return;
		}
	}else{
		if((s[1]=='o'&&ans[2]==ans[n])||(s[n]=='x'&&ans[2]!=ans[n])){
			return;
		}
	}
	if(ans[n]=='W'){
		if((s[n]=='o'&&ans[n-1]==ans[1])||(s[n]=='x'&&ans[n-1]!=ans[1])){
			return;
		}
	}else{
		if((s[n]=='o'&&ans[n-1]!=ans[1])||(s[n]=='x'&&ans[n-1]==ans[1])){
			return;
		}
	}
	for(int i=1;i<=n;i++){
		cout<<ans[i];
	}
	exit(0);
}
void f4(){
	ans[1]='W',ans[2]='S';
	for(int i=3;i<=n;i++){
		if(s[i-1]=='o'){
			if(ans[i-1]=='S'){
				ans[i]=ans[i-2];
			}else{
				if(ans[i-2]=='S'){
					ans[i]='W';
				}else{
					ans[i]='S';
				}
			}
		}else{
			if(ans[i-1]=='S'){
				if(ans[i-2]=='W'){
					ans[i]='S';
				}else{
					ans[i]='W';
				}
			}else{
				ans[i]=ans[i-2];
			}
		}
	}
	if(ans[1]=='S'){
		if((s[1]=='o'&&ans[2]!=ans[n])||(s[1]=='x'&&ans[2]==ans[n])){
			return;
		}
	}else{
		if((s[1]=='o'&&ans[2]==ans[n])||(s[1]=='x'&&ans[2]!=ans[n])){
			return;
		}
	}
	if(ans[n]=='W'){
		if((s[n]=='o'&&ans[n-1]==ans[1])||(s[n]=='x'&&ans[n-1]!=ans[1])){
			return;
		}
	}else{
		if((s[n]=='o'&&ans[n-1]!=ans[1])||(s[n]=='x'&&ans[n-1]==ans[1])){
			return;
		}
	}
	for(int i=1;i<=n;i++){
		cout<<ans[i];
	}
	exit(0);
}
int main(){
//	freopen("animal.in","r",stdin);
//	freopen("animal.out","w",stdout);
	cin>>n;
	scanf("%s",s+1);
	f1();
	f2();
	f3();
	f4();
	cout<<-1;
	return 0;
}
```

---

## 作者：tian720 (赞：1)

题目传送门：[[ABC055D] Menagerie](https://www.luogu.com.cn/problem/AT_arc069_b)。
## 思路：
主要为**枚举+递推**，我们发现整个环具有依赖性，因此只要确定了开头两个连续的动物，就可以从左到右递推出每一个动物，最后再判断首尾是否成立就可以了。枚举部分可以用二进制，如果所有情况都不满足要求，则输出 $-1$。

取反 $0$ 和 $1$ 可以直接异或 $1$，这相当于模 $2$ 下的加 $1$ 操作。

## 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=100010;
int n,t[N];
char a[N];
bool check(){//1代表羊，0代表狼 
	for(int i=2;i<=n;i++){
		if(t[i]==1){
			if(a[i]=='o') t[i+1]=t[i-1];
			else t[i+1]=(t[i-1]^1);
		}
		else{
			if(a[i]=='o') t[i+1]=(t[i-1]^1);
			else t[i+1]=t[i-1];
		}
	}
	if(t[1]==1){
		if(a[1]=='o'){
			if(t[2]!=t[n]) return false;
		}
		else{
			if(t[2]==t[n]) return false;
		}
	}
	else{
		if(a[1]=='o'){
			if(t[2]==t[n]) return false;
		}
		else{
			if(t[2]!=t[n]) return false;
		}
	}
	if(t[n]==1){
		if(a[n]=='o'){
			if(t[n-1]!=t[1]) return false;
		}
		else{
			if(t[n-1]==t[1]) return false;
		}
	} 
	else{
		if(a[n]=='o'){
			if(t[n-1]==t[1]) return false;
		}
		else{
			if(t[n-1]!=t[1]) return false;
		}
	}
	return true;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	bool flag=0;
	for(int op=0;op<(1<<2);op++){//二进制枚举 
		for(int k=0;k<=1;k++){
			if((op>>k)&1) t[k+1]=0;
			else t[k+1]=1;
		}
		if(check()) break;
	} 
	if(!check()){
		puts("-1");
		return 0;
	}
	for(int i=1;i<=n;i++){
		if(t[i]==1) cout<<"S";
		else cout<<"W";
	}
	return 0;
}
```
这种先枚举再递推的思路十分经典，类似的题还有[[SCOI2005] 扫雷](https://www.luogu.com.cn/problem/P2327)和[费解的开关](https://www.luogu.com.cn/problem/P10449)。读者有兴趣可以自行练习。

---

## 作者：little_sheep917 (赞：1)

分析一下题目，在题目中，只要有连续两个动物确定下来了，就可以模拟出所有的动物，再检查其中的连续两个动物（一个不算数，为什么？不用讲了吧）说的话，就可以确定是不是正确的解。

```cpp
#include<bits/stdc++.h>
using namespace std;

char p[100005];
int S[100005],P[100005],n; 

int main(){
	scanf("%d%s",&n,&p);
	for(int i=0;i<n;i++){
		if(p[i]=='o') P[i+1]=0;
		else P[i+1]=1;
	}
	P[n+1]=P[1];
	for(int i=0;i<8;i++){
		S[0]=i&1;
		S[1]=(i>>1)&1;
		S[2]=(i>>2)&1;
		for(int j=2;j<=n+1;j++){
			S[j+1]=S[j-2]^P[j];
		}
		if((S[0]^S[1]^S[n]^S[n+1])||(S[1]^S[2]^S[n+1]^S[n+2])) continue;
		for(int j=1;j<=n;j++){
			printf("%c",(S[j-1]^S[j])?'W':'S');
		}
		return 0;
	}
	printf("-1\n");
	return 0;
} 
```

---

## 作者：xibaohe (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_arc069_b)



------------


# 题目大意
在动物园中**环形**展出狼和羊两种动物，狼说假话，羊说真话。告诉你狼和羊关于左右动物类型的陈述，试问能否求出一种符合陈述的展览方法。

# 题目思路
这道题可以用暴力来做，但肯定无法拿到满分。但是我们可以根据**连续**两个动物的类别和其中一个动物的陈述判断第三个动物的性别，即通过减少循环次数进行**优化**。



# 注意事项
 - 题目中是以环形展出，输入是一条线，因此我们要在输入字符串后加上字符串的前两位。
 
 - 狼说的是假话，要对狼的陈述取反。
 
# 初始情况
由于我们根据**连续**两个动物的类别和其中一个动物的陈述判断第三个动物的性别，因此开头的两个动物需要我们来定，在这里共有四种情况：

 - 羊羊
 
 - 羊狼
 
 - 狼羊
 
 - 狼狼
 
为什么用以上的排序呢？因为题目要求输出字典序最靠前的，据题目，羊的字典序比狼更靠前，故如此排序。
 
 
# 真实性判断
如何判断答案的正确性呢？我们只要推出答案，再看答案的最后一位、答案的第一位、答案的第二位是否符合陈述即可。


# 思路图解
我看到已有的几篇题解都没有出示举例的图解，于是我在题解中添加了思路的**图解**。

![](https://cdn.luogu.com.cn/upload/image_hosting/b6eukq2g.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/c49rf41z.png)
 
 
# 满分代码
我把其他一些小细节都写进了代码里。
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
int n;
bool flag=false;//flag用来存是否有答案
string s,ans1,ans2,ans3,ans4,ans;
char chg[110];//难点1：chg数组用来进行o与x，S与W的转换
string show(string t)//show函数用来搜答案
{
	for(int i=2;i<=n+1;i++)//搜答案
	{
		char k;
		if(t[i-1]=='S') k=s[i-1];
		else k=chg[s[i-1]];
		if(k=='o') t+=t[i-2];
		else t+=chg[t[i-2]];
	}
	if(t[0]==t[n]&&t[1]==t[n+1]) flag=true;
	/*难点4：看答案的最后一位、答案的第一位、答案的第二位判断真实性*/
	return t;//返回搜索完的字符串
}
int main(){
	cin>>n;
	cin>>s;
	s+=s[0];//难点2：加上陈述的第1位
	s+=s[1];//难点2：加上陈述的第2位
	chg['o']='x';//设置转换函数
	chg['x']='o';//设置转换函数
	chg['S']='W';//设置转换函数
	chg['W']='S';//设置转换函数
	/*难点3：由于羊是S，狼是W，因此羊的字典序更靠前*/
	ans1="SS";//设置初始字符串
	ans3="WS";//设置初始字符串
	ans2="SW";//设置初始字符串
	ans4="WW";//设置初始字符串
	ans=show(ans1);//搜索ans1
	if(flag)
	{
		ans=ans.substr(0,n);//用substr函数把输入时加上的最后两位删去
		cout<<ans<<endl;
		return 0;
	}
	ans=show(ans2);//搜索ans2
	if(flag)
	{
		ans=ans.substr(0,n);//用substr函数把输入时加上的最后两位删去
		cout<<ans<<endl;
		return 0;
	}
	ans=show(ans3);//搜索ans3
	if(flag)
	{
		ans=ans.substr(0,n);//用substr函数把输入时加上的最后两位删去
		cout<<ans<<endl;
		return 0;
	}
	ans=show(ans4);//搜索ans4
	if(flag)
	{
		ans=ans.substr(0,n);//用substr函数把输入时加上的最后两位删去
		cout<<ans<<endl;
		return 0;
	}
	cout<<-1<<endl;//没有答案，输出-1
	return 0;
}
```



---

## 作者：small_john (赞：1)

## 分析

其实很简单。

我们只要知道了前两个动物的种类，就可以推出所有动物的种类。那么思路就是，枚举前两个动物的种类即可。

但如果每种情况都讨论的话未免太复杂，所以我们考虑一种简化方法。

| 前两个动物的种类 | 第 $2$ 个动物的回答 | 第 $3$ 个动物的种类 |
| :----------: | :----------: | :----------: |
| SS | o | S |
| SS | x | W |
| SW | o | W |
| SW | x | S |
| WS | o | W |
| WS | x | S |
| WW | o | S |
| WW | x | W |

找规律得，如果设 $S$ 为 $1$，$W$ 为 $0$，$o$ 为 $1$，$x$ 为 $0$，则第三个动物种类为 $(a_2+b_1+b_2)\bmod 2$，所以递推式为 $b_i = (b_{i-1}+b_{i-2}+a_{i-1})\bmod 2$。

推出所有动物的种类之后，还要进行验证，前两个动物往前两个在环的情况下与其他的不一样，需要特判。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5+5;
int n;
bool a[N],b[N];
char in[N];
bool ok(int x,int y)
{
	b[1] = x,b[2] = y;
	for(int i = 3;i<=n;i++)
		b[i] = (a[i-1]+b[i-1]+b[i-2])%2;
	return b[1]==(a[n]+b[n]+b[n-1])%2&&b[2]==(a[1]+b[1]+b[n])%2;
}
void print()
{
	for(int i = 1;i<=n;i++)
		if(b[i]) cout<<'S';
		else cout<<'W';
}
signed main()
{
	cin>>n>>(in+1);
	for(int i = 1;i<=n;i++)
		a[i] = (in[i]=='o');
	for(int i = 0;i<=1;i++)
		for(int j = 0;j<=1;j++)
			if(ok(i,j))
				return print(),0;
	cout<<-1;
	return 0;
}
```

---

## 作者：Phoenix114514 (赞：0)

# AT_arc069_b ABC055D
## Menagerie
此乃本 programer 第一篇题解，求过！
### 思路 
暴力枚举第一和第二个动物，因为有五种情况，所以四次暴力+输出没有这种范围，即程序中的五条判断语句，第 32-36 行，再判断是否符合。

算法：暴力枚举+递归+记忆化。
##  _Code_ 
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+10;
int n,a[maxn],t[maxn];
bool check_True_or_False(int x,int y){
    t[1]=x;
    t[2]=y;
    for(int i=3;i<=n;++i) t[i]=(a[i-1]+t[i-1]+t[i-2])%2;
    if((t[n]+t[1]+t[2])%2==a[1]&&(t[n-1]+t[n]+t[1])%2==a[n])return 1;
    return 0;
}
void std_print(){
    for(int i=1;i<=n;++i){
        if(!t[i])printf("S");
        else printf("W");
    }
}
int main(){
    scanf("%lld\n",&n);
    for(int i=1;i<=n;++i){
        char c;
        scanf("%c",&c);
        if (c=='x')a[i]=1;
    }
    if(check_True_or_False(0,0))std_print();
    else if(check_True_or_False(0,1))std_print();
    else if(check_True_or_False(1,0))std_print();
    else if(check_True_or_False(1,1))std_print();
    else printf("%s","-1");
    return 0;
}
```

---

## 作者：C20212724杨京朝 (赞：0)

10分钟敲完但是找bug找了20min，~~就为了蹭个题解~~，我容易吗我

------------
咳咳，言归正传，这个题其实是一点点数学加上99%的暴力，我们不妨考虑，如何能得到某个位置是狼还是羊，能得到一个就能得到下一个，个人觉得跟递推很像。

前提：我们知道每个位置说的是x还是o

如果知道整个序列中的一个数，那么是无法推出左右两边的（因为跟这个数没有关系），相反，如果我们知道相邻位置上的两个数，那么就可以推出第三个数:

```
1 2 -> 3

2 3 -> 4
......
```
这个很容易想通的，代码里会有更详细的操作
![图片来自于网络](https://img-blog.csdn.net/20180522184045774?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L21laXR1YW53YWltYWk=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)

我们可以枚举开头的两个数，四种情况：羊羊，狼狼，羊狼，狼羊~~~~和平~~~~
最后check一下

------------
代码：
```cpp
#include <cstdio>
int ans[100005],n;
char a[100005];
int check() {
	for(int i = 1;i <= n;i ++) {
		int l = i - 1,r = i + 1;
		if(l == 0) l = n; 
		if(r == n + 1) r = 1;//虽然我们用数组处理，但其实这是个环，所以要特判
		if(ans[i] == 1) {
			if(a[i] == 'o' && ans[l] != ans[r]) return 0;
			if(a[i] == 'x' && ans[l] == ans[r]) return 0;
		}
		else {
			if(a[i] == 'o' && ans[l] == ans[r]) return 0;
			if(a[i] == 'x' && ans[l] != ans[r]) return 0;
		}//如果不满足题意就不行，return 0，表否定
	}
	return 1;
}
void init() {
	for(int i = 2;i <= n - 1;i ++) {//讲的很清楚了，就是简单的数学推理，类似于递推，如果这都不懂建议左转再看一遍题
		if(ans[i] == 1) {
			if(a[i] == 'o') ans[i + 1] = ans[i - 1];
			if(a[i] == 'x') {
				if(a[i] == 'o') ans[i + 1] = ans[i - 1];
				else ans[i + 1] = (ans[i - 1] == 1?2:1);
			}
		}
		if(ans[i] == 2) {
			if(a[i] == 'x') ans[i + 1] = ans[i - 1];
			if(a[i] == 'o') {
				if(a[i] == 'o') ans[i + 1] = (ans[i - 1] == 1?2:1);
				else ans[i + 1] = ans[i - 1];
			}
		}
	}
}

void print() {
	for(int i = 1;i <= n;i ++) {
		if(ans[i] == 1) printf("S");
		else printf("W");
	}
}//ans记录答案，打包成函数输出比较简单
int main() {
	scanf("%d",&n);
	scanf("%s",a + 1);
	ans[1] = ans[2] = 1;
	init();
	if(check()) {
		print();
		printf("\n");
		return 0;
	}
	ans[1] = ans[2] = 2;
	init();
	if(check()) {
		print();
		printf("\n");
		return 0;
	}
	ans[1] = 1,ans[2] = 2;
	init();
	if(check()) {
		print();
		printf("\n");
		return 0;
	}
	ans[1] = 2,ans[2] = 1;
	init();
	if(check()) {
		print();
		printf("\n");
		return 0;
	}//四种枚举，check后输出，如果全都不行输出-1
	printf("-1\n");
	return 0;
} 
```


---

## 作者：shaozhehan (赞：0)

[原题链接](https://www.luogu.com.cn/problem/AT_arc069_b)

[AtCoder 链接](https://atcoder.jp/contests/abc055/tasks/arc069_b?lang=ja)

题目大意：

有一个人养了一群动物。这群动物里每一只动物不是狼就是羊，羊只说真话，狼只说假话。这个人脸盲，无法分辨羊和狼。一天，他为了分辨出每只动物是羊还是狼，把动物们排成了一圈，分别对每只动物询问：“你两旁的动物种类相同吗？”如果命题为真，羊回答 $\texttt{o}$，狼回答 $\texttt{x}$，否则羊回答 $\texttt{x}$，狼回答 $\texttt{o}$。$\texttt{S}$ 代表羊，$\texttt{W}$ 代表狼，如果有多组排列符合，输出字典序最小的动物种类排列。如果没有，输出 $\texttt{-1}$。

思路：

为了让后面的计算方便，我们可以把第 $1$ 个字符添加到回答的字符串 $s$ 后面去。

我们可以发现，如果第一只动物和第二只动物的种类都确定下来的话，后面的动物种类就都确定下来了。

- 如果第 $i$ 只动物是羊：
	- 如果它的回答是 $\texttt{o}$，那么第 $i+1$ 只动物的种类和第 $i-1$ 只动物相同。
   - 如果它的回答是 $\texttt{x}$，那么第 $i+1$ 只动物的种类和第 $i-1$ 只动物相反。
- 如果第 $i$ 只动物是狼：
	- 如果它的回答是 $\texttt{o}$，那么第 $i+1$ 只动物的种类和第 $i-1$ 只动物相反。
   - 如果它的回答是 $\texttt{x}$，那么第 $i+1$ 只动物的种类和第 $i-1$  只动物相同。

我们可以写出判断前两个动物种类是否可行的代码。
```cpp
inline bool chk(const char &c1, const char &c2){// c1 和 c2 分别代表前两只动物的种类（S 代表羊，W 代表狼）
    // t 代表所有动物排成一排的种类
    t[1] = c1;
    t[2] = c2;
    for (int i = 2; i <= n + 1; i++){
        // 分如上四种情况
        if (s[i] == 'o' && t[i] == 'S'){
            t[i + 1] = t[i - 1];
        } else if (s[i] == 'o' && t[i] == 'W'){
            t[i + 1] = 'W' + 'S' - t[i - 1]; 
        } else if (s[i] == 'x' && t[i] == 'S'){
            t[i + 1] = 'W' + 'S' - t[i - 1];
        } else if (s[i] == 'x' && t[i] == 'W'){
            t[i + 1] = t[i - 1]; 
        }
    }
    if (t[n + 1] == t[1] && t[n + 2] == t[2]){// 验证
        return true;
    }
    return false;
}
```

这样，我们就可以把所有的动物遍历一下，按这四种情况分别分类讨论，最终验证最后两只动物是否跟前两只动物品种相同就可以了。

但是，我们还要枚举前两只动物的种类：

- 第 $1$ 只动物是羊，第 $2$ 只动物是羊。
- 第 $1$ 只动物是羊，第 $2$ 只动物是狼。
- 第 $1$ 只动物是狼，第 $2$ 只动物是羊。
- 第 $1$ 只动物是狼，第 $2$ 只动物是狼。

共四种情况。

这样，我们就可以按顺序枚举，确定下来字典序最小的排列。如果没有，输出 $\texttt{-1}$。

坑点：

1. 四种情况，不要打错或打丢！
1. 需要特判如果输入自相矛盾输出 $\texttt{-1}$！
1. 数组要开大一点，最好开成 ```char``` 类型的以便后续操作！

完整代码贴在[这里](https://www.luogu.com.cn/paste/waxxyuv7)。

---

## 作者：zhengzonghaoak (赞：0)

考虑到只要确定了前两只动物就可以推出整个环，我们枚举四种情况，递归推出后判断是否矛盾即可。代码贴上,注释中已经写的比较详细了。
```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
const int N=1e5+100;
int n;
string s;//输入的字符串 
int ls;//字符串的长度 
bool pd[N];//用来记录相同或者不同 
int c[N];//用来记录是羊还是狼 
int gz(int a,int b){
	memset(c,0,sizeof(c));//别忘清空 
	c[1]=a;//记录下来环的前两位 
	c[2]=b;
	for(int i=2;i<=n;i++){
		if(c[i]==pd[i]){//说明左右相同 
			c[i+1]=c[i-1];//那就让后一位等于前一位 
		}
		else{//左右不同 
			if(c[i-1]==1) c[i+1]=0;//与左边的反过来赋值 
			else c[i+1]=1;
		}
	}
	if(c[1]==pd[1]&&c[2]==c[n]){//注意，要判断两个地方，不然会出错
		if(c[n]==pd[n]&&c[n-1]==c[1]) return 1;//两项都符合就说明可以 
		else if(c[n]!=pd[n]&&c[n-1]!=c[1]) return 1;
		return 0;//有一项不符合 
	}
	else if(c[1]!=pd[1]&&c[2]!=c[n]){
		if(c[n]==pd[n]&&c[n-1]==c[1]) return 1;
		else if(c[n]!=pd[n]&&c[n-1]!=c[1]) return 1;
		return 0;
	}
	else return 0;//有一到两项不符合 
}
int main(){
	cin>>n;
	cin>>s;
	ls=s.length();
	for(int i=0;i<ls;i++){
		if(s[i]=='o') pd[i+1]=1;//1表示羊的相同和狼的不同 
		else pd[i+1]=0;//0表示羊的不同和狼的相同 
	}
	int flag=0;
	for(int i=0;i<=1;i++){//1表示羊，0表示狼 
		for(int j=0;j<=1;j++){
			if(gz(i,j)==1){//说明推出了一种合法环 
				flag=1;//打标记说明存在合法解 
				break;
			}
		}
		if(flag==1) break;//外层也要判断 
	}
	if(flag==0){//不存在合法环 
		cout<<"-1\n";
		return 0;
	}
	else{
		for(int i=1;i<=n;i++){//转换回来 
			if(c[i]==1) cout<<"S";//一表示羊 
			else cout<<"W";//零表示狼 
		}
		cout<<"\n";//ATCORDER要换行 
		return 0;//完结散花！！！ 
	}
}
```
跪求管理员大大通过！！！码字不易！！！

---

## 作者：_Above_the_clouds_ (赞：0)

# 思路：
设动物序列 $a$ 中狼表示 $1$，羊表示 $0$。设输入序列为 $s$，相同为 $0$，不同为 $1$，则 $s_i=(a_{i-1}+a_i+a_{i+1})\bmod 2$。因此，我们只需要枚举序列 $a$ 的前两项，就可以推出整个序列。记得最后还要判断序列是否矛盾。如果无解，就输出 $-1$。

# 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
char x;
int a[100005], t[100005];
bool solve(int x, int y) {
	t[1] = x, t[2] = y;
	for (int i = 3; i <= n; i++)
		t[i] = (a[i - 1] + t[i - 1] + t[i - 2]) % 2;//向下推算是那种动物
	if ((t[n] + t[1] + t[2]) % 2 == a[1] && (t[n - 1] + t[n] + t[1]) % 2 == a[n])//判断这种情况是否成立
		return 1;
	return 0;
}
int main() {
	cin >> n;//输入
	for (int i = 1; i <= n; i++) {
		cin >> x;
		if (x == 'x') a[i] = 1;//如果相邻两只动物相同就记录为1
	}
	for(int i=0;i<2;++i) for(int j=0;j<2;++j) if (solve(i, j)){//枚举前两只动物
		for (int i = 1; i <= n; i++) if (!t[i]) printf("S");
		else printf("W");
		return 0;
	}
	cout << -1;//都不行输出-1
	return 0;
}

---

