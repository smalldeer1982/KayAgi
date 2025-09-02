# Binary String Reconstruction

## 题目描述

Consider the following process. You have a binary string (a string where each character is either 0 or 1) $ w $ of length $ n $ and an integer $ x $ . You build a new binary string $ s $ consisting of $ n $ characters. The $ i $ -th character of $ s $ is chosen as follows:

- if the character $ w_{i-x} $ exists and is equal to 1, then $ s_i $ is 1 (formally, if $ i         > x $ and $ w_{i-x} =  $ 1, then $ s_i =  $ 1);
- if the character $ w_{i+x} $ exists and is equal to 1, then $ s_i $ is 1 (formally, if $ i + x \le         n $ and $ w_{i+x} =  $ 1, then $ s_i =  $ 1);
- if both of the aforementioned conditions are false, then $ s_i $ is 0.

You are given the integer $ x $ and the resulting string $ s $ . Reconstruct the original string $ w $ .

## 样例 #1

### 输入

```
3
101110
2
01
1
110
1```

### 输出

```
111011
10
-1```

# 题解

## 作者：_•́へ•́╬_ (赞：5)

### 题意

如果你知道字符串 $w$ 和正整数 $x$，那么你珂以用一下方式构造字符串 $s$：

- 如果 $w_{i-x}\texttt{存在且}=1$ 或 $w_{i+x}\texttt{存在且}=1$，那么 $s_i=1$。
- 否则 $s_i=0$。

但是你知道 $x$ 和 $s$ ，试构造 $w$。

### 思路

如果 $s_i=0$，那么 $w_{i-x}$ 和 $w_{i+x}$ 都为 $0$。$w$ 中的其他位置都写 $1$，因为写 $0$ 不保证 $s$ 中的其他地方一定不会变成 $0$，而写 $1$ 珂以保证 $s$ 中的其他地方是 $1$，也一定不会影响到 $s$ 中为 $0$ 的位置。

然后如果发现某个 $s_i=1$，但是 $w_{i-x}=0$ 且 $w_{i+x}=0$，那么显然它与一些 $s_i=0$ 的要求冲突了，那么无解。

### $code$

```cpp
#include<stdio.h>
int t,n,x;char s[100001],w[100001];bool f;
main()
{
	for(scanf("%d",&t);t--;)
	{
		scanf("%s%d",s,&x);
		for(n=0;s[n];++n);//strlen
		for(register int i=0;i<n;++i)w[i]='1';/*初始化为1*/w[n]=0;f=0;
		for(register int i=0;i<n;++i)if(s[i]=='0')
		{
			if(i-x>=0)w[i-x]='0';//存在就是0
			if(i+x<n)w[i+x]='0';//存在就是0
		}
		for(register int i=0;i<n;++i)
			if(s[i]=='1'&&(i-x<0||w[i-x]=='0')&&(i+x>=n||w[i+x]=='0')){f=1;break;}//矛盾，无解
		if(f)puts("-1");
		else printf("%s\n",w);
	}
}
```



---

## 作者：邓布利多6 (赞：5)

题目描述：

考虑以下过程。 您有一个长度为 $n$ 的二进制字符串 $w$ (每个字符为 $0$ 或 $1$) 和一个整数 $x$。

新二进制字符串 $s$ 的第 $i$ 个字符按如下规则构造：

1. 如果字符 $w_ {i-x}$ 存在且等于 $1$，则 $s_i$ 为 $1$. 

2. 如果字符 $w_ {i+x}$ 存在且等于 $1$，则 $s_i$ 为 $1$.

3. 如果上述两个条件均为假，则 $s_i$ 是 $0$。

给您整数 $x$ 和结果字符串 $s$。 要求重建原始字符串 $w$。 

思路：

$s_i = 0$ 说明两边都是 $0$ , 那么我们先构造一个全是 $1$ 的字符串, 然后扫一遍 $s$，对于每一个 $s_i=0$ , 把 $w$ 的两边赋值为 $0$

注意 ： 前提是左右两边要都有，防止数组越界 RE。

再扫一遍 $s$，看看所有 $s_i=1$ 的位置两边有没有 $1$ 。

如果有任意一个位置上没有，答案为 $-1$ 。

否则输出字符串 $w$ .

#### Code

``` cpp
#include <iostream>
#include <string>
using namespace std;
int T, x, n;
string s, ans;
bool f1, f2, flag;
int main()
{
	cin >> T;
	while(T--)
	{
		cin >> s >> x;  
		n = s.length(); ans = ""; flag = false;
		for(int i = 0; i < n; i++) ans += '1';

		for(int i = 0; i < n; i++) if(s[i] == '0')
		{
			if(i - x >= 0) ans[i - x] = '0';
			if(i + x < n)  ans[i + x] = '0';
		}	
		for(int i = 0; i < n; i++) if(s[i] == '1')
		{
			f1 = f2 = 0;
			if(i - x >= 0) f1 = (ans[i - x] == '1');
			if(i + x < n)  f2 = (ans[i + x] == '1');
			if(!f1 && !f2) { cout << -1 << endl; flag = true; break; }
		}
		
		if(flag) continue;
		cout << ans << endl;
	}
	
	return 0;
}

```

---

## 作者：ZigZagKmp (赞：2)

本文同步发表于[我的cnblog](https://www.cnblogs.com/ZigZagKmp/p/13563143.html)

本场题解可见[此](https://www.luogu.com.cn/blog/ZigZagKmp/codeforces-1400-edu-94-solution)

## 题意简述
已知一个长度为$n$的01字符串$s$由长度为$n$的01字符串和一个正整数$x$生成。字符串下标从$1$开始。$s_i$生成规则如下：

- 如果$i>x$且$w_{i-x}=1$，则$s_i=1$；
- 如果$i+x\le n$且$w_{i+x}=1$，则$s_i=1$；
- 否则$s_i=0$。

输入$s$和$x$，输出一种可行的$w$，如果不存在这样的$w$，输出$-1$。

多测，$2\le |s|\le 10^5$，$1\le x\le |s|-1$，$\sum|s|\le 10^5$。
### 算法考察
模拟
## 算法分析
我们先改写一下条件：

- $s_i=1$，则$w_{i-x}=1(i>x)$或$w_{i+x}=1(i+x\le n)$；
- $s_i=0$，则$w_{i-x}=0(i>x)$且$w_{i+x}=0(i+x\le n)$；

我们发现$s_i=0$的限制条件比较确定，因此我们可以确定$w$的哪些位置一定是$0$。

此时如果要使第一个条件成立，我们只需要检验每一个$s_i=1$的位置，如果对应的$w$的位置都是确定的$0$，那一定无解，否则我们让剩余不确定的位置全部填$1$，可以证明这样的构造一定合法。
## 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
#define maxn 100005
#define maxm 200005
#define inf 0x3f3f3f3f
#define int long long
#define mod 1000000007
#define local
template <typename Tp> void read(Tp &x){
	int fh=1;char c=getchar();x=0;
	while(c>'9'||c<'0'){if(c=='-'){fh=-1;}c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c&15);c=getchar();}x*=fh;
}
int n,m;
int pos[maxn];
char s[maxn];
signed main(){
	int CasT;
	read(CasT);
	int X;
	while(CasT--){
		memset(pos,0,sizeof(pos));//此处实际可以更加精细处理，但本身已经能过
		scanf("%s",s+1);
		read(X);
		n=strlen(s+1);
		for(int i=1;i<=n;i++){//处理0
			if(s[i]=='0'){
				if(i-X>0)pos[i-X]=1;
				if(i+X<=n)pos[i+X]=1;
			}
		}
		int ffl=1;
		for(int i=1;i<=n;i++){
			if(s[i]=='1'){//处理1
				int fla=0,flb=0;
				if(i-X>0){
					if(pos[i-X]==1)fla=1;
				}
				else fla=1;
				if(i+X<=n){
					if(pos[i+X]==1)flb=1;
				}
				else flb=1;
				if(fla&&flb){//无法满足1，一定无解
					puts("-1");
					ffl=0;
					break;
				}
			}
		}
		if(ffl){
			for(int i=1;i<=n;i++){
				if(pos[i])putchar('0');
				else putchar('1');
			}
			puts("");
		}
	}
	return 0;
}
```

---

## 作者：STDquantum (赞：0)

观察变换方式，可以发现在 $s_i=\mathbf0$ 的情况下，对原串有 $w_{i+x}=w_{i-x}=\mathbf0$（若存在的话）。

所以可以先扫一遍 $s$，标记这些位置，再处理 $s_i=\mathbf1$ 的情况。

```cpp
for (int i = 1; i <= len; ++i) {
    if (ch[i] == '0') {
        if (i - x > 0) vis[i - x] = 1;
        if (i + x <= len) vis[i + x] = 1;
    }
}
```

对于 $s_i=\mathbf1$ 的情况，可能有 $w_{i-x}=\mathbf1$ 或 $w_{i+x}=\mathbf1$ 或两者都有。而只要有一个就足够了，所以若两边都被打上了标记，就直接判断无解。可以只标记左边的 $w_{i-x}=1$，若 $w_{i-x}$ 已经被打上了标记，那就标记右边的 $w_{i+x}=1$。

有些位置可能不会被以上的方法赋值，这些位置是什么都可以，赋为`'0'`在第一个步骤比较方便。

思路很简单但是`if`太多而且每行很短，所以为了观感将缩进改为两格。

代码中`ch`串是结果串，`s`串是原串。

代码中还采用了C++的一个小trick：`goto`。这可以代替打标记+`break`，在情况较复杂时使用很方便。简单来说它的用法，那就是`goto wherever;`，若程序执行到这一句就会跑到`wherever:`的后面。可以用来跳出多个循环直接输出无解（或者类似的操作）。

```cpp
#include <bits/stdc++.h>
using namespace std;

namespace STDquantum { // 防止命名冲突用的，main()就相当于主函数

const int N = 3e5 + 10;
int t, x, len;
char ch[N], s[N];
bool vis[N];
inline void main() {
  scanf("%d", &t);
  while (t--) {
    scanf("%s%d", ch + 1, &x);
    len = strlen(ch + 1);
    fill(vis + 1, vis + len + 1, 0); // 可以代替memset把[vis+1,vis+len+1)全清零
    fill(s + 1, s + len + 1, '0'); // 清空s串
    s[len + 1] = 0; // printf遇见s[i]=0就会停止，所以这句相当于一个终止符
    for (int i = 1; i <= len; ++i) {
      if (ch[i] == '0') { // 第一个步骤：标记已有信息
        if (i - x > 0) vis[i - x] = 1;
        if (i + x <= len) vis[i + x] = 1;
      }
    }
    for (int i = 1; i <= len; ++i) {
      if (ch[i] == '1') { // 第二个步骤：求出原串
        if (i - x > 0) { // 若左边位置合法
          if (vis[i - x]) { // 若左边位置被标记过
            if (i + x <= len) { // 若右边位置合法
              if (vis[i + x]) { // 若右边位置被标记过
                goto school; // 都被标记过则无解
              } else {
                s[i + x] = '1'; // 左边被标记过、右边合法，就把右边赋为'1'
              }
            } else { // 右边位置不合法
              goto school; // 左边位置合法但被标记过，右边位置不合法，无解
            }
          } else { // 左边合法且没有被标记过直接赋为'1'
            s[i - x] = '1';
          }
        } else if (i + x <= len) { // 左边位置不合法，右边位置合法
          if (vis[i + x]) { // 右边被标记过
            goto school; // 左边位置不合法，右边位置合法但被标记过，无解
          } else {
            s[i + x] = '1'; // 左边位置不合法，右边位置合法且未被标记过，直接赋为'1'
          }
        } else {
          goto school; // 左右位置都不合法，无解
        }
      }
    }
    printf("%s\n", s + 1); // 全都合法直接输出原串
    continue;
  school: // goto school跳到这里，输出-1后直接进行下一次循环
    puts("-1");
  }
}

}  // namespace STDquantum

int main() {
  STDquantum::main();
  return 0;
}
```





---

## 作者：引领天下 (赞：0)

分析一下如何倒推，发现需要分类讨论：

- 如果 $s_i$ 是 $0$，则必然满足 $i-x<1\text{ or } w_{i-x}=0$ 且 $i+x>n\text{ or }w_{i+x}=0$ 。
  
  根据此条件，我们可以将 $w_{i-x}$ 和 $x_{i+x}$ 均设置为 $0$（不越界）。
  
- 如果 $s_i$ 是 $1$，则必然满足 $i-x\ge 1\text{ and }w_{i-x}=1$ 或 $i+x\le n\text{ and }w_{i+n}=1$。

于是我们可以根据情况一将可能的 $w$ 构造出来，再根据情况二判断是否可行。

```cpp
#include <bits/stdc++.h>
#define min(x,y) ((y)^(((x)^(y))&(-((x)<(y)))))
#define max(x,y) ((x)^(((x)^(y))&(-((x)<(y)))))
using namespace std;
int main(){
    register int t;
    cin>>t;
    bool w[100005];
    string s,s1;
    while(t--){
        s=" ";
        bool ok=1;register int n,x;
        cin>>s1>>x;memset(w,1,sizeof(w));s+=s1;//w初始全为1，是一种贪心的思想：尽可能满足1的需求
        n=s1.size();
        for(int i=1;i<=n&&ok;i++)if(s[i]=='0'){
            if(i-x)w[i-x]=0;//情况一，对w处理
            if(i+x<=n)w[i+x]=0;
        }
        for(int i=1;i<=n&&ok;i++)if(s[i]=='1'){
            bool z=0;
            if(i-x)z|=w[i-x];//情况二，对w判断
            if(i+x<=n)z|=w[i+x];
            ok&=z;
        }
        if(!ok)cout<<"-1";
        else for(int i=1;i<=n;i++)cout<<w[i];
        cout<<endl;
    }
    return 0;
}
```

---

## 作者：fsy_juruo (赞：0)

C 题 比 B 题 简 单.jpg

首先，我们可以确定原字符串中 ``0`` 的位置：将给定字符串扫一遍，遇到第 $i$ 位为 ``0`` 就将原字符串中 $i-x$，$i+x$ 位更新为 ``0``。

然后检查 ``1``，如果有一个 ``1`` 位置两边都已经赋值成了 ``0``，那么无解。

如果有解就把剩下空的位置赋值成 ``1`` 即可，正确性显然。

时间复杂度 $\mathcal{O}(\sum |s|)$。

**代码：**

代码写的烦了一点....

```cpp
#include <bits/stdc++.h>
#define LL long long
#define ULL unsigned long long
#define LD long double
#define reg register
#define _rep(i, x, y) for(int i = x; i <= y; i++)
#define _per(i, x, y) for(int i = x; i >= y; i--)
template <typename T>
inline void read(T &x) {
	x = 0; T f = (T) 1;
	char c = getchar();
	for(; !isdigit(c); c = getchar()) {if(c == '-') f = -f;}
	for(; isdigit(c); c = getchar()) x = x * 10 + c - 48;
	x *= f;
}
template <typename T, typename... Args>
inline void read(T& x, Args&... args) {
    read(x); read(args...);
}
template <typename T>
inline void write(T x) {
	if(x < 0) {x = -x; putchar('-');}
	if(x > 9) write(x / 10);
	putchar(x % 10 + '0');
}
template <typename T>
inline void writesp(T x, char sp = ' ') {write(x); putchar(sp);}
const int maxN = 1e5 + 10;
int t, n;
char str[maxN], c[maxN];
int x;
int main() {
	read(t);
	while(t--) {
		scanf("%s", str + 1); read(x);
		n = strlen(str + 1);
		_rep(i, 1, n) c[i] = 'Z';
		_rep(i, 1, n) {
			if(str[i] == '0') {
				if(i - x >= 1) c[i - x] = '-';
				if(i + x <= n) c[i + x] = '-';
			}
		}
		int flg = 1;
		_rep(i, 1, n) {
			if(str[i] == '1') {
				if(i - x >= 1 && c[i - x] != '-') {
					c[i - x] = '+';
				} else if(i + x <= n && c[i + x] != '-') {
					c[i + x] = '+';
				} else {
					flg = 0; break;
				}
			}
		}
		if(flg == 0) puts("-1");
		else {
			_rep(i, 1, n) {
				putchar(c[i] == '-' ? '0' : '1');
			}
			putchar('\n');
		}
	}
	return 0;
}

```

---

