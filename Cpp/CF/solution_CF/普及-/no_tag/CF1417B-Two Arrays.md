# Two Arrays

## 题目描述

RedDreamer has an array $ a $ consisting of $ n $ non-negative integers, and an unlucky integer $ T $ .

Let's denote the misfortune of array $ b $ having length $ m $ as $ f(b) $ — the number of pairs of integers $ (i, j) $ such that $ 1 \le i < j \le m $ and $ b_i + b_j = T $ . RedDreamer has to paint each element of $ a $ into one of two colors, white and black (for each element, the color is chosen independently), and then create two arrays $ c $ and $ d $ so that all white elements belong to $ c $ , and all black elements belong to $ d $ (it is possible that one of these two arrays becomes empty). RedDreamer wants to paint the elements in such a way that $ f(c) + f(d) $ is minimum possible.

For example:

- if $ n = 6 $ , $ T = 7 $ and $ a = [1, 2, 3, 4, 5, 6] $ , it is possible to paint the $ 1 $ -st, the $ 4 $ -th and the $ 5 $ -th elements white, and all other elements black. So $ c = [1, 4, 5] $ , $ d = [2, 3, 6] $ , and $ f(c) + f(d) = 0 + 0 = 0 $ ;
- if $ n = 3 $ , $ T = 6 $ and $ a = [3, 3, 3] $ , it is possible to paint the $ 1 $ -st element white, and all other elements black. So $ c = [3] $ , $ d = [3, 3] $ , and $ f(c) + f(d) = 0 + 1 = 1 $ .

Help RedDreamer to paint the array optimally!

## 样例 #1

### 输入

```
2
6 7
1 2 3 4 5 6
3 6
3 3 3```

### 输出

```
1 0 0 1 1 0 
1 0 0```

# 题解

## 作者：gengchenghao (赞：3)

# 思路
要将所以小于 $\frac{T}{2}$ 的数放入第一个集合中，将大于 $ \frac{T}{2}$ 的数放入第二个集合这样二元组 $(i,j)$ 数量归零。  
然后处理等于 $\frac{T}{2}$ 的数将它们平均放入两个集合，你一个我一个。
## code
```cpp
#include <bits/stdc++.h>
using namespace std;
int T;
int main(){
	cin>>T;
	while(T--){
        int n,t,tmp,p=0;
		cin>>n>>t;
		for(int i=1;i<=n;i++){
			cin>>tmp;
			if(tmp*2<t) cout<<0<<" ";
			else if(tmp*2==t){
                cout<<p<<" ";
                p=p^1;
            }
			else cout<<1<<" ";
		}
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：是个汉子 (赞：3)

### Solution

因为要求 $f$ 最小，我们发现只要将 $a_i$ 和 $T-a_i$ 染成不同的颜色就行了。

但是当 $T$ 为偶数的时候， $\frac T2$ 是要一个染白，一个染黑这样轮流的。

举个例子：设 $k$ 为 $\frac T2$ 的个数，那么如果将 $k$ 个全染一个颜色，则 $f$ 起码是 $\frac{(k-1)k}{2}$ ，然后平均分成两种颜色，则是 $(\frac k2-1)\frac k2$ ，是小于前值的。

注意：因为 $1\leq a_i\leq 10^9$ ，所以可以拿 $map$ 来做映射。

​		（要么开全局记得清零，要么开局部变量，不要像我一样没有清零然后考场爆零）

### 代码

```c++
#include<bits/stdc++.h>

using namespace std;
const int N=1e5+10;
int n,t,col[N],a[N],pre;
map<int,int> mp;

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        pre=0;
        mp.clear();
        scanf("%d%d",&n,&t);
        if(t%2){
            for(int i=1;i<=n;i++){
                scanf("%d",&a[i]);
                if(mp[a[i]]) col[i]=1;
                else{
                    col[i]=0;
                    if(a[i]<=t) mp[t-a[i]]=1;//可以不判的，比赛的时候忘了qwq
                }
            }
            for(int i=1;i<=n;i++)
                printf("%d ",col[i]);
            puts("");
        }
        else{
            for(int i=1;i<=n;i++){
                scanf("%d",&a[i]);
                if(a[i]==t/2){
                    if(pre) col[i]=1^col[pre];
                    pre=i;
                    continue;
                }
                if(mp[a[i]]) col[i]=1;
                else{
                    col[i]=0;
                    if(a[i]<=t) mp[t-a[i]]=1;
                }
            }
            for(int i=1;i<=n;i++)
                printf("%d ",col[i]);
            puts("");
        }
    }
    return 0;
}
```



---

## 作者：mot1ve (赞：2)

这题一开始真没想出来。。但其实很简单，由于是两个数，小于 $T/2$ 的放左，大于的放右，正好等于的一左一右放。因为小于 $T/2$ 的两个数加起来一定还是小于 $T/2$ ，大于 $T/2$ 的两个数加起来一定大于 $T/2$ 。这个性质想到就秒题了。

超短代码：

```
#include<bits/stdc++.h>
using namespace std;
int n,TT,T,a[100010],col[100010];
int main()
{
	cin>>TT;
	while(TT--)
	{
		int t=0;
		cin>>n>>T;
		for(int i=1;i<=n;i++)
		cin>>a[i];
		for(int i=1;i<=n;i++)
		{
			if(a[i]*2>T) col[i]=1;
			if(a[i]*2<T) col[i]=0;
			if(a[i]*2==T)
			{
				t++;
				col[i]=t%2;
			}
		}
		for(int i=1;i<=n;i++)
		cout<<col[i]<<" ";
		puts(""); 
	}
	return 0;
} 
```

---

## 作者：Coffee_zzz (赞：1)

诈骗题。

### 分析

考虑将所有小于 $\dfrac{T}{2}$ 的数放到集合 $0$，大于$\dfrac{T}{2}$ 的数放到集合 $1$，如此一来可以使二元组 $(i,j)$ 的数量变为 $0$。

接着考虑等于 $\dfrac{T}{2}$ 的数。可以考虑穿插开来，第一个数放在集合 $0$ 中，第二个数放在集合 $1$ 中，以此类推，可以使 $(i,j)$ 的数量尽可能少。

甚至不需要使用数组。

### 代码

```c++
#include <bits/stdc++.h>
using namespace std;
int main(){
	ios::sync_with_stdio(0);
	int q,n,t,x,p;
	cin>>q;
	for(int temp=0;temp<q;temp++){
		cin>>n>>t;
		p=0;
		for(int i=0;i<n;i++){
			cin>>x;
			if(x*2<t) printf("0 ");
			else if(x*2==t) printf("%d ",p),p=p^1;
			else printf("1 ");
		}
		printf("\n");
	}
	return 0;
}
```

---

## 作者：FuriousC (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1417B)

思路：结论题

**结论**：$<\lfloor\dfrac{T}{2}\rfloor$ 的放一个集合，$>\lfloor\dfrac{T}{2}\rfloor$ 的放另一个集合，剩下的平均放在两个集合中即可。

**证明**：有题目知所有输入的 $a_i$ 都是非负数，所以对于 $a_i+a_j=T(a_i<a_j)$，有两种情况：

- $a_i=a_j=\lfloor\dfrac{T}{2}\rfloor$

- $a_i<\lfloor\dfrac{T}{2}\rfloor,a_j>\lfloor\dfrac{T}{2}\rfloor$

因此将所有 $<\lfloor\dfrac{T}{2}\rfloor$ 一类的数放在一个集合中，所有 $>\lfloor\dfrac{T}{2}\rfloor$ 一类的放在一个集合中：

这样可以保证每个集合中不会有两个数加起来 $=T$，剩下的数平均着放就可以使每个集合中加起来 $=T$ 的数对最少。

**代码**：

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100005],pos[100005];
int main(){
	int t;
	cin>>t;
	while(t--){
		int n,T,tmp=0;
		cin>>n>>T;
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		for(int i=1;i<=n;i++){
			if(a[i]*2>T){
				pos[i]=1;
			}else if(a[i]*2<T){
				pos[i]=0;
			}else if(a[i]*2==T){
				tmp++;pos[i]=tmp%2;
			}
		}
		for(int i=1;i<=n;i++){
			cout<<pos[i]<<" ";
		}
		cout<<"\n";
	}
	return 0;
}
```


---

## 作者：STDquantum (赞：1)

发现对于一个确定的值 $x$，若 $T-x$ 不和它在同一集合中，那么会使答案更优。而且对于每个不同的 $x$，所能影响到的只有 $T-x$，所以每个元素对都是独立的。

所以我们能得出一种解法：如果 $T-x$ 在序列中，那么就把其中任意一个标记为 1，另一个为 0。

但是这只对 $x\ne T-x$ 起作用，因为若 $\displaystyle x=\frac T2$ 的数量比 $2$ 大，就无法保证不出现符合条件的二元组。

所以考虑如何排布这些 $\displaystyle x=\frac T2$，使得 $\displaystyle \left(\begin{array}c cnt_1\\2\end{array}\right)+\left(\begin{array}c cnt_2\\2\end{array}\right)$ 最小。

令 $n=cnt_1$，$m=cnt_2$，分别为两个集合中 $\displaystyle x=\frac T2$ 的数量，$n+m=C$ 为定值。

则想要求的式子 $\displaystyle ans=\frac{n\cdot(n-1)}2+\frac{m\cdot(m-1)}2=\frac{n^2+m^2}2-\frac{n+m}2=\frac{n^2+m^2}2-\frac{C}2$，

根据基本不等式的变形，有 $\displaystyle ans\ge \frac{(n+m)^2}2-\frac{C}2=\frac{C^2-C}2$，当且仅当 $n=m$ 时等号成立。

而由于 $n,m$ 均为整数，则 $\vert n-m\vert\le1$，也就是取其中一个为 $\displaystyle \left\lfloor\frac C2\right\rfloor$ 就可以了。

代码中把存在 $\displaystyle x=\frac T2$ 与否分开考虑。

```cpp
const int N = 2e5 + 10;
struct E {
    int x, id;
} a[N];
int n, t, T, b[N], pos[N];
map<int, bool> vis;
inline void main() {
    for (read(t); t--; vis.clear()) { // 记得清空vis
        read(n), read(T);
        memset(pos, 0, sizeof(pos));
        if (T % 2) {
            for (int i = 1; i <= n; ++i) { read(b[i]); }
            for (int i = 1; i <= n; ++i) {
                if (vis[b[i]]) {
                    pos[i] = 1;
                } else {
                    vis[T - b[i]] = true;
                }
            }
        } else {
            int cnt = 0, cntT = 0;
            for (int i = 1, x; i <= n; ++i) {
                read(x);
                if (x == T / 2) {
                    b[++cntT] = i;
                } else {
                    a[++cnt] = (E){x, i};
                }
            }
            for (int i = 1; i <= cnt; ++i) {
                if (vis[a[i].x]) {
                    pos[a[i].id] = 1;
                } else {
                    vis[T - a[i].x] = true;
                }
            }
            for (int i = 1; i <= cntT / 2; ++i) { pos[b[i]] = 1; }
        }
        for (int i = 1; i <= n; ++i) putchar(pos[i] + '0'), putchar(' ');
        putchar('\n');
    }
}
```



---

## 作者：Laisira (赞：1)

### 题面
给一串序列和常数 $T$，你要将他们分成两组，最小化两组每一组中任意 $i,j$ 有 $a_i+a_j=T$ 的数量和。

### 思路
纯纯的构造题，要有 $a_i+a_j=T$，第一种是 $a_i$ 和 $a_j$ 一个比 $T/2$ 大另一个小，第二种都是 $T/2$。于是分组方式就是大于 $T/2$ 的一组，小于一组，而等于的就一组一半。

### 代码
```cpp
#include<bits/stdc++.h>
#define Maxn 100005 
using namespace std;
int res[Maxn];
bool color[Maxn];
int main()
{
    int t,n,k;
    cin>>t;
    while(t--) {
        int tot=0;
        cin>>n>>k;
        for(int i=1;i<=n;i++)
        {
            int u;
            cin>>u;
            if((u<<1)>k)color[i]=1;
            else if((u<<1)<k)color[i]=0;
            else res[++tot]=i;
        }
        for(int i=1;i<=tot/2;i++)
            color[res[i]]=0;
        for(int i=tot/2+1;i<=tot;i++)
            color[res[i]]=1;
        for(int i=1;i<=n;i++)
            cout<<color[i]<<" ";
        puts("");
    }
    return 0;
}
```

---

## 作者：yu1128_AKIOI (赞：0)

# 思路

要把小于 $\frac{T}{2}$ 的元素放到一个集合，大于 $\frac{T}{2}$ 的元素放到另一个集合。因为小于 $\frac{T}{2}$ 的两数相加小于 $ T $，反之则大于 $ T $。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int T;
int main(){
	cin>>T;
	while(T--){
        int n,t,p=0;
		cin>>n>>t;
        for(int i=1;i<=n;i++){
            int a;
			cin>>a;
			if(a*2<t) cout<<"0 ";
			else if(a*2==t){
                cout<<p<<" ";
                p=p^1;
            }
			else cout<<"1 ";
		}
		cout<<endl;
	}
}
```

---

## 作者：zhengpie (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1417B)

### 1.思路

诈骗题。

不妨设两个集合分别为 $A,B$，题目说让同时满足 $\forall {a_i,a_j}(i \lt j) \in A $ 与 $a_i + a_j = T$ 或者 $\forall {a_i,a_j}(i \lt j) \in B $ 与 $a_i + a_j = T$ 的组数最小，那么考虑的极端一点，把集合 $A$ 的每个元素都设很小，使得 $\forall {a_i,a_j}(i \lt j) \in A $ 都有 $a_i + a_j \lt T$,再把把集合 $B$ 的每个元素都设很大，使得 $\forall {a_i,a_j}(i \lt j) \in B $ 都有 $a_i + a_j \gt T$。这样，不就最小了吗？

### 2.细节

按照前面那么说，对于一个 $a_i$：

- 如果 $a_i \lt \Large{\lfloor{\frac{T}{2}}\rfloor}$，那么就把它归到集合 $A$ 中；

- 如果 $a_i \gt \Large{\lfloor{\frac{T}{2}}\rfloor}$，那么就把它归到集合 $B$ 中；

- 如果 $a_i = \Large{\lfloor{\frac{T}{2}}\rfloor}$，那么该怎么办呢？这时，我们考虑上一个满足 $a_k = \Large{\lfloor{\frac{T}{2}}\rfloor}$，与它放的集合错开即可。就假设 $a_k \in A$，那么那么就把 $a_i$ 归到集合 $B$ 中，反之亦然。

### 3.完整代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int q,n,t;
signed main()
{
	ios::sync_with_stdio(0);
	cin>>q;
	while(q--)//注意有多组数据
	{
		cin>>n>>t;
		int f = 0;
		for(int i = 1,x;i <= n;i++)
		{
			cin>>x;
			if(x * 2 < t) cout<<"0";//如果小于2分之t就放到集合0
			else if(x * 2 == t) {cout<<f;f = ((f == 0) ? 1 : 0);/*记得修改f！*/}//等于2分之t就看上一个等于2分之t的集合位置，与其错开即可。
			else cout<<"1";//如果大于2分之t就放到集合1
			if(i != n) cout<<" ";
			else cout<<endl;
		}
	}
	return 0;
}
```

---

## 作者：dlzlj_2010 (赞：0)

题目要求使集合内满足 $i<j \land a_i+a_j=T$ 的二元组 $(i,j)$ 数量最少。我们记 $a_i=t$，那么：

- 当 $t<\dfrac{T}{2}$ 时，我们将 $t$ 放到集合 $1$ 中。


- 当 $t>\dfrac{T}{2}$ 时，我们将 $t$ 放到集合 $2$ 中。


- 当 $t=\dfrac{T}{2}$ 时，为了满足条件，我们就要将 $t$ 尽量分散到两个集合里。


## code：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;

signed main(){
	int T;
	cin>>T;
	while(T--){
		int n,t;
		cin>>n>>t;
		vector<int> v(n+5);
		vector<bool>ans(n+5);
		for(int i=1;i<=n;i++){
			cin>>v[i];
		}
		bool f=0;
		for(int i=1;i<=n;i++){
			int x=v[i];
			if(2*x>t)ans[i]=0;
			else if(2*x<t) ans[i]=1;
			else{
				ans[i]=f,f=!f;
			}
		}
		for(int i=1;i<=n;i++){
			cout<<ans[i]<<" ";
		}
		puts("");
	}
	return 0;
}
```

---

## 作者：ny_Dacong (赞：0)

读完题后，发现题目实际上要把加起来等于 $T$ 的两个元素尽可能分在不同的集合里。发现这个之后，做题就很简单了。

如何要把加起来等于 $T$ 的两个元素尽可能分在不同的集合里？

很明显，我们要尽可能让 $a_i \times 2 < T$ 的元素 $a_i$ 放在集合 $0$。$a_i \times 2 > T$ 的元素 $a_i$ 放在集合 $1$。这样，同一集合里任意两个元素相加都不可能等于 $T$。换言之，加起来等于 $T$ 的两个元素被我们分在了不同的集合里。

最后，再来考虑一下 $a_i \times 2 = T$ 的情况。这种情况只能把所有 $a_i \times 2 = T$ 的 $a_i$ 交叉放在两个不同的集合里。这样才是最优的。

# AC代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,T,now;
bool flag = 0;
int main(){
    scanf("%d",&t);
    while(t--){
        scanf("%d%d",&n,&T);
        flag = 0;
        for(int i = 1; i <= n; i++){
            scanf("%d",&now);
            if(now*2 < T){
                printf("0 ");
            }else if(now*2 == T){
                printf("%d ",flag);
                flag = !flag;
            }else{
                printf("1 ");
            }
        }
        printf("\n");
    }
    return 0;
}
```

---

## 作者：Berd__ (赞：0)

~~看题面很复杂，实际上很简单~~

# 思路

如果小于 $T/2$，就放在左面，大于的放右。因为小于 $T/2$ 的两个数加起来一定还是小于 $T/2$，大于 $T/2$ 的两个数加起来一定大于 $T/2$。

写出如下代码。

```
if(a[i]*2>T) c[i]=1;
if(a[i]*2<T) c[i]=0;
if(a[i]*2==T) t++,c[i]=t%2;
```

完整代码不放了，楼上几位大佬都有放。

---

## 作者：GoodLuckCat (赞：0)

一种不用数组的方法。

把 $\le\frac T2$ 的数放到一个集合里，$\ge\frac T2$ 的数放到另一个集合里，而 $=\frac T2$ 的数平均地放，就可以满足题目的条件。

变量 $p$ 是用来平均分的。

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,a,b;
int main()
{
	cin>>t;
	while(t--)
	{
		bool p=0;
		cin>>a>>b;
		for(int i=1;i<=a;i++)
		{
		    int x;
		    cin>>x;
		    if(x*2<b)cout<<"0 ";
		    if(x*2>b)cout<<"1 ";
		    if(x*2==b)
		    {
		        p=!p;
		        cout<<p<<' ';
		    }
		}
		cout<<endl;
	}
}
```

---

## 作者：luosw (赞：0)

考虑构造出一种方法，使得尽可能不存在题目中 $a_i+a_j=T$ 的二元组 $(i,j)$。

令 $res\gets\dfrac{T}{2}$，可以发现元素的大小都是非负数，因此若 $a_i+a_j=T$ 成立，有两种情况：

1. $a_i=a_j=res$；

1. 若 $a_i<a_j$，则 $a_i<res,a_j>res$。

因此我们可以把所有小于 $res$ 的分成一组，大于 $res$ 的分成一组；等于 $res$ 的只需要保证每组个数相同或差 $1$，即换着分即可。

时间复杂度 $\mathcal O(t\cdot n)$。

---

## 作者：zxqwq (赞：0)

看到机房有人调了一个多小时于是就来写，题目的大意是如果将所有数字划分至两个集合，最小化集合中两两相加为 $T$ 的个数

如果 $T$ 是一个奇数，那么我们可以把奇数放在一边偶数放在一边，显然答案是 $0$，但是在 $T$ 为偶数的时候还要再写一次分法，于是我没用这种方法

此外我们还可以把 $<\frac{T}{2}$ 的放在一边，剩下的放在一边，答案也一定是 $0$

如果是一个偶数的话，我们只需要考虑 $\frac{T}{2}$ ，此时答案是$ \frac{l(l-1)}{2}+\frac{r(r-1)}{2}$ 设 $l+r=k$ 那么当 $l=r=\frac{k}{2}$ 的时候取到最小值

据说这是一个二分图，我太菜了还没去学

```cpp
#include<head.h>

using namespace std;

const int maxn=100200;

int a[maxn],n;
int rr,ll,sz;

int main()
{
	ios::sync_with_stdio(false);
	register int i,j;
	int t; cin>>t;
	while(t--)
	{
		rr=ll=sz=0;
		int target,lc=0;
		cin>>n>>target;
		for(i=1;i<=n;i++) 
		{
			cin>>a[i];
			if(a[i]==target/2) sz++;
		}
		if(target%2==0)
		{
			lc=1;
			ll=sz/2;
			rr=sz-ll;
		}
		for(i=1;i<=n;i++)
		{
			if(lc)
			{
				if(a[i]==target/2) if(ll) ll--,cout<<0<<" "; else rr--,cout<<1<<" ";
				else if(a[i]<target/2) cout<<0<<" ";
				else cout<<1<<" ";
			}
			else if(a[i]<=target/2) cout<<0<<" ";
			else cout<<1<<" ";
		}
		cout<<endl;
	}
	return 0;
}

```



---

