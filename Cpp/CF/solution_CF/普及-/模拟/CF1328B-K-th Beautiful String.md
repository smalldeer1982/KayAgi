# K-th Beautiful String

## 题目描述

For the given integer $ n $ ( $ n > 2 $ ) let's write down all the strings of length $ n $ which contain $ n-2 $ letters 'a' and two letters 'b' in lexicographical (alphabetical) order.

Recall that the string $ s $ of length $ n $ is lexicographically less than string $ t $ of length $ n $ , if there exists such $ i $ ( $ 1 \le i \le n $ ), that $ s_i < t_i $ , and for any $ j $ ( $ 1 \le j < i $ ) $ s_j = t_j $ . The lexicographic comparison of strings is implemented by the operator &lt; in modern programming languages.

For example, if $ n=5 $ the strings are (the order does matter):

1. aaabb
2. aabab
3. aabba
4. abaab
5. ababa
6. abbaa
7. baaab
8. baaba
9. babaa
10. bbaaa

It is easy to show that such a list of strings will contain exactly $ \frac{n \cdot (n-1)}{2} $ strings.

You are given $ n $ ( $ n > 2 $ ) and $ k $ ( $ 1 \le k \le \frac{n \cdot (n-1)}{2} $ ). Print the $ k $ -th string from the list.

## 样例 #1

### 输入

```
7
5 1
5 2
5 8
5 10
3 1
3 2
20 100```

### 输出

```
aaabb
aabab
baaba
bbaaa
abb
bab
aaaaabaaaaabaaaaaaaa```

# 题解

## 作者：suxxsfe (赞：5)

[CF1328B K-th Beautiful String](https://www.luogu.com.cn/problem/CF1328B)，然而CF今天却上不去了，这是洛谷的链接  

## 题意  

一个长度为$n$的字符串，有2个$\texttt{b}$和$n-2$个$\texttt{a}$  
按字典序排序后，问你第$k$个是啥  
$n\leq 10^5$  

----------  

由于我们相信CF从来不卡常，所以这实际是个$O(n)$找规律  
看题目里的例子：  
```plain  
aaabb
aabab
aabba
abaab
ababa
abbaa
baaab
baaba
babaa
bbaaa
```  

可以发现，如果只看前面一个$\texttt{b}$的运动轨迹，是从后向前以为一位移动的  
而对于靠后的一个$\texttt{b}$，当前面那个$\texttt{b}$确定后，它也是从最后一位向前移动，直到移动到前面那个$\texttt{b}$的后一位  
然后，它又回到最后，前面那个$\texttt{b}$再往前走一位  

所以我们可以从后到前枚举第一个$\texttt{b}$的位置，假设当前位置是$i$，那么这一种情况就有$n-i$个字符串  
讨论如下：  

- $k>n-i$，那么，$k\rightarrow k-(n-i)$，就是说这$n-i$个字符串里面没有要找的，再向前考虑  
- 其余情况，也就是我们要找的第$k$个字符串就在这$n-i$个，那么第二个$\texttt{b}$就是在第$n-k+1$为，输出就行  

可以结合上面的例子理解  
放上代码  

```cpp  
#include<cstdio>
#include<algorithm>
#include<iostream>
#include<cmath>
#include<iomanip>
#include<cstring>
#define reg register
#define EN std::puts("")
#define LL long long
inline LL read(){
	LL x=0,y=1;
	char c=std::getchar();
	while(c<'0'||c>'9'){if(c=='-') y=0;c=std::getchar();}
	while(c>='0'&&c<='9'){x=x*10+(c^48);c=std::getchar();}
	return y?x:-x;
}
LL n,k;
int main(){int T=read();while(T--){
	n=read();k=read();
	for(reg int i=n-1;i;i--){
		if(k>n-i) k-=n-i;
		else{
			for(reg int j=1;j<i;j++) std::putchar('a');
			std::putchar('b');
			for(reg int j=i+1;j<n-k+1;j++) std::putchar('a');
			std::putchar('b');
			for(reg int j=n-k+2;j<=n;j++) std::putchar('a');
			break;
		}
	}
	EN;
}
	return 0;
}
```

---

## 作者：registerGen (赞：3)

神仙 div3...

可以看出，只需求出两个 $\texttt{b}$ 的位置即可。

构造数表：

$$
\begin{matrix}
&1\\\\
&2&3\\\\
&4&5&6\\\\
&\cdots\\\\
&\cdots&\cdots&\cdots&\dfrac{n(n-1)}{2}
\end{matrix}
$$

设 $k$ 在第 $r$ 行，第 $c$ 列，则两个 $\texttt{b}$ 的出现位置为 $n-r$，$n-c+1$。

那么，如何 $O(1)$ 求出 $r$，$c$ 呢？

首先，设整数 $x$ 满足

$$\dfrac{x(x+1)}{2}\le k$$

即

$$x^2+x-2k\le 0$$

所以

$$x\le \dfrac{-1+\sqrt{1+8k}}{2}$$

显然我们要求的 $r=\lceil x\rceil$。

求出了 $r$，我们自然也能求出 $c=k-\dfrac{x(x+1)}{2}=k-\dfrac{r(r-1)}{2}$。

---

## 作者：JACK_POT (赞：2)

题意：给一个长度n的ab字符串，要求包含（n-2）个a和2个b，进行字典序排列，求第k个字符串

思路：由于只有2个b点，因此可以枚举b的位置来得到第k个排列。我们假设第一个b点位置为l，第二个为r，很明显，l的范围是1~n-1,r的范围是l+1~n。

但是如果逐个枚举k次，k<=2e9一定会TLE。因此我们先从后往前枚举l,对于每一个l所对应的r的个数（n-i）累加到计数器sum中。如果sum>=k了，说明排列已经超过了k个，答案一定在当前l中，l确定了，r也就可以很容易推出来了

code:
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define PII pair<int,int>
#define fr(i,a,b) for(int i=a;i<=b;i++)
#define fo(i,a,b) for(int i=a;i>=b;i--)
//#pragma GCC optimize(2)
/*inline int read() {
    char ch = getchar(); int x = 0, f = 1;
    while(ch < '0' || ch > '9') {
        if(ch == '-') f = -1;
        ch = getchar();
    } while('0' <= ch && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    } return x * f;
}*/
int t,n,k;
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&n,&k);//输入
		int sum=0,l,r;//sum是计数器
		fo(i,n-1,1){//从后往前枚举l
			sum+=n-i;//n-i是每个l对应的r的数量
			if(sum>=k) {//如果超过k，注意相等要取，因为相等时l也是当前i
				sum-=n-i;//t退回到上一状态
				l=i;//确定l
				r=n-(k-sum)+1;//推出r
				break;//退出循环
			}
		}
		fr(i,1,n){//输出
			if(i==l||i==r) printf("b");
			else printf("a");
		}
		cout<<endl;
	}
	return 0;
}

```


---

## 作者：waltz26 (赞：1)

题意就是求第k个排列，由题目给的例子可以发现倒数第一个b是按照1,2,3,4,...这样的规律(从右到左走1步又回到了起点又从右到左走了2步...)。

例如n=5，k=3，那么它走到了第二个规律，所以说序列是aabba。这样思路就很清晰了，请看代码。

```
#include<bits/stdc++.h>
using namespace std; 
int main()
{
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int t;
    cin>>t;

    while (t--)
    {
        int n,k;
        cin>>n>>k;

        int div=1;
        int cnt=0;
        while (k-div>=0)
        {
            cnt++;
            k-=div;
            div++;
        }

        string ans(n,'a');    //先把n个字符全部都填满a
        if (k)    //替换b
        {
            ans[n-2-cnt]='b';
            ans[n-k]='b';
        }
        else
        {
            ans[n-1-cnt]='b';
            ans[n-cnt]='b';
        }

        cout<<ans<<'\n';
    }
    return 0;
}
```

---

## 作者：andyli (赞：0)

记 $f(n,0/1/2)$ 表示长度为 $n$ 的字符串中包含 $0/1/2$个 `b` ，剩余字符均为 `a` 的字符串数，$g(n,0/1/2)$ 表示长度为 $n$ 的字符串中包含 $0/1/2$ 个 `b` ，剩余字符均为 `a` 的字符串有 $g(n,0/1/2)$ 个以 `b`为首字符，易知：  
$$f(n,0)=1$$  
$$f(n,1)=\dfrac{n!}{1!(n-1)!}=n$$  
$$f(n,2)=\dfrac{n!}{2!(n-2)!}=\dfrac{n(n+1)}{2}$$  

$$g(n,0)=0$$  
$$g(n,1)=f(n-1,0)=1$$
$$g(n,2)=f(n-1,1)=n-1$$  

因此，对于每一位，根据当前的 $k$ 值以及当前输出 `b` 的个数判断当前的字符。  

- 若已输出 $2$ 个 `b` ，则这一位必然为 `a` 。  
- 若已输出 $1$ 个 `b` ，若当前 $k \leq f(n,1)-g(n,1)=n-1$，则这一位为 `a` ，否则为 `b`，并令 $k = k-(n-1)$ 。  
- 若未输出 `b` ，若当前 $k\leq f(n,2)-g(n,2)=\dfrac{n(n+1)}{2}-(n-1)$，则这一位为 `a` ，否则为 `b` ，并令 $k = k-[\dfrac{n(n+1)}{2}-(n-1)]$。  

时间复杂度 $\mathcal O(\sum n)$。  

代码如下（[快读模板](https://www.luogu.com.cn/blog/andyli/read-template)）：  
```cpp
int main()
{
    int q;
    io.read(q);
    while (q--) {
        int n, k;
        io.read(n, k);
        int cntb = 0;
        for (int i = 1; i <= n; i++) {
            if (!cntb) { // 未输出 b
                LL x = 1LL * (n - i + 1) * ((n - i + 1) - 1) / 2; // f(n,2)
                if (k <= x - (n - i)) // f(n,2)-g(n,2)
                    io.putch('a');
                else
                    io.putch('b'), k -= (x - (n - i)), cntb++;
            } else if (cntb == 1) { // 已输出 1 个 b
                LL x = n - i + 1;
                if (k <= x - 1) // f(n,1)-g(n,1)
                    io.putch('a');
                else
                    io.putch('b'), k -= (x - 1), cntb++;
            } else // 已输出 2 个 b
                io.putch('a');
        }
        writeln();
    }
    return 0;
}
```

---

## 作者：do_while_true (赞：0)

细节还是比较多的，个人认为应当和C题调换一下。

## 题目分析

显然我们可以把$\frac{n(n-1)}{2}$个段按照第一个 'b' 的位置分为长度为$1,2,3...n-1$的段。计算这些段的前缀和，也就是计算这个段的最末端位置的位置，第i段的前缀和记作$f_i$。然后我们二分找到一个离 $k$ 最近的$f_i$，就可以$\mathcal{O}(1)$求出两个 'b' 的位置。注意如果 $k$ 等于找到的 $f_i$ 的话要加一个特判。

具体$\mathcal{O}(1)$求出两个b的位置是怎么求的，大家可以在纸上画出第 $k$ 个字符串，并且手动找到一个$f_i$ ，看这第 $k$ 个字符串的两个 'b' 的位置与 $i$ 的关系。实在看不出来就看代码部分理解。

## Code:
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int maxx,n[10011],k[10011],l,r;
unsigned long long f[100011];
char ch[100011];
int main()
{
	int T,a,b;
	scanf("%d",&T);
	for(int i=1;i<=T;i++){
		scanf("%d%d",&n[i],&k[i]);
		maxx=max(maxx,n[i]);
	}
	for(int i=1;i<=maxx-1;i++){
		f[i]=f[i-1]+i;
	}
	for(int o=1;o<=T;o++)
	{
		for(int i=1;i<=n[o];i++)
			ch[i]='a';
		l=1,r=n[o]-1;
		int mid;
		while(l<r)
		{
			mid=l+r>>1;
			if(f[mid]>k[o]) r=mid;
			else if(f[mid]<k[o]){
				if(l==mid){
					mid=r;
					break;
				}
				l=mid;
			}
			else if(f[mid]==k[o])
				break;
		}
		if(f[mid]==k[o]) ch[n[o]-mid]=ch[n[o]-mid+1]='b';
		else{
		ch[n[o]-mid]='b';
		if(mid!=1) ch[n[o]-k[o]%f[mid-1]+1]='b';
		else ch[n[o]-k[o]+1]='b';
		if(ch[n[o]+1]=='b') ch[n[o]]='b',ch[n[o]+1]='a';
		}
		for(int i=1;i<=n[o];i++)
			putchar(ch[i]);
		puts("");
	}
	return 0;
}
```


---

