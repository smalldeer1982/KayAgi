# [ARC127C] Binary Strings

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc127/tasks/arc127_c

すぬけくんは黒板に $ 1 $ 以上 $ (2^N-1) $ 以下の整数をすべて書きました． ただし，整数は $ 2 $ 進表記で書きました．

黒板に書かれた整数を文字列として見た時，辞書順で $ X $ 番目に小さい文字列を求めてください．

なお，入力において $ N $ は $ 10 $ 進法で与えられますが，$ X $ は $ 2 $ 進法で与えられます．

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 10^6 $
- $ 1\ \leq\ X\ \leq\ 2^N-1 $
- $ X $ は $ 2 $ 進法で与えられる．

### Sample Explanation 1

黒板に書かれた文字列を辞書順に並べると，`1`,`10`,`100`,`101`,`11`,`110`,`111` です． また $ X=101(2\mathrm{進})=5(10\mathrm{進}) $ です． よって，答えは `11` になります．

## 样例 #1

### 输入

```
3
101```

### 输出

```
11```

## 样例 #2

### 输入

```
10
10100011```

### 输出

```
1001001111```

## 样例 #3

### 输入

```
1000000
11111```

### 输出

```
1000000000000000000000000000000```

# 题解

## 作者：cjh20090318 (赞：5)

## 题意

给出 $n,x$，请求出二进制下 $[1,2^n-1]$ 中字典序第 $x$ 小的数是什么。

## 分析

从样例观察出每一个数的第一个字符都是 $1$，然后画出 $n=3$ 的树。

![](https://cdn.luogu.com.cn/upload/image_hosting/1bmpfrpo.png)



节点即第 $x$ 小的终止位置，边权从上到下依次表示二进制位。

顺着树从上往下，设当前节点在第 $i$ 层（$1$ 为第 $1$ 层），依次判断：

- 当 $x=1$ 时，跳出循环。
- 如果 $x > 2^{n-i}$ 时，$x \gets x-2^{n-i}$，进入右子树并输出 $1$。
- 否则 $x \gets x-1$，进入左子树并输出 $0$。

用 `std::bitset` 模拟即可，具体实现看代码。

## 代码

```cpp
//the code is from chenjh
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<bitset>
#define MAXN 1000005
using namespace std;
int n,m;
char s[MAXN];
bitset<MAXN> b;
int main(){
	scanf("%d ",&n);
	int c=0;//维护 popcount。
	scanf("%s",s),m=strlen(s),reverse(s,s+m);//翻转最低位和最高位。
	for(int i=0;i<n;i++) c+=(b[i]=s[i]?s[i]^'0':0);
	putchar('1');
	for(int i=n-1;i>=0;--i){
		if(c==1&&b[0]) break;//只有 1 个位置为 1 且为第 0 位，即说明 x=1。
		else if(b[i]&&c>1) b[i]=b[i]^1,--c,putchar('1');//严格大于（不止该位为 1）。
		else{
			int x=b._Find_first();//找到最低位为 1 的。
			for(int i=0;i<x;i++) b[i]=1,++c;//减 1 操作。
			b[x]=0,--c;
			putchar('0');
		}
	}
	return 0;
}
```

---

## 作者：rizynvu (赞：4)

[我的博客](https://www.cnblogs.com/rizynvu/p/18296386)。

首先考虑把 $x$ 补成 $n$ 位的。  
然后考虑对 $x\leftarrow x - 1$，这样子相当于可以考虑成还要变大 $x$ 次才是答案。

然后考虑从开头一位一位来确定。  
首先第一位肯定有个 $1$。  
接下来考虑第 $2$ 位，分讨一下第 $2$ 位的情况：  

1. 第 $2$ 位为空（即答案就为 $1$），此时一定有 $x = 0$。
2. 第 $2$ 位为 $0$，考虑如果知道第 $2$ 位为 $0$ 后后面的填法还有多少种选择。  
   这部分数量可以表示为 $\sum\limits_{i = 0}^{n - 2} 2^i$，即枚举除掉第二位剩余长度 $i$，那么这 $i$ 项可以任意填。  
   易知这部分的数量为 $2^{n - 1} - 1$。  
   那么对于 $x$ 的限制就是 $0 < x < 2^{n - 1}$。
3. 第 $2$ 位为 $1$，根据上面可以得出 $x\ge 2^{n - 1}$，那么选上 $1$ 后就要排除掉 $2^{n - 1}$ 种（$2^{n - 1} - 1$ 种来自第 $2$ 位为 $0$，还有 $1$ 种来自答案为 $11$）。

类似的，发现这个选择对于第 $i(i\ge 2)$ 位都成立。

于是接下来就只需要去实现给定二进制数 $-1$ 或是把 $x$ 位变为 $0$ 的操作了。  
对于位变为 $0$，直接做就可以了。  
对于二进制数 $-1$，这里考虑到实际上会遍历的位数是 $1, 2, 1, 3, 1, 2, 1, 4,\cdots$ 这样的，即第 $i$ 位对应的遍历位数为其二进制下后缀 $0$ 的个数 $+1$，那么做 $n$ 次遍历的位数其实是 $\sum\limits_{i = 1}^{\lfloor\log_2 n\rfloor} \lfloor\frac{n}{2^i}\rfloor < 2n$ 的，所以直接暴力做就行了。

时间复杂度 $\mathcal{O}(n)$。

```cpp
#include<bits/stdc++.h>
int main() {
   int n; std::string s;
   std::cin >> n >> s;
   reverse(s.begin(), s.end());
   for (; s.size() < n; s += '0');
   int hd = 0; while (s[hd] == '0') hd++;
   auto del = [&]() {
      for (int i = 0; i <= hd; i++) s[i] ^= 1;
      for (hd = 0; hd < n && s[hd] == '0'; hd++);
   };
   std::string ans = "1";
   del();
   for (int i = n - 1; hd < n; i--) {
      if (s[i] == '1') {
         s[i] = '0', ans += '1';
         if (hd == i) hd = n;
      } else {
         ans += '0';
         del();
      }
   }
   std::cout << ans;
   return 0;
}
```

---

## 作者：uid_310801 (赞：4)

#### 题面补充

这里的 $x$ 和输出都是二进制格式的。

#### 解题思路

研究一下样例 1，将数按字典序从小到大写出来：

1. $1$  
2. $10$  
3. $100$  
4. $101$  
5. $11$  
6. $110$  
7. $111$  

发现了一些规律：

- **从高往低**第一位是 $1$（废话）。
- 对于第二位来说，排名第一的是“结束符”，排名第二到四的该位是 $0$，剩下的是 $1$。

第二条规律归纳总结一下就是：

- **从低往高**数第 $i$ 位，排名第一的该位为“结束符”，排名第 $2$ 到第 $2^i$ 的该位是 $0$，剩下的是 $1$。 

这样思路就明了了，**从高往低**判断每一位，设当前考虑到第 $i$ 位，如果排名为 $1$ 则结束，否则如果排名小于等于 $2^{n-i}$，则该位填 $0$，并将排名减 $1$。否则该位填 $1$，将排名减 $2^{n-i}$。

直接用高精减法来做就行。不难证明暴力减复杂度是对的。

小细节：

- 判断排名是否小于 $2^{n-i}$ 时，直接看位数就行。
- 判断排名是否等于 $2^{n-i}$ 时，可以通过存 $1$ 的数量，来判断是否满足条件。
- 如果你的写法退位操作会超时，可以用数组开头存低位，后面存高位的方法来避免。

#### 代码（很丑不要在意）

```cpp
#include<bits/stdc++.h>
using namespace std;
//#define int long long
typedef long long ll;
const ll N=1e6+10;
ll n,a[N],top,cnt;
char str[N];
string ans;
signed main(){
	scanf("%lld",&n);
	scanf("%s",str);
	top=strlen(str);
	for(int i=1;i<=top;i++){
		a[i]=str[top-i]-'0';
		if(a[i]==1)	cnt++;
	}
	ans="1";
	while(top>1){
		if(top<n||(top==n&&cnt==1)){
			ll nw=1;
			while(a[nw]==0){
				nw++;
			}
			a[nw]=0;
			cnt--;
			for(int i=nw-1;i>=1;i--){
				a[i]=1;
				cnt++;
			}
			ans+='0';
		}
		else{
			a[top]=0;	
			cnt--;
			ans+='1';
		}
		while(a[top]==0)	top--;
		n--;
	}
	cout<<ans<<endl;
	return 0;
}
/*
exSample:

*/
```


---

## 作者：DeepSeaSpray (赞：0)

# [ARC127C] Binary Strings

手玩一下样例，发现是一个按层编号的满二叉树上求先序遍历第 $K$ 位的问题。

如果你手玩不出来，可以画一颗 Trie 然后删除前导 $0$。

实现上设当前层数为 $X$，节点编号为 $V$：

- $K = 1$，输出 $V$。
- $K - 1 \leq 2^X - 1$，$K$ 减 $1$，$V$ 乘 $2$。
- 否则 $K$ 减去 $2^X$，$V$ 乘 $2$ 加 $1$。

减 $1$ 暴力减，操作位数与次数平均不会超过 $\log N$。

判断需要维护 popcount（$1$ 的个数）。

具体看代码。

[完整代码](https://atcoder.jp/contests/arc127/submissions/49644033)

---

## 作者：shinkuu (赞：0)

很有意思的题。

考虑每一个位置选 $1/0$ 对排名的贡献。设当前数为 $x$，如果选 $0$，此数的排名为 $x$ 的排名 $+1$，否则，发现全部改为选 $0$ 的情况，排名都会在此数前面，则会将排名 $+2^{k+1}$，$k$ 为该位置为从低到高第几位。

所以，我们可以从高位开始枚举，每次能取 $1$ 就取，相当于每次将要求排名减去一个数。容易发现，如果取 $1$，要求排名对应位置一定也是 $1$，于是将那一位变为 $0$ 即可。否则，将排名 $-1$ 的操作相当于将一段为 $0$ 的后缀全部变成 $1$ 并将前一位变为 $0$。

这个操作很容易用线段树维护。直到排名的 $01$ 序列全为 $0$ 时停止。

看了标程好像暴力修改有复杂度保证，感兴趣的可以去看看。

code：

```cpp
int n,m,e[N];
int tr[N<<2],tag[N<<2];
char s[N];
vector<int> vec;
inline void pushup(int o){
	tr[o]=tr[o<<1]|tr[o<<1|1];
}
inline void pushdown(int l,int r,int o){
	if(tag[o]==-1){
		return;
	}
	tr[o<<1]=tag[o],tr[o<<1|1]=tag[o];
	tag[o<<1]=tag[o],tag[o<<1|1]=tag[o];
	tag[o]=-1;
}
void build(int l,int r,int o){
	tag[o]=-1;
	if(l==r){
		tr[o]=e[l];
		return;
	}
	int mid=(l+r)>>1;
	build(l,mid,o<<1);
	build(mid+1,r,o<<1|1);
	pushup(o);
}
int query_l(int l,int r,int o){
	if(l==r){
		if(tr[o]){
			return l;
		}
		return -1;
	}
	pushdown(l,r,o);
	int mid=(l+r)>>1;
	if(tr[o<<1]){
		return query_l(l,mid,o<<1);
	}
	return query_l(mid+1,r,o<<1|1);
}
int query_r(int l,int r,int o){
	if(l==r){
		if(tr[o]){
			return l;
		}
		return -1;
	}
	pushdown(l,r,o);
	int mid=(l+r)>>1;
	if(tr[o<<1|1]){
		return query_r(mid+1,r,o<<1|1);
	}
	return query_r(l,mid,o<<1);
}
void update(int l,int r,int o,int x,int y,int k){
	if(l>=x&&r<=y){
		tr[o]=k;
		tag[o]=k;
		return;
	}
	pushdown(l,r,o);
	int mid=(l+r)>>1;
	if(x<=mid){
		update(l,mid,o<<1,x,y,k);
	}
	if(y>mid){
		update(mid+1,r,o<<1|1,x,y,k);
	}
	pushup(o);
}
void solve(){
	scanf("%d%s",&n,s+1);
	m=strlen(s+1);
	for(int i=1;i<=n-m;i++){
		e[i]=0;
	}
	for(int i=1;i<=m;i++){
		e[i+n-m]=s[i]-'0';
	}
	build(1,n,1);
	vec.push_back(1);
	for(int i=2;i<=n;i++){
		int x=query_l(1,n,1),y=query_r(1,n,1);//线段树上二分找左/右第一个1
		if(x==y&&y==n){
			break;
		}//当前要求排名为1，结束
		if(x<i&&x!=y){
			vec.push_back(1);
			update(1,n,1,x,x,0);
		}else{
			vec.push_back(0);
			if(y==n){
				update(1,n,1,n,n,0);
			}else{
				update(1,n,1,y,y,0);
				update(1,n,1,y+1,n,1);
			}
		}
	}
	for(int i:vec){
		printf("%d",i);
	}
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)solve();
}
```

---

