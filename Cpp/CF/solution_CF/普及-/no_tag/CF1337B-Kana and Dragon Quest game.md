# Kana and Dragon Quest game

## 题目描述

现在我们有一条龙，它的血量为 $x$ 。

我们有两个技能：雷击和空洞吸收。

雷击：

攻击后使得龙的血量减 $10$ ，也就是说，原来 $h$ 的血量变为了 $h - 10$ 。

空洞吸收：

攻击后使得龙的血量变为：$[\frac{h}{2}]+10$  ，其中 $[h]$ 表示向下取整。

现在要知道是否可以在技能有使用次数的限制下打倒龙。

## 说明/提示

$1 \le T \le 1000$。

$1 \le x \le 10^5$。

$0 \le n,m \le 30 $。

-----------
以下是样例 $1$ 的测试数据 $1$ 的解释：

(以 $L$ 代替 雷击, $V$ 代替 空洞吸收)

操作    || 血量状态

$V \ \ \ \ \ [\frac{100}{2}]+10 =60$

$L \ \ \ \ \ 60-10=50$

$V \ \ \ \ \  [\frac{50}{2}]+10=35$

$V \ \ \ \ \ [\frac {35}{2}]+10=27$

$L \ \ \ \ \ 27-10=17$

$L \ \ \ \ \ 17-10=7$

$L \ \ \ \ \ 7-10=-3$

·Translated by black_trees

## 样例 #1

### 输入

```
7
100 3 4
189 3 4
64 2 3
63 2 3
30 27 7
10 9 1
69117 21 2```

### 输出

```
YES
NO
NO
YES
YES
YES
YES```

# 题解

## 作者：lingfunny (赞：6)

## 题目翻译
有一条$dragon$（龙），生命值是$x$。

$Kana$想要击败这条龙，她总共能够释放两种技能：
- 空洞吸收（百度翻译，只是技能名字别太纠结），能把龙原来的生命值$h$降到$h\div 2+10$（$h\div2$下取整）。
- 雷击（英语憨憨靠百度翻译过日子），能把龙的生命值降低$10$，比如原来生命值是$h$，使用过雷击后，龙的生命值变成$h-10$。

出于某种原因，$Kana$只能使用不超过$n$次空洞吸收和$m$次雷击（技能可以不放完）。请你告诉$Kana$她能否打败这条龙。如果能，请输出```Yes```，否则输出```NO```。
## 题目分析
简单模拟。只需要每次挑选性价比最高的那个技能释放就好了。~~（怎么感觉有点像贪心）~~

首先很明显，在血量较高的情况下，空洞吸收肯定比雷击性价比高。但是到了某个血量$k$时，空洞吸收就不再能降低龙的血量了，果断选择雷击。

假设龙的生命值在$k$的时候空洞吸收就不降低血量，可以得到$k-(k\div2+10)=0$，不难算出$k=20$。接下来**万事大吉**。
## AC代码
```cpp
#include <iostream>
using namespace std;
int t,x,n,m;
int main(){
	cin>>t;
	while(t--){
		x=n=m=0;
		cin>>x>>n>>m;
		while(x>=20 && n--)x=x/2+10;	//满足性价比值k 同时n还不为0
		while(x>0 && m--)x-=10;			//还活着同时m还不为0
		if(x<=0)cout<<"YES";			//没血输出yes
		else cout<<"NO";				//否则输出no
		cout<<"\n";
	}
	return 0;
}

---

## 作者：huayucaiji (赞：3)

~~那个switch好珂爱~~

首先，我们要考虑贪心，但有一个问题：因为一技能 $\lfloor \frac{h}{2}\rfloor+10$ 有可能会使得龙的血量变大，那么什么时候采用第一种会使龙的血量增加呢？

~~Q:不就是不等式吗，小学三年级都会做，说的那么玄乎~~  
~~A:你说的没错~~

我们来列个不等式看看：  
$$\lfloor \frac{h}{2}\rfloor+10\geq h$$  
$$\lceil \frac{h}{2}\rceil\leq 10$$  
$$h\leq 20$$

所以我们就知道，如果 $h\leq 20$，就只能用第二种技能，否则龙的血量会增加。一个贪心地思路就出现了：  
1.我们先尽量使用一技能，直到 $h\leq 20$ 或一技能 $n$ 次用完了，在等时间为 $∞$ 的CD。  
2.我们一直用二技能，直到 $h\leq 0$ 或二技能 $m$ 次用完了，在等时间同样为 $∞$ 的CD。  
3.如果 $h\leq 0$，输出 YES，否则 NO。（由于题目说 YES，NO 大小写随意，所以代码会有点不正常（滑稽））

总结这道题，是一个不等式的小应用，同时用贪心辅助即可，作为CF的div2 B还是很合适的~

还有注意：

### 多组数据！！！

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

int read() {
	char ch=getchar();
	int f=1,x=0;
	while(ch<'0'||ch>'9') {
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		x=x*10+ch-'0';
		ch=getchar();
	}
	return f*x;
}

int n,x,m;

signed main() {
	int t;
	t=read();
	while(t--) {
		x=read();
		n=read();
		m=read();
		while(n&&x>20) {
			x=x/2+10;
			n--;
		}
		if(m*10>=x) {
			printf("YeS\n");//这里
		}
		else{
			printf("nO\n");//这里
		}
	}
	return 0;
}


```

---

## 作者：Aw顿顿 (赞：2)

[Blog](https://www.luogu.com.cn/blog/AlanWalkerWilson/)

其实可以直接模拟。

我们可以知道，第二个技能当 $x<20$ 的时候回导致对面加血。

我们还知道，第一个技能要尽可能用完。

所以可以得出贪心的策略：

```cpp
#include<bits/stdc++.h>
using namespace std;
int hp,l,v,s;
int main(){
    cin>>hp;
    for(int i=1;i<=hp;i++){
        cin>>l>>v>>s;
        while(l>20&&v>0){
            l=(l>>1)+10;
            --v;
        }if(l<=s*10)puts("YES");
        else puts("NO");
    }return 0;
}
```

当然可以使用快读进一步卡常：

```cpp
inline char g(){
    static char buf[100000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
}inline int read(){
    char c=g();int s=0;
    while(!isdigit(c))c=g();
    while(isdigit(c))s=s*10+c-48,c=g();
    return s;
}
```

提交记录：https://www.luogu.com.cn/record/32860382

快读来自：https://www.luogu.com.cn/paste/0kez7qrf

---

## 作者：Hexarhy (赞：2)

### Preface

这题还是很良心的，给出题人点个赞。一道简单送分的题，难度红橙。

### Solution

一种另类的解法。

每次都只有两种选择，我们就可以进行递推。

设 $F_{i,j}$ 为使用了 $i$ 次`Absorption`，$j$ 次`Lightning Strike`后龙的生命值。递推式就枚举选择哪一个即可。

$$F_{i,j}=\min\{\lfloor\dfrac{F_{i-1,j}}{2}\rfloor+10,F_{i,j-1}-10\}$$

只要有任意时刻 $F_{i,j}\le 0$ 我们就可以判断 `YES`。否则用完了都始终 $F_{i,j}> 0$，判断为`NO`。

注意一下边界，也就是当 $i$ 或 $j$ 为 $0$ 的时候，就有

$$F_{i,0}=\lfloor\dfrac{F_{i-1,0}}{2}\rfloor+10$$

$$F_{0,i}=F_{0,i-1}-10$$

别忘了 $F_{0,0}=x$。

时间复杂度 $\Theta(Tnm)$。

### Another One

显然可以贪心。

若当前的 $x$ 越大，第一种操作的收益就越多。我们就可以贪心。

每次只使用第一种操作，直到当前的 $x\le 10$，我们就可以用第二种操作直接完成。

如果用完了第一种操作都没有使 $x\le 10$，或者当 $x\le10$ 的时候第二种操作用完了，结果就是 `NO`。

时间复杂度 $O(Tn)$，优于刚才的递推。

不过作为送分题，$n,m,T$ 都很小，想到哪种算法就用哪种。

### Notice

递推完是不是判断 $F_{n,m}\le 0$，因为第一种操作的 $+10$ 可能会使本来小于 $0$ 的 $F_{n,m}$ 变大。因此需要遍历全部的 $F$，只要有任意的 $F_{i,j}<0$ 即可判断`YES`。

然后就没有其它坑点了，别把 $n,m$ 弄反了。

### Code

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;

const int MAXN=35;
int x,n,m;
int f[MAXN][MAXN];

bool solve(void)
{
	f[0][0]=x;
	for(int i=1;i<=n;i++)	f[i][0]=f[i-1][0]/2+10;
	for(int i=1;i<=m;i++)	f[0][i]=f[0][i-1]-10;//处理边界
	for(int i=1;i<=n;i++)
	 for(int j=1;j<=m;j++)
	  f[i][j]=min(f[i-1][j]/2+10,f[i][j-1]-10);//根据题意递推
	for(int i=0;i<=n;i++)
	 for(int j=0;j<=m;j++)
	  if(f[i][j]<=0)//任意一个小于0即可为YES
	   return true;
	return false; 
}

int main()
{
    ios_base::sync_with_stdio(false);
    int T;cin>>T;
    while(T--)
    {
    	cin>>x>>n>>m;
    	cout<<(solve()?"YES":"NO")<<endl;
	}
	return 0;
}
```

---

## 作者：风人 (赞：2)

+ 当你看到我的时候就知道这是道水题


# [CF1337](https://www.luogu.com.cn/problem/CF1337B) 题解

### 一、题意：

有一条龙，生命值是x。

Kana想要击败这条龙，她总共能够释放两种技能：

空洞（h/2+10）、雷击（h−10）。
出于某种原因，Kana只能使用不超过n次空洞吸收和m次雷击。请你告诉Kana她能否打败这条龙。如果能，请输出Yes，否则输出NO。

### 二、提示


关于 “[  ]”，题意说是四舍五入，这里有误，应是向下取整。

### 三、思路

很多人是每一次都判断用哪一个攻击方式合适，一种类似贪心做法，但我觉得没有必要，因为雷击是常数级攻击（无关HP），而空洞是线性攻击（有关HP且HP越高攻击越大），因此先进行空洞再雷击是正解。

但是空洞也有一定范围，我们用一手小学二年级学过的方法 $ (h/2) + 10 \le h $ ，很容易得在$ 20 \le h $ 时空洞攻击是有效地，那么待$ HP \le 20 $ 或次数用完后一次使用完雷击看最后生命值，比零大就“NO”，小（等于）就“YES”。
所以在这一部分，我们有

```
while (n-- && x > 10) x = floor(x / 2) + 10;
```

这段话就是空洞攻击还有次数，并且HP比二十大，此时选择空洞攻击就是有效地，所以我们一次把空洞用完。

下来就应当使用雷击了，我们可以根据剩余HP判断攻击次数，但实际上我们仍然一次用完雷击就看，最后判断HP与0比较即可，据此写下了

```
x -= (m * 10)
```
判断x即可

### 四、完整代码


```cpp
#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;
int T, x, n, m;
int main() {
  cin >> T;
  while (T--) {
    cin >> x >> n >> m;
    while (n-- && x > 10) x = floor(x / 2) + 10;
    x -= (m * 10);
    if (x > 0)
      cout << "NO" << endl;
    else
      cout << "YES" << endl;
  }
}
```


---

## 作者：xiezihan (赞：1)

转了一圈，又没有**C语言**的，~~水一波~~


------------

这道题的意思：

有一条龙，生命值是x，Kana想要击败这条龙，她总共能够释放两种技能

一技能 ~~（名字过于中二已隐藏）~~ ：能把龙原来的生命值打到h/2+10

二技能 ~~（名字过于中二已隐藏）~~ ：能把龙的生命值降低10

如果Kana能打过小龙龙，就输出YES,不然输出NO



------------
输出性价比最高的就好了，真的也没什么了

上AC代码



------------
```c
#include<stdio.h>
int main()
{
	int t,x,n,m;
	scanf("%d",&t);
	while(t--)
	{
		x=0;
		n=0;
		m=0;
		scanf("%d%d%d",&x,&n,&m);
		while(x>=20&&n)
		{
			n--;
			x=x/2+10;
		}
		while(x>0&&m)
		{
			m--;
			x-=10;
		}
		if(x<=0)printf("YES");
		else printf("NO");
		printf("\n");
	}
	return 0;
}
```

[AC记录](https://www.luogu.com.cn/record/34146677)

---

## 作者：Warriors_Cat (赞：1)

### $Description:$

给你 $n$ 次 $A$ 操作和 $m$ 次 $B$ 操作，$A$ 操作是把 $x$ 变为 $\left[\dfrac{x}{2}\right]+10$，$B$ 操作是把 $x$ 变为 $x-10$，问可以不可以经过这些操作后把 $x$ 变为非负数，不用所有操作都要进行。

### $Solution:$

考虑贪心。

因为当 $x \le  20$ 时，$A$ 操作反而更劣，所以我们在 $x > 20$ 时一直进行 $A$ 操作，直到 $n=0$ 为止。

接着全部进行 $B$ 操作，最后判断 $x$ 是否为非负数即可。

### $Code:$

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
int t, x, n, m;
int main(){
	scanf("%d", &t);
	while(t--){
		scanf("%d%d%d", &x, &n, &m);
		bool flag = 0;
		while(x > 20 && n){
			x = x / 2 + 10;
			n--; 
		}//先进行 A 操作
		if(x - m * 10 <= 0) puts("YES");//直接判断即可
		else puts("NO");
	}
	return 0;
}
```


---

## 作者：Doubeecat (赞：1)

## 题意
敌人有 $x$ 点血量，你有两种操作，分别可以使用 $n,m$ 次，可以不按照顺序。  
1. 令 $x = [\frac{x}{2}]+10$
2. 令 $x = x -10$    

求是否能击杀敌人。

## 思路
贪心。  
如果第一个操作没有这个 +10，我们的第一想法肯定是  
当 $x > 10$ 时，不断令 $x = [\frac{x}{2}]$，因为到 10 以下，选择 1 操作的性价比就没有 2 高了   
当 $x \leq 10$ 时，使用一次 2 操作。  
那么这里有了 +10 要怎么做呢？  
我们会发现，在某个值以下，再使用 1 操作就不会改变值，甚至会让值变得更大！而这个临界点也很好算 $x = 20$  
所以只要当 $x > 20$ 时，不断令 $x = [\frac{x}{2}]+10$  
当 $x \leq 20$ 时，不断令 $x = x - 10$  
代码就不难写了。

## 代码
```cpp
#include <cstdio>
#include <cctype>

inline int read() {
	char v = getchar();int x = 0,f = 1;
	while (!isdigit(v)) {if (v == '-')f = -1;v = getchar();}
	while (isdigit(v)) {x = x * 10 + v - 48;v = getchar();}
	return x * f;
}

int main() {
	int T = read();
	while (T--) {
		int a = read(),b = read(),c = read(),lb = b,lc = c;
		for (int i = 1;i <= b+c;++i) {
			if (a >= 20 && lb) {
				a /= 2;a += 10;
				lb--;
			}
			else if (lc){
				a -= 10;
				lc--;
			}
		}
		if (a <= 0) puts("YES");
		else puts("NO");
	}
	return 0;
}
```

---

## 作者：BFqwq (赞：1)

一个简单的小模拟，因为我们看到数字很大的时候先用除以二的操作会使减小的比较快，因此我们只需要不断除以二，然后在中间顺便判断一下能否在某一时刻用减十降到 $0$ 即可。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	register int x=0;
	register bool f=0;
	register char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=(x<<3)+(x<<1)+c-48;
		c=getchar();
	}
	return f?-x:x;
}
char cr[200],str[200];int tt;
inline void print(int x,char k='\n') {
    if(!x) putchar('0');
    while(x) cr[++tt]=x%10+'0',x/=10;
    while(tt) putchar(cr[tt--]);
    putchar(k);
}
int n,m;
signed main(){
	int T=read();
	while(T--){
		int sum=read();n=read();m=read();
		int tot=m*10;bool f=0;
		if(sum<=tot) f=1;
		while(n){
			sum=sum/2+10;
			if(sum<=tot) f=1;
			n--;
		}
		puts(f?"Yes":"No");
	}
	return 0;
}
```


---

## 作者：Trafford1894 (赞：0)

## 这是一道模拟水题。

### $Problem$

我们有两个技能：雷击和空洞吸收。

假设龙的血量为$x$

雷击：
攻击后使得龙的血量变为$x - 10$

空洞吸收：
攻击后使得龙的血量变为$[\dfrac{x}{2}] + 10$

现在要知道是否可以在技能有使用次数的限制下打倒龙。

### $Solution$

在血量多的时候我们会使用空洞吸收，这种方式攻击力强。

但假设当龙的血量为$k$时，$[\dfrac{k}{2}] + 10 >= k$

解不等式得$k <= 20$

所以，在$k < 20$时，我们要用雷击。

### $Code$

```cpp


#include <iostream>

using namespace std;

int _maxi;
int _hp;
int _n;
int _m;

int main () {
	
	cin >> _maxi;
	
	while (_maxi > 0) {
	    _maxi--;
		cin >> _hp >> _n >> _m;
		
		while (_n > 0 && _hp > 20) {
			_hp = _hp / 2 + 10;
			_n--;//use all the Void AbsorptionAssume
		}
		
        //check that the dragen will die or not
		if (_m * 10 < _hp) {
			cout << "NO\n";
			continue;
		}
		
		cout << "YES\n";
	}
	
	return 0;
}
```

### 感谢管理员大佬们的审阅！


---

## 作者：VenusM1nT (赞：0)

模拟。  
（这技能名……我佛了，谷歌翻译把 Lightning Strike 翻译成 惊雷 哈哈哈哈）  
先考虑 Void Absorption，对伤害的贡献为 $n-\lfloor \frac{n}{2}\rfloor-10$，后面这个 $-10$ 是负贡献，而 Lightning Strike 正好可以贡献 $10$ 的伤害，所以只要 Void Absorption 对伤害有贡献，即 $n-\lfloor \frac{n}{2}\rfloor>10$ 就狂用，最后看看用 Lightning Strike 能不能收尾就可以了。

---

## 作者：绝尘影_Sheldow (赞：0)

首先祝贺自己在 $\texttt{Codeforces}$ 参加的第一场比赛！

步入正题。题目要求我们由给定的龙的生命值和两种技能的最大使用次数计算是否能击败龙。

首先考虑“空洞吸收”技能（以下简称一技能）：使龙减少一半的血量再恢复 $10$ 点血量。由此容易推出：只有龙的一半的血量高于 $10$，即总的剩余血量高于 $20$ 时，这个技能才能发挥出正面作用。

【同时只有血量高于 $40$ 时，效率才会高于“雷击”（以下简称二技能）——但这并不影响顺序】

然后考虑二技能：它的释放时机为所有的一技能已经消耗殆尽或一技能无法取得正收益时。同时因为它的伤害是固定的，所以可以直接将龙的剩余血量同所有二技能能够造成的最大伤害（即二技能个数 $\times 10$）作比较。

这个思路本质上还是贪心，但它有的时候并不能获得最优解（比如样例 $1$ 的测试数据 $1$ ，按照题目解释能造成 $103$ 点伤害，但本思路只有 $100$ 点）。但因为本题只是要求简单地输出是否，所以也可以通过，即本思路也同样是本题的一个合法解。（事实上，在本题中使用这个思路能在确保正确性的同时尽量节省时间和空间。）

（引申：所以如果要求计算最大伤害或最少次数，正解其实是 $\texttt{DP}$。）

解释得已经够多了，上代码：

```cpp
#include<iostream>
#include<cmath>
#include<string>
#include<algorithm>
#include<cstdio>
#include<cstring>
using namespace std;
int main()
{
	int t,x,n,m;
	cin>>t;
	for(int i=1;i<=t;i++)
	{
		cin>>x>>n>>m;
		while(x>20&&n>0)	\\重复使用一技能，直到用尽或者无法继续取得正收益
		{
			x/=2;	\\利用了c++的整除时自动下取整
			x+=10;
			n--;
		}
		if(m*10>=x)	\\不再循环，直接将二技能的伤害和剩余血量进行比较
		{
			cout<<"YES";
		}
		else
		{
			cout<<"NO";
		}
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：Sora1336 (赞：0)

对于这道题，我们可以简化为：

kana要打败恶龙，恶龙有h点血。

Kana有两种法术：

1. V法术——使龙的血量变成$[\frac{h}{2}]+10$（[ ]代表向上取整）。
2. L法术——使龙的血量变成$h-10$。

给你龙的血量和使用V法术和L法术的最大次数，问可爱的kana能否杀死恶龙。

战略：

使用尽可能多的V法术，但是不至于让恶龙回血。比如这个：

恶龙10点血。代入$[\frac{h}{2}]+10$中得龙的血量变成15.

这是绝对不行的。

最后使用完L法术，看能不能把龙打死，如果能，输出“YES”；如果不能，输出“NO”。

AC代码：
```
#include <iostream>
using namespace std;
int main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		int h,v,l;
		cin>>h>>v>>l;
		while((((h/2)+10)<=h)&&(v!=0)){		//使用尽可能多的V法术，但是不至于让恶龙回血。其中((h/2)+10)<=h是来判断是否会给恶龙回血的。
			h/=2;
			h+=10;
			v--;			//使用V法术
		}if((l*10)>=h){			//最后使用完L法术，看能不能把龙打死
			cout<<"YES"<<endl;
		}else{
			cout<<"NO"<<endl;
		}
	}
}
```


---

