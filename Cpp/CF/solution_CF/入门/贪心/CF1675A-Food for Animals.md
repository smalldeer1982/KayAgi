# Food for Animals

## 题目描述

在宠物店出售的商品中有：

- $a$ 包狗粮；

- $b$ 包猫粮；

- $c$ 包通用食物（这种食物既适合狗也适合猫）。

Polycarp 有 $x$ 只狗和 $y$ 只猫。他能从宠物店里为他所有的动物买食物吗？他的每只狗和每只猫都应该得到一包合适的食物。

## 样例 #1

### 输入

```
7
1 1 4 2 3
0 0 0 0 0
5 5 0 4 6
1 1 1 1 1
50000000 50000000 100000000 100000000 100000000
0 0 0 100000000 100000000
1 3 2 2 5```

### 输出

```
YES
YES
NO
YES
YES
NO
NO```

# 题解

## 作者：FFTotoro (赞：4)

观察题目可以发现，我们可以用一种策略——只能喂给猫或狗的食物优先使用，最后不够的看通用食物能不能给剩下的宠物吃即可。

本题要注意特判：只能给某种宠物用的食物即使没用完也不能再用，即注意判断没吃食物的宠物数量不能小于 $0$。

放代码：

```cpp
#include<iostream>
using namespace std;
int main(){
  ios::sync_with_stdio(false);
  int t; cin>>t;
  while(t--){
    int a,b,c,x,y; cin>>a>>b>>c>>x>>y;
    cout<<(max(x-a,0)+max(y-b,0)<=c?"Yes\n":"No\n");
  }
  return 0;
}
```

---

## 作者：ztrztr (赞：3)

## 题目大意
这道题的翻译：

- 有 $a$ 袋狗粮
- 有 $b$ 袋猫粮
- 有 $c$ 袋通用粮

现在有 $x$ 只狗，$y$ 只猫，请问粮食够不够（一只猫动物至少吃一袋粮食）
## 思路
一道贪心题。我们可以优先选一种动物，让他们各吃一份，再轮到下一种动物。这样会避免出现实际是够的，但是一种动物把所有食物都吃光，其他动物没得吃了。
## 实现
1. 输入数据组数。
2. 预计猫够不够吃，如果不够吃，输出```no```，进入下一组。，否则继续计算。
3. 先喂猫吃，让猫吃一份，如果这时狗没吃的，输```no```，进入下一组。
4. 最后如果还没跳走，输出```yes```，结束这一组。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(false);
    int t;
    cin >> t;//输入组数
    while (t--) {
    	int a, b, c, x, y;
    	cin >> a >> b >> c >> x >> y;
    	if (y > (b + c)) {//判断猫够不够吃
    		cout << "NO\n";
    		continue;//到下一组
		}
		if (b >= y) b -= y;//让猫吃
		else c -= (y - b), b = 0;
		if (x > (a + c)) {//如果狗不够吃
			cout << "NO\n";
			continue;//到下一组
		}
		cout << "YES\n";//完美输出
	}
    return 0;
}
```

---

## 作者：happy_dengziyue (赞：1)

### 1 视频题解

![](bilibili:BV1na411J7GD)

### 2 思路

很明显，将所有的粮食买下来最好。

那么，我们先算出，狗粮和猫粮都买完后，剩下的需求缺口，即为 $x-a$ 和 $y-b$。

如果 $x-a>0$，那么代表狗粮有需求缺口，需要填上；猫粮同理。

等到填完需求缺口后，看看通用粮是否为负数。如果通用粮为非负数，证明通用粮能够满足需求；否则不行。

### 3 代码与记录

```cpp
#include<cstdio>
using namespace std;
int t;
long long a;
long long b;
long long c;
long long x;
long long y;
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1675A_1.in","r",stdin);
	freopen("CF1675A_1.out","w",stdout);
	#endif
	scanf("%d",&t);
	while(t--){
		scanf("%lld%lld%lld%lld%lld",&a,&b,&c,&x,&y);
		x-=a;
		y-=b;
		if(x>0)c-=x;
		if(y>0)c-=y;
		if(c>=0)printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/75514136)

By **dengziyue**

---

## 作者：德布劳内yyds (赞：1)

```
#include<bits/stdc++.h>
using namespace std;
 
int t;
 
int main(){
	cin>>t;
	while(t--){
		int a,b,c,x,y;//猫狗优先装独属于自己的袋子
      //多的装入共用袋子
		cin>>a>>b>>c;cin>>x>>y;
		int dog = x<=a?0:x-a;//三目：专用装得下时不有管公用
		int cat = y<=b?0:y-b;
		if(cat+dog<=c) cout<<"YES"<<'\n';
		else cout<<"NO"<<'\n';
	}
	return 0;
}
```


---

## 作者：云裳 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1675A)


这道题还是比较简单的。

解释在代码里。
```cpp
#include<bits/stdc++.h>
#define maxn 100010
typedef long long ll;
using namespace std;
int read() {//快读 
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {
		if(ch=='-') w=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		s=s*10+ch-'0';
		ch=getchar();
	}
	return s*w;
}
void write(int x) {//快输 
	if(x<0) {
		putchar('-');
		x=-x;
	}
	if(x>9) write(x/10);
	putchar(x%10+'0');
}
int main() {
	ll t=read();//共有t组数据 
	while(t--){
		ll a=read(),b=read(),c=read(),x=read(),y=read();//按题意模拟a,b,c,x,y 
		ll m=0;//因为max函数无法将0(int)和long long 比较，故创造这个m 
		if(max(m,x-a)+max(m,y-b)>c) puts("NO");
		//如果x只狗所需的食物-商店有的狗粮+y只猫所需的食物-商店有的猫粮  (还需要补充的猫狗都能吃的粮食 c ) 
		//比猫狗都能吃的粮食( c 本身)还多，那无论如何也无法将猫狗都喂好
		//注意！如果不用max函数会出现负数！用max函数就能避免负数  
		else puts("YES");
	}
	return 0;
}
```

---

## 作者：Engulf (赞：1)

直接膜你即可。

如果专用粮不够吃就加上通用粮判断。

```cpp
// author: TMJYH09
// create time: 2022/05/05 22:42:08
#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int t;cin>>t;
    while(t--){
        int a,b,c,x,y;
        cin>>a>>b>>c>>x>>y;
        if((a>=x)&&(b>=y)){
            cout<<"YES\n";
        }else{
            if(a<x)c-=(x-a);
            if(b<y)c-=(y-b);
            if(c>=0)cout<<"YES\n";
            else cout<<"NO\n";
        }
    }
    return 0;
}
```

---

## 作者：哈士奇憨憨 (赞：0)

## 题目大意
有 $x$ 只狗和 $y$ 只猫，$a$ 包狗粮，$b$ 包猫粮，$c$ 包通用食物（这种食物既适合狗也适合猫）。问能为所有的动物买到食物吗？他的每只狗和每只猫都应该得到一包合适的食物。
## 思路
首先，我们先让 $\min(a, x)$ 条狗吃狗粮，$min(b, y)$ 只猫吃猫粮。如果还有狗和猫没有吃到食物，就让 $c$ 只狗和猫吃通用食物。如果够吃，输出 `yes`，否则输出 `no`。
## CODE
```cpp
#include<bits/stdc++.h>
using namespace std;
int t, a, b, c, x, y;
int main(){
	cin >> t;
	while(t--){
		cin >> a >> b >> c >> x >> y;
		x -= a, y -= b;//a条狗吃狗粮,b只猫吃猫粮
		if(max(0, x) + max(0, y) <= c){
			puts("YES");
		}else{
			puts("NO");
		}
	}	
	return 0;
} 
```

---

## 作者：Tetrahydrofunina (赞：0)

把狗粮全部给狗，猫粮全部给猫。剩下的狗和猫都得吃通用饲料，看通用饲料够不够就行了。

Code(C++)：
```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
	int t,a,b,c,x,y;
	scanf("%d",&t);
	while(t--){
		scanf("%d%d%d%d%d",&a,&b,&c,&x,&y);
		c-=max(x-a,0);
		printf((c<y-b)?"NO\n":"YES\n");
	}
	return 0;
}
```
然后，就：[![](https://www.luogu.com.cn/images/congratulation.png)](https://www.luogu.com.cn/record/75599578)

---

## 作者：zzr1 (赞：0)

#### 题目简述

你现在有 $a$ 袋狗粮，$b$ 袋猫粮，$c$ 袋通用粮食（猫狗都能吃的粮食）。

你现在有 $x$ 只狗，$y$ 只猫，问每只猫狗能不能至少吃到一袋粮食。


------------

#### 题目做法
先不看通用粮食，看看是否能分到每只猫狗 $1$ 袋粮食，也就是看看 $a-x$ 和 $b-y$ 是不是大于 $0$，如果是大于 $0$ 就代表够分。

如果小于 $0$ 的话代表不靠通用粮食不是全部猫狗都能拿到 $1$ 袋粮食。  

这时我们就要去看还差狗粮多少袋，猫粮多少袋，如果狗粮和猫粮还需要的袋数要大于通用粮食，就代表不能全部猫狗都可以拿到 $1$ 袋粮食，如果小于或者等于，就代表全部猫狗都可以至少拿到 $1$ 袋粮食。

##### 注意：此题有多组数据。



------------
AC 代码：

```cpp
#include<iostream>
#include<algorithm>
#include<iomanip>
#include<cstring>
#include<cmath>
#include<cstdio>
using namespace std;
long long a,b,c,x,y,n;
int main(){
	cin>>n;
	while(n--){
		cin>>a>>b>>c>>x>>y;
		x=x-a;//看看如果狗只吃狗粮够不够吃 
		y=y-b;//看看如果猫只吃猫粮够不够吃 
		if(x<=0){//如果够吃 
			x=0;//还需要0袋通用粮食  
		}
		if(y<=0){//如果够吃 
			y=0;//还需要0袋通用粮食 
		}
		//x和y即为需要通用粮食的数量 
		if(x==0&&y==0){//不需要通用粮食了 
			cout<<"YES"<<endl;//记得换行 
		}
		else if(x+y<=c){//如果需要的猫狗粮通用粮食正好可以补上 
			cout<<"YES"<<endl;
		} 
		else{//否则就补不上了 
			cout<<"NO"<<endl;
		} 
	}
	return 0;//好习惯 
}

```



------------
~~谢谢观看。~~



---

## 作者：Failure_Terminator (赞：0)

## Problem

有 $a$ 包狗粮，$b$ 包猫粮和 $c$ 包通用粮食（既适合狗也适合猫）。

Polycarp 有 $x$ 只狗和 $y$ 只猫，问他有没有可能给所有的动物买到食物。

## Solution

首先，我们考虑先把狗粮和猫粮用掉。

如果还不够用，再给还没有食物的动物通用粮食。

在这些操作后，若还不够用，就无法给这些动物足够的食物。

## AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,a,b,c,x,y;
int main() 
{
	cin>>t;
	while(t--){
		cin>>a>>b>>c>>x>>y;
		x=max(x-a,0);y=max(y-b,0);
		if(x==0&&y==0) cout<<"YES\n";
		else if(x+y<=c) cout<<"YES\n";
		else cout<<"NO\n";
	}
    return 0;
}
```

By **haimo**

---

## 作者：iiiiiiiiiiiiiiiiiii (赞：0)

## 题目描述

你有 $a$ 份狗粮、$b$ 份猫粮和 $c$ 份通用粮食（猫和狗都能吃）。每只猫吃一份猫粮或通用粮食，每只狗吃一份狗粮或通用粮食，问你的食物够不够 $x$ 只狗和 $y$ 只猫吃。

## 算法

贪心。猫尽量吃猫粮，狗尽量吃狗粮。先满足狗，如果狗粮够吃，只吃狗粮，否则吃所有的狗粮和通用粮食。如果吃完狗粮后通用粮食还不够，那么无法满足狗的要求，输出 NO。把狗吃剩的给猫吃，同样道理，先吃猫粮，不够吃通用粮食，如果还是不够同样输出 NO。

## 代码

```cpp
#include<algorithm>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iomanip>
#include<iostream>
#include<queue>
#include<string>
#include<vector>
using namespace std;
const int INF=0x3f3f3f3f;
const int N=1e5+10;
const double eps=1e-5;
int read()
{
	char ch=getchar();
	int x=0,f=1;
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-48,ch=getchar();}
	return x*f;
}
int T;
signed main()
{
	T=read();
	while(T--)
	{
		int a=read(),b=read(),c=read(),x=read(),y=read();
		if(a+c<x)
			puts("NO");
		else
		{
			if(x<a)
				a-=x;
			else
				c-=x-a,a=0;
			if(b+c<y)
				puts("NO");
			else
				puts("YES");
		}
	}
	return 0;
}

```


---

## 作者：ryanright (赞：0)

## Description

宠物店里有 $a$ 袋狗粮，$b$ 袋猫粮，$c$ 袋通用粮（狗和猫都能吃）。你有 $x$ 只狗，$y$ 只猫，问是否能够买一些宠物粮满足你所有的宠物们的需求？

## Solution

一开始的时候尽量买专用粮，如果专用粮不够就去取通用粮，看通用粮够不够取。因为猫是吃不了狗粮的，所以我们就把狗粮都给狗吃，这样能够最小化对狗的通用粮供应量。对于猫而言也是一样的。

## Code

```cpp
#include <cstdio>
using namespace std;
int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		int a, b, c, x, y;
		scanf("%d%d%d%d%d", &a, &b, &c, &x, &y);
		if (a < x)//狗粮不够
			c -= x - a;
		if (b < y)//猫粮不够
			c -= y - b;
		puts(c >= 0 ? "YES" : "NO");
	}
	return 0;
}
```

---

## 作者：Kevin0007 (赞：0)

分析：

如果 $x>a$ 且 $y>b$，那么都不需要通用食品就可以喂饱了。

而只要有一个不满足，那么通用食品就要上场了。

如果单纯的狗粮不够，那么多出来的狗就需要用通用食品来喂饱。对于猫亦是如此。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,a,b,c,x,y;
int main(){
  cin>>T;
  while(T--){
    cin>>a>>b>>c>>x>>y;
    x-=a;y-=b;
    if(x<=0&&y<=0) cout<<"YES"<<endl;
    else{
      if(x>0) c-=x;
      if(y>0) c-=y;
      if(c>=0) cout<<"YES"<<endl;
      else cout<<"NO"<<endl;
    }
  }
  return 0;
}
```


---

## 作者：pengzy (赞：0)

### 题意：

对于每一组数据，给定 $a,b,c,x,y$。$a$ 是狗粮的份数，$b$ 是猫粮的份数，$c$ 是两种动物都能吃粮食的份数。现在，Polycarp 有 $x$ 条狗和 $y$ 只猫，每个动物吃一份粮食，问你这些粮食够不够它们吃。

### 思路：

对狗粮和猫粮分别进行判断。狗需要满足狗粮加通用粮足够，猫需要满足猫粮加通用粮足够。同时，因为通用粮虽然能让两种动物同时使用，但是它只能算一次，所以还要看总和够不够。

### 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
inline int read()
{
	int x=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){x=x*10+c-48;c=getchar();}
	return x*f;
}
int T,a,b,c,x,y;
int main()
{
	T=read();
	while(T--) {
		a=read(),b=read(),c=read(),x=read(),y=read();
		if(a+c>=x&&b+c>=y&&a+b+c>=x+y)cout<<"YES"<<endl;
		else cout<<"NO"<<endl;
	}
	return 0;
}
```

---

## 作者：cyrxdzj (赞：0)

### 一、思路

对于每一组数据，如果 $x\le a$ 并且 $y\le b$，那当然是最好的。

但如果此条件不符合，那就看看还需要多少包通用食品。具体方法是，将 $x$ 减去 $a$，将 $y$ 减去 $b$；然后，如果 $max(x,0)+max(y,0)\le c$，则通用食品数量足够。否则为不足够。

### 二、代码

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int t;
int a,b,c,x,y;
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d%d%d%d",&a,&b,&c,&x,&y);
		if(a>=x&&b>=y)
		{
			printf("YES\n");
			continue;
		}
		x-=a;
		y-=b;
		if(max(x,0)+max(y,0)<=c)
		{
			printf("YES\n");
		}
		else
		{
			printf("NO\n");
		}
	}
	return 0;
}

```


---

## 作者：charleshe (赞：0)

题目大意：

某个人有 $x$ 只猫和 $y$ 只狗，每只猫要一份猫粮，每只狗也要一份狗粮。商店有 $a$ 份猫粮，$b$ 份狗粮，还有 $c$ 份既可以当猫粮又可以当狗粮的东西，求这个人能否能让每只猫和每只狗都有粮食。

$t$ 组数据。

数据范围：$1 \leq t \leq 10^4$，$0 \leq a,b,c,x,y \leq 10^8$。

解决方案：

一道性质明显的贪心。

很明显，只能拿来当猫粮或狗粮的东西先拿回去给猫或狗分配了，因为猫粮不能给狗吃，狗粮不能给猫吃。反正题目是问有没有解，因此不用考虑价格（题目也没给啊）。

还剩下一些既能当猫粮又能当狗粮的东西，把它们分配给剩下的猫狗，如果可以分配完就有方案，否则没方案。

接下来解决一个疑问：

Q：为什么先考虑只能当猫粮或狗粮的东西，而不先考虑都能当的？

A：因为只能当猫粮的东西和只能当狗粮的东西，其分配目标是一定的，而都能当的粮食的分配目标是不一定的（可以给猫，也可以给狗），而分配目标一定的粮食只有唯一的归宿（猫粮给猫，狗粮给狗），容易处理，所以先处理一定的，这本质上是一个贪心。

至此思路已经清晰了，但还有几个注意事项：

- 题目多测。

- 需要考虑猫粮（或狗粮）的数量比猫（或狗）的数量多的情况，总不可能有负数只猫还没有粮食吧。

考虑了这些，代码便好写了。

```cpp
#include <iostream>
using namespace std;
int t;
int a,b,c,x,y;
int main(){
	cin>>t;
	while(t--){
		cin>>a>>b>>c>>x>>y;
		x-=a;
		if(x<0) x=0;
		y-=b;
		if(y<0) y=0;//特判粮食比动物多的情况，不然样例都过不去。
		if(x+y<=c) cout<<"YES\n";
		else cout<<"NO\n";
	}
	return 0;
}
```


---

## 作者：SnowTrace (赞：0)

先把需要的猫粮减去现有的猫粮，把需要的狗粮减去现有的狗粮。

然后剩下的和通用粮食比，大于就是不行，小于等于就是可以。

```cpp

#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;
	cin >> t;
	while(t--){
		int a,b,c,d,e,last =0;
		cin >> a >> b >> c >> d >> e;
		d-=a,e-=b;
		last+=max(d,0)+max(e,0);
		if(c>=last)cout << "Yes" << endl;
		else cout << "No" << endl;
		}
}
```


---

## 作者：ZZQF5677 (赞：0)

### 解题思路
直接模拟：既然除了通用粮食外的每种粮食只能给每种动物吃，那干脆就让每种动物把只能给自己吃粮食全部吃光，$x \gets x - a,y \gets y - b$。然后再把没吃到的动物放在一起，共同吃通用粮食看够不够，如果能吃，那剩下没吃到的动物就可以归 $0$ 了。

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int t, a, b, c, x, y;
int main() {
  scanf("%d", &t);
  while (t--) {
    scanf("%d%d%d%d%d", &a, &b, &c, &x, &y);
    bool f = 1;
    x = (x - a <= 0 ? 0 : x - a);
    y = (y - b <= 0 ? 0 : y - b);
    if (x + y <= c) {  //没吃到的动物放在一起，共同吃通用粮食看够不够。
      //如果能吃，那剩下没吃到的动物就可以归 0 了。
      x = 0;
      y = 0;
    }
    if (x > 0 || y > 0) {
      puts("NO");
    } else {
      puts("YES");
    }
  }
  return 0;
}
```

---

## 作者：user470883 (赞：0)

## 思路：
模拟。

翻译的挺好，不难懂，我们按照题意模拟，因为狗食不能给猫吃（同样猫食也不能给狗），所以我们先把“专用食材”给剪掉，算出：还有几个狗没有食吃，还有几个猫没食吃。

然后混着吃的就派上用场了，将没食的狗和没食的猫加在一起，然后看看混合食物能不能喂饱他们。

然后比较一下就行。

**注意事项**：

错了？别走！注意可能狗食大于狗的数量（猫同理），所以可能减出负数出来，然后神奇的最后一加，可能刚刚好小于等于混合食物，当然错了，所以**减出负数时，及时置零**。

## AC CODE:
```

#include<bits/stdc++.h>
using namespace std;

signed main()           
{
	int t;
	cin >> t;
	while(t--)
	{
		int a,b,c,d,e;
		cin >> a >> b >> c >> d >> e;
		d-=a;
		if(d<0)
		{
			d=0;
		}
		e-=b;
		if(e<0)
		{
			e=0;
		}
		if(c>=(d+e))
		{
			cout << "YES" << endl;
		}
		else
		{
			cout << "NO" << endl;
		}
	}
	return 0;
}

```


---

