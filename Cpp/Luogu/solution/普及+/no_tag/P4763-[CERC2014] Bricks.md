# [CERC2014] Bricks

## 题目描述

给你一个由 'B' 和 'W' 组成的序列，将其按分成最多的区间且每个区间的 'B':'W' 的值相等。

## 样例 #1

### 输入

```
3
3
1 B
3 W
2 B
4
3 W
3 B
9 W
1 B
2
2 W
3 W```

### 输出

```
2
3
5```

# 题解

## 作者：XL4453 (赞：5)

### 解题思路：

首先特殊处理比值恒为 $0$ 和不存在比值的情况，也就是全是 $\text{W}$ 或者 $\text{B}$，明显这两种情况下每一个字符分一组就是最优解。

对于其它情况，发现所有段的比值都等于整个串里面的比值，也就是比值固定。在这个前提下，发现如果对于某一个满足比值区间，其子区间同样满足这个比值，将这个大区间拆成这个子区间和其补集同样满足条件，而且划分出的区间还多了一个。由此得出结论，每一次从边缘贪心地选取出最短可以满足条件的区间一定是最优的。

具体判断时可以计算出当前情况下满足条件需要的数量，检验这个数量是否可以被取到即可。总复杂度 $O(n)$。


---
### 代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
#define int long long
const int MAXN=100005;
int T,n,cnt1,cnt2,num[MAXN],col[MAXN],ans,c1,c2,t;
char c;
int gcd(int a,int b){
	if(b==0)return a;
	return gcd(b,a%b);
}
void init(){
	cnt1=cnt2=ans=c1=c2=t=0;
}
signed main(){
	scanf("%lld",&T);
	while(T--){
		init();
		scanf("%lld",&n);
		for(int i=1;i<=n;i++){
			scanf("%lld",&num[i]);
			for(c=getchar();c!='B'&&c!='W';c=getchar());
			if(c=='B')col[i]=1,cnt1+=num[i];
			else col[i]=2,cnt2+=num[i];
		}
		if(cnt1==0||cnt2==0){
			printf("%lld\n",cnt1+cnt2);
			continue;
		}
		int GCD=gcd(cnt1,cnt2);
		cnt1=cnt1/GCD;cnt2=cnt2/GCD;
		for(int i=1;i<=n;i++){
			if(col[i]==1){//当前为黑 
				//(c1+k)/c2==cnt1/cnt2
				//k==cnt1*c2/cnt2-c1
				if(c2%cnt2!=0){
					c1+=num[i];
					continue;
				}
				t=(cnt1*(c2/cnt2))-c1;
				if(c2&&t>=0&&t<=num[i])ans++,c1=num[i]-t,c2=0;
				else c1+=num[i];
			}
			else{
				if(c1%cnt1!=0){
					c2+=num[i];
					continue;
				}
				t=(cnt2*(c1/cnt1))-c2;
				if(c1&&t>=0&&t<=num[i])ans++,c2=num[i]-t,c1=0;
				else c2+=num[i];				
			}
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```


---

## 作者：wjr_jok (赞：2)

## 题意

有一个由 $B$ 和 $W$ 组成的字符串，要将它划分成尽量多的区间，并使得每个区间中 $B$ 和 $W$ 的比例相等。

## 思路

首先需要知道的一点是，不管划分成多少个区间，如果要保证它们中 $B$ 和 $W$ 的比例相等，那么它们和原字符串中 $B$ 和 $W$ 的比例是一样的。

那么就很容易得到一个策略：**能分就分**

不难想，但还是小证一下：设原字符串有 $a \times x$ 个 $B$，$b \times x$ 个 $W$，那么当我们分去一个有 $a \times y$ 个 $B$，$b \times y$ 个 $W$ 的区间后，这个字符串就会剩下 $a \times (x-y)$ 个 $B$，$b \times (x-y)$ 个 $W$，比例不会变，仍然是 $\frac{a}{b}$。

所以我们只需要从头到尾遍历字符串，一旦能分区间就分区间。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t,n,x;
int b,w;
int cnt1,cnt2,gcd,ans;
char y,jl;
int xl[100001],bw[100001];
signed main(){
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=0;i<=n;i++){
			xl[i]=bw[i]=0;
		}
		b=w=cnt1=cnt2=gcd=ans=y=jl=0;
		for(int i=1;i<=n;i++){
			cin>>x>>y;
			if(y=='B'){
				b+=x;
			}
			else{
				w+=x;
			}//记录B，W的个数
			if(y==jl){
				xl[xl[0]]+=x;
			}	
			else{
				jl=y;
				xl[++xl[0]]+=x;
				if(jl=='B'){
					bw[xl[0]]=1;
				}
				else{
					bw[xl[0]]=0;
				}
             			
			}//注意，因为数据直接展开存不下，所以只能一块一块的遍历
		}
		if(!b||!w){//无解情况
			cout<<b+w<<endl;
			continue;
		}
		else{
			gcd=__gcd(b,w);
			b/=gcd;
			w/=gcd;
			for(int i=1;i<=xl[0];i++){
				if(bw[i]){
					cnt1+=xl[i];
					if(cnt2&&cnt2%w==0&&cnt1>=cnt2/w*b&&cnt1-cnt2/w*b<=xl[i]){//当前遍历到B的块
						ans++;
						cnt1=cnt1-cnt2/w*b;
						cnt2=0;
					}
				}
				else{
					cnt2+=xl[i];
					if(cnt1&&cnt1%b==0&&cnt2>=cnt1/b*w&&cnt2-cnt1/b*w<=xl[i]){//当前遍历到W的块
						ans++;
						cnt2=cnt2-cnt1/b*w;
						cnt1=0;
					}
				}
			}
			if(cnt1||cnt2){//只能分一个区间的情况
				cout<<1<<endl;
			}
			else{
				cout<<ans<<endl;
			}
		}
	}
	return 0;
} 
```

---

## 作者：LincW (赞：0)

下文中用 $B$ 表示黑块的总量，用 ${W}$ 表示白块的总量，用 $b_{i,j}$ 表示区间 $[i,j]$ 中黑块的数量，用 $w_{i,j}$ 表示区间 $[i,j]$ 中白块的数量。

（原题是 $W:B$，翻译翻成了 $B:W$）

对于任意一个划分 $\{[x_0+1,x_1],[x_1+1,x_2],\cdots,[x_{m-1}+1,x_m]\}$，其中 $x_0=1$，$x_m=\mathrm{len}$，$\forall p\in[1,m], \dfrac{w_{x_{p-1}+1,x_p}}{b_{x_{p-1}+1,x_p}}=C$。

$$\large{B=\sum\limits_{i=1}^{m}b_{x_{i-1}+1,x_i}}$$

$$\large{W=\sum\limits_{i=1}^{m}w_{x_{i-1}+1,x_i}}$$

$$\large{\dfrac{W}{B}=\dfrac{\sum\limits_{i=1}^{m}w_{x_{i-1}+1,x_i}}{\sum\limits_{i=1}^{m}b_{x_{i-1}+1,x_i}}=C}$$

$$\forall p\in[1,m], \dfrac{w_{x_{p-1}+1,x_p}}{b_{x_{p-1}+1,x_p}}=\dfrac{W}{B}$$
为了避免存在 ${W}:{B}$ 无定义的情况，先特判 ${B=0}$ 的情况，在这种情况下，显然每一块分一个区间最优。

现在已知了每个区间的 $C$ 值，考虑如何划分区间。

每次取最小的 $x$ 使 $w_{1,x}:b_{1,x}=C$，分出区间 $[1,x]$，然后在区间 $(x,\mathrm{len}]$ 重复以上操作。

正确性证明：反证。

如果这个结论是错的，那么就一定存在一个序列，使其的最优划分方式中的最靠左的区间（设其为 $[1,y]$）不为**最小的 $x$ 使 $w_{1,x}:b_{1,x}=W:B$ 时**的 $[1,x]$。显然 $y>x$。

$$w_{1,y}:b_{1,y}=C=w_{1,x}:b_{1,x}$$

$$\dfrac{w_{1,y}}{b_{1,y}}=\dfrac{w_{1,x}}{b_{1,x}}$$

$$\dfrac{w_{1,y}}{b_{1,y}}=\dfrac{w_{1,y}-w_{1,x}}{b_{1,y}-b_{1,x}}$$

$$\dfrac{w_{1,y}}{b_{1,y}}=\dfrac{w_{x+1,y}}{b_{x+1,y}}$$

$$W:B={w_{x+1,y}}:{b_{x+1,y}}$$

所以 $[x+1,y]$ 是一个合法的区间。

显然，将上述的“最优划分方式”中 $[1,y]$ 换成 $[1,x]$ 和 $[x+1,y]$ 是合法的，而且更优，与上述假设矛盾。

所以贪心是最优的。

```cpp
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
int t,n,bcnt,wcnt,ans,cb,cw;
vector<pair<int,char>> sq;
int main()
{
	cin>>t;
	while(t--)
	{
		sq.clear();
		cin>>n;
		bcnt=0;
		wcnt=0;
		for(int i=1;i<=n;++i)
		{
			int cnt;
			char col;
			cin>>cnt>>col;
			if(col=='B') bcnt+=cnt;
			else wcnt+=cnt;
			sq.push_back(make_pair(cnt,col));
		}
		ans=cb=cw=0;
		if(wcnt==0 || bcnt==0)
		{
			for(auto seg : sq) ans+=seg.first;
			cout<<ans<<endl;
			continue;
		}
		int gcd=__gcd(wcnt,bcnt);
		wcnt/=gcd;
		bcnt/=gcd;
		cerr<<"Ratio: "<<bcnt<<" : "<<wcnt<<endl;
		for(int i=0;i<sq.size();++i)
		{
			bool flg=0;
			if(sq[i].second=='B')
			{
				if(cw%wcnt==0 && cw!=0)
				{
					int tms=cw/wcnt;
					int rq=bcnt*tms;
					int diff=rq-cb;
					if(diff>0 && diff<=sq[i].first)
					{
						ans++;
						cb=0;
						cw=0;
						flg=1;
						if((sq[i].first-diff)>0)
						{
							sq[i].first-=diff;
							i--;
						}
					}
				}
				if(!flg)
				{
					cb+=sq[i].first;
				}
			}
			else if(sq[i].second=='W')
			{
				if(cb%bcnt==0 && cb!=0)
				{
					int tms=cb/bcnt;
					int rq=wcnt*tms;
					int diff=rq-cw;
					if(diff>0 && diff<=sq[i].first)
					{
						ans++;
						cw=0;
						cb=0;
						flg=1;
						if((sq[i].first-diff)>0)
						{
							sq[i].first-=diff;
							i--;
						}
					}
				}
				if(!flg)
				{
					cw+=sq[i].first;
				}
			}
		}
		cout<<ans<<endl;
	}
}
```


---

