# 「Cfz Round 9」Lone

## 题目背景

[Click here (or at the bottom of this page) to download the English version of statements for this contest (PDF).](https://www.luogu.com.cn/fe/api/problem/downloadAttachment/of2k8jng?contestId=205839)

## 题目描述

她有一根长度为 $m$ 的木棍。

她希望你把这根木棍分成 $n$ 根小木棍，使得每一根小木棍的长度均为**正整数**，且从中任选 $3$ 根小木棍都可以通过首尾相连的方式组成一个三角形。

你想求出，你能否满足她的愿望。

## 说明/提示

#### 「样例解释 #1」

对于第 $1$ 组测试数据，可以把木棍分成长度分别为 $1,2,2,2$ 的小木棍。

对于第 $2$ 组测试数据，可以证明不存在满足要求的方案。

对于第 $3$ 组测试数据，其中一种满足要求的方案为把木棍分成长度分别为 $3,4,4,5,5$ 的小木棍。

#### 「数据范围」

对于所有测试数据，保证：

- $1 \le T \le 100$；
- $3 \le n \le m \le 10^9$。

**本题采用捆绑测试。**

- Subtask 0（18 points）：$m \le 500$，$n=3$。
- Subtask 1（15 points）：$n=3$。  
- Subtask 2（32 points）：$n\times 2 \ge m$。  
- Subtask 3（35 points）：无特殊限制。

## 样例 #1

### 输入

```
3
4 7
3 4
5 21```

### 输出

```
Yes
No
Yes```

# 题解

## 作者：Vct14 (赞：12)

方法好像比 std 简单。

显然 $m=n$ 时是可以的。下面考虑 $m>n$ 的情况。

我们让所有每一根小木棍的长度尽量平均，那么两根小木棍长度之差最大为 $1$。则除非有至少两根长度为 $1$ 的小木棍（此时一定可以选出三根长度分别为 $1,1,2$ 的小木棍），其他情况一定可以满足要求。

我们考虑什么时候不会存在至少两根长度为 $1$ 的小木棍。因为如果存在，最短的小木棍长度为 $\left\lfloor\dfrac{m}{n}\right\rfloor$ 应该为 $1$，所以 $m\geqslant 2n$ 时不会存在；并且因为至少要有两根，所以 $m\ne 2n-1$ 时也不会存在。因此 $m\geqslant 2n-1$ 时不会存在多于一根长度为 $1$ 的小木棍，一定可以满足要求，直接判断即可。

```cpp
#include<bits/stdc++.h>
using namespace std;

int main(){
	int t;cin>>t;
	while(t--){
		int n,m;cin>>n>>m;
		if(m==n || m>=n*2-1) puts("Yes");
		else puts("No");
	}
	return 0;
}
```

---

## 作者：lby_commandBlock (赞：10)

## 思路

考虑数学归纳法。下方 $m,n$ 为题目描述中的 $m,n$。

根据三角形边定理，得知选出来线段的最短两条边相加的长度要大于第三条边。

1. 首先特判，由每一根小木棍的长度均为**正整数**，若 $m<n$，则无法凑成正整数，必为小数，输出 `No`。
2. 若 $m \bmod n = 0$，则必可以构成等边三角形，输出 `Yes`。

考虑 `No`。若有 `No`，则肯定是因为最短两条边相加的长度小于等于最长的那条边，所以平均分为最优方案。若平均分，则只有分出大于等于两个数量的 $1$ 和至少一个 $2$ 才能凑成一个 $1+1=2$，最短两边长度相加 $\le 2$。

所以，判断 $\lfloor \dfrac m n \rfloor$ 要等于 $1$，这样才能保证有至少一个 $1$；其次，判断 $(m \bmod n) < (n - 1)$，这样就保证至少有 $1$ 个 $2$ 且保证了至少有 $2$ 个 $1$。

剩下的情况则是 `Yes`。

## 赛时满分代码

```cpp
#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

int T, n, m;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	for (cin >> T; T; T--) {
		cin >> n >> m;
		if (m < n) {
			cout << "No" << endl;
			continue;
		}
		if (m % n == 0) {
			cout << "Yes" << endl;
			continue;
		}
		if (m / n == 1 && m % n < n - 1)
			cout << "No" << endl;
		else
			cout << "Yes" << endl;
	}
	return 0;
}
```

---

## 作者：NTT__int128 (赞：3)

# P11204 「Cfz Round 9」Lone题解
我们为了让分成的木棍能组成三角形，肯定会贪心地是没两根木棍的长度之差最小。我们发现，两根木棍的长度差最大可以被缩小到 $1$。

然后，我们发现，如果没跟木棍的长度均大于 $1$，则一定成立。只考虑有长度为 $1$ 的木棍的情况。

若此时全部为长度为 $1$ 的木棍，则成立。如果只有一根长度为 $1$ 的木棍，其余全为长度为 $2$ 的木棍，则成立。其余情况，会有 $1+1=2$ 成立，无法构成三角形。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m;
int main(){
	cin>>t;
	while(t--){
		cin>>n>>m;
		int g=m/n,k=m%n;
		if(g==1&&k&&k<n-1)cout<<"No\n";
		else cout<<"Yes\n";
	}
	return 0;
}
```

---

## 作者：CJZJC (赞：2)

首先可以观察出把木棍平均分是最优的。

然后平均分后最多只有两种长度的木棒，长度分别为 $\lfloor \frac{m}{n} \rfloor$ 和 $\lfloor \frac{m}{n} \rfloor + 1$。

最后 check 一下就行了。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define flush() fwrite(obuf,1,O-obuf,stdout)
#define putchar(x) ((O==obuf+(1<<21))&&(flush(),O=obuf)),*O++=x
char buf[1<<23],*p1=buf,*p2=buf,obuf[1<<23],*O=obuf;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
inline int read() {
    register int x=0,f=1;register char ch=getchar();
    while(!isdigit(ch)){if(ch=='-') f=-1;ch=getchar();}
    while(isdigit(ch)) x=x*10+(ch^48),ch=getchar();
    return x*f;
}
inline void write(register int x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar((x%10)^48);
}
struct Flush{
    ~Flush(){flush();}
}_;
signed main(){
    int t,n,m;
    cin>>t;
    while(t--){
        cin>>n>>m;
        bool f=1;
        int s1=m%n,s2=n-m%n;
        int len1=m/n+1,len2=m/n;
        if(s1==0){
            cout<<"Yes\n";
        }
        else{
            if(s1>1){
                if(len2+len1<=len1){
                    f=0;
                }
            }
            if(s2>1){
                if(len2+len2<=len1){
                    f=0;
                }
            }
            if(!f){
                cout<<"No\n";
            }
            else{
                cout<<"Yes\n";
            }
        }
    }
    return 0;
}
```

---

## 作者：Zskioaert1106 (赞：2)

题目传送门：[P11204 「Cfz Round 9」Lone](https://www.luogu.com.cn/problem/P11204)

简单题。

不难注意到当 $\lceil \dfrac{m}{2} \rceil$ 比 $n$ 小时，必定会有大于 $1$ 个的长度为 $1$ 的边。

只要不是所有边都为 $1$，那么就会存在三条边 $1,1,k$ （其中 $k>1$）使得无法组成三角形。否则我们可以将 $m$ 尽量平分成 $n$ 条，即任意两条边的长度不会相差超过 $1$（参见 [P3235 江南乐](https://www.luogu.com.cn/problem/P3235)）。那么两边之和一定会大于第三边。（当 $k>1$ 时，$2k>k+1$ 总成立）

不难编写出代码。

```cpp
#include<iostream>
using namespace std;
int main(){
    int t;
    cin>>t;
    while(t--){
        int m,n;
        cin>>n>>m;
        if(n==m||(m+1)/2>=n)cout<<"Yes";
        else cout<<"No";
        cout<<"\n";
    }
    return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/183293849)。

---

## 作者：jiangyunuo (赞：2)

### 意思：

有一根长为 $m$ 的木棍，要把这根木棍分成 $n$ 份，求有没有一种分法可以在分完后的 $n$ 份中任选 $3$ 根小木棍都可以通过首尾相连的方式组成一个三角形。

### 思路：

显然判断一个三角形的方法就是任意两条边长度的和都大于第三边。

那么这样我们可以这样想：我们可以让每个小木棍的长度差最小，这时我们就是将木棍的长度尽量平均分，如：$m=3,n=3$ 那么可以分成 $1,1,1$；$m=4,n=3$ 那么可以分成 $1,1,2$。

当我们这样分时可以发现当小木棍中有多个长度（至少有一个小木棍长度不为 $1$）为 $1$ 的时，那么就不可能实现，因为 $1,1,2$ 不可能实现；当 $1$ 只有一个或没有时就可以实现，因为 $1,2,2$ 可以实现，而没有 $1$ 的时候由于最长的小木棍与最短的相差 $1$ 或 $0$ 那么当最短的不为 $1$ 时，另外一根小木棍长度也大于 $1$，肯定可以实现；当所有小木棍长度都为 $1$ 时，任取 $3$ 个都可以组成一个等边三角形。

如此我们可以推出当 `(m+1)/2>=n` 或 `m=n` 时，就可以实现任选 $3$ 根小木棍都可以通过首尾相连的方式组成一个三角形。

### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int t;
    cin>>t;
    int n,m;
    for(int i=1;i<=t;i++){
        cin>>n>>m;
        if((m+1)/2>=n||m==n)cout<<"Yes"<<endl;
        else cout<<"No"<<endl;
    }
	return 0;
}
```

---

## 作者：汤圆0512 (赞：1)

[P11204 「Cfz Round 9」Lone - 题目链接](https://www.luogu.com.cn/problem/P11204)

### 基本知识

三角形的三边关系：任意两边之和大于第三边，任意两边之差小于第三边。（以上两句等价）

### 实现方法

小学里学过带余除法，由此可以知道，我们可以使得分成的小木棍有且仅有两种长度： $\lfloor \frac{m}{n} \rfloor$ 和 $\lfloor \frac{m}{n} \rfloor +1$ ，此时任意两边之差为 $1$ （若 $n \vert m$ 则差为 $0$ ），取到最小差。由三角形三边关系可知，差最小时就是最优情况。若 $\lfloor \frac{m}{n} \rfloor \geq 2$ ，即满足题意。

如果 $\lfloor \frac{m}{n} \rfloor =1$ ，则需要特判，当且仅当 $n \vert m$ 或 $n \vert m+1$ 时符合题意（即全是 $1$ ，或仅有一个 $1$ ，其余长度均为 $2$ ），否则不符合题意。 

### AC Code


```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int n,m;
		cin>>n>>m;
		int p=m/n,q=m%n;
		if(p==1&&q!=0&&q!=n-1) cout<<"No"<<endl;
		else cout<<"Yes"<<endl;
	}
	return 0;
}
```

  2024.10.19（这是本人的第一篇题解）

---

## 作者：K_J_M (赞：1)

## 题目描述
她有一根长度为 $m$ 的木棍。

她希望你把这根木棍分成 $n$ 根小木棍，使得每一根小木棍的长度均为**正整数**，且从中任选 $3$ 根小木棍都可以通过首尾相连的方式组成一个三角形。

你想求出，你能否满足她的愿望。
## Solution
首先，如果我们将长度为 $m$ 的木棍拆分成很多长度不同的木棍，会非常的麻烦，所以我们不妨考虑特殊一点，将长度 $m$ 的木棍拆分成长度一样的一些木棍。例如将长度为 $11$ 的木棍分成 $5$ 个木棍，我们可以分为 $2,2,2,2,3$。更一般的，我们可以将长度为 $m$ 的木棍划分为 
$$\begin{cases}\
\{\lfloor \frac{m}{n} \rfloor,\lfloor \frac{m}{n} \rfloor\dots \lfloor \frac{m}{n} \rfloor,m-\lfloor \frac{m}{n} \rfloor \times(n-1)\} &m-\lfloor \frac{m}{n} \rfloor \times(n-1)>0并且2\times \lfloor \frac{m}{n} \rfloor>m-\lfloor \frac{m}{n} \rfloor \times(n-1)\\
\{\lfloor \frac{m}{n} \rfloor+1,\lfloor \frac{m}{n} \rfloor+1\dots \lfloor \frac{m}{n} \rfloor+1,m-(\lfloor \frac{m}{n} \rfloor+1) \times(n-1)\} &m-(\lfloor \frac{m}{n} \rfloor+1) \times(n-1)>0并且2\times (\lfloor \frac{m}{n} \rfloor+1)>m-(\lfloor \frac{m}{n} \rfloor+1) \times(n-1)
\end{cases}$$
然而这样有些复杂（~~对于一道红题来说~~），所以我们尽可能只考虑不合法的情况。当上述序列只能被写成 $1,1\dots 1,2$ 时，也就是 $n+1=m$ 时，肯定不行，也就是 $1,1\dots 1,2,2\dots 2$ 的时候，此时满足 $n\times 2-1>m$ 的时候，请读者自行思考为什么要减 $1$。其余情况就都合法了。\
[Ac Code](https://www.luogu.com.cn/paste/dhabfivn)

---

## 作者：zyc230721hzx (赞：1)

蒟蒻的第五篇题解。

[题目传送门](https://www.luogu.com.cn/problem/P11204)。
### 前置知识：

判断三条线段是否能够成三角形：

设这三条线段分别为 $a,b,c$ 且满足 $a \le b \le c$，当且仅当 $a+b > c$ 时，这三条线段可以构成三角形。


### 题意：
将一个正整数 $m$ 拆分成 $n$ 个正整数之和，使得这 $n$ 个正整数之中任意两个数之和都不大于另一个数。

### 考点：

贪心。



### 思路：

使拆分出来的 $n$ 个正整数大小最接近，即先将这 $n$ 个数赋值为 $\lfloor \frac{m}{n}\rfloor$，然后把其中 $m \bmod n$ 个数加上 $1$，这时 $n$ 个正整数中最小值为 $\lfloor \frac{m}{n}\rfloor$，最大值为 $\lfloor \frac{m}{n}\rfloor+1$，最后判断极端情况是否可以组成三角形。

注意：当 $m \bmod n=n-1$ 时，中间值为 $\lfloor \frac{m}{n}\rfloor+1$，因为 $\lfloor \frac{m}{n}\rfloor$ 为正整数，所以 $\lfloor \frac{m}{n}\rfloor+1+\lfloor \frac{m}{n}\rfloor>\lfloor \frac{m}{n}\rfloor+1$，一定可以构成三角形；

### 完整 AC 代码（C++ 版）：
```cpp
#include <bits/stdc++.h>
using namespace std;
int T,n,m;
int main()
{
	cin>>T;
	while(T--){
		cin>>n>>m;
		if(m%n==n-1){
			cout<<"Yes\n";
			continue;
		}
		int ans=m/n;
		int yu=m/n+(m%n!=0);
		if(ans*2>yu){
			cout<<"Yes\n";
		}else{
			cout<<"No\n";
		}
	}
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/183310956)。

**预祝 AC！**

---

## 作者：chzhh_111 (赞：1)

首先把这个木条的长度平均分成的 $n$ 份肯定是最优的，那么这样肯定还会剩下一些长度，或者不剩下一些长度就是整除的情况，那这个时候肯定就是可以的。而剩下的长度一定是小于 $n$ 的，所以这个木条就可以分成较长的和较短的两个部分。

看你怎么接下来我们去讨论一下就会发现如果较短的那部分为 `1`，较长的那部分为 `2`，那么若出现有两条为 `1`，一条为 `2` 的情况这就不可以，因为 `1+1=2`。则我们在判断 `m/n=1` 的情况，使在判断 `1` 的个数是否大于等于两条就可以了。

代码实现：
```cpp
#include<bits/stdc++.h> 
using namespace std;
#define int long long
int T,n,m;
signed main()
{
	cin>>T;
	while(T--)
	{
		cin>>n>>m;
		if(m%n==0) printf("Yes\n");
		else if((m/n==1&&m%n<=n-2)) printf("No\n");
		else printf("Yes\n");
	}
}
```

---

## 作者：_H17_ (赞：0)

## 题目分析

考虑尽量平均长度，每一根长 $\lfloor m\div n\rfloor$，为了方便后面表示为 $a$。

同时我们记剩余部分 $b=m\bmod n$。

显然 $a>1$ 时，满足 $a+1<(a+1)+a,a+1<a+a$。（将余数均摊）

在 $a=1$ 时，不能出现 $1,1,2$，所以最多 $1$ 个 $1$。$b=0,b=n-1$ 满足。

## 代码实现

```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
int T,n,m;
signed main(){
    for(cin>>T;T;--T){
        cin>>n>>m;
        int k=m/n,t=m%n;
        if(k>1)
            cout<<"Yes\n";
        else{
            if(t>=n-1||!t)
                cout<<"Yes\n";
            else
                cout<<"No\n";
        }
    }
    return 0;
}
```

---

## 作者：gavinliu266 (赞：0)

# 思路
考虑让分完后的每一段长度尽可能平均。

容易发现这样最长边与最短边长度差距之多为 $1$。

记最短边长度为 $a$。

然后分类讨论。

- 最短边长度大于 $2$，此时 $2a>a+1$，满足题目条件。
- 最短边长度等于 $1$，但是只有一条，此时，$a+(a+1)>a+1$，满足题目条件。
- 所有边长度均为 $1$，此时 $1+1>1$，满足题目条件。
- 否则不可以构造成功。

然后完了。

时间复杂度：$\Theta(T)$。

# 代码实现
```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int t, n, m;
int main() {
    scanf("%d", &t);
    while(t--) {
        scanf("%d%d", &n, &m);
        if(m % n == 0 || (m + 1) / n >= 2) printf("Yes\n");
        else printf("No\n");
    }
}
```

---

## 作者：Ayanami_404 (赞：0)

在鄙人洛谷专栏食用更佳。[戳我戳我](https://www.luogu.com.cn/article/8d5hbqve "你不会真的想要戳罢（恼")  
### 一些其他话
蒟蒻的第一篇题解居然是给这种入门题的（悲
### 总体评价
一道~~焯水~~超水の红色签到数学题。
### 题目分析
最好的分割方法（即让分出的木棍尽量长度差最少）可以分成以下几种情况来分类讨论:
1. 可以分成等长的 $ n $ 根
2. 可以分成长度为 $ \lceil \frac{m}{n} \rceil $ 的 $ \gt 1 $ 根与 $ \lfloor \frac{m}{n} \rfloor $ 的 若干根
3. 可以分成长度为 $ \lceil \frac{m}{n} \rceil $ 的 $ 1 $ 根与 $ \lfloor \frac{m}{n} \rfloor $ 的  $ n-1 $ 根

第一种情况下显然可行（等边三角形，显然 $ \frac{m}{n} \times 2 \gt \frac{m}{n} $ ）。  
第二种情况下为了考虑最好分割方法下最坏情况拿出其中长度为 $ \lceil \frac{m}{n} \rceil $ 的 $ 1 $ 根与长度为 $ \lfloor \frac{m}{n} \rfloor $ 的  $ 2 $ 根，此时若 $ \lfloor \frac{m}{n} \rfloor \times 2 \gt \lceil \frac{m}{n} \rceil $ 则可以形成三角形，否则无法形成。  
第三种情况下的最坏情况中取 $ \lceil \frac{m}{n} \rceil $ 的 $ 1 $ 根与 $ \lfloor \frac{m}{n} \rfloor $ 的  $ 2 $ 根，也显然可行（显然 $ \lceil \frac{m}{n} \rceil + \lfloor \frac{m}{n} \rfloor \gt \lfloor \frac{m}{n} \rfloor $ ）。
### AC代码
按照三种情况分类码代码即可：  
~~Talking is cheap, show me your code.~~
```cpp
// 瘟刑啸啼逝: 有朋Ctrl-C+Ctrl-V代码去，虽远必棕
// Author: @jiyizhuo2011
#include <cstdio>
using namespace std;

long long read() { // 快读(虽然我也不知道这道题需不需要)
	char c;
	long long r=0, f=1;
	while(!((c=getchar())>='0' && c <= '9')) {
		if(c=='-')f=-f;
	}
	while(c >= '0' && c <= '9') {
		r=r*10+c-'0';
		c=getchar();
	}
	return r*f;
}

long long T, m, n;
int main() {
	T=read();
	for(;T;T--) {
		n=read();m=read();
		if((m/n)*n==m) { // 第一种情况
			printf("Yes\n");
		}
		else if(m%n==n-1) { // 第三种情况
			printf("Yes\n");
		}
		else { // 第二种情况
			if(m/n*2>m/n+1)printf("Yes\n");
			else           printf("No\n");
		}
	}
	return 0;
}
```
### 实际结果
~~实际上是为了证明我童叟无欺~~
![不骗你的罢（喜](https://cdn.luogu.com.cn/upload/image_hosting/hzgl152s.png "你不会不信罢")

---

## 作者：xuduang (赞：0)

### 分析

注意到，如果可以组成一组长度和小于 $m$ 的合法方案，那 $m$ 就是合法的了。

那自然的就能想到，我们找出一组总长最小的合法方案，看是否大于 $m$ 即可。我们考虑只使用长度最短的 $1$ 和 $2$ 来构造。

运用到初一的三角形知识，我们可以知道，两边之和大于第三边，两边之差小于第三边。所以我们构造出的序列中只能含有一个 $1$，因为 $1+1=2$ 了，构造不出三角形。那自然剩下的全是 $2$ 了。易得最小总长度为 $n \times 2 - 1$。

注意可能出现 $n=m$，此时可以构造出全为 $1$ 的序列。

### 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n, m;
void solve()
{
    cin >> n >> m;
    cout << ((2 * (n - 1) + 1 <= m) || (n == m) ? "Yes\n" : "No\n");
}
signed main()
{
    int T;
    cin >> T;
    while(T--) solve();
    return 0;
} 
```

---

## 作者：ZYXzyx1006 (赞：0)

## 题意简述与思路分析
题目要求使任意三段都满足三边关系，可组成三角形，容易想到将长度平均分配。那么所有边中，最长边与最短边之间的差最大为 $1$，故只需在较短边有两条或以上时判断较短边是否为 $1$ 即可。 

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n,m;
	int t;
	cin>>t;
	while(t--)
	{
	cin>>m>>n;
	int k=n/m;//长度 
	int kk=n%m;//余数 
	if(kk!=0&&k==1&&kk<m-1)//例子：1+1=2 不可组成三角形 
	cout<<"No"<<endl;
	else
	cout<<"Yes"<<endl;//可平均分配 
	}
 } 
```

---

## 作者：llamn (赞：0)

只需要考虑四种情况：

1. $n > m$。 此时木棍长度不足以让 $n$ 个小木棍长度都为正整数。   
2. $n = m$。 此时将木棍分成 $m$ 份恰好满足所有小木棍长度都是 $1$，一定能满足要求。  
3. $n < m < 2 \times n$。     
此时当 $m = 2 \times n - 1$ 时，将木棍分成 $1$ 个长度为 $1$ 的小木棍和 $n-1$ 个长度为 $2$ 的小木棍时满足要求。   
否则（即 $n < m < 2 \times n - 1$）时，一定不满足要求。原因是最少有 $2$ 个小木棍长度为 $1$ 且有其它小木棍长度不为 $1$。这时取这两个长度为 $1$ 的小木棍和另一个长度不为 $1$ 的小木棍就不能构成三角形。     
4. $2 \times n \le m$。 此时，令 $m \bmod n$ 个小木棍长度为 $\lfloor \frac{m}{n} \rfloor + 1$，其余小木棍长度为 $\lfloor \frac{m}{n} \rfloor$，可以满足要求。

代码：   
```cpp
#include <bits/stdc++.h> 
#define _eggy_ using 
#define _party_ namespace
_eggy_ _party_ std; 
int n,m,T;
int main()
{
	scanf("%d",&T);
    while(T--)
    {
    	scanf("%d%d",&n,&m);
    	if (n > m) puts("No");
		else if (n == m || (2 * n <= m)) puts("Yes");
		else if (2 * n - 1 != m) puts("No");
		else puts("Yes");
	}    
    return 0;
}
```

---

## 作者：signed_long_long (赞：0)

# 题目解法
尽量平均分，如果 $m$ 对 $n$ 取余的结果为 $0$，就说明可以平均分，可以达成目标。如果结果为 $n-1$，也可以。对于其它的，如果 $\lfloor m\div n\rfloor\times 2\le\lfloor m\div n\rfloor+1$，就说明两个 $\lfloor m\div n\rfloor$ 和一个 $\lfloor m\div n\rfloor+1$ 不符合三角形的条件（任意两边之和大于第三遍），无法满足条件。否则，可以满足条件。

代码：
```cpp
#include<iostream>
#include<algorithm>
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T;
void work(){
	int n,m;
	scanf("%lld%lld",&n,&m);
	int x=m/n,y=m%n;
	if(y!=0 and y!=n-1){
		if(2*x<=x+1) {printf("No\n");return;}
	}
	printf("Yes\n");
}
signed main() {
	scanf("%lld",&T);
	while(T--) work();
    return 0;
}
```

---

## 作者：liyunhe (赞：0)

### 分析
分两种情况，首先将 $m$ 分成 $n$ 份，显然，再将剩下的进行一定的均分后，三角形的任意两边差最多为 $1$，所以只有当两边和大于其中一遍加 $1$ 时，即 $2\times n\le m$ 时，但是当 $m=2\times n-1$ 时只有一段边为一，所以也成立。综上为 $2\times n-1\le m$ 时成立。另一种情况是 $m=n$ 两个相等明显成立。
### 代码
```cpp
#include<iostream>
using namespace std;
void solve(){
	int n,m;
	cin>>n>>m;
	if(m>=2*n-1||n==m)cout<<"Yes";
	else cout<<"No";
	cout<<endl;
}
signed main(){
	int T;cin>>T;
	while(T--)solve();
}
```

---

## 作者：wbqhasvcf (赞：0)

要想尽可能保证任选三根木棍都可以拼成三角形，就得使这 $n$ 根木棍之间的差尽可能地小，也就是尽量令 $n$ 个木棍相等。

这很简单，先令每根木棍等于 $m$ 整除 $n$ ，再将多余的部分（$m$ 取余 $n$）匀给 $n$ 根木棒。按这种方法分配，很明显只要 $\lfloor \frac{a}{b} \rfloor>1$ 就是成立的。接下来需要另讨论 $\lfloor\frac{a}{b}\rfloor=1$ 的情况：如果 $m$ 刚好能被 $n$ 整除，即 $m=n$，那么只能将其分成 $n$ 个 $1$，任选三个木棍拼成的都是等边三角形，成立；如果 $m=2n-1$，即 $m\bmod n=n-1$，长度为 $1$ 的木棍便只有一个，剩下的只能抽出两根长度为 $2$ 的木棍，可以拼成三角形，也成立；除此之外剩下的情况总会出现 $1,1,2$ 的组合，这是拼不成三角形的，所以剩下的情况全部不成立。

因此循迹着这个贪心的思路我们的代码就敲好了：
```cpp
#include<iostream>
using namespace std;

int t,n,m;
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>n>>m;
		if(m/n==1&&m%n<n-1&&m%n>0) cout<<"No"<<endl;//仅需要一个双分支就搞定，非常非常地简单
		else cout<<"Yes"<<endl; 
	}
	return 0;
}
```

---

