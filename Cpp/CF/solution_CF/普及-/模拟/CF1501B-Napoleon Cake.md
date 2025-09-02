# Napoleon Cake

## 题目描述

This week Arkady wanted to cook some pancakes (to follow ancient traditions) and make a problem about that. But then he remembered that one can't make a problem about stacking pancakes without working at a specific IT company, so he decided to bake the Napoleon cake instead.

To bake a Napoleon cake, one has to bake $ n $ dry layers first, and then put them on each other in one stack, adding some cream. Arkady started with an empty plate, and performed the following steps $ n $ times:

- place a new cake layer on the top of the stack;
- after the $ i $ -th layer is placed, pour $ a_i $ units of cream on top of the stack.

When $ x $ units of cream are poured on the top of the stack, top $ x $ layers of the cake get drenched in the cream. If there are less than $ x $ layers, all layers get drenched and the rest of the cream is wasted. If $ x = 0 $ , no layer gets drenched.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1501B/d2a848de33f21319239069b9694ee652ecb320b0.png)The picture represents the first test case of the example.Help Arkady determine which layers of the cake eventually get drenched when the process is over, and which don't.

## 样例 #1

### 输入

```
3
6
0 3 0 0 1 3
10
0 0 0 1 0 5 0 0 0 2
3
0 0 0```

### 输出

```
1 1 0 1 1 1 
0 1 1 1 1 1 0 0 1 1 
0 0 0```

# 题解

## 作者：Silence_water (赞：6)

[题目传送门](https://www.luogu.com.cn/problem/CF1501B)

---

**Description**

简化后的题意就是：从左往右扫，遇到 $a_i>0$，将 $[\max(1,i-a_i+1),i]$ 区间的数都覆盖一遍。输出 $[1,n]$ 中每个数是否被覆盖。若是，输出 $1$，否则输出 $0$。

---

**Analyse**

直接用差分求出每个数被覆盖的次数，次数大于 $0$ 即被覆盖。

---

**Solution**

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int M=2e5+5;
int T,n,a[M];
ll p[M];
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		memset(p,0,sizeof(p));
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&a[i]);
			int pre=max(i-a[i]+1,1);
			p[pre]++,p[i+1]--;
		}
		for(int i=1;i<=n;i++)
		{
			p[i]+=p[i-1];
			if(p[i])printf("1 ");
			else printf("0 ");
		}
		printf("\n");
	}
	return 0;
}
```

---

**The end**

感谢您的观看！如有不足，请麻烦指正哦。

---

## 作者：Daidly (赞：3)

$O(n^2)$ 不行，要用 $O(n)$ 的。

### Solution

先输入。

用 $a[i]$ 表示奶油，$b[i]$ 表示是否（$1/0$）。

从后往前扫一遍：

- 若 $a[i]>0$，就要记录下它的值，~~为后世造福~~，记为 $tmp$。

- 若 $tmp>0$，则 $b[i]=1$，反之为 $0$，$tmp$ 每次减一。

- 若 $a[i]>tmp$，及时更新 $tmp$ 的值。

最后输出即可。

记得 $b[i]$ 和 $tmp$ 要每次清零。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[200005],b[200005],tmp;
int main(){
	cin>>t;
	while(t--){
		cin>>n;tmp=0;
		for(int i=1;i<=n;++i)cin>>a[i],b[i]=0;
		for(int i=n;i>=1;--i){
			tmp=max(tmp,a[i]);
			if(tmp>0){
				b[i]=1;
				tmp--;
			}
		}
		for(int i=1;i<=n;++i)cout<<b[i]<<" ";
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：EuphoricStar (赞：2)

## 思路

差分模板题。

第 $i$ 次放奶油，将 $[\max(1,i-a_i+1),i]$ 这个区间内的数加 $1$。

由于暴力会超时，于是可以考虑使用差分。

不会差分的可以来看这里：[基础算法：差分讲解](https://www.pianshen.com/article/2386279923/)，题解中我就不多说了。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int t, n, ans[200100], a[200100];

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i) {
            ans[i] = 0;
        }
        for (int i = 1; i <= n; ++i) {
            int x;
            scanf("%d", &x);
            ++ans[max(1, i - x + 1)];
            --ans[i + 1];
        }
        for (int i = 1; i <= n; ++i) {
            a[i] = a[i - 1] + ans[i];
            printf("%d ", a[i] > 0);
        }
        putchar('\n');
    }
    return 0;
}
```


---

## 作者：pitiless0514 (赞：2)

### CF1501B
这道题的题意就贼清晰了，然后就很简单了。
发现如果 $a_i = 0$ 时，那么你就只用正常的叠加一层没被涂的。
否则，你就要叠一层，并且往下进行染色。
暴力进行染色肯定是会超时的，因为 $1$ 个点有可能被染色多次，所以我采用了一种方式，那就是用树状数组来进行修改。
对要染色的区间的值都加上 $1$ ，最后进行单点查询，如果值不为 $0$ ，那就输出 $1$ ，否则输出 $0$.
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
template<typename T> inline void read(T &x){
	T f=1;x=0;
	char ch=getchar();
	while(!isdigit(ch)){if(ch=='-') f=-1;ch=getchar();}
	while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	x*=f;
}
const int N = 2e6;
int T,n,a[N],vis[N],tot=0,f[N],num;
vector<int>b;
vector<pair<int,int> > c;
int lowbit(int x){
	return x&(-x);
}
int c1[N],c2[N];
void update(int x,int k){
	int i=x;
	while(x<=n){
		c1[x]+=k;
		c2[x]+=i*k;
		x+=lowbit(x);
	}
}
int sum(int x){
	int ans=0,i=x;
	while(x>0){
		ans+=c1[x]*(i+1);
		ans-=c2[x];
		x-=lowbit(x);
	}
	return ans;
}
signed main(){
	read(T);
	while(T--){
		read(n);
		for(int i=1;i<=n;i++){
			read(a[i]);
		}
		for(int i=1;i<=n;i++){
			f[++num]=0;
			if(a[i]){
		//	f[++num]=1;
			int last=num-a[i]+1;
			if(last<=0) last=1;
			c.push_back( make_pair(last,num) );
			  
			}
		}
		for(int i=0;i<c.size();i++){
			int l=c[i].first;
			int r=c[i].second;
			update(l,1);
			update(r+1,-1);
		}
		for(int i=1;i<=num;i++){
			int x=sum(i);
			if(sum(i)-sum(i-1)==0){
				printf("0 ");
			}
			else printf("1 ");
		}
		puts("");
		for(int i=0;i<=num;i++) c1[i]=c2[i]=0;
		c.clear();
		num=0;
		
	}
    return 0;
}
```

---

## 作者：AuCloud (赞：2)

简单模拟。

# 题意

一个蛋糕塔，按从$1$到$N$的顺序向上叠，叠完第$i$层会使第$i$层以及下面最多连续$a_i$层染色，问最终染色情况

# 题解

毕竟是个 2B ，怎么想也不会太难。

这里提供一种不用差分的做法。

首先用**大眼观察法**得出这玩意倒着做比较好做，所以先整个数组倒序一下

然后循环模拟一遍，从$i$跑到$i + a_i-1$，给$ans$数组赋值，最后从$i+a_i$继续赋值

这样可以保证时间复杂度是$O(N)$

注意我们在赋值的时候，如果发现$i+a_i-1<j+a_j-1$，说明第$j$层比第$i$层向下染的颜色层数多，将$i$赋值为$j$继续往下循环就可以。

注意最后清空最好不要`memset`，不然会被杀的很惨。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int a[200001], b[200001];
int main()
{
	int T;
	cin >> T;
	while(T--)
	{
		int n;
		cin >> n;
		for(int i = 1; i <= n; i++)
		{
			 cin >> a[i];
		}
		reverse(a + 1, a + n + 1);
		for(int i = 1; i <= n; i++)
		{
			if(a[i]) for(int j = i; j < i + a[i] && j <= n; j++)
			{
				b[j] = 1;
				if(i + a[i] < j + a[j]) i = j;
			}
			if(a[i]) i += a[i] - 1;
		}
		reverse(b + 1, b + n + 1);
		for(int i = 1; i <= n; i++) cout << b[i] << ' ';
		cout << endl;
		for(int i = 1; i <= n; i++) a[i] = b[i] = 0;
	}
   return 0;
}

```

---

## 作者：血色黄昏 (赞：2)

题意为给 n 个操作，每次加一层，然后将从上至下 $a_i$ 染上奶油，输出操作后的序列

我们从最后一层开始操作，每次更新能染到的最低层数，如果不行就说明染不上，一直更新到最后一层即可，复杂度为 $O(n)$ 。

然后按照思路写就好了，良心 2B ，比 A 还水。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n, t, a[200010];//开2e6
bool tong[200010];
int main()
{
	cin>>t;
	while(t --)//多组数据
	{
		cin>>n;
		for(int i = 1;i <= n;i ++)
		{
			cin>>a[i];
			tong[i] = false;//输入&清空
		}
		int pos = n, minn = 0x3f3f3f3f;//更新最小值
		while(pos > 0)//一直更新到没有
		{
			if(a[pos] == 0)//如果这层染不了自己
			{
				if(minn > pos)//如果之后被染了就可以
				{
					tong[pos] = true;
				}
				pos --;
			}
			else
			{
				minn = min(minn, pos - a[pos] + 1);//更新层数
				pos --;
			}
		}
		for(int i = 1;i <= n;i ++)//输出
		{
			if(tong[i])cout<<"0"<<" ";
			else cout<<"1"<<" ";
		}
		cout<<"\n";
	}
	return 0;
}
```


---

## 作者：_lmh_ (赞：1)

### 题目分析
一道水题，多种算法都能做，比如模拟，线段树等。

当然这里只会介绍其中有一种——差分。

### 差分介绍

假设有一个数列 $\{a_i\}$，则其对应的差分数列为 $\{d_i\}$，它的公式为 $d_1=a_1,d_i=a_i-a_{i-1}$。

根据这个公式可以推出，$a_i=d_1+d_2+...+d_n$。

在OI中，它常用于多次区间改之后遍历整个数组的题目，比如本题。

### 基础代码

修改：
```cpp
void add(int val,int l,int r){
    d[l]+=val;
    d[r+1]-=val;
}/*l,r:修改区间左右端点 val:修改的值
实际使用时一般不会编写此函数，在此仅作演示*/
```

遍历数组：
```cpp
int tmp=0;
for (int i=1;i<=n;++i){
    tmp+=d[i];
    cout<<tmp<<' '; //tmp=a[i]
}
```

### 代码

注意被浸湿的是 $[i-a_i+1,i]$ 而不是 $[i,i+a_i-1]$，并且要防止数组越界。

#### 本题有多组数据，记得清零差分数组。

最后是代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,d[200007],n,a,ans,tmp;
int main(){
    cin>>T;
    while(T--){
        cin>>n;
        memset(d,0,sizeof(d));
        tmp=0; //清零
        for (int i=1;i<=n;i++){
            cin>>a;
            d[i+1]--;
            d[max(1,i-a+1)]++; //数组不要越界
        }
        for (int i=1;i<=n;i++){
            tmp+=d[i];
            cout<<(tmp>0)<<' ';
//只需输出是否被浸湿，不是被浸湿了几次
        }
        cout<<endl; //不要忘记换行
    }
    return 0;
}
```

---

## 作者：sysong (赞：1)

# 题解CF1501B Napoleon Cake

### Description

Arkady​ 想要做蛋糕。这个蛋糕有 $n$ 层，ta计划在第 $i$ 层放 $a_i$ 的奶油，这些奶油会浸湿下面（包括第 $i$ 层）的 $a_i$ 层，Arkady 想知道，他做出来的蛋糕的所有层是否有奶油。

### Solution

赛时愣是没想到差分，感觉暴力 $\Omicron ( n^2 )$ 应该过不了，就打了个分块板子上去。

看到大家都没有用分块，就发个题解供大家参考，并不是正解。

时间复杂度 $\Omicron ( n \sqrt n )$。

### Code

```c++
#include <bits/stdc++.h>
#define gc() getchar()
using namespace std;
typedef long long ll;

template <typename T> void rd(T &x){
	ll f=1;x=0;char c=gc();
	for(;!isdigit(c);c=gc())if(c=='-')f=-1;
	for(;isdigit(c);c=gc())x=(x<<1)+(x<<3)+(c^48);
	x*=f;
}

int t,n,k,d[200010];
bool f[200010],h[200010];

inline void add(int l,int r){					// 原本是区间加，这里被我改成了区间赋值
	int b=d[l],e=d[r];
	if(b==e)for(int i=l;i<=r;i++)h[i]=1;
	else{
		for(int i=l;d[i]==b;i++)h[i]=1;
		for(int i=b+1;i<e;i++)f[i]=1;
		for(int i=r;d[i]==e;i--)h[i]=1;
	}
}

int main(){
	rd(t);
	for(;t;--t){
		rd(n);k=sqrt(n);
		for(int i=1;i<=n;i++)
			d[i]=(i-1)/k+1;
		for(int i=1,ff;i<=n;i++){
			rd(ff);
			if(ff){
				add(max(1,i-ff+1),i);			// 这里要注意从 1 开始，不要出现负数
			}
		}
		for(int i=1;i<=n;i++)
			if(h[i]||f[d[i]])printf("1 ");
			else printf("0 ");
		printf("\n");
		for(int i=1;i<=n;i++)f[i]=h[i]=0;
	}
	return 0;
}

```

跑得比较慢，赛时用时140ms，但没有超限。



***by sysong***

$2021.3.23$



---

## 作者：Zboh_Zbp (赞：0)

## 题目分析

很明显，我们在读题的时候便可以发现，这是一道模拟题，可以根据题意进行模拟。

但是我们注意到，这道题目需要进行染色，方式如下图：

![染色方式](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1501B/d2a848de33f21319239069b9694ee652ecb320b0.png)

可以发现，染色是从上往下的，那么我们就可以考虑从 $n$ 开始遍历到 $1$，也就是倒序遍历。

接着，用 $i-input[i]+1$ 表示染色终点，但是，可能有被覆盖的情况出现，所以我们就用 `cnt` 记录当前覆盖后的染色终点。

那我们要怎样判断是否被覆盖过呢？

可以发现，未被覆盖的染色，染色终点 $i-input[i]+1$ 就越靠后，我们只需要不断更新 `cnt` 即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n;
int main(){
    scanf("%lld",&t);
    while(t--){
        scanf("%lld",&n);
    	int a[200010];
    	int input[200010];
    	int cnt=100000000;
    	for(int i=1;i<=n;i++){
			scanf("%d",&input[i]);
		}
    	for(int i=n;i>=1;i--){ // 倒序遍历。  
        	cnt=min(cnt,i-input[i]+1); // 判断染色终点并更新。  
        	if(i>=cnt) a[i]=1; // 判断是否染色。  
        	else a[i]=0;
    	}
    	for(int i=1;i<=n;i++){
    		printf("%d ",a[i]);
    	}
    	printf("\n");
    }
    return 0;
}
```

---

## 作者：Booksnow (赞：0)

# Napoleon Cake

## 题目大意

给定一个长度为 $n$ 的区间，初始状态下每个值都为 $0$ ，之后给出一个数组 $a[i]$ ，表示区间里第 $i$ 个数包括在内往前数的 $a[i]$ 个 数全部变为 $1$ ，输出最后的区间。

## 分析

有一个很显然的做法，就是纯粹暴力，手动更改，然而同样很显然的是时间复杂度肯定是过不了的，显然我们只需要一个 $O(1)$ 更改的方法。

很容易想到差分，只需要更改首尾的值即可，但这样的话中间可能会出现大于 $1$ 的数，其实有一个很简单的标准判断就是了。由于每一个区间我们**只需要关注他是否被覆盖**，所以只要他的差分值不为 $0$ ，我们就输出 $1$ 。

## CODE
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=2e5+10;
inline int read()
{
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') { if(ch=='-') w*=-1; ch=getchar(); }
	while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
	return s*w;
}
int T,n;
int ans[N];
int main()
{
	T=read();
	while(T--){
		n=read();
		for(register int i=1;i<=n;i++){
			int x=read();
			ans[max(i+1-x,1)]+=1,ans[i+1]-=1;
		}
		int now=0;
		for(register int i=1;i<=n;i++){
			now+=ans[i];
			if(now>0) printf("1 ");
			else printf("0 ");
			ans[i]=0;
		}
		ans[n+1]=0;
		puts("");
	}
	return 0;
}
```



---

## 作者：Allanljx (赞：0)

### [洛谷题目传送门](https://www.luogu.com.cn/problem/CF1501B)
### [CF题目传送门](https://codeforces.com/problemset/problem/1501/B)
## 题意
一个蛋糕塔，按从1到 $N$ 的顺序向上叠，叠完第 $i$ 层会使第 $i$ 层以及下面最多连续 $a[i]$ 层染色，问最终染色情况。


------------
## 思路
倒着循环一遍，用 $d$ 记录奶油最多还能往下染几层。用 $f$ 数组记录这层有没有奶酪。时间复杂度 $O(n)$ 。


------------
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[200001],f[200001]; //f数组记录第i层有没有奶酪，1代表有，0代表没有
int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
		int n;
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&a[i]);
			f[i]=0; //边输入边清零
			if(a[i]!=0) f[i]=1;
		}
		int d=-2147483646; //d表示奶酪还能往下漏几层
		for(int i=n;i>0;i--) //倒序枚举
		{
			d=max(d,a[i]); //更新奶酪还能往下漏几层
			if(d>0) //此处是否有奶酪
			{
				f[i]=1;
				d--;
			}
		}
		for(int i=1;i<n;i++)
		{
			printf("%d ",f[i]);
		}
		printf("%d\n",f[n]);
	}
	return 0;
}
```

---

## 作者：int32 (赞：0)

### 思路

遍历 $[1,n]$ ，将 $[\max(1,i-a_i+1),i]$ 范围中的数的值 $+1$。

首先可以想到暴力，预估时间复杂度 $O(n^2)$，会超时。

于是考虑差分。

### 代码

```cpp
//a[]:原数组
//c[]:差分数组
read(t);
while(t--){
	memset(c,0,sizeof(c));//一定要清零
	read(n);
	for(int i=1;i<=n;i++){
		read(a[i]);
		//差分
		c[max(1,i-a[i]+1)]++;
		c[i+1]--;
	}
	for(int i=1;i<=n;i++){
		c[i]+=c[i-1];
		write(c[i]>0);
		putchar(' ');
	}
	puts("");
}
```

---

## 作者：Umbrella_Leaf (赞：0)

**一句话题意**：区间或 $1$ ，最后查询 $n$ 次。

简单的线段树（差分？~~我不会~~我才不要

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int a[200005],c[2000005],tab[2000005];
int read(){
	int x=0;char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9')x=x*10+(c^48),c=getchar();
	return x;
}
void pushdown(int k){
	tab[k*2]=tab[k];
	tab[k*2+1]=tab[k];
	c[k*2]=tab[k];
	c[k*2+1]=tab[k];
	tab[k]=0;
}
void build(int k,int l,int r){
	c[k]=tab[k]=0;
	if(l==r)return;
	int mid=l+r>>1;
	build(k*2,l,mid);
	build(k*2+1,mid+1,r);
}
void change(int k,int l,int r,int x,int y){
	if(y<l||r<x)return;
	if(x<=l && r<=y){c[k]=tab[k]=1;return;}
	int mid=l+r>>1;
	if(tab[k])pushdown(k);
	change(k*2,l,mid,x,y);
	change(k*2+1,mid+1,r,x,y);
	if(c[k*2]&&c[k*2+1])c[k]=1;
}
int query(int k,int l,int r,int x){
	if(l==r)return c[k];
	int mid=l+r>>1;
	if(tab[k])pushdown(k);
	if(mid>=x)return query(k*2,l,mid,x);
	else return query(k*2+1,mid+1,r,x);
}
int main(){
	int T=read();
	while(T--){
		n=read();
		build(1,1,n);
		for(int i=1;i<=n;i++){
			a[i]=read();
			if(a[i])change(1,1,n,max(1,i-a[i]+1),i);
		}
		for(int i=1;i<=n;i++)printf("%d ",query(1,1,n,i));
		puts("");
	}
	return 0;
}

```
既然是区间更新，为什么不用线段树呢

---

## 作者：dalao_see_me (赞：0)

题目大意：做一个 $n$ 层的蛋糕，在第 $i$ 层放置 $a_i$ 的奶油，从第 $max(i-a_i+1,1)$ 层到第 $i$ 层都会被奶油浸湿，输出所有层被奶油浸湿的状况。

照着题意打一遍即可，需要注意的是，如果直接给所有浸湿的层赋值的话，会被fst（我的一个朋友就是这么写的）。所以我们要用**差分**来做。

差分是什么呢？

差分可以 $O(1)$ 区间修改，适用于只有修改的题目，搭配上树状数组也可以实现单点查询，不过区间修改和单点查询都变成了 $O(log_2n)$。

我们可以用一个数组 $c$ 来记录 $a_i-a_{i-1}$ 的值，当每次区间修改的时候，我们让 $c_l+val$，让 $c_{r+1}-val$，这样，就实现了区间加的操作。查询值的时候，$c_1+c_2+...+c_i$ 就是 $a_i$ 的值。

详细操作在代码里，不多赘述。

# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int a[N],c[N];
int n,_;
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-f;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x*f;
}
int main(){
	_=read();
	while(_--){
		n=read();memset(c,0,sizeof(c));
		for(int i=1;i<=n;i++)a[i]=read();
		for(int i=1;i<=n;i++)
			if(a[i]){
				c[i+1]--;
				c[max(i-a[i]+1,1)]++;
			}
		int s=0;
		for(int i=1;i<=n;i++){
			s+=c[i];
			if(s>0)putchar('1');
			else putchar('0');
			putchar(' ');
		}
		putchar('\n');
	}
	return 0;
}
```


---

## 作者：_caiji_ (赞：0)

题目可以转化一下：给一个长为 $n$ 的数组 $a$，请求出一个长为 $n$ 的数组 $b$。要求若 $a_i$ 不为 $0$，则 $[b_{i-a_i+1},b_i]$ 这个区间要为 $1$。

知道这个题目意思就好办了。题目说 $n\leq 2\times 10^5$，暴力修改显然超时。我们可以用差分维护一下，每次给区间 $[b_{i-a_i+1},b_i]$ 加 $1$，最后没被加到的就是 $0$，反之是 $1$。这样 $O(1)$ 区间加，$O(n)$ 递推求原数组，不会超时。如果不会差分可以看[这里](https://www.pianshen.com/article/2386279923/)。

```cpp
//封装一个模版，用起来更方便
class Difference{//difference差分
    private:
        int a[100010],n;
    public:
        void clear(int size){//由于是多测，要清空
            memset(a,0,sizeof a);
            n=size;
        }
        void add(int l,int r,int c=1){//区间加
            a[l]+=c,a[r+1]-=c;
        }
        void init(){//递推求原数组
            for(int i=1;i<=n;i++){
                a[i]+=a[i-1];
            }
        }
        int operator[](int x)const{//访问
            return a[x];    
        }
};
int n;
Difference a;
int mian(){
    scanf("%d",&n);
    a.clear(n);
    for(int i=1,x;i<=n;i++){
        scanf("%d",&x);
        if(x) a.add(max(1,i-x+1),i);
    }
    a.init();
    for(int i=1;i<=n;i++){
        printf("%d ",min(1,a[i]));
        //min(1,0)=0，min(1,非0数)=1，保证输出只有0和1
    }
    return puts(""),0;
}
```


---

## 作者：清烛 (赞：0)

[My Blog](https://imyangty.com/oi/1327)

## 题意
制作拿破仑蛋糕时需要依次叠放 $n$ 个干的层，给定 $\lbrace a_n\rbrace$，描述了在叠放第 $i$ 层之后需要加的奶油量，加了量为 $x$ 的奶油会使得最顶层的 $x$ 层变湿。

对于每一层求最后的干湿状态。

## 题解
不难发现其就是一个线段覆盖问题，可以使用差分进行求解。加到 $i$ 层的时候把 $d_{\max\lbrace0, i - a_i + 1\rbrace}:= 1$，$d_{i + 1}:= -1$ 即可，最后把前缀和累加回来就能得到答案。

注意多测清空。

```cpp
#include <cstdio>
#include <cctype>
#include <cstring>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

int read()
{
    int s = 0;
    char c = getchar();
    while (!isdigit(c))
        c = getchar();
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return s;
}

inline int max(int a, int b) {return a > b ? a : b;}

const int maxn = 2e5 + 5;
int stk[maxn], n;

int main()
{
    int T = read();
    while (T--)
    {
        n = read();
        FOR(i, 1, n)
        {
            int a = read();
            if (!a) continue;
            int low = max(0, i - a + 1), up = i;
            ++stk[low], --stk[up + 1];
        }
        FOR(i, 1, n) stk[i] += stk[i - 1];
        FOR(i, 1, n) printf("%d ", stk[i] ? 1 : 0), stk[i] = 0;
        stk[n + 1] = stk[0] = 0;
        puts("");
    }
    return 0;
}
```

---

## 作者：vectorwyx (赞：0)

对于每个 $i$，将区间 $[i-a_i+1,i]$ 里的数全部加 $1$。最后所有大于零的位置的答案就是 $1$，否则为 $0$。差分即可。

代码如下：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define ll long long
#define fo(i,x,y) for(register int i=x;i<=y;++i)
#define go(i,x,y) for(register int i=x;i>=y;--i)
using namespace std;

inline int read(){
	int x=0,fh=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-') fh=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	return x*fh;
}

const int N=1e6+5;
int a[N],b[N];

void work(){
	int n=read();
	fo(i,1,n) a[i]=read();
	fo(i,1,n){
		int l=max(i-a[i]+1,1),r=min(n+1,i+1);
		b[l]++,b[r]--;
	}
	fo(i,1,n){
		b[i]=b[i-1]+b[i];
		if(b[i]) printf("1 ");
		else printf("0 ");
	}
	fo(i,1,n+1) b[i]=0;
	puts("");
}

int main(){
	int T=read();
	while(T--) work(); 
	return 0;
}

```


---

