# [CERC2016] 外观分析 Appearance Analysis

## 题目描述

你在萨格勒布拍摄了一张电气工程与计算机“C”楼的照片，它的尺寸相同的窗户整齐地排列在行列上。一些窗户上画着美妙的图案，你现在正在尝试分析有多少本质不同的创意画。


我们用一个r行c列的矩形格子图来描述一张照片。每个窗户都占据了一个矩形区域，并且所有窗户都有着相同的尺寸。一个窗户里的每个格子要么是空白的（用“.”表示），要么是被画过的（用“+”表示）。两个窗户的图案被认为是相同的，当且仅当其中有一个窗户旋转90度、180度、270度或360度后，放在另一个窗户上会完全匹配（包括边框）。当比较图案时，我们不允许翻转窗户。


所有窗户都规则地分布在行列中，窗户之间的边框用一格“#”字符表示。确切地说，在上下相邻的两个窗户之间，有恰好一行“#”字符，同时在第一行窗户之上或者最后一行窗户之下，也有恰好一行“#”字符。同理，在左右相邻的两个窗户之间，有恰好一列“#”字符，同时在第一列窗户之左或者最后一列窗户之右，也有恰好一列“#”字符。窗户的行数与列数是任意的，窗户的长宽也是任意的，不一定是正方形。但是，每个窗户至少占据一个格子，而且所有窗户的尺寸都是相同的。


请统计有多少本质不同的创意画。


## 样例 #1

### 输入

```
11 16
################
#....#++++#+...#
#....#++.+#+...#
#....#.++.#++.+#
#....#....#++++#
################
#....#.+..#++++#
#..++#.+..#++.+#
#+...#....#.++.#
#+...#..++#....#
################```

### 输出

```
4```

# 题解

## 作者：Super_Cube (赞：2)

# Solution

求出每个窗户的横纵边长，然后将窗户内的样子进行哈希。算哈希的方法就正常打字符串哈希，不过要在换行处补上一个空字符把两行隔开。有点烦人的地方是窗户可以旋转，所以每个窗户会算出四个哈希值，要全部判断一遍才知道是否已经和前面的某个窗户重复了。没重复就把哈希值放入桶中，最后的答案即为桶中元素数量。

# Code

```cpp
#include<bits/stdc++.h>
typedef unsigned long long ull;
const ull P=173;
std::unordered_set<ull>mp;
char s[150][150];
int n,m,p,q;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;scanf("%s",s[i++]));
	for(int i=0;i<n;++i)p+=s[i][1]=='#';
	for(int i=0;i<m;++i)q+=s[1][i]=='#';
	p=(n-p)/(p-1);q=(m-q)/(q-1);
	for(int i=1;i<n;i+=p+1)
		for(int j=1;j<m;j+=q+1){
			static ull hash1,hash2,hash3,hash4;
			hash1=hash2=hash3=hash4=0;
			for(int x=0;x<p;++x){
				hash1=hash1*P+54;
				for(int y=0;y<q;++y)
					hash1=hash1*P+s[i+x][j+y];
			}
			for(int x=p-1;~x;--x){
				hash2=hash2*P+54;
				for(int y=q-1;~y;--y)
					hash2=hash2*P+s[i+x][j+y];
			}
			for(int y=q-1;~y;--y){
				hash3=hash3*P+54;
				for(int x=0;x<p;++x)
					hash3=hash3*P+s[i+x][j+y];
			}
			for(int y=0;y<q;++y){
				hash4=hash4*P+54;
				for(int x=p-1;~x;--x)
					hash4=hash4*P+s[i+x][j+y];
			}
			if(!mp.count(hash1)&&!mp.count(hash2)&&!mp.count(hash3)&&!mp.count(hash4))
				mp.insert(hash1);
		}
	printf("%d",mp.size());
	return 0;
}
```

---

## 作者：Chenaknoip (赞：2)

一道求字符串哈希的问题。

> Hash，一般翻译做散列、杂凑，或音译为哈希，是把任意长度的输入（又叫做预映射 pre-image）通过散列算法变换成固定长度的输出，该输出就是散列值。这种转换是一种压缩映射，也就是，散列值的空间通常远小于输入的空间，不同的输入可能会散列成相同的输出，所以不可能从散列值来确定唯一的输入值。简单的说就是一种将任意长度的消息压缩到某一固定长度的消息摘要的函数。

简单来说，就是把字符串转换为一组固定长度的数的方法。

因为时间复杂度问题，暴力判断可能无法通过此题目，故考虑哈希比较。

这里我们使用最常见的哈希计算法。

对于长度为 $n$ 的字符串 $s$，令 $hash _s = \sum _{i=0} ^{n-1} {(p ^ {n - i - 1} \times s _{i})}$，其中 $p$ 是一常数。

显然，对于同一个 $p$，任何字符串都对应唯一的一个哈希值；但每个哈希值都对应无穷多字符串。所以 $p$ 的取值对可能发生的“碰撞”有很大影响。

> 碰撞，即出现两个不同的字符串的哈希相同的情况。

在这里，我们使用 $131$ 作为 $p$ 的取值。这个数字并没有什么特殊的含义，只是发生碰撞的概率较小。

当然，你也可以使用 $1331$，$171$ 等数字进行尝试。

对于这道题目，只需要将画旋转四次，将其“拼接”成字符串后计算哈希即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ULL; 
int n, m;
string s[2010];
int cnt1 = 0, cnt2 = 0, ans = 0;
const int P = 43243;
map<ULL, bool> mp; // 记录哈希
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++) {
		cin >> s[i];
	}
	for (int i = 0; i < n; i++) {
		if (s[i][1] == '#') cnt1++;
	}
	for (int i = 0; i < m; i++) {
		if (s[1][i] == '#') cnt2++;
	}
	cnt1 = (n - cnt1) / (cnt1 - 1);
	cnt2 = (m - cnt2) / (cnt2 - 1); // 计算每幅画的长和宽
	for (int i = 1; i < n; i += cnt1 + 1) {
		for (int j = 1; j < m; j += cnt2 + 1) {
			ULL hash1 = 0, hash2 = 0, hash3 = 0, hash4 = 0;
			for (int k = 0; k < cnt1; k++) {
				for (int l = 0; l < cnt2; l++) {
					hash1 = hash1 * P + s[i + k][j + l]; // 计算哈希值，下同
				}
			}
            if (cnt1 == cnt2)
			for (int l = cnt2 - 1; l > -1; l--) {
				for (int k = 0; k < cnt1; k++) {
					hash2 = hash2 * P + s[i + k][j + l];
				}
			}
			for (int k = cnt1 - 1; k > -1; k--) {
				for (int l = cnt2 - 1; l > -1; l--) {
					hash3 = hash3 * P + s[i + k][j + l];
				}
			}
            if (cnt1 == cnt2)
			for (int l = 0; l < cnt2; l++) {
				for (int k = cnt1 - 1; k > -1; k--) {
					hash4 = hash4 * P + s[i + k][j + l];
				}
			}
			if (!mp.count(hash1)) {
				++ans;
				mp[hash1] = mp[hash2] = mp[hash3] = mp[hash4] = 1;
			}
			// cout << hex << "0x" << hash1 << " 0x" << hash2 << " 0x" << hash3 << " 0x" << hash4 << endl;
		}
	}
	printf("%d\n", ans);
	return 0;
}
```

---

## 作者：Error_Eric (赞：1)

### Statement

给定若干个 01 矩阵，如果旋转后相等我们认为两个矩阵相等。求不相等矩阵个数。

### Sol

考虑哈希。

四个方向哈希一遍，哈希出来的四个结果再哈希一遍，最后扔进 uset 里面统计次数就可以。

这里讲一个其他题解没有的细节：不能直接拼接字符串进行哈希。

以下两个矩阵

```plain
.+. ..+
.+. +..
```

都可以哈希出来 ``..++..`` 这个字符串。具体可以看 [我的这篇 hack](https://www.luogu.com.cn/discuss/722445)。

解决方式是要么像其他题解一样进行特判，要么在每次换行的时候用另外一种方式哈希一次。我选择后者。

### Code

```cpp
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<vector>
#include<map>
#include<unordered_set>
using namespace std;
typedef unsigned long long ull;
const ull P=0x217300badccfd5,R=0x114514ccfdead;
int r,c,pr=0,pc=0;
vector<string>a;
unordered_set<ull>us;
void fun(int x,int y){
    //cout<<x<<'&'<<y<<endl;
    ull hsh1=114,hsh2=114,hsh3=114,hsh4=114;
    for(int i=x;i<x+pr-1;i++){
        for(int j=y;j<y+pc-1;j++)
            ((hsh1<<=1)|=(a[i][j]=='.'))%=P;//,cout<<a[i][j];
        (((hsh1*=3)%=P)+=R)%=P; //cout<<endl;
    }
    for(int j=y;j<y+pc-1;j++){
        for(int i=x+pr-2;i>=x;i--)
            ((hsh2<<=1)|=(a[i][j]=='.'))%=P;
        (((hsh2*=3)%=P)+=R)%=P;
    }
    for(int i=x+pr-2;i>=x;i--){
        for(int j=y+pc-2;j>=y;j--)       
            ((hsh3<<=1)|=(a[i][j]=='.'))%=P;
        (((hsh3*=3)%=P)+=R)%=P;
    }
    for(int j=y+pc-2;j>=y;j--){
        for(int i=x;i<x+pr-1;i++)
            ((hsh4<<=1)|=(a[i][j]=='.'))%=P;
        (((hsh4*=3)%=P)+=R)%=P;
    }
    //cout<<hsh1<<'!'<<hsh2<<'!'<<hsh3<<'!'<<hsh4<<'!'<<endl;
    auto hs={hsh1,hsh2,hsh3,hsh4};
    ull res=(min(hs)+max(hs))%P;
    us.insert(res);
}
int main(){
    cin>>r>>c,a.resize(r);
    for(auto&ax:a) cin>>ax;
    for(int i=1;i<r&&pr==0;i++)
        if(a[i][1]=='#') 
            pr=i;
    for(int i=1;i<c&&pc==0;i++)
        if(a[1][i]=='#')
            pc=i;
    //cout<<pr<<'?'<<pc<<endl;
    for(int i=1;i<r;i+=pr)
        for(int j=1;j<c;j+=pc)
            fun(i,j);
    cout<<us.size()<<endl;
}
```

---

## 作者：Provicy (赞：1)

[CF GYM 链接](https://codeforces.com/gym/101173)

$\text{Solution}$：

首先找到第二个全 ``#`` 行和第二个全 ``#`` 列，可以得到每个矩形的大小。

然后对于每个矩形，暴力 Hash + map 判断它是否在之前出现过。对于旋转的操作，可以先看旋转后矩形的每个位置在原矩形中是哪个位置。

个人建议无论什么情况下写双哈希，不过这里我偷懒了没写，毕竟矩阵数量比较少。

$\text{Code}$：

```cpp
#include <bits/stdc++.h>
#pragma GCC optimize(3)
#define int long long
#define ri register
#define mk make_pair
#define fi first
#define se second
#define pb push_back
#define eb emplace_back
#define is insert
#define es erase
using namespace std; const int N=233, B1=191, B2=137, Mod=998244353;
inline int read()
{
	int s=0, w=1; ri char ch=getchar();
	while(ch<'0'||ch>'9') { if(ch=='-') w=-1; ch=getchar(); }
	while(ch>='0'&&ch<='9') s=(s<<3)+(s<<1)+(ch^48), ch=getchar();
	return s*w;
}
int n,m,H,W,Ans,hsh[N][N];
char s[N][N];
map<int,int> Q;
signed main()
{
	n=read(), m=read();
	for(ri int i=1;i<=n;i++)
	{
		scanf("%s",s[i]+1);
		int flg=1;
		for(ri int j=1;j<=m;j++)
		{
			if(s[i][j]!='#')
			{
				flg=0;
				break;
			}
		}
		if(flg&&i>1&&H==0) H=i-1;
	}
	for(ri int i=1;i<=m;i++)
	{
		int flg=1;
		for(ri int j=1;j<=n;j++)
		{
			if(s[j][i]!='#')
			{
				flg=0;
				break;
			}
		}
		if(flg&&i>1&&W==0) W=i-1;
	}
	for(ri int i=2;i<=n;i+=H)
	for(ri int j=2;j<=m;j+=W)
	{
		for(ri int x=0;x<=H;x++) hsh[x][0]=0;
		for(ri int x=0;x<=W;x++) hsh[0][x]=0;
		for(ri int x=1;x<H;x++)
		for(ri int y=1;y<W;y++)
		hsh[x][y]=(hsh[x][y-1]*B1+s[i+x-1][j+y-1])%Mod;
		for(ri int x=1;x<H;x++)
		for(ri int y=1;y<W;y++)
		hsh[x][y]=(hsh[x][y]+hsh[x-1][y]*B2)%Mod;
		if(Q[hsh[H-1][W-1]]) continue;
		Q[hsh[H-1][W-1]]=1, Ans++;
        
		for(ri int x=0;x<=H;x++) hsh[x][0]=0;
		for(ri int x=0;x<=W;x++) hsh[0][x]=0;
		for(ri int x=1;x<H;x++)
		for(ri int y=1;y<W;y++)
		hsh[x][y]=(hsh[x][y-1]*B1+s[i+H-x-1][j+W-y-1])%Mod;
		for(ri int x=1;x<H;x++)
		for(ri int y=1;y<W;y++)
		hsh[x][y]=(hsh[x][y]+hsh[x-1][y]*B2)%Mod;
		Q[hsh[H-1][W-1]]=1;
        
		for(ri int x=0;x<=W;x++) hsh[x][0]=0;
		for(ri int x=0;x<=H;x++) hsh[0][x]=0;
		for(ri int x=1;x<W;x++)
		for(ri int y=1;y<H;y++)
		hsh[x][y]=(hsh[x][y-1]*B1+s[i+H-y-1][j+x-1])%Mod;
		for(ri int x=1;x<W;x++)
		for(ri int y=1;y<H;y++)
		hsh[x][y]=(hsh[x][y]+hsh[x-1][y]*B2)%Mod;
		Q[hsh[W-1][H-1]]=1;
        
		for(ri int x=0;x<=W;x++) hsh[x][0]=0;
		for(ri int x=0;x<=H;x++) hsh[0][x]=0;
		for(ri int x=1;x<W;x++)
		for(ri int y=1;y<H;y++)
		hsh[x][y]=(hsh[x][y-1]*B1+s[i+y-1][j+W-x-1])%Mod;
		for(ri int x=1;x<W;x++)
		for(ri int y=1;y<H;y++)
		hsh[x][y]=(hsh[x][y]+hsh[x-1][y]*B2)%Mod;
		Q[hsh[W-1][H-1]]=1;
	}
	printf("%lld\n",Ans);
	return 0;
}
```


---

## 作者：chenjianong (赞：0)

题意：$r$ 行 $c$ 列的矩阵里存在多个 $n$ 行 $m$ 列的子矩阵（$n$、$m$ 要自己计算出来），用 `#` 隔开。  
定义两个子矩阵同构，当且仅当其中一个旋转 $90$ 度、$180$ 度、$270$ 度、$360$ 度后两者完全相同。问一共有多少个不同的子矩阵（即同构的算一种）。

思路：
1. 对每个子矩阵的 $90$ 度、$180$ 度、$270$ 度、$360$度计算 $4$ 个 hash，只要有一个相同就判为同构。
2. 用 unordered_map 存储 hash，做为判断依据。

```cpp
#include<bits/stdc++.h>
#include<unordered_map>

using namespace std;
typedef unsigned long long ull;

const int N = 2005;
const int Base = 131;
char a[N][N];
int r, c, n, m, ans;

int findN()
{
  for(int i = 3; i <= r; i++)
    if(a[i][2] == '#')
      return i-2;
  return 0;
}

int findM()
{
  for(int i = 3; i <= c; i++)
    if(a[2][i] == '#')
      return i-2;
  return 0;
}

unordered_map<ull, bool> mp;
void solve(int y, int x)
{
  ull hs = 0;
  int Y = y+n-1, X = x+m-1;

  //  a[y][x]
  for(int i = y; i <= Y; i++)
    for(int j = x; j <= X; j++)
      hs = hs*Base + a[i][j];
  if(mp.count(hs)) return;
  ans++;
  mp[hs] = true;

  hs = 0;
  //  a[Y][x]
  for(int j = x; j <= X; j++)
    for(int i = Y; i >= y; i--)
      hs = hs*Base + a[i][j];
  mp[hs] = true;
  
  hs = 0;
  //  a[Y][X]
  for(int i = Y; i >= y; i--)
    for(int j = X; j >= x; j--)
      hs = hs*Base + a[i][j];
  mp[hs] = true;

  hs = 0;
  //  a[y][X]
  for(int j = X; j >= x; j--)
    for(int i = y; i <= Y; i++)
      hs = hs*Base + a[i][j];
  mp[hs] = true;
}

int main()
{
  cin >> r >> c;
  for(int i = 1; i <= r; i++)
    for(int j = 1; j <= c; j++)
      cin >> a[i][j];

  n = findN();
  m = findM();

  int y = 2, x = 2;
  while(y <= r){
    solve(y, x);
    if(x+m+1 <= c) x += m+1;
    else x = 2, y += n+1;
  }

  cout << ans << endl;

  return 0;
}
```



---

