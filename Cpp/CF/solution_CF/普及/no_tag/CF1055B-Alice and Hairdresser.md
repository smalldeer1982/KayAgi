# Alice and Hairdresser

## 题目描述

Alice's hair is growing by leaps and bounds. Maybe the cause of it is the excess of vitamins, or maybe it is some black magic...

To prevent this, Alice decided to go to the hairdresser. She wants for her hair length to be at most $ l $ centimeters after haircut, where $ l $ is her favorite number. Suppose, that the Alice's head is a straight line on which $ n $ hairlines grow. Let's number them from $ 1 $ to $ n $ . With one swing of the scissors the hairdresser can shorten all hairlines on any segment to the length $ l $ , given that all hairlines on that segment had length strictly greater than $ l $ . The hairdresser wants to complete his job as fast as possible, so he will make the least possible number of swings of scissors, since each swing of scissors takes one second.

Alice hasn't decided yet when she would go to the hairdresser, so she asked you to calculate how much time the haircut would take depending on the time she would go to the hairdresser. In particular, you need to process queries of two types:

- $ 0 $ — Alice asks how much time the haircut would take if she would go to the hairdresser now.
- $ 1 $ $ p $ $ d $ — $ p $ -th hairline grows by $ d $ centimeters.

Note, that in the request $ 0 $ Alice is interested in hypothetical scenario of taking a haircut now, so no hairlines change their length.

## 说明/提示

Consider the first example:

- Initially lengths of hairlines are equal to $ 1, 2, 3, 4 $ and only $ 4 $ -th hairline is longer $ l=3 $ , and hairdresser can cut it in $ 1 $ second.
- Then Alice's second hairline grows, the lengths of hairlines are now equal to $ 1, 5, 3, 4 $
- Now haircut takes two seonds: two swings are required: for the $ 4 $ -th hairline and for the $ 2 $ -nd.
- Then Alice's first hairline grows, the lengths of hairlines are now equal to $ 4, 5, 3, 4 $
- The haircut still takes two seconds: with one swing hairdresser can cut $ 4 $ -th hairline and with one more swing cut the segment from $ 1 $ -st to $ 2 $ -nd hairline.
- Then Alice's third hairline grows, the lengths of hairlines are now equal to $ 4, 5, 4, 4 $
- Now haircut takes only one second: with one swing it is possible to cut the segment from $ 1 $ -st hairline to the $ 4 $ -th.

## 样例 #1

### 输入

```
4 7 3
1 2 3 4
0
1 2 3
0
1 1 3
0
1 3 1
0
```

### 输出

```
1
2
2
1
```

# 题解

## 作者：XL4453 (赞：3)

### 题目分析：

~~一个数组能解决的问题为什么是蓝题，果然蓝是水的颜色吗。~~

用一个数组记录当前每一根头发的长度，每当一根头发长长，若依然没有超过理想线或本来就超过了理想线那么显然都没有影响，唯一需要考虑的情况就是原来没有超过理想线而后来超过了理想线。

那么对于这一种情况，如果这是一个独立的区间则需要新的一刀，如果是某一个区间旁边那么答案不影响，否则链接了两个区间则答案减一。

----------------
```cpp
#include<cstdio>
using namespace std;
long long a[100005],n,m,l,T,ans,x,y;
int main(){
	scanf("%lld%lld%lld",&n,&m,&l);
	a[0]=-2147483647;ans=0;
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		if(a[i-1]<=l&&a[i]>l)ans++;
	}
	for(int i=1;i<=m;i++){
		scanf("%lld",&x);
		if(!x)printf("%lld\n",ans);
		else{
			scanf("%lld%lld",&x,&y);
			if(a[x]<=l&&(a[x]+=y)>l){
				ans++;
				if(a[x-1]>l)ans--;
				if(a[x+1]>l)ans--;
			}
		}
	}
	return 0;
}
```


---

## 作者：cqbztz2 (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF1055B)

# 前言

~~这不是模拟+思维吗，为什么大佬说是线段树~~

# 思路

因为在题目中头发的长度只会不断增长而不会减少，所以我们可以先分情况讨论可能出现的情况。

 *  ：如果该根头发是要剪的，那么它再增长的话是不会对所剪的次数造成影响的.

* ：如果该头发起初不要剪，增长了之后要剪，我们需要讨论与它相邻的头发的状态：

如果只有一边的头发需要剪，则不会造成影响；

如果两边都是要剪的头发，则说明把两部分需要剪的头发连了起来，所以要剪的次数就会-1；

如果都不要剪，则这根头发要单独再剪一次，结果增加。

# 代码

```cpp
  #include<bits/stdc++.h>
  using namespace std;
  long long n,m,l,a[100005],u,v,ans,x;
  int main(){
      cin>>n>>m>>l;
      for(int i=0;i<n;i++){
          cin>>a[i];
          if(a[i]>l){
              if(i==0){
                  ans++;
              }
              else{
                  if(a[i-1]<=l){
                      ans++;
                  }
              }
          }
      }
      while(m--){
          cin>>x;
          if(x==0){
              cout<<ans<<endl;
          }
          else{
              cin>>u>>v;
              u--;
              if(a[u]>l){
                  continue;
              }
              a[u]+=v;
              if(a[u]<=l){
                  continue;
              }
              if(u!=0){
                  if(u==n-1){
                      if(a[u-1]<=l){
                          ans++;
                      }
                  } 
                  else{
                      if(a[u-1]>l&&a[u+1]>l){
                          ans--;
                      }
                      else if(a[u-1]<=l&&a[u+1]<=l){
                          ans++;
                      }
                  }
              }
              else{
                  if(a[u+1]<=l){
                      ans++;
                  }
              }
          }
      }
      return 0;
  }
```


---

## 作者：ccxswl (赞：1)

# Alice and Hairdresser  

第一眼线段树，第二眼好像可以直接用数组模拟。

当一根头发长于 $l$，它再长多长其实都一样，所以不用开 `long long`。

如果一根新的头发长到比 $l$ 长，那可以分成以下几种情况：

- 如果它**左侧和右侧只有一个元素大于 $l$** ，那答案不变。

- 如果**左侧和右侧都大于 $l$**，答案减一。因为相当于将左侧区间和右侧区间并到一起。

- 如果**右侧和左侧都不大于 $l$**，答案加一。

在刚开始时统计一遍答案，每次做修改就行了。

复杂度 $O(n)$。

```cpp
  #include <bits/stdc++.h>
  
  using namespace std;
  
  int n, m, l;
  vector<int> a;
  int ans;
  
  int main() {
  	cin >> n >> m >> l;
  	a.resize(n + 7);
  	for (int i = 1; i <= n; i++)
  		cin >> a[i];
  	for (int i = 1; i <= n; i++)
  		if (a[i] > l && a[i - 1] <= l)
  			ans++;
  	while (m--) {
  		int op;
  		cin >> op;
  		if (op == 1) {
  			int x, y;
  			cin >> x >> y;
  			if (a[x] > l) continue;
  			a[x] += y;
  			if (a[x] <= l) continue;
  			if (a[x - 1] > l && a[x + 1] > l) ans--;
  			if (a[x - 1] <= l && a[x + 1] <= l) ans++;
  		}
  		if (op == 0)
  			cout << ans << endl;
  	}
  }
```

  

---

## 作者：Rbu_nas (赞：1)

这道题的题意已经说得很清楚了，因为每次剪都需要1s，我们剪的次数必须最少，一次剪得头发数要最大。

我们用$a_i$表示头发长度，$b_i$表示$a_i$是否剪过，就能很方便的进行判断是否可以剪一段头发。可是这道题的长度会持续增加，每次判重的操作十分不便，我们可以**先剪再判重**。详细解释见代码。这题还有一个坑点就是$10^9$的数据得开`long long`

$\mathcal{Code}$

```cpp
#include <cstdio>
using namespace std;

#define N 100003
#define LL long long

int n, q, l, opt, p, h;
LL a[N], res;
bool flag[N];

int main(void)
{
    scanf("%d %d %d", &n, &q, &l);
    for(int i=1; i<=n; ++i)
    {
        scanf("%lld", &a[i]);
        if(a[i] > l)
        {
            flag[i]=true;
            if(!flag[i-1]) ++res; //进来预处理，不能一段剪的ans+1
        }
    }
    while(q--)
    {
        scanf("%d", &opt);
        if(!opt)
            printf("%lld\n", res);
        else
        {
            scanf("%d %d", &p, &h);
            if(a[p] <= l && a[p]+h > l) //这里条件注意一下，之前的a[i]>l的情况已经计数，如果直接a[p]>l的话会重复计数
            {
                ++res; flag[p]=true;
                if(flag[p-1]) --res;
                if(flag[p+1]) --res;
                /*
                	这里也要注意，如果前面一根和后面一根都剪过，a[p]这根头发相当于连接了新的一段，ans-=2
                    如果只是前面或后面见过a[p]只是连接了1根头发，ans-=1
                */
            }
            a[p]+=h;
        }
    }
    return 0;
}

```

---

## 作者：QQH08 (赞：1)

~~这题不是裸的线段树吗？~~

用线段树维护区间要剪的次数，但是连续要剪的可以一刀
解决，所以在合并区间的时候，再记录区间左端点的长度和右端点的长度。

在 push_up 的时候，如果左儿子的右端点的长度和右儿子的左端点的长度都要剪，那么总的次数就要减一。（因为可以一刀减掉）。

最后每次询问的时候直接输出总区间的答案即可。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=100005;
struct node{
	int l,r,sum;
	ll lenl,lenr;
}tr[N*4];
// sum为区间答案， lenl为左端点长度，lenr为右端点长度 
int n,m;
ll L,a[N];
void push_up(int p){
	int ls=p<<1,rs=p<<1|1;
	tr[p].lenl=tr[ls].lenl;
	tr[p].lenr=tr[rs].lenr;
	tr[p].sum=tr[ls].sum+tr[rs].sum;
	if(tr[ls].lenr>L&&tr[rs].lenl>L)tr[p].sum--;
}
void build(int p,int l,int r){
	tr[p].l=l,tr[p].r=r,tr[p].sum=0;
	tr[p].lenl=tr[p].lenr=0;
	if(l==r){
		tr[p].lenl=tr[p].lenr=a[l];
		tr[p].sum=(a[l]>L);
		return;
	}
	int mid=(l+r)>>1;
	build(p<<1,l,mid);
	build(p<<1|1,mid+1,r);
	push_up(p);
}
void Add(int p,int x,ll y){
	if(tr[p].l==tr[p].r){
		tr[p].lenl+=y,tr[p].lenr+=y;
		tr[p].sum=(tr[p].lenl>L);
		return;
	}
	int mid=(tr[p].l+tr[p].r)>>1;
	if(x<=mid)Add(p<<1,x,y);
	else Add(p<<1|1,x,y);
	push_up(p);
}
int main(){
	scanf("%d%d%d",&n,&m,&L);
	for(int i=1;i<=n;i++)
		scanf("%lld",&a[i]);
	build(1,1,n);
	for(int i=1;i<=m;i++){
		int opt;
		scanf("%d",&opt);
		if(opt==0)printf("%d\n",tr[1].sum);
		else{
			int x;ll y;
			scanf("%d%lld",&x,&y);
			Add(1,x,y);
		}
	}
	return 0;
}
```


---

## 作者：qw1234321 (赞：0)

一眼线段树板子，秒了。

线段树维护最少剪的次数 $ans$，但是连续一段 $\gt L$ 的可以一刀剪掉，所以再记一个左右端点头发的长度，方便更新。

若左儿子右端点长度 $\gt L$ 或 右儿子左端点长度 $\gt L$，那么当前节点的值就要减 $1$。

当前节点的左端点长度即为左儿子左端点长度，右端点长度即为右儿子右端点长度。

建树的时候若当前头发长度 $\gt L$，则 $ans$ 初值为 $1$，否则为 $0$。

然后就是模板了，注意最佳长度 $L$ 和 线段树中的 $l$ 容易弄混，需要小心（本人被卡 10min）。

code：

```cpp
#include<bits/stdc++.h>
#define int long long
#define il inline
using namespace std;

const int N = 1e5 + 5;
int n, m, L, a[N];
struct Segment_Tree{
	struct node{
		int ans, lenl, lenr;
	}t[N << 2];
	il void pushup(int k){
		t[k].lenl = t[k << 1].lenl;
		t[k].lenr = t[k << 1 | 1].lenr;
		t[k].ans = t[k << 1].ans + t[k << 1 | 1].ans;
		if (t[k << 1].lenr > L && t[k << 1 | 1].lenl > L) t[k].ans--;
	}
	il void build(int k, int l, int r){
		t[k].lenl = t[k].lenr = t[k].ans = 0;
		if (l == r){
			t[k].lenl = t[k].lenr = a[l];
			t[k].ans = (a[l] > L);
			return ;
		}
		int mid = l + r >> 1;
		build(k << 1, l, mid);
		build(k << 1 | 1, mid + 1, r);
		pushup(k);
	}
	il void change(int k, int l, int r, int x, int v){
		if (l == r){
			t[k].lenl += v, t[k].lenr += v;
			t[k].ans = (t[k].lenl > L);
			return ;
		}
		int mid = l + r >> 1;
		if (x <= mid) change(k << 1, l, mid, x, v);
		else change(k << 1 | 1, mid + 1, r, x, v);
		pushup(k);
	}
}t;

void work(){
	cin >> n >> m >> L;
	for (int i = 1; i <= n; i++) cin >> a[i];
	t.build(1, 1, n);
	while(m--){
		int opt;
		cin >> opt;
		if (opt & 1){
			int p, x;
			cin >> p >> x;
			t.change(1, 1, n, p, x);
		}
		else{
			cout << t.t[1].ans << "\n";
		}
	}
}

signed main(){
	int t = 1;
	//  cin >> t;
	while(t--) work();
	return 0;
}
```

---

## 作者：naroto2022 (赞：0)

# CF1055B 题解

### 思路

其实就是一道用数组做的模拟题。

就用一个数组 $a$ 记录第 $i$ 根头发的长度，一个变量 $ans$ 来记录目前捡的话要几秒钟，接下来就是要输入 $a$ 数组，那其实也很简单，$ans$ 就动态更新，如果前面一根头发不需要剪，而这根头发大于 $l$，则 `ans++`，因为其实将 $ans$ 转化一下就是求 $a$ 数组中有几个连续区间使得区间内的所有数都大于 $l$，所以要是 $a_i>l$ 并且 $a_{i-1}\leqslant l$，则会多出一个区间。

然后初始化完了就要开始进行 $m$ 次操作：

1. 要是第一个数为 $0$，则直接输出 $ans$。
2. 要是第一个数是 $1$，就要开始操作了：

首先，$a_p=a_p+d$，然后就要开始更新 $ans$，分为以下两种情况：

1. 要是更新完的 $a_p$ 大于 $l$，并且 $a_{p-1}\leqslant l,a_{p+1}\leqslant l$，则 $a_p$ 为一个新的区间，因此 `ans++`。
2. 要是更新完的 $a_p$ 大于 $l$，并且 $a_{p-1}>l,a_{p+1}>l$，则 $a_p$ 让前面和后面的区间连在了一起（两个区间合二为一），因此 `ans--`。

注意：上面两种情况都是原本的 $a_p$ 小于等于 $l$。

### 总结

1. 模拟。
2. 数组基础。
3. 分类讨论。

### 代码
```
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
long long n,m,l,ans,a[100005],x,p,d;
int main(){
	scanf("%lld %lld %lld",&n,&m,&l);
	for(int i=1; i<=n; i++){
		scanf("%lld",&a[i]);
		if(a[i-1]<=l&&a[i]>l) ans++;//a[i]要剪，且a[i-1]不需要剪，则a[i]多创造出来了一个区间。 
	}
	while(m--){//m次操作。 
		scanf("%lld",&x);
		if(x==0) printf("%lld\n",ans);//直接输出答案，头发全都剪完了。 
		else{//某根头发又神经质的长长了。 
			scanf("%lld %lld",&p,&d);
			a[p]+=d;//更新。 
			if(a[p]-d<=l){//原本是不需要剪的才可以，因为它如果原本就已经要剪的话它不管怎么长都是要剪的，而且那样ans不用变。 
				if(a[p]>l&&a[p-1]<=l&&a[p+1]<=l) ans++;//前后都是不需要剪的，所以这根头发创建了一个新区间。 
				if(a[p-1]>l&&a[p]>l&&a[p+1]>l) ans--;//前后都是要剪的，而因为原本a[p]不需要减，不属于前后两个区间，而现在，它不仅属于两个区间了，还把两个区间连起来了，所以区间数减少1。 
			}
		}
	}
	return 0;
}
```


---

## 作者：JiaY19 (赞：0)

应该算是水题吧。

看见有大佬用线段树来做这道题，但好像仅要一个数组就可以了。

#### 思路

因为没有删除操作。

所以可以用一个数组去维护头发的长度。

先预处理出初始答案。

再枚举判断周围有没有比规定长度长的头发。

如果有，在判断是不是两边都比规定长度长。

如果是，那么答案减一。

如果不是，答案不变。

如果两边都没有，答案加一。

#### 一个细节

这个细节卡了我一下。

要注意判断之前，这根头发是否超过规定长度，如果超过了。

那么它对答案没有影响。

#### Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n , m , l , ans , a[100010];

int read()
{
	int X = 0 , W = 1;
	char asd = getchar();
	while(!isdigit(asd))
	{
		if(asd == '-') W = -1;
		asd = getchar();
	}
	while(isdigit(asd)) X = X * 10 + (int)(asd - '0') , asd = getchar();
	return X * W;
}

signed main()
{
	n = read() , m = read() , l = read();
	for(int i = 1;i <= n;i++) a[i] = read();
	for(int i = 1;i <= n;i++) if(a[i] > l && a[i - 1] <= l) ans++;
	for(int i = 1;i <= m;i++)
	{
		int x = read();
		if(x == 0) cout << ans << endl;
		else
		{
			int y = read() , z = read();
			a[y] += z;
			if(a[y] > l && a[y] - z <= l)
			{
				if(a[y - 1] > l || a [y + 1] > l)
				{
					if(a[y - 1] > l && a [y + 1] > l) ans--;
				}
				else ans++;
			}
		}
	}
	return 0;
}
```
完结撒花！

---

