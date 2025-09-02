# Waste Sorting

## 题目描述

有三个桶，五种垃圾，每个桶有固定的容量。

$1$垃圾放入$1$号桶中，$2$垃圾放入$2$号桶中，$3$垃圾放入$3$号桶中，$4$垃圾可以放入$1$、$3$号桶中，$5$垃圾可以放入$2$、$3$号桶中。

对于给定的桶容量$c$和垃圾量$a$，请问垃圾是否可以全部放入桶中？

## 样例 #1

### 输入

```
7
1 2 3
1 2 3 0 0
2 2 3
1 2 3 1 0
2 2 3
1 2 3 0 1
1 2 5
1 2 3 1 1
0 0 0
0 0 0 0 0
0 0 4
1 0 0 0 0
13 37 42
0 0 0 40 47```

### 输出

```
YES
YES
NO
YES
YES
NO
YES```

# 题解

## 作者：daiarineko (赞：2)

## 0. 题意简述

有三个桶，五种垃圾，每个桶有固定的容量。

前三种垃圾分别放入三种桶中，第四种垃圾可以放进1、3桶中，第五种垃圾可以放进2、3桶中。

问题：对于给定的桶容量和垃圾量，请问垃圾是否可以全部放入桶中？

## 1. 题目分析&主要代码

首先画一下图，分析一下切入点：
![桶与垃圾的关系](https://cdn.luogu.com.cn/upload/image_hosting/qayndkj0.png)

通过图片，我们发现，$1,2,3$ 类垃圾都有固定的放置位置，所以没有任何放置位置的歧义，于是我们首先把 $1,2,3$ 类垃圾处理掉（`c*`为桶，`t*`为垃圾）：
```cpp
c1-=t1;
c2-=t2;
c3-=t3;
```
有些特殊情况，在处理完这几类垃圾后已经放不下了，没必要处理 $4,5$ 类，需要特判：
```cpp
if(c1<0||c2<0||c3<0)return false;
```
接下来处理 $4,5$ 类。

我们重新画一遍图。
![](https://cdn.luogu.com.cn/upload/image_hosting/5irx7cck.png)
灰色指的是有的桶已经占用一部分了。

这次看来，没有任何一种垃圾不会出现歧义，那么可以看桶的分配，发现 $1,2$ 桶只有一种垃圾可以放，所以能放多少放多少：
```cpp
t4-=c1;
t5-=c2;
```
可能还有放不满的情况，这时候如果让 `t4` 和 `t5` 为负数，可能出现一些 $\color{red}bug$，所以特判：
```cpp
if(t4<0)c1=-t4,t4=0
if(t5<0)c2=-t5,t5=0;
```
为什么是 `-t4` 呢？再画一个图（你不怕费高级空间吗）：
![](https://cdn.luogu.com.cn/upload/image_hosting/f9484026.png)
`-t5` 也同理。

再次判定0，如果垃圾已经没了，可以直接结束：
```cpp
if(t4==0&&t5==0)return true;
```

这样，大部分的垃圾已经分配完了，目前 $3$ 桶还没有处理完，所以尝试把剩下的所有 $4,5$ 类垃圾扔进去：
```cpp
if((t4+t5)<=c3)return true;
```

最后，如果不够的话，就相当于放不下：
```cpp
return false;
```

## 2. 完整代码
注意：这段代码跟我的实际代码完全相同，如果直接提交，不保证不会打回评测！
```cpp
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <string>
#include <iostream>
#include <cstring>
using namespace std;
bool do_(){
	int c1,c2,c3,
		t1,t2,t3,
		t4,t5;
	cin>>c1>>c2>>c3
	   >>t1>>t2>>t3>>t4>>t5;
	c1-=t1;
	c2-=t2;
	c3-=t3;
	if(c1<0||c2<0||c3<0)return false;//已经装不下了
	t4-=c1;
	if(t4<0)c1=-t4,t4=0;//先把能扔的扔完
	t5-=c2;
	if(t5<0)c2=-t5,t5=0;//同理
	if(t4<=0&&t5<=0)return true;//只需要c1和c2就可以扔完，那么肯定是yes
	if((t4+t5)<=c3)return true;//否则如果剩下的c3可以扔完，那么也是yes
	return false;
}
int main(){
	int t;
	cin>>t;
	for(int i=0;i<t;++i){
		if(do_()){
			cout<<"YES"<<endl;
		}else{
			cout<<"NO"<<endl;
		}
	}
	return 0;
}
```
## 3. ~~出题人挖坑不埋~~
还是老规矩，**多组数据**！

有特殊情况，**没有垃圾**！

任何类型垃圾个数可以为 $\bold0$！

## 4. 结尾

祝大家Rating++，RP++！

看在我浪费50KB图床空间画图的份上，点个赞吧~~

---

## 作者：So_noSlack (赞：0)

[洛谷链接](https://www.luogu.com.cn/problem/CF1468N)&[CF 链接](http://codeforces.com/problemset/problem/1468/N)

## 题目简述

共有 $T$ 组数据，对于每组数据：

有三个桶，五种垃圾，每个桶有固定的容量。

前三种垃圾分别放入三种桶中，第四种垃圾可以放进 $1,3$ 桶中，第五种垃圾可以放进 $2,3$ 桶中。

问题：对于给定的桶容量和垃圾量，请问垃圾是否可以全部放入桶中？

## 思路

简单贪心题。

贪心思路很简单，首先装 $1,2,3$ 种垃圾，如果此时都装不下直接输出 `NO`，因为这三种垃圾只能装入 $1,2,3$ 号桶。

那么接下来就是处理剩下两种垃圾，发现这两种垃圾都可装入 $3$ 号桶，所以需要优先装 $1,2$ 号桶，装不下之后再装 $3$ 号，如果此时装不下，则输出 `NO`，否则输出 `YES`。

下面是代码实现：

```cpp
#include<iostream>
using namespace std;

int T, a, b, c, d, e, x, y, z; // 垃圾及桶

int main(){
	cin >> T; // 多组数据！
	while(T --) {
		cin >> x >> y >> z;
		cin >> a >> b >> c >> d >> e; // 分别输入垃圾数及桶数
		if(x < a || y < b || z < c) {
			cout << "NO\n"; // 1 2 3 装不下，输出 NO
			continue;
		}
		x -= a, y -= b, z -= c; // 能装下就装
		d -= x, e -= y; // 剩下两种垃圾，分别优先装入 1 2 号桶
		d = max(0, d), e = max(0, e); // 去除负数情况！！
		if(z >= d + e) cout << "YES\n"; // 剩下垃圾能装下
		else cout << "NO\n"; // 装不下
	}
	return 0;
}
```

[提交记录](https://www.luogu.com.cn/record/118628596)

$$\text{The End!}$$

---

## 作者：xxxalq (赞：0)

[洛谷链接](https://www.luogu.com.cn/problem/CF1468N) & [CF链接](http://codeforces.com/problemset/problem/1468/N)

## 思路分析：

这就是一道很贪心题。首先将前三号垃圾扔进对应的垃圾桶，如果此时已经装不下了就表示不合法，直接结束。因为 $4$ 和 $5$ 号垃圾都分别可以放进两个垃圾桶，但是 $3$ 号垃圾桶两种垃圾都能放，所以对于 $4$ 号垃圾先考虑 $1$ 号垃圾桶，$1$ 号垃圾桶不够装了再往 $3$ 号放。同理 $5$ 号垃圾也是一样。

## 代码：

```cpp
#include<iostream>
using namespace std;
int T,c1,c2,c3,a1,a2,a3,a4,a5;
int main(){
	cin>>T;
	while(T--){//T组数据
		cin>>c1>>c2>>c3;
		cin>>a1>>a2>>a3>>a4>>a5;
		c1-=a1,c2-=a2,c3-=a3;//先装1,2,3号
		if(c1<0||c2<0||c3<0){
			cout<<"NO"<<endl;//如果不满足输出NO
			continue;
		}
		if(c1-a4<0){//如果1好垃圾桶装不下4号垃圾
			c3-=a4-c1;
			c1=0;
			//注意这两句的顺序
			//先全部装满，剩下的给3号垃圾桶
		}else{
			c1-=a4;//如果能装下就装
		}
		//a5同理
		if(c2-a5<0){
			//注意顺序
			c3-=a5-c2;
			c2=0;
		}else{
			c2-=a5;
		}
		if(c1<0||c2<0||c3<0){
			cout<<"NO"<<endl;//如果不合法输出NO
			continue;
		}
		cout<<"YES"<<endl;//否则输出YES
	}
	return 0;
}
```

---

## 作者：blsya23a2 (赞：0)

## 分析
首先，$1,2,3$ 号垃圾只能放入对应的桶中，算出放入后每个桶剩下的容量，如果有剩余容量小于 $0$ 的桶就输出 `NO`，否则继续。对于 $4,5$ 号垃圾，先尽量放入 $1,2$ 号桶中，再放入 $3$ 号桶中，这样可以保证最优。如果 $3$ 号桶的剩余容量大于或等于必须放入的垃圾数量，就输出 `YES`，否则输出 `NO`。
## 代码
```python
a=int(input())
for b in range(a):
    c,d,e=map(int,input().split())
    f,g,h,i,j=map(int,input().split())
    c-=f
    d-=g
    e-=h
    if c<0 or d<0 or e<0:
        print('NO')
    else:
        k=0
        if c<i:
            k+=i-c
        if d<j:
            k+=j-d
        if k<=e:
            print('YES')
        else:
            print('NO')
```

---

## 作者：SunsetVoice (赞：0)

更新：修改了公式。

贪心。

首先不难发现第 $1$ 到第 $3$ 这三种垃圾肯定要先放进去（他们只能投一个垃圾桶）。如果对应垃圾桶放不下对应垃圾，输出 $\texttt{NO}$。

如果可以，再来处理第 $4$ 和第 $5$ 种垃圾。

第四种垃圾优先放第 $1$ 个垃圾桶，因为这样可以让出 $3$ 号桶的空间给 $5$ 垃圾。而 $5$ 号同理。实在不行再放 $3$ 号桶。

code：
```cpp
#include<bits/stdc++.h>
using namespace std;
signed main(){
	int a1,a2,a3,b1,b2,b3,b4,b5,T;
	cin>>T;
	while(T--){
		cin>>a1>>a2>>a3>>b1>>b2>>b3>>b4>>b5;
		if(a1<b1 or a2<b2 or a3<b3){
			cout<<"NO"<<endl;
			continue;
		}
		a1-=b1;a2-=b2;a3-=b3;
		//cout<<a1<<" "<<a2<<" "<<a3<<endl;
		if(a1>0){
			b4-=min(b4,a1);
			a1 = 0;
		}
		if(a2>0){
			b5-=min(b5,a2);
			a2 = 0;
		}
		if(a3>=(b4+b5)){
			cout<<"YES"<<endl;
		}else{
			cout<<"NO"<<endl;
		}
	}
	return 0;
}
```


---

## 作者：_Above_the_clouds_ (赞：0)

# 思路：
判断垃圾是否能全部放入桶中。

因为前三种垃圾只能放入一种桶中，所以将三种垃圾放入对应桶中，桶的容量就要减去对应数量，如果桶的容量小于 $0$，说明装不下，就用 $f$ 标记为 $1$。

特判后两种垃圾，如果桶 $1$ 的容量小于 垃圾 $4$ 的数量，那么将桶 $1$ 装满，垃圾 $4$ 的数量就减去桶 $1$ 先前剩下的容量。再判断如果桶 $3$ 的容量小于 垃圾 $4$ 的数量，说明两个桶都装不下，$f$ 标记为 $1$；否则桶 $3$ 的容量减少垃圾 $4$ 的数量。垃圾 $5$ 同理，最后如果 $f$ 为 $1$，输出 $NO$；否则输出 $YES$。

# 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int t;
bool f;
int c[5], a[10];
int main() {
	cin >> t;
	while (t--) {
		f = 0;
		for (int i = 1; i <= 3; i++) cin >> c[i];
		for (int i = 1; i <= 5; i++) cin >> a[i];
		for (int i = 1; i <= 3; i++) {
			c[i] -= a[i];
			if (c[i] < 0) f = 1;
		}
		if (c[1] < a[4]) {
			a[4] -= c[1];
			if (c[3] < a[4]) f = 1;
			else c[3] -= a[4];
		}
		if (c[2] < a[5]) {
			a[5] -= c[2];
			if (c[3] < a[5]) f = 1;
			else c[3] -= a[5];
		}
		if (f) cout << "NO\n";
		else cout << "YES\n";
	}
	return 0;
}

```


---

## 作者：LiuTaifu (赞：0)

## 题目
$1$ 垃圾放入 $1$ 号桶中，$2$ 垃圾放入 $2$ 号桶中，$3$ 垃圾放入 $3$ 号桶中，$4$ 垃圾可以放入 $1$、$3$ 号桶中，$5$ 垃圾可以放入 $2$、$3$ 号桶中。

对于给定的桶容量 ```c``` 和垃圾量 ```a``` ，请问垃圾是否可以全部放入桶中？

## 思路
1. 因为 $1$、$2$、$3$ 号垃圾只能放入 $1$、$2$、$3$ 号桶，所以先将 $1$、$2$、$3$ 号垃圾放入 $1$、$2$、$3$ 号桶。

2. 再将 $1$、$2$、$3$ 号桶中还能装的空间计算出来，根据题意判断 $4$、$5$ 号垃圾能不能再装入桶中。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
	int t;
	cin>>t;
	while(t--) {
		bool f=false;
		int c[4],a[6],k1,k2;
		for(int i=1; i<=3; i++) cin>>c[i];
		for(int i=1; i<=5; i++) cin>>a[i];
		for(int i=1; i<=3; i++) {
			c[i]-=a[i];
			if(c[i]<0) {
				f=true;
				break;
			}
		}
		k1=c[1]+c[3];
		k2=c[2]+c[3];
		if(k1<a[4]) f=true;//如果空间不够，下同
		if(k2<a[5]) f=true;
		if(f==true) {
			f=false;
			printf("NO\n");
			continue;
		}
		printf("YES\n");
	}
	return 0;
}
	
```

## 后言
1. 作者写题解时 ```CF UKE```，没有检测，所以代码~~不能复制~~仅供参考。
2. 蒟蒻第一次写题解，有错误请在评论区指出，不喜轻喷。

---

## 作者：zhouzihe (赞：0)

## 1 观察题目
观察题目，不难发现 $4$ 垃圾和 $5$ 垃圾都可以放进 $3$ 号桶中，所以我们尽量把 $4$ 垃圾和 $5$ 垃圾放进 $1$ 号桶和 $2$ 号桶中，最后判断是否放完即可。
## 2 code
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,c1,c2,c3,a1,a2,a3,a4,a5;
int main(){
	cin>>t;
	while(t--){
		cin>>c1>>c2>>c3>>a1>>a2>>a3>>a4>>a5;
		c1-=a1;
		c2-=a2;
		c3-=a3;
		if(c1<0||c2<0||c3<0){
			cout<<"NO"<<endl;
			continue;
		}
		a4=max(a4-c1,0);
		a5=max(a5-c2,0);
		if(c3>=a4+a5){
			cout<<"YES"<<endl;
		}
		else{
			cout<<"NO"<<endl;
		}
	}
	return 0;
}
```


---

## 作者：lrmlrm_ (赞：0)

## 题意

有三个桶，五种垃圾，每个桶有固定的容量。

 $1$ 垃圾放入 $1$ 号桶中，$2$ 垃圾放入 $2$ 号桶中，$3$ 垃圾放入 $3$ 号桶中，$4$ 垃圾可以放入 $1,3$ 号桶中，$5$ 垃圾可以放入 $2,3$ 号桶中。

对于给定的桶容量 $c$ 和垃圾量 $a$，请问垃圾是否可以全部放入桶中？

## 思路

这道题无非就无解和有解两种情况。

首先，如果 $1$ 号垃圾桶放不下 $1$ 号垃圾（$a_1>c_1$），显然直接无解。同理，$2$ 号垃圾桶放不下 $2$ 号垃圾，$3$ 号垃圾桶放不下 $3$ 号垃圾这两种情况也是无解的。

如果以上的条件都满足，为了接下来的计算，我们分别算出 $1\sim3$ 号垃圾桶目前剩下多大的容量（$c_1\gets c_1-a_1,c_2\gets c_2-a_2,c_3\gets c_3-a_3$）。

接下来考虑 $4$ 号垃圾。如果 $1$ 号垃圾桶剩下的容量加上 $3$ 号垃圾桶剩下的容量都装不下 $4$ 号垃圾（$a_4>c_1+c_3$），显然无解。如果能装下，我们就要尽量把 $4$ 号垃圾放进 $1$ 号垃圾桶里面，放不下才放 $3$ 号垃圾桶（$3$ 号垃圾桶要腾出容量放 $5$ 号垃圾）。这个时候如果 $1$ 号垃圾桶装不下 $4$ 号垃圾，$4$ 号垃圾多出来的就要放进 $3$ 号垃圾桶中；如果装得下，就全部放进 $1$ 号垃圾桶里面。

最后考虑 $5$ 号垃圾。如果 $2$ 号垃圾桶剩下的容量加上 $3$ 号垃圾桶目前剩下的容量都装不下 $5$ 号垃圾（$a_5>c_2+c_3$），就无解。否则肯定有解（能走到这一步，$1\sim4$ 号垃圾肯定都能装下，如果 $5$ 号垃圾也可以装下，说明 $1\sim5$ 号垃圾都可以装下，满足题目要求）。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,c1,c2,c3,a1,a2,a3,a4,a5;
signed main(){
	scanf("%lld",&t);
	while(t--){
		scanf("%lld%lld%lld%lld%lld%lld%lld%lld",&c1,&c2,&c3,&a1,&a2,&a3,&a4,&a5);
		if(a1>c1||a2>c2||a3>c3){
			printf("NO");
			goto loop;
		} 
		c1-=a1,c2-=a2,c3-=a3;
		if(a4>c1+c3){
			printf("NO");
			goto loop;
		}
		if(a4>=c1)a4-=c1,c1=0,c3-=a4;
		if(a5>c2+c3){
			printf("NO");
			goto loop;
		}
		printf("YES");
		loop:
		printf("\n");
	}
	return 0;
} 
```

---

## 作者：Light_az (赞：0)

## 模拟

这个模拟有点抽象，首先我们可以排除这道题目使用 `while`，数据范围那么大，不超时才怪。然后我们可以采用特判的方式来处理每一种垃圾：

- 对于第一，二，三种垃圾，他只能放在 $1,2,3$ 号垃圾桶，如果 $1,2,3$ 号垃圾桶装不下第一，二，三种垃圾，说明无解，输出 `No`。

- 对于第四种垃圾，它可以放在 $1,3$ 号垃圾桶，但是我们要优先选择放在 $1$ 号垃圾桶，因为 $3$ 号垃圾桶也要接第五种垃圾，如果 $1,3$ 号垃圾桶加起来都装不下第四种垃圾，说明无解，输出 `No`。

- 对于第五种垃圾，它可以放在 $2,3$ 号垃圾桶，如果 $2,3$ 号垃圾桶加起来都装不下第四种垃圾，说明无解，输出 `No`，否则输出 `Yes`。

下面是完整代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define Test ios::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr)
#define found __builtin_popcount
using namespace std;
ll n,m,k,x,y,u,v,w,cnt=0,ans=0,t=0,l,r,len,T;
ll mini=INT_MAX,maxi=0,Mod;
string s1,s2;
ll a[10],b[10];

int main(){
	cin>>T;
	while(T--){//多组数据 
		for(int i=1;i<=3;i++) cin>>a[i];
		for(int i=1;i<=5;i++) cin>>b[i];
		if(a[1]<b[1]){//特判 
			cout<<"No"<<endl;
			continue;
		}
		else{//装下第一种垃圾 
			a[1]-=b[1];
			b[1]=0;
		}
		if(a[2]<b[2]){//特判 
			cout<<"No"<<endl;
			continue;
		}
		else{//装下第二种垃圾 
			a[2]-=b[2];
			b[2]=0;
		}
		if(a[3]<b[3]){//特判 
			cout<<"No"<<endl;
			continue;
		}
		else{//装下第三种垃圾 
			a[3]-=b[3];
			b[3]=0;
		}
		if(a[1]+a[3]<b[4]){//加起来也装不下第四种垃圾 
			cout<<"No"<<endl;
			continue;
		}
		if(a[1]<b[4]){//装下第四种垃圾 
			b[4]-=a[1];
			a[3]-=b[4];
		}
		if(a[2]+a[3]<b[5]){//加起来也装不下第五种垃圾 
			cout<<"No"<<endl;
			continue;
		}
		cout<<"Yes"<<endl;//有解 
	}

	return 0;
}


```

最后让我们一起膜拜 [creation_hy](https://www.luogu.com.cn/user/576378) 吧。


---

## 作者：hzoi_liuchang (赞：0)

## 分析
~~最简单的一道题放在最后~~

题目大意：有三个垃圾桶容量分别为 $c_1,c_2,c_3$

有五种类型的垃圾数量分别为 $a_1,a_2,a_3,a_4,a_5$

$a_1$ 只能扔进 $c_1$，$a_2$ 只能扔进 $c_2$，$a_3$ 只能扔进 $c_3$，$a_4$ 能扔进 $c_1$ 和 $c_3$，$a_5$ 能扔进 $c_2$ 和 $c_3$

问所有的垃圾能不能都扔进垃圾桶里

送分题，依次判断每一个条件是否合法即可
## 代码
``` cpp
#include<cstdio>
#include<algorithm>
#define rg register
inline int read(){
	rg int x=0,fh=1;
	rg char ch=getchar();
	while(ch<'0' || ch>'9'){
		if(ch=='-') fh=-1;
		ch=getchar();
	}
	while(ch>='0' && ch<='9'){
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x*fh;
}
const int maxn=16;
int a[maxn],t,c[maxn];
int main(){
	t=read();
	while(t--){
		for(rg int i=1;i<=3;i++) c[i]=read();
		for(rg int i=1;i<=5;i++) a[i]=read();
		rg bool jud=1;
		if(a[1]>c[1] || a[2]>c[2] || a[3]>c[3]) jud=0;
		else if(a[1]+a[2]+a[3]+a[4]+a[5]>c[1]+c[2]+c[3] || a[4]+a[1]+a[3]>c[1]+c[3] || a[5]+a[2]+a[3]>c[2]+c[3]) jud=0;
		if(jud) printf("YES\n");
		else printf("NO\n");
	}
	return 0;	
}
```

---

## 作者：lianchanghua (赞：0)

### 题目大意
三个容器 $c_1$，$c_2$，$c_3$,分别装入五种东西 $a_1$，$a_2$，$a_3$，$a_4$，$a_5$。装法如下：

- $a_1$ 放入 $c_1$ 中，$a_2$ 垃圾放入 $c_2$ 中，$a_3$ 垃圾放入 $c_3$ 中。 
- $4$ 垃圾可以放入 $c_1$，$c_3$ 中，$a_5$ 垃圾可以放入 $c_2$，$c_3$ 中。

### 思路
因为可以放在 $c_3$ 的较多，所以我们在判断 $a_4$ 和 $a_5$ 的去处时要优先考虑 $c_1$ 和 $c_2$ 这样才能保证 $c_3$ 不会被撑满，所以我们可以写出下面代码：
```cpp
if(a4-c1>0)	a4-=c1;
else		a4=0;
if(a5-c2>0)	a5-=c2;
else		a5=0;
```
这样就可以实现：**优先考虑 $c_1$ 和 $c_2$ 保证 $c_3$ 不会被撑满了。**

当然，再减完 $a_1$，$a_2$，$a_3$ 之后，一定要判断一下是否能装，否则直接输出 `No` 进行下一轮的判断。

### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int T;
	cin>>T;
	while(T--){
		int c1,c2,c3;
		cin>>c1>>c2>>c3;
		int a1,a2,a3,a4,a5;
		cin>>a1>>a2>>a3>>a4>>a5;
		c1-=a1;
		c2-=a2;
		c3-=a3;
		if(c1<0||c2<0||c3<0){
			cout<<"No\n";
			continue;
		}
		if(a4-c1>0)	a4-=c1;
		else		a4=0;
		if(a5-c2>0)	a5-=c2;
		else		a5=0;
		if(c3>=a4+a5)	cout<<"Yes\n";
		else			cout<<"No\n";
	}
	return 0;
}
```

---

