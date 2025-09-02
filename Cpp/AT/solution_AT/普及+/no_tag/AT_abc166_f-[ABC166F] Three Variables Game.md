# [ABC166F] Three Variables Game

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc166/tasks/abc166_f

あるゲームでは $ 3 $ つの変数があり、それぞれ $ A,B,C $ で表されます。

ゲームの進行と共に、あなたは $ N $ 回の選択に迫られます。 それぞれの選択は文字列 $ s_i $ によって示され、 $ s_i $ が `AB` のとき、$ A $ と $ B $ のどちらかに $ 1 $ を足しもう一方から $ 1 $ を引くこと、 `AC` のとき、$ A $ と $ C $ のどちらかに $ 1 $ を足しもう一方から $ 1 $ を引くこと、 `BC` のとき、$ B $ と $ C $ のどちらかに $ 1 $ を足しもう一方から $ 1 $ を引くことを意味します。

いずれの選択の後にも、$ A,B,C $ のいずれも負の値になってはいけません。

この条件を満たしつつ $ N $ 回すべての選択を終えることが可能であるか判定し、可能であるならそのような選択方法をひとつ示してください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 10^5 $
- $ 0\ \leq\ A,B,C\ \leq\ 10^9 $
- $ N,\ A,\ B,\ C $ は整数である。
- $ s_i $ は `AB`, `AC`, `BC` のいずれか

### Sample Explanation 1

次のようにすることで $ 2 $ 回すべての選択を終えることができます。 - $ 1 $ 回目の選択では、$ A $ に $ 1 $ を足し $ B $ から $ 1 $ を引く。$ A $ の値が $ 2 $ に、$ B $ の値が $ 2 $ に変化する。 - $ 2 $ 回目の選択では、$ C $ に $ 1 $ を足し $ A $ から $ 1 $ を引く。$ C $ の値が $ 1 $ に、$ A $ の値が $ 1 $ に変化する。

## 样例 #1

### 输入

```
2 1 3 0
AB
AC```

### 输出

```
Yes
A
C```

## 样例 #2

### 输入

```
3 1 0 0
AB
BC
AB```

### 输出

```
No```

## 样例 #3

### 输入

```
1 0 9 0
AC```

### 输出

```
No```

## 样例 #4

### 输入

```
8 6 9 1
AC
BC
AB
BC
AC
BC
AB
AB```

### 输出

```
Yes
C
B
B
C
C
B
A
A```

# 题解

## 作者：irris (赞：6)

> 搜索 / dp / 分类讨论 / 剪枝 / corner case

$*1800$，$7$，很牛的题。

## Solution

除非初始操作了两个 $0$，否则我们发现当 $a + b + c \geq 3$ 时，答案一定为 `Yes`。为了证明这个，我们只要为初始 $a = b = c = 1$ 设计一个合法的策略即可。而这是容易的：进一步，我们只要每次都不存在两个 $0$ 即可。我们将 $a, b, c$ 无序化考虑，那么：

- 对于局面 $\lang 1, 1, 1\rang$，随便进行一次操作，总会得到 $\lang 2, 1, 0\rang$。
- 对于局面 $\lang 2, 1, 0\rang$，如果选择 $(2, 1)$ 或 $(1, 0)$，我们依旧转化为 $\lang 2, 1, 0\rang$；如果选择 $(2, 0)$，转化为 $\lang 1, 1, 1\rang$。

对于 $a + b + c = 0$，显然为 `No`；对于 $a + b + c = 1$，听天由命。

因此问题转化为 $a + b + c = 2$。这个时候我们要尽可能每次避免 $\lang 2, 0, 0\rang$ 时操作 $0, 0$ 的情况，因此每次 $\lang 1, 1, 0\rang$ 时，假设下一次操作是 $(1, 1)$，我们就需要看下面的第二次操作，如果和这一次操作不同，就需要把 $2$ 放到一个恰当的位置，那么就能再回到 $\lang 1, 1, 0\rang$。因此这时我们还是在「除非初始操作了两个 $0$」的时候一定为 `Yes`。

## Code

代码很难写，我不想分类讨论！我不想 CV！我不想实现上面的 akjfdhkqoiudwhbwhyrodcsihjasbkjhdlpqewouyjnmasdqq！怎么办？

**下面我们证明搜索算法的实际时间复杂度为 $\bm{\mathcal O(n)}$**。参考代码实现见下。

首先，「除非初始操作了两个 $0$」的情况，显然执行 `dfs` 的次数是 $1$。

其次，假如我们的程序很笨比，在一个 `Yes` 的过程中操作了两个 $0$，那么显然的是其中一个 $0$ 一定是上一次操作产生的，**我们只要回退一步就可以接着走下去，并且这次并不会接着产生第二个 $\bm 0$（因为显然这里是 $\bm{1, 0}$ 互换）**，因此每一步最多被回溯一次。因此时间复杂度是 $\mathcal O(n)$ 的。

```cpp
#include <bits/stdc++.h>

#define MAXN 100001
std::string S[MAXN];
char t[MAXN]; int N;
void dfs(int a, int b, int c, int n = 1) {
	if (n == N + 1) {
		std::cout << "Yes\n";
		for (int i = 1; i <= N; ++i) std::cout << char(t[i] ^ 32) << '\n';
		exit(0);
	}
	if (S[n] == "AB") {
		if (a > 0) t[n] = 'b', dfs(a - 1, b + 1, c, n + 1);
		if (b > 0) t[n] = 'a', dfs(a + 1, b - 1, c, n + 1);
	} if (S[n] == "AC") {
		if (a > 0) t[n] = 'c', dfs(a - 1, b, c + 1, n + 1);
		if (c > 0) t[n] = 'a', dfs(a + 1, b, c - 1, n + 1);
	} if (S[n] == "BC") {
		if (b > 0) t[n] = 'c', dfs(a, b - 1, c + 1, n + 1);
		if (c > 0) t[n] = 'b', dfs(a, b + 1, c - 1, n + 1);
	}
}

int main() {
	int a, b, c; std::cin >> N >> a >> b >> c;
	for (int i = 1; i <= N; ++i) std::cin >> S[i];
	return dfs(a, b, c), std::cout << "No\n", 0;
}
```

---

## 作者：feecle6418 (赞：4)

~~这次 ABC 难度太不均匀了，差评~~

这是一篇纯贪心的题解！

首先，设 $c$ 为开始三个数中，非零数个数的个数。若 $c\ge 2$，则易证一定有解。若 $c=1$，我们看 $A+B+C$ 的取值：若 $\ge 2$，则只需特判第一次操作有无解，即转化为了 $c=2$ 的情况。否则 $A,B,C$ 中仅有一个为 $1$，直接贪心即可。

在 $c\ge 2$ 时怎么做？有一个显然的贪心：每次选择较小的加，较大的减。可是这样在 $A=B>0$ 时，操作 $AB$ 会出问题，因为你不知道应该加哪一个。怎么办呢？考虑下一次操作。若下一次操作为 $AC$，显然让 $A$ 加一更好，因为这样保证了下一次操作的正确性；下一次操作中有 $B$，显然让 $B$ 加一更好，理由同上。若下一次为 $AB$，那么我们在这次让 $A$ 减一 $B$ 加一，下一次再来判断也不迟（可以按照 $i\bmod 2$ 分类），这样也一定能保证不会无解。

其他两种情况，旋转一下就好。

代码：

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cassert>
using namespace std;
typedef long long ll;
int n,A,B,C,P=1;
char str[5],ans[100005];
char ss[100005][5];
void SolveRR() {
	for(int i=P; i<=n; i++) {
		scanf("%s",ss[i]);
	}
	for(int i=P; i<=n; i++) {
		if(ss[i][0]=='A'&&ss[i][1]=='B') {
			if(max(A,B)<=0)return puts("No"),void();
			if(A==0)ans[i]='A',A++,B--;
			else if(B==0)ans[i]='B',B++,A--;
			else if(i==n||(ss[i+1][0]=='A'&&ss[i+1][1]=='B')){
				if(i%2==0)ans[i]='A',A++,B--;
				else ans[i]='B',A--,B++;
			}
			else if(ss[i+1][0]=='A')ans[i]='A',B--,A++;
			else ans[i]='B',A--,B++;
		}
		if(ss[i][0]=='A'&&ss[i][1]=='C') {
			if(max(A,C)<=0)return puts("No"),void();
			if(A==0)ans[i]='A',A++,C--;
			else if(C==0)ans[i]='C',C++,A--;
			else if(i==n||(ss[i+1][0]=='A'&&ss[i+1][1]=='C')){
				if(i%2==0)ans[i]='A',A++,C--;
				else ans[i]='C',A--,C++;
			}
			else if(ss[i+1][0]=='A')ans[i]='A',C--,A++;
			else ans[i]='C',A--,C++;
		}
		if(ss[i][0]=='B'&&ss[i][1]=='C') {
			if(max(B,C)<=0)return puts("No"),void();
			if(B==0)ans[i]='B',B++,C--;
			else if(C==0)ans[i]='C',C++,B--;
			else if(i==n||(ss[i+1][0]=='B'&&ss[i+1][1]=='C')){
				if(i%2==0)ans[i]='B',B++,C--;
				else ans[i]='C',B--,C++;
			}
			else if(ss[i+1][0]=='B'||ss[i+1][1]=='B')ans[i]='B',C--,B++;
			else ans[i]='C',B--,C++;
		}
	}
	puts("Yes");
	for(int i=1; i<=n; i++)cout<<ans[i]<<'\n';
}
int main() {
	cin>>n>>A>>B>>C;
	int cnt=0;
	if(A)cnt++;
	if(B)cnt++;
	if(C)cnt++;
	if(cnt>1) {
		SolveRR();
		return 0;
	}
	if(!cnt)return puts("No"),0;
	scanf("%s",str);
	if(str[0]=='A'&&str[1]=='B') {
		if(max(A,B)<=0)return puts("No"),0;
		if(A<B)ans[1]='A',A++,B--;
		else ans[1]='B',B++,A--;
	}
	if(str[0]=='A'&&str[1]=='C') {
		if(max(A,C)<=0)return puts("No"),0;
		if(A<C)ans[1]='A',A++,C--;
		else ans[1]='C',C++,A--;
	} 
	if(str[0]=='B'&&str[1]=='C') {
		if(max(B,C)<=0)return puts("No"),0;
		if(B<C)ans[1]='B',B++,C--;
		else ans[1]='C',C++,B--;
	}
	P=2;
	SolveRR();
}
```

---

## 作者：BqtMtsZDnlpsT (赞：4)

[传送门](https://www.luogu.com.cn/problem/AT5239)

ABC 的 F 题，伪了好几发才过，at 上难度评级：$1668$。

相信大家都已经发现了一个贪心的做法：每次大的减，小的加。

核心代码：

```cpp
if(k[i]=="AB"){
	if(a>b)--a,++b,ans[i]='B';
	else --b,++a,ans[i]='A';
}
else if(k[i]=="AC"){
	if(a>c)--a,++c,ans[i]='C';
	else --c,++a,ans[i]='A';
}
else{
	if(b>c)--b,++c,ans[i]='C';
	else --c,++b,ans[i]='B';
}
if(a<0||b<0||c<0){puts("No");return 0;}
```

但是有一个显然的漏洞，如果你的两个数相等且都为 $1$，另一个数为 $0$，如果当前先要在两个 $1$ 中做一次操作，然后有一个 $1$ 会变成 $0$，再选这两个 $0$，就 `No` 了。

于是我们考虑克服这个问题。

首先，你可以发现在操作过程中，除非不和法、只有一个 $1$，否则一般情况下最多只会有一个 $0$。

但是在其中两个数为 $1$，并且选中它们的时候就会有一个变成 $0$，这就是上面所说的问题的本质。

然后就可以解决它了。首先通过鸽巢原理可以发现，连续的两个字符串中至少有一个字符是相同的。

在发现两选中数相同的时候，进行分类讨论：
1. 若下一次操作与本次相同，就在这一次进行任意一个操作，下一次进行相反的操作，这样就使现在的状态与原来相同。
2. 否则我们就选择与下一次重复的的那个字符这次加，保证下次可以减（即使下一次另一个不是 $0$ 也不会出问题）。

最后有几个小细节：
- 如果初始 $a,b,c$ 都是 $0$ 且有操作直接 `No`，若有操作，选中的必定都是。
- 每次相等的时候要判断是否均为 $0$，若是，则无解。
- 在 $i=n$ 的时候若有相等的要另外处理，因为 $i+1$ 并没有赋值。

代码：
```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<queue>
#include<map>
#include<algorithm>
using namespace std;
//char cc[1<<21],*uu=cc,*vv=cc;
//#define getchar() (uu==vv&&(vv=(uu=cc)+fread(cc,1,1<<21,stdin),uu==vv)?EOF:*uu++)
inline int read(){
	char ch=getchar();int X=0;bool fl=0;
	while(ch<'0'||ch>'9'){if(ch=='-')fl=1;ch=getchar();}
	while(ch>='0'&&ch<='9'){X=(X<<1)+(X<<3)+ch-'0';ch=getchar();}
	if(fl)return ~(X-1);
	return X;
}
int q,a,b,c;
string k[100005];
char ans[100005];
int main(){
	q=read(),a=read(),b=read(),c=read();
	if(!a&&!b&&!c){puts(q?"No":"Yes");return 0;}
	for(int i=1;i<=q;i++)cin>>k[i];
	for(int i=1;i<=q;i++){
		if(k[i]=="AB"){
			if(a>b)--a,++b,ans[i]='B';
			else if(a==b&&i<q){
				if(!a){puts("No");return 0;}
				if(k[i+1]=="AB")ans[i]='A',ans[i+1]='B';
				if(k[i+1]=="AC")--b,++c,ans[i]='A',ans[i+1]='C';
				if(k[i+1]=="BC")--a,++c,ans[i]='B',ans[i+1]='C';
				++i;
			}
			else --b,++a,ans[i]='A';
		}
		else if(k[i]=="AC"){
			if(a>c)--a,++c,ans[i]='C';
			else if(a==c&&i<q){
				if(!a){puts("No");return 0;}
				if(k[i+1]=="AB")--c,++b,ans[i]='A',ans[i+1]='B';
				if(k[i+1]=="AC")ans[i]='A',ans[i+1]='C';
				if(k[i+1]=="BC")--a,++b,ans[i]='C',ans[i+1]='B';
				++i;
			}
			else --c,++a,ans[i]='A';
		}
		else{
			if(b>c)--b,++c,ans[i]='C';
			else if(b==c&&i<q){
				if(!b){puts("No");return 0;}
				if(k[i+1]=="AB")--c,++a,ans[i]='B',ans[i+1]='A';
				if(k[i+1]=="AC")--b,++a,ans[i]='C',ans[i+1]='A';
				if(k[i+1]=="BC")ans[i]='B',ans[i+1]='C';
				++i;
			}
			else --c,++b,ans[i]='B';
		}
		if(a<0||b<0||c<0){puts("No");return 0;}
	}
	puts("Yes");
	for(int i=1;i<=q;i++)putchar(ans[i]),putchar('\n');
}
```

最后，在这里膜拜机房的神仙 @loser_king，他只写了 381B，交了一发就过了，并抢到了 c++ 的最短解，Orz。

[欢迎大家观赏](https://atcoder.jp/contests/abc166/submissions/25890607)

[如果您看不惯压行，也可看这里](https://www.luogu.com.cn/paste/onkqpqpb)

---

## 作者：Dreamer_xbt910 (赞：3)

[题目](https://www.luogu.com.cn/problem/AT_abc166_f)



# 思路

这是一道比较简单的贪心题。

不断地分类讨论。哪一个小就加一，另一个就减一。如果两个都相等时，就判断下一个，有相同的就加一，另一个减一,如果都没有相同的,就随便加减。如果两个都为 $0$ 时，就直接输出 ```No``` 即可。

# Code
代码有点长。额。

```
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,a,b,c;
string s[100005],ans;
signed main(){
	scanf("%lld%lld%lld%lld",&n,&a,&b,&c);
	for(int i=1;i<=n;i++)
		cin>>s[i];
	for(int i=1;i<=n;i++){
		if(s[i]=="AB"){
			if(a==0&&b==0) {
				puts("No");
				return 0;
			}
			if(a>b){
				b++,a--;
				ans+='B';
			}else if(a<b){
				b--,a++;
				ans+='A';
			}else{
				if(s[i+1]=="BC"){
					b++;
					a--;
					ans+='B';
				}
				else if(s[i+1]=="AC"){
					a++;
					b--;
					ans+='A';
				}else{
					a++;
					b--;
					ans+='A'; 
				}
			}
		}
		if(s[i]=="AC"){
			if(a==0&&c==0)
			{
				puts("No");
				return 0;
			}
			if(a>c){
				c++;
				a--;
				ans+='C';
			}else if(a<c){
				c--,a++;
				ans+='A';
			}else{
				if(s[i+1]=="AB"){
					a++;
					c--;
					ans+='A';
				}
				else if(s[i+1]=="BC"){
					c++;
					a--;
					ans+='C';
				}else{
					a++;
					c--;
					ans+='A';
				}
			}
		}
		if(s[i]=="BC"){
			if(c==0&&b==0)
			{
				puts("No");
				return 0;
			}
			if(c>b){
				b++;
				c--;
				ans+='B';
			}else if(c<b){
				b--,c++;
				ans+='C';
			}else{
				if(s[i+1]=="AC"){
					c++,b--;
					ans+='C';
				}
				else if(s[i+1]=="AB"){
					b++;
					c--;
					ans+='B';
				}else{
					b++;
					c--;
					ans+='B';
				}
			}
		}
	}
	puts("Yes");
	for(int i=1;i<=n;i++){
		cout<<ans[i-1]<<"\n";
	}
	return 0;
}
```

如有问题，请指出错误。

谢谢！

---

## 作者：Mu_leaf (赞：3)

## [前言]
~~什么题啊，我模拟赛打了半天贪心没 A，同班大佬 dfs 直接把我虐爆。~~
## [思路]
### 1. 贪心

------------

拿到题目，由于题目要求使 $a,b,c$ 都不能小于 $0$，那么很容易得到以下贪心策略：

遇到 2 个数，让大的减少，小的增加。

但这样虽然正确率极高(~~只 WA 9 个点~~)，但毕竟不是 AC。

给出以下 hack 数据：
```
2 0 1 1
BC
AC
```
可以发现，无论任何时刻，这三个数中最多有一个 $0$，否则无解。
上面给出的 hack 数据，如果您选择 $C$ 变小，$B$ 变大那就错啦。

莫非是 dp？其实不然，因为只有在两个数相等且都为 $1$，另一个数为 $0$，如果当前先要在两个 $1$ 中做一次操作，然后有一个 $1$ 会变成 $0$，再选这两个 $0$，当然就是 ```No``` 啦。

于是当出现这种情况时，我们便可以分类讨论：

- 若下一次操作与本次相同，就在这一次进行任意一个操作，下一次进行相反的操作，这样就使现在的状态与原来相同。
- 否则我们就选择与下一次重复的的那个字符这次加，保证下次可以减（即使下一次另一个不是 $0$ 也不会出问题）。
# 贪心CODE

```cpp
#include <bits/stdc++.h>
#define Yes printf("Yes\n")
#define No printf("No\n")
using namespace std;
int n,a,b,c;
string k[100005];
char ans[100005];
int main(){
	cin >> n >> a >> b >> c;
	if(!a&&!b&&!c){
		if(n) No;
		else Yes;
		return 0;
	}
	for(int i=1;i<=n;i++)cin>>k[i];
	for(int i=1;i<=n;i++){
		if(k[i]=="AB"){
			if(a>b)--a,++b,ans[i]='B';
			else if(a==b&&i<n){
				if(!a){puts("No");return 0;}
				if(k[i+1]=="AB")ans[i]='A',ans[i+1]='B';
				if(k[i+1]=="AC")--b,++c,ans[i]='A',ans[i+1]='C';
				if(k[i+1]=="BC")--a,++c,ans[i]='B',ans[i+1]='C';
				++i;
			}
			else --b,++a,ans[i]='A';
		}
		else if(k[i]=="AC"){
			if(a>c)--a,++c,ans[i]='C';
			else if(a==c&&i<n){
				if(!a){puts("No");return 0;}
				if(k[i+1]=="AB")--c,++b,ans[i]='A',ans[i+1]='B';
				if(k[i+1]=="AC")ans[i]='A',ans[i+1]='C';
				if(k[i+1]=="BC")--a,++b,ans[i]='C',ans[i+1]='B';
				++i;
			}
			else --c,++a,ans[i]='A';
		}
		else{
			if(b>c)--b,++c,ans[i]='C';
			else if(b==c&&i<n){
				if(!b){puts("No");return 0;}
				if(k[i+1]=="AB")--c,++a,ans[i]='B',ans[i+1]='A';
				if(k[i+1]=="AC")--b,++a,ans[i]='C',ans[i+1]='A';
				if(k[i+1]=="BC")ans[i]='B',ans[i+1]='C';
				++i;
			}
			else --c,++b,ans[i]='B';
		}
		if(a<0||b<0||c<0){No;return 0;}
	}
	Yes;
	for(int i=1;i<=n;i++) printf("%c\n",ans[i]);
}
```


~~那么这道题就结束了。~~

介绍一下大佬的 dfs 做法：

~~感觉歪解~~。

### 2.DFS


------------

由于每两个操作之间只有 6 种情况。

所以当我们到一个操作时，枚举加那个数，减那个数，当有数小于 0 时，退出循环即可。

至于时间复杂度嘛，就留给读者自证了。
# 深搜Code：
```cpp
#include <bits/stdc++.h>
#define a v[0]
#define b v[1]
#define c v[2]
using namespace std;
const int N = 1e5 + 5;
int n, v[4];
string s[N];
int ans[N];
void dfs(int u) {
	if (a < 0 || b < 0 || c < 0) { return; }
	if (u > n) {
		puts("Yes");
		for (int i = 1; i <= n; ++i) { cout << s[i][ans[i]] << "\n"; }
		exit(0);
	}
	for (int i = 0; i < 2; ++i) {
		ans[u] = i;
		++v[s[u][i] - 'A'];
		--v[s[u][!i] - 'A'];
		dfs(u + 1);
		--v[s[u][i] - 'A'];
		++v[s[u][!i] - 'A'];
	}
	return;
}
int main() {
	cin >> n >> a >> b >> c;
	for (int i = 1; i <= n; ++i) { cin >> s[i]; }
	dfs(1);
	puts("No");
	return 0;
}
```
自此本题结。

---

## 作者：gyh20 (赞：2)

可以轻易的想出一种贪心做法，每次减大的，加小的。

这样的正确率很高，事实上，只会 WA 9 个点。

考虑如何 hack。

比如这个数据

$2 ~0 ~1 ~1$

$BC$

$AC$

如果您将 $C$ 变小 $B$ 变大那么您就成功的 WA 了。

此时，我们发现这种 hack 数据只会某一时刻是 $0~1~1$ 这种数据，也就是 $sum=2$。然而总量是不会变的，特判即可。

对于 $sum=2$：

DP

令 $f[x][i][j][k]$ 表示第 $x$ 次操作，$A=i$，$B=j$，$C=k$ 是否可行。

枚举上一层状态即可。同时记录是由哪一个状态转移来的。

最后递归输出答案即可。

代码有点长，但很多都是复制粘贴的，所以不是那么难写，同时要注意细节。

```cpp
#include<bits/stdc++.h>
#define in inline
#define int long long
#define re register
using namespace std;
in int read() {
	re int t=0;
	re char v=getchar();
	while(v<'0'||v>'9')v=getchar();
	while(v>='0'&&v<='9') {
		t=(t<<3)+(t<<1)+(v^48);
		v=getchar();
	}
	return t;
}
int n,m,ans[100002],A,B,C,dp[100002][3][3][3],pre[100002][3][3][3];
char s[12];
long long sum;
inline void work(re int x,re int a,re int b,re int c){
	if(x==0)return;
	re int xx=pre[x][a][b][c];
	if(xx==1)++a,--b;
	if(xx==2)--a,++b;
	if(xx==3)++a,--c;
	if(xx==4)--a,++c;
	if(xx==5)++b,--c;
	if(xx==6)--b,++c;
	work(x-1,a,b,c);
	if(xx==2||xx==4)puts("A");
	if(xx==1||xx==6)puts("B");
	if(xx==3||xx==5)puts("C");
}
signed main(){
	n=read();A=read();B=read();C=read();
//	if(A+B+C==2ll)return 1;
	if(A+B+C!=2ll){
		for(re int i=1;i<=n;++i){
			scanf("%s",s+1);
			if(s[1]=='A'&&s[2]=='B'){
				if(A>B){--A;++B;ans[i]=2;
				}
				else{
					if(B==0){
						puts("No");
						return 0;
					}
					--B;++A;
					ans[i]=1;
				}
			}
			if(s[1]=='A'&&s[2]=='C'){
				if(A>C){
					--A;++C;
					ans[i]=3;
				}
				else{
					if(C==0){
						puts("No");
						return 0;
					}
					--C;++A;
					ans[i]=1;
				}
			}
			if(s[1]=='B'&&s[2]=='C'){
				if(B>C){
					--B;++C;
					ans[i]=3;
				}
				else{
					if(C==0){
						puts("No");
						return 0;
					}
					--C;++B;
					ans[i]=2;
				}
			}
		}
		puts("Yes");
		for(re int i=1;i<=n;++i){
			if(ans[i]==1)puts("A");
			if(ans[i]==2)puts("B");
			if(ans[i]==3)puts("C");
		}
	}
	else{
		dp[0][A][B][C]=1;
		for(re int ii=1;ii<=n;++ii){
			scanf("%s",s+1);
			if(s[1]=='A'&&s[2]=='B'){
				for(re int i=0;i<=1;++i){
					for(re int j=1;j<=2;++j){
						for(re int k=0;k<=2;++k){
							if(dp[ii-1][i+1][j-1][k]){
								dp[ii][i][j][k]=1;
								pre[ii][i][j][k]=1;
							}
						}
					}
				}
				for(re int i=1;i<=2;++i){
					for(re int j=0;j<=1;++j){
						for(re int k=0;k<=2;++k){
							if(dp[ii-1][i-1][j+1][k]){
								dp[ii][i][j][k]=1;
								pre[ii][i][j][k]=2;
							}
						}
					}
				}
			}
			if(s[1]=='A'&&s[2]=='C'){
				for(re int i=0;i<=1;++i){
					for(re int j=0;j<=2;++j){
						for(re int k=1;k<=2;++k){
							if(dp[ii-1][i+1][j][k-1]){
								dp[ii][i][j][k]=1;
								pre[ii][i][j][k]=3;
							}
						}
					}
				}
				for(re int i=1;i<=2;++i){
					for(re int j=0;j<=2;++j){
						for(re int k=0;k<=1;++k){
							if(dp[ii-1][i-1][j][k+1]){
								dp[ii][i][j][k]=1;
								pre[ii][i][j][k]=4;
							}
						}
					}
				}
			}
			if(s[1]=='B'&&s[2]=='C'){
				for(re int i=0;i<=2;++i){
					for(re int j=0;j<=1;++j){
						for(re int k=1;k<=2;++k){
							if(dp[ii-1][i][j+1][k-1]){
								dp[ii][i][j][k]=1;
								pre[ii][i][j][k]=5;
							}
						}
					}}
				for(re int i=0;i<=2;++i){
					for(re int j=1;j<=2;++j){
						for(re int k=0;k<=1;++k){
							if(dp[ii-1][i][j-1][k+1]){
								dp[ii][i][j][k]=1;
								pre[ii][i][j][k]=6;
							}
						}
					}
				}
		}
		}
		for(re int i=0;i<=2;++i){
			for(re int j=0;j<=2;++j){
				for(re int k=0;k<=2;++k){
					if(dp[n][i][j][k]){
						puts("Yes");
						work(n,i,j,k);
						return 0;
					}
				}
			}
		}
		puts("No");
	}
}
```


---

## 作者：Rannio (赞：1)

纯贪心做法。

有一个结论是显然的：对于一个操作的两个变量，哪个小哪个加 $1$。但当两个变量相同时是不能随便加的，因为这样可能会失去最优性，例如 `2 1 1 0 AB BC`，当我们在处理询问 `AB` 时需要给 $b$ 加 $1$ 而不是 $a$。

这种情况其实也不难处理，只需要判断一下下一个处理的是哪两个变量，将下一个操作与当前操作中要处理的相同变量加 $1$ 即可，如果下一个操作与当前操作相同那就随便加，因为我们可以在下一个操作中给当前减 $1$ 的变量加 $1$，这样这两个操作其实就等价于没操作，对最优性肯定是不影响的。

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a,b,c;
char cr[1000005];
string l[100005];
int cnt;
signed main(){
    scanf("%lld%lld%lld%lld",&n,&a,&b,&c);
    for(int i=1;i<=n;i++) cin>>l[i];
    for(int i=1;i<=n;i++){
        if(l[i]=="AB"){
            if(a<b){
                a++,b--;
                cr[++cnt]='A';
            }
            else if(a>b){
                a--,b++;
                cr[++cnt]='B';
            }
            else{
                if(l[i+1]=="BC"){
                    b++,a--;
                    cr[++cnt]='B';
                }
                else{
                    a++,b--;
                    cr[++cnt]='A';
                }
            }
        }
        if(l[i]=="AC"){
            if(a<c){
                a++,c--;
                cr[++cnt]='A';
            }
            else if(a>c){
                a--,c++;
                cr[++cnt]='C';
            }
            else{
                if(l[i+1]=="AB"){
                    a++,c--;
                    cr[++cnt]='A';
                }
                else{
                    a--,c++;
                    cr[++cnt]='C';
                }
            }
        }
        if(l[i]=="BC"){
            if(b<c){
                b++,c--;
                cr[++cnt]='B';
            }
            else if(b>c){
                b--,c++;
                cr[++cnt]='C';
            }
            else{
                if(l[i+1]=="AB"){
                    b++,c--;
                    cr[++cnt]='B';
                }
                else{
                    c++,b--;
                    cr[++cnt]='C';
                }
            }
        }
        if(a<0||b<0||c<0){
            printf("No");
            return 0;
        }
    }
    printf("Yes\n");
    for(int i=1;i<=cnt;i++) cout<<cr[i]<<endl;
    return 0;
}
```

---

## 作者：fighter (赞：1)

首先考虑一个贪心的策略，每次操作，我们都把大的那个数-1，小的+1。相等的情况下面特殊考虑。

YY一会儿或者手玩几组数据就会发现，如果我们能做到任意时刻这三个数中最多只有1个0，那么这种策略一定能构成合法方案。

那么怎样才能保证任意时刻最多只有1个0呢？

如果现在已经有一个0，那么当另外两个数的和>3的时候，是满足条件的。因为我们的策略决定另外两个数会慢慢趋向于平均，所以不会再出现0。

同样的，三个数都大于0的情况也是成立的。

于是我们发现可能不合法的情况只有1种：

- 初始局面就有2个0。

但如果局面是(1,1,0)，那么一次操作就可以变成(2,0,0)，这样就会出现两个0，如果操作不当可能会不合法。

所以我们根据三个数字的和分类讨论。当和大于等于3时，我们直接按贪心策略，但是要特判初始两个0的情况。

当和小于3时，情况稍稍复杂一点。如果当前操作在1和0之间，那就把1变成0，0变成1。

如果操作是两个1之间，那么就要根据后一步的操作来确定哪一个1变成2。因为这样会出现2个0，如果不跟据后面的操作随便选的话会出现不合法。

如果后面一步和这步完全一样，那么这两个操作就可以忽略掉。

如果后一步是这步中的一个位置和不在这步中的位置，那么我们就要把后面那次操作和这次操作中共有的那个数变成2。

代码写得自己都看不下去了……

```cpp
#include <bits/stdc++.h>
#define ll long long
#define MAX 500005
using namespace std;

int n;
char s[20];
vector<int> ans;
ll a[5];

int main()
{
    cin >> n >> a[0] >> a[1] >> a[2];
    if(a[0]+a[1]+a[2] > 2){
        for(int i = 1; i <= n; i++){
            scanf("%s", s+1);
            int x = s[1]-'A', y = s[2]-'A';
            if(a[x] == 0 && a[y] == 0){
                puts("No");
                return 0;
            }
            ans.push_back(a[x] > a[y]?y:x);
            if(a[x] > a[y]) a[x]--, a[y]++;
            else a[x]++, a[y]--;
        }
    }
    else{
        for(int i = 1; i <= n; i++){
            scanf("%s", s+1);
            int x = s[1]-'A', y = s[2]-'A';
            if(a[x] == 0 && a[y] == 0){
                puts("No");
                return 0;
            }
            if(!a[x]) ans.push_back(x), a[y]--, a[x]++;
            else if(!a[y]) ans.push_back(y), a[x]--, a[y]++;
            else{
                if(i == n){
                    ans.push_back(x);
                    break;
                }
                scanf("%s", s+1);
                int u = s[1]-'A', v = s[2]-'A';
                if(u == x && v == y){
                    ans.push_back(x), ans.push_back(y);
                    i++;
                }
                else{
                    int p;
                    if(u == x || v == x) p = x;
                    else p = y;
                    ans.push_back(p);
                    ans.push_back(u+v-p);
                    a[x+y-p]--, a[u+v-p]++;
                    i++;
                }
            }
        }
    }
    puts("Yes");
    for(int i = 0; i < ans.size(); i++){
        putchar(ans[i]+'A'), puts("");
    }

    return 0;
}

```

---

## 作者：ldll0721 (赞：0)

本题就是一个普通的贪心，每一次针对较小数作加法，然后对于每一步操作用一个 $ans_i$ 进行保存，并且因为我们是使用的 dfs 来判断每一次的增减，所以不用担心出现例如 $a=b$ 增加错误而导致后面出现 $a<0$ 或 $b<0$ 的情况。
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
string s[500005];
char ans[500005];
int n,a,b,c;
void find(int a, int b, int c, int k) {
	if (k == n + 1) {
		cout << "Yes"<<endl;
		for (int i = 1; i <= k; i++) {
			cout << ans[i] << endl;
		}
		exit(0);
	}
	if (s[k] == "AB") {
		if (a > 0) {
			ans[k] = 'B';
			find(a - 1, b + 1, c, k + 1);
		}
		if (b > 0) {
			ans[k] = 'A';
			find(a + 1, b - 1, c, k + 1);
		}
	}
	if (s[k] == "AC") {
		if (a > 0) {
			ans[k] = 'C';
			find(a - 1, b, c + 1, k + 1);
		}
		if (c > 0) {
			ans[k] = 'A';
			find(a + 1, b, c - 1, k + 1);
		}
	}
	if (s[k] == "BC") {
		if (b > 0) {
			ans[k] = 'C';
			find(a, b - 1, c + 1, k + 1);
		}
		if (c > 0) {
			ans[k] = 'B';
			find(a, b + 1, c - 1, k + 1);
		}
	}
}
signed main() {
	cin >> n >> a >> b >> c;
	for (int i = 1; i <= n; i++) {
		cin >> s[i];
	}
	int q=1;
	find(a, b, c, q);
	cout << "No";
	return 0;
}
```
##### p.s 建议降黄。

---

## 作者：Chenyichen0420 (赞：0)

## 思路分析

首先，有一个比较正确的贪心思路：更改的二者中，选更小的加，更大的减。

不过，这种贪心需要一点修正，就是在遇到二者相等的时候，比如 `2 1 1 0 AB BC`。

如果按照上面的贪心的话，那么你可能会出现 $2 0 0$，从而判无解，但实际上他是有解的。

其实仔细一想，对于这一轮而言，因为二者相等，所以唯一的差别就在于这个选择对下一轮的影响。分两种情况：

1. 两次操作相同，则两次分别取不同的加即可。
2. 两次操作不同，其中一定有一个数被修改了两次。我们要尽可能地让后面的不被影响，所以这次给重合的数加，下次给另一个数加。

其实思路还是比较简洁的，代码也偏短。如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,v[4]; char t[100005][3],an[100005];
inline void net(){
	cout<<"No\n";
	exit(0);
}
int main(){
	ios::sync_with_stdio(0);
	cin>>n>>v[0]>>v[1]>>v[2];
	for(int i=1;i<=n;++i) cin>>t[i];
	for(int i=1;i<=n;++i){
		int cl=t[i][0]-'A',cr=t[i][1]-'A';
		if(v[cl]>v[cr]) v[cl]--,v[cr]++,an[i]=cr+'A';
		else if(v[cl]<v[cr]) v[cr]--,v[cl]++,an[i]=cl+'A';
		else{
			if(!v[cl]) net();
			int ccl=t[i+1][0]-'A',ccr=t[i+1][1]-'A';
			if(cl==ccl&&cr==ccr) an[i]=cl+'A',an[i+1]=cr+'A';
			else if(cl==ccl) an[i]=cl+'A',an[i+1]=ccr+'A',v[cr]--,v[ccr]++;
			else if(cr==ccr) an[i]=cr+'A',an[i+1]=ccl+'A',v[cl]--,v[ccl]++;
			else if(cl==ccr) an[i]='B',an[i+1]='A',v[2]--,v[0]++;  //BC-AB
			else if(cr==ccl) an[i]='B',an[i+1]='C',v[2]++,v[0]--;
			else an[i]=cl+'A',v[cl]++,v[cr]--; i++;
		}
		if(v[0]<0||v[1]<0||v[2]<0) net();
	}
	cout<<"Yes\n";
	for(int i=1;i<=n;++i)cout<<an[i]<<"\n";
}
```

附赠一组自造的数据：

```txt
9 1 0 1
BC
AB
BC
BC
AB
AB
AC
AB
AB
```

---

## 作者：AKPC (赞：0)

这是一篇纯贪心题解。

令 $k=[a\geq1]+[b\geq1]+[c\geq1]$，在这里先假设 $a,b,c\in\{0,1\}$。

- 如果 $k=0$，显然无解。
- 如果 $k=1$，要看操作会不会出现两个 $0$ 同时操作的情况，如果有解，解是唯一的。
- 如果 $k=2$，讨论操作：
	- 如果操作涉及一个 $1$ 和一个 $0$，直接交换。
	- 如果涉及到两个 $1$，假设是 $a,b$，此时要把 $a,b$ 其中一个变成 $2$，继续讨论下一次操作情况：
		- 如果下一次操作涉及依然是 $a,b$，这次就随便选一个变成 $2$，下次可以改回来。
		- 如果不是，则下次操作只涉及到这次的其中一个，假设其为 $a$，也就是下次涉及到 $a,c$，那就把 $a$ 变成 $2$，这样在下次操作的时候能把 $a,c$ 都变成 $1$。
	- 也就是说，$k=2$ 一定有解。
- 如果 $k=3$，因为 $k=2$ 一定有解，所以 $k=3$ 也一定有解，你甚至可以把 $k=3$ 视作 $k=2$ 来解，即故意把其中一个改成 $0$。

延申 $a,b,c$ 到正常范围。

- 如果 $k=0$，无解。
- 如果 $k=1$，假设 $a\geq 1$，则讨论：
	- 如果 $a=1$，同上。
	- 如果 $a>1$，则判断第一次操作能不能给出去一个 $1$，如果第一次操作到 $b,c$ 显然无解，否则就可以把 $1$ 给出去，根据前面的 $k=2$ 求解。
- $k=2$，同上。
- $k=3$，同上。

本题还有一半的难度在[代码](https://www.luogu.com.cn/paste/ev9vncd2)实现，模拟即可。

---

