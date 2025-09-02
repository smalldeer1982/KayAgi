# Full Turn

## 题目描述

There are $ n $ persons located on a plane. The $ i $ -th person is located at the point $ (x_i, y_i) $ and initially looks at the point $ (u_i, v_i) $ .

At the same moment of time, all persons will start to rotate clockwise synchronously with the same angular speed. They will rotate until they do one full $ 360 $ -degree turn.

It is said that persons $ A $ and $ B $ made eye contact if person $ A $ looks in person $ B $ 's direction at the same moment when person $ B $ looks in person $ A $ 's direction. If there is a person $ C $ located between persons $ A $ and $ B $ , that will not obstruct $ A $ and $ B $ from making eye contact. A person can make eye contact with more than one person at the same time.

Calculate the number of pairs of persons that will make eye contact at least once during the rotation (including the initial moment).

## 样例 #1

### 输入

```
3
2
0 0 0 1
1 0 2 0
3
0 0 1 1
1 1 0 0
1 0 2 0
6
0 0 0 1
1 0 1 2
2 0 2 3
3 0 3 -5
4 0 4 -5
5 0 5 -5```

### 输出

```
0
1
9```

# 题解

## 作者：npqenqpve (赞：2)

### 题意：

给你 $n$ 个以 $(x,y)$ 为开始，过点 $(u,v)$ 的射线，现在这些射线开始顺时针旋转，问有多少对射线可以同时互相过对方的 $(x,y)$ 。

### 思路：

首先思考什么时候会出现题目中这种情况，把射线所在直线画出发现如果两个直线不平行则始终存在一个夹角，那么只有两条射线所在直线平行时才行，但是射线方向相同时显然不行。

那么满足题意的射线必须满足：

- 所在直线平行 $(k_1=k_2)$
- 方向相反

存斜率，判断方向就是把所有 $(x,y)$ 移动到原点然后判断 $(u,v)$ 所在象限即可 。

但是实测直接存斜率会挂精度，所以对斜率双哈希一下就行 。

### 代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n;
struct node
{
	int x,y,u,v,op,k1,k2;
}a[(int)(1e5)+10];
map<pair<int,int>,int>m;
signed main()
{
	int t;cin>>t;
	while(t--)
	{
		m.clear();
		cin>>n;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i].x>>a[i].y>>a[i].u>>a[i].v;
			a[i].u-=a[i].x;
			a[i].v-=a[i].y;
			a[i].x=a[i].y=0;
		}
		for(int i=1;i<=n;i++)
		{
			if(a[i].v==0)
			{
				if(a[i].u>0)
				{
					a[i].k1=99224992999;
					a[i].k2=1919810;
					a[i].op=-3;
				}
				if(a[i].u<0)
				{
					a[i].k1=99224992999;
					a[i].k2=1919810;
					a[i].op=3;
				}
				m[make_pair(a[i].k1+a[i].k2,a[i].op)]++;
				continue;
			}
			if(a[i].u==0)
			{
				if(a[i].v>0)
				{
					a[i].k1=1149850917;
					a[i].k2=114514;
					a[i].op=-4;
				}
				if(a[i].v<0)
				{
					a[i].k1=1149850917;
					a[i].k2=114514;
					a[i].op=4;
				}
				m[make_pair(a[i].k1+a[i].k2,a[i].op)]++;
				continue;
			}
			a[i].k1=(int)(998244353*(double)((double)a[i].v/(double)a[i].u))%(1000000000007);
			a[i].k2=(int)((int)(2147483647)*(double)((double)a[i].v/(double)a[i].u))%(998244353);
			if(a[i].u>0&&a[i].v>0)
			{
				a[i].op=-1;
			}
			if(a[i].u<0&&a[i].v>0)
			{
				a[i].op=-2;
			}
			if(a[i].u<0&&a[i].v<0)
			{
				a[i].op=1;
			}
			if(a[i].u>0&&a[i].v<0)
			{
				a[i].op=2;
			}
			m[make_pair(a[i].k1+a[i].k2,a[i].op)]++;
		}
		int ans=0;
//		for(int i=1;i<=n;i++)
//		{
//			cout<<a[i].k<<" "<<a[i].op<<"\n";
//		 } 
		for(int i=1;i<=n;i++)
		{
			ans+=m[make_pair(a[i].k1+a[i].k2,-a[i].op)];
//			cout<<a[i].k<<" "<<-a[i].op<<"\n";
//			cout<<m[make_pair(a[i].k,-a[i].op)]<<"\n";
		}
		cout<<ans/2<<"\n";
	}
}
```



---

## 作者：Jinzixun (赞：1)

显然，只有两个人面朝的方向相反，他们才会眼神接触。

接下来考虑如何表示方向。

可以将每个人平移移到 $(0,0)$，通过计算最简面朝的坐标进行表示。

代码比较简洁。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t, n;
signed main(){
	scanf("%lld", &t);
	while(t--){
		int ans = 0;
		map<pair<int, int>, int> mp;//map 统计面朝这个方向的数量。
		scanf("%lld", &n);
		while(n--){
			int x, y, u, v;
			scanf("%lld%lld%lld%lld", &x, &y, &u, &v);
			u -= x;
			v -= y;//计算平移后面朝的方向。
			int g = abs(__gcd(u, v));
			u /= g;
			v /= g;//化简为最简方向。
			ans += mp[make_pair(-u, -v)];//增加此前和这个人方向相反的人的个数。
			mp[make_pair(u, v)]++;//添加这个人。
		}
		printf("%lld\n", ans);
	}
	return 0;
}
```

---

## 作者：hzoi_liuchang (赞：1)

## 分析
我们求出给定的两点形成的直线的斜率

不难发现，斜率相等的点一定能够在旋转的过程中发生交流

因为内错角相等两直线平行

又因为直线是有方向的 

所以我们开两个数组分别记录一下不同的方向，然后双指针匹配即可
## 代码
``` cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<queue>
#include<cmath>
#define rg register
inline int read(){
	rg int x=0,fh=1;
	rg char ch=getchar();
	while(ch<'0' || ch>'9'){
		if(ch=='-') fh=-1;
		ch=getchar();
	}
	while(ch>='0' && ch<='9'){
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x*fh;
}
const int maxn=1e5+5;
const long double eps=1e-15;
long double sta1[maxn],sta2[maxn];
int tp1,tp2,t,n,js1,js2;
long long ans=0;
int main(){
	t=read();
	while(t--){
		n=read();
		tp1=tp2=js1=js2=0;
		rg int aa,bb,cc,dd;
		ans=0;
		for(rg int i=1;i<=n;i++){
			aa=read(),bb=read(),cc=read(),dd=read();
			if(aa==cc){
				if(bb>dd) js1++;
				else js2++;
			} else {
				if(aa>cc) sta1[++tp1]=1.0*(dd-bb)/(cc-aa);
				else sta2[++tp2]=1.0*(dd-bb)/(cc-aa);
			}
		}
		ans+=1LL*js1*js2;
		std::sort(sta1+1,sta1+tp1+1);
		std::sort(sta2+1,sta2+tp2+1);
		rg int head=1;
		for(rg int i=1;i<=tp1;i++){
			rg int j=i;
			while(std::fabs(sta1[j]-sta1[i])<eps && j<=tp1) j++;
			while(sta1[i]-sta2[head]>eps && head<=tp2) head++;
			rg int tail=head;
			while(std::fabs(sta2[tail]-sta1[i])<eps && tail<=tp2) tail++;
			ans+=1LL*(j-i)*(tail-head);
			head=tail;
			i=j-1;
		}
		printf("%lld\n",ans);
	}
	return 0;	
}

```

---

## 作者：conti123 (赞：0)

## CF1468F Full Turn

小清新数学题。

考虑两人视线相交前在干什么。

如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/5pgrq131.png)

由题意的两角相等，所以两线平行，而且观察到方向相反。

于是考虑直接统计有多少斜率相同的线，并判断方向即可。

为此我们可以用两个容器维护，具体看代码。

顺便说一下直线斜率。

根据不知哪里的知识，过点 $(x_1,y_1),(x_2,y_2)$ 的直线斜率 $k=\frac{y_1-y_2}{x_1-x_2}$

这里需要注意一下平行于坐标轴的线。

```cpp

void solve(){
	map<double,int>A1,A2;
	set<double>B;
	cin>>n;
	int cnt1=0,cnt2=0,cnt3=0,cnt4=0;//统计特殊的线
	B.clear();
	A1.clear();
	A2.clear();
	for(int i=1;i<=n;i++){
		int x,y,X,Y;
		cin>>x>>y>>X>>Y;
  //注意方向
		if(X==x){
			if(Y>y)
				cnt1++;
			else
				cnt2++;
		}
		else if(y==Y){
			if(X>x)
				cnt3++;
			else
				cnt4++;
		}
		else{
			double p=(Y-y)*1.0/((X-x)*1.0);
			if(Y>y)A1[p]++;
			else A2[p]++;
			B.insert(p);
			
		}
	}
	int ans=cnt1*cnt2+cnt3*cnt4;
	for(double v:B){
		ans+=A1[v]*A2[v];
	}
	cout<<ans<<"\n";
}
//听说精度可能会炸？不行就用哈希搞一下，反正VP时是可以过的。
```

---

## 作者：jhdrgfj (赞：0)

## 解法

首先易证两个人会进行眼神接触当且仅当两人视角的方向相反，感性理解一下，在旋转的过程中两人视角的方向差是不变的，所以如果没有一开始就相对，那么继续旋转也不会相对。

那么接下来就简单了，首先求出每个人眼神的方向向量 $(x_i,y_i)$，用 ``map`` 进行储存。然后遍历每个人眼神的方向向量，对于每个方向向量 $(x_i,y_i)$，将 $ans+m_{-x_i,-y_i}$。

如何求出方向向量？首先将每个人平移至 $(0,0)$，则视角移至 $(u-x,v-y)$。然后将新的视角的坐标同时除以 $\gcd(u-x,v-y)$，就得到了最简的方向向量。注意要特判 $u-x=0$ 或 $v-y=0$ 的情况。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std; 
vector<int> x,y;    //用于储存坐标值
int main() { 
    int t; cin>>t; 
    while (t--){ 
        map<pair<int,int>,long long> m;   //由于本题爆精度，要用整数存方向向量
        long long n,ans=0ll; 
        cin>>n; 
        x.push_back(0);
        y.push_back(0);   //vector 默认从 0 开始，先存一个数占位
        for (int i=1;i<=n;i++){ 
            long long x1,x2,y1,y2; 
            cin>>x1>>y1>>x2>>y2;
            x.push_back(x2-x1);
            y.push_back(y2-y1);
            if (x[i]==0){
                y[i]=y[i]/abs(y[i]);
            }
            if (y[i]==0){
                x[i]=x[i]/abs(x[i]);
            }                    //特判 x,y=0
            int gcd=abs(__gcd(x[i],y[i]));
            x[i]/=gcd;
            y[i]/=gcd;
            m[make_pair(x[i],y[i])]++;
        }
        for (int i=1;i<=n;i++){
            ans+=m[make_pair(-x[i],-y[i])];    //统计答案
        } 
        cout<<ans/2ll<<endl;       //由于每一对人会算两次，要除以 2
        x.clear();
        y.clear();
    }
}
```


---

