# Minimums and Maximums

## 题目描述

LBW 想要一个数组，满足下面的条件：

- 设数组有 $n$ 个最小值，有 $n \in[l_1, r_1]$。

- 设数组有 $m$ 个最大值，有 $m \in[l_2, r_2]$。

LBW 比较吝啬，所以他希望数组元素个数尽可能少。

请帮助他求出这个最小值。

## 说明/提示

$1 \le T \le 5000$

$1 \le l_1 \le r_1 \le 50$

$1 \le l_2 \le r_2 \le 50$

## 样例 #1

### 输入

```
7
3 5 4 6
5 8 5 5
3 3 10 12
1 5 3 3
1 1 2 2
2 2 1 1
6 6 6 6```

### 输出

```
4
5
13
3
3
3
6```

# 题解

## 作者：Dream_weavers (赞：2)

## 题意

给出一个序列，满足以下条件被称为是“漂亮的”：

- 最少 $l_1$ 个数最多 $r_1$ 个数的与序列的**最小值**相等

- 最少 $l_2$ 个数最多 $r_2$ 个数的与序列的**最大值**相等

现在给出 $l_1,r_1,l_2,r_2$，求“漂亮的”序列长度**最小**是多少。

## 思路

虽然题目中提到了最大值和最小值，但只用求序列的长度，就不用考虑序列中的数值分别是多少。

为了让序列长度**最小**，就要先考虑 $l_1,l_2$ 的大小，分为两种情况：$l_1\leq l_2$ 和 $l_1>l_2$。

设 $ans$ 为序列长度。看情况一 $l_1\leq l_2$，那么序列中所有数都和最大值相等，也就是所有数都相等，$ans=l_2$。但如果 $r_1<l_2$，序列中就要分为两类数，一类与最小值相等，一类与最大值相等，$ans$ 再加上 $l_1$。

情况二和情况一类似，把 $l_1$ 和 $l_2$ 颠倒，$r_1$ 和 $r_2$ 颠倒就可以了。

ps：当序列中所有数相等时，最小值**等于**最大值。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int l1,r1,l2,r2,t; 
signed main(){
	scanf("%lld",&t);
	while(t--){
		int ans=0;
		scanf("%lld%lld%lld%lld",&l1,&r1,&l2,&r2);
		if(l1<=l2){
			ans=l2;
			if(r1<l2)ans+=l1;
		}else{
			ans=l1;
			if(r2<l1)ans+=l2;
		}
		printf("%lld\n",ans);
	}
	return 0;
}

```

---

## 作者：Drind (赞：1)

## 题面简述
一个数列仅当有 $l_1$ 至 $r_1$ 个元素等于数列最小值且有 $l_2$ 至 $r_2$ 个元素等于序列最大值时该序列是完美的。


给定4个数  $l_1$ $r_1$ $l_2$ 和 $r_2$ ， 请问最短的完美序列长度。

## 题面分析
看到题面我们开始分析。

其实只需要使序列满足有 $l_1$ 个最小值和 $l_2$ 个最大值即可，那么理论上输出 $l_1+l_2$ 可得到100pts。

事实上[这样](https://www.luogu.com.cn/record/75885698)得不到满分。

考虑一个特殊情况:

输入为 $3$ $5$ $4$ $6$ ， 预计输出答案7，实际输出答案4，原因：最大值和最小值重合，数列中只有一种值时最大值即为最小值。

## 讨论特殊情况

那么在什么情况下最大值等于最小值呢？

分为两种情况:

1. $l_1 \le r_2$ 且 $l_1 \ge l_2$ . 
2. $l_2 \le r_1$ 且 $l_2 \ge l_1$ .

显然在情况1下答案为更大的 $l_1$ ，情况二下答案为更大的 $l_2$。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;

int main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)//n组数据
	{
		int l1,l2,r1,r2;//输入
		cin>>l1>>r1>>l2>>r2;
		if(l1<=r2&&l1>=l2)//情况1
		{
			cout<<l1;
		}
		else if(l2<=r1&&l2>=l1)//情况2
		{
			cout<<l2;
		}
		else//朴素情况
		{
			cout<<l1+l2;
		}
		cout<<endl;
	}
   return 0;
} 
```

祝您成功[AC](https://www.luogu.com.cn/record/75887928)!

---

## 作者：snail2956 (赞：1)

### 题意:

[To 洛谷](https://www.luogu.com.cn/problem/CF1680A)  
[To CF](https://codeforces.com/problemset/problem/1680/A)

若同时满足以下两个条件，则数组是美观的：
- 数组中元素最小值个数 $n_1$ 满足 $l_1\leqslant n_1 \leqslant r_1$;
- 数组中元素最大值个数 $n_2$ 满足 $l_2\leqslant n_2 \leqslant r_2$。

给定 $l_1,r_1,l_2,r_2$，计算一个美观的数组中,元素的最小可能数量。

---

### 思路

特判即可

- 当 $l_1=l_2$ 时，可构建一个长度为 $l_1$（或 $l_2$），且每个元素都相等的数组，使该数组美观；
- 当 $r_2\geqslant l_1$ 且 $l_1>l_2$ 时，可构建一个长度为 $l_1$ ，且每个元素都相等的数组，使该数组美观；
- 当 $r_1\geqslant l_2$ 且 $l_1<l_2$ 时，可构建一个长度为 $l_2$ ，且每个元素都相等的数组，使该数组美观；
- 剩余情况下，可构建一个长度为 $l_1+l_2$ ，且有 $l_1$ 个相等较小元素、$l_2$ 个相等较大元素的数组，使该数组美观。

可证明上述思路最优

---

### $Code$

```cpp
//snail2956
//CF1680A
//2022.5.15 16:56

#include<cstdio>

int t;

int main(){
	scanf("%d",&t);
	while(t--){
		int l1,r1,l2,r2;
		scanf("%d %d %d %d",&l1,&r1,&l2,&r2);
		if(l1==l2) printf("%d\n",l1);
		else if(r2>=l1&&l1>l2) printf("%d\n",l1);
		else if(r1>=l2&&l1<l2) printf("%d\n",l2);
		else printf("%d\n",l1+l2);
	}
	//QwQ
	return 0;
} 
```


---

## 作者：duchengjun (赞：1)

# 题意

给你四个数 $l_1,r_1,l_2,r_2$，使得美丽的数组元素个数最少，求最少元素个数。

什么是美丽的数组？

1. 数组中最少有 $l_1$ 个元素，最多有 $r_1$ 个元素等于其最小值；

2. 数组中最少有 $l_2$ 个元素，最多有 $r_2$ 个元素等于其最大值。

# 分析

原题太良心了，告诉我们可能每一个元素值是一样的，但这样的情况十分特殊。

这种情况就是：

$$\max(l_1,l_2)\le \min(r_1,r_2)$$

因为当每一个元素都相等时，数组中的最小值等于数组中的最大值，所以只需要满足 $\max(l_1,l_2)\le \min(r_1,r_2)$ 就行了。

而若 $\max(l_1,l_2)> \min(r_1,r_2)$ 时，需要两个不同的元素，所以要 $l_1+l_2$ 个元素。

# Code

```cpp
#include<bits/stdc++.h>
#define ri register int
#define ll long long
#define ull unsigned long long
using namespace std;
#define getchar() (S==T&&(T=(S=B)+fread(B,1,1<<15,stdin),S==T)?EOF:*S++)
namespace get_out
{
    char B[1<<20],*S=B,*T=B;
    char op;
    inline void read_(int &x)
    {
        x=0;
        int fi(1);
        op=getchar();
        while((op<'0'||op>'9')&&op!='-') op=getchar();
        if(op=='-') op=getchar(),fi=-1;
        while(op>='0'&&op<='9') x=(x<<1)+(x<<3)+(op^48),op=getchar();
        x*=fi;
        return;
    }
    inline void read_(long long &x)
    {
        x=0;
        int fi(1);
        op=getchar();
        while((op<'0'||op>'9')&&op!='-') op=getchar();
        if(op=='-') op=getchar(),fi=-1;
        while(op>='0'&&op<='9') x=(x<<1)+(x<<3)+(op^48),op=getchar();
        x*=fi;
        return;
    }
    inline void read_(double &x)
    {
        x=0.0;
        float fi(1.0),sm(0.0);
        op=getchar();
        while((op<'0'||op>'9')&&op!='-') op=getchar();
        if(op=='-') op=getchar(),fi=-1.0;
        while(op>='0'&&op<='9') x=(x*10.0)+(op^48),op=getchar();
        if(op=='.') op=getchar();
        int rtim=0;
        while(op>='0'&&op<='9') sm=(sm*10.0)+(op^48),++rtim,op=getchar();
        while(rtim--) sm/=10.0;
        x+=sm,x*=fi;
        return;
    }
    inline void read_(string &s)
    {
        char c(getchar());
        s="";
        while(!isgraph(c)&&c!=EOF) c=getchar();
        for(;isgraph(c);c=getchar()) s+=c;
    }
    inline void read_(char &c)
    {
        for(c=op;c==' '||c=='\n'||c=='\r'||c=='\t';c=getchar());
        op=c;
    }

    template<typename Head,typename ...Tail>
    inline void read_(Head& h,Tail&... t)
    {read_(h),read_(t...);}

    inline void write_(){}
    inline void postive_write(unsigned x)
    {
        if(x>9) postive_write(x/10);
        putchar(x%10|'0');
    }
    inline void postive_write(unsigned long long x)
    {
        if(x>9) postive_write(x/10);
        putchar(x%10|'0');
    }
    inline void postive_write(int x)
    {
        if(x>9) postive_write(x/10);
        putchar(x%10|'0');
    }
    inline void postive_write(long long x)
    {
        if(x>9) postive_write(x/10);
        putchar(x%10|'0');
    }
    inline void postive_write(short x)
    {
        if(x>9) postive_write(x/10);
        putchar(x%10|'0');
    }
    inline void write_(const char* ss) {while(*ss) putchar(*ss++);}
    inline void write_(char c) {putchar(c);}
    inline void write_(string s) {for(unsigned i=0;i<s.size();++i) putchar(s[i]);}
    inline void write_(short x)
    {
        if(x<0) putchar('-'),postive_write(-x);
        else postive_write(x);
    }
    inline void write_(int x)
    {
        if(x<0) x=-x,putchar('-');
        postive_write(x);
    }
    inline void write_(long long x)
    {
        if(x<0) x=-x,putchar('-');
        postive_write(x);
    }
    inline void write_(unsigned x) {postive_write(x);}
    inline void write_(ull x) {postive_write(x);}

    template<typename Head,typename ...Tail>
    inline void write_(Head h,Tail ...t) {write_(h),write_(t...);}
}
using get_out::read_;
using get_out::write_;
int T;
int l1,r1,l2,r2;
int main(void){
	std::ios::sync_with_stdio(false);
	read_(T);
	while(T--){
		read_(l1,r1,l2,r2);
		int a=max(l1,l2),b=min(r1,r2); 
		if(a<=b)
			write_(a,"\n");
		else
			write_(l1+l2,"\n");
	}
	write_("\n");
	return 0;
}


```


---

## 作者：Jerrlee✅ (赞：1)

## 题意
如果满足以下两个条件，则数组是美丽的：

- 数组中至少有 $l_1$ 并且最多有 $r_1$ 个值等于数组所有值的最小值；

- 数组中至少有 $l_2$ 并且最多有 $r_2$ 个值等于数组所有值的最大值。

求这个数组内包含的元素数量的最小值。
## 思路
观察样例，发现当 $l_1 \sim r_1$ 与 $l_2 \sim r_2$ 有共同的数时，选择 $l_1$ 和 $r_1$ 的最大值即可（最大值此时也是最小值）。

当 $l_1 \sim r_1$ 与 $l_2 \sim r_2$ 无共同的数时，既要满足最小值的数量要求，也要满足最大值的数量要求，那数组不仅包括 $l_1$ 个最小值，还得包括 $l_2$ 个最大值，答案就是 $l_1+l_2$。
## 代码
```cpp
#include<iostream>
using namespace std;
int main(){
    int t;
    cin>>t;
    while(t--){
        int a,b,c,d;
        cin>>a>>b>>c>>d;
        if(a>=c&&a<=d) cout<<a;
        else if(c>=a&&c<=b) cout<<c;
        else cout<<a+c;
        cout<<endl;
    }
}
```
[AC 记录（洛谷）](https://www.luogu.com.cn/record/75791398)

[AC 记录（CF）](https://codeforces.com/contest/1680/submission/157255704)

---

## 作者：ttq012 (赞：0)

思维题。

我们判断两个区间 $[a, c]$ 和 $[b, d]$ 是否可以相交，如果相交，那么只需要 $\max(a, c)$ 个数字就可以组成这种序列，否则就需要 $a$ 个最小值和 $c$ 个最大值，输出 $a+c$。

```cpp
#include <bits/stdc++.h>

using namespace std;

signed main() {
    int T;
    cin >> T;
    while (T --) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        int mi = max(a, c);
        int mx = min(b, d);
        if (mi <= mx)
            cout << mi << '\n';
        else
            cout << a + c << '\n';
    }
    return 0;
}


```


---

## 作者：力巴尔 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1680A)

这道题的做法很简单：如果 $r_1 < l_2$ 或 $l_1 > r_2$，则输出 $l_1 + l_2$；否则输出 $\max(l_1, l_2)$。

拿 $3$ $5$ $4$ $6$ 为例，我们可以构造一个只有 $4$ 个 $1$ 的数列，即可满足题意。

再拿 $3$ $3$ $10$ $12$ 为例，可以构造出一个含有 $3$ 个 $1$ 和 $10$ 个 $2$ 的数列，即可满足题意。

其他样例同理，即可得到上述结论。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int t;
    cin>>t;
    while (t--)
    {
        int a, b, c, d;
        cin>>a>>b>>c>>d;
        if (a > d || b < c)
            cout<<a + c<<endl;
        else
            cout<<max(a, c)<<endl;
    }
}
```


---

