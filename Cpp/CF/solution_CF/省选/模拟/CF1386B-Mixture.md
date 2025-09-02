# Mixture

## 题目描述

Serge, the chef of the famous restaurant "Salt, Pepper &amp; Garlic" is trying to obtain his first Michelin star. He has been informed that a secret expert plans to visit his restaurant this evening.

Even though the expert's name hasn't been disclosed, Serge is certain he knows which dish from the menu will be ordered as well as what the taste preferences of the expert are. Namely, the expert requires an extremely precise proportion of salt, pepper and garlic powder in his dish.

Serge keeps a set of bottles with mixtures of salt, pepper and garlic powder on a special shelf in the kitchen. For each bottle, he knows the exact amount of each of the ingredients in kilograms. Serge can combine any number of bottled mixtures (or just use one of them directly) to get a mixture of particular proportions needed for a certain dish.

Luckily, the absolute amount of a mixture that needs to be added to a dish is so small that you can assume that the amounts in the bottles will always be sufficient. However, the numeric values describing the proportions may be quite large.

Serge would like to know whether it is possible to obtain the expert's favourite mixture from the available bottles, and if so—what is the smallest possible number of bottles needed to achieve that.

Furthermore, the set of bottles on the shelf may change over time as Serge receives new ones or lends his to other chefs. So he would like to answer this question after each such change.

For example, assume that expert's favorite mixture is $ 1:1:1 $ and there are three bottles of mixtures on the shelf:

  $ $$$ \begin{array}{cccc} \hline \text{Mixture} &       \text{Salt} & \text{Pepper} & \text{Garlic powder} \\       \hline 1 & 10 & 20 & 30 \\ 2 & 300 & 200 &       100 \\ 3 & 12 & 15 & 27 \\ \hline \end{array}  $ $$$ Amount of ingredient in the bottle, kg To obtain the desired mixture it is enough to use an equivalent amount of mixtures from bottles 1 and 2. If bottle 2 is removed, then it is no longer possible to obtain it.

Write a program that helps Serge to solve this task!

## 说明/提示

Pay attention that in the example, bottles $ 1 $ and $ 3 $ contain the same proportions of salt, pepper and garlic powder.

## 样例 #1

### 输入

```
1 2 3
6
A 5 6 7
A 3 10 17
R 1
A 15 18 21
A 5 10 15
R 3```

### 输出

```
0
2
0
2
1
1```

# 题解

## 作者：丛雨 (赞：1)

# CF1386B Mixture

> 题意:初始给出一个目标空间向量$N=(S_f,P_f,G_f)$和初始为空的空间向量的**可重**集$I$，每次选择增加或删去一个空间向量$(S_i,P_i,G_i)$，求最小集合$U$使得$U\subseteq I$且存在长度为$|U|$的序列$\lambda$,使得$\forall i,\lambda_i>0$且$\sum_{i=1}^{|U|}\lambda_iU_i=N$($U_i$表示$U$中第$i$个向量，顺序无实意)

将题意转换成上面的样子后，我们就已经可以得到$n^2$的判断线性无关问题(因为$\lambda >0$)

我们就可以先进行一些恒等变换：

$$
\begin{cases}
\sum_{i=1}^n\lambda_i S_i=S_f\\
\sum_{i=1}^n\lambda_i P_i=P_f\\
\sum_{i=1}^n\lambda_i G_i=G_f\\
\end{cases}
\Rightarrow\sum_{i=1}^n\lambda_iS_iP_fG_f=\sum_{i=1}^n\lambda_iS_fP_iG_f=\sum_{i=1}^n\lambda_iS_fP_fG_i=S_fP_fG_f
$$


这时我们就发现可以将$(S_iP_fG_f,S_fP_iG_f,S_fP_fG_i)$看成一个向量，问题则转换成了与$(S_fP_fG_f,S_fP_fG_f,S_fP_fG_f)$线性相关的最小向量组大小

下面我们就暂时先忽略$\lambda>0$的要求，只要求$\lambda\not= 0$

我们不难发现$(S_fP_fG_f,S_fP_fG_f,S_fP_fG_f)$在直线$x=y=z$上.为了降维，我们可以考虑将向量组旋转一定空间角度，使之转到$z$轴，即乘上$\left(\begin{matrix}\cos\frac{\pi}{4}&\sin\frac{\pi}{4}&0\\-\sin\frac{\pi}{4}&\cos\frac{\pi}{4}&0\\0&0&1\end{matrix}\right)\left(\begin{matrix}\frac{\sqrt 3}{3}&0&-\frac{\sqrt 6}{3}\\0&1&0\\\frac{\sqrt 6}{3}&0&\frac{\sqrt 3}{3}\end{matrix}\right)$

~~（我懒得算了~~

此时只需要使空间向量的和在$z$轴上即可，即$\sum_{i=1}^n\lambda_i x_i=\sum_{i=1}^n\lambda_i y_i=0$，而$z$坐标无限制

此时我们便可以将原先的三维向量转换为二维向量了，要求则变为了求出最少的向量使得可以从原点到达原点

如果没有$\lambda>0$的限制，则~~显然答案为1~~

我们同样可以发现，答案不会大于$3$

当存在**新**向量为0向量时，答案为$1$

当存在**新**向量中有相反向量时，答案为$2$

当存在**新**向量在另外两向量的相反向量之间时，答案为$3$

时间复杂度$O(n\log n)$，但是因为不能用$\tt \_\_int128$,所以在叉乘时代码有点复杂.

还有不能用$\tt (long )double$，会爆精度

```cpp
#include<bits/stdc++.h>
using namespace std;
# define ll long long
# define read read1<ll>()
# define Type template<typename T>
Type T read1(){
	T t=0;
	char k;
	bool vis=0;
	do (k=getchar())=='-'&&(vis=1);while('0'>k||k>'9');
	while('0'<=k&&k<='9')t=(t<<3)+(t<<1)+(k^'0'),k=getchar();
	return vis?-t:t;
}
# define fre(k) freopen(k".in","r",stdin);freopen(k".out","w",stdout)
# define ld long double
# define eps 1e-9
ll Abs(ll x){return x<0?-x:x;}
char str[3];
int t;ll tot;
const ll V=1ll<<31;
const double Pi=acos(-1);
map<pair<ll,ll>,int>ma;
pair<ll,ll>A[100005];
bool judge(ll x,ll y,ll z,ll w){
	if((x==0||y==0)&&(z==0||w==0))return 0;
	if(x==0||y==0)return (z<0)^(w<0);
	if(z==0||w==0)return (x<0)==(y<0);
	if((x>0)*(y>0)!=(z>0)*(w>0))return (x>0)*(y>0)>(z>0)*(w>0);
	ll l1=(x/V)*(y/V)+((x%V)*(y/V)+(x/V)*(y%V))/V,l2=((x%V)*(y/V)+(x/V)*(y%V))%V+(x%V)*(y%V)/V,l3=(x%V)*(y%V)%V;
	ll r1=(z/V)*(w/V)+((z%V)*(w/V)+(z/V)*(w%V))/V,r2=((z%V)*(w/V)+(z/V)*(w%V))%V+(z%V)*(w%V)/V,r3=(z%V)*(w%V)%V;
	if(l3>=V)l2+=l3/V,l3%=V;if(l2>=V)l1+=l2/V,l2%=V;
	if(r3>=V)r2+=r3/V,r3%=V;if(r2>=V)r1+=r2/V,r2%=V;
	return l1==r1?l2==r2?l3>r3:l2>r2:l1>r1;
}
const int E[3][3]={{6,7,8},{5,9,1},{4,3,2}};
struct X{
	ll x,y;
	X(ll _x=0,ll _y=0){x=_x;y=_y;}
	X(pair<ll,ll>z):x(z.first),y(z.second){}
	int Wh()const{return E[(y>0)+(y>=0)][(x>0)+(x>=0)];}
	X operator -()const{return X(-x,-y);}
	bool operator <(const X &w)const{return judge(x,w.y,y,w.x);}
	bool operator >(const X &w)const{return w<*this;}
	bool operator <=(const X &w)const{return !(*this>w);}
	bool operator >=(const X &w)const{return w<=*this;}
	bool operator ==(const X &w)const{return !(*this<w||*this>w);}
};
multiset<X>se[2];
X va[100005];
ll Gcd(ll x,ll y){if(y<0||x<0)return Gcd(Abs(x),Abs(y));if(!x)return y;while(y)swap(y,x%=y);return x;}
bool judge(){
	if(se[0].size()>1){
		auto l=se[0].begin(),r=se[0].end(),x=se[1].lower_bound(-*l);--r;
		if(x!=se[1].end()&&*x<=-*r)return 1;
	}if(se[1].size()>1){
		auto l=se[1].begin(),r=se[1].end(),x=se[0].lower_bound(-*l);--r;
		if(x!=se[0].end()&&*x<=-*r)return 1;
	}return 0;
}
int main(){
	ll a=read,b=read,c=read;
	int w=0;
	if(a==0)swap(a,b),w|=1;
	if(a==0)swap(a,c),w|=2;
	int cnt=0;
	for(int T=read;T--;){
		scanf("%s",str);
		if(*str=='A'){
			ll x=read,y=read,z=read;
			if(w&1)swap(x,y);
			if(w&2)swap(x,z);
			if(b==0&&y!=0){A[++cnt]=make_pair(2,4);goto OP;}
			if(c==0&&z!=0){A[++cnt]=make_pair(2,4);goto OP;}
			y=b*x-a*y;z=c*x-a*z;
			if(c)y*=c;if(b)z*=b;
			x=Gcd(y,z);if(x)y/=x,z/=x;
			tot+=ma[make_pair(-y,-z)];
			if(!ma[A[++cnt]=make_pair(y,z)]++)++t;
			va[cnt]=X(y,z);
			if(y||z)
				if(va[cnt].Wh()<=4)se[0].insert(va[cnt]);
				else se[1].insert(va[cnt]);
		}else{
			int v=read;
			if(A[v].first==2&&A[v].second==4)goto OP;
			if(!--ma[A[v]])--t;
			tot-=ma[make_pair(-A[v].first,-A[v].second)];
			if(va[v].x||va[v].y)
				if(va[v].Wh()<=4)se[0].erase(se[0].lower_bound(va[v]));
				else se[1].erase(se[1].lower_bound(va[v]));
		}OP:;
		if(ma[make_pair(0,0)])puts("1");
		else if(tot)puts("2");
		else if(t>2&&judge())puts("3");
		else puts("0");
	}
	return 0;
}
```



---

## 作者：良心WA题人 (赞：0)

三维很难看啊，考虑降维度，给所有的数除一个 $x+y+z$，则满足了所有的和都为 $1$，那么在满足前两维的时候就会自然满足第三维了。

有个经典结论是选择一些点，能取到的点在他们围成的凸包内。因为多边形有三角剖分，所以答案最大为 $3$。把目标看作原点，下面分情况讨论一下：

当答案为 $1$ 时，存在一个点就在原点上。可以记录原点上的点数 $cnt$ 完成修改。

当答案为 $2$ 时，存在两个点关于原点中心对称，可以通过 `set` 存极角动态求满足的点对个数。

剩下要么是无解或答案为 $3$ 了。如果存在一条过原点的直线满足所有的点全在半边则一定无解，否则一定有解。$x$ 正负半轴和 $y$ 正负半轴一定存在一个不在有点的那一半内，所以可以找到这些极角的前一个和后一个点，看它们到原点连线形成的角是否大于 $180$ 度即可。

注意极角是 $2\times \pi$ 一个周期的，需要一定的特判。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long double ld;
const int NN=1e5+4;
const ld eps=1e-12,PI=acos(-1);
ld x[NN],y[NN];
int w1,w2,w3;
multiset<ld>st;
bool find(ld t)
{
	if(!st.size())
		return false;
	bool flag=false;
	if(abs(t+PI)<eps)
		t=PI;
	auto it=st.lower_bound(t-eps);
	if(it==st.end())
		flag=true,it=st.begin();
	if(!flag)
		return *it-t<eps;
	return 2*PI-t+*it<eps;
}
bool check(ld t)
{
	bool flag=false;
	auto it1=st.lower_bound(t),it2=st.lower_bound(t);
	if(it1==st.begin())
		flag=true,it1=st.end();
	it1--;
	if(it2==st.end())
		flag=true,it2=st.begin();
	if(!flag)
		return *it2-*it1>PI;
	return *it2-*it1>-PI;
}
int main()
{
	ld X,Y,Z;
	scanf("%Lf%Lf%Lf",&X,&Y,&Z);
	ld s=X+Y+Z;
	X/=s,Y/=s;
	int q,idx=0;
	scanf("%d",&q);
	while(q--)
	{
		char opt[4];
		scanf("%s",opt);
		if(opt[0]=='A')
		{
			idx++;
			ld z;
			scanf("%Lf%Lf%Lf",&x[idx],&y[idx],&z);
			s=x[idx]+y[idx]+z;
			x[idx]=x[idx]/s-X,y[idx]=y[idx]/s-Y;
			if(abs(x[idx])<eps&&abs(y[idx])<eps)
				w1++;
			else
			{
				w2+=!find(atan2l(y[idx],x[idx]))&&find(atan2l(-y[idx],-x[idx]));
				st.insert(atan2l(y[idx],x[idx]));
			}
		}
		else
		{
			int u;
			scanf("%d",&u);
			if(abs(x[u])<eps&&abs(y[u])<eps)
				w1--;
			else
			{
				st.erase(st.find(atan2l(y[u],x[u])));
				w2-=!find(atan2l(y[u],x[u]))&&find(atan2l(-y[u],-x[u]));
			}
		}
		if(w1)
			puts("1");
		else if(w2)
			puts("2");
		else
		{
			if(!st.size()||check(-PI)||check(0)||check(PI)||check(2*PI))
				puts("0");
			else
				puts("3");
		}
	}
	return 0;
}
```

---

