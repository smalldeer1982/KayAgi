# Dice Tower

## 题目描述

鲍勃正在玩 $6$ 面的骰子。他有不限量的这样的骰子。骰子可以搭成骰子塔，骰子塔上可以看见的点子的数量称为骰子塔的点数。

## 样例 #1

### 输入

```
4
29 34 19 38
```

### 输出

```
YES
YES
YES
NO
```

# 题解

## 作者：C171501 (赞：4)

看 Codeforces 出了 Global Round 7, 就翻了翻以前的题。

这道题可以说是找规律。由骰子构造可以看出，$1$ 的对面是 $6$, $2$ 的对面是 $5$, $3$ 的对面是 $4$。由此可见，无论摆放方式如何，相对的面的和总为 $7$, 则骰子侧面的点数和为 $14$。

同时顶面还有 $1$到 $6$ 点，那么我们就可以判断 $x \bmod 14$ 是否大于 $1$ 且小于 $6$。

但是如果直接这样交上去，就会 Wrong Answer on test 2 。为什么呢？我们发现，无论怎么放，总点数一定会大于 $14$，那么如果 $x$ 不大于 $14$，则直接输出 `NO` 即可。

记得开大一点，毕竟 $10^{18}$ 不是一个小数目。

如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
unsigned long long t,x;
int main()
{
	cin>>t;
	for(int i=1;i<=t;++i)
	{
		cin>>x;
		if(x<=14) cout<<"NO"<<endl;
		else
		{
			if(x%14>=1&&x%14<=6) cout<<"YES"<<endl;
			else cout<<"NO"<<endl;
		}
	}
	return 0;
}
```


---

## 作者：luguangxing (赞：1)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1266B/4b7ea8a80a5909a0126993bc3864bdd5c9fee908.png)

看这张图由小学知识可以得出 $1$ 的对面是 $6$，$2$ 的对面是 $5$，$3$ 的对面是 $4$。我们再看这个骰子塔，他的点数是由 $14+14+1$ （被遮住的面不算）得出的那么我们可知一个骰子塔的点数是由：顶层的点数+骰子数 $\times 14$ 得出的,程序中把他反推写到判断中即可正确，还有一种可以直接判 NO 就是输入的数小于或等于 $14$（这骰子又不能切开，记得要开 long long）。
![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1266B/0ece854e079dda4451dd5831b0aed5800fd947c0.png)

代码展示：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long x,t;
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>x;
		if(x<=14)
			cout<<"NO"<<endl;
		else
		{
			if(x%14>=1&&x%14<=6)
				cout<<"YES"<<endl;
			else
				cout<<"NO"<<endl;
		}
	}
	return 0;
} 
```

---

## 作者：cff_0102 (赞：1)

众所周知，骰子相对的面相加为 $7$，所以一个由 $n$ 个骰子堆成的塔点数应该为 $14\times n$ 加上顶上的那个数字。

所以当 $x>14$ 时，判断 $x\bmod14$ 是否在 $1$ 和 $6$ 之间即可。

注意数据范围， $x$ 要用 `long long` 来存。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	ios::sync_with_stdio(false);
	int t;cin>>t;
	while(t--){
		long long x;cin>>x;
		if(x<=14){
			cout<<"NO\n";
			continue;
		}
		x=x%14;
		if(1<=x&&x<=6){
			cout<<"YES\n";
		}else{
			cout<<"No\n";
		}
	} 
	return 0;
}
```

---

## 作者：Lizj (赞：1)

题意：输入 $T$ 个整数 $n$ 代表骰子塔表面的点数，求出有没有合适个数的骰子能搭成这样的塔。

分析：观察骰子可以看出，骰子相对的面的点数之和一定为 $7$($1+6,2+5,3+4$)，而骰子塔的侧面由多个这样的相对的面构成，同时，塔的顶面还有 $1$ 到 $6$ 个点，所以只需要判断 $n\bmod 14$ 是否在 $1$ 到 $6$ 以内，如果在，输出 `YES`；如果不在，输出 `NO`。但在开始前还需要判断骰子总点数是否大于 $14$，如果不大于 $14$ 也需要输出 `NO`。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int T;
	cin>>T;
	while(T--){
		long long n;	//记得开 long long
		cin>>n;
		if(n<=14){
			cout<<"NO"<<endl;
		}
		else{
			if(n%14>=1&&n%14<=6){
				cout<<"YES"<<endl;
			}
			else{
				cout<<"NO"<<endl;
			}
		}
	}
	return 0;
}
```


---

## 作者：Terry2011 (赞：0)

# 题面描述：
有 $t$ 次询问，每次包含一个整数，表示骰子塔的点数。如果可以搭成这样的骰子塔，输出`YES`，否则输出`NO`。
# 题目分析：
这道题目的第一张图给了我们提示：骰子相对的两个面相加等于 $7$ 这样我们再来看一个骰子塔，可以看成两个部分：侧面和顶面。每一层的侧面都是由两组相对的面组成的。和为 $14$，也就是说，骰子塔侧面的点数一定是 $14$ 的倍数。还剩下顶面。因为顶面只可能是 $1$ 至 $6$，所以每次输入的 $x \bmod 14 $ 要 $\ge1$ 并且 $\le 6$。最后还要再特判一次，$x$ 是否 $> 14$，记得开`long long`哦！
# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	long long t,x;//定义变量 
	cin>>t;//输入询问次数 
	for(int i=1;i<=t;i++){
		cin>>x;//循环读入 
		if(x>14&&x%14>=1&&x%14<=6){//判断条件 
			cout<<"YES"<<endl;//
		}else{
			cout<<"NO"<<endl;
		}
	}
	return 0;
}
```

---

## 作者：SunsetVoice (赞：0)

$10^{18}$ 的数据必定思维，暴力直接寄掉。

一个在中间的骰子**被遮住的一定是相对的两个面**，而相对的两面和为 $7$。所以一个在中间的骰子对答案的贡献是 $14$。此时只需要看顶上的数就行了。

而顶上的数只能是 $1$ 到 $6$。所以只需要看输入的这个数对 $14$ 取余后的余数是否小于 $6$ 并大于 $1$。

然后作者由于兴奋过度而亡。

![图又炸了......](https://cdn.luogu.com.cn/upload/image_hosting/ttmc7t90.png)

如果他给的数在一到六之间，是无论如何也到不了的。此时输出 `NO`。

code：
```cpp
#include<bits/stdc++.h>
using namespace std;

int main(){
	long long i,j,n,a;
	cin>>n;
	for(i = 1;i<=n;i++){
		cin>>a;
		if(a<=6)cout<<"NO"<<endl;
		else if(a%14<=6 and a%14>=1)cout<<"YES"<<endl;
		else cout<<"NO"<<endl;
	}
	return 0;
} 
```


---

## 作者：Rainbow_Sky (赞：0)

## 思路

对于一个骰子，相对的两面之和为 $7$，所以首先，我们需要明白，由一个骰子组成的塔，设点数为 $k$，可以看到 $k\ge15$，所以首先判断它是否大于 $14$，然后，再用 $k\bmod6$，如果结果在 $1$ 和 $6$ 之间，说明是可行的，否则不行。

## AC code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxm=1e5+10;
const int maxn=1e3+10;
const int mod=1e9+7;
inline int read(){
	int x=0,y=1;char c=getchar();
	for(;c<'0'||c>'9';c=getchar())if(c=='-')y=-1;
	for(;c>='0'&&c<='9';c=getchar())x=(x<<1)+(x<<3)+(c^48);
	return x*y;
}
int a[maxm];
signed main()
{
	int t=read();
	while(t--)
	{
		int x=read();
		if(x<=14)
		{
			cout<<"NO\n";
			continue;
		}
		else
		{
			int k=x%14;
			if(k>=1&&k<=6)
			{
				cout<<"YES\n";
			}
			else cout<<"NO\n";
		}
	}
	return 0;
}
```

---

## 作者：zwyyy (赞：0)

### [原题传送门](https://www.luogu.com.cn/problem/CF1266B)

~~既然写了翻译，那就顺便写个题解吧~~

---

## 思路
第一眼看这题的时候以为会是一道模拟，但是~~通过生活常识~~我们可以得知，骰子的两个相对的面加起来一定为 $7$。

所以我们无论怎么摆骰子，它的四个侧面的点数加起来肯定为 $2 \times 7 = 14$。

现在验证能否摆出塔，只需要判断最顶上的面即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;
	long long x;
	scanf("%d", &t);
	for(int i = 1; i <= t; ++i){
		scanf("%lld", &x);
		if(x <= 14){	//x小于14代表了这个数想要摆出来就最多只能有4个侧面，而这样是不行的，因为最上面的骰子还有一个上面
			printf("NO\n");
			continue;
		}
		else{
			if(x % 14 >= 1 && x % 14 <= 6){	/*x%14<1代表这个数想要摆出来就只会有侧面，没有上面；
											x%14>6代表这个数想要摆出来最上面的面点数会大于6*/
				printf("YES\n");
			}
			else{
				printf("NO\n");
			}
		}
	}
	return 0;
}
```


[AC](https://www.luogu.com.cn/record/112962828)

#### 这道题比较简单，建议自己看着思路写一遍

---

## 作者：_VEGETABLE_OIer_xlc (赞：0)

## 题意

Bob 有 $t$ 个最喜欢的数，现在想用若干个骰子竖着叠起来，使能看到的数的和等于这个最喜欢的数，这可能吗？

## 思路

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1266B/4b7ea8a80a5909a0126993bc3864bdd5c9fee908.png)

观察骰子结构，会发现 $1$ 对 $6$，$2$ 对 $5$，$3$ 对 $4$。每一对的和都为    $7$。

假设摆 $a$ 个骰子，则无论怎么摆，它的侧面之和都为 $14\times a$，所以能不能摆成最喜欢的数，还要看最顶上的数。

由于最顶上的数能为和最少贡献 $1$，最多贡献 $6$，所以如果最喜欢的数取余  $14$  的结果大于等于 $1$ 且小于等于 $6$，那它就能摆出来。

```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
long long n;
int main(){
	cin>>t;
	while(t--)
	{
		cin>>n;
		if(n<=14)
		{
			cout<<"No"<<endl;
			continue;
		}//非常重要，不然会WA。 
		else
		{
			if(n%14>=1&&n%14<=6)
				cout<<"Yes"<<endl;
			else
				cout<<"No"<<endl;
		}
	}
	return 0;
} 
```






---

