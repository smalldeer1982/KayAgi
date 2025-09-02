# 「MCOI-09」Dream and Strings REMATCH

## 题目描述

给定 $N$ 以及非负整数序列 $a_1,a_2,\dots,a_N$。

请找到 **任何** 一个整数序列 $b_1,b_2,\dots,b_N$ 满足 $\sum |b_i|\neq 0$，$|b_i|\le 1$，和 $\sum a_ib_i=0$。

## 说明/提示

本样例不符合题意 $5000\le N$ 的限制。

**本题采用捆绑测试。**

 - Subtask 1（50 pts）：$10^5\le N$
 - Subtask 2（50 pts）：无特殊限制。

对于 $100\%$ 的数据：$1\le T\le 20$，$5000\le N\le\frac{10^5}{T}$，$0\le a_i\le 10^{18}$。**数据保证随机生成。**

## 样例 #1

### 输入

```
2
5
1 1 2 60 60
4
100 101 100 102```

### 输出

```
1 1 -1 1 -1
1 0 -1 0```

# 题解

## 作者：peterwuyihong (赞：3)

官方题解先扔这儿。

![](https://cdn.luogu.com.cn/upload/image_hosting/yoy8n1rt.png)

草，那怎么实现呢？

于是我请教了 Dead_X 奆佬，学来了以下实现：

对于每一个值，维护制造出它的位置，这个位置包含两个 set ，一个是 pos  ，代表加上这个位置的数，另一个是neg，表示减去这个位置的数。

如果发现存在两个数相同，就对这两个数的 pos，neg 保存的位置标记，直接 break ，其他默认为 $0$ 。

否则就不断合并，设 $a<b$ ，要让 $b$ 吃了 $a$ ，就在 $b$ 的 pos 集合中合并 $a$ 的 neg 集合，在 $b$ 的 neg 集合中合并 $a$ 的 pos 集合，然后将值相减。

吐槽一句，你随机生成 $10^{18}$， $131$ 个点，就没有 $-1$ 的数据？

最后：


>sto DX orz             



```cpp
#include<bits/stdc++.h>
using namespace std;
#define debug(x) cerr<<#x<<' '<<x<<endl
/* --------------- fast io --------------- */ // begin
namespace Fread {
const int SIZE = 1 << 26;
char buf[SIZE], *S, *T;
inline char getchar() {
	if (S == T) {
		T = (S = buf) + fread(buf, 1, SIZE, stdin);
		if (S == T) return '\n';
	}
	return *S++;
}
} // namespace Fread
namespace Fwrite {
const int SIZE = 1 << 26;
char buf[SIZE], *S = buf, *T = buf + SIZE;
inline void flush() {
	fwrite(buf, 1, S - buf, stdout);
	S = buf;
}
inline void putchar(char c) {
	*S++ = c;
	if (S == T) flush();
}
struct NTR {
	~ NTR() { flush(); }
} ztr;
} // namespace Fwrite
#ifdef ONLINE_JUDGE
	#define getchar Fread :: getchar
	#define putchar Fwrite :: putchar
#endif
namespace Fastio {
struct Reader {
	template<typename T>
	Reader& operator >> (T& x) {
		char c = getchar();
		T f = 1;
		while (c < '0' || c > '9') {
			if (c == '-') f = -1;
			c = getchar();
		}
		x = 0;
		while (c >= '0' && c <= '9') {
			x = x * 10 + (c - '0');
			c = getchar();
		}
		x *= f;
		return *this;
	}
	Reader& operator >> (char& c) {
		c = getchar();
		while (c == '\n' || c == ' ') c = getchar();
		return *this;
	}
	Reader& operator >> (char* str) {
		int len = 0;
		char c = getchar();
		while (c == '\n' || c == ' ') c = getchar();
		while (c != '\n' && c != ' ') {
			str[len++] = c;
			c = getchar();
		}
		str[len] = '\0';
		return *this;
	}
	Reader(){}
} cin;
const char endl = '\n';
struct Writer {
	template<typename T>
	Writer& operator << (T x) {
		if (x == 0) { putchar('0'); return *this; }
		if (x < 0) { putchar('-'); x = -x; }
		static int sta[45];
		int top = 0;
		while (x) { sta[++top] = x % 10; x /= 10; }
		while (top) { putchar(sta[top] + '0'); --top; }
		return *this;
	}
	Writer& operator << (char c) {
		putchar(c);
		return *this;
	}
	Writer& operator << (char* str) {
		int cur = 0;
		while (str[cur]) putchar(str[cur++]);
		return *this;
	}
	Writer& operator << (const char* str) {
		int cur = 0;
		while (str[cur]) putchar(str[cur++]);
		return *this;
	}
	Writer(){}
} cout;
} // namespace Fastio
#define cin Fastio :: cin
#define cout Fastio :: cout
#define endl Fastio :: endl
/* --------------- fast io --------------- */ // end
#define int long long
#define maxn 100010
struct stO_DX_Orz{
	set<int>pos,neg;//加法标记，减法标记 
	int d;
	bool operator<(const stO_DX_Orz x)const{return d<x.d;}
}a[maxn];
int ans[maxn];
stO_DX_Orz merge(stO_DX_Orz a,stO_DX_Orz b){
	for(int i:b.pos)a.neg.insert(i);
	for(int i:b.neg)a.pos.insert(i);
	a.d-=b.d;
	return a;
}
int n,T; 
signed main(){
#ifndef ONLINE_JUDGE
	freopen("testdata.in","r",stdin);
#endif
	for(cin>>T;T;T--){
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a[i].d;
			a[i].pos.clear();//多测不清空 
			a[i].neg.clear();//* * 两行泪 
			a[i].pos.insert(i);
			ans[i]=0;//先默认为0 
		}
		int tmp=n;
		while(n){
			int o=n>>1;
			bool F=0;
			sort(a+1,a+n+1);//排序 
			for(int i=1;i<=o;i++)
			if(a[i*2-1].d==a[i<<1].d){
				F=1;//出现两个一样直接标记然后其他默认0结束了 
				for(int j:a[i*2-1].pos)ans[j]=1;
				for(int j:a[i*2-1].neg)ans[j]=-1;
				for(int j:a[i*2].pos)ans[j]=-1;
				for(int j:a[i*2].neg)ans[j]=1;
			}
			if(F)break;
			for(int i=1;i<=o;i++)a[i]=merge(a[i*2],a[i*2-1]);
			n>>=1;//↑否则合并两个，各种互换标记 
		}
		for(int i=1;i<=tmp;i++)cout<<ans[i]<<' ';
		cout<<endl;
		//也不知道咋随机的，数据莫得无解 
	}
#ifndef ONLINE_JUDGE
	cerr<<endl<<(double)clock()/CLOCKS_PER_SEC;
#endif
}
```


---

