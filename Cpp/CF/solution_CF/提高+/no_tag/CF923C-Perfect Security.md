# Perfect Security

## 题目描述

Alice has a very important message $ M $ consisting of some non-negative integers that she wants to keep secret from Eve. Alice knows that the only theoretically secure cipher is one-time pad. Alice generates a random key $ K $ of the length equal to the message's length. Alice computes the bitwise xor of each element of the message and the key (![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF923C/e682f428388c1821c0c087d86489287fdf087075.png), where ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF923C/bc47da33894a98df53134f30108d8405a90ea418.png) denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)) and stores this encrypted message $ A $ . Alice is smart. Be like Alice.

For example, Alice may have wanted to store a message $ M=(0,15,9,18) $ . She generated a key $ K=(16,7,6,3) $ . The encrypted message is thus $ A=(16,8,15,17) $ .

Alice realised that she cannot store the key with the encrypted message. Alice sent her key $ K $ to Bob and deleted her own copy. Alice is smart. Really, be like Alice.

Bob realised that the encrypted message is only secure as long as the key is secret. Bob thus randomly permuted the key before storing it. Bob thinks that this way, even if Eve gets both the encrypted message and the key, she will not be able to read the message. Bob is not smart. Don't be like Bob.

In the above example, Bob may have, for instance, selected a permutation $ (3,4,1,2) $ and stored the permuted key $ P=(6,3,16,7) $ .

One year has passed and Alice wants to decrypt her message. Only now Bob has realised that this is impossible. As he has permuted the key randomly, the message is lost forever. Did we mention that Bob isn't smart?

Bob wants to salvage at least some information from the message. Since he is not so smart, he asks for your help. You know the encrypted message $ A $ and the permuted key $ P $ . What is the lexicographically smallest message that could have resulted in the given encrypted text?

More precisely, for given $ A $ and $ P $ , find the lexicographically smallest message $ O $ , for which there exists a permutation $ π $ such that ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF923C/de5bfee0996493336b3c6a243dac127c9ce9ab1e.png) for every $ i $ .

Note that the sequence $ S $ is lexicographically smaller than the sequence $ T $ , if there is an index $ i $ such that $ S_{i}&lt;T_{i} $ and for all $ j&lt;i $ the condition $ S_{j}=T_{j} $ holds.

## 说明/提示

In the first case, the solution is $ (10,3,28) $ , since ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF923C/17e05ed9460ddec1d5b18884e347be7ab250027f.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF923C/192332f82ce7694a9d2edf310b6f1dcd5c1423c7.png) and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF923C/b997ec85123f2441d408438ac0f17abfac65319e.png). Other possible permutations of key yield messages $ (25,6,10) $ , $ (25,3,15) $ , $ (10,21,10) $ , $ (15,21,15) $ and $ (15,6,28) $ , which are all lexicographically larger than the solution.

## 样例 #1

### 输入

```
3
8 4 13
17 2 7
```

### 输出

```
10 3 28
```

## 样例 #2

### 输入

```
5
12 7 87 22 11
18 39 9 12 16
```

### 输出

```
0 14 69 6 44
```

## 样例 #3

### 输入

```
10
331415699 278745619 998190004 423175621 42983144 166555524 843586353 802130100 337889448 685310951
226011312 266003835 342809544 504667531 529814910 684873393 817026985 844010788 993949858 1031395667
```

### 输出

```
128965467 243912600 4281110 112029883 223689619 76924724 429589 119397893 613490433 362863284
```

# 题解

## 作者：灵乌路空 (赞：7)

先无良宣传一下博客wwwwww  
[文章列表 - 核融合炉心 - 洛谷博客](https://www.luogu.org/blog/koishikoishi/)

------------

## 知识点:Trie树/字典树/贪心 

- ### 题意:

###### ~~(简略版的题干太鬼畜了)~~
有$a,b$ 两长度为 $n$ 的数列 ,   
将 $b$ 数列进行重新排列,  
然后使 $a,b$ 对应位置的数相 $\underline{\text{异或}}$ ,  
得到一个新数列$c$

求能使新数列 $c$  $\underline{\text{字典序最小}}$ 的方案  
并输出此方案的结果

$1\leqslant N \leqslant 3e5$   
$\underline{a[i],b[i] \leqslant 2^{30}}$

------------


- ### 分析题意 :  
    
  - 字典序最小 :   
    则 $c$ 数列的各位置 $c[i]$ ,  
    都应该是能达到的最小的值      
    就可以考虑贪心  
    
  - 异或 , $a[i],b[i] \leqslant 2^{30}$ :  
    为什么数据范围要写成这个样子?  
    再考虑异或运算...  
    想到进行二进制拆分   
   	
    将 $a[i],b[i]$ 拆分后 ,   贪心就可以方便地进行  
    枚举两 $01$ 串上 每一位上的数  
    尽量使 各位 相异 或后为 $0$  
    即可选择出最合适的 $b[i]$
    
    
  - 用什么来维护 拆分后的二进制数 ?   
    可以将二进制数  
    当成字符串来处理    
    想到建立一棵字典树  
    由于只有 $0,1$ 两字符,所以是一棵二叉树  
    根据 字典树 的性质 ,   
    可以很方便地完成上述操作 .  
    
------------

  
- ### 算法实现:

  先建立一棵基于各 $b[i]$ 的二进制数 的字典树  
  并记录 各节点代表的 元素出现的个数 $cnt$  
  
  每次查询操作 , 将 $a[i]$ 作参数进行传递  
  从字典树根部 , 开始向下查找 ,   
  查找每一层 (即每一二进制位) 的元素 ,   
  都尽量使 $a[i],b[i]$ 此二进制位相异或为 $0$  
  若最优元素在此位置个数为 $0$ ,选择另一元素  
  使此位置选择的元素数量 $-1$  
  并进入下一层 , 继续进行查找 .

  根据字典树的性质 ,   
  每次查询操作 必然可以找到,  
  一个满足局部最优的 , 最适合 $a[i]$ 的 $b[i]$  
  查询 $n$ 次后 , 即可找到最优的答案
  
- ### 注意的点:  
  
  为方便运算 ,   
  要保证 字典树 中 ,   
  二进制数按照正向存储  
  
  也就是说,
  如果使用位运算符进行二进制拆分  
  要先拆出高位 , 再拆出低位  
  详见代码
   
------------

附上 ~~奇丑~~ 的代码:

```cpp
#include<cstdio>
#include<ctype.h>
#include<algorithm>
#define int long long
//==================================================
const int MARX = 3e5+10;
struct node
{
	int cnt,son[2];//存每个节点代表元素出现次数 , 两儿子 
}trie[20*MARX];
int n,num=1;
int a[MARX],b[MARX];//原始数列 
//==================================================
inline int read()
{
	int fl=1,w=0;char ch=getchar();
	while(!isdigit(ch) && ch!='-') ch=getchar();
	if(ch=='-') fl=-1;
	while(isdigit(ch)){w=w*10+ch-'0',ch=getchar();}
	return fl*w;
}
inline void insert(int key)//建树 
{
	int now=1;//从根节点开始,向下查找 
	trie[1].cnt++;
	for(int i=30;i>=0;i--)//将二进制数正向加入字典树 
	{
		int next=(key>>i)&1; //当前位数 
		if(!trie[now].son[next]) trie[now].son[next]= ++num;//添加新节点 
		now=trie[now].son[next];
		trie[now].cnt++;//增加出现次数 
	}
}
inline int query(int key)//回答询问 
{
	int now=1,ans=0;//从根部查找 
	for(int i=30;i>=0;i--) 
	{
		int next=(key>>i)&1;//最优情况 
		if(!trie[trie[now].son[next]].cnt) next=(!next);//不能满足最优情况 
		ans=(ans<<1)+next;//更新找到的 b[i] 
		now=trie[now].son[next];
		trie[now].cnt--;//减少出现次数 
	}
	return ans^key;
}
//==================================================
signed main()
{
	n=read();
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=1;i<=n;i++) b[i]=read(),insert(b[i]); 
	for(int i=1;i<=n;i++) printf("%lld ",query(a[i]));
}
```

---

## 作者：Super_Cube (赞：1)

# Solution

为了让异或后得到的序列字典序最小，从前往后逐个位置进行最小化是毫无疑问的。

由于 $b$ 序列可以任意打乱，那先把 $b$ 中所有元素插入 0/1 Trie 树中，然后遍历 $a$ 中的每个元素去 Trie 上跑，如果二进制下与当前位相同的地方有值就往那边走，这样异或出的结果该位为 $0$，否则往另一边走，答案加上二的幂次。

记得走完一个元素后要把刚刚走出的 $b_i$ 在 Trie 上消除掉。

# Code

```cpp
#include<bits/stdc++.h>
struct Trie{
	int nxt[9000005][2];
	int cnt[9000005];
	int idx;
	inline void insert(int x){
		static int p;p=0;
		for(int i=29;~i;--i){
			if(!nxt[p][x>>i&1])nxt[p][x>>i&1]=++idx;
			++cnt[p=nxt[p][x>>i&1]];
		}
	}
	inline int ask(int x){
		static int p,res;p=0;res=0;
		for(int i=29;~i;--i){
			if(cnt[nxt[p][x>>i&1]])p=nxt[p][x>>i&1];
			else res|=1<<i,p=nxt[p][~x>>i&1];
			--cnt[p];
		}
		return res;
	}
}trie;
int a[300005];
int n;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;scanf("%d",&a[i++]));
	for(int i=1,x;i<=n;++i)
		scanf("%d",&x),trie.insert(x);
	for(int i=1;i<=n;++i)
		printf("%d ",trie.ask(a[i]));
	return 0;
}
```

---

## 作者：_Wind_Leaves_ShaDow_ (赞：1)

有蓝？建议降绿或者黄。

字典序问题贪心即可，越前面的越小越好。

$a_i$ 固定，所以问题变为对于当前 $a_i$，在未选择的 $b$ 中挑一个 $b_j$，使得 $a_i\oplus b_j$ 最小。

显然的 01-trie 问题。不会或者没做过的可以去做 [这题](https://www.luogu.com.cn/problem/P4551)。查询答案时从高往低位贪心取和当前二进制位相同的一位可以让得到的结果尽量小。

你谷最近交不了 CF，[这是过题记录](https://codeforces.com/contest/923/submission/277622099)。

```cpp
#include <bits/stdc++.h>
#define int long long
#define Rg register
#define Ri Rg int
#define Il inline
#define vec vector
#define pb push_back
#define fi first
#define se second
#define IT ::iterator

using namespace std;

typedef double db;
//typedef long long ll;
typedef pair<int,int> pii;
const int N=3e5,Inf=1e9;
const db eps=1e-9;

int n,a[N+5],b[N+5];
int pid=0,ch[N*31+5][2],c[N*31+5];

Il void ins(int x){
	int p=0;
	for(Ri i=30;~i;i--){
		int t=(x>>i)&1;
		if(!ch[p][t])ch[p][t]=++pid;
		p=ch[p][t];
		c[p]++;
	}
	return;
}

Il int qmn(int x){
	int p=0,ans=0;
	for(Ri i=30;~i;i--){
		int t=(x>>i)&1;
		if(c[ch[p][t]])p=ch[p][t];
		else p=ch[p][t^1],ans+=(1ll<<i);
		c[p]--;
	}
	return ans;
}

signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n;
	for(Ri i=1;i<=n;i++)cin>>a[i];
	for(Ri i=1;i<=n;i++)cin>>b[i],ins(b[i]);
	for(Ri i=1;i<=n;i++)cout<<qmn(a[i])<<' ';
	return 0;
}
```

---

## 作者：endswitch (赞：1)

## 题意

有长度为 $n$ 的数列 $a,b$，将数列 $b$ 重新排列，使得数列 $c$ 字典序最小，$c_i = a_i \oplus b_i(1 \le i \le n)$。

## 思路

**异或、最小**这两个关键字眼提醒我们此题是可以朝着 01 trie 的方向去思考的。

要使 $c$ 序列字典序最小，那么越靠前的元素就一定越小，于是我们可以贪心地去做元素的查询。

那么应该如何查询呢？由于异或的性质，我们还是去贪心，每次从高位往低位尽量选和 $a_i$ 二进制下相同的一位，01 trie 可以很好的维护。

时间复杂度 $O(n\log V)$，其中 $\log V$ 是跑满的。

代码：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 3e5 + 5;
int n, x, a[N];

namespace _01trie {
	const int V = 31;
	int tot;
	struct Trie {
		int sz, cnt, ch[2];
		
		inline int operator [] (const bool x) const {
			return ch[x];
		}
	} t[N << 5];
	
	inline void insert(int x) {
		int p = 0;
		
		for(int i = V - 1 ; ~ i ; -- i) {
			bool w = x & (1 << i);
			
			if(! t[p][w]) t[p].ch[w] = ++ tot;
			
			p = t[p][w], 	++ t[p].cnt;
		}
	}
	
	inline int query(int x) {
		int p = 0, res = 0;
		
		for(int i = V - 1 ; ~ i ; -- i) {
			bool w = x & (1 << i);
			
			if(! t[t[p][w]].cnt) w ^= 1;
			
			res = (res << 1) | w;
			
			p = t[p][w];
			
			-- t[p].cnt;
		}
		
		return res ^ x;
	}
}

using namespace _01trie;

signed main() {
	ios_base :: sync_with_stdio(NULL);
	cin.tie(nullptr);
	cout.tie(nullptr);
	
	cin >> n;
	for(int i = 1 ; i <= n ; ++ i)
		cin >> a[i];
	for(int i = 1 ; i <= n ; ++ i) {
		cin >> x;
		
		insert(x);
	}
	
	for(int i = 1 ; i <= n ; ++ i)
		cout << query(a[i]) << ' ';
	
	return 0;
}
```

---

## 作者：_JF_ (赞：1)

[CF923C Perfect Security](https://www.luogu.com.cn/problem/CF923C)

题目意思很简洁。

我们考虑需要结果的字典序最小，考虑贪心，其实就是我们考虑对于当前的 $i$，找到剩下的一个 $P_j$，满足 $a_i \oplus P_j$ 最小即可。

我们考虑使用字典树来模拟这个过程，具体的，对每个位置开桶维护当前位置是否还有数。

很显然，如果对应的 $0$ 没有数，那就只能走 $1$，如果 $1$ 没有，我们只能走 $0$。我们可以发现，在任意时刻必然不会出现 $0,1$ 都没有数的情况。

如果对应的 $0,1$ 都有数，那么如果 $a_i$ 的第 $x$ 位是 $1$，我们选择走 $1$，反之走 $0$。

也就是对当前位的贪心，这个显然也是对的。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N =3e5+10;
int n,ch[N*31][3],Tot[N*31],tot,a[N],b[N],sum;
void build(int x){
	int p=0;
	for(int i=30;i>=0;i--){
		int now=x>>i&1;
		if(ch[p][now]==0)	ch[p][now]=++tot;
		p=ch[p][now],Tot[p]++;
//		cout<<now<<" ";
	}
//	cout<<endl;
}
void Slove(int x,int num,int p){
	if(num==-1)	return ;
	int now=x>>num&1;
	if(Tot[ch[p][1]]==0)	{Slove(x,num-1,ch[p][0]),Tot[ch[p][0]]--; return ;}
	else if(Tot[ch[p][0]]==0)	{sum+=(1<<num),Slove(x,num-1,ch[p][1]),Tot[ch[p][1]]--; return ;}
	if(now==1)	sum+=(1<<num),Slove(x,num-1,ch[p][1]),Tot[ch[p][1]]--;
	else	Slove(x,num-1,ch[p][0]),Tot[ch[p][0]]--;	
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)	cin>>a[i];
	for(int i=1;i<=n;i++)	cin>>b[i],build(b[i]);
	for(int i=1;i<=n;i++)
		sum=0,Slove(a[i],30,0),cout<<(a[i]^sum)<<" ";
	return 0;
} 
```

---

## 作者：COsm0s (赞：0)

我们抓住题目中两个重点：**异或、字典序最小**。


------------

我们知道，对于一个数列，它越靠前的数越小，其字典序越小，比如 `1 7777 8888` 的字典序小于 `2 2 2`。

那么反推至一个数，它在二进制位上越靠前的 $1$ 越少，其字典序越小。


------------

异或我们通常用 `01 trie` 来处理。

按照刚才的思路，我们从 $a_1$ 开始枚举，每一次贪心地找到与 $a_i$ 异或后最小的数，然后将其删去。容易发现，在这种处理下，越靠前的 $c_i$ 越小，也就满足字典序最小。

复杂度 $\Theta(n\log V)$，$V$ 是值域。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int Depth = 31;
const int N = 3e5 + 5;
struct _01trie {
	struct node {
		int ch[2];
		int siz, cnt;
	} T[N << 4];
	int p;
	void update(int x) {
		int u = 0;
		for (int i = Depth - 1; ~i; i --) {
			bool b = (x & (1 << i));
			if (T[u].ch[b] == 0)
				T[u].ch[b] = ++ p;
			u = T[u].ch[b], T[u].cnt ++;
		}
	}
	
	int query(int x) {
		int u = 0, ans = 0;
		for (int i = Depth - 1; ~i; i --) {
			bool b = (x & (1 << i));
			if (!T[T[u].ch[b]].cnt) {
				ans = ans << 1 | (b ^ 1);
				u = T[u].ch[b ^ 1];
				T[u].cnt --;
			} else {
				ans = ans << 1 | b;
				u = T[u].ch[b];
				T[u].cnt --;
			}
		}
		return ans ^ x;
	}
} Trie;

int n, u, m;
int a[N], b[N];

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cin >> n;
	for(int i = 1; i <= n; i ++) cin >> a[i];
	for(int i = 1; i <= n; i ++) cin >> b[i], Trie.update(b[i]);
	for(int i = 1; i <= n; i ++) cout << Trie.query(a[i]) << ' ';
	return 0;
}

```


---

## 作者：IkunTeddy (赞：0)

# 题目大意
这个翻译是真的读不懂，所以这里放上题目大意。

给你一个数组 $a$ 和数组 $p$。将 $p$ 打乱后，定义数组 $c$，使得 $c_i=a_i\oplus p_i$，求字典序最小的 $c$。

# 题目分析
这里看到有异或操作，我们自然按位考虑。能求最小异或和的数据结构很明显就是 01-Trie。我们将 $p_i$ 插入 Trie 中，遍历 $a$ 时在 Trie 中贪心地去找n能使 $c_i$ 最小的 $p_i$ 即可。在查找过程中，设 $a_i$ 当前二进制位的值为 $f$。先看 $son[f]$ 的子树中是否有某个 $p_i$，有直接下去，没有就去 $son[f\oplus1]$ 的子树中找，这样一直找到叶子就能得到最小值。找完后把找到的 $p_i$ 从 Trie 中删除即可。这个题就被我们切掉了。

# Code
```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=9e6+10;
int a[maxn],p[maxn],l=31;
struct node{
	int son[2];
	int cnt;
}tree[maxn];
int rt,cnt;
void update(int &v,int x,int p,int k){
	if(!v)v=++cnt;
	tree[v].cnt+=k;
	if(!p)return ;
	int c=(x>>p-1)&1;
	update(tree[v].son[c],x,p-1,k);
}
int ask(int v,int x,int p){
	if(!p)return 0;
	int chk=(x>>p-1)&1;
	if(tree[tree[v].son[0^chk]].cnt){
		return ((0^chk)<<p-1)+ask(tree[v].son[0^chk],x,p-1);
	}else{
		return ((1^chk)<<p-1)+ask(tree[v].son[1^chk],x,p-1);
	}
}
int main(){
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
	}
	for(int i=1;i<=n;i++){
		scanf("%d",&p[i]);
		update(rt,p[i],l,1);
	}
	for(int i=1;i<=n;i++){
		int x=ask(rt,a[i],l);
		printf("%d ",x^a[i]);
		update(rt,x,l,-1);
	}

	return 0;
}

```


---

