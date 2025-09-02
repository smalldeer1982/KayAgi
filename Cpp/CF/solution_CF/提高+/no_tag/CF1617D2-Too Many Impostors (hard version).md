# Too Many Impostors (hard version)

## 题目描述

This is an interactive problem. The only difference between the easy and hard version is the limit on number of questions.

There are $ n $ players labelled from $ 1 $ to $ n $ . It is guaranteed that $ n $ is a multiple of $ 3 $ .

Among them, there are $ k $ impostors and $ n-k $ crewmates. The number of impostors, $ k $ , is not given to you. It is guaranteed that $ \frac{n}{3} < k < \frac{2n}{3} $ .

In each question, you can choose three distinct integers $ a $ , $ b $ , $ c $ ( $ 1 \le a, b, c \le n $ ) and ask: "Among the players labelled $ a $ , $ b $ and $ c $ , are there more impostors or more crewmates?" You will be given the integer $ 0 $ if there are more impostors than crewmates, and $ 1 $ otherwise.

Find the number of impostors $ k $ and the indices of players that are impostors after asking at most $ n+6 $ questions.

The jury is adaptive, which means the indices of impostors may not be fixed beforehand and can depend on your questions. It is guaranteed that there is at least one set of impostors which fulfills the constraints and the answers to your questions at any time.

## 说明/提示

Explanation for example interaction (note that this example only exists to demonstrate the interaction procedure and does not provide any hint for the solution):

For the first test case:

Question "? 1 2 3" returns $ 0 $ , so there are more impostors than crewmates among players $ 1 $ , $ 2 $ and $ 3 $ .

Question "? 3 4 5" returns $ 1 $ , so there are more crewmates than impostors among players $ 3 $ , $ 4 $ and $ 5 $ .

Outputting "! 3 4 1 2" means that one has found all the impostors, by some miracle. There are $ k = 3 $ impostors. The players who are impostors are players $ 4 $ , $ 1 $ and $ 2 $ .

For the second test case:

Question "? 7 1 9" returns $ 1 $ , so there are more crewmates than impostors among players $ 7 $ , $ 1 $ and $ 9 $ .

Outputting "! 4 2 3 6 8" means that one has found all the impostors, by some miracle. There are $ k = 4 $ impostors. The players who are impostors are players $ 2 $ , $ 3 $ , $ 6 $ and $ 8 $ .

## 样例 #1

### 输入

```
2
6

0

1

9

1```

### 输出

```
? 1 2 3

? 3 4 5

! 3 4 1 2

? 7 1 9

! 4 2 3 6 8```

# 题解

## 作者：vectorwyx (赞：3)

延续 easy version 的思路，找到两个三元组 $(a,b,c),(b,c,d)$ 满足它们询问出的 $01$ 值不同。

把原序列每三个元素分一块分成 $\frac{n}{3}$ 块，然后对每一块对应的三元组依次询问。由于题目保证 $\frac{n}{3}<k<\frac{2n}{3}$，因此一定能找到两块满足它们询问得到的值不同，不妨设 $(p,p+1,p+2),(q,q+1,q+2)$ 是找到的询问值不同的两块，且前者询问的结果为 $0$。

把 $(p,p+1,p+2),(q,q+1,q+2)$ 单拎出来，每次询问两个相邻的三元组，如 $(p+1,p+2,q),(p+2,q,q+1)$，一定能找到相邻且询问值不同的两个三元组。这有点像离散版的零点存在定理，因为三元组内 $1$ 的数量的变化只可能为 $-2,0,2$，而最终 $1$ 的数量由负转正，那么一定有一个时刻 $1$ 的数量由 $-1$ 变为了 $1$。

现在我们可以用 $\frac{n}{3}+2$ 次操作找到两个三元组 $(a,b,c),(b,c,d)$ 满足它们询问出的 $01$ 值不同，即找到两个位置 $s,t$ 满足 $a_s=0,a_t=1$。接下来，我们对于每一块使用至多 $2$ 次求出块内三个位置的确切值。不妨设当前块 $(i,i+1,i+2)$ 询问值为 $0$，先询问 $(t,i,i+1)$，如果返回值为 $1$ 则 $i,i+1$ 中有且仅有一个 $1$，所以 $a_{i+2}=0$，再询问一次 $(s,t,i)$ 就能确定 $a_i$，从而确定 $a_{i+1}$。而如果 $(t,i,i+1)$ 返回值为 $0$，那么 $a_i=a_{i+1}=0$，再询问一次 $(s,t,i+2)$ 就能确定 $a_{i+2}$。$(i,i+1,i+2)$ 询问值为 $1$ 时同理。综上，总操作数为 $n+2$。

代码如下：

```cpp
//author:望远星
#include<bits/stdc++.h>
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define mk make_pair
#define sml(x,y) (x=min(x,y))
#define big(x,y) (x=max(x,y))
#define ll long long
#define ull unsigned long long
#define db double
#define fo(i,x,y) for(int i=x;i<=y;++i)
#define go(i,x,y) for(int i=x;i>=y;--i)
using namespace std;
inline int read(){int x=0,fh=1; char ch=getchar(); while(!isdigit(ch)){if(ch=='-') fh=-1; ch=getchar();} while(isdigit(ch)){x=(x<<1)+(x<<3)+ch-'0'; ch=getchar();} return x*fh;}
inline void out(int *a,int l,int r){fo(i,l,r) cout<<*(a+i)<<' ';puts("");}

const int N=1e5+5;
int a[N],n,b[N];

int ask(int x,int y,int z){
	printf("? %d %d %d\n",x,y,z);cout.flush();
	int ret=read();
	if(ret==-1) exit(0);
	return ret;
}

void solve(){
	cin>>n;int p,q;//p:0 q:1
	for(int i=1;i<=n;i+=3){
		b[i]=ask(i,i+1,i+2);
		if(b[i]) q=i;
		else p=i;
	}
	int x=ask(p+1,p+2,q),y,s,t;
	if(x) s=p,t=q;
	else{
		y=ask(p+2,q,q+1);
		if(y) s=p+1,t=q+1;
		else s=p+2,t=q+2;
	}
	//printf("%d,%d\n",s,t);
	a[s]=0,a[t]=1;
	for(int i=1;i<=n;i+=3){
		if(p==i||q==i){
			fo(j,i,i+2) if(j!=s&&j!=t) a[j]=ask(s,t,j);
			continue;
		}
		if(b[i]){
			if(ask(s,i,i+1)){
				a[i]=a[i+1]=1;
				a[i+2]=ask(s,t,i+2);
			}else a[i+2]=1,a[i]=ask(s,t,i),a[i+1]=a[i]^1;
		}else{
			if(!ask(t,i,i+1)){
				a[i]=a[i+1]=0;
				a[i+2]=ask(s,t,i+2);
			}else a[i+2]=0,a[i]=ask(s,t,i),a[i+1]=a[i]^1;
		}
	}
	vector<int> ans;fo(i,1,n) if(!a[i]) ans.pb(i);
	cout<<"! "<<ans.size()<<' ';for(int i:ans) cout<<i<<' ';puts("");
	cout.flush();
}

signed main(){
	int T=read();
	while(T--) solve();
	return 0;
}
/*
-------------------------------------------------
*/
```



---

## 作者：Alan_Zhao (赞：2)

## 题意

有 $n$ 个人（保证 $n\bmod 3=0$），其中有 $k$ 个 impostor（保证 $n< 3k< 2n$）和 $n-k$ 个 crewmate，但你不知道 $k$ 具体是多少。你可以询问至多 $n+6$ 次，每次给出 $a,b,c(1\le a,b,c\le n)$，你可以得知 $a,b,c$ 中是 impostor 多还是 crewmate 多。

找到所有的 impostors。

## 题解

### 找到任意一个 impostor 和一个 crewmate

一个结论是，对于四个人 $x,y,z,w$，若询问 $(x,y,z)$ 和 $(y,z,w)$ 得到的结果不同，那么我们可以确定 $x$ 和 $w$ 的身份。

将这 $n$ 个人分成 $\frac{n}{3}$ 组，第 $i$ 组是 $(3i-2,3i-1,3i)$。若某一组中 impostor 更多，则称这一组是 $1$；否则这一组是 $0$。

用 $\frac{n}{3}$ 次询问得到每组是 $0$ 还是 $1$。由于 $\frac{n}{3}<k<\frac{2n}{3}$，所以一定存在一组 $p$ 满足它是 $0$；也一定存在一组 $q$ 满足它是 $1$。

我们询问 $(3p-1,3p,3q-2),(3p,3q-2,3q-1)$。我们知道，在 $3p-2,3p-1,3p,3q-2,3q-1,3q$ 中，一定有相邻的四个人 $x,y,z,w$ 满足 $(x,y,z)$ 和 $(y,z,w)$ 询问的结果不同。根据上面的结论，我们可以在这六个人里找到一个 impostor 和一个 crewmate，使用了 $\frac{n}{3}+2$ 次操作。

### 确定所有人的身份

找到了一个 impostor 和一个 crewmate，设它们分别是 $a$ 和 $b$。

对于第 $i$ 组，我们已经知道了它是 $0$ 还是 $1$。不妨设它是 $0$。我们询问 $(3i-2,3i-1,b)$，分类讨论这个询问的结果：

0. 说明 $3i-2$ 和 $3i-1$ 都是 impostor。再询问 $(3i,a,b)$ 就可以得到 $3i$ 的身份。
1. 说明 $3i$ 一定是 impostor，且 $3i-2$ 和 $3i-1$ 中恰好有一个 impostor。询问 $(3i-2,a,b)$ 就可以得到 $3i-2$ 和 $3i-1$ 的身份。

若这一组是 $1$，类似地分类讨论即可。

总共使用了 $n+2$ 次操作。

## 代码

```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
#define For(Ti,Ta,Tb) for(int Ti=(Ta);Ti<=(Tb);++Ti)
#define Dec(Ti,Ta,Tb) for(int Ti=(Ta);Ti>=(Tb);--Ti)
#define Debug(...) fprintf(stderr,__VA_ARGS__)
typedef long long ll;
const int N=1e4+5;
int Query(int a,int b,int c){
	cout<<"? "<<a<<' '<<b<<' '<<c<<endl;
	int res;cin>>res;
	return res;
}
int T,n,res[N];
int main(){
	cin>>T;
	while(T--){
		cin>>n;
		int _imp=0,_crm=0;
		For(i,1,n/3){
			res[i]=Query(i*3-2,i*3-1,i*3);
			if(res[i]) _crm=i;
			else _imp=i;
		}
		int res1=Query(_imp*3-1,_imp*3,_crm*3-2),res2=Query(_imp*3,_crm*3-2,_crm*3-1),imp,crm;
		if(res[_imp]!=res1) imp=_imp*3-2,crm=_crm*3-2;
		else if(res1!=res2){
			if(res1) imp=_crm*3-1,crm=_imp*3-1;
			else imp=_imp*3-1,crm=_crm*3-1;
		}else imp=_imp*3,crm=_crm*3;
		vector<int> ans;
		ans.push_back(imp);
		For(i,1,n/3){
			if(_imp==i||_crm==i){
				For(j,i*3-2,i*3) if(j!=imp&&j!=crm&&Query(j,imp,crm)==0) ans.push_back(j);
				continue;
			}
			if(res[i]){
				int x=Query(i*3-2,i*3-1,imp);
				if(x){if(Query(i*3,imp,crm)==0) ans.push_back(i*3);}
				else ans.push_back(Query(i*3-2,imp,crm)?i*3-1:i*3-2);
			}else{
				int x=Query(i*3-2,i*3-1,crm);
				if(!x){ans.push_back(i*3-2),ans.push_back(i*3-1);if(Query(i*3,imp,crm)==0) ans.push_back(i*3);}
				else ans.push_back(i*3),ans.push_back(Query(i*3-2,imp,crm)?i*3-1:i*3-2);
			}
		}
		sort(ans.begin(),ans.end());
		cout<<"! "<<ans.size()<<' ';
		for(int x:ans) cout<<x<<' ';
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：shucai (赞：1)

## 1617D2

首先有 $k \in (\frac{n}{3}, \frac{2n}{3})$，我们把 $n$ 分成区间 $(3,3i+1,3i+2)(i \in [0,\frac{n}{3}))$。

那么根据鸽巢原理：若每个区间都只有一个坏人，那么一共有 $\dfrac{n}{3}$ 个坏人，但他不在区间内；若每个区间都有两个坏人，那么一共有 $\dfrac{2n}{3}$ 个坏人，但他也不在区间内。这说明至少有一个区间只有 $1$ 个坏人，至少有一个区间有 $2$ 个坏人。

那么我们对每个区间都进行询问，并能找到两个相邻区间结果互异，我们对他进行处理。

我们不妨假设 $0$ 区间为 $(x,x+1,x+2)$，$1$ 区间为 $(y,y+1,y+2)$，那么我们对区间 $(x+1,x+2,y),(x+2,y,y+1)$ 进行询问。我们对他们结果进行讨论：

1. 结果为 $0\ 1$，那么 $x+1$ 为 $0$，$y+1$ 为 $1$，因为中间 $x+2,y$ 是公共的，二他们查询结果不同，前面结果会代表 $x+1$，后面代表 $y+1$。
2. 结果为 $1\ 0$，那么 $x+1$ 为 $1$，$y+1$ 为 $0$，理由同上。
3. 结果为 $1\ 1$，那么 $x$ 为 $0$，$y$ 为 $1$，因为 $x+1,x+2$ 中至少有一个 $1$，而 $(x,x+1,x+2)$ 中要有两个 $0$，那么 $x$ 必须是 $0$。而 $x+1,x+2$ 中有必有一个 $0$，而 $(x+1,x+2,y)$ 要有至少两个 $1$，那么 $y$ 必为 $1$。
4. 若结果为 $0\ 0$，那么 $x+2$ 为 $0$，$y+2$ 为 $1$，理由同上。

由上我们只问 $2$ 次就必能找出一个好人和一个坏人，我们设他们分别为 $G,B$。那么对于一个人 $x$，我们只要问 $(G,B,x)$ 就可以知道 $x$ 的身份。

我们问出 $(x,x+1,x+2),(y,y+1,y+2)$ 中每个人的身份，那么我们共用 $6$ 次就问出了该区间每个人的身份。

我们来处理剩下每个区间，我们设这个区间为 $(x,y,z)$。

对于一个区间，若它查询结果为 $0$，那么我们可以先问 $(G,x,y)$ 的结果。若为 $0$，那么 $x,y$ 都为 $1$。再查一个 $(G,B,z)$ 即可。若为 $1$，即 $x,y$ 中是有一个 $1$ 和一个 $0$，那么 $z$ 一定为 $0$，我们查一个 $(G,B,x)$ 就行了。

若该区间是 $1$，那么把 $G$ 换成 $B$ 即可，同样讨论。

这样把剩下 $\frac{n}{3}-2$ 个区间每个用两次查掉了。

则一共查了：$A=\frac{n}{3}+2 \times (\frac{n}{3}-2)+6=n+2$ 次。


---

## 作者：WRuperD (赞：0)

简单分讨交互题目。

一个自然的想法是找到一个好人和坏人。

发现题目条件 $3|n$ 和 ${n \over 3} < k < {2n\over 3}$ 非常可疑。于是果断把序列每隔 $3$ 个分一段一次询问。发现会得到至少一个坏人多的序列和至少一个坏人少的序列。这意味着这 $6$ 个人中至少是有我们想要的人的。考虑在 $7$ 次操作内找出来。谁这 $6$ 个人为 $ A,B,C,D,E,F,G$ 且在 $A,B,C$ 中有至少两个好人，$D,E,F$ 中有至少两个坏人。

---

考虑如下构造：首先我们先问询 $(A,B,D),(A,B,E),(A,B,F)$。

#### 如果结果全为 1
这也就意味着 $A,B$ 全是好人。首先 $DEF$ 中必然有两个坏人。那么我们可以考虑从中挑两个人来与 $AB$ 询问。如果结果是 $0$ 那么显然那两个都是坏人否则第三人是坏人。接下来暴力确认一下就好了。代码实现的是一个比较蠢笨的 $7$ 次询问。

#### 其他情况
这也就意味着 $A,B$ 为一个坏人一个好人。那么之前的询问结果全部有用，可以确定 $E，F，G$ 同时 $C$ 一定是好人。那么首先我们一定可以找到了确定的一个好人和一个坏人。那么我们再用两次操作暴力确定 $A,B$ 即可，用了 $5$ 次操作。


```cpp
pair <int, int> find(int a, int b, int c, int d, int e, int f){
	// abc 0 > 1 def 1 > 0
	bool fl = ask(a, b, d), fl2 = ask(a, b, e), fl3 = ask(a, b, f);
	if(fl and fl2 and fl3){
		// a = b = 0 
		ans[a] = ans[b] = 0;
		if(!ask(a, d, e)){
			ans[d] = ans[e] = 1;
			ans[f] = (ask(a, d, f) ^ 1);
			ans[c] = (ask(a, d, c) ^ 1);
			return make_pair(a, d);
		}
		else if(!ask(a, d, f)){
			ans[d] = ans[f] = 1;
			ans[e] = (ask(a, d, e) ^ 1);
			ans[c] = (ask(a, d, c) ^ 1);
			return make_pair(a, d);
		}else{
			ans[e] = ans[f] = 1;
			ans[d] = (ask(a, e, d) ^ 1);
			ans[c] = (ask(a, e, c) ^ 1);
			return make_pair(a, e);
		}
	}else{
		ans[d] = fl ^ 1;
		ans[e] = fl2 ^ 1;
		ans[f] = fl3 ^ 1;
		ans[c] = 0;
		if(ans[d]){
			ans[a] = (ask(c, d, a) ^ 1);
			ans[b] = (ask(c, d, b) ^ 1);
			return make_pair(c, d);
		}else{
			ans[a] = (ask(c, e, a) ^ 1);
			ans[b] = (ask(c, e, b) ^ 1);
			return make_pair(c, e);	
		}
	}
}

```



---

确定了一个 $0$ 和 $1$ 之后我们可以使用如下策略在  $2({n\over3}-2)$ 之内确定所有数。（不用考虑上述策略确定了的那一块所以减二。）

如果这三个数坏人多，那么我们用一个已知的好人与这个区间前两个人询问。如果结果为 $0$ 那么这两个人中就一好一坏。那么第三人一定是坏人。再查询一次即可。否则这两个人一定都是坏人，那么我们再验一下第三人的身份即可。好人多是同理的。

所以我们做完了，总的询问次数为 ${n\over3}+7+2({n\over3}-2)=n-6$ 刚刚好！


```cpp
// Problem: Too Many Impostors (hard version)
// URL: https://www.luogu.com.cn/problem/CF1617D2
// Writer: WRuperD
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
const long long inf = 1e18;
const int mininf = 1e9 + 7;
const int MAX = 2e4 + 10;
bool Ans[MAX];
bool ans[MAX];

bool ask(int a, int b, int c){
	cout << "? " << a << " " << b << " " << c << endl;
	int r;
	cin>>r;
	if(r == -1)	exit(0);
	return r; // 0 r=0 表示坏人比好人多；r=1 表示好人比坏人多；
}

pair <int, int> find(int a, int b, int c, int d, int e, int f){
	// abc 0 > 1 def 1 > 0
	bool fl = ask(a, b, d), fl2 = ask(a, b, e), fl3 = ask(a, b, f);
	if(fl and fl2 and fl3){
		// a = b = 0 
		ans[a] = ans[b] = 0;
		if(!ask(a, d, e)){
			ans[d] = ans[e] = 1;
			ans[f] = (ask(a, d, f) ^ 1);
			ans[c] = (ask(a, d, c) ^ 1);
			return make_pair(a, d);
		}
		else if(!ask(a, d, f)){
			ans[d] = ans[f] = 1;
			ans[e] = (ask(a, d, e) ^ 1);
			ans[c] = (ask(a, d, c) ^ 1);
			return make_pair(a, d);
		}else{
			ans[e] = ans[f] = 1;
			ans[d] = (ask(a, e, d) ^ 1);
			ans[c] = (ask(a, e, c) ^ 1);
			return make_pair(a, e);
		}
	}else{
		ans[d] = fl ^ 1;
		ans[e] = fl2 ^ 1;
		ans[f] = fl3 ^ 1;
		ans[c] = 0;
		if(ans[d]){
			ans[a] = (ask(c, d, a) ^ 1);
			ans[b] = (ask(c, d, b) ^ 1);
			return make_pair(c, d);
		}else{
			ans[a] = (ask(c, e, a) ^ 1);
			ans[b] = (ask(c, e, b) ^ 1);
			return make_pair(c, e);	
		}
	}
}


void solve(){
	int n;
	cin >> n;
	int mk = 0, mk2 = 0;
	for(int i = 1; i <= n; i += 3){
		Ans[i] = ask(i, i + 1, i + 2);
		if(Ans[i])	mk = i;
		else mk2 = i;
	}
	if(mk == 0 or mk2 == 0){
		puts("fukcyou");
		exit(0);
	}                                   
	auto X = find(mk, mk + 1, mk + 2, mk2, mk2 + 1, mk2 + 2);
	for(int i = 1; i <= n; i += 3){
		if(i == mk or i == mk2)	continue;
		if(Ans[i]){ // 0 > 1
			bool fll = ask(i, i + 1, X.second);
			if(fll)	{
				ans[i] = 0, ans[i + 1] = 0;
				ans[i + 2] = (ask(i + 2, X.first, X.second) ^ 1);
			}	else{
				ans[i + 2] = 0;
				ans[i] = (ask(i, X.first, X.second) ^ 1);
				ans[i + 1] = ans[i] ^ 1;
			}
		}else{
			bool fll = ask(i, i + 1, X.first);
			if(!fll)	{
				ans[i] = 1, ans[i + 1] = 1;
				ans[i + 2] = (ask(i + 2, X.first, X.second) ^ 1);
			}	else{
				ans[i + 2] = 1;
				ans[i] = (ask(i, X.first, X.second) ^ 1);
				ans[i + 1] = ans[i] ^ 1;
			}
		}
	}
	cout << "! ";
	int cntt = 0;
	for(int i = 1; i <= n; i++)	cntt += ans[i];
	cout << cntt << " ";
	for(int i = 1; i <= n; i++)	if(ans[i])	cout << i << " ";
	cout << endl;
}

signed main(){
	int t = 1;
	cin >> t;
	while(t--)	solve();
	return 0;
}
```

---

## 作者：zhanghengrui (赞：0)

思路和官方题解（以及楼上几位）差不多，不过有一点细节可以优化一下

我们找到一组 $0$ 和一组 $1$ 之后，可以再用 $5$ 次询问直接确定两组组内的所有人

怎么想到的？容易发现 $6$ 个人总共只有 $20$ 种询问，除去整组的两种只剩 $18$ 种，暴力枚举一下哪些组合能确定就好了。。。

共需要 $n + 1$ 次询问

---

枚举询问的代码：

```cpp
#include <iostream>
#include <limits>
#include <set>
#include <vector>

struct Query {
  unsigned pos[3];
  bool result = false;

  constexpr auto operator<=>(const Query &) const = default;
};

constexpr unsigned SIZE = 6;
const Query fixedQueries[]{{{0, 1, 2}, false}, {{3, 4, 5}, true}};

bool color[SIZE];

unsigned minNums = std::numeric_limits<unsigned>::max();
std::vector<std::vector<Query>> optimalQueries;

void getPossibleQueries(unsigned x, unsigned y, Query query,
                        std::vector<Query> &v) {
  if (y == 3) {
    for (const auto &q : fixedQueries) {
      if (q == query)
        return;
    }
    v.push_back(query);
    return;
  }
  if (x == SIZE)
    return;
  query.pos[y] = x;
  getPossibleQueries(x + 1, y + 1, query, v);
  getPossibleQueries(x + 1, y, query, v);
}

bool checkBasic() {
  for (const auto &query : fixedQueries) {
    unsigned cnt[2]{};
    for (unsigned i = 0; i < 3; ++i)
      ++cnt[color[query.pos[i]]];
    if ((cnt[0] < cnt[1]) != query.result)
      return false;
  }
  return true;
}

std::vector<Query> getResults(const std::vector<Query> &queries) {
  std::vector<Query> v;
  for (const auto &query : queries) {
    unsigned cnt[2]{};
    for (unsigned i = 0; i < 3; ++i)
      ++cnt[color[query.pos[i]]];
    v.push_back({query.pos[0], query.pos[1], query.pos[2], cnt[1] > cnt[0]});
  }
  return v;
}

void updateAnswer(const std::vector<Query> &queries) {
  if (queries.size() > minNums)
    return;
  std::set<std::vector<Query>> results;
  for (unsigned i = 0; i < (1 << SIZE); ++i) {
    for (unsigned j = 0; j < SIZE; ++j)
      color[j] = (i >> j) & 1;
    if (checkBasic() && !results.emplace(getResults(queries)).second)
      return;
  }
  if (queries.size() < minNums) {
    minNums = queries.size();
    optimalQueries.clear();
  }
  optimalQueries.push_back(queries);
}

int main() {
  std::vector<Query> possibleQueries;
  getPossibleQueries(0, 0, {}, possibleQueries);
  for (unsigned i = 0; i < (1U << possibleQueries.size()); ++i) {
    std::vector<Query> queries;
    for (unsigned j = 0; j < possibleQueries.size(); ++j) {
      if ((i >> j) & 1)
        queries.push_back(possibleQueries[j]);
    }
    updateAnswer(queries);
  }
  std::cout << "Minimal number of queries: " << minNums << std::endl;
  for (const auto &queries : optimalQueries) {
    bool flag = false;
    for (const auto &query : queries) {
      if (flag)
        std::cout << ", ";
      else
        flag = true;
      std::cout << '{' << query.pos[0] << ", " << query.pos[1] << ", "
                << query.pos[2] << '}';
    }
    std::cout << std::endl;
  }
  return 0;
}
```

---

这题本身的代码：

```cpp
#ifdef ONLINE_JUDGE
#define NDEBUG
#endif

#include <cassert>
#include <cstdlib>

#include <bit>
#include <iostream>
#include <limits>
#include <map>
#include <utility>
#include <vector>

class Interactor {
private:
  unsigned short n;

public:
  unsigned short getN() {
    unsigned short n;
    std::cin >> n;
    return n;
  }

  bool query(unsigned short pos1, unsigned short pos2, unsigned short pos3) {
    int result;
    std::cout << "? " << pos1 << ' ' << pos2 << ' ' << pos3 << std::endl;
    std::cin >> result;
    if (result != 0 && result != 1)
      std::exit(0);
    return result;
  }

  void answer(const std::vector<unsigned short> &v) {
    std::cout << "! " << v.size();
    for (const auto &p : v)
      std::cout << ' ' << p;
    std::cout << std::endl;
  }
} interactor;

std::vector<bool> types;

constexpr unsigned short NUM_OF_FIXED_QUERIES = 5;
constexpr unsigned short FIXED_QUERIES[NUM_OF_FIXED_QUERIES][3] = {
    {0, 1, 4}, {0, 2, 5}, {0, 3, 5}, {1, 2, 3}, {1, 3, 4}};

std::pair<unsigned short, unsigned short>
getIndicator(unsigned short first0Block, unsigned short first1Block) {
  std::map<unsigned short, unsigned short> resultToTypes;
  for (unsigned short i = 0; i < (1U << 6U); ++i) {
    unsigned short s = 0;
    if (std::popcount(i & ((1U << 3U) - 1U)) > 1 ||
        std::popcount<unsigned short>(i >> 3) < 2)
      continue;
    for (unsigned short j = 0; j < NUM_OF_FIXED_QUERIES; ++j) {
      unsigned short cnt[2]{};
      for (unsigned short k = 0; k < 3; ++k)
        ++cnt[(i >> FIXED_QUERIES[j][k]) & 1];
      if (cnt[1] > cnt[0])
        s |= (1U << j);
    }
    resultToTypes.emplace(s, i);
  }

  unsigned short s = 0;
  for (unsigned short i = 0; i < NUM_OF_FIXED_QUERIES; ++i) {
    unsigned short pos[3];
    for (unsigned short j = 0; j < 3; ++j)
      pos[j] = FIXED_QUERIES[i][j] < 3
                   ? first0Block * 3 + FIXED_QUERIES[i][j] + 1
                   : first1Block * 3 + FIXED_QUERIES[i][j] - 2;
    const auto t = interactor.query(pos[0], pos[1], pos[2]);
    if (t)
      s |= (1U << i);
  }

  assert(resultToTypes.count(s));
  const auto typesInBlocks = resultToTypes[s];
  std::pair<unsigned short, unsigned short> indicator{0, 0};
  for (unsigned short i = 0; i < 6; ++i) {
    const auto realPos =
        i < 3 ? first0Block * 3 + i + 1 : first1Block * 3 + i - 2;
    if ((typesInBlocks >> i) & 1) {
      if (!indicator.second)
        indicator.second = realPos;
    } else {
      if (!indicator.first)
        indicator.first = realPos;
    }
    types[realPos] = (typesInBlocks >> i) & 1;
  }
  assert(indicator.first && indicator.second);
  return indicator;
}

void determine(unsigned short block, bool blockType,
               std::pair<unsigned short, unsigned short> indicator) {
  const unsigned short p[3]{block * 3 + 1, block * 3 + 2, block * 3 + 3};
  if (blockType) {
    const auto s1 = interactor.query(indicator.first, p[0], p[1]);
    if (s1) {
      const auto s2 = interactor.query(indicator.first, indicator.second, p[2]);
      types[p[0]] = true;
      types[p[1]] = true;
      types[p[2]] = s2;
    } else {
      const auto s2 = interactor.query(indicator.first, indicator.second, p[0]);
      types[p[0]] = s2;
      types[p[1]] = !s2;
      types[p[2]] = true;
    }
  } else {
    const auto s1 = interactor.query(indicator.second, p[0], p[1]);
    if (s1) {
      const auto s2 = interactor.query(indicator.first, indicator.second, p[0]);
      types[p[0]] = s2;
      types[p[1]] = !s2;
      types[p[2]] = false;
    } else {
      const auto s2 = interactor.query(indicator.first, indicator.second, p[2]);
      types[p[0]] = false;
      types[p[1]] = false;
      types[p[2]] = s2;
    }
  }
}

int main() {
  unsigned short t;
  std::cin >> t;
  while (t--) {
    unsigned short n = interactor.getN(),
                   first0Block = std::numeric_limits<unsigned short>::max(),
                   first1Block = std::numeric_limits<unsigned short>::max();
    std::pair<unsigned short, unsigned short> indicator;
    std::vector<unsigned short> v;
    std::vector<bool> blockType(n / 3);
    types.resize(n + 1);
    for (unsigned short i = 0; i < n / 3; ++i) {
      blockType[i] = interactor.query(i * 3 + 1, i * 3 + 2, i * 3 + 3);
      if (blockType[i]) {
        if (first1Block == std::numeric_limits<unsigned short>::max())
          first1Block = i;
      } else {
        if (first0Block == std::numeric_limits<unsigned short>::max())
          first0Block = i;
      }
    }
    assert(first0Block != std::numeric_limits<unsigned short>::max() &&
           first1Block != std::numeric_limits<unsigned short>::max());
    indicator = getIndicator(first0Block, first1Block);
    for (unsigned short i = 0; i < n / 3; ++i) {
      if (i == first0Block || i == first1Block)
        continue;
      determine(i, blockType[i], indicator);
    }
    for (unsigned short i = 1; i <= n; ++i) {
      if (!types[i])
        v.push_back(i);
    }
    interactor.answer(v);
  }
  return 0;
}
```

---

## 作者：I_am_Accepted (赞：0)

### Preface

相信读者们都会了 Easy version 的解法了。

这题的**核心想法**在于**通过知道一对 "0+1" 后与另一个数进行询问来确定这个数的值**。

### Analysis

**下文中所有 $m$ 均指代 $\dfrac{n}{3}$。**

发现询问次数限制甚至减少了一半！考虑优化。

1. 先确定一个 $0$ 位置和一个 $1$ 位置，我们用 $m+8$ 次询问之内实现。

2. 再通过 "0+1" 组合确定剩下位置的值，用 $2(m-2)$ 次实现。

我们将人按连续 $3$ 个为一组分组，组分别编号为 $1,2,\dots,m$，我们将每组 $3$ 个都询问一遍，回答记为 $a_1,a_2,\dots,a_m$，由于 $0$ 个数的限制：

$$\exists i\in [1,m],a_i=0\land a_{i\%m+1}=1$$

我们可以通过不超过 $8$ 次知道组 $i,i+1$ 中 $6$ 个值（下文 Function A），而这之中必有 "0+1" 的组合。

我们用这一对 "0+1" 去求其他 $m-2$ 组的值，每一组只要 $2$ 次即可（下文 Function B）。

最后输出 $0$ 的个数和位置即可。

#### Function A

记这 $6$ 个连续的位置分别为 $0,1,\dots,5$，先询问 $(0,1,3)$ 和 $(0,1,4)$。若两个询问答案不等，则 $(0,1)$ 即为 "0+1"；若均为 $0$ 则确定 $(0,1)$ 均为 $0$，再通过询问 $(0,3,4)$ 即可确定 "0+1"；两个询问均为 $1$ 的情况与 $0$ 类似。不懂看代码。

确定了 "0+1" 后再 $4$ 次确定剩下的 $4$ 个位置的值，再通过她们 $4$ 个返回来确定 "0+1" 的 $0,1$ 分别对应关系。

#### Function B

我们以 $a_i=0$ 的情况为例，$a_i=1$ 与之相反对称。

类似于 Function A，记这 $3$ 个连续的位置分别为 $0,1,2$。

设 "0+1" 中 $0,1$ 分别对应 $A,B$。

先询问 $(B,1,2)$ 如果答案为 $1$ 表示 $0$ 的值必定为 $0$，再通过一次询问求出 $1,2$ 的值；如果答案为 $0$，那么 $1,2$ 的值均为 $0$，再通过一次询问求出 $0$ 的值。

### Code

[Link](https://codeforces.com/contest/1617/submission/140167999)

---

## 作者：Tyyyyyy (赞：0)

# CF1617D2
#### 题意简述
- 有 $n$ 个人（$n$ 是 $3$ 的倍数），其中有 $k$ 个是骗子（$\frac{n}{3}<k<\frac{2n}{3}$），其余人是普通人。
- 你可以进行若干次询问，如 `? a b c` 所示（要求 $a,b,c$ 互不相同且都在 $1\sim n$）。
- 作为对询问的回答，你会得到一个整数 $0$ 或 $1$。若为 $0$，表示编号为 $a,b,c$ 的三个人中，骗子多于普通人；若为 $1$，表示普通人多于骗子。
- 进行最多 $n+6$ 次询问，找到骗子的数量和所有骗子的编号。
- $6 \leq n < 10^4$，数据组数满足 $1 \leq t \leq 100$。

#### 题目分析
**请确保您已经明白 CF1617D1（本题弱化版）的基本思路。**

首先，我们的核心仍是找到两个身份不同的人，并借助他们找到其他人的身份。

本题只允许我们进行 $n+6$ 次询问，我们需要更高效地找出两个身份不同的人。注意到 $n$ 是 $3$ 的倍数，我们可以考虑将每 $3$ 个人分到一组（注意，各组之间无交集），并对每一组进行提问。

因为 $\frac{n}{3}<k<\frac{2n}{3}$，所以一定存在相邻的两组答案不同。我们设这两组为 $\{i,i+1,i+2\}$ 和 $\{i+3,i+4,i+5\}$。

考虑在这 $6$ 个人之中对相邻的 $3$ 个人进行提问（如 D1 中的做法）。因为两组的答案不同，所以必然存在一个 $j \in \{i,i+1,i+2\}$，使得 $\{j,j+1,j+2\}$ 和 $\{j+1,j+2,j+3\}$ 的答案不同。此时我们知道 $j+1$ 和 $j+2$ 身份不同，再根据 $\{j,j+1,j+2\}$ 和 $\{j+1,j+2,j+3\}$ 的答案，我们可以得到 $j$ 和 $j+3$ 的**确切身份**。

此时我们再用 $j$ 和 $j+3$ 对上面的 $i\sim i+5$ 六个人中的其他人提问，即可知道这六个人的身份。现在我们一共用掉了 $\frac{n}{3}+6$ 次询问机会，还剩下 $\frac{2n}{3}$ 次。我们需要找到其他人的身份。

考虑利用我们已经知道的信息：每一组三个人的答案。对于答案为 $0$ 的组 $\{i,i+1,i+2\}$，我们用一个已知的普通人和 $i,i+1$，$i+1,i+2$ 分别提出两次询问，即可知道这三个人的具体身份。原来答案为 $1$ 的组同理。

至此，我们使用 $n+2$ 次询问，找到了所有人的身份。

Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[10010],tot;
int ans[10010],cnt;
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		tot=0;
		for(int i=1;i<=n;i+=3)
		{
			printf("? %d %d %d\n",i,i+1,i+2);
			fflush(stdout);
			scanf("%d",&a[(i-1)/3+1]);
		}
		tot=n/3;
		int p;
		for(int i=1;i<tot;i++)
			if(a[i]!=a[i+1]){p=i;break;}
		int lst=a[p];
		int crew=0,impo=0;cnt=0;
		for(int i=p*3-1,rec;i<=p*3;i++)
		{
			printf("? %d %d %d\n",i,i+1,i+2);
			fflush(stdout);
			scanf("%d",&rec);
			if(rec!=lst)
			{	
				if(rec==0)ans[++cnt]=i+2,crew=i-1,impo=i+2;
				else ans[++cnt]=i-1,crew=i+2,impo=i-1;
				break;
			}
			lst=rec;
		}
		if(!crew&&!impo)
		{
			if(a[p+1]!=lst)
			{	
				if(a[p+1]==0)ans[++cnt]=p*3+3,crew=p*3,impo=p*3+3;
				else ans[++cnt]=p*3,crew=p*3+3,impo=p*3;
			}	
		}
		for(int i=p*3-2,rec;i<=p*3+3;i++)
		{
			if(crew==i||impo==i)continue;
			printf("? %d %d %d\n",i,crew,impo);
			fflush(stdout);
			scanf("%d",&rec);
			if(rec==0)ans[++cnt]=i;
		}
		for(int i=1;i<=tot;i++)
		{
			if(i==p||i==p+1)continue;
			int a1,a2;
			if(a[i]==0)
			{
				printf("? %d %d %d\n",i*3-2,i*3-1,crew);
				fflush(stdout);
				scanf("%d",&a1);
				if(a1==0)
				{
					ans[++cnt]=i*3-2,ans[++cnt]=i*3-1;
					printf("? %d %d %d\n",i*3,crew,impo);
					fflush(stdout);
					scanf("%d",&a2);
					if(a2==0)ans[++cnt]=i*3;
				}
				else
				{
					printf("? %d %d %d\n",i*3-1,i*3,crew);
					fflush(stdout);
					scanf("%d",&a2);
					if(a2==1)ans[++cnt]=i*3-2,ans[++cnt]=i*3;
					else ans[++cnt]=i*3-1,ans[++cnt]=i*3;
				}
			}
			else
			{
				printf("? %d %d %d\n",i*3-2,i*3-1,impo);
				fflush(stdout);
				scanf("%d",&a1);
				if(a1==1)
				{
					printf("? %d %d %d\n",i*3,crew,impo);
					fflush(stdout);
					scanf("%d",&a2);
					if(a2==0)ans[++cnt]=i*3; 
				}
				else
				{
					printf("? %d %d %d\n",i*3-1,i*3,impo);
					fflush(stdout);
					scanf("%d",&a2);
					if(a2==0)ans[++cnt]=i*3-1;
					else ans[++cnt]=i*3-2;
				}
			}
		}
		printf("! %d ",cnt);
		for(int i=1;i<=cnt;i++)printf("%d ",ans[i]);
		puts("");
		fflush(stdout);
	}
	return 0;
}
```

---

