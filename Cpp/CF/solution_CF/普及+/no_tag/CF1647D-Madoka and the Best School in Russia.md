# Madoka and the Best School in Russia

## 题目描述

- 如果 $n$ 是 $d$ 的倍数，则称 $n$ 为“好数”；
- 如果 $n$ 是“好数”且不能写成任意两个“好数”之积，则称 $n$ 是“美丽数”。

$T$ 组询问，每组询问给定两个正整数 $x,d$，保证 $x$ 是好数，问 $x$ 是否有至少两种方式写为至少一个“美丽数”之积。如果是，输出 `YES`；否则输出 `NO`。

注意输出对大小写不敏感。

## 样例 #1

### 输入

```
8
6 2
12 2
36 2
8 2
1000 10
2376 6
128 4
16384 4```

### 输出

```
NO
NO
YES
NO
YES
YES
NO
YES```

# 题解

## 作者：StarLbright40 (赞：7)

~~前言：分讨题爬~~

[博客园链接](https://www.cnblogs.com/XG0000/p/CF1647D.html)

题意：

>给定 $x,d(2\le x,d\le 10^9)$，定义 $d$ 的倍数为“好数”，不能分解为好数之积的好数为“漂亮数”。

>保证 $x$ 是好数，询问 $x$ 是否有两种方式分解为漂亮数之积。多组询问。

（注：本文中“分解”和“拆”均指分解为积）

首先，令 $x=d^k\times s$，其中 $k>0,d\nmid s$。

那么 $k-1$ 个 $d$ 和一个 $d\times s$ 即为一种分解方案。

接下来考虑构造另一种。

1. 若 $k=1$，则显然没有第二种方案。

则接下来的讨论中均有 $k>1$。

2. 若 $s$ 为合数，则将其分解为两个数，分别乘在两个 $d$ 上，则得到第二种方案。

则接下来的讨论中 $s$ 均为质数或 $1$。

那么 $s$ 拆不动了，只能拆 $d$。

3. 若 $d$ 为质数，那么它就没得拆，所以没有第二种方案。

则现在剩下的情况是 $k>1$，$s$ 不是合数，$d$ 是合数。

4. 若 $d$ 中含有不同于 $s$ 的质因数，则将这个质因数乘在一个 $d$ 上，剩下的部分与 $s$ 一起乘在另一个 $d$ 上，则得到第二种方案，连上被拆的一共需要 $3$ 个 $d$，所以需要 $k>2$。

那么注意到，接下来的讨论中有 $d=s^q$，其中 $q>1$。

5. 若 $q>2$，则 $d$ 可以拆为 $s$ 和 $s^{q-1}$。将 $s^2$ 和 $s^{q-1}$ 分别乘在一个 $d$ 上，则得到第二种方案，连上被拆的一共需要 $3$ 个 $d$，所以需要 $k>2$。

6. 若 $q=2$，则 $d$ 可以拆为两个 $s$。现在不能将 $s^2$ 乘在 $d$ 上了（因为结果不是漂亮数），所以只能将三个 $s$ 分别乘在三个 $d$ 上，连上被拆的一共需要 $4$ 个 $d$，所以需要 $k>3$。

注意到后三类可以整合为对 $s^2$ 与 $d$ 是否相等的判断。

分类清楚了，代码就容易实现了。加一个质数判断即可。时间复杂度 $O(T\sqrt{x})$。

```cpp
#include<cstdio>
using namespace std;
int T,x,d,k;
bool check(int n){
	if(n<4) return 1;
	if(n%2==0||n%3==0) return 0;
	for(int i=5;i*i<=n;i+=6)
		if(n%i==0||n%(i+2)==0) return 0;
	return 1;
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&x,&d);
		for(k=0;x%d==0;x/=d,++k);
		if(k<2) printf("NO\n");
		else if(!check(x)) printf("YES\n");
		else if(check(d)) printf("NO\n");
		else printf(k>(x*x==d)+2?"YES\n":"NO\n");
	}
	return 0;
}
```


---

## 作者：Feyn (赞：1)

首先如果只是需要找出来一个乘积的方案是话，那么答案很简单，只需要一直用 $d$ 去除 $n$，直到 $n$ 剩下一个除不尽 $d$ 的部分，令为 $x$。于是可以把除掉的这些 $d$ 依次排开，需要做的就是把 $x$ 拆成一些数的乘积形式并分配给这些  $d$ 就能得到方案，于是有结论说如果 $x$ 不是质数的话，那么该组数据一定是有解的。

如果 $x$ 是个质数，那么说明当前状态下只能贡献出来一组连乘方案，所以可以考虑把一个 $d$ 放入 $x$ 中，思考是否存在合法方案（相当于把 $x$ 乘上 $d$）。如果 $d$ 含有多个质因子，那么可以把不同的质因子分到不同的地方，最后肯定能得到合法方案；如果 $d$ 只有一个因子，那么统计一下 $x$（乘上 $d$ 之后的） 该因子次数以及每个 $d$ 中该因子的次数，然后贪心地去判断一下即可。

代码：

```cpp
#include<bits/stdc++.h>
//#define feyn
using namespace std;
const int N=110;
inline void read(int &wh){
    wh=0;int f=1;char w=getchar();
    while(w<'0'||w>'9'){if(w=='-')f=-1;w=getchar();}
    while(w<='9'&&w>='0'){wh=wh*10+w-'0';w=getchar();}
    wh*=f;return;
}

int m,n;

void solve(){
	read(m);read(n);
	int pr,pn=0,nn=n,snum=0;
	for(int i=2;i*i<=nn;i++){
		if(nn%i==0){
			pn++;pr=i;
			while(nn%i==0)nn/=i;
		}
	}
	if(nn^1)pr=nn,pn++;
	while(m%n==0)m/=n,snum++;
	if(snum<=1)return puts("No"),void();
	for(int i=2;i*i<=m;i++){
		if(m%i==0)return puts("Yes"),void();
	}
	m*=n;int num=0;
	if(snum==2)return puts("No"),void();
	if(pn>1)return puts("Yes"),void();
	while(n%pr==0)num++,n/=pr;int pnum=0;
	while(m%pr==0)pnum++,m/=pr;snum--;
	if(pnum<=(num-1)*snum)puts("Yes");
	else puts("No");
}

signed main(){
	
	#ifdef feyn
	freopen("in.txt","r",stdin);
	#endif
	
	int test;read(test);
	while(test--)solve();
	
	return 0;
}
```

---

## 作者：Argon_Cube (赞：0)

大力分类讨论屑题。

* **【题目链接】**

[Link:CF1674D](https://www.luogu.com.cn/problem/CF1647D)

* **【题目翻译】**

我们定义，一个数是 $\rm Nsq$ 数，当且仅当它是 $d$ 的倍数，但不能表示为两个 $d$ 的倍数的积。

现在给定一个数 $n$，保证 $d|n$，问是否有不止一种方法将 $n$ 表示为几个 $\rm Nsq$ 数的积。

* **【解题思路】**

大力分讨。

首先如果 $d^2|n$ 才有可能有不止一种方案；

然后，我们将 $n$ 表示为 $xd^k$，其中 $x,k\in\mathbb Z$ 且 $x$ 不是 $d$ 的倍数。

如果 $x$ 不是质数，那么一定有不止一种方案；

否则，$d^3|n$ 才有可能有不止一种方案。

做完上面的判断，如果还没出结果，那么继续判断，假如 $d$ 是质数，那么只有一种方案；

否则，我们可以尝试将一个 $d$ 拆成两份。假如存在一种方案，使得可以将这两份中的一份分配给 $xd$，使得结果不是 $d^2$ 的倍数，有不止一种方案；

假如以上判断都没判断出来，那么，有不止一种方案，当且仅当 $d^4|n$。

* **【代码实现】**

```cpp
#include <iostream>
#include <array>
 
using namespace std;
 
bool is_prime(long long num)
{
	for(long long i=2;i*i<=num;i++)
		if(num%i==0)
			return false;
	return true;
}
 
int main(int argc,char* argv[],char* envp[])
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int testcnt;
	cin>>testcnt;
	while(testcnt--)
	{
		long long num,div;
		cin>>num>>div;
		long long tmp=num;
		if(num%(div*div))
		{
			cout<<"No";
			goto nextcase;
		}
		while(tmp%div==0)
			tmp/=div;
		if(!is_prime(tmp))
		{
			cout<<"Yes";
			goto nextcase;
		}
		if(num/div/div/div*div*div*div!=num)
		{
			cout<<"No";
			goto nextcase;
		}
		if(is_prime(div))
		{
			cout<<"No";
			goto nextcase;
		}
		for(long long i=2;i*i<=div;i++)
			if(div%i==0&&(i*tmp%div||div/i*tmp%div))
			{
				cout<<"Yes";
				goto nextcase;
			}
		if(num/div/div/div/div*div*div*div*div==num)
		{
			cout<<"Yes";
			goto nextcase;
		}
		cout<<"No";
		nextcase:cout<<'\n';
	}
	return 0;
}
```

---

## 作者：清烛 (赞：0)

题意：给定正整数 $d\ge 2$，给出下面的定义：

- 一个数是*好数*当且仅当其为 $d$ 的倍数。
- 一个数是*美丽数*当且仅当其为*好数*而且其**不能被表示为两个好数的乘积**。

给定一个*好数* $x$，问是否**存在两种或以上方法**，将 $x$ 分解为**若干**个*美丽数*的乘积。多组询问，$t\le 100$，$2\le d\le 10^9$。

~~结合样例~~观察性质：发现一个美丽数 $x$ 一定可以写作 $t\times d$ 的形式，其中 $d\not\mid t$。

而要将 $x$ 分解为若干个美丽数的乘积，相当于 $x = y\times d^k$。

显然 $k = 1$ 的时候是不存在两种或以上的分解方法的，因为只能用 $x = yd$ 来描述。

当 $k = 2$ 时，当 $y$ 不为质数的时候，有解。构造可以考虑 $x = yd\times d$ 和 $x = y_1d\times y_2d$，其中 $y_1y_2 = y$ 且 $y_1,y_2>1$。而 $y$ 不为质数的时候显然没有办法构造两种或以上方案了。

当 $k\ge 3$ 时，当 $y$ 不为质数的时候显然有解。但若 $y$ 为质数，我们还可以考虑将一个 $d$ 拆开并乘到另外若干 $d$ 上面，考虑这种做法的可行性。$d$ 为质数的时候无解，因为没法拆了。但 $d$ 不为质数的情况相对复杂。

发现样例有 `128 4: NO`，思考其原因。$128 = 4\times 4\times 4\times 2$，而将 $4$ 拆开后，我们会发现无论如何都只能构造出 $4\times 4\times 8$。这是为什么？考虑 $x = t^2\times t^2\times t^2\times t$，将 $t^3$ 拆开后我们是只能找到一种方案放置的。而若 $t^2$ 的数量更多，则还是能够存在放置拆开的 $t^3$ 的方案。

所以对于 $k\ge 3$，$y$ 为质数，$d$ 不为质数的情况，只有当 $k=3\land d = t^2$ 时无解，剩余情况都是有解的（总能将一个 $d$ 拆开后分配到别的 $d$ 上）。

判断质数就直接用 $O(\sqrt x)$ 的方法。总时间复杂度 $O(T\sqrt x)$。

```cpp
bool isPrime(int x) {
    for (int i = 2; 1ll * i * i <= x; ++i)
        if (x % i == 0) return false;
    return true;
}

int main() {
    int T; read(T);
    while (T--) {
        int x, d; read(x, d);
        int xx = x, cnt = 0;
        while (!(xx % d)) xx /= d, ++cnt;
        if (cnt == 1) {
            print("No");
        } else if (cnt == 2) {
            //printf("%d ", xx);
            if (isPrime(xx)) print("No");
            else print("Yes");
        } else {
            if (!isPrime(xx)) print("Yes");
            else if (isPrime(d)) print("No");
            else if (d == 1ll * xx * xx && cnt == 3) print("No");
            else print("Yes");
        }
    }
    return output(), 0;
}
```



---

## 作者：JS_TZ_ZHR (赞：0)

## 题意：

给定 $x$ 和 $d$，问是否有两种或以上的方法将 $x$ 表示为一个或多个数的乘积，使得这几个数都是 $d$ 的倍数且不是 $d^2$ 的倍数。两个方案不同当且仅当使用的数的集合不同。

## 题解：

先将 $x$ 表示为 $a\times d^k$ 的形式，其中 $a$ 不是 $d$ 的倍数。然后对于 $k$ 和 $d$ 分类讨论。

$k=1$ 时，显然只有 $x=x$ 这一种方法，无解。

$k=2$ 时，如果 $a$ 是质数或 $1$ 这样不能分解成两个非 $1$ 数的乘积 ,那么也只有 $x=d\times (d\times a)$ 这一种方法。否则令 $a_1a_2=a$ 就可以得到 $x=d\times (d\times a)=(d\times a_1)\times (d\times a_2)$ 两种方案。

$d$ 为质数时，$x$ 就只能分解成 $k$ 个数的乘积。此时情况和 $k=2$ 一样。

如果上述情况不存在且 $k\ge 4$ 时，将 $d$ 表示为 $d=d_1d_2$，那么存在$x=d^{k-1}(d\times a)=d^{k-4}(d\times a)(d\times d_1)(d\times d_2)$ 两种方法。

接下来就是 $k=3$ 的情况。很容易想到 $x=d^{2}(d\times a)=(d\times a\times d_1)(d\times d_2)$ 这个方案，但是当无论如何 $d$ 的非 $1$ 因数与 $a$ 的乘积都是 $d$ 的倍数时这个方案就不行。容易发现只有 $d=p^2=a^2$ 时满足上述条件。至此，所有情况全讨论完了。

## 代码：

```cpp
#include<bits/stdc++.h>
#define N 1000005
#define int long long 
using namespace std;
int T,x,d,cnt,p[N],tot,num;
bool check(int x){
	for(int i=2;i*i<=x;i++){
		if(x%i==0)return 0;
	}
	return 1;
}
bool Check(int x){
	int sum=0;
	for(int i=2;i*i<=x;i++){
		if(x%i==0){
			sum=i;
			break;
		}
	}
	while(x%sum==0)x/=sum,num++;
	return (x==1);
}
signed main(){
	cin>>T;
	while(T--){
		cin>>x>>d;
		cnt=num=0;
		int tmp=x;
		while(tmp%d==0)tmp/=d,cnt++;
	//	cout<<cnt<<' '<<check(d)<<' '<<Check(d)<<endl;
		if(cnt==1){
			puts("NO");
			continue;
		}
		if(check(d)||cnt==2){
			if(tmp==1||check(tmp))puts("NO");
			else puts("YES");
			continue;
		}
		if(Check(d)){
			if(cnt==3){
				if(num==2&&(d%tmp==0&&tmp!=1))puts("NO");
				else puts("YES");
			}
			else puts("YES");
			continue;
		}
		puts("YES");
	}
} 
//8*8*8*2
//
```


---

