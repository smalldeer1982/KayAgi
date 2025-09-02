# Increase and Copy

## 题目描述

Initially, you have the array $ a $ consisting of one element $ 1 $ ( $ a = [1] $ ).

In one move, you can do one of the following things:

- Increase some (single) element of $ a $ by $ 1 $ (choose some $ i $ from $ 1 $ to the current length of $ a $ and increase $ a_i $ by one);
- Append the copy of some (single) element of $ a $ to the end of the array (choose some $ i $ from $ 1 $ to the current length of $ a $ and append $ a_i $ to the end of the array).

For example, consider the sequence of five moves:

1. You take the first element $ a_1 $ , append its copy to the end of the array and get $ a = [1, 1] $ .
2. You take the first element $ a_1 $ , increase it by $ 1 $ and get $ a = [2, 1] $ .
3. You take the second element $ a_2 $ , append its copy to the end of the array and get $ a = [2, 1, 1] $ .
4. You take the first element $ a_1 $ , append its copy to the end of the array and get $ a = [2, 1, 1, 2] $ .
5. You take the fourth element $ a_4 $ , increase it by $ 1 $ and get $ a = [2, 1, 1, 3] $ .

Your task is to find the minimum number of moves required to obtain the array with the sum at least $ n $ .

You have to answer $ t $ independent test cases.

## 样例 #1

### 输入

```
5
1
5
42
1337
1000000000```

### 输出

```
0
3
11
72
63244```

# 题解

## 作者：tommymio (赞：3)

考虑最简单的做法，将 $n$ 分解为 $xy+b(0\leq b<x\leq y)$。

那么我们需要花 $(x-1)$ 步将 $1\to x$，然后花 $y-1$ 步复制出另 $y-1$ 个 $x$，如果 $b>0$ ，我们在将 $x$ 增加的时候顺带复制出一份 $b$，否则不需要。那么对于一个分解 $xy+b$，如果 $b>0$，它的答案为 $(x-1)+(y-1)+1$，如果 $b=0$，它的答案为 $(x-1)+(y-1)$。

显然 $x,y$ 尽可能接近时答案最优。也就是 $\sqrt n$ 时。但是为了不因为一些奇怪的特判 $\text{Hacked}$，我们使用 $O(\sqrt n)$ 的枚举，枚举每对 $x,y$，时间复杂度为 $O(T\sqrt n)$。

其实比赛时什么方法好写，能过题，又不会假就是最好的，无需过于纠结时间复杂度，这些事情是平常考虑的qwq。

**Show the Code**

```cpp
#include<cstdio>
inline int read() {
	register int x=0,f=1;register char s=getchar();
	while(s>'9'||s<'0') {if(s=='-') f=-1;s=getchar();}
	while(s>='0'&&s<='9') {x=x*10+s-'0';s=getchar();}
	return x*f;
}
inline int min(const int &x,const int &y) {return x<y? x:y;} 
int main() {
	int T=read();
	while(T--) {
		int n=read(),ans=n+10;
		for(register int i=1;1ll*i*i<=n;++i) {
			ans=min(ans,n/i+i-2+(n%i>0));
		}
		printf("%d\n",ans);
	}
	return 0; 
}
```

---

## 作者：king_xbz (赞：2)

# 题意分析 
给定$n$和初始数组，其中$a[1]=1$,每次操作可以让数组中的**一个元素**增加1，或者复制一个元素到空白位置，最少多少次操作让数组元素之和到达$n$.

# 思路分析
刚开始样例描述有问题，给我卡了好久不知所云。。。

考虑贪心：对于5，我们分解成$2*2+1,42$分解成 $7*6=6*6+7$，推广一下大数据，$1337=36*36+41$.找到规律了吧！

先分解成最近平方和$ans=(\sqrt {n}-1)*2$

然后特判$+1，+2$情况即可。特判情况在下面

# 代码实现
```cpp
signed main()
{
	int T;
	cin>>T;
	while(T--)
	{
		int n;
		cin>>n;
		int now=floor(sqrt(n));
		int tim=(now-1)*2;
		n-=now*now;
		if(n==0)
		cout<<tim;
		else
		if(n>now)//特殊情况
		cout<<tim+2;
		else
		cout<<tim+1;
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：—维尼— (赞：1)

## 题目描述
给定$n$和初始数组，其中$a[1]=1$,每次操作可以让数组中的一个元素++，或者复制一个元素到空白位置，最少多少次操作让数组元素之和到达$n$.

## 题目思路
那我现在可以告诉大家题目的真正意图了

其实就是给你一个元素，你可以选择让他加$1$或者复制一个

我们口胡一下样例就能发现规律了

其实这种题要么是从加到一半开始复制，要么就是加到根号的位置开始复制

加到一半显然不可能，最后一组样例

$1000000000$如果加到一半显然不符合标准

我们来试加到$n$的根号

假如是样例中的$42$，平方根为$6$（取整）

我们加到$6$需要$5$次操作

然后再复制6次就能到$42$了

刚好$11$次

其他样例也是如此

机房大佬说可以用对勾函数证明，蒟蒻只会口胡，大家有什么可以严格证明的方法可以发到评论区分享

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;
	cin>>t;
	while(t--){
		long long n;
		cin>>n;
		int x=sqrt(n);
		int ans=x-1;//次数 
		long long sum=x;
		while(sum<n){
			sum+=x;
			ans++;
		}
		cout<<ans<<endl;
	}
	return 0;
} 
```



---

## 作者：dead_X (赞：1)

## 题意
求出 $x\times y\geq n,x\in Z^+,y\in Z^+$  中 $x+y-1$ 的最小值。
## 思路
显然 $y=\lceil\frac{n}{x}\rceil$，因此 $Ans=x+\lceil\frac{n}{x}\rceil-1$ 的最小值。

显然根据数学老师教我们的知识，$x=\frac{n}{x}=\sqrt{n}$ 的时候能取到最优值。

但是为了确保正确性，最好把这个值附近的数值都搜一遍。
## 代码
```
#include<bits/stdc++.h>
using namespace std;
#define int long long
int read(){
    int num=0;
    char ch=getchar();
    while(!isdigit(ch)) ch=getchar();
    while(isdigit(ch)) num*=10,num+=ch-48,ch=getchar();
    return num;
}
int n;
void Main(){
	scanf("%lld",&n);
	int t=sqrt(n-1);++t;
	printf("%lld\n",t+(n-1)/t-1);
}
signed main(){
	for(int T=read();T;--T)Main();
}
```

---

## 作者：shzaiz (赞：0)

#### CF1426C Increase and Copy 题解

**一些性质**. 

*性质1.* 当$n>1$的时候,应当复制一个大于1的元素接在后面.

*说明*. 考虑增加1操作. 这对于答案的贡献是1. 如果当前数是n,`Copy`操作就会对答案贡献n.

假设现在的和是$m$, 要求的和是$S$.增加1达到的是$S-1$. 然而复制一个比$1$大的数$l$会导致答案变为$S-l$. 由于$l>1$, 必然会导致结果最优.

*结论1.* 首先将第一个数增加到某个值,然后不断的复制,才是最优秀的.

*性质2.* 先增加到$\sqrt{n}$,再自增,达到最优秀情况.

*说明*. 假设自增到$x$. 首先需要增加$(x-1)$个操作.接下来考虑不断地复制,需要:$\lceil\frac{n-x}{x}\rceil$次操作.那么总共的次数是:
$$
(x-1)+\frac{n-x}{x}=x+\lceil\frac{n}{x}\rceil-2
$$
.

由基本不等式不难发现,在大于0的部分在$\sqrt n$处存在极小值.

**思路**. 首先将第一个数增加到$\sqrt{n}$,然后不断的复制自身.

**代码**. 

```cpp
#include <bits/stdc++.h>
using namespace std;
void solve(){
	int n;cin>>n
	int s = sqrt(n);
	int ans = (s+(n/s)-2);
	if(n%s!=0) ans++;
	cout<<ans<<"\n";
}
int main(){
	int T;cin>>T;while(T--)solve();return 0;
}
```



---

