# Median Queries

## 题目描述

This is an interactive problem.

There is a secret permutation $ p $ ( $ 1 $ -indexed) of numbers from $ 1 $ to $ n $ . More formally, for $ 1 \leq i \leq n $ , $ 1 \leq p[i] \leq n $ and for $ 1 \leq i < j \leq n $ , $ p[i] \neq p[j] $ . It is known that $ p[1]<p[2] $ .

In $ 1 $ query, you give $ 3 $ distinct integers $ a,b,c $ ( $ 1 \leq a,b,c \leq n $ ), and receive the median of $ \{|p[a]-p[b]|,|p[b]-p[c]|,|p[a]-p[c]|\} $ .

In this case, the median is the $ 2 $ -nd element ( $ 1 $ -indexed) of the sequence when sorted in non-decreasing order. The median of $ \{4,6,2\} $ is $ 4 $ and the median of $ \{0,123,33\} $ is $ 33 $ .

Can you find the secret permutation in not more than $ 2n+420 $ queries?

Note: the grader is not adaptive: the permutation is fixed before any queries are made.

## 说明/提示

The secret permutation is $ \{9,10,19,7,16,18,11,14,15,6,20,8,17,4,5,3,12,2,13,1\} $ .

For the first query, the values of $ (a,b,c) $ is $ (1,5,2) $ . Since $ p[1]=9 $ , $ p[5]=16 $ and $ p[2]=10 $ . The return value is the median of $ \{|9-16|,|16-10|,|9-10|\} $ which is $ 6 $ .

For the second query, the values of $ (a,b,c) $ is $ (20,19,2) $ . Since $ p[20]=1 $ , $ p[19]=13 $ and $ p[2]=10 $ . The return value is the median of $ \{|1-13|,|13-10|,|1-10|\} $ which is $ 9 $ .

By some miracle, we have figured out that the secret permutation is $ \{9,10,19,7,16,18,11,14,15,6,20,8,17,4,5,3,12,2,13,1\} $ . We output it and receive $ 1 $ from the interactor, meaning that we have guessed the secret permutation correctly.

## 样例 #1

### 输入

```
1
20

6

9

1```

### 输出

```
? 1 5 2

? 20 19 2

! 9 10 19 7 16 18 11 14 15 6 20 8 17 4 5 3 12 2 13 1```

# 题解

## 作者：dztlb (赞：11)

[CF1526F Median Queries](https://www.luogu.com.cn/problem/CF1526F)

人类智慧构造题。

首先转化询问。$|p_a-p_b|,|p_b-p_c|,|p_c-p_a|$ 这三个数中第二小的数。如果我们钦定 $p_a<p_b<p_c$，我们每次询问就得到 $max(p_b-p_a,p_c-p_b)$。

~~开脑洞~~，一个不是很显然的思路：如果我们让 $p_a,p_b$ 或者 $p_b,p_c$ 挨得足够近，每次询问就能确定得到 $p_b-p_a$ 或 $p_c-p_b$。

最极端的情况是直接将两个值确定为 $1,2$ 或 $n-1,n$，我们就能使用 $n-2$ 次操作确定其他值。问题转化为如何在 $n+420$ 次操作内找到这两对数的任意一对。

同样回到开始的思路，如果我们确定了两个离得较近的值，再以此询问其他所有的位置，大概率距离最远和第二远的值就是 $1,2$ 或 $n-1,n$。这一步仍然要使用 $n-2$ 次操作。

那么剩下的 $420$ 次操作我们找那两个离得较近的值，我们只能随机化了。

有两个问题：距离多小才能保证正确？距离多小才能保证随机次数不超过 $420$？

显然，如果距离小于 $\frac{n-4}{3}$，就能够保证正确（刨掉的四个点是将要选定的四个点：两个较近值和两对数的任意一对）。而随机时保证距离小于 $\frac{n-4}{6}$ 就能保证 $|p_a-p_b| \leq 2*\frac{n-4}{6}=\frac{n-4}{3}$。

次数限制：取 $420$ 次，取不到的概率 $(\frac{8}{9})^{420}\approx 3.28*10^{-22}$。

还有具体细节看代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5;
int T,n;
int val[maxn+5];
int p[maxn+5];
int query(int a,int b,int c){
	int x;
	printf("? %d %d %d\n",a,b,c);
	fflush(stdout);
	scanf("%d",&x);
	return x;
}
int main(){
	scanf("%d",&T);
	while(T--){
		int a,b;
		scanf("%d",&n);
		bool ok=0;
		for(int i=1;i<=13&&!ok;i++)
			for(int j=i+1;j<=13&&!ok;j++)
				for(int k=j+1;k<=13&&!ok;k++)
					if(query(i,j,k)*6<=n-4){
						a=i; b=j; ok=1;
					}
		int nowid,nows=0;
		int y[5],toty=0;
		for(int i=1;i<=n;i++){
			val[i]=0;
			if(i==a||i==b) continue;
			val[i]=query(a,b,i);
			if(val[i]>nows){
				nows=val[i]; nowid=i;
			}
		}
		//nowid 是距离它们最大的那个 
		for(int i=1;i<=n;i++)
			if(val[i]==nows-1) y[++toty]=i;
		if(toty==1){ a=nowid; b=y[1]; }
		else{
			int v1=query(nowid,a,y[1]),v2=query(nowid,a,y[2]);
			a=nowid;
			if(v1<v2) b=y[1];
			else b=y[2];
		}
		p[a]=1; p[b]=2;
		//确定 1 2 的位置 
		for(int i=1;i<=n;i++) if(i!=a&&i!=b) p[i]=query(a,b,i)+2;
		if(p[1]>p[2]) for(int i=1;i<=n;i++) p[i]=n-p[i]+1;//满足题目要求的性质 
		printf("! ");
		for(int i=1;i<=n;i++) printf("%d ",p[i]);
		cout<<endl;
		scanf("%d",&n);
	}
	return 0;
}

 
```


---

## 作者：EuphoricStar (赞：6)

首先，如果我们确定了 $1, 2$ 或 $n - 1, n$ 的位置，我们就能求出原排列。因为题目给了 $p_1 < p_2$，所以可以不考虑对称性。也就是说我们知道两个位置是 $1, 2$ 或 $n - 1, n$ 但不确定究竟是 $1, 2$ 还是 $n - 1, n$ 也可以。

然后，如果我们确定了一对挨得够近的一对数 $i, j$，用它们再去问剩下的，距离最大和次大的就是 $1, 2$ 或 $n - 1, n$。（有个 corner case，若 $p_i + p_j = n - 1$，那么最大和次大值都有两个，注意判一下）

发现只要 $|i - j| \le \frac{n - 4}{3}$，距离最大和次大的就是 $1, 2$ 或 $n - 1, n$。

上面用了 $2(n - 2)$ 次操作，还剩下 $424$ 次操作留给随机化。随机问一些 $(a, b, c)$，如果回答 $\le \frac{n - 4}{6}$，那它们两两距离都 $\le \frac{n - 4}{3}$。操作次数很充裕，随不到的概率 $< 10^{-10}$。

[code](https://codeforces.com/problemset/submission/1526/235461316)

---

## 作者：BPG_ning (赞：2)

~~爆标。~~

## $ n^3 $

首先你可以 $ n^3 $ 的求出每一对的答案，如果 $ ask(a,b,c) = 1 $ 那么 $ p_a,p_b,p_c $ 在值域上是相邻的，因为序列是较长的，所以一定有解，并且保证 $ p_1 < p_2 $ ，所以解唯一（因为将 $ p_i \gets n-p_i+1 $ 之后查询结果都不变，若不保证这一点就会有两个解）。

这个 $ n^3 $ 做法能告诉我们这题是可做的。

## $ n^2 $

考虑对于一个点 $ {pos} $ 求出其他点的相对位置。

先考虑求 $ |p_{pos} - p_i| $，钦定 $ p_{pos}<p_{i} $。

**定理一**：发现一个 $ ask(a,b,c) $ 在数轴上的意义是按顺序排列的三点的相邻两点的距离较大值。

**定理二**：对于每个 $ p_{pos}<p_{j}<p_{i} $ 的 $ j $ 的 $ ask(i,j,pos) $ 一定小于不在区间里的 $ j' $ 的 $ ask(i,j',pos) $。

---

定理二证明：

根据定理一：

$ \max(p_{i}-p_{pos},d) \geq p_{i}-p_{pos} > \max(p_i-p_j,p_j-p_{pos}) $.

---

我们称 $ [p_{pos},p_i] $ 为区间。

然后我们发现对于在区间里的 $ j' $ 的 $ ask(i,j,pos) $ 的最小值就是区间长的一半！

因为他是 $ [p_{pos},p_j] , [p_j,p_i] $ 长度的较大值，当 $ p_j $ 在 $ [p_{pos},p_i] $ 中点时是最小的。

而我们还关心区间长的奇偶性，我们只需要数最小值出现几次即可！

我们 $ n $ 次询问求出区间长，这就是 $ p_i $ 到 $ p_{pos} $ 的距离！随便钦定一点在 $ p_{pos} $ 左边，通过定理二判断其他 $ p_i $ 在左边还是在右边，最后判断 $ p_1,p_2 $ 的大小关系镜像处理即可。

## $ 2n + C $

我们抛开求每个点到一个点的距离的想法，考虑求极值。

具体来说如果我们找到了 $ p_i=1,p_j=2 $ ，那么 $ p_k=ask(i,j,k)+2 $ ，我们就可以用 $ n-2 $ 次询问求出答案！

现在我们需要用 $ C+n+2 $ 次询问找到这个极值。

假设我们有一个**较短**的区间 $ [p_l,p_r] $，由于序列是较长的，根据定理一，我们可以找到所有 $ ask(i,l,r) $ 的**最大**和**次大**的 $ i $ 并认为他们是极值，因为他们是在数轴上距离 $ [p_l,p_r] $ 最远的点，自然是极值。

而且我们能发现**较短**的区间的定义是 $ len \leq \frac{n}{3} $，因为若区间长 $ > \frac{n}{3} $，那么可能存在两端的极值 $ ask(l,r,i) = | p_r-p_l | $，这样你就无法区分极值了。

所以如果我们找到一个**较短**的区间，用 $ n-2 $ 次询问就可以找到极值！

考虑用 $ C+4 $ 次询问找到任意**较短**的区间，一个很好的想法就是随机化，每次随一个 $ a,b,c $ ，若 $ ask(a,b,c) \leq \frac{n}{6} $ ，那么这三点中任意两点构成的区间都是**较短**的！

---

证明：

令 $ p_a<p_b<p_c $.

那么根据定理一有 $ \frac{n}{6} \geq ask(a,b,c) = \max(p_b-p_a,p_c-p_b) \geq \frac{p_c-p_a}{2} $.

所以 $ p_c-p_a \leq \frac{n}{3} $.

$ p_b-p_a,p_c-p_b \leq \max(p_b-p_a,p_c-p_b) \leq \frac{n}{6} \leq \frac{n}{3} $.

---

随一次随不到的概率约为 $ \frac{8}{9} $ ，那么随 $ C+4 $ 次随不到的概率是 $ {(\frac{8}{9})}^{C+4} $ ，是极小的，所以可以认为这是正确的。

## $ 2n $

~~我们再抛开找极值的思路。~~

考虑将找极值弱化，只要找到一对相邻的元素，即长度为 $ 1 $ 的区间。

怎么找呢？根据 $ n^2 $ 做法，考虑 $ [p_1,p_2] $ 这个区间，先用 $ n-2 $ 次询问算出这个区间长度 $ len $，根据定理二能知道那些点在区间里面，即满足 $ p_1 < p_i < p_2 $。

能把区间内的每一个元素求出来吗？考虑随便找到一个 $ {mid} $（区间长为奇数的时候不关心这是靠左的中点还是靠右的中点），用 $ len $ 次询问同理得出 $ p_2-p_{mid} $，再次根据定理二得知那些点在区间 $ [p_{mid},p_2] $ 里！由于这是中点，所以这样你就可以知道区间里每一个 $ ask(1,2,i) $ 是 $ p_2-p_i $ 还是 $ p_i-p_1 $。

我们用 $ len+n-2 $ 次询问，但是求出了区间内的所有点，我们在区间里找到 $ pos $ 满足 $ p_{pos}=p_1+1 $ ，那么我们就找到了一对相邻的元素，满足 $ ask(1,pos,i) = p_1-p_i $ 或 $ p_i-p_{pos} $，这是显然的。

我们对于不在区间里的 $ n-len-2 $ 个点询问 $ ask(1,pos,i) $ ，如果我们知道这个点是 $ p_i<p_1 $ 还是 $ p_{pos}<p_i $ 我们就做完了！

我们结合 $ ask(1,2,i) $ 进行分类讨论：

1.若 $ ask(1,2,i)=len,ask(1,pos,i)<len $，那么 $ p_i<p_1 $。

2.若 $ ask(1,2,i)=len,ask(1,pos,i)>len $，那么 $ p_i>p_{pos} $。

3.若 $ ask(1,2,i)>len,ask(1,pos,i)=ask(1,2,i) $，那么 $ p_i<p_1 $。

4.若 $ ask(1,2,i)>len,ask(1,pos,i) \ne ask(1,2,i) $，那么 $ p_i>p_{pos} $。

5.若 $ ask(1,2,i)=len,ask(1,pos,i)=len $，此时你无法只通过这两种询问区分 $ p_i=p_1-len $ 和 $ p_i=p_{pos}+len $。因为这种情况只会出现一次，我们可以询问 $ ask(1,mid,i) $ 来区分他们（总之是好做的）。

这部分读者根据定理一手玩即可发现。

$ ask(1,2,i)=len $ 意味着 $ p_i \in [p_1-len,p_1] \cup [p_2,p_2+len] $，所以在左边的都是 $ ask(1,pos,i) \leq len $，在右边都是 $ ask(1,pos,i) \geq len $，特殊情况再多花一次询问即可。

总询问次数为 $ n+len-2+n-len-2+1=2n-3 $。

但是我们刚刚都是默认区间较长，应为如果区间较短可能出现包括但不限于无法区分 $ len=1 $ 和 $ len=2 $ 的区间、$ mid=pos $ 等等问题，尤其是对于 $ p_1=1,p_2=2 $ 的情况是很棘手的。

所以我们要接着大分讨？

不妨回头看看，对于**较短**的区间我们不是已经有做法了吗！

于是我们的总操作次数为 $ \max(2n-3,2n-2)=2n-2 $。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N=1e5+10;
void over(){cout<<"dou guai sqy"<<endl;exit(0);}
int n,l,r,len,d1[N],d2[N],ans[N];
int ask(int a,int b,int c){
    int op=0;
    cout<<"? "<<a<<' '<<b<<' '<<c<<endl;
    cin>>op;
    if(op==-1) over();
    return op;
}
namespace sol1{
    void work(){
        int fl=0,fr=0,m=0,c=0;
        for(int i=1;i<=n;i++) m=max(m,d1[i]);
        for(int i=1;i<=n;i++) if(d1[i]==m) fr=i;
        for(int i=1;i<=n;i++) if(d1[i]==m-1){
            if(fl==0) fl=i;
            else{
                if(ask(fr,l,i)<ask(fr,l,fl)) fl=i;
            }
        }

        ans[fr]=1; ans[fl]=2;
        for(int i=1;i<=n;i++) if(i!=fr && i!=fl) ans[i]=ask(fl,fr,i)+2;
    }
}
namespace sol2{
    int chk(int Minid,int m){
        int Min=len,c=0;
        for(int i=1;i<=n;i++) if(d1[i]<len && i!=l && i!=r && i!=Minid){
            Min=min(Min,d2[i]);
        }
        for(int i=1;i<=n;i++) if(d1[i]<len && i!=l && i!=r && i!=Minid){
            if(d2[i]==Min) c++;
        }
        return Min*2+1-c;
    }
    void work(int Minid){
        int m=d1[Minid],c=0;
        for(int i=1;i<=n;i++) if(d1[i]==m) c++;
        len=m*2+1-c;
        ans[l]=1; ans[r]=len+1;
        int fl=0,id=0;
        for(int i=1;i<=n;i++) if(d1[i]<len && i!=l && i!=r && i!=Minid){
            d2[i]=ask(Minid,i,r);
        }
        int llen=chk(Minid,m);
        ans[Minid]=ans[r]-llen;
        for(int i=1;i<=n;i++) if(d1[i]<len && i!=l && i!=r && i!=Minid){
            if(d2[i]<llen) ans[i]=ans[l]+d1[i];
            else ans[i]=ans[r]-d1[i];
        }
        for(int i=1;i<=n;i++) if(ans[i]==m+1) id=i;
        for(int i=1;i<=n;i++) if(d1[i]<len && ans[i]==2) fl=i;

        for(int i=1;i<=n;i++) if(d1[i]>=len){
            int k=ask(l,fl,i);
            if(d1[i]==len){
                if(k==len){
                    if(ask(l,id,i)==len) ans[i]=ans[l]-k;
                    else ans[i]=ans[fl]+k;
                }
                else if(k<len) ans[i]=ans[l]-k;
                else ans[i]=ans[fl]+k;
            }else{
                if(d1[i]==k) ans[i]=ans[l]-k;
                else ans[i]=ans[fl]+k;
            }
        }
    }
}
void work(){
    cin>>n;
    l=1,r=2;
    for(int i=3;i<=n;i++) d1[i]=ask(l,r,i);
    int Minid=3;
    for(int i=4;i<=n;i++) if(d1[i]<d1[Minid]) Minid=i;
    if(d1[Minid]<=2){
        sol1::work();
    }else{
        sol2::work(Minid);
    }
}
int tid[N];
bool cmp(int i,int j){return ans[i]<ans[j];}
void out(){
    for(int i=1;i<=n;i++) tid[i]=i;
    sort(tid+1,tid+1+n,cmp);
    for(int i=1;i<=n;i++) ans[tid[i]]=i;
    if(ans[1]>ans[2]){
        for(int i=1;i<=n;i++) ans[i]=n-ans[i]+1;
    }
    cout<<"! ";
    for(int i=1;i<=n;i++) cout<<ans[i]<<' '; cout<<endl;
    int op=0;
    cin>>op;
    if(op==-1) over();
}
void clear(){
    l=r=len=0;
    for(int i=1;i<=n;i++){
        d1[i]=d2[i]=ans[i]=0;
    }
}
int main(){
    int T=1;
    cin>>T;
    for(int c=1;c<=T;c++){
        work();
        out();
        clear();
    }
    cerr<<1.0*clock()/CLOCKS_PER_SEC<<'\n';
    return 0;
}
//nzq
```

---

## 作者：happybob (赞：0)

真是人能想到的吗？

首先注意到 $i$ 与 $n-i+1$ 对称。对于排列 $p_i$ 和 $q_i = n-p_i+1$，所有询问结构都相同。题目要求 $p_1 < p_2$ 本质上是确定了 $p$ 和 $q$ 谁是答案。

一个显然的观察是，如果设询问满足 $p_a < p_b < p_c$，那么询问返回 $\max\{p_b-p_a,p_c-p_b\}$。

进一步地，如果我们知道 $1$ 和 $2$ 的位置，那么询问每个位置都可以直接知道这个位置的值。故问题转化为在 $n+422$ 次询问内找到 $1$ 和 $2$。

然后考虑怎么找 $1$ 和 $2$。如果我们能找到 $i,j$ 使得 $p_i$ 和 $p_j$ 的差比较小，那么询问其他所有 $n-2$ 个 $(p_i,p_j,k)$，得到的最大值和次大值大概率就是 $1$ 和 $2$。特别地，当 $p_i+p_j=n+1$ 时次大值会同时找到 $2$ 和 $n-1$，这里可以花两次操作特判一下谁是 $2$。

进一步分析当 $\left| p_i - p_j \right| \leq \dfrac{n-4}{3}$ 时上述做法总是对的。现在考虑随机化，每次随机询问 $(a,b,c)$，若询问结果不超过 $\dfrac{n-4}{6}$，那么两两之差显然不超过 $\dfrac{n-4}{3}$。有大约 $420$ 次随机化的机会，完全可以通过。

代码：


```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <array>
#include <vector>
#include <random>
using namespace std;

const int N = 1e5 + 5;

int t, n;
array<int, N> p, res;
mt19937 rnd(114514);

int query(int a, int b, int c)
{
	cout << "? " << a << " " << b << " " << c << "\n";
	cout.flush();
	int x;
	cin >> x;
	return x;
}

int main()
{
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> t;
	while (t--)
	{
		cin >> n;
		uniform_int_distribution<int> rg(1, n);
		int nd = (n - 4) / 6, pa = -1, pb = -1;
		while (true)
		{
			int a = rg(rnd), b = rg(rnd), c = rg(rnd);
			while (a == b || a == c || b == c)
			{
				a = rg(rnd), b = rg(rnd), c = rg(rnd);
			}
			if (query(a, b, c) <= nd)
			{
				pa = a, pb = b;
				break;
			}
		}
		int pos1 = 0, maxn = -1;
		for (int i = 1; i <= n; i++)
		{
			if (i == pa || i == pb) continue;
			int val = query(pa, pb, i);
			res[i] = val;
			if (val > maxn) maxn = val, pos1 = i;
		}
		int pos21 = 0, pos22 = 0;
		for (int i = 1; i <= n; i++)
		{
			if (i == pa || i == pb) continue;
			if (res[i] == maxn - 1)
			{
				if (!pos21) pos21 = i;
				else pos22 = i;
			}
		}
		if (pos21 && pos22)
		{
			if (pa > pb) swap(pa, pb);
			int q1 = query(pos1, pos21, pa), q2 = query(pos1, pos22, pa);
			if (q2 < q1) pos21 = pos22;
		}
		p[pos1] = 1, p[pos21] = 2;
		for (int i = 1; i <= n; i++)
		{
			if (i == pos1 || i == pos21) continue;
			int v = query(pos1, pos21, i);
			p[i] = v + 2;
		}
		if (p[1] > p[2]) for (int i = 1; i <= n; i++) p[i] = n - p[i] + 1;
		cout << "! ";
		for (int i = 1; i <= n; i++) cout << p[i] << " ";
		cout << "\n";
		cout.flush();
		int x;
		cin >> x;
	}
	return 0;
}
```

---

